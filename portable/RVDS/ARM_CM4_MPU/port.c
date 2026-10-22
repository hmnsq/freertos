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
#وصف_ڪريو MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "mpu_syscall_numbers.h"

#جيڪڏهن_وصف_نه_ٿيل __TARGET_FPU_VFP
    #غلطي This پورٽ can only be استعمال_ٿيل when the project options are configured منزل enable hardware floating نقطو_2 support.
#جيڪڏهن_پورو

#وصف_رد MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Unprivileged critical sections are not supported when using MPU wrappers
 * version 2. Default the option to 0 and reject an explicit value of 1. */
#جيڪڏهن_وصف_نه_ٿيل configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS
    #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
        #وصف_ڪريو configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    0
    #وإلا
        #warning "configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not defined. We recommend defining it to 0 in FreeRTOSConfig.h for better security."
        #وصف_ڪريو configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    1
    #جيڪڏهن_پورو
#وإلا
    #إذا ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) )
        #غلطي configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not supported with MPU wrappers نسخو 2 ( configUSE_MPU_WRAPPERS_V1 == 0 ).
    #جيڪڏهن_پورو
#جيڪڏهن_پورو

/* Prototype of all Interrupt Service Routines (ISRs). */
تعريفنوع فراغ ( * پورٽ_ISR_t )( فراغ );

/* Constants required to access and manipulate the NVIC. */
#وصف_ڪريو پورٽ_NVIC_SYSTICK_CTRL_REG                 ( *( ( متطاير uint32_t * ) 0xe000e010 ) )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_ڀريو_REG                 ( *( ( متطاير uint32_t * ) 0xe000e014 ) )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_CURRENT_قدر_REG        ( *( ( متطاير uint32_t * ) 0xe000e018 ) )
#وصف_ڪريو پورٽ_NVIC_SHPR3_REG                        ( *( ( متطاير uint32_t * ) 0xe000ed20 ) )
#وصف_ڪريو پورٽ_NVIC_SHPR2_REG                        ( *( ( متطاير uint32_t * ) 0xe000ed1c ) )
#وصف_ڪريو پورٽ_NVIC_SYS_CTRL_STATE_REG               ( *( ( متطاير uint32_t * ) 0xe000ed24 ) )
#وصف_ڪريو پورٽ_NVIC_MEM_FAULT_ENABLE                 ( 1UL << 16UL )

/* Constants used to detect Cortex-M7 r0p0 and r0p1 cores, and ensure
 * that a work around is active for errata 837070. */
#وصف_ڪريو پورٽ_CPUID                                 ( *( ( متطاير uint32_t * ) 0xE000ed00 ) )
#وصف_ڪريو پورٽ_CORTEX_M7_r0p1_ID                     ( 0x410FC271UL )
#وصف_ڪريو پورٽ_CORTEX_M7_r0p0_ID                     ( 0x410FC270UL )

/* Constants required to access and manipulate the MPU. */
#وصف_ڪريو پورٽ_MPU_TYPE_REG                          ( *( ( متطاير uint32_t * ) 0xe000ed90 ) )
#وصف_ڪريو پورٽ_MPU_REGION_بنياد_پتو_REG           ( *( ( متطاير uint32_t * ) 0xe000ed9C ) )
#وصف_ڪريو پورٽ_MPU_REGION_ATTRIBUTE_REG              ( *( ( متطاير uint32_t * ) 0xe000edA0 ) )
#وصف_ڪريو پورٽ_MPU_CTRL_REG                          ( *( ( متطاير uint32_t * ) 0xe000ed94 ) )
#وصف_ڪريو پورٽ_EXPECTED_MPU_TYPE_قدر               ( config_ڪل_MPU_REGIONS << 8UL )
#وصف_ڪريو پورٽ_MPU_ENABLE                            ( 0x01UL )
#وصف_ڪريو پورٽ_MPU_BACKGROUND_ENABLE                 ( 1UL << 2UL )
#وصف_ڪريو پورٽ_PRIVILEGED_EXECUTION_شروعات_پتو    ( 0UL )
#وصف_ڪريو پورٽ_MPU_REGION_VALID                      ( 0x10UL )
#وصف_ڪريو پورٽ_MPU_REGION_ENABLE                     ( 0x01UL )
#وصف_ڪريو پورٽ_PERIPHERALS_شروعات_پتو             0x40000000UL
#وصف_ڪريو پورٽ_PERIPHERALS_پڇاڙي_پتو               0x5FFFFFFFUL

/* Constants required to access and manipulate the SysTick and other FreeRTOS
 * interrupts. */
#وصف_ڪريو پورٽ_NVIC_SYSTICK_CLK                      ( 0x00000004UL )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_INT                      ( 0x00000002UL )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_ENABLE                   ( 0x00000001UL )
#وصف_ڪريو پورٽ_MIN_مداخلت_ترجيح                ( 255UL )
#وصف_ڪريو پورٽ_NVIC_PENDSV_PRI                       ( ( ( uint32_t ) پورٽ_MIN_مداخلت_ترجيح ) << 16UL )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_PRI                      ( ( ( uint32_t ) پورٽ_MIN_مداخلت_ترجيح ) << 24UL )
#وصف_ڪريو پورٽ_NVIC_SVC_PRI                          ( ( ( uint32_t ) config_MAX_SYSCALL_مداخلت_ترجيح - 1UL ) << 24UL )

/* Constants required to manipulate the VFP. */
#وصف_ڪريو پورٽ_FPCCR                                 ( ( متطاير uint32_t * ) 0xe000ef34UL ) /* Floating point context control register. */
#وصف_ڪريو پورٽ_ASPEN_AND_LSPEN_بٽ                  ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#وصف_ڪريو پورٽ_INITIAL_XPSR                          ( 0x01000000UL )
#وصف_ڪريو پورٽ_INITIAL_EXC_RETURN                    ( 0xfffffffdUL )
#وصف_ڪريو پورٽ_INITIAL_CONTROL_IF_UNPRIVILEGED       ( 0x03 )
#وصف_ڪريو پورٽ_INITIAL_CONTROL_IF_PRIVILEGED         ( 0x02 )

/* Constants used to check the installation of the FreeRTOS interrupt handlers. */
#وصف_ڪريو پورٽ_SCB_VTOR_REG                          ( *( ( پورٽ_ISR_t ** ) 0xE000ED08 ) )
#وصف_ڪريو پورٽ_ويڪٽر_اشاريو_SVC                      ( 11 )
#وصف_ڪريو پورٽ_ويڪٽر_اشاريو_PENDSV                   ( 14 )

/* Constants required to check the validity of an interrupt priority. */
#وصف_ڪريو پورٽ_پهريون_USER_مداخلت_عدد           ( 16 )
#وصف_ڪريو پورٽ_NVIC_IP_REGISTERS_وٿي_16           ( 0xE000E3F0 )
#وصف_ڪريو پورٽ_AIRCR_REG                             ( *( ( متطاير uint32_t * ) 0xE000ED0C ) )
#وصف_ڪريو پورٽ_MAX_8_ٻٽو_انگ_قدر                       ( ( uint8_t ) 0xff )
#وصف_ڪريو پورٽ_چوٽي_ٻٽو_انگ_جو_BYTE                       ( ( uint8_t ) 0x80 )
#وصف_ڪريو پورٽ_MAX_PRIGROUP_بٽ                     ( ( uint8_t ) 7 )
#وصف_ڪريو پورٽ_ترجيح_گروهه_نقاب                   ( 0x07UL << 8UL )
#وصف_ڪريو پورٽ_PRIGROUP_سرڪايو                        ( 8UL )

