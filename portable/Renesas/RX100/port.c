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
#شامل "limits.h"

/* Scheduler includes. */
#شامل "FreeRTOS.h"
#شامل "task.h"

/* Library includes. */
#شامل "string.h"

/* Hardware specifics. */
#شامل "iodefine.h"

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
PSW is set with U and I set, and PM and IPL clear. */
#تعریف_کرو پورٹ_INITIAL_PSW     ( ( ڈھیر_Type_t ) 0x00030000 )

/* The peripheral clock is divided by this value before being supplying the
CMT. */
#اگر ( configUSE_TICKLESS_IDLE == 0 )
    /* If tickless idle is not used then the divisor can be fixed. */
    #تعریف_کرو پورٹ_CLOCK_مقسوم_علیہ   8UL
#وگرنہ_اگر ( configPERIPHERAL_CLOCK_HZ >= 12000000 )
    #تعریف_کرو پورٹ_CLOCK_مقسوم_علیہ   512UL
#وگرنہ_اگر ( configPERIPHERAL_CLOCK_HZ >= 6000000 )
    #تعریف_کرو پورٹ_CLOCK_مقسوم_علیہ   128UL
#وگرنہ_اگر ( configPERIPHERAL_CLOCK_HZ >= 1000000 )
    #تعریف_کرو پورٹ_CLOCK_مقسوم_علیہ   32UL
#ورنہ
    #تعریف_کرو پورٹ_CLOCK_مقسوم_علیہ   8UL
#اگر_ختم


/* Keys required to lock and unlock access to certain system registers
respectively. */
#تعریف_کرو پورٹ_UNLOCK_کلید      0xA50B
#تعریف_کرو پورٹ_تالا_کلید        0xA500

/*-----------------------------------------------------------*/

/* The following lines are to ensure vSoftwareInterruptEntry can be referenced,
 and therefore installed in the vector table, when the FreeRTOS code is built
as a library. */
خارجی بنیاد_Type_t v_Software_مداخلت_اندراج;
ثابت بنیاد_Type_t * p_v_Software_مداخلت_اندراج = &v_Software_مداخلت_اندراج;

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
ساکن خالی prv_آغاز_پہلا_Task( خالی );

/*
 * Software interrupt handler.  Performs the actual context switch (saving and
 * restoring of registers).  Written in asm code as direct register access is
 * required.
 */
ساکن خالی prvYieldHandler( خالی );

/*
 * The entry point for the software interrupt handler.  This is the function
 * that calls the inline asm function prvYieldHandler().  It is installed in
 * the vector table, but the code that installs it is in prvYieldHandler rather
 * than using a #pragma.
 */
خالی v_Software_مداخلت_ISR( خالی );

/*
 * Sets up the periodic ISR used for the RTOS tick using the CMT.
 * The application writer can define configSETUP_TICK_INTERRUPT() (in
 * FreeRTOSConfig.h) such that their own tick interrupt configuration is used
 * in place of prvSetupTimerInterrupt().
 */
ساکن خالی prv_تیاری_Timer_مداخلت( خالی );
#اگر_غیر_تعریف_شدہ config_تیاری_TICK_مداخلت
    /* The user has not provided their own tick interrupt configuration so use
    the definition in this file (which uses the interval timer). */
    #تعریف_کرو config_تیاری_TICK_مداخلت() prv_تیاری_Timer_مداخلت()
#اگر_ختم /* configSETUP_TICK_INTERRUPT */

/*
 * Called after the sleep mode registers have been configured, prvSleep()
 * executes the pre and post sleep macros, and actually calls the wait
 * instruction.
 */
#اگر configUSE_TICKLESS_IDLE == 1
    ساکن خالی prvSleep( TickType_t x_Expected_Idle_وقت );
#اگر_ختم /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

/* These is accessed by the inline assembler functions. */
خارجی خالی *pxCurrentTCB;
خارجی خالی vTaskSwitchContext( خالی );

/*-----------------------------------------------------------*/

