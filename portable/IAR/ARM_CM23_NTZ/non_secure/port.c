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
#અન્તર્ભાવ "FreeRTOS.h"
#અન્તર્ભાવ "task.h"

/* MPU includes. */
#અન્તર્ભાવ "mpu_wrappers.h"
#અન્તર્ભાવ "mpu_syscall_numbers.h"

/* Portasm includes. */
#અન્તર્ભાવ "portasm.h"

#જો ( configENABLE_TRUSTZONE == 1 )
    /* Secure components includes. */
    #અન્તર્ભાવ "secure_context.h"
    #અન્તર્ભાવ "secure_init.h"
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
#જો ( ( configRUN_FREERTOS_SECURE_ONLY == 1 ) && ( configENABLE_TRUSTZONE == 1 ) )
    #error TrustZone needs to be disabled in order to run FreeRTOS on the Secure Side.
#endif

/**
 * Cortex-M23 does not have non-secure PSPLIM. We should use PSPLIM on Cortex-M23
 * only when FreeRTOS runs on secure side.
 */
#જો ( ( portHAS_ARMV8M_MAIN_EXTENSION == 0 ) && ( configRUN_FREERTOS_SECURE_ONLY == 0 ) )
    #define portUSE_PSPLIM_REGISTER    0
#નહીંતર
    #define portUSE_PSPLIM_REGISTER    1
#endif
/*-----------------------------------------------------------*/

/**
 * @brief Prototype of all Interrupt Service Routines (ISRs).
 */
પ્રકારવ્યાખ્યા શૂન્ય ( * portISR_t )( શૂન્ય );
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the NVIC.
 */
#define portNVIC_SYSTICK_CTRL_REG             ( *( ( અસ્થિર uint32_t * ) 0xe000e010 ) )
#define portNVIC_SYSTICK_LOAD_REG             ( *( ( અસ્થિર uint32_t * ) 0xe000e014 ) )
#define port_NVIC_SYSTICK_CURRENT_કિંમત_REG    ( *( ( અસ્થિર uint32_t * ) 0xe000e018 ) )
#define portNVIC_SHPR3_REG                    ( *( ( અસ્થિર uint32_t * ) 0xe000ed20 ) )
#define portNVIC_SYSTICK_ENABLE_BIT           ( 1UL << 0UL )
#define portNVIC_SYSTICK_INT_BIT              ( 1UL << 1UL )
#define portNVIC_SYSTICK_CLK_BIT              ( 1UL << 2UL )
#define port_NVIC_SYSTICK_ગણતરી_FLAG_BIT       ( 1UL << 16UL )
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
#define portSCB_SYS_HANDLER_CTRL_STATE_REG    ( *( ( અસ્થિર uint32_t * ) 0xe000ed24 ) )
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
#define portNVIC_SHPR2_REG                 ( *( ( અસ્થિર uint32_t * ) 0xE000ED1C ) )
#define port_FIRST_USER_INTERRUPT_સંખ્યા    ( 16 )
#define portNVIC_IP_REGISTERS_OFFSET_16    ( 0xE000E3F0 )
#define portAIRCR_REG                      ( *( ( અસ્થિર uint32_t * ) 0xE000ED0C ) )
#define port_ટોચ_BIT_OF_BYTE                ( ( uint8_t ) 0x80 )
#define portMAX_PRIGROUP_BITS              ( ( uint8_t ) 7 )
#define portPRIORITY_GROUP_MASK            ( 0x07UL << 8UL )
#define portPRIGROUP_SHIFT                 ( 8UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants used during system call enter and exit.
 */
#define port_PSR_ઢગલો_PADDING_MASK              ( 1UL << 9UL )
#define port_EXC_RETURN_ઢગલો_FRAME_TYPE_MASK    ( 1UL << 4UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the FPU.
 */
#define portCPACR               ( ( અસ્થિર uint32_t * ) 0xe000ed88 ) /* Coprocessor Access Control Register. */
#define port_CPACR_CP10_કિંમત    ( 3UL )
#define port_CPACR_CP11_કિંમત    port_CPACR_CP10_કિંમત
#define portCPACR_CP10_POS      ( 20UL )
#define portCPACR_CP11_POS      ( 22UL )

#define portFPCCR               ( ( અસ્થિર uint32_t * ) 0xe000ef34 ) /* Floating Point Context Control Register. */
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
#define portMPU_TYPE_REG                        ( *( ( અસ્થિર uint32_t * ) 0xe000ed90 ) )
#define portMPU_CTRL_REG                        ( *( ( અસ્થિર uint32_t * ) 0xe000ed94 ) )
#define portMPU_RNR_REG                         ( *( ( અસ્થિર uint32_t * ) 0xe000ed98 ) )

#define portMPU_RBAR_REG                        ( *( ( અસ્થિર uint32_t * ) 0xe000ed9c ) )
#define portMPU_RLAR_REG                        ( *( ( અસ્થિર uint32_t * ) 0xe000eda0 ) )

#define portMPU_RBAR_A1_REG                     ( *( ( અસ્થિર uint32_t * ) 0xe000eda4 ) )
#define portMPU_RLAR_A1_REG                     ( *( ( અસ્થિર uint32_t * ) 0xe000eda8 ) )

#define portMPU_RBAR_A2_REG                     ( *( ( અસ્થિર uint32_t * ) 0xe000edac ) )
#define portMPU_RLAR_A2_REG                     ( *( ( અસ્થિર uint32_t * ) 0xe000edb0 ) )

#define portMPU_RBAR_A3_REG                     ( *( ( અસ્થિર uint32_t * ) 0xe000edb4 ) )
#define portMPU_RLAR_A3_REG                     ( *( ( અસ્થિર uint32_t * ) 0xe000edb8 ) )

#define portMPU_MAIR0_REG                       ( *( ( અસ્થિર uint32_t * ) 0xe000edc0 ) )
#define portMPU_MAIR1_REG                       ( *( ( અસ્થિર uint32_t * ) 0xe000edc4 ) )

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

#જો ( portARMV8M_MINOR_VERSION >= 1 )

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
#define port_MAX_24_BIT_સંખ્યા       ( 0xffffffUL )

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

#જો ( configRUN_FREERTOS_SECURE_ONLY == 1 )

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
#નહીંતર

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
#નહીંતર
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
#નહીંતર
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
#જો ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )

    #define portID_ISAR5_REG       ( *( ( અસ્થિર uint32_t * ) 0xe000ed74 ) )

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
સ્થિર શૂન્ય prvTaskExitError( શૂન્ય );

#જો ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Extract MPU region's access permissions from the Region Base Address
     * Register (RBAR) value.
     *
     * @param ulRBARValue RBAR value for the MPU region.
     *
     * @return uint32_t Access permissions.
     */
    સ્થિર uint32_t prvGetRegionAccessPermissions( uint32_t ulRBARValue ) PRIVILEGED_FUNCTION;
#endif /* configENABLE_MPU == 1 && configUSE_MPU_WRAPPERS_V1 == 0 */

#જો ( configENABLE_MPU == 1 )

    /**
     * @brief Setup the Memory Protection Unit (MPU).
     */
    સ્થિર શૂન્ય prvSetupMPU( શૂન્ય ) PRIVILEGED_FUNCTION;
#endif /* configENABLE_MPU */

#જો ( configENABLE_FPU == 1 )

    /**
     * @brief Setup the Floating Point Unit (FPU).
     */
    સ્થિર શૂન્ય prvSetupFPU( શૂન્ય ) PRIVILEGED_FUNCTION;
#endif /* configENABLE_FPU */

#જો ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )

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
    #જો ( config_સંખ્યા_OF_CORES == 1 )
        સ્થિર uint32_t prvConfigurePACBTI( BaseType_t xWriteControlRegister );
    #નહીંતર /* #if ( configNUMBER_OF_CORES == 1 ) */
        uint32_t vConfigurePACBTI( BaseType_t xWriteControlRegister );
    #endif /* #if ( configNUMBER_OF_CORES == 1 ) */

#endif /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

/**
 * @brief Setup the timer to generate the tick interrupts.
 *
 * The implementation in this file is weak to allow application writers to
 * change the timer used to generate the tick interrupt.
 */
શૂન્ય vPortSetupTimerInterrupt( શૂન્ય ) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether the current execution context is interrupt.
 *
 * @return pdTRUE if the current execution context is interrupt, pdFALSE
 * otherwise.
 */
BaseType_t xPortIsInsideInterrupt( શૂન્ય );

/**
 * @brief Yield the processor.
 */
શૂન્ય vPortYield( શૂન્ય ) PRIVILEGED_FUNCTION;

/**
 * @brief Enter critical section.
 */
શૂન્ય vPortEnterCritical( શૂન્ય ) PRIVILEGED_FUNCTION;

/**
 * @brief Exit from critical section.
 */
શૂન્ય vPortExitCritical( શૂન્ય ) PRIVILEGED_FUNCTION;

/**
 * @brief SysTick handler.
 */
શૂન્ય SysTick_Handler( શૂન્ય ) PRIVILEGED_FUNCTION;

/**
 * @brief C part of SVC handler.
 */
