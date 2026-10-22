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
#અન્તર્ભાવ "FreeRTOS.h"
#અન્તર્ભાવ "task.h"
#અન્તર્ભાવ "mpu_syscall_numbers.h"

#ifndef __TARGET_FPU_VFP
    #error This port can only be used when the project options are configured to enable hardware floating point support.
#endif

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Unprivileged critical sections are not supported when using MPU wrappers
 * version 2. Default the option to 0 and reject an explicit value of 1. */
#ifndef configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS
    #જો ( configUSE_MPU_WRAPPERS_V1 == 0 )
        #define configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    0
    #નહીંતર
        #warning "configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not defined. We recommend defining it to 0 in FreeRTOSConfig.h for better security."
        #define configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    1
    #endif
#નહીંતર
    #જો ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) )
        #error configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not supported with MPU wrappers version 2 ( configUSE_MPU_WRAPPERS_V1 == 0 ).
    #endif
#endif

/* Prototype of all Interrupt Service Routines (ISRs). */
પ્રકારવ્યાખ્યા શૂન્ય ( * portISR_t )( શૂન્ય );

/* Constants required to access and manipulate the NVIC. */
#define portNVIC_SYSTICK_CTRL_REG                 ( *( ( અસ્થિર uint32_t * ) 0xe000e010 ) )
#define portNVIC_SYSTICK_LOAD_REG                 ( *( ( અસ્થિર uint32_t * ) 0xe000e014 ) )
#define port_NVIC_SYSTICK_CURRENT_કિંમત_REG        ( *( ( અસ્થિર uint32_t * ) 0xe000e018 ) )
#define portNVIC_SHPR3_REG                        ( *( ( અસ્થિર uint32_t * ) 0xe000ed20 ) )
#define portNVIC_SHPR2_REG                        ( *( ( અસ્થિર uint32_t * ) 0xe000ed1c ) )
#define portNVIC_SYS_CTRL_STATE_REG               ( *( ( અસ્થિર uint32_t * ) 0xe000ed24 ) )
#define portNVIC_MEM_FAULT_ENABLE                 ( 1UL << 16UL )

/* Constants used to detect Cortex-M7 r0p0 and r0p1 cores, and ensure
 * that a work around is active for errata 837070. */
#define portCPUID                                 ( *( ( અસ્થિર uint32_t * ) 0xE000ed00 ) )
#define portCORTEX_M7_r0p1_ID                     ( 0x410FC271UL )
#define portCORTEX_M7_r0p0_ID                     ( 0x410FC270UL )

/* Constants required to access and manipulate the MPU. */
#define portMPU_TYPE_REG                          ( *( ( અસ્થિર uint32_t * ) 0xe000ed90 ) )
#define portMPU_REGION_BASE_ADDRESS_REG           ( *( ( અસ્થિર uint32_t * ) 0xe000ed9C ) )
#define portMPU_REGION_ATTRIBUTE_REG              ( *( ( અસ્થિર uint32_t * ) 0xe000edA0 ) )
#define portMPU_CTRL_REG                          ( *( ( અસ્થિર uint32_t * ) 0xe000ed94 ) )
#define port_EXPECTED_MPU_TYPE_કિંમત               ( configTOTAL_MPU_REGIONS << 8UL )
#define portMPU_ENABLE                            ( 0x01UL )
#define portMPU_BACKGROUND_ENABLE                 ( 1UL << 2UL )
#define portPRIVILEGED_EXECUTION_START_ADDRESS    ( 0UL )
#define portMPU_REGION_VALID                      ( 0x10UL )
#define portMPU_REGION_ENABLE                     ( 0x01UL )
#define portPERIPHERALS_START_ADDRESS             0x40000000UL
#define portPERIPHERALS_END_ADDRESS               0x5FFFFFFFUL

/* Constants required to access and manipulate the SysTick and other FreeRTOS
 * interrupts. */
#define portNVIC_SYSTICK_CLK                      ( 0x00000004UL )
#define portNVIC_SYSTICK_INT                      ( 0x00000002UL )
#define portNVIC_SYSTICK_ENABLE                   ( 0x00000001UL )
#define portMIN_INTERRUPT_PRIORITY                ( 255UL )
#define portNVIC_PENDSV_PRI                       ( ( ( uint32_t ) portMIN_INTERRUPT_PRIORITY ) << 16UL )
#define portNVIC_SYSTICK_PRI                      ( ( ( uint32_t ) portMIN_INTERRUPT_PRIORITY ) << 24UL )
#define portNVIC_SVC_PRI                          ( ( ( uint32_t ) configMAX_SYSCALL_INTERRUPT_PRIORITY - 1UL ) << 24UL )

/* Constants required to manipulate the VFP. */
#define portFPCCR                                 ( ( અસ્થિર uint32_t * ) 0xe000ef34UL ) /* Floating point context control register. */
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
#define port_FIRST_USER_INTERRUPT_સંખ્યા           ( 16 )
#define portNVIC_IP_REGISTERS_OFFSET_16           ( 0xE000E3F0 )
#define portAIRCR_REG                             ( *( ( અસ્થિર uint32_t * ) 0xE000ED0C ) )
#define port_MAX_8_BIT_કિંમત                       ( ( uint8_t ) 0xff )
#define port_ટોચ_BIT_OF_BYTE                       ( ( uint8_t ) 0x80 )
#define portMAX_PRIGROUP_BITS                     ( ( uint8_t ) 7 )
#define portPRIORITY_GROUP_MASK                   ( 0x07UL << 8UL )
#define portPRIGROUP_SHIFT                        ( 8UL )

/* Constants used during system call enter and exit. */
#define port_PSR_ઢગલો_PADDING_MASK                ( 1UL << 9UL )
#define port_EXC_RETURN_ઢગલો_FRAME_TYPE_MASK      ( 1UL << 4UL )

/* Offsets in the stack to the parameters when inside the SVC handler. */
#define portOFFSET_TO_LR                          ( 5 )
#define portOFFSET_TO_PC                          ( 6 )
#define portOFFSET_TO_PSR                         ( 7 )

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#define portSTART_ADDRESS_MASK                    ( ( ઢગલો_Type_t ) 0xfffffffeUL )

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

/* Each task maintains its own interrupt status in the critical nesting
 * variable.  Note this is not saved as part of the task context as context
 * switches can only occur when uxCriticalNesting is zero. */
PRIVILEGED_DATA સ્થિર UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

