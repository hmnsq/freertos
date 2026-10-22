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
 * Implementation of functions defined in portable.h for the PIC32MEC14xx  port.
 *----------------------------------------------------------*/

/* Scheduler include files. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/* Microchip includes. */
#अन्तर्भाव <xc.h>
#अन्तर्भाव <cp0defs.h>

#जर !defined(__MEC__)
    #error This port is designed to work with XC32 on MEC14xx.  Please update your C compiler version or settings.
#endif

#जर( ( configMAX_SYSCALL_INTERRUPT_PRIORITY >= 0x7 ) || ( configMAX_SYSCALL_INTERRUPT_PRIORITY == 0 ) )
    #error configMAX_SYSCALL_INTERRUPT_PRIORITY must be less than 7 and greater than 0
#endif

/* Bits within various registers. */
#define portIE_BIT                  ( 0x00000001 )
#define portEXL_BIT                 ( 0x00000002 )

/* The EXL bit is set to ensure interrupts do not occur while the context of
the first task is being restored.  MEC14xx does not have DSP HW. */
#define portINITIAL_SR              ( portIE_BIT | portEXL_BIT )

/* MEC14xx RTOS Timer MMCR's. */
#define portMMCR_RTMR_PRELOAD   *((अस्थिर uint32_t *)(0xA0007404ul))
#define portMMCR_RTMR_CONTROL   *((अस्थिर uint32_t *)(0xA0007408ul))

/* MEC14xx JTVIC external interrupt controller is mapped to M14K closely-coupled
peripheral space. */
#define portGIRQ23_RTOS_TIMER_BITPOS    ( 4 )
#define portGIRQ23_RTOS_TIMER_MASK      ( 1ul << ( portGIRQ23_RTOS_TIMER_BITPOS ) )
#define portMMCR_JTVIC_GIRQ23_SRC       *((अस्थिर uint32_t *)(0xBFFFC0F0ul))
#define portMMCR_JTVIC_GIRQ23_SETEN     *((अस्थिर uint32_t *)(0xBFFFC0F4ul))
#define portMMCR_JTVIC_GIRQ23_PRIA      *((अस्थिर uint32_t *)(0xBFFFC3F0ul))

/* MIPS Software Interrupts are routed through JTVIC GIRQ24 */
#define portGIRQ24_M14K_SOFTIRQ0_BITPOS ( 1 )
#define portGIRQ24_M14K_SOFTIRQ0_MASK   ( 1ul << ( portGIRQ24_M14K_SOFTIRQ0_BITPOS ) )
#define portMMCR_JTVIC_GIRQ24_SRC       *((अस्थिर uint32_t *)(0xBFFFC100ul))
#define portMMCR_JTVIC_GIRQ24_SETEN     *((अस्थिर uint32_t *)(0xBFFFC104ul))
#define portMMCR_JTVIC_GIRQ24_PRIA      *((अस्थिर uint32_t *)(0xBFFFC400ul))

/*
By default port.c generates its tick interrupt from the RTOS timer.  The user
can override this behaviour by:
    1: Providing their own implementation of vApplicationSetupTickTimerInterrupt(),
       which is the function that configures the timer.  The function is defined
       as a weak symbol in this file so if the same function name is used in the
       application code then the version in the application code will be linked
       into the application in preference to the version defined in this file.
    2: Provide a vector implementation in port_asm.S that overrides the default
       behaviour for the specified interrupt vector.
    3: Specify the correct bit to clear the interrupt during the timer interrupt
       handler.
*/
#ifndef configTICK_INTERRUPT_VECTOR
    #define configTICK_INTERRUPT_VECTOR girq23_b4
    #define configCLEAR_TICK_TIMER_INTERRUPT() portMMCR_JTVIC_GIRQ23_SRC = portGIRQ23_RTOS_TIMER_MASK
#अन्यथा
    #ifndef configCLEAR_TICK_TIMER_INTERRUPT
        #error If configTICK_INTERRUPT_VECTOR is defined in application code then configCLEAR_TICK_TIMER_INTERRUPT must also be defined in application code.
    #endif
#endif

/* Let the user override the pre-loading of the initial RA with the address of
prvTaskExitError() in case it messes up unwinding of the stack in the debugger -
in which case configTASK_RETURN_ADDRESS can be defined as 0 (NULL). */
#ifdef configTASK_RETURN_ADDRESS
    #define portTASK_RETURN_ADDRESS configTASK_RETURN_ADDRESS
#अन्यथा
    #define portTASK_RETURN_ADDRESS prvTaskExitError
