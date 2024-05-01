project(EC_lib VERSION 0.1.0 LANGUAGES C)


set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE EC_LIB_SRC
        ${PROJECT_SOURCE_DIR}/device/*.*
        ${PROJECT_SOURCE_DIR}/bsp/*.*
        ${PROJECT_SOURCE_DIR}/algorithm/*.*
)

add_library(EC_lib STATIC ${EC_LIB_SRC})

target_link_libraries(EC_lib
        ${PROJECT_SOURCE_DIR}/algorithm/libarm_cortexM7lfdp_math.a)

target_include_directories(EC_lib
        PUBLIC ${PROJECT_SOURCE_DIR}/bsp
        PUBLIC ${PROJECT_SOURCE_DIR}/config
        PUBLIC ${PROJECT_SOURCE_DIR}/algorithm
        PUBLIC ${PROJECT_SOURCE_DIR}/device
        PUBLIC ${PROJECT_SOURCE_DIR}/device/BMI088
        PUBLIC ${PROJECT_SOURCE_DIR}/device/Buzzer
        PUBLIC ${PROJECT_SOURCE_DIR}/device/Motor
        PUBLIC ${PROJECT_SOURCE_DIR}/device/referee
        PUBLIC ${PROJECT_SOURCE_DIR}/device/referee/referee_ui
        PUBLIC ${PROJECT_SOURCE_DIR}/device/RM_remote
        PUBLIC ${PROJECT_SOURCE_DIR}/device/ws2812
)