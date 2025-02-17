#include <boost/test/unit_test.hpp>
#include "Vehicle.h"

using namespace std;

struct TestSuiteVehicleFixture {
    std::string testPlate1 = "XYZ1980";
    std::string testPlate2 = "DE55345";
    int testPrice1 = 20;
    int testPrice2 = 50;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteVehicle, TestSuiteVehicleFixture)

BOOST_AUTO_TEST_CASE(VehicleConstructorTest) {
    VehiclePtr vehicle = new Vehicle(testPlate1, testPrice1);
    BOOST_TEST(vehicle->getPlateNumber() == testPlate1);
    BOOST_TEST(vehicle->getBasePrice() == testPrice1);
    delete vehicle;
}

BOOST_AUTO_TEST_CASE(VehicleSettersTest) {
    Vehicle *vehicle = new Vehicle(testPlate1, testPrice1);
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

BOOST_AUTO_TEST_SUITE_END()