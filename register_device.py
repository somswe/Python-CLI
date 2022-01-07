import os
from azure.iot.hub import IoTHubRegistryManager

# Get system variables. Use Azure CLI automation script to get these automatically
# (Azure CLI automation in development - An easy way to store keys into system variables)
sas_token = os.getenv('SAS_TOKEN')
iothub_string = os.getenv('IOTHUB_CONNECTION_STRING')
primary_key = os.getenv('IOTHUB_PRIMARY_KEY')
secondary_key = os.getenv('IOTHUB_SECONDARY_KEY')
# Here Hostname is based on the IoT Hub name. Maybe we should grab this from the 
# Azure CLI script and store in sys. variables? Saves setup time.
hub_name = "devhub-iot" # write the IoT Hub name manually for now
host = "{0}.azure-devices.net".format(hub_name)
device_id = "103" # <- this should be programmatically iteraded for every new device. Database?
status = "enabled" # <- Initial activation/de-activation of device.

# Create IoT Hub manager object, hubmgr
hubmgr = IoTHubRegistryManager(iothub_string, host, sas_token)
# Create new device
new_device = hubmgr.create_device_with_sas(device_id, primary_key, secondary_key, status)

# Get information from the device in IoT Hub
device = hubmgr.get_device(device_id)

print("Connected: {0}".format(device.device_id))
print("Connection state: {0}".format(device.connection_state))
