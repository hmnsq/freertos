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
* Implementation of functions defined in portable.h for the ARM CM3 MPU port.
*----------------------------------------------------------*/

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#تعریف_کرو MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "mpu_syscall_numbers.h"

#تعریف_رد MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#جے_بنا_تعریف configSYSTICK_CLOCK_HZ
    #تعریف_کرو configSYSTICK_CLOCK_HZ    configCPU_CLOCK_HZ
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #تعریف_کرو پورٹ_NVIC_SYSTICK_CLK      ( 1UL << 2UL )
#وإلا

/* The way the SysTick is clocked is not modified in case it is not the same
 * as the core. */
    #تعریف_کرو پورٹ_NVIC_SYSTICK_CLK    ( 0 )
#جے_انت

/* Unprivileged critical sections are not supported when using MPU wrappers
 * version 2. Default the option to 0 and reject an explicit value of 1. */
#جے_بنا_تعریف configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS
    #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
        #تعریف_کرو configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    0
    #وإلا
        #warning "configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not defined. We recommend defining it to 0 in FreeRTOSConfig.h for better security."
        #تعریف_کرو configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    1
    #جے_انت
#وإلا
    #إذا ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) )
        #غلطی configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not supported with MPU wrappers نسخہ 2 ( configUSE_MPU_WRAPPERS_V1 == 0 ).
    #جے_انت
#جے_انت

/* Prototype of all Interrupt Service Routines (ISRs). */
تعريفنوع فراغ ( * پورٹ_ISR_t )( فراغ );

/* Constants required to access and manipulate the NVIC. */
#تعریف_کرو پورٹ_NVIC_SYSTICK_CTRL_REG                 ( *( ( متطاير uint32_t * ) 0xe000e010 ) )
#تعریف_کرو پورٹ_NVIC_SYSTICK_لدو_REG                 ( *( ( متطاير uint32_t * ) 0xe000e014 ) )
#تعریف_کرو پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG        ( *( ( متطاير uint32_t * ) 0xe000e018 ) )
#تعریف_کرو پورٹ_NVIC_SHPR3_REG                        ( *( ( متطاير uint32_t * ) 0xe000ed20 ) )
#تعریف_کرو پورٹ_NVIC_SHPR2_REG                        ( *( ( متطاير uint32_t * ) 0xe000ed1c ) )
#تعریف_کرو پورٹ_NVIC_SYS_CTRL_STATE_REG               ( *( ( متطاير uint32_t * ) 0xe000ed24 ) )
#تعریف_کرو پورٹ_NVIC_MEM_FAULT_ENABLE                 ( 1UL << 16UL )

/* Constants required to access and manipulate the MPU. */
#تعریف_کرو پورٹ_MPU_TYPE_REG                          ( *( ( متطاير uint32_t * ) 0xe000ed90 ) )
#تعریف_کرو پورٹ_MPU_REGION_ادھار_پتہ_REG           ( *( ( متطاير uint32_t * ) 0xe000ed9C ) )
#تعریف_کرو پورٹ_MPU_REGION_ATTRIBUTE_REG              ( *( ( متطاير uint32_t * ) 0xe000edA0 ) )
#تعریف_کرو پورٹ_MPU_CTRL_REG                          ( *( ( متطاير uint32_t * ) 0xe000ed94 ) )
#تعریف_کرو پورٹ_EXPECTED_MPU_TYPE_قدر               ( 8UL << 8UL ) /* 8 regions, unified. */
#تعریف_کرو پورٹ_MPU_ENABLE                            ( 0x01UL )
#تعریف_کرو پورٹ_MPU_BACKGROUND_ENABLE                 ( 1UL << 2UL )
#تعریف_کرو پورٹ_PRIVILEGED_EXECUTION_شروع_پتہ    ( 0UL )
#تعریف_کرو پورٹ_MPU_REGION_VALID                      ( 0x10UL )
#تعریف_کرو پورٹ_MPU_REGION_ENABLE                     ( 0x01UL )
#تعریف_کرو پورٹ_PERIPHERALS_شروع_پتہ             0x40000000UL
#تعریف_کرو پورٹ_PERIPHERALS_سرا_پتہ               0x5FFFFFFFUL

/* Constants required to access and manipulate the SysTick and other FreeRTOS
 * interrupts. */
#تعریف_کرو پورٹ_NVIC_SYSTICK_INT                      ( 0x00000002UL )
#تعریف_کرو پورٹ_NVIC_SYSTICK_ENABLE                   ( 0x00000001UL )
#تعریف_کرو پورٹ_MIN_رکاوٹ_ترجیح                ( 255UL )
#تعریف_کرو پورٹ_NVIC_PENDSV_PRI                       ( ( ( uint32_t ) پورٹ_MIN_رکاوٹ_ترجیح ) << 16UL )
#تعریف_کرو پورٹ_NVIC_SYSTICK_PRI                      ( ( ( uint32_t ) پورٹ_MIN_رکاوٹ_ترجیح ) << 24UL )
#تعریف_کرو پورٹ_NVIC_SVC_PRI                          ( ( ( uint32_t ) config_MAX_SYSCALL_رکاوٹ_ترجیح - 1UL ) << 24UL )

/* Constants required to set up the initial stack. */
#تعریف_کرو پورٹ_INITIAL_XPSR                          ( 0x01000000 )
#تعریف_کرو پورٹ_INITIAL_EXC_RETURN                    ( 0xfffffffdUL )
#تعریف_کرو پورٹ_INITIAL_CONTROL_IF_UNPRIVILEGED       ( 0x03 )
#تعریف_کرو پورٹ_INITIAL_CONTROL_IF_PRIVILEGED         ( 0x02 )

/* Constants used to check the installation of the FreeRTOS interrupt handlers. */
#تعریف_کرو پورٹ_SCB_VTOR_REG                          ( *( ( پورٹ_ISR_t ** ) 0xE000ED08 ) )
#تعریف_کرو پورٹ_سمتیہ_اشاریہ_SVC                      ( 11 )
#تعریف_کرو پورٹ_سمتیہ_اشاریہ_PENDSV                   ( 14 )

/* Constants required to check the validity of an interrupt priority. */
#تعریف_کرو پورٹ_پہلا_USER_رکاوٹ_نمبر           ( 16 )
#تعریف_کرو پورٹ_NVIC_IP_REGISTERS_وتھ_16           ( 0xE000E3F0 )
#تعریف_کرو پورٹ_AIRCR_REG                             ( *( ( متطاير uint32_t * ) 0xE000ED0C ) )
#تعریف_کرو پورٹ_MAX_8_ثنائی_ہندسہ_قدر                       ( ( uint8_t ) 0xff )
#تعریف_کرو پورٹ_چوٹی_ثنائی_ہندسہ_دا_BYTE                       ( ( uint8_t ) 0x80 )
#تعریف_کرو پورٹ_MAX_PRIGROUP_بٹ                     ( ( uint8_t ) 7 )
#تعریف_کرو پورٹ_ترجیح_گروہ_نقاب                   ( 0x07UL << 8UL )
#تعریف_کرو پورٹ_PRIGROUP_کھسکاؤ                        ( 8UL )

