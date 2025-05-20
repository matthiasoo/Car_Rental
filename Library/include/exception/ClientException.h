#ifndef CLIENTEXCEPTION_H
#define CLIENTEXCEPTION_H
#include <stdexcept>

class ClientException : public std::logic_error {
public:
    explicit ClientException(const std::string& message)
        : std::logic_error(message) {}
};

#endif //CLIENTEXCEPTION_H
