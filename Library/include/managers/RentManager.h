#ifndef RENTMANAGER_H
#define RENTMANAGER_H
#include "typedefs.h"
#include "RentRepository.h"

class RentManager {
private:
    RentRepositoryPtr currentRents;
    RentRepositoryPtr archiveRents;

public:
    RentManager();
    ~RentManager();

    std::vector<RentPtr> getAllClientRents(ClientPtr client);
    RentPtr getVehicleRent(VehiclePtr vehicle);
    std::vector<RentPtr> findRents(RentPtr predicate);
    std::vector<RentPtr> findAllRents();
    double checkClientRentBalance(ClientPtr client);
};



#endif //RENTMANAGER_H
