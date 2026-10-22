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
#అన్తర్భావ <xc.h>

/* Standard headers. */
#అన్తర్భావ <string.h>

/* Scheduler include files. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

#ఒకవేళ !defined(__PIC32MZ__)
    #దోషం This పోర్టు is designed గమ్యం work with XC32 on PIC32MZ MCUs.  Please update your C compiler సంస్కరణ or settings.
#అయితే_ముగింపు

#ఒకవేళ( ( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత >= 0x7 ) || ( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత == 0 ) )
    #దోషం config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత must be less than 7 and greater than 0
#అయితే_ముగింపు

/* Hardware specifics. */
#నిర్వచించు పోర్టు_TIMER_PRESCALE  8
#నిర్వచించు పోర్టు_PRESCALE_బిట్లు   1

/* Bits within various registers. */
#నిర్వచించు పోర్టు_IE_బిట్టు                  ( 0x00000001 )
#నిర్వచించు పోర్టు_EXL_బిట్టు                 ( 0x00000002 )
#నిర్వచించు పోర్టు_MX_బిట్టు                  ( 0x01000000 ) /* Allow access to DSP instructions. */
#నిర్వచించు పోర్టు_CU1_బిట్టు                 ( 0x20000000 ) /* enable CP1 for parts with hardware. */
#నిర్వచించు పోర్టు_FR_బిట్టు                  ( 0x04000000 ) /* Enable 64 bit floating point registers. */

/* Bits within the CAUSE register. */
#నిర్వచించు పోర్టు_CORE_SW_0               ( 0x00000100 )
#నిర్వచించు పోర్టు_CORE_SW_1               ( 0x00000200 )

/* The EXL bit is set to ensure interrupts do not occur while the context of
the first task is being restored. */
#ఒకవేళ ( __mips_hard_float == 1 )
    #నిర్వచించు పోర్టు_INITIAL_SR          ( పోర్టు_IE_బిట్టు | పోర్టు_EXL_బిట్టు | పోర్టు_MX_బిట్టు | పోర్టు_FR_బిట్టు | పోర్టు_CU1_బిట్టు )
#లేకపోతే
    #నిర్వచించు పోర్టు_INITIAL_SR          ( పోర్టు_IE_బిట్టు | పోర్టు_EXL_బిట్టు | పోర్టు_MX_బిట్టు )
#అయితే_ముగింపు

/* The initial value to store into the FPU status and control register. This is
 only used on parts that support a hardware FPU. */
#నిర్వచించు పోర్టు_INITIAL_FPSCR           (0x1000000) /* High perf on denormal ops */


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
#నిర్వచితం_కాకపోతే config_TICK_అంతరాయం_సదిశ
    #నిర్వచించు config_TICK_అంతరాయం_సదిశ TIMER_1_సదిశ
    #నిర్వచించు config_CLEAR_TICK_TIMER_అంతరాయం() IFS0CLR = IFS0_T1_IF_ముసుగు
#లేకపోతే
    #నిర్వచితం_కాకపోతే config_CLEAR_TICK_TIMER_అంతరాయం
        #దోషం If config_TICK_అంతరాయం_సదిశ is defined లోపల application సంకేతం_2 then config_CLEAR_TICK_TIMER_అంతరాయం must also be defined లోపల application సంకేతం_2.
    #అయితే_ముగింపు
#అయితే_ముగింపు

/* Let the user override the pre-loading of the initial RA with the address of
prvTaskExitError() in case it messes up unwinding of the stack in the
debugger - in which case configTASK_RETURN_ADDRESS can be defined as 0 (NULL). */
#నిర్వచితమైతే config_TASK_RETURN_చిరునామా
    #నిర్వచించు పోర్టు_TASK_RETURN_చిరునామా config_TASK_RETURN_చిరునామా
#లేకపోతే
    #నిర్వచించు పోర్టు_TASK_RETURN_చిరునామా prvTaskExitError
#అయితే_ముగింపు

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
stack checking.  A problem in the ISR stack will trigger an assert, not call the
stack overflow hook function (because the stack overflow hook is specific to a
task stack, not the ISR stack). */
#ఒకవేళ( config_CHECK_FOR_దొంతర_అధికప్రవాహం > 2 )

    /* Don't use 0xa5 as the stack fill bytes as that is used by the kernel for
    the task stacks, and so will legitimately appear in many positions within
    the ISR stack. */
    #నిర్వచించు పోర్టు_ISR_దొంతర_FILL_BYTE 0xee

    స్థిర స్థిరరాశి uint8_t uc_Expected_దొంతర_బైట్లు[] = {
                                    పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE,     \
                                    పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE,     \
                                    పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE,     \
                                    పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE,     \
                                    పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE, పోర్టు_ISR_దొంతర_FILL_BYTE };   \

    #నిర్వచించు పోర్టు_CHECK_ISR_దొంతర() configASSERT( ( memcmp( ( శూన్య * ) xISRStack, ( శూన్య * ) uc_Expected_దొంతర_బైట్లు, పరిమాణం( uc_Expected_దొంతర_బైట్లు ) ) == 0 ) )
