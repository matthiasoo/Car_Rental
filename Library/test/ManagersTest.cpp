#include <boost/test/unit_test.hpp>
#include <boost/date_time.hpp>
#include "StorageContainer.h"
#include "ClientType.h"
#include "ClientManager.h"

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

BOOST_AUTO_TEST_SUITE_END()