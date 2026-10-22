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
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"
#ಅನ್ತರ್ಭಾವ "portmacro.h"

/* Standard includes. */
#ಅನ್ತರ್ಭಾವ "string.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ config_CLINT_ತಳ_ವಿಳಾಸ
    #warning "The configCLINT_BASE_ADDRESS constant has been deprecated.  configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS are currently being derived from the (possibly 0) configCLINT_BASE_ADDRESS setting.  Please update to define configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS directly in place of configCLINT_BASE_ADDRESS.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_MTIME_ತಳ_ವಿಳಾಸ
    #warning "configMTIME_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  If the target chip includes a memory-mapped mtime register then set configMTIME_BASE_ADDRESS to the mapped address.  Otherwise set configMTIME_BASE_ADDRESS to 0.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_MTIMECMP_ತಳ_ವಿಳಾಸ
    #warning "configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  If the target chip includes a memory-mapped mtimecmp register then set configMTIMECMP_BASE_ADDRESS to the mapped address.  Otherwise set configMTIMECMP_BASE_ADDRESS to 0.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#ಆದರೆ_ಅಂತ್ಯ

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ config_TASK_RETURN_ವಿಳಾಸ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ    config_TASK_RETURN_ವಿಳಾಸ
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ    prvTaskExitError
#ಆದರೆ_ಅಂತ್ಯ

/* The stack used by interrupt service routines.  Set configISR_STACK_SIZE_WORDS
 * to use a statically allocated array as the interrupt stack.  Alternative leave
 * configISR_STACK_SIZE_WORDS undefined and update the linker script so that a
 * linker variable names __freertos_irq_stack_top has the same value as the top
 * of the stack used by main.  Using the linker script method will repurpose the
 * stack that was used by main before the scheduler was started for use as the
 * interrupt stack after the scheduler has started. */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ config_ISR_ರಾಶಿ_ಗಾತ್ರ_ಪದಗಳು
ಸ್ಥಿರ __attribute__( ( aligned( 16 ) ) ) ರಾಶಿ_Type_t xISRStack[ config_ISR_ರಾಶಿ_ಗಾತ್ರ_ಪದಗಳು ] = { 0 };
ಸ್ಥಿರಾಂಕ ರಾಶಿ_Type_t x_ISRStack_ತುದಿ = ( ರಾಶಿ_Type_t ) &( xISRStack[ config_ISR_ರಾಶಿ_ಗಾತ್ರ_ಪದಗಳು & ~ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ ] );

/* Don't use 0xa5 as the stack fill bytes as that is used by the kernel for
 * the task stacks, and so will legitimately appear in many positions within
 * the ISR stack. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE    0xee
#ಇಲ್ಲದಿದ್ದರೆ
    ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ uint32_t __freertos_irq_stack_top[];
    ಸ್ಥಿರಾಂಕ ರಾಶಿ_Type_t x_ISRStack_ತುದಿ = ( ರಾಶಿ_Type_t ) __freertos_irq_stack_top;
#ಆದರೆ_ಅಂತ್ಯ

/**
 * @brief Used to catch tasks that attempt to return from their implementing
 * function.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ );

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ ) __attribute__( ( weak ) );

/*-----------------------------------------------------------*/

/* Used to program the machine timer compare register. */
uint64_t ull_ಮುಂದಿನ_ಸಮಯ = 0ULL;
ಸ್ಥಿರಾಂಕ uint64_t * pull_ಮುಂದಿನ_ಸಮಯ = &ull_ಮುಂದಿನ_ಸಮಯ;
ಸ್ಥಿರಾಂಕ size_t uxTimerIncrementsForOneTick = ( size_t ) ( ( configCPU_CLOCK_HZ ) / ( config_TICK_ದರ_HZ ) ); /* Assumes increment won't go over 32-bits. */
ಅಸ್ಥಿರ uint64_t * pull_Machine_Timer_Compare_ರಿಜಿಸ್ಟರ್ = ಖಾಲಿ;

/* Holds the critical nesting value - deliberately non-zero at start up to
 * ensure interrupts are not accidentally enabled before the scheduler starts. */
size_t xCriticalNesting = ( size_t ) 0xaaaaaaaa;
size_t * pxCriticalNesting = &xCriticalNesting;

/* Used to catch tasks that attempt to return from their implementing function. */
size_t x_Task_Return_ವಿಳಾಸ = ( size_t ) ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ;

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
 * stack checking.  A problem in the ISR stack will trigger an assert, not call
 * the stack overflow hook function (because the stack overflow hook is specific
 * to a task stack, not the ISR stack). */
#ಆದರೆ defined( config_ISR_ರಾಶಿ_ಗಾತ್ರ_ಪದಗಳು ) && ( config_CHECK_FOR_ರಾಶಿ_ಅತಿಪ್ರವಾಹ > 2 )
    #warning "This path not tested, or even compiled yet."

    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint8_t uc_Expected_ರಾಶಿ_ಬೈಟುಗಳು[] =
    {
        ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, \
        ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, \
        ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, \
        ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, \
        ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE
    }; \

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CHECK_ISR_ರಾಶಿ()    configASSERT( ( memcmp( ( ಶೂನ್ಯ * ) xISRStack, ( ಶೂನ್ಯ * ) uc_Expected_ರಾಶಿ_ಬೈಟುಗಳು, ಗಾತ್ರ( uc_Expected_ರಾಶಿ_ಬೈಟುಗಳು ) ) == 0 ) )
#ಇಲ್ಲದಿದ್ದರೆ /* if defined( configISR_STACK_SIZE_WORDS ) && ( configCHECK_FOR_STACK_OVERFLOW > 2 ) */
    /* Define the function away. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CHECK_ISR_ರಾಶಿ()
#ಆದರೆ_ಅಂತ್ಯ /* configCHECK_FOR_STACK_OVERFLOW > 2 */

