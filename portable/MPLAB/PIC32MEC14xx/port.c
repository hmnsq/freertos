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
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Microchip includes. */
#ضمن <xc.h>
#ضمن <cp0defs.h>

#إذا !defined(__MEC__)
    #تېروتنه This پورټ is designed منزل work with XC32 on MEC14xx.  Please update your C compiler نسخه or settings.
#د_که_پای

#إذا( ( config_MAX_SYSCALL_مداخله_لومړیتوب >= 0x7 ) || ( config_MAX_SYSCALL_مداخله_لومړیتوب == 0 ) )
    #تېروتنه config_MAX_SYSCALL_مداخله_لومړیتوب must be less than 7 and greater than 0
#د_که_پای

/* Bits within various registers. */
#تعریف_کړه پورټ_IE_بټ                  ( 0x00000001 )
#تعریف_کړه پورټ_EXL_بټ                 ( 0x00000002 )

/* The EXL bit is set to ensure interrupts do not occur while the context of
the first task is being restored.  MEC14xx does not have DSP HW. */
#تعریف_کړه پورټ_INITIAL_SR              ( پورټ_IE_بټ | پورټ_EXL_بټ )

/* MEC14xx RTOS Timer MMCR's. */
#تعریف_کړه پورټ_MMCR_RTMR_PRELOAD   *((متطاير uint32_t *)(0xA0007404ul))
#تعریف_کړه پورټ_MMCR_RTMR_CONTROL   *((متطاير uint32_t *)(0xA0007408ul))

/* MEC14xx JTVIC external interrupt controller is mapped to M14K closely-coupled
peripheral space. */
#تعریف_کړه پورټ_GIRQ23_RTOS_TIMER_BITPOS    ( 4 )
#تعریف_کړه پورټ_GIRQ23_RTOS_TIMER_ماسک      ( 1ul << ( پورټ_GIRQ23_RTOS_TIMER_BITPOS ) )
#تعریف_کړه پورټ_MMCR_JTVIC_GIRQ23_SRC       *((متطاير uint32_t *)(0xBFFFC0F0ul))
#تعریف_کړه پورټ_MMCR_JTVIC_GIRQ23_SETEN     *((متطاير uint32_t *)(0xBFFFC0F4ul))
#تعریف_کړه پورټ_MMCR_JTVIC_GIRQ23_PRIA      *((متطاير uint32_t *)(0xBFFFC3F0ul))

/* MIPS Software Interrupts are routed through JTVIC GIRQ24 */
#تعریف_کړه پورټ_GIRQ24_M14_K_SOFTIRQ0_BITPOS ( 1 )
#تعریف_کړه پورټ_GIRQ24_M14_K_SOFTIRQ0_ماسک   ( 1ul << ( پورټ_GIRQ24_M14_K_SOFTIRQ0_BITPOS ) )
#تعریف_کړه پورټ_MMCR_JTVIC_GIRQ24_SRC       *((متطاير uint32_t *)(0xBFFFC100ul))
#تعریف_کړه پورټ_MMCR_JTVIC_GIRQ24_SETEN     *((متطاير uint32_t *)(0xBFFFC104ul))
#تعریف_کړه پورټ_MMCR_JTVIC_GIRQ24_PRIA      *((متطاير uint32_t *)(0xBFFFC400ul))

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
#که_نه_تعریف_شوی config_TICK_مداخله_ویکټور
    #تعریف_کړه config_TICK_مداخله_ویکټور girq23_b4
    #تعریف_کړه config_CLEAR_TICK_TIMER_مداخله() پورټ_MMCR_JTVIC_GIRQ23_SRC = پورټ_GIRQ23_RTOS_TIMER_ماسک
#وإلا
    #که_نه_تعریف_شوی config_CLEAR_TICK_TIMER_مداخله
        #تېروتنه If config_TICK_مداخله_ویکټور is defined دننه application کوډ then config_CLEAR_TICK_TIMER_مداخله must also be defined دننه application کوډ.
    #د_که_پای
#د_که_پای

/* Let the user override the pre-loading of the initial RA with the address of
prvTaskExitError() in case it messes up unwinding of the stack in the debugger -
in which case configTASK_RETURN_ADDRESS can be defined as 0 (NULL). */
#که_تعریف_شوی config_TASK_RETURN_پته
    #تعریف_کړه پورټ_TASK_RETURN_پته config_TASK_RETURN_پته
#وإلا
    #تعریف_کړه پورټ_TASK_RETURN_پته prvTaskExitError
