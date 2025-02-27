//
// Created by RGAA on 27/02/2025.
//

#include "mgr_client_sdk.h"
#include "mgr_context.h"
#include "mgr_apis.h"
#include "mgr_device.h"
#include "json/json.hpp"
#include "tc_common_new/log.h"
#include "tc_common_new/thread.h"
#include "tc_common_new/message_notifier.h"
#include "tc_common_new/http_client.h"
#include "tc_common_new/hardware.h"
#include "tc_common_new/ip_util.h"
#include "tc_common_new/base64.h"
#include "mgr_device_operator.h"

using namespace nlohmann;

namespace tc
{

    MgrClientSdk::MgrClientSdk(const std::shared_ptr<MessageNotifier>& notifier) {
        mgr_context_ = std::make_shared<MgrContext>(notifier);
        device_opt_ = std::make_shared<MgrDeviceOperator>(mgr_context_);
    }

    void MgrClientSdk::SetSdkParam(const MgrClientSdkParam& param) {
        sdk_param_ = param;
        device_opt_->SetSdkParam(param);
    }

    std::shared_ptr<MgrDeviceOperator> MgrClientSdk::GetDeviceOperator() {
        return device_opt_;
    }

}