/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ )
{
    ಅಸ್ಥಿರ uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    configASSERT( xCriticalNesting == ~0UL );
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();

    ಆಗ( ulDummy == 0 )
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

#ಆದರೆ ( config_MTIME_ತಳ_ವಿಳಾಸ != 0 ) && ( config_MTIMECMP_ತಳ_ವಿಳಾಸ != 0 )

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
    {
        uint32_t ul_Current_ಸಮಯ_ಮೇಲಿನ, ul_Current_ಸಮಯ_ಕೆಳಗಿನ;
        ಅಸ್ಥಿರ uint32_t * ಸ್ಥಿರಾಂಕ pul_ಸಮಯ_ಮೇಲಿನ = ( uint32_t * ) ( ( config_MTIME_ತಳ_ವಿಳಾಸ ) + 4UL ); /* 8-byte type so high 32-bit word is 4 bytes up. */
        ಅಸ್ಥಿರ uint32_t * ಸ್ಥಿರಾಂಕ pul_ಸಮಯ_ಕೆಳಗಿನ = ( uint32_t * ) ( config_MTIME_ತಳ_ವಿಳಾಸ );
        ಅಸ್ಥಿರ uint32_t ulHartId;

        __asm ಅಸ್ಥಿರ ( "csrr %0, 0xf14" : "=r" ( ulHartId ) ); /* 0xf14 is HART ID. */

        pull_Machine_Timer_Compare_ರಿಜಿಸ್ಟರ್ = ( ಅಸ್ಥಿರ uint64_t * ) ( config_MTIMECMP_ತಳ_ವಿಳಾಸ + ( ulHartId * ಗಾತ್ರ( uint64_t ) ) );

        ಮಾಡು
        {
            ul_Current_ಸಮಯ_ಮೇಲಿನ = *pul_ಸಮಯ_ಮೇಲಿನ;
            ul_Current_ಸಮಯ_ಕೆಳಗಿನ = *pul_ಸಮಯ_ಕೆಳಗಿನ;
        } ಆಗ( ul_Current_ಸಮಯ_ಮೇಲಿನ != *pul_ಸಮಯ_ಮೇಲಿನ );

        ull_ಮುಂದಿನ_ಸಮಯ = ( uint64_t ) ul_Current_ಸಮಯ_ಮೇಲಿನ;
        ull_ಮುಂದಿನ_ಸಮಯ <<= 32ULL; /* High 4-byte word is 32-bits up. */
        ull_ಮುಂದಿನ_ಸಮಯ |= ( uint64_t ) ul_Current_ಸಮಯ_ಕೆಳಗಿನ;
        ull_ಮುಂದಿನ_ಸಮಯ += ( uint64_t ) uxTimerIncrementsForOneTick;
        *pull_Machine_Timer_Compare_ರಿಜಿಸ್ಟರ್ = ull_ಮುಂದಿನ_ಸಮಯ;

        /* Prepare the time to use after the next tick interrupt. */
        ull_ಮುಂದಿನ_ಸಮಯ += ( uint64_t ) uxTimerIncrementsForOneTick;
    }

#ಆದರೆ_ಅಂತ್ಯ /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    ಬಾಹ್ಯ ಶೂನ್ಯ x_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ );

    #ಆದರೆ ( configASSERT_DEFINED == 1 )
    {
        /* Check alignment of the interrupt stack - which is the same as the
         * stack that was being used by main() prior to the scheduler being
         * started. */
        configASSERT( ( x_ISRStack_ತುದಿ & ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ ) == 0 );

        #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ config_ISR_ರಾಶಿ_ಗಾತ್ರ_ಪದಗಳು
        {
            memset( ( ಶೂನ್ಯ * ) xISRStack, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಗಾತ್ರ( xISRStack ) );
        }
        #ಆದರೆ_ಅಂತ್ಯ /* configISR_STACK_SIZE_WORDS */
    }
    #ಆದರೆ_ಅಂತ್ಯ /* configASSERT_DEFINED */

    /* If there is a CLINT then it is ok to use the default implementation
     * in this file, otherwise vPortSetupTimerInterrupt() must be implemented to
     * configure whichever clock is to be used to generate the tick interrupt. */
    v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    #ಆದರೆ ( ( config_MTIME_ತಳ_ವಿಳಾಸ != 0 ) && ( config_MTIMECMP_ತಳ_ವಿಳಾಸ != 0 ) )
    {
        /* Enable mtime and external interrupts.  1<<7 for timer interrupt,
         * 1<<11 for external interrupt.  _RB_ What happens here when mtime is
         * not present as with pulpino? */
        __asm ಅಸ್ಥಿರ ( "csrs 0x304, %0" ::"r" ( 0x880 ) ); /* 0x304 is mie. */
    }
    #ಆದರೆ_ಅಂತ್ಯ /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */

    x_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task();

    /* Should not get here as after calling xPortStartFirstTask() only tasks
     * should be executing. */
    ಹಿಂತಿರುಗಿ pdFAIL;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented. */
    ಗಾಗಿ( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/
