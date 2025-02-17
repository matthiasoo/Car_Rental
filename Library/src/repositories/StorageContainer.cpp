#include "StorageContainer.h"
#include "Address.h" // why?

StorageContainer::StorageContainer() {
    // INITIALIZING
    this->clientRepo = new ClientRepository();
    this->vehicleRepo = new VehicleRepository();
    this->rentRepo = new RentRepository();

    // CREATING TEST DATA
    AddressPtr address1 = new Address("LA", "Main Street", "10");
    AddressPtr address2 = new Address("Las Vegas", "Sunny Avenue", "19");
    ClientPtr client1 = new Client("Brad", "Pitt", "11267", address1);
    ClientPtr client2 = new Client("Leonardo", "DiCaprio", "81627", address2);
    VehiclePtr vehicle1 = new Vehicle("LA9988", 200);
    VehiclePtr vehicle2 = new Vehicle("LVG0001", 150);
    pt::ptime start1 = pt::ptime(gr::date(2020, 10, 1), pt::hours(10) + pt::minutes(30));
    pt::ptime end1 = pt::ptime(gr::date(2020, 11, 2), pt::hours(12) + pt::minutes(30));
    pt::ptime start2 = pt::ptime(gr::date(2021, 5, 1), pt::hours(10) + pt::minutes(30));
    pt::ptime end2 = pt::ptime(gr::date(2021, 5, 25), pt::hours(12) + pt::minutes(30));
    RentPtr rent1 = new Rent(1, client1, vehicle1, start1);
    RentPtr rent2 = new Rent(2, client2, vehicle2, start2);

    // ADDING TO REPOSITORIES
    this->clientRepo->add(client1);
    this->clientRepo->add(client2);
    this->vehicleRepo->add(vehicle1);
    this->vehicleRepo->add(vehicle2);
    this->rentRepo->add(rent1);
    this->rentRepo->add(rent2);

    // ENDING RENTS
    rent1->endRent(end1);
    rent2->endRent(end2);
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
