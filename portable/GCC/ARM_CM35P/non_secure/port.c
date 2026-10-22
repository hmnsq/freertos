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
#परिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/* MPU includes. */
#अन्तर्भाव "mpu_wrappers.h"
#अन्तर्भाव "mpu_syscall_numbers.h"

/* Portasm includes. */
#अन्तर्भाव "portasm.h"

#यदि ( configENABLE_TRUSTZONE == 1 )
    /* Secure components includes. */
    #अन्तर्भाव "secure_context.h"
    #अन्तर्भाव "secure_init.h"
#यदि_अन्तः /* configENABLE_TRUSTZONE */

#अपरिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE

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
#यदि ( ( config_सततम्_FREERTOS_SECURE_ONLY == 1 ) && ( configENABLE_TRUSTZONE == 1 ) )
    #दोषः TrustZone needs गन्तव्यम् be disabled अन्तर् क्रमः गन्तव्यम् सततम् FreeRTOS on the Secure Side.
#यदि_अन्तः

/**
 * Cortex-M23 does not have non-secure PSPLIM. We should use PSPLIM on Cortex-M23
 * only when FreeRTOS runs on secure side.
 */
#यदि ( ( पत्तनम्_HAS_ARMV8_M_MAIN_EXTENSION == 0 ) && ( config_सततम्_FREERTOS_SECURE_ONLY == 0 ) )
    #परिभाषय पत्तनम्_USE_PSPLIM_पञ्जिकाकोशः    0
#अन्यथा
    #परिभाषय पत्तनम्_USE_PSPLIM_पञ्जिकाकोशः    1
#यदि_अन्तः
/*-----------------------------------------------------------*/

/**
 * @brief Prototype of all Interrupt Service Routines (ISRs).
 */
प्रकारनिर्देश शून्य ( * पत्तनम्_ISR_t )( शून्य );
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the NVIC.
 */
#परिभाषय पत्तनम्_NVIC_SYSTICK_CTRL_REG             ( *( ( चञ्चल uint32_t * ) 0xe000e010 ) )
#परिभाषय पत्तनम्_NVIC_SYSTICK_आरोपय_REG             ( *( ( चञ्चल uint32_t * ) 0xe000e014 ) )
#परिभाषय पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG    ( *( ( चञ्चल uint32_t * ) 0xe000e018 ) )
#परिभाषय पत्तनम्_NVIC_SHPR3_REG                    ( *( ( चञ्चल uint32_t * ) 0xe000ed20 ) )
#परिभाषय पत्तनम्_NVIC_SYSTICK_ENABLE_BIT           ( 1UL << 0UL )
#परिभाषय पत्तनम्_NVIC_SYSTICK_INT_BIT              ( 1UL << 1UL )
#परिभाषय पत्तनम्_NVIC_SYSTICK_CLK_BIT              ( 1UL << 2UL )
#परिभाषय पत्तनम्_NVIC_SYSTICK_गणनम्_FLAG_BIT       ( 1UL << 16UL )
#परिभाषय पत्तनम्_NVIC_PEND_SYSTICK_CLEAR_BIT       ( 1UL << 25UL )
#परिभाषय पत्तनम्_NVIC_PEND_SYSTICK_समुच्चयः_BIT         ( 1UL << 26UL )
#परिभाषय पत्तनम्_MIN_व्यवधानम्_प्राथमिकता            ( 255UL )
#परिभाषय पत्तनम्_NVIC_PENDSV_PRI                   ( पत्तनम्_MIN_व्यवधानम्_प्राथमिकता << 16UL )
#परिभाषय पत्तनम्_NVIC_SYSTICK_PRI                  ( पत्तनम्_MIN_व्यवधानम्_प्राथमिकता << 24UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the SCB.
 */
#परिभाषय पत्तनम्_SCB_VTOR_REG                      ( *( ( पत्तनम्_ISR_t ** ) 0xe000ed08 ) )
#परिभाषय पत्तनम्_SCB_SYS_HANDLER_CTRL_STATE_REG    ( *( ( चञ्चल uint32_t * ) 0xe000ed24 ) )
#परिभाषय पत्तनम्_SCB_MEM_FAULT_ENABLE_BIT          ( 1UL << 16UL )
#परिभाषय पत्तनम्_SCB_USG_FAULT_ENABLE_BIT          ( 1UL << 18UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants used to check the installation of the FreeRTOS interrupt handlers.
 */
#परिभाषय पत्तनम्_सदिशम्_सूचकांक_SVC       ( 11 )
#परिभाषय पत्तनम्_सदिशम्_सूचकांक_PENDSV    ( 14 )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to check the validity of an interrupt priority.
 */
#परिभाषय पत्तनम्_NVIC_SHPR2_REG                 ( *( ( चञ्चल uint32_t * ) 0xE000ED1C ) )
#परिभाषय पत्तनम्_FIRST_USER_व्यवधानम्_सङ्ख्या    ( 16 )
#परिभाषय पत्तनम्_NVIC_IP_REGISTERS_विस्थापनम्_16    ( 0xE000E3F0 )
#परिभाषय पत्तनम्_AIRCR_REG                      ( *( ( चञ्चल uint32_t * ) 0xE000ED0C ) )
#परिभाषय पत्तनम्_शिखरम्_BIT_सम्बन्धि_BYTE                ( ( uint8_t ) 0x80 )
#परिभाषय पत्तनम्_MAX_PRIGROUP_द्वयङ्काः              ( ( uint8_t ) 7 )
#परिभाषय पत्तनम्_प्राथमिकता_गणः_आवरणम्            ( 0x07UL << 8UL )
#परिभाषय पत्तनम्_PRIGROUP_सरणम्                 ( 8UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants used during system call enter and exit.
 */
#परिभाषय पत्तनम्_PSR_राशिः_PADDING_आवरणम्              ( 1UL << 9UL )
#परिभाषय पत्तनम्_EXC_RETURN_राशिः_FRAME_TYPE_आवरणम्    ( 1UL << 4UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the FPU.
 */
#परिभाषय पत्तनम्_CPACR               ( ( चञ्चल uint32_t * ) 0xe000ed88 ) /* Coprocessor Access Control Register. */
#परिभाषय पत्तनम्_CPACR_CP10_मानम्    ( 3UL )
#परिभाषय पत्तनम्_CPACR_CP11_मानम्    पत्तनम्_CPACR_CP10_मानम्
#परिभाषय पत्तनम्_CPACR_CP10_POS      ( 20UL )
#परिभाषय पत्तनम्_CPACR_CP11_POS      ( 22UL )

#परिभाषय पत्तनम्_FPCCR               ( ( चञ्चल uint32_t * ) 0xe000ef34 ) /* Floating Point Context Control Register. */
#परिभाषय पत्तनम्_FPCCR_ASPEN_POS     ( 31UL )
#परिभाषय पत्तनम्_FPCCR_ASPEN_आवरणम्    ( 1UL << पत्तनम्_FPCCR_ASPEN_POS )
#परिभाषय पत्तनम्_FPCCR_LSPEN_POS     ( 30UL )
#परिभाषय पत्तनम्_FPCCR_LSPEN_आवरणम्    ( 1UL << पत्तनम्_FPCCR_LSPEN_POS )
/*-----------------------------------------------------------*/

/**
 * @brief Offsets in the stack to the parameters when inside the SVC handler.
 */
#परिभाषय पत्तनम्_विस्थापनम्_गन्तव्यम्_LR     ( 5 )
#परिभाषय पत्तनम्_विस्थापनम्_गन्तव्यम्_PC     ( 6 )
#परिभाषय पत्तनम्_विस्थापनम्_गन्तव्यम्_PSR    ( 7 )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the MPU.
 */
#परिभाषय पत्तनम्_MPU_TYPE_REG                        ( *( ( चञ्चल uint32_t * ) 0xe000ed90 ) )
#परिभाषय पत्तनम्_MPU_CTRL_REG                        ( *( ( चञ्चल uint32_t * ) 0xe000ed94 ) )
#परिभाषय पत्तनम्_MPU_RNR_REG                         ( *( ( चञ्चल uint32_t * ) 0xe000ed98 ) )

#परिभाषय पत्तनम्_MPU_RBAR_REG                        ( *( ( चञ्चल uint32_t * ) 0xe000ed9c ) )
#परिभाषय पत्तनम्_MPU_RLAR_REG                        ( *( ( चञ्चल uint32_t * ) 0xe000eda0 ) )

#परिभाषय पत्तनम्_MPU_RBAR_A1_REG                     ( *( ( चञ्चल uint32_t * ) 0xe000eda4 ) )
#परिभाषय पत्तनम्_MPU_RLAR_A1_REG                     ( *( ( चञ्चल uint32_t * ) 0xe000eda8 ) )

#परिभाषय पत्तनम्_MPU_RBAR_A2_REG                     ( *( ( चञ्चल uint32_t * ) 0xe000edac ) )
#परिभाषय पत्तनम्_MPU_RLAR_A2_REG                     ( *( ( चञ्चल uint32_t * ) 0xe000edb0 ) )

#परिभाषय पत्तनम्_MPU_RBAR_A3_REG                     ( *( ( चञ्चल uint32_t * ) 0xe000edb4 ) )
#परिभाषय पत्तनम्_MPU_RLAR_A3_REG                     ( *( ( चञ्चल uint32_t * ) 0xe000edb8 ) )

#परिभाषय पत्तनम्_MPU_MAIR0_REG                       ( *( ( चञ्चल uint32_t * ) 0xe000edc0 ) )
#परिभाषय पत्तनम्_MPU_MAIR1_REG                       ( *( ( चञ्चल uint32_t * ) 0xe000edc4 ) )

#परिभाषय पत्तनम्_MPU_RBAR_स्थानाङ्कः_आवरणम्               ( 0xffffffe0 ) /* Must be 32-byte aligned. */
#परिभाषय पत्तनम्_MPU_RLAR_स्थानाङ्कः_आवरणम्               ( 0xffffffe0 ) /* Must be 32-byte aligned. */

#परिभाषय पत्तनम्_MPU_RBAR_ACCESS_PERMISSIONS_आवरणम्    ( 3UL << 1UL )

#परिभाषय पत्तनम्_MPU_MAIR_ATTR0_POS                  ( 0UL )
#परिभाषय पत्तनम्_MPU_MAIR_ATTR0_आवरणम्                 ( 0x000000ff )

#परिभाषय पत्तनम्_MPU_MAIR_ATTR1_POS                  ( 8UL )
#परिभाषय पत्तनम्_MPU_MAIR_ATTR1_आवरणम्                 ( 0x0000ff00 )

#परिभाषय पत्तनम्_MPU_MAIR_ATTR2_POS                  ( 16UL )
#परिभाषय पत्तनम्_MPU_MAIR_ATTR2_आवरणम्                 ( 0x00ff0000 )

#परिभाषय पत्तनम्_MPU_MAIR_ATTR3_POS                  ( 24UL )
#परिभाषय पत्तनम्_MPU_MAIR_ATTR3_आवरणम्                 ( 0xff000000 )

#परिभाषय पत्तनम्_MPU_MAIR_ATTR4_POS                  ( 0UL )
#परिभाषय पत्तनम्_MPU_MAIR_ATTR4_आवरणम्                 ( 0x000000ff )

#परिभाषय पत्तनम्_MPU_MAIR_ATTR5_POS                  ( 8UL )
#परिभाषय पत्तनम्_MPU_MAIR_ATTR5_आवरणम्                 ( 0x0000ff00 )

#परिभाषय पत्तनम्_MPU_MAIR_ATTR6_POS                  ( 16UL )
#परिभाषय पत्तनम्_MPU_MAIR_ATTR6_आवरणम्                 ( 0x00ff0000 )

#परिभाषय पत्तनम्_MPU_MAIR_ATTR7_POS                  ( 24UL )
#परिभाषय पत्तनम्_MPU_MAIR_ATTR7_आवरणम्                 ( 0xff000000 )

#परिभाषय पत्तनम्_MPU_RLAR_ATTR_INDEX0                ( 0UL << 1UL )
#परिभाषय पत्तनम्_MPU_RLAR_ATTR_INDEX1                ( 1UL << 1UL )
#परिभाषय पत्तनम्_MPU_RLAR_ATTR_INDEX2                ( 2UL << 1UL )
#परिभाषय पत्तनम्_MPU_RLAR_ATTR_INDEX3                ( 3UL << 1UL )
#परिभाषय पत्तनम्_MPU_RLAR_ATTR_INDEX4                ( 4UL << 1UL )
#परिभाषय पत्तनम्_MPU_RLAR_ATTR_INDEX5                ( 5UL << 1UL )
#परिभाषय पत्तनम्_MPU_RLAR_ATTR_INDEX6                ( 6UL << 1UL )
#परिभाषय पत्तनम्_MPU_RLAR_ATTR_INDEX7                ( 7UL << 1UL )

