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
#ଅନ୍ତର୍ଭାଵ "FreeRTOS.h"
#ଅନ୍ତର୍ଭାଵ "task.h"

/*-----------------------------------------------------------*/

/* Count of the critical section nesting depth. */
uint32_t ulCriticalNesting = 9999;

/*-----------------------------------------------------------*/

/* Registers required to configure the RTI. */
#define portRTI_GCTRL_REG       ( * ( ( ଅସ୍ଥିର uint32_t * ) 0xFFFFFC00 ) )
#define portRTI_TBCTRL_REG      ( * ( ( ଅସ୍ଥିର uint32_t * ) 0xFFFFFC04 ) )
#define portRTI_COMPCTRL_REG    ( * ( ( ଅସ୍ଥିର uint32_t * ) 0xFFFFFC0C ) )
#define portRTI_CNT0_FRC0_REG   ( * ( ( ଅସ୍ଥିର uint32_t * ) 0xFFFFFC10 ) )
#define portRTI_CNT0_UC0_REG    ( * ( ( ଅସ୍ଥିର uint32_t * ) 0xFFFFFC14 ) )
#define portRTI_CNT0_CPUC0_REG  ( * ( ( ଅସ୍ଥିର uint32_t * ) 0xFFFFFC18 ) )
#define portRTI_CNT0_COMP0_REG  ( * ( ( ଅସ୍ଥିର uint32_t * ) 0xFFFFFC50 ) )
#define portRTI_CNT0_UDCP0_REG  ( * ( ( ଅସ୍ଥିର uint32_t * ) 0xFFFFFC54 ) )
#define portRTI_SETINTENA_REG   ( * ( ( ଅସ୍ଥିର uint32_t * ) 0xFFFFFC80 ) )
#define portRTI_CLEARINTENA_REG ( * ( ( ଅସ୍ଥିର uint32_t * ) 0xFFFFFC84 ) )
#define portRTI_INTFLAG_REG     ( * ( ( ଅସ୍ଥିର uint32_t * ) 0xFFFFFC88 ) )


/* Constants required to set up the initial stack of each task. */
#define portINITIAL_SPSR        ( ( ଗଦା_Type_t ) 0x1F )
#define portINITIAL_FPSCR       ( ( ଗଦା_Type_t ) 0x00 )
#define portINSTRUCTION_SIZE    ( ( ଗଦା_Type_t ) 0x04 )
#define portTHUMB_MODE_BIT      ( ( ଗଦା_Type_t ) 0x20 )

/* The number of words on the stack frame between the saved Top Of Stack and
R0 (in which the parameters are passed. */
#define portSPACE_BETWEEN_TOS_AND_PARAMETERS    ( 12 )

/*-----------------------------------------------------------*/

/* vPortStartFirstSTask() is defined in portASM.asm */
ବାହ୍ୟ ଶୂନ୍ୟ vPortStartFirstTask( ଶୂନ୍ୟ );

/*-----------------------------------------------------------*/

/* Saved as part of the task context.  Set to pdFALSE if the task does not
require an FPU context. */
uint32_t ulTaskHasFPUContext = 0;

/*-----------------------------------------------------------*/


/*
 * See header file for description.
 */
