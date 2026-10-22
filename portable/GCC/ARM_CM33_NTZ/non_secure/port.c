/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Copyright 2024-2026 Arm Limited and/or its affiliates <open-source-office@arm.com>
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers. That should only be done when
 * task.h is included from an application file. */
#define MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#അന്തര്ഭാവ "FreeRTOS.h"
#അന്തര്ഭാവ "task.h"

/* MPU includes. */
#അന്തര്ഭാവ "mpu_wrappers.h"
#അന്തര്ഭാവ "mpu_syscall_numbers.h"

/* Portasm includes. */
#അന്തര്ഭാവ "portasm.h"

#എങ്കിൽ ( configENABLE_TRUSTZONE == 1 )
    /* Secure components includes. */
    #അന്തര്ഭാവ "secure_context.h"
    #അന്തര്ഭാവ "secure_init.h"
#endif /* configENABLE_TRUSTZONE */

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/**
 * The FreeRTOS Cortex M33 port can be configured to run on the Secure Side only
 * i.e. the processor boots as secure and never jumps to the non-secure side.
 * The Trust Zone support in the port must be disabled in order to run FreeRTOS
 * on the secure side. The following are the valid configuration settings:
 *
 * 1. Run FreeRTOS on the Secure Side:
 *    configRUN_FREERTOS_SECURE_ONLY = 1 and configENABLE_TRUSTZONE = 0
 *
 * 2. Run FreeRTOS on the Non-Secure Side with Secure Side function call support:
 *    configRUN_FREERTOS_SECURE_ONLY = 0 and configENABLE_TRUSTZONE = 1
 *
 * 3. Run FreeRTOS on the Non-Secure Side only i.e. no Secure Side function call support:
 *    configRUN_FREERTOS_SECURE_ONLY = 0 and configENABLE_TRUSTZONE = 0
 */
#എങ്കിൽ ( ( configRUN_FREERTOS_SECURE_ONLY == 1 ) && ( configENABLE_TRUSTZONE == 1 ) )
    #error TrustZone needs to be disabled in order to run FreeRTOS on the Secure Side.
#endif

/**
 * Cortex-M23 does not have non-secure PSPLIM. We should use PSPLIM on Cortex-M23
 * only when FreeRTOS runs on secure side.
 */
#എങ്കിൽ ( ( portHAS_ARMV8M_MAIN_EXTENSION == 0 ) && ( configRUN_FREERTOS_SECURE_ONLY == 0 ) )
    #define portUSE_PSPLIM_REGISTER    0
#അല്ലെങ്കിൽ
    #define portUSE_PSPLIM_REGISTER    1
#endif
/*-----------------------------------------------------------*/

/**
 * @brief Prototype of all Interrupt Service Routines (ISRs).
 */
തരനിർവചനം ശൂന്യം ( * portISR_t )( ശൂന്യം );
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the NVIC.
 */
#define portNVIC_SYSTICK_CTRL_REG             ( *( ( അസ്ഥിര uint32_t * ) 0xe000e010 ) )
#define portNVIC_SYSTICK_LOAD_REG             ( *( ( അസ്ഥിര uint32_t * ) 0xe000e014 ) )
#define port_NVIC_SYSTICK_CURRENT_മൂല്യം_REG    ( *( ( അസ്ഥിര uint32_t * ) 0xe000e018 ) )
#define portNVIC_SHPR3_REG                    ( *( ( അസ്ഥിര uint32_t * ) 0xe000ed20 ) )
#define portNVIC_SYSTICK_ENABLE_BIT           ( 1UL << 0UL )
#define portNVIC_SYSTICK_INT_BIT              ( 1UL << 1UL )
#define portNVIC_SYSTICK_CLK_BIT              ( 1UL << 2UL )
#define port_NVIC_SYSTICK_എണ്ണം_FLAG_BIT       ( 1UL << 16UL )
#define portNVIC_PEND_SYSTICK_CLEAR_BIT       ( 1UL << 25UL )
#define portNVIC_PEND_SYSTICK_SET_BIT         ( 1UL << 26UL )
#define portMIN_INTERRUPT_PRIORITY            ( 255UL )
#define portNVIC_PENDSV_PRI                   ( portMIN_INTERRUPT_PRIORITY << 16UL )
#define portNVIC_SYSTICK_PRI                  ( portMIN_INTERRUPT_PRIORITY << 24UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the SCB.
 */
#define portSCB_VTOR_REG                      ( *( ( portISR_t ** ) 0xe000ed08 ) )
#define portSCB_SYS_HANDLER_CTRL_STATE_REG    ( *( ( അസ്ഥിര uint32_t * ) 0xe000ed24 ) )
#define portSCB_MEM_FAULT_ENABLE_BIT          ( 1UL << 16UL )
#define portSCB_USG_FAULT_ENABLE_BIT          ( 1UL << 18UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants used to check the installation of the FreeRTOS interrupt handlers.
 */
#define portVECTOR_INDEX_SVC       ( 11 )
#define portVECTOR_INDEX_PENDSV    ( 14 )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to check the validity of an interrupt priority.
 */
#define portNVIC_SHPR2_REG                 ( *( ( അസ്ഥിര uint32_t * ) 0xE000ED1C ) )
#define port_FIRST_USER_INTERRUPT_സംഖ്യ    ( 16 )
#define portNVIC_IP_REGISTERS_OFFSET_16    ( 0xE000E3F0 )
#define portAIRCR_REG                      ( *( ( അസ്ഥിര uint32_t * ) 0xE000ED0C ) )
#define port_മുകൾ_BIT_OF_BYTE                ( ( uint8_t ) 0x80 )
#define portMAX_PRIGROUP_BITS              ( ( uint8_t ) 7 )
#define portPRIORITY_GROUP_MASK            ( 0x07UL << 8UL )
#define portPRIGROUP_SHIFT                 ( 8UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants used during system call enter and exit.
 */
#define port_PSR_അട്ടി_PADDING_MASK              ( 1UL << 9UL )
#define port_EXC_RETURN_അട്ടി_FRAME_TYPE_MASK    ( 1UL << 4UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the FPU.
 */
#define portCPACR               ( ( അസ്ഥിര uint32_t * ) 0xe000ed88 ) /* Coprocessor Access Control Register. */
#define port_CPACR_CP10_മൂല്യം    ( 3UL )
#define port_CPACR_CP11_മൂല്യം    port_CPACR_CP10_മൂല്യം
#define portCPACR_CP10_POS      ( 20UL )
#define portCPACR_CP11_POS      ( 22UL )

#define portFPCCR               ( ( അസ്ഥിര uint32_t * ) 0xe000ef34 ) /* Floating Point Context Control Register. */
#define portFPCCR_ASPEN_POS     ( 31UL )
#define portFPCCR_ASPEN_MASK    ( 1UL << portFPCCR_ASPEN_POS )
#define portFPCCR_LSPEN_POS     ( 30UL )
#define portFPCCR_LSPEN_MASK    ( 1UL << portFPCCR_LSPEN_POS )
/*-----------------------------------------------------------*/

/**
 * @brief Offsets in the stack to the parameters when inside the SVC handler.
 */
#define portOFFSET_TO_LR     ( 5 )
#define portOFFSET_TO_PC     ( 6 )
#define portOFFSET_TO_PSR    ( 7 )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the MPU.
 */
#define portMPU_TYPE_REG                        ( *( ( അസ്ഥിര uint32_t * ) 0xe000ed90 ) )
#define portMPU_CTRL_REG                        ( *( ( അസ്ഥിര uint32_t * ) 0xe000ed94 ) )
#define portMPU_RNR_REG                         ( *( ( അസ്ഥിര uint32_t * ) 0xe000ed98 ) )

#define portMPU_RBAR_REG                        ( *( ( അസ്ഥിര uint32_t * ) 0xe000ed9c ) )
#define portMPU_RLAR_REG                        ( *( ( അസ്ഥിര uint32_t * ) 0xe000eda0 ) )

#define portMPU_RBAR_A1_REG                     ( *( ( അസ്ഥിര uint32_t * ) 0xe000eda4 ) )
#define portMPU_RLAR_A1_REG                     ( *( ( അസ്ഥിര uint32_t * ) 0xe000eda8 ) )

#define portMPU_RBAR_A2_REG                     ( *( ( അസ്ഥിര uint32_t * ) 0xe000edac ) )
#define portMPU_RLAR_A2_REG                     ( *( ( അസ്ഥിര uint32_t * ) 0xe000edb0 ) )

#define portMPU_RBAR_A3_REG                     ( *( ( അസ്ഥിര uint32_t * ) 0xe000edb4 ) )
#define portMPU_RLAR_A3_REG                     ( *( ( അസ്ഥിര uint32_t * ) 0xe000edb8 ) )

#define portMPU_MAIR0_REG                       ( *( ( അസ്ഥിര uint32_t * ) 0xe000edc0 ) )
#define portMPU_MAIR1_REG                       ( *( ( അസ്ഥിര uint32_t * ) 0xe000edc4 ) )

#define portMPU_RBAR_ADDRESS_MASK               ( 0xffffffe0 ) /* Must be 32-byte aligned. */
#define portMPU_RLAR_ADDRESS_MASK               ( 0xffffffe0 ) /* Must be 32-byte aligned. */

#define portMPU_RBAR_ACCESS_PERMISSIONS_MASK    ( 3UL << 1UL )

#define portMPU_MAIR_ATTR0_POS                  ( 0UL )
#define portMPU_MAIR_ATTR0_MASK                 ( 0x000000ff )

#define portMPU_MAIR_ATTR1_POS                  ( 8UL )
#define portMPU_MAIR_ATTR1_MASK                 ( 0x0000ff00 )

#define portMPU_MAIR_ATTR2_POS                  ( 16UL )
#define portMPU_MAIR_ATTR2_MASK                 ( 0x00ff0000 )

#define portMPU_MAIR_ATTR3_POS                  ( 24UL )
#define portMPU_MAIR_ATTR3_MASK                 ( 0xff000000 )

#define portMPU_MAIR_ATTR4_POS                  ( 0UL )
#define portMPU_MAIR_ATTR4_MASK                 ( 0x000000ff )

#define portMPU_MAIR_ATTR5_POS                  ( 8UL )
#define portMPU_MAIR_ATTR5_MASK                 ( 0x0000ff00 )

#define portMPU_MAIR_ATTR6_POS                  ( 16UL )
#define portMPU_MAIR_ATTR6_MASK                 ( 0x00ff0000 )

#define portMPU_MAIR_ATTR7_POS                  ( 24UL )
#define portMPU_MAIR_ATTR7_MASK                 ( 0xff000000 )

#define portMPU_RLAR_ATTR_INDEX0                ( 0UL << 1UL )
#define portMPU_RLAR_ATTR_INDEX1                ( 1UL << 1UL )
#define portMPU_RLAR_ATTR_INDEX2                ( 2UL << 1UL )
#define portMPU_RLAR_ATTR_INDEX3                ( 3UL << 1UL )
#define portMPU_RLAR_ATTR_INDEX4                ( 4UL << 1UL )
#define portMPU_RLAR_ATTR_INDEX5                ( 5UL << 1UL )
#define portMPU_RLAR_ATTR_INDEX6                ( 6UL << 1UL )
#define portMPU_RLAR_ATTR_INDEX7                ( 7UL << 1UL )

#define portMPU_RLAR_REGION_ENABLE              ( 1UL )

#എങ്കിൽ ( portARMV8M_MINOR_VERSION >= 1 )

    /* Enable Privileged eXecute Never MPU attribute for the selected memory
     * region. */
    #define portMPU_RLAR_PRIVILEGED_EXECUTE_NEVER    ( 1UL << 4UL )
#endif /* portARMV8M_MINOR_VERSION >= 1 */

/* Enable privileged access to unmapped region. */
#define portMPU_PRIV_BACKGROUND_ENABLE_BIT    ( 1UL << 2UL )

/* Enable MPU. */
#define portMPU_ENABLE_BIT                    ( 1UL << 0UL )

/* Extract first address of the MPU region as encoded in the
 * RBAR (Region Base Address Register) value. */
#define portEXTRACT_FIRST_ADDRESS_FROM_RBAR( rbar ) \
    ( ( rbar ) & portMPU_RBAR_ADDRESS_MASK )

/* Extract last address of the MPU region as encoded in the
 * RLAR (Region Limit Address Register) value. */
#define portEXTRACT_LAST_ADDRESS_FROM_RLAR( rlar ) \
    ( ( ( rlar ) & portMPU_RLAR_ADDRESS_MASK ) | ~portMPU_RLAR_ADDRESS_MASK )

/* Does addr lies within [start, end] address range? */
#define portIS_ADDRESS_WITHIN_RANGE( addr, start, end ) \
    ( ( ( addr ) >= ( start ) ) && ( ( addr ) <= ( end ) ) )

/* Is the access request satisfied by the available permissions? */
#define portIS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#define portUINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#define portADD_UINT32_WILL_OVERFLOW( a, b )    ( ( a ) > ( portUINT32_MAX - ( b ) ) )
/*-----------------------------------------------------------*/

/**
 * @brief The maximum 24-bit number.
 *
 * It is needed because the systick is a 24-bit counter.
 */
#define port_MAX_24_BIT_സംഖ്യ       ( 0xffffffUL )

/**
 * @brief A fiddle factor to estimate the number of SysTick counts that would
 * have occurred while the SysTick counter is stopped during tickless idle
 * calculations.
 */
