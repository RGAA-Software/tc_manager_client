//
// Created by RGAA on 27/02/2025.
//

#include "mgr_context.h"

namespace tc
{

    MgrContext::MgrContext(const std::shared_ptr<MessageNotifier>& notifier) {
        msg_notifier_ = notifier;
    }

    std::shared_ptr<MessageListener> MgrContext::CreateMessageListener() {
        return msg_notifier_->CreateListener();
    }

}