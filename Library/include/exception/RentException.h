#ifndef RENT_EXCEPTION_H
#define RENT_EXCEPTION_H
#include <stdexcept>

class RentException : public std::logic_error {
public:
    explicit RentException(const std::string& message)
        : std::logic_error(message) {}
};

#endif // RENT_EXCEPTION_H
