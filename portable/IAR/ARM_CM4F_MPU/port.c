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
#समावेश <intrinsics.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#घोषणा MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#समावेश "FreeRTOS.h"
#समावेश "task.h"
#समावेश "mpu_syscall_numbers.h"

#अघोषित MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#अगर_अघोषित __ARMVFP__
    #त्रुटि This port can only be used when the project options are configured to enable hardware floating point support.
#पूर्ण_अगर

#अगर ( configMAX_SYSCALL_INTERRUPT_PRIORITY == 0 )
    #त्रुटि configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to 0.  See http: /*www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
#पूर्ण_अगर

#अगर_अघोषित configSYSTICK_CLOCK_HZ
    #घोषणा configSYSTICK_CLOCK_HZ      configCPU_CLOCK_HZ
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #घोषणा portNVIC_SYSTICK_CLK_BIT    ( 1UL << 2UL )
#अन्यथा

/* The way the SysTick is clocked is not modified in case it is not the same
 * as the core. */
    #घोषणा portNVIC_SYSTICK_CLK_BIT    ( 0 )
#पूर्ण_अगर

/* Unprivileged critical sections are not supported when using MPU wrappers
 * version 2. Default the option to 0 and reject an explicit value of 1. */
#अगर_अघोषित configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS
    #अगर ( configUSE_MPU_WRAPPERS_V1 == 0 )
        #घोषणा configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    0
    #अन्यथा
        #warning "configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not defined. We recommend defining it to 0 in FreeRTOSConfig.h for better security."
        #घोषणा configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    1
    #पूर्ण_अगर
#अन्यथा
    #अगर ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) )
        #त्रुटि configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not supported with MPU wrappers version 2 ( configUSE_MPU_WRAPPERS_V1 == 0 ).
    #पूर्ण_अगर
#पूर्ण_अगर

/* Prototype of all Interrupt Service Routines (ISRs). */
प्रकार व्योम ( * portISR_t )( व्योम );

/* Constants required to manipulate the core.  Registers first... */
#घोषणा portNVIC_SYSTICK_CTRL_REG                 ( *( ( अस्थिर uint32_t * ) 0xe000e010 ) )
#घोषणा portNVIC_SYSTICK_LOAD_REG                 ( *( ( अस्थिर uint32_t * ) 0xe000e014 ) )
#घोषणा port_NVIC_SYSTICK_CURRENT_मूल्य_REG        ( *( ( अस्थिर uint32_t * ) 0xe000e018 ) )
#घोषणा portNVIC_SHPR3_REG                        ( *( ( अस्थिर uint32_t * ) 0xe000ed20 ) )
#घोषणा portNVIC_SHPR2_REG                        ( *( ( अस्थिर uint32_t * ) 0xe000ed1c ) )
#घोषणा portNVIC_SYS_CTRL_STATE_REG               ( *( ( अस्थिर uint32_t * ) 0xe000ed24 ) )
#घोषणा portNVIC_MEM_FAULT_ENABLE                 ( 1UL << 16UL )

/* Constants required to access and manipulate the MPU. */
#घोषणा portMPU_TYPE_REG                          ( *( ( अस्थिर uint32_t * ) 0xe000ed90 ) )
#घोषणा portMPU_REGION_BASE_ADDRESS_REG           ( *( ( अस्थिर uint32_t * ) 0xe000ed9C ) )
#घोषणा portMPU_REGION_ATTRIBUTE_REG              ( *( ( अस्थिर uint32_t * ) 0xe000edA0 ) )
#घोषणा portMPU_CTRL_REG                          ( *( ( अस्थिर uint32_t * ) 0xe000ed94 ) )
#घोषणा port_EXPECTED_MPU_TYPE_मूल्य               ( config_योग_MPU_REGIONS << 8UL )
#घोषणा portMPU_ENABLE                            ( 0x01UL )
#घोषणा portMPU_BACKGROUND_ENABLE                 ( 1UL << 2UL )
#घोषणा portPRIVILEGED_EXECUTION_START_ADDRESS    ( 0UL )
#घोषणा portMPU_REGION_VALID                      ( 0x10UL )
#घोषणा portMPU_REGION_ENABLE                     ( 0x01UL )
#घोषणा portPERIPHERALS_START_ADDRESS             0x40000000UL
#घोषणा portPERIPHERALS_END_ADDRESS               0x5FFFFFFFUL

/* ...then bits in the registers. */
#घोषणा portNVIC_SYSTICK_INT_BIT                  ( 1UL << 1UL )
#घोषणा portNVIC_SYSTICK_ENABLE_BIT               ( 1UL << 0UL )
#घोषणा port_NVIC_SYSTICK_गिनती_FLAG_BIT           ( 1UL << 16UL )
#घोषणा portNVIC_PENDSVCLEAR_BIT                  ( 1UL << 27UL )
#घोषणा portNVIC_PEND_SYSTICK_CLEAR_BIT           ( 1UL << 25UL )

/* Constants used to detect Cortex-M7 r0p0 and r0p1 cores, and ensure
 * that a work around is active for errata 837070. */
#घोषणा portCPUID                                 ( *( ( अस्थिर uint32_t * ) 0xE000ed00 ) )
#घोषणा portCORTEX_M7_r0p1_ID                     ( 0x410FC271UL )
#घोषणा portCORTEX_M7_r0p0_ID                     ( 0x410FC270UL )

/* Constants to manipulate FreeRTOS interrupt priorities. */
#घोषणा portMIN_INTERRUPT_PRIORITY                ( 255UL )
#घोषणा portNVIC_PENDSV_PRI                       ( ( ( uint32_t ) portMIN_INTERRUPT_PRIORITY ) << 16UL )
#घोषणा portNVIC_SYSTICK_PRI                      ( ( ( uint32_t ) portMIN_INTERRUPT_PRIORITY ) << 24UL )
#घोषणा portNVIC_SVC_PRI                          ( ( ( uint32_t ) configMAX_SYSCALL_INTERRUPT_PRIORITY - 1UL ) << 24UL )

/* Constants used to check the installation of the FreeRTOS interrupt handlers. */
#घोषणा portSCB_VTOR_REG                          ( *( ( portISR_t ** ) 0xE000ED08 ) )
#घोषणा port_VECTOR_सूचकांक_SVC                      ( 11 )
#घोषणा port_VECTOR_सूचकांक_PENDSV                   ( 14 )

