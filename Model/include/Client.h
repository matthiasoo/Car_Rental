#ifndef CLIENT_H
#define CLIENT_H
#include <string>


class Client {
private:
    std::string firstName;
    std::string lastName;
    std::string personalID;

public:
    // Client();
    Client(std::string firstName, std::string lastName, std::string personalID);

    ~Client();

    // getters
    std::string getClientInfo();
    std::string getFirstName();
    std::string getLastName();
    std::string getPersonalID();

    // setters
    void setFirstName(std::string firstName);
    void setLastName(std::string lastName);
};



#endif //CLIENT_H
