#ifndef STORAGECONTAINER_H
#define STORAGECONTAINER_H

#include "ClientRepository.h"
#include "VehicleRepository.h"
#include "RentRepository.h"

class StorageContainer {
private:
    ClientRepositoryPtr clientRepo;
    VehicleRepositoryPtr vehicleRepo;
    RentRepositoryPtr rentRepo;

public:
    StorageContainer();
    ~StorageContainer();

    ClientRepositoryPtr getClientRepository();
    VehicleRepositoryPtr getVehicleRepository();
    RentRepositoryPtr getRentRepository();
};



#endif //STORAGECONTAINER_H
