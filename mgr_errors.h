//
// Created by RGAA on 18/09/2025.
//

#ifndef GAMMARAYPREMIUM_MGR_ERROS_H
#define GAMMARAYPREMIUM_MGR_ERROS_H

namespace tc
{

    enum class MgrError {
        kInvalidHostAddress,
        kParseJsonFailed,

        kInvalidParams = 600,
        kDatabaseError = 601,
        kDeviceNotFound = 602,
        kPasswordInvalid = 603,
        kInvalidAppkey = 604,
        kCreateDeviceFailed = 605,
        kInvalidAuthorization = 606,
    };

}

#endif //GAMMARAYPREMIUM_MGR_ERROS_H
