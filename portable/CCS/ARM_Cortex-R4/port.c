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
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/*-----------------------------------------------------------*/

/* Count of the critical section nesting depth. */
uint32_t ulCriticalNesting = 9999;

/*-----------------------------------------------------------*/

/* Registers required to configure the RTI. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RTI_GCTRL_REG       ( * ( ( ಅಸ್ಥಿರ uint32_t * ) 0xFFFFFC00 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RTI_TBCTRL_REG      ( * ( ( ಅಸ್ಥಿರ uint32_t * ) 0xFFFFFC04 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RTI_COMPCTRL_REG    ( * ( ( ಅಸ್ಥಿರ uint32_t * ) 0xFFFFFC0C ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RTI_CNT0_FRC0_REG   ( * ( ( ಅಸ್ಥಿರ uint32_t * ) 0xFFFFFC10 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RTI_CNT0_UC0_REG    ( * ( ( ಅಸ್ಥಿರ uint32_t * ) 0xFFFFFC14 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RTI_CNT0_CPUC0_REG  ( * ( ( ಅಸ್ಥಿರ uint32_t * ) 0xFFFFFC18 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RTI_CNT0_COMP0_REG  ( * ( ( ಅಸ್ಥಿರ uint32_t * ) 0xFFFFFC50 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RTI_CNT0_UDCP0_REG  ( * ( ( ಅಸ್ಥಿರ uint32_t * ) 0xFFFFFC54 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RTI_SETINTENA_REG   ( * ( ( ಅಸ್ಥಿರ uint32_t * ) 0xFFFFFC80 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RTI_CLEARINTENA_REG ( * ( ( ಅಸ್ಥಿರ uint32_t * ) 0xFFFFFC84 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RTI_INTFLAG_REG     ( * ( ( ಅಸ್ಥಿರ uint32_t * ) 0xFFFFFC88 ) )


/* Constants required to set up the initial stack of each task. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_SPSR        ( ( ರಾಶಿ_Type_t ) 0x1F )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_FPSCR       ( ( ರಾಶಿ_Type_t ) 0x00 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INSTRUCTION_ಗಾತ್ರ    ( ( ರಾಶಿ_Type_t ) 0x04 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ಬಿಟ್      ( ( ರಾಶಿ_Type_t ) 0x20 )

/* The number of words on the stack frame between the saved Top Of Stack and
R0 (in which the parameters are passed. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SPACE_BETWEEN_TOS_AND_PARAMETERS    ( 12 )

/*-----------------------------------------------------------*/

/* vPortStartFirstSTask() is defined in portASM.asm */
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ );

/*-----------------------------------------------------------*/

/* Saved as part of the task context.  Set to pdFALSE if the task does not
require an FPU context. */
uint32_t ulTaskHasFPUContext = 0;

/*-----------------------------------------------------------*/


/*
 * See header file for description.
 */
