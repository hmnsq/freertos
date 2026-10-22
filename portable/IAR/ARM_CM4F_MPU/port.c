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
* Implementation of functions defined in portable.h for the ARM CM4F MPU port.
*----------------------------------------------------------*/

/* IAR includes. */
#شامل <intrinsics.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#define MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#شامل "FreeRTOS.h"
#شامل "task.h"
#شامل "mpu_syscall_numbers.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ifndef __ARMVFP__
    #error This port can only be used when the project options are configured to enable hardware floating point support.
#endif

#اگر ( configMAX_SYSCALL_INTERRUPT_PRIORITY == 0 )
    #error configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to 0.  See http: /*www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
#endif

#ifndef configSYSTICK_CLOCK_HZ
    #define configSYSTICK_CLOCK_HZ      configCPU_CLOCK_HZ
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #define portNVIC_SYSTICK_CLK_BIT    ( 1UL << 2UL )
#وگرنه

/* The way the SysTick is clocked is not modified in case it is not the same
 * as the core. */
    #define portNVIC_SYSTICK_CLK_BIT    ( 0 )
#endif

/* Unprivileged critical sections are not supported when using MPU wrappers
 * version 2. Default the option to 0 and reject an explicit value of 1. */
#ifndef configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS
    #اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )
        #define configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    0
    #وگرنه
        #warning "configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not defined. We recommend defining it to 0 in FreeRTOSConfig.h for better security."
        #define configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    1
    #endif
#وگرنه
    #اگر ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) )
        #error configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not supported with MPU wrappers version 2 ( configUSE_MPU_WRAPPERS_V1 == 0 ).
    #endif
#endif

/* Prototype of all Interrupt Service Routines (ISRs). */
تعریفنوع تهی ( * portISR_t )( تهی );

/* Constants required to manipulate the core.  Registers first... */
#define portNVIC_SYSTICK_CTRL_REG                 ( *( ( فرار uint32_t * ) 0xe000e010 ) )
#define portNVIC_SYSTICK_LOAD_REG                 ( *( ( فرار uint32_t * ) 0xe000e014 ) )
#define port_NVIC_SYSTICK_CURRENT_مقدار_REG        ( *( ( فرار uint32_t * ) 0xe000e018 ) )
#define portNVIC_SHPR3_REG                        ( *( ( فرار uint32_t * ) 0xe000ed20 ) )
#define portNVIC_SHPR2_REG                        ( *( ( فرار uint32_t * ) 0xe000ed1c ) )
#define portNVIC_SYS_CTRL_STATE_REG               ( *( ( فرار uint32_t * ) 0xe000ed24 ) )
#define portNVIC_MEM_FAULT_ENABLE                 ( 1UL << 16UL )

/* Constants required to access and manipulate the MPU. */
#define portMPU_TYPE_REG                          ( *( ( فرار uint32_t * ) 0xe000ed90 ) )
#define portMPU_REGION_BASE_ADDRESS_REG           ( *( ( فرار uint32_t * ) 0xe000ed9C ) )
#define portMPU_REGION_ATTRIBUTE_REG              ( *( ( فرار uint32_t * ) 0xe000edA0 ) )
#define portMPU_CTRL_REG                          ( *( ( فرار uint32_t * ) 0xe000ed94 ) )
#define port_EXPECTED_MPU_TYPE_مقدار               ( configTOTAL_MPU_REGIONS << 8UL )
#define portMPU_ENABLE                            ( 0x01UL )
#define portMPU_BACKGROUND_ENABLE                 ( 1UL << 2UL )
#define portPRIVILEGED_EXECUTION_START_ADDRESS    ( 0UL )
#define portMPU_REGION_VALID                      ( 0x10UL )
#define portMPU_REGION_ENABLE                     ( 0x01UL )
#define portPERIPHERALS_START_ADDRESS             0x40000000UL
#define portPERIPHERALS_END_ADDRESS               0x5FFFFFFFUL

/* ...then bits in the registers. */
#define portNVIC_SYSTICK_INT_BIT                  ( 1UL << 1UL )
#define portNVIC_SYSTICK_ENABLE_BIT               ( 1UL << 0UL )
#define port_NVIC_SYSTICK_شمار_FLAG_BIT           ( 1UL << 16UL )
#define portNVIC_PENDSVCLEAR_BIT                  ( 1UL << 27UL )
#define portNVIC_PEND_SYSTICK_CLEAR_BIT           ( 1UL << 25UL )

/* Constants used to detect Cortex-M7 r0p0 and r0p1 cores, and ensure
 * that a work around is active for errata 837070. */
#define portCPUID                                 ( *( ( فرار uint32_t * ) 0xE000ed00 ) )
#define portCORTEX_M7_r0p1_ID                     ( 0x410FC271UL )
#define portCORTEX_M7_r0p0_ID                     ( 0x410FC270UL )

