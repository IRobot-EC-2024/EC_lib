project(EC_lib VERSION 0.1.0 LANGUAGES C)


set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE EC_LIB_SRC
        ${PROJECT_SOURCE_DIR}/device/*.*
        ${PROJECT_SOURCE_DIR}/bsp/*.*
        ${PROJECT_SOURCE_DIR}/Algorithm/*.*
)

add_library(EC_lib STATIC ${EC_LIB_SRC})

target_include_directories(EC_lib
        PUBLIC ${PROJECT_SOURCE_DIR}/device/BMI088
        PUBLIC ${PROJECT_SOURCE_DIR}/device/Buzzer
        PUBLIC ${PROJECT_SOURCE_DIR}/device/Motor
        PUBLIC ${PROJECT_SOURCE_DIR}/device/Motor/DMMotor
        PUBLIC ${PROJECT_SOURCE_DIR}/device/Motor/djiMotor
        PUBLIC ${PROJECT_SOURCE_DIR}/device/Motor/RMDMotor
        PUBLIC ${PROJECT_SOURCE_DIR}/device/Motor/ServoMotor
        PUBLIC ${PROJECT_SOURCE_DIR}/device/referee
        PUBLIC ${PROJECT_SOURCE_DIR}/device/referee/referee_ui
        PUBLIC ${PROJECT_SOURCE_DIR}/device/RM_remote
        PUBLIC ${PROJECT_SOURCE_DIR}/device/ws2812
        PUBLIC ${PROJECT_SOURCE_DIR}/bsp/bsp_can
        PUBLIC ${PROJECT_SOURCE_DIR}/bsp/bsp_delay
        PUBLIC ${PROJECT_SOURCE_DIR}/bsp/bsp_dwt
        PUBLIC ${PROJECT_SOURCE_DIR}/bsp/bsp_gpio
        PUBLIC ${PROJECT_SOURCE_DIR}/bsp/bsp_monitor
        PUBLIC ${PROJECT_SOURCE_DIR}/bsp/bsp_pwm
        PUBLIC ${PROJECT_SOURCE_DIR}/bsp/bsp_spi
        PUBLIC ${PROJECT_SOURCE_DIR}/bsp/bsp_timer
        PUBLIC ${PROJECT_SOURCE_DIR}/bsp/bsp_uart
        PUBLIC ${PROJECT_SOURCE_DIR}/Config
        PUBLIC ${PROJECT_SOURCE_DIR}/Algorithm
        PUBLIC ${PROJECT_SOURCE_DIR}/Algorithm/crc
        PUBLIC ${PROJECT_SOURCE_DIR}/Algorithm/FIFO
        PUBLIC ${PROJECT_SOURCE_DIR}/Algorithm/KalmamFilter
        PUBLIC ${PROJECT_SOURCE_DIR}/Algorithm/Mahony
        PUBLIC ${PROJECT_SOURCE_DIR}/Algorithm/PID
        PUBLIC ${PROJECT_SOURCE_DIR}/Algorithm/TD
)