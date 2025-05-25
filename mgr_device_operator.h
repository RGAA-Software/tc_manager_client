//
// Created by RGAA on 27/02/2025.
//

#ifndef GAMMARAY_MGR_DEVICE_OPERATOR_H
#define GAMMARAY_MGR_DEVICE_OPERATOR_H

#include <memory>
#include <string>
#include "mgr_client_sdk_param.h"

namespace tc
{

    class MgrDevice;
    class MgrContext;

    class MgrDeviceOperator {
    public:
        explicit MgrDeviceOperator(const std::shared_ptr<MgrContext>& ctx);
        void SetSdkParam(const MgrClientSdkParam& param);
        // device
        std::shared_ptr<MgrDevice> RequestNewDevice(const std::string& info);
        //
        std::shared_ptr<MgrDevice> RefreshRandomPwd(const std::string& device_id);

    private:
        std::shared_ptr<MgrContext> mgr_context_ = nullptr;
        MgrClientSdkParam sdk_param_;
    };

}

#endif //GAMMARAY_MGR_DEVICE_OPERATOR_H
