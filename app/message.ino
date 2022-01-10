#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>
#include <DHT.h>

static DHT dht_in(DHT_IN_PIN, DHT_TYPE);
static DHT dht_out(DHT_OUT_PIN, DHT_TYPE);

void initSensor()
{
    dht_in.begin();
    dht_out.begin();
}

bool readMessage(int messageId, char *payload)
{
    int lum = analogRead(PHOTO_PIN);
    lum = map(lum, 0, 1023, 0, 100);
    float inTemp = dht_in.readTemperature();
    float outTemp = dht_out.readTemperature();
    float inHumi = dht_in.readHumidity();
    //float outHumi = dht_out.readHumidity();


    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    
    root["deviceId"] = DEVICE_ID;
    root["messageCount"] = messageId;

    //JsonObject& location = root.createNestedObject("location");
   // location["latitude"] = 59.24668;
    //location["longitude"] = 18.06538;

    JsonObject& data = root.createNestedObject("data");
    data["lum"] = lum;

    JsonObject& temperature = data.createNestedObject("temperature");
    temperature["inside"] = inTemp;
    temperature["outside"] = outTemp;

    JsonObject& humidity = data.createNestedObject("humidity");
    humidity["inside"] = inHumi;
    //humidity["outside"] = outHumi;

    bool temperatureAlert = false;  
    if (outTemp < tempAlert)
    {
        temperatureAlert = true;
    }

    root.printTo(payload, MESSAGE_MAX_LEN);
    return temperatureAlert;
}













void parseTwinMessage(char *message)
{
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(message);
    if (!root.success())
    {
        Serial.printf("Parse %s failed.\r\n", message);
        return;
    }

    if (root["desired"]["interval"].success())
    {
        interval = root["desired"]["interval"];
    }
    else if (root.containsKey("interval"))
    {
        interval = root["interval"];
    }

    
    if (root["desired"]["tempAlert"].success())
    {
        tempAlert = root["desired"]["tempAlert"];
    }
    else if (root.containsKey("tempAlert"))
    {
        tempAlert = root["tempAlert"];
    }
}
