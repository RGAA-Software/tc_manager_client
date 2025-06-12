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
        // create new device
        std::shared_ptr<MgrDevice> RequestNewDevice(const std::string& info);
        // update random password
        std::shared_ptr<MgrDevice> UpdateRandomPwd(const std::string& device_id);
        // update safety password
        std::shared_ptr<MgrDevice> UpdateSafetyPwd(const std::string& device_id, const std::string& safety_pwd_md5);
        // get device
        std::shared_ptr<MgrDevice> QueryDevice(const std::string& device_id);

    private:
        static std::shared_ptr<MgrDevice> ParseJsonAsDevice(const std::string& body);

    private:
        std::shared_ptr<MgrContext> mgr_context_ = nullptr;
        MgrClientSdkParam sdk_param_;
    };

}

#endif //GAMMARAY_MGR_DEVICE_OPERATOR_H
