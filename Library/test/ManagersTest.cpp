#include <NullPointerException.h>
#include <boost/test/unit_test.hpp>
#include <boost/date_time.hpp>
#include "StorageContainer.h"
#include "ClientType.h"
#include "ClientManager.h"
#include "VehicleManager.h"
#include "RentManager.h"
#include "ClientException.h"
#include "VehicleException.h"
#include "RentException.h"

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
    BOOST_CHECK_THROW(clientManager->getClient("123"), ClientNotFoundException);
    ClientPtr client1 = clientManager->registerClient("Tobey", "Maguire", "123", testAddress1, testType1);
    BOOST_TEST(clientManager->getClient("123") == client1);
    BOOST_CHECK_THROW(clientManager->registerClient("Brad", "Pitt", "123", testAddress1, testType1), ClientAlreadyExistsException);
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

    BOOST_CHECK_THROW(vehicleManager->unregisterVehicle("XXXDDD"), VehicleNotFoundException);
}

BOOST_AUTO_TEST_CASE(RentManagerTest) {
    RentManagerPtr rentManager = std::make_shared<RentManager>();
    AddressPtr addr1 = std::make_shared<Address>("Lodz", "Aleja Politechniki", "10");
    ClientTypePtr type1 = std::make_shared<Diamond>();
    ClientPtr client1 = std::make_shared<Client>("Cezary", "Pazura", "123", addr1, type1);
    VehiclePtr car1 = std::make_shared<Car>("EL67FP", 100, 2500, E);
    VehiclePtr bicycle1 = std::make_shared<Bicycle>("B05", 100);
    pt::ptime begin = pt::ptime(gr::date(2015, 10, 1), pt::hours(10));
    RentPtr carRent = rentManager->rentVehicle(1, client1, car1, begin);
    RentPtr bicycleRent = rentManager->rentVehicle(2, client1, bicycle1, begin);
    BOOST_TEST(rentManager->getAllClientRents(client1).size() == 2);
    BOOST_TEST(rentManager->getVehicleRent(car1) == carRent);
    BOOST_TEST(rentManager->findRents([](RentPtr rent) { return rent->getId() == 2;}).size() == 1);
    BOOST_TEST(rentManager->findRents([](RentPtr rent) { return rent->getId() == 2;}).front() == bicycleRent);
    BOOST_TEST(rentManager->findAllRents().size() == 2);
    rentManager->returnVehicle(car1);
    BOOST_TEST(rentManager->getAllClientRents(client1).size() == 1);
    BOOST_TEST(rentManager->getVehicleRent(car1) == nullptr);
    BOOST_TEST(rentManager->findRents([](RentPtr rent) { return rent->getId() == 1;}).size() == 0);
    BOOST_TEST(rentManager->findAllRents().size() == 1);
    BOOST_TEST(rentManager->getArchiveRents()->get(0)->getEndTime() == pt::second_clock::local_time());
    ClientTypePtr type2 = std::make_shared<Default>();
    ClientPtr client2 = std::make_shared<Client>("Margot", "Robbie", "789", addr1, type2);
    BOOST_TEST(client2->getMaxVehicles() == 1);
    VehiclePtr bicycle2 = std::make_shared<Bicycle>("SF9071", 2000);
    RentPtr bicycleRent2 = rentManager->rentVehicle(3, client2, bicycle2, begin);
    rentManager->returnVehicle(bicycle2);
    BOOST_TEST(client2->getMaxVehicles() == 10);
    AddressPtr addr = std::make_shared<Address>("City", "Street", "1");
    ClientTypePtr defaultType = std::make_shared<Default>();
    ClientTypePtr diamondType = std::make_shared<Diamond>();
    pt::ptime begin2 = pt::ptime(gr::date(2024, 1, 1), pt::hours(10));
    VehiclePtr vehicle = std::make_shared<Bicycle>("BIKE123", 100);
    ClientPtr activeClient = std::make_shared<Client>("Anna", "Smith", "123", addr, diamondType);
    ClientPtr archivedClient = std::make_shared<Client>("Tom", "Cruise", "456", addr, diamondType);
    archivedClient->setArchive();
    VehiclePtr archivedVehicle = std::make_shared<Bicycle>("BIKE456", 100);
    archivedVehicle->setArchive();
    BOOST_CHECK_THROW(rentManager->rentVehicle(1, nullptr, vehicle, begin2), NullPointerException);
    BOOST_CHECK_THROW(rentManager->rentVehicle(2, activeClient, nullptr, begin2), NullPointerException);
    BOOST_CHECK_THROW(rentManager->rentVehicle(3, archivedClient, vehicle, begin2), ClientUnavailableException);
    BOOST_CHECK_THROW(rentManager->rentVehicle(4, activeClient, archivedVehicle, begin2), VehicleUnavailableException);
    ClientPtr limitedClient = std::make_shared<Client>("Bruce", "Wayne", "789", addr, defaultType);
    VehiclePtr v1 = std::make_shared<Bicycle>("B1", 100);
    VehiclePtr v2 = std::make_shared<Bicycle>("B2", 100);
    rentManager->rentVehicle(5, limitedClient, v1, begin2);
    BOOST_CHECK_THROW(rentManager->rentVehicle(6, limitedClient, v2, begin2), CannotRentException);
    ClientPtr anotherClient = std::make_shared<Client>("Peter", "Parker", "999", addr, diamondType);
    BOOST_CHECK_THROW(rentManager->rentVehicle(7, anotherClient, v1, begin2), VehicleAlreadyRentedException);
    VehiclePtr nullVehicle;
    BOOST_CHECK_THROW(rentManager->returnVehicle(nullVehicle), NullPointerException);
    VehiclePtr notRentedVehicle = std::make_shared<Car>("UNUSED1", 50, 1400, B);
    BOOST_CHECK_THROW(rentManager->returnVehicle(notRentedVehicle), NullPointerException);
}

BOOST_AUTO_TEST_SUITE_END()