#include <boost/test/unit_test.hpp>
#include "Vehicle.h"
#include "Bicycle.h"
#include "Moped.h"
#include "Car.h"

using namespace std;

struct TestSuiteVehicleFixture {
    std::string testPlate1 = "XYZ1980";
    std::string testPlate2 = "DE55345";
    int testPrice1 = 20;
    int testPrice2 = 50;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteVehicle, TestSuiteVehicleFixture)

BOOST_AUTO_TEST_CASE(VehicleConstructorTest) {
    VehiclePtr vehicle = new Bicycle(testPlate1, testPrice1);
    BOOST_TEST(vehicle->getPlateNumber() == testPlate1);
    BOOST_TEST(vehicle->getBasePrice() == testPrice1);
    delete vehicle;
}

BOOST_AUTO_TEST_CASE(VehicleSettersTest) {
    Vehicle *vehicle = new Bicycle(testPlate1, testPrice1);
    vehicle->setPlateNumber("");
    vehicle->setBasePrice(-100);
    BOOST_TEST(vehicle->getPlateNumber() == testPlate1);
    BOOST_TEST(vehicle->getBasePrice() == testPrice1);
    vehicle->setPlateNumber(testPlate2);
    vehicle->setBasePrice(testPrice2);
    BOOST_TEST(vehicle->getPlateNumber() == testPlate2);
    BOOST_TEST(vehicle->getBasePrice() == testPrice2);

    delete vehicle;
}

BOOST_AUTO_TEST_CASE(SpecificVehiclesTest) {
    VehiclePtr bicycle = new Bicycle("B590", 100);
    VehiclePtr moped = new Moped("M700", 100, 1250);
    VehiclePtr car = new Car("C987", 100, 1500, C);

    BOOST_TEST(bicycle->getPlateNumber() == "B590");
    BOOST_TEST(bicycle->getBasePrice() == 100);
    BOOST_TEST(bicycle->getActualRentalPrice() == 100);

    BOOST_TEST(moped->getPlateNumber() == "M700");
    BOOST_TEST(moped->getBasePrice() == 100);
    BOOST_TEST(moped->getActualRentalPrice() == 112.5);

    BOOST_TEST(car->getPlateNumber() == "C987");
    BOOST_TEST(car->getBasePrice() == 100);
    BOOST_TEST(car->getActualRentalPrice() == 150);

    delete bicycle;
    delete moped;
    delete car;
}

BOOST_AUTO_TEST_SUITE_END()