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
#ضمن <intrinsics.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#تعریف_کن MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "mpu_syscall_numbers.h"

#لغو_تعریف MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#اگر_تعریف_نشده __ARMVFP__
    #خطا This پورت can only be استفاده_شده when the project options are configured مقصد enable hardware floating نقطه_2 support.
#پایان_اگر

#إذا ( config_MAX_SYSCALL_وقفه_اولویت == 0 )
    #خطا config_MAX_SYSCALL_وقفه_اولویت must not be مجموعه مقصد 0.  See http: /*www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
#پایان_اگر

#اگر_تعریف_نشده configSYSTICK_CLOCK_HZ
    #تعریف_کن configSYSTICK_CLOCK_HZ      configCPU_CLOCK_HZ
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #تعریف_کن پورت_NVIC_SYSTICK_CLK_بیت    ( 1UL << 2UL )
#وإلا

/* The way the SysTick is clocked is not modified in case it is not the same
 * as the core. */
    #تعریف_کن پورت_NVIC_SYSTICK_CLK_بیت    ( 0 )
#پایان_اگر

/* Unprivileged critical sections are not supported when using MPU wrappers
 * version 2. Default the option to 0 and reject an explicit value of 1. */
#اگر_تعریف_نشده configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS
    #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
        #تعریف_کن configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    0
    #وإلا
        #warning "configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not defined. We recommend defining it to 0 in FreeRTOSConfig.h for better security."
        #تعریف_کن configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    1
    #پایان_اگر
#وإلا
    #إذا ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) )
        #خطا configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not supported with MPU wrappers نسخه 2 ( configUSE_MPU_WRAPPERS_V1 == 0 ).
    #پایان_اگر
#پایان_اگر

/* Prototype of all Interrupt Service Routines (ISRs). */
تعريفنوع فراغ ( * پورت_ISR_t )( فراغ );

/* Constants required to manipulate the core.  Registers first... */
#تعریف_کن پورت_NVIC_SYSTICK_CTRL_REG                 ( *( ( متطاير uint32_t * ) 0xe000e010 ) )
#تعریف_کن پورت_NVIC_SYSTICK_بارگیری_REG                 ( *( ( متطاير uint32_t * ) 0xe000e014 ) )
#تعریف_کن پورت_NVIC_SYSTICK_CURRENT_مقدار_REG        ( *( ( متطاير uint32_t * ) 0xe000e018 ) )
#تعریف_کن پورت_NVIC_SHPR3_REG                        ( *( ( متطاير uint32_t * ) 0xe000ed20 ) )
#تعریف_کن پورت_NVIC_SHPR2_REG                        ( *( ( متطاير uint32_t * ) 0xe000ed1c ) )
#تعریف_کن پورت_NVIC_SYS_CTRL_STATE_REG               ( *( ( متطاير uint32_t * ) 0xe000ed24 ) )
#تعریف_کن پورت_NVIC_MEM_FAULT_ENABLE                 ( 1UL << 16UL )

/* Constants required to access and manipulate the MPU. */
#تعریف_کن پورت_MPU_TYPE_REG                          ( *( ( متطاير uint32_t * ) 0xe000ed90 ) )
#تعریف_کن پورت_MPU_REGION_پایه_آدرس_REG           ( *( ( متطاير uint32_t * ) 0xe000ed9C ) )
#تعریف_کن پورت_MPU_REGION_ATTRIBUTE_REG              ( *( ( متطاير uint32_t * ) 0xe000edA0 ) )
#تعریف_کن پورت_MPU_CTRL_REG                          ( *( ( متطاير uint32_t * ) 0xe000ed94 ) )
#تعریف_کن پورت_EXPECTED_MPU_TYPE_مقدار               ( config_مجموع_MPU_REGIONS << 8UL )
#تعریف_کن پورت_MPU_ENABLE                            ( 0x01UL )
#تعریف_کن پورت_MPU_BACKGROUND_ENABLE                 ( 1UL << 2UL )
#تعریف_کن پورت_PRIVILEGED_EXECUTION_شروع_آدرس    ( 0UL )
#تعریف_کن پورت_MPU_REGION_VALID                      ( 0x10UL )
#تعریف_کن پورت_MPU_REGION_ENABLE                     ( 0x01UL )
#تعریف_کن پورت_PERIPHERALS_شروع_آدرس             0x40000000UL
#تعریف_کن پورت_PERIPHERALS_انتها_آدرس               0x5FFFFFFFUL

/* ...then bits in the registers. */
#تعریف_کن پورت_NVIC_SYSTICK_INT_بیت                  ( 1UL << 1UL )
#تعریف_کن پورت_NVIC_SYSTICK_ENABLE_بیت               ( 1UL << 0UL )
#تعریف_کن پورت_NVIC_SYSTICK_شمار_FLAG_بیت           ( 1UL << 16UL )
#تعریف_کن پورت_NVIC_PENDSVCLEAR_بیت                  ( 1UL << 27UL )
#تعریف_کن پورت_NVIC_PEND_SYSTICK_CLEAR_بیت           ( 1UL << 25UL )

/* Constants used to detect Cortex-M7 r0p0 and r0p1 cores, and ensure
 * that a work around is active for errata 837070. */
#تعریف_کن پورت_CPUID                                 ( *( ( متطاير uint32_t * ) 0xE000ed00 ) )
#تعریف_کن پورت_CORTEX_M7_r0p1_ID                     ( 0x410FC271UL )
#تعریف_کن پورت_CORTEX_M7_r0p0_ID                     ( 0x410FC270UL )

/* Constants to manipulate FreeRTOS interrupt priorities. */
#تعریف_کن پورت_MIN_وقفه_اولویت                ( 255UL )
#تعریف_کن پورت_NVIC_PENDSV_PRI                       ( ( ( uint32_t ) پورت_MIN_وقفه_اولویت ) << 16UL )
#تعریف_کن پورت_NVIC_SYSTICK_PRI                      ( ( ( uint32_t ) پورت_MIN_وقفه_اولویت ) << 24UL )
#تعریف_کن پورت_NVIC_SVC_PRI                          ( ( ( uint32_t ) config_MAX_SYSCALL_وقفه_اولویت - 1UL ) << 24UL )

/* Constants used to check the installation of the FreeRTOS interrupt handlers. */
#تعریف_کن پورت_SCB_VTOR_REG                          ( *( ( پورت_ISR_t ** ) 0xE000ED08 ) )
#تعریف_کن پورت_وکتور_شاخص_SVC                      ( 11 )
#تعریف_کن پورت_وکتور_شاخص_PENDSV                   ( 14 )

