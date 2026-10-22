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
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

/* Microchip includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ <xc.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <cp0defs.h>

#ਜੇ !defined(__MEC__)
    #ਗਲਤੀ This ਪੋਰਟ is designed ਮੰਜ਼ਿਲ work with XC32 on MEC14xx.  Please update your C compiler ਸੰਸਕਰਣ or settings.
#ਜੇ_ਅੰਤ

#ਜੇ( ( config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ >= 0x7 ) || ( config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ == 0 ) )
    #ਗਲਤੀ config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ must be less than 7 and greater than 0
#ਜੇ_ਅੰਤ

/* Bits within various registers. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IE_ਦੋਆਧਾਰੀ_ਅੰਕ                  ( 0x00000001 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXL_ਦੋਆਧਾਰੀ_ਅੰਕ                 ( 0x00000002 )

/* The EXL bit is set to ensure interrupts do not occur while the context of
the first task is being restored.  MEC14xx does not have DSP HW. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_SR              ( ਪੋਰਟ_IE_ਦੋਆਧਾਰੀ_ਅੰਕ | ਪੋਰਟ_EXL_ਦੋਆਧਾਰੀ_ਅੰਕ )

/* MEC14xx RTOS Timer MMCR's. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MMCR_RTMR_PRELOAD   *((ਅਸਥਿਰ uint32_t *)(0xA0007404ul))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MMCR_RTMR_CONTROL   *((ਅਸਥਿਰ uint32_t *)(0xA0007408ul))

/* MEC14xx JTVIC external interrupt controller is mapped to M14K closely-coupled
peripheral space. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GIRQ23_RTOS_TIMER_BITPOS    ( 4 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GIRQ23_RTOS_TIMER_ਨਕਾਬ      ( 1ul << ( ਪੋਰਟ_GIRQ23_RTOS_TIMER_BITPOS ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MMCR_JTVIC_GIRQ23_SRC       *((ਅਸਥਿਰ uint32_t *)(0xBFFFC0F0ul))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MMCR_JTVIC_GIRQ23_SETEN     *((ਅਸਥਿਰ uint32_t *)(0xBFFFC0F4ul))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MMCR_JTVIC_GIRQ23_PRIA      *((ਅਸਥਿਰ uint32_t *)(0xBFFFC3F0ul))

/* MIPS Software Interrupts are routed through JTVIC GIRQ24 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GIRQ24_M14_K_SOFTIRQ0_BITPOS ( 1 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GIRQ24_M14_K_SOFTIRQ0_ਨਕਾਬ   ( 1ul << ( ਪੋਰਟ_GIRQ24_M14_K_SOFTIRQ0_BITPOS ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MMCR_JTVIC_GIRQ24_SRC       *((ਅਸਥਿਰ uint32_t *)(0xBFFFC100ul))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MMCR_JTVIC_GIRQ24_SETEN     *((ਅਸਥਿਰ uint32_t *)(0xBFFFC104ul))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MMCR_JTVIC_GIRQ24_PRIA      *((ਅਸਥਿਰ uint32_t *)(0xBFFFC400ul))

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
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_TICK_ਰੁਕਾਵਟ_ਸਦਿਸ਼
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_TICK_ਰੁਕਾਵਟ_ਸਦਿਸ਼ girq23_b4
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_CLEAR_TICK_TIMER_ਰੁਕਾਵਟ() ਪੋਰਟ_MMCR_JTVIC_GIRQ23_SRC = ਪੋਰਟ_GIRQ23_RTOS_TIMER_ਨਕਾਬ
#ਨਹੀਂਤਾਂ
    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_CLEAR_TICK_TIMER_ਰੁਕਾਵਟ
        #ਗਲਤੀ If config_TICK_ਰੁਕਾਵਟ_ਸਦਿਸ਼ is defined ਵਿੱਚ_2 application ਕੋਡ then config_CLEAR_TICK_TIMER_ਰੁਕਾਵਟ must also be defined ਵਿੱਚ_2 application ਕੋਡ.
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

/* Let the user override the pre-loading of the initial RA with the address of
prvTaskExitError() in case it messes up unwinding of the stack in the debugger -
in which case configTASK_RETURN_ADDRESS can be defined as 0 (NULL). */
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
ਢੇਰ_Type_t xISRStack[ config_ISR_ਢੇਰ_ਮਾਪ ] = { 0 };

