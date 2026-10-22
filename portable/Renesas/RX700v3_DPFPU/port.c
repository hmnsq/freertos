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

#warning Testing প্রতি DFPU support in this port is not yet complete

/* Scheduler includes. */
#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "task.h"

/* Library includes. */
#অন্তর্ভাব "string.h"

/* Hardware specifics. */
#যদি ( configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H == 1 )

    #অন্তর্ভাব "platform.h"

#অন্যথা /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

    #অন্তর্ভাব "iodefine.h"

#endif /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
 * PSW is set with U and I set, and PM and IPL clear. */
#define portINITIAL_PSW     ( ( স্তূপ_Type_t ) 0x00030000 )
#define portINITIAL_FPSW    ( ( স্তূপ_Type_t ) 0x00000100 )
#define portINITIAL_DPSW    ( ( স্তূপ_Type_t ) 0x00000100 )
#define portINITIAL_DCMR    ( ( স্তূপ_Type_t ) 0x00000000 )
#define portINITIAL_DECNT   ( ( স্তূপ_Type_t ) 0x00000001 )

/* Tasks are not created with a DPFPU context, but can be given a DPFPU context
 * after they have been created.  A variable is stored as part of the tasks context
 * that holds portNO_DPFPU_CONTEXT if the task does not have a DPFPU context, or
 * any other value if the task does have a DPFPU context. */
#define portNO_DPFPU_CONTEXT    ( ( স্তূপ_Type_t ) 0 )
#define portHAS_DPFPU_CONTEXT   ( ( স্তূপ_Type_t ) 1 )

/* The space on the stack required to hold the DPFPU data registers.  This is 16
 * 64-bit registers. */
#define port_DPFPU_DATA_REGISTER_শব্দগুলি   ( 16 * 2 )

/*-----------------------------------------------------------*/

/* The following lines are to ensure vSoftwareInterruptEntry can be referenced,
 * and therefore installed in the vector table, when the FreeRTOS code is built
 * as a library. */
বাহ্য BaseType_t vSoftwareInterruptEntry;
ধ্রুব BaseType_t * p_vSoftwareInterruptEntry = &vSoftwareInterruptEntry;

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
স্থির শূন্য prvStartFirstTask( শূন্য );

/*
 * Software interrupt handler.  Performs the actual context switch (saving and
 * restoring of registers).  Written in asm code as direct register access is
 * required.
 */
স্থির শূন্য prvYieldHandler( শূন্য );

/*
 * The entry point for the software interrupt handler.  This is the function
 * that calls the inline asm function prvYieldHandler().  It is installed in
 * the vector table, but the code that installs it is in prvYieldHandler rather
 * than using a #pragma.
 */
শূন্য vSoftwareInterruptISR( শূন্য );

/*
 * The tick ISR handler.  The peripheral used is configured by the application
 * via a hook/callback function.
 */
শূন্য vTickISR( শূন্য );

/*-----------------------------------------------------------*/

/* Saved as part of the task context.  If ulPortTaskHasDPFPUContext is non-zero
 * then a DPFPU context must be saved and restored for the task. */
#যদি ( configUSE_TASK_DPFPU_SUPPORT == 1 )

    স্তূপ_Type_t ulPortTaskHasDPFPUContext = portNO_DPFPU_CONTEXT;

#endif /* configUSE_TASK_DPFPU_SUPPORT */

/* This is accessed by the inline assembler functions so is file scope for
 * convenience. */
