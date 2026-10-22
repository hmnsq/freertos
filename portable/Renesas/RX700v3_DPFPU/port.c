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
* Implementation of functions defined in portable.h for the RXv3 DPFPU port.
*----------------------------------------------------------*/

#warning Testing కొరకు DFPU support లోపల this పోర్టు is not yet complete

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
#నిర్వచించు పోర్టు_INITIAL_PSW     ( ( దొంతర_Type_t ) 0x00030000 )
#నిర్వచించు పోర్టు_INITIAL_FPSW    ( ( దొంతర_Type_t ) 0x00000100 )
#నిర్వచించు పోర్టు_INITIAL_DPSW    ( ( దొంతర_Type_t ) 0x00000100 )
#నిర్వచించు పోర్టు_INITIAL_DCMR    ( ( దొంతర_Type_t ) 0x00000000 )
#నిర్వచించు పోర్టు_INITIAL_DECNT   ( ( దొంతర_Type_t ) 0x00000001 )

/* Tasks are not created with a DPFPU context, but can be given a DPFPU context
 * after they have been created.  A variable is stored as part of the tasks context
 * that holds portNO_DPFPU_CONTEXT if the task does not have a DPFPU context, or
 * any other value if the task does have a DPFPU context. */
#నిర్వచించు పోర్టు_NO_DPFPU_CONTEXT    ( ( దొంతర_Type_t ) 0 )
#నిర్వచించు పోర్టు_HAS_DPFPU_CONTEXT   ( ( దొంతర_Type_t ) 1 )

/* The space on the stack required to hold the DPFPU data registers.  This is 16
 * 64-bit registers. */
#నిర్వచించు పోర్టు_DPFPU_దత్తాంశం_రిజిస్టరు_పదాలు   ( 16 * 2 )

/*-----------------------------------------------------------*/

/* The following lines are to ensure vSoftwareInterruptEntry can be referenced,
 * and therefore installed in the vector table, when the FreeRTOS code is built
 * as a library. */
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

/*
 * The tick ISR handler.  The peripheral used is configured by the application
 * via a hook/callback function.
 */
శూన్య vTickISR( శూన్య );

/*-----------------------------------------------------------*/

/* Saved as part of the task context.  If ulPortTaskHasDPFPUContext is non-zero
 * then a DPFPU context must be saved and restored for the task. */
#ఒకవేళ ( configUSE_TASK_DPFPU_SUPPORT == 1 )

    దొంతర_Type_t ul_పోర్టు_Task_Has_DPFPUContext = పోర్టు_NO_DPFPU_CONTEXT;

#అయితే_ముగింపు /* configUSE_TASK_DPFPU_SUPPORT */

/* This is accessed by the inline assembler functions so is file scope for
 * convenience. */
