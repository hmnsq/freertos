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

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Library includes. */
#ضمن "string.h"

/* Hardware specifics. */
#إذا ( configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H == 1 )

    #ضمن "platform.h"

#وإلا /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

    #ضمن "iodefine.h"

#endif /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
 * PSW is set with U and I set, and PM and IPL clear. */
#define portINITIAL_PSW     ( ( تيندنن_Type_t ) 0x00030000 )
#define portINITIAL_FPSW    ( ( تيندنن_Type_t ) 0x00000100 )

/* These macros allow a critical section to be added around the call to
 * xTaskIncrementTick(), which is only ever called from interrupts at the kernel
 * priority - ie a known priority.  Therefore these local macros are a slight
 * optimisation compared to calling the global SET/CLEAR_INTERRUPT_MASK macros,
 * which would require the old IPL to be read first and stored in a local variable. */
#define portMASK_INTERRUPTS_FROM_KERNEL_ISR()      __asm متطاير ( "MVTIPL    %0" ::"i" ( configMAX_SYSCALL_INTERRUPT_PRIORITY ) )
#define portUNMASK_INTERRUPTS_FROM_KERNEL_ISR()    __asm متطاير ( "MVTIPL    %0" ::"i" ( configKERNEL_INTERRUPT_PRIORITY ) )

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
ساكن فراغ prvStartFirstTask( فراغ ) __attribute__( ( naked ) );

/*
 * Software interrupt handler.  Performs the actual context switch (saving and
 * restoring of registers).  Written in asm code as direct register access is
 * required.
 */
#إذا ( configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H == 1 )
    R_BSP_PRAGMA_INTERRUPT( vSoftwareInterruptISR, VECT( ICU, SWINT ) )
    R_BSP_ATTRIB_INTERRUPT فراغ vSoftwareInterruptISR( فراغ ) __attribute__( ( naked ) );
#وإلا /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */
    فراغ vSoftwareInterruptISR( فراغ ) __attribute__( ( naked ) );
#endif /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H  */

/*
 * The tick ISR handler.  The peripheral used is configured by the application
 * via a hook/callback function.
 */
#إذا ( configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H == 1 )

    R_BSP_PRAGMA_INTERRUPT( vTickISR, _VECT( configTICK_VECTOR ) )
    R_BSP_ATTRIB_INTERRUPT فراغ vTickISR( فراغ ); /* Do not add __attribute__( ( interrupt ) ). */

#وإلا /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

    فراغ vTickISR( فراغ ) __attribute__( ( interrupt ) );

#endif /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */
/*-----------------------------------------------------------*/

