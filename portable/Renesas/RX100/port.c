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
 * Implementation of functions defined in portable.h for the RX100 port.
 *----------------------------------------------------------*/

/* Standard C includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "limits.h"

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

/* Library includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "string.h"

/* Hardware specifics. */
#ਅਨ੍ਤਰ੍ਭਾਵ "iodefine.h"

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
PSW is set with U and I set, and PM and IPL clear. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_PSW     ( ( ਢੇਰ_Type_t ) 0x00030000 )

/* The peripheral clock is divided by this value before being supplying the
CMT. */
#ਜੇ ( configUSE_TICKLESS_IDLE == 0 )
    /* If tickless idle is not used then the divisor can be fixed. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLOCK_ਭਾਜਕ   8UL
#ਜਾਂਜੇ ( configPERIPHERAL_CLOCK_HZ >= 12000000 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLOCK_ਭਾਜਕ   512UL
#ਜਾਂਜੇ ( configPERIPHERAL_CLOCK_HZ >= 6000000 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLOCK_ਭਾਜਕ   128UL
#ਜਾਂਜੇ ( configPERIPHERAL_CLOCK_HZ >= 1000000 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLOCK_ਭਾਜਕ   32UL
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLOCK_ਭਾਜਕ   8UL
#ਜੇ_ਅੰਤ


/* Keys required to lock and unlock access to certain system registers
respectively. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_UNLOCK_ਕੁੰਜੀ      0xA50B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਤਾਲਾ_ਕੁੰਜੀ        0xA500

/*-----------------------------------------------------------*/

/* The following lines are to ensure vSoftwareInterruptEntry can be referenced,
 and therefore installed in the vector table, when the FreeRTOS code is built
as a library. */
ਬਾਹਰੀ ਅਧਾਰ_Type_t v_Software_ਰੁਕਾਵਟ_ਇੰਦਰਾਜ;
ਅਚਲ ਅਧਾਰ_Type_t * p_v_Software_ਰੁਕਾਵਟ_ਇੰਦਰਾਜ = &v_Software_ਰੁਕਾਵਟ_ਇੰਦਰਾਜ;

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
ਸਥਿਰ ਖਾਲੀ prv_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task( ਖਾਲੀ );

/*
 * Software interrupt handler.  Performs the actual context switch (saving and
 * restoring of registers).  Written in asm code as direct register access is
 * required.
 */
ਸਥਿਰ ਖਾਲੀ prvYieldHandler( ਖਾਲੀ );

/*
 * The entry point for the software interrupt handler.  This is the function
 * that calls the inline asm function prvYieldHandler().  It is installed in
 * the vector table, but the code that installs it is in prvYieldHandler rather
 * than using a #pragma.
 */
ਖਾਲੀ v_Software_ਰੁਕਾਵਟ_ISR( ਖਾਲੀ );

/*
 * Sets up the periodic ISR used for the RTOS tick using the CMT.
 * The application writer can define configSETUP_TICK_INTERRUPT() (in
 * FreeRTOSConfig.h) such that their own tick interrupt configuration is used
 * in place of prvSetupTimerInterrupt().
 */
ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_ਤਿਆਰੀ_TICK_ਰੁਕਾਵਟ
    /* The user has not provided their own tick interrupt configuration so use
    the definition in this file (which uses the interval timer). */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_ਤਿਆਰੀ_TICK_ਰੁਕਾਵਟ() prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ()
#ਜੇ_ਅੰਤ /* configSETUP_TICK_INTERRUPT */

/*
 * Called after the sleep mode registers have been configured, prvSleep()
 * executes the pre and post sleep macros, and actually calls the wait
 * instruction.
 */
#ਜੇ configUSE_TICKLESS_IDLE == 1
    ਸਥਿਰ ਖਾਲੀ prvSleep( TickType_t x_Expected_Idle_ਸਮਾਂ );
#ਜੇ_ਅੰਤ /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

/* These is accessed by the inline assembler functions. */
ਬਾਹਰੀ ਖਾਲੀ *pxCurrentTCB;
ਬਾਹਰੀ ਖਾਲੀ vTaskSwitchContext( ਖਾਲੀ );

/*-----------------------------------------------------------*/

