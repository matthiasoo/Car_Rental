#include "Client.h"
#include "Address.h"
#include "Vehicle.h"
#include "Rent.h"
#include "StorageContainer.h"
#include <iostream>
#include <boost/date_time.hpp>

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

int main() {

    AddressPtr address = new Address("LA", "Golden", "10");
    ClientPtr client = new Client("Brad", "Pitt", "1234", address);
    VehiclePtr vehicle = new Vehicle("LA5566", 200);
    pt::ptime start = pt::ptime(gr::date(2024, 1, 1), pt::hours(10));
    pt::ptime end = pt::ptime(gr::date(2024, 1, 2), pt::hours(10));
    RentPtr rent = new Rent(1, client, vehicle, start);
    rent->endRent(end);
    std::cout << rent->getRentCost() << std::endl;
    vehicle->setBasePrice(100);
    std::cout << rent->getRentCost() << std::endl;

    StorageContainerPtr data = new StorageContainer();
    std::cout << data->getClientRepository()->report();

    return 0;
}
