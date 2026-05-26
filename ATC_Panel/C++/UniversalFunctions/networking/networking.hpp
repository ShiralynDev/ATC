#pragma once

#include "../../../../ATC_Dator/src/ATCData.hpp"

#include <ShiraNet.hpp>
#include <optional>

namespace ATCNetworking {

std::optional<ATCReturnData> getATCData(ShiraNet::Sockets::TcpSocket &socket);
void toggleATCPower(bool state, ShiraNet::Sockets::TcpSocket &socket);

}