/* Constants to manipulate FreeRTOS interrupt priorities. */
#define portMIN_INTERRUPT_PRIORITY                ( 255UL )
#define portNVIC_PENDSV_PRI                       ( ( ( uint32_t ) portMIN_INTERRUPT_PRIORITY ) << 16UL )
#define portNVIC_SYSTICK_PRI                      ( ( ( uint32_t ) portMIN_INTERRUPT_PRIORITY ) << 24UL )
#define portNVIC_SVC_PRI                          ( ( ( uint32_t ) configMAX_SYSCALL_INTERRUPT_PRIORITY - 1UL ) << 24UL )

/* Constants used to check the installation of the FreeRTOS interrupt handlers. */
#define portSCB_VTOR_REG                          ( *( ( portISR_t ** ) 0xE000ED08 ) )
#define portVECTOR_INDEX_SVC                      ( 11 )
#define portVECTOR_INDEX_PENDSV                   ( 14 )

/* Constants required to check the validity of an interrupt priority. */
#define port_FIRST_USER_INTERRUPT_عدد           ( 16 )
#define portNVIC_IP_REGISTERS_OFFSET_16           ( 0xE000E3F0 )
#define portAIRCR_REG                             ( *( ( فرار uint32_t * ) 0xE000ED0C ) )
#define port_MAX_8_BIT_مقدار                       ( ( uint8_t ) 0xff )
#define port_بالاترین_BIT_OF_BYTE                       ( ( uint8_t ) 0x80 )
#define portMAX_PRIGROUP_BITS                     ( ( uint8_t ) 7 )
#define portPRIORITY_GROUP_MASK                   ( 0x07UL << 8UL )
#define portPRIGROUP_SHIFT                        ( 8UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#define portVECTACTIVE_MASK                       ( 0xFFUL )

/* Constants required to manipulate the VFP. */
#define portFPCCR                                 ( ( فرار uint32_t * ) 0xe000ef34 ) /* Floating point context control register. */
#define portASPEN_AND_LSPEN_BITS                  ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#define portINITIAL_XPSR                          ( 0x01000000 )
#define portINITIAL_EXC_RETURN                    ( 0xfffffffd )
#define portINITIAL_CONTROL_IF_UNPRIVILEGED       ( 0x03 )
#define portINITIAL_CONTROL_IF_PRIVILEGED         ( 0x02 )

/* Constants used during system call enter and exit. */
#define port_PSR_پشته_PADDING_MASK                ( 1UL << 9UL )
#define port_EXC_RETURN_پشته_FRAME_TYPE_MASK      ( 1UL << 4UL )

/* Offsets in the stack to the parameters when inside the SVC handler. */
#define portOFFSET_TO_LR                          ( 5 )
#define portOFFSET_TO_PC                          ( 6 )
#define portOFFSET_TO_PSR                         ( 7 )

/* The systick is a 24-bit counter. */
#define port_MAX_24_BIT_عدد                     ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#define portMISSED_COUNTS_FACTOR                  ( 45UL )

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#define portSTART_ADDRESS_MASK                    ( ( پشته_Type_t ) 0xfffffffeUL )

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
ایستا تهی prvSetupMPU( تهی ) PRIVILEGED_FUNCTION;

/*
 * Return the smallest MPU region size that a given number of bytes will fit
 * into.  The region size is returned as the value that should be programmed
 * into the region attribute register for that region.
 */
ایستا uint32_t prvGetMPURegionSizeSetting( uint32_t ulActualSizeInBytes ) PRIVILEGED_FUNCTION;

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
تهی vPortSetupTimerInterrupt( تهی );

/*
 * Exception handlers.
 */
تهی xPortSysTickHandler( تهی ) PRIVILEGED_FUNCTION;

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
بیرونی تهی vPortStartFirstTask( تهی ) PRIVILEGED_FUNCTION;

/*
 * Turn the VFP on.
 */
بیرونی تهی vPortEnableVFP( تهی );

/*
 * The C portion of the SVC handler.
 */
تهی vPortSVCHandler_C( uint32_t * pulParam ) PRIVILEGED_FUNCTION;

/*
 * Called from the SVC handler used to start the scheduler.
 */
بیرونی تهی vPortRestoreContextOfFirstTask( تهی ) PRIVILEGED_FUNCTION;

/**
 * @brief Enter critical section.
 */
#اگر ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    تهی vPortEnterCritical( تهی ) FREERTOS_SYSTEM_CALL;
#وگرنه
    تهی vPortEnterCritical( تهی ) PRIVILEGED_FUNCTION;
#endif

/**
 * @brief Exit from critical section.
 */
#اگر ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    تهی vPortExitCritical( تهی ) FREERTOS_SYSTEM_CALL;
#وگرنه
    تهی vPortExitCritical( تهی ) PRIVILEGED_FUNCTION;