/* Constants used during system call enter and exit. */
#تعریف_کرو پورٹ_PSR_ڈھیر_PADDING_نقاب                ( 1UL << 9UL )

/* Offsets in the stack to the parameters when inside the SVC handler. */
#تعریف_کرو پورٹ_وتھ_منزل_LR                          ( 5 )
#تعریف_کرو پورٹ_وتھ_منزل_PC                          ( 6 )
#تعریف_کرو پورٹ_وتھ_منزل_PSR                         ( 7 )

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#تعریف_کرو پورٹ_شروع_پتہ_نقاب                    ( ( ڈھیر_Type_t ) 0xfffffffeUL )

/* Does addr lie within [start, end] address range? */
#تعریف_کرو پورٹ_IS_پتہ_WITHIN_RANGE( addr, شروع, سرا ) \
    ( ( ( addr ) >= ( شروع ) ) && ( ( addr ) <= ( سرا ) ) )

/* Is the access request satisfied by the available permissions? */
#تعریف_کرو پورٹ_IS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#تعریف_کرو پورٹ_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کرو پورٹ_جوڑو_UINT32_WILL_حد_توں_ودھ( a, b )    ( ( a ) > ( پورٹ_UINT32_MAX - ( b ) ) )
/*-----------------------------------------------------------*/

/*
 * Configure a number of standard MPU regions that are used by all tasks.
 */
ساكن فراغ prv_تیاری_MPU( فراغ ) PRIVILEGED_FUNCTION;

/*
 * Return the smallest MPU region size that a given number of bytes will fit
 * into.  The region size is returned as the value that should be programmed
 * into the region attribute register for that region.
 */
ساكن uint32_t prv_Get_MPURegion_ناپ_Setting( uint32_t ul_Actual_ناپ_وچ_بائٹاں ) PRIVILEGED_FUNCTION;

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
فراغ v_پورٹ_تیاری_Timer_رکاوٹ( فراغ );

/*
 * Standard FreeRTOS exception handlers.
 */
فراغ x_پورٹ_Pend_SVHandler( فراغ ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;
فراغ x_پورٹ_Sys_Tick_Handler( فراغ )  __attribute__( ( optimize( "3" ) ) ) PRIVILEGED_FUNCTION;
فراغ v_پورٹ_SVCHandler( فراغ ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/*
 * Starts the scheduler by restoring the context of the first task to run.
 */
ساكن فراغ prv_Restore_Context_دا_پہلا_Task( فراغ ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/*
 * C portion of the SVC handler.  The SVC handler is split between an asm entry
 * and a C wrapper for simplicity of coding and maintenance.
 */
فراغ vSVCHandler_C( uint32_t * pulRegisters ) __attribute__( ( noinline ) ) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
ادھار_Type_t xIsPrivileged( فراغ ) __attribute__( ( naked ) );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 *
 * Bit 0 of the CONTROL register defines the privilege level of Thread Mode.
 *  Bit[0] = 0 --> The processor is running privileged
 *  Bit[0] = 1 --> The processor is running unprivileged.
 */
فراغ vResetPrivilege( فراغ ) __attribute__( ( naked ) );

/**
 * @brief Make a task unprivileged.
 */
فراغ v_پورٹ_Switch_منزل_User_منوال( فراغ );

/**
 * @brief Enter critical section.
 */
#إذا ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    فراغ v_پورٹ_Enter_Critical( فراغ ) FREERTOS_SYSTEM_CALL;
#وإلا
    فراغ v_پورٹ_Enter_Critical( فراغ ) PRIVILEGED_FUNCTION;
#جے_انت

/**
 * @brief Exit from critical section.
 */
#إذا ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    فراغ v_پورٹ_Exit_Critical( فراغ ) FREERTOS_SYSTEM_CALL;
#وإلا
    فراغ v_پورٹ_Exit_Critical( فراغ ) PRIVILEGED_FUNCTION;
#جے_انت

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the system call stack so that upon returning from
 * SVC, the system call stack is used.
 *
 * @param pulTaskStack The current SP when the SVC was raised.
 * @param ucSystemCallNumber The system call number of the system call.
 */
    فراغ vSystemCallEnter( uint32_t * pul_Task_ڈھیر,
                           uint8_t uc_System_Call_نمبر ) PRIVILEGED_FUNCTION;

#جے_انت /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Raise SVC for exiting from a system call.
 */
    فراغ vRequestSystemCallExit( فراغ ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#جے_انت /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the task stack so that upon returning from
 * SVC, the task stack is used again.
 *
 * @param pulSystemCallStack The current SP when the SVC was raised.
 */
    فراغ vSystemCallExit( uint32_t * pul_System_Call_ڈھیر ) PRIVILEGED_FUNCTION;

#جے_انت /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
ادھار_Type_t x_پورٹ_Is_Task_Privileged( فراغ ) PRIVILEGED_FUNCTION;
/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable.  Note this is not saved as part of the task context as context
 * switches can only occur when uxCriticalNesting is zero. */
ساكن UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

/*
 * This variable is set to pdTRUE when the scheduler is started.
 */
    PRIVILEGED_انکڑے ساكن ادھار_Type_t xSchedulerRunning = pdFALSE;

#جے_انت /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#إذا ( configASSERT_DEFINED == 1 )
    ساكن uint8_t uc_Max_Sys_Call_ترجیح = 0;
    ساكن uint32_t ulMaxPRIGROUPValue = 0;
    ساكن ثابت متطاير uint8_t * ثابت pc_رکاوٹ_ترجیح_Registers = ( ثابت متطاير uint8_t * ثابت ) پورٹ_NVIC_IP_REGISTERS_وتھ_16;
#جے_انت /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                     TaskFunction_t px_کوڈ,
                                     فراغ * pvParameters,
                                     ادھار_Type_t x_لگاتار_Privileged,
                                     xMPU_SETTINGS * xMPUSettings )
{
    إذا( x_لگاتار_Privileged == pdTRUE )
    {
        xMPUSettings->ulTaskFlags |= پورٹ_TASK_IS_PRIVILEGED_FLAG;
        xMPUSettings->ulContext[ 0 ] = پورٹ_INITIAL_CONTROL_IF_PRIVILEGED;
    }
    وإلا
    {
        xMPUSettings->ulTaskFlags &= ( ~( پورٹ_TASK_IS_PRIVILEGED_FLAG ) );
        xMPUSettings->ulContext[ 0 ] = پورٹ_INITIAL_CONTROL_IF_UNPRIVILEGED;
    }

    xMPUSettings->ulContext[ 1 ] = 0x04040404;                                        /* r4. */
    xMPUSettings->ulContext[ 2 ] = 0x05050505;                                        /* r5. */
    xMPUSettings->ulContext[ 3 ] = 0x06060606;                                        /* r6. */
    xMPUSettings->ulContext[ 4 ] = 0x07070707;                                        /* r7. */
    xMPUSettings->ulContext[ 5 ] = 0x08080808;                                        /* r8. */
    xMPUSettings->ulContext[ 6 ] = 0x09090909;                                        /* r9. */
    xMPUSettings->ulContext[ 7 ] = 0x10101010;                                        /* r10. */
    xMPUSettings->ulContext[ 8 ] = 0x11111111;                                        /* r11. */
    xMPUSettings->ulContext[ 9 ] = پورٹ_INITIAL_EXC_RETURN;                            /* EXC_RETURN. */

    xMPUSettings->ulContext[ 10 ] = ( uint32_t ) ( px_چوٹی_دا_ڈھیر - 8 );                /* PSP with the hardware saved stack. */
    xMPUSettings->ulContext[ 11 ] = ( uint32_t ) pvParameters;                        /* r0. */
    xMPUSettings->ulContext[ 12 ] = 0x01010101;                                       /* r1. */
    xMPUSettings->ulContext[ 13 ] = 0x02020202;                                       /* r2. */
    xMPUSettings->ulContext[ 14 ] = 0x03030303;                                       /* r3. */
    xMPUSettings->ulContext[ 15 ] = 0x12121212;                                       /* r12. */
    xMPUSettings->ulContext[ 16 ] = 0;                                                /* LR. */
    xMPUSettings->ulContext[ 17 ] = ( ( uint32_t ) px_کوڈ ) & پورٹ_شروع_پتہ_نقاب; /* PC. */
    xMPUSettings->ulContext[ 18 ] = پورٹ_INITIAL_XPSR;                                 /* xPSR. */

    #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        /* Ensure that the system call stack is double word aligned. */
        xMPUSettings->x_System_Call_ڈھیر_Info.pul_System_Call_ڈھیر = &( xMPUSettings->x_System_Call_ڈھیر_Info.ul_System_Call_ڈھیر_بفر[ config_SYSTEM_CALL_ڈھیر_ناپ - 1 ] );
        xMPUSettings->x_System_Call_ڈھیر_Info.pul_System_Call_ڈھیر = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_ڈھیر_Info.pul_System_Call_ڈھیر ) &
                                                                                 ( uint32_t ) ( ~( پورٹ_BYTE_ALIGNMENT_نقاب ) ) );

        /* This is not NULL only for the duration of a system call. */
        xMPUSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر = عدم;
    }
    #جے_انت /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    أرجع &( xMPUSettings->ulContext[ 19 ] );
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    فراغ v_پورٹ_SVCHandler( فراغ ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm متطاير
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
            "ldr r2, [r0, #24]              \n"
            "ldrb r1, [r2, #-2]             \n"
            "cmp r1, %0                     \n"
            "blt vSystemCallEnter           \n"
            "cmp r1, %1                     \n"
            "beq vSystemCallExit            \n"
            "b vSVCHandler_C                \n"
            "                               \n"
            : /* No outputs. */
            : "i" ( عدد_SYSTEM_CALLS ), "i" ( پورٹ_SVC_SYSTEM_CALL_EXIT )
            : "r0", "r1", "r2", "memory"
        );
    }

