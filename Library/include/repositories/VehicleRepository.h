#ifndef VEHICLEREPOSITORY_H
#define VEHICLEREPOSITORY_H

#include "Vehicle.h"
#include <vector>

class VehicleRepository {
private:
    std::vector<VehiclePtr> vehicleRepository;

public:
    const VehiclePtr get(int index) const;
    void add(VehiclePtr vehicle);
    void remove(VehiclePtr vehicle);
    std::string report() const;
    int size();
};



#endif //VEHICLEREPOSITORY_H