خارجي فراغ * pxCurrentTCB;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
تيندنن_Type_t * px_Port_Initialise_تيندنن( تيندنن_Type_t * px_اتس_Of_تيندنن,
                                     TaskFunction_t pxCode,
                                     فراغ * pvParameters )
{
    /* R0 is not included as it is the stack pointer. */

    *px_اتس_Of_تيندنن = 0x00;
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = portINITIAL_PSW;
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) pxCode;

    /* When debugging it can be useful if every register is set to a known
     * value.  Otherwise code space can be saved by just setting the registers
     * that need to be set. */
    #ifdef USE_FULL_REGISTER_INITIALISATION
    {
        px_اتس_Of_تيندنن--;
        *px_اتس_Of_تيندنن = 0xffffffff; /* r15. */
        px_اتس_Of_تيندنن--;
        *px_اتس_Of_تيندنن = 0xeeeeeeee;
        px_اتس_Of_تيندنن--;
        *px_اتس_Of_تيندنن = 0xdddddddd;
        px_اتس_Of_تيندنن--;
        *px_اتس_Of_تيندنن = 0xcccccccc;
        px_اتس_Of_تيندنن--;
        *px_اتس_Of_تيندنن = 0xbbbbbbbb;
        px_اتس_Of_تيندنن--;
        *px_اتس_Of_تيندنن = 0xaaaaaaaa;
        px_اتس_Of_تيندنن--;
        *px_اتس_Of_تيندنن = 0x99999999;
        px_اتس_Of_تيندنن--;
        *px_اتس_Of_تيندنن = 0x88888888;
        px_اتس_Of_تيندنن--;
        *px_اتس_Of_تيندنن = 0x77777777;
        px_اتس_Of_تيندنن--;
        *px_اتس_Of_تيندنن = 0x66666666;
        px_اتس_Of_تيندنن--;
        *px_اتس_Of_تيندنن = 0x55555555;
        px_اتس_Of_تيندنن--;
        *px_اتس_Of_تيندنن = 0x44444444;
        px_اتس_Of_تيندنن--;
        *px_اتس_Of_تيندنن = 0x33333333;
        px_اتس_Of_تيندنن--;
        *px_اتس_Of_تيندنن = 0x22222222;
        px_اتس_Of_تيندنن--;
    }
    #وإلا /* ifdef USE_FULL_REGISTER_INITIALISATION */
    {
        px_اتس_Of_تيندنن -= 15;
    }
    #endif /* ifdef USE_FULL_REGISTER_INITIALISATION */

    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) pvParameters; /* R1 */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = portINITIAL_FPSW;
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = 0x11111111; /* Accumulator 0. */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = 0x22222222; /* Accumulator 0. */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = 0x33333333; /* Accumulator 0. */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = 0x44444444; /* Accumulator 1. */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = 0x55555555; /* Accumulator 1. */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = 0x66666666; /* Accumulator 1. */

    أرجع px_اتس_Of_تيندنن;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( فراغ )
{
    خارجي فراغ vApplicationSetupTimerInterrupt( فراغ );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    إذا( pxCurrentTCB != عدم )
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
    أرجع pdFAIL;
}
/*-----------------------------------------------------------*/

فراغ vPortEndScheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pxCurrentTCB == عدم );
}
/*-----------------------------------------------------------*/

ساكن فراغ prvStartFirstTask( فراغ )
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

فراغ vSoftwareInterruptISR( فراغ )
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

        /* Save the FPSW and accumulator. */
        "MVFC       FPSW, R15                   \n" \
        "PUSH.L     R15                         \n" \
        "MVFACGU    #0, A1, R15                 \n" \
        "PUSH.L     R15                         \n" \
        "MVFACHI    #0, A1, R15                 \n" \
        "PUSH.L     R15                         \n" \
        /* Low order word. */
        "MVFACLO    #0, A1, R15                 \n" \
        "PUSH.L     R15                         \n" \
        "MVFACGU    #0, A0, R15                 \n" \
        "PUSH.L     R15                         \n" \
        "MVFACHI    #0, A0, R15                 \n" \
        "PUSH.L     R15                         \n" \
        /* Low order word. */
        "MVFACLO    #0, A0, R15                 \n" \
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

فراغ vTickISR( فراغ )
{
    /* Re-enabled interrupts. */
    __asm متطاير ( "SETPSW I" );

    /* Increment the tick, and perform any processing the new tick value
     * necessitates.  Ensure IPL is at the max syscall value first. */
    portMASK_INTERRUPTS_FROM_KERNEL_ISR();
    {
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    portUNMASK_INTERRUPTS_FROM_KERNEL_ISR();
}
/*-----------------------------------------------------------*/

uint32_t ulPortGetIPL( فراغ )
{
    __asm متطاير
    (
        "MVFC   PSW, R1         \n" \
        "SHLR   #24, R1         \n" \
        "RTS                      "
    );

    /* This will never get executed, but keeps the compiler from complaining. */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ vPortSetIPL( uint32_t ulNewIPL )
{
    /* Avoid compiler warning about unreferenced parameter. */
    ( فراغ ) ulNewIPL;

    __asm متطاير
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