/* Constants used during system call enter and exit. */
#وصف_ڪريو پورٽ_PSR_ڍير_PADDING_نقاب                ( 1UL << 9UL )
#وصف_ڪريو پورٽ_EXC_RETURN_ڍير_چوکٺو_TYPE_نقاب      ( 1UL << 4UL )

/* Offsets in the stack to the parameters when inside the SVC handler. */
#وصف_ڪريو پورٽ_وٿي_منزل_LR                          ( 5 )
#وصف_ڪريو پورٽ_وٿي_منزل_PC                          ( 6 )
#وصف_ڪريو پورٽ_وٿي_منزل_PSR                         ( 7 )

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#وصف_ڪريو پورٽ_شروعات_پتو_نقاب                    ( ( ڍير_Type_t ) 0xfffffffeUL )

/* Does addr lie within [start, end] address range? */
#وصف_ڪريو پورٽ_IS_پتو_WITHIN_RANGE( addr, شروعات, پڇاڙي ) \
    ( ( ( addr ) >= ( شروعات ) ) && ( ( addr ) <= ( پڇاڙي ) ) )

/* Is the access request satisfied by the available permissions? */
#وصف_ڪريو پورٽ_IS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#وصف_ڪريو پورٽ_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#وصف_ڪريو پورٽ_جوڙيو_UINT32_WILL_حد_کان_مٿي( a, b )    ( ( a ) > ( پورٽ_UINT32_MAX - ( b ) ) )
/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable.  Note this is not saved as part of the task context as context
 * switches can only occur when uxCriticalNesting is zero. */
PRIVILEGED_معلومات ساكن UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

/*
 * This variable is set to pdTRUE when the scheduler is started.
 */
    PRIVILEGED_معلومات ساكن بنياد_Type_t xSchedulerRunning = pdFALSE;

#جيڪڏهن_پورو /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*
 * Setup the timer to generate the tick interrupts.
 */
فراغ v_تياري_Timer_مداخلت( فراغ ) PRIVILEGED_FUNCTION;

/*
 * Configure a number of standard MPU regions that are used by all tasks.
 */
ساكن فراغ prv_تياري_MPU( فراغ ) PRIVILEGED_FUNCTION;

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
ساكن فراغ prv_شروعات_پهريون_Task( فراغ ) PRIVILEGED_FUNCTION;

/*
 * Return the smallest MPU region size that a given number of bytes will fit
 * into.  The region size is returned as the value that should be programmed
 * into the region attribute register for that region.
 */
ساكن uint32_t prv_Get_MPURegion_سائيز_Setting( uint32_t ul_Actual_سائيز_اندريون_بائيٽون ) PRIVILEGED_FUNCTION;

/*
 * Standard FreeRTOS exception handlers.
 */
فراغ x_پورٽ_Pend_SVHandler( فراغ ) PRIVILEGED_FUNCTION;
فراغ x_پورٽ_Sys_Tick_Handler( فراغ ) PRIVILEGED_FUNCTION;
فراغ v_پورٽ_SVCHandler( فراغ ) PRIVILEGED_FUNCTION;

/*
 * Starts the scheduler by restoring the context of the first task to run.
 */
ساكن فراغ prv_Restore_Context_جو_پهريون_Task( فراغ ) PRIVILEGED_FUNCTION;

/*
 * C portion of the SVC handler.  The SVC handler is split between an asm entry
 * and a C wrapper for simplicity of coding and maintenance.
 */
فراغ vSVCHandler_C( uint32_t * pulRegisters ) __attribute__( ( استعمال_ٿيل ) ) PRIVILEGED_FUNCTION;

/*
 * Function to enable the VFP.
 */
ساكن فراغ v_پورٽ_Enable_VFP( فراغ );

/*
 * Utility function.
 */
ساكن uint32_t prv_پورٽ_Get_IPSR( فراغ );

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#إذا ( configASSERT_DEFINED == 1 )
    ساكن uint8_t uc_Max_Sys_Call_ترجيح = 0;
    ساكن uint32_t ulMaxPRIGROUPValue = 0;
    ساكن ثابت متطاير uint8_t * ثابت pc_مداخلت_ترجيح_Registers = ( ثابت uint8_t * ) پورٽ_NVIC_IP_REGISTERS_وٿي_16;
#جيڪڏهن_پورو /* configASSERT_DEFINED */

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
بنياد_Type_t xIsPrivileged( فراغ );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 *
 * Bit 0 of the CONTROL register defines the privilege level of Thread Mode.
 *  Bit[0] = 0 --> The processor is running privileged
 *  Bit[0] = 1 --> The processor is running unprivileged.
 */
فراغ vResetPrivilege( فراغ );

/**
 * @brief Make a task unprivileged.
 */
فراغ v_پورٽ_Switch_منزل_User_گهڻائي( فراغ );

/**
 * @brief Enter critical section.
 */
#إذا ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    فراغ v_پورٽ_Enter_Critical( فراغ ) FREERTOS_SYSTEM_CALL;
#وإلا
    فراغ v_پورٽ_Enter_Critical( فراغ ) PRIVILEGED_FUNCTION;
#جيڪڏهن_پورو

/**
 * @brief Exit from critical section.
 */
#إذا ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    فراغ v_پورٽ_Exit_Critical( فراغ ) FREERTOS_SYSTEM_CALL;
#وإلا
    فراغ v_پورٽ_Exit_Critical( فراغ ) PRIVILEGED_FUNCTION;
#جيڪڏهن_پورو

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Triggers lazy stacking of FPU registers.
 */
    ساكن فراغ prvTriggerLazyStacking( فراغ ) PRIVILEGED_FUNCTION;

#جيڪڏهن_پورو /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the system call stack so that upon returning from
 * SVC, the system call stack is used.
 *
 * @param pulTaskStack The current SP when the SVC was raised.
 * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
 * @param ucSystemCallNumber The system call number of the system call.
 */
    فراغ vSystemCallEnter( uint32_t * pul_Task_ڍير,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_عدد ) PRIVILEGED_FUNCTION;

#جيڪڏهن_پورو /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Raise SVC for exiting from a system call.
 */
    فراغ vRequestSystemCallExit( فراغ ) PRIVILEGED_FUNCTION;

