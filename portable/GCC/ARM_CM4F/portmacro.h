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
#تعریف_کن پورت_CHAR          حرف
#تعریف_کن پورت_FLOAT         عائم
#تعریف_کن پورت_DOUBLE        مزدوج
#تعریف_کن پورت_LONG          دراز
#تعریف_کن پورت_SHORT         کوتاه
#تعریف_کن پورت_پشته_TYPE    uint32_t
#تعریف_کن پورت_پایه_TYPE     دراز

تعريفنوع پورت_پشته_TYPE   پشته_Type_t;
تعريفنوع دراز             پایه_Type_t;
تعريفنوع بیعلامت دراز    UBaseType_t;

#إذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_32_بیتها )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کن پورت_TICK_TYPE_IS_ATOMIC    1
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_64_بیتها )
    تعريفنوع uint64_t TickType_t;
    #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffffffffffffffffULL
#وإلا /* if ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS ) */
    #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
#پایان_اگر /* if ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS ) */
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#تعریف_کن پورت_پشته_GROWTH      ( -1 )
#تعریف_کن پورت_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
#تعریف_کن پورت_BYTE_ALIGNMENT    8
#تعریف_کن پورت_DONT_DISCARD      __attribute__( ( استفاده_شده ) )
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
#تعریف_کن پورت_YIELD()                                     \
    {                                                   \
        /* Set a PendSV to request a context switch. */ \
        پورت_NVIC_INT_CTRL_REG = پورت_NVIC_PENDSVSET_بیت; \
                                                        \
        /* Barriers are normally not required but do ensure the code is completely \
         * within the specified behaviour for the architecture. */ \
        __asm متطاير ( "dsb" ::: "memory" );                     \
        __asm متطاير ( "isb" );                                  \
    }

#تعریف_کن پورت_NVIC_INT_CTRL_REG     ( *( ( متطاير uint32_t * ) 0xe000ed04 ) )
#تعریف_کن پورت_NVIC_PENDSVSET_بیت    ( 1UL << 28UL )
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
#تعریف_کن پورت_YIELD_FROM_ISR( x )    پورت_انتها_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
خارجي فراغ v_پورت_Enter_Critical( فراغ );
خارجي فراغ v_پورت_Exit_Critical( فراغ );
#تعریف_کن پورت_مجموعه_وقفه_ماسک_FROM_ISR()         ul_پورت_Raise_BASEPRI()
#تعریف_کن پورت_CLEAR_وقفه_ماسک_FROM_ISR( x )    v_پورت_مجموعه_BASEPRI( x )
#تعریف_کن پورت_DISABLE_INTERRUPTS()                  v_پورت_Raise_BASEPRI()
#تعریف_کن پورت_ENABLE_INTERRUPTS()                   v_پورت_مجموعه_BASEPRI( 0 )
#تعریف_کن پورت_ENTER_CRITICAL()                      v_پورت_Enter_Critical()
#تعریف_کن پورت_EXIT_CRITICAL()                       v_پورت_Exit_Critical()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
#تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#اگر_تعریف_نشده پورت_SUPPRESS_TICKS_AND_SLEEP
    خارجي فراغ v_پورت_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_زمان );
    #تعریف_کن پورت_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_زمان )    v_پورت_Suppress_Ticks_And_Sleep( x_Expected_Idle_زمان )
#پایان_اگر
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#اگر_تعریف_نشده config_USE_پورت_OPTIMISED_TASK_SELECTION
    #تعریف_کن config_USE_پورت_OPTIMISED_TASK_SELECTION    1
#پایان_اگر

#إذا config_USE_پورت_OPTIMISED_TASK_SELECTION == 1

/* Generic helper function. */
    __attribute__( ( always_inline ) ) ساكن مضمن uint8_t uc_پورت_شمار_Leading_Zeros( uint32_t ulBitmap )
    {
        uint8_t ucReturn;

        __asm متطاير ( "clz %0, %1" : "=r" ( ucReturn ) : "r" ( ulBitmap ) : "memory" );

        أرجع ucReturn;
    }

/* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #خطا config_USE_پورت_OPTIMISED_TASK_SELECTION can only be مجموعه مقصد 1 when configMAX_PRIORITIES is less than or equal مقصد 32.  It is very rare that a system requires بیشتر than 10 مقصد 15 difference priorities as tasks that share a اولویت will time برش.
    #پایان_اگر

/* Store/clear the ready priorities in a bit map. */
    #تعریف_کن پورت_رکورد_READY_اولویت( ux_اولویت, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_اولویت ) )
    #تعریف_کن پورت_RESET_READY_اولویت( ux_اولویت, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_اولویت ) )

/*-----------------------------------------------------------*/

    #تعریف_کن پورت_GET_HIGHEST_اولویت( ux_بالاترین_اولویت, uxReadyPriorities )    ux_بالاترین_اولویت = ( 31UL - ( uint32_t ) uc_پورت_شمار_Leading_Zeros( ( uxReadyPriorities ) ) )

#پایان_اگر /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/*-----------------------------------------------------------*/

#إذا ( configASSERT_DEFINED == 1 )
    فراغ v_پورت_Validate_وقفه_اولویت( فراغ );
    #تعریف_کن پورت_ASSERT_IF_وقفه_اولویت_INVALID()    v_پورت_Validate_وقفه_اولویت()
#پایان_اگر

/* portNOP() is not required by this port. */
#تعریف_کن پورت_NOP()

#تعریف_کن پورت_INLINE              __inline

#اگر_تعریف_نشده پورت_FORCE_INLINE
    #تعریف_کن پورت_FORCE_INLINE    مضمن __attribute__( ( always_inline ) )
#پایان_اگر

پورت_FORCE_INLINE ساكن پایه_Type_t x_پورت_Is_Inside_وقفه( فراغ )
{
    uint32_t ul_Current_وقفه;
    پایه_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
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

پورت_FORCE_INLINE ساكن فراغ v_پورت_Raise_BASEPRI( فراغ )
{
    uint32_t ulNewBASEPRI;

    __asm متطاير
    (
        "   mov %0, %1                                              \n" \
        "   msr basepri, %0                                         \n" \
        "   isb                                                     \n" \
        "   dsb                                                     \n" \
        : "=r" ( ulNewBASEPRI ) : "i" ( config_MAX_SYSCALL_وقفه_اولویت ) : "memory"
    );
}

/*-----------------------------------------------------------*/

پورت_FORCE_INLINE ساكن uint32_t ul_پورت_Raise_BASEPRI( فراغ )
{
    uint32_t ulOriginalBASEPRI, ulNewBASEPRI;

    __asm متطاير
    (
        "   mrs %0, basepri                                         \n" \
        "   mov %1, %2                                              \n" \
        "   msr basepri, %1                                         \n" \
        "   isb                                                     \n" \
        "   dsb                                                     \n" \
        : "=r" ( ulOriginalBASEPRI ), "=r" ( ulNewBASEPRI ) : "i" ( config_MAX_SYSCALL_وقفه_اولویت ) : "memory"
    );

    /* This return will not be reached but is necessary to prevent compiler
     * warnings. */
    أرجع ulOriginalBASEPRI;
}
/*-----------------------------------------------------------*/

پورت_FORCE_INLINE ساكن فراغ v_پورت_مجموعه_BASEPRI( uint32_t ul_New_ماسک_مقدار )
{
    __asm متطاير
    (
        "   msr basepri, %0 " ::"r" ( ul_New_ماسک_مقدار ) : "memory"
    );
}
/*-----------------------------------------------------------*/

#تعریف_کن پورت_حافظه_BARRIER()    __asm متطاير ( "" ::: "memory" )

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */
