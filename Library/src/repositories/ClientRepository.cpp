#include "ClientRepository.h"

const ClientPtr ClientRepository::get(int index) const {
    if (index >= 0 && index < this->clientRepository.size()) {
        return this->clientRepository[index];
    } else {
        return nullptr;
    }
}

void ClientRepository::add(ClientPtr client) {
    if (client != nullptr) {
        this->clientRepository.push_back(client);
    }
}

void ClientRepository::remove(ClientPtr client) {
    if (client != nullptr) {
        for (int i = 0; i < this->clientRepository.size(); i++) {
            if (this->clientRepository[i] == client) {
                this->clientRepository.erase(this->clientRepository.begin() + i);
            }
        }
    }
}

std::string ClientRepository::report() const {
    std::string info;
    for (int i = 0; i < this->clientRepository.size(); i++) {
        info += this->clientRepository[i]->getClientInfo() + "\n";
    }

    return info;
}

int ClientRepository::size() {
    return this->clientRepository.size();
}

std::vector<ClientPtr> ClientRepository::findBy(ClientPredicate predicate) const {
    std::vector<ClientPtr> found;
    for (int i = 0; i < clientRepository.size(); i++) {
        ClientPtr client = get(i);
        if (client != nullptr && predicate(client)) {
            found.push_back(client);
        }
    }
    return found;
}

bool alwaysTrue(ClientPtr) {
    return true;
}

std::vector<ClientPtr> ClientRepository::findAll() const {
    ClientPredicate predicate = alwaysTrue;
    return findBy(predicate);
}

ClientPtr ClientRepository::findByPersonalID(const std::string &id) const {
    ClientPredicate predicate = [id](ClientPtr client) {
        return client->getPersonalID() == id;
    };

    std::vector<ClientPtr> result = findBy(predicate);

    return result.empty() ? nullptr : result.front();
}
