# Source Generated with Decompyle++
# File: tokenGenerator.pyc (Python 3.10)

import sqlite3
import pickle
from base64 import b64encode, b64decode

class User:
    
    def __init__(self, username, rank):
        self.username = username
        self.rank = rank

    
    def summary(self):
        print('Token info: ', self.username, ';', self.rank)



def addInfo(name, object):
    conn = sqlite3.connect('tokens.db')
    cursor = conn.cursor()
    auth_token = b64encode(pickle.dumps(object))
    serialized_data = auth_token
    cursor.execute('CREATE TABLE IF NOT EXISTS serialized_objects\n                      (id INTEGER PRIMARY KEY, name TEXT, serialized_data BLOB)')
    cursor.execute('INSERT INTO serialized_objects (name, serialized_data) VALUES (?, ?)', (name, serialized_data))
    conn.commit()
    conn.close()


def getInfo(name):
    conn = sqlite3.connect('tokens.db')
    cursor = conn.cursor()
    cursor.execute('SELECT serialized_data FROM serialized_objects WHERE name = ?', (name,))
    row = cursor.fetchone()
    data = row[0]
    conn.close()
    return data


def checkToken(token):
    deserialized_data = pickle.loads(b64decode(token))
    return deserialized_data

# WARNING: Decompyle incomplete