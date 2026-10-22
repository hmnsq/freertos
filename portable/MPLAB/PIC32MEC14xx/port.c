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
#شامل "FreeRTOS.h"
#شامل "task.h"

/* Microchip includes. */
#شامل <xc.h>
#شامل <cp0defs.h>

#اگر !defined(__MEC__)
    #غلطی This پورٹ is designed مقصد work with XC32 on MEC14xx.  Please update your C compiler نسخہ or settings.
#اگر_ختم

#اگر( ( config_MAX_SYSCALL_مداخلت_ترجیح >= 0x7 ) || ( config_MAX_SYSCALL_مداخلت_ترجیح == 0 ) )
    #غلطی config_MAX_SYSCALL_مداخلت_ترجیح must be less than 7 and greater than 0
#اگر_ختم

/* Bits within various registers. */
#تعریف_کرو پورٹ_IE_ثنائی_ہندسہ                  ( 0x00000001 )
#تعریف_کرو پورٹ_EXL_ثنائی_ہندسہ                 ( 0x00000002 )

/* The EXL bit is set to ensure interrupts do not occur while the context of
the first task is being restored.  MEC14xx does not have DSP HW. */
#تعریف_کرو پورٹ_INITIAL_SR              ( پورٹ_IE_ثنائی_ہندسہ | پورٹ_EXL_ثنائی_ہندسہ )

/* MEC14xx RTOS Timer MMCR's. */
#تعریف_کرو پورٹ_MMCR_RTMR_PRELOAD   *((متلون uint32_t *)(0xA0007404ul))
#تعریف_کرو پورٹ_MMCR_RTMR_CONTROL   *((متلون uint32_t *)(0xA0007408ul))

/* MEC14xx JTVIC external interrupt controller is mapped to M14K closely-coupled
peripheral space. */
#تعریف_کرو پورٹ_GIRQ23_RTOS_TIMER_BITPOS    ( 4 )
#تعریف_کرو پورٹ_GIRQ23_RTOS_TIMER_نقاب      ( 1ul << ( پورٹ_GIRQ23_RTOS_TIMER_BITPOS ) )
#تعریف_کرو پورٹ_MMCR_JTVIC_GIRQ23_SRC       *((متلون uint32_t *)(0xBFFFC0F0ul))
#تعریف_کرو پورٹ_MMCR_JTVIC_GIRQ23_SETEN     *((متلون uint32_t *)(0xBFFFC0F4ul))
#تعریف_کرو پورٹ_MMCR_JTVIC_GIRQ23_PRIA      *((متلون uint32_t *)(0xBFFFC3F0ul))

/* MIPS Software Interrupts are routed through JTVIC GIRQ24 */
#تعریف_کرو پورٹ_GIRQ24_M14_K_SOFTIRQ0_BITPOS ( 1 )
#تعریف_کرو پورٹ_GIRQ24_M14_K_SOFTIRQ0_نقاب   ( 1ul << ( پورٹ_GIRQ24_M14_K_SOFTIRQ0_BITPOS ) )
#تعریف_کرو پورٹ_MMCR_JTVIC_GIRQ24_SRC       *((متلون uint32_t *)(0xBFFFC100ul))
#تعریف_کرو پورٹ_MMCR_JTVIC_GIRQ24_SETEN     *((متلون uint32_t *)(0xBFFFC104ul))
#تعریف_کرو پورٹ_MMCR_JTVIC_GIRQ24_PRIA      *((متلون uint32_t *)(0xBFFFC400ul))

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
#اگر_غیر_تعریف_شدہ config_TICK_مداخلت_سمتیہ
    #تعریف_کرو config_TICK_مداخلت_سمتیہ girq23_b4
    #تعریف_کرو config_CLEAR_TICK_TIMER_مداخلت() پورٹ_MMCR_JTVIC_GIRQ23_SRC = پورٹ_GIRQ23_RTOS_TIMER_نقاب
#ورنہ
    #اگر_غیر_تعریف_شدہ config_CLEAR_TICK_TIMER_مداخلت
        #غلطی If config_TICK_مداخلت_سمتیہ is defined اندر application رمز then config_CLEAR_TICK_TIMER_مداخلت must also be defined اندر application رمز.
    #اگر_ختم
#اگر_ختم

/* Let the user override the pre-loading of the initial RA with the address of
prvTaskExitError() in case it messes up unwinding of the stack in the debugger -
in which case configTASK_RETURN_ADDRESS can be defined as 0 (NULL). */
#اگر_تعریف_شدہ config_TASK_RETURN_پتہ
    #تعریف_کرو پورٹ_TASK_RETURN_پتہ config_TASK_RETURN_پتہ
#ورنہ
    #تعریف_کرو پورٹ_TASK_RETURN_پتہ prvTaskExitError
