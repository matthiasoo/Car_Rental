#include <iostream>
#include <boost/date_time.hpp>
#include "Client.h"
#include "Address.h"
#include "Vehicle.h"
#include "Rent.h"
#include "StorageContainer.h"
#include "Bicycle.h"
#include "Moped.h"
#include "Car.h"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

int main() {

    StorageContainerPtr container = new StorageContainer();

    std::cout << "CLIENTS:\n" << container->getClientRepository()->report() << std::endl;
    std::cout << "VEHICLES:\n" << container->getVehicleRepository()->report() << std::endl;
    std::cout << "RENTS:\n" << container->getRentRepository()->report() << std::endl;


    AddressPtr address = new Address("LA", "Golden", "10");
    ClientPtr client = new Client("Tobey", "Maguire", "1234", address);
    VehiclePtr vehicle = new Car("LA5566", 100, 1500, C);
    pt::ptime start = pt::ptime(gr::date(2024, 1, 1), pt::hours(10));
    pt::ptime end = pt::ptime(gr::date(2024, 1, 2), pt::hours(9));
    RentPtr rent = new Rent(3, client, vehicle, start);
    rent->endRent(end);

    container->getRentRepository()->add(rent);
    container->getClientRepository()->add(client);
    container->getVehicleRepository()->add(vehicle);

    std::cout << "CLIENTS:\n" << container->getClientRepository()->report() << std::endl;
    std::cout << "VEHICLES:\n" << container->getVehicleRepository()->report() << std::endl;
    std::cout << "RENTS:\n" << container->getRentRepository()->report() << std::endl;

    return 0;
}
