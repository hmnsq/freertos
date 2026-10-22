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
#ವ್ಯಾಖ್ಯಾನಿಸು MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* MPU includes. */
#ಅನ್ತರ್ಭಾವ "mpu_wrappers.h"
#ಅನ್ತರ್ಭಾವ "mpu_syscall_numbers.h"

/* Portasm includes. */
#ಅನ್ತರ್ಭಾವ "portasm.h"

#ಆದರೆ ( configENABLE_TRUSTZONE == 1 )
    /* Secure components includes. */
    #ಅನ್ತರ್ಭಾವ "secure_context.h"
    #ಅನ್ತರ್ಭಾವ "secure_init.h"
#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_TRUSTZONE */

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು MPU_WRAPPERS_INCLUDED_FROM_API_FILE

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
#ಆದರೆ ( ( config_ಸತತ_FREERTOS_SECURE_ONLY == 1 ) && ( configENABLE_TRUSTZONE == 1 ) )
    #ದೋಷ TrustZone needs ಗಮ್ಯ be disabled ಒಳ ಕ್ರಮ ಗಮ್ಯ ಸತತ FreeRTOS on the Secure Side.
#ಆದರೆ_ಅಂತ್ಯ

/**
 * Cortex-M23 does not have non-secure PSPLIM. We should use PSPLIM on Cortex-M23
 * only when FreeRTOS runs on secure side.
 */
#ಆದರೆ ( ( ಪೋರ್ಟ್_HAS_ARMV8_M_MAIN_EXTENSION == 0 ) && ( config_ಸತತ_FREERTOS_SECURE_ONLY == 0 ) )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_USE_PSPLIM_ರಿಜಿಸ್ಟರ್    0
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_USE_PSPLIM_ರಿಜಿಸ್ಟರ್    1
#ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

/**
 * @brief Prototype of all Interrupt Service Routines (ISRs).
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ ( * ಪೋರ್ಟ್_ISR_t )( ಶೂನ್ಯ );
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the NVIC.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG             ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000e010 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG             ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000e014 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG    ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000e018 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SHPR3_REG                    ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed20 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್           ( 1UL << 0UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್              ( 1UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್              ( 1UL << 2UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_ಎಣಿಕೆ_FLAG_ಬಿಟ್       ( 1UL << 16UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_PEND_SYSTICK_CLEAR_ಬಿಟ್       ( 1UL << 25UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_PEND_SYSTICK_ಗಣ_ಬಿಟ್         ( 1UL << 26UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MIN_ಅಡಚಣೆ_ಆದ್ಯತೆ            ( 255UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_PENDSV_PRI                   ( ಪೋರ್ಟ್_MIN_ಅಡಚಣೆ_ಆದ್ಯತೆ << 16UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_PRI                  ( ಪೋರ್ಟ್_MIN_ಅಡಚಣೆ_ಆದ್ಯತೆ << 24UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the SCB.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SCB_VTOR_REG                      ( *( ( ಪೋರ್ಟ್_ISR_t ** ) 0xe000ed08 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SCB_SYS_HANDLER_CTRL_STATE_REG    ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed24 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SCB_MEM_FAULT_ENABLE_ಬಿಟ್          ( 1UL << 16UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SCB_USG_FAULT_ENABLE_ಬಿಟ್          ( 1UL << 18UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants used to check the installation of the FreeRTOS interrupt handlers.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸದಿಶ_ಸೂಚ್ಯಂಕ_SVC       ( 11 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸದಿಶ_ಸೂಚ್ಯಂಕ_PENDSV    ( 14 )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to check the validity of an interrupt priority.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SHPR2_REG                 ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xE000ED1C ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಮೊದಲ_USER_ಅಡಚಣೆ_ಸಂಖ್ಯೆ    ( 16 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_IP_REGISTERS_ಸ್ಥಾನಾಂತರ_16    ( 0xE000E3F0 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_AIRCR_REG                      ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xE000ED0C ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ತುದಿ_ಬಿಟ್_ದ_BYTE                ( ( uint8_t ) 0x80 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_PRIGROUP_ಬಿಟ್ಟುಗಳು              ( ( uint8_t ) 7 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಗುಂಪು_ಮುಖವಾಡ            ( 0x07UL << 8UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIGROUP_ಸರಿಸು                 ( 8UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants used during system call enter and exit.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PSR_ರಾಶಿ_PADDING_ಮುಖವಾಡ              ( 1UL << 9UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXC_RETURN_ರಾಶಿ_ಚೌಕಟ್ಟು_TYPE_ಮುಖವಾಡ    ( 1UL << 4UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the FPU.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CPACR               ( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed88 ) /* Coprocessor Access Control Register. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CPACR_CP10_ಮೌಲ್ಯ    ( 3UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CPACR_CP11_ಮೌಲ್ಯ    ಪೋರ್ಟ್_CPACR_CP10_ಮೌಲ್ಯ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CPACR_CP10_POS      ( 20UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CPACR_CP11_POS      ( 22UL )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FPCCR               ( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ef34 ) /* Floating Point Context Control Register. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FPCCR_ASPEN_POS     ( 31UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FPCCR_ASPEN_ಮುಖವಾಡ    ( 1UL << ಪೋರ್ಟ್_FPCCR_ASPEN_POS )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FPCCR_LSPEN_POS     ( 30UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FPCCR_LSPEN_ಮುಖವಾಡ    ( 1UL << ಪೋರ್ಟ್_FPCCR_LSPEN_POS )
/*-----------------------------------------------------------*/

