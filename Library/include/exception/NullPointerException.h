#ifndef NULLPOINTEREXCEPTION_H
#define NULLPOINTEREXCEPTION_H
#include <stdexcept>

class NullPointerException : public std::runtime_error {
public:
    explicit NullPointerException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif //NULLPOINTEREXCEPTION_H
