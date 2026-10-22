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
#تعریف_کرو MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#شامل "FreeRTOS.h"
#شامل "task.h"
#شامل "mpu_syscall_numbers.h"

#اگر_غیر_تعریف_شدہ __ARM_FP
    #غلطی This پورٹ can only be مستعمل when the project options are configured مقصد enable hardware floating نقطہ_2 support.
#اگر_ختم

#تعریف_منسوخ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#اگر_غیر_تعریف_شدہ configSYSTICK_CLOCK_HZ
    #تعریف_کرو configSYSTICK_CLOCK_HZ    configCPU_CLOCK_HZ
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #تعریف_کرو پورٹ_NVIC_SYSTICK_CLK      ( 1UL << 2UL )
#ورنہ

/* The way the SysTick is clocked is not modified in case it is not the same
 * as the core. */
    #تعریف_کرو پورٹ_NVIC_SYSTICK_CLK    ( 0 )
#اگر_ختم

/* Unprivileged critical sections are not supported when using MPU wrappers
 * version 2. Default the option to 0 and reject an explicit value of 1. */
#اگر_غیر_تعریف_شدہ configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS
    #اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )
        #تعریف_کرو configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    0
    #ورنہ
        #warning "configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not defined. We recommend defining it to 0 in FreeRTOSConfig.h for better security."
        #تعریف_کرو configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    1
    #اگر_ختم
#ورنہ
    #اگر ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) )
        #غلطی configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not supported with MPU wrappers نسخہ 2 ( configUSE_MPU_WRAPPERS_V1 == 0 ).
    #اگر_ختم
#اگر_ختم

/* Prototype of all Interrupt Service Routines (ISRs). */
قسمتعریف خالی ( * پورٹ_ISR_t )( خالی );

/* Constants required to access and manipulate the NVIC. */
#تعریف_کرو پورٹ_NVIC_SYSTICK_CTRL_REG                 ( *( ( متلون uint32_t * ) 0xe000e010 ) )
#تعریف_کرو پورٹ_NVIC_SYSTICK_بھرو_REG                 ( *( ( متلون uint32_t * ) 0xe000e014 ) )
#تعریف_کرو پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG        ( *( ( متلون uint32_t * ) 0xe000e018 ) )
#تعریف_کرو پورٹ_NVIC_SHPR3_REG                        ( *( ( متلون uint32_t * ) 0xe000ed20 ) )
#تعریف_کرو پورٹ_NVIC_SHPR2_REG                        ( *( ( متلون uint32_t * ) 0xe000ed1c ) )
#تعریف_کرو پورٹ_NVIC_SYS_CTRL_STATE_REG               ( *( ( متلون uint32_t * ) 0xe000ed24 ) )
#تعریف_کرو پورٹ_NVIC_MEM_FAULT_ENABLE                 ( 1UL << 16UL )

/* Constants used to detect Cortex-M7 r0p0 and r0p1 cores, and ensure
 * that a work around is active for errata 837070. */
#تعریف_کرو پورٹ_CPUID                                 ( *( ( متلون uint32_t * ) 0xE000ed00 ) )
#تعریف_کرو پورٹ_CORTEX_M7_r0p1_ID                     ( 0x410FC271UL )
#تعریف_کرو پورٹ_CORTEX_M7_r0p0_ID                     ( 0x410FC270UL )

/* Constants required to access and manipulate the MPU. */
#تعریف_کرو پورٹ_MPU_TYPE_REG                          ( *( ( متلون uint32_t * ) 0xe000ed90 ) )
#تعریف_کرو پورٹ_MPU_REGION_بنیاد_پتہ_REG           ( *( ( متلون uint32_t * ) 0xe000ed9C ) )
#تعریف_کرو پورٹ_MPU_REGION_ATTRIBUTE_REG              ( *( ( متلون uint32_t * ) 0xe000edA0 ) )
#تعریف_کرو پورٹ_MPU_CTRL_REG                          ( *( ( متلون uint32_t * ) 0xe000ed94 ) )
#تعریف_کرو پورٹ_EXPECTED_MPU_TYPE_قدر               ( config_کل_MPU_REGIONS << 8UL )
#تعریف_کرو پورٹ_MPU_ENABLE                            ( 0x01UL )
#تعریف_کرو پورٹ_MPU_BACKGROUND_ENABLE                 ( 1UL << 2UL )
#تعریف_کرو پورٹ_PRIVILEGED_EXECUTION_آغاز_پتہ    ( 0UL )
#تعریف_کرو پورٹ_MPU_REGION_VALID                      ( 0x10UL )
#تعریف_کرو پورٹ_MPU_REGION_ENABLE                     ( 0x01UL )
#تعریف_کرو پورٹ_PERIPHERALS_آغاز_پتہ             0x40000000UL
#تعریف_کرو پورٹ_PERIPHERALS_انتہا_پتہ               0x5FFFFFFFUL

/* Constants required to access and manipulate the SysTick and other FreeRTOS
 * interrupts. */
#تعریف_کرو پورٹ_NVIC_SYSTICK_INT                      ( 0x00000002UL )
#تعریف_کرو پورٹ_NVIC_SYSTICK_ENABLE                   ( 0x00000001UL )
#تعریف_کرو پورٹ_MIN_مداخلت_ترجیح                ( 255UL )
#تعریف_کرو پورٹ_NVIC_PENDSV_PRI                       ( ( ( uint32_t ) پورٹ_MIN_مداخلت_ترجیح ) << 16UL )
#تعریف_کرو پورٹ_NVIC_SYSTICK_PRI                      ( ( ( uint32_t ) پورٹ_MIN_مداخلت_ترجیح ) << 24UL )
#تعریف_کرو پورٹ_NVIC_SVC_PRI                          ( ( ( uint32_t ) config_MAX_SYSCALL_مداخلت_ترجیح - 1UL ) << 24UL )

/* Constants required to manipulate the VFP. */
#تعریف_کرو پورٹ_FPCCR                                 ( ( متلون uint32_t * ) 0xe000ef34UL ) /* Floating point context control register. */
#تعریف_کرو پورٹ_ASPEN_AND_LSPEN_بٹ                  ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#تعریف_کرو پورٹ_INITIAL_XPSR                          ( 0x01000000UL )
#تعریف_کرو پورٹ_INITIAL_EXC_RETURN                    ( 0xfffffffdUL )
#تعریف_کرو پورٹ_INITIAL_CONTROL_IF_UNPRIVILEGED       ( 0x03 )
#تعریف_کرو پورٹ_INITIAL_CONTROL_IF_PRIVILEGED         ( 0x02 )

/* Constants used to check the installation of the FreeRTOS interrupt handlers. */
#تعریف_کرو پورٹ_SCB_VTOR_REG                          ( *( ( پورٹ_ISR_t ** ) 0xE000ED08 ) )
#تعریف_کرو پورٹ_سمتیہ_اشاریہ_SVC                      ( 11 )
#تعریف_کرو پورٹ_سمتیہ_اشاریہ_PENDSV                   ( 14 )

