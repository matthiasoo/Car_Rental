#ifndef CLIENTEXCEPTION_H
#define CLIENTEXCEPTION_H
#include <stdexcept>

class ClientException : public std::logic_error {
public:
    explicit ClientException(const std::string& message)
        : std::logic_error(message) {}
};

class ClientUnavailableException : public ClientException {
public:
    explicit ClientUnavailableException(const std::string& message)
        : ClientException(message) {}
};

class ClientNotFoundException : public ClientException {
public:
    explicit ClientNotFoundException(const std::string& message)
        : ClientException(message) {}
};

class ClientAlreadyExistsException : public ClientException {
public:
    explicit ClientAlreadyExistsException(const std::string& message)
        : ClientException(message) {}
};

#endif //CLIENTEXCEPTION_H
