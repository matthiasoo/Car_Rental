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

typedef Client *ClientPtr;
typedef Address *AddressPtr;
typedef Rent *RentPtr;
typedef Vehicle *VehiclePtr;
typedef ClientRepository *ClientRepositoryPtr;
typedef VehicleRepository *VehicleRepositoryPtr;
typedef RentRepository *RentRepositoryPtr;
typedef StorageContainer *StorageContainerPtr;

typedef bool (*ClientPredicate)(ClientPtr);
typedef bool (*VehiclePredicate)(VehiclePtr);
typedef bool (*RentPredicate)(RentPtr);