#اگر_ختم

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
stack checking.  A problem in the ISR stack will trigger an assert, not call the
stack overflow hook function (because the stack overflow hook is specific to a
task stack, not the ISR stack). */
#اگر( config_CHECK_FOR_ڈھیر_حد_سے_تجاوز > 2 )

    /* Don't use 0xa5 as the stack fill bytes as that is used by the kernel for
    the task stacks, and so will legitimately appear in many positions within
    the ISR stack. */
    #تعریف_کرو پورٹ_ISR_ڈھیر_FILL_BYTE 0xee

    ساکن ثابت uint8_t uc_Expected_ڈھیر_بائٹیں[] = {
                            پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE,     \
                            پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE,     \
                            پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE,     \
                            پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE,     \
                            پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE };   \

    #تعریف_کرو پورٹ_CHECK_ISR_ڈھیر() configASSERT( ( memcmp( ( خالی * ) xISRStack, ( خالی * ) uc_Expected_ڈھیر_بائٹیں, حجم( uc_Expected_ڈھیر_بائٹیں ) ) == 0 ) )
#ورنہ
    /* Define the function away. */
    #تعریف_کرو پورٹ_CHECK_ISR_ڈھیر()
#اگر_ختم /* configCHECK_FOR_STACK_OVERFLOW > 2 */


/*-----------------------------------------------------------*/

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساکن خالی prvTaskExitError( خالی );

/*-----------------------------------------------------------*/

/* Records the interrupt nesting depth.  This is initialised to one as it is
decremented to 0 when the first task starts. */
متلون UBaseType_t ux_مداخلت_Nesting = 0x01;

/* Stores the task stack pointer when a switch is made to use the system stack. */
UBaseType_t ux_Saved_Task_ڈھیر_اشارہ_گر = 0;

/* The stack used by interrupt service routines that cause a context switch. */
ڈھیر_Type_t xISRStack[ config_ISR_ڈھیر_سائز ] = { 0 };

