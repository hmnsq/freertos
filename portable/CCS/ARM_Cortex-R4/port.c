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
#وصف_ڪريو پورٽ_RTI_GCTRL_REG       ( * ( ( متطاير uint32_t * ) 0xFFFFFC00 ) )
#وصف_ڪريو پورٽ_RTI_TBCTRL_REG      ( * ( ( متطاير uint32_t * ) 0xFFFFFC04 ) )
#وصف_ڪريو پورٽ_RTI_COMPCTRL_REG    ( * ( ( متطاير uint32_t * ) 0xFFFFFC0C ) )
#وصف_ڪريو پورٽ_RTI_CNT0_FRC0_REG   ( * ( ( متطاير uint32_t * ) 0xFFFFFC10 ) )
#وصف_ڪريو پورٽ_RTI_CNT0_UC0_REG    ( * ( ( متطاير uint32_t * ) 0xFFFFFC14 ) )
#وصف_ڪريو پورٽ_RTI_CNT0_CPUC0_REG  ( * ( ( متطاير uint32_t * ) 0xFFFFFC18 ) )
#وصف_ڪريو پورٽ_RTI_CNT0_COMP0_REG  ( * ( ( متطاير uint32_t * ) 0xFFFFFC50 ) )
#وصف_ڪريو پورٽ_RTI_CNT0_UDCP0_REG  ( * ( ( متطاير uint32_t * ) 0xFFFFFC54 ) )
#وصف_ڪريو پورٽ_RTI_SETINTENA_REG   ( * ( ( متطاير uint32_t * ) 0xFFFFFC80 ) )
#وصف_ڪريو پورٽ_RTI_CLEARINTENA_REG ( * ( ( متطاير uint32_t * ) 0xFFFFFC84 ) )
#وصف_ڪريو پورٽ_RTI_INTFLAG_REG     ( * ( ( متطاير uint32_t * ) 0xFFFFFC88 ) )


/* Constants required to set up the initial stack of each task. */
#وصف_ڪريو پورٽ_INITIAL_SPSR        ( ( ڍير_Type_t ) 0x1F )
#وصف_ڪريو پورٽ_INITIAL_FPSCR       ( ( ڍير_Type_t ) 0x00 )
#وصف_ڪريو پورٽ_INSTRUCTION_سائيز    ( ( ڍير_Type_t ) 0x04 )
#وصف_ڪريو پورٽ_THUMB_گهڻائي_ٻٽو_انگ      ( ( ڍير_Type_t ) 0x20 )

/* The number of words on the stack frame between the saved Top Of Stack and
R0 (in which the parameters are passed. */
#وصف_ڪريو پورٽ_SPACE_BETWEEN_TOS_AND_PARAMETERS    ( 12 )

/*-----------------------------------------------------------*/

/* vPortStartFirstSTask() is defined in portASM.asm */
خارجي فراغ v_پورٽ_شروعات_پهريون_Task( فراغ );

/*-----------------------------------------------------------*/

/* Saved as part of the task context.  Set to pdFALSE if the task does not
require an FPU context. */
uint32_t ulTaskHasFPUContext = 0;

/*-----------------------------------------------------------*/


/*
 * See header file for description.
 */
ڍير_Type_t *px_پورٽ_Initialise_ڍير( ڍير_Type_t *px_چوٽي_جو_ڍير, TaskFunction_t px_ڪوڊ, فراغ *pvParameters )
{
ڍير_Type_t *pxOriginalTOS;

    pxOriginalTOS = px_چوٽي_جو_ڍير;

    #إذا __TI_VFP_SUPPORT__
    {
        /* Ensure the stack is correctly aligned on exit. */
        px_چوٽي_جو_ڍير--;
    }
    #جيڪڏهن_پورو

    /* Setup the initial stack of the task.  The stack is set exactly as
    expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which is the start of the as
    the task has not executed yet.  The offset is added to make the return
    address appear as it would within an IRQ ISR. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) px_ڪوڊ + پورٽ_INSTRUCTION_سائيز;
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x00000000; /* R14 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_چوٽي_جو_ڍير--;

    #جيڪڏهن_وصف_ٿيل پورٽ_PRELOAD_TASK_REGISTERS
    {
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x12121212; /* R12 */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x11111111; /* R11 */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x10101010; /* R10 */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x09090909; /* R9 */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x08080808; /* R8 */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x07070707; /* R7 */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x06060606; /* R6 */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x05050505; /* R5 */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x04040404; /* R4 */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x03030303; /* R3 */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x02020202; /* R2 */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x01010101; /* R1 */
        px_چوٽي_جو_ڍير--;
    }
    #وإلا
    {
        px_چوٽي_جو_ڍير -= پورٽ_SPACE_BETWEEN_TOS_AND_PARAMETERS;
    }
    #جيڪڏهن_پورو

    /* Function parameters are passed in R0. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pvParameters; /* R0 */
    px_چوٽي_جو_ڍير--;

    /* Set the status register for system mode, with interrupts enabled. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ( ( _get_CPSR() & ~0xFF ) | پورٽ_INITIAL_SPSR );

    إذا( ( ( uint32_t ) px_ڪوڊ & 0x01UL ) != 0x00 )
    {
        /* The task will start in thumb mode. */
        *px_چوٽي_جو_ڍير |= پورٽ_THUMB_گهڻائي_ٻٽو_انگ;
    }

    #جيڪڏهن_وصف_ٿيل __TI_VFP_SUPPORT__
    {
        px_چوٽي_جو_ڍير--;

        /* The last thing on the stack is the tasks ulUsingFPU value, which by
        default is set to indicate that the stack frame does not include FPU
        registers. */
        *px_چوٽي_جو_ڍير = pdFALSE;
    }
    #جيڪڏهن_پورو

    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_تياري_Timer_مداخلت(فراغ)
{
    /* Disable timer 0. */
    پورٽ_RTI_GCTRL_REG &= 0xFFFFFFFEUL;

    /* Use the internal counter. */
    پورٽ_RTI_TBCTRL_REG = 0x00000000U;

    /* COMPSEL0 will use the RTIFRC0 counter. */
    پورٽ_RTI_COMPCTRL_REG = 0x00000000U;

    /* Initialise the counter and the prescale counter registers. */
    پورٽ_RTI_CNT0_UC0_REG =  0x00000000U;
    پورٽ_RTI_CNT0_FRC0_REG =  0x00000000U;

    /* Set Prescalar for RTI clock. */
    پورٽ_RTI_CNT0_CPUC0_REG = 0x00000001U;
    پورٽ_RTI_CNT0_COMP0_REG = ( configCPU_CLOCK_HZ / 2 ) / config_TICK_شرح_HZ;
    پورٽ_RTI_CNT0_UDCP0_REG = ( configCPU_CLOCK_HZ / 2 ) / config_TICK_شرح_HZ;

    /* Clear interrupts. */
    پورٽ_RTI_INTFLAG_REG =  0x0007000FU;
    پورٽ_RTI_CLEARINTENA_REG = 0x00070F0FU;

    /* Enable the compare 0 interrupt. */
    پورٽ_RTI_SETINTENA_REG = 0x00000001U;
    پورٽ_RTI_GCTRL_REG |= 0x00000001U;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
بنياد_Type_t x_پورٽ_شروعات_Scheduler(فراغ)
{
    /* Start the timer that generates the tick ISR. */
    prv_تياري_Timer_مداخلت();

    /* Reset the critical section nesting count read to execute the first task. */
    ulCriticalNesting = 0;

    /* Start the first task.  This is done from portASM.asm as ARM mode must be
    used. */
    v_پورٽ_شروعات_پهريون_Task();

    /* Should not get here! */
    أرجع pdFAIL;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
فراغ v_پورٽ_پڇاڙي_Scheduler(فراغ)
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

#إذا configUSE_PREEMPTION == 0

    /* The cooperative scheduler requires a normal IRQ service routine to
     * simply increment the system tick. */
    __interrupt فراغ v_پورٽ_Non_Preemptive_Tick( فراغ )
    {
        /* clear clock interrupt flag */
        پورٽ_RTI_INTFLAG_REG = 0x00000001;

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
    فراغ v_پورٽ_Preemptive_Tick( فراغ );

#جيڪڏهن_پورو
/*-----------------------------------------------------------*/


/*
 * Disable interrupts, and keep a count of the nesting depth.
 */
فراغ v_پورٽ_Enter_Critical( فراغ )
{
    /* Disable interrupts as per portDISABLE_INTERRUPTS(); */
    پورٽ_DISABLE_INTERRUPTS();

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
فراغ v_پورٽ_Exit_Critical( فراغ )
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
            پورٽ_ENABLE_INTERRUPTS();
        }
    }
}
/*-----------------------------------------------------------*/

#إذا __TI_VFP_SUPPORT__

    فراغ v_پورٽ_Task_استعمال_ڪري_FPU( فراغ )
    {
    خارجي فراغ v_پورٽ_Initialise_FPSCR( فراغ );

        /* A task is registering the fact that it needs an FPU context.  Set the
        FPU flag (saved as part of the task context. */
        ulTaskHasFPUContext = pdTRUE;

        /* Initialise the floating point status register. */
        v_پورٽ_Initialise_FPSCR();
    }

#جيڪڏهن_پورو /* __TI_VFP_SUPPORT__ */

/*-----------------------------------------------------------*/
