from functools import wraps
from flask import request, jsonify, current_app
from application.models import school
import jwt

def generate(email, password, isadmin=False):
    try:
        return  jwt.encode(
                    {"user_id": school.select_by_email(email)[0]['id'],
                    "email": email,
                    "password": password,
                    "isadmin": school.select_by_email(email)[0]['isadmin'] or isadmin},
                    current_app.config['SECRET_KEY']
                )
    except Exception as e:
         return {"error": "Something went wrong"}, 500

def decode_token(token):
    try:
        return jwt.decode(token, current_app.config['SECRET_KEY'], algorithms=['HS256'])
    
    except Exception as e:
         return {"error": "Something went wrong"}, 500



def auth_required(fn):
   @wraps(fn)
   def decorator(*args, **kwargs):
       token = None
       if 'Authorization' in request.headers:
           token = request.headers["Authorization"].split(" ")[1]
 
       if not token:
           return jsonify({'message': 'Authorization token is missing!'})
       try:
           decode_token(token)
       except:
           return jsonify({'message': 'User is not authorized! :('})
       
       return fn(*args, **kwargs)
 
   return decorator

def admin_required(fn):
   @wraps(fn)
   def decorator(*args, **kwargs):
       token = None
       if 'Authorization' in request.headers:
           token = request.headers["Authorization"].split(" ")[1]

       if not token:
           return jsonify({'message': 'Authorization token is missing!'})
       try:
           data = decode_token(token)
           if bool(data['isadmin']) != True:
            return  jsonify({'message': 'User is not authorized!'})         
       except:
            return jsonify({'message': 'Unexpected issue occurred!'})
        
       return fn(*args, **kwargs)
   return decorator