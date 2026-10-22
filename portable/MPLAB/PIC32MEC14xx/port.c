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
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* Microchip includes. */
#ಅನ್ತರ್ಭಾವ <xc.h>
#ಅನ್ತರ್ಭಾವ <cp0defs.h>

#ಆದರೆ !defined(__MEC__)
    #ದೋಷ This ಪೋರ್ಟ್ is designed ಗಮ್ಯ work with XC32 on MEC14xx.  Please update your C compiler ಆವೃತ್ತಿ or settings.
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ( ( config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ >= 0x7 ) || ( config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ == 0 ) )
    #ದೋಷ config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ must be less than 7 and greater than 0
#ಆದರೆ_ಅಂತ್ಯ

/* Bits within various registers. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IE_ಬಿಟ್                  ( 0x00000001 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXL_ಬಿಟ್                 ( 0x00000002 )

/* The EXL bit is set to ensure interrupts do not occur while the context of
the first task is being restored.  MEC14xx does not have DSP HW. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_SR              ( ಪೋರ್ಟ್_IE_ಬಿಟ್ | ಪೋರ್ಟ್_EXL_ಬಿಟ್ )

/* MEC14xx RTOS Timer MMCR's. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MMCR_RTMR_PRELOAD   *((ಅಸ್ಥಿರ uint32_t *)(0xA0007404ul))
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MMCR_RTMR_CONTROL   *((ಅಸ್ಥಿರ uint32_t *)(0xA0007408ul))

/* MEC14xx JTVIC external interrupt controller is mapped to M14K closely-coupled
peripheral space. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GIRQ23_RTOS_TIMER_BITPOS    ( 4 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GIRQ23_RTOS_TIMER_ಮುಖವಾಡ      ( 1ul << ( ಪೋರ್ಟ್_GIRQ23_RTOS_TIMER_BITPOS ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MMCR_JTVIC_GIRQ23_SRC       *((ಅಸ್ಥಿರ uint32_t *)(0xBFFFC0F0ul))
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MMCR_JTVIC_GIRQ23_SETEN     *((ಅಸ್ಥಿರ uint32_t *)(0xBFFFC0F4ul))
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MMCR_JTVIC_GIRQ23_PRIA      *((ಅಸ್ಥಿರ uint32_t *)(0xBFFFC3F0ul))

/* MIPS Software Interrupts are routed through JTVIC GIRQ24 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GIRQ24_M14_K_SOFTIRQ0_BITPOS ( 1 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GIRQ24_M14_K_SOFTIRQ0_ಮುಖವಾಡ   ( 1ul << ( ಪೋರ್ಟ್_GIRQ24_M14_K_SOFTIRQ0_BITPOS ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MMCR_JTVIC_GIRQ24_SRC       *((ಅಸ್ಥಿರ uint32_t *)(0xBFFFC100ul))
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MMCR_JTVIC_GIRQ24_SETEN     *((ಅಸ್ಥಿರ uint32_t *)(0xBFFFC104ul))
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MMCR_JTVIC_GIRQ24_PRIA      *((ಅಸ್ಥಿರ uint32_t *)(0xBFFFC400ul))

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
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_TICK_ಅಡಚಣೆ_ಸದಿಶ
    #ವ್ಯಾಖ್ಯಾನಿಸು config_TICK_ಅಡಚಣೆ_ಸದಿಶ girq23_b4
    #ವ್ಯಾಖ್ಯಾನಿಸು config_CLEAR_TICK_TIMER_ಅಡಚಣೆ() ಪೋರ್ಟ್_MMCR_JTVIC_GIRQ23_SRC = ಪೋರ್ಟ್_GIRQ23_RTOS_TIMER_ಮುಖವಾಡ
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_CLEAR_TICK_TIMER_ಅಡಚಣೆ
        #ದೋಷ If config_TICK_ಅಡಚಣೆ_ಸದಿಶ is defined ಒಳ application ಸಂಕೇತ_2 then config_CLEAR_TICK_TIMER_ಅಡಚಣೆ must also be defined ಒಳ application ಸಂಕೇತ_2.
    #ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

/* Let the user override the pre-loading of the initial RA with the address of
prvTaskExitError() in case it messes up unwinding of the stack in the debugger -
in which case configTASK_RETURN_ADDRESS can be defined as 0 (NULL). */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ config_TASK_RETURN_ವಿಳಾಸ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ config_TASK_RETURN_ವಿಳಾಸ
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ prvTaskExitError
#ಆದರೆ_ಅಂತ್ಯ

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
stack checking.  A problem in the ISR stack will trigger an assert, not call the
stack overflow hook function (because the stack overflow hook is specific to a
task stack, not the ISR stack). */
#ಆದರೆ( config_CHECK_FOR_ರಾಶಿ_ಅತಿಪ್ರವಾಹ > 2 )

    /* Don't use 0xa5 as the stack fill bytes as that is used by the kernel for
    the task stacks, and so will legitimately appear in many positions within
    the ISR stack. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE 0xee

    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint8_t uc_Expected_ರಾಶಿ_ಬೈಟುಗಳು[] = {
                            ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE,     \
                            ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE,     \
                            ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE,     \
                            ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE,     \
                            ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE };   \

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CHECK_ISR_ರಾಶಿ() configASSERT( ( memcmp( ( ಶೂನ್ಯ * ) xISRStack, ( ಶೂನ್ಯ * ) uc_Expected_ರಾಶಿ_ಬೈಟುಗಳು, ಗಾತ್ರ( uc_Expected_ರಾಶಿ_ಬೈಟುಗಳು ) ) == 0 ) )
#ಇಲ್ಲದಿದ್ದರೆ
    /* Define the function away. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CHECK_ISR_ರಾಶಿ()
#ಆದರೆ_ಅಂತ್ಯ /* configCHECK_FOR_STACK_OVERFLOW > 2 */


