#include <Client.h>
#include <Address.h>
#include <Vehicle.h>
#include <Rent.h>
#include <iostream>
#include <boost/date_time.hpp>

using namespace std;
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

int main() {

    Address *address = new Address("LA", "Golden", "10");
    Client *client = new Client("Brad", "Pitt", "1234", address);
    Vehicle *vehicle = new Vehicle("LA5566", 200);
    pt::ptime start = pt::ptime(gr::date(2024, 1, 1), pt::hours(10));
    pt::ptime end = pt::ptime(gr::date(2024, 1, 2), pt::hours(10));
    Rent *rent = new Rent(1, client, vehicle, start);
    rent->endRent(end);
    std::cout << rent->getRentCost() << std::endl;
    vehicle->setBasePrice(100);
    std::cout << rent->getRentCost() << std::endl;

    return 0;
}
