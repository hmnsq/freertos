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
* Implementation of functions defined in portable.h for the ARM CM4F port.
*----------------------------------------------------------*/

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* Constants required to manipulate the core.  Registers first... */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG             ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000e010 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG             ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000e014 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG    ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000e018 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SHPR3_REG                    ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed20 ) )
/* ...then bits in the registers. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್              ( 1UL << 2UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್              ( 1UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್           ( 1UL << 0UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_ಎಣಿಕೆ_FLAG_ಬಿಟ್       ( 1UL << 16UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_PENDSVCLEAR_ಬಿಟ್              ( 1UL << 27UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_PEND_SYSTICK_ಗಣ_ಬಿಟ್         ( 1UL << 26UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_PEND_SYSTICK_CLEAR_ಬಿಟ್       ( 1UL << 25UL )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MIN_ಅಡಚಣೆ_ಆದ್ಯತೆ            ( 255UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_PENDSV_PRI                   ( ( ( uint32_t ) ಪೋರ್ಟ್_MIN_ಅಡಚಣೆ_ಆದ್ಯತೆ ) << 16UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_PRI                  ( ( ( uint32_t ) ಪೋರ್ಟ್_MIN_ಅಡಚಣೆ_ಆದ್ಯತೆ ) << 24UL )

/* Constants required to check the validity of an interrupt priority. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಮೊದಲ_USER_ಅಡಚಣೆ_ಸಂಖ್ಯೆ       ( 16 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_IP_REGISTERS_ಸ್ಥಾನಾಂತರ_16       ( 0xE000E3F0 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_AIRCR_REG                         ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xE000ED0C ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_8_ಬಿಟ್_ಮೌಲ್ಯ                   ( ( uint8_t ) 0xff )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ತುದಿ_ಬಿಟ್_ದ_BYTE                   ( ( uint8_t ) 0x80 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_PRIGROUP_ಬಿಟ್ಟುಗಳು                 ( ( uint8_t ) 7 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಗುಂಪು_ಮುಖವಾಡ               ( 0x07UL << 8UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIGROUP_ಸರಿಸು                    ( 8UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_VECTACTIVE_ಮುಖವಾಡ                   ( 0xFFUL )

/* Constants required to manipulate the VFP. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FPCCR                             ( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ef34 ) /* Floating point context control register. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ASPEN_AND_LSPEN_ಬಿಟ್ಟುಗಳು              ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_XPSR                      ( 0x01000000 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_EXC_RETURN                ( 0xfffffffd )

/* The systick is a 24-bit counter. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_24_ಬಿಟ್_ಸಂಖ್ಯೆ                 ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MISSED_COUNTS_ಗುಣಕ              ( 94UL )

/* Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configSYSTICK_CLOCK_HZ
    #ವ್ಯಾಖ್ಯಾನಿಸು configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG    ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ )
#ಇಲ್ಲದಿದ್ದರೆ
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG    ( 0 )
#ಆದರೆ_ಅಂತ್ಯ

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ config_TASK_RETURN_ವಿಳಾಸ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ    config_TASK_RETURN_ವಿಳಾಸ
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ    prvTaskExitError
#ಆದರೆ_ಅಂತ್ಯ

/* Cannot find a weak linkage attribute, so the
 * configOVERRIDE_DEFAULT_TICK_CONFIGURATION constant must be set to 1 if the
 * application writer wants to provide their own implementation of
 * vPortSetupTimerInterrupt().  Ensure configOVERRIDE_DEFAULT_TICK_CONFIGURATION
 * is defined. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configOVERRIDE_DEFAULT_TICK_CONFIGURATION
    #ವ್ಯಾಖ್ಯಾನಿಸು configOVERRIDE_DEFAULT_TICK_CONFIGURATION    0
#ಆದರೆ_ಅಂತ್ಯ

/* Manual definition of missing asm names. */
#ವ್ಯಾಖ್ಯಾನಿಸು psp        9
#ವ್ಯಾಖ್ಯಾನಿಸು basepri    17
#ವ್ಯಾಖ್ಯಾನಿಸು msp        8
#ವ್ಯಾಖ್ಯಾನಿಸು ipsr       5
#ವ್ಯಾಖ್ಯಾನಿಸು control    20

