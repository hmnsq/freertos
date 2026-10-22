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
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* Microchip includes. */
#అన్తర్భావ <xc.h>
#అన్తర్భావ <cp0defs.h>

#ఒకవేళ !defined(__MEC__)
    #దోషం This పోర్టు is designed గమ్యం work with XC32 on MEC14xx.  Please update your C compiler సంస్కరణ or settings.
#అయితే_ముగింపు

#ఒకవేళ( ( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత >= 0x7 ) || ( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత == 0 ) )
    #దోషం config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత must be less than 7 and greater than 0
#అయితే_ముగింపు

/* Bits within various registers. */
#నిర్వచించు పోర్టు_IE_బిట్టు                  ( 0x00000001 )
#నిర్వచించు పోర్టు_EXL_బిట్టు                 ( 0x00000002 )

/* The EXL bit is set to ensure interrupts do not occur while the context of
the first task is being restored.  MEC14xx does not have DSP HW. */
#నిర్వచించు పోర్టు_INITIAL_SR              ( పోర్టు_IE_బిట్టు | పోర్టు_EXL_బిట్టు )

/* MEC14xx RTOS Timer MMCR's. */
#నిర్వచించు పోర్టు_MMCR_RTMR_PRELOAD   *((అస్థిర uint32_t *)(0xA0007404ul))
#నిర్వచించు పోర్టు_MMCR_RTMR_CONTROL   *((అస్థిర uint32_t *)(0xA0007408ul))

/* MEC14xx JTVIC external interrupt controller is mapped to M14K closely-coupled
peripheral space. */
#నిర్వచించు పోర్టు_GIRQ23_RTOS_TIMER_BITPOS    ( 4 )
#నిర్వచించు పోర్టు_GIRQ23_RTOS_TIMER_ముసుగు      ( 1ul << ( పోర్టు_GIRQ23_RTOS_TIMER_BITPOS ) )
#నిర్వచించు పోర్టు_MMCR_JTVIC_GIRQ23_SRC       *((అస్థిర uint32_t *)(0xBFFFC0F0ul))
#నిర్వచించు పోర్టు_MMCR_JTVIC_GIRQ23_SETEN     *((అస్థిర uint32_t *)(0xBFFFC0F4ul))
#నిర్వచించు పోర్టు_MMCR_JTVIC_GIRQ23_PRIA      *((అస్థిర uint32_t *)(0xBFFFC3F0ul))

/* MIPS Software Interrupts are routed through JTVIC GIRQ24 */
#నిర్వచించు పోర్టు_GIRQ24_M14_K_SOFTIRQ0_BITPOS ( 1 )
#నిర్వచించు పోర్టు_GIRQ24_M14_K_SOFTIRQ0_ముసుగు   ( 1ul << ( పోర్టు_GIRQ24_M14_K_SOFTIRQ0_BITPOS ) )
#నిర్వచించు పోర్టు_MMCR_JTVIC_GIRQ24_SRC       *((అస్థిర uint32_t *)(0xBFFFC100ul))
#నిర్వచించు పోర్టు_MMCR_JTVIC_GIRQ24_SETEN     *((అస్థిర uint32_t *)(0xBFFFC104ul))
#నిర్వచించు పోర్టు_MMCR_JTVIC_GIRQ24_PRIA      *((అస్థిర uint32_t *)(0xBFFFC400ul))

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
#నిర్వచితం_కాకపోతే config_TICK_అంతరాయం_సదిశ
    #నిర్వచించు config_TICK_అంతరాయం_సదిశ girq23_b4
    #నిర్వచించు config_CLEAR_TICK_TIMER_అంతరాయం() పోర్టు_MMCR_JTVIC_GIRQ23_SRC = పోర్టు_GIRQ23_RTOS_TIMER_ముసుగు
#లేకపోతే
    #నిర్వచితం_కాకపోతే config_CLEAR_TICK_TIMER_అంతరాయం
        #దోషం If config_TICK_అంతరాయం_సదిశ is defined లోపల application సంకేతం_2 then config_CLEAR_TICK_TIMER_అంతరాయం must also be defined లోపల application సంకేతం_2.
    #అయితే_ముగింపు
#అయితే_ముగింపు

/* Let the user override the pre-loading of the initial RA with the address of
prvTaskExitError() in case it messes up unwinding of the stack in the debugger -
in which case configTASK_RETURN_ADDRESS can be defined as 0 (NULL). */
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
దొంతర_Type_t xISRStack[ config_ISR_దొంతర_కొలత ] = { 0 };