#define portMISSED_COUNTS_FACTOR    ( 94UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to set up the initial stack.
 */
#define portINITIAL_XPSR    ( 0x01000000 )

#എങ്കിൽ ( configRUN_FREERTOS_SECURE_ONLY == 1 )

    /**
     * @brief Initial EXC_RETURN value.
     *
     *     FF         FF         FF         FD
     * 1111 1111  1111 1111  1111 1111  1111 1101
     *
     * Bit[6] - 1 --> The exception was taken from the Secure state.
     * Bit[5] - 1 --> Do not skip stacking of additional state context.
     * Bit[4] - 1 --> The PE did not allocate space on the stack for FP context.
     * Bit[3] - 1 --> Return to the Thread mode.
     * Bit[2] - 1 --> Restore registers from the process stack.
     * Bit[1] - 0 --> Reserved, 0.
     * Bit[0] - 1 --> The exception was taken to the Secure state.
     */
    #define portINITIAL_EXC_RETURN    ( 0xfffffffd )
#അല്ലെങ്കിൽ

    /**
     * @brief Initial EXC_RETURN value.
     *
     *     FF         FF         FF         BC
     * 1111 1111  1111 1111  1111 1111  1011 1100
     *
     * Bit[6] - 0 --> The exception was taken from the Non-Secure state.
     * Bit[5] - 1 --> Do not skip stacking of additional state context.
     * Bit[4] - 1 --> The PE did not allocate space on the stack for FP context.
     * Bit[3] - 1 --> Return to the Thread mode.
     * Bit[2] - 1 --> Restore registers from the process stack.
     * Bit[1] - 0 --> Reserved, 0.
     * Bit[0] - 0 --> The exception was taken to the Non-Secure state.
     */
    #define portINITIAL_EXC_RETURN    ( 0xffffffbc )
#endif /* configRUN_FREERTOS_SECURE_ONLY */

/**
 * @brief CONTROL register privileged bit mask.
 *
 * Bit[0] in CONTROL register tells the privilege:
 *  Bit[0] = 0 ==> The task is privileged.
 *  Bit[0] = 1 ==> The task is not privileged.
 */
#define portCONTROL_PRIVILEGED_MASK         ( 1UL << 0UL )

/**
 * @brief Initial CONTROL register values.
 */
#define portINITIAL_CONTROL_UNPRIVILEGED    ( 0x3 )
#define portINITIAL_CONTROL_PRIVILEGED      ( 0x2 )

/**
 * @brief Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register.
 */
#ifndef configSYSTICK_CLOCK_HZ
    #define configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #define portNVIC_SYSTICK_CLK_BIT_CONFIG    ( portNVIC_SYSTICK_CLK_BIT )
#അല്ലെങ്കിൽ
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #define portNVIC_SYSTICK_CLK_BIT_CONFIG    ( 0 )
#endif

/**
 * @brief Let the user override the pre-loading of the initial LR with the
 * address of prvTaskExitError() in case it messes up unwinding of the stack
 * in the debugger.
 */
#ifdef configTASK_RETURN_ADDRESS
    #define portTASK_RETURN_ADDRESS    configTASK_RETURN_ADDRESS
#അല്ലെങ്കിൽ
    #define portTASK_RETURN_ADDRESS    prvTaskExitError
#endif

/**
 * @brief If portPRELOAD_REGISTERS then registers will be given an initial value
 * when a task is created. This helps in debugging at the cost of code size.
 */
#define portPRELOAD_REGISTERS    1

/**
 * @brief A task is created without a secure context, and must call
 * portALLOCATE_SECURE_CONTEXT() to give itself a secure context before it makes
 * any secure calls.
 */
#define portNO_SECURE_CONTEXT    0

/**
 * @brief Constants required to check and configure PACBTI security feature implementation.
 */
#എങ്കിൽ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )

    #define portID_ISAR5_REG       ( *( ( അസ്ഥിര uint32_t * ) 0xe000ed74 ) )

    #define portCONTROL_UPAC_EN    ( 1UL << 7UL )
    #define portCONTROL_PAC_EN     ( 1UL << 6UL )
    #define portCONTROL_UBTI_EN    ( 1UL << 5UL )
    #define portCONTROL_BTI_EN     ( 1UL << 4UL )

#endif /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Used to catch tasks that attempt to return from their implementing
 * function.
 */
സ്ഥിതം ശൂന്യം prvTaskExitError( ശൂന്യം );

#എങ്കിൽ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Extract MPU region's access permissions from the Region Base Address
     * Register (RBAR) value.
     *
     * @param ulRBARValue RBAR value for the MPU region.
     *
     * @return uint32_t Access permissions.
     */
    സ്ഥിതം uint32_t prvGetRegionAccessPermissions( uint32_t ulRBARValue ) PRIVILEGED_FUNCTION;
#endif /* configENABLE_MPU == 1 && configUSE_MPU_WRAPPERS_V1 == 0 */

#എങ്കിൽ ( configENABLE_MPU == 1 )

    /**
     * @brief Setup the Memory Protection Unit (MPU).
     */
    സ്ഥിതം ശൂന്യം prvSetupMPU( ശൂന്യം ) PRIVILEGED_FUNCTION;
#endif /* configENABLE_MPU */

#എങ്കിൽ ( configENABLE_FPU == 1 )

    /**
     * @brief Setup the Floating Point Unit (FPU).
     */
    സ്ഥിതം ശൂന്യം prvSetupFPU( ശൂന്യം ) PRIVILEGED_FUNCTION;
#endif /* configENABLE_FPU */

#എങ്കിൽ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )

    /**
     * @brief Configures PACBTI features.
     *
     * This function configures the Pointer Authentication, and Branch Target
     * Identification security features as per the user configuration. It returns
     * the value of the special purpose CONTROL register accordingly, and optionally
     * updates the CONTROL register value. Currently, only Cortex-M85 (ARMv8.1-M
     * architecture based) target supports PACBTI security feature.
     *
     * @param xWriteControlRegister Used to control whether the special purpose
     * CONTROL register should be updated or not.
     *
     * @return CONTROL register value according to the configured PACBTI option.
     */
    #എങ്കിൽ ( config_സംഖ്യ_OF_CORES == 1 )
        സ്ഥിതം uint32_t prvConfigurePACBTI( BaseType_t xWriteControlRegister );
    #അല്ലെങ്കിൽ /* #if ( configNUMBER_OF_CORES == 1 ) */
        uint32_t vConfigurePACBTI( BaseType_t xWriteControlRegister );
    #endif /* #if ( configNUMBER_OF_CORES == 1 ) */

#endif /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

/**
 * @brief Setup the timer to generate the tick interrupts.
 *
 * The implementation in this file is weak to allow application writers to
 * change the timer used to generate the tick interrupt.
 */
ശൂന്യം vPortSetupTimerInterrupt( ശൂന്യം ) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether the current execution context is interrupt.
 *
 * @return pdTRUE if the current execution context is interrupt, pdFALSE
 * otherwise.
 */
BaseType_t xPortIsInsideInterrupt( ശൂന്യം );

/**
 * @brief Yield the processor.
 */
ശൂന്യം vPortYield( ശൂന്യം ) PRIVILEGED_FUNCTION;

/**
 * @brief Enter critical section.
 */
ശൂന്യം vPortEnterCritical( ശൂന്യം ) PRIVILEGED_FUNCTION;

/**
 * @brief Exit from critical section.
 */
ശൂന്യം vPortExitCritical( ശൂന്യം ) PRIVILEGED_FUNCTION;

/**
 * @brief SysTick handler.
 */
ശൂന്യം SysTick_Handler( ശൂന്യം ) PRIVILEGED_FUNCTION;

/**
 * @brief C part of SVC handler.
 */
portDONT_DISCARD ശൂന്യം vPortSVCHandler_C( uint32_t * pul_Caller_അട്ടി_Address ) PRIVILEGED_FUNCTION;

#എങ്കിൽ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the system call stack so that upon returning from
     * SVC, the system call stack is used.
     *
     * @param pulTaskStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    ശൂന്യം vSystemCallEnter( uint32_t * pul_Task_അട്ടി,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_സംഖ്യ ) PRIVILEGED_FUNCTION;