బాహ్య శూన్య * pxCurrentTCB;
బాహ్య శూన్య vTaskSwitchContext( శూన్య );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    /* R0 is not included as it is the stack pointer. */

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
    #లేకపోతే /* ifdef USE_FULL_REGISTER_INITIALISATION */
        {
            px_శిఖరం_యొక్క_దొంతర -= 15;
        }
    #అయితే_ముగింపు /* ifdef USE_FULL_REGISTER_INITIALISATION */

    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters; /* R1 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_FPSW;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x11111111; /* Accumulator 1. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x22222222; /* Accumulator 1. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x33333333; /* Accumulator 1. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x44444444; /* Accumulator 0. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x55555555; /* Accumulator 0. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x66666666; /* Accumulator 0. */

    #ఒకవేళ ( configUSE_TASK_DPFPU_SUPPORT == 1 )
        {
            /* The task will start without a DPFPU context.  A task that
             * uses the DPFPU hardware must call vPortTaskUsesDPFPU() before
             * executing any floating point instructions. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = పోర్టు_NO_DPFPU_CONTEXT;
        }
    #లేదావేళ ( configUSE_TASK_DPFPU_SUPPORT == 2 )
        {
            /* The task will start with a DPFPU context.  Leave enough
             * space for the registers - and ensure they are initialised if desired. */
            #నిర్వచితమైతే USE_నిండిన_రిజిస్టరు_INITIALISATION
                {
                    px_శిఖరం_యొక్క_దొంతర -= 2;
                    *(ద్విగుణ *)px_శిఖరం_యొక్క_దొంతర = 1515.1515; /* DR15. */
                    px_శిఖరం_యొక్క_దొంతర -= 2;
                    *(ద్విగుణ *)px_శిఖరం_యొక్క_దొంతర = 1414.1414; /* DR14. */
                    px_శిఖరం_యొక్క_దొంతర -= 2;
                    *(ద్విగుణ *)px_శిఖరం_యొక్క_దొంతర = 1313.1313; /* DR13. */
                    px_శిఖరం_యొక్క_దొంతర -= 2;
                    *(ద్విగుణ *)px_శిఖరం_యొక్క_దొంతర = 1212.1212; /* DR12. */
                    px_శిఖరం_యొక్క_దొంతర -= 2;
                    *(ద్విగుణ *)px_శిఖరం_యొక్క_దొంతర = 1111.1111; /* DR11. */
                    px_శిఖరం_యొక్క_దొంతర -= 2;
                    *(ద్విగుణ *)px_శిఖరం_యొక్క_దొంతర = 1010.1010; /* DR10. */
                    px_శిఖరం_యొక్క_దొంతర -= 2;
                    *(ద్విగుణ *)px_శిఖరం_యొక్క_దొంతర =  909.0909; /* DR9. */
                    px_శిఖరం_యొక్క_దొంతర -= 2;
                    *(ద్విగుణ *)px_శిఖరం_యొక్క_దొంతర =  808.0808; /* DR8. */
                    px_శిఖరం_యొక్క_దొంతర -= 2;
                    *(ద్విగుణ *)px_శిఖరం_యొక్క_దొంతర =  707.0707; /* DR7. */
                    px_శిఖరం_యొక్క_దొంతర -= 2;
                    *(ద్విగుణ *)px_శిఖరం_యొక్క_దొంతర =  606.0606; /* DR6. */
                    px_శిఖరం_యొక్క_దొంతర -= 2;
                    *(ద్విగుణ *)px_శిఖరం_యొక్క_దొంతర =  505.0505; /* DR5. */
                    px_శిఖరం_యొక్క_దొంతర -= 2;
                    *(ద్విగుణ *)px_శిఖరం_యొక్క_దొంతర =  404.0404; /* DR4. */
                    px_శిఖరం_యొక్క_దొంతర -= 2;
                    *(ద్విగుణ *)px_శిఖరం_యొక్క_దొంతర =  303.0303; /* DR3. */
                    px_శిఖరం_యొక్క_దొంతర -= 2;
                    *(ద్విగుణ *)px_శిఖరం_యొక్క_దొంతర =  202.0202; /* DR2. */
                    px_శిఖరం_యొక్క_దొంతర -= 2;
                    *(ద్విగుణ *)px_శిఖరం_యొక్క_దొంతర =  101.0101; /* DR1. */
                    px_శిఖరం_యొక్క_దొంతర -= 2;
                    *(ద్విగుణ *)px_శిఖరం_యొక్క_దొంతర = 9876.54321;/* DR0. */
                }
            #లేకపోతే /* ifdef USE_FULL_REGISTER_INITIALISATION */
                {
                    px_శిఖరం_యొక్క_దొంతర -= పోర్టు_DPFPU_దత్తాంశం_రిజిస్టరు_పదాలు;
                    memset( px_శిఖరం_యొక్క_దొంతర, 0x00, పోర్టు_DPFPU_దత్తాంశం_రిజిస్టరు_పదాలు * పరిమాణం( దొంతర_Type_t ) );
                }
            #అయితే_ముగింపు /* ifdef USE_FULL_REGISTER_INITIALISATION */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_DECNT; /* DECNT. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_DCMR;  /* DCMR. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_DPSW;  /* DPSW. */
        }
    #లేదావేళ ( configUSE_TASK_DPFPU_SUPPORT == 0 )
        {
            /* Omit DPFPU support. */
        }
    #లేకపోతే /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */
        {
            #దోషం Invalid configUSE_TASK_DPFPU_SUPPORT setting - configUSE_TASK_DPFPU_SUPPORT must be సమితి గమ్యం 0, 1, 2, or ఎడమ undefined.
        }
    #అయితే_ముగింపు /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TASK_DPFPU_SUPPORT == 1 )

    శూన్య v_పోర్టు_Task_ఉపయోగిస్తుంది_DPFPU( శూన్య )
    {
        /* A task is registering the fact that it needs a DPFPU context.  Set the
         * DPFPU flag (which is saved as part of the task context). */
        ul_పోర్టు_Task_Has_DPFPUContext = పోర్టు_HAS_DPFPU_CONTEXT;
    }

