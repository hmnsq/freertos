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

#warning Testing لكل DFPU support وچ this پورٹ is not yet complete

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Library includes. */
#ضمن "string.h"

/* Hardware specifics. */
#إذا ( config_INCLUDE_PLATFORM_H_INSTEAD_دا_IODEFINE_H == 1 )

    #ضمن "platform.h"

#وإلا /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

    #ضمن "iodefine.h"

#جے_انت /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
 * PSW is set with U and I set, and PM and IPL clear. */
#تعریف_کرو پورٹ_INITIAL_PSW     ( ( ڈھیر_Type_t ) 0x00030000 )
#تعریف_کرو پورٹ_INITIAL_FPSW    ( ( ڈھیر_Type_t ) 0x00000100 )
#تعریف_کرو پورٹ_INITIAL_DPSW    ( ( ڈھیر_Type_t ) 0x00000100 )
#تعریف_کرو پورٹ_INITIAL_DCMR    ( ( ڈھیر_Type_t ) 0x00000000 )
#تعریف_کرو پورٹ_INITIAL_DECNT   ( ( ڈھیر_Type_t ) 0x00000001 )

/* Tasks are not created with a DPFPU context, but can be given a DPFPU context
 * after they have been created.  A variable is stored as part of the tasks context
 * that holds portNO_DPFPU_CONTEXT if the task does not have a DPFPU context, or
 * any other value if the task does have a DPFPU context. */
#تعریف_کرو پورٹ_NO_DPFPU_CONTEXT    ( ( ڈھیر_Type_t ) 0 )
#تعریف_کرو پورٹ_HAS_DPFPU_CONTEXT   ( ( ڈھیر_Type_t ) 1 )

/* The space on the stack required to hold the DPFPU data registers.  This is 16
 * 64-bit registers. */
#تعریف_کرو پورٹ_DPFPU_انکڑے_رجسٹر_الفاظ   ( 16 * 2 )

/*-----------------------------------------------------------*/

/* The following lines are to ensure vSoftwareInterruptEntry can be referenced,
 * and therefore installed in the vector table, when the FreeRTOS code is built
 * as a library. */
خارجي ادھار_Type_t v_Software_رکاوٹ_اندراج;
ثابت ادھار_Type_t * p_v_Software_رکاوٹ_اندراج = &v_Software_رکاوٹ_اندراج;

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
ساكن فراغ prv_شروع_پہلا_Task( فراغ );

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
فراغ v_Software_رکاوٹ_ISR( فراغ );

/*
 * The tick ISR handler.  The peripheral used is configured by the application
 * via a hook/callback function.
 */
فراغ vTickISR( فراغ );

/*-----------------------------------------------------------*/

/* Saved as part of the task context.  If ulPortTaskHasDPFPUContext is non-zero
 * then a DPFPU context must be saved and restored for the task. */
#إذا ( configUSE_TASK_DPFPU_SUPPORT == 1 )

    ڈھیر_Type_t ul_پورٹ_Task_Has_DPFPUContext = پورٹ_NO_DPFPU_CONTEXT;

#جے_انت /* configUSE_TASK_DPFPU_SUPPORT */

/* This is accessed by the inline assembler functions so is file scope for
 * convenience. */