#endif

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
stack checking.  A problem in the ISR stack will trigger an assert, not call the
stack overflow hook function (because the stack overflow hook is specific to a
task stack, not the ISR stack). */
#जर( config_CHECK_FOR_चळत_OVERFLOW > 2 )

    /* Don't use 0xa5 as the stack fill bytes as that is used by the kernel for
    the task stacks, and so will legitimately appear in many positions within
    the ISR stack. */
    #define port_ISR_चळत_FILL_BYTE 0xee

    स्थिर स्थिरांक uint8_t uc_Expected_चळत_Bytes[] = {
                            port_ISR_चळत_FILL_BYTE, port_ISR_चळत_FILL_BYTE, port_ISR_चळत_FILL_BYTE, port_ISR_चळत_FILL_BYTE,     \
                            port_ISR_चळत_FILL_BYTE, port_ISR_चळत_FILL_BYTE, port_ISR_चळत_FILL_BYTE, port_ISR_चळत_FILL_BYTE,     \
                            port_ISR_चळत_FILL_BYTE, port_ISR_चळत_FILL_BYTE, port_ISR_चळत_FILL_BYTE, port_ISR_चळत_FILL_BYTE,     \
                            port_ISR_चळत_FILL_BYTE, port_ISR_चळत_FILL_BYTE, port_ISR_चळत_FILL_BYTE, port_ISR_चळत_FILL_BYTE,     \
                            port_ISR_चळत_FILL_BYTE, port_ISR_चळत_FILL_BYTE, port_ISR_चळत_FILL_BYTE, port_ISR_चळत_FILL_BYTE };   \

    #define port_CHECK_ISR_चळत() configASSERT( ( स_भेद( ( शून्य * ) xISRStack, ( शून्य * ) uc_Expected_चळत_Bytes, आकार( uc_Expected_चळत_Bytes ) ) == 0 ) )
#अन्यथा
    /* Define the function away. */
    #define port_CHECK_ISR_चळत()
#endif /* configCHECK_FOR_STACK_OVERFLOW > 2 */


/*-----------------------------------------------------------*/

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
स्थिर शून्य prvTaskExitError( शून्य );

/*-----------------------------------------------------------*/

/* Records the interrupt nesting depth.  This is initialised to one as it is
decremented to 0 when the first task starts. */
अस्थिर UBaseType_t uxInterruptNesting = 0x01;

/* Stores the task stack pointer when a switch is made to use the system stack. */
UBaseType_t ux_Saved_Task_चळत_Pointer = 0;

/* The stack used by interrupt service routines that cause a context switch. */
चळत_Type_t xISRStack[ config_ISR_चळत_SIZE ] = { 0 };

/* The top of stack value ensures there is enough space to store 6 registers on
the callers stack, as some functions seem to want to do this. */
स्थिरांक चळत_Type_t * स्थिरांक x_ISRStack_शीर्ष = &( xISRStack[ config_ISR_चळत_SIZE - 7 ] );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
चळत_Type_t *px_Port_Initialise_चळत( चळत_Type_t *px_शीर्ष_Of_चळत, TaskFunction_t pxCode, शून्य *pvParameters )
{
    /* Ensure byte alignment is maintained when leaving this function. */
    px_शीर्ष_Of_चळत--;

    *px_शीर्ष_Of_चळत = (चळत_Type_t) 0xDEADBEEF;
    px_शीर्ष_Of_चळत--;

    *px_शीर्ष_Of_चळत = (चळत_Type_t) 0x12345678;   /* Word to which the stack pointer will be left pointing after context restore. */
    px_शीर्ष_Of_चळत--;

    *px_शीर्ष_Of_चळत = (चळत_Type_t) ulPortGetCP0Cause();
    px_शीर्ष_Of_चळत--;

    *px_शीर्ष_Of_चळत = (चळत_Type_t) portINITIAL_SR;   /* CP0_STATUS */
    px_शीर्ष_Of_चळत--;

    *px_शीर्ष_Of_चळत = (चळत_Type_t) pxCode;       /* CP0_EPC */
    px_शीर्ष_Of_चळत--;

    *px_शीर्ष_Of_चळत = (चळत_Type_t) portTASK_RETURN_ADDRESS;  /* ra */
    px_शीर्ष_Of_चळत -= 15;

    *px_शीर्ष_Of_चळत = (चळत_Type_t) pvParameters; /* Parameters to pass in. */
    px_शीर्ष_Of_चळत -= 15;

    परत px_शीर्ष_Of_चळत;
}
/*-----------------------------------------------------------*/

