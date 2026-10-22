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
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/*-----------------------------------------------------------*/

/* Count of the critical section nesting depth. */
uint32_t ulCriticalNesting = 9999;

/*-----------------------------------------------------------*/

/* Registers required to configure the RTI. */
#تعریف_کن پورت_RTI_GCTRL_REG       ( * ( ( متطاير uint32_t * ) 0xFFFFFC00 ) )
#تعریف_کن پورت_RTI_TBCTRL_REG      ( * ( ( متطاير uint32_t * ) 0xFFFFFC04 ) )
#تعریف_کن پورت_RTI_COMPCTRL_REG    ( * ( ( متطاير uint32_t * ) 0xFFFFFC0C ) )
#تعریف_کن پورت_RTI_CNT0_FRC0_REG   ( * ( ( متطاير uint32_t * ) 0xFFFFFC10 ) )
#تعریف_کن پورت_RTI_CNT0_UC0_REG    ( * ( ( متطاير uint32_t * ) 0xFFFFFC14 ) )
#تعریف_کن پورت_RTI_CNT0_CPUC0_REG  ( * ( ( متطاير uint32_t * ) 0xFFFFFC18 ) )
#تعریف_کن پورت_RTI_CNT0_COMP0_REG  ( * ( ( متطاير uint32_t * ) 0xFFFFFC50 ) )
#تعریف_کن پورت_RTI_CNT0_UDCP0_REG  ( * ( ( متطاير uint32_t * ) 0xFFFFFC54 ) )
#تعریف_کن پورت_RTI_SETINTENA_REG   ( * ( ( متطاير uint32_t * ) 0xFFFFFC80 ) )
#تعریف_کن پورت_RTI_CLEARINTENA_REG ( * ( ( متطاير uint32_t * ) 0xFFFFFC84 ) )
#تعریف_کن پورت_RTI_INTFLAG_REG     ( * ( ( متطاير uint32_t * ) 0xFFFFFC88 ) )


/* Constants required to set up the initial stack of each task. */
#تعریف_کن پورت_INITIAL_SPSR        ( ( پشته_Type_t ) 0x1F )
#تعریف_کن پورت_INITIAL_FPSCR       ( ( پشته_Type_t ) 0x00 )
#تعریف_کن پورت_INSTRUCTION_اندازه    ( ( پشته_Type_t ) 0x04 )
#تعریف_کن پورت_THUMB_نما_بیت      ( ( پشته_Type_t ) 0x20 )

/* The number of words on the stack frame between the saved Top Of Stack and
R0 (in which the parameters are passed. */
#تعریف_کن پورت_SPACE_BETWEEN_TOS_AND_PARAMETERS    ( 12 )

/*-----------------------------------------------------------*/

/* vPortStartFirstSTask() is defined in portASM.asm */
خارجي فراغ v_پورت_شروع_اولی_Task( فراغ );

/*-----------------------------------------------------------*/

/* Saved as part of the task context.  Set to pdFALSE if the task does not
require an FPU context. */
uint32_t ulTaskHasFPUContext = 0;

/*-----------------------------------------------------------*/


/*
 * See header file for description.
 */
