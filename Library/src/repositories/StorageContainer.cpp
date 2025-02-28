#include "StorageContainer.h"
#include "Bicycle.h"
#include "Moped.h"
#include "Car.h"
#include "ClientType.h"

StorageContainer::StorageContainer() {
    // INITIALIZING
    this->clientRepo = std::make_shared<ClientRepository>();
    this->vehicleRepo = std::make_shared<VehicleRepository>();
    this->rentRepo = std::make_shared<RentRepository>();

    // CREATING TEST DATA
    AddressPtr address1 = std::make_shared<Address>("LA", "Main Street", "10");
    AddressPtr address2 = std::make_shared<Address>("Las Vegas", "Sunny Avenue", "19");
    ClientTypePtr type1 = std::make_shared<Silver>();
    ClientTypePtr type2 = std::make_shared<Diamond>();
    ClientPtr client1 = std::make_shared<Client>("Brad", "Pitt", "11267", address1, type1);
    ClientPtr client2 = std::make_shared<Client>("Leonardo", "DiCaprio", "81627", address2, type2);
    VehiclePtr vehicle1 = std::make_shared<Bicycle>("LA9988", 200);
    VehiclePtr vehicle2 = std::make_shared<Moped>("LVG0001", 150, 900);
    VehiclePtr vehicle3 = std::make_shared<Car>("DE55798", 250, 1800, C);
    pt::ptime start1 = pt::ptime(gr::date(2020, 10, 1), pt::hours(10) + pt::minutes(30));
    pt::ptime end1 = pt::ptime(gr::date(2020, 11, 2), pt::hours(12) + pt::minutes(30));
    pt::ptime start2 = pt::ptime(gr::date(2021, 5, 1), pt::hours(10) + pt::minutes(30));
    pt::ptime end2 = pt::ptime(gr::date(2021, 5, 25), pt::hours(12) + pt::minutes(30));
    RentPtr rent1 = std::make_shared<Rent>(1, client1, vehicle1, start1);
    RentPtr rent2 = std::make_shared<Rent>(2, client2, vehicle2, start2);

    // ADDING TO REPOSITORIES
    this->clientRepo->add(client1);
    this->clientRepo->add(client2);
    this->vehicleRepo->add(vehicle1);
    this->vehicleRepo->add(vehicle2);
    this->vehicleRepo->add(vehicle3);
    this->rentRepo->add(rent1);
    this->rentRepo->add(rent2);

    // ENDING RENTS
    rent1->endRent();
    rent2->endRent();
}

StorageContainer::~StorageContainer() {}

ClientRepositoryPtr StorageContainer::getClientRepository() {
    return this->clientRepo;
}

VehicleRepositoryPtr StorageContainer::getVehicleRepository() {
    return this->vehicleRepo;
}

RentRepositoryPtr StorageContainer::getRentRepository() {
    return this->rentRepo;
}