#endif /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#എങ്കിൽ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    ശൂന്യം vRequestSystemCallExit( ശൂന്യം ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#endif /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#എങ്കിൽ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param pulSystemCallStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     */
    ശൂന്യം vSystemCallExit( uint32_t * pul_System_Call_അട്ടി,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#endif /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#എങ്കിൽ ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    BaseType_t xPortIsTaskPrivileged( ശൂന്യം ) PRIVILEGED_FUNCTION;

#endif /* configENABLE_MPU == 1 */

#എങ്കിൽ ( config_സംഖ്യ_OF_CORES > 1 )

    /**
     * @brief Platform/Application-defined function that wakes up the secondary cores.
     *
     * @return pdTRUE if the secondary cores were successfully woken up.
     *         pdFALSE otherwise.
     */
    ബാഹ്യ BaseType_t configWAKE_SECONDARY_CORES( ശൂന്യം );

#endif /* #if ( configNUMBER_OF_CORES > 1 ) */

/**
 * @brief Configures interrupt priorities.
 */
ശൂന്യം vPortConfigureInterruptPriorities( ശൂന്യം ) PRIVILEGED_FUNCTION;
/*-----------------------------------------------------------*/

#എങ്കിൽ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief This variable is set to pdTRUE when the scheduler is started.
     */
    PRIVILEGED_DATA സ്ഥിതം BaseType_t xSchedulerRunning = pdFALSE;

#endif /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/**
 * @brief Each task maintains its own interrupt status in the critical nesting
 * variable.
 */
#എങ്കിൽ ( config_സംഖ്യ_OF_CORES == 1 )
    PRIVILEGED_DATA സ്ഥിതം അസ്ഥിര uint32_t ulCriticalNesting = 0UL;
#അല്ലെങ്കിൽ /* #if ( configNUMBER_OF_CORES == 1 ) */
    PRIVILEGED_DATA അസ്ഥിര uint32_t ulCriticalNestings[ config_സംഖ്യ_OF_CORES ] = { 0 };
    /* Flags to check if the secondary cores are ready. */
    PRIVILEGED_DATA അസ്ഥിര uint8_t ucSecondaryCoresReadyFlags[ config_സംഖ്യ_OF_CORES - 1 ] = { 0 };
    /* Flag to indicate that the primary core has completed its initialisation. */
    PRIVILEGED_DATA അസ്ഥിര uint8_t ucPrimaryCoreInitDoneFlag = 0;
 #endif /* #if ( configNUMBER_OF_CORES == 1 ) */

#എങ്കിൽ ( configENABLE_TRUSTZONE == 1 )

    /**
     * @brief Saved as part of the task context to indicate which context the
     * task is using on the secure side.
     */
    PRIVILEGED_DATA portDONT_DISCARD അസ്ഥിര SecureContextHandle_t xSecureContext = portNO_SECURE_CONTEXT;
#endif /* configENABLE_TRUSTZONE */

/**
 * @brief Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#എങ്കിൽ ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) )

    സ്ഥിതം uint8_t ucMaxSysCallPriority = 0;
    സ്ഥിതം uint32_t ulMaxPRIGROUPValue = 0;
    സ്ഥിതം സ്ഥിരം അസ്ഥിര uint8_t * സ്ഥിരം pcInterruptPriorityRegisters = ( സ്ഥിരം അസ്ഥിര uint8_t * ) portNVIC_IP_REGISTERS_OFFSET_16;

#endif /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */

#എങ്കിൽ ( configUSE_TICKLESS_IDLE == 1 )

    /**
     * @brief The number of SysTick increments that make up one tick period.
     */
    PRIVILEGED_DATA സ്ഥിതം uint32_t ulTimerCountsForOneTick = 0;

    /**
     * @brief The maximum number of tick periods that can be suppressed is
     * limited by the 24 bit resolution of the SysTick timer.
     */
    PRIVILEGED_DATA സ്ഥിതം uint32_t xMaximumPossibleSuppressedTicks = 0;

    /**
     * @brief Compensate for the CPU cycles that pass while the SysTick is
     * stopped (low power functionality only).
     */
    PRIVILEGED_DATA സ്ഥിതം uint32_t ulStoppedTimerCompensation = 0;
#endif /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) ശൂന്യം vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime )
    {
        uint32_t ul_Reload_മൂല്യം, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_ഇടത്;
        TickType_t xModifiableIdleTime;

        /* Make sure the SysTick reload value does not overflow the counter. */
        എങ്കിൽ( xExpectedIdleTime > xMaximumPossibleSuppressedTicks )
        {
            xExpectedIdleTime = xMaximumPossibleSuppressedTicks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm അസ്ഥിര ( "cpsid i" ::: "memory" );
        __asm അസ്ഥിര ( "dsb" );
        __asm അസ്ഥിര ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        എങ്കിൽ( eTaskConfirmSleepModeStatus() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the cpsid instruction
             * above. */
            __asm അസ്ഥിര ( "cpsie i" ::: "memory" );
        }
        അല്ലെങ്കിൽ
        {
            /* Stop the SysTick momentarily.  The time the SysTick is stopped for
             * is accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            portNVIC_SYSTICK_CTRL_REG = ( portNVIC_SYSTICK_CLK_BIT_CONFIG | portNVIC_SYSTICK_INT_BIT );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_ഇടത് = port_NVIC_SYSTICK_CURRENT_മൂല്യം_REG;

            എങ്കിൽ( ul_Sys_Tick_Decrements_ഇടത് == 0 )
            {
                ul_Sys_Tick_Decrements_ഇടത് = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_മൂല്യം = ul_Sys_Tick_Decrements_ഇടത് + ( ulTimerCountsForOneTick * ( xExpectedIdleTime - 1UL ) );

            എങ്കിൽ( ( portNVIC_INT_CTRL_REG & portNVIC_PEND_SYSTICK_SET_BIT ) != 0 )
            {
                portNVIC_INT_CTRL_REG = portNVIC_PEND_SYSTICK_CLEAR_BIT;
                ul_Reload_മൂല്യം -= ulTimerCountsForOneTick;
            }

            എങ്കിൽ( ul_Reload_മൂല്യം > ulStoppedTimerCompensation )
            {
                ul_Reload_മൂല്യം -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            portNVIC_SYSTICK_LOAD_REG = ul_Reload_മൂല്യം;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            port_NVIC_SYSTICK_CURRENT_മൂല്യം_REG = 0UL;

            /* Restart SysTick. */
            portNVIC_SYSTICK_CTRL_REG |= portNVIC_SYSTICK_ENABLE_BIT;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            xModifiableIdleTime = xExpectedIdleTime;
            configPRE_SLEEP_PROCESSING( xModifiableIdleTime );

            എങ്കിൽ( xModifiableIdleTime > 0 )
            {
                __asm അസ്ഥിര ( "dsb" ::: "memory" );
                __asm അസ്ഥിര ( "wfi" );
                __asm അസ്ഥിര ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( xExpectedIdleTime );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the cpsid instruction above. */
            __asm അസ്ഥിര ( "cpsie i" ::: "memory" );
            __asm അസ്ഥിര ( "dsb" );
            __asm അസ്ഥിര ( "isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm അസ്ഥിര ( "cpsid i" ::: "memory" );
            __asm അസ്ഥിര ( "dsb" );
            __asm അസ്ഥിര ( "isb" );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            portNVIC_SYSTICK_CTRL_REG = ( portNVIC_SYSTICK_CLK_BIT_CONFIG | portNVIC_SYSTICK_INT_BIT );

            /* Determine whether the SysTick has already counted to zero. */
            എങ്കിൽ( ( portNVIC_SYSTICK_CTRL_REG & port_NVIC_SYSTICK_എണ്ണം_FLAG_BIT ) != 0 )
            {
                uint32_t ul_Calculated_Load_മൂല്യം;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_Load_മൂല്യം = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_മൂല്യം - port_NVIC_SYSTICK_CURRENT_മൂല്യം_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                എങ്കിൽ( ( ul_Calculated_Load_മൂല്യം <= ulStoppedTimerCompensation ) || ( ul_Calculated_Load_മൂല്യം > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_Load_മൂല്യം = ( ulTimerCountsForOneTick - 1UL );
                }

                portNVIC_SYSTICK_LOAD_REG = ul_Calculated_Load_മൂല്യം;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = xExpectedIdleTime - 1UL;
            }
            അല്ലെങ്കിൽ
            {
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_ഇടത് = port_NVIC_SYSTICK_CURRENT_മൂല്യം_REG;
                #എങ്കിൽ ( portNVIC_SYSTICK_CLK_BIT_CONFIG != portNVIC_SYSTICK_CLK_BIT )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    എങ്കിൽ( ul_Sys_Tick_Decrements_ഇടത് == 0 )
                    {
                        ul_Sys_Tick_Decrements_ഇടത് = ul_Reload_മൂല്യം;
                    }
                }
                #endif /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( xExpectedIdleTime * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_ഇടത്;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                portNVIC_SYSTICK_LOAD_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            port_NVIC_SYSTICK_CURRENT_മൂല്യം_REG = 0UL;
            portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT;
            #എങ്കിൽ ( portNVIC_SYSTICK_CLK_BIT_CONFIG == portNVIC_SYSTICK_CLK_BIT )
            {
                portNVIC_SYSTICK_LOAD_REG = ulTimerCountsForOneTick - 1UL;
            }
            #അല്ലെങ്കിൽ
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT;

                എങ്കിൽ( ( portNVIC_SYSTICK_CTRL_REG & port_NVIC_SYSTICK_എണ്ണം_FLAG_BIT ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    port_NVIC_SYSTICK_CURRENT_മൂല്യം_REG = 0;
                }

                portNVIC_SYSTICK_LOAD_REG = ulTimerCountsForOneTick - 1UL;
                portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT_CONFIG | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT;
            }
            #endif /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            vTaskStepTick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __asm അസ്ഥിര ( "cpsie i" ::: "memory" );
        }
    }

#endif /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

__attribute__( ( weak ) ) ശൂന്യം vPortSetupTimerInterrupt( ശൂന്യം ) /* PRIVILEGED_FUNCTION */
{
    /* Calculate the constants required to configure the tick interrupt. */
    #എങ്കിൽ ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ );
        xMaximumPossibleSuppressedTicks = port_MAX_24_BIT_സംഖ്യ / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = portMISSED_COUNTS_FACTOR / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #endif /* configUSE_TICKLESS_IDLE */

    /* Stop and reset SysTick.
     *
     * QEMU versions older than 7.0.0 contain a bug which causes an error if we
     * enable SysTick without first selecting a valid clock source. We trigger
     * the bug if we change clock sources from a clock with a zero clock period
     * to one with a nonzero clock period and enable Systick at the same time.
     * So we configure the CLKSOURCE bit here, prior to setting the ENABLE bit.
     * This workaround avoids the bug in QEMU versions older than 7.0.0. */
    portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT_CONFIG;
    port_NVIC_SYSTICK_CURRENT_മൂല്യം_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    portNVIC_SYSTICK_LOAD_REG = ( configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL;
    portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT_CONFIG | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT;
}
/*-----------------------------------------------------------*/

സ്ഥിതം ശൂന്യം prvTaskExitError( ശൂന്യം )
{
    അസ്ഥിര uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    #എങ്കിൽ ( config_സംഖ്യ_OF_CORES == 1 )
        configASSERT( ulCriticalNesting == ~0UL );
    #അല്ലെങ്കിൽ /* #if ( configNUMBER_OF_CORES == 1 ) */
        configASSERT( ulCriticalNestings[ portGET_CORE_ID() ] == ~0UL );
    #endif /* #if ( configNUMBER_OF_CORES == 1 ) */
    portDISABLE_INTERRUPTS();

    ആകുമ്പോൾ( ulDummy == 0 )
    {
        /* This file calls prvTaskExitError() after the scheduler has been
         * started to remove a compiler warning about the function being
         * defined but never called.  ulDummy is used purely to quieten other
         * warnings about code appearing after this function is called - making
         * ulDummy volatile makes the compiler think the function could return
         * and therefore not output an 'unreachable code' warning for code that
         * appears after it. */
    }
}
/*-----------------------------------------------------------*/

#എങ്കിൽ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    സ്ഥിതം uint32_t prvGetRegionAccessPermissions( uint32_t ulRBARValue ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ulAccessPermissions = 0;

        എങ്കിൽ( ( ulRBARValue & portMPU_RBAR_ACCESS_PERMISSIONS_MASK ) == portMPU_REGION_READ_ONLY )
        {
            ulAccessPermissions = tskMPU_READ_PERMISSION;
        }

        എങ്കിൽ( ( ulRBARValue & portMPU_RBAR_ACCESS_PERMISSIONS_MASK ) == portMPU_REGION_READ_WRITE )
        {
            ulAccessPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
        }

        തിരികെ ulAccessPermissions;
    }

#endif /* configENABLE_MPU == 1 && configUSE_MPU_WRAPPERS_V1 == 0 */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configENABLE_MPU == 1 )

    സ്ഥിതം ശൂന്യം prvSetupMPU( ശൂന്യം ) /* PRIVILEGED_FUNCTION */
    {
        #എങ്കിൽ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ബാഹ്യ uint32_t * __privileged_functions_start__;
            ബാഹ്യ uint32_t * __privileged_functions_end__;
            ബാഹ്യ uint32_t * __syscalls_flash_start__;
            ബാഹ്യ uint32_t * __syscalls_flash_end__;
            ബാഹ്യ uint32_t * __unprivileged_flash_start__;
            ബാഹ്യ uint32_t * __unprivileged_flash_end__;
            ബാഹ്യ uint32_t * __privileged_sram_start__;
            ബാഹ്യ uint32_t * __privileged_sram_end__;
        #അല്ലെങ്കിൽ /* if defined( __ARMCC_VERSION ) */
            /* Declaration when these variable are exported from linker scripts. */
            ബാഹ്യ uint32_t __privileged_functions_start__[];
            ബാഹ്യ uint32_t __privileged_functions_end__[];
            ബാഹ്യ uint32_t __syscalls_flash_start__[];
            ബാഹ്യ uint32_t __syscalls_flash_end__[];
            ബാഹ്യ uint32_t __unprivileged_flash_start__[];
            ബാഹ്യ uint32_t __unprivileged_flash_end__[];
            ബാഹ്യ uint32_t __privileged_sram_start__[];
            ബാഹ്യ uint32_t __privileged_sram_end__[];
        #endif /* defined( __ARMCC_VERSION ) */

        /* The only permitted number of regions are 8 or 16. */
        configASSERT( ( configTOTAL_MPU_REGIONS == 8 ) || ( configTOTAL_MPU_REGIONS == 16 ) );

        /* MAIR0 - Index 0. */
        portMPU_MAIR0_REG |= ( ( portMPU_NORMAL_MEMORY_BUFFERABLE_CACHEABLE << portMPU_MAIR_ATTR0_POS ) & portMPU_MAIR_ATTR0_MASK );
        /* MAIR0 - Index 1. */
        portMPU_MAIR0_REG |= ( ( portMPU_DEVICE_MEMORY_nGnRE << portMPU_MAIR_ATTR1_POS ) & portMPU_MAIR_ATTR1_MASK );

        /* Setup privileged flash as Read Only so that privileged tasks can
         * read it but not modify. */
        portMPU_RNR_REG = portPRIVILEGED_FLASH_REGION;
        portMPU_RBAR_REG = ( ( ( uint32_t ) __privileged_functions_start__ ) & portMPU_RBAR_ADDRESS_MASK ) |
                           ( portMPU_REGION_NON_SHAREABLE ) |
                           ( portMPU_REGION_PRIVILEGED_READ_ONLY );
        portMPU_RLAR_REG = ( ( ( uint32_t ) __privileged_functions_end__ ) & portMPU_RLAR_ADDRESS_MASK ) |
                           ( portMPU_RLAR_ATTR_INDEX0 ) |
                           ( portMPU_RLAR_REGION_ENABLE );

        /* Setup unprivileged flash as Read Only by both privileged and
         * unprivileged tasks. All tasks can read it but no-one can modify. */
        portMPU_RNR_REG = portUNPRIVILEGED_FLASH_REGION;
        portMPU_RBAR_REG = ( ( ( uint32_t ) __unprivileged_flash_start__ ) & portMPU_RBAR_ADDRESS_MASK ) |
                           ( portMPU_REGION_NON_SHAREABLE ) |
                           ( portMPU_REGION_READ_ONLY );
        portMPU_RLAR_REG = ( ( ( uint32_t ) __unprivileged_flash_end__ ) & portMPU_RLAR_ADDRESS_MASK ) |
                           ( portMPU_RLAR_ATTR_INDEX0 ) |
                           ( portMPU_RLAR_REGION_ENABLE );

        /* Setup unprivileged syscalls flash as Read Only by both privileged
         * and unprivileged tasks. All tasks can read it but no-one can modify. */
        portMPU_RNR_REG = portUNPRIVILEGED_SYSCALLS_REGION;
        portMPU_RBAR_REG = ( ( ( uint32_t ) __syscalls_flash_start__ ) & portMPU_RBAR_ADDRESS_MASK ) |
                           ( portMPU_REGION_NON_SHAREABLE ) |
                           ( portMPU_REGION_READ_ONLY );
        portMPU_RLAR_REG = ( ( ( uint32_t ) __syscalls_flash_end__ ) & portMPU_RLAR_ADDRESS_MASK ) |
                           ( portMPU_RLAR_ATTR_INDEX0 ) |
                           ( portMPU_RLAR_REGION_ENABLE );

        /* Setup RAM containing kernel data for privileged access only. */
        portMPU_RNR_REG = portPRIVILEGED_RAM_REGION;
        portMPU_RBAR_REG = ( ( ( uint32_t ) __privileged_sram_start__ ) & portMPU_RBAR_ADDRESS_MASK ) |
                           ( portMPU_REGION_NON_SHAREABLE ) |
                           ( portMPU_REGION_PRIVILEGED_READ_WRITE ) |
                           ( portMPU_REGION_EXECUTE_NEVER );
        portMPU_RLAR_REG = ( ( ( uint32_t ) __privileged_sram_end__ ) & portMPU_RLAR_ADDRESS_MASK ) |
                           ( portMPU_RLAR_ATTR_INDEX0 ) |
                           ( portMPU_RLAR_REGION_ENABLE );

        /* Enable mem fault. */
        portSCB_SYS_HANDLER_CTRL_STATE_REG |= portSCB_MEM_FAULT_ENABLE_BIT;

        /* Enable MPU with privileged background access i.e. unmapped
         * regions have privileged access. */
        portMPU_CTRL_REG |= ( portMPU_PRIV_BACKGROUND_ENABLE_BIT | portMPU_ENABLE_BIT );
    }

#endif /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configENABLE_FPU == 1 )

    സ്ഥിതം ശൂന്യം prvSetupFPU( ശൂന്യം ) /* PRIVILEGED_FUNCTION */
    {
        #എങ്കിൽ ( configENABLE_TRUSTZONE == 1 )
        {
            /* Enable non-secure access to the FPU. */
            SecureInit_EnableNSFPUAccess();
        }
        #endif /* configENABLE_TRUSTZONE */

        /* CP10 = 11 ==> Full access to FPU i.e. both privileged and
         * unprivileged code should be able to access FPU. CP11 should be
         * programmed to the same value as CP10. */
        *( portCPACR ) |= ( ( port_CPACR_CP10_മൂല്യം << portCPACR_CP10_POS ) |
                            ( port_CPACR_CP11_മൂല്യം << portCPACR_CP11_POS )
                            );

        /* ASPEN = 1 ==> Hardware should automatically preserve floating point
         * context on exception entry and restore on exception return.
         * LSPEN = 1 ==> Enable lazy context save of FP state. */
        *( portFPCCR ) |= ( portFPCCR_ASPEN_MASK | portFPCCR_LSPEN_MASK );
    }

#endif /* configENABLE_FPU */
/*-----------------------------------------------------------*/

ശൂന്യം vPortYield( ശൂന്യം ) /* PRIVILEGED_FUNCTION */
{
    /* Set a PendSV to request a context switch. */
    portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm അസ്ഥിര ( "dsb" ::: "memory" );
    __asm അസ്ഥിര ( "isb" );
}
/*-----------------------------------------------------------*/

#എങ്കിൽ ( config_സംഖ്യ_OF_CORES == 1 )
    ശൂന്യം vPortEnterCritical( ശൂന്യം ) /* PRIVILEGED_FUNCTION */
    {
        portDISABLE_INTERRUPTS();
        ulCriticalNesting++;
        /* Barriers are normally not required but do ensure the code is
        * completely within the specified behaviour for the architecture. */
        __asm അസ്ഥിര ( "dsb" ::: "memory" );
        __asm അസ്ഥിര ( "isb" );
    }
    /*-----------------------------------------------------------*/

    ശൂന്യം vPortExitCritical( ശൂന്യം ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( ulCriticalNesting );
        ulCriticalNesting--;

        എങ്കിൽ( ulCriticalNesting == 0 )
        {
            portENABLE_INTERRUPTS();
        }
    }
#endif /* configNUMBER_OF_CORES == 1 */
/*-----------------------------------------------------------*/

ശൂന്യം SysTick_Handler( ശൂന്യം ) /* PRIVILEGED_FUNCTION */
{
    uint32_t ulPreviousMask;

    ulPreviousMask = portSET_INTERRUPT_MASK_FROM_ISR();
    #എങ്കിൽ ( config_സംഖ്യ_OF_CORES > 1 )
        UBaseType_t uxSavedInterruptStatus = portENTER_CRITICAL_FROM_ISR();
    #endif /* if ( configNUMBER_OF_CORES > 1 ) */

    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        എങ്കിൽ( xTaskIncrementTick() != pdFALSE )
        {
            traceISR_EXIT_TO_SCHEDULER();
            /* Pend a context switch. */
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;
        }
        അല്ലെങ്കിൽ
        {
            traceISR_EXIT();
        }
    }
    #എങ്കിൽ ( config_സംഖ്യ_OF_CORES > 1 )
        portEXIT_CRITICAL_FROM_ISR( uxSavedInterruptStatus );
    #endif /* if ( configNUMBER_OF_CORES > 1 ) */

    portCLEAR_INTERRUPT_MASK_FROM_ISR( ulPreviousMask );
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortSVCHandler_C( uint32_t * pul_Caller_അട്ടി_Address ) /* PRIVILEGED_FUNCTION portDONT_DISCARD */
{
    #എങ്കിൽ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )
        #എങ്കിൽ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ബാഹ്യ uint32_t * __syscalls_flash_start__;
            ബാഹ്യ uint32_t * __syscalls_flash_end__;
        #അല്ലെങ്കിൽ
            /* Declaration when these variable are exported from linker scripts. */
            ബാഹ്യ uint32_t __syscalls_flash_start__[];
            ബാഹ്യ uint32_t __syscalls_flash_end__[];
        #endif /* defined( __ARMCC_VERSION ) */
    #endif /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #എങ്കിൽ ( configENABLE_MPU == 1 )
        #എങ്കിൽ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ബാഹ്യ uint32_t * __privileged_functions_start__;
            ബാഹ്യ uint32_t * __privileged_functions_end__;
        #അല്ലെങ്കിൽ
            /* Declaration when these variable are exported from linker scripts. */
            ബാഹ്യ uint32_t __privileged_functions_start__[];
            ബാഹ്യ uint32_t __privileged_functions_end__[];
        #endif /* defined( __ARMCC_VERSION ) */
    #endif /* configENABLE_MPU == 1 */

    uint32_t ulPC;

    #എങ്കിൽ ( configENABLE_TRUSTZONE == 1 )
        uint32_t ulR0, ulR1;
        ബാഹ്യ TaskHandle_t pxCurrentTCB;
        #എങ്കിൽ ( configENABLE_MPU == 1 )
            uint32_t ulControl, ulIsTaskPrivileged;
        #endif /* configENABLE_MPU */
    #endif /* configENABLE_TRUSTZONE */
    uint8_t ucSVCNumber;

    /* Register are stored on the stack in the following order - R0, R1, R2, R3,
     * R12, LR, PC, xPSR. */
    ulPC = pul_Caller_അട്ടി_Address[ portOFFSET_TO_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    തിരഞ്ഞെടുപ്പ്( ucSVCNumber )
    {
    #എങ്കിൽ ( configENABLE_TRUSTZONE == 1 )
        അവസ്ഥ portSVC_ALLOCATE_SECURE_CONTEXT:

            /* R0 contains the stack size passed as parameter to the
             * vPortAllocateSecureContext function. */
            ulR0 = pul_Caller_അട്ടി_Address[ 0 ];

            #എങ്കിൽ ( configENABLE_MPU == 1 )
            {
                /* Read the CONTROL register value. */
                __asm അസ്ഥിര ( "mrs %0, control"  : "=r" ( ulControl ) );

                /* The task that raised the SVC is privileged if Bit[0]
                 * in the CONTROL register is 0. */
                ulIsTaskPrivileged = ( ( ulControl & portCONTROL_PRIVILEGED_MASK ) == 0 );

                /* Allocate and load a context for the secure task. */
                xSecureContext = SecureContext_AllocateContext( ulR0, ulIsTaskPrivileged, pxCurrentTCB );
            }
            #അല്ലെങ്കിൽ /* if ( configENABLE_MPU == 1 ) */
            {
                /* Allocate and load a context for the secure task. */
                xSecureContext = SecureContext_AllocateContext( ulR0, pxCurrentTCB );
            }
            #endif /* configENABLE_MPU */

            configASSERT( xSecureContext != securecontextINVALID_CONTEXT_ID );
            SecureContext_LoadContext( xSecureContext, pxCurrentTCB );
            നിർത്തുക;

        അവസ്ഥ portSVC_FREE_SECURE_CONTEXT:
            #എങ്കിൽ ( configENABLE_MPU == 1 )
            എങ്കിൽ( ( ulPC >= ( uint32_t ) __privileged_functions_start__ ) &&
                ( ulPC <= ( uint32_t ) __privileged_functions_end__ ) )
            {
            #endif /* configENABLE_MPU */
                /* R0 contains TCB being freed and R1 contains the secure
                 * context handle to be freed. */
                ulR0 = pul_Caller_അട്ടി_Address[ 0 ];
                ulR1 = pul_Caller_അട്ടി_Address[ 1 ];

                /* Free the secure context. */
                SecureContext_FreeContext( ( SecureContextHandle_t ) ulR1, ( ശൂന്യം * ) ulR0 );
            #എങ്കിൽ ( configENABLE_MPU == 1 )
            }
            #endif /* configENABLE_MPU */
            നിർത്തുക;
    #endif /* configENABLE_TRUSTZONE */

        അവസ്ഥ portSVC_START_SCHEDULER:
            #എങ്കിൽ ( configENABLE_MPU == 1 )
            എങ്കിൽ( ( ulPC >= ( uint32_t ) __privileged_functions_start__ ) &&
                ( ulPC <= ( uint32_t ) __privileged_functions_end__ ) )
            {
            #endif /* configENABLE_MPU */
                #എങ്കിൽ ( configENABLE_TRUSTZONE == 1 )
                {
                    /* De-prioritize the non-secure exceptions so that the
                     * non-secure pendSV runs at the lowest priority. */
                    SecureInit_DePrioritizeNSExceptions();

                    /* Initialize the secure context management system. */
                    SecureContext_Init();
                }
                #endif /* configENABLE_TRUSTZONE */

                #എങ്കിൽ ( configENABLE_FPU == 1 )
                {
                    /* Setup the Floating Point Unit (FPU). */
                    prvSetupFPU();
                }
                #endif /* configENABLE_FPU */

                /* Setup the context of the first task so that the first task starts
                 * executing. */
                vRestoreContextOfFirstTask();
            #എങ്കിൽ ( configENABLE_MPU == 1 )
            }
            #endif /* configENABLE_MPU */
            നിർത്തുക;

    #എങ്കിൽ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )
        അവസ്ഥ portSVC_RAISE_PRIVILEGE:

            /* Only raise the privilege, if the svc was raised from any of
             * the system calls. */
            എങ്കിൽ( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
            {
                vRaisePrivilege();
            }
            നിർത്തുക;
    #endif /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #എങ്കിൽ ( configENABLE_MPU == 1 )
        അവസ്ഥ portSVC_YIELD:
            vPortYield();
            നിർത്തുക;
    #endif /* configENABLE_MPU == 1 */

        സ്ഥിരസ്ഥിതി:
            /* Incorrect SVC call. */
            configASSERT( pdFALSE );
    }
}
/*-----------------------------------------------------------*/

#എങ്കിൽ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ശൂന്യം vSystemCallEnter( uint32_t * pul_Task_അട്ടി,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_സംഖ്യ ) /* PRIVILEGED_FUNCTION */
    {
        ബാഹ്യ TaskHandle_t pxCurrentTCB;
        ബാഹ്യ UBaseType_t uxSystemCallImplementations[ അക്കം_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_അട്ടി;
        uint32_t ulHardwareSavedExceptionFrameSize, ulSystemCallLocation, i;

        #എങ്കിൽ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ബാഹ്യ uint32_t * __syscalls_flash_start__;
            ബാഹ്യ uint32_t * __syscalls_flash_end__;
        #അല്ലെങ്കിൽ
            /* Declaration when these variable are exported from linker scripts. */
            ബാഹ്യ uint32_t __syscalls_flash_start__[];
            ബാഹ്യ uint32_t __syscalls_flash_end__[];
        #endif /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_അട്ടി[ portOFFSET_TO_PC ];
        pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );

        /* Checks:
         * 1. SVC is raised from the system call section (i.e. application is
         *    not raising SVC directly).
         * 2. pxMpuSettings->xSystemCallStackInfo.pulTaskStack must be NULL as
         *    it is non-NULL only during the execution of a system call (i.e.
         *    between system call enter and exit).
         * 3. System call is not for a kernel API disabled by the configuration
         *    in FreeRTOSConfig.h.
         * 4. We do not need to check that ucSystemCallNumber is within range
         *    because the assembly SVC handler checks that before calling
         *    this function.
         */
        എങ്കിൽ( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_അട്ടി_Info.pul_Task_അട്ടി == ശൂന്യ ) &&
            ( uxSystemCallImplementations[ uc_System_Call_സംഖ്യ ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_അട്ടി = pxMpuSettings->x_System_Call_അട്ടി_Info.pul_System_Call_അട്ടി;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            #എങ്കിൽ ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )
            {
                എങ്കിൽ( ( ulLR & port_EXC_RETURN_അട്ടി_FRAME_TYPE_MASK ) == 0UL )
                {
                    /* Extended frame i.e. FPU in use. */
                    ulHardwareSavedExceptionFrameSize = 26;
                    __asm അസ്ഥിര (
                        " vpush {s0}         \n" /* Trigger lazy stacking. */
                        " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                        ::: "memory"
                        );
                }
                അല്ലെങ്കിൽ
                {
                    /* Standard frame i.e. FPU not in use. */
                    ulHardwareSavedExceptionFrameSize = 8;
                }
            }
            #അല്ലെങ്കിൽ /* if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */
            {
                ulHardwareSavedExceptionFrameSize = 8;
            }
            #endif /* configENABLE_FPU || configENABLE_MVE */

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_അട്ടി = pul_System_Call_അട്ടി - ulHardwareSavedExceptionFrameSize;

            /* Copy the stack frame. */
            വേണ്ടി( i = 0; i < ulHardwareSavedExceptionFrameSize; i++ )
            {
                pul_System_Call_അട്ടി[ i ] = pul_Task_അട്ടി[ i ];
            }

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_അട്ടി_Info.ulLinkRegisterAtSystemCallEntry = pul_Task_അട്ടി[ portOFFSET_TO_LR ];

            /* Store the value of the PSPLIM register before the SVC was raised.
             * We need to restore it when we exit from the system call. */
            #എങ്കിൽ ( portUSE_PSPLIM_REGISTER == 1 )
            {
                __asm അസ്ഥിര ( "mrs %0, psplim" : "=r" ( pxMpuSettings->x_System_Call_അട്ടി_Info.ul_അട്ടി_Limit_Register_At_System_Call_Entry ) );
            }
            #endif

            /* Use the pulSystemCallStack in thread mode. */
            __asm അസ്ഥിര ( "msr psp, %0" : : "r" ( pul_System_Call_അട്ടി ) );
            #എങ്കിൽ ( portUSE_PSPLIM_REGISTER == 1 )
            {
                __asm അസ്ഥിര ( "msr psplim, %0" : : "r" ( pxMpuSettings->x_System_Call_അട്ടി_Info.pul_System_Call_അട്ടി_Limit ) );
            }
            #endif

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_അട്ടി[ portOFFSET_TO_PC ] = uxSystemCallImplementations[ uc_System_Call_സംഖ്യ ];

            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_അട്ടി[ portOFFSET_TO_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_അട്ടി_Info.pul_Task_അട്ടി = pul_Task_അട്ടി + ulHardwareSavedExceptionFrameSize;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            എങ്കിൽ( ( pul_Task_അട്ടി[ portOFFSET_TO_PSR ] & port_PSR_അട്ടി_PADDING_MASK ) == port_PSR_അട്ടി_PADDING_MASK )
            {
                pxMpuSettings->ulTaskFlags |= port_അട്ടി_FRAME_HAS_PADDING_FLAG;
            }
            അല്ലെങ്കിൽ
            {
                pxMpuSettings->ulTaskFlags &= ( ~port_അട്ടി_FRAME_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_അട്ടി[ portOFFSET_TO_PSR ] &= ( ~port_PSR_അട്ടി_PADDING_MASK );

            /* Raise the privilege for the duration of the system call. */
            __asm അസ്ഥിര (
                " mrs r0, control     \n" /* Obtain current control value. */
                " movs r1, #1         \n" /* r1 = 1. */
                " bics r0, r1         \n" /* Clear nPRIV bit. */
                " msr control, r0     \n" /* Write back new control value. */
                ::: "r0", "r1", "memory"
                );
        }
    }

#endif /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ശൂന്യം vRequestSystemCallExit( ശൂന്യം ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm അസ്ഥിര ( "svc %0 \n" ::"i" ( portSVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#endif /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ശൂന്യം vSystemCallExit( uint32_t * pul_System_Call_അട്ടി,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        ബാഹ്യ TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_അട്ടി;
        uint32_t ulHardwareSavedExceptionFrameSize, ulSystemCallLocation, i;

        #എങ്കിൽ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ബാഹ്യ uint32_t * __privileged_functions_start__;
            ബാഹ്യ uint32_t * __privileged_functions_end__;
        #അല്ലെങ്കിൽ
            /* Declaration when these variable are exported from linker scripts. */
            ബാഹ്യ uint32_t __privileged_functions_start__[];
            ബാഹ്യ uint32_t __privileged_functions_end__[];
        #endif /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_അട്ടി[ portOFFSET_TO_PC ];
        pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );

        /* Checks:
         * 1. SVC is raised from the privileged code (i.e. application is not
         *    raising SVC directly). This SVC is only raised from
         *    vRequestSystemCallExit which is in the privileged code section.
         * 2. pxMpuSettings->xSystemCallStackInfo.pulTaskStack must not be NULL -
         *    this means that we previously entered a system call and the
         *    application is not attempting to exit without entering a system
         *    call.
         */
        എങ്കിൽ( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_അട്ടി_Info.pul_Task_അട്ടി != ശൂന്യ ) )
        {
            pul_Task_അട്ടി = pxMpuSettings->x_System_Call_അട്ടി_Info.pul_Task_അട്ടി;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            #എങ്കിൽ ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )
            {
                എങ്കിൽ( ( ulLR & port_EXC_RETURN_അട്ടി_FRAME_TYPE_MASK ) == 0UL )
                {
                    /* Extended frame i.e. FPU in use. */
                    ulHardwareSavedExceptionFrameSize = 26;
                    __asm അസ്ഥിര (
                        " vpush {s0}         \n" /* Trigger lazy stacking. */
                        " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                        ::: "memory"
                        );
                }
                അല്ലെങ്കിൽ
                {
                    /* Standard frame i.e. FPU not in use. */
                    ulHardwareSavedExceptionFrameSize = 8;
                }
            }
            #അല്ലെങ്കിൽ /* if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */
            {
                ulHardwareSavedExceptionFrameSize = 8;
            }
            #endif /* configENABLE_FPU || configENABLE_MVE */

            /* Make space on the task stack for the stack frame. */
            pul_Task_അട്ടി = pul_Task_അട്ടി - ulHardwareSavedExceptionFrameSize;

            /* Copy the stack frame. */
            വേണ്ടി( i = 0; i < ulHardwareSavedExceptionFrameSize; i++ )
            {
                pul_Task_അട്ടി[ i ] = pul_System_Call_അട്ടി[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm അസ്ഥിര ( "msr psp, %0" : : "r" ( pul_Task_അട്ടി ) );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_അട്ടി[ portOFFSET_TO_PC ] = pxMpuSettings->x_System_Call_അട്ടി_Info.ulLinkRegisterAtSystemCallEntry;
            /* Ensure that LR has a valid value.*/
            pul_Task_അട്ടി[ portOFFSET_TO_LR ] = pxMpuSettings->x_System_Call_അട്ടി_Info.ulLinkRegisterAtSystemCallEntry;

            /* Restore the PSPLIM register to what it was at the time of
             * system call entry. */
            #എങ്കിൽ ( portUSE_PSPLIM_REGISTER == 1 )
            {
                __asm അസ്ഥിര ( "msr psplim, %0" : : "r" ( pxMpuSettings->x_System_Call_അട്ടി_Info.ul_അട്ടി_Limit_Register_At_System_Call_Entry ) );
            }
            #endif

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            എങ്കിൽ( ( pxMpuSettings->ulTaskFlags & port_അട്ടി_FRAME_HAS_PADDING_FLAG ) == port_അട്ടി_FRAME_HAS_PADDING_FLAG )
            {
                pul_Task_അട്ടി[ portOFFSET_TO_PSR ] |= port_PSR_അട്ടി_PADDING_MASK;
            }
            അല്ലെങ്കിൽ
            {
                pul_Task_അട്ടി[ portOFFSET_TO_PSR ] &= ( ~port_PSR_അട്ടി_PADDING_MASK );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_അട്ടി_Info.pul_Task_അട്ടി = ശൂന്യ;

            /* Drop the privilege before returning to the thread mode. */
            __asm അസ്ഥിര (
                " mrs r0, control     \n" /* Obtain current control value. */
                " movs r1, #1         \n" /* r1 = 1. */
                " orrs r0, r1         \n" /* Set nPRIV bit. */
                " msr control, r0     \n" /* Write back new control value. */
                ::: "r0", "r1", "memory"
                );
        }
    }

#endif /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configENABLE_MPU == 1 )

    BaseType_t xPortIsTaskPrivileged( ശൂന്യം ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xTaskIsPrivileged = pdFALSE;
        സ്ഥിരം xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ശൂന്യ ); /* Calling task's MPU settings. */

        എങ്കിൽ( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        തിരികെ xTaskIsPrivileged;
    }

#endif /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configENABLE_MPU == 1 )

    അട്ടി_Type_t * px_Port_Initialise_അട്ടി( അട്ടി_Type_t * px_മുകൾ_Of_അട്ടി,
                                         അട്ടി_Type_t * px_End_Of_അട്ടി,
                                         TaskFunction_t pxCode,
                                         ശൂന്യം * pvParameters,
                                         BaseType_t xRunPrivileged,
                                         xMPU_SETTINGS * xMPUSettings ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ulIndex = 0;
        uint32_t ulControl = 0x0;

        xMPUSettings->ulContext[ ulIndex ] = 0x04040404; /* r4. */
        ulIndex++;
        xMPUSettings->ulContext[ ulIndex ] = 0x05050505; /* r5. */
        ulIndex++;
        xMPUSettings->ulContext[ ulIndex ] = 0x06060606; /* r6. */
        ulIndex++;
        xMPUSettings->ulContext[ ulIndex ] = 0x07070707; /* r7. */
        ulIndex++;
        xMPUSettings->ulContext[ ulIndex ] = 0x08080808; /* r8. */
        ulIndex++;
        xMPUSettings->ulContext[ ulIndex ] = 0x09090909; /* r9. */
        ulIndex++;
        xMPUSettings->ulContext[ ulIndex ] = 0x10101010; /* r10. */
        ulIndex++;
        xMPUSettings->ulContext[ ulIndex ] = 0x11111111; /* r11. */
        ulIndex++;

        xMPUSettings->ulContext[ ulIndex ] = ( uint32_t ) pvParameters; /* r0. */
        ulIndex++;
        xMPUSettings->ulContext[ ulIndex ] = 0x01010101; /* r1. */
        ulIndex++;
        xMPUSettings->ulContext[ ulIndex ] = 0x02020202; /* r2. */
        ulIndex++;
        xMPUSettings->ulContext[ ulIndex ] = 0x03030303; /* r3. */
        ulIndex++;
        xMPUSettings->ulContext[ ulIndex ] = 0x12121212; /* r12. */
        ulIndex++;
        xMPUSettings->ulContext[ ulIndex ] = ( uint32_t ) portTASK_RETURN_ADDRESS; /* LR. */
        ulIndex++;
        xMPUSettings->ulContext[ ulIndex ] = ( uint32_t ) pxCode; /* PC. */
        ulIndex++;
        xMPUSettings->ulContext[ ulIndex ] = portINITIAL_XPSR; /* xPSR. */
        ulIndex++;

        #എങ്കിൽ ( configENABLE_TRUSTZONE == 1 )
        {
            xMPUSettings->ulContext[ ulIndex ] = portNO_SECURE_CONTEXT; /* xSecureContext. */
            ulIndex++;
        }
        #endif /* configENABLE_TRUSTZONE */
        xMPUSettings->ulContext[ ulIndex ] = ( uint32_t ) ( px_മുകൾ_Of_അട്ടി - 8 ); /* PSP with the hardware saved stack. */
        ulIndex++;
        xMPUSettings->ulContext[ ulIndex ] = ( uint32_t ) px_End_Of_അട്ടി; /* PSPLIM. */
        ulIndex++;

        #എങ്കിൽ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
        {
            /* Check PACBTI security feature configuration before pushing the
             * CONTROL register's value on task's TCB. */
            #എങ്കിൽ ( config_സംഖ്യ_OF_CORES == 1 )
                ulControl = prvConfigurePACBTI( pdFALSE );
            #അല്ലെങ്കിൽ /* configNUMBER_OF_CORES > 1 */
                ulControl = vConfigurePACBTI( pdFALSE );
            #endif /* configNUMBER_OF_CORES */
        }
        #endif /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

        എങ്കിൽ( xRunPrivileged == pdTRUE )
        {
            xMPUSettings->ulTaskFlags |= portTASK_IS_PRIVILEGED_FLAG;
            xMPUSettings->ulContext[ ulIndex ] = ( ulControl | ( uint32_t ) portINITIAL_CONTROL_PRIVILEGED ); /* CONTROL. */
            ulIndex++;
        }
        അല്ലെങ്കിൽ
        {
            xMPUSettings->ulTaskFlags &= ( ~portTASK_IS_PRIVILEGED_FLAG );
            xMPUSettings->ulContext[ ulIndex ] = ( ulControl | ( uint32_t ) portINITIAL_CONTROL_UNPRIVILEGED ); /* CONTROL. */
            ulIndex++;
        }

        xMPUSettings->ulContext[ ulIndex ] = portINITIAL_EXC_RETURN; /* LR (EXC_RETURN). */
        ulIndex++;

        #എങ്കിൽ ( configUSE_MPU_WRAPPERS_V1 == 0 )
        {
            /* Ensure that the system call stack is double word aligned. */
            xMPUSettings->x_System_Call_അട്ടി_Info.pul_System_Call_അട്ടി = &( xMPUSettings->x_System_Call_അട്ടി_Info.ul_System_Call_അട്ടി_Buffer[ config_SYSTEM_CALL_അട്ടി_SIZE - 1 ] );
            xMPUSettings->x_System_Call_അട്ടി_Info.pul_System_Call_അട്ടി = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_അട്ടി_Info.pul_System_Call_അട്ടി ) &
                                                                                     ( uint32_t ) ( ~( portBYTE_ALIGNMENT_MASK ) ) );

            xMPUSettings->x_System_Call_അട്ടി_Info.pul_System_Call_അട്ടി_Limit = &( xMPUSettings->x_System_Call_അട്ടി_Info.ul_System_Call_അട്ടി_Buffer[ 0 ] );
            xMPUSettings->x_System_Call_അട്ടി_Info.pul_System_Call_അട്ടി_Limit = ( uint32_t * ) ( ( ( uint32_t ) ( xMPUSettings->x_System_Call_അട്ടി_Info.pul_System_Call_അട്ടി_Limit ) +
                                                                                            ( uint32_t ) ( portBYTE_ALIGNMENT - 1 ) ) &
                                                                                          ( uint32_t ) ( ~( portBYTE_ALIGNMENT_MASK ) ) );

            /* This is not NULL only for the duration of a system call. */
            xMPUSettings->x_System_Call_അട്ടി_Info.pul_Task_അട്ടി = ശൂന്യ;
        }
        #endif /* configUSE_MPU_WRAPPERS_V1 == 0 */

        #എങ്കിൽ ( configENABLE_PAC == 1 )
        {
            uint32_t ul_Task_Pac_താക്കോൽ[ 4 ], i;

            v_Application_Generate_Task_Random_Pac_താക്കോൽ( &( ul_Task_Pac_താക്കോൽ[ 0 ] ) );

            വേണ്ടി( i = 0; i < 4; i++ )
            {
                xMPUSettings->ulContext[ ulIndex ] = ul_Task_Pac_താക്കോൽ[ i ];
                ulIndex++;
            }
        }
        #endif /* configENABLE_PAC */

        തിരികെ &( xMPUSettings->ulContext[ ulIndex ] );
    }

#അല്ലെങ്കിൽ /* configENABLE_MPU */

    അട്ടി_Type_t * px_Port_Initialise_അട്ടി( അട്ടി_Type_t * px_മുകൾ_Of_അട്ടി,
                                         അട്ടി_Type_t * px_End_Of_അട്ടി,
                                         TaskFunction_t pxCode,
                                         ശൂന്യം * pvParameters ) /* PRIVILEGED_FUNCTION */
    {
        /* Simulate the stack frame as it would be created by a context switch
         * interrupt. */
        #എങ്കിൽ ( portPRELOAD_REGISTERS == 0 )
        {
            px_മുകൾ_Of_അട്ടി--; /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_മുകൾ_Of_അട്ടി = portINITIAL_XPSR; /* xPSR. */
            px_മുകൾ_Of_അട്ടി--;
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) pxCode; /* PC. */
            px_മുകൾ_Of_അട്ടി--;
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) portTASK_RETURN_ADDRESS; /* LR. */
            px_മുകൾ_Of_അട്ടി -= 5; /* R12, R3, R2 and R1. */
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) pvParameters; /* R0. */
            px_മുകൾ_Of_അട്ടി -= 9; /* R11..R4, EXC_RETURN. */
            *px_മുകൾ_Of_അട്ടി = portINITIAL_EXC_RETURN;
            px_മുകൾ_Of_അട്ടി--;
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) px_End_Of_അട്ടി; /* Slot used to hold this task's PSPLIM value. */

            #എങ്കിൽ ( configENABLE_TRUSTZONE == 1 )
            {
                px_മുകൾ_Of_അട്ടി--;
                *px_മുകൾ_Of_അട്ടി = portNO_SECURE_CONTEXT; /* Slot used to hold this task's xSecureContext value. */
            }
            #endif /* configENABLE_TRUSTZONE */
        }
        #അല്ലെങ്കിൽ /* portPRELOAD_REGISTERS */
        {
            px_മുകൾ_Of_അട്ടി--; /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_മുകൾ_Of_അട്ടി = portINITIAL_XPSR; /* xPSR. */
            px_മുകൾ_Of_അട്ടി--;
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) pxCode; /* PC. */
            px_മുകൾ_Of_അട്ടി--;
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) portTASK_RETURN_ADDRESS; /* LR. */
            px_മുകൾ_Of_അട്ടി--;
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x12121212UL; /* R12. */
            px_മുകൾ_Of_അട്ടി--;
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x03030303UL; /* R3. */
            px_മുകൾ_Of_അട്ടി--;
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x02020202UL; /* R2. */
            px_മുകൾ_Of_അട്ടി--;
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x01010101UL; /* R1. */
            px_മുകൾ_Of_അട്ടി--;
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) pvParameters; /* R0. */
            px_മുകൾ_Of_അട്ടി--;
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x11111111UL; /* R11. */
            px_മുകൾ_Of_അട്ടി--;
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x10101010UL; /* R10. */
            px_മുകൾ_Of_അട്ടി--;
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x09090909UL; /* R09. */
            px_മുകൾ_Of_അട്ടി--;
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x08080808UL; /* R08. */
            px_മുകൾ_Of_അട്ടി--;
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x07070707UL; /* R07. */
            px_മുകൾ_Of_അട്ടി--;
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x06060606UL; /* R06. */
            px_മുകൾ_Of_അട്ടി--;
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x05050505UL; /* R05. */
            px_മുകൾ_Of_അട്ടി--;
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x04040404UL; /* R04. */
            px_മുകൾ_Of_അട്ടി--;
            *px_മുകൾ_Of_അട്ടി = portINITIAL_EXC_RETURN; /* EXC_RETURN. */
            px_മുകൾ_Of_അട്ടി--;
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) px_End_Of_അട്ടി; /* Slot used to hold this task's PSPLIM value. */

            #എങ്കിൽ ( configENABLE_TRUSTZONE == 1 )
            {
                px_മുകൾ_Of_അട്ടി--;
                *px_മുകൾ_Of_അട്ടി = portNO_SECURE_CONTEXT; /* Slot used to hold this task's xSecureContext value. */
            }
            #endif /* configENABLE_TRUSTZONE */
        }
        #endif /* portPRELOAD_REGISTERS */

        #എങ്കിൽ ( configENABLE_PAC == 1 )
        {
            uint32_t ul_Task_Pac_താക്കോൽ[ 4 ], i;

            v_Application_Generate_Task_Random_Pac_താക്കോൽ( &( ul_Task_Pac_താക്കോൽ[ 0 ] ) );

            വേണ്ടി( i = 0; i < 4; i++ )
            {
                px_മുകൾ_Of_അട്ടി--;
                *px_മുകൾ_Of_അട്ടി = ul_Task_Pac_താക്കോൽ[ i ];
            }
        }
        #endif /* configENABLE_PAC */

        തിരികെ px_മുകൾ_Of_അട്ടി;
    }

#endif /* configENABLE_MPU */
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( ശൂന്യം ) /* PRIVILEGED_FUNCTION */
{
    /* An application can install FreeRTOS interrupt handlers in one of the
     * following ways:
     * 1. Direct Routing - Install the functions SVC_Handler and PendSV_Handler
     *    for SVCall and PendSV interrupts respectively.
     * 2. Indirect Routing - Install separate handlers for SVCall and PendSV
     *    interrupts and route program control from those handlers to
     *    SVC_Handler and PendSV_Handler functions.
     *
     * Applications that use Indirect Routing must set
     * configCHECK_HANDLER_INSTALLATION to 0 in their FreeRTOSConfig.h. Direct
     * routing, which is validated here when configCHECK_HANDLER_INSTALLATION
     * is 1, should be preferred when possible. */
    #എങ്കിൽ ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        സ്ഥിരം portISR_t * സ്ഥിരം pxVectorTable = portSCB_VTOR_REG;

        /* Validate that the application has correctly installed the FreeRTOS
         * handlers for SVCall and PendSV interrupts. We do not check the
         * installation of the SysTick handler because the application may
         * choose to drive the RTOS tick using a timer other than the SysTick
         * timer by overriding the weak function vPortSetupTimerInterrupt().
         *
         * Assertion failures here indicate incorrect installation of the
         * FreeRTOS handlers. For help installing the FreeRTOS handlers, see
         * https://www.freertos.org/Why-FreeRTOS/FAQs.
         *
         * Systems with a configurable address for the interrupt vector table
         * can also encounter assertion failures or even system faults here if
         * VTOR is not set correctly to point to the application's vector table. */
        configASSERT( pxVectorTable[ portVECTOR_INDEX_SVC ] == SVC_Handler );
        configASSERT( pxVectorTable[ portVECTOR_INDEX_PENDSV ] == PendSV_Handler );
    }
    #endif /* configCHECK_HANDLER_INSTALLATION */

    vPortConfigureInterruptPriorities();

    #എങ്കിൽ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
    {
        /* Set the CONTROL register value based on PACBTI security feature
         * configuration before starting the first task. */
        #എങ്കിൽ ( config_സംഖ്യ_OF_CORES == 1 )
            ( ശൂന്യം ) prvConfigurePACBTI( pdTRUE );
        #അല്ലെങ്കിൽ /* configNUMBER_OF_CORES > 1 */
            ( ശൂന്യം ) vConfigurePACBTI( pdTRUE );
        #endif /* configNUMBER_OF_CORES */
    }
    #endif /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

    #എങ്കിൽ ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        prvSetupMPU();
    }
    #endif /* configENABLE_MPU */

    #എങ്കിൽ ( config_സംഖ്യ_OF_CORES > 1 )
        /* Start the timer that generates the tick ISR. Interrupts are disabled
         * here already. */
        vPortSetupTimerInterrupt();
        /* Initialize the critical nesting count for all cores. */
        വേണ്ടി ( uint8_t ucCoreID = 0; ucCoreID < config_സംഖ്യ_OF_CORES; ucCoreID++ )
        {
            ulCriticalNestings[ ucCoreID ] = 0;
        }
        /* Signal that primary core has done all the necessary initialisations. */
        ucPrimaryCoreInitDoneFlag = 1;
        /* Wake up secondary cores */
        BaseType_t xWakeResult = configWAKE_SECONDARY_CORES();
        configASSERT( xWakeResult == pdTRUE );

        /* Hold the primary core here until all the secondary cores are ready, this would be achieved only when
         * all elements of ucSecondaryCoresReadyFlags are set.
         */
        ആകുമ്പോൾ( 1 )
        {
            BaseType_t xAllCoresReady = pdTRUE;
            വേണ്ടി( uint8_t ucCoreID = 0; ucCoreID < ( config_സംഖ്യ_OF_CORES - 1 ); ucCoreID++ )
            {
                എങ്കിൽ( ucSecondaryCoresReadyFlags[ ucCoreID ] != pdTRUE )
                {
                    xAllCoresReady = pdFALSE;
                    നിർത്തുക;
                }
                }

            എങ്കിൽ ( xAllCoresReady == pdTRUE )
            {
                നിർത്തുക;
            }
        }
    #അല്ലെങ്കിൽ /* if ( configNUMBER_OF_CORES > 1 ) */
        /* Start the timer that generates the tick ISR. */
        vPortSetupTimerInterrupt();
        /* Initialize the critical nesting count ready for the first task. */
        ulCriticalNesting = 0;
    #endif /* if ( configNUMBER_OF_CORES > 1 ) */

    #എങ്കിൽ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )
    {
        xSchedulerRunning = pdTRUE;
    }
    #endif /* ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

    /* Start the first task. */
    vStartFirstTask();

    /* Should never get here as the tasks will now be executing. Call the task
     * exit error function to prevent compiler warnings about a static function
     * not being called in the case that the application writer overrides this
     * functionality by defining configTASK_RETURN_ADDRESS. Call
     * vTaskSwitchContext() so link time optimization does not remove the
     * symbol. */
    #എങ്കിൽ ( config_സംഖ്യ_OF_CORES > 1 )
        vTaskSwitchContext( portGET_CORE_ID() );
    #അല്ലെങ്കിൽ
        vTaskSwitchContext();
    #endif
    prvTaskExitError();

    /* Should not get here. */
    തിരികെ 0;
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortEndScheduler( ശൂന്യം ) /* PRIVILEGED_FUNCTION */
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    #എങ്കിൽ ( config_സംഖ്യ_OF_CORES == 1 )
        configASSERT( ulCriticalNesting == 1000UL );
    #അല്ലെങ്കിൽ /* if ( configNUMBER_OF_CORES == 1 ) */
        configASSERT( ulCriticalNestings[ portGET_CORE_ID() ] == 1000UL );
    #endif /* if ( configNUMBER_OF_CORES == 1 ) */
}
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configENABLE_MPU == 1 )

    ശൂന്യം vPortStoreTaskMPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    സ്ഥിരം ഘടന xMEMORY_REGION * സ്ഥിരം xRegions,
                                    അട്ടി_Type_t * px_Bottom_Of_അട്ടി,
                                    config_അട്ടി_DEPTH_TYPE ux_അട്ടി_Depth )
    {
        uint32_t ulRegionStartAddress, ulRegionEndAddress, ul_Region_സംഖ്യ;
        int32_t lIndex = 0;

        #എങ്കിൽ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ബാഹ്യ uint32_t * __privileged_sram_start__;
            ബാഹ്യ uint32_t * __privileged_sram_end__;
        #അല്ലെങ്കിൽ
            /* Declaration when these variable are exported from linker scripts. */
            ബാഹ്യ uint32_t __privileged_sram_start__[];
            ബാഹ്യ uint32_t __privileged_sram_end__[];
        #endif /* defined( __ARMCC_VERSION ) */

        /* Setup MAIR0. */
        xMPUSettings->ulMAIR0 = ( ( portMPU_NORMAL_MEMORY_BUFFERABLE_CACHEABLE << portMPU_MAIR_ATTR0_POS ) & portMPU_MAIR_ATTR0_MASK );
        xMPUSettings->ulMAIR0 |= ( ( portMPU_DEVICE_MEMORY_nGnRE << portMPU_MAIR_ATTR1_POS ) & portMPU_MAIR_ATTR1_MASK );

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid.  At all other
         * times the stack parameters will not be valid and it is assumed that
         * the stack region has already been configured. */
        എങ്കിൽ( ux_അട്ടി_Depth > 0 )
        {
            ulRegionStartAddress = ( uint32_t ) px_Bottom_Of_അട്ടി;
            ulRegionEndAddress = ( uint32_t ) px_Bottom_Of_അട്ടി + ( ux_അട്ടി_Depth * ( config_അട്ടി_DEPTH_TYPE ) വലുപ്പം( അട്ടി_Type_t ) ) - 1;

            /* If the stack is within the privileged SRAM, do not protect it
             * using a separate MPU region. This is needed because privileged
             * SRAM is already protected using an MPU region and ARMv8-M does
             * not allow overlapping MPU regions. */
            എങ്കിൽ( ( ulRegionStartAddress >= ( uint32_t ) __privileged_sram_start__ ) &&
                ( ulRegionEndAddress <= ( uint32_t ) __privileged_sram_end__ ) )
            {
                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR = 0;
                xMPUSettings->xRegionsSettings[ 0 ].ulRLAR = 0;
            }
            അല്ലെങ്കിൽ
            {
                /* Define the region that allows access to the stack. */
                ulRegionStartAddress &= portMPU_RBAR_ADDRESS_MASK;
                ulRegionEndAddress &= portMPU_RLAR_ADDRESS_MASK;

                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR = ( ulRegionStartAddress ) |
                                                             ( portMPU_REGION_NON_SHAREABLE ) |
                                                             ( portMPU_REGION_READ_WRITE ) |
                                                             ( portMPU_REGION_EXECUTE_NEVER );

                xMPUSettings->xRegionsSettings[ 0 ].ulRLAR = ( ulRegionEndAddress ) |
                                                             ( portMPU_RLAR_ATTR_INDEX0 ) |
                                                             ( portMPU_RLAR_REGION_ENABLE );
            }
        }

        /* User supplied configurable regions. */
        വേണ്ടി( ul_Region_സംഖ്യ = 1; ul_Region_സംഖ്യ <= port_അക്കം_CONFIGURABLE_REGIONS; ul_Region_സംഖ്യ++ )
        {
            /* If xRegions is NULL i.e. the task has not specified any MPU
             * region, the else part ensures that all the configurable MPU
             * regions are invalidated. */
            എങ്കിൽ( ( xRegions != ശൂന്യ ) && ( xRegions[ lIndex ].ulLengthInBytes > 0UL ) )
            {
                /* Translate the generic region definition contained in xRegions
                 * into the ARMv8 specific MPU settings that are then stored in
                 * xMPUSettings. */
                ulRegionStartAddress = ( ( uint32_t ) xRegions[ lIndex ].pvBaseAddress ) & portMPU_RBAR_ADDRESS_MASK;
                ulRegionEndAddress = ( uint32_t ) xRegions[ lIndex ].pvBaseAddress + xRegions[ lIndex ].ulLengthInBytes - 1;
                ulRegionEndAddress &= portMPU_RLAR_ADDRESS_MASK;

                /* Start address. */
                xMPUSettings->xRegionsSettings[ ul_Region_സംഖ്യ ].ulRBAR = ( ulRegionStartAddress ) |
                                                                          ( portMPU_REGION_NON_SHAREABLE );

                /* RO/RW. */
                എങ്കിൽ( ( xRegions[ lIndex ].ulParameters & tskMPU_REGION_READ_ONLY ) != 0 )
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_സംഖ്യ ].ulRBAR |= ( portMPU_REGION_READ_ONLY );
                }
                അല്ലെങ്കിൽ
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_സംഖ്യ ].ulRBAR |= ( portMPU_REGION_READ_WRITE );
                }

                /* XN. */
                എങ്കിൽ( ( xRegions[ lIndex ].ulParameters & tskMPU_REGION_EXECUTE_NEVER ) != 0 )
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_സംഖ്യ ].ulRBAR |= ( portMPU_REGION_EXECUTE_NEVER );
                }

                /* End Address. */
                xMPUSettings->xRegionsSettings[ ul_Region_സംഖ്യ ].ulRLAR = ( ulRegionEndAddress ) |
                                                                          ( portMPU_RLAR_REGION_ENABLE );

                /* PXN. */
                #എങ്കിൽ ( portARMV8M_MINOR_VERSION >= 1 )
                {
                    എങ്കിൽ( ( xRegions[ lIndex ].ulParameters & tskMPU_REGION_PRIVILEGED_EXECUTE_NEVER ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ ul_Region_സംഖ്യ ].ulRLAR |= ( portMPU_RLAR_PRIVILEGED_EXECUTE_NEVER );
                    }
                }
                #endif /* portARMV8M_MINOR_VERSION >= 1 */

                /* Normal memory/ Device memory. */
                എങ്കിൽ( ( xRegions[ lIndex ].ulParameters & tskMPU_REGION_DEVICE_MEMORY ) != 0 )
                {
                    /* Attr1 in MAIR0 is configured as device memory. */
                    xMPUSettings->xRegionsSettings[ ul_Region_സംഖ്യ ].ulRLAR |= portMPU_RLAR_ATTR_INDEX1;
                }
                അല്ലെങ്കിൽ
                {
                    /* Attr0 in MAIR0 is configured as normal memory. */
                    xMPUSettings->xRegionsSettings[ ul_Region_സംഖ്യ ].ulRLAR |= portMPU_RLAR_ATTR_INDEX0;
                }
            }
            അല്ലെങ്കിൽ
            {
                /* Invalidate the region. */
                xMPUSettings->xRegionsSettings[ ul_Region_സംഖ്യ ].ulRBAR = 0UL;
                xMPUSettings->xRegionsSettings[ ul_Region_സംഖ്യ ].ulRLAR = 0UL;
            }

            lIndex++;
        }
    }

