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

#جے_بنا_تعریف PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/* System include files */
#ضمن <xc.h>

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    خارجي "C" {
#جے_انت
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
#تعریف_کرو پورٹ_CHAR        حرف
#تعریف_کرو پورٹ_FLOAT       عائم
#تعریف_کرو پورٹ_DOUBLE      مزدوج
#تعریف_کرو پورٹ_LONG        لما
#تعریف_کرو پورٹ_SHORT       چھوٹا
#تعریف_کرو پورٹ_ڈھیر_TYPE  uint32_t
#تعریف_کرو پورٹ_ادھار_TYPE   لما

تعريفنوع پورٹ_ڈھیر_TYPE ڈھیر_Type_t;
تعريفنوع لما ادھار_Type_t;
تعريفنوع بنانشانی لما UBaseType_t;

#إذا( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    تعريفنوع uint16_t TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    تعريفنوع uint32_t TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY ( TickType_t ) 0xffffffffUL

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
    not need to be guarded with a critical section. */
    #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC 1
#وإلا
    #غلطی config_TICK_TYPE_چوڑائی_وچ_بٹ سیٹ منزل unsupported tick type چوڑائی.
#جے_انت
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کرو پورٹ_BYTE_ALIGNMENT          8
#تعریف_کرو پورٹ_ڈھیر_GROWTH            -1
#تعریف_کرو پورٹ_TICK_PERIOD_MS          ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
/*-----------------------------------------------------------*/

/* Critical section management. */
#تعریف_کرو پورٹ_IPL_کھسکاؤ               ( 10UL )
/* Don't straddle the CEE bit.  Interrupts calling FreeRTOS functions should
never have higher IPL bits set anyway. */
#تعریف_کرو پورٹ_ALL_IPL_بٹ            ( 0x7FUL << پورٹ_IPL_کھسکاؤ )
#تعریف_کرو پورٹ_SW0_ثنائی_ہندسہ                 ( 0x01 << 8 )

/* This clears the IPL bits, then sets them to
configMAX_SYSCALL_INTERRUPT_PRIORITY.  An extra check is performed if
configASSERT() is defined to ensure an assertion handler does not inadvertently
attempt to lower the IPL when the call to assert was triggered because the IPL
value was found to be above configMAX_SYSCALL_INTERRUPT_PRIORITY when an ISR
safe FreeRTOS API function was executed.  ISR safe FreeRTOS API functions are
those that end in FromISR.  FreeRTOS maintains a separate interrupt API to
ensure API function and interrupt entry is as fast and as simple as possible. */
#إذا ( configASSERT_DEFINED == 1 )
    #تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                                            \
    {                                                                           \
    uint32_t ul_حالت;                                                          \
                                                                                \
        /* Mask interrupts at and below the kernel interrupt priority. */       \
        ul_حالت = CP0_GET_حالت();                                           \
                                                                                \
        /* Is the current IPL below configMAX_SYSCALL_INTERRUPT_PRIORITY? */    \
        إذا( ( ( ul_حالت & پورٹ_ALL_IPL_بٹ ) >> پورٹ_IPL_کھسکاؤ ) < config_MAX_SYSCALL_رکاوٹ_ترجیح ) \
        {                                                                       \
            ul_حالت &= ~پورٹ_ALL_IPL_بٹ;                                      \
            CP0_سیٹ_حالت( ( ul_حالت | ( config_MAX_SYSCALL_رکاوٹ_ترجیح << پورٹ_IPL_کھسکاؤ ) ) ); \
        }                                                                       \
    }
#وإلا /* configASSERT */
    #تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                                        \
    {                                                                       \
    uint32_t ul_حالت;                                                      \
                                                                            \
        /* Mask interrupts at and below the kernel interrupt priority. */   \
        ul_حالت = CP0_GET_حالت();                                       \
        ul_حالت &= ~پورٹ_ALL_IPL_بٹ;                                      \
        CP0_سیٹ_حالت( ( ul_حالت | ( config_MAX_SYSCALL_رکاوٹ_ترجیح << پورٹ_IPL_کھسکاؤ ) ) ); \
    }
#جے_انت /* configASSERT */

#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                                         \
{                                                                       \
uint32_t ul_حالت;                                                      \
                                                                        \
    /* Unmask all interrupts. */                                        \
    ul_حالت = CP0_GET_حالت();                                       \
    ul_حالت &= ~پورٹ_ALL_IPL_بٹ;                                      \
    CP0_سیٹ_حالت( ul_حالت );                                        \
}


خارجي فراغ vTaskEnterCritical( فراغ );
خارجي فراغ vTaskExitCritical( فراغ );
#تعریف_کرو پورٹ_CRITICAL_NESTING_وچ_TCB 1
#تعریف_کرو پورٹ_ENTER_CRITICAL()        vTaskEnterCritical()
#تعریف_کرو پورٹ_EXIT_CRITICAL()         vTaskExitCritical()

خارجي UBaseType_t ux_پورٹ_سیٹ_رکاوٹ_نقاب_From_ISR();
خارجي فراغ v_پورٹ_Clear_رکاوٹ_نقاب_From_ISR( UBaseType_t );
#تعریف_کرو پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR() ux_پورٹ_سیٹ_رکاوٹ_نقاب_From_ISR()
#تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( ux_Saved_حالت_رجسٹر ) v_پورٹ_Clear_رکاوٹ_نقاب_From_ISR( ux_Saved_حالت_رجسٹر )

#إذا ( __mips_hard_float == 0 ) && ( configUSE_TASK_FPU_SUPPORT == 1 )
    #غلطی configUSE_TASK_FPU_SUPPORT can only be سیٹ منزل 1 when the part supports a hardware FPU module.
#جے_انت

#إذا ( __mips_hard_float == 1 ) && ( configUSE_TASK_FPU_SUPPORT == 1 )
    فراغ v_پورٹ_Task_ورتدا_FPU( فراغ );
    #تعریف_کرو پورٹ_TASK_ورتدا_FLOATING_نقطہ() v_پورٹ_Task_ورتدا_FPU()
#جے_انت

#جے_بنا_تعریف config_USE_پورٹ_OPTIMISED_TASK_SELECTION
    #تعریف_کرو config_USE_پورٹ_OPTIMISED_TASK_SELECTION 1
#جے_انت

#إذا config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #إذا( configMAX_PRIORITIES > 32 )
        #غلطی config_USE_پورٹ_OPTIMISED_TASK_SELECTION can only be سیٹ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires ہور than 10 منزل 15 difference priorities as tasks that share a ترجیح will time ٹکڑا.
    #جے_انت

    /* Store/clear the ready priorities in a bit map. */
    #تعریف_کرو پورٹ_ریکارڈ_READY_ترجیح( ux_ترجیح, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجیح ) )
    #تعریف_کرو پورٹ_RESET_READY_ترجیح( ux_ترجیح, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجیح ) )

    /*-----------------------------------------------------------*/

    #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities ) ux_چوٹی_ترجیح = ( 31UL - _clz( ( uxReadyPriorities ) ) )

#جے_انت /* taskRECORD_READY_PRIORITY */

/*-----------------------------------------------------------*/

/* Task utilities. */

#تعریف_کرو پورٹ_YIELD()                             \
{                                               \
uint32_t ulCause;                               \
                                                \
    /* Trigger software interrupt. */           \
    ulCause = _CP0_GET_CAUSE();                 \
    ulCause |= پورٹ_SW0_ثنائی_ہندسہ;                     \
    CP0_سیٹ_CAUSE( ulCause );                  \
}

خارجي متطاير UBaseType_t ux_رکاوٹ_Nesting;
#تعریف_کرو پورٹ_ASSERT_IF_وچ_ISR() configASSERT( ux_رکاوٹ_Nesting == 0 )

#تعریف_کرو پورٹ_NOP()   __asm متطاير ( "nop" )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters ) __attribute__((noreturn))
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )
/*-----------------------------------------------------------*/

#تعریف_کرو پورٹ_سرا_SWITCHING_ISR( xSwitchRequired ) \
    افعل                                           \
    {                                            \
        إذا( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_منزل_SCHEDULER();        \
            پورٹ_YIELD();                         \
        }                                        \
        وإلا                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } طالما( 0 )

/* Required by the kernel aware debugger. */
#جے_تعریف_شدہ __DEBUG
    #تعریف_کرو پورٹ_REMOVE_STATIC_QUALIFIER
#جے_انت

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    }
#جے_انت
/* *INDENT-ON* */

#جے_انت /* PORTMACRO_H */
