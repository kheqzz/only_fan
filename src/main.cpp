#include <Arduino.h>
#include <ble.h>
#include <bleCallbacks.h>


BLEManager bleManager;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting BLE initialization...");
  
  bleManager.init();
  bleManager.startAdvertising();
  Serial.println("BLE initialized and advertising started.");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Main loop running...");
  delay(1000);
  bleManager.checkConnection(); // Check BLE connection status

}

