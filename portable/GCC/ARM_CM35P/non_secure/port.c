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
#నిర్వచించు MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* MPU includes. */
#అన్తర్భావ "mpu_wrappers.h"
#అన్తర్భావ "mpu_syscall_numbers.h"

/* Portasm includes. */
#అన్తర్భావ "portasm.h"

#ఒకవేళ ( configENABLE_TRUSTZONE == 1 )
    /* Secure components includes. */
    #అన్తర్భావ "secure_context.h"
    #అన్తర్భావ "secure_init.h"
#అయితే_ముగింపు /* configENABLE_TRUSTZONE */

#నిర్వచనం_రద్దు MPU_WRAPPERS_INCLUDED_FROM_API_FILE

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
#ఒకవేళ ( ( config_నిరంతరం_FREERTOS_SECURE_ONLY == 1 ) && ( configENABLE_TRUSTZONE == 1 ) )
    #దోషం TrustZone needs గమ్యం be disabled లోపల క్రమం గమ్యం నిరంతరం FreeRTOS on the Secure Side.
#అయితే_ముగింపు

/**
 * Cortex-M23 does not have non-secure PSPLIM. We should use PSPLIM on Cortex-M23
 * only when FreeRTOS runs on secure side.
 */
#ఒకవేళ ( ( పోర్టు_HAS_ARMV8_M_MAIN_EXTENSION == 0 ) && ( config_నిరంతరం_FREERTOS_SECURE_ONLY == 0 ) )
    #నిర్వచించు పోర్టు_USE_PSPLIM_రిజిస్టరు    0
#లేకపోతే
    #నిర్వచించు పోర్టు_USE_PSPLIM_రిజిస్టరు    1
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

/**
 * @brief Prototype of all Interrupt Service Routines (ISRs).
 */
రకనిర్వచనం శూన్య ( * పోర్టు_ISR_t )( శూన్య );
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the NVIC.
 */
#నిర్వచించు పోర్టు_NVIC_SYSTICK_CTRL_REG             ( *( ( అస్థిర uint32_t * ) 0xe000e010 ) )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG             ( *( ( అస్థిర uint32_t * ) 0xe000e014 ) )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG    ( *( ( అస్థిర uint32_t * ) 0xe000e018 ) )
#నిర్వచించు పోర్టు_NVIC_SHPR3_REG                    ( *( ( అస్థిర uint32_t * ) 0xe000ed20 ) )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_ENABLE_బిట్టు           ( 1UL << 0UL )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_INT_బిట్టు              ( 1UL << 1UL )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_CLK_బిట్టు              ( 1UL << 2UL )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_లెక్క_FLAG_బిట్టు       ( 1UL << 16UL )
#నిర్వచించు పోర్టు_NVIC_PEND_SYSTICK_CLEAR_బిట్టు       ( 1UL << 25UL )
#నిర్వచించు పోర్టు_NVIC_PEND_SYSTICK_సమితి_బిట్టు         ( 1UL << 26UL )
#నిర్వచించు పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత            ( 255UL )
#నిర్వచించు పోర్టు_NVIC_PENDSV_PRI                   ( పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత << 16UL )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_PRI                  ( పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత << 24UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the SCB.
 */
#నిర్వచించు పోర్టు_SCB_VTOR_REG                      ( *( ( పోర్టు_ISR_t ** ) 0xe000ed08 ) )
#నిర్వచించు పోర్టు_SCB_SYS_HANDLER_CTRL_STATE_REG    ( *( ( అస్థిర uint32_t * ) 0xe000ed24 ) )
#నిర్వచించు పోర్టు_SCB_MEM_FAULT_ENABLE_బిట్టు          ( 1UL << 16UL )
#నిర్వచించు పోర్టు_SCB_USG_FAULT_ENABLE_బిట్టు          ( 1UL << 18UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants used to check the installation of the FreeRTOS interrupt handlers.
 */
#నిర్వచించు పోర్టు_సదిశ_సూచీ_SVC       ( 11 )
#నిర్వచించు పోర్టు_సదిశ_సూచీ_PENDSV    ( 14 )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to check the validity of an interrupt priority.
 */
#నిర్వచించు పోర్టు_NVIC_SHPR2_REG                 ( *( ( అస్థిర uint32_t * ) 0xE000ED1C ) )
#నిర్వచించు పోర్టు_మొదటి_USER_అంతరాయం_సంఖ్య    ( 16 )
#నిర్వచించు పోర్టు_NVIC_IP_REGISTERS_స్థానభ్రంశం_16    ( 0xE000E3F0 )
#నిర్వచించు పోర్టు_AIRCR_REG                      ( *( ( అస్థిర uint32_t * ) 0xE000ED0C ) )
#నిర్వచించు పోర్టు_శిఖరం_బిట్టు_యొక్క_BYTE                ( ( uint8_t ) 0x80 )
#నిర్వచించు పోర్టు_MAX_PRIGROUP_బిట్లు              ( ( uint8_t ) 7 )
#నిర్వచించు పోర్టు_ప్రాధాన్యత_సమూహం_ముసుగు            ( 0x07UL << 8UL )
#నిర్వచించు పోర్టు_PRIGROUP_జరుపు                 ( 8UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants used during system call enter and exit.
 */
#నిర్వచించు పోర్టు_PSR_దొంతర_PADDING_ముసుగు              ( 1UL << 9UL )
#నిర్వచించు పోర్టు_EXC_RETURN_దొంతర_చట్రం_TYPE_ముసుగు    ( 1UL << 4UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the FPU.
 */
#నిర్వచించు పోర్టు_CPACR               ( ( అస్థిర uint32_t * ) 0xe000ed88 ) /* Coprocessor Access Control Register. */
#నిర్వచించు పోర్టు_CPACR_CP10_విలువ    ( 3UL )
#నిర్వచించు పోర్టు_CPACR_CP11_విలువ    పోర్టు_CPACR_CP10_విలువ
#నిర్వచించు పోర్టు_CPACR_CP10_POS      ( 20UL )
#నిర్వచించు పోర్టు_CPACR_CP11_POS      ( 22UL )

#నిర్వచించు పోర్టు_FPCCR               ( ( అస్థిర uint32_t * ) 0xe000ef34 ) /* Floating Point Context Control Register. */
#నిర్వచించు పోర్టు_FPCCR_ASPEN_POS     ( 31UL )
#నిర్వచించు పోర్టు_FPCCR_ASPEN_ముసుగు    ( 1UL << పోర్టు_FPCCR_ASPEN_POS )
#నిర్వచించు పోర్టు_FPCCR_LSPEN_POS     ( 30UL )
#నిర్వచించు పోర్టు_FPCCR_LSPEN_ముసుగు    ( 1UL << పోర్టు_FPCCR_LSPEN_POS )
/*-----------------------------------------------------------*/

/**
 * @brief Offsets in the stack to the parameters when inside the SVC handler.
 */
#నిర్వచించు పోర్టు_స్థానభ్రంశం_గమ్యం_LR     ( 5 )
#నిర్వచించు పోర్టు_స్థానభ్రంశం_గమ్యం_PC     ( 6 )
#నిర్వచించు పోర్టు_స్థానభ్రంశం_గమ్యం_PSR    ( 7 )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the MPU.
 */
#నిర్వచించు పోర్టు_MPU_TYPE_REG                        ( *( ( అస్థిర uint32_t * ) 0xe000ed90 ) )
#నిర్వచించు పోర్టు_MPU_CTRL_REG                        ( *( ( అస్థిర uint32_t * ) 0xe000ed94 ) )
#నిర్వచించు పోర్టు_MPU_RNR_REG                         ( *( ( అస్థిర uint32_t * ) 0xe000ed98 ) )

#నిర్వచించు పోర్టు_MPU_RBAR_REG                        ( *( ( అస్థిర uint32_t * ) 0xe000ed9c ) )
#నిర్వచించు పోర్టు_MPU_RLAR_REG                        ( *( ( అస్థిర uint32_t * ) 0xe000eda0 ) )

#నిర్వచించు పోర్టు_MPU_RBAR_A1_REG                     ( *( ( అస్థిర uint32_t * ) 0xe000eda4 ) )
#నిర్వచించు పోర్టు_MPU_RLAR_A1_REG                     ( *( ( అస్థిర uint32_t * ) 0xe000eda8 ) )

#నిర్వచించు పోర్టు_MPU_RBAR_A2_REG                     ( *( ( అస్థిర uint32_t * ) 0xe000edac ) )
#నిర్వచించు పోర్టు_MPU_RLAR_A2_REG                     ( *( ( అస్థిర uint32_t * ) 0xe000edb0 ) )

#నిర్వచించు పోర్టు_MPU_RBAR_A3_REG                     ( *( ( అస్థిర uint32_t * ) 0xe000edb4 ) )
#నిర్వచించు పోర్టు_MPU_RLAR_A3_REG                     ( *( ( అస్థిర uint32_t * ) 0xe000edb8 ) )

#నిర్వచించు పోర్టు_MPU_MAIR0_REG                       ( *( ( అస్థిర uint32_t * ) 0xe000edc0 ) )
#నిర్వచించు పోర్టు_MPU_MAIR1_REG                       ( *( ( అస్థిర uint32_t * ) 0xe000edc4 ) )

#నిర్వచించు పోర్టు_MPU_RBAR_చిరునామా_ముసుగు               ( 0xffffffe0 ) /* Must be 32-byte aligned. */
#నిర్వచించు పోర్టు_MPU_RLAR_చిరునామా_ముసుగు               ( 0xffffffe0 ) /* Must be 32-byte aligned. */

#నిర్వచించు పోర్టు_MPU_RBAR_ACCESS_PERMISSIONS_ముసుగు    ( 3UL << 1UL )

#నిర్వచించు పోర్టు_MPU_MAIR_ATTR0_POS                  ( 0UL )
#నిర్వచించు పోర్టు_MPU_MAIR_ATTR0_ముసుగు                 ( 0x000000ff )

#నిర్వచించు పోర్టు_MPU_MAIR_ATTR1_POS                  ( 8UL )
#నిర్వచించు పోర్టు_MPU_MAIR_ATTR1_ముసుగు                 ( 0x0000ff00 )

#నిర్వచించు పోర్టు_MPU_MAIR_ATTR2_POS                  ( 16UL )
#నిర్వచించు పోర్టు_MPU_MAIR_ATTR2_ముసుగు                 ( 0x00ff0000 )

#నిర్వచించు పోర్టు_MPU_MAIR_ATTR3_POS                  ( 24UL )
#నిర్వచించు పోర్టు_MPU_MAIR_ATTR3_ముసుగు                 ( 0xff000000 )

#నిర్వచించు పోర్టు_MPU_MAIR_ATTR4_POS                  ( 0UL )
#నిర్వచించు పోర్టు_MPU_MAIR_ATTR4_ముసుగు                 ( 0x000000ff )

#నిర్వచించు పోర్టు_MPU_MAIR_ATTR5_POS                  ( 8UL )
#నిర్వచించు పోర్టు_MPU_MAIR_ATTR5_ముసుగు                 ( 0x0000ff00 )

#నిర్వచించు పోర్టు_MPU_MAIR_ATTR6_POS                  ( 16UL )
#నిర్వచించు పోర్టు_MPU_MAIR_ATTR6_ముసుగు                 ( 0x00ff0000 )

#నిర్వచించు పోర్టు_MPU_MAIR_ATTR7_POS                  ( 24UL )
#నిర్వచించు పోర్టు_MPU_MAIR_ATTR7_ముసుగు                 ( 0xff000000 )

#నిర్వచించు పోర్టు_MPU_RLAR_ATTR_INDEX0                ( 0UL << 1UL )
#నిర్వచించు పోర్టు_MPU_RLAR_ATTR_INDEX1                ( 1UL << 1UL )
#నిర్వచించు పోర్టు_MPU_RLAR_ATTR_INDEX2                ( 2UL << 1UL )
#నిర్వచించు పోర్టు_MPU_RLAR_ATTR_INDEX3                ( 3UL << 1UL )
#నిర్వచించు పోర్టు_MPU_RLAR_ATTR_INDEX4                ( 4UL << 1UL )
#నిర్వచించు పోర్టు_MPU_RLAR_ATTR_INDEX5                ( 5UL << 1UL )
#నిర్వచించు పోర్టు_MPU_RLAR_ATTR_INDEX6                ( 6UL << 1UL )
#నిర్వచించు పోర్టు_MPU_RLAR_ATTR_INDEX7                ( 7UL << 1UL )

#నిర్వచించు పోర్టు_MPU_RLAR_REGION_ENABLE              ( 1UL )

#ఒకవేళ ( పోర్టు_ARMV8_M_MINOR_సంస్కరణ >= 1 )

    /* Enable Privileged eXecute Never MPU attribute for the selected memory
     * region. */
    #నిర్వచించు పోర్టు_MPU_RLAR_PRIVILEGED_EXECUTE_NEVER    ( 1UL << 4UL )
#అయితే_ముగింపు /* portARMV8M_MINOR_VERSION >= 1 */

/* Enable privileged access to unmapped region. */
#నిర్వచించు పోర్టు_MPU_PRIV_BACKGROUND_ENABLE_బిట్టు    ( 1UL << 2UL )

/* Enable MPU. */
#నిర్వచించు పోర్టు_MPU_ENABLE_బిట్టు                    ( 1UL << 0UL )

/* Extract first address of the MPU region as encoded in the
 * RBAR (Region Base Address Register) value. */
#నిర్వచించు పోర్టు_వెలికితీయి_మొదటి_చిరునామా_FROM_RBAR( rbar ) \
    ( ( rbar ) & పోర్టు_MPU_RBAR_చిరునామా_ముసుగు )

/* Extract last address of the MPU region as encoded in the
 * RLAR (Region Limit Address Register) value. */
#నిర్వచించు పోర్టు_వెలికితీయి_చివరి_చిరునామా_FROM_RLAR( rlar ) \
    ( ( ( rlar ) & పోర్టు_MPU_RLAR_చిరునామా_ముసుగు ) | ~పోర్టు_MPU_RLAR_చిరునామా_ముసుగు )

/* Does addr lies within [start, end] address range? */
#నిర్వచించు పోర్టు_IS_చిరునామా_WITHIN_RANGE( addr, ప్రారంభం, చివర ) \
    ( ( ( addr ) >= ( ప్రారంభం ) ) && ( ( addr ) <= ( చివర ) ) )

/* Is the access request satisfied by the available permissions? */
#నిర్వచించు పోర్టు_IS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#నిర్వచించు పోర్టు_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#నిర్వచించు పోర్టు_కూడు_UINT32_WILL_అధికప్రవాహం( a, b )    ( ( a ) > ( పోర్టు_UINT32_MAX - ( b ) ) )
/*-----------------------------------------------------------*/

/**
 * @brief The maximum 24-bit number.
 *
 * It is needed because the systick is a 24-bit counter.
 */
#నిర్వచించు పోర్టు_MAX_24_బిట్టు_సంఖ్య       ( 0xffffffUL )

/**
 * @brief A fiddle factor to estimate the number of SysTick counts that would
 * have occurred while the SysTick counter is stopped during tickless idle
 * calculations.
 */
#నిర్వచించు పోర్టు_MISSED_COUNTS_గుణకం    ( 94UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to set up the initial stack.
 */
#నిర్వచించు పోర్టు_INITIAL_XPSR    ( 0x01000000 )

#ఒకవేళ ( config_నిరంతరం_FREERTOS_SECURE_ONLY == 1 )

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
    #నిర్వచించు పోర్టు_INITIAL_EXC_RETURN    ( 0xfffffffd )
#లేకపోతే

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
    #నిర్వచించు పోర్టు_INITIAL_EXC_RETURN    ( 0xffffffbc )
#అయితే_ముగింపు /* configRUN_FREERTOS_SECURE_ONLY */

/**
 * @brief CONTROL register privileged bit mask.
 *
 * Bit[0] in CONTROL register tells the privilege:
 *  Bit[0] = 0 ==> The task is privileged.
 *  Bit[0] = 1 ==> The task is not privileged.
 */
#నిర్వచించు పోర్టు_CONTROL_PRIVILEGED_ముసుగు         ( 1UL << 0UL )

/**
 * @brief Initial CONTROL register values.
 */
#నిర్వచించు పోర్టు_INITIAL_CONTROL_UNPRIVILEGED    ( 0x3 )
#నిర్వచించు పోర్టు_INITIAL_CONTROL_PRIVILEGED      ( 0x2 )

/**
 * @brief Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register.
 */
#నిర్వచితం_కాకపోతే configSYSTICK_CLOCK_HZ
    #నిర్వచించు configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #నిర్వచించు పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG    ( పోర్టు_NVIC_SYSTICK_CLK_బిట్టు )
#లేకపోతే
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #నిర్వచించు పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG    ( 0 )
#అయితే_ముగింపు

/**
 * @brief Let the user override the pre-loading of the initial LR with the
 * address of prvTaskExitError() in case it messes up unwinding of the stack
 * in the debugger.
 */
#నిర్వచితమైతే config_TASK_RETURN_చిరునామా
    #నిర్వచించు పోర్టు_TASK_RETURN_చిరునామా    config_TASK_RETURN_చిరునామా
#లేకపోతే
    #నిర్వచించు పోర్టు_TASK_RETURN_చిరునామా    prvTaskExitError
#అయితే_ముగింపు

/**
 * @brief If portPRELOAD_REGISTERS then registers will be given an initial value
 * when a task is created. This helps in debugging at the cost of code size.
 */
#నిర్వచించు పోర్టు_PRELOAD_REGISTERS    1

/**
 * @brief A task is created without a secure context, and must call
 * portALLOCATE_SECURE_CONTEXT() to give itself a secure context before it makes
 * any secure calls.
 */
#నిర్వచించు పోర్టు_NO_SECURE_CONTEXT    0

/**
 * @brief Constants required to check and configure PACBTI security feature implementation.
 */
#ఒకవేళ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )

    #నిర్వచించు పోర్టు_ID_ISAR5_REG       ( *( ( అస్థిర uint32_t * ) 0xe000ed74 ) )

    #నిర్వచించు పోర్టు_CONTROL_UPAC_EN    ( 1UL << 7UL )
    #నిర్వచించు పోర్టు_CONTROL_PAC_EN     ( 1UL << 6UL )
    #నిర్వచించు పోర్టు_CONTROL_UBTI_EN    ( 1UL << 5UL )
    #నిర్వచించు పోర్టు_CONTROL_BTI_EN     ( 1UL << 4UL )

#అయితే_ముగింపు /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Used to catch tasks that attempt to return from their implementing
 * function.
 */
స్థిర శూన్య prvTaskExitError( శూన్య );

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Extract MPU region's access permissions from the Region Base Address
     * Register (RBAR) value.
     *
     * @param ulRBARValue RBAR value for the MPU region.
     *
     * @return uint32_t Access permissions.
     */
    స్థిర uint32_t prvGetRegionAccessPermissions( uint32_t ulRBARValue ) PRIVILEGED_FUNCTION;
#అయితే_ముగింపు /* configENABLE_MPU == 1 && configUSE_MPU_WRAPPERS_V1 == 0 */

#ఒకవేళ ( configENABLE_MPU == 1 )

    /**
     * @brief Setup the Memory Protection Unit (MPU).
     */
    స్థిర శూన్య prv_అమరిక_MPU( శూన్య ) PRIVILEGED_FUNCTION;
#అయితే_ముగింపు /* configENABLE_MPU */

#ఒకవేళ ( configENABLE_FPU == 1 )

    /**
     * @brief Setup the Floating Point Unit (FPU).
     */
    స్థిర శూన్య prv_అమరిక_FPU( శూన్య ) PRIVILEGED_FUNCTION;
#అయితే_ముగింపు /* configENABLE_FPU */

#ఒకవేళ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )

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
    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
        స్థిర uint32_t prvConfigurePACBTI( పునాది_Type_t x_Write_Control_రిజిస్టరు );
    #లేకపోతే /* #if ( configNUMBER_OF_CORES == 1 ) */
        uint32_t vConfigurePACBTI( పునాది_Type_t x_Write_Control_రిజిస్టరు );
    #అయితే_ముగింపు /* #if ( configNUMBER_OF_CORES == 1 ) */

#అయితే_ముగింపు /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

/**
 * @brief Setup the timer to generate the tick interrupts.
 *
 * The implementation in this file is weak to allow application writers to
 * change the timer used to generate the tick interrupt.
 */
శూన్య v_పోర్టు_అమరిక_Timer_అంతరాయం( శూన్య ) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether the current execution context is interrupt.
 *
 * @return pdTRUE if the current execution context is interrupt, pdFALSE
 * otherwise.
 */
పునాది_Type_t x_పోర్టు_Is_Inside_అంతరాయం( శూన్య );

/**
 * @brief Yield the processor.
 */
శూన్య v_పోర్టు_Yield( శూన్య ) PRIVILEGED_FUNCTION;

/**
 * @brief Enter critical section.
 */
శూన్య v_పోర్టు_Enter_Critical( శూన్య ) PRIVILEGED_FUNCTION;

/**
 * @brief Exit from critical section.
 */
శూన్య v_పోర్టు_Exit_Critical( శూన్య ) PRIVILEGED_FUNCTION;

/**
 * @brief SysTick handler.
 */
శూన్య SysTick_Handler( శూన్య ) PRIVILEGED_FUNCTION;

/**
 * @brief C part of SVC handler.
 */
పోర్టు_DONT_DISCARD శూన్య v_పోర్టు_SVCHandler_C( uint32_t * pul_Caller_దొంతర_చిరునామా ) PRIVILEGED_FUNCTION;

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the system call stack so that upon returning from
     * SVC, the system call stack is used.
     *
     * @param pulTaskStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    శూన్య vSystemCallEnter( uint32_t * pul_Task_దొంతర,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_సంఖ్య ) PRIVILEGED_FUNCTION;

#అయితే_ముగింపు /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    శూన్య vRequestSystemCallExit( శూన్య ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#అయితే_ముగింపు /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param pulSystemCallStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     */
    శూన్య vSystemCallExit( uint32_t * pul_System_Call_దొంతర,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#అయితే_ముగింపు /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ఒకవేళ ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    పునాది_Type_t x_పోర్టు_Is_Task_Privileged( శూన్య ) PRIVILEGED_FUNCTION;

#అయితే_ముగింపు /* configENABLE_MPU == 1 */

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )

    /**
     * @brief Platform/Application-defined function that wakes up the secondary cores.
     *
     * @return pdTRUE if the secondary cores were successfully woken up.
     *         pdFALSE otherwise.
     */
    బాహ్య పునాది_Type_t configWAKE_SECONDARY_CORES( శూన్య );

#అయితే_ముగింపు /* #if ( configNUMBER_OF_CORES > 1 ) */

/**
 * @brief Configures interrupt priorities.
 */
శూన్య v_పోర్టు_Configure_అంతరాయం_Priorities( శూన్య ) PRIVILEGED_FUNCTION;
/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief This variable is set to pdTRUE when the scheduler is started.
     */
    PRIVILEGED_దత్తాంశం స్థిర పునాది_Type_t xSchedulerRunning = pdFALSE;

#అయితే_ముగింపు /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/**
 * @brief Each task maintains its own interrupt status in the critical nesting
 * variable.
 */
#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
    PRIVILEGED_దత్తాంశం స్థిర అస్థిర uint32_t ulCriticalNesting = 0UL;
#లేకపోతే /* #if ( configNUMBER_OF_CORES == 1 ) */
    PRIVILEGED_దత్తాంశం అస్థిర uint32_t ulCriticalNestings[ config_సంఖ్య_యొక్క_CORES ] = { 0 };
    /* Flags to check if the secondary cores are ready. */
    PRIVILEGED_దత్తాంశం అస్థిర uint8_t ucSecondaryCoresReadyFlags[ config_సంఖ్య_యొక్క_CORES - 1 ] = { 0 };
    /* Flag to indicate that the primary core has completed its initialisation. */
    PRIVILEGED_దత్తాంశం అస్థిర uint8_t uc_Primary_Core_Init_పూర్తి_Flag = 0;
 #అయితే_ముగింపు /* #if ( configNUMBER_OF_CORES == 1 ) */

#ఒకవేళ ( configENABLE_TRUSTZONE == 1 )

    /**
     * @brief Saved as part of the task context to indicate which context the
     * task is using on the secure side.
     */
    PRIVILEGED_దత్తాంశం పోర్టు_DONT_DISCARD అస్థిర SecureContextHandle_t xSecureContext = పోర్టు_NO_SECURE_CONTEXT;
#అయితే_ముగింపు /* configENABLE_TRUSTZONE */

/**
 * @brief Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#ఒకవేళ ( ( configASSERT_DEFINED == 1 ) && ( పోర్టు_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) )

    స్థిర uint8_t uc_Max_Sys_Call_ప్రాధాన్యత = 0;
    స్థిర uint32_t ulMaxPRIGROUPValue = 0;
    స్థిర స్థిరరాశి అస్థిర uint8_t * స్థిరరాశి pc_అంతరాయం_ప్రాధాన్యత_Registers = ( స్థిరరాశి అస్థిర uint8_t * ) పోర్టు_NVIC_IP_REGISTERS_స్థానభ్రంశం_16;

#అయితే_ముగింపు /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */

#ఒకవేళ ( configUSE_TICKLESS_IDLE == 1 )

    /**
     * @brief The number of SysTick increments that make up one tick period.
     */
    PRIVILEGED_దత్తాంశం స్థిర uint32_t ulTimerCountsForOneTick = 0;

    /**
     * @brief The maximum number of tick periods that can be suppressed is
     * limited by the 24 bit resolution of the SysTick timer.
     */
    PRIVILEGED_దత్తాంశం స్థిర uint32_t x_గరిష్ఠ_Possible_Suppressed_Ticks = 0;

    /**
     * @brief Compensate for the CPU cycles that pass while the SysTick is
     * stopped (low power functionality only).
     */
    PRIVILEGED_దత్తాంశం స్థిర uint32_t ulStoppedTimerCompensation = 0;
#అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) శూన్య v_పోర్టు_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_సమయం )
    {
        uint32_t ul_Reload_విలువ, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_ఎడమ;
        TickType_t x_Modifiable_Idle_సమయం;

        /* Make sure the SysTick reload value does not overflow the counter. */
        ఒకవేళ( x_Expected_Idle_సమయం > x_గరిష్ఠ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_సమయం = x_గరిష్ఠ_Possible_Suppressed_Ticks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm అస్థిర ( "cpsid i" ::: "memory" );
        __asm అస్థిర ( "dsb" );
        __asm అస్థిర ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        ఒకవేళ( e_Task_Confirm_Sleep_బహుళకం_స్థితి() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the cpsid instruction
             * above. */
            __asm అస్థిర ( "cpsie i" ::: "memory" );
        }
        లేకపోతే
        {
            /* Stop the SysTick momentarily.  The time the SysTick is stopped for
             * is accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            పోర్టు_NVIC_SYSTICK_CTRL_REG = ( పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG | పోర్టు_NVIC_SYSTICK_INT_బిట్టు );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_ఎడమ = పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG;

            ఒకవేళ( ul_Sys_Tick_Decrements_ఎడమ == 0 )
            {
                ul_Sys_Tick_Decrements_ఎడమ = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_విలువ = ul_Sys_Tick_Decrements_ఎడమ + ( ulTimerCountsForOneTick * ( x_Expected_Idle_సమయం - 1UL ) );

            ఒకవేళ( ( పోర్టు_NVIC_INT_CTRL_REG & పోర్టు_NVIC_PEND_SYSTICK_సమితి_బిట్టు ) != 0 )
            {
                పోర్టు_NVIC_INT_CTRL_REG = పోర్టు_NVIC_PEND_SYSTICK_CLEAR_బిట్టు;
                ul_Reload_విలువ -= ulTimerCountsForOneTick;
            }

            ఒకవేళ( ul_Reload_విలువ > ulStoppedTimerCompensation )
            {
                ul_Reload_విలువ -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ul_Reload_విలువ;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG = 0UL;

            /* Restart SysTick. */
            పోర్టు_NVIC_SYSTICK_CTRL_REG |= పోర్టు_NVIC_SYSTICK_ENABLE_బిట్టు;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            x_Modifiable_Idle_సమయం = x_Expected_Idle_సమయం;
            configPRE_SLEEP_PROCESSING( x_Modifiable_Idle_సమయం );

            ఒకవేళ( x_Modifiable_Idle_సమయం > 0 )
            {
                __asm అస్థిర ( "dsb" ::: "memory" );
                __asm అస్థిర ( "wfi" );
                __asm అస్థిర ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_సమయం );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the cpsid instruction above. */
            __asm అస్థిర ( "cpsie i" ::: "memory" );
            __asm అస్థిర ( "dsb" );
            __asm అస్థిర ( "isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm అస్థిర ( "cpsid i" ::: "memory" );
            __asm అస్థిర ( "dsb" );
            __asm అస్థిర ( "isb" );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            పోర్టు_NVIC_SYSTICK_CTRL_REG = ( పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG | పోర్టు_NVIC_SYSTICK_INT_బిట్టు );

            /* Determine whether the SysTick has already counted to zero. */
            ఒకవేళ( ( పోర్టు_NVIC_SYSTICK_CTRL_REG & పోర్టు_NVIC_SYSTICK_లెక్క_FLAG_బిట్టు ) != 0 )
            {
                uint32_t ul_Calculated_ఎక్కించు_విలువ;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_ఎక్కించు_విలువ = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_విలువ - పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                ఒకవేళ( ( ul_Calculated_ఎక్కించు_విలువ <= ulStoppedTimerCompensation ) || ( ul_Calculated_ఎక్కించు_విలువ > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_ఎక్కించు_విలువ = ( ulTimerCountsForOneTick - 1UL );
                }

                పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ul_Calculated_ఎక్కించు_విలువ;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = x_Expected_Idle_సమయం - 1UL;
            }
            లేకపోతే
            {
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_ఎడమ = పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG;
                #ఒకవేళ ( పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG != పోర్టు_NVIC_SYSTICK_CLK_బిట్టు )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    ఒకవేళ( ul_Sys_Tick_Decrements_ఎడమ == 0 )
                    {
                        ul_Sys_Tick_Decrements_ఎడమ = ul_Reload_విలువ;
                    }
                }
                #అయితే_ముగింపు /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_సమయం * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_ఎడమ;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG = 0UL;
            పోర్టు_NVIC_SYSTICK_CTRL_REG = పోర్టు_NVIC_SYSTICK_CLK_బిట్టు | పోర్టు_NVIC_SYSTICK_INT_బిట్టు | పోర్టు_NVIC_SYSTICK_ENABLE_బిట్టు;
            #ఒకవేళ ( పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG == పోర్టు_NVIC_SYSTICK_CLK_బిట్టు )
            {
                పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ulTimerCountsForOneTick - 1UL;
            }
            #లేకపోతే
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                పోర్టు_NVIC_SYSTICK_CTRL_REG = పోర్టు_NVIC_SYSTICK_CLK_బిట్టు | పోర్టు_NVIC_SYSTICK_INT_బిట్టు;

                ఒకవేళ( ( పోర్టు_NVIC_SYSTICK_CTRL_REG & పోర్టు_NVIC_SYSTICK_లెక్క_FLAG_బిట్టు ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG = 0;
                }

                పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ulTimerCountsForOneTick - 1UL;
                పోర్టు_NVIC_SYSTICK_CTRL_REG = పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG | పోర్టు_NVIC_SYSTICK_INT_బిట్టు | పోర్టు_NVIC_SYSTICK_ENABLE_బిట్టు;
            }
            #అయితే_ముగింపు /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            v_Task_అడుగు_Tick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __asm అస్థిర ( "cpsie i" ::: "memory" );
        }
    }

#అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

__attribute__( ( weak ) ) శూన్య v_పోర్టు_అమరిక_Timer_అంతరాయం( శూన్య ) /* PRIVILEGED_FUNCTION */
{
    /* Calculate the constants required to configure the tick interrupt. */
    #ఒకవేళ ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_రేటు_HZ );
        x_గరిష్ఠ_Possible_Suppressed_Ticks = పోర్టు_MAX_24_బిట్టు_సంఖ్య / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = పోర్టు_MISSED_COUNTS_గుణకం / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */

    /* Stop and reset SysTick.
     *
     * QEMU versions older than 7.0.0 contain a bug which causes an error if we
     * enable SysTick without first selecting a valid clock source. We trigger
     * the bug if we change clock sources from a clock with a zero clock period
     * to one with a nonzero clock period and enable Systick at the same time.
     * So we configure the CLKSOURCE bit here, prior to setting the ENABLE bit.
     * This workaround avoids the bug in QEMU versions older than 7.0.0. */
    పోర్టు_NVIC_SYSTICK_CTRL_REG = పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG;
    పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_రేటు_HZ ) - 1UL;
    పోర్టు_NVIC_SYSTICK_CTRL_REG = పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG | పోర్టు_NVIC_SYSTICK_INT_బిట్టు | పోర్టు_NVIC_SYSTICK_ENABLE_బిట్టు;
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prvTaskExitError( శూన్య )
{
    అస్థిర uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
        configASSERT( ulCriticalNesting == ~0UL );
    #లేకపోతే /* #if ( configNUMBER_OF_CORES == 1 ) */
        configASSERT( ulCriticalNestings[ పోర్టు_GET_CORE_ID() ] == ~0UL );
    #అయితే_ముగింపు /* #if ( configNUMBER_OF_CORES == 1 ) */
    పోర్టు_DISABLE_INTERRUPTS();

    అయితే( ulDummy == 0 )
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

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    స్థిర uint32_t prvGetRegionAccessPermissions( uint32_t ulRBARValue ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ulAccessPermissions = 0;

        ఒకవేళ( ( ulRBARValue & పోర్టు_MPU_RBAR_ACCESS_PERMISSIONS_ముసుగు ) == పోర్టు_MPU_REGION_READ_ONLY )
        {
            ulAccessPermissions = tskMPU_READ_PERMISSION;
        }

        ఒకవేళ( ( ulRBARValue & పోర్టు_MPU_RBAR_ACCESS_PERMISSIONS_ముసుగు ) == పోర్టు_MPU_REGION_READ_WRITE )
        {
            ulAccessPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
        }

        తిరిగి ulAccessPermissions;
    }

#అయితే_ముగింపు /* configENABLE_MPU == 1 && configUSE_MPU_WRAPPERS_V1 == 0 */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configENABLE_MPU == 1 )

    స్థిర శూన్య prv_అమరిక_MPU( శూన్య ) /* PRIVILEGED_FUNCTION */
    {
        #ఒకవేళ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            బాహ్య uint32_t * __privileged_functions_start__;
            బాహ్య uint32_t * __privileged_functions_end__;
            బాహ్య uint32_t * __syscalls_flash_start__;
            బాహ్య uint32_t * __syscalls_flash_end__;
            బాహ్య uint32_t * __unprivileged_flash_start__;
            బాహ్య uint32_t * __unprivileged_flash_end__;
            బాహ్య uint32_t * __privileged_sram_start__;
            బాహ్య uint32_t * __privileged_sram_end__;
        #లేకపోతే /* if defined( __ARMCC_VERSION ) */
            /* Declaration when these variable are exported from linker scripts. */
            బాహ్య uint32_t __privileged_functions_start__[];
            బాహ్య uint32_t __privileged_functions_end__[];
            బాహ్య uint32_t __syscalls_flash_start__[];
            బాహ్య uint32_t __syscalls_flash_end__[];
            బాహ్య uint32_t __unprivileged_flash_start__[];
            బాహ్య uint32_t __unprivileged_flash_end__[];
            బాహ్య uint32_t __privileged_sram_start__[];
            బాహ్య uint32_t __privileged_sram_end__[];
        #అయితే_ముగింపు /* defined( __ARMCC_VERSION ) */

        /* The only permitted number of regions are 8 or 16. */
        configASSERT( ( config_మొత్తం_MPU_REGIONS == 8 ) || ( config_మొత్తం_MPU_REGIONS == 16 ) );

        /* MAIR0 - Index 0. */
        పోర్టు_MPU_MAIR0_REG |= ( ( పోర్టు_MPU_సాధారణ_జ్ఞాపకం_BUFFERABLE_CACHEABLE << పోర్టు_MPU_MAIR_ATTR0_POS ) & పోర్టు_MPU_MAIR_ATTR0_ముసుగు );
        /* MAIR0 - Index 1. */
        పోర్టు_MPU_MAIR0_REG |= ( ( పోర్టు_MPU_DEVICE_జ్ఞాపకం_n_Gn_RE << పోర్టు_MPU_MAIR_ATTR1_POS ) & పోర్టు_MPU_MAIR_ATTR1_ముసుగు );

        /* Setup privileged flash as Read Only so that privileged tasks can
         * read it but not modify. */
        పోర్టు_MPU_RNR_REG = పోర్టు_PRIVILEGED_FLASH_REGION;
        పోర్టు_MPU_RBAR_REG = ( ( ( uint32_t ) __privileged_functions_start__ ) & పోర్టు_MPU_RBAR_చిరునామా_ముసుగు ) |
                           ( పోర్టు_MPU_REGION_NON_SHAREABLE ) |
                           ( పోర్టు_MPU_REGION_PRIVILEGED_READ_ONLY );
        పోర్టు_MPU_RLAR_REG = ( ( ( uint32_t ) __privileged_functions_end__ ) & పోర్టు_MPU_RLAR_చిరునామా_ముసుగు ) |
                           ( పోర్టు_MPU_RLAR_ATTR_INDEX0 ) |
                           ( పోర్టు_MPU_RLAR_REGION_ENABLE );

        /* Setup unprivileged flash as Read Only by both privileged and
         * unprivileged tasks. All tasks can read it but no-one can modify. */
        పోర్టు_MPU_RNR_REG = పోర్టు_UNPRIVILEGED_FLASH_REGION;
        పోర్టు_MPU_RBAR_REG = ( ( ( uint32_t ) __unprivileged_flash_start__ ) & పోర్టు_MPU_RBAR_చిరునామా_ముసుగు ) |
                           ( పోర్టు_MPU_REGION_NON_SHAREABLE ) |
                           ( పోర్టు_MPU_REGION_READ_ONLY );
        పోర్టు_MPU_RLAR_REG = ( ( ( uint32_t ) __unprivileged_flash_end__ ) & పోర్టు_MPU_RLAR_చిరునామా_ముసుగు ) |
                           ( పోర్టు_MPU_RLAR_ATTR_INDEX0 ) |
                           ( పోర్టు_MPU_RLAR_REGION_ENABLE );

        /* Setup unprivileged syscalls flash as Read Only by both privileged
         * and unprivileged tasks. All tasks can read it but no-one can modify. */
        పోర్టు_MPU_RNR_REG = పోర్టు_UNPRIVILEGED_SYSCALLS_REGION;
        పోర్టు_MPU_RBAR_REG = ( ( ( uint32_t ) __syscalls_flash_start__ ) & పోర్టు_MPU_RBAR_చిరునామా_ముసుగు ) |
                           ( పోర్టు_MPU_REGION_NON_SHAREABLE ) |
                           ( పోర్టు_MPU_REGION_READ_ONLY );
        పోర్టు_MPU_RLAR_REG = ( ( ( uint32_t ) __syscalls_flash_end__ ) & పోర్టు_MPU_RLAR_చిరునామా_ముసుగు ) |
                           ( పోర్టు_MPU_RLAR_ATTR_INDEX0 ) |
                           ( పోర్టు_MPU_RLAR_REGION_ENABLE );

        /* Setup RAM containing kernel data for privileged access only. */
        పోర్టు_MPU_RNR_REG = పోర్టు_PRIVILEGED_RAM_REGION;
        పోర్టు_MPU_RBAR_REG = ( ( ( uint32_t ) __privileged_sram_start__ ) & పోర్టు_MPU_RBAR_చిరునామా_ముసుగు ) |
                           ( పోర్టు_MPU_REGION_NON_SHAREABLE ) |
                           ( పోర్టు_MPU_REGION_PRIVILEGED_READ_WRITE ) |
                           ( పోర్టు_MPU_REGION_EXECUTE_NEVER );
        పోర్టు_MPU_RLAR_REG = ( ( ( uint32_t ) __privileged_sram_end__ ) & పోర్టు_MPU_RLAR_చిరునామా_ముసుగు ) |
                           ( పోర్టు_MPU_RLAR_ATTR_INDEX0 ) |
                           ( పోర్టు_MPU_RLAR_REGION_ENABLE );

        /* Enable mem fault. */
        పోర్టు_SCB_SYS_HANDLER_CTRL_STATE_REG |= పోర్టు_SCB_MEM_FAULT_ENABLE_బిట్టు;

        /* Enable MPU with privileged background access i.e. unmapped
         * regions have privileged access. */
        పోర్టు_MPU_CTRL_REG |= ( పోర్టు_MPU_PRIV_BACKGROUND_ENABLE_బిట్టు | పోర్టు_MPU_ENABLE_బిట్టు );
    }

#అయితే_ముగింపు /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configENABLE_FPU == 1 )

    స్థిర శూన్య prv_అమరిక_FPU( శూన్య ) /* PRIVILEGED_FUNCTION */
    {
        #ఒకవేళ ( configENABLE_TRUSTZONE == 1 )
        {
            /* Enable non-secure access to the FPU. */
            SecureInit_EnableNSFPUAccess();
        }
        #అయితే_ముగింపు /* configENABLE_TRUSTZONE */

        /* CP10 = 11 ==> Full access to FPU i.e. both privileged and
         * unprivileged code should be able to access FPU. CP11 should be
         * programmed to the same value as CP10. */
        *( పోర్టు_CPACR ) |= ( ( పోర్టు_CPACR_CP10_విలువ << పోర్టు_CPACR_CP10_POS ) |
                            ( పోర్టు_CPACR_CP11_విలువ << పోర్టు_CPACR_CP11_POS )
                            );

        /* ASPEN = 1 ==> Hardware should automatically preserve floating point
         * context on exception entry and restore on exception return.
         * LSPEN = 1 ==> Enable lazy context save of FP state. */
        *( పోర్టు_FPCCR ) |= ( పోర్టు_FPCCR_ASPEN_ముసుగు | పోర్టు_FPCCR_LSPEN_ముసుగు );
    }

#అయితే_ముగింపు /* configENABLE_FPU */
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Yield( శూన్య ) /* PRIVILEGED_FUNCTION */
{
    /* Set a PendSV to request a context switch. */
    పోర్టు_NVIC_INT_CTRL_REG = పోర్టు_NVIC_PENDSVSET_బిట్టు;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm అస్థిర ( "dsb" ::: "memory" );
    __asm అస్థిర ( "isb" );
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
    శూన్య v_పోర్టు_Enter_Critical( శూన్య ) /* PRIVILEGED_FUNCTION */
    {
        పోర్టు_DISABLE_INTERRUPTS();
        ulCriticalNesting++;
        /* Barriers are normally not required but do ensure the code is
        * completely within the specified behaviour for the architecture. */
        __asm అస్థిర ( "dsb" ::: "memory" );
        __asm అస్థిర ( "isb" );
    }
    /*-----------------------------------------------------------*/

    శూన్య v_పోర్టు_Exit_Critical( శూన్య ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( ulCriticalNesting );
        ulCriticalNesting--;

        ఒకవేళ( ulCriticalNesting == 0 )
        {
            పోర్టు_ENABLE_INTERRUPTS();
        }
    }
#అయితే_ముగింపు /* configNUMBER_OF_CORES == 1 */
/*-----------------------------------------------------------*/

శూన్య SysTick_Handler( శూన్య ) /* PRIVILEGED_FUNCTION */
{
    uint32_t ul_మునుపటి_ముసుగు;

    ul_మునుపటి_ముసుగు = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();
    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )
        UBaseType_t ux_Saved_అంతరాయం_స్థితి = పోర్టు_ENTER_CRITICAL_FROM_ISR();
    #అయితే_ముగింపు /* if ( configNUMBER_OF_CORES > 1 ) */

    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_గమ్యం_SCHEDULER();
            /* Pend a context switch. */
            పోర్టు_NVIC_INT_CTRL_REG = పోర్టు_NVIC_PENDSVSET_బిట్టు;
        }
        లేకపోతే
        {
            traceISR_EXIT();
        }
    }
    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )
        పోర్టు_EXIT_CRITICAL_FROM_ISR( ux_Saved_అంతరాయం_స్థితి );
    #అయితే_ముగింపు /* if ( configNUMBER_OF_CORES > 1 ) */

    పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( ul_మునుపటి_ముసుగు );
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_SVCHandler_C( uint32_t * pul_Caller_దొంతర_చిరునామా ) /* PRIVILEGED_FUNCTION portDONT_DISCARD */
{
    #ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )
        #ఒకవేళ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            బాహ్య uint32_t * __syscalls_flash_start__;
            బాహ్య uint32_t * __syscalls_flash_end__;
        #లేకపోతే
            /* Declaration when these variable are exported from linker scripts. */
            బాహ్య uint32_t __syscalls_flash_start__[];
            బాహ్య uint32_t __syscalls_flash_end__[];
        #అయితే_ముగింపు /* defined( __ARMCC_VERSION ) */
    #అయితే_ముగింపు /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #ఒకవేళ ( configENABLE_MPU == 1 )
        #ఒకవేళ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            బాహ్య uint32_t * __privileged_functions_start__;
            బాహ్య uint32_t * __privileged_functions_end__;
        #లేకపోతే
            /* Declaration when these variable are exported from linker scripts. */
            బాహ్య uint32_t __privileged_functions_start__[];
            బాహ్య uint32_t __privileged_functions_end__[];
        #అయితే_ముగింపు /* defined( __ARMCC_VERSION ) */
    #అయితే_ముగింపు /* configENABLE_MPU == 1 */

    uint32_t ulPC;

    #ఒకవేళ ( configENABLE_TRUSTZONE == 1 )
        uint32_t ulR0, ulR1;
        బాహ్య TaskHandle_t pxCurrentTCB;
        #ఒకవేళ ( configENABLE_MPU == 1 )
            uint32_t ulControl, ulIsTaskPrivileged;
        #అయితే_ముగింపు /* configENABLE_MPU */
    #అయితే_ముగింపు /* configENABLE_TRUSTZONE */
    uint8_t ucSVCNumber;

    /* Register are stored on the stack in the following order - R0, R1, R2, R3,
     * R12, LR, PC, xPSR. */
    ulPC = pul_Caller_దొంతర_చిరునామా[ పోర్టు_స్థానభ్రంశం_గమ్యం_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    ఎంపిక( ucSVCNumber )
    {
    #ఒకవేళ ( configENABLE_TRUSTZONE == 1 )
        స్థితి పోర్టు_SVC_ALLOCATE_SECURE_CONTEXT:

            /* R0 contains the stack size passed as parameter to the
             * vPortAllocateSecureContext function. */
            ulR0 = pul_Caller_దొంతర_చిరునామా[ 0 ];

            #ఒకవేళ ( configENABLE_MPU == 1 )
            {
                /* Read the CONTROL register value. */
                __asm అస్థిర ( "mrs %0, control"  : "=r" ( ulControl ) );

                /* The task that raised the SVC is privileged if Bit[0]
                 * in the CONTROL register is 0. */
                ulIsTaskPrivileged = ( ( ulControl & పోర్టు_CONTROL_PRIVILEGED_ముసుగు ) == 0 );

                /* Allocate and load a context for the secure task. */
                xSecureContext = SecureContext_AllocateContext( ulR0, ulIsTaskPrivileged, pxCurrentTCB );
            }
            #లేకపోతే /* if ( configENABLE_MPU == 1 ) */
            {
                /* Allocate and load a context for the secure task. */
                xSecureContext = SecureContext_AllocateContext( ulR0, pxCurrentTCB );
            }
            #అయితే_ముగింపు /* configENABLE_MPU */

            configASSERT( xSecureContext != securecontextINVALID_CONTEXT_ID );
            Secure_Context_ఎక్కించు_Context( xSecureContext, pxCurrentTCB );
            ఆపు;

        స్థితి పోర్టు_SVC_FREE_SECURE_CONTEXT:
            #ఒకవేళ ( configENABLE_MPU == 1 )
            ఒకవేళ( ( ulPC >= ( uint32_t ) __privileged_functions_start__ ) &&
                ( ulPC <= ( uint32_t ) __privileged_functions_end__ ) )
            {
            #అయితే_ముగింపు /* configENABLE_MPU */
                /* R0 contains TCB being freed and R1 contains the secure
                 * context handle to be freed. */
                ulR0 = pul_Caller_దొంతర_చిరునామా[ 0 ];
                ulR1 = pul_Caller_దొంతర_చిరునామా[ 1 ];

                /* Free the secure context. */
                SecureContext_FreeContext( ( SecureContextHandle_t ) ulR1, ( శూన్య * ) ulR0 );
            #ఒకవేళ ( configENABLE_MPU == 1 )
            }
            #అయితే_ముగింపు /* configENABLE_MPU */
            ఆపు;
    #అయితే_ముగింపు /* configENABLE_TRUSTZONE */

        స్థితి పోర్టు_SVC_ప్రారంభం_SCHEDULER:
            #ఒకవేళ ( configENABLE_MPU == 1 )
            ఒకవేళ( ( ulPC >= ( uint32_t ) __privileged_functions_start__ ) &&
                ( ulPC <= ( uint32_t ) __privileged_functions_end__ ) )
            {
            #అయితే_ముగింపు /* configENABLE_MPU */
                #ఒకవేళ ( configENABLE_TRUSTZONE == 1 )
                {
                    /* De-prioritize the non-secure exceptions so that the
                     * non-secure pendSV runs at the lowest priority. */
                    SecureInit_DePrioritizeNSExceptions();

                    /* Initialize the secure context management system. */
                    SecureContext_Init();
                }
                #అయితే_ముగింపు /* configENABLE_TRUSTZONE */

                #ఒకవేళ ( configENABLE_FPU == 1 )
                {
                    /* Setup the Floating Point Unit (FPU). */
                    prv_అమరిక_FPU();
                }
                #అయితే_ముగింపు /* configENABLE_FPU */

                /* Setup the context of the first task so that the first task starts
                 * executing. */
                v_Restore_Context_యొక్క_మొదటి_Task();
            #ఒకవేళ ( configENABLE_MPU == 1 )
            }
            #అయితే_ముగింపు /* configENABLE_MPU */
            ఆపు;

    #ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )
        స్థితి పోర్టు_SVC_RAISE_PRIVILEGE:

            /* Only raise the privilege, if the svc was raised from any of
             * the system calls. */
            ఒకవేళ( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
            {
                vRaisePrivilege();
            }
            ఆపు;
    #అయితే_ముగింపు /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #ఒకవేళ ( configENABLE_MPU == 1 )
        స్థితి పోర్టు_SVC_YIELD:
            v_పోర్టు_Yield();
            ఆపు;
    #అయితే_ముగింపు /* configENABLE_MPU == 1 */

        అప్రమేయ:
            /* Incorrect SVC call. */
            configASSERT( pdFALSE );
    }
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    శూన్య vSystemCallEnter( uint32_t * pul_Task_దొంతర,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_సంఖ్య ) /* PRIVILEGED_FUNCTION */
    {
        బాహ్య TaskHandle_t pxCurrentTCB;
        బాహ్య UBaseType_t uxSystemCallImplementations[ అంకె_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_దొంతర;
        uint32_t ul_Hardware_Saved_Exception_చట్రం_కొలత, ulSystemCallLocation, i;

        #ఒకవేళ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            బాహ్య uint32_t * __syscalls_flash_start__;
            బాహ్య uint32_t * __syscalls_flash_end__;
        #లేకపోతే
            /* Declaration when these variable are exported from linker scripts. */
            బాహ్య uint32_t __syscalls_flash_start__[];
            బాహ్య uint32_t __syscalls_flash_end__[];
        #అయితే_ముగింపు /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PC ];
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
        ఒకవేళ( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_దొంతర_Info.pul_Task_దొంతర == ఖాళీ ) &&
            ( uxSystemCallImplementations[ uc_System_Call_సంఖ్య ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_దొంతర = pxMpuSettings->x_System_Call_దొంతర_Info.pul_System_Call_దొంతర;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            #ఒకవేళ ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )
            {
                ఒకవేళ( ( ulLR & పోర్టు_EXC_RETURN_దొంతర_చట్రం_TYPE_ముసుగు ) == 0UL )
                {
                    /* Extended frame i.e. FPU in use. */
                    ul_Hardware_Saved_Exception_చట్రం_కొలత = 26;
                    __asm అస్థిర (
                        " vpush {s0}         \n" /* Trigger lazy stacking. */
                        " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                        ::: "memory"
                        );
                }
                లేకపోతే
                {
                    /* Standard frame i.e. FPU not in use. */
                    ul_Hardware_Saved_Exception_చట్రం_కొలత = 8;
                }
            }
            #లేకపోతే /* if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */
            {
                ul_Hardware_Saved_Exception_చట్రం_కొలత = 8;
            }
            #అయితే_ముగింపు /* configENABLE_FPU || configENABLE_MVE */

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_దొంతర = pul_System_Call_దొంతర - ul_Hardware_Saved_Exception_చట్రం_కొలత;

            /* Copy the stack frame. */
            కొరకు( i = 0; i < ul_Hardware_Saved_Exception_చట్రం_కొలత; i++ )
            {
                pul_System_Call_దొంతర[ i ] = pul_Task_దొంతర[ i ];
            }

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_దొంతర_Info.ul_Link_రిజిస్టరు_At_System_Call_నమోదు = pul_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_LR ];

            /* Store the value of the PSPLIM register before the SVC was raised.
             * We need to restore it when we exit from the system call. */
            #ఒకవేళ ( పోర్టు_USE_PSPLIM_రిజిస్టరు == 1 )
            {
                __asm అస్థిర ( "mrs %0, psplim" : "=r" ( pxMpuSettings->x_System_Call_దొంతర_Info.ul_దొంతర_హద్దు_రిజిస్టరు_At_System_Call_నమోదు ) );
            }
            #అయితే_ముగింపు

            /* Use the pulSystemCallStack in thread mode. */
            __asm అస్థిర ( "msr psp, %0" : : "r" ( pul_System_Call_దొంతర ) );
            #ఒకవేళ ( పోర్టు_USE_PSPLIM_రిజిస్టరు == 1 )
            {
                __asm అస్థిర ( "msr psplim, %0" : : "r" ( pxMpuSettings->x_System_Call_దొంతర_Info.pul_System_Call_దొంతర_హద్దు ) );
            }
            #అయితే_ముగింపు

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PC ] = uxSystemCallImplementations[ uc_System_Call_సంఖ్య ];

            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_దొంతర_Info.pul_Task_దొంతర = pul_Task_దొంతర + ul_Hardware_Saved_Exception_చట్రం_కొలత;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            ఒకవేళ( ( pul_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PSR ] & పోర్టు_PSR_దొంతర_PADDING_ముసుగు ) == పోర్టు_PSR_దొంతర_PADDING_ముసుగు )
            {
                pxMpuSettings->ulTaskFlags |= పోర్టు_దొంతర_చట్రం_HAS_PADDING_FLAG;
            }
            లేకపోతే
            {
                pxMpuSettings->ulTaskFlags &= ( ~పోర్టు_దొంతర_చట్రం_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PSR ] &= ( ~పోర్టు_PSR_దొంతర_PADDING_ముసుగు );

            /* Raise the privilege for the duration of the system call. */
            __asm అస్థిర (
                " mrs r0, control     \n" /* Obtain current control value. */
                " movs r1, #1         \n" /* r1 = 1. */
                " bics r0, r1         \n" /* Clear nPRIV bit. */
                " msr control, r0     \n" /* Write back new control value. */
                ::: "r0", "r1", "memory"
                );
        }
    }

#అయితే_ముగింపు /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    శూన్య vRequestSystemCallExit( శూన్య ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm అస్థిర ( "svc %0 \n" ::"i" ( పోర్టు_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#అయితే_ముగింపు /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    శూన్య vSystemCallExit( uint32_t * pul_System_Call_దొంతర,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        బాహ్య TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_దొంతర;
        uint32_t ul_Hardware_Saved_Exception_చట్రం_కొలత, ulSystemCallLocation, i;

        #ఒకవేళ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            బాహ్య uint32_t * __privileged_functions_start__;
            బాహ్య uint32_t * __privileged_functions_end__;
        #లేకపోతే
            /* Declaration when these variable are exported from linker scripts. */
            బాహ్య uint32_t __privileged_functions_start__[];
            బాహ్య uint32_t __privileged_functions_end__[];
        #అయితే_ముగింపు /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PC ];
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
        ఒకవేళ( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_దొంతర_Info.pul_Task_దొంతర != ఖాళీ ) )
        {
            pul_Task_దొంతర = pxMpuSettings->x_System_Call_దొంతర_Info.pul_Task_దొంతర;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            #ఒకవేళ ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )
            {
                ఒకవేళ( ( ulLR & పోర్టు_EXC_RETURN_దొంతర_చట్రం_TYPE_ముసుగు ) == 0UL )
                {
                    /* Extended frame i.e. FPU in use. */
                    ul_Hardware_Saved_Exception_చట్రం_కొలత = 26;
                    __asm అస్థిర (
                        " vpush {s0}         \n" /* Trigger lazy stacking. */
                        " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                        ::: "memory"
                        );
                }
                లేకపోతే
                {
                    /* Standard frame i.e. FPU not in use. */
                    ul_Hardware_Saved_Exception_చట్రం_కొలత = 8;
                }
            }
            #లేకపోతే /* if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */
            {
                ul_Hardware_Saved_Exception_చట్రం_కొలత = 8;
            }
            #అయితే_ముగింపు /* configENABLE_FPU || configENABLE_MVE */

            /* Make space on the task stack for the stack frame. */
            pul_Task_దొంతర = pul_Task_దొంతర - ul_Hardware_Saved_Exception_చట్రం_కొలత;

            /* Copy the stack frame. */
            కొరకు( i = 0; i < ul_Hardware_Saved_Exception_చట్రం_కొలత; i++ )
            {
                pul_Task_దొంతర[ i ] = pul_System_Call_దొంతర[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm అస్థిర ( "msr psp, %0" : : "r" ( pul_Task_దొంతర ) );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PC ] = pxMpuSettings->x_System_Call_దొంతర_Info.ul_Link_రిజిస్టరు_At_System_Call_నమోదు;
            /* Ensure that LR has a valid value.*/
            pul_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_LR ] = pxMpuSettings->x_System_Call_దొంతర_Info.ul_Link_రిజిస్టరు_At_System_Call_నమోదు;

            /* Restore the PSPLIM register to what it was at the time of
             * system call entry. */
            #ఒకవేళ ( పోర్టు_USE_PSPLIM_రిజిస్టరు == 1 )
            {
                __asm అస్థిర ( "msr psplim, %0" : : "r" ( pxMpuSettings->x_System_Call_దొంతర_Info.ul_దొంతర_హద్దు_రిజిస్టరు_At_System_Call_నమోదు ) );
            }
            #అయితే_ముగింపు

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            ఒకవేళ( ( pxMpuSettings->ulTaskFlags & పోర్టు_దొంతర_చట్రం_HAS_PADDING_FLAG ) == పోర్టు_దొంతర_చట్రం_HAS_PADDING_FLAG )
            {
                pul_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PSR ] |= పోర్టు_PSR_దొంతర_PADDING_ముసుగు;
            }
            లేకపోతే
            {
                pul_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PSR ] &= ( ~పోర్టు_PSR_దొంతర_PADDING_ముసుగు );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_దొంతర_Info.pul_Task_దొంతర = ఖాళీ;

            /* Drop the privilege before returning to the thread mode. */
            __asm అస్థిర (
                " mrs r0, control     \n" /* Obtain current control value. */
                " movs r1, #1         \n" /* r1 = 1. */
                " orrs r0, r1         \n" /* Set nPRIV bit. */
                " msr control, r0     \n" /* Write back new control value. */
                ::: "r0", "r1", "memory"
                );
        }
    }

#అయితే_ముగింపు /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configENABLE_MPU == 1 )

    పునాది_Type_t x_పోర్టు_Is_Task_Privileged( శూన్య ) /* PRIVILEGED_FUNCTION */
    {
        పునాది_Type_t xTaskIsPrivileged = pdFALSE;
        స్థిరరాశి xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ఖాళీ ); /* Calling task's MPU settings. */

        ఒకవేళ( ( xTaskMpuSettings->ulTaskFlags & పోర్టు_TASK_IS_PRIVILEGED_FLAG ) == పోర్టు_TASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        తిరిగి xTaskIsPrivileged;
    }

#అయితే_ముగింపు /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configENABLE_MPU == 1 )

    దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                         దొంతర_Type_t * px_చివర_యొక్క_దొంతర,
                                         TaskFunction_t px_సంకేతం,
                                         శూన్య * pvParameters,
                                         పునాది_Type_t x_నిరంతరం_Privileged,
                                         xMPU_SETTINGS * xMPUSettings ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_సూచీ = 0;
        uint32_t ulControl = 0x0;

        xMPUSettings->ulContext[ ul_సూచీ ] = 0x04040404; /* r4. */
        ul_సూచీ++;
        xMPUSettings->ulContext[ ul_సూచీ ] = 0x05050505; /* r5. */
        ul_సూచీ++;
        xMPUSettings->ulContext[ ul_సూచీ ] = 0x06060606; /* r6. */
        ul_సూచీ++;
        xMPUSettings->ulContext[ ul_సూచీ ] = 0x07070707; /* r7. */
        ul_సూచీ++;
        xMPUSettings->ulContext[ ul_సూచీ ] = 0x08080808; /* r8. */
        ul_సూచీ++;
        xMPUSettings->ulContext[ ul_సూచీ ] = 0x09090909; /* r9. */
        ul_సూచీ++;
        xMPUSettings->ulContext[ ul_సూచీ ] = 0x10101010; /* r10. */
        ul_సూచీ++;
        xMPUSettings->ulContext[ ul_సూచీ ] = 0x11111111; /* r11. */
        ul_సూచీ++;

        xMPUSettings->ulContext[ ul_సూచీ ] = ( uint32_t ) pvParameters; /* r0. */
        ul_సూచీ++;
        xMPUSettings->ulContext[ ul_సూచీ ] = 0x01010101; /* r1. */
        ul_సూచీ++;
        xMPUSettings->ulContext[ ul_సూచీ ] = 0x02020202; /* r2. */
        ul_సూచీ++;
        xMPUSettings->ulContext[ ul_సూచీ ] = 0x03030303; /* r3. */
        ul_సూచీ++;
        xMPUSettings->ulContext[ ul_సూచీ ] = 0x12121212; /* r12. */
        ul_సూచీ++;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( uint32_t ) పోర్టు_TASK_RETURN_చిరునామా; /* LR. */
        ul_సూచీ++;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( uint32_t ) px_సంకేతం; /* PC. */
        ul_సూచీ++;
        xMPUSettings->ulContext[ ul_సూచీ ] = పోర్టు_INITIAL_XPSR; /* xPSR. */
        ul_సూచీ++;

        #ఒకవేళ ( configENABLE_TRUSTZONE == 1 )
        {
            xMPUSettings->ulContext[ ul_సూచీ ] = పోర్టు_NO_SECURE_CONTEXT; /* xSecureContext. */
            ul_సూచీ++;
        }
        #అయితే_ముగింపు /* configENABLE_TRUSTZONE */
        xMPUSettings->ulContext[ ul_సూచీ ] = ( uint32_t ) ( px_శిఖరం_యొక్క_దొంతర - 8 ); /* PSP with the hardware saved stack. */
        ul_సూచీ++;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( uint32_t ) px_చివర_యొక్క_దొంతర; /* PSPLIM. */
        ul_సూచీ++;

        #ఒకవేళ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
        {
            /* Check PACBTI security feature configuration before pushing the
             * CONTROL register's value on task's TCB. */
            #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
                ulControl = prvConfigurePACBTI( pdFALSE );
            #లేకపోతే /* configNUMBER_OF_CORES > 1 */
                ulControl = vConfigurePACBTI( pdFALSE );
            #అయితే_ముగింపు /* configNUMBER_OF_CORES */
        }
        #అయితే_ముగింపు /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

        ఒకవేళ( x_నిరంతరం_Privileged == pdTRUE )
        {
            xMPUSettings->ulTaskFlags |= పోర్టు_TASK_IS_PRIVILEGED_FLAG;
            xMPUSettings->ulContext[ ul_సూచీ ] = ( ulControl | ( uint32_t ) పోర్టు_INITIAL_CONTROL_PRIVILEGED ); /* CONTROL. */
            ul_సూచీ++;
        }
        లేకపోతే
        {
            xMPUSettings->ulTaskFlags &= ( ~పోర్టు_TASK_IS_PRIVILEGED_FLAG );
            xMPUSettings->ulContext[ ul_సూచీ ] = ( ulControl | ( uint32_t ) పోర్టు_INITIAL_CONTROL_UNPRIVILEGED ); /* CONTROL. */
            ul_సూచీ++;
        }

        xMPUSettings->ulContext[ ul_సూచీ ] = పోర్టు_INITIAL_EXC_RETURN; /* LR (EXC_RETURN). */
        ul_సూచీ++;

        #ఒకవేళ ( configUSE_MPU_WRAPPERS_V1 == 0 )
        {
            /* Ensure that the system call stack is double word aligned. */
            xMPUSettings->x_System_Call_దొంతర_Info.pul_System_Call_దొంతర = &( xMPUSettings->x_System_Call_దొంతర_Info.ul_System_Call_దొంతర_బఫరు[ config_SYSTEM_CALL_దొంతర_కొలత - 1 ] );
            xMPUSettings->x_System_Call_దొంతర_Info.pul_System_Call_దొంతర = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_దొంతర_Info.pul_System_Call_దొంతర ) &
                                                                                     ( uint32_t ) ( ~( పోర్టు_BYTE_ALIGNMENT_ముసుగు ) ) );

            xMPUSettings->x_System_Call_దొంతర_Info.pul_System_Call_దొంతర_హద్దు = &( xMPUSettings->x_System_Call_దొంతర_Info.ul_System_Call_దొంతర_బఫరు[ 0 ] );
            xMPUSettings->x_System_Call_దొంతర_Info.pul_System_Call_దొంతర_హద్దు = ( uint32_t * ) ( ( ( uint32_t ) ( xMPUSettings->x_System_Call_దొంతర_Info.pul_System_Call_దొంతర_హద్దు ) +
                                                                                            ( uint32_t ) ( పోర్టు_BYTE_ALIGNMENT - 1 ) ) &
                                                                                          ( uint32_t ) ( ~( పోర్టు_BYTE_ALIGNMENT_ముసుగు ) ) );

            /* This is not NULL only for the duration of a system call. */
            xMPUSettings->x_System_Call_దొంతర_Info.pul_Task_దొంతర = ఖాళీ;
        }
        #అయితే_ముగింపు /* configUSE_MPU_WRAPPERS_V1 == 0 */

        #ఒకవేళ ( configENABLE_PAC == 1 )
        {
            uint32_t ul_Task_Pac_కీలకం[ 4 ], i;

            v_Application_Generate_Task_Random_Pac_కీలకం( &( ul_Task_Pac_కీలకం[ 0 ] ) );

            కొరకు( i = 0; i < 4; i++ )
            {
                xMPUSettings->ulContext[ ul_సూచీ ] = ul_Task_Pac_కీలకం[ i ];
                ul_సూచీ++;
            }
        }
        #అయితే_ముగింపు /* configENABLE_PAC */

        తిరిగి &( xMPUSettings->ulContext[ ul_సూచీ ] );
    }

#లేకపోతే /* configENABLE_MPU */

    దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                         దొంతర_Type_t * px_చివర_యొక్క_దొంతర,
                                         TaskFunction_t px_సంకేతం,
                                         శూన్య * pvParameters ) /* PRIVILEGED_FUNCTION */
    {
        /* Simulate the stack frame as it would be created by a context switch
         * interrupt. */
        #ఒకవేళ ( పోర్టు_PRELOAD_REGISTERS == 0 )
        {
            px_శిఖరం_యొక్క_దొంతర--; /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_XPSR; /* xPSR. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం; /* PC. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_TASK_RETURN_చిరునామా; /* LR. */
            px_శిఖరం_యొక్క_దొంతర -= 5; /* R12, R3, R2 and R1. */
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters; /* R0. */
            px_శిఖరం_యొక్క_దొంతర -= 9; /* R11..R4, EXC_RETURN. */
            *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_EXC_RETURN;
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_చివర_యొక్క_దొంతర; /* Slot used to hold this task's PSPLIM value. */

            #ఒకవేళ ( configENABLE_TRUSTZONE == 1 )
            {
                px_శిఖరం_యొక్క_దొంతర--;
                *px_శిఖరం_యొక్క_దొంతర = పోర్టు_NO_SECURE_CONTEXT; /* Slot used to hold this task's xSecureContext value. */
            }
            #అయితే_ముగింపు /* configENABLE_TRUSTZONE */
        }
        #లేకపోతే /* portPRELOAD_REGISTERS */
        {
            px_శిఖరం_యొక్క_దొంతర--; /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_XPSR; /* xPSR. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం; /* PC. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_TASK_RETURN_చిరునామా; /* LR. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x12121212UL; /* R12. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x03030303UL; /* R3. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x02020202UL; /* R2. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x01010101UL; /* R1. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters; /* R0. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x11111111UL; /* R11. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x10101010UL; /* R10. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x09090909UL; /* R09. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x08080808UL; /* R08. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x07070707UL; /* R07. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x06060606UL; /* R06. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x05050505UL; /* R05. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x04040404UL; /* R04. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_EXC_RETURN; /* EXC_RETURN. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_చివర_యొక్క_దొంతర; /* Slot used to hold this task's PSPLIM value. */

            #ఒకవేళ ( configENABLE_TRUSTZONE == 1 )
            {
                px_శిఖరం_యొక్క_దొంతర--;
                *px_శిఖరం_యొక్క_దొంతర = పోర్టు_NO_SECURE_CONTEXT; /* Slot used to hold this task's xSecureContext value. */
            }
            #అయితే_ముగింపు /* configENABLE_TRUSTZONE */
        }
        #అయితే_ముగింపు /* portPRELOAD_REGISTERS */

        #ఒకవేళ ( configENABLE_PAC == 1 )
        {
            uint32_t ul_Task_Pac_కీలకం[ 4 ], i;

            v_Application_Generate_Task_Random_Pac_కీలకం( &( ul_Task_Pac_కీలకం[ 0 ] ) );

            కొరకు( i = 0; i < 4; i++ )
            {
                px_శిఖరం_యొక్క_దొంతర--;
                *px_శిఖరం_యొక్క_దొంతర = ul_Task_Pac_కీలకం[ i ];
            }
        }
        #అయితే_ముగింపు /* configENABLE_PAC */

        తిరిగి px_శిఖరం_యొక్క_దొంతర;
    }

#అయితే_ముగింపు /* configENABLE_MPU */
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య ) /* PRIVILEGED_FUNCTION */
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
    #ఒకవేళ ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        స్థిరరాశి పోర్టు_ISR_t * స్థిరరాశి px_సదిశ_పట్టిక = పోర్టు_SCB_VTOR_REG;

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
        configASSERT( px_సదిశ_పట్టిక[ పోర్టు_సదిశ_సూచీ_SVC ] == SVC_Handler );
        configASSERT( px_సదిశ_పట్టిక[ పోర్టు_సదిశ_సూచీ_PENDSV ] == PendSV_Handler );
    }
    #అయితే_ముగింపు /* configCHECK_HANDLER_INSTALLATION */

    v_పోర్టు_Configure_అంతరాయం_Priorities();

    #ఒకవేళ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
    {
        /* Set the CONTROL register value based on PACBTI security feature
         * configuration before starting the first task. */
        #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
            ( శూన్య ) prvConfigurePACBTI( pdTRUE );
        #లేకపోతే /* configNUMBER_OF_CORES > 1 */
            ( శూన్య ) vConfigurePACBTI( pdTRUE );
        #అయితే_ముగింపు /* configNUMBER_OF_CORES */
    }
    #అయితే_ముగింపు /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

    #ఒకవేళ ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        prv_అమరిక_MPU();
    }
    #అయితే_ముగింపు /* configENABLE_MPU */

    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )
        /* Start the timer that generates the tick ISR. Interrupts are disabled
         * here already. */
        v_పోర్టు_అమరిక_Timer_అంతరాయం();
        /* Initialize the critical nesting count for all cores. */
        కొరకు ( uint8_t ucCoreID = 0; ucCoreID < config_సంఖ్య_యొక్క_CORES; ucCoreID++ )
        {
            ulCriticalNestings[ ucCoreID ] = 0;
        }
        /* Signal that primary core has done all the necessary initialisations. */
        uc_Primary_Core_Init_పూర్తి_Flag = 1;
        /* Wake up secondary cores */
        పునాది_Type_t x_Wake_ఫలితం = configWAKE_SECONDARY_CORES();
        configASSERT( x_Wake_ఫలితం == pdTRUE );

        /* Hold the primary core here until all the secondary cores are ready, this would be achieved only when
         * all elements of ucSecondaryCoresReadyFlags are set.
         */
        అయితే( 1 )
        {
            పునాది_Type_t xAllCoresReady = pdTRUE;
            కొరకు( uint8_t ucCoreID = 0; ucCoreID < ( config_సంఖ్య_యొక్క_CORES - 1 ); ucCoreID++ )
            {
                ఒకవేళ( ucSecondaryCoresReadyFlags[ ucCoreID ] != pdTRUE )
                {
                    xAllCoresReady = pdFALSE;
                    ఆపు;
                }
                }

            ఒకవేళ ( xAllCoresReady == pdTRUE )
            {
                ఆపు;
            }
        }
    #లేకపోతే /* if ( configNUMBER_OF_CORES > 1 ) */
        /* Start the timer that generates the tick ISR. */
        v_పోర్టు_అమరిక_Timer_అంతరాయం();
        /* Initialize the critical nesting count ready for the first task. */
        ulCriticalNesting = 0;
    #అయితే_ముగింపు /* if ( configNUMBER_OF_CORES > 1 ) */

    #ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )
    {
        xSchedulerRunning = pdTRUE;
    }
    #అయితే_ముగింపు /* ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

    /* Start the first task. */
    v_ప్రారంభం_మొదటి_Task();

    /* Should never get here as the tasks will now be executing. Call the task
     * exit error function to prevent compiler warnings about a static function
     * not being called in the case that the application writer overrides this
     * functionality by defining configTASK_RETURN_ADDRESS. Call
     * vTaskSwitchContext() so link time optimization does not remove the
     * symbol. */
    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )
        vTaskSwitchContext( పోర్టు_GET_CORE_ID() );
    #లేకపోతే
        vTaskSwitchContext();
    #అయితే_ముగింపు
    prvTaskExitError();

    /* Should not get here. */
    తిరిగి 0;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య ) /* PRIVILEGED_FUNCTION */
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
        configASSERT( ulCriticalNesting == 1000UL );
    #లేకపోతే /* if ( configNUMBER_OF_CORES == 1 ) */
        configASSERT( ulCriticalNestings[ పోర్టు_GET_CORE_ID() ] == 1000UL );
    #అయితే_ముగింపు /* if ( configNUMBER_OF_CORES == 1 ) */
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( configENABLE_MPU == 1 )

    శూన్య v_పోర్టు_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    స్థిరరాశి నిర్మాణం x_జ్ఞాపకం_REGION * స్థిరరాశి xRegions,
                                    దొంతర_Type_t * px_Bottom_యొక్క_దొంతర,
                                    config_దొంతర_లోతు_TYPE ux_దొంతర_లోతు )
    {
        uint32_t ul_Region_ప్రారంభం_చిరునామా, ul_Region_చివర_చిరునామా, ul_Region_సంఖ్య;
        int32_t l_సూచీ = 0;

        #ఒకవేళ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            బాహ్య uint32_t * __privileged_sram_start__;
            బాహ్య uint32_t * __privileged_sram_end__;
        #లేకపోతే
            /* Declaration when these variable are exported from linker scripts. */
            బాహ్య uint32_t __privileged_sram_start__[];
            బాహ్య uint32_t __privileged_sram_end__[];
        #అయితే_ముగింపు /* defined( __ARMCC_VERSION ) */

        /* Setup MAIR0. */
        xMPUSettings->ulMAIR0 = ( ( పోర్టు_MPU_సాధారణ_జ్ఞాపకం_BUFFERABLE_CACHEABLE << పోర్టు_MPU_MAIR_ATTR0_POS ) & పోర్టు_MPU_MAIR_ATTR0_ముసుగు );
        xMPUSettings->ulMAIR0 |= ( ( పోర్టు_MPU_DEVICE_జ్ఞాపకం_n_Gn_RE << పోర్టు_MPU_MAIR_ATTR1_POS ) & పోర్టు_MPU_MAIR_ATTR1_ముసుగు );

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid.  At all other
         * times the stack parameters will not be valid and it is assumed that
         * the stack region has already been configured. */
        ఒకవేళ( ux_దొంతర_లోతు > 0 )
        {
            ul_Region_ప్రారంభం_చిరునామా = ( uint32_t ) px_Bottom_యొక్క_దొంతర;
            ul_Region_చివర_చిరునామా = ( uint32_t ) px_Bottom_యొక్క_దొంతర + ( ux_దొంతర_లోతు * ( config_దొంతర_లోతు_TYPE ) పరిమాణం( దొంతర_Type_t ) ) - 1;

            /* If the stack is within the privileged SRAM, do not protect it
             * using a separate MPU region. This is needed because privileged
             * SRAM is already protected using an MPU region and ARMv8-M does
             * not allow overlapping MPU regions. */
            ఒకవేళ( ( ul_Region_ప్రారంభం_చిరునామా >= ( uint32_t ) __privileged_sram_start__ ) &&
                ( ul_Region_చివర_చిరునామా <= ( uint32_t ) __privileged_sram_end__ ) )
            {
                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR = 0;
                xMPUSettings->xRegionsSettings[ 0 ].ulRLAR = 0;
            }
            లేకపోతే
            {
                /* Define the region that allows access to the stack. */
                ul_Region_ప్రారంభం_చిరునామా &= పోర్టు_MPU_RBAR_చిరునామా_ముసుగు;
                ul_Region_చివర_చిరునామా &= పోర్టు_MPU_RLAR_చిరునామా_ముసుగు;

                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR = ( ul_Region_ప్రారంభం_చిరునామా ) |
                                                             ( పోర్టు_MPU_REGION_NON_SHAREABLE ) |
                                                             ( పోర్టు_MPU_REGION_READ_WRITE ) |
                                                             ( పోర్టు_MPU_REGION_EXECUTE_NEVER );

                xMPUSettings->xRegionsSettings[ 0 ].ulRLAR = ( ul_Region_చివర_చిరునామా ) |
                                                             ( పోర్టు_MPU_RLAR_ATTR_INDEX0 ) |
                                                             ( పోర్టు_MPU_RLAR_REGION_ENABLE );
            }
        }

        /* User supplied configurable regions. */
        కొరకు( ul_Region_సంఖ్య = 1; ul_Region_సంఖ్య <= పోర్టు_అంకె_CONFIGURABLE_REGIONS; ul_Region_సంఖ్య++ )
        {
            /* If xRegions is NULL i.e. the task has not specified any MPU
             * region, the else part ensures that all the configurable MPU
             * regions are invalidated. */
            ఒకవేళ( ( xRegions != ఖాళీ ) && ( xRegions[ l_సూచీ ].ul_నిడివి_లోపల_బైట్లు > 0UL ) )
            {
                /* Translate the generic region definition contained in xRegions
                 * into the ARMv8 specific MPU settings that are then stored in
                 * xMPUSettings. */
                ul_Region_ప్రారంభం_చిరునామా = ( ( uint32_t ) xRegions[ l_సూచీ ].pv_పునాది_చిరునామా ) & పోర్టు_MPU_RBAR_చిరునామా_ముసుగు;
                ul_Region_చివర_చిరునామా = ( uint32_t ) xRegions[ l_సూచీ ].pv_పునాది_చిరునామా + xRegions[ l_సూచీ ].ul_నిడివి_లోపల_బైట్లు - 1;
                ul_Region_చివర_చిరునామా &= పోర్టు_MPU_RLAR_చిరునామా_ముసుగు;

                /* Start address. */
                xMPUSettings->xRegionsSettings[ ul_Region_సంఖ్య ].ulRBAR = ( ul_Region_ప్రారంభం_చిరునామా ) |
                                                                          ( పోర్టు_MPU_REGION_NON_SHAREABLE );

                /* RO/RW. */
                ఒకవేళ( ( xRegions[ l_సూచీ ].ulParameters & tskMPU_REGION_READ_ONLY ) != 0 )
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_సంఖ్య ].ulRBAR |= ( పోర్టు_MPU_REGION_READ_ONLY );
                }
                లేకపోతే
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_సంఖ్య ].ulRBAR |= ( పోర్టు_MPU_REGION_READ_WRITE );
                }

                /* XN. */
                ఒకవేళ( ( xRegions[ l_సూచీ ].ulParameters & tskMPU_REGION_EXECUTE_NEVER ) != 0 )
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_సంఖ్య ].ulRBAR |= ( పోర్టు_MPU_REGION_EXECUTE_NEVER );
                }

                /* End Address. */
                xMPUSettings->xRegionsSettings[ ul_Region_సంఖ్య ].ulRLAR = ( ul_Region_చివర_చిరునామా ) |
                                                                          ( పోర్టు_MPU_RLAR_REGION_ENABLE );

                /* PXN. */
                #ఒకవేళ ( పోర్టు_ARMV8_M_MINOR_సంస్కరణ >= 1 )
                {
                    ఒకవేళ( ( xRegions[ l_సూచీ ].ulParameters & tskMPU_REGION_PRIVILEGED_EXECUTE_NEVER ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ ul_Region_సంఖ్య ].ulRLAR |= ( పోర్టు_MPU_RLAR_PRIVILEGED_EXECUTE_NEVER );
                    }
                }
                #అయితే_ముగింపు /* portARMV8M_MINOR_VERSION >= 1 */

                /* Normal memory/ Device memory. */
                ఒకవేళ( ( xRegions[ l_సూచీ ].ulParameters & tsk_MPU_REGION_DEVICE_జ్ఞాపకం ) != 0 )
                {
                    /* Attr1 in MAIR0 is configured as device memory. */
                    xMPUSettings->xRegionsSettings[ ul_Region_సంఖ్య ].ulRLAR |= పోర్టు_MPU_RLAR_ATTR_INDEX1;
                }
                లేకపోతే
                {
                    /* Attr0 in MAIR0 is configured as normal memory. */
                    xMPUSettings->xRegionsSettings[ ul_Region_సంఖ్య ].ulRLAR |= పోర్టు_MPU_RLAR_ATTR_INDEX0;
                }
            }
            లేకపోతే
            {
                /* Invalidate the region. */
                xMPUSettings->xRegionsSettings[ ul_Region_సంఖ్య ].ulRBAR = 0UL;
                xMPUSettings->xRegionsSettings[ ul_Region_సంఖ్య ].ulRLAR = 0UL;
            }

            l_సూచీ++;
        }
    }

