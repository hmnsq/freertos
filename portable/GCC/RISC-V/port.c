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
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"
#अन्तर्भाव "portmacro.h"

/* Standard includes. */
#अन्तर्भाव "string.h"

#ifdef configCLINT_BASE_ADDRESS
    #warning "The configCLINT_BASE_ADDRESS constant has been deprecated. configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS are currently being derived from the (possibly 0) configCLINT_BASE_ADDRESS setting.  Please update to define configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS directly in place of configCLINT_BASE_ADDRESS. See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#endif

#ifndef configMTIME_BASE_ADDRESS
    #warning "configMTIME_BASE_ADDRESS must be defined in FreeRTOSConfig.h. If the target chip includes a memory-mapped mtime register then set configMTIME_BASE_ADDRESS to the mapped address.  Otherwise set configMTIME_BASE_ADDRESS to 0.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#endif

#ifndef configMTIMECMP_BASE_ADDRESS
    #warning "configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h. If the target chip includes a memory-mapped mtimecmp register then set configMTIMECMP_BASE_ADDRESS to the mapped address.  Otherwise set configMTIMECMP_BASE_ADDRESS to 0.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#endif

/* Let the user override the pre-loading of the initial RA. */
#ifdef configTASK_RETURN_ADDRESS
    #define portTASK_RETURN_ADDRESS    configTASK_RETURN_ADDRESS
#अण्णहा
    #define portTASK_RETURN_ADDRESS    0
#endif

/* The stack used by interrupt service routines.  Set configISR_STACK_SIZE_WORDS
 * to use a statically allocated array as the interrupt stack.  Alternative leave
 * configISR_STACK_SIZE_WORDS undefined and update the linker script so that a
 * linker variable names __freertos_irq_stack_top has the same value as the top
 * of the stack used by main.  Using the linker script method will repurpose the
 * stack that was used by main before the scheduler was started for use as the
 * interrupt stack after the scheduler has started. */
#ifdef config_ISR_राशिः_SIZE_शब्दाः
स्थिर __attribute__( ( aligned( 16 ) ) ) राशिः_Type_t xISRStack[ config_ISR_राशिः_SIZE_शब्दाः ] = { 0 };
ध्रुव राशिः_Type_t x_ISRStack_शिखरम् = ( राशिः_Type_t ) &( xISRStack[ config_ISR_राशिः_SIZE_शब्दाः & ~portBYTE_ALIGNMENT_MASK ] );

/* Don't use 0xa5 as the stack fill bytes as that is used by the kernel for
 * the task stacks, and so will legitimately appear in many positions within
 * the ISR stack. */
    #define port_ISR_राशिः_FILL_BYTE    0xee
#अण्णहा
    बाह्य ध्रुव uint32_t __freertos_irq_stack_top[];
    ध्रुव राशिः_Type_t x_ISRStack_शिखरम् = ( राशिः_Type_t ) __freertos_irq_stack_top;
#endif

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
शून्य vPortSetupTimerInterrupt( शून्य ) __attribute__( ( weak ) );

/*-----------------------------------------------------------*/

/* Used to program the machine timer compare register. */
uint64_t ullNextTime = 0ULL;
ध्रुव uint64_t * pullNextTime = &ullNextTime;
ध्रुव size_t uxTimerIncrementsForOneTick = ( size_t ) ( ( configCPU_CLOCK_HZ ) / ( configTICK_RATE_HZ ) ); /* Assumes increment won't go over 32-bits. */
चञ्चल uint64_t * pullMachineTimerCompareRegister = रिक्त;

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
#जइ defined( config_ISR_राशिः_SIZE_शब्दाः ) && ( config_CHECK_FOR_राशिः_OVERFLOW > 2 )
    #warning "This path not tested, or even compiled yet."

    स्थिर ध्रुव uint8_t uc_Expected_राशिः_Bytes[] =
    {
        port_ISR_राशिः_FILL_BYTE, port_ISR_राशिः_FILL_BYTE, port_ISR_राशिः_FILL_BYTE, port_ISR_राशिः_FILL_BYTE, \
        port_ISR_राशिः_FILL_BYTE, port_ISR_राशिः_FILL_BYTE, port_ISR_राशिः_FILL_BYTE, port_ISR_राशिः_FILL_BYTE, \
        port_ISR_राशिः_FILL_BYTE, port_ISR_राशिः_FILL_BYTE, port_ISR_राशिः_FILL_BYTE, port_ISR_राशिः_FILL_BYTE, \
        port_ISR_राशिः_FILL_BYTE, port_ISR_राशिः_FILL_BYTE, port_ISR_राशिः_FILL_BYTE, port_ISR_राशिः_FILL_BYTE, \
        port_ISR_राशिः_FILL_BYTE, port_ISR_राशिः_FILL_BYTE, port_ISR_राशिः_FILL_BYTE, port_ISR_राशिः_FILL_BYTE
    }; \

    #define port_CHECK_ISR_राशिः()    configASSERT( ( memcmp( ( शून्य * ) xISRStack, ( शून्य * ) uc_Expected_राशिः_Bytes, परिमाण( uc_Expected_राशिः_Bytes ) ) == 0 ) )
#अण्णहा /* if defined( configISR_STACK_SIZE_WORDS ) && ( configCHECK_FOR_STACK_OVERFLOW > 2 ) */
    /* Define the function away. */
    #define port_CHECK_ISR_राशिः()
#endif /* configCHECK_FOR_STACK_OVERFLOW > 2 */

/*-----------------------------------------------------------*/

#जइ ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 )

    शून्य vPortSetupTimerInterrupt( शून्य )
    {
        uint32_t ul_Current_Time_उच्चः, ul_Current_Time_नीचः;
        चञ्चल uint32_t * ध्रुव pul_Time_उच्चः = ( चञ्चल uint32_t * ध्रुव ) ( ( configMTIME_BASE_ADDRESS ) + 4UL ); /* 8-byte type so high 32-bit word is 4 bytes up. */
        चञ्चल uint32_t * ध्रुव pul_Time_नीचः = ( चञ्चल uint32_t * ध्रुव ) ( configMTIME_BASE_ADDRESS );
        चञ्चल uint32_t ulHartId;

        __asm चञ्चल ( "csrr %0, mhartid" : "=r" ( ulHartId ) );

        pullMachineTimerCompareRegister = ( चञ्चल uint64_t * ) ( configMTIMECMP_BASE_ADDRESS + ( ulHartId * परिमाण( uint64_t ) ) );

        करेहि
        {
            ul_Current_Time_उच्चः = *pul_Time_उच्चः;
            ul_Current_Time_नीचः = *pul_Time_नीचः;
        } जाव( ul_Current_Time_उच्चः != *pul_Time_उच्चः );

        ullNextTime = ( uint64_t ) ul_Current_Time_उच्चः;
        ullNextTime <<= 32ULL; /* High 4-byte word is 32-bits up. */
        ullNextTime |= ( uint64_t ) ul_Current_Time_नीचः;
        ullNextTime += ( uint64_t ) uxTimerIncrementsForOneTick;
        *pullMachineTimerCompareRegister = ullNextTime;

        /* Prepare the time to use after the next tick interrupt. */
        ullNextTime += ( uint64_t ) uxTimerIncrementsForOneTick;
    }

#endif /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( शून्य )
{
    बाह्य शून्य xPortStartFirstTask( शून्य );

    #जइ ( configASSERT_DEFINED == 1 )
    {
        /* Check alignment of the interrupt stack - which is the same as the
         * stack that was being used by main() prior to the scheduler being
         * started. */
        configASSERT( ( x_ISRStack_शिखरम् & portBYTE_ALIGNMENT_MASK ) == 0 );

        #ifdef config_ISR_राशिः_SIZE_शब्दाः
        {
            memset( ( शून्य * ) xISRStack, port_ISR_राशिः_FILL_BYTE, परिमाण( xISRStack ) );
        }
        #endif /* configISR_STACK_SIZE_WORDS */
    }
    #endif /* configASSERT_DEFINED */

    /* If there is a CLINT then it is ok to use the default implementation
     * in this file, otherwise vPortSetupTimerInterrupt() must be implemented to
     * configure whichever clock is to be used to generate the tick interrupt. */
    vPortSetupTimerInterrupt();

    #जइ ( ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) )
    {
        /* Enable mtime and external interrupts.  1<<7 for timer interrupt,
         * 1<<11 for external interrupt.  _RB_ What happens here when mtime is
         * not present as with pulpino? */
        __asm चञ्चल ( "csrs mie, %0" ::"r" ( 0x880 ) );
    }
    #endif /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */

    xPortStartFirstTask();

    /* Should not get here as after calling xPortStartFirstTask() only tasks
     * should be executing. */
    प्रत्यागम pdFAIL;
}
/*-----------------------------------------------------------*/

शून्य vPortEndScheduler( शून्य )
{
    /* Not implemented. */
    प्रति( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/
