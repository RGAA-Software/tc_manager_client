//
// Created by RGAA on 27/02/2025.
//

#ifndef GAMMARAY_MGR_APIS_H
#define GAMMARAY_MGR_APIS_H

#include <string>

namespace tc
{

    // /api/v1/device/control
    const std::string kSpvrDeviceControl = "/api/v1/device/control";

    // create new device
    const std::string kApiRequestNewDevice = kSpvrDeviceControl + "/create/new/device";

    // update random password
    const std::string kApiUpdateRandomPwd = kSpvrDeviceControl + "/update/random/pwd";

    // update safety password
    const std::string kApiUpdateSafetyPwd = kSpvrDeviceControl + "/update/safety/pwd";

    // get device by id
    const std::string kApiQueryDeviceById = kSpvrDeviceControl + "/query/device/by/id";

}

#endif //GAMMARAY_MGR_APIS_H