/* Calculate how many clock increments make up a single tick period. */
ਸਥਿਰ ਅਚਲ uint32_t ul_ਮੇਲ_ਮੁੱਲ_For_One_Tick = ( ( configPERIPHERAL_CLOCK_HZ / ਪੋਰਟ_CLOCK_ਭਾਜਕ ) / config_TICK_ਦਰ_HZ );

#ਜੇ configUSE_TICKLESS_IDLE == 1

    /* Holds the maximum number of ticks that can be suppressed - which is
    basically how far into the future an interrupt can be generated. Set
    during initialisation.  This is the maximum possible value that the
    compare match register can hold divided by ulMatchValueForOneTick. */
    ਸਥਿਰ ਅਚਲ TickType_t x_ਵੱਧ_ਤੋਂ_ਵੱਧ_Possible_Suppressed_Ticks = USHRT_MAX / ( ( configPERIPHERAL_CLOCK_HZ / ਪੋਰਟ_CLOCK_ਭਾਜਕ ) / config_TICK_ਦਰ_HZ );

    /* Flag set from the tick interrupt to allow the sleep processing to know if
    sleep mode was exited because of a tick interrupt, or an interrupt
    generated by something else. */
    ਸਥਿਰ ਅਸਥਿਰ uint32_t ulTickFlag = pdFALSE;

    /* The CMT counter is stopped temporarily each time it is re-programmed.
    The following constant offsets the CMT counter match value by the number of
    CMT counts that would typically be missed while the counter was stopped to
    compensate for the lost time.  The large difference between the divided CMT
    clock and the CPU clock means it is likely ulStoppedTimerCompensation will
    equal zero - and be optimised away. */
    ਸਥਿਰ ਅਚਲ uint32_t ulStoppedTimerCompensation = 100UL / ( configCPU_CLOCK_HZ / ( configPERIPHERAL_CLOCK_HZ / ਪੋਰਟ_CLOCK_ਭਾਜਕ ) );

