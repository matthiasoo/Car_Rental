#include <InvalidValueException.h>
#include <NullPointerException.h>
#include <boost/test/unit_test.hpp>
#include "Client.h"
#include "Address.h"
#include "ClientType.h"

struct TestSuiteClientFixture {
    const std::string testFirstName1 = "Brad";
    const std::string testFirstName2 = "Leonardo";
    const std::string testLastName1 = "Pitt";
    const std::string testLastName2 = "DiCaprio";
    const std::string testPersonalID = "123";
    AddressPtr testAddress1;
    AddressPtr testAddress2;
    ClientTypePtr testType1;
    ClientTypePtr testType2;
    ClientTypePtr testType3;

    TestSuiteClientFixture() {
        testAddress1 = std::make_shared<Address>("NYC", "Wall Street", "10");
        testAddress2 = std::make_shared<Address>("LA", "Main", "21");
        testType1 = std::make_shared<Silver>();
        testType2 = std::make_shared<Diamond>();
        testType3 = std::make_shared<Platinum>();
    }

    ~TestSuiteClientFixture() {}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteClient, TestSuiteClientFixture)

BOOST_AUTO_TEST_CASE(ClientConstructorTest) {
    ClientPtr client = std::make_shared<Client>(testFirstName1, testLastName1, testPersonalID, testAddress1, testType1);
    BOOST_TEST(client->getFirstName() == testFirstName1);
    BOOST_TEST(client->getLastName() == testLastName1);
    BOOST_TEST(client->getPersonalID() == testPersonalID);
    BOOST_TEST(client->getAddress() == testAddress1);
    BOOST_TEST(client->getMaxVehicles() == 3);
    BOOST_TEST(client->applyDiscount(100) == 6);
    BOOST_TEST(client->isArchive() == false);
    client->setArchive();
    BOOST_TEST(client->isArchive() == true);
}

BOOST_AUTO_TEST_CASE(ClientSettersTest) {
    ClientPtr client = std::make_shared<Client>(testFirstName1, testLastName1, testPersonalID, testAddress1, testType2);
    BOOST_CHECK_THROW(client->setFirstName(""), InvalidValueException);
    BOOST_CHECK_THROW(client->setLastName(""), InvalidValueException);
    BOOST_CHECK_THROW(client->setAddress(nullptr), NullPointerException);
    BOOST_TEST(client->getFirstName() == testFirstName1);
    BOOST_TEST(client->getLastName() == testLastName1);
    BOOST_TEST(client->getAddress() == testAddress1);
    client->setFirstName(testFirstName2);
    client->setLastName(testLastName2);
    client->setAddress(testAddress2);
    BOOST_TEST(client->getFirstName() == testFirstName2);
    BOOST_TEST(client->getLastName() == testLastName2);
    BOOST_TEST(client->getAddress() == testAddress2);
    BOOST_TEST(client->getMaxVehicles() == 10);
    BOOST_TEST(client->applyDiscount(200) == 40);
    client->setClientType(testType3);
    BOOST_TEST(client->getMaxVehicles() == 5);
    BOOST_TEST(client->applyDiscount(200) == 20);
}

BOOST_AUTO_TEST_SUITE_END()