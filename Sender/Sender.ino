//This is the code of the sending device in the WirellesControll project
//We recommend using the Nodemcu device for this code

#include <ESP8266WiFi.h>
#include <espnow.h>

const int button_pin = D6;

// You must specify the mac address of your Nodemcu device here: E8:DB:84:E2:38:58
uint8_t reciever[] = {0xE8, 0xDB, 0x84, 0xE2, 0x38, 0x58};

typedef struct Message
{
    String text = "click";
};

Message msg;

bool buttonState = false;
bool lastButtonState = false;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void handleButtonPress()
{ 
    esp_now_send(reciever, (uint8_t *)&msg, sizeof(msg));

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus)
{
    if (sendStatus == 0)
    {
        Serial.println("Delivery success");
    }
    else
    {
        Serial.println("Delivery fail");
    }
}

void setup()
{
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);

    pinMode(button_pin, INPUT);

    if (esp_now_init() != 0)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
    esp_now_register_send_cb(OnDataSent);

    esp_now_add_peer(reciever, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop()
{
    int reading = digitalRead(button_pin);

    if (reading != lastButtonState)
    {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        if (reading != buttonState)
        {
            buttonState = reading;

            if (buttonState == HIGH)
            {
                handleButtonPress();
            }
        }
    }

    lastButtonState = reading;
}
