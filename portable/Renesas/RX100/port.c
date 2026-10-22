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
#अन्तर्भाव "limits.h"

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/* Library includes. */
#अन्तर्भाव "string.h"

/* Hardware specifics. */
#अन्तर्भाव "iodefine.h"

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
PSW is set with U and I set, and PM and IPL clear. */
#define portINITIAL_PSW     ( ( चळत_Type_t ) 0x00030000 )

/* The peripheral clock is divided by this value before being supplying the
CMT. */
#जर ( configUSE_TICKLESS_IDLE == 0 )
    /* If tickless idle is not used then the divisor can be fixed. */
    #define port_CLOCK_भाजक   8UL
#किंवाजर ( configPERIPHERAL_CLOCK_HZ >= 12000000 )
    #define port_CLOCK_भाजक   512UL
#किंवाजर ( configPERIPHERAL_CLOCK_HZ >= 6000000 )
    #define port_CLOCK_भाजक   128UL
#किंवाजर ( configPERIPHERAL_CLOCK_HZ >= 1000000 )
    #define port_CLOCK_भाजक   32UL
#अन्यथा
    #define port_CLOCK_भाजक   8UL
#endif


/* Keys required to lock and unlock access to certain system registers
respectively. */
#define port_UNLOCK_किल्ली      0xA50B
#define port_LOCK_किल्ली        0xA500

/*-----------------------------------------------------------*/

/* The following lines are to ensure vSoftwareInterruptEntry can be referenced,
 and therefore installed in the vector table, when the FreeRTOS code is built
as a library. */
बाह्य BaseType_t vSoftwareInterruptEntry;
स्थिरांक BaseType_t * p_vSoftwareInterruptEntry = &vSoftwareInterruptEntry;

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
स्थिर शून्य prvStartFirstTask( शून्य );

/*
 * Software interrupt handler.  Performs the actual context switch (saving and
 * restoring of registers).  Written in asm code as direct register access is
 * required.
 */
स्थिर शून्य prvYieldHandler( शून्य );

/*
 * The entry point for the software interrupt handler.  This is the function
 * that calls the inline asm function prvYieldHandler().  It is installed in
 * the vector table, but the code that installs it is in prvYieldHandler rather
 * than using a #pragma.
 */
शून्य vSoftwareInterruptISR( शून्य );

/*
 * Sets up the periodic ISR used for the RTOS tick using the CMT.
 * The application writer can define configSETUP_TICK_INTERRUPT() (in
 * FreeRTOSConfig.h) such that their own tick interrupt configuration is used
 * in place of prvSetupTimerInterrupt().
 */
स्थिर शून्य prvSetupTimerInterrupt( शून्य );
#ifndef configSETUP_TICK_INTERRUPT
    /* The user has not provided their own tick interrupt configuration so use
    the definition in this file (which uses the interval timer). */
    #define configSETUP_TICK_INTERRUPT() prvSetupTimerInterrupt()
#endif /* configSETUP_TICK_INTERRUPT */

/*
 * Called after the sleep mode registers have been configured, prvSleep()
 * executes the pre and post sleep macros, and actually calls the wait
 * instruction.
 */
#जर configUSE_TICKLESS_IDLE == 1
    स्थिर शून्य prvSleep( TickType_t xExpectedIdleTime );
#endif /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

/* These is accessed by the inline assembler functions. */
बाह्य शून्य *pxCurrentTCB;
बाह्य शून्य vTaskSwitchContext( शून्य );

/*-----------------------------------------------------------*/

/* Calculate how many clock increments make up a single tick period. */
स्थिर स्थिरांक uint32_t ul_Match_मूल्य_For_One_Tick = ( ( configPERIPHERAL_CLOCK_HZ / port_CLOCK_भाजक ) / configTICK_RATE_HZ );

#जर configUSE_TICKLESS_IDLE == 1

    /* Holds the maximum number of ticks that can be suppressed - which is
    basically how far into the future an interrupt can be generated. Set
    during initialisation.  This is the maximum possible value that the
    compare match register can hold divided by ulMatchValueForOneTick. */
    स्थिर स्थिरांक TickType_t xMaximumPossibleSuppressedTicks = अच_लघु_उच्च / ( ( configPERIPHERAL_CLOCK_HZ / port_CLOCK_भाजक ) / configTICK_RATE_HZ );

    /* Flag set from the tick interrupt to allow the sleep processing to know if
    sleep mode was exited because of a tick interrupt, or an interrupt
    generated by something else. */
    स्थिर अस्थिर uint32_t ulTickFlag = pdFALSE;

    /* The CMT counter is stopped temporarily each time it is re-programmed.
    The following constant offsets the CMT counter match value by the number of
    CMT counts that would typically be missed while the counter was stopped to
    compensate for the lost time.  The large difference between the divided CMT
    clock and the CPU clock means it is likely ulStoppedTimerCompensation will
    equal zero - and be optimised away. */
    स्थिर स्थिरांक uint32_t ulStoppedTimerCompensation = 100UL / ( configCPU_CLOCK_HZ / ( configPERIPHERAL_CLOCK_HZ / port_CLOCK_भाजक ) );

