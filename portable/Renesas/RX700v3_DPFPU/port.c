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

#warning Testing لكل DFPU support اندريون this پورٽ is not yet complete

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Library includes. */
#ضمن "string.h"

/* Hardware specifics. */
#إذا ( config_INCLUDE_PLATFORM_H_INSTEAD_جو_IODEFINE_H == 1 )

    #ضمن "platform.h"

#وإلا /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

    #ضمن "iodefine.h"

#جيڪڏهن_پورو /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
 * PSW is set with U and I set, and PM and IPL clear. */
#وصف_ڪريو پورٽ_INITIAL_PSW     ( ( ڍير_Type_t ) 0x00030000 )
#وصف_ڪريو پورٽ_INITIAL_FPSW    ( ( ڍير_Type_t ) 0x00000100 )
#وصف_ڪريو پورٽ_INITIAL_DPSW    ( ( ڍير_Type_t ) 0x00000100 )
#وصف_ڪريو پورٽ_INITIAL_DCMR    ( ( ڍير_Type_t ) 0x00000000 )
#وصف_ڪريو پورٽ_INITIAL_DECNT   ( ( ڍير_Type_t ) 0x00000001 )

/* Tasks are not created with a DPFPU context, but can be given a DPFPU context
 * after they have been created.  A variable is stored as part of the tasks context
 * that holds portNO_DPFPU_CONTEXT if the task does not have a DPFPU context, or
 * any other value if the task does have a DPFPU context. */
#وصف_ڪريو پورٽ_NO_DPFPU_CONTEXT    ( ( ڍير_Type_t ) 0 )
#وصف_ڪريو پورٽ_HAS_DPFPU_CONTEXT   ( ( ڍير_Type_t ) 1 )

/* The space on the stack required to hold the DPFPU data registers.  This is 16
 * 64-bit registers. */
#وصف_ڪريو پورٽ_DPFPU_معلومات_رجسٽر_لفظ   ( 16 * 2 )

/*-----------------------------------------------------------*/

/* The following lines are to ensure vSoftwareInterruptEntry can be referenced,
 * and therefore installed in the vector table, when the FreeRTOS code is built
 * as a library. */
خارجي بنياد_Type_t v_Software_مداخلت_داخلا;
ثابت بنياد_Type_t * p_v_Software_مداخلت_داخلا = &v_Software_مداخلت_داخلا;

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
ساكن فراغ prv_شروعات_پهريون_Task( فراغ );

/*
 * Software interrupt handler.  Performs the actual context switch (saving and
 * restoring of registers).  Written in asm code as direct register access is
 * required.
 */
ساكن فراغ prvYieldHandler( فراغ );

/*
 * The entry point for the software interrupt handler.  This is the function
 * that calls the inline asm function prvYieldHandler().  It is installed in
 * the vector table, but the code that installs it is in prvYieldHandler rather
 * than using a #pragma.
 */
فراغ v_Software_مداخلت_ISR( فراغ );

/*
 * The tick ISR handler.  The peripheral used is configured by the application
 * via a hook/callback function.
 */
فراغ vTickISR( فراغ );

/*-----------------------------------------------------------*/

/* Saved as part of the task context.  If ulPortTaskHasDPFPUContext is non-zero
 * then a DPFPU context must be saved and restored for the task. */
#إذا ( configUSE_TASK_DPFPU_SUPPORT == 1 )

    ڍير_Type_t ul_پورٽ_Task_Has_DPFPUContext = پورٽ_NO_DPFPU_CONTEXT;

#جيڪڏهن_پورو /* configUSE_TASK_DPFPU_SUPPORT */

/* This is accessed by the inline assembler functions so is file scope for
 * convenience. */
