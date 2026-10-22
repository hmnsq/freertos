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
 * Implementation of functions defined in portable.h for the RX600 port.
 *----------------------------------------------------------*/

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* Library includes. */
#అన్తర్భావ "string.h"

/* Hardware specifics. */
#ఒకవేళ defined( config_INCLUDE_PLATFORM_H_INSTEAD_యొక్క_IODEFINE_H ) && ( config_INCLUDE_PLATFORM_H_INSTEAD_యొక్క_IODEFINE_H == 1 )
    #అన్తర్భావ "platform.h"
#లేకపోతే
    #అన్తర్భావ "iodefine.h"
#అయితే_ముగింపు

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
PSW is set with U and I set, and PM and IPL clear. */
#నిర్వచించు పోర్టు_INITIAL_PSW     ( ( దొంతర_Type_t ) 0x00030000 )
#నిర్వచించు పోర్టు_INITIAL_FPSW    ( ( దొంతర_Type_t ) 0x00000100 )

/*-----------------------------------------------------------*/

/* The following lines are to ensure vSoftwareInterruptEntry can be referenced,
 and therefore installed in the vector table, when the FreeRTOS code is built
as a library. */
బాహ్య పునాది_Type_t v_Software_అంతరాయం_నమోదు;
స్థిరరాశి పునాది_Type_t * p_v_Software_అంతరాయం_నమోదు = &v_Software_అంతరాయం_నమోదు;

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
స్థిర శూన్య prv_ప్రారంభం_మొదటి_Task( శూన్య );

/*
 * Software interrupt handler.  Performs the actual context switch (saving and
 * restoring of registers).  Written in asm code as direct register access is
 * required.
 */
స్థిర శూన్య prvYieldHandler( శూన్య );

/*
 * The entry point for the software interrupt handler.  This is the function
 * that calls the inline asm function prvYieldHandler().  It is installed in
 * the vector table, but the code that installs it is in prvYieldHandler rather
 * than using a #pragma.
 */
శూన్య v_Software_అంతరాయం_ISR( శూన్య );

/*-----------------------------------------------------------*/

/* This is accessed by the inline assembler functions so is file scope for
convenience. */
బాహ్య శూన్య *pxCurrentTCB;
బాహ్య శూన్య vTaskSwitchContext( శూన్య );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
దొంతర_Type_t *px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t *px_శిఖరం_యొక్క_దొంతర, TaskFunction_t px_సంకేతం, శూన్య *pvParameters )
{
    /* R0 is not included as it is the stack pointer. */

    *px_శిఖరం_యొక్క_దొంతర = 0x00;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_PSW;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం;

    /* When debugging it can be useful if every register is set to a known
    value.  Otherwise code space can be saved by just setting the registers
    that need to be set. */
    #నిర్వచితమైతే USE_నిండిన_రిజిస్టరు_INITIALISATION
    {
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0xffffffff; /* r15. */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0xeeeeeeee;
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
    #లేకపోతే
    {
        px_శిఖరం_యొక్క_దొంతర -= 15;
    }
    #అయితే_ముగింపు

    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters; /* R1 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_FPSW;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x11111111; /* Accumulator 0. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x22222222; /* Accumulator 0. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x33333333; /* Accumulator 0. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x44444444; /* Accumulator 1. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x55555555; /* Accumulator 1. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x66666666; /* Accumulator 1. */

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
బాహ్య శూన్య v_Application_అమరిక_Timer_అంతరాయం( శూన్య );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    ఒకవేళ( pxCurrentTCB != ఖాళీ )
    {
        /* Call an application function to set up the timer that will generate the
        tick interrupt.  This way the application can decide which peripheral to
        use.  A demo application is provided to show a suitable example. */
        v_Application_అమరిక_Timer_అంతరాయం();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = config_KERNEL_అంతరాయం_ప్రాధాన్యత;

        /* Start the first task. */
        prv_ప్రారంభం_మొదటి_Task();
    }

    /* Just to make sure the function is not optimised away. */
    ( శూన్య ) v_Software_అంతరాయం_ISR();

    /* Should not get here. */
    తిరిగి pdFAIL;
}
/*-----------------------------------------------------------*/

#సూచన inline_asm prv_ప్రారంభం_మొదటి_Task
స్థిర శూన్య prv_ప్రారంభం_మొదటి_Task( శూన్య )
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
    తీయి_2     R15
    MVTACLO R15, A0     /* Accumulator low 32 bits. */
    తీయి_2     R15
    MVTACHI R15, A0     /* Accumulator high 32 bits. */
    తీయి_2     R15
    MVTACGU R15, A0     /* Accumulator guard. */
    తీయి_2     R15
    MVTACLO R15, A1     /* Accumulator low 32 bits. */
    తీయి_2     R15
    MVTACHI R15, A1     /* Accumulator high 32 bits. */
    తీయి_2     R15
    MVTACGU R15, A1     /* Accumulator guard. */
    తీయి_2     R15
    MVTC    R15,FPSW    /* Floating point status word. */
    POPM    R1-R15      /* R1 to R15 - R0 is not included as it is the SP. */
    RTE                 /* This pops the remaining registers. */
    NOP
    NOP
}
/*-----------------------------------------------------------*/

