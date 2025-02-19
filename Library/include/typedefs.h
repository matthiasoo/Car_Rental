#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <memory>

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

typedef std::shared_ptr<Client> ClientPtr;
typedef std::shared_ptr<Address> AddressPtr;
typedef std::shared_ptr<Rent> RentPtr;
typedef std::shared_ptr<Vehicle> VehiclePtr;
typedef std::shared_ptr<ClientRepository> ClientRepositoryPtr;
typedef std::shared_ptr<VehicleRepository> VehicleRepositoryPtr;
typedef std::shared_ptr<RentRepository> RentRepositoryPtr;
typedef std::shared_ptr<StorageContainer> StorageContainerPtr;
typedef std::shared_ptr<Bicycle> BicyclePtr;
typedef std::shared_ptr<MotorVehicle> MotorVehiclePtr;
typedef std::shared_ptr<Moped> MopedPtr;
typedef std::shared_ptr<Car> CarPtr;

typedef bool (*ClientPredicate)(ClientPtr);
typedef bool (*VehiclePredicate)(VehiclePtr);
typedef bool (*RentPredicate)(RentPtr);