/* The top of stack value ensures there is enough space to store 6 registers on
the callers stack, as some functions seem to want to do this. */
స్థిరరాశి దొంతర_Type_t * స్థిరరాశి x_ISRStack_శిఖరం = &( xISRStack[ config_ISR_దొంతర_కొలత - 7 ] );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
దొంతర_Type_t *px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t *px_శిఖరం_యొక్క_దొంతర, TaskFunction_t px_సంకేతం, శూన్య *pvParameters )
{
    /* Ensure byte alignment is maintained when leaving this function. */
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = (దొంతర_Type_t) 0xDEADBEEF;
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = (దొంతర_Type_t) 0x12345678;   /* Word to which the stack pointer will be left pointing after context restore. */
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = (దొంతర_Type_t) ul_పోర్టు_Get_CP0_Cause();
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = (దొంతర_Type_t) పోర్టు_INITIAL_SR;   /* CP0_STATUS */
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = (దొంతర_Type_t) px_సంకేతం;       /* CP0_EPC */
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = (దొంతర_Type_t) పోర్టు_TASK_RETURN_చిరునామా;  /* ra */
    px_శిఖరం_యొక్క_దొంతర -= 15;

    *px_శిఖరం_యొక్క_దొంతర = (దొంతర_Type_t) pvParameters; /* Parameters to pass in. */
    px_శిఖరం_యొక్క_దొంతర -= 15;

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

స్థిర __inline uint32_t prv_Disable_అంతరాయం( శూన్య )
{
uint32_t prev_state;

    __asm అస్థిర( "di %0; ehb" : "=r" ( prev_state ) :: "memory" );
    తిరిగి prev_state;
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
 * Setup a timer for a regular tick.  This function uses the RTOS timer.
 * The function is declared weak so an application writer can use a different
 * timer by redefining this implementation.  If a different timer is used then
 * configTICK_INTERRUPT_VECTOR must also be defined in FreeRTOSConfig.h to
 * ensure the RTOS provided tick interrupt handler is installed on the correct
 * vector number.
 */
__attribute__(( weak )) శూన్య v_Application_అమరిక_Tick_Timer_అంతరాయం( శూన్య )
{
/* MEC14xx RTOS Timer whose input clock is 32KHz. */
స్థిరరాశి uint32_t ulPreload = ( 32768ul / ( config_TICK_రేటు_HZ ) );

    configASSERT( ulPreload != 0UL );

    /* Configure the RTOS timer. */
    పోర్టు_MMCR_RTMR_CONTROL = 0ul;
    పోర్టు_MMCR_RTMR_PRELOAD = ulPreload;

    /* Configure interrupts from the RTOS timer. */
    పోర్టు_MMCR_JTVIC_GIRQ23_SRC = ( పోర్టు_GIRQ23_RTOS_TIMER_ముసుగు );
    పోర్టు_MMCR_JTVIC_GIRQ23_PRIA &= ~( 0x0Ful << 16 );
    పోర్టు_MMCR_JTVIC_GIRQ23_PRIA |= ( ( పోర్టు_IPL_గమ్యం_సంకేతం( config_KERNEL_అంతరాయం_ప్రాధాన్యత ) ) << 16 );
    పోర్టు_MMCR_JTVIC_GIRQ23_SETEN = ( పోర్టు_GIRQ23_RTOS_TIMER_ముసుగు );

    /* Enable the RTOS timer. */
    పోర్టు_MMCR_RTMR_CONTROL = 0x0Fu;
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
    పోర్టు_MMCR_JTVIC_GIRQ24_SRC = (పోర్టు_GIRQ24_M14_K_SOFTIRQ0_ముసుగు);

    /* Set software timer priority.  Each GIRQn has one nibble containing its
ప్రాధాన్యత*/
    పోర్టు_MMCR_JTVIC_GIRQ24_PRIA &= ~(0xF0ul);
    పోర్టు_MMCR_JTVIC_GIRQ24_PRIA |= ( పోర్టు_IPL_గమ్యం_సంకేతం( config_KERNEL_అంతరాయం_ప్రాధాన్యత ) << 4 );

    /* Enable software interrupt. */
    పోర్టు_MMCR_JTVIC_GIRQ24_SETEN = ( పోర్టు_GIRQ24_M14_K_SOFTIRQ0_ముసుగు );

    /* Setup the timer to generate the tick.  Interrupts will have been disabled
    by the time we get here. */
    v_Application_అమరిక_Tick_Timer_అంతరాయం();

    /* Start the highest priority task that has been created so far.  Its stack
    location is loaded into uxSavedTaskStackPointer. */
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
uint32_t ulCause;

    ux_Saved_స్థితి = ux_పోర్టు_సమితి_అంతరాయం_ముసుగు_From_ISR();
    {
        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            ulCause = ul_పోర్టు_Get_CP0_Cause();
            ulCause |= ( 1ul << 8UL );
            v_పోర్టు_సమితి_CP0_Cause( ulCause );
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

    prv_Disable_అంతరాయం();
    ux_Saved_స్థితి_రిజిస్టరు = ul_పోర్టు_Get_CP0_స్థితి() | 0x01;

    /* This clears the IPL bits, then sets them to
    configMAX_SYSCALL_INTERRUPT_PRIORITY.  This function should not be called
    from an interrupt that has a priority above
    configMAX_SYSCALL_INTERRUPT_PRIORITY so, when used correctly, the action
    can only result in the IPL being unchanged or raised, and therefore never
    lowered. */
    v_పోర్టు_సమితి_CP0_స్థితి( ( ( ux_Saved_స్థితి_రిజిస్టరు & ( ~పోర్టు_ALL_IPL_బిట్లు ) ) ) | ( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత << పోర్టు_IPL_జరుపు ) );

    తిరిగి ux_Saved_స్థితి_రిజిస్టరు;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Clear_అంతరాయం_ముసుగు_From_ISR( UBaseType_t ux_Saved_స్థితి_రిజిస్టరు )
{
    v_పోర్టు_సమితి_CP0_స్థితి( ux_Saved_స్థితి_రిజిస్టరు );
}
/*-----------------------------------------------------------*/