বাহ্য শূন্য * pxCurrentTCB;
বাহ্য শূন্য vTaskSwitchContext( শূন্য );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
স্তূপ_Type_t * px_Port_Initialise_স্তূপ( স্তূপ_Type_t * px_শীর্ষ_Of_স্তূপ,
                                     TaskFunction_t pxCode,
                                     শূন্য * pvParameters )
{
    /* R0 is not included as it is the stack pointer. */

    *px_শীর্ষ_Of_স্তূপ = 0x00;
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = portINITIAL_PSW;
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) pxCode;

    /* When debugging it can be useful if every register is set to a known
     * value.  Otherwise code space can be saved by just setting the registers
     * that need to be set. */
    #ifdef USE_FULL_REGISTER_INITIALISATION
        {
            px_শীর্ষ_Of_স্তূপ--;
            *px_শীর্ষ_Of_স্তূপ = 0xffffffff; /* r15. */
            px_শীর্ষ_Of_স্তূপ--;
            *px_শীর্ষ_Of_স্তূপ = 0xeeeeeeee;
            px_শীর্ষ_Of_স্তূপ--;
            *px_শীর্ষ_Of_স্তূপ = 0xdddddddd;
            px_শীর্ষ_Of_স্তূপ--;
            *px_শীর্ষ_Of_স্তূপ = 0xcccccccc;
            px_শীর্ষ_Of_স্তূপ--;
            *px_শীর্ষ_Of_স্তূপ = 0xbbbbbbbb;
            px_শীর্ষ_Of_স্তূপ--;
            *px_শীর্ষ_Of_স্তূপ = 0xaaaaaaaa;
            px_শীর্ষ_Of_স্তূপ--;
            *px_শীর্ষ_Of_স্তূপ = 0x99999999;
            px_শীর্ষ_Of_স্তূপ--;
            *px_শীর্ষ_Of_স্তূপ = 0x88888888;
            px_শীর্ষ_Of_স্তূপ--;
            *px_শীর্ষ_Of_স্তূপ = 0x77777777;
            px_শীর্ষ_Of_স্তূপ--;
            *px_শীর্ষ_Of_স্তূপ = 0x66666666;
            px_শীর্ষ_Of_স্তূপ--;
            *px_শীর্ষ_Of_স্তূপ = 0x55555555;
            px_শীর্ষ_Of_স্তূপ--;
            *px_শীর্ষ_Of_স্তূপ = 0x44444444;
            px_শীর্ষ_Of_স্তূপ--;
            *px_শীর্ষ_Of_স্তূপ = 0x33333333;
            px_শীর্ষ_Of_স্তূপ--;
            *px_শীর্ষ_Of_স্তূপ = 0x22222222;
            px_শীর্ষ_Of_স্তূপ--;
        }
    #অন্যথা /* ifdef USE_FULL_REGISTER_INITIALISATION */
        {
            px_শীর্ষ_Of_স্তূপ -= 15;
        }
    #endif /* ifdef USE_FULL_REGISTER_INITIALISATION */

    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) pvParameters; /* R1 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = portINITIAL_FPSW;
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = 0x11111111; /* Accumulator 1. */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = 0x22222222; /* Accumulator 1. */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = 0x33333333; /* Accumulator 1. */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = 0x44444444; /* Accumulator 0. */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = 0x55555555; /* Accumulator 0. */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = 0x66666666; /* Accumulator 0. */

    #যদি ( configUSE_TASK_DPFPU_SUPPORT == 1 )
        {
            /* The task will start without a DPFPU context.  A task that
             * uses the DPFPU hardware must call vPortTaskUsesDPFPU() before
             * executing any floating point instructions. */
            px_শীর্ষ_Of_স্তূপ--;
            *px_শীর্ষ_Of_স্তূপ = portNO_DPFPU_CONTEXT;
        }
    #নোচেদ্যদি ( configUSE_TASK_DPFPU_SUPPORT == 2 )
        {
            /* The task will start with a DPFPU context.  Leave enough
             * space for the registers - and ensure they are initialised if desired. */
            #ifdef USE_FULL_REGISTER_INITIALISATION
                {
                    px_শীর্ষ_Of_স্তূপ -= 2;
                    *(দ্বিগুণ *)px_শীর্ষ_Of_স্তূপ = 1515.1515; /* DR15. */
                    px_শীর্ষ_Of_স্তূপ -= 2;
                    *(দ্বিগুণ *)px_শীর্ষ_Of_স্তূপ = 1414.1414; /* DR14. */
                    px_শীর্ষ_Of_স্তূপ -= 2;
                    *(দ্বিগুণ *)px_শীর্ষ_Of_স্তূপ = 1313.1313; /* DR13. */
                    px_শীর্ষ_Of_স্তূপ -= 2;
                    *(দ্বিগুণ *)px_শীর্ষ_Of_স্তূপ = 1212.1212; /* DR12. */
                    px_শীর্ষ_Of_স্তূপ -= 2;
                    *(দ্বিগুণ *)px_শীর্ষ_Of_স্তূপ = 1111.1111; /* DR11. */
                    px_শীর্ষ_Of_স্তূপ -= 2;
                    *(দ্বিগুণ *)px_শীর্ষ_Of_স্তূপ = 1010.1010; /* DR10. */
                    px_শীর্ষ_Of_স্তূপ -= 2;
                    *(দ্বিগুণ *)px_শীর্ষ_Of_স্তূপ =  909.0909; /* DR9. */
                    px_শীর্ষ_Of_স্তূপ -= 2;
                    *(দ্বিগুণ *)px_শীর্ষ_Of_স্তূপ =  808.0808; /* DR8. */
                    px_শীর্ষ_Of_স্তূপ -= 2;
                    *(দ্বিগুণ *)px_শীর্ষ_Of_স্তূপ =  707.0707; /* DR7. */
                    px_শীর্ষ_Of_স্তূপ -= 2;
                    *(দ্বিগুণ *)px_শীর্ষ_Of_স্তূপ =  606.0606; /* DR6. */
                    px_শীর্ষ_Of_স্তূপ -= 2;
                    *(দ্বিগুণ *)px_শীর্ষ_Of_স্তূপ =  505.0505; /* DR5. */
                    px_শীর্ষ_Of_স্তূপ -= 2;
                    *(দ্বিগুণ *)px_শীর্ষ_Of_স্তূপ =  404.0404; /* DR4. */
                    px_শীর্ষ_Of_স্তূপ -= 2;
                    *(দ্বিগুণ *)px_শীর্ষ_Of_স্তূপ =  303.0303; /* DR3. */
                    px_শীর্ষ_Of_স্তূপ -= 2;
                    *(দ্বিগুণ *)px_শীর্ষ_Of_স্তূপ =  202.0202; /* DR2. */
                    px_শীর্ষ_Of_স্তূপ -= 2;
                    *(দ্বিগুণ *)px_শীর্ষ_Of_স্তূপ =  101.0101; /* DR1. */
                    px_শীর্ষ_Of_স্তূপ -= 2;
                    *(দ্বিগুণ *)px_শীর্ষ_Of_স্তূপ = 9876.54321;/* DR0. */
                }
            #অন্যথা /* ifdef USE_FULL_REGISTER_INITIALISATION */
                {
                    px_শীর্ষ_Of_স্তূপ -= port_DPFPU_DATA_REGISTER_শব্দগুলি;
                    memset( px_শীর্ষ_Of_স্তূপ, 0x00, port_DPFPU_DATA_REGISTER_শব্দগুলি * পরিমাণ( স্তূপ_Type_t ) );
                }
            #endif /* ifdef USE_FULL_REGISTER_INITIALISATION */
            px_শীর্ষ_Of_স্তূপ--;
            *px_শীর্ষ_Of_স্তূপ = portINITIAL_DECNT; /* DECNT. */
            px_শীর্ষ_Of_স্তূপ--;
            *px_শীর্ষ_Of_স্তূপ = portINITIAL_DCMR;  /* DCMR. */
            px_শীর্ষ_Of_স্তূপ--;
            *px_শীর্ষ_Of_স্তূপ = portINITIAL_DPSW;  /* DPSW. */
        }
    #নোচেদ্যদি ( configUSE_TASK_DPFPU_SUPPORT == 0 )
        {
            /* Omit DPFPU support. */
        }
    #অন্যথা /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */
        {
            #error Invalid configUSE_TASK_DPFPU_SUPPORT setting - configUSE_TASK_DPFPU_SUPPORT must be set to 0, 1, 2, or বাম undefined.
        }
    #endif /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */

    প্রত্যাগম px_শীর্ষ_Of_স্তূপ;
}
/*-----------------------------------------------------------*/

#যদি ( configUSE_TASK_DPFPU_SUPPORT == 1 )

    শূন্য vPortTaskUsesDPFPU( শূন্য )
    {
        /* A task is registering the fact that it needs a DPFPU context.  Set the
         * DPFPU flag (which is saved as part of the task context). */
        ulPortTaskHasDPFPUContext = portHAS_DPFPU_CONTEXT;
    }

#endif /* configUSE_TASK_DPFPU_SUPPORT */
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( শূন্য )
{
    বাহ্য শূন্য vApplicationSetupTimerInterrupt( শূন্য );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    যদি( pxCurrentTCB != রিক্ত )
    {
        /* Call an application function to set up the timer that will generate the
         * tick interrupt.  This way the application can decide which peripheral to
         * use.  A demo application is provided to show a suitable example. */
        vApplicationSetupTimerInterrupt();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = configKERNEL_INTERRUPT_PRIORITY;

        /* Start the first task. */
        prvStartFirstTask();
    }

    /* Just to make sure the function is not optimised away. */
    ( শূন্য ) vSoftwareInterruptISR();

    /* Should not get here. */
    প্রত্যাগম pdFAIL;
}
/*-----------------------------------------------------------*/

শূন্য vPortEndScheduler( শূন্য )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pxCurrentTCB == রিক্ত );

    /* The following line is just to prevent the symbol getting optimised away. */
    ( শূন্য ) vTaskSwitchContext();
}
/*-----------------------------------------------------------*/

