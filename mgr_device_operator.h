//
// Created by RGAA on 27/02/2025.
//

#ifndef GAMMARAY_MGR_DEVICE_OPERATOR_H
#define GAMMARAY_MGR_DEVICE_OPERATOR_H

#include <memory>
#include <string>
#include "mgr_errors.h"
#include "mgr_client_sdk_param.h"
#include "tc_3rdparty/expt/expected.h"

namespace tc
{

    class MgrDevice;
    class MgrContext;

    class MgrDeviceOperator {
    public:
        explicit MgrDeviceOperator(const std::shared_ptr<MgrContext>& ctx);
        void SetSdkParam(const MgrClientSdkParam& param);
        // create new device
        Result<std::shared_ptr<MgrDevice>, MgrError> RequestNewDevice(const std::string& info);
        // update random password
        Result<std::shared_ptr<MgrDevice>, MgrError> UpdateRandomPwd(const std::string& device_id);
        // update safety password
        Result<std::shared_ptr<MgrDevice>, MgrError> UpdateSafetyPwd(const std::string& device_id, const std::string& safety_pwd_md5);
        // get device
        Result<std::shared_ptr<MgrDevice>, MgrError> QueryDevice(const std::string& device_id);

    private:
        static std::shared_ptr<MgrDevice> ParseJsonAsDevice(const std::string& body);

    private:
        std::shared_ptr<MgrContext> mgr_context_ = nullptr;
        MgrClientSdkParam sdk_param_;
    };

}

#endif //GAMMARAY_MGR_DEVICE_OPERATOR_H
