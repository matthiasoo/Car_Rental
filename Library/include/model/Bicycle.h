#ifndef BICYCLE_H
#define BICYCLE_H

#include "Vehicle.h"

class Bicycle : public Vehicle {
public:
    Bicycle(const std::string &plateNumber, const int &basePrice);
    ~Bicycle();

    const double getActualRentalPrice() const override;
    std::string getVehicleInfo() const override;
};



#endif //BICYCLE_H
