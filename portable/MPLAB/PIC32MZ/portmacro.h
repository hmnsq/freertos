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

#اگر_تعریف_نشده PORTMACRO_H
#تعریف_کن PORTMACRO_H

/* System include files */
#ضمن <xc.h>

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    خارجي "C" {
#پایان_اگر
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
#تعریف_کن پورت_CHAR        حرف
#تعریف_کن پورت_FLOAT       عائم
#تعریف_کن پورت_DOUBLE      مزدوج
#تعریف_کن پورت_LONG        دراز
#تعریف_کن پورت_SHORT       کوتاه
#تعریف_کن پورت_پشته_TYPE  uint32_t
#تعریف_کن پورت_پایه_TYPE   دراز

تعريفنوع پورت_پشته_TYPE پشته_Type_t;
تعريفنوع دراز پایه_Type_t;
تعريفنوع بیعلامت دراز UBaseType_t;

#إذا( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
    تعريفنوع uint16_t TickType_t;
    #تعریف_کن پورت_MAX_DELAY ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_32_بیتها )
    تعريفنوع uint32_t TickType_t;
    #تعریف_کن پورت_MAX_DELAY ( TickType_t ) 0xffffffffUL

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
    not need to be guarded with a critical section. */
    #تعریف_کن پورت_TICK_TYPE_IS_ATOMIC 1
#وإلا
    #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
#پایان_اگر
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کن پورت_BYTE_ALIGNMENT          8
#تعریف_کن پورت_پشته_GROWTH            -1
#تعریف_کن پورت_TICK_PERIOD_MS          ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
/*-----------------------------------------------------------*/

/* Critical section management. */
#تعریف_کن پورت_IPL_لغزش               ( 10UL )
/* Don't straddle the CEE bit.  Interrupts calling FreeRTOS functions should
never have higher IPL bits set anyway. */
#تعریف_کن پورت_ALL_IPL_بیتها            ( 0x7FUL << پورت_IPL_لغزش )
#تعریف_کن پورت_SW0_بیت                 ( 0x01 << 8 )

/* This clears the IPL bits, then sets them to
configMAX_SYSCALL_INTERRUPT_PRIORITY.  An extra check is performed if
configASSERT() is defined to ensure an assertion handler does not inadvertently
attempt to lower the IPL when the call to assert was triggered because the IPL
value was found to be above configMAX_SYSCALL_INTERRUPT_PRIORITY when an ISR
safe FreeRTOS API function was executed.  ISR safe FreeRTOS API functions are
those that end in FromISR.  FreeRTOS maintains a separate interrupt API to
ensure API function and interrupt entry is as fast and as simple as possible. */
#إذا ( configASSERT_DEFINED == 1 )
    #تعریف_کن پورت_DISABLE_INTERRUPTS()                                            \
    {                                                                           \
    uint32_t ul_وضعیت;                                                          \
                                                                                \
        /* Mask interrupts at and below the kernel interrupt priority. */       \
        ul_وضعیت = CP0_GET_وضعیت();                                           \
                                                                                \
        /* Is the current IPL below configMAX_SYSCALL_INTERRUPT_PRIORITY? */    \
        إذا( ( ( ul_وضعیت & پورت_ALL_IPL_بیتها ) >> پورت_IPL_لغزش ) < config_MAX_SYSCALL_وقفه_اولویت ) \
        {                                                                       \
            ul_وضعیت &= ~پورت_ALL_IPL_بیتها;                                      \
            CP0_مجموعه_وضعیت( ( ul_وضعیت | ( config_MAX_SYSCALL_وقفه_اولویت << پورت_IPL_لغزش ) ) ); \
        }                                                                       \
    }
#وإلا /* configASSERT */
    #تعریف_کن پورت_DISABLE_INTERRUPTS()                                        \
    {                                                                       \
    uint32_t ul_وضعیت;                                                      \
                                                                            \
        /* Mask interrupts at and below the kernel interrupt priority. */   \
        ul_وضعیت = CP0_GET_وضعیت();                                       \
        ul_وضعیت &= ~پورت_ALL_IPL_بیتها;                                      \
        CP0_مجموعه_وضعیت( ( ul_وضعیت | ( config_MAX_SYSCALL_وقفه_اولویت << پورت_IPL_لغزش ) ) ); \
    }
#پایان_اگر /* configASSERT */

#تعریف_کن پورت_ENABLE_INTERRUPTS()                                         \
{                                                                       \
uint32_t ul_وضعیت;                                                      \
                                                                        \
    /* Unmask all interrupts. */                                        \
    ul_وضعیت = CP0_GET_وضعیت();                                       \
    ul_وضعیت &= ~پورت_ALL_IPL_بیتها;                                      \
    CP0_مجموعه_وضعیت( ul_وضعیت );                                        \
}


خارجي فراغ vTaskEnterCritical( فراغ );
خارجي فراغ vTaskExitCritical( فراغ );
#تعریف_کن پورت_CRITICAL_NESTING_درون_TCB 1
#تعریف_کن پورت_ENTER_CRITICAL()        vTaskEnterCritical()
#تعریف_کن پورت_EXIT_CRITICAL()         vTaskExitCritical()

خارجي UBaseType_t ux_پورت_مجموعه_وقفه_ماسک_From_ISR();
خارجي فراغ v_پورت_Clear_وقفه_ماسک_From_ISR( UBaseType_t );
#تعریف_کن پورت_مجموعه_وقفه_ماسک_FROM_ISR() ux_پورت_مجموعه_وقفه_ماسک_From_ISR()
#تعریف_کن پورت_CLEAR_وقفه_ماسک_FROM_ISR( ux_Saved_وضعیت_ثبات ) v_پورت_Clear_وقفه_ماسک_From_ISR( ux_Saved_وضعیت_ثبات )

#إذا ( __mips_hard_float == 0 ) && ( configUSE_TASK_FPU_SUPPORT == 1 )
    #خطا configUSE_TASK_FPU_SUPPORT can only be مجموعه مقصد 1 when the part supports a hardware FPU module.
#پایان_اگر

#إذا ( __mips_hard_float == 1 ) && ( configUSE_TASK_FPU_SUPPORT == 1 )
    فراغ v_پورت_Task_استفاده_میکند_FPU( فراغ );
    #تعریف_کن پورت_TASK_استفاده_میکند_FLOATING_نقطه() v_پورت_Task_استفاده_میکند_FPU()
#پایان_اگر

#اگر_تعریف_نشده config_USE_پورت_OPTIMISED_TASK_SELECTION
    #تعریف_کن config_USE_پورت_OPTIMISED_TASK_SELECTION 1
#پایان_اگر

#إذا config_USE_پورت_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #إذا( configMAX_PRIORITIES > 32 )
        #خطا config_USE_پورت_OPTIMISED_TASK_SELECTION can only be مجموعه مقصد 1 when configMAX_PRIORITIES is less than or equal مقصد 32.  It is very rare that a system requires بیشتر than 10 مقصد 15 difference priorities as tasks that share a اولویت will time برش.
    #پایان_اگر

    /* Store/clear the ready priorities in a bit map. */
    #تعریف_کن پورت_رکورد_READY_اولویت( ux_اولویت, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( ux_اولویت ) )
    #تعریف_کن پورت_RESET_READY_اولویت( ux_اولویت, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( ux_اولویت ) )

    /*-----------------------------------------------------------*/

    #تعریف_کن پورت_GET_HIGHEST_اولویت( ux_بالاترین_اولویت, uxReadyPriorities ) ux_بالاترین_اولویت = ( 31UL - _clz( ( uxReadyPriorities ) ) )

#پایان_اگر /* taskRECORD_READY_PRIORITY */

/*-----------------------------------------------------------*/

/* Task utilities. */

#تعریف_کن پورت_YIELD()                             \
{                                               \
uint32_t ulCause;                               \
                                                \
    /* Trigger software interrupt. */           \
    ulCause = _CP0_GET_CAUSE();                 \
    ulCause |= پورت_SW0_بیت;                     \
    CP0_مجموعه_CAUSE( ulCause );                  \
}

خارجي متطاير UBaseType_t ux_وقفه_Nesting;
#تعریف_کن پورت_ASSERT_IF_درون_ISR() configASSERT( ux_وقفه_Nesting == 0 )

#تعریف_کن پورت_NOP()   __asm متطاير ( "nop" )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters ) __attribute__((noreturn))
#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )
/*-----------------------------------------------------------*/

#تعریف_کن پورت_انتها_SWITCHING_ISR( xSwitchRequired ) \
    افعل                                           \
    {                                            \
        إذا( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_مقصد_SCHEDULER();        \
            پورت_YIELD();                         \
        }                                        \
        وإلا                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } طالما( 0 )

/* Required by the kernel aware debugger. */
#اگر_تعریف_شده __DEBUG
    #تعریف_کن پورت_REMOVE_STATIC_QUALIFIER
#پایان_اگر

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */
