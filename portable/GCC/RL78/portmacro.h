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

#నిర్వచితం_కాకపోతే PORTMACRO_H
#నిర్వచించు PORTMACRO_H

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

#నిర్వచించు పోర్టు_CHAR                 అక్షరం
#నిర్వచించు పోర్టు_FLOAT                దశాంశం
#నిర్వచించు పోర్టు_DOUBLE               ద్విగుణ
#నిర్వచించు పోర్టు_LONG                 దీర్ఘ
#నిర్వచించు పోర్టు_SHORT                పొట్టి
#నిర్వచించు పోర్టు_దొంతర_TYPE           uint16_t
#నిర్వచించు పోర్టు_పునాది_TYPE            పొట్టి
#నిర్వచించు పోర్టు_సూచిక_కొలత_TYPE    uint16_t

రకనిర్వచనం పోర్టు_దొంతర_TYPE   దొంతర_Type_t;
రకనిర్వచనం పొట్టి            పునాది_Type_t;
రకనిర్వచనం గుర్తులేని పొట్టి   UBaseType_t;

#ఒకవేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_16_బిట్లు )
    రకనిర్వచనం uint16_t     TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) 0xffff
#లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_32_బిట్లు )
    రకనిర్వచనం uint32_t     TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#లేకపోతే
    #దోషం config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు సమితి గమ్యం unsupported tick type వెడల్పు.
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

/* Interrupt control macros. */
#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()    __asm అస్థిర ( "DI" )
#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()     __asm అస్థిర ( "EI" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
#నిర్వచించు పోర్టు_NO_CRITICAL_SECTION_NESTING    ( ( గుర్తులేని పొట్టి ) 0 )

#నిర్వచించు పోర్టు_ENTER_CRITICAL()                                                      \
    {                                                                             \
        బాహ్య అస్థిర uint16_t usCriticalNesting;                               \
                                                                                  \
        పోర్టు_DISABLE_INTERRUPTS();                                                 \
                                                                                  \
        /* Now that interrupts are disabled, ulCriticalNesting can be accessed */ \
        /* directly.  Increment ulCriticalNesting to keep a count of how many */  \
        /* times portENTER_CRITICAL() has been called. */                         \
        usCriticalNesting++;                                                      \
    }

#నిర్వచించు పోర్టు_EXIT_CRITICAL()                                                         \
    {                                                                               \
        బాహ్య అస్థిర uint16_t usCriticalNesting;                                 \
                                                                                    \
        ఒకవేళ( usCriticalNesting > పోర్టు_NO_CRITICAL_SECTION_NESTING )                   \
        {                                                                           \
            /* Decrement the nesting count as we are leaving a critical section. */ \
            usCriticalNesting--;                                                    \
                                                                                    \
            /* If the nesting level has reached zero then interrupts should be */   \
            /* re-enabled. */                                                       \
            ఒకవేళ( usCriticalNesting == పోర్టు_NO_CRITICAL_SECTION_NESTING )              \
            {                                                                       \
                పోర్టు_ENABLE_INTERRUPTS();                                            \
            }                                                                       \
        }                                                                           \
    }
/*-----------------------------------------------------------*/

/* Task utilities. */
#నిర్వచించు పోర్టు_YIELD()                                       __asm అస్థిర ( "BRK" )
#నిర్వచితం_కాకపోతే configREQUIRE_ASM_ISR_WRAPPER
    #నిర్వచించు configREQUIRE_ASM_ISR_WRAPPER    1
#అయితే_ముగింపు
#ఒకవేళ( configREQUIRE_ASM_ISR_WRAPPER == 1 )
    /* You must implement an assembly ISR wrapper (see the below for details) if you need an ISR to cause a context switch.
     * https://www.freertos.org/Documentation/02-Kernel/03-Supported-devices/04-Demos/Renesas/RTOS_RL78_IAR_Demos#writing-interrupt-service-routines */
    #నిర్వచించు పోర్టు_YIELD_FROM_ISR( x_Higher_ప్రాధాన్యత_Task_Woken )    చేయి { ఒకవేళ( x_Higher_ప్రాధాన్యత_Task_Woken != pdFALSE ) vTaskSwitchContext(); } అయితే( 0 )
#లేకపోతే
    /* You must not implement an assembly ISR wrapper even if you need an ISR to cause a context switch.
     * The portYIELD, which is similar to role of an assembly ISR wrapper, runs only when a context switch is required. */
    #నిర్వచించు పోర్టు_YIELD_FROM_ISR( x_Higher_ప్రాధాన్యత_Task_Woken )    చేయి { ఒకవేళ( x_Higher_ప్రాధాన్యత_Task_Woken != pdFALSE ) పోర్టు_YIELD(); } అయితే( 0 )
#అయితే_ముగింపు
#నిర్వచించు పోర్టు_NOP()                                         __asm అస్థిర ( "NOP" )
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT    2
#నిర్వచించు పోర్టు_దొంతర_GROWTH      ( -1 )
#నిర్వచించు పోర్టు_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )

#అయితే_ముగింపు /* PORTMACRO_H */
