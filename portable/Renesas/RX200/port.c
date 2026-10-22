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
 * Implementation of functions defined in portable.h for the RX200 port.
 *----------------------------------------------------------*/

/* Scheduler includes. */
#شامل "FreeRTOS.h"
#شامل "task.h"

/* Library includes. */
#شامل "string.h"

/* Hardware specifics. */
#شامل "iodefine.h"

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
PSW is set with U and I set, and PM and IPL clear. */
#تعریف_کرو پورٹ_INITIAL_PSW     ( ( ڈھیر_Type_t ) 0x00030000 )

/*-----------------------------------------------------------*/

/* The following lines are to ensure vSoftwareInterruptEntry can be referenced,
 and therefore installed in the vector table, when the FreeRTOS code is built
as a library. */
خارجی بنیاد_Type_t v_Software_مداخلت_اندراج;
ثابت بنیاد_Type_t * p_v_Software_مداخلت_اندراج = &v_Software_مداخلت_اندراج;

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
ساکن خالی prv_آغاز_پہلا_Task( خالی );

/*
 * Software interrupt handler.  Performs the actual context switch (saving and
 * restoring of registers).  Written in asm code as direct register access is
 * required.
 */
ساکن خالی prvYieldHandler( خالی );

/*
 * The entry point for the software interrupt handler.  This is the function
 * that calls the inline asm function prvYieldHandler().  It is installed in
 * the vector table, but the code that installs it is in prvYieldHandler rather
 * than using a #pragma.
 */
خالی v_Software_مداخلت_ISR( خالی );

/*-----------------------------------------------------------*/

/* This is accessed by the inline assembler functions so is file scope for
convenience. */
خارجی خالی *pxCurrentTCB;
خارجی خالی vTaskSwitchContext( خالی );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t *px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t *px_چوٹی_کا_ڈھیر, TaskFunction_t px_رمز, خالی *pvParameters )
{
    /* Offset to end up on 8 byte boundary. */
    px_چوٹی_کا_ڈھیر--;

    /* R0 is not included as it is the stack pointer. */
    *px_چوٹی_کا_ڈھیر = 0x00;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x00;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = پورٹ_INITIAL_PSW;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) px_رمز;

    /* When debugging it can be useful if every register is set to a known
    value.  Otherwise code space can be saved by just setting the registers
    that need to be set. */
    #اگر_تعریف_شدہ USE_بھرا_رجسٹر_INITIALISATION
    {
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x12345678; /* r15. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0xaaaabbbb;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0xdddddddd;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0xcccccccc;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0xbbbbbbbb;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0xaaaaaaaa;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x99999999;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x88888888;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x77777777;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x66666666;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x55555555;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x44444444;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x33333333;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x22222222;
        px_چوٹی_کا_ڈھیر--;
    }
    #ورنہ
    {
        px_چوٹی_کا_ڈھیر -= 15;
    }
    #اگر_ختم

    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) pvParameters; /* R1 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x12345678; /* Accumulator. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x87654321; /* Accumulator. */

    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
خارجی خالی v_Application_تیاری_Timer_مداخلت( خالی );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    اگر( pxCurrentTCB != تہی )
    {
        /* Call an application function to set up the timer that will generate the
        tick interrupt.  This way the application can decide which peripheral to
        use.  A demo application is provided to show a suitable example. */
        v_Application_تیاری_Timer_مداخلت();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = config_KERNEL_مداخلت_ترجیح;

        /* Start the first task. */
        prv_آغاز_پہلا_Task();
    }

    /* Just to make sure the function is not optimised away. */
    ( خالی ) v_Software_مداخلت_ISR();

    /* Should not get here. */
    واپس pdFAIL;
}
/*-----------------------------------------------------------*/

#ہدایت inline_asm prv_آغاز_پہلا_Task
ساکن خالی prv_آغاز_پہلا_Task( خالی )
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
    نکالو_2     R15
    MVTACLO R15         /* Accumulator low 32 bits. */
    نکالو_2     R15
    MVTACHI R15         /* Accumulator high 32 bits. */
    POPM    R1-R15      /* R1 to R15 - R0 is not included as it is the SP. */
    RTE                 /* This pops the remaining registers. */
    NOP
    NOP
}
/*-----------------------------------------------------------*/

#ہدایت مداخلت ( vTickISR( vect = _VECT( config_TICK_سمتیہ ), enable ) )
خالی vTickISR( خالی )
{
    /* Increment the tick, and perform any processing the new tick value
    necessitates. */
    سیٹ_ipl( config_MAX_SYSCALL_مداخلت_ترجیح );
    {
        اگر( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    سیٹ_ipl( config_KERNEL_مداخلت_ترجیح );
}
/*-----------------------------------------------------------*/

خالی v_Software_مداخلت_ISR( خالی )
{
    prvYieldHandler();
}
/*-----------------------------------------------------------*/

#ہدایت inline_asm prvYieldHandler
ساکن خالی prvYieldHandler( خالی )
{
    /* Re-enable interrupts. */
    SETPSW  I

    /* Move the data that was automatically pushed onto the interrupt stack when
    the interrupt occurred from the interrupt stack to the user stack.

    R15 is saved before it is clobbered. */
    ڈالو_2.L  R15

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
    جوڑو_2 #12, R0

    /* All the rest of the registers are saved directly to the user stack. */
    SETPSW  U

    /* Save the rest of the general registers (R15 has been saved already). */
    PUSHM   R1-R14

    /* Save the accumulator. */
    MVFACHI R15
    ڈالو_2.L  R15
    MVFACMI R15 ; درمیان ترتیب لفظ.
    SHLL    #16, R15 ; Shifted بایاں as it is restored مقصد the کم_2 ترتیب لفظ.
    ڈالو_2.L  R15

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
    نکالو_2     R15
    MVTACLO R15
    نکالو_2     R15
    MVTACHI R15
    POPM    R1-R15
    RTE
    NOP
    NOP
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( pxCurrentTCB == تہی );

    /* The following line is just to prevent the symbol getting optimised away. */
    ( خالی ) vTaskSwitchContext();
}
/*-----------------------------------------------------------*/