#د_که_پای

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
stack checking.  A problem in the ISR stack will trigger an assert, not call the
stack overflow hook function (because the stack overflow hook is specific to a
task stack, not the ISR stack). */
#إذا( config_CHECK_FOR_ډېری_ډکېدنه > 2 )

    /* Don't use 0xa5 as the stack fill bytes as that is used by the kernel for
    the task stacks, and so will legitimately appear in many positions within
    the ISR stack. */
    #تعریف_کړه پورټ_ISR_ډېری_FILL_BYTE 0xee

    ساكن ثابت uint8_t uc_Expected_ډېری_بایټونه[] = {
                            پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE,     \
                            پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE,     \
                            پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE,     \
                            پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE,     \
                            پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE };   \

    #تعریف_کړه پورټ_CHECK_ISR_ډېری() configASSERT( ( memcmp( ( فراغ * ) xISRStack, ( فراغ * ) uc_Expected_ډېری_بایټونه, حجم( uc_Expected_ډېری_بایټونه ) ) == 0 ) )
#وإلا
    /* Define the function away. */
    #تعریف_کړه پورټ_CHECK_ISR_ډېری()
#د_که_پای /* configCHECK_FOR_STACK_OVERFLOW > 2 */


/*-----------------------------------------------------------*/

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/*-----------------------------------------------------------*/

/* Records the interrupt nesting depth.  This is initialised to one as it is
decremented to 0 when the first task starts. */
متطاير UBaseType_t ux_مداخله_Nesting = 0x01;

/* Stores the task stack pointer when a switch is made to use the system stack. */
UBaseType_t ux_Saved_Task_ډېری_اشاره_ګر = 0;

/* The stack used by interrupt service routines that cause a context switch. */
ډېری_Type_t xISRStack[ config_ISR_ډېری_اندازه ] = { 0 };

/* The top of stack value ensures there is enough space to store 6 registers on
the callers stack, as some functions seem to want to do this. */
ثابت ډېری_Type_t * ثابت x_ISRStack_سر = &( xISRStack[ config_ISR_ډېری_اندازه - 7 ] );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ډېری_Type_t *px_پورټ_Initialise_ډېری( ډېری_Type_t *px_سر_د_ډېری, TaskFunction_t px_کوډ, فراغ *pvParameters )
{
    /* Ensure byte alignment is maintained when leaving this function. */
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = (ډېری_Type_t) 0xDEADBEEF;
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = (ډېری_Type_t) 0x12345678;   /* Word to which the stack pointer will be left pointing after context restore. */
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = (ډېری_Type_t) ul_پورټ_Get_CP0_Cause();
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = (ډېری_Type_t) پورټ_INITIAL_SR;   /* CP0_STATUS */
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = (ډېری_Type_t) px_کوډ;       /* CP0_EPC */
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = (ډېری_Type_t) پورټ_TASK_RETURN_پته;  /* ra */
    px_سر_د_ډېری -= 15;

    *px_سر_د_ډېری = (ډېری_Type_t) pvParameters; /* Parameters to pass in. */
    px_سر_د_ډېری -= 15;

    أرجع px_سر_د_ډېری;
}
/*-----------------------------------------------------------*/

ساكن __inline uint32_t prv_Disable_مداخله( فراغ )
{
uint32_t prev_state;

    __asm متطاير( "di %0; ehb" : "=r" ( prev_state ) :: "memory" );
    أرجع prev_state;
}
/*-----------------------------------------------------------*/

