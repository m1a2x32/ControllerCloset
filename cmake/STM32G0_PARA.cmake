set(CPU_PARAMETERS ${CPU_PARAMETERS}
    -mthumb
    -mcpu=cortex-m0plus
    -mfloat-abi=soft
)

set(compiler_define ${compiler_define}
    "STM32G070xx"
)

