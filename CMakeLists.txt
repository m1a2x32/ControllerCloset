cmake_minimum_required(VERSION 3.22)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
message("Build type: "              ${CMAKE_BUILD_TYPE})

# ------------------- Setup -------------------
# C version
set(CMAKE_C_STANDARD                17)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
message("C Standard: ${CMAKE_C_STANDARD}")

# C++ version
set(CMAKE_CXX_STANDARD              20)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS   ON)
message("C++ Standard: ${CMAKE_CXX_STANDARD}")

# Define .cmake module for toolchain compile flags that does holds true for all ARM projects
set(CMAKE_TOOLCHAIN_FILE            gcc-arm-none-eabi)

# ------------------- PROJECT SETUP -------------------
project("ClosetController")
enable_language(C CXX ASM)

set(BOARD_DIR 						${CMAKE_CURRENT_SOURCE_DIR}/boards)
set(LIBS_DIR 						${CMAKE_CURRENT_SOURCE_DIR}/libs)
set(HAL_DIR 						${CMAKE_CURRENT_SOURCE_DIR}/libs/HAL)
set(SRC_DIR 						${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(${BOARD_DIR}/stm32g0x/STM32CubeG0)
# ------------------- MCU Config ------------------- 
set(linker_script_SRC               ${BOARD_DIR}/stm32g0x/STM32G070RBTx_FLASH.ld)
include(STM32G0_PARA)

# ------------------- LIST SOURCE -------------------
file(GLOB source_list
	${HAL_DIR}/GPIO/*.cpp
    ${HAL_DIR}/USART/*.cpp
	${LIBS_DIR}/RGBLed/*.cpp
	${LIBS_DIR}/Modbus/*.cpp
    ${SRC_DIR}/*.c
	${SRC_DIR}/*.cpp
	${SRC_DIR}/Application/*.cpp
)

add_executable(${CMAKE_PROJECT_NAME} 
	${source_list}
	${BOARD_DIR}/stm32g0x/startup_stm32g070xx.s
)

# ------------------- Includes Setup -------------------
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE 
	${HAL_DIR}/GPIO
	${HAL_DIR}/USART
	${LIBS_DIR}/Modbus
	${LIBS_DIR}/RGBLed
	${SRC_DIR}
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE 
	STM32CubeG0
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE 
	${compiler_define}
)

# Compiler options
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
	${CPU_PARAMETERS}
	-Wall
	-Wpedantic
	-Wno-unused-parameter
	-Wno-unused-function
	-Wno-unused-variable		
)

# Linker options
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
	-g
	-T${linker_script_SRC}
	${CPU_PARAMETERS}
	-Wl,-Map=${CMAKE_PROJECT_NAME}.map
	--specs=nosys.specs
	#-u _printf_float                # STDIO float formatting support
	-Wl,--start-group
	-lc
	-lm
	-lstdc++
	-lsupc++
	-Wl,--end-group
	-Wl,--print-memory-usage
)

# -------------- POST BUILD --------------

# Execute print size
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
)

# Convert output to hex and binary
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.hex
)

# Convert to bin file
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.bin
)

set(CMAKE_C_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")