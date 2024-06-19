/**
 * @file extended_beacon.cpp
 * @author Alejandro Linde Cerezo (alindecerezo@uoc.edu)
 * @brief Extended beacon class implementation for boards with BLE 5.0
 * @version 0.1
 */

#include "NimBLEDevice.h"
#include "extended_beacon.hpp"

#define ADV_MAX_INTERVAL 160U // 100 ms
#define ADV_MIN_INTERVAL 144U //  90 ms

#define TX_POWER 18

#define CHANNEL_37 true
#define CHANNEL_38 true
#define CHANNEL_39 true

#define INSTANCE_ID 0U

ExtendedBeacon::ExtendedBeacon(const char* beaconUUID, const char* beaconName) {
    NimBLEDevice::init("");
    NimBLEDevice::setPower(ESP_PWR_LVL_P9, ESP_BLE_PWR_TYPE_ADV);

    initAdvertisement(beaconUUID, beaconName);
}

bool ExtendedBeacon::start() {
    _ptrAdvertising = NimBLEDevice::getAdvertising();

    if (_ptrAdvertising != nullptr) {
        _ptrAdvertising->setInstanceData(INSTANCE_ID, _advertisement);

        return _ptrAdvertising->start(INSTANCE_ID);
    }

    return false;
}

void ExtendedBeacon::initAdvertisement(const char* beaconUUID, const char* beaconName) {
    _advertisement = NimBLEExtAdvertisement(BLE_HCI_LE_PHY_CODED, BLE_HCI_LE_PHY_1M);
    _advertisement.setFlags(0x04);
    _advertisement.setLegacyAdvertising(true);
    _advertisement.setScannable(false);
    _advertisement.setConnectable(false);
    _advertisement.setAddress(NimBLEAddress("BE:BE:CA:FE:00:02"));
    _advertisement.setTxPower(TX_POWER);
    _advertisement.setMaxInterval(ADV_MAX_INTERVAL);
    _advertisement.setMinInterval(ADV_MIN_INTERVAL);
    _advertisement.setPrimaryChannels(CHANNEL_37, CHANNEL_38, CHANNEL_39);
    _advertisement.setCompleteServices16({NimBLEUUID(beaconUUID)});
    _advertisement.setName(beaconName);
    _advertisement.setShortName(beaconName);
    _advertisement.enableScanRequestCallback(false);
}

bool ExtendedBeacon::isAdvertising() {
    return _ptrAdvertising->isAdvertising();
}