#లేకపోతే
    /* Define the function away. */
    #నిర్వచించు పోర్టు_CHECK_ISR_దొంతర()
#అయితే_ముగింపు /* configCHECK_FOR_STACK_OVERFLOW > 2 */

/*-----------------------------------------------------------*/

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
స్థిర శూన్య prvTaskExitError( శూన్య );

/*-----------------------------------------------------------*/

/* Records the interrupt nesting depth.  This is initialised to one as it is
decremented to 0 when the first task starts. */
అస్థిర UBaseType_t ux_అంతరాయం_Nesting = 0x01;

/* Stores the task stack pointer when a switch is made to use the system stack. */
UBaseType_t ux_Saved_Task_దొంతర_సూచిక = 0;

/* The stack used by interrupt service routines that cause a context switch. */
__attribute__ ((aligned(8))) దొంతర_Type_t xISRStack[ config_ISR_దొంతర_కొలత ] = { 0 };

/* The top of stack value ensures there is enough space to store 6 registers on
the callers stack, as some functions seem to want to do this.  8 byte alignment
is required to allow double word floating point stack pushes generated by the
compiler. */
స్థిరరాశి దొంతర_Type_t * స్థిరరాశి x_ISRStack_శిఖరం = &( xISRStack[ ( config_ISR_దొంతర_కొలత & ~పోర్టు_BYTE_ALIGNMENT_ముసుగు ) - 8 ] );

/* Saved as part of the task context. Set to pdFALSE if the task does not
 require an FPU context. */
#ఒకవేళ ( __mips_hard_float == 1 ) && ( configUSE_TASK_FPU_SUPPORT == 1 )
    uint32_t ulTaskHasFPUContext = 0;
#అయితే_ముగింపు

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
దొంతర_Type_t *px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t *px_శిఖరం_యొక్క_దొంతర, TaskFunction_t px_సంకేతం, శూన్య *pvParameters )
{
    /* Ensure 8 byte alignment is maintained when leaving this function. */
    px_శిఖరం_యొక్క_దొంతర--;
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = (దొంతర_Type_t) 0xDEADBEEF;
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = (దొంతర_Type_t) 0x12345678;   /* Word to which the stack pointer will be left pointing after context restore. */
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = (దొంతర_Type_t) _CP0_GET_CAUSE();
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = (దొంతర_Type_t) పోర్టు_INITIAL_SR;/* CP0_STATUS */
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = (దొంతర_Type_t) px_సంకేతం;       /* CP0_EPC */
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = (దొంతర_Type_t) 0x00000000;   /* DSPControl */
    px_శిఖరం_యొక్క_దొంతర -= 7;                          /* Includes space for AC1 - AC3. */

    *px_శిఖరం_యొక్క_దొంతర = (దొంతర_Type_t) పోర్టు_TASK_RETURN_చిరునామా;  /* ra */
    px_శిఖరం_యొక్క_దొంతర -= 15;

    *px_శిఖరం_యొక్క_దొంతర = (దొంతర_Type_t) pvParameters; /* Parameters to pass in. */
    px_శిఖరం_యొక్క_దొంతర -= 15;

    *px_శిఖరం_యొక్క_దొంతర = (దొంతర_Type_t) pdFALSE; /*by default disable FPU context save on parts with FPU */

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prvTaskExitError( శూన్య )
{
    /* A function that implements a task must not exit or attempt to return to
    its caller as there is nothing to return to.  If a task wants to exit it
    should instead call vTaskDelete( NULL ).

    Artificially force an assert() to be triggered if configASSERT() is
    defined, then stop here so application writers can catch the error. */
    configASSERT( ux_Saved_Task_దొంతర_సూచిక == 0UL );
    పోర్టు_DISABLE_INTERRUPTS();
    కొరకు( ;; );
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
__attribute__(( weak )) శూన్య v_Application_అమరిక_Tick_Timer_అంతరాయం( శూన్య )
{
స్థిరరాశి uint32_t ul_Compare_సరిపోలిక = ( (configPERIPHERAL_CLOCK_HZ / పోర్టు_TIMER_PRESCALE) / config_TICK_రేటు_HZ ) - 1UL;

    /* PR1 is 16-bit. Ensure that the configPERIPHERAL_CLOCK_HZ and
     * configTICK_RATE_HZ are defined such that ulCompareMatch value would fit
     * in 16-bits. */
    configASSERT( ( ul_Compare_సరిపోలిక & 0xFFFF0000 ) == 0 );

    T1CON = 0x0000;
    T1CONbits.TCKPS = పోర్టు_PRESCALE_బిట్లు;
    PR1 = ul_Compare_సరిపోలిక;
    IPC1bits.T1IP = config_KERNEL_అంతరాయం_ప్రాధాన్యత;

    /* Clear the interrupt as a starting condition. */
    IFS0bits.T1IF = 0;

    /* Enable the interrupt. */
    IEC0bits.T1IE = 1;

    /* Start the timer. */
    T1CONbits.TON = 1;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler(శూన్య)
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( ux_అంతరాయం_Nesting == 1000UL );
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
బాహ్య శూన్య v_పోర్టు_ప్రారంభం_మొదటి_Task( శూన్య );
బాహ్య శూన్య *pxCurrentTCB;

    #ఒకవేళ ( config_CHECK_FOR_దొంతర_అధికప్రవాహం > 2 )
    {
        /* Fill the ISR stack to make it easy to asses how much is being used. */
        memset( ( శూన్య * ) xISRStack, పోర్టు_ISR_దొంతర_FILL_BYTE, పరిమాణం( xISRStack ) );
    }
    #అయితే_ముగింపు /* configCHECK_FOR_STACK_OVERFLOW > 2 */

    /* Clear the software interrupt flag. */
    IFS0CLR = IFS0_CS0_IF_ముసుగు;

    /* Set software timer priority. */
    IPC0CLR = IPC0_CS0_IP_ముసుగు;
    IPC0_సమితి = ( config_KERNEL_అంతరాయం_ప్రాధాన్యత << _IPC0_CS0IP_POSITION );

    /* Enable software interrupt. */
    IEC0CLR = IEC0_CS0_IE_ముసుగు;
    IEC0_సమితి = 1 << _IEC0_CS0IE_POSITION;

    /* Setup the timer to generate the tick.  Interrupts will have been
    disabled by the time we get here. */
    v_Application_అమరిక_Tick_Timer_అంతరాయం();

    /* Kick off the highest priority task that has been created so far.
    Its stack location is loaded into uxSavedTaskStackPointer. */
    ux_Saved_Task_దొంతర_సూచిక = *( UBaseType_t * ) pxCurrentTCB;
    v_పోర్టు_ప్రారంభం_మొదటి_Task();

    /* Should never get here as the tasks will now be executing!  Call the task
    exit error function to prevent compiler warnings about a static function
    not being called in the case that the application writer overrides this
    functionality by defining configTASK_RETURN_ADDRESS. */
    prvTaskExitError();

    తిరిగి pdFALSE;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Increment_Tick( శూన్య )
{
UBaseType_t ux_Saved_స్థితి;

    ux_Saved_స్థితి = ux_పోర్టు_సమితి_అంతరాయం_ముసుగు_From_ISR();
    {
        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            _CP0_BIS_CAUSE( పోర్టు_CORE_SW_0 );
        }
    }
    v_పోర్టు_Clear_అంతరాయం_ముసుగు_From_ISR( ux_Saved_స్థితి );

    /* Look for the ISR stack getting near or past its limit. */
    పోర్టు_CHECK_ISR_దొంతర();

    /* Clear timer interrupt. */
    config_CLEAR_TICK_TIMER_అంతరాయం();
}
/*-----------------------------------------------------------*/

UBaseType_t ux_పోర్టు_సమితి_అంతరాయం_ముసుగు_From_ISR( శూన్య )
{
UBaseType_t ux_Saved_స్థితి_రిజిస్టరు;

    __builtin_disable_interrupts();
    ux_Saved_స్థితి_రిజిస్టరు = CP0_GET_స్థితి() | 0x01;
    /* This clears the IPL bits, then sets them to
    configMAX_SYSCALL_INTERRUPT_PRIORITY.  This function should not be called
    from an interrupt that has a priority above
    configMAX_SYSCALL_INTERRUPT_PRIORITY so, when used correctly, the action
    can only result in the IPL being unchanged or raised, and therefore never
    lowered. */
    CP0_సమితి_స్థితి( ( ( ux_Saved_స్థితి_రిజిస్టరు & ( ~పోర్టు_ALL_IPL_బిట్లు ) ) ) | ( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత << పోర్టు_IPL_జరుపు ) );

    తిరిగి ux_Saved_స్థితి_రిజిస్టరు;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Clear_అంతరాయం_ముసుగు_From_ISR( UBaseType_t ux_Saved_స్థితి_రిజిస్టరు )
{
    CP0_సమితి_స్థితి( ux_Saved_స్థితి_రిజిస్టరు );
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( __mips_hard_float == 1 ) && ( configUSE_TASK_FPU_SUPPORT == 1 )

    శూన్య v_పోర్టు_Task_ఉపయోగిస్తుంది_FPU(శూన్య)
    {
    బాహ్య శూన్య v_పోర్టు_Initialise_FPSCR( uint32_t uxFPSCRInit );

        పోర్టు_ENTER_CRITICAL();

        /* Initialise the floating point status register. */
        v_పోర్టు_Initialise_FPSCR(పోర్టు_INITIAL_FPSCR);

        /* A task is registering the fact that it needs a FPU context. Set the
        FPU flag (saved as part of the task context). */
        ulTaskHasFPUContext = pdTRUE;

        పోర్టు_EXIT_CRITICAL();
    }

#అయితే_ముగింపు /* __mips_hard_float == 1 */

/*-----------------------------------------------------------*/
