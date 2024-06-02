from flask import Flask, g
from application.blueprints.routes import api

app = Flask(__name__)
app.config.from_object('application.config.Config')

app.register_blueprint(api)

@app.teardown_appcontext
def close_connection(exception):
    db = getattr(g, '_database', None)
    if db is not None: db.close()