#endif /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    BaseType_t xPortIsAuthorizedToAccessBuffer( സ്ഥിരം ശൂന്യം * pvBuffer,
                                                size_t xBufferLength,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ulBufferStartAddress, ulBufferEndAddress;
        BaseType_t xAccessGranted = pdFALSE;
        സ്ഥിരം xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ശൂന്യ ); /* Calling task's MPU settings. */

        എങ്കിൽ( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        അല്ലെങ്കിൽ എങ്കിൽ( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        അല്ലെങ്കിൽ
        {
            എങ്കിൽ( portADD_UINT32_WILL_OVERFLOW( ( ( uint32_t ) pvBuffer ), ( ( uint32_t ) xBufferLength - 1UL ) ) == pdFALSE )
            {
                ulBufferStartAddress = ( uint32_t ) pvBuffer;
                ulBufferEndAddress = ( ( ( uint32_t ) pvBuffer ) + ( uint32_t ) xBufferLength - 1UL );

                വേണ്ടി( i = 0; i < port_TOTAL_അക്കം_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    എങ്കിൽ( ( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR & portMPU_RLAR_REGION_ENABLE ) == portMPU_RLAR_REGION_ENABLE )
                    {
                        എങ്കിൽ( portIS_ADDRESS_WITHIN_RANGE( ulBufferStartAddress,
                                                         portEXTRACT_FIRST_ADDRESS_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ),
                                                         portEXTRACT_LAST_ADDRESS_FROM_RLAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR ) ) &&
                            portIS_ADDRESS_WITHIN_RANGE( ulBufferEndAddress,
                                                         portEXTRACT_FIRST_ADDRESS_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ),
                                                         portEXTRACT_LAST_ADDRESS_FROM_RLAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR ) ) &&
                            portIS_AUTHORIZED( ulAccessRequested,
                                               prvGetRegionAccessPermissions( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ) ) )
                        {
                            xAccessGranted = pdTRUE;
                            നിർത്തുക;
                        }
                    }
                }
            }
        }

        തിരികെ xAccessGranted;
    }

