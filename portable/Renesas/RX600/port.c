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
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Library includes. */
#ضمن "string.h"

/* Hardware specifics. */
#ضمن "iodefine.h"

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
PSW is set with U and I set, and PM and IPL clear. */
#وصف_ڪريو پورٽ_INITIAL_PSW     ( ( ڍير_Type_t ) 0x00030000 )
#وصف_ڪريو پورٽ_INITIAL_FPSW    ( ( ڍير_Type_t ) 0x00000100 )

/*-----------------------------------------------------------*/

/* The following lines are to ensure vSoftwareInterruptEntry can be referenced,
 and therefore installed in the vector table, when the FreeRTOS code is built
as a library. */
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

/*-----------------------------------------------------------*/

/* This is accessed by the inline assembler functions so is file scope for
convenience. */
خارجي فراغ *pxCurrentTCB;
خارجي فراغ vTaskSwitchContext( فراغ );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڍير_Type_t *px_پورٽ_Initialise_ڍير( ڍير_Type_t *px_چوٽي_جو_ڍير, TaskFunction_t px_ڪوڊ, فراغ *pvParameters )
{
    /* R0 is not included as it is the stack pointer. */

    *px_چوٽي_جو_ڍير = 0x00;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = پورٽ_INITIAL_PSW;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) px_ڪوڊ;

    /* When debugging it can be useful if every register is set to a known
    value.  Otherwise code space can be saved by just setting the registers
    that need to be set. */
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
    #وإلا
    {
        px_چوٽي_جو_ڍير -= 15;
    }
    #جيڪڏهن_پورو

    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pvParameters; /* R1 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = پورٽ_INITIAL_FPSW;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x12345678; /* Accumulator. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x87654321; /* Accumulator. */

    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
خارجي فراغ v_Application_تياري_Timer_مداخلت( فراغ );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    إذا( pxCurrentTCB != عدم )
    {
        /* Call an application function to set up the timer that will generate the
        tick interrupt.  This way the application can decide which peripheral to
        use.  A demo application is provided to show a suitable example. */
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

#هدايت inline_asm prv_شروعات_پهريون_Task
ساكن فراغ prv_شروعات_پهريون_Task( فراغ )
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
    ڪڍو_2     R15
    MVTACLO R15         /* Accumulator low 32 bits. */
    ڪڍو_2     R15
    MVTACHI R15         /* Accumulator high 32 bits. */
    ڪڍو_2     R15
    MVTC    R15,FPSW    /* Floating point status word. */
    POPM    R1-R15      /* R1 to R15 - R0 is not included as it is the SP. */
    RTE                 /* This pops the remaining registers. */
    NOP
    NOP
}
/*-----------------------------------------------------------*/

#هدايت مداخلت ( vTickISR( vect = _VECT( config_TICK_ويڪٽر ), enable ) )
فراغ vTickISR( فراغ )
{
    /* Increment the tick, and perform any processing the new tick value
    necessitates. */
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

فراغ v_Software_مداخلت_ISR( فراغ )
{
    prvYieldHandler();
}
/*-----------------------------------------------------------*/

#هدايت inline_asm prvYieldHandler
ساكن فراغ prvYieldHandler( فراغ )
{
    /* Re-enable interrupts. */
    SETPSW  I

    /* Move the data that was automatically pushed onto the interrupt stack when
    the interrupt occurred from the interrupt stack to the user stack.

    R15 is saved before it is clobbered. */
    ڌڪو_2.L  R15

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
    جوڙيو_2 #12, R0

    /* All the rest of the registers are saved directly to the user stack. */
    SETPSW  U

    /* Save the rest of the general registers (R15 has been saved already). */
    PUSHM   R1-R14

    /* Save the FPSW and accumulator. */
    MVFC    FPSW, R15
    ڌڪو_2.L  R15
    MVFACHI R15
    ڌڪو_2.L  R15
    MVFACMI R15 ; وچ ترتيب لفظ_2.
    SHLL    #16, R15 ; Shifted کاٻو as it is restored منزل the هيٺيون_2 ترتيب لفظ_2.
    ڌڪو_2.L  R15

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
    ڪڍو_2     R15
    MVTACLO R15
    ڪڍو_2     R15
    MVTACHI R15
    ڪڍو_2     R15
    MVTC    R15,FPSW
    POPM    R1-R15
    RTE
    NOP
    NOP
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( pxCurrentTCB == عدم );

    /* The following line is just to prevent the symbol getting optimised away. */
    ( فراغ ) vTaskSwitchContext();
}
/*-----------------------------------------------------------*/