ساكن فراغ prvTaskExitError( فراغ )
{
    /* A function that implements a task must not exit or attempt to return to
    its caller as there is nothing to return to.  If a task wants to exit it
    should instead call vTaskDelete( NULL ).

    Artificially force an assert() to be triggered if configASSERT() is
    defined, then stop here so application writers can catch the error. */
    configASSERT( ux_Saved_Task_ډېری_اشاره_ګر == 0UL );
    پورټ_DISABLE_INTERRUPTS();
    لكل( ;; );
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
__attribute__(( weak )) فراغ v_Application_تیاری_Tick_Timer_مداخله( فراغ )
{
/* MEC14xx RTOS Timer whose input clock is 32KHz. */
ثابت uint32_t ulPreload = ( 32768ul / ( config_TICK_شرح_HZ ) );

    configASSERT( ulPreload != 0UL );

    /* Configure the RTOS timer. */
    پورټ_MMCR_RTMR_CONTROL = 0ul;
    پورټ_MMCR_RTMR_PRELOAD = ulPreload;

    /* Configure interrupts from the RTOS timer. */
    پورټ_MMCR_JTVIC_GIRQ23_SRC = ( پورټ_GIRQ23_RTOS_TIMER_ماسک );
    پورټ_MMCR_JTVIC_GIRQ23_PRIA &= ~( 0x0Ful << 16 );
    پورټ_MMCR_JTVIC_GIRQ23_PRIA |= ( ( پورټ_IPL_منزل_کوډ( config_KERNEL_مداخله_لومړیتوب ) ) << 16 );
    پورټ_MMCR_JTVIC_GIRQ23_SETEN = ( پورټ_GIRQ23_RTOS_TIMER_ماسک );

    /* Enable the RTOS timer. */
    پورټ_MMCR_RTMR_CONTROL = 0x0Fu;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler(فراغ)
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( ux_مداخله_Nesting == 1000UL );
}
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
خارجي فراغ v_پورټ_پیل_لومړی_Task( فراغ );
خارجي فراغ *pxCurrentTCB;

    #إذا ( config_CHECK_FOR_ډېری_ډکېدنه > 2 )
    {
        /* Fill the ISR stack to make it easy to asses how much is being used. */
        memset( ( فراغ * ) xISRStack, پورټ_ISR_ډېری_FILL_BYTE, حجم( xISRStack ) );
    }
    #د_که_پای /* configCHECK_FOR_STACK_OVERFLOW > 2 */

    /* Clear the software interrupt flag. */
    پورټ_MMCR_JTVIC_GIRQ24_SRC = (پورټ_GIRQ24_M14_K_SOFTIRQ0_ماسک);

    /* Set software timer priority.  Each GIRQn has one nibble containing its
لومړیتوب*/
    پورټ_MMCR_JTVIC_GIRQ24_PRIA &= ~(0xF0ul);
    پورټ_MMCR_JTVIC_GIRQ24_PRIA |= ( پورټ_IPL_منزل_کوډ( config_KERNEL_مداخله_لومړیتوب ) << 4 );

    /* Enable software interrupt. */
    پورټ_MMCR_JTVIC_GIRQ24_SETEN = ( پورټ_GIRQ24_M14_K_SOFTIRQ0_ماسک );

    /* Setup the timer to generate the tick.  Interrupts will have been disabled
    by the time we get here. */
    v_Application_تیاری_Tick_Timer_مداخله();

    /* Start the highest priority task that has been created so far.  Its stack
    location is loaded into uxSavedTaskStackPointer. */
    ux_Saved_Task_ډېری_اشاره_ګر = *( UBaseType_t * ) pxCurrentTCB;
    v_پورټ_پیل_لومړی_Task();

    /* Should never get here as the tasks will now be executing!  Call the task
    exit error function to prevent compiler warnings about a static function
    not being called in the case that the application writer overrides this
    functionality by defining configTASK_RETURN_ADDRESS. */
    prvTaskExitError();

    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Increment_Tick( فراغ )
{
UBaseType_t ux_Saved_حالت;
uint32_t ulCause;

    ux_Saved_حالت = ux_پورټ_سېټ_مداخله_ماسک_From_ISR();
    {
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            ulCause = ul_پورټ_Get_CP0_Cause();
            ulCause |= ( 1ul << 8UL );
            v_پورټ_سېټ_CP0_Cause( ulCause );
        }
    }
    v_پورټ_Clear_مداخله_ماسک_From_ISR( ux_Saved_حالت );

    /* Look for the ISR stack getting near or past its limit. */
    پورټ_CHECK_ISR_ډېری();

    /* Clear timer interrupt. */
    config_CLEAR_TICK_TIMER_مداخله();
}
/*-----------------------------------------------------------*/

UBaseType_t ux_پورټ_سېټ_مداخله_ماسک_From_ISR( فراغ )
{
UBaseType_t ux_Saved_حالت_ثبتوونکی;

    prv_Disable_مداخله();
    ux_Saved_حالت_ثبتوونکی = ul_پورټ_Get_CP0_حالت() | 0x01;

    /* This clears the IPL bits, then sets them to
    configMAX_SYSCALL_INTERRUPT_PRIORITY.  This function should not be called
    from an interrupt that has a priority above
    configMAX_SYSCALL_INTERRUPT_PRIORITY so, when used correctly, the action
    can only result in the IPL being unchanged or raised, and therefore never
    lowered. */
    v_پورټ_سېټ_CP0_حالت( ( ( ux_Saved_حالت_ثبتوونکی & ( ~پورټ_ALL_IPL_بټونه ) ) ) | ( config_MAX_SYSCALL_مداخله_لومړیتوب << پورټ_IPL_ښويدنه ) );

    أرجع ux_Saved_حالت_ثبتوونکی;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Clear_مداخله_ماسک_From_ISR( UBaseType_t ux_Saved_حالت_ثبتوونکی )
{
    v_پورټ_سېټ_CP0_حالت( ux_Saved_حالت_ثبتوونکی );
}
/*-----------------------------------------------------------*/