#pragma inline_asm prvStartFirstTask
স্থির শূন্য prvStartFirstTask( শূন্য )
{
#ifndef __CDT_PARSER__

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

    #যদি ( configUSE_TASK_DPFPU_SUPPORT == 1 )

        /* The restored ulPortTaskHasDPFPUContext is to be zero here.
         * So, it is never necessary to restore the DPFPU context here. */
        বের_করো_2 R15
        MOV.L # _ulPortTaskHasDPFPUContext, R14
        MOV.L R15, [ R14 ]

    #নোচেদ্যদি ( configUSE_TASK_DPFPU_SUPPORT == 2 )

        /* Restore the DPFPU context. */
        DPOPM.L DPSW-DECNT
        DPOPM.D DR0-DR15

    #endif /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */

    বের_করো_2 R15

    /* Accumulator low 32 bits. */
    MVTACLO R15, A0
    বের_করো_2 R15

    /* Accumulator high 32 bits. */
    MVTACHI R15, A0
    বের_করো_2 R15

    /* Accumulator guard. */
    MVTACGU R15, A0
    বের_করো_2 R15

    /* Accumulator low 32 bits. */
    MVTACLO R15, A1
    বের_করো_2 R15

    /* Accumulator high 32 bits. */
    MVTACHI R15, A1
    বের_করো_2 R15

    /* Accumulator guard. */
    MVTACGU R15, A1
    বের_করো_2 R15

    /* Floating point status word. */
    MVTC R15, FPSW

    /* R1 to R15 - R0 is not included as it is the SP. */
    POPM R1-R15

    /* This pops the remaining registers. */
    RTE
    NOP
    NOP

#endif /* ifndef __CDT_PARSER__ */
}
/*-----------------------------------------------------------*/

শূন্য vSoftwareInterruptISR( শূন্য )
{
    prvYieldHandler();
}
/*-----------------------------------------------------------*/

