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
* Implementation of functions defined in portable.h for the SH2A port.
*----------------------------------------------------------*/

/* Standard C includes. */
#అన్తర్భావ "limits.h"

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* Library includes. */
#అన్తర్భావ "string.h"

/* Hardware specifics. */
#ఒకవేళ ( config_INCLUDE_PLATFORM_H_INSTEAD_యొక్క_IODEFINE_H == 1 )

    #అన్తర్భావ "platform.h"

#లేకపోతే /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

    #అన్తర్భావ "iodefine.h"

#అయితే_ముగింపు /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */
/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
 * PSW is set with U and I set, and PM and IPL clear. */
#నిర్వచించు పోర్టు_INITIAL_PSW    ( ( దొంతర_Type_t ) 0x00030000 )

/* The peripheral clock is divided by this value before being supplying the
 * CMT. */
#ఒకవేళ ( configUSE_TICKLESS_IDLE == 0 )
    /* If tickless idle is not used then the divisor can be fixed. */
    #నిర్వచించు పోర్టు_CLOCK_భాజకం    8UL
#లేదావేళ ( configPERIPHERAL_CLOCK_HZ >= 12000000 )
    #నిర్వచించు పోర్టు_CLOCK_భాజకం    512UL
#లేదావేళ ( configPERIPHERAL_CLOCK_HZ >= 6000000 )
    #నిర్వచించు పోర్టు_CLOCK_భాజకం    128UL
#లేదావేళ ( configPERIPHERAL_CLOCK_HZ >= 1000000 )
    #నిర్వచించు పోర్టు_CLOCK_భాజకం    32UL
#లేకపోతే
    #నిర్వచించు పోర్టు_CLOCK_భాజకం    8UL
#అయితే_ముగింపు

/* These macros allow a critical section to be added around the call to
 * xTaskIncrementTick(), which is only ever called from interrupts at the kernel
 * priority - ie a known priority.  Therefore these local macros are a slight
 * optimisation compared to calling the global SET/CLEAR_INTERRUPT_MASK macros,
 * which would require the old IPL to be read first and stored in a local variable. */
#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS_FROM_KERNEL_ISR()    __asm అస్థిర ( "MVTIPL    %0" ::"i" ( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత ) )
#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS_FROM_KERNEL_ISR()     __asm అస్థిర ( "MVTIPL    %0" ::"i" ( config_KERNEL_అంతరాయం_ప్రాధాన్యత ) )

/* Keys required to lock and unlock access to certain system registers
 * respectively. */
#నిర్వచించు పోర్టు_UNLOCK_కీలకం    0xA50B
#నిర్వచించు పోర్టు_తాళం_కీలకం      0xA500

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
స్థిర శూన్య prv_ప్రారంభం_మొదటి_Task( శూన్య ) __attribute__( ( naked ) );

/*
 * Software interrupt handler.  Performs the actual context switch (saving and
 * restoring of registers).  Written in asm code as direct register access is
 * required.
 */
#ఒకవేళ ( config_INCLUDE_PLATFORM_H_INSTEAD_యొక్క_IODEFINE_H == 1 )

    R_BSP_PRAGMA_అంతరాయం( v_పోర్టు_Software_అంతరాయం_ISR, VECT( ICU, SWINT ) )
    R_BSP_ATTRIB_అంతరాయం శూన్య v_పోర్టు_Software_అంతరాయం_ISR( శూన్య ) __attribute__( ( naked ) );

#లేకపోతే /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

    శూన్య v_పోర్టు_Software_అంతరాయం_ISR( శూన్య ) __attribute__( ( naked ) );

#అయితే_ముగింపు /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H  */

/*
 * The tick ISR handler.  The peripheral used is configured by the application
 * via a hook/callback function.
 */
#ఒకవేళ ( config_INCLUDE_PLATFORM_H_INSTEAD_యొక్క_IODEFINE_H == 1 )

    R_BSP_PRAGMA_అంతరాయం( v_పోర్టు_Tick_ISR, _VECT( config_TICK_సదిశ ) )
    R_BSP_ATTRIB_అంతరాయం శూన్య v_పోర్టు_Tick_ISR( శూన్య ); /* Do not add __attribute__( ( interrupt ) ). */

