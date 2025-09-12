//
// Created by RGAA on 27/02/2025.
//

#ifndef GAMMARAY_MGR_CLIENT_SDK_PARAM_H
#define GAMMARAY_MGR_CLIENT_SDK_PARAM_H

#include <string>

namespace tc
{
    // MgrClientSdkParam
    class MgrClientSdkParam {
    public:
        std::string host_;
        int port_{0};
        bool ssl_ = false;
        std::string appkey_;
    };


}

#endif //GAMMARAY_MGR_CLIENT_SDK_PARAM_H