#endif

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the system call stack so that upon returning from
 * SVC, the system call stack is used.
 *
 * @param pulTaskStack The current SP when the SVC was raised.
 * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
 * @param ucSystemCallNumber The system call number of the system call.
 */
    تهی vSystemCallEnter( uint32_t * pul_Task_پشته,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_عدد ) PRIVILEGED_FUNCTION;

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Raise SVC for exiting from a system call.
 */
    تهی vRequestSystemCallExit( تهی ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the task stack so that upon returning from
 * SVC, the task stack is used again.
 *
 * @param pulSystemCallStack The current SP when the SVC was raised.
 * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
 */
    تهی vSystemCallExit( uint32_t * pul_System_Call_پشته,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
BaseType_t xPortIsTaskPrivileged( تهی ) PRIVILEGED_FUNCTION;

/**
 * @brief Make a task unprivileged.
 */
تهی vPortSwitchToUserMode( تهی );

/*
 * FreeRTOS handlers implemented in assembly.
 */
بیرونی تهی vPortSVCHandler( تهی ) PRIVILEGED_FUNCTION;
بیرونی تهی xPortPendSVHandler( تهی ) PRIVILEGED_FUNCTION;
/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
ایستا UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

/*
 * This variable is set to pdTRUE when the scheduler is started.
 */
    PRIVILEGED_DATA ایستا BaseType_t xSchedulerRunning = pdFALSE;

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#اگر ( configASSERT_DEFINED == 1 )
    ایستا uint8_t ucMaxSysCallPriority = 0;
    ایستا uint32_t ulMaxPRIGROUPValue = 0;
    ایستا ثابت فرار uint8_t * ثابت pcInterruptPriorityRegisters = ( ثابت فرار uint8_t * ثابت ) portNVIC_IP_REGISTERS_OFFSET_16;
#endif /* configASSERT_DEFINED */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
پشته_Type_t * px_Port_Initialise_پشته( پشته_Type_t * px_بالاترین_Of_پشته,
                                     TaskFunction_t pxCode,
                                     تهی * pvParameters,
                                     BaseType_t xRunPrivileged,
                                     xMPU_SETTINGS * xMPUSettings )
{
    اگر( xRunPrivileged == pdTRUE )
    {
        xMPUSettings->ulTaskFlags |= portTASK_IS_PRIVILEGED_FLAG;
        xMPUSettings->ulContext[ 0 ] = portINITIAL_CONTROL_IF_PRIVILEGED;
    }
    وگرنه
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

    xMPUSettings->ulContext[ 10 ] = ( uint32_t ) ( px_بالاترین_Of_پشته - 8 );                /* PSP with the hardware saved stack. */
    xMPUSettings->ulContext[ 11 ] = ( uint32_t ) pvParameters;                        /* r0. */
    xMPUSettings->ulContext[ 12 ] = 0x01010101;                                       /* r1. */
    xMPUSettings->ulContext[ 13 ] = 0x02020202;                                       /* r2. */
    xMPUSettings->ulContext[ 14 ] = 0x03030303;                                       /* r3. */
    xMPUSettings->ulContext[ 15 ] = 0x12121212;                                       /* r12. */
    xMPUSettings->ulContext[ 16 ] = 0;                                                /* LR. */
    xMPUSettings->ulContext[ 17 ] = ( ( uint32_t ) pxCode ) & portSTART_ADDRESS_MASK; /* PC. */
    xMPUSettings->ulContext[ 18 ] = portINITIAL_XPSR;                                 /* xPSR. */

    #اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        /* Ensure that the system call stack is double word aligned. */
        xMPUSettings->x_System_Call_پشته_Info.pul_System_Call_پشته = &( xMPUSettings->x_System_Call_پشته_Info.ul_System_Call_پشته_Buffer[ config_SYSTEM_CALL_پشته_SIZE - 1 ] );
        xMPUSettings->x_System_Call_پشته_Info.pul_System_Call_پشته = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_پشته_Info.pul_System_Call_پشته ) &
                                                                                 ( uint32_t ) ( ~( portBYTE_ALIGNMENT_MASK ) ) );

        /* This is not NULL only for the duration of a system call. */
        xMPUSettings->x_System_Call_پشته_Info.pul_Task_پشته = پوچ;
    }
    #endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    بازگشت &( xMPUSettings->ulContext[ 19 ] );
}
/*-----------------------------------------------------------*/

