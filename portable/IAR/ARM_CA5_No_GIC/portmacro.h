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

/* IAR includes. */
#اگر_تعریف_شده __ICCARM__

    #ضمن <intrinsics.h>



/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the given hardware
 * and compiler.
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

    تعريفنوع uint32_t         TickType_t;
    #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کن پورت_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
    #تعریف_کن پورت_پشته_GROWTH      ( -1 )
    #تعریف_کن پورت_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
    #تعریف_کن پورت_BYTE_ALIGNMENT    8

/*-----------------------------------------------------------*/

/* Task utilities. */

/* Called at the end of an ISR that can cause a context switch. */
    #تعریف_کن پورت_انتها_SWITCHING_ISR( xSwitchRequired ) \
    {                                                \
        خارجي uint32_t ul_پورت_Yield_Required;         \
                                                     \
        إذا( xSwitchRequired != pdFALSE )             \
        {                                            \
            ul_پورت_Yield_Required = pdTRUE;            \
        }                                            \
    }

    #تعریف_کن پورت_YIELD_FROM_ISR( x )    پورت_انتها_SWITCHING_ISR( x )
    #تعریف_کن پورت_YIELD()                __asm متطاير ( "SWI 0" ); __ISB()


/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

    خارجي فراغ v_پورت_Enter_Critical( فراغ );
    خارجي فراغ v_پورت_Exit_Critical( فراغ );
    خارجي uint32_t ul_پورت_مجموعه_وقفه_ماسک( فراغ );
    خارجي فراغ v_پورت_Clear_وقفه_ماسک( uint32_t ul_New_ماسک_مقدار );

    #تعریف_کن پورت_ENTER_CRITICAL()                      v_پورت_Enter_Critical();
    #تعریف_کن پورت_EXIT_CRITICAL()                       v_پورت_Exit_Critical();
    #تعریف_کن پورت_DISABLE_INTERRUPTS()                  __disable_irq(); __DSB(); __ISB()        /* No priority mask register so global disable is used. */
    #تعریف_کن پورت_ENABLE_INTERRUPTS()                   __enable_irq()
    #تعریف_کن پورت_مجموعه_وقفه_ماسک_FROM_ISR()         __get_interrupt_state(); __disable_irq() /* No priority mask register so global disable is used. */
    #تعریف_کن پورت_CLEAR_وقفه_ماسک_FROM_ISR( x )    __set_interrupt_state( x )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
    #تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
    #تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* Prototype of the FreeRTOS tick handler.  This must be installed as the
 * handler for whichever peripheral is used to generate the RTOS tick. */
    فراغ FreeRTOS_Tick_Handler( فراغ );

/* Any task that uses the floating point unit MUST call vPortTaskUsesFPU()
 * before any floating point instructions are executed. */
    فراغ v_پورت_Task_استفاده_میکند_FPU( فراغ );
    #تعریف_کن پورت_TASK_استفاده_میکند_FLOATING_نقطه()    v_پورت_Task_استفاده_میکند_FPU()

/* Architecture specific optimisations. */
    #اگر_تعریف_نشده config_USE_پورت_OPTIMISED_TASK_SELECTION
        #تعریف_کن config_USE_پورت_OPTIMISED_TASK_SELECTION    1
    #پایان_اگر

    #إذا config_USE_پورت_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
        #تعریف_کن پورت_رکورد_READY_اولویت( ux_اولویت, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_اولویت ) )
        #تعریف_کن پورت_RESET_READY_اولویت( ux_اولویت, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_اولویت ) )

/*-----------------------------------------------------------*/

        #تعریف_کن پورت_GET_HIGHEST_اولویت( ux_بالاترین_اولویت, uxReadyPriorities )    ux_بالاترین_اولویت = ( 31 - __CLZ( uxReadyPriorities ) )

    #پایان_اگر /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

    #تعریف_کن پورت_NOP()    __asm متطاير ( "NOP" )

/* Suppress warnings that are generated by the IAR tools, but cannot be
 * fixed in the source code because to do so would cause other compilers to
 * generate warnings. */
    #رهنمود diag_suppress=Pe191
    #رهنمود diag_suppress=Pa082

#پایان_اگر /* __ICCARM__ */

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */
