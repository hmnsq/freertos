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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

/* MPU includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "mpu_wrappers.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mpu_syscall_numbers.h"

/* Portasm includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "portasm.h"

#ਜੇ ( configENABLE_TRUSTZONE == 1 )
    /* Secure components includes. */
    #ਅਨ੍ਤਰ੍ਭਾਵ "secure_context.h"
    #ਅਨ੍ਤਰ੍ਭਾਵ "secure_init.h"
#ਜੇ_ਅੰਤ /* configENABLE_TRUSTZONE */

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

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
#ਜੇ ( ( config_ਲੜੀਵਾਰ_FREERTOS_SECURE_ONLY == 1 ) && ( configENABLE_TRUSTZONE == 1 ) )
    #ਗਲਤੀ TrustZone needs ਮੰਜ਼ਿਲ be disabled ਵਿੱਚ_2 ਕ੍ਰਮ ਮੰਜ਼ਿਲ ਲੜੀਵਾਰ FreeRTOS on the Secure Side.
#ਜੇ_ਅੰਤ

/**
 * Cortex-M23 does not have non-secure PSPLIM. We should use PSPLIM on Cortex-M23
 * only when FreeRTOS runs on secure side.
 */
#ਜੇ ( ( ਪੋਰਟ_HAS_ARMV8_M_MAIN_EXTENSION == 0 ) && ( config_ਲੜੀਵਾਰ_FREERTOS_SECURE_ONLY == 0 ) )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_USE_PSPLIM_ਰਜਿਸਟਰ    0
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_USE_PSPLIM_ਰਜਿਸਟਰ    1
#ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

/**
 * @brief Prototype of all Interrupt Service Routines (ISRs).
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ ( * ਪੋਰਟ_ISR_t )( ਖਾਲੀ );
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the NVIC.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG             ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000e010 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG             ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000e014 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG    ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000e018 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SHPR3_REG                    ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed20 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ           ( 1UL << 0UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_INT_ਦੋਆਧਾਰੀ_ਅੰਕ              ( 1UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ              ( 1UL << 2UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_ਗਿਣਤੀ_FLAG_ਦੋਆਧਾਰੀ_ਅੰਕ       ( 1UL << 16UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_PEND_SYSTICK_CLEAR_ਦੋਆਧਾਰੀ_ਅੰਕ       ( 1UL << 25UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_PEND_SYSTICK_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ         ( 1UL << 26UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MIN_ਰੁਕਾਵਟ_ਤਰਜੀਹ            ( 255UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_PENDSV_PRI                   ( ਪੋਰਟ_MIN_ਰੁਕਾਵਟ_ਤਰਜੀਹ << 16UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_PRI                  ( ਪੋਰਟ_MIN_ਰੁਕਾਵਟ_ਤਰਜੀਹ << 24UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the SCB.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SCB_VTOR_REG                      ( *( ( ਪੋਰਟ_ISR_t ** ) 0xe000ed08 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SCB_SYS_HANDLER_CTRL_STATE_REG    ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed24 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SCB_MEM_FAULT_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ          ( 1UL << 16UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SCB_USG_FAULT_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ          ( 1UL << 18UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants used to check the installation of the FreeRTOS interrupt handlers.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਦਿਸ਼_ਸੂਚਕਾਂਕ_SVC       ( 11 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਦਿਸ਼_ਸੂਚਕਾਂਕ_PENDSV    ( 14 )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to check the validity of an interrupt priority.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SHPR2_REG                 ( *( ( ਅਸਥਿਰ uint32_t * ) 0xE000ED1C ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਪਹਿਲਾ_USER_ਰੁਕਾਵਟ_ਸੰਖਿਆ    ( 16 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_IP_REGISTERS_ਵਿੱਥ_16    ( 0xE000E3F0 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_AIRCR_REG                      ( *( ( ਅਸਥਿਰ uint32_t * ) 0xE000ED0C ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਿਖਰ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਦਾ_BYTE                ( ( uint8_t ) 0x80 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_PRIGROUP_ਬਿੱਟ              ( ( uint8_t ) 7 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਤਰਜੀਹ_ਸਮੂਹ_ਨਕਾਬ            ( 0x07UL << 8UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIGROUP_ਖਿਸਕਾਓ                 ( 8UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants used during system call enter and exit.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PSR_ਢੇਰ_PADDING_ਨਕਾਬ              ( 1UL << 9UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXC_RETURN_ਢੇਰ_ਚੌਖਟਾ_TYPE_ਨਕਾਬ    ( 1UL << 4UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the FPU.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CPACR               ( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed88 ) /* Coprocessor Access Control Register. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CPACR_CP10_ਮੁੱਲ    ( 3UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CPACR_CP11_ਮੁੱਲ    ਪੋਰਟ_CPACR_CP10_ਮੁੱਲ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CPACR_CP10_POS      ( 20UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CPACR_CP11_POS      ( 22UL )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FPCCR               ( ( ਅਸਥਿਰ uint32_t * ) 0xe000ef34 ) /* Floating Point Context Control Register. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FPCCR_ASPEN_POS     ( 31UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FPCCR_ASPEN_ਨਕਾਬ    ( 1UL << ਪੋਰਟ_FPCCR_ASPEN_POS )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FPCCR_LSPEN_POS     ( 30UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FPCCR_LSPEN_ਨਕਾਬ    ( 1UL << ਪੋਰਟ_FPCCR_LSPEN_POS )
/*-----------------------------------------------------------*/

