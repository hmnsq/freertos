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
#تعریف_کرو MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* MPU includes. */
#ضمن "mpu_wrappers.h"
#ضمن "mpu_syscall_numbers.h"

/* Portasm includes. */
#ضمن "portasm.h"

#إذا ( configENABLE_TRUSTZONE == 1 )
    /* Secure components includes. */
    #ضمن "secure_context.h"
    #ضمن "secure_init.h"
#جے_انت /* configENABLE_TRUSTZONE */

#تعریف_رد MPU_WRAPPERS_INCLUDED_FROM_API_FILE

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
#إذا ( ( config_لگاتار_FREERTOS_SECURE_ONLY == 1 ) && ( configENABLE_TRUSTZONE == 1 ) )
    #غلطی TrustZone needs منزل be disabled وچ ترتیب منزل لگاتار FreeRTOS on the Secure Side.
#جے_انت

/**
 * Cortex-M23 does not have non-secure PSPLIM. We should use PSPLIM on Cortex-M23
 * only when FreeRTOS runs on secure side.
 */
#إذا ( ( پورٹ_HAS_ARMV8_M_MAIN_EXTENSION == 0 ) && ( config_لگاتار_FREERTOS_SECURE_ONLY == 0 ) )
    #تعریف_کرو پورٹ_USE_PSPLIM_رجسٹر    0
#وإلا
    #تعریف_کرو پورٹ_USE_PSPLIM_رجسٹر    1
#جے_انت
/*-----------------------------------------------------------*/

/**
 * @brief Prototype of all Interrupt Service Routines (ISRs).
 */
تعريفنوع فراغ ( * پورٹ_ISR_t )( فراغ );
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the NVIC.
 */
#تعریف_کرو پورٹ_NVIC_SYSTICK_CTRL_REG             ( *( ( متطاير uint32_t * ) 0xe000e010 ) )
#تعریف_کرو پورٹ_NVIC_SYSTICK_لدو_REG             ( *( ( متطاير uint32_t * ) 0xe000e014 ) )
#تعریف_کرو پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG    ( *( ( متطاير uint32_t * ) 0xe000e018 ) )
#تعریف_کرو پورٹ_NVIC_SHPR3_REG                    ( *( ( متطاير uint32_t * ) 0xe000ed20 ) )
#تعریف_کرو پورٹ_NVIC_SYSTICK_ENABLE_ثنائی_ہندسہ           ( 1UL << 0UL )
#تعریف_کرو پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ              ( 1UL << 1UL )
#تعریف_کرو پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ              ( 1UL << 2UL )
#تعریف_کرو پورٹ_NVIC_SYSTICK_گنتی_FLAG_ثنائی_ہندسہ       ( 1UL << 16UL )
#تعریف_کرو پورٹ_NVIC_PEND_SYSTICK_CLEAR_ثنائی_ہندسہ       ( 1UL << 25UL )
#تعریف_کرو پورٹ_NVIC_PEND_SYSTICK_سیٹ_ثنائی_ہندسہ         ( 1UL << 26UL )
#تعریف_کرو پورٹ_MIN_رکاوٹ_ترجیح            ( 255UL )
#تعریف_کرو پورٹ_NVIC_PENDSV_PRI                   ( پورٹ_MIN_رکاوٹ_ترجیح << 16UL )
#تعریف_کرو پورٹ_NVIC_SYSTICK_PRI                  ( پورٹ_MIN_رکاوٹ_ترجیح << 24UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the SCB.
 */
#تعریف_کرو پورٹ_SCB_VTOR_REG                      ( *( ( پورٹ_ISR_t ** ) 0xe000ed08 ) )
#تعریف_کرو پورٹ_SCB_SYS_HANDLER_CTRL_STATE_REG    ( *( ( متطاير uint32_t * ) 0xe000ed24 ) )
#تعریف_کرو پورٹ_SCB_MEM_FAULT_ENABLE_ثنائی_ہندسہ          ( 1UL << 16UL )
#تعریف_کرو پورٹ_SCB_USG_FAULT_ENABLE_ثنائی_ہندسہ          ( 1UL << 18UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants used to check the installation of the FreeRTOS interrupt handlers.
 */
#تعریف_کرو پورٹ_سمتیہ_اشاریہ_SVC       ( 11 )
#تعریف_کرو پورٹ_سمتیہ_اشاریہ_PENDSV    ( 14 )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to check the validity of an interrupt priority.
 */
#تعریف_کرو پورٹ_NVIC_SHPR2_REG                 ( *( ( متطاير uint32_t * ) 0xE000ED1C ) )
#تعریف_کرو پورٹ_پہلا_USER_رکاوٹ_نمبر    ( 16 )
#تعریف_کرو پورٹ_NVIC_IP_REGISTERS_وتھ_16    ( 0xE000E3F0 )
#تعریف_کرو پورٹ_AIRCR_REG                      ( *( ( متطاير uint32_t * ) 0xE000ED0C ) )
#تعریف_کرو پورٹ_چوٹی_ثنائی_ہندسہ_دا_BYTE                ( ( uint8_t ) 0x80 )
#تعریف_کرو پورٹ_MAX_PRIGROUP_بٹ              ( ( uint8_t ) 7 )
#تعریف_کرو پورٹ_ترجیح_گروہ_نقاب            ( 0x07UL << 8UL )
#تعریف_کرو پورٹ_PRIGROUP_کھسکاؤ                 ( 8UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants used during system call enter and exit.
 */
#تعریف_کرو پورٹ_PSR_ڈھیر_PADDING_نقاب              ( 1UL << 9UL )
#تعریف_کرو پورٹ_EXC_RETURN_ڈھیر_چوکھٹا_TYPE_نقاب    ( 1UL << 4UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the FPU.
 */
#تعریف_کرو پورٹ_CPACR               ( ( متطاير uint32_t * ) 0xe000ed88 ) /* Coprocessor Access Control Register. */
#تعریف_کرو پورٹ_CPACR_CP10_قدر    ( 3UL )
#تعریف_کرو پورٹ_CPACR_CP11_قدر    پورٹ_CPACR_CP10_قدر
#تعریف_کرو پورٹ_CPACR_CP10_POS      ( 20UL )
#تعریف_کرو پورٹ_CPACR_CP11_POS      ( 22UL )

#تعریف_کرو پورٹ_FPCCR               ( ( متطاير uint32_t * ) 0xe000ef34 ) /* Floating Point Context Control Register. */
#تعریف_کرو پورٹ_FPCCR_ASPEN_POS     ( 31UL )
#تعریف_کرو پورٹ_FPCCR_ASPEN_نقاب    ( 1UL << پورٹ_FPCCR_ASPEN_POS )
#تعریف_کرو پورٹ_FPCCR_LSPEN_POS     ( 30UL )
#تعریف_کرو پورٹ_FPCCR_LSPEN_نقاب    ( 1UL << پورٹ_FPCCR_LSPEN_POS )
/*-----------------------------------------------------------*/

/**
 * @brief Offsets in the stack to the parameters when inside the SVC handler.
 */
#تعریف_کرو پورٹ_وتھ_منزل_LR     ( 5 )
#تعریف_کرو پورٹ_وتھ_منزل_PC     ( 6 )
#تعریف_کرو پورٹ_وتھ_منزل_PSR    ( 7 )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the MPU.
 */
#تعریف_کرو پورٹ_MPU_TYPE_REG                        ( *( ( متطاير uint32_t * ) 0xe000ed90 ) )
#تعریف_کرو پورٹ_MPU_CTRL_REG                        ( *( ( متطاير uint32_t * ) 0xe000ed94 ) )
#تعریف_کرو پورٹ_MPU_RNR_REG                         ( *( ( متطاير uint32_t * ) 0xe000ed98 ) )

#تعریف_کرو پورٹ_MPU_RBAR_REG                        ( *( ( متطاير uint32_t * ) 0xe000ed9c ) )
#تعریف_کرو پورٹ_MPU_RLAR_REG                        ( *( ( متطاير uint32_t * ) 0xe000eda0 ) )

#تعریف_کرو پورٹ_MPU_RBAR_A1_REG                     ( *( ( متطاير uint32_t * ) 0xe000eda4 ) )
#تعریف_کرو پورٹ_MPU_RLAR_A1_REG                     ( *( ( متطاير uint32_t * ) 0xe000eda8 ) )

#تعریف_کرو پورٹ_MPU_RBAR_A2_REG                     ( *( ( متطاير uint32_t * ) 0xe000edac ) )
#تعریف_کرو پورٹ_MPU_RLAR_A2_REG                     ( *( ( متطاير uint32_t * ) 0xe000edb0 ) )

#تعریف_کرو پورٹ_MPU_RBAR_A3_REG                     ( *( ( متطاير uint32_t * ) 0xe000edb4 ) )
#تعریف_کرو پورٹ_MPU_RLAR_A3_REG                     ( *( ( متطاير uint32_t * ) 0xe000edb8 ) )

#تعریف_کرو پورٹ_MPU_MAIR0_REG                       ( *( ( متطاير uint32_t * ) 0xe000edc0 ) )
#تعریف_کرو پورٹ_MPU_MAIR1_REG                       ( *( ( متطاير uint32_t * ) 0xe000edc4 ) )

#تعریف_کرو پورٹ_MPU_RBAR_پتہ_نقاب               ( 0xffffffe0 ) /* Must be 32-byte aligned. */
#تعریف_کرو پورٹ_MPU_RLAR_پتہ_نقاب               ( 0xffffffe0 ) /* Must be 32-byte aligned. */

#تعریف_کرو پورٹ_MPU_RBAR_ACCESS_PERMISSIONS_نقاب    ( 3UL << 1UL )

#تعریف_کرو پورٹ_MPU_MAIR_ATTR0_POS                  ( 0UL )
#تعریف_کرو پورٹ_MPU_MAIR_ATTR0_نقاب                 ( 0x000000ff )

#تعریف_کرو پورٹ_MPU_MAIR_ATTR1_POS                  ( 8UL )
#تعریف_کرو پورٹ_MPU_MAIR_ATTR1_نقاب                 ( 0x0000ff00 )

#تعریف_کرو پورٹ_MPU_MAIR_ATTR2_POS                  ( 16UL )
#تعریف_کرو پورٹ_MPU_MAIR_ATTR2_نقاب                 ( 0x00ff0000 )

#تعریف_کرو پورٹ_MPU_MAIR_ATTR3_POS                  ( 24UL )
#تعریف_کرو پورٹ_MPU_MAIR_ATTR3_نقاب                 ( 0xff000000 )

#تعریف_کرو پورٹ_MPU_MAIR_ATTR4_POS                  ( 0UL )
#تعریف_کرو پورٹ_MPU_MAIR_ATTR4_نقاب                 ( 0x000000ff )

#تعریف_کرو پورٹ_MPU_MAIR_ATTR5_POS                  ( 8UL )
#تعریف_کرو پورٹ_MPU_MAIR_ATTR5_نقاب                 ( 0x0000ff00 )

#تعریف_کرو پورٹ_MPU_MAIR_ATTR6_POS                  ( 16UL )
#تعریف_کرو پورٹ_MPU_MAIR_ATTR6_نقاب                 ( 0x00ff0000 )

#تعریف_کرو پورٹ_MPU_MAIR_ATTR7_POS                  ( 24UL )
#تعریف_کرو پورٹ_MPU_MAIR_ATTR7_نقاب                 ( 0xff000000 )

#تعریف_کرو پورٹ_MPU_RLAR_ATTR_INDEX0                ( 0UL << 1UL )
#تعریف_کرو پورٹ_MPU_RLAR_ATTR_INDEX1                ( 1UL << 1UL )
#تعریف_کرو پورٹ_MPU_RLAR_ATTR_INDEX2                ( 2UL << 1UL )
#تعریف_کرو پورٹ_MPU_RLAR_ATTR_INDEX3                ( 3UL << 1UL )
#تعریف_کرو پورٹ_MPU_RLAR_ATTR_INDEX4                ( 4UL << 1UL )
#تعریف_کرو پورٹ_MPU_RLAR_ATTR_INDEX5                ( 5UL << 1UL )
#تعریف_کرو پورٹ_MPU_RLAR_ATTR_INDEX6                ( 6UL << 1UL )
#تعریف_کرو پورٹ_MPU_RLAR_ATTR_INDEX7                ( 7UL << 1UL )

#تعریف_کرو پورٹ_MPU_RLAR_REGION_ENABLE              ( 1UL )

#إذا ( پورٹ_ARMV8_M_MINOR_نسخہ >= 1 )

    /* Enable Privileged eXecute Never MPU attribute for the selected memory
     * region. */
    #تعریف_کرو پورٹ_MPU_RLAR_PRIVILEGED_EXECUTE_NEVER    ( 1UL << 4UL )
#جے_انت /* portARMV8M_MINOR_VERSION >= 1 */

/* Enable privileged access to unmapped region. */
#تعریف_کرو پورٹ_MPU_PRIV_BACKGROUND_ENABLE_ثنائی_ہندسہ    ( 1UL << 2UL )

/* Enable MPU. */
#تعریف_کرو پورٹ_MPU_ENABLE_ثنائی_ہندسہ                    ( 1UL << 0UL )

/* Extract first address of the MPU region as encoded in the
 * RBAR (Region Base Address Register) value. */
#تعریف_کرو پورٹ_کڈھو_پہلا_پتہ_FROM_RBAR( rbar ) \
    ( ( rbar ) & پورٹ_MPU_RBAR_پتہ_نقاب )

/* Extract last address of the MPU region as encoded in the
 * RLAR (Region Limit Address Register) value. */
#تعریف_کرو پورٹ_کڈھو_آخری_پتہ_FROM_RLAR( rlar ) \
    ( ( ( rlar ) & پورٹ_MPU_RLAR_پتہ_نقاب ) | ~پورٹ_MPU_RLAR_پتہ_نقاب )

/* Does addr lies within [start, end] address range? */
#تعریف_کرو پورٹ_IS_پتہ_WITHIN_RANGE( addr, شروع, سرا ) \
    ( ( ( addr ) >= ( شروع ) ) && ( ( addr ) <= ( سرا ) ) )

/* Is the access request satisfied by the available permissions? */
#تعریف_کرو پورٹ_IS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#تعریف_کرو پورٹ_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کرو پورٹ_جوڑو_UINT32_WILL_حد_توں_ودھ( a, b )    ( ( a ) > ( پورٹ_UINT32_MAX - ( b ) ) )
/*-----------------------------------------------------------*/

/**
 * @brief The maximum 24-bit number.
 *
 * It is needed because the systick is a 24-bit counter.
 */
#تعریف_کرو پورٹ_MAX_24_ثنائی_ہندسہ_نمبر       ( 0xffffffUL )

/**
 * @brief A fiddle factor to estimate the number of SysTick counts that would
 * have occurred while the SysTick counter is stopped during tickless idle
 * calculations.
 */
#تعریف_کرو پورٹ_MISSED_COUNTS_ضارب    ( 94UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to set up the initial stack.
 */
#تعریف_کرو پورٹ_INITIAL_XPSR    ( 0x01000000 )

#إذا ( config_لگاتار_FREERTOS_SECURE_ONLY == 1 )

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
    #تعریف_کرو پورٹ_INITIAL_EXC_RETURN    ( 0xfffffffd )
#وإلا

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
    #تعریف_کرو پورٹ_INITIAL_EXC_RETURN    ( 0xffffffbc )
#جے_انت /* configRUN_FREERTOS_SECURE_ONLY */

/**
 * @brief CONTROL register privileged bit mask.
 *
 * Bit[0] in CONTROL register tells the privilege:
 *  Bit[0] = 0 ==> The task is privileged.
 *  Bit[0] = 1 ==> The task is not privileged.
 */
#تعریف_کرو پورٹ_CONTROL_PRIVILEGED_نقاب         ( 1UL << 0UL )

/**
 * @brief Initial CONTROL register values.
 */
#تعریف_کرو پورٹ_INITIAL_CONTROL_UNPRIVILEGED    ( 0x3 )
#تعریف_کرو پورٹ_INITIAL_CONTROL_PRIVILEGED      ( 0x2 )

/**
 * @brief Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register.
 */
#جے_بنا_تعریف configSYSTICK_CLOCK_HZ
    #تعریف_کرو configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #تعریف_کرو پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG    ( پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ )
#وإلا
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #تعریف_کرو پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG    ( 0 )
#جے_انت

/**
 * @brief Let the user override the pre-loading of the initial LR with the
 * address of prvTaskExitError() in case it messes up unwinding of the stack
 * in the debugger.
 */
#جے_تعریف_شدہ config_TASK_RETURN_پتہ
    #تعریف_کرو پورٹ_TASK_RETURN_پتہ    config_TASK_RETURN_پتہ
#وإلا
    #تعریف_کرو پورٹ_TASK_RETURN_پتہ    prvTaskExitError
#جے_انت

/**
 * @brief If portPRELOAD_REGISTERS then registers will be given an initial value
 * when a task is created. This helps in debugging at the cost of code size.
 */
#تعریف_کرو پورٹ_PRELOAD_REGISTERS    1

/**
 * @brief A task is created without a secure context, and must call
 * portALLOCATE_SECURE_CONTEXT() to give itself a secure context before it makes
 * any secure calls.
 */
#تعریف_کرو پورٹ_NO_SECURE_CONTEXT    0

/**
 * @brief Constants required to check and configure PACBTI security feature implementation.
 */
#إذا ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )

    #تعریف_کرو پورٹ_ID_ISAR5_REG       ( *( ( متطاير uint32_t * ) 0xe000ed74 ) )

    #تعریف_کرو پورٹ_CONTROL_UPAC_EN    ( 1UL << 7UL )
    #تعریف_کرو پورٹ_CONTROL_PAC_EN     ( 1UL << 6UL )
    #تعریف_کرو پورٹ_CONTROL_UBTI_EN    ( 1UL << 5UL )
    #تعریف_کرو پورٹ_CONTROL_BTI_EN     ( 1UL << 4UL )

#جے_انت /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Used to catch tasks that attempt to return from their implementing
 * function.
 */
ساكن فراغ prvTaskExitError( فراغ );

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Extract MPU region's access permissions from the Region Base Address
     * Register (RBAR) value.
     *
     * @param ulRBARValue RBAR value for the MPU region.
     *
     * @return uint32_t Access permissions.
     */
    ساكن uint32_t prvGetRegionAccessPermissions( uint32_t ulRBARValue ) PRIVILEGED_FUNCTION;
#جے_انت /* configENABLE_MPU == 1 && configUSE_MPU_WRAPPERS_V1 == 0 */

#إذا ( configENABLE_MPU == 1 )

    /**
     * @brief Setup the Memory Protection Unit (MPU).
     */
    ساكن فراغ prv_تیاری_MPU( فراغ ) PRIVILEGED_FUNCTION;
#جے_انت /* configENABLE_MPU */

#إذا ( configENABLE_FPU == 1 )

    /**
     * @brief Setup the Floating Point Unit (FPU).
     */
    ساكن فراغ prv_تیاری_FPU( فراغ ) PRIVILEGED_FUNCTION;
#جے_انت /* configENABLE_FPU */

#إذا ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )

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
    #إذا ( config_نمبر_دا_CORES == 1 )
        ساكن uint32_t prvConfigurePACBTI( ادھار_Type_t x_Write_Control_رجسٹر );
    #وإلا /* #if ( configNUMBER_OF_CORES == 1 ) */
        uint32_t vConfigurePACBTI( ادھار_Type_t x_Write_Control_رجسٹر );
    #جے_انت /* #if ( configNUMBER_OF_CORES == 1 ) */

#جے_انت /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

/**
 * @brief Setup the timer to generate the tick interrupts.
 *
 * The implementation in this file is weak to allow application writers to
 * change the timer used to generate the tick interrupt.
 */