#परिभाषय पत्तनम्_MPU_RLAR_REGION_ENABLE              ( 1UL )

#यदि ( पत्तनम्_ARMV8_M_MINOR_संस्करणम् >= 1 )

    /* Enable Privileged eXecute Never MPU attribute for the selected memory
     * region. */
    #परिभाषय पत्तनम्_MPU_RLAR_PRIVILEGED_EXECUTE_NEVER    ( 1UL << 4UL )
#यदि_अन्तः /* portARMV8M_MINOR_VERSION >= 1 */

/* Enable privileged access to unmapped region. */
#परिभाषय पत्तनम्_MPU_PRIV_BACKGROUND_ENABLE_BIT    ( 1UL << 2UL )

/* Enable MPU. */
#परिभाषय पत्तनम्_MPU_ENABLE_BIT                    ( 1UL << 0UL )

/* Extract first address of the MPU region as encoded in the
 * RBAR (Region Base Address Register) value. */
#परिभाषय पत्तनम्_EXTRACT_FIRST_स्थानाङ्कः_FROM_RBAR( rbar ) \
    ( ( rbar ) & पत्तनम्_MPU_RBAR_स्थानाङ्कः_आवरणम् )

/* Extract last address of the MPU region as encoded in the
 * RLAR (Region Limit Address Register) value. */
#परिभाषय पत्तनम्_EXTRACT_चरमः_स्थानाङ्कः_FROM_RLAR( rlar ) \
    ( ( ( rlar ) & पत्तनम्_MPU_RLAR_स्थानाङ्कः_आवरणम् ) | ~पत्तनम्_MPU_RLAR_स्थानाङ्कः_आवरणम् )

/* Does addr lies within [start, end] address range? */
#परिभाषय पत्तनम्_IS_स्थानाङ्कः_WITHIN_RANGE( addr, start, अन्तः_2 ) \
    ( ( ( addr ) >= ( start ) ) && ( ( addr ) <= ( अन्तः_2 ) ) )

/* Is the access request satisfied by the available permissions? */
#परिभाषय पत्तनम्_IS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#परिभाषय पत्तनम्_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#परिभाषय पत्तनम्_सङ्कलय_UINT32_WILL_अतिप्रवाहः( a, b )    ( ( a ) > ( पत्तनम्_UINT32_MAX - ( b ) ) )
/*-----------------------------------------------------------*/

/**
 * @brief The maximum 24-bit number.
 *
 * It is needed because the systick is a 24-bit counter.
 */
#परिभाषय पत्तनम्_MAX_24_BIT_सङ्ख्या       ( 0xffffffUL )

/**
 * @brief A fiddle factor to estimate the number of SysTick counts that would
 * have occurred while the SysTick counter is stopped during tickless idle
 * calculations.
 */
#परिभाषय पत्तनम्_MISSED_COUNTS_गुणकः    ( 94UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to set up the initial stack.
 */
#परिभाषय पत्तनम्_INITIAL_XPSR    ( 0x01000000 )

#यदि ( config_सततम्_FREERTOS_SECURE_ONLY == 1 )

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
    #परिभाषय पत्तनम्_INITIAL_EXC_RETURN    ( 0xfffffffd )
#अन्यथा

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
    #परिभाषय पत्तनम्_INITIAL_EXC_RETURN    ( 0xffffffbc )
#यदि_अन्तः /* configRUN_FREERTOS_SECURE_ONLY */

/**
 * @brief CONTROL register privileged bit mask.
 *
 * Bit[0] in CONTROL register tells the privilege:
 *  Bit[0] = 0 ==> The task is privileged.
 *  Bit[0] = 1 ==> The task is not privileged.
 */
#परिभाषय पत्तनम्_CONTROL_PRIVILEGED_आवरणम्         ( 1UL << 0UL )

/**
 * @brief Initial CONTROL register values.
 */
#परिभाषय पत्तनम्_INITIAL_CONTROL_UNPRIVILEGED    ( 0x3 )
#परिभाषय पत्तनम्_INITIAL_CONTROL_PRIVILEGED      ( 0x2 )

/**
 * @brief Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register.
 */
#यदि_अपरिभाषितम् configSYSTICK_CLOCK_HZ
    #परिभाषय configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #परिभाषय पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG    ( पत्तनम्_NVIC_SYSTICK_CLK_BIT )
#अन्यथा
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #परिभाषय पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG    ( 0 )
#यदि_अन्तः

/**
 * @brief Let the user override the pre-loading of the initial LR with the
 * address of prvTaskExitError() in case it messes up unwinding of the stack
 * in the debugger.
 */
#यदि_परिभाषितम् config_TASK_RETURN_स्थानाङ्कः
    #परिभाषय पत्तनम्_TASK_RETURN_स्थानाङ्कः    config_TASK_RETURN_स्थानाङ्कः
#अन्यथा
    #परिभाषय पत्तनम्_TASK_RETURN_स्थानाङ्कः    prvTaskExitError
#यदि_अन्तः

/**
 * @brief If portPRELOAD_REGISTERS then registers will be given an initial value
 * when a task is created. This helps in debugging at the cost of code size.
 */
#परिभाषय पत्तनम्_PRELOAD_REGISTERS    1

/**
 * @brief A task is created without a secure context, and must call
 * portALLOCATE_SECURE_CONTEXT() to give itself a secure context before it makes
 * any secure calls.
 */
#परिभाषय पत्तनम्_NO_SECURE_CONTEXT    0

/**
 * @brief Constants required to check and configure PACBTI security feature implementation.
 */
#यदि ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )

    #परिभाषय पत्तनम्_ID_ISAR5_REG       ( *( ( चञ्चल uint32_t * ) 0xe000ed74 ) )

    #परिभाषय पत्तनम्_CONTROL_UPAC_EN    ( 1UL << 7UL )
    #परिभाषय पत्तनम्_CONTROL_PAC_EN     ( 1UL << 6UL )
    #परिभाषय पत्तनम्_CONTROL_UBTI_EN    ( 1UL << 5UL )
    #परिभाषय पत्तनम्_CONTROL_BTI_EN     ( 1UL << 4UL )

#यदि_अन्तः /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Used to catch tasks that attempt to return from their implementing
 * function.
 */
स्थिर शून्य prvTaskExitError( शून्य );

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Extract MPU region's access permissions from the Region Base Address
     * Register (RBAR) value.
     *
     * @param ulRBARValue RBAR value for the MPU region.
     *
     * @return uint32_t Access permissions.
     */
    स्थिर uint32_t prvGetRegionAccessPermissions( uint32_t ulRBARValue ) PRIVILEGED_FUNCTION;
#यदि_अन्तः /* configENABLE_MPU == 1 && configUSE_MPU_WRAPPERS_V1 == 0 */

#यदि ( configENABLE_MPU == 1 )

    /**
     * @brief Setup the Memory Protection Unit (MPU).
     */
    स्थिर शून्य prv_सज्जता_MPU( शून्य ) PRIVILEGED_FUNCTION;
#यदि_अन्तः /* configENABLE_MPU */

#यदि ( configENABLE_FPU == 1 )

    /**
     * @brief Setup the Floating Point Unit (FPU).
     */
    स्थिर शून्य prv_सज्जता_FPU( शून्य ) PRIVILEGED_FUNCTION;
#यदि_अन्तः /* configENABLE_FPU */

#यदि ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )

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
    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
        स्थिर uint32_t prvConfigurePACBTI( आधारः_Type_t x_Write_Control_पञ्जिकाकोशः );
    #अन्यथा /* #if ( configNUMBER_OF_CORES == 1 ) */
        uint32_t vConfigurePACBTI( आधारः_Type_t x_Write_Control_पञ्जिकाकोशः );
    #यदि_अन्तः /* #if ( configNUMBER_OF_CORES == 1 ) */

#यदि_अन्तः /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

/**
 * @brief Setup the timer to generate the tick interrupts.
 *
 * The implementation in this file is weak to allow application writers to
 * change the timer used to generate the tick interrupt.
 */
शून्य v_पत्तनम्_सज्जता_Timer_व्यवधानम्( शून्य ) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether the current execution context is interrupt.
 *
 * @return pdTRUE if the current execution context is interrupt, pdFALSE
 * otherwise.
 */
आधारः_Type_t x_पत्तनम्_Is_Inside_व्यवधानम्( शून्य );

/**
 * @brief Yield the processor.
 */
शून्य v_पत्तनम्_Yield( शून्य ) PRIVILEGED_FUNCTION;

/**
 * @brief Enter critical section.
 */
शून्य v_पत्तनम्_Enter_Critical( शून्य ) PRIVILEGED_FUNCTION;

/**
 * @brief Exit from critical section.
 */
शून्य v_पत्तनम्_Exit_Critical( शून्य ) PRIVILEGED_FUNCTION;

/**
 * @brief SysTick handler.
 */
शून्य SysTick_Handler( शून्य ) PRIVILEGED_FUNCTION;

/**
 * @brief C part of SVC handler.
 */
पत्तनम्_DONT_DISCARD शून्य v_पत्तनम्_SVCHandler_C( uint32_t * pul_Caller_राशिः_स्थानाङ्कः ) PRIVILEGED_FUNCTION;

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the system call stack so that upon returning from
     * SVC, the system call stack is used.
     *
     * @param pulTaskStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    शून्य vSystemCallEnter( uint32_t * pul_Task_राशिः,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_सङ्ख्या ) PRIVILEGED_FUNCTION;

#यदि_अन्तः /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    शून्य vRequestSystemCallExit( शून्य ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#यदि_अन्तः /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param pulSystemCallStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     */
    शून्य vSystemCallExit( uint32_t * pul_System_Call_राशिः,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#यदि_अन्तः /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#यदि ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    आधारः_Type_t x_पत्तनम्_Is_Task_Privileged( शून्य ) PRIVILEGED_FUNCTION;

#यदि_अन्तः /* configENABLE_MPU == 1 */

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )

    /**
     * @brief Platform/Application-defined function that wakes up the secondary cores.
     *
     * @return pdTRUE if the secondary cores were successfully woken up.
     *         pdFALSE otherwise.
     */
    बाह्य आधारः_Type_t configWAKE_SECONDARY_CORES( शून्य );

#यदि_अन्तः /* #if ( configNUMBER_OF_CORES > 1 ) */

/**
 * @brief Configures interrupt priorities.
 */
शून्य v_पत्तनम्_Configure_व्यवधानम्_Priorities( शून्य ) PRIVILEGED_FUNCTION;
/*-----------------------------------------------------------*/

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief This variable is set to pdTRUE when the scheduler is started.
     */
    PRIVILEGED_दत्त स्थिर आधारः_Type_t xSchedulerRunning = pdFALSE;

#यदि_अन्तः /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/**
 * @brief Each task maintains its own interrupt status in the critical nesting
 * variable.
 */
#यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
    PRIVILEGED_दत्त स्थिर चञ्चल uint32_t ulCriticalNesting = 0UL;
#अन्यथा /* #if ( configNUMBER_OF_CORES == 1 ) */
    PRIVILEGED_दत्त चञ्चल uint32_t ulCriticalNestings[ config_सङ्ख्या_सम्बन्धि_CORES ] = { 0 };
    /* Flags to check if the secondary cores are ready. */
    PRIVILEGED_दत्त चञ्चल uint8_t ucSecondaryCoresReadyFlags[ config_सङ्ख्या_सम्बन्धि_CORES - 1 ] = { 0 };
    /* Flag to indicate that the primary core has completed its initialisation. */
    PRIVILEGED_दत्त चञ्चल uint8_t uc_Primary_Core_Init_समाप्तम्_Flag = 0;
 #यदि_अन्तः /* #if ( configNUMBER_OF_CORES == 1 ) */

#यदि ( configENABLE_TRUSTZONE == 1 )

    /**
     * @brief Saved as part of the task context to indicate which context the
     * task is using on the secure side.
     */
    PRIVILEGED_दत्त पत्तनम्_DONT_DISCARD चञ्चल SecureContextHandle_t xSecureContext = पत्तनम्_NO_SECURE_CONTEXT;
#यदि_अन्तः /* configENABLE_TRUSTZONE */

/**
 * @brief Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#यदि ( ( configASSERT_DEFINED == 1 ) && ( पत्तनम्_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) )

    स्थिर uint8_t uc_Max_Sys_Call_प्राथमिकता = 0;
    स्थिर uint32_t ulMaxPRIGROUPValue = 0;
    स्थिर ध्रुव चञ्चल uint8_t * ध्रुव pc_व्यवधानम्_प्राथमिकता_Registers = ( ध्रुव चञ्चल uint8_t * ) पत्तनम्_NVIC_IP_REGISTERS_विस्थापनम्_16;

#यदि_अन्तः /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */

#यदि ( configUSE_TICKLESS_IDLE == 1 )

    /**
     * @brief The number of SysTick increments that make up one tick period.
     */
    PRIVILEGED_दत्त स्थिर uint32_t ulTimerCountsForOneTick = 0;

    /**
     * @brief The maximum number of tick periods that can be suppressed is
     * limited by the 24 bit resolution of the SysTick timer.
     */
    PRIVILEGED_दत्त स्थिर uint32_t x_अधिकतमम्_Possible_Suppressed_Ticks = 0;

    /**
     * @brief Compensate for the CPU cycles that pass while the SysTick is
     * stopped (low power functionality only).
     */
    PRIVILEGED_दत्त स्थिर uint32_t ulStoppedTimerCompensation = 0;
#यदि_अन्तः /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

#यदि ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) शून्य v_पत्तनम्_Suppress_Ticks_And_Sleep( TickType_t xExpectedIdleTime )
    {
        uint32_t ul_Reload_मानम्, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_वामः;
        TickType_t xModifiableIdleTime;

        /* Make sure the SysTick reload value does not overflow the counter. */
        यदि( xExpectedIdleTime > x_अधिकतमम्_Possible_Suppressed_Ticks )
        {
            xExpectedIdleTime = x_अधिकतमम्_Possible_Suppressed_Ticks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm चञ्चल ( "cpsid i" ::: "memory" );
        __asm चञ्चल ( "dsb" );
        __asm चञ्चल ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        यदि( e_Task_Confirm_Sleep_बहुलकम्_स्थितिः() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the cpsid instruction
             * above. */
            __asm चञ्चल ( "cpsie i" ::: "memory" );
        }
        अन्यथा
        {
            /* Stop the SysTick momentarily.  The time the SysTick is stopped for
             * is accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            पत्तनम्_NVIC_SYSTICK_CTRL_REG = ( पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG | पत्तनम्_NVIC_SYSTICK_INT_BIT );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_वामः = पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG;

            यदि( ul_Sys_Tick_Decrements_वामः == 0 )
            {
                ul_Sys_Tick_Decrements_वामः = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_मानम् = ul_Sys_Tick_Decrements_वामः + ( ulTimerCountsForOneTick * ( xExpectedIdleTime - 1UL ) );

            यदि( ( पत्तनम्_NVIC_INT_CTRL_REG & पत्तनम्_NVIC_PEND_SYSTICK_समुच्चयः_BIT ) != 0 )
            {
                पत्तनम्_NVIC_INT_CTRL_REG = पत्तनम्_NVIC_PEND_SYSTICK_CLEAR_BIT;
                ul_Reload_मानम् -= ulTimerCountsForOneTick;
            }

            यदि( ul_Reload_मानम् > ulStoppedTimerCompensation )
            {
                ul_Reload_मानम् -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ul_Reload_मानम्;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG = 0UL;

            /* Restart SysTick. */
            पत्तनम्_NVIC_SYSTICK_CTRL_REG |= पत्तनम्_NVIC_SYSTICK_ENABLE_BIT;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            xModifiableIdleTime = xExpectedIdleTime;
            configPRE_SLEEP_PROCESSING( xModifiableIdleTime );

            यदि( xModifiableIdleTime > 0 )
            {
                __asm चञ्चल ( "dsb" ::: "memory" );
                __asm चञ्चल ( "wfi" );
                __asm चञ्चल ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( xExpectedIdleTime );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the cpsid instruction above. */
            __asm चञ्चल ( "cpsie i" ::: "memory" );
            __asm चञ्चल ( "dsb" );
            __asm चञ्चल ( "isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm चञ्चल ( "cpsid i" ::: "memory" );
            __asm चञ्चल ( "dsb" );
            __asm चञ्चल ( "isb" );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            पत्तनम्_NVIC_SYSTICK_CTRL_REG = ( पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG | पत्तनम्_NVIC_SYSTICK_INT_BIT );

            /* Determine whether the SysTick has already counted to zero. */
            यदि( ( पत्तनम्_NVIC_SYSTICK_CTRL_REG & पत्तनम्_NVIC_SYSTICK_गणनम्_FLAG_BIT ) != 0 )
            {
                uint32_t ul_Calculated_आरोपय_मानम्;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_आरोपय_मानम् = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_मानम् - पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                यदि( ( ul_Calculated_आरोपय_मानम् <= ulStoppedTimerCompensation ) || ( ul_Calculated_आरोपय_मानम् > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_आरोपय_मानम् = ( ulTimerCountsForOneTick - 1UL );
                }

                पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ul_Calculated_आरोपय_मानम्;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = xExpectedIdleTime - 1UL;
            }
            अन्यथा
            {
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_वामः = पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG;
                #यदि ( पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG != पत्तनम्_NVIC_SYSTICK_CLK_BIT )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    यदि( ul_Sys_Tick_Decrements_वामः == 0 )
                    {
                        ul_Sys_Tick_Decrements_वामः = ul_Reload_मानम्;
                    }
                }
                #यदि_अन्तः /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( xExpectedIdleTime * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_वामः;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG = 0UL;
            पत्तनम्_NVIC_SYSTICK_CTRL_REG = पत्तनम्_NVIC_SYSTICK_CLK_BIT | पत्तनम्_NVIC_SYSTICK_INT_BIT | पत्तनम्_NVIC_SYSTICK_ENABLE_BIT;
            #यदि ( पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG == पत्तनम्_NVIC_SYSTICK_CLK_BIT )
            {
                पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ulTimerCountsForOneTick - 1UL;
            }
            #अन्यथा
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                पत्तनम्_NVIC_SYSTICK_CTRL_REG = पत्तनम्_NVIC_SYSTICK_CLK_BIT | पत्तनम्_NVIC_SYSTICK_INT_BIT;

                यदि( ( पत्तनम्_NVIC_SYSTICK_CTRL_REG & पत्तनम्_NVIC_SYSTICK_गणनम्_FLAG_BIT ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG = 0;
                }

                पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ulTimerCountsForOneTick - 1UL;
                पत्तनम्_NVIC_SYSTICK_CTRL_REG = पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG | पत्तनम्_NVIC_SYSTICK_INT_BIT | पत्तनम्_NVIC_SYSTICK_ENABLE_BIT;
            }
            #यदि_अन्तः /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            v_Task_चरणः_Tick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __asm चञ्चल ( "cpsie i" ::: "memory" );
        }
    }

#यदि_अन्तः /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

__attribute__( ( weak ) ) शून्य v_पत्तनम्_सज्जता_Timer_व्यवधानम्( शून्य ) /* PRIVILEGED_FUNCTION */
{
    /* Calculate the constants required to configure the tick interrupt. */
    #यदि ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_दरः_HZ );
        x_अधिकतमम्_Possible_Suppressed_Ticks = पत्तनम्_MAX_24_BIT_सङ्ख्या / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = पत्तनम्_MISSED_COUNTS_गुणकः / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #यदि_अन्तः /* configUSE_TICKLESS_IDLE */

    /* Stop and reset SysTick.
     *
     * QEMU versions older than 7.0.0 contain a bug which causes an error if we
     * enable SysTick without first selecting a valid clock source. We trigger
     * the bug if we change clock sources from a clock with a zero clock period
     * to one with a nonzero clock period and enable Systick at the same time.
     * So we configure the CLKSOURCE bit here, prior to setting the ENABLE bit.
     * This workaround avoids the bug in QEMU versions older than 7.0.0. */
    पत्तनम्_NVIC_SYSTICK_CTRL_REG = पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG;
    पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_दरः_HZ ) - 1UL;
    पत्तनम्_NVIC_SYSTICK_CTRL_REG = पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG | पत्तनम्_NVIC_SYSTICK_INT_BIT | पत्तनम्_NVIC_SYSTICK_ENABLE_BIT;
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvTaskExitError( शून्य )
{
    चञ्चल uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
        configASSERT( ulCriticalNesting == ~0UL );
    #अन्यथा /* #if ( configNUMBER_OF_CORES == 1 ) */
        configASSERT( ulCriticalNestings[ पत्तनम्_GET_CORE_ID() ] == ~0UL );
    #यदि_अन्तः /* #if ( configNUMBER_OF_CORES == 1 ) */
    पत्तनम्_DISABLE_INTERRUPTS();

    यावत्( ulDummy == 0 )
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

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    स्थिर uint32_t prvGetRegionAccessPermissions( uint32_t ulRBARValue ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ulAccessPermissions = 0;

        यदि( ( ulRBARValue & पत्तनम्_MPU_RBAR_ACCESS_PERMISSIONS_आवरणम् ) == पत्तनम्_MPU_REGION_READ_ONLY )
        {
            ulAccessPermissions = tskMPU_READ_PERMISSION;
        }

        यदि( ( ulRBARValue & पत्तनम्_MPU_RBAR_ACCESS_PERMISSIONS_आवरणम् ) == पत्तनम्_MPU_REGION_READ_WRITE )
        {
            ulAccessPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
        }

        प्रत्यागम ulAccessPermissions;
    }

#यदि_अन्तः /* configENABLE_MPU == 1 && configUSE_MPU_WRAPPERS_V1 == 0 */
/*-----------------------------------------------------------*/

#यदि ( configENABLE_MPU == 1 )

    स्थिर शून्य prv_सज्जता_MPU( शून्य ) /* PRIVILEGED_FUNCTION */
    {
        #यदि defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            बाह्य uint32_t * __privileged_functions_start__;
            बाह्य uint32_t * __privileged_functions_end__;
            बाह्य uint32_t * __syscalls_flash_start__;
            बाह्य uint32_t * __syscalls_flash_end__;
            बाह्य uint32_t * __unprivileged_flash_start__;
            बाह्य uint32_t * __unprivileged_flash_end__;
            बाह्य uint32_t * __privileged_sram_start__;
            बाह्य uint32_t * __privileged_sram_end__;
        #अन्यथा /* if defined( __ARMCC_VERSION ) */
            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint32_t __privileged_functions_start__[];
            बाह्य uint32_t __privileged_functions_end__[];
            बाह्य uint32_t __syscalls_flash_start__[];
            बाह्य uint32_t __syscalls_flash_end__[];
            बाह्य uint32_t __unprivileged_flash_start__[];
            बाह्य uint32_t __unprivileged_flash_end__[];
            बाह्य uint32_t __privileged_sram_start__[];
            बाह्य uint32_t __privileged_sram_end__[];
        #यदि_अन्तः /* defined( __ARMCC_VERSION ) */

        /* The only permitted number of regions are 8 or 16. */
        configASSERT( ( config_योग_MPU_REGIONS == 8 ) || ( config_योग_MPU_REGIONS == 16 ) );

        /* MAIR0 - Index 0. */
        पत्तनम्_MPU_MAIR0_REG |= ( ( पत्तनम्_MPU_प्रसामान्यम्_स्मृतिः_BUFFERABLE_CACHEABLE << पत्तनम्_MPU_MAIR_ATTR0_POS ) & पत्तनम्_MPU_MAIR_ATTR0_आवरणम् );
        /* MAIR0 - Index 1. */
        पत्तनम्_MPU_MAIR0_REG |= ( ( पत्तनम्_MPU_DEVICE_स्मृतिः_n_Gn_RE << पत्तनम्_MPU_MAIR_ATTR1_POS ) & पत्तनम्_MPU_MAIR_ATTR1_आवरणम् );

        /* Setup privileged flash as Read Only so that privileged tasks can
         * read it but not modify. */
        पत्तनम्_MPU_RNR_REG = पत्तनम्_PRIVILEGED_FLASH_REGION;
        पत्तनम्_MPU_RBAR_REG = ( ( ( uint32_t ) __privileged_functions_start__ ) & पत्तनम्_MPU_RBAR_स्थानाङ्कः_आवरणम् ) |
                           ( पत्तनम्_MPU_REGION_NON_SHAREABLE ) |
                           ( पत्तनम्_MPU_REGION_PRIVILEGED_READ_ONLY );
        पत्तनम्_MPU_RLAR_REG = ( ( ( uint32_t ) __privileged_functions_end__ ) & पत्तनम्_MPU_RLAR_स्थानाङ्कः_आवरणम् ) |
                           ( पत्तनम्_MPU_RLAR_ATTR_INDEX0 ) |
                           ( पत्तनम्_MPU_RLAR_REGION_ENABLE );

        /* Setup unprivileged flash as Read Only by both privileged and
         * unprivileged tasks. All tasks can read it but no-one can modify. */
        पत्तनम्_MPU_RNR_REG = पत्तनम्_UNPRIVILEGED_FLASH_REGION;
        पत्तनम्_MPU_RBAR_REG = ( ( ( uint32_t ) __unprivileged_flash_start__ ) & पत्तनम्_MPU_RBAR_स्थानाङ्कः_आवरणम् ) |
                           ( पत्तनम्_MPU_REGION_NON_SHAREABLE ) |
                           ( पत्तनम्_MPU_REGION_READ_ONLY );
        पत्तनम्_MPU_RLAR_REG = ( ( ( uint32_t ) __unprivileged_flash_end__ ) & पत्तनम्_MPU_RLAR_स्थानाङ्कः_आवरणम् ) |
                           ( पत्तनम्_MPU_RLAR_ATTR_INDEX0 ) |
                           ( पत्तनम्_MPU_RLAR_REGION_ENABLE );

        /* Setup unprivileged syscalls flash as Read Only by both privileged
         * and unprivileged tasks. All tasks can read it but no-one can modify. */
        पत्तनम्_MPU_RNR_REG = पत्तनम्_UNPRIVILEGED_SYSCALLS_REGION;
        पत्तनम्_MPU_RBAR_REG = ( ( ( uint32_t ) __syscalls_flash_start__ ) & पत्तनम्_MPU_RBAR_स्थानाङ्कः_आवरणम् ) |
                           ( पत्तनम्_MPU_REGION_NON_SHAREABLE ) |
                           ( पत्तनम्_MPU_REGION_READ_ONLY );
        पत्तनम्_MPU_RLAR_REG = ( ( ( uint32_t ) __syscalls_flash_end__ ) & पत्तनम्_MPU_RLAR_स्थानाङ्कः_आवरणम् ) |
                           ( पत्तनम्_MPU_RLAR_ATTR_INDEX0 ) |
                           ( पत्तनम्_MPU_RLAR_REGION_ENABLE );

        /* Setup RAM containing kernel data for privileged access only. */
        पत्तनम्_MPU_RNR_REG = पत्तनम्_PRIVILEGED_RAM_REGION;
        पत्तनम्_MPU_RBAR_REG = ( ( ( uint32_t ) __privileged_sram_start__ ) & पत्तनम्_MPU_RBAR_स्थानाङ्कः_आवरणम् ) |
                           ( पत्तनम्_MPU_REGION_NON_SHAREABLE ) |
                           ( पत्तनम्_MPU_REGION_PRIVILEGED_READ_WRITE ) |
                           ( पत्तनम्_MPU_REGION_EXECUTE_NEVER );
        पत्तनम्_MPU_RLAR_REG = ( ( ( uint32_t ) __privileged_sram_end__ ) & पत्तनम्_MPU_RLAR_स्थानाङ्कः_आवरणम् ) |
                           ( पत्तनम्_MPU_RLAR_ATTR_INDEX0 ) |
                           ( पत्तनम्_MPU_RLAR_REGION_ENABLE );

        /* Enable mem fault. */
        पत्तनम्_SCB_SYS_HANDLER_CTRL_STATE_REG |= पत्तनम्_SCB_MEM_FAULT_ENABLE_BIT;

        /* Enable MPU with privileged background access i.e. unmapped
         * regions have privileged access. */
        पत्तनम्_MPU_CTRL_REG |= ( पत्तनम्_MPU_PRIV_BACKGROUND_ENABLE_BIT | पत्तनम्_MPU_ENABLE_BIT );
    }

#यदि_अन्तः /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#यदि ( configENABLE_FPU == 1 )

    स्थिर शून्य prv_सज्जता_FPU( शून्य ) /* PRIVILEGED_FUNCTION */
    {
        #यदि ( configENABLE_TRUSTZONE == 1 )
        {
            /* Enable non-secure access to the FPU. */
            SecureInit_EnableNSFPUAccess();
        }
        #यदि_अन्तः /* configENABLE_TRUSTZONE */

        /* CP10 = 11 ==> Full access to FPU i.e. both privileged and
         * unprivileged code should be able to access FPU. CP11 should be
         * programmed to the same value as CP10. */
        *( पत्तनम्_CPACR ) |= ( ( पत्तनम्_CPACR_CP10_मानम् << पत्तनम्_CPACR_CP10_POS ) |
                            ( पत्तनम्_CPACR_CP11_मानम् << पत्तनम्_CPACR_CP11_POS )
                            );

        /* ASPEN = 1 ==> Hardware should automatically preserve floating point
         * context on exception entry and restore on exception return.
         * LSPEN = 1 ==> Enable lazy context save of FP state. */
        *( पत्तनम्_FPCCR ) |= ( पत्तनम्_FPCCR_ASPEN_आवरणम् | पत्तनम्_FPCCR_LSPEN_आवरणम् );
    }

#यदि_अन्तः /* configENABLE_FPU */
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Yield( शून्य ) /* PRIVILEGED_FUNCTION */
{
    /* Set a PendSV to request a context switch. */
    पत्तनम्_NVIC_INT_CTRL_REG = पत्तनम्_NVIC_PENDSVSET_BIT;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm चञ्चल ( "dsb" ::: "memory" );
    __asm चञ्चल ( "isb" );
}
/*-----------------------------------------------------------*/

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
    शून्य v_पत्तनम्_Enter_Critical( शून्य ) /* PRIVILEGED_FUNCTION */
    {
        पत्तनम्_DISABLE_INTERRUPTS();
        ulCriticalNesting++;
        /* Barriers are normally not required but do ensure the code is
        * completely within the specified behaviour for the architecture. */
        __asm चञ्चल ( "dsb" ::: "memory" );
        __asm चञ्चल ( "isb" );
    }
    /*-----------------------------------------------------------*/

    शून्य v_पत्तनम्_Exit_Critical( शून्य ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( ulCriticalNesting );
        ulCriticalNesting--;

        यदि( ulCriticalNesting == 0 )
        {
            पत्तनम्_ENABLE_INTERRUPTS();
        }
    }
#यदि_अन्तः /* configNUMBER_OF_CORES == 1 */
/*-----------------------------------------------------------*/

शून्य SysTick_Handler( शून्य ) /* PRIVILEGED_FUNCTION */
{
    uint32_t ul_Previous_आवरणम्;

    ul_Previous_आवरणम् = पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR();
    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )
        UBaseType_t ux_Saved_व्यवधानम्_स्थितिः = पत्तनम्_ENTER_CRITICAL_FROM_ISR();
    #यदि_अन्तः /* if ( configNUMBER_OF_CORES > 1 ) */

    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        यदि( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_गन्तव्यम्_SCHEDULER();
            /* Pend a context switch. */
            पत्तनम्_NVIC_INT_CTRL_REG = पत्तनम्_NVIC_PENDSVSET_BIT;
        }
        अन्यथा
        {
            traceISR_EXIT();
        }
    }
    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )
        पत्तनम्_EXIT_CRITICAL_FROM_ISR( ux_Saved_व्यवधानम्_स्थितिः );
    #यदि_अन्तः /* if ( configNUMBER_OF_CORES > 1 ) */

    पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( ul_Previous_आवरणम् );
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_SVCHandler_C( uint32_t * pul_Caller_राशिः_स्थानाङ्कः ) /* PRIVILEGED_FUNCTION portDONT_DISCARD */
{
    #यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )
        #यदि defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            बाह्य uint32_t * __syscalls_flash_start__;
            बाह्य uint32_t * __syscalls_flash_end__;
        #अन्यथा
            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint32_t __syscalls_flash_start__[];
            बाह्य uint32_t __syscalls_flash_end__[];
        #यदि_अन्तः /* defined( __ARMCC_VERSION ) */
    #यदि_अन्तः /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #यदि ( configENABLE_MPU == 1 )
        #यदि defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            बाह्य uint32_t * __privileged_functions_start__;
            बाह्य uint32_t * __privileged_functions_end__;
        #अन्यथा
            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint32_t __privileged_functions_start__[];
            बाह्य uint32_t __privileged_functions_end__[];
        #यदि_अन्तः /* defined( __ARMCC_VERSION ) */
    #यदि_अन्तः /* configENABLE_MPU == 1 */

    uint32_t ulPC;

    #यदि ( configENABLE_TRUSTZONE == 1 )
        uint32_t ulR0, ulR1;
        बाह्य TaskHandle_t pxCurrentTCB;
        #यदि ( configENABLE_MPU == 1 )
            uint32_t ulControl, ulIsTaskPrivileged;
        #यदि_अन्तः /* configENABLE_MPU */
    #यदि_अन्तः /* configENABLE_TRUSTZONE */
    uint8_t ucSVCNumber;

    /* Register are stored on the stack in the following order - R0, R1, R2, R3,
     * R12, LR, PC, xPSR. */
    ulPC = pul_Caller_राशिः_स्थानाङ्कः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    विकल्प( ucSVCNumber )
    {
    #यदि ( configENABLE_TRUSTZONE == 1 )
        पक्ष पत्तनम्_SVC_ALLOCATE_SECURE_CONTEXT:

            /* R0 contains the stack size passed as parameter to the
             * vPortAllocateSecureContext function. */
            ulR0 = pul_Caller_राशिः_स्थानाङ्कः[ 0 ];

            #यदि ( configENABLE_MPU == 1 )
            {
                /* Read the CONTROL register value. */
                __asm चञ्चल ( "mrs %0, control"  : "=r" ( ulControl ) );

                /* The task that raised the SVC is privileged if Bit[0]
                 * in the CONTROL register is 0. */
                ulIsTaskPrivileged = ( ( ulControl & पत्तनम्_CONTROL_PRIVILEGED_आवरणम् ) == 0 );

                /* Allocate and load a context for the secure task. */
                xSecureContext = SecureContext_AllocateContext( ulR0, ulIsTaskPrivileged, pxCurrentTCB );
            }
            #अन्यथा /* if ( configENABLE_MPU == 1 ) */
            {
                /* Allocate and load a context for the secure task. */
                xSecureContext = SecureContext_AllocateContext( ulR0, pxCurrentTCB );
            }
            #यदि_अन्तः /* configENABLE_MPU */

            configASSERT( xSecureContext != securecontextINVALID_CONTEXT_ID );
            Secure_Context_आरोपय_Context( xSecureContext, pxCurrentTCB );
            भङ्ग;

        पक्ष पत्तनम्_SVC_FREE_SECURE_CONTEXT:
            #यदि ( configENABLE_MPU == 1 )
            यदि( ( ulPC >= ( uint32_t ) __privileged_functions_start__ ) &&
                ( ulPC <= ( uint32_t ) __privileged_functions_end__ ) )
            {
            #यदि_अन्तः /* configENABLE_MPU */
                /* R0 contains TCB being freed and R1 contains the secure
                 * context handle to be freed. */
                ulR0 = pul_Caller_राशिः_स्थानाङ्कः[ 0 ];
                ulR1 = pul_Caller_राशिः_स्थानाङ्कः[ 1 ];

                /* Free the secure context. */
                SecureContext_FreeContext( ( SecureContextHandle_t ) ulR1, ( शून्य * ) ulR0 );
            #यदि ( configENABLE_MPU == 1 )
            }
            #यदि_अन्तः /* configENABLE_MPU */
            भङ्ग;
    #यदि_अन्तः /* configENABLE_TRUSTZONE */

        पक्ष पत्तनम्_SVC_START_SCHEDULER:
            #यदि ( configENABLE_MPU == 1 )
            यदि( ( ulPC >= ( uint32_t ) __privileged_functions_start__ ) &&
                ( ulPC <= ( uint32_t ) __privileged_functions_end__ ) )
            {
            #यदि_अन्तः /* configENABLE_MPU */
                #यदि ( configENABLE_TRUSTZONE == 1 )
                {
                    /* De-prioritize the non-secure exceptions so that the
                     * non-secure pendSV runs at the lowest priority. */
                    SecureInit_DePrioritizeNSExceptions();

                    /* Initialize the secure context management system. */
                    SecureContext_Init();
                }
                #यदि_अन्तः /* configENABLE_TRUSTZONE */

                #यदि ( configENABLE_FPU == 1 )
                {
                    /* Setup the Floating Point Unit (FPU). */
                    prv_सज्जता_FPU();
                }
                #यदि_अन्तः /* configENABLE_FPU */

                /* Setup the context of the first task so that the first task starts
                 * executing. */
                v_Restore_Context_सम्बन्धि_First_Task();
            #यदि ( configENABLE_MPU == 1 )
            }
            #यदि_अन्तः /* configENABLE_MPU */
            भङ्ग;

    #यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )
        पक्ष पत्तनम्_SVC_RAISE_PRIVILEGE:

            /* Only raise the privilege, if the svc was raised from any of
             * the system calls. */
            यदि( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
            {
                vRaisePrivilege();
            }
            भङ्ग;
    #यदि_अन्तः /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #यदि ( configENABLE_MPU == 1 )
        पक्ष पत्तनम्_SVC_YIELD:
            v_पत्तनम्_Yield();
            भङ्ग;
    #यदि_अन्तः /* configENABLE_MPU == 1 */

        स्वभाव:
            /* Incorrect SVC call. */
            configASSERT( pdFALSE );
    }
}
/*-----------------------------------------------------------*/

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    शून्य vSystemCallEnter( uint32_t * pul_Task_राशिः,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_सङ्ख्या ) /* PRIVILEGED_FUNCTION */
    {
        बाह्य TaskHandle_t pxCurrentTCB;
        बाह्य UBaseType_t uxSystemCallImplementations[ अङ्कः_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_राशिः;
        uint32_t ul_Hardware_Saved_Exception_Frame_आकार, ulSystemCallLocation, i;

        #यदि defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            बाह्य uint32_t * __syscalls_flash_start__;
            बाह्य uint32_t * __syscalls_flash_end__;
        #अन्यथा
            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint32_t __syscalls_flash_start__[];
            बाह्य uint32_t __syscalls_flash_end__[];
        #यदि_अन्तः /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PC ];
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
        यदि( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_राशिः_Info.pul_Task_राशिः == रिक्त ) &&
            ( uxSystemCallImplementations[ uc_System_Call_सङ्ख्या ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_राशिः = pxMpuSettings->x_System_Call_राशिः_Info.pul_System_Call_राशिः;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            #यदि ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )
            {
                यदि( ( ulLR & पत्तनम्_EXC_RETURN_राशिः_FRAME_TYPE_आवरणम् ) == 0UL )
                {
                    /* Extended frame i.e. FPU in use. */
                    ul_Hardware_Saved_Exception_Frame_आकार = 26;
                    __asm चञ्चल (
                        " vpush {s0}         \n" /* Trigger lazy stacking. */
                        " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                        ::: "memory"
                        );
                }
                अन्यथा
                {
                    /* Standard frame i.e. FPU not in use. */
                    ul_Hardware_Saved_Exception_Frame_आकार = 8;
                }
            }
            #अन्यथा /* if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */
            {
                ul_Hardware_Saved_Exception_Frame_आकार = 8;
            }
            #यदि_अन्तः /* configENABLE_FPU || configENABLE_MVE */

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_राशिः = pul_System_Call_राशिः - ul_Hardware_Saved_Exception_Frame_आकार;

            /* Copy the stack frame. */
            प्रति( i = 0; i < ul_Hardware_Saved_Exception_Frame_आकार; i++ )
            {
                pul_System_Call_राशिः[ i ] = pul_Task_राशिः[ i ];
            }

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_राशिः_Info.ul_Link_पञ्जिकाकोशः_At_System_Call_प्रविष्टिः = pul_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_LR ];

            /* Store the value of the PSPLIM register before the SVC was raised.
             * We need to restore it when we exit from the system call. */
            #यदि ( पत्तनम्_USE_PSPLIM_पञ्जिकाकोशः == 1 )
            {
                __asm चञ्चल ( "mrs %0, psplim" : "=r" ( pxMpuSettings->x_System_Call_राशिः_Info.ul_राशिः_सीमा_पञ्जिकाकोशः_At_System_Call_प्रविष्टिः ) );
            }
            #यदि_अन्तः

            /* Use the pulSystemCallStack in thread mode. */
            __asm चञ्चल ( "msr psp, %0" : : "r" ( pul_System_Call_राशिः ) );
            #यदि ( पत्तनम्_USE_PSPLIM_पञ्जिकाकोशः == 1 )
            {
                __asm चञ्चल ( "msr psplim, %0" : : "r" ( pxMpuSettings->x_System_Call_राशिः_Info.pul_System_Call_राशिः_सीमा ) );
            }
            #यदि_अन्तः

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PC ] = uxSystemCallImplementations[ uc_System_Call_सङ्ख्या ];

            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_राशिः_Info.pul_Task_राशिः = pul_Task_राशिः + ul_Hardware_Saved_Exception_Frame_आकार;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            यदि( ( pul_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PSR ] & पत्तनम्_PSR_राशिः_PADDING_आवरणम् ) == पत्तनम्_PSR_राशिः_PADDING_आवरणम् )
            {
                pxMpuSettings->ulTaskFlags |= पत्तनम्_राशिः_FRAME_HAS_PADDING_FLAG;
            }
            अन्यथा
            {
                pxMpuSettings->ulTaskFlags &= ( ~पत्तनम्_राशिः_FRAME_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PSR ] &= ( ~पत्तनम्_PSR_राशिः_PADDING_आवरणम् );

            /* Raise the privilege for the duration of the system call. */
            __asm चञ्चल (
                " mrs r0, control     \n" /* Obtain current control value. */
                " movs r1, #1         \n" /* r1 = 1. */
                " bics r0, r1         \n" /* Clear nPRIV bit. */
                " msr control, r0     \n" /* Write back new control value. */
                ::: "r0", "r1", "memory"
                );
        }
    }

#यदि_अन्तः /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    शून्य vRequestSystemCallExit( शून्य ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm चञ्चल ( "svc %0 \n" ::"i" ( पत्तनम्_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#यदि_अन्तः /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    शून्य vSystemCallExit( uint32_t * pul_System_Call_राशिः,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        बाह्य TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_राशिः;
        uint32_t ul_Hardware_Saved_Exception_Frame_आकार, ulSystemCallLocation, i;

        #यदि defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            बाह्य uint32_t * __privileged_functions_start__;
            बाह्य uint32_t * __privileged_functions_end__;
        #अन्यथा
            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint32_t __privileged_functions_start__[];
            बाह्य uint32_t __privileged_functions_end__[];
        #यदि_अन्तः /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PC ];
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
        यदि( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_राशिः_Info.pul_Task_राशिः != रिक्त ) )
        {
            pul_Task_राशिः = pxMpuSettings->x_System_Call_राशिः_Info.pul_Task_राशिः;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            #यदि ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )
            {
                यदि( ( ulLR & पत्तनम्_EXC_RETURN_राशिः_FRAME_TYPE_आवरणम् ) == 0UL )
                {
                    /* Extended frame i.e. FPU in use. */
                    ul_Hardware_Saved_Exception_Frame_आकार = 26;
                    __asm चञ्चल (
                        " vpush {s0}         \n" /* Trigger lazy stacking. */
                        " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                        ::: "memory"
                        );
                }
                अन्यथा
                {
                    /* Standard frame i.e. FPU not in use. */
                    ul_Hardware_Saved_Exception_Frame_आकार = 8;
                }
            }
            #अन्यथा /* if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */
            {
                ul_Hardware_Saved_Exception_Frame_आकार = 8;
            }
            #यदि_अन्तः /* configENABLE_FPU || configENABLE_MVE */

            /* Make space on the task stack for the stack frame. */
            pul_Task_राशिः = pul_Task_राशिः - ul_Hardware_Saved_Exception_Frame_आकार;

            /* Copy the stack frame. */
            प्रति( i = 0; i < ul_Hardware_Saved_Exception_Frame_आकार; i++ )
            {
                pul_Task_राशिः[ i ] = pul_System_Call_राशिः[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm चञ्चल ( "msr psp, %0" : : "r" ( pul_Task_राशिः ) );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PC ] = pxMpuSettings->x_System_Call_राशिः_Info.ul_Link_पञ्जिकाकोशः_At_System_Call_प्रविष्टिः;
            /* Ensure that LR has a valid value.*/
            pul_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_LR ] = pxMpuSettings->x_System_Call_राशिः_Info.ul_Link_पञ्जिकाकोशः_At_System_Call_प्रविष्टिः;

            /* Restore the PSPLIM register to what it was at the time of
             * system call entry. */
            #यदि ( पत्तनम्_USE_PSPLIM_पञ्जिकाकोशः == 1 )
            {
                __asm चञ्चल ( "msr psplim, %0" : : "r" ( pxMpuSettings->x_System_Call_राशिः_Info.ul_राशिः_सीमा_पञ्जिकाकोशः_At_System_Call_प्रविष्टिः ) );
            }
            #यदि_अन्तः

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            यदि( ( pxMpuSettings->ulTaskFlags & पत्तनम्_राशिः_FRAME_HAS_PADDING_FLAG ) == पत्तनम्_राशिः_FRAME_HAS_PADDING_FLAG )
            {
                pul_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PSR ] |= पत्तनम्_PSR_राशिः_PADDING_आवरणम्;
            }
            अन्यथा
            {
                pul_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PSR ] &= ( ~पत्तनम्_PSR_राशिः_PADDING_आवरणम् );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_राशिः_Info.pul_Task_राशिः = रिक्त;

            /* Drop the privilege before returning to the thread mode. */
            __asm चञ्चल (
                " mrs r0, control     \n" /* Obtain current control value. */
                " movs r1, #1         \n" /* r1 = 1. */
                " orrs r0, r1         \n" /* Set nPRIV bit. */
                " msr control, r0     \n" /* Write back new control value. */
                ::: "r0", "r1", "memory"
                );
        }
    }

#यदि_अन्तः /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#यदि ( configENABLE_MPU == 1 )

    आधारः_Type_t x_पत्तनम्_Is_Task_Privileged( शून्य ) /* PRIVILEGED_FUNCTION */
    {
        आधारः_Type_t xTaskIsPrivileged = pdFALSE;
        ध्रुव xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( रिक्त ); /* Calling task's MPU settings. */

        यदि( ( xTaskMpuSettings->ulTaskFlags & पत्तनम्_TASK_IS_PRIVILEGED_FLAG ) == पत्तनम्_TASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        प्रत्यागम xTaskIsPrivileged;
    }

#यदि_अन्तः /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

#यदि ( configENABLE_MPU == 1 )

    राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                         राशिः_Type_t * px_अन्तः_सम्बन्धि_राशिः,
                                         TaskFunction_t px_संहिता,
                                         शून्य * pvParameters,
                                         आधारः_Type_t x_सततम्_Privileged,
                                         xMPU_SETTINGS * xMPUSettings ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_सूचकांक = 0;
        uint32_t ulControl = 0x0;

        xMPUSettings->ulContext[ ul_सूचकांक ] = 0x04040404; /* r4. */
        ul_सूचकांक++;
        xMPUSettings->ulContext[ ul_सूचकांक ] = 0x05050505; /* r5. */
        ul_सूचकांक++;
        xMPUSettings->ulContext[ ul_सूचकांक ] = 0x06060606; /* r6. */
        ul_सूचकांक++;
        xMPUSettings->ulContext[ ul_सूचकांक ] = 0x07070707; /* r7. */
        ul_सूचकांक++;
        xMPUSettings->ulContext[ ul_सूचकांक ] = 0x08080808; /* r8. */
        ul_सूचकांक++;
        xMPUSettings->ulContext[ ul_सूचकांक ] = 0x09090909; /* r9. */
        ul_सूचकांक++;
        xMPUSettings->ulContext[ ul_सूचकांक ] = 0x10101010; /* r10. */
        ul_सूचकांक++;
        xMPUSettings->ulContext[ ul_सूचकांक ] = 0x11111111; /* r11. */
        ul_सूचकांक++;

        xMPUSettings->ulContext[ ul_सूचकांक ] = ( uint32_t ) pvParameters; /* r0. */
        ul_सूचकांक++;
        xMPUSettings->ulContext[ ul_सूचकांक ] = 0x01010101; /* r1. */
        ul_सूचकांक++;
        xMPUSettings->ulContext[ ul_सूचकांक ] = 0x02020202; /* r2. */
        ul_सूचकांक++;
        xMPUSettings->ulContext[ ul_सूचकांक ] = 0x03030303; /* r3. */
        ul_सूचकांक++;
        xMPUSettings->ulContext[ ul_सूचकांक ] = 0x12121212; /* r12. */
        ul_सूचकांक++;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( uint32_t ) पत्तनम्_TASK_RETURN_स्थानाङ्कः; /* LR. */
        ul_सूचकांक++;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( uint32_t ) px_संहिता; /* PC. */
        ul_सूचकांक++;
        xMPUSettings->ulContext[ ul_सूचकांक ] = पत्तनम्_INITIAL_XPSR; /* xPSR. */
        ul_सूचकांक++;

        #यदि ( configENABLE_TRUSTZONE == 1 )
        {
            xMPUSettings->ulContext[ ul_सूचकांक ] = पत्तनम्_NO_SECURE_CONTEXT; /* xSecureContext. */
            ul_सूचकांक++;
        }
        #यदि_अन्तः /* configENABLE_TRUSTZONE */
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( uint32_t ) ( px_शिखरम्_सम्बन्धि_राशिः - 8 ); /* PSP with the hardware saved stack. */
        ul_सूचकांक++;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( uint32_t ) px_अन्तः_सम्बन्धि_राशिः; /* PSPLIM. */
        ul_सूचकांक++;

        #यदि ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
        {
            /* Check PACBTI security feature configuration before pushing the
             * CONTROL register's value on task's TCB. */
            #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
                ulControl = prvConfigurePACBTI( pdFALSE );
            #अन्यथा /* configNUMBER_OF_CORES > 1 */
                ulControl = vConfigurePACBTI( pdFALSE );
            #यदि_अन्तः /* configNUMBER_OF_CORES */
        }
        #यदि_अन्तः /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

        यदि( x_सततम्_Privileged == pdTRUE )
        {
            xMPUSettings->ulTaskFlags |= पत्तनम्_TASK_IS_PRIVILEGED_FLAG;
            xMPUSettings->ulContext[ ul_सूचकांक ] = ( ulControl | ( uint32_t ) पत्तनम्_INITIAL_CONTROL_PRIVILEGED ); /* CONTROL. */
            ul_सूचकांक++;
        }
        अन्यथा
        {
            xMPUSettings->ulTaskFlags &= ( ~पत्तनम्_TASK_IS_PRIVILEGED_FLAG );
            xMPUSettings->ulContext[ ul_सूचकांक ] = ( ulControl | ( uint32_t ) पत्तनम्_INITIAL_CONTROL_UNPRIVILEGED ); /* CONTROL. */
            ul_सूचकांक++;
        }

        xMPUSettings->ulContext[ ul_सूचकांक ] = पत्तनम्_INITIAL_EXC_RETURN; /* LR (EXC_RETURN). */
        ul_सूचकांक++;

        #यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )
        {
            /* Ensure that the system call stack is double word aligned. */
            xMPUSettings->x_System_Call_राशिः_Info.pul_System_Call_राशिः = &( xMPUSettings->x_System_Call_राशिः_Info.ul_System_Call_राशिः_बफर[ config_SYSTEM_CALL_राशिः_आकार - 1 ] );
            xMPUSettings->x_System_Call_राशिः_Info.pul_System_Call_राशिः = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_राशिः_Info.pul_System_Call_राशिः ) &
                                                                                     ( uint32_t ) ( ~( पत्तनम्_BYTE_ALIGNMENT_आवरणम् ) ) );

            xMPUSettings->x_System_Call_राशिः_Info.pul_System_Call_राशिः_सीमा = &( xMPUSettings->x_System_Call_राशिः_Info.ul_System_Call_राशिः_बफर[ 0 ] );
            xMPUSettings->x_System_Call_राशिः_Info.pul_System_Call_राशिः_सीमा = ( uint32_t * ) ( ( ( uint32_t ) ( xMPUSettings->x_System_Call_राशिः_Info.pul_System_Call_राशिः_सीमा ) +
                                                                                            ( uint32_t ) ( पत्तनम्_BYTE_ALIGNMENT - 1 ) ) &
                                                                                          ( uint32_t ) ( ~( पत्तनम्_BYTE_ALIGNMENT_आवरणम् ) ) );

            /* This is not NULL only for the duration of a system call. */
            xMPUSettings->x_System_Call_राशिः_Info.pul_Task_राशिः = रिक्त;
        }
        #यदि_अन्तः /* configUSE_MPU_WRAPPERS_V1 == 0 */

        #यदि ( configENABLE_PAC == 1 )
        {
            uint32_t ul_Task_Pac_कुञ्चिका[ 4 ], i;

            v_Application_Generate_Task_Random_Pac_कुञ्चिका( &( ul_Task_Pac_कुञ्चिका[ 0 ] ) );

            प्रति( i = 0; i < 4; i++ )
            {
                xMPUSettings->ulContext[ ul_सूचकांक ] = ul_Task_Pac_कुञ्चिका[ i ];
                ul_सूचकांक++;
            }
        }
        #यदि_अन्तः /* configENABLE_PAC */

        प्रत्यागम &( xMPUSettings->ulContext[ ul_सूचकांक ] );
    }