/* From port.c. */
ಬಾಹ್ಯ ಶೂನ್ಯ * pxCurrentTCB;

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
ಸ್ಥಿರ UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );

/*
 * Exception handlers.
 */
ಶೂನ್ಯ x_ಪೋರ್ಟ್_Pend_SVHandler( ಶೂನ್ಯ );
ಶೂನ್ಯ x_ಪೋರ್ಟ್_Sys_Tick_Handler( ಶೂನ್ಯ );
ಶೂನ್ಯ v_ಪೋರ್ಟ್_SVCHandler( ಶೂನ್ಯ );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ );

/*
 * Function to enable the VFP.
 */
ಸ್ಥಿರ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enable_VFP( ಶೂನ್ಯ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ );

/*-----------------------------------------------------------*/

/*
 * The number of SysTick increments that make up one tick period.
 */
#ಆದರೆ ( configUSE_TICKLESS_IDLE == 1 )
    ಸ್ಥಿರ uint32_t ulTimerCountsForOneTick = 0;
#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */

/*
 * The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer.
 */
#ಆದರೆ ( configUSE_TICKLESS_IDLE == 1 )
    ಸ್ಥಿರ uint32_t x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks = 0;
#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */

/*
 * Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only.
 */
#ಆದರೆ ( configUSE_TICKLESS_IDLE == 1 )
    ಸ್ಥಿರ uint32_t ulStoppedTimerCompensation = 0;
#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#ಆದರೆ ( configASSERT_DEFINED == 1 )
    ಸ್ಥಿರ uint8_t uc_Max_Sys_Call_ಆದ್ಯತೆ = 0;
    ಸ್ಥಿರ uint32_t ulMaxPRIGROUPValue = 0;
