#include <ShiraNet.hpp>
#include <iostream>
#include <sys/socket.h>
#include <thread>

#include "ATCStartup/startup.hpp"

struct ClientData {
    bool power = false;
};

ClientData clientData;

ATCReturnData atcReturn;

void togglePowerMessage(ShiraNet::NetworkData::Message &message) {
    ShiraNet::NetworkData::DataField<bool> data;
    message.payloadToDataField(data);

    clientData.power = data.data;
    std::cout << "power is now: " << std::to_string(data.data) << std::endl;
}

void handleMessage(ShiraNet::NetworkData::Message &message) {
    switch (message.id) {
    case 0:
        break;

    case 1:
        togglePowerMessage(message);
        break;

    default:
        break;
    }
}

void clientCallback(std::shared_ptr<ShiraNet::Sockets::TcpSocket> client, ShiraNet::Servers::TcpServer *server) {
    while (true) {
        try {
            ShiraNet::NetworkData::Message message = client->receiveMessage(MSG_DONTWAIT);
            handleMessage(message);
        } catch (...) {
        }

        try {
            ShiraNet::NetworkData::DataField<ATCReturnData> ATCDataField{sizeof(ATCReturnData), atcReturn};
            ShiraNet::NetworkData::Message ATCDataMessage(0, ATCDataField);
            client->send(ATCDataMessage);
            std::cout << "sent message\n";
        } catch (const std::exception &e) {
            std::cerr << "Failed to send (std): " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Failed to send: unknown exception\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void server(ShiraNet::Servers::TcpServer *server) {
    while (true) {
        server->getConnection(clientCallback);
    }
}

int main() {
    ShiraNet::Servers::TcpServer ATCServer(AF_INET, 1337, 10);
    std::thread serverThread(server, &ATCServer);

    ATCData atcData;
    internalATCData atcInternal;

    while (true) {
        if (clientData.power || atcInternal.startup == 1) {
            clientData.power = false;
            ATC::startupSequence(atcData, atcInternal, atcReturn);
        }
    }
}