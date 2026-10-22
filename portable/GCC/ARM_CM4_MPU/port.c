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
#నిర్వచించు MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"
#అన్తర్భావ "mpu_syscall_numbers.h"

#నిర్వచితం_కాకపోతే __ARM_FP
    #దోషం This పోర్టు can only be వాడిన when the project options are configured గమ్యం enable hardware floating బిందువు_2 support.
#అయితే_ముగింపు

#నిర్వచనం_రద్దు MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#నిర్వచితం_కాకపోతే configSYSTICK_CLOCK_HZ
    #నిర్వచించు configSYSTICK_CLOCK_HZ    configCPU_CLOCK_HZ
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #నిర్వచించు పోర్టు_NVIC_SYSTICK_CLK      ( 1UL << 2UL )
#లేకపోతే

/* The way the SysTick is clocked is not modified in case it is not the same
 * as the core. */
    #నిర్వచించు పోర్టు_NVIC_SYSTICK_CLK    ( 0 )
#అయితే_ముగింపు

/* Unprivileged critical sections are not supported when using MPU wrappers
 * version 2. Default the option to 0 and reject an explicit value of 1. */
#నిర్వచితం_కాకపోతే configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS
    #ఒకవేళ ( configUSE_MPU_WRAPPERS_V1 == 0 )
        #నిర్వచించు configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    0
    #లేకపోతే
        #warning "configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not defined. We recommend defining it to 0 in FreeRTOSConfig.h for better security."
        #నిర్వచించు configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    1
    #అయితే_ముగింపు
#లేకపోతే
    #ఒకవేళ ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) )
        #దోషం configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not supported with MPU wrappers సంస్కరణ 2 ( configUSE_MPU_WRAPPERS_V1 == 0 ).
    #అయితే_ముగింపు
#అయితే_ముగింపు

/* Prototype of all Interrupt Service Routines (ISRs). */
రకనిర్వచనం శూన్య ( * పోర్టు_ISR_t )( శూన్య );

/* Constants required to access and manipulate the NVIC. */
#నిర్వచించు పోర్టు_NVIC_SYSTICK_CTRL_REG                 ( *( ( అస్థిర uint32_t * ) 0xe000e010 ) )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG                 ( *( ( అస్థిర uint32_t * ) 0xe000e014 ) )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG        ( *( ( అస్థిర uint32_t * ) 0xe000e018 ) )
#నిర్వచించు పోర్టు_NVIC_SHPR3_REG                        ( *( ( అస్థిర uint32_t * ) 0xe000ed20 ) )
#నిర్వచించు పోర్టు_NVIC_SHPR2_REG                        ( *( ( అస్థిర uint32_t * ) 0xe000ed1c ) )
#నిర్వచించు పోర్టు_NVIC_SYS_CTRL_STATE_REG               ( *( ( అస్థిర uint32_t * ) 0xe000ed24 ) )
#నిర్వచించు పోర్టు_NVIC_MEM_FAULT_ENABLE                 ( 1UL << 16UL )

/* Constants used to detect Cortex-M7 r0p0 and r0p1 cores, and ensure
 * that a work around is active for errata 837070. */
#నిర్వచించు పోర్టు_CPUID                                 ( *( ( అస్థిర uint32_t * ) 0xE000ed00 ) )
#నిర్వచించు పోర్టు_CORTEX_M7_r0p1_ID                     ( 0x410FC271UL )
#నిర్వచించు పోర్టు_CORTEX_M7_r0p0_ID                     ( 0x410FC270UL )

/* Constants required to access and manipulate the MPU. */
#నిర్వచించు పోర్టు_MPU_TYPE_REG                          ( *( ( అస్థిర uint32_t * ) 0xe000ed90 ) )
#నిర్వచించు పోర్టు_MPU_REGION_పునాది_చిరునామా_REG           ( *( ( అస్థిర uint32_t * ) 0xe000ed9C ) )
#నిర్వచించు పోర్టు_MPU_REGION_ATTRIBUTE_REG              ( *( ( అస్థిర uint32_t * ) 0xe000edA0 ) )
#నిర్వచించు పోర్టు_MPU_CTRL_REG                          ( *( ( అస్థిర uint32_t * ) 0xe000ed94 ) )
#నిర్వచించు పోర్టు_EXPECTED_MPU_TYPE_విలువ               ( config_మొత్తం_MPU_REGIONS << 8UL )
#నిర్వచించు పోర్టు_MPU_ENABLE                            ( 0x01UL )
#నిర్వచించు పోర్టు_MPU_BACKGROUND_ENABLE                 ( 1UL << 2UL )
#నిర్వచించు పోర్టు_PRIVILEGED_EXECUTION_ప్రారంభం_చిరునామా    ( 0UL )
#నిర్వచించు పోర్టు_MPU_REGION_VALID                      ( 0x10UL )
#నిర్వచించు పోర్టు_MPU_REGION_ENABLE                     ( 0x01UL )
#నిర్వచించు పోర్టు_PERIPHERALS_ప్రారంభం_చిరునామా             0x40000000UL
#నిర్వచించు పోర్టు_PERIPHERALS_చివర_చిరునామా               0x5FFFFFFFUL

/* Constants required to access and manipulate the SysTick and other FreeRTOS
 * interrupts. */
#నిర్వచించు పోర్టు_NVIC_SYSTICK_INT                      ( 0x00000002UL )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_ENABLE                   ( 0x00000001UL )
#నిర్వచించు పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత                ( 255UL )
#నిర్వచించు పోర్టు_NVIC_PENDSV_PRI                       ( ( ( uint32_t ) పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత ) << 16UL )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_PRI                      ( ( ( uint32_t ) పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత ) << 24UL )
#నిర్వచించు పోర్టు_NVIC_SVC_PRI                          ( ( ( uint32_t ) config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత - 1UL ) << 24UL )

/* Constants required to manipulate the VFP. */
#నిర్వచించు పోర్టు_FPCCR                                 ( ( అస్థిర uint32_t * ) 0xe000ef34UL ) /* Floating point context control register. */
#నిర్వచించు పోర్టు_ASPEN_AND_LSPEN_బిట్లు                  ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#నిర్వచించు పోర్టు_INITIAL_XPSR                          ( 0x01000000UL )
#నిర్వచించు పోర్టు_INITIAL_EXC_RETURN                    ( 0xfffffffdUL )
#నిర్వచించు పోర్టు_INITIAL_CONTROL_IF_UNPRIVILEGED       ( 0x03 )
#నిర్వచించు పోర్టు_INITIAL_CONTROL_IF_PRIVILEGED         ( 0x02 )

/* Constants used to check the installation of the FreeRTOS interrupt handlers. */
#నిర్వచించు పోర్టు_SCB_VTOR_REG                          ( *( ( పోర్టు_ISR_t ** ) 0xE000ED08 ) )
#నిర్వచించు పోర్టు_సదిశ_సూచీ_SVC                      ( 11 )
#నిర్వచించు పోర్టు_సదిశ_సూచీ_PENDSV                   ( 14 )

/* Constants required to check the validity of an interrupt priority. */
#నిర్వచించు పోర్టు_మొదటి_USER_అంతరాయం_సంఖ్య           ( 16 )
#నిర్వచించు పోర్టు_NVIC_IP_REGISTERS_స్థానభ్రంశం_16           ( 0xE000E3F0 )
#నిర్వచించు పోర్టు_AIRCR_REG                             ( *( ( అస్థిర uint32_t * ) 0xE000ED0C ) )
#నిర్వచించు పోర్టు_MAX_8_బిట్టు_విలువ                       ( ( uint8_t ) 0xff )
#నిర్వచించు పోర్టు_శిఖరం_బిట్టు_యొక్క_BYTE                       ( ( uint8_t ) 0x80 )
#నిర్వచించు పోర్టు_MAX_PRIGROUP_బిట్లు                     ( ( uint8_t ) 7 )
#నిర్వచించు పోర్టు_ప్రాధాన్యత_సమూహం_ముసుగు                   ( 0x07UL << 8UL )
#నిర్వచించు పోర్టు_PRIGROUP_జరుపు                        ( 8UL )

