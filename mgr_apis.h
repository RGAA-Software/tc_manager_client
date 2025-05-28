//
// Created by RGAA on 27/02/2025.
//

#ifndef GAMMARAY_MGR_APIS_H
#define GAMMARAY_MGR_APIS_H

#include <string>

namespace tc
{

    // create new device
    const std::string kApiRequestNewDevice = "/create/new/device";
    // update random password
    const std::string kApiUpdateRandomPwd = "/update/random/pwd";
    // update safety password
    const std::string kApiUpdateSafetyPwd = "/update/safety/pwd";

}

#endif //GAMMARAY_MGR_APIS_H
