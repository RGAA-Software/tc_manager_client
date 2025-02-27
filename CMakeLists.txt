project(tc_manager_client)

set(SRCS
        mgr_client_sdk.cpp
        mgr_context.cpp
        mgr_device.cpp
        mgr_user.cpp
        mgr_device_operator.cpp
)

add_library(${PROJECT_NAME} ${SRCS})