/* Constants used during system call enter and exit. */
#నిర్వచించు పోర్టు_PSR_దొంతర_PADDING_ముసుగు                ( 1UL << 9UL )
#నిర్వచించు పోర్టు_EXC_RETURN_దొంతర_చట్రం_TYPE_ముసుగు      ( 1UL << 4UL )

/* Offsets in the stack to the parameters when inside the SVC handler. */
#నిర్వచించు పోర్టు_స్థానభ్రంశం_గమ్యం_LR                          ( 5 )
#నిర్వచించు పోర్టు_స్థానభ్రంశం_గమ్యం_PC                          ( 6 )
#నిర్వచించు పోర్టు_స్థానభ్రంశం_గమ్యం_PSR                         ( 7 )


/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#నిర్వచించు పోర్టు_ప్రారంభం_చిరునామా_ముసుగు    ( ( దొంతర_Type_t ) 0xfffffffeUL )

/* Does addr lie within [start, end] address range? */
#నిర్వచించు పోర్టు_IS_చిరునామా_WITHIN_RANGE( addr, ప్రారంభం, చివర ) \
    ( ( ( addr ) >= ( ప్రారంభం ) ) && ( ( addr ) <= ( చివర ) ) )

/* Is the access request satisfied by the available permissions? */
#నిర్వచించు పోర్టు_IS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#నిర్వచించు పోర్టు_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#నిర్వచించు పోర్టు_కూడు_UINT32_WILL_అధికప్రవాహం( a, b )    ( ( a ) > ( పోర్టు_UINT32_MAX - ( b ) ) )
/*-----------------------------------------------------------*/

/*
 * Configure a number of standard MPU regions that are used by all tasks.
 */
స్థిర శూన్య prv_అమరిక_MPU( శూన్య ) PRIVILEGED_FUNCTION;

/*
 * Return the smallest MPU region size that a given number of bytes will fit
 * into.  The region size is returned as the value that should be programmed
 * into the region attribute register for that region.
 */
స్థిర uint32_t prv_Get_MPURegion_కొలత_Setting( uint32_t ul_Actual_కొలత_లోపల_బైట్లు ) PRIVILEGED_FUNCTION;

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
శూన్య v_పోర్టు_అమరిక_Timer_అంతరాయం( శూన్య );

/*
 * Standard FreeRTOS exception handlers.
 */
శూన్య x_పోర్టు_Pend_SVHandler( శూన్య ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;
శూన్య x_పోర్టు_Sys_Tick_Handler( శూన్య ) PRIVILEGED_FUNCTION;
శూన్య v_పోర్టు_SVCHandler( శూన్య ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/*
 * Starts the scheduler by restoring the context of the first task to run.
 */
స్థిర శూన్య prv_Restore_Context_యొక్క_మొదటి_Task( శూన్య ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/*
 * C portion of the SVC handler.  The SVC handler is split between an asm entry
 * and a C wrapper for simplicity of coding and maintenance.
 */
శూన్య vSVCHandler_C( uint32_t * pulRegisters ) __attribute__( ( noinline ) ) PRIVILEGED_FUNCTION;

/*
 * Function to enable the VFP.
 */
స్థిర శూన్య v_పోర్టు_Enable_VFP( శూన్య ) __attribute__( ( naked ) );

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
పునాది_Type_t xIsPrivileged( శూన్య ) __attribute__( ( naked ) );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 *
 * Bit 0 of the CONTROL register defines the privilege level of Thread Mode.
 *  Bit[0] = 0 --> The processor is running privileged
 *  Bit[0] = 1 --> The processor is running unprivileged.
 */
శూన్య vResetPrivilege( శూన్య ) __attribute__( ( naked ) );

/**
 * @brief Make a task unprivileged.
 */
శూన్య v_పోర్టు_Switch_గమ్యం_User_బహుళకం( శూన్య );

/**
 * @brief Enter critical section.
 */
#ఒకవేళ ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    శూన్య v_పోర్టు_Enter_Critical( శూన్య ) FREERTOS_SYSTEM_CALL;
#లేకపోతే
    శూన్య v_పోర్టు_Enter_Critical( శూన్య ) PRIVILEGED_FUNCTION;
#అయితే_ముగింపు

/**
 * @brief Exit from critical section.
 */
#ఒకవేళ ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    శూన్య v_పోర్టు_Exit_Critical( శూన్య ) FREERTOS_SYSTEM_CALL;
#లేకపోతే
    శూన్య v_పోర్టు_Exit_Critical( శూన్య ) PRIVILEGED_FUNCTION;
#అయితే_ముగింపు

#ఒకవేళ ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the system call stack so that upon returning from
 * SVC, the system call stack is used.
 *
 * @param pulTaskStack The current SP when the SVC was raised.
 * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
 * @param ucSystemCallNumber The system call number of the system call.
 */
    శూన్య vSystemCallEnter( uint32_t * pul_Task_దొంతర,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_సంఖ్య ) PRIVILEGED_FUNCTION;

#అయితే_ముగింపు /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ఒకవేళ ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Raise SVC for exiting from a system call.
 */
    శూన్య vRequestSystemCallExit( శూన్య ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#అయితే_ముగింపు /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ఒకవేళ ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the task stack so that upon returning from
 * SVC, the task stack is used again.
 *
 * @param pulSystemCallStack The current SP when the SVC was raised.
 * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
 */
    శూన్య vSystemCallExit( uint32_t * pul_System_Call_దొంతర,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#అయితే_ముగింపు /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
పునాది_Type_t x_పోర్టు_Is_Task_Privileged( శూన్య ) PRIVILEGED_FUNCTION;
/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable.  Note this is not saved as part of the task context as context
 * switches can only occur when uxCriticalNesting is zero. */
స్థిర UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

#ఒకవేళ ( configUSE_MPU_WRAPPERS_V1 == 0 )

/*
 * This variable is set to pdTRUE when the scheduler is started.
 */
    PRIVILEGED_దత్తాంశం స్థిర పునాది_Type_t xSchedulerRunning = pdFALSE;

#అయితే_ముగింపు /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#ఒకవేళ ( configASSERT_DEFINED == 1 )
    స్థిర uint8_t uc_Max_Sys_Call_ప్రాధాన్యత = 0;
    స్థిర uint32_t ulMaxPRIGROUPValue = 0;
    స్థిర స్థిరరాశి అస్థిర uint8_t * స్థిరరాశి pc_అంతరాయం_ప్రాధాన్యత_Registers = ( స్థిరరాశి అస్థిర uint8_t * స్థిరరాశి ) పోర్టు_NVIC_IP_REGISTERS_స్థానభ్రంశం_16;
#అయితే_ముగింపు /* configASSERT_DEFINED */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters,
                                     పునాది_Type_t x_నిరంతరం_Privileged,
                                     xMPU_SETTINGS * xMPUSettings )
{
    ఒకవేళ( x_నిరంతరం_Privileged == pdTRUE )
    {
        xMPUSettings->ulTaskFlags |= పోర్టు_TASK_IS_PRIVILEGED_FLAG;
        xMPUSettings->ulContext[ 0 ] = పోర్టు_INITIAL_CONTROL_IF_PRIVILEGED;
    }
    లేకపోతే
    {
        xMPUSettings->ulTaskFlags &= ( ~( పోర్టు_TASK_IS_PRIVILEGED_FLAG ) );
        xMPUSettings->ulContext[ 0 ] = పోర్టు_INITIAL_CONTROL_IF_UNPRIVILEGED;
    }

    xMPUSettings->ulContext[ 1 ] = 0x04040404;                                        /* r4. */
    xMPUSettings->ulContext[ 2 ] = 0x05050505;                                        /* r5. */
    xMPUSettings->ulContext[ 3 ] = 0x06060606;                                        /* r6. */
    xMPUSettings->ulContext[ 4 ] = 0x07070707;                                        /* r7. */
    xMPUSettings->ulContext[ 5 ] = 0x08080808;                                        /* r8. */
    xMPUSettings->ulContext[ 6 ] = 0x09090909;                                        /* r9. */
    xMPUSettings->ulContext[ 7 ] = 0x10101010;                                        /* r10. */
    xMPUSettings->ulContext[ 8 ] = 0x11111111;                                        /* r11. */
    xMPUSettings->ulContext[ 9 ] = పోర్టు_INITIAL_EXC_RETURN;                            /* EXC_RETURN. */

    xMPUSettings->ulContext[ 10 ] = ( uint32_t ) ( px_శిఖరం_యొక్క_దొంతర - 8 );                /* PSP with the hardware saved stack. */
    xMPUSettings->ulContext[ 11 ] = ( uint32_t ) pvParameters;                        /* r0. */
    xMPUSettings->ulContext[ 12 ] = 0x01010101;                                       /* r1. */
    xMPUSettings->ulContext[ 13 ] = 0x02020202;                                       /* r2. */
    xMPUSettings->ulContext[ 14 ] = 0x03030303;                                       /* r3. */
    xMPUSettings->ulContext[ 15 ] = 0x12121212;                                       /* r12. */
    xMPUSettings->ulContext[ 16 ] = 0;                                                /* LR. */
    xMPUSettings->ulContext[ 17 ] = ( ( uint32_t ) px_సంకేతం ) & పోర్టు_ప్రారంభం_చిరునామా_ముసుగు; /* PC. */
    xMPUSettings->ulContext[ 18 ] = పోర్టు_INITIAL_XPSR;                                 /* xPSR. */

    #ఒకవేళ ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        /* Ensure that the system call stack is double word aligned. */
        xMPUSettings->x_System_Call_దొంతర_Info.pul_System_Call_దొంతర = &( xMPUSettings->x_System_Call_దొంతర_Info.ul_System_Call_దొంతర_బఫరు[ config_SYSTEM_CALL_దొంతర_కొలత - 1 ] );
        xMPUSettings->x_System_Call_దొంతర_Info.pul_System_Call_దొంతర = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_దొంతర_Info.pul_System_Call_దొంతర ) &
                                                                                 ( uint32_t ) ( ~( పోర్టు_BYTE_ALIGNMENT_ముసుగు ) ) );

        /* This is not NULL only for the duration of a system call. */
        xMPUSettings->x_System_Call_దొంతర_Info.pul_Task_దొంతర = ఖాళీ;
    }
    #అయితే_ముగింపు /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    తిరిగి &( xMPUSettings->ulContext[ 19 ] );
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    శూన్య v_పోర్టు_SVCHandler( శూన్య ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm అస్థిర
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
            : "i" ( అంకె_SYSTEM_CALLS ), "i" ( పోర్టు_SVC_SYSTEM_CALL_EXIT )
            : "r0", "r1", "r2", "memory"
        );
    }

#లేకపోతే /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    శూన్య v_పోర్టు_SVCHandler( శూన్య )
    {
        /* Assumes psp was in use. */
        __asm అస్థిర
        (
            #నిర్వచితం_కాకపోతే USE_PROCESS_దొంతర /* Code should not be required if a main() is using the process stack. */
                "   tst lr, #4                      \n"
                "   ite eq                          \n"
                "   mrseq r0, msp                   \n"
                "   mrsne r0, psp                   \n"
            #లేకపోతే
                "   mrs r0, psp                     \n"
            #అయితే_ముగింపు
            "   b %0                            \n"
            ::"i" ( vSVCHandler_C ) : "r0", "memory"
        );
    }

#అయితే_ముగింపు /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

శూన్య vSVCHandler_C( uint32_t * pulParam ) /* PRIVILEGED_FUNCTION */
{
    uint8_t ucSVCNumber;
    uint32_t ulPC;

    #ఒకవేళ ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) )
        #ఒకవేళ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            బాహ్య uint32_t * __syscalls_flash_start__;
            బాహ్య uint32_t * __syscalls_flash_end__;
        #లేకపోతే
            /* Declaration when these variable are exported from linker scripts. */
            బాహ్య uint32_t __syscalls_flash_start__[];
            బాహ్య uint32_t __syscalls_flash_end__[];
        #అయితే_ముగింపు /* #if defined( __ARMCC_VERSION ) */
    #అయితే_ముగింపు /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) ) */

    /* The stack contains: r0, r1, r2, r3, r12, LR, PC and xPSR.  The first
     * argument (r0) is pulParam[ 0 ]. */
    ulPC = pulParam[ పోర్టు_స్థానభ్రంశం_గమ్యం_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    ఎంపిక( ucSVCNumber )
    {
        స్థితి పోర్టు_SVC_ప్రారంభం_SCHEDULER:
            prv_Restore_Context_యొక్క_మొదటి_Task();
            ఆపు;

        స్థితి పోర్టు_SVC_YIELD:
            పోర్టు_NVIC_INT_CTRL_REG = పోర్టు_NVIC_PENDSVSET_బిట్టు;

            /* Barriers are normally not required
             * but do ensure the code is completely
             * within the specified behaviour for the
             * architecture. */
            __asm అస్థిర ( "dsb" ::: "memory" );
            __asm అస్థిర ( "isb" );

            ఆపు;

    #ఒకవేళ ( configUSE_MPU_WRAPPERS_V1 == 1 )
        #ఒకవేళ ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 )
            స్థితి పోర్టు_SVC_RAISE_PRIVILEGE: /* Only raise the privilege, if the
                                           * svc was raised from any of the
                                           * system calls. */

                ఒకవేళ( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                    ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
                {
                    __asm అస్థిర
                    (
                        "   mrs r1, control     \n" /* Obtain current control value. */
                        "   bic r1, #1          \n" /* Set privilege bit. */
                        "   msr control, r1     \n" /* Write back new control value. */
                        ::: "r1", "memory"
                    );
                }

                ఆపు;
        #లేకపోతే /* if ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
            స్థితి పోర్టు_SVC_RAISE_PRIVILEGE:
                __asm అస్థిర
                (
                    "   mrs r1, control     \n" /* Obtain current control value. */
                    "   bic r1, #1          \n" /* Set privilege bit. */
                    "   msr control, r1     \n" /* Write back new control value. */
                    ::: "r1", "memory"
                );
                ఆపు;
        #అయితే_ముగింపు /* #if( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
    #అయితే_ముగింపు /* #if ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

        అప్రమేయ: /* Unknown SVC call. */
            ఆపు;
    }
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    శూన్య vSystemCallEnter( uint32_t * pul_Task_దొంతర,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_సంఖ్య ) /* PRIVILEGED_FUNCTION */
    {
        బాహ్య TaskHandle_t pxCurrentTCB;
        బాహ్య UBaseType_t uxSystemCallImplementations[ అంకె_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_దొంతర;
        uint32_t ul_Hardware_Saved_Exception_చట్రం_కొలత, ulSystemCallLocation, i;

        #ఒకవేళ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            బాహ్య uint32_t * __syscalls_flash_start__;
            బాహ్య uint32_t * __syscalls_flash_end__;
        #లేకపోతే
            /* Declaration when these variable are exported from linker scripts. */
            బాహ్య uint32_t __syscalls_flash_start__[];
            బాహ్య uint32_t __syscalls_flash_end__[];
        #అయితే_ముగింపు /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PC ];
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
        ఒకవేళ( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_దొంతర_Info.pul_Task_దొంతర == ఖాళీ ) &&
            ( uxSystemCallImplementations[ uc_System_Call_సంఖ్య ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_దొంతర = pxMpuSettings->x_System_Call_దొంతర_Info.pul_System_Call_దొంతర;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            ఒకవేళ( ( ulLR & పోర్టు_EXC_RETURN_దొంతర_చట్రం_TYPE_ముసుగు ) == 0UL )
            {
                /* Extended frame i.e. FPU in use. */
                ul_Hardware_Saved_Exception_చట్రం_కొలత = 26;
                __asm అస్థిర (
                    " vpush {s0}         \n" /* Trigger lazy stacking. */
                    " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                    ::: "memory"
                    );
            }
            లేకపోతే
            {
                /* Standard frame i.e. FPU not in use. */
                ul_Hardware_Saved_Exception_చట్రం_కొలత = 8;
            }

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_దొంతర = pul_System_Call_దొంతర - ul_Hardware_Saved_Exception_చట్రం_కొలత;

            /* Copy the stack frame. */
            కొరకు( i = 0; i < ul_Hardware_Saved_Exception_చట్రం_కొలత; i++ )
            {
                pul_System_Call_దొంతర[ i ] = pul_Task_దొంతర[ i ];
            }

            /* Use the pulSystemCallStack in thread mode. */
            __asm అస్థిర ( "msr psp, %0" : : "r" ( pul_System_Call_దొంతర ) );

            /* Raise the privilege for the duration of the system call. */
            __asm అస్థిర (
                " mrs r1, control     \n" /* Obtain current control value. */
                " bic r1, #1          \n" /* Clear nPRIV bit. */
                " msr control, r1     \n" /* Write back new control value. */
                ::: "r1", "memory"
                );

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_దొంతర_Info.pul_Task_దొంతర = pul_Task_దొంతర + ul_Hardware_Saved_Exception_చట్రం_కొలత;

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_దొంతర_Info.ul_Link_రిజిస్టరు_At_System_Call_నమోదు = pul_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_LR ];

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PC ] = uxSystemCallImplementations[ uc_System_Call_సంఖ్య ];
            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            ఒకవేళ( ( pul_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PSR ] & పోర్టు_PSR_దొంతర_PADDING_ముసుగు ) == పోర్టు_PSR_దొంతర_PADDING_ముసుగు )
            {
                pxMpuSettings->ulTaskFlags |= పోర్టు_దొంతర_చట్రం_HAS_PADDING_FLAG;
            }
            లేకపోతే
            {
                pxMpuSettings->ulTaskFlags &= ( ~పోర్టు_దొంతర_చట్రం_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PSR ] &= ( ~పోర్టు_PSR_దొంతర_PADDING_ముసుగు );
        }
    }

#అయితే_ముగింపు /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    శూన్య vRequestSystemCallExit( శూన్య ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm అస్థిర ( "svc %0 \n" ::"i" ( పోర్టు_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#అయితే_ముగింపు /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    శూన్య vSystemCallExit( uint32_t * pul_System_Call_దొంతర,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        బాహ్య TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_దొంతర;
        uint32_t ul_Hardware_Saved_Exception_చట్రం_కొలత, ulSystemCallLocation, i;

        #ఒకవేళ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            బాహ్య uint32_t * __privileged_functions_start__;
            బాహ్య uint32_t * __privileged_functions_end__;
        #లేకపోతే
            /* Declaration when these variable are exported from linker scripts. */
            బాహ్య uint32_t __privileged_functions_start__[];
            బాహ్య uint32_t __privileged_functions_end__[];
        #అయితే_ముగింపు /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PC ];
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
        ఒకవేళ( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_దొంతర_Info.pul_Task_దొంతర != ఖాళీ ) )
        {
            pul_Task_దొంతర = pxMpuSettings->x_System_Call_దొంతర_Info.pul_Task_దొంతర;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            ఒకవేళ( ( ulLR & పోర్టు_EXC_RETURN_దొంతర_చట్రం_TYPE_ముసుగు ) == 0UL )
            {
                /* Extended frame i.e. FPU in use. */
                ul_Hardware_Saved_Exception_చట్రం_కొలత = 26;
                __asm అస్థిర (
                    " vpush {s0}         \n" /* Trigger lazy stacking. */
                    " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                    ::: "memory"
                    );
            }
            లేకపోతే
            {
                /* Standard frame i.e. FPU not in use. */
                ul_Hardware_Saved_Exception_చట్రం_కొలత = 8;
            }

            /* Make space on the task stack for the stack frame. */
            pul_Task_దొంతర = pul_Task_దొంతర - ul_Hardware_Saved_Exception_చట్రం_కొలత;

            /* Copy the stack frame. */
            కొరకు( i = 0; i < ul_Hardware_Saved_Exception_చట్రం_కొలత; i++ )
            {
                pul_Task_దొంతర[ i ] = pul_System_Call_దొంతర[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm అస్థిర ( "msr psp, %0" : : "r" ( pul_Task_దొంతర ) );

            /* Drop the privilege before returning to the thread mode. */
            __asm అస్థిర (
                " mrs r1, control     \n" /* Obtain current control value. */
                " orr r1, #1          \n" /* Set nPRIV bit. */
                " msr control, r1     \n" /* Write back new control value. */
                ::: "r1", "memory"
                );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PC ] = pxMpuSettings->x_System_Call_దొంతర_Info.ul_Link_రిజిస్టరు_At_System_Call_నమోదు;
            /* Ensure that LR has a valid value.*/
            pul_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_LR ] = pxMpuSettings->x_System_Call_దొంతర_Info.ul_Link_రిజిస్టరు_At_System_Call_నమోదు;

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            ఒకవేళ( ( pxMpuSettings->ulTaskFlags & పోర్టు_దొంతర_చట్రం_HAS_PADDING_FLAG ) == పోర్టు_దొంతర_చట్రం_HAS_PADDING_FLAG )
            {
                pul_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PSR ] |= పోర్టు_PSR_దొంతర_PADDING_ముసుగు;
            }
            లేకపోతే
            {
                pul_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PSR ] &= ( ~పోర్టు_PSR_దొంతర_PADDING_ముసుగు );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_దొంతర_Info.pul_Task_దొంతర = ఖాళీ;
        }
    }

#అయితే_ముగింపు /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_Is_Task_Privileged( శూన్య ) /* PRIVILEGED_FUNCTION */
{
    పునాది_Type_t xTaskIsPrivileged = pdFALSE;
    స్థిరరాశి xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ఖాళీ ); /* Calling task's MPU settings. */

    ఒకవేళ( ( xTaskMpuSettings->ulTaskFlags & పోర్టు_TASK_IS_PRIVILEGED_FLAG ) == పోర్టు_TASK_IS_PRIVILEGED_FLAG )
    {
        xTaskIsPrivileged = pdTRUE;
    }

    తిరిగి xTaskIsPrivileged;
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_Restore_Context_యొక్క_మొదటి_Task( శూన్య )
{
    __asm అస్థిర
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
        #ఒకవేళ ( config_మొత్తం_MPU_REGIONS == 16 )
            " ldmia r2!, {r4-r11}                   \n" /* Read 4 sets of MPU registers [MPU Region # 4 - 8]. */
            " stmia r0, {r4-r11}                    \n" /* Write 4 sets of MPU registers. [MPU Region # 4 - 8]. */
            " ldmia r2!, {r4-r11}                   \n" /* Read 4 sets of MPU registers [MPU Region # 9 - 12]. */
            " stmia r0, {r4-r11}                    \n" /* Write 4 sets of MPU registers. [MPU Region # 9 - 12]. */
        #అయితే_ముగింపు /* configTOTAL_MPU_REGIONS == 16. */
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
పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    /* Errata 837070 workaround must only be enabled on Cortex-M7 r0p0
     * and r0p1 cores. */
    #ఒకవేళ ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        configASSERT( ( పోర్టు_CPUID == పోర్టు_CORTEX_M7_r0p1_ID ) || ( పోర్టు_CPUID == పోర్టు_CORTEX_M7_r0p0_ID ) );
    #లేకపోతే

        /* When using this port on a Cortex-M7 r0p0 or r0p1 core, define
         * configENABLE_ERRATA_837070_WORKAROUND to 1 in your
         * FreeRTOSConfig.h. */
        configASSERT( పోర్టు_CPUID != పోర్టు_CORTEX_M7_r0p1_ID );
        configASSERT( పోర్టు_CPUID != పోర్టు_CORTEX_M7_r0p0_ID );
    #అయితే_ముగింపు

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
    #ఒకవేళ ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        స్థిరరాశి పోర్టు_ISR_t * స్థిరరాశి px_సదిశ_పట్టిక = పోర్టు_SCB_VTOR_REG;

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
        configASSERT( px_సదిశ_పట్టిక[ పోర్టు_సదిశ_సూచీ_SVC ] == v_పోర్టు_SVCHandler );
        configASSERT( px_సదిశ_పట్టిక[ పోర్టు_సదిశ_సూచీ_PENDSV ] == x_పోర్టు_Pend_SVHandler );
    }
    #అయితే_ముగింపు /* configCHECK_HANDLER_INSTALLATION */

    #ఒకవేళ ( configASSERT_DEFINED == 1 )
    {
        అస్థిర uint8_t uc_Original_ప్రాధాన్యత;
        అస్థిర uint32_t ul_Implemented_Prio_బిట్లు = 0;
        అస్థిర uint8_t * స్థిరరాశి puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు = ( అస్థిర uint8_t * స్థిరరాశి ) ( పోర్టు_NVIC_IP_REGISTERS_స్థానభ్రంశం_16 + పోర్టు_మొదటి_USER_అంతరాయం_సంఖ్య );
        అస్థిర uint8_t uc_Max_ప్రాధాన్యత_విలువ;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
         * functions can be called.  ISR safe functions are those that end in
         * "FromISR".  FreeRTOS maintains separate thread and ISR API functions to
         * ensure interrupt entry is as fast and simple as possible.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_ప్రాధాన్యత = *puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు;

        /* Determine the number of priority bits available.  First write to all
         * possible bits. */
        *puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు = పోర్టు_MAX_8_బిట్టు_విలువ;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ప్రాధాన్యత_విలువ = *puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు;

        /* Use the same mask on the maximum system call priority. */
        uc_Max_Sys_Call_ప్రాధాన్యత = config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత & uc_Max_ప్రాధాన్యత_విలువ;

        /* Check that the maximum system call priority is nonzero after
         * accounting for the number of priority bits supported by the
         * hardware. A priority of 0 is invalid because setting the BASEPRI
         * register to 0 unmasks all interrupts, and interrupts with priority 0
         * cannot be masked using BASEPRI.
         * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( uc_Max_Sys_Call_ప్రాధాన్యత );

        /* Check that the bits not implemented in hardware are zero in
         * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత & ( ~uc_Max_ప్రాధాన్యత_విలువ ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
         * of bits read back. */

        అయితే( ( uc_Max_ప్రాధాన్యత_విలువ & పోర్టు_శిఖరం_బిట్టు_యొక్క_BYTE ) == పోర్టు_శిఖరం_బిట్టు_యొక్క_BYTE )
        {
            ul_Implemented_Prio_బిట్లు++;
            uc_Max_ప్రాధాన్యత_విలువ <<= ( uint8_t ) 0x01;
        }

        ఒకవేళ( ul_Implemented_Prio_బిట్లు == 8 )
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
            configASSERT( ( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        లేకపోతే
        {
            ulMaxPRIGROUPValue = పోర్టు_MAX_PRIGROUP_బిట్లు - ul_Implemented_Prio_బిట్లు;
        }

        /* Shift the priority group value back to its position within the AIRCR
         * register. */
        ulMaxPRIGROUPValue <<= పోర్టు_PRIGROUP_జరుపు;
        ulMaxPRIGROUPValue &= పోర్టు_ప్రాధాన్యత_సమూహం_ముసుగు;

        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు = uc_Original_ప్రాధాన్యత;
    }
    #అయితే_ముగింపు /* configASSERT_DEFINED */

    /* Make PendSV and SysTick the lowest priority interrupts, and configure
     * SVCall for sufficient preemption priority. */
    పోర్టు_NVIC_SHPR3_REG |= పోర్టు_NVIC_PENDSV_PRI;
    పోర్టు_NVIC_SHPR3_REG |= పోర్టు_NVIC_SYSTICK_PRI;
    పోర్టు_NVIC_SHPR2_REG = పోర్టు_NVIC_SVC_PRI;

    /* Configure the regions in the MPU that are common to all tasks. */
    prv_అమరిక_MPU();

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_పోర్టు_అమరిక_Timer_అంతరాయం();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    #ఒకవేళ ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        xSchedulerRunning = pdTRUE;
    }
    #అయితే_ముగింపు /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    /* Ensure the VFP is enabled - it should be anyway. */
    v_పోర్టు_Enable_VFP();

    /* Lazy save always. */
    *( పోర్టు_FPCCR ) |= పోర్టు_ASPEN_AND_LSPEN_బిట్లు;

    /* Start the first task.  This also clears the bit that indicates the FPU is
     * in use in case the FPU was used before the scheduler was started - which
     * would otherwise result in the unnecessary leaving of space in the SVC stack
     * for lazy saving of FPU registers. */
    __asm అస్థిర (
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
        ::"i" ( పోర్టు_SVC_ప్రారంభం_SCHEDULER ) : "memory" );

    /* Should not get here! */
    తిరిగి 0;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Enter_Critical( శూన్య )
{
    #ఒకవేళ ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
        {
            పోర్టు_RAISE_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();

            పోర్టు_DISABLE_INTERRUPTS();
            uxCriticalNesting++;
            పోర్టు_జ్ఞాపకం_BARRIER();

            పోర్టు_RESET_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();
        }
        లేకపోతే
        {
            పోర్టు_DISABLE_INTERRUPTS();
            uxCriticalNesting++;
        }
    #లేకపోతే /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        పోర్టు_DISABLE_INTERRUPTS();
        uxCriticalNesting++;
    #అయితే_ముగింపు /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Exit_Critical( శూన్య )
{
    #ఒకవేళ ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
        {
            పోర్టు_RAISE_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();

            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            ఒకవేళ( uxCriticalNesting == 0 )
            {
                పోర్టు_ENABLE_INTERRUPTS();
            }

            పోర్టు_జ్ఞాపకం_BARRIER();

            పోర్టు_RESET_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();
        }
        లేకపోతే
        {
            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            ఒకవేళ( uxCriticalNesting == 0 )
            {
                పోర్టు_ENABLE_INTERRUPTS();
            }
        }
    #లేకపోతే /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        configASSERT( uxCriticalNesting );
        uxCriticalNesting--;

        ఒకవేళ( uxCriticalNesting == 0 )
        {
            పోర్టు_ENABLE_INTERRUPTS();
        }
    #అయితే_ముగింపు /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

శూన్య x_పోర్టు_Pend_SVHandler( శూన్య )
{
    /* This is a naked function. */

    __asm అస్థిర
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
        #ఒకవేళ ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
            " cpsid i                               \n" /* ARM Cortex-M7 r0p1 Errata 837070 workaround. */
        #అయితే_ముగింపు
        " msr basepri, r0                       \n"
        " dsb                                   \n"
        " isb                                   \n"
        #ఒకవేళ ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
            " cpsie i                               \n" /* ARM Cortex-M7 r0p1 Errata 837070 workaround. */
        #అయితే_ముగింపు
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
        #ఒకవేళ ( config_మొత్తం_MPU_REGIONS == 16 )
            " ldmia r2!, {r4-r11}                   \n" /* Read 4 sets of MPU registers [MPU Region # 4 - 7]. */
            " stmia r0, {r4-r11}                    \n" /* Write 4 sets of MPU registers. [MPU Region # 4 - 7]. */
            " ldmia r2!, {r4-r11}                   \n" /* Read 4 sets of MPU registers [MPU Region # 8 - 11]. */
            " stmia r0, {r4-r11}                    \n" /* Write 4 sets of MPU registers. [MPU Region # 8 - 11]. */
        #అయితే_ముగింపు /* configTOTAL_MPU_REGIONS == 16. */
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
        ::"i" ( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత )
    );
}
/*-----------------------------------------------------------*/

శూన్య x_పోర్టు_Sys_Tick_Handler( శూన్య )
{
    uint32_t ulDummy;

    ulDummy = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_గమ్యం_SCHEDULER();
            /* Pend a context switch. */
            పోర్టు_NVIC_INT_CTRL_REG = పోర్టు_NVIC_PENDSVSET_బిట్టు;
        }
        లేకపోతే
        {
            traceISR_EXIT();
        }
    }
    పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( ulDummy );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__attribute__( ( weak ) ) శూన్య v_పోర్టు_అమరిక_Timer_అంతరాయం( శూన్య )
{
    /* Stop and clear the SysTick. */
    పోర్టు_NVIC_SYSTICK_CTRL_REG = 0UL;
    పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_రేటు_HZ ) - 1UL;
    పోర్టు_NVIC_SYSTICK_CTRL_REG = ( పోర్టు_NVIC_SYSTICK_CLK | పోర్టు_NVIC_SYSTICK_INT | పోర్టు_NVIC_SYSTICK_ENABLE );
}
/*-----------------------------------------------------------*/

/* This is a naked function. */
స్థిర శూన్య v_పోర్టు_Enable_VFP( శూన్య )
{
    __asm అస్థిర
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

స్థిర శూన్య prv_అమరిక_MPU( శూన్య )
{
    #ఒకవేళ defined( __ARMCC_VERSION )

        /* Declaration when these variable are defined in code instead of being
         * exported from linker scripts. */
        బాహ్య uint32_t * __privileged_functions_start__;
        బాహ్య uint32_t * __privileged_functions_end__;
        బాహ్య uint32_t * __FLASH_segment_start__;
        బాహ్య uint32_t * __FLASH_segment_end__;
        బాహ్య uint32_t * __privileged_data_start__;
        బాహ్య uint32_t * __privileged_data_end__;
    #లేకపోతే
        /* Declaration when these variable are exported from linker scripts. */
        బాహ్య uint32_t __privileged_functions_start__[];
        బాహ్య uint32_t __privileged_functions_end__[];
        బాహ్య uint32_t __FLASH_segment_start__[];
        బాహ్య uint32_t __FLASH_segment_end__[];
        బాహ్య uint32_t __privileged_data_start__[];
        బాహ్య uint32_t __privileged_data_end__[];
    #అయితే_ముగింపు /* if defined( __ARMCC_VERSION ) */

    /* The only permitted number of regions are 8 or 16. */
    configASSERT( ( config_మొత్తం_MPU_REGIONS == 8 ) || ( config_మొత్తం_MPU_REGIONS == 16 ) );

    /* Ensure that the configTOTAL_MPU_REGIONS is configured correctly. */
    configASSERT( పోర్టు_MPU_TYPE_REG == పోర్టు_EXPECTED_MPU_TYPE_విలువ );

    /* Check the expected MPU is present. */
    ఒకవేళ( పోర్టు_MPU_TYPE_REG == పోర్టు_EXPECTED_MPU_TYPE_విలువ )
    {
        /* First setup the unprivileged flash for unprivileged read only access. */
        పోర్టు_MPU_REGION_పునాది_చిరునామా_REG = ( ( uint32_t ) __FLASH_segment_start__ ) | /* Base address. */
                                          ( పోర్టు_MPU_REGION_VALID ) |
                                          ( పోర్టు_UNPRIVILEGED_FLASH_REGION );

        పోర్టు_MPU_REGION_ATTRIBUTE_REG = ( పోర్టు_MPU_REGION_READ_ONLY ) |
                                       ( ( configTEX_S_C_B_FLASH & పోర్టు_MPU_RASR_TEX_S_C_B_ముసుగు ) << పోర్టు_MPU_RASR_TEX_S_C_B_LOCATION ) |
                                       ( prv_Get_MPURegion_కొలత_Setting( ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__ ) ) |
                                       ( పోర్టు_MPU_REGION_ENABLE );

        /* Setup the privileged flash for privileged only access.  This is where
         * the kernel code is placed. */
        పోర్టు_MPU_REGION_పునాది_చిరునామా_REG = ( ( uint32_t ) __privileged_functions_start__ ) | /* Base address. */
                                          ( పోర్టు_MPU_REGION_VALID ) |
                                          ( పోర్టు_PRIVILEGED_FLASH_REGION );

        పోర్టు_MPU_REGION_ATTRIBUTE_REG = ( పోర్టు_MPU_REGION_PRIVILEGED_READ_ONLY ) |
                                       ( ( configTEX_S_C_B_FLASH & పోర్టు_MPU_RASR_TEX_S_C_B_ముసుగు ) << పోర్టు_MPU_RASR_TEX_S_C_B_LOCATION ) |
                                       ( prv_Get_MPURegion_కొలత_Setting( ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__ ) ) |
                                       ( పోర్టు_MPU_REGION_ENABLE );

        /* Setup the privileged data RAM region.  This is where the kernel data
         * is placed. */
        పోర్టు_MPU_REGION_పునాది_చిరునామా_REG = ( ( uint32_t ) __privileged_data_start__ ) | /* Base address. */
                                          ( పోర్టు_MPU_REGION_VALID ) |
                                          ( పోర్టు_PRIVILEGED_RAM_REGION );

        పోర్టు_MPU_REGION_ATTRIBUTE_REG = ( పోర్టు_MPU_REGION_PRIVILEGED_READ_WRITE ) |
                                       ( పోర్టు_MPU_REGION_EXECUTE_NEVER ) |
                                       ( ( configTEX_S_C_B_SRAM & పోర్టు_MPU_RASR_TEX_S_C_B_ముసుగు ) << పోర్టు_MPU_RASR_TEX_S_C_B_LOCATION ) |
                                       prv_Get_MPURegion_కొలత_Setting( ( uint32_t ) __privileged_data_end__ - ( uint32_t ) __privileged_data_start__ ) |
                                       ( పోర్టు_MPU_REGION_ENABLE );

        /* By default allow everything to access the general peripherals.  The
         * system peripherals and registers are protected. */
        పోర్టు_MPU_REGION_పునాది_చిరునామా_REG = ( పోర్టు_PERIPHERALS_ప్రారంభం_చిరునామా ) |
                                          ( పోర్టు_MPU_REGION_VALID ) |
                                          ( పోర్టు_GENERAL_PERIPHERALS_REGION );

        పోర్టు_MPU_REGION_ATTRIBUTE_REG = ( పోర్టు_MPU_REGION_READ_WRITE | పోర్టు_MPU_REGION_EXECUTE_NEVER ) |
                                       ( prv_Get_MPURegion_కొలత_Setting( పోర్టు_PERIPHERALS_చివర_చిరునామా - పోర్టు_PERIPHERALS_ప్రారంభం_చిరునామా ) ) |
                                       ( పోర్టు_MPU_REGION_ENABLE );

        /* Enable the memory fault exception. */
        పోర్టు_NVIC_SYS_CTRL_STATE_REG |= పోర్టు_NVIC_MEM_FAULT_ENABLE;

        /* Enable the MPU with the background region configured. */
        పోర్టు_MPU_CTRL_REG |= ( పోర్టు_MPU_ENABLE | పోర్టు_MPU_BACKGROUND_ENABLE );
    }
}
/*-----------------------------------------------------------*/

స్థిర uint32_t prv_Get_MPURegion_కొలత_Setting( uint32_t ul_Actual_కొలత_లోపల_బైట్లు )
{
    uint32_t ul_Region_కొలత, ul_Return_విలువ = 4;

    /* 32 is the smallest region size, 31 is the largest valid value for
     * ulReturnValue. */
    కొరకు( ul_Region_కొలత = 32UL; ul_Return_విలువ < 31UL; ( ul_Region_కొలత <<= 1UL ) )
    {
        ఒకవేళ( ul_Actual_కొలత_లోపల_బైట్లు <= ul_Region_కొలత )
        {
            ఆపు;
        }
        లేకపోతే
        {
            ul_Return_విలువ++;
        }
    }

    /* Shift the code by one before returning so it can be written directly
     * into the correct bit position of the attribute register. */
    తిరిగి( ul_Return_విలువ << 1UL );
}
/*-----------------------------------------------------------*/

పునాది_Type_t xIsPrivileged( శూన్య ) /* __attribute__ (( naked )) */
{
    __asm అస్థిర
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

శూన్య vResetPrivilege( శూన్య ) /* __attribute__ (( naked )) */
{
    __asm అస్థిర
    (
        "   mrs r0, control                         \n" /* r0 = CONTROL. */
        "   orr r0, #1                              \n" /* r0 = r0 | 1. */
        "   msr control, r0                         \n" /* CONTROL = r0. */
        "   bx lr                                   \n" /* Return to the caller. */
        ::: "r0", "memory"
    );
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Switch_గమ్యం_User_బహుళకం( శూన్య )
{
    /* Load the current task's MPU settings from its TCB. */
    xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ఖాళీ );

    /* Mark the task as unprivileged. */
    xTaskMpuSettings->ulTaskFlags &= ( ~( పోర్టు_TASK_IS_PRIVILEGED_FLAG ) );

    /* Lower the processor's privilege level. */
    vResetPrivilege();
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                స్థిరరాశి నిర్మాణం x_జ్ఞాపకం_REGION * స్థిరరాశి xRegions,
                                దొంతర_Type_t * px_Bottom_యొక్క_దొంతర,
                                config_దొంతర_లోతు_TYPE ux_దొంతర_లోతు )
{
    #ఒకవేళ defined( __ARMCC_VERSION )

        /* Declaration when these variable are defined in code instead of being
         * exported from linker scripts. */
        బాహ్య uint32_t * __SRAM_segment_start__;
        బాహ్య uint32_t * __SRAM_segment_end__;
        బాహ్య uint32_t * __privileged_data_start__;
        బాహ్య uint32_t * __privileged_data_end__;
    #లేకపోతే
        /* Declaration when these variable are exported from linker scripts. */
        బాహ్య uint32_t __SRAM_segment_start__[];
        బాహ్య uint32_t __SRAM_segment_end__[];
        బాహ్య uint32_t __privileged_data_start__[];
        బాహ్య uint32_t __privileged_data_end__[];
    #అయితే_ముగింపు /* if defined( __ARMCC_VERSION ) */

    int32_t l_సూచీ;
    uint32_t ul;

    ఒకవేళ( xRegions == ఖాళీ )
    {
        /* No MPU regions are specified so allow access to all RAM. */
        xMPUSettings->xRegion[ 0 ].ul_Region_పునాది_చిరునామా =
            ( ( uint32_t ) __SRAM_segment_start__ ) | /* Base address. */
            ( పోర్టు_MPU_REGION_VALID ) |
            ( పోర్టు_దొంతర_REGION );                     /* Region number. */

        xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
            ( పోర్టు_MPU_REGION_READ_WRITE ) |
            ( పోర్టు_MPU_REGION_EXECUTE_NEVER ) |
            ( ( configTEX_S_C_B_SRAM & పోర్టు_MPU_RASR_TEX_S_C_B_ముసుగు ) << పోర్టు_MPU_RASR_TEX_S_C_B_LOCATION ) |
            ( prv_Get_MPURegion_కొలత_Setting( ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__ ) ) |
            ( పోర్టు_MPU_REGION_ENABLE );

        xMPUSettings->xRegionSettings[ 0 ].ul_Region_ప్రారంభం_చిరునామా = ( uint32_t ) __SRAM_segment_start__;
        xMPUSettings->xRegionSettings[ 0 ].ul_Region_చివర_చిరునామా = ( uint32_t ) __SRAM_segment_end__;
        xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                   tskMPU_WRITE_PERMISSION );

        /* Invalidate user configurable regions. */
        కొరకు( ul = 1UL; ul <= పోర్టు_అంకె_CONFIGURABLE_REGIONS; ul++ )
        {
            xMPUSettings->xRegion[ ul ].ul_Region_పునాది_చిరునామా = ( ( ul - 1UL ) | పోర్టు_MPU_REGION_VALID );
            xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ul_Region_ప్రారంభం_చిరునామా = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ul_Region_చివర_చిరునామా = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
        }
    }
    లేకపోతే
    {
        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid.  At all other
         * times the stack parameters will not be valid and it is assumed that the
         * stack region has already been configured. */
        ఒకవేళ( ux_దొంతర_లోతు > 0 )
        {
            /* Define the region that allows access to the stack. */
            xMPUSettings->xRegion[ 0 ].ul_Region_పునాది_చిరునామా =
                ( ( uint32_t ) px_Bottom_యొక్క_దొంతర ) |
                ( పోర్టు_MPU_REGION_VALID ) |
                ( పోర్టు_దొంతర_REGION ); /* Region number. */

            xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
                ( పోర్టు_MPU_REGION_READ_WRITE ) |
                ( పోర్టు_MPU_REGION_EXECUTE_NEVER ) |
                ( prv_Get_MPURegion_కొలత_Setting( ux_దొంతర_లోతు * ( config_దొంతర_లోతు_TYPE ) పరిమాణం( దొంతర_Type_t ) ) ) |
                ( ( configTEX_S_C_B_SRAM & పోర్టు_MPU_RASR_TEX_S_C_B_ముసుగు ) << పోర్టు_MPU_RASR_TEX_S_C_B_LOCATION ) |
                ( పోర్టు_MPU_REGION_ENABLE );

            xMPUSettings->xRegionSettings[ 0 ].ul_Region_ప్రారంభం_చిరునామా = ( uint32_t ) px_Bottom_యొక్క_దొంతర;
            xMPUSettings->xRegionSettings[ 0 ].ul_Region_చివర_చిరునామా = ( uint32_t ) ( ( uint32_t ) ( px_Bottom_యొక్క_దొంతర ) +
                                                                                   ( ux_దొంతర_లోతు * ( config_దొంతర_లోతు_TYPE ) పరిమాణం( దొంతర_Type_t ) ) - 1UL );
            xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                       tskMPU_WRITE_PERMISSION );
        }

        l_సూచీ = 0;

        కొరకు( ul = 1UL; ul <= పోర్టు_అంకె_CONFIGURABLE_REGIONS; ul++ )
        {
            ఒకవేళ( ( xRegions[ l_సూచీ ] ).ul_నిడివి_లోపల_బైట్లు > 0UL )
            {
                /* Translate the generic region definition contained in
                 * xRegions into the CM4 specific MPU settings that are then
                 * stored in xMPUSettings. */
                xMPUSettings->xRegion[ ul ].ul_Region_పునాది_చిరునామా =
                    ( ( uint32_t ) xRegions[ l_సూచీ ].pv_పునాది_చిరునామా ) |
                    ( పోర్టు_MPU_REGION_VALID ) |
                    ( ul - 1UL ); /* Region number. */

                xMPUSettings->xRegion[ ul ].ulRegionAttribute =
                    ( prv_Get_MPURegion_కొలత_Setting( xRegions[ l_సూచీ ].ul_నిడివి_లోపల_బైట్లు ) ) |
                    ( xRegions[ l_సూచీ ].ulParameters ) |
                    ( పోర్టు_MPU_REGION_ENABLE );

                xMPUSettings->xRegionSettings[ ul ].ul_Region_ప్రారంభం_చిరునామా = ( uint32_t ) xRegions[ l_సూచీ ].pv_పునాది_చిరునామా;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_చివర_చిరునామా = ( uint32_t ) ( ( uint32_t ) xRegions[ l_సూచీ ].pv_పునాది_చిరునామా + xRegions[ l_సూచీ ].ul_నిడివి_లోపల_బైట్లు - 1UL );
                xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;

                ఒకవేళ( ( ( xRegions[ l_సూచీ ].ulParameters & పోర్టు_MPU_REGION_READ_ONLY ) == పోర్టు_MPU_REGION_READ_ONLY ) ||
                    ( ( xRegions[ l_సూచీ ].ulParameters & పోర్టు_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) == పోర్టు_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = tskMPU_READ_PERMISSION;
                }

                ఒకవేళ( ( xRegions[ l_సూచీ ].ulParameters & పోర్టు_MPU_REGION_READ_WRITE ) == పోర్టు_MPU_REGION_READ_WRITE )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
                }
            }
            లేకపోతే
            {
                /* Invalidate the region. */
                xMPUSettings->xRegion[ ul ].ul_Region_పునాది_చిరునామా = ( ( ul - 1UL ) | పోర్టు_MPU_REGION_VALID );
                xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_ప్రారంభం_చిరునామా = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_చివర_చిరునామా = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
            }

            l_సూచీ++;
        }
    }
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    పునాది_Type_t x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( స్థిరరాశి శూన్య * pv_బఫరు,
                                                size_t x_బఫరు_నిడివి,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_బఫరు_ప్రారంభం_చిరునామా, ul_బఫరు_చివర_చిరునామా;
        పునాది_Type_t xAccessGranted = pdFALSE;
        స్థిరరాశి xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ఖాళీ ); /* Calling task's MPU settings. */

        ఒకవేళ( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        లేకపోతే ఒకవేళ( ( xTaskMpuSettings->ulTaskFlags & పోర్టు_TASK_IS_PRIVILEGED_FLAG ) == పోర్టు_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        లేకపోతే
        {
            ఒకవేళ( పోర్టు_కూడు_UINT32_WILL_అధికప్రవాహం( ( ( uint32_t ) pv_బఫరు ), ( ( uint32_t ) x_బఫరు_నిడివి - 1UL ) ) == pdFALSE )
            {
                ul_బఫరు_ప్రారంభం_చిరునామా = ( uint32_t ) pv_బఫరు;
                ul_బఫరు_చివర_చిరునామా = ( ( ( uint32_t ) pv_బఫరు ) + ( uint32_t ) x_బఫరు_నిడివి - 1UL );

                కొరకు( i = 0; i < పోర్టు_మొత్తం_అంకె_REGIONS_లోపల_TCB; i++ )
                {
                    ఒకవేళ( పోర్టు_IS_చిరునామా_WITHIN_RANGE( ul_బఫరు_ప్రారంభం_చిరునామా,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_ప్రారంభం_చిరునామా,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_చివర_చిరునామా ) &&
                        పోర్టు_IS_చిరునామా_WITHIN_RANGE( ul_బఫరు_చివర_చిరునామా,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_ప్రారంభం_చిరునామా,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_చివర_చిరునామా ) &&
                        పోర్టు_IS_AUTHORIZED( ulAccessRequested, xTaskMpuSettings->xRegionSettings[ i ].ulRegionPermissions ) )
                    {
                        xAccessGranted = pdTRUE;
                        ఆపు;
                    }
                }
            }
        }

        తిరిగి xAccessGranted;
    }

#అయితే_ముగింపు /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configASSERT_DEFINED == 1 )

    శూన్య v_పోర్టు_Validate_అంతరాయం_ప్రాధాన్యత( శూన్య )
    {
        uint32_t ul_Current_అంతరాయం;
        uint8_t uc_Current_ప్రాధాన్యత;

        /* Obtain the number of the currently executing interrupt. */
        __asm అస్థిర ( "mrs %0, ipsr" : "=r" ( ul_Current_అంతరాయం )::"memory" );

        /* Is the interrupt number a user defined interrupt? */
        ఒకవేళ( ul_Current_అంతరాయం >= పోర్టు_మొదటి_USER_అంతరాయం_సంఖ్య )
        {
            /* Look up the interrupt's priority. */
            uc_Current_ప్రాధాన్యత = pc_అంతరాయం_ప్రాధాన్యత_Registers[ ul_Current_అంతరాయం ];

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
            configASSERT( uc_Current_ప్రాధాన్యత >= uc_Max_Sys_Call_ప్రాధాన్యత );
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
        configASSERT( ( పోర్టు_AIRCR_REG & పోర్టు_ప్రాధాన్యత_సమూహం_ముసుగు ) <= ulMaxPRIGROUPValue );
    }

#అయితే_ముగింపు /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    శూన్య v_పోర్టు_Grant_Access_గమ్యం_Kernel_Object( TaskHandle_t x_అంతర్గత_Task_Handle,
                                         int32_t l_అంతర్గత_సూచీ_యొక్క_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_నమోదు_సూచీ, ul_Access_Control_List_నమోదు_బిట్టు;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_నమోదు_సూచీ = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object / పోర్టు_ACL_నమోదు_కొలత_బిట్లు );
        ul_Access_Control_List_నమోదు_బిట్టు = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object % పోర్టు_ACL_నమోదు_కొలత_బిట్లు );

        xTaskMpuSettings = xTaskGetMPUSettings( x_అంతర్గత_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_నమోదు_సూచీ ] |= ( 1U << ul_Access_Control_List_నమోదు_బిట్టు );
    }

#అయితే_ముగింపు /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    శూన్య v_పోర్టు_Revoke_Access_గమ్యం_Kernel_Object( TaskHandle_t x_అంతర్గత_Task_Handle,
                                          int32_t l_అంతర్గత_సూచీ_యొక్క_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_నమోదు_సూచీ, ul_Access_Control_List_నమోదు_బిట్టు;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_నమోదు_సూచీ = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object / పోర్టు_ACL_నమోదు_కొలత_బిట్లు );
        ul_Access_Control_List_నమోదు_బిట్టు = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object % పోర్టు_ACL_నమోదు_కొలత_బిట్లు );

        xTaskMpuSettings = xTaskGetMPUSettings( x_అంతర్గత_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_నమోదు_సూచీ ] &= ~( 1U << ul_Access_Control_List_నమోదు_బిట్టు );
    }

