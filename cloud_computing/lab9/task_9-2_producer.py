import pika
import random
import datetime
import json
import time
import os

broker_host = "172.17.66.174"
broker_port = "5672"

username = os.getenv('USERNAME')
password = os.getenv('PASSWORD')

credentials = pika.PlainCredentials(username, password)

connection = pika.BlockingConnection(pika.ConnectionParameters(host = broker_host, port = broker_port, credentials = credentials))
channel = connection.channel()

message = {
    "id": "f634f37d-218d-4f04-a5ab-8e61b14ceedd", 
    "content": "Parcel is arriving in 10min", 
    "img_path": "https://mywebsite.blob.core.windows.net/lab9/fognode.png",  
    "timestamp": "2024-04-08 09:20:57"
}

message_str = json.dumps(message)

routing_key = "messageboard.messages.urgent"
exchange = "couzi"

while True:
	channel.basic_publish(exchange = exchange, routing_key = routing_key, body = message_str)
	print("Message sent:")
	print(message_str)
	time.sleep(5)

channel.close()
connection.close()
