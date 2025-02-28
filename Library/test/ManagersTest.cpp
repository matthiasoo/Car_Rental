#include <boost/test/unit_test.hpp>
#include <boost/date_time.hpp>
#include "StorageContainer.h"
#include "ClientType.h"
#include "ClientManager.h"
#include "VehicleManager.h"
#include "RentManager.h"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

struct TestSuiteManagersFixture {
    AddressPtr testAddress1;
    AddressPtr testAddress2;
    ClientTypePtr testType1;

    TestSuiteManagersFixture() {
        testAddress1 = std::make_shared<Address>("NYC", "Wall Street", "10");
        testAddress2 = std::make_shared<Address>("LA", "Golden", "2");
        testType1 = std::make_shared<Gold>();
    }

    ~TestSuiteManagersFixture() {}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteManagers, TestSuiteManagersFixture)

BOOST_AUTO_TEST_CASE(ClientManagerTest) {
    ClientManagerPtr clientManager = std::make_shared<ClientManager>();
    BOOST_TEST(clientManager->getClient("123") == nullptr);
    ClientPtr client1 = clientManager->registerClient("Tobey", "Maguire", "123", testAddress1, testType1);
    BOOST_TEST(clientManager->getClient("123") == client1);
    BOOST_TEST(clientManager->registerClient("Brad", "Pitt", "123", testAddress1, testType1) == client1);
    ClientPtr client2 = clientManager->registerClient("Tom", "Hanks", "555", testAddress1, testType1);
    ClientPtr client3 = clientManager->registerClient("Margot", "Robbie", "789", testAddress2, testType1);
    BOOST_TEST(clientManager->getClient("555") == client2);
    AddressPtr address1 = testAddress1;
    ClientPredicate pred1 = [&address1](const ClientPtr &client) {
        return client->getAddress() == address1;
    };
    BOOST_TEST(clientManager->findClients(pred1).size() == 2);
    BOOST_TEST(clientManager->findAllClients().size() == 3);
    clientManager->getClient("555")->setArchive();
    BOOST_TEST(clientManager->findClients(pred1).size() == 1);
    BOOST_TEST(clientManager->findAllClients().size() == 2);
}

BOOST_AUTO_TEST_CASE(VehicleManagerTest) {
    VehicleManagerPtr vehicleManager = std::make_shared<VehicleManager>();
    BOOST_TEST(vehicleManager->getVehicle("LA789") == nullptr);
    VehiclePtr bicycle1 = vehicleManager->registerBicycle("LA798", 25);
    BOOST_TEST(vehicleManager->getVehicle("LA798") == bicycle1);
    BOOST_TEST(vehicleManager->registerMoped("LA798", 50, 150) == bicycle1);
    VehiclePtr moped1 = vehicleManager->registerMoped("LV001", 65, 250);
    VehiclePtr car1 = vehicleManager->registerCar("CA904", 150, 1600, C);
    BOOST_TEST(vehicleManager->getVehicle("LV001") == moped1);
    BOOST_TEST(vehicleManager->getVehicle("CA904") == car1);
    VehiclePredicate predPrice = [](const VehiclePtr &vehicle) {
        return vehicle->getBasePrice() == 65;
    };
    BOOST_TEST(vehicleManager->findVehicles(predPrice).size() == 1);
    vehicleManager->registerMoped("LA117", 65, 200);
    BOOST_TEST(vehicleManager->findVehicles(predPrice).size() == 2);
    BOOST_TEST(vehicleManager->findAllVehicles().size() == 4);
    vehicleManager->getVehicle("LV001")->setArchive();
    BOOST_TEST(vehicleManager->findAllVehicles().size() == 3);
}

BOOST_AUTO_TEST_CASE(RentManagerTest) {
    RentManagerPtr rentManager = std::make_shared<RentManager>();
    AddressPtr addr1 = std::make_shared<Address>("Lodz", "Aleja Politechniki", "10");
    ClientTypePtr type1 = std::make_shared<Diamond>();
    ClientPtr client1 = std::make_shared<Client>("Cezary", "Pazura", "123", addr1, type1);
    VehiclePtr car1 = std::make_shared<Car>("EL67FP", 100, 2500, E);
    VehiclePtr bicycle1 = std::make_shared<Bicycle>("B05", 100);
    pt::ptime begin = pt::ptime(gr::date(2015, 10, 1), pt::hours(10));
    pt::ptime end = pt::ptime(gr::date(2015, 10, 2), pt::hours(9));
    RentPtr carRent = std::make_shared<Rent>(1, client1, car1, begin);
    RentPtr bicycleRent = std::make_shared<Rent>(2, client1, bicycle1, begin);
    carRent->endRent(end);
    bicycleRent->endRent(end);
}

BOOST_AUTO_TEST_SUITE_END()