/**
 * @brief Offsets in the stack to the parameters when inside the SVC handler.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_LR     ( 5 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PC     ( 6 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PSR    ( 7 )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the MPU.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_TYPE_REG                        ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed90 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_CTRL_REG                        ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed94 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RNR_REG                         ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed98 ) )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RBAR_REG                        ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed9c ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RLAR_REG                        ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000eda0 ) )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RBAR_A1_REG                     ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000eda4 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RLAR_A1_REG                     ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000eda8 ) )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RBAR_A2_REG                     ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000edac ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RLAR_A2_REG                     ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000edb0 ) )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RBAR_A3_REG                     ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000edb4 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RLAR_A3_REG                     ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000edb8 ) )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR0_REG                       ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000edc0 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR1_REG                       ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000edc4 ) )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RBAR_ਪਤਾ_ਨਕਾਬ               ( 0xffffffe0 ) /* Must be 32-byte aligned. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RLAR_ਪਤਾ_ਨਕਾਬ               ( 0xffffffe0 ) /* Must be 32-byte aligned. */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RBAR_ACCESS_PERMISSIONS_ਨਕਾਬ    ( 3UL << 1UL )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_ATTR0_POS                  ( 0UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_ATTR0_ਨਕਾਬ                 ( 0x000000ff )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_ATTR1_POS                  ( 8UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_ATTR1_ਨਕਾਬ                 ( 0x0000ff00 )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_ATTR2_POS                  ( 16UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_ATTR2_ਨਕਾਬ                 ( 0x00ff0000 )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_ATTR3_POS                  ( 24UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_ATTR3_ਨਕਾਬ                 ( 0xff000000 )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_ATTR4_POS                  ( 0UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_ATTR4_ਨਕਾਬ                 ( 0x000000ff )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_ATTR5_POS                  ( 8UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_ATTR5_ਨਕਾਬ                 ( 0x0000ff00 )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_ATTR6_POS                  ( 16UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_ATTR6_ਨਕਾਬ                 ( 0x00ff0000 )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_ATTR7_POS                  ( 24UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_ATTR7_ਨਕਾਬ                 ( 0xff000000 )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RLAR_ATTR_INDEX0                ( 0UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RLAR_ATTR_INDEX1                ( 1UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RLAR_ATTR_INDEX2                ( 2UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RLAR_ATTR_INDEX3                ( 3UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RLAR_ATTR_INDEX4                ( 4UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RLAR_ATTR_INDEX5                ( 5UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RLAR_ATTR_INDEX6                ( 6UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RLAR_ATTR_INDEX7                ( 7UL << 1UL )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RLAR_REGION_ENABLE              ( 1UL )

#ਜੇ ( ਪੋਰਟ_ARMV8_M_MINOR_ਸੰਸਕਰਣ >= 1 )

    /* Enable Privileged eXecute Never MPU attribute for the selected memory
     * region. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RLAR_PRIVILEGED_EXECUTE_NEVER    ( 1UL << 4UL )
#ਜੇ_ਅੰਤ /* portARMV8M_MINOR_VERSION >= 1 */

/* Enable privileged access to unmapped region. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_PRIV_BACKGROUND_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ    ( 1UL << 2UL )

/* Enable MPU. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ                    ( 1UL << 0UL )

/* Extract first address of the MPU region as encoded in the
 * RBAR (Region Base Address Register) value. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਕੱਢੋ_ਪਹਿਲਾ_ਪਤਾ_FROM_RBAR( rbar ) \
    ( ( rbar ) & ਪੋਰਟ_MPU_RBAR_ਪਤਾ_ਨਕਾਬ )

/* Extract last address of the MPU region as encoded in the
 * RLAR (Region Limit Address Register) value. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਕੱਢੋ_ਆਖਰੀ_ਪਤਾ_FROM_RLAR( rlar ) \
    ( ( ( rlar ) & ਪੋਰਟ_MPU_RLAR_ਪਤਾ_ਨਕਾਬ ) | ~ਪੋਰਟ_MPU_RLAR_ਪਤਾ_ਨਕਾਬ )

/* Does addr lies within [start, end] address range? */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IS_ਪਤਾ_WITHIN_RANGE( addr, ਸ਼ੁਰੂ, ਸਿਰਾ ) \
    ( ( ( addr ) >= ( ਸ਼ੁਰੂ ) ) && ( ( addr ) <= ( ਸਿਰਾ ) ) )

/* Is the access request satisfied by the available permissions? */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਜੋੜੋ_UINT32_WILL_ਉਛਾਲ( a, b )    ( ( a ) > ( ਪੋਰਟ_UINT32_MAX - ( b ) ) )
/*-----------------------------------------------------------*/

/**
 * @brief The maximum 24-bit number.
 *
 * It is needed because the systick is a 24-bit counter.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_24_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੰਖਿਆ       ( 0xffffffUL )

/**
 * @brief A fiddle factor to estimate the number of SysTick counts that would
 * have occurred while the SysTick counter is stopped during tickless idle
 * calculations.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MISSED_COUNTS_ਗੁਣਕ    ( 94UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to set up the initial stack.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_XPSR    ( 0x01000000 )

#ਜੇ ( config_ਲੜੀਵਾਰ_FREERTOS_SECURE_ONLY == 1 )

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
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_EXC_RETURN    ( 0xfffffffd )
#ਨਹੀਂਤਾਂ

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
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_EXC_RETURN    ( 0xffffffbc )
#ਜੇ_ਅੰਤ /* configRUN_FREERTOS_SECURE_ONLY */

/**
 * @brief CONTROL register privileged bit mask.
 *
 * Bit[0] in CONTROL register tells the privilege:
 *  Bit[0] = 0 ==> The task is privileged.
 *  Bit[0] = 1 ==> The task is not privileged.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CONTROL_PRIVILEGED_ਨਕਾਬ         ( 1UL << 0UL )

/**
 * @brief Initial CONTROL register values.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_CONTROL_UNPRIVILEGED    ( 0x3 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_CONTROL_PRIVILEGED      ( 0x2 )

/**
 * @brief Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register.
 */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configSYSTICK_CLOCK_HZ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ_CONFIG    ( ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ )
#ਨਹੀਂਤਾਂ
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ_CONFIG    ( 0 )
#ਜੇ_ਅੰਤ

/**
 * @brief Let the user override the pre-loading of the initial LR with the
 * address of prvTaskExitError() in case it messes up unwinding of the stack
 * in the debugger.
 */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ config_TASK_RETURN_ਪਤਾ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_RETURN_ਪਤਾ    config_TASK_RETURN_ਪਤਾ
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_RETURN_ਪਤਾ    prvTaskExitError
#ਜੇ_ਅੰਤ

/**
 * @brief If portPRELOAD_REGISTERS then registers will be given an initial value
 * when a task is created. This helps in debugging at the cost of code size.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRELOAD_REGISTERS    1

/**
 * @brief A task is created without a secure context, and must call
 * portALLOCATE_SECURE_CONTEXT() to give itself a secure context before it makes
 * any secure calls.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NO_SECURE_CONTEXT    0

/**
 * @brief Constants required to check and configure PACBTI security feature implementation.
 */
#ਜੇ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ID_ISAR5_REG       ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed74 ) )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CONTROL_UPAC_EN    ( 1UL << 7UL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CONTROL_PAC_EN     ( 1UL << 6UL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CONTROL_UBTI_EN    ( 1UL << 5UL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CONTROL_BTI_EN     ( 1UL << 4UL )

#ਜੇ_ਅੰਤ /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Used to catch tasks that attempt to return from their implementing
 * function.
 */
ਸਥਿਰ ਖਾਲੀ prvTaskExitError( ਖਾਲੀ );

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Extract MPU region's access permissions from the Region Base Address
     * Register (RBAR) value.
     *
     * @param ulRBARValue RBAR value for the MPU region.
     *
     * @return uint32_t Access permissions.
     */
    ਸਥਿਰ uint32_t prvGetRegionAccessPermissions( uint32_t ulRBARValue ) PRIVILEGED_FUNCTION;
#ਜੇ_ਅੰਤ /* configENABLE_MPU == 1 && configUSE_MPU_WRAPPERS_V1 == 0 */

#ਜੇ ( configENABLE_MPU == 1 )

    /**
     * @brief Setup the Memory Protection Unit (MPU).
     */
    ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_MPU( ਖਾਲੀ ) PRIVILEGED_FUNCTION;
#ਜੇ_ਅੰਤ /* configENABLE_MPU */

#ਜੇ ( configENABLE_FPU == 1 )

    /**
     * @brief Setup the Floating Point Unit (FPU).
     */
    ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_FPU( ਖਾਲੀ ) PRIVILEGED_FUNCTION;
#ਜੇ_ਅੰਤ /* configENABLE_FPU */

#ਜੇ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )

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
    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
        ਸਥਿਰ uint32_t prvConfigurePACBTI( ਅਧਾਰ_Type_t x_Write_Control_ਰਜਿਸਟਰ );
    #ਨਹੀਂਤਾਂ /* #if ( configNUMBER_OF_CORES == 1 ) */
        uint32_t vConfigurePACBTI( ਅਧਾਰ_Type_t x_Write_Control_ਰਜਿਸਟਰ );
    #ਜੇ_ਅੰਤ /* #if ( configNUMBER_OF_CORES == 1 ) */

#ਜੇ_ਅੰਤ /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

/**
 * @brief Setup the timer to generate the tick interrupts.
 *
 * The implementation in this file is weak to allow application writers to
 * change the timer used to generate the tick interrupt.
 */
ਖਾਲੀ v_ਪੋਰਟ_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether the current execution context is interrupt.
 *
 * @return pdTRUE if the current execution context is interrupt, pdFALSE
 * otherwise.
 */
ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Inside_ਰੁਕਾਵਟ( ਖਾਲੀ );

/**
 * @brief Yield the processor.
 */
ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

/**
 * @brief Enter critical section.
 */
ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

/**
 * @brief Exit from critical section.
 */
ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

/**
 * @brief SysTick handler.
 */
ਖਾਲੀ SysTick_Handler( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

/**
 * @brief C part of SVC handler.
 */
ਪੋਰਟ_DONT_DISCARD ਖਾਲੀ v_ਪੋਰਟ_SVCHandler_C( uint32_t * pul_Caller_ਢੇਰ_ਪਤਾ ) PRIVILEGED_FUNCTION;

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the system call stack so that upon returning from
     * SVC, the system call stack is used.
     *
     * @param pulTaskStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    ਖਾਲੀ vSystemCallEnter( uint32_t * pul_Task_ਢੇਰ,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_ਸੰਖਿਆ ) PRIVILEGED_FUNCTION;

#ਜੇ_ਅੰਤ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    ਖਾਲੀ vRequestSystemCallExit( ਖਾਲੀ ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#ਜੇ_ਅੰਤ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param pulSystemCallStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     */
    ਖਾਲੀ vSystemCallExit( uint32_t * pul_System_Call_ਢੇਰ,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#ਜੇ_ਅੰਤ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ਜੇ ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Task_Privileged( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

#ਜੇ_ਅੰਤ /* configENABLE_MPU == 1 */

#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )

    /**
     * @brief Platform/Application-defined function that wakes up the secondary cores.
     *
     * @return pdTRUE if the secondary cores were successfully woken up.
     *         pdFALSE otherwise.
     */
    ਬਾਹਰੀ ਅਧਾਰ_Type_t configWAKE_SECONDARY_CORES( ਖਾਲੀ );

#ਜੇ_ਅੰਤ /* #if ( configNUMBER_OF_CORES > 1 ) */

/**
 * @brief Configures interrupt priorities.
 */
ਖਾਲੀ v_ਪੋਰਟ_Configure_ਰੁਕਾਵਟ_Priorities( ਖਾਲੀ ) PRIVILEGED_FUNCTION;
/*-----------------------------------------------------------*/

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief This variable is set to pdTRUE when the scheduler is started.
     */
    PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ ਅਧਾਰ_Type_t xSchedulerRunning = pdFALSE;

#ਜੇ_ਅੰਤ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/**
 * @brief Each task maintains its own interrupt status in the critical nesting
 * variable.
 */
#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
    PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ ਅਸਥਿਰ uint32_t ulCriticalNesting = 0UL;
#ਨਹੀਂਤਾਂ /* #if ( configNUMBER_OF_CORES == 1 ) */
    PRIVILEGED_ਅੰਕੜੇ ਅਸਥਿਰ uint32_t ulCriticalNestings[ config_ਸੰਖਿਆ_ਦਾ_CORES ] = { 0 };
    /* Flags to check if the secondary cores are ready. */
    PRIVILEGED_ਅੰਕੜੇ ਅਸਥਿਰ uint8_t ucSecondaryCoresReadyFlags[ config_ਸੰਖਿਆ_ਦਾ_CORES - 1 ] = { 0 };
    /* Flag to indicate that the primary core has completed its initialisation. */
    PRIVILEGED_ਅੰਕੜੇ ਅਸਥਿਰ uint8_t uc_Primary_Core_Init_ਪੂਰਾ_Flag = 0;
 #ਜੇ_ਅੰਤ /* #if ( configNUMBER_OF_CORES == 1 ) */

#ਜੇ ( configENABLE_TRUSTZONE == 1 )

    /**
     * @brief Saved as part of the task context to indicate which context the
     * task is using on the secure side.
     */
    PRIVILEGED_ਅੰਕੜੇ ਪੋਰਟ_DONT_DISCARD ਅਸਥਿਰ SecureContextHandle_t xSecureContext = ਪੋਰਟ_NO_SECURE_CONTEXT;
#ਜੇ_ਅੰਤ /* configENABLE_TRUSTZONE */

/**
 * @brief Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#ਜੇ ( ( configASSERT_DEFINED == 1 ) && ( ਪੋਰਟ_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) )

    ਸਥਿਰ uint8_t uc_Max_Sys_Call_ਤਰਜੀਹ = 0;
    ਸਥਿਰ uint32_t ulMaxPRIGROUPValue = 0;
    ਸਥਿਰ ਅਚਲ ਅਸਥਿਰ uint8_t * ਅਚਲ pc_ਰੁਕਾਵਟ_ਤਰਜੀਹ_Registers = ( ਅਚਲ ਅਸਥਿਰ uint8_t * ) ਪੋਰਟ_NVIC_IP_REGISTERS_ਵਿੱਥ_16;

#ਜੇ_ਅੰਤ /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */

#ਜੇ ( configUSE_TICKLESS_IDLE == 1 )

    /**
     * @brief The number of SysTick increments that make up one tick period.
     */
    PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ uint32_t ulTimerCountsForOneTick = 0;

    /**
     * @brief The maximum number of tick periods that can be suppressed is
     * limited by the 24 bit resolution of the SysTick timer.
     */
    PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ uint32_t x_ਵੱਧ_ਤੋਂ_ਵੱਧ_Possible_Suppressed_Ticks = 0;

    /**
     * @brief Compensate for the CPU cycles that pass while the SysTick is
     * stopped (low power functionality only).
     */
    PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ uint32_t ulStoppedTimerCompensation = 0;
#ਜੇ_ਅੰਤ /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) ਖਾਲੀ v_ਪੋਰਟ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ਸਮਾਂ )
    {
        uint32_t ul_Reload_ਮੁੱਲ, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_ਖੱਬਾ;
        TickType_t x_Modifiable_Idle_ਸਮਾਂ;

        /* Make sure the SysTick reload value does not overflow the counter. */
        ਜੇ( x_Expected_Idle_ਸਮਾਂ > x_ਵੱਧ_ਤੋਂ_ਵੱਧ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_ਸਮਾਂ = x_ਵੱਧ_ਤੋਂ_ਵੱਧ_Possible_Suppressed_Ticks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm ਅਸਥਿਰ ( "cpsid i" ::: "memory" );
        __asm ਅਸਥਿਰ ( "dsb" );
        __asm ਅਸਥਿਰ ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        ਜੇ( e_Task_Confirm_Sleep_ਬਹੁਲਕ_ਸਥਿਤੀ() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the cpsid instruction
             * above. */
            __asm ਅਸਥਿਰ ( "cpsie i" ::: "memory" );
        }
        ਨਹੀਂਤਾਂ
        {
            /* Stop the SysTick momentarily.  The time the SysTick is stopped for
             * is accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG = ( ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ_CONFIG | ਪੋਰਟ_NVIC_SYSTICK_INT_ਦੋਆਧਾਰੀ_ਅੰਕ );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_ਖੱਬਾ = ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG;

            ਜੇ( ul_Sys_Tick_Decrements_ਖੱਬਾ == 0 )
            {
                ul_Sys_Tick_Decrements_ਖੱਬਾ = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_ਮੁੱਲ = ul_Sys_Tick_Decrements_ਖੱਬਾ + ( ulTimerCountsForOneTick * ( x_Expected_Idle_ਸਮਾਂ - 1UL ) );

            ਜੇ( ( ਪੋਰਟ_NVIC_INT_CTRL_REG & ਪੋਰਟ_NVIC_PEND_SYSTICK_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ ) != 0 )
            {
                ਪੋਰਟ_NVIC_INT_CTRL_REG = ਪੋਰਟ_NVIC_PEND_SYSTICK_CLEAR_ਦੋਆਧਾਰੀ_ਅੰਕ;
                ul_Reload_ਮੁੱਲ -= ulTimerCountsForOneTick;
            }

            ਜੇ( ul_Reload_ਮੁੱਲ > ulStoppedTimerCompensation )
            {
                ul_Reload_ਮੁੱਲ -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG = ul_Reload_ਮੁੱਲ;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG = 0UL;

            /* Restart SysTick. */
            ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG |= ਪੋਰਟ_NVIC_SYSTICK_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            x_Modifiable_Idle_ਸਮਾਂ = x_Expected_Idle_ਸਮਾਂ;
            configPRE_SLEEP_PROCESSING( x_Modifiable_Idle_ਸਮਾਂ );

            ਜੇ( x_Modifiable_Idle_ਸਮਾਂ > 0 )
            {
                __asm ਅਸਥਿਰ ( "dsb" ::: "memory" );
                __asm ਅਸਥਿਰ ( "wfi" );
                __asm ਅਸਥਿਰ ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_ਸਮਾਂ );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the cpsid instruction above. */
            __asm ਅਸਥਿਰ ( "cpsie i" ::: "memory" );
            __asm ਅਸਥਿਰ ( "dsb" );
            __asm ਅਸਥਿਰ ( "isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm ਅਸਥਿਰ ( "cpsid i" ::: "memory" );
            __asm ਅਸਥਿਰ ( "dsb" );
            __asm ਅਸਥਿਰ ( "isb" );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG = ( ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ_CONFIG | ਪੋਰਟ_NVIC_SYSTICK_INT_ਦੋਆਧਾਰੀ_ਅੰਕ );

            /* Determine whether the SysTick has already counted to zero. */
            ਜੇ( ( ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG & ਪੋਰਟ_NVIC_SYSTICK_ਗਿਣਤੀ_FLAG_ਦੋਆਧਾਰੀ_ਅੰਕ ) != 0 )
            {
                uint32_t ul_Calculated_ਲੱਦੋ_ਮੁੱਲ;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_ਲੱਦੋ_ਮੁੱਲ = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_ਮੁੱਲ - ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                ਜੇ( ( ul_Calculated_ਲੱਦੋ_ਮੁੱਲ <= ulStoppedTimerCompensation ) || ( ul_Calculated_ਲੱਦੋ_ਮੁੱਲ > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_ਲੱਦੋ_ਮੁੱਲ = ( ulTimerCountsForOneTick - 1UL );
                }

                ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG = ul_Calculated_ਲੱਦੋ_ਮੁੱਲ;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = x_Expected_Idle_ਸਮਾਂ - 1UL;
            }
            ਨਹੀਂਤਾਂ
            {
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_ਖੱਬਾ = ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG;
                #ਜੇ ( ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ_CONFIG != ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    ਜੇ( ul_Sys_Tick_Decrements_ਖੱਬਾ == 0 )
                    {
                        ul_Sys_Tick_Decrements_ਖੱਬਾ = ul_Reload_ਮੁੱਲ;
                    }
                }
                #ਜੇ_ਅੰਤ /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_ਸਮਾਂ * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_ਖੱਬਾ;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG = 0UL;
            ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG = ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ | ਪੋਰਟ_NVIC_SYSTICK_INT_ਦੋਆਧਾਰੀ_ਅੰਕ | ਪੋਰਟ_NVIC_SYSTICK_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ;
            #ਜੇ ( ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ_CONFIG == ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ )
            {
                ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG = ulTimerCountsForOneTick - 1UL;
            }
            #ਨਹੀਂਤਾਂ
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG = ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ | ਪੋਰਟ_NVIC_SYSTICK_INT_ਦੋਆਧਾਰੀ_ਅੰਕ;

                ਜੇ( ( ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG & ਪੋਰਟ_NVIC_SYSTICK_ਗਿਣਤੀ_FLAG_ਦੋਆਧਾਰੀ_ਅੰਕ ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG = 0;
                }

                ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG = ulTimerCountsForOneTick - 1UL;
                ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG = ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ_CONFIG | ਪੋਰਟ_NVIC_SYSTICK_INT_ਦੋਆਧਾਰੀ_ਅੰਕ | ਪੋਰਟ_NVIC_SYSTICK_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ;
            }
            #ਜੇ_ਅੰਤ /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            v_Task_ਕਦਮ_Tick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __asm ਅਸਥਿਰ ( "cpsie i" ::: "memory" );
        }
    }

#ਜੇ_ਅੰਤ /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

__attribute__( ( weak ) ) ਖਾਲੀ v_ਪੋਰਟ_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
{
    /* Calculate the constants required to configure the tick interrupt. */
    #ਜੇ ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_ਦਰ_HZ );
        x_ਵੱਧ_ਤੋਂ_ਵੱਧ_Possible_Suppressed_Ticks = ਪੋਰਟ_MAX_24_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੰਖਿਆ / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = ਪੋਰਟ_MISSED_COUNTS_ਗੁਣਕ / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #ਜੇ_ਅੰਤ /* configUSE_TICKLESS_IDLE */

    /* Stop and reset SysTick.
     *
     * QEMU versions older than 7.0.0 contain a bug which causes an error if we
     * enable SysTick without first selecting a valid clock source. We trigger
     * the bug if we change clock sources from a clock with a zero clock period
     * to one with a nonzero clock period and enable Systick at the same time.
     * So we configure the CLKSOURCE bit here, prior to setting the ENABLE bit.
     * This workaround avoids the bug in QEMU versions older than 7.0.0. */
    ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG = ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ_CONFIG;
    ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_ਦਰ_HZ ) - 1UL;
    ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG = ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ_CONFIG | ਪੋਰਟ_NVIC_SYSTICK_INT_ਦੋਆਧਾਰੀ_ਅੰਕ | ਪੋਰਟ_NVIC_SYSTICK_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prvTaskExitError( ਖਾਲੀ )
{
    ਅਸਥਿਰ uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
        configASSERT( ulCriticalNesting == ~0UL );
    #ਨਹੀਂਤਾਂ /* #if ( configNUMBER_OF_CORES == 1 ) */
        configASSERT( ulCriticalNestings[ ਪੋਰਟ_GET_CORE_ID() ] == ~0UL );
    #ਜੇ_ਅੰਤ /* #if ( configNUMBER_OF_CORES == 1 ) */
    ਪੋਰਟ_DISABLE_INTERRUPTS();

    ਜਦੋਂ( ulDummy == 0 )
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

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ਸਥਿਰ uint32_t prvGetRegionAccessPermissions( uint32_t ulRBARValue ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ulAccessPermissions = 0;

        ਜੇ( ( ulRBARValue & ਪੋਰਟ_MPU_RBAR_ACCESS_PERMISSIONS_ਨਕਾਬ ) == ਪੋਰਟ_MPU_REGION_READ_ONLY )
        {
            ulAccessPermissions = tskMPU_READ_PERMISSION;
        }

        ਜੇ( ( ulRBARValue & ਪੋਰਟ_MPU_RBAR_ACCESS_PERMISSIONS_ਨਕਾਬ ) == ਪੋਰਟ_MPU_REGION_READ_WRITE )
        {
            ulAccessPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
        }

        ਵਾਪਸ ulAccessPermissions;
    }

#ਜੇ_ਅੰਤ /* configENABLE_MPU == 1 && configUSE_MPU_WRAPPERS_V1 == 0 */
/*-----------------------------------------------------------*/

#ਜੇ ( configENABLE_MPU == 1 )

    ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_MPU( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
    {
        #ਜੇ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ਬਾਹਰੀ uint32_t * __privileged_functions_start__;
            ਬਾਹਰੀ uint32_t * __privileged_functions_end__;
            ਬਾਹਰੀ uint32_t * __syscalls_flash_start__;
            ਬਾਹਰੀ uint32_t * __syscalls_flash_end__;
            ਬਾਹਰੀ uint32_t * __unprivileged_flash_start__;
            ਬਾਹਰੀ uint32_t * __unprivileged_flash_end__;
            ਬਾਹਰੀ uint32_t * __privileged_sram_start__;
            ਬਾਹਰੀ uint32_t * __privileged_sram_end__;
        #ਨਹੀਂਤਾਂ /* if defined( __ARMCC_VERSION ) */
            /* Declaration when these variable are exported from linker scripts. */
            ਬਾਹਰੀ uint32_t __privileged_functions_start__[];
            ਬਾਹਰੀ uint32_t __privileged_functions_end__[];
            ਬਾਹਰੀ uint32_t __syscalls_flash_start__[];
            ਬਾਹਰੀ uint32_t __syscalls_flash_end__[];
            ਬਾਹਰੀ uint32_t __unprivileged_flash_start__[];
            ਬਾਹਰੀ uint32_t __unprivileged_flash_end__[];
            ਬਾਹਰੀ uint32_t __privileged_sram_start__[];
            ਬਾਹਰੀ uint32_t __privileged_sram_end__[];
        #ਜੇ_ਅੰਤ /* defined( __ARMCC_VERSION ) */

        /* The only permitted number of regions are 8 or 16. */
        configASSERT( ( config_ਕੁੱਲ_MPU_REGIONS == 8 ) || ( config_ਕੁੱਲ_MPU_REGIONS == 16 ) );

        /* MAIR0 - Index 0. */
        ਪੋਰਟ_MPU_MAIR0_REG |= ( ( ਪੋਰਟ_MPU_ਸਾਧਾਰਨ_ਸਮ੍ਰਿਤੀ_BUFFERABLE_CACHEABLE << ਪੋਰਟ_MPU_MAIR_ATTR0_POS ) & ਪੋਰਟ_MPU_MAIR_ATTR0_ਨਕਾਬ );
        /* MAIR0 - Index 1. */
        ਪੋਰਟ_MPU_MAIR0_REG |= ( ( ਪੋਰਟ_MPU_DEVICE_ਸਮ੍ਰਿਤੀ_n_Gn_RE << ਪੋਰਟ_MPU_MAIR_ATTR1_POS ) & ਪੋਰਟ_MPU_MAIR_ATTR1_ਨਕਾਬ );

        /* Setup privileged flash as Read Only so that privileged tasks can
         * read it but not modify. */
        ਪੋਰਟ_MPU_RNR_REG = ਪੋਰਟ_PRIVILEGED_FLASH_REGION;
        ਪੋਰਟ_MPU_RBAR_REG = ( ( ( uint32_t ) __privileged_functions_start__ ) & ਪੋਰਟ_MPU_RBAR_ਪਤਾ_ਨਕਾਬ ) |
                           ( ਪੋਰਟ_MPU_REGION_NON_SHAREABLE ) |
                           ( ਪੋਰਟ_MPU_REGION_PRIVILEGED_READ_ONLY );
        ਪੋਰਟ_MPU_RLAR_REG = ( ( ( uint32_t ) __privileged_functions_end__ ) & ਪੋਰਟ_MPU_RLAR_ਪਤਾ_ਨਕਾਬ ) |
                           ( ਪੋਰਟ_MPU_RLAR_ATTR_INDEX0 ) |
                           ( ਪੋਰਟ_MPU_RLAR_REGION_ENABLE );

        /* Setup unprivileged flash as Read Only by both privileged and
         * unprivileged tasks. All tasks can read it but no-one can modify. */
        ਪੋਰਟ_MPU_RNR_REG = ਪੋਰਟ_UNPRIVILEGED_FLASH_REGION;
        ਪੋਰਟ_MPU_RBAR_REG = ( ( ( uint32_t ) __unprivileged_flash_start__ ) & ਪੋਰਟ_MPU_RBAR_ਪਤਾ_ਨਕਾਬ ) |
                           ( ਪੋਰਟ_MPU_REGION_NON_SHAREABLE ) |
                           ( ਪੋਰਟ_MPU_REGION_READ_ONLY );
        ਪੋਰਟ_MPU_RLAR_REG = ( ( ( uint32_t ) __unprivileged_flash_end__ ) & ਪੋਰਟ_MPU_RLAR_ਪਤਾ_ਨਕਾਬ ) |
                           ( ਪੋਰਟ_MPU_RLAR_ATTR_INDEX0 ) |
                           ( ਪੋਰਟ_MPU_RLAR_REGION_ENABLE );

        /* Setup unprivileged syscalls flash as Read Only by both privileged
         * and unprivileged tasks. All tasks can read it but no-one can modify. */
        ਪੋਰਟ_MPU_RNR_REG = ਪੋਰਟ_UNPRIVILEGED_SYSCALLS_REGION;
        ਪੋਰਟ_MPU_RBAR_REG = ( ( ( uint32_t ) __syscalls_flash_start__ ) & ਪੋਰਟ_MPU_RBAR_ਪਤਾ_ਨਕਾਬ ) |
                           ( ਪੋਰਟ_MPU_REGION_NON_SHAREABLE ) |
                           ( ਪੋਰਟ_MPU_REGION_READ_ONLY );
        ਪੋਰਟ_MPU_RLAR_REG = ( ( ( uint32_t ) __syscalls_flash_end__ ) & ਪੋਰਟ_MPU_RLAR_ਪਤਾ_ਨਕਾਬ ) |
                           ( ਪੋਰਟ_MPU_RLAR_ATTR_INDEX0 ) |
                           ( ਪੋਰਟ_MPU_RLAR_REGION_ENABLE );

        /* Setup RAM containing kernel data for privileged access only. */
        ਪੋਰਟ_MPU_RNR_REG = ਪੋਰਟ_PRIVILEGED_RAM_REGION;
        ਪੋਰਟ_MPU_RBAR_REG = ( ( ( uint32_t ) __privileged_sram_start__ ) & ਪੋਰਟ_MPU_RBAR_ਪਤਾ_ਨਕਾਬ ) |
                           ( ਪੋਰਟ_MPU_REGION_NON_SHAREABLE ) |
                           ( ਪੋਰਟ_MPU_REGION_PRIVILEGED_READ_WRITE ) |
                           ( ਪੋਰਟ_MPU_REGION_EXECUTE_NEVER );
        ਪੋਰਟ_MPU_RLAR_REG = ( ( ( uint32_t ) __privileged_sram_end__ ) & ਪੋਰਟ_MPU_RLAR_ਪਤਾ_ਨਕਾਬ ) |
                           ( ਪੋਰਟ_MPU_RLAR_ATTR_INDEX0 ) |
                           ( ਪੋਰਟ_MPU_RLAR_REGION_ENABLE );

        /* Enable mem fault. */
        ਪੋਰਟ_SCB_SYS_HANDLER_CTRL_STATE_REG |= ਪੋਰਟ_SCB_MEM_FAULT_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ;

        /* Enable MPU with privileged background access i.e. unmapped
         * regions have privileged access. */
        ਪੋਰਟ_MPU_CTRL_REG |= ( ਪੋਰਟ_MPU_PRIV_BACKGROUND_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ | ਪੋਰਟ_MPU_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ );
    }

#ਜੇ_ਅੰਤ /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#ਜੇ ( configENABLE_FPU == 1 )

    ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_FPU( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
    {
        #ਜੇ ( configENABLE_TRUSTZONE == 1 )
        {
            /* Enable non-secure access to the FPU. */
            SecureInit_EnableNSFPUAccess();
        }
        #ਜੇ_ਅੰਤ /* configENABLE_TRUSTZONE */

        /* CP10 = 11 ==> Full access to FPU i.e. both privileged and
         * unprivileged code should be able to access FPU. CP11 should be
         * programmed to the same value as CP10. */
        *( ਪੋਰਟ_CPACR ) |= ( ( ਪੋਰਟ_CPACR_CP10_ਮੁੱਲ << ਪੋਰਟ_CPACR_CP10_POS ) |
                            ( ਪੋਰਟ_CPACR_CP11_ਮੁੱਲ << ਪੋਰਟ_CPACR_CP11_POS )
                            );

        /* ASPEN = 1 ==> Hardware should automatically preserve floating point
         * context on exception entry and restore on exception return.
         * LSPEN = 1 ==> Enable lazy context save of FP state. */
        *( ਪੋਰਟ_FPCCR ) |= ( ਪੋਰਟ_FPCCR_ASPEN_ਨਕਾਬ | ਪੋਰਟ_FPCCR_LSPEN_ਨਕਾਬ );
    }

#ਜੇ_ਅੰਤ /* configENABLE_FPU */
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
{
    /* Set a PendSV to request a context switch. */
    ਪੋਰਟ_NVIC_INT_CTRL_REG = ਪੋਰਟ_NVIC_PENDSVSET_ਦੋਆਧਾਰੀ_ਅੰਕ;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm ਅਸਥਿਰ ( "dsb" ::: "memory" );
    __asm ਅਸਥਿਰ ( "isb" );
}
/*-----------------------------------------------------------*/

#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
    ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
    {
        ਪੋਰਟ_DISABLE_INTERRUPTS();
        ulCriticalNesting++;
        /* Barriers are normally not required but do ensure the code is
        * completely within the specified behaviour for the architecture. */
        __asm ਅਸਥਿਰ ( "dsb" ::: "memory" );
        __asm ਅਸਥਿਰ ( "isb" );
    }
    /*-----------------------------------------------------------*/

    ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( ulCriticalNesting );
        ulCriticalNesting--;

        ਜੇ( ulCriticalNesting == 0 )
        {
            ਪੋਰਟ_ENABLE_INTERRUPTS();
        }
    }
#ਜੇ_ਅੰਤ /* configNUMBER_OF_CORES == 1 */
/*-----------------------------------------------------------*/

ਖਾਲੀ SysTick_Handler( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
{
    uint32_t ul_ਪਿਛਲਾ_ਨਕਾਬ;

    ul_ਪਿਛਲਾ_ਨਕਾਬ = ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR();
    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )
        UBaseType_t ux_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ = ਪੋਰਟ_ENTER_CRITICAL_FROM_ISR();
    #ਜੇ_ਅੰਤ /* if ( configNUMBER_OF_CORES > 1 ) */

    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        ਜੇ( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_ਮੰਜ਼ਿਲ_SCHEDULER();
            /* Pend a context switch. */
            ਪੋਰਟ_NVIC_INT_CTRL_REG = ਪੋਰਟ_NVIC_PENDSVSET_ਦੋਆਧਾਰੀ_ਅੰਕ;
        }
        ਨਹੀਂਤਾਂ
        {
            traceISR_EXIT();
        }
    }
    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )
        ਪੋਰਟ_EXIT_CRITICAL_FROM_ISR( ux_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ );
    #ਜੇ_ਅੰਤ /* if ( configNUMBER_OF_CORES > 1 ) */

    ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( ul_ਪਿਛਲਾ_ਨਕਾਬ );
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_SVCHandler_C( uint32_t * pul_Caller_ਢੇਰ_ਪਤਾ ) /* PRIVILEGED_FUNCTION portDONT_DISCARD */
{
    #ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )
        #ਜੇ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ਬਾਹਰੀ uint32_t * __syscalls_flash_start__;
            ਬਾਹਰੀ uint32_t * __syscalls_flash_end__;
        #ਨਹੀਂਤਾਂ
            /* Declaration when these variable are exported from linker scripts. */
            ਬਾਹਰੀ uint32_t __syscalls_flash_start__[];
            ਬਾਹਰੀ uint32_t __syscalls_flash_end__[];
        #ਜੇ_ਅੰਤ /* defined( __ARMCC_VERSION ) */
    #ਜੇ_ਅੰਤ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #ਜੇ ( configENABLE_MPU == 1 )
        #ਜੇ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ਬਾਹਰੀ uint32_t * __privileged_functions_start__;
            ਬਾਹਰੀ uint32_t * __privileged_functions_end__;
        #ਨਹੀਂਤਾਂ
            /* Declaration when these variable are exported from linker scripts. */
            ਬਾਹਰੀ uint32_t __privileged_functions_start__[];
            ਬਾਹਰੀ uint32_t __privileged_functions_end__[];
        #ਜੇ_ਅੰਤ /* defined( __ARMCC_VERSION ) */
    #ਜੇ_ਅੰਤ /* configENABLE_MPU == 1 */

    uint32_t ulPC;

    #ਜੇ ( configENABLE_TRUSTZONE == 1 )
        uint32_t ulR0, ulR1;
        ਬਾਹਰੀ TaskHandle_t pxCurrentTCB;
        #ਜੇ ( configENABLE_MPU == 1 )
            uint32_t ulControl, ulIsTaskPrivileged;
        #ਜੇ_ਅੰਤ /* configENABLE_MPU */
    #ਜੇ_ਅੰਤ /* configENABLE_TRUSTZONE */
    uint8_t ucSVCNumber;

    /* Register are stored on the stack in the following order - R0, R1, R2, R3,
     * R12, LR, PC, xPSR. */
    ulPC = pul_Caller_ਢੇਰ_ਪਤਾ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    ਚੋਣ( ucSVCNumber )
    {
    #ਜੇ ( configENABLE_TRUSTZONE == 1 )
        ਹਾਲਤ ਪੋਰਟ_SVC_ALLOCATE_SECURE_CONTEXT:

            /* R0 contains the stack size passed as parameter to the
             * vPortAllocateSecureContext function. */
            ulR0 = pul_Caller_ਢੇਰ_ਪਤਾ[ 0 ];

            #ਜੇ ( configENABLE_MPU == 1 )
            {
                /* Read the CONTROL register value. */
                __asm ਅਸਥਿਰ ( "mrs %0, control"  : "=r" ( ulControl ) );

                /* The task that raised the SVC is privileged if Bit[0]
                 * in the CONTROL register is 0. */
                ulIsTaskPrivileged = ( ( ulControl & ਪੋਰਟ_CONTROL_PRIVILEGED_ਨਕਾਬ ) == 0 );

                /* Allocate and load a context for the secure task. */
                xSecureContext = SecureContext_AllocateContext( ulR0, ulIsTaskPrivileged, pxCurrentTCB );
            }
            #ਨਹੀਂਤਾਂ /* if ( configENABLE_MPU == 1 ) */
            {
                /* Allocate and load a context for the secure task. */
                xSecureContext = SecureContext_AllocateContext( ulR0, pxCurrentTCB );
            }
            #ਜੇ_ਅੰਤ /* configENABLE_MPU */

            configASSERT( xSecureContext != securecontextINVALID_CONTEXT_ID );
            Secure_Context_ਲੱਦੋ_Context( xSecureContext, pxCurrentTCB );
            ਰੋਕੋ;

        ਹਾਲਤ ਪੋਰਟ_SVC_FREE_SECURE_CONTEXT:
            #ਜੇ ( configENABLE_MPU == 1 )
            ਜੇ( ( ulPC >= ( uint32_t ) __privileged_functions_start__ ) &&
                ( ulPC <= ( uint32_t ) __privileged_functions_end__ ) )
            {
            #ਜੇ_ਅੰਤ /* configENABLE_MPU */
                /* R0 contains TCB being freed and R1 contains the secure
                 * context handle to be freed. */
                ulR0 = pul_Caller_ਢੇਰ_ਪਤਾ[ 0 ];
                ulR1 = pul_Caller_ਢੇਰ_ਪਤਾ[ 1 ];

                /* Free the secure context. */
                SecureContext_FreeContext( ( SecureContextHandle_t ) ulR1, ( ਖਾਲੀ * ) ulR0 );
            #ਜੇ ( configENABLE_MPU == 1 )
            }
            #ਜੇ_ਅੰਤ /* configENABLE_MPU */
            ਰੋਕੋ;
    #ਜੇ_ਅੰਤ /* configENABLE_TRUSTZONE */

        ਹਾਲਤ ਪੋਰਟ_SVC_ਸ਼ੁਰੂ_SCHEDULER:
            #ਜੇ ( configENABLE_MPU == 1 )
            ਜੇ( ( ulPC >= ( uint32_t ) __privileged_functions_start__ ) &&
                ( ulPC <= ( uint32_t ) __privileged_functions_end__ ) )
            {
            #ਜੇ_ਅੰਤ /* configENABLE_MPU */
                #ਜੇ ( configENABLE_TRUSTZONE == 1 )
                {
                    /* De-prioritize the non-secure exceptions so that the
                     * non-secure pendSV runs at the lowest priority. */
                    SecureInit_DePrioritizeNSExceptions();

                    /* Initialize the secure context management system. */
                    SecureContext_Init();
                }
                #ਜੇ_ਅੰਤ /* configENABLE_TRUSTZONE */

                #ਜੇ ( configENABLE_FPU == 1 )
                {
                    /* Setup the Floating Point Unit (FPU). */
                    prv_ਤਿਆਰੀ_FPU();
                }
                #ਜੇ_ਅੰਤ /* configENABLE_FPU */

                /* Setup the context of the first task so that the first task starts
                 * executing. */
                v_Restore_Context_ਦਾ_ਪਹਿਲਾ_Task();
            #ਜੇ ( configENABLE_MPU == 1 )
            }
            #ਜੇ_ਅੰਤ /* configENABLE_MPU */
            ਰੋਕੋ;

    #ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )
        ਹਾਲਤ ਪੋਰਟ_SVC_RAISE_PRIVILEGE:

            /* Only raise the privilege, if the svc was raised from any of
             * the system calls. */
            ਜੇ( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
            {
                vRaisePrivilege();
            }
            ਰੋਕੋ;
    #ਜੇ_ਅੰਤ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #ਜੇ ( configENABLE_MPU == 1 )
        ਹਾਲਤ ਪੋਰਟ_SVC_YIELD:
            v_ਪੋਰਟ_Yield();
            ਰੋਕੋ;
    #ਜੇ_ਅੰਤ /* configENABLE_MPU == 1 */

        ਮੂਲ:
            /* Incorrect SVC call. */
            configASSERT( pdFALSE );
    }
}
/*-----------------------------------------------------------*/

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ਖਾਲੀ vSystemCallEnter( uint32_t * pul_Task_ਢੇਰ,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_ਸੰਖਿਆ ) /* PRIVILEGED_FUNCTION */
    {
        ਬਾਹਰੀ TaskHandle_t pxCurrentTCB;
        ਬਾਹਰੀ UBaseType_t uxSystemCallImplementations[ ਅੰਕ_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_ਢੇਰ;
        uint32_t ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ, ulSystemCallLocation, i;

        #ਜੇ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ਬਾਹਰੀ uint32_t * __syscalls_flash_start__;
            ਬਾਹਰੀ uint32_t * __syscalls_flash_end__;
        #ਨਹੀਂਤਾਂ
            /* Declaration when these variable are exported from linker scripts. */
            ਬਾਹਰੀ uint32_t __syscalls_flash_start__[];
            ਬਾਹਰੀ uint32_t __syscalls_flash_end__[];
        #ਜੇ_ਅੰਤ /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PC ];
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
        ਜੇ( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_ਢੇਰ_Info.pul_Task_ਢੇਰ == ਨਿਰਾ ) &&
            ( uxSystemCallImplementations[ uc_System_Call_ਸੰਖਿਆ ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_ਢੇਰ = pxMpuSettings->x_System_Call_ਢੇਰ_Info.pul_System_Call_ਢੇਰ;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            #ਜੇ ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )
            {
                ਜੇ( ( ulLR & ਪੋਰਟ_EXC_RETURN_ਢੇਰ_ਚੌਖਟਾ_TYPE_ਨਕਾਬ ) == 0UL )
                {
                    /* Extended frame i.e. FPU in use. */
                    ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ = 26;
                    __asm ਅਸਥਿਰ (
                        " vpush {s0}         \n" /* Trigger lazy stacking. */
                        " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                        ::: "memory"
                        );
                }
                ਨਹੀਂਤਾਂ
                {
                    /* Standard frame i.e. FPU not in use. */
                    ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ = 8;
                }
            }
            #ਨਹੀਂਤਾਂ /* if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */
            {
                ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ = 8;
            }
            #ਜੇ_ਅੰਤ /* configENABLE_FPU || configENABLE_MVE */

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_ਢੇਰ = pul_System_Call_ਢੇਰ - ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ;

            /* Copy the stack frame. */
            ਲਈ( i = 0; i < ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ; i++ )
            {
                pul_System_Call_ਢੇਰ[ i ] = pul_Task_ਢੇਰ[ i ];
            }

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_ਢੇਰ_Info.ul_Link_ਰਜਿਸਟਰ_At_System_Call_ਇੰਦਰਾਜ = pul_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_LR ];

            /* Store the value of the PSPLIM register before the SVC was raised.
             * We need to restore it when we exit from the system call. */
            #ਜੇ ( ਪੋਰਟ_USE_PSPLIM_ਰਜਿਸਟਰ == 1 )
            {
                __asm ਅਸਥਿਰ ( "mrs %0, psplim" : "=r" ( pxMpuSettings->x_System_Call_ਢੇਰ_Info.ul_ਢੇਰ_ਹੱਦਬੰਦੀ_ਰਜਿਸਟਰ_At_System_Call_ਇੰਦਰਾਜ ) );
            }
            #ਜੇ_ਅੰਤ

            /* Use the pulSystemCallStack in thread mode. */
            __asm ਅਸਥਿਰ ( "msr psp, %0" : : "r" ( pul_System_Call_ਢੇਰ ) );
            #ਜੇ ( ਪੋਰਟ_USE_PSPLIM_ਰਜਿਸਟਰ == 1 )
            {
                __asm ਅਸਥਿਰ ( "msr psplim, %0" : : "r" ( pxMpuSettings->x_System_Call_ਢੇਰ_Info.pul_System_Call_ਢੇਰ_ਹੱਦਬੰਦੀ ) );
            }
            #ਜੇ_ਅੰਤ

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PC ] = uxSystemCallImplementations[ uc_System_Call_ਸੰਖਿਆ ];

            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_ਢੇਰ_Info.pul_Task_ਢੇਰ = pul_Task_ਢੇਰ + ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            ਜੇ( ( pul_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PSR ] & ਪੋਰਟ_PSR_ਢੇਰ_PADDING_ਨਕਾਬ ) == ਪੋਰਟ_PSR_ਢੇਰ_PADDING_ਨਕਾਬ )
            {
                pxMpuSettings->ulTaskFlags |= ਪੋਰਟ_ਢੇਰ_ਚੌਖਟਾ_HAS_PADDING_FLAG;
            }
            ਨਹੀਂਤਾਂ
            {
                pxMpuSettings->ulTaskFlags &= ( ~ਪੋਰਟ_ਢੇਰ_ਚੌਖਟਾ_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PSR ] &= ( ~ਪੋਰਟ_PSR_ਢੇਰ_PADDING_ਨਕਾਬ );

            /* Raise the privilege for the duration of the system call. */
            __asm ਅਸਥਿਰ (
                " mrs r0, control     \n" /* Obtain current control value. */
                " movs r1, #1         \n" /* r1 = 1. */
                " bics r0, r1         \n" /* Clear nPRIV bit. */
                " msr control, r0     \n" /* Write back new control value. */
                ::: "r0", "r1", "memory"
                );
        }
    }

#ਜੇ_ਅੰਤ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ਖਾਲੀ vRequestSystemCallExit( ਖਾਲੀ ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm ਅਸਥਿਰ ( "svc %0 \n" ::"i" ( ਪੋਰਟ_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#ਜੇ_ਅੰਤ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ਖਾਲੀ vSystemCallExit( uint32_t * pul_System_Call_ਢੇਰ,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        ਬਾਹਰੀ TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_ਢੇਰ;
        uint32_t ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ, ulSystemCallLocation, i;

        #ਜੇ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ਬਾਹਰੀ uint32_t * __privileged_functions_start__;
            ਬਾਹਰੀ uint32_t * __privileged_functions_end__;
        #ਨਹੀਂਤਾਂ
            /* Declaration when these variable are exported from linker scripts. */
            ਬਾਹਰੀ uint32_t __privileged_functions_start__[];
            ਬਾਹਰੀ uint32_t __privileged_functions_end__[];
        #ਜੇ_ਅੰਤ /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PC ];
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
        ਜੇ( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_ਢੇਰ_Info.pul_Task_ਢੇਰ != ਨਿਰਾ ) )
        {
            pul_Task_ਢੇਰ = pxMpuSettings->x_System_Call_ਢੇਰ_Info.pul_Task_ਢੇਰ;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            #ਜੇ ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )
            {
                ਜੇ( ( ulLR & ਪੋਰਟ_EXC_RETURN_ਢੇਰ_ਚੌਖਟਾ_TYPE_ਨਕਾਬ ) == 0UL )
                {
                    /* Extended frame i.e. FPU in use. */
                    ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ = 26;
                    __asm ਅਸਥਿਰ (
                        " vpush {s0}         \n" /* Trigger lazy stacking. */
                        " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                        ::: "memory"
                        );
                }
                ਨਹੀਂਤਾਂ
                {
                    /* Standard frame i.e. FPU not in use. */
                    ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ = 8;
                }
            }
            #ਨਹੀਂਤਾਂ /* if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */
            {
                ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ = 8;
            }
            #ਜੇ_ਅੰਤ /* configENABLE_FPU || configENABLE_MVE */

            /* Make space on the task stack for the stack frame. */
            pul_Task_ਢੇਰ = pul_Task_ਢੇਰ - ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ;

            /* Copy the stack frame. */
            ਲਈ( i = 0; i < ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ; i++ )
            {
                pul_Task_ਢੇਰ[ i ] = pul_System_Call_ਢੇਰ[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm ਅਸਥਿਰ ( "msr psp, %0" : : "r" ( pul_Task_ਢੇਰ ) );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PC ] = pxMpuSettings->x_System_Call_ਢੇਰ_Info.ul_Link_ਰਜਿਸਟਰ_At_System_Call_ਇੰਦਰਾਜ;
            /* Ensure that LR has a valid value.*/
            pul_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_LR ] = pxMpuSettings->x_System_Call_ਢੇਰ_Info.ul_Link_ਰਜਿਸਟਰ_At_System_Call_ਇੰਦਰਾਜ;

            /* Restore the PSPLIM register to what it was at the time of
             * system call entry. */
            #ਜੇ ( ਪੋਰਟ_USE_PSPLIM_ਰਜਿਸਟਰ == 1 )
            {
                __asm ਅਸਥਿਰ ( "msr psplim, %0" : : "r" ( pxMpuSettings->x_System_Call_ਢੇਰ_Info.ul_ਢੇਰ_ਹੱਦਬੰਦੀ_ਰਜਿਸਟਰ_At_System_Call_ਇੰਦਰਾਜ ) );
            }
            #ਜੇ_ਅੰਤ

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            ਜੇ( ( pxMpuSettings->ulTaskFlags & ਪੋਰਟ_ਢੇਰ_ਚੌਖਟਾ_HAS_PADDING_FLAG ) == ਪੋਰਟ_ਢੇਰ_ਚੌਖਟਾ_HAS_PADDING_FLAG )
            {
                pul_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PSR ] |= ਪੋਰਟ_PSR_ਢੇਰ_PADDING_ਨਕਾਬ;
            }
            ਨਹੀਂਤਾਂ
            {
                pul_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PSR ] &= ( ~ਪੋਰਟ_PSR_ਢੇਰ_PADDING_ਨਕਾਬ );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_ਢੇਰ_Info.pul_Task_ਢੇਰ = ਨਿਰਾ;

            /* Drop the privilege before returning to the thread mode. */
            __asm ਅਸਥਿਰ (
                " mrs r0, control     \n" /* Obtain current control value. */
                " movs r1, #1         \n" /* r1 = 1. */
                " orrs r0, r1         \n" /* Set nPRIV bit. */
                " msr control, r0     \n" /* Write back new control value. */
                ::: "r0", "r1", "memory"
                );
        }
    }

#ਜੇ_ਅੰਤ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configENABLE_MPU == 1 )

    ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Task_Privileged( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
    {
        ਅਧਾਰ_Type_t xTaskIsPrivileged = pdFALSE;
        ਅਚਲ xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ਨਿਰਾ ); /* Calling task's MPU settings. */

        ਜੇ( ( xTaskMpuSettings->ulTaskFlags & ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG ) == ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        ਵਾਪਸ xTaskIsPrivileged;
    }

#ਜੇ_ਅੰਤ /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

#ਜੇ ( configENABLE_MPU == 1 )

    ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                         ਢੇਰ_Type_t * px_ਸਿਰਾ_ਦਾ_ਢੇਰ,
                                         TaskFunction_t px_ਕੋਡ,
                                         ਖਾਲੀ * pvParameters,
                                         ਅਧਾਰ_Type_t x_ਲੜੀਵਾਰ_Privileged,
                                         xMPU_SETTINGS * xMPUSettings ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_ਸੂਚਕਾਂਕ = 0;
        uint32_t ulControl = 0x0;

        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = 0x04040404; /* r4. */
        ul_ਸੂਚਕਾਂਕ++;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = 0x05050505; /* r5. */
        ul_ਸੂਚਕਾਂਕ++;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = 0x06060606; /* r6. */
        ul_ਸੂਚਕਾਂਕ++;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = 0x07070707; /* r7. */
        ul_ਸੂਚਕਾਂਕ++;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = 0x08080808; /* r8. */
        ul_ਸੂਚਕਾਂਕ++;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = 0x09090909; /* r9. */
        ul_ਸੂਚਕਾਂਕ++;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = 0x10101010; /* r10. */
        ul_ਸੂਚਕਾਂਕ++;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = 0x11111111; /* r11. */
        ul_ਸੂਚਕਾਂਕ++;

        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( uint32_t ) pvParameters; /* r0. */
        ul_ਸੂਚਕਾਂਕ++;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = 0x01010101; /* r1. */
        ul_ਸੂਚਕਾਂਕ++;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = 0x02020202; /* r2. */
        ul_ਸੂਚਕਾਂਕ++;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = 0x03030303; /* r3. */
        ul_ਸੂਚਕਾਂਕ++;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = 0x12121212; /* r12. */
        ul_ਸੂਚਕਾਂਕ++;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( uint32_t ) ਪੋਰਟ_TASK_RETURN_ਪਤਾ; /* LR. */
        ul_ਸੂਚਕਾਂਕ++;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( uint32_t ) px_ਕੋਡ; /* PC. */
        ul_ਸੂਚਕਾਂਕ++;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ਪੋਰਟ_INITIAL_XPSR; /* xPSR. */
        ul_ਸੂਚਕਾਂਕ++;

        #ਜੇ ( configENABLE_TRUSTZONE == 1 )
        {
            xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ਪੋਰਟ_NO_SECURE_CONTEXT; /* xSecureContext. */
            ul_ਸੂਚਕਾਂਕ++;
        }
        #ਜੇ_ਅੰਤ /* configENABLE_TRUSTZONE */
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( uint32_t ) ( px_ਸਿਖਰ_ਦਾ_ਢੇਰ - 8 ); /* PSP with the hardware saved stack. */
        ul_ਸੂਚਕਾਂਕ++;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( uint32_t ) px_ਸਿਰਾ_ਦਾ_ਢੇਰ; /* PSPLIM. */
        ul_ਸੂਚਕਾਂਕ++;

        #ਜੇ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
        {
            /* Check PACBTI security feature configuration before pushing the
             * CONTROL register's value on task's TCB. */
            #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
                ulControl = prvConfigurePACBTI( pdFALSE );
            #ਨਹੀਂਤਾਂ /* configNUMBER_OF_CORES > 1 */
                ulControl = vConfigurePACBTI( pdFALSE );
            #ਜੇ_ਅੰਤ /* configNUMBER_OF_CORES */
        }
        #ਜੇ_ਅੰਤ /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

        ਜੇ( x_ਲੜੀਵਾਰ_Privileged == pdTRUE )
        {
            xMPUSettings->ulTaskFlags |= ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG;
            xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ulControl | ( uint32_t ) ਪੋਰਟ_INITIAL_CONTROL_PRIVILEGED ); /* CONTROL. */
            ul_ਸੂਚਕਾਂਕ++;
        }
        ਨਹੀਂਤਾਂ
        {
            xMPUSettings->ulTaskFlags &= ( ~ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG );
            xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ulControl | ( uint32_t ) ਪੋਰਟ_INITIAL_CONTROL_UNPRIVILEGED ); /* CONTROL. */
            ul_ਸੂਚਕਾਂਕ++;
        }

        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ਪੋਰਟ_INITIAL_EXC_RETURN; /* LR (EXC_RETURN). */
        ul_ਸੂਚਕਾਂਕ++;

        #ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 0 )
        {
            /* Ensure that the system call stack is double word aligned. */
            xMPUSettings->x_System_Call_ਢੇਰ_Info.pul_System_Call_ਢੇਰ = &( xMPUSettings->x_System_Call_ਢੇਰ_Info.ul_System_Call_ਢੇਰ_ਬਫਰ[ config_SYSTEM_CALL_ਢੇਰ_ਮਾਪ - 1 ] );
            xMPUSettings->x_System_Call_ਢੇਰ_Info.pul_System_Call_ਢੇਰ = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_ਢੇਰ_Info.pul_System_Call_ਢੇਰ ) &
                                                                                     ( uint32_t ) ( ~( ਪੋਰਟ_BYTE_ALIGNMENT_ਨਕਾਬ ) ) );

            xMPUSettings->x_System_Call_ਢੇਰ_Info.pul_System_Call_ਢੇਰ_ਹੱਦਬੰਦੀ = &( xMPUSettings->x_System_Call_ਢੇਰ_Info.ul_System_Call_ਢੇਰ_ਬਫਰ[ 0 ] );
            xMPUSettings->x_System_Call_ਢੇਰ_Info.pul_System_Call_ਢੇਰ_ਹੱਦਬੰਦੀ = ( uint32_t * ) ( ( ( uint32_t ) ( xMPUSettings->x_System_Call_ਢੇਰ_Info.pul_System_Call_ਢੇਰ_ਹੱਦਬੰਦੀ ) +
                                                                                            ( uint32_t ) ( ਪੋਰਟ_BYTE_ALIGNMENT - 1 ) ) &
                                                                                          ( uint32_t ) ( ~( ਪੋਰਟ_BYTE_ALIGNMENT_ਨਕਾਬ ) ) );

            /* This is not NULL only for the duration of a system call. */
            xMPUSettings->x_System_Call_ਢੇਰ_Info.pul_Task_ਢੇਰ = ਨਿਰਾ;
        }
        #ਜੇ_ਅੰਤ /* configUSE_MPU_WRAPPERS_V1 == 0 */

        #ਜੇ ( configENABLE_PAC == 1 )
        {
            uint32_t ul_Task_Pac_ਕੁੰਜੀ[ 4 ], i;

            v_Application_Generate_Task_Random_Pac_ਕੁੰਜੀ( &( ul_Task_Pac_ਕੁੰਜੀ[ 0 ] ) );

            ਲਈ( i = 0; i < 4; i++ )
            {
                xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ul_Task_Pac_ਕੁੰਜੀ[ i ];
                ul_ਸੂਚਕਾਂਕ++;
            }
        }
        #ਜੇ_ਅੰਤ /* configENABLE_PAC */

        ਵਾਪਸ &( xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] );
    }

#ਨਹੀਂਤਾਂ /* configENABLE_MPU */

    ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                         ਢੇਰ_Type_t * px_ਸਿਰਾ_ਦਾ_ਢੇਰ,
                                         TaskFunction_t px_ਕੋਡ,
                                         ਖਾਲੀ * pvParameters ) /* PRIVILEGED_FUNCTION */
    {
        /* Simulate the stack frame as it would be created by a context switch
         * interrupt. */
        #ਜੇ ( ਪੋਰਟ_PRELOAD_REGISTERS == 0 )
        {
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--; /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_XPSR; /* xPSR. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ; /* PC. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_TASK_RETURN_ਪਤਾ; /* LR. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 5; /* R12, R3, R2 and R1. */
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters; /* R0. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 9; /* R11..R4, EXC_RETURN. */
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_EXC_RETURN;
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਸਿਰਾ_ਦਾ_ਢੇਰ; /* Slot used to hold this task's PSPLIM value. */

            #ਜੇ ( configENABLE_TRUSTZONE == 1 )
            {
                px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
                *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_NO_SECURE_CONTEXT; /* Slot used to hold this task's xSecureContext value. */
            }
            #ਜੇ_ਅੰਤ /* configENABLE_TRUSTZONE */
        }
        #ਨਹੀਂਤਾਂ /* portPRELOAD_REGISTERS */
        {
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--; /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_XPSR; /* xPSR. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ; /* PC. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_TASK_RETURN_ਪਤਾ; /* LR. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x12121212UL; /* R12. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x03030303UL; /* R3. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x02020202UL; /* R2. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x01010101UL; /* R1. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters; /* R0. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x11111111UL; /* R11. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x10101010UL; /* R10. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x09090909UL; /* R09. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x08080808UL; /* R08. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x07070707UL; /* R07. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x06060606UL; /* R06. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x05050505UL; /* R05. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x04040404UL; /* R04. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_EXC_RETURN; /* EXC_RETURN. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਸਿਰਾ_ਦਾ_ਢੇਰ; /* Slot used to hold this task's PSPLIM value. */

            #ਜੇ ( configENABLE_TRUSTZONE == 1 )
            {
                px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
                *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_NO_SECURE_CONTEXT; /* Slot used to hold this task's xSecureContext value. */
            }
            #ਜੇ_ਅੰਤ /* configENABLE_TRUSTZONE */
        }
        #ਜੇ_ਅੰਤ /* portPRELOAD_REGISTERS */

        #ਜੇ ( configENABLE_PAC == 1 )
        {
            uint32_t ul_Task_Pac_ਕੁੰਜੀ[ 4 ], i;

            v_Application_Generate_Task_Random_Pac_ਕੁੰਜੀ( &( ul_Task_Pac_ਕੁੰਜੀ[ 0 ] ) );

            ਲਈ( i = 0; i < 4; i++ )
            {
                px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
                *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ul_Task_Pac_ਕੁੰਜੀ[ i ];
            }
        }
        #ਜੇ_ਅੰਤ /* configENABLE_PAC */

        ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
    }

#ਜੇ_ਅੰਤ /* configENABLE_MPU */
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
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
    #ਜੇ ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        ਅਚਲ ਪੋਰਟ_ISR_t * ਅਚਲ px_ਸਦਿਸ਼_ਸਾਰਣੀ = ਪੋਰਟ_SCB_VTOR_REG;

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
        configASSERT( px_ਸਦਿਸ਼_ਸਾਰਣੀ[ ਪੋਰਟ_ਸਦਿਸ਼_ਸੂਚਕਾਂਕ_SVC ] == SVC_Handler );
        configASSERT( px_ਸਦਿਸ਼_ਸਾਰਣੀ[ ਪੋਰਟ_ਸਦਿਸ਼_ਸੂਚਕਾਂਕ_PENDSV ] == PendSV_Handler );
    }
    #ਜੇ_ਅੰਤ /* configCHECK_HANDLER_INSTALLATION */

    v_ਪੋਰਟ_Configure_ਰੁਕਾਵਟ_Priorities();

    #ਜੇ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
    {
        /* Set the CONTROL register value based on PACBTI security feature
         * configuration before starting the first task. */
        #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
            ( ਖਾਲੀ ) prvConfigurePACBTI( pdTRUE );
        #ਨਹੀਂਤਾਂ /* configNUMBER_OF_CORES > 1 */
            ( ਖਾਲੀ ) vConfigurePACBTI( pdTRUE );
        #ਜੇ_ਅੰਤ /* configNUMBER_OF_CORES */
    }
    #ਜੇ_ਅੰਤ /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

    #ਜੇ ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        prv_ਤਿਆਰੀ_MPU();
    }
    #ਜੇ_ਅੰਤ /* configENABLE_MPU */

    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )
        /* Start the timer that generates the tick ISR. Interrupts are disabled
         * here already. */
        v_ਪੋਰਟ_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();
        /* Initialize the critical nesting count for all cores. */
        ਲਈ ( uint8_t ucCoreID = 0; ucCoreID < config_ਸੰਖਿਆ_ਦਾ_CORES; ucCoreID++ )
        {
            ulCriticalNestings[ ucCoreID ] = 0;
        }
        /* Signal that primary core has done all the necessary initialisations. */
        uc_Primary_Core_Init_ਪੂਰਾ_Flag = 1;
        /* Wake up secondary cores */
        ਅਧਾਰ_Type_t x_Wake_ਨਤੀਜਾ = configWAKE_SECONDARY_CORES();
        configASSERT( x_Wake_ਨਤੀਜਾ == pdTRUE );

        /* Hold the primary core here until all the secondary cores are ready, this would be achieved only when
         * all elements of ucSecondaryCoresReadyFlags are set.
         */
        ਜਦੋਂ( 1 )
        {
            ਅਧਾਰ_Type_t xAllCoresReady = pdTRUE;
            ਲਈ( uint8_t ucCoreID = 0; ucCoreID < ( config_ਸੰਖਿਆ_ਦਾ_CORES - 1 ); ucCoreID++ )
            {
                ਜੇ( ucSecondaryCoresReadyFlags[ ucCoreID ] != pdTRUE )
                {
                    xAllCoresReady = pdFALSE;
                    ਰੋਕੋ;
                }
                }

            ਜੇ ( xAllCoresReady == pdTRUE )
            {
                ਰੋਕੋ;
            }
        }
    #ਨਹੀਂਤਾਂ /* if ( configNUMBER_OF_CORES > 1 ) */
        /* Start the timer that generates the tick ISR. */
        v_ਪੋਰਟ_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();
        /* Initialize the critical nesting count ready for the first task. */
        ulCriticalNesting = 0;
    #ਜੇ_ਅੰਤ /* if ( configNUMBER_OF_CORES > 1 ) */

    #ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )
    {
        xSchedulerRunning = pdTRUE;
    }
    #ਜੇ_ਅੰਤ /* ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

    /* Start the first task. */
    v_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();

    /* Should never get here as the tasks will now be executing. Call the task
     * exit error function to prevent compiler warnings about a static function
     * not being called in the case that the application writer overrides this
     * functionality by defining configTASK_RETURN_ADDRESS. Call
     * vTaskSwitchContext() so link time optimization does not remove the
     * symbol. */
    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )
        vTaskSwitchContext( ਪੋਰਟ_GET_CORE_ID() );
    #ਨਹੀਂਤਾਂ
        vTaskSwitchContext();
    #ਜੇ_ਅੰਤ
    prvTaskExitError();

    /* Should not get here. */
    ਵਾਪਸ 0;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
        configASSERT( ulCriticalNesting == 1000UL );
    #ਨਹੀਂਤਾਂ /* if ( configNUMBER_OF_CORES == 1 ) */
        configASSERT( ulCriticalNestings[ ਪੋਰਟ_GET_CORE_ID() ] == 1000UL );
    #ਜੇ_ਅੰਤ /* if ( configNUMBER_OF_CORES == 1 ) */
}
/*-----------------------------------------------------------*/

#ਜੇ ( configENABLE_MPU == 1 )

    ਖਾਲੀ v_ਪੋਰਟ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ਅਚਲ ਬਣਤਰ x_ਸਮ੍ਰਿਤੀ_REGION * ਅਚਲ xRegions,
                                    ਢੇਰ_Type_t * px_Bottom_ਦਾ_ਢੇਰ,
                                    config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE ux_ਢੇਰ_ਡੂੰਘਾਈ )
    {
        uint32_t ul_Region_ਸ਼ੁਰੂ_ਪਤਾ, ul_Region_ਸਿਰਾ_ਪਤਾ, ul_Region_ਸੰਖਿਆ;
        int32_t l_ਸੂਚਕਾਂਕ = 0;

        #ਜੇ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ਬਾਹਰੀ uint32_t * __privileged_sram_start__;
            ਬਾਹਰੀ uint32_t * __privileged_sram_end__;
        #ਨਹੀਂਤਾਂ
            /* Declaration when these variable are exported from linker scripts. */
            ਬਾਹਰੀ uint32_t __privileged_sram_start__[];
            ਬਾਹਰੀ uint32_t __privileged_sram_end__[];
        #ਜੇ_ਅੰਤ /* defined( __ARMCC_VERSION ) */

        /* Setup MAIR0. */
        xMPUSettings->ulMAIR0 = ( ( ਪੋਰਟ_MPU_ਸਾਧਾਰਨ_ਸਮ੍ਰਿਤੀ_BUFFERABLE_CACHEABLE << ਪੋਰਟ_MPU_MAIR_ATTR0_POS ) & ਪੋਰਟ_MPU_MAIR_ATTR0_ਨਕਾਬ );
        xMPUSettings->ulMAIR0 |= ( ( ਪੋਰਟ_MPU_DEVICE_ਸਮ੍ਰਿਤੀ_n_Gn_RE << ਪੋਰਟ_MPU_MAIR_ATTR1_POS ) & ਪੋਰਟ_MPU_MAIR_ATTR1_ਨਕਾਬ );

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid.  At all other
         * times the stack parameters will not be valid and it is assumed that
         * the stack region has already been configured. */
        ਜੇ( ux_ਢੇਰ_ਡੂੰਘਾਈ > 0 )
        {
            ul_Region_ਸ਼ੁਰੂ_ਪਤਾ = ( uint32_t ) px_Bottom_ਦਾ_ਢੇਰ;
            ul_Region_ਸਿਰਾ_ਪਤਾ = ( uint32_t ) px_Bottom_ਦਾ_ਢੇਰ + ( ux_ਢੇਰ_ਡੂੰਘਾਈ * ( config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE ) ਆਕਾਰ( ਢੇਰ_Type_t ) ) - 1;

            /* If the stack is within the privileged SRAM, do not protect it
             * using a separate MPU region. This is needed because privileged
             * SRAM is already protected using an MPU region and ARMv8-M does
             * not allow overlapping MPU regions. */
            ਜੇ( ( ul_Region_ਸ਼ੁਰੂ_ਪਤਾ >= ( uint32_t ) __privileged_sram_start__ ) &&
                ( ul_Region_ਸਿਰਾ_ਪਤਾ <= ( uint32_t ) __privileged_sram_end__ ) )
            {
                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR = 0;
                xMPUSettings->xRegionsSettings[ 0 ].ulRLAR = 0;
            }
            ਨਹੀਂਤਾਂ
            {
                /* Define the region that allows access to the stack. */
                ul_Region_ਸ਼ੁਰੂ_ਪਤਾ &= ਪੋਰਟ_MPU_RBAR_ਪਤਾ_ਨਕਾਬ;
                ul_Region_ਸਿਰਾ_ਪਤਾ &= ਪੋਰਟ_MPU_RLAR_ਪਤਾ_ਨਕਾਬ;

                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR = ( ul_Region_ਸ਼ੁਰੂ_ਪਤਾ ) |
                                                             ( ਪੋਰਟ_MPU_REGION_NON_SHAREABLE ) |
                                                             ( ਪੋਰਟ_MPU_REGION_READ_WRITE ) |
                                                             ( ਪੋਰਟ_MPU_REGION_EXECUTE_NEVER );

                xMPUSettings->xRegionsSettings[ 0 ].ulRLAR = ( ul_Region_ਸਿਰਾ_ਪਤਾ ) |
                                                             ( ਪੋਰਟ_MPU_RLAR_ATTR_INDEX0 ) |
                                                             ( ਪੋਰਟ_MPU_RLAR_REGION_ENABLE );
            }
        }

        /* User supplied configurable regions. */
        ਲਈ( ul_Region_ਸੰਖਿਆ = 1; ul_Region_ਸੰਖਿਆ <= ਪੋਰਟ_ਅੰਕ_CONFIGURABLE_REGIONS; ul_Region_ਸੰਖਿਆ++ )
        {
            /* If xRegions is NULL i.e. the task has not specified any MPU
             * region, the else part ensures that all the configurable MPU
             * regions are invalidated. */
            ਜੇ( ( xRegions != ਨਿਰਾ ) && ( xRegions[ l_ਸੂਚਕਾਂਕ ].ul_ਲੰਮਾਈ_ਵਿੱਚ_ਬਾਈਟਾਂ > 0UL ) )
            {
                /* Translate the generic region definition contained in xRegions
                 * into the ARMv8 specific MPU settings that are then stored in
                 * xMPUSettings. */
                ul_Region_ਸ਼ੁਰੂ_ਪਤਾ = ( ( uint32_t ) xRegions[ l_ਸੂਚਕਾਂਕ ].pv_ਅਧਾਰ_ਪਤਾ ) & ਪੋਰਟ_MPU_RBAR_ਪਤਾ_ਨਕਾਬ;
                ul_Region_ਸਿਰਾ_ਪਤਾ = ( uint32_t ) xRegions[ l_ਸੂਚਕਾਂਕ ].pv_ਅਧਾਰ_ਪਤਾ + xRegions[ l_ਸੂਚਕਾਂਕ ].ul_ਲੰਮਾਈ_ਵਿੱਚ_ਬਾਈਟਾਂ - 1;
                ul_Region_ਸਿਰਾ_ਪਤਾ &= ਪੋਰਟ_MPU_RLAR_ਪਤਾ_ਨਕਾਬ;

                /* Start address. */
                xMPUSettings->xRegionsSettings[ ul_Region_ਸੰਖਿਆ ].ulRBAR = ( ul_Region_ਸ਼ੁਰੂ_ਪਤਾ ) |
                                                                          ( ਪੋਰਟ_MPU_REGION_NON_SHAREABLE );

                /* RO/RW. */
                ਜੇ( ( xRegions[ l_ਸੂਚਕਾਂਕ ].ulParameters & tskMPU_REGION_READ_ONLY ) != 0 )
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_ਸੰਖਿਆ ].ulRBAR |= ( ਪੋਰਟ_MPU_REGION_READ_ONLY );
                }
                ਨਹੀਂਤਾਂ
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_ਸੰਖਿਆ ].ulRBAR |= ( ਪੋਰਟ_MPU_REGION_READ_WRITE );
                }

                /* XN. */
                ਜੇ( ( xRegions[ l_ਸੂਚਕਾਂਕ ].ulParameters & tskMPU_REGION_EXECUTE_NEVER ) != 0 )
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_ਸੰਖਿਆ ].ulRBAR |= ( ਪੋਰਟ_MPU_REGION_EXECUTE_NEVER );
                }

                /* End Address. */
                xMPUSettings->xRegionsSettings[ ul_Region_ਸੰਖਿਆ ].ulRLAR = ( ul_Region_ਸਿਰਾ_ਪਤਾ ) |
                                                                          ( ਪੋਰਟ_MPU_RLAR_REGION_ENABLE );

                /* PXN. */
                #ਜੇ ( ਪੋਰਟ_ARMV8_M_MINOR_ਸੰਸਕਰਣ >= 1 )
                {
                    ਜੇ( ( xRegions[ l_ਸੂਚਕਾਂਕ ].ulParameters & tskMPU_REGION_PRIVILEGED_EXECUTE_NEVER ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ ul_Region_ਸੰਖਿਆ ].ulRLAR |= ( ਪੋਰਟ_MPU_RLAR_PRIVILEGED_EXECUTE_NEVER );
                    }
                }
                #ਜੇ_ਅੰਤ /* portARMV8M_MINOR_VERSION >= 1 */

                /* Normal memory/ Device memory. */
                ਜੇ( ( xRegions[ l_ਸੂਚਕਾਂਕ ].ulParameters & tsk_MPU_REGION_DEVICE_ਸਮ੍ਰਿਤੀ ) != 0 )
                {
                    /* Attr1 in MAIR0 is configured as device memory. */
                    xMPUSettings->xRegionsSettings[ ul_Region_ਸੰਖਿਆ ].ulRLAR |= ਪੋਰਟ_MPU_RLAR_ATTR_INDEX1;
                }
                ਨਹੀਂਤਾਂ
                {
                    /* Attr0 in MAIR0 is configured as normal memory. */
                    xMPUSettings->xRegionsSettings[ ul_Region_ਸੰਖਿਆ ].ulRLAR |= ਪੋਰਟ_MPU_RLAR_ATTR_INDEX0;
                }
            }
            ਨਹੀਂਤਾਂ
            {
                /* Invalidate the region. */
                xMPUSettings->xRegionsSettings[ ul_Region_ਸੰਖਿਆ ].ulRBAR = 0UL;
                xMPUSettings->xRegionsSettings[ ul_Region_ਸੰਖਿਆ ].ulRLAR = 0UL;
            }

            l_ਸੂਚਕਾਂਕ++;
        }
    }

#ਜੇ_ਅੰਤ /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( ਅਚਲ ਖਾਲੀ * pv_ਬਫਰ,
                                                size_t x_ਬਫਰ_ਲੰਮਾਈ,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_ਬਫਰ_ਸ਼ੁਰੂ_ਪਤਾ, ul_ਬਫਰ_ਸਿਰਾ_ਪਤਾ;
        ਅਧਾਰ_Type_t xAccessGranted = pdFALSE;
        ਅਚਲ xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ਨਿਰਾ ); /* Calling task's MPU settings. */

        ਜੇ( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        ਨਹੀਂਤਾਂ ਜੇ( ( xTaskMpuSettings->ulTaskFlags & ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG ) == ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        ਨਹੀਂਤਾਂ
        {
            ਜੇ( ਪੋਰਟ_ਜੋੜੋ_UINT32_WILL_ਉਛਾਲ( ( ( uint32_t ) pv_ਬਫਰ ), ( ( uint32_t ) x_ਬਫਰ_ਲੰਮਾਈ - 1UL ) ) == pdFALSE )
            {
                ul_ਬਫਰ_ਸ਼ੁਰੂ_ਪਤਾ = ( uint32_t ) pv_ਬਫਰ;
                ul_ਬਫਰ_ਸਿਰਾ_ਪਤਾ = ( ( ( uint32_t ) pv_ਬਫਰ ) + ( uint32_t ) x_ਬਫਰ_ਲੰਮਾਈ - 1UL );

                ਲਈ( i = 0; i < ਪੋਰਟ_ਕੁੱਲ_ਅੰਕ_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    ਜੇ( ( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR & ਪੋਰਟ_MPU_RLAR_REGION_ENABLE ) == ਪੋਰਟ_MPU_RLAR_REGION_ENABLE )
                    {
                        ਜੇ( ਪੋਰਟ_IS_ਪਤਾ_WITHIN_RANGE( ul_ਬਫਰ_ਸ਼ੁਰੂ_ਪਤਾ,
                                                         ਪੋਰਟ_ਕੱਢੋ_ਪਹਿਲਾ_ਪਤਾ_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ),
                                                         ਪੋਰਟ_ਕੱਢੋ_ਆਖਰੀ_ਪਤਾ_FROM_RLAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR ) ) &&
                            ਪੋਰਟ_IS_ਪਤਾ_WITHIN_RANGE( ul_ਬਫਰ_ਸਿਰਾ_ਪਤਾ,
                                                         ਪੋਰਟ_ਕੱਢੋ_ਪਹਿਲਾ_ਪਤਾ_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ),
                                                         ਪੋਰਟ_ਕੱਢੋ_ਆਖਰੀ_ਪਤਾ_FROM_RLAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR ) ) &&
                            ਪੋਰਟ_IS_AUTHORIZED( ulAccessRequested,
                                               prvGetRegionAccessPermissions( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ) ) )
                        {
                            xAccessGranted = pdTRUE;
                            ਰੋਕੋ;
                        }
                    }
                }
            }
        }

        ਵਾਪਸ xAccessGranted;
    }

