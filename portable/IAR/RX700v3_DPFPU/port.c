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

#warning Testing لكل DFPU support درون this پورت is not yet complete

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Library includes. */
#ضمن "string.h"

/* Hardware specifics. */
#إذا ( config_INCLUDE_PLATFORM_H_INSTEAD_از_IODEFINE_H == 1 )

    #ضمن "platform.h"

#وإلا /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

    #ضمن "iodefine.h"

#پایان_اگر /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
 * PSW is set with U and I set, and PM and IPL clear. */
#تعریف_کن پورت_INITIAL_PSW                  ( ( پشته_Type_t ) 0x00030000 )
#تعریف_کن پورت_INITIAL_FPSW                 ( ( پشته_Type_t ) 0x00000100 )
#تعریف_کن پورت_INITIAL_DPSW                 ( ( پشته_Type_t ) 0x00000100 )
#تعریف_کن پورت_INITIAL_DCMR                 ( ( پشته_Type_t ) 0x00000000 )
#تعریف_کن پورت_INITIAL_DECNT                ( ( پشته_Type_t ) 0x00000001 )

/* Tasks are not created with a DPFPU context, but can be given a DPFPU context
 * after they have been created.  A variable is stored as part of the tasks context
 * that holds portNO_DPFPU_CONTEXT if the task does not have a DPFPU context, or
 * any other value if the task does have a DPFPU context. */
#تعریف_کن پورت_NO_DPFPU_CONTEXT             ( ( پشته_Type_t ) 0 )
#تعریف_کن پورت_HAS_DPFPU_CONTEXT            ( ( پشته_Type_t ) 1 )

/* The space on the stack required to hold the DPFPU data registers.  This is 16
 * 64-bit registers. */
#تعریف_کن پورت_DPFPU_داده_ثبات_واژگان    ( 16 * 2 )

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
ساكن فراغ prv_شروع_اولی_Task( فراغ );

/*
 * Software interrupt handler.  Performs the actual context switch (saving and
 * restoring of registers).  Written in asm code as direct register access is
 * required.
 */
__interrupt فراغ v_Software_وقفه_ISR( فراغ );

/*
 * The tick ISR handler.  The peripheral used is configured by the application
 * via a hook/callback function.
 */
__interrupt فراغ vTickISR( فراغ );

/*-----------------------------------------------------------*/

/* Saved as part of the task context.  If ulPortTaskHasDPFPUContext is non-zero
 * then a DPFPU context must be saved and restored for the task. */
#إذا ( configUSE_TASK_DPFPU_SUPPORT == 1 )

    پشته_Type_t ul_پورت_Task_Has_DPFPUContext = پورت_NO_DPFPU_CONTEXT;

#پایان_اگر /* configUSE_TASK_DPFPU_SUPPORT */

/* This is accessed by the inline assembler functions so is file scope for
 * convenience. */
خارجي فراغ * pxCurrentTCB;
خارجي فراغ vTaskSwitchContext( فراغ );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
پشته_Type_t * px_پورت_Initialise_پشته( پشته_Type_t * px_بالاترین_از_پشته,
                                     TaskFunction_t px_کد,
                                     فراغ * pvParameters )
{
    /* R0 is not included as it is the stack pointer. */

    *px_بالاترین_از_پشته = 0x00;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = پورت_INITIAL_PSW;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) px_کد;

    /* When debugging it can be useful if every register is set to a known
     * value.  Otherwise code space can be saved by just setting the registers
     * that need to be set. */
    #اگر_تعریف_شده USE_پر_ثبات_INITIALISATION
    {
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = 0xffffffff; /* r15. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = 0xeeeeeeee;
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = 0xdddddddd;
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = 0xcccccccc;
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = 0xbbbbbbbb;
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = 0xaaaaaaaa;
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = 0x99999999;
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = 0x88888888;
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = 0x77777777;
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = 0x66666666;
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = 0x55555555;
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = 0x44444444;
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = 0x33333333;
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = 0x22222222;
        px_بالاترین_از_پشته--;
    }
    #وإلا /* ifdef USE_FULL_REGISTER_INITIALISATION */
    {
        px_بالاترین_از_پشته -= 15;
    }
    #پایان_اگر /* ifdef USE_FULL_REGISTER_INITIALISATION */

    *px_بالاترین_از_پشته = ( پشته_Type_t ) pvParameters; /* R1 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = پورت_INITIAL_FPSW;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x11111111; /* Accumulator 1. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x22222222; /* Accumulator 1. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x33333333; /* Accumulator 1. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x44444444; /* Accumulator 0. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x55555555; /* Accumulator 0. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x66666666; /* Accumulator 0. */

    #إذا ( configUSE_TASK_DPFPU_SUPPORT == 1 )
    {
        /* The task will start without a DPFPU context.  A task that
         * uses the DPFPU hardware must call vPortTaskUsesDPFPU() before
         * executing any floating point instructions. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = پورت_NO_DPFPU_CONTEXT;
    }
    #وإلاإذا ( configUSE_TASK_DPFPU_SUPPORT == 2 )
    {
        /* The task will start with a DPFPU context.  Leave enough
         * space for the registers - and ensure they are initialised if desired. */
        #اگر_تعریف_شده USE_پر_ثبات_INITIALISATION
        {
            px_بالاترین_از_پشته -= 2;
            *( مزدوج * ) px_بالاترین_از_پشته = 1515.1515;  /* DR15. */
            px_بالاترین_از_پشته -= 2;
            *( مزدوج * ) px_بالاترین_از_پشته = 1414.1414;  /* DR14. */
            px_بالاترین_از_پشته -= 2;
            *( مزدوج * ) px_بالاترین_از_پشته = 1313.1313;  /* DR13. */
            px_بالاترین_از_پشته -= 2;
            *( مزدوج * ) px_بالاترین_از_پشته = 1212.1212;  /* DR12. */
            px_بالاترین_از_پشته -= 2;
            *( مزدوج * ) px_بالاترین_از_پشته = 1111.1111;  /* DR11. */
            px_بالاترین_از_پشته -= 2;
            *( مزدوج * ) px_بالاترین_از_پشته = 1010.1010;  /* DR10. */
            px_بالاترین_از_پشته -= 2;
            *( مزدوج * ) px_بالاترین_از_پشته = 909.0909;   /* DR9. */
            px_بالاترین_از_پشته -= 2;
            *( مزدوج * ) px_بالاترین_از_پشته = 808.0808;   /* DR8. */
            px_بالاترین_از_پشته -= 2;
            *( مزدوج * ) px_بالاترین_از_پشته = 707.0707;   /* DR7. */
            px_بالاترین_از_پشته -= 2;
            *( مزدوج * ) px_بالاترین_از_پشته = 606.0606;   /* DR6. */
            px_بالاترین_از_پشته -= 2;
            *( مزدوج * ) px_بالاترین_از_پشته = 505.0505;   /* DR5. */
            px_بالاترین_از_پشته -= 2;
            *( مزدوج * ) px_بالاترین_از_پشته = 404.0404;   /* DR4. */
            px_بالاترین_از_پشته -= 2;
            *( مزدوج * ) px_بالاترین_از_پشته = 303.0303;   /* DR3. */
            px_بالاترین_از_پشته -= 2;
            *( مزدوج * ) px_بالاترین_از_پشته = 202.0202;   /* DR2. */
            px_بالاترین_از_پشته -= 2;
            *( مزدوج * ) px_بالاترین_از_پشته = 101.0101;   /* DR1. */
            px_بالاترین_از_پشته -= 2;
            *( مزدوج * ) px_بالاترین_از_پشته = 9876.54321; /* DR0. */
        }
        #وإلا /* ifdef USE_FULL_REGISTER_INITIALISATION */
        {
            px_بالاترین_از_پشته -= پورت_DPFPU_داده_ثبات_واژگان;
            memset( px_بالاترین_از_پشته, 0x00, پورت_DPFPU_داده_ثبات_واژگان * حجم( پشته_Type_t ) );
        }
        #پایان_اگر /* ifdef USE_FULL_REGISTER_INITIALISATION */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = پورت_INITIAL_DECNT; /* DECNT. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = پورت_INITIAL_DCMR;  /* DCMR. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = پورت_INITIAL_DPSW;  /* DPSW. */
    }
    #وإلاإذا ( configUSE_TASK_DPFPU_SUPPORT == 0 )
    {
        /* Omit DPFPU support. */
    }
    #وإلا /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */
    {
        #خطا Invalid configUSE_TASK_DPFPU_SUPPORT setting - configUSE_TASK_DPFPU_SUPPORT must be مجموعه مقصد 0, 1, 2, or چپ undefined.
    }
    #پایان_اگر /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */

    أرجع px_بالاترین_از_پشته;
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_DPFPU_SUPPORT == 1 )

    فراغ v_پورت_Task_استفاده_میکند_DPFPU( فراغ )
    {
        /* A task is registering the fact that it needs a DPFPU context.  Set the
         * DPFPU flag (which is saved as part of the task context). */
        ul_پورت_Task_Has_DPFPUContext = پورت_HAS_DPFPU_CONTEXT;
    }

