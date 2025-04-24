//
// Created by RGAA on 27/02/2025.
//

#include "mgr_device_operator.h"
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
#include "tc_common_new/uuid.h"

using namespace nlohmann;

namespace tc
{

    MgrDeviceOperator::MgrDeviceOperator(const std::shared_ptr<MgrContext>& ctx) {
        mgr_context_ = ctx;
    }

    void MgrDeviceOperator::SetSdkParam(const MgrClientSdkParam& param) {
        sdk_param_ = param;
    }

    std::shared_ptr<MgrDevice> MgrDeviceOperator::RequestNewDevice(const std::string& info) {
        if (sdk_param_.host_.empty()) {
            LOGE("RequestNewDevice error, host is empty.");
            return nullptr;
        }

        std::string hw_info;
        if (info.empty()) {
            auto hardware_desc = Hardware::Instance()->GetHardwareDescription();
            auto et_info = IPUtil::ScanIPs();
            std::string mac_address;
            for (auto &item: et_info) {
                if (!item.mac_address_.empty() && mac_address.find(item.mac_address_) != std::string::npos) {
                    continue;
                }
                mac_address = mac_address.append(item.mac_address_);
            }
            if (hardware_desc.empty()) {
                LOGW("Hardware desc is empty! Can't request new device!");
            }
            hw_info = hardware_desc + Base64::Base64Encode(mac_address);
        }
        else {
            hw_info = info;
        }

        // SHIT!
        if (hw_info.empty()) {
            hw_info = GetUUID();
        }

        auto client = HttpClient::Make(std::format("{}:{}", sdk_param_.host_, sdk_param_.port_), kApiRequestNewDevice);
        auto resp = client->Post({
#ifdef WIN32
            {"platform", "windows"},
#else
            {"platform", "android"},
#endif
            {"hw_info", hw_info},
        });
        if (resp.status != 200 || resp.body.empty()) {
            LOGE("Request new device failed.");
            return nullptr;
        }

        try {
            auto obj = json::parse(resp.body);
            auto device_id = obj["data"]["device_id"].get<std::string>();
            auto random_pwd = obj["data"]["random_pwd"].get<std::string>();
            LOGI("RequestNewDevice: {} => {}", device_id, random_pwd);
            auto device = std::make_shared<MgrDevice>();
            device->device_id_ = device_id;
            device->random_pwd_ = random_pwd;
            return device;
        } catch(std::exception& e) {
            LOGE("RequestNewDevice failed: {}, message: {}", e.what(), resp.body);
            return nullptr;
        }
    }

}