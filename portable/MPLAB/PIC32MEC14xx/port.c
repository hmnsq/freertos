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
    #خطا This پورت is designed مقصد work with XC32 on MEC14xx.  Please update your C compiler نسخه or settings.
#پایان_اگر

#إذا( ( config_MAX_SYSCALL_وقفه_اولویت >= 0x7 ) || ( config_MAX_SYSCALL_وقفه_اولویت == 0 ) )
    #خطا config_MAX_SYSCALL_وقفه_اولویت must be less than 7 and greater than 0
#پایان_اگر

/* Bits within various registers. */
#تعریف_کن پورت_IE_بیت                  ( 0x00000001 )
#تعریف_کن پورت_EXL_بیت                 ( 0x00000002 )

/* The EXL bit is set to ensure interrupts do not occur while the context of
the first task is being restored.  MEC14xx does not have DSP HW. */
#تعریف_کن پورت_INITIAL_SR              ( پورت_IE_بیت | پورت_EXL_بیت )

/* MEC14xx RTOS Timer MMCR's. */
#تعریف_کن پورت_MMCR_RTMR_PRELOAD   *((متطاير uint32_t *)(0xA0007404ul))
#تعریف_کن پورت_MMCR_RTMR_CONTROL   *((متطاير uint32_t *)(0xA0007408ul))

/* MEC14xx JTVIC external interrupt controller is mapped to M14K closely-coupled
peripheral space. */
#تعریف_کن پورت_GIRQ23_RTOS_TIMER_BITPOS    ( 4 )
#تعریف_کن پورت_GIRQ23_RTOS_TIMER_ماسک      ( 1ul << ( پورت_GIRQ23_RTOS_TIMER_BITPOS ) )
#تعریف_کن پورت_MMCR_JTVIC_GIRQ23_SRC       *((متطاير uint32_t *)(0xBFFFC0F0ul))
#تعریف_کن پورت_MMCR_JTVIC_GIRQ23_SETEN     *((متطاير uint32_t *)(0xBFFFC0F4ul))
#تعریف_کن پورت_MMCR_JTVIC_GIRQ23_PRIA      *((متطاير uint32_t *)(0xBFFFC3F0ul))

/* MIPS Software Interrupts are routed through JTVIC GIRQ24 */
#تعریف_کن پورت_GIRQ24_M14_K_SOFTIRQ0_BITPOS ( 1 )
#تعریف_کن پورت_GIRQ24_M14_K_SOFTIRQ0_ماسک   ( 1ul << ( پورت_GIRQ24_M14_K_SOFTIRQ0_BITPOS ) )
#تعریف_کن پورت_MMCR_JTVIC_GIRQ24_SRC       *((متطاير uint32_t *)(0xBFFFC100ul))
#تعریف_کن پورت_MMCR_JTVIC_GIRQ24_SETEN     *((متطاير uint32_t *)(0xBFFFC104ul))
#تعریف_کن پورت_MMCR_JTVIC_GIRQ24_PRIA      *((متطاير uint32_t *)(0xBFFFC400ul))

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
#اگر_تعریف_نشده config_TICK_وقفه_وکتور
    #تعریف_کن config_TICK_وقفه_وکتور girq23_b4
    #تعریف_کن config_CLEAR_TICK_TIMER_وقفه() پورت_MMCR_JTVIC_GIRQ23_SRC = پورت_GIRQ23_RTOS_TIMER_ماسک
#وإلا
    #اگر_تعریف_نشده config_CLEAR_TICK_TIMER_وقفه
        #خطا If config_TICK_وقفه_وکتور is defined درون application کد then config_CLEAR_TICK_TIMER_وقفه must also be defined درون application کد.
    #پایان_اگر
#پایان_اگر

/* Let the user override the pre-loading of the initial RA with the address of
prvTaskExitError() in case it messes up unwinding of the stack in the debugger -
in which case configTASK_RETURN_ADDRESS can be defined as 0 (NULL). */
#اگر_تعریف_شده config_TASK_RETURN_آدرس
    #تعریف_کن پورت_TASK_RETURN_آدرس config_TASK_RETURN_آدرس
#وإلا
    #تعریف_کن پورت_TASK_RETURN_آدرس prvTaskExitError
#پایان_اگر

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
stack checking.  A problem in the ISR stack will trigger an assert, not call the
stack overflow hook function (because the stack overflow hook is specific to a
task stack, not the ISR stack). */
#إذا( config_CHECK_FOR_پشته_سرریز > 2 )

    /* Don't use 0xa5 as the stack fill bytes as that is used by the kernel for
    the task stacks, and so will legitimately appear in many positions within
    the ISR stack. */
    #تعریف_کن پورت_ISR_پشته_FILL_BYTE 0xee

    ساكن ثابت uint8_t uc_Expected_پشته_بایتها[] = {
                            پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE,     \
                            پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE,     \
                            پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE,     \
                            پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE,     \
                            پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE, پورت_ISR_پشته_FILL_BYTE };   \

    #تعریف_کن پورت_CHECK_ISR_پشته() configASSERT( ( memcmp( ( فراغ * ) xISRStack, ( فراغ * ) uc_Expected_پشته_بایتها, حجم( uc_Expected_پشته_بایتها ) ) == 0 ) )
#وإلا
    /* Define the function away. */
    #تعریف_کن پورت_CHECK_ISR_پشته()
#پایان_اگر /* configCHECK_FOR_STACK_OVERFLOW > 2 */


/*-----------------------------------------------------------*/

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/*-----------------------------------------------------------*/

/* Records the interrupt nesting depth.  This is initialised to one as it is
decremented to 0 when the first task starts. */
متطاير UBaseType_t ux_وقفه_Nesting = 0x01;

/* Stores the task stack pointer when a switch is made to use the system stack. */
UBaseType_t ux_Saved_Task_پشته_اشاره_گر = 0;

/* The stack used by interrupt service routines that cause a context switch. */
پشته_Type_t xISRStack[ config_ISR_پشته_اندازه ] = { 0 };

/* The top of stack value ensures there is enough space to store 6 registers on
the callers stack, as some functions seem to want to do this. */
ثابت پشته_Type_t * ثابت x_ISRStack_بالاترین = &( xISRStack[ config_ISR_پشته_اندازه - 7 ] );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
پشته_Type_t *px_پورت_Initialise_پشته( پشته_Type_t *px_بالاترین_از_پشته, TaskFunction_t px_کد, فراغ *pvParameters )
{
    /* Ensure byte alignment is maintained when leaving this function. */
    px_بالاترین_از_پشته--;

    *px_بالاترین_از_پشته = (پشته_Type_t) 0xDEADBEEF;
    px_بالاترین_از_پشته--;

    *px_بالاترین_از_پشته = (پشته_Type_t) 0x12345678;   /* Word to which the stack pointer will be left pointing after context restore. */
    px_بالاترین_از_پشته--;

    *px_بالاترین_از_پشته = (پشته_Type_t) ul_پورت_Get_CP0_Cause();
    px_بالاترین_از_پشته--;

    *px_بالاترین_از_پشته = (پشته_Type_t) پورت_INITIAL_SR;   /* CP0_STATUS */
    px_بالاترین_از_پشته--;

    *px_بالاترین_از_پشته = (پشته_Type_t) px_کد;       /* CP0_EPC */
    px_بالاترین_از_پشته--;

    *px_بالاترین_از_پشته = (پشته_Type_t) پورت_TASK_RETURN_آدرس;  /* ra */
    px_بالاترین_از_پشته -= 15;

    *px_بالاترین_از_پشته = (پشته_Type_t) pvParameters; /* Parameters to pass in. */
    px_بالاترین_از_پشته -= 15;

    أرجع px_بالاترین_از_پشته;
}
/*-----------------------------------------------------------*/

ساكن __inline uint32_t prv_Disable_وقفه( فراغ )
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
    configASSERT( ux_Saved_Task_پشته_اشاره_گر == 0UL );
    پورت_DISABLE_INTERRUPTS();
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
__attribute__(( weak )) فراغ v_Application_راهاندازی_Tick_Timer_وقفه( فراغ )
{
/* MEC14xx RTOS Timer whose input clock is 32KHz. */
ثابت uint32_t ulPreload = ( 32768ul / ( config_TICK_نرخ_HZ ) );

    configASSERT( ulPreload != 0UL );

    /* Configure the RTOS timer. */
    پورت_MMCR_RTMR_CONTROL = 0ul;
    پورت_MMCR_RTMR_PRELOAD = ulPreload;

    /* Configure interrupts from the RTOS timer. */
    پورت_MMCR_JTVIC_GIRQ23_SRC = ( پورت_GIRQ23_RTOS_TIMER_ماسک );
    پورت_MMCR_JTVIC_GIRQ23_PRIA &= ~( 0x0Ful << 16 );
    پورت_MMCR_JTVIC_GIRQ23_PRIA |= ( ( پورت_IPL_مقصد_کد( config_KERNEL_وقفه_اولویت ) ) << 16 );
    پورت_MMCR_JTVIC_GIRQ23_SETEN = ( پورت_GIRQ23_RTOS_TIMER_ماسک );

    /* Enable the RTOS timer. */
    پورت_MMCR_RTMR_CONTROL = 0x0Fu;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_انتها_Scheduler(فراغ)
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( ux_وقفه_Nesting == 1000UL );
}
/*-----------------------------------------------------------*/