تهی vPortSVCHandler_C( uint32_t * pulParam ) /* PRIVILEGED_FUNCTION */
{
    uint8_t ucSVCNumber;
    uint32_t ulPC;

    #اگر ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) )
        بیرونی uint32_t __syscalls_flash_start__[];
        بیرونی uint32_t __syscalls_flash_end__[];
    #endif /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) ) */

    /* The stack contains: r0, r1, r2, r3, r12, LR, PC and xPSR. The first
     * argument (r0) is pulParam[ 0 ]. */
    ulPC = pulParam[ portOFFSET_TO_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    انتخاب( ucSVCNumber )
    {
        حالت portSVC_START_SCHEDULER:
            vPortRestoreContextOfFirstTask();
            بشکن;

        حالت portSVC_YIELD:
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;

            /* Barriers are normally not required
             * but do ensure the code is completely
             * within the specified behaviour for the
             * architecture. */
            __asm فرار ( "dsb" ::: "memory" );
            __asm فرار ( "isb" );

            بشکن;

    #اگر ( configUSE_MPU_WRAPPERS_V1 == 1 )
        #اگر ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 )
            حالت portSVC_RAISE_PRIVILEGE: /* Only raise the privilege, if the
                                           * svc was raised from any of the
                                           * system calls. */

                اگر( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                    ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
                {
                    __asm فرار
                    (
                        "   mrs r1, control     \n" /* Obtain current control value. */
                        "   bic r1, r1, #1      \n" /* Set privilege bit. */
                        "   msr control, r1     \n" /* Write back new control value. */
                        ::: "r1", "memory"
                    );
                }

                بشکن;
        #وگرنه /* if ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
            حالت portSVC_RAISE_PRIVILEGE:
                __asm فرار
                (
                    "   mrs r1, control     \n" /* Obtain current control value. */
                    "   bic r1, r1, #1      \n" /* Set privilege bit. */
                    "   msr control, r1     \n" /* Write back new control value. */
                    ::: "r1", "memory"
                );
                بشکن;
        #endif /* #if( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
    #endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

        پیشفرض: /* Unknown SVC call. */
            بشکن;
    }
}
/*-----------------------------------------------------------*/

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

    تهی vSystemCallEnter( uint32_t * pul_Task_پشته,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_عدد ) /* PRIVILEGED_FUNCTION */
    {
        بیرونی TaskHandle_t pxCurrentTCB;
        بیرونی UBaseType_t uxSystemCallImplementations[ رقم_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_پشته;
        uint32_t ulHardwareSavedExceptionFrameSize, ulSystemCallLocation, i;

        #اگر defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            بیرونی uint32_t * __syscalls_flash_start__;
            بیرونی uint32_t * __syscalls_flash_end__;
        #وگرنه
            /* Declaration when these variable are exported from linker scripts. */
            بیرونی uint32_t __syscalls_flash_start__[];
            بیرونی uint32_t __syscalls_flash_end__[];
        #endif /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_پشته[ portOFFSET_TO_PC ];
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
        اگر( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_پشته_Info.pul_Task_پشته == پوچ ) &&
            ( uxSystemCallImplementations[ uc_System_Call_عدد ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_پشته = pxMpuSettings->x_System_Call_پشته_Info.pul_System_Call_پشته;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            اگر( ( ulLR & port_EXC_RETURN_پشته_FRAME_TYPE_MASK ) == 0UL )
            {
                /* Extended frame i.e. FPU in use. */
                ulHardwareSavedExceptionFrameSize = 26;
                __asm فرار (
                    " vpush {s0}         \n" /* Trigger lazy stacking. */
                    " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                    ::: "memory"
                    );
            }
            وگرنه
            {
                /* Standard frame i.e. FPU not in use. */
                ulHardwareSavedExceptionFrameSize = 8;
            }

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_پشته = pul_System_Call_پشته - ulHardwareSavedExceptionFrameSize;

            /* Copy the stack frame. */
            برای( i = 0; i < ulHardwareSavedExceptionFrameSize; i++ )
            {
                pul_System_Call_پشته[ i ] = pul_Task_پشته[ i ];
            }

            /* Use the pulSystemCallStack in thread mode. */
            __asm فرار ( "msr psp, %0" : : "r" ( pul_System_Call_پشته ) );

            /* Raise the privilege for the duration of the system call. */
            __asm فرار (
                " mrs r1, control     \n" /* Obtain current control value. */
                " bic r1, #1          \n" /* Clear nPRIV bit. */
                " msr control, r1     \n" /* Write back new control value. */
                ::: "r1", "memory"
                );

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_پشته_Info.pul_Task_پشته = pul_Task_پشته + ulHardwareSavedExceptionFrameSize;

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_پشته_Info.ulLinkRegisterAtSystemCallEntry = pul_Task_پشته[ portOFFSET_TO_LR ];


            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_پشته[ portOFFSET_TO_PC ] = uxSystemCallImplementations[ uc_System_Call_عدد ];
            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_پشته[ portOFFSET_TO_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            اگر( ( pul_Task_پشته[ portOFFSET_TO_PSR ] & port_PSR_پشته_PADDING_MASK ) == port_PSR_پشته_PADDING_MASK )
            {
                pxMpuSettings->ulTaskFlags |= port_پشته_FRAME_HAS_PADDING_FLAG;
            }
            وگرنه
            {
                pxMpuSettings->ulTaskFlags &= ( ~port_پشته_FRAME_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_پشته[ portOFFSET_TO_PSR ] &= ( ~port_PSR_پشته_PADDING_MASK );
        }
    }

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

    تهی vRequestSystemCallExit( تهی ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm فرار ( "svc %0 \n" ::"i" ( portSVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

    تهی vSystemCallExit( uint32_t * pul_System_Call_پشته,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        بیرونی TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_پشته;
        uint32_t ulHardwareSavedExceptionFrameSize, ulSystemCallLocation, i;

        #اگر defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            بیرونی uint32_t * __privileged_functions_start__;
            بیرونی uint32_t * __privileged_functions_end__;
        #وگرنه
            /* Declaration when these variable are exported from linker scripts. */
            بیرونی uint32_t __privileged_functions_start__[];
            بیرونی uint32_t __privileged_functions_end__[];
        #endif /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_پشته[ portOFFSET_TO_PC ];
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
        اگر( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_پشته_Info.pul_Task_پشته != پوچ ) )
        {
            pul_Task_پشته = pxMpuSettings->x_System_Call_پشته_Info.pul_Task_پشته;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            اگر( ( ulLR & port_EXC_RETURN_پشته_FRAME_TYPE_MASK ) == 0UL )
            {
                /* Extended frame i.e. FPU in use. */
                ulHardwareSavedExceptionFrameSize = 26;
                __asm فرار (
                    " vpush {s0}         \n" /* Trigger lazy stacking. */
                    " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                    ::: "memory"
                    );
            }
            وگرنه
            {
                /* Standard frame i.e. FPU not in use. */
                ulHardwareSavedExceptionFrameSize = 8;
            }

            /* Make space on the task stack for the stack frame. */
            pul_Task_پشته = pul_Task_پشته - ulHardwareSavedExceptionFrameSize;

            /* Copy the stack frame. */
            برای( i = 0; i < ulHardwareSavedExceptionFrameSize; i++ )
            {
                pul_Task_پشته[ i ] = pul_System_Call_پشته[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm فرار ( "msr psp, %0" : : "r" ( pul_Task_پشته ) );

            /* Drop the privilege before returning to the thread mode. */
            __asm فرار (
                " mrs r1, control     \n" /* Obtain current control value. */
                " orr r1, #1          \n" /* Set nPRIV bit. */
                " msr control, r1     \n" /* Write back new control value. */
                ::: "r1", "memory"
                );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_پشته[ portOFFSET_TO_PC ] = pxMpuSettings->x_System_Call_پشته_Info.ulLinkRegisterAtSystemCallEntry;
            /* Ensure that LR has a valid value.*/
            pul_Task_پشته[ portOFFSET_TO_LR ] = pxMpuSettings->x_System_Call_پشته_Info.ulLinkRegisterAtSystemCallEntry;

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            اگر( ( pxMpuSettings->ulTaskFlags & port_پشته_FRAME_HAS_PADDING_FLAG ) == port_پشته_FRAME_HAS_PADDING_FLAG )
            {
                pul_Task_پشته[ portOFFSET_TO_PSR ] |= port_PSR_پشته_PADDING_MASK;
            }
            وگرنه
            {
                pul_Task_پشته[ portOFFSET_TO_PSR ] &= ( ~port_PSR_پشته_PADDING_MASK );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_پشته_Info.pul_Task_پشته = پوچ;
        }
    }

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

BaseType_t xPortIsTaskPrivileged( تهی ) /* PRIVILEGED_FUNCTION */
{
    BaseType_t xTaskIsPrivileged = pdFALSE;
    ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( پوچ ); /* Calling task's MPU settings. */

    اگر( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
    {
        xTaskIsPrivileged = pdTRUE;
    }

    بازگشت xTaskIsPrivileged;
}
/*-----------------------------------------------------------*/

تهی vPortSwitchToUserMode( تهی )
{
    /* Load the current task's MPU settings from its TCB. */
    xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( پوچ );

    /* Mark the task as unprivileged. */
    xTaskMpuSettings->ulTaskFlags &= ( ~( portTASK_IS_PRIVILEGED_FLAG ) );

    /* Lower the processor's privilege level. */
    vResetPrivilege();
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( تهی )
{
    /* Errata 837070 workaround must only be enabled on Cortex-M7 r0p0
     * and r0p1 cores. */
    #اگر ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        configASSERT( ( portCPUID == portCORTEX_M7_r0p1_ID ) || ( portCPUID == portCORTEX_M7_r0p0_ID ) );
    #وگرنه

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
    #اگر ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        ثابت portISR_t * ثابت pxVectorTable = portSCB_VTOR_REG;

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

    #اگر ( configASSERT_DEFINED == 1 )
    {
        فرار uint8_t ucOriginalPriority;
        فرار uint32_t ulImplementedPrioBits = 0;
        فرار uint8_t * ثابت pucFirstUserPriorityRegister = ( فرار uint8_t * ثابت ) ( portNVIC_IP_REGISTERS_OFFSET_16 + port_FIRST_USER_INTERRUPT_عدد );
        فرار uint8_t uc_Max_Priority_مقدار;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
         * functions can be called.  ISR safe functions are those that end in
         * "FromISR".  FreeRTOS maintains separate thread and ISR API functions to
         * ensure interrupt entry is as fast and simple as possible.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        ucOriginalPriority = *pucFirstUserPriorityRegister;

        /* Determine the number of priority bits available.  First write to all
         * possible bits. */
        *pucFirstUserPriorityRegister = port_MAX_8_BIT_مقدار;

        /* Read the value back to see how many bits stuck. */
        uc_Max_Priority_مقدار = *pucFirstUserPriorityRegister;

        /* Use the same mask on the maximum system call priority. */
        ucMaxSysCallPriority = configMAX_SYSCALL_INTERRUPT_PRIORITY & uc_Max_Priority_مقدار;

        /* Check that the maximum system call priority is nonzero after
         * accounting for the number of priority bits supported by the
         * hardware. A priority of 0 is invalid because setting the BASEPRI
         * register to 0 unmasks all interrupts, and interrupts with priority 0
         * cannot be masked using BASEPRI.
         * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( ucMaxSysCallPriority );

        /* Check that the bits not implemented in hardware are zero in
         * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( configMAX_SYSCALL_INTERRUPT_PRIORITY & ( uint8_t ) ( ~( uint32_t ) uc_Max_Priority_مقدار ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
         * of bits read back. */

        وقتی( ( uc_Max_Priority_مقدار & port_بالاترین_BIT_OF_BYTE ) == port_بالاترین_BIT_OF_BYTE )
        {
            ulImplementedPrioBits++;
            uc_Max_Priority_مقدار <<= ( uint8_t ) 0x01;
        }

        اگر( ulImplementedPrioBits == 8 )
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
        وگرنه
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

    #اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        xSchedulerRunning = pdTRUE;
    }
    #endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    /* Ensure the VFP is enabled - it should be anyway. */
    vPortEnableVFP();

    /* Lazy save always. */
    *( portFPCCR ) |= portASPEN_AND_LSPEN_BITS;

    /* Start the first task. */
    vPortStartFirstTask();

    /* Should not get here! */
    بازگشت 0;
}
/*-----------------------------------------------------------*/

تهی vPortEndScheduler( تهی )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

تهی vPortEnterCritical( تهی )
{
    #اگر ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        اگر( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            portDISABLE_INTERRUPTS();
            uxCriticalNesting++;

            /* This is not the interrupt safe version of the enter critical function so
             * assert() if it is being called from an interrupt context.  Only API
             * functions that end in "FromISR" can be used in an interrupt.  Only assert if
             * the critical nesting count is 1 to protect against recursive calls if the
             * assert function also uses a critical section. */
            اگر( uxCriticalNesting == 1 )
            {
                configASSERT( ( portNVIC_INT_CTRL_REG & portVECTACTIVE_MASK ) == 0 );
            }

            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        وگرنه
        {
            portDISABLE_INTERRUPTS();
            uxCriticalNesting++;

            /* This is not the interrupt safe version of the enter critical function so
             * assert() if it is being called from an interrupt context.  Only API
             * functions that end in "FromISR" can be used in an interrupt.  Only assert if
             * the critical nesting count is 1 to protect against recursive calls if the
             * assert function also uses a critical section. */
            اگر( uxCriticalNesting == 1 )
            {
                configASSERT( ( portNVIC_INT_CTRL_REG & portVECTACTIVE_MASK ) == 0 );
            }
        }
    #وگرنه /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        portDISABLE_INTERRUPTS();
        uxCriticalNesting++;

        /* This is not the interrupt safe version of the enter critical function so
         * assert() if it is being called from an interrupt context.  Only API
         * functions that end in "FromISR" can be used in an interrupt.  Only assert if
         * the critical nesting count is 1 to protect against recursive calls if the
         * assert function also uses a critical section. */
        اگر( uxCriticalNesting == 1 )
        {
            configASSERT( ( portNVIC_INT_CTRL_REG & portVECTACTIVE_MASK ) == 0 );
        }
    #endif /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

تهی vPortExitCritical( تهی )
{
    #اگر ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        اگر( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            اگر( uxCriticalNesting == 0 )
            {
                portENABLE_INTERRUPTS();
            }

            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        وگرنه
        {
            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            اگر( uxCriticalNesting == 0 )
            {
                portENABLE_INTERRUPTS();
            }
        }
    #وگرنه /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        configASSERT( uxCriticalNesting );
        uxCriticalNesting--;

        اگر( uxCriticalNesting == 0 )
        {
            portENABLE_INTERRUPTS();
        }
    #endif /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

تهی xPortSysTickHandler( تهی )
{
    /* The SysTick runs at the lowest interrupt priority, so when this interrupt
     * executes all interrupts must be unmasked.  There is therefore no need to
     * save and then restore the interrupt mask value as its value is already
     * known. */
    portDISABLE_INTERRUPTS();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        اگر( xTaskIncrementTick() != pdFALSE )
        {
            traceISR_EXIT_TO_SCHEDULER();

            /* A context switch is required.  Context switching is performed in
             * the PendSV interrupt.  Pend the PendSV interrupt. */
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;
        }
        وگرنه
        {
            traceISR_EXIT();
        }
    }
    portENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__weak تهی vPortSetupTimerInterrupt( تهی )
{
    /* Stop and clear the SysTick. */
    portNVIC_SYSTICK_CTRL_REG = 0UL;
    port_NVIC_SYSTICK_CURRENT_مقدار_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    portNVIC_SYSTICK_LOAD_REG = ( configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL;
    portNVIC_SYSTICK_CTRL_REG = ( portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT );
}
/*-----------------------------------------------------------*/

ایستا تهی prvSetupMPU( تهی )
{
    بیرونی uint32_t __privileged_functions_start__[];
    بیرونی uint32_t __privileged_functions_end__[];
    بیرونی uint32_t __FLASH_segment_start__[];
    بیرونی uint32_t __FLASH_segment_end__[];
    بیرونی uint32_t __privileged_data_start__[];
    بیرونی uint32_t __privileged_data_end__[];

    /* The only permitted number of regions are 8 or 16. */
    configASSERT( ( configTOTAL_MPU_REGIONS == 8 ) || ( configTOTAL_MPU_REGIONS == 16 ) );

    /* Ensure that the configTOTAL_MPU_REGIONS is configured correctly. */
    configASSERT( portMPU_TYPE_REG == port_EXPECTED_MPU_TYPE_مقدار );

    /* Check the expected MPU is present. */
    اگر( portMPU_TYPE_REG == port_EXPECTED_MPU_TYPE_مقدار )
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

ایستا uint32_t prvGetMPURegionSizeSetting( uint32_t ulActualSizeInBytes )
{
    uint32_t ulRegionSize, ul_Return_مقدار = 4;

    /* 32 is the smallest region size, 31 is the largest valid value for
     * ulReturnValue. */
    برای( ulRegionSize = 32UL; ul_Return_مقدار < 31UL; ( ulRegionSize <<= 1UL ) )
    {
        اگر( ulActualSizeInBytes <= ulRegionSize )
        {
            بشکن;
        }
        وگرنه
        {
            ul_Return_مقدار++;
        }
    }

    /* Shift the code by one before returning so it can be written directly
     * into the correct bit position of the attribute register. */
    بازگشت( ul_Return_مقدار << 1UL );
}
/*-----------------------------------------------------------*/

تهی vPortStoreTaskMPUSettings( xMPU_SETTINGS * xMPUSettings,
                                ثابت ساختار xMEMORY_REGION * ثابت xRegions,
                                پشته_Type_t * px_Bottom_Of_پشته,
                                config_پشته_DEPTH_TYPE ux_پشته_Depth )
{
    بیرونی uint32_t __SRAM_segment_start__[];
    بیرونی uint32_t __SRAM_segment_end__[];
    بیرونی uint32_t __privileged_data_start__[];
    بیرونی uint32_t __privileged_data_end__[];
    int32_t lIndex;
    uint32_t ul;

    اگر( xRegions == پوچ )
    {
        /* No MPU regions are specified so allow access to all RAM. */
        xMPUSettings->xRegion[ 0 ].ulRegionBaseAddress =
            ( ( uint32_t ) __SRAM_segment_start__ ) | /* Base address. */
            ( portMPU_REGION_VALID ) |
            ( port_پشته_REGION );                     /* Region number. */

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
        برای( ul = 1UL; ul <= port_رقم_CONFIGURABLE_REGIONS; ul++ )
        {
            xMPUSettings->xRegion[ ul ].ulRegionBaseAddress = ( ( ul - 1UL ) | portMPU_REGION_VALID );
            xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ulRegionStartAddress = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ulRegionEndAddress = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
        }
    }
    وگرنه
    {
        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid.  At all other
         * times the stack parameters will not be valid and it is assumed that the
         * stack region has already been configured. */
        اگر( ux_پشته_Depth > 0 )
        {
            /* Define the region that allows access to the stack. */
            xMPUSettings->xRegion[ 0 ].ulRegionBaseAddress =
                ( ( uint32_t ) px_Bottom_Of_پشته ) |
                ( portMPU_REGION_VALID ) |
                ( port_پشته_REGION ); /* Region number. */

            xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
                ( portMPU_REGION_READ_WRITE ) |
                ( portMPU_REGION_EXECUTE_NEVER ) |
                ( prvGetMPURegionSizeSetting( ux_پشته_Depth * ( config_پشته_DEPTH_TYPE ) اندازه( پشته_Type_t ) ) ) |
                ( ( configTEX_S_C_B_SRAM & portMPU_RASR_TEX_S_C_B_MASK ) << portMPU_RASR_TEX_S_C_B_LOCATION ) |
                ( portMPU_REGION_ENABLE );

            xMPUSettings->xRegionSettings[ 0 ].ulRegionStartAddress = ( uint32_t ) px_Bottom_Of_پشته;
            xMPUSettings->xRegionSettings[ 0 ].ulRegionEndAddress = ( uint32_t ) ( ( uint32_t ) ( px_Bottom_Of_پشته ) +
                                                                                   ( ux_پشته_Depth * ( config_پشته_DEPTH_TYPE ) اندازه( پشته_Type_t ) ) - 1UL );
            xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                       tskMPU_WRITE_PERMISSION );
        }

        lIndex = 0;

        برای( ul = 1UL; ul <= port_رقم_CONFIGURABLE_REGIONS; ul++ )
        {
            اگر( ( xRegions[ lIndex ] ).ulLengthInBytes > 0UL )
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

                اگر( ( ( xRegions[ lIndex ].ulParameters & portMPU_REGION_READ_ONLY ) == portMPU_REGION_READ_ONLY ) ||
                    ( ( xRegions[ lIndex ].ulParameters & portMPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) == portMPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = tskMPU_READ_PERMISSION;
                }

                اگر( ( xRegions[ lIndex ].ulParameters & portMPU_REGION_READ_WRITE ) == portMPU_REGION_READ_WRITE )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
                }
            }
            وگرنه
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

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

    BaseType_t xPortIsAuthorizedToAccessBuffer( ثابت تهی * pvBuffer,
                                                size_t xBufferLength,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ulBufferStartAddress, ulBufferEndAddress;
        BaseType_t xAccessGranted = pdFALSE;
        ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( پوچ ); /* Calling task's MPU settings. */

        اگر( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        وگرنه اگر( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        وگرنه
        {
            اگر( portADD_UINT32_WILL_OVERFLOW( ( ( uint32_t ) pvBuffer ), ( ( uint32_t ) xBufferLength - 1UL ) ) == pdFALSE )
            {
                ulBufferStartAddress = ( uint32_t ) pvBuffer;
                ulBufferEndAddress = ( ( ( uint32_t ) pvBuffer ) + ( uint32_t ) xBufferLength - 1UL );

                برای( i = 0; i < port_TOTAL_رقم_REGIONS_IN_TCB; i++ )
                {
                    اگر( portIS_ADDRESS_WITHIN_RANGE( ulBufferStartAddress,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ulRegionStartAddress,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ulRegionEndAddress ) &&
                        portIS_ADDRESS_WITHIN_RANGE( ulBufferEndAddress,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ulRegionStartAddress,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ulRegionEndAddress ) &&
                        portIS_AUTHORIZED( ulAccessRequested, xTaskMpuSettings->xRegionSettings[ i ].ulRegionPermissions ) )
                    {
                        xAccessGranted = pdTRUE;
                        بشکن;
                    }
                }
            }
        }

        بازگشت xAccessGranted;
    }

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/


#اگر ( configASSERT_DEFINED == 1 )

    تهی vPortValidateInterruptPriority( تهی )
    {
        uint32_t ulCurrentInterrupt;
        uint8_t ucCurrentPriority;

        /* Obtain the number of the currently executing interrupt. */
        __asm فرار ( "mrs %0, ipsr" : "=r" ( ulCurrentInterrupt )::"memory" );

        /* Is the interrupt number a user defined interrupt? */
        اگر( ulCurrentInterrupt >= port_FIRST_USER_INTERRUPT_عدد )
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

#اگر ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    تهی vPortGrantAccessToKernelObject( TaskHandle_t xInternalTaskHandle,
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

#اگر ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    تهی vPortRevokeAccessToKernelObject( TaskHandle_t xInternalTaskHandle,
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

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #اگر ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        BaseType_t xPortIsAuthorizedToAccessKernelObject( int32_t lInternalIndexOfKernelObject ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulAccessControlListEntryIndex, ulAccessControlListEntryBit;
            BaseType_t xAccessGranted = pdFALSE;
            ثابت xMPU_SETTINGS * xTaskMpuSettings;

            اگر( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            وگرنه
            {
                xTaskMpuSettings = xTaskGetMPUSettings( پوچ ); /* Calling task's MPU settings. */

                ulAccessControlListEntryIndex = ( ( uint32_t ) lInternalIndexOfKernelObject / portACL_ENTRY_SIZE_BITS );
                ulAccessControlListEntryBit = ( ( uint32_t ) lInternalIndexOfKernelObject % portACL_ENTRY_SIZE_BITS );

                اگر( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                وگرنه
                {
                    اگر( ( xTaskMpuSettings->ulAccessControlList[ ulAccessControlListEntryIndex ] & ( 1U << ulAccessControlListEntryBit ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            بازگشت xAccessGranted;
        }

    #وگرنه /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        BaseType_t xPortIsAuthorizedToAccessKernelObject( int32_t lInternalIndexOfKernelObject ) /* PRIVILEGED_FUNCTION */
        {
            ( تهی ) lInternalIndexOfKernelObject;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            بازگشت pdTRUE;
        }

    #endif /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/
