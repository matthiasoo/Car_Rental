#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>

class Address;
class Rent;

class Client {
private:
    std::string firstName;
    std::string lastName;
    std::string personalID;
    Address *address;
    std::vector<Rent*> currentRents;

public:

    // Client();
    Client(const std::string &firstName, const std::string &lastName, const std::string &personalID, Address *address);
    ~Client();

    // getters
    std::string getClientInfo() const;
    std::string getFullClientInfo() const;
    const std::string &getFirstName() const;
    const std::string &getLastName() const;
    const std::string &getPersonalID() const;
    const Address *getAddress() const;
    const std::vector<Rent*> &getCurrentRents() const;

    // setters
    void setFirstName(const std::string &firstName);
    void setLastName(const std::string &lastName);
    void setAddress(Address *address);

    void addRent(Rent *rent);
    void removeRent(Rent *rent);
};



#endif //CLIENT_H
