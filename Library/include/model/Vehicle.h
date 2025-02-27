#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include "typedefs.h"

class Vehicle {
private:
    std::string plateNumber;
    int basePrice;
    bool archive = false;

public:
    Vehicle(const std::string &plateNumber, const int &basePrice);
    virtual ~Vehicle() = 0;

    // getters
    virtual std::string getVehicleInfo() const;
    const std::string &getPlateNumber() const;
    const int &getBasePrice() const;
    virtual const double getActualRentalPrice() const;
    const bool isArchive() const;

    // setters
    void setPlateNumber(const std::string &plateNumber);
    void setBasePrice(const int &basePrice);
    void setArchive();
};



#endif //VEHICLE_H
