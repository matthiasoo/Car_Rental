#ifndef MOTORVEHICLE_H
#define MOTORVEHICLE_H

#include "Vehicle.h"

class MotorVehicle : public Vehicle {
protected:
    int engineDisplacement;

public:
    MotorVehicle(const std::string &plateNumber, const int &basePrice, const int &engineDisplacement);
    virtual ~MotorVehicle() = 0;

    const double getActualRentalPrice() const override;
    std::string getVehicleInfo() const override;
};



#endif //MOTORVEHICLE_H
