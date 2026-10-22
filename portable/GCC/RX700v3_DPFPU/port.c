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

#warning Testing क्रम DFPU support in this port is not yet complete

/* Scheduler includes. */
#समावेश "FreeRTOS.h"
#समावेश "task.h"

/* Library includes. */
#समावेश "string.h"

/* Hardware specifics. */
#अगर ( configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H == 1 )

    #समावेश "platform.h"

#अन्यथा /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

    #समावेश "iodefine.h"

#पूर्ण_अगर /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
 * PSW is set with U and I set, and PM and IPL clear. */
#घोषणा portINITIAL_PSW                  ( ( ढेर_Type_t ) 0x00030000 )
#घोषणा portINITIAL_FPSW                 ( ( ढेर_Type_t ) 0x00000100 )
#घोषणा portINITIAL_DPSW                 ( ( ढेर_Type_t ) 0x00000100 )
#घोषणा portINITIAL_DCMR                 ( ( ढेर_Type_t ) 0x00000000 )
#घोषणा portINITIAL_DECNT                ( ( ढेर_Type_t ) 0x00000001 )

/* Tasks are not created with a DPFPU context, but can be given a DPFPU context
 * after they have been created.  A variable is stored as part of the tasks context
 * that holds portNO_DPFPU_CONTEXT if the task does not have a DPFPU context, or
 * any other value if the task does have a DPFPU context. */
#घोषणा portNO_DPFPU_CONTEXT             ( ( ढेर_Type_t ) 0 )
#घोषणा portHAS_DPFPU_CONTEXT            ( ( ढेर_Type_t ) 1 )

/* The space on the stack required to hold the DPFPU data registers.  This is 16
 * 64-bit registers. */
#घोषणा port_DPFPU_तथ्य_REGISTER_शब्दगण    ( 16 * 2 )

/* These macros allow a critical section to be added around the call to
 * xTaskIncrementTick(), which is only ever called from interrupts at the kernel
 * priority - ie a known priority.  Therefore these local macros are a slight
 * optimisation compared to calling the global SET/CLEAR_INTERRUPT_MASK macros,
 * which would require the old IPL to be read first and stored in a local variable. */
#घोषणा portMASK_INTERRUPTS_FROM_KERNEL_ISR()      __asm अस्थिर ( "MVTIPL %0" ::"i" ( configMAX_SYSCALL_INTERRUPT_PRIORITY ) )
#घोषणा portUNMASK_INTERRUPTS_FROM_KERNEL_ISR()    __asm अस्थिर ( "MVTIPL %0" ::"i" ( configKERNEL_INTERRUPT_PRIORITY ) )

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
अटल व्योम prvStartFirstTask( व्योम ) __attribute__( ( naked ) );

/*
 * Software interrupt handler.  Performs the actual context switch (saving and
 * restoring of registers).  Written in asm code as direct register access is
 * required.
 */
#अगर ( configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H == 1 )

    R_BSP_PRAGMA_INTERRUPT( vSoftwareInterruptISR, VECT( ICU, SWINT ) )
    R_BSP_ATTRIB_INTERRUPT व्योम vSoftwareInterruptISR( व्योम ) __attribute__( ( naked ) );

#अन्यथा /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

    व्योम vSoftwareInterruptISR( व्योम ) __attribute__( ( naked ) );

#पूर्ण_अगर /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H  */

/*
 * The tick ISR handler.  The peripheral used is configured by the application
 * via a hook/callback function.
 */
#अगर ( configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H == 1 )

    R_BSP_PRAGMA_INTERRUPT( vTickISR, _VECT( configTICK_VECTOR ) )
    R_BSP_ATTRIB_INTERRUPT व्योम vTickISR( व्योम ); /* Do not add __attribute__( ( interrupt ) ). */

#अन्यथा /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

    व्योम vTickISR( व्योम ) __attribute__( ( interrupt ) );

#पूर्ण_अगर /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

/*-----------------------------------------------------------*/