#پایان_اگر /* configUSE_TASK_DPFPU_SUPPORT */
/*-----------------------------------------------------------*/

پایه_Type_t x_پورت_شروع_Scheduler( فراغ )
{
    خارجي فراغ v_Application_راهاندازی_Timer_وقفه( فراغ );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    إذا( pxCurrentTCB != عدم )
    {
        /* Call an application function to set up the timer that will generate the
         * tick interrupt.  This way the application can decide which peripheral to
         * use.  A demo application is provided to show a suitable example. */
        v_Application_راهاندازی_Timer_وقفه();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = config_KERNEL_وقفه_اولویت;

        /* Start the first task. */
        prv_شروع_اولی_Task();
    }

    /* Should not get here. */
    أرجع pdFAIL;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_انتها_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pxCurrentTCB == عدم );

    /* The following line is just to prevent the symbol getting optimised away. */
    ( فراغ ) vTaskSwitchContext();
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_شروع_اولی_Task( فراغ )
{
    __asm متطاير
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

        #إذا ( configUSE_TASK_DPFPU_SUPPORT == 1 )

            /* The restored ulPortTaskHasDPFPUContext is to be zero here.
             * So, it is never necessary to restore the DPFPU context here. */
            "POP        R15                                 \n" \
            "MOV.L      #_ulPortTaskHasDPFPUContext, R14    \n" \
            "MOV.L      R15, [R14]                          \n" \

        #وإلاإذا ( configUSE_TASK_DPFPU_SUPPORT == 2 )
            /* Restore the DPFPU context. */
            "DPOPM.L    DPSW-DECNT              \n" \
            "DPOPM.D    DR0-DR15                \n" \

        #پایان_اگر /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */

        "POP        R15                     \n" \

        /* Accumulator low 32 bits. */
        "MVTACLO    R15, A0                 \n" \
        "POP        R15                     \n" \

        /* Accumulator high 32 bits. */
        "MVTACHI    R15, A0                 \n" \
        "POP        R15                     \n" \

        /* Accumulator guard. */
        "MVTACGU    R15, A0                 \n" \
        "POP        R15                     \n" \

        /* Accumulator low 32 bits. */
        "MVTACLO    R15, A1                 \n" \
        "POP        R15                     \n" \

        /* Accumulator high 32 bits. */
        "MVTACHI    R15, A1                 \n" \
        "POP        R15                     \n" \

        /* Accumulator guard. */
        "MVTACGU    R15, A1                 \n" \
        "POP        R15                     \n" \

        /* Floating point status word. */
        "MVTC       R15, FPSW               \n" \

        /* R1 to R15 - R0 is not included as it is the SP. */
        "POPM       R1-R15                  \n" \

        /* This pops the remaining registers. */
        "RTE                                \n" \
        "NOP                                \n" \
        "NOP                                \n"
    );
}
/*-----------------------------------------------------------*/

