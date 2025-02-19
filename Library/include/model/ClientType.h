#ifndef CLIENTTYPE_H
#define CLIENTTYPE_H

#include <string>

class ClientType {
public:
    ClientType();
    virtual ~ClientType() = 0;;

    virtual int getMaxVehicles() = 0;
    virtual double applyDiscount(double price) = 0;
    virtual std::string getTypeInfo() = 0;
};

class Default : public ClientType {
public:
    Default();
    ~Default();

    int getMaxVehicles() override;
    double applyDiscount(double price) override;
    std::string getTypeInfo() override;
};

class Bronze : public ClientType {
public:
    Bronze();
    ~Bronze();

    int getMaxVehicles() override;
    double applyDiscount(double price) override;
    std::string getTypeInfo() override;
};

class Silver : public ClientType {
public:
    Silver();
    ~Silver();

    int getMaxVehicles() override;
    double applyDiscount(double price) override;
    std::string getTypeInfo() override;
};

class Gold : public ClientType {
public:
    Gold();
    ~Gold();

    int getMaxVehicles() override;
    double applyDiscount(double price) override;
    std::string getTypeInfo() override;
};

class Platinum : public ClientType {
public:
    Platinum();
    ~Platinum();

    int getMaxVehicles() override;
    double applyDiscount(double price) override;
    std::string getTypeInfo() override;
};

class Diamond : public ClientType {
public:
    Diamond();
    ~Diamond();

    int getMaxVehicles() override;
    double applyDiscount(double price) override;
    std::string getTypeInfo() override;
};

#endif //CLIENTTYPE_H
