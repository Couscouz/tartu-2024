from application.app import app
from application.database import migrate_db
from flasgger import Swagger
import yaml

with app.app_context():
    migrate_db()
    
# Load Flasgger configuration from YAML file
with open('/app/secprog_hw1_api.yml', 'r') as file:
    flasgger_config = yaml.safe_load(file)

swagger = Swagger(app, config=flasgger_config, merge=True)

app.run(host='0.0.0.0', port=8080, debug=False, use_evalex=False)