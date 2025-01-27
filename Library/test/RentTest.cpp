#include <Rent.h>
#include <boost/test/unit_test.hpp>

#include <Client.h>
#include <Address.h>
#include <Vehicle.h>

struct TestSuiteRentFixture {
    int testId = 1;
    Client *testClient1;
    Address *testAddress1;
    Vehicle *testVehicle1;

    TestSuiteRentFixture() {
        testAddress1 = new Address("NYC", "Wall Street", "10");
        testClient1 = new Client("Brad", "Pitt", "8899", testAddress1);
        testVehicle1 = new Vehicle("US0067", 200);
    }

    ~TestSuiteRentFixture() {
        delete testClient1;
        delete testAddress1;
        delete testVehicle1;
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRent, TestSuiteRentFixture)

BOOST_AUTO_TEST_CASE(RentConstructorTest) {
    Rent *rent = new Rent(testId, testClient1, testVehicle1);
    BOOST_TEST(rent->getId() == testId);
    BOOST_TEST(rent->getClient() == testClient1);
    BOOST_TEST(rent->getVehicle() == testVehicle1);
}

BOOST_AUTO_TEST_CASE(RentSettersTest) {
}

BOOST_AUTO_TEST_SUITE_END()