portDONT_DISCARD શૂન્ય vPortSVCHandler_C( uint32_t * pul_Caller_ઢગલો_Address ) PRIVILEGED_FUNCTION;

#જો ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the system call stack so that upon returning from
     * SVC, the system call stack is used.
     *
     * @param pulTaskStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    શૂન્ય vSystemCallEnter( uint32_t * pul_Task_ઢગલો,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_સંખ્યા ) PRIVILEGED_FUNCTION;

#endif /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#જો ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    શૂન્ય vRequestSystemCallExit( શૂન્ય ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#endif /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#જો ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param pulSystemCallStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     */
    શૂન્ય vSystemCallExit( uint32_t * pul_System_Call_ઢગલો,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#endif /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#જો ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    BaseType_t xPortIsTaskPrivileged( શૂન્ય ) PRIVILEGED_FUNCTION;

#endif /* configENABLE_MPU == 1 */

#જો ( config_સંખ્યા_OF_CORES > 1 )

    /**
     * @brief Platform/Application-defined function that wakes up the secondary cores.
     *
     * @return pdTRUE if the secondary cores were successfully woken up.
     *         pdFALSE otherwise.
     */
    બાહ્ય BaseType_t configWAKE_SECONDARY_CORES( શૂન્ય );

#endif /* #if ( configNUMBER_OF_CORES > 1 ) */

/**
 * @brief Configures interrupt priorities.
 */
શૂન્ય vPortConfigureInterruptPriorities( શૂન્ય ) PRIVILEGED_FUNCTION;
/*-----------------------------------------------------------*/

#જો ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief This variable is set to pdTRUE when the scheduler is started.
     */
    PRIVILEGED_DATA સ્થિર BaseType_t xSchedulerRunning = pdFALSE;

#endif /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/**
 * @brief Each task maintains its own interrupt status in the critical nesting
 * variable.
 */
#જો ( config_સંખ્યા_OF_CORES == 1 )
    PRIVILEGED_DATA સ્થિર અસ્થિર uint32_t ulCriticalNesting = 0UL;
#નહીંતર /* #if ( configNUMBER_OF_CORES == 1 ) */
    PRIVILEGED_DATA અસ્થિર uint32_t ulCriticalNestings[ config_સંખ્યા_OF_CORES ] = { 0 };
    /* Flags to check if the secondary cores are ready. */
    PRIVILEGED_DATA અસ્થિર uint8_t ucSecondaryCoresReadyFlags[ config_સંખ્યા_OF_CORES - 1 ] = { 0 };
    /* Flag to indicate that the primary core has completed its initialisation. */
    PRIVILEGED_DATA અસ્થિર uint8_t ucPrimaryCoreInitDoneFlag = 0;
 #endif /* #if ( configNUMBER_OF_CORES == 1 ) */

#જો ( configENABLE_TRUSTZONE == 1 )

    /**
     * @brief Saved as part of the task context to indicate which context the
     * task is using on the secure side.
     */
    PRIVILEGED_DATA portDONT_DISCARD અસ્થિર SecureContextHandle_t xSecureContext = portNO_SECURE_CONTEXT;
#endif /* configENABLE_TRUSTZONE */

/**
 * @brief Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#જો ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) )

    સ્થિર uint8_t ucMaxSysCallPriority = 0;
    સ્થિર uint32_t ulMaxPRIGROUPValue = 0;
    સ્થિર અચલ અસ્થિર uint8_t * અચલ pcInterruptPriorityRegisters = ( અચલ અસ્થિર uint8_t * ) portNVIC_IP_REGISTERS_OFFSET_16;

#endif /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */

#જો ( configUSE_TICKLESS_IDLE == 1 )

    /**
     * @brief The number of SysTick increments that make up one tick period.
     */
    PRIVILEGED_DATA સ્થિર uint32_t ulTimerCountsForOneTick = 0;

    /**
     * @brief The maximum number of tick periods that can be suppressed is
     * limited by the 24 bit resolution of the SysTick timer.
     */
    PRIVILEGED_DATA સ્થિર uint32_t xMaximumPossibleSuppressedTicks = 0;

    /**
     * @brief Compensate for the CPU cycles that pass while the SysTick is
     * stopped (low power functionality only).
     */
    PRIVILEGED_DATA સ્થિર uint32_t ulStoppedTimerCompensation = 0;
#endif /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

#જો ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) શૂન્ય vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime )
    {
        uint32_t ul_Reload_કિંમત, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_ડાબું;
        TickType_t xModifiableIdleTime;

        /* Make sure the SysTick reload value does not overflow the counter. */
        જો( xExpectedIdleTime > xMaximumPossibleSuppressedTicks )
        {
            xExpectedIdleTime = xMaximumPossibleSuppressedTicks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm અસ્થિર ( "cpsid i" ::: "memory" );
        __asm અસ્થિર ( "dsb" );
        __asm અસ્થિર ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        જો( eTaskConfirmSleepModeStatus() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the cpsid instruction
             * above. */
            __asm અસ્થિર ( "cpsie i" ::: "memory" );
        }
        નહીંતર
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
            ul_Sys_Tick_Decrements_ડાબું = port_NVIC_SYSTICK_CURRENT_કિંમત_REG;

            જો( ul_Sys_Tick_Decrements_ડાબું == 0 )
            {
                ul_Sys_Tick_Decrements_ડાબું = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_કિંમત = ul_Sys_Tick_Decrements_ડાબું + ( ulTimerCountsForOneTick * ( xExpectedIdleTime - 1UL ) );

            જો( ( portNVIC_INT_CTRL_REG & portNVIC_PEND_SYSTICK_SET_BIT ) != 0 )
            {
                portNVIC_INT_CTRL_REG = portNVIC_PEND_SYSTICK_CLEAR_BIT;
                ul_Reload_કિંમત -= ulTimerCountsForOneTick;
            }

            જો( ul_Reload_કિંમત > ulStoppedTimerCompensation )
            {
                ul_Reload_કિંમત -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            portNVIC_SYSTICK_LOAD_REG = ul_Reload_કિંમત;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            port_NVIC_SYSTICK_CURRENT_કિંમત_REG = 0UL;

            /* Restart SysTick. */
            portNVIC_SYSTICK_CTRL_REG |= portNVIC_SYSTICK_ENABLE_BIT;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            xModifiableIdleTime = xExpectedIdleTime;
            configPRE_SLEEP_PROCESSING( xModifiableIdleTime );

            જો( xModifiableIdleTime > 0 )
            {
                __asm અસ્થિર ( "dsb" ::: "memory" );
                __asm અસ્થિર ( "wfi" );
                __asm અસ્થિર ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( xExpectedIdleTime );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the cpsid instruction above. */
            __asm અસ્થિર ( "cpsie i" ::: "memory" );
            __asm અસ્થિર ( "dsb" );
            __asm અસ્થિર ( "isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm અસ્થિર ( "cpsid i" ::: "memory" );
            __asm અસ્થિર ( "dsb" );
            __asm અસ્થિર ( "isb" );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            portNVIC_SYSTICK_CTRL_REG = ( portNVIC_SYSTICK_CLK_BIT_CONFIG | portNVIC_SYSTICK_INT_BIT );

            /* Determine whether the SysTick has already counted to zero. */
            જો( ( portNVIC_SYSTICK_CTRL_REG & port_NVIC_SYSTICK_ગણતરી_FLAG_BIT ) != 0 )
            {
                uint32_t ul_Calculated_Load_કિંમત;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_Load_કિંમત = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_કિંમત - port_NVIC_SYSTICK_CURRENT_કિંમત_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                જો( ( ul_Calculated_Load_કિંમત <= ulStoppedTimerCompensation ) || ( ul_Calculated_Load_કિંમત > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_Load_કિંમત = ( ulTimerCountsForOneTick - 1UL );
                }

                portNVIC_SYSTICK_LOAD_REG = ul_Calculated_Load_કિંમત;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = xExpectedIdleTime - 1UL;
            }
            નહીંતર
            {
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_ડાબું = port_NVIC_SYSTICK_CURRENT_કિંમત_REG;
                #જો ( portNVIC_SYSTICK_CLK_BIT_CONFIG != portNVIC_SYSTICK_CLK_BIT )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    જો( ul_Sys_Tick_Decrements_ડાબું == 0 )
                    {
                        ul_Sys_Tick_Decrements_ડાબું = ul_Reload_કિંમત;
                    }
                }
                #endif /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( xExpectedIdleTime * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_ડાબું;

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
            port_NVIC_SYSTICK_CURRENT_કિંમત_REG = 0UL;
            portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT;
            #જો ( portNVIC_SYSTICK_CLK_BIT_CONFIG == portNVIC_SYSTICK_CLK_BIT )
            {
                portNVIC_SYSTICK_LOAD_REG = ulTimerCountsForOneTick - 1UL;
            }
            #નહીંતર
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT;

                જો( ( portNVIC_SYSTICK_CTRL_REG & port_NVIC_SYSTICK_ગણતરી_FLAG_BIT ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    port_NVIC_SYSTICK_CURRENT_કિંમત_REG = 0;
                }

                portNVIC_SYSTICK_LOAD_REG = ulTimerCountsForOneTick - 1UL;
                portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT_CONFIG | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT;
            }
            #endif /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            vTaskStepTick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __asm અસ્થિર ( "cpsie i" ::: "memory" );
        }
    }

#endif /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

__attribute__( ( weak ) ) શૂન્ય vPortSetupTimerInterrupt( શૂન્ય ) /* PRIVILEGED_FUNCTION */
{
    /* Calculate the constants required to configure the tick interrupt. */
    #જો ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ );
        xMaximumPossibleSuppressedTicks = port_MAX_24_BIT_સંખ્યા / ulTimerCountsForOneTick;
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
    port_NVIC_SYSTICK_CURRENT_કિંમત_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    portNVIC_SYSTICK_LOAD_REG = ( configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL;
    portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT_CONFIG | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT;
}
/*-----------------------------------------------------------*/

સ્થિર શૂન્ય prvTaskExitError( શૂન્ય )
{
    અસ્થિર uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    #જો ( config_સંખ્યા_OF_CORES == 1 )
        configASSERT( ulCriticalNesting == ~0UL );
    #નહીંતર /* #if ( configNUMBER_OF_CORES == 1 ) */
        configASSERT( ulCriticalNestings[ portGET_CORE_ID() ] == ~0UL );
    #endif /* #if ( configNUMBER_OF_CORES == 1 ) */
    portDISABLE_INTERRUPTS();

    જ્યારે( ulDummy == 0 )
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

#જો ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    સ્થિર uint32_t prvGetRegionAccessPermissions( uint32_t ulRBARValue ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ulAccessPermissions = 0;

        જો( ( ulRBARValue & portMPU_RBAR_ACCESS_PERMISSIONS_MASK ) == portMPU_REGION_READ_ONLY )
        {
            ulAccessPermissions = tskMPU_READ_PERMISSION;
        }

        જો( ( ulRBARValue & portMPU_RBAR_ACCESS_PERMISSIONS_MASK ) == portMPU_REGION_READ_WRITE )
        {
            ulAccessPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
        }

        પાછા ulAccessPermissions;
    }

#endif /* configENABLE_MPU == 1 && configUSE_MPU_WRAPPERS_V1 == 0 */
/*-----------------------------------------------------------*/

#જો ( configENABLE_MPU == 1 )

    સ્થિર શૂન્ય prvSetupMPU( શૂન્ય ) /* PRIVILEGED_FUNCTION */
    {
        #જો defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            બાહ્ય uint32_t * __privileged_functions_start__;
            બાહ્ય uint32_t * __privileged_functions_end__;
            બાહ્ય uint32_t * __syscalls_flash_start__;
            બાહ્ય uint32_t * __syscalls_flash_end__;
            બાહ્ય uint32_t * __unprivileged_flash_start__;
            બાહ્ય uint32_t * __unprivileged_flash_end__;
            બાહ્ય uint32_t * __privileged_sram_start__;
            બાહ્ય uint32_t * __privileged_sram_end__;
        #નહીંતર /* if defined( __ARMCC_VERSION ) */
            /* Declaration when these variable are exported from linker scripts. */
            બાહ્ય uint32_t __privileged_functions_start__[];
            બાહ્ય uint32_t __privileged_functions_end__[];
            બાહ્ય uint32_t __syscalls_flash_start__[];
            બાહ્ય uint32_t __syscalls_flash_end__[];
            બાહ્ય uint32_t __unprivileged_flash_start__[];
            બાહ્ય uint32_t __unprivileged_flash_end__[];
            બાહ્ય uint32_t __privileged_sram_start__[];
            બાહ્ય uint32_t __privileged_sram_end__[];
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

#જો ( configENABLE_FPU == 1 )

    સ્થિર શૂન્ય prvSetupFPU( શૂન્ય ) /* PRIVILEGED_FUNCTION */
    {
        #જો ( configENABLE_TRUSTZONE == 1 )
        {
            /* Enable non-secure access to the FPU. */
            SecureInit_EnableNSFPUAccess();
        }
        #endif /* configENABLE_TRUSTZONE */

        /* CP10 = 11 ==> Full access to FPU i.e. both privileged and
         * unprivileged code should be able to access FPU. CP11 should be
         * programmed to the same value as CP10. */
        *( portCPACR ) |= ( ( port_CPACR_CP10_કિંમત << portCPACR_CP10_POS ) |
                            ( port_CPACR_CP11_કિંમત << portCPACR_CP11_POS )
                            );

        /* ASPEN = 1 ==> Hardware should automatically preserve floating point
         * context on exception entry and restore on exception return.
         * LSPEN = 1 ==> Enable lazy context save of FP state. */
        *( portFPCCR ) |= ( portFPCCR_ASPEN_MASK | portFPCCR_LSPEN_MASK );
    }

#endif /* configENABLE_FPU */
/*-----------------------------------------------------------*/

શૂન્ય vPortYield( શૂન્ય ) /* PRIVILEGED_FUNCTION */
{
    /* Set a PendSV to request a context switch. */
    portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm અસ્થિર ( "dsb" ::: "memory" );
    __asm અસ્થિર ( "isb" );
}
/*-----------------------------------------------------------*/

#જો ( config_સંખ્યા_OF_CORES == 1 )
    શૂન્ય vPortEnterCritical( શૂન્ય ) /* PRIVILEGED_FUNCTION */
    {
        portDISABLE_INTERRUPTS();
        ulCriticalNesting++;
        /* Barriers are normally not required but do ensure the code is
        * completely within the specified behaviour for the architecture. */
        __asm અસ્થિર ( "dsb" ::: "memory" );
        __asm અસ્થિર ( "isb" );
    }
    /*-----------------------------------------------------------*/

    શૂન્ય vPortExitCritical( શૂન્ય ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( ulCriticalNesting );
        ulCriticalNesting--;

        જો( ulCriticalNesting == 0 )
        {
            portENABLE_INTERRUPTS();
        }
    }
#endif /* configNUMBER_OF_CORES == 1 */
/*-----------------------------------------------------------*/

શૂન્ય SysTick_Handler( શૂન્ય ) /* PRIVILEGED_FUNCTION */
{
    uint32_t ulPreviousMask;

    ulPreviousMask = portSET_INTERRUPT_MASK_FROM_ISR();
    #જો ( config_સંખ્યા_OF_CORES > 1 )
        UBaseType_t uxSavedInterruptStatus = portENTER_CRITICAL_FROM_ISR();
    #endif /* if ( configNUMBER_OF_CORES > 1 ) */

    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        જો( xTaskIncrementTick() != pdFALSE )
        {
            traceISR_EXIT_TO_SCHEDULER();
            /* Pend a context switch. */
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;
        }
        નહીંતર
        {
            traceISR_EXIT();
        }
    }
    #જો ( config_સંખ્યા_OF_CORES > 1 )
        portEXIT_CRITICAL_FROM_ISR( uxSavedInterruptStatus );
    #endif /* if ( configNUMBER_OF_CORES > 1 ) */

    portCLEAR_INTERRUPT_MASK_FROM_ISR( ulPreviousMask );
}
/*-----------------------------------------------------------*/

શૂન્ય vPortSVCHandler_C( uint32_t * pul_Caller_ઢગલો_Address ) /* PRIVILEGED_FUNCTION portDONT_DISCARD */
{
    #જો ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )
        #જો defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            બાહ્ય uint32_t * __syscalls_flash_start__;
            બાહ્ય uint32_t * __syscalls_flash_end__;
        #નહીંતર
            /* Declaration when these variable are exported from linker scripts. */
            બાહ્ય uint32_t __syscalls_flash_start__[];
            બાહ્ય uint32_t __syscalls_flash_end__[];
        #endif /* defined( __ARMCC_VERSION ) */
    #endif /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #જો ( configENABLE_MPU == 1 )
        #જો defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            બાહ્ય uint32_t * __privileged_functions_start__;
            બાહ્ય uint32_t * __privileged_functions_end__;
        #નહીંતર
            /* Declaration when these variable are exported from linker scripts. */
            બાહ્ય uint32_t __privileged_functions_start__[];
            બાહ્ય uint32_t __privileged_functions_end__[];
        #endif /* defined( __ARMCC_VERSION ) */
    #endif /* configENABLE_MPU == 1 */

    uint32_t ulPC;

    #જો ( configENABLE_TRUSTZONE == 1 )
        uint32_t ulR0, ulR1;
        બાહ્ય TaskHandle_t pxCurrentTCB;
        #જો ( configENABLE_MPU == 1 )
            uint32_t ulControl, ulIsTaskPrivileged;
        #endif /* configENABLE_MPU */
    #endif /* configENABLE_TRUSTZONE */
    uint8_t ucSVCNumber;

    /* Register are stored on the stack in the following order - R0, R1, R2, R3,
     * R12, LR, PC, xPSR. */
    ulPC = pul_Caller_ઢગલો_Address[ portOFFSET_TO_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    પસંદગી( ucSVCNumber )
    {
    #જો ( configENABLE_TRUSTZONE == 1 )
        સ્થિતિ portSVC_ALLOCATE_SECURE_CONTEXT:

            /* R0 contains the stack size passed as parameter to the
             * vPortAllocateSecureContext function. */
            ulR0 = pul_Caller_ઢગલો_Address[ 0 ];

            #જો ( configENABLE_MPU == 1 )
            {
                /* Read the CONTROL register value. */
                __asm અસ્થિર ( "mrs %0, control"  : "=r" ( ulControl ) );

                /* The task that raised the SVC is privileged if Bit[0]
                 * in the CONTROL register is 0. */
                ulIsTaskPrivileged = ( ( ulControl & portCONTROL_PRIVILEGED_MASK ) == 0 );

                /* Allocate and load a context for the secure task. */
                xSecureContext = SecureContext_AllocateContext( ulR0, ulIsTaskPrivileged, pxCurrentTCB );
            }
            #નહીંતર /* if ( configENABLE_MPU == 1 ) */
            {
                /* Allocate and load a context for the secure task. */
                xSecureContext = SecureContext_AllocateContext( ulR0, pxCurrentTCB );
            }
            #endif /* configENABLE_MPU */

            configASSERT( xSecureContext != securecontextINVALID_CONTEXT_ID );
            SecureContext_LoadContext( xSecureContext, pxCurrentTCB );
            તોડો;

        સ્થિતિ portSVC_FREE_SECURE_CONTEXT:
            #જો ( configENABLE_MPU == 1 )
            જો( ( ulPC >= ( uint32_t ) __privileged_functions_start__ ) &&
                ( ulPC <= ( uint32_t ) __privileged_functions_end__ ) )
            {
            #endif /* configENABLE_MPU */
                /* R0 contains TCB being freed and R1 contains the secure
                 * context handle to be freed. */
                ulR0 = pul_Caller_ઢગલો_Address[ 0 ];
                ulR1 = pul_Caller_ઢગલો_Address[ 1 ];

                /* Free the secure context. */
                SecureContext_FreeContext( ( SecureContextHandle_t ) ulR1, ( શૂન્ય * ) ulR0 );
            #જો ( configENABLE_MPU == 1 )
            }
            #endif /* configENABLE_MPU */
            તોડો;
    #endif /* configENABLE_TRUSTZONE */

        સ્થિતિ portSVC_START_SCHEDULER:
            #જો ( configENABLE_MPU == 1 )
            જો( ( ulPC >= ( uint32_t ) __privileged_functions_start__ ) &&
                ( ulPC <= ( uint32_t ) __privileged_functions_end__ ) )
            {
            #endif /* configENABLE_MPU */
                #જો ( configENABLE_TRUSTZONE == 1 )
                {
                    /* De-prioritize the non-secure exceptions so that the
                     * non-secure pendSV runs at the lowest priority. */
                    SecureInit_DePrioritizeNSExceptions();

                    /* Initialize the secure context management system. */
                    SecureContext_Init();
                }
                #endif /* configENABLE_TRUSTZONE */

                #જો ( configENABLE_FPU == 1 )
                {
                    /* Setup the Floating Point Unit (FPU). */
                    prvSetupFPU();
                }
                #endif /* configENABLE_FPU */

                /* Setup the context of the first task so that the first task starts
                 * executing. */
                vRestoreContextOfFirstTask();
            #જો ( configENABLE_MPU == 1 )
            }
            #endif /* configENABLE_MPU */
            તોડો;

    #જો ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )
        સ્થિતિ portSVC_RAISE_PRIVILEGE:

            /* Only raise the privilege, if the svc was raised from any of
             * the system calls. */
            જો( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
            {
                vRaisePrivilege();
            }
            તોડો;
    #endif /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #જો ( configENABLE_MPU == 1 )
        સ્થિતિ portSVC_YIELD:
            vPortYield();
            તોડો;
    #endif /* configENABLE_MPU == 1 */

        મૂળભૂત:
            /* Incorrect SVC call. */
            configASSERT( pdFALSE );
    }
}
/*-----------------------------------------------------------*/

#જો ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    શૂન્ય vSystemCallEnter( uint32_t * pul_Task_ઢગલો,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_સંખ્યા ) /* PRIVILEGED_FUNCTION */
    {
        બાહ્ય TaskHandle_t pxCurrentTCB;
        બાહ્ય UBaseType_t uxSystemCallImplementations[ અંક_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_ઢગલો;
        uint32_t ulHardwareSavedExceptionFrameSize, ulSystemCallLocation, i;

        #જો defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            બાહ્ય uint32_t * __syscalls_flash_start__;
            બાહ્ય uint32_t * __syscalls_flash_end__;
        #નહીંતર
            /* Declaration when these variable are exported from linker scripts. */
            બાહ્ય uint32_t __syscalls_flash_start__[];
            બાહ્ય uint32_t __syscalls_flash_end__[];
        #endif /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_ઢગલો[ portOFFSET_TO_PC ];
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
        જો( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_ઢગલો_Info.pul_Task_ઢગલો == ખાલી ) &&
            ( uxSystemCallImplementations[ uc_System_Call_સંખ્યા ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_ઢગલો = pxMpuSettings->x_System_Call_ઢગલો_Info.pul_System_Call_ઢગલો;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            #જો ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )
            {
                જો( ( ulLR & port_EXC_RETURN_ઢગલો_FRAME_TYPE_MASK ) == 0UL )
                {
                    /* Extended frame i.e. FPU in use. */
                    ulHardwareSavedExceptionFrameSize = 26;
                    __asm અસ્થિર (
                        " vpush {s0}         \n" /* Trigger lazy stacking. */
                        " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                        ::: "memory"
                        );
                }
                નહીંતર
                {
                    /* Standard frame i.e. FPU not in use. */
                    ulHardwareSavedExceptionFrameSize = 8;
                }
            }
            #નહીંતર /* if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */
            {
                ulHardwareSavedExceptionFrameSize = 8;
            }
            #endif /* configENABLE_FPU || configENABLE_MVE */

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_ઢગલો = pul_System_Call_ઢગલો - ulHardwareSavedExceptionFrameSize;

            /* Copy the stack frame. */
            માટે( i = 0; i < ulHardwareSavedExceptionFrameSize; i++ )
            {
                pul_System_Call_ઢગલો[ i ] = pul_Task_ઢગલો[ i ];
            }

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_ઢગલો_Info.ulLinkRegisterAtSystemCallEntry = pul_Task_ઢગલો[ portOFFSET_TO_LR ];

            /* Store the value of the PSPLIM register before the SVC was raised.
             * We need to restore it when we exit from the system call. */
            #જો ( portUSE_PSPLIM_REGISTER == 1 )
            {
                __asm અસ્થિર ( "mrs %0, psplim" : "=r" ( pxMpuSettings->x_System_Call_ઢગલો_Info.ul_ઢગલો_Limit_Register_At_System_Call_Entry ) );
            }
            #endif

            /* Use the pulSystemCallStack in thread mode. */
            __asm અસ્થિર ( "msr psp, %0" : : "r" ( pul_System_Call_ઢગલો ) );
            #જો ( portUSE_PSPLIM_REGISTER == 1 )
            {
                __asm અસ્થિર ( "msr psplim, %0" : : "r" ( pxMpuSettings->x_System_Call_ઢગલો_Info.pul_System_Call_ઢગલો_Limit ) );
            }
            #endif

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_ઢગલો[ portOFFSET_TO_PC ] = uxSystemCallImplementations[ uc_System_Call_સંખ્યા ];

            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_ઢગલો[ portOFFSET_TO_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_ઢગલો_Info.pul_Task_ઢગલો = pul_Task_ઢગલો + ulHardwareSavedExceptionFrameSize;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            જો( ( pul_Task_ઢગલો[ portOFFSET_TO_PSR ] & port_PSR_ઢગલો_PADDING_MASK ) == port_PSR_ઢગલો_PADDING_MASK )
            {
                pxMpuSettings->ulTaskFlags |= port_ઢગલો_FRAME_HAS_PADDING_FLAG;
            }
            નહીંતર
            {
                pxMpuSettings->ulTaskFlags &= ( ~port_ઢગલો_FRAME_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_ઢગલો[ portOFFSET_TO_PSR ] &= ( ~port_PSR_ઢગલો_PADDING_MASK );

            /* Raise the privilege for the duration of the system call. */
            __asm અસ્થિર (
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

#જો ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    શૂન્ય vRequestSystemCallExit( શૂન્ય ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm અસ્થિર ( "svc %0 \n" ::"i" ( portSVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#endif /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#જો ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    શૂન્ય vSystemCallExit( uint32_t * pul_System_Call_ઢગલો,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        બાહ્ય TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_ઢગલો;
        uint32_t ulHardwareSavedExceptionFrameSize, ulSystemCallLocation, i;

        #જો defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            બાહ્ય uint32_t * __privileged_functions_start__;
            બાહ્ય uint32_t * __privileged_functions_end__;
        #નહીંતર
            /* Declaration when these variable are exported from linker scripts. */
            બાહ્ય uint32_t __privileged_functions_start__[];
            બાહ્ય uint32_t __privileged_functions_end__[];
        #endif /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_ઢગલો[ portOFFSET_TO_PC ];
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
        જો( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_ઢગલો_Info.pul_Task_ઢગલો != ખાલી ) )
        {
            pul_Task_ઢગલો = pxMpuSettings->x_System_Call_ઢગલો_Info.pul_Task_ઢગલો;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            #જો ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )
            {
                જો( ( ulLR & port_EXC_RETURN_ઢગલો_FRAME_TYPE_MASK ) == 0UL )
                {
                    /* Extended frame i.e. FPU in use. */
                    ulHardwareSavedExceptionFrameSize = 26;
                    __asm અસ્થિર (
                        " vpush {s0}         \n" /* Trigger lazy stacking. */
                        " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                        ::: "memory"
                        );
                }
                નહીંતર
                {
                    /* Standard frame i.e. FPU not in use. */
                    ulHardwareSavedExceptionFrameSize = 8;
                }
            }
            #નહીંતર /* if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */
            {
                ulHardwareSavedExceptionFrameSize = 8;
            }
            #endif /* configENABLE_FPU || configENABLE_MVE */

            /* Make space on the task stack for the stack frame. */
            pul_Task_ઢગલો = pul_Task_ઢગલો - ulHardwareSavedExceptionFrameSize;

            /* Copy the stack frame. */
            માટે( i = 0; i < ulHardwareSavedExceptionFrameSize; i++ )
            {
                pul_Task_ઢગલો[ i ] = pul_System_Call_ઢગલો[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm અસ્થિર ( "msr psp, %0" : : "r" ( pul_Task_ઢગલો ) );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_ઢગલો[ portOFFSET_TO_PC ] = pxMpuSettings->x_System_Call_ઢગલો_Info.ulLinkRegisterAtSystemCallEntry;
            /* Ensure that LR has a valid value.*/
            pul_Task_ઢગલો[ portOFFSET_TO_LR ] = pxMpuSettings->x_System_Call_ઢગલો_Info.ulLinkRegisterAtSystemCallEntry;

            /* Restore the PSPLIM register to what it was at the time of
             * system call entry. */
            #જો ( portUSE_PSPLIM_REGISTER == 1 )
            {
                __asm અસ્થિર ( "msr psplim, %0" : : "r" ( pxMpuSettings->x_System_Call_ઢગલો_Info.ul_ઢગલો_Limit_Register_At_System_Call_Entry ) );
            }
            #endif

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            જો( ( pxMpuSettings->ulTaskFlags & port_ઢગલો_FRAME_HAS_PADDING_FLAG ) == port_ઢગલો_FRAME_HAS_PADDING_FLAG )
            {
                pul_Task_ઢગલો[ portOFFSET_TO_PSR ] |= port_PSR_ઢગલો_PADDING_MASK;
            }
            નહીંતર
            {
                pul_Task_ઢગલો[ portOFFSET_TO_PSR ] &= ( ~port_PSR_ઢગલો_PADDING_MASK );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_ઢગલો_Info.pul_Task_ઢગલો = ખાલી;

            /* Drop the privilege before returning to the thread mode. */
            __asm અસ્થિર (
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

#જો ( configENABLE_MPU == 1 )

    BaseType_t xPortIsTaskPrivileged( શૂન્ય ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xTaskIsPrivileged = pdFALSE;
        અચલ xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ખાલી ); /* Calling task's MPU settings. */

        જો( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        પાછા xTaskIsPrivileged;
    }

#endif /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

#જો ( configENABLE_MPU == 1 )

    ઢગલો_Type_t * px_Port_Initialise_ઢગલો( ઢગલો_Type_t * px_ટોચ_Of_ઢગલો,
                                         ઢગલો_Type_t * px_End_Of_ઢગલો,
                                         TaskFunction_t pxCode,
                                         શૂન્ય * pvParameters,
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

        #જો ( configENABLE_TRUSTZONE == 1 )
        {
            xMPUSettings->ulContext[ ulIndex ] = portNO_SECURE_CONTEXT; /* xSecureContext. */
            ulIndex++;
        }
        #endif /* configENABLE_TRUSTZONE */
        xMPUSettings->ulContext[ ulIndex ] = ( uint32_t ) ( px_ટોચ_Of_ઢગલો - 8 ); /* PSP with the hardware saved stack. */
        ulIndex++;
        xMPUSettings->ulContext[ ulIndex ] = ( uint32_t ) px_End_Of_ઢગલો; /* PSPLIM. */
        ulIndex++;

        #જો ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
        {
            /* Check PACBTI security feature configuration before pushing the
             * CONTROL register's value on task's TCB. */
            #જો ( config_સંખ્યા_OF_CORES == 1 )
                ulControl = prvConfigurePACBTI( pdFALSE );
            #નહીંતર /* configNUMBER_OF_CORES > 1 */
                ulControl = vConfigurePACBTI( pdFALSE );
            #endif /* configNUMBER_OF_CORES */
        }
        #endif /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

        જો( xRunPrivileged == pdTRUE )
        {
            xMPUSettings->ulTaskFlags |= portTASK_IS_PRIVILEGED_FLAG;
            xMPUSettings->ulContext[ ulIndex ] = ( ulControl | ( uint32_t ) portINITIAL_CONTROL_PRIVILEGED ); /* CONTROL. */
            ulIndex++;
        }
        નહીંતર
        {
            xMPUSettings->ulTaskFlags &= ( ~portTASK_IS_PRIVILEGED_FLAG );
            xMPUSettings->ulContext[ ulIndex ] = ( ulControl | ( uint32_t ) portINITIAL_CONTROL_UNPRIVILEGED ); /* CONTROL. */
            ulIndex++;
        }

        xMPUSettings->ulContext[ ulIndex ] = portINITIAL_EXC_RETURN; /* LR (EXC_RETURN). */
        ulIndex++;

        #જો ( configUSE_MPU_WRAPPERS_V1 == 0 )
        {
            /* Ensure that the system call stack is double word aligned. */
            xMPUSettings->x_System_Call_ઢગલો_Info.pul_System_Call_ઢગલો = &( xMPUSettings->x_System_Call_ઢગલો_Info.ul_System_Call_ઢગલો_Buffer[ config_SYSTEM_CALL_ઢગલો_SIZE - 1 ] );
            xMPUSettings->x_System_Call_ઢગલો_Info.pul_System_Call_ઢગલો = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_ઢગલો_Info.pul_System_Call_ઢગલો ) &
                                                                                     ( uint32_t ) ( ~( portBYTE_ALIGNMENT_MASK ) ) );

            xMPUSettings->x_System_Call_ઢગલો_Info.pul_System_Call_ઢગલો_Limit = &( xMPUSettings->x_System_Call_ઢગલો_Info.ul_System_Call_ઢગલો_Buffer[ 0 ] );
            xMPUSettings->x_System_Call_ઢગલો_Info.pul_System_Call_ઢગલો_Limit = ( uint32_t * ) ( ( ( uint32_t ) ( xMPUSettings->x_System_Call_ઢગલો_Info.pul_System_Call_ઢગલો_Limit ) +
                                                                                            ( uint32_t ) ( portBYTE_ALIGNMENT - 1 ) ) &
                                                                                          ( uint32_t ) ( ~( portBYTE_ALIGNMENT_MASK ) ) );

            /* This is not NULL only for the duration of a system call. */
            xMPUSettings->x_System_Call_ઢગલો_Info.pul_Task_ઢગલો = ખાલી;
        }
        #endif /* configUSE_MPU_WRAPPERS_V1 == 0 */

        #જો ( configENABLE_PAC == 1 )
        {
            uint32_t ul_Task_Pac_ચાવી[ 4 ], i;

            v_Application_Generate_Task_Random_Pac_ચાવી( &( ul_Task_Pac_ચાવી[ 0 ] ) );

            માટે( i = 0; i < 4; i++ )
            {
                xMPUSettings->ulContext[ ulIndex ] = ul_Task_Pac_ચાવી[ i ];
                ulIndex++;
            }
        }
        #endif /* configENABLE_PAC */

        પાછા &( xMPUSettings->ulContext[ ulIndex ] );
    }

#નહીંતર /* configENABLE_MPU */

    ઢગલો_Type_t * px_Port_Initialise_ઢગલો( ઢગલો_Type_t * px_ટોચ_Of_ઢગલો,
                                         ઢગલો_Type_t * px_End_Of_ઢગલો,
                                         TaskFunction_t pxCode,
                                         શૂન્ય * pvParameters ) /* PRIVILEGED_FUNCTION */
    {
        /* Simulate the stack frame as it would be created by a context switch
         * interrupt. */
        #જો ( portPRELOAD_REGISTERS == 0 )
        {
            px_ટોચ_Of_ઢગલો--; /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_ટોચ_Of_ઢગલો = portINITIAL_XPSR; /* xPSR. */
            px_ટોચ_Of_ઢગલો--;
            *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) pxCode; /* PC. */
            px_ટોચ_Of_ઢગલો--;
            *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) portTASK_RETURN_ADDRESS; /* LR. */
            px_ટોચ_Of_ઢગલો -= 5; /* R12, R3, R2 and R1. */
            *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) pvParameters; /* R0. */
            px_ટોચ_Of_ઢગલો -= 9; /* R11..R4, EXC_RETURN. */
            *px_ટોચ_Of_ઢગલો = portINITIAL_EXC_RETURN;
            px_ટોચ_Of_ઢગલો--;
            *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) px_End_Of_ઢગલો; /* Slot used to hold this task's PSPLIM value. */

            #જો ( configENABLE_TRUSTZONE == 1 )
            {
                px_ટોચ_Of_ઢગલો--;
                *px_ટોચ_Of_ઢગલો = portNO_SECURE_CONTEXT; /* Slot used to hold this task's xSecureContext value. */
            }
            #endif /* configENABLE_TRUSTZONE */
        }
        #નહીંતર /* portPRELOAD_REGISTERS */
        {
            px_ટોચ_Of_ઢગલો--; /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_ટોચ_Of_ઢગલો = portINITIAL_XPSR; /* xPSR. */
            px_ટોચ_Of_ઢગલો--;
            *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) pxCode; /* PC. */
            px_ટોચ_Of_ઢગલો--;
            *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) portTASK_RETURN_ADDRESS; /* LR. */
            px_ટોચ_Of_ઢગલો--;
            *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x12121212UL; /* R12. */
            px_ટોચ_Of_ઢગલો--;
            *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x03030303UL; /* R3. */
            px_ટોચ_Of_ઢગલો--;
            *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x02020202UL; /* R2. */
            px_ટોચ_Of_ઢગલો--;
            *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x01010101UL; /* R1. */
            px_ટોચ_Of_ઢગલો--;
            *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) pvParameters; /* R0. */
            px_ટોચ_Of_ઢગલો--;
            *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x11111111UL; /* R11. */
            px_ટોચ_Of_ઢગલો--;
            *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x10101010UL; /* R10. */
            px_ટોચ_Of_ઢગલો--;
            *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x09090909UL; /* R09. */
            px_ટોચ_Of_ઢગલો--;
            *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x08080808UL; /* R08. */
            px_ટોચ_Of_ઢગલો--;
            *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x07070707UL; /* R07. */
            px_ટોચ_Of_ઢગલો--;
            *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x06060606UL; /* R06. */
            px_ટોચ_Of_ઢગલો--;
            *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x05050505UL; /* R05. */
            px_ટોચ_Of_ઢગલો--;
            *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x04040404UL; /* R04. */
            px_ટોચ_Of_ઢગલો--;
            *px_ટોચ_Of_ઢગલો = portINITIAL_EXC_RETURN; /* EXC_RETURN. */
            px_ટોચ_Of_ઢગલો--;
            *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) px_End_Of_ઢગલો; /* Slot used to hold this task's PSPLIM value. */

            #જો ( configENABLE_TRUSTZONE == 1 )
            {
                px_ટોચ_Of_ઢગલો--;
                *px_ટોચ_Of_ઢગલો = portNO_SECURE_CONTEXT; /* Slot used to hold this task's xSecureContext value. */
            }
            #endif /* configENABLE_TRUSTZONE */
        }
        #endif /* portPRELOAD_REGISTERS */

        #જો ( configENABLE_PAC == 1 )
        {
            uint32_t ul_Task_Pac_ચાવી[ 4 ], i;

            v_Application_Generate_Task_Random_Pac_ચાવી( &( ul_Task_Pac_ચાવી[ 0 ] ) );

            માટે( i = 0; i < 4; i++ )
            {
                px_ટોચ_Of_ઢગલો--;
                *px_ટોચ_Of_ઢગલો = ul_Task_Pac_ચાવી[ i ];
            }
        }
        #endif /* configENABLE_PAC */

        પાછા px_ટોચ_Of_ઢગલો;
    }

#endif /* configENABLE_MPU */
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( શૂન્ય ) /* PRIVILEGED_FUNCTION */
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
    #જો ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        અચલ portISR_t * અચલ pxVectorTable = portSCB_VTOR_REG;

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

    #જો ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
    {
        /* Set the CONTROL register value based on PACBTI security feature
         * configuration before starting the first task. */
        #જો ( config_સંખ્યા_OF_CORES == 1 )
            ( શૂન્ય ) prvConfigurePACBTI( pdTRUE );
        #નહીંતર /* configNUMBER_OF_CORES > 1 */
            ( શૂન્ય ) vConfigurePACBTI( pdTRUE );
        #endif /* configNUMBER_OF_CORES */
    }
    #endif /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

    #જો ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        prvSetupMPU();
    }
    #endif /* configENABLE_MPU */

    #જો ( config_સંખ્યા_OF_CORES > 1 )
        /* Start the timer that generates the tick ISR. Interrupts are disabled
         * here already. */
        vPortSetupTimerInterrupt();
        /* Initialize the critical nesting count for all cores. */
        માટે ( uint8_t ucCoreID = 0; ucCoreID < config_સંખ્યા_OF_CORES; ucCoreID++ )
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
        જ્યારે( 1 )
        {
            BaseType_t xAllCoresReady = pdTRUE;
            માટે( uint8_t ucCoreID = 0; ucCoreID < ( config_સંખ્યા_OF_CORES - 1 ); ucCoreID++ )
            {
                જો( ucSecondaryCoresReadyFlags[ ucCoreID ] != pdTRUE )
                {
                    xAllCoresReady = pdFALSE;
                    તોડો;
                }
                }

            જો ( xAllCoresReady == pdTRUE )
            {
                તોડો;
            }
        }
    #નહીંતર /* if ( configNUMBER_OF_CORES > 1 ) */
        /* Start the timer that generates the tick ISR. */
        vPortSetupTimerInterrupt();
        /* Initialize the critical nesting count ready for the first task. */
        ulCriticalNesting = 0;
    #endif /* if ( configNUMBER_OF_CORES > 1 ) */

    #જો ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )
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
    #જો ( config_સંખ્યા_OF_CORES > 1 )
        vTaskSwitchContext( portGET_CORE_ID() );
    #નહીંતર
        vTaskSwitchContext();
    #endif
    prvTaskExitError();

    /* Should not get here. */
    પાછા 0;
}
/*-----------------------------------------------------------*/

શૂન્ય vPortEndScheduler( શૂન્ય ) /* PRIVILEGED_FUNCTION */
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    #જો ( config_સંખ્યા_OF_CORES == 1 )
        configASSERT( ulCriticalNesting == 1000UL );
    #નહીંતર /* if ( configNUMBER_OF_CORES == 1 ) */
        configASSERT( ulCriticalNestings[ portGET_CORE_ID() ] == 1000UL );
    #endif /* if ( configNUMBER_OF_CORES == 1 ) */
}
/*-----------------------------------------------------------*/

#જો ( configENABLE_MPU == 1 )

    શૂન્ય vPortStoreTaskMPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    અચલ સંરચના xMEMORY_REGION * અચલ xRegions,
                                    ઢગલો_Type_t * px_Bottom_Of_ઢગલો,
                                    config_ઢગલો_DEPTH_TYPE ux_ઢગલો_Depth )
    {
        uint32_t ulRegionStartAddress, ulRegionEndAddress, ul_Region_સંખ્યા;
        int32_t lIndex = 0;

        #જો defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            બાહ્ય uint32_t * __privileged_sram_start__;
            બાહ્ય uint32_t * __privileged_sram_end__;
        #નહીંતર
            /* Declaration when these variable are exported from linker scripts. */
            બાહ્ય uint32_t __privileged_sram_start__[];
            બાહ્ય uint32_t __privileged_sram_end__[];
        #endif /* defined( __ARMCC_VERSION ) */

        /* Setup MAIR0. */
        xMPUSettings->ulMAIR0 = ( ( portMPU_NORMAL_MEMORY_BUFFERABLE_CACHEABLE << portMPU_MAIR_ATTR0_POS ) & portMPU_MAIR_ATTR0_MASK );
        xMPUSettings->ulMAIR0 |= ( ( portMPU_DEVICE_MEMORY_nGnRE << portMPU_MAIR_ATTR1_POS ) & portMPU_MAIR_ATTR1_MASK );

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid.  At all other
         * times the stack parameters will not be valid and it is assumed that
         * the stack region has already been configured. */
        જો( ux_ઢગલો_Depth > 0 )
        {
            ulRegionStartAddress = ( uint32_t ) px_Bottom_Of_ઢગલો;
            ulRegionEndAddress = ( uint32_t ) px_Bottom_Of_ઢગલો + ( ux_ઢગલો_Depth * ( config_ઢગલો_DEPTH_TYPE ) કદ( ઢગલો_Type_t ) ) - 1;

            /* If the stack is within the privileged SRAM, do not protect it
             * using a separate MPU region. This is needed because privileged
             * SRAM is already protected using an MPU region and ARMv8-M does
             * not allow overlapping MPU regions. */
            જો( ( ulRegionStartAddress >= ( uint32_t ) __privileged_sram_start__ ) &&
                ( ulRegionEndAddress <= ( uint32_t ) __privileged_sram_end__ ) )
            {
                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR = 0;
                xMPUSettings->xRegionsSettings[ 0 ].ulRLAR = 0;
            }
            નહીંતર
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
        માટે( ul_Region_સંખ્યા = 1; ul_Region_સંખ્યા <= port_અંક_CONFIGURABLE_REGIONS; ul_Region_સંખ્યા++ )
        {
            /* If xRegions is NULL i.e. the task has not specified any MPU
             * region, the else part ensures that all the configurable MPU
             * regions are invalidated. */
            જો( ( xRegions != ખાલી ) && ( xRegions[ lIndex ].ulLengthInBytes > 0UL ) )
            {
                /* Translate the generic region definition contained in xRegions
                 * into the ARMv8 specific MPU settings that are then stored in
                 * xMPUSettings. */
                ulRegionStartAddress = ( ( uint32_t ) xRegions[ lIndex ].pvBaseAddress ) & portMPU_RBAR_ADDRESS_MASK;
                ulRegionEndAddress = ( uint32_t ) xRegions[ lIndex ].pvBaseAddress + xRegions[ lIndex ].ulLengthInBytes - 1;
                ulRegionEndAddress &= portMPU_RLAR_ADDRESS_MASK;

                /* Start address. */
                xMPUSettings->xRegionsSettings[ ul_Region_સંખ્યા ].ulRBAR = ( ulRegionStartAddress ) |
                                                                          ( portMPU_REGION_NON_SHAREABLE );

                /* RO/RW. */
                જો( ( xRegions[ lIndex ].ulParameters & tskMPU_REGION_READ_ONLY ) != 0 )
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_સંખ્યા ].ulRBAR |= ( portMPU_REGION_READ_ONLY );
                }
                નહીંતર
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_સંખ્યા ].ulRBAR |= ( portMPU_REGION_READ_WRITE );
                }

                /* XN. */
                જો( ( xRegions[ lIndex ].ulParameters & tskMPU_REGION_EXECUTE_NEVER ) != 0 )
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_સંખ્યા ].ulRBAR |= ( portMPU_REGION_EXECUTE_NEVER );
                }

                /* End Address. */
                xMPUSettings->xRegionsSettings[ ul_Region_સંખ્યા ].ulRLAR = ( ulRegionEndAddress ) |
                                                                          ( portMPU_RLAR_REGION_ENABLE );

                /* PXN. */
                #જો ( portARMV8M_MINOR_VERSION >= 1 )
                {
                    જો( ( xRegions[ lIndex ].ulParameters & tskMPU_REGION_PRIVILEGED_EXECUTE_NEVER ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ ul_Region_સંખ્યા ].ulRLAR |= ( portMPU_RLAR_PRIVILEGED_EXECUTE_NEVER );
                    }
                }
                #endif /* portARMV8M_MINOR_VERSION >= 1 */

                /* Normal memory/ Device memory. */
                જો( ( xRegions[ lIndex ].ulParameters & tskMPU_REGION_DEVICE_MEMORY ) != 0 )
                {
                    /* Attr1 in MAIR0 is configured as device memory. */
                    xMPUSettings->xRegionsSettings[ ul_Region_સંખ્યા ].ulRLAR |= portMPU_RLAR_ATTR_INDEX1;
                }
                નહીંતર
                {
                    /* Attr0 in MAIR0 is configured as normal memory. */
                    xMPUSettings->xRegionsSettings[ ul_Region_સંખ્યા ].ulRLAR |= portMPU_RLAR_ATTR_INDEX0;
                }
            }
            નહીંતર
            {
                /* Invalidate the region. */
                xMPUSettings->xRegionsSettings[ ul_Region_સંખ્યા ].ulRBAR = 0UL;
                xMPUSettings->xRegionsSettings[ ul_Region_સંખ્યા ].ulRLAR = 0UL;
            }

            lIndex++;
        }
    }

#endif /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#જો ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    BaseType_t xPortIsAuthorizedToAccessBuffer( અચલ શૂન્ય * pvBuffer,
                                                size_t xBufferLength,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ulBufferStartAddress, ulBufferEndAddress;
        BaseType_t xAccessGranted = pdFALSE;
        અચલ xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ખાલી ); /* Calling task's MPU settings. */

        જો( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        નહીંતર જો( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        નહીંતર
        {
            જો( portADD_UINT32_WILL_OVERFLOW( ( ( uint32_t ) pvBuffer ), ( ( uint32_t ) xBufferLength - 1UL ) ) == pdFALSE )
            {
                ulBufferStartAddress = ( uint32_t ) pvBuffer;
                ulBufferEndAddress = ( ( ( uint32_t ) pvBuffer ) + ( uint32_t ) xBufferLength - 1UL );

                માટે( i = 0; i < port_TOTAL_અંક_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    જો( ( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR & portMPU_RLAR_REGION_ENABLE ) == portMPU_RLAR_REGION_ENABLE )
                    {
                        જો( portIS_ADDRESS_WITHIN_RANGE( ulBufferStartAddress,
                                                         portEXTRACT_FIRST_ADDRESS_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ),
                                                         portEXTRACT_LAST_ADDRESS_FROM_RLAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR ) ) &&
                            portIS_ADDRESS_WITHIN_RANGE( ulBufferEndAddress,
                                                         portEXTRACT_FIRST_ADDRESS_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ),
                                                         portEXTRACT_LAST_ADDRESS_FROM_RLAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR ) ) &&
                            portIS_AUTHORIZED( ulAccessRequested,
                                               prvGetRegionAccessPermissions( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ) ) )
                        {
                            xAccessGranted = pdTRUE;
                            તોડો;
                        }
                    }
                }
            }
        }

        પાછા xAccessGranted;
    }

