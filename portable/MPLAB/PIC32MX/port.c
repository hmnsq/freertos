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
 * Implementation of functions defined in portable.h for the PIC32MX port.
  *----------------------------------------------------------*/

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __XC
    #ਗਲਤੀ This ਪੋਰਟ is designed ਮੰਜ਼ਿਲ work with XC32.  Please update your C compiler ਸੰਸਕਰਣ.
#ਜੇ_ਅੰਤ

/* Scheduler include files. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

/* Hardware specifics. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_PRESCALE  8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRESCALE_ਬਿੱਟ   1

/* Bits within various registers. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IE_ਦੋਆਧਾਰੀ_ਅੰਕ                      ( 0x00000001 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXL_ਦੋਆਧਾਰੀ_ਅੰਕ                     ( 0x00000002 )

/* Bits within the CAUSE register. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CORE_SW_0                   ( 0x00000100 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CORE_SW_1                   ( 0x00000200 )

/* The EXL bit is set to ensure interrupts do not occur while the context of
the first task is being restored. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_SR                  ( ਪੋਰਟ_IE_ਦੋਆਧਾਰੀ_ਅੰਕ | ਪੋਰਟ_EXL_ਦੋਆਧਾਰੀ_ਅੰਕ )

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
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_TICK_ਰੁਕਾਵਟ_ਸਦਿਸ਼
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_TICK_ਰੁਕਾਵਟ_ਸਦਿਸ਼ TIMER_1_ਸਦਿਸ਼
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_CLEAR_TICK_TIMER_ਰੁਕਾਵਟ() IFS0CLR = IFS0_T1_IF_ਨਕਾਬ
#ਨਹੀਂਤਾਂ
    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_CLEAR_TICK_TIMER_ਰੁਕਾਵਟ
        #ਗਲਤੀ If config_TICK_ਰੁਕਾਵਟ_ਸਦਿਸ਼ is defined ਵਿੱਚ_2 application ਕੋਡ then config_CLEAR_TICK_TIMER_ਰੁਕਾਵਟ must also be defined ਵਿੱਚ_2 application ਕੋਡ.
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

/* Let the user override the pre-loading of the initial RA with the address of
prvTaskExitError() in case it messes up unwinding of the stack in the
debugger - in which case configTASK_RETURN_ADDRESS can be defined as 0 (NULL). */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ config_TASK_RETURN_ਪਤਾ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_RETURN_ਪਤਾ config_TASK_RETURN_ਪਤਾ
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_RETURN_ਪਤਾ prvTaskExitError
#ਜੇ_ਅੰਤ

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
stack checking.  A problem in the ISR stack will trigger an assert, not call the
stack overflow hook function (because the stack overflow hook is specific to a
task stack, not the ISR stack). */
#ਜੇ( config_CHECK_FOR_ਢੇਰ_ਉਛਾਲ > 2 )

    /* Don't use 0xa5 as the stack fill bytes as that is used by the kernel for
    the task stacks, and so will legitimately appear in many positions within
    the ISR stack. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE 0xee

    ਸਥਿਰ ਅਚਲ uint8_t uc_Expected_ਢੇਰ_ਬਾਈਟਾਂ[] = {
                                    ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE,     \
                                    ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE,     \
                                    ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE,     \
                                    ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE,     \
                                    ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE };   \

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHECK_ISR_ਢੇਰ() configASSERT( ( memcmp( ( ਖਾਲੀ * ) xISRStack, ( ਖਾਲੀ * ) uc_Expected_ਢੇਰ_ਬਾਈਟਾਂ, ਆਕਾਰ( uc_Expected_ਢੇਰ_ਬਾਈਟਾਂ ) ) == 0 ) )
#ਨਹੀਂਤਾਂ
    /* Define the function away. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHECK_ISR_ਢੇਰ()
#ਜੇ_ਅੰਤ /* configCHECK_FOR_STACK_OVERFLOW > 2 */

/*-----------------------------------------------------------*/


/*
 * Place the prototype here to ensure the interrupt vector is correctly installed.
 * Note that because the interrupt is written in assembly, the IPL setting in the
 * following line of code has no effect.  The interrupt priority is set by the
 * call to ConfigIntTimer1() in vApplicationSetupTickTimerInterrupt().
 */
