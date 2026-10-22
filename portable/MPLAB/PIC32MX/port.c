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

#جيڪڏهن_وصف_نه_ٿيل __XC
    #غلطي This پورٽ is designed منزل work with XC32.  Please update your C compiler نسخو.
#جيڪڏهن_پورو

/* Scheduler include files. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Hardware specifics. */
#وصف_ڪريو پورٽ_TIMER_PRESCALE  8
#وصف_ڪريو پورٽ_PRESCALE_بٽ   1

/* Bits within various registers. */
#وصف_ڪريو پورٽ_IE_ٻٽو_انگ                      ( 0x00000001 )
#وصف_ڪريو پورٽ_EXL_ٻٽو_انگ                     ( 0x00000002 )

/* Bits within the CAUSE register. */
#وصف_ڪريو پورٽ_CORE_SW_0                   ( 0x00000100 )
#وصف_ڪريو پورٽ_CORE_SW_1                   ( 0x00000200 )

/* The EXL bit is set to ensure interrupts do not occur while the context of
the first task is being restored. */
#وصف_ڪريو پورٽ_INITIAL_SR                  ( پورٽ_IE_ٻٽو_انگ | پورٽ_EXL_ٻٽو_انگ )

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
#جيڪڏهن_وصف_نه_ٿيل config_TICK_مداخلت_ويڪٽر
    #وصف_ڪريو config_TICK_مداخلت_ويڪٽر TIMER_1_ويڪٽر
    #وصف_ڪريو config_CLEAR_TICK_TIMER_مداخلت() IFS0CLR = IFS0_T1_IF_نقاب
#وإلا
    #جيڪڏهن_وصف_نه_ٿيل config_CLEAR_TICK_TIMER_مداخلت
        #غلطي If config_TICK_مداخلت_ويڪٽر is defined اندريون application ڪوڊ then config_CLEAR_TICK_TIMER_مداخلت must also be defined اندريون application ڪوڊ.
    #جيڪڏهن_پورو
#جيڪڏهن_پورو

/* Let the user override the pre-loading of the initial RA with the address of
prvTaskExitError() in case it messes up unwinding of the stack in the
debugger - in which case configTASK_RETURN_ADDRESS can be defined as 0 (NULL). */
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
 * Place the prototype here to ensure the interrupt vector is correctly installed.
 * Note that because the interrupt is written in assembly, the IPL setting in the
 * following line of code has no effect.  The interrupt priority is set by the
 * call to ConfigIntTimer1() in vApplicationSetupTickTimerInterrupt().
 */
خارجي فراغ __attribute__( (مداخلت(IPL1AUTO), ويڪٽر( config_TICK_مداخلت_ويڪٽر ))) v_پورٽ_Tick_مداخلت_Handler( فراغ );

/*
 * The software interrupt handler that performs the yield.  Note that, because
 * the interrupt is written in assembly, the IPL setting in the following line of
 * code has no effect.  The interrupt priority is set by the call to
 * mConfigIntCoreSW0() in xPortStartScheduler().
 */
فراغ __attribute__( (مداخلت(IPL1AUTO), ويڪٽر(CORE_SOFTWARE_0_ويڪٽر))) v_پورٽ_Yield_ISR( فراغ );

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
__attribute__ ((aligned(8))) ڍير_Type_t xISRStack[ config_ISR_ڍير_سائيز ] = { 0 };

/* The top of stack value ensures there is enough space to store 6 registers on
the callers stack, as some functions seem to want to do this. */
ثابت ڍير_Type_t * ثابت x_ISRStack_چوٽي = &( xISRStack[ ( config_ISR_ڍير_سائيز & ~پورٽ_BYTE_ALIGNMENT_نقاب ) - 8 ] );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڍير_Type_t *px_پورٽ_Initialise_ڍير( ڍير_Type_t *px_چوٽي_جو_ڍير, TaskFunction_t px_ڪوڊ, فراغ *pvParameters )
{
    /* Ensure 8 byte alignment is maintained when the context is popped from
     * stack. The size of the context is 33 words (132 bytes). */
    px_چوٽي_جو_ڍير--;
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = (ڍير_Type_t) 0xDEADBEEF;
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = (ڍير_Type_t) 0x12345678;   /* Word to which the stack pointer will be left pointing after context restore. */
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = (ڍير_Type_t) _CP0_GET_CAUSE();
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = (ڍير_Type_t) پورٽ_INITIAL_SR;/* CP0_STATUS */
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
 * Setup a timer for a regular tick.  This function uses peripheral timer 1.
 * The function is declared weak so an application writer can use a different
 * timer by redefining this implementation.  If a different timer is used then
 * configTICK_INTERRUPT_VECTOR must also be defined in FreeRTOSConfig.h to
 * ensure the RTOS provided tick interrupt handler is installed on the correct
 * vector number.  When Timer 1 is used the vector number is defined as
 * _TIMER_1_VECTOR.
 */
__attribute__(( weak )) فراغ v_Application_تياري_Tick_Timer_مداخلت( فراغ )
{
ثابت uint32_t ul_Compare_ميلاپ = ( (configPERIPHERAL_CLOCK_HZ / پورٽ_TIMER_PRESCALE) / config_TICK_شرح_HZ ) - 1;

    T1CON = 0x0000;
    T1CONbits.TCKPS = پورٽ_PRESCALE_بٽ;
    PR1 = ul_Compare_ميلاپ;
    IPC1bits.T1IP = config_KERNEL_مداخلت_ترجيح;

    /* Clear the interrupt as a starting condition. */
    IFS0bits.T1IF = 0;

    /* Enable the interrupt. */
    IEC0bits.T1IE = 1;

    /* Start the timer. */
    T1CONbits.TON = 1;
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
    IFS0CLR = IFS0_CS0_IF_نقاب;

    /* Set software timer priority. */
    IPC0CLR = IPC0_CS0_IP_نقاب;
    IPC0_سيٽ = ( config_KERNEL_مداخلت_ترجيح << _IPC0_CS0IP_POSITION );

    /* Enable software interrupt. */
    IEC0CLR = IEC0_CS0_IE_نقاب;
    IEC0_سيٽ = 1 << _IEC0_CS0IE_POSITION;

    /* Setup the timer to generate the tick.  Interrupts will have been
    disabled by the time we get here. */
    v_Application_تياري_Tick_Timer_مداخلت();

    /* Kick off the highest priority task that has been created so far.
    Its stack location is loaded into uxSavedTaskStackPointer. */
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

    ux_Saved_حالت = ux_پورٽ_سيٽ_مداخلت_نقاب_From_ISR();
    {
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            _CP0_BIS_CAUSE( پورٽ_CORE_SW_0 );
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

    __builtin_disable_interrupts();
    ux_Saved_حالت_رجسٽر = CP0_GET_حالت() | 0x01;
    /* This clears the IPL bits, then sets them to
    configMAX_SYSCALL_INTERRUPT_PRIORITY.  This function should not be called
    from an interrupt that has a priority above
    configMAX_SYSCALL_INTERRUPT_PRIORITY so, when used correctly, the action
    can only result in the IPL being unchanged or raised, and therefore never
    lowered. */
    CP0_سيٽ_حالت( ( ( ux_Saved_حالت_رجسٽر & ( ~پورٽ_ALL_IPL_بٽ ) ) ) | ( config_MAX_SYSCALL_مداخلت_ترجيح << پورٽ_IPL_سرڪايو ) );

    أرجع ux_Saved_حالت_رجسٽر;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Clear_مداخلت_نقاب_From_ISR( UBaseType_t ux_Saved_حالت_رجسٽر )
{
    CP0_سيٽ_حالت( ux_Saved_حالت_رجسٽر );
}
/*-----------------------------------------------------------*/