#وإلا /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    فراغ v_پورٹ_SVCHandler( فراغ ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        /* Assumes psp was in use. */
        __asm متطاير
        (
            #جے_بنا_تعریف USE_PROCESS_ڈھیر /* Code should not be required if a main() is using the process stack. */
                "   tst lr, #4                      \n"
                "   ite eq                          \n"
                "   mrseq r0, msp                   \n"
                "   mrsne r0, psp                   \n"
            #وإلا
                "   mrs r0, psp                     \n"
            #جے_انت
            "   b %0                            \n"
            ::"i" ( vSVCHandler_C ) : "r0", "memory"
        );
    }

#جے_انت /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

فراغ vSVCHandler_C( uint32_t * pulParam ) /* PRIVILEGED_FUNCTION */
{
    uint8_t ucSVCNumber;
    uint32_t ulPC;

    #إذا ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) )
        #إذا defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint32_t * __syscalls_flash_start__;
            خارجي uint32_t * __syscalls_flash_end__;
        #وإلا
            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint32_t __syscalls_flash_start__[];
            خارجي uint32_t __syscalls_flash_end__[];
        #جے_انت /* #if defined( __ARMCC_VERSION ) */
    #جے_انت /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) ) */

    /* The stack contains: r0, r1, r2, r3, r12, LR, PC and xPSR.  The first
     * argument (r0) is pulParam[ 0 ]. */
    ulPC = pulParam[ پورٹ_وتھ_منزل_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    بدل( ucSVCNumber )
    {
        حالة پورٹ_SVC_شروع_SCHEDULER:
            prv_Restore_Context_دا_پہلا_Task();
            اكسر;

        حالة پورٹ_SVC_YIELD:
            پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ;

            /* Barriers are normally not required
             * but do ensure the code is completely
             * within the specified behaviour for the
             * architecture. */
            __asm متطاير ( "dsb" ::: "memory" );
            __asm متطاير ( "isb" );

            اكسر;

    #إذا ( configUSE_MPU_WRAPPERS_V1 == 1 )
        #إذا ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 )
            حالة پورٹ_SVC_RAISE_PRIVILEGE: /* Only raise the privilege, if the
                                           * svc was raised from any of the
                                           * system calls. */

                إذا( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                    ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
                {
                    __asm متطاير
                    (
                        "   mrs r1, control     \n" /* Obtain current control value. */
                        "   bic r1, #1          \n" /* Set privilege bit. */
                        "   msr control, r1     \n" /* Write back new control value. */
                        ::: "r1", "memory"
                    );
                }

                اكسر;
        #وإلا /* if ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
            حالة پورٹ_SVC_RAISE_PRIVILEGE:
                __asm متطاير
                (
                    "   mrs r1, control     \n" /* Obtain current control value. */
                    "   bic r1, #1          \n" /* Set privilege bit. */
                    "   msr control, r1     \n" /* Write back new control value. */
                    ::: "r1", "memory"
                );
                اكسر;
        #جے_انت /* #if( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
    #جے_انت /* #if ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

        افتراضي: /* Unknown SVC call. */
            اكسر;
    }
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    فراغ vSystemCallEnter( uint32_t * pul_Task_ڈھیر,
                           uint8_t uc_System_Call_نمبر ) /* PRIVILEGED_FUNCTION */
    {
        خارجي TaskHandle_t pxCurrentTCB;
        خارجي UBaseType_t uxSystemCallImplementations[ عدد_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_ڈھیر;
        uint32_t ulSystemCallLocation, i;
        /* Hardware Saved Stack Frame Size upon Exception entry:
         * Basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
         */
        ثابت uint32_t ul_Hardware_Saved_Exception_چوکھٹا_ناپ = 8;

        #إذا defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint32_t * __syscalls_flash_start__;
            خارجي uint32_t * __syscalls_flash_end__;
        #وإلا
            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint32_t __syscalls_flash_start__[];
            خارجي uint32_t __syscalls_flash_end__[];
        #جے_انت /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_ڈھیر[ پورٹ_وتھ_منزل_PC ];
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
            ( pxMpuSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر == عدم ) &&
            ( uxSystemCallImplementations[ uc_System_Call_نمبر ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_ڈھیر = pxMpuSettings->x_System_Call_ڈھیر_Info.pul_System_Call_ڈھیر;

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_ڈھیر = pul_System_Call_ڈھیر - ul_Hardware_Saved_Exception_چوکھٹا_ناپ;

            /* Copy the stack frame. */
            لكل( i = 0; i < ul_Hardware_Saved_Exception_چوکھٹا_ناپ; i++ )
            {
                pul_System_Call_ڈھیر[ i ] = pul_Task_ڈھیر[ i ];
            }

            /* Use the pulSystemCallStack in thread mode. */
            __asm متطاير ( "msr psp, %0" : : "r" ( pul_System_Call_ڈھیر ) );

            /* Raise the privilege for the duration of the system call. */
            __asm متطاير (
                " mrs r1, control     \n" /* Obtain current control value. */
                " bic r1, #1          \n" /* Clear nPRIV bit. */
                " msr control, r1     \n" /* Write back new control value. */
                ::: "r1", "memory"
                );

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر = pul_Task_ڈھیر + ul_Hardware_Saved_Exception_چوکھٹا_ناپ;

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_ڈھیر_Info.ul_Link_رجسٹر_At_System_Call_اندراج = pul_Task_ڈھیر[ پورٹ_وتھ_منزل_LR ];

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_ڈھیر[ پورٹ_وتھ_منزل_PC ] = uxSystemCallImplementations[ uc_System_Call_نمبر ];
            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_ڈھیر[ پورٹ_وتھ_منزل_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            إذا( ( pul_Task_ڈھیر[ پورٹ_وتھ_منزل_PSR ] & پورٹ_PSR_ڈھیر_PADDING_نقاب ) == پورٹ_PSR_ڈھیر_PADDING_نقاب )
            {
                pxMpuSettings->ulTaskFlags |= پورٹ_ڈھیر_چوکھٹا_HAS_PADDING_FLAG;
            }
            وإلا
            {
                pxMpuSettings->ulTaskFlags &= ( ~پورٹ_ڈھیر_چوکھٹا_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_ڈھیر[ پورٹ_وتھ_منزل_PSR ] &= ( ~پورٹ_PSR_ڈھیر_PADDING_نقاب );
        }
    }

#جے_انت /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    فراغ vRequestSystemCallExit( فراغ ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm متطاير ( "svc %0 \n" ::"i" ( پورٹ_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#جے_انت /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    فراغ vSystemCallExit( uint32_t * pul_System_Call_ڈھیر ) /* PRIVILEGED_FUNCTION */
    {
        خارجي TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_ڈھیر;
        uint32_t ulSystemCallLocation, i;
        /* Hardware Saved Stack Frame Size upon Exception entry:
         * Basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
         */
        ثابت uint32_t ul_Hardware_Saved_Exception_چوکھٹا_ناپ = 8;

        #إذا defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint32_t * __privileged_functions_start__;
            خارجي uint32_t * __privileged_functions_end__;
        #وإلا
            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint32_t __privileged_functions_start__[];
            خارجي uint32_t __privileged_functions_end__[];
        #جے_انت /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_ڈھیر[ پورٹ_وتھ_منزل_PC ];
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
            ( pxMpuSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر != عدم ) )
        {
            pul_Task_ڈھیر = pxMpuSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر;

            /* Make space on the task stack for the stack frame. */
            pul_Task_ڈھیر = pul_Task_ڈھیر - ul_Hardware_Saved_Exception_چوکھٹا_ناپ;

            /* Copy the stack frame. */
            لكل( i = 0; i < ul_Hardware_Saved_Exception_چوکھٹا_ناپ; i++ )
            {
                pul_Task_ڈھیر[ i ] = pul_System_Call_ڈھیر[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm متطاير ( "msr psp, %0" : : "r" ( pul_Task_ڈھیر ) );

            /* Drop the privilege before returning to the thread mode. */
            __asm متطاير (
                " mrs r1, control     \n" /* Obtain current control value. */
                " orr r1, #1          \n" /* Set nPRIV bit. */
                " msr control, r1     \n" /* Write back new control value. */
                ::: "r1", "memory"
                );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_ڈھیر[ پورٹ_وتھ_منزل_PC ] = pxMpuSettings->x_System_Call_ڈھیر_Info.ul_Link_رجسٹر_At_System_Call_اندراج;
            /* Ensure that LR has a valid value.*/
            pul_Task_ڈھیر[ پورٹ_وتھ_منزل_LR ] = pxMpuSettings->x_System_Call_ڈھیر_Info.ul_Link_رجسٹر_At_System_Call_اندراج;

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            إذا( ( pxMpuSettings->ulTaskFlags & پورٹ_ڈھیر_چوکھٹا_HAS_PADDING_FLAG ) == پورٹ_ڈھیر_چوکھٹا_HAS_PADDING_FLAG )
            {
                pul_Task_ڈھیر[ پورٹ_وتھ_منزل_PSR ] |= پورٹ_PSR_ڈھیر_PADDING_نقاب;
            }
            وإلا
            {
                pul_Task_ڈھیر[ پورٹ_وتھ_منزل_PSR ] &= ( ~پورٹ_PSR_ڈھیر_PADDING_نقاب );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر = عدم;
        }
    }

#جے_انت /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_Is_Task_Privileged( فراغ ) /* PRIVILEGED_FUNCTION */
{
    ادھار_Type_t xTaskIsPrivileged = pdFALSE;
    ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( عدم ); /* Calling task's MPU settings. */

    إذا( ( xTaskMpuSettings->ulTaskFlags & پورٹ_TASK_IS_PRIVILEGED_FLAG ) == پورٹ_TASK_IS_PRIVILEGED_FLAG )
    {
        xTaskIsPrivileged = pdTRUE;
    }

    أرجع xTaskIsPrivileged;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_Restore_Context_دا_پہلا_Task( فراغ )
{
    __asm متطاير
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
ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
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
        ثابت پورٹ_ISR_t * ثابت px_سمتیہ_جدول = پورٹ_SCB_VTOR_REG;

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
        configASSERT( px_سمتیہ_جدول[ پورٹ_سمتیہ_اشاریہ_SVC ] == v_پورٹ_SVCHandler );
        configASSERT( px_سمتیہ_جدول[ پورٹ_سمتیہ_اشاریہ_PENDSV ] == x_پورٹ_Pend_SVHandler );
    }
    #جے_انت /* configCHECK_HANDLER_INSTALLATION */

    #إذا ( configASSERT_DEFINED == 1 )
    {
        متطاير uint8_t uc_Original_ترجیح;
        متطاير uint32_t ul_Implemented_Prio_بٹ = 0;
        متطاير uint8_t * ثابت puc_پہلا_User_ترجیح_رجسٹر = ( متطاير uint8_t * ثابت ) ( پورٹ_NVIC_IP_REGISTERS_وتھ_16 + پورٹ_پہلا_USER_رکاوٹ_نمبر );
        متطاير uint8_t uc_Max_ترجیح_قدر;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
         * functions can be called.  ISR safe functions are those that end in
         * "FromISR".  FreeRTOS maintains separate thread and ISR API functions
         * to ensure interrupt entry is as fast and simple as possible.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_ترجیح = *puc_پہلا_User_ترجیح_رجسٹر;

        /* Determine the number of priority bits available.  First write to all
         * possible bits. */
        *puc_پہلا_User_ترجیح_رجسٹر = پورٹ_MAX_8_ثنائی_ہندسہ_قدر;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ترجیح_قدر = *puc_پہلا_User_ترجیح_رجسٹر;

        /* Use the same mask on the maximum system call priority. */
        uc_Max_Sys_Call_ترجیح = config_MAX_SYSCALL_رکاوٹ_ترجیح & uc_Max_ترجیح_قدر;

        /* Check that the maximum system call priority is nonzero after
         * accounting for the number of priority bits supported by the
         * hardware. A priority of 0 is invalid because setting the BASEPRI
         * register to 0 unmasks all interrupts, and interrupts with priority 0
         * cannot be masked using BASEPRI.
         * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( uc_Max_Sys_Call_ترجیح );

        /* Check that the bits not implemented in hardware are zero in
         * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( config_MAX_SYSCALL_رکاوٹ_ترجیح & ( ~uc_Max_ترجیح_قدر ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
         * of bits read back. */

        طالما( ( uc_Max_ترجیح_قدر & پورٹ_چوٹی_ثنائی_ہندسہ_دا_BYTE ) == پورٹ_چوٹی_ثنائی_ہندسہ_دا_BYTE )
        {
            ul_Implemented_Prio_بٹ++;
            uc_Max_ترجیح_قدر <<= ( uint8_t ) 0x01;
        }

        إذا( ul_Implemented_Prio_بٹ == 8 )
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
            configASSERT( ( config_MAX_SYSCALL_رکاوٹ_ترجیح & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        وإلا
        {
            ulMaxPRIGROUPValue = پورٹ_MAX_PRIGROUP_بٹ - ul_Implemented_Prio_بٹ;
        }

        /* Shift the priority group value back to its position within the AIRCR
         * register. */
        ulMaxPRIGROUPValue <<= پورٹ_PRIGROUP_کھسکاؤ;
        ulMaxPRIGROUPValue &= پورٹ_ترجیح_گروہ_نقاب;

        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_پہلا_User_ترجیح_رجسٹر = uc_Original_ترجیح;
    }
    #جے_انت /* configASSERT_DEFINED */

    /* Make PendSV and SysTick the lowest priority interrupts, and configure
     * SVCall for sufficient preemption priority. */
    پورٹ_NVIC_SHPR3_REG |= پورٹ_NVIC_PENDSV_PRI;
    پورٹ_NVIC_SHPR3_REG |= پورٹ_NVIC_SYSTICK_PRI;
    پورٹ_NVIC_SHPR2_REG = پورٹ_NVIC_SVC_PRI;

    /* Configure the regions in the MPU that are common to all tasks. */
    prv_تیاری_MPU();

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_پورٹ_تیاری_Timer_رکاوٹ();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        xSchedulerRunning = pdTRUE;
    }
    #جے_انت /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    /* Start the first task. */
    __asm متطاير (
        " ldr r0, =0xE000ED08   \n" /* Use the NVIC offset register to locate the stack. */
        " ldr r0, [r0]          \n"
        " ldr r0, [r0]          \n"
        " msr msp, r0           \n" /* Set the msp back to the start of the stack. */
        " cpsie i               \n" /* Globally enable interrupts. */
        " cpsie f               \n"
        " dsb                   \n"
        " isb                   \n"
        " svc %0                \n" /* System call to start first task. */
        " nop                   \n"
        " .ltorg                \n"
        ::"i" ( پورٹ_SVC_شروع_SCHEDULER ) : "memory" );

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Enter_Critical( فراغ )
{
    #إذا ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            پورٹ_DISABLE_INTERRUPTS();
            uxCriticalNesting++;
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        وإلا
        {
            پورٹ_DISABLE_INTERRUPTS();
            uxCriticalNesting++;
        }
    #وإلا /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        پورٹ_DISABLE_INTERRUPTS();
        uxCriticalNesting++;
    #جے_انت /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Exit_Critical( فراغ )
{
    #إذا ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            إذا( uxCriticalNesting == 0 )
            {
                پورٹ_ENABLE_INTERRUPTS();
            }

            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        وإلا
        {
            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            إذا( uxCriticalNesting == 0 )
            {
                پورٹ_ENABLE_INTERRUPTS();
            }
        }
    #وإلا /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        configASSERT( uxCriticalNesting );
        uxCriticalNesting--;

        إذا( uxCriticalNesting == 0 )
        {
            پورٹ_ENABLE_INTERRUPTS();
        }
    #جے_انت /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

فراغ x_پورٹ_Pend_SVHandler( فراغ )
{
    /* This is a naked function. */

    __asm متطاير
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
        " stmia r1!, {r3-r11, lr}               \n" /* Store CONTROL register, r4-r11 and LR. */
        " ldmia r0, {r4-r11}                    \n" /* Copy hardware saved context into r4-r11. */
        " stmia r1!, {r0, r4-r11}               \n" /* Store original PSP (after hardware has saved context) and the hardware saved context. */
        " str r1, [r2]                          \n" /* Save the location from where the context should be restored as the first member of TCB. */
        "                                       \n"
        /*---------- Select next task. --------- */
        " mov r0, %0                            \n"
        " msr basepri, r0                       \n"
        " dsb                                   \n"
        " isb                                   \n"
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
        "                                       \n"
        " str r1, [r2]                          \n" /* Save the location where the context should be saved next as the first member of TCB. */
        " bx lr                                 \n"
        "                                       \n"
        " .ltorg                                \n" /* Assemble current literal pool to avoid offset-out-of-bound errors with lto. */
        ::"i" ( config_MAX_SYSCALL_رکاوٹ_ترجیح )
    );
}
/*-----------------------------------------------------------*/

فراغ x_پورٹ_Sys_Tick_Handler( فراغ )
{
    uint32_t ulDummy;

    ulDummy = پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_منزل_SCHEDULER();
            /* Pend a context switch. */
            پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ;
        }
        وإلا
        {
            traceISR_EXIT();
        }
    }
    پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( ulDummy );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__attribute__( ( weak ) ) فراغ v_پورٹ_تیاری_Timer_رکاوٹ( فراغ )
{
    /* Stop and clear the SysTick. */
    پورٹ_NVIC_SYSTICK_CTRL_REG = 0UL;
    پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    پورٹ_NVIC_SYSTICK_لدو_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_شرح_HZ ) - 1UL;
    پورٹ_NVIC_SYSTICK_CTRL_REG = ( پورٹ_NVIC_SYSTICK_CLK | پورٹ_NVIC_SYSTICK_INT | پورٹ_NVIC_SYSTICK_ENABLE );
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_تیاری_MPU( فراغ )
{
    #إذا defined( __ARMCC_VERSION )

        /* Declaration when these variable are defined in code instead of being
         * exported from linker scripts. */
        خارجي uint32_t * __privileged_functions_start__;
        خارجي uint32_t * __privileged_functions_end__;
        خارجي uint32_t * __FLASH_segment_start__;
        خارجي uint32_t * __FLASH_segment_end__;
        خارجي uint32_t * __privileged_data_start__;
        خارجي uint32_t * __privileged_data_end__;
    #وإلا
        /* Declaration when these variable are exported from linker scripts. */
        خارجي uint32_t __privileged_functions_start__[];
        خارجي uint32_t __privileged_functions_end__[];
        خارجي uint32_t __FLASH_segment_start__[];
        خارجي uint32_t __FLASH_segment_end__[];
        خارجي uint32_t __privileged_data_start__[];
        خارجي uint32_t __privileged_data_end__[];
    #جے_انت /* if defined( __ARMCC_VERSION ) */

    /* Ensure that the device has the expected MPU type */
    configASSERT( پورٹ_MPU_TYPE_REG == پورٹ_EXPECTED_MPU_TYPE_قدر );

    /* Check the expected MPU is present. */
    إذا( پورٹ_MPU_TYPE_REG == پورٹ_EXPECTED_MPU_TYPE_قدر )
    {
        /* First setup the unprivileged flash for unprivileged read only access. */
        پورٹ_MPU_REGION_ادھار_پتہ_REG = ( ( uint32_t ) __FLASH_segment_start__ ) | /* Base address. */
                                          ( پورٹ_MPU_REGION_VALID ) |
                                          ( پورٹ_UNPRIVILEGED_FLASH_REGION );

        پورٹ_MPU_REGION_ATTRIBUTE_REG = ( پورٹ_MPU_REGION_READ_ONLY ) |
                                       ( پورٹ_MPU_REGION_CACHEABLE_BUFFERABLE ) |
                                       ( prv_Get_MPURegion_ناپ_Setting( ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__ ) ) |
                                       ( پورٹ_MPU_REGION_ENABLE );

        /* Setup the privileged flash for privileged only access.  This is where
         * the kernel code is * placed. */
        پورٹ_MPU_REGION_ادھار_پتہ_REG = ( ( uint32_t ) __privileged_functions_start__ ) | /* Base address. */
                                          ( پورٹ_MPU_REGION_VALID ) |
                                          ( پورٹ_PRIVILEGED_FLASH_REGION );

        پورٹ_MPU_REGION_ATTRIBUTE_REG = ( پورٹ_MPU_REGION_PRIVILEGED_READ_ONLY ) |
                                       ( پورٹ_MPU_REGION_CACHEABLE_BUFFERABLE ) |
                                       ( prv_Get_MPURegion_ناپ_Setting( ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__ ) ) |
                                       ( پورٹ_MPU_REGION_ENABLE );

        /* Setup the privileged data RAM region.  This is where the kernel data
         * is placed. */
        پورٹ_MPU_REGION_ادھار_پتہ_REG = ( ( uint32_t ) __privileged_data_start__ ) | /* Base address. */
                                          ( پورٹ_MPU_REGION_VALID ) |
                                          ( پورٹ_PRIVILEGED_RAM_REGION );

        پورٹ_MPU_REGION_ATTRIBUTE_REG = ( پورٹ_MPU_REGION_PRIVILEGED_READ_WRITE ) |
                                       ( پورٹ_MPU_REGION_CACHEABLE_BUFFERABLE ) |
                                       ( پورٹ_MPU_REGION_EXECUTE_NEVER ) |
                                       prv_Get_MPURegion_ناپ_Setting( ( uint32_t ) __privileged_data_end__ - ( uint32_t ) __privileged_data_start__ ) |
                                       ( پورٹ_MPU_REGION_ENABLE );

        /* By default allow everything to access the general peripherals.  The
         * system peripherals and registers are protected. */
        پورٹ_MPU_REGION_ادھار_پتہ_REG = ( پورٹ_PERIPHERALS_شروع_پتہ ) |
                                          ( پورٹ_MPU_REGION_VALID ) |
                                          ( پورٹ_GENERAL_PERIPHERALS_REGION );

        پورٹ_MPU_REGION_ATTRIBUTE_REG = ( پورٹ_MPU_REGION_READ_WRITE | پورٹ_MPU_REGION_EXECUTE_NEVER ) |
                                       ( prv_Get_MPURegion_ناپ_Setting( پورٹ_PERIPHERALS_سرا_پتہ - پورٹ_PERIPHERALS_شروع_پتہ ) ) |
                                       ( پورٹ_MPU_REGION_ENABLE );

        /* Enable the memory fault exception. */
        پورٹ_NVIC_SYS_CTRL_STATE_REG |= پورٹ_NVIC_MEM_FAULT_ENABLE;

        /* Enable the MPU with the background region configured. */
        پورٹ_MPU_CTRL_REG |= ( پورٹ_MPU_ENABLE | پورٹ_MPU_BACKGROUND_ENABLE );
    }
}
/*-----------------------------------------------------------*/

ساكن uint32_t prv_Get_MPURegion_ناپ_Setting( uint32_t ul_Actual_ناپ_وچ_بائٹاں )
{
    uint32_t ul_Region_ناپ, ul_Return_قدر = 4;

    /* 32 is the smallest region size, 31 is the largest valid value for
     * ulReturnValue. */
    لكل( ul_Region_ناپ = 32UL; ul_Return_قدر < 31UL; ( ul_Region_ناپ <<= 1UL ) )
    {
        إذا( ul_Actual_ناپ_وچ_بائٹاں <= ul_Region_ناپ )
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

ادھار_Type_t xIsPrivileged( فراغ ) /* __attribute__ (( naked )) */
{
    __asm متطاير
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

فراغ vResetPrivilege( فراغ ) /* __attribute__ (( naked )) */
{
    __asm متطاير
    (
        "   mrs r0, control                         \n" /* r0 = CONTROL. */
        "   orr r0, #1                              \n" /* r0 = r0 | 1. */
        "   msr control, r0                         \n" /* CONTROL = r0. */
        "   bx lr                                   \n" /* Return to the caller. */
        ::: "r0", "memory"
    );
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Switch_منزل_User_منوال( فراغ )
{
    /* Load the current task's MPU settings from its TCB. */
    xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( عدم );

    /* Mark the task as unprivileged. */
    xTaskMpuSettings->ulTaskFlags &= ( ~( پورٹ_TASK_IS_PRIVILEGED_FLAG ) );

    /* Lower the processor's privilege level. */
    vResetPrivilege();
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                ثابت بنية x_حافظہ_REGION * ثابت xRegions,
                                ڈھیر_Type_t * px_Bottom_دا_ڈھیر,
                                config_ڈھیر_ڈونگھائی_TYPE ux_ڈھیر_ڈونگھائی )
{
    #إذا defined( __ARMCC_VERSION )

        /* Declaration when these variable are defined in code instead of being
         * exported from linker scripts. */
        خارجي uint32_t * __SRAM_segment_start__;
        خارجي uint32_t * __SRAM_segment_end__;
        خارجي uint32_t * __privileged_data_start__;
        خارجي uint32_t * __privileged_data_end__;
    #وإلا
        /* Declaration when these variable are exported from linker scripts. */
        خارجي uint32_t __SRAM_segment_start__[];
        خارجي uint32_t __SRAM_segment_end__[];
        خارجي uint32_t __privileged_data_start__[];
        خارجي uint32_t __privileged_data_end__[];
    #جے_انت /* if defined( __ARMCC_VERSION ) */

    int32_t l_اشاریہ;
    uint32_t ul;

    إذا( xRegions == عدم )
    {
        /* No MPU regions are specified so allow access to all RAM. */
        xMPUSettings->xRegion[ 0 ].ul_Region_ادھار_پتہ =
            ( ( uint32_t ) __SRAM_segment_start__ ) | /* Base address. */
            ( پورٹ_MPU_REGION_VALID ) |
            ( پورٹ_ڈھیر_REGION );                     /* Region number. */

        xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
            ( پورٹ_MPU_REGION_READ_WRITE ) |
            ( پورٹ_MPU_REGION_CACHEABLE_BUFFERABLE ) |
            ( پورٹ_MPU_REGION_EXECUTE_NEVER ) |
            ( prv_Get_MPURegion_ناپ_Setting( ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__ ) ) |
            ( پورٹ_MPU_REGION_ENABLE );

        xMPUSettings->xRegionSettings[ 0 ].ul_Region_شروع_پتہ = ( uint32_t ) __SRAM_segment_start__;
        xMPUSettings->xRegionSettings[ 0 ].ul_Region_سرا_پتہ = ( uint32_t ) __SRAM_segment_end__;
        xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                   tskMPU_WRITE_PERMISSION );

        /* Invalidate user configurable regions. */
        لكل( ul = 1UL; ul <= پورٹ_عدد_CONFIGURABLE_REGIONS; ul++ )
        {
            xMPUSettings->xRegion[ ul ].ul_Region_ادھار_پتہ = ( ( ul - 1UL ) | پورٹ_MPU_REGION_VALID );
            xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ul_Region_شروع_پتہ = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ul_Region_سرا_پتہ = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
        }
    }
    وإلا
    {
        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid.  At all other
         * times the stack parameters will not be valid and it is assumed that the
         * stack region has already been configured. */
        إذا( ux_ڈھیر_ڈونگھائی > 0 )
        {
            /* Define the region that allows access to the stack. */
            xMPUSettings->xRegion[ 0 ].ul_Region_ادھار_پتہ =
                ( ( uint32_t ) px_Bottom_دا_ڈھیر ) |
                ( پورٹ_MPU_REGION_VALID ) |
                ( پورٹ_ڈھیر_REGION ); /* Region number. */

            xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
                ( پورٹ_MPU_REGION_READ_WRITE ) |
                ( پورٹ_MPU_REGION_EXECUTE_NEVER ) |
                ( prv_Get_MPURegion_ناپ_Setting ( ( uint32_t ) ( ux_ڈھیر_ڈونگھائی * ( config_ڈھیر_ڈونگھائی_TYPE ) حجم( ڈھیر_Type_t ) ) ) ) |
                ( پورٹ_MPU_REGION_CACHEABLE_BUFFERABLE ) |
                ( پورٹ_MPU_REGION_ENABLE );
            xMPUSettings->xRegionSettings[ 0 ].ul_Region_شروع_پتہ = ( uint32_t ) px_Bottom_دا_ڈھیر;
            xMPUSettings->xRegionSettings[ 0 ].ul_Region_سرا_پتہ = ( uint32_t ) ( ( uint32_t ) ( px_Bottom_دا_ڈھیر ) +
                                                                                   ( ux_ڈھیر_ڈونگھائی * ( config_ڈھیر_ڈونگھائی_TYPE ) حجم( ڈھیر_Type_t ) ) - 1UL );
            xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                       tskMPU_WRITE_PERMISSION );
        }

        l_اشاریہ = 0;

        لكل( ul = 1UL; ul <= پورٹ_عدد_CONFIGURABLE_REGIONS; ul++ )
        {
            إذا( ( xRegions[ l_اشاریہ ] ).ul_لمائی_وچ_بائٹاں > 0UL )
            {
                /* Translate the generic region definition contained in
                 * xRegions into the CM3 specific MPU settings that are then
                 * stored in xMPUSettings. */
                xMPUSettings->xRegion[ ul ].ul_Region_ادھار_پتہ =
                    ( ( uint32_t ) xRegions[ l_اشاریہ ].pv_ادھار_پتہ ) |
                    ( پورٹ_MPU_REGION_VALID ) |
                    ( ul - 1UL ); /* Region number. */

                xMPUSettings->xRegion[ ul ].ulRegionAttribute =
                    ( prv_Get_MPURegion_ناپ_Setting( xRegions[ l_اشاریہ ].ul_لمائی_وچ_بائٹاں ) ) |
                    ( xRegions[ l_اشاریہ ].ulParameters ) |
                    ( پورٹ_MPU_REGION_ENABLE );

                xMPUSettings->xRegionSettings[ ul ].ul_Region_شروع_پتہ = ( uint32_t ) xRegions[ l_اشاریہ ].pv_ادھار_پتہ;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_سرا_پتہ = ( uint32_t ) ( ( uint32_t ) xRegions[ l_اشاریہ ].pv_ادھار_پتہ + xRegions[ l_اشاریہ ].ul_لمائی_وچ_بائٹاں - 1UL );
                xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;

                إذا( ( ( xRegions[ l_اشاریہ ].ulParameters & پورٹ_MPU_REGION_READ_ONLY ) == پورٹ_MPU_REGION_READ_ONLY ) ||
                    ( ( xRegions[ l_اشاریہ ].ulParameters & پورٹ_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) == پورٹ_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = tskMPU_READ_PERMISSION;
                }

                إذا( ( xRegions[ l_اشاریہ ].ulParameters & پورٹ_MPU_REGION_READ_WRITE ) == پورٹ_MPU_REGION_READ_WRITE )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
                }
            }
            وإلا
            {
                /* Invalidate the region. */
                xMPUSettings->xRegion[ ul ].ul_Region_ادھار_پتہ = ( ( ul - 1UL ) | پورٹ_MPU_REGION_VALID );
                xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_شروع_پتہ = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_سرا_پتہ = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
            }

            l_اشاریہ++;
        }
    }
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    ادھار_Type_t x_پورٹ_Is_Authorized_منزل_Access_بفر( ثابت فراغ * pv_بفر,
                                                size_t x_بفر_لمائی,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_بفر_شروع_پتہ, ul_بفر_سرا_پتہ;
        ادھار_Type_t xAccessGranted = pdFALSE;
        ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( عدم ); /* Calling task's MPU settings. */

        إذا( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        وإلا إذا( ( xTaskMpuSettings->ulTaskFlags & پورٹ_TASK_IS_PRIVILEGED_FLAG ) == پورٹ_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        وإلا
        {
            إذا( پورٹ_جوڑو_UINT32_WILL_حد_توں_ودھ( ( ( uint32_t ) pv_بفر ), ( ( uint32_t ) x_بفر_لمائی - 1UL ) ) == pdFALSE )
            {
                ul_بفر_شروع_پتہ = ( uint32_t ) pv_بفر;
                ul_بفر_سرا_پتہ = ( ( ( uint32_t ) pv_بفر ) + ( uint32_t ) x_بفر_لمائی - 1UL );

                لكل( i = 0; i < پورٹ_کل_عدد_REGIONS_وچ_TCB; i++ )
                {
                    إذا( پورٹ_IS_پتہ_WITHIN_RANGE( ul_بفر_شروع_پتہ,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_شروع_پتہ,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_سرا_پتہ ) &&
                        پورٹ_IS_پتہ_WITHIN_RANGE( ul_بفر_سرا_پتہ,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_شروع_پتہ,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_سرا_پتہ ) &&
                        پورٹ_IS_AUTHORIZED( ulAccessRequested, xTaskMpuSettings->xRegionSettings[ i ].ulRegionPermissions ) )
                    {
                        xAccessGranted = pdTRUE;
                        اكسر;
                    }
                }
            }
        }

        أرجع xAccessGranted;
    }

#جے_انت /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#إذا ( configASSERT_DEFINED == 1 )

    فراغ v_پورٹ_Validate_رکاوٹ_ترجیح( فراغ )
    {
        uint32_t ul_Current_رکاوٹ;
        uint8_t uc_Current_ترجیح;

        /* Obtain the number of the currently executing interrupt. */
        __asm متطاير ( "mrs %0, ipsr" : "=r" ( ul_Current_رکاوٹ )::"memory" );

        /* Is the interrupt number a user defined interrupt? */
        إذا( ul_Current_رکاوٹ >= پورٹ_پہلا_USER_رکاوٹ_نمبر )
        {
            /* Look up the interrupt's priority. */
            uc_Current_ترجیح = pc_رکاوٹ_ترجیح_Registers[ ul_Current_رکاوٹ ];

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
            configASSERT( uc_Current_ترجیح >= uc_Max_Sys_Call_ترجیح );
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
        configASSERT( ( پورٹ_AIRCR_REG & پورٹ_ترجیح_گروہ_نقاب ) <= ulMaxPRIGROUPValue );
    }

#جے_انت /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/

#إذا ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    فراغ v_پورٹ_Grant_Access_منزل_Kernel_Object( TaskHandle_t x_اندرونی_Task_Handle,
                                         int32_t l_اندرونی_اشاریہ_دا_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_اندراج_اشاریہ, ul_Access_Control_List_اندراج_ثنائی_ہندسہ;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_اندراج_اشاریہ = ( ( uint32_t ) l_اندرونی_اشاریہ_دا_Kernel_Object / پورٹ_ACL_اندراج_ناپ_بٹ );
        ul_Access_Control_List_اندراج_ثنائی_ہندسہ = ( ( uint32_t ) l_اندرونی_اشاریہ_دا_Kernel_Object % پورٹ_ACL_اندراج_ناپ_بٹ );

        xTaskMpuSettings = xTaskGetMPUSettings( x_اندرونی_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_اندراج_اشاریہ ] |= ( 1U << ul_Access_Control_List_اندراج_ثنائی_ہندسہ );
    }

#جے_انت /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    فراغ v_پورٹ_Revoke_Access_منزل_Kernel_Object( TaskHandle_t x_اندرونی_Task_Handle,
                                          int32_t l_اندرونی_اشاریہ_دا_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_اندراج_اشاریہ, ul_Access_Control_List_اندراج_ثنائی_ہندسہ;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_اندراج_اشاریہ = ( ( uint32_t ) l_اندرونی_اشاریہ_دا_Kernel_Object / پورٹ_ACL_اندراج_ناپ_بٹ );
        ul_Access_Control_List_اندراج_ثنائی_ہندسہ = ( ( uint32_t ) l_اندرونی_اشاریہ_دا_Kernel_Object % پورٹ_ACL_اندراج_ناپ_بٹ );

        xTaskMpuSettings = xTaskGetMPUSettings( x_اندرونی_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_اندراج_اشاریہ ] &= ~( 1U << ul_Access_Control_List_اندراج_ثنائی_ہندسہ );
    }

#جے_انت /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        ادھار_Type_t x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( int32_t l_اندرونی_اشاریہ_دا_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_اندراج_اشاریہ, ul_Access_Control_List_اندراج_ثنائی_ہندسہ;
            ادھار_Type_t xAccessGranted = pdFALSE;
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

                ul_Access_Control_List_اندراج_اشاریہ = ( ( uint32_t ) l_اندرونی_اشاریہ_دا_Kernel_Object / پورٹ_ACL_اندراج_ناپ_بٹ );
                ul_Access_Control_List_اندراج_ثنائی_ہندسہ = ( ( uint32_t ) l_اندرونی_اشاریہ_دا_Kernel_Object % پورٹ_ACL_اندراج_ناپ_بٹ );

                إذا( ( xTaskMpuSettings->ulTaskFlags & پورٹ_TASK_IS_PRIVILEGED_FLAG ) == پورٹ_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                وإلا
                {
                    إذا( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_اندراج_اشاریہ ] & ( 1U << ul_Access_Control_List_اندراج_ثنائی_ہندسہ ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            أرجع xAccessGranted;
        }

    #وإلا /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        ادھار_Type_t x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( int32_t l_اندرونی_اشاریہ_دا_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( فراغ ) l_اندرونی_اشاریہ_دا_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            أرجع pdTRUE;
        }

    #جے_انت /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#جے_انت /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/