#جيڪڏهن_پورو /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the task stack so that upon returning from
 * SVC, the task stack is used again.
 *
 * @param pulSystemCallStack The current SP when the SVC was raised.
 * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
 */
    فراغ vSystemCallExit( uint32_t * pul_System_Call_ڍير,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#جيڪڏهن_پورو /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
بنياد_Type_t x_پورٽ_Is_Task_Privileged( فراغ ) PRIVILEGED_FUNCTION;
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters,
                                     بنياد_Type_t x_لاڳيتو_Privileged,
                                     xMPU_SETTINGS * xMPUSettings )
{
    إذا( x_لاڳيتو_Privileged == pdTRUE )
    {
        xMPUSettings->ulTaskFlags |= پورٽ_TASK_IS_PRIVILEGED_FLAG;
        xMPUSettings->ulContext[ 0 ] = پورٽ_INITIAL_CONTROL_IF_PRIVILEGED;
    }
    وإلا
    {
        xMPUSettings->ulTaskFlags &= ( ~( پورٽ_TASK_IS_PRIVILEGED_FLAG ) );
        xMPUSettings->ulContext[ 0 ] = پورٽ_INITIAL_CONTROL_IF_UNPRIVILEGED;
    }

    xMPUSettings->ulContext[ 1 ] = 0x04040404;                                        /* r4. */
    xMPUSettings->ulContext[ 2 ] = 0x05050505;                                        /* r5. */
    xMPUSettings->ulContext[ 3 ] = 0x06060606;                                        /* r6. */
    xMPUSettings->ulContext[ 4 ] = 0x07070707;                                        /* r7. */
    xMPUSettings->ulContext[ 5 ] = 0x08080808;                                        /* r8. */
    xMPUSettings->ulContext[ 6 ] = 0x09090909;                                        /* r9. */
    xMPUSettings->ulContext[ 7 ] = 0x10101010;                                        /* r10. */
    xMPUSettings->ulContext[ 8 ] = 0x11111111;                                        /* r11. */
    xMPUSettings->ulContext[ 9 ] = پورٽ_INITIAL_EXC_RETURN;                            /* EXC_RETURN. */

    xMPUSettings->ulContext[ 10 ] = ( uint32_t ) ( px_چوٽي_جو_ڍير - 8 );                /* PSP with the hardware saved stack. */
    xMPUSettings->ulContext[ 11 ] = ( uint32_t ) pvParameters;                        /* r0. */
    xMPUSettings->ulContext[ 12 ] = 0x01010101;                                       /* r1. */
    xMPUSettings->ulContext[ 13 ] = 0x02020202;                                       /* r2. */
    xMPUSettings->ulContext[ 14 ] = 0x03030303;                                       /* r3. */
    xMPUSettings->ulContext[ 15 ] = 0x12121212;                                       /* r12. */
    xMPUSettings->ulContext[ 16 ] = 0;                                                /* LR. */
    xMPUSettings->ulContext[ 17 ] = ( ( uint32_t ) px_ڪوڊ ) & پورٽ_شروعات_پتو_نقاب; /* PC. */
    xMPUSettings->ulContext[ 18 ] = پورٽ_INITIAL_XPSR;                                 /* xPSR. */

    #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        /* Ensure that the system call stack is double word aligned. */
        xMPUSettings->x_System_Call_ڍير_Info.pul_System_Call_ڍير = &( xMPUSettings->x_System_Call_ڍير_Info.ul_System_Call_ڍير_بفر[ config_SYSTEM_CALL_ڍير_سائيز - 1 ] );
        xMPUSettings->x_System_Call_ڍير_Info.pul_System_Call_ڍير = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_ڍير_Info.pul_System_Call_ڍير ) &
                                                                                 ( uint32_t ) ( ~( پورٽ_BYTE_ALIGNMENT_نقاب ) ) );

        /* This is not NULL only for the duration of a system call. */
        xMPUSettings->x_System_Call_ڍير_Info.pul_Task_ڍير = عدم;
    }
    #جيڪڏهن_پورو /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    أرجع &( xMPUSettings->ulContext[ 19 ] );
}
/*-----------------------------------------------------------*/