/* Constants required to check the validity of an interrupt priority. */
#تعریف_کرو پورٹ_پہلا_USER_مداخلت_نمبر           ( 16 )
#تعریف_کرو پورٹ_NVIC_IP_REGISTERS_انحراف_16           ( 0xE000E3F0 )
#تعریف_کرو پورٹ_AIRCR_REG                             ( *( ( متلون uint32_t * ) 0xE000ED0C ) )
#تعریف_کرو پورٹ_MAX_8_ثنائی_ہندسہ_قدر                       ( ( uint8_t ) 0xff )
#تعریف_کرو پورٹ_چوٹی_ثنائی_ہندسہ_کا_BYTE                       ( ( uint8_t ) 0x80 )
#تعریف_کرو پورٹ_MAX_PRIGROUP_بٹ                     ( ( uint8_t ) 7 )
#تعریف_کرو پورٹ_ترجیح_گروہ_نقاب                   ( 0x07UL << 8UL )
#تعریف_کرو پورٹ_PRIGROUP_سرکاؤ                        ( 8UL )

/* Constants used during system call enter and exit. */
#تعریف_کرو پورٹ_PSR_ڈھیر_PADDING_نقاب                ( 1UL << 9UL )
#تعریف_کرو پورٹ_EXC_RETURN_ڈھیر_چوکھٹا_TYPE_نقاب      ( 1UL << 4UL )

/* Offsets in the stack to the parameters when inside the SVC handler. */
#تعریف_کرو پورٹ_انحراف_مقصد_LR                          ( 5 )
#تعریف_کرو پورٹ_انحراف_مقصد_PC                          ( 6 )
#تعریف_کرو پورٹ_انحراف_مقصد_PSR                         ( 7 )


/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#تعریف_کرو پورٹ_آغاز_پتہ_نقاب    ( ( ڈھیر_Type_t ) 0xfffffffeUL )

/* Does addr lie within [start, end] address range? */
#تعریف_کرو پورٹ_IS_پتہ_WITHIN_RANGE( addr, آغاز, انتہا ) \
    ( ( ( addr ) >= ( آغاز ) ) && ( ( addr ) <= ( انتہا ) ) )

/* Is the access request satisfied by the available permissions? */
#تعریف_کرو پورٹ_IS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#تعریف_کرو پورٹ_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کرو پورٹ_جوڑو_UINT32_WILL_حد_سے_تجاوز( a, b )    ( ( a ) > ( پورٹ_UINT32_MAX - ( b ) ) )
/*-----------------------------------------------------------*/

/*
 * Configure a number of standard MPU regions that are used by all tasks.
 */
ساکن خالی prv_تیاری_MPU( خالی ) PRIVILEGED_FUNCTION;

/*
 * Return the smallest MPU region size that a given number of bytes will fit
 * into.  The region size is returned as the value that should be programmed
 * into the region attribute register for that region.
 */
ساکن uint32_t prv_Get_MPURegion_سائز_Setting( uint32_t ul_Actual_سائز_اندر_بائٹیں ) PRIVILEGED_FUNCTION;

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
خالی v_پورٹ_تیاری_Timer_مداخلت( خالی );

/*
 * Standard FreeRTOS exception handlers.
 */
خالی x_پورٹ_Pend_SVHandler( خالی ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;
خالی x_پورٹ_Sys_Tick_Handler( خالی ) PRIVILEGED_FUNCTION;
خالی v_پورٹ_SVCHandler( خالی ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/*
 * Starts the scheduler by restoring the context of the first task to run.
 */
ساکن خالی prv_Restore_Context_کا_پہلا_Task( خالی ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/*
 * C portion of the SVC handler.  The SVC handler is split between an asm entry
 * and a C wrapper for simplicity of coding and maintenance.
 */
خالی vSVCHandler_C( uint32_t * pulRegisters ) __attribute__( ( noinline ) ) PRIVILEGED_FUNCTION;

/*
 * Function to enable the VFP.
 */
ساکن خالی v_پورٹ_Enable_VFP( خالی ) __attribute__( ( naked ) );

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
بنیاد_Type_t xIsPrivileged( خالی ) __attribute__( ( naked ) );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 *
 * Bit 0 of the CONTROL register defines the privilege level of Thread Mode.
 *  Bit[0] = 0 --> The processor is running privileged
 *  Bit[0] = 1 --> The processor is running unprivileged.
 */
خالی vResetPrivilege( خالی ) __attribute__( ( naked ) );

/**
 * @brief Make a task unprivileged.
 */
خالی v_پورٹ_Switch_مقصد_User_منوال( خالی );

/**
 * @brief Enter critical section.
 */
#اگر ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    خالی v_پورٹ_Enter_Critical( خالی ) FREERTOS_SYSTEM_CALL;
#ورنہ
    خالی v_پورٹ_Enter_Critical( خالی ) PRIVILEGED_FUNCTION;
#اگر_ختم

/**
 * @brief Exit from critical section.
 */
#اگر ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    خالی v_پورٹ_Exit_Critical( خالی ) FREERTOS_SYSTEM_CALL;
#ورنہ
    خالی v_پورٹ_Exit_Critical( خالی ) PRIVILEGED_FUNCTION;
#اگر_ختم

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the system call stack so that upon returning from
 * SVC, the system call stack is used.
 *
 * @param pulTaskStack The current SP when the SVC was raised.
 * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
 * @param ucSystemCallNumber The system call number of the system call.
 */
    خالی vSystemCallEnter( uint32_t * pul_Task_ڈھیر,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_نمبر ) PRIVILEGED_FUNCTION;

#اگر_ختم /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Raise SVC for exiting from a system call.
 */
    خالی vRequestSystemCallExit( خالی ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#اگر_ختم /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the task stack so that upon returning from
 * SVC, the task stack is used again.
 *
 * @param pulSystemCallStack The current SP when the SVC was raised.
 * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
 */
    خالی vSystemCallExit( uint32_t * pul_System_Call_ڈھیر,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#اگر_ختم /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
بنیاد_Type_t x_پورٹ_Is_Task_Privileged( خالی ) PRIVILEGED_FUNCTION;
/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable.  Note this is not saved as part of the task context as context
 * switches can only occur when uxCriticalNesting is zero. */
ساکن UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

/*
 * This variable is set to pdTRUE when the scheduler is started.
 */
    PRIVILEGED_ڈیٹا ساکن بنیاد_Type_t xSchedulerRunning = pdFALSE;

#اگر_ختم /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#اگر ( configASSERT_DEFINED == 1 )
    ساکن uint8_t uc_Max_Sys_Call_ترجیح = 0;
    ساکن uint32_t ulMaxPRIGROUPValue = 0;
    ساکن ثابت متلون uint8_t * ثابت pc_مداخلت_ترجیح_Registers = ( ثابت متلون uint8_t * ثابت ) پورٹ_NVIC_IP_REGISTERS_انحراف_16;
#اگر_ختم /* configASSERT_DEFINED */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters,
                                     بنیاد_Type_t x_تسلسل_Privileged,
                                     xMPU_SETTINGS * xMPUSettings )
{
    اگر( x_تسلسل_Privileged == pdTRUE )
    {
        xMPUSettings->ulTaskFlags |= پورٹ_TASK_IS_PRIVILEGED_FLAG;
        xMPUSettings->ulContext[ 0 ] = پورٹ_INITIAL_CONTROL_IF_PRIVILEGED;
    }
    ورنہ
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

    xMPUSettings->ulContext[ 10 ] = ( uint32_t ) ( px_چوٹی_کا_ڈھیر - 8 );                /* PSP with the hardware saved stack. */
    xMPUSettings->ulContext[ 11 ] = ( uint32_t ) pvParameters;                        /* r0. */
    xMPUSettings->ulContext[ 12 ] = 0x01010101;                                       /* r1. */
    xMPUSettings->ulContext[ 13 ] = 0x02020202;                                       /* r2. */
    xMPUSettings->ulContext[ 14 ] = 0x03030303;                                       /* r3. */
    xMPUSettings->ulContext[ 15 ] = 0x12121212;                                       /* r12. */
    xMPUSettings->ulContext[ 16 ] = 0;                                                /* LR. */
    xMPUSettings->ulContext[ 17 ] = ( ( uint32_t ) px_رمز ) & پورٹ_آغاز_پتہ_نقاب; /* PC. */
    xMPUSettings->ulContext[ 18 ] = پورٹ_INITIAL_XPSR;                                 /* xPSR. */

    #اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        /* Ensure that the system call stack is double word aligned. */
        xMPUSettings->x_System_Call_ڈھیر_Info.pul_System_Call_ڈھیر = &( xMPUSettings->x_System_Call_ڈھیر_Info.ul_System_Call_ڈھیر_بفر[ config_SYSTEM_CALL_ڈھیر_سائز - 1 ] );
        xMPUSettings->x_System_Call_ڈھیر_Info.pul_System_Call_ڈھیر = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_ڈھیر_Info.pul_System_Call_ڈھیر ) &
                                                                                 ( uint32_t ) ( ~( پورٹ_BYTE_ALIGNMENT_نقاب ) ) );

        /* This is not NULL only for the duration of a system call. */
        xMPUSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر = تہی;
    }
    #اگر_ختم /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    واپس &( xMPUSettings->ulContext[ 19 ] );
}
/*-----------------------------------------------------------*/

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

    خالی v_پورٹ_SVCHandler( خالی ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm متلون
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
            : "i" ( عدد_SYSTEM_CALLS ), "i" ( پورٹ_SVC_SYSTEM_CALL_EXIT )
            : "r0", "r1", "r2", "memory"
        );
    }

