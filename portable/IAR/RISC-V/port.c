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
#समावेश "FreeRTOS.h"
#समावेश "task.h"
#समावेश "portmacro.h"

/* Standard includes. */
#समावेश "string.h"

#अगर_घोषित configCLINT_BASE_ADDRESS
    #warning "The configCLINT_BASE_ADDRESS constant has been deprecated.  configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS are currently being derived from the (possibly 0) configCLINT_BASE_ADDRESS setting.  Please update to define configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS directly in place of configCLINT_BASE_ADDRESS.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#पूर्ण_अगर

#अगर_अघोषित configMTIME_BASE_ADDRESS
    #warning "configMTIME_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  If the target chip includes a memory-mapped mtime register then set configMTIME_BASE_ADDRESS to the mapped address.  Otherwise set configMTIME_BASE_ADDRESS to 0.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#पूर्ण_अगर

#अगर_अघोषित configMTIMECMP_BASE_ADDRESS
    #warning "configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  If the target chip includes a memory-mapped mtimecmp register then set configMTIMECMP_BASE_ADDRESS to the mapped address.  Otherwise set configMTIMECMP_BASE_ADDRESS to 0.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#पूर्ण_अगर

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#अगर_घोषित configTASK_RETURN_ADDRESS
    #घोषणा portTASK_RETURN_ADDRESS    configTASK_RETURN_ADDRESS
#अन्यथा
    #घोषणा portTASK_RETURN_ADDRESS    prvTaskExitError
#पूर्ण_अगर

/* The stack used by interrupt service routines.  Set configISR_STACK_SIZE_WORDS
 * to use a statically allocated array as the interrupt stack.  Alternative leave
 * configISR_STACK_SIZE_WORDS undefined and update the linker script so that a
 * linker variable names __freertos_irq_stack_top has the same value as the top
 * of the stack used by main.  Using the linker script method will repurpose the
 * stack that was used by main before the scheduler was started for use as the
 * interrupt stack after the scheduler has started. */
#अगर_घोषित config_ISR_ढेर_आकार_शब्दगण
अटल __attribute__( ( aligned( 16 ) ) ) ढेर_Type_t xISRStack[ config_ISR_ढेर_आकार_शब्दगण ] = { 0 };
स्थिर ढेर_Type_t x_ISRStack_शीर्ष = ( ढेर_Type_t ) &( xISRStack[ config_ISR_ढेर_आकार_शब्दगण & ~portBYTE_ALIGNMENT_MASK ] );

/* Don't use 0xa5 as the stack fill bytes as that is used by the kernel for
 * the task stacks, and so will legitimately appear in many positions within
 * the ISR stack. */
    #घोषणा port_ISR_ढेर_FILL_BYTE    0xee
#अन्यथा
    बाह्य स्थिर uint32_t __freertos_irq_stack_top[];
    स्थिर ढेर_Type_t x_ISRStack_शीर्ष = ( ढेर_Type_t ) __freertos_irq_stack_top;
#पूर्ण_अगर

/**
 * @brief Used to catch tasks that attempt to return from their implementing
 * function.
 */
अटल व्योम prvTaskExitError( व्योम );

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
व्योम vPortSetupTimerInterrupt( व्योम ) __attribute__( ( weak ) );

/*-----------------------------------------------------------*/

/* Used to program the machine timer compare register. */
uint64_t ull_अग्र_Time = 0ULL;
स्थिर uint64_t * pull_अग्र_Time = &ull_अग्र_Time;
स्थिर माप_प्रकार uxTimerIncrementsForOneTick = ( माप_प्रकार ) ( ( configCPU_CLOCK_HZ ) / ( configTICK_RATE_HZ ) ); /* Assumes increment won't go over 32-bits. */
अस्थिर uint64_t * pullMachineTimerCompareRegister = शून्य;

/* Holds the critical nesting value - deliberately non-zero at start up to
 * ensure interrupts are not accidentally enabled before the scheduler starts. */
माप_प्रकार xCriticalNesting = ( माप_प्रकार ) 0xaaaaaaaa;
माप_प्रकार * pxCriticalNesting = &xCriticalNesting;

/* Used to catch tasks that attempt to return from their implementing function. */
माप_प्रकार xTaskReturnAddress = ( माप_प्रकार ) portTASK_RETURN_ADDRESS;

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
 * stack checking.  A problem in the ISR stack will trigger an assert, not call
 * the stack overflow hook function (because the stack overflow hook is specific
 * to a task stack, not the ISR stack). */