/**
 * @brief Offsets in the stack to the parameters when inside the SVC handler.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_LR     ( 5 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PC     ( 6 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PSR    ( 7 )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the MPU.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_TYPE_REG                        ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed90 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_CTRL_REG                        ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed94 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RNR_REG                         ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed98 ) )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RBAR_REG                        ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed9c ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RLAR_REG                        ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000eda0 ) )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RBAR_A1_REG                     ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000eda4 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RLAR_A1_REG                     ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000eda8 ) )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RBAR_A2_REG                     ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000edac ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RLAR_A2_REG                     ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000edb0 ) )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RBAR_A3_REG                     ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000edb4 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RLAR_A3_REG                     ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000edb8 ) )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR0_REG                       ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000edc0 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR1_REG                       ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000edc4 ) )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RBAR_ವಿಳಾಸ_ಮುಖವಾಡ               ( 0xffffffe0 ) /* Must be 32-byte aligned. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RLAR_ವಿಳಾಸ_ಮುಖವಾಡ               ( 0xffffffe0 ) /* Must be 32-byte aligned. */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RBAR_ACCESS_PERMISSIONS_ಮುಖವಾಡ    ( 3UL << 1UL )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_ATTR0_POS                  ( 0UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_ATTR0_ಮುಖವಾಡ                 ( 0x000000ff )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_ATTR1_POS                  ( 8UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_ATTR1_ಮುಖವಾಡ                 ( 0x0000ff00 )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_ATTR2_POS                  ( 16UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_ATTR2_ಮುಖವಾಡ                 ( 0x00ff0000 )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_ATTR3_POS                  ( 24UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_ATTR3_ಮುಖವಾಡ                 ( 0xff000000 )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_ATTR4_POS                  ( 0UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_ATTR4_ಮುಖವಾಡ                 ( 0x000000ff )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_ATTR5_POS                  ( 8UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_ATTR5_ಮುಖವಾಡ                 ( 0x0000ff00 )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_ATTR6_POS                  ( 16UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_ATTR6_ಮುಖವಾಡ                 ( 0x00ff0000 )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_ATTR7_POS                  ( 24UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_ATTR7_ಮುಖವಾಡ                 ( 0xff000000 )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RLAR_ATTR_INDEX0                ( 0UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RLAR_ATTR_INDEX1                ( 1UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RLAR_ATTR_INDEX2                ( 2UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RLAR_ATTR_INDEX3                ( 3UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RLAR_ATTR_INDEX4                ( 4UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RLAR_ATTR_INDEX5                ( 5UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RLAR_ATTR_INDEX6                ( 6UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RLAR_ATTR_INDEX7                ( 7UL << 1UL )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RLAR_REGION_ENABLE              ( 1UL )

#ಆದರೆ ( ಪೋರ್ಟ್_ARMV8_M_MINOR_ಆವೃತ್ತಿ >= 1 )

    /* Enable Privileged eXecute Never MPU attribute for the selected memory
     * region. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RLAR_PRIVILEGED_EXECUTE_NEVER    ( 1UL << 4UL )
#ಆದರೆ_ಅಂತ್ಯ /* portARMV8M_MINOR_VERSION >= 1 */

/* Enable privileged access to unmapped region. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_PRIV_BACKGROUND_ENABLE_ಬಿಟ್    ( 1UL << 2UL )

/* Enable MPU. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_ENABLE_ಬಿಟ್                    ( 1UL << 0UL )

/* Extract first address of the MPU region as encoded in the
 * RBAR (Region Base Address Register) value. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಹೊರತೆಗೆ_ಮೊದಲ_ವಿಳಾಸ_FROM_RBAR( rbar ) \
    ( ( rbar ) & ಪೋರ್ಟ್_MPU_RBAR_ವಿಳಾಸ_ಮುಖವಾಡ )

/* Extract last address of the MPU region as encoded in the
 * RLAR (Region Limit Address Register) value. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಹೊರತೆಗೆ_ಕೊನೆಯ_ವಿಳಾಸ_FROM_RLAR( rlar ) \
    ( ( ( rlar ) & ಪೋರ್ಟ್_MPU_RLAR_ವಿಳಾಸ_ಮುಖವಾಡ ) | ~ಪೋರ್ಟ್_MPU_RLAR_ವಿಳಾಸ_ಮುಖವಾಡ )

/* Does addr lies within [start, end] address range? */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IS_ವಿಳಾಸ_WITHIN_RANGE( addr, ಆರಂಭ, ಕೊನೆ ) \
    ( ( ( addr ) >= ( ಆರಂಭ ) ) && ( ( addr ) <= ( ಕೊನೆ ) ) )

/* Is the access request satisfied by the available permissions? */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೂಡಿಸು_UINT32_WILL_ಅತಿಪ್ರವಾಹ( a, b )    ( ( a ) > ( ಪೋರ್ಟ್_UINT32_MAX - ( b ) ) )
/*-----------------------------------------------------------*/

/**
 * @brief The maximum 24-bit number.
 *
 * It is needed because the systick is a 24-bit counter.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_24_ಬಿಟ್_ಸಂಖ್ಯೆ       ( 0xffffffUL )

/**
 * @brief A fiddle factor to estimate the number of SysTick counts that would
 * have occurred while the SysTick counter is stopped during tickless idle
 * calculations.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MISSED_COUNTS_ಗುಣಕ    ( 94UL )
/*-----------------------------------------------------------*/

/**
 * @brief Constants required to set up the initial stack.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_XPSR    ( 0x01000000 )

#ಆದರೆ ( config_ಸತತ_FREERTOS_SECURE_ONLY == 1 )

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
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_EXC_RETURN    ( 0xfffffffd )
#ಇಲ್ಲದಿದ್ದರೆ

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
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_EXC_RETURN    ( 0xffffffbc )
#ಆದರೆ_ಅಂತ್ಯ /* configRUN_FREERTOS_SECURE_ONLY */

/**
 * @brief CONTROL register privileged bit mask.
 *
 * Bit[0] in CONTROL register tells the privilege:
 *  Bit[0] = 0 ==> The task is privileged.
 *  Bit[0] = 1 ==> The task is not privileged.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CONTROL_PRIVILEGED_ಮುಖವಾಡ         ( 1UL << 0UL )

/**
 * @brief Initial CONTROL register values.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_CONTROL_UNPRIVILEGED    ( 0x3 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_CONTROL_PRIVILEGED      ( 0x2 )

/**
 * @brief Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register.
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configSYSTICK_CLOCK_HZ
    #ವ್ಯಾಖ್ಯಾನಿಸು configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG    ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ )
#ಇಲ್ಲದಿದ್ದರೆ
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG    ( 0 )
#ಆದರೆ_ಅಂತ್ಯ

/**
 * @brief Let the user override the pre-loading of the initial LR with the
 * address of prvTaskExitError() in case it messes up unwinding of the stack
 * in the debugger.
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ config_TASK_RETURN_ವಿಳಾಸ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ    config_TASK_RETURN_ವಿಳಾಸ
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ    prvTaskExitError
#ಆದರೆ_ಅಂತ್ಯ

/**
 * @brief If portPRELOAD_REGISTERS then registers will be given an initial value
 * when a task is created. This helps in debugging at the cost of code size.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRELOAD_REGISTERS    1

/**
 * @brief A task is created without a secure context, and must call
 * portALLOCATE_SECURE_CONTEXT() to give itself a secure context before it makes
 * any secure calls.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_SECURE_CONTEXT    0

/**
 * @brief Constants required to check and configure PACBTI security feature implementation.
 */
#ಆದರೆ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ID_ISAR5_REG       ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed74 ) )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CONTROL_UPAC_EN    ( 1UL << 7UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CONTROL_PAC_EN     ( 1UL << 6UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CONTROL_UBTI_EN    ( 1UL << 5UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CONTROL_BTI_EN     ( 1UL << 4UL )

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Used to catch tasks that attempt to return from their implementing
 * function.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ );

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Extract MPU region's access permissions from the Region Base Address
     * Register (RBAR) value.
     *
     * @param ulRBARValue RBAR value for the MPU region.
     *
     * @return uint32_t Access permissions.
     */
    ಸ್ಥಿರ uint32_t prvGetRegionAccessPermissions( uint32_t ulRBARValue ) PRIVILEGED_FUNCTION;
#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU == 1 && configUSE_MPU_WRAPPERS_V1 == 0 */

#ಆದರೆ ( configENABLE_MPU == 1 )

    /**
     * @brief Setup the Memory Protection Unit (MPU).
     */
    ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_MPU( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;
#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */

#ಆದರೆ ( configENABLE_FPU == 1 )

    /**
     * @brief Setup the Floating Point Unit (FPU).
     */
    ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_FPU( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;
#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_FPU */

#ಆದರೆ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )

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
    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
        ಸ್ಥಿರ uint32_t prvConfigurePACBTI( ತಳ_Type_t x_Write_Control_ರಿಜಿಸ್ಟರ್ );
    #ಇಲ್ಲದಿದ್ದರೆ /* #if ( configNUMBER_OF_CORES == 1 ) */
        uint32_t vConfigurePACBTI( ತಳ_Type_t x_Write_Control_ರಿಜಿಸ್ಟರ್ );
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configNUMBER_OF_CORES == 1 ) */

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

/**
 * @brief Setup the timer to generate the tick interrupts.
 *
 * The implementation in this file is weak to allow application writers to
 * change the timer used to generate the tick interrupt.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether the current execution context is interrupt.
 *
 * @return pdTRUE if the current execution context is interrupt, pdFALSE
 * otherwise.
 */
ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Inside_ಅಡಚಣೆ( ಶೂನ್ಯ );

/**
 * @brief Yield the processor.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

/**
 * @brief Enter critical section.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

/**
 * @brief Exit from critical section.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

/**
 * @brief SysTick handler.
 */
ಶೂನ್ಯ SysTick_Handler( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

/**
 * @brief C part of SVC handler.
 */
ಪೋರ್ಟ್_DONT_DISCARD ಶೂನ್ಯ v_ಪೋರ್ಟ್_SVCHandler_C( uint32_t * pul_Caller_ರಾಶಿ_ವಿಳಾಸ ) PRIVILEGED_FUNCTION;

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the system call stack so that upon returning from
     * SVC, the system call stack is used.
     *
     * @param pulTaskStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    ಶೂನ್ಯ vSystemCallEnter( uint32_t * pul_Task_ರಾಶಿ,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_ಸಂಖ್ಯೆ ) PRIVILEGED_FUNCTION;

#ಆದರೆ_ಅಂತ್ಯ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    ಶೂನ್ಯ vRequestSystemCallExit( ಶೂನ್ಯ ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#ಆದರೆ_ಅಂತ್ಯ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param pulSystemCallStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     */
    ಶೂನ್ಯ vSystemCallExit( uint32_t * pul_System_Call_ರಾಶಿ,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#ಆದರೆ_ಅಂತ್ಯ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ಆದರೆ ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Task_Privileged( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU == 1 */

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )

    /**
     * @brief Platform/Application-defined function that wakes up the secondary cores.
     *
     * @return pdTRUE if the secondary cores were successfully woken up.
     *         pdFALSE otherwise.
     */
    ಬಾಹ್ಯ ತಳ_Type_t configWAKE_SECONDARY_CORES( ಶೂನ್ಯ );

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configNUMBER_OF_CORES > 1 ) */

/**
 * @brief Configures interrupt priorities.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Configure_ಅಡಚಣೆ_Priorities( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;
/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief This variable is set to pdTRUE when the scheduler is started.
     */
    PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ ತಳ_Type_t xSchedulerRunning = pdFALSE;

#ಆದರೆ_ಅಂತ್ಯ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/**
 * @brief Each task maintains its own interrupt status in the critical nesting
 * variable.
 */
#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
    PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ ಅಸ್ಥಿರ uint32_t ulCriticalNesting = 0UL;
#ಇಲ್ಲದಿದ್ದರೆ /* #if ( configNUMBER_OF_CORES == 1 ) */
    PRIVILEGED_ದತ್ತಾಂಶ ಅಸ್ಥಿರ uint32_t ulCriticalNestings[ config_ಸಂಖ್ಯೆ_ದ_CORES ] = { 0 };
    /* Flags to check if the secondary cores are ready. */
    PRIVILEGED_ದತ್ತಾಂಶ ಅಸ್ಥಿರ uint8_t ucSecondaryCoresReadyFlags[ config_ಸಂಖ್ಯೆ_ದ_CORES - 1 ] = { 0 };
    /* Flag to indicate that the primary core has completed its initialisation. */
    PRIVILEGED_ದತ್ತಾಂಶ ಅಸ್ಥಿರ uint8_t uc_Primary_Core_Init_ಮುಗಿದ_Flag = 0;
 #ಆದರೆ_ಅಂತ್ಯ /* #if ( configNUMBER_OF_CORES == 1 ) */

#ಆದರೆ ( configENABLE_TRUSTZONE == 1 )

    /**
     * @brief Saved as part of the task context to indicate which context the
     * task is using on the secure side.
     */
    PRIVILEGED_ದತ್ತಾಂಶ ಪೋರ್ಟ್_DONT_DISCARD ಅಸ್ಥಿರ SecureContextHandle_t xSecureContext = ಪೋರ್ಟ್_NO_SECURE_CONTEXT;
#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_TRUSTZONE */

/**
 * @brief Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#ಆದರೆ ( ( configASSERT_DEFINED == 1 ) && ( ಪೋರ್ಟ್_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) )

    ಸ್ಥಿರ uint8_t uc_Max_Sys_Call_ಆದ್ಯತೆ = 0;
    ಸ್ಥಿರ uint32_t ulMaxPRIGROUPValue = 0;
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಸ್ಥಿರ uint8_t * ಸ್ಥಿರಾಂಕ pc_ಅಡಚಣೆ_ಆದ್ಯತೆ_Registers = ( ಸ್ಥಿರಾಂಕ ಅಸ್ಥಿರ uint8_t * ) ಪೋರ್ಟ್_NVIC_IP_REGISTERS_ಸ್ಥಾನಾಂತರ_16;

#ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */

#ಆದರೆ ( configUSE_TICKLESS_IDLE == 1 )

    /**
     * @brief The number of SysTick increments that make up one tick period.
     */
    PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ uint32_t ulTimerCountsForOneTick = 0;

    /**
     * @brief The maximum number of tick periods that can be suppressed is
     * limited by the 24 bit resolution of the SysTick timer.
     */
    PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ uint32_t x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks = 0;

    /**
     * @brief Compensate for the CPU cycles that pass while the SysTick is
     * stopped (low power functionality only).
     */
    PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ uint32_t ulStoppedTimerCompensation = 0;
#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) ಶೂನ್ಯ v_ಪೋರ್ಟ್_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ಸಮಯ )
    {
        uint32_t ul_Reload_ಮೌಲ್ಯ, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_ಎಡ;
        TickType_t x_Modifiable_Idle_ಸಮಯ;

        /* Make sure the SysTick reload value does not overflow the counter. */
        ಆದರೆ( x_Expected_Idle_ಸಮಯ > x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_ಸಮಯ = x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm ಅಸ್ಥಿರ ( "cpsid i" ::: "memory" );
        __asm ಅಸ್ಥಿರ ( "dsb" );
        __asm ಅಸ್ಥಿರ ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        ಆದರೆ( e_Task_Confirm_Sleep_ಬಹುಲಕ_ಸ್ಥಿತಿ() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the cpsid instruction
             * above. */
            __asm ಅಸ್ಥಿರ ( "cpsie i" ::: "memory" );
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            /* Stop the SysTick momentarily.  The time the SysTick is stopped for
             * is accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_ಎಡ = ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG;

            ಆದರೆ( ul_Sys_Tick_Decrements_ಎಡ == 0 )
            {
                ul_Sys_Tick_Decrements_ಎಡ = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_ಮೌಲ್ಯ = ul_Sys_Tick_Decrements_ಎಡ + ( ulTimerCountsForOneTick * ( x_Expected_Idle_ಸಮಯ - 1UL ) );

            ಆದರೆ( ( ಪೋರ್ಟ್_NVIC_INT_CTRL_REG & ಪೋರ್ಟ್_NVIC_PEND_SYSTICK_ಗಣ_ಬಿಟ್ ) != 0 )
            {
                ಪೋರ್ಟ್_NVIC_INT_CTRL_REG = ಪೋರ್ಟ್_NVIC_PEND_SYSTICK_CLEAR_ಬಿಟ್;
                ul_Reload_ಮೌಲ್ಯ -= ulTimerCountsForOneTick;
            }

            ಆದರೆ( ul_Reload_ಮೌಲ್ಯ > ulStoppedTimerCompensation )
            {
                ul_Reload_ಮೌಲ್ಯ -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ul_Reload_ಮೌಲ್ಯ;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG = 0UL;

            /* Restart SysTick. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG |= ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            x_Modifiable_Idle_ಸಮಯ = x_Expected_Idle_ಸಮಯ;
            configPRE_SLEEP_PROCESSING( x_Modifiable_Idle_ಸಮಯ );

            ಆದರೆ( x_Modifiable_Idle_ಸಮಯ > 0 )
            {
                __asm ಅಸ್ಥಿರ ( "dsb" ::: "memory" );
                __asm ಅಸ್ಥಿರ ( "wfi" );
                __asm ಅಸ್ಥಿರ ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_ಸಮಯ );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the cpsid instruction above. */
            __asm ಅಸ್ಥಿರ ( "cpsie i" ::: "memory" );
            __asm ಅಸ್ಥಿರ ( "dsb" );
            __asm ಅಸ್ಥಿರ ( "isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm ಅಸ್ಥಿರ ( "cpsid i" ::: "memory" );
            __asm ಅಸ್ಥಿರ ( "dsb" );
            __asm ಅಸ್ಥಿರ ( "isb" );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ );

            /* Determine whether the SysTick has already counted to zero. */
            ಆದರೆ( ( ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG & ಪೋರ್ಟ್_NVIC_SYSTICK_ಎಣಿಕೆ_FLAG_ಬಿಟ್ ) != 0 )
            {
                uint32_t ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_ಮೌಲ್ಯ - ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                ಆದರೆ( ( ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ <= ulStoppedTimerCompensation ) || ( ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ = ( ulTimerCountsForOneTick - 1UL );
                }

                ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = x_Expected_Idle_ಸಮಯ - 1UL;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_ಎಡ = ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG;
                #ಆದರೆ ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG != ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    ಆದರೆ( ul_Sys_Tick_Decrements_ಎಡ == 0 )
                    {
                        ul_Sys_Tick_Decrements_ಎಡ = ul_Reload_ಮೌಲ್ಯ;
                    }
                }
                #ಆದರೆ_ಅಂತ್ಯ /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_ಸಮಯ * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_ಎಡ;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG = 0UL;
            ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್;
            #ಆದರೆ ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG == ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ )
            {
                ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ulTimerCountsForOneTick - 1UL;
            }
            #ಇಲ್ಲದಿದ್ದರೆ
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್;

                ಆದರೆ( ( ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG & ಪೋರ್ಟ್_NVIC_SYSTICK_ಎಣಿಕೆ_FLAG_ಬಿಟ್ ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG = 0;
                }

                ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ulTimerCountsForOneTick - 1UL;
                ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್;
            }
            #ಆದರೆ_ಅಂತ್ಯ /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            v_Task_ಹೆಜ್ಜೆ_Tick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __asm ಅಸ್ಥಿರ ( "cpsie i" ::: "memory" );
        }
    }

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

__attribute__( ( weak ) ) ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
{
    /* Calculate the constants required to configure the tick interrupt. */
    #ಆದರೆ ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_ದರ_HZ );
        x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks = ಪೋರ್ಟ್_MAX_24_ಬಿಟ್_ಸಂಖ್ಯೆ / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = ಪೋರ್ಟ್_MISSED_COUNTS_ಗುಣಕ / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */

    /* Stop and reset SysTick.
     *
     * QEMU versions older than 7.0.0 contain a bug which causes an error if we
     * enable SysTick without first selecting a valid clock source. We trigger
     * the bug if we change clock sources from a clock with a zero clock period
     * to one with a nonzero clock period and enable Systick at the same time.
     * So we configure the CLKSOURCE bit here, prior to setting the ENABLE bit.
     * This workaround avoids the bug in QEMU versions older than 7.0.0. */
    ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG;
    ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_ದರ_HZ ) - 1UL;
    ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ )
{
    ಅಸ್ಥಿರ uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
        configASSERT( ulCriticalNesting == ~0UL );
    #ಇಲ್ಲದಿದ್ದರೆ /* #if ( configNUMBER_OF_CORES == 1 ) */
        configASSERT( ulCriticalNestings[ ಪೋರ್ಟ್_GET_CORE_ID() ] == ~0UL );
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configNUMBER_OF_CORES == 1 ) */
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();

    ಆಗ( ulDummy == 0 )
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

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ಸ್ಥಿರ uint32_t prvGetRegionAccessPermissions( uint32_t ulRBARValue ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ulAccessPermissions = 0;

        ಆದರೆ( ( ulRBARValue & ಪೋರ್ಟ್_MPU_RBAR_ACCESS_PERMISSIONS_ಮುಖವಾಡ ) == ಪೋರ್ಟ್_MPU_REGION_READ_ONLY )
        {
            ulAccessPermissions = tskMPU_READ_PERMISSION;
        }

        ಆದರೆ( ( ulRBARValue & ಪೋರ್ಟ್_MPU_RBAR_ACCESS_PERMISSIONS_ಮುಖವಾಡ ) == ಪೋರ್ಟ್_MPU_REGION_READ_WRITE )
        {
            ulAccessPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
        }

        ಹಿಂತಿರುಗಿ ulAccessPermissions;
    }

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU == 1 && configUSE_MPU_WRAPPERS_V1 == 0 */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configENABLE_MPU == 1 )

    ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_MPU( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
    {
        #ಆದರೆ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t * __privileged_functions_start__;
            ಬಾಹ್ಯ uint32_t * __privileged_functions_end__;
            ಬಾಹ್ಯ uint32_t * __syscalls_flash_start__;
            ಬಾಹ್ಯ uint32_t * __syscalls_flash_end__;
            ಬಾಹ್ಯ uint32_t * __unprivileged_flash_start__;
            ಬಾಹ್ಯ uint32_t * __unprivileged_flash_end__;
            ಬಾಹ್ಯ uint32_t * __privileged_sram_start__;
            ಬಾಹ್ಯ uint32_t * __privileged_sram_end__;
        #ಇಲ್ಲದಿದ್ದರೆ /* if defined( __ARMCC_VERSION ) */
            /* Declaration when these variable are exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t __privileged_functions_start__[];
            ಬಾಹ್ಯ uint32_t __privileged_functions_end__[];
            ಬಾಹ್ಯ uint32_t __syscalls_flash_start__[];
            ಬಾಹ್ಯ uint32_t __syscalls_flash_end__[];
            ಬಾಹ್ಯ uint32_t __unprivileged_flash_start__[];
            ಬಾಹ್ಯ uint32_t __unprivileged_flash_end__[];
            ಬಾಹ್ಯ uint32_t __privileged_sram_start__[];
            ಬಾಹ್ಯ uint32_t __privileged_sram_end__[];
        #ಆದರೆ_ಅಂತ್ಯ /* defined( __ARMCC_VERSION ) */

        /* The only permitted number of regions are 8 or 16. */
        configASSERT( ( config_ಒಟ್ಟು_MPU_REGIONS == 8 ) || ( config_ಒಟ್ಟು_MPU_REGIONS == 16 ) );

        /* MAIR0 - Index 0. */
        ಪೋರ್ಟ್_MPU_MAIR0_REG |= ( ( ಪೋರ್ಟ್_MPU_ಸಾಮಾನ್ಯ_ಸ್ಮರಣೆ_BUFFERABLE_CACHEABLE << ಪೋರ್ಟ್_MPU_MAIR_ATTR0_POS ) & ಪೋರ್ಟ್_MPU_MAIR_ATTR0_ಮುಖವಾಡ );
        /* MAIR0 - Index 1. */
        ಪೋರ್ಟ್_MPU_MAIR0_REG |= ( ( ಪೋರ್ಟ್_MPU_DEVICE_ಸ್ಮರಣೆ_n_Gn_RE << ಪೋರ್ಟ್_MPU_MAIR_ATTR1_POS ) & ಪೋರ್ಟ್_MPU_MAIR_ATTR1_ಮುಖವಾಡ );

        /* Setup privileged flash as Read Only so that privileged tasks can
         * read it but not modify. */
        ಪೋರ್ಟ್_MPU_RNR_REG = ಪೋರ್ಟ್_PRIVILEGED_FLASH_REGION;
        ಪೋರ್ಟ್_MPU_RBAR_REG = ( ( ( uint32_t ) __privileged_functions_start__ ) & ಪೋರ್ಟ್_MPU_RBAR_ವಿಳಾಸ_ಮುಖವಾಡ ) |
                           ( ಪೋರ್ಟ್_MPU_REGION_NON_SHAREABLE ) |
                           ( ಪೋರ್ಟ್_MPU_REGION_PRIVILEGED_READ_ONLY );
        ಪೋರ್ಟ್_MPU_RLAR_REG = ( ( ( uint32_t ) __privileged_functions_end__ ) & ಪೋರ್ಟ್_MPU_RLAR_ವಿಳಾಸ_ಮುಖವಾಡ ) |
                           ( ಪೋರ್ಟ್_MPU_RLAR_ATTR_INDEX0 ) |
                           ( ಪೋರ್ಟ್_MPU_RLAR_REGION_ENABLE );

        /* Setup unprivileged flash as Read Only by both privileged and
         * unprivileged tasks. All tasks can read it but no-one can modify. */
        ಪೋರ್ಟ್_MPU_RNR_REG = ಪೋರ್ಟ್_UNPRIVILEGED_FLASH_REGION;
        ಪೋರ್ಟ್_MPU_RBAR_REG = ( ( ( uint32_t ) __unprivileged_flash_start__ ) & ಪೋರ್ಟ್_MPU_RBAR_ವಿಳಾಸ_ಮುಖವಾಡ ) |
                           ( ಪೋರ್ಟ್_MPU_REGION_NON_SHAREABLE ) |
                           ( ಪೋರ್ಟ್_MPU_REGION_READ_ONLY );
        ಪೋರ್ಟ್_MPU_RLAR_REG = ( ( ( uint32_t ) __unprivileged_flash_end__ ) & ಪೋರ್ಟ್_MPU_RLAR_ವಿಳಾಸ_ಮುಖವಾಡ ) |
                           ( ಪೋರ್ಟ್_MPU_RLAR_ATTR_INDEX0 ) |
                           ( ಪೋರ್ಟ್_MPU_RLAR_REGION_ENABLE );

        /* Setup unprivileged syscalls flash as Read Only by both privileged
         * and unprivileged tasks. All tasks can read it but no-one can modify. */
        ಪೋರ್ಟ್_MPU_RNR_REG = ಪೋರ್ಟ್_UNPRIVILEGED_SYSCALLS_REGION;
        ಪೋರ್ಟ್_MPU_RBAR_REG = ( ( ( uint32_t ) __syscalls_flash_start__ ) & ಪೋರ್ಟ್_MPU_RBAR_ವಿಳಾಸ_ಮುಖವಾಡ ) |
                           ( ಪೋರ್ಟ್_MPU_REGION_NON_SHAREABLE ) |
                           ( ಪೋರ್ಟ್_MPU_REGION_READ_ONLY );
        ಪೋರ್ಟ್_MPU_RLAR_REG = ( ( ( uint32_t ) __syscalls_flash_end__ ) & ಪೋರ್ಟ್_MPU_RLAR_ವಿಳಾಸ_ಮುಖವಾಡ ) |
                           ( ಪೋರ್ಟ್_MPU_RLAR_ATTR_INDEX0 ) |
                           ( ಪೋರ್ಟ್_MPU_RLAR_REGION_ENABLE );

        /* Setup RAM containing kernel data for privileged access only. */
        ಪೋರ್ಟ್_MPU_RNR_REG = ಪೋರ್ಟ್_PRIVILEGED_RAM_REGION;
        ಪೋರ್ಟ್_MPU_RBAR_REG = ( ( ( uint32_t ) __privileged_sram_start__ ) & ಪೋರ್ಟ್_MPU_RBAR_ವಿಳಾಸ_ಮುಖವಾಡ ) |
                           ( ಪೋರ್ಟ್_MPU_REGION_NON_SHAREABLE ) |
                           ( ಪೋರ್ಟ್_MPU_REGION_PRIVILEGED_READ_WRITE ) |
                           ( ಪೋರ್ಟ್_MPU_REGION_EXECUTE_NEVER );
        ಪೋರ್ಟ್_MPU_RLAR_REG = ( ( ( uint32_t ) __privileged_sram_end__ ) & ಪೋರ್ಟ್_MPU_RLAR_ವಿಳಾಸ_ಮುಖವಾಡ ) |
                           ( ಪೋರ್ಟ್_MPU_RLAR_ATTR_INDEX0 ) |
                           ( ಪೋರ್ಟ್_MPU_RLAR_REGION_ENABLE );

        /* Enable mem fault. */
        ಪೋರ್ಟ್_SCB_SYS_HANDLER_CTRL_STATE_REG |= ಪೋರ್ಟ್_SCB_MEM_FAULT_ENABLE_ಬಿಟ್;

        /* Enable MPU with privileged background access i.e. unmapped
         * regions have privileged access. */
        ಪೋರ್ಟ್_MPU_CTRL_REG |= ( ಪೋರ್ಟ್_MPU_PRIV_BACKGROUND_ENABLE_ಬಿಟ್ | ಪೋರ್ಟ್_MPU_ENABLE_ಬಿಟ್ );
    }

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configENABLE_FPU == 1 )

    ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_FPU( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
    {
        #ಆದರೆ ( configENABLE_TRUSTZONE == 1 )
        {
            /* Enable non-secure access to the FPU. */
            SecureInit_EnableNSFPUAccess();
        }
        #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_TRUSTZONE */

        /* CP10 = 11 ==> Full access to FPU i.e. both privileged and
         * unprivileged code should be able to access FPU. CP11 should be
         * programmed to the same value as CP10. */
        *( ಪೋರ್ಟ್_CPACR ) |= ( ( ಪೋರ್ಟ್_CPACR_CP10_ಮೌಲ್ಯ << ಪೋರ್ಟ್_CPACR_CP10_POS ) |
                            ( ಪೋರ್ಟ್_CPACR_CP11_ಮೌಲ್ಯ << ಪೋರ್ಟ್_CPACR_CP11_POS )
                            );

        /* ASPEN = 1 ==> Hardware should automatically preserve floating point
         * context on exception entry and restore on exception return.
         * LSPEN = 1 ==> Enable lazy context save of FP state. */
        *( ಪೋರ್ಟ್_FPCCR ) |= ( ಪೋರ್ಟ್_FPCCR_ASPEN_ಮುಖವಾಡ | ಪೋರ್ಟ್_FPCCR_LSPEN_ಮುಖವಾಡ );
    }

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_FPU */
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
{
    /* Set a PendSV to request a context switch. */
    ಪೋರ್ಟ್_NVIC_INT_CTRL_REG = ಪೋರ್ಟ್_NVIC_PENDSVSET_ಬಿಟ್;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm ಅಸ್ಥಿರ ( "dsb" ::: "memory" );
    __asm ಅಸ್ಥಿರ ( "isb" );
}
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
    {
        ಪೋರ್ಟ್_DISABLE_INTERRUPTS();
        ulCriticalNesting++;
        /* Barriers are normally not required but do ensure the code is
        * completely within the specified behaviour for the architecture. */
        __asm ಅಸ್ಥಿರ ( "dsb" ::: "memory" );
        __asm ಅಸ್ಥಿರ ( "isb" );
    }
    /*-----------------------------------------------------------*/

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( ulCriticalNesting );
        ulCriticalNesting--;

        ಆದರೆ( ulCriticalNesting == 0 )
        {
            ಪೋರ್ಟ್_ENABLE_INTERRUPTS();
        }
    }
#ಆದರೆ_ಅಂತ್ಯ /* configNUMBER_OF_CORES == 1 */
/*-----------------------------------------------------------*/

ಶೂನ್ಯ SysTick_Handler( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
{
    uint32_t ul_ಹಿಂದಿನ_ಮುಖವಾಡ;

    ul_ಹಿಂದಿನ_ಮುಖವಾಡ = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();
    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )
        UBaseType_t ux_Saved_ಅಡಚಣೆ_ಸ್ಥಿತಿ = ಪೋರ್ಟ್_ENTER_CRITICAL_FROM_ISR();
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configNUMBER_OF_CORES > 1 ) */

    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        ಆದರೆ( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_ಗಮ್ಯ_SCHEDULER();
            /* Pend a context switch. */
            ಪೋರ್ಟ್_NVIC_INT_CTRL_REG = ಪೋರ್ಟ್_NVIC_PENDSVSET_ಬಿಟ್;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            traceISR_EXIT();
        }
    }
    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )
        ಪೋರ್ಟ್_EXIT_CRITICAL_FROM_ISR( ux_Saved_ಅಡಚಣೆ_ಸ್ಥಿತಿ );
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configNUMBER_OF_CORES > 1 ) */

    ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( ul_ಹಿಂದಿನ_ಮುಖವಾಡ );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_SVCHandler_C( uint32_t * pul_Caller_ರಾಶಿ_ವಿಳಾಸ ) /* PRIVILEGED_FUNCTION portDONT_DISCARD */
{
    #ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )
        #ಆದರೆ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t * __syscalls_flash_start__;
            ಬಾಹ್ಯ uint32_t * __syscalls_flash_end__;
        #ಇಲ್ಲದಿದ್ದರೆ
            /* Declaration when these variable are exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t __syscalls_flash_start__[];
            ಬಾಹ್ಯ uint32_t __syscalls_flash_end__[];
        #ಆದರೆ_ಅಂತ್ಯ /* defined( __ARMCC_VERSION ) */
    #ಆದರೆ_ಅಂತ್ಯ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #ಆದರೆ ( configENABLE_MPU == 1 )
        #ಆದರೆ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t * __privileged_functions_start__;
            ಬಾಹ್ಯ uint32_t * __privileged_functions_end__;
        #ಇಲ್ಲದಿದ್ದರೆ
            /* Declaration when these variable are exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t __privileged_functions_start__[];
            ಬಾಹ್ಯ uint32_t __privileged_functions_end__[];
        #ಆದರೆ_ಅಂತ್ಯ /* defined( __ARMCC_VERSION ) */
    #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU == 1 */

    uint32_t ulPC;

    #ಆದರೆ ( configENABLE_TRUSTZONE == 1 )
        uint32_t ulR0, ulR1;
        ಬಾಹ್ಯ TaskHandle_t pxCurrentTCB;
        #ಆದರೆ ( configENABLE_MPU == 1 )
            uint32_t ulControl, ulIsTaskPrivileged;
        #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */
    #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_TRUSTZONE */
    uint8_t ucSVCNumber;

    /* Register are stored on the stack in the following order - R0, R1, R2, R3,
     * R12, LR, PC, xPSR. */
    ulPC = pul_Caller_ರಾಶಿ_ವಿಳಾಸ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    ಆಯ್ಕೆ( ucSVCNumber )
    {
    #ಆದರೆ ( configENABLE_TRUSTZONE == 1 )
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_SVC_ALLOCATE_SECURE_CONTEXT:

            /* R0 contains the stack size passed as parameter to the
             * vPortAllocateSecureContext function. */
            ulR0 = pul_Caller_ರಾಶಿ_ವಿಳಾಸ[ 0 ];

            #ಆದರೆ ( configENABLE_MPU == 1 )
            {
                /* Read the CONTROL register value. */
                __asm ಅಸ್ಥಿರ ( "mrs %0, control"  : "=r" ( ulControl ) );

                /* The task that raised the SVC is privileged if Bit[0]
                 * in the CONTROL register is 0. */
                ulIsTaskPrivileged = ( ( ulControl & ಪೋರ್ಟ್_CONTROL_PRIVILEGED_ಮುಖವಾಡ ) == 0 );

                /* Allocate and load a context for the secure task. */
                xSecureContext = SecureContext_AllocateContext( ulR0, ulIsTaskPrivileged, pxCurrentTCB );
            }
            #ಇಲ್ಲದಿದ್ದರೆ /* if ( configENABLE_MPU == 1 ) */
            {
                /* Allocate and load a context for the secure task. */
                xSecureContext = SecureContext_AllocateContext( ulR0, pxCurrentTCB );
            }
            #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */

            configASSERT( xSecureContext != securecontextINVALID_CONTEXT_ID );
            Secure_Context_ತುಂಬು_Context( xSecureContext, pxCurrentTCB );
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ ಪೋರ್ಟ್_SVC_FREE_SECURE_CONTEXT:
            #ಆದರೆ ( configENABLE_MPU == 1 )
            ಆದರೆ( ( ulPC >= ( uint32_t ) __privileged_functions_start__ ) &&
                ( ulPC <= ( uint32_t ) __privileged_functions_end__ ) )
            {
            #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */
                /* R0 contains TCB being freed and R1 contains the secure
                 * context handle to be freed. */
                ulR0 = pul_Caller_ರಾಶಿ_ವಿಳಾಸ[ 0 ];
                ulR1 = pul_Caller_ರಾಶಿ_ವಿಳಾಸ[ 1 ];

                /* Free the secure context. */
                SecureContext_FreeContext( ( SecureContextHandle_t ) ulR1, ( ಶೂನ್ಯ * ) ulR0 );
            #ಆದರೆ ( configENABLE_MPU == 1 )
            }
            #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */
            ನಿಲ್ಲಿಸು;
    #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_TRUSTZONE */

        ಸ್ಥಿತಿ ಪೋರ್ಟ್_SVC_ಆರಂಭ_SCHEDULER:
            #ಆದರೆ ( configENABLE_MPU == 1 )
            ಆದರೆ( ( ulPC >= ( uint32_t ) __privileged_functions_start__ ) &&
                ( ulPC <= ( uint32_t ) __privileged_functions_end__ ) )
            {
            #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */
                #ಆದರೆ ( configENABLE_TRUSTZONE == 1 )
                {
                    /* De-prioritize the non-secure exceptions so that the
                     * non-secure pendSV runs at the lowest priority. */
                    SecureInit_DePrioritizeNSExceptions();

                    /* Initialize the secure context management system. */
                    SecureContext_Init();
                }
                #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_TRUSTZONE */

                #ಆದರೆ ( configENABLE_FPU == 1 )
                {
                    /* Setup the Floating Point Unit (FPU). */
                    prv_ಸಿದ್ಧತೆ_FPU();
                }
                #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_FPU */

                /* Setup the context of the first task so that the first task starts
                 * executing. */
                v_Restore_Context_ದ_ಮೊದಲ_Task();
            #ಆದರೆ ( configENABLE_MPU == 1 )
            }
            #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */
            ನಿಲ್ಲಿಸು;

    #ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_SVC_RAISE_PRIVILEGE:

            /* Only raise the privilege, if the svc was raised from any of
             * the system calls. */
            ಆದರೆ( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
            {
                vRaisePrivilege();
            }
            ನಿಲ್ಲಿಸು;
    #ಆದರೆ_ಅಂತ್ಯ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #ಆದರೆ ( configENABLE_MPU == 1 )
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_SVC_YIELD:
            v_ಪೋರ್ಟ್_Yield();
            ನಿಲ್ಲಿಸು;
    #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU == 1 */

        ಪೂರ್ವನಿಯೋಜಿತ:
            /* Incorrect SVC call. */
            configASSERT( pdFALSE );
    }
}
/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ಶೂನ್ಯ vSystemCallEnter( uint32_t * pul_Task_ರಾಶಿ,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_ಸಂಖ್ಯೆ ) /* PRIVILEGED_FUNCTION */
    {
        ಬಾಹ್ಯ TaskHandle_t pxCurrentTCB;
        ಬಾಹ್ಯ UBaseType_t uxSystemCallImplementations[ ಅಂಕೆ_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_ರಾಶಿ;
        uint32_t ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ, ulSystemCallLocation, i;

        #ಆದರೆ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t * __syscalls_flash_start__;
            ಬಾಹ್ಯ uint32_t * __syscalls_flash_end__;
        #ಇಲ್ಲದಿದ್ದರೆ
            /* Declaration when these variable are exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t __syscalls_flash_start__[];
            ಬಾಹ್ಯ uint32_t __syscalls_flash_end__[];
        #ಆದರೆ_ಅಂತ್ಯ /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PC ];
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
        ಆದರೆ( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ == ಖಾಲಿ ) &&
            ( uxSystemCallImplementations[ uc_System_Call_ಸಂಖ್ಯೆ ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_ರಾಶಿ = pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_System_Call_ರಾಶಿ;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            #ಆದರೆ ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )
            {
                ಆದರೆ( ( ulLR & ಪೋರ್ಟ್_EXC_RETURN_ರಾಶಿ_ಚೌಕಟ್ಟು_TYPE_ಮುಖವಾಡ ) == 0UL )
                {
                    /* Extended frame i.e. FPU in use. */
                    ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ = 26;
                    __asm ಅಸ್ಥಿರ (
                        " vpush {s0}         \n" /* Trigger lazy stacking. */
                        " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                        ::: "memory"
                        );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    /* Standard frame i.e. FPU not in use. */
                    ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ = 8;
                }
            }
            #ಇಲ್ಲದಿದ್ದರೆ /* if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */
            {
                ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ = 8;
            }
            #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_FPU || configENABLE_MVE */

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_ರಾಶಿ = pul_System_Call_ರಾಶಿ - ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ;

            /* Copy the stack frame. */
            ಗಾಗಿ( i = 0; i < ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ; i++ )
            {
                pul_System_Call_ರಾಶಿ[ i ] = pul_Task_ರಾಶಿ[ i ];
            }

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_ರಾಶಿ_Info.ul_Link_ರಿಜಿಸ್ಟರ್_At_System_Call_ನಮೂದು = pul_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_LR ];

            /* Store the value of the PSPLIM register before the SVC was raised.
             * We need to restore it when we exit from the system call. */
            #ಆದರೆ ( ಪೋರ್ಟ್_USE_PSPLIM_ರಿಜಿಸ್ಟರ್ == 1 )
            {
                __asm ಅಸ್ಥಿರ ( "mrs %0, psplim" : "=r" ( pxMpuSettings->x_System_Call_ರಾಶಿ_Info.ul_ರಾಶಿ_ಎಲ್ಲೆ_ರಿಜಿಸ್ಟರ್_At_System_Call_ನಮೂದು ) );
            }
            #ಆದರೆ_ಅಂತ್ಯ

            /* Use the pulSystemCallStack in thread mode. */
            __asm ಅಸ್ಥಿರ ( "msr psp, %0" : : "r" ( pul_System_Call_ರಾಶಿ ) );
            #ಆದರೆ ( ಪೋರ್ಟ್_USE_PSPLIM_ರಿಜಿಸ್ಟರ್ == 1 )
            {
                __asm ಅಸ್ಥಿರ ( "msr psplim, %0" : : "r" ( pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_System_Call_ರಾಶಿ_ಎಲ್ಲೆ ) );
            }
            #ಆದರೆ_ಅಂತ್ಯ

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PC ] = uxSystemCallImplementations[ uc_System_Call_ಸಂಖ್ಯೆ ];

            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ = pul_Task_ರಾಶಿ + ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            ಆದರೆ( ( pul_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PSR ] & ಪೋರ್ಟ್_PSR_ರಾಶಿ_PADDING_ಮುಖವಾಡ ) == ಪೋರ್ಟ್_PSR_ರಾಶಿ_PADDING_ಮುಖವಾಡ )
            {
                pxMpuSettings->ulTaskFlags |= ಪೋರ್ಟ್_ರಾಶಿ_ಚೌಕಟ್ಟು_HAS_PADDING_FLAG;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                pxMpuSettings->ulTaskFlags &= ( ~ಪೋರ್ಟ್_ರಾಶಿ_ಚೌಕಟ್ಟು_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PSR ] &= ( ~ಪೋರ್ಟ್_PSR_ರಾಶಿ_PADDING_ಮುಖವಾಡ );

            /* Raise the privilege for the duration of the system call. */
            __asm ಅಸ್ಥಿರ (
                " mrs r0, control     \n" /* Obtain current control value. */
                " movs r1, #1         \n" /* r1 = 1. */
                " bics r0, r1         \n" /* Clear nPRIV bit. */
                " msr control, r0     \n" /* Write back new control value. */
                ::: "r0", "r1", "memory"
                );
        }
    }

#ಆದರೆ_ಅಂತ್ಯ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ಶೂನ್ಯ vRequestSystemCallExit( ಶೂನ್ಯ ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm ಅಸ್ಥಿರ ( "svc %0 \n" ::"i" ( ಪೋರ್ಟ್_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#ಆದರೆ_ಅಂತ್ಯ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ಶೂನ್ಯ vSystemCallExit( uint32_t * pul_System_Call_ರಾಶಿ,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        ಬಾಹ್ಯ TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_ರಾಶಿ;
        uint32_t ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ, ulSystemCallLocation, i;

        #ಆದರೆ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t * __privileged_functions_start__;
            ಬಾಹ್ಯ uint32_t * __privileged_functions_end__;
        #ಇಲ್ಲದಿದ್ದರೆ
            /* Declaration when these variable are exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t __privileged_functions_start__[];
            ಬಾಹ್ಯ uint32_t __privileged_functions_end__[];
        #ಆದರೆ_ಅಂತ್ಯ /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PC ];
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
        ಆದರೆ( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ != ಖಾಲಿ ) )
        {
            pul_Task_ರಾಶಿ = pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            #ಆದರೆ ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )
            {
                ಆದರೆ( ( ulLR & ಪೋರ್ಟ್_EXC_RETURN_ರಾಶಿ_ಚೌಕಟ್ಟು_TYPE_ಮುಖವಾಡ ) == 0UL )
                {
                    /* Extended frame i.e. FPU in use. */
                    ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ = 26;
                    __asm ಅಸ್ಥಿರ (
                        " vpush {s0}         \n" /* Trigger lazy stacking. */
                        " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                        ::: "memory"
                        );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    /* Standard frame i.e. FPU not in use. */
                    ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ = 8;
                }
            }
            #ಇಲ್ಲದಿದ್ದರೆ /* if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */
            {
                ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ = 8;
            }
            #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_FPU || configENABLE_MVE */

            /* Make space on the task stack for the stack frame. */
            pul_Task_ರಾಶಿ = pul_Task_ರಾಶಿ - ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ;

            /* Copy the stack frame. */
            ಗಾಗಿ( i = 0; i < ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ; i++ )
            {
                pul_Task_ರಾಶಿ[ i ] = pul_System_Call_ರಾಶಿ[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm ಅಸ್ಥಿರ ( "msr psp, %0" : : "r" ( pul_Task_ರಾಶಿ ) );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PC ] = pxMpuSettings->x_System_Call_ರಾಶಿ_Info.ul_Link_ರಿಜಿಸ್ಟರ್_At_System_Call_ನಮೂದು;
            /* Ensure that LR has a valid value.*/
            pul_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_LR ] = pxMpuSettings->x_System_Call_ರಾಶಿ_Info.ul_Link_ರಿಜಿಸ್ಟರ್_At_System_Call_ನಮೂದು;

            /* Restore the PSPLIM register to what it was at the time of
             * system call entry. */
            #ಆದರೆ ( ಪೋರ್ಟ್_USE_PSPLIM_ರಿಜಿಸ್ಟರ್ == 1 )
            {
                __asm ಅಸ್ಥಿರ ( "msr psplim, %0" : : "r" ( pxMpuSettings->x_System_Call_ರಾಶಿ_Info.ul_ರಾಶಿ_ಎಲ್ಲೆ_ರಿಜಿಸ್ಟರ್_At_System_Call_ನಮೂದು ) );
            }
            #ಆದರೆ_ಅಂತ್ಯ

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            ಆದರೆ( ( pxMpuSettings->ulTaskFlags & ಪೋರ್ಟ್_ರಾಶಿ_ಚೌಕಟ್ಟು_HAS_PADDING_FLAG ) == ಪೋರ್ಟ್_ರಾಶಿ_ಚೌಕಟ್ಟು_HAS_PADDING_FLAG )
            {
                pul_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PSR ] |= ಪೋರ್ಟ್_PSR_ರಾಶಿ_PADDING_ಮುಖವಾಡ;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                pul_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PSR ] &= ( ~ಪೋರ್ಟ್_PSR_ರಾಶಿ_PADDING_ಮುಖವಾಡ );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ = ಖಾಲಿ;

            /* Drop the privilege before returning to the thread mode. */
            __asm ಅಸ್ಥಿರ (
                " mrs r0, control     \n" /* Obtain current control value. */
                " movs r1, #1         \n" /* r1 = 1. */
                " orrs r0, r1         \n" /* Set nPRIV bit. */
                " msr control, r0     \n" /* Write back new control value. */
                ::: "r0", "r1", "memory"
                );
        }
    }

#ಆದರೆ_ಅಂತ್ಯ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configENABLE_MPU == 1 )

    ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Task_Privileged( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
    {
        ತಳ_Type_t xTaskIsPrivileged = pdFALSE;
        ಸ್ಥಿರಾಂಕ xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ಖಾಲಿ ); /* Calling task's MPU settings. */

        ಆದರೆ( ( xTaskMpuSettings->ulTaskFlags & ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG ) == ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        ಹಿಂತಿರುಗಿ xTaskIsPrivileged;
    }

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configENABLE_MPU == 1 )

    ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                         ರಾಶಿ_Type_t * px_ಕೊನೆ_ದ_ರಾಶಿ,
                                         TaskFunction_t px_ಸಂಕೇತ,
                                         ಶೂನ್ಯ * pvParameters,
                                         ತಳ_Type_t x_ಸತತ_Privileged,
                                         xMPU_SETTINGS * xMPUSettings ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_ಸೂಚ್ಯಂಕ = 0;
        uint32_t ulControl = 0x0;

        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = 0x04040404; /* r4. */
        ul_ಸೂಚ್ಯಂಕ++;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = 0x05050505; /* r5. */
        ul_ಸೂಚ್ಯಂಕ++;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = 0x06060606; /* r6. */
        ul_ಸೂಚ್ಯಂಕ++;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = 0x07070707; /* r7. */
        ul_ಸೂಚ್ಯಂಕ++;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = 0x08080808; /* r8. */
        ul_ಸೂಚ್ಯಂಕ++;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = 0x09090909; /* r9. */
        ul_ಸೂಚ್ಯಂಕ++;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = 0x10101010; /* r10. */
        ul_ಸೂಚ್ಯಂಕ++;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = 0x11111111; /* r11. */
        ul_ಸೂಚ್ಯಂಕ++;

        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( uint32_t ) pvParameters; /* r0. */
        ul_ಸೂಚ್ಯಂಕ++;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = 0x01010101; /* r1. */
        ul_ಸೂಚ್ಯಂಕ++;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = 0x02020202; /* r2. */
        ul_ಸೂಚ್ಯಂಕ++;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = 0x03030303; /* r3. */
        ul_ಸೂಚ್ಯಂಕ++;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = 0x12121212; /* r12. */
        ul_ಸೂಚ್ಯಂಕ++;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( uint32_t ) ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ; /* LR. */
        ul_ಸೂಚ್ಯಂಕ++;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( uint32_t ) px_ಸಂಕೇತ; /* PC. */
        ul_ಸೂಚ್ಯಂಕ++;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ಪೋರ್ಟ್_INITIAL_XPSR; /* xPSR. */
        ul_ಸೂಚ್ಯಂಕ++;

        #ಆದರೆ ( configENABLE_TRUSTZONE == 1 )
        {
            xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ಪೋರ್ಟ್_NO_SECURE_CONTEXT; /* xSecureContext. */
            ul_ಸೂಚ್ಯಂಕ++;
        }
        #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_TRUSTZONE */
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( uint32_t ) ( px_ತುದಿ_ದ_ರಾಶಿ - 8 ); /* PSP with the hardware saved stack. */
        ul_ಸೂಚ್ಯಂಕ++;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( uint32_t ) px_ಕೊನೆ_ದ_ರಾಶಿ; /* PSPLIM. */
        ul_ಸೂಚ್ಯಂಕ++;

        #ಆದರೆ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
        {
            /* Check PACBTI security feature configuration before pushing the
             * CONTROL register's value on task's TCB. */
            #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
                ulControl = prvConfigurePACBTI( pdFALSE );
            #ಇಲ್ಲದಿದ್ದರೆ /* configNUMBER_OF_CORES > 1 */
                ulControl = vConfigurePACBTI( pdFALSE );
            #ಆದರೆ_ಅಂತ್ಯ /* configNUMBER_OF_CORES */
        }
        #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

        ಆದರೆ( x_ಸತತ_Privileged == pdTRUE )
        {
            xMPUSettings->ulTaskFlags |= ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG;
            xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ulControl | ( uint32_t ) ಪೋರ್ಟ್_INITIAL_CONTROL_PRIVILEGED ); /* CONTROL. */
            ul_ಸೂಚ್ಯಂಕ++;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            xMPUSettings->ulTaskFlags &= ( ~ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG );
            xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ulControl | ( uint32_t ) ಪೋರ್ಟ್_INITIAL_CONTROL_UNPRIVILEGED ); /* CONTROL. */
            ul_ಸೂಚ್ಯಂಕ++;
        }

        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ಪೋರ್ಟ್_INITIAL_EXC_RETURN; /* LR (EXC_RETURN). */
        ul_ಸೂಚ್ಯಂಕ++;

        #ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )
        {
            /* Ensure that the system call stack is double word aligned. */
            xMPUSettings->x_System_Call_ರಾಶಿ_Info.pul_System_Call_ರಾಶಿ = &( xMPUSettings->x_System_Call_ರಾಶಿ_Info.ul_System_Call_ರಾಶಿ_ಬಫರ್[ config_SYSTEM_CALL_ರಾಶಿ_ಗಾತ್ರ - 1 ] );
            xMPUSettings->x_System_Call_ರಾಶಿ_Info.pul_System_Call_ರಾಶಿ = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_ರಾಶಿ_Info.pul_System_Call_ರಾಶಿ ) &
                                                                                     ( uint32_t ) ( ~( ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ ) ) );

            xMPUSettings->x_System_Call_ರಾಶಿ_Info.pul_System_Call_ರಾಶಿ_ಎಲ್ಲೆ = &( xMPUSettings->x_System_Call_ರಾಶಿ_Info.ul_System_Call_ರಾಶಿ_ಬಫರ್[ 0 ] );
            xMPUSettings->x_System_Call_ರಾಶಿ_Info.pul_System_Call_ರಾಶಿ_ಎಲ್ಲೆ = ( uint32_t * ) ( ( ( uint32_t ) ( xMPUSettings->x_System_Call_ರಾಶಿ_Info.pul_System_Call_ರಾಶಿ_ಎಲ್ಲೆ ) +
                                                                                            ( uint32_t ) ( ಪೋರ್ಟ್_BYTE_ALIGNMENT - 1 ) ) &
                                                                                          ( uint32_t ) ( ~( ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ ) ) );

            /* This is not NULL only for the duration of a system call. */
            xMPUSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ = ಖಾಲಿ;
        }
        #ಆದರೆ_ಅಂತ್ಯ /* configUSE_MPU_WRAPPERS_V1 == 0 */

        #ಆದರೆ ( configENABLE_PAC == 1 )
        {
            uint32_t ul_Task_Pac_ಕೀಲಿ[ 4 ], i;

            v_Application_Generate_Task_Random_Pac_ಕೀಲಿ( &( ul_Task_Pac_ಕೀಲಿ[ 0 ] ) );

            ಗಾಗಿ( i = 0; i < 4; i++ )
            {
                xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ul_Task_Pac_ಕೀಲಿ[ i ];
                ul_ಸೂಚ್ಯಂಕ++;
            }
        }
        #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_PAC */

        ಹಿಂತಿರುಗಿ &( xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] );
    }