#अन्यथा /* configENABLE_MPU */

    राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                         राशिः_Type_t * px_अन्तः_सम्बन्धि_राशिः,
                                         TaskFunction_t px_संहिता,
                                         शून्य * pvParameters ) /* PRIVILEGED_FUNCTION */
    {
        /* Simulate the stack frame as it would be created by a context switch
         * interrupt. */
        #यदि ( पत्तनम्_PRELOAD_REGISTERS == 0 )
        {
            px_शिखरम्_सम्बन्धि_राशिः--; /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_XPSR; /* xPSR. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) px_संहिता; /* PC. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_TASK_RETURN_स्थानाङ्कः; /* LR. */
            px_शिखरम्_सम्बन्धि_राशिः -= 5; /* R12, R3, R2 and R1. */
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) pvParameters; /* R0. */
            px_शिखरम्_सम्बन्धि_राशिः -= 9; /* R11..R4, EXC_RETURN. */
            *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_EXC_RETURN;
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) px_अन्तः_सम्बन्धि_राशिः; /* Slot used to hold this task's PSPLIM value. */

            #यदि ( configENABLE_TRUSTZONE == 1 )
            {
                px_शिखरम्_सम्बन्धि_राशिः--;
                *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_NO_SECURE_CONTEXT; /* Slot used to hold this task's xSecureContext value. */
            }
            #यदि_अन्तः /* configENABLE_TRUSTZONE */
        }
        #अन्यथा /* portPRELOAD_REGISTERS */
        {
            px_शिखरम्_सम्बन्धि_राशिः--; /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_XPSR; /* xPSR. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) px_संहिता; /* PC. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_TASK_RETURN_स्थानाङ्कः; /* LR. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x12121212UL; /* R12. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x03030303UL; /* R3. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x02020202UL; /* R2. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x01010101UL; /* R1. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) pvParameters; /* R0. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x11111111UL; /* R11. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x10101010UL; /* R10. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x09090909UL; /* R09. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x08080808UL; /* R08. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x07070707UL; /* R07. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x06060606UL; /* R06. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x05050505UL; /* R05. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x04040404UL; /* R04. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_EXC_RETURN; /* EXC_RETURN. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) px_अन्तः_सम्बन्धि_राशिः; /* Slot used to hold this task's PSPLIM value. */

            #यदि ( configENABLE_TRUSTZONE == 1 )
            {
                px_शिखरम्_सम्बन्धि_राशिः--;
                *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_NO_SECURE_CONTEXT; /* Slot used to hold this task's xSecureContext value. */
            }
            #यदि_अन्तः /* configENABLE_TRUSTZONE */
        }
        #यदि_अन्तः /* portPRELOAD_REGISTERS */

        #यदि ( configENABLE_PAC == 1 )
        {
            uint32_t ul_Task_Pac_कुञ्चिका[ 4 ], i;

            v_Application_Generate_Task_Random_Pac_कुञ्चिका( &( ul_Task_Pac_कुञ्चिका[ 0 ] ) );

            प्रति( i = 0; i < 4; i++ )
            {
                px_शिखरम्_सम्बन्धि_राशिः--;
                *px_शिखरम्_सम्बन्धि_राशिः = ul_Task_Pac_कुञ्चिका[ i ];
            }
        }
        #यदि_अन्तः /* configENABLE_PAC */

        प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
    }

#यदि_अन्तः /* configENABLE_MPU */
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य ) /* PRIVILEGED_FUNCTION */
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
    #यदि ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        ध्रुव पत्तनम्_ISR_t * ध्रुव px_सदिशम्_सारणी = पत्तनम्_SCB_VTOR_REG;

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
        configASSERT( px_सदिशम्_सारणी[ पत्तनम्_सदिशम्_सूचकांक_SVC ] == SVC_Handler );
        configASSERT( px_सदिशम्_सारणी[ पत्तनम्_सदिशम्_सूचकांक_PENDSV ] == PendSV_Handler );
    }
    #यदि_अन्तः /* configCHECK_HANDLER_INSTALLATION */

    v_पत्तनम्_Configure_व्यवधानम्_Priorities();

    #यदि ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
    {
        /* Set the CONTROL register value based on PACBTI security feature
         * configuration before starting the first task. */
        #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
            ( शून्य ) prvConfigurePACBTI( pdTRUE );
        #अन्यथा /* configNUMBER_OF_CORES > 1 */
            ( शून्य ) vConfigurePACBTI( pdTRUE );
        #यदि_अन्तः /* configNUMBER_OF_CORES */
    }
    #यदि_अन्तः /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

    #यदि ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        prv_सज्जता_MPU();
    }
    #यदि_अन्तः /* configENABLE_MPU */

    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )
        /* Start the timer that generates the tick ISR. Interrupts are disabled
         * here already. */
        v_पत्तनम्_सज्जता_Timer_व्यवधानम्();
        /* Initialize the critical nesting count for all cores. */
        प्रति ( uint8_t ucCoreID = 0; ucCoreID < config_सङ्ख्या_सम्बन्धि_CORES; ucCoreID++ )
        {
            ulCriticalNestings[ ucCoreID ] = 0;
        }
        /* Signal that primary core has done all the necessary initialisations. */
        uc_Primary_Core_Init_समाप्तम्_Flag = 1;
        /* Wake up secondary cores */
        आधारः_Type_t x_Wake_परिणाम = configWAKE_SECONDARY_CORES();
        configASSERT( x_Wake_परिणाम == pdTRUE );

        /* Hold the primary core here until all the secondary cores are ready, this would be achieved only when
         * all elements of ucSecondaryCoresReadyFlags are set.
         */
        यावत्( 1 )
        {
            आधारः_Type_t xAllCoresReady = pdTRUE;
            प्रति( uint8_t ucCoreID = 0; ucCoreID < ( config_सङ्ख्या_सम्बन्धि_CORES - 1 ); ucCoreID++ )
            {
                यदि( ucSecondaryCoresReadyFlags[ ucCoreID ] != pdTRUE )
                {
                    xAllCoresReady = pdFALSE;
                    भङ्ग;
                }
                }

            यदि ( xAllCoresReady == pdTRUE )
            {
                भङ्ग;
            }
        }
    #अन्यथा /* if ( configNUMBER_OF_CORES > 1 ) */
        /* Start the timer that generates the tick ISR. */
        v_पत्तनम्_सज्जता_Timer_व्यवधानम्();
        /* Initialize the critical nesting count ready for the first task. */
        ulCriticalNesting = 0;
    #यदि_अन्तः /* if ( configNUMBER_OF_CORES > 1 ) */

    #यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )
    {
        xSchedulerRunning = pdTRUE;
    }
    #यदि_अन्तः /* ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

    /* Start the first task. */
    vStartFirstTask();

    /* Should never get here as the tasks will now be executing. Call the task
     * exit error function to prevent compiler warnings about a static function
     * not being called in the case that the application writer overrides this
     * functionality by defining configTASK_RETURN_ADDRESS. Call
     * vTaskSwitchContext() so link time optimization does not remove the
     * symbol. */
    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )
        vTaskSwitchContext( पत्तनम्_GET_CORE_ID() );
    #अन्यथा
        vTaskSwitchContext();
    #यदि_अन्तः
    prvTaskExitError();

    /* Should not get here. */
    प्रत्यागम 0;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य ) /* PRIVILEGED_FUNCTION */
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
        configASSERT( ulCriticalNesting == 1000UL );
    #अन्यथा /* if ( configNUMBER_OF_CORES == 1 ) */
        configASSERT( ulCriticalNestings[ पत्तनम्_GET_CORE_ID() ] == 1000UL );
    #यदि_अन्तः /* if ( configNUMBER_OF_CORES == 1 ) */
}
/*-----------------------------------------------------------*/

