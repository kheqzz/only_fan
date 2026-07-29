#include "ble.h"
#include "bleCallbacks.h"
#include "config.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <Arduino.h>
#include <BLE2902.h>

BLEManager::BLEManager()
{
    // Constructor implementation
    bleData.pServer = nullptr;
    bleData.pMonitoringChar = nullptr;
    bleData.pConfigChar = nullptr;
    bleData.deviceConnected = false;
    bleData.pServerCallbacks = nullptr;

}

BLEManager::~BLEManager()
{
    // Destructor implementation
    stopAdvertising();
}

void BLEManager::init()
{
    // Initialize BLE
    Serial.println("Initializing BLE...");
    BLEDevice::init("FanController");
    Serial.println("BLE initialized. /n Creating BLE server...");
    bleData.pServer = BLEDevice::createServer();
    Serial.println("BLE server created. /n Setting up callbacks...");
    bleData.pServerCallbacks = new BLECallbacks(&bleData);
    Serial.println("Callbacks set. /n Setting server callbacks...");
    bleData.pServer->setCallbacks(bleData.pServerCallbacks);

}

void BLEManager::startAdvertising()
{
    // Start BLE advertising
    BLEService* pService = bleData.pServer->createService(UUID_SERVICE);
    bleData.pMonitoringChar = pService-> createCharacteristic(UUID_MONITORING, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    bleData.pMonitoringChar->addDescriptor(new BLE2902());
    bleData.pConfigChar = pService-> createCharacteristic(UUID_FAN_CONFIG, BLECharacteristic::PROPERTY_WRITE);
    bleData.pConfigChar->setCallbacks(new BLEConfigCallbacks(&bleData));
    pService->start();
    BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(UUID_SERVICE);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
   
    Serial.println("Waiting for a client connection to notify...");
    pAdvertising->start();

}

void BLEManager::stopAdvertising()
{
    // Stop BLE advertising
    BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
    if (pAdvertising) {
        pAdvertising->stop();
    }

}



void BLECallbacks::onConnect(BLEServer* pServer) {
    bleData->deviceConnected = true;
}

void BLECallbacks::onDisconnect(BLEServer* pServer){
    bleData ->deviceConnected = false;
    // Restart advertising when a client disconnects
    BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
    if (pAdvertising) {
        pAdvertising->start();
    }
}

void BLEConfigCallbacks::onWrite(BLECharacteristic* pCharacteristic, esp_ble_gatts_cb_param_t* param) {
    String receivedValue = pCharacteristic->getValue();
    if(receivedValue.length() > 0) {
        Serial.print("Received value for configuration characteristic: ");
        Serial.println(receivedValue);
        // Process the received value as needed
    }


}