خارجي فراغ * pxCurrentTCB;
خارجي فراغ vTaskSwitchContext( فراغ );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    /* R0 is not included as it is the stack pointer. */

    *px_چوٽي_جو_ڍير = 0x00;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = پورٽ_INITIAL_PSW;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) px_ڪوڊ;

    /* When debugging it can be useful if every register is set to a known
     * value.  Otherwise code space can be saved by just setting the registers
     * that need to be set. */
    #جيڪڏهن_وصف_ٿيل USE_ڀريل_رجسٽر_INITIALISATION
        {
            px_چوٽي_جو_ڍير--;
            *px_چوٽي_جو_ڍير = 0xffffffff; /* r15. */
            px_چوٽي_جو_ڍير--;
            *px_چوٽي_جو_ڍير = 0xeeeeeeee;
            px_چوٽي_جو_ڍير--;
            *px_چوٽي_جو_ڍير = 0xdddddddd;
            px_چوٽي_جو_ڍير--;
            *px_چوٽي_جو_ڍير = 0xcccccccc;
            px_چوٽي_جو_ڍير--;
            *px_چوٽي_جو_ڍير = 0xbbbbbbbb;
            px_چوٽي_جو_ڍير--;
            *px_چوٽي_جو_ڍير = 0xaaaaaaaa;
            px_چوٽي_جو_ڍير--;
            *px_چوٽي_جو_ڍير = 0x99999999;
            px_چوٽي_جو_ڍير--;
            *px_چوٽي_جو_ڍير = 0x88888888;
            px_چوٽي_جو_ڍير--;
            *px_چوٽي_جو_ڍير = 0x77777777;
            px_چوٽي_جو_ڍير--;
            *px_چوٽي_جو_ڍير = 0x66666666;
            px_چوٽي_جو_ڍير--;
            *px_چوٽي_جو_ڍير = 0x55555555;
            px_چوٽي_جو_ڍير--;
            *px_چوٽي_جو_ڍير = 0x44444444;
            px_چوٽي_جو_ڍير--;
            *px_چوٽي_جو_ڍير = 0x33333333;
            px_چوٽي_جو_ڍير--;
            *px_چوٽي_جو_ڍير = 0x22222222;
            px_چوٽي_جو_ڍير--;
        }
    #وإلا /* ifdef USE_FULL_REGISTER_INITIALISATION */
        {
            px_چوٽي_جو_ڍير -= 15;
        }
    #جيڪڏهن_پورو /* ifdef USE_FULL_REGISTER_INITIALISATION */

    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pvParameters; /* R1 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = پورٽ_INITIAL_FPSW;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x11111111; /* Accumulator 1. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x22222222; /* Accumulator 1. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x33333333; /* Accumulator 1. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x44444444; /* Accumulator 0. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x55555555; /* Accumulator 0. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x66666666; /* Accumulator 0. */

    #إذا ( configUSE_TASK_DPFPU_SUPPORT == 1 )
        {
            /* The task will start without a DPFPU context.  A task that
             * uses the DPFPU hardware must call vPortTaskUsesDPFPU() before
             * executing any floating point instructions. */
            px_چوٽي_جو_ڍير--;
            *px_چوٽي_جو_ڍير = پورٽ_NO_DPFPU_CONTEXT;
        }
    #وإلاإذا ( configUSE_TASK_DPFPU_SUPPORT == 2 )
        {
            /* The task will start with a DPFPU context.  Leave enough
             * space for the registers - and ensure they are initialised if desired. */
            #جيڪڏهن_وصف_ٿيل USE_ڀريل_رجسٽر_INITIALISATION
                {
                    px_چوٽي_جو_ڍير -= 2;
                    *(مزدوج *)px_چوٽي_جو_ڍير = 1515.1515; /* DR15. */
                    px_چوٽي_جو_ڍير -= 2;
                    *(مزدوج *)px_چوٽي_جو_ڍير = 1414.1414; /* DR14. */
                    px_چوٽي_جو_ڍير -= 2;
                    *(مزدوج *)px_چوٽي_جو_ڍير = 1313.1313; /* DR13. */
                    px_چوٽي_جو_ڍير -= 2;
                    *(مزدوج *)px_چوٽي_جو_ڍير = 1212.1212; /* DR12. */
                    px_چوٽي_جو_ڍير -= 2;
                    *(مزدوج *)px_چوٽي_جو_ڍير = 1111.1111; /* DR11. */
                    px_چوٽي_جو_ڍير -= 2;
                    *(مزدوج *)px_چوٽي_جو_ڍير = 1010.1010; /* DR10. */
                    px_چوٽي_جو_ڍير -= 2;
                    *(مزدوج *)px_چوٽي_جو_ڍير =  909.0909; /* DR9. */
                    px_چوٽي_جو_ڍير -= 2;
                    *(مزدوج *)px_چوٽي_جو_ڍير =  808.0808; /* DR8. */
                    px_چوٽي_جو_ڍير -= 2;
                    *(مزدوج *)px_چوٽي_جو_ڍير =  707.0707; /* DR7. */
                    px_چوٽي_جو_ڍير -= 2;
                    *(مزدوج *)px_چوٽي_جو_ڍير =  606.0606; /* DR6. */
                    px_چوٽي_جو_ڍير -= 2;
                    *(مزدوج *)px_چوٽي_جو_ڍير =  505.0505; /* DR5. */
                    px_چوٽي_جو_ڍير -= 2;
                    *(مزدوج *)px_چوٽي_جو_ڍير =  404.0404; /* DR4. */
                    px_چوٽي_جو_ڍير -= 2;
                    *(مزدوج *)px_چوٽي_جو_ڍير =  303.0303; /* DR3. */
                    px_چوٽي_جو_ڍير -= 2;
                    *(مزدوج *)px_چوٽي_جو_ڍير =  202.0202; /* DR2. */
                    px_چوٽي_جو_ڍير -= 2;
                    *(مزدوج *)px_چوٽي_جو_ڍير =  101.0101; /* DR1. */
                    px_چوٽي_جو_ڍير -= 2;
                    *(مزدوج *)px_چوٽي_جو_ڍير = 9876.54321;/* DR0. */
                }
            #وإلا /* ifdef USE_FULL_REGISTER_INITIALISATION */
                {
                    px_چوٽي_جو_ڍير -= پورٽ_DPFPU_معلومات_رجسٽر_لفظ;
                    memset( px_چوٽي_جو_ڍير, 0x00, پورٽ_DPFPU_معلومات_رجسٽر_لفظ * حجم( ڍير_Type_t ) );
                }
            #جيڪڏهن_پورو /* ifdef USE_FULL_REGISTER_INITIALISATION */
            px_چوٽي_جو_ڍير--;
            *px_چوٽي_جو_ڍير = پورٽ_INITIAL_DECNT; /* DECNT. */
            px_چوٽي_جو_ڍير--;
            *px_چوٽي_جو_ڍير = پورٽ_INITIAL_DCMR;  /* DCMR. */
            px_چوٽي_جو_ڍير--;
            *px_چوٽي_جو_ڍير = پورٽ_INITIAL_DPSW;  /* DPSW. */
        }
    #وإلاإذا ( configUSE_TASK_DPFPU_SUPPORT == 0 )
        {
            /* Omit DPFPU support. */
        }
    #وإلا /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */
        {
            #غلطي Invalid configUSE_TASK_DPFPU_SUPPORT setting - configUSE_TASK_DPFPU_SUPPORT must be سيٽ منزل 0, 1, 2, or کاٻو undefined.
        }
    #جيڪڏهن_پورو /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */

    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_DPFPU_SUPPORT == 1 )

    فراغ v_پورٽ_Task_استعمال_ڪري_DPFPU( فراغ )
    {
        /* A task is registering the fact that it needs a DPFPU context.  Set the
         * DPFPU flag (which is saved as part of the task context). */
        ul_پورٽ_Task_Has_DPFPUContext = پورٽ_HAS_DPFPU_CONTEXT;
    }

#جيڪڏهن_پورو /* configUSE_TASK_DPFPU_SUPPORT */
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    خارجي فراغ v_Application_تياري_Timer_مداخلت( فراغ );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    إذا( pxCurrentTCB != عدم )
    {
        /* Call an application function to set up the timer that will generate the
         * tick interrupt.  This way the application can decide which peripheral to
         * use.  A demo application is provided to show a suitable example. */
        v_Application_تياري_Timer_مداخلت();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = config_KERNEL_مداخلت_ترجيح;

        /* Start the first task. */
        prv_شروعات_پهريون_Task();
    }

    /* Just to make sure the function is not optimised away. */
    ( فراغ ) v_Software_مداخلت_ISR();

    /* Should not get here. */
    أرجع pdFAIL;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pxCurrentTCB == عدم );

    /* The following line is just to prevent the symbol getting optimised away. */
    ( فراغ ) vTaskSwitchContext();
}
/*-----------------------------------------------------------*/

#هدايت inline_asm prv_شروعات_پهريون_Task
ساكن فراغ prv_شروعات_پهريون_Task( فراغ )
{
#جيڪڏهن_وصف_نه_ٿيل __CDT_PARSER__

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

    #إذا ( configUSE_TASK_DPFPU_SUPPORT == 1 )

        /* The restored ulPortTaskHasDPFPUContext is to be zero here.
         * So, it is never necessary to restore the DPFPU context here. */
        ڪڍو_2 R15
        MOV.L # ul_پورٽ_Task_Has_DPFPUContext_2, R14
        MOV.L R15, [ R14 ]

    #وإلاإذا ( configUSE_TASK_DPFPU_SUPPORT == 2 )

        /* Restore the DPFPU context. */
        DPOPM.L DPSW-DECNT
        DPOPM.D DR0-DR15

    #جيڪڏهن_پورو /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */

    ڪڍو_2 R15

    /* Accumulator low 32 bits. */
    MVTACLO R15, A0
    ڪڍو_2 R15

    /* Accumulator high 32 bits. */
    MVTACHI R15, A0
    ڪڍو_2 R15

    /* Accumulator guard. */
    MVTACGU R15, A0
    ڪڍو_2 R15

    /* Accumulator low 32 bits. */
    MVTACLO R15, A1
    ڪڍو_2 R15

    /* Accumulator high 32 bits. */
    MVTACHI R15, A1
    ڪڍو_2 R15

    /* Accumulator guard. */
    MVTACGU R15, A1
    ڪڍو_2 R15

    /* Floating point status word. */
    MVTC R15, FPSW

    /* R1 to R15 - R0 is not included as it is the SP. */
    POPM R1-R15

    /* This pops the remaining registers. */
    RTE
    NOP
    NOP

#جيڪڏهن_پورو /* ifndef __CDT_PARSER__ */
}
/*-----------------------------------------------------------*/

