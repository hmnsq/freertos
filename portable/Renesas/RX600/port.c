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
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/* Library includes. */
#अन्तर्भाव "string.h"

/* Hardware specifics. */
#अन्तर्भाव "iodefine.h"

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
PSW is set with U and I set, and PM and IPL clear. */
#define portINITIAL_PSW     ( ( ढेर_Type_t ) 0x00030000 )
#define portINITIAL_FPSW    ( ( ढेर_Type_t ) 0x00000100 )

/*-----------------------------------------------------------*/

/* The following lines are to ensure vSoftwareInterruptEntry can be referenced,
 and therefore installed in the vector table, when the FreeRTOS code is built
as a library. */
बाह्य BaseType_t vSoftwareInterruptEntry;
ध्रुव BaseType_t * p_vSoftwareInterruptEntry = &vSoftwareInterruptEntry;

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
स्थिर शून्य prvStartFirstTask( शून्य );

/*
 * Software interrupt handler.  Performs the actual context switch (saving and
 * restoring of registers).  Written in asm code as direct register access is
 * required.
 */
स्थिर शून्य prvYieldHandler( शून्य );

/*
 * The entry point for the software interrupt handler.  This is the function
 * that calls the inline asm function prvYieldHandler().  It is installed in
 * the vector table, but the code that installs it is in prvYieldHandler rather
 * than using a #pragma.
 */
शून्य vSoftwareInterruptISR( शून्य );

/*-----------------------------------------------------------*/

/* This is accessed by the inline assembler functions so is file scope for
convenience. */
बाह्य शून्य *pxCurrentTCB;
बाह्य शून्य vTaskSwitchContext( शून्य );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ढेर_Type_t *px_Port_Initialise_ढेर( ढेर_Type_t *px_शीर्ष_Of_ढेर, TaskFunction_t pxCode, शून्य *pvParameters )
{
    /* R0 is not included as it is the stack pointer. */

    *px_शीर्ष_Of_ढेर = 0x00;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = portINITIAL_PSW;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pxCode;

    /* When debugging it can be useful if every register is set to a known
    value.  Otherwise code space can be saved by just setting the registers
    that need to be set. */
    #ifdef USE_FULL_REGISTER_INITIALISATION
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
    #अन्यथा
    {
        px_शीर्ष_Of_ढेर -= 15;
    }
    #endif

    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pvParameters; /* R1 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = portINITIAL_FPSW;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x12345678; /* Accumulator. */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x87654321; /* Accumulator. */

    प्रत्यागम px_शीर्ष_Of_ढेर;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( शून्य )
{
बाह्य शून्य vApplicationSetupTimerInterrupt( शून्य );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    यदि( pxCurrentTCB != रिक्त )
    {
        /* Call an application function to set up the timer that will generate the
        tick interrupt.  This way the application can decide which peripheral to
        use.  A demo application is provided to show a suitable example. */
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
    ( शून्य ) vSoftwareInterruptISR();

    /* Should not get here. */
    प्रत्यागम pdFAIL;
}
/*-----------------------------------------------------------*/

#pragma inline_asm prvStartFirstTask
स्थिर शून्य prvStartFirstTask( शून्य )
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
    निकालो_2     R15
    MVTACLO R15         /* Accumulator low 32 bits. */
    निकालो_2     R15
    MVTACHI R15         /* Accumulator high 32 bits. */
    निकालो_2     R15
    MVTC    R15,FPSW    /* Floating point status word. */
    POPM    R1-R15      /* R1 to R15 - R0 is not included as it is the SP. */
    RTE                 /* This pops the remaining registers. */
    NOP
    NOP
}
/*-----------------------------------------------------------*/

#pragma interrupt ( vTickISR( vect = _VECT( configTICK_VECTOR ), enable ) )
शून्य vTickISR( शून्य )
{
    /* Increment the tick, and perform any processing the new tick value
    necessitates. */
    set_ipl( configMAX_SYSCALL_INTERRUPT_PRIORITY );
    {
        यदि( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    set_ipl( configKERNEL_INTERRUPT_PRIORITY );
}
/*-----------------------------------------------------------*/

शून्य vSoftwareInterruptISR( शून्य )
{
    prvYieldHandler();
}
/*-----------------------------------------------------------*/

#pragma inline_asm prvYieldHandler
स्थिर शून्य prvYieldHandler( शून्य )
{
    /* Re-enable interrupts. */
    SETPSW  I

    /* Move the data that was automatically pushed onto the interrupt stack when
    the interrupt occurred from the interrupt stack to the user stack.

    R15 is saved before it is clobbered. */
    धकेलो_2.L  R15

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
    ADD #12, R0

    /* All the rest of the registers are saved directly to the user stack. */
    SETPSW  U

    /* Save the rest of the general registers (R15 has been saved already). */
    PUSHM   R1-R14

    /* Save the FPSW and accumulator. */
    MVFC    FPSW, R15
    धकेलो_2.L  R15
    MVFACHI R15
    धकेलो_2.L  R15
    MVFACMI R15 ; मध्य order word.
    SHLL    #16, R15 ; Shifted बायाँ as it is restored to the निचला_2 order word.
    धकेलो_2.L  R15

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
    निकालो_2     R15
    MVTACLO R15
    निकालो_2     R15
    MVTACHI R15
    निकालो_2     R15
    MVTC    R15,FPSW
    POPM    R1-R15
    RTE
    NOP
    NOP
}
/*-----------------------------------------------------------*/

शून्य vPortEndScheduler( शून्य )
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( pxCurrentTCB == रिक्त );

    /* The following line is just to prevent the symbol getting optimised away. */
    ( शून्य ) vTaskSwitchContext();
}
/*-----------------------------------------------------------*/