#ಆದರೆ_ಅಂತ್ಯ /* configASSERT_DEFINED */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */

    /* Offset added to account for the way the MCU uses the stack on entry/exit
     * of interrupts, and to ensure alignment. */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* Sometimes the parameters are loaded from the stack. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_XPSR;                        /* xPSR */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ;                  /* PC */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ; /* LR */

    /* Save code space by skipping register initialisation. */
    px_ತುದಿ_ದ_ರಾಶಿ -= 5;                            /* R12, R3, R2 and R1. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters; /* R0 */

    /* A save method is being used that requires each task to maintain its
     * own exec return value. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_EXC_RETURN;

    px_ತುದಿ_ದ_ರಾಶಿ -= 8; /* R11, R10, R9, R8, R7, R6, R5 and R4. */

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( uxCriticalNesting == ~0UL );
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();

    ಗಾಗಿ( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_SVCHandler( ಶೂನ್ಯ ) iv IVT_INT_SVCall ics ICS_OFF
{
    __asm {
/* *INDENT-OFF* */
        ldr r3, =_pxCurrentTCB     /* Restore the context. */
        ldr r1, [ r3 ]    /* Use pxCurrentTCBConst to get the pxCurrentTCB address. */
        ldr r0, [ r1 ]              /* The first item in pxCurrentTCB is the task top of stack. */
        ldm r0 !, ( r4 - r11, r14 ) /* Pop the registers that are not automatically saved on exception entry and the critical nesting count. */
        msr psp, r0                 /* Restore the task stack pointer. */
        isb
        mov r0, #0
        msr basepri, r0
        bx r14
/* *INDENT-ON* */
    };
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ )
{
    __asm {
/* *INDENT-OFF* */
        ldr r0, =0xE000ED08 /* Use the NVIC offset register to locate the stack. */
        ldr r0, [ r0 ]
        ldr r0, [ r0 ]
        msr msp, r0 /* Set the msp back to the start of the stack. */

        /* Clear the bit that indicates the FPU is in use in case the FPU was used
         * before the scheduler was started - which would otherwise result in the
         * unnecessary leaving of space in the SVC stack for lazy saving of FPU
         * registers. */
        mov r0, #0
        msr control, r0
        cpsie i /* Globally enable interrupts. */
        cpsie f
        dsb
        isb
        svc #0 /* System call to start first task. */
        nop
/* *INDENT-ON* */
    };
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    #ಆದರೆ ( configASSERT_DEFINED == 1 )
    {
        ಅಸ್ಥಿರ uint8_t uc_Original_ಆದ್ಯತೆ;
        ಅಸ್ಥಿರ uint32_t ul_Implemented_Prio_ಬಿಟ್ಟುಗಳು = 0;
        ಅಸ್ಥಿರ uint8_t * ಸ್ಥಿರಾಂಕ puc_ಮೊದಲ_User_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್ = ( ಅಸ್ಥಿರ uint8_t * ಸ್ಥಿರಾಂಕ ) ( ಪೋರ್ಟ್_NVIC_IP_REGISTERS_ಸ್ಥಾನಾಂತರ_16 + ಪೋರ್ಟ್_ಮೊದಲ_USER_ಅಡಚಣೆ_ಸಂಖ್ಯೆ );
        ಅಸ್ಥಿರ uint8_t uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
         * functions can be called.  ISR safe functions are those that end in
         * "FromISR".  FreeRTOS maintains separate thread and ISR API functions to
         * ensure interrupt entry is as fast and simple as possible.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_ಆದ್ಯತೆ = *puc_ಮೊದಲ_User_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್;

        /* Determine the number of priority bits available.  First write to all
         * possible bits. */
        *puc_ಮೊದಲ_User_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್ = ಪೋರ್ಟ್_MAX_8_ಬಿಟ್_ಮೌಲ್ಯ;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ = *puc_ಮೊದಲ_User_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್;

        /* Use the same mask on the maximum system call priority. */
        uc_Max_Sys_Call_ಆದ್ಯತೆ = config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ & uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ;

        /* Check that the maximum system call priority is nonzero after
         * accounting for the number of priority bits supported by the
         * hardware. A priority of 0 is invalid because setting the BASEPRI
         * register to 0 unmasks all interrupts, and interrupts with priority 0
         * cannot be masked using BASEPRI.
         * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( uc_Max_Sys_Call_ಆದ್ಯತೆ );

        /* Check that the bits not implemented in hardware are zero in
         * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ & ( ~uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
         * of bits read back. */

        ಆಗ( ( uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ & ಪೋರ್ಟ್_ತುದಿ_ಬಿಟ್_ದ_BYTE ) == ಪೋರ್ಟ್_ತುದಿ_ಬಿಟ್_ದ_BYTE )
        {
            ul_Implemented_Prio_ಬಿಟ್ಟುಗಳು++;
            uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ <<= ( uint8_t ) 0x01;
        }

        ಆದರೆ( ul_Implemented_Prio_ಬಿಟ್ಟುಗಳು == 8 )
        {
            /* When the hardware implements 8 priority bits, there is no way for
            * the software to configure PRIGROUP to not have sub-priorities. As
            * a result, the least significant bit is always used for sub-priority
            * and there are 128 preemption priorities and 2 sub-priorities.
            *
            * This may cause some confusion in some cases - for example, if
            * configMAX_SYSCALL_INTERRUPT_PRIORITY is set to 5, both 5 and 4
            * priority interrupts will be masked in Critical Sections as those
            * are at the same preemption priority. This may appear confusing as
            * 4 is higher (numerically lower) priority than
            * configMAX_SYSCALL_INTERRUPT_PRIORITY and therefore, should not
            * have been masked. Instead, if we set configMAX_SYSCALL_INTERRUPT_PRIORITY
            * to 4, this confusion does not happen and the behaviour remains the same.
            *
            * The following assert ensures that the sub-priority bit in the
            * configMAX_SYSCALL_INTERRUPT_PRIORITY is clear to avoid the above mentioned
            * confusion. */
            configASSERT( ( config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            ulMaxPRIGROUPValue = ಪೋರ್ಟ್_MAX_PRIGROUP_ಬಿಟ್ಟುಗಳು - ul_Implemented_Prio_ಬಿಟ್ಟುಗಳು;
        }

        /* Shift the priority group value back to its position within the AIRCR
         * register. */
        ulMaxPRIGROUPValue <<= ಪೋರ್ಟ್_PRIGROUP_ಸರಿಸು;
        ulMaxPRIGROUPValue &= ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಗುಂಪು_ಮುಖವಾಡ;

        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_ಮೊದಲ_User_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್ = uc_Original_ಆದ್ಯತೆ;
    }
    #ಆದರೆ_ಅಂತ್ಯ /* configASSERT_DEFINED */

    /* Make PendSV and SysTick the lowest priority interrupts. */
    ಪೋರ್ಟ್_NVIC_SHPR3_REG |= ಪೋರ್ಟ್_NVIC_PENDSV_PRI;
    ಪೋರ್ಟ್_NVIC_SHPR3_REG |= ಪೋರ್ಟ್_NVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    /* Ensure the VFP is enabled - it should be anyway. */
    v_ಪೋರ್ಟ್_Enable_VFP();

    /* Lazy save always. */
    *( ಪೋರ್ಟ್_FPCCR ) |= ಪೋರ್ಟ್_ASPEN_AND_LSPEN_ಬಿಟ್ಟುಗಳು;

    /* Start the first task. */
    prv_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task();

    /* Should never get here as the tasks will now be executing!  Call the task
     * exit error function to prevent compiler warnings about a static function
     * not being called in the case that the application writer overrides this
     * functionality by defining configTASK_RETURN_ADDRESS. */
    prvTaskExitError();

    /* Should not get here! */
    ಹಿಂತಿರುಗಿ 0;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ )
{
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();
    uxCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    ಆದರೆ( uxCriticalNesting == 1 )
    {
        configASSERT( ( ಪೋರ್ಟ್_NVIC_INT_CTRL_REG & ಪೋರ್ಟ್_VECTACTIVE_ಮುಖವಾಡ ) == 0 );
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;

    ಆದರೆ( uxCriticalNesting == 0 )
    {
        ಪೋರ್ಟ್_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರಾಂಕ uint8_t uc_Max_Syscall_ಅಡಚಣೆ_ಆದ್ಯತೆ = config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ;
ಶೂನ್ಯ x_ಪೋರ್ಟ್_Pend_SVHandler( ಶೂನ್ಯ ) iv IVT_INT_PendSV ics ICS_OFF
{
    __asm {
        #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HW_DEBUG
/* *INDENT-OFF* */

            /* The function is not truly naked, so add back the 4 bytes subtracted
            * from the stack pointer by the function prologue. */
            ಕೂಡಿಸು sp, sp, # 4
        #ಆದರೆ_ಅಂತ್ಯ
        mrs r0, psp
        isb

        ldr r3, =_pxCurrentTCB /* Get the location of the current TCB. */
        ldr r2, [ r3 ]

        tst r14, #0x10 /* Is the task using the FPU context?  If so, push high vfp registers. */
        it eq
        vstmdbeq r0 !, ( s16 - s31 )

        stmdb r0 !, ( r4 - r11, r14 ) /* Save the core registers. */

        str r0, [ r2 ]                /* Save the new top of stack into the first member of the TCB. */

        stmdb sp !, ( r0, r3 )
        ldr r0, = uc_Max_Syscall_ಅಡಚಣೆ_ಆದ್ಯತೆ_2
        ldr r1, [ r0 ]
        msr basepri, r1
        dsb
        isb
        bl _vTaskSwitchContext
        mov r0, #0
        msr basepri, r0
        ldm sp !, ( r0, r3 )

        ldr r1, [ r3 ] /* The first item in pxCurrentTCB is the task top of stack. */
        ldr r0, [ r1 ]

        ldm r0 !, ( r4 - r11, r14 ) /* Pop the core registers. */

        tst r14, #0x10             /* Is the task using the FPU context?  If so, pop the high vfp registers too. */
        it eq
        vldmiaeq r0 !, ( s16 - s31 )

        msr psp, r0
        isb
        bx r14
/* *INDENT-ON* */
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ x_ಪೋರ್ಟ್_Sys_Tick_Handler( ಶೂನ್ಯ ) iv IVT_INT_SysTick ics ICS_AUTO
{
    /* The SysTick runs at the lowest interrupt priority, so when this interrupt
     * executes all interrupts must be unmasked.  There is therefore no need to
     * save and then restore the interrupt mask value as its value is already
     * known - therefore the slightly faster portDISABLE_INTERRUPTS() function is
     * used in place of portSET_INTERRUPT_MASK_FROM_ISR(). */
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        ಆದರೆ( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_ಗಮ್ಯ_SCHEDULER();

            /* A context switch is required.  Context switching is performed in
             * the PendSV interrupt.  Pend the PendSV interrupt. */
            ಪೋರ್ಟ್_NVIC_INT_CTRL_REG = ಪೋರ್ಟ್_NVIC_PENDSVSET_ಬಿಟ್;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            traceISR_EXIT();
        }
    }
    ಪೋರ್ಟ್_ENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( configUSE_TICKLESS_IDLE == 1 ) && ( configOVERRIDE_DEFAULT_TICK_CONFIGURATION == 0 ) )

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ಸಮಯ )
    {
        uint32_t ul_Reload_ಮೌಲ್ಯ, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_ಎಡ;
        TickType_t x_Modifiable_Idle_ಸಮಯ;

        /* Make sure the SysTick reload value does not overflow the counter. */
        ಆದರೆ( x_Expected_Idle_ಸಮಯ > x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_ಸಮಯ = x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm {
            "cpsid i"
        };
        __asm {
            "dsb"
        };
        __asm {
            "isb"
        };

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        ಆದರೆ( e_Task_Confirm_Sleep_ಬಹುಲಕ_ಸ್ಥಿತಿ() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the cpsid instruction
             * above. */
            __asm {
                "cpsie i"
            };
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            /* Stop the SysTick momentarily.  The time the SysTick is stopped for
             * is accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_ಎಡ = ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG;

            ಆದರೆ( ul_Sys_Tick_Decrements_ಎಡ == 0 )
            {
                ul_Sys_Tick_Decrements_ಎಡ = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_ಮೌಲ್ಯ = ul_Sys_Tick_Decrements_ಎಡ + ( ulTimerCountsForOneTick * ( x_Expected_Idle_ಸಮಯ - 1UL ) );

            ಆದರೆ( ( ಪೋರ್ಟ್_NVIC_INT_CTRL_REG & ಪೋರ್ಟ್_NVIC_PEND_SYSTICK_ಗಣ_ಬಿಟ್ ) != 0 )
            {
                ಪೋರ್ಟ್_NVIC_INT_CTRL_REG = ಪೋರ್ಟ್_NVIC_PEND_SYSTICK_CLEAR_ಬಿಟ್;
                ul_Reload_ಮೌಲ್ಯ -= ulTimerCountsForOneTick;
            }

            ಆದರೆ( ul_Reload_ಮೌಲ್ಯ > ulStoppedTimerCompensation )
            {
                ul_Reload_ಮೌಲ್ಯ -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ul_Reload_ಮೌಲ್ಯ;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG = 0UL;

            /* Restart SysTick. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG |= ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            x_Modifiable_Idle_ಸಮಯ = x_Expected_Idle_ಸಮಯ;
            configPRE_SLEEP_PROCESSING( x_Modifiable_Idle_ಸಮಯ );

            ಆದರೆ( x_Modifiable_Idle_ಸಮಯ > 0 )
            {
                __asm {
                    "dsb"
                };
                __asm {
                    "wfi"
                };
                __asm {
                    "isb"
                };
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_ಸಮಯ );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the cpsid instruction above. */
            __asm {
                "cpsie i"
            };
            __asm {
                "dsb"
            };
            __asm {
                "isb"
            };

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm {
                "cpsid i"
            };
            __asm {
                "dsb"
            };
            __asm {
                "isb"
            };

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ );

            /* Determine whether the SysTick has already counted to zero. */
            ಆದರೆ( ( ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG & ಪೋರ್ಟ್_NVIC_SYSTICK_ಎಣಿಕೆ_FLAG_ಬಿಟ್ ) != 0 )
            {
                uint32_t ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_ಮೌಲ್ಯ - ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                ಆದರೆ( ( ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ <= ulStoppedTimerCompensation ) || ( ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ = ( ulTimerCountsForOneTick - 1UL );
                }

                ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = x_Expected_Idle_ಸಮಯ - 1UL;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_ಎಡ = ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG;
                #ಆದರೆ ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG != ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    ಆದರೆ( ul_Sys_Tick_Decrements_ಎಡ == 0 )
                    {
                        ul_Sys_Tick_Decrements_ಎಡ = ul_Reload_ಮೌಲ್ಯ;
                    }
                }
                #ಆದರೆ_ಅಂತ್ಯ /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_ಸಮಯ * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_ಎಡ;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG = 0UL;
            ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್;
            #ಆದರೆ ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG == ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ )
            {
                ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ulTimerCountsForOneTick - 1UL;
            }
            #ಇಲ್ಲದಿದ್ದರೆ
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್;

                ಆದರೆ( ( ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG & ಪೋರ್ಟ್_NVIC_SYSTICK_ಎಣಿಕೆ_FLAG_ಬಿಟ್ ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG = 0;
                }

                ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ulTimerCountsForOneTick - 1UL;
                ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್;
            }
            #ಆದರೆ_ಅಂತ್ಯ /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            v_Task_ಹೆಜ್ಜೆ_Tick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __asm {
                "cpsie i"
            };
        }
    }

    #ಆದರೆ_ಅಂತ್ಯ /* #if configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
    #ಆದರೆ ( configOVERRIDE_DEFAULT_TICK_CONFIGURATION == 0 )

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
    {
        /* Calculate the constants required to configure the tick interrupt. */
        #ಆದರೆ ( configUSE_TICKLESS_IDLE == 1 )
        {
            ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_ದರ_HZ );
            x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks = ಪೋರ್ಟ್_MAX_24_ಬಿಟ್_ಸಂಖ್ಯೆ / ulTimerCountsForOneTick;
            ulStoppedTimerCompensation = ಪೋರ್ಟ್_MISSED_COUNTS_ಗುಣಕ / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
        }
        #ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */

        /* Reset SysTick. */
        ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = 0UL;
        ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG = 0UL;

        /* Configure SysTick to interrupt at the requested rate. */
        ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_ದರ_HZ ) - 1UL;
        ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್ );
    }

    #ಆದರೆ_ಅಂತ್ಯ /* configOVERRIDE_DEFAULT_TICK_CONFIGURATION */
/*-----------------------------------------------------------*/

/* This is a naked function. */
ಸ್ಥಿರ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enable_VFP( ಶೂನ್ಯ )
{
    __asm {
/* *INDENT-OFF* */
        ldr r0, =0xE000ED88 /* The FPU enable bits are in the CPACR. */
        ldr r1, [ r0 ]

        orr r1, r1, #0xF00000 /* Enable CP10 and CP11 coprocessors, then save back. */
        str r1, [ r0 ]
        bx r14
/* *INDENT-ON* */
    };
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Inside_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    ತಳ_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    ಆದರೆ( CPU_REG_GET( CPU_IPSR ) == 0 )
    {
        xReturn = pdFALSE;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        xReturn = pdTRUE;
    }

    ಹಿಂತಿರುಗಿ xReturn;
}
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configASSERT_DEFINED == 1 )

/* Limitations in the MikroC inline asm means ulCurrentInterrupt has to be
 * global - which makes vPortValidateInterruptPriority() non re-entrant.
 * However that should not matter as an interrupt can only itself be
 * interrupted by a higher priority interrupt.  That means if
 * ulCurrentInterrupt, so ulCurrentInterrupt getting corrupted cannot lead to
 * an invalid interrupt priority being missed. */
    uint32_t ul_Current_ಅಡಚಣೆ;
    uint8_t uc_Current_ಆದ್ಯತೆ;
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Validate_ಅಡಚಣೆ_ಆದ್ಯತೆ( ಶೂನ್ಯ )
    {
        /* Obtain the number of the currently executing interrupt. */
        __asm {
/* *INDENT-OFF* */
            ತಳ್ಳು( r0, r1 )
            mrs r0, ipsr
            ldr r1, =ul_Current_ಅಡಚಣೆ_2
            str r0, [ r1 ]
            ತೆಗೆ_2( r0, r1 )
/* *INDENT-ON* */
        };

        /* Is the interrupt number a user defined interrupt? */
        ಆದರೆ( ul_Current_ಅಡಚಣೆ >= ಪೋರ್ಟ್_ಮೊದಲ_USER_ಅಡಚಣೆ_ಸಂಖ್ಯೆ )
        {
            /* Look up the interrupt's priority. */
            uc_Current_ಆದ್ಯತೆ = *( ( uint8_t * ) ( ಪೋರ್ಟ್_NVIC_IP_REGISTERS_ಸ್ಥಾನಾಂತರ_16 + ul_Current_ಅಡಚಣೆ ) );

            /* The following assertion will fail if a service routine (ISR) for
             * an interrupt that has been assigned a priority above
             * configMAX_SYSCALL_INTERRUPT_PRIORITY calls an ISR safe FreeRTOS API
             * function.  ISR safe FreeRTOS API functions must *only* be called
             * from interrupts that have been assigned a priority at or below
             * configMAX_SYSCALL_INTERRUPT_PRIORITY.
             *
             * Numerically low interrupt priority numbers represent logically high
             * interrupt priorities, therefore the priority of the interrupt must
             * be set to a value equal to or numerically *higher* than
             * configMAX_SYSCALL_INTERRUPT_PRIORITY.
             *
             * Interrupts that  use the FreeRTOS API must not be left at their
             * default priority of  zero as that is the highest possible priority,
             * which is guaranteed to be above configMAX_SYSCALL_INTERRUPT_PRIORITY,
             * and  therefore also guaranteed to be invalid.
             *
             * FreeRTOS maintains separate thread and ISR API functions to ensure
             * interrupt entry is as fast and simple as possible.
             *
             * The following links provide detailed information:
             * https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html
             * https://www.freertos.org/Why-FreeRTOS/FAQs */
            configASSERT( uc_Current_ಆದ್ಯತೆ >= uc_Max_Sys_Call_ಆದ್ಯತೆ );
        }

        /* Priority grouping:  The interrupt controller (NVIC) allows the bits
         * that define each interrupt's priority to be split between bits that
         * define the interrupt's pre-emption priority bits and bits that define
         * the interrupt's sub-priority.  For simplicity all bits must be defined
         * to be pre-emption priority bits.  The following assertion will fail if
         * this is not the case (if some bits represent a sub-priority).
         *
         * If the application only uses CMSIS libraries for interrupt
         * configuration then the correct setting can be achieved on all Cortex-M
         * devices by calling NVIC_SetPriorityGrouping( 0 ); before starting the
         * scheduler.  Note however that some vendor specific peripheral libraries
         * assume a non-zero priority group setting, in which cases using a value
         * of zero will result in unpredictable behaviour. */
        configASSERT( ( ಪೋರ್ಟ್_AIRCR_REG & ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಗುಂಪು_ಮುಖವಾಡ ) <= ulMaxPRIGROUPValue );
    }

    #ಆದರೆ_ಅಂತ್ಯ /* configASSERT_DEFINED */