/* Saved as part of the task context.  If ulPortTaskHasDPFPUContext is non-zero
 * then a DPFPU context must be saved and restored for the task. */
#अगर ( configUSE_TASK_DPFPU_SUPPORT == 1 )

    ढेर_Type_t ulPortTaskHasDPFPUContext = portNO_DPFPU_CONTEXT;

#पूर्ण_अगर /* configUSE_TASK_DPFPU_SUPPORT */

/* This is accessed by the inline assembler functions so is file scope for
 * convenience. */
बाह्य व्योम * pxCurrentTCB;
बाह्य व्योम vTaskSwitchContext( व्योम );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ढेर_Type_t * px_Port_Initialise_ढेर( ढेर_Type_t * px_शीर्ष_Of_ढेर,
                                     TaskFunction_t pxCode,
                                     व्योम * pvParameters )
{
    /* R0 is not included as it is the stack pointer. */

    *px_शीर्ष_Of_ढेर = 0x00;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = portINITIAL_PSW;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pxCode;

    /* When debugging it can be useful if every register is set to a known
     * value.  Otherwise code space can be saved by just setting the registers
     * that need to be set. */
    #अगर_घोषित USE_FULL_REGISTER_INITIALISATION
    {
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = 0xffffffff; /* r15. */
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = 0xeeeeeeee;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = 0xdddddddd;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = 0xcccccccc;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = 0xbbbbbbbb;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = 0xaaaaaaaa;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = 0x99999999;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = 0x88888888;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = 0x77777777;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = 0x66666666;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = 0x55555555;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = 0x44444444;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = 0x33333333;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = 0x22222222;
        px_शीर्ष_Of_ढेर--;
    }
    #अन्यथा /* ifdef USE_FULL_REGISTER_INITIALISATION */
    {
        px_शीर्ष_Of_ढेर -= 15;
    }
    #पूर्ण_अगर /* ifdef USE_FULL_REGISTER_INITIALISATION */

    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pvParameters; /* R1 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = portINITIAL_FPSW;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x11111111; /* Accumulator 1. */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x22222222; /* Accumulator 1. */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x33333333; /* Accumulator 1. */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x44444444; /* Accumulator 0. */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x55555555; /* Accumulator 0. */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x66666666; /* Accumulator 0. */

    #अगर ( configUSE_TASK_DPFPU_SUPPORT == 1 )
    {
        /* The task will start without a DPFPU context.  A task that
         * uses the DPFPU hardware must call vPortTaskUsesDPFPU() before
         * executing any floating point instructions. */
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = portNO_DPFPU_CONTEXT;
    }
    #या_अगर ( configUSE_TASK_DPFPU_SUPPORT == 2 )
    {
        /* The task will start with a DPFPU context.  Leave enough
         * space for the registers - and ensure they are initialised if desired. */
        #अगर_घोषित USE_FULL_REGISTER_INITIALISATION
        {
            px_शीर्ष_Of_ढेर -= 2;
            *( द्विगुन * ) px_शीर्ष_Of_ढेर = 1515.1515;  /* DR15. */
            px_शीर्ष_Of_ढेर -= 2;
            *( द्विगुन * ) px_शीर्ष_Of_ढेर = 1414.1414;  /* DR14. */
            px_शीर्ष_Of_ढेर -= 2;
            *( द्विगुन * ) px_शीर्ष_Of_ढेर = 1313.1313;  /* DR13. */
            px_शीर्ष_Of_ढेर -= 2;
            *( द्विगुन * ) px_शीर्ष_Of_ढेर = 1212.1212;  /* DR12. */
            px_शीर्ष_Of_ढेर -= 2;
            *( द्विगुन * ) px_शीर्ष_Of_ढेर = 1111.1111;  /* DR11. */
            px_शीर्ष_Of_ढेर -= 2;
            *( द्विगुन * ) px_शीर्ष_Of_ढेर = 1010.1010;  /* DR10. */
            px_शीर्ष_Of_ढेर -= 2;
            *( द्विगुन * ) px_शीर्ष_Of_ढेर = 909.0909;   /* DR9. */
            px_शीर्ष_Of_ढेर -= 2;
            *( द्विगुन * ) px_शीर्ष_Of_ढेर = 808.0808;   /* DR8. */
            px_शीर्ष_Of_ढेर -= 2;
            *( द्विगुन * ) px_शीर्ष_Of_ढेर = 707.0707;   /* DR7. */
            px_शीर्ष_Of_ढेर -= 2;
            *( द्विगुन * ) px_शीर्ष_Of_ढेर = 606.0606;   /* DR6. */
            px_शीर्ष_Of_ढेर -= 2;
            *( द्विगुन * ) px_शीर्ष_Of_ढेर = 505.0505;   /* DR5. */
            px_शीर्ष_Of_ढेर -= 2;
            *( द्विगुन * ) px_शीर्ष_Of_ढेर = 404.0404;   /* DR4. */
            px_शीर्ष_Of_ढेर -= 2;
            *( द्विगुन * ) px_शीर्ष_Of_ढेर = 303.0303;   /* DR3. */
            px_शीर्ष_Of_ढेर -= 2;
            *( द्विगुन * ) px_शीर्ष_Of_ढेर = 202.0202;   /* DR2. */
            px_शीर्ष_Of_ढेर -= 2;
            *( द्विगुन * ) px_शीर्ष_Of_ढेर = 101.0101;   /* DR1. */
            px_शीर्ष_Of_ढेर -= 2;
            *( द्विगुन * ) px_शीर्ष_Of_ढेर = 9876.54321; /* DR0. */
        }
        #अन्यथा /* ifdef USE_FULL_REGISTER_INITIALISATION */
        {
            px_शीर्ष_Of_ढेर -= port_DPFPU_तथ्य_REGISTER_शब्दगण;
            स_रखो( px_शीर्ष_Of_ढेर, 0x00, port_DPFPU_तथ्य_REGISTER_शब्दगण * माप( ढेर_Type_t ) );
        }
        #पूर्ण_अगर /* ifdef USE_FULL_REGISTER_INITIALISATION */
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = portINITIAL_DECNT; /* DECNT. */
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = portINITIAL_DCMR;  /* DCMR. */
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = portINITIAL_DPSW;  /* DPSW. */
    }
    #या_अगर ( configUSE_TASK_DPFPU_SUPPORT == 0 )
    {
        /* Omit DPFPU support. */
    }
    #अन्यथा /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */
    {
        #त्रुटि Invalid configUSE_TASK_DPFPU_SUPPORT setting - configUSE_TASK_DPFPU_SUPPORT must be set to 0, 1, 2, or बायाँ undefined.
    }
    #पूर्ण_अगर /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */

    वापस px_शीर्ष_Of_ढेर;
}
/*-----------------------------------------------------------*/

#अगर ( configUSE_TASK_DPFPU_SUPPORT == 1 )

    व्योम vPortTaskUsesDPFPU( व्योम )
    {
        /* A task is registering the fact that it needs a DPFPU context.  Set the
         * DPFPU flag (which is saved as part of the task context). */
        ulPortTaskHasDPFPUContext = portHAS_DPFPU_CONTEXT;
    }

#पूर्ण_अगर /* configUSE_TASK_DPFPU_SUPPORT */
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( व्योम )
{
    बाह्य व्योम vApplicationSetupTimerInterrupt( व्योम );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    अगर( pxCurrentTCB != शून्य )
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

    /* Should not get here. */
    वापस pdFAIL;
}
/*-----------------------------------------------------------*/

व्योम vPortEndScheduler( व्योम )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pxCurrentTCB == शून्य );
}
/*-----------------------------------------------------------*/

अटल व्योम prvStartFirstTask( व्योम )
{
    __asm अस्थिर
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

        #अगर ( configUSE_TASK_DPFPU_SUPPORT == 1 )

            /* The restored ulPortTaskHasDPFPUContext is to be zero here.
             * So, it is never necessary to restore the DPFPU context here. */
            "POP        R15                                 \n" \
            "MOV.L      #_ulPortTaskHasDPFPUContext, R14    \n" \
            "MOV.L      R15, [R14]                          \n" \

        #या_अगर ( configUSE_TASK_DPFPU_SUPPORT == 2 )
            /* Restore the DPFPU context. */
            "DPOPM.L    DPSW-DECNT              \n" \
            "DPOPM.D    DR0-DR15                \n" \

        #पूर्ण_अगर /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */

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

व्योम vSoftwareInterruptISR( व्योम )
{
    __asm अस्थिर
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

        #अगर ( configUSE_TASK_DPFPU_SUPPORT == 1 )

            /* Does the task have a DPFPU context that needs saving?  If
             * ulPortTaskHasDPFPUContext is 0 then no. */
            "MOV.L      #_ulPortTaskHasDPFPUContext, R15    \n" \
            "MOV.L      [R15], R15                          \n" \
            "CMP        #0, R15                             \n" \

            /* Save the DPFPU context, if any. */
            "BEQ.B      ?+                          \n" \
            "DPUSHM.D   DR0-DR15                    \n" \
            "DPUSHM.L   DPSW-DECNT                  \n" \
            "?:                                     \n" \

            /* Save ulPortTaskHasDPFPUContext itself. */
            "PUSH.L     R15                         \n" \

        #या_अगर ( configUSE_TASK_DPFPU_SUPPORT == 2 )
            /* Save the DPFPU context, always. */
            "DPUSHM.D   DR0-DR15                    \n" \
            "DPUSHM.L   DPSW-DECNT                  \n" \

        #पूर्ण_अगर /* if ( configUSE_TASK_DPFPU_SUPPORT == 1 ) */


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

        #अगर ( configUSE_TASK_DPFPU_SUPPORT == 1 )

            /* Is there a DPFPU context to restore?  If the restored
             * ulPortTaskHasDPFPUContext is zero then no. */
            "POP        R15                                 \n" \
            "MOV.L      #_ulPortTaskHasDPFPUContext, R14    \n" \
            "MOV.L      R15, [R14]                          \n" \
            "CMP        #0, R15                             \n" \

            /* Restore the DPFPU context, if any. */
            "BEQ.B      ?+                          \n" \
            "DPOPM.L    DPSW-DECNT                  \n" \
            "DPOPM.D    DR0-DR15                    \n" \
            "?:                                     \n" \

        #या_अगर ( configUSE_TASK_DPFPU_SUPPORT == 2 )
            /* Restore the DPFPU context, always. */
            "DPOPM.L    DPSW-DECNT                  \n" \
            "DPOPM.D    DR0-DR15                    \n" \

        #पूर्ण_अगर /* if( configUSE_TASK_DPFPU_SUPPORT == 1 ) */

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
        ::"i" ( configMAX_SYSCALL_INTERRUPT_PRIORITY ), "i" ( configKERNEL_INTERRUPT_PRIORITY )
    );
}
/*-----------------------------------------------------------*/

व्योम vTickISR( व्योम )
{
    /* Re-enabled interrupts. */
    __asm अस्थिर ( "SETPSW    I" );

    /* Increment the tick, and perform any processing the new tick value
     * necessitates.  Ensure IPL is at the max syscall value first. */
    portMASK_INTERRUPTS_FROM_KERNEL_ISR();
    {
        अगर( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    portUNMASK_INTERRUPTS_FROM_KERNEL_ISR();
}
/*-----------------------------------------------------------*/

uint32_t ulPortGetIPL( व्योम )
{
    __asm अस्थिर
    (
        "MVFC   PSW, R1         \n" \
        "SHLR   #24, R1         \n" \
        "RTS                      "
    );

    /* This will never get executed, but keeps the compiler from complaining. */
    वापस 0;
}
/*-----------------------------------------------------------*/

व्योम vPortSetIPL( uint32_t ulNewIPL )
{
    /* Avoid compiler warning about unreferenced parameter. */
    ( व्योम ) ulNewIPL;

    __asm अस्थिर
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