#అయితే_ముగింపు /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #ఒకవేళ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        పునాది_Type_t x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( int32_t l_అంతర్గత_సూచీ_యొక్క_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_నమోదు_సూచీ, ul_Access_Control_List_నమోదు_బిట్టు;
            పునాది_Type_t xAccessGranted = pdFALSE;
            స్థిరరాశి xMPU_SETTINGS * xTaskMpuSettings;

            ఒకవేళ( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            లేకపోతే
            {
                xTaskMpuSettings = xTaskGetMPUSettings( ఖాళీ ); /* Calling task's MPU settings. */

                ul_Access_Control_List_నమోదు_సూచీ = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object / పోర్టు_ACL_నమోదు_కొలత_బిట్లు );
                ul_Access_Control_List_నమోదు_బిట్టు = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object % పోర్టు_ACL_నమోదు_కొలత_బిట్లు );

                ఒకవేళ( ( xTaskMpuSettings->ulTaskFlags & పోర్టు_TASK_IS_PRIVILEGED_FLAG ) == పోర్టు_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                లేకపోతే
                {
                    ఒకవేళ( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_నమోదు_సూచీ ] & ( 1U << ul_Access_Control_List_నమోదు_బిట్టు ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            తిరిగి xAccessGranted;
        }

    #లేకపోతే /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        పునాది_Type_t x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( int32_t l_అంతర్గత_సూచీ_యొక్క_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( శూన్య ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            తిరిగి pdTRUE;
        }

    #అయితే_ముగింపు /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#అయితే_ముగింపు /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/
