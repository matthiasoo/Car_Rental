#ifndef VEHICLEREPOSITORY_H
#define VEHICLEREPOSITORY_H

#include <vector>
#include "Vehicle.h"

class VehicleRepository {
private:
    std::vector<VehiclePtr> vehicleRepository;

public:
    const VehiclePtr get(int index) const;
    void add(VehiclePtr vehicle);
    void remove(VehiclePtr vehicle);
    std::string report() const;
    int size();

    std::vector<VehiclePtr> findBy(VehiclePredicate predicate) const;
    std::vector<VehiclePtr> findAll() const;
    VehiclePtr findByPlateNumber(const std::string &plateNumber) const;
};



#endif //VEHICLEREPOSITORY_H
