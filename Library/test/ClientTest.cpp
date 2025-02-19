#include <boost/test/unit_test.hpp>
#include "Client.h"
#include "Address.h"

struct TestSuiteClientFixture {
    const std::string testFirstName1 = "Brad";
    const std::string testFirstName2 = "Leonardo";
    const std::string testLastName1 = "Pitt";
    const std::string testLastName2 = "DiCaprio";
    const std::string testPersonalID = "123";
    AddressPtr testAddress1;
    AddressPtr testAddress2;

    TestSuiteClientFixture() {
        testAddress1 = std::make_shared<Address>("NYC", "Wall Street", "10");
        testAddress2 = std::make_shared<Address>("LA", "Main", "21");
    }

    ~TestSuiteClientFixture() {}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteClient, TestSuiteClientFixture)

BOOST_AUTO_TEST_CASE(ClientConstructorTest) {
    ClientPtr client = std::make_shared<Client>(testFirstName1, testLastName1, testPersonalID, testAddress1);
    BOOST_TEST(client->getFirstName() == testFirstName1);
    BOOST_TEST(client->getLastName() == testLastName1);
    BOOST_TEST(client->getPersonalID() == testPersonalID);
    BOOST_TEST(client->getAddress() == testAddress1);
}

BOOST_AUTO_TEST_CASE(ClientSettersTest) {
    ClientPtr client = std::make_shared<Client>(testFirstName1, testLastName1, testPersonalID, testAddress1);
    client->setFirstName("");
    client->setLastName("");
    client->setAddress(nullptr);
    BOOST_TEST(client->getFirstName() == testFirstName1);
    BOOST_TEST(client->getLastName() == testLastName1);
    BOOST_TEST(client->getAddress() == testAddress1);
    client->setFirstName(testFirstName2);
    client->setLastName(testLastName2);
    client->setAddress(testAddress2);
    BOOST_TEST(client->getFirstName() == testFirstName2);
    BOOST_TEST(client->getLastName() == testLastName2);
    BOOST_TEST(client->getAddress() == testAddress2);
}

BOOST_AUTO_TEST_SUITE_END()