#pragma inline_asm prvYieldHandler
স্থির শূন্য prvYieldHandler( শূন্য )
{
#ifndef __CDT_PARSER__

    /* Re-enable interrupts. */
    SETPSW I


    /* Move the data that was automatically pushed onto the interrupt stack when
     * the interrupt occurred from the interrupt stack to the user stack.
     *
     * R15 is saved before it is clobbered. */
    ঠেলো_2.L R15

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
    ADD # 12, R0

    /* All the rest of the registers are saved directly to the user stack. */
    SETPSW U

    /* Save the rest of the general registers (R15 has been saved already). */
    PUSHM R1-R14

    /* Save the FPSW and accumulators. */
    MVFC FPSW, R15
    ঠেলো_2.L R15
    MVFACGU # 0, A1, R15
    ঠেলো_2.L R15
    MVFACHI # 0, A1, R15
    ঠেলো_2.L R15
    MVFACLO # 0, A1, R15 /* Low order word. */
    ঠেলো_2.L R15
    MVFACGU # 0, A0, R15
    ঠেলো_2.L R15
    MVFACHI # 0, A0, R15
    ঠেলো_2.L R15
    MVFACLO # 0, A0, R15 /* Low order word. */
    ঠেলো_2.L R15

    #যদি ( configUSE_TASK_DPFPU_SUPPORT == 1 )

        /* Does the task have a DPFPU context that needs saving?  If
         * ulPortTaskHasDPFPUContext is 0 then no. */
        MOV.L # _ulPortTaskHasDPFPUContext, R15
        MOV.L [ R15 ], R15
        CMP # 0, R15

        /* Save the DPFPU context, if any. */
        BEQ.B ?+
        DPUSHM.D DR0-DR15
        DPUSHM.L DPSW-DECNT
        ?:

        /* Save ulPortTaskHasDPFPUContext itself. */
        ঠেলো_2.L R15

    #নোচেদ্যদি ( configUSE_TASK_DPFPU_SUPPORT == 2 )

        /* Save the DPFPU context, always. */
        DPUSHM.D DR0-DR15
        DPUSHM.L DPSW-DECNT

    #endif /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */


    /* Save the stack pointer to the TCB. */
    MOV.L # _pxCurrentTCB, R15
    MOV.L [ R15 ], R15
    MOV.L R0, [ R15 ]


    /* Ensure the interrupt mask is set to the syscall priority while the kernel
     * structures are being accessed. */
    MVTIPL # configMAX_SYSCALL_INTERRUPT_PRIORITY

    /* Select the next task to run. */
    BSR.A _vTaskSwitchContext

    /* Reset the interrupt mask as no more data structure access is required. */
    MVTIPL # configKERNEL_INTERRUPT_PRIORITY


    /* Load the stack pointer of the task that is now selected as the Running
     * state task from its TCB. */
    MOV.L # _pxCurrentTCB, R15
    MOV.L [ R15 ], R15
    MOV.L [ R15 ], R0


    /* Restore the context of the new task.  The PSW (Program Status Word) and
     * PC will be popped by the RTE instruction. */

    #যদি ( configUSE_TASK_DPFPU_SUPPORT == 1 )

        /* Is there a DPFPU context to restore?  If the restored
         * ulPortTaskHasDPFPUContext is zero then no. */
        বের_করো_2 R15
        MOV.L # _ulPortTaskHasDPFPUContext, R14
        MOV.L R15, [ R14 ]
        CMP # 0, R15

        /* Restore the DPFPU context, if any. */
        BEQ.B ?+
        DPOPM.L DPSW-DECNT
        DPOPM.D DR0-DR15
        ?:

    #নোচেদ্যদি ( configUSE_TASK_DPFPU_SUPPORT == 2 )

        /* Restore the DPFPU context, always. */
        DPOPM.L DPSW-DECNT
        DPOPM.D DR0-DR15

    #endif /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */

    বের_করো_2 R15

    /* Accumulator low 32 bits. */
    MVTACLO R15, A0
    বের_করো_2 R15

    /* Accumulator high 32 bits. */
    MVTACHI R15, A0
    বের_করো_2 R15

    /* Accumulator guard. */
    MVTACGU R15, A0
    বের_করো_2 R15

    /* Accumulator low 32 bits. */
    MVTACLO R15, A1
    বের_করো_2 R15

    /* Accumulator high 32 bits. */
    MVTACHI R15, A1
    বের_করো_2 R15

    /* Accumulator guard. */
    MVTACGU R15, A1
    বের_করো_2 R15
    MVTC R15, FPSW
    POPM R1-R15
    RTE
    NOP
    NOP

#endif /* ifndef __CDT_PARSER__ */
}
/*-----------------------------------------------------------*/

#pragma interrupt ( vTickISR( vect = _VECT( configTICK_VECTOR ), enable ) )
শূন্য vTickISR( শূন্য )
{
    /* Increment the tick, and perform any processing the new tick value
     * necessitates.  Ensure IPL is at the max syscall value first. */
    set_ipl( configMAX_SYSCALL_INTERRUPT_PRIORITY );
    {
        যদি( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    set_ipl( configKERNEL_INTERRUPT_PRIORITY );
}
/*-----------------------------------------------------------*/