#అయితే_ముగింపు /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    పునాది_Type_t x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( స్థిరరాశి శూన్య * pv_బఫరు,
                                                size_t x_బఫరు_నిడివి,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_బఫరు_ప్రారంభం_చిరునామా, ul_బఫరు_చివర_చిరునామా;
        పునాది_Type_t xAccessGranted = pdFALSE;
        స్థిరరాశి xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ఖాళీ ); /* Calling task's MPU settings. */

        ఒకవేళ( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        లేకపోతే ఒకవేళ( ( xTaskMpuSettings->ulTaskFlags & పోర్టు_TASK_IS_PRIVILEGED_FLAG ) == పోర్టు_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        లేకపోతే
        {
            ఒకవేళ( పోర్టు_కూడు_UINT32_WILL_అధికప్రవాహం( ( ( uint32_t ) pv_బఫరు ), ( ( uint32_t ) x_బఫరు_నిడివి - 1UL ) ) == pdFALSE )
            {
                ul_బఫరు_ప్రారంభం_చిరునామా = ( uint32_t ) pv_బఫరు;
                ul_బఫరు_చివర_చిరునామా = ( ( ( uint32_t ) pv_బఫరు ) + ( uint32_t ) x_బఫరు_నిడివి - 1UL );

                కొరకు( i = 0; i < పోర్టు_మొత్తం_అంకె_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    ఒకవేళ( ( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR & పోర్టు_MPU_RLAR_REGION_ENABLE ) == పోర్టు_MPU_RLAR_REGION_ENABLE )
                    {
                        ఒకవేళ( పోర్టు_IS_చిరునామా_WITHIN_RANGE( ul_బఫరు_ప్రారంభం_చిరునామా,
                                                         పోర్టు_వెలికితీయి_మొదటి_చిరునామా_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ),
                                                         పోర్టు_వెలికితీయి_చివరి_చిరునామా_FROM_RLAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR ) ) &&
                            పోర్టు_IS_చిరునామా_WITHIN_RANGE( ul_బఫరు_చివర_చిరునామా,
                                                         పోర్టు_వెలికితీయి_మొదటి_చిరునామా_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ),
                                                         పోర్టు_వెలికితీయి_చివరి_చిరునామా_FROM_RLAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR ) ) &&
                            పోర్టు_IS_AUTHORIZED( ulAccessRequested,
                                               prvGetRegionAccessPermissions( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ) ) )
                        {
                            xAccessGranted = pdTRUE;
                            ఆపు;
                        }
                    }
                }
            }
        }

        తిరిగి xAccessGranted;
    }

#అయితే_ముగింపు /* #if ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_Is_Inside_అంతరాయం( శూన్య )
{
    uint32_t ul_Current_అంతరాయం;
    పునాది_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. Interrupt Program
     * Status Register (IPSR) holds the exception number of the currently-executing
     * exception or zero for Thread mode.*/
    __asm అస్థిర ( "mrs %0, ipsr" : "=r" ( ul_Current_అంతరాయం )::"memory" );

    ఒకవేళ( ul_Current_అంతరాయం == 0 )
    {
        xReturn = pdFALSE;
    }
    లేకపోతే
    {
        xReturn = pdTRUE;
    }

    తిరిగి xReturn;
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configASSERT_DEFINED == 1 ) && ( పోర్టు_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) )

    శూన్య v_పోర్టు_Validate_అంతరాయం_ప్రాధాన్యత( శూన్య )
    {
        uint32_t ul_Current_అంతరాయం;
        uint8_t uc_Current_ప్రాధాన్యత;

        /* Obtain the number of the currently executing interrupt. */
        __asm అస్థిర ( "mrs %0, ipsr" : "=r" ( ul_Current_అంతరాయం )::"memory" );

        /* Is the interrupt number a user defined interrupt? */
        ఒకవేళ( ul_Current_అంతరాయం >= పోర్టు_మొదటి_USER_అంతరాయం_సంఖ్య )
        {
            /* Look up the interrupt's priority. */
            uc_Current_ప్రాధాన్యత = pc_అంతరాయం_ప్రాధాన్యత_Registers[ ul_Current_అంతరాయం ];

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
            configASSERT( uc_Current_ప్రాధాన్యత >= uc_Max_Sys_Call_ప్రాధాన్యత );
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
        configASSERT( ( పోర్టు_AIRCR_REG & పోర్టు_ప్రాధాన్యత_సమూహం_ముసుగు ) <= ulMaxPRIGROUPValue );
    }

#అయితే_ముగింపు /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Configure_అంతరాయం_Priorities( శూన్య ) /* PRIVILEGED_FUNCTION */
{
    #ఒకవేళ ( ( configASSERT_DEFINED == 1 ) && ( పోర్టు_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) )
    {
        అస్థిర uint32_t ul_Implemented_Prio_బిట్లు = 0;
        అస్థిర uint8_t uc_Max_ప్రాధాన్యత_విలువ;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
        * functions can be called. ISR safe functions are those that end in
        * "FromISR". FreeRTOS maintains separate thread and ISR API functions to
        * ensure interrupt entry is as fast and simple as possible.
        *
        * First, determine the number of priority bits available. Write to all
        * possible bits in the priority setting for SVCall. */
        పోర్టు_NVIC_SHPR2_REG = 0xFF000000;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ప్రాధాన్యత_విలువ = ( uint8_t ) ( ( పోర్టు_NVIC_SHPR2_REG & 0xFF000000 ) >> 24 );

        /* Use the same mask on the maximum system call priority. */
        uc_Max_Sys_Call_ప్రాధాన్యత = config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత & uc_Max_ప్రాధాన్యత_విలువ;

        /* Check that the maximum system call priority is nonzero after
        * accounting for the number of priority bits supported by the
        * hardware. A priority of 0 is invalid because setting the BASEPRI
        * register to 0 unmasks all interrupts, and interrupts with priority 0
        * cannot be masked using BASEPRI.
        * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( uc_Max_Sys_Call_ప్రాధాన్యత );

        /* Check that the bits not implemented in hardware are zero in
        * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత & ( uint8_t ) ( ~( uint32_t ) uc_Max_ప్రాధాన్యత_విలువ ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
        * of bits read back. */
        అయితే( ( uc_Max_ప్రాధాన్యత_విలువ & పోర్టు_శిఖరం_బిట్టు_యొక్క_BYTE ) == పోర్టు_శిఖరం_బిట్టు_యొక్క_BYTE )
        {
            ul_Implemented_Prio_బిట్లు++;
            uc_Max_ప్రాధాన్యత_విలువ <<= ( uint8_t ) 0x01;
        }

        ఒకవేళ( ul_Implemented_Prio_బిట్లు == 8 )
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
            configASSERT( ( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        లేకపోతే
        {
            ulMaxPRIGROUPValue = పోర్టు_MAX_PRIGROUP_బిట్లు - ul_Implemented_Prio_బిట్లు;
        }

        /* Shift the priority group value back to its position within the AIRCR
        * register. */
        ulMaxPRIGROUPValue <<= పోర్టు_PRIGROUP_జరుపు;
        ulMaxPRIGROUPValue &= పోర్టు_ప్రాధాన్యత_సమూహం_ముసుగు;
    }
    #అయితే_ముగింపు /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */

    /* Make PendSV and SysTick the lowest priority interrupts, and make SVCall
    * the highest priority. */
    పోర్టు_NVIC_SHPR3_REG |= పోర్టు_NVIC_PENDSV_PRI;
    పోర్టు_NVIC_SHPR3_REG |= పోర్టు_NVIC_SYSTICK_PRI;
    పోర్టు_NVIC_SHPR2_REG = 0;
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    శూన్య v_పోర్టు_Grant_Access_గమ్యం_Kernel_Object( TaskHandle_t x_అంతర్గత_Task_Handle,
                                         int32_t l_అంతర్గత_సూచీ_యొక్క_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_నమోదు_సూచీ, ul_Access_Control_List_నమోదు_బిట్టు;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_నమోదు_సూచీ = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object / పోర్టు_ACL_నమోదు_కొలత_బిట్లు );
        ul_Access_Control_List_నమోదు_బిట్టు = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object % పోర్టు_ACL_నమోదు_కొలత_బిట్లు );

        xTaskMpuSettings = xTaskGetMPUSettings( x_అంతర్గత_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_నమోదు_సూచీ ] |= ( 1U << ul_Access_Control_List_నమోదు_బిట్టు );
    }

#అయితే_ముగింపు /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    శూన్య v_పోర్టు_Revoke_Access_గమ్యం_Kernel_Object( TaskHandle_t x_అంతర్గత_Task_Handle,
                                          int32_t l_అంతర్గత_సూచీ_యొక్క_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_నమోదు_సూచీ, ul_Access_Control_List_నమోదు_బిట్టు;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_నమోదు_సూచీ = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object / పోర్టు_ACL_నమోదు_కొలత_బిట్లు );
        ul_Access_Control_List_నమోదు_బిట్టు = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object % పోర్టు_ACL_నమోదు_కొలత_బిట్లు );

        xTaskMpuSettings = xTaskGetMPUSettings( x_అంతర్గత_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_నమోదు_సూచీ ] &= ~( 1U << ul_Access_Control_List_నమోదు_బిట్టు );
    }

