#include <boost/test/unit_test.hpp>
#include <boost/date_time.hpp>
#include "StorageContainer.h"
#include "ClientType.h"
#include "ClientManager.h"

struct TestSuiteManagersFixture {
    AddressPtr testAddress1;
    ClientTypePtr testType1;

    TestSuiteManagersFixture() {
        testAddress1 = std::make_shared<Address>("NYC", "Wall Street", "10");
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
    BOOST_TEST(clientManager->getClient("555") == client2);
}

BOOST_AUTO_TEST_SUITE_END()