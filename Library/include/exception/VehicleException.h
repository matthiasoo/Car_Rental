#ifndef VEHICLE_EXCEPTION_H
#define VEHICLE_EXCEPTION_H
#include <stdexcept>

class VehicleException : public std::logic_error {
public:
    explicit VehicleException(const std::string& message)
        : std::logic_error(message) {}
};

class VehicleUnavailableException : public VehicleException {
public:
    explicit VehicleUnavailableException(const std::string& message)
        : VehicleException(message) {}
};

class VehicleAlreadyRentedException : public VehicleException {
public:
    explicit VehicleAlreadyRentedException(const std::string& message)
        : VehicleException(message) {}
};

#endif // VEHICLE_EXCEPTION_H