#ਜੇ_ਅੰਤ /* #if ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Inside_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    uint32_t ul_Current_ਰੁਕਾਵਟ;
    ਅਧਾਰ_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. Interrupt Program
     * Status Register (IPSR) holds the exception number of the currently-executing
     * exception or zero for Thread mode.*/
    __asm ਅਸਥਿਰ ( "mrs %0, ipsr" : "=r" ( ul_Current_ਰੁਕਾਵਟ )::"memory" );

    ਜੇ( ul_Current_ਰੁਕਾਵਟ == 0 )
    {
        xReturn = pdFALSE;
    }
    ਨਹੀਂਤਾਂ
    {
        xReturn = pdTRUE;
    }

    ਵਾਪਸ xReturn;
}
/*-----------------------------------------------------------*/

#ਜੇ ( ( configASSERT_DEFINED == 1 ) && ( ਪੋਰਟ_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) )

    ਖਾਲੀ v_ਪੋਰਟ_Validate_ਰੁਕਾਵਟ_ਤਰਜੀਹ( ਖਾਲੀ )
    {
        uint32_t ul_Current_ਰੁਕਾਵਟ;
        uint8_t uc_Current_ਤਰਜੀਹ;

        /* Obtain the number of the currently executing interrupt. */
        __asm ਅਸਥਿਰ ( "mrs %0, ipsr" : "=r" ( ul_Current_ਰੁਕਾਵਟ )::"memory" );

        /* Is the interrupt number a user defined interrupt? */
        ਜੇ( ul_Current_ਰੁਕਾਵਟ >= ਪੋਰਟ_ਪਹਿਲਾ_USER_ਰੁਕਾਵਟ_ਸੰਖਿਆ )
        {
            /* Look up the interrupt's priority. */
            uc_Current_ਤਰਜੀਹ = pc_ਰੁਕਾਵਟ_ਤਰਜੀਹ_Registers[ ul_Current_ਰੁਕਾਵਟ ];

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
            configASSERT( uc_Current_ਤਰਜੀਹ >= uc_Max_Sys_Call_ਤਰਜੀਹ );
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
        configASSERT( ( ਪੋਰਟ_AIRCR_REG & ਪੋਰਟ_ਤਰਜੀਹ_ਸਮੂਹ_ਨਕਾਬ ) <= ulMaxPRIGROUPValue );
    }

#ਜੇ_ਅੰਤ /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Configure_ਰੁਕਾਵਟ_Priorities( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
{
    #ਜੇ ( ( configASSERT_DEFINED == 1 ) && ( ਪੋਰਟ_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) )
    {
        ਅਸਥਿਰ uint32_t ul_Implemented_Prio_ਬਿੱਟ = 0;
        ਅਸਥਿਰ uint8_t uc_Max_ਤਰਜੀਹ_ਮੁੱਲ;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
        * functions can be called. ISR safe functions are those that end in
        * "FromISR". FreeRTOS maintains separate thread and ISR API functions to
        * ensure interrupt entry is as fast and simple as possible.
        *
        * First, determine the number of priority bits available. Write to all
        * possible bits in the priority setting for SVCall. */
        ਪੋਰਟ_NVIC_SHPR2_REG = 0xFF000000;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ਤਰਜੀਹ_ਮੁੱਲ = ( uint8_t ) ( ( ਪੋਰਟ_NVIC_SHPR2_REG & 0xFF000000 ) >> 24 );

        /* Use the same mask on the maximum system call priority. */
        uc_Max_Sys_Call_ਤਰਜੀਹ = config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ & uc_Max_ਤਰਜੀਹ_ਮੁੱਲ;

        /* Check that the maximum system call priority is nonzero after
        * accounting for the number of priority bits supported by the
        * hardware. A priority of 0 is invalid because setting the BASEPRI
        * register to 0 unmasks all interrupts, and interrupts with priority 0
        * cannot be masked using BASEPRI.
        * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( uc_Max_Sys_Call_ਤਰਜੀਹ );

        /* Check that the bits not implemented in hardware are zero in
        * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ & ( uint8_t ) ( ~( uint32_t ) uc_Max_ਤਰਜੀਹ_ਮੁੱਲ ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
        * of bits read back. */
        ਜਦੋਂ( ( uc_Max_ਤਰਜੀਹ_ਮੁੱਲ & ਪੋਰਟ_ਸਿਖਰ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਦਾ_BYTE ) == ਪੋਰਟ_ਸਿਖਰ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਦਾ_BYTE )
        {
            ul_Implemented_Prio_ਬਿੱਟ++;
            uc_Max_ਤਰਜੀਹ_ਮੁੱਲ <<= ( uint8_t ) 0x01;
        }

        ਜੇ( ul_Implemented_Prio_ਬਿੱਟ == 8 )
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
            configASSERT( ( config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        ਨਹੀਂਤਾਂ
        {
            ulMaxPRIGROUPValue = ਪੋਰਟ_MAX_PRIGROUP_ਬਿੱਟ - ul_Implemented_Prio_ਬਿੱਟ;
        }

        /* Shift the priority group value back to its position within the AIRCR
        * register. */
        ulMaxPRIGROUPValue <<= ਪੋਰਟ_PRIGROUP_ਖਿਸਕਾਓ;
        ulMaxPRIGROUPValue &= ਪੋਰਟ_ਤਰਜੀਹ_ਸਮੂਹ_ਨਕਾਬ;
    }
    #ਜੇ_ਅੰਤ /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */

    /* Make PendSV and SysTick the lowest priority interrupts, and make SVCall
    * the highest priority. */
    ਪੋਰਟ_NVIC_SHPR3_REG |= ਪੋਰਟ_NVIC_PENDSV_PRI;
    ਪੋਰਟ_NVIC_SHPR3_REG |= ਪੋਰਟ_NVIC_SYSTICK_PRI;
    ਪੋਰਟ_NVIC_SHPR2_REG = 0;
}
/*-----------------------------------------------------------*/

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    ਖਾਲੀ v_ਪੋਰਟ_Grant_Access_ਮੰਜ਼ਿਲ_Kernel_Object( TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle,
                                         int32_t l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ, ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object / ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );
        ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object % ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );

        xTaskMpuSettings = xTaskGetMPUSettings( x_ਅੰਦਰੂਨੀ_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ ] |= ( 1U << ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ );
    }

#ਜੇ_ਅੰਤ /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    ਖਾਲੀ v_ਪੋਰਟ_Revoke_Access_ਮੰਜ਼ਿਲ_Kernel_Object( TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle,
                                          int32_t l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ, ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object / ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );
        ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object % ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );

        xTaskMpuSettings = xTaskGetMPUSettings( x_ਅੰਦਰੂਨੀ_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ ] &= ~( 1U << ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ );
    }

#ਜੇ_ਅੰਤ /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #ਜੇ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( int32_t l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ, ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ;
            ਅਧਾਰ_Type_t xAccessGranted = pdFALSE;
            ਅਚਲ xMPU_SETTINGS * xTaskMpuSettings;

            ਜੇ( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            ਨਹੀਂਤਾਂ
            {
                xTaskMpuSettings = xTaskGetMPUSettings( ਨਿਰਾ ); /* Calling task's MPU settings. */

                ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object / ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );
                ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object % ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );

                ਜੇ( ( xTaskMpuSettings->ulTaskFlags & ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG ) == ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                ਨਹੀਂਤਾਂ
                {
                    ਜੇ( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ ] & ( 1U << ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            ਵਾਪਸ xAccessGranted;
        }

    #ਨਹੀਂਤਾਂ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( int32_t l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( ਖਾਲੀ ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            ਵਾਪਸ pdTRUE;
        }

    #ਜੇ_ਅੰਤ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#ਜੇ_ਅੰਤ /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */
/*-----------------------------------------------------------*/

#ਜੇ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
        ਸਥਿਰ uint32_t prvConfigurePACBTI( ਅਧਾਰ_Type_t x_Write_Control_ਰਜਿਸਟਰ )
    #ਨਹੀਂਤਾਂ /* configNUMBER_OF_CORES > 1 */
        uint32_t vConfigurePACBTI( ਅਧਾਰ_Type_t x_Write_Control_ਰਜਿਸਟਰ )
    #ਜੇ_ਅੰਤ /* configNUMBER_OF_CORES */
        {
            uint32_t ulControl = 0x0;

            /* Ensure that PACBTI is implemented. */
            configASSERT( ਪੋਰਟ_ID_ISAR5_REG != 0x0 );

            /* Enable UsageFault exception. */
            ਪੋਰਟ_SCB_SYS_HANDLER_CTRL_STATE_REG |= ਪੋਰਟ_SCB_USG_FAULT_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ;

            #ਜੇ ( configENABLE_PAC == 1 )
            {
                ulControl |= ( ਪੋਰਟ_CONTROL_UPAC_EN | ਪੋਰਟ_CONTROL_PAC_EN );
            }
            #ਜੇ_ਅੰਤ

            #ਜੇ ( configENABLE_BTI == 1 )
            {
                ulControl |= ( ਪੋਰਟ_CONTROL_UBTI_EN | ਪੋਰਟ_CONTROL_BTI_EN );
            }
            #ਜੇ_ਅੰਤ

            ਜੇ( x_Write_Control_ਰਜਿਸਟਰ == pdTRUE )
            {
                __asm ਅਸਥਿਰ ( "msr control, %0" : : "r" ( ulControl ) );
            }

            ਵਾਪਸ ulControl;
        }

#ਜੇ_ਅੰਤ /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */
/*-----------------------------------------------------------*/

#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )

    /* Which core owns the lock? */
    PRIVILEGED_ਅੰਕੜੇ ਅਸਥਿਰ uint32_t ulOwnedByCore[ ਪੋਰਟ_MAX_CORE_ਗਿਣਤੀ ];
    /* Lock count a core owns. */
    PRIVILEGED_ਅੰਕੜੇ ਅਸਥਿਰ uint32_t ul_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ e_ਤਾਲਾ_ਗਿਣਤੀ ];
    /* Index 0 is used for ISR lock and Index 1 is used for task lock. */
    PRIVILEGED_ਅੰਕੜੇ ਅਸਥਿਰ uint32_t ul_Gate_ਸ਼ਬਦ[ e_ਤਾਲਾ_ਗਿਣਤੀ ];

    __attribute__((weak)) ਖਾਲੀ v_ਰੁਕਾਵਟ_Core( uint8_t ucCoreID )
    {
        /* Default weak stub - platform specific implementation may override. */
        ( ਖਾਲੀ ) ucCoreID;
    }