#यदि ( configENABLE_MPU == 1 )

    शून्य v_पत्तनम्_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ध्रुव संरचना x_स्मृतिः_REGION * ध्रुव xRegions,
                                    राशिः_Type_t * px_Bottom_सम्बन्धि_राशिः,
                                    config_राशिः_गभीरता_TYPE ux_राशिः_गभीरता )
    {
        uint32_t ul_Region_Start_स्थानाङ्कः, ul_Region_अन्तः_स्थानाङ्कः, ul_Region_सङ्ख्या;
        int32_t l_सूचकांक = 0;

        #यदि defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            बाह्य uint32_t * __privileged_sram_start__;
            बाह्य uint32_t * __privileged_sram_end__;
        #अन्यथा
            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint32_t __privileged_sram_start__[];
            बाह्य uint32_t __privileged_sram_end__[];
        #यदि_अन्तः /* defined( __ARMCC_VERSION ) */

        /* Setup MAIR0. */
        xMPUSettings->ulMAIR0 = ( ( पत्तनम्_MPU_प्रसामान्यम्_स्मृतिः_BUFFERABLE_CACHEABLE << पत्तनम्_MPU_MAIR_ATTR0_POS ) & पत्तनम्_MPU_MAIR_ATTR0_आवरणम् );
        xMPUSettings->ulMAIR0 |= ( ( पत्तनम्_MPU_DEVICE_स्मृतिः_n_Gn_RE << पत्तनम्_MPU_MAIR_ATTR1_POS ) & पत्तनम्_MPU_MAIR_ATTR1_आवरणम् );

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid.  At all other
         * times the stack parameters will not be valid and it is assumed that
         * the stack region has already been configured. */
        यदि( ux_राशिः_गभीरता > 0 )
        {
            ul_Region_Start_स्थानाङ्कः = ( uint32_t ) px_Bottom_सम्बन्धि_राशिः;
            ul_Region_अन्तः_स्थानाङ्कः = ( uint32_t ) px_Bottom_सम्बन्धि_राशिः + ( ux_राशिः_गभीरता * ( config_राशिः_गभीरता_TYPE ) परिमाण( राशिः_Type_t ) ) - 1;

            /* If the stack is within the privileged SRAM, do not protect it
             * using a separate MPU region. This is needed because privileged
             * SRAM is already protected using an MPU region and ARMv8-M does
             * not allow overlapping MPU regions. */
            यदि( ( ul_Region_Start_स्थानाङ्कः >= ( uint32_t ) __privileged_sram_start__ ) &&
                ( ul_Region_अन्तः_स्थानाङ्कः <= ( uint32_t ) __privileged_sram_end__ ) )
            {
                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR = 0;
                xMPUSettings->xRegionsSettings[ 0 ].ulRLAR = 0;
            }
            अन्यथा
            {
                /* Define the region that allows access to the stack. */
                ul_Region_Start_स्थानाङ्कः &= पत्तनम्_MPU_RBAR_स्थानाङ्कः_आवरणम्;
                ul_Region_अन्तः_स्थानाङ्कः &= पत्तनम्_MPU_RLAR_स्थानाङ्कः_आवरणम्;

                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR = ( ul_Region_Start_स्थानाङ्कः ) |
                                                             ( पत्तनम्_MPU_REGION_NON_SHAREABLE ) |
                                                             ( पत्तनम्_MPU_REGION_READ_WRITE ) |
                                                             ( पत्तनम्_MPU_REGION_EXECUTE_NEVER );

                xMPUSettings->xRegionsSettings[ 0 ].ulRLAR = ( ul_Region_अन्तः_स्थानाङ्कः ) |
                                                             ( पत्तनम्_MPU_RLAR_ATTR_INDEX0 ) |
                                                             ( पत्तनम्_MPU_RLAR_REGION_ENABLE );
            }
        }

        /* User supplied configurable regions. */
        प्रति( ul_Region_सङ्ख्या = 1; ul_Region_सङ्ख्या <= पत्तनम्_अङ्कः_CONFIGURABLE_REGIONS; ul_Region_सङ्ख्या++ )
        {
            /* If xRegions is NULL i.e. the task has not specified any MPU
             * region, the else part ensures that all the configurable MPU
             * regions are invalidated. */
            यदि( ( xRegions != रिक्त ) && ( xRegions[ l_सूचकांक ].ul_दीर्घता_अन्तर्_अष्टकानि > 0UL ) )
            {
                /* Translate the generic region definition contained in xRegions
                 * into the ARMv8 specific MPU settings that are then stored in
                 * xMPUSettings. */
                ul_Region_Start_स्थानाङ्कः = ( ( uint32_t ) xRegions[ l_सूचकांक ].pv_आधारः_स्थानाङ्कः ) & पत्तनम्_MPU_RBAR_स्थानाङ्कः_आवरणम्;
                ul_Region_अन्तः_स्थानाङ्कः = ( uint32_t ) xRegions[ l_सूचकांक ].pv_आधारः_स्थानाङ्कः + xRegions[ l_सूचकांक ].ul_दीर्घता_अन्तर्_अष्टकानि - 1;
                ul_Region_अन्तः_स्थानाङ्कः &= पत्तनम्_MPU_RLAR_स्थानाङ्कः_आवरणम्;

                /* Start address. */
                xMPUSettings->xRegionsSettings[ ul_Region_सङ्ख्या ].ulRBAR = ( ul_Region_Start_स्थानाङ्कः ) |
                                                                          ( पत्तनम्_MPU_REGION_NON_SHAREABLE );

                /* RO/RW. */
                यदि( ( xRegions[ l_सूचकांक ].ulParameters & tskMPU_REGION_READ_ONLY ) != 0 )
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_सङ्ख्या ].ulRBAR |= ( पत्तनम्_MPU_REGION_READ_ONLY );
                }
                अन्यथा
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_सङ्ख्या ].ulRBAR |= ( पत्तनम्_MPU_REGION_READ_WRITE );
                }

                /* XN. */
                यदि( ( xRegions[ l_सूचकांक ].ulParameters & tskMPU_REGION_EXECUTE_NEVER ) != 0 )
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_सङ्ख्या ].ulRBAR |= ( पत्तनम्_MPU_REGION_EXECUTE_NEVER );
                }

                /* End Address. */
                xMPUSettings->xRegionsSettings[ ul_Region_सङ्ख्या ].ulRLAR = ( ul_Region_अन्तः_स्थानाङ्कः ) |
                                                                          ( पत्तनम्_MPU_RLAR_REGION_ENABLE );

                /* PXN. */
                #यदि ( पत्तनम्_ARMV8_M_MINOR_संस्करणम् >= 1 )
                {
                    यदि( ( xRegions[ l_सूचकांक ].ulParameters & tskMPU_REGION_PRIVILEGED_EXECUTE_NEVER ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ ul_Region_सङ्ख्या ].ulRLAR |= ( पत्तनम्_MPU_RLAR_PRIVILEGED_EXECUTE_NEVER );
                    }
                }
                #यदि_अन्तः /* portARMV8M_MINOR_VERSION >= 1 */

                /* Normal memory/ Device memory. */
                यदि( ( xRegions[ l_सूचकांक ].ulParameters & tsk_MPU_REGION_DEVICE_स्मृतिः ) != 0 )
                {
                    /* Attr1 in MAIR0 is configured as device memory. */
                    xMPUSettings->xRegionsSettings[ ul_Region_सङ्ख्या ].ulRLAR |= पत्तनम्_MPU_RLAR_ATTR_INDEX1;
                }
                अन्यथा
                {
                    /* Attr0 in MAIR0 is configured as normal memory. */
                    xMPUSettings->xRegionsSettings[ ul_Region_सङ्ख्या ].ulRLAR |= पत्तनम्_MPU_RLAR_ATTR_INDEX0;
                }
            }
            अन्यथा
            {
                /* Invalidate the region. */
                xMPUSettings->xRegionsSettings[ ul_Region_सङ्ख्या ].ulRBAR = 0UL;
                xMPUSettings->xRegionsSettings[ ul_Region_सङ्ख्या ].ulRLAR = 0UL;
            }

            l_सूचकांक++;
        }
    }

