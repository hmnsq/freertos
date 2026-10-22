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
 * Implementation of functions defined in portable.h for the PIC32MZ port.
  *----------------------------------------------------------*/

/* Microchip specific headers. */
#অন্তর্ভাব <xc.h>

/* Standard headers. */
#অন্তর্ভাব <string.h>

/* Scheduler include files. */
#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "task.h"

#যদি !defined(__PIC32MZ__)
    #error This port is designed to work with XC32 on PIC32MZ MCUs.  Please update your C compiler version or settings.
#endif

#যদি( ( configMAX_SYSCALL_INTERRUPT_PRIORITY >= 0x7 ) || ( configMAX_SYSCALL_INTERRUPT_PRIORITY == 0 ) )
    #error configMAX_SYSCALL_INTERRUPT_PRIORITY must be less than 7 and greater than 0
#endif

/* Hardware specifics. */
#define portTIMER_PRESCALE  8
#define portPRESCALE_BITS   1

/* Bits within various registers. */
#define portIE_BIT                  ( 0x00000001 )
#define portEXL_BIT                 ( 0x00000002 )
#define portMX_BIT                  ( 0x01000000 ) /* Allow access to DSP instructions. */
#define portCU1_BIT                 ( 0x20000000 ) /* enable CP1 for parts with hardware. */
#define portFR_BIT                  ( 0x04000000 ) /* Enable 64 bit floating point registers. */

/* Bits within the CAUSE register. */
#define portCORE_SW_0               ( 0x00000100 )
#define portCORE_SW_1               ( 0x00000200 )

/* The EXL bit is set to ensure interrupts do not occur while the context of
the first task is being restored. */
#যদি ( __mips_hard_float == 1 )
    #define portINITIAL_SR          ( portIE_BIT | portEXL_BIT | portMX_BIT | portFR_BIT | portCU1_BIT )
#অন্যথা
    #define portINITIAL_SR          ( portIE_BIT | portEXL_BIT | portMX_BIT )
#endif

/* The initial value to store into the FPU status and control register. This is
 only used on parts that support a hardware FPU. */
#define portINITIAL_FPSCR           (0x1000000) /* High perf on denormal ops */


/*
By default port.c generates its tick interrupt from TIMER1.  The user can
override this behaviour by:
    1: Providing their own implementation of vApplicationSetupTickTimerInterrupt(),
       which is the function that configures the timer.  The function is defined
       as a weak symbol in this file so if the same function name is used in the
       application code then the version in the application code will be linked
       into the application in preference to the version defined in this file.
    2: Define configTICK_INTERRUPT_VECTOR to the vector number of the timer used
       to generate the tick interrupt.  For example, when timer 1 is used then
       configTICK_INTERRUPT_VECTOR is set to _TIMER_1_VECTOR.
       configTICK_INTERRUPT_VECTOR should be defined in FreeRTOSConfig.h.
    3: Define configCLEAR_TICK_TIMER_INTERRUPT() to clear the interrupt in the
       timer used to generate the tick interrupt.  For example, when timer 1 is
       used configCLEAR_TICK_TIMER_INTERRUPT() is defined to
       IFS0CLR = _IFS0_T1IF_MASK.
*/
#ifndef configTICK_INTERRUPT_VECTOR
    #define configTICK_INTERRUPT_VECTOR _TIMER_1_VECTOR
    #define configCLEAR_TICK_TIMER_INTERRUPT() IFS0CLR = _IFS0_T1IF_MASK
#অন্যথা
    #ifndef configCLEAR_TICK_TIMER_INTERRUPT
        #error If configTICK_INTERRUPT_VECTOR is defined in application code then configCLEAR_TICK_TIMER_INTERRUPT must also be defined in application code.
    #endif
#endif

/* Let the user override the pre-loading of the initial RA with the address of
prvTaskExitError() in case it messes up unwinding of the stack in the
debugger - in which case configTASK_RETURN_ADDRESS can be defined as 0 (NULL). */
#ifdef configTASK_RETURN_ADDRESS
    #define portTASK_RETURN_ADDRESS configTASK_RETURN_ADDRESS
