/**
 * @file beacon.cpp
 * @author Alejandro Linde Cerezo (alindecerezo@uoc.edu)
 * @brief Beacon class implementation for iBeacon protocol.
 * @version 0.1
 */

#include "NimBLEDevice.h"
#include "NimBLEBeacon.h"
#include "esp_bt.h"
#include "beacon.hpp"

#define ADV_MAX_INTERVAL 160U // 100 ms
#define ADV_MIN_INTERVAL 144U //  90 ms

Beacon::Beacon(const char* beaconUUID, const char* beaconName) {
    NimBLEDevice::init("");
    NimBLEDevice::setPower(ESP_PWR_LVL_P9, ESP_BLE_PWR_TYPE_ADV);

    initBeaconData(beaconUUID);
    initAdvertisementData(beaconName);
    initScanResponseData();
}

bool Beacon::start() {
    _ptrAdvertising = NimBLEDevice::getAdvertising();

    if (_ptrAdvertising != nullptr) {
        _ptrAdvertising->setAdvertisementData(advData);
        _ptrAdvertising->setScanResponseData(scanRespData);
        _ptrAdvertising->setAdvertisementType(BLE_GAP_CONN_MODE_NON);
        _ptrAdvertising->setMaxInterval(ADV_MAX_INTERVAL);
        _ptrAdvertising->setMinInterval(ADV_MIN_INTERVAL);
        return _ptrAdvertising->start();
    }

    return false;
}

void Beacon::initBeaconData(const char* beaconUUID) {
    _beacon = NimBLEBeacon();
    _beacon.setManufacturerId(0x4c00);
    _beacon.setProximityUUID(NimBLEUUID(beaconUUID));
    _beacon.setMajor(0);
    _beacon.setMinor(0);
    _beacon.setSignalPower(-50);
}

void Beacon::initAdvertisementData(const char* beaconName) {
    advData = NimBLEAdvertisementData();
    advData.setName(beaconName);
    advData.setShortName(beaconName);
    advData.setFlags(0x04);

    std::string serviceData = "";
    serviceData += (char) 26;   // length
    serviceData += (char) 0xFF; // type
    serviceData += _beacon.getData();
    advData.addData(serviceData);
}

void Beacon::initScanResponseData() {
    scanRespData = NimBLEAdvertisementData();
}
