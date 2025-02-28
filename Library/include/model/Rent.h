#ifndef RENT_H
#define RENT_H

#include <string>
#include <boost/date_time.hpp>
#include "typedefs.h"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

class Client;
class Vehicle;

class Rent {
private:
    int id; // maybe unsigned
    ClientPtr client;
    VehiclePtr vehicle;
    pt::ptime beginTime;
    pt::ptime endTime = pt::not_a_date_time;
    double rentCost = 0;

public:
    Rent(const int &id, ClientPtr client, VehiclePtr vehicle, const pt::ptime &beginTime);
    ~Rent();

    // getters
    std::string getRentInfo() const;
    const int &getId() const;
    const ClientPtr getClient() const;
    const VehiclePtr getVehicle() const;
    const pt::ptime &getBeginTime() const;
    const pt::ptime &getEndTime() const;
    int getRentDays();
    const double getRentCost();

    // void endRent(const pt::ptime &endRent);
    void endRent();
};



#endif //RENT_H
