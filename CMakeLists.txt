cmake_minimum_required(VERSION 3.22)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
message("Build type: "              ${CMAKE_BUILD_TYPE})

# ------------------- Setup -------------------
# C version
set(CMAKE_C_STANDARD                17)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
# C++ version
set(CMAKE_CXX_STANDARD              17)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS   ON)

# Define .cmake module for toolchain compile flags that does holds true for all ARM projects
set(CMAKE_TOOLCHAIN_FILE            gcc-arm-none-eabi)# This path is defined in the list() function above

# ------------------- PROJECT SETUP -------------------
project("ClosetController")
enable_language(C CXX ASM)

# ------------------- Linker File ------------------- 
set(linker_script_SRC               ${CMAKE_CURRENT_SOURCE_DIR}/STM32G070RBTx_FLASH.ld)

# -------------------  MCU Configs ------------------- 
# include(MAKE NEW PARA FOR NEW MCU CONF)
include(STM32G0_PARA)

# ------------------- Driver Setup -------------------
set(CMSIS_DIR drivers/CMSIS)
set(HAL_DIR drivers/HAL)
set(SRC_DIR src)


# ------------------- Includes Setup -------------------
set(include_list ${include_list}
    ${CMSIS_DIR}/Include
    ${CMSIS_DIR}/Device/ST/STM32G0xx/Include
    ${HAL_DIR}/GPIO
	${HAL_DIR}/USART
	${SRC_DIR}
)

# ------------------- LIST SOURCE FILES HERE -------------------
set (source_list
	${CMSIS_DIR}/Startup/startup_stm32g070xx.s
	
	${HAL_DIR}/GPIO/gpio.cpp
	${HAL_DIR}/USART/usart.cpp
	
	${SRC_DIR}/main.c
	${SRC_DIR}/syscalls.c
	${SRC_DIR}/sysmem.c
	${SRC_DIR}/system_stm32g0xx.c
	${SRC_DIR}/soil_sensor/communication.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${source_list})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${include_list})
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE ${compiler_define})

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