#অন্যথা
    #define portTASK_RETURN_ADDRESS prvTaskExitError
#endif

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
stack checking.  A problem in the ISR stack will trigger an assert, not call the
stack overflow hook function (because the stack overflow hook is specific to a
task stack, not the ISR stack). */
#যদি( config_CHECK_FOR_স্তূপ_OVERFLOW > 2 )

    /* Don't use 0xa5 as the stack fill bytes as that is used by the kernel for
    the task stacks, and so will legitimately appear in many positions within
    the ISR stack. */
    #define port_ISR_স্তূপ_FILL_BYTE 0xee

    স্থির ধ্রুব uint8_t uc_Expected_স্তূপ_Bytes[] = {
                                    port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE,     \
                                    port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE,     \
                                    port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE,     \
                                    port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE,     \
                                    port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE, port_ISR_স্তূপ_FILL_BYTE };   \

    #define port_CHECK_ISR_স্তূপ() configASSERT( ( memcmp( ( শূন্য * ) xISRStack, ( শূন্য * ) uc_Expected_স্তূপ_Bytes, পরিমাণ( uc_Expected_স্তূপ_Bytes ) ) == 0 ) )
#অন্যথা
    /* Define the function away. */
    #define port_CHECK_ISR_স্তূপ()
#endif /* configCHECK_FOR_STACK_OVERFLOW > 2 */

/*-----------------------------------------------------------*/

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
স্থির শূন্য prvTaskExitError( শূন্য );

/*-----------------------------------------------------------*/

/* Records the interrupt nesting depth.  This is initialised to one as it is
decremented to 0 when the first task starts. */
চঞ্চল UBaseType_t uxInterruptNesting = 0x01;

/* Stores the task stack pointer when a switch is made to use the system stack. */
UBaseType_t ux_Saved_Task_স্তূপ_Pointer = 0;

/* The stack used by interrupt service routines that cause a context switch. */
__attribute__ ((aligned(8))) স্তূপ_Type_t xISRStack[ config_ISR_স্তূপ_SIZE ] = { 0 };

/* The top of stack value ensures there is enough space to store 6 registers on
the callers stack, as some functions seem to want to do this.  8 byte alignment
is required to allow double word floating point stack pushes generated by the
compiler. */
ধ্রুব স্তূপ_Type_t * ধ্রুব x_ISRStack_শীর্ষ = &( xISRStack[ ( config_ISR_স্তূপ_SIZE & ~portBYTE_ALIGNMENT_MASK ) - 8 ] );

/* Saved as part of the task context. Set to pdFALSE if the task does not
 require an FPU context. */
#যদি ( __mips_hard_float == 1 ) && ( configUSE_TASK_FPU_SUPPORT == 1 )
    uint32_t ulTaskHasFPUContext = 0;
