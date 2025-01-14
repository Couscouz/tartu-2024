import os
import logging
import asyncio
from azure.eventhub.aio import EventHubConsumerClient

connection_str = os.getenv('CONNECTION_STR')
consumer_group = "$Default"
eventhub_name = "iothub-ehub-lab13couzi-58332565-7b18189bb6"

logger = logging.getLogger("azure.eventhub")
logging.basicConfig(level=logging.INFO)

async def on_event(partition_context, event):
    logger.info("Received event from partition {}".format(partition_context.partition_id))
    await partition_context.update_checkpoint(event)
    print("Telemetry received: ", event.body_as_str())
    print("Properties (set by device): ", event.properties)
    print("System properties (set by IoT Hub): ", event.system_properties)

async def receive():
    client = EventHubConsumerClient.from_connection_string(connection_str, consumer_group, eventhub_name=eventhub_name)
    async with client:
        await client.receive(on_event=on_event)
        # receive events from specified partition:
        # await client.receive(on_event=on_event, partition_id='0')

if __name__ == '__main__':
    loop = asyncio.get_event_loop()
    loop.run_until_complete(receive())