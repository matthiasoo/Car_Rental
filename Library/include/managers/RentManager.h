#ifndef RENTMANAGER_H
#define RENTMANAGER_H
#include "typedefs.h"
#include "RentRepository.h"
#include "ClientType.h"

class RentManager {
private:
    RentRepositoryPtr currentRents;
    RentRepositoryPtr archiveRents;

public:
    RentManager();
    ~RentManager();

    std::vector<RentPtr> getAllClientRents(ClientPtr client);
    std::vector<RentPtr> getClientArchiveRents(ClientPtr client);
    RentPtr getVehicleRent(VehiclePtr vehicle);
    std::vector<RentPtr> findRents(RentPredicate predicate);
    std::vector<RentPtr> findAllRents();
    std::vector<RentPtr> findAllArchiveRents();
    std::string listAllCurrentRents();
    std::string listAllArchiveRents();
    double checkClientRentBalance(ClientPtr client);
    RentPtr rentVehicle(const int &id, ClientPtr client, VehiclePtr vehicle, pt::ptime &beginTime);
    void returnVehicle(ClientPtr client, VehiclePtr vehicle);
    RentRepositoryPtr getArchiveRents(); // only for tests
    void changeClientType(ClientPtr client);
};



#endif //RENTMANAGER_H
