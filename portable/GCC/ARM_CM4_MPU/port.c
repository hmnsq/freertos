/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Copyright 2025 Arm Limited and/or its affiliates
 * <open-source-office@arm.com>
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
* Implementation of functions defined in portable.h for the ARM CM4 MPU port.
*----------------------------------------------------------*/

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#define MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"
#ಅನ್ತರ್ಭಾವ "mpu_syscall_numbers.h"

#ifndef __ARM_FP
    #error This port can only be used when the project options are configured to enable hardware floating point support.
#endif

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ifndef configSYSTICK_CLOCK_HZ
    #define configSYSTICK_CLOCK_HZ    configCPU_CLOCK_HZ
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #define portNVIC_SYSTICK_CLK      ( 1UL << 2UL )
#ಅನ್ಯಥಾ

/* The way the SysTick is clocked is not modified in case it is not the same
 * as the core. */
    #define portNVIC_SYSTICK_CLK    ( 0 )
#endif

/* Unprivileged critical sections are not supported when using MPU wrappers
 * version 2. Default the option to 0 and reject an explicit value of 1. */
#ifndef configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS
    #ಯದಿ ( configUSE_MPU_WRAPPERS_V1 == 0 )
        #define configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    0
    #ಅನ್ಯಥಾ
        #warning "configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not defined. We recommend defining it to 0 in FreeRTOSConfig.h for better security."
        #define configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    1
    #endif
#ಅನ್ಯಥಾ
    #ಯದಿ ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) )
        #error configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not supported with MPU wrappers version 2 ( configUSE_MPU_WRAPPERS_V1 == 0 ).
    #endif
#endif

/* Prototype of all Interrupt Service Routines (ISRs). */
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ ( * portISR_t )( ಶೂನ್ಯ );

/* Constants required to access and manipulate the NVIC. */
#define portNVIC_SYSTICK_CTRL_REG                 ( *( ( ಚಞ್ಚಲ uint32_t * ) 0xe000e010 ) )
#define portNVIC_SYSTICK_LOAD_REG                 ( *( ( ಚಞ್ಚಲ uint32_t * ) 0xe000e014 ) )
#define port_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG        ( *( ( ಚಞ್ಚಲ uint32_t * ) 0xe000e018 ) )
#define portNVIC_SHPR3_REG                        ( *( ( ಚಞ್ಚಲ uint32_t * ) 0xe000ed20 ) )
#define portNVIC_SHPR2_REG                        ( *( ( ಚಞ್ಚಲ uint32_t * ) 0xe000ed1c ) )
#define portNVIC_SYS_CTRL_STATE_REG               ( *( ( ಚಞ್ಚಲ uint32_t * ) 0xe000ed24 ) )
#define portNVIC_MEM_FAULT_ENABLE                 ( 1UL << 16UL )

/* Constants used to detect Cortex-M7 r0p0 and r0p1 cores, and ensure
 * that a work around is active for errata 837070. */
#define portCPUID                                 ( *( ( ಚಞ್ಚಲ uint32_t * ) 0xE000ed00 ) )
#define portCORTEX_M7_r0p1_ID                     ( 0x410FC271UL )
#define portCORTEX_M7_r0p0_ID                     ( 0x410FC270UL )

/* Constants required to access and manipulate the MPU. */
#define portMPU_TYPE_REG                          ( *( ( ಚಞ್ಚಲ uint32_t * ) 0xe000ed90 ) )
#define portMPU_REGION_BASE_ADDRESS_REG           ( *( ( ಚಞ್ಚಲ uint32_t * ) 0xe000ed9C ) )
#define portMPU_REGION_ATTRIBUTE_REG              ( *( ( ಚಞ್ಚಲ uint32_t * ) 0xe000edA0 ) )
#define portMPU_CTRL_REG                          ( *( ( ಚಞ್ಚಲ uint32_t * ) 0xe000ed94 ) )
#define port_EXPECTED_MPU_TYPE_ಮೌಲ್ಯ               ( configTOTAL_MPU_REGIONS << 8UL )
#define portMPU_ENABLE                            ( 0x01UL )
#define portMPU_BACKGROUND_ENABLE                 ( 1UL << 2UL )
#define portPRIVILEGED_EXECUTION_START_ADDRESS    ( 0UL )
#define portMPU_REGION_VALID                      ( 0x10UL )
#define portMPU_REGION_ENABLE                     ( 0x01UL )
#define portPERIPHERALS_START_ADDRESS             0x40000000UL
#define portPERIPHERALS_END_ADDRESS               0x5FFFFFFFUL

/* Constants required to access and manipulate the SysTick and other FreeRTOS
 * interrupts. */
#define portNVIC_SYSTICK_INT                      ( 0x00000002UL )
#define portNVIC_SYSTICK_ENABLE                   ( 0x00000001UL )
#define portMIN_INTERRUPT_PRIORITY                ( 255UL )
#define portNVIC_PENDSV_PRI                       ( ( ( uint32_t ) portMIN_INTERRUPT_PRIORITY ) << 16UL )
#define portNVIC_SYSTICK_PRI                      ( ( ( uint32_t ) portMIN_INTERRUPT_PRIORITY ) << 24UL )
#define portNVIC_SVC_PRI                          ( ( ( uint32_t ) configMAX_SYSCALL_INTERRUPT_PRIORITY - 1UL ) << 24UL )

/* Constants required to manipulate the VFP. */
#define portFPCCR                                 ( ( ಚಞ್ಚಲ uint32_t * ) 0xe000ef34UL ) /* Floating point context control register. */
#define portASPEN_AND_LSPEN_BITS                  ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#define portINITIAL_XPSR                          ( 0x01000000UL )
#define portINITIAL_EXC_RETURN                    ( 0xfffffffdUL )
#define portINITIAL_CONTROL_IF_UNPRIVILEGED       ( 0x03 )
#define portINITIAL_CONTROL_IF_PRIVILEGED         ( 0x02 )

/* Constants used to check the installation of the FreeRTOS interrupt handlers. */
#define portSCB_VTOR_REG                          ( *( ( portISR_t ** ) 0xE000ED08 ) )
#define portVECTOR_INDEX_SVC                      ( 11 )
#define portVECTOR_INDEX_PENDSV                   ( 14 )

/* Constants required to check the validity of an interrupt priority. */
#define port_FIRST_USER_INTERRUPT_ಸಂಖ್ಯೆ           ( 16 )
#define portNVIC_IP_REGISTERS_OFFSET_16           ( 0xE000E3F0 )
#define portAIRCR_REG                             ( *( ( ಚಞ್ಚಲ uint32_t * ) 0xE000ED0C ) )
#define port_MAX_8_BIT_ಮೌಲ್ಯ                       ( ( uint8_t ) 0xff )
#define port_ತುದಿ_BIT_OF_BYTE                       ( ( uint8_t ) 0x80 )
#define portMAX_PRIGROUP_BITS                     ( ( uint8_t ) 7 )
#define portPRIORITY_GROUP_MASK                   ( 0x07UL << 8UL )
#define portPRIGROUP_SHIFT                        ( 8UL )

/* Constants used during system call enter and exit. */
#define port_PSR_ರಾಶಿ_PADDING_MASK                ( 1UL << 9UL )
#define port_EXC_RETURN_ರಾಶಿ_FRAME_TYPE_MASK      ( 1UL << 4UL )

/* Offsets in the stack to the parameters when inside the SVC handler. */
#define portOFFSET_TO_LR                          ( 5 )
#define portOFFSET_TO_PC                          ( 6 )
#define portOFFSET_TO_PSR                         ( 7 )


/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#define portSTART_ADDRESS_MASK    ( ( ರಾಶಿ_Type_t ) 0xfffffffeUL )

/* Does addr lie within [start, end] address range? */
#define portIS_ADDRESS_WITHIN_RANGE( addr, start, end ) \
    ( ( ( addr ) >= ( start ) ) && ( ( addr ) <= ( end ) ) )

/* Is the access request satisfied by the available permissions? */
#define portIS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#define portUINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#define portADD_UINT32_WILL_OVERFLOW( a, b )    ( ( a ) > ( portUINT32_MAX - ( b ) ) )
/*-----------------------------------------------------------*/

/*
 * Configure a number of standard MPU regions that are used by all tasks.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvSetupMPU( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

/*
 * Return the smallest MPU region size that a given number of bytes will fit
 * into.  The region size is returned as the value that should be programmed
 * into the region attribute register for that region.
 */
ಸ್ಥಿರ uint32_t prvGetMPURegionSizeSetting( uint32_t ulActualSizeInBytes ) PRIVILEGED_FUNCTION;

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
ಶೂನ್ಯ vPortSetupTimerInterrupt( ಶೂನ್ಯ );

/*
 * Standard FreeRTOS exception handlers.
 */
