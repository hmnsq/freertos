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

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the RISC-V port.
 *----------------------------------------------------------*/

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"
#అన్తర్భావ "portmacro.h"

/* Standard includes. */
#అన్తర్భావ "string.h"

#నిర్వచితమైతే config_CLINT_పునాది_చిరునామా
    #warning "The configCLINT_BASE_ADDRESS constant has been deprecated.  configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS are currently being derived from the (possibly 0) configCLINT_BASE_ADDRESS setting.  Please update to define configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS directly in place of configCLINT_BASE_ADDRESS.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే config_MTIME_పునాది_చిరునామా
    #warning "configMTIME_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  If the target chip includes a memory-mapped mtime register then set configMTIME_BASE_ADDRESS to the mapped address.  Otherwise set configMTIME_BASE_ADDRESS to 0.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే config_MTIMECMP_పునాది_చిరునామా
    #warning "configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  If the target chip includes a memory-mapped mtimecmp register then set configMTIMECMP_BASE_ADDRESS to the mapped address.  Otherwise set configMTIMECMP_BASE_ADDRESS to 0.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#అయితే_ముగింపు

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#నిర్వచితమైతే config_TASK_RETURN_చిరునామా
    #నిర్వచించు పోర్టు_TASK_RETURN_చిరునామా    config_TASK_RETURN_చిరునామా
#లేకపోతే
    #నిర్వచించు పోర్టు_TASK_RETURN_చిరునామా    prvTaskExitError
#అయితే_ముగింపు

/* The stack used by interrupt service routines.  Set configISR_STACK_SIZE_WORDS
 * to use a statically allocated array as the interrupt stack.  Alternative leave
 * configISR_STACK_SIZE_WORDS undefined and update the linker script so that a
 * linker variable names __freertos_irq_stack_top has the same value as the top
 * of the stack used by main.  Using the linker script method will repurpose the
 * stack that was used by main before the scheduler was started for use as the
 * interrupt stack after the scheduler has started. */
#నిర్వచితమైతే config_ISR_దొంతర_కొలత_పదాలు
స్థిర __attribute__( ( aligned( 16 ) ) ) దొంతర_Type_t xISRStack[ config_ISR_దొంతర_కొలత_పదాలు ] = { 0 };
స్థిరరాశి దొంతర_Type_t x_ISRStack_శిఖరం = ( దొంతర_Type_t ) &( xISRStack[ config_ISR_దొంతర_కొలత_పదాలు & ~పోర్టు_BYTE_ALIGNMENT_ముసుగు ] );

/* Don't use 0xa5 as the stack fill bytes as that is used by the kernel for
 * the task stacks, and so will legitimately appear in many positions within
 * the ISR stack. */
    #నిర్వచించు పోర్టు_ISR_దొంతర_FILL_BYTE    0xee
#లేకపోతే
    బాహ్య స్థిరరాశి uint32_t __freertos_irq_stack_top[];
    స్థిరరాశి దొంతర_Type_t x_ISRStack_శిఖరం = ( దొంతర_Type_t ) __freertos_irq_stack_top;
#అయితే_ముగింపు

/**
 * @brief Used to catch tasks that attempt to return from their implementing
 * function.
 */
స్థిర శూన్య prvTaskExitError( శూన్య );

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
శూన్య v_పోర్టు_అమరిక_Timer_అంతరాయం( శూన్య ) __attribute__( ( weak ) );

/*-----------------------------------------------------------*/

/* Used to program the machine timer compare register. */
uint64_t ull_తదుపరి_సమయం = 0ULL;
స్థిరరాశి uint64_t * pull_తదుపరి_సమయం = &ull_తదుపరి_సమయం;
స్థిరరాశి size_t uxTimerIncrementsForOneTick = ( size_t ) ( ( configCPU_CLOCK_HZ ) / ( config_TICK_రేటు_HZ ) ); /* Assumes increment won't go over 32-bits. */
అస్థిర uint64_t * pull_Machine_Timer_Compare_రిజిస్టరు = ఖాళీ;

/* Holds the critical nesting value - deliberately non-zero at start up to
 * ensure interrupts are not accidentally enabled before the scheduler starts. */
size_t xCriticalNesting = ( size_t ) 0xaaaaaaaa;
size_t * pxCriticalNesting = &xCriticalNesting;

/* Used to catch tasks that attempt to return from their implementing function. */
size_t x_Task_Return_చిరునామా = ( size_t ) పోర్టు_TASK_RETURN_చిరునామా;

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
 * stack checking.  A problem in the ISR stack will trigger an assert, not call
 * the stack overflow hook function (because the stack overflow hook is specific
 * to a task stack, not the ISR stack). */
#ఒకవేళ defined( config_ISR_దొంతర_కొలత_పదాలు ) && ( config_CHECK_FOR_దొంతర_అధికప్రవాహం > 2 )
    #warning "This path not tested, or even compiled yet."

    స్థిర స్థిరరాశి uint8_t uc_Expected_దొంతర_బైట్లు[] =
    {
        పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, \
        పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, \
        పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, \
        పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, \
        పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE
    }; \

    #నిర్వచించు పోర్టు_CHECK_ISR_దొంతర()    configASSERT( ( memcmp( ( శూన్య * ) xISRStack, ( శూన్య * ) uc_Expected_దొంతర_బైట్లు, పరిమాణం( uc_Expected_దొంతర_బైట్లు ) ) == 0 ) )