#यदि_अन्तः /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    आधारः_Type_t x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( ध्रुव शून्य * pv_बफर,
                                                size_t x_बफर_दीर्घता,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_बफर_Start_स्थानाङ्कः, ul_बफर_अन्तः_स्थानाङ्कः;
        आधारः_Type_t xAccessGranted = pdFALSE;
        ध्रुव xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( रिक्त ); /* Calling task's MPU settings. */

        यदि( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        अन्यथा यदि( ( xTaskMpuSettings->ulTaskFlags & पत्तनम्_TASK_IS_PRIVILEGED_FLAG ) == पत्तनम्_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        अन्यथा
        {
            यदि( पत्तनम्_सङ्कलय_UINT32_WILL_अतिप्रवाहः( ( ( uint32_t ) pv_बफर ), ( ( uint32_t ) x_बफर_दीर्घता - 1UL ) ) == pdFALSE )
            {
                ul_बफर_Start_स्थानाङ्कः = ( uint32_t ) pv_बफर;
                ul_बफर_अन्तः_स्थानाङ्कः = ( ( ( uint32_t ) pv_बफर ) + ( uint32_t ) x_बफर_दीर्घता - 1UL );

                प्रति( i = 0; i < पत्तनम्_योग_अङ्कः_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    यदि( ( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR & पत्तनम्_MPU_RLAR_REGION_ENABLE ) == पत्तनम्_MPU_RLAR_REGION_ENABLE )
                    {
                        यदि( पत्तनम्_IS_स्थानाङ्कः_WITHIN_RANGE( ul_बफर_Start_स्थानाङ्कः,
                                                         पत्तनम्_EXTRACT_FIRST_स्थानाङ्कः_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ),
                                                         पत्तनम्_EXTRACT_चरमः_स्थानाङ्कः_FROM_RLAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR ) ) &&
                            पत्तनम्_IS_स्थानाङ्कः_WITHIN_RANGE( ul_बफर_अन्तः_स्थानाङ्कः,
                                                         पत्तनम्_EXTRACT_FIRST_स्थानाङ्कः_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ),
                                                         पत्तनम्_EXTRACT_चरमः_स्थानाङ्कः_FROM_RLAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR ) ) &&
                            पत्तनम्_IS_AUTHORIZED( ulAccessRequested,
                                               prvGetRegionAccessPermissions( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ) ) )
                        {
                            xAccessGranted = pdTRUE;
                            भङ्ग;
                        }
                    }
                }
            }
        }

        प्रत्यागम xAccessGranted;
    }

#यदि_अन्तः /* #if ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Is_Inside_व्यवधानम्( शून्य )
{
    uint32_t ul_Current_व्यवधानम्;
    आधारः_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. Interrupt Program
     * Status Register (IPSR) holds the exception number of the currently-executing
     * exception or zero for Thread mode.*/
    __asm चञ्चल ( "mrs %0, ipsr" : "=r" ( ul_Current_व्यवधानम् )::"memory" );

    यदि( ul_Current_व्यवधानम् == 0 )
    {
        xReturn = pdFALSE;
    }
    अन्यथा
    {
        xReturn = pdTRUE;
    }

    प्रत्यागम xReturn;
}
/*-----------------------------------------------------------*/

#यदि ( ( configASSERT_DEFINED == 1 ) && ( पत्तनम्_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) )

    शून्य v_पत्तनम्_Validate_व्यवधानम्_प्राथमिकता( शून्य )
    {
        uint32_t ul_Current_व्यवधानम्;
        uint8_t uc_Current_प्राथमिकता;

        /* Obtain the number of the currently executing interrupt. */
        __asm चञ्चल ( "mrs %0, ipsr" : "=r" ( ul_Current_व्यवधानम् )::"memory" );

        /* Is the interrupt number a user defined interrupt? */
        यदि( ul_Current_व्यवधानम् >= पत्तनम्_FIRST_USER_व्यवधानम्_सङ्ख्या )
        {
            /* Look up the interrupt's priority. */
            uc_Current_प्राथमिकता = pc_व्यवधानम्_प्राथमिकता_Registers[ ul_Current_व्यवधानम् ];

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
            configASSERT( uc_Current_प्राथमिकता >= uc_Max_Sys_Call_प्राथमिकता );
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
        configASSERT( ( पत्तनम्_AIRCR_REG & पत्तनम्_प्राथमिकता_गणः_आवरणम् ) <= ulMaxPRIGROUPValue );
    }

#यदि_अन्तः /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Configure_व्यवधानम्_Priorities( शून्य ) /* PRIVILEGED_FUNCTION */
{
    #यदि ( ( configASSERT_DEFINED == 1 ) && ( पत्तनम्_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) )
    {
        चञ्चल uint32_t ul_Implemented_Prio_द्वयङ्काः = 0;
        चञ्चल uint8_t uc_Max_प्राथमिकता_मानम्;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
        * functions can be called. ISR safe functions are those that end in
        * "FromISR". FreeRTOS maintains separate thread and ISR API functions to
        * ensure interrupt entry is as fast and simple as possible.
        *
        * First, determine the number of priority bits available. Write to all
        * possible bits in the priority setting for SVCall. */
        पत्तनम्_NVIC_SHPR2_REG = 0xFF000000;

        /* Read the value back to see how many bits stuck. */
        uc_Max_प्राथमिकता_मानम् = ( uint8_t ) ( ( पत्तनम्_NVIC_SHPR2_REG & 0xFF000000 ) >> 24 );

        /* Use the same mask on the maximum system call priority. */
        uc_Max_Sys_Call_प्राथमिकता = config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता & uc_Max_प्राथमिकता_मानम्;

        /* Check that the maximum system call priority is nonzero after
        * accounting for the number of priority bits supported by the
        * hardware. A priority of 0 is invalid because setting the BASEPRI
        * register to 0 unmasks all interrupts, and interrupts with priority 0
        * cannot be masked using BASEPRI.
        * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( uc_Max_Sys_Call_प्राथमिकता );

        /* Check that the bits not implemented in hardware are zero in
        * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता & ( uint8_t ) ( ~( uint32_t ) uc_Max_प्राथमिकता_मानम् ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
        * of bits read back. */
        यावत्( ( uc_Max_प्राथमिकता_मानम् & पत्तनम्_शिखरम्_BIT_सम्बन्धि_BYTE ) == पत्तनम्_शिखरम्_BIT_सम्बन्धि_BYTE )
        {
            ul_Implemented_Prio_द्वयङ्काः++;
            uc_Max_प्राथमिकता_मानम् <<= ( uint8_t ) 0x01;
        }

        यदि( ul_Implemented_Prio_द्वयङ्काः == 8 )
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
            configASSERT( ( config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        अन्यथा
        {
            ulMaxPRIGROUPValue = पत्तनम्_MAX_PRIGROUP_द्वयङ्काः - ul_Implemented_Prio_द्वयङ्काः;
        }

        /* Shift the priority group value back to its position within the AIRCR
        * register. */
        ulMaxPRIGROUPValue <<= पत्तनम्_PRIGROUP_सरणम्;
        ulMaxPRIGROUPValue &= पत्तनम्_प्राथमिकता_गणः_आवरणम्;
    }
    #यदि_अन्तः /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */

    /* Make PendSV and SysTick the lowest priority interrupts, and make SVCall
    * the highest priority. */
    पत्तनम्_NVIC_SHPR3_REG |= पत्तनम्_NVIC_PENDSV_PRI;
    पत्तनम्_NVIC_SHPR3_REG |= पत्तनम्_NVIC_SYSTICK_PRI;
    पत्तनम्_NVIC_SHPR2_REG = 0;
}
/*-----------------------------------------------------------*/

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    शून्य v_पत्तनम्_Grant_Access_गन्तव्यम्_Kernel_Object( TaskHandle_t x_आन्तरिकम्_Task_Handle,
                                         int32_t l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_प्रविष्टिः_सूचकांक, ul_Access_Control_List_प्रविष्टिः_Bit;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_प्रविष्टिः_सूचकांक = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object / पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );
        ul_Access_Control_List_प्रविष्टिः_Bit = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object % पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );

        xTaskMpuSettings = xTaskGetMPUSettings( x_आन्तरिकम्_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_प्रविष्टिः_सूचकांक ] |= ( 1U << ul_Access_Control_List_प्रविष्टिः_Bit );
    }

#यदि_अन्तः /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    शून्य v_पत्तनम्_Revoke_Access_गन्तव्यम्_Kernel_Object( TaskHandle_t x_आन्तरिकम्_Task_Handle,
                                          int32_t l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_प्रविष्टिः_सूचकांक, ul_Access_Control_List_प्रविष्टिः_Bit;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_प्रविष्टिः_सूचकांक = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object / पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );
        ul_Access_Control_List_प्रविष्टिः_Bit = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object % पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );

        xTaskMpuSettings = xTaskGetMPUSettings( x_आन्तरिकम्_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_प्रविष्टिः_सूचकांक ] &= ~( 1U << ul_Access_Control_List_प्रविष्टिः_Bit );
    }

#यदि_अन्तः /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #यदि ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        आधारः_Type_t x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( int32_t l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_प्रविष्टिः_सूचकांक, ul_Access_Control_List_प्रविष्टिः_Bit;
            आधारः_Type_t xAccessGranted = pdFALSE;
            ध्रुव xMPU_SETTINGS * xTaskMpuSettings;

            यदि( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            अन्यथा
            {
                xTaskMpuSettings = xTaskGetMPUSettings( रिक्त ); /* Calling task's MPU settings. */

                ul_Access_Control_List_प्रविष्टिः_सूचकांक = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object / पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );
                ul_Access_Control_List_प्रविष्टिः_Bit = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object % पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );

                यदि( ( xTaskMpuSettings->ulTaskFlags & पत्तनम्_TASK_IS_PRIVILEGED_FLAG ) == पत्तनम्_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                अन्यथा
                {
                    यदि( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_प्रविष्टिः_सूचकांक ] & ( 1U << ul_Access_Control_List_प्रविष्टिः_Bit ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            प्रत्यागम xAccessGranted;
        }

    #अन्यथा /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        आधारः_Type_t x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( int32_t l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( शून्य ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            प्रत्यागम pdTRUE;
        }

    #यदि_अन्तः /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#यदि_अन्तः /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */
/*-----------------------------------------------------------*/

#यदि ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
        स्थिर uint32_t prvConfigurePACBTI( आधारः_Type_t x_Write_Control_पञ्जिकाकोशः )
    #अन्यथा /* configNUMBER_OF_CORES > 1 */
        uint32_t vConfigurePACBTI( आधारः_Type_t x_Write_Control_पञ्जिकाकोशः )
    #यदि_अन्तः /* configNUMBER_OF_CORES */
        {
            uint32_t ulControl = 0x0;

            /* Ensure that PACBTI is implemented. */
            configASSERT( पत्तनम्_ID_ISAR5_REG != 0x0 );

            /* Enable UsageFault exception. */
            पत्तनम्_SCB_SYS_HANDLER_CTRL_STATE_REG |= पत्तनम्_SCB_USG_FAULT_ENABLE_BIT;

            #यदि ( configENABLE_PAC == 1 )
            {
                ulControl |= ( पत्तनम्_CONTROL_UPAC_EN | पत्तनम्_CONTROL_PAC_EN );
            }
            #यदि_अन्तः

            #यदि ( configENABLE_BTI == 1 )
            {
                ulControl |= ( पत्तनम्_CONTROL_UBTI_EN | पत्तनम्_CONTROL_BTI_EN );
            }
            #यदि_अन्तः

            यदि( x_Write_Control_पञ्जिकाकोशः == pdTRUE )
            {
                __asm चञ्चल ( "msr control, %0" : : "r" ( ulControl ) );
            }

            प्रत्यागम ulControl;
        }

#यदि_अन्तः /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */
/*-----------------------------------------------------------*/

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )

    /* Which core owns the lock? */
    PRIVILEGED_दत्त चञ्चल uint32_t ulOwnedByCore[ पत्तनम्_MAX_CORE_गणनम् ];
    /* Lock count a core owns. */
    PRIVILEGED_दत्त चञ्चल uint32_t ul_Recursion_गणनम्_By_तालकम्[ e_तालकम्_गणनम् ];
    /* Index 0 is used for ISR lock and Index 1 is used for task lock. */
    PRIVILEGED_दत्त चञ्चल uint32_t ulGateWord[ e_तालकम्_गणनम् ];

    __attribute__((weak)) शून्य v_व्यवधानम्_Core( uint8_t ucCoreID )
    {
        /* Default weak stub - platform specific implementation may override. */
        ( शून्य ) ucCoreID;
    }

/*-----------------------------------------------------------*/

    स्थिर अन्तःस्थ शून्य prvSpinUnlock( चञ्चल uint32_t * ul_तालकम् )
    {
        /* Conservative unlock: preserve original barriers for broad HW/FVP. */
        __asm चञ्चल (
            "dmb sy         \n"
            "mov r1, #0     \n"
            "str r1, [%0]   \n"
            "sev            \n"
            "dsb            \n"
            "isb            \n"
            :
            : "r" ( ul_तालकम् )
            : "memory", "r1"
        );
    }

/*-----------------------------------------------------------*/

    स्थिर अन्तःस्थ uint32_t prvSpinTrylock( चञ्चल uint32_t * ul_तालकम् )
    {
        /*
         * Conservative ldrex/strex trylock:
         * - Return 1 immediately if busy, clearing exclusive state (CLREX).
         * - Retry strex only on spurious failure when observed free.
         * - DMB on success to preserve expected acquire semantics.
         */
        uint32_t ulVal;
        uint32_t ul_स्थितिः;

        __asm चञ्चल (
            " ldrex %0, [%1]   \n"
            : "=r" ( ulVal )
            : "r" ( ul_तालकम् )
            : "memory"
        );

        यदि( ulVal != 0U )
        {
            __asm चञ्चल ("clrex" ::: "memory");
            प्रत्यागम 1U;
        }

        __asm चञ्चल (
            " strex %0, %2, [%1]   \n"
            : "=&r" ( ul_स्थितिः )
            : "r" ( ul_तालकम् ), "r" (1U)
            : "memory"
        );

        यदि( ul_स्थितिः != 0U )
        {
            प्रत्यागम 1U;
        }
        __asm चञ्चल ( "dmb" ::: "memory" );
        प्रत्यागम 0U;
    }


/*-----------------------------------------------------------*/

    /* Read 32b value shared between cores. */
    स्थिर अन्तःस्थ uint32_t prvGet32( चञ्चल uint32_t * x )
    {
        __asm( "dsb" );
        प्रत्यागम *x;
    }

/*-----------------------------------------------------------*/

    /* Write 32b value shared between cores. */
    स्थिर अन्तःस्थ शून्य prvSet32( चञ्चल uint32_t * x,
                                 uint32_t मानम् )
    {
        *x = मानम्;
        __asm( "dsb" );
    }

/*-----------------------------------------------------------*/

    शून्य v_पत्तनम्_Recursive_तालकम्( uint8_t ucCoreID,
                             e_पत्तनम्_RTOSLock e_तालकम्_अङ्कः,
                             आधारः_Type_t uxAcquire )
    {
        /* Validate the core ID and lock number. */
        configASSERT( ucCoreID < पत्तनम्_MAX_CORE_गणनम् );
        configASSERT( e_तालकम्_अङ्कः < e_तालकम्_गणनम् );

        uint32_t ul_तालकम्_Bit = 1u << e_तालकम्_अङ्कः;

        /* Lock acquire */
        यदि( uxAcquire )
        {
            /* Check if spinlock is available. */
            /* If spinlock is not available check if the core owns the lock. */
            /* If the core owns the lock wait increment the lock count by the core. */
            /* If core does not own the lock wait for the spinlock. */
            यदि( prvSpinTrylock( &ulGateWord[ e_तालकम्_अङ्कः ] ) != 0 )
            {
                /* Check if the core owns the spinlock. */
                यदि( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ul_तालकम्_Bit )
                {
                    configASSERT( prvGet32( &ul_Recursion_गणनम्_By_तालकम्[ e_तालकम्_अङ्कः ] ) != पत्तनम्_UINT32_MAX );
                    prvSet32( &ul_Recursion_गणनम्_By_तालकम्[ e_तालकम्_अङ्कः ], ( prvGet32( &ul_Recursion_गणनम्_By_तालकम्[ e_तालकम्_अङ्कः ] ) + 1 ) );
                    प्रत्यागम;
                }

                /* Preload the gate word into the cache. */
                uint32_t dummy = ulGateWord[ e_तालकम्_अङ्कः ];
                dummy++;

                यावत्( prvSpinTrylock( &ulGateWord[ e_तालकम्_अङ्कः ] ) != 0 )
                {
                    __asm चञ्चल ( "wfe" );
                }
            }

            /* Add barrier to ensure lock is taken before we proceed. */
            __asm चञ्चल( "dmb sy" ::: "memory" );

            /* Assert the lock count is 0 when the spinlock is free and is acquired. */
            configASSERT( prvGet32( &ul_Recursion_गणनम्_By_तालकम्[ e_तालकम्_अङ्कः ] ) == 0 );

            /* Set lock count as 1. */
            prvSet32( &ul_Recursion_गणनम्_By_तालकम्[ e_तालकम्_अङ्कः ], 1 );
            /* Set ulOwnedByCore. */
            prvSet32( &ulOwnedByCore[ ucCoreID ], ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) | ul_तालकम्_Bit ) );
        }
        /* Lock release. */
        अन्यथा
        {
            /* Assert the lock is not free already. */
            configASSERT( ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ul_तालकम्_Bit ) != 0 );
            configASSERT( prvGet32( &ul_Recursion_गणनम्_By_तालकम्[ e_तालकम्_अङ्कः ] ) != 0 );

            /* Reduce ulRecursionCountByLock by 1. */
            prvSet32( &ul_Recursion_गणनम्_By_तालकम्[ e_तालकम्_अङ्कः ], ( prvGet32( &ul_Recursion_गणनम्_By_तालकम्[ e_तालकम्_अङ्कः ] ) - 1 ) );

            यदि( !prvGet32( &ul_Recursion_गणनम्_By_तालकम्[ e_तालकम्_अङ्कः ] ) )
            {
                prvSet32( &ulOwnedByCore[ ucCoreID ], ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ~ul_तालकम्_Bit ) );
                prvSpinUnlock( &ulGateWord[ e_तालकम्_अङ्कः ] );
                /* Add barrier to ensure lock status is reflected before we proceed. */
                __asm चञ्चल( "dmb sy" ::: "memory" );
            }
        }
    }

/*-----------------------------------------------------------*/

    uint8_t uc_पत्तनम्_Get_Core_ID( शून्य )
    {
        प्रत्यागम *(चञ्चल uint8_t *)(config_CORE_ID_पञ्जिकाकोशः);
    }

/*-----------------------------------------------------------*/

#यदि_अन्तः /* if( configNUMBER_OF_CORES > 1 ) */
