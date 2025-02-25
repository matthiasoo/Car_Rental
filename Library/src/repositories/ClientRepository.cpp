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

std::vector<ClientPtr> ClientRepository::findAll() const {
    return findBy([](ClientPtr) { return true; });
}

ClientPtr ClientRepository::findByPersonalID(const std::string &id) const {
    std::vector<ClientPtr> result = findBy([id](ClientPtr client) {
        return client->getPersonalID() == id;
    });

    return result.empty() ? nullptr : result.front();
}
