#ifndef INVALIDVALUEEXCEPTION_H
#define INVALIDVALUEEXCEPTION_H
#include <stdexcept>

class InvalidValueException : public std::invalid_argument {
public:
    explicit InvalidValueException(const std::string& msg) : std::invalid_argument(msg) {}
};

#endif //INVALIDVALUEEXCEPTION_H