#ಇಲ್ಲದಿದ್ದರೆ /* configENABLE_MPU */

    ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                         ರಾಶಿ_Type_t * px_ಕೊನೆ_ದ_ರಾಶಿ,
                                         TaskFunction_t px_ಸಂಕೇತ,
                                         ಶೂನ್ಯ * pvParameters ) /* PRIVILEGED_FUNCTION */
    {
        /* Simulate the stack frame as it would be created by a context switch
         * interrupt. */
        #ಆದರೆ ( ಪೋರ್ಟ್_PRELOAD_REGISTERS == 0 )
        {
            px_ತುದಿ_ದ_ರಾಶಿ--; /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_XPSR; /* xPSR. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ; /* PC. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ; /* LR. */
            px_ತುದಿ_ದ_ರಾಶಿ -= 5; /* R12, R3, R2 and R1. */
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters; /* R0. */
            px_ತುದಿ_ದ_ರಾಶಿ -= 9; /* R11..R4, EXC_RETURN. */
            *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_EXC_RETURN;
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಕೊನೆ_ದ_ರಾಶಿ; /* Slot used to hold this task's PSPLIM value. */

            #ಆದರೆ ( configENABLE_TRUSTZONE == 1 )
            {
                px_ತುದಿ_ದ_ರಾಶಿ--;
                *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_NO_SECURE_CONTEXT; /* Slot used to hold this task's xSecureContext value. */
            }
            #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_TRUSTZONE */
        }
        #ಇಲ್ಲದಿದ್ದರೆ /* portPRELOAD_REGISTERS */
        {
            px_ತುದಿ_ದ_ರಾಶಿ--; /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_XPSR; /* xPSR. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ; /* PC. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ; /* LR. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x12121212UL; /* R12. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x03030303UL; /* R3. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x02020202UL; /* R2. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x01010101UL; /* R1. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters; /* R0. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x11111111UL; /* R11. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x10101010UL; /* R10. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x09090909UL; /* R09. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x08080808UL; /* R08. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x07070707UL; /* R07. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x06060606UL; /* R06. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x05050505UL; /* R05. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x04040404UL; /* R04. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_EXC_RETURN; /* EXC_RETURN. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಕೊನೆ_ದ_ರಾಶಿ; /* Slot used to hold this task's PSPLIM value. */

            #ಆದರೆ ( configENABLE_TRUSTZONE == 1 )
            {
                px_ತುದಿ_ದ_ರಾಶಿ--;
                *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_NO_SECURE_CONTEXT; /* Slot used to hold this task's xSecureContext value. */
            }
            #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_TRUSTZONE */
        }
        #ಆದರೆ_ಅಂತ್ಯ /* portPRELOAD_REGISTERS */

        #ಆದರೆ ( configENABLE_PAC == 1 )
        {
            uint32_t ul_Task_Pac_ಕೀಲಿ[ 4 ], i;

            v_Application_Generate_Task_Random_Pac_ಕೀಲಿ( &( ul_Task_Pac_ಕೀಲಿ[ 0 ] ) );

            ಗಾಗಿ( i = 0; i < 4; i++ )
            {
                px_ತುದಿ_ದ_ರಾಶಿ--;
                *px_ತುದಿ_ದ_ರಾಶಿ = ul_Task_Pac_ಕೀಲಿ[ i ];
            }
        }
        #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_PAC */

        ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
    }

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
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
    #ಆದರೆ ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        ಸ್ಥಿರಾಂಕ ಪೋರ್ಟ್_ISR_t * ಸ್ಥಿರಾಂಕ px_ಸದಿಶ_ಕೋಷ್ಟಕ = ಪೋರ್ಟ್_SCB_VTOR_REG;

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
        configASSERT( px_ಸದಿಶ_ಕೋಷ್ಟಕ[ ಪೋರ್ಟ್_ಸದಿಶ_ಸೂಚ್ಯಂಕ_SVC ] == SVC_Handler );
        configASSERT( px_ಸದಿಶ_ಕೋಷ್ಟಕ[ ಪೋರ್ಟ್_ಸದಿಶ_ಸೂಚ್ಯಂಕ_PENDSV ] == PendSV_Handler );
    }
    #ಆದರೆ_ಅಂತ್ಯ /* configCHECK_HANDLER_INSTALLATION */

    v_ಪೋರ್ಟ್_Configure_ಅಡಚಣೆ_Priorities();

    #ಆದರೆ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
    {
        /* Set the CONTROL register value based on PACBTI security feature
         * configuration before starting the first task. */
        #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
            ( ಶೂನ್ಯ ) prvConfigurePACBTI( pdTRUE );
        #ಇಲ್ಲದಿದ್ದರೆ /* configNUMBER_OF_CORES > 1 */
            ( ಶೂನ್ಯ ) vConfigurePACBTI( pdTRUE );
        #ಆದರೆ_ಅಂತ್ಯ /* configNUMBER_OF_CORES */
    }
    #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */

    #ಆದರೆ ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        prv_ಸಿದ್ಧತೆ_MPU();
    }
    #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */

    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )
        /* Start the timer that generates the tick ISR. Interrupts are disabled
         * here already. */
        v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();
        /* Initialize the critical nesting count for all cores. */
        ಗಾಗಿ ( uint8_t ucCoreID = 0; ucCoreID < config_ಸಂಖ್ಯೆ_ದ_CORES; ucCoreID++ )
        {
            ulCriticalNestings[ ucCoreID ] = 0;
        }
        /* Signal that primary core has done all the necessary initialisations. */
        uc_Primary_Core_Init_ಮುಗಿದ_Flag = 1;
        /* Wake up secondary cores */
        ತಳ_Type_t x_Wake_ಫಲಿತಾಂಶ = configWAKE_SECONDARY_CORES();
        configASSERT( x_Wake_ಫಲಿತಾಂಶ == pdTRUE );

        /* Hold the primary core here until all the secondary cores are ready, this would be achieved only when
         * all elements of ucSecondaryCoresReadyFlags are set.
         */
        ಆಗ( 1 )
        {
            ತಳ_Type_t xAllCoresReady = pdTRUE;
            ಗಾಗಿ( uint8_t ucCoreID = 0; ucCoreID < ( config_ಸಂಖ್ಯೆ_ದ_CORES - 1 ); ucCoreID++ )
            {
                ಆದರೆ( ucSecondaryCoresReadyFlags[ ucCoreID ] != pdTRUE )
                {
                    xAllCoresReady = pdFALSE;
                    ನಿಲ್ಲಿಸು;
                }
                }

            ಆದರೆ ( xAllCoresReady == pdTRUE )
            {
                ನಿಲ್ಲಿಸು;
            }
        }
    #ಇಲ್ಲದಿದ್ದರೆ /* if ( configNUMBER_OF_CORES > 1 ) */
        /* Start the timer that generates the tick ISR. */
        v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();
        /* Initialize the critical nesting count ready for the first task. */
        ulCriticalNesting = 0;
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configNUMBER_OF_CORES > 1 ) */

    #ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )
    {
        xSchedulerRunning = pdTRUE;
    }
    #ಆದರೆ_ಅಂತ್ಯ /* ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

    /* Start the first task. */
    v_ಆರಂಭ_ಮೊದಲ_Task();

    /* Should never get here as the tasks will now be executing. Call the task
     * exit error function to prevent compiler warnings about a static function
     * not being called in the case that the application writer overrides this
     * functionality by defining configTASK_RETURN_ADDRESS. Call
     * vTaskSwitchContext() so link time optimization does not remove the
     * symbol. */
    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )
        vTaskSwitchContext( ಪೋರ್ಟ್_GET_CORE_ID() );
    #ಇಲ್ಲದಿದ್ದರೆ
        vTaskSwitchContext();
    #ಆದರೆ_ಅಂತ್ಯ
    prvTaskExitError();

    /* Should not get here. */
    ಹಿಂತಿರುಗಿ 0;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
        configASSERT( ulCriticalNesting == 1000UL );
    #ಇಲ್ಲದಿದ್ದರೆ /* if ( configNUMBER_OF_CORES == 1 ) */
        configASSERT( ulCriticalNestings[ ಪೋರ್ಟ್_GET_CORE_ID() ] == 1000UL );
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configNUMBER_OF_CORES == 1 ) */
}
/*-----------------------------------------------------------*/