#अगर defined( config_ISR_ढेर_आकार_शब्दगण ) && ( config_CHECK_FOR_ढेर_OVERFLOW > 2 )
    #warning "This path not tested, or even compiled yet."

    अटल स्थिर uint8_t uc_Expected_ढेर_Bytes[] =
    {
        port_ISR_ढेर_FILL_BYTE, port_ISR_ढेर_FILL_BYTE, port_ISR_ढेर_FILL_BYTE, port_ISR_ढेर_FILL_BYTE, \
        port_ISR_ढेर_FILL_BYTE, port_ISR_ढेर_FILL_BYTE, port_ISR_ढेर_FILL_BYTE, port_ISR_ढेर_FILL_BYTE, \
        port_ISR_ढेर_FILL_BYTE, port_ISR_ढेर_FILL_BYTE, port_ISR_ढेर_FILL_BYTE, port_ISR_ढेर_FILL_BYTE, \
        port_ISR_ढेर_FILL_BYTE, port_ISR_ढेर_FILL_BYTE, port_ISR_ढेर_FILL_BYTE, port_ISR_ढेर_FILL_BYTE, \
        port_ISR_ढेर_FILL_BYTE, port_ISR_ढेर_FILL_BYTE, port_ISR_ढेर_FILL_BYTE, port_ISR_ढेर_FILL_BYTE
    }; \

    #घोषणा port_CHECK_ISR_ढेर()    configASSERT( ( स_भेद( ( व्योम * ) xISRStack, ( व्योम * ) uc_Expected_ढेर_Bytes, माप( uc_Expected_ढेर_Bytes ) ) == 0 ) )
#अन्यथा /* if defined( configISR_STACK_SIZE_WORDS ) && ( configCHECK_FOR_STACK_OVERFLOW > 2 ) */
    /* Define the function away. */
    #घोषणा port_CHECK_ISR_ढेर()
#पूर्ण_अगर /* configCHECK_FOR_STACK_OVERFLOW > 2 */

/*-----------------------------------------------------------*/

अटल व्योम prvTaskExitError( व्योम )
{
    अस्थिर uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    configASSERT( xCriticalNesting == ~0UL );
    portDISABLE_INTERRUPTS();

    जबतक( ulDummy == 0 )
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

#अगर ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 )

    व्योम vPortSetupTimerInterrupt( व्योम )
    {
        uint32_t ul_Current_Time_ऊपरी, ul_Current_Time_निचला;
        अस्थिर uint32_t * स्थिर pul_Time_ऊपरी = ( uint32_t * ) ( ( configMTIME_BASE_ADDRESS ) + 4UL ); /* 8-byte type so high 32-bit word is 4 bytes up. */
        अस्थिर uint32_t * स्थिर pul_Time_निचला = ( uint32_t * ) ( configMTIME_BASE_ADDRESS );
        अस्थिर uint32_t ulHartId;

        __asm अस्थिर ( "csrr %0, 0xf14" : "=r" ( ulHartId ) ); /* 0xf14 is HART ID. */

        pullMachineTimerCompareRegister = ( अस्थिर uint64_t * ) ( configMTIMECMP_BASE_ADDRESS + ( ulHartId * माप( uint64_t ) ) );

        करो
        {
            ul_Current_Time_ऊपरी = *pul_Time_ऊपरी;
            ul_Current_Time_निचला = *pul_Time_निचला;
        } जबतक( ul_Current_Time_ऊपरी != *pul_Time_ऊपरी );

        ull_अग्र_Time = ( uint64_t ) ul_Current_Time_ऊपरी;
        ull_अग्र_Time <<= 32ULL; /* High 4-byte word is 32-bits up. */
        ull_अग्र_Time |= ( uint64_t ) ul_Current_Time_निचला;
        ull_अग्र_Time += ( uint64_t ) uxTimerIncrementsForOneTick;
        *pullMachineTimerCompareRegister = ull_अग्र_Time;

        /* Prepare the time to use after the next tick interrupt. */
        ull_अग्र_Time += ( uint64_t ) uxTimerIncrementsForOneTick;
    }

#पूर्ण_अगर /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( व्योम )
{
    बाह्य व्योम xPortStartFirstTask( व्योम );

    #अगर ( configASSERT_DEFINED == 1 )
    {
        /* Check alignment of the interrupt stack - which is the same as the
         * stack that was being used by main() prior to the scheduler being
         * started. */
        configASSERT( ( x_ISRStack_शीर्ष & portBYTE_ALIGNMENT_MASK ) == 0 );

        #अगर_घोषित config_ISR_ढेर_आकार_शब्दगण
        {
            स_रखो( ( व्योम * ) xISRStack, port_ISR_ढेर_FILL_BYTE, माप( xISRStack ) );
        }
        #पूर्ण_अगर /* configISR_STACK_SIZE_WORDS */
    }
    #पूर्ण_अगर /* configASSERT_DEFINED */

    /* If there is a CLINT then it is ok to use the default implementation
     * in this file, otherwise vPortSetupTimerInterrupt() must be implemented to
     * configure whichever clock is to be used to generate the tick interrupt. */
    vPortSetupTimerInterrupt();

    #अगर ( ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) )
    {
        /* Enable mtime and external interrupts.  1<<7 for timer interrupt,
         * 1<<11 for external interrupt.  _RB_ What happens here when mtime is
         * not present as with pulpino? */
        __asm अस्थिर ( "csrs 0x304, %0" ::"r" ( 0x880 ) ); /* 0x304 is mie. */
    }
    #पूर्ण_अगर /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */

    xPortStartFirstTask();

    /* Should not get here as after calling xPortStartFirstTask() only tasks
     * should be executing. */
    वापस pdFAIL;
}
/*-----------------------------------------------------------*/

व्योम vPortEndScheduler( व्योम )
{
    /* Not implemented. */
    क्रम( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/