#ਜੇ_ਅੰਤ

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਢੇਰ_Type_t *px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t *px_ਸਿਖਰ_ਦਾ_ਢੇਰ, TaskFunction_t px_ਕੋਡ, ਖਾਲੀ *pvParameters )
{
    /* Offset to end up on 8 byte boundary. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* R0 is not included as it is the stack pointer. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x00;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x00;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_PSW;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ;

    /* When debugging it can be useful if every register is set to a known
    value.  Otherwise code space can be saved by just setting the registers
    that need to be set. */
    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ USE_ਭਰਿਆ_ਰਜਿਸਟਰ_INITIALISATION
    {
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x12345678; /* r15. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0xaaaabbbb;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0xdddddddd;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0xcccccccc;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0xbbbbbbbb;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0xaaaaaaaa;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x99999999;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x88888888;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x77777777;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x66666666;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x55555555;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x44444444;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x33333333;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x22222222;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    }
    #ਨਹੀਂਤਾਂ
    {
        /* Leave space for the registers that will get popped from the stack
        when the task first starts executing. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 15;
    }
    #ਜੇ_ਅੰਤ

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters; /* R1 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x12345678; /* Accumulator. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x87654321; /* Accumulator. */

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    /* Use pxCurrentTCB just so it does not get optimised away. */
    ਜੇ( pxCurrentTCB != ਨਿਰਾ )
    {
        /* Call an application function to set up the timer that will generate
        the tick interrupt.  This way the application can decide which
        peripheral to use.  If tickless mode is used then the default
        implementation defined in this file (which uses CMT0) should not be
        overridden. */
        config_ਤਿਆਰੀ_TICK_ਰੁਕਾਵਟ();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = config_KERNEL_ਰੁਕਾਵਟ_ਤਰਜੀਹ;

        /* Start the first task. */
        prv_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();
    }

    /* Execution should not reach here as the tasks are now running!
    prvSetupTimerInterrupt() is called here to prevent the compiler outputting
    a warning about a statically declared function not being referenced in the
    case that the application writer has provided their own tick interrupt
    configuration routine (and defined configSETUP_TICK_INTERRUPT() such that
    their own routine will be called in place of prvSetupTimerInterrupt()). */
    prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

    /* Just to make sure the function is not optimised away. */
    ( ਖਾਲੀ ) v_Software_ਰੁਕਾਵਟ_ISR();

    /* Should not get here. */
    ਵਾਪਸ pdFAIL;
}
/*-----------------------------------------------------------*/

#ਹਦਾਇਤ inline_asm prv_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task
ਸਥਿਰ ਖਾਲੀ prv_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task( ਖਾਲੀ )
{
    /* When starting the scheduler there is nothing that needs moving to the
    interrupt stack because the function is not called from an interrupt.
    Just ensure the current stack is the user stack. */
    SETPSW  U

    /* Obtain the location of the stack associated with which ever task
    pxCurrentTCB is currently pointing to. */
    MOV.L   #_pxCurrentTCB, R15
    MOV.L   [R15], R15
    MOV.L   [R15], R0

    /* Restore the registers from the stack of the task pointed to by
    pxCurrentTCB. */
    ਕੱਢੋ_2     R15
    MVTACLO R15         /* Accumulator low 32 bits. */
    ਕੱਢੋ_2     R15
    MVTACHI R15         /* Accumulator high 32 bits. */
    POPM    R1-R15      /* R1 to R15 - R0 is not included as it is the SP. */
    RTE                 /* This pops the remaining registers. */
    NOP
    NOP
}
/*-----------------------------------------------------------*/

#ਹਦਾਇਤ ਰੁਕਾਵਟ ( prvTickISR( vect = _VECT( config_TICK_ਸਦਿਸ਼ ), enable ) )
ਖਾਲੀ prvTickISR( ਖਾਲੀ )
{
    /* Increment the tick, and perform any processing the new tick value
    necessitates. */
    ਸੈੱਟ_ipl( config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ );
    {
        ਜੇ( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    ਸੈੱਟ_ipl( config_KERNEL_ਰੁਕਾਵਟ_ਤਰਜੀਹ );

    #ਜੇ configUSE_TICKLESS_IDLE == 1
    {
        /* The CPU woke because of a tick. */
        ulTickFlag = pdTRUE;

        /* If this is the first tick since exiting tickless mode then the CMT
        compare match value needs resetting. */
        CMT0.CMCOR = ( uint16_t ) ul_ਮੇਲ_ਮੁੱਲ_For_One_Tick;
    }
    #ਜੇ_ਅੰਤ
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_Software_ਰੁਕਾਵਟ_ISR( ਖਾਲੀ )
{
    prvYieldHandler();
}
/*-----------------------------------------------------------*/

#ਹਦਾਇਤ inline_asm prvYieldHandler
ਸਥਿਰ ਖਾਲੀ prvYieldHandler( ਖਾਲੀ )
{
    /* Re-enable interrupts. */
    SETPSW  I

    /* Move the data that was automatically pushed onto the interrupt stack
    when the interrupt occurred from the interrupt stack to the user stack.

    R15 is saved before it is clobbered. */
    ਧੱਕੋ_2.L  R15

    /* Read the user stack pointer. */
    MVFC    USP, R15

    /* Move the address down to the data being moved. */
    SUB     #12, R15
    MVTC    R15, USP

    /* Copy the data across. */
    MOV.L   [ R0 ], [ R15 ] ; R15
    MOV.L   4[ R0 ], 4[ R15 ]  ; PC
    MOV.L   8[ R0 ], 8[ R15 ]  ; PSW

    /* Move the interrupt stack pointer to its new correct position. */
    ਜੋੜੋ_2 #12, R0

    /* All the rest of the registers are saved directly to the user stack. */
    SETPSW  U

    /* Save the rest of the general registers (R15 has been saved already). */
    PUSHM   R1-R14

    /* Save the accumulator. */
    MVFACHI R15
    ਧੱਕੋ_2.L  R15
    MVFACMI R15 ; ਵਿਚਕਾਰ ਕ੍ਰਮ ਸ਼ਬਦ_2.
    SHLL    #16, R15 ; Shifted ਖੱਬਾ as it is restored ਮੰਜ਼ਿਲ the ਨੀਵਾਂ_2 ਕ੍ਰਮ ਸ਼ਬਦ_2.
    ਧੱਕੋ_2.L  R15

    /* Save the stack pointer to the TCB. */
    MOV.L   #_pxCurrentTCB, R15
    MOV.L   [ R15 ], R15
    MOV.L   R0, [ R15 ]

    /* Ensure the interrupt mask is set to the syscall priority while the
    kernel structures are being accessed. */
    MVTIPL  #configMAX_SYSCALL_INTERRUPT_PRIORITY

    /* Select the next task to run. */
    BSR.A   _vTaskSwitchContext

    /* Reset the interrupt mask as no more data structure access is
    required. */
    MVTIPL  #configKERNEL_INTERRUPT_PRIORITY

    /* Load the stack pointer of the task that is now selected as the Running
    state task from its TCB. */
    MOV.L   #_pxCurrentTCB,R15
    MOV.L   [ R15 ], R15
    MOV.L   [ R15 ], R0

    /* Restore the context of the new task.  The PSW (Program Status Word) and
    PC will be popped by the RTE instruction. */
    ਕੱਢੋ_2     R15
    MVTACLO R15
    ਕੱਢੋ_2     R15
    MVTACHI R15
    POPM    R1-R15
    RTE
    NOP
    NOP
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( pxCurrentTCB == ਨਿਰਾ );

    /* The following line is just to prevent the symbol getting optimised away. */
    ( ਖਾਲੀ ) vTaskSwitchContext();
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    /* Unlock. */
    SYSTEM.PRCR.ਸ਼ਬਦ_4 = ਪੋਰਟ_UNLOCK_ਕੁੰਜੀ;

    /* Enable CMT0. */
    MSTP( CMT0 ) = 0;

    /* Lock again. */
    SYSTEM.PRCR.ਸ਼ਬਦ_4 = ਪੋਰਟ_ਤਾਲਾ_ਕੁੰਜੀ;

    /* Interrupt on compare match. */
    CMT0.CMCR.ਦੋਆਧਾਰੀ_ਅੰਕ_3.CMIE = 1;

    /* Set the compare match value. */
    CMT0.CMCOR = ( uint16_t ) ul_ਮੇਲ_ਮੁੱਲ_For_One_Tick;

    /* Divide the PCLK. */
    #ਜੇ ਪੋਰਟ_CLOCK_ਭਾਜਕ == 512
    {
        CMT0.CMCR.ਦੋਆਧਾਰੀ_ਅੰਕ_3.CKS = 3;
    }
    #ਜਾਂਜੇ ਪੋਰਟ_CLOCK_ਭਾਜਕ == 128
    {
        CMT0.CMCR.ਦੋਆਧਾਰੀ_ਅੰਕ_3.CKS = 2;
    }
    #ਜਾਂਜੇ ਪੋਰਟ_CLOCK_ਭਾਜਕ == 32
    {
        CMT0.CMCR.ਦੋਆਧਾਰੀ_ਅੰਕ_3.CKS = 1;
    }
    #ਜਾਂਜੇ ਪੋਰਟ_CLOCK_ਭਾਜਕ == 8
    {
        CMT0.CMCR.ਦੋਆਧਾਰੀ_ਅੰਕ_3.CKS = 0;
    }
    #ਨਹੀਂਤਾਂ
    {
        #ਗਲਤੀ Invalid ਪੋਰਟ_CLOCK_ਭਾਜਕ setting
    }
    #ਜੇ_ਅੰਤ


    /* Enable the interrupt... */
    _IEN( _CMT0_CMI0 ) = 1;

    /* ...and set its priority to the application defined kernel priority. */
    _IPR( _CMT0_CMI0 ) = config_KERNEL_ਰੁਕਾਵਟ_ਤਰਜੀਹ;

    /* Start the timer. */
    CMT.CMSTR0.ਦੋਆਧਾਰੀ_ਅੰਕ_3.STR0 = 1;
}
/*-----------------------------------------------------------*/

#ਜੇ configUSE_TICKLESS_IDLE == 1

    ਸਥਿਰ ਖਾਲੀ prvSleep( TickType_t x_Expected_Idle_ਸਮਾਂ )
    {
        /* Allow the application to define some pre-sleep processing. */
        configPRE_SLEEP_PROCESSING( x_Expected_Idle_ਸਮਾਂ );

        /* xExpectedIdleTime being set to 0 by configPRE_SLEEP_PROCESSING()
        means the application defined code has already executed the WAIT
        instruction. */
        ਜੇ( x_Expected_Idle_ਸਮਾਂ > 0 )
        {
            wait();
        }

        /* Allow the application to define some post sleep processing. */
        configPOST_SLEEP_PROCESSING( x_Expected_Idle_ਸਮਾਂ );
    }

#ਜੇ_ਅੰਤ /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

#ਜੇ configUSE_TICKLESS_IDLE == 1

    ਖਾਲੀ v_ਪੋਰਟ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ਸਮਾਂ )
    {
    uint32_t ul_ਮੇਲ_ਮੁੱਲ, ulCompleteTickPeriods, ul_Current_ਗਿਣਤੀ;
    e_Sleep_ਬਹੁਲਕ_ਸਥਿਤੀ eSleepAction;

        /* THIS FUNCTION IS CALLED WITH THE SCHEDULER SUSPENDED. */

        /* Make sure the CMT reload value does not overflow the counter. */
        ਜੇ( x_Expected_Idle_ਸਮਾਂ > x_ਵੱਧ_ਤੋਂ_ਵੱਧ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_ਸਮਾਂ = x_ਵੱਧ_ਤੋਂ_ਵੱਧ_Possible_Suppressed_Ticks;
        }

        /* Calculate the reload value required to wait xExpectedIdleTime tick
        periods. */
        ul_ਮੇਲ_ਮੁੱਲ = ul_ਮੇਲ_ਮੁੱਲ_For_One_Tick * x_Expected_Idle_ਸਮਾਂ;
        ਜੇ( ul_ਮੇਲ_ਮੁੱਲ > ulStoppedTimerCompensation )
        {
            /* Compensate for the fact that the CMT is going to be stopped
            momentarily. */
            ul_ਮੇਲ_ਮੁੱਲ -= ulStoppedTimerCompensation;
        }

        /* Stop the CMT momentarily.  The time the CMT is stopped for is
        accounted for as best it can be, but using the tickless mode will
        inevitably result in some tiny drift of the time maintained by the
        kernel with respect to calendar time. */
        CMT.CMSTR0.ਦੋਆਧਾਰੀ_ਅੰਕ_3.STR0 = 0;
        ਜਦੋਂ( CMT.CMSTR0.ਦੋਆਧਾਰੀ_ਅੰਕ_3.STR0 == 1 )
        {
            /* Nothing to do here. */
        }

        /* Critical section using the global interrupt bit as the i bit is
        automatically reset by the WAIT instruction. */
        clrpsw_i();

        /* The tick flag is set to false before sleeping.  If it is true when
        sleep mode is exited then sleep mode was probably exited because the
        tick was suppressed for the entire xExpectedIdleTime period. */
        ulTickFlag = pdFALSE;

        /* If a context switch is pending then abandon the low power entry as
        the context switch might have been pended by an external interrupt that
        requires processing. */
        eSleepAction = e_Task_Confirm_Sleep_ਬਹੁਲਕ_ਸਥਿਤੀ();
        ਜੇ( eSleepAction == eAbortSleep )
        {
            /* Restart tick. */
            CMT.CMSTR0.ਦੋਆਧਾਰੀ_ਅੰਕ_3.STR0 = 1;
            setpsw_i();
        }
        ਨਹੀਂਤਾਂ ਜੇ( eSleepAction == e_No_Tasks_ਉਡੀਕ_Timeout )
        {
            /* Protection off. */
            SYSTEM.PRCR.ਸ਼ਬਦ_4 = ਪੋਰਟ_UNLOCK_ਕੁੰਜੀ;

            /* Ready for software standby with all clocks stopped. */
            SYSTEM.SBYCR.ਦੋਆਧਾਰੀ_ਅੰਕ_3.SSBY = 1;

            /* Protection on. */
            SYSTEM.PRCR.ਸ਼ਬਦ_4 = ਪੋਰਟ_ਤਾਲਾ_ਕੁੰਜੀ;

            /* Sleep until something happens.  Calling prvSleep() will
            automatically reset the i bit in the PSW. */
            prvSleep( x_Expected_Idle_ਸਮਾਂ );

            /* Restart the CMT. */
            CMT.CMSTR0.ਦੋਆਧਾਰੀ_ਅੰਕ_3.STR0 = 1;
        }
        ਨਹੀਂਤਾਂ
        {
            /* Protection off. */
            SYSTEM.PRCR.ਸ਼ਬਦ_4 = ਪੋਰਟ_UNLOCK_ਕੁੰਜੀ;

            /* Ready for deep sleep mode. */
            SYSTEM.MSTPCRC.ਦੋਆਧਾਰੀ_ਅੰਕ_3.DSLPE = 1;
            SYSTEM.MSTPCRA.ਦੋਆਧਾਰੀ_ਅੰਕ_3.MSTPA28 = 1;
            SYSTEM.SBYCR.ਦੋਆਧਾਰੀ_ਅੰਕ_3.SSBY = 0;

            /* Protection on. */
            SYSTEM.PRCR.ਸ਼ਬਦ_4 = ਪੋਰਟ_ਤਾਲਾ_ਕੁੰਜੀ;

            /* Adjust the match value to take into account that the current
            time slice is already partially complete. */
            ul_ਮੇਲ_ਮੁੱਲ -= ( uint32_t ) CMT0.CMCNT;
            CMT0.CMCOR = ( uint16_t ) ul_ਮੇਲ_ਮੁੱਲ;

            /* Restart the CMT to count up to the new match value. */
            CMT0.CMCNT = 0;
            CMT.CMSTR0.ਦੋਆਧਾਰੀ_ਅੰਕ_3.STR0 = 1;

            /* Sleep until something happens.  Calling prvSleep() will
            automatically reset the i bit in the PSW. */
            prvSleep( x_Expected_Idle_ਸਮਾਂ );

            /* Stop CMT.  Again, the time the SysTick is stopped for is
            accounted for as best it can be, but using the tickless mode will
            inevitably result in some tiny drift of the time maintained by the
            kernel with respect to calendar time. */
            CMT.CMSTR0.ਦੋਆਧਾਰੀ_ਅੰਕ_3.STR0 = 0;
            ਜਦੋਂ( CMT.CMSTR0.ਦੋਆਧਾਰੀ_ਅੰਕ_3.STR0 == 1 )
            {
                /* Nothing to do here. */
            }

            ul_Current_ਗਿਣਤੀ = ( uint32_t ) CMT0.CMCNT;

            ਜੇ( ulTickFlag != pdFALSE )
            {
                /* The tick interrupt has already executed, although because
                this function is called with the scheduler suspended the actual
                tick processing will not occur until after this function has
                exited.  Reset the match value with whatever remains of this
                tick period. */
                ul_ਮੇਲ_ਮੁੱਲ = ul_ਮੇਲ_ਮੁੱਲ_For_One_Tick - ul_Current_ਗਿਣਤੀ;
                CMT0.CMCOR = ( uint16_t ) ul_ਮੇਲ_ਮੁੱਲ;

                /* The tick interrupt handler will already have pended the tick
                processing in the kernel.  As the pending tick will be
                processed as soon as this function exits, the tick value
                maintained by the tick is stepped forward by one less than the
                time spent sleeping.  The actual stepping of the tick appears
                later in this function. */
                ulCompleteTickPeriods = x_Expected_Idle_ਸਮਾਂ - 1UL;
            }
            ਨਹੀਂਤਾਂ
            {
                /* Something other than the tick interrupt ended the sleep.
                How many complete tick periods passed while the processor was
                sleeping? */
                ulCompleteTickPeriods = ul_Current_ਗਿਣਤੀ / ul_ਮੇਲ_ਮੁੱਲ_For_One_Tick;

                /* The match value is set to whatever fraction of a single tick
                period remains. */
                ul_ਮੇਲ_ਮੁੱਲ = ul_Current_ਗਿਣਤੀ - ( ulCompleteTickPeriods * ul_ਮੇਲ_ਮੁੱਲ_For_One_Tick );
                CMT0.CMCOR = ( uint16_t ) ul_ਮੇਲ_ਮੁੱਲ;
            }

            /* Restart the CMT so it runs up to the match value.  The match value
            will get set to the value required to generate exactly one tick period
            the next time the CMT interrupt executes. */
            CMT0.CMCNT = 0;
            CMT.CMSTR0.ਦੋਆਧਾਰੀ_ਅੰਕ_3.STR0 = 1;

            /* Wind the tick forward by the number of tick periods that the CPU
            remained in a low power state. */
            v_Task_ਕਦਮ_Tick( ulCompleteTickPeriods );
        }
    }

#ਜੇ_ਅੰਤ /* configUSE_TICKLESS_IDLE */