فراغ v_پورٹ_تیاری_Timer_رکاوٹ( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether the current execution context is interrupt.
 *
 * @return pdTRUE if the current execution context is interrupt, pdFALSE
 * otherwise.
 */
ادھار_Type_t x_پورٹ_Is_Inside_رکاوٹ( فراغ );

/**
 * @brief Yield the processor.
 */
فراغ v_پورٹ_Yield( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief Enter critical section.
 */
فراغ v_پورٹ_Enter_Critical( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief Exit from critical section.
 */
فراغ v_پورٹ_Exit_Critical( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief SysTick handler.
 */
فراغ SysTick_Handler( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief C part of SVC handler.
 */
پورٹ_DONT_DISCARD فراغ v_پورٹ_SVCHandler_C( uint32_t * pul_Caller_ڈھیر_پتہ ) PRIVILEGED_FUNCTION;

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the system call stack so that upon returning from
     * SVC, the system call stack is used.
     *
     * @param pulTaskStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    فراغ vSystemCallEnter( uint32_t * pul_Task_ڈھیر,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_نمبر ) PRIVILEGED_FUNCTION;

#جے_انت /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    فراغ vRequestSystemCallExit( فراغ ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#جے_انت /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param pulSystemCallStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     */
    فراغ vSystemCallExit( uint32_t * pul_System_Call_ڈھیر,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#جے_انت /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#إذا ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    ادھار_Type_t x_پورٹ_Is_Task_Privileged( فراغ ) PRIVILEGED_FUNCTION;

#جے_انت /* configENABLE_MPU == 1 */

#إذا ( config_نمبر_دا_CORES > 1 )

    /**
     * @brief Platform/Application-defined function that wakes up the secondary cores.
     *
     * @return pdTRUE if the secondary cores were successfully woken up.
     *         pdFALSE otherwise.
     */
    خارجي ادھار_Type_t configWAKE_SECONDARY_CORES( فراغ );

#جے_انت /* #if ( configNUMBER_OF_CORES > 1 ) */

/**
 * @brief Configures interrupt priorities.
 */
فراغ v_پورٹ_Configure_رکاوٹ_Priorities( فراغ ) PRIVILEGED_FUNCTION;
/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief This variable is set to pdTRUE when the scheduler is started.
     */
    PRIVILEGED_انکڑے ساكن ادھار_Type_t xSchedulerRunning = pdFALSE;

#جے_انت /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/**
 * @brief Each task maintains its own interrupt status in the critical nesting
 * variable.
 */
#إذا ( config_نمبر_دا_CORES == 1 )
    PRIVILEGED_انکڑے ساكن متطاير uint32_t ulCriticalNesting = 0UL;
#وإلا /* #if ( configNUMBER_OF_CORES == 1 ) */
    PRIVILEGED_انکڑے متطاير uint32_t ulCriticalNestings[ config_نمبر_دا_CORES ] = { 0 };
    /* Flags to check if the secondary cores are ready. */
    PRIVILEGED_انکڑے متطاير uint8_t ucSecondaryCoresReadyFlags[ config_نمبر_دا_CORES - 1 ] = { 0 };
    /* Flag to indicate that the primary core has completed its initialisation. */
    PRIVILEGED_انکڑے متطاير uint8_t uc_Primary_Core_Init_پورا_Flag = 0;
 #جے_انت /* #if ( configNUMBER_OF_CORES == 1 ) */

#إذا ( configENABLE_TRUSTZONE == 1 )

    /**
     * @brief Saved as part of the task context to indicate which context the
     * task is using on the secure side.
     */
    PRIVILEGED_انکڑے پورٹ_DONT_DISCARD متطاير SecureContextHandle_t xSecureContext = پورٹ_NO_SECURE_CONTEXT;
#جے_انت /* configENABLE_TRUSTZONE */

/**
 * @brief Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#إذا ( ( configASSERT_DEFINED == 1 ) && ( پورٹ_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) )

    ساكن uint8_t uc_Max_Sys_Call_ترجیح = 0;
    ساكن uint32_t ulMaxPRIGROUPValue = 0;
    ساكن ثابت متطاير uint8_t * ثابت pc_رکاوٹ_ترجیح_Registers = ( ثابت متطاير uint8_t * ) پورٹ_NVIC_IP_REGISTERS_وتھ_16;

#جے_انت /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */

#إذا ( configUSE_TICKLESS_IDLE == 1 )

    /**
     * @brief The number of SysTick increments that make up one tick period.
     */
    PRIVILEGED_انکڑے ساكن uint32_t ulTimerCountsForOneTick = 0;

    /**
     * @brief The maximum number of tick periods that can be suppressed is
     * limited by the 24 bit resolution of the SysTick timer.
     */
    PRIVILEGED_انکڑے ساكن uint32_t x_ودھ_توں_ودھ_Possible_Suppressed_Ticks = 0;

    /**
     * @brief Compensate for the CPU cycles that pass while the SysTick is
     * stopped (low power functionality only).
     */
    PRIVILEGED_انکڑے ساكن uint32_t ulStoppedTimerCompensation = 0;
#جے_انت /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) فراغ v_پورٹ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ویلا )
    {
        uint32_t ul_Reload_قدر, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_بایاں;
        TickType_t x_Modifiable_Idle_ویلا;

        /* Make sure the SysTick reload value does not overflow the counter. */
        إذا( x_Expected_Idle_ویلا > x_ودھ_توں_ودھ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_ویلا = x_ودھ_توں_ودھ_Possible_Suppressed_Ticks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm متطاير ( "cpsid i" ::: "memory" );
        __asm متطاير ( "dsb" );
        __asm متطاير ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        إذا( e_Task_Confirm_Sleep_منوال_حالت() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the cpsid instruction
             * above. */
            __asm متطاير ( "cpsie i" ::: "memory" );
        }
        وإلا
        {
            /* Stop the SysTick momentarily.  The time the SysTick is stopped for
             * is accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            پورٹ_NVIC_SYSTICK_CTRL_REG = ( پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG | پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_بایاں = پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG;

            إذا( ul_Sys_Tick_Decrements_بایاں == 0 )
            {
                ul_Sys_Tick_Decrements_بایاں = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_قدر = ul_Sys_Tick_Decrements_بایاں + ( ulTimerCountsForOneTick * ( x_Expected_Idle_ویلا - 1UL ) );

            إذا( ( پورٹ_NVIC_INT_CTRL_REG & پورٹ_NVIC_PEND_SYSTICK_سیٹ_ثنائی_ہندسہ ) != 0 )
            {
                پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PEND_SYSTICK_CLEAR_ثنائی_ہندسہ;
                ul_Reload_قدر -= ulTimerCountsForOneTick;
            }

            إذا( ul_Reload_قدر > ulStoppedTimerCompensation )
            {
                ul_Reload_قدر -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            پورٹ_NVIC_SYSTICK_لدو_REG = ul_Reload_قدر;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG = 0UL;

            /* Restart SysTick. */
            پورٹ_NVIC_SYSTICK_CTRL_REG |= پورٹ_NVIC_SYSTICK_ENABLE_ثنائی_ہندسہ;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            x_Modifiable_Idle_ویلا = x_Expected_Idle_ویلا;
            configPRE_SLEEP_PROCESSING( x_Modifiable_Idle_ویلا );

            إذا( x_Modifiable_Idle_ویلا > 0 )
            {
                __asm متطاير ( "dsb" ::: "memory" );
                __asm متطاير ( "wfi" );
                __asm متطاير ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_ویلا );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the cpsid instruction above. */
            __asm متطاير ( "cpsie i" ::: "memory" );
            __asm متطاير ( "dsb" );
            __asm متطاير ( "isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm متطاير ( "cpsid i" ::: "memory" );
            __asm متطاير ( "dsb" );
            __asm متطاير ( "isb" );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            پورٹ_NVIC_SYSTICK_CTRL_REG = ( پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG | پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ );

            /* Determine whether the SysTick has already counted to zero. */
            إذا( ( پورٹ_NVIC_SYSTICK_CTRL_REG & پورٹ_NVIC_SYSTICK_گنتی_FLAG_ثنائی_ہندسہ ) != 0 )
            {
                uint32_t ul_Calculated_لدو_قدر;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_لدو_قدر = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_قدر - پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                إذا( ( ul_Calculated_لدو_قدر <= ulStoppedTimerCompensation ) || ( ul_Calculated_لدو_قدر > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_لدو_قدر = ( ulTimerCountsForOneTick - 1UL );
                }

                پورٹ_NVIC_SYSTICK_لدو_REG = ul_Calculated_لدو_قدر;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = x_Expected_Idle_ویلا - 1UL;
            }
            وإلا
            {
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_بایاں = پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG;
                #إذا ( پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG != پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    إذا( ul_Sys_Tick_Decrements_بایاں == 0 )
                    {
                        ul_Sys_Tick_Decrements_بایاں = ul_Reload_قدر;
                    }
                }
                #جے_انت /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_ویلا * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_بایاں;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                پورٹ_NVIC_SYSTICK_لدو_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG = 0UL;
            پورٹ_NVIC_SYSTICK_CTRL_REG = پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ | پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ | پورٹ_NVIC_SYSTICK_ENABLE_ثنائی_ہندسہ;
            #إذا ( پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG == پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ )
            {
                پورٹ_NVIC_SYSTICK_لدو_REG = ulTimerCountsForOneTick - 1UL;
            }
            #وإلا
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                پورٹ_NVIC_SYSTICK_CTRL_REG = پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ | پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ;

                إذا( ( پورٹ_NVIC_SYSTICK_CTRL_REG & پورٹ_NVIC_SYSTICK_گنتی_FLAG_ثنائی_ہندسہ ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG = 0;
                }

                پورٹ_NVIC_SYSTICK_لدو_REG = ulTimerCountsForOneTick - 1UL;
                پورٹ_NVIC_SYSTICK_CTRL_REG = پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG | پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ | پورٹ_NVIC_SYSTICK_ENABLE_ثنائی_ہندسہ;
            }
            #جے_انت /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            v_Task_قدم_Tick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __asm متطاير ( "cpsie i" ::: "memory" );
        }
    }

#جے_انت /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

__attribute__( ( weak ) ) فراغ v_پورٹ_تیاری_Timer_رکاوٹ( فراغ ) /* PRIVILEGED_FUNCTION */
{
    /* Calculate the constants required to configure the tick interrupt. */
    #إذا ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_شرح_HZ );
        x_ودھ_توں_ودھ_Possible_Suppressed_Ticks = پورٹ_MAX_24_ثنائی_ہندسہ_نمبر / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = پورٹ_MISSED_COUNTS_ضارب / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #جے_انت /* configUSE_TICKLESS_IDLE */

    /* Stop and reset SysTick.
     *
     * QEMU versions older than 7.0.0 contain a bug which causes an error if we
     * enable SysTick without first selecting a valid clock source. We trigger
     * the bug if we change clock sources from a clock with a zero clock period
     * to one with a nonzero clock period and enable Systick at the same time.
     * So we configure the CLKSOURCE bit here, prior to setting the ENABLE bit.
     * This workaround avoids the bug in QEMU versions older than 7.0.0. */
    پورٹ_NVIC_SYSTICK_CTRL_REG = پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG;
    پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    پورٹ_NVIC_SYSTICK_لدو_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_شرح_HZ ) - 1UL;
    پورٹ_NVIC_SYSTICK_CTRL_REG = پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG | پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ | پورٹ_NVIC_SYSTICK_ENABLE_ثنائی_ہندسہ;
}
/*-----------------------------------------------------------*/

ساكن فراغ prvTaskExitError( فراغ )
{
    متطاير uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    #إذا ( config_نمبر_دا_CORES == 1 )
        configASSERT( ulCriticalNesting == ~0UL );
    #وإلا /* #if ( configNUMBER_OF_CORES == 1 ) */
        configASSERT( ulCriticalNestings[ پورٹ_GET_CORE_ID() ] == ~0UL );
    #جے_انت /* #if ( configNUMBER_OF_CORES == 1 ) */
    پورٹ_DISABLE_INTERRUPTS();

    طالما( ulDummy == 0 )
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

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ساكن uint32_t prvGetRegionAccessPermissions( uint32_t ulRBARValue ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ulAccessPermissions = 0;

        إذا( ( ulRBARValue & پورٹ_MPU_RBAR_ACCESS_PERMISSIONS_نقاب ) == پورٹ_MPU_REGION_READ_ONLY )
        {
            ulAccessPermissions = tskMPU_READ_PERMISSION;
        }

        إذا( ( ulRBARValue & پورٹ_MPU_RBAR_ACCESS_PERMISSIONS_نقاب ) == پورٹ_MPU_REGION_READ_WRITE )
        {
            ulAccessPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
        }

        أرجع ulAccessPermissions;
    }

#جے_انت /* configENABLE_MPU == 1 && configUSE_MPU_WRAPPERS_V1 == 0 */
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    ساكن فراغ prv_تیاری_MPU( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        #إذا defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint32_t * __privileged_functions_start__;
            خارجي uint32_t * __privileged_functions_end__;
            خارجي uint32_t * __syscalls_flash_start__;
            خارجي uint32_t * __syscalls_flash_end__;
            خارجي uint32_t * __unprivileged_flash_start__;
            خارجي uint32_t * __unprivileged_flash_end__;
            خارجي uint32_t * __privileged_sram_start__;
            خارجي uint32_t * __privileged_sram_end__;
        #وإلا /* if defined( __ARMCC_VERSION ) */
            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint32_t __privileged_functions_start__[];
            خارجي uint32_t __privileged_functions_end__[];
            خارجي uint32_t __syscalls_flash_start__[];
            خارجي uint32_t __syscalls_flash_end__[];
            خارجي uint32_t __unprivileged_flash_start__[];
            خارجي uint32_t __unprivileged_flash_end__[];
            خارجي uint32_t __privileged_sram_start__[];
            خارجي uint32_t __privileged_sram_end__[];
        #جے_انت /* defined( __ARMCC_VERSION ) */

        /* The only permitted number of regions are 8 or 16. */
        configASSERT( ( config_کل_MPU_REGIONS == 8 ) || ( config_کل_MPU_REGIONS == 16 ) );

        /* MAIR0 - Index 0. */
        پورٹ_MPU_MAIR0_REG |= ( ( پورٹ_MPU_عام_حافظہ_BUFFERABLE_CACHEABLE << پورٹ_MPU_MAIR_ATTR0_POS ) & پورٹ_MPU_MAIR_ATTR0_نقاب );
        /* MAIR0 - Index 1. */
        پورٹ_MPU_MAIR0_REG |= ( ( پورٹ_MPU_DEVICE_حافظہ_n_Gn_RE << پورٹ_MPU_MAIR_ATTR1_POS ) & پورٹ_MPU_MAIR_ATTR1_نقاب );

        /* Setup privileged flash as Read Only so that privileged tasks can
         * read it but not modify. */
        پورٹ_MPU_RNR_REG = پورٹ_PRIVILEGED_FLASH_REGION;
        پورٹ_MPU_RBAR_REG = ( ( ( uint32_t ) __privileged_functions_start__ ) & پورٹ_MPU_RBAR_پتہ_نقاب ) |
                           ( پورٹ_MPU_REGION_NON_SHAREABLE ) |
                           ( پورٹ_MPU_REGION_PRIVILEGED_READ_ONLY );
        پورٹ_MPU_RLAR_REG = ( ( ( uint32_t ) __privileged_functions_end__ ) & پورٹ_MPU_RLAR_پتہ_نقاب ) |
                           ( پورٹ_MPU_RLAR_ATTR_INDEX0 ) |
                           ( پورٹ_MPU_RLAR_REGION_ENABLE );

        /* Setup unprivileged flash as Read Only by both privileged and
         * unprivileged tasks. All tasks can read it but no-one can modify. */
        پورٹ_MPU_RNR_REG = پورٹ_UNPRIVILEGED_FLASH_REGION;
        پورٹ_MPU_RBAR_REG = ( ( ( uint32_t ) __unprivileged_flash_start__ ) & پورٹ_MPU_RBAR_پتہ_نقاب ) |
                           ( پورٹ_MPU_REGION_NON_SHAREABLE ) |
                           ( پورٹ_MPU_REGION_READ_ONLY );
        پورٹ_MPU_RLAR_REG = ( ( ( uint32_t ) __unprivileged_flash_end__ ) & پورٹ_MPU_RLAR_پتہ_نقاب ) |
                           ( پورٹ_MPU_RLAR_ATTR_INDEX0 ) |
                           ( پورٹ_MPU_RLAR_REGION_ENABLE );

        /* Setup unprivileged syscalls flash as Read Only by both privileged
         * and unprivileged tasks. All tasks can read it but no-one can modify. */
        پورٹ_MPU_RNR_REG = پورٹ_UNPRIVILEGED_SYSCALLS_REGION;
        پورٹ_MPU_RBAR_REG = ( ( ( uint32_t ) __syscalls_flash_start__ ) & پورٹ_MPU_RBAR_پتہ_نقاب ) |
                           ( پورٹ_MPU_REGION_NON_SHAREABLE ) |
                           ( پورٹ_MPU_REGION_READ_ONLY );
        پورٹ_MPU_RLAR_REG = ( ( ( uint32_t ) __syscalls_flash_end__ ) & پورٹ_MPU_RLAR_پتہ_نقاب ) |
                           ( پورٹ_MPU_RLAR_ATTR_INDEX0 ) |
                           ( پورٹ_MPU_RLAR_REGION_ENABLE );

        /* Setup RAM containing kernel data for privileged access only. */
        پورٹ_MPU_RNR_REG = پورٹ_PRIVILEGED_RAM_REGION;
        پورٹ_MPU_RBAR_REG = ( ( ( uint32_t ) __privileged_sram_start__ ) & پورٹ_MPU_RBAR_پتہ_نقاب ) |
                           ( پورٹ_MPU_REGION_NON_SHAREABLE ) |
                           ( پورٹ_MPU_REGION_PRIVILEGED_READ_WRITE ) |
                           ( پورٹ_MPU_REGION_EXECUTE_NEVER );
        پورٹ_MPU_RLAR_REG = ( ( ( uint32_t ) __privileged_sram_end__ ) & پورٹ_MPU_RLAR_پتہ_نقاب ) |
                           ( پورٹ_MPU_RLAR_ATTR_INDEX0 ) |
                           ( پورٹ_MPU_RLAR_REGION_ENABLE );

        /* Enable mem fault. */
        پورٹ_SCB_SYS_HANDLER_CTRL_STATE_REG |= پورٹ_SCB_MEM_FAULT_ENABLE_ثنائی_ہندسہ;

        /* Enable MPU with privileged background access i.e. unmapped
         * regions have privileged access. */
        پورٹ_MPU_CTRL_REG |= ( پورٹ_MPU_PRIV_BACKGROUND_ENABLE_ثنائی_ہندسہ | پورٹ_MPU_ENABLE_ثنائی_ہندسہ );
    }

#جے_انت /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#إذا ( configENABLE_FPU == 1 )

    ساكن فراغ prv_تیاری_FPU( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        #إذا ( configENABLE_TRUSTZONE == 1 )
        {
            /* Enable non-secure access to the FPU. */
            SecureInit_EnableNSFPUAccess();
        }
        #جے_انت /* configENABLE_TRUSTZONE */

        /* CP10 = 11 ==> Full access to FPU i.e. both privileged and
         * unprivileged code should be able to access FPU. CP11 should be
         * programmed to the same value as CP10. */
        *( پورٹ_CPACR ) |= ( ( پورٹ_CPACR_CP10_قدر << پورٹ_CPACR_CP10_POS ) |
                            ( پورٹ_CPACR_CP11_قدر << پورٹ_CPACR_CP11_POS )
                            );

        /* ASPEN = 1 ==> Hardware should automatically preserve floating point
         * context on exception entry and restore on exception return.
         * LSPEN = 1 ==> Enable lazy context save of FP state. */
        *( پورٹ_FPCCR ) |= ( پورٹ_FPCCR_ASPEN_نقاب | پورٹ_FPCCR_LSPEN_نقاب );
    }

#جے_انت /* configENABLE_FPU */
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Yield( فراغ ) /* PRIVILEGED_FUNCTION */
{
    /* Set a PendSV to request a context switch. */
    پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm متطاير ( "dsb" ::: "memory" );
    __asm متطاير ( "isb" );
}
/*-----------------------------------------------------------*/

#إذا ( config_نمبر_دا_CORES == 1 )
    فراغ v_پورٹ_Enter_Critical( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        پورٹ_DISABLE_INTERRUPTS();
        ulCriticalNesting++;
        /* Barriers are normally not required but do ensure the code is
        * completely within the specified behaviour for the architecture. */
        __asm متطاير ( "dsb" ::: "memory" );
        __asm متطاير ( "isb" );
    }
    /*-----------------------------------------------------------*/

    فراغ v_پورٹ_Exit_Critical( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( ulCriticalNesting );
        ulCriticalNesting--;

        إذا( ulCriticalNesting == 0 )
        {
            پورٹ_ENABLE_INTERRUPTS();
        }
    }
#جے_انت /* configNUMBER_OF_CORES == 1 */
/*-----------------------------------------------------------*/

فراغ SysTick_Handler( فراغ ) /* PRIVILEGED_FUNCTION */
{
    uint32_t ul_پچھلا_نقاب;

    ul_پچھلا_نقاب = پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR();
    #إذا ( config_نمبر_دا_CORES > 1 )
        UBaseType_t ux_Saved_رکاوٹ_حالت = پورٹ_ENTER_CRITICAL_FROM_ISR();
    #جے_انت /* if ( configNUMBER_OF_CORES > 1 ) */

    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_منزل_SCHEDULER();
            /* Pend a context switch. */
            پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ;
        }
        وإلا
        {
            traceISR_EXIT();
        }
    }
    #إذا ( config_نمبر_دا_CORES > 1 )
        پورٹ_EXIT_CRITICAL_FROM_ISR( ux_Saved_رکاوٹ_حالت );
    #جے_انت /* if ( configNUMBER_OF_CORES > 1 ) */

    پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( ul_پچھلا_نقاب );
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_SVCHandler_C( uint32_t * pul_Caller_ڈھیر_پتہ ) /* PRIVILEGED_FUNCTION portDONT_DISCARD */
{
    #إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )
        #إذا defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint32_t * __syscalls_flash_start__;
            خارجي uint32_t * __syscalls_flash_end__;
        #وإلا
            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint32_t __syscalls_flash_start__[];
            خارجي uint32_t __syscalls_flash_end__[];
        #جے_انت /* defined( __ARMCC_VERSION ) */
    #جے_انت /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #إذا ( configENABLE_MPU == 1 )
        #إذا defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint32_t * __privileged_functions_start__;
            خارجي uint32_t * __privileged_functions_end__;
        #وإلا
            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint32_t __privileged_functions_start__[];
            خارجي uint32_t __privileged_functions_end__[];
        #جے_انت /* defined( __ARMCC_VERSION ) */
    #جے_انت /* configENABLE_MPU == 1 */

    uint32_t ulPC;

    #إذا ( configENABLE_TRUSTZONE == 1 )
        uint32_t ulR0, ulR1;
        خارجي TaskHandle_t pxCurrentTCB;
        #إذا ( configENABLE_MPU == 1 )
            uint32_t ulControl, ulIsTaskPrivileged;
        #جے_انت /* configENABLE_MPU */
    #جے_انت /* configENABLE_TRUSTZONE */
    uint8_t ucSVCNumber;

    /* Register are stored on the stack in the following order - R0, R1, R2, R3,
     * R12, LR, PC, xPSR. */
    ulPC = pul_Caller_ڈھیر_پتہ[ پورٹ_وتھ_منزل_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    بدل( ucSVCNumber )
    {
    #إذا ( configENABLE_TRUSTZONE == 1 )
        حالة پورٹ_SVC_ALLOCATE_SECURE_CONTEXT:

            /* R0 contains the stack size passed as parameter to the
             * vPortAllocateSecureContext function. */
            ulR0 = pul_Caller_ڈھیر_پتہ[ 0 ];

            #إذا ( configENABLE_MPU == 1 )
            {
                /* Read the CONTROL register value. */
                __asm متطاير ( "mrs %0, control"  : "=r" ( ulControl ) );

                /* The task that raised the SVC is privileged if Bit[0]
                 * in the CONTROL register is 0. */
                ulIsTaskPrivileged = ( ( ulControl & پورٹ_CONTROL_PRIVILEGED_نقاب ) == 0 );

                /* Allocate and load a context for the secure task. */
                xSecureContext = SecureContext_AllocateContext( ulR0, ulIsTaskPrivileged, pxCurrentTCB );
            }
            #وإلا /* if ( configENABLE_MPU == 1 ) */
            {
                /* Allocate and load a context for the secure task. */
                xSecureContext = SecureContext_AllocateContext( ulR0, pxCurrentTCB );
            }
            #جے_انت /* configENABLE_MPU */

            configASSERT( xSecureContext != securecontextINVALID_CONTEXT_ID );
            Secure_Context_لدو_Context( xSecureContext, pxCurrentTCB );
            اكسر;

        حالة پورٹ_SVC_FREE_SECURE_CONTEXT:
            #إذا ( configENABLE_MPU == 1 )
            إذا( ( ulPC >= ( uint32_t ) __privileged_functions_start__ ) &&
                ( ulPC <= ( uint32_t ) __privileged_functions_end__ ) )
            {
            #جے_انت /* configENABLE_MPU */
                /* R0 contains TCB being freed and R1 contains the secure
                 * context handle to be freed. */
                ulR0 = pul_Caller_ڈھیر_پتہ[ 0 ];
                ulR1 = pul_Caller_ڈھیر_پتہ[ 1 ];

                /* Free the secure context. */
                SecureContext_FreeContext( ( SecureContextHandle_t ) ulR1, ( فراغ * ) ulR0 );
            #إذا ( configENABLE_MPU == 1 )
            }
            #جے_انت /* configENABLE_MPU */
            اكسر;
    #جے_انت /* configENABLE_TRUSTZONE */

        حالة پورٹ_SVC_شروع_SCHEDULER:
            #إذا ( configENABLE_MPU == 1 )
            إذا( ( ulPC >= ( uint32_t ) __privileged_functions_start__ ) &&
                ( ulPC <= ( uint32_t ) __privileged_functions_end__ ) )
            {
            #جے_انت /* configENABLE_MPU */
                #إذا ( configENABLE_TRUSTZONE == 1 )
                {
                    /* De-prioritize the non-secure exceptions so that the
                     * non-secure pendSV runs at the lowest priority. */
                    SecureInit_DePrioritizeNSExceptions();

                    /* Initialize the secure context management system. */
                    SecureContext_Init();
                }
                #جے_انت /* configENABLE_TRUSTZONE */

                #إذا ( configENABLE_FPU == 1 )
                {
                    /* Setup the Floating Point Unit (FPU). */
                    prv_تیاری_FPU();
                }
                #جے_انت /* configENABLE_FPU */

                /* Setup the context of the first task so that the first task starts
                 * executing. */
                v_Restore_Context_دا_پہلا_Task();
            #إذا ( configENABLE_MPU == 1 )
            }
            #جے_انت /* configENABLE_MPU */
            اكسر;

    #إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )
        حالة پورٹ_SVC_RAISE_PRIVILEGE:

            /* Only raise the privilege, if the svc was raised from any of
             * the system calls. */
            إذا( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
            {
                vRaisePrivilege();
            }
            اكسر;
    #جے_انت /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #إذا ( configENABLE_MPU == 1 )
        حالة پورٹ_SVC_YIELD:
            v_پورٹ_Yield();
            اكسر;
    #جے_انت /* configENABLE_MPU == 1 */

        افتراضي:
            /* Incorrect SVC call. */
            configASSERT( pdFALSE );
    }
}
/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    فراغ vSystemCallEnter( uint32_t * pul_Task_ڈھیر,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_نمبر ) /* PRIVILEGED_FUNCTION */
    {
        خارجي TaskHandle_t pxCurrentTCB;
        خارجي UBaseType_t uxSystemCallImplementations[ عدد_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_ڈھیر;
        uint32_t ul_Hardware_Saved_Exception_چوکھٹا_ناپ, ulSystemCallLocation, i;

        #إذا defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint32_t * __syscalls_flash_start__;
            خارجي uint32_t * __syscalls_flash_end__;
        #وإلا
            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint32_t __syscalls_flash_start__[];
            خارجي uint32_t __syscalls_flash_end__[];
        #جے_انت /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_ڈھیر[ پورٹ_وتھ_منزل_PC ];
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
        إذا( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر == عدم ) &&
            ( uxSystemCallImplementations[ uc_System_Call_نمبر ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_ڈھیر = pxMpuSettings->x_System_Call_ڈھیر_Info.pul_System_Call_ڈھیر;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            #إذا ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )
            {
                إذا( ( ulLR & پورٹ_EXC_RETURN_ڈھیر_چوکھٹا_TYPE_نقاب ) == 0UL )
                {
                    /* Extended frame i.e. FPU in use. */
                    ul_Hardware_Saved_Exception_چوکھٹا_ناپ = 26;
                    __asm متطاير (
                        " vpush {s0}         \n" /* Trigger lazy stacking. */
                        " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                        ::: "memory"
                        );
                }
                وإلا
                {
                    /* Standard frame i.e. FPU not in use. */
                    ul_Hardware_Saved_Exception_چوکھٹا_ناپ = 8;
                }
            }
            #وإلا /* if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */
            {
                ul_Hardware_Saved_Exception_چوکھٹا_ناپ = 8;
            }
            #جے_انت /* configENABLE_FPU || configENABLE_MVE */

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_ڈھیر = pul_System_Call_ڈھیر - ul_Hardware_Saved_Exception_چوکھٹا_ناپ;

            /* Copy the stack frame. */
            لكل( i = 0; i < ul_Hardware_Saved_Exception_چوکھٹا_ناپ; i++ )
            {
                pul_System_Call_ڈھیر[ i ] = pul_Task_ڈھیر[ i ];
            }

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_ڈھیر_Info.ul_Link_رجسٹر_At_System_Call_اندراج = pul_Task_ڈھیر[ پورٹ_وتھ_منزل_LR ];

            /* Store the value of the PSPLIM register before the SVC was raised.
             * We need to restore it when we exit from the system call. */
            #إذا ( پورٹ_USE_PSPLIM_رجسٹر == 1 )
            {
                __asm متطاير ( "mrs %0, psplim" : "=r" ( pxMpuSettings->x_System_Call_ڈھیر_Info.ul_ڈھیر_حد_بندی_رجسٹر_At_System_Call_اندراج ) );
            }
            #جے_انت

            /* Use the pulSystemCallStack in thread mode. */
            __asm متطاير ( "msr psp, %0" : : "r" ( pul_System_Call_ڈھیر ) );
            #إذا ( پورٹ_USE_PSPLIM_رجسٹر == 1 )
            {
                __asm متطاير ( "msr psplim, %0" : : "r" ( pxMpuSettings->x_System_Call_ڈھیر_Info.pul_System_Call_ڈھیر_حد_بندی ) );
            }
            #جے_انت

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_ڈھیر[ پورٹ_وتھ_منزل_PC ] = uxSystemCallImplementations[ uc_System_Call_نمبر ];

            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_ڈھیر[ پورٹ_وتھ_منزل_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر = pul_Task_ڈھیر + ul_Hardware_Saved_Exception_چوکھٹا_ناپ;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            إذا( ( pul_Task_ڈھیر[ پورٹ_وتھ_منزل_PSR ] & پورٹ_PSR_ڈھیر_PADDING_نقاب ) == پورٹ_PSR_ڈھیر_PADDING_نقاب )
            {
                pxMpuSettings->ulTaskFlags |= پورٹ_ڈھیر_چوکھٹا_HAS_PADDING_FLAG;
            }
            وإلا
            {
                pxMpuSettings->ulTaskFlags &= ( ~پورٹ_ڈھیر_چوکھٹا_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_ڈھیر[ پورٹ_وتھ_منزل_PSR ] &= ( ~پورٹ_PSR_ڈھیر_PADDING_نقاب );

            /* Raise the privilege for the duration of the system call. */
            __asm متطاير (
                " mrs r0, control     \n" /* Obtain current control value. */
                " movs r1, #1         \n" /* r1 = 1. */
                " bics r0, r1         \n" /* Clear nPRIV bit. */
                " msr control, r0     \n" /* Write back new control value. */
                ::: "r0", "r1", "memory"
                );
        }
    }

#جے_انت /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    فراغ vRequestSystemCallExit( فراغ ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm متطاير ( "svc %0 \n" ::"i" ( پورٹ_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#جے_انت /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    فراغ vSystemCallExit( uint32_t * pul_System_Call_ڈھیر,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        خارجي TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_ڈھیر;
        uint32_t ul_Hardware_Saved_Exception_چوکھٹا_ناپ, ulSystemCallLocation, i;

        #إذا defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint32_t * __privileged_functions_start__;
            خارجي uint32_t * __privileged_functions_end__;
        #وإلا
            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint32_t __privileged_functions_start__[];
            خارجي uint32_t __privileged_functions_end__[];
        #جے_انت /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_ڈھیر[ پورٹ_وتھ_منزل_PC ];
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
        إذا( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر != عدم ) )
        {
            pul_Task_ڈھیر = pxMpuSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            #إذا ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )
            {
                إذا( ( ulLR & پورٹ_EXC_RETURN_ڈھیر_چوکھٹا_TYPE_نقاب ) == 0UL )
                {
                    /* Extended frame i.e. FPU in use. */
                    ul_Hardware_Saved_Exception_چوکھٹا_ناپ = 26;
                    __asm متطاير (
                        " vpush {s0}         \n" /* Trigger lazy stacking. */
                        " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                        ::: "memory"
                        );
                }
                وإلا
                {
                    /* Standard frame i.e. FPU not in use. */
                    ul_Hardware_Saved_Exception_چوکھٹا_ناپ = 8;
                }
            }
            #وإلا /* if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */
            {
                ul_Hardware_Saved_Exception_چوکھٹا_ناپ = 8;
            }
            #جے_انت /* configENABLE_FPU || configENABLE_MVE */

            /* Make space on the task stack for the stack frame. */
            pul_Task_ڈھیر = pul_Task_ڈھیر - ul_Hardware_Saved_Exception_چوکھٹا_ناپ;

            /* Copy the stack frame. */
            لكل( i = 0; i < ul_Hardware_Saved_Exception_چوکھٹا_ناپ; i++ )
            {
                pul_Task_ڈھیر[ i ] = pul_System_Call_ڈھیر[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm متطاير ( "msr psp, %0" : : "r" ( pul_Task_ڈھیر ) );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_ڈھیر[ پورٹ_وتھ_منزل_PC ] = pxMpuSettings->x_System_Call_ڈھیر_Info.ul_Link_رجسٹر_At_System_Call_اندراج;
            /* Ensure that LR has a valid value.*/
            pul_Task_ڈھیر[ پورٹ_وتھ_منزل_LR ] = pxMpuSettings->x_System_Call_ڈھیر_Info.ul_Link_رجسٹر_At_System_Call_اندراج;

            /* Restore the PSPLIM register to what it was at the time of
             * system call entry. */
            #إذا ( پورٹ_USE_PSPLIM_رجسٹر == 1 )
            {
                __asm متطاير ( "msr psplim, %0" : : "r" ( pxMpuSettings->x_System_Call_ڈھیر_Info.ul_ڈھیر_حد_بندی_رجسٹر_At_System_Call_اندراج ) );
            }
            #جے_انت

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            إذا( ( pxMpuSettings->ulTaskFlags & پورٹ_ڈھیر_چوکھٹا_HAS_PADDING_FLAG ) == پورٹ_ڈھیر_چوکھٹا_HAS_PADDING_FLAG )
            {
                pul_Task_ڈھیر[ پورٹ_وتھ_منزل_PSR ] |= پورٹ_PSR_ڈھیر_PADDING_نقاب;
            }
            وإلا
            {
                pul_Task_ڈھیر[ پورٹ_وتھ_منزل_PSR ] &= ( ~پورٹ_PSR_ڈھیر_PADDING_نقاب );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر = عدم;

            /* Drop the privilege before returning to the thread mode. */
            __asm متطاير (
                " mrs r0, control     \n" /* Obtain current control value. */
                " movs r1, #1         \n" /* r1 = 1. */
                " orrs r0, r1         \n" /* Set nPRIV bit. */
                " msr control, r0     \n" /* Write back new control value. */
                ::: "r0", "r1", "memory"
                );
        }
    }

#جے_انت /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    ادھار_Type_t x_پورٹ_Is_Task_Privileged( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        ادھار_Type_t xTaskIsPrivileged = pdFALSE;
        ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( عدم ); /* Calling task's MPU settings. */

        إذا( ( xTaskMpuSettings->ulTaskFlags & پورٹ_TASK_IS_PRIVILEGED_FLAG ) == پورٹ_TASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        أرجع xTaskIsPrivileged;
    }

#جے_انت /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                         ڈھیر_Type_t * px_سرا_دا_ڈھیر,
                                         TaskFunction_t px_کوڈ,
                                         فراغ * pvParameters,
                                         ادھار_Type_t x_لگاتار_Privileged,
                                         xMPU_SETTINGS * xMPUSettings ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_اشاریہ = 0;
        uint32_t ulControl = 0x0;

        xMPUSettings->ulContext[ ul_اشاریہ ] = 0x04040404; /* r4. */
        ul_اشاریہ++;
        xMPUSettings->ulContext[ ul_اشاریہ ] = 0x05050505; /* r5. */
        ul_اشاریہ++;
        xMPUSettings->ulContext[ ul_اشاریہ ] = 0x06060606; /* r6. */
        ul_اشاریہ++;
        xMPUSettings->ulContext[ ul_اشاریہ ] = 0x07070707; /* r7. */
        ul_اشاریہ++;
        xMPUSettings->ulContext[ ul_اشاریہ ] = 0x08080808; /* r8. */
        ul_اشاریہ++;
        xMPUSettings->ulContext[ ul_اشاریہ ] = 0x09090909; /* r9. */
        ul_اشاریہ++;
        xMPUSettings->ulContext[ ul_اشاریہ ] = 0x10101010; /* r10. */
        ul_اشاریہ++;
        xMPUSettings->ulContext[ ul_اشاریہ ] = 0x11111111; /* r11. */
        ul_اشاریہ++;

        xMPUSettings->ulContext[ ul_اشاریہ ] = ( uint32_t ) pvParameters; /* r0. */
        ul_اشاریہ++;
        xMPUSettings->ulContext[ ul_اشاریہ ] = 0x01010101; /* r1. */
        ul_اشاریہ++;
        xMPUSettings->ulContext[ ul_اشاریہ ] = 0x02020202; /* r2. */
        ul_اشاریہ++;
        xMPUSettings->ulContext[ ul_اشاریہ ] = 0x03030303; /* r3. */
        ul_اشاریہ++;
        xMPUSettings->ulContext[ ul_اشاریہ ] = 0x12121212; /* r12. */
        ul_اشاریہ++;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( uint32_t ) پورٹ_TASK_RETURN_پتہ; /* LR. */
        ul_اشاریہ++;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( uint32_t ) px_کوڈ; /* PC. */
        ul_اشاریہ++;
        xMPUSettings->ulContext[ ul_اشاریہ ] = پورٹ_INITIAL_XPSR; /* xPSR. */
        ul_اشاریہ++;

        #إذا ( configENABLE_TRUSTZONE == 1 )
        {
            xMPUSettings->ulContext[ ul_اشاریہ ] = پورٹ_NO_SECURE_CONTEXT; /* xSecureContext. */
            ul_اشاریہ++;
        }
        #جے_انت /* configENABLE_TRUSTZONE */
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( uint32_t ) ( px_چوٹی_دا_ڈھیر - 8 ); /* PSP with the hardware saved stack. */
        ul_اشاریہ++;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( uint32_t ) px_سرا_دا_ڈھیر; /* PSPLIM. */
        ul_اشاریہ++;

        #إذا ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
        {
            /* Check PACBTI security feature configuration before pushing the
             * CONTROL register's value on task's TCB. */
            #إذا ( config_نمبر_دا_CORES == 1 )
                ulControl = prvConfigurePACBTI( pdFALSE );
            #وإلا /* configNUMBER_OF_CORES > 1 */
                ulControl = vConfigurePACBTI( pdFALSE );
            #جے_انت /* configNUMBER_OF_CORES */
        }
        #جے_انت /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

        إذا( x_لگاتار_Privileged == pdTRUE )
        {
            xMPUSettings->ulTaskFlags |= پورٹ_TASK_IS_PRIVILEGED_FLAG;
            xMPUSettings->ulContext[ ul_اشاریہ ] = ( ulControl | ( uint32_t ) پورٹ_INITIAL_CONTROL_PRIVILEGED ); /* CONTROL. */
            ul_اشاریہ++;
        }
        وإلا
        {
            xMPUSettings->ulTaskFlags &= ( ~پورٹ_TASK_IS_PRIVILEGED_FLAG );
            xMPUSettings->ulContext[ ul_اشاریہ ] = ( ulControl | ( uint32_t ) پورٹ_INITIAL_CONTROL_UNPRIVILEGED ); /* CONTROL. */
            ul_اشاریہ++;
        }

        xMPUSettings->ulContext[ ul_اشاریہ ] = پورٹ_INITIAL_EXC_RETURN; /* LR (EXC_RETURN). */
        ul_اشاریہ++;

        #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
        {
            /* Ensure that the system call stack is double word aligned. */
            xMPUSettings->x_System_Call_ڈھیر_Info.pul_System_Call_ڈھیر = &( xMPUSettings->x_System_Call_ڈھیر_Info.ul_System_Call_ڈھیر_بفر[ config_SYSTEM_CALL_ڈھیر_ناپ - 1 ] );
            xMPUSettings->x_System_Call_ڈھیر_Info.pul_System_Call_ڈھیر = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_ڈھیر_Info.pul_System_Call_ڈھیر ) &
                                                                                     ( uint32_t ) ( ~( پورٹ_BYTE_ALIGNMENT_نقاب ) ) );

            xMPUSettings->x_System_Call_ڈھیر_Info.pul_System_Call_ڈھیر_حد_بندی = &( xMPUSettings->x_System_Call_ڈھیر_Info.ul_System_Call_ڈھیر_بفر[ 0 ] );
            xMPUSettings->x_System_Call_ڈھیر_Info.pul_System_Call_ڈھیر_حد_بندی = ( uint32_t * ) ( ( ( uint32_t ) ( xMPUSettings->x_System_Call_ڈھیر_Info.pul_System_Call_ڈھیر_حد_بندی ) +
                                                                                            ( uint32_t ) ( پورٹ_BYTE_ALIGNMENT - 1 ) ) &
                                                                                          ( uint32_t ) ( ~( پورٹ_BYTE_ALIGNMENT_نقاب ) ) );

            /* This is not NULL only for the duration of a system call. */
            xMPUSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر = عدم;
        }
        #جے_انت /* configUSE_MPU_WRAPPERS_V1 == 0 */

        #إذا ( configENABLE_PAC == 1 )
        {
            uint32_t ul_Task_Pac_کلید[ 4 ], i;

            v_Application_Generate_Task_Random_Pac_کلید( &( ul_Task_Pac_کلید[ 0 ] ) );

            لكل( i = 0; i < 4; i++ )
            {
                xMPUSettings->ulContext[ ul_اشاریہ ] = ul_Task_Pac_کلید[ i ];
                ul_اشاریہ++;
            }
        }
        #جے_انت /* configENABLE_PAC */

        أرجع &( xMPUSettings->ulContext[ ul_اشاریہ ] );
    }

#وإلا /* configENABLE_MPU */

    ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                         ڈھیر_Type_t * px_سرا_دا_ڈھیر,
                                         TaskFunction_t px_کوڈ,
                                         فراغ * pvParameters ) /* PRIVILEGED_FUNCTION */
    {
        /* Simulate the stack frame as it would be created by a context switch
         * interrupt. */
        #إذا ( پورٹ_PRELOAD_REGISTERS == 0 )
        {
            px_چوٹی_دا_ڈھیر--; /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_چوٹی_دا_ڈھیر = پورٹ_INITIAL_XPSR; /* xPSR. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) px_کوڈ; /* PC. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_TASK_RETURN_پتہ; /* LR. */
            px_چوٹی_دا_ڈھیر -= 5; /* R12, R3, R2 and R1. */
            *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) pvParameters; /* R0. */
            px_چوٹی_دا_ڈھیر -= 9; /* R11..R4, EXC_RETURN. */
            *px_چوٹی_دا_ڈھیر = پورٹ_INITIAL_EXC_RETURN;
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) px_سرا_دا_ڈھیر; /* Slot used to hold this task's PSPLIM value. */

            #إذا ( configENABLE_TRUSTZONE == 1 )
            {
                px_چوٹی_دا_ڈھیر--;
                *px_چوٹی_دا_ڈھیر = پورٹ_NO_SECURE_CONTEXT; /* Slot used to hold this task's xSecureContext value. */
            }
            #جے_انت /* configENABLE_TRUSTZONE */
        }
        #وإلا /* portPRELOAD_REGISTERS */
        {
            px_چوٹی_دا_ڈھیر--; /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_چوٹی_دا_ڈھیر = پورٹ_INITIAL_XPSR; /* xPSR. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) px_کوڈ; /* PC. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_TASK_RETURN_پتہ; /* LR. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x12121212UL; /* R12. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x03030303UL; /* R3. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x02020202UL; /* R2. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x01010101UL; /* R1. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) pvParameters; /* R0. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x11111111UL; /* R11. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x10101010UL; /* R10. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x09090909UL; /* R09. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x08080808UL; /* R08. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x07070707UL; /* R07. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x06060606UL; /* R06. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x05050505UL; /* R05. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x04040404UL; /* R04. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = پورٹ_INITIAL_EXC_RETURN; /* EXC_RETURN. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) px_سرا_دا_ڈھیر; /* Slot used to hold this task's PSPLIM value. */

            #إذا ( configENABLE_TRUSTZONE == 1 )
            {
                px_چوٹی_دا_ڈھیر--;
                *px_چوٹی_دا_ڈھیر = پورٹ_NO_SECURE_CONTEXT; /* Slot used to hold this task's xSecureContext value. */
            }
            #جے_انت /* configENABLE_TRUSTZONE */
        }
        #جے_انت /* portPRELOAD_REGISTERS */

        #إذا ( configENABLE_PAC == 1 )
        {
            uint32_t ul_Task_Pac_کلید[ 4 ], i;

            v_Application_Generate_Task_Random_Pac_کلید( &( ul_Task_Pac_کلید[ 0 ] ) );

            لكل( i = 0; i < 4; i++ )
            {
                px_چوٹی_دا_ڈھیر--;
                *px_چوٹی_دا_ڈھیر = ul_Task_Pac_کلید[ i ];
            }
        }
        #جے_انت /* configENABLE_PAC */

        أرجع px_چوٹی_دا_ڈھیر;
    }

#جے_انت /* configENABLE_MPU */
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ ) /* PRIVILEGED_FUNCTION */
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
    #إذا ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        ثابت پورٹ_ISR_t * ثابت px_سمتیہ_جدول = پورٹ_SCB_VTOR_REG;

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
        configASSERT( px_سمتیہ_جدول[ پورٹ_سمتیہ_اشاریہ_SVC ] == SVC_Handler );
        configASSERT( px_سمتیہ_جدول[ پورٹ_سمتیہ_اشاریہ_PENDSV ] == PendSV_Handler );
    }
    #جے_انت /* configCHECK_HANDLER_INSTALLATION */

    v_پورٹ_Configure_رکاوٹ_Priorities();

    #إذا ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
    {
        /* Set the CONTROL register value based on PACBTI security feature
         * configuration before starting the first task. */
        #إذا ( config_نمبر_دا_CORES == 1 )
            ( فراغ ) prvConfigurePACBTI( pdTRUE );
        #وإلا /* configNUMBER_OF_CORES > 1 */
            ( فراغ ) vConfigurePACBTI( pdTRUE );
        #جے_انت /* configNUMBER_OF_CORES */
    }
    #جے_انت /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

    #إذا ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        prv_تیاری_MPU();
    }
    #جے_انت /* configENABLE_MPU */

    #إذا ( config_نمبر_دا_CORES > 1 )
        /* Start the timer that generates the tick ISR. Interrupts are disabled
         * here already. */
        v_پورٹ_تیاری_Timer_رکاوٹ();
        /* Initialize the critical nesting count for all cores. */
        لكل ( uint8_t ucCoreID = 0; ucCoreID < config_نمبر_دا_CORES; ucCoreID++ )
        {
            ulCriticalNestings[ ucCoreID ] = 0;
        }
        /* Signal that primary core has done all the necessary initialisations. */
        uc_Primary_Core_Init_پورا_Flag = 1;
        /* Wake up secondary cores */
        ادھار_Type_t x_Wake_نتیجہ = configWAKE_SECONDARY_CORES();
        configASSERT( x_Wake_نتیجہ == pdTRUE );

        /* Hold the primary core here until all the secondary cores are ready, this would be achieved only when
         * all elements of ucSecondaryCoresReadyFlags are set.
         */
        طالما( 1 )
        {
            ادھار_Type_t xAllCoresReady = pdTRUE;
            لكل( uint8_t ucCoreID = 0; ucCoreID < ( config_نمبر_دا_CORES - 1 ); ucCoreID++ )
            {
                إذا( ucSecondaryCoresReadyFlags[ ucCoreID ] != pdTRUE )
                {
                    xAllCoresReady = pdFALSE;
                    اكسر;
                }
                }

            إذا ( xAllCoresReady == pdTRUE )
            {
                اكسر;
            }
        }
    #وإلا /* if ( configNUMBER_OF_CORES > 1 ) */
        /* Start the timer that generates the tick ISR. */
        v_پورٹ_تیاری_Timer_رکاوٹ();
        /* Initialize the critical nesting count ready for the first task. */
        ulCriticalNesting = 0;
    #جے_انت /* if ( configNUMBER_OF_CORES > 1 ) */

    #إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )
    {
        xSchedulerRunning = pdTRUE;
    }
    #جے_انت /* ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

    /* Start the first task. */
    v_شروع_پہلا_Task();

    /* Should never get here as the tasks will now be executing. Call the task
     * exit error function to prevent compiler warnings about a static function
     * not being called in the case that the application writer overrides this
     * functionality by defining configTASK_RETURN_ADDRESS. Call
     * vTaskSwitchContext() so link time optimization does not remove the
     * symbol. */
    #إذا ( config_نمبر_دا_CORES > 1 )
        vTaskSwitchContext( پورٹ_GET_CORE_ID() );
    #وإلا
        vTaskSwitchContext();
    #جے_انت
    prvTaskExitError();

    /* Should not get here. */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ ) /* PRIVILEGED_FUNCTION */
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    #إذا ( config_نمبر_دا_CORES == 1 )
        configASSERT( ulCriticalNesting == 1000UL );
    #وإلا /* if ( configNUMBER_OF_CORES == 1 ) */
        configASSERT( ulCriticalNestings[ پورٹ_GET_CORE_ID() ] == 1000UL );
    #جے_انت /* if ( configNUMBER_OF_CORES == 1 ) */
}
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    فراغ v_پورٹ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ثابت بنية x_حافظہ_REGION * ثابت xRegions,
                                    ڈھیر_Type_t * px_Bottom_دا_ڈھیر,
                                    config_ڈھیر_ڈونگھائی_TYPE ux_ڈھیر_ڈونگھائی )
    {
        uint32_t ul_Region_شروع_پتہ, ul_Region_سرا_پتہ, ul_Region_نمبر;
        int32_t l_اشاریہ = 0;

        #إذا defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint32_t * __privileged_sram_start__;
            خارجي uint32_t * __privileged_sram_end__;
        #وإلا
            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint32_t __privileged_sram_start__[];
            خارجي uint32_t __privileged_sram_end__[];
        #جے_انت /* defined( __ARMCC_VERSION ) */

        /* Setup MAIR0. */
        xMPUSettings->ulMAIR0 = ( ( پورٹ_MPU_عام_حافظہ_BUFFERABLE_CACHEABLE << پورٹ_MPU_MAIR_ATTR0_POS ) & پورٹ_MPU_MAIR_ATTR0_نقاب );
        xMPUSettings->ulMAIR0 |= ( ( پورٹ_MPU_DEVICE_حافظہ_n_Gn_RE << پورٹ_MPU_MAIR_ATTR1_POS ) & پورٹ_MPU_MAIR_ATTR1_نقاب );

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid.  At all other
         * times the stack parameters will not be valid and it is assumed that
         * the stack region has already been configured. */
        إذا( ux_ڈھیر_ڈونگھائی > 0 )
        {
            ul_Region_شروع_پتہ = ( uint32_t ) px_Bottom_دا_ڈھیر;
            ul_Region_سرا_پتہ = ( uint32_t ) px_Bottom_دا_ڈھیر + ( ux_ڈھیر_ڈونگھائی * ( config_ڈھیر_ڈونگھائی_TYPE ) حجم( ڈھیر_Type_t ) ) - 1;

            /* If the stack is within the privileged SRAM, do not protect it
             * using a separate MPU region. This is needed because privileged
             * SRAM is already protected using an MPU region and ARMv8-M does
             * not allow overlapping MPU regions. */
            إذا( ( ul_Region_شروع_پتہ >= ( uint32_t ) __privileged_sram_start__ ) &&
                ( ul_Region_سرا_پتہ <= ( uint32_t ) __privileged_sram_end__ ) )
            {
                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR = 0;
                xMPUSettings->xRegionsSettings[ 0 ].ulRLAR = 0;
            }
            وإلا
            {
                /* Define the region that allows access to the stack. */
                ul_Region_شروع_پتہ &= پورٹ_MPU_RBAR_پتہ_نقاب;
                ul_Region_سرا_پتہ &= پورٹ_MPU_RLAR_پتہ_نقاب;

                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR = ( ul_Region_شروع_پتہ ) |
                                                             ( پورٹ_MPU_REGION_NON_SHAREABLE ) |
                                                             ( پورٹ_MPU_REGION_READ_WRITE ) |
                                                             ( پورٹ_MPU_REGION_EXECUTE_NEVER );

                xMPUSettings->xRegionsSettings[ 0 ].ulRLAR = ( ul_Region_سرا_پتہ ) |
                                                             ( پورٹ_MPU_RLAR_ATTR_INDEX0 ) |
                                                             ( پورٹ_MPU_RLAR_REGION_ENABLE );
            }
        }

        /* User supplied configurable regions. */
        لكل( ul_Region_نمبر = 1; ul_Region_نمبر <= پورٹ_عدد_CONFIGURABLE_REGIONS; ul_Region_نمبر++ )
        {
            /* If xRegions is NULL i.e. the task has not specified any MPU
             * region, the else part ensures that all the configurable MPU
             * regions are invalidated. */
            إذا( ( xRegions != عدم ) && ( xRegions[ l_اشاریہ ].ul_لمائی_وچ_بائٹاں > 0UL ) )
            {
                /* Translate the generic region definition contained in xRegions
                 * into the ARMv8 specific MPU settings that are then stored in
                 * xMPUSettings. */
                ul_Region_شروع_پتہ = ( ( uint32_t ) xRegions[ l_اشاریہ ].pv_ادھار_پتہ ) & پورٹ_MPU_RBAR_پتہ_نقاب;
                ul_Region_سرا_پتہ = ( uint32_t ) xRegions[ l_اشاریہ ].pv_ادھار_پتہ + xRegions[ l_اشاریہ ].ul_لمائی_وچ_بائٹاں - 1;
                ul_Region_سرا_پتہ &= پورٹ_MPU_RLAR_پتہ_نقاب;

                /* Start address. */
                xMPUSettings->xRegionsSettings[ ul_Region_نمبر ].ulRBAR = ( ul_Region_شروع_پتہ ) |
                                                                          ( پورٹ_MPU_REGION_NON_SHAREABLE );

                /* RO/RW. */
                إذا( ( xRegions[ l_اشاریہ ].ulParameters & tskMPU_REGION_READ_ONLY ) != 0 )
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_نمبر ].ulRBAR |= ( پورٹ_MPU_REGION_READ_ONLY );
                }
                وإلا
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_نمبر ].ulRBAR |= ( پورٹ_MPU_REGION_READ_WRITE );
                }

                /* XN. */
                إذا( ( xRegions[ l_اشاریہ ].ulParameters & tskMPU_REGION_EXECUTE_NEVER ) != 0 )
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_نمبر ].ulRBAR |= ( پورٹ_MPU_REGION_EXECUTE_NEVER );
                }

                /* End Address. */
                xMPUSettings->xRegionsSettings[ ul_Region_نمبر ].ulRLAR = ( ul_Region_سرا_پتہ ) |
                                                                          ( پورٹ_MPU_RLAR_REGION_ENABLE );

                /* PXN. */
                #إذا ( پورٹ_ARMV8_M_MINOR_نسخہ >= 1 )
                {
                    إذا( ( xRegions[ l_اشاریہ ].ulParameters & tskMPU_REGION_PRIVILEGED_EXECUTE_NEVER ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ ul_Region_نمبر ].ulRLAR |= ( پورٹ_MPU_RLAR_PRIVILEGED_EXECUTE_NEVER );
                    }
                }
                #جے_انت /* portARMV8M_MINOR_VERSION >= 1 */

                /* Normal memory/ Device memory. */
                إذا( ( xRegions[ l_اشاریہ ].ulParameters & tsk_MPU_REGION_DEVICE_حافظہ ) != 0 )
                {
                    /* Attr1 in MAIR0 is configured as device memory. */
                    xMPUSettings->xRegionsSettings[ ul_Region_نمبر ].ulRLAR |= پورٹ_MPU_RLAR_ATTR_INDEX1;
                }
                وإلا
                {
                    /* Attr0 in MAIR0 is configured as normal memory. */
                    xMPUSettings->xRegionsSettings[ ul_Region_نمبر ].ulRLAR |= پورٹ_MPU_RLAR_ATTR_INDEX0;
                }
            }
            وإلا
            {
                /* Invalidate the region. */
                xMPUSettings->xRegionsSettings[ ul_Region_نمبر ].ulRBAR = 0UL;
                xMPUSettings->xRegionsSettings[ ul_Region_نمبر ].ulRLAR = 0UL;
            }

            l_اشاریہ++;
        }
    }