ଗଦା_Type_t *px_Port_Initialise_ଗଦା( ଗଦା_Type_t *px_ଶୀର୍ଷ_Of_ଗଦା, TaskFunction_t pxCode, ଶୂନ୍ୟ *pvParameters )
{
ଗଦା_Type_t *pxOriginalTOS;

    pxOriginalTOS = px_ଶୀର୍ଷ_Of_ଗଦା;

    #ଯଦି __TI_VFP_SUPPORT__
    {
        /* Ensure the stack is correctly aligned on exit. */
        px_ଶୀର୍ଷ_Of_ଗଦା--;
    }
    #endif

    /* Setup the initial stack of the task.  The stack is set exactly as
    expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which is the start of the as
    the task has not executed yet.  The offset is added to make the return
    address appear as it would within an IRQ ISR. */
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) pxCode + portINSTRUCTION_SIZE;
    px_ଶୀର୍ଷ_Of_ଗଦା--;

    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x00000000; /* R14 */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_ଶୀର୍ଷ_Of_ଗଦା--;

    #ifdef portPRELOAD_TASK_REGISTERS
    {
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x12121212; /* R12 */
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x11111111; /* R11 */
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x10101010; /* R10 */
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x09090909; /* R9 */
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x08080808; /* R8 */
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x07070707; /* R7 */
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x06060606; /* R6 */
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x05050505; /* R5 */
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x04040404; /* R4 */
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x03030303; /* R3 */
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x02020202; /* R2 */
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x01010101; /* R1 */
        px_ଶୀର୍ଷ_Of_ଗଦା--;
    }
    #ଅନ୍ୟଥା
    {
        px_ଶୀର୍ଷ_Of_ଗଦା -= portSPACE_BETWEEN_TOS_AND_PARAMETERS;
    }
    #endif

    /* Function parameters are passed in R0. */
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) pvParameters; /* R0 */
    px_ଶୀର୍ଷ_Of_ଗଦା--;

    /* Set the status register for system mode, with interrupts enabled. */
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) ( ( _get_CPSR() & ~0xFF ) | portINITIAL_SPSR );

    ଯଦି( ( ( uint32_t ) pxCode & 0x01UL ) != 0x00 )
    {
        /* The task will start in thumb mode. */
        *px_ଶୀର୍ଷ_Of_ଗଦା |= portTHUMB_MODE_BIT;
    }

    #ifdef __TI_VFP_SUPPORT__
    {
        px_ଶୀର୍ଷ_Of_ଗଦା--;

        /* The last thing on the stack is the tasks ulUsingFPU value, which by
        default is set to indicate that the stack frame does not include FPU
        registers. */
        *px_ଶୀର୍ଷ_Of_ଗଦା = pdFALSE;
    }
    #endif

    ଫେରନ୍ତୁ px_ଶୀର୍ଷ_Of_ଗଦା;
}
/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ prvSetupTimerInterrupt(ଶୂନ୍ୟ)
{
    /* Disable timer 0. */
    portRTI_GCTRL_REG &= 0xFFFFFFFEUL;

    /* Use the internal counter. */
    portRTI_TBCTRL_REG = 0x00000000U;

    /* COMPSEL0 will use the RTIFRC0 counter. */
    portRTI_COMPCTRL_REG = 0x00000000U;

    /* Initialise the counter and the prescale counter registers. */
    portRTI_CNT0_UC0_REG =  0x00000000U;
    portRTI_CNT0_FRC0_REG =  0x00000000U;

    /* Set Prescalar for RTI clock. */
    portRTI_CNT0_CPUC0_REG = 0x00000001U;
    portRTI_CNT0_COMP0_REG = ( configCPU_CLOCK_HZ / 2 ) / configTICK_RATE_HZ;
    portRTI_CNT0_UDCP0_REG = ( configCPU_CLOCK_HZ / 2 ) / configTICK_RATE_HZ;

    /* Clear interrupts. */
    portRTI_INTFLAG_REG =  0x0007000FU;
    portRTI_CLEARINTENA_REG = 0x00070F0FU;

    /* Enable the compare 0 interrupt. */
    portRTI_SETINTENA_REG = 0x00000001U;
    portRTI_GCTRL_REG |= 0x00000001U;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler(ଶୂନ୍ୟ)
{
    /* Start the timer that generates the tick ISR. */
    prvSetupTimerInterrupt();

    /* Reset the critical section nesting count read to execute the first task. */
    ulCriticalNesting = 0;

    /* Start the first task.  This is done from portASM.asm as ARM mode must be
    used. */
    vPortStartFirstTask();

    /* Should not get here! */
    ଫେରନ୍ତୁ pdFAIL;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ଶୂନ୍ୟ vPortEndScheduler(ଶୂନ୍ୟ)
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

#ଯଦି configUSE_PREEMPTION == 0

    /* The cooperative scheduler requires a normal IRQ service routine to
     * simply increment the system tick. */
    __interrupt ଶୂନ୍ୟ vPortNonPreemptiveTick( ଶୂନ୍ୟ )
    {
        /* clear clock interrupt flag */
        portRTI_INTFLAG_REG = 0x00000001;

        /* Increment the tick count - this may make a delaying task ready
        to run - but a context switch is not performed. */
        xTaskIncrementTick();
    }

 #ଅନ୍ୟଥା

    /*
     **************************************************************************
     * The preemptive scheduler ISR is written in assembler and can be found
     * in the portASM.asm file. This will only get used if portUSE_PREEMPTION
     * is set to 1 in portmacro.h
     **************************************************************************
     */
    ଶୂନ୍ୟ vPortPreemptiveTick( ଶୂନ୍ୟ );

#endif
/*-----------------------------------------------------------*/


/*
 * Disable interrupts, and keep a count of the nesting depth.
 */
ଶୂନ୍ୟ vPortEnterCritical( ଶୂନ୍ୟ )
{
    /* Disable interrupts as per portDISABLE_INTERRUPTS(); */
    portDISABLE_INTERRUPTS();

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
ଶୂନ୍ୟ vPortExitCritical( ଶୂନ୍ୟ )
{
    ଯଦି( ulCriticalNesting > 0 )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
        re-enabled. */
        ଯଦି( ulCriticalNesting == 0 )
        {
            /* Enable interrupts as per portENABLE_INTERRUPTS(). */
            portENABLE_INTERRUPTS();
        }
    }
}
/*-----------------------------------------------------------*/

#ଯଦି __TI_VFP_SUPPORT__

    ଶୂନ୍ୟ vPortTaskUsesFPU( ଶୂନ୍ୟ )
    {
    ବାହ୍ୟ ଶୂନ୍ୟ vPortInitialiseFPSCR( ଶୂନ୍ୟ );

        /* A task is registering the fact that it needs an FPU context.  Set the
        FPU flag (saved as part of the task context. */
        ulTaskHasFPUContext = pdTRUE;

        /* Initialise the floating point status register. */
        vPortInitialiseFPSCR();
    }

#endif /* __TI_VFP_SUPPORT__ */

/*-----------------------------------------------------------*/
