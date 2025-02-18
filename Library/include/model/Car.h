#ifndef CAR_H
#define CAR_H

#include "MotorVehicle.h"

enum SegmentType {
    A = 10,
    B = 11,
    C = 12,
    D = 13,
    E = 15
};

class Car : public MotorVehicle {
private:
    SegmentType segment;

public:
    Car(const std::string &plateNumber, const int &basePrice, const int &engineDisplacement, const SegmentType &segment);
    ~Car();

    const double getActualRentalPrice() const override;
    std::string getVehicleInfo() const override;
};



#endif //CAR_H