/* Constants required to check the validity of an interrupt priority. */
#تعریف_کن پورت_اولی_USER_وقفه_عدد           ( 16 )
#تعریف_کن پورت_NVIC_IP_REGISTERS_جابه_جایی_16           ( 0xE000E3F0 )
#تعریف_کن پورت_AIRCR_REG                             ( *( ( متطاير uint32_t * ) 0xE000ED0C ) )
#تعریف_کن پورت_MAX_8_بیت_مقدار                       ( ( uint8_t ) 0xff )
#تعریف_کن پورت_بالاترین_بیت_از_BYTE                       ( ( uint8_t ) 0x80 )
#تعریف_کن پورت_MAX_PRIGROUP_بیتها                     ( ( uint8_t ) 7 )
#تعریف_کن پورت_اولویت_گروه_ماسک                   ( 0x07UL << 8UL )
#تعریف_کن پورت_PRIGROUP_لغزش                        ( 8UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#تعریف_کن پورت_VECTACTIVE_ماسک                       ( 0xFFUL )

/* Constants required to manipulate the VFP. */
#تعریف_کن پورت_FPCCR                                 ( ( متطاير uint32_t * ) 0xe000ef34 ) /* Floating point context control register. */
#تعریف_کن پورت_ASPEN_AND_LSPEN_بیتها                  ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#تعریف_کن پورت_INITIAL_XPSR                          ( 0x01000000 )
#تعریف_کن پورت_INITIAL_EXC_RETURN                    ( 0xfffffffd )
#تعریف_کن پورت_INITIAL_CONTROL_IF_UNPRIVILEGED       ( 0x03 )
#تعریف_کن پورت_INITIAL_CONTROL_IF_PRIVILEGED         ( 0x02 )

/* Constants used during system call enter and exit. */
#تعریف_کن پورت_PSR_پشته_PADDING_ماسک                ( 1UL << 9UL )
#تعریف_کن پورت_EXC_RETURN_پشته_قاب_TYPE_ماسک      ( 1UL << 4UL )

/* Offsets in the stack to the parameters when inside the SVC handler. */
#تعریف_کن پورت_جابه_جایی_مقصد_LR                          ( 5 )
#تعریف_کن پورت_جابه_جایی_مقصد_PC                          ( 6 )
#تعریف_کن پورت_جابه_جایی_مقصد_PSR                         ( 7 )

/* The systick is a 24-bit counter. */
#تعریف_کن پورت_MAX_24_بیت_عدد                     ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#تعریف_کن پورت_MISSED_COUNTS_ضریب                  ( 45UL )

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#تعریف_کن پورت_شروع_آدرس_ماسک                    ( ( پشته_Type_t ) 0xfffffffeUL )

/* Does addr lie within [start, end] address range? */
#تعریف_کن پورت_IS_آدرس_WITHIN_RANGE( addr, شروع, انتها ) \
    ( ( ( addr ) >= ( شروع ) ) && ( ( addr ) <= ( انتها ) ) )

/* Is the access request satisfied by the available permissions? */
#تعریف_کن پورت_IS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#تعریف_کن پورت_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کن پورت_جمع_کن_UINT32_WILL_سرریز( a, b )    ( ( a ) > ( پورت_UINT32_MAX - ( b ) ) )
/*-----------------------------------------------------------*/

/*
 * Configure a number of standard MPU regions that are used by all tasks.
 */
ساكن فراغ prv_راهاندازی_MPU( فراغ ) PRIVILEGED_FUNCTION;

/*
 * Return the smallest MPU region size that a given number of bytes will fit
 * into.  The region size is returned as the value that should be programmed
 * into the region attribute register for that region.
 */
ساكن uint32_t prv_Get_MPURegion_اندازه_Setting( uint32_t ul_Actual_اندازه_درون_بایتها ) PRIVILEGED_FUNCTION;

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
فراغ v_پورت_راهاندازی_Timer_وقفه( فراغ );

/*
 * Exception handlers.
 */
فراغ x_پورت_Sys_Tick_Handler( فراغ ) PRIVILEGED_FUNCTION;

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
خارجي فراغ v_پورت_شروع_اولی_Task( فراغ ) PRIVILEGED_FUNCTION;

/*
 * Turn the VFP on.
 */
خارجي فراغ v_پورت_Enable_VFP( فراغ );

/*
 * The C portion of the SVC handler.
 */
فراغ v_پورت_SVCHandler_C( uint32_t * pulParam ) PRIVILEGED_FUNCTION;

/*
 * Called from the SVC handler used to start the scheduler.
 */