#જો ( configUSE_MPU_WRAPPERS_V1 == 0 )

/*
 * This variable is set to pdTRUE when the scheduler is started.
 */
    PRIVILEGED_DATA સ્થિર BaseType_t xSchedulerRunning = pdFALSE;

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*
 * Setup the timer to generate the tick interrupts.
 */
શૂન્ય vSetupTimerInterrupt( શૂન્ય ) PRIVILEGED_FUNCTION;

/*
 * Configure a number of standard MPU regions that are used by all tasks.
 */
સ્થિર શૂન્ય prvSetupMPU( શૂન્ય ) PRIVILEGED_FUNCTION;

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
સ્થિર શૂન્ય prvStartFirstTask( શૂન્ય ) PRIVILEGED_FUNCTION;

/*
 * Return the smallest MPU region size that a given number of bytes will fit
 * into.  The region size is returned as the value that should be programmed
 * into the region attribute register for that region.
 */
સ્થિર uint32_t prvGetMPURegionSizeSetting( uint32_t ulActualSizeInBytes ) PRIVILEGED_FUNCTION;

/*
 * Standard FreeRTOS exception handlers.
 */
શૂન્ય xPortPendSVHandler( શૂન્ય ) PRIVILEGED_FUNCTION;
શૂન્ય xPortSysTickHandler( શૂન્ય ) PRIVILEGED_FUNCTION;
શૂન્ય vPortSVCHandler( શૂન્ય ) PRIVILEGED_FUNCTION;

/*
 * Starts the scheduler by restoring the context of the first task to run.
 */
સ્થિર શૂન્ય prvRestoreContextOfFirstTask( શૂન્ય ) PRIVILEGED_FUNCTION;

/*
 * C portion of the SVC handler.  The SVC handler is split between an asm entry
 * and a C wrapper for simplicity of coding and maintenance.
 */
શૂન્ય vSVCHandler_C( uint32_t * pulRegisters ) __attribute__( ( used ) ) PRIVILEGED_FUNCTION;

/*
 * Function to enable the VFP.
 */
સ્થિર શૂન્ય vPortEnableVFP( શૂન્ય );

/*
 * Utility function.
 */
સ્થિર uint32_t prvPortGetIPSR( શૂન્ય );

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#જો ( configASSERT_DEFINED == 1 )
    સ્થિર uint8_t ucMaxSysCallPriority = 0;
    સ્થિર uint32_t ulMaxPRIGROUPValue = 0;
    સ્થિર અચલ અસ્થિર uint8_t * અચલ pcInterruptPriorityRegisters = ( અચલ uint8_t * ) portNVIC_IP_REGISTERS_OFFSET_16;
#endif /* configASSERT_DEFINED */

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
BaseType_t xIsPrivileged( શૂન્ય );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 *
 * Bit 0 of the CONTROL register defines the privilege level of Thread Mode.
 *  Bit[0] = 0 --> The processor is running privileged
 *  Bit[0] = 1 --> The processor is running unprivileged.
 */
શૂન્ય vResetPrivilege( શૂન્ય );

/**
 * @brief Make a task unprivileged.
 */
શૂન્ય vPortSwitchToUserMode( શૂન્ય );

/**
 * @brief Enter critical section.
 */
#જો ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    શૂન્ય vPortEnterCritical( શૂન્ય ) FREERTOS_SYSTEM_CALL;
#નહીંતર
    શૂન્ય vPortEnterCritical( શૂન્ય ) PRIVILEGED_FUNCTION;
#endif

/**
 * @brief Exit from critical section.
 */
#જો ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    શૂન્ય vPortExitCritical( શૂન્ય ) FREERTOS_SYSTEM_CALL;
#નહીંતર
    શૂન્ય vPortExitCritical( શૂન્ય ) PRIVILEGED_FUNCTION;
#endif

#જો ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Triggers lazy stacking of FPU registers.
 */
    સ્થિર શૂન્ય prvTriggerLazyStacking( શૂન્ય ) PRIVILEGED_FUNCTION;

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#જો ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the system call stack so that upon returning from
 * SVC, the system call stack is used.
 *
 * @param pulTaskStack The current SP when the SVC was raised.
 * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
 * @param ucSystemCallNumber The system call number of the system call.
 */
    શૂન્ય vSystemCallEnter( uint32_t * pul_Task_ઢગલો,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_સંખ્યા ) PRIVILEGED_FUNCTION;

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#જો ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Raise SVC for exiting from a system call.
 */
    શૂન્ય vRequestSystemCallExit( શૂન્ય ) PRIVILEGED_FUNCTION;

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#જો ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the task stack so that upon returning from
 * SVC, the task stack is used again.
 *
 * @param pulSystemCallStack The current SP when the SVC was raised.
 * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
 */
    શૂન્ય vSystemCallExit( uint32_t * pul_System_Call_ઢગલો,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
BaseType_t xPortIsTaskPrivileged( શૂન્ય ) PRIVILEGED_FUNCTION;
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ઢગલો_Type_t * px_Port_Initialise_ઢગલો( ઢગલો_Type_t * px_ટોચ_Of_ઢગલો,
                                     TaskFunction_t pxCode,
                                     શૂન્ય * pvParameters,
                                     BaseType_t xRunPrivileged,
                                     xMPU_SETTINGS * xMPUSettings )
{
    જો( xRunPrivileged == pdTRUE )
    {
        xMPUSettings->ulTaskFlags |= portTASK_IS_PRIVILEGED_FLAG;
        xMPUSettings->ulContext[ 0 ] = portINITIAL_CONTROL_IF_PRIVILEGED;
    }
    નહીંતર
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

    xMPUSettings->ulContext[ 10 ] = ( uint32_t ) ( px_ટોચ_Of_ઢગલો - 8 );                /* PSP with the hardware saved stack. */
    xMPUSettings->ulContext[ 11 ] = ( uint32_t ) pvParameters;                        /* r0. */
    xMPUSettings->ulContext[ 12 ] = 0x01010101;                                       /* r1. */
    xMPUSettings->ulContext[ 13 ] = 0x02020202;                                       /* r2. */
    xMPUSettings->ulContext[ 14 ] = 0x03030303;                                       /* r3. */
    xMPUSettings->ulContext[ 15 ] = 0x12121212;                                       /* r12. */
    xMPUSettings->ulContext[ 16 ] = 0;                                                /* LR. */
    xMPUSettings->ulContext[ 17 ] = ( ( uint32_t ) pxCode ) & portSTART_ADDRESS_MASK; /* PC. */
    xMPUSettings->ulContext[ 18 ] = portINITIAL_XPSR;                                 /* xPSR. */

    #જો ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        /* Ensure that the system call stack is double word aligned. */
        xMPUSettings->x_System_Call_ઢગલો_Info.pul_System_Call_ઢગલો = &( xMPUSettings->x_System_Call_ઢગલો_Info.ul_System_Call_ઢગલો_Buffer[ config_SYSTEM_CALL_ઢગલો_SIZE - 1 ] );
        xMPUSettings->x_System_Call_ઢગલો_Info.pul_System_Call_ઢગલો = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_ઢગલો_Info.pul_System_Call_ઢગલો ) &
                                                                                 ( uint32_t ) ( ~( portBYTE_ALIGNMENT_MASK ) ) );

        /* This is not NULL only for the duration of a system call. */
        xMPUSettings->x_System_Call_ઢગલો_Info.pul_Task_ઢગલો = ખાલી;
    }
    #endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    પાછા &( xMPUSettings->ulContext[ 19 ] );
}
/*-----------------------------------------------------------*/

