#ifndef CLIENT_H
#define CLIENT_H

#include "typedefs.h"

#include <string>
#include <vector>

class Address;
class Rent;

class Client {
private:
    std::string firstName;
    std::string lastName;
    std::string personalID;
    AddressPtr address;
    std::vector<RentPtr> currentRents;

public:

    // Client();
    Client(const std::string &firstName, const std::string &lastName, const std::string &personalID, AddressPtr address);
    ~Client();

    // getters
    std::string getClientInfo() const;
    std::string getFullClientInfo() const;
    const std::string &getFirstName() const;
    const std::string &getLastName() const;
    const std::string &getPersonalID() const;
    const AddressPtr getAddress() const;
    const std::vector<RentPtr> &getCurrentRents() const;

    // setters
    void setFirstName(const std::string &firstName);
    void setLastName(const std::string &lastName);
    void setAddress(AddressPtr address);

    void addRent(RentPtr rent);
    void removeRent(RentPtr rent);
};



#endif //CLIENT_H
