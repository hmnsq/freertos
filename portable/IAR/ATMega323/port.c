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

#അന്തര്ഭാവ <stdlib.h>

#അന്തര്ഭാവ "FreeRTOS.h"
#അന്തര്ഭാവ "task.h"

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the AVR/IAR port.
*----------------------------------------------------------*/

/* Start tasks with interrupts enables. */
#define portFLAGS_INT_ENABLED                   ( ( അട്ടി_Type_t ) 0x80 )

/* Hardware constants for timer 1. */
#define portCLEAR_COUNTER_ON_MATCH              ( ( uint8_t ) 0x08 )
#define portPRESCALE_64                         ( ( uint8_t ) 0x03 )
#define portCLOCK_PRESCALER                     ( ( uint32_t ) 64 )
#define portCOMPARE_MATCH_A_INTERRUPT_ENABLE    ( ( uint8_t ) 0x10 )

/* The number of bytes used on the hardware stack by the task start address. */
#define portBYTES_USED_BY_RETURN_ADDRESS        ( 2 )
/*-----------------------------------------------------------*/

/* Stores the critical section nesting.  This must not be initialised to 0.
 * It will be initialised when a task starts. */
#define portNO_CRITICAL_NESTING    ( ( UBaseType_t ) 0 )
UBaseType_t uxCriticalNesting = 0x50;


/*
 * Perform hardware setup to enable ticks from timer 1, compare match A.
 */
സ്ഥിതം ശൂന്യം prvSetupTimerInterrupt( ശൂന്യം );

/*
 * The IAR compiler does not have full support for inline assembler, so
 * these are defined in the portmacro assembler file.
 */