/* Constants required to check the validity of an interrupt priority. */
#घोषणा port_FIRST_USER_INTERRUPT_संख्या           ( 16 )
#घोषणा portNVIC_IP_REGISTERS_OFFSET_16           ( 0xE000E3F0 )
#घोषणा portAIRCR_REG                             ( *( ( अस्थिर uint32_t * ) 0xE000ED0C ) )
#घोषणा port_MAX_8_BIT_मूल्य                       ( ( uint8_t ) 0xff )
#घोषणा port_शीर्ष_BIT_OF_BYTE                       ( ( uint8_t ) 0x80 )
#घोषणा portMAX_PRIGROUP_BITS                     ( ( uint8_t ) 7 )
#घोषणा portPRIORITY_GROUP_MASK                   ( 0x07UL << 8UL )
#घोषणा portPRIGROUP_SHIFT                        ( 8UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#घोषणा portVECTACTIVE_MASK                       ( 0xFFUL )

/* Constants required to manipulate the VFP. */
#घोषणा portFPCCR                                 ( ( अस्थिर uint32_t * ) 0xe000ef34 ) /* Floating point context control register. */
#घोषणा portASPEN_AND_LSPEN_BITS                  ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#घोषणा portINITIAL_XPSR                          ( 0x01000000 )
#घोषणा portINITIAL_EXC_RETURN                    ( 0xfffffffd )
#घोषणा portINITIAL_CONTROL_IF_UNPRIVILEGED       ( 0x03 )
#घोषणा portINITIAL_CONTROL_IF_PRIVILEGED         ( 0x02 )

/* Constants used during system call enter and exit. */
#घोषणा port_PSR_ढेर_PADDING_MASK                ( 1UL << 9UL )
#घोषणा port_EXC_RETURN_ढेर_FRAME_TYPE_MASK      ( 1UL << 4UL )

/* Offsets in the stack to the parameters when inside the SVC handler. */
#घोषणा portOFFSET_TO_LR                          ( 5 )
#घोषणा portOFFSET_TO_PC                          ( 6 )
#घोषणा portOFFSET_TO_PSR                         ( 7 )

/* The systick is a 24-bit counter. */
#घोषणा port_MAX_24_BIT_संख्या                     ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#घोषणा portMISSED_COUNTS_FACTOR                  ( 45UL )

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#घोषणा portSTART_ADDRESS_MASK                    ( ( ढेर_Type_t ) 0xfffffffeUL )

/* Does addr lie within [start, end] address range? */
#घोषणा portIS_ADDRESS_WITHIN_RANGE( addr, start, end ) \
    ( ( ( addr ) >= ( start ) ) && ( ( addr ) <= ( end ) ) )

/* Is the access request satisfied by the available permissions? */
#घोषणा portIS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#घोषणा portUINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#घोषणा portADD_UINT32_WILL_OVERFLOW( a, b )    ( ( a ) > ( portUINT32_MAX - ( b ) ) )
/*-----------------------------------------------------------*/

/*
 * Configure a number of standard MPU regions that are used by all tasks.
 */
अटल व्योम prvSetupMPU( व्योम ) PRIVILEGED_FUNCTION;

/*
 * Return the smallest MPU region size that a given number of bytes will fit
 * into.  The region size is returned as the value that should be programmed
 * into the region attribute register for that region.
 */
अटल uint32_t prv_Get_MPURegion_आकार_Setting( uint32_t ul_Actual_आकार_In_Bytes ) PRIVILEGED_FUNCTION;

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
व्योम vPortSetupTimerInterrupt( व्योम );

/*
 * Exception handlers.
 */
व्योम xPortSysTickHandler( व्योम ) PRIVILEGED_FUNCTION;

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
बाह्य व्योम vPortStartFirstTask( व्योम ) PRIVILEGED_FUNCTION;

/*
 * Turn the VFP on.
 */
बाह्य व्योम vPortEnableVFP( व्योम );

/*
 * The C portion of the SVC handler.
 */
व्योम vPortSVCHandler_C( uint32_t * pulParam ) PRIVILEGED_FUNCTION;

/*
 * Called from the SVC handler used to start the scheduler.
 */
बाह्य व्योम vPortRestoreContextOfFirstTask( व्योम ) PRIVILEGED_FUNCTION;

/**
 * @brief Enter critical section.
 */
#अगर ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    व्योम vPortEnterCritical( व्योम ) FREERTOS_SYSTEM_CALL;
#अन्यथा
    व्योम vPortEnterCritical( व्योम ) PRIVILEGED_FUNCTION;
#पूर्ण_अगर

/**
 * @brief Exit from critical section.
 */
#अगर ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    व्योम vPortExitCritical( व्योम ) FREERTOS_SYSTEM_CALL;
#अन्यथा
    व्योम vPortExitCritical( व्योम ) PRIVILEGED_FUNCTION;
#पूर्ण_अगर

#अगर ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the system call stack so that upon returning from
 * SVC, the system call stack is used.
 *
 * @param pulTaskStack The current SP when the SVC was raised.
 * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
 * @param ucSystemCallNumber The system call number of the system call.
 */
    व्योम vSystemCallEnter( uint32_t * pul_Task_ढेर,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_संख्या ) PRIVILEGED_FUNCTION;

