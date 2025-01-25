#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

class Address {
private:
    std::string city;
    std::string street;
    std::string number;

public:
    Address(const std::string &city, const std::string &street, const std::string &number);
    ~Address();

    // getters
    std::string getAddressInfo();
    std::string getCity() const;
    std::string getStreet() const;
    std::string getNumber() const;

    // setters
    // void setCity(std::string city);
    // void setStreet(std::string street);
    // void setNumber(std::string number);
};



#endif //ADDRESS_H