/*-----------------------------------------------------------*/

    ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ prvSpinUnlock( ਅਸਥਿਰ uint32_t * ul_ਤਾਲਾ )
    {
        /* Conservative unlock: preserve original barriers for broad HW/FVP. */
        __asm ਅਸਥਿਰ (
            "dmb sy         \n"
            "mov r1, #0     \n"
            "str r1, [%0]   \n"
            "sev            \n"
            "dsb            \n"
            "isb            \n"
            :
            : "r" ( ul_ਤਾਲਾ )
            : "memory", "r1"
        );
    }

/*-----------------------------------------------------------*/

    ਸਥਿਰ ਸਤਰਅੰਦਰ uint32_t prvSpinTrylock( ਅਸਥਿਰ uint32_t * ul_ਤਾਲਾ )
    {
        /*
         * Conservative ldrex/strex trylock:
         * - Return 1 immediately if busy, clearing exclusive state (CLREX).
         * - Retry strex only on spurious failure when observed free.
         * - DMB on success to preserve expected acquire semantics.
         */
        uint32_t ulVal;
        uint32_t ul_ਸਥਿਤੀ;

        __asm ਅਸਥਿਰ (
            " ldrex %0, [%1]   \n"
            : "=r" ( ulVal )
            : "r" ( ul_ਤਾਲਾ )
            : "memory"
        );

        ਜੇ( ulVal != 0U )
        {
            __asm ਅਸਥਿਰ ("clrex" ::: "memory");
            ਵਾਪਸ 1U;
        }

        __asm ਅਸਥਿਰ (
            " strex %0, %2, [%1]   \n"
            : "=&r" ( ul_ਸਥਿਤੀ )
            : "r" ( ul_ਤਾਲਾ ), "r" (1U)
            : "memory"
        );

        ਜੇ( ul_ਸਥਿਤੀ != 0U )
        {
            ਵਾਪਸ 1U;
        }
        __asm ਅਸਥਿਰ ( "dmb" ::: "memory" );
        ਵਾਪਸ 0U;
    }