#సూచన అంతరాయం ( vTickISR( vect = _VECT( config_TICK_సదిశ ), enable ) )
శూన్య vTickISR( శూన్య )
{
    /* Increment the tick, and perform any processing the new tick value
    necessitates. */
    సమితి_ipl( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత );
    {
        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    సమితి_ipl( config_KERNEL_అంతరాయం_ప్రాధాన్యత );
}
/*-----------------------------------------------------------*/

శూన్య v_Software_అంతరాయం_ISR( శూన్య )
{
    prvYieldHandler();
}
/*-----------------------------------------------------------*/

#సూచన inline_asm prvYieldHandler
స్థిర శూన్య prvYieldHandler( శూన్య )
{
    /* Re-enable interrupts. */
    SETPSW  I

    /* Move the data that was automatically pushed onto the interrupt stack when
    the interrupt occurred from the interrupt stack to the user stack.

    R15 is saved before it is clobbered. */
    నెట్టు_2.L  R15

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
    కూడు_2 #12, R0

    /* All the rest of the registers are saved directly to the user stack. */
    SETPSW  U

    /* Save the rest of the general registers (R15 has been saved already). */
    PUSHM   R1-R14

    /* Save the FPSW and accumulators. */
    MVFC    FPSW, R15
    నెట్టు_2.L  R15
    MVFACGU #0, A1, R15
    నెట్టు_2.L  R15
    MVFACHI #0, A1, R15
    నెట్టు_2.L  R15
    MVFACLO #0, A1, R15 ; దిగువ క్రమం మాట.
    నెట్టు_2.L  R15
    MVFACGU #0, A0, R15
    నెట్టు_2.L  R15
    MVFACHI #0, A0, R15
    నెట్టు_2.L  R15
    MVFACLO #0, A0, R15 ; దిగువ క్రమం మాట.
    నెట్టు_2.L  R15

    /* Save the stack pointer to the TCB. */
    MOV.L   #_pxCurrentTCB, R15
    MOV.L   [ R15 ], R15
    MOV.L   R0, [ R15 ]

    /* Ensure the interrupt mask is set to the syscall priority while the kernel
    structures are being accessed. */
    MVTIPL  #configMAX_SYSCALL_INTERRUPT_PRIORITY

    /* Select the next task to run. */
    BSR.A   _vTaskSwitchContext

    /* Reset the interrupt mask as no more data structure access is required. */
    MVTIPL  #configKERNEL_INTERRUPT_PRIORITY

    /* Load the stack pointer of the task that is now selected as the Running
    state task from its TCB. */
    MOV.L   #_pxCurrentTCB,R15
    MOV.L   [ R15 ], R15
    MOV.L   [ R15 ], R0

    /* Restore the context of the new task.  The PSW (Program Status Word) and
    PC will be popped by the RTE instruction. */
    తీయి_2     R15
    MVTACLO R15, A0     /* Accumulator low 32 bits. */
    తీయి_2     R15
    MVTACHI R15, A0     /* Accumulator high 32 bits. */
    తీయి_2     R15
    MVTACGU R15, A0     /* Accumulator guard. */
    తీయి_2     R15
    MVTACLO R15, A1     /* Accumulator low 32 bits. */
    తీయి_2     R15
    MVTACHI R15, A1     /* Accumulator high 32 bits. */
    తీయి_2     R15
    MVTACGU R15, A1     /* Accumulator guard. */
    తీయి_2     R15
    MVTC    R15,FPSW
    POPM    R1-R15
    RTE
    NOP
    NOP
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( pxCurrentTCB == ఖాళీ );

    /* The following line is just to prevent the symbol getting optimised away. */
    ( శూన్య ) vTaskSwitchContext();
}
/*-----------------------------------------------------------*/
