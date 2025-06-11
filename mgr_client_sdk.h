//
// Created by RGAA on 27/02/2025.
//

#ifndef GAMMARAY_MGR_CLIENT_SDK_H
#define GAMMARAY_MGR_CLIENT_SDK_H

#include <memory>
#include "mgr_client_sdk_param.h"
#include "tc_common_new/message_notifier.h"

namespace tc
{

    class MgrContext;
    class MgrDevice;
    class MgrDeviceOperator;

    // MgrClientSdk
    class MgrClientSdk {
    public:
        explicit MgrClientSdk(const std::shared_ptr<MessageNotifier>& notifier);
        void SetSdkParam(const MgrClientSdkParam& param);

        std::shared_ptr<MgrDeviceOperator> GetDeviceOperator();
        [[nodiscard]] bool IsServerConfigured() const;

    private:
        std::shared_ptr<MgrContext> mgr_context_ = nullptr;
        MgrClientSdkParam sdk_param_;
        std::shared_ptr<MgrDeviceOperator> device_opt_ = nullptr;
    };

}

#endif //GAMMARAY_MGR_CLIENT_SDK_H
