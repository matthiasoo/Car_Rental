#include "ClientManager.h"

#include <iostream>
#include "NullPointerException.h"
#include "ClientException.h"

ClientManager::ClientManager() {
    this->clientRepo = std::make_shared<ClientRepository>();
}

ClientManager::~ClientManager() {}

ClientPtr ClientManager::getClient(const std::string &personalID) {
    ClientPtr client = this->clientRepo->findByPersonalID(personalID);
    if (client == nullptr) {
        throw ClientNotFoundException("Client with ID: " + personalID + " not found.");
    }
    return client;
}

ClientPtr ClientManager::registerClient(const std::string &firstName, const std::string &lastName, const std::string &personalID, AddressPtr address, ClientTypePtr clientType) {
    if (clientRepo->findByPersonalID(personalID)) {
        throw ClientAlreadyExistsException("Client with ID: " + personalID + " already exists.");
    }

    ClientPtr newClient = std::make_shared<Client>(firstName, lastName, personalID, address, clientType);
    this->clientRepo->add(newClient);
    return newClient;
}

void ClientManager::unregisterClient(const std::string &personalID) {
    if (this->getClient(personalID) == nullptr) {
        throw ClientNotFoundException("Client with ID: " + personalID + " not found.");
    } else {
        this->getClient(personalID)->setArchive();
    }
}

std::vector<ClientPtr> ClientManager::findClients(ClientPredicate predicate) {
    return this->clientRepo->findBy([predicate](ClientPtr client) {
        return !client->isArchive() && predicate(client);
    });
}

std::vector<ClientPtr> ClientManager::findAllClients() {
    return this->findClients([](ClientPtr) { return true; });
}
