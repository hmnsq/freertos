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
    #غلطي This پورٽ is designed منزل work with XC32 on MEC14xx.  Please update your C compiler نسخو or settings.
#جيڪڏهن_پورو

#إذا( ( config_MAX_SYSCALL_مداخلت_ترجيح >= 0x7 ) || ( config_MAX_SYSCALL_مداخلت_ترجيح == 0 ) )
    #غلطي config_MAX_SYSCALL_مداخلت_ترجيح must be less than 7 and greater than 0
#جيڪڏهن_پورو

/* Bits within various registers. */
#وصف_ڪريو پورٽ_IE_ٻٽو_انگ                  ( 0x00000001 )
#وصف_ڪريو پورٽ_EXL_ٻٽو_انگ                 ( 0x00000002 )

/* The EXL bit is set to ensure interrupts do not occur while the context of
the first task is being restored.  MEC14xx does not have DSP HW. */
#وصف_ڪريو پورٽ_INITIAL_SR              ( پورٽ_IE_ٻٽو_انگ | پورٽ_EXL_ٻٽو_انگ )

/* MEC14xx RTOS Timer MMCR's. */
#وصف_ڪريو پورٽ_MMCR_RTMR_PRELOAD   *((متطاير uint32_t *)(0xA0007404ul))
#وصف_ڪريو پورٽ_MMCR_RTMR_CONTROL   *((متطاير uint32_t *)(0xA0007408ul))

/* MEC14xx JTVIC external interrupt controller is mapped to M14K closely-coupled
peripheral space. */
#وصف_ڪريو پورٽ_GIRQ23_RTOS_TIMER_BITPOS    ( 4 )
#وصف_ڪريو پورٽ_GIRQ23_RTOS_TIMER_نقاب      ( 1ul << ( پورٽ_GIRQ23_RTOS_TIMER_BITPOS ) )
#وصف_ڪريو پورٽ_MMCR_JTVIC_GIRQ23_SRC       *((متطاير uint32_t *)(0xBFFFC0F0ul))
#وصف_ڪريو پورٽ_MMCR_JTVIC_GIRQ23_SETEN     *((متطاير uint32_t *)(0xBFFFC0F4ul))
#وصف_ڪريو پورٽ_MMCR_JTVIC_GIRQ23_PRIA      *((متطاير uint32_t *)(0xBFFFC3F0ul))

/* MIPS Software Interrupts are routed through JTVIC GIRQ24 */
#وصف_ڪريو پورٽ_GIRQ24_M14_K_SOFTIRQ0_BITPOS ( 1 )
#وصف_ڪريو پورٽ_GIRQ24_M14_K_SOFTIRQ0_نقاب   ( 1ul << ( پورٽ_GIRQ24_M14_K_SOFTIRQ0_BITPOS ) )
#وصف_ڪريو پورٽ_MMCR_JTVIC_GIRQ24_SRC       *((متطاير uint32_t *)(0xBFFFC100ul))
#وصف_ڪريو پورٽ_MMCR_JTVIC_GIRQ24_SETEN     *((متطاير uint32_t *)(0xBFFFC104ul))
#وصف_ڪريو پورٽ_MMCR_JTVIC_GIRQ24_PRIA      *((متطاير uint32_t *)(0xBFFFC400ul))

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
#جيڪڏهن_وصف_نه_ٿيل config_TICK_مداخلت_ويڪٽر
    #وصف_ڪريو config_TICK_مداخلت_ويڪٽر girq23_b4
    #وصف_ڪريو config_CLEAR_TICK_TIMER_مداخلت() پورٽ_MMCR_JTVIC_GIRQ23_SRC = پورٽ_GIRQ23_RTOS_TIMER_نقاب
#وإلا
    #جيڪڏهن_وصف_نه_ٿيل config_CLEAR_TICK_TIMER_مداخلت
        #غلطي If config_TICK_مداخلت_ويڪٽر is defined اندريون application ڪوڊ then config_CLEAR_TICK_TIMER_مداخلت must also be defined اندريون application ڪوڊ.
    #جيڪڏهن_پورو
#جيڪڏهن_پورو

/* Let the user override the pre-loading of the initial RA with the address of
prvTaskExitError() in case it messes up unwinding of the stack in the debugger -
in which case configTASK_RETURN_ADDRESS can be defined as 0 (NULL). */
#جيڪڏهن_وصف_ٿيل config_TASK_RETURN_پتو
    #وصف_ڪريو پورٽ_TASK_RETURN_پتو config_TASK_RETURN_پتو