स्थिर __inline uint32_t prvDisableInterrupt( शून्य )
{
uint32_t prev_state;

    __asm अस्थिर( "di %0; ehb" : "=r" ( prev_state ) :: "memory" );
    परत prev_state;
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvTaskExitError( शून्य )
{
    /* A function that implements a task must not exit or attempt to return to
    its caller as there is nothing to return to.  If a task wants to exit it
    should instead call vTaskDelete( NULL ).

    Artificially force an assert() to be triggered if configASSERT() is
    defined, then stop here so application writers can catch the error. */
    configASSERT( ux_Saved_Task_चळत_Pointer == 0UL );
    portDISABLE_INTERRUPTS();
    साठी( ;; );
}
/*-----------------------------------------------------------*/

/*
 * Setup a timer for a regular tick.  This function uses the RTOS timer.
 * The function is declared weak so an application writer can use a different
 * timer by redefining this implementation.  If a different timer is used then
 * configTICK_INTERRUPT_VECTOR must also be defined in FreeRTOSConfig.h to
 * ensure the RTOS provided tick interrupt handler is installed on the correct
 * vector number.
 */
__attribute__(( weak )) शून्य vApplicationSetupTickTimerInterrupt( शून्य )
{
/* MEC14xx RTOS Timer whose input clock is 32KHz. */
स्थिरांक uint32_t ulPreload = ( 32768ul / ( configTICK_RATE_HZ ) );

    configASSERT( ulPreload != 0UL );

    /* Configure the RTOS timer. */
    portMMCR_RTMR_CONTROL = 0ul;
    portMMCR_RTMR_PRELOAD = ulPreload;

    /* Configure interrupts from the RTOS timer. */
    portMMCR_JTVIC_GIRQ23_SRC = ( portGIRQ23_RTOS_TIMER_MASK );
    portMMCR_JTVIC_GIRQ23_PRIA &= ~( 0x0Ful << 16 );
    portMMCR_JTVIC_GIRQ23_PRIA |= ( ( portIPL_TO_CODE( configKERNEL_INTERRUPT_PRIORITY ) ) << 16 );
    portMMCR_JTVIC_GIRQ23_SETEN = ( portGIRQ23_RTOS_TIMER_MASK );

    /* Enable the RTOS timer. */
    portMMCR_RTMR_CONTROL = 0x0Fu;
}
/*-----------------------------------------------------------*/

शून्य vPortEndScheduler(शून्य)
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( uxInterruptNesting == 1000UL );
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( शून्य )
{
बाह्य शून्य vPortStartFirstTask( शून्य );
बाह्य शून्य *pxCurrentTCB;

    #जर ( config_CHECK_FOR_चळत_OVERFLOW > 2 )
    {
        /* Fill the ISR stack to make it easy to asses how much is being used. */
        स_रखो( ( शून्य * ) xISRStack, port_ISR_चळत_FILL_BYTE, आकार( xISRStack ) );
    }
    #endif /* configCHECK_FOR_STACK_OVERFLOW > 2 */

    /* Clear the software interrupt flag. */
    portMMCR_JTVIC_GIRQ24_SRC = (portGIRQ24_M14K_SOFTIRQ0_MASK);

    /* Set software timer priority.  Each GIRQn has one nibble containing its
    priority */
    portMMCR_JTVIC_GIRQ24_PRIA &= ~(0xF0ul);
    portMMCR_JTVIC_GIRQ24_PRIA |= ( portIPL_TO_CODE( configKERNEL_INTERRUPT_PRIORITY ) << 4 );

    /* Enable software interrupt. */
    portMMCR_JTVIC_GIRQ24_SETEN = ( portGIRQ24_M14K_SOFTIRQ0_MASK );

    /* Setup the timer to generate the tick.  Interrupts will have been disabled
    by the time we get here. */
    vApplicationSetupTickTimerInterrupt();

    /* Start the highest priority task that has been created so far.  Its stack
    location is loaded into uxSavedTaskStackPointer. */
    ux_Saved_Task_चळत_Pointer = *( UBaseType_t * ) pxCurrentTCB;
    vPortStartFirstTask();

    /* Should never get here as the tasks will now be executing!  Call the task
    exit error function to prevent compiler warnings about a static function
    not being called in the case that the application writer overrides this
    functionality by defining configTASK_RETURN_ADDRESS. */
    prvTaskExitError();

    परत pdFALSE;
}
/*-----------------------------------------------------------*/

शून्य vPortIncrementTick( शून्य )
{
UBaseType_t uxSavedStatus;
uint32_t ulCause;

    uxSavedStatus = uxPortSetInterruptMaskFromISR();
    {
        जर( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            ulCause = ulPortGetCP0Cause();
            ulCause |= ( 1ul << 8UL );
            vPortSetCP0Cause( ulCause );
        }
    }
    vPortClearInterruptMaskFromISR( uxSavedStatus );

    /* Look for the ISR stack getting near or past its limit. */
    port_CHECK_ISR_चळत();

    /* Clear timer interrupt. */
    configCLEAR_TICK_TIMER_INTERRUPT();
}
/*-----------------------------------------------------------*/

UBaseType_t uxPortSetInterruptMaskFromISR( शून्य )
{
UBaseType_t uxSavedStatusRegister;

    prvDisableInterrupt();
    uxSavedStatusRegister = ulPortGetCP0Status() | 0x01;

    /* This clears the IPL bits, then sets them to
    configMAX_SYSCALL_INTERRUPT_PRIORITY.  This function should not be called
    from an interrupt that has a priority above
    configMAX_SYSCALL_INTERRUPT_PRIORITY so, when used correctly, the action
    can only result in the IPL being unchanged or raised, and therefore never
    lowered. */
    vPortSetCP0Status( ( ( uxSavedStatusRegister & ( ~portALL_IPL_BITS ) ) ) | ( configMAX_SYSCALL_INTERRUPT_PRIORITY << portIPL_SHIFT ) );

    परत uxSavedStatusRegister;
}
/*-----------------------------------------------------------*/

शून्य vPortClearInterruptMaskFromISR( UBaseType_t uxSavedStatusRegister )
{
    vPortSetCP0Status( uxSavedStatusRegister );
}
/*-----------------------------------------------------------*/