#అయితే_ముగింపు /* configUSE_TASK_DPFPU_SUPPORT */
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    బాహ్య శూన్య v_Application_అమరిక_Timer_అంతరాయం( శూన్య );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    ఒకవేళ( pxCurrentTCB != ఖాళీ )
    {
        /* Call an application function to set up the timer that will generate the
         * tick interrupt.  This way the application can decide which peripheral to
         * use.  A demo application is provided to show a suitable example. */
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

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pxCurrentTCB == ఖాళీ );

    /* The following line is just to prevent the symbol getting optimised away. */
    ( శూన్య ) vTaskSwitchContext();
}
/*-----------------------------------------------------------*/

#సూచన inline_asm prv_ప్రారంభం_మొదటి_Task
స్థిర శూన్య prv_ప్రారంభం_మొదటి_Task( శూన్య )
{
#నిర్వచితం_కాకపోతే __CDT_PARSER__

    /* When starting the scheduler there is nothing that needs moving to the
     * interrupt stack because the function is not called from an interrupt.
     * Just ensure the current stack is the user stack. */
    SETPSW U


    /* Obtain the location of the stack associated with which ever task
     * pxCurrentTCB is currently pointing to. */
    MOV.L # _pxCurrentTCB, R15
    MOV.L [ R15 ], R15
    MOV.L [ R15 ], R0


    /* Restore the registers from the stack of the task pointed to by
     * pxCurrentTCB. */

    #ఒకవేళ ( configUSE_TASK_DPFPU_SUPPORT == 1 )

        /* The restored ulPortTaskHasDPFPUContext is to be zero here.
         * So, it is never necessary to restore the DPFPU context here. */
        తీయి_2 R15
        MOV.L # ul_పోర్టు_Task_Has_DPFPUContext_2, R14
        MOV.L R15, [ R14 ]

    #లేదావేళ ( configUSE_TASK_DPFPU_SUPPORT == 2 )

        /* Restore the DPFPU context. */
        DPOPM.L DPSW-DECNT
        DPOPM.D DR0-DR15

    #అయితే_ముగింపు /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */

    తీయి_2 R15

    /* Accumulator low 32 bits. */
    MVTACLO R15, A0
    తీయి_2 R15

    /* Accumulator high 32 bits. */
    MVTACHI R15, A0
    తీయి_2 R15

    /* Accumulator guard. */
    MVTACGU R15, A0
    తీయి_2 R15

    /* Accumulator low 32 bits. */
    MVTACLO R15, A1
    తీయి_2 R15

    /* Accumulator high 32 bits. */
    MVTACHI R15, A1
    తీయి_2 R15

    /* Accumulator guard. */
    MVTACGU R15, A1
    తీయి_2 R15

    /* Floating point status word. */
    MVTC R15, FPSW

    /* R1 to R15 - R0 is not included as it is the SP. */
    POPM R1-R15

    /* This pops the remaining registers. */
    RTE
    NOP
    NOP

#అయితే_ముగింపు /* ifndef __CDT_PARSER__ */
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
#నిర్వచితం_కాకపోతే __CDT_PARSER__

    /* Re-enable interrupts. */
    SETPSW I


    /* Move the data that was automatically pushed onto the interrupt stack when
     * the interrupt occurred from the interrupt stack to the user stack.
     *
     * R15 is saved before it is clobbered. */
    నెట్టు_2.L R15

    /* Read the user stack pointer. */
    MVFC USP, R15

    /* Move the address down to the data being moved. */
    SUB # 12, R15
    MVTC R15, USP

    /* Copy the data across, R15, then PC, then PSW. */
    MOV.L [ R0 ], [ R15 ]
    MOV.L 4[ R0 ], 4[ R15 ]
    MOV.L 8[ R0 ], 8[ R15 ]

    /* Move the interrupt stack pointer to its new correct position. */
    కూడు_2 # 12, R0

    /* All the rest of the registers are saved directly to the user stack. */
    SETPSW U

    /* Save the rest of the general registers (R15 has been saved already). */
    PUSHM R1-R14

    /* Save the FPSW and accumulators. */
    MVFC FPSW, R15
    నెట్టు_2.L R15
    MVFACGU # 0, A1, R15
    నెట్టు_2.L R15
    MVFACHI # 0, A1, R15
    నెట్టు_2.L R15
    MVFACLO # 0, A1, R15 /* Low order word. */
    నెట్టు_2.L R15
    MVFACGU # 0, A0, R15
    నెట్టు_2.L R15
    MVFACHI # 0, A0, R15
    నెట్టు_2.L R15
    MVFACLO # 0, A0, R15 /* Low order word. */
    నెట్టు_2.L R15

    #ఒకవేళ ( configUSE_TASK_DPFPU_SUPPORT == 1 )

        /* Does the task have a DPFPU context that needs saving?  If
         * ulPortTaskHasDPFPUContext is 0 then no. */
        MOV.L # ul_పోర్టు_Task_Has_DPFPUContext_2, R15
        MOV.L [ R15 ], R15
        CMP # 0, R15

        /* Save the DPFPU context, if any. */
        BEQ.B ?+
        DPUSHM.D DR0-DR15
        DPUSHM.L DPSW-DECNT
        ?:

        /* Save ulPortTaskHasDPFPUContext itself. */
        నెట్టు_2.L R15

    #లేదావేళ ( configUSE_TASK_DPFPU_SUPPORT == 2 )

        /* Save the DPFPU context, always. */
        DPUSHM.D DR0-DR15
        DPUSHM.L DPSW-DECNT

    #అయితే_ముగింపు /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */


    /* Save the stack pointer to the TCB. */
    MOV.L # _pxCurrentTCB, R15
    MOV.L [ R15 ], R15
    MOV.L R0, [ R15 ]


    /* Ensure the interrupt mask is set to the syscall priority while the kernel
     * structures are being accessed. */
    MVTIPL # config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత

    /* Select the next task to run. */
    BSR.A _vTaskSwitchContext

    /* Reset the interrupt mask as no more data structure access is required. */
    MVTIPL # config_KERNEL_అంతరాయం_ప్రాధాన్యత


    /* Load the stack pointer of the task that is now selected as the Running
     * state task from its TCB. */
    MOV.L # _pxCurrentTCB, R15
    MOV.L [ R15 ], R15
    MOV.L [ R15 ], R0


    /* Restore the context of the new task.  The PSW (Program Status Word) and
     * PC will be popped by the RTE instruction. */

    #ఒకవేళ ( configUSE_TASK_DPFPU_SUPPORT == 1 )

        /* Is there a DPFPU context to restore?  If the restored
         * ulPortTaskHasDPFPUContext is zero then no. */
        తీయి_2 R15
        MOV.L # ul_పోర్టు_Task_Has_DPFPUContext_2, R14
        MOV.L R15, [ R14 ]
        CMP # 0, R15

        /* Restore the DPFPU context, if any. */
        BEQ.B ?+
        DPOPM.L DPSW-DECNT
        DPOPM.D DR0-DR15
        ?:

    #లేదావేళ ( configUSE_TASK_DPFPU_SUPPORT == 2 )

        /* Restore the DPFPU context, always. */
        DPOPM.L DPSW-DECNT
        DPOPM.D DR0-DR15

    #అయితే_ముగింపు /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */

    తీయి_2 R15

    /* Accumulator low 32 bits. */
    MVTACLO R15, A0
    తీయి_2 R15

    /* Accumulator high 32 bits. */
    MVTACHI R15, A0
    తీయి_2 R15

    /* Accumulator guard. */
    MVTACGU R15, A0
    తీయి_2 R15

    /* Accumulator low 32 bits. */
    MVTACLO R15, A1
    తీయి_2 R15

    /* Accumulator high 32 bits. */
    MVTACHI R15, A1
    తీయి_2 R15

    /* Accumulator guard. */
    MVTACGU R15, A1
    తీయి_2 R15
    MVTC R15, FPSW
    POPM R1-R15
    RTE
    NOP
    NOP

#అయితే_ముగింపు /* ifndef __CDT_PARSER__ */
}
/*-----------------------------------------------------------*/

#సూచన అంతరాయం ( vTickISR( vect = _VECT( config_TICK_సదిశ ), enable ) )
శూన్య vTickISR( శూన్య )
{
    /* Increment the tick, and perform any processing the new tick value
     * necessitates.  Ensure IPL is at the max syscall value first. */
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