#पूर्ण_अगर /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#अगर ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Raise SVC for exiting from a system call.
 */
    व्योम vRequestSystemCallExit( व्योम ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#पूर्ण_अगर /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#अगर ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the task stack so that upon returning from
 * SVC, the task stack is used again.
 *
 * @param pulSystemCallStack The current SP when the SVC was raised.
 * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
 */
    व्योम vSystemCallExit( uint32_t * pul_System_Call_ढेर,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#पूर्ण_अगर /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
BaseType_t xPortIsTaskPrivileged( व्योम ) PRIVILEGED_FUNCTION;

/**
 * @brief Make a task unprivileged.
 */
व्योम vPortSwitchToUserMode( व्योम );

/*
 * FreeRTOS handlers implemented in assembly.
 */
बाह्य व्योम vPortSVCHandler( व्योम ) PRIVILEGED_FUNCTION;
बाह्य व्योम xPortPendSVHandler( व्योम ) PRIVILEGED_FUNCTION;
/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
अटल UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

#अगर ( configUSE_MPU_WRAPPERS_V1 == 0 )

/*
 * This variable is set to pdTRUE when the scheduler is started.
 */
    PRIVILEGED_तथ्य अटल BaseType_t xSchedulerRunning = pdFALSE;

#पूर्ण_अगर /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#अगर ( configASSERT_DEFINED == 1 )
    अटल uint8_t ucMaxSysCallPriority = 0;
    अटल uint32_t ulMaxPRIGROUPValue = 0;
    अटल स्थिर अस्थिर uint8_t * स्थिर pcInterruptPriorityRegisters = ( स्थिर अस्थिर uint8_t * स्थिर ) portNVIC_IP_REGISTERS_OFFSET_16;
#पूर्ण_अगर /* configASSERT_DEFINED */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ढेर_Type_t * px_Port_Initialise_ढेर( ढेर_Type_t * px_शीर्ष_Of_ढेर,
                                     TaskFunction_t pxCode,
                                     व्योम * pvParameters,
                                     BaseType_t xRunPrivileged,
                                     xMPU_SETTINGS * xMPUSettings )
{
    अगर( xRunPrivileged == pdTRUE )
    {
        xMPUSettings->ulTaskFlags |= portTASK_IS_PRIVILEGED_FLAG;
        xMPUSettings->ulContext[ 0 ] = portINITIAL_CONTROL_IF_PRIVILEGED;
    }
    अन्यथा
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

    xMPUSettings->ulContext[ 10 ] = ( uint32_t ) ( px_शीर्ष_Of_ढेर - 8 );                /* PSP with the hardware saved stack. */
    xMPUSettings->ulContext[ 11 ] = ( uint32_t ) pvParameters;                        /* r0. */
    xMPUSettings->ulContext[ 12 ] = 0x01010101;                                       /* r1. */
    xMPUSettings->ulContext[ 13 ] = 0x02020202;                                       /* r2. */
    xMPUSettings->ulContext[ 14 ] = 0x03030303;                                       /* r3. */
    xMPUSettings->ulContext[ 15 ] = 0x12121212;                                       /* r12. */
    xMPUSettings->ulContext[ 16 ] = 0;                                                /* LR. */
    xMPUSettings->ulContext[ 17 ] = ( ( uint32_t ) pxCode ) & portSTART_ADDRESS_MASK; /* PC. */
    xMPUSettings->ulContext[ 18 ] = portINITIAL_XPSR;                                 /* xPSR. */

    #अगर ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        /* Ensure that the system call stack is double word aligned. */
        xMPUSettings->x_System_Call_ढेर_Info.pul_System_Call_ढेर = &( xMPUSettings->x_System_Call_ढेर_Info.ul_System_Call_ढेर_बफर[ config_SYSTEM_CALL_ढेर_आकार - 1 ] );
        xMPUSettings->x_System_Call_ढेर_Info.pul_System_Call_ढेर = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_ढेर_Info.pul_System_Call_ढेर ) &
                                                                                 ( uint32_t ) ( ~( portBYTE_ALIGNMENT_MASK ) ) );

        /* This is not NULL only for the duration of a system call. */
        xMPUSettings->x_System_Call_ढेर_Info.pul_Task_ढेर = शून्य;
    }
    #पूर्ण_अगर /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    वापस &( xMPUSettings->ulContext[ 19 ] );
}
/*-----------------------------------------------------------*/