#ಆದರೆ ( configENABLE_MPU == 1 )

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ಸ್ಥಿರಾಂಕ ರಚನೆ x_ಸ್ಮರಣೆ_REGION * ಸ್ಥಿರಾಂಕ xRegions,
                                    ರಾಶಿ_Type_t * px_Bottom_ದ_ರಾಶಿ,
                                    config_ರಾಶಿ_ಆಳ_TYPE ux_ರಾಶಿ_ಆಳ )
    {
        uint32_t ul_Region_ಆರಂಭ_ವಿಳಾಸ, ul_Region_ಕೊನೆ_ವಿಳಾಸ, ul_Region_ಸಂಖ್ಯೆ;
        int32_t l_ಸೂಚ್ಯಂಕ = 0;

        #ಆದರೆ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t * __privileged_sram_start__;
            ಬಾಹ್ಯ uint32_t * __privileged_sram_end__;
        #ಇಲ್ಲದಿದ್ದರೆ
            /* Declaration when these variable are exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t __privileged_sram_start__[];
            ಬಾಹ್ಯ uint32_t __privileged_sram_end__[];
        #ಆದರೆ_ಅಂತ್ಯ /* defined( __ARMCC_VERSION ) */

        /* Setup MAIR0. */
        xMPUSettings->ulMAIR0 = ( ( ಪೋರ್ಟ್_MPU_ಸಾಮಾನ್ಯ_ಸ್ಮರಣೆ_BUFFERABLE_CACHEABLE << ಪೋರ್ಟ್_MPU_MAIR_ATTR0_POS ) & ಪೋರ್ಟ್_MPU_MAIR_ATTR0_ಮುಖವಾಡ );
        xMPUSettings->ulMAIR0 |= ( ( ಪೋರ್ಟ್_MPU_DEVICE_ಸ್ಮರಣೆ_n_Gn_RE << ಪೋರ್ಟ್_MPU_MAIR_ATTR1_POS ) & ಪೋರ್ಟ್_MPU_MAIR_ATTR1_ಮುಖವಾಡ );

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid.  At all other
         * times the stack parameters will not be valid and it is assumed that
         * the stack region has already been configured. */
        ಆದರೆ( ux_ರಾಶಿ_ಆಳ > 0 )
        {
            ul_Region_ಆರಂಭ_ವಿಳಾಸ = ( uint32_t ) px_Bottom_ದ_ರಾಶಿ;
            ul_Region_ಕೊನೆ_ವಿಳಾಸ = ( uint32_t ) px_Bottom_ದ_ರಾಶಿ + ( ux_ರಾಶಿ_ಆಳ * ( config_ರಾಶಿ_ಆಳ_TYPE ) ಗಾತ್ರ( ರಾಶಿ_Type_t ) ) - 1;

            /* If the stack is within the privileged SRAM, do not protect it
             * using a separate MPU region. This is needed because privileged
             * SRAM is already protected using an MPU region and ARMv8-M does
             * not allow overlapping MPU regions. */
            ಆದರೆ( ( ul_Region_ಆರಂಭ_ವಿಳಾಸ >= ( uint32_t ) __privileged_sram_start__ ) &&
                ( ul_Region_ಕೊನೆ_ವಿಳಾಸ <= ( uint32_t ) __privileged_sram_end__ ) )
            {
                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR = 0;
                xMPUSettings->xRegionsSettings[ 0 ].ulRLAR = 0;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                /* Define the region that allows access to the stack. */
                ul_Region_ಆರಂಭ_ವಿಳಾಸ &= ಪೋರ್ಟ್_MPU_RBAR_ವಿಳಾಸ_ಮುಖವಾಡ;
                ul_Region_ಕೊನೆ_ವಿಳಾಸ &= ಪೋರ್ಟ್_MPU_RLAR_ವಿಳಾಸ_ಮುಖವಾಡ;

                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR = ( ul_Region_ಆರಂಭ_ವಿಳಾಸ ) |
                                                             ( ಪೋರ್ಟ್_MPU_REGION_NON_SHAREABLE ) |
                                                             ( ಪೋರ್ಟ್_MPU_REGION_READ_WRITE ) |
                                                             ( ಪೋರ್ಟ್_MPU_REGION_EXECUTE_NEVER );

                xMPUSettings->xRegionsSettings[ 0 ].ulRLAR = ( ul_Region_ಕೊನೆ_ವಿಳಾಸ ) |
                                                             ( ಪೋರ್ಟ್_MPU_RLAR_ATTR_INDEX0 ) |
                                                             ( ಪೋರ್ಟ್_MPU_RLAR_REGION_ENABLE );
            }
        }

        /* User supplied configurable regions. */
        ಗಾಗಿ( ul_Region_ಸಂಖ್ಯೆ = 1; ul_Region_ಸಂಖ್ಯೆ <= ಪೋರ್ಟ್_ಅಂಕೆ_CONFIGURABLE_REGIONS; ul_Region_ಸಂಖ್ಯೆ++ )
        {
            /* If xRegions is NULL i.e. the task has not specified any MPU
             * region, the else part ensures that all the configurable MPU
             * regions are invalidated. */
            ಆದರೆ( ( xRegions != ಖಾಲಿ ) && ( xRegions[ l_ಸೂಚ್ಯಂಕ ].ul_ಉದ್ದಳತೆ_ಒಳ_ಬೈಟುಗಳು > 0UL ) )
            {
                /* Translate the generic region definition contained in xRegions
                 * into the ARMv8 specific MPU settings that are then stored in
                 * xMPUSettings. */
                ul_Region_ಆರಂಭ_ವಿಳಾಸ = ( ( uint32_t ) xRegions[ l_ಸೂಚ್ಯಂಕ ].pv_ತಳ_ವಿಳಾಸ ) & ಪೋರ್ಟ್_MPU_RBAR_ವಿಳಾಸ_ಮುಖವಾಡ;
                ul_Region_ಕೊನೆ_ವಿಳಾಸ = ( uint32_t ) xRegions[ l_ಸೂಚ್ಯಂಕ ].pv_ತಳ_ವಿಳಾಸ + xRegions[ l_ಸೂಚ್ಯಂಕ ].ul_ಉದ್ದಳತೆ_ಒಳ_ಬೈಟುಗಳು - 1;
                ul_Region_ಕೊನೆ_ವಿಳಾಸ &= ಪೋರ್ಟ್_MPU_RLAR_ವಿಳಾಸ_ಮುಖವಾಡ;

                /* Start address. */
                xMPUSettings->xRegionsSettings[ ul_Region_ಸಂಖ್ಯೆ ].ulRBAR = ( ul_Region_ಆರಂಭ_ವಿಳಾಸ ) |
                                                                          ( ಪೋರ್ಟ್_MPU_REGION_NON_SHAREABLE );

                /* RO/RW. */
                ಆದರೆ( ( xRegions[ l_ಸೂಚ್ಯಂಕ ].ulParameters & tskMPU_REGION_READ_ONLY ) != 0 )
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_ಸಂಖ್ಯೆ ].ulRBAR |= ( ಪೋರ್ಟ್_MPU_REGION_READ_ONLY );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_ಸಂಖ್ಯೆ ].ulRBAR |= ( ಪೋರ್ಟ್_MPU_REGION_READ_WRITE );
                }

                /* XN. */
                ಆದರೆ( ( xRegions[ l_ಸೂಚ್ಯಂಕ ].ulParameters & tskMPU_REGION_EXECUTE_NEVER ) != 0 )
                {
                    xMPUSettings->xRegionsSettings[ ul_Region_ಸಂಖ್ಯೆ ].ulRBAR |= ( ಪೋರ್ಟ್_MPU_REGION_EXECUTE_NEVER );
                }

                /* End Address. */
                xMPUSettings->xRegionsSettings[ ul_Region_ಸಂಖ್ಯೆ ].ulRLAR = ( ul_Region_ಕೊನೆ_ವಿಳಾಸ ) |
                                                                          ( ಪೋರ್ಟ್_MPU_RLAR_REGION_ENABLE );

                /* PXN. */
                #ಆದರೆ ( ಪೋರ್ಟ್_ARMV8_M_MINOR_ಆವೃತ್ತಿ >= 1 )
                {
                    ಆದರೆ( ( xRegions[ l_ಸೂಚ್ಯಂಕ ].ulParameters & tskMPU_REGION_PRIVILEGED_EXECUTE_NEVER ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ ul_Region_ಸಂಖ್ಯೆ ].ulRLAR |= ( ಪೋರ್ಟ್_MPU_RLAR_PRIVILEGED_EXECUTE_NEVER );
                    }
                }
                #ಆದರೆ_ಅಂತ್ಯ /* portARMV8M_MINOR_VERSION >= 1 */

                /* Normal memory/ Device memory. */
                ಆದರೆ( ( xRegions[ l_ಸೂಚ್ಯಂಕ ].ulParameters & tsk_MPU_REGION_DEVICE_ಸ್ಮರಣೆ ) != 0 )
                {
                    /* Attr1 in MAIR0 is configured as device memory. */
                    xMPUSettings->xRegionsSettings[ ul_Region_ಸಂಖ್ಯೆ ].ulRLAR |= ಪೋರ್ಟ್_MPU_RLAR_ATTR_INDEX1;
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    /* Attr0 in MAIR0 is configured as normal memory. */
                    xMPUSettings->xRegionsSettings[ ul_Region_ಸಂಖ್ಯೆ ].ulRLAR |= ಪೋರ್ಟ್_MPU_RLAR_ATTR_INDEX0;
                }
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                /* Invalidate the region. */
                xMPUSettings->xRegionsSettings[ ul_Region_ಸಂಖ್ಯೆ ].ulRBAR = 0UL;
                xMPUSettings->xRegionsSettings[ ul_Region_ಸಂಖ್ಯೆ ].ulRLAR = 0UL;
            }

            l_ಸೂಚ್ಯಂಕ++;
        }
    }

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * pv_ಬಫರ್,
                                                size_t x_ಬಫರ್_ಉದ್ದಳತೆ,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_ಬಫರ್_ಆರಂಭ_ವಿಳಾಸ, ul_ಬಫರ್_ಕೊನೆ_ವಿಳಾಸ;
        ತಳ_Type_t xAccessGranted = pdFALSE;
        ಸ್ಥಿರಾಂಕ xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ಖಾಲಿ ); /* Calling task's MPU settings. */

        ಆದರೆ( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ( ( xTaskMpuSettings->ulTaskFlags & ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG ) == ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            ಆದರೆ( ಪೋರ್ಟ್_ಕೂಡಿಸು_UINT32_WILL_ಅತಿಪ್ರವಾಹ( ( ( uint32_t ) pv_ಬಫರ್ ), ( ( uint32_t ) x_ಬಫರ್_ಉದ್ದಳತೆ - 1UL ) ) == pdFALSE )
            {
                ul_ಬಫರ್_ಆರಂಭ_ವಿಳಾಸ = ( uint32_t ) pv_ಬಫರ್;
                ul_ಬಫರ್_ಕೊನೆ_ವಿಳಾಸ = ( ( ( uint32_t ) pv_ಬಫರ್ ) + ( uint32_t ) x_ಬಫರ್_ಉದ್ದಳತೆ - 1UL );

                ಗಾಗಿ( i = 0; i < ಪೋರ್ಟ್_ಒಟ್ಟು_ಅಂಕೆ_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    ಆದರೆ( ( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR & ಪೋರ್ಟ್_MPU_RLAR_REGION_ENABLE ) == ಪೋರ್ಟ್_MPU_RLAR_REGION_ENABLE )
                    {
                        ಆದರೆ( ಪೋರ್ಟ್_IS_ವಿಳಾಸ_WITHIN_RANGE( ul_ಬಫರ್_ಆರಂಭ_ವಿಳಾಸ,
                                                         ಪೋರ್ಟ್_ಹೊರತೆಗೆ_ಮೊದಲ_ವಿಳಾಸ_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ),
                                                         ಪೋರ್ಟ್_ಹೊರತೆಗೆ_ಕೊನೆಯ_ವಿಳಾಸ_FROM_RLAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR ) ) &&
                            ಪೋರ್ಟ್_IS_ವಿಳಾಸ_WITHIN_RANGE( ul_ಬಫರ್_ಕೊನೆ_ವಿಳಾಸ,
                                                         ಪೋರ್ಟ್_ಹೊರತೆಗೆ_ಮೊದಲ_ವಿಳಾಸ_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ),
                                                         ಪೋರ್ಟ್_ಹೊರತೆಗೆ_ಕೊನೆಯ_ವಿಳಾಸ_FROM_RLAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRLAR ) ) &&
                            ಪೋರ್ಟ್_IS_AUTHORIZED( ulAccessRequested,
                                               prvGetRegionAccessPermissions( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR ) ) )
                        {
                            xAccessGranted = pdTRUE;
                            ನಿಲ್ಲಿಸು;
                        }
                    }
                }
            }
        }

        ಹಿಂತಿರುಗಿ xAccessGranted;
    }

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Inside_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    uint32_t ul_Current_ಅಡಚಣೆ;
    ತಳ_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. Interrupt Program
     * Status Register (IPSR) holds the exception number of the currently-executing
     * exception or zero for Thread mode.*/
    __asm ಅಸ್ಥಿರ ( "mrs %0, ipsr" : "=r" ( ul_Current_ಅಡಚಣೆ )::"memory" );

    ಆದರೆ( ul_Current_ಅಡಚಣೆ == 0 )
    {
        xReturn = pdFALSE;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        xReturn = pdTRUE;
    }

    ಹಿಂತಿರುಗಿ xReturn;
}
/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configASSERT_DEFINED == 1 ) && ( ಪೋರ್ಟ್_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) )

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Validate_ಅಡಚಣೆ_ಆದ್ಯತೆ( ಶೂನ್ಯ )
    {
        uint32_t ul_Current_ಅಡಚಣೆ;
        uint8_t uc_Current_ಆದ್ಯತೆ;

        /* Obtain the number of the currently executing interrupt. */
        __asm ಅಸ್ಥಿರ ( "mrs %0, ipsr" : "=r" ( ul_Current_ಅಡಚಣೆ )::"memory" );

        /* Is the interrupt number a user defined interrupt? */
        ಆದರೆ( ul_Current_ಅಡಚಣೆ >= ಪೋರ್ಟ್_ಮೊದಲ_USER_ಅಡಚಣೆ_ಸಂಖ್ಯೆ )
        {
            /* Look up the interrupt's priority. */
            uc_Current_ಆದ್ಯತೆ = pc_ಅಡಚಣೆ_ಆದ್ಯತೆ_Registers[ ul_Current_ಅಡಚಣೆ ];

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
            configASSERT( uc_Current_ಆದ್ಯತೆ >= uc_Max_Sys_Call_ಆದ್ಯತೆ );
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
        configASSERT( ( ಪೋರ್ಟ್_AIRCR_REG & ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಗುಂಪು_ಮುಖವಾಡ ) <= ulMaxPRIGROUPValue );
    }

#ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Configure_ಅಡಚಣೆ_Priorities( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
{
    #ಆದರೆ ( ( configASSERT_DEFINED == 1 ) && ( ಪೋರ್ಟ್_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) )
    {
        ಅಸ್ಥಿರ uint32_t ul_Implemented_Prio_ಬಿಟ್ಟುಗಳು = 0;
        ಅಸ್ಥಿರ uint8_t uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
        * functions can be called. ISR safe functions are those that end in
        * "FromISR". FreeRTOS maintains separate thread and ISR API functions to
        * ensure interrupt entry is as fast and simple as possible.
        *
        * First, determine the number of priority bits available. Write to all
        * possible bits in the priority setting for SVCall. */
        ಪೋರ್ಟ್_NVIC_SHPR2_REG = 0xFF000000;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ = ( uint8_t ) ( ( ಪೋರ್ಟ್_NVIC_SHPR2_REG & 0xFF000000 ) >> 24 );

        /* Use the same mask on the maximum system call priority. */
        uc_Max_Sys_Call_ಆದ್ಯತೆ = config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ & uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ;

        /* Check that the maximum system call priority is nonzero after
        * accounting for the number of priority bits supported by the
        * hardware. A priority of 0 is invalid because setting the BASEPRI
        * register to 0 unmasks all interrupts, and interrupts with priority 0
        * cannot be masked using BASEPRI.
        * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( uc_Max_Sys_Call_ಆದ್ಯತೆ );

        /* Check that the bits not implemented in hardware are zero in
        * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ & ( uint8_t ) ( ~( uint32_t ) uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
        * of bits read back. */
        ಆಗ( ( uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ & ಪೋರ್ಟ್_ತುದಿ_ಬಿಟ್_ದ_BYTE ) == ಪೋರ್ಟ್_ತುದಿ_ಬಿಟ್_ದ_BYTE )
        {
            ul_Implemented_Prio_ಬಿಟ್ಟುಗಳು++;
            uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ <<= ( uint8_t ) 0x01;
        }

        ಆದರೆ( ul_Implemented_Prio_ಬಿಟ್ಟುಗಳು == 8 )
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
            configASSERT( ( config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            ulMaxPRIGROUPValue = ಪೋರ್ಟ್_MAX_PRIGROUP_ಬಿಟ್ಟುಗಳು - ul_Implemented_Prio_ಬಿಟ್ಟುಗಳು;
        }

        /* Shift the priority group value back to its position within the AIRCR
        * register. */
        ulMaxPRIGROUPValue <<= ಪೋರ್ಟ್_PRIGROUP_ಸರಿಸು;
        ulMaxPRIGROUPValue &= ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಗುಂಪು_ಮುಖವಾಡ;
    }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configASSERT_DEFINED == 1 ) && ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) ) */

    /* Make PendSV and SysTick the lowest priority interrupts, and make SVCall
    * the highest priority. */
    ಪೋರ್ಟ್_NVIC_SHPR3_REG |= ಪೋರ್ಟ್_NVIC_PENDSV_PRI;
    ಪೋರ್ಟ್_NVIC_SHPR3_REG |= ಪೋರ್ಟ್_NVIC_SYSTICK_PRI;
    ಪೋರ್ಟ್_NVIC_SHPR2_REG = 0;
}
/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Grant_Access_ಗಮ್ಯ_Kernel_Object( TaskHandle_t x_ಆಂತರಿಕ_Task_Handle,
                                         int32_t l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ, ul_Access_Control_List_ನಮೂದು_ಬಿಟ್;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object / ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );
        ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object % ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );

        xTaskMpuSettings = xTaskGetMPUSettings( x_ಆಂತರಿಕ_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ ] |= ( 1U << ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ );
    }

#ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Revoke_Access_ಗಮ್ಯ_Kernel_Object( TaskHandle_t x_ಆಂತರಿಕ_Task_Handle,
                                          int32_t l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ, ul_Access_Control_List_ನಮೂದು_ಬಿಟ್;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object / ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );
        ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object % ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );

        xTaskMpuSettings = xTaskGetMPUSettings( x_ಆಂತರಿಕ_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ ] &= ~( 1U << ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ );
    }

#ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #ಆದರೆ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( int32_t l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ, ul_Access_Control_List_ನಮೂದು_ಬಿಟ್;
            ತಳ_Type_t xAccessGranted = pdFALSE;
            ಸ್ಥಿರಾಂಕ xMPU_SETTINGS * xTaskMpuSettings;

            ಆದರೆ( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xTaskMpuSettings = xTaskGetMPUSettings( ಖಾಲಿ ); /* Calling task's MPU settings. */

                ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object / ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );
                ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object % ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );

                ಆದರೆ( ( xTaskMpuSettings->ulTaskFlags & ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG ) == ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    ಆದರೆ( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ ] & ( 1U << ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xAccessGranted;
        }

    #ಇಲ್ಲದಿದ್ದರೆ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( int32_t l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( ಶೂನ್ಯ ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            ಹಿಂತಿರುಗಿ pdTRUE;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
        ಸ್ಥಿರ uint32_t prvConfigurePACBTI( ತಳ_Type_t x_Write_Control_ರಿಜಿಸ್ಟರ್ )
    #ಇಲ್ಲದಿದ್ದರೆ /* configNUMBER_OF_CORES > 1 */
        uint32_t vConfigurePACBTI( ತಳ_Type_t x_Write_Control_ರಿಜಿಸ್ಟರ್ )
    #ಆದರೆ_ಅಂತ್ಯ /* configNUMBER_OF_CORES */
        {
            uint32_t ulControl = 0x0;

            /* Ensure that PACBTI is implemented. */
            configASSERT( ಪೋರ್ಟ್_ID_ISAR5_REG != 0x0 );

            /* Enable UsageFault exception. */
            ಪೋರ್ಟ್_SCB_SYS_HANDLER_CTRL_STATE_REG |= ಪೋರ್ಟ್_SCB_USG_FAULT_ENABLE_ಬಿಟ್;

            #ಆದರೆ ( configENABLE_PAC == 1 )
            {
                ulControl |= ( ಪೋರ್ಟ್_CONTROL_UPAC_EN | ಪೋರ್ಟ್_CONTROL_PAC_EN );
            }
            #ಆದರೆ_ಅಂತ್ಯ

            #ಆದರೆ ( configENABLE_BTI == 1 )
            {
                ulControl |= ( ಪೋರ್ಟ್_CONTROL_UBTI_EN | ಪೋರ್ಟ್_CONTROL_BTI_EN );
            }
            #ಆದರೆ_ಅಂತ್ಯ

            ಆದರೆ( x_Write_Control_ರಿಜಿಸ್ಟರ್ == pdTRUE )
            {
                __asm ಅಸ್ಥಿರ ( "msr control, %0" : : "r" ( ulControl ) );
            }

            ಹಿಂತಿರುಗಿ ulControl;
        }

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_PAC == 1 || configENABLE_BTI == 1 */
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )

    /* Which core owns the lock? */
    PRIVILEGED_ದತ್ತಾಂಶ ಅಸ್ಥಿರ uint32_t ulOwnedByCore[ ಪೋರ್ಟ್_MAX_CORE_ಎಣಿಕೆ ];
    /* Lock count a core owns. */
    PRIVILEGED_ದತ್ತಾಂಶ ಅಸ್ಥಿರ uint32_t ul_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ e_ಬೀಗ_ಎಣಿಕೆ ];
    /* Index 0 is used for ISR lock and Index 1 is used for task lock. */
    PRIVILEGED_ದತ್ತಾಂಶ ಅಸ್ಥಿರ uint32_t ul_Gate_ಶಬ್ದ[ e_ಬೀಗ_ಎಣಿಕೆ ];

    __attribute__((weak)) ಶೂನ್ಯ v_ಅಡಚಣೆ_Core( uint8_t ucCoreID )
    {
        /* Default weak stub - platform specific implementation may override. */
        ( ಶೂನ್ಯ ) ucCoreID;
    }

