#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include "typedefs.h"

class Address;
class Rent;
class ClientType;

class Client {
private:
    std::string firstName;
    std::string lastName;
    std::string personalID;
    AddressPtr address;
    ClientTypePtr clientType;
    bool archive = false;

public:

    // Client();
    Client(const std::string &firstName, const std::string &lastName, const std::string &personalID, AddressPtr address, ClientTypePtr clientType);
    ~Client();

    // getters
    std::string getClientInfo() const;
    const std::string &getFirstName() const;
    const std::string &getLastName() const;
    const std::string &getPersonalID() const;
    const AddressPtr getAddress() const;
    const int getMaxVehicles() const;
    const bool isArchive() const;

    // setters
    void setFirstName(const std::string &firstName);
    void setLastName(const std::string &lastName);
    void setAddress(AddressPtr address);
    void setClientType(ClientTypePtr clientType);
    void setArchive();

    const double applyDiscount(double price);
};



#endif //CLIENT_H