ਬਾਹਰੀ ਖਾਲੀ __attribute__( (ਰੁਕਾਵਟ(IPL1AUTO), ਸਦਿਸ਼( config_TICK_ਰੁਕਾਵਟ_ਸਦਿਸ਼ ))) v_ਪੋਰਟ_Tick_ਰੁਕਾਵਟ_Handler( ਖਾਲੀ );

/*
 * The software interrupt handler that performs the yield.  Note that, because
 * the interrupt is written in assembly, the IPL setting in the following line of
 * code has no effect.  The interrupt priority is set by the call to
 * mConfigIntCoreSW0() in xPortStartScheduler().
 */
ਖਾਲੀ __attribute__( (ਰੁਕਾਵਟ(IPL1AUTO), ਸਦਿਸ਼(CORE_SOFTWARE_0_ਸਦਿਸ਼))) v_ਪੋਰਟ_Yield_ISR( ਖਾਲੀ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ਸਥਿਰ ਖਾਲੀ prvTaskExitError( ਖਾਲੀ );

/*-----------------------------------------------------------*/

/* Records the interrupt nesting depth.  This is initialised to one as it is
decremented to 0 when the first task starts. */
ਅਸਥਿਰ UBaseType_t ux_ਰੁਕਾਵਟ_Nesting = 0x01;

/* Stores the task stack pointer when a switch is made to use the system stack. */
UBaseType_t ux_Saved_Task_ਢੇਰ_ਸੂਚਕ = 0;

/* The stack used by interrupt service routines that cause a context switch. */
__attribute__ ((aligned(8))) ਢੇਰ_Type_t xISRStack[ config_ISR_ਢੇਰ_ਮਾਪ ] = { 0 };

/* The top of stack value ensures there is enough space to store 6 registers on
the callers stack, as some functions seem to want to do this. */
ਅਚਲ ਢੇਰ_Type_t * ਅਚਲ x_ISRStack_ਸਿਖਰ = &( xISRStack[ ( config_ISR_ਢੇਰ_ਮਾਪ & ~ਪੋਰਟ_BYTE_ALIGNMENT_ਨਕਾਬ ) - 8 ] );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਢੇਰ_Type_t *px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t *px_ਸਿਖਰ_ਦਾ_ਢੇਰ, TaskFunction_t px_ਕੋਡ, ਖਾਲੀ *pvParameters )
{
    /* Ensure 8 byte alignment is maintained when the context is popped from
     * stack. The size of the context is 33 words (132 bytes). */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = (ਢੇਰ_Type_t) 0xDEADBEEF;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = (ਢੇਰ_Type_t) 0x12345678;   /* Word to which the stack pointer will be left pointing after context restore. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = (ਢੇਰ_Type_t) _CP0_GET_CAUSE();
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = (ਢੇਰ_Type_t) ਪੋਰਟ_INITIAL_SR;/* CP0_STATUS */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = (ਢੇਰ_Type_t) px_ਕੋਡ;       /* CP0_EPC */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = (ਢੇਰ_Type_t) ਪੋਰਟ_TASK_RETURN_ਪਤਾ;  /* ra */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 15;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = (ਢੇਰ_Type_t) pvParameters; /* Parameters to pass in. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 15;

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prvTaskExitError( ਖਾਲੀ )
{
    /* A function that implements a task must not exit or attempt to return to
    its caller as there is nothing to return to.  If a task wants to exit it
    should instead call vTaskDelete( NULL ).

    Artificially force an assert() to be triggered if configASSERT() is
    defined, then stop here so application writers can catch the error. */
    configASSERT( ux_Saved_Task_ਢੇਰ_ਸੂਚਕ == 0UL );
    ਪੋਰਟ_DISABLE_INTERRUPTS();
    ਲਈ( ;; );
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
__attribute__(( weak )) ਖਾਲੀ v_Application_ਤਿਆਰੀ_Tick_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
ਅਚਲ uint32_t ul_Compare_ਮੇਲ = ( (configPERIPHERAL_CLOCK_HZ / ਪੋਰਟ_TIMER_PRESCALE) / config_TICK_ਦਰ_HZ ) - 1;

    T1CON = 0x0000;
    T1CONbits.TCKPS = ਪੋਰਟ_PRESCALE_ਬਿੱਟ;
    PR1 = ul_Compare_ਮੇਲ;
    IPC1bits.T1IP = config_KERNEL_ਰੁਕਾਵਟ_ਤਰਜੀਹ;

    /* Clear the interrupt as a starting condition. */
    IFS0bits.T1IF = 0;

    /* Enable the interrupt. */
    IEC0bits.T1IE = 1;

    /* Start the timer. */
    T1CONbits.TON = 1;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler(ਖਾਲੀ)
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( ux_ਰੁਕਾਵਟ_Nesting == 1000UL );
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task( ਖਾਲੀ );
ਬਾਹਰੀ ਖਾਲੀ *pxCurrentTCB;

    #ਜੇ ( config_CHECK_FOR_ਢੇਰ_ਉਛਾਲ > 2 )
    {
        /* Fill the ISR stack to make it easy to asses how much is being used. */
        memset( ( ਖਾਲੀ * ) xISRStack, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਆਕਾਰ( xISRStack ) );
    }
    #ਜੇ_ਅੰਤ /* configCHECK_FOR_STACK_OVERFLOW > 2 */

    /* Clear the software interrupt flag. */
    IFS0CLR = IFS0_CS0_IF_ਨਕਾਬ;

    /* Set software timer priority. */
    IPC0CLR = IPC0_CS0_IP_ਨਕਾਬ;
    IPC0_ਸੈੱਟ = ( config_KERNEL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << _IPC0_CS0IP_POSITION );

    /* Enable software interrupt. */
    IEC0CLR = IEC0_CS0_IE_ਨਕਾਬ;
    IEC0_ਸੈੱਟ = 1 << _IEC0_CS0IE_POSITION;

    /* Setup the timer to generate the tick.  Interrupts will have been
    disabled by the time we get here. */
    v_Application_ਤਿਆਰੀ_Tick_Timer_ਰੁਕਾਵਟ();

    /* Kick off the highest priority task that has been created so far.
    Its stack location is loaded into uxSavedTaskStackPointer. */
    ux_Saved_Task_ਢੇਰ_ਸੂਚਕ = *( UBaseType_t * ) pxCurrentTCB;
    v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();

    /* Should never get here as the tasks will now be executing!  Call the task
    exit error function to prevent compiler warnings about a static function
    not being called in the case that the application writer overrides this
    functionality by defining configTASK_RETURN_ADDRESS. */
    prvTaskExitError();

    ਵਾਪਸ pdFALSE;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Increment_Tick( ਖਾਲੀ )
{
UBaseType_t ux_Saved_ਸਥਿਤੀ;

    ux_Saved_ਸਥਿਤੀ = ux_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR();
    {
        ਜੇ( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            _CP0_BIS_CAUSE( ਪੋਰਟ_CORE_SW_0 );
        }
    }
    v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR( ux_Saved_ਸਥਿਤੀ );

    /* Look for the ISR stack getting near or past its limit. */
    ਪੋਰਟ_CHECK_ISR_ਢੇਰ();

    /* Clear timer interrupt. */
    config_CLEAR_TICK_TIMER_ਰੁਕਾਵਟ();
}
/*-----------------------------------------------------------*/

UBaseType_t ux_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR( ਖਾਲੀ )
{
UBaseType_t ux_Saved_ਸਥਿਤੀ_ਰਜਿਸਟਰ;

    __builtin_disable_interrupts();
    ux_Saved_ਸਥਿਤੀ_ਰਜਿਸਟਰ = CP0_GET_ਸਥਿਤੀ() | 0x01;
    /* This clears the IPL bits, then sets them to
    configMAX_SYSCALL_INTERRUPT_PRIORITY.  This function should not be called
    from an interrupt that has a priority above
    configMAX_SYSCALL_INTERRUPT_PRIORITY so, when used correctly, the action
    can only result in the IPL being unchanged or raised, and therefore never
    lowered. */
    CP0_ਸੈੱਟ_ਸਥਿਤੀ( ( ( ux_Saved_ਸਥਿਤੀ_ਰਜਿਸਟਰ & ( ~ਪੋਰਟ_ALL_IPL_ਬਿੱਟ ) ) ) | ( config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_IPL_ਖਿਸਕਾਓ ) );

    ਵਾਪਸ ux_Saved_ਸਥਿਤੀ_ਰਜਿਸਟਰ;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR( UBaseType_t ux_Saved_ਸਥਿਤੀ_ਰਜਿਸਟਰ )
{
    CP0_ਸੈੱਟ_ਸਥਿਤੀ( ux_Saved_ਸਥਿਤੀ_ਰਜਿਸਟਰ );
}
/*-----------------------------------------------------------*/