#లేకపోతే /* if defined( configISR_STACK_SIZE_WORDS ) && ( configCHECK_FOR_STACK_OVERFLOW > 2 ) */
    /* Define the function away. */
    #నిర్వచించు పోర్టు_CHECK_ISR_దొంతర()
#అయితే_ముగింపు /* configCHECK_FOR_STACK_OVERFLOW > 2 */

/*-----------------------------------------------------------*/

స్థిర శూన్య prvTaskExitError( శూన్య )
{
    అస్థిర uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    configASSERT( xCriticalNesting == ~0UL );
    పోర్టు_DISABLE_INTERRUPTS();

    అయితే( ulDummy == 0 )
    {
        /* This file calls prvTaskExitError() after the scheduler has been
         * started to remove a compiler warning about the function being
         * defined but never called.  ulDummy is used purely to quieten other
         * warnings about code appearing after this function is called - making
         * ulDummy volatile makes the compiler think the function could return
         * and therefore not output an 'unreachable code' warning for code that
         * appears after it. */
    }
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_MTIME_పునాది_చిరునామా != 0 ) && ( config_MTIMECMP_పునాది_చిరునామా != 0 )

    శూన్య v_పోర్టు_అమరిక_Timer_అంతరాయం( శూన్య )
    {
        uint32_t ul_Current_సమయం_ఎగువ, ul_Current_సమయం_దిగువ;
        అస్థిర uint32_t * స్థిరరాశి pul_సమయం_ఎగువ = ( uint32_t * ) ( ( config_MTIME_పునాది_చిరునామా ) + 4UL ); /* 8-byte type so high 32-bit word is 4 bytes up. */
        అస్థిర uint32_t * స్థిరరాశి pul_సమయం_దిగువ = ( uint32_t * ) ( config_MTIME_పునాది_చిరునామా );
        అస్థిర uint32_t ulHartId;

        __asm అస్థిర ( "csrr %0, 0xf14" : "=r" ( ulHartId ) ); /* 0xf14 is HART ID. */

        pull_Machine_Timer_Compare_రిజిస్టరు = ( అస్థిర uint64_t * ) ( config_MTIMECMP_పునాది_చిరునామా + ( ulHartId * పరిమాణం( uint64_t ) ) );

        చేయి
        {
            ul_Current_సమయం_ఎగువ = *pul_సమయం_ఎగువ;
            ul_Current_సమయం_దిగువ = *pul_సమయం_దిగువ;
        } అయితే( ul_Current_సమయం_ఎగువ != *pul_సమయం_ఎగువ );

        ull_తదుపరి_సమయం = ( uint64_t ) ul_Current_సమయం_ఎగువ;
        ull_తదుపరి_సమయం <<= 32ULL; /* High 4-byte word is 32-bits up. */
        ull_తదుపరి_సమయం |= ( uint64_t ) ul_Current_సమయం_దిగువ;
        ull_తదుపరి_సమయం += ( uint64_t ) uxTimerIncrementsForOneTick;
        *pull_Machine_Timer_Compare_రిజిస్టరు = ull_తదుపరి_సమయం;

        /* Prepare the time to use after the next tick interrupt. */
        ull_తదుపరి_సమయం += ( uint64_t ) uxTimerIncrementsForOneTick;
    }

#అయితే_ముగింపు /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    బాహ్య శూన్య x_పోర్టు_ప్రారంభం_మొదటి_Task( శూన్య );

    #ఒకవేళ ( configASSERT_DEFINED == 1 )
    {
        /* Check alignment of the interrupt stack - which is the same as the
         * stack that was being used by main() prior to the scheduler being
         * started. */
        configASSERT( ( x_ISRStack_శిఖరం & పోర్టు_BYTE_ALIGNMENT_ముసుగు ) == 0 );

        #నిర్వచితమైతే config_ISR_దొంతర_కొలత_పదాలు
        {
            memset( ( శూన్య * ) xISRStack, పోర్టు_ISR_దొంతర_FILL_BYTE, పరిమాణం( xISRStack ) );
        }
        #అయితే_ముగింపు /* configISR_STACK_SIZE_WORDS */
    }
    #అయితే_ముగింపు /* configASSERT_DEFINED */

    /* If there is a CLINT then it is ok to use the default implementation
     * in this file, otherwise vPortSetupTimerInterrupt() must be implemented to
     * configure whichever clock is to be used to generate the tick interrupt. */
    v_పోర్టు_అమరిక_Timer_అంతరాయం();

    #ఒకవేళ ( ( config_MTIME_పునాది_చిరునామా != 0 ) && ( config_MTIMECMP_పునాది_చిరునామా != 0 ) )
    {
        /* Enable mtime and external interrupts.  1<<7 for timer interrupt,
         * 1<<11 for external interrupt.  _RB_ What happens here when mtime is
         * not present as with pulpino? */
        __asm అస్థిర ( "csrs 0x304, %0" ::"r" ( 0x880 ) ); /* 0x304 is mie. */
    }
    #అయితే_ముగింపు /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */

    x_పోర్టు_ప్రారంభం_మొదటి_Task();

    /* Should not get here as after calling xPortStartFirstTask() only tasks
     * should be executing. */
    తిరిగి pdFAIL;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented. */
    కొరకు( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/
