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
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* Library includes. */
#ಅನ್ತರ್ಭಾವ "string.h"

/* Hardware specifics. */
#ಅನ್ತರ್ಭಾವ "iodefine.h"

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
PSW is set with U and I set, and PM and IPL clear. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_PSW     ( ( ರಾಶಿ_Type_t ) 0x00030000 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_FPSW    ( ( ರಾಶಿ_Type_t ) 0x00000100 )

/*-----------------------------------------------------------*/

/* The following lines are to ensure vSoftwareInterruptEntry can be referenced,
 and therefore installed in the vector table, when the FreeRTOS code is built
as a library. */
ಬಾಹ್ಯ ತಳ_Type_t v_Software_ಅಡಚಣೆ_ನಮೂದು;
ಸ್ಥಿರಾಂಕ ತಳ_Type_t * p_v_Software_ಅಡಚಣೆ_ನಮೂದು = &v_Software_ಅಡಚಣೆ_ನಮೂದು;

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ );

/*
 * Software interrupt handler.  Performs the actual context switch (saving and
 * restoring of registers).  Written in asm code as direct register access is
 * required.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvYieldHandler( ಶೂನ್ಯ );

/*
 * The entry point for the software interrupt handler.  This is the function
 * that calls the inline asm function prvYieldHandler().  It is installed in
 * the vector table, but the code that installs it is in prvYieldHandler rather
 * than using a #pragma.
 */
ಶೂನ್ಯ v_Software_ಅಡಚಣೆ_ISR( ಶೂನ್ಯ );

/*-----------------------------------------------------------*/

/* This is accessed by the inline assembler functions so is file scope for
convenience. */
ಬಾಹ್ಯ ಶೂನ್ಯ *pxCurrentTCB;
ಬಾಹ್ಯ ಶೂನ್ಯ vTaskSwitchContext( ಶೂನ್ಯ );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t *px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t *px_ತುದಿ_ದ_ರಾಶಿ, TaskFunction_t px_ಸಂಕೇತ, ಶೂನ್ಯ *pvParameters )
{
    /* R0 is not included as it is the stack pointer. */

    *px_ತುದಿ_ದ_ರಾಶಿ = 0x00;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_PSW;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ;

    /* When debugging it can be useful if every register is set to a known
    value.  Otherwise code space can be saved by just setting the registers
    that need to be set. */
    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_ತುಂಬಿದ_ರಿಜಿಸ್ಟರ್_INITIALISATION
    {
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0xffffffff; /* r15. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0xeeeeeeee;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0xdddddddd;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0xcccccccc;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0xbbbbbbbb;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0xaaaaaaaa;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x99999999;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x88888888;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x77777777;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x66666666;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x55555555;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x44444444;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x33333333;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x22222222;
        px_ತುದಿ_ದ_ರಾಶಿ--;
    }
    #ಇಲ್ಲದಿದ್ದರೆ
    {
        px_ತುದಿ_ದ_ರಾಶಿ -= 15;
    }
    #ಆದರೆ_ಅಂತ್ಯ

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters; /* R1 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_FPSW;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x12345678; /* Accumulator. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x87654321; /* Accumulator. */

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
ಬಾಹ್ಯ ಶೂನ್ಯ v_Application_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    ಆದರೆ( pxCurrentTCB != ಖಾಲಿ )
    {
        /* Call an application function to set up the timer that will generate the
        tick interrupt.  This way the application can decide which peripheral to
        use.  A demo application is provided to show a suitable example. */
        v_Application_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = config_KERNEL_ಅಡಚಣೆ_ಆದ್ಯತೆ;

        /* Start the first task. */
        prv_ಆರಂಭ_ಮೊದಲ_Task();
    }

    /* Just to make sure the function is not optimised away. */
    ( ಶೂನ್ಯ ) v_Software_ಅಡಚಣೆ_ISR();

    /* Should not get here. */
    ಹಿಂತಿರುಗಿ pdFAIL;
}
/*-----------------------------------------------------------*/

#ಸೂಚನೆ inline_asm prv_ಆರಂಭ_ಮೊದಲ_Task
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ )
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
    ತೆಗೆ_3     R15
    MVTACLO R15         /* Accumulator low 32 bits. */
    ತೆಗೆ_3     R15
    MVTACHI R15         /* Accumulator high 32 bits. */
    ತೆಗೆ_3     R15
    MVTC    R15,FPSW    /* Floating point status word. */
    POPM    R1-R15      /* R1 to R15 - R0 is not included as it is the SP. */
    RTE                 /* This pops the remaining registers. */
    NOP
    NOP
}
/*-----------------------------------------------------------*/

#ಸೂಚನೆ ಅಡಚಣೆ ( vTickISR( vect = _VECT( config_TICK_ಸದಿಶ ), enable ) )
ಶೂನ್ಯ vTickISR( ಶೂನ್ಯ )
{
    /* Increment the tick, and perform any processing the new tick value
    necessitates. */
    ಗಣ_ipl( config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ );
    {
        ಆದರೆ( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    ಗಣ_ipl( config_KERNEL_ಅಡಚಣೆ_ಆದ್ಯತೆ );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_Software_ಅಡಚಣೆ_ISR( ಶೂನ್ಯ )
{
    prvYieldHandler();
}
/*-----------------------------------------------------------*/

#ಸೂಚನೆ inline_asm prvYieldHandler
ಸ್ಥಿರ ಶೂನ್ಯ prvYieldHandler( ಶೂನ್ಯ )
{
    /* Re-enable interrupts. */
    SETPSW  I

    /* Move the data that was automatically pushed onto the interrupt stack when
    the interrupt occurred from the interrupt stack to the user stack.

    R15 is saved before it is clobbered. */
    ತಳ್ಳು_2.L  R15

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
    ಕೂಡಿಸು_2 #12, R0

    /* All the rest of the registers are saved directly to the user stack. */
    SETPSW  U

    /* Save the rest of the general registers (R15 has been saved already). */
    PUSHM   R1-R14

    /* Save the FPSW and accumulator. */
    MVFC    FPSW, R15
    ತಳ್ಳು_2.L  R15
    MVFACHI R15
    ತಳ್ಳು_2.L  R15
    MVFACMI R15 ; ಮಧ್ಯ ಕ್ರಮ ಶಬ್ದ.
    SHLL    #16, R15 ; Shifted ಎಡ as it is restored ಗಮ್ಯ the ಕೆಳಗಿನ_2 ಕ್ರಮ ಶಬ್ದ.
    ತಳ್ಳು_2.L  R15

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
    ತೆಗೆ_3     R15
    MVTACLO R15
    ತೆಗೆ_3     R15
    MVTACHI R15
    ತೆಗೆ_3     R15
    MVTC    R15,FPSW
    POPM    R1-R15
    RTE
    NOP
    NOP
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( pxCurrentTCB == ಖಾಲಿ );

    /* The following line is just to prevent the symbol getting optimised away. */
    ( ಶೂನ್ಯ ) vTaskSwitchContext();
}
/*-----------------------------------------------------------*/
