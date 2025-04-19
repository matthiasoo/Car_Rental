#ifndef CLIENTNOTFOUNDEXCEPTION_H
#define CLIENTNOTFOUNDEXCEPTION_H
#include <stdexcept>

class ClientNotFoundException : public std::runtime_error {
public:
    explicit ClientNotFoundException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif //CLIENTNOTFOUNDEXCEPTION_H