فراغ v_Software_مداخلت_ISR( فراغ )
{
    prvYieldHandler();
}
/*-----------------------------------------------------------*/

#هدايت inline_asm prvYieldHandler
ساكن فراغ prvYieldHandler( فراغ )
{
#جيڪڏهن_وصف_نه_ٿيل __CDT_PARSER__

    /* Re-enable interrupts. */
    SETPSW I


    /* Move the data that was automatically pushed onto the interrupt stack when
     * the interrupt occurred from the interrupt stack to the user stack.
     *
     * R15 is saved before it is clobbered. */
    ڌڪو_2.L R15

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
    جوڙيو_2 # 12, R0

    /* All the rest of the registers are saved directly to the user stack. */
    SETPSW U

    /* Save the rest of the general registers (R15 has been saved already). */
    PUSHM R1-R14

    /* Save the FPSW and accumulators. */
    MVFC FPSW, R15
    ڌڪو_2.L R15
    MVFACGU # 0, A1, R15
    ڌڪو_2.L R15
    MVFACHI # 0, A1, R15
    ڌڪو_2.L R15
    MVFACLO # 0, A1, R15 /* Low order word. */
    ڌڪو_2.L R15
    MVFACGU # 0, A0, R15
    ڌڪو_2.L R15
    MVFACHI # 0, A0, R15
    ڌڪو_2.L R15
    MVFACLO # 0, A0, R15 /* Low order word. */
    ڌڪو_2.L R15

    #إذا ( configUSE_TASK_DPFPU_SUPPORT == 1 )

        /* Does the task have a DPFPU context that needs saving?  If
         * ulPortTaskHasDPFPUContext is 0 then no. */
        MOV.L # ul_پورٽ_Task_Has_DPFPUContext_2, R15
        MOV.L [ R15 ], R15
        CMP # 0, R15

        /* Save the DPFPU context, if any. */
        BEQ.B ?+
        DPUSHM.D DR0-DR15
        DPUSHM.L DPSW-DECNT
        ?:

        /* Save ulPortTaskHasDPFPUContext itself. */
        ڌڪو_2.L R15

    #وإلاإذا ( configUSE_TASK_DPFPU_SUPPORT == 2 )

        /* Save the DPFPU context, always. */
        DPUSHM.D DR0-DR15
        DPUSHM.L DPSW-DECNT

    #جيڪڏهن_پورو /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */


    /* Save the stack pointer to the TCB. */
    MOV.L # _pxCurrentTCB, R15
    MOV.L [ R15 ], R15
    MOV.L R0, [ R15 ]


    /* Ensure the interrupt mask is set to the syscall priority while the kernel
     * structures are being accessed. */
    MVTIPL # config_MAX_SYSCALL_مداخلت_ترجيح

    /* Select the next task to run. */
    BSR.A _vTaskSwitchContext

    /* Reset the interrupt mask as no more data structure access is required. */
    MVTIPL # config_KERNEL_مداخلت_ترجيح


    /* Load the stack pointer of the task that is now selected as the Running
     * state task from its TCB. */
    MOV.L # _pxCurrentTCB, R15
    MOV.L [ R15 ], R15
    MOV.L [ R15 ], R0


    /* Restore the context of the new task.  The PSW (Program Status Word) and
     * PC will be popped by the RTE instruction. */

    #إذا ( configUSE_TASK_DPFPU_SUPPORT == 1 )

        /* Is there a DPFPU context to restore?  If the restored
         * ulPortTaskHasDPFPUContext is zero then no. */
        ڪڍو_2 R15
        MOV.L # ul_پورٽ_Task_Has_DPFPUContext_2, R14
        MOV.L R15, [ R14 ]
        CMP # 0, R15

        /* Restore the DPFPU context, if any. */
        BEQ.B ?+
        DPOPM.L DPSW-DECNT
        DPOPM.D DR0-DR15
        ?:

    #وإلاإذا ( configUSE_TASK_DPFPU_SUPPORT == 2 )

        /* Restore the DPFPU context, always. */
        DPOPM.L DPSW-DECNT
        DPOPM.D DR0-DR15

    #جيڪڏهن_پورو /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */

    ڪڍو_2 R15

    /* Accumulator low 32 bits. */
    MVTACLO R15, A0
    ڪڍو_2 R15

    /* Accumulator high 32 bits. */
    MVTACHI R15, A0
    ڪڍو_2 R15

    /* Accumulator guard. */
    MVTACGU R15, A0
    ڪڍو_2 R15

    /* Accumulator low 32 bits. */
    MVTACLO R15, A1
    ڪڍو_2 R15

    /* Accumulator high 32 bits. */
    MVTACHI R15, A1
    ڪڍو_2 R15

    /* Accumulator guard. */
    MVTACGU R15, A1
    ڪڍو_2 R15
    MVTC R15, FPSW
    POPM R1-R15
    RTE
    NOP
    NOP

#جيڪڏهن_پورو /* ifndef __CDT_PARSER__ */
}
/*-----------------------------------------------------------*/

#هدايت مداخلت ( vTickISR( vect = _VECT( config_TICK_ويڪٽر ), enable ) )
فراغ vTickISR( فراغ )
{
    /* Increment the tick, and perform any processing the new tick value
     * necessitates.  Ensure IPL is at the max syscall value first. */
    سيٽ_ipl( config_MAX_SYSCALL_مداخلت_ترجيح );
    {
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    سيٽ_ipl( config_KERNEL_مداخلت_ترجيح );
}
/*-----------------------------------------------------------*/