#وإلا
    #وصف_ڪريو پورٽ_TASK_RETURN_پتو prvTaskExitError
#جيڪڏهن_پورو

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
stack checking.  A problem in the ISR stack will trigger an assert, not call the
stack overflow hook function (because the stack overflow hook is specific to a
task stack, not the ISR stack). */
#إذا( config_CHECK_FOR_ڍير_حد_کان_مٿي > 2 )

    /* Don't use 0xa5 as the stack fill bytes as that is used by the kernel for
    the task stacks, and so will legitimately appear in many positions within
    the ISR stack. */
    #وصف_ڪريو پورٽ_ISR_ڍير_FILL_BYTE 0xee

    ساكن ثابت uint8_t uc_Expected_ڍير_بائيٽون[] = {
                            پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE,     \
                            پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE,     \
                            پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE,     \
                            پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE,     \
                            پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE };   \

    #وصف_ڪريو پورٽ_CHECK_ISR_ڍير() configASSERT( ( memcmp( ( فراغ * ) xISRStack, ( فراغ * ) uc_Expected_ڍير_بائيٽون, حجم( uc_Expected_ڍير_بائيٽون ) ) == 0 ) )
#وإلا
    /* Define the function away. */
    #وصف_ڪريو پورٽ_CHECK_ISR_ڍير()
#جيڪڏهن_پورو /* configCHECK_FOR_STACK_OVERFLOW > 2 */


/*-----------------------------------------------------------*/

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/*-----------------------------------------------------------*/

/* Records the interrupt nesting depth.  This is initialised to one as it is
decremented to 0 when the first task starts. */
متطاير UBaseType_t ux_مداخلت_Nesting = 0x01;

/* Stores the task stack pointer when a switch is made to use the system stack. */
UBaseType_t ux_Saved_Task_ڍير_اشارو = 0;

/* The stack used by interrupt service routines that cause a context switch. */
ڍير_Type_t xISRStack[ config_ISR_ڍير_سائيز ] = { 0 };

