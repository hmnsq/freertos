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
#अन्तर्भाव "limits.h"

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/* Library includes. */
#अन्तर्भाव "string.h"

/* Hardware specifics. */
#यदि ( config_INCLUDE_PLATFORM_H_INSTEAD_सम्बन्धि_IODEFINE_H == 1 )

    #अन्तर्भाव "platform.h"

#अन्यथा /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

    #अन्तर्भाव "iodefine.h"

#यदि_अन्तः /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */
/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
 * PSW is set with U and I set, and PM and IPL clear. */
#परिभाषय पत्तनम्_INITIAL_PSW    ( ( राशिः_Type_t ) 0x00030000 )

/* The peripheral clock is divided by this value before being supplying the
 * CMT. */
#यदि ( configUSE_TICKLESS_IDLE == 0 )
    /* If tickless idle is not used then the divisor can be fixed. */
    #परिभाषय पत्तनम्_CLOCK_भाजकः    8UL
#नोचेद्यदि ( configPERIPHERAL_CLOCK_HZ >= 12000000 )
    #परिभाषय पत्तनम्_CLOCK_भाजकः    512UL
#नोचेद्यदि ( configPERIPHERAL_CLOCK_HZ >= 6000000 )
    #परिभाषय पत्तनम्_CLOCK_भाजकः    128UL
#नोचेद्यदि ( configPERIPHERAL_CLOCK_HZ >= 1000000 )
    #परिभाषय पत्तनम्_CLOCK_भाजकः    32UL
#अन्यथा
    #परिभाषय पत्तनम्_CLOCK_भाजकः    8UL
#यदि_अन्तः

/* These macros allow a critical section to be added around the call to
 * xTaskIncrementTick(), which is only ever called from interrupts at the kernel
 * priority - ie a known priority.  Therefore these local macros are a slight
 * optimisation compared to calling the global SET/CLEAR_INTERRUPT_MASK macros,
 * which would require the old IPL to be read first and stored in a local variable. */
#परिभाषय पत्तनम्_DISABLE_INTERRUPTS_FROM_KERNEL_ISR()    __asm चञ्चल ( "MVTIPL    %0" ::"i" ( config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता ) )
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS_FROM_KERNEL_ISR()     __asm चञ्चल ( "MVTIPL    %0" ::"i" ( config_KERNEL_व्यवधानम्_प्राथमिकता ) )

/* Keys required to lock and unlock access to certain system registers
 * respectively. */
#परिभाषय पत्तनम्_UNLOCK_कुञ्चिका    0xA50B
#परिभाषय पत्तनम्_तालकम्_कुञ्चिका      0xA500

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
स्थिर शून्य prvStartFirstTask( शून्य ) __attribute__( ( naked ) );

/*
 * Software interrupt handler.  Performs the actual context switch (saving and
 * restoring of registers).  Written in asm code as direct register access is
 * required.
 */
#यदि ( config_INCLUDE_PLATFORM_H_INSTEAD_सम्बन्धि_IODEFINE_H == 1 )

    R_BSP_PRAGMA_व्यवधानम्( v_पत्तनम्_Software_व्यवधानम्_ISR, VECT( ICU, SWINT ) )
    R_BSP_ATTRIB_व्यवधानम् शून्य v_पत्तनम्_Software_व्यवधानम्_ISR( शून्य ) __attribute__( ( naked ) );

#अन्यथा /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

    शून्य v_पत्तनम्_Software_व्यवधानम्_ISR( शून्य ) __attribute__( ( naked ) );

#यदि_अन्तः /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H  */

/*
 * The tick ISR handler.  The peripheral used is configured by the application
 * via a hook/callback function.
 */
#यदि ( config_INCLUDE_PLATFORM_H_INSTEAD_सम्बन्धि_IODEFINE_H == 1 )

    R_BSP_PRAGMA_व्यवधानम्( v_पत्तनम्_Tick_ISR, _VECT( config_TICK_सदिशम् ) )
    R_BSP_ATTRIB_व्यवधानम् शून्य v_पत्तनम्_Tick_ISR( शून्य ); /* Do not add __attribute__( ( interrupt ) ). */