ಶೂನ್ಯ xPortPendSVHandler( ಶೂನ್ಯ ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;
ಶೂನ್ಯ xPortSysTickHandler( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;
ಶೂನ್ಯ vPortSVCHandler( ಶೂನ್ಯ ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/*
 * Starts the scheduler by restoring the context of the first task to run.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvRestoreContextOfFirstTask( ಶೂನ್ಯ ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/*
 * C portion of the SVC handler.  The SVC handler is split between an asm entry
 * and a C wrapper for simplicity of coding and maintenance.
 */
ಶೂನ್ಯ vSVCHandler_C( uint32_t * pulRegisters ) __attribute__( ( noinline ) ) PRIVILEGED_FUNCTION;

/*
 * Function to enable the VFP.
 */
ಸ್ಥಿರ ಶೂನ್ಯ vPortEnableVFP( ಶೂನ್ಯ ) __attribute__( ( naked ) );

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
BaseType_t xIsPrivileged( ಶೂನ್ಯ ) __attribute__( ( naked ) );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 *
 * Bit 0 of the CONTROL register defines the privilege level of Thread Mode.
 *  Bit[0] = 0 --> The processor is running privileged
 *  Bit[0] = 1 --> The processor is running unprivileged.
 */
ಶೂನ್ಯ vResetPrivilege( ಶೂನ್ಯ ) __attribute__( ( naked ) );

/**
 * @brief Make a task unprivileged.
 */
ಶೂನ್ಯ vPortSwitchToUserMode( ಶೂನ್ಯ );

/**
 * @brief Enter critical section.
 */
#ಯದಿ ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    ಶೂನ್ಯ vPortEnterCritical( ಶೂನ್ಯ ) FREERTOS_SYSTEM_CALL;
#ಅನ್ಯಥಾ
    ಶೂನ್ಯ vPortEnterCritical( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;
#endif

/**
 * @brief Exit from critical section.
 */
#ಯದಿ ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    ಶೂನ್ಯ vPortExitCritical( ಶೂನ್ಯ ) FREERTOS_SYSTEM_CALL;
#ಅನ್ಯಥಾ
    ಶೂನ್ಯ vPortExitCritical( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;
#endif

#ಯದಿ ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the system call stack so that upon returning from
 * SVC, the system call stack is used.
 *
 * @param pulTaskStack The current SP when the SVC was raised.
 * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
 * @param ucSystemCallNumber The system call number of the system call.
 */
    ಶೂನ್ಯ vSystemCallEnter( uint32_t * pul_Task_ರಾಶಿ,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_ಸಂಖ್ಯೆ ) PRIVILEGED_FUNCTION;

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ಯದಿ ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Raise SVC for exiting from a system call.
 */
    ಶೂನ್ಯ vRequestSystemCallExit( ಶೂನ್ಯ ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ಯದಿ ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the task stack so that upon returning from
 * SVC, the task stack is used again.
 *
 * @param pulSystemCallStack The current SP when the SVC was raised.
 * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
 */
    ಶೂನ್ಯ vSystemCallExit( uint32_t * pul_System_Call_ರಾಶಿ,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
BaseType_t xPortIsTaskPrivileged( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;
/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable.  Note this is not saved as part of the task context as context
 * switches can only occur when uxCriticalNesting is zero. */
ಸ್ಥಿರ UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

#ಯದಿ ( configUSE_MPU_WRAPPERS_V1 == 0 )

/*
 * This variable is set to pdTRUE when the scheduler is started.
 */
    PRIVILEGED_DATA ಸ್ಥಿರ BaseType_t xSchedulerRunning = pdFALSE;

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#ಯದಿ ( configASSERT_DEFINED == 1 )
    ಸ್ಥಿರ uint8_t ucMaxSysCallPriority = 0;
    ಸ್ಥಿರ uint32_t ulMaxPRIGROUPValue = 0;
    ಸ್ಥಿರ ಧ್ರುವ ಚಞ್ಚಲ uint8_t * ಧ್ರುವ pcInterruptPriorityRegisters = ( ಧ್ರುವ ಚಞ್ಚಲ uint8_t * ಧ್ರುವ ) portNVIC_IP_REGISTERS_OFFSET_16;
#endif /* configASSERT_DEFINED */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t * px_Port_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_Of_ರಾಶಿ,
                                     TaskFunction_t pxCode,
                                     ಶೂನ್ಯ * pvParameters,
                                     BaseType_t xRunPrivileged,
                                     xMPU_SETTINGS * xMPUSettings )
{
    ಯದಿ( xRunPrivileged == pdTRUE )
    {
        xMPUSettings->ulTaskFlags |= portTASK_IS_PRIVILEGED_FLAG;
        xMPUSettings->ulContext[ 0 ] = portINITIAL_CONTROL_IF_PRIVILEGED;
    }
    ಅನ್ಯಥಾ
    {
        xMPUSettings->ulTaskFlags &= ( ~( portTASK_IS_PRIVILEGED_FLAG ) );
        xMPUSettings->ulContext[ 0 ] = portINITIAL_CONTROL_IF_UNPRIVILEGED;
    }

    xMPUSettings->ulContext[ 1 ] = 0x04040404;                                        /* r4. */
    xMPUSettings->ulContext[ 2 ] = 0x05050505;                                        /* r5. */
    xMPUSettings->ulContext[ 3 ] = 0x06060606;                                        /* r6. */
    xMPUSettings->ulContext[ 4 ] = 0x07070707;                                        /* r7. */
    xMPUSettings->ulContext[ 5 ] = 0x08080808;                                        /* r8. */
    xMPUSettings->ulContext[ 6 ] = 0x09090909;                                        /* r9. */
    xMPUSettings->ulContext[ 7 ] = 0x10101010;                                        /* r10. */
    xMPUSettings->ulContext[ 8 ] = 0x11111111;                                        /* r11. */
    xMPUSettings->ulContext[ 9 ] = portINITIAL_EXC_RETURN;                            /* EXC_RETURN. */

    xMPUSettings->ulContext[ 10 ] = ( uint32_t ) ( px_ತುದಿ_Of_ರಾಶಿ - 8 );                /* PSP with the hardware saved stack. */
    xMPUSettings->ulContext[ 11 ] = ( uint32_t ) pvParameters;                        /* r0. */
    xMPUSettings->ulContext[ 12 ] = 0x01010101;                                       /* r1. */
    xMPUSettings->ulContext[ 13 ] = 0x02020202;                                       /* r2. */
    xMPUSettings->ulContext[ 14 ] = 0x03030303;                                       /* r3. */
    xMPUSettings->ulContext[ 15 ] = 0x12121212;                                       /* r12. */
    xMPUSettings->ulContext[ 16 ] = 0;                                                /* LR. */
    xMPUSettings->ulContext[ 17 ] = ( ( uint32_t ) pxCode ) & portSTART_ADDRESS_MASK; /* PC. */
    xMPUSettings->ulContext[ 18 ] = portINITIAL_XPSR;                                 /* xPSR. */

    #ಯದಿ ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        /* Ensure that the system call stack is double word aligned. */
        xMPUSettings->x_System_Call_ರಾಶಿ_Info.pul_System_Call_ರಾಶಿ = &( xMPUSettings->x_System_Call_ರಾಶಿ_Info.ul_System_Call_ರಾಶಿ_Buffer[ config_SYSTEM_CALL_ರಾಶಿ_SIZE - 1 ] );
        xMPUSettings->x_System_Call_ರಾಶಿ_Info.pul_System_Call_ರಾಶಿ = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_ರಾಶಿ_Info.pul_System_Call_ರಾಶಿ ) &
                                                                                 ( uint32_t ) ( ~( portBYTE_ALIGNMENT_MASK ) ) );

        /* This is not NULL only for the duration of a system call. */
        xMPUSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ = ರಿಕ್ತ;
    }
    #endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    ಪ್ರತ್ಯಾಗಮ &( xMPUSettings->ulContext[ 19 ] );
}
/*-----------------------------------------------------------*/

#ಯದಿ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    ಶೂನ್ಯ vPortSVCHandler( ಶೂನ್ಯ ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm ಚಞ್ಚಲ
        (
            ".syntax unified                \n"
            ".extern vSVCHandler_C          \n"
            ".extern vSystemCallEnter       \n"
            ".extern vSystemCallExit        \n"
            "                               \n"
            "tst lr, #4                     \n"
            "ite eq                         \n"
            "mrseq r0, msp                  \n"
            "mrsne r0, psp                  \n"
            "                               \n"
            "ldr r1, [r0, #24]              \n"
            "ldrb r2, [r1, #-2]             \n"
            "cmp r2, %0                     \n"
            "blt syscall_enter              \n"
            "cmp r2, %1                     \n"
            "beq syscall_exit               \n"
            "b vSVCHandler_C                \n"
            "                               \n"
            "syscall_enter:                 \n"
            "    mov r1, lr                 \n"
            "    b vSystemCallEnter         \n"
            "                               \n"
            "syscall_exit:                  \n"
            "    mov r1, lr                 \n"
            "    b vSystemCallExit          \n"
            "                               \n"
            : /* No outputs. */
            : "i" ( ಅಂಕೆ_SYSTEM_CALLS ), "i" ( portSVC_SYSTEM_CALL_EXIT )
            : "r0", "r1", "r2", "memory"
        );
    }

#ಅನ್ಯಥಾ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    ಶೂನ್ಯ vPortSVCHandler( ಶೂನ್ಯ )
    {
        /* Assumes psp was in use. */
        __asm ಚಞ್ಚಲ
        (
            #ifndef USE_PROCESS_ರಾಶಿ /* Code should not be required if a main() is using the process stack. */
                "   tst lr, #4                      \n"
                "   ite eq                          \n"
                "   mrseq r0, msp                   \n"
                "   mrsne r0, psp                   \n"
            #ಅನ್ಯಥಾ
                "   mrs r0, psp                     \n"
            #endif
            "   b %0                            \n"
            ::"i" ( vSVCHandler_C ) : "r0", "memory"
        );
    }

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vSVCHandler_C( uint32_t * pulParam ) /* PRIVILEGED_FUNCTION */
{
    uint8_t ucSVCNumber;
    uint32_t ulPC;

    #ಯದಿ ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) )
        #ಯದಿ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t * __syscalls_flash_start__;
            ಬಾಹ್ಯ uint32_t * __syscalls_flash_end__;
        #ಅನ್ಯಥಾ
            /* Declaration when these variable are exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t __syscalls_flash_start__[];
            ಬಾಹ್ಯ uint32_t __syscalls_flash_end__[];
        #endif /* #if defined( __ARMCC_VERSION ) */
    #endif /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) ) */

    /* The stack contains: r0, r1, r2, r3, r12, LR, PC and xPSR.  The first
     * argument (r0) is pulParam[ 0 ]. */
    ulPC = pulParam[ portOFFSET_TO_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    ವಿಕಲ್ಪ( ucSVCNumber )
    {
        ಪಕ್ಷ portSVC_START_SCHEDULER:
            prvRestoreContextOfFirstTask();
            ಭಙ್ಗ;

        ಪಕ್ಷ portSVC_YIELD:
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;

            /* Barriers are normally not required
             * but do ensure the code is completely
             * within the specified behaviour for the
             * architecture. */
            __asm ಚಞ್ಚಲ ( "dsb" ::: "memory" );
            __asm ಚಞ್ಚಲ ( "isb" );

            ಭಙ್ಗ;

    #ಯದಿ ( configUSE_MPU_WRAPPERS_V1 == 1 )
        #ಯದಿ ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 )
            ಪಕ್ಷ portSVC_RAISE_PRIVILEGE: /* Only raise the privilege, if the
                                           * svc was raised from any of the
                                           * system calls. */

                ಯದಿ( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                    ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
                {
                    __asm ಚಞ್ಚಲ
                    (
                        "   mrs r1, control     \n" /* Obtain current control value. */
                        "   bic r1, #1          \n" /* Set privilege bit. */
                        "   msr control, r1     \n" /* Write back new control value. */
                        ::: "r1", "memory"
                    );
                }

                ಭಙ್ಗ;
        #ಅನ್ಯಥಾ /* if ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
            ಪಕ್ಷ portSVC_RAISE_PRIVILEGE:
                __asm ಚಞ್ಚಲ
                (
                    "   mrs r1, control     \n" /* Obtain current control value. */
                    "   bic r1, #1          \n" /* Set privilege bit. */
                    "   msr control, r1     \n" /* Write back new control value. */
                    ::: "r1", "memory"
                );
                ಭಙ್ಗ;
        #endif /* #if( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
    #endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

        ಸ್ವಭಾವ: /* Unknown SVC call. */
            ಭಙ್ಗ;
    }
}
/*-----------------------------------------------------------*/

#ಯದಿ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    ಶೂನ್ಯ vSystemCallEnter( uint32_t * pul_Task_ರಾಶಿ,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_ಸಂಖ್ಯೆ ) /* PRIVILEGED_FUNCTION */
    {
        ಬಾಹ್ಯ TaskHandle_t pxCurrentTCB;
        ಬಾಹ್ಯ UBaseType_t uxSystemCallImplementations[ ಅಂಕೆ_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_ರಾಶಿ;
        uint32_t ulHardwareSavedExceptionFrameSize, ulSystemCallLocation, i;

        #ಯದಿ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t * __syscalls_flash_start__;
            ಬಾಹ್ಯ uint32_t * __syscalls_flash_end__;
        #ಅನ್ಯಥಾ
            /* Declaration when these variable are exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t __syscalls_flash_start__[];
            ಬಾಹ್ಯ uint32_t __syscalls_flash_end__[];
        #endif /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_ರಾಶಿ[ portOFFSET_TO_PC ];
        pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );

        /* Checks:
         * 1. SVC is raised from the system call section (i.e. application is
         *    not raising SVC directly).
         * 2. pxMpuSettings->xSystemCallStackInfo.pulTaskStack must be NULL as
         *    it is non-NULL only during the execution of a system call (i.e.
         *    between system call enter and exit).
         * 3. System call is not for a kernel API disabled by the configuration
         *    in FreeRTOSConfig.h.
         * 4. We do not need to check that ucSystemCallNumber is within range
         *    because the assembly SVC handler checks that before calling
         *    this function.
         */
        ಯದಿ( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ == ರಿಕ್ತ ) &&
            ( uxSystemCallImplementations[ uc_System_Call_ಸಂಖ್ಯೆ ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_ರಾಶಿ = pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_System_Call_ರಾಶಿ;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            ಯದಿ( ( ulLR & port_EXC_RETURN_ರಾಶಿ_FRAME_TYPE_MASK ) == 0UL )
            {
                /* Extended frame i.e. FPU in use. */
                ulHardwareSavedExceptionFrameSize = 26;
                __asm ಚಞ್ಚಲ (
                    " vpush {s0}         \n" /* Trigger lazy stacking. */
                    " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                    ::: "memory"
                    );
            }
            ಅನ್ಯಥಾ
            {
                /* Standard frame i.e. FPU not in use. */
                ulHardwareSavedExceptionFrameSize = 8;
            }

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_ರಾಶಿ = pul_System_Call_ರಾಶಿ - ulHardwareSavedExceptionFrameSize;

            /* Copy the stack frame. */
            ಪ್ರತಿ( i = 0; i < ulHardwareSavedExceptionFrameSize; i++ )
            {
                pul_System_Call_ರಾಶಿ[ i ] = pul_Task_ರಾಶಿ[ i ];
            }

            /* Use the pulSystemCallStack in thread mode. */
            __asm ಚಞ್ಚಲ ( "msr psp, %0" : : "r" ( pul_System_Call_ರಾಶಿ ) );

            /* Raise the privilege for the duration of the system call. */
            __asm ಚಞ್ಚಲ (
                " mrs r1, control     \n" /* Obtain current control value. */
                " bic r1, #1          \n" /* Clear nPRIV bit. */
                " msr control, r1     \n" /* Write back new control value. */
                ::: "r1", "memory"
                );

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ = pul_Task_ರಾಶಿ + ulHardwareSavedExceptionFrameSize;

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_ರಾಶಿ_Info.ulLinkRegisterAtSystemCallEntry = pul_Task_ರಾಶಿ[ portOFFSET_TO_LR ];

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_ರಾಶಿ[ portOFFSET_TO_PC ] = uxSystemCallImplementations[ uc_System_Call_ಸಂಖ್ಯೆ ];
            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_ರಾಶಿ[ portOFFSET_TO_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            ಯದಿ( ( pul_Task_ರಾಶಿ[ portOFFSET_TO_PSR ] & port_PSR_ರಾಶಿ_PADDING_MASK ) == port_PSR_ರಾಶಿ_PADDING_MASK )
            {
                pxMpuSettings->ulTaskFlags |= port_ರಾಶಿ_FRAME_HAS_PADDING_FLAG;
            }
            ಅನ್ಯಥಾ
            {
                pxMpuSettings->ulTaskFlags &= ( ~port_ರಾಶಿ_FRAME_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_ರಾಶಿ[ portOFFSET_TO_PSR ] &= ( ~port_PSR_ರಾಶಿ_PADDING_MASK );
        }
    }

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#ಯದಿ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    ಶೂನ್ಯ vRequestSystemCallExit( ಶೂನ್ಯ ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm ಚಞ್ಚಲ ( "svc %0 \n" ::"i" ( portSVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#ಯದಿ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    ಶೂನ್ಯ vSystemCallExit( uint32_t * pul_System_Call_ರಾಶಿ,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        ಬಾಹ್ಯ TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_ರಾಶಿ;
        uint32_t ulHardwareSavedExceptionFrameSize, ulSystemCallLocation, i;

        #ಯದಿ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t * __privileged_functions_start__;
            ಬಾಹ್ಯ uint32_t * __privileged_functions_end__;
        #ಅನ್ಯಥಾ
            /* Declaration when these variable are exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t __privileged_functions_start__[];
            ಬಾಹ್ಯ uint32_t __privileged_functions_end__[];
        #endif /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_ರಾಶಿ[ portOFFSET_TO_PC ];
        pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );

        /* Checks:
         * 1. SVC is raised from the privileged code (i.e. application is not
         *    raising SVC directly). This SVC is only raised from
         *    vRequestSystemCallExit which is in the privileged code section.
         * 2. pxMpuSettings->xSystemCallStackInfo.pulTaskStack must not be NULL -
         *    this means that we previously entered a system call and the
         *    application is not attempting to exit without entering a system
         *    call.
         */
        ಯದಿ( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ != ರಿಕ್ತ ) )
        {
            pul_Task_ರಾಶಿ = pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            ಯದಿ( ( ulLR & port_EXC_RETURN_ರಾಶಿ_FRAME_TYPE_MASK ) == 0UL )
            {
                /* Extended frame i.e. FPU in use. */
                ulHardwareSavedExceptionFrameSize = 26;
                __asm ಚಞ್ಚಲ (
                    " vpush {s0}         \n" /* Trigger lazy stacking. */
                    " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                    ::: "memory"
                    );
            }
            ಅನ್ಯಥಾ
            {
                /* Standard frame i.e. FPU not in use. */
                ulHardwareSavedExceptionFrameSize = 8;
            }

            /* Make space on the task stack for the stack frame. */
            pul_Task_ರಾಶಿ = pul_Task_ರಾಶಿ - ulHardwareSavedExceptionFrameSize;

            /* Copy the stack frame. */
            ಪ್ರತಿ( i = 0; i < ulHardwareSavedExceptionFrameSize; i++ )
            {
                pul_Task_ರಾಶಿ[ i ] = pul_System_Call_ರಾಶಿ[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm ಚಞ್ಚಲ ( "msr psp, %0" : : "r" ( pul_Task_ರಾಶಿ ) );

            /* Drop the privilege before returning to the thread mode. */
            __asm ಚಞ್ಚಲ (
                " mrs r1, control     \n" /* Obtain current control value. */
                " orr r1, #1          \n" /* Set nPRIV bit. */
                " msr control, r1     \n" /* Write back new control value. */
                ::: "r1", "memory"
                );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_ರಾಶಿ[ portOFFSET_TO_PC ] = pxMpuSettings->x_System_Call_ರಾಶಿ_Info.ulLinkRegisterAtSystemCallEntry;
            /* Ensure that LR has a valid value.*/
            pul_Task_ರಾಶಿ[ portOFFSET_TO_LR ] = pxMpuSettings->x_System_Call_ರಾಶಿ_Info.ulLinkRegisterAtSystemCallEntry;

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            ಯದಿ( ( pxMpuSettings->ulTaskFlags & port_ರಾಶಿ_FRAME_HAS_PADDING_FLAG ) == port_ರಾಶಿ_FRAME_HAS_PADDING_FLAG )
            {
                pul_Task_ರಾಶಿ[ portOFFSET_TO_PSR ] |= port_PSR_ರಾಶಿ_PADDING_MASK;
            }
            ಅನ್ಯಥಾ
            {
                pul_Task_ರಾಶಿ[ portOFFSET_TO_PSR ] &= ( ~port_PSR_ರಾಶಿ_PADDING_MASK );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ = ರಿಕ್ತ;
        }
    }

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

BaseType_t xPortIsTaskPrivileged( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
{
    BaseType_t xTaskIsPrivileged = pdFALSE;
    ಧ್ರುವ xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ರಿಕ್ತ ); /* Calling task's MPU settings. */

    ಯದಿ( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
    {
        xTaskIsPrivileged = pdTRUE;
    }

    ಪ್ರತ್ಯಾಗಮ xTaskIsPrivileged;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvRestoreContextOfFirstTask( ಶೂನ್ಯ )
{
    __asm ಚಞ್ಚಲ
    (
        " ldr r0, =0xE000ED08                   \n" /* Use the NVIC offset register to locate the stack. */
        " ldr r0, [r0]                          \n"
        " ldr r0, [r0]                          \n"
        " msr msp, r0                           \n" /* Set the msp back to the start of the stack. */
        "                                       \n"
        /*------------ Program MPU. ------------ */
        " ldr r3, =pxCurrentTCB                 \n" /* r3 = =pxCurrentTCB. */
        " ldr r2, [r3]                          \n" /* r2 = pxCurrentTCB. */
        " add r2, r2, #4                        \n" /* r2 = Second item in the TCB which is xMPUSettings. */
        "                                       \n"
        " dmb                                   \n" /* Complete outstanding transfers before disabling MPU. */
        " ldr r0, =0xe000ed94                   \n" /* MPU_CTRL register. */
        " ldr r3, [r0]                          \n" /* Read the value of MPU_CTRL. */
        " bic r3, #1                            \n" /* r3 = r3 & ~1 i.e. Clear the bit 0 in r3. */
        " str r3, [r0]                          \n" /* Disable MPU. */
        "                                       \n"
        " ldr r0, =0xe000ed9c                   \n" /* Region Base Address register. */
        " ldmia r2!, {r4-r11}                   \n" /* Read 4 sets of MPU registers [MPU Region # 0 - 3]. */
        " stmia r0, {r4-r11}                    \n" /* Write 4 sets of MPU registers [MPU Region # 0 - 3]. */
        "                                       \n"
        #ಯದಿ ( configTOTAL_MPU_REGIONS == 16 )
            " ldmia r2!, {r4-r11}                   \n" /* Read 4 sets of MPU registers [MPU Region # 4 - 8]. */
            " stmia r0, {r4-r11}                    \n" /* Write 4 sets of MPU registers. [MPU Region # 4 - 8]. */
            " ldmia r2!, {r4-r11}                   \n" /* Read 4 sets of MPU registers [MPU Region # 9 - 12]. */
            " stmia r0, {r4-r11}                    \n" /* Write 4 sets of MPU registers. [MPU Region # 9 - 12]. */
        #endif /* configTOTAL_MPU_REGIONS == 16. */
        "                                       \n"
        " ldr r0, =0xe000ed94                   \n" /* MPU_CTRL register. */
        " ldr r3, [r0]                          \n" /* Read the value of MPU_CTRL. */
        " orr r3, #1                            \n" /* r3 = r3 | 1 i.e. Set the bit 0 in r3. */
        " str r3, [r0]                          \n" /* Enable MPU. */
        " dsb                                   \n" /* Force memory writes before continuing. */
        "                                       \n"
        /*---------- Restore Context. ---------- */
        " ldr r3, =pxCurrentTCB                 \n" /* r3 = =pxCurrentTCB. */
        " ldr r2, [r3]                          \n" /* r2 = pxCurrentTCB. */
        " ldr r1, [r2]                          \n" /* r1 = Location of saved context in TCB. */
        "                                       \n"
        " ldmdb r1!, {r0, r4-r11}               \n" /* r0 contains PSP after the hardware had saved context. r4-r11 contain hardware saved context. */
        " msr psp, r0                           \n"
        " stmia r0, {r4-r11}                    \n" /* Copy the hardware saved context on the task stack. */
        " ldmdb r1!, {r3-r11, lr}               \n" /* r3 contains CONTROL register. r4-r11 and LR restored. */
        " msr control, r3                       \n"
        " str r1, [r2]                          \n" /* Save the location where the context should be saved next as the first member of TCB. */
        "                                       \n"
        " mov r0, #0                            \n"
        " msr basepri, r0                       \n"
        " bx lr                                 \n"
        "                                       \n"
        " .ltorg                                \n" /* Assemble current literal pool to avoid offset-out-of-bound errors with lto. */
    );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( ಶೂನ್ಯ )
{
    /* Errata 837070 workaround must only be enabled on Cortex-M7 r0p0
     * and r0p1 cores. */
    #ಯದಿ ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        configASSERT( ( portCPUID == portCORTEX_M7_r0p1_ID ) || ( portCPUID == portCORTEX_M7_r0p0_ID ) );
    #ಅನ್ಯಥಾ

        /* When using this port on a Cortex-M7 r0p0 or r0p1 core, define
         * configENABLE_ERRATA_837070_WORKAROUND to 1 in your
         * FreeRTOSConfig.h. */
        configASSERT( portCPUID != portCORTEX_M7_r0p1_ID );
        configASSERT( portCPUID != portCORTEX_M7_r0p0_ID );
    #endif

    /* An application can install FreeRTOS interrupt handlers in one of the
     * following ways:
     * 1. Direct Routing - Install the functions vPortSVCHandler and
     *    xPortPendSVHandler for SVCall and PendSV interrupts respectively.
     * 2. Indirect Routing - Install separate handlers for SVCall and PendSV
     *    interrupts and route program control from those handlers to
     *    vPortSVCHandler and xPortPendSVHandler functions.
     *
     * Applications that use Indirect Routing must set
     * configCHECK_HANDLER_INSTALLATION to 0 in their FreeRTOSConfig.h. Direct
     * routing, which is validated here when configCHECK_HANDLER_INSTALLATION
     * is 1, should be preferred when possible. */
    #ಯದಿ ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        ಧ್ರುವ portISR_t * ಧ್ರುವ pxVectorTable = portSCB_VTOR_REG;

        /* Validate that the application has correctly installed the FreeRTOS
         * handlers for SVCall and PendSV interrupts. We do not check the
         * installation of the SysTick handler because the application may
         * choose to drive the RTOS tick using a timer other than the SysTick
         * timer by overriding the weak function vPortSetupTimerInterrupt().
         *
         * Assertion failures here indicate incorrect installation of the
         * FreeRTOS handlers. For help installing the FreeRTOS handlers, see
         * https://www.freertos.org/Why-FreeRTOS/FAQs.
         *
         * Systems with a configurable address for the interrupt vector table
         * can also encounter assertion failures or even system faults here if
         * VTOR is not set correctly to point to the application's vector table. */
        configASSERT( pxVectorTable[ portVECTOR_INDEX_SVC ] == vPortSVCHandler );
        configASSERT( pxVectorTable[ portVECTOR_INDEX_PENDSV ] == xPortPendSVHandler );
    }
    #endif /* configCHECK_HANDLER_INSTALLATION */

    #ಯದಿ ( configASSERT_DEFINED == 1 )
    {
        ಚಞ್ಚಲ uint8_t ucOriginalPriority;
        ಚಞ್ಚಲ uint32_t ulImplementedPrioBits = 0;
        ಚಞ್ಚಲ uint8_t * ಧ್ರುವ pucFirstUserPriorityRegister = ( ಚಞ್ಚಲ uint8_t * ಧ್ರುವ ) ( portNVIC_IP_REGISTERS_OFFSET_16 + port_FIRST_USER_INTERRUPT_ಸಂಖ್ಯೆ );
        ಚಞ್ಚಲ uint8_t uc_Max_Priority_ಮೌಲ್ಯ;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
         * functions can be called.  ISR safe functions are those that end in
         * "FromISR".  FreeRTOS maintains separate thread and ISR API functions to
         * ensure interrupt entry is as fast and simple as possible.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        ucOriginalPriority = *pucFirstUserPriorityRegister;

        /* Determine the number of priority bits available.  First write to all
         * possible bits. */
        *pucFirstUserPriorityRegister = port_MAX_8_BIT_ಮೌಲ್ಯ;

        /* Read the value back to see how many bits stuck. */
        uc_Max_Priority_ಮೌಲ್ಯ = *pucFirstUserPriorityRegister;

        /* Use the same mask on the maximum system call priority. */
        ucMaxSysCallPriority = configMAX_SYSCALL_INTERRUPT_PRIORITY & uc_Max_Priority_ಮೌಲ್ಯ;

        /* Check that the maximum system call priority is nonzero after
         * accounting for the number of priority bits supported by the
         * hardware. A priority of 0 is invalid because setting the BASEPRI
         * register to 0 unmasks all interrupts, and interrupts with priority 0
         * cannot be masked using BASEPRI.
         * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( ucMaxSysCallPriority );

        /* Check that the bits not implemented in hardware are zero in
         * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( configMAX_SYSCALL_INTERRUPT_PRIORITY & ( ~uc_Max_Priority_ಮೌಲ್ಯ ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
         * of bits read back. */

        ಯಾವತ್( ( uc_Max_Priority_ಮೌಲ್ಯ & port_ತುದಿ_BIT_OF_BYTE ) == port_ತುದಿ_BIT_OF_BYTE )
        {
            ulImplementedPrioBits++;
            uc_Max_Priority_ಮೌಲ್ಯ <<= ( uint8_t ) 0x01;
        }

        ಯದಿ( ulImplementedPrioBits == 8 )
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
            configASSERT( ( configMAX_SYSCALL_INTERRUPT_PRIORITY & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        ಅನ್ಯಥಾ
        {
            ulMaxPRIGROUPValue = portMAX_PRIGROUP_BITS - ulImplementedPrioBits;
        }

        /* Shift the priority group value back to its position within the AIRCR
         * register. */
        ulMaxPRIGROUPValue <<= portPRIGROUP_SHIFT;
        ulMaxPRIGROUPValue &= portPRIORITY_GROUP_MASK;

        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *pucFirstUserPriorityRegister = ucOriginalPriority;
    }
    #endif /* configASSERT_DEFINED */

    /* Make PendSV and SysTick the lowest priority interrupts, and configure
     * SVCall for sufficient preemption priority. */
    portNVIC_SHPR3_REG |= portNVIC_PENDSV_PRI;
    portNVIC_SHPR3_REG |= portNVIC_SYSTICK_PRI;
    portNVIC_SHPR2_REG = portNVIC_SVC_PRI;

    /* Configure the regions in the MPU that are common to all tasks. */
    prvSetupMPU();

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    vPortSetupTimerInterrupt();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    #ಯದಿ ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        xSchedulerRunning = pdTRUE;
    }
    #endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    /* Ensure the VFP is enabled - it should be anyway. */
    vPortEnableVFP();

    /* Lazy save always. */
    *( portFPCCR ) |= portASPEN_AND_LSPEN_BITS;

    /* Start the first task.  This also clears the bit that indicates the FPU is
     * in use in case the FPU was used before the scheduler was started - which
     * would otherwise result in the unnecessary leaving of space in the SVC stack
     * for lazy saving of FPU registers. */
    __asm ಚಞ್ಚಲ (
        " ldr r0, =0xE000ED08   \n" /* Use the NVIC offset register to locate the stack. */
        " ldr r0, [r0]          \n"
        " ldr r0, [r0]          \n"
        " msr msp, r0           \n" /* Set the msp back to the start of the stack. */
        " mov r0, #0            \n" /* Clear the bit that indicates the FPU is in use, see comment above. */
        " msr control, r0       \n"
        " cpsie i               \n" /* Globally enable interrupts. */
        " cpsie f               \n"
        " dsb                   \n"
        " isb                   \n"
        " svc %0                \n" /* System call to start first task. */
        " nop                   \n"
        " .ltorg                \n"
        ::"i" ( portSVC_START_SCHEDULER ) : "memory" );

    /* Should not get here! */
    ಪ್ರತ್ಯಾಗಮ 0;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortEndScheduler( ಶೂನ್ಯ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortEnterCritical( ಶೂನ್ಯ )
{
    #ಯದಿ ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            portDISABLE_INTERRUPTS();
            uxCriticalNesting++;
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        ಅನ್ಯಥಾ
        {
            portDISABLE_INTERRUPTS();
            uxCriticalNesting++;
        }
    #ಅನ್ಯಥಾ /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        portDISABLE_INTERRUPTS();
        uxCriticalNesting++;
    #endif /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortExitCritical( ಶೂನ್ಯ )
{
    #ಯದಿ ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            ಯದಿ( uxCriticalNesting == 0 )
            {
                portENABLE_INTERRUPTS();
            }

            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        ಅನ್ಯಥಾ
        {
            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            ಯದಿ( uxCriticalNesting == 0 )
            {
                portENABLE_INTERRUPTS();
            }
        }
    #ಅನ್ಯಥಾ /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        configASSERT( uxCriticalNesting );
        uxCriticalNesting--;

        ಯದಿ( uxCriticalNesting == 0 )
        {
            portENABLE_INTERRUPTS();
        }
    #endif /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ xPortPendSVHandler( ಶೂನ್ಯ )
{
    /* This is a naked function. */

    __asm ಚಞ್ಚಲ
    (
        " ldr r3, =pxCurrentTCB                 \n" /* r3 = =pxCurrentTCB. */
        " ldr r2, [r3]                          \n" /* r2 = pxCurrentTCB. */
        " ldr r1, [r2]                          \n" /* r1 = Location where the context should be saved. */
        "                                       \n"
        /*------------ Save Context. ----------- */
        " mrs r3, control                       \n"
        " mrs r0, psp                           \n"
        " isb                                   \n"
        "                                       \n"
        " add r0, r0, #0x20                     \n" /* Move r0 to location where s0 is saved. */
        " tst lr, #0x10                         \n"
        " ittt eq                               \n"
        " vstmiaeq r1!, {s16-s31}               \n" /* Store s16-s31. */
        " vldmiaeq r0, {s0-s16}                 \n" /* Copy hardware saved FP context into s0-s16. */
        " vstmiaeq r1!, {s0-s16}                \n" /* Store hardware saved FP context. */
        " sub r0, r0, #0x20                     \n" /* Set r0 back to the location of hardware saved context. */
        "                                       \n"
        " stmia r1!, {r3-r11, lr}               \n" /* Store CONTROL register, r4-r11 and LR. */
        " ldmia r0, {r4-r11}                    \n" /* Copy hardware saved context into r4-r11. */
        " stmia r1!, {r0, r4-r11}               \n" /* Store original PSP (after hardware has saved context) and the hardware saved context. */
        " str r1, [r2]                          \n" /* Save the location from where the context should be restored as the first member of TCB. */
        "                                       \n"
        /*---------- Select next task. --------- */
        " mov r0, %0                            \n"
        #ಯದಿ ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
            " cpsid i                               \n" /* ARM Cortex-M7 r0p1 Errata 837070 workaround. */
        #endif
        " msr basepri, r0                       \n"
        " dsb                                   \n"
        " isb                                   \n"
        #ಯದಿ ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
            " cpsie i                               \n" /* ARM Cortex-M7 r0p1 Errata 837070 workaround. */
        #endif
        " bl vTaskSwitchContext                 \n"
        " mov r0, #0                            \n"
        " msr basepri, r0                       \n"
        "                                       \n"
        /*------------ Program MPU. ------------ */
        " ldr r3, =pxCurrentTCB                 \n" /* r3 = =pxCurrentTCB. */
        " ldr r2, [r3]                          \n" /* r2 = pxCurrentTCB. */
        " add r2, r2, #4                        \n" /* r2 = Second item in the TCB which is xMPUSettings. */
        "                                       \n"
        " dmb                                   \n" /* Complete outstanding transfers before disabling MPU. */
        " ldr r0, =0xe000ed94                   \n" /* MPU_CTRL register. */
        " ldr r3, [r0]                          \n" /* Read the value of MPU_CTRL. */
        " bic r3, #1                            \n" /* r3 = r3 & ~1 i.e. Clear the bit 0 in r3. */
        " str r3, [r0]                          \n" /* Disable MPU. */
        "                                       \n"
        " ldr r0, =0xe000ed9c                   \n" /* Region Base Address register. */
        " ldmia r2!, {r4-r11}                   \n" /* Read 4 sets of MPU registers [MPU Region # 0 - 3]. */
        " stmia r0, {r4-r11}                    \n" /* Write 4 sets of MPU registers [MPU Region # 0 - 3]. */
        "                                       \n"
        #ಯದಿ ( configTOTAL_MPU_REGIONS == 16 )
            " ldmia r2!, {r4-r11}                   \n" /* Read 4 sets of MPU registers [MPU Region # 4 - 7]. */
            " stmia r0, {r4-r11}                    \n" /* Write 4 sets of MPU registers. [MPU Region # 4 - 7]. */
            " ldmia r2!, {r4-r11}                   \n" /* Read 4 sets of MPU registers [MPU Region # 8 - 11]. */
            " stmia r0, {r4-r11}                    \n" /* Write 4 sets of MPU registers. [MPU Region # 8 - 11]. */
        #endif /* configTOTAL_MPU_REGIONS == 16. */
        "                                       \n"
        " ldr r0, =0xe000ed94                   \n" /* MPU_CTRL register. */
        " ldr r3, [r0]                          \n" /* Read the value of MPU_CTRL. */
        " orr r3, #1                            \n" /* r3 = r3 | 1 i.e. Set the bit 0 in r3. */
        " str r3, [r0]                          \n" /* Enable MPU. */
        " dsb                                   \n" /* Force memory writes before continuing. */
        "                                       \n"
        /*---------- Restore Context. ---------- */
        " ldr r3, =pxCurrentTCB                 \n" /* r3 = =pxCurrentTCB. */
        " ldr r2, [r3]                          \n" /* r2 = pxCurrentTCB. */
        " ldr r1, [r2]                          \n" /* r1 = Location of saved context in TCB. */
        "                                       \n"
        " ldmdb r1!, {r0, r4-r11}               \n" /* r0 contains PSP after the hardware had saved context. r4-r11 contain hardware saved context. */
        " msr psp, r0                           \n"
        " stmia r0!, {r4-r11}                   \n" /* Copy the hardware saved context on the task stack. */
        " ldmdb r1!, {r3-r11, lr}               \n" /* r3 contains CONTROL register. r4-r11 and LR restored. */
        " msr control, r3                       \n"

        " tst lr, #0x10                         \n"
        " ittt eq                               \n"
        " vldmdbeq r1!, {s0-s16}                \n" /* s0-s16 contain hardware saved FP context. */
        " vstmiaeq r0!, {s0-s16}                \n" /* Copy hardware saved FP context on the task stack. */
        " vldmdbeq r1!, {s16-s31}               \n" /* Restore s16-s31. */

        " str r1, [r2]                          \n" /* Save the location where the context should be saved next as the first member of TCB. */
        " bx lr                                 \n"
        "                                       \n"
        " .ltorg                                \n" /* Assemble the current literal pool to avoid offset-out-of-bound errors with lto. */
        ::"i" ( configMAX_SYSCALL_INTERRUPT_PRIORITY )
    );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ xPortSysTickHandler( ಶೂನ್ಯ )
{
    uint32_t ulDummy;

    ulDummy = portSET_INTERRUPT_MASK_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        ಯದಿ( xTaskIncrementTick() != pdFALSE )
        {
            traceISR_EXIT_TO_SCHEDULER();
            /* Pend a context switch. */
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;
        }
        ಅನ್ಯಥಾ
        {
            traceISR_EXIT();
        }
    }
    portCLEAR_INTERRUPT_MASK_FROM_ISR( ulDummy );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__attribute__( ( weak ) ) ಶೂನ್ಯ vPortSetupTimerInterrupt( ಶೂನ್ಯ )
{
    /* Stop and clear the SysTick. */
    portNVIC_SYSTICK_CTRL_REG = 0UL;
    port_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    portNVIC_SYSTICK_LOAD_REG = ( configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL;
    portNVIC_SYSTICK_CTRL_REG = ( portNVIC_SYSTICK_CLK | portNVIC_SYSTICK_INT | portNVIC_SYSTICK_ENABLE );
}
/*-----------------------------------------------------------*/

/* This is a naked function. */
ಸ್ಥಿರ ಶೂನ್ಯ vPortEnableVFP( ಶೂನ್ಯ )
{
    __asm ಚಞ್ಚಲ
    (
        "   ldr.w r0, =0xE000ED88       \n" /* The FPU enable bits are in the CPACR. */
        "   ldr r1, [r0]                \n"
        "                               \n"
        "   orr r1, r1, #( 0xf << 20 )  \n" /* Enable CP10 and CP11 coprocessors, then save back. */
        "   str r1, [r0]                \n"
        "   bx r14                      \n"
        "   .ltorg                      \n"
    );
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvSetupMPU( ಶೂನ್ಯ )
{
    #ಯದಿ defined( __ARMCC_VERSION )

        /* Declaration when these variable are defined in code instead of being
         * exported from linker scripts. */
        ಬಾಹ್ಯ uint32_t * __privileged_functions_start__;
        ಬಾಹ್ಯ uint32_t * __privileged_functions_end__;
        ಬಾಹ್ಯ uint32_t * __FLASH_segment_start__;
        ಬಾಹ್ಯ uint32_t * __FLASH_segment_end__;
        ಬಾಹ್ಯ uint32_t * __privileged_data_start__;
        ಬಾಹ್ಯ uint32_t * __privileged_data_end__;
    #ಅನ್ಯಥಾ
        /* Declaration when these variable are exported from linker scripts. */
        ಬಾಹ್ಯ uint32_t __privileged_functions_start__[];
        ಬಾಹ್ಯ uint32_t __privileged_functions_end__[];
        ಬಾಹ್ಯ uint32_t __FLASH_segment_start__[];
        ಬಾಹ್ಯ uint32_t __FLASH_segment_end__[];
        ಬಾಹ್ಯ uint32_t __privileged_data_start__[];
        ಬಾಹ್ಯ uint32_t __privileged_data_end__[];
    #endif /* if defined( __ARMCC_VERSION ) */

    /* The only permitted number of regions are 8 or 16. */
    configASSERT( ( configTOTAL_MPU_REGIONS == 8 ) || ( configTOTAL_MPU_REGIONS == 16 ) );

    /* Ensure that the configTOTAL_MPU_REGIONS is configured correctly. */
    configASSERT( portMPU_TYPE_REG == port_EXPECTED_MPU_TYPE_ಮೌಲ್ಯ );

    /* Check the expected MPU is present. */
    ಯದಿ( portMPU_TYPE_REG == port_EXPECTED_MPU_TYPE_ಮೌಲ್ಯ )
    {
        /* First setup the unprivileged flash for unprivileged read only access. */
        portMPU_REGION_BASE_ADDRESS_REG = ( ( uint32_t ) __FLASH_segment_start__ ) | /* Base address. */
                                          ( portMPU_REGION_VALID ) |
                                          ( portUNPRIVILEGED_FLASH_REGION );

        portMPU_REGION_ATTRIBUTE_REG = ( portMPU_REGION_READ_ONLY ) |
                                       ( ( configTEX_S_C_B_FLASH & portMPU_RASR_TEX_S_C_B_MASK ) << portMPU_RASR_TEX_S_C_B_LOCATION ) |
                                       ( prvGetMPURegionSizeSetting( ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__ ) ) |
                                       ( portMPU_REGION_ENABLE );

        /* Setup the privileged flash for privileged only access.  This is where
         * the kernel code is placed. */
        portMPU_REGION_BASE_ADDRESS_REG = ( ( uint32_t ) __privileged_functions_start__ ) | /* Base address. */
                                          ( portMPU_REGION_VALID ) |
                                          ( portPRIVILEGED_FLASH_REGION );

        portMPU_REGION_ATTRIBUTE_REG = ( portMPU_REGION_PRIVILEGED_READ_ONLY ) |
                                       ( ( configTEX_S_C_B_FLASH & portMPU_RASR_TEX_S_C_B_MASK ) << portMPU_RASR_TEX_S_C_B_LOCATION ) |
                                       ( prvGetMPURegionSizeSetting( ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__ ) ) |
                                       ( portMPU_REGION_ENABLE );

        /* Setup the privileged data RAM region.  This is where the kernel data
         * is placed. */
        portMPU_REGION_BASE_ADDRESS_REG = ( ( uint32_t ) __privileged_data_start__ ) | /* Base address. */
                                          ( portMPU_REGION_VALID ) |
                                          ( portPRIVILEGED_RAM_REGION );

        portMPU_REGION_ATTRIBUTE_REG = ( portMPU_REGION_PRIVILEGED_READ_WRITE ) |
                                       ( portMPU_REGION_EXECUTE_NEVER ) |
                                       ( ( configTEX_S_C_B_SRAM & portMPU_RASR_TEX_S_C_B_MASK ) << portMPU_RASR_TEX_S_C_B_LOCATION ) |
                                       prvGetMPURegionSizeSetting( ( uint32_t ) __privileged_data_end__ - ( uint32_t ) __privileged_data_start__ ) |
                                       ( portMPU_REGION_ENABLE );

        /* By default allow everything to access the general peripherals.  The
         * system peripherals and registers are protected. */
        portMPU_REGION_BASE_ADDRESS_REG = ( portPERIPHERALS_START_ADDRESS ) |
                                          ( portMPU_REGION_VALID ) |
                                          ( portGENERAL_PERIPHERALS_REGION );

        portMPU_REGION_ATTRIBUTE_REG = ( portMPU_REGION_READ_WRITE | portMPU_REGION_EXECUTE_NEVER ) |
                                       ( prvGetMPURegionSizeSetting( portPERIPHERALS_END_ADDRESS - portPERIPHERALS_START_ADDRESS ) ) |
                                       ( portMPU_REGION_ENABLE );

        /* Enable the memory fault exception. */
        portNVIC_SYS_CTRL_STATE_REG |= portNVIC_MEM_FAULT_ENABLE;

        /* Enable the MPU with the background region configured. */
        portMPU_CTRL_REG |= ( portMPU_ENABLE | portMPU_BACKGROUND_ENABLE );
    }
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ uint32_t prvGetMPURegionSizeSetting( uint32_t ulActualSizeInBytes )
{
    uint32_t ulRegionSize, ul_Return_ಮೌಲ್ಯ = 4;

    /* 32 is the smallest region size, 31 is the largest valid value for
     * ulReturnValue. */
    ಪ್ರತಿ( ulRegionSize = 32UL; ul_Return_ಮೌಲ್ಯ < 31UL; ( ulRegionSize <<= 1UL ) )
    {
        ಯದಿ( ulActualSizeInBytes <= ulRegionSize )
        {
            ಭಙ್ಗ;
        }
        ಅನ್ಯಥಾ
        {
            ul_Return_ಮೌಲ್ಯ++;
        }
    }

    /* Shift the code by one before returning so it can be written directly
     * into the correct bit position of the attribute register. */
    ಪ್ರತ್ಯಾಗಮ( ul_Return_ಮೌಲ್ಯ << 1UL );
}
/*-----------------------------------------------------------*/

BaseType_t xIsPrivileged( ಶೂನ್ಯ ) /* __attribute__ (( naked )) */
{
    __asm ಚಞ್ಚಲ
    (
        "   mrs r0, control                         \n" /* r0 = CONTROL. */
        "   tst r0, #1                              \n" /* Perform r0 & 1 (bitwise AND) and update the conditions flag. */
        "   ite ne                                  \n"
        "   movne r0, #0                            \n" /* CONTROL[0]!=0. Return false to indicate that the processor is not privileged. */
        "   moveq r0, #1                            \n" /* CONTROL[0]==0. Return true to indicate that the processor is privileged. */
        "   bx lr                                   \n" /* Return. */
        ::: "r0", "memory"
    );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vResetPrivilege( ಶೂನ್ಯ ) /* __attribute__ (( naked )) */
{
    __asm ಚಞ್ಚಲ
    (
        "   mrs r0, control                         \n" /* r0 = CONTROL. */
        "   orr r0, #1                              \n" /* r0 = r0 | 1. */
        "   msr control, r0                         \n" /* CONTROL = r0. */
        "   bx lr                                   \n" /* Return to the caller. */
        ::: "r0", "memory"
    );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortSwitchToUserMode( ಶೂನ್ಯ )
{
    /* Load the current task's MPU settings from its TCB. */
    xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ರಿಕ್ತ );

    /* Mark the task as unprivileged. */
    xTaskMpuSettings->ulTaskFlags &= ( ~( portTASK_IS_PRIVILEGED_FLAG ) );

    /* Lower the processor's privilege level. */
    vResetPrivilege();
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortStoreTaskMPUSettings( xMPU_SETTINGS * xMPUSettings,
                                ಧ್ರುವ ಸಂರಚನಾ xMEMORY_REGION * ಧ್ರುವ xRegions,
                                ರಾಶಿ_Type_t * px_Bottom_Of_ರಾಶಿ,
                                config_ರಾಶಿ_DEPTH_TYPE ux_ರಾಶಿ_Depth )
{
    #ಯದಿ defined( __ARMCC_VERSION )

        /* Declaration when these variable are defined in code instead of being
         * exported from linker scripts. */
        ಬಾಹ್ಯ uint32_t * __SRAM_segment_start__;
        ಬಾಹ್ಯ uint32_t * __SRAM_segment_end__;
        ಬಾಹ್ಯ uint32_t * __privileged_data_start__;
        ಬಾಹ್ಯ uint32_t * __privileged_data_end__;
    #ಅನ್ಯಥಾ
        /* Declaration when these variable are exported from linker scripts. */
        ಬಾಹ್ಯ uint32_t __SRAM_segment_start__[];
        ಬಾಹ್ಯ uint32_t __SRAM_segment_end__[];
        ಬಾಹ್ಯ uint32_t __privileged_data_start__[];
        ಬಾಹ್ಯ uint32_t __privileged_data_end__[];
    #endif /* if defined( __ARMCC_VERSION ) */

    int32_t lIndex;
    uint32_t ul;

    ಯದಿ( xRegions == ರಿಕ್ತ )
    {
        /* No MPU regions are specified so allow access to all RAM. */
        xMPUSettings->xRegion[ 0 ].ulRegionBaseAddress =
            ( ( uint32_t ) __SRAM_segment_start__ ) | /* Base address. */
            ( portMPU_REGION_VALID ) |
            ( port_ರಾಶಿ_REGION );                     /* Region number. */

        xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
            ( portMPU_REGION_READ_WRITE ) |
            ( portMPU_REGION_EXECUTE_NEVER ) |
            ( ( configTEX_S_C_B_SRAM & portMPU_RASR_TEX_S_C_B_MASK ) << portMPU_RASR_TEX_S_C_B_LOCATION ) |
            ( prvGetMPURegionSizeSetting( ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__ ) ) |
            ( portMPU_REGION_ENABLE );

        xMPUSettings->xRegionSettings[ 0 ].ulRegionStartAddress = ( uint32_t ) __SRAM_segment_start__;
        xMPUSettings->xRegionSettings[ 0 ].ulRegionEndAddress = ( uint32_t ) __SRAM_segment_end__;
        xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                   tskMPU_WRITE_PERMISSION );

        /* Invalidate user configurable regions. */
        ಪ್ರತಿ( ul = 1UL; ul <= port_ಅಂಕೆ_CONFIGURABLE_REGIONS; ul++ )
        {
            xMPUSettings->xRegion[ ul ].ulRegionBaseAddress = ( ( ul - 1UL ) | portMPU_REGION_VALID );
            xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ulRegionStartAddress = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ulRegionEndAddress = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
        }
    }
    ಅನ್ಯಥಾ
    {
        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid.  At all other
         * times the stack parameters will not be valid and it is assumed that the
         * stack region has already been configured. */
        ಯದಿ( ux_ರಾಶಿ_Depth > 0 )
        {
            /* Define the region that allows access to the stack. */
            xMPUSettings->xRegion[ 0 ].ulRegionBaseAddress =
                ( ( uint32_t ) px_Bottom_Of_ರಾಶಿ ) |
                ( portMPU_REGION_VALID ) |
                ( port_ರಾಶಿ_REGION ); /* Region number. */

            xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
                ( portMPU_REGION_READ_WRITE ) |
                ( portMPU_REGION_EXECUTE_NEVER ) |
                ( prvGetMPURegionSizeSetting( ux_ರಾಶಿ_Depth * ( config_ರಾಶಿ_DEPTH_TYPE ) ಪರಿಮಾಣ( ರಾಶಿ_Type_t ) ) ) |
                ( ( configTEX_S_C_B_SRAM & portMPU_RASR_TEX_S_C_B_MASK ) << portMPU_RASR_TEX_S_C_B_LOCATION ) |
                ( portMPU_REGION_ENABLE );

            xMPUSettings->xRegionSettings[ 0 ].ulRegionStartAddress = ( uint32_t ) px_Bottom_Of_ರಾಶಿ;
            xMPUSettings->xRegionSettings[ 0 ].ulRegionEndAddress = ( uint32_t ) ( ( uint32_t ) ( px_Bottom_Of_ರಾಶಿ ) +
                                                                                   ( ux_ರಾಶಿ_Depth * ( config_ರಾಶಿ_DEPTH_TYPE ) ಪರಿಮಾಣ( ರಾಶಿ_Type_t ) ) - 1UL );
            xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                       tskMPU_WRITE_PERMISSION );
        }

        lIndex = 0;

        ಪ್ರತಿ( ul = 1UL; ul <= port_ಅಂಕೆ_CONFIGURABLE_REGIONS; ul++ )
        {
            ಯದಿ( ( xRegions[ lIndex ] ).ulLengthInBytes > 0UL )
            {
                /* Translate the generic region definition contained in
                 * xRegions into the CM4 specific MPU settings that are then
                 * stored in xMPUSettings. */
                xMPUSettings->xRegion[ ul ].ulRegionBaseAddress =
                    ( ( uint32_t ) xRegions[ lIndex ].pvBaseAddress ) |
                    ( portMPU_REGION_VALID ) |
                    ( ul - 1UL ); /* Region number. */

                xMPUSettings->xRegion[ ul ].ulRegionAttribute =
                    ( prvGetMPURegionSizeSetting( xRegions[ lIndex ].ulLengthInBytes ) ) |
                    ( xRegions[ lIndex ].ulParameters ) |
                    ( portMPU_REGION_ENABLE );

                xMPUSettings->xRegionSettings[ ul ].ulRegionStartAddress = ( uint32_t ) xRegions[ lIndex ].pvBaseAddress;
                xMPUSettings->xRegionSettings[ ul ].ulRegionEndAddress = ( uint32_t ) ( ( uint32_t ) xRegions[ lIndex ].pvBaseAddress + xRegions[ lIndex ].ulLengthInBytes - 1UL );
                xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;

                ಯದಿ( ( ( xRegions[ lIndex ].ulParameters & portMPU_REGION_READ_ONLY ) == portMPU_REGION_READ_ONLY ) ||
                    ( ( xRegions[ lIndex ].ulParameters & portMPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) == portMPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = tskMPU_READ_PERMISSION;
                }

                ಯದಿ( ( xRegions[ lIndex ].ulParameters & portMPU_REGION_READ_WRITE ) == portMPU_REGION_READ_WRITE )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
                }
            }
            ಅನ್ಯಥಾ
            {
                /* Invalidate the region. */
                xMPUSettings->xRegion[ ul ].ulRegionBaseAddress = ( ( ul - 1UL ) | portMPU_REGION_VALID );
                xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ulRegionStartAddress = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ulRegionEndAddress = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
            }

            lIndex++;
        }
    }
}
/*-----------------------------------------------------------*/

#ಯದಿ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    BaseType_t xPortIsAuthorizedToAccessBuffer( ಧ್ರುವ ಶೂನ್ಯ * pvBuffer,
                                                size_t xBufferLength,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ulBufferStartAddress, ulBufferEndAddress;
        BaseType_t xAccessGranted = pdFALSE;
        ಧ್ರುವ xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ರಿಕ್ತ ); /* Calling task's MPU settings. */

        ಯದಿ( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        ಅನ್ಯಥಾ ಯದಿ( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        ಅನ್ಯಥಾ
        {
            ಯದಿ( portADD_UINT32_WILL_OVERFLOW( ( ( uint32_t ) pvBuffer ), ( ( uint32_t ) xBufferLength - 1UL ) ) == pdFALSE )
            {
                ulBufferStartAddress = ( uint32_t ) pvBuffer;
                ulBufferEndAddress = ( ( ( uint32_t ) pvBuffer ) + ( uint32_t ) xBufferLength - 1UL );

                ಪ್ರತಿ( i = 0; i < port_TOTAL_ಅಂಕೆ_REGIONS_IN_TCB; i++ )
                {
                    ಯದಿ( portIS_ADDRESS_WITHIN_RANGE( ulBufferStartAddress,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ulRegionStartAddress,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ulRegionEndAddress ) &&
                        portIS_ADDRESS_WITHIN_RANGE( ulBufferEndAddress,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ulRegionStartAddress,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ulRegionEndAddress ) &&
                        portIS_AUTHORIZED( ulAccessRequested, xTaskMpuSettings->xRegionSettings[ i ].ulRegionPermissions ) )
                    {
                        xAccessGranted = pdTRUE;
                        ಭಙ್ಗ;
                    }
                }
            }
        }

        ಪ್ರತ್ಯಾಗಮ xAccessGranted;
    }

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#ಯದಿ ( configASSERT_DEFINED == 1 )

    ಶೂನ್ಯ vPortValidateInterruptPriority( ಶೂನ್ಯ )
    {
        uint32_t ulCurrentInterrupt;
        uint8_t ucCurrentPriority;

        /* Obtain the number of the currently executing interrupt. */
        __asm ಚಞ್ಚಲ ( "mrs %0, ipsr" : "=r" ( ulCurrentInterrupt )::"memory" );

        /* Is the interrupt number a user defined interrupt? */
        ಯದಿ( ulCurrentInterrupt >= port_FIRST_USER_INTERRUPT_ಸಂಖ್ಯೆ )
        {
            /* Look up the interrupt's priority. */
            ucCurrentPriority = pcInterruptPriorityRegisters[ ulCurrentInterrupt ];

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
             * Interrupts that use the FreeRTOS API must not be left at their
             * default priority of zero as that is the highest possible priority,
             * which is guaranteed to be above configMAX_SYSCALL_INTERRUPT_PRIORITY,
             * and therefore also guaranteed to be invalid.
             *
             * FreeRTOS maintains separate thread and ISR API functions to ensure
             * interrupt entry is as fast and simple as possible.
             *
             * The following links provide detailed information:
             * https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html
             * https://www.freertos.org/Why-FreeRTOS/FAQs */
            configASSERT( ucCurrentPriority >= ucMaxSysCallPriority );
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
        configASSERT( ( portAIRCR_REG & portPRIORITY_GROUP_MASK ) <= ulMaxPRIGROUPValue );
    }

#endif /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/

#ಯದಿ ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    ಶೂನ್ಯ vPortGrantAccessToKernelObject( TaskHandle_t xInternalTaskHandle,
                                         int32_t lInternalIndexOfKernelObject ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ulAccessControlListEntryIndex, ulAccessControlListEntryBit;
        xMPU_SETTINGS * xTaskMpuSettings;

        ulAccessControlListEntryIndex = ( ( uint32_t ) lInternalIndexOfKernelObject / portACL_ENTRY_SIZE_BITS );
        ulAccessControlListEntryBit = ( ( uint32_t ) lInternalIndexOfKernelObject % portACL_ENTRY_SIZE_BITS );

        xTaskMpuSettings = xTaskGetMPUSettings( xInternalTaskHandle );

        xTaskMpuSettings->ulAccessControlList[ ulAccessControlListEntryIndex ] |= ( 1U << ulAccessControlListEntryBit );
    }

#endif /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#ಯದಿ ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    ಶೂನ್ಯ vPortRevokeAccessToKernelObject( TaskHandle_t xInternalTaskHandle,
                                          int32_t lInternalIndexOfKernelObject ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ulAccessControlListEntryIndex, ulAccessControlListEntryBit;
        xMPU_SETTINGS * xTaskMpuSettings;

        ulAccessControlListEntryIndex = ( ( uint32_t ) lInternalIndexOfKernelObject / portACL_ENTRY_SIZE_BITS );
        ulAccessControlListEntryBit = ( ( uint32_t ) lInternalIndexOfKernelObject % portACL_ENTRY_SIZE_BITS );

        xTaskMpuSettings = xTaskGetMPUSettings( xInternalTaskHandle );

        xTaskMpuSettings->ulAccessControlList[ ulAccessControlListEntryIndex ] &= ~( 1U << ulAccessControlListEntryBit );
    }

#endif /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#ಯದಿ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #ಯದಿ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        BaseType_t xPortIsAuthorizedToAccessKernelObject( int32_t lInternalIndexOfKernelObject ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulAccessControlListEntryIndex, ulAccessControlListEntryBit;
            BaseType_t xAccessGranted = pdFALSE;
            ಧ್ರುವ xMPU_SETTINGS * xTaskMpuSettings;

            ಯದಿ( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            ಅನ್ಯಥಾ
            {
                xTaskMpuSettings = xTaskGetMPUSettings( ರಿಕ್ತ ); /* Calling task's MPU settings. */

                ulAccessControlListEntryIndex = ( ( uint32_t ) lInternalIndexOfKernelObject / portACL_ENTRY_SIZE_BITS );
                ulAccessControlListEntryBit = ( ( uint32_t ) lInternalIndexOfKernelObject % portACL_ENTRY_SIZE_BITS );

                ಯದಿ( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                ಅನ್ಯಥಾ
                {
                    ಯದಿ( ( xTaskMpuSettings->ulAccessControlList[ ulAccessControlListEntryIndex ] & ( 1U << ulAccessControlListEntryBit ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xAccessGranted;
        }

    #ಅನ್ಯಥಾ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        BaseType_t xPortIsAuthorizedToAccessKernelObject( int32_t lInternalIndexOfKernelObject ) /* PRIVILEGED_FUNCTION */
        {
            ( ಶೂನ್ಯ ) lInternalIndexOfKernelObject;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            ಪ್ರತ್ಯಾಗಮ pdTRUE;
        }

    #endif /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/