/* The top of stack value ensures there is enough space to store 6 registers on
the callers stack, as some functions seem to want to do this. */
ثابت ڍير_Type_t * ثابت x_ISRStack_چوٽي = &( xISRStack[ config_ISR_ڍير_سائيز - 7 ] );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڍير_Type_t *px_پورٽ_Initialise_ڍير( ڍير_Type_t *px_چوٽي_جو_ڍير, TaskFunction_t px_ڪوڊ, فراغ *pvParameters )
{
    /* Ensure byte alignment is maintained when leaving this function. */
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = (ڍير_Type_t) 0xDEADBEEF;
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = (ڍير_Type_t) 0x12345678;   /* Word to which the stack pointer will be left pointing after context restore. */
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = (ڍير_Type_t) ul_پورٽ_Get_CP0_Cause();
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = (ڍير_Type_t) پورٽ_INITIAL_SR;   /* CP0_STATUS */
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = (ڍير_Type_t) px_ڪوڊ;       /* CP0_EPC */
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = (ڍير_Type_t) پورٽ_TASK_RETURN_پتو;  /* ra */
    px_چوٽي_جو_ڍير -= 15;

    *px_چوٽي_جو_ڍير = (ڍير_Type_t) pvParameters; /* Parameters to pass in. */
    px_چوٽي_جو_ڍير -= 15;

    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

ساكن __inline uint32_t prv_Disable_مداخلت( فراغ )
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
    configASSERT( ux_Saved_Task_ڍير_اشارو == 0UL );
    پورٽ_DISABLE_INTERRUPTS();
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
__attribute__(( weak )) فراغ v_Application_تياري_Tick_Timer_مداخلت( فراغ )
{
/* MEC14xx RTOS Timer whose input clock is 32KHz. */
ثابت uint32_t ulPreload = ( 32768ul / ( config_TICK_شرح_HZ ) );

    configASSERT( ulPreload != 0UL );

    /* Configure the RTOS timer. */
    پورٽ_MMCR_RTMR_CONTROL = 0ul;
    پورٽ_MMCR_RTMR_PRELOAD = ulPreload;

    /* Configure interrupts from the RTOS timer. */
    پورٽ_MMCR_JTVIC_GIRQ23_SRC = ( پورٽ_GIRQ23_RTOS_TIMER_نقاب );
    پورٽ_MMCR_JTVIC_GIRQ23_PRIA &= ~( 0x0Ful << 16 );
    پورٽ_MMCR_JTVIC_GIRQ23_PRIA |= ( ( پورٽ_IPL_منزل_ڪوڊ( config_KERNEL_مداخلت_ترجيح ) ) << 16 );
    پورٽ_MMCR_JTVIC_GIRQ23_SETEN = ( پورٽ_GIRQ23_RTOS_TIMER_نقاب );

    /* Enable the RTOS timer. */
    پورٽ_MMCR_RTMR_CONTROL = 0x0Fu;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler(فراغ)
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( ux_مداخلت_Nesting == 1000UL );
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
خارجي فراغ v_پورٽ_شروعات_پهريون_Task( فراغ );
خارجي فراغ *pxCurrentTCB;

    #إذا ( config_CHECK_FOR_ڍير_حد_کان_مٿي > 2 )
    {
        /* Fill the ISR stack to make it easy to asses how much is being used. */
        memset( ( فراغ * ) xISRStack, پورٽ_ISR_ڍير_FILL_BYTE, حجم( xISRStack ) );
    }
    #جيڪڏهن_پورو /* configCHECK_FOR_STACK_OVERFLOW > 2 */

    /* Clear the software interrupt flag. */
    پورٽ_MMCR_JTVIC_GIRQ24_SRC = (پورٽ_GIRQ24_M14_K_SOFTIRQ0_نقاب);

    /* Set software timer priority.  Each GIRQn has one nibble containing its
ترجيح*/
    پورٽ_MMCR_JTVIC_GIRQ24_PRIA &= ~(0xF0ul);
    پورٽ_MMCR_JTVIC_GIRQ24_PRIA |= ( پورٽ_IPL_منزل_ڪوڊ( config_KERNEL_مداخلت_ترجيح ) << 4 );

    /* Enable software interrupt. */
    پورٽ_MMCR_JTVIC_GIRQ24_SETEN = ( پورٽ_GIRQ24_M14_K_SOFTIRQ0_نقاب );

    /* Setup the timer to generate the tick.  Interrupts will have been disabled
    by the time we get here. */
    v_Application_تياري_Tick_Timer_مداخلت();

    /* Start the highest priority task that has been created so far.  Its stack
    location is loaded into uxSavedTaskStackPointer. */
    ux_Saved_Task_ڍير_اشارو = *( UBaseType_t * ) pxCurrentTCB;
    v_پورٽ_شروعات_پهريون_Task();

    /* Should never get here as the tasks will now be executing!  Call the task
    exit error function to prevent compiler warnings about a static function
    not being called in the case that the application writer overrides this
    functionality by defining configTASK_RETURN_ADDRESS. */
    prvTaskExitError();

    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Increment_Tick( فراغ )
{
UBaseType_t ux_Saved_حالت;
uint32_t ulCause;

    ux_Saved_حالت = ux_پورٽ_سيٽ_مداخلت_نقاب_From_ISR();
    {
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            ulCause = ul_پورٽ_Get_CP0_Cause();
            ulCause |= ( 1ul << 8UL );
            v_پورٽ_سيٽ_CP0_Cause( ulCause );
        }
    }
    v_پورٽ_Clear_مداخلت_نقاب_From_ISR( ux_Saved_حالت );

    /* Look for the ISR stack getting near or past its limit. */
    پورٽ_CHECK_ISR_ڍير();

    /* Clear timer interrupt. */
    config_CLEAR_TICK_TIMER_مداخلت();
}
/*-----------------------------------------------------------*/

UBaseType_t ux_پورٽ_سيٽ_مداخلت_نقاب_From_ISR( فراغ )
{
UBaseType_t ux_Saved_حالت_رجسٽر;

    prv_Disable_مداخلت();
    ux_Saved_حالت_رجسٽر = ul_پورٽ_Get_CP0_حالت() | 0x01;

    /* This clears the IPL bits, then sets them to
    configMAX_SYSCALL_INTERRUPT_PRIORITY.  This function should not be called
    from an interrupt that has a priority above
    configMAX_SYSCALL_INTERRUPT_PRIORITY so, when used correctly, the action
    can only result in the IPL being unchanged or raised, and therefore never
    lowered. */
    v_پورٽ_سيٽ_CP0_حالت( ( ( ux_Saved_حالت_رجسٽر & ( ~پورٽ_ALL_IPL_بٽ ) ) ) | ( config_MAX_SYSCALL_مداخلت_ترجيح << پورٽ_IPL_سرڪايو ) );

    أرجع ux_Saved_حالت_رجسٽر;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Clear_مداخلت_نقاب_From_ISR( UBaseType_t ux_Saved_حالت_رجسٽر )
{
    v_پورٽ_سيٽ_CP0_حالت( ux_Saved_حالت_رجسٽر );
}
/*-----------------------------------------------------------*/
