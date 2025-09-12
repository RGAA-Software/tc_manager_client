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
            hw_info = Base64::Base64Encode(hardware_desc + mac_address);
        }
        else {
            hw_info = info;
        }

        // SHIT!
        if (hw_info.empty()) {
            hw_info = GetUUID();
        }

        auto client = HttpClient::MakeSSL(sdk_param_.host_, sdk_param_.port_, kApiRequestNewDevice);
        auto resp = client->Post({
#ifdef WIN32
            {"platform", "windows"},
#else
            {"platform", "android"},
#endif
            {"hw_info", hw_info},
            {"appkey", sdk_param_.appkey_}
        });

        // wireshark: http and ip.addr == 39.91.109.105 and tcp.port == 40301
        if (resp.status != 200 || resp.body.empty()) {
            LOGE("Request new device failed, code: {}", resp.status);
            return nullptr;
        }

        return ParseJsonAsDevice(resp.body);
    }

    std::shared_ptr<MgrDevice> MgrDeviceOperator::UpdateRandomPwd(const std::string& target_device_id) {
        if (sdk_param_.host_.empty()) {
            LOGE("UpdateRandomPwd error, host is empty.");
            return nullptr;
        }
        auto client = HttpClient::MakeSSL(sdk_param_.host_, sdk_param_.port_, kApiUpdateRandomPwd);
        auto resp = client->Post({
                {"device_id", target_device_id},
                {"appkey", sdk_param_.appkey_}
            });
        if (resp.status != 200 || resp.body.empty()) {
            LOGE("UpdateRandomPwd failed.");
            return nullptr;
        }

        return ParseJsonAsDevice(resp.body);
    }

    std::shared_ptr<MgrDevice> MgrDeviceOperator::UpdateSafetyPwd(const std::string& target_device_id, const std::string& safety_pwd_md5) {
        if (sdk_param_.host_.empty()) {
            LOGE("UpdateSafetyPwd error, host is empty.");
            return nullptr;
        }
        auto client = HttpClient::MakeSSL(sdk_param_.host_, sdk_param_.port_, kApiUpdateSafetyPwd, 2000);
        auto resp = client->Post({
             {"device_id", target_device_id},
             {"safety_pwd_md5", safety_pwd_md5},
             {"appkey", sdk_param_.appkey_}
        });
        if (resp.status != 200 || resp.body.empty()) {
            LOGE("UpdateSafetyPwd failed.");
            return nullptr;
        }

        return ParseJsonAsDevice(resp.body);
    }

    std::shared_ptr<MgrDevice> MgrDeviceOperator::QueryDevice(const std::string& device_id) {
        if (sdk_param_.host_.empty()) {
            LOGE("RequestNewDevice error, host is empty.");
            return nullptr;
        }
        auto client = HttpClient::MakeSSL(sdk_param_.host_, sdk_param_.port_, kApiQueryDeviceById);
        auto resp = client->Request({
            {"device_id", device_id},
            {"appkey", sdk_param_.appkey_}
        });
        if (resp.status != 200 || resp.body.empty()) {
            LOGE("GetDevice failed: {}", device_id);
            return nullptr;
        }

        return ParseJsonAsDevice(resp.body);
    }

    std::shared_ptr<MgrDevice> MgrDeviceOperator::ParseJsonAsDevice(const std::string& body) {
        try {
            auto obj = json::parse(body);
            auto resp_device_id = obj["data"]["device_id"].get<std::string>();
            auto random_pwd_md5 = obj["data"]["random_pwd_md5"].get<std::string>();
            auto gen_random_pwd = obj["data"]["gen_random_pwd"].get<std::string>();
            auto safety_pwd_md5 = obj["data"]["safety_pwd_md5"].get<std::string>();
            auto used_time = obj["data"]["used_time"].get<int64_t>();
            auto created_timestamp = obj["data"]["created_timestamp"].get<int64_t>();
            auto last_update_timestamp = obj["data"]["last_update_timestamp"].get<int64_t>();
            //LOGI("PaserJsonAsDevice: {} => RPWD: {}, SPWD: {}", resp_device_id, random_pwd_md5, safety_pwd_md5);

            auto device = std::make_shared<MgrDevice>();
            device->device_id_ = resp_device_id;
            device->gen_random_pwd_ = gen_random_pwd;
            device->random_pwd_md5_ = random_pwd_md5;
            device->safety_pwd_md5_ = safety_pwd_md5;
            device->used_time_ = used_time;
            device->created_timestamp_ = created_timestamp;
            device->updated_timestamp_ = last_update_timestamp;
            return device;
        } catch(std::exception& e) {
            LOGE("RequestNewDevice failed: {}, message: {}", e.what(), body);
            return nullptr;
        }
    }
}