/* The top of stack value ensures there is enough space to store 6 registers on
the callers stack, as some functions seem to want to do this. */
ਅਚਲ ਢੇਰ_Type_t * ਅਚਲ x_ISRStack_ਸਿਖਰ = &( xISRStack[ config_ISR_ਢੇਰ_ਮਾਪ - 7 ] );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਢੇਰ_Type_t *px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t *px_ਸਿਖਰ_ਦਾ_ਢੇਰ, TaskFunction_t px_ਕੋਡ, ਖਾਲੀ *pvParameters )
{
    /* Ensure byte alignment is maintained when leaving this function. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = (ਢੇਰ_Type_t) 0xDEADBEEF;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = (ਢੇਰ_Type_t) 0x12345678;   /* Word to which the stack pointer will be left pointing after context restore. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = (ਢੇਰ_Type_t) ul_ਪੋਰਟ_Get_CP0_Cause();
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = (ਢੇਰ_Type_t) ਪੋਰਟ_INITIAL_SR;   /* CP0_STATUS */
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

ਸਥਿਰ __inline uint32_t prv_Disable_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
uint32_t prev_state;

    __asm ਅਸਥਿਰ( "di %0; ehb" : "=r" ( prev_state ) :: "memory" );
    ਵਾਪਸ prev_state;
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
 * Setup a timer for a regular tick.  This function uses the RTOS timer.
 * The function is declared weak so an application writer can use a different
 * timer by redefining this implementation.  If a different timer is used then
 * configTICK_INTERRUPT_VECTOR must also be defined in FreeRTOSConfig.h to
 * ensure the RTOS provided tick interrupt handler is installed on the correct
 * vector number.
 */
__attribute__(( weak )) ਖਾਲੀ v_Application_ਤਿਆਰੀ_Tick_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
/* MEC14xx RTOS Timer whose input clock is 32KHz. */
ਅਚਲ uint32_t ulPreload = ( 32768ul / ( config_TICK_ਦਰ_HZ ) );

    configASSERT( ulPreload != 0UL );

    /* Configure the RTOS timer. */
    ਪੋਰਟ_MMCR_RTMR_CONTROL = 0ul;
    ਪੋਰਟ_MMCR_RTMR_PRELOAD = ulPreload;

    /* Configure interrupts from the RTOS timer. */
    ਪੋਰਟ_MMCR_JTVIC_GIRQ23_SRC = ( ਪੋਰਟ_GIRQ23_RTOS_TIMER_ਨਕਾਬ );
    ਪੋਰਟ_MMCR_JTVIC_GIRQ23_PRIA &= ~( 0x0Ful << 16 );
    ਪੋਰਟ_MMCR_JTVIC_GIRQ23_PRIA |= ( ( ਪੋਰਟ_IPL_ਮੰਜ਼ਿਲ_ਕੋਡ( config_KERNEL_ਰੁਕਾਵਟ_ਤਰਜੀਹ ) ) << 16 );
    ਪੋਰਟ_MMCR_JTVIC_GIRQ23_SETEN = ( ਪੋਰਟ_GIRQ23_RTOS_TIMER_ਨਕਾਬ );

    /* Enable the RTOS timer. */
    ਪੋਰਟ_MMCR_RTMR_CONTROL = 0x0Fu;
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
    ਪੋਰਟ_MMCR_JTVIC_GIRQ24_SRC = (ਪੋਰਟ_GIRQ24_M14_K_SOFTIRQ0_ਨਕਾਬ);

    /* Set software timer priority.  Each GIRQn has one nibble containing its
ਤਰਜੀਹ*/
    ਪੋਰਟ_MMCR_JTVIC_GIRQ24_PRIA &= ~(0xF0ul);
    ਪੋਰਟ_MMCR_JTVIC_GIRQ24_PRIA |= ( ਪੋਰਟ_IPL_ਮੰਜ਼ਿਲ_ਕੋਡ( config_KERNEL_ਰੁਕਾਵਟ_ਤਰਜੀਹ ) << 4 );

    /* Enable software interrupt. */
    ਪੋਰਟ_MMCR_JTVIC_GIRQ24_SETEN = ( ਪੋਰਟ_GIRQ24_M14_K_SOFTIRQ0_ਨਕਾਬ );

    /* Setup the timer to generate the tick.  Interrupts will have been disabled
    by the time we get here. */
    v_Application_ਤਿਆਰੀ_Tick_Timer_ਰੁਕਾਵਟ();

    /* Start the highest priority task that has been created so far.  Its stack
    location is loaded into uxSavedTaskStackPointer. */
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
uint32_t ulCause;

    ux_Saved_ਸਥਿਤੀ = ux_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR();
    {
        ਜੇ( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            ulCause = ul_ਪੋਰਟ_Get_CP0_Cause();
            ulCause |= ( 1ul << 8UL );
            v_ਪੋਰਟ_ਸੈੱਟ_CP0_Cause( ulCause );
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

    prv_Disable_ਰੁਕਾਵਟ();
    ux_Saved_ਸਥਿਤੀ_ਰਜਿਸਟਰ = ul_ਪੋਰਟ_Get_CP0_ਸਥਿਤੀ() | 0x01;

    /* This clears the IPL bits, then sets them to
    configMAX_SYSCALL_INTERRUPT_PRIORITY.  This function should not be called
    from an interrupt that has a priority above
    configMAX_SYSCALL_INTERRUPT_PRIORITY so, when used correctly, the action
    can only result in the IPL being unchanged or raised, and therefore never
    lowered. */
    v_ਪੋਰਟ_ਸੈੱਟ_CP0_ਸਥਿਤੀ( ( ( ux_Saved_ਸਥਿਤੀ_ਰਜਿਸਟਰ & ( ~ਪੋਰਟ_ALL_IPL_ਬਿੱਟ ) ) ) | ( config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_IPL_ਖਿਸਕਾਓ ) );

    ਵਾਪਸ ux_Saved_ਸਥਿਤੀ_ਰਜਿਸਟਰ;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR( UBaseType_t ux_Saved_ਸਥਿਤੀ_ਰਜਿਸਟਰ )
{
    v_ਪੋਰਟ_ਸੈੱਟ_CP0_ਸਥਿਤੀ( ux_Saved_ਸਥਿਤੀ_ਰਜਿਸਟਰ );
}
/*-----------------------------------------------------------*/
