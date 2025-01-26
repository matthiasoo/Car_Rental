#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle {
private:
    std::string plateNumber;
    int basePrice;

public:
    Vehicle(const std::string &plateNumber, const int &basePrice);
    ~Vehicle();

    // getters
    std::string getVehicleInfo();
    const std::string &getPlateNumber() const;
    const int &getBasePrice() const;

    // setters
    void setPlateNumber(const std::string &plateNumber);
    void setBasePrice(const int &basePrice);
};



#endif //VEHICLE_H