#endif

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
স্তূপ_Type_t *px_Port_Initialise_স্তূপ( স্তূপ_Type_t *px_শীর্ষ_Of_স্তূপ, TaskFunction_t pxCode, শূন্য *pvParameters )
{
    /* Ensure 8 byte alignment is maintained when leaving this function. */
    px_শীর্ষ_Of_স্তূপ--;
    px_শীর্ষ_Of_স্তূপ--;

    *px_শীর্ষ_Of_স্তূপ = (স্তূপ_Type_t) 0xDEADBEEF;
    px_শীর্ষ_Of_স্তূপ--;

    *px_শীর্ষ_Of_স্তূপ = (স্তূপ_Type_t) 0x12345678;   /* Word to which the stack pointer will be left pointing after context restore. */
    px_শীর্ষ_Of_স্তূপ--;

    *px_শীর্ষ_Of_স্তূপ = (স্তূপ_Type_t) _CP0_GET_CAUSE();
    px_শীর্ষ_Of_স্তূপ--;

    *px_শীর্ষ_Of_স্তূপ = (স্তূপ_Type_t) portINITIAL_SR;/* CP0_STATUS */
    px_শীর্ষ_Of_স্তূপ--;

    *px_শীর্ষ_Of_স্তূপ = (স্তূপ_Type_t) pxCode;       /* CP0_EPC */
    px_শীর্ষ_Of_স্তূপ--;

    *px_শীর্ষ_Of_স্তূপ = (স্তূপ_Type_t) 0x00000000;   /* DSPControl */
    px_শীর্ষ_Of_স্তূপ -= 7;                          /* Includes space for AC1 - AC3. */

    *px_শীর্ষ_Of_স্তূপ = (স্তূপ_Type_t) portTASK_RETURN_ADDRESS;  /* ra */
    px_শীর্ষ_Of_স্তূপ -= 15;

    *px_শীর্ষ_Of_স্তূপ = (স্তূপ_Type_t) pvParameters; /* Parameters to pass in. */
    px_শীর্ষ_Of_স্তূপ -= 15;

    *px_শীর্ষ_Of_স্তূপ = (স্তূপ_Type_t) pdFALSE; /*by default disable FPU context save on parts with FPU */

    প্রত্যাগম px_শীর্ষ_Of_স্তূপ;
}
/*-----------------------------------------------------------*/

স্থির শূন্য prvTaskExitError( শূন্য )
{
    /* A function that implements a task must not exit or attempt to return to
    its caller as there is nothing to return to.  If a task wants to exit it
    should instead call vTaskDelete( NULL ).

    Artificially force an assert() to be triggered if configASSERT() is
    defined, then stop here so application writers can catch the error. */
    configASSERT( ux_Saved_Task_স্তূপ_Pointer == 0UL );
    portDISABLE_INTERRUPTS();
    প্রতি( ;; );
}
/*-----------------------------------------------------------*/

/*
 * Setup a timer for a regular tick.  This function uses peripheral timer 1.
 * The function is declared weak so an application writer can use a different
 * timer by redefining this implementation.  If a different timer is used then
 * configTICK_INTERRUPT_VECTOR must also be defined in FreeRTOSConfig.h to
 * ensure the RTOS provided tick interrupt handler is installed on the correct
 * vector number.  When Timer 1 is used the vector number is defined as
 * _TIMER_1_VECTOR.
 */
__attribute__(( weak )) শূন্য vApplicationSetupTickTimerInterrupt( শূন্য )
{
ধ্রুব uint32_t ulCompareMatch = ( (configPERIPHERAL_CLOCK_HZ / portTIMER_PRESCALE) / configTICK_RATE_HZ ) - 1UL;

    /* PR1 is 16-bit. Ensure that the configPERIPHERAL_CLOCK_HZ and
     * configTICK_RATE_HZ are defined such that ulCompareMatch value would fit
     * in 16-bits. */
    configASSERT( ( ulCompareMatch & 0xFFFF0000 ) == 0 );

    T1CON = 0x0000;
    T1CONbits.TCKPS = portPRESCALE_BITS;
    PR1 = ulCompareMatch;
    IPC1bits.T1IP = configKERNEL_INTERRUPT_PRIORITY;

    /* Clear the interrupt as a starting condition. */
    IFS0bits.T1IF = 0;

    /* Enable the interrupt. */
    IEC0bits.T1IE = 1;

    /* Start the timer. */
    T1CONbits.TON = 1;
}
/*-----------------------------------------------------------*/

