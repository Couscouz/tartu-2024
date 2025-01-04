import asyncio
import uuid
from azure.iot.device.aio import ProvisioningDeviceClient
from azure.iot.device.aio import IoTHubDeviceClient
from azure.iot.device import Message
import json
import os

import time as t
import pandas as pd

provisioning_host = "global.azure-devices-provisioning.net"

id_scope = "0ne00CB12E8"

request_key = os.getenv("REQUEST_KEY")
device_id = os.getenv("REG_ID")

async def main():
    provisioning_device_client = ProvisioningDeviceClient.create_from_symmetric_key(
        provisioning_host=provisioning_host,
        registration_id=device_id,
        id_scope=id_scope,
        symmetric_key=request_key,
    )

    registration_result = await provisioning_device_client.register()

    if registration_result.status == "assigned":
        print(f"Registration succeeded, REG_ID={device_id}")
        device_client = IoTHubDeviceClient.create_from_symmetric_key(
            symmetric_key=request_key,
            hostname=registration_result.registration_state.assigned_hub,
            device_id=registration_result.registration_state.device_id,
        )
        # Connect the client.
        await device_client.connect()
        print("Device connected successfully")

        df=pd.read_csv('./puhatu.csv')
        messages = json.loads(df.to_json(orient="records"))

        try:
            for message in messages:
                msg_data = json.dumps(message)
                message = Message(msg_data)
                message.message_id = uuid.uuid4()
                await device_client.send_message(message)
                print(message)
                t.sleep(10)
        except KeyboardInterrupt:
            pass

    else:
        print("Registration failed")


if __name__ == "__main__":
    asyncio.run(main())