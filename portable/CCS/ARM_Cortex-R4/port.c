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

/* FreeRTOS includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/*-----------------------------------------------------------*/

/* Count of the critical section nesting depth. */
uint32_t ulCriticalNesting = 9999;

/*-----------------------------------------------------------*/

/* Registers required to configure the RTI. */
#నిర్వచించు పోర్టు_RTI_GCTRL_REG       ( * ( ( అస్థిర uint32_t * ) 0xFFFFFC00 ) )
#నిర్వచించు పోర్టు_RTI_TBCTRL_REG      ( * ( ( అస్థిర uint32_t * ) 0xFFFFFC04 ) )
#నిర్వచించు పోర్టు_RTI_COMPCTRL_REG    ( * ( ( అస్థిర uint32_t * ) 0xFFFFFC0C ) )
#నిర్వచించు పోర్టు_RTI_CNT0_FRC0_REG   ( * ( ( అస్థిర uint32_t * ) 0xFFFFFC10 ) )
#నిర్వచించు పోర్టు_RTI_CNT0_UC0_REG    ( * ( ( అస్థిర uint32_t * ) 0xFFFFFC14 ) )
#నిర్వచించు పోర్టు_RTI_CNT0_CPUC0_REG  ( * ( ( అస్థిర uint32_t * ) 0xFFFFFC18 ) )
#నిర్వచించు పోర్టు_RTI_CNT0_COMP0_REG  ( * ( ( అస్థిర uint32_t * ) 0xFFFFFC50 ) )
#నిర్వచించు పోర్టు_RTI_CNT0_UDCP0_REG  ( * ( ( అస్థిర uint32_t * ) 0xFFFFFC54 ) )
#నిర్వచించు పోర్టు_RTI_SETINTENA_REG   ( * ( ( అస్థిర uint32_t * ) 0xFFFFFC80 ) )
#నిర్వచించు పోర్టు_RTI_CLEARINTENA_REG ( * ( ( అస్థిర uint32_t * ) 0xFFFFFC84 ) )
#నిర్వచించు పోర్టు_RTI_INTFLAG_REG     ( * ( ( అస్థిర uint32_t * ) 0xFFFFFC88 ) )


/* Constants required to set up the initial stack of each task. */
#నిర్వచించు పోర్టు_INITIAL_SPSR        ( ( దొంతర_Type_t ) 0x1F )
#నిర్వచించు పోర్టు_INITIAL_FPSCR       ( ( దొంతర_Type_t ) 0x00 )
#నిర్వచించు పోర్టు_INSTRUCTION_కొలత    ( ( దొంతర_Type_t ) 0x04 )
#నిర్వచించు పోర్టు_THUMB_బహుళకం_బిట్టు      ( ( దొంతర_Type_t ) 0x20 )

/* The number of words on the stack frame between the saved Top Of Stack and
R0 (in which the parameters are passed. */
#నిర్వచించు పోర్టు_SPACE_BETWEEN_TOS_AND_PARAMETERS    ( 12 )

/*-----------------------------------------------------------*/

/* vPortStartFirstSTask() is defined in portASM.asm */
బాహ్య శూన్య v_పోర్టు_ప్రారంభం_మొదటి_Task( శూన్య );

/*-----------------------------------------------------------*/

/* Saved as part of the task context.  Set to pdFALSE if the task does not
require an FPU context. */
uint32_t ulTaskHasFPUContext = 0;

/*-----------------------------------------------------------*/


/*
 * See header file for description.
 */
దొంతర_Type_t *px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t *px_శిఖరం_యొక్క_దొంతర, TaskFunction_t px_సంకేతం, శూన్య *pvParameters )
{
దొంతర_Type_t *pxOriginalTOS;

    pxOriginalTOS = px_శిఖరం_యొక్క_దొంతర;

    #ఒకవేళ __TI_VFP_SUPPORT__
    {
        /* Ensure the stack is correctly aligned on exit. */
        px_శిఖరం_యొక్క_దొంతర--;
    }
    #అయితే_ముగింపు

    /* Setup the initial stack of the task.  The stack is set exactly as
    expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which is the start of the as
    the task has not executed yet.  The offset is added to make the return
    address appear as it would within an IRQ ISR. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం + పోర్టు_INSTRUCTION_కొలత;
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x00000000; /* R14 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_శిఖరం_యొక్క_దొంతర--;

    #నిర్వచితమైతే పోర్టు_PRELOAD_TASK_REGISTERS
    {
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x12121212; /* R12 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x11111111; /* R11 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x10101010; /* R10 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x09090909; /* R9 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x08080808; /* R8 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x07070707; /* R7 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x06060606; /* R6 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x05050505; /* R5 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x04040404; /* R4 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x03030303; /* R3 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x02020202; /* R2 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x01010101; /* R1 */
        px_శిఖరం_యొక్క_దొంతర--;
    }
    #లేకపోతే
    {
        px_శిఖరం_యొక్క_దొంతర -= పోర్టు_SPACE_BETWEEN_TOS_AND_PARAMETERS;
    }
    #అయితే_ముగింపు

    /* Function parameters are passed in R0. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters; /* R0 */
    px_శిఖరం_యొక్క_దొంతర--;

    /* Set the status register for system mode, with interrupts enabled. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ( ( _get_CPSR() & ~0xFF ) | పోర్టు_INITIAL_SPSR );

    ఒకవేళ( ( ( uint32_t ) px_సంకేతం & 0x01UL ) != 0x00 )
    {
        /* The task will start in thumb mode. */
        *px_శిఖరం_యొక్క_దొంతర |= పోర్టు_THUMB_బహుళకం_బిట్టు;
    }

    #నిర్వచితమైతే __TI_VFP_SUPPORT__
    {
        px_శిఖరం_యొక్క_దొంతర--;

        /* The last thing on the stack is the tasks ulUsingFPU value, which by
        default is set to indicate that the stack frame does not include FPU
        registers. */
        *px_శిఖరం_యొక్క_దొంతర = pdFALSE;
    }
    #అయితే_ముగింపు

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం(శూన్య)
{
    /* Disable timer 0. */
    పోర్టు_RTI_GCTRL_REG &= 0xFFFFFFFEUL;

    /* Use the internal counter. */
    పోర్టు_RTI_TBCTRL_REG = 0x00000000U;

    /* COMPSEL0 will use the RTIFRC0 counter. */
    పోర్టు_RTI_COMPCTRL_REG = 0x00000000U;

    /* Initialise the counter and the prescale counter registers. */
    పోర్టు_RTI_CNT0_UC0_REG =  0x00000000U;
    పోర్టు_RTI_CNT0_FRC0_REG =  0x00000000U;

    /* Set Prescalar for RTI clock. */
    పోర్టు_RTI_CNT0_CPUC0_REG = 0x00000001U;
    పోర్టు_RTI_CNT0_COMP0_REG = ( configCPU_CLOCK_HZ / 2 ) / config_TICK_రేటు_HZ;
    పోర్టు_RTI_CNT0_UDCP0_REG = ( configCPU_CLOCK_HZ / 2 ) / config_TICK_రేటు_HZ;

    /* Clear interrupts. */
    పోర్టు_RTI_INTFLAG_REG =  0x0007000FU;
    పోర్టు_RTI_CLEARINTENA_REG = 0x00070F0FU;

    /* Enable the compare 0 interrupt. */
    పోర్టు_RTI_SETINTENA_REG = 0x00000001U;
    పోర్టు_RTI_GCTRL_REG |= 0x00000001U;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler(శూన్య)
{
    /* Start the timer that generates the tick ISR. */
    prv_అమరిక_Timer_అంతరాయం();

    /* Reset the critical section nesting count read to execute the first task. */
    ulCriticalNesting = 0;

    /* Start the first task.  This is done from portASM.asm as ARM mode must be
    used. */
    v_పోర్టు_ప్రారంభం_మొదటి_Task();

    /* Should not get here! */
    తిరిగి pdFAIL;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
శూన్య v_పోర్టు_చివర_Scheduler(శూన్య)
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

#ఒకవేళ configUSE_PREEMPTION == 0

    /* The cooperative scheduler requires a normal IRQ service routine to
     * simply increment the system tick. */
    __interrupt శూన్య v_పోర్టు_Non_Preemptive_Tick( శూన్య )
    {
        /* clear clock interrupt flag */
        పోర్టు_RTI_INTFLAG_REG = 0x00000001;

        /* Increment the tick count - this may make a delaying task ready
        to run - but a context switch is not performed. */
        xTaskIncrementTick();
    }

 #లేకపోతే

    /*
     **************************************************************************
     * The preemptive scheduler ISR is written in assembler and can be found
     * in the portASM.asm file. This will only get used if portUSE_PREEMPTION
     * is set to 1 in portmacro.h
     **************************************************************************
     */
    శూన్య v_పోర్టు_Preemptive_Tick( శూన్య );

#అయితే_ముగింపు
/*-----------------------------------------------------------*/


/*
 * Disable interrupts, and keep a count of the nesting depth.
 */
శూన్య v_పోర్టు_Enter_Critical( శూన్య )
{
    /* Disable interrupts as per portDISABLE_INTERRUPTS(); */
    పోర్టు_DISABLE_INTERRUPTS();

    /* Now interrupts are disabled ulCriticalNesting can be accessed
    directly.  Increment ulCriticalNesting to keep a count of how many times
    portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

/*
 * Decrement the critical nesting count, and if it has reached zero, re-enable
 * interrupts.
 */
శూన్య v_పోర్టు_Exit_Critical( శూన్య )
{
    ఒకవేళ( ulCriticalNesting > 0 )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
        re-enabled. */
        ఒకవేళ( ulCriticalNesting == 0 )
        {
            /* Enable interrupts as per portENABLE_INTERRUPTS(). */
            పోర్టు_ENABLE_INTERRUPTS();
        }
    }
}
/*-----------------------------------------------------------*/

#ఒకవేళ __TI_VFP_SUPPORT__

    శూన్య v_పోర్టు_Task_ఉపయోగిస్తుంది_FPU( శూన్య )
    {
    బాహ్య శూన్య v_పోర్టు_Initialise_FPSCR( శూన్య );

        /* A task is registering the fact that it needs an FPU context.  Set the
        FPU flag (saved as part of the task context. */
        ulTaskHasFPUContext = pdTRUE;

        /* Initialise the floating point status register. */
        v_పోర్టు_Initialise_FPSCR();
    }

#అయితే_ముగింపు /* __TI_VFP_SUPPORT__ */

/*-----------------------------------------------------------*/
