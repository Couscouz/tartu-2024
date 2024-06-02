import jwt
KEY=12345
token = jwt.encode({"isadmin": True}, str(KEY))
print(token)