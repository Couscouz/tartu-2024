from flask import Blueprint, request, jsonify
from werkzeug.security import check_password_hash
from application.models import school
from .jwt import *

api = Blueprint('api', __name__, url_prefix='/api')

@api.route('/')
def index():
    return jsonify({'Hello': ', world!'})

@api.route('/login', methods=['POST'])
def login():

    #TODO: Add some validation?
    post_data = request.form
    user = school.select_by_email(post_data['email'])

    if not user or not check_password_hash(user[0]['password'], post_data['password']):
        return jsonify({'message': 'Invalid email or password!'})

    token = generate(*post_data.values())
    return jsonify({'message': 'Success!', "token": token})

@api.route('/signup', methods=['POST'])
def signup():

    #TODO: Add some validation?
    post_data = request.form

    if not school.select_by_email(post_data['email']):
        school.create_new_user(*post_data.values())
        return jsonify({'message': 'Created new user!','user': post_data['email']})

    else:
        return jsonify({'message': 'User already exists'})

@api.route('/users/<user_id>', methods=['GET'])
@auth_required
def user(user_id):
    return {"user_id": user_id}

@api.route('/logout', methods=['POST'])
@auth_required
def logout():
    school.delete_jwt_token(request.headers["Authorization"])
    return jsonify({'message': 'Success!'})

@api.route('/grades', methods=['GET'])
@auth_required
def get_grades():
    try:
        profile = decode_token(request.headers["Authorization"].split(" ")[1])
        grades = None

        if(profile['isadmin']  == 1):
            grades = school.get_grades(None)
        
        else:
            grades = school.get_grades(profile['user_id'])

        return jsonify({'grades': grades})
    except:
           return jsonify({'message': 'Unexpected issue occurred!'})

@api.route('/average-grade', methods=['GET'])
@auth_required
def average_grade():

    user_id = decode_token(request.headers["Authorization"].split(" ")[1])['user_id']    
    grades = school.get_grades(user_id) 
    vals = [entry['grade'] for entry in grades]

    try:
        return jsonify({'message': 'Success!', 'average_grade': sum(vals) / len(vals) })
    except ZeroDivisionError:
        return jsonify({'message': 'Student has no grades yet!', 'average_grade': 0})

@api.route('/grades/<user_id>', methods=['GET', 'POST', 'DELETE'])
@admin_required
def manage_grade(user_id):

    post_data = request.form
    if request.method == 'POST':    
        school.add_grade(*post_data.values(), user_id)
    elif request.method == 'DELETE':
        school.delete_grade(user_id)

    grades = school.get_grades(user_id)
    return jsonify({'grades': grades})


@api.route('/users', methods=['GET', 'DELETE'])
@admin_required
def users():
    users = school.all_users()
    return jsonify(users)

@admin_required
@api.route('/users/<user_id>', methods=['DELETE'])
def delete(user_id):
    try:
        school.delete_user(user_id)
    except:
           return jsonify({'message': 'Unexpected issue occurred!'})
    return jsonify({'message': 'Success! User is deleted'})