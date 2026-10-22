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

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    బాహ్య "C" {
#అయితే_ముగింపు
/* *INDENT-ON* */

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
#నిర్వచించు పోర్టు_CHAR          అక్షరం
#నిర్వచించు పోర్టు_FLOAT         దశాంశం
#నిర్వచించు పోర్టు_DOUBLE        ద్విగుణ
#నిర్వచించు పోర్టు_LONG          దీర్ఘ
#నిర్వచించు పోర్టు_SHORT         పొట్టి
#నిర్వచించు పోర్టు_దొంతర_TYPE    uint32_t
#నిర్వచించు పోర్టు_పునాది_TYPE     దీర్ఘ

రకనిర్వచనం పోర్టు_దొంతర_TYPE   దొంతర_Type_t;
రకనిర్వచనం దీర్ఘ             పునాది_Type_t;
రకనిర్వచనం గుర్తులేని దీర్ఘ    UBaseType_t;

రకనిర్వచనం uint32_t         TickType_t;
#నిర్వచించు పోర్టు_MAX_DELAY    ( ( TickType_t ) 0xffffffffUL )

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#నిర్వచించు పోర్టు_దొంతర_GROWTH      ( -1 )
#నిర్వచించు పోర్టు_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT    32

/*-----------------------------------------------------------*/

/* Task utilities. */

/* The interrupt priority (for vectors 16 to 255) is determined using vector/16.
 * The quotient is rounded to the nearest integer with 1 being the lowest priority
 * and 15 is the highest.  Therefore the following two interrupts are at the lowest
 * priority.  *NOTE 1* If the yield vector is changed then it must also be changed
 * in the portYIELD_INTERRUPT definition immediately below. */
#నిర్వచించు పోర్టు_APIC_TIMER_INT_సదిశ       ( 0x21 )
#నిర్వచించు పోర్టు_APIC_YIELD_INT_సదిశ       ( 0x20 )

/* Build yield interrupt instruction. */
#నిర్వచించు పోర్టు_YIELD_అంతరాయం             "int $0x20"

/* APIC register addresses. */
#నిర్వచించు పోర్టు_APIC_EOI                    ( *( ( అస్థిర uint32_t * ) 0xFEE000B0UL ) )

/* APIC bit definitions. */
#నిర్వచించు పోర్టు_APIC_ENABLE_బిట్టు             ( 1UL << 8UL )
#నిర్వచించు పోర్టు_APIC_TIMER_PERIODIC         ( 1UL << 17UL )
#నిర్వచించు పోర్టు_APIC_DISABLE                ( 1UL << 16UL )
#నిర్వచించు పోర్టు_APIC_NMI                    ( 4 << 8 )
#నిర్వచించు పోర్టు_APIC_DIV_16                 ( 0x03 )

/* Define local API register addresses. */
#నిర్వచించు పోర్టు_APIC_ID_రిజిస్టరు            ( *( ( అస్థిర uint32_t * ) ( config_APIC_పునాది + 0x20UL ) ) )
#నిర్వచించు పోర్టు_APIC_SPURIOUS_INT           ( *( ( అస్థిర uint32_t * ) ( config_APIC_పునాది + 0xF0UL ) ) )
#నిర్వచించు పోర్టు_APIC_LVT_TIMER              ( *( ( అస్థిర uint32_t * ) ( config_APIC_పునాది + 0x320UL ) ) )
#నిర్వచించు పోర్టు_APIC_TIMER_INITIAL_లెక్క    ( *( ( అస్థిర uint32_t * ) ( config_APIC_పునాది + 0x380UL ) ) )
#నిర్వచించు పోర్టు_APIC_TIMER_CURRENT_లెక్క    ( *( ( అస్థిర uint32_t * ) ( config_APIC_పునాది + 0x390UL ) ) )
#నిర్వచించు పోర్టు_APIC_TASK_ప్రాధాన్యత          ( *( ( అస్థిర uint32_t * ) ( config_APIC_పునాది + 0x80UL ) ) )
#నిర్వచించు పోర్టు_APIC_LVT_ERROR              ( *( ( అస్థిర uint32_t * ) ( config_APIC_పునాది + 0x370UL ) ) )
#నిర్వచించు పోర్టు_APIC_ERROR_స్థితి           ( *( ( అస్థిర uint32_t * ) ( config_APIC_పునాది + 0x280UL ) ) )
#నిర్వచించు పోర్టు_APIC_LDR                    ( *( ( అస్థిర uint32_t * ) ( config_APIC_పునాది + 0xD0UL ) ) )
#నిర్వచించు పోర్టు_APIC_TMRDIV                 ( *( ( అస్థిర uint32_t * ) ( config_APIC_పునాది + 0x3E0UL ) ) )
#నిర్వచించు పోర్టు_APIC_LVT_PERF               ( *( ( అస్థిర uint32_t * ) ( config_APIC_పునాది + 0x340UL ) ) )
#నిర్వచించు పోర్టు_APIC_LVT_LINT0              ( *( ( అస్థిర uint32_t * ) ( config_APIC_పునాది + 0x350UL ) ) )
#నిర్వచించు పోర్టు_APIC_LVT_LINT1              ( *( ( అస్థిర uint32_t * ) ( config_APIC_పునాది + 0x360UL ) ) )

/* Don't yield if inside a critical section - instead hold the yield pending
 * so it is performed when the critical section is exited. */
#నిర్వచించు పోర్టు_YIELD()                                  \
    {                                                \
        బాహ్య అస్థిర uint32_t ulCriticalNesting;  \
        బాహ్య అస్థిర uint32_t ul_పోర్టు_Yield_Pending; \
        ఒకవేళ( ulCriticalNesting != 0 )                 \
        {                                            \
            ul_పోర్టు_Yield_Pending = pdTRUE;             \
        }                                            \
        లేకపోతే                                         \
        {                                            \
            __asm అస్థిర ( పోర్టు_YIELD_అంతరాయం );  \
        }                                            \
    }

/* Called at the end of an ISR that can cause a context switch - pend a yield if
 * xSwitchRequired is not false. */
#నిర్వచించు పోర్టు_చివర_SWITCHING_ISR( xSwitchRequired )     \
    {                                                \
        బాహ్య అస్థిర uint32_t ul_పోర్టు_Yield_Pending; \
        ఒకవేళ( xSwitchRequired != pdFALSE )             \
        {                                            \
            ul_పోర్టు_Yield_Pending = 1;                  \
        }                                            \
    }

/* Same as portEND_SWITCHING_ISR() - take your pick which name to use. */
#నిర్వచించు పోర్టు_YIELD_FROM_ISR( x )    పోర్టు_చివర_SWITCHING_ISR( x )

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

/* Critical sections for use in interrupts. */
#నిర్వచించు పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR()         ul_పోర్టు_సమితి_అంతరాయం_ముసుగు()
#నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( x )    v_పోర్టు_Clear_అంతరాయం_ముసుగు( x )

బాహ్య శూన్య v_పోర్టు_Enter_Critical( శూన్య );
బాహ్య శూన్య v_పోర్టు_Exit_Critical( శూన్య );
బాహ్య uint32_t ul_పోర్టు_సమితి_అంతరాయం_ముసుగు( శూన్య );
బాహ్య శూన్య v_పోర్టు_Clear_అంతరాయం_ముసుగు( uint32_t ul_New_ముసుగు_విలువ );

/* These macros do not globally disable/enable interrupts.  They do mask off
 * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
#నిర్వచించు పోర్టు_ENTER_CRITICAL()        v_పోర్టు_Enter_Critical()
#నిర్వచించు పోర్టు_EXIT_CRITICAL()         v_పోర్టు_Exit_Critical()
#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()    __asm అస్థిర ( "cli" )
#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()     __asm అస్థిర ( "sti" )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )

/* Architecture specific optimisations. */
#ఒకవేళ config_USE_పోర్టు_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
    #నిర్వచించు పోర్టు_GET_HIGHEST_ప్రాధాన్యత( ux_శిఖరం_ప్రాధాన్యత, uxReadyPriorities ) \
    __asm అస్థిర ( "bsr %1, %0\n\t"                                    \
                     : "=r" ( ux_శిఖరం_ప్రాధాన్యత ) : "rm" ( uxReadyPriorities ) : "cc" )

    #నిర్వచించు పోర్టు_రికార్డు_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ప్రాధాన్యత ) )
    #నిర్వచించు పోర్టు_RESET_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ప్రాధాన్యత ) )

#అయితే_ముగింపు /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#నిర్వచించు పోర్టు_NOP()    __asm అస్థిర ( "NOP" )

/*-----------------------------------------------------------
* Misc
*----------------------------------------------------------*/

#నిర్వచించు పోర్టు_అంకె_VECTORS     256
#నిర్వచించు పోర్టు_MAX_ప్రాధాన్యత    15
రకనిర్వచనం శూన్య ( * ISR_Handler_t ) ( శూన్య );

/* Any task that uses the floating point unit MUST call vPortTaskUsesFPU()
 * before any floating point instructions are executed. */
#నిర్వచితం_కాకపోతే configSUPPORT_FPU
    #నిర్వచించు configSUPPORT_FPU    0
#అయితే_ముగింపు

#ఒకవేళ configSUPPORT_FPU == 1
    శూన్య v_పోర్టు_Task_ఉపయోగిస్తుంది_FPU( శూన్య );
    #నిర్వచించు పోర్టు_TASK_ఉపయోగిస్తుంది_FLOATING_బిందువు()    v_పోర్టు_Task_ఉపయోగిస్తుంది_FPU()
#అయితే_ముగింపు

/* See the comments under the configUSE_COMMON_INTERRUPT_ENTRY_POINT definition
 * below. */
పునాది_Type_t x_పోర్టు_రిజిస్టరు_CInterrupt_Handler( ISR_Handler_t pxHandler,
                                           uint32_t ul_సదిశ_సంఖ్య );
పునాది_Type_t x_పోర్టు_Install_అంతరాయం_Handler( ISR_Handler_t pxHandler,
                                         uint32_t ul_సదిశ_సంఖ్య );

#నిర్వచితం_కాకపోతే config_APIC_పునాది

/* configAPIC_BASE_ADDRESS sets the base address of the local APIC.  It can
 * be overridden in FreeRTOSConfig.h should it not be constant. */
    #నిర్వచించు config_APIC_పునాది    0xFEE00000UL
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే config_USE_పోర్టు_OPTIMISED_TASK_SELECTION

/* The FreeRTOS scheduling algorithm selects the task that will enter the
 * Running state.  configUSE_PORT_OPTIMISED_TASK_SELECTION is used to set how
 * that is done.
 *
 * If configUSE_PORT_OPTIMISED_TASK_SELECTION is set to 0 then the task to
 * enter the Running state is selected using a portable algorithm written in
 * C.  This is the slowest method, but the algorithm does not restrict the
 * maximum number of unique RTOS task priorities that are available.
 *
 * If configUSE_PORT_OPTIMISED_TASK_SELECTION is set to 1 then the task to
 * enter the Running state is selected using a single assembly instruction.
 * This is the fastest method, but restricts the maximum number of unique RTOS
 * task priorities to 32 (the same task priority can be assigned to any number
 * of RTOS tasks). */
    #warning config_USE_పోర్టు_OPTIMISED_TASK_SELECTION was not defined లోపల FreeRTOSConfig.h and has been defaulted గమ్యం 1
    #నిర్వచించు config_USE_పోర్టు_OPTIMISED_TASK_SELECTION    1
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే config_USE_COMMON_అంతరాయం_నమోదు_బిందువు

/* There are two ways of implementing interrupt handlers:
 *
 *  1) As standard C functions -
 *
 *  This method can only be used if configUSE_COMMON_INTERRUPT_ENTRY_POINT
 *  is set to 1.  The C function is installed using
 *  xPortRegisterCInterruptHandler().
 *
 *  This is the simplest of the two methods but incurs a slightly longer
 *  interrupt entry time.
 *
 *  2) By using an assembly stub that wraps the handler in the FreeRTOS
 *     portFREERTOS_INTERRUPT_ENTRY and portFREERTOS_INTERRUPT_EXIT macros.
 *
 *  This method can always be used.  It is slightly more complex than
 *  method 1 but benefits from a faster interrupt entry time. */
    #warning config_USE_COMMON_అంతరాయం_నమోదు_బిందువు was not defined లోపల FreeRTOSConfig.h and has been defaulted గమ్యం 1.
    #నిర్వచించు config_USE_COMMON_అంతరాయం_నమోదు_బిందువు    1
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే config_ISR_దొంతర_కొలత

/* Interrupt entry code will switch the stack in use to a dedicated system
 * stack.
 *
 * configISR_STACK_SIZE defines the number of 32-bit values that can be stored
 * on the system stack, and must be large enough to hold a potentially nested
 * interrupt stack frame. */

    #దోషం config_ISR_దొంతర_కొలత was not defined లోపల FreeRTOSConfig.h.
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత

/* Interrupt safe FreeRTOS functions (those that end in "FromISR" must not
 * be called from an interrupt that has a priority above that set by
 * configMAX_API_CALL_INTERRUPT_PRIORITY.  */
    #warning config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత was not defined లోపల FreeRTOSConfig.h and has been defaulted గమ్యం 10
    #నిర్వచించు config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత    10
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే configSUPPORT_FPU
    #warning configSUPPORT_FPU was not defined లోపల FreeRTOSConfig.h and has been defaulted గమ్యం 0
    #నిర్వచించు configSUPPORT_FPU    0
#అయితే_ముగింపు

/* The value written to the task priority register to raise the interrupt mask
 * to the maximum from which FreeRTOS API calls can be made. */
#నిర్వచించు పోర్టు_APIC_ప్రాధాన్యత_జరుపు        ( 4UL )
#నిర్వచించు పోర్టు_APIC_MAX_SUB_ప్రాధాన్యత      ( 0x0fUL )
#నిర్వచించు పోర్టు_MAX_API_CALL_ప్రాధాన్యత      ( ( config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత << పోర్టు_APIC_ప్రాధాన్యత_జరుపు ) | పోర్టు_APIC_MAX_SUB_ప్రాధాన్యత )

/* Asserts if interrupt safe FreeRTOS functions are called from a priority
 * above the max system call interrupt priority. */
#నిర్వచించు పోర్టు_APIC_PROCESSOR_ప్రాధాన్యత    ( *( ( అస్థిర uint32_t * ) ( config_APIC_పునాది + 0xA0UL ) ) )
#నిర్వచించు పోర్టు_ASSERT_IF_అంతరాయం_ప్రాధాన్యత_INVALID()    configASSERT( ( పోర్టు_APIC_PROCESSOR_ప్రాధాన్యత ) <= ( పోర్టు_MAX_API_CALL_ప్రాధాన్యత ) )

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
