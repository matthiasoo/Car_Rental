#ifndef INVALIDTEXTEXCEPTION_H
#define INVALIDTEXTEXCEPTION_H
#include <stdexcept>


class InvalidTextException : public std::invalid_argument {
public:
    explicit InvalidTextException(const std::string& msg) : std::invalid_argument(msg) {}
};



#endif //INVALIDTEXTEXCEPTION_H
