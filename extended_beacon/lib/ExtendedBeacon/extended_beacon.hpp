/**
 * @file extended_beacon.hpp
 * @author Alejandro Linde Cerezo (alindecerezo@uoc.edu)
 * @brief Extended beacon class implementation for boards with BLE 5.0
 * @version 0.1
 */

#include "NimBLEDevice.h"
#include "NimBLEExtAdvertising.h"

#ifndef EXTENDED_BEACON_H
#define EXTENDED_BEACON_H

class ExtendedBeacon {
    public:
        ExtendedBeacon(const char* beaconUUID, const char* beaconName);
        bool start();

    protected:
        NimBLEExtAdvertising* _ptrAdvertising;
        NimBLEExtAdvertisement _advertisement;
        NimBLEExtAdvertisement _scanResponse;

        void initAdvertisement(const char* beaconUUID, const char* beaconName);
        bool isAdvertising();
};

#endif // EXTENDED_BEACON_H