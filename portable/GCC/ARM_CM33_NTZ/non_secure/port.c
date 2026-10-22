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
#تعریف_کن MPU_WRAPPERS_INCLUDED_FROM_API_FILE

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
#پایان_اگر /* configENABLE_TRUSTZONE */

#لغو_تعریف MPU_WRAPPERS_INCLUDED_FROM_API_FILE

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
#إذا ( ( config_پیاپی_FREERTOS_SECURE_ONLY == 1 ) && ( configENABLE_TRUSTZONE == 1 ) )
    #خطا TrustZone needs مقصد be disabled درون ترتیب مقصد پیاپی FreeRTOS on the Secure Side.
#پایان_اگر

/**
 * Cortex-M23 does not have non-secure PSPLIM. We should use PSPLIM on Cortex-M23
 * only when FreeRTOS runs on secure side.
 */
#إذا ( ( پورت_HAS_ARMV8_M_MAIN_EXTENSION == 0 ) && ( config_پیاپی_FREERTOS_SECURE_ONLY == 0 ) )
    #تعریف_کن پورت_USE_PSPLIM_ثبات    0
#وإلا
    #تعریف_کن پورت_USE_PSPLIM_ثبات    1
#پایان_اگر
/*-----------------------------------------------------------*/

/**
 * @brief Prototype of all Interrupt Service Routines (ISRs).
 */
تعريفنوع فراغ ( * پورت_ISR_t )( فراغ );
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the NVIC.
 */
#تعریف_کن پورت_NVIC_SYSTICK_CTRL_REG             ( *( ( متطاير uint32_t * ) 0xe000e010 ) )
#تعریف_کن پورت_NVIC_SYSTICK_بارگیری_REG             ( *( ( متطاير uint32_t * ) 0xe000e014 ) )
#تعریف_کن پورت_NVIC_SYSTICK_CURRENT_مقدار_REG    ( *( ( متطاير uint32_t * ) 0xe000e018 ) )
#تعریف_کن پورت_NVIC_SHPR3_REG                    ( *( ( متطاير uint32_t * ) 0xe000ed20 ) )
#تعریف_کن پورت_NVIC_SYSTICK_ENABLE_بیت           ( 1UL << 0UL )
#تعریف_کن پورت_NVIC_SYSTICK_INT_بیت              ( 1UL << 1UL )
#تعریف_کن پورت_NVIC_SYSTICK_CLK_بیت              ( 1UL << 2UL )
#تعریف_کن پورت_NVIC_SYSTICK_شمار_FLAG_بیت       ( 1UL << 16UL )
#تعریف_کن پورت_NVIC_PEND_SYSTICK_CLEAR_بیت       ( 1UL << 25UL )
#تعریف_کن پورت_NVIC_PEND_SYSTICK_مجموعه_بیت         ( 1UL << 26UL )
#تعریف_کن پورت_MIN_وقفه_اولویت            ( 255UL )
#تعریف_کن پورت_NVIC_PENDSV_PRI                   ( پورت_MIN_وقفه_اولویت << 16UL )
#تعریف_کن پورت_NVIC_SYSTICK_PRI                  ( پورت_MIN_وقفه_اولویت << 24UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the SCB.
 */
#تعریف_کن پورت_SCB_VTOR_REG                      ( *( ( پورت_ISR_t ** ) 0xe000ed08 ) )
#تعریف_کن پورت_SCB_SYS_HANDLER_CTRL_STATE_REG    ( *( ( متطاير uint32_t * ) 0xe000ed24 ) )
#تعریف_کن پورت_SCB_MEM_FAULT_ENABLE_بیت          ( 1UL << 16UL )
#تعریف_کن پورت_SCB_USG_FAULT_ENABLE_بیت          ( 1UL << 18UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants used to check the installation of the FreeRTOS interrupt handlers.
 */
#تعریف_کن پورت_وکتور_شاخص_SVC       ( 11 )
#تعریف_کن پورت_وکتور_شاخص_PENDSV    ( 14 )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to check the validity of an interrupt priority.
 */
#تعریف_کن پورت_NVIC_SHPR2_REG                 ( *( ( متطاير uint32_t * ) 0xE000ED1C ) )
#تعریف_کن پورت_اولی_USER_وقفه_عدد    ( 16 )
#تعریف_کن پورت_NVIC_IP_REGISTERS_جابه_جایی_16    ( 0xE000E3F0 )
#تعریف_کن پورت_AIRCR_REG                      ( *( ( متطاير uint32_t * ) 0xE000ED0C ) )
#تعریف_کن پورت_بالاترین_بیت_از_BYTE                ( ( uint8_t ) 0x80 )
#تعریف_کن پورت_MAX_PRIGROUP_بیتها              ( ( uint8_t ) 7 )
#تعریف_کن پورت_اولویت_گروه_ماسک            ( 0x07UL << 8UL )
#تعریف_کن پورت_PRIGROUP_لغزش                 ( 8UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants used during system call enter and exit.
 */
#تعریف_کن پورت_PSR_پشته_PADDING_ماسک              ( 1UL << 9UL )
#تعریف_کن پورت_EXC_RETURN_پشته_قاب_TYPE_ماسک    ( 1UL << 4UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the FPU.
 */
#تعریف_کن پورت_CPACR               ( ( متطاير uint32_t * ) 0xe000ed88 ) /* Coprocessor Access Control Register. */
#تعریف_کن پورت_CPACR_CP10_مقدار    ( 3UL )
#تعریف_کن پورت_CPACR_CP11_مقدار    پورت_CPACR_CP10_مقدار
#تعریف_کن پورت_CPACR_CP10_POS      ( 20UL )
#تعریف_کن پورت_CPACR_CP11_POS      ( 22UL )

#تعریف_کن پورت_FPCCR               ( ( متطاير uint32_t * ) 0xe000ef34 ) /* Floating Point Context Control Register. */
#تعریف_کن پورت_FPCCR_ASPEN_POS     ( 31UL )
#تعریف_کن پورت_FPCCR_ASPEN_ماسک    ( 1UL << پورت_FPCCR_ASPEN_POS )
#تعریف_کن پورت_FPCCR_LSPEN_POS     ( 30UL )
#تعریف_کن پورت_FPCCR_LSPEN_ماسک    ( 1UL << پورت_FPCCR_LSPEN_POS )
/*-----------------------------------------------------------*/

/**
 * @brief Offsets in the stack to the parameters when inside the SVC handler.
 */
#تعریف_کن پورت_جابه_جایی_مقصد_LR     ( 5 )
#تعریف_کن پورت_جابه_جایی_مقصد_PC     ( 6 )
#تعریف_کن پورت_جابه_جایی_مقصد_PSR    ( 7 )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the MPU.
 */
#تعریف_کن پورت_MPU_TYPE_REG                        ( *( ( متطاير uint32_t * ) 0xe000ed90 ) )
#تعریف_کن پورت_MPU_CTRL_REG                        ( *( ( متطاير uint32_t * ) 0xe000ed94 ) )
#تعریف_کن پورت_MPU_RNR_REG                         ( *( ( متطاير uint32_t * ) 0xe000ed98 ) )

#تعریف_کن پورت_MPU_RBAR_REG                        ( *( ( متطاير uint32_t * ) 0xe000ed9c ) )
#تعریف_کن پورت_MPU_RLAR_REG                        ( *( ( متطاير uint32_t * ) 0xe000eda0 ) )

#تعریف_کن پورت_MPU_RBAR_A1_REG                     ( *( ( متطاير uint32_t * ) 0xe000eda4 ) )
#تعریف_کن پورت_MPU_RLAR_A1_REG                     ( *( ( متطاير uint32_t * ) 0xe000eda8 ) )

#تعریف_کن پورت_MPU_RBAR_A2_REG                     ( *( ( متطاير uint32_t * ) 0xe000edac ) )
#تعریف_کن پورت_MPU_RLAR_A2_REG                     ( *( ( متطاير uint32_t * ) 0xe000edb0 ) )

#تعریف_کن پورت_MPU_RBAR_A3_REG                     ( *( ( متطاير uint32_t * ) 0xe000edb4 ) )
#تعریف_کن پورت_MPU_RLAR_A3_REG                     ( *( ( متطاير uint32_t * ) 0xe000edb8 ) )

#تعریف_کن پورت_MPU_MAIR0_REG                       ( *( ( متطاير uint32_t * ) 0xe000edc0 ) )
#تعریف_کن پورت_MPU_MAIR1_REG                       ( *( ( متطاير uint32_t * ) 0xe000edc4 ) )

#تعریف_کن پورت_MPU_RBAR_آدرس_ماسک               ( 0xffffffe0 ) /* Must be 32-byte aligned. */
#تعریف_کن پورت_MPU_RLAR_آدرس_ماسک               ( 0xffffffe0 ) /* Must be 32-byte aligned. */

#تعریف_کن پورت_MPU_RBAR_ACCESS_PERMISSIONS_ماسک    ( 3UL << 1UL )

#تعریف_کن پورت_MPU_MAIR_ATTR0_POS                  ( 0UL )
#تعریف_کن پورت_MPU_MAIR_ATTR0_ماسک                 ( 0x000000ff )

#تعریف_کن پورت_MPU_MAIR_ATTR1_POS                  ( 8UL )
#تعریف_کن پورت_MPU_MAIR_ATTR1_ماسک                 ( 0x0000ff00 )

#تعریف_کن پورت_MPU_MAIR_ATTR2_POS                  ( 16UL )
#تعریف_کن پورت_MPU_MAIR_ATTR2_ماسک                 ( 0x00ff0000 )

#تعریف_کن پورت_MPU_MAIR_ATTR3_POS                  ( 24UL )
#تعریف_کن پورت_MPU_MAIR_ATTR3_ماسک                 ( 0xff000000 )

#تعریف_کن پورت_MPU_MAIR_ATTR4_POS                  ( 0UL )
#تعریف_کن پورت_MPU_MAIR_ATTR4_ماسک                 ( 0x000000ff )

#تعریف_کن پورت_MPU_MAIR_ATTR5_POS                  ( 8UL )
#تعریف_کن پورت_MPU_MAIR_ATTR5_ماسک                 ( 0x0000ff00 )

#تعریف_کن پورت_MPU_MAIR_ATTR6_POS                  ( 16UL )
#تعریف_کن پورت_MPU_MAIR_ATTR6_ماسک                 ( 0x00ff0000 )

#تعریف_کن پورت_MPU_MAIR_ATTR7_POS                  ( 24UL )
#تعریف_کن پورت_MPU_MAIR_ATTR7_ماسک                 ( 0xff000000 )

#تعریف_کن پورت_MPU_RLAR_ATTR_INDEX0                ( 0UL << 1UL )
#تعریف_کن پورت_MPU_RLAR_ATTR_INDEX1                ( 1UL << 1UL )
#تعریف_کن پورت_MPU_RLAR_ATTR_INDEX2                ( 2UL << 1UL )
#تعریف_کن پورت_MPU_RLAR_ATTR_INDEX3                ( 3UL << 1UL )
#تعریف_کن پورت_MPU_RLAR_ATTR_INDEX4                ( 4UL << 1UL )
#تعریف_کن پورت_MPU_RLAR_ATTR_INDEX5                ( 5UL << 1UL )
#تعریف_کن پورت_MPU_RLAR_ATTR_INDEX6                ( 6UL << 1UL )
#تعریف_کن پورت_MPU_RLAR_ATTR_INDEX7                ( 7UL << 1UL )

#تعریف_کن پورت_MPU_RLAR_REGION_ENABLE              ( 1UL )

#إذا ( پورت_ARMV8_M_MINOR_نسخه >= 1 )

    /* Enable Privileged eXecute Never MPU attribute for the selected memory
     * region. */
    #تعریف_کن پورت_MPU_RLAR_PRIVILEGED_EXECUTE_NEVER    ( 1UL << 4UL )
#پایان_اگر /* portARMV8M_MINOR_VERSION >= 1 */

/* Enable privileged access to unmapped region. */
#تعریف_کن پورت_MPU_PRIV_BACKGROUND_ENABLE_بیت    ( 1UL << 2UL )

/* Enable MPU. */
#تعریف_کن پورت_MPU_ENABLE_بیت                    ( 1UL << 0UL )

/* Extract first address of the MPU region as encoded in the
 * RBAR (Region Base Address Register) value. */
#تعریف_کن پورت_استخراج_اولی_آدرس_FROM_RBAR( rbar ) \
    ( ( rbar ) & پورت_MPU_RBAR_آدرس_ماسک )

/* Extract last address of the MPU region as encoded in the
 * RLAR (Region Limit Address Register) value. */
#تعریف_کن پورت_استخراج_آخرین_آدرس_FROM_RLAR( rlar ) \
    ( ( ( rlar ) & پورت_MPU_RLAR_آدرس_ماسک ) | ~پورت_MPU_RLAR_آدرس_ماسک )

/* Does addr lies within [start, end] address range? */
#تعریف_کن پورت_IS_آدرس_WITHIN_RANGE( addr, شروع, انتها ) \
    ( ( ( addr ) >= ( شروع ) ) && ( ( addr ) <= ( انتها ) ) )

/* Is the access request satisfied by the available permissions? */
#تعریف_کن پورت_IS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#تعریف_کن پورت_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کن پورت_جمع_کن_UINT32_WILL_سرریز( a, b )    ( ( a ) > ( پورت_UINT32_MAX - ( b ) ) )
/*-----------------------------------------------------------*/

/**
 * @brief The maximum 24-bit number.
 *
 * It is needed because the systick is a 24-bit counter.
 */
#تعریف_کن پورت_MAX_24_بیت_عدد       ( 0xffffffUL )

/**
 * @brief A fiddle factor to estimate the number of SysTick counts that would
 * have occurred while the SysTick counter is stopped during tickless idle
 * calculations.
 */
#تعریف_کن پورت_MISSED_COUNTS_ضریب    ( 94UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to set up the initial stack.
 */
#تعریف_کن پورت_INITIAL_XPSR    ( 0x01000000 )

#إذا ( config_پیاپی_FREERTOS_SECURE_ONLY == 1 )

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
    #تعریف_کن پورت_INITIAL_EXC_RETURN    ( 0xfffffffd )
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
    #تعریف_کن پورت_INITIAL_EXC_RETURN    ( 0xffffffbc )
#پایان_اگر /* configRUN_FREERTOS_SECURE_ONLY */

/**
 * @brief CONTROL register privileged bit mask.
 *
 * Bit[0] in CONTROL register tells the privilege:
 *  Bit[0] = 0 ==> The task is privileged.
 *  Bit[0] = 1 ==> The task is not privileged.
 */
#تعریف_کن پورت_CONTROL_PRIVILEGED_ماسک         ( 1UL << 0UL )

/**
 * @brief Initial CONTROL register values.
 */
#تعریف_کن پورت_INITIAL_CONTROL_UNPRIVILEGED    ( 0x3 )
#تعریف_کن پورت_INITIAL_CONTROL_PRIVILEGED      ( 0x2 )

/**
 * @brief Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register.
 */
#اگر_تعریف_نشده configSYSTICK_CLOCK_HZ
    #تعریف_کن configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #تعریف_کن پورت_NVIC_SYSTICK_CLK_بیت_CONFIG    ( پورت_NVIC_SYSTICK_CLK_بیت )
#وإلا
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #تعریف_کن پورت_NVIC_SYSTICK_CLK_بیت_CONFIG    ( 0 )
#پایان_اگر

/**
 * @brief Let the user override the pre-loading of the initial LR with the
 * address of prvTaskExitError() in case it messes up unwinding of the stack
 * in the debugger.
 */
#اگر_تعریف_شده config_TASK_RETURN_آدرس
    #تعریف_کن پورت_TASK_RETURN_آدرس    config_TASK_RETURN_آدرس
#وإلا
    #تعریف_کن پورت_TASK_RETURN_آدرس    prvTaskExitError
#پایان_اگر

/**
 * @brief If portPRELOAD_REGISTERS then registers will be given an initial value
 * when a task is created. This helps in debugging at the cost of code size.
 */
#تعریف_کن پورت_PRELOAD_REGISTERS    1

/**
 * @brief A task is created without a secure context, and must call
 * portALLOCATE_SECURE_CONTEXT() to give itself a secure context before it makes
 * any secure calls.
 */
#تعریف_کن پورت_NO_SECURE_CONTEXT    0

/**
 * @brief Constants required to check and configure PACBTI security feature implementation.
 */
#إذا ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )

    #تعریف_کن پورت_ID_ISAR5_REG       ( *( ( متطاير uint32_t * ) 0xe000ed74 ) )

    #تعریف_کن پورت_CONTROL_UPAC_EN    ( 1UL << 7UL )
    #تعریف_کن پورت_CONTROL_PAC_EN     ( 1UL << 6UL )
    #تعریف_کن پورت_CONTROL_UBTI_EN    ( 1UL << 5UL )
    #تعریف_کن پورت_CONTROL_BTI_EN     ( 1UL << 4UL )

#پایان_اگر /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */
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
#پایان_اگر /* configENABLE_MPU == 1 && configUSE_MPU_WRAPPERS_V1 == 0 */

#إذا ( configENABLE_MPU == 1 )

    /**
     * @brief Setup the Memory Protection Unit (MPU).
     */
    ساكن فراغ prv_راهاندازی_MPU( فراغ ) PRIVILEGED_FUNCTION;
#پایان_اگر /* configENABLE_MPU */

#إذا ( configENABLE_FPU == 1 )

    /**
     * @brief Setup the Floating Point Unit (FPU).
     */
    ساكن فراغ prv_راهاندازی_FPU( فراغ ) PRIVILEGED_FUNCTION;
#پایان_اگر /* configENABLE_FPU */

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
    #إذا ( config_عدد_از_CORES == 1 )
        ساكن uint32_t prvConfigurePACBTI( پایه_Type_t x_Write_Control_ثبات );
    #وإلا /* #if ( configNUMBER_OF_CORES == 1 ) */
        uint32_t vConfigurePACBTI( پایه_Type_t x_Write_Control_ثبات );
    #پایان_اگر /* #if ( configNUMBER_OF_CORES == 1 ) */

#پایان_اگر /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

/**
 * @brief Setup the timer to generate the tick interrupts.
 *
 * The implementation in this file is weak to allow application writers to
 * change the timer used to generate the tick interrupt.
 */