فراغ vSVCHandler_C( uint32_t * pulParam )
{
    uint8_t ucSVCNumber;
    uint32_t ulPC;

    #إذا ( configUSE_MPU_WRAPPERS_V1 == 1 )
        uint32_t ulReg;
    #جيڪڏهن_پورو /* #if ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #إذا ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) )
        خارجي uint32_t __syscalls_flash_start__;
        خارجي uint32_t __syscalls_flash_end__;
    #جيڪڏهن_پورو /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) ) */

    /* The stack contains: r0, r1, r2, r3, r12, LR, PC and xPSR. The first
     * argument (r0) is pulParam[ 0 ]. */
    ulPC = pulParam[ پورٽ_وٿي_منزل_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    بدل( ucSVCNumber )
    {
        حالة پورٽ_SVC_شروعات_SCHEDULER:
            prv_Restore_Context_جو_پهريون_Task();
            اكسر;

        حالة پورٽ_SVC_YIELD:
            پورٽ_NVIC_INT_CTRL_REG = پورٽ_NVIC_PENDSVSET_ٻٽو_انگ;

            /* Barriers are normally not required
             * but do ensure the code is completely
             * within the specified behaviour for the
             * architecture. */
            __asm متطاير ( "dsb" );
            __asm متطاير ( "isb" );

            اكسر;

    #إذا ( configUSE_MPU_WRAPPERS_V1 == 1 )
        #إذا ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 )
            حالة پورٽ_SVC_RAISE_PRIVILEGE: /* Only raise the privilege, if the
                                           * svc was raised from any of the
                                           * system calls. */

                إذا( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
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

                اكسر;
        #وإلا /* if ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
            حالة پورٽ_SVC_RAISE_PRIVILEGE:
                __asm
                {
                    /* *INDENT-OFF* */
                    mrs ulReg, control /* Obtain current control value. */
                    bic ulReg, # 1     /* Set privilege bit. */
                    msr control, ulReg /* Write back new control value. */
                    /* *INDENT-ON* */
                }
                اكسر;
        #جيڪڏهن_پورو /* #if( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
    #جيڪڏهن_پورو /* #if ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

        افتراضي: /* Unknown SVC call. */
            اكسر;
    }
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    __asm فراغ prvTriggerLazyStacking( فراغ ) /* PRIVILEGED_FUNCTION */
    {
    /* *INDENT-OFF* */
        PRESERVE8

        vpush {s0} /* Trigger lazy stacking. */
        vpop  {s0} /* Nullify the affect of the above instruction. */

    /* *INDENT-ON* */
    }

#جيڪڏهن_پورو /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    فراغ vSystemCallEnter( uint32_t * pul_Task_ڍير,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_عدد ) /* PRIVILEGED_FUNCTION */
    {
        خارجي TaskHandle_t pxCurrentTCB;
        خارجي UBaseType_t uxSystemCallImplementations[ انگ_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_ڍير;
        uint32_t ul_Hardware_Saved_Exception_چوکٺو_سائيز, ulSystemCallLocation, i, r1;
        خارجي uint32_t __syscalls_flash_start__;
        خارجي uint32_t __syscalls_flash_end__;

        ulSystemCallLocation = pul_Task_ڍير[ پورٽ_وٿي_منزل_PC ];
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
        إذا( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_ڍير_Info.pul_Task_ڍير == عدم ) &&
            ( uxSystemCallImplementations[ uc_System_Call_عدد ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_ڍير = pxMpuSettings->x_System_Call_ڍير_Info.pul_System_Call_ڍير;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            إذا( ( ulLR & پورٽ_EXC_RETURN_ڍير_چوکٺو_TYPE_نقاب ) == 0UL )
            {
                /* Extended frame i.e. FPU in use. */
                ul_Hardware_Saved_Exception_چوکٺو_سائيز = 26;
                prvTriggerLazyStacking();
            }
            وإلا
            {
                /* Standard frame i.e. FPU not in use. */
                ul_Hardware_Saved_Exception_چوکٺو_سائيز = 8;
            }

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_ڍير = pul_System_Call_ڍير - ul_Hardware_Saved_Exception_چوکٺو_سائيز;

            /* Copy the stack frame. */
            لكل( i = 0; i < ul_Hardware_Saved_Exception_چوکٺو_سائيز; i++ )
            {
                pul_System_Call_ڍير[ i ] = pul_Task_ڍير[ i ];
            }

            /* Use the pulSystemCallStack in thread mode. */
            __asm
            {
                msr psp, pul_System_Call_ڍير
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
            pxMpuSettings->x_System_Call_ڍير_Info.pul_Task_ڍير = pul_Task_ڍير + ul_Hardware_Saved_Exception_چوکٺو_سائيز;

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_ڍير_Info.ul_Link_رجسٽر_At_System_Call_داخلا = pul_Task_ڍير[ پورٽ_وٿي_منزل_LR ];

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_ڍير[ پورٽ_وٿي_منزل_PC ] = uxSystemCallImplementations[ uc_System_Call_عدد ];
            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_ڍير[ پورٽ_وٿي_منزل_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            إذا( ( pul_Task_ڍير[ پورٽ_وٿي_منزل_PSR ] & پورٽ_PSR_ڍير_PADDING_نقاب ) == پورٽ_PSR_ڍير_PADDING_نقاب )
            {
                pxMpuSettings->ulTaskFlags |= پورٽ_ڍير_چوکٺو_HAS_PADDING_FLAG;
            }
            وإلا
            {
                pxMpuSettings->ulTaskFlags &= ( ~پورٽ_ڍير_چوکٺو_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_ڍير[ پورٽ_وٿي_منزل_PSR ] &= ( ~پورٽ_PSR_ڍير_PADDING_نقاب );
        }
    }

#جيڪڏهن_پورو /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    __asm فراغ vRequestSystemCallExit( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        PRESERVE8

        svc #portSVC_SYSTEM_CALL_EXIT
    }

#جيڪڏهن_پورو /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    فراغ vSystemCallExit( uint32_t * pul_System_Call_ڍير,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        خارجي TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_ڍير;
        uint32_t ul_Hardware_Saved_Exception_چوکٺو_سائيز, ulSystemCallLocation, i, r1;
        خارجي uint32_t __privileged_functions_start__;
        خارجي uint32_t __privileged_functions_end__;

        ulSystemCallLocation = pul_System_Call_ڍير[ پورٽ_وٿي_منزل_PC ];
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
        إذا( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_ڍير_Info.pul_Task_ڍير != عدم ) )
        {
            pul_Task_ڍير = pxMpuSettings->x_System_Call_ڍير_Info.pul_Task_ڍير;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            إذا( ( ulLR & پورٽ_EXC_RETURN_ڍير_چوکٺو_TYPE_نقاب ) == 0UL )
            {
                /* Extended frame i.e. FPU in use. */
                ul_Hardware_Saved_Exception_چوکٺو_سائيز = 26;
                prvTriggerLazyStacking();
            }
            وإلا
            {
                /* Standard frame i.e. FPU not in use. */
                ul_Hardware_Saved_Exception_چوکٺو_سائيز = 8;
            }

            /* Make space on the task stack for the stack frame. */
            pul_Task_ڍير = pul_Task_ڍير - ul_Hardware_Saved_Exception_چوکٺو_سائيز;

            /* Copy the stack frame. */
            لكل( i = 0; i < ul_Hardware_Saved_Exception_چوکٺو_سائيز; i++ )
            {
                pul_Task_ڍير[ i ] = pul_System_Call_ڍير[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm
            {
                msr psp, pul_Task_ڍير
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
            pul_Task_ڍير[ پورٽ_وٿي_منزل_PC ] = pxMpuSettings->x_System_Call_ڍير_Info.ul_Link_رجسٽر_At_System_Call_داخلا;
            /* Ensure that LR has a valid value.*/
            pul_Task_ڍير[ پورٽ_وٿي_منزل_LR ] = pxMpuSettings->x_System_Call_ڍير_Info.ul_Link_رجسٽر_At_System_Call_داخلا;

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            إذا( ( pxMpuSettings->ulTaskFlags & پورٽ_ڍير_چوکٺو_HAS_PADDING_FLAG ) == پورٽ_ڍير_چوکٺو_HAS_PADDING_FLAG )
            {
                pul_Task_ڍير[ پورٽ_وٿي_منزل_PSR ] |= پورٽ_PSR_ڍير_PADDING_نقاب;
            }
            وإلا
            {
                pul_Task_ڍير[ پورٽ_وٿي_منزل_PSR ] &= ( ~پورٽ_PSR_ڍير_PADDING_نقاب );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_ڍير_Info.pul_Task_ڍير = عدم;
        }
    }

#جيڪڏهن_پورو /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_Is_Task_Privileged( فراغ ) /* PRIVILEGED_FUNCTION */
{
    بنياد_Type_t xTaskIsPrivileged = pdFALSE;
    ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( عدم ); /* Calling task's MPU settings. */

    إذا( ( xTaskMpuSettings->ulTaskFlags & پورٽ_TASK_IS_PRIVILEGED_FLAG ) == پورٽ_TASK_IS_PRIVILEGED_FLAG )
    {
        xTaskIsPrivileged = pdTRUE;
    }

    أرجع xTaskIsPrivileged;
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    __asm فراغ v_پورٽ_SVCHandler( فراغ )
    {
        خارجي vSVCHandler_C
        خارجي vSystemCallEnter
        خارجي vSystemCallExit

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

#وإلا /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    __asm فراغ v_پورٽ_SVCHandler( فراغ )
    {
        خارجي vSVCHandler_C

/* *INDENT-OFF* */
        PRESERVE8

    /* Assumes psp was in use. */
    #جيڪڏهن_وصف_نه_ٿيل USE_PROCESS_ڍير   /* Code should not be required if a main() is using the process stack. */
        tst lr, # 4
        ite eq
        mrseq r0, msp
        mrsne r0, psp
    #وإلا
        mrs r0, psp
    #جيڪڏهن_پورو

    b vSVCHandler_C
/* *INDENT-ON* */
    }

#جيڪڏهن_پورو /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

__asm فراغ prv_Restore_Context_جو_پهريون_Task( فراغ )
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
    جوڙيو r2, r2, #4              /* r2 = Second item in the TCB which is xMPUSettings. */

    dmb                         /* Complete outstanding transfers before disabling MPU. */
    ldr r0, =0xe000ed94         /* MPU_CTRL register. */
    ldr r3, [r0]                /* Read the value of MPU_CTRL. */
    bic r3, r3, # 1             /* r3 = r3 & ~1 i.e. Clear the bit 0 in r3. */
    str r3, [r0]                /* Disable MPU. */

    ldr r0, =0xe000ed9c         /* Region Base Address register. */
    ldmia r2!, {r4-r11}         /* Read 4 sets of MPU registers [MPU Region # 0 - 3]. */
    stmia r0, {r4-r11}          /* Write 4 sets of MPU registers [MPU Region # 0 - 3]. */

    #إذا ( config_ڪل_MPU_REGIONS == 16 )
        ldmia r2!, {r4-r11}     /* Read 4 sets of MPU registers [MPU Region # 4 - 7]. */
        stmia r0, {r4-r11}      /* Write 4 sets of MPU registers. [MPU Region # 4 - 7]. */
        ldmia r2!, {r4-r11}     /* Read 4 sets of MPU registers [MPU Region # 8 - 11]. */
        stmia r0, {r4-r11}      /* Write 4 sets of MPU registers. [MPU Region # 8 - 11]. */
    #جيڪڏهن_پورو /* configTOTAL_MPU_REGIONS == 16. */

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
بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    /* configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to 0.
     * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
    configASSERT( config_MAX_SYSCALL_مداخلت_ترجيح );

    /* Errata 837070 workaround must only be enabled on Cortex-M7 r0p0
     * and r0p1 cores. */
    #إذا ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        configASSERT( ( پورٽ_CPUID == پورٽ_CORTEX_M7_r0p1_ID ) || ( پورٽ_CPUID == پورٽ_CORTEX_M7_r0p0_ID ) );
    #وإلا

        /* When using this port on a Cortex-M7 r0p0 or r0p1 core, define
         * configENABLE_ERRATA_837070_WORKAROUND to 1 in your
         * FreeRTOSConfig.h. */
        configASSERT( پورٽ_CPUID != پورٽ_CORTEX_M7_r0p1_ID );
        configASSERT( پورٽ_CPUID != پورٽ_CORTEX_M7_r0p0_ID );
    #جيڪڏهن_پورو

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
    #إذا ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        ثابت پورٽ_ISR_t * ثابت px_ويڪٽر_جدول = پورٽ_SCB_VTOR_REG;

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
        configASSERT( px_ويڪٽر_جدول[ پورٽ_ويڪٽر_اشاريو_SVC ] == v_پورٽ_SVCHandler );
        configASSERT( px_ويڪٽر_جدول[ پورٽ_ويڪٽر_اشاريو_PENDSV ] == x_پورٽ_Pend_SVHandler );
    }
    #جيڪڏهن_پورو /* configCHECK_HANDLER_INSTALLATION */

    #إذا ( configASSERT_DEFINED == 1 )
    {
        متطاير uint8_t uc_Original_ترجيح;
        متطاير uint32_t ul_Implemented_Prio_بٽ = 0;
        متطاير uint8_t * ثابت puc_پهريون_User_ترجيح_رجسٽر = ( uint8_t * ) ( پورٽ_NVIC_IP_REGISTERS_وٿي_16 + پورٽ_پهريون_USER_مداخلت_عدد );
        متطاير uint8_t uc_Max_ترجيح_قدر;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
         * functions can be called.  ISR safe functions are those that end in
         * "FromISR".  FreeRTOS maintains separate thread and ISR API functions to
         * ensure interrupt entry is as fast and simple as possible.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_ترجيح = *puc_پهريون_User_ترجيح_رجسٽر;

        /* Determine the number of priority bits available.  First write to all
         * possible bits. */
        *puc_پهريون_User_ترجيح_رجسٽر = پورٽ_MAX_8_ٻٽو_انگ_قدر;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ترجيح_قدر = *puc_پهريون_User_ترجيح_رجسٽر;

        /* Use the same mask on the maximum system call priority. */
        uc_Max_Sys_Call_ترجيح = config_MAX_SYSCALL_مداخلت_ترجيح & uc_Max_ترجيح_قدر;

        /* Check that the maximum system call priority is nonzero after
         * accounting for the number of priority bits supported by the
         * hardware. A priority of 0 is invalid because setting the BASEPRI
         * register to 0 unmasks all interrupts, and interrupts with priority 0
         * cannot be masked using BASEPRI.
         * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( uc_Max_Sys_Call_ترجيح );

        /* Check that the bits not implemented in hardware are zero in
         * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( config_MAX_SYSCALL_مداخلت_ترجيح & ( ~uc_Max_ترجيح_قدر ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
         * of bits read back. */

        طالما( ( uc_Max_ترجيح_قدر & پورٽ_چوٽي_ٻٽو_انگ_جو_BYTE ) == پورٽ_چوٽي_ٻٽو_انگ_جو_BYTE )
        {
            ul_Implemented_Prio_بٽ++;
            uc_Max_ترجيح_قدر <<= ( uint8_t ) 0x01;
        }

        إذا( ul_Implemented_Prio_بٽ == 8 )
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
            configASSERT( ( config_MAX_SYSCALL_مداخلت_ترجيح & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        وإلا
        {
            ulMaxPRIGROUPValue = پورٽ_MAX_PRIGROUP_بٽ - ul_Implemented_Prio_بٽ;
        }

        /* Shift the priority group value back to its position within the AIRCR
         * register. */
        ulMaxPRIGROUPValue <<= پورٽ_PRIGROUP_سرڪايو;
        ulMaxPRIGROUPValue &= پورٽ_ترجيح_گروهه_نقاب;

        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_پهريون_User_ترجيح_رجسٽر = uc_Original_ترجيح;
    }
    #جيڪڏهن_پورو /* configASSERT_DEFINED */

    /* Make PendSV and SysTick the lowest priority interrupts, and configure
     * SVCall for sufficient preemption priority. */
    پورٽ_NVIC_SHPR3_REG |= پورٽ_NVIC_PENDSV_PRI;
    پورٽ_NVIC_SHPR3_REG |= پورٽ_NVIC_SYSTICK_PRI;
    پورٽ_NVIC_SHPR2_REG = پورٽ_NVIC_SVC_PRI;

    /* Configure the regions in the MPU that are common to all tasks. */
    prv_تياري_MPU();

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_تياري_Timer_مداخلت();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        xSchedulerRunning = pdTRUE;
    }
    #جيڪڏهن_پورو /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    /* Ensure the VFP is enabled - it should be anyway. */
    v_پورٽ_Enable_VFP();

    /* Lazy save always. */
    *( پورٽ_FPCCR ) |= پورٽ_ASPEN_AND_LSPEN_بٽ;

    /* Start the first task. */
    prv_شروعات_پهريون_Task();

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

__asm فراغ prv_شروعات_پهريون_Task( فراغ )
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
    svc پورٽ_SVC_شروعات_SCHEDULER /* System call to start first task. */
    nop
    nop
/* *INDENT-ON* */
}

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Enter_Critical( فراغ )
{
    #إذا ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٽ_RAISE_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();

            پورٽ_DISABLE_INTERRUPTS();
            uxCriticalNesting++;
            پورٽ_يادگيري_BARRIER();

            پورٽ_RESET_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();
        }
        وإلا
        {
            پورٽ_DISABLE_INTERRUPTS();
            uxCriticalNesting++;
        }
    #وإلا /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        پورٽ_DISABLE_INTERRUPTS();
        uxCriticalNesting++;
    #جيڪڏهن_پورو /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Exit_Critical( فراغ )
{
    #إذا ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٽ_RAISE_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();

            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            إذا( uxCriticalNesting == 0 )
            {
                پورٽ_ENABLE_INTERRUPTS();
            }

            پورٽ_يادگيري_BARRIER();

            پورٽ_RESET_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();
        }
        وإلا
        {
            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            إذا( uxCriticalNesting == 0 )
            {
                پورٽ_ENABLE_INTERRUPTS();
            }
        }
    #وإلا /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        configASSERT( uxCriticalNesting );
        uxCriticalNesting--;

        إذا( uxCriticalNesting == 0 )
        {
            پورٽ_ENABLE_INTERRUPTS();
        }
    #جيڪڏهن_پورو /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

__asm فراغ x_پورٽ_Pend_SVHandler( فراغ )
{
    خارجي uxCriticalNesting;
    خارجي pxCurrentTCB;
    خارجي vTaskSwitchContext;

/* *INDENT-OFF* */
    PRESERVE8

    ldr r3, =pxCurrentTCB               /* r3 = &( pxCurrentTCB ). */
    ldr r2, [r3]                        /* r2 = pxCurrentTCB. */
    ldr r1, [r2]                        /* r1 = Location where the context should be saved. */

    /*------------ Save Context. ----------- */
    mrs r3, control
    mrs r0, psp
    isb

    جوڙيو r0, r0, #0x20                   /* Move r0 to location where s0 is saved. */
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
#إذا ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
    cpsid i                             /* ARM Cortex-M7 r0p1 Errata 837070 workaround. */
#جيڪڏهن_پورو
    msr basepri, r0
    dsb
    isb
#إذا ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
    cpsie i                             /* ARM Cortex-M7 r0p1 Errata 837070 workaround. */
#جيڪڏهن_پورو
    bl vTaskSwitchContext
    mov r0, #0
    msr basepri, r0

    /*------------ Program MPU. ------------ */
    ldr r3, =pxCurrentTCB               /* r3 = &( pxCurrentTCB ). */
    ldr r2, [r3]                        /* r2 = pxCurrentTCB. */
    جوڙيو r2, r2, #4                      /* r2 = Second item in the TCB which is xMPUSettings. */

    dmb                                 /* Complete outstanding transfers before disabling MPU. */
    ldr r0, =0xe000ed94                 /* MPU_CTRL register. */
    ldr r3, [r0]                        /* Read the value of MPU_CTRL. */
    bic r3, #1                          /* r3 = r3 & ~1 i.e. Clear the bit 0 in r3. */
    str r3, [r0]                        /* Disable MPU. */

    ldr r0, =0xe000ed9c                 /* Region Base Address register. */
    ldmia r2!, {r4-r11}                 /* Read 4 sets of MPU registers [MPU Region # 0 - 3]. */
    stmia r0, {r4-r11}                  /* Write 4 sets of MPU registers [MPU Region # 0 - 3]. */

#إذا ( config_ڪل_MPU_REGIONS == 16 )
    ldmia r2!, {r4-r11}                 /* Read 4 sets of MPU registers [MPU Region # 4 - 7]. */
    stmia r0, {r4-r11}                  /* Write 4 sets of MPU registers. [MPU Region # 4 - 7]. */
    ldmia r2!, {r4-r11}                 /* Read 4 sets of MPU registers [MPU Region # 8 - 11]. */
    stmia r0, {r4-r11}                  /* Write 4 sets of MPU registers. [MPU Region # 8 - 11]. */
#جيڪڏهن_پورو /* configTOTAL_MPU_REGIONS == 16. */

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

فراغ x_پورٽ_Sys_Tick_Handler( فراغ )
{
    uint32_t ulDummy;

    ulDummy = پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_منزل_SCHEDULER();
            /* Pend a context switch. */
            پورٽ_NVIC_INT_CTRL_REG = پورٽ_NVIC_PENDSVSET_ٻٽو_انگ;
        }
        وإلا
        {
            traceISR_EXIT();
        }
    }
    پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( ulDummy );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__weak فراغ v_تياري_Timer_مداخلت( فراغ )
{
    /* Reset the SysTick. */
    پورٽ_NVIC_SYSTICK_CTRL_REG = 0UL;
    پورٽ_NVIC_SYSTICK_CURRENT_قدر_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    پورٽ_NVIC_SYSTICK_ڀريو_REG = ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ ) - 1UL;
    پورٽ_NVIC_SYSTICK_CTRL_REG = پورٽ_NVIC_SYSTICK_CLK | پورٽ_NVIC_SYSTICK_INT | پورٽ_NVIC_SYSTICK_ENABLE;
}
/*-----------------------------------------------------------*/

__asm فراغ v_پورٽ_Enable_VFP( فراغ )
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

ساكن فراغ prv_تياري_MPU( فراغ )
{
    خارجي uint32_t __privileged_functions_start__;
    خارجي uint32_t __privileged_functions_end__;
    خارجي uint32_t __FLASH_segment_start__;
    خارجي uint32_t __FLASH_segment_end__;
    خارجي uint32_t __privileged_data_start__;
    خارجي uint32_t __privileged_data_end__;

    /* The only permitted number of regions are 8 or 16. */
    configASSERT( ( config_ڪل_MPU_REGIONS == 8 ) || ( config_ڪل_MPU_REGIONS == 16 ) );

    /* Ensure that the configTOTAL_MPU_REGIONS is configured correctly. */
    configASSERT( پورٽ_MPU_TYPE_REG == پورٽ_EXPECTED_MPU_TYPE_قدر );

    /* Check the expected MPU is present. */
    إذا( پورٽ_MPU_TYPE_REG == پورٽ_EXPECTED_MPU_TYPE_قدر )
    {
        /* First setup the unprivileged flash for unprivileged read only access. */
        پورٽ_MPU_REGION_بنياد_پتو_REG = ( ( uint32_t ) __FLASH_segment_start__ ) | /* Base address. */
                                          ( پورٽ_MPU_REGION_VALID ) |
                                          ( پورٽ_UNPRIVILEGED_FLASH_REGION );

        پورٽ_MPU_REGION_ATTRIBUTE_REG = ( پورٽ_MPU_REGION_READ_ONLY ) |
                                       ( ( configTEX_S_C_B_FLASH & پورٽ_MPU_RASR_TEX_S_C_B_نقاب ) << پورٽ_MPU_RASR_TEX_S_C_B_LOCATION ) |
                                       ( prv_Get_MPURegion_سائيز_Setting( ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__ ) ) |
                                       ( پورٽ_MPU_REGION_ENABLE );

        /* Setup the privileged flash for privileged only access.  This is where
         * the kernel code is placed. */
        پورٽ_MPU_REGION_بنياد_پتو_REG = ( ( uint32_t ) __privileged_functions_start__ ) | /* Base address. */
                                          ( پورٽ_MPU_REGION_VALID ) |
                                          ( پورٽ_PRIVILEGED_FLASH_REGION );

        پورٽ_MPU_REGION_ATTRIBUTE_REG = ( پورٽ_MPU_REGION_PRIVILEGED_READ_ONLY ) |
                                       ( ( configTEX_S_C_B_FLASH & پورٽ_MPU_RASR_TEX_S_C_B_نقاب ) << پورٽ_MPU_RASR_TEX_S_C_B_LOCATION ) |
                                       ( prv_Get_MPURegion_سائيز_Setting( ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__ ) ) |
                                       ( پورٽ_MPU_REGION_ENABLE );

        /* Setup the privileged data RAM region.  This is where the kernel data
         * is placed. */
        پورٽ_MPU_REGION_بنياد_پتو_REG = ( ( uint32_t ) __privileged_data_start__ ) | /* Base address. */
                                          ( پورٽ_MPU_REGION_VALID ) |
                                          ( پورٽ_PRIVILEGED_RAM_REGION );

        پورٽ_MPU_REGION_ATTRIBUTE_REG = ( پورٽ_MPU_REGION_PRIVILEGED_READ_WRITE ) |
                                       ( پورٽ_MPU_REGION_EXECUTE_NEVER ) |
                                       ( ( configTEX_S_C_B_SRAM & پورٽ_MPU_RASR_TEX_S_C_B_نقاب ) << پورٽ_MPU_RASR_TEX_S_C_B_LOCATION ) |
                                       prv_Get_MPURegion_سائيز_Setting( ( uint32_t ) __privileged_data_end__ - ( uint32_t ) __privileged_data_start__ ) |
                                       ( پورٽ_MPU_REGION_ENABLE );

        /* By default allow everything to access the general peripherals.  The
         * system peripherals and registers are protected. */
        پورٽ_MPU_REGION_بنياد_پتو_REG = ( پورٽ_PERIPHERALS_شروعات_پتو ) |
                                          ( پورٽ_MPU_REGION_VALID ) |
                                          ( پورٽ_GENERAL_PERIPHERALS_REGION );

        پورٽ_MPU_REGION_ATTRIBUTE_REG = ( پورٽ_MPU_REGION_READ_WRITE | پورٽ_MPU_REGION_EXECUTE_NEVER ) |
                                       ( prv_Get_MPURegion_سائيز_Setting( پورٽ_PERIPHERALS_پڇاڙي_پتو - پورٽ_PERIPHERALS_شروعات_پتو ) ) |
                                       ( پورٽ_MPU_REGION_ENABLE );

        /* Enable the memory fault exception. */
        پورٽ_NVIC_SYS_CTRL_STATE_REG |= پورٽ_NVIC_MEM_FAULT_ENABLE;

        /* Enable the MPU with the background region configured. */
        پورٽ_MPU_CTRL_REG |= ( پورٽ_MPU_ENABLE | پورٽ_MPU_BACKGROUND_ENABLE );
    }
}
/*-----------------------------------------------------------*/

ساكن uint32_t prv_Get_MPURegion_سائيز_Setting( uint32_t ul_Actual_سائيز_اندريون_بائيٽون )
{
    uint32_t ul_Region_سائيز, ul_Return_قدر = 4;

    /* 32 is the smallest region size, 31 is the largest valid value for
     * ulReturnValue. */
    لكل( ul_Region_سائيز = 32UL; ul_Return_قدر < 31UL; ( ul_Region_سائيز <<= 1UL ) )
    {
        إذا( ul_Actual_سائيز_اندريون_بائيٽون <= ul_Region_سائيز )
        {
            اكسر;
        }
        وإلا
        {
            ul_Return_قدر++;
        }
    }

    /* Shift the code by one before returning so it can be written directly
     * into the correct bit position of the attribute register. */
    أرجع( ul_Return_قدر << 1UL );
}
/*-----------------------------------------------------------*/

__asm بنياد_Type_t xIsPrivileged( فراغ )
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

__asm فراغ vResetPrivilege( فراغ )
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

فراغ v_پورٽ_Switch_منزل_User_گهڻائي( فراغ )
{
    /* Load the current task's MPU settings from its TCB. */
    xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( عدم );

    /* Mark the task as unprivileged. */
    xTaskMpuSettings->ulTaskFlags &= ( ~( پورٽ_TASK_IS_PRIVILEGED_FLAG ) );

    /* Lower the processor's privilege level. */
    vResetPrivilege();
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                ثابت بنية x_يادگيري_REGION * ثابت xRegions,
                                ڍير_Type_t * px_Bottom_جو_ڍير,
                                config_ڍير_اونهائي_TYPE ux_ڍير_اونهائي )
{
    خارجي uint32_t __SRAM_segment_start__;
    خارجي uint32_t __SRAM_segment_end__;
    خارجي uint32_t __privileged_data_start__;
    خارجي uint32_t __privileged_data_end__;


    int32_t l_اشاريو;
    uint32_t ul;

    إذا( xRegions == عدم )
    {
        /* No MPU regions are specified so allow access to all RAM. */
        xMPUSettings->xRegion[ 0 ].ul_Region_بنياد_پتو =
            ( ( uint32_t ) __SRAM_segment_start__ ) | /* Base address. */
            ( پورٽ_MPU_REGION_VALID ) |
            ( پورٽ_ڍير_REGION );                     /* Region number. */

        xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
            ( پورٽ_MPU_REGION_READ_WRITE ) |
            ( پورٽ_MPU_REGION_EXECUTE_NEVER ) |
            ( ( configTEX_S_C_B_SRAM & پورٽ_MPU_RASR_TEX_S_C_B_نقاب ) << پورٽ_MPU_RASR_TEX_S_C_B_LOCATION ) |
            ( prv_Get_MPURegion_سائيز_Setting( ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__ ) ) |
            ( پورٽ_MPU_REGION_ENABLE );

        xMPUSettings->xRegionSettings[ 0 ].ul_Region_شروعات_پتو = ( uint32_t ) __SRAM_segment_start__;
        xMPUSettings->xRegionSettings[ 0 ].ul_Region_پڇاڙي_پتو = ( uint32_t ) __SRAM_segment_end__;
        xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                   tskMPU_WRITE_PERMISSION );

        /* Invalidate user configurable regions. */
        لكل( ul = 1UL; ul <= پورٽ_انگ_CONFIGURABLE_REGIONS; ul++ )
        {
            xMPUSettings->xRegion[ ul ].ul_Region_بنياد_پتو = ( ( ul - 1UL ) | پورٽ_MPU_REGION_VALID );
            xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ul_Region_شروعات_پتو = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ul_Region_پڇاڙي_پتو = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
        }
    }
    وإلا
    {
        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid.  At all other
         * times the stack parameters will not be valid and it is assumed that the
         * stack region has already been configured. */
        إذا( ux_ڍير_اونهائي > 0 )
        {
            /* Define the region that allows access to the stack. */
            xMPUSettings->xRegion[ 0 ].ul_Region_بنياد_پتو =
                ( ( uint32_t ) px_Bottom_جو_ڍير ) |
                ( پورٽ_MPU_REGION_VALID ) |
                ( پورٽ_ڍير_REGION ); /* Region number. */

            xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
                ( پورٽ_MPU_REGION_READ_WRITE ) |
                ( پورٽ_MPU_REGION_EXECUTE_NEVER ) |
                ( prv_Get_MPURegion_سائيز_Setting( ux_ڍير_اونهائي * ( config_ڍير_اونهائي_TYPE ) حجم( ڍير_Type_t ) ) ) |
                ( ( configTEX_S_C_B_SRAM & پورٽ_MPU_RASR_TEX_S_C_B_نقاب ) << پورٽ_MPU_RASR_TEX_S_C_B_LOCATION ) |
                ( پورٽ_MPU_REGION_ENABLE );

            xMPUSettings->xRegionSettings[ 0 ].ul_Region_شروعات_پتو = ( uint32_t ) px_Bottom_جو_ڍير;
            xMPUSettings->xRegionSettings[ 0 ].ul_Region_پڇاڙي_پتو = ( uint32_t ) ( ( uint32_t ) ( px_Bottom_جو_ڍير ) +
                                                                                   ( ux_ڍير_اونهائي * ( config_ڍير_اونهائي_TYPE ) حجم( ڍير_Type_t ) ) - 1UL );
            xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                       tskMPU_WRITE_PERMISSION );
        }

        l_اشاريو = 0;

        لكل( ul = 1UL; ul <= پورٽ_انگ_CONFIGURABLE_REGIONS; ul++ )
        {
            إذا( ( xRegions[ l_اشاريو ] ).ul_ڊيگهائي_اندريون_بائيٽون > 0UL )
            {
                /* Translate the generic region definition contained in
                 * xRegions into the CM4 specific MPU settings that are then
                 * stored in xMPUSettings. */
                xMPUSettings->xRegion[ ul ].ul_Region_بنياد_پتو =
                    ( ( uint32_t ) xRegions[ l_اشاريو ].pv_بنياد_پتو ) |
                    ( پورٽ_MPU_REGION_VALID ) |
                    ( ul - 1UL ); /* Region number. */

                xMPUSettings->xRegion[ ul ].ulRegionAttribute =
                    ( prv_Get_MPURegion_سائيز_Setting( xRegions[ l_اشاريو ].ul_ڊيگهائي_اندريون_بائيٽون ) ) |
                    ( xRegions[ l_اشاريو ].ulParameters ) |
                    ( پورٽ_MPU_REGION_ENABLE );

                xMPUSettings->xRegionSettings[ ul ].ul_Region_شروعات_پتو = ( uint32_t ) xRegions[ l_اشاريو ].pv_بنياد_پتو;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_پڇاڙي_پتو = ( uint32_t ) ( ( uint32_t ) xRegions[ l_اشاريو ].pv_بنياد_پتو + xRegions[ l_اشاريو ].ul_ڊيگهائي_اندريون_بائيٽون - 1UL );
                xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;

                إذا( ( ( xRegions[ l_اشاريو ].ulParameters & پورٽ_MPU_REGION_READ_ONLY ) == پورٽ_MPU_REGION_READ_ONLY ) ||
                    ( ( xRegions[ l_اشاريو ].ulParameters & پورٽ_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) == پورٽ_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = tskMPU_READ_PERMISSION;
                }

                إذا( ( xRegions[ l_اشاريو ].ulParameters & پورٽ_MPU_REGION_READ_WRITE ) == پورٽ_MPU_REGION_READ_WRITE )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
                }
            }
            وإلا
            {
                /* Invalidate the region. */
                xMPUSettings->xRegion[ ul ].ul_Region_بنياد_پتو = ( ( ul - 1UL ) | پورٽ_MPU_REGION_VALID );
                xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_شروعات_پتو = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_پڇاڙي_پتو = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
            }

            l_اشاريو++;
        }
    }
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    بنياد_Type_t x_پورٽ_Is_Authorized_منزل_Access_بفر( ثابت فراغ * pv_بفر,
                                                size_t x_بفر_ڊيگهائي,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_بفر_شروعات_پتو, ul_بفر_پڇاڙي_پتو;
        بنياد_Type_t xAccessGranted = pdFALSE;
        ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( عدم ); /* Calling task's MPU settings. */


        إذا( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        وإلا إذا( ( xTaskMpuSettings->ulTaskFlags & پورٽ_TASK_IS_PRIVILEGED_FLAG ) == پورٽ_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        وإلا
        {
            إذا( پورٽ_جوڙيو_UINT32_WILL_حد_کان_مٿي( ( ( uint32_t ) pv_بفر ), ( ( uint32_t ) x_بفر_ڊيگهائي - 1UL ) ) == pdFALSE )
            {
                ul_بفر_شروعات_پتو = ( uint32_t ) pv_بفر;
                ul_بفر_پڇاڙي_پتو = ( ( ( uint32_t ) pv_بفر ) + ( uint32_t ) x_بفر_ڊيگهائي - 1UL );

                لكل( i = 0; i < پورٽ_ڪل_انگ_REGIONS_اندريون_TCB; i++ )
                {
                    إذا( پورٽ_IS_پتو_WITHIN_RANGE( ul_بفر_شروعات_پتو,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_شروعات_پتو,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_پڇاڙي_پتو ) &&
                        پورٽ_IS_پتو_WITHIN_RANGE( ul_بفر_پڇاڙي_پتو,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_شروعات_پتو,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_پڇاڙي_پتو ) &&
                        پورٽ_IS_AUTHORIZED( ulAccessRequested, xTaskMpuSettings->xRegionSettings[ i ].ulRegionPermissions ) )
                    {
                        xAccessGranted = pdTRUE;
                        اكسر;
                    }
                }
            }
        }

        أرجع xAccessGranted;
    }

#جيڪڏهن_پورو /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

__asm uint32_t prv_پورٽ_Get_IPSR( فراغ )
{
/* *INDENT-OFF* */
    PRESERVE8

    mrs r0, ipsr
    bx r14
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

#إذا ( configASSERT_DEFINED == 1 )

    فراغ v_پورٽ_Validate_مداخلت_ترجيح( فراغ )
    {
        uint32_t ul_Current_مداخلت;
        uint8_t uc_Current_ترجيح;

        /* Obtain the number of the currently executing interrupt. */
        ul_Current_مداخلت = prv_پورٽ_Get_IPSR();

        /* Is the interrupt number a user defined interrupt? */
        إذا( ul_Current_مداخلت >= پورٽ_پهريون_USER_مداخلت_عدد )
        {
            /* Look up the interrupt's priority. */
            uc_Current_ترجيح = pc_مداخلت_ترجيح_Registers[ ul_Current_مداخلت ];

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
            configASSERT( uc_Current_ترجيح >= uc_Max_Sys_Call_ترجيح );
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
        configASSERT( ( پورٽ_AIRCR_REG & پورٽ_ترجيح_گروهه_نقاب ) <= ulMaxPRIGROUPValue );
    }

#جيڪڏهن_پورو /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/

#إذا ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    فراغ v_پورٽ_Grant_Access_منزل_Kernel_Object( TaskHandle_t x_اندروني_Task_Handle,
                                         int32_t l_اندروني_اشاريو_جو_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_داخلا_اشاريو, ul_Access_Control_List_داخلا_ٻٽو_انگ;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_داخلا_اشاريو = ( ( uint32_t ) l_اندروني_اشاريو_جو_Kernel_Object / پورٽ_ACL_داخلا_سائيز_بٽ );
        ul_Access_Control_List_داخلا_ٻٽو_انگ = ( ( uint32_t ) l_اندروني_اشاريو_جو_Kernel_Object % پورٽ_ACL_داخلا_سائيز_بٽ );

        xTaskMpuSettings = xTaskGetMPUSettings( x_اندروني_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_داخلا_اشاريو ] |= ( 1U << ul_Access_Control_List_داخلا_ٻٽو_انگ );
    }

#جيڪڏهن_پورو /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    فراغ v_پورٽ_Revoke_Access_منزل_Kernel_Object( TaskHandle_t x_اندروني_Task_Handle,
                                          int32_t l_اندروني_اشاريو_جو_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_داخلا_اشاريو, ul_Access_Control_List_داخلا_ٻٽو_انگ;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_داخلا_اشاريو = ( ( uint32_t ) l_اندروني_اشاريو_جو_Kernel_Object / پورٽ_ACL_داخلا_سائيز_بٽ );
        ul_Access_Control_List_داخلا_ٻٽو_انگ = ( ( uint32_t ) l_اندروني_اشاريو_جو_Kernel_Object % پورٽ_ACL_داخلا_سائيز_بٽ );

        xTaskMpuSettings = xTaskGetMPUSettings( x_اندروني_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_داخلا_اشاريو ] &= ~( 1U << ul_Access_Control_List_داخلا_ٻٽو_انگ );
    }

#جيڪڏهن_پورو /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        بنياد_Type_t x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( int32_t l_اندروني_اشاريو_جو_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_داخلا_اشاريو, ul_Access_Control_List_داخلا_ٻٽو_انگ;
            بنياد_Type_t xAccessGranted = pdFALSE;
            ثابت xMPU_SETTINGS * xTaskMpuSettings;

            إذا( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            وإلا
            {
                xTaskMpuSettings = xTaskGetMPUSettings( عدم ); /* Calling task's MPU settings. */

                ul_Access_Control_List_داخلا_اشاريو = ( ( uint32_t ) l_اندروني_اشاريو_جو_Kernel_Object / پورٽ_ACL_داخلا_سائيز_بٽ );
                ul_Access_Control_List_داخلا_ٻٽو_انگ = ( ( uint32_t ) l_اندروني_اشاريو_جو_Kernel_Object % پورٽ_ACL_داخلا_سائيز_بٽ );

                إذا( ( xTaskMpuSettings->ulTaskFlags & پورٽ_TASK_IS_PRIVILEGED_FLAG ) == پورٽ_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                وإلا
                {
                    إذا( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_داخلا_اشاريو ] & ( 1U << ul_Access_Control_List_داخلا_ٻٽو_انگ ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            أرجع xAccessGranted;
        }

    #وإلا /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        بنياد_Type_t x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( int32_t l_اندروني_اشاريو_جو_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( فراغ ) l_اندروني_اشاريو_جو_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            أرجع pdTRUE;
        }

    #جيڪڏهن_پورو /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#جيڪڏهن_پورو /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/
