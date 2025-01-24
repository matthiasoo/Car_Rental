#include <Client.h>
#include <iostream>

int main() {

    Client client = Client("Brad", "Pitt", "123456789");
    Client *clientD = new Client("Leonardo", "DiCaprio", "987654321");

    std::cout << client.getClientInfo() << std::endl;
    client.setFirstName("Bradley");
    std::cout << client.getClientInfo() << std::endl;
    std::cout << clientD->getClientInfo() << std::endl;

    delete clientD;

    return 0;
}
