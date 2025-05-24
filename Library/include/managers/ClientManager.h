#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H
#include "typedefs.h"
#include "ClientRepository.h"
#include "ClientType.h"

class ClientManager {
private:
    ClientRepositoryPtr clientRepo;

public:
    ClientManager();
    ~ClientManager();

    ClientPtr getClient(const std::string &personalID);
    ClientPtr registerClient(const std::string &firstName, const std::string &lastName, const std::string &personalID,
        AddressPtr address, ClientTypePtr clientType);
    void unregisterClient(const std::string &personalID);
    std::vector<ClientPtr> findClients(ClientPredicate predicate);
    std::vector<ClientPtr> findAllClients();
    std::string listAllClients();
};



#endif //CLIENTMANAGER_H
