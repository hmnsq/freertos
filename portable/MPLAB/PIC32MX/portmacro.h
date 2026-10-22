/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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

#جيڪڏهن_وصف_نه_ٿيل PORTMACRO_H
#وصف_ڪريو PORTMACRO_H

/* System include files */
#ضمن <xc.h>

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    خارجي "C" {
#جيڪڏهن_پورو
/* *INDENT-ON* */

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#وصف_ڪريو پورٽ_CHAR        حرف
#وصف_ڪريو پورٽ_FLOAT       عائم
#وصف_ڪريو پورٽ_DOUBLE      مزدوج
#وصف_ڪريو پورٽ_LONG        ڊگهو
#وصف_ڪريو پورٽ_SHORT       ننڍو
#وصف_ڪريو پورٽ_ڍير_TYPE  uint32_t
#وصف_ڪريو پورٽ_بنياد_TYPE   ڊگهو

تعريفنوع پورٽ_ڍير_TYPE ڍير_Type_t;
تعريفنوع ڊگهو بنياد_Type_t;
تعريفنوع بنانشان ڊگهو UBaseType_t;

#إذا( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_16_بٽ )
    تعريفنوع uint16_t TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_32_بٽ )
    تعريفنوع uint32_t TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY ( TickType_t ) 0xffffffffUL

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
    not need to be guarded with a critical section. */
    #وصف_ڪريو پورٽ_TICK_TYPE_IS_ATOMIC 1
#وإلا
    #غلطي config_TICK_TYPE_ويڪر_اندريون_بٽ سيٽ منزل unsupported tick type ويڪر.
#جيڪڏهن_پورو
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#وصف_ڪريو پورٽ_BYTE_ALIGNMENT          8
#وصف_ڪريو پورٽ_ڍير_GROWTH            -1
#وصف_ڪريو پورٽ_TICK_PERIOD_MS          ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
/*-----------------------------------------------------------*/

/* Critical section management. */
#وصف_ڪريو پورٽ_IPL_سرڪايو               ( 10UL )
#وصف_ڪريو پورٽ_ALL_IPL_بٽ            ( 0x3fUL << پورٽ_IPL_سرڪايو )
#وصف_ڪريو پورٽ_SW0_ٻٽو_انگ                 ( 0x01 << 8 )

/* This clears the IPL bits, then sets them to
configMAX_SYSCALL_INTERRUPT_PRIORITY.  An extra check is performed if
configASSERT() is defined to ensure an assertion handler does not inadvertently
attempt to lower the IPL when the call to assert was triggered because the IPL
value was found to be above configMAX_SYSCALL_INTERRUPT_PRIORITY when an ISR
safe FreeRTOS API function was executed.  ISR safe FreeRTOS API functions are
those that end in FromISR.  FreeRTOS maintains a separate interrupt API to
ensure API function and interrupt entry is as fast and as simple as possible. */
#إذا ( configASSERT_DEFINED == 1 )
    #وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()                                            \
    {                                                                           \
    uint32_t ul_حالت;                                                      \
                                                                                \
        /* Mask interrupts at and below the kernel interrupt priority. */       \
        ul_حالت = CP0_GET_حالت();                                           \
                                                                                \
        /* Is the current IPL below configMAX_SYSCALL_INTERRUPT_PRIORITY? */    \
        إذا( ( ( ul_حالت & پورٽ_ALL_IPL_بٽ ) >> پورٽ_IPL_سرڪايو ) < config_MAX_SYSCALL_مداخلت_ترجيح ) \
        {                                                                       \
            ul_حالت &= ~پورٽ_ALL_IPL_بٽ;                                      \
            CP0_سيٽ_حالت( ( ul_حالت | ( config_MAX_SYSCALL_مداخلت_ترجيح << پورٽ_IPL_سرڪايو ) ) ); \
        }                                                                       \
    }
#وإلا /* configASSERT */
    #وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()                                        \
    {                                                                       \
    uint32_t ul_حالت;                                                  \
                                                                            \
        /* Mask interrupts at and below the kernel interrupt priority. */   \
        ul_حالت = CP0_GET_حالت();                                       \
        ul_حالت &= ~پورٽ_ALL_IPL_بٽ;                                      \
        CP0_سيٽ_حالت( ( ul_حالت | ( config_MAX_SYSCALL_مداخلت_ترجيح << پورٽ_IPL_سرڪايو ) ) ); \
    }
#جيڪڏهن_پورو /* configASSERT */

#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()                                         \
{                                                                       \
uint32_t ul_حالت;                                                  \
                                                                        \
    /* Unmask all interrupts. */                                        \
    ul_حالت = CP0_GET_حالت();                                       \
    ul_حالت &= ~پورٽ_ALL_IPL_بٽ;                                      \
    CP0_سيٽ_حالت( ul_حالت );                                        \
}


خارجي فراغ vTaskEnterCritical( فراغ );
خارجي فراغ vTaskExitCritical( فراغ );
#وصف_ڪريو پورٽ_CRITICAL_NESTING_اندريون_TCB 1
#وصف_ڪريو پورٽ_ENTER_CRITICAL()        vTaskEnterCritical()
#وصف_ڪريو پورٽ_EXIT_CRITICAL()         vTaskExitCritical()

خارجي UBaseType_t ux_پورٽ_سيٽ_مداخلت_نقاب_From_ISR();
خارجي فراغ v_پورٽ_Clear_مداخلت_نقاب_From_ISR( UBaseType_t );
#وصف_ڪريو پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR() ux_پورٽ_سيٽ_مداخلت_نقاب_From_ISR()
#وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( ux_Saved_حالت_رجسٽر ) v_پورٽ_Clear_مداخلت_نقاب_From_ISR( ux_Saved_حالت_رجسٽر )

#جيڪڏهن_وصف_نه_ٿيل config_USE_پورٽ_OPTIMISED_TASK_SELECTION
    #وصف_ڪريو config_USE_پورٽ_OPTIMISED_TASK_SELECTION 1
#جيڪڏهن_پورو

#إذا config_USE_پورٽ_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #إذا( configMAX_PRIORITIES > 32 )
        #غلطي config_USE_پورٽ_OPTIMISED_TASK_SELECTION can only be سيٽ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires وڌيڪ than 10 منزل 15 difference priorities as tasks that share a ترجيح will time ٽڪرو.
    #جيڪڏهن_پورو

    /* Store/clear the ready priorities in a bit map. */
    #وصف_ڪريو پورٽ_رڪارڊ_READY_ترجيح( ux_ترجيح, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجيح ) )
    #وصف_ڪريو پورٽ_RESET_READY_ترجيح( ux_ترجيح, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجيح ) )

    /*-----------------------------------------------------------*/

    #وصف_ڪريو پورٽ_GET_HIGHEST_ترجيح( ux_چوٽي_ترجيح, uxReadyPriorities ) ux_چوٽي_ترجيح = ( 31UL - _clz( ( uxReadyPriorities ) ) )

#جيڪڏهن_پورو /* taskRECORD_READY_PRIORITY */

/*-----------------------------------------------------------*/

/* Task utilities. */

#وصف_ڪريو پورٽ_YIELD()                             \
{                                               \
uint32_t ulCause;                           \
                                                \
    /* Trigger software interrupt. */           \
    ulCause = _CP0_GET_CAUSE();                 \
    ulCause |= پورٽ_SW0_ٻٽو_انگ;                     \
    CP0_سيٽ_CAUSE( ulCause );                  \
}

خارجي متطاير UBaseType_t ux_مداخلت_Nesting;
#وصف_ڪريو پورٽ_ASSERT_IF_اندريون_ISR() configASSERT( ux_مداخلت_Nesting == 0 )

#وصف_ڪريو پورٽ_NOP()   __asm متطاير ( "nop" )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters ) __attribute__((noreturn))
#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )
/*-----------------------------------------------------------*/

#وصف_ڪريو پورٽ_پڇاڙي_SWITCHING_ISR( xSwitchRequired ) \
    افعل                                           \
    {                                            \
        إذا( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_منزل_SCHEDULER();        \
            پورٽ_YIELD();                         \
        }                                        \
        وإلا                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } طالما( 0 )

/* Required by the kernel aware debugger. */
#جيڪڏهن_وصف_ٿيل __DEBUG
    #وصف_ڪريو پورٽ_REMOVE_STATIC_QUALIFIER
#جيڪڏهن_پورو

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_پورو /* PORTMACRO_H */
