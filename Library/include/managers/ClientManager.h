#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H
#include <typedefs.h>


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
};



#endif //CLIENTMANAGER_H