#endif

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
चळत_Type_t *px_Port_Initialise_चळत( चळत_Type_t *px_शीर्ष_Of_चळत, TaskFunction_t pxCode, शून्य *pvParameters )
{
    /* Offset to end up on 8 byte boundary. */
    px_शीर्ष_Of_चळत--;

    /* R0 is not included as it is the stack pointer. */
    *px_शीर्ष_Of_चळत = 0x00;
    px_शीर्ष_Of_चळत--;
    *px_शीर्ष_Of_चळत = 0x00;
    px_शीर्ष_Of_चळत--;
    *px_शीर्ष_Of_चळत = portINITIAL_PSW;
    px_शीर्ष_Of_चळत--;
    *px_शीर्ष_Of_चळत = ( चळत_Type_t ) pxCode;

    /* When debugging it can be useful if every register is set to a known
    value.  Otherwise code space can be saved by just setting the registers
    that need to be set. */
    #ifdef USE_FULL_REGISTER_INITIALISATION
    {
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0x12345678; /* r15. */
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0xaaaabbbb;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0xdddddddd;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0xcccccccc;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0xbbbbbbbb;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0xaaaaaaaa;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0x99999999;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0x88888888;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0x77777777;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0x66666666;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0x55555555;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0x44444444;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0x33333333;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0x22222222;
        px_शीर्ष_Of_चळत--;
    }
    #अन्यथा
    {
        /* Leave space for the registers that will get popped from the stack
        when the task first starts executing. */
        px_शीर्ष_Of_चळत -= 15;
    }
    #endif

    *px_शीर्ष_Of_चळत = ( चळत_Type_t ) pvParameters; /* R1 */
    px_शीर्ष_Of_चळत--;
    *px_शीर्ष_Of_चळत = 0x12345678; /* Accumulator. */
    px_शीर्ष_Of_चळत--;
    *px_शीर्ष_Of_चळत = 0x87654321; /* Accumulator. */

    परत px_शीर्ष_Of_चळत;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( शून्य )
{
    /* Use pxCurrentTCB just so it does not get optimised away. */
    जर( pxCurrentTCB != रिक्त )
    {
        /* Call an application function to set up the timer that will generate
        the tick interrupt.  This way the application can decide which
        peripheral to use.  If tickless mode is used then the default
        implementation defined in this file (which uses CMT0) should not be
        overridden. */
        configSETUP_TICK_INTERRUPT();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = configKERNEL_INTERRUPT_PRIORITY;

        /* Start the first task. */
        prvStartFirstTask();
    }

    /* Execution should not reach here as the tasks are now running!
    prvSetupTimerInterrupt() is called here to prevent the compiler outputting
    a warning about a statically declared function not being referenced in the
    case that the application writer has provided their own tick interrupt
    configuration routine (and defined configSETUP_TICK_INTERRUPT() such that
    their own routine will be called in place of prvSetupTimerInterrupt()). */
    prvSetupTimerInterrupt();

    /* Just to make sure the function is not optimised away. */
    ( शून्य ) vSoftwareInterruptISR();

    /* Should not get here. */
    परत pdFAIL;
}
/*-----------------------------------------------------------*/

#pragma inline_asm prvStartFirstTask
स्थिर शून्य prvStartFirstTask( शून्य )
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
    काढा_2     R15
    MVTACLO R15         /* Accumulator low 32 bits. */
    काढा_2     R15
    MVTACHI R15         /* Accumulator high 32 bits. */
    POPM    R1-R15      /* R1 to R15 - R0 is not included as it is the SP. */
    RTE                 /* This pops the remaining registers. */
    NOP
    NOP
}
/*-----------------------------------------------------------*/

#pragma interrupt ( prvTickISR( vect = _VECT( configTICK_VECTOR ), enable ) )
शून्य prvTickISR( शून्य )
{
    /* Increment the tick, and perform any processing the new tick value
    necessitates. */
    set_ipl( configMAX_SYSCALL_INTERRUPT_PRIORITY );
    {
        जर( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    set_ipl( configKERNEL_INTERRUPT_PRIORITY );

    #जर configUSE_TICKLESS_IDLE == 1
    {
        /* The CPU woke because of a tick. */
        ulTickFlag = pdTRUE;

        /* If this is the first tick since exiting tickless mode then the CMT
        compare match value needs resetting. */
        CMT0.CMCOR = ( uint16_t ) ul_Match_मूल्य_For_One_Tick;
    }
    #endif
}
/*-----------------------------------------------------------*/

शून्य vSoftwareInterruptISR( शून्य )
{
    prvYieldHandler();
}
/*-----------------------------------------------------------*/

#pragma inline_asm prvYieldHandler
स्थिर शून्य prvYieldHandler( शून्य )
{
    /* Re-enable interrupts. */
    SETPSW  I

    /* Move the data that was automatically pushed onto the interrupt stack
    when the interrupt occurred from the interrupt stack to the user stack.

    R15 is saved before it is clobbered. */
    ढकला_2.L  R15

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
    ADD #12, R0

    /* All the rest of the registers are saved directly to the user stack. */
    SETPSW  U

    /* Save the rest of the general registers (R15 has been saved already). */
    PUSHM   R1-R14

    /* Save the accumulator. */
    MVFACHI R15
    ढकला_2.L  R15
    MVFACMI R15 ; मधला order word.
    SHLL    #16, R15 ; Shifted डावा as it is restored to the खालचा_2 order word.
    ढकला_2.L  R15

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
    काढा_2     R15
    MVTACLO R15
    काढा_2     R15
    MVTACHI R15
    POPM    R1-R15
    RTE
    NOP
    NOP
}
/*-----------------------------------------------------------*/

शून्य vPortEndScheduler( शून्य )
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( pxCurrentTCB == रिक्त );

    /* The following line is just to prevent the symbol getting optimised away. */
    ( शून्य ) vTaskSwitchContext();
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvSetupTimerInterrupt( शून्य )
{
    /* Unlock. */
    SYSTEM.PRCR.WORD = port_UNLOCK_किल्ली;

    /* Enable CMT0. */
    MSTP( CMT0 ) = 0;

    /* Lock again. */
    SYSTEM.PRCR.WORD = port_LOCK_किल्ली;

    /* Interrupt on compare match. */
    CMT0.CMCR.BIT.CMIE = 1;

    /* Set the compare match value. */
    CMT0.CMCOR = ( uint16_t ) ul_Match_मूल्य_For_One_Tick;

    /* Divide the PCLK. */
    #जर port_CLOCK_भाजक == 512
    {
        CMT0.CMCR.BIT.CKS = 3;
    }
    #किंवाजर port_CLOCK_भाजक == 128
    {
        CMT0.CMCR.BIT.CKS = 2;
    }
    #किंवाजर port_CLOCK_भाजक == 32
    {
        CMT0.CMCR.BIT.CKS = 1;
    }
    #किंवाजर port_CLOCK_भाजक == 8
    {
        CMT0.CMCR.BIT.CKS = 0;
    }
    #अन्यथा
    {
        #error Invalid port_CLOCK_भाजक setting
    }
    #endif


    /* Enable the interrupt... */
    _IEN( _CMT0_CMI0 ) = 1;

    /* ...and set its priority to the application defined kernel priority. */
    _IPR( _CMT0_CMI0 ) = configKERNEL_INTERRUPT_PRIORITY;

    /* Start the timer. */
    CMT.CMSTR0.BIT.STR0 = 1;
}
/*-----------------------------------------------------------*/

#जर configUSE_TICKLESS_IDLE == 1

    स्थिर शून्य prvSleep( TickType_t xExpectedIdleTime )
    {
        /* Allow the application to define some pre-sleep processing. */
        configPRE_SLEEP_PROCESSING( xExpectedIdleTime );

        /* xExpectedIdleTime being set to 0 by configPRE_SLEEP_PROCESSING()
        means the application defined code has already executed the WAIT
        instruction. */
        जर( xExpectedIdleTime > 0 )
        {
            रुको();
        }

        /* Allow the application to define some post sleep processing. */
        configPOST_SLEEP_PROCESSING( xExpectedIdleTime );
    }

#endif /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

#जर configUSE_TICKLESS_IDLE == 1

    शून्य vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime )
    {
    uint32_t ul_Match_मूल्य, ulCompleteTickPeriods, ul_Current_मोजणी;
    eSleepModeStatus eSleepAction;

        /* THIS FUNCTION IS CALLED WITH THE SCHEDULER SUSPENDED. */

        /* Make sure the CMT reload value does not overflow the counter. */
        जर( xExpectedIdleTime > xMaximumPossibleSuppressedTicks )
        {
            xExpectedIdleTime = xMaximumPossibleSuppressedTicks;
        }

        /* Calculate the reload value required to wait xExpectedIdleTime tick
        periods. */
        ul_Match_मूल्य = ul_Match_मूल्य_For_One_Tick * xExpectedIdleTime;
        जर( ul_Match_मूल्य > ulStoppedTimerCompensation )
        {
            /* Compensate for the fact that the CMT is going to be stopped
            momentarily. */
            ul_Match_मूल्य -= ulStoppedTimerCompensation;
        }

        /* Stop the CMT momentarily.  The time the CMT is stopped for is
        accounted for as best it can be, but using the tickless mode will
        inevitably result in some tiny drift of the time maintained by the
        kernel with respect to calendar time. */
        CMT.CMSTR0.BIT.STR0 = 0;
        पर्यंत( CMT.CMSTR0.BIT.STR0 == 1 )
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
        eSleepAction = eTaskConfirmSleepModeStatus();
        जर( eSleepAction == eAbortSleep )
        {
            /* Restart tick. */
            CMT.CMSTR0.BIT.STR0 = 1;
            setpsw_i();
        }
        अन्यथा जर( eSleepAction == eNoTasksWaitingTimeout )
        {
            /* Protection off. */
            SYSTEM.PRCR.WORD = port_UNLOCK_किल्ली;

            /* Ready for software standby with all clocks stopped. */
            SYSTEM.SBYCR.BIT.SSBY = 1;

            /* Protection on. */
            SYSTEM.PRCR.WORD = port_LOCK_किल्ली;

            /* Sleep until something happens.  Calling prvSleep() will
            automatically reset the i bit in the PSW. */
            prvSleep( xExpectedIdleTime );

            /* Restart the CMT. */
            CMT.CMSTR0.BIT.STR0 = 1;
        }
        अन्यथा
        {
            /* Protection off. */
            SYSTEM.PRCR.WORD = port_UNLOCK_किल्ली;

            /* Ready for deep sleep mode. */
            SYSTEM.MSTPCRC.BIT.DSLPE = 1;
            SYSTEM.MSTPCRA.BIT.MSTPA28 = 1;
            SYSTEM.SBYCR.BIT.SSBY = 0;

            /* Protection on. */
            SYSTEM.PRCR.WORD = port_LOCK_किल्ली;

            /* Adjust the match value to take into account that the current
            time slice is already partially complete. */
            ul_Match_मूल्य -= ( uint32_t ) CMT0.CMCNT;
            CMT0.CMCOR = ( uint16_t ) ul_Match_मूल्य;

            /* Restart the CMT to count up to the new match value. */
            CMT0.CMCNT = 0;
            CMT.CMSTR0.BIT.STR0 = 1;

            /* Sleep until something happens.  Calling prvSleep() will
            automatically reset the i bit in the PSW. */
            prvSleep( xExpectedIdleTime );

            /* Stop CMT.  Again, the time the SysTick is stopped for is
            accounted for as best it can be, but using the tickless mode will
            inevitably result in some tiny drift of the time maintained by the
            kernel with respect to calendar time. */
            CMT.CMSTR0.BIT.STR0 = 0;
            पर्यंत( CMT.CMSTR0.BIT.STR0 == 1 )
            {
                /* Nothing to do here. */
            }

            ul_Current_मोजणी = ( uint32_t ) CMT0.CMCNT;

            जर( ulTickFlag != pdFALSE )
            {
                /* The tick interrupt has already executed, although because
                this function is called with the scheduler suspended the actual
                tick processing will not occur until after this function has
                exited.  Reset the match value with whatever remains of this
                tick period. */
                ul_Match_मूल्य = ul_Match_मूल्य_For_One_Tick - ul_Current_मोजणी;
                CMT0.CMCOR = ( uint16_t ) ul_Match_मूल्य;

                /* The tick interrupt handler will already have pended the tick
                processing in the kernel.  As the pending tick will be
                processed as soon as this function exits, the tick value
                maintained by the tick is stepped forward by one less than the
                time spent sleeping.  The actual stepping of the tick appears
                later in this function. */
                ulCompleteTickPeriods = xExpectedIdleTime - 1UL;
            }
            अन्यथा
            {
                /* Something other than the tick interrupt ended the sleep.
                How many complete tick periods passed while the processor was
                sleeping? */
                ulCompleteTickPeriods = ul_Current_मोजणी / ul_Match_मूल्य_For_One_Tick;

                /* The match value is set to whatever fraction of a single tick
                period remains. */
                ul_Match_मूल्य = ul_Current_मोजणी - ( ulCompleteTickPeriods * ul_Match_मूल्य_For_One_Tick );
                CMT0.CMCOR = ( uint16_t ) ul_Match_मूल्य;
            }

            /* Restart the CMT so it runs up to the match value.  The match value
            will get set to the value required to generate exactly one tick period
            the next time the CMT interrupt executes. */
            CMT0.CMCNT = 0;
            CMT.CMSTR0.BIT.STR0 = 1;

            /* Wind the tick forward by the number of tick periods that the CPU
            remained in a low power state. */
            vTaskStepTick( ulCompleteTickPeriods );
        }
    }

#endif /* configUSE_TICKLESS_IDLE */
