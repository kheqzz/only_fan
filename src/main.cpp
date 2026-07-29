#include <Arduino.h>
#include "./lib/bluetoothBLE/ble.h"
#include "./lib/bluetoothBLE/bleCallbacks.h"
// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  BLEManager bleManager;
  bleManager.init();
  // bleManager.startAdvertising();
  Serial.println("BLE initialized and advertising started.");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Main loop running...");
  delay(1000);

}

