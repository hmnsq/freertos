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
#ضمن <xc.h>

/* Standard headers. */
#ضمن <string.h>

/* Scheduler include files. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

#إذا !defined(__PIC32MZ__)
    #تېروتنه This پورټ is designed منزل work with XC32 on PIC32MZ MCUs.  Please update your C compiler نسخه or settings.
#د_که_پای

#إذا( ( config_MAX_SYSCALL_مداخله_لومړیتوب >= 0x7 ) || ( config_MAX_SYSCALL_مداخله_لومړیتوب == 0 ) )
    #تېروتنه config_MAX_SYSCALL_مداخله_لومړیتوب must be less than 7 and greater than 0
#د_که_پای

/* Hardware specifics. */
#تعریف_کړه پورټ_TIMER_PRESCALE  8
#تعریف_کړه پورټ_PRESCALE_بټونه   1

/* Bits within various registers. */
#تعریف_کړه پورټ_IE_بټ                  ( 0x00000001 )
#تعریف_کړه پورټ_EXL_بټ                 ( 0x00000002 )
#تعریف_کړه پورټ_MX_بټ                  ( 0x01000000 ) /* Allow access to DSP instructions. */
#تعریف_کړه پورټ_CU1_بټ                 ( 0x20000000 ) /* enable CP1 for parts with hardware. */
#تعریف_کړه پورټ_FR_بټ                  ( 0x04000000 ) /* Enable 64 bit floating point registers. */

/* Bits within the CAUSE register. */
#تعریف_کړه پورټ_CORE_SW_0               ( 0x00000100 )
#تعریف_کړه پورټ_CORE_SW_1               ( 0x00000200 )

/* The EXL bit is set to ensure interrupts do not occur while the context of
the first task is being restored. */
#إذا ( __mips_hard_float == 1 )
    #تعریف_کړه پورټ_INITIAL_SR          ( پورټ_IE_بټ | پورټ_EXL_بټ | پورټ_MX_بټ | پورټ_FR_بټ | پورټ_CU1_بټ )
#وإلا
    #تعریف_کړه پورټ_INITIAL_SR          ( پورټ_IE_بټ | پورټ_EXL_بټ | پورټ_MX_بټ )
#د_که_پای

/* The initial value to store into the FPU status and control register. This is
 only used on parts that support a hardware FPU. */
#تعریف_کړه پورټ_INITIAL_FPSCR           (0x1000000) /* High perf on denormal ops */


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
#که_نه_تعریف_شوی config_TICK_مداخله_ویکټور
    #تعریف_کړه config_TICK_مداخله_ویکټور TIMER_1_ویکټور
    #تعریف_کړه config_CLEAR_TICK_TIMER_مداخله() IFS0CLR = IFS0_T1_IF_ماسک
#وإلا
    #که_نه_تعریف_شوی config_CLEAR_TICK_TIMER_مداخله
        #تېروتنه If config_TICK_مداخله_ویکټور is defined دننه application کوډ then config_CLEAR_TICK_TIMER_مداخله must also be defined دننه application کوډ.
    #د_که_پای
#د_که_پای

/* Let the user override the pre-loading of the initial RA with the address of
prvTaskExitError() in case it messes up unwinding of the stack in the
debugger - in which case configTASK_RETURN_ADDRESS can be defined as 0 (NULL). */
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
__attribute__ ((aligned(8))) ډېری_Type_t xISRStack[ config_ISR_ډېری_اندازه ] = { 0 };

/* The top of stack value ensures there is enough space to store 6 registers on
the callers stack, as some functions seem to want to do this.  8 byte alignment
is required to allow double word floating point stack pushes generated by the
compiler. */
ثابت ډېری_Type_t * ثابت x_ISRStack_سر = &( xISRStack[ ( config_ISR_ډېری_اندازه & ~پورټ_BYTE_ALIGNMENT_ماسک ) - 8 ] );

/* Saved as part of the task context. Set to pdFALSE if the task does not
 require an FPU context. */
#إذا ( __mips_hard_float == 1 ) && ( configUSE_TASK_FPU_SUPPORT == 1 )
    uint32_t ulTaskHasFPUContext = 0;
#د_که_پای

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ډېری_Type_t *px_پورټ_Initialise_ډېری( ډېری_Type_t *px_سر_د_ډېری, TaskFunction_t px_کوډ, فراغ *pvParameters )
{
    /* Ensure 8 byte alignment is maintained when leaving this function. */
    px_سر_د_ډېری--;
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = (ډېری_Type_t) 0xDEADBEEF;
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = (ډېری_Type_t) 0x12345678;   /* Word to which the stack pointer will be left pointing after context restore. */
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = (ډېری_Type_t) _CP0_GET_CAUSE();
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = (ډېری_Type_t) پورټ_INITIAL_SR;/* CP0_STATUS */
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = (ډېری_Type_t) px_کوډ;       /* CP0_EPC */
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = (ډېری_Type_t) 0x00000000;   /* DSPControl */
    px_سر_د_ډېری -= 7;                          /* Includes space for AC1 - AC3. */

    *px_سر_د_ډېری = (ډېری_Type_t) پورټ_TASK_RETURN_پته;  /* ra */
    px_سر_د_ډېری -= 15;

    *px_سر_د_ډېری = (ډېری_Type_t) pvParameters; /* Parameters to pass in. */
    px_سر_د_ډېری -= 15;

    *px_سر_د_ډېری = (ډېری_Type_t) pdFALSE; /*by default disable FPU context save on parts with FPU */

    أرجع px_سر_د_ډېری;
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
 * Setup a timer for a regular tick.  This function uses peripheral timer 1.
 * The function is declared weak so an application writer can use a different
 * timer by redefining this implementation.  If a different timer is used then
 * configTICK_INTERRUPT_VECTOR must also be defined in FreeRTOSConfig.h to
 * ensure the RTOS provided tick interrupt handler is installed on the correct
 * vector number.  When Timer 1 is used the vector number is defined as
 * _TIMER_1_VECTOR.
 */
__attribute__(( weak )) فراغ v_Application_تیاری_Tick_Timer_مداخله( فراغ )
{
ثابت uint32_t ul_Compare_سمون = ( (configPERIPHERAL_CLOCK_HZ / پورټ_TIMER_PRESCALE) / config_TICK_شرح_HZ ) - 1UL;

    /* PR1 is 16-bit. Ensure that the configPERIPHERAL_CLOCK_HZ and
     * configTICK_RATE_HZ are defined such that ulCompareMatch value would fit
     * in 16-bits. */
    configASSERT( ( ul_Compare_سمون & 0xFFFF0000 ) == 0 );

    T1CON = 0x0000;
    T1CONbits.TCKPS = پورټ_PRESCALE_بټونه;
    PR1 = ul_Compare_سمون;
    IPC1bits.T1IP = config_KERNEL_مداخله_لومړیتوب;

    /* Clear the interrupt as a starting condition. */
    IFS0bits.T1IF = 0;

    /* Enable the interrupt. */
    IEC0bits.T1IE = 1;

    /* Start the timer. */
    T1CONbits.TON = 1;
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
    IFS0CLR = IFS0_CS0_IF_ماسک;

    /* Set software timer priority. */
    IPC0CLR = IPC0_CS0_IP_ماسک;
    IPC0_سېټ = ( config_KERNEL_مداخله_لومړیتوب << _IPC0_CS0IP_POSITION );

    /* Enable software interrupt. */
    IEC0CLR = IEC0_CS0_IE_ماسک;
    IEC0_سېټ = 1 << _IEC0_CS0IE_POSITION;

    /* Setup the timer to generate the tick.  Interrupts will have been
    disabled by the time we get here. */
    v_Application_تیاری_Tick_Timer_مداخله();

    /* Kick off the highest priority task that has been created so far.
    Its stack location is loaded into uxSavedTaskStackPointer. */
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

    ux_Saved_حالت = ux_پورټ_سېټ_مداخله_ماسک_From_ISR();
    {
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            _CP0_BIS_CAUSE( پورټ_CORE_SW_0 );
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

    __builtin_disable_interrupts();
    ux_Saved_حالت_ثبتوونکی = CP0_GET_حالت() | 0x01;
    /* This clears the IPL bits, then sets them to
    configMAX_SYSCALL_INTERRUPT_PRIORITY.  This function should not be called
    from an interrupt that has a priority above
    configMAX_SYSCALL_INTERRUPT_PRIORITY so, when used correctly, the action
    can only result in the IPL being unchanged or raised, and therefore never
    lowered. */
    CP0_سېټ_حالت( ( ( ux_Saved_حالت_ثبتوونکی & ( ~پورټ_ALL_IPL_بټونه ) ) ) | ( config_MAX_SYSCALL_مداخله_لومړیتوب << پورټ_IPL_ښويدنه ) );

    أرجع ux_Saved_حالت_ثبتوونکی;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Clear_مداخله_ماسک_From_ISR( UBaseType_t ux_Saved_حالت_ثبتوونکی )
{
    CP0_سېټ_حالت( ux_Saved_حالت_ثبتوونکی );
}
/*-----------------------------------------------------------*/

#إذا ( __mips_hard_float == 1 ) && ( configUSE_TASK_FPU_SUPPORT == 1 )

    فراغ v_پورټ_Task_کاروي_FPU(فراغ)
    {
    خارجي فراغ v_پورټ_Initialise_FPSCR( uint32_t uxFPSCRInit );

        پورټ_ENTER_CRITICAL();

        /* Initialise the floating point status register. */
        v_پورټ_Initialise_FPSCR(پورټ_INITIAL_FPSCR);

        /* A task is registering the fact that it needs a FPU context. Set the
        FPU flag (saved as part of the task context). */
        ulTaskHasFPUContext = pdTRUE;

        پورټ_EXIT_CRITICAL();
    }

#د_که_پای /* __mips_hard_float == 1 */

/*-----------------------------------------------------------*/
