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

/* Standard C includes. */
#ضمن "limits.h"

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
#وصف_ڪريو پورٽ_INITIAL_PSW    ( ( ڍير_Type_t ) 0x00030000 )

/* The peripheral clock is divided by this value before being supplying the
 * CMT. */
#إذا ( configUSE_TICKLESS_IDLE == 0 )
    /* If tickless idle is not used then the divisor can be fixed. */
    #وصف_ڪريو پورٽ_CLOCK_ورهائيندڙ    8UL
#وإلاإذا ( configPERIPHERAL_CLOCK_HZ >= 12000000 )
    #وصف_ڪريو پورٽ_CLOCK_ورهائيندڙ    512UL
#وإلاإذا ( configPERIPHERAL_CLOCK_HZ >= 6000000 )
    #وصف_ڪريو پورٽ_CLOCK_ورهائيندڙ    128UL
#وإلاإذا ( configPERIPHERAL_CLOCK_HZ >= 1000000 )
    #وصف_ڪريو پورٽ_CLOCK_ورهائيندڙ    32UL
#وإلا
    #وصف_ڪريو پورٽ_CLOCK_ورهائيندڙ    8UL
#جيڪڏهن_پورو

/* These macros allow a critical section to be added around the call to
 * xTaskIncrementTick(), which is only ever called from interrupts at the kernel
 * priority - ie a known priority.  Therefore these local macros are a slight
 * optimisation compared to calling the global SET/CLEAR_INTERRUPT_MASK macros,
 * which would require the old IPL to be read first and stored in a local variable. */
#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS_FROM_KERNEL_ISR()    __asm متطاير ( "MVTIPL    %0" ::"i" ( config_MAX_SYSCALL_مداخلت_ترجيح ) )
#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS_FROM_KERNEL_ISR()     __asm متطاير ( "MVTIPL    %0" ::"i" ( config_KERNEL_مداخلت_ترجيح ) )

/* Keys required to lock and unlock access to certain system registers
 * respectively. */
#وصف_ڪريو پورٽ_UNLOCK_ڪنجي    0xA50B
#وصف_ڪريو پورٽ_تالو_ڪنجي      0xA500

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
ساكن فراغ prv_شروعات_پهريون_Task( فراغ ) __attribute__( ( naked ) );

/*
 * Software interrupt handler.  Performs the actual context switch (saving and
 * restoring of registers).  Written in asm code as direct register access is
 * required.
 */
#إذا ( config_INCLUDE_PLATFORM_H_INSTEAD_جو_IODEFINE_H == 1 )

    R_BSP_PRAGMA_مداخلت( v_پورٽ_Software_مداخلت_ISR, VECT( ICU, SWINT ) )
    R_BSP_ATTRIB_مداخلت فراغ v_پورٽ_Software_مداخلت_ISR( فراغ ) __attribute__( ( naked ) );

#وإلا /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

    فراغ v_پورٽ_Software_مداخلت_ISR( فراغ ) __attribute__( ( naked ) );

#جيڪڏهن_پورو /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H  */

/*
 * The tick ISR handler.  The peripheral used is configured by the application
 * via a hook/callback function.
 */
#إذا ( config_INCLUDE_PLATFORM_H_INSTEAD_جو_IODEFINE_H == 1 )

    R_BSP_PRAGMA_مداخلت( v_پورٽ_Tick_ISR, _VECT( config_TICK_ويڪٽر ) )
    R_BSP_ATTRIB_مداخلت فراغ v_پورٽ_Tick_ISR( فراغ ); /* Do not add __attribute__( ( interrupt ) ). */

#وإلا /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

    فراغ v_پورٽ_Tick_ISR( فراغ ) __attribute__( ( مداخلت ) );

#جيڪڏهن_پورو /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

/*
 * Sets up the periodic ISR used for the RTOS tick using the CMT.
 * The application writer can define configSETUP_TICK_INTERRUPT() (in
 * FreeRTOSConfig.h) such that their own tick interrupt configuration is used
 * in place of prvSetupTimerInterrupt().
 */
ساكن فراغ prv_تياري_Timer_مداخلت( فراغ );
#جيڪڏهن_وصف_نه_ٿيل config_تياري_TICK_مداخلت