#अन्यथा /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

    शून्य v_पत्तनम्_Tick_ISR( शून्य ) __attribute__( ( व्यवधानम् ) );

#यदि_अन्तः /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

/*
 * Sets up the periodic ISR used for the RTOS tick using the CMT.
 * The application writer can define configSETUP_TICK_INTERRUPT() (in
 * FreeRTOSConfig.h) such that their own tick interrupt configuration is used
 * in place of prvSetupTimerInterrupt().
 */
स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य );
#यदि_अपरिभाषितम् config_सज्जता_TICK_व्यवधानम्

/* The user has not provided their own tick interrupt configuration so use
 * the definition in this file (which uses the interval timer). */
    #परिभाषय config_सज्जता_TICK_व्यवधानम्()    prv_सज्जता_Timer_व्यवधानम्()
#यदि_अन्तः /* configSETUP_TICK_INTERRUPT */

/*
 * Called after the sleep mode registers have been configured, prvSleep()
 * executes the pre and post sleep macros, and actually calls the wait
 * instruction.
 */
#यदि configUSE_TICKLESS_IDLE == 1
    स्थिर शून्य prvSleep( TickType_t xExpectedIdleTime );
#यदि_अन्तः /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

/* Used in the context save and restore code. */
बाह्य शून्य * pxCurrentTCB;

/* Calculate how many clock increments make up a single tick period. */
स्थिर ध्रुव uint32_t ul_मेलनम्_मानम्_For_One_Tick = ( ( configPERIPHERAL_CLOCK_HZ / पत्तनम्_CLOCK_भाजकः ) / config_TICK_दरः_HZ );

#यदि configUSE_TICKLESS_IDLE == 1

/* Holds the maximum number of ticks that can be suppressed - which is
 * basically how far into the future an interrupt can be generated. Set
 * during initialisation.  This is the maximum possible value that the
 * compare match register can hold divided by ulMatchValueForOneTick. */
    स्थिर ध्रुव TickType_t x_अधिकतमम्_Possible_Suppressed_Ticks = USHRT_MAX / ( ( configPERIPHERAL_CLOCK_HZ / पत्तनम्_CLOCK_भाजकः ) / config_TICK_दरः_HZ );

/* Flag set from the tick interrupt to allow the sleep processing to know if
 * sleep mode was exited because of a tick interrupt, or an interrupt
 * generated by something else. */
    स्थिर चञ्चल uint32_t ulTickFlag = pdFALSE;

/* The CMT counter is stopped temporarily each time it is re-programmed.
 * The following constant offsets the CMT counter match value by the number of
 * CMT counts that would typically be missed while the counter was stopped to
 * compensate for the lost time.  The large difference between the divided CMT
 * clock and the CPU clock means it is likely ulStoppedTimerCompensation will
 * equal zero - and be optimised away. */
    स्थिर ध्रुव uint32_t ulStoppedTimerCompensation = 100UL / ( configCPU_CLOCK_HZ / ( configPERIPHERAL_CLOCK_HZ / पत्तनम्_CLOCK_भाजकः ) );

