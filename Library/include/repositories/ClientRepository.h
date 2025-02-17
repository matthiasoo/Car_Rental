#ifndef CLIENTREPOSITORY_H
#define CLIENTREPOSITORY_H

#include <vector>
#include "Client.h"
#include "Address.h"

class ClientRepository {
private:
    std::vector<ClientPtr> clientRepository;

public:
    const ClientPtr get(int index) const;
    void add(ClientPtr client);
    void remove(ClientPtr client);
    std::string report() const;
    int size();
};



#endif //CLIENTREPOSITORY_H