શૂન્ય vSVCHandler_C( uint32_t * pulParam )
{
    uint8_t ucSVCNumber;
    uint32_t ulPC;

    #જો ( configUSE_MPU_WRAPPERS_V1 == 1 )
        uint32_t ulReg;
    #endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #જો ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) )
        બાહ્ય uint32_t __syscalls_flash_start__;
        બાહ્ય uint32_t __syscalls_flash_end__;
    #endif /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) ) */

    /* The stack contains: r0, r1, r2, r3, r12, LR, PC and xPSR. The first
     * argument (r0) is pulParam[ 0 ]. */
    ulPC = pulParam[ portOFFSET_TO_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    પસંદગી( ucSVCNumber )
    {
        સ્થિતિ portSVC_START_SCHEDULER:
            prvRestoreContextOfFirstTask();
            તોડો;

        સ્થિતિ portSVC_YIELD:
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;

            /* Barriers are normally not required
             * but do ensure the code is completely
             * within the specified behaviour for the
             * architecture. */
            __asm અસ્થિર ( "dsb" );
            __asm અસ્થિર ( "isb" );

            તોડો;

    #જો ( configUSE_MPU_WRAPPERS_V1 == 1 )
        #જો ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 )
            સ્થિતિ portSVC_RAISE_PRIVILEGE: /* Only raise the privilege, if the
                                           * svc was raised from any of the
                                           * system calls. */

                જો( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                    ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
                {
                    __asm
                    {
                        /* *INDENT-OFF* */
                        mrs ulReg, control /* Obtain current control value. */
                        bic ulReg, # 1     /* Set privilege bit. */
                        msr control, ulReg /* Write back new control value. */
                        /* *INDENT-ON* */
                    }
                }

                તોડો;
        #નહીંતર /* if ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
            સ્થિતિ portSVC_RAISE_PRIVILEGE:
                __asm
                {
                    /* *INDENT-OFF* */
                    mrs ulReg, control /* Obtain current control value. */
                    bic ulReg, # 1     /* Set privilege bit. */
                    msr control, ulReg /* Write back new control value. */
                    /* *INDENT-ON* */
                }
                તોડો;
        #endif /* #if( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
    #endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

        મૂળભૂત: /* Unknown SVC call. */
            તોડો;
    }
}
/*-----------------------------------------------------------*/

#જો ( configUSE_MPU_WRAPPERS_V1 == 0 )

    __asm શૂન્ય prvTriggerLazyStacking( શૂન્ય ) /* PRIVILEGED_FUNCTION */
    {
    /* *INDENT-OFF* */
        PRESERVE8

        vpush {s0} /* Trigger lazy stacking. */
        vpop  {s0} /* Nullify the affect of the above instruction. */

    /* *INDENT-ON* */
    }

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#જો ( configUSE_MPU_WRAPPERS_V1 == 0 )

    શૂન્ય vSystemCallEnter( uint32_t * pul_Task_ઢગલો,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_સંખ્યા ) /* PRIVILEGED_FUNCTION */
    {
        બાહ્ય TaskHandle_t pxCurrentTCB;
        બાહ્ય UBaseType_t uxSystemCallImplementations[ અંક_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_ઢગલો;
        uint32_t ulHardwareSavedExceptionFrameSize, ulSystemCallLocation, i, r1;
        બાહ્ય uint32_t __syscalls_flash_start__;
        બાહ્ય uint32_t __syscalls_flash_end__;

        ulSystemCallLocation = pul_Task_ઢગલો[ portOFFSET_TO_PC ];
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
        જો( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_ઢગલો_Info.pul_Task_ઢગલો == ખાલી ) &&
            ( uxSystemCallImplementations[ uc_System_Call_સંખ્યા ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_ઢગલો = pxMpuSettings->x_System_Call_ઢગલો_Info.pul_System_Call_ઢગલો;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            જો( ( ulLR & port_EXC_RETURN_ઢગલો_FRAME_TYPE_MASK ) == 0UL )
            {
                /* Extended frame i.e. FPU in use. */
                ulHardwareSavedExceptionFrameSize = 26;
                prvTriggerLazyStacking();
            }
            નહીંતર
            {
                /* Standard frame i.e. FPU not in use. */
                ulHardwareSavedExceptionFrameSize = 8;
            }

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_ઢગલો = pul_System_Call_ઢગલો - ulHardwareSavedExceptionFrameSize;

            /* Copy the stack frame. */
            માટે( i = 0; i < ulHardwareSavedExceptionFrameSize; i++ )
            {
                pul_System_Call_ઢગલો[ i ] = pul_Task_ઢગલો[ i ];
            }

            /* Use the pulSystemCallStack in thread mode. */
            __asm
            {
                msr psp, pul_System_Call_ઢગલો
            };

            /* Raise the privilege for the duration of the system call. */
            __asm
            {
                mrs r1, control /* Obtain current control value. */
                bic r1, # 1     /* Clear nPRIV bit. */
                msr control, r1 /* Write back new control value. */
            };

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_ઢગલો_Info.pul_Task_ઢગલો = pul_Task_ઢગલો + ulHardwareSavedExceptionFrameSize;

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_ઢગલો_Info.ulLinkRegisterAtSystemCallEntry = pul_Task_ઢગલો[ portOFFSET_TO_LR ];

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_ઢગલો[ portOFFSET_TO_PC ] = uxSystemCallImplementations[ uc_System_Call_સંખ્યા ];
            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_ઢગલો[ portOFFSET_TO_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            જો( ( pul_Task_ઢગલો[ portOFFSET_TO_PSR ] & port_PSR_ઢગલો_PADDING_MASK ) == port_PSR_ઢગલો_PADDING_MASK )
            {
                pxMpuSettings->ulTaskFlags |= port_ઢગલો_FRAME_HAS_PADDING_FLAG;
            }
            નહીંતર
            {
                pxMpuSettings->ulTaskFlags &= ( ~port_ઢગલો_FRAME_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_ઢગલો[ portOFFSET_TO_PSR ] &= ( ~port_PSR_ઢગલો_PADDING_MASK );
        }
    }

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#જો ( configUSE_MPU_WRAPPERS_V1 == 0 )

    __asm શૂન્ય vRequestSystemCallExit( શૂન્ય ) /* PRIVILEGED_FUNCTION */
    {
        PRESERVE8

        svc #portSVC_SYSTEM_CALL_EXIT
    }

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#જો ( configUSE_MPU_WRAPPERS_V1 == 0 )

    શૂન્ય vSystemCallExit( uint32_t * pul_System_Call_ઢગલો,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        બાહ્ય TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_ઢગલો;
        uint32_t ulHardwareSavedExceptionFrameSize, ulSystemCallLocation, i, r1;
        બાહ્ય uint32_t __privileged_functions_start__;
        બાહ્ય uint32_t __privileged_functions_end__;

        ulSystemCallLocation = pul_System_Call_ઢગલો[ portOFFSET_TO_PC ];
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
        જો( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_ઢગલો_Info.pul_Task_ઢગલો != ખાલી ) )
        {
            pul_Task_ઢગલો = pxMpuSettings->x_System_Call_ઢગલો_Info.pul_Task_ઢગલો;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            જો( ( ulLR & port_EXC_RETURN_ઢગલો_FRAME_TYPE_MASK ) == 0UL )
            {
                /* Extended frame i.e. FPU in use. */
                ulHardwareSavedExceptionFrameSize = 26;
                prvTriggerLazyStacking();
            }
            નહીંતર
            {
                /* Standard frame i.e. FPU not in use. */
                ulHardwareSavedExceptionFrameSize = 8;
            }

            /* Make space on the task stack for the stack frame. */
            pul_Task_ઢગલો = pul_Task_ઢગલો - ulHardwareSavedExceptionFrameSize;

            /* Copy the stack frame. */
            માટે( i = 0; i < ulHardwareSavedExceptionFrameSize; i++ )
            {
                pul_Task_ઢગલો[ i ] = pul_System_Call_ઢગલો[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm
            {
                msr psp, pul_Task_ઢગલો
            };

            /* Drop the privilege before returning to the thread mode. */
            __asm
            {
                mrs r1, control /* Obtain current control value. */
                orr r1, # 1     /* Set nPRIV bit. */
                msr control, r1 /* Write back new control value. */
            };

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_ઢગલો[ portOFFSET_TO_PC ] = pxMpuSettings->x_System_Call_ઢગલો_Info.ulLinkRegisterAtSystemCallEntry;
            /* Ensure that LR has a valid value.*/
            pul_Task_ઢગલો[ portOFFSET_TO_LR ] = pxMpuSettings->x_System_Call_ઢગલો_Info.ulLinkRegisterAtSystemCallEntry;

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            જો( ( pxMpuSettings->ulTaskFlags & port_ઢગલો_FRAME_HAS_PADDING_FLAG ) == port_ઢગલો_FRAME_HAS_PADDING_FLAG )
            {
                pul_Task_ઢગલો[ portOFFSET_TO_PSR ] |= port_PSR_ઢગલો_PADDING_MASK;
            }
            નહીંતર
            {
                pul_Task_ઢગલો[ portOFFSET_TO_PSR ] &= ( ~port_PSR_ઢગલો_PADDING_MASK );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_ઢગલો_Info.pul_Task_ઢગલો = ખાલી;
        }
    }

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

BaseType_t xPortIsTaskPrivileged( શૂન્ય ) /* PRIVILEGED_FUNCTION */
{
    BaseType_t xTaskIsPrivileged = pdFALSE;
    અચલ xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ખાલી ); /* Calling task's MPU settings. */

    જો( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
    {
        xTaskIsPrivileged = pdTRUE;
    }

    પાછા xTaskIsPrivileged;
}
/*-----------------------------------------------------------*/

#જો ( configUSE_MPU_WRAPPERS_V1 == 0 )

    __asm શૂન્ય vPortSVCHandler( શૂન્ય )
    {
        બાહ્ય vSVCHandler_C
        બાહ્ય vSystemCallEnter
        બાહ્ય vSystemCallExit

/* *INDENT-OFF* */
    PRESERVE8

    tst lr, #4
    ite eq
    mrseq r0, msp
    mrsne r0, psp

    ldr r1, [r0, #24]
    ldrb r2, [r1, #-2]
    cmp r2, #NUM_SYSTEM_CALLS
    blt syscall_enter
    cmp r2, #portSVC_SYSTEM_CALL_EXIT
    beq syscall_exit
    b vSVCHandler_C

syscall_enter
        mov r1, lr
        b vSystemCallEnter

syscall_exit
        mov r1, lr
        b vSystemCallExit
/* *INDENT-ON* */
    }

#નહીંતર /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    __asm શૂન્ય vPortSVCHandler( શૂન્ય )
    {
        બાહ્ય vSVCHandler_C

/* *INDENT-OFF* */
        PRESERVE8

    /* Assumes psp was in use. */
    #ifndef USE_PROCESS_ઢગલો   /* Code should not be required if a main() is using the process stack. */
        tst lr, # 4
        ite eq
        mrseq r0, msp
        mrsne r0, psp
    #નહીંતર
        mrs r0, psp
    #endif

    b vSVCHandler_C
/* *INDENT-ON* */
    }

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

__asm શૂન્ય prvRestoreContextOfFirstTask( શૂન્ય )
{
/* *INDENT-OFF* */
    PRESERVE8

    ldr r0, =0xE000ED08         /* Use the NVIC offset register to locate the stack. */
    ldr r0, [r0]
    ldr r0, [r0]
    msr msp, r0                 /* Set the msp back to the start of the stack. */

    /*------------ Program MPU. ------------ */
    ldr r3, =pxCurrentTCB       /* r3 = &( pxCurrentTCB ). */
    ldr r2, [r3]                /* r2 = pxCurrentTCB. */
    add r2, r2, #4              /* r2 = Second item in the TCB which is xMPUSettings. */

    dmb                         /* Complete outstanding transfers before disabling MPU. */
    ldr r0, =0xe000ed94         /* MPU_CTRL register. */
    ldr r3, [r0]                /* Read the value of MPU_CTRL. */
    bic r3, r3, # 1             /* r3 = r3 & ~1 i.e. Clear the bit 0 in r3. */
    str r3, [r0]                /* Disable MPU. */

    ldr r0, =0xe000ed9c         /* Region Base Address register. */
    ldmia r2!, {r4-r11}         /* Read 4 sets of MPU registers [MPU Region # 0 - 3]. */
    stmia r0, {r4-r11}          /* Write 4 sets of MPU registers [MPU Region # 0 - 3]. */

    #જો ( configTOTAL_MPU_REGIONS == 16 )
        ldmia r2!, {r4-r11}     /* Read 4 sets of MPU registers [MPU Region # 4 - 7]. */
        stmia r0, {r4-r11}      /* Write 4 sets of MPU registers. [MPU Region # 4 - 7]. */
        ldmia r2!, {r4-r11}     /* Read 4 sets of MPU registers [MPU Region # 8 - 11]. */
        stmia r0, {r4-r11}      /* Write 4 sets of MPU registers. [MPU Region # 8 - 11]. */
    #endif /* configTOTAL_MPU_REGIONS == 16. */

    ldr r0, =0xe000ed94         /* MPU_CTRL register. */
    ldr r3, [r0]                /* Read the value of MPU_CTRL. */
    orr r3, r3, #1              /* r3 = r3 | 1 i.e. Set the bit 0 in r3. */
    str r3, [r0]                /* Enable MPU. */
    dsb                         /* Force memory writes before continuing. */

    /*---------- Restore Context. ---------- */
    ldr r3, =pxCurrentTCB       /* r3 = &( pxCurrentTCB ). */
    ldr r2, [r3]                /* r2 = pxCurrentTCB. */
    ldr r1, [r2]                /* r1 = Location of saved context in TCB. */

    ldmdb r1!, {r0, r4-r11}     /* r0 contains PSP after the hardware had saved context. r4-r11 contain hardware saved context. */
    msr psp, r0
    stmia r0, {r4-r11}          /* Copy the hardware saved context on the task stack. */
    ldmdb r1!, {r3-r11, lr}     /* r3 contains CONTROL register. r4-r11 and LR restored. */
    msr control, r3
    str r1, [r2]                /* Save the location where the context should be saved next as the first member of TCB. */

    mov r0, #0
    msr basepri, r0
    bx lr
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( શૂન્ય )
{
    /* configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to 0.
     * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
    configASSERT( configMAX_SYSCALL_INTERRUPT_PRIORITY );

    /* Errata 837070 workaround must only be enabled on Cortex-M7 r0p0
     * and r0p1 cores. */
    #જો ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        configASSERT( ( portCPUID == portCORTEX_M7_r0p1_ID ) || ( portCPUID == portCORTEX_M7_r0p0_ID ) );
    #નહીંતર

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
    #જો ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        અચલ portISR_t * અચલ pxVectorTable = portSCB_VTOR_REG;

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

    #જો ( configASSERT_DEFINED == 1 )
    {
        અસ્થિર uint8_t ucOriginalPriority;
        અસ્થિર uint32_t ulImplementedPrioBits = 0;
        અસ્થિર uint8_t * અચલ pucFirstUserPriorityRegister = ( uint8_t * ) ( portNVIC_IP_REGISTERS_OFFSET_16 + port_FIRST_USER_INTERRUPT_સંખ્યા );
        અસ્થિર uint8_t uc_Max_Priority_કિંમત;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
         * functions can be called.  ISR safe functions are those that end in
         * "FromISR".  FreeRTOS maintains separate thread and ISR API functions to
         * ensure interrupt entry is as fast and simple as possible.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        ucOriginalPriority = *pucFirstUserPriorityRegister;

        /* Determine the number of priority bits available.  First write to all
         * possible bits. */
        *pucFirstUserPriorityRegister = port_MAX_8_BIT_કિંમત;

        /* Read the value back to see how many bits stuck. */
        uc_Max_Priority_કિંમત = *pucFirstUserPriorityRegister;

        /* Use the same mask on the maximum system call priority. */
        ucMaxSysCallPriority = configMAX_SYSCALL_INTERRUPT_PRIORITY & uc_Max_Priority_કિંમત;

        /* Check that the maximum system call priority is nonzero after
         * accounting for the number of priority bits supported by the
         * hardware. A priority of 0 is invalid because setting the BASEPRI
         * register to 0 unmasks all interrupts, and interrupts with priority 0
         * cannot be masked using BASEPRI.
         * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( ucMaxSysCallPriority );

        /* Check that the bits not implemented in hardware are zero in
         * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( configMAX_SYSCALL_INTERRUPT_PRIORITY & ( ~uc_Max_Priority_કિંમત ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
         * of bits read back. */

        જ્યારે( ( uc_Max_Priority_કિંમત & port_ટોચ_BIT_OF_BYTE ) == port_ટોચ_BIT_OF_BYTE )
        {
            ulImplementedPrioBits++;
            uc_Max_Priority_કિંમત <<= ( uint8_t ) 0x01;
        }

        જો( ulImplementedPrioBits == 8 )
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
        નહીંતર
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
    vSetupTimerInterrupt();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    #જો ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        xSchedulerRunning = pdTRUE;
    }
    #endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    /* Ensure the VFP is enabled - it should be anyway. */
    vPortEnableVFP();

    /* Lazy save always. */
    *( portFPCCR ) |= portASPEN_AND_LSPEN_BITS;

    /* Start the first task. */
    prvStartFirstTask();

    /* Should not get here! */
    પાછા 0;
}
/*-----------------------------------------------------------*/

__asm શૂન્ય prvStartFirstTask( શૂન્ય )
{
/* *INDENT-OFF* */
    PRESERVE8

    /* Use the NVIC offset register to locate the stack. */
    ldr r0, =0xE000ED08
    ldr r0, [ r0 ]
    ldr r0, [ r0 ]
    /* Set the msp back to the start of the stack. */
    msr msp, r0

    /* Clear the bit that indicates the FPU is in use in case the FPU was used
     * before the scheduler was started - which would otherwise result in the
     * unnecessary leaving of space in the SVC stack for lazy saving of FPU
     * registers. */
    mov r0, #0
    msr control, r0
    /* Globally enable interrupts. */
    cpsie i
    cpsie f
    dsb
    isb
    svc portSVC_START_SCHEDULER /* System call to start first task. */
    nop
    nop
/* *INDENT-ON* */
}

શૂન્ય vPortEndScheduler( શૂન્ય )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

શૂન્ય vPortEnterCritical( શૂન્ય )
{
    #જો ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        જો( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            portDISABLE_INTERRUPTS();
            uxCriticalNesting++;
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        નહીંતર
        {
            portDISABLE_INTERRUPTS();
            uxCriticalNesting++;
        }
    #નહીંતર /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        portDISABLE_INTERRUPTS();
        uxCriticalNesting++;
    #endif /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

શૂન્ય vPortExitCritical( શૂન્ય )
{
    #જો ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        જો( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            જો( uxCriticalNesting == 0 )
            {
                portENABLE_INTERRUPTS();
            }

            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        નહીંતર
        {
            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            જો( uxCriticalNesting == 0 )
            {
                portENABLE_INTERRUPTS();
            }
        }
    #નહીંતર /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        configASSERT( uxCriticalNesting );
        uxCriticalNesting--;

        જો( uxCriticalNesting == 0 )
        {
            portENABLE_INTERRUPTS();
        }
    #endif /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

__asm શૂન્ય xPortPendSVHandler( શૂન્ય )
{
    બાહ્ય uxCriticalNesting;
    બાહ્ય pxCurrentTCB;
    બાહ્ય vTaskSwitchContext;

/* *INDENT-OFF* */
    PRESERVE8

    ldr r3, =pxCurrentTCB               /* r3 = &( pxCurrentTCB ). */
    ldr r2, [r3]                        /* r2 = pxCurrentTCB. */
    ldr r1, [r2]                        /* r1 = Location where the context should be saved. */

    /*------------ Save Context. ----------- */
    mrs r3, control
    mrs r0, psp
    isb

    add r0, r0, #0x20                   /* Move r0 to location where s0 is saved. */
    tst lr, #0x10
    ittt eq
    vstmiaeq r1!, {s16-s31}             /* Store s16-s31. */
    vldmiaeq r0, {s0-s16}               /* Copy hardware saved FP context into s0-s16. */
    vstmiaeq r1!, {s0-s16}              /* Store hardware saved FP context. */
    sub r0, r0, #0x20                   /* Set r0 back to the location of hardware saved context. */

    stmia r1!, {r3-r11, lr}             /* Store CONTROL register, r4-r11 and LR. */
    ldmia r0, {r4-r11}                  /* Copy hardware saved context into r4-r11. */
    stmia r1!, {r0, r4-r11}             /* Store original PSP (after hardware has saved context) and the hardware saved context. */
    str r1, [r2]                        /* Save the location from where the context should be restored as the first member of TCB. */

    /*---------- Select next task. --------- */
    mov r0, #configMAX_SYSCALL_INTERRUPT_PRIORITY
#જો ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
    cpsid i                             /* ARM Cortex-M7 r0p1 Errata 837070 workaround. */
#endif
    msr basepri, r0
    dsb
    isb
#જો ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
    cpsie i                             /* ARM Cortex-M7 r0p1 Errata 837070 workaround. */
#endif
    bl vTaskSwitchContext
    mov r0, #0
    msr basepri, r0

    /*------------ Program MPU. ------------ */
    ldr r3, =pxCurrentTCB               /* r3 = &( pxCurrentTCB ). */
    ldr r2, [r3]                        /* r2 = pxCurrentTCB. */
    add r2, r2, #4                      /* r2 = Second item in the TCB which is xMPUSettings. */

    dmb                                 /* Complete outstanding transfers before disabling MPU. */
    ldr r0, =0xe000ed94                 /* MPU_CTRL register. */
    ldr r3, [r0]                        /* Read the value of MPU_CTRL. */
    bic r3, #1                          /* r3 = r3 & ~1 i.e. Clear the bit 0 in r3. */
    str r3, [r0]                        /* Disable MPU. */

    ldr r0, =0xe000ed9c                 /* Region Base Address register. */
    ldmia r2!, {r4-r11}                 /* Read 4 sets of MPU registers [MPU Region # 0 - 3]. */
    stmia r0, {r4-r11}                  /* Write 4 sets of MPU registers [MPU Region # 0 - 3]. */

#જો ( configTOTAL_MPU_REGIONS == 16 )
    ldmia r2!, {r4-r11}                 /* Read 4 sets of MPU registers [MPU Region # 4 - 7]. */
    stmia r0, {r4-r11}                  /* Write 4 sets of MPU registers. [MPU Region # 4 - 7]. */
    ldmia r2!, {r4-r11}                 /* Read 4 sets of MPU registers [MPU Region # 8 - 11]. */
    stmia r0, {r4-r11}                  /* Write 4 sets of MPU registers. [MPU Region # 8 - 11]. */
#endif /* configTOTAL_MPU_REGIONS == 16. */

    ldr r0, =0xe000ed94                 /* MPU_CTRL register. */
    ldr r3, [r0]                        /* Read the value of MPU_CTRL. */
    orr r3, #1                          /* r3 = r3 | 1 i.e. Set the bit 0 in r3. */
    str r3, [r0]                        /* Enable MPU. */
    dsb                                 /* Force memory writes before continuing. */

    /*---------- Restore Context. ---------- */
    ldr r3, =pxCurrentTCB               /* r3 = &( pxCurrentTCB ). */
    ldr r2, [r3]                        /* r2 = pxCurrentTCB. */
    ldr r1, [r2]                        /* r1 = Location of saved context in TCB. */

    ldmdb r1!, {r0, r4-r11}             /* r0 contains PSP after the hardware had saved context. r4-r11 contain hardware saved context. */
    msr psp, r0
    stmia r0!, {r4-r11}                 /* Copy the hardware saved context on the task stack. */
    ldmdb r1!, {r3-r11, lr}             /* r3 contains CONTROL register. r4-r11 and LR restored. */
    msr control, r3

    tst lr, #0x10
    ittt eq
    vldmdbeq r1!, {s0-s16}              /* s0-s16 contain hardware saved FP context. */
    vstmiaeq r0!, {s0-s16}              /* Copy hardware saved FP context on the task stack. */
    vldmdbeq r1!, {s16-s31}             /* Restore s16-s31. */

    str r1, [r2]                        /* Save the location where the context should be saved next as the first member of TCB. */
    bx lr
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

શૂન્ય xPortSysTickHandler( શૂન્ય )
{
    uint32_t ulDummy;

    ulDummy = portSET_INTERRUPT_MASK_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        જો( xTaskIncrementTick() != pdFALSE )
        {
            traceISR_EXIT_TO_SCHEDULER();
            /* Pend a context switch. */
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;
        }
        નહીંતર
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
__weak શૂન્ય vSetupTimerInterrupt( શૂન્ય )
{
    /* Reset the SysTick. */
    portNVIC_SYSTICK_CTRL_REG = 0UL;
    port_NVIC_SYSTICK_CURRENT_કિંમત_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    portNVIC_SYSTICK_LOAD_REG = ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL;
    portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK | portNVIC_SYSTICK_INT | portNVIC_SYSTICK_ENABLE;
}
/*-----------------------------------------------------------*/

__asm શૂન્ય vPortEnableVFP( શૂન્ય )
{
/* *INDENT-OFF* */
    PRESERVE8

    ldr.w r0, =0xE000ED88 /* The FPU enable bits are in the CPACR. */
    ldr r1, [ r0 ]

    orr r1, r1, #( 0xf << 20 ) /* Enable CP10 and CP11 coprocessors, then save back. */
    str r1, [ r0 ]
    bx r14
    nop
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

સ્થિર શૂન્ય prvSetupMPU( શૂન્ય )
{
    બાહ્ય uint32_t __privileged_functions_start__;
    બાહ્ય uint32_t __privileged_functions_end__;
    બાહ્ય uint32_t __FLASH_segment_start__;
    બાહ્ય uint32_t __FLASH_segment_end__;
    બાહ્ય uint32_t __privileged_data_start__;
    બાહ્ય uint32_t __privileged_data_end__;

    /* The only permitted number of regions are 8 or 16. */
    configASSERT( ( configTOTAL_MPU_REGIONS == 8 ) || ( configTOTAL_MPU_REGIONS == 16 ) );

    /* Ensure that the configTOTAL_MPU_REGIONS is configured correctly. */
    configASSERT( portMPU_TYPE_REG == port_EXPECTED_MPU_TYPE_કિંમત );

    /* Check the expected MPU is present. */
    જો( portMPU_TYPE_REG == port_EXPECTED_MPU_TYPE_કિંમત )
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

સ્થિર uint32_t prvGetMPURegionSizeSetting( uint32_t ulActualSizeInBytes )
{
    uint32_t ulRegionSize, ul_Return_કિંમત = 4;

    /* 32 is the smallest region size, 31 is the largest valid value for
     * ulReturnValue. */
    માટે( ulRegionSize = 32UL; ul_Return_કિંમત < 31UL; ( ulRegionSize <<= 1UL ) )
    {
        જો( ulActualSizeInBytes <= ulRegionSize )
        {
            તોડો;
        }
        નહીંતર
        {
            ul_Return_કિંમત++;
        }
    }

    /* Shift the code by one before returning so it can be written directly
     * into the correct bit position of the attribute register. */
    પાછા( ul_Return_કિંમત << 1UL );
}
/*-----------------------------------------------------------*/

__asm BaseType_t xIsPrivileged( શૂન્ય )
{
/* *INDENT-OFF* */
    PRESERVE8

    mrs r0, control /* r0 = CONTROL. */
    tst r0, #1      /* Perform r0 & 1 (bitwise AND) and update the conditions flag. */
    ite ne
    movne r0, #0    /* CONTROL[0]!=0. Return false to indicate that the processor is not privileged. */
    moveq r0, #1    /* CONTROL[0]==0. Return true to indicate that the processor is privileged. */
    bx lr           /* Return. */
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

__asm શૂન્ય vResetPrivilege( શૂન્ય )
{
/* *INDENT-OFF* */
    PRESERVE8

    mrs r0, control     /* r0 = CONTROL. */
    orrs r0, #1         /* r0 = r0 | 1. */
    msr control, r0     /* CONTROL = r0. */
    bx lr               /* Return. */
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

શૂન્ય vPortSwitchToUserMode( શૂન્ય )
{
    /* Load the current task's MPU settings from its TCB. */
    xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ખાલી );

    /* Mark the task as unprivileged. */
    xTaskMpuSettings->ulTaskFlags &= ( ~( portTASK_IS_PRIVILEGED_FLAG ) );

    /* Lower the processor's privilege level. */
    vResetPrivilege();
}
/*-----------------------------------------------------------*/

શૂન્ય vPortStoreTaskMPUSettings( xMPU_SETTINGS * xMPUSettings,
                                અચલ સંરચના xMEMORY_REGION * અચલ xRegions,
                                ઢગલો_Type_t * px_Bottom_Of_ઢગલો,
                                config_ઢગલો_DEPTH_TYPE ux_ઢગલો_Depth )
{
    બાહ્ય uint32_t __SRAM_segment_start__;
    બાહ્ય uint32_t __SRAM_segment_end__;
    બાહ્ય uint32_t __privileged_data_start__;
    બાહ્ય uint32_t __privileged_data_end__;


    int32_t lIndex;
    uint32_t ul;

    જો( xRegions == ખાલી )
    {
        /* No MPU regions are specified so allow access to all RAM. */
        xMPUSettings->xRegion[ 0 ].ulRegionBaseAddress =
            ( ( uint32_t ) __SRAM_segment_start__ ) | /* Base address. */
            ( portMPU_REGION_VALID ) |
            ( port_ઢગલો_REGION );                     /* Region number. */

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
        માટે( ul = 1UL; ul <= port_અંક_CONFIGURABLE_REGIONS; ul++ )
        {
            xMPUSettings->xRegion[ ul ].ulRegionBaseAddress = ( ( ul - 1UL ) | portMPU_REGION_VALID );
            xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ulRegionStartAddress = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ulRegionEndAddress = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
        }
    }
    નહીંતર
    {
        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid.  At all other
         * times the stack parameters will not be valid and it is assumed that the
         * stack region has already been configured. */
        જો( ux_ઢગલો_Depth > 0 )
        {
            /* Define the region that allows access to the stack. */
            xMPUSettings->xRegion[ 0 ].ulRegionBaseAddress =
                ( ( uint32_t ) px_Bottom_Of_ઢગલો ) |
                ( portMPU_REGION_VALID ) |
                ( port_ઢગલો_REGION ); /* Region number. */

            xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
                ( portMPU_REGION_READ_WRITE ) |
                ( portMPU_REGION_EXECUTE_NEVER ) |
                ( prvGetMPURegionSizeSetting( ux_ઢગલો_Depth * ( config_ઢગલો_DEPTH_TYPE ) કદ( ઢગલો_Type_t ) ) ) |
                ( ( configTEX_S_C_B_SRAM & portMPU_RASR_TEX_S_C_B_MASK ) << portMPU_RASR_TEX_S_C_B_LOCATION ) |
                ( portMPU_REGION_ENABLE );

            xMPUSettings->xRegionSettings[ 0 ].ulRegionStartAddress = ( uint32_t ) px_Bottom_Of_ઢગલો;
            xMPUSettings->xRegionSettings[ 0 ].ulRegionEndAddress = ( uint32_t ) ( ( uint32_t ) ( px_Bottom_Of_ઢગલો ) +
                                                                                   ( ux_ઢગલો_Depth * ( config_ઢગલો_DEPTH_TYPE ) કદ( ઢગલો_Type_t ) ) - 1UL );
            xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                       tskMPU_WRITE_PERMISSION );
        }

        lIndex = 0;

        માટે( ul = 1UL; ul <= port_અંક_CONFIGURABLE_REGIONS; ul++ )
        {
            જો( ( xRegions[ lIndex ] ).ulLengthInBytes > 0UL )
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

                જો( ( ( xRegions[ lIndex ].ulParameters & portMPU_REGION_READ_ONLY ) == portMPU_REGION_READ_ONLY ) ||
                    ( ( xRegions[ lIndex ].ulParameters & portMPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) == portMPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = tskMPU_READ_PERMISSION;
                }

                જો( ( xRegions[ lIndex ].ulParameters & portMPU_REGION_READ_WRITE ) == portMPU_REGION_READ_WRITE )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
                }
            }
            નહીંતર
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

#જો ( configUSE_MPU_WRAPPERS_V1 == 0 )

    BaseType_t xPortIsAuthorizedToAccessBuffer( અચલ શૂન્ય * pvBuffer,
                                                size_t xBufferLength,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ulBufferStartAddress, ulBufferEndAddress;
        BaseType_t xAccessGranted = pdFALSE;
        અચલ xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ખાલી ); /* Calling task's MPU settings. */


        જો( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        નહીંતર જો( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        નહીંતર
        {
            જો( portADD_UINT32_WILL_OVERFLOW( ( ( uint32_t ) pvBuffer ), ( ( uint32_t ) xBufferLength - 1UL ) ) == pdFALSE )
            {
                ulBufferStartAddress = ( uint32_t ) pvBuffer;
                ulBufferEndAddress = ( ( ( uint32_t ) pvBuffer ) + ( uint32_t ) xBufferLength - 1UL );

                માટે( i = 0; i < port_TOTAL_અંક_REGIONS_IN_TCB; i++ )
                {
                    જો( portIS_ADDRESS_WITHIN_RANGE( ulBufferStartAddress,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ulRegionStartAddress,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ulRegionEndAddress ) &&
                        portIS_ADDRESS_WITHIN_RANGE( ulBufferEndAddress,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ulRegionStartAddress,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ulRegionEndAddress ) &&
                        portIS_AUTHORIZED( ulAccessRequested, xTaskMpuSettings->xRegionSettings[ i ].ulRegionPermissions ) )
                    {
                        xAccessGranted = pdTRUE;
                        તોડો;
                    }
                }
            }
        }

        પાછા xAccessGranted;
    }

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

__asm uint32_t prvPortGetIPSR( શૂન્ય )
{
/* *INDENT-OFF* */
    PRESERVE8

    mrs r0, ipsr
    bx r14
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

#જો ( configASSERT_DEFINED == 1 )

    શૂન્ય vPortValidateInterruptPriority( શૂન્ય )
    {
        uint32_t ulCurrentInterrupt;
        uint8_t ucCurrentPriority;

        /* Obtain the number of the currently executing interrupt. */
        ulCurrentInterrupt = prvPortGetIPSR();

        /* Is the interrupt number a user defined interrupt? */
        જો( ulCurrentInterrupt >= port_FIRST_USER_INTERRUPT_સંખ્યા )
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

#જો ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    શૂન્ય vPortGrantAccessToKernelObject( TaskHandle_t xInternalTaskHandle,
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

#જો ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    શૂન્ય vPortRevokeAccessToKernelObject( TaskHandle_t xInternalTaskHandle,
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

#જો ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #જો ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        BaseType_t xPortIsAuthorizedToAccessKernelObject( int32_t lInternalIndexOfKernelObject ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulAccessControlListEntryIndex, ulAccessControlListEntryBit;
            BaseType_t xAccessGranted = pdFALSE;
            અચલ xMPU_SETTINGS * xTaskMpuSettings;

            જો( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            નહીંતર
            {
                xTaskMpuSettings = xTaskGetMPUSettings( ખાલી ); /* Calling task's MPU settings. */

                ulAccessControlListEntryIndex = ( ( uint32_t ) lInternalIndexOfKernelObject / portACL_ENTRY_SIZE_BITS );
                ulAccessControlListEntryBit = ( ( uint32_t ) lInternalIndexOfKernelObject % portACL_ENTRY_SIZE_BITS );

                જો( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                નહીંતર
                {
                    જો( ( xTaskMpuSettings->ulAccessControlList[ ulAccessControlListEntryIndex ] & ( 1U << ulAccessControlListEntryBit ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            પાછા xAccessGranted;
        }

    #નહીંતર /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        BaseType_t xPortIsAuthorizedToAccessKernelObject( int32_t lInternalIndexOfKernelObject ) /* PRIVILEGED_FUNCTION */
        {
            ( શૂન્ય ) lInternalIndexOfKernelObject;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            પાછા pdTRUE;
        }

    #endif /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/