پشته_Type_t *px_پورت_Initialise_پشته( پشته_Type_t *px_بالاترین_از_پشته, TaskFunction_t px_کد, فراغ *pvParameters )
{
پشته_Type_t *pxOriginalTOS;

    pxOriginalTOS = px_بالاترین_از_پشته;

    #إذا __TI_VFP_SUPPORT__
    {
        /* Ensure the stack is correctly aligned on exit. */
        px_بالاترین_از_پشته--;
    }
    #پایان_اگر

    /* Setup the initial stack of the task.  The stack is set exactly as
    expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which is the start of the as
    the task has not executed yet.  The offset is added to make the return
    address appear as it would within an IRQ ISR. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) px_کد + پورت_INSTRUCTION_اندازه;
    px_بالاترین_از_پشته--;

    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x00000000; /* R14 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_بالاترین_از_پشته--;

    #اگر_تعریف_شده پورت_PRELOAD_TASK_REGISTERS
    {
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x12121212; /* R12 */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x11111111; /* R11 */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x10101010; /* R10 */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x09090909; /* R9 */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x08080808; /* R8 */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x07070707; /* R7 */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x06060606; /* R6 */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x05050505; /* R5 */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x04040404; /* R4 */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x03030303; /* R3 */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x02020202; /* R2 */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x01010101; /* R1 */
        px_بالاترین_از_پشته--;
    }
    #وإلا
    {
        px_بالاترین_از_پشته -= پورت_SPACE_BETWEEN_TOS_AND_PARAMETERS;
    }
    #پایان_اگر

    /* Function parameters are passed in R0. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) pvParameters; /* R0 */
    px_بالاترین_از_پشته--;

    /* Set the status register for system mode, with interrupts enabled. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) ( ( _get_CPSR() & ~0xFF ) | پورت_INITIAL_SPSR );

    إذا( ( ( uint32_t ) px_کد & 0x01UL ) != 0x00 )
    {
        /* The task will start in thumb mode. */
        *px_بالاترین_از_پشته |= پورت_THUMB_نما_بیت;
    }

    #اگر_تعریف_شده __TI_VFP_SUPPORT__
    {
        px_بالاترین_از_پشته--;

        /* The last thing on the stack is the tasks ulUsingFPU value, which by
        default is set to indicate that the stack frame does not include FPU
        registers. */
        *px_بالاترین_از_پشته = pdFALSE;
    }
    #پایان_اگر

    أرجع px_بالاترین_از_پشته;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_راهاندازی_Timer_وقفه(فراغ)
{
    /* Disable timer 0. */
    پورت_RTI_GCTRL_REG &= 0xFFFFFFFEUL;

    /* Use the internal counter. */
    پورت_RTI_TBCTRL_REG = 0x00000000U;

    /* COMPSEL0 will use the RTIFRC0 counter. */
    پورت_RTI_COMPCTRL_REG = 0x00000000U;

    /* Initialise the counter and the prescale counter registers. */
    پورت_RTI_CNT0_UC0_REG =  0x00000000U;
    پورت_RTI_CNT0_FRC0_REG =  0x00000000U;

    /* Set Prescalar for RTI clock. */
    پورت_RTI_CNT0_CPUC0_REG = 0x00000001U;
    پورت_RTI_CNT0_COMP0_REG = ( configCPU_CLOCK_HZ / 2 ) / config_TICK_نرخ_HZ;
    پورت_RTI_CNT0_UDCP0_REG = ( configCPU_CLOCK_HZ / 2 ) / config_TICK_نرخ_HZ;

    /* Clear interrupts. */
    پورت_RTI_INTFLAG_REG =  0x0007000FU;
    پورت_RTI_CLEARINTENA_REG = 0x00070F0FU;

    /* Enable the compare 0 interrupt. */
    پورت_RTI_SETINTENA_REG = 0x00000001U;
    پورت_RTI_GCTRL_REG |= 0x00000001U;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
پایه_Type_t x_پورت_شروع_Scheduler(فراغ)
{
    /* Start the timer that generates the tick ISR. */
    prv_راهاندازی_Timer_وقفه();

    /* Reset the critical section nesting count read to execute the first task. */
    ulCriticalNesting = 0;

    /* Start the first task.  This is done from portASM.asm as ARM mode must be
    used. */
    v_پورت_شروع_اولی_Task();

    /* Should not get here! */
    أرجع pdFAIL;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
فراغ v_پورت_انتها_Scheduler(فراغ)
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

#إذا configUSE_PREEMPTION == 0

    /* The cooperative scheduler requires a normal IRQ service routine to
     * simply increment the system tick. */
    __interrupt فراغ v_پورت_Non_Preemptive_Tick( فراغ )
    {
        /* clear clock interrupt flag */
        پورت_RTI_INTFLAG_REG = 0x00000001;

        /* Increment the tick count - this may make a delaying task ready
        to run - but a context switch is not performed. */
        xTaskIncrementTick();
    }

 #وإلا

    /*
     **************************************************************************
     * The preemptive scheduler ISR is written in assembler and can be found
     * in the portASM.asm file. This will only get used if portUSE_PREEMPTION
     * is set to 1 in portmacro.h
     **************************************************************************
     */
    فراغ v_پورت_Preemptive_Tick( فراغ );

#پایان_اگر
/*-----------------------------------------------------------*/


/*
 * Disable interrupts, and keep a count of the nesting depth.
 */
فراغ v_پورت_Enter_Critical( فراغ )
{
    /* Disable interrupts as per portDISABLE_INTERRUPTS(); */
    پورت_DISABLE_INTERRUPTS();

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
فراغ v_پورت_Exit_Critical( فراغ )
{
    إذا( ulCriticalNesting > 0 )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
        re-enabled. */
        إذا( ulCriticalNesting == 0 )
        {
            /* Enable interrupts as per portENABLE_INTERRUPTS(). */
            پورت_ENABLE_INTERRUPTS();
        }
    }
}
/*-----------------------------------------------------------*/

#إذا __TI_VFP_SUPPORT__

    فراغ v_پورت_Task_استفاده_میکند_FPU( فراغ )
    {
    خارجي فراغ v_پورت_Initialise_FPSCR( فراغ );

        /* A task is registering the fact that it needs an FPU context.  Set the
        FPU flag (saved as part of the task context. */
        ulTaskHasFPUContext = pdTRUE;

        /* Initialise the floating point status register. */
        v_پورت_Initialise_FPSCR();
    }

#پایان_اگر /* __TI_VFP_SUPPORT__ */

/*-----------------------------------------------------------*/
