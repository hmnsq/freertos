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
#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "task.h"
#অন্তর্ভাব "portmacro.h"

/* Standard includes. */
#অন্তর্ভাব "string.h"

#ifdef configCLINT_BASE_ADDRESS
    #warning "The configCLINT_BASE_ADDRESS constant has been deprecated.  configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS are currently being derived from the (possibly 0) configCLINT_BASE_ADDRESS setting.  Please update to define configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS directly in place of configCLINT_BASE_ADDRESS.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#endif

#ifndef configMTIME_BASE_ADDRESS
    #warning "configMTIME_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  If the target chip includes a memory-mapped mtime register then set configMTIME_BASE_ADDRESS to the mapped address.  Otherwise set configMTIME_BASE_ADDRESS to 0.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#endif

#ifndef configMTIMECMP_BASE_ADDRESS
    #warning "configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  If the target chip includes a memory-mapped mtimecmp register then set configMTIMECMP_BASE_ADDRESS to the mapped address.  Otherwise set configMTIMECMP_BASE_ADDRESS to 0.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#endif

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#ifdef configTASK_RETURN_ADDRESS
    #define portTASK_RETURN_ADDRESS    configTASK_RETURN_ADDRESS
#অন্যথা
    #define portTASK_RETURN_ADDRESS    prvTaskExitError
#endif

/* The stack used by interrupt service routines.  Set configISR_STACK_SIZE_WORDS
 * to use a statically allocated array as the interrupt stack.  Alternative leave
 * configISR_STACK_SIZE_WORDS undefined and update the linker script so that a
 * linker variable names __freertos_irq_stack_top has the same value as the top
 * of the stack used by main.  Using the linker script method will repurpose the
 * stack that was used by main before the scheduler was started for use as the
 * interrupt stack after the scheduler has started. */
#ifdef config_ISR_স্তূপ_আকার_শব্দগুলি
স্থির __attribute__( ( aligned( 16 ) ) ) স্তূপ_Type_t xISRStack[ config_ISR_স্তূপ_আকার_শব্দগুলি ] = { 0 };
ধ্রুবক স্তূপ_Type_t x_ISRStack_শীর্ষ = ( স্তূপ_Type_t ) &( xISRStack[ config_ISR_স্তূপ_আকার_শব্দগুলি & ~portBYTE_ALIGNMENT_MASK ] );

/* Don't use 0xa5 as the stack fill bytes as that is used by the kernel for
 * the task stacks, and so will legitimately appear in many positions within
 * the ISR stack. */
    #define port_ISR_স্তূপ_FILL_BYTE    0xee
#অন্যথা
    বাহ্যিক ধ্রুবক uint32_t __freertos_irq_stack_top[];
    ধ্রুবক স্তূপ_Type_t x_ISRStack_শীর্ষ = ( স্তূপ_Type_t ) __freertos_irq_stack_top;
#endif

/**
 * @brief Used to catch tasks that attempt to return from their implementing
 * function.
 */
স্থির শূন্য prvTaskExitError( শূন্য );

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
শূন্য vPortSetupTimerInterrupt( শূন্য ) __attribute__( ( weak ) );

/*-----------------------------------------------------------*/

/* Used to program the machine timer compare register. */
uint64_t ull_পরবর্তী_Time = 0ULL;
ধ্রুবক uint64_t * pull_পরবর্তী_Time = &ull_পরবর্তী_Time;
ধ্রুবক size_t uxTimerIncrementsForOneTick = ( size_t ) ( ( configCPU_CLOCK_HZ ) / ( configTICK_RATE_HZ ) ); /* Assumes increment won't go over 32-bits. */
অস্থির uint64_t * pullMachineTimerCompareRegister = ফাঁকা;

/* Holds the critical nesting value - deliberately non-zero at start up to
 * ensure interrupts are not accidentally enabled before the scheduler starts. */
size_t xCriticalNesting = ( size_t ) 0xaaaaaaaa;
size_t * pxCriticalNesting = &xCriticalNesting;

/* Used to catch tasks that attempt to return from their implementing function. */
size_t xTaskReturnAddress = ( size_t ) portTASK_RETURN_ADDRESS;

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
 * stack checking.  A problem in the ISR stack will trigger an assert, not call
 * the stack overflow hook function (because the stack overflow hook is specific
 * to a task stack, not the ISR stack). */
