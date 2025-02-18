#ifndef MOPED_H
#define MOPED_H

#include "MotorVehicle.h"

class Moped : public MotorVehicle {
public:
    Moped(const std::string &plateNumber, const int &basePrice, const int &engineDisplacement);
    ~Moped();

    const double getActualRentalPrice() const override;
    std::string getVehicleInfo() const override;
};



#endif //MOPED_H
