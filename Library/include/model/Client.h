#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Address;

class Client {
private:
    std::string firstName;
    std::string lastName;
    std::string personalID;
    Address* address;

public:
    // Client();
    Client(const std::string &firstName, const std::string &lastName, const std::string &personalID, Address *address);
    ~Client();

    // getters
    std::string getClientInfo();
    const std::string &getFirstName() const;
    const std::string &getLastName() const;
    const std::string &getPersonalID() const;
    const Address* getAddress() const;

    // setters
    void setFirstName(const std::string &firstName);
    void setLastName(const std::string &lastName);
    void setAddress(Address *address);
};



#endif //CLIENT_H