#यदि_अन्तः /* if configUSE_TICKLESS_IDLE == 1 */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters )
{
    /* Offset to end up on 8 byte boundary. */
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* R0 is not included as it is the stack pointer. */
    *px_शिखरम्_सम्बन्धि_राशिः = 0x00;
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = 0x00;
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_PSW;
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) px_संहिता;

    /* When debugging it can be useful if every register is set to a known
     * value.  Otherwise code space can be saved by just setting the registers
     * that need to be set. */
    #यदि_परिभाषितम् USE_पूर्णम्_पञ्जिकाकोशः_INITIALISATION
    {
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x12345678; /* r15. */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0xaaaabbbb;
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0xdddddddd;
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0xcccccccc;
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0xbbbbbbbb;
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0xaaaaaaaa;
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x99999999;
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x88888888;
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x77777777;
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x66666666;
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x55555555;
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x44444444;
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x33333333;
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x22222222;
        px_शिखरम्_सम्बन्धि_राशिः--;
    }
    #अन्यथा /* ifdef USE_FULL_REGISTER_INITIALISATION */
    {
        /* Leave space for the registers that will get popped from the stack
         * when the task first starts executing. */
        px_शिखरम्_सम्बन्धि_राशिः -= 15;
    }
    #यदि_अन्तः /* ifdef USE_FULL_REGISTER_INITIALISATION */

    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) pvParameters; /* R1 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = 0x12345678;                   /* Accumulator. */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = 0x87654321;                   /* Accumulator. */

    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    /* Use pxCurrentTCB just so it does not get optimised away. */
    यदि( pxCurrentTCB != रिक्त )
    {
        /* Call an application function to set up the timer that will generate
         * the tick interrupt.  This way the application can decide which
         * peripheral to use.  If tickless mode is used then the default
         * implementation defined in this file (which uses CMT0) should not be
         * overridden. */
        config_सज्जता_TICK_व्यवधानम्();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = config_KERNEL_व्यवधानम्_प्राथमिकता;

        /* Start the first task. */
        prvStartFirstTask();
    }

    /* Execution should not reach here as the tasks are now running!
     * prvSetupTimerInterrupt() is called here to prevent the compiler outputting
     * a warning about a statically declared function not being referenced in the
     * case that the application writer has provided their own tick interrupt
     * configuration routine (and defined configSETUP_TICK_INTERRUPT() such that
     * their own routine will be called in place of prvSetupTimerInterrupt()). */
    prv_सज्जता_Timer_व्यवधानम्();

    /* Should not get here. */
    प्रत्यागम pdFAIL;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pxCurrentTCB == रिक्त );
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvStartFirstTask( शून्य )
{
    __asm चञ्चल
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

शून्य v_पत्तनम्_Software_व्यवधानम्_ISR( शून्य )
{
    __asm चञ्चल
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
        ::"i" ( config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता ), "i" ( config_KERNEL_व्यवधानम्_प्राथमिकता )
    );
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Tick_ISR( शून्य )
{
    /* Re-enabled interrupts. */
    __asm चञ्चल ( "SETPSW I" );

    /* Increment the tick, and perform any processing the new tick value
     * necessitates.  Ensure IPL is at the max syscall value first. */
    पत्तनम्_DISABLE_INTERRUPTS_FROM_KERNEL_ISR();
    {
        यदि( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    पत्तनम्_ENABLE_INTERRUPTS_FROM_KERNEL_ISR();

    #यदि configUSE_TICKLESS_IDLE == 1
    {
        /* The CPU woke because of a tick. */
        ulTickFlag = pdTRUE;

        /* If this is the first tick since exiting tickless mode then the CMT
         * compare match value needs resetting. */
        CMT0.CMCOR = ( uint16_t ) ul_मेलनम्_मानम्_For_One_Tick;
    }
    #यदि_अन्तः
}
/*-----------------------------------------------------------*/

uint32_t ul_पत्तनम्_Get_IPL( शून्य )
{
    __asm चञ्चल
    (
        "MVFC   PSW, R1         \n" \
        "SHLR   #24, R1         \n" \
        "RTS                      "
    );

    /* This will never get executed, but keeps the compiler from complaining. */
    प्रत्यागम 0;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_समुच्चयः_IPL( uint32_t ulNewIPL )
{
    __asm चञ्चल
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

स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य )
{
    /* Unlock. */
    SYSTEM.PRCR.WORD = पत्तनम्_UNLOCK_कुञ्चिका;

    /* Enable CMT0. */
    MSTP( CMT0 ) = 0;

    /* Lock again. */
    SYSTEM.PRCR.WORD = पत्तनम्_तालकम्_कुञ्चिका;

    /* Interrupt on compare match. */
    CMT0.CMCR.BIT.CMIE = 1;

    /* Set the compare match value. */
    CMT0.CMCOR = ( uint16_t ) ul_मेलनम्_मानम्_For_One_Tick;

    /* Divide the PCLK. */
    #यदि पत्तनम्_CLOCK_भाजकः == 512
    {
        CMT0.CMCR.BIT.CKS = 3;
    }
    #नोचेद्यदि पत्तनम्_CLOCK_भाजकः == 128
    {
        CMT0.CMCR.BIT.CKS = 2;
    }
    #नोचेद्यदि पत्तनम्_CLOCK_भाजकः == 32
    {
        CMT0.CMCR.BIT.CKS = 1;
    }
    #नोचेद्यदि पत्तनम्_CLOCK_भाजकः == 8
    {
        CMT0.CMCR.BIT.CKS = 0;
    }
    #अन्यथा /* if portCLOCK_DIVISOR == 512 */
    {
        #दोषः Invalid पत्तनम्_CLOCK_भाजकः setting
    }
    #यदि_अन्तः /* if portCLOCK_DIVISOR == 512 */

    /* Enable the interrupt... */
    _IEN( _CMT0_CMI0 ) = 1;

    /* ...and set its priority to the application defined kernel priority. */
    _IPR( _CMT0_CMI0 ) = config_KERNEL_व्यवधानम्_प्राथमिकता;

    /* Start the timer. */
    CMT.CMSTR0.BIT.STR0 = 1;
}
/*-----------------------------------------------------------*/

#यदि configUSE_TICKLESS_IDLE == 1

    स्थिर शून्य prvSleep( TickType_t xExpectedIdleTime )
    {
        /* Allow the application to define some pre-sleep processing. */
        configPRE_SLEEP_PROCESSING( xExpectedIdleTime );

        /* xExpectedIdleTime being set to 0 by configPRE_SLEEP_PROCESSING()
         * means the application defined code has already executed the WAIT
         * instruction. */
        यदि( xExpectedIdleTime > 0 )
        {
            __asm चञ्चल ( "WAIT" );
        }

        /* Allow the application to define some post sleep processing. */
        configPOST_SLEEP_PROCESSING( xExpectedIdleTime );
    }

#यदि_अन्तः /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

#यदि configUSE_TICKLESS_IDLE == 1

    शून्य v_पत्तनम्_Suppress_Ticks_And_Sleep( TickType_t xExpectedIdleTime )
    {
        uint32_t ul_मेलनम्_मानम्, ulCompleteTickPeriods, ul_Current_गणनम्;
        e_Sleep_बहुलकम्_स्थितिः eSleepAction;

        /* THIS FUNCTION IS CALLED WITH THE SCHEDULER SUSPENDED. */

        /* Make sure the CMT reload value does not overflow the counter. */
        यदि( xExpectedIdleTime > x_अधिकतमम्_Possible_Suppressed_Ticks )
        {
            xExpectedIdleTime = x_अधिकतमम्_Possible_Suppressed_Ticks;
        }

        /* Calculate the reload value required to wait xExpectedIdleTime tick
         * periods. */
        ul_मेलनम्_मानम् = ul_मेलनम्_मानम्_For_One_Tick * xExpectedIdleTime;

        यदि( ul_मेलनम्_मानम् > ulStoppedTimerCompensation )
        {
            /* Compensate for the fact that the CMT is going to be stopped
             * momentarily. */
            ul_मेलनम्_मानम् -= ulStoppedTimerCompensation;
        }

        /* Stop the CMT momentarily.  The time the CMT is stopped for is
         * accounted for as best it can be, but using the tickless mode will
         * inevitably result in some tiny drift of the time maintained by the
         * kernel with respect to calendar time. */
        CMT.CMSTR0.BIT.STR0 = 0;

        यावत्( CMT.CMSTR0.BIT.STR0 == 1 )
        {
            /* Nothing to do here. */
        }

        /* Critical section using the global interrupt bit as the i bit is
         * automatically reset by the WAIT instruction. */
        __asm चञ्चल ( "CLRPSW i" );

        /* The tick flag is set to false before sleeping.  If it is true when
         * sleep mode is exited then sleep mode was probably exited because the
         * tick was suppressed for the entire xExpectedIdleTime period. */
        ulTickFlag = pdFALSE;

        /* If a context switch is pending then abandon the low power entry as
         * the context switch might have been pended by an external interrupt that
         * requires processing. */
        eSleepAction = e_Task_Confirm_Sleep_बहुलकम्_स्थितिः();

        यदि( eSleepAction == eAbortSleep )
        {
            /* Restart tick. */
            CMT.CMSTR0.BIT.STR0 = 1;
            __asm चञ्चल ( "SETPSW i" );
        }
        अन्यथा यदि( eSleepAction == e_No_Tasks_प्रतीक्षा_Timeout )
        {
            /* Protection off. */
            SYSTEM.PRCR.WORD = पत्तनम्_UNLOCK_कुञ्चिका;

            /* Ready for software standby with all clocks stopped. */
            SYSTEM.SBYCR.BIT.SSBY = 1;

            /* Protection on. */
            SYSTEM.PRCR.WORD = पत्तनम्_तालकम्_कुञ्चिका;

            /* Sleep until something happens.  Calling prvSleep() will
             * automatically reset the i bit in the PSW. */
            prvSleep( xExpectedIdleTime );

            /* Restart the CMT. */
            CMT.CMSTR0.BIT.STR0 = 1;
        }
        अन्यथा
        {
            /* Protection off. */
            SYSTEM.PRCR.WORD = पत्तनम्_UNLOCK_कुञ्चिका;

            /* Ready for deep sleep mode. */
            SYSTEM.MSTPCRC.BIT.DSLPE = 1;
            SYSTEM.MSTPCRA.BIT.MSTPA28 = 1;
            SYSTEM.SBYCR.BIT.SSBY = 0;

            /* Protection on. */
            SYSTEM.PRCR.WORD = पत्तनम्_तालकम्_कुञ्चिका;

            /* Adjust the match value to take into account that the current
             * time slice is already partially complete. */
            ul_मेलनम्_मानम् -= ( uint32_t ) CMT0.CMCNT;
            CMT0.CMCOR = ( uint16_t ) ul_मेलनम्_मानम्;

            /* Restart the CMT to count up to the new match value. */
            CMT0.CMCNT = 0;
            CMT.CMSTR0.BIT.STR0 = 1;

            /* Sleep until something happens.  Calling prvSleep() will
             * automatically reset the i bit in the PSW. */
            prvSleep( xExpectedIdleTime );

            /* Stop CMT.  Again, the time the SysTick is stopped for is
             * accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            CMT.CMSTR0.BIT.STR0 = 0;

            यावत्( CMT.CMSTR0.BIT.STR0 == 1 )
            {
                /* Nothing to do here. */
            }

            ul_Current_गणनम् = ( uint32_t ) CMT0.CMCNT;

            यदि( ulTickFlag != pdFALSE )
            {
                /* The tick interrupt has already executed, although because
                 * this function is called with the scheduler suspended the actual
                 * tick processing will not occur until after this function has
                 * exited.  Reset the match value with whatever remains of this
                 * tick period. */
                ul_मेलनम्_मानम् = ul_मेलनम्_मानम्_For_One_Tick - ul_Current_गणनम्;
                CMT0.CMCOR = ( uint16_t ) ul_मेलनम्_मानम्;

                /* The tick interrupt handler will already have pended the tick
                 * processing in the kernel.  As the pending tick will be
                 * processed as soon as this function exits, the tick value
                 * maintained by the tick is stepped forward by one less than the
                 * time spent sleeping.  The actual stepping of the tick appears
                 * later in this function. */
                ulCompleteTickPeriods = xExpectedIdleTime - 1UL;
            }
            अन्यथा
            {
                /* Something other than the tick interrupt ended the sleep.
                 * How many complete tick periods passed while the processor was
                 * sleeping? */
                ulCompleteTickPeriods = ul_Current_गणनम् / ul_मेलनम्_मानम्_For_One_Tick;

                /* The match value is set to whatever fraction of a single tick
                 * period remains. */
                ul_मेलनम्_मानम् = ul_Current_गणनम् - ( ulCompleteTickPeriods * ul_मेलनम्_मानम्_For_One_Tick );
                CMT0.CMCOR = ( uint16_t ) ul_मेलनम्_मानम्;
            }

            /* Restart the CMT so it runs up to the match value.  The match value
             * will get set to the value required to generate exactly one tick period
             * the next time the CMT interrupt executes. */
            CMT0.CMCNT = 0;
            CMT.CMSTR0.BIT.STR0 = 1;

            /* Wind the tick forward by the number of tick periods that the CPU
             * remained in a low power state. */
            v_Task_चरणः_Tick( ulCompleteTickPeriods );
        }
    }

#यदि_अन्तः /* configUSE_TICKLESS_IDLE */