ರಾಶಿ_Type_t *px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t *px_ತುದಿ_ದ_ರಾಶಿ, TaskFunction_t px_ಸಂಕೇತ, ಶೂನ್ಯ *pvParameters )
{
ರಾಶಿ_Type_t *pxOriginalTOS;

    pxOriginalTOS = px_ತುದಿ_ದ_ರಾಶಿ;

    #ಆದರೆ __TI_VFP_SUPPORT__
    {
        /* Ensure the stack is correctly aligned on exit. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
    }
    #ಆದರೆ_ಅಂತ್ಯ

    /* Setup the initial stack of the task.  The stack is set exactly as
    expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which is the start of the as
    the task has not executed yet.  The offset is added to make the return
    address appear as it would within an IRQ ISR. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ + ಪೋರ್ಟ್_INSTRUCTION_ಗಾತ್ರ;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x00000000; /* R14 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ ಪೋರ್ಟ್_PRELOAD_TASK_REGISTERS
    {
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x12121212; /* R12 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x11111111; /* R11 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x10101010; /* R10 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x09090909; /* R9 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x08080808; /* R8 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x07070707; /* R7 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x06060606; /* R6 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x05050505; /* R5 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x04040404; /* R4 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x03030303; /* R3 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x02020202; /* R2 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x01010101; /* R1 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
    }
    #ಇಲ್ಲದಿದ್ದರೆ
    {
        px_ತುದಿ_ದ_ರಾಶಿ -= ಪೋರ್ಟ್_SPACE_BETWEEN_TOS_AND_PARAMETERS;
    }
    #ಆದರೆ_ಅಂತ್ಯ

    /* Function parameters are passed in R0. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters; /* R0 */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* Set the status register for system mode, with interrupts enabled. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ( ( _get_CPSR() & ~0xFF ) | ಪೋರ್ಟ್_INITIAL_SPSR );

    ಆದರೆ( ( ( uint32_t ) px_ಸಂಕೇತ & 0x01UL ) != 0x00 )
    {
        /* The task will start in thumb mode. */
        *px_ತುದಿ_ದ_ರಾಶಿ |= ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ಬಿಟ್;
    }

    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __TI_VFP_SUPPORT__
    {
        px_ತುದಿ_ದ_ರಾಶಿ--;

        /* The last thing on the stack is the tasks ulUsingFPU value, which by
        default is set to indicate that the stack frame does not include FPU
        registers. */
        *px_ತುದಿ_ದ_ರಾಶಿ = pdFALSE;
    }
    #ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ(ಶೂನ್ಯ)
{
    /* Disable timer 0. */
    ಪೋರ್ಟ್_RTI_GCTRL_REG &= 0xFFFFFFFEUL;

    /* Use the internal counter. */
    ಪೋರ್ಟ್_RTI_TBCTRL_REG = 0x00000000U;

    /* COMPSEL0 will use the RTIFRC0 counter. */
    ಪೋರ್ಟ್_RTI_COMPCTRL_REG = 0x00000000U;

    /* Initialise the counter and the prescale counter registers. */
    ಪೋರ್ಟ್_RTI_CNT0_UC0_REG =  0x00000000U;
    ಪೋರ್ಟ್_RTI_CNT0_FRC0_REG =  0x00000000U;

    /* Set Prescalar for RTI clock. */
    ಪೋರ್ಟ್_RTI_CNT0_CPUC0_REG = 0x00000001U;
    ಪೋರ್ಟ್_RTI_CNT0_COMP0_REG = ( configCPU_CLOCK_HZ / 2 ) / config_TICK_ದರ_HZ;
    ಪೋರ್ಟ್_RTI_CNT0_UDCP0_REG = ( configCPU_CLOCK_HZ / 2 ) / config_TICK_ದರ_HZ;

    /* Clear interrupts. */
    ಪೋರ್ಟ್_RTI_INTFLAG_REG =  0x0007000FU;
    ಪೋರ್ಟ್_RTI_CLEARINTENA_REG = 0x00070F0FU;

    /* Enable the compare 0 interrupt. */
    ಪೋರ್ಟ್_RTI_SETINTENA_REG = 0x00000001U;
    ಪೋರ್ಟ್_RTI_GCTRL_REG |= 0x00000001U;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler(ಶೂನ್ಯ)
{
    /* Start the timer that generates the tick ISR. */
    prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    /* Reset the critical section nesting count read to execute the first task. */
    ulCriticalNesting = 0;

    /* Start the first task.  This is done from portASM.asm as ARM mode must be
    used. */
    v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task();

    /* Should not get here! */
    ಹಿಂತಿರುಗಿ pdFAIL;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler(ಶೂನ್ಯ)
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

#ಆದರೆ configUSE_PREEMPTION == 0

    /* The cooperative scheduler requires a normal IRQ service routine to
     * simply increment the system tick. */
    __interrupt ಶೂನ್ಯ v_ಪೋರ್ಟ್_Non_Preemptive_Tick( ಶೂನ್ಯ )
    {
        /* clear clock interrupt flag */
        ಪೋರ್ಟ್_RTI_INTFLAG_REG = 0x00000001;

        /* Increment the tick count - this may make a delaying task ready
        to run - but a context switch is not performed. */
        xTaskIncrementTick();
    }

 #ಇಲ್ಲದಿದ್ದರೆ

    /*
     **************************************************************************
     * The preemptive scheduler ISR is written in assembler and can be found
     * in the portASM.asm file. This will only get used if portUSE_PREEMPTION
     * is set to 1 in portmacro.h
     **************************************************************************
     */
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Preemptive_Tick( ಶೂನ್ಯ );

#ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/


/*
 * Disable interrupts, and keep a count of the nesting depth.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ )
{
    /* Disable interrupts as per portDISABLE_INTERRUPTS(); */
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();

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
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ )
{
    ಆದರೆ( ulCriticalNesting > 0 )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
        re-enabled. */
        ಆದರೆ( ulCriticalNesting == 0 )
        {
            /* Enable interrupts as per portENABLE_INTERRUPTS(). */
            ಪೋರ್ಟ್_ENABLE_INTERRUPTS();
        }
    }
}
/*-----------------------------------------------------------*/

#ಆದರೆ __TI_VFP_SUPPORT__

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Task_ಬಳಸುತ್ತದೆ_FPU( ಶೂನ್ಯ )
    {
    ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Initialise_FPSCR( ಶೂನ್ಯ );

        /* A task is registering the fact that it needs an FPU context.  Set the
        FPU flag (saved as part of the task context. */
        ulTaskHasFPUContext = pdTRUE;

        /* Initialise the floating point status register. */
        v_ಪೋರ್ಟ್_Initialise_FPSCR();
    }

#ಆದರೆ_ಅಂತ್ಯ /* __TI_VFP_SUPPORT__ */

/*-----------------------------------------------------------*/
