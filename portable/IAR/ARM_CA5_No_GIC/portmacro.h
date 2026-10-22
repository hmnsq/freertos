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

#اگر_غیر_تعریف_شدہ PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    خارجی "C" {
#اگر_ختم
/* *INDENT-ON* */

/* IAR includes. */
#اگر_تعریف_شدہ __ICCARM__

    #شامل <intrinsics.h>



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
    #تعریف_کرو پورٹ_CHAR          حرف
    #تعریف_کرو پورٹ_FLOAT         اعشاری
    #تعریف_کرو پورٹ_DOUBLE        دوہرا
    #تعریف_کرو پورٹ_LONG          طویل
    #تعریف_کرو پورٹ_SHORT         مختصر
    #تعریف_کرو پورٹ_ڈھیر_TYPE    uint32_t
    #تعریف_کرو پورٹ_بنیاد_TYPE     طویل

    قسمتعریف پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
    قسمتعریف طویل             بنیاد_Type_t;
    قسمتعریف غیرعلامتی طویل    UBaseType_t;

    قسمتعریف uint32_t         TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
    #تعریف_کرو پورٹ_ڈھیر_GROWTH      ( -1 )
    #تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
    #تعریف_کرو پورٹ_BYTE_ALIGNMENT    8

/*-----------------------------------------------------------*/

/* Task utilities. */

/* Called at the end of an ISR that can cause a context switch. */
    #تعریف_کرو پورٹ_انتہا_SWITCHING_ISR( xSwitchRequired ) \
    {                                                \
        خارجی uint32_t ul_پورٹ_Yield_Required;         \
                                                     \
        اگر( xSwitchRequired != pdFALSE )             \
        {                                            \
            ul_پورٹ_Yield_Required = pdTRUE;            \
        }                                            \
    }

    #تعریف_کرو پورٹ_YIELD_FROM_ISR( x )    پورٹ_انتہا_SWITCHING_ISR( x )
    #تعریف_کرو پورٹ_YIELD()                __asm متلون ( "SWI 0" ); __ISB()


/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

    خارجی خالی v_پورٹ_Enter_Critical( خالی );
    خارجی خالی v_پورٹ_Exit_Critical( خالی );
    خارجی uint32_t ul_پورٹ_سیٹ_مداخلت_نقاب( خالی );
    خارجی خالی v_پورٹ_Clear_مداخلت_نقاب( uint32_t ul_New_نقاب_قدر );

    #تعریف_کرو پورٹ_ENTER_CRITICAL()                      v_پورٹ_Enter_Critical();
    #تعریف_کرو پورٹ_EXIT_CRITICAL()                       v_پورٹ_Exit_Critical();
    #تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                  __disable_irq(); __DSB(); __ISB()        /* No priority mask register so global disable is used. */
    #تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                   __enable_irq()
    #تعریف_کرو پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR()         __get_interrupt_state(); __disable_irq() /* No priority mask register so global disable is used. */
    #تعریف_کرو پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( x )    __set_interrupt_state( x )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
    #تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters )
    #تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )

/* Prototype of the FreeRTOS tick handler.  This must be installed as the
 * handler for whichever peripheral is used to generate the RTOS tick. */
    خالی FreeRTOS_Tick_Handler( خالی );

/* Any task that uses the floating point unit MUST call vPortTaskUsesFPU()
 * before any floating point instructions are executed. */
    خالی v_پورٹ_Task_استعمال_کرتا_FPU( خالی );
    #تعریف_کرو پورٹ_TASK_استعمال_کرتا_FLOATING_نقطہ()    v_پورٹ_Task_استعمال_کرتا_FPU()

/* Architecture specific optimisations. */
    #اگر_غیر_تعریف_شدہ config_USE_پورٹ_OPTIMISED_TASK_SELECTION
        #تعریف_کرو config_USE_پورٹ_OPTIMISED_TASK_SELECTION    1
    #اگر_ختم

    #اگر config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
        #تعریف_کرو پورٹ_ریکارڈ_READY_ترجیح( ux_ترجیح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجیح ) )
        #تعریف_کرو پورٹ_RESET_READY_ترجیح( ux_ترجیح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجیح ) )

/*-----------------------------------------------------------*/

        #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities )    ux_چوٹی_ترجیح = ( 31 - __CLZ( uxReadyPriorities ) )

    #اگر_ختم /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

    #تعریف_کرو پورٹ_NOP()    __asm متلون ( "NOP" )

/* Suppress warnings that are generated by the IAR tools, but cannot be
 * fixed in the source code because to do so would cause other compilers to
 * generate warnings. */
    #ہدایت diag_suppress=Pe191
    #ہدایت diag_suppress=Pa082

#اگر_ختم /* __ICCARM__ */

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    }
#اگر_ختم
/* *INDENT-ON* */

#اگر_ختم /* PORTMACRO_H */
