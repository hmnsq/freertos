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
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

/*-----------------------------------------------------------*/

/* Count of the critical section nesting depth. */
uint32_t ulCriticalNesting = 9999;

/*-----------------------------------------------------------*/

/* Registers required to configure the RTI. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RTI_GCTRL_REG       ( * ( ( ਅਸਥਿਰ uint32_t * ) 0xFFFFFC00 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RTI_TBCTRL_REG      ( * ( ( ਅਸਥਿਰ uint32_t * ) 0xFFFFFC04 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RTI_COMPCTRL_REG    ( * ( ( ਅਸਥਿਰ uint32_t * ) 0xFFFFFC0C ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RTI_CNT0_FRC0_REG   ( * ( ( ਅਸਥਿਰ uint32_t * ) 0xFFFFFC10 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RTI_CNT0_UC0_REG    ( * ( ( ਅਸਥਿਰ uint32_t * ) 0xFFFFFC14 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RTI_CNT0_CPUC0_REG  ( * ( ( ਅਸਥਿਰ uint32_t * ) 0xFFFFFC18 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RTI_CNT0_COMP0_REG  ( * ( ( ਅਸਥਿਰ uint32_t * ) 0xFFFFFC50 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RTI_CNT0_UDCP0_REG  ( * ( ( ਅਸਥਿਰ uint32_t * ) 0xFFFFFC54 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RTI_SETINTENA_REG   ( * ( ( ਅਸਥਿਰ uint32_t * ) 0xFFFFFC80 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RTI_CLEARINTENA_REG ( * ( ( ਅਸਥਿਰ uint32_t * ) 0xFFFFFC84 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RTI_INTFLAG_REG     ( * ( ( ਅਸਥਿਰ uint32_t * ) 0xFFFFFC88 ) )


/* Constants required to set up the initial stack of each task. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_SPSR        ( ( ਢੇਰ_Type_t ) 0x1F )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_FPSCR       ( ( ਢੇਰ_Type_t ) 0x00 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INSTRUCTION_ਮਾਪ    ( ( ਢੇਰ_Type_t ) 0x04 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_THUMB_ਬਹੁਲਕ_ਦੋਆਧਾਰੀ_ਅੰਕ      ( ( ਢੇਰ_Type_t ) 0x20 )

/* The number of words on the stack frame between the saved Top Of Stack and
R0 (in which the parameters are passed. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SPACE_BETWEEN_TOS_AND_PARAMETERS    ( 12 )

/*-----------------------------------------------------------*/

/* vPortStartFirstSTask() is defined in portASM.asm */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task( ਖਾਲੀ );

/*-----------------------------------------------------------*/

/* Saved as part of the task context.  Set to pdFALSE if the task does not
require an FPU context. */
uint32_t ulTaskHasFPUContext = 0;

/*-----------------------------------------------------------*/


/*
 * See header file for description.
 */