#endif /* #if ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

BaseType_t xPortIsInsideInterrupt( ശൂന്യം )
{
    uint32_t ulCurrentInterrupt;
    BaseType_t xReturn;

    /* Obtain the number of the currently executing interrupt. Interrupt Program
     * Status Register (IPSR) holds the exception number of the currently-executing
     * exception or zero for Thread mode.*/
    __asm അസ്ഥിര ( "mrs %0, ipsr" : "=r" ( ulCurrentInterrupt )::"memory" );

    എങ്കിൽ( ulCurrentInterrupt == 0 )
    {
        xReturn = pdFALSE;
    }
    അല്ലെങ്കിൽ
    {
        xReturn = pdTRUE;
    }

    തിരികെ xReturn;
}
/*-----------------------------------------------------------*/

#എങ്കിൽ ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) )

    ശൂന്യം vPortValidateInterruptPriority( ശൂന്യം )
    {
        uint32_t ulCurrentInterrupt;
        uint8_t ucCurrentPriority;

        /* Obtain the number of the currently executing interrupt. */
        __asm അസ്ഥിര ( "mrs %0, ipsr" : "=r" ( ulCurrentInterrupt )::"memory" );

        /* Is the interrupt number a user defined interrupt? */
        എങ്കിൽ( ulCurrentInterrupt >= port_FIRST_USER_INTERRUPT_സംഖ്യ )
        {
            /* Look up the interrupt's priority. */
            ucCurrentPriority = pcInterruptPriorityRegisters[ ulCurrentInterrupt ];

            /* The following assertion will fail if a service routine (ISR) for
             * an interrupt that has been assigned a priority above
             * configMAX_SYSCALL_INTERRUPT_PRIORITY calls an ISR safe FreeRTOS API
             * function.  ISR safe FreeRTOS API functions must *only* be called
             * from interrupts that have been assigned a priority at or below
             * configMAX_SYSCALL_INTERRUPT_PRIORITY.
             *
             * Numerically low interrupt priority numbers represent logically high
             * interrupt priorities, therefore the priority of the interrupt must
             * be set to a value equal to or numerically *higher* than
             * configMAX_SYSCALL_INTERRUPT_PRIORITY.
             *
             * Interrupts that  use the FreeRTOS API must not be left at their
             * default priority of  zero as that is the highest possible priority,
             * which is guaranteed to be above configMAX_SYSCALL_INTERRUPT_PRIORITY,
             * and  therefore also guaranteed to be invalid.
             *
             * FreeRTOS maintains separate thread and ISR API functions to ensure
             * interrupt entry is as fast and simple as possible.
             *
             * The following links provide detailed information:
             * https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html
             * https://www.freertos.org/Why-FreeRTOS/FAQs */
            configASSERT( ucCurrentPriority >= ucMaxSysCallPriority );
        }

        /* Priority grouping:  The interrupt controller (NVIC) allows the bits
         * that define each interrupt's priority to be split between bits that
         * define the interrupt's pre-emption priority bits and bits that define
         * the interrupt's sub-priority.  For simplicity all bits must be defined
         * to be pre-emption priority bits.  The following assertion will fail if
         * this is not the case (if some bits represent a sub-priority).
         *
         * If the application only uses CMSIS libraries for interrupt
         * configuration then the correct setting can be achieved on all Cortex-M
         * devices by calling NVIC_SetPriorityGrouping( 0 ); before starting the
         * scheduler.  Note however that some vendor specific peripheral libraries
         * assume a non-zero priority group setting, in which cases using a value
         * of zero will result in unpredictable behaviour. */
        configASSERT( ( portAIRCR_REG & portPRIORITY_GROUP_MASK ) <= ulMaxPRIGROUPValue );
    }

#endif /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */
/*-----------------------------------------------------------*/

ശൂന്യം vPortConfigureInterruptPriorities( ശൂന്യം ) /* PRIVILEGED_FUNCTION */
{
    #എങ്കിൽ ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) )
    {
        അസ്ഥിര uint32_t ulImplementedPrioBits = 0;
        അസ്ഥിര uint8_t uc_Max_Priority_മൂല്യം;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
        * functions can be called. ISR safe functions are those that end in
        * "FromISR". FreeRTOS maintains separate thread and ISR API functions to
        * ensure interrupt entry is as fast and simple as possible.
        *
        * First, determine the number of priority bits available. Write to all
        * possible bits in the priority setting for SVCall. */
        portNVIC_SHPR2_REG = 0xFF000000;

        /* Read the value back to see how many bits stuck. */
        uc_Max_Priority_മൂല്യം = ( uint8_t ) ( ( portNVIC_SHPR2_REG & 0xFF000000 ) >> 24 );

        /* Use the same mask on the maximum system call priority. */
        ucMaxSysCallPriority = configMAX_SYSCALL_INTERRUPT_PRIORITY & uc_Max_Priority_മൂല്യം;

        /* Check that the maximum system call priority is nonzero after
        * accounting for the number of priority bits supported by the
        * hardware. A priority of 0 is invalid because setting the BASEPRI
        * register to 0 unmasks all interrupts, and interrupts with priority 0
        * cannot be masked using BASEPRI.
        * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( ucMaxSysCallPriority );

        /* Check that the bits not implemented in hardware are zero in
        * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( configMAX_SYSCALL_INTERRUPT_PRIORITY & ( uint8_t ) ( ~( uint32_t ) uc_Max_Priority_മൂല്യം ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
        * of bits read back. */
        ആകുമ്പോൾ( ( uc_Max_Priority_മൂല്യം & port_മുകൾ_BIT_OF_BYTE ) == port_മുകൾ_BIT_OF_BYTE )
        {
            ulImplementedPrioBits++;
            uc_Max_Priority_മൂല്യം <<= ( uint8_t ) 0x01;
        }

        എങ്കിൽ( ulImplementedPrioBits == 8 )
        {
            /* When the hardware implements 8 priority bits, there is no way for
            * the software to configure PRIGROUP to not have sub-priorities. As
            * a result, the least significant bit is always used for sub-priority
            * and there are 128 preemption priorities and 2 sub-priorities.
            *
            * This may cause some confusion in some cases - for example, if
            * configMAX_SYSCALL_INTERRUPT_PRIORITY is set to 5, both 5 and 4
            * priority interrupts will be masked in Critical Sections as those
            * are at the same preemption priority. This may appear confusing as
            * 4 is higher (numerically lower) priority than
            * configMAX_SYSCALL_INTERRUPT_PRIORITY and therefore, should not
            * have been masked. Instead, if we set configMAX_SYSCALL_INTERRUPT_PRIORITY
            * to 4, this confusion does not happen and the behaviour remains the same.
            *
            * The following assert ensures that the sub-priority bit in the
            * configMAX_SYSCALL_INTERRUPT_PRIORITY is clear to avoid the above mentioned
            * confusion. */
            configASSERT( ( configMAX_SYSCALL_INTERRUPT_PRIORITY & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        അല്ലെങ്കിൽ
        {
            ulMaxPRIGROUPValue = portMAX_PRIGROUP_BITS - ulImplementedPrioBits;
        }

        /* Shift the priority group value back to its position within the AIRCR
        * register. */
        ulMaxPRIGROUPValue <<= portPRIGROUP_SHIFT;
        ulMaxPRIGROUPValue &= portPRIORITY_GROUP_MASK;
    }
    #endif /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */

    /* Make PendSV and SysTick the lowest priority interrupts, and make SVCall
    * the highest priority. */
    portNVIC_SHPR3_REG |= portNVIC_PENDSV_PRI;
    portNVIC_SHPR3_REG |= portNVIC_SYSTICK_PRI;
    portNVIC_SHPR2_REG = 0;
}
/*-----------------------------------------------------------*/

#എങ്കിൽ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    ശൂന്യം vPortGrantAccessToKernelObject( TaskHandle_t xInternalTaskHandle,
                                         int32_t lInternalIndexOfKernelObject ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ulAccessControlListEntryIndex, ulAccessControlListEntryBit;
        xMPU_SETTINGS * xTaskMpuSettings;

        ulAccessControlListEntryIndex = ( ( uint32_t ) lInternalIndexOfKernelObject / portACL_ENTRY_SIZE_BITS );
        ulAccessControlListEntryBit = ( ( uint32_t ) lInternalIndexOfKernelObject % portACL_ENTRY_SIZE_BITS );

        xTaskMpuSettings = xTaskGetMPUSettings( xInternalTaskHandle );

        xTaskMpuSettings->ulAccessControlList[ ulAccessControlListEntryIndex ] |= ( 1U << ulAccessControlListEntryBit );
    }

#endif /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    ശൂന്യം vPortRevokeAccessToKernelObject( TaskHandle_t xInternalTaskHandle,
                                          int32_t lInternalIndexOfKernelObject ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ulAccessControlListEntryIndex, ulAccessControlListEntryBit;
        xMPU_SETTINGS * xTaskMpuSettings;

        ulAccessControlListEntryIndex = ( ( uint32_t ) lInternalIndexOfKernelObject / portACL_ENTRY_SIZE_BITS );
        ulAccessControlListEntryBit = ( ( uint32_t ) lInternalIndexOfKernelObject % portACL_ENTRY_SIZE_BITS );

        xTaskMpuSettings = xTaskGetMPUSettings( xInternalTaskHandle );

        xTaskMpuSettings->ulAccessControlList[ ulAccessControlListEntryIndex ] &= ~( 1U << ulAccessControlListEntryBit );
    }

#endif /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #എങ്കിൽ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        BaseType_t xPortIsAuthorizedToAccessKernelObject( int32_t lInternalIndexOfKernelObject ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulAccessControlListEntryIndex, ulAccessControlListEntryBit;
            BaseType_t xAccessGranted = pdFALSE;
            സ്ഥിരം xMPU_SETTINGS * xTaskMpuSettings;

            എങ്കിൽ( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            അല്ലെങ്കിൽ
            {
                xTaskMpuSettings = xTaskGetMPUSettings( ശൂന്യ ); /* Calling task's MPU settings. */

                ulAccessControlListEntryIndex = ( ( uint32_t ) lInternalIndexOfKernelObject / portACL_ENTRY_SIZE_BITS );
                ulAccessControlListEntryBit = ( ( uint32_t ) lInternalIndexOfKernelObject % portACL_ENTRY_SIZE_BITS );

                എങ്കിൽ( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                അല്ലെങ്കിൽ
                {
                    എങ്കിൽ( ( xTaskMpuSettings->ulAccessControlList[ ulAccessControlListEntryIndex ] & ( 1U << ulAccessControlListEntryBit ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            തിരികെ xAccessGranted;
        }

    #അല്ലെങ്കിൽ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        BaseType_t xPortIsAuthorizedToAccessKernelObject( int32_t lInternalIndexOfKernelObject ) /* PRIVILEGED_FUNCTION */
        {
            ( ശൂന്യം ) lInternalIndexOfKernelObject;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            തിരികെ pdTRUE;
        }

    #endif /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#endif /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
    #എങ്കിൽ ( config_സംഖ്യ_OF_CORES == 1 )
        സ്ഥിതം uint32_t prvConfigurePACBTI( BaseType_t xWriteControlRegister )
    #അല്ലെങ്കിൽ /* configNUMBER_OF_CORES > 1 */
        uint32_t vConfigurePACBTI( BaseType_t xWriteControlRegister )
    #endif /* configNUMBER_OF_CORES */
        {
            uint32_t ulControl = 0x0;

            /* Ensure that PACBTI is implemented. */
            configASSERT( portID_ISAR5_REG != 0x0 );

            /* Enable UsageFault exception. */
            portSCB_SYS_HANDLER_CTRL_STATE_REG |= portSCB_USG_FAULT_ENABLE_BIT;

            #എങ്കിൽ ( configENABLE_PAC == 1 )
            {
                ulControl |= ( portCONTROL_UPAC_EN | portCONTROL_PAC_EN );
            }
            #endif

            #എങ്കിൽ ( configENABLE_BTI == 1 )
            {
                ulControl |= ( portCONTROL_UBTI_EN | portCONTROL_BTI_EN );
            }
            #endif

            എങ്കിൽ( xWriteControlRegister == pdTRUE )
            {
                __asm അസ്ഥിര ( "msr control, %0" : : "r" ( ulControl ) );
            }

            തിരികെ ulControl;
        }

#endif /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( config_സംഖ്യ_OF_CORES > 1 )

    /* Which core owns the lock? */
    PRIVILEGED_DATA അസ്ഥിര uint32_t ulOwnedByCore[ port_MAX_CORE_എണ്ണം ];
    /* Lock count a core owns. */
    PRIVILEGED_DATA അസ്ഥിര uint32_t ul_Recursion_എണ്ണം_By_Lock[ e_Lock_എണ്ണം ];
    /* Index 0 is used for ISR lock and Index 1 is used for task lock. */
    PRIVILEGED_DATA അസ്ഥിര uint32_t ulGateWord[ e_Lock_എണ്ണം ];

    __attribute__((weak)) ശൂന്യം vInterruptCore( uint8_t ucCoreID )
    {
        /* Default weak stub - platform specific implementation may override. */
        ( ശൂന്യം ) ucCoreID;
    }

/*-----------------------------------------------------------*/

    സ്ഥിതം വരിയിൽ ശൂന്യം prvSpinUnlock( അസ്ഥിര uint32_t * ulLock )
    {
        /* Conservative unlock: preserve original barriers for broad HW/FVP. */
        __asm അസ്ഥിര (
            "dmb sy         \n"
            "mov r1, #0     \n"
            "str r1, [%0]   \n"
            "sev            \n"
            "dsb            \n"
            "isb            \n"
            :
            : "r" ( ulLock )
            : "memory", "r1"
        );
    }

/*-----------------------------------------------------------*/

    സ്ഥിതം വരിയിൽ uint32_t prvSpinTrylock( അസ്ഥിര uint32_t * ulLock )
    {
        /*
         * Conservative ldrex/strex trylock:
         * - Return 1 immediately if busy, clearing exclusive state (CLREX).
         * - Retry strex only on spurious failure when observed free.
         * - DMB on success to preserve expected acquire semantics.
         */
        uint32_t ulVal;
        uint32_t ulStatus;

        __asm അസ്ഥിര (
            " ldrex %0, [%1]   \n"
            : "=r" ( ulVal )
            : "r" ( ulLock )
            : "memory"
        );

        എങ്കിൽ( ulVal != 0U )
        {
            __asm അസ്ഥിര ("clrex" ::: "memory");
            തിരികെ 1U;
        }

        __asm അസ്ഥിര (
            " strex %0, %2, [%1]   \n"
            : "=&r" ( ulStatus )
            : "r" ( ulLock ), "r" (1U)
            : "memory"
        );

        എങ്കിൽ( ulStatus != 0U )
        {
            തിരികെ 1U;
        }
        __asm അസ്ഥിര ( "dmb" ::: "memory" );
        തിരികെ 0U;
    }


/*-----------------------------------------------------------*/

    /* Read 32b value shared between cores. */
    സ്ഥിതം വരിയിൽ uint32_t prvGet32( അസ്ഥിര uint32_t * x )
    {
        __asm( "dsb" );
        തിരികെ *x;
    }

/*-----------------------------------------------------------*/

    /* Write 32b value shared between cores. */
    സ്ഥിതം വരിയിൽ ശൂന്യം prvSet32( അസ്ഥിര uint32_t * x,
                                 uint32_t മൂല്യം )
    {
        *x = മൂല്യം;
        __asm( "dsb" );
    }

/*-----------------------------------------------------------*/

    ശൂന്യം vPortRecursiveLock( uint8_t ucCoreID,
                             ePortRTOSLock e_Lock_അക്കം,
                             BaseType_t uxAcquire )
    {
        /* Validate the core ID and lock number. */
        configASSERT( ucCoreID < port_MAX_CORE_എണ്ണം );
        configASSERT( e_Lock_അക്കം < e_Lock_എണ്ണം );

        uint32_t ulLockBit = 1u << e_Lock_അക്കം;

        /* Lock acquire */
        എങ്കിൽ( uxAcquire )
        {
            /* Check if spinlock is available. */
            /* If spinlock is not available check if the core owns the lock. */
            /* If the core owns the lock wait increment the lock count by the core. */
            /* If core does not own the lock wait for the spinlock. */
            എങ്കിൽ( prvSpinTrylock( &ulGateWord[ e_Lock_അക്കം ] ) != 0 )
            {
                /* Check if the core owns the spinlock. */
                എങ്കിൽ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ulLockBit )
                {
                    configASSERT( prvGet32( &ul_Recursion_എണ്ണം_By_Lock[ e_Lock_അക്കം ] ) != portUINT32_MAX );
                    prvSet32( &ul_Recursion_എണ്ണം_By_Lock[ e_Lock_അക്കം ], ( prvGet32( &ul_Recursion_എണ്ണം_By_Lock[ e_Lock_അക്കം ] ) + 1 ) );
                    തിരികെ;
                }

                /* Preload the gate word into the cache. */
                uint32_t dummy = ulGateWord[ e_Lock_അക്കം ];
                dummy++;

                ആകുമ്പോൾ( prvSpinTrylock( &ulGateWord[ e_Lock_അക്കം ] ) != 0 )
                {
                    __asm അസ്ഥിര ( "wfe" );
                }
            }

            /* Add barrier to ensure lock is taken before we proceed. */
            __asm അസ്ഥിര( "dmb sy" ::: "memory" );

            /* Assert the lock count is 0 when the spinlock is free and is acquired. */
            configASSERT( prvGet32( &ul_Recursion_എണ്ണം_By_Lock[ e_Lock_അക്കം ] ) == 0 );

            /* Set lock count as 1. */
            prvSet32( &ul_Recursion_എണ്ണം_By_Lock[ e_Lock_അക്കം ], 1 );
            /* Set ulOwnedByCore. */
            prvSet32( &ulOwnedByCore[ ucCoreID ], ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) | ulLockBit ) );
        }
        /* Lock release. */
        അല്ലെങ്കിൽ
        {
            /* Assert the lock is not free already. */
            configASSERT( ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ulLockBit ) != 0 );
            configASSERT( prvGet32( &ul_Recursion_എണ്ണം_By_Lock[ e_Lock_അക്കം ] ) != 0 );

            /* Reduce ulRecursionCountByLock by 1. */
            prvSet32( &ul_Recursion_എണ്ണം_By_Lock[ e_Lock_അക്കം ], ( prvGet32( &ul_Recursion_എണ്ണം_By_Lock[ e_Lock_അക്കം ] ) - 1 ) );

            എങ്കിൽ( !prvGet32( &ul_Recursion_എണ്ണം_By_Lock[ e_Lock_അക്കം ] ) )
            {
                prvSet32( &ulOwnedByCore[ ucCoreID ], ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ~ulLockBit ) );
                prvSpinUnlock( &ulGateWord[ e_Lock_അക്കം ] );
                /* Add barrier to ensure lock status is reflected before we proceed. */
                __asm അസ്ഥിര( "dmb sy" ::: "memory" );
            }
        }
    }

/*-----------------------------------------------------------*/

    uint8_t ucPortGetCoreID( ശൂന്യം )
    {
        തിരികെ *(അസ്ഥിര uint8_t *)(configCORE_ID_REGISTER);
    }

/*-----------------------------------------------------------*/

#endif /* if( configNUMBER_OF_CORES > 1 ) */