#جے_انت /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ادھار_Type_t x_پورٹ_Is_Authorized_منزل_Access_بفر( ثابت فراغ * pv_بفر,
                                                size_t x_بفر_لمائی,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_بفر_شروع_پتہ, ul_بفر_سرا_پتہ;
        ادھار_Type_t xAccessGranted = pdFALSE;
        ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( عدم ); /* Calling task's MPU settings. */

        إذا( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        وإلا إذا( ( xTaskMpuSettings->ulTaskFlags & پورٹ_TASK_IS_PRIVILEGED_FLAG ) == پورٹ_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        وإلا
        {
            إذا( پورٹ_جوڑو_UINT32_WILL_حد_توں_ودھ( ( ( uint32_t ) pv_بفر ), ( ( uint32_t ) x_بفر_لمائی - 1UL ) ) == pdFALSE )
            {
                ul_بفر_شروع_پتہ = ( uint32_t ) pv_بفر;
                ul_بفر_سرا_پتہ = ( ( ( uint32_t ) pv_بفر ) + ( uint32_t ) x_بفر_لمائی - 1UL );

                لكل( i = 0; i < پورٹ_کل_عدد_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    إذا( ( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR & پورٹ_MPU_RLAR_REGION_ENABLE ) == پورٹ_MPU_RLAR_REGION_ENABLE )
                    {
                        إذا( پورٹ_IS_پتہ_WITHIN_RANGE( ul_بفر_شروع_پتہ,
                                                         پورٹ_کڈھو_پہلا_پتہ_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ),
                                                         پورٹ_کڈھو_آخری_پتہ_FROM_RLAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR ) ) &&
                            پورٹ_IS_پتہ_WITHIN_RANGE( ul_بفر_سرا_پتہ,
                                                         پورٹ_کڈھو_پہلا_پتہ_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ),
                                                         پورٹ_کڈھو_آخری_پتہ_FROM_RLAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR ) ) &&
                            پورٹ_IS_AUTHORIZED( ulAccessRequested,
                                               prvGetRegionAccessPermissions( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ) ) )
                        {
                            xAccessGranted = pdTRUE;
                            اكسر;
                        }
                    }
                }
            }
        }

        أرجع xAccessGranted;
    }

