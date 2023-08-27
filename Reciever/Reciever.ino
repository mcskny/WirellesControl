//This is the code of the receiving device in the WirellesControl project
//We recommend using a Nodemcu device for this code

#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Wire.h>

#define SLAVE_ADDR 9
#define ANSWERSIZE 5

void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len)
{
    if (len > 0)
    {
        Wire.beginTransmission(SLAVE_ADDR);
        Wire.write("click");
        Wire.endTransmission();
    }
}

void setup()
{
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);

    if (esp_now_init() != 0)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
    esp_now_register_recv_cb(OnDataRecv);

    Wire.begin();

    Serial.println("I2C Master Demonstration");
}

void loop()
{
}
