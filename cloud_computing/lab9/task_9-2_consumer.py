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

queue_name = "all_messages_queue"
channel.queue_declare(queue=queue_name, durable=True)

routing_key = "messageboard.messages.*"
exchange = "couzi"

channel.queue_bind(exchange=exchange, queue=queue_name, routing_key=routing_key)


def lab_callback (ch, method, properties, body):
	message = json.loads(body.decode())
	print(message)
	ch.basic_ack (delivery_tag = method.delivery_tag)

channel.basic_consume(queue = queue_name, on_message_callback = lab_callback)
channel.start_consuming()

channel.close()
connection.close()
