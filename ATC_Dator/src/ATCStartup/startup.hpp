#pragma once

#include "ATCData.hpp"

namespace ATC {

namespace Startup {
extern int ms;
extern void errors(ATCData &data, internalATCData &internalData, ATCReturnData &returnData);
} // namespace Startup

extern void startupSequence(ATCData &data, internalATCData &internalData, ATCReturnData &returnData);

} // namespace ATC