#رهنمود وکتور = VECT( ICU, SWINT )
__interrupt فراغ v_Software_وقفه_ISR( فراغ )
{
    __asm متطاير
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

        /* Save the FPSW and accumulators. */
        "MVFC       FPSW, R15                   \n"                       \
        "PUSH.L     R15                         \n"                       \
        "MVFACGU    #0, A1, R15                 \n"                       \
        "PUSH.L     R15                         \n"                       \
        "MVFACHI    #0, A1, R15                 \n"                       \
        "PUSH.L     R15                         \n"                       \
        "MVFACLO    #0, A1, R15                 \n" /* Low order word. */ \
        "PUSH.L     R15                         \n"                       \
        "MVFACGU    #0, A0, R15                 \n"                       \
        "PUSH.L     R15                         \n"                       \
        "MVFACHI    #0, A0, R15                 \n"                       \
        "PUSH.L     R15                         \n"                       \
        "MVFACLO    #0, A0, R15                 \n" /* Low order word. */ \
        "PUSH.L     R15                         \n"                       \

        #إذا ( configUSE_TASK_DPFPU_SUPPORT == 1 )

            /* Does the task have a DPFPU context that needs saving?  If
             * ulPortTaskHasDPFPUContext is 0 then no. */
            "MOV.L      #_ulPortTaskHasDPFPUContext, R15    \n" \
            "MOV.L      [R15], R15                          \n" \
            "CMP        #0, R15                             \n" \

            /* Save the DPFPU context, if any. */
            "BEQ.B      __lab1                      \n" \
            "DPUSHM.D   DR0-DR15                    \n" \
            "DPUSHM.L   DPSW-DECNT                  \n" \
            "__lab1:                                \n" \

            /* Save ulPortTaskHasDPFPUContext itself. */
            "PUSH.L     R15                         \n" \

        #وإلاإذا ( configUSE_TASK_DPFPU_SUPPORT == 2 )
            /* Save the DPFPU context, always. */
            "DPUSHM.D   DR0-DR15                    \n" \
            "DPUSHM.L   DPSW-DECNT                  \n" \

        #پایان_اگر /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */


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

        #إذا ( configUSE_TASK_DPFPU_SUPPORT == 1 )

            /* Is there a DPFPU context to restore?  If the restored
             * ulPortTaskHasDPFPUContext is zero then no. */
            "POP        R15                                 \n" \
            "MOV.L      #_ulPortTaskHasDPFPUContext, R14    \n" \
            "MOV.L      R15, [R14]                          \n" \
            "CMP        #0, R15                             \n" \

            /* Restore the DPFPU context, if any. */
            "BEQ.B      __lab2                      \n" \
            "DPOPM.L    DPSW-DECNT                  \n" \
            "DPOPM.D    DR0-DR15                    \n" \
            "__lab2:                                \n" \

        #وإلاإذا ( configUSE_TASK_DPFPU_SUPPORT == 2 )
            /* Restore the DPFPU context, always. */
            "DPOPM.L    DPSW-DECNT                  \n" \
            "DPOPM.D    DR0-DR15                    \n" \

        #پایان_اگر /* if( configUSE_TASK_DPFPU_SUPPORT == 1 ) */

        "POP        R15                         \n" \

        /* Accumulator low 32 bits. */
        "MVTACLO    R15, A0                     \n" \
        "POP        R15                         \n" \

        /* Accumulator high 32 bits. */
        "MVTACHI    R15, A0                     \n" \
        "POP        R15                         \n" \

        /* Accumulator guard. */
        "MVTACGU    R15, A0                     \n" \
        "POP        R15                         \n" \

        /* Accumulator low 32 bits. */
        "MVTACLO    R15, A1                     \n" \
        "POP        R15                         \n" \

        /* Accumulator high 32 bits. */
        "MVTACHI    R15, A1                     \n" \
        "POP        R15                         \n" \

        /* Accumulator guard. */
        "MVTACGU    R15, A1                     \n" \
        "POP        R15                         \n" \
        "MVTC       R15, FPSW                   \n" \
        "POPM       R1-R15                      \n" \
        "RTE                                    \n" \
        "NOP                                    \n" \
        "NOP                                      "
        پورت_CDT_NO_PARSE( ::) "i" ( config_MAX_SYSCALL_وقفه_اولویت ), "i" ( config_KERNEL_وقفه_اولویت )
    );
}
/*-----------------------------------------------------------*/

#رهنمود وکتور = _VECT( config_TICK_وکتور )
__interrupt فراغ vTickISR( فراغ )
{
    /* Re-enable interrupts. */
    __enable_interrupt();

    /* Increment the tick, and perform any processing the new tick value
     * necessitates.  Ensure IPL is at the max syscall value first. */
    __set_interrupt_level( config_MAX_SYSCALL_وقفه_اولویت );
    {
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    __set_interrupt_level( config_KERNEL_وقفه_اولویت );
}
/*-----------------------------------------------------------*/
