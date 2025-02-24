#include "ClientManager.h"
#include "ClientRepository.h"
#include "ClientType.h"

ClientManager::ClientManager() {
    this->clientRepo = std::make_shared<ClientRepository>();
}

ClientManager::~ClientManager() {}

ClientPtr ClientManager::getClient(const std::string &personalID) {
    return this->clientRepo->findByPersonalID(personalID);
}

ClientPtr ClientManager::registerClient(const std::string &firstName, const std::string &lastName, const std::string &personalID, AddressPtr address, ClientTypePtr clientType) {
    if (this->getClient(personalID) != nullptr) {
        return this->getClient(personalID);
    } else {
        ClientPtr newClient = std::make_shared<Client>(firstName, lastName, personalID, address, clientType);
        this->clientRepo->add(newClient);
        return newClient;
    }
}