#లేకపోతే /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

    శూన్య v_పోర్టు_Tick_ISR( శూన్య ) __attribute__( ( అంతరాయం ) );

#అయితే_ముగింపు /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

/*
 * Sets up the periodic ISR used for the RTOS tick using the CMT.
 * The application writer can define configSETUP_TICK_INTERRUPT() (in
 * FreeRTOSConfig.h) such that their own tick interrupt configuration is used
 * in place of prvSetupTimerInterrupt().
 */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య );
#నిర్వచితం_కాకపోతే config_అమరిక_TICK_అంతరాయం

/* The user has not provided their own tick interrupt configuration so use
 * the definition in this file (which uses the interval timer). */
    #నిర్వచించు config_అమరిక_TICK_అంతరాయం()    prv_అమరిక_Timer_అంతరాయం()
#అయితే_ముగింపు /* configSETUP_TICK_INTERRUPT */

/*
 * Called after the sleep mode registers have been configured, prvSleep()
 * executes the pre and post sleep macros, and actually calls the wait
 * instruction.
 */
#ఒకవేళ configUSE_TICKLESS_IDLE == 1
    స్థిర శూన్య prvSleep( TickType_t x_Expected_Idle_సమయం );
#అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

/* Used in the context save and restore code. */
బాహ్య శూన్య * pxCurrentTCB;

/* Calculate how many clock increments make up a single tick period. */
స్థిర స్థిరరాశి uint32_t ul_సరిపోలిక_విలువ_For_One_Tick = ( ( configPERIPHERAL_CLOCK_HZ / పోర్టు_CLOCK_భాజకం ) / config_TICK_రేటు_HZ );

#ఒకవేళ configUSE_TICKLESS_IDLE == 1

/* Holds the maximum number of ticks that can be suppressed - which is
 * basically how far into the future an interrupt can be generated. Set
 * during initialisation.  This is the maximum possible value that the
 * compare match register can hold divided by ulMatchValueForOneTick. */
    స్థిర స్థిరరాశి TickType_t x_గరిష్ఠ_Possible_Suppressed_Ticks = USHRT_MAX / ( ( configPERIPHERAL_CLOCK_HZ / పోర్టు_CLOCK_భాజకం ) / config_TICK_రేటు_HZ );

/* Flag set from the tick interrupt to allow the sleep processing to know if
 * sleep mode was exited because of a tick interrupt, or an interrupt
 * generated by something else. */
    స్థిర అస్థిర uint32_t ulTickFlag = pdFALSE;

/* The CMT counter is stopped temporarily each time it is re-programmed.
 * The following constant offsets the CMT counter match value by the number of
 * CMT counts that would typically be missed while the counter was stopped to
 * compensate for the lost time.  The large difference between the divided CMT
 * clock and the CPU clock means it is likely ulStoppedTimerCompensation will
 * equal zero - and be optimised away. */
    స్థిర స్థిరరాశి uint32_t ulStoppedTimerCompensation = 100UL / ( configCPU_CLOCK_HZ / ( configPERIPHERAL_CLOCK_HZ / పోర్టు_CLOCK_భాజకం ) );

#అయితే_ముగింపు /* if configUSE_TICKLESS_IDLE == 1 */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    /* Offset to end up on 8 byte boundary. */
    px_శిఖరం_యొక్క_దొంతర--;

    /* R0 is not included as it is the stack pointer. */
    *px_శిఖరం_యొక్క_దొంతర = 0x00;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x00;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_PSW;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం;

    /* When debugging it can be useful if every register is set to a known
     * value.  Otherwise code space can be saved by just setting the registers
     * that need to be set. */
    #నిర్వచితమైతే USE_నిండిన_రిజిస్టరు_INITIALISATION
    {
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x12345678; /* r15. */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0xaaaabbbb;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0xdddddddd;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0xcccccccc;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0xbbbbbbbb;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0xaaaaaaaa;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x99999999;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x88888888;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x77777777;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x66666666;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x55555555;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x44444444;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x33333333;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x22222222;
        px_శిఖరం_యొక్క_దొంతర--;
    }
    #లేకపోతే /* ifdef USE_FULL_REGISTER_INITIALISATION */
    {
        /* Leave space for the registers that will get popped from the stack
         * when the task first starts executing. */
        px_శిఖరం_యొక్క_దొంతర -= 15;
    }
    #అయితే_ముగింపు /* ifdef USE_FULL_REGISTER_INITIALISATION */

    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters; /* R1 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x12345678;                   /* Accumulator. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x87654321;                   /* Accumulator. */

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    /* Use pxCurrentTCB just so it does not get optimised away. */
    ఒకవేళ( pxCurrentTCB != ఖాళీ )
    {
        /* Call an application function to set up the timer that will generate
         * the tick interrupt.  This way the application can decide which
         * peripheral to use.  If tickless mode is used then the default
         * implementation defined in this file (which uses CMT0) should not be
         * overridden. */
        config_అమరిక_TICK_అంతరాయం();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = config_KERNEL_అంతరాయం_ప్రాధాన్యత;

        /* Start the first task. */
        prv_ప్రారంభం_మొదటి_Task();
    }

    /* Execution should not reach here as the tasks are now running!
     * prvSetupTimerInterrupt() is called here to prevent the compiler outputting
     * a warning about a statically declared function not being referenced in the
     * case that the application writer has provided their own tick interrupt
     * configuration routine (and defined configSETUP_TICK_INTERRUPT() such that
     * their own routine will be called in place of prvSetupTimerInterrupt()). */
    prv_అమరిక_Timer_అంతరాయం();

    /* Should not get here. */
    తిరిగి pdFAIL;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pxCurrentTCB == ఖాళీ );
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_ప్రారంభం_మొదటి_Task( శూన్య )
{
    __asm అస్థిర
    (

        /* When starting the scheduler there is nothing that needs moving to the
         * interrupt stack because the function is not called from an interrupt.
         * Just ensure the current stack is the user stack. */
        "SETPSW     U                       \n" \


        /* Obtain the location of the stack associated with which ever task
         * pxCurrentTCB is currently pointing to. */
        "MOV.L      #_pxCurrentTCB, R15     \n" \
        "MOV.L      [R15], R15              \n" \
        "MOV.L      [R15], R0               \n" \


        /* Restore the registers from the stack of the task pointed to by
         * pxCurrentTCB. */
        "POP        R15                     \n" \

        /* Accumulator low 32 bits. */
        "MVTACLO    R15                     \n" \
        "POP        R15                     \n" \

        /* Accumulator high 32 bits. */
        "MVTACHI    R15                     \n" \

        /* R1 to R15 - R0 is not included as it is the SP. */
        "POPM       R1-R15                  \n" \

        /* This pops the remaining registers. */
        "RTE                                \n" \
        "NOP                                \n" \
        "NOP                                \n"
    );
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Software_అంతరాయం_ISR( శూన్య )
{
    __asm అస్థిర
    (
        /* Re-enable interrupts. */
        "SETPSW     I                           \n" \


        /* Move the data that was automatically pushed onto the interrupt stack when
         * the interrupt occurred from the interrupt stack to the user stack.
         *
         * R15 is saved before it is clobbered. */
        "PUSH.L     R15                         \n" \

        /* Read the user stack pointer. */
        "MVFC       USP, R15                    \n" \

        /* Move the address down to the data being moved. */
        "SUB        #12, R15                    \n" \
        "MVTC       R15, USP                    \n" \

        /* Copy the data across, R15, then PC, then PSW. */
        "MOV.L      [ R0 ], [ R15 ]             \n" \
        "MOV.L      4[ R0 ], 4[ R15 ]           \n" \
        "MOV.L      8[ R0 ], 8[ R15 ]           \n" \

        /* Move the interrupt stack pointer to its new correct position. */
        "ADD        #12, R0                     \n" \

        /* All the rest of the registers are saved directly to the user stack. */
        "SETPSW     U                           \n" \

        /* Save the rest of the general registers (R15 has been saved already). */
        "PUSHM      R1-R14                      \n" \

        /* Save the accumulator. */
        "MVFACHI    R15                         \n" \
        "PUSH.L     R15                         \n" \

        /* Middle word. */
        "MVFACMI    R15                         \n" \

        /* Shifted left as it is restored to the low order word. */
        "SHLL       #16, R15                    \n" \
        "PUSH.L     R15                         \n" \

        /* Save the stack pointer to the TCB. */
        "MOV.L      #_pxCurrentTCB, R15         \n" \
        "MOV.L      [ R15 ], R15                \n" \
        "MOV.L      R0, [ R15 ]                 \n" \


        /* Ensure the interrupt mask is set to the syscall priority while the kernel
         * structures are being accessed. */
        "MVTIPL     %0                          \n" \

        /* Select the next task to run. */
        "BSR.A      _vTaskSwitchContext         \n" \

        /* Reset the interrupt mask as no more data structure access is required. */
        "MVTIPL     %1                          \n" \


        /* Load the stack pointer of the task that is now selected as the Running
         * state task from its TCB. */
        "MOV.L      #_pxCurrentTCB,R15          \n" \
        "MOV.L      [ R15 ], R15                \n" \
        "MOV.L      [ R15 ], R0                 \n" \


        /* Restore the context of the new task.  The PSW (Program Status Word) and
         * PC will be popped by the RTE instruction. */
        "POP        R15                         \n" \
        "MVTACLO    R15                         \n" \
        "POP        R15                         \n" \
        "MVTACHI    R15                         \n" \
        "POPM       R1-R15                      \n" \
        "RTE                                    \n" \
        "NOP                                    \n" \
        "NOP                                      "
        ::"i" ( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత ), "i" ( config_KERNEL_అంతరాయం_ప్రాధాన్యత )
    );
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Tick_ISR( శూన్య )
{
    /* Re-enabled interrupts. */
    __asm అస్థిర ( "SETPSW I" );

    /* Increment the tick, and perform any processing the new tick value
     * necessitates.  Ensure IPL is at the max syscall value first. */
    పోర్టు_DISABLE_INTERRUPTS_FROM_KERNEL_ISR();
    {
        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    పోర్టు_ENABLE_INTERRUPTS_FROM_KERNEL_ISR();

    #ఒకవేళ configUSE_TICKLESS_IDLE == 1
    {
        /* The CPU woke because of a tick. */
        ulTickFlag = pdTRUE;

        /* If this is the first tick since exiting tickless mode then the CMT
         * compare match value needs resetting. */
        CMT0.CMCOR = ( uint16_t ) ul_సరిపోలిక_విలువ_For_One_Tick;
    }
    #అయితే_ముగింపు
}
/*-----------------------------------------------------------*/

uint32_t ul_పోర్టు_Get_IPL( శూన్య )
{
    __asm అస్థిర
    (
        "MVFC   PSW, R1         \n" \
        "SHLR   #24, R1         \n" \
        "RTS                      "
    );

    /* This will never get executed, but keeps the compiler from complaining. */
    తిరిగి 0;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_సమితి_IPL( uint32_t ulNewIPL )
{
    __asm అస్థిర
    (
        "PUSH   R5              \n" \
        "MVFC   PSW, R5         \n" \
        "SHLL   #24, R1         \n" \
        "AND    #-0F000001H, R5 \n" \
        "OR     R1, R5          \n" \
        "MVTC   R5, PSW         \n" \
        "POP    R5              \n" \
        "RTS                      "
    );
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
{
    /* Unlock. */
    SYSTEM.PRCR.మాట_3 = పోర్టు_UNLOCK_కీలకం;

    /* Enable CMT0. */
    MSTP( CMT0 ) = 0;

    /* Lock again. */
    SYSTEM.PRCR.మాట_3 = పోర్టు_తాళం_కీలకం;

    /* Interrupt on compare match. */
    CMT0.CMCR.బిట్టు_3.CMIE = 1;

    /* Set the compare match value. */
    CMT0.CMCOR = ( uint16_t ) ul_సరిపోలిక_విలువ_For_One_Tick;

    /* Divide the PCLK. */
    #ఒకవేళ పోర్టు_CLOCK_భాజకం == 512
    {
        CMT0.CMCR.బిట్టు_3.CKS = 3;
    }
    #లేదావేళ పోర్టు_CLOCK_భాజకం == 128
    {
        CMT0.CMCR.బిట్టు_3.CKS = 2;
    }
    #లేదావేళ పోర్టు_CLOCK_భాజకం == 32
    {
        CMT0.CMCR.బిట్టు_3.CKS = 1;
    }
    #లేదావేళ పోర్టు_CLOCK_భాజకం == 8
    {
        CMT0.CMCR.బిట్టు_3.CKS = 0;
    }
    #లేకపోతే /* if portCLOCK_DIVISOR == 512 */
    {
        #దోషం Invalid పోర్టు_CLOCK_భాజకం setting
    }
    #అయితే_ముగింపు /* if portCLOCK_DIVISOR == 512 */

    /* Enable the interrupt... */
    _IEN( _CMT0_CMI0 ) = 1;

    /* ...and set its priority to the application defined kernel priority. */
    _IPR( _CMT0_CMI0 ) = config_KERNEL_అంతరాయం_ప్రాధాన్యత;

    /* Start the timer. */
    CMT.CMSTR0.బిట్టు_3.STR0 = 1;
}
/*-----------------------------------------------------------*/

#ఒకవేళ configUSE_TICKLESS_IDLE == 1

    స్థిర శూన్య prvSleep( TickType_t x_Expected_Idle_సమయం )
    {
        /* Allow the application to define some pre-sleep processing. */
        configPRE_SLEEP_PROCESSING( x_Expected_Idle_సమయం );

        /* xExpectedIdleTime being set to 0 by configPRE_SLEEP_PROCESSING()
         * means the application defined code has already executed the WAIT
         * instruction. */
        ఒకవేళ( x_Expected_Idle_సమయం > 0 )
        {
            __asm అస్థిర ( "WAIT" );
        }

        /* Allow the application to define some post sleep processing. */
        configPOST_SLEEP_PROCESSING( x_Expected_Idle_సమయం );
    }

#అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

#ఒకవేళ configUSE_TICKLESS_IDLE == 1

    శూన్య v_పోర్టు_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_సమయం )
    {
        uint32_t ul_సరిపోలిక_విలువ, ulCompleteTickPeriods, ul_Current_లెక్క;
        e_Sleep_బహుళకం_స్థితి eSleepAction;

        /* THIS FUNCTION IS CALLED WITH THE SCHEDULER SUSPENDED. */

        /* Make sure the CMT reload value does not overflow the counter. */
        ఒకవేళ( x_Expected_Idle_సమయం > x_గరిష్ఠ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_సమయం = x_గరిష్ఠ_Possible_Suppressed_Ticks;
        }

        /* Calculate the reload value required to wait xExpectedIdleTime tick
         * periods. */
        ul_సరిపోలిక_విలువ = ul_సరిపోలిక_విలువ_For_One_Tick * x_Expected_Idle_సమయం;

        ఒకవేళ( ul_సరిపోలిక_విలువ > ulStoppedTimerCompensation )
        {
            /* Compensate for the fact that the CMT is going to be stopped
             * momentarily. */
            ul_సరిపోలిక_విలువ -= ulStoppedTimerCompensation;
        }

        /* Stop the CMT momentarily.  The time the CMT is stopped for is
         * accounted for as best it can be, but using the tickless mode will
         * inevitably result in some tiny drift of the time maintained by the
         * kernel with respect to calendar time. */
        CMT.CMSTR0.బిట్టు_3.STR0 = 0;

        అయితే( CMT.CMSTR0.బిట్టు_3.STR0 == 1 )
        {
            /* Nothing to do here. */
        }

        /* Critical section using the global interrupt bit as the i bit is
         * automatically reset by the WAIT instruction. */
        __asm అస్థిర ( "CLRPSW i" );

        /* The tick flag is set to false before sleeping.  If it is true when
         * sleep mode is exited then sleep mode was probably exited because the
         * tick was suppressed for the entire xExpectedIdleTime period. */
        ulTickFlag = pdFALSE;

        /* If a context switch is pending then abandon the low power entry as
         * the context switch might have been pended by an external interrupt that
         * requires processing. */
        eSleepAction = e_Task_Confirm_Sleep_బహుళకం_స్థితి();

        ఒకవేళ( eSleepAction == eAbortSleep )
        {
            /* Restart tick. */
            CMT.CMSTR0.బిట్టు_3.STR0 = 1;
            __asm అస్థిర ( "SETPSW i" );
        }
        లేకపోతే ఒకవేళ( eSleepAction == e_No_Tasks_నిరీక్షణ_Timeout )
        {
            /* Protection off. */
            SYSTEM.PRCR.మాట_3 = పోర్టు_UNLOCK_కీలకం;

            /* Ready for software standby with all clocks stopped. */
            SYSTEM.SBYCR.బిట్టు_3.SSBY = 1;

            /* Protection on. */
            SYSTEM.PRCR.మాట_3 = పోర్టు_తాళం_కీలకం;

            /* Sleep until something happens.  Calling prvSleep() will
             * automatically reset the i bit in the PSW. */
            prvSleep( x_Expected_Idle_సమయం );

            /* Restart the CMT. */
            CMT.CMSTR0.బిట్టు_3.STR0 = 1;
        }
        లేకపోతే
        {
            /* Protection off. */
            SYSTEM.PRCR.మాట_3 = పోర్టు_UNLOCK_కీలకం;

            /* Ready for deep sleep mode. */
            SYSTEM.MSTPCRC.బిట్టు_3.DSLPE = 1;
            SYSTEM.MSTPCRA.బిట్టు_3.MSTPA28 = 1;
            SYSTEM.SBYCR.బిట్టు_3.SSBY = 0;

            /* Protection on. */
            SYSTEM.PRCR.మాట_3 = పోర్టు_తాళం_కీలకం;

            /* Adjust the match value to take into account that the current
             * time slice is already partially complete. */
            ul_సరిపోలిక_విలువ -= ( uint32_t ) CMT0.CMCNT;
            CMT0.CMCOR = ( uint16_t ) ul_సరిపోలిక_విలువ;

            /* Restart the CMT to count up to the new match value. */
            CMT0.CMCNT = 0;
            CMT.CMSTR0.బిట్టు_3.STR0 = 1;

            /* Sleep until something happens.  Calling prvSleep() will
             * automatically reset the i bit in the PSW. */
            prvSleep( x_Expected_Idle_సమయం );

            /* Stop CMT.  Again, the time the SysTick is stopped for is
             * accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            CMT.CMSTR0.బిట్టు_3.STR0 = 0;

            అయితే( CMT.CMSTR0.బిట్టు_3.STR0 == 1 )
            {
                /* Nothing to do here. */
            }

            ul_Current_లెక్క = ( uint32_t ) CMT0.CMCNT;

            ఒకవేళ( ulTickFlag != pdFALSE )
            {
                /* The tick interrupt has already executed, although because
                 * this function is called with the scheduler suspended the actual
                 * tick processing will not occur until after this function has
                 * exited.  Reset the match value with whatever remains of this
                 * tick period. */
                ul_సరిపోలిక_విలువ = ul_సరిపోలిక_విలువ_For_One_Tick - ul_Current_లెక్క;
                CMT0.CMCOR = ( uint16_t ) ul_సరిపోలిక_విలువ;

                /* The tick interrupt handler will already have pended the tick
                 * processing in the kernel.  As the pending tick will be
                 * processed as soon as this function exits, the tick value
                 * maintained by the tick is stepped forward by one less than the
                 * time spent sleeping.  The actual stepping of the tick appears
                 * later in this function. */
                ulCompleteTickPeriods = x_Expected_Idle_సమయం - 1UL;
            }
            లేకపోతే
            {
                /* Something other than the tick interrupt ended the sleep.
                 * How many complete tick periods passed while the processor was
                 * sleeping? */
                ulCompleteTickPeriods = ul_Current_లెక్క / ul_సరిపోలిక_విలువ_For_One_Tick;

                /* The match value is set to whatever fraction of a single tick
                 * period remains. */
                ul_సరిపోలిక_విలువ = ul_Current_లెక్క - ( ulCompleteTickPeriods * ul_సరిపోలిక_విలువ_For_One_Tick );
                CMT0.CMCOR = ( uint16_t ) ul_సరిపోలిక_విలువ;
            }

            /* Restart the CMT so it runs up to the match value.  The match value
             * will get set to the value required to generate exactly one tick period
             * the next time the CMT interrupt executes. */
            CMT0.CMCNT = 0;
            CMT.CMSTR0.బిట్టు_3.STR0 = 1;

            /* Wind the tick forward by the number of tick periods that the CPU
             * remained in a low power state. */
            v_Task_అడుగు_Tick( ulCompleteTickPeriods );
        }
    }

#అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */
