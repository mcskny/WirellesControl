//This is the code of the device connected to the receiver via i2c in the WirellessControl project
//We recommend using Leonardo, Micro or Pro micro for this code

#include <Wire.h>
#include <Mouse.h>

bool isLedOn;
  const int ledPin = 4;

void setup() {
  Serial.begin(9600);
  Wire.begin(9);
  Wire.onReceive(receiveData);
      pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
    Mouse.begin();

}

void loop() {
  //empty
}

void receiveData(int byteCount) {
  while (Wire.available()) {
    isLedOn = !isLedOn;
    char receivedByte = Wire.read();
    Serial.print("Received Data: ");
    Serial.println(receivedByte);
    digitalWrite(ledPin, isLedOn);
    Mouse.click(MOUSE_LEFT);
  }
}
