from base64 import b64encode, b64decode
from hashlib import sha256
from time import time
from urllib import parse
from hmac import HMAC

import uamqp
import uuid
import json
import os
import urllib

import time as t
import pandas as pd

def generate_sas_token(uri, key, policy_name, expiry=3600):
    ttl = time() + expiry
    sign_key = "%s\n%d" % ((parse.quote_plus(uri)), int(ttl))
    print(sign_key)
    signature = b64encode(HMAC(b64decode(key), sign_key.encode('utf-8'), sha256).digest())

    rawtoken = {
        'sr' :  uri,
        'sig': signature,
        'se' : str(int(ttl))
    }

    if policy_name is not None:
        rawtoken['skn'] = policy_name

    return 'SharedAccessSignature ' + parse.urlencode(rawtoken)

#----------------------------------------

iot_hub_name = "lab13couzi"
hostname = "lab13couzi.azure-devices.net"
device_id = "device1couzi"
username = f"{device_id}@sas.{iot_hub_name}"

access_key = os.getenv("ACCESS_KEY")

sas_token = generate_sas_token(f"{hostname}/devices/{device_id}", access_key, None)

operation = f"/devices/{device_id}/messages/events"

uri = f"amqps://{urllib.parse.quote_plus(username)}:{urllib.parse.quote_plus(sas_token)}@{hostname}{operation}"

with uamqp.SendClient(uri, debug=True) as send_client:

    msg_props = uamqp.message.MessageProperties() 
    
    # msg_props.message_id = str(uuid.uuid4()) 
    # message_json = {'temperature': 22 } 
    # msg_data = json.dumps(message_json) 
    # message = uamqp.Message(msg_data, properties=msg_props) 

    df=pd.read_csv('./puhatu.csv')
    messages = json.loads(df.to_json(orient="records"))

    try:
        for message in messages:
            msg_props.message_id = str(uuid.uuid4())
            msg_data = json.dumps(message)
            message = uamqp.Message(msg_data, properties=msg_props)
            send_client.send_message(message)
            print(message)
            t.sleep(10)
    except KeyboardInterrupt:
        pass