/* Calculate how many clock increments make up a single tick period. */
ساکن ثابت uint32_t ul_مطابقت_قدر_For_One_Tick = ( ( configPERIPHERAL_CLOCK_HZ / پورٹ_CLOCK_مقسوم_علیہ ) / config_TICK_شرح_HZ );

#اگر configUSE_TICKLESS_IDLE == 1

    /* Holds the maximum number of ticks that can be suppressed - which is
    basically how far into the future an interrupt can be generated. Set
    during initialisation.  This is the maximum possible value that the
    compare match register can hold divided by ulMatchValueForOneTick. */
    ساکن ثابت TickType_t x_زیادہ_سے_زیادہ_Possible_Suppressed_Ticks = USHRT_MAX / ( ( configPERIPHERAL_CLOCK_HZ / پورٹ_CLOCK_مقسوم_علیہ ) / config_TICK_شرح_HZ );

    /* Flag set from the tick interrupt to allow the sleep processing to know if
    sleep mode was exited because of a tick interrupt, or an interrupt
    generated by something else. */
    ساکن متلون uint32_t ulTickFlag = pdFALSE;

    /* The CMT counter is stopped temporarily each time it is re-programmed.
    The following constant offsets the CMT counter match value by the number of
    CMT counts that would typically be missed while the counter was stopped to
    compensate for the lost time.  The large difference between the divided CMT
    clock and the CPU clock means it is likely ulStoppedTimerCompensation will
    equal zero - and be optimised away. */
    ساکن ثابت uint32_t ulStoppedTimerCompensation = 100UL / ( configCPU_CLOCK_HZ / ( configPERIPHERAL_CLOCK_HZ / پورٹ_CLOCK_مقسوم_علیہ ) );

#اگر_ختم

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t *px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t *px_چوٹی_کا_ڈھیر, TaskFunction_t px_رمز, خالی *pvParameters )
{
    /* Offset to end up on 8 byte boundary. */
    px_چوٹی_کا_ڈھیر--;

    /* R0 is not included as it is the stack pointer. */
    *px_چوٹی_کا_ڈھیر = 0x00;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x00;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = پورٹ_INITIAL_PSW;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) px_رمز;

    /* When debugging it can be useful if every register is set to a known
    value.  Otherwise code space can be saved by just setting the registers
    that need to be set. */
    #اگر_تعریف_شدہ USE_بھرا_رجسٹر_INITIALISATION
    {
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x12345678; /* r15. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0xaaaabbbb;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0xdddddddd;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0xcccccccc;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0xbbbbbbbb;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0xaaaaaaaa;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x99999999;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x88888888;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x77777777;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x66666666;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x55555555;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x44444444;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x33333333;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x22222222;
        px_چوٹی_کا_ڈھیر--;
    }
    #ورنہ
    {
        /* Leave space for the registers that will get popped from the stack
        when the task first starts executing. */
        px_چوٹی_کا_ڈھیر -= 15;
    }
    #اگر_ختم

    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) pvParameters; /* R1 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x12345678; /* Accumulator. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x87654321; /* Accumulator. */

    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    /* Use pxCurrentTCB just so it does not get optimised away. */
    اگر( pxCurrentTCB != تہی )
    {
        /* Call an application function to set up the timer that will generate
        the tick interrupt.  This way the application can decide which
        peripheral to use.  If tickless mode is used then the default
        implementation defined in this file (which uses CMT0) should not be
        overridden. */
        config_تیاری_TICK_مداخلت();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = config_KERNEL_مداخلت_ترجیح;

        /* Start the first task. */
        prv_آغاز_پہلا_Task();
    }

    /* Execution should not reach here as the tasks are now running!
    prvSetupTimerInterrupt() is called here to prevent the compiler outputting
    a warning about a statically declared function not being referenced in the
    case that the application writer has provided their own tick interrupt
    configuration routine (and defined configSETUP_TICK_INTERRUPT() such that
    their own routine will be called in place of prvSetupTimerInterrupt()). */
    prv_تیاری_Timer_مداخلت();

    /* Just to make sure the function is not optimised away. */
    ( خالی ) v_Software_مداخلت_ISR();

    /* Should not get here. */
    واپس pdFAIL;
}
/*-----------------------------------------------------------*/

