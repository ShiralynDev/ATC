#include <ShiraNet.hpp>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <thread>
#include <vector>

#include "ATCStartup/startup.hpp"

struct ClientData {
    bool power = false;
    bool isCabA = true;
};

ClientData clientData;

ATCReturnData atcReturn;

void togglePowerMessage(ShiraNet::NetworkData::Message &message) {
    ShiraNet::NetworkData::DataField<bool> data;
    message.payloadToDataField(data);

    clientData.power = data.data;
}

void togglePowerMessageWithCabID(ShiraNet::NetworkData::Message &message) {
    ShiraNet::NetworkData::DataField<std::vector<bool>> data;
    message.payloadToDataField(data);

    clientData.power = data.data.at(0);
    clientData.isCabA = data.data.at(1);
}

void handleMessage(ShiraNet::NetworkData::Message &message) {
    switch (message.id) {
    case 0:
        break;

    case 1:
        togglePowerMessage(message);
        break;

    case 2:
        togglePowerMessageWithCabID(message);
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
        } catch (const std::exception &e) {
            std::cerr << "Failed to send (std): " << e.what() << std::endl;
            break;
        } catch (...) {
            std::cerr << "Failed to send: unknown exception\n";
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void server(ShiraNet::Servers::TcpServer *server) {
    while (true) {
        server->getConnection(clientCallback);
    }
}

int main(int argc, char *argv[]) {
    internalATCData atcInternal;

    if (argc == 2 && strcmp(argv[1], "B"))
        atcInternal.isCabA = false;

    ShiraNet::Servers::TcpServer ATCServer(AF_INET, 1337, 10);
    std::thread serverThread(server, &ATCServer);

    ATCData atcData;

    while (true) {
        if (clientData.power || atcInternal.startup == 1) {
            clientData.power = false;
            ATC::startupSequence(atcData, atcInternal, atcReturn, clientData.isCabA);
        }
    }
}