خارجي فراغ v_پورت_Restore_Context_از_اولی_Task( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief Enter critical section.
 */
#إذا ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    فراغ v_پورت_Enter_Critical( فراغ ) FREERTOS_SYSTEM_CALL;
#وإلا
    فراغ v_پورت_Enter_Critical( فراغ ) PRIVILEGED_FUNCTION;
#پایان_اگر

/**
 * @brief Exit from critical section.
 */
#إذا ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    فراغ v_پورت_Exit_Critical( فراغ ) FREERTOS_SYSTEM_CALL;
#وإلا
    فراغ v_پورت_Exit_Critical( فراغ ) PRIVILEGED_FUNCTION;
#پایان_اگر

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the system call stack so that upon returning from
 * SVC, the system call stack is used.
 *
 * @param pulTaskStack The current SP when the SVC was raised.
 * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
 * @param ucSystemCallNumber The system call number of the system call.
 */
    فراغ vSystemCallEnter( uint32_t * pul_Task_پشته,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_عدد ) PRIVILEGED_FUNCTION;

#پایان_اگر /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Raise SVC for exiting from a system call.
 */
    فراغ vRequestSystemCallExit( فراغ ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#پایان_اگر /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the task stack so that upon returning from
 * SVC, the task stack is used again.
 *
 * @param pulSystemCallStack The current SP when the SVC was raised.
 * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
 */
    فراغ vSystemCallExit( uint32_t * pul_System_Call_پشته,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#پایان_اگر /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
پایه_Type_t x_پورت_Is_Task_Privileged( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief Make a task unprivileged.
 */
فراغ v_پورت_Switch_مقصد_User_نما( فراغ );

/*
 * FreeRTOS handlers implemented in assembly.
 */
خارجي فراغ v_پورت_SVCHandler( فراغ ) PRIVILEGED_FUNCTION;
خارجي فراغ x_پورت_Pend_SVHandler( فراغ ) PRIVILEGED_FUNCTION;
/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
ساكن UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

/*
 * This variable is set to pdTRUE when the scheduler is started.
 */
    PRIVILEGED_داده ساكن پایه_Type_t xSchedulerRunning = pdFALSE;

#پایان_اگر /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#إذا ( configASSERT_DEFINED == 1 )
    ساكن uint8_t uc_Max_Sys_Call_اولویت = 0;
    ساكن uint32_t ulMaxPRIGROUPValue = 0;
    ساكن ثابت متطاير uint8_t * ثابت pc_وقفه_اولویت_Registers = ( ثابت متطاير uint8_t * ثابت ) پورت_NVIC_IP_REGISTERS_جابه_جایی_16;
#پایان_اگر /* configASSERT_DEFINED */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
پشته_Type_t * px_پورت_Initialise_پشته( پشته_Type_t * px_بالاترین_از_پشته,
                                     TaskFunction_t px_کد,
                                     فراغ * pvParameters,
                                     پایه_Type_t x_پیاپی_Privileged,
                                     xMPU_SETTINGS * xMPUSettings )
{
    إذا( x_پیاپی_Privileged == pdTRUE )
    {
        xMPUSettings->ulTaskFlags |= پورت_TASK_IS_PRIVILEGED_FLAG;
        xMPUSettings->ulContext[ 0 ] = پورت_INITIAL_CONTROL_IF_PRIVILEGED;
    }
    وإلا
    {
        xMPUSettings->ulTaskFlags &= ( ~( پورت_TASK_IS_PRIVILEGED_FLAG ) );
        xMPUSettings->ulContext[ 0 ] = پورت_INITIAL_CONTROL_IF_UNPRIVILEGED;
    }

    xMPUSettings->ulContext[ 1 ] = 0x04040404;                                        /* r4. */
    xMPUSettings->ulContext[ 2 ] = 0x05050505;                                        /* r5. */
    xMPUSettings->ulContext[ 3 ] = 0x06060606;                                        /* r6. */
    xMPUSettings->ulContext[ 4 ] = 0x07070707;                                        /* r7. */
    xMPUSettings->ulContext[ 5 ] = 0x08080808;                                        /* r8. */
    xMPUSettings->ulContext[ 6 ] = 0x09090909;                                        /* r9. */
    xMPUSettings->ulContext[ 7 ] = 0x10101010;                                        /* r10. */
    xMPUSettings->ulContext[ 8 ] = 0x11111111;                                        /* r11. */
    xMPUSettings->ulContext[ 9 ] = پورت_INITIAL_EXC_RETURN;                            /* EXC_RETURN. */

    xMPUSettings->ulContext[ 10 ] = ( uint32_t ) ( px_بالاترین_از_پشته - 8 );                /* PSP with the hardware saved stack. */
    xMPUSettings->ulContext[ 11 ] = ( uint32_t ) pvParameters;                        /* r0. */
    xMPUSettings->ulContext[ 12 ] = 0x01010101;                                       /* r1. */
    xMPUSettings->ulContext[ 13 ] = 0x02020202;                                       /* r2. */
    xMPUSettings->ulContext[ 14 ] = 0x03030303;                                       /* r3. */
    xMPUSettings->ulContext[ 15 ] = 0x12121212;                                       /* r12. */
    xMPUSettings->ulContext[ 16 ] = 0;                                                /* LR. */
    xMPUSettings->ulContext[ 17 ] = ( ( uint32_t ) px_کد ) & پورت_شروع_آدرس_ماسک; /* PC. */
    xMPUSettings->ulContext[ 18 ] = پورت_INITIAL_XPSR;                                 /* xPSR. */

    #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        /* Ensure that the system call stack is double word aligned. */
        xMPUSettings->x_System_Call_پشته_Info.pul_System_Call_پشته = &( xMPUSettings->x_System_Call_پشته_Info.ul_System_Call_پشته_میانگیر[ config_SYSTEM_CALL_پشته_اندازه - 1 ] );
        xMPUSettings->x_System_Call_پشته_Info.pul_System_Call_پشته = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_پشته_Info.pul_System_Call_پشته ) &
                                                                                 ( uint32_t ) ( ~( پورت_BYTE_ALIGNMENT_ماسک ) ) );

        /* This is not NULL only for the duration of a system call. */
        xMPUSettings->x_System_Call_پشته_Info.pul_Task_پشته = عدم;
    }
    #پایان_اگر /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    أرجع &( xMPUSettings->ulContext[ 19 ] );
}
/*-----------------------------------------------------------*/

فراغ v_پورت_SVCHandler_C( uint32_t * pulParam ) /* PRIVILEGED_FUNCTION */
{
    uint8_t ucSVCNumber;
    uint32_t ulPC;

    #إذا ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) )
        خارجي uint32_t __syscalls_flash_start__[];
        خارجي uint32_t __syscalls_flash_end__[];
    #پایان_اگر /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) ) */

    /* The stack contains: r0, r1, r2, r3, r12, LR, PC and xPSR. The first
     * argument (r0) is pulParam[ 0 ]. */
    ulPC = pulParam[ پورت_جابه_جایی_مقصد_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    بدل( ucSVCNumber )
    {
        حالة پورت_SVC_شروع_SCHEDULER:
            v_پورت_Restore_Context_از_اولی_Task();
            اكسر;

        حالة پورت_SVC_YIELD:
            پورت_NVIC_INT_CTRL_REG = پورت_NVIC_PENDSVSET_بیت;

            /* Barriers are normally not required
             * but do ensure the code is completely
             * within the specified behaviour for the
             * architecture. */
            __asm متطاير ( "dsb" ::: "memory" );
            __asm متطاير ( "isb" );

            اكسر;

    #إذا ( configUSE_MPU_WRAPPERS_V1 == 1 )
        #إذا ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 )
            حالة پورت_SVC_RAISE_PRIVILEGE: /* Only raise the privilege, if the
                                           * svc was raised from any of the
                                           * system calls. */

                إذا( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                    ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
                {
                    __asm متطاير
                    (
                        "   mrs r1, control     \n" /* Obtain current control value. */
                        "   bic r1, r1, #1      \n" /* Set privilege bit. */
                        "   msr control, r1     \n" /* Write back new control value. */
                        ::: "r1", "memory"
                    );
                }

                اكسر;
        #وإلا /* if ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
            حالة پورت_SVC_RAISE_PRIVILEGE:
                __asm متطاير
                (
                    "   mrs r1, control     \n" /* Obtain current control value. */
                    "   bic r1, r1, #1      \n" /* Set privilege bit. */
                    "   msr control, r1     \n" /* Write back new control value. */
                    ::: "r1", "memory"
                );
                اكسر;
        #پایان_اگر /* #if( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
    #پایان_اگر /* #if ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

        افتراضي: /* Unknown SVC call. */
            اكسر;
    }
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    فراغ vSystemCallEnter( uint32_t * pul_Task_پشته,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_عدد ) /* PRIVILEGED_FUNCTION */
    {
        خارجي TaskHandle_t pxCurrentTCB;
        خارجي UBaseType_t uxSystemCallImplementations[ رقم_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_پشته;
        uint32_t ul_Hardware_Saved_Exception_قاب_اندازه, ulSystemCallLocation, i;

        #إذا defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint32_t * __syscalls_flash_start__;
            خارجي uint32_t * __syscalls_flash_end__;
        #وإلا
            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint32_t __syscalls_flash_start__[];
            خارجي uint32_t __syscalls_flash_end__[];
        #پایان_اگر /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_پشته[ پورت_جابه_جایی_مقصد_PC ];
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
            ( pxMpuSettings->x_System_Call_پشته_Info.pul_Task_پشته == عدم ) &&
            ( uxSystemCallImplementations[ uc_System_Call_عدد ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_پشته = pxMpuSettings->x_System_Call_پشته_Info.pul_System_Call_پشته;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            إذا( ( ulLR & پورت_EXC_RETURN_پشته_قاب_TYPE_ماسک ) == 0UL )
            {
                /* Extended frame i.e. FPU in use. */
                ul_Hardware_Saved_Exception_قاب_اندازه = 26;
                __asm متطاير (
                    " vpush {s0}         \n" /* Trigger lazy stacking. */
                    " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                    ::: "memory"
                    );
            }
            وإلا
            {
                /* Standard frame i.e. FPU not in use. */
                ul_Hardware_Saved_Exception_قاب_اندازه = 8;
            }

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_پشته = pul_System_Call_پشته - ul_Hardware_Saved_Exception_قاب_اندازه;

            /* Copy the stack frame. */
            لكل( i = 0; i < ul_Hardware_Saved_Exception_قاب_اندازه; i++ )
            {
                pul_System_Call_پشته[ i ] = pul_Task_پشته[ i ];
            }

            /* Use the pulSystemCallStack in thread mode. */
            __asm متطاير ( "msr psp, %0" : : "r" ( pul_System_Call_پشته ) );

            /* Raise the privilege for the duration of the system call. */
            __asm متطاير (
                " mrs r1, control     \n" /* Obtain current control value. */
                " bic r1, #1          \n" /* Clear nPRIV bit. */
                " msr control, r1     \n" /* Write back new control value. */
                ::: "r1", "memory"
                );

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_پشته_Info.pul_Task_پشته = pul_Task_پشته + ul_Hardware_Saved_Exception_قاب_اندازه;

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_پشته_Info.ul_Link_ثبات_At_System_Call_مدخل = pul_Task_پشته[ پورت_جابه_جایی_مقصد_LR ];


            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_پشته[ پورت_جابه_جایی_مقصد_PC ] = uxSystemCallImplementations[ uc_System_Call_عدد ];
            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_پشته[ پورت_جابه_جایی_مقصد_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            إذا( ( pul_Task_پشته[ پورت_جابه_جایی_مقصد_PSR ] & پورت_PSR_پشته_PADDING_ماسک ) == پورت_PSR_پشته_PADDING_ماسک )
            {
                pxMpuSettings->ulTaskFlags |= پورت_پشته_قاب_HAS_PADDING_FLAG;
            }
            وإلا
            {
                pxMpuSettings->ulTaskFlags &= ( ~پورت_پشته_قاب_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_پشته[ پورت_جابه_جایی_مقصد_PSR ] &= ( ~پورت_PSR_پشته_PADDING_ماسک );
        }
    }

#پایان_اگر /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    فراغ vRequestSystemCallExit( فراغ ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm متطاير ( "svc %0 \n" ::"i" ( پورت_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#پایان_اگر /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    فراغ vSystemCallExit( uint32_t * pul_System_Call_پشته,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        خارجي TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_پشته;
        uint32_t ul_Hardware_Saved_Exception_قاب_اندازه, ulSystemCallLocation, i;

        #إذا defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint32_t * __privileged_functions_start__;
            خارجي uint32_t * __privileged_functions_end__;
        #وإلا
            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint32_t __privileged_functions_start__[];
            خارجي uint32_t __privileged_functions_end__[];
        #پایان_اگر /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_پشته[ پورت_جابه_جایی_مقصد_PC ];
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
            ( pxMpuSettings->x_System_Call_پشته_Info.pul_Task_پشته != عدم ) )
        {
            pul_Task_پشته = pxMpuSettings->x_System_Call_پشته_Info.pul_Task_پشته;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            إذا( ( ulLR & پورت_EXC_RETURN_پشته_قاب_TYPE_ماسک ) == 0UL )
            {
                /* Extended frame i.e. FPU in use. */
                ul_Hardware_Saved_Exception_قاب_اندازه = 26;
                __asm متطاير (
                    " vpush {s0}         \n" /* Trigger lazy stacking. */
                    " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                    ::: "memory"
                    );
            }
            وإلا
            {
                /* Standard frame i.e. FPU not in use. */
                ul_Hardware_Saved_Exception_قاب_اندازه = 8;
            }

            /* Make space on the task stack for the stack frame. */
            pul_Task_پشته = pul_Task_پشته - ul_Hardware_Saved_Exception_قاب_اندازه;

            /* Copy the stack frame. */
            لكل( i = 0; i < ul_Hardware_Saved_Exception_قاب_اندازه; i++ )
            {
                pul_Task_پشته[ i ] = pul_System_Call_پشته[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm متطاير ( "msr psp, %0" : : "r" ( pul_Task_پشته ) );

            /* Drop the privilege before returning to the thread mode. */
            __asm متطاير (
                " mrs r1, control     \n" /* Obtain current control value. */
                " orr r1, #1          \n" /* Set nPRIV bit. */
                " msr control, r1     \n" /* Write back new control value. */
                ::: "r1", "memory"
                );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_پشته[ پورت_جابه_جایی_مقصد_PC ] = pxMpuSettings->x_System_Call_پشته_Info.ul_Link_ثبات_At_System_Call_مدخل;
            /* Ensure that LR has a valid value.*/
            pul_Task_پشته[ پورت_جابه_جایی_مقصد_LR ] = pxMpuSettings->x_System_Call_پشته_Info.ul_Link_ثبات_At_System_Call_مدخل;

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            إذا( ( pxMpuSettings->ulTaskFlags & پورت_پشته_قاب_HAS_PADDING_FLAG ) == پورت_پشته_قاب_HAS_PADDING_FLAG )
            {
                pul_Task_پشته[ پورت_جابه_جایی_مقصد_PSR ] |= پورت_PSR_پشته_PADDING_ماسک;
            }
            وإلا
            {
                pul_Task_پشته[ پورت_جابه_جایی_مقصد_PSR ] &= ( ~پورت_PSR_پشته_PADDING_ماسک );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_پشته_Info.pul_Task_پشته = عدم;
        }
    }

#پایان_اگر /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

پایه_Type_t x_پورت_Is_Task_Privileged( فراغ ) /* PRIVILEGED_FUNCTION */
{
    پایه_Type_t xTaskIsPrivileged = pdFALSE;
    ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( عدم ); /* Calling task's MPU settings. */

    إذا( ( xTaskMpuSettings->ulTaskFlags & پورت_TASK_IS_PRIVILEGED_FLAG ) == پورت_TASK_IS_PRIVILEGED_FLAG )
    {
        xTaskIsPrivileged = pdTRUE;
    }

    أرجع xTaskIsPrivileged;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Switch_مقصد_User_نما( فراغ )
{
    /* Load the current task's MPU settings from its TCB. */
    xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( عدم );

    /* Mark the task as unprivileged. */
    xTaskMpuSettings->ulTaskFlags &= ( ~( پورت_TASK_IS_PRIVILEGED_FLAG ) );

    /* Lower the processor's privilege level. */
    vResetPrivilege();
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
پایه_Type_t x_پورت_شروع_Scheduler( فراغ )
{
    /* Errata 837070 workaround must only be enabled on Cortex-M7 r0p0
     * and r0p1 cores. */
    #إذا ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        configASSERT( ( پورت_CPUID == پورت_CORTEX_M7_r0p1_ID ) || ( پورت_CPUID == پورت_CORTEX_M7_r0p0_ID ) );
    #وإلا

        /* When using this port on a Cortex-M7 r0p0 or r0p1 core, define
         * configENABLE_ERRATA_837070_WORKAROUND to 1 in your
         * FreeRTOSConfig.h. */
        configASSERT( پورت_CPUID != پورت_CORTEX_M7_r0p1_ID );
        configASSERT( پورت_CPUID != پورت_CORTEX_M7_r0p0_ID );
    #پایان_اگر

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
        ثابت پورت_ISR_t * ثابت px_وکتور_جدول = پورت_SCB_VTOR_REG;

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
        configASSERT( px_وکتور_جدول[ پورت_وکتور_شاخص_SVC ] == v_پورت_SVCHandler );
        configASSERT( px_وکتور_جدول[ پورت_وکتور_شاخص_PENDSV ] == x_پورت_Pend_SVHandler );
    }
    #پایان_اگر /* configCHECK_HANDLER_INSTALLATION */

    #إذا ( configASSERT_DEFINED == 1 )
    {
        متطاير uint8_t uc_Original_اولویت;
        متطاير uint32_t ul_Implemented_Prio_بیتها = 0;
        متطاير uint8_t * ثابت puc_اولی_User_اولویت_ثبات = ( متطاير uint8_t * ثابت ) ( پورت_NVIC_IP_REGISTERS_جابه_جایی_16 + پورت_اولی_USER_وقفه_عدد );
        متطاير uint8_t uc_Max_اولویت_مقدار;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
         * functions can be called.  ISR safe functions are those that end in
         * "FromISR".  FreeRTOS maintains separate thread and ISR API functions to
         * ensure interrupt entry is as fast and simple as possible.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_اولویت = *puc_اولی_User_اولویت_ثبات;

        /* Determine the number of priority bits available.  First write to all
         * possible bits. */
        *puc_اولی_User_اولویت_ثبات = پورت_MAX_8_بیت_مقدار;

        /* Read the value back to see how many bits stuck. */
        uc_Max_اولویت_مقدار = *puc_اولی_User_اولویت_ثبات;

        /* Use the same mask on the maximum system call priority. */
        uc_Max_Sys_Call_اولویت = config_MAX_SYSCALL_وقفه_اولویت & uc_Max_اولویت_مقدار;

        /* Check that the maximum system call priority is nonzero after
         * accounting for the number of priority bits supported by the
         * hardware. A priority of 0 is invalid because setting the BASEPRI
         * register to 0 unmasks all interrupts, and interrupts with priority 0
         * cannot be masked using BASEPRI.
         * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( uc_Max_Sys_Call_اولویت );

        /* Check that the bits not implemented in hardware are zero in
         * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( config_MAX_SYSCALL_وقفه_اولویت & ( uint8_t ) ( ~( uint32_t ) uc_Max_اولویت_مقدار ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
         * of bits read back. */

        طالما( ( uc_Max_اولویت_مقدار & پورت_بالاترین_بیت_از_BYTE ) == پورت_بالاترین_بیت_از_BYTE )
        {
            ul_Implemented_Prio_بیتها++;
            uc_Max_اولویت_مقدار <<= ( uint8_t ) 0x01;
        }

        إذا( ul_Implemented_Prio_بیتها == 8 )
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
            configASSERT( ( config_MAX_SYSCALL_وقفه_اولویت & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        وإلا
        {
            ulMaxPRIGROUPValue = پورت_MAX_PRIGROUP_بیتها - ul_Implemented_Prio_بیتها;
        }

        /* Shift the priority group value back to its position within the AIRCR
         * register. */
        ulMaxPRIGROUPValue <<= پورت_PRIGROUP_لغزش;
        ulMaxPRIGROUPValue &= پورت_اولویت_گروه_ماسک;

        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_اولی_User_اولویت_ثبات = uc_Original_اولویت;
    }
    #پایان_اگر /* configASSERT_DEFINED */

    /* Make PendSV and SysTick the lowest priority interrupts, and configure
     * SVCall for sufficient preemption priority. */
    پورت_NVIC_SHPR3_REG |= پورت_NVIC_PENDSV_PRI;
    پورت_NVIC_SHPR3_REG |= پورت_NVIC_SYSTICK_PRI;
    پورت_NVIC_SHPR2_REG = پورت_NVIC_SVC_PRI;

    /* Configure the regions in the MPU that are common to all tasks. */
    prv_راهاندازی_MPU();

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_پورت_راهاندازی_Timer_وقفه();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        xSchedulerRunning = pdTRUE;
    }
    #پایان_اگر /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    /* Ensure the VFP is enabled - it should be anyway. */
    v_پورت_Enable_VFP();

    /* Lazy save always. */
    *( پورت_FPCCR ) |= پورت_ASPEN_AND_LSPEN_بیتها;

    /* Start the first task. */
    v_پورت_شروع_اولی_Task();

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_انتها_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Enter_Critical( فراغ )
{
    #إذا ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        إذا( پورت_IS_PRIVILEGED() == pdFALSE )
        {
            پورت_RAISE_PRIVILEGE();
            پورت_حافظه_BARRIER();

            پورت_DISABLE_INTERRUPTS();
            uxCriticalNesting++;

            /* This is not the interrupt safe version of the enter critical function so
             * assert() if it is being called from an interrupt context.  Only API
             * functions that end in "FromISR" can be used in an interrupt.  Only assert if
             * the critical nesting count is 1 to protect against recursive calls if the
             * assert function also uses a critical section. */
            إذا( uxCriticalNesting == 1 )
            {
                configASSERT( ( پورت_NVIC_INT_CTRL_REG & پورت_VECTACTIVE_ماسک ) == 0 );
            }

            پورت_حافظه_BARRIER();

            پورت_RESET_PRIVILEGE();
            پورت_حافظه_BARRIER();
        }
        وإلا
        {
            پورت_DISABLE_INTERRUPTS();
            uxCriticalNesting++;

            /* This is not the interrupt safe version of the enter critical function so
             * assert() if it is being called from an interrupt context.  Only API
             * functions that end in "FromISR" can be used in an interrupt.  Only assert if
             * the critical nesting count is 1 to protect against recursive calls if the
             * assert function also uses a critical section. */
            إذا( uxCriticalNesting == 1 )
            {
                configASSERT( ( پورت_NVIC_INT_CTRL_REG & پورت_VECTACTIVE_ماسک ) == 0 );
            }
        }
    #وإلا /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        پورت_DISABLE_INTERRUPTS();
        uxCriticalNesting++;

        /* This is not the interrupt safe version of the enter critical function so
         * assert() if it is being called from an interrupt context.  Only API
         * functions that end in "FromISR" can be used in an interrupt.  Only assert if
         * the critical nesting count is 1 to protect against recursive calls if the
         * assert function also uses a critical section. */
        إذا( uxCriticalNesting == 1 )
        {
            configASSERT( ( پورت_NVIC_INT_CTRL_REG & پورت_VECTACTIVE_ماسک ) == 0 );
        }
    #پایان_اگر /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Exit_Critical( فراغ )
{
    #إذا ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        إذا( پورت_IS_PRIVILEGED() == pdFALSE )
        {
            پورت_RAISE_PRIVILEGE();
            پورت_حافظه_BARRIER();

            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            إذا( uxCriticalNesting == 0 )
            {
                پورت_ENABLE_INTERRUPTS();
            }

            پورت_حافظه_BARRIER();

            پورت_RESET_PRIVILEGE();
            پورت_حافظه_BARRIER();
        }
        وإلا
        {
            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            إذا( uxCriticalNesting == 0 )
            {
                پورت_ENABLE_INTERRUPTS();
            }
        }
    #وإلا /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        configASSERT( uxCriticalNesting );
        uxCriticalNesting--;

        إذا( uxCriticalNesting == 0 )
        {
            پورت_ENABLE_INTERRUPTS();
        }
    #پایان_اگر /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

فراغ x_پورت_Sys_Tick_Handler( فراغ )
{
    /* The SysTick runs at the lowest interrupt priority, so when this interrupt
     * executes all interrupts must be unmasked.  There is therefore no need to
     * save and then restore the interrupt mask value as its value is already
     * known. */
    پورت_DISABLE_INTERRUPTS();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_مقصد_SCHEDULER();

            /* A context switch is required.  Context switching is performed in
             * the PendSV interrupt.  Pend the PendSV interrupt. */
            پورت_NVIC_INT_CTRL_REG = پورت_NVIC_PENDSVSET_بیت;
        }
        وإلا
        {
            traceISR_EXIT();
        }
    }
    پورت_ENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__weak فراغ v_پورت_راهاندازی_Timer_وقفه( فراغ )
{
    /* Stop and clear the SysTick. */
    پورت_NVIC_SYSTICK_CTRL_REG = 0UL;
    پورت_NVIC_SYSTICK_CURRENT_مقدار_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    پورت_NVIC_SYSTICK_بارگیری_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_نرخ_HZ ) - 1UL;
    پورت_NVIC_SYSTICK_CTRL_REG = ( پورت_NVIC_SYSTICK_CLK_بیت | پورت_NVIC_SYSTICK_INT_بیت | پورت_NVIC_SYSTICK_ENABLE_بیت );
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_راهاندازی_MPU( فراغ )
{
    خارجي uint32_t __privileged_functions_start__[];
    خارجي uint32_t __privileged_functions_end__[];
    خارجي uint32_t __FLASH_segment_start__[];
    خارجي uint32_t __FLASH_segment_end__[];
    خارجي uint32_t __privileged_data_start__[];
    خارجي uint32_t __privileged_data_end__[];

    /* The only permitted number of regions are 8 or 16. */
    configASSERT( ( config_مجموع_MPU_REGIONS == 8 ) || ( config_مجموع_MPU_REGIONS == 16 ) );

    /* Ensure that the configTOTAL_MPU_REGIONS is configured correctly. */
    configASSERT( پورت_MPU_TYPE_REG == پورت_EXPECTED_MPU_TYPE_مقدار );

    /* Check the expected MPU is present. */
    إذا( پورت_MPU_TYPE_REG == پورت_EXPECTED_MPU_TYPE_مقدار )
    {
        /* First setup the unprivileged flash for unprivileged read only access. */
        پورت_MPU_REGION_پایه_آدرس_REG = ( ( uint32_t ) __FLASH_segment_start__ ) | /* Base address. */
                                          ( پورت_MPU_REGION_VALID ) |
                                          ( پورت_UNPRIVILEGED_FLASH_REGION );

        پورت_MPU_REGION_ATTRIBUTE_REG = ( پورت_MPU_REGION_READ_ONLY ) |
                                       ( ( configTEX_S_C_B_FLASH & پورت_MPU_RASR_TEX_S_C_B_ماسک ) << پورت_MPU_RASR_TEX_S_C_B_LOCATION ) |
                                       ( prv_Get_MPURegion_اندازه_Setting( ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__ ) ) |
                                       ( پورت_MPU_REGION_ENABLE );

        /* Setup the privileged flash for privileged only access.  This is where
         * the kernel code is placed. */
        پورت_MPU_REGION_پایه_آدرس_REG = ( ( uint32_t ) __privileged_functions_start__ ) | /* Base address. */
                                          ( پورت_MPU_REGION_VALID ) |
                                          ( پورت_PRIVILEGED_FLASH_REGION );

        پورت_MPU_REGION_ATTRIBUTE_REG = ( پورت_MPU_REGION_PRIVILEGED_READ_ONLY ) |
                                       ( ( configTEX_S_C_B_FLASH & پورت_MPU_RASR_TEX_S_C_B_ماسک ) << پورت_MPU_RASR_TEX_S_C_B_LOCATION ) |
                                       ( prv_Get_MPURegion_اندازه_Setting( ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__ ) ) |
                                       ( پورت_MPU_REGION_ENABLE );

        /* Setup the privileged data RAM region.  This is where the kernel data
         * is placed. */
        پورت_MPU_REGION_پایه_آدرس_REG = ( ( uint32_t ) __privileged_data_start__ ) | /* Base address. */
                                          ( پورت_MPU_REGION_VALID ) |
                                          ( پورت_PRIVILEGED_RAM_REGION );

        پورت_MPU_REGION_ATTRIBUTE_REG = ( پورت_MPU_REGION_PRIVILEGED_READ_WRITE ) |
                                       ( پورت_MPU_REGION_EXECUTE_NEVER ) |
                                       ( ( configTEX_S_C_B_SRAM & پورت_MPU_RASR_TEX_S_C_B_ماسک ) << پورت_MPU_RASR_TEX_S_C_B_LOCATION ) |
                                       prv_Get_MPURegion_اندازه_Setting( ( uint32_t ) __privileged_data_end__ - ( uint32_t ) __privileged_data_start__ ) |
                                       ( پورت_MPU_REGION_ENABLE );

        /* By default allow everything to access the general peripherals.  The
         * system peripherals and registers are protected. */
        پورت_MPU_REGION_پایه_آدرس_REG = ( پورت_PERIPHERALS_شروع_آدرس ) |
                                          ( پورت_MPU_REGION_VALID ) |
                                          ( پورت_GENERAL_PERIPHERALS_REGION );

        پورت_MPU_REGION_ATTRIBUTE_REG = ( پورت_MPU_REGION_READ_WRITE | پورت_MPU_REGION_EXECUTE_NEVER ) |
                                       ( prv_Get_MPURegion_اندازه_Setting( پورت_PERIPHERALS_انتها_آدرس - پورت_PERIPHERALS_شروع_آدرس ) ) |
                                       ( پورت_MPU_REGION_ENABLE );

        /* Enable the memory fault exception. */
        پورت_NVIC_SYS_CTRL_STATE_REG |= پورت_NVIC_MEM_FAULT_ENABLE;

        /* Enable the MPU with the background region configured. */
        پورت_MPU_CTRL_REG |= ( پورت_MPU_ENABLE | پورت_MPU_BACKGROUND_ENABLE );
    }
}
/*-----------------------------------------------------------*/

ساكن uint32_t prv_Get_MPURegion_اندازه_Setting( uint32_t ul_Actual_اندازه_درون_بایتها )
{
    uint32_t ul_Region_اندازه, ul_Return_مقدار = 4;

    /* 32 is the smallest region size, 31 is the largest valid value for
     * ulReturnValue. */
    لكل( ul_Region_اندازه = 32UL; ul_Return_مقدار < 31UL; ( ul_Region_اندازه <<= 1UL ) )
    {
        إذا( ul_Actual_اندازه_درون_بایتها <= ul_Region_اندازه )
        {
            اكسر;
        }
        وإلا
        {
            ul_Return_مقدار++;
        }
    }

    /* Shift the code by one before returning so it can be written directly
     * into the correct bit position of the attribute register. */
    أرجع( ul_Return_مقدار << 1UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                ثابت بنية x_حافظه_REGION * ثابت xRegions,
                                پشته_Type_t * px_Bottom_از_پشته,
                                config_پشته_عمق_TYPE ux_پشته_عمق )
{
    خارجي uint32_t __SRAM_segment_start__[];
    خارجي uint32_t __SRAM_segment_end__[];
    خارجي uint32_t __privileged_data_start__[];
    خارجي uint32_t __privileged_data_end__[];
    int32_t l_شاخص;
    uint32_t ul;

    إذا( xRegions == عدم )
    {
        /* No MPU regions are specified so allow access to all RAM. */
        xMPUSettings->xRegion[ 0 ].ul_Region_پایه_آدرس =
            ( ( uint32_t ) __SRAM_segment_start__ ) | /* Base address. */
            ( پورت_MPU_REGION_VALID ) |
            ( پورت_پشته_REGION );                     /* Region number. */

        xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
            ( پورت_MPU_REGION_READ_WRITE ) |
            ( پورت_MPU_REGION_EXECUTE_NEVER ) |
            ( ( configTEX_S_C_B_SRAM & پورت_MPU_RASR_TEX_S_C_B_ماسک ) << پورت_MPU_RASR_TEX_S_C_B_LOCATION ) |
            ( prv_Get_MPURegion_اندازه_Setting( ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__ ) ) |
            ( پورت_MPU_REGION_ENABLE );

        xMPUSettings->xRegionSettings[ 0 ].ul_Region_شروع_آدرس = ( uint32_t ) __SRAM_segment_start__;
        xMPUSettings->xRegionSettings[ 0 ].ul_Region_انتها_آدرس = ( uint32_t ) __SRAM_segment_end__;
        xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                   tskMPU_WRITE_PERMISSION );

        /* Invalidate user configurable regions. */
        لكل( ul = 1UL; ul <= پورت_رقم_CONFIGURABLE_REGIONS; ul++ )
        {
            xMPUSettings->xRegion[ ul ].ul_Region_پایه_آدرس = ( ( ul - 1UL ) | پورت_MPU_REGION_VALID );
            xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ul_Region_شروع_آدرس = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ul_Region_انتها_آدرس = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
        }
    }
    وإلا
    {
        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid.  At all other
         * times the stack parameters will not be valid and it is assumed that the
         * stack region has already been configured. */
        إذا( ux_پشته_عمق > 0 )
        {
            /* Define the region that allows access to the stack. */
            xMPUSettings->xRegion[ 0 ].ul_Region_پایه_آدرس =
                ( ( uint32_t ) px_Bottom_از_پشته ) |
                ( پورت_MPU_REGION_VALID ) |
                ( پورت_پشته_REGION ); /* Region number. */

            xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
                ( پورت_MPU_REGION_READ_WRITE ) |
                ( پورت_MPU_REGION_EXECUTE_NEVER ) |
                ( prv_Get_MPURegion_اندازه_Setting( ux_پشته_عمق * ( config_پشته_عمق_TYPE ) حجم( پشته_Type_t ) ) ) |
                ( ( configTEX_S_C_B_SRAM & پورت_MPU_RASR_TEX_S_C_B_ماسک ) << پورت_MPU_RASR_TEX_S_C_B_LOCATION ) |
                ( پورت_MPU_REGION_ENABLE );

            xMPUSettings->xRegionSettings[ 0 ].ul_Region_شروع_آدرس = ( uint32_t ) px_Bottom_از_پشته;
            xMPUSettings->xRegionSettings[ 0 ].ul_Region_انتها_آدرس = ( uint32_t ) ( ( uint32_t ) ( px_Bottom_از_پشته ) +
                                                                                   ( ux_پشته_عمق * ( config_پشته_عمق_TYPE ) حجم( پشته_Type_t ) ) - 1UL );
            xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                       tskMPU_WRITE_PERMISSION );
        }

        l_شاخص = 0;

        لكل( ul = 1UL; ul <= پورت_رقم_CONFIGURABLE_REGIONS; ul++ )
        {
            إذا( ( xRegions[ l_شاخص ] ).ul_درازی_درون_بایتها > 0UL )
            {
                /* Translate the generic region definition contained in
                 * xRegions into the CM4 specific MPU settings that are then
                 * stored in xMPUSettings. */
                xMPUSettings->xRegion[ ul ].ul_Region_پایه_آدرس =
                    ( ( uint32_t ) xRegions[ l_شاخص ].pv_پایه_آدرس ) |
                    ( پورت_MPU_REGION_VALID ) |
                    ( ul - 1UL ); /* Region number. */

                xMPUSettings->xRegion[ ul ].ulRegionAttribute =
                    ( prv_Get_MPURegion_اندازه_Setting( xRegions[ l_شاخص ].ul_درازی_درون_بایتها ) ) |
                    ( xRegions[ l_شاخص ].ulParameters ) |
                    ( پورت_MPU_REGION_ENABLE );

                xMPUSettings->xRegionSettings[ ul ].ul_Region_شروع_آدرس = ( uint32_t ) xRegions[ l_شاخص ].pv_پایه_آدرس;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_انتها_آدرس = ( uint32_t ) ( ( uint32_t ) xRegions[ l_شاخص ].pv_پایه_آدرس + xRegions[ l_شاخص ].ul_درازی_درون_بایتها - 1UL );
                xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;

                إذا( ( ( xRegions[ l_شاخص ].ulParameters & پورت_MPU_REGION_READ_ONLY ) == پورت_MPU_REGION_READ_ONLY ) ||
                    ( ( xRegions[ l_شاخص ].ulParameters & پورت_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) == پورت_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = tskMPU_READ_PERMISSION;
                }

                إذا( ( xRegions[ l_شاخص ].ulParameters & پورت_MPU_REGION_READ_WRITE ) == پورت_MPU_REGION_READ_WRITE )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
                }
            }
            وإلا
            {
                /* Invalidate the region. */
                xMPUSettings->xRegion[ ul ].ul_Region_پایه_آدرس = ( ( ul - 1UL ) | پورت_MPU_REGION_VALID );
                xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_شروع_آدرس = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_انتها_آدرس = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
            }

            l_شاخص++;
        }
    }
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    پایه_Type_t x_پورت_Is_Authorized_مقصد_Access_میانگیر( ثابت فراغ * pv_میانگیر,
                                                size_t x_میانگیر_درازی,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_میانگیر_شروع_آدرس, ul_میانگیر_انتها_آدرس;
        پایه_Type_t xAccessGranted = pdFALSE;
        ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( عدم ); /* Calling task's MPU settings. */

        إذا( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        وإلا إذا( ( xTaskMpuSettings->ulTaskFlags & پورت_TASK_IS_PRIVILEGED_FLAG ) == پورت_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        وإلا
        {
            إذا( پورت_جمع_کن_UINT32_WILL_سرریز( ( ( uint32_t ) pv_میانگیر ), ( ( uint32_t ) x_میانگیر_درازی - 1UL ) ) == pdFALSE )
            {
                ul_میانگیر_شروع_آدرس = ( uint32_t ) pv_میانگیر;
                ul_میانگیر_انتها_آدرس = ( ( ( uint32_t ) pv_میانگیر ) + ( uint32_t ) x_میانگیر_درازی - 1UL );

                لكل( i = 0; i < پورت_مجموع_رقم_REGIONS_درون_TCB; i++ )
                {
                    إذا( پورت_IS_آدرس_WITHIN_RANGE( ul_میانگیر_شروع_آدرس,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_شروع_آدرس,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_انتها_آدرس ) &&
                        پورت_IS_آدرس_WITHIN_RANGE( ul_میانگیر_انتها_آدرس,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_شروع_آدرس,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_انتها_آدرس ) &&
                        پورت_IS_AUTHORIZED( ulAccessRequested, xTaskMpuSettings->xRegionSettings[ i ].ulRegionPermissions ) )
                    {
                        xAccessGranted = pdTRUE;
                        اكسر;
                    }
                }
            }
        }

        أرجع xAccessGranted;
    }

#پایان_اگر /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/


#إذا ( configASSERT_DEFINED == 1 )

    فراغ v_پورت_Validate_وقفه_اولویت( فراغ )
    {
        uint32_t ul_Current_وقفه;
        uint8_t uc_Current_اولویت;

        /* Obtain the number of the currently executing interrupt. */
        __asm متطاير ( "mrs %0, ipsr" : "=r" ( ul_Current_وقفه )::"memory" );

        /* Is the interrupt number a user defined interrupt? */
        إذا( ul_Current_وقفه >= پورت_اولی_USER_وقفه_عدد )
        {
            /* Look up the interrupt's priority. */
            uc_Current_اولویت = pc_وقفه_اولویت_Registers[ ul_Current_وقفه ];

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
            configASSERT( uc_Current_اولویت >= uc_Max_Sys_Call_اولویت );
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
        configASSERT( ( پورت_AIRCR_REG & پورت_اولویت_گروه_ماسک ) <= ulMaxPRIGROUPValue );
    }

#پایان_اگر /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/

#إذا ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    فراغ v_پورت_Grant_Access_مقصد_Kernel_Object( TaskHandle_t x_داخلی_Task_Handle,
                                         int32_t l_داخلی_شاخص_از_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_مدخل_شاخص, ul_Access_Control_List_مدخل_بیت;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_مدخل_شاخص = ( ( uint32_t ) l_داخلی_شاخص_از_Kernel_Object / پورت_ACL_مدخل_اندازه_بیتها );
        ul_Access_Control_List_مدخل_بیت = ( ( uint32_t ) l_داخلی_شاخص_از_Kernel_Object % پورت_ACL_مدخل_اندازه_بیتها );

        xTaskMpuSettings = xTaskGetMPUSettings( x_داخلی_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_مدخل_شاخص ] |= ( 1U << ul_Access_Control_List_مدخل_بیت );
    }

#پایان_اگر /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    فراغ v_پورت_Revoke_Access_مقصد_Kernel_Object( TaskHandle_t x_داخلی_Task_Handle,
                                          int32_t l_داخلی_شاخص_از_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_مدخل_شاخص, ul_Access_Control_List_مدخل_بیت;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_مدخل_شاخص = ( ( uint32_t ) l_داخلی_شاخص_از_Kernel_Object / پورت_ACL_مدخل_اندازه_بیتها );
        ul_Access_Control_List_مدخل_بیت = ( ( uint32_t ) l_داخلی_شاخص_از_Kernel_Object % پورت_ACL_مدخل_اندازه_بیتها );

        xTaskMpuSettings = xTaskGetMPUSettings( x_داخلی_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_مدخل_شاخص ] &= ~( 1U << ul_Access_Control_List_مدخل_بیت );
    }

#پایان_اگر /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        پایه_Type_t x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( int32_t l_داخلی_شاخص_از_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_مدخل_شاخص, ul_Access_Control_List_مدخل_بیت;
            پایه_Type_t xAccessGranted = pdFALSE;
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

                ul_Access_Control_List_مدخل_شاخص = ( ( uint32_t ) l_داخلی_شاخص_از_Kernel_Object / پورت_ACL_مدخل_اندازه_بیتها );
                ul_Access_Control_List_مدخل_بیت = ( ( uint32_t ) l_داخلی_شاخص_از_Kernel_Object % پورت_ACL_مدخل_اندازه_بیتها );

                إذا( ( xTaskMpuSettings->ulTaskFlags & پورت_TASK_IS_PRIVILEGED_FLAG ) == پورت_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                وإلا
                {
                    إذا( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_مدخل_شاخص ] & ( 1U << ul_Access_Control_List_مدخل_بیت ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            أرجع xAccessGranted;
        }

    #وإلا /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        پایه_Type_t x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( int32_t l_داخلی_شاخص_از_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( فراغ ) l_داخلی_شاخص_از_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            أرجع pdTRUE;
        }

    #پایان_اگر /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#پایان_اگر /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/
