#include <Client.h>
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(TestSuiteClient)

BOOST_AUTO_TEST_CASE(ConstructorTest) {
    Client client = Client("A", "B", "123");
    BOOST_TEST(client.getFirstName() == "A");
    BOOST_TEST(client.getLastName() == "B");
    BOOST_TEST(client.getPersonalID() == "123");
    BOOST_TEST(client.getClientInfo() == "A B 123");
}

BOOST_AUTO_TEST_CASE(SettersTest) {
    Client client = Client("A", "B", "123");
    client.setFirstName("");
    client.setLastName("");
    BOOST_TEST(client.getFirstName() == "A");
    BOOST_TEST(client.getLastName() == "B");
    client.setFirstName("X");
    client.setLastName("Y");
    BOOST_TEST(client.getFirstName() == "X");
    BOOST_TEST(client.getLastName() == "Y");
}

BOOST_AUTO_TEST_SUITE_END()