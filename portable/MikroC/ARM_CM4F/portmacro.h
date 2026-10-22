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

/* The compiler needs to be told functions that are only referenced by pointer
 * are to be included in the build.  NOTE:  Omitting these lines will result in a
 * run-time crash, not a linker error! */
    #لارښوونه funcall v_Task_پیل_Scheduler prvIdleTask
    #لارښوونه funcall xTimerCreateTimerTask prvTimerTask

/* Type definitions. */
    #تعریف_کړه پورټ_CHAR          حرف
    #تعریف_کړه پورټ_FLOAT         عائم
    #تعریف_کړه پورټ_DOUBLE        مزدوج
    #تعریف_کړه پورټ_LONG          اوږد
    #تعریف_کړه پورټ_SHORT         لنډ
    #تعریف_کړه پورټ_ډېری_TYPE    uint32_t
    #تعریف_کړه پورټ_بنسټ_TYPE     اوږد

    تعريفنوع پورټ_ډېری_TYPE   ډېری_Type_t;
    تعريفنوع اوږد             بنسټ_Type_t;
    تعريفنوع بینښه اوږد    UBaseType_t;

    #إذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
        تعريفنوع uint16_t     TickType_t;
        #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffff
    #وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
        تعريفنوع uint32_t     TickType_t;
        #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
        #تعریف_کړه پورټ_TICK_TYPE_IS_ATOMIC    1
    #وإلا
        #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
    #د_که_پای
/*-----------------------------------------------------------*/

/* Architecture specifics. */
    #تعریف_کړه پورټ_ډېری_GROWTH      ( -1 )
    #تعریف_کړه پورټ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
    #تعریف_کړه پورټ_BYTE_ALIGNMENT    8
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
    #تعریف_کړه پورټ_YIELD()                                 \
    {                                                   \
        /* Set a PendSV to request a context switch. */ \
        پورټ_NVIC_INT_CTRL_REG = پورټ_NVIC_PENDSVSET_بټ; \
                                                        \
        /* Barriers are normally not required but do ensure the code is completely \
         * within the specified behaviour for the architecture. */ \
        __asm{ dsb };                                              \
        __asm{ isb };                                              \
    }

#تعریف_کړه پورټ_NVIC_INT_CTRL_REG     ( *( ( متطاير uint32_t * ) 0xe000ed04 ) )
#تعریف_کړه پورټ_NVIC_PENDSVSET_بټ    ( 1UL << 28UL )
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
#تعریف_کړه پورټ_YIELD_FROM_ISR( x )    پورټ_پای_ټکی_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
    خارجي فراغ v_پورټ_Enter_Critical( فراغ );
    خارجي فراغ v_پورټ_Exit_Critical( فراغ );
    #تعریف_کړه پورټ_DISABLE_INTERRUPTS()                  CPU_REG_سېټ( CPU_BASEPRI, config_MAX_SYSCALL_مداخله_لومړیتوب ); __asm{ dsb }; __asm{ isb }
    #تعریف_کړه پورټ_ENABLE_INTERRUPTS()                   CPU_REG_سېټ( CPU_BASEPRI, 0 );
    #تعریف_کړه پورټ_ENTER_CRITICAL()                      v_پورټ_Enter_Critical()
    #تعریف_کړه پورټ_EXIT_CRITICAL()                       v_پورټ_Exit_Critical()
    #تعریف_کړه پورټ_سېټ_مداخله_ماسک_FROM_ISR()         ul_پورټ_Raise_BASEPRI()
    #تعریف_کړه پورټ_CLEAR_مداخله_ماسک_FROM_ISR( x )    CPU_REG_سېټ( CPU_BASEPRI, x ); /* Barrier instructions not used as this is only used to lower the basepri. */

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
    #تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
    #تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
    #که_نه_تعریف_شوی پورټ_SUPPRESS_TICKS_AND_SLEEP
        خارجي فراغ v_پورټ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وخت );
        #تعریف_کړه پورټ_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_وخت )    v_پورټ_Suppress_Ticks_And_Sleep( x_Expected_Idle_وخت )
    #د_که_پای
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
    #که_نه_تعریف_شوی config_USE_پورټ_OPTIMISED_TASK_SELECTION
        #تعریف_کړه config_USE_پورټ_OPTIMISED_TASK_SELECTION    1
    #د_که_پای

    #إذا config_USE_پورټ_OPTIMISED_TASK_SELECTION == 1

/* Generic helper function. */
        __attribute__( ( always_inline ) ) ساكن مضمن uint8_t uc_پورټ_شمېر_Leading_Zeros( uint32_t ulBitmap )
        {
            uint8_t ucReturn;

            __asm متطاير ( "clz %0, %1" : "=r" ( ucReturn ) : "r" ( ulBitmap ) );

            أرجع ucReturn;
        }

/* Check the configuration. */
        #إذا ( configMAX_PRIORITIES > 32 )
            #تېروتنه config_USE_پورټ_OPTIMISED_TASK_SELECTION can only be سېټ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires نور than 10 منزل 15 difference priorities as tasks that share a لومړیتوب will time ټوټه.
        #د_که_پای

/* Store/clear the ready priorities in a bit map. */
        #تعریف_کړه پورټ_ریکارډ_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_لومړیتوب ) )
        #تعریف_کړه پورټ_RESET_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_لومړیتوب ) )

/*-----------------------------------------------------------*/

        #تعریف_کړه پورټ_GET_HIGHEST_لومړیتوب( ux_سر_لومړیتوب, uxReadyPriorities )    ux_سر_لومړیتوب = ( 31UL - ( uint32_t ) uc_پورټ_شمېر_Leading_Zeros( ( uxReadyPriorities ) ) )

    #د_که_پای /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/*-----------------------------------------------------------*/

    #إذا ( configASSERT_DEFINED == 1 )
        فراغ v_پورټ_Validate_مداخله_لومړیتوب( فراغ );
        #تعریف_کړه پورټ_ASSERT_IF_مداخله_لومړیتوب_INVALID()    v_پورټ_Validate_مداخله_لومړیتوب()
    #د_که_پای

/* portNOP() is not required by this port. */
    #تعریف_کړه پورټ_NOP()

    بنسټ_Type_t x_پورټ_Is_Inside_مداخله( فراغ );

/*-----------------------------------------------------------*/

    ساكن مضمن uint32_t ul_پورټ_Raise_BASEPRI( فراغ )
    {
        uint32_t ulOriginalBASEPRI;

        ulOriginalBASEPRI = CPU_REG_GET( CPU_BASEPRI );
        CPU_REG_سېټ( CPU_BASEPRI, config_MAX_SYSCALL_مداخله_لومړیتوب );
        __asm{ dsb };
        __asm{ isb };
        أرجع ulOriginalBASEPRI;
    }
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
