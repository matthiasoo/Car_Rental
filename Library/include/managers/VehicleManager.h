#ifndef VEHICLEMANAGER_H
#define VEHICLEMANAGER_H
#include "typedefs.h"
#include "VehicleRepository.h"
#include "Bicycle.h"
#include "Moped.h"
#include "Car.h"


class VehicleManager {
private:
    VehicleRepositoryPtr activeVehicles;
    VehicleRepositoryPtr archiveVehicles;

public:
    VehicleManager();
    ~VehicleManager();

    VehiclePtr getVehicle(const std::string &plateNumber);
    VehiclePtr registerBicycle(const std::string &plateNumber, const int &basePrice);
    VehiclePtr registerMoped(const std::string &plateNumber, const int &basePrice, const int &engineDisplacement);
    VehiclePtr registerCar(const std::string &plateNumber, const int &basePrice, const int &engineDisplacement, const SegmentType &segment);
    void unregisterVehicle(const std::string &plateNumber);
    std::vector<VehiclePtr> findVehicles(VehiclePredicate predicate);
    std::vector<VehiclePtr> findArchiveVehicles();
    std::vector<VehiclePtr> findActiveVehicles();
    std::string listVehicles(bool archive);
};



#endif //VEHICLEMANAGER_H