#ورنہ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    خالی v_پورٹ_SVCHandler( خالی )
    {
        /* Assumes psp was in use. */
        __asm متلون
        (
            #اگر_غیر_تعریف_شدہ USE_PROCESS_ڈھیر /* Code should not be required if a main() is using the process stack. */
                "   tst lr, #4                      \n"
                "   ite eq                          \n"
                "   mrseq r0, msp                   \n"
                "   mrsne r0, psp                   \n"
            #ورنہ
                "   mrs r0, psp                     \n"
            #اگر_ختم
            "   b %0                            \n"
            ::"i" ( vSVCHandler_C ) : "r0", "memory"
        );
    }

#اگر_ختم /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

خالی vSVCHandler_C( uint32_t * pulParam ) /* PRIVILEGED_FUNCTION */
{
    uint8_t ucSVCNumber;
    uint32_t ulPC;

    #اگر ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) )
        #اگر defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجی uint32_t * __syscalls_flash_start__;
            خارجی uint32_t * __syscalls_flash_end__;
        #ورنہ
            /* Declaration when these variable are exported from linker scripts. */
            خارجی uint32_t __syscalls_flash_start__[];
            خارجی uint32_t __syscalls_flash_end__[];
        #اگر_ختم /* #if defined( __ARMCC_VERSION ) */
    #اگر_ختم /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) ) */

    /* The stack contains: r0, r1, r2, r3, r12, LR, PC and xPSR.  The first
     * argument (r0) is pulParam[ 0 ]. */
    ulPC = pulParam[ پورٹ_انحراف_مقصد_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    انتخاب( ucSVCNumber )
    {
        حالت پورٹ_SVC_آغاز_SCHEDULER:
            prv_Restore_Context_کا_پہلا_Task();
            توڑو;

        حالت پورٹ_SVC_YIELD:
            پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ;

            /* Barriers are normally not required
             * but do ensure the code is completely
             * within the specified behaviour for the
             * architecture. */
            __asm متلون ( "dsb" ::: "memory" );
            __asm متلون ( "isb" );

            توڑو;

    #اگر ( configUSE_MPU_WRAPPERS_V1 == 1 )
        #اگر ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 )
            حالت پورٹ_SVC_RAISE_PRIVILEGE: /* Only raise the privilege, if the
                                           * svc was raised from any of the
                                           * system calls. */

                اگر( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                    ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
                {
                    __asm متلون
                    (
                        "   mrs r1, control     \n" /* Obtain current control value. */
                        "   bic r1, #1          \n" /* Set privilege bit. */
                        "   msr control, r1     \n" /* Write back new control value. */
                        ::: "r1", "memory"
                    );
                }

                توڑو;
        #ورنہ /* if ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
            حالت پورٹ_SVC_RAISE_PRIVILEGE:
                __asm متلون
                (
                    "   mrs r1, control     \n" /* Obtain current control value. */
                    "   bic r1, #1          \n" /* Set privilege bit. */
                    "   msr control, r1     \n" /* Write back new control value. */
                    ::: "r1", "memory"
                );
                توڑو;
        #اگر_ختم /* #if( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
    #اگر_ختم /* #if ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

        طےشدہ: /* Unknown SVC call. */
            توڑو;
    }
}
/*-----------------------------------------------------------*/

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

    خالی vSystemCallEnter( uint32_t * pul_Task_ڈھیر,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_نمبر ) /* PRIVILEGED_FUNCTION */
    {
        خارجی TaskHandle_t pxCurrentTCB;
        خارجی UBaseType_t uxSystemCallImplementations[ عدد_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_ڈھیر;
        uint32_t ul_Hardware_Saved_Exception_چوکھٹا_سائز, ulSystemCallLocation, i;

        #اگر defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجی uint32_t * __syscalls_flash_start__;
            خارجی uint32_t * __syscalls_flash_end__;
        #ورنہ
            /* Declaration when these variable are exported from linker scripts. */
            خارجی uint32_t __syscalls_flash_start__[];
            خارجی uint32_t __syscalls_flash_end__[];
        #اگر_ختم /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_ڈھیر[ پورٹ_انحراف_مقصد_PC ];
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
            ( pxMpuSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر == تہی ) &&
            ( uxSystemCallImplementations[ uc_System_Call_نمبر ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_ڈھیر = pxMpuSettings->x_System_Call_ڈھیر_Info.pul_System_Call_ڈھیر;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            اگر( ( ulLR & پورٹ_EXC_RETURN_ڈھیر_چوکھٹا_TYPE_نقاب ) == 0UL )
            {
                /* Extended frame i.e. FPU in use. */
                ul_Hardware_Saved_Exception_چوکھٹا_سائز = 26;
                __asm متلون (
                    " vpush {s0}         \n" /* Trigger lazy stacking. */
                    " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                    ::: "memory"
                    );
            }
            ورنہ
            {
                /* Standard frame i.e. FPU not in use. */
                ul_Hardware_Saved_Exception_چوکھٹا_سائز = 8;
            }

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_ڈھیر = pul_System_Call_ڈھیر - ul_Hardware_Saved_Exception_چوکھٹا_سائز;

            /* Copy the stack frame. */
            برائے( i = 0; i < ul_Hardware_Saved_Exception_چوکھٹا_سائز; i++ )
            {
                pul_System_Call_ڈھیر[ i ] = pul_Task_ڈھیر[ i ];
            }

            /* Use the pulSystemCallStack in thread mode. */
            __asm متلون ( "msr psp, %0" : : "r" ( pul_System_Call_ڈھیر ) );

            /* Raise the privilege for the duration of the system call. */
            __asm متلون (
                " mrs r1, control     \n" /* Obtain current control value. */
                " bic r1, #1          \n" /* Clear nPRIV bit. */
                " msr control, r1     \n" /* Write back new control value. */
                ::: "r1", "memory"
                );

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر = pul_Task_ڈھیر + ul_Hardware_Saved_Exception_چوکھٹا_سائز;

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_ڈھیر_Info.ul_Link_رجسٹر_At_System_Call_اندراج = pul_Task_ڈھیر[ پورٹ_انحراف_مقصد_LR ];

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_ڈھیر[ پورٹ_انحراف_مقصد_PC ] = uxSystemCallImplementations[ uc_System_Call_نمبر ];
            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_ڈھیر[ پورٹ_انحراف_مقصد_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            اگر( ( pul_Task_ڈھیر[ پورٹ_انحراف_مقصد_PSR ] & پورٹ_PSR_ڈھیر_PADDING_نقاب ) == پورٹ_PSR_ڈھیر_PADDING_نقاب )
            {
                pxMpuSettings->ulTaskFlags |= پورٹ_ڈھیر_چوکھٹا_HAS_PADDING_FLAG;
            }
            ورنہ
            {
                pxMpuSettings->ulTaskFlags &= ( ~پورٹ_ڈھیر_چوکھٹا_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_ڈھیر[ پورٹ_انحراف_مقصد_PSR ] &= ( ~پورٹ_PSR_ڈھیر_PADDING_نقاب );
        }
    }

#اگر_ختم /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

    خالی vRequestSystemCallExit( خالی ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm متلون ( "svc %0 \n" ::"i" ( پورٹ_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#اگر_ختم /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

    خالی vSystemCallExit( uint32_t * pul_System_Call_ڈھیر,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        خارجی TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_ڈھیر;
        uint32_t ul_Hardware_Saved_Exception_چوکھٹا_سائز, ulSystemCallLocation, i;

        #اگر defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجی uint32_t * __privileged_functions_start__;
            خارجی uint32_t * __privileged_functions_end__;
        #ورنہ
            /* Declaration when these variable are exported from linker scripts. */
            خارجی uint32_t __privileged_functions_start__[];
            خارجی uint32_t __privileged_functions_end__[];
        #اگر_ختم /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_ڈھیر[ پورٹ_انحراف_مقصد_PC ];
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
            ( pxMpuSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر != تہی ) )
        {
            pul_Task_ڈھیر = pxMpuSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            اگر( ( ulLR & پورٹ_EXC_RETURN_ڈھیر_چوکھٹا_TYPE_نقاب ) == 0UL )
            {
                /* Extended frame i.e. FPU in use. */
                ul_Hardware_Saved_Exception_چوکھٹا_سائز = 26;
                __asm متلون (
                    " vpush {s0}         \n" /* Trigger lazy stacking. */
                    " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                    ::: "memory"
                    );
            }
            ورنہ
            {
                /* Standard frame i.e. FPU not in use. */
                ul_Hardware_Saved_Exception_چوکھٹا_سائز = 8;
            }

            /* Make space on the task stack for the stack frame. */
            pul_Task_ڈھیر = pul_Task_ڈھیر - ul_Hardware_Saved_Exception_چوکھٹا_سائز;

            /* Copy the stack frame. */
            برائے( i = 0; i < ul_Hardware_Saved_Exception_چوکھٹا_سائز; i++ )
            {
                pul_Task_ڈھیر[ i ] = pul_System_Call_ڈھیر[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm متلون ( "msr psp, %0" : : "r" ( pul_Task_ڈھیر ) );

            /* Drop the privilege before returning to the thread mode. */
            __asm متلون (
                " mrs r1, control     \n" /* Obtain current control value. */
                " orr r1, #1          \n" /* Set nPRIV bit. */
                " msr control, r1     \n" /* Write back new control value. */
                ::: "r1", "memory"
                );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_ڈھیر[ پورٹ_انحراف_مقصد_PC ] = pxMpuSettings->x_System_Call_ڈھیر_Info.ul_Link_رجسٹر_At_System_Call_اندراج;
            /* Ensure that LR has a valid value.*/
            pul_Task_ڈھیر[ پورٹ_انحراف_مقصد_LR ] = pxMpuSettings->x_System_Call_ڈھیر_Info.ul_Link_رجسٹر_At_System_Call_اندراج;

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            اگر( ( pxMpuSettings->ulTaskFlags & پورٹ_ڈھیر_چوکھٹا_HAS_PADDING_FLAG ) == پورٹ_ڈھیر_چوکھٹا_HAS_PADDING_FLAG )
            {
                pul_Task_ڈھیر[ پورٹ_انحراف_مقصد_PSR ] |= پورٹ_PSR_ڈھیر_PADDING_نقاب;
            }
            ورنہ
            {
                pul_Task_ڈھیر[ پورٹ_انحراف_مقصد_PSR ] &= ( ~پورٹ_PSR_ڈھیر_PADDING_نقاب );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر = تہی;
        }
    }

#اگر_ختم /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_Is_Task_Privileged( خالی ) /* PRIVILEGED_FUNCTION */
{
    بنیاد_Type_t xTaskIsPrivileged = pdFALSE;
    ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( تہی ); /* Calling task's MPU settings. */

    اگر( ( xTaskMpuSettings->ulTaskFlags & پورٹ_TASK_IS_PRIVILEGED_FLAG ) == پورٹ_TASK_IS_PRIVILEGED_FLAG )
    {
        xTaskIsPrivileged = pdTRUE;
    }

    واپس xTaskIsPrivileged;
}
/*-----------------------------------------------------------*/

ساکن خالی prv_Restore_Context_کا_پہلا_Task( خالی )
{
    __asm متلون
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
        #اگر ( config_کل_MPU_REGIONS == 16 )
            " ldmia r2!, {r4-r11}                   \n" /* Read 4 sets of MPU registers [MPU Region # 4 - 8]. */
            " stmia r0, {r4-r11}                    \n" /* Write 4 sets of MPU registers. [MPU Region # 4 - 8]. */
            " ldmia r2!, {r4-r11}                   \n" /* Read 4 sets of MPU registers [MPU Region # 9 - 12]. */
            " stmia r0, {r4-r11}                    \n" /* Write 4 sets of MPU registers. [MPU Region # 9 - 12]. */
        #اگر_ختم /* configTOTAL_MPU_REGIONS == 16. */
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
بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    /* Errata 837070 workaround must only be enabled on Cortex-M7 r0p0
     * and r0p1 cores. */
    #اگر ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        configASSERT( ( پورٹ_CPUID == پورٹ_CORTEX_M7_r0p1_ID ) || ( پورٹ_CPUID == پورٹ_CORTEX_M7_r0p0_ID ) );
    #ورنہ

        /* When using this port on a Cortex-M7 r0p0 or r0p1 core, define
         * configENABLE_ERRATA_837070_WORKAROUND to 1 in your
         * FreeRTOSConfig.h. */
        configASSERT( پورٹ_CPUID != پورٹ_CORTEX_M7_r0p1_ID );
        configASSERT( پورٹ_CPUID != پورٹ_CORTEX_M7_r0p0_ID );
    #اگر_ختم

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
    #اگر_ختم /* configCHECK_HANDLER_INSTALLATION */

    #اگر ( configASSERT_DEFINED == 1 )
    {
        متلون uint8_t uc_Original_ترجیح;
        متلون uint32_t ul_Implemented_Prio_بٹ = 0;
        متلون uint8_t * ثابت puc_پہلا_User_ترجیح_رجسٹر = ( متلون uint8_t * ثابت ) ( پورٹ_NVIC_IP_REGISTERS_انحراف_16 + پورٹ_پہلا_USER_مداخلت_نمبر );
        متلون uint8_t uc_Max_ترجیح_قدر;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
         * functions can be called.  ISR safe functions are those that end in
         * "FromISR".  FreeRTOS maintains separate thread and ISR API functions to
         * ensure interrupt entry is as fast and simple as possible.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_ترجیح = *puc_پہلا_User_ترجیح_رجسٹر;

        /* Determine the number of priority bits available.  First write to all
         * possible bits. */
        *puc_پہلا_User_ترجیح_رجسٹر = پورٹ_MAX_8_ثنائی_ہندسہ_قدر;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ترجیح_قدر = *puc_پہلا_User_ترجیح_رجسٹر;

        /* Use the same mask on the maximum system call priority. */
        uc_Max_Sys_Call_ترجیح = config_MAX_SYSCALL_مداخلت_ترجیح & uc_Max_ترجیح_قدر;

        /* Check that the maximum system call priority is nonzero after
         * accounting for the number of priority bits supported by the
         * hardware. A priority of 0 is invalid because setting the BASEPRI
         * register to 0 unmasks all interrupts, and interrupts with priority 0
         * cannot be masked using BASEPRI.
         * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( uc_Max_Sys_Call_ترجیح );

        /* Check that the bits not implemented in hardware are zero in
         * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( config_MAX_SYSCALL_مداخلت_ترجیح & ( ~uc_Max_ترجیح_قدر ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
         * of bits read back. */

        جب( ( uc_Max_ترجیح_قدر & پورٹ_چوٹی_ثنائی_ہندسہ_کا_BYTE ) == پورٹ_چوٹی_ثنائی_ہندسہ_کا_BYTE )
        {
            ul_Implemented_Prio_بٹ++;
            uc_Max_ترجیح_قدر <<= ( uint8_t ) 0x01;
        }

        اگر( ul_Implemented_Prio_بٹ == 8 )
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
            configASSERT( ( config_MAX_SYSCALL_مداخلت_ترجیح & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        ورنہ
        {
            ulMaxPRIGROUPValue = پورٹ_MAX_PRIGROUP_بٹ - ul_Implemented_Prio_بٹ;
        }

        /* Shift the priority group value back to its position within the AIRCR
         * register. */
        ulMaxPRIGROUPValue <<= پورٹ_PRIGROUP_سرکاؤ;
        ulMaxPRIGROUPValue &= پورٹ_ترجیح_گروہ_نقاب;

        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_پہلا_User_ترجیح_رجسٹر = uc_Original_ترجیح;
    }
    #اگر_ختم /* configASSERT_DEFINED */

    /* Make PendSV and SysTick the lowest priority interrupts, and configure
     * SVCall for sufficient preemption priority. */
    پورٹ_NVIC_SHPR3_REG |= پورٹ_NVIC_PENDSV_PRI;
    پورٹ_NVIC_SHPR3_REG |= پورٹ_NVIC_SYSTICK_PRI;
    پورٹ_NVIC_SHPR2_REG = پورٹ_NVIC_SVC_PRI;

    /* Configure the regions in the MPU that are common to all tasks. */
    prv_تیاری_MPU();

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_پورٹ_تیاری_Timer_مداخلت();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    #اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        xSchedulerRunning = pdTRUE;
    }
    #اگر_ختم /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    /* Ensure the VFP is enabled - it should be anyway. */
    v_پورٹ_Enable_VFP();

    /* Lazy save always. */
    *( پورٹ_FPCCR ) |= پورٹ_ASPEN_AND_LSPEN_بٹ;

    /* Start the first task.  This also clears the bit that indicates the FPU is
     * in use in case the FPU was used before the scheduler was started - which
     * would otherwise result in the unnecessary leaving of space in the SVC stack
     * for lazy saving of FPU registers. */
    __asm متلون (
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
        ::"i" ( پورٹ_SVC_آغاز_SCHEDULER ) : "memory" );

    /* Should not get here! */
    واپس 0;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Enter_Critical( خالی )
{
    #اگر ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            پورٹ_DISABLE_INTERRUPTS();
            uxCriticalNesting++;
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        ورنہ
        {
            پورٹ_DISABLE_INTERRUPTS();
            uxCriticalNesting++;
        }
    #ورنہ /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        پورٹ_DISABLE_INTERRUPTS();
        uxCriticalNesting++;
    #اگر_ختم /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Exit_Critical( خالی )
{
    #اگر ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            اگر( uxCriticalNesting == 0 )
            {
                پورٹ_ENABLE_INTERRUPTS();
            }

            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        ورنہ
        {
            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            اگر( uxCriticalNesting == 0 )
            {
                پورٹ_ENABLE_INTERRUPTS();
            }
        }
    #ورنہ /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        configASSERT( uxCriticalNesting );
        uxCriticalNesting--;

        اگر( uxCriticalNesting == 0 )
        {
            پورٹ_ENABLE_INTERRUPTS();
        }
    #اگر_ختم /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

خالی x_پورٹ_Pend_SVHandler( خالی )
{
    /* This is a naked function. */

    __asm متلون
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
        #اگر ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
            " cpsid i                               \n" /* ARM Cortex-M7 r0p1 Errata 837070 workaround. */
        #اگر_ختم
        " msr basepri, r0                       \n"
        " dsb                                   \n"
        " isb                                   \n"
        #اگر ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
            " cpsie i                               \n" /* ARM Cortex-M7 r0p1 Errata 837070 workaround. */
        #اگر_ختم
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
        #اگر ( config_کل_MPU_REGIONS == 16 )
            " ldmia r2!, {r4-r11}                   \n" /* Read 4 sets of MPU registers [MPU Region # 4 - 7]. */
            " stmia r0, {r4-r11}                    \n" /* Write 4 sets of MPU registers. [MPU Region # 4 - 7]. */
            " ldmia r2!, {r4-r11}                   \n" /* Read 4 sets of MPU registers [MPU Region # 8 - 11]. */
            " stmia r0, {r4-r11}                    \n" /* Write 4 sets of MPU registers. [MPU Region # 8 - 11]. */
        #اگر_ختم /* configTOTAL_MPU_REGIONS == 16. */
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
        ::"i" ( config_MAX_SYSCALL_مداخلت_ترجیح )
    );
}
/*-----------------------------------------------------------*/

خالی x_پورٹ_Sys_Tick_Handler( خالی )
{
    uint32_t ulDummy;

    ulDummy = پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        اگر( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_مقصد_SCHEDULER();
            /* Pend a context switch. */
            پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ;
        }
        ورنہ
        {
            traceISR_EXIT();
        }
    }
    پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( ulDummy );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__attribute__( ( weak ) ) خالی v_پورٹ_تیاری_Timer_مداخلت( خالی )
{
    /* Stop and clear the SysTick. */
    پورٹ_NVIC_SYSTICK_CTRL_REG = 0UL;
    پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    پورٹ_NVIC_SYSTICK_بھرو_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_شرح_HZ ) - 1UL;
    پورٹ_NVIC_SYSTICK_CTRL_REG = ( پورٹ_NVIC_SYSTICK_CLK | پورٹ_NVIC_SYSTICK_INT | پورٹ_NVIC_SYSTICK_ENABLE );
}
/*-----------------------------------------------------------*/

/* This is a naked function. */
ساکن خالی v_پورٹ_Enable_VFP( خالی )
{
    __asm متلون
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

ساکن خالی prv_تیاری_MPU( خالی )
{
    #اگر defined( __ARMCC_VERSION )

        /* Declaration when these variable are defined in code instead of being
         * exported from linker scripts. */
        خارجی uint32_t * __privileged_functions_start__;
        خارجی uint32_t * __privileged_functions_end__;
        خارجی uint32_t * __FLASH_segment_start__;
        خارجی uint32_t * __FLASH_segment_end__;
        خارجی uint32_t * __privileged_data_start__;
        خارجی uint32_t * __privileged_data_end__;
    #ورنہ
        /* Declaration when these variable are exported from linker scripts. */
        خارجی uint32_t __privileged_functions_start__[];
        خارجی uint32_t __privileged_functions_end__[];
        خارجی uint32_t __FLASH_segment_start__[];
        خارجی uint32_t __FLASH_segment_end__[];
        خارجی uint32_t __privileged_data_start__[];
        خارجی uint32_t __privileged_data_end__[];
    #اگر_ختم /* if defined( __ARMCC_VERSION ) */

    /* The only permitted number of regions are 8 or 16. */
    configASSERT( ( config_کل_MPU_REGIONS == 8 ) || ( config_کل_MPU_REGIONS == 16 ) );

    /* Ensure that the configTOTAL_MPU_REGIONS is configured correctly. */
    configASSERT( پورٹ_MPU_TYPE_REG == پورٹ_EXPECTED_MPU_TYPE_قدر );

    /* Check the expected MPU is present. */
    اگر( پورٹ_MPU_TYPE_REG == پورٹ_EXPECTED_MPU_TYPE_قدر )
    {
        /* First setup the unprivileged flash for unprivileged read only access. */
        پورٹ_MPU_REGION_بنیاد_پتہ_REG = ( ( uint32_t ) __FLASH_segment_start__ ) | /* Base address. */
                                          ( پورٹ_MPU_REGION_VALID ) |
                                          ( پورٹ_UNPRIVILEGED_FLASH_REGION );

        پورٹ_MPU_REGION_ATTRIBUTE_REG = ( پورٹ_MPU_REGION_READ_ONLY ) |
                                       ( ( configTEX_S_C_B_FLASH & پورٹ_MPU_RASR_TEX_S_C_B_نقاب ) << پورٹ_MPU_RASR_TEX_S_C_B_LOCATION ) |
                                       ( prv_Get_MPURegion_سائز_Setting( ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__ ) ) |
                                       ( پورٹ_MPU_REGION_ENABLE );

        /* Setup the privileged flash for privileged only access.  This is where
         * the kernel code is placed. */
        پورٹ_MPU_REGION_بنیاد_پتہ_REG = ( ( uint32_t ) __privileged_functions_start__ ) | /* Base address. */
                                          ( پورٹ_MPU_REGION_VALID ) |
                                          ( پورٹ_PRIVILEGED_FLASH_REGION );

        پورٹ_MPU_REGION_ATTRIBUTE_REG = ( پورٹ_MPU_REGION_PRIVILEGED_READ_ONLY ) |
                                       ( ( configTEX_S_C_B_FLASH & پورٹ_MPU_RASR_TEX_S_C_B_نقاب ) << پورٹ_MPU_RASR_TEX_S_C_B_LOCATION ) |
                                       ( prv_Get_MPURegion_سائز_Setting( ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__ ) ) |
                                       ( پورٹ_MPU_REGION_ENABLE );

        /* Setup the privileged data RAM region.  This is where the kernel data
         * is placed. */
        پورٹ_MPU_REGION_بنیاد_پتہ_REG = ( ( uint32_t ) __privileged_data_start__ ) | /* Base address. */
                                          ( پورٹ_MPU_REGION_VALID ) |
                                          ( پورٹ_PRIVILEGED_RAM_REGION );

        پورٹ_MPU_REGION_ATTRIBUTE_REG = ( پورٹ_MPU_REGION_PRIVILEGED_READ_WRITE ) |
                                       ( پورٹ_MPU_REGION_EXECUTE_NEVER ) |
                                       ( ( configTEX_S_C_B_SRAM & پورٹ_MPU_RASR_TEX_S_C_B_نقاب ) << پورٹ_MPU_RASR_TEX_S_C_B_LOCATION ) |
                                       prv_Get_MPURegion_سائز_Setting( ( uint32_t ) __privileged_data_end__ - ( uint32_t ) __privileged_data_start__ ) |
                                       ( پورٹ_MPU_REGION_ENABLE );

        /* By default allow everything to access the general peripherals.  The
         * system peripherals and registers are protected. */
        پورٹ_MPU_REGION_بنیاد_پتہ_REG = ( پورٹ_PERIPHERALS_آغاز_پتہ ) |
                                          ( پورٹ_MPU_REGION_VALID ) |
                                          ( پورٹ_GENERAL_PERIPHERALS_REGION );

        پورٹ_MPU_REGION_ATTRIBUTE_REG = ( پورٹ_MPU_REGION_READ_WRITE | پورٹ_MPU_REGION_EXECUTE_NEVER ) |
                                       ( prv_Get_MPURegion_سائز_Setting( پورٹ_PERIPHERALS_انتہا_پتہ - پورٹ_PERIPHERALS_آغاز_پتہ ) ) |
                                       ( پورٹ_MPU_REGION_ENABLE );

        /* Enable the memory fault exception. */
        پورٹ_NVIC_SYS_CTRL_STATE_REG |= پورٹ_NVIC_MEM_FAULT_ENABLE;

        /* Enable the MPU with the background region configured. */
        پورٹ_MPU_CTRL_REG |= ( پورٹ_MPU_ENABLE | پورٹ_MPU_BACKGROUND_ENABLE );
    }
}
/*-----------------------------------------------------------*/

ساکن uint32_t prv_Get_MPURegion_سائز_Setting( uint32_t ul_Actual_سائز_اندر_بائٹیں )
{
    uint32_t ul_Region_سائز, ul_Return_قدر = 4;

    /* 32 is the smallest region size, 31 is the largest valid value for
     * ulReturnValue. */
    برائے( ul_Region_سائز = 32UL; ul_Return_قدر < 31UL; ( ul_Region_سائز <<= 1UL ) )
    {
        اگر( ul_Actual_سائز_اندر_بائٹیں <= ul_Region_سائز )
        {
            توڑو;
        }
        ورنہ
        {
            ul_Return_قدر++;
        }
    }

    /* Shift the code by one before returning so it can be written directly
     * into the correct bit position of the attribute register. */
    واپس( ul_Return_قدر << 1UL );
}
/*-----------------------------------------------------------*/

بنیاد_Type_t xIsPrivileged( خالی ) /* __attribute__ (( naked )) */
{
    __asm متلون
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

خالی vResetPrivilege( خالی ) /* __attribute__ (( naked )) */
{
    __asm متلون
    (
        "   mrs r0, control                         \n" /* r0 = CONTROL. */
        "   orr r0, #1                              \n" /* r0 = r0 | 1. */
        "   msr control, r0                         \n" /* CONTROL = r0. */
        "   bx lr                                   \n" /* Return to the caller. */
        ::: "r0", "memory"
    );
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Switch_مقصد_User_منوال( خالی )
{
    /* Load the current task's MPU settings from its TCB. */
    xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( تہی );

    /* Mark the task as unprivileged. */
    xTaskMpuSettings->ulTaskFlags &= ( ~( پورٹ_TASK_IS_PRIVILEGED_FLAG ) );

    /* Lower the processor's privilege level. */
    vResetPrivilege();
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                ثابت ساخت x_حافظہ_REGION * ثابت xRegions,
                                ڈھیر_Type_t * px_Bottom_کا_ڈھیر,
                                config_ڈھیر_گہرائی_TYPE ux_ڈھیر_گہرائی )
{
    #اگر defined( __ARMCC_VERSION )

        /* Declaration when these variable are defined in code instead of being
         * exported from linker scripts. */
        خارجی uint32_t * __SRAM_segment_start__;
        خارجی uint32_t * __SRAM_segment_end__;
        خارجی uint32_t * __privileged_data_start__;
        خارجی uint32_t * __privileged_data_end__;
    #ورنہ
        /* Declaration when these variable are exported from linker scripts. */
        خارجی uint32_t __SRAM_segment_start__[];
        خارجی uint32_t __SRAM_segment_end__[];
        خارجی uint32_t __privileged_data_start__[];
        خارجی uint32_t __privileged_data_end__[];
    #اگر_ختم /* if defined( __ARMCC_VERSION ) */

    int32_t l_اشاریہ;
    uint32_t ul;

    اگر( xRegions == تہی )
    {
        /* No MPU regions are specified so allow access to all RAM. */
        xMPUSettings->xRegion[ 0 ].ul_Region_بنیاد_پتہ =
            ( ( uint32_t ) __SRAM_segment_start__ ) | /* Base address. */
            ( پورٹ_MPU_REGION_VALID ) |
            ( پورٹ_ڈھیر_REGION );                     /* Region number. */

        xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
            ( پورٹ_MPU_REGION_READ_WRITE ) |
            ( پورٹ_MPU_REGION_EXECUTE_NEVER ) |
            ( ( configTEX_S_C_B_SRAM & پورٹ_MPU_RASR_TEX_S_C_B_نقاب ) << پورٹ_MPU_RASR_TEX_S_C_B_LOCATION ) |
            ( prv_Get_MPURegion_سائز_Setting( ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__ ) ) |
            ( پورٹ_MPU_REGION_ENABLE );

        xMPUSettings->xRegionSettings[ 0 ].ul_Region_آغاز_پتہ = ( uint32_t ) __SRAM_segment_start__;
        xMPUSettings->xRegionSettings[ 0 ].ul_Region_انتہا_پتہ = ( uint32_t ) __SRAM_segment_end__;
        xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                   tskMPU_WRITE_PERMISSION );

        /* Invalidate user configurable regions. */
        برائے( ul = 1UL; ul <= پورٹ_عدد_CONFIGURABLE_REGIONS; ul++ )
        {
            xMPUSettings->xRegion[ ul ].ul_Region_بنیاد_پتہ = ( ( ul - 1UL ) | پورٹ_MPU_REGION_VALID );
            xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ul_Region_آغاز_پتہ = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ul_Region_انتہا_پتہ = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
        }
    }
    ورنہ
    {
        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid.  At all other
         * times the stack parameters will not be valid and it is assumed that the
         * stack region has already been configured. */
        اگر( ux_ڈھیر_گہرائی > 0 )
        {
            /* Define the region that allows access to the stack. */
            xMPUSettings->xRegion[ 0 ].ul_Region_بنیاد_پتہ =
                ( ( uint32_t ) px_Bottom_کا_ڈھیر ) |
                ( پورٹ_MPU_REGION_VALID ) |
                ( پورٹ_ڈھیر_REGION ); /* Region number. */

            xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
                ( پورٹ_MPU_REGION_READ_WRITE ) |
                ( پورٹ_MPU_REGION_EXECUTE_NEVER ) |
                ( prv_Get_MPURegion_سائز_Setting( ux_ڈھیر_گہرائی * ( config_ڈھیر_گہرائی_TYPE ) حجم( ڈھیر_Type_t ) ) ) |
                ( ( configTEX_S_C_B_SRAM & پورٹ_MPU_RASR_TEX_S_C_B_نقاب ) << پورٹ_MPU_RASR_TEX_S_C_B_LOCATION ) |
                ( پورٹ_MPU_REGION_ENABLE );

            xMPUSettings->xRegionSettings[ 0 ].ul_Region_آغاز_پتہ = ( uint32_t ) px_Bottom_کا_ڈھیر;
            xMPUSettings->xRegionSettings[ 0 ].ul_Region_انتہا_پتہ = ( uint32_t ) ( ( uint32_t ) ( px_Bottom_کا_ڈھیر ) +
                                                                                   ( ux_ڈھیر_گہرائی * ( config_ڈھیر_گہرائی_TYPE ) حجم( ڈھیر_Type_t ) ) - 1UL );
            xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                       tskMPU_WRITE_PERMISSION );
        }

        l_اشاریہ = 0;

        برائے( ul = 1UL; ul <= پورٹ_عدد_CONFIGURABLE_REGIONS; ul++ )
        {
            اگر( ( xRegions[ l_اشاریہ ] ).ul_لمبائی_اندر_بائٹیں > 0UL )
            {
                /* Translate the generic region definition contained in
                 * xRegions into the CM4 specific MPU settings that are then
                 * stored in xMPUSettings. */
                xMPUSettings->xRegion[ ul ].ul_Region_بنیاد_پتہ =
                    ( ( uint32_t ) xRegions[ l_اشاریہ ].pv_بنیاد_پتہ ) |
                    ( پورٹ_MPU_REGION_VALID ) |
                    ( ul - 1UL ); /* Region number. */

                xMPUSettings->xRegion[ ul ].ulRegionAttribute =
                    ( prv_Get_MPURegion_سائز_Setting( xRegions[ l_اشاریہ ].ul_لمبائی_اندر_بائٹیں ) ) |
                    ( xRegions[ l_اشاریہ ].ulParameters ) |
                    ( پورٹ_MPU_REGION_ENABLE );

                xMPUSettings->xRegionSettings[ ul ].ul_Region_آغاز_پتہ = ( uint32_t ) xRegions[ l_اشاریہ ].pv_بنیاد_پتہ;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_انتہا_پتہ = ( uint32_t ) ( ( uint32_t ) xRegions[ l_اشاریہ ].pv_بنیاد_پتہ + xRegions[ l_اشاریہ ].ul_لمبائی_اندر_بائٹیں - 1UL );
                xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;

                اگر( ( ( xRegions[ l_اشاریہ ].ulParameters & پورٹ_MPU_REGION_READ_ONLY ) == پورٹ_MPU_REGION_READ_ONLY ) ||
                    ( ( xRegions[ l_اشاریہ ].ulParameters & پورٹ_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) == پورٹ_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = tskMPU_READ_PERMISSION;
                }

                اگر( ( xRegions[ l_اشاریہ ].ulParameters & پورٹ_MPU_REGION_READ_WRITE ) == پورٹ_MPU_REGION_READ_WRITE )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
                }
            }
            ورنہ
            {
                /* Invalidate the region. */
                xMPUSettings->xRegion[ ul ].ul_Region_بنیاد_پتہ = ( ( ul - 1UL ) | پورٹ_MPU_REGION_VALID );
                xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_آغاز_پتہ = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_انتہا_پتہ = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
            }

            l_اشاریہ++;
        }
    }
}
/*-----------------------------------------------------------*/

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

    بنیاد_Type_t x_پورٹ_Is_Authorized_مقصد_Access_بفر( ثابت خالی * pv_بفر,
                                                size_t x_بفر_لمبائی,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_بفر_آغاز_پتہ, ul_بفر_انتہا_پتہ;
        بنیاد_Type_t xAccessGranted = pdFALSE;
        ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( تہی ); /* Calling task's MPU settings. */

        اگر( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        ورنہ اگر( ( xTaskMpuSettings->ulTaskFlags & پورٹ_TASK_IS_PRIVILEGED_FLAG ) == پورٹ_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        ورنہ
        {
            اگر( پورٹ_جوڑو_UINT32_WILL_حد_سے_تجاوز( ( ( uint32_t ) pv_بفر ), ( ( uint32_t ) x_بفر_لمبائی - 1UL ) ) == pdFALSE )
            {
                ul_بفر_آغاز_پتہ = ( uint32_t ) pv_بفر;
                ul_بفر_انتہا_پتہ = ( ( ( uint32_t ) pv_بفر ) + ( uint32_t ) x_بفر_لمبائی - 1UL );

                برائے( i = 0; i < پورٹ_کل_عدد_REGIONS_اندر_TCB; i++ )
                {
                    اگر( پورٹ_IS_پتہ_WITHIN_RANGE( ul_بفر_آغاز_پتہ,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_آغاز_پتہ,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_انتہا_پتہ ) &&
                        پورٹ_IS_پتہ_WITHIN_RANGE( ul_بفر_انتہا_پتہ,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_آغاز_پتہ,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_انتہا_پتہ ) &&
                        پورٹ_IS_AUTHORIZED( ulAccessRequested, xTaskMpuSettings->xRegionSettings[ i ].ulRegionPermissions ) )
                    {
                        xAccessGranted = pdTRUE;
                        توڑو;
                    }
                }
            }
        }

        واپس xAccessGranted;
    }

#اگر_ختم /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#اگر ( configASSERT_DEFINED == 1 )

    خالی v_پورٹ_Validate_مداخلت_ترجیح( خالی )
    {
        uint32_t ul_Current_مداخلت;
        uint8_t uc_Current_ترجیح;

        /* Obtain the number of the currently executing interrupt. */
        __asm متلون ( "mrs %0, ipsr" : "=r" ( ul_Current_مداخلت )::"memory" );

        /* Is the interrupt number a user defined interrupt? */
        اگر( ul_Current_مداخلت >= پورٹ_پہلا_USER_مداخلت_نمبر )
        {
            /* Look up the interrupt's priority. */
            uc_Current_ترجیح = pc_مداخلت_ترجیح_Registers[ ul_Current_مداخلت ];

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

#اگر_ختم /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/

#اگر ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    خالی v_پورٹ_Grant_Access_مقصد_Kernel_Object( TaskHandle_t x_اندرونی_Task_Handle,
                                         int32_t l_اندرونی_اشاریہ_کا_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_اندراج_اشاریہ, ul_Access_Control_List_اندراج_ثنائی_ہندسہ;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_اندراج_اشاریہ = ( ( uint32_t ) l_اندرونی_اشاریہ_کا_Kernel_Object / پورٹ_ACL_اندراج_سائز_بٹ );
        ul_Access_Control_List_اندراج_ثنائی_ہندسہ = ( ( uint32_t ) l_اندرونی_اشاریہ_کا_Kernel_Object % پورٹ_ACL_اندراج_سائز_بٹ );

        xTaskMpuSettings = xTaskGetMPUSettings( x_اندرونی_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_اندراج_اشاریہ ] |= ( 1U << ul_Access_Control_List_اندراج_ثنائی_ہندسہ );
    }

#اگر_ختم /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#اگر ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    خالی v_پورٹ_Revoke_Access_مقصد_Kernel_Object( TaskHandle_t x_اندرونی_Task_Handle,
                                          int32_t l_اندرونی_اشاریہ_کا_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_اندراج_اشاریہ, ul_Access_Control_List_اندراج_ثنائی_ہندسہ;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_اندراج_اشاریہ = ( ( uint32_t ) l_اندرونی_اشاریہ_کا_Kernel_Object / پورٹ_ACL_اندراج_سائز_بٹ );
        ul_Access_Control_List_اندراج_ثنائی_ہندسہ = ( ( uint32_t ) l_اندرونی_اشاریہ_کا_Kernel_Object % پورٹ_ACL_اندراج_سائز_بٹ );

        xTaskMpuSettings = xTaskGetMPUSettings( x_اندرونی_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_اندراج_اشاریہ ] &= ~( 1U << ul_Access_Control_List_اندراج_ثنائی_ہندسہ );
    }

#اگر_ختم /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #اگر ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        بنیاد_Type_t x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( int32_t l_اندرونی_اشاریہ_کا_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_اندراج_اشاریہ, ul_Access_Control_List_اندراج_ثنائی_ہندسہ;
            بنیاد_Type_t xAccessGranted = pdFALSE;
            ثابت xMPU_SETTINGS * xTaskMpuSettings;

            اگر( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            ورنہ
            {
                xTaskMpuSettings = xTaskGetMPUSettings( تہی ); /* Calling task's MPU settings. */

                ul_Access_Control_List_اندراج_اشاریہ = ( ( uint32_t ) l_اندرونی_اشاریہ_کا_Kernel_Object / پورٹ_ACL_اندراج_سائز_بٹ );
                ul_Access_Control_List_اندراج_ثنائی_ہندسہ = ( ( uint32_t ) l_اندرونی_اشاریہ_کا_Kernel_Object % پورٹ_ACL_اندراج_سائز_بٹ );

                اگر( ( xTaskMpuSettings->ulTaskFlags & پورٹ_TASK_IS_PRIVILEGED_FLAG ) == پورٹ_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                ورنہ
                {
                    اگر( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_اندراج_اشاریہ ] & ( 1U << ul_Access_Control_List_اندراج_ثنائی_ہندسہ ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            واپس xAccessGranted;
        }

    #ورنہ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        بنیاد_Type_t x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( int32_t l_اندرونی_اشاریہ_کا_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( خالی ) l_اندرونی_اشاریہ_کا_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            واپس pdTRUE;
        }

    #اگر_ختم /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#اگر_ختم /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/
