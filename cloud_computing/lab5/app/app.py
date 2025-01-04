import logging
import json
import uuid
from datetime import datetime
import os
from flask import Flask, render_template, request
from azure.storage.blob import BlobServiceClient
import azure.cosmos.cosmos_client as cosmos_client
import azure.cosmos.exceptions as exceptions

app = Flask(__name__)
logging.basicConfig(level=logging.DEBUG)


app.logger.info("LAB5 Started")

UPLOAD_FOLDER ='./static/images'

CONN_KEY = os.getenv('APPSETTING_CONN_KEY')
storage_account = os.getenv('APPSETTING_STORAGE_ACCOUNT')
images_container = "images"

COSMOS_URL = os.getenv('APPSETTING_COSMOS_URL')
MasterKey = os.getenv('APPSETTING_MasterKey')
DATABASE_ID='lab5messagesdb'
CONTAINER_ID='lab5messages'

blob_service_client = BlobServiceClient(account_url="https://"+storage_account+".blob.core.windows.net/",credential=CONN_KEY)

cosmos_db_client = cosmos_client.CosmosClient(COSMOS_URL, {'masterKey': MasterKey} )
cosmos_db = cosmos_db_client.get_database_client(DATABASE_ID)
container = cosmos_db.get_container_client(CONTAINER_ID)


def insert_blob(img_path):
    filename = (img_path).split('/')[-1]
    blob_client = blob_service_client.get_blob_client(container=images_container, blob=filename)
    with open(file=img_path, mode="rb") as data:
       	blob_client.upload_blob(data,overwrite=True)

def insert_cosmos(img_path, username, content):
    app.logger.info("Inserting in cosmos")
    new_message = {
        'id': str(uuid.uuid4()),
        'username': username,
        'content': content,
        'img_path': img_path,
        'timestamp': datetime.now().isoformat(" ", "seconds")
    }
    try:
        container.create_item(body=new_message)
    except exceptions.CosmosResourceExistsError:
        app.logger.info("Resource already exists, didn't insert message.")

def read_cosmos():
    """ Read last 10 messages from cosmos """
    messages = list(container.read_all_items(max_item_count=10))
    return messages

def read_messages_from_file():
    """ Read all messages from a JSON file"""
    with open('data.json') as messages_file:
        return json.load(messages_file)

def append_message_to_file(img_path, content):
    """ Read the contents of JSON file, add this message to it's contents, then write it back to disk. """
    data = read_messages_from_file()
    new_message = {
        'content': content,
        'img_path': img_path,
        'timestamp': datetime.now().isoformat(" ", "seconds")
    }

    data['messages'].append(new_message)

    with open('data.json', mode='w') as messages_file:
        json.dump(data, messages_file)



# The Flask route, defining the main behaviour of the webserver:
@app.route("/handle_message", methods=['POST'])
def handleMessage():
    app.logger.info("handleMessage")
    new_username = request.form['username']
    new_message = request.form['msg']
    img_path = ""
    blob_path = ""

    allowed_extensions = [".png",".jpg",".JPG",".jpeg",".SVG",".gif"]

    if ('file' in request.files and request.files['file']):
        image = request.files['file']
        img_ext = os.path.splitext(image.filename)[1]
        app.logger.info(f"image extension = {img_ext}")
        if (img_ext in allowed_extensions):
            img_path = os.path.join(UPLOAD_FOLDER, image.filename)
            image.save(img_path)
            insert_blob(img_path)
        else:
            app.logger.info("No image, going to error")
            data = read_cosmos()
            return render_template('home.html', messages=data, error="Please upload png/jpg/jpeg/gig/SVG only")

    if new_message and new_username:
        if img_path is not "":
            blob_path = 'https://'+storage_account+'.blob.core.windows.net/'+images_container+'/'+image.filename
        insert_cosmos(blob_path, new_username, new_message)

    return render_template('handle_message.html', username=new_username, message=new_message)



# The Flask route, defining the main behaviour of the webserver:
@app.route("/", methods=['GET'])
def htmlForm():
    app.logger.info("htmlForm main")
    data = read_cosmos()

    # Return a Jinja HTML template, passing the messages as an argument to the template:
    return render_template('home.html', messages=data, error="")

