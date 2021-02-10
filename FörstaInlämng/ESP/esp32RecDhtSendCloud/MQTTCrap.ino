
#include <AzureIoTHub.h>
#include <AzureIoTProtocol_MQTT.h>
#include <AzureIoTUtility.h>


void initIotDevice() {
  deviceClient = IoTHubClient_LL_CreateFromConnectionString(conn, MQTT_Protocol);

  if(deviceClient == NULL) {
    Serial.println("Failed to initialize IotDevice");
    while(true);
  }

  IoTHubClient_LL_SetMessageCallback(deviceClient, receviceMessageCallback, NULL); // C2D
  //IoTHubClient_LL_SetDeviceMethodCallback(deviceClient, deviceMethodCallback, NULL); // Direct Method
  //IoTHubClient_LL_SetDeviceTwinCallback(deviceClient, deviceTwinCallback, NULL); // Device Twin
}


void sendCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void *userContextCallback) {
  if(IOTHUB_CLIENT_CONFIRMATION_OK == result) {
    Serial.println("Message sent to IotHub");
  }
  else {
    Serial.println("Failed to send message to IotHub");
  }

  messagePending = false;
}


void sendIotMessage(char* message) {

  IOTHUB_MESSAGE_HANDLE payload = IoTHubMessage_CreateFromByteArray((const unsigned char *) message, strlen(message));

  if(payload == NULL) {
    Serial.println("Unable to create Message");
  }
  else {

    if(IoTHubClient_LL_SendEventAsync(deviceClient, payload, sendCallback, NULL) != IOTHUB_CLIENT_OK) {
      Serial.println("Failed to insert message to deviceClient");
    }
    else {
      messagePending = true;
      Serial.println("deviceClient accepted the message");
    }

    IoTHubMessage_Destroy(payload);
  }
}


IOTHUBMESSAGE_DISPOSITION_RESULT receviceMessageCallback(IOTHUB_MESSAGE_HANDLE message, void *userContextCallback) {

  IOTHUBMESSAGE_DISPOSITION_RESULT result;
  const unsigned char *buf;
  size_t size;

  if(IoTHubMessage_GetByteArray(message, &buf, &size) != IOTHUB_MESSAGE_OK) {
    result = IOTHUBMESSAGE_REJECTED;
  } else {
    char *temp = (char *)malloc(size + 1);

    if(temp == NULL) {
      return IOTHUBMESSAGE_ABANDONED;
    }

    strncpy(temp, (const char *)buf, size);
    temp[size] = '\0';
  
    Serial.printf("C2D: %s \r\n", temp);
    free(temp);
  }

  return IOTHUBMESSAGE_ACCEPTED;
}