/* The user has not provided their own tick interrupt configuration so use
 * the definition in this file (which uses the interval timer). */
    #وصف_ڪريو config_تياري_TICK_مداخلت()    prv_تياري_Timer_مداخلت()
#جيڪڏهن_پورو /* configSETUP_TICK_INTERRUPT */

/*
 * Called after the sleep mode registers have been configured, prvSleep()
 * executes the pre and post sleep macros, and actually calls the wait
 * instruction.
 */
#إذا configUSE_TICKLESS_IDLE == 1
    ساكن فراغ prvSleep( TickType_t x_Expected_Idle_وقت );
#جيڪڏهن_پورو /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

/* Used in the context save and restore code. */
خارجي فراغ * pxCurrentTCB;

/* Calculate how many clock increments make up a single tick period. */
ساكن ثابت uint32_t ul_ميلاپ_قدر_For_One_Tick = ( ( configPERIPHERAL_CLOCK_HZ / پورٽ_CLOCK_ورهائيندڙ ) / config_TICK_شرح_HZ );

#إذا configUSE_TICKLESS_IDLE == 1

/* Holds the maximum number of ticks that can be suppressed - which is
 * basically how far into the future an interrupt can be generated. Set
 * during initialisation.  This is the maximum possible value that the
 * compare match register can hold divided by ulMatchValueForOneTick. */
    ساكن ثابت TickType_t x_وڌ_کان_وڌ_Possible_Suppressed_Ticks = USHRT_MAX / ( ( configPERIPHERAL_CLOCK_HZ / پورٽ_CLOCK_ورهائيندڙ ) / config_TICK_شرح_HZ );

/* Flag set from the tick interrupt to allow the sleep processing to know if
 * sleep mode was exited because of a tick interrupt, or an interrupt
 * generated by something else. */
    ساكن متطاير uint32_t ulTickFlag = pdFALSE;

/* The CMT counter is stopped temporarily each time it is re-programmed.
 * The following constant offsets the CMT counter match value by the number of
 * CMT counts that would typically be missed while the counter was stopped to
 * compensate for the lost time.  The large difference between the divided CMT
 * clock and the CPU clock means it is likely ulStoppedTimerCompensation will
 * equal zero - and be optimised away. */
    ساكن ثابت uint32_t ulStoppedTimerCompensation = 100UL / ( configCPU_CLOCK_HZ / ( configPERIPHERAL_CLOCK_HZ / پورٽ_CLOCK_ورهائيندڙ ) );