/*-----------------------------------------------------------*/

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ );

/*-----------------------------------------------------------*/

/* Records the interrupt nesting depth.  This is initialised to one as it is
decremented to 0 when the first task starts. */
ಅಸ್ಥಿರ UBaseType_t ux_ಅಡಚಣೆ_Nesting = 0x01;

/* Stores the task stack pointer when a switch is made to use the system stack. */
UBaseType_t ux_Saved_Task_ರಾಶಿ_ಸೂಚಕ = 0;

/* The stack used by interrupt service routines that cause a context switch. */
ರಾಶಿ_Type_t xISRStack[ config_ISR_ರಾಶಿ_ಗಾತ್ರ ] = { 0 };

/* The top of stack value ensures there is enough space to store 6 registers on
the callers stack, as some functions seem to want to do this. */
ಸ್ಥಿರಾಂಕ ರಾಶಿ_Type_t * ಸ್ಥಿರಾಂಕ x_ISRStack_ತುದಿ = &( xISRStack[ config_ISR_ರಾಶಿ_ಗಾತ್ರ - 7 ] );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t *px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t *px_ತುದಿ_ದ_ರಾಶಿ, TaskFunction_t px_ಸಂಕೇತ, ಶೂನ್ಯ *pvParameters )
{
    /* Ensure byte alignment is maintained when leaving this function. */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    *px_ತುದಿ_ದ_ರಾಶಿ = (ರಾಶಿ_Type_t) 0xDEADBEEF;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    *px_ತುದಿ_ದ_ರಾಶಿ = (ರಾಶಿ_Type_t) 0x12345678;   /* Word to which the stack pointer will be left pointing after context restore. */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    *px_ತುದಿ_ದ_ರಾಶಿ = (ರಾಶಿ_Type_t) ul_ಪೋರ್ಟ್_Get_CP0_Cause();
    px_ತುದಿ_ದ_ರಾಶಿ--;

    *px_ತುದಿ_ದ_ರಾಶಿ = (ರಾಶಿ_Type_t) ಪೋರ್ಟ್_INITIAL_SR;   /* CP0_STATUS */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    *px_ತುದಿ_ದ_ರಾಶಿ = (ರಾಶಿ_Type_t) px_ಸಂಕೇತ;       /* CP0_EPC */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    *px_ತುದಿ_ದ_ರಾಶಿ = (ರಾಶಿ_Type_t) ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ;  /* ra */
    px_ತುದಿ_ದ_ರಾಶಿ -= 15;

    *px_ತುದಿ_ದ_ರಾಶಿ = (ರಾಶಿ_Type_t) pvParameters; /* Parameters to pass in. */
    px_ತುದಿ_ದ_ರಾಶಿ -= 15;

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ __inline uint32_t prv_Disable_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
uint32_t prev_state;

    __asm ಅಸ್ಥಿರ( "di %0; ehb" : "=r" ( prev_state ) :: "memory" );
    ಹಿಂತಿರುಗಿ prev_state;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ )
{
    /* A function that implements a task must not exit or attempt to return to
    its caller as there is nothing to return to.  If a task wants to exit it
    should instead call vTaskDelete( NULL ).

    Artificially force an assert() to be triggered if configASSERT() is
    defined, then stop here so application writers can catch the error. */
    configASSERT( ux_Saved_Task_ರಾಶಿ_ಸೂಚಕ == 0UL );
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();
    ಗಾಗಿ( ;; );
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
__attribute__(( weak )) ಶೂನ್ಯ v_Application_ಸಿದ್ಧತೆ_Tick_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
/* MEC14xx RTOS Timer whose input clock is 32KHz. */
ಸ್ಥಿರಾಂಕ uint32_t ulPreload = ( 32768ul / ( config_TICK_ದರ_HZ ) );

    configASSERT( ulPreload != 0UL );

    /* Configure the RTOS timer. */
    ಪೋರ್ಟ್_MMCR_RTMR_CONTROL = 0ul;
    ಪೋರ್ಟ್_MMCR_RTMR_PRELOAD = ulPreload;

    /* Configure interrupts from the RTOS timer. */
    ಪೋರ್ಟ್_MMCR_JTVIC_GIRQ23_SRC = ( ಪೋರ್ಟ್_GIRQ23_RTOS_TIMER_ಮುಖವಾಡ );
    ಪೋರ್ಟ್_MMCR_JTVIC_GIRQ23_PRIA &= ~( 0x0Ful << 16 );
    ಪೋರ್ಟ್_MMCR_JTVIC_GIRQ23_PRIA |= ( ( ಪೋರ್ಟ್_IPL_ಗಮ್ಯ_ಸಂಕೇತ( config_KERNEL_ಅಡಚಣೆ_ಆದ್ಯತೆ ) ) << 16 );
    ಪೋರ್ಟ್_MMCR_JTVIC_GIRQ23_SETEN = ( ಪೋರ್ಟ್_GIRQ23_RTOS_TIMER_ಮುಖವಾಡ );

    /* Enable the RTOS timer. */
    ಪೋರ್ಟ್_MMCR_RTMR_CONTROL = 0x0Fu;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler(ಶೂನ್ಯ)
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( ux_ಅಡಚಣೆ_Nesting == 1000UL );
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ *pxCurrentTCB;

    #ಆದರೆ ( config_CHECK_FOR_ರಾಶಿ_ಅತಿಪ್ರವಾಹ > 2 )
    {
        /* Fill the ISR stack to make it easy to asses how much is being used. */
        memset( ( ಶೂನ್ಯ * ) xISRStack, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_BYTE, ಗಾತ್ರ( xISRStack ) );
    }
    #ಆದರೆ_ಅಂತ್ಯ /* configCHECK_FOR_STACK_OVERFLOW > 2 */

    /* Clear the software interrupt flag. */
    ಪೋರ್ಟ್_MMCR_JTVIC_GIRQ24_SRC = (ಪೋರ್ಟ್_GIRQ24_M14_K_SOFTIRQ0_ಮುಖವಾಡ);

    /* Set software timer priority.  Each GIRQn has one nibble containing its
ಆದ್ಯತೆ*/
    ಪೋರ್ಟ್_MMCR_JTVIC_GIRQ24_PRIA &= ~(0xF0ul);
    ಪೋರ್ಟ್_MMCR_JTVIC_GIRQ24_PRIA |= ( ಪೋರ್ಟ್_IPL_ಗಮ್ಯ_ಸಂಕೇತ( config_KERNEL_ಅಡಚಣೆ_ಆದ್ಯತೆ ) << 4 );

    /* Enable software interrupt. */
    ಪೋರ್ಟ್_MMCR_JTVIC_GIRQ24_SETEN = ( ಪೋರ್ಟ್_GIRQ24_M14_K_SOFTIRQ0_ಮುಖವಾಡ );

    /* Setup the timer to generate the tick.  Interrupts will have been disabled
    by the time we get here. */
    v_Application_ಸಿದ್ಧತೆ_Tick_Timer_ಅಡಚಣೆ();

    /* Start the highest priority task that has been created so far.  Its stack
    location is loaded into uxSavedTaskStackPointer. */
    ux_Saved_Task_ರಾಶಿ_ಸೂಚಕ = *( UBaseType_t * ) pxCurrentTCB;
    v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task();

    /* Should never get here as the tasks will now be executing!  Call the task
    exit error function to prevent compiler warnings about a static function
    not being called in the case that the application writer overrides this
    functionality by defining configTASK_RETURN_ADDRESS. */
    prvTaskExitError();

    ಹಿಂತಿರುಗಿ pdFALSE;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Increment_Tick( ಶೂನ್ಯ )
{
UBaseType_t ux_Saved_ಸ್ಥಿತಿ;
uint32_t ulCause;

    ux_Saved_ಸ್ಥಿತಿ = ux_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR();
    {
        ಆದರೆ( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            ulCause = ul_ಪೋರ್ಟ್_Get_CP0_Cause();
            ulCause |= ( 1ul << 8UL );
            v_ಪೋರ್ಟ್_ಗಣ_CP0_Cause( ulCause );
        }
    }
    v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR( ux_Saved_ಸ್ಥಿತಿ );

    /* Look for the ISR stack getting near or past its limit. */
    ಪೋರ್ಟ್_CHECK_ISR_ರಾಶಿ();

    /* Clear timer interrupt. */
    config_CLEAR_TICK_TIMER_ಅಡಚಣೆ();
}
/*-----------------------------------------------------------*/

UBaseType_t ux_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR( ಶೂನ್ಯ )
{
UBaseType_t ux_Saved_ಸ್ಥಿತಿ_ರಿಜಿಸ್ಟರ್;

    prv_Disable_ಅಡಚಣೆ();
    ux_Saved_ಸ್ಥಿತಿ_ರಿಜಿಸ್ಟರ್ = ul_ಪೋರ್ಟ್_Get_CP0_ಸ್ಥಿತಿ() | 0x01;

    /* This clears the IPL bits, then sets them to
    configMAX_SYSCALL_INTERRUPT_PRIORITY.  This function should not be called
    from an interrupt that has a priority above
    configMAX_SYSCALL_INTERRUPT_PRIORITY so, when used correctly, the action
    can only result in the IPL being unchanged or raised, and therefore never
    lowered. */
    v_ಪೋರ್ಟ್_ಗಣ_CP0_ಸ್ಥಿತಿ( ( ( ux_Saved_ಸ್ಥಿತಿ_ರಿಜಿಸ್ಟರ್ & ( ~ಪೋರ್ಟ್_ALL_IPL_ಬಿಟ್ಟುಗಳು ) ) ) | ( config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_IPL_ಸರಿಸು ) );

    ಹಿಂತಿರುಗಿ ux_Saved_ಸ್ಥಿತಿ_ರಿಜಿಸ್ಟರ್;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR( UBaseType_t ux_Saved_ಸ್ಥಿತಿ_ರಿಜಿಸ್ಟರ್ )
{
    v_ಪೋರ್ಟ್_ಗಣ_CP0_ಸ್ಥಿತಿ( ux_Saved_ಸ್ಥಿತಿ_ರಿಜಿಸ್ಟರ್ );
}
/*-----------------------------------------------------------*/