व्योम vPortSVCHandler_C( uint32_t * pulParam ) /* PRIVILEGED_FUNCTION */
{
    uint8_t ucSVCNumber;
    uint32_t ulPC;

    #अगर ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) )
        बाह्य uint32_t __syscalls_flash_start__[];
        बाह्य uint32_t __syscalls_flash_end__[];
    #पूर्ण_अगर /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) ) */

    /* The stack contains: r0, r1, r2, r3, r12, LR, PC and xPSR. The first
     * argument (r0) is pulParam[ 0 ]. */
    ulPC = pulParam[ portOFFSET_TO_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    चयन( ucSVCNumber )
    {
        हाल portSVC_START_SCHEDULER:
            vPortRestoreContextOfFirstTask();
            अवरोध;

        हाल portSVC_YIELD:
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;

            /* Barriers are normally not required
             * but do ensure the code is completely
             * within the specified behaviour for the
             * architecture. */
            __asm अस्थिर ( "dsb" ::: "memory" );
            __asm अस्थिर ( "isb" );

            अवरोध;

    #अगर ( configUSE_MPU_WRAPPERS_V1 == 1 )
        #अगर ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 )
            हाल portSVC_RAISE_PRIVILEGE: /* Only raise the privilege, if the
                                           * svc was raised from any of the
                                           * system calls. */

                अगर( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                    ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
                {
                    __asm अस्थिर
                    (
                        "   mrs r1, control     \n" /* Obtain current control value. */
                        "   bic r1, r1, #1      \n" /* Set privilege bit. */
                        "   msr control, r1     \n" /* Write back new control value. */
                        ::: "r1", "memory"
                    );
                }

                अवरोध;
        #अन्यथा /* if ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
            हाल portSVC_RAISE_PRIVILEGE:
                __asm अस्थिर
                (
                    "   mrs r1, control     \n" /* Obtain current control value. */
                    "   bic r1, r1, #1      \n" /* Set privilege bit. */
                    "   msr control, r1     \n" /* Write back new control value. */
                    ::: "r1", "memory"
                );
                अवरोध;
        #पूर्ण_अगर /* #if( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
    #पूर्ण_अगर /* #if ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

        शेष: /* Unknown SVC call. */
            अवरोध;
    }
}
/*-----------------------------------------------------------*/

#अगर ( configUSE_MPU_WRAPPERS_V1 == 0 )

    व्योम vSystemCallEnter( uint32_t * pul_Task_ढेर,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_संख्या ) /* PRIVILEGED_FUNCTION */
    {
        बाह्य TaskHandle_t pxCurrentTCB;
        बाह्य UBaseType_t uxSystemCallImplementations[ अंक_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_ढेर;
        uint32_t ul_Hardware_Saved_Exception_Frame_आकार, ulSystemCallLocation, i;

        #अगर defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            बाह्य uint32_t * __syscalls_flash_start__;
            बाह्य uint32_t * __syscalls_flash_end__;
        #अन्यथा
            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint32_t __syscalls_flash_start__[];
            बाह्य uint32_t __syscalls_flash_end__[];
        #पूर्ण_अगर /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_ढेर[ portOFFSET_TO_PC ];
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
        अगर( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_ढेर_Info.pul_Task_ढेर == शून्य ) &&
            ( uxSystemCallImplementations[ uc_System_Call_संख्या ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_ढेर = pxMpuSettings->x_System_Call_ढेर_Info.pul_System_Call_ढेर;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            अगर( ( ulLR & port_EXC_RETURN_ढेर_FRAME_TYPE_MASK ) == 0UL )
            {
                /* Extended frame i.e. FPU in use. */
                ul_Hardware_Saved_Exception_Frame_आकार = 26;
                __asm अस्थिर (
                    " vpush {s0}         \n" /* Trigger lazy stacking. */
                    " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                    ::: "memory"
                    );
            }
            अन्यथा
            {
                /* Standard frame i.e. FPU not in use. */
                ul_Hardware_Saved_Exception_Frame_आकार = 8;
            }

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_ढेर = pul_System_Call_ढेर - ul_Hardware_Saved_Exception_Frame_आकार;

            /* Copy the stack frame. */
            क्रम( i = 0; i < ul_Hardware_Saved_Exception_Frame_आकार; i++ )
            {
                pul_System_Call_ढेर[ i ] = pul_Task_ढेर[ i ];
            }

            /* Use the pulSystemCallStack in thread mode. */
            __asm अस्थिर ( "msr psp, %0" : : "r" ( pul_System_Call_ढेर ) );

            /* Raise the privilege for the duration of the system call. */
            __asm अस्थिर (
                " mrs r1, control     \n" /* Obtain current control value. */
                " bic r1, #1          \n" /* Clear nPRIV bit. */
                " msr control, r1     \n" /* Write back new control value. */
                ::: "r1", "memory"
                );

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_ढेर_Info.pul_Task_ढेर = pul_Task_ढेर + ul_Hardware_Saved_Exception_Frame_आकार;

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_ढेर_Info.ulLinkRegisterAtSystemCallEntry = pul_Task_ढेर[ portOFFSET_TO_LR ];


            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_ढेर[ portOFFSET_TO_PC ] = uxSystemCallImplementations[ uc_System_Call_संख्या ];
            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_ढेर[ portOFFSET_TO_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            अगर( ( pul_Task_ढेर[ portOFFSET_TO_PSR ] & port_PSR_ढेर_PADDING_MASK ) == port_PSR_ढेर_PADDING_MASK )
            {
                pxMpuSettings->ulTaskFlags |= port_ढेर_FRAME_HAS_PADDING_FLAG;
            }
            अन्यथा
            {
                pxMpuSettings->ulTaskFlags &= ( ~port_ढेर_FRAME_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_ढेर[ portOFFSET_TO_PSR ] &= ( ~port_PSR_ढेर_PADDING_MASK );
        }
    }

#पूर्ण_अगर /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#अगर ( configUSE_MPU_WRAPPERS_V1 == 0 )

    व्योम vRequestSystemCallExit( व्योम ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm अस्थिर ( "svc %0 \n" ::"i" ( portSVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#पूर्ण_अगर /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#अगर ( configUSE_MPU_WRAPPERS_V1 == 0 )

    व्योम vSystemCallExit( uint32_t * pul_System_Call_ढेर,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        बाह्य TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_ढेर;
        uint32_t ul_Hardware_Saved_Exception_Frame_आकार, ulSystemCallLocation, i;

        #अगर defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            बाह्य uint32_t * __privileged_functions_start__;
            बाह्य uint32_t * __privileged_functions_end__;
        #अन्यथा
            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint32_t __privileged_functions_start__[];
            बाह्य uint32_t __privileged_functions_end__[];
        #पूर्ण_अगर /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_ढेर[ portOFFSET_TO_PC ];
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
        अगर( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_ढेर_Info.pul_Task_ढेर != शून्य ) )
        {
            pul_Task_ढेर = pxMpuSettings->x_System_Call_ढेर_Info.pul_Task_ढेर;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            अगर( ( ulLR & port_EXC_RETURN_ढेर_FRAME_TYPE_MASK ) == 0UL )
            {
                /* Extended frame i.e. FPU in use. */
                ul_Hardware_Saved_Exception_Frame_आकार = 26;
                __asm अस्थिर (
                    " vpush {s0}         \n" /* Trigger lazy stacking. */
                    " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                    ::: "memory"
                    );
            }
            अन्यथा
            {
                /* Standard frame i.e. FPU not in use. */
                ul_Hardware_Saved_Exception_Frame_आकार = 8;
            }

            /* Make space on the task stack for the stack frame. */
            pul_Task_ढेर = pul_Task_ढेर - ul_Hardware_Saved_Exception_Frame_आकार;

            /* Copy the stack frame. */
            क्रम( i = 0; i < ul_Hardware_Saved_Exception_Frame_आकार; i++ )
            {
                pul_Task_ढेर[ i ] = pul_System_Call_ढेर[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm अस्थिर ( "msr psp, %0" : : "r" ( pul_Task_ढेर ) );

            /* Drop the privilege before returning to the thread mode. */
            __asm अस्थिर (
                " mrs r1, control     \n" /* Obtain current control value. */
                " orr r1, #1          \n" /* Set nPRIV bit. */
                " msr control, r1     \n" /* Write back new control value. */
                ::: "r1", "memory"
                );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_ढेर[ portOFFSET_TO_PC ] = pxMpuSettings->x_System_Call_ढेर_Info.ulLinkRegisterAtSystemCallEntry;
            /* Ensure that LR has a valid value.*/
            pul_Task_ढेर[ portOFFSET_TO_LR ] = pxMpuSettings->x_System_Call_ढेर_Info.ulLinkRegisterAtSystemCallEntry;

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            अगर( ( pxMpuSettings->ulTaskFlags & port_ढेर_FRAME_HAS_PADDING_FLAG ) == port_ढेर_FRAME_HAS_PADDING_FLAG )
            {
                pul_Task_ढेर[ portOFFSET_TO_PSR ] |= port_PSR_ढेर_PADDING_MASK;
            }
            अन्यथा
            {
                pul_Task_ढेर[ portOFFSET_TO_PSR ] &= ( ~port_PSR_ढेर_PADDING_MASK );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_ढेर_Info.pul_Task_ढेर = शून्य;
        }
    }

#पूर्ण_अगर /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

BaseType_t xPortIsTaskPrivileged( व्योम ) /* PRIVILEGED_FUNCTION */
{
    BaseType_t xTaskIsPrivileged = pdFALSE;
    स्थिर xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( शून्य ); /* Calling task's MPU settings. */

    अगर( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
    {
        xTaskIsPrivileged = pdTRUE;
    }

    वापस xTaskIsPrivileged;
}
/*-----------------------------------------------------------*/

व्योम vPortSwitchToUserMode( व्योम )
{
    /* Load the current task's MPU settings from its TCB. */
    xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( शून्य );

    /* Mark the task as unprivileged. */
    xTaskMpuSettings->ulTaskFlags &= ( ~( portTASK_IS_PRIVILEGED_FLAG ) );

    /* Lower the processor's privilege level. */
    vResetPrivilege();
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( व्योम )
{
    /* Errata 837070 workaround must only be enabled on Cortex-M7 r0p0
     * and r0p1 cores. */
    #अगर ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        configASSERT( ( portCPUID == portCORTEX_M7_r0p1_ID ) || ( portCPUID == portCORTEX_M7_r0p0_ID ) );
    #अन्यथा

        /* When using this port on a Cortex-M7 r0p0 or r0p1 core, define
         * configENABLE_ERRATA_837070_WORKAROUND to 1 in your
         * FreeRTOSConfig.h. */
        configASSERT( portCPUID != portCORTEX_M7_r0p1_ID );
        configASSERT( portCPUID != portCORTEX_M7_r0p0_ID );
    #पूर्ण_अगर

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
    #अगर ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        स्थिर portISR_t * स्थिर pxVectorTable = portSCB_VTOR_REG;

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
        configASSERT( pxVectorTable[ port_VECTOR_सूचकांक_SVC ] == vPortSVCHandler );
        configASSERT( pxVectorTable[ port_VECTOR_सूचकांक_PENDSV ] == xPortPendSVHandler );
    }
    #पूर्ण_अगर /* configCHECK_HANDLER_INSTALLATION */

    #अगर ( configASSERT_DEFINED == 1 )
    {
        अस्थिर uint8_t ucOriginalPriority;
        अस्थिर uint32_t ulImplementedPrioBits = 0;
        अस्थिर uint8_t * स्थिर pucFirstUserPriorityRegister = ( अस्थिर uint8_t * स्थिर ) ( portNVIC_IP_REGISTERS_OFFSET_16 + port_FIRST_USER_INTERRUPT_संख्या );
        अस्थिर uint8_t uc_Max_Priority_मूल्य;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
         * functions can be called.  ISR safe functions are those that end in
         * "FromISR".  FreeRTOS maintains separate thread and ISR API functions to
         * ensure interrupt entry is as fast and simple as possible.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        ucOriginalPriority = *pucFirstUserPriorityRegister;

        /* Determine the number of priority bits available.  First write to all
         * possible bits. */
        *pucFirstUserPriorityRegister = port_MAX_8_BIT_मूल्य;

        /* Read the value back to see how many bits stuck. */
        uc_Max_Priority_मूल्य = *pucFirstUserPriorityRegister;

        /* Use the same mask on the maximum system call priority. */
        ucMaxSysCallPriority = configMAX_SYSCALL_INTERRUPT_PRIORITY & uc_Max_Priority_मूल्य;

        /* Check that the maximum system call priority is nonzero after
         * accounting for the number of priority bits supported by the
         * hardware. A priority of 0 is invalid because setting the BASEPRI
         * register to 0 unmasks all interrupts, and interrupts with priority 0
         * cannot be masked using BASEPRI.
         * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( ucMaxSysCallPriority );

        /* Check that the bits not implemented in hardware are zero in
         * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( configMAX_SYSCALL_INTERRUPT_PRIORITY & ( uint8_t ) ( ~( uint32_t ) uc_Max_Priority_मूल्य ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
         * of bits read back. */

        जबतक( ( uc_Max_Priority_मूल्य & port_शीर्ष_BIT_OF_BYTE ) == port_शीर्ष_BIT_OF_BYTE )
        {
            ulImplementedPrioBits++;
            uc_Max_Priority_मूल्य <<= ( uint8_t ) 0x01;
        }

        अगर( ulImplementedPrioBits == 8 )
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
        अन्यथा
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
    #पूर्ण_अगर /* configASSERT_DEFINED */

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

    #अगर ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        xSchedulerRunning = pdTRUE;
    }
    #पूर्ण_अगर /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    /* Ensure the VFP is enabled - it should be anyway. */
    vPortEnableVFP();

    /* Lazy save always. */
    *( portFPCCR ) |= portASPEN_AND_LSPEN_BITS;

    /* Start the first task. */
    vPortStartFirstTask();

    /* Should not get here! */
    वापस 0;
}
/*-----------------------------------------------------------*/

व्योम vPortEndScheduler( व्योम )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

व्योम vPortEnterCritical( व्योम )
{
    #अगर ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        अगर( portIS_PRIVILEGED() == pdFALSE )
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
            अगर( uxCriticalNesting == 1 )
            {
                configASSERT( ( portNVIC_INT_CTRL_REG & portVECTACTIVE_MASK ) == 0 );
            }

            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        अन्यथा
        {
            portDISABLE_INTERRUPTS();
            uxCriticalNesting++;

            /* This is not the interrupt safe version of the enter critical function so
             * assert() if it is being called from an interrupt context.  Only API
             * functions that end in "FromISR" can be used in an interrupt.  Only assert if
             * the critical nesting count is 1 to protect against recursive calls if the
             * assert function also uses a critical section. */
            अगर( uxCriticalNesting == 1 )
            {
                configASSERT( ( portNVIC_INT_CTRL_REG & portVECTACTIVE_MASK ) == 0 );
            }
        }
    #अन्यथा /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        portDISABLE_INTERRUPTS();
        uxCriticalNesting++;

        /* This is not the interrupt safe version of the enter critical function so
         * assert() if it is being called from an interrupt context.  Only API
         * functions that end in "FromISR" can be used in an interrupt.  Only assert if
         * the critical nesting count is 1 to protect against recursive calls if the
         * assert function also uses a critical section. */
        अगर( uxCriticalNesting == 1 )
        {
            configASSERT( ( portNVIC_INT_CTRL_REG & portVECTACTIVE_MASK ) == 0 );
        }
    #पूर्ण_अगर /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

व्योम vPortExitCritical( व्योम )
{
    #अगर ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        अगर( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            अगर( uxCriticalNesting == 0 )
            {
                portENABLE_INTERRUPTS();
            }

            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        अन्यथा
        {
            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            अगर( uxCriticalNesting == 0 )
            {
                portENABLE_INTERRUPTS();
            }
        }
    #अन्यथा /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        configASSERT( uxCriticalNesting );
        uxCriticalNesting--;

        अगर( uxCriticalNesting == 0 )
        {
            portENABLE_INTERRUPTS();
        }
    #पूर्ण_अगर /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

व्योम xPortSysTickHandler( व्योम )
{
    /* The SysTick runs at the lowest interrupt priority, so when this interrupt
     * executes all interrupts must be unmasked.  There is therefore no need to
     * save and then restore the interrupt mask value as its value is already
     * known. */
    portDISABLE_INTERRUPTS();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        अगर( xTaskIncrementTick() != pdFALSE )
        {
            traceISR_EXIT_TO_SCHEDULER();

            /* A context switch is required.  Context switching is performed in
             * the PendSV interrupt.  Pend the PendSV interrupt. */
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;
        }
        अन्यथा
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
__weak व्योम vPortSetupTimerInterrupt( व्योम )
{
    /* Stop and clear the SysTick. */
    portNVIC_SYSTICK_CTRL_REG = 0UL;
    port_NVIC_SYSTICK_CURRENT_मूल्य_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    portNVIC_SYSTICK_LOAD_REG = ( configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL;
    portNVIC_SYSTICK_CTRL_REG = ( portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT );
}
/*-----------------------------------------------------------*/

अटल व्योम prvSetupMPU( व्योम )
{
    बाह्य uint32_t __privileged_functions_start__[];
    बाह्य uint32_t __privileged_functions_end__[];
    बाह्य uint32_t __FLASH_segment_start__[];
    बाह्य uint32_t __FLASH_segment_end__[];
    बाह्य uint32_t __privileged_data_start__[];
    बाह्य uint32_t __privileged_data_end__[];

    /* The only permitted number of regions are 8 or 16. */
    configASSERT( ( config_योग_MPU_REGIONS == 8 ) || ( config_योग_MPU_REGIONS == 16 ) );

    /* Ensure that the configTOTAL_MPU_REGIONS is configured correctly. */
    configASSERT( portMPU_TYPE_REG == port_EXPECTED_MPU_TYPE_मूल्य );

    /* Check the expected MPU is present. */
    अगर( portMPU_TYPE_REG == port_EXPECTED_MPU_TYPE_मूल्य )
    {
        /* First setup the unprivileged flash for unprivileged read only access. */
        portMPU_REGION_BASE_ADDRESS_REG = ( ( uint32_t ) __FLASH_segment_start__ ) | /* Base address. */
                                          ( portMPU_REGION_VALID ) |
                                          ( portUNPRIVILEGED_FLASH_REGION );

        portMPU_REGION_ATTRIBUTE_REG = ( portMPU_REGION_READ_ONLY ) |
                                       ( ( configTEX_S_C_B_FLASH & portMPU_RASR_TEX_S_C_B_MASK ) << portMPU_RASR_TEX_S_C_B_LOCATION ) |
                                       ( prv_Get_MPURegion_आकार_Setting( ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__ ) ) |
                                       ( portMPU_REGION_ENABLE );

        /* Setup the privileged flash for privileged only access.  This is where
         * the kernel code is placed. */
        portMPU_REGION_BASE_ADDRESS_REG = ( ( uint32_t ) __privileged_functions_start__ ) | /* Base address. */
                                          ( portMPU_REGION_VALID ) |
                                          ( portPRIVILEGED_FLASH_REGION );

        portMPU_REGION_ATTRIBUTE_REG = ( portMPU_REGION_PRIVILEGED_READ_ONLY ) |
                                       ( ( configTEX_S_C_B_FLASH & portMPU_RASR_TEX_S_C_B_MASK ) << portMPU_RASR_TEX_S_C_B_LOCATION ) |
                                       ( prv_Get_MPURegion_आकार_Setting( ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__ ) ) |
                                       ( portMPU_REGION_ENABLE );

        /* Setup the privileged data RAM region.  This is where the kernel data
         * is placed. */
        portMPU_REGION_BASE_ADDRESS_REG = ( ( uint32_t ) __privileged_data_start__ ) | /* Base address. */
                                          ( portMPU_REGION_VALID ) |
                                          ( portPRIVILEGED_RAM_REGION );

        portMPU_REGION_ATTRIBUTE_REG = ( portMPU_REGION_PRIVILEGED_READ_WRITE ) |
                                       ( portMPU_REGION_EXECUTE_NEVER ) |
                                       ( ( configTEX_S_C_B_SRAM & portMPU_RASR_TEX_S_C_B_MASK ) << portMPU_RASR_TEX_S_C_B_LOCATION ) |
                                       prv_Get_MPURegion_आकार_Setting( ( uint32_t ) __privileged_data_end__ - ( uint32_t ) __privileged_data_start__ ) |
                                       ( portMPU_REGION_ENABLE );

        /* By default allow everything to access the general peripherals.  The
         * system peripherals and registers are protected. */
        portMPU_REGION_BASE_ADDRESS_REG = ( portPERIPHERALS_START_ADDRESS ) |
                                          ( portMPU_REGION_VALID ) |
                                          ( portGENERAL_PERIPHERALS_REGION );

        portMPU_REGION_ATTRIBUTE_REG = ( portMPU_REGION_READ_WRITE | portMPU_REGION_EXECUTE_NEVER ) |
                                       ( prv_Get_MPURegion_आकार_Setting( portPERIPHERALS_END_ADDRESS - portPERIPHERALS_START_ADDRESS ) ) |
                                       ( portMPU_REGION_ENABLE );

        /* Enable the memory fault exception. */
        portNVIC_SYS_CTRL_STATE_REG |= portNVIC_MEM_FAULT_ENABLE;

        /* Enable the MPU with the background region configured. */
        portMPU_CTRL_REG |= ( portMPU_ENABLE | portMPU_BACKGROUND_ENABLE );
    }
}
/*-----------------------------------------------------------*/

अटल uint32_t prv_Get_MPURegion_आकार_Setting( uint32_t ul_Actual_आकार_In_Bytes )
{
    uint32_t ul_Region_आकार, ul_Return_मूल्य = 4;

    /* 32 is the smallest region size, 31 is the largest valid value for
     * ulReturnValue. */
    क्रम( ul_Region_आकार = 32UL; ul_Return_मूल्य < 31UL; ( ul_Region_आकार <<= 1UL ) )
    {
        अगर( ul_Actual_आकार_In_Bytes <= ul_Region_आकार )
        {
            अवरोध;
        }
        अन्यथा
        {
            ul_Return_मूल्य++;
        }
    }

    /* Shift the code by one before returning so it can be written directly
     * into the correct bit position of the attribute register. */
    वापस( ul_Return_मूल्य << 1UL );
}
/*-----------------------------------------------------------*/

व्योम vPortStoreTaskMPUSettings( xMPU_SETTINGS * xMPUSettings,
                                स्थिर काष्ठा xMEMORY_REGION * स्थिर xRegions,
                                ढेर_Type_t * px_Bottom_Of_ढेर,
                                config_ढेर_DEPTH_TYPE ux_ढेर_Depth )
{
    बाह्य uint32_t __SRAM_segment_start__[];
    बाह्य uint32_t __SRAM_segment_end__[];
    बाह्य uint32_t __privileged_data_start__[];
    बाह्य uint32_t __privileged_data_end__[];
    int32_t l_सूचकांक;
    uint32_t ul;

    अगर( xRegions == शून्य )
    {
        /* No MPU regions are specified so allow access to all RAM. */
        xMPUSettings->xRegion[ 0 ].ulRegionBaseAddress =
            ( ( uint32_t ) __SRAM_segment_start__ ) | /* Base address. */
            ( portMPU_REGION_VALID ) |
            ( port_ढेर_REGION );                     /* Region number. */

        xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
            ( portMPU_REGION_READ_WRITE ) |
            ( portMPU_REGION_EXECUTE_NEVER ) |
            ( ( configTEX_S_C_B_SRAM & portMPU_RASR_TEX_S_C_B_MASK ) << portMPU_RASR_TEX_S_C_B_LOCATION ) |
            ( prv_Get_MPURegion_आकार_Setting( ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__ ) ) |
            ( portMPU_REGION_ENABLE );

        xMPUSettings->xRegionSettings[ 0 ].ulRegionStartAddress = ( uint32_t ) __SRAM_segment_start__;
        xMPUSettings->xRegionSettings[ 0 ].ulRegionEndAddress = ( uint32_t ) __SRAM_segment_end__;
        xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                   tskMPU_WRITE_PERMISSION );

        /* Invalidate user configurable regions. */
        क्रम( ul = 1UL; ul <= port_अंक_CONFIGURABLE_REGIONS; ul++ )
        {
            xMPUSettings->xRegion[ ul ].ulRegionBaseAddress = ( ( ul - 1UL ) | portMPU_REGION_VALID );
            xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ulRegionStartAddress = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ulRegionEndAddress = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
        }
    }
    अन्यथा
    {
        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid.  At all other
         * times the stack parameters will not be valid and it is assumed that the
         * stack region has already been configured. */
        अगर( ux_ढेर_Depth > 0 )
        {
            /* Define the region that allows access to the stack. */
            xMPUSettings->xRegion[ 0 ].ulRegionBaseAddress =
                ( ( uint32_t ) px_Bottom_Of_ढेर ) |
                ( portMPU_REGION_VALID ) |
                ( port_ढेर_REGION ); /* Region number. */

            xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
                ( portMPU_REGION_READ_WRITE ) |
                ( portMPU_REGION_EXECUTE_NEVER ) |
                ( prv_Get_MPURegion_आकार_Setting( ux_ढेर_Depth * ( config_ढेर_DEPTH_TYPE ) माप( ढेर_Type_t ) ) ) |
                ( ( configTEX_S_C_B_SRAM & portMPU_RASR_TEX_S_C_B_MASK ) << portMPU_RASR_TEX_S_C_B_LOCATION ) |
                ( portMPU_REGION_ENABLE );

            xMPUSettings->xRegionSettings[ 0 ].ulRegionStartAddress = ( uint32_t ) px_Bottom_Of_ढेर;
            xMPUSettings->xRegionSettings[ 0 ].ulRegionEndAddress = ( uint32_t ) ( ( uint32_t ) ( px_Bottom_Of_ढेर ) +
                                                                                   ( ux_ढेर_Depth * ( config_ढेर_DEPTH_TYPE ) माप( ढेर_Type_t ) ) - 1UL );
            xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                       tskMPU_WRITE_PERMISSION );
        }

        l_सूचकांक = 0;

        क्रम( ul = 1UL; ul <= port_अंक_CONFIGURABLE_REGIONS; ul++ )
        {
            अगर( ( xRegions[ l_सूचकांक ] ).ul_लंबाई_In_Bytes > 0UL )
            {
                /* Translate the generic region definition contained in
                 * xRegions into the CM4 specific MPU settings that are then
                 * stored in xMPUSettings. */
                xMPUSettings->xRegion[ ul ].ulRegionBaseAddress =
                    ( ( uint32_t ) xRegions[ l_सूचकांक ].pvBaseAddress ) |
                    ( portMPU_REGION_VALID ) |
                    ( ul - 1UL ); /* Region number. */

                xMPUSettings->xRegion[ ul ].ulRegionAttribute =
                    ( prv_Get_MPURegion_आकार_Setting( xRegions[ l_सूचकांक ].ul_लंबाई_In_Bytes ) ) |
                    ( xRegions[ l_सूचकांक ].ulParameters ) |
                    ( portMPU_REGION_ENABLE );

                xMPUSettings->xRegionSettings[ ul ].ulRegionStartAddress = ( uint32_t ) xRegions[ l_सूचकांक ].pvBaseAddress;
                xMPUSettings->xRegionSettings[ ul ].ulRegionEndAddress = ( uint32_t ) ( ( uint32_t ) xRegions[ l_सूचकांक ].pvBaseAddress + xRegions[ l_सूचकांक ].ul_लंबाई_In_Bytes - 1UL );
                xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;

                अगर( ( ( xRegions[ l_सूचकांक ].ulParameters & portMPU_REGION_READ_ONLY ) == portMPU_REGION_READ_ONLY ) ||
                    ( ( xRegions[ l_सूचकांक ].ulParameters & portMPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) == portMPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = tskMPU_READ_PERMISSION;
                }

                अगर( ( xRegions[ l_सूचकांक ].ulParameters & portMPU_REGION_READ_WRITE ) == portMPU_REGION_READ_WRITE )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
                }
            }
            अन्यथा
            {
                /* Invalidate the region. */
                xMPUSettings->xRegion[ ul ].ulRegionBaseAddress = ( ( ul - 1UL ) | portMPU_REGION_VALID );
                xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ulRegionStartAddress = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ulRegionEndAddress = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
            }

            l_सूचकांक++;
        }
    }
}
/*-----------------------------------------------------------*/

#अगर ( configUSE_MPU_WRAPPERS_V1 == 0 )

    BaseType_t x_Port_Is_Authorized_To_Access_बफर( स्थिर व्योम * pv_बफर,
                                                माप_प्रकार x_बफर_लंबाई,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_बफर_Start_Address, ul_बफर_End_Address;
        BaseType_t xAccessGranted = pdFALSE;
        स्थिर xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( शून्य ); /* Calling task's MPU settings. */

        अगर( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        अन्यथा अगर( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        अन्यथा
        {
            अगर( portADD_UINT32_WILL_OVERFLOW( ( ( uint32_t ) pv_बफर ), ( ( uint32_t ) x_बफर_लंबाई - 1UL ) ) == pdFALSE )
            {
                ul_बफर_Start_Address = ( uint32_t ) pv_बफर;
                ul_बफर_End_Address = ( ( ( uint32_t ) pv_बफर ) + ( uint32_t ) x_बफर_लंबाई - 1UL );

                क्रम( i = 0; i < port_योग_अंक_REGIONS_IN_TCB; i++ )
                {
                    अगर( portIS_ADDRESS_WITHIN_RANGE( ul_बफर_Start_Address,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ulRegionStartAddress,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ulRegionEndAddress ) &&
                        portIS_ADDRESS_WITHIN_RANGE( ul_बफर_End_Address,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ulRegionStartAddress,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ulRegionEndAddress ) &&
                        portIS_AUTHORIZED( ulAccessRequested, xTaskMpuSettings->xRegionSettings[ i ].ulRegionPermissions ) )
                    {
                        xAccessGranted = pdTRUE;
                        अवरोध;
                    }
                }
            }
        }

        वापस xAccessGranted;
    }

#पूर्ण_अगर /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/


#अगर ( configASSERT_DEFINED == 1 )

    व्योम vPortValidateInterruptPriority( व्योम )
    {
        uint32_t ulCurrentInterrupt;
        uint8_t ucCurrentPriority;

        /* Obtain the number of the currently executing interrupt. */
        __asm अस्थिर ( "mrs %0, ipsr" : "=r" ( ulCurrentInterrupt )::"memory" );

        /* Is the interrupt number a user defined interrupt? */
        अगर( ulCurrentInterrupt >= port_FIRST_USER_INTERRUPT_संख्या )
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

#पूर्ण_अगर /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/

#अगर ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    व्योम vPortGrantAccessToKernelObject( TaskHandle_t xInternalTaskHandle,
                                         int32_t l_Internal_सूचकांक_Of_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_Entry_सूचकांक, ulAccessControlListEntryBit;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_Entry_सूचकांक = ( ( uint32_t ) l_Internal_सूचकांक_Of_Kernel_Object / port_ACL_ENTRY_आकार_BITS );
        ulAccessControlListEntryBit = ( ( uint32_t ) l_Internal_सूचकांक_Of_Kernel_Object % port_ACL_ENTRY_आकार_BITS );

        xTaskMpuSettings = xTaskGetMPUSettings( xInternalTaskHandle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_Entry_सूचकांक ] |= ( 1U << ulAccessControlListEntryBit );
    }

#पूर्ण_अगर /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#अगर ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    व्योम vPortRevokeAccessToKernelObject( TaskHandle_t xInternalTaskHandle,
                                          int32_t l_Internal_सूचकांक_Of_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_Entry_सूचकांक, ulAccessControlListEntryBit;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_Entry_सूचकांक = ( ( uint32_t ) l_Internal_सूचकांक_Of_Kernel_Object / port_ACL_ENTRY_आकार_BITS );
        ulAccessControlListEntryBit = ( ( uint32_t ) l_Internal_सूचकांक_Of_Kernel_Object % port_ACL_ENTRY_आकार_BITS );

        xTaskMpuSettings = xTaskGetMPUSettings( xInternalTaskHandle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_Entry_सूचकांक ] &= ~( 1U << ulAccessControlListEntryBit );
    }

#पूर्ण_अगर /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#अगर ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #अगर ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        BaseType_t xPortIsAuthorizedToAccessKernelObject( int32_t l_Internal_सूचकांक_Of_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_Entry_सूचकांक, ulAccessControlListEntryBit;
            BaseType_t xAccessGranted = pdFALSE;
            स्थिर xMPU_SETTINGS * xTaskMpuSettings;

            अगर( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            अन्यथा
            {
                xTaskMpuSettings = xTaskGetMPUSettings( शून्य ); /* Calling task's MPU settings. */

                ul_Access_Control_List_Entry_सूचकांक = ( ( uint32_t ) l_Internal_सूचकांक_Of_Kernel_Object / port_ACL_ENTRY_आकार_BITS );
                ulAccessControlListEntryBit = ( ( uint32_t ) l_Internal_सूचकांक_Of_Kernel_Object % port_ACL_ENTRY_आकार_BITS );

                अगर( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                अन्यथा
                {
                    अगर( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_Entry_सूचकांक ] & ( 1U << ulAccessControlListEntryBit ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            वापस xAccessGranted;
        }

    #अन्यथा /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        BaseType_t xPortIsAuthorizedToAccessKernelObject( int32_t l_Internal_सूचकांक_Of_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( व्योम ) l_Internal_सूचकांक_Of_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            वापस pdTRUE;
        }

    #पूर्ण_अगर /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#पूर्ण_अगर /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/