/*-----------------------------------------------------------*/

    /* Read 32b value shared between cores. */
    ਸਥਿਰ ਸਤਰਅੰਦਰ uint32_t prvGet32( ਅਸਥਿਰ uint32_t * x )
    {
        __asm( "dsb" );
        ਵਾਪਸ *x;
    }

/*-----------------------------------------------------------*/

    /* Write 32b value shared between cores. */
    ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ prvSet32( ਅਸਥਿਰ uint32_t * x,
                                 uint32_t ਮੁੱਲ )
    {
        *x = ਮੁੱਲ;
        __asm( "dsb" );
    }

/*-----------------------------------------------------------*/

    ਖਾਲੀ v_ਪੋਰਟ_Recursive_ਤਾਲਾ( uint8_t ucCoreID,
                             e_ਪੋਰਟ_RTOSLock e_ਤਾਲਾ_ਅੰਕ,
                             ਅਧਾਰ_Type_t uxAcquire )
    {
        /* Validate the core ID and lock number. */
        configASSERT( ucCoreID < ਪੋਰਟ_MAX_CORE_ਗਿਣਤੀ );
        configASSERT( e_ਤਾਲਾ_ਅੰਕ < e_ਤਾਲਾ_ਗਿਣਤੀ );

        uint32_t ul_ਤਾਲਾ_ਦੋਆਧਾਰੀ_ਅੰਕ = 1u << e_ਤਾਲਾ_ਅੰਕ;

        /* Lock acquire */
        ਜੇ( uxAcquire )
        {
            /* Check if spinlock is available. */
            /* If spinlock is not available check if the core owns the lock. */
            /* If the core owns the lock wait increment the lock count by the core. */
            /* If core does not own the lock wait for the spinlock. */
            ਜੇ( prvSpinTrylock( &ul_Gate_ਸ਼ਬਦ[ e_ਤਾਲਾ_ਅੰਕ ] ) != 0 )
            {
                /* Check if the core owns the spinlock. */
                ਜੇ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ul_ਤਾਲਾ_ਦੋਆਧਾਰੀ_ਅੰਕ )
                {
                    configASSERT( prvGet32( &ul_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ e_ਤਾਲਾ_ਅੰਕ ] ) != ਪੋਰਟ_UINT32_MAX );
                    prvSet32( &ul_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ e_ਤਾਲਾ_ਅੰਕ ], ( prvGet32( &ul_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ e_ਤਾਲਾ_ਅੰਕ ] ) + 1 ) );
                    ਵਾਪਸ;
                }

                /* Preload the gate word into the cache. */
                uint32_t dummy = ul_Gate_ਸ਼ਬਦ[ e_ਤਾਲਾ_ਅੰਕ ];
                dummy++;

                ਜਦੋਂ( prvSpinTrylock( &ul_Gate_ਸ਼ਬਦ[ e_ਤਾਲਾ_ਅੰਕ ] ) != 0 )
                {
                    __asm ਅਸਥਿਰ ( "wfe" );
                }
            }

            /* Add barrier to ensure lock is taken before we proceed. */
            __asm ਅਸਥਿਰ( "dmb sy" ::: "memory" );

            /* Assert the lock count is 0 when the spinlock is free and is acquired. */
            configASSERT( prvGet32( &ul_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ e_ਤਾਲਾ_ਅੰਕ ] ) == 0 );

            /* Set lock count as 1. */
            prvSet32( &ul_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ e_ਤਾਲਾ_ਅੰਕ ], 1 );
            /* Set ulOwnedByCore. */
            prvSet32( &ulOwnedByCore[ ucCoreID ], ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) | ul_ਤਾਲਾ_ਦੋਆਧਾਰੀ_ਅੰਕ ) );
        }
        /* Lock release. */
        ਨਹੀਂਤਾਂ
        {
            /* Assert the lock is not free already. */
            configASSERT( ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ul_ਤਾਲਾ_ਦੋਆਧਾਰੀ_ਅੰਕ ) != 0 );
            configASSERT( prvGet32( &ul_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ e_ਤਾਲਾ_ਅੰਕ ] ) != 0 );

            /* Reduce ulRecursionCountByLock by 1. */
            prvSet32( &ul_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ e_ਤਾਲਾ_ਅੰਕ ], ( prvGet32( &ul_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ e_ਤਾਲਾ_ਅੰਕ ] ) - 1 ) );

            ਜੇ( !prvGet32( &ul_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ e_ਤਾਲਾ_ਅੰਕ ] ) )
            {
                prvSet32( &ulOwnedByCore[ ucCoreID ], ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ~ul_ਤਾਲਾ_ਦੋਆਧਾਰੀ_ਅੰਕ ) );
                prvSpinUnlock( &ul_Gate_ਸ਼ਬਦ[ e_ਤਾਲਾ_ਅੰਕ ] );
                /* Add barrier to ensure lock status is reflected before we proceed. */
                __asm ਅਸਥਿਰ( "dmb sy" ::: "memory" );
            }
        }
    }

/*-----------------------------------------------------------*/

    uint8_t uc_ਪੋਰਟ_Get_Core_ID( ਖਾਲੀ )
    {
        ਵਾਪਸ *(ਅਸਥਿਰ uint8_t *)(config_CORE_ID_ਰਜਿਸਟਰ);
    }

/*-----------------------------------------------------------*/

#ਜੇ_ਅੰਤ /* if( configNUMBER_OF_CORES > 1 ) */
