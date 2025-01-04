import azure.functions as func
import logging
import uuid
import json
from datetime import datetime

app = func.FunctionApp(http_auth_level=func.AuthLevel.ANONYMOUS)

@app.cosmos_db_input(arg_name="inputDocument", database_name="messagesdb", container_name = "messages", connection="CosmosDB")
@app.route(route="htmlForm")
def htmlForm(req: func.HttpRequest, inputDocument: func.DocumentList) -> func.HttpResponse:
    html_data = """
        <html>
        <title>Message board</title>
        <body>
            <h2>Lab 4 | COUZI Remi</h4>
            <h4>Messages so far:</h4>
            <ul>
    """

    for doc in inputDocument:
        html_data += f"""<li> "{doc['content']}" <small>{doc['message_time']}</small></li>"""

    html_data += """
            </ul>
        <h4> Enter a new message</h4>
        <form action="/api/handleMessage">
            <label> Your message: </label><br>
            <input type="text" name="msg"><br>
            <input type="submit" value="Submit">
        </form>
        </body>
        </html>
    """

    logging.info('Python HTTP trigger function processed a request.')

    return func.HttpResponse(
        html_data,
        status_code=200,
        mimetype="text/html"
    )

@app.cosmos_db_output(arg_name="outputDocument", database_name="messagesdb", container_name = "messages", create_if_not_exists=True, connection="CosmosDB")
@app.route(route="handleMessage", auth_level=func.AuthLevel.ANONYMOUS)
def handleMessage(req: func.HttpRequest, outputDocument: func.Out[func.Document]) -> func.HttpResponse:
    logging.info('Python HTTP trigger function processed a request.')

    msg = req.params.get('msg')
    rowKey = str(uuid.uuid4())

    json_message = {
        'content': msg,
        'id':  rowKey,
        'message_time': datetime.now().isoformat(" ", "seconds")
    }

    outputDocument.set(func.Document.from_dict(json_message))

    return func.HttpResponse(
            f"Entered message was: {msg}, <a href=\"/api/htmlForm\">Go back to main page</a>",
            status_code=200,
            mimetype="text/html"
    )










    