خارجي فراغ * pxCurrentTCB;
خارجي فراغ vTaskSwitchContext( فراغ );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                     TaskFunction_t px_کوڈ,
                                     فراغ * pvParameters )
{
    /* R0 is not included as it is the stack pointer. */

    *px_چوٹی_دا_ڈھیر = 0x00;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = پورٹ_INITIAL_PSW;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) px_کوڈ;

    /* When debugging it can be useful if every register is set to a known
     * value.  Otherwise code space can be saved by just setting the registers
     * that need to be set. */
    #جے_تعریف_شدہ USE_بھریا_رجسٹر_INITIALISATION
        {
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = 0xffffffff; /* r15. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = 0xeeeeeeee;
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = 0xdddddddd;
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = 0xcccccccc;
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = 0xbbbbbbbb;
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = 0xaaaaaaaa;
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = 0x99999999;
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = 0x88888888;
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = 0x77777777;
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = 0x66666666;
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = 0x55555555;
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = 0x44444444;
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = 0x33333333;
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = 0x22222222;
            px_چوٹی_دا_ڈھیر--;
        }
    #وإلا /* ifdef USE_FULL_REGISTER_INITIALISATION */
        {
            px_چوٹی_دا_ڈھیر -= 15;
        }
    #جے_انت /* ifdef USE_FULL_REGISTER_INITIALISATION */

    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) pvParameters; /* R1 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = پورٹ_INITIAL_FPSW;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x11111111; /* Accumulator 1. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x22222222; /* Accumulator 1. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x33333333; /* Accumulator 1. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x44444444; /* Accumulator 0. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x55555555; /* Accumulator 0. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x66666666; /* Accumulator 0. */

    #إذا ( configUSE_TASK_DPFPU_SUPPORT == 1 )
        {
            /* The task will start without a DPFPU context.  A task that
             * uses the DPFPU hardware must call vPortTaskUsesDPFPU() before
             * executing any floating point instructions. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = پورٹ_NO_DPFPU_CONTEXT;
        }
    #وإلاإذا ( configUSE_TASK_DPFPU_SUPPORT == 2 )
        {
            /* The task will start with a DPFPU context.  Leave enough
             * space for the registers - and ensure they are initialised if desired. */
            #جے_تعریف_شدہ USE_بھریا_رجسٹر_INITIALISATION
                {
                    px_چوٹی_دا_ڈھیر -= 2;
                    *(مزدوج *)px_چوٹی_دا_ڈھیر = 1515.1515; /* DR15. */
                    px_چوٹی_دا_ڈھیر -= 2;
                    *(مزدوج *)px_چوٹی_دا_ڈھیر = 1414.1414; /* DR14. */
                    px_چوٹی_دا_ڈھیر -= 2;
                    *(مزدوج *)px_چوٹی_دا_ڈھیر = 1313.1313; /* DR13. */
                    px_چوٹی_دا_ڈھیر -= 2;
                    *(مزدوج *)px_چوٹی_دا_ڈھیر = 1212.1212; /* DR12. */
                    px_چوٹی_دا_ڈھیر -= 2;
                    *(مزدوج *)px_چوٹی_دا_ڈھیر = 1111.1111; /* DR11. */
                    px_چوٹی_دا_ڈھیر -= 2;
                    *(مزدوج *)px_چوٹی_دا_ڈھیر = 1010.1010; /* DR10. */
                    px_چوٹی_دا_ڈھیر -= 2;
                    *(مزدوج *)px_چوٹی_دا_ڈھیر =  909.0909; /* DR9. */
                    px_چوٹی_دا_ڈھیر -= 2;
                    *(مزدوج *)px_چوٹی_دا_ڈھیر =  808.0808; /* DR8. */
                    px_چوٹی_دا_ڈھیر -= 2;
                    *(مزدوج *)px_چوٹی_دا_ڈھیر =  707.0707; /* DR7. */
                    px_چوٹی_دا_ڈھیر -= 2;
                    *(مزدوج *)px_چوٹی_دا_ڈھیر =  606.0606; /* DR6. */
                    px_چوٹی_دا_ڈھیر -= 2;
                    *(مزدوج *)px_چوٹی_دا_ڈھیر =  505.0505; /* DR5. */
                    px_چوٹی_دا_ڈھیر -= 2;
                    *(مزدوج *)px_چوٹی_دا_ڈھیر =  404.0404; /* DR4. */
                    px_چوٹی_دا_ڈھیر -= 2;
                    *(مزدوج *)px_چوٹی_دا_ڈھیر =  303.0303; /* DR3. */
                    px_چوٹی_دا_ڈھیر -= 2;
                    *(مزدوج *)px_چوٹی_دا_ڈھیر =  202.0202; /* DR2. */
                    px_چوٹی_دا_ڈھیر -= 2;
                    *(مزدوج *)px_چوٹی_دا_ڈھیر =  101.0101; /* DR1. */
                    px_چوٹی_دا_ڈھیر -= 2;
                    *(مزدوج *)px_چوٹی_دا_ڈھیر = 9876.54321;/* DR0. */
                }
            #وإلا /* ifdef USE_FULL_REGISTER_INITIALISATION */
                {
                    px_چوٹی_دا_ڈھیر -= پورٹ_DPFPU_انکڑے_رجسٹر_الفاظ;
                    memset( px_چوٹی_دا_ڈھیر, 0x00, پورٹ_DPFPU_انکڑے_رجسٹر_الفاظ * حجم( ڈھیر_Type_t ) );
                }
            #جے_انت /* ifdef USE_FULL_REGISTER_INITIALISATION */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = پورٹ_INITIAL_DECNT; /* DECNT. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = پورٹ_INITIAL_DCMR;  /* DCMR. */
            px_چوٹی_دا_ڈھیر--;
            *px_چوٹی_دا_ڈھیر = پورٹ_INITIAL_DPSW;  /* DPSW. */
        }
    #وإلاإذا ( configUSE_TASK_DPFPU_SUPPORT == 0 )
        {
            /* Omit DPFPU support. */
        }
    #وإلا /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */
        {
            #غلطی Invalid configUSE_TASK_DPFPU_SUPPORT setting - configUSE_TASK_DPFPU_SUPPORT must be سیٹ منزل 0, 1, 2, or بایاں undefined.
        }
    #جے_انت /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */

    أرجع px_چوٹی_دا_ڈھیر;
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_DPFPU_SUPPORT == 1 )

    فراغ v_پورٹ_Task_ورتدا_DPFPU( فراغ )
    {
        /* A task is registering the fact that it needs a DPFPU context.  Set the
         * DPFPU flag (which is saved as part of the task context). */
        ul_پورٹ_Task_Has_DPFPUContext = پورٹ_HAS_DPFPU_CONTEXT;
    }

#جے_انت /* configUSE_TASK_DPFPU_SUPPORT */
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
    خارجي فراغ v_Application_تیاری_Timer_رکاوٹ( فراغ );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    إذا( pxCurrentTCB != عدم )
    {
        /* Call an application function to set up the timer that will generate the
         * tick interrupt.  This way the application can decide which peripheral to
         * use.  A demo application is provided to show a suitable example. */
        v_Application_تیاری_Timer_رکاوٹ();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = config_KERNEL_رکاوٹ_ترجیح;

        /* Start the first task. */
        prv_شروع_پہلا_Task();
    }

    /* Just to make sure the function is not optimised away. */
    ( فراغ ) v_Software_رکاوٹ_ISR();

    /* Should not get here. */
    أرجع pdFAIL;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pxCurrentTCB == عدم );

    /* The following line is just to prevent the symbol getting optimised away. */
    ( فراغ ) vTaskSwitchContext();
}
/*-----------------------------------------------------------*/

#ہدایت inline_asm prv_شروع_پہلا_Task
ساكن فراغ prv_شروع_پہلا_Task( فراغ )
{
#جے_بنا_تعریف __CDT_PARSER__

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
        نکالو_2 R15
        MOV.L # ul_پورٹ_Task_Has_DPFPUContext_2, R14
        MOV.L R15, [ R14 ]

    #وإلاإذا ( configUSE_TASK_DPFPU_SUPPORT == 2 )

        /* Restore the DPFPU context. */
        DPOPM.L DPSW-DECNT
        DPOPM.D DR0-DR15

    #جے_انت /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */

    نکالو_2 R15

    /* Accumulator low 32 bits. */
    MVTACLO R15, A0
    نکالو_2 R15

    /* Accumulator high 32 bits. */
    MVTACHI R15, A0
    نکالو_2 R15

    /* Accumulator guard. */
    MVTACGU R15, A0
    نکالو_2 R15

    /* Accumulator low 32 bits. */
    MVTACLO R15, A1
    نکالو_2 R15

    /* Accumulator high 32 bits. */
    MVTACHI R15, A1
    نکالو_2 R15

    /* Accumulator guard. */
    MVTACGU R15, A1
    نکالو_2 R15

    /* Floating point status word. */
    MVTC R15, FPSW

    /* R1 to R15 - R0 is not included as it is the SP. */
    POPM R1-R15

    /* This pops the remaining registers. */
    RTE
    NOP
    NOP

#جے_انت /* ifndef __CDT_PARSER__ */
}
/*-----------------------------------------------------------*/

فراغ v_Software_رکاوٹ_ISR( فراغ )
{
    prvYieldHandler();
}
/*-----------------------------------------------------------*/

#ہدایت inline_asm prvYieldHandler
ساكن فراغ prvYieldHandler( فراغ )
{
#جے_بنا_تعریف __CDT_PARSER__

    /* Re-enable interrupts. */
    SETPSW I


    /* Move the data that was automatically pushed onto the interrupt stack when
     * the interrupt occurred from the interrupt stack to the user stack.
     *
     * R15 is saved before it is clobbered. */
    ڈالو_2.L R15

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
    جوڑو_2 # 12, R0

    /* All the rest of the registers are saved directly to the user stack. */
    SETPSW U

    /* Save the rest of the general registers (R15 has been saved already). */
    PUSHM R1-R14

    /* Save the FPSW and accumulators. */
    MVFC FPSW, R15
    ڈالو_2.L R15
    MVFACGU # 0, A1, R15
    ڈالو_2.L R15
    MVFACHI # 0, A1, R15
    ڈالو_2.L R15
    MVFACLO # 0, A1, R15 /* Low order word. */
    ڈالو_2.L R15
    MVFACGU # 0, A0, R15
    ڈالو_2.L R15
    MVFACHI # 0, A0, R15
    ڈالو_2.L R15
    MVFACLO # 0, A0, R15 /* Low order word. */
    ڈالو_2.L R15

    #إذا ( configUSE_TASK_DPFPU_SUPPORT == 1 )

        /* Does the task have a DPFPU context that needs saving?  If
         * ulPortTaskHasDPFPUContext is 0 then no. */
        MOV.L # ul_پورٹ_Task_Has_DPFPUContext_2, R15
        MOV.L [ R15 ], R15
        CMP # 0, R15

        /* Save the DPFPU context, if any. */
        BEQ.B ?+
        DPUSHM.D DR0-DR15
        DPUSHM.L DPSW-DECNT
        ?:

        /* Save ulPortTaskHasDPFPUContext itself. */
        ڈالو_2.L R15

    #وإلاإذا ( configUSE_TASK_DPFPU_SUPPORT == 2 )

        /* Save the DPFPU context, always. */
        DPUSHM.D DR0-DR15
        DPUSHM.L DPSW-DECNT

    #جے_انت /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */


    /* Save the stack pointer to the TCB. */
    MOV.L # _pxCurrentTCB, R15
    MOV.L [ R15 ], R15
    MOV.L R0, [ R15 ]


    /* Ensure the interrupt mask is set to the syscall priority while the kernel
     * structures are being accessed. */
    MVTIPL # config_MAX_SYSCALL_رکاوٹ_ترجیح

    /* Select the next task to run. */
    BSR.A _vTaskSwitchContext

    /* Reset the interrupt mask as no more data structure access is required. */
    MVTIPL # config_KERNEL_رکاوٹ_ترجیح


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
        نکالو_2 R15
        MOV.L # ul_پورٹ_Task_Has_DPFPUContext_2, R14
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

    #جے_انت /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */

    نکالو_2 R15

    /* Accumulator low 32 bits. */
    MVTACLO R15, A0
    نکالو_2 R15

    /* Accumulator high 32 bits. */
    MVTACHI R15, A0
    نکالو_2 R15

    /* Accumulator guard. */
    MVTACGU R15, A0
    نکالو_2 R15

    /* Accumulator low 32 bits. */
    MVTACLO R15, A1
    نکالو_2 R15

    /* Accumulator high 32 bits. */
    MVTACHI R15, A1
    نکالو_2 R15

    /* Accumulator guard. */
    MVTACGU R15, A1
    نکالو_2 R15
    MVTC R15, FPSW
    POPM R1-R15
    RTE
    NOP
    NOP

#جے_انت /* ifndef __CDT_PARSER__ */
}
/*-----------------------------------------------------------*/

#ہدایت رکاوٹ ( vTickISR( vect = _VECT( config_TICK_سمتیہ ), enable ) )
فراغ vTickISR( فراغ )
{
    /* Increment the tick, and perform any processing the new tick value
     * necessitates.  Ensure IPL is at the max syscall value first. */
    سیٹ_ipl( config_MAX_SYSCALL_رکاوٹ_ترجیح );
    {
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    سیٹ_ipl( config_KERNEL_رکاوٹ_ترجیح );
}
/*-----------------------------------------------------------*/
