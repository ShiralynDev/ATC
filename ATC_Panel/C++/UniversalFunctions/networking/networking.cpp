#include "networking.hpp"

#include <ShiraNet.hpp>
#include <iostream>

std::optional<ATCReturnData> ATCNetworking::getATCData(ShiraNet::Sockets::TcpSocket &socket) {
    try {
        ShiraNet::NetworkData::Message message = socket.receiveMessage(); // note this is blocking which is good in this case
        if (message.payloadSize == 0)
            return std::nullopt;
        ShiraNet::NetworkData::DataField<ATCReturnData> data;
        message.payloadToDataField(data);
        return data.data;
    } catch (...) {
        return std::nullopt;
    }
}

void ATCNetworking::toggleATCPower(bool state, ShiraNet::Sockets::TcpSocket &socket) {
    try {
        ShiraNet::NetworkData::DataField<bool> data;
        data.data = state;

        ShiraNet::NetworkData::Message message(1, data);
        socket.send(message);
    } catch (...) {
        std::cout << "Failed to send toggelATCPower message\n";
    }
}