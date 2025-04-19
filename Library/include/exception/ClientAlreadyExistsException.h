#ifndef CLIENTALREADYEXISTSEXCEPTION_H
#define CLIENTALREADYEXISTSEXCEPTION_H
#include <stdexcept>

class ClientAlreadyExistsException : public std::runtime_error {
public:
    explicit ClientAlreadyExistsException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif //CLIENTALREADYEXISTSEXCEPTION_H
