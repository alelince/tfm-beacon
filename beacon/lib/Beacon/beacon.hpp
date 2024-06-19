/**
 * @file beacon.hpp
 * @author Alejandro Linde Cerezo (alindecerezo@uoc.edu)
 * @brief Beacon class implementation.
 * @version 0.1
 */

#include "NimBLEBeacon.h"
#include "NimBLEAdvertising.h"

#ifndef BEACON_H
#define BEACON_H

class Beacon {
    public:
        Beacon(const char* beaconUUID, const char* beaconName);
        bool start();

    protected:
        NimBLEBeacon _beacon;
        NimBLEAdvertising* _ptrAdvertising;
        NimBLEAdvertisementData advData;
        NimBLEAdvertisementData scanRespData;

        void initBeaconData(const char* beaconUUID);
        void initAdvertisementData(const char* beaconName);
        void initScanResponseData();
};

#endif // BEACON_H