#అయితే_ముగింపు /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #ఒకవేళ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        పునాది_Type_t x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( int32_t l_అంతర్గత_సూచీ_యొక్క_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_నమోదు_సూచీ, ul_Access_Control_List_నమోదు_బిట్టు;
            పునాది_Type_t xAccessGranted = pdFALSE;
            స్థిరరాశి xMPU_SETTINGS * xTaskMpuSettings;

            ఒకవేళ( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            లేకపోతే
            {
                xTaskMpuSettings = xTaskGetMPUSettings( ఖాళీ ); /* Calling task's MPU settings. */

                ul_Access_Control_List_నమోదు_సూచీ = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object / పోర్టు_ACL_నమోదు_కొలత_బిట్లు );
                ul_Access_Control_List_నమోదు_బిట్టు = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object % పోర్టు_ACL_నమోదు_కొలత_బిట్లు );

                ఒకవేళ( ( xTaskMpuSettings->ulTaskFlags & పోర్టు_TASK_IS_PRIVILEGED_FLAG ) == పోర్టు_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                లేకపోతే
                {
                    ఒకవేళ( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_నమోదు_సూచీ ] & ( 1U << ul_Access_Control_List_నమోదు_బిట్టు ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            తిరిగి xAccessGranted;
        }

    #లేకపోతే /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        పునాది_Type_t x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( int32_t l_అంతర్గత_సూచీ_యొక్క_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( శూన్య ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            తిరిగి pdTRUE;
        }

    #అయితే_ముగింపు /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#అయితే_ముగింపు /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
        స్థిర uint32_t prvConfigurePACBTI( పునాది_Type_t x_Write_Control_రిజిస్టరు )
    #లేకపోతే /* configNUMBER_OF_CORES > 1 */
        uint32_t vConfigurePACBTI( పునాది_Type_t x_Write_Control_రిజిస్టరు )
    #అయితే_ముగింపు /* configNUMBER_OF_CORES */
        {
            uint32_t ulControl = 0x0;

            /* Ensure that PACBTI is implemented. */
            configASSERT( పోర్టు_ID_ISAR5_REG != 0x0 );

            /* Enable UsageFault exception. */
            పోర్టు_SCB_SYS_HANDLER_CTRL_STATE_REG |= పోర్టు_SCB_USG_FAULT_ENABLE_బిట్టు;

            #ఒకవేళ ( configENABLE_PAC == 1 )
            {
                ulControl |= ( పోర్టు_CONTROL_UPAC_EN | పోర్టు_CONTROL_PAC_EN );
            }
            #అయితే_ముగింపు

            #ఒకవేళ ( configENABLE_BTI == 1 )
            {
                ulControl |= ( పోర్టు_CONTROL_UBTI_EN | పోర్టు_CONTROL_BTI_EN );
            }
            #అయితే_ముగింపు

            ఒకవేళ( x_Write_Control_రిజిస్టరు == pdTRUE )
            {
                __asm అస్థిర ( "msr control, %0" : : "r" ( ulControl ) );
            }

            తిరిగి ulControl;
        }

#అయితే_ముగింపు /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )

    /* Which core owns the lock? */
    PRIVILEGED_దత్తాంశం అస్థిర uint32_t ulOwnedByCore[ పోర్టు_MAX_CORE_లెక్క ];
    /* Lock count a core owns. */
    PRIVILEGED_దత్తాంశం అస్థిర uint32_t ul_Recursion_లెక్క_By_తాళం[ e_తాళం_లెక్క ];
    /* Index 0 is used for ISR lock and Index 1 is used for task lock. */
    PRIVILEGED_దత్తాంశం అస్థిర uint32_t ul_Gate_మాట[ e_తాళం_లెక్క ];

    __attribute__((weak)) శూన్య v_అంతరాయం_Core( uint8_t ucCoreID )
    {
        /* Default weak stub - platform specific implementation may override. */
        ( శూన్య ) ucCoreID;
    }

/*-----------------------------------------------------------*/

    స్థిర అంతఃవరుస శూన్య prvSpinUnlock( అస్థిర uint32_t * ul_తాళం )
    {
        /* Conservative unlock: preserve original barriers for broad HW/FVP. */
        __asm అస్థిర (
            "dmb sy         \n"
            "mov r1, #0     \n"
            "str r1, [%0]   \n"
            "sev            \n"
            "dsb            \n"
            "isb            \n"
            :
            : "r" ( ul_తాళం )
            : "memory", "r1"
        );
    }

/*-----------------------------------------------------------*/

    స్థిర అంతఃవరుస uint32_t prvSpinTrylock( అస్థిర uint32_t * ul_తాళం )
    {
        /*
         * Conservative ldrex/strex trylock:
         * - Return 1 immediately if busy, clearing exclusive state (CLREX).
         * - Retry strex only on spurious failure when observed free.
         * - DMB on success to preserve expected acquire semantics.
         */
        uint32_t ulVal;
        uint32_t ul_స్థితి;

        __asm అస్థిర (
            " ldrex %0, [%1]   \n"
            : "=r" ( ulVal )
            : "r" ( ul_తాళం )
            : "memory"
        );

        ఒకవేళ( ulVal != 0U )
        {
            __asm అస్థిర ("clrex" ::: "memory");
            తిరిగి 1U;
        }

        __asm అస్థిర (
            " strex %0, %2, [%1]   \n"
            : "=&r" ( ul_స్థితి )
            : "r" ( ul_తాళం ), "r" (1U)
            : "memory"
        );

        ఒకవేళ( ul_స్థితి != 0U )
        {
            తిరిగి 1U;
        }
        __asm అస్థిర ( "dmb" ::: "memory" );
        తిరిగి 0U;
    }


/*-----------------------------------------------------------*/

    /* Read 32b value shared between cores. */
    స్థిర అంతఃవరుస uint32_t prvGet32( అస్థిర uint32_t * x )
    {
        __asm( "dsb" );
        తిరిగి *x;
    }

/*-----------------------------------------------------------*/

    /* Write 32b value shared between cores. */
    స్థిర అంతఃవరుస శూన్య prvSet32( అస్థిర uint32_t * x,
                                 uint32_t విలువ )
    {
        *x = విలువ;
        __asm( "dsb" );
    }

/*-----------------------------------------------------------*/

    శూన్య v_పోర్టు_Recursive_తాళం( uint8_t ucCoreID,
                             e_పోర్టు_RTOSLock e_తాళం_అంకె,
                             పునాది_Type_t uxAcquire )
    {
        /* Validate the core ID and lock number. */
        configASSERT( ucCoreID < పోర్టు_MAX_CORE_లెక్క );
        configASSERT( e_తాళం_అంకె < e_తాళం_లెక్క );

        uint32_t ul_తాళం_బిట్టు = 1u << e_తాళం_అంకె;

        /* Lock acquire */
        ఒకవేళ( uxAcquire )
        {
            /* Check if spinlock is available. */
            /* If spinlock is not available check if the core owns the lock. */
            /* If the core owns the lock wait increment the lock count by the core. */
            /* If core does not own the lock wait for the spinlock. */
            ఒకవేళ( prvSpinTrylock( &ul_Gate_మాట[ e_తాళం_అంకె ] ) != 0 )
            {
                /* Check if the core owns the spinlock. */
                ఒకవేళ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ul_తాళం_బిట్టు )
                {
                    configASSERT( prvGet32( &ul_Recursion_లెక్క_By_తాళం[ e_తాళం_అంకె ] ) != పోర్టు_UINT32_MAX );
                    prvSet32( &ul_Recursion_లెక్క_By_తాళం[ e_తాళం_అంకె ], ( prvGet32( &ul_Recursion_లెక్క_By_తాళం[ e_తాళం_అంకె ] ) + 1 ) );
                    తిరిగి;
                }

                /* Preload the gate word into the cache. */
                uint32_t dummy = ul_Gate_మాట[ e_తాళం_అంకె ];
                dummy++;

                అయితే( prvSpinTrylock( &ul_Gate_మాట[ e_తాళం_అంకె ] ) != 0 )
                {
                    __asm అస్థిర ( "wfe" );
                }
            }

            /* Add barrier to ensure lock is taken before we proceed. */
            __asm అస్థిర( "dmb sy" ::: "memory" );

            /* Assert the lock count is 0 when the spinlock is free and is acquired. */
            configASSERT( prvGet32( &ul_Recursion_లెక్క_By_తాళం[ e_తాళం_అంకె ] ) == 0 );

            /* Set lock count as 1. */
            prvSet32( &ul_Recursion_లెక్క_By_తాళం[ e_తాళం_అంకె ], 1 );
            /* Set ulOwnedByCore. */
            prvSet32( &ulOwnedByCore[ ucCoreID ], ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) | ul_తాళం_బిట్టు ) );
        }
        /* Lock release. */
        లేకపోతే
        {
            /* Assert the lock is not free already. */
            configASSERT( ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ul_తాళం_బిట్టు ) != 0 );
            configASSERT( prvGet32( &ul_Recursion_లెక్క_By_తాళం[ e_తాళం_అంకె ] ) != 0 );

            /* Reduce ulRecursionCountByLock by 1. */
            prvSet32( &ul_Recursion_లెక్క_By_తాళం[ e_తాళం_అంకె ], ( prvGet32( &ul_Recursion_లెక్క_By_తాళం[ e_తాళం_అంకె ] ) - 1 ) );

            ఒకవేళ( !prvGet32( &ul_Recursion_లెక్క_By_తాళం[ e_తాళం_అంకె ] ) )
            {
                prvSet32( &ulOwnedByCore[ ucCoreID ], ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ~ul_తాళం_బిట్టు ) );
                prvSpinUnlock( &ul_Gate_మాట[ e_తాళం_అంకె ] );
                /* Add barrier to ensure lock status is reflected before we proceed. */
                __asm అస్థిర( "dmb sy" ::: "memory" );
            }
        }
    }

/*-----------------------------------------------------------*/

    uint8_t uc_పోర్టు_Get_Core_ID( శూన్య )
    {
        తిరిగి *(అస్థిర uint8_t *)(config_CORE_ID_రిజిస్టరు);
    }

/*-----------------------------------------------------------*/

#అయితే_ముగింపు /* if( configNUMBER_OF_CORES > 1 ) */