#endif /* #if ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

BaseType_t xPortIsInsideInterrupt( શૂન્ય )
{
    uint32_t ulCurrentInterrupt;
    BaseType_t xReturn;

    /* Obtain the number of the currently executing interrupt. Interrupt Program
     * Status Register (IPSR) holds the exception number of the currently-executing
     * exception or zero for Thread mode.*/
    __asm અસ્થિર ( "mrs %0, ipsr" : "=r" ( ulCurrentInterrupt )::"memory" );

    જો( ulCurrentInterrupt == 0 )
    {
        xReturn = pdFALSE;
    }
    નહીંતર
    {
        xReturn = pdTRUE;
    }

    પાછા xReturn;
}
/*-----------------------------------------------------------*/

#જો ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) )

    શૂન્ય vPortValidateInterruptPriority( શૂન્ય )
    {
        uint32_t ulCurrentInterrupt;
        uint8_t ucCurrentPriority;

        /* Obtain the number of the currently executing interrupt. */
        __asm અસ્થિર ( "mrs %0, ipsr" : "=r" ( ulCurrentInterrupt )::"memory" );

        /* Is the interrupt number a user defined interrupt? */
        જો( ulCurrentInterrupt >= port_FIRST_USER_INTERRUPT_સંખ્યા )
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

શૂન્ય vPortConfigureInterruptPriorities( શૂન્ય ) /* PRIVILEGED_FUNCTION */
{
    #જો ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) )
    {
        અસ્થિર uint32_t ulImplementedPrioBits = 0;
        અસ્થિર uint8_t uc_Max_Priority_કિંમત;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
        * functions can be called. ISR safe functions are those that end in
        * "FromISR". FreeRTOS maintains separate thread and ISR API functions to
        * ensure interrupt entry is as fast and simple as possible.
        *
        * First, determine the number of priority bits available. Write to all
        * possible bits in the priority setting for SVCall. */
        portNVIC_SHPR2_REG = 0xFF000000;

        /* Read the value back to see how many bits stuck. */
        uc_Max_Priority_કિંમત = ( uint8_t ) ( ( portNVIC_SHPR2_REG & 0xFF000000 ) >> 24 );

        /* Use the same mask on the maximum system call priority. */
        ucMaxSysCallPriority = configMAX_SYSCALL_INTERRUPT_PRIORITY & uc_Max_Priority_કિંમત;

        /* Check that the maximum system call priority is nonzero after
        * accounting for the number of priority bits supported by the
        * hardware. A priority of 0 is invalid because setting the BASEPRI
        * register to 0 unmasks all interrupts, and interrupts with priority 0
        * cannot be masked using BASEPRI.
        * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( ucMaxSysCallPriority );

        /* Check that the bits not implemented in hardware are zero in
        * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( configMAX_SYSCALL_INTERRUPT_PRIORITY & ( uint8_t ) ( ~( uint32_t ) uc_Max_Priority_કિંમત ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
        * of bits read back. */
        જ્યારે( ( uc_Max_Priority_કિંમત & port_ટોચ_BIT_OF_BYTE ) == port_ટોચ_BIT_OF_BYTE )
        {
            ulImplementedPrioBits++;
            uc_Max_Priority_કિંમત <<= ( uint8_t ) 0x01;
        }

        જો( ulImplementedPrioBits == 8 )
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
        નહીંતર
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

#જો ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    શૂન્ય vPortGrantAccessToKernelObject( TaskHandle_t xInternalTaskHandle,
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

#જો ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    શૂન્ય vPortRevokeAccessToKernelObject( TaskHandle_t xInternalTaskHandle,
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

#જો ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #જો ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        BaseType_t xPortIsAuthorizedToAccessKernelObject( int32_t lInternalIndexOfKernelObject ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulAccessControlListEntryIndex, ulAccessControlListEntryBit;
            BaseType_t xAccessGranted = pdFALSE;
            અચલ xMPU_SETTINGS * xTaskMpuSettings;

            જો( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            નહીંતર
            {
                xTaskMpuSettings = xTaskGetMPUSettings( ખાલી ); /* Calling task's MPU settings. */

                ulAccessControlListEntryIndex = ( ( uint32_t ) lInternalIndexOfKernelObject / portACL_ENTRY_SIZE_BITS );
                ulAccessControlListEntryBit = ( ( uint32_t ) lInternalIndexOfKernelObject % portACL_ENTRY_SIZE_BITS );

                જો( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                નહીંતર
                {
                    જો( ( xTaskMpuSettings->ulAccessControlList[ ulAccessControlListEntryIndex ] & ( 1U << ulAccessControlListEntryBit ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            પાછા xAccessGranted;
        }

    #નહીંતર /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        BaseType_t xPortIsAuthorizedToAccessKernelObject( int32_t lInternalIndexOfKernelObject ) /* PRIVILEGED_FUNCTION */
        {
            ( શૂન્ય ) lInternalIndexOfKernelObject;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            પાછા pdTRUE;
        }

    #endif /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#endif /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */
/*-----------------------------------------------------------*/

#જો ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
    #જો ( config_સંખ્યા_OF_CORES == 1 )
        સ્થિર uint32_t prvConfigurePACBTI( BaseType_t xWriteControlRegister )
    #નહીંતર /* configNUMBER_OF_CORES > 1 */
        uint32_t vConfigurePACBTI( BaseType_t xWriteControlRegister )
    #endif /* configNUMBER_OF_CORES */
        {
            uint32_t ulControl = 0x0;

            /* Ensure that PACBTI is implemented. */
            configASSERT( portID_ISAR5_REG != 0x0 );

            /* Enable UsageFault exception. */
            portSCB_SYS_HANDLER_CTRL_STATE_REG |= portSCB_USG_FAULT_ENABLE_BIT;

            #જો ( configENABLE_PAC == 1 )
            {
                ulControl |= ( portCONTROL_UPAC_EN | portCONTROL_PAC_EN );
            }
            #endif

            #જો ( configENABLE_BTI == 1 )
            {
                ulControl |= ( portCONTROL_UBTI_EN | portCONTROL_BTI_EN );
            }
            #endif

            જો( xWriteControlRegister == pdTRUE )
            {
                __asm અસ્થિર ( "msr control, %0" : : "r" ( ulControl ) );
            }

            પાછા ulControl;
        }

#endif /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */
/*-----------------------------------------------------------*/

#જો ( config_સંખ્યા_OF_CORES > 1 )

    /* Which core owns the lock? */
    PRIVILEGED_DATA અસ્થિર uint32_t ulOwnedByCore[ port_MAX_CORE_ગણતરી ];
    /* Lock count a core owns. */
    PRIVILEGED_DATA અસ્થિર uint32_t ul_Recursion_ગણતરી_By_Lock[ e_Lock_ગણતરી ];
    /* Index 0 is used for ISR lock and Index 1 is used for task lock. */
    PRIVILEGED_DATA અસ્થિર uint32_t ulGateWord[ e_Lock_ગણતરી ];

    __attribute__((weak)) શૂન્ય vInterruptCore( uint8_t ucCoreID )
    {
        /* Default weak stub - platform specific implementation may override. */
        ( શૂન્ય ) ucCoreID;
    }

/*-----------------------------------------------------------*/

    સ્થિર અંતઃરેખ શૂન્ય prvSpinUnlock( અસ્થિર uint32_t * ulLock )
    {
        /* Conservative unlock: preserve original barriers for broad HW/FVP. */
        __asm અસ્થિર (
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

    સ્થિર અંતઃરેખ uint32_t prvSpinTrylock( અસ્થિર uint32_t * ulLock )
    {
        /*
         * Conservative ldrex/strex trylock:
         * - Return 1 immediately if busy, clearing exclusive state (CLREX).
         * - Retry strex only on spurious failure when observed free.
         * - DMB on success to preserve expected acquire semantics.
         */
        uint32_t ulVal;
        uint32_t ulStatus;

        __asm અસ્થિર (
            " ldrex %0, [%1]   \n"
            : "=r" ( ulVal )
            : "r" ( ulLock )
            : "memory"
        );

        જો( ulVal != 0U )
        {
            __asm અસ્થિર ("clrex" ::: "memory");
            પાછા 1U;
        }

        __asm અસ્થિર (
            " strex %0, %2, [%1]   \n"
            : "=&r" ( ulStatus )
            : "r" ( ulLock ), "r" (1U)
            : "memory"
        );

        જો( ulStatus != 0U )
        {
            પાછા 1U;
        }
        __asm અસ્થિર ( "dmb" ::: "memory" );
        પાછા 0U;
    }


/*-----------------------------------------------------------*/

    /* Read 32b value shared between cores. */
    સ્થિર અંતઃરેખ uint32_t prvGet32( અસ્થિર uint32_t * x )
    {
        __asm( "dsb" );
        પાછા *x;
    }

/*-----------------------------------------------------------*/

    /* Write 32b value shared between cores. */
    સ્થિર અંતઃરેખ શૂન્ય prvSet32( અસ્થિર uint32_t * x,
                                 uint32_t કિંમત )
    {
        *x = કિંમત;
        __asm( "dsb" );
    }

/*-----------------------------------------------------------*/

    શૂન્ય vPortRecursiveLock( uint8_t ucCoreID,
                             ePortRTOSLock e_Lock_અંક,
                             BaseType_t uxAcquire )
    {
        /* Validate the core ID and lock number. */
        configASSERT( ucCoreID < port_MAX_CORE_ગણતરી );
        configASSERT( e_Lock_અંક < e_Lock_ગણતરી );

        uint32_t ulLockBit = 1u << e_Lock_અંક;

        /* Lock acquire */
        જો( uxAcquire )
        {
            /* Check if spinlock is available. */
            /* If spinlock is not available check if the core owns the lock. */
            /* If the core owns the lock wait increment the lock count by the core. */
            /* If core does not own the lock wait for the spinlock. */
            જો( prvSpinTrylock( &ulGateWord[ e_Lock_અંક ] ) != 0 )
            {
                /* Check if the core owns the spinlock. */
                જો( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ulLockBit )
                {
                    configASSERT( prvGet32( &ul_Recursion_ગણતરી_By_Lock[ e_Lock_અંક ] ) != portUINT32_MAX );
                    prvSet32( &ul_Recursion_ગણતરી_By_Lock[ e_Lock_અંક ], ( prvGet32( &ul_Recursion_ગણતરી_By_Lock[ e_Lock_અંક ] ) + 1 ) );
                    પાછા;
                }

                /* Preload the gate word into the cache. */
                uint32_t dummy = ulGateWord[ e_Lock_અંક ];
                dummy++;

                જ્યારે( prvSpinTrylock( &ulGateWord[ e_Lock_અંક ] ) != 0 )
                {
                    __asm અસ્થિર ( "wfe" );
                }
            }

            /* Add barrier to ensure lock is taken before we proceed. */
            __asm અસ્થિર( "dmb sy" ::: "memory" );

            /* Assert the lock count is 0 when the spinlock is free and is acquired. */
            configASSERT( prvGet32( &ul_Recursion_ગણતરી_By_Lock[ e_Lock_અંક ] ) == 0 );

            /* Set lock count as 1. */
            prvSet32( &ul_Recursion_ગણતરી_By_Lock[ e_Lock_અંક ], 1 );
            /* Set ulOwnedByCore. */
            prvSet32( &ulOwnedByCore[ ucCoreID ], ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) | ulLockBit ) );
        }
        /* Lock release. */
        નહીંતર
        {
            /* Assert the lock is not free already. */
            configASSERT( ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ulLockBit ) != 0 );
            configASSERT( prvGet32( &ul_Recursion_ગણતરી_By_Lock[ e_Lock_અંક ] ) != 0 );

            /* Reduce ulRecursionCountByLock by 1. */
            prvSet32( &ul_Recursion_ગણતરી_By_Lock[ e_Lock_અંક ], ( prvGet32( &ul_Recursion_ગણતરી_By_Lock[ e_Lock_અંક ] ) - 1 ) );

            જો( !prvGet32( &ul_Recursion_ગણતરી_By_Lock[ e_Lock_અંક ] ) )
            {
                prvSet32( &ulOwnedByCore[ ucCoreID ], ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ~ulLockBit ) );
                prvSpinUnlock( &ulGateWord[ e_Lock_અંક ] );
                /* Add barrier to ensure lock status is reflected before we proceed. */
                __asm અસ્થિર( "dmb sy" ::: "memory" );
            }
        }
    }

/*-----------------------------------------------------------*/

    uint8_t ucPortGetCoreID( શૂન્ય )
    {
        પાછા *(અસ્થિર uint8_t *)(configCORE_ID_REGISTER);
    }

/*-----------------------------------------------------------*/

#endif /* if( configNUMBER_OF_CORES > 1 ) */
