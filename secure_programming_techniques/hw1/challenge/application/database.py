from flask import g
from application import app
from sqlite3 import dbapi2 as sqlite3

def connect_db():
    return sqlite3.connect('school.db', isolation_level=None)
    
def get_db():
    db = getattr(g, '_database', None)
    if db is None:
        db = g._database = connect_db()
        db.row_factory = sqlite3.Row
    return db

def query_db(query, args=(), one=False):
    with app.app.app_context():
        cur = get_db().execute(query, args)
        rv = [dict((cur.description[idx][0], value) \
            for idx, value in enumerate(row)) for row in cur.fetchall()]
        return (next(iter(rv[0].values())) if rv else None) if one else rv
    
def populate_db(query, args=()):
    with app.app.app_context():
        con = get_db()
        con.cursor().execute(query, args)
        con.commit()
        con.close()

def migrate_db():
    with open('schema.sql', mode='r') as f:
        get_db().cursor().executescript(f.read())
    get_db().commit()