#যদি defined( config_ISR_স্তূপ_আকার_শব্দগুলি ) && ( config_CHECK_FOR_স্তূপ_OVERFLOW > 2 )
    #warning "This path not tested, or even compiled yet."

    স্থির ধ্রুবক uint8_t uc_Expected_স্তূপ_Bytes[] =
    {
        port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, \
        port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, \
        port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, \
        port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, \
        port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE
    }; \

    #define port_CHECK_ISR_স্তূপ()    configASSERT( ( memcmp( ( শূন্য * ) xISRStack, ( শূন্য * ) uc_Expected_স্তূপ_Bytes, আকার( uc_Expected_স্তূপ_Bytes ) ) == 0 ) )
#অন্যথা /* if defined( configISR_STACK_SIZE_WORDS ) && ( configCHECK_FOR_STACK_OVERFLOW > 2 ) */
    /* Define the function away. */
    #define port_CHECK_ISR_স্তূপ()
#endif /* configCHECK_FOR_STACK_OVERFLOW > 2 */

/*-----------------------------------------------------------*/

স্থির শূন্য prvTaskExitError( শূন্য )
{
    অস্থির uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    configASSERT( xCriticalNesting == ~0UL );
    portDISABLE_INTERRUPTS();

    যখন( ulDummy == 0 )
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

#যদি ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 )

    শূন্য vPortSetupTimerInterrupt( শূন্য )
    {
        uint32_t ul_Current_Time_উপরের, ul_Current_Time_নিচের;
        অস্থির uint32_t * ধ্রুবক pul_Time_উপরের = ( uint32_t * ) ( ( configMTIME_BASE_ADDRESS ) + 4UL ); /* 8-byte type so high 32-bit word is 4 bytes up. */
        অস্থির uint32_t * ধ্রুবক pul_Time_নিচের = ( uint32_t * ) ( configMTIME_BASE_ADDRESS );
        অস্থির uint32_t ulHartId;

        __asm অস্থির ( "csrr %0, 0xf14" : "=r" ( ulHartId ) ); /* 0xf14 is HART ID. */

        pullMachineTimerCompareRegister = ( অস্থির uint64_t * ) ( configMTIMECMP_BASE_ADDRESS + ( ulHartId * আকার( uint64_t ) ) );

        করো
        {
            ul_Current_Time_উপরের = *pul_Time_উপরের;
            ul_Current_Time_নিচের = *pul_Time_নিচের;
        } যখন( ul_Current_Time_উপরের != *pul_Time_উপরের );

        ull_পরবর্তী_Time = ( uint64_t ) ul_Current_Time_উপরের;
        ull_পরবর্তী_Time <<= 32ULL; /* High 4-byte word is 32-bits up. */
        ull_পরবর্তী_Time |= ( uint64_t ) ul_Current_Time_নিচের;
        ull_পরবর্তী_Time += ( uint64_t ) uxTimerIncrementsForOneTick;
        *pullMachineTimerCompareRegister = ull_পরবর্তী_Time;

        /* Prepare the time to use after the next tick interrupt. */
        ull_পরবর্তী_Time += ( uint64_t ) uxTimerIncrementsForOneTick;
    }

#endif /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( শূন্য )
{
    বাহ্যিক শূন্য xPortStartFirstTask( শূন্য );

    #যদি ( configASSERT_DEFINED == 1 )
    {
        /* Check alignment of the interrupt stack - which is the same as the
         * stack that was being used by main() prior to the scheduler being
         * started. */
        configASSERT( ( x_ISRStack_শীর্ষ & portBYTE_ALIGNMENT_MASK ) == 0 );

        #ifdef config_ISR_স্তূপ_আকার_শব্দগুলি
        {
            memset( ( শূন্য * ) xISRStack, port_ISR_স্তূপ_FILL_BYTE, আকার( xISRStack ) );
        }
        #endif /* configISR_STACK_SIZE_WORDS */
    }
    #endif /* configASSERT_DEFINED */

    /* If there is a CLINT then it is ok to use the default implementation
     * in this file, otherwise vPortSetupTimerInterrupt() must be implemented to
     * configure whichever clock is to be used to generate the tick interrupt. */
    vPortSetupTimerInterrupt();

    #যদি ( ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) )
    {
        /* Enable mtime and external interrupts.  1<<7 for timer interrupt,
         * 1<<11 for external interrupt.  _RB_ What happens here when mtime is
         * not present as with pulpino? */
        __asm অস্থির ( "csrs 0x304, %0" ::"r" ( 0x880 ) ); /* 0x304 is mie. */
    }
    #endif /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */

    xPortStartFirstTask();

    /* Should not get here as after calling xPortStartFirstTask() only tasks
     * should be executing. */
    ফেরত pdFAIL;
}
/*-----------------------------------------------------------*/

শূন্য vPortEndScheduler( শূন্য )
{
    /* Not implemented. */
    জন্য( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/
