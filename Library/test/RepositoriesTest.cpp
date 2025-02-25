#include <boost/test/unit_test.hpp>
#include <boost/date_time.hpp>
#include "StorageContainer.h"
#include "Address.h"
#include "Bicycle.h"
#include "ClientType.h"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

struct TestSuiteRepoFixture {
    ClientPtr testClient1;
    AddressPtr testAddress1;
    VehiclePtr testVehicle1;
    RentPtr testRent1;
    ClientTypePtr testType1;
    pt::ptime testBeginTime = pt::ptime(gr::date(2010, 1, 1), pt::hours(10));
    pt::ptime testEndTime1 = pt::ptime(gr::date(2020, 1, 1), pt::hours(10));
    pt::ptime testEndTime2 = pt::ptime(gr::date(2023, 1, 1), pt::hours(10));

    StorageContainerPtr data;

    TestSuiteRepoFixture() {
        testAddress1 = std::make_shared<Address>("NYC", "Wall Street", "10");
        testType1 = std::make_shared<Gold>();
        testClient1 = std::make_shared<Client>("Tobey", "Maguire", "8899", testAddress1, testType1);
        testVehicle1 = std::make_shared<Bicycle>("US0067", 200);
        testRent1 = std::make_shared<Rent>(3, testClient1, testVehicle1, testBeginTime);
        testRent1->endRent(testEndTime1);

        data = std::make_shared<StorageContainer>();
    }

    ~TestSuiteRepoFixture() {}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRepo, TestSuiteRepoFixture)

BOOST_AUTO_TEST_CASE(ClientRepositoryTest) {
    BOOST_TEST(data->getClientRepository()->size() == 2);
    BOOST_TEST(data->getClientRepository()->get(2) == nullptr);
    data->getClientRepository()->add(testClient1);
    BOOST_TEST(data->getClientRepository()->size() == 3);
    BOOST_TEST(data->getClientRepository()->get(2) == testClient1);
    BOOST_TEST(data->getClientRepository()->get(2)->getFirstName() == "Tobey");
    BOOST_TEST(data->getClientRepository()->get(2)->getLastName() == "Maguire");
    BOOST_TEST(data->getClientRepository()->get(2)->getPersonalID() == "8899");
    BOOST_TEST(data->getClientRepository()->get(2)->getAddress() == testAddress1);

    ClientPredicate predicate = [](const ClientPtr &search) { return search->getFirstName() == "Tobey"; };
    BOOST_TEST(data->getClientRepository()->findBy(predicate).size() == 1);
    BOOST_TEST(data->getClientRepository()->findBy(predicate)[0]->getFirstName() == "Tobey");
    BOOST_TEST(data->getClientRepository()->findAll().size() == 3);

    data->getClientRepository()->remove(testClient1);
    BOOST_TEST(data->getClientRepository()->size() == 2);
    BOOST_TEST(data->getClientRepository()->get(2) == nullptr);

    ClientPtr client1 = std::make_shared<Client>("X", "Y", "123", testAddress1, testType1);
    ClientPtr client2 = std::make_shared<Client>("W", "Z", "123", testAddress1, testType1);
    data->getClientRepository()->add(client1);
    data->getClientRepository()->add(client2);
    ClientPredicate pred2 = [](const ClientPtr &search) { return search->getPersonalID() == "123"; };
    BOOST_TEST(data->getClientRepository()->findBy(pred2).size() == 2);
}

BOOST_AUTO_TEST_CASE(VehicleRepositoryTest) {
    BOOST_TEST(data->getVehicleRepository()->size() == 3);
    BOOST_TEST(data->getVehicleRepository()->get(3) == nullptr);
    data->getVehicleRepository()->add(testVehicle1);
    BOOST_TEST(data->getVehicleRepository()->size() == 4);
    BOOST_TEST(data->getVehicleRepository()->get(3) == testVehicle1);
    BOOST_TEST(data->getVehicleRepository()->get(3)->getPlateNumber() == "US0067");
    BOOST_TEST(data->getVehicleRepository()->get(3)->getBasePrice() == 200);

    VehiclePredicate predicate = [](const VehiclePtr& search) { return search->getPlateNumber() == "US0067"; };
    BOOST_TEST(data->getVehicleRepository()->findBy(predicate).size() == 1);
    BOOST_TEST(data->getVehicleRepository()->findBy(predicate)[0]->getPlateNumber() == "US0067");
    BOOST_TEST(data->getVehicleRepository()->findAll().size() == 4);

    data->getVehicleRepository()->remove(testVehicle1);
    BOOST_TEST(data->getVehicleRepository()->size() == 3);
    BOOST_TEST(data->getVehicleRepository()->get(3) == nullptr);
}

BOOST_AUTO_TEST_CASE(RentRepositoryTest) {
    BOOST_TEST(data->getRentRepository()->size() == 2);
    BOOST_TEST(data->getRentRepository()->get(2) == nullptr);
    data->getRentRepository()->add(testRent1);
    BOOST_TEST(data->getRentRepository()->size() == 3);
    BOOST_TEST(data->getRentRepository()->get(2) == testRent1);
    BOOST_TEST(data->getRentRepository()->get(2)->getId() == 3);
    BOOST_TEST(data->getRentRepository()->get(2)->getClient() == testClient1);
    BOOST_TEST(data->getRentRepository()->get(2)->getVehicle() == testVehicle1);
    BOOST_TEST(data->getRentRepository()->get(2)->getBeginTime() == testBeginTime);
    BOOST_TEST(data->getRentRepository()->get(2)->getEndTime() == testEndTime1);

    RentPredicate predicate = [](const RentPtr& search) { return search->getId() == 3; };
    BOOST_TEST(data->getRentRepository()->findBy(predicate).size() == 1);
    BOOST_TEST(data->getRentRepository()->findBy(predicate)[0]->getId() == 3);
    BOOST_TEST(data->getRentRepository()->findAll().size() == 3);

    data->getRentRepository()->remove(testRent1);
    BOOST_TEST(data->getRentRepository()->size() == 2);
    BOOST_TEST(data->getRentRepository()->get(2) == nullptr);
}

BOOST_AUTO_TEST_SUITE_END()