ബാഹ്യ ശൂന്യം vPortYieldFromTick( ശൂന്യം );
ബാഹ്യ ശൂന്യം vPortStart( ശൂന്യം );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
അട്ടി_Type_t * px_Port_Initialise_അട്ടി( അട്ടി_Type_t * px_മുകൾ_Of_അട്ടി,
                                     TaskFunction_t pxCode,
                                     ശൂന്യം * pvParameters )
{
    uint16_t usAddress;
    അട്ടി_Type_t * px_മുകൾ_Of_Hardware_അട്ടി;

    /* Place a few bytes of known values on the bottom of the stack.
     * This is just useful for debugging. */

    *px_മുകൾ_Of_അട്ടി = 0x11;
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = 0x22;
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = 0x33;
    px_മുകൾ_Of_അട്ടി--;

    /* Remember where the top of the hardware stack is - this is required
     * below. */
    px_മുകൾ_Of_Hardware_അട്ടി = px_മുകൾ_Of_അട്ടി;


    /* Simulate how the stack would look after a call to vPortYield(). */

    /*lint -e950 -e611 -e923 Lint doesn't like this much - but nothing I can do about it. */



    /* The IAR compiler requires two stacks per task.  First there is the
     * hardware call stack which uses the AVR stack pointer.  Second there is the
     * software stack (local variables, parameter passing, etc.) which uses the
     * AVR Y register.
     *
     * This function places both stacks within the memory block passed in as the
     * first parameter.  The hardware stack is placed at the bottom of the memory
     * block.  A gap is then left for the hardware stack to grow.  Next the software
     * stack is placed.  The amount of space between the software and hardware
     * stacks is defined by configCALL_STACK_SIZE.
     *
     *
     *
     * The first part of the stack is the hardware stack.  Place the start
     * address of the task on the hardware stack. */
    usAddress = ( uint16_t ) pxCode;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) ( usAddress & ( uint16_t ) 0x00ff );
    px_മുകൾ_Of_അട്ടി--;

    usAddress >>= 8;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) ( usAddress & ( uint16_t ) 0x00ff );
    px_മുകൾ_Of_അട്ടി--;


    /* Leave enough space for the hardware stack before starting the software
     * stack.  The '- 2' is because we have already used two spaces for the
     * address of the start of the task. */
    px_മുകൾ_Of_അട്ടി -= ( config_CALL_അട്ടി_SIZE - 2 );



    /* Next simulate the stack as if after a call to portSAVE_CONTEXT().
     *  portSAVE_CONTEXT places the flags on the stack immediately after r0
     *  to ensure the interrupts get disabled as soon as possible, and so ensuring
     *  the stack use is minimal should a context switch interrupt occur. */
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x00; /* R0 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = portFLAGS_INT_ENABLED;
    px_മുകൾ_Of_അട്ടി--;

    /* Next place the address of the hardware stack.  This is required so
     * the AVR stack pointer can be restored to point to the hardware stack. */
    px_മുകൾ_Of_Hardware_അട്ടി -= portBYTES_USED_BY_RETURN_ADDRESS;
    usAddress = ( uint16_t ) px_മുകൾ_Of_Hardware_അട്ടി;

    /* SPL */
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) ( usAddress & ( uint16_t ) 0x00ff );
    px_മുകൾ_Of_അട്ടി--;

    /* SPH */
    usAddress >>= 8;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) ( usAddress & ( uint16_t ) 0x00ff );
    px_മുകൾ_Of_അട്ടി--;



    /* Now the remaining registers. */
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x01; /* R1 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x02; /* R2 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x03; /* R3 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x04; /* R4 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x05; /* R5 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x06; /* R6 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x07; /* R7 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x08; /* R8 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x09; /* R9 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x10; /* R10 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x11; /* R11 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x12; /* R12 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x13; /* R13 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x14; /* R14 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x15; /* R15 */
    px_മുകൾ_Of_അട്ടി--;

    /* Place the parameter on the stack in the expected location. */
    usAddress = ( uint16_t ) pvParameters;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) ( usAddress & ( uint16_t ) 0x00ff );
    px_മുകൾ_Of_അട്ടി--;

    usAddress >>= 8;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) ( usAddress & ( uint16_t ) 0x00ff );
    px_മുകൾ_Of_അട്ടി--;

    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x18; /* R18 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x19; /* R19 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x20; /* R20 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x21; /* R21 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x22; /* R22 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x23; /* R23 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x24; /* R24 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x25; /* R25 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x26; /* R26 X */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x27; /* R27 */
    px_മുകൾ_Of_അട്ടി--;

    /* The Y register is not stored as it is used as the software stack and
     * gets saved into the task control block. */

    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x30;  /* R30 Z */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x031; /* R31 */

    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = portNO_CRITICAL_NESTING; /* Critical nesting is zero when the task starts. */

    /*lint +e950 +e611 +e923 */

    തിരികെ px_മുകൾ_Of_അട്ടി;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( ശൂന്യം )
{
    /* Setup the hardware to generate the tick. */
    prvSetupTimerInterrupt();

    /* Restore the context of the first task that is going to run.
     * Normally we would just call portRESTORE_CONTEXT() here, but as the IAR
     * compiler does not fully support inline assembler we have to make a call.*/
    vPortStart();

    /* Should not get here! */
    തിരികെ pdTRUE;
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortEndScheduler( ശൂന്യം )
{
    /* It is unlikely that the AVR port will get stopped.  If required simply
     * disable the tick interrupt here. */
}
/*-----------------------------------------------------------*/

/*
 * Setup timer 1 compare match A to generate a tick interrupt.
 */
സ്ഥിതം ശൂന്യം prvSetupTimerInterrupt( ശൂന്യം )
{
    uint32_t ulCompareMatch;
    uint8_t uc_മുകളിലെ_Byte, uc_താഴെയുള്ള_Byte;

    /* Using 16bit timer 1 to generate the tick.  Correct fuses must be
     * selected for the configCPU_CLOCK_HZ clock. */

    ulCompareMatch = configCPU_CLOCK_HZ / configTICK_RATE_HZ;

    /* We only have 16 bits so have to scale to get our required tick rate. */
    ulCompareMatch /= portCLOCK_PRESCALER;

    /* Adjust for correct value. */
    ulCompareMatch -= ( uint32_t ) 1;

    /* Setup compare match value for compare match A.  Interrupts are disabled
     * before this is called so we need not worry here. */
    uc_താഴെയുള്ള_Byte = ( uint8_t ) ( ulCompareMatch & ( uint32_t ) 0xff );
    ulCompareMatch >>= 8;
    uc_മുകളിലെ_Byte = ( uint8_t ) ( ulCompareMatch & ( uint32_t ) 0xff );
    OCR1AH = uc_മുകളിലെ_Byte;
    OCR1AL = uc_താഴെയുള്ള_Byte;

    /* Setup clock source and compare match behaviour. */
    uc_താഴെയുള്ള_Byte = portCLEAR_COUNTER_ON_MATCH | portPRESCALE_64;
    TCCR1B = uc_താഴെയുള്ള_Byte;

    /* Enable the interrupt - this is okay as interrupt are currently globally
     * disabled. */
    TIMSK |= portCOMPARE_MATCH_A_INTERRUPT_ENABLE;
}
/*-----------------------------------------------------------*/

#എങ്കിൽ configUSE_PREEMPTION == 1

/*
 * Tick ISR for preemptive scheduler.  We can use a __task attribute as
 * the context is saved at the start of vPortYieldFromTick().  The tick
 * count is incremented after the context is saved.
 */
    __task ശൂന്യം SIG_OUTPUT_COMPARE1A( ശൂന്യം )
    {
        vPortYieldFromTick();
        asm ( "reti" );
    }

#അല്ലെങ്കിൽ

/*
 * Tick ISR for the cooperative scheduler.  All this does is increment the
 * tick count.  We don't need to switch context, this can only be done by
 * manual calls to taskYIELD();
 *
 * THE INTERRUPT VECTOR IS POPULATED IN portmacro.s90.  DO NOT INSTALL
 * IT HERE USING THE USUAL PRAGMA.
 */
    __interrupt ശൂന്യം SIG_OUTPUT_COMPARE1A( ശൂന്യം )
    {
        xTaskIncrementTick();
    }
#endif /* if configUSE_PREEMPTION == 1 */
/*-----------------------------------------------------------*/

ശൂന്യം vPortEnterCritical( ശൂന്യം )
{
    portDISABLE_INTERRUPTS();
    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortExitCritical( ശൂന്യം )
{
    uxCriticalNesting--;

    എങ്കിൽ( uxCriticalNesting == portNO_CRITICAL_NESTING )
    {
        portENABLE_INTERRUPTS();
    }
}