#جے_انت /* #if ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_Is_Inside_رکاوٹ( فراغ )
{
    uint32_t ul_Current_رکاوٹ;
    ادھار_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. Interrupt Program
     * Status Register (IPSR) holds the exception number of the currently-executing
     * exception or zero for Thread mode.*/
    __asm متطاير ( "mrs %0, ipsr" : "=r" ( ul_Current_رکاوٹ )::"memory" );

    إذا( ul_Current_رکاوٹ == 0 )
    {
        xReturn = pdFALSE;
    }
    وإلا
    {
        xReturn = pdTRUE;
    }

    أرجع xReturn;
}
/*-----------------------------------------------------------*/

#إذا ( ( configASSERT_DEFINED == 1 ) && ( پورٹ_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) )

    فراغ v_پورٹ_Validate_رکاوٹ_ترجیح( فراغ )
    {
        uint32_t ul_Current_رکاوٹ;
        uint8_t uc_Current_ترجیح;

        /* Obtain the number of the currently executing interrupt. */
        __asm متطاير ( "mrs %0, ipsr" : "=r" ( ul_Current_رکاوٹ )::"memory" );

        /* Is the interrupt number a user defined interrupt? */
        إذا( ul_Current_رکاوٹ >= پورٹ_پہلا_USER_رکاوٹ_نمبر )
        {
            /* Look up the interrupt's priority. */
            uc_Current_ترجیح = pc_رکاوٹ_ترجیح_Registers[ ul_Current_رکاوٹ ];

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
            configASSERT( uc_Current_ترجیح >= uc_Max_Sys_Call_ترجیح );
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
        configASSERT( ( پورٹ_AIRCR_REG & پورٹ_ترجیح_گروہ_نقاب ) <= ulMaxPRIGROUPValue );
    }

#جے_انت /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Configure_رکاوٹ_Priorities( فراغ ) /* PRIVILEGED_FUNCTION */
{
    #إذا ( ( configASSERT_DEFINED == 1 ) && ( پورٹ_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) )
    {
        متطاير uint32_t ul_Implemented_Prio_بٹ = 0;
        متطاير uint8_t uc_Max_ترجیح_قدر;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
        * functions can be called. ISR safe functions are those that end in
        * "FromISR". FreeRTOS maintains separate thread and ISR API functions to
        * ensure interrupt entry is as fast and simple as possible.
        *
        * First, determine the number of priority bits available. Write to all
        * possible bits in the priority setting for SVCall. */
        پورٹ_NVIC_SHPR2_REG = 0xFF000000;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ترجیح_قدر = ( uint8_t ) ( ( پورٹ_NVIC_SHPR2_REG & 0xFF000000 ) >> 24 );

        /* Use the same mask on the maximum system call priority. */
        uc_Max_Sys_Call_ترجیح = config_MAX_SYSCALL_رکاوٹ_ترجیح & uc_Max_ترجیح_قدر;

        /* Check that the maximum system call priority is nonzero after
        * accounting for the number of priority bits supported by the
        * hardware. A priority of 0 is invalid because setting the BASEPRI
        * register to 0 unmasks all interrupts, and interrupts with priority 0
        * cannot be masked using BASEPRI.
        * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( uc_Max_Sys_Call_ترجیح );

        /* Check that the bits not implemented in hardware are zero in
        * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( config_MAX_SYSCALL_رکاوٹ_ترجیح & ( uint8_t ) ( ~( uint32_t ) uc_Max_ترجیح_قدر ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
        * of bits read back. */
        طالما( ( uc_Max_ترجیح_قدر & پورٹ_چوٹی_ثنائی_ہندسہ_دا_BYTE ) == پورٹ_چوٹی_ثنائی_ہندسہ_دا_BYTE )
        {
            ul_Implemented_Prio_بٹ++;
            uc_Max_ترجیح_قدر <<= ( uint8_t ) 0x01;
        }

        إذا( ul_Implemented_Prio_بٹ == 8 )
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
            configASSERT( ( config_MAX_SYSCALL_رکاوٹ_ترجیح & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        وإلا
        {
            ulMaxPRIGROUPValue = پورٹ_MAX_PRIGROUP_بٹ - ul_Implemented_Prio_بٹ;
        }

        /* Shift the priority group value back to its position within the AIRCR
        * register. */
        ulMaxPRIGROUPValue <<= پورٹ_PRIGROUP_کھسکاؤ;
        ulMaxPRIGROUPValue &= پورٹ_ترجیح_گروہ_نقاب;
    }
    #جے_انت /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */

    /* Make PendSV and SysTick the lowest priority interrupts, and make SVCall
    * the highest priority. */
    پورٹ_NVIC_SHPR3_REG |= پورٹ_NVIC_PENDSV_PRI;
    پورٹ_NVIC_SHPR3_REG |= پورٹ_NVIC_SYSTICK_PRI;
    پورٹ_NVIC_SHPR2_REG = 0;
}
/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    فراغ v_پورٹ_Grant_Access_منزل_Kernel_Object( TaskHandle_t x_اندرونی_Task_Handle,
                                         int32_t l_اندرونی_اشاریہ_دا_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_اندراج_اشاریہ, ul_Access_Control_List_اندراج_ثنائی_ہندسہ;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_اندراج_اشاریہ = ( ( uint32_t ) l_اندرونی_اشاریہ_دا_Kernel_Object / پورٹ_ACL_اندراج_ناپ_بٹ );
        ul_Access_Control_List_اندراج_ثنائی_ہندسہ = ( ( uint32_t ) l_اندرونی_اشاریہ_دا_Kernel_Object % پورٹ_ACL_اندراج_ناپ_بٹ );

        xTaskMpuSettings = xTaskGetMPUSettings( x_اندرونی_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_اندراج_اشاریہ ] |= ( 1U << ul_Access_Control_List_اندراج_ثنائی_ہندسہ );
    }

#جے_انت /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    فراغ v_پورٹ_Revoke_Access_منزل_Kernel_Object( TaskHandle_t x_اندرونی_Task_Handle,
                                          int32_t l_اندرونی_اشاریہ_دا_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_اندراج_اشاریہ, ul_Access_Control_List_اندراج_ثنائی_ہندسہ;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_اندراج_اشاریہ = ( ( uint32_t ) l_اندرونی_اشاریہ_دا_Kernel_Object / پورٹ_ACL_اندراج_ناپ_بٹ );
        ul_Access_Control_List_اندراج_ثنائی_ہندسہ = ( ( uint32_t ) l_اندرونی_اشاریہ_دا_Kernel_Object % پورٹ_ACL_اندراج_ناپ_بٹ );

        xTaskMpuSettings = xTaskGetMPUSettings( x_اندرونی_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_اندراج_اشاریہ ] &= ~( 1U << ul_Access_Control_List_اندراج_ثنائی_ہندسہ );
    }

#جے_انت /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        ادھار_Type_t x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( int32_t l_اندرونی_اشاریہ_دا_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_اندراج_اشاریہ, ul_Access_Control_List_اندراج_ثنائی_ہندسہ;
            ادھار_Type_t xAccessGranted = pdFALSE;
            ثابت xMPU_SETTINGS * xTaskMpuSettings;

            إذا( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            وإلا
            {
                xTaskMpuSettings = xTaskGetMPUSettings( عدم ); /* Calling task's MPU settings. */

                ul_Access_Control_List_اندراج_اشاریہ = ( ( uint32_t ) l_اندرونی_اشاریہ_دا_Kernel_Object / پورٹ_ACL_اندراج_ناپ_بٹ );
                ul_Access_Control_List_اندراج_ثنائی_ہندسہ = ( ( uint32_t ) l_اندرونی_اشاریہ_دا_Kernel_Object % پورٹ_ACL_اندراج_ناپ_بٹ );

                إذا( ( xTaskMpuSettings->ulTaskFlags & پورٹ_TASK_IS_PRIVILEGED_FLAG ) == پورٹ_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                وإلا
                {
                    إذا( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_اندراج_اشاریہ ] & ( 1U << ul_Access_Control_List_اندراج_ثنائی_ہندسہ ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            أرجع xAccessGranted;
        }

    #وإلا /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        ادھار_Type_t x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( int32_t l_اندرونی_اشاریہ_دا_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( فراغ ) l_اندرونی_اشاریہ_دا_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            أرجع pdTRUE;
        }

    #جے_انت /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#جے_انت /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */
/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
    #إذا ( config_نمبر_دا_CORES == 1 )
        ساكن uint32_t prvConfigurePACBTI( ادھار_Type_t x_Write_Control_رجسٹر )
    #وإلا /* configNUMBER_OF_CORES > 1 */
        uint32_t vConfigurePACBTI( ادھار_Type_t x_Write_Control_رجسٹر )
    #جے_انت /* configNUMBER_OF_CORES */
        {
            uint32_t ulControl = 0x0;

            /* Ensure that PACBTI is implemented. */
            configASSERT( پورٹ_ID_ISAR5_REG != 0x0 );

            /* Enable UsageFault exception. */
            پورٹ_SCB_SYS_HANDLER_CTRL_STATE_REG |= پورٹ_SCB_USG_FAULT_ENABLE_ثنائی_ہندسہ;

            #إذا ( configENABLE_PAC == 1 )
            {
                ulControl |= ( پورٹ_CONTROL_UPAC_EN | پورٹ_CONTROL_PAC_EN );
            }
            #جے_انت

            #إذا ( configENABLE_BTI == 1 )
            {
                ulControl |= ( پورٹ_CONTROL_UBTI_EN | پورٹ_CONTROL_BTI_EN );
            }
            #جے_انت

            إذا( x_Write_Control_رجسٹر == pdTRUE )
            {
                __asm متطاير ( "msr control, %0" : : "r" ( ulControl ) );
            }

            أرجع ulControl;
        }

#جے_انت /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */
/*-----------------------------------------------------------*/

#إذا ( config_نمبر_دا_CORES > 1 )

    /* Which core owns the lock? */
    PRIVILEGED_انکڑے متطاير uint32_t ulOwnedByCore[ پورٹ_MAX_CORE_گنتی ];
    /* Lock count a core owns. */
    PRIVILEGED_انکڑے متطاير uint32_t ul_Recursion_گنتی_By_جندرا[ e_جندرا_گنتی ];
    /* Index 0 is used for ISR lock and Index 1 is used for task lock. */
    PRIVILEGED_انکڑے متطاير uint32_t ul_Gate_لفظ[ e_جندرا_گنتی ];

    __attribute__((weak)) فراغ v_رکاوٹ_Core( uint8_t ucCoreID )
    {
        /* Default weak stub - platform specific implementation may override. */
        ( فراغ ) ucCoreID;
    }

/*-----------------------------------------------------------*/

    ساكن مضمن فراغ prvSpinUnlock( متطاير uint32_t * ul_جندرا )
    {
        /* Conservative unlock: preserve original barriers for broad HW/FVP. */
        __asm متطاير (
            "dmb sy         \n"
            "mov r1, #0     \n"
            "str r1, [%0]   \n"
            "sev            \n"
            "dsb            \n"
            "isb            \n"
            :
            : "r" ( ul_جندرا )
            : "memory", "r1"
        );
    }

/*-----------------------------------------------------------*/

    ساكن مضمن uint32_t prvSpinTrylock( متطاير uint32_t * ul_جندرا )
    {
        /*
         * Conservative ldrex/strex trylock:
         * - Return 1 immediately if busy, clearing exclusive state (CLREX).
         * - Retry strex only on spurious failure when observed free.
         * - DMB on success to preserve expected acquire semantics.
         */
        uint32_t ulVal;
        uint32_t ul_حالت;

        __asm متطاير (
            " ldrex %0, [%1]   \n"
            : "=r" ( ulVal )
            : "r" ( ul_جندرا )
            : "memory"
        );

        إذا( ulVal != 0U )
        {
            __asm متطاير ("clrex" ::: "memory");
            أرجع 1U;
        }

        __asm متطاير (
            " strex %0, %2, [%1]   \n"
            : "=&r" ( ul_حالت )
            : "r" ( ul_جندرا ), "r" (1U)
            : "memory"
        );

        إذا( ul_حالت != 0U )
        {
            أرجع 1U;
        }
        __asm متطاير ( "dmb" ::: "memory" );
        أرجع 0U;
    }


/*-----------------------------------------------------------*/

    /* Read 32b value shared between cores. */
    ساكن مضمن uint32_t prvGet32( متطاير uint32_t * x )
    {
        __asm( "dsb" );
        أرجع *x;
    }

/*-----------------------------------------------------------*/

    /* Write 32b value shared between cores. */
    ساكن مضمن فراغ prvSet32( متطاير uint32_t * x,
                                 uint32_t قدر )
    {
        *x = قدر;
        __asm( "dsb" );
    }

/*-----------------------------------------------------------*/

    فراغ v_پورٹ_Recursive_جندرا( uint8_t ucCoreID,
                             e_پورٹ_RTOSLock e_جندرا_عدد,
                             ادھار_Type_t uxAcquire )
    {
        /* Validate the core ID and lock number. */
        configASSERT( ucCoreID < پورٹ_MAX_CORE_گنتی );
        configASSERT( e_جندرا_عدد < e_جندرا_گنتی );

        uint32_t ul_جندرا_ثنائی_ہندسہ = 1u << e_جندرا_عدد;

        /* Lock acquire */
        إذا( uxAcquire )
        {
            /* Check if spinlock is available. */
            /* If spinlock is not available check if the core owns the lock. */
            /* If the core owns the lock wait increment the lock count by the core. */
            /* If core does not own the lock wait for the spinlock. */
            إذا( prvSpinTrylock( &ul_Gate_لفظ[ e_جندرا_عدد ] ) != 0 )
            {
                /* Check if the core owns the spinlock. */
                إذا( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ul_جندرا_ثنائی_ہندسہ )
                {
                    configASSERT( prvGet32( &ul_Recursion_گنتی_By_جندرا[ e_جندرا_عدد ] ) != پورٹ_UINT32_MAX );
                    prvSet32( &ul_Recursion_گنتی_By_جندرا[ e_جندرا_عدد ], ( prvGet32( &ul_Recursion_گنتی_By_جندرا[ e_جندرا_عدد ] ) + 1 ) );
                    أرجع;
                }

                /* Preload the gate word into the cache. */
                uint32_t dummy = ul_Gate_لفظ[ e_جندرا_عدد ];
                dummy++;

                طالما( prvSpinTrylock( &ul_Gate_لفظ[ e_جندرا_عدد ] ) != 0 )
                {
                    __asm متطاير ( "wfe" );
                }
            }

            /* Add barrier to ensure lock is taken before we proceed. */
            __asm متطاير( "dmb sy" ::: "memory" );

            /* Assert the lock count is 0 when the spinlock is free and is acquired. */
            configASSERT( prvGet32( &ul_Recursion_گنتی_By_جندرا[ e_جندرا_عدد ] ) == 0 );

            /* Set lock count as 1. */
            prvSet32( &ul_Recursion_گنتی_By_جندرا[ e_جندرا_عدد ], 1 );
            /* Set ulOwnedByCore. */
            prvSet32( &ulOwnedByCore[ ucCoreID ], ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) | ul_جندرا_ثنائی_ہندسہ ) );
        }
        /* Lock release. */
        وإلا
        {
            /* Assert the lock is not free already. */
            configASSERT( ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ul_جندرا_ثنائی_ہندسہ ) != 0 );
            configASSERT( prvGet32( &ul_Recursion_گنتی_By_جندرا[ e_جندرا_عدد ] ) != 0 );

            /* Reduce ulRecursionCountByLock by 1. */
            prvSet32( &ul_Recursion_گنتی_By_جندرا[ e_جندرا_عدد ], ( prvGet32( &ul_Recursion_گنتی_By_جندرا[ e_جندرا_عدد ] ) - 1 ) );

            إذا( !prvGet32( &ul_Recursion_گنتی_By_جندرا[ e_جندرا_عدد ] ) )
            {
                prvSet32( &ulOwnedByCore[ ucCoreID ], ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ~ul_جندرا_ثنائی_ہندسہ ) );
                prvSpinUnlock( &ul_Gate_لفظ[ e_جندرا_عدد ] );
                /* Add barrier to ensure lock status is reflected before we proceed. */
                __asm متطاير( "dmb sy" ::: "memory" );
            }
        }
    }

/*-----------------------------------------------------------*/

    uint8_t uc_پورٹ_Get_Core_ID( فراغ )
    {
        أرجع *(متطاير uint8_t *)(config_CORE_ID_رجسٹر);
    }

/*-----------------------------------------------------------*/

#جے_انت /* if( configNUMBER_OF_CORES > 1 ) */
