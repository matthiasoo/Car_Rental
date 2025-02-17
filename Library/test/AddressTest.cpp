#include <boost/test/unit_test.hpp>
#include "Address.h"

using namespace std;

struct TestSuiteAddressFixture {
    std::string testCity1 = "NYC";
    std::string testCity2 = "Paris";
    std::string testStreet1 = "Wall Street";
    std::string testStreet2 = "Croissant";
    std::string testNumber1 = "48";
    std::string testNumber2 = "7";
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteAddress, TestSuiteAddressFixture)

BOOST_AUTO_TEST_CASE(AddressConstructorTest) {
    AddressPtr address = new Address(testCity1, testStreet1, testNumber1);
    BOOST_TEST(address->getCity() == testCity1);
    BOOST_TEST(address->getStreet() == testStreet1);
    BOOST_TEST(address->getNumber() == testNumber1);
    delete address;
}

// BOOST_AUTO_TEST_CASE(AddressSettersTest) {
//     Address *address = new Address(testCity1, testStreet1, testNumber1);
//     address->setCity("");
//     address->setStreet("");
//     address->setNumber("");
//     BOOST_TEST(address->getCity() == testCity1);
//     BOOST_TEST(address->getStreet() == testStreet1);
//     BOOST_TEST(address->getNumber() == testNumber1);
//     address->setCity(testCity2);
//     address->setStreet(testStreet2);
//     address->setNumber(testNumber2);
//     BOOST_TEST(address->getCity() == testCity2);
//     BOOST_TEST(address->getStreet() == testStreet2);
//     BOOST_TEST(address->getNumber() == testNumber2);
//     delete address;
// }

BOOST_AUTO_TEST_SUITE_END()