#جيڪڏهن_پورو /* if configUSE_TICKLESS_IDLE == 1 */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    /* Offset to end up on 8 byte boundary. */
    px_چوٽي_جو_ڍير--;

    /* R0 is not included as it is the stack pointer. */
    *px_چوٽي_جو_ڍير = 0x00;
    px_چوٽي_جو_ڍير--;
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
        *px_چوٽي_جو_ڍير = 0x12345678; /* r15. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = 0xaaaabbbb;
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
        /* Leave space for the registers that will get popped from the stack
         * when the task first starts executing. */
        px_چوٽي_جو_ڍير -= 15;
    }
    #جيڪڏهن_پورو /* ifdef USE_FULL_REGISTER_INITIALISATION */

    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pvParameters; /* R1 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x12345678;                   /* Accumulator. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x87654321;                   /* Accumulator. */

    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    /* Use pxCurrentTCB just so it does not get optimised away. */
    إذا( pxCurrentTCB != عدم )
    {
        /* Call an application function to set up the timer that will generate
         * the tick interrupt.  This way the application can decide which
         * peripheral to use.  If tickless mode is used then the default
         * implementation defined in this file (which uses CMT0) should not be
         * overridden. */
        config_تياري_TICK_مداخلت();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = config_KERNEL_مداخلت_ترجيح;

        /* Start the first task. */
        prv_شروعات_پهريون_Task();
    }

    /* Execution should not reach here as the tasks are now running!
     * prvSetupTimerInterrupt() is called here to prevent the compiler outputting
     * a warning about a statically declared function not being referenced in the
     * case that the application writer has provided their own tick interrupt
     * configuration routine (and defined configSETUP_TICK_INTERRUPT() such that
     * their own routine will be called in place of prvSetupTimerInterrupt()). */
    prv_تياري_Timer_مداخلت();

    /* Should not get here. */
    أرجع pdFAIL;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pxCurrentTCB == عدم );
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_شروعات_پهريون_Task( فراغ )
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
        "MVTACLO    R15                     \n" \
        "POP        R15                     \n" \

        /* Accumulator high 32 bits. */
        "MVTACHI    R15                     \n" \

        /* R1 to R15 - R0 is not included as it is the SP. */
        "POPM       R1-R15                  \n" \

        /* This pops the remaining registers. */
        "RTE                                \n" \
        "NOP                                \n" \
        "NOP                                \n"
    );
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Software_مداخلت_ISR( فراغ )
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

        /* Save the accumulator. */
        "MVFACHI    R15                         \n" \
        "PUSH.L     R15                         \n" \

        /* Middle word. */
        "MVFACMI    R15                         \n" \

        /* Shifted left as it is restored to the low order word. */
        "SHLL       #16, R15                    \n" \
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
        "MVTACLO    R15                         \n" \
        "POP        R15                         \n" \
        "MVTACHI    R15                         \n" \
        "POPM       R1-R15                      \n" \
        "RTE                                    \n" \
        "NOP                                    \n" \
        "NOP                                      "
        ::"i" ( config_MAX_SYSCALL_مداخلت_ترجيح ), "i" ( config_KERNEL_مداخلت_ترجيح )
    );
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Tick_ISR( فراغ )
{
    /* Re-enabled interrupts. */
    __asm متطاير ( "SETPSW I" );

    /* Increment the tick, and perform any processing the new tick value
     * necessitates.  Ensure IPL is at the max syscall value first. */
    پورٽ_DISABLE_INTERRUPTS_FROM_KERNEL_ISR();
    {
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    پورٽ_ENABLE_INTERRUPTS_FROM_KERNEL_ISR();

    #إذا configUSE_TICKLESS_IDLE == 1
    {
        /* The CPU woke because of a tick. */
        ulTickFlag = pdTRUE;

        /* If this is the first tick since exiting tickless mode then the CMT
         * compare match value needs resetting. */
        CMT0.CMCOR = ( uint16_t ) ul_ميلاپ_قدر_For_One_Tick;
    }
    #جيڪڏهن_پورو
}
/*-----------------------------------------------------------*/

uint32_t ul_پورٽ_Get_IPL( فراغ )
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

فراغ v_پورٽ_سيٽ_IPL( uint32_t ulNewIPL )
{
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
/*-----------------------------------------------------------*/

ساكن فراغ prv_تياري_Timer_مداخلت( فراغ )
{
    /* Unlock. */
    SYSTEM.PRCR.لفظ_4 = پورٽ_UNLOCK_ڪنجي;

    /* Enable CMT0. */
    MSTP( CMT0 ) = 0;

    /* Lock again. */
    SYSTEM.PRCR.لفظ_4 = پورٽ_تالو_ڪنجي;

    /* Interrupt on compare match. */
    CMT0.CMCR.ٻٽو_انگ_3.CMIE = 1;

    /* Set the compare match value. */
    CMT0.CMCOR = ( uint16_t ) ul_ميلاپ_قدر_For_One_Tick;

    /* Divide the PCLK. */
    #إذا پورٽ_CLOCK_ورهائيندڙ == 512
    {
        CMT0.CMCR.ٻٽو_انگ_3.CKS = 3;
    }
    #وإلاإذا پورٽ_CLOCK_ورهائيندڙ == 128
    {
        CMT0.CMCR.ٻٽو_انگ_3.CKS = 2;
    }
    #وإلاإذا پورٽ_CLOCK_ورهائيندڙ == 32
    {
        CMT0.CMCR.ٻٽو_انگ_3.CKS = 1;
    }
    #وإلاإذا پورٽ_CLOCK_ورهائيندڙ == 8
    {
        CMT0.CMCR.ٻٽو_انگ_3.CKS = 0;
    }
    #وإلا /* if portCLOCK_DIVISOR == 512 */
    {
        #غلطي Invalid پورٽ_CLOCK_ورهائيندڙ setting
    }
    #جيڪڏهن_پورو /* if portCLOCK_DIVISOR == 512 */

    /* Enable the interrupt... */
    _IEN( _CMT0_CMI0 ) = 1;

    /* ...and set its priority to the application defined kernel priority. */
    _IPR( _CMT0_CMI0 ) = config_KERNEL_مداخلت_ترجيح;

    /* Start the timer. */
    CMT.CMSTR0.ٻٽو_انگ_3.STR0 = 1;
}
/*-----------------------------------------------------------*/

#إذا configUSE_TICKLESS_IDLE == 1

    ساكن فراغ prvSleep( TickType_t x_Expected_Idle_وقت )
    {
        /* Allow the application to define some pre-sleep processing. */
        configPRE_SLEEP_PROCESSING( x_Expected_Idle_وقت );

        /* xExpectedIdleTime being set to 0 by configPRE_SLEEP_PROCESSING()
         * means the application defined code has already executed the WAIT
         * instruction. */
        إذا( x_Expected_Idle_وقت > 0 )
        {
            __asm متطاير ( "WAIT" );
        }

        /* Allow the application to define some post sleep processing. */
        configPOST_SLEEP_PROCESSING( x_Expected_Idle_وقت );
    }

#جيڪڏهن_پورو /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

#إذا configUSE_TICKLESS_IDLE == 1

    فراغ v_پورٽ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وقت )
    {
        uint32_t ul_ميلاپ_قدر, ulCompleteTickPeriods, ul_Current_ڳڻپ;
        e_Sleep_گهڻائي_حالت eSleepAction;

        /* THIS FUNCTION IS CALLED WITH THE SCHEDULER SUSPENDED. */

        /* Make sure the CMT reload value does not overflow the counter. */
        إذا( x_Expected_Idle_وقت > x_وڌ_کان_وڌ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_وقت = x_وڌ_کان_وڌ_Possible_Suppressed_Ticks;
        }

        /* Calculate the reload value required to wait xExpectedIdleTime tick
         * periods. */
        ul_ميلاپ_قدر = ul_ميلاپ_قدر_For_One_Tick * x_Expected_Idle_وقت;

        إذا( ul_ميلاپ_قدر > ulStoppedTimerCompensation )
        {
            /* Compensate for the fact that the CMT is going to be stopped
             * momentarily. */
            ul_ميلاپ_قدر -= ulStoppedTimerCompensation;
        }

        /* Stop the CMT momentarily.  The time the CMT is stopped for is
         * accounted for as best it can be, but using the tickless mode will
         * inevitably result in some tiny drift of the time maintained by the
         * kernel with respect to calendar time. */
        CMT.CMSTR0.ٻٽو_انگ_3.STR0 = 0;

        طالما( CMT.CMSTR0.ٻٽو_انگ_3.STR0 == 1 )
        {
            /* Nothing to do here. */
        }

        /* Critical section using the global interrupt bit as the i bit is
         * automatically reset by the WAIT instruction. */
        __asm متطاير ( "CLRPSW i" );

        /* The tick flag is set to false before sleeping.  If it is true when
         * sleep mode is exited then sleep mode was probably exited because the
         * tick was suppressed for the entire xExpectedIdleTime period. */
        ulTickFlag = pdFALSE;

        /* If a context switch is pending then abandon the low power entry as
         * the context switch might have been pended by an external interrupt that
         * requires processing. */
        eSleepAction = e_Task_Confirm_Sleep_گهڻائي_حالت();

        إذا( eSleepAction == eAbortSleep )
        {
            /* Restart tick. */
            CMT.CMSTR0.ٻٽو_انگ_3.STR0 = 1;
            __asm متطاير ( "SETPSW i" );
        }
        وإلا إذا( eSleepAction == e_No_Tasks_انتظار_Timeout )
        {
            /* Protection off. */
            SYSTEM.PRCR.لفظ_4 = پورٽ_UNLOCK_ڪنجي;

            /* Ready for software standby with all clocks stopped. */
            SYSTEM.SBYCR.ٻٽو_انگ_3.SSBY = 1;

            /* Protection on. */
            SYSTEM.PRCR.لفظ_4 = پورٽ_تالو_ڪنجي;

            /* Sleep until something happens.  Calling prvSleep() will
             * automatically reset the i bit in the PSW. */
            prvSleep( x_Expected_Idle_وقت );

            /* Restart the CMT. */
            CMT.CMSTR0.ٻٽو_انگ_3.STR0 = 1;
        }
        وإلا
        {
            /* Protection off. */
            SYSTEM.PRCR.لفظ_4 = پورٽ_UNLOCK_ڪنجي;

            /* Ready for deep sleep mode. */
            SYSTEM.MSTPCRC.ٻٽو_انگ_3.DSLPE = 1;
            SYSTEM.MSTPCRA.ٻٽو_انگ_3.MSTPA28 = 1;
            SYSTEM.SBYCR.ٻٽو_انگ_3.SSBY = 0;

            /* Protection on. */
            SYSTEM.PRCR.لفظ_4 = پورٽ_تالو_ڪنجي;

            /* Adjust the match value to take into account that the current
             * time slice is already partially complete. */
            ul_ميلاپ_قدر -= ( uint32_t ) CMT0.CMCNT;
            CMT0.CMCOR = ( uint16_t ) ul_ميلاپ_قدر;

            /* Restart the CMT to count up to the new match value. */
            CMT0.CMCNT = 0;
            CMT.CMSTR0.ٻٽو_انگ_3.STR0 = 1;

            /* Sleep until something happens.  Calling prvSleep() will
             * automatically reset the i bit in the PSW. */
            prvSleep( x_Expected_Idle_وقت );

            /* Stop CMT.  Again, the time the SysTick is stopped for is
             * accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            CMT.CMSTR0.ٻٽو_انگ_3.STR0 = 0;

            طالما( CMT.CMSTR0.ٻٽو_انگ_3.STR0 == 1 )
            {
                /* Nothing to do here. */
            }

            ul_Current_ڳڻپ = ( uint32_t ) CMT0.CMCNT;

            إذا( ulTickFlag != pdFALSE )
            {
                /* The tick interrupt has already executed, although because
                 * this function is called with the scheduler suspended the actual
                 * tick processing will not occur until after this function has
                 * exited.  Reset the match value with whatever remains of this
                 * tick period. */
                ul_ميلاپ_قدر = ul_ميلاپ_قدر_For_One_Tick - ul_Current_ڳڻپ;
                CMT0.CMCOR = ( uint16_t ) ul_ميلاپ_قدر;

                /* The tick interrupt handler will already have pended the tick
                 * processing in the kernel.  As the pending tick will be
                 * processed as soon as this function exits, the tick value
                 * maintained by the tick is stepped forward by one less than the
                 * time spent sleeping.  The actual stepping of the tick appears
                 * later in this function. */
                ulCompleteTickPeriods = x_Expected_Idle_وقت - 1UL;
            }
            وإلا
            {
                /* Something other than the tick interrupt ended the sleep.
                 * How many complete tick periods passed while the processor was
                 * sleeping? */
                ulCompleteTickPeriods = ul_Current_ڳڻپ / ul_ميلاپ_قدر_For_One_Tick;

                /* The match value is set to whatever fraction of a single tick
                 * period remains. */
                ul_ميلاپ_قدر = ul_Current_ڳڻپ - ( ulCompleteTickPeriods * ul_ميلاپ_قدر_For_One_Tick );
                CMT0.CMCOR = ( uint16_t ) ul_ميلاپ_قدر;
            }

            /* Restart the CMT so it runs up to the match value.  The match value
             * will get set to the value required to generate exactly one tick period
             * the next time the CMT interrupt executes. */
            CMT0.CMCNT = 0;
            CMT.CMSTR0.ٻٽو_انگ_3.STR0 = 1;

            /* Wind the tick forward by the number of tick periods that the CPU
             * remained in a low power state. */
            v_Task_قدم_Tick( ulCompleteTickPeriods );
        }
    }

#جيڪڏهن_پورو /* configUSE_TICKLESS_IDLE */