শূন্য vPortEndScheduler(শূন্য)
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( uxInterruptNesting == 1000UL );
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( শূন্য )
{
বাহ্য শূন্য vPortStartFirstTask( শূন্য );
বাহ্য শূন্য *pxCurrentTCB;

    #যদি ( config_CHECK_FOR_স্তূপ_OVERFLOW > 2 )
    {
        /* Fill the ISR stack to make it easy to asses how much is being used. */
        memset( ( শূন্য * ) xISRStack, port_ISR_স্তূপ_FILL_BYTE, পরিমাণ( xISRStack ) );
    }
    #endif /* configCHECK_FOR_STACK_OVERFLOW > 2 */

    /* Clear the software interrupt flag. */
    IFS0CLR = _IFS0_CS0IF_MASK;

    /* Set software timer priority. */
    IPC0CLR = _IPC0_CS0IP_MASK;
    IPC0SET = ( configKERNEL_INTERRUPT_PRIORITY << _IPC0_CS0IP_POSITION );

    /* Enable software interrupt. */
    IEC0CLR = _IEC0_CS0IE_MASK;
    IEC0SET = 1 << _IEC0_CS0IE_POSITION;

    /* Setup the timer to generate the tick.  Interrupts will have been
    disabled by the time we get here. */
    vApplicationSetupTickTimerInterrupt();

    /* Kick off the highest priority task that has been created so far.
    Its stack location is loaded into uxSavedTaskStackPointer. */
    ux_Saved_Task_স্তূপ_Pointer = *( UBaseType_t * ) pxCurrentTCB;
    vPortStartFirstTask();

    /* Should never get here as the tasks will now be executing!  Call the task
    exit error function to prevent compiler warnings about a static function
    not being called in the case that the application writer overrides this
    functionality by defining configTASK_RETURN_ADDRESS. */
    prvTaskExitError();

    প্রত্যাগম pdFALSE;
}
/*-----------------------------------------------------------*/

শূন্য vPortIncrementTick( শূন্য )
{
UBaseType_t uxSavedStatus;

    uxSavedStatus = uxPortSetInterruptMaskFromISR();
    {
        যদি( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            _CP0_BIS_CAUSE( portCORE_SW_0 );
        }
    }
    vPortClearInterruptMaskFromISR( uxSavedStatus );

    /* Look for the ISR stack getting near or past its limit. */
    port_CHECK_ISR_স্তূপ();

    /* Clear timer interrupt. */
    configCLEAR_TICK_TIMER_INTERRUPT();
}
/*-----------------------------------------------------------*/

UBaseType_t uxPortSetInterruptMaskFromISR( শূন্য )
{
UBaseType_t uxSavedStatusRegister;

    __builtin_disable_interrupts();
    uxSavedStatusRegister = _CP0_GET_STATUS() | 0x01;
    /* This clears the IPL bits, then sets them to
    configMAX_SYSCALL_INTERRUPT_PRIORITY.  This function should not be called
    from an interrupt that has a priority above
    configMAX_SYSCALL_INTERRUPT_PRIORITY so, when used correctly, the action
    can only result in the IPL being unchanged or raised, and therefore never
    lowered. */
    _CP0_SET_STATUS( ( ( uxSavedStatusRegister & ( ~portALL_IPL_BITS ) ) ) | ( configMAX_SYSCALL_INTERRUPT_PRIORITY << portIPL_SHIFT ) );

    প্রত্যাগম uxSavedStatusRegister;
}
/*-----------------------------------------------------------*/

শূন্য vPortClearInterruptMaskFromISR( UBaseType_t uxSavedStatusRegister )
{
    _CP0_SET_STATUS( uxSavedStatusRegister );
}
/*-----------------------------------------------------------*/

#যদি ( __mips_hard_float == 1 ) && ( configUSE_TASK_FPU_SUPPORT == 1 )

    শূন্য vPortTaskUsesFPU(শূন্য)
    {
    বাহ্য শূন্য vPortInitialiseFPSCR( uint32_t uxFPSCRInit );

        portENTER_CRITICAL();

        /* Initialise the floating point status register. */
        vPortInitialiseFPSCR(portINITIAL_FPSCR);

        /* A task is registering the fact that it needs a FPU context. Set the
        FPU flag (saved as part of the task context). */
        ulTaskHasFPUContext = pdTRUE;

        portEXIT_CRITICAL();
    }

#endif /* __mips_hard_float == 1 */

/*-----------------------------------------------------------*/
