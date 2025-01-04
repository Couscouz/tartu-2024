import pika
import random
import datetime
import json
import time
from twilio.rest import Client
import os

account_sid = os.getenv('TWILIO_ACCOUNT_SID')
auth_token = os.getenv('TWILIO_AUTH_TOKEN')
to_phone = os.getenv('tophone')
from_phone = os.getenv('fromphone')

broker_host = "172.17.66.174"
broker_port = "5672"

username = "admin"
password = "depreter"
credentials = pika.PlainCredentials(username, password)

connection = pika.BlockingConnection(pika.ConnectionParameters(host = broker_host, port = broker_port, credentials = credentials))
channel = connection.channel()

queue_name = "urgent_messages_queue"
channel.queue_declare(queue=queue_name, durable=True)
routing_key = "messageboard.messages.urgent"
exchange = "couzi"

channel.queue_bind(exchange=exchange, queue=queue_name, routing_key=routing_key)

client = Client(account_sid, auth_token)

def lab_callback (ch, method, properties, body):
	message = json.loads(body.decode())
	message = client.messages.create(
				body="High priority message for you:"+message['content'],
            			from_=from_phone,
            			to=to_phone
		)
	print(message)
	ch.basic_ack (delivery_tag = method.delivery_tag)

channel.basic_consume(queue = queue_name, on_message_callback = lab_callback)
channel.start_consuming()

channel.close()
connection.close()