#ہدایت inline_asm prv_آغاز_پہلا_Task
ساکن خالی prv_آغاز_پہلا_Task( خالی )
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
    نکالو_2     R15
    MVTACLO R15         /* Accumulator low 32 bits. */
    نکالو_2     R15
    MVTACHI R15         /* Accumulator high 32 bits. */
    POPM    R1-R15      /* R1 to R15 - R0 is not included as it is the SP. */
    RTE                 /* This pops the remaining registers. */
    NOP
    NOP
}
/*-----------------------------------------------------------*/

#ہدایت مداخلت ( prvTickISR( vect = _VECT( config_TICK_سمتیہ ), enable ) )
خالی prvTickISR( خالی )
{
    /* Increment the tick, and perform any processing the new tick value
    necessitates. */
    سیٹ_ipl( config_MAX_SYSCALL_مداخلت_ترجیح );
    {
        اگر( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    سیٹ_ipl( config_KERNEL_مداخلت_ترجیح );

    #اگر configUSE_TICKLESS_IDLE == 1
    {
        /* The CPU woke because of a tick. */
        ulTickFlag = pdTRUE;

        /* If this is the first tick since exiting tickless mode then the CMT
        compare match value needs resetting. */
        CMT0.CMCOR = ( uint16_t ) ul_مطابقت_قدر_For_One_Tick;
    }
    #اگر_ختم
}
/*-----------------------------------------------------------*/

خالی v_Software_مداخلت_ISR( خالی )
{
    prvYieldHandler();
}
/*-----------------------------------------------------------*/

#ہدایت inline_asm prvYieldHandler
ساکن خالی prvYieldHandler( خالی )
{
    /* Re-enable interrupts. */
    SETPSW  I

    /* Move the data that was automatically pushed onto the interrupt stack
    when the interrupt occurred from the interrupt stack to the user stack.

    R15 is saved before it is clobbered. */
    ڈالو_2.L  R15

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
    جوڑو_2 #12, R0

    /* All the rest of the registers are saved directly to the user stack. */
    SETPSW  U

    /* Save the rest of the general registers (R15 has been saved already). */
    PUSHM   R1-R14

    /* Save the accumulator. */
    MVFACHI R15
    ڈالو_2.L  R15
    MVFACMI R15 ; درمیان ترتیب لفظ.
    SHLL    #16, R15 ; Shifted بایاں as it is restored مقصد the کم_2 ترتیب لفظ.
    ڈالو_2.L  R15

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
    نکالو_2     R15
    MVTACLO R15
    نکالو_2     R15
    MVTACHI R15
    POPM    R1-R15
    RTE
    NOP
    NOP
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( pxCurrentTCB == تہی );

    /* The following line is just to prevent the symbol getting optimised away. */
    ( خالی ) vTaskSwitchContext();
}
/*-----------------------------------------------------------*/

ساکن خالی prv_تیاری_Timer_مداخلت( خالی )
{
    /* Unlock. */
    SYSTEM.PRCR.لفظ_3 = پورٹ_UNLOCK_کلید;

    /* Enable CMT0. */
    MSTP( CMT0 ) = 0;

    /* Lock again. */
    SYSTEM.PRCR.لفظ_3 = پورٹ_تالا_کلید;

    /* Interrupt on compare match. */
    CMT0.CMCR.ثنائی_ہندسہ_3.CMIE = 1;

    /* Set the compare match value. */
    CMT0.CMCOR = ( uint16_t ) ul_مطابقت_قدر_For_One_Tick;

    /* Divide the PCLK. */
    #اگر پورٹ_CLOCK_مقسوم_علیہ == 512
    {
        CMT0.CMCR.ثنائی_ہندسہ_3.CKS = 3;
    }
    #وگرنہ_اگر پورٹ_CLOCK_مقسوم_علیہ == 128
    {
        CMT0.CMCR.ثنائی_ہندسہ_3.CKS = 2;
    }
    #وگرنہ_اگر پورٹ_CLOCK_مقسوم_علیہ == 32
    {
        CMT0.CMCR.ثنائی_ہندسہ_3.CKS = 1;
    }
    #وگرنہ_اگر پورٹ_CLOCK_مقسوم_علیہ == 8
    {
        CMT0.CMCR.ثنائی_ہندسہ_3.CKS = 0;
    }
    #ورنہ
    {
        #غلطی Invalid پورٹ_CLOCK_مقسوم_علیہ setting
    }
    #اگر_ختم


    /* Enable the interrupt... */
    _IEN( _CMT0_CMI0 ) = 1;

    /* ...and set its priority to the application defined kernel priority. */
    _IPR( _CMT0_CMI0 ) = config_KERNEL_مداخلت_ترجیح;

    /* Start the timer. */
    CMT.CMSTR0.ثنائی_ہندسہ_3.STR0 = 1;
}
/*-----------------------------------------------------------*/

#اگر configUSE_TICKLESS_IDLE == 1

    ساکن خالی prvSleep( TickType_t x_Expected_Idle_وقت )
    {
        /* Allow the application to define some pre-sleep processing. */
        configPRE_SLEEP_PROCESSING( x_Expected_Idle_وقت );

        /* xExpectedIdleTime being set to 0 by configPRE_SLEEP_PROCESSING()
        means the application defined code has already executed the WAIT
        instruction. */
        اگر( x_Expected_Idle_وقت > 0 )
        {
            wait();
        }

        /* Allow the application to define some post sleep processing. */
        configPOST_SLEEP_PROCESSING( x_Expected_Idle_وقت );
    }

#اگر_ختم /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

#اگر configUSE_TICKLESS_IDLE == 1

    خالی v_پورٹ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وقت )
    {
    uint32_t ul_مطابقت_قدر, ulCompleteTickPeriods, ul_Current_گنتی;
    e_Sleep_منوال_حالت eSleepAction;

        /* THIS FUNCTION IS CALLED WITH THE SCHEDULER SUSPENDED. */

        /* Make sure the CMT reload value does not overflow the counter. */
        اگر( x_Expected_Idle_وقت > x_زیادہ_سے_زیادہ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_وقت = x_زیادہ_سے_زیادہ_Possible_Suppressed_Ticks;
        }

        /* Calculate the reload value required to wait xExpectedIdleTime tick
        periods. */
        ul_مطابقت_قدر = ul_مطابقت_قدر_For_One_Tick * x_Expected_Idle_وقت;
        اگر( ul_مطابقت_قدر > ulStoppedTimerCompensation )
        {
            /* Compensate for the fact that the CMT is going to be stopped
            momentarily. */
            ul_مطابقت_قدر -= ulStoppedTimerCompensation;
        }

        /* Stop the CMT momentarily.  The time the CMT is stopped for is
        accounted for as best it can be, but using the tickless mode will
        inevitably result in some tiny drift of the time maintained by the
        kernel with respect to calendar time. */
        CMT.CMSTR0.ثنائی_ہندسہ_3.STR0 = 0;
        جب( CMT.CMSTR0.ثنائی_ہندسہ_3.STR0 == 1 )
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
        eSleepAction = e_Task_Confirm_Sleep_منوال_حالت();
        اگر( eSleepAction == eAbortSleep )
        {
            /* Restart tick. */
            CMT.CMSTR0.ثنائی_ہندسہ_3.STR0 = 1;
            setpsw_i();
        }
        ورنہ اگر( eSleepAction == e_No_Tasks_انتظار_Timeout )
        {
            /* Protection off. */
            SYSTEM.PRCR.لفظ_3 = پورٹ_UNLOCK_کلید;

            /* Ready for software standby with all clocks stopped. */
            SYSTEM.SBYCR.ثنائی_ہندسہ_3.SSBY = 1;

            /* Protection on. */
            SYSTEM.PRCR.لفظ_3 = پورٹ_تالا_کلید;

            /* Sleep until something happens.  Calling prvSleep() will
            automatically reset the i bit in the PSW. */
            prvSleep( x_Expected_Idle_وقت );

            /* Restart the CMT. */
            CMT.CMSTR0.ثنائی_ہندسہ_3.STR0 = 1;
        }
        ورنہ
        {
            /* Protection off. */
            SYSTEM.PRCR.لفظ_3 = پورٹ_UNLOCK_کلید;

            /* Ready for deep sleep mode. */
            SYSTEM.MSTPCRC.ثنائی_ہندسہ_3.DSLPE = 1;
            SYSTEM.MSTPCRA.ثنائی_ہندسہ_3.MSTPA28 = 1;
            SYSTEM.SBYCR.ثنائی_ہندسہ_3.SSBY = 0;

            /* Protection on. */
            SYSTEM.PRCR.لفظ_3 = پورٹ_تالا_کلید;

            /* Adjust the match value to take into account that the current
            time slice is already partially complete. */
            ul_مطابقت_قدر -= ( uint32_t ) CMT0.CMCNT;
            CMT0.CMCOR = ( uint16_t ) ul_مطابقت_قدر;

            /* Restart the CMT to count up to the new match value. */
            CMT0.CMCNT = 0;
            CMT.CMSTR0.ثنائی_ہندسہ_3.STR0 = 1;

            /* Sleep until something happens.  Calling prvSleep() will
            automatically reset the i bit in the PSW. */
            prvSleep( x_Expected_Idle_وقت );

            /* Stop CMT.  Again, the time the SysTick is stopped for is
            accounted for as best it can be, but using the tickless mode will
            inevitably result in some tiny drift of the time maintained by the
            kernel with respect to calendar time. */
            CMT.CMSTR0.ثنائی_ہندسہ_3.STR0 = 0;
            جب( CMT.CMSTR0.ثنائی_ہندسہ_3.STR0 == 1 )
            {
                /* Nothing to do here. */
            }

            ul_Current_گنتی = ( uint32_t ) CMT0.CMCNT;

            اگر( ulTickFlag != pdFALSE )
            {
                /* The tick interrupt has already executed, although because
                this function is called with the scheduler suspended the actual
                tick processing will not occur until after this function has
                exited.  Reset the match value with whatever remains of this
                tick period. */
                ul_مطابقت_قدر = ul_مطابقت_قدر_For_One_Tick - ul_Current_گنتی;
                CMT0.CMCOR = ( uint16_t ) ul_مطابقت_قدر;

                /* The tick interrupt handler will already have pended the tick
                processing in the kernel.  As the pending tick will be
                processed as soon as this function exits, the tick value
                maintained by the tick is stepped forward by one less than the
                time spent sleeping.  The actual stepping of the tick appears
                later in this function. */
                ulCompleteTickPeriods = x_Expected_Idle_وقت - 1UL;
            }
            ورنہ
            {
                /* Something other than the tick interrupt ended the sleep.
                How many complete tick periods passed while the processor was
                sleeping? */
                ulCompleteTickPeriods = ul_Current_گنتی / ul_مطابقت_قدر_For_One_Tick;

                /* The match value is set to whatever fraction of a single tick
                period remains. */
                ul_مطابقت_قدر = ul_Current_گنتی - ( ulCompleteTickPeriods * ul_مطابقت_قدر_For_One_Tick );
                CMT0.CMCOR = ( uint16_t ) ul_مطابقت_قدر;
            }

            /* Restart the CMT so it runs up to the match value.  The match value
            will get set to the value required to generate exactly one tick period
            the next time the CMT interrupt executes. */
            CMT0.CMCNT = 0;
            CMT.CMSTR0.ثنائی_ہندسہ_3.STR0 = 1;

            /* Wind the tick forward by the number of tick periods that the CPU
            remained in a low power state. */
            v_Task_قدم_Tick( ulCompleteTickPeriods );
        }
    }

#اگر_ختم /* configUSE_TICKLESS_IDLE */