فراغ v_پورت_راهاندازی_Timer_وقفه( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether the current execution context is interrupt.
 *
 * @return pdTRUE if the current execution context is interrupt, pdFALSE
 * otherwise.
 */
پایه_Type_t x_پورت_Is_Inside_وقفه( فراغ );

/**
 * @brief Yield the processor.
 */
فراغ v_پورت_Yield( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief Enter critical section.
 */
فراغ v_پورت_Enter_Critical( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief Exit from critical section.
 */
فراغ v_پورت_Exit_Critical( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief SysTick handler.
 */
فراغ SysTick_Handler( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief C part of SVC handler.
 */
پورت_DONT_DISCARD فراغ v_پورت_SVCHandler_C( uint32_t * pul_Caller_پشته_آدرس ) PRIVILEGED_FUNCTION;

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the system call stack so that upon returning from
     * SVC, the system call stack is used.
     *
     * @param pulTaskStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    فراغ vSystemCallEnter( uint32_t * pul_Task_پشته,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_عدد ) PRIVILEGED_FUNCTION;

#پایان_اگر /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    فراغ vRequestSystemCallExit( فراغ ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#پایان_اگر /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param pulSystemCallStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     */
    فراغ vSystemCallExit( uint32_t * pul_System_Call_پشته,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#پایان_اگر /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#إذا ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    پایه_Type_t x_پورت_Is_Task_Privileged( فراغ ) PRIVILEGED_FUNCTION;

#پایان_اگر /* configENABLE_MPU == 1 */

#إذا ( config_عدد_از_CORES > 1 )

    /**
     * @brief Platform/Application-defined function that wakes up the secondary cores.
     *
     * @return pdTRUE if the secondary cores were successfully woken up.
     *         pdFALSE otherwise.
     */
    خارجي پایه_Type_t configWAKE_SECONDARY_CORES( فراغ );

#پایان_اگر /* #if ( configNUMBER_OF_CORES > 1 ) */

/**
 * @brief Configures interrupt priorities.
 */
فراغ v_پورت_Configure_وقفه_Priorities( فراغ ) PRIVILEGED_FUNCTION;
/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief This variable is set to pdTRUE when the scheduler is started.
     */
    PRIVILEGED_داده ساكن پایه_Type_t xSchedulerRunning = pdFALSE;

#پایان_اگر /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/**
 * @brief Each task maintains its own interrupt status in the critical nesting
 * variable.
 */
#إذا ( config_عدد_از_CORES == 1 )
    PRIVILEGED_داده ساكن متطاير uint32_t ulCriticalNesting = 0UL;
#وإلا /* #if ( configNUMBER_OF_CORES == 1 ) */
    PRIVILEGED_داده متطاير uint32_t ulCriticalNestings[ config_عدد_از_CORES ] = { 0 };
    /* Flags to check if the secondary cores are ready. */
    PRIVILEGED_داده متطاير uint8_t ucSecondaryCoresReadyFlags[ config_عدد_از_CORES - 1 ] = { 0 };
    /* Flag to indicate that the primary core has completed its initialisation. */
    PRIVILEGED_داده متطاير uint8_t uc_Primary_Core_Init_انجامشده_Flag = 0;
 #پایان_اگر /* #if ( configNUMBER_OF_CORES == 1 ) */

#إذا ( configENABLE_TRUSTZONE == 1 )

    /**
     * @brief Saved as part of the task context to indicate which context the
     * task is using on the secure side.
     */
    PRIVILEGED_داده پورت_DONT_DISCARD متطاير SecureContextHandle_t xSecureContext = پورت_NO_SECURE_CONTEXT;
#پایان_اگر /* configENABLE_TRUSTZONE */

/**
 * @brief Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#إذا ( ( configASSERT_DEFINED == 1 ) && ( پورت_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) )

    ساكن uint8_t uc_Max_Sys_Call_اولویت = 0;
    ساكن uint32_t ulMaxPRIGROUPValue = 0;
    ساكن ثابت متطاير uint8_t * ثابت pc_وقفه_اولویت_Registers = ( ثابت متطاير uint8_t * ) پورت_NVIC_IP_REGISTERS_جابه_جایی_16;

#پایان_اگر /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */

#إذا ( configUSE_TICKLESS_IDLE == 1 )

    /**
     * @brief The number of SysTick increments that make up one tick period.
     */
    PRIVILEGED_داده ساكن uint32_t ulTimerCountsForOneTick = 0;

    /**
     * @brief The maximum number of tick periods that can be suppressed is
     * limited by the 24 bit resolution of the SysTick timer.
     */
    PRIVILEGED_داده ساكن uint32_t x_بیشینه_Possible_Suppressed_Ticks = 0;

    /**
     * @brief Compensate for the CPU cycles that pass while the SysTick is
     * stopped (low power functionality only).
     */
    PRIVILEGED_داده ساكن uint32_t ulStoppedTimerCompensation = 0;
#پایان_اگر /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) فراغ v_پورت_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_زمان )
    {
        uint32_t ul_Reload_مقدار, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_چپ;
        TickType_t x_Modifiable_Idle_زمان;

        /* Make sure the SysTick reload value does not overflow the counter. */
        إذا( x_Expected_Idle_زمان > x_بیشینه_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_زمان = x_بیشینه_Possible_Suppressed_Ticks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm متطاير ( "cpsid i" ::: "memory" );
        __asm متطاير ( "dsb" );
        __asm متطاير ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        إذا( e_Task_Confirm_Sleep_نما_وضعیت() == eAbortSleep )
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
            پورت_NVIC_SYSTICK_CTRL_REG = ( پورت_NVIC_SYSTICK_CLK_بیت_CONFIG | پورت_NVIC_SYSTICK_INT_بیت );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_چپ = پورت_NVIC_SYSTICK_CURRENT_مقدار_REG;

            إذا( ul_Sys_Tick_Decrements_چپ == 0 )
            {
                ul_Sys_Tick_Decrements_چپ = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_مقدار = ul_Sys_Tick_Decrements_چپ + ( ulTimerCountsForOneTick * ( x_Expected_Idle_زمان - 1UL ) );

            إذا( ( پورت_NVIC_INT_CTRL_REG & پورت_NVIC_PEND_SYSTICK_مجموعه_بیت ) != 0 )
            {
                پورت_NVIC_INT_CTRL_REG = پورت_NVIC_PEND_SYSTICK_CLEAR_بیت;
                ul_Reload_مقدار -= ulTimerCountsForOneTick;
            }

            إذا( ul_Reload_مقدار > ulStoppedTimerCompensation )
            {
                ul_Reload_مقدار -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            پورت_NVIC_SYSTICK_بارگیری_REG = ul_Reload_مقدار;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            پورت_NVIC_SYSTICK_CURRENT_مقدار_REG = 0UL;

            /* Restart SysTick. */
            پورت_NVIC_SYSTICK_CTRL_REG |= پورت_NVIC_SYSTICK_ENABLE_بیت;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            x_Modifiable_Idle_زمان = x_Expected_Idle_زمان;
            configPRE_SLEEP_PROCESSING( x_Modifiable_Idle_زمان );

            إذا( x_Modifiable_Idle_زمان > 0 )
            {
                __asm متطاير ( "dsb" ::: "memory" );
                __asm متطاير ( "wfi" );
                __asm متطاير ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_زمان );

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
            پورت_NVIC_SYSTICK_CTRL_REG = ( پورت_NVIC_SYSTICK_CLK_بیت_CONFIG | پورت_NVIC_SYSTICK_INT_بیت );

            /* Determine whether the SysTick has already counted to zero. */
            إذا( ( پورت_NVIC_SYSTICK_CTRL_REG & پورت_NVIC_SYSTICK_شمار_FLAG_بیت ) != 0 )
            {
                uint32_t ul_Calculated_بارگیری_مقدار;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_بارگیری_مقدار = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_مقدار - پورت_NVIC_SYSTICK_CURRENT_مقدار_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                إذا( ( ul_Calculated_بارگیری_مقدار <= ulStoppedTimerCompensation ) || ( ul_Calculated_بارگیری_مقدار > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_بارگیری_مقدار = ( ulTimerCountsForOneTick - 1UL );
                }

                پورت_NVIC_SYSTICK_بارگیری_REG = ul_Calculated_بارگیری_مقدار;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = x_Expected_Idle_زمان - 1UL;
            }
            وإلا
            {
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_چپ = پورت_NVIC_SYSTICK_CURRENT_مقدار_REG;
                #إذا ( پورت_NVIC_SYSTICK_CLK_بیت_CONFIG != پورت_NVIC_SYSTICK_CLK_بیت )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    إذا( ul_Sys_Tick_Decrements_چپ == 0 )
                    {
                        ul_Sys_Tick_Decrements_چپ = ul_Reload_مقدار;
                    }
                }
                #پایان_اگر /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_زمان * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_چپ;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                پورت_NVIC_SYSTICK_بارگیری_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            پورت_NVIC_SYSTICK_CURRENT_مقدار_REG = 0UL;
            پورت_NVIC_SYSTICK_CTRL_REG = پورت_NVIC_SYSTICK_CLK_بیت | پورت_NVIC_SYSTICK_INT_بیت | پورت_NVIC_SYSTICK_ENABLE_بیت;
            #إذا ( پورت_NVIC_SYSTICK_CLK_بیت_CONFIG == پورت_NVIC_SYSTICK_CLK_بیت )
            {
                پورت_NVIC_SYSTICK_بارگیری_REG = ulTimerCountsForOneTick - 1UL;
            }
            #وإلا
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                پورت_NVIC_SYSTICK_CTRL_REG = پورت_NVIC_SYSTICK_CLK_بیت | پورت_NVIC_SYSTICK_INT_بیت;

                إذا( ( پورت_NVIC_SYSTICK_CTRL_REG & پورت_NVIC_SYSTICK_شمار_FLAG_بیت ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    پورت_NVIC_SYSTICK_CURRENT_مقدار_REG = 0;
                }

                پورت_NVIC_SYSTICK_بارگیری_REG = ulTimerCountsForOneTick - 1UL;
                پورت_NVIC_SYSTICK_CTRL_REG = پورت_NVIC_SYSTICK_CLK_بیت_CONFIG | پورت_NVIC_SYSTICK_INT_بیت | پورت_NVIC_SYSTICK_ENABLE_بیت;
            }
            #پایان_اگر /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            v_Task_گام_Tick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __asm متطاير ( "cpsie i" ::: "memory" );
        }
    }

#پایان_اگر /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

__attribute__( ( weak ) ) فراغ v_پورت_راهاندازی_Timer_وقفه( فراغ ) /* PRIVILEGED_FUNCTION */
{
    /* Calculate the constants required to configure the tick interrupt. */
    #إذا ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_نرخ_HZ );
        x_بیشینه_Possible_Suppressed_Ticks = پورت_MAX_24_بیت_عدد / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = پورت_MISSED_COUNTS_ضریب / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #پایان_اگر /* configUSE_TICKLESS_IDLE */

    /* Stop and reset SysTick.
     *
     * QEMU versions older than 7.0.0 contain a bug which causes an error if we
     * enable SysTick without first selecting a valid clock source. We trigger
     * the bug if we change clock sources from a clock with a zero clock period
     * to one with a nonzero clock period and enable Systick at the same time.
     * So we configure the CLKSOURCE bit here, prior to setting the ENABLE bit.
     * This workaround avoids the bug in QEMU versions older than 7.0.0. */
    پورت_NVIC_SYSTICK_CTRL_REG = پورت_NVIC_SYSTICK_CLK_بیت_CONFIG;
    پورت_NVIC_SYSTICK_CURRENT_مقدار_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    پورت_NVIC_SYSTICK_بارگیری_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_نرخ_HZ ) - 1UL;
    پورت_NVIC_SYSTICK_CTRL_REG = پورت_NVIC_SYSTICK_CLK_بیت_CONFIG | پورت_NVIC_SYSTICK_INT_بیت | پورت_NVIC_SYSTICK_ENABLE_بیت;
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
    #إذا ( config_عدد_از_CORES == 1 )
        configASSERT( ulCriticalNesting == ~0UL );
    #وإلا /* #if ( configNUMBER_OF_CORES == 1 ) */
        configASSERT( ulCriticalNestings[ پورت_GET_CORE_ID() ] == ~0UL );
    #پایان_اگر /* #if ( configNUMBER_OF_CORES == 1 ) */
    پورت_DISABLE_INTERRUPTS();

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

        إذا( ( ulRBARValue & پورت_MPU_RBAR_ACCESS_PERMISSIONS_ماسک ) == پورت_MPU_REGION_READ_ONLY )
        {
            ulAccessPermissions = tskMPU_READ_PERMISSION;
        }

        إذا( ( ulRBARValue & پورت_MPU_RBAR_ACCESS_PERMISSIONS_ماسک ) == پورت_MPU_REGION_READ_WRITE )
        {
            ulAccessPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
        }

        أرجع ulAccessPermissions;
    }

#پایان_اگر /* configENABLE_MPU == 1 && configUSE_MPU_WRAPPERS_V1 == 0 */
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    ساكن فراغ prv_راهاندازی_MPU( فراغ ) /* PRIVILEGED_FUNCTION */
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
        #پایان_اگر /* defined( __ARMCC_VERSION ) */

        /* The only permitted number of regions are 8 or 16. */
        configASSERT( ( config_مجموع_MPU_REGIONS == 8 ) || ( config_مجموع_MPU_REGIONS == 16 ) );

        /* MAIR0 - Index 0. */
        پورت_MPU_MAIR0_REG |= ( ( پورت_MPU_نرمال_حافظه_BUFFERABLE_CACHEABLE << پورت_MPU_MAIR_ATTR0_POS ) & پورت_MPU_MAIR_ATTR0_ماسک );
        /* MAIR0 - Index 1. */
        پورت_MPU_MAIR0_REG |= ( ( پورت_MPU_DEVICE_حافظه_n_Gn_RE << پورت_MPU_MAIR_ATTR1_POS ) & پورت_MPU_MAIR_ATTR1_ماسک );

        /* Setup privileged flash as Read Only so that privileged tasks can
         * read it but not modify. */
        پورت_MPU_RNR_REG = پورت_PRIVILEGED_FLASH_REGION;
        پورت_MPU_RBAR_REG = ( ( ( uint32_t ) __privileged_functions_start__ ) & پورت_MPU_RBAR_آدرس_ماسک ) |
                           ( پورت_MPU_REGION_NON_SHAREABLE ) |
                           ( پورت_MPU_REGION_PRIVILEGED_READ_ONLY );
        پورت_MPU_RLAR_REG = ( ( ( uint32_t ) __privileged_functions_end__ ) & پورت_MPU_RLAR_آدرس_ماسک ) |
                           ( پورت_MPU_RLAR_ATTR_INDEX0 ) |
                           ( پورت_MPU_RLAR_REGION_ENABLE );

        /* Setup unprivileged flash as Read Only by both privileged and
         * unprivileged tasks. All tasks can read it but no-one can modify. */
        پورت_MPU_RNR_REG = پورت_UNPRIVILEGED_FLASH_REGION;
        پورت_MPU_RBAR_REG = ( ( ( uint32_t ) __unprivileged_flash_start__ ) & پورت_MPU_RBAR_آدرس_ماسک ) |
                           ( پورت_MPU_REGION_NON_SHAREABLE ) |
                           ( پورت_MPU_REGION_READ_ONLY );
        پورت_MPU_RLAR_REG = ( ( ( uint32_t ) __unprivileged_flash_end__ ) & پورت_MPU_RLAR_آدرس_ماسک ) |
                           ( پورت_MPU_RLAR_ATTR_INDEX0 ) |
                           ( پورت_MPU_RLAR_REGION_ENABLE );

        /* Setup unprivileged syscalls flash as Read Only by both privileged
         * and unprivileged tasks. All tasks can read it but no-one can modify. */
        پورت_MPU_RNR_REG = پورت_UNPRIVILEGED_SYSCALLS_REGION;
        پورت_MPU_RBAR_REG = ( ( ( uint32_t ) __syscalls_flash_start__ ) & پورت_MPU_RBAR_آدرس_ماسک ) |
                           ( پورت_MPU_REGION_NON_SHAREABLE ) |
                           ( پورت_MPU_REGION_READ_ONLY );
        پورت_MPU_RLAR_REG = ( ( ( uint32_t ) __syscalls_flash_end__ ) & پورت_MPU_RLAR_آدرس_ماسک ) |
                           ( پورت_MPU_RLAR_ATTR_INDEX0 ) |
                           ( پورت_MPU_RLAR_REGION_ENABLE );

        /* Setup RAM containing kernel data for privileged access only. */
        پورت_MPU_RNR_REG = پورت_PRIVILEGED_RAM_REGION;
        پورت_MPU_RBAR_REG = ( ( ( uint32_t ) __privileged_sram_start__ ) & پورت_MPU_RBAR_آدرس_ماسک ) |
                           ( پورت_MPU_REGION_NON_SHAREABLE ) |
                           ( پورت_MPU_REGION_PRIVILEGED_READ_WRITE ) |
                           ( پورت_MPU_REGION_EXECUTE_NEVER );
        پورت_MPU_RLAR_REG = ( ( ( uint32_t ) __privileged_sram_end__ ) & پورت_MPU_RLAR_آدرس_ماسک ) |
                           ( پورت_MPU_RLAR_ATTR_INDEX0 ) |
                           ( پورت_MPU_RLAR_REGION_ENABLE );

        /* Enable mem fault. */
        پورت_SCB_SYS_HANDLER_CTRL_STATE_REG |= پورت_SCB_MEM_FAULT_ENABLE_بیت;

        /* Enable MPU with privileged background access i.e. unmapped
         * regions have privileged access. */
        پورت_MPU_CTRL_REG |= ( پورت_MPU_PRIV_BACKGROUND_ENABLE_بیت | پورت_MPU_ENABLE_بیت );
    }

#پایان_اگر /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#إذا ( configENABLE_FPU == 1 )

    ساكن فراغ prv_راهاندازی_FPU( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        #إذا ( configENABLE_TRUSTZONE == 1 )
        {
            /* Enable non-secure access to the FPU. */
            SecureInit_EnableNSFPUAccess();
        }
        #پایان_اگر /* configENABLE_TRUSTZONE */

        /* CP10 = 11 ==> Full access to FPU i.e. both privileged and
         * unprivileged code should be able to access FPU. CP11 should be
         * programmed to the same value as CP10. */
        *( پورت_CPACR ) |= ( ( پورت_CPACR_CP10_مقدار << پورت_CPACR_CP10_POS ) |
                            ( پورت_CPACR_CP11_مقدار << پورت_CPACR_CP11_POS )
                            );

        /* ASPEN = 1 ==> Hardware should automatically preserve floating point
         * context on exception entry and restore on exception return.
         * LSPEN = 1 ==> Enable lazy context save of FP state. */
        *( پورت_FPCCR ) |= ( پورت_FPCCR_ASPEN_ماسک | پورت_FPCCR_LSPEN_ماسک );
    }

#پایان_اگر /* configENABLE_FPU */
/*-----------------------------------------------------------*/

فراغ v_پورت_Yield( فراغ ) /* PRIVILEGED_FUNCTION */
{
    /* Set a PendSV to request a context switch. */
    پورت_NVIC_INT_CTRL_REG = پورت_NVIC_PENDSVSET_بیت;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm متطاير ( "dsb" ::: "memory" );
    __asm متطاير ( "isb" );
}
/*-----------------------------------------------------------*/

#إذا ( config_عدد_از_CORES == 1 )
    فراغ v_پورت_Enter_Critical( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        پورت_DISABLE_INTERRUPTS();
        ulCriticalNesting++;
        /* Barriers are normally not required but do ensure the code is
        * completely within the specified behaviour for the architecture. */
        __asm متطاير ( "dsb" ::: "memory" );
        __asm متطاير ( "isb" );
    }
    /*-----------------------------------------------------------*/

    فراغ v_پورت_Exit_Critical( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( ulCriticalNesting );
        ulCriticalNesting--;

        إذا( ulCriticalNesting == 0 )
        {
            پورت_ENABLE_INTERRUPTS();
        }
    }
#پایان_اگر /* configNUMBER_OF_CORES == 1 */
/*-----------------------------------------------------------*/

فراغ SysTick_Handler( فراغ ) /* PRIVILEGED_FUNCTION */
{
    uint32_t ul_قبلی_ماسک;

    ul_قبلی_ماسک = پورت_مجموعه_وقفه_ماسک_FROM_ISR();
    #إذا ( config_عدد_از_CORES > 1 )
        UBaseType_t ux_Saved_وقفه_وضعیت = پورت_ENTER_CRITICAL_FROM_ISR();
    #پایان_اگر /* if ( configNUMBER_OF_CORES > 1 ) */

    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_مقصد_SCHEDULER();
            /* Pend a context switch. */
            پورت_NVIC_INT_CTRL_REG = پورت_NVIC_PENDSVSET_بیت;
        }
        وإلا
        {
            traceISR_EXIT();
        }
    }
    #إذا ( config_عدد_از_CORES > 1 )
        پورت_EXIT_CRITICAL_FROM_ISR( ux_Saved_وقفه_وضعیت );
    #پایان_اگر /* if ( configNUMBER_OF_CORES > 1 ) */

    پورت_CLEAR_وقفه_ماسک_FROM_ISR( ul_قبلی_ماسک );
}
/*-----------------------------------------------------------*/

فراغ v_پورت_SVCHandler_C( uint32_t * pul_Caller_پشته_آدرس ) /* PRIVILEGED_FUNCTION portDONT_DISCARD */
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
        #پایان_اگر /* defined( __ARMCC_VERSION ) */
    #پایان_اگر /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

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
        #پایان_اگر /* defined( __ARMCC_VERSION ) */
    #پایان_اگر /* configENABLE_MPU == 1 */

    uint32_t ulPC;

    #إذا ( configENABLE_TRUSTZONE == 1 )
        uint32_t ulR0, ulR1;
        خارجي TaskHandle_t pxCurrentTCB;
        #إذا ( configENABLE_MPU == 1 )
            uint32_t ulControl, ulIsTaskPrivileged;
        #پایان_اگر /* configENABLE_MPU */
    #پایان_اگر /* configENABLE_TRUSTZONE */
    uint8_t ucSVCNumber;

    /* Register are stored on the stack in the following order - R0, R1, R2, R3,
     * R12, LR, PC, xPSR. */
    ulPC = pul_Caller_پشته_آدرس[ پورت_جابه_جایی_مقصد_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    بدل( ucSVCNumber )
    {
    #إذا ( configENABLE_TRUSTZONE == 1 )
        حالة پورت_SVC_ALLOCATE_SECURE_CONTEXT:

            /* R0 contains the stack size passed as parameter to the
             * vPortAllocateSecureContext function. */
            ulR0 = pul_Caller_پشته_آدرس[ 0 ];

            #إذا ( configENABLE_MPU == 1 )
            {
                /* Read the CONTROL register value. */
                __asm متطاير ( "mrs %0, control"  : "=r" ( ulControl ) );

                /* The task that raised the SVC is privileged if Bit[0]
                 * in the CONTROL register is 0. */
                ulIsTaskPrivileged = ( ( ulControl & پورت_CONTROL_PRIVILEGED_ماسک ) == 0 );

                /* Allocate and load a context for the secure task. */
                xSecureContext = SecureContext_AllocateContext( ulR0, ulIsTaskPrivileged, pxCurrentTCB );
            }
            #وإلا /* if ( configENABLE_MPU == 1 ) */
            {
                /* Allocate and load a context for the secure task. */
                xSecureContext = SecureContext_AllocateContext( ulR0, pxCurrentTCB );
            }
            #پایان_اگر /* configENABLE_MPU */

            configASSERT( xSecureContext != securecontextINVALID_CONTEXT_ID );
            Secure_Context_بارگیری_Context( xSecureContext, pxCurrentTCB );
            اكسر;

        حالة پورت_SVC_FREE_SECURE_CONTEXT:
            #إذا ( configENABLE_MPU == 1 )
            إذا( ( ulPC >= ( uint32_t ) __privileged_functions_start__ ) &&
                ( ulPC <= ( uint32_t ) __privileged_functions_end__ ) )
            {
            #پایان_اگر /* configENABLE_MPU */
                /* R0 contains TCB being freed and R1 contains the secure
                 * context handle to be freed. */
                ulR0 = pul_Caller_پشته_آدرس[ 0 ];
                ulR1 = pul_Caller_پشته_آدرس[ 1 ];

                /* Free the secure context. */
                SecureContext_FreeContext( ( SecureContextHandle_t ) ulR1, ( فراغ * ) ulR0 );
            #إذا ( configENABLE_MPU == 1 )
            }
            #پایان_اگر /* configENABLE_MPU */
            اكسر;
    #پایان_اگر /* configENABLE_TRUSTZONE */

        حالة پورت_SVC_شروع_SCHEDULER:
            #إذا ( configENABLE_MPU == 1 )
            إذا( ( ulPC >= ( uint32_t ) __privileged_functions_start__ ) &&
                ( ulPC <= ( uint32_t ) __privileged_functions_end__ ) )
            {
            #پایان_اگر /* configENABLE_MPU */
                #إذا ( configENABLE_TRUSTZONE == 1 )
                {
                    /* De-prioritize the non-secure exceptions so that the
                     * non-secure pendSV runs at the lowest priority. */
                    SecureInit_DePrioritizeNSExceptions();

                    /* Initialize the secure context management system. */
                    SecureContext_Init();
                }
                #پایان_اگر /* configENABLE_TRUSTZONE */

                #إذا ( configENABLE_FPU == 1 )
                {
                    /* Setup the Floating Point Unit (FPU). */
                    prv_راهاندازی_FPU();
                }
                #پایان_اگر /* configENABLE_FPU */

                /* Setup the context of the first task so that the first task starts
                 * executing. */
                v_Restore_Context_از_اولی_Task();
            #إذا ( configENABLE_MPU == 1 )
            }
            #پایان_اگر /* configENABLE_MPU */
            اكسر;

    #إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )
        حالة پورت_SVC_RAISE_PRIVILEGE:

            /* Only raise the privilege, if the svc was raised from any of
             * the system calls. */
            إذا( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
            {
                vRaisePrivilege();
            }
            اكسر;
    #پایان_اگر /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #إذا ( configENABLE_MPU == 1 )
        حالة پورت_SVC_YIELD:
            v_پورت_Yield();
            اكسر;
    #پایان_اگر /* configENABLE_MPU == 1 */

        افتراضي:
            /* Incorrect SVC call. */
            configASSERT( pdFALSE );
    }
}
/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    فراغ vSystemCallEnter( uint32_t * pul_Task_پشته,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_عدد ) /* PRIVILEGED_FUNCTION */
    {
        خارجي TaskHandle_t pxCurrentTCB;
        خارجي UBaseType_t uxSystemCallImplementations[ رقم_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_پشته;
        uint32_t ul_Hardware_Saved_Exception_قاب_اندازه, ulSystemCallLocation, i;

        #إذا defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint32_t * __syscalls_flash_start__;
            خارجي uint32_t * __syscalls_flash_end__;
        #وإلا
            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint32_t __syscalls_flash_start__[];
            خارجي uint32_t __syscalls_flash_end__[];
        #پایان_اگر /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_پشته[ پورت_جابه_جایی_مقصد_PC ];
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
            ( pxMpuSettings->x_System_Call_پشته_Info.pul_Task_پشته == عدم ) &&
            ( uxSystemCallImplementations[ uc_System_Call_عدد ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_پشته = pxMpuSettings->x_System_Call_پشته_Info.pul_System_Call_پشته;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            #إذا ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )
            {
                إذا( ( ulLR & پورت_EXC_RETURN_پشته_قاب_TYPE_ماسک ) == 0UL )
                {
                    /* Extended frame i.e. FPU in use. */
                    ul_Hardware_Saved_Exception_قاب_اندازه = 26;
                    __asm متطاير (
                        " vpush {s0}         \n" /* Trigger lazy stacking. */
                        " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                        ::: "memory"
                        );
                }
                وإلا
                {
                    /* Standard frame i.e. FPU not in use. */
                    ul_Hardware_Saved_Exception_قاب_اندازه = 8;
                }
            }
            #وإلا /* if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */
            {
                ul_Hardware_Saved_Exception_قاب_اندازه = 8;
            }
            #پایان_اگر /* configENABLE_FPU || configENABLE_MVE */

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_پشته = pul_System_Call_پشته - ul_Hardware_Saved_Exception_قاب_اندازه;

            /* Copy the stack frame. */
            لكل( i = 0; i < ul_Hardware_Saved_Exception_قاب_اندازه; i++ )
            {
                pul_System_Call_پشته[ i ] = pul_Task_پشته[ i ];
            }

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_پشته_Info.ul_Link_ثبات_At_System_Call_مدخل = pul_Task_پشته[ پورت_جابه_جایی_مقصد_LR ];

            /* Store the value of the PSPLIM register before the SVC was raised.
             * We need to restore it when we exit from the system call. */
            #إذا ( پورت_USE_PSPLIM_ثبات == 1 )
            {
                __asm متطاير ( "mrs %0, psplim" : "=r" ( pxMpuSettings->x_System_Call_پشته_Info.ul_پشته_حد_ثبات_At_System_Call_مدخل ) );
            }
            #پایان_اگر

            /* Use the pulSystemCallStack in thread mode. */
            __asm متطاير ( "msr psp, %0" : : "r" ( pul_System_Call_پشته ) );
            #إذا ( پورت_USE_PSPLIM_ثبات == 1 )
            {
                __asm متطاير ( "msr psplim, %0" : : "r" ( pxMpuSettings->x_System_Call_پشته_Info.pul_System_Call_پشته_حد ) );
            }
            #پایان_اگر

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_پشته[ پورت_جابه_جایی_مقصد_PC ] = uxSystemCallImplementations[ uc_System_Call_عدد ];

            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_پشته[ پورت_جابه_جایی_مقصد_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_پشته_Info.pul_Task_پشته = pul_Task_پشته + ul_Hardware_Saved_Exception_قاب_اندازه;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            إذا( ( pul_Task_پشته[ پورت_جابه_جایی_مقصد_PSR ] & پورت_PSR_پشته_PADDING_ماسک ) == پورت_PSR_پشته_PADDING_ماسک )
            {
                pxMpuSettings->ulTaskFlags |= پورت_پشته_قاب_HAS_PADDING_FLAG;
            }
            وإلا
            {
                pxMpuSettings->ulTaskFlags &= ( ~پورت_پشته_قاب_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_پشته[ پورت_جابه_جایی_مقصد_PSR ] &= ( ~پورت_PSR_پشته_PADDING_ماسک );

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

#پایان_اگر /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    فراغ vRequestSystemCallExit( فراغ ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm متطاير ( "svc %0 \n" ::"i" ( پورت_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#پایان_اگر /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    فراغ vSystemCallExit( uint32_t * pul_System_Call_پشته,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        خارجي TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_پشته;
        uint32_t ul_Hardware_Saved_Exception_قاب_اندازه, ulSystemCallLocation, i;

        #إذا defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint32_t * __privileged_functions_start__;
            خارجي uint32_t * __privileged_functions_end__;
        #وإلا
            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint32_t __privileged_functions_start__[];
            خارجي uint32_t __privileged_functions_end__[];
        #پایان_اگر /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_پشته[ پورت_جابه_جایی_مقصد_PC ];
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
            ( pxMpuSettings->x_System_Call_پشته_Info.pul_Task_پشته != عدم ) )
        {
            pul_Task_پشته = pxMpuSettings->x_System_Call_پشته_Info.pul_Task_پشته;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            #إذا ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )
            {
                إذا( ( ulLR & پورت_EXC_RETURN_پشته_قاب_TYPE_ماسک ) == 0UL )
                {
                    /* Extended frame i.e. FPU in use. */
                    ul_Hardware_Saved_Exception_قاب_اندازه = 26;
                    __asm متطاير (
                        " vpush {s0}         \n" /* Trigger lazy stacking. */
                        " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                        ::: "memory"
                        );
                }
                وإلا
                {
                    /* Standard frame i.e. FPU not in use. */
                    ul_Hardware_Saved_Exception_قاب_اندازه = 8;
                }
            }
            #وإلا /* if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */
            {
                ul_Hardware_Saved_Exception_قاب_اندازه = 8;
            }
            #پایان_اگر /* configENABLE_FPU || configENABLE_MVE */

            /* Make space on the task stack for the stack frame. */
            pul_Task_پشته = pul_Task_پشته - ul_Hardware_Saved_Exception_قاب_اندازه;

            /* Copy the stack frame. */
            لكل( i = 0; i < ul_Hardware_Saved_Exception_قاب_اندازه; i++ )
            {
                pul_Task_پشته[ i ] = pul_System_Call_پشته[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm متطاير ( "msr psp, %0" : : "r" ( pul_Task_پشته ) );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_پشته[ پورت_جابه_جایی_مقصد_PC ] = pxMpuSettings->x_System_Call_پشته_Info.ul_Link_ثبات_At_System_Call_مدخل;
            /* Ensure that LR has a valid value.*/
            pul_Task_پشته[ پورت_جابه_جایی_مقصد_LR ] = pxMpuSettings->x_System_Call_پشته_Info.ul_Link_ثبات_At_System_Call_مدخل;

            /* Restore the PSPLIM register to what it was at the time of
             * system call entry. */
            #إذا ( پورت_USE_PSPLIM_ثبات == 1 )
            {
                __asm متطاير ( "msr psplim, %0" : : "r" ( pxMpuSettings->x_System_Call_پشته_Info.ul_پشته_حد_ثبات_At_System_Call_مدخل ) );
            }
            #پایان_اگر

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            إذا( ( pxMpuSettings->ulTaskFlags & پورت_پشته_قاب_HAS_PADDING_FLAG ) == پورت_پشته_قاب_HAS_PADDING_FLAG )
            {
                pul_Task_پشته[ پورت_جابه_جایی_مقصد_PSR ] |= پورت_PSR_پشته_PADDING_ماسک;
            }
            وإلا
            {
                pul_Task_پشته[ پورت_جابه_جایی_مقصد_PSR ] &= ( ~پورت_PSR_پشته_PADDING_ماسک );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_پشته_Info.pul_Task_پشته = عدم;

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

#پایان_اگر /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    پایه_Type_t x_پورت_Is_Task_Privileged( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        پایه_Type_t xTaskIsPrivileged = pdFALSE;
        ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( عدم ); /* Calling task's MPU settings. */

        إذا( ( xTaskMpuSettings->ulTaskFlags & پورت_TASK_IS_PRIVILEGED_FLAG ) == پورت_TASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        أرجع xTaskIsPrivileged;
    }

#پایان_اگر /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    پشته_Type_t * px_پورت_Initialise_پشته( پشته_Type_t * px_بالاترین_از_پشته,
                                         پشته_Type_t * px_انتها_از_پشته,
                                         TaskFunction_t px_کد,
                                         فراغ * pvParameters,
                                         پایه_Type_t x_پیاپی_Privileged,
                                         xMPU_SETTINGS * xMPUSettings ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_شاخص = 0;
        uint32_t ulControl = 0x0;

        xMPUSettings->ulContext[ ul_شاخص ] = 0x04040404; /* r4. */
        ul_شاخص++;
        xMPUSettings->ulContext[ ul_شاخص ] = 0x05050505; /* r5. */
        ul_شاخص++;
        xMPUSettings->ulContext[ ul_شاخص ] = 0x06060606; /* r6. */
        ul_شاخص++;
        xMPUSettings->ulContext[ ul_شاخص ] = 0x07070707; /* r7. */
        ul_شاخص++;
        xMPUSettings->ulContext[ ul_شاخص ] = 0x08080808; /* r8. */
        ul_شاخص++;
        xMPUSettings->ulContext[ ul_شاخص ] = 0x09090909; /* r9. */
        ul_شاخص++;
        xMPUSettings->ulContext[ ul_شاخص ] = 0x10101010; /* r10. */
        ul_شاخص++;
        xMPUSettings->ulContext[ ul_شاخص ] = 0x11111111; /* r11. */
        ul_شاخص++;

        xMPUSettings->ulContext[ ul_شاخص ] = ( uint32_t ) pvParameters; /* r0. */
        ul_شاخص++;
        xMPUSettings->ulContext[ ul_شاخص ] = 0x01010101; /* r1. */
        ul_شاخص++;
        xMPUSettings->ulContext[ ul_شاخص ] = 0x02020202; /* r2. */
        ul_شاخص++;
        xMPUSettings->ulContext[ ul_شاخص ] = 0x03030303; /* r3. */
        ul_شاخص++;
        xMPUSettings->ulContext[ ul_شاخص ] = 0x12121212; /* r12. */
        ul_شاخص++;
        xMPUSettings->ulContext[ ul_شاخص ] = ( uint32_t ) پورت_TASK_RETURN_آدرس; /* LR. */
        ul_شاخص++;
        xMPUSettings->ulContext[ ul_شاخص ] = ( uint32_t ) px_کد; /* PC. */
        ul_شاخص++;
        xMPUSettings->ulContext[ ul_شاخص ] = پورت_INITIAL_XPSR; /* xPSR. */
        ul_شاخص++;

        #إذا ( configENABLE_TRUSTZONE == 1 )
        {
            xMPUSettings->ulContext[ ul_شاخص ] = پورت_NO_SECURE_CONTEXT; /* xSecureContext. */
            ul_شاخص++;
        }
        #پایان_اگر /* configENABLE_TRUSTZONE */
        xMPUSettings->ulContext[ ul_شاخص ] = ( uint32_t ) ( px_بالاترین_از_پشته - 8 ); /* PSP with the hardware saved stack. */
        ul_شاخص++;
        xMPUSettings->ulContext[ ul_شاخص ] = ( uint32_t ) px_انتها_از_پشته; /* PSPLIM. */
        ul_شاخص++;

        #إذا ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
        {
            /* Check PACBTI security feature configuration before pushing the
             * CONTROL register's value on task's TCB. */
            #إذا ( config_عدد_از_CORES == 1 )
                ulControl = prvConfigurePACBTI( pdFALSE );
            #وإلا /* configNUMBER_OF_CORES > 1 */
                ulControl = vConfigurePACBTI( pdFALSE );
            #پایان_اگر /* configNUMBER_OF_CORES */
        }
        #پایان_اگر /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

        إذا( x_پیاپی_Privileged == pdTRUE )
        {
            xMPUSettings->ulTaskFlags |= پورت_TASK_IS_PRIVILEGED_FLAG;
            xMPUSettings->ulContext[ ul_شاخص ] = ( ulControl | ( uint32_t ) پورت_INITIAL_CONTROL_PRIVILEGED ); /* CONTROL. */
            ul_شاخص++;
        }
        وإلا
        {
            xMPUSettings->ulTaskFlags &= ( ~پورت_TASK_IS_PRIVILEGED_FLAG );
            xMPUSettings->ulContext[ ul_شاخص ] = ( ulControl | ( uint32_t ) پورت_INITIAL_CONTROL_UNPRIVILEGED ); /* CONTROL. */
            ul_شاخص++;
        }

        xMPUSettings->ulContext[ ul_شاخص ] = پورت_INITIAL_EXC_RETURN; /* LR (EXC_RETURN). */
        ul_شاخص++;

        #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
        {
            /* Ensure that the system call stack is double word aligned. */
            xMPUSettings->x_System_Call_پشته_Info.pul_System_Call_پشته = &( xMPUSettings->x_System_Call_پشته_Info.ul_System_Call_پشته_میانگیر[ config_SYSTEM_CALL_پشته_اندازه - 1 ] );
            xMPUSettings->x_System_Call_پشته_Info.pul_System_Call_پشته = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_پشته_Info.pul_System_Call_پشته ) &
                                                                                     ( uint32_t ) ( ~( پورت_BYTE_ALIGNMENT_ماسک ) ) );

            xMPUSettings->x_System_Call_پشته_Info.pul_System_Call_پشته_حد = &( xMPUSettings->x_System_Call_پشته_Info.ul_System_Call_پشته_میانگیر[ 0 ] );
            xMPUSettings->x_System_Call_پشته_Info.pul_System_Call_پشته_حد = ( uint32_t * ) ( ( ( uint32_t ) ( xMPUSettings->x_System_Call_پشته_Info.pul_System_Call_پشته_حد ) +
                                                                                            ( uint32_t ) ( پورت_BYTE_ALIGNMENT - 1 ) ) &
                                                                                          ( uint32_t ) ( ~( پورت_BYTE_ALIGNMENT_ماسک ) ) );

            /* This is not NULL only for the duration of a system call. */
            xMPUSettings->x_System_Call_پشته_Info.pul_Task_پشته = عدم;
        }
        #پایان_اگر /* configUSE_MPU_WRAPPERS_V1 == 0 */

        #إذا ( configENABLE_PAC == 1 )
        {
            uint32_t ul_Task_Pac_کلید[ 4 ], i;

            v_Application_Generate_Task_Random_Pac_کلید( &( ul_Task_Pac_کلید[ 0 ] ) );

            لكل( i = 0; i < 4; i++ )
            {
                xMPUSettings->ulContext[ ul_شاخص ] = ul_Task_Pac_کلید[ i ];
                ul_شاخص++;
            }
        }
        #پایان_اگر /* configENABLE_PAC */

        أرجع &( xMPUSettings->ulContext[ ul_شاخص ] );
    }

#وإلا /* configENABLE_MPU */

    پشته_Type_t * px_پورت_Initialise_پشته( پشته_Type_t * px_بالاترین_از_پشته,
                                         پشته_Type_t * px_انتها_از_پشته,
                                         TaskFunction_t px_کد,
                                         فراغ * pvParameters ) /* PRIVILEGED_FUNCTION */
    {
        /* Simulate the stack frame as it would be created by a context switch
         * interrupt. */
        #إذا ( پورت_PRELOAD_REGISTERS == 0 )
        {
            px_بالاترین_از_پشته--; /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_بالاترین_از_پشته = پورت_INITIAL_XPSR; /* xPSR. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) px_کد; /* PC. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_TASK_RETURN_آدرس; /* LR. */
            px_بالاترین_از_پشته -= 5; /* R12, R3, R2 and R1. */
            *px_بالاترین_از_پشته = ( پشته_Type_t ) pvParameters; /* R0. */
            px_بالاترین_از_پشته -= 9; /* R11..R4, EXC_RETURN. */
            *px_بالاترین_از_پشته = پورت_INITIAL_EXC_RETURN;
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) px_انتها_از_پشته; /* Slot used to hold this task's PSPLIM value. */

            #إذا ( configENABLE_TRUSTZONE == 1 )
            {
                px_بالاترین_از_پشته--;
                *px_بالاترین_از_پشته = پورت_NO_SECURE_CONTEXT; /* Slot used to hold this task's xSecureContext value. */
            }
            #پایان_اگر /* configENABLE_TRUSTZONE */
        }
        #وإلا /* portPRELOAD_REGISTERS */
        {
            px_بالاترین_از_پشته--; /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_بالاترین_از_پشته = پورت_INITIAL_XPSR; /* xPSR. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) px_کد; /* PC. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_TASK_RETURN_آدرس; /* LR. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x12121212UL; /* R12. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x03030303UL; /* R3. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x02020202UL; /* R2. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x01010101UL; /* R1. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) pvParameters; /* R0. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x11111111UL; /* R11. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x10101010UL; /* R10. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x09090909UL; /* R09. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x08080808UL; /* R08. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x07070707UL; /* R07. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x06060606UL; /* R06. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x05050505UL; /* R05. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x04040404UL; /* R04. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = پورت_INITIAL_EXC_RETURN; /* EXC_RETURN. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) px_انتها_از_پشته; /* Slot used to hold this task's PSPLIM value. */

            #إذا ( configENABLE_TRUSTZONE == 1 )
            {
                px_بالاترین_از_پشته--;
                *px_بالاترین_از_پشته = پورت_NO_SECURE_CONTEXT; /* Slot used to hold this task's xSecureContext value. */
            }
            #پایان_اگر /* configENABLE_TRUSTZONE */
        }
        #پایان_اگر /* portPRELOAD_REGISTERS */

        #إذا ( configENABLE_PAC == 1 )
        {
            uint32_t ul_Task_Pac_کلید[ 4 ], i;

            v_Application_Generate_Task_Random_Pac_کلید( &( ul_Task_Pac_کلید[ 0 ] ) );

            لكل( i = 0; i < 4; i++ )
            {
                px_بالاترین_از_پشته--;
                *px_بالاترین_از_پشته = ul_Task_Pac_کلید[ i ];
            }
        }
        #پایان_اگر /* configENABLE_PAC */

        أرجع px_بالاترین_از_پشته;
    }

#پایان_اگر /* configENABLE_MPU */
/*-----------------------------------------------------------*/

پایه_Type_t x_پورت_شروع_Scheduler( فراغ ) /* PRIVILEGED_FUNCTION */
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
        ثابت پورت_ISR_t * ثابت px_وکتور_جدول = پورت_SCB_VTOR_REG;

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
        configASSERT( px_وکتور_جدول[ پورت_وکتور_شاخص_SVC ] == SVC_Handler );
        configASSERT( px_وکتور_جدول[ پورت_وکتور_شاخص_PENDSV ] == PendSV_Handler );
    }
    #پایان_اگر /* configCHECK_HANDLER_INSTALLATION */

    v_پورت_Configure_وقفه_Priorities();

    #إذا ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
    {
        /* Set the CONTROL register value based on PACBTI security feature
         * configuration before starting the first task. */
        #إذا ( config_عدد_از_CORES == 1 )
            ( فراغ ) prvConfigurePACBTI( pdTRUE );
        #وإلا /* configNUMBER_OF_CORES > 1 */
            ( فراغ ) vConfigurePACBTI( pdTRUE );
        #پایان_اگر /* configNUMBER_OF_CORES */
    }
    #پایان_اگر /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

    #إذا ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        prv_راهاندازی_MPU();
    }
    #پایان_اگر /* configENABLE_MPU */

    #إذا ( config_عدد_از_CORES > 1 )
        /* Start the timer that generates the tick ISR. Interrupts are disabled
         * here already. */
        v_پورت_راهاندازی_Timer_وقفه();
        /* Initialize the critical nesting count for all cores. */
        لكل ( uint8_t ucCoreID = 0; ucCoreID < config_عدد_از_CORES; ucCoreID++ )
        {
            ulCriticalNestings[ ucCoreID ] = 0;
        }
        /* Signal that primary core has done all the necessary initialisations. */
        uc_Primary_Core_Init_انجامشده_Flag = 1;
        /* Wake up secondary cores */
        پایه_Type_t x_Wake_نتیجه = configWAKE_SECONDARY_CORES();
        configASSERT( x_Wake_نتیجه == pdTRUE );

        /* Hold the primary core here until all the secondary cores are ready, this would be achieved only when
         * all elements of ucSecondaryCoresReadyFlags are set.
         */
        طالما( 1 )
        {
            پایه_Type_t xAllCoresReady = pdTRUE;
            لكل( uint8_t ucCoreID = 0; ucCoreID < ( config_عدد_از_CORES - 1 ); ucCoreID++ )
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
        v_پورت_راهاندازی_Timer_وقفه();
        /* Initialize the critical nesting count ready for the first task. */
        ulCriticalNesting = 0;
    #پایان_اگر /* if ( configNUMBER_OF_CORES > 1 ) */

    #إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )
    {
        xSchedulerRunning = pdTRUE;
    }
    #پایان_اگر /* ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

    /* Start the first task. */
    v_شروع_اولی_Task();

    /* Should never get here as the tasks will now be executing. Call the task
     * exit error function to prevent compiler warnings about a static function
     * not being called in the case that the application writer overrides this
     * functionality by defining configTASK_RETURN_ADDRESS. Call
     * vTaskSwitchContext() so link time optimization does not remove the
     * symbol. */
    #إذا ( config_عدد_از_CORES > 1 )
        vTaskSwitchContext( پورت_GET_CORE_ID() );
    #وإلا
        vTaskSwitchContext();
    #پایان_اگر
    prvTaskExitError();

    /* Should not get here. */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_انتها_Scheduler( فراغ ) /* PRIVILEGED_FUNCTION */
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    #إذا ( config_عدد_از_CORES == 1 )
        configASSERT( ulCriticalNesting == 1000UL );
    #وإلا /* if ( configNUMBER_OF_CORES == 1 ) */
        configASSERT( ulCriticalNestings[ پورت_GET_CORE_ID() ] == 1000UL );
    #پایان_اگر /* if ( configNUMBER_OF_CORES == 1 ) */
}
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    فراغ v_پورت_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ثابت بنية x_حافظه_REGION * ثابت xRegions,
                                    پشته_Type_t * px_Bottom_از_پشته,
                                    config_پشته_عمق_TYPE ux_پشته_عمق )
    {
        uint32_t ul_Region_شروع_آدرس, ul_Region_انتها_آدرس, ul_Region_عدد;
        int32_t l_شاخص = 0;

        #إذا defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint32_t * __privileged_sram_start__;
            خارجي uint32_t * __privileged_sram_end__;
        #وإلا
            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint32_t __privileged_sram_start__[];
            خارجي uint32_t __privileged_sram_end__[];
        #پایان_اگر /* defined( __ARMCC_VERSION ) */

        /* Setup MAIR0. */
        xMPUSettings->ulMAIR0 = ( ( پورت_MPU_نرمال_حافظه_BUFFERABLE_CACHEABLE << پورت_MPU_MAIR_ATTR0_POS ) & پورت_MPU_MAIR_ATTR0_ماسک );
        xMPUSettings->ulMAIR0 |= ( ( پورت_MPU_DEVICE_حافظه_n_Gn_RE << پورت_MPU_MAIR_ATTR1_POS ) & پورت_MPU_MAIR_ATTR1_ماسک );

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid.  At all other
         * times the stack parameters will not be valid and it is assumed that
         * the stack region has already been configured. */
        إذا( ux_پشته_عمق > 0 )
        {
            ul_Region_شروع_آدرس = ( uint32_t ) px_Bottom_از_پشته;
            ul_Region_انتها_آدرس = ( uint32_t ) px_Bottom_از_پشته + ( ux_پشته_عمق * ( config_پشته_عمق_TYPE ) حجم( پشته_Type_t ) ) - 1;

            /* If the stack is within the privileged SRAM, do not protect it
             * using a separate MPU region. This is needed because privileged
             * SRAM is already protected using an MPU region and ARMv8-M does
             * not allow overlapping MPU regions. */
            إذا( ( ul_Region_شروع_آدرس >= ( uint32_t ) __privileged_sram_start__ ) &&
                ( ul_Region_انتها_آدرس <= ( uint32_t ) __privileged_sram_end__ ) )
            {
                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR = 0;
                xMPUSettings->xRegionsSettings[ 0 ].ulRLAR = 0;
            }
            وإلا
            {
                /* Define the region that allows access to the stack. */
                ul_Region_شروع_آدرس &= پورت_MPU_RBAR_آدرس_ماسک;
                ul_Region_انتها_آدرس &= پورت_MPU_RLAR_آدرس_ماسک;

                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR = ( ul_Region_شروع_آدرس ) |
                                                             ( پورت_MPU_REGION_NON_SHAREABLE ) |
                                                             ( پورت_MPU_REGION_READ_WRITE ) |
                                                             ( پورت_MPU_REGION_EXECUTE_NEVER );

                xMPUSettings->xRegionsSettings[ 0 ].ulRLAR = ( ul_Region_انتها_آدرس ) |
                                                             ( پورت_MPU_RLAR_ATTR_INDEX0 ) |
                                                             ( پورت_MPU_RLAR_REGION_ENABLE );
            }
        }

        /* User supplied configurable regions. */
        لكل( ul_Region_عدد = 1; ul_Region_عدد <= پورت_رقم_CONFIGURABLE_REGIONS; ul_Region_عدد++ )
        {
            /* If xRegions is NULL i.e. the task has not specified any MPU
             * region, the else part ensures that all the configurable MPU
             * regions are invalidated. */
            إذا( ( xRegions != عدم ) && ( xRegions[ l_شاخص ].ul_درازی_درون_بایتها > 0UL ) )
            {
                /* Translate the generic region definition contained in xRegions
                 * into the ARMv8 specific MPU settings that are then stored in
                 * xMPUSettings. */
                ul_Region_شروع_آدرس = ( ( uint32_t ) xRegions[ l_شاخص ].pv_پایه_آدرس ) & پورت_MPU_RBAR_آدرس_ماسک;
                ul_Region_انتها_آدرس = ( uint32_t ) xRegions[ l_شاخص ].pv_پایه_آدرس + xRegions[ l_شاخص ].ul_درازی_درون_بایتها - 1;
                ul_Region_انتها_آدرس &= پورت_MPU_RLAR_آدرس_ماسک;

                /* Start address. */
                xMPUSettings->xRegionsSettings[ ul_Region_عدد ].ulRBAR = ( ul_Region_شروع_آدرس ) |
                                                                          ( پورت_MPU_REGION_NON_SHAREABLE );

                /* RO/RW. */
                إذا( ( xRegions[ l_شاخص ].ulParameters & tskMPU_REGION_READ_ONLY ) != 0 )
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_عدد ].ulRBAR |= ( پورت_MPU_REGION_READ_ONLY );
                }
                وإلا
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_عدد ].ulRBAR |= ( پورت_MPU_REGION_READ_WRITE );
                }

                /* XN. */
                إذا( ( xRegions[ l_شاخص ].ulParameters & tskMPU_REGION_EXECUTE_NEVER ) != 0 )
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_عدد ].ulRBAR |= ( پورت_MPU_REGION_EXECUTE_NEVER );
                }

                /* End Address. */
                xMPUSettings->xRegionsSettings[ ul_Region_عدد ].ulRLAR = ( ul_Region_انتها_آدرس ) |
                                                                          ( پورت_MPU_RLAR_REGION_ENABLE );

                /* PXN. */
                #إذا ( پورت_ARMV8_M_MINOR_نسخه >= 1 )
                {
                    إذا( ( xRegions[ l_شاخص ].ulParameters & tskMPU_REGION_PRIVILEGED_EXECUTE_NEVER ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ ul_Region_عدد ].ulRLAR |= ( پورت_MPU_RLAR_PRIVILEGED_EXECUTE_NEVER );
                    }
                }
                #پایان_اگر /* portARMV8M_MINOR_VERSION >= 1 */

                /* Normal memory/ Device memory. */
                إذا( ( xRegions[ l_شاخص ].ulParameters & tsk_MPU_REGION_DEVICE_حافظه ) != 0 )
                {
                    /* Attr1 in MAIR0 is configured as device memory. */
                    xMPUSettings->xRegionsSettings[ ul_Region_عدد ].ulRLAR |= پورت_MPU_RLAR_ATTR_INDEX1;
                }
                وإلا
                {
                    /* Attr0 in MAIR0 is configured as normal memory. */
                    xMPUSettings->xRegionsSettings[ ul_Region_عدد ].ulRLAR |= پورت_MPU_RLAR_ATTR_INDEX0;
                }
            }
            وإلا
            {
                /* Invalidate the region. */
                xMPUSettings->xRegionsSettings[ ul_Region_عدد ].ulRBAR = 0UL;
                xMPUSettings->xRegionsSettings[ ul_Region_عدد ].ulRLAR = 0UL;
            }

            l_شاخص++;
        }
    }

#پایان_اگر /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    پایه_Type_t x_پورت_Is_Authorized_مقصد_Access_میانگیر( ثابت فراغ * pv_میانگیر,
                                                size_t x_میانگیر_درازی,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_میانگیر_شروع_آدرس, ul_میانگیر_انتها_آدرس;
        پایه_Type_t xAccessGranted = pdFALSE;
        ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( عدم ); /* Calling task's MPU settings. */

        إذا( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        وإلا إذا( ( xTaskMpuSettings->ulTaskFlags & پورت_TASK_IS_PRIVILEGED_FLAG ) == پورت_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        وإلا
        {
            إذا( پورت_جمع_کن_UINT32_WILL_سرریز( ( ( uint32_t ) pv_میانگیر ), ( ( uint32_t ) x_میانگیر_درازی - 1UL ) ) == pdFALSE )
            {
                ul_میانگیر_شروع_آدرس = ( uint32_t ) pv_میانگیر;
                ul_میانگیر_انتها_آدرس = ( ( ( uint32_t ) pv_میانگیر ) + ( uint32_t ) x_میانگیر_درازی - 1UL );

                لكل( i = 0; i < پورت_مجموع_رقم_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    إذا( ( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR & پورت_MPU_RLAR_REGION_ENABLE ) == پورت_MPU_RLAR_REGION_ENABLE )
                    {
                        إذا( پورت_IS_آدرس_WITHIN_RANGE( ul_میانگیر_شروع_آدرس,
                                                         پورت_استخراج_اولی_آدرس_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ),
                                                         پورت_استخراج_آخرین_آدرس_FROM_RLAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR ) ) &&
                            پورت_IS_آدرس_WITHIN_RANGE( ul_میانگیر_انتها_آدرس,
                                                         پورت_استخراج_اولی_آدرس_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ),
                                                         پورت_استخراج_آخرین_آدرس_FROM_RLAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR ) ) &&
                            پورت_IS_AUTHORIZED( ulAccessRequested,
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

#پایان_اگر /* #if ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

پایه_Type_t x_پورت_Is_Inside_وقفه( فراغ )
{
    uint32_t ul_Current_وقفه;
    پایه_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. Interrupt Program
     * Status Register (IPSR) holds the exception number of the currently-executing
     * exception or zero for Thread mode.*/
    __asm متطاير ( "mrs %0, ipsr" : "=r" ( ul_Current_وقفه )::"memory" );

    إذا( ul_Current_وقفه == 0 )
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

#إذا ( ( configASSERT_DEFINED == 1 ) && ( پورت_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) )

    فراغ v_پورت_Validate_وقفه_اولویت( فراغ )
    {
        uint32_t ul_Current_وقفه;
        uint8_t uc_Current_اولویت;

        /* Obtain the number of the currently executing interrupt. */
        __asm متطاير ( "mrs %0, ipsr" : "=r" ( ul_Current_وقفه )::"memory" );

        /* Is the interrupt number a user defined interrupt? */
        إذا( ul_Current_وقفه >= پورت_اولی_USER_وقفه_عدد )
        {
            /* Look up the interrupt's priority. */
            uc_Current_اولویت = pc_وقفه_اولویت_Registers[ ul_Current_وقفه ];

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
            configASSERT( uc_Current_اولویت >= uc_Max_Sys_Call_اولویت );
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
        configASSERT( ( پورت_AIRCR_REG & پورت_اولویت_گروه_ماسک ) <= ulMaxPRIGROUPValue );
    }

#پایان_اگر /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */
/*-----------------------------------------------------------*/

فراغ v_پورت_Configure_وقفه_Priorities( فراغ ) /* PRIVILEGED_FUNCTION */
{
    #إذا ( ( configASSERT_DEFINED == 1 ) && ( پورت_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) )
    {
        متطاير uint32_t ul_Implemented_Prio_بیتها = 0;
        متطاير uint8_t uc_Max_اولویت_مقدار;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
        * functions can be called. ISR safe functions are those that end in
        * "FromISR". FreeRTOS maintains separate thread and ISR API functions to
        * ensure interrupt entry is as fast and simple as possible.
        *
        * First, determine the number of priority bits available. Write to all
        * possible bits in the priority setting for SVCall. */
        پورت_NVIC_SHPR2_REG = 0xFF000000;

        /* Read the value back to see how many bits stuck. */
        uc_Max_اولویت_مقدار = ( uint8_t ) ( ( پورت_NVIC_SHPR2_REG & 0xFF000000 ) >> 24 );

        /* Use the same mask on the maximum system call priority. */
        uc_Max_Sys_Call_اولویت = config_MAX_SYSCALL_وقفه_اولویت & uc_Max_اولویت_مقدار;

        /* Check that the maximum system call priority is nonzero after
        * accounting for the number of priority bits supported by the
        * hardware. A priority of 0 is invalid because setting the BASEPRI
        * register to 0 unmasks all interrupts, and interrupts with priority 0
        * cannot be masked using BASEPRI.
        * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( uc_Max_Sys_Call_اولویت );

        /* Check that the bits not implemented in hardware are zero in
        * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( config_MAX_SYSCALL_وقفه_اولویت & ( uint8_t ) ( ~( uint32_t ) uc_Max_اولویت_مقدار ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
        * of bits read back. */
        طالما( ( uc_Max_اولویت_مقدار & پورت_بالاترین_بیت_از_BYTE ) == پورت_بالاترین_بیت_از_BYTE )
        {
            ul_Implemented_Prio_بیتها++;
            uc_Max_اولویت_مقدار <<= ( uint8_t ) 0x01;
        }

        إذا( ul_Implemented_Prio_بیتها == 8 )
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
            configASSERT( ( config_MAX_SYSCALL_وقفه_اولویت & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        وإلا
        {
            ulMaxPRIGROUPValue = پورت_MAX_PRIGROUP_بیتها - ul_Implemented_Prio_بیتها;
        }

        /* Shift the priority group value back to its position within the AIRCR
        * register. */
        ulMaxPRIGROUPValue <<= پورت_PRIGROUP_لغزش;
        ulMaxPRIGROUPValue &= پورت_اولویت_گروه_ماسک;
    }
    #پایان_اگر /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */

    /* Make PendSV and SysTick the lowest priority interrupts, and make SVCall
    * the highest priority. */
    پورت_NVIC_SHPR3_REG |= پورت_NVIC_PENDSV_PRI;
    پورت_NVIC_SHPR3_REG |= پورت_NVIC_SYSTICK_PRI;
    پورت_NVIC_SHPR2_REG = 0;
}
/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    فراغ v_پورت_Grant_Access_مقصد_Kernel_Object( TaskHandle_t x_داخلی_Task_Handle,
                                         int32_t l_داخلی_شاخص_از_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_مدخل_شاخص, ul_Access_Control_List_مدخل_بیت;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_مدخل_شاخص = ( ( uint32_t ) l_داخلی_شاخص_از_Kernel_Object / پورت_ACL_مدخل_اندازه_بیتها );
        ul_Access_Control_List_مدخل_بیت = ( ( uint32_t ) l_داخلی_شاخص_از_Kernel_Object % پورت_ACL_مدخل_اندازه_بیتها );

        xTaskMpuSettings = xTaskGetMPUSettings( x_داخلی_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_مدخل_شاخص ] |= ( 1U << ul_Access_Control_List_مدخل_بیت );
    }

#پایان_اگر /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    فراغ v_پورت_Revoke_Access_مقصد_Kernel_Object( TaskHandle_t x_داخلی_Task_Handle,
                                          int32_t l_داخلی_شاخص_از_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_مدخل_شاخص, ul_Access_Control_List_مدخل_بیت;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_مدخل_شاخص = ( ( uint32_t ) l_داخلی_شاخص_از_Kernel_Object / پورت_ACL_مدخل_اندازه_بیتها );
        ul_Access_Control_List_مدخل_بیت = ( ( uint32_t ) l_داخلی_شاخص_از_Kernel_Object % پورت_ACL_مدخل_اندازه_بیتها );

        xTaskMpuSettings = xTaskGetMPUSettings( x_داخلی_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_مدخل_شاخص ] &= ~( 1U << ul_Access_Control_List_مدخل_بیت );
    }

#پایان_اگر /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        پایه_Type_t x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( int32_t l_داخلی_شاخص_از_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_مدخل_شاخص, ul_Access_Control_List_مدخل_بیت;
            پایه_Type_t xAccessGranted = pdFALSE;
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

                ul_Access_Control_List_مدخل_شاخص = ( ( uint32_t ) l_داخلی_شاخص_از_Kernel_Object / پورت_ACL_مدخل_اندازه_بیتها );
                ul_Access_Control_List_مدخل_بیت = ( ( uint32_t ) l_داخلی_شاخص_از_Kernel_Object % پورت_ACL_مدخل_اندازه_بیتها );

                إذا( ( xTaskMpuSettings->ulTaskFlags & پورت_TASK_IS_PRIVILEGED_FLAG ) == پورت_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                وإلا
                {
                    إذا( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_مدخل_شاخص ] & ( 1U << ul_Access_Control_List_مدخل_بیت ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            أرجع xAccessGranted;
        }

    #وإلا /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        پایه_Type_t x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( int32_t l_داخلی_شاخص_از_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( فراغ ) l_داخلی_شاخص_از_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            أرجع pdTRUE;
        }

    #پایان_اگر /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#پایان_اگر /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */
/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
    #إذا ( config_عدد_از_CORES == 1 )
        ساكن uint32_t prvConfigurePACBTI( پایه_Type_t x_Write_Control_ثبات )
    #وإلا /* configNUMBER_OF_CORES > 1 */
        uint32_t vConfigurePACBTI( پایه_Type_t x_Write_Control_ثبات )
    #پایان_اگر /* configNUMBER_OF_CORES */
        {
            uint32_t ulControl = 0x0;

            /* Ensure that PACBTI is implemented. */
            configASSERT( پورت_ID_ISAR5_REG != 0x0 );

            /* Enable UsageFault exception. */
            پورت_SCB_SYS_HANDLER_CTRL_STATE_REG |= پورت_SCB_USG_FAULT_ENABLE_بیت;

            #إذا ( configENABLE_PAC == 1 )
            {
                ulControl |= ( پورت_CONTROL_UPAC_EN | پورت_CONTROL_PAC_EN );
            }
            #پایان_اگر

            #إذا ( configENABLE_BTI == 1 )
            {
                ulControl |= ( پورت_CONTROL_UBTI_EN | پورت_CONTROL_BTI_EN );
            }
            #پایان_اگر

            إذا( x_Write_Control_ثبات == pdTRUE )
            {
                __asm متطاير ( "msr control, %0" : : "r" ( ulControl ) );
            }

            أرجع ulControl;
        }

#پایان_اگر /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */
/*-----------------------------------------------------------*/

#إذا ( config_عدد_از_CORES > 1 )

    /* Which core owns the lock? */
    PRIVILEGED_داده متطاير uint32_t ulOwnedByCore[ پورت_MAX_CORE_شمار ];
    /* Lock count a core owns. */
    PRIVILEGED_داده متطاير uint32_t ul_Recursion_شمار_By_قفل[ e_قفل_شمار ];
    /* Index 0 is used for ISR lock and Index 1 is used for task lock. */
    PRIVILEGED_داده متطاير uint32_t ul_Gate_کلمه[ e_قفل_شمار ];

    __attribute__((weak)) فراغ v_وقفه_Core( uint8_t ucCoreID )
    {
        /* Default weak stub - platform specific implementation may override. */
        ( فراغ ) ucCoreID;
    }

/*-----------------------------------------------------------*/

    ساكن مضمن فراغ prvSpinUnlock( متطاير uint32_t * ul_قفل )
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
            : "r" ( ul_قفل )
            : "memory", "r1"
        );
    }

/*-----------------------------------------------------------*/

    ساكن مضمن uint32_t prvSpinTrylock( متطاير uint32_t * ul_قفل )
    {
        /*
         * Conservative ldrex/strex trylock:
         * - Return 1 immediately if busy, clearing exclusive state (CLREX).
         * - Retry strex only on spurious failure when observed free.
         * - DMB on success to preserve expected acquire semantics.
         */
        uint32_t ulVal;
        uint32_t ul_وضعیت;

        __asm متطاير (
            " ldrex %0, [%1]   \n"
            : "=r" ( ulVal )
            : "r" ( ul_قفل )
            : "memory"
        );

        إذا( ulVal != 0U )
        {
            __asm متطاير ("clrex" ::: "memory");
            أرجع 1U;
        }

        __asm متطاير (
            " strex %0, %2, [%1]   \n"
            : "=&r" ( ul_وضعیت )
            : "r" ( ul_قفل ), "r" (1U)
            : "memory"
        );

        إذا( ul_وضعیت != 0U )
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
                                 uint32_t مقدار )
    {
        *x = مقدار;
        __asm( "dsb" );
    }

/*-----------------------------------------------------------*/

    فراغ v_پورت_Recursive_قفل( uint8_t ucCoreID,
                             e_پورت_RTOSLock e_قفل_رقم,
                             پایه_Type_t uxAcquire )
    {
        /* Validate the core ID and lock number. */
        configASSERT( ucCoreID < پورت_MAX_CORE_شمار );
        configASSERT( e_قفل_رقم < e_قفل_شمار );

        uint32_t ul_قفل_بیت = 1u << e_قفل_رقم;

        /* Lock acquire */
        إذا( uxAcquire )
        {
            /* Check if spinlock is available. */
            /* If spinlock is not available check if the core owns the lock. */
            /* If the core owns the lock wait increment the lock count by the core. */
            /* If core does not own the lock wait for the spinlock. */
            إذا( prvSpinTrylock( &ul_Gate_کلمه[ e_قفل_رقم ] ) != 0 )
            {
                /* Check if the core owns the spinlock. */
                إذا( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ul_قفل_بیت )
                {
                    configASSERT( prvGet32( &ul_Recursion_شمار_By_قفل[ e_قفل_رقم ] ) != پورت_UINT32_MAX );
                    prvSet32( &ul_Recursion_شمار_By_قفل[ e_قفل_رقم ], ( prvGet32( &ul_Recursion_شمار_By_قفل[ e_قفل_رقم ] ) + 1 ) );
                    أرجع;
                }

                /* Preload the gate word into the cache. */
                uint32_t dummy = ul_Gate_کلمه[ e_قفل_رقم ];
                dummy++;

                طالما( prvSpinTrylock( &ul_Gate_کلمه[ e_قفل_رقم ] ) != 0 )
                {
                    __asm متطاير ( "wfe" );
                }
            }

            /* Add barrier to ensure lock is taken before we proceed. */
            __asm متطاير( "dmb sy" ::: "memory" );

            /* Assert the lock count is 0 when the spinlock is free and is acquired. */
            configASSERT( prvGet32( &ul_Recursion_شمار_By_قفل[ e_قفل_رقم ] ) == 0 );

            /* Set lock count as 1. */
            prvSet32( &ul_Recursion_شمار_By_قفل[ e_قفل_رقم ], 1 );
            /* Set ulOwnedByCore. */
            prvSet32( &ulOwnedByCore[ ucCoreID ], ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) | ul_قفل_بیت ) );
        }
        /* Lock release. */
        وإلا
        {
            /* Assert the lock is not free already. */
            configASSERT( ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ul_قفل_بیت ) != 0 );
            configASSERT( prvGet32( &ul_Recursion_شمار_By_قفل[ e_قفل_رقم ] ) != 0 );

            /* Reduce ulRecursionCountByLock by 1. */
            prvSet32( &ul_Recursion_شمار_By_قفل[ e_قفل_رقم ], ( prvGet32( &ul_Recursion_شمار_By_قفل[ e_قفل_رقم ] ) - 1 ) );

            إذا( !prvGet32( &ul_Recursion_شمار_By_قفل[ e_قفل_رقم ] ) )
            {
                prvSet32( &ulOwnedByCore[ ucCoreID ], ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ~ul_قفل_بیت ) );
                prvSpinUnlock( &ul_Gate_کلمه[ e_قفل_رقم ] );
                /* Add barrier to ensure lock status is reflected before we proceed. */
                __asm متطاير( "dmb sy" ::: "memory" );
            }
        }
    }

/*-----------------------------------------------------------*/

    uint8_t uc_پورت_Get_Core_ID( فراغ )
    {
        أرجع *(متطاير uint8_t *)(config_CORE_ID_ثبات);
    }

/*-----------------------------------------------------------*/

#پایان_اگر /* if( configNUMBER_OF_CORES > 1 ) */
