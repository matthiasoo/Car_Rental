#include <boost/test/unit_test.hpp>
#include <boost/date_time.hpp>
#include "Rent.h"
#include "Client.h"
#include "Address.h"
#include "Vehicle.h"
#include "Bicycle.h"
#include "ClientType.h"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

struct TestSuiteRentFixture {
    int testId = 1;
    ClientPtr testClient1;
    AddressPtr testAddress1;
    VehiclePtr testVehicle1;
    ClientTypePtr testType1;
    ClientTypePtr testType2;
    pt::ptime testBeginTime = pt::ptime(gr::date(2010, 1, 1), pt::hours(10));
    pt::ptime testEndTime1 = pt::ptime(gr::date(2020, 1, 1), pt::hours(10));
    pt::ptime testEndTime2 = pt::ptime(gr::date(2023, 1, 1), pt::hours(10));

    TestSuiteRentFixture() {
        testAddress1 = std::make_shared<Address>("NYC", "Wall Street", "10");
        testType1 = std::make_shared<Silver>();
        testType2 = std::make_shared<Diamond>();
        testClient1 = std::make_shared<Client>("Brad", "Pitt", "8899", testAddress1, testType1);
        testVehicle1 = std::make_shared<Bicycle>("US0067", 200);
    }

    ~TestSuiteRentFixture() {}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRent, TestSuiteRentFixture)

BOOST_AUTO_TEST_CASE(RentConstructorTest) {
    RentPtr rent = std::make_shared<Rent>(testId, testClient1, testVehicle1, testBeginTime);
    BOOST_TEST(rent->getId() == testId);
    BOOST_TEST(rent->getClient() == testClient1);
    BOOST_TEST(rent->getVehicle() == testVehicle1);
    BOOST_TEST(rent->getBeginTime() == testBeginTime);
    BOOST_TEST(rent->getEndTime().is_not_a_date_time());
}

BOOST_AUTO_TEST_CASE(RentingTest) {
    auto mockTime = pt::time_from_string("2023-01-01 12:00:00");
    auto timeProvider = [mockTime]() {return mockTime;};

    BOOST_TEST(testVehicle1->isRented() == false);
    RentPtr rent = std::make_shared<Rent>(testId, testClient1, testVehicle1, testBeginTime, timeProvider);
    BOOST_TEST(testVehicle1->isRented() == true);
    rent->endRent();
    BOOST_TEST(testVehicle1->isRented() == false);

    BOOST_TEST(rent->getEndTime() == mockTime);
}

BOOST_AUTO_TEST_CASE(RentTimeTest) {
    RentPtr rent1 =std::make_shared<Rent>(testId, testClient1, testVehicle1, testBeginTime);
    BOOST_TEST_REQUIRE(rent1->getEndTime().is_not_a_date_time());
    rent1->endRent();
    BOOST_TEST(rent1->getEndTime() == pt::second_clock::local_time());

    auto mockTime = pt::time_from_string("2009-01-01 10:00:00");
    auto timeProvider1 = [mockTime]() {return mockTime;};
    RentPtr rent2 = std::make_shared<Rent>(testId, testClient1, testVehicle1, testBeginTime, timeProvider1);
    BOOST_TEST_REQUIRE(rent2->getEndTime().is_not_a_date_time());
    rent2->endRent();
    BOOST_TEST(rent2->getEndTime() == rent2->getBeginTime());
    BOOST_TEST(rent2->getRentDays() == 0);
    BOOST_TEST(rent2->getRentCost() == 0);

    pt::ptime t1 = pt::ptime(gr::date(2010, 1, 1), pt::hours(0));
    pt::ptime t2 = pt::ptime(gr::date(2010, 1, 1), pt::hours(0) + pt::minutes(1));
    pt::ptime t3 = pt::ptime(gr::date(2010, 1, 1), pt::hours(23) + pt::minutes(59));
    pt::ptime t4 = pt::ptime(gr::date(2010, 1, 2), pt::hours(0));

    mockTime = t2;
    auto timeProvider2 = [mockTime]() {return mockTime;};
    RentPtr rent4 = std::make_shared<Rent>(testId, testClient1, testVehicle1, t1, timeProvider2);
    rent4->endRent();
    pt::time_period period = pt::time_period(rent4->getBeginTime(), rent4->getEndTime());
    std::cout << period.length() << std::endl;
    BOOST_TEST(rent4->getRentDays() == 0);

    mockTime = t3;
    auto timeProvider3 = [mockTime]() {return mockTime;};
    RentPtr rent5 = std::make_shared<Rent>(testId, testClient1, testVehicle1, t1, timeProvider3);
    rent5->endRent();
    pt::time_period period2 = pt::time_period(rent5->getBeginTime(), rent5->getEndTime());
    std::cout << period2.length() << std::endl;
    BOOST_TEST(rent5->getRentDays() == 1);
    BOOST_TEST(rent5->getRentCost() == 194);

    testClient1->setClientType(testType2);

    mockTime = t4;
    auto timeProvider4 = [mockTime]() {return mockTime;};
    RentPtr rent6 = std::make_shared<Rent>(testId, testClient1, testVehicle1, t1, timeProvider4);
    rent6->endRent();
    pt::time_period period3 = pt::time_period(rent6->getBeginTime(), rent6->getEndTime());
    std::cout << period3.length() << std::endl;
    BOOST_TEST(rent6->getRentDays() == 2);
    BOOST_TEST(rent6->getRentCost() == 280);
}

BOOST_AUTO_TEST_SUITE_END()