#ifndef VEHICLE_EXCEPTION_H
#define VEHICLE_EXCEPTION_H
#include <stdexcept>

class VehicleException : public std::logic_error {
public:
    explicit VehicleException(const std::string& message)
        : std::logic_error(message) {}
};

#endif // VEHICLE_EXCEPTION_H
