#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#endif //TYPEDEFS_H

class Client;
class Address;
class Rent;
class Vehicle;
class ClientRepository;
class VehicleRepository;
class RentRepository;
class StorageContainer;
class Bicycle;
class MotorVehicle;
class Moped;
class Car;

typedef Client *ClientPtr;
typedef Address *AddressPtr;
typedef Rent *RentPtr;
typedef Vehicle *VehiclePtr;
typedef ClientRepository *ClientRepositoryPtr;
typedef VehicleRepository *VehicleRepositoryPtr;
typedef RentRepository *RentRepositoryPtr;
typedef StorageContainer *StorageContainerPtr;
typedef Bicycle *BicyclePtr;
typedef MotorVehicle *MotorVehiclePtr;
typedef Moped *MopedPtr;
typedef Car *CarPtr;

typedef bool (*ClientPredicate)(ClientPtr);
typedef bool (*VehiclePredicate)(VehiclePtr);
typedef bool (*RentPredicate)(RentPtr);