پایه_Type_t x_پورت_شروع_Scheduler( فراغ )
{
خارجي فراغ v_پورت_شروع_اولی_Task( فراغ );
خارجي فراغ *pxCurrentTCB;

    #إذا ( config_CHECK_FOR_پشته_سرریز > 2 )
    {
        /* Fill the ISR stack to make it easy to asses how much is being used. */
        memset( ( فراغ * ) xISRStack, پورت_ISR_پشته_FILL_BYTE, حجم( xISRStack ) );
    }
    #پایان_اگر /* configCHECK_FOR_STACK_OVERFLOW > 2 */

    /* Clear the software interrupt flag. */
    پورت_MMCR_JTVIC_GIRQ24_SRC = (پورت_GIRQ24_M14_K_SOFTIRQ0_ماسک);

    /* Set software timer priority.  Each GIRQn has one nibble containing its
اولویت*/
    پورت_MMCR_JTVIC_GIRQ24_PRIA &= ~(0xF0ul);
    پورت_MMCR_JTVIC_GIRQ24_PRIA |= ( پورت_IPL_مقصد_کد( config_KERNEL_وقفه_اولویت ) << 4 );

    /* Enable software interrupt. */
    پورت_MMCR_JTVIC_GIRQ24_SETEN = ( پورت_GIRQ24_M14_K_SOFTIRQ0_ماسک );

    /* Setup the timer to generate the tick.  Interrupts will have been disabled
    by the time we get here. */
    v_Application_راهاندازی_Tick_Timer_وقفه();

    /* Start the highest priority task that has been created so far.  Its stack
    location is loaded into uxSavedTaskStackPointer. */
    ux_Saved_Task_پشته_اشاره_گر = *( UBaseType_t * ) pxCurrentTCB;
    v_پورت_شروع_اولی_Task();

    /* Should never get here as the tasks will now be executing!  Call the task
    exit error function to prevent compiler warnings about a static function
    not being called in the case that the application writer overrides this
    functionality by defining configTASK_RETURN_ADDRESS. */
    prvTaskExitError();

    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Increment_Tick( فراغ )
{
UBaseType_t ux_Saved_وضعیت;
uint32_t ulCause;

    ux_Saved_وضعیت = ux_پورت_مجموعه_وقفه_ماسک_From_ISR();
    {
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            ulCause = ul_پورت_Get_CP0_Cause();
            ulCause |= ( 1ul << 8UL );
            v_پورت_مجموعه_CP0_Cause( ulCause );
        }
    }
    v_پورت_Clear_وقفه_ماسک_From_ISR( ux_Saved_وضعیت );

    /* Look for the ISR stack getting near or past its limit. */
    پورت_CHECK_ISR_پشته();

    /* Clear timer interrupt. */
    config_CLEAR_TICK_TIMER_وقفه();
}
/*-----------------------------------------------------------*/

UBaseType_t ux_پورت_مجموعه_وقفه_ماسک_From_ISR( فراغ )
{
UBaseType_t ux_Saved_وضعیت_ثبات;

    prv_Disable_وقفه();
    ux_Saved_وضعیت_ثبات = ul_پورت_Get_CP0_وضعیت() | 0x01;

    /* This clears the IPL bits, then sets them to
    configMAX_SYSCALL_INTERRUPT_PRIORITY.  This function should not be called
    from an interrupt that has a priority above
    configMAX_SYSCALL_INTERRUPT_PRIORITY so, when used correctly, the action
    can only result in the IPL being unchanged or raised, and therefore never
    lowered. */
    v_پورت_مجموعه_CP0_وضعیت( ( ( ux_Saved_وضعیت_ثبات & ( ~پورت_ALL_IPL_بیتها ) ) ) | ( config_MAX_SYSCALL_وقفه_اولویت << پورت_IPL_لغزش ) );

    أرجع ux_Saved_وضعیت_ثبات;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Clear_وقفه_ماسک_From_ISR( UBaseType_t ux_Saved_وضعیت_ثبات )
{
    v_پورت_مجموعه_CP0_وضعیت( ux_Saved_وضعیت_ثبات );
}
/*-----------------------------------------------------------*/
