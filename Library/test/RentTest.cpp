#include <boost/test/unit_test.hpp>
#include <boost/date_time.hpp>
#include "Rent.h"
#include "Client.h"
#include "Address.h"
#include "Vehicle.h"
#include "Bicycle.h"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

struct TestSuiteRentFixture {
    int testId = 1;
    ClientPtr testClient1;
    AddressPtr testAddress1;
    VehiclePtr testVehicle1;
    pt::ptime testBeginTime = pt::ptime(gr::date(2010, 1, 1), pt::hours(10));
    pt::ptime testEndTime1 = pt::ptime(gr::date(2020, 1, 1), pt::hours(10));
    pt::ptime testEndTime2 = pt::ptime(gr::date(2023, 1, 1), pt::hours(10));

    TestSuiteRentFixture() {
        testAddress1 = new Address("NYC", "Wall Street", "10");
        testClient1 = new Client("Brad", "Pitt", "8899", testAddress1);
        testVehicle1 = new Bicycle("US0067", 200);
    }

    ~TestSuiteRentFixture() {
        delete testClient1;
        delete testAddress1;
        delete testVehicle1;
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRent, TestSuiteRentFixture)

BOOST_AUTO_TEST_CASE(RentConstructorTest) {
    RentPtr rent = new Rent(testId, testClient1, testVehicle1, testBeginTime);
    BOOST_TEST(rent->getId() == testId);
    BOOST_TEST(rent->getClient() == testClient1);
    BOOST_TEST(rent->getVehicle() == testVehicle1);
    BOOST_TEST(rent->getBeginTime() == testBeginTime);
    BOOST_TEST(rent->getEndTime().is_not_a_date_time());

    delete rent;
}

BOOST_AUTO_TEST_CASE(RentingTest) {
    BOOST_TEST(testClient1->getCurrentRents().size() == 0);
    BOOST_TEST(testVehicle1->getRentState() == false);
    RentPtr rent = new Rent(testId, testClient1, testVehicle1, testBeginTime);
    BOOST_TEST(testClient1->getCurrentRents().size() == 1);
    BOOST_TEST(rent->getClient()->getCurrentRents().size() == 1);
    BOOST_TEST(testClient1->getCurrentRents()[0] == rent);
    BOOST_TEST(rent->getClient()->getCurrentRents()[0] == rent);
    BOOST_TEST(testVehicle1->getRentState() == true);
    rent->endRent(testEndTime1);
    BOOST_TEST(testVehicle1->getRentState() == false);
    BOOST_TEST(rent->getClient()->getCurrentRents().size() == 0);

    delete rent;
}

BOOST_AUTO_TEST_CASE(RentTimeTest) {
    RentPtr rent1 = new Rent(testId, testClient1, testVehicle1, testBeginTime);
    BOOST_TEST_REQUIRE(rent1->getEndTime().is_not_a_date_time());
    rent1->endRent(pt::not_a_date_time);
    BOOST_TEST(rent1->getEndTime() == pt::second_clock::local_time());
    delete rent1;

    RentPtr rent2 = new Rent(testId, testClient1, testVehicle1, testBeginTime);
    BOOST_TEST_REQUIRE(rent2->getEndTime().is_not_a_date_time());
    rent2->endRent(pt::ptime(gr::date(2009, 1, 1), pt::hours(10)));
    BOOST_TEST(rent2->getEndTime() == rent2->getBeginTime());
    BOOST_TEST(rent2->getRentDays() == 0);
    BOOST_TEST(rent2->getRentCost() == 0);
    delete rent2;

    RentPtr rent3 = new Rent(testId, testClient1, testVehicle1, testBeginTime);
    BOOST_TEST_REQUIRE(rent3->getEndTime().is_not_a_date_time());
    BOOST_TEST(rent3->getRentDays() == 0);
    rent3->endRent(testEndTime1);
    BOOST_TEST(rent3->getEndTime() == testEndTime1);
    rent3->endRent(testEndTime2);
    BOOST_TEST(rent3->getEndTime() == testEndTime1);
    delete rent3;

    pt::ptime t1 = pt::ptime(gr::date(2010, 1, 1), pt::hours(0));
    pt::ptime t2 = pt::ptime(gr::date(2010, 1, 1), pt::hours(0) + pt::minutes(1));
    pt::ptime t3 = pt::ptime(gr::date(2010, 1, 1), pt::hours(23) + pt::minutes(59));
    pt::ptime t4 = pt::ptime(gr::date(2010, 1, 2), pt::hours(0));

    RentPtr rent4 = new Rent(testId, testClient1, testVehicle1, t1);
    rent4->endRent(t2);
    pt::time_period period = pt::time_period(rent4->getBeginTime(), rent4->getEndTime());
    std::cout << period.length() << std::endl;
    BOOST_TEST(rent4->getRentDays() == 0);
    delete rent4;

    RentPtr rent5 = new Rent(testId, testClient1, testVehicle1, t1);
    rent5->endRent(t3);
    pt::time_period period2 = pt::time_period(rent5->getBeginTime(), rent5->getEndTime());
    std::cout << period2.length() << std::endl;
    BOOST_TEST(rent5->getRentDays() == 1);
    BOOST_TEST(rent5->getRentCost() == 200);
    delete rent5;

    RentPtr rent6 = new Rent(testId, testClient1, testVehicle1, t1);
    rent6->endRent(t4);
    pt::time_period period3 = pt::time_period(rent6->getBeginTime(), rent6->getEndTime());
    std::cout << period3.length() << std::endl;
    BOOST_TEST(rent6->getRentDays() == 2);
    BOOST_TEST(rent6->getRentCost() == 400);
    delete rent6;
}

BOOST_AUTO_TEST_SUITE_END()