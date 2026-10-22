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

/* The compiler needs to be told functions that are only referenced by pointer
 * are to be included in the build.  NOTE:  Omitting these lines will result in a
 * run-time crash, not a linker error! */
    #ہدایت funcall v_Task_شروع_Scheduler prvIdleTask
    #ہدایت funcall xTimerCreateTimerTask prvTimerTask

/* Type definitions. */
    #تعریف_کرو پورٹ_CHAR          حرف
    #تعریف_کرو پورٹ_FLOAT         عائم
    #تعریف_کرو پورٹ_DOUBLE        مزدوج
    #تعریف_کرو پورٹ_LONG          لما
    #تعریف_کرو پورٹ_SHORT         چھوٹا
    #تعریف_کرو پورٹ_ڈھیر_TYPE    uint32_t
    #تعریف_کرو پورٹ_ادھار_TYPE     لما

    تعريفنوع پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
    تعريفنوع لما             ادھار_Type_t;
    تعريفنوع بنانشانی لما    UBaseType_t;

    #إذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
        تعريفنوع uint16_t     TickType_t;
        #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffff
    #وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
        تعريفنوع uint32_t     TickType_t;
        #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
        #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
    #وإلا
        #غلطی config_TICK_TYPE_چوڑائی_وچ_بٹ سیٹ منزل unsupported tick type چوڑائی.
    #جے_انت
/*-----------------------------------------------------------*/

/* Architecture specifics. */
    #تعریف_کرو پورٹ_ڈھیر_GROWTH      ( -1 )
    #تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
    #تعریف_کرو پورٹ_BYTE_ALIGNMENT    8
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
    #تعریف_کرو پورٹ_YIELD()                                 \
    {                                                   \
        /* Set a PendSV to request a context switch. */ \
        پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ; \
                                                        \
        /* Barriers are normally not required but do ensure the code is completely \
         * within the specified behaviour for the architecture. */ \
        __asm{ dsb };                                              \
        __asm{ isb };                                              \
    }

#تعریف_کرو پورٹ_NVIC_INT_CTRL_REG     ( *( ( متطاير uint32_t * ) 0xe000ed04 ) )
#تعریف_کرو پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ    ( 1UL << 28UL )
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
#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )    پورٹ_سرا_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
    خارجي فراغ v_پورٹ_Enter_Critical( فراغ );
    خارجي فراغ v_پورٹ_Exit_Critical( فراغ );
    #تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                  CPU_REG_سیٹ( CPU_BASEPRI, config_MAX_SYSCALL_رکاوٹ_ترجیح ); __asm{ dsb }; __asm{ isb }
    #تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                   CPU_REG_سیٹ( CPU_BASEPRI, 0 );
    #تعریف_کرو پورٹ_ENTER_CRITICAL()                      v_پورٹ_Enter_Critical()
    #تعریف_کرو پورٹ_EXIT_CRITICAL()                       v_پورٹ_Exit_Critical()
    #تعریف_کرو پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR()         ul_پورٹ_Raise_BASEPRI()
    #تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( x )    CPU_REG_سیٹ( CPU_BASEPRI, x ); /* Barrier instructions not used as this is only used to lower the basepri. */

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
    #تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
    #تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
    #جے_بنا_تعریف پورٹ_SUPPRESS_TICKS_AND_SLEEP
        خارجي فراغ v_پورٹ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ویلا );
        #تعریف_کرو پورٹ_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_ویلا )    v_پورٹ_Suppress_Ticks_And_Sleep( x_Expected_Idle_ویلا )
    #جے_انت
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
    #جے_بنا_تعریف config_USE_پورٹ_OPTIMISED_TASK_SELECTION
        #تعریف_کرو config_USE_پورٹ_OPTIMISED_TASK_SELECTION    1
    #جے_انت

    #إذا config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1

/* Generic helper function. */
        __attribute__( ( always_inline ) ) ساكن مضمن uint8_t uc_پورٹ_گنتی_Leading_Zeros( uint32_t ulBitmap )
        {
            uint8_t ucReturn;

            __asm متطاير ( "clz %0, %1" : "=r" ( ucReturn ) : "r" ( ulBitmap ) );

            أرجع ucReturn;
        }

/* Check the configuration. */
        #إذا ( configMAX_PRIORITIES > 32 )
            #غلطی config_USE_پورٹ_OPTIMISED_TASK_SELECTION can only be سیٹ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires ہور than 10 منزل 15 difference priorities as tasks that share a ترجیح will time ٹکڑا.
        #جے_انت

/* Store/clear the ready priorities in a bit map. */
        #تعریف_کرو پورٹ_ریکارڈ_READY_ترجیح( ux_ترجیح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجیح ) )
        #تعریف_کرو پورٹ_RESET_READY_ترجیح( ux_ترجیح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجیح ) )

/*-----------------------------------------------------------*/

        #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities )    ux_چوٹی_ترجیح = ( 31UL - ( uint32_t ) uc_پورٹ_گنتی_Leading_Zeros( ( uxReadyPriorities ) ) )

    #جے_انت /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/*-----------------------------------------------------------*/

    #إذا ( configASSERT_DEFINED == 1 )
        فراغ v_پورٹ_Validate_رکاوٹ_ترجیح( فراغ );
        #تعریف_کرو پورٹ_ASSERT_IF_رکاوٹ_ترجیح_INVALID()    v_پورٹ_Validate_رکاوٹ_ترجیح()
    #جے_انت

/* portNOP() is not required by this port. */
    #تعریف_کرو پورٹ_NOP()

    ادھار_Type_t x_پورٹ_Is_Inside_رکاوٹ( فراغ );

/*-----------------------------------------------------------*/

    ساكن مضمن uint32_t ul_پورٹ_Raise_BASEPRI( فراغ )
    {
        uint32_t ulOriginalBASEPRI;

        ulOriginalBASEPRI = CPU_REG_GET( CPU_BASEPRI );
        CPU_REG_سیٹ( CPU_BASEPRI, config_MAX_SYSCALL_رکاوٹ_ترجیح );
        __asm{ dsb };
        __asm{ isb };
        أرجع ulOriginalBASEPRI;
    }
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    }
#جے_انت
/* *INDENT-ON* */

#جے_انت /* PORTMACRO_H */
