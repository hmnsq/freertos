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

#که_نه_تعریف_شوی PORTMACRO_H
#تعریف_کړه PORTMACRO_H

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    خارجي "C" {
#د_که_پای
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
#تعریف_کړه پورټ_CHAR        حرف
#تعریف_کړه پورټ_FLOAT       عائم
#تعریف_کړه پورټ_DOUBLE      مزدوج
#تعریف_کړه پورټ_LONG        اوږد
#تعریف_کړه پورټ_SHORT       لنډ
#تعریف_کړه پورټ_ډېری_TYPE  uint32_t
#تعریف_کړه پورټ_بنسټ_TYPE   اوږد

تعريفنوع پورټ_ډېری_TYPE ډېری_Type_t;
تعريفنوع اوږد بنسټ_Type_t;
تعريفنوع بینښه اوږد UBaseType_t;

#إذا( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
    تعريفنوع uint16_t TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه  == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t             TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
#د_که_پای
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کړه پورټ_BYTE_ALIGNMENT  8
#تعریف_کړه پورټ_ډېری_GROWTH    -1
#تعریف_کړه پورټ_TICK_PERIOD_MS  ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
/*-----------------------------------------------------------*/

/* Critical section management. */
#تعریف_کړه پورټ_IPL_ښويدنه       ( 10UL )
/* Don't straddle the CEE bit.  Interrupts calling FreeRTOS functions should
never have higher IPL bits set anyway. */
#تعریف_کړه پورټ_ALL_IPL_بټونه    ( 0x7FUL << پورټ_IPL_ښويدنه )
#تعریف_کړه پورټ_SW0_بټ         ( 0x01 << 8 )

/* Interrupt priority conversion */
#تعریف_کړه پورټ_IPL_منزل_کوډ( ipl_شمېره )    ( ( ipl_شمېره >> 1 ) & 0x03ul )
#تعریف_کړه پورټ_کوډ_منزل_IPL( ipl_کوډ )      ( ( ipl_کوډ << 1 ) | 0x01ul )

/*-----------------------------------------------------------*/

ساكن مضمن uint32_t ul_پورټ_Get_CP0_حالت( فراغ )
{
uint32_t rv;

    __asm متطاير(
            "\n\t"
            "mfc0 %0,$12,0      \n\t"
            : "=r" ( rv ) :: );

    أرجع rv;
}
/*-----------------------------------------------------------*/

ساكن مضمن فراغ v_پورټ_سېټ_CP0_حالت( uint32_t new_حالت)
{
    ( فراغ ) new_حالت;

    __asm__ __volatile__(
            "\n\t"
            "mtc0 %0,$12,0      \n\t"
            "ehb                \n\t"
            :
            :"r" ( new_حالت ) : );
}
/*-----------------------------------------------------------*/

ساكن مضمن uint32_t ul_پورټ_Get_CP0_Cause( فراغ )
{
uint32_t rv;

    __asm متطاير(
            "\n\t"
            "mfc0 %0,$13,0      \n\t"
            : "=r" ( rv ) :: );

    أرجع rv;
}
/*-----------------------------------------------------------*/

ساكن مضمن فراغ v_پورټ_سېټ_CP0_Cause( uint32_t new_cause )
{
    ( فراغ ) new_cause;

    __asm__ __volatile__(
            "\n\t"
            "mtc0 %0,$13,0      \n\t"
            "ehb                \n\t"
            :
            :"r" ( new_cause ) : );
}
/*-----------------------------------------------------------*/

/* This clears the IPL bits, then sets them to
configMAX_SYSCALL_INTERRUPT_PRIORITY.  An extra check is performed if
configASSERT() is defined to ensure an assertion handler does not inadvertently
attempt to lower the IPL when the call to assert was triggered because the IPL
value was found to be above configMAX_SYSCALL_INTERRUPT_PRIORITY when an ISR
safe FreeRTOS API function was executed.  ISR safe FreeRTOS API functions are
those that end in FromISR.  FreeRTOS maintains a separate interrupt API to
ensure API function and interrupt entry is as fast and as simple as possible. */
#إذا ( configASSERT_DEFINED == 1 )
    #تعریف_کړه پورټ_DISABLE_INTERRUPTS()                                                                            \
    {                                                                                                           \
    uint32_t ul_حالت;                                                                                          \
        /* Mask interrupts at and below the kernel interrupt priority. */                                       \
        ul_حالت = ul_پورټ_Get_CP0_حالت();                                                                        \
        /* Is the current IPL below configMAX_SYSCALL_INTERRUPT_PRIORITY? */                                    \
        إذا( ( ( ul_حالت & پورټ_ALL_IPL_بټونه ) >> پورټ_IPL_ښويدنه ) < config_MAX_SYSCALL_مداخله_لومړیتوب )       \
        {                                                                                                       \
            ul_حالت &= ~پورټ_ALL_IPL_بټونه;                                                                      \
            v_پورټ_سېټ_CP0_حالت( ( ul_حالت | ( config_MAX_SYSCALL_مداخله_لومړیتوب << پورټ_IPL_ښويدنه ) ) );      \
        }                                                                                                       \
    }
#وإلا /* configASSERT */
    #تعریف_کړه پورټ_DISABLE_INTERRUPTS()                                                                            \
    {                                                                                                           \
    uint32_t ul_حالت;                                                                                          \
        /* Mask interrupts at and below the kernel interrupt priority. */                                       \
        ul_حالت = ul_پورټ_Get_CP0_حالت();                                                                        \
        ul_حالت &= ~پورټ_ALL_IPL_بټونه;                                                                          \
        v_پورټ_سېټ_CP0_حالت( ( ul_حالت | ( config_MAX_SYSCALL_مداخله_لومړیتوب << پورټ_IPL_ښويدنه ) ) );          \
    }
#د_که_پای /* configASSERT */

#تعریف_کړه پورټ_ENABLE_INTERRUPTS()             \
{                                           \
uint32_t ul_حالت;                          \
    /* Unmask all interrupts. */            \
    ul_حالت = ul_پورټ_Get_CP0_حالت();        \
    ul_حالت &= ~پورټ_ALL_IPL_بټونه;          \
    v_پورټ_سېټ_CP0_حالت( ul_حالت );          \
}


خارجي فراغ vTaskEnterCritical( فراغ );
خارجي فراغ vTaskExitCritical( فراغ );
#تعریف_کړه پورټ_CRITICAL_NESTING_دننه_TCB 1
#تعریف_کړه پورټ_ENTER_CRITICAL()        vTaskEnterCritical()
#تعریف_کړه پورټ_EXIT_CRITICAL()         vTaskExitCritical()

خارجي UBaseType_t ux_پورټ_سېټ_مداخله_ماسک_From_ISR();
خارجي فراغ v_پورټ_Clear_مداخله_ماسک_From_ISR( UBaseType_t );
#تعریف_کړه پورټ_سېټ_مداخله_ماسک_FROM_ISR() ux_پورټ_سېټ_مداخله_ماسک_From_ISR()
#تعریف_کړه پورټ_CLEAR_مداخله_ماسک_FROM_ISR( ux_Saved_حالت_ثبتوونکی ) v_پورټ_Clear_مداخله_ماسک_From_ISR( ux_Saved_حالت_ثبتوونکی )

#که_نه_تعریف_شوی config_USE_پورټ_OPTIMISED_TASK_SELECTION
    #تعریف_کړه config_USE_پورټ_OPTIMISED_TASK_SELECTION 1
#د_که_پای

#إذا config_USE_پورټ_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #إذا( configMAX_PRIORITIES > 32 )
        #تېروتنه config_USE_پورټ_OPTIMISED_TASK_SELECTION can only be سېټ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires نور than 10 منزل 15 difference priorities as tasks that share a لومړیتوب will time ټوټه.
    #د_که_پای

    /* Store/clear the ready priorities in a bit map. */
    #تعریف_کړه پورټ_ریکارډ_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( ux_لومړیتوب ) )
    #تعریف_کړه پورټ_RESET_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( ux_لومړیتوب ) )

    /*-----------------------------------------------------------*/

    #تعریف_کړه پورټ_GET_HIGHEST_لومړیتوب( ux_سر_لومړیتوب, uxReadyPriorities ) ux_سر_لومړیتوب = ( 31 - _clz( ( uxReadyPriorities ) ) )

#د_که_پای /* taskRECORD_READY_PRIORITY */

/*-----------------------------------------------------------*/

/* Task utilities. */

#تعریف_کړه پورټ_YIELD()                         \
{                                           \
uint32_t ulCause;                           \
    /* Trigger software interrupt. */       \
    ulCause = ul_پورټ_Get_CP0_Cause();          \
    ulCause |= پورټ_SW0_بټ;                 \
    v_پورټ_سېټ_CP0_Cause( ulCause );            \
}

خارجي متطاير UBaseType_t ux_مداخله_Nesting;
#تعریف_کړه پورټ_ASSERT_IF_دننه_ISR() configASSERT( ux_مداخله_Nesting == 0 )

#تعریف_کړه پورټ_NOP() __asm متطاير ( "nop" )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters ) __attribute__((noreturn))
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )
/*-----------------------------------------------------------*/

#تعریف_کړه پورټ_پای_ټکی_SWITCHING_ISR( xSwitchRequired ) \
    افعل                                           \
    {                                            \
        إذا( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_منزل_SCHEDULER();        \
            پورټ_YIELD();                         \
        }                                        \
        وإلا                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } طالما( 0 )

/* Required by the kernel aware debugger. */
#که_تعریف_شوی __DEBUG
    #تعریف_کړه پورټ_REMOVE_STATIC_QUALIFIER
#د_که_پای

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