/*-----------------------------------------------------------*/

    ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ prvSpinUnlock( ಅಸ್ಥಿರ uint32_t * ul_ಬೀಗ )
    {
        /* Conservative unlock: preserve original barriers for broad HW/FVP. */
        __asm ಅಸ್ಥಿರ (
            "dmb sy         \n"
            "mov r1, #0     \n"
            "str r1, [%0]   \n"
            "sev            \n"
            "dsb            \n"
            "isb            \n"
            :
            : "r" ( ul_ಬೀಗ )
            : "memory", "r1"
        );
    }

/*-----------------------------------------------------------*/

    ಸ್ಥಿರ ಸಾಲೊಳಗೆ uint32_t prvSpinTrylock( ಅಸ್ಥಿರ uint32_t * ul_ಬೀಗ )
    {
        /*
         * Conservative ldrex/strex trylock:
         * - Return 1 immediately if busy, clearing exclusive state (CLREX).
         * - Retry strex only on spurious failure when observed free.
         * - DMB on success to preserve expected acquire semantics.
         */
        uint32_t ulVal;
        uint32_t ul_ಸ್ಥಿತಿ;

        __asm ಅಸ್ಥಿರ (
            " ldrex %0, [%1]   \n"
            : "=r" ( ulVal )
            : "r" ( ul_ಬೀಗ )
            : "memory"
        );

        ಆದರೆ( ulVal != 0U )
        {
            __asm ಅಸ್ಥಿರ ("clrex" ::: "memory");
            ಹಿಂತಿರುಗಿ 1U;
        }

        __asm ಅಸ್ಥಿರ (
            " strex %0, %2, [%1]   \n"
            : "=&r" ( ul_ಸ್ಥಿತಿ )
            : "r" ( ul_ಬೀಗ ), "r" (1U)
            : "memory"
        );

        ಆದರೆ( ul_ಸ್ಥಿತಿ != 0U )
        {
            ಹಿಂತಿರುಗಿ 1U;
        }
        __asm ಅಸ್ಥಿರ ( "dmb" ::: "memory" );
        ಹಿಂತಿರುಗಿ 0U;
    }


/*-----------------------------------------------------------*/

    /* Read 32b value shared between cores. */
    ಸ್ಥಿರ ಸಾಲೊಳಗೆ uint32_t prvGet32( ಅಸ್ಥಿರ uint32_t * x )
    {
        __asm( "dsb" );
        ಹಿಂತಿರುಗಿ *x;
    }

/*-----------------------------------------------------------*/

    /* Write 32b value shared between cores. */
    ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ prvSet32( ಅಸ್ಥಿರ uint32_t * x,
                                 uint32_t ಮೌಲ್ಯ )
    {
        *x = ಮೌಲ್ಯ;
        __asm( "dsb" );
    }

/*-----------------------------------------------------------*/

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Recursive_ಬೀಗ( uint8_t ucCoreID,
                             e_ಪೋರ್ಟ್_RTOSLock e_ಬೀಗ_ಅಂಕೆ,
                             ತಳ_Type_t uxAcquire )
    {
        /* Validate the core ID and lock number. */
        configASSERT( ucCoreID < ಪೋರ್ಟ್_MAX_CORE_ಎಣಿಕೆ );
        configASSERT( e_ಬೀಗ_ಅಂಕೆ < e_ಬೀಗ_ಎಣಿಕೆ );

        uint32_t ul_ಬೀಗ_ಬಿಟ್ = 1u << e_ಬೀಗ_ಅಂಕೆ;

        /* Lock acquire */
        ಆದರೆ( uxAcquire )
        {
            /* Check if spinlock is available. */
            /* If spinlock is not available check if the core owns the lock. */
            /* If the core owns the lock wait increment the lock count by the core. */
            /* If core does not own the lock wait for the spinlock. */
            ಆದರೆ( prvSpinTrylock( &ul_Gate_ಶಬ್ದ[ e_ಬೀಗ_ಅಂಕೆ ] ) != 0 )
            {
                /* Check if the core owns the spinlock. */
                ಆದರೆ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ul_ಬೀಗ_ಬಿಟ್ )
                {
                    configASSERT( prvGet32( &ul_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ e_ಬೀಗ_ಅಂಕೆ ] ) != ಪೋರ್ಟ್_UINT32_MAX );
                    prvSet32( &ul_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ e_ಬೀಗ_ಅಂಕೆ ], ( prvGet32( &ul_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ e_ಬೀಗ_ಅಂಕೆ ] ) + 1 ) );
                    ಹಿಂತಿರುಗಿ;
                }

                /* Preload the gate word into the cache. */
                uint32_t dummy = ul_Gate_ಶಬ್ದ[ e_ಬೀಗ_ಅಂಕೆ ];
                dummy++;

                ಆಗ( prvSpinTrylock( &ul_Gate_ಶಬ್ದ[ e_ಬೀಗ_ಅಂಕೆ ] ) != 0 )
                {
                    __asm ಅಸ್ಥಿರ ( "wfe" );
                }
            }

            /* Add barrier to ensure lock is taken before we proceed. */
            __asm ಅಸ್ಥಿರ( "dmb sy" ::: "memory" );

            /* Assert the lock count is 0 when the spinlock is free and is acquired. */
            configASSERT( prvGet32( &ul_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ e_ಬೀಗ_ಅಂಕೆ ] ) == 0 );

            /* Set lock count as 1. */
            prvSet32( &ul_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ e_ಬೀಗ_ಅಂಕೆ ], 1 );
            /* Set ulOwnedByCore. */
            prvSet32( &ulOwnedByCore[ ucCoreID ], ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) | ul_ಬೀಗ_ಬಿಟ್ ) );
        }
        /* Lock release. */
        ಇಲ್ಲದಿದ್ದರೆ
        {
            /* Assert the lock is not free already. */
            configASSERT( ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ul_ಬೀಗ_ಬಿಟ್ ) != 0 );
            configASSERT( prvGet32( &ul_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ e_ಬೀಗ_ಅಂಕೆ ] ) != 0 );

            /* Reduce ulRecursionCountByLock by 1. */
            prvSet32( &ul_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ e_ಬೀಗ_ಅಂಕೆ ], ( prvGet32( &ul_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ e_ಬೀಗ_ಅಂಕೆ ] ) - 1 ) );

            ಆದರೆ( !prvGet32( &ul_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ e_ಬೀಗ_ಅಂಕೆ ] ) )
            {
                prvSet32( &ulOwnedByCore[ ucCoreID ], ( prvGet32( &ulOwnedByCore[ ucCoreID ] ) & ~ul_ಬೀಗ_ಬಿಟ್ ) );
                prvSpinUnlock( &ul_Gate_ಶಬ್ದ[ e_ಬೀಗ_ಅಂಕೆ ] );
                /* Add barrier to ensure lock status is reflected before we proceed. */
                __asm ಅಸ್ಥಿರ( "dmb sy" ::: "memory" );
            }
        }
    }

/*-----------------------------------------------------------*/

    uint8_t uc_ಪೋರ್ಟ್_Get_Core_ID( ಶೂನ್ಯ )
    {
        ಹಿಂತಿರುಗಿ *(ಅಸ್ಥಿರ uint8_t *)(config_CORE_ID_ರಿಜಿಸ್ಟರ್);
    }

/*-----------------------------------------------------------*/

#ಆದರೆ_ಅಂತ್ಯ /* if( configNUMBER_OF_CORES > 1 ) */