/* The top of stack value ensures there is enough space to store 6 registers on
the callers stack, as some functions seem to want to do this. */
ثابت ڈھیر_Type_t * ثابت x_ISRStack_چوٹی = &( xISRStack[ config_ISR_ڈھیر_سائز - 7 ] );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t *px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t *px_چوٹی_کا_ڈھیر, TaskFunction_t px_رمز, خالی *pvParameters )
{
    /* Ensure byte alignment is maintained when leaving this function. */
    px_چوٹی_کا_ڈھیر--;

    *px_چوٹی_کا_ڈھیر = (ڈھیر_Type_t) 0xDEADBEEF;
    px_چوٹی_کا_ڈھیر--;

    *px_چوٹی_کا_ڈھیر = (ڈھیر_Type_t) 0x12345678;   /* Word to which the stack pointer will be left pointing after context restore. */
    px_چوٹی_کا_ڈھیر--;

    *px_چوٹی_کا_ڈھیر = (ڈھیر_Type_t) ul_پورٹ_Get_CP0_Cause();
    px_چوٹی_کا_ڈھیر--;

    *px_چوٹی_کا_ڈھیر = (ڈھیر_Type_t) پورٹ_INITIAL_SR;   /* CP0_STATUS */
    px_چوٹی_کا_ڈھیر--;

    *px_چوٹی_کا_ڈھیر = (ڈھیر_Type_t) px_رمز;       /* CP0_EPC */
    px_چوٹی_کا_ڈھیر--;

    *px_چوٹی_کا_ڈھیر = (ڈھیر_Type_t) پورٹ_TASK_RETURN_پتہ;  /* ra */
    px_چوٹی_کا_ڈھیر -= 15;

    *px_چوٹی_کا_ڈھیر = (ڈھیر_Type_t) pvParameters; /* Parameters to pass in. */
    px_چوٹی_کا_ڈھیر -= 15;

    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

ساکن __inline uint32_t prv_Disable_مداخلت( خالی )
{
uint32_t پچھلا_state;

    __asm متلون( "di %0; ehb" : "=r" ( پچھلا_state ) :: "memory" );
    واپس پچھلا_state;
}
/*-----------------------------------------------------------*/

ساکن خالی prvTaskExitError( خالی )
{
    /* A function that implements a task must not exit or attempt to return to
    its caller as there is nothing to return to.  If a task wants to exit it
    should instead call vTaskDelete( NULL ).

    Artificially force an assert() to be triggered if configASSERT() is
    defined, then stop here so application writers can catch the error. */
    configASSERT( ux_Saved_Task_ڈھیر_اشارہ_گر == 0UL );
    پورٹ_DISABLE_INTERRUPTS();
    برائے( ;; );
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
__attribute__(( weak )) خالی v_Application_تیاری_Tick_Timer_مداخلت( خالی )
{
/* MEC14xx RTOS Timer whose input clock is 32KHz. */
ثابت uint32_t ulPreload = ( 32768ul / ( config_TICK_شرح_HZ ) );

    configASSERT( ulPreload != 0UL );

    /* Configure the RTOS timer. */
    پورٹ_MMCR_RTMR_CONTROL = 0ul;
    پورٹ_MMCR_RTMR_PRELOAD = ulPreload;

    /* Configure interrupts from the RTOS timer. */
    پورٹ_MMCR_JTVIC_GIRQ23_SRC = ( پورٹ_GIRQ23_RTOS_TIMER_نقاب );
    پورٹ_MMCR_JTVIC_GIRQ23_PRIA &= ~( 0x0Ful << 16 );
    پورٹ_MMCR_JTVIC_GIRQ23_PRIA |= ( ( پورٹ_IPL_مقصد_رمز( config_KERNEL_مداخلت_ترجیح ) ) << 16 );
    پورٹ_MMCR_JTVIC_GIRQ23_SETEN = ( پورٹ_GIRQ23_RTOS_TIMER_نقاب );

    /* Enable the RTOS timer. */
    پورٹ_MMCR_RTMR_CONTROL = 0x0Fu;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler(خالی)
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( ux_مداخلت_Nesting == 1000UL );
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
خارجی خالی v_پورٹ_آغاز_پہلا_Task( خالی );
خارجی خالی *pxCurrentTCB;

    #اگر ( config_CHECK_FOR_ڈھیر_حد_سے_تجاوز > 2 )
    {
        /* Fill the ISR stack to make it easy to asses how much is being used. */
        memset( ( خالی * ) xISRStack, پورٹ_ISR_ڈھیر_FILL_BYTE, حجم( xISRStack ) );
    }
    #اگر_ختم /* configCHECK_FOR_STACK_OVERFLOW > 2 */

    /* Clear the software interrupt flag. */
    پورٹ_MMCR_JTVIC_GIRQ24_SRC = (پورٹ_GIRQ24_M14_K_SOFTIRQ0_نقاب);

    /* Set software timer priority.  Each GIRQn has one nibble containing its
ترجیح*/
    پورٹ_MMCR_JTVIC_GIRQ24_PRIA &= ~(0xF0ul);
    پورٹ_MMCR_JTVIC_GIRQ24_PRIA |= ( پورٹ_IPL_مقصد_رمز( config_KERNEL_مداخلت_ترجیح ) << 4 );

    /* Enable software interrupt. */
    پورٹ_MMCR_JTVIC_GIRQ24_SETEN = ( پورٹ_GIRQ24_M14_K_SOFTIRQ0_نقاب );

    /* Setup the timer to generate the tick.  Interrupts will have been disabled
    by the time we get here. */
    v_Application_تیاری_Tick_Timer_مداخلت();

    /* Start the highest priority task that has been created so far.  Its stack
    location is loaded into uxSavedTaskStackPointer. */
    ux_Saved_Task_ڈھیر_اشارہ_گر = *( UBaseType_t * ) pxCurrentTCB;
    v_پورٹ_آغاز_پہلا_Task();

    /* Should never get here as the tasks will now be executing!  Call the task
    exit error function to prevent compiler warnings about a static function
    not being called in the case that the application writer overrides this
    functionality by defining configTASK_RETURN_ADDRESS. */
    prvTaskExitError();

    واپس pdFALSE;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Increment_Tick( خالی )
{
UBaseType_t ux_Saved_حالت;
uint32_t ulCause;

    ux_Saved_حالت = ux_پورٹ_سیٹ_مداخلت_نقاب_From_ISR();
    {
        اگر( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            ulCause = ul_پورٹ_Get_CP0_Cause();
            ulCause |= ( 1ul << 8UL );
            v_پورٹ_سیٹ_CP0_Cause( ulCause );
        }
    }
    v_پورٹ_Clear_مداخلت_نقاب_From_ISR( ux_Saved_حالت );

    /* Look for the ISR stack getting near or past its limit. */
    پورٹ_CHECK_ISR_ڈھیر();

    /* Clear timer interrupt. */
    config_CLEAR_TICK_TIMER_مداخلت();
}
/*-----------------------------------------------------------*/

UBaseType_t ux_پورٹ_سیٹ_مداخلت_نقاب_From_ISR( خالی )
{
UBaseType_t ux_Saved_حالت_رجسٹر;

    prv_Disable_مداخلت();
    ux_Saved_حالت_رجسٹر = ul_پورٹ_Get_CP0_حالت() | 0x01;

    /* This clears the IPL bits, then sets them to
    configMAX_SYSCALL_INTERRUPT_PRIORITY.  This function should not be called
    from an interrupt that has a priority above
    configMAX_SYSCALL_INTERRUPT_PRIORITY so, when used correctly, the action
    can only result in the IPL being unchanged or raised, and therefore never
    lowered. */
    v_پورٹ_سیٹ_CP0_حالت( ( ( ux_Saved_حالت_رجسٹر & ( ~پورٹ_ALL_IPL_بٹ ) ) ) | ( config_MAX_SYSCALL_مداخلت_ترجیح << پورٹ_IPL_سرکاؤ ) );

    واپس ux_Saved_حالت_رجسٹر;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Clear_مداخلت_نقاب_From_ISR( UBaseType_t ux_Saved_حالت_رجسٹر )
{
    v_پورٹ_سیٹ_CP0_حالت( ux_Saved_حالت_رجسٹر );
}
/*-----------------------------------------------------------*/
