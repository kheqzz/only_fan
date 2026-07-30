#ifndef BLE_H
#define BLE_H

// this file is for BLE related functions and definitions

class BLEServer;
class BLECharacteristic;
class BLEServerCallbacks;
struct ble
{
    BLEServer* pServer;
    BLECharacteristic* pMonitoringChar;
    BLECharacteristic* pConfigChar;
    BLEServerCallbacks* pServerCallbacks;
    bool deviceConnected;
};

class BLEManager
{
private:
    ble bleData;
public:
    BLEManager();
    ~BLEManager();

    void init();
    void startAdvertising();
    void stopAdvertising();
    void checkConnection();
   
};



#endif // BLE_H