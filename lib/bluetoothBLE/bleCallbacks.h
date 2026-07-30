#ifndef BLECALLBACKS_H
#define BLECALLBACKS_H

#include <BLEServer.h>

class BLECallbacks : public BLEServerCallbacks {
    private:
        ble* bleData;
    public:
        BLECallbacks(ble* data) : bleData(data) {}
    
        void onConnect(BLEServer* pServer) override;
        void onDisconnect(BLEServer* pServer) override;        
};

class BLEConfigCallbacks : public BLECharacteristicCallbacks {
    private:
        ble* bleData;
    public:
        BLEConfigCallbacks(ble* data) : bleData(data) {}
        void onWrite(BLECharacteristic* pCharacteristic, esp_ble_gatts_cb_param_t* param) override;
       
};
#endif // BLECALLBACKS_H