ਢੇਰ_Type_t *px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t *px_ਸਿਖਰ_ਦਾ_ਢੇਰ, TaskFunction_t px_ਕੋਡ, ਖਾਲੀ *pvParameters )
{
ਢੇਰ_Type_t *pxOriginalTOS;

    pxOriginalTOS = px_ਸਿਖਰ_ਦਾ_ਢੇਰ;

    #ਜੇ __TI_VFP_SUPPORT__
    {
        /* Ensure the stack is correctly aligned on exit. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    }
    #ਜੇ_ਅੰਤ

    /* Setup the initial stack of the task.  The stack is set exactly as
    expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which is the start of the as
    the task has not executed yet.  The offset is added to make the return
    address appear as it would within an IRQ ISR. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ + ਪੋਰਟ_INSTRUCTION_ਮਾਪ;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x00000000; /* R14 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ ਪੋਰਟ_PRELOAD_TASK_REGISTERS
    {
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x12121212; /* R12 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x11111111; /* R11 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x10101010; /* R10 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x09090909; /* R9 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x08080808; /* R8 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x07070707; /* R7 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x06060606; /* R6 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x05050505; /* R5 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x04040404; /* R4 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x03030303; /* R3 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x02020202; /* R2 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x01010101; /* R1 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    }
    #ਨਹੀਂਤਾਂ
    {
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= ਪੋਰਟ_SPACE_BETWEEN_TOS_AND_PARAMETERS;
    }
    #ਜੇ_ਅੰਤ

    /* Function parameters are passed in R0. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters; /* R0 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* Set the status register for system mode, with interrupts enabled. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ( ( _get_CPSR() & ~0xFF ) | ਪੋਰਟ_INITIAL_SPSR );

    ਜੇ( ( ( uint32_t ) px_ਕੋਡ & 0x01UL ) != 0x00 )
    {
        /* The task will start in thumb mode. */
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ |= ਪੋਰਟ_THUMB_ਬਹੁਲਕ_ਦੋਆਧਾਰੀ_ਅੰਕ;
    }

    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __TI_VFP_SUPPORT__
    {
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

        /* The last thing on the stack is the tasks ulUsingFPU value, which by
        default is set to indicate that the stack frame does not include FPU
        registers. */
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = pdFALSE;
    }
    #ਜੇ_ਅੰਤ

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ(ਖਾਲੀ)
{
    /* Disable timer 0. */
    ਪੋਰਟ_RTI_GCTRL_REG &= 0xFFFFFFFEUL;

    /* Use the internal counter. */
    ਪੋਰਟ_RTI_TBCTRL_REG = 0x00000000U;

    /* COMPSEL0 will use the RTIFRC0 counter. */
    ਪੋਰਟ_RTI_COMPCTRL_REG = 0x00000000U;

    /* Initialise the counter and the prescale counter registers. */
    ਪੋਰਟ_RTI_CNT0_UC0_REG =  0x00000000U;
    ਪੋਰਟ_RTI_CNT0_FRC0_REG =  0x00000000U;

    /* Set Prescalar for RTI clock. */
    ਪੋਰਟ_RTI_CNT0_CPUC0_REG = 0x00000001U;
    ਪੋਰਟ_RTI_CNT0_COMP0_REG = ( configCPU_CLOCK_HZ / 2 ) / config_TICK_ਦਰ_HZ;
    ਪੋਰਟ_RTI_CNT0_UDCP0_REG = ( configCPU_CLOCK_HZ / 2 ) / config_TICK_ਦਰ_HZ;

    /* Clear interrupts. */
    ਪੋਰਟ_RTI_INTFLAG_REG =  0x0007000FU;
    ਪੋਰਟ_RTI_CLEARINTENA_REG = 0x00070F0FU;

    /* Enable the compare 0 interrupt. */
    ਪੋਰਟ_RTI_SETINTENA_REG = 0x00000001U;
    ਪੋਰਟ_RTI_GCTRL_REG |= 0x00000001U;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler(ਖਾਲੀ)
{
    /* Start the timer that generates the tick ISR. */
    prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

    /* Reset the critical section nesting count read to execute the first task. */
    ulCriticalNesting = 0;

    /* Start the first task.  This is done from portASM.asm as ARM mode must be
    used. */
    v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();

    /* Should not get here! */
    ਵਾਪਸ pdFAIL;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler(ਖਾਲੀ)
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

#ਜੇ configUSE_PREEMPTION == 0

    /* The cooperative scheduler requires a normal IRQ service routine to
     * simply increment the system tick. */
    __interrupt ਖਾਲੀ v_ਪੋਰਟ_Non_Preemptive_Tick( ਖਾਲੀ )
    {
        /* clear clock interrupt flag */
        ਪੋਰਟ_RTI_INTFLAG_REG = 0x00000001;

        /* Increment the tick count - this may make a delaying task ready
        to run - but a context switch is not performed. */
        xTaskIncrementTick();
    }

 #ਨਹੀਂਤਾਂ

    /*
     **************************************************************************
     * The preemptive scheduler ISR is written in assembler and can be found
     * in the portASM.asm file. This will only get used if portUSE_PREEMPTION
     * is set to 1 in portmacro.h
     **************************************************************************
     */
    ਖਾਲੀ v_ਪੋਰਟ_Preemptive_Tick( ਖਾਲੀ );

#ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/


/*
 * Disable interrupts, and keep a count of the nesting depth.
 */
ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ )
{
    /* Disable interrupts as per portDISABLE_INTERRUPTS(); */
    ਪੋਰਟ_DISABLE_INTERRUPTS();

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
ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ )
{
    ਜੇ( ulCriticalNesting > 0 )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
        re-enabled. */
        ਜੇ( ulCriticalNesting == 0 )
        {
            /* Enable interrupts as per portENABLE_INTERRUPTS(). */
            ਪੋਰਟ_ENABLE_INTERRUPTS();
        }
    }
}
/*-----------------------------------------------------------*/

#ਜੇ __TI_VFP_SUPPORT__

    ਖਾਲੀ v_ਪੋਰਟ_Task_ਵਰਤਦਾ_FPU( ਖਾਲੀ )
    {
    ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Initialise_FPSCR( ਖਾਲੀ );

        /* A task is registering the fact that it needs an FPU context.  Set the
        FPU flag (saved as part of the task context. */
        ulTaskHasFPUContext = pdTRUE;

        /* Initialise the floating point status register. */
        v_ਪੋਰਟ_Initialise_FPSCR();
    }

#ਜੇ_ਅੰਤ /* __TI_VFP_SUPPORT__ */

/*-----------------------------------------------------------*/
