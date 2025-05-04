#ifndef RENT_EXCEPTION_H
#define RENT_EXCEPTION_H
#include <stdexcept>

class RentException : public std::logic_error {
public:
    explicit RentException(const std::string& message)
        : std::logic_error(message) {}
};

class CannotRentException : public RentException {
public:
    explicit CannotRentException(const std::string& message)
        : RentException(message) {}
};

class RentNotFoundException : public RentException {
public:
    explicit RentNotFoundException(const std::string& message)
        : RentException(message) {}
};

class NotYourVehicleException : public RentException {
public:
    explicit NotYourVehicleException(const std::string& message)
        : RentException(message) {}
};

#endif // RENT_EXCEPTION_H
