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
#ਅਨ੍ਤਰ੍ਭਾਵ <intrinsics.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mpu_syscall_numbers.h"

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __ARMVFP__
    #ਗਲਤੀ This ਪੋਰਟ can only be ਵਰਤਿਆ when the project options are configured ਮੰਜ਼ਿਲ enable hardware floating ਬਿੰਦੂ_2 support.
#ਜੇ_ਅੰਤ

#ਜੇ ( config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ == 0 )
    #ਗਲਤੀ config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ must not be ਸੈੱਟ ਮੰਜ਼ਿਲ 0.  See http: /*www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configSYSTICK_CLOCK_HZ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configSYSTICK_CLOCK_HZ      configCPU_CLOCK_HZ
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ    ( 1UL << 2UL )
#ਨਹੀਂਤਾਂ

/* The way the SysTick is clocked is not modified in case it is not the same
 * as the core. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ    ( 0 )
#ਜੇ_ਅੰਤ

/* Unprivileged critical sections are not supported when using MPU wrappers
 * version 2. Default the option to 0 and reject an explicit value of 1. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS
    #ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 0 )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    0
    #ਨਹੀਂਤਾਂ
        #warning "configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not defined. We recommend defining it to 0 in FreeRTOSConfig.h for better security."
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    1
    #ਜੇ_ਅੰਤ
#ਨਹੀਂਤਾਂ
    #ਜੇ ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) )
        #ਗਲਤੀ configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not supported with MPU wrappers ਸੰਸਕਰਣ 2 ( configUSE_MPU_WRAPPERS_V1 == 0 ).
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

/* Prototype of all Interrupt Service Routines (ISRs). */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ ( * ਪੋਰਟ_ISR_t )( ਖਾਲੀ );

/* Constants required to manipulate the core.  Registers first... */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG                 ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000e010 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG                 ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000e014 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG        ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000e018 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SHPR3_REG                        ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed20 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SHPR2_REG                        ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed1c ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYS_CTRL_STATE_REG               ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed24 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_MEM_FAULT_ENABLE                 ( 1UL << 16UL )

/* Constants required to access and manipulate the MPU. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_TYPE_REG                          ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed90 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਅਧਾਰ_ਪਤਾ_REG           ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed9C ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ATTRIBUTE_REG              ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000edA0 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_CTRL_REG                          ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed94 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXPECTED_MPU_TYPE_ਮੁੱਲ               ( config_ਕੁੱਲ_MPU_REGIONS << 8UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_ENABLE                            ( 0x01UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_BACKGROUND_ENABLE                 ( 1UL << 2UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIVILEGED_EXECUTION_ਸ਼ੁਰੂ_ਪਤਾ    ( 0UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_VALID                      ( 0x10UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ENABLE                     ( 0x01UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PERIPHERALS_ਸ਼ੁਰੂ_ਪਤਾ             0x40000000UL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PERIPHERALS_ਸਿਰਾ_ਪਤਾ               0x5FFFFFFFUL

/* ...then bits in the registers. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_INT_ਦੋਆਧਾਰੀ_ਅੰਕ                  ( 1UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ               ( 1UL << 0UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_ਗਿਣਤੀ_FLAG_ਦੋਆਧਾਰੀ_ਅੰਕ           ( 1UL << 16UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_PENDSVCLEAR_ਦੋਆਧਾਰੀ_ਅੰਕ                  ( 1UL << 27UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_PEND_SYSTICK_CLEAR_ਦੋਆਧਾਰੀ_ਅੰਕ           ( 1UL << 25UL )

/* Constants used to detect Cortex-M7 r0p0 and r0p1 cores, and ensure
 * that a work around is active for errata 837070. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CPUID                                 ( *( ( ਅਸਥਿਰ uint32_t * ) 0xE000ed00 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CORTEX_M7_r0p1_ID                     ( 0x410FC271UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CORTEX_M7_r0p0_ID                     ( 0x410FC270UL )

/* Constants to manipulate FreeRTOS interrupt priorities. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MIN_ਰੁਕਾਵਟ_ਤਰਜੀਹ                ( 255UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_PENDSV_PRI                       ( ( ( uint32_t ) ਪੋਰਟ_MIN_ਰੁਕਾਵਟ_ਤਰਜੀਹ ) << 16UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_PRI                      ( ( ( uint32_t ) ਪੋਰਟ_MIN_ਰੁਕਾਵਟ_ਤਰਜੀਹ ) << 24UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SVC_PRI                          ( ( ( uint32_t ) config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ - 1UL ) << 24UL )

/* Constants used to check the installation of the FreeRTOS interrupt handlers. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SCB_VTOR_REG                          ( *( ( ਪੋਰਟ_ISR_t ** ) 0xE000ED08 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਦਿਸ਼_ਸੂਚਕਾਂਕ_SVC                      ( 11 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਦਿਸ਼_ਸੂਚਕਾਂਕ_PENDSV                   ( 14 )

/* Constants required to check the validity of an interrupt priority. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਪਹਿਲਾ_USER_ਰੁਕਾਵਟ_ਸੰਖਿਆ           ( 16 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_IP_REGISTERS_ਵਿੱਥ_16           ( 0xE000E3F0 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_AIRCR_REG                             ( *( ( ਅਸਥਿਰ uint32_t * ) 0xE000ED0C ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_8_ਦੋਆਧਾਰੀ_ਅੰਕ_ਮੁੱਲ                       ( ( uint8_t ) 0xff )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਿਖਰ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਦਾ_BYTE                       ( ( uint8_t ) 0x80 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_PRIGROUP_ਬਿੱਟ                     ( ( uint8_t ) 7 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਤਰਜੀਹ_ਸਮੂਹ_ਨਕਾਬ                   ( 0x07UL << 8UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIGROUP_ਖਿਸਕਾਓ                        ( 8UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_VECTACTIVE_ਨਕਾਬ                       ( 0xFFUL )

/* Constants required to manipulate the VFP. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FPCCR                                 ( ( ਅਸਥਿਰ uint32_t * ) 0xe000ef34 ) /* Floating point context control register. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ASPEN_AND_LSPEN_ਬਿੱਟ                  ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_XPSR                          ( 0x01000000 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_EXC_RETURN                    ( 0xfffffffd )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_CONTROL_IF_UNPRIVILEGED       ( 0x03 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_CONTROL_IF_PRIVILEGED         ( 0x02 )

/* Constants used during system call enter and exit. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PSR_ਢੇਰ_PADDING_ਨਕਾਬ                ( 1UL << 9UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXC_RETURN_ਢੇਰ_ਚੌਖਟਾ_TYPE_ਨਕਾਬ      ( 1UL << 4UL )

/* Offsets in the stack to the parameters when inside the SVC handler. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_LR                          ( 5 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PC                          ( 6 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PSR                         ( 7 )

/* The systick is a 24-bit counter. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_24_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੰਖਿਆ                     ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MISSED_COUNTS_ਗੁਣਕ                  ( 45UL )

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਤਾ_ਨਕਾਬ                    ( ( ਢੇਰ_Type_t ) 0xfffffffeUL )

/* Does addr lie within [start, end] address range? */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IS_ਪਤਾ_WITHIN_RANGE( addr, ਸ਼ੁਰੂ, ਸਿਰਾ ) \
    ( ( ( addr ) >= ( ਸ਼ੁਰੂ ) ) && ( ( addr ) <= ( ਸਿਰਾ ) ) )

/* Is the access request satisfied by the available permissions? */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਜੋੜੋ_UINT32_WILL_ਉਛਾਲ( a, b )    ( ( a ) > ( ਪੋਰਟ_UINT32_MAX - ( b ) ) )
/*-----------------------------------------------------------*/

/*
 * Configure a number of standard MPU regions that are used by all tasks.
 */
ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_MPU( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

/*
 * Return the smallest MPU region size that a given number of bytes will fit
 * into.  The region size is returned as the value that should be programmed
 * into the region attribute register for that region.
 */
ਸਥਿਰ uint32_t prv_Get_MPURegion_ਮਾਪ_Setting( uint32_t ul_Actual_ਮਾਪ_ਵਿੱਚ_ਬਾਈਟਾਂ ) PRIVILEGED_FUNCTION;

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
ਖਾਲੀ v_ਪੋਰਟ_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );

/*
 * Exception handlers.
 */
ਖਾਲੀ x_ਪੋਰਟ_Sys_Tick_Handler( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

/*
 * Turn the VFP on.
 */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Enable_VFP( ਖਾਲੀ );

/*
 * The C portion of the SVC handler.
 */
ਖਾਲੀ v_ਪੋਰਟ_SVCHandler_C( uint32_t * pulParam ) PRIVILEGED_FUNCTION;

/*
 * Called from the SVC handler used to start the scheduler.
 */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Restore_Context_ਦਾ_ਪਹਿਲਾ_Task( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

/**
 * @brief Enter critical section.
 */
#ਜੇ ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ ) FREERTOS_SYSTEM_CALL;
#ਨਹੀਂਤਾਂ
    ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ ) PRIVILEGED_FUNCTION;
#ਜੇ_ਅੰਤ

/**
 * @brief Exit from critical section.
 */
#ਜੇ ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ ) FREERTOS_SYSTEM_CALL;
#ਨਹੀਂਤਾਂ
    ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ ) PRIVILEGED_FUNCTION;
#ਜੇ_ਅੰਤ

#ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the system call stack so that upon returning from
 * SVC, the system call stack is used.
 *
 * @param pulTaskStack The current SP when the SVC was raised.
 * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
 * @param ucSystemCallNumber The system call number of the system call.
 */
    ਖਾਲੀ vSystemCallEnter( uint32_t * pul_Task_ਢੇਰ,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_ਸੰਖਿਆ ) PRIVILEGED_FUNCTION;

#ਜੇ_ਅੰਤ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Raise SVC for exiting from a system call.
 */
    ਖਾਲੀ vRequestSystemCallExit( ਖਾਲੀ ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#ਜੇ_ਅੰਤ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the task stack so that upon returning from
 * SVC, the task stack is used again.
 *
 * @param pulSystemCallStack The current SP when the SVC was raised.
 * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
 */
    ਖਾਲੀ vSystemCallExit( uint32_t * pul_System_Call_ਢੇਰ,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#ਜੇ_ਅੰਤ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Task_Privileged( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

/**
 * @brief Make a task unprivileged.
 */
ਖਾਲੀ v_ਪੋਰਟ_Switch_ਮੰਜ਼ਿਲ_User_ਬਹੁਲਕ( ਖਾਲੀ );

/*
 * FreeRTOS handlers implemented in assembly.
 */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_SVCHandler( ਖਾਲੀ ) PRIVILEGED_FUNCTION;
ਬਾਹਰੀ ਖਾਲੀ x_ਪੋਰਟ_Pend_SVHandler( ਖਾਲੀ ) PRIVILEGED_FUNCTION;
/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
ਸਥਿਰ UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

#ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 0 )

/*
 * This variable is set to pdTRUE when the scheduler is started.
 */
    PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ ਅਧਾਰ_Type_t xSchedulerRunning = pdFALSE;

#ਜੇ_ਅੰਤ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#ਜੇ ( configASSERT_DEFINED == 1 )
    ਸਥਿਰ uint8_t uc_Max_Sys_Call_ਤਰਜੀਹ = 0;
    ਸਥਿਰ uint32_t ulMaxPRIGROUPValue = 0;
    ਸਥਿਰ ਅਚਲ ਅਸਥਿਰ uint8_t * ਅਚਲ pc_ਰੁਕਾਵਟ_ਤਰਜੀਹ_Registers = ( ਅਚਲ ਅਸਥਿਰ uint8_t * ਅਚਲ ) ਪੋਰਟ_NVIC_IP_REGISTERS_ਵਿੱਥ_16;
#ਜੇ_ਅੰਤ /* configASSERT_DEFINED */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters,
                                     ਅਧਾਰ_Type_t x_ਲੜੀਵਾਰ_Privileged,
                                     xMPU_SETTINGS * xMPUSettings )
{
    ਜੇ( x_ਲੜੀਵਾਰ_Privileged == pdTRUE )
    {
        xMPUSettings->ulTaskFlags |= ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG;
        xMPUSettings->ulContext[ 0 ] = ਪੋਰਟ_INITIAL_CONTROL_IF_PRIVILEGED;
    }
    ਨਹੀਂਤਾਂ
    {
        xMPUSettings->ulTaskFlags &= ( ~( ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG ) );
        xMPUSettings->ulContext[ 0 ] = ਪੋਰਟ_INITIAL_CONTROL_IF_UNPRIVILEGED;
    }

    xMPUSettings->ulContext[ 1 ] = 0x04040404;                                        /* r4. */
    xMPUSettings->ulContext[ 2 ] = 0x05050505;                                        /* r5. */
    xMPUSettings->ulContext[ 3 ] = 0x06060606;                                        /* r6. */
    xMPUSettings->ulContext[ 4 ] = 0x07070707;                                        /* r7. */
    xMPUSettings->ulContext[ 5 ] = 0x08080808;                                        /* r8. */
    xMPUSettings->ulContext[ 6 ] = 0x09090909;                                        /* r9. */
    xMPUSettings->ulContext[ 7 ] = 0x10101010;                                        /* r10. */
    xMPUSettings->ulContext[ 8 ] = 0x11111111;                                        /* r11. */
    xMPUSettings->ulContext[ 9 ] = ਪੋਰਟ_INITIAL_EXC_RETURN;                            /* EXC_RETURN. */

    xMPUSettings->ulContext[ 10 ] = ( uint32_t ) ( px_ਸਿਖਰ_ਦਾ_ਢੇਰ - 8 );                /* PSP with the hardware saved stack. */
    xMPUSettings->ulContext[ 11 ] = ( uint32_t ) pvParameters;                        /* r0. */
    xMPUSettings->ulContext[ 12 ] = 0x01010101;                                       /* r1. */
    xMPUSettings->ulContext[ 13 ] = 0x02020202;                                       /* r2. */
    xMPUSettings->ulContext[ 14 ] = 0x03030303;                                       /* r3. */
    xMPUSettings->ulContext[ 15 ] = 0x12121212;                                       /* r12. */
    xMPUSettings->ulContext[ 16 ] = 0;                                                /* LR. */
    xMPUSettings->ulContext[ 17 ] = ( ( uint32_t ) px_ਕੋਡ ) & ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਤਾ_ਨਕਾਬ; /* PC. */
    xMPUSettings->ulContext[ 18 ] = ਪੋਰਟ_INITIAL_XPSR;                                 /* xPSR. */

    #ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        /* Ensure that the system call stack is double word aligned. */
        xMPUSettings->x_System_Call_ਢੇਰ_Info.pul_System_Call_ਢੇਰ = &( xMPUSettings->x_System_Call_ਢੇਰ_Info.ul_System_Call_ਢੇਰ_ਬਫਰ[ config_SYSTEM_CALL_ਢੇਰ_ਮਾਪ - 1 ] );
        xMPUSettings->x_System_Call_ਢੇਰ_Info.pul_System_Call_ਢੇਰ = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_ਢੇਰ_Info.pul_System_Call_ਢੇਰ ) &
                                                                                 ( uint32_t ) ( ~( ਪੋਰਟ_BYTE_ALIGNMENT_ਨਕਾਬ ) ) );

        /* This is not NULL only for the duration of a system call. */
        xMPUSettings->x_System_Call_ਢੇਰ_Info.pul_Task_ਢੇਰ = ਨਿਰਾ;
    }
    #ਜੇ_ਅੰਤ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    ਵਾਪਸ &( xMPUSettings->ulContext[ 19 ] );
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_SVCHandler_C( uint32_t * pulParam ) /* PRIVILEGED_FUNCTION */
{
    uint8_t ucSVCNumber;
    uint32_t ulPC;

    #ਜੇ ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) )
        ਬਾਹਰੀ uint32_t __syscalls_flash_start__[];
        ਬਾਹਰੀ uint32_t __syscalls_flash_end__[];
    #ਜੇ_ਅੰਤ /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) ) */

    /* The stack contains: r0, r1, r2, r3, r12, LR, PC and xPSR. The first
     * argument (r0) is pulParam[ 0 ]. */
    ulPC = pulParam[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    ਚੋਣ( ucSVCNumber )
    {
        ਹਾਲਤ ਪੋਰਟ_SVC_ਸ਼ੁਰੂ_SCHEDULER:
            v_ਪੋਰਟ_Restore_Context_ਦਾ_ਪਹਿਲਾ_Task();
            ਰੋਕੋ;

        ਹਾਲਤ ਪੋਰਟ_SVC_YIELD:
            ਪੋਰਟ_NVIC_INT_CTRL_REG = ਪੋਰਟ_NVIC_PENDSVSET_ਦੋਆਧਾਰੀ_ਅੰਕ;

            /* Barriers are normally not required
             * but do ensure the code is completely
             * within the specified behaviour for the
             * architecture. */
            __asm ਅਸਥਿਰ ( "dsb" ::: "memory" );
            __asm ਅਸਥਿਰ ( "isb" );

            ਰੋਕੋ;

    #ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 1 )
        #ਜੇ ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 )
            ਹਾਲਤ ਪੋਰਟ_SVC_RAISE_PRIVILEGE: /* Only raise the privilege, if the
                                           * svc was raised from any of the
                                           * system calls. */

                ਜੇ( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                    ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
                {
                    __asm ਅਸਥਿਰ
                    (
                        "   mrs r1, control     \n" /* Obtain current control value. */
                        "   bic r1, r1, #1      \n" /* Set privilege bit. */
                        "   msr control, r1     \n" /* Write back new control value. */
                        ::: "r1", "memory"
                    );
                }

                ਰੋਕੋ;
        #ਨਹੀਂਤਾਂ /* if ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
            ਹਾਲਤ ਪੋਰਟ_SVC_RAISE_PRIVILEGE:
                __asm ਅਸਥਿਰ
                (
                    "   mrs r1, control     \n" /* Obtain current control value. */
                    "   bic r1, r1, #1      \n" /* Set privilege bit. */
                    "   msr control, r1     \n" /* Write back new control value. */
                    ::: "r1", "memory"
                );
                ਰੋਕੋ;
        #ਜੇ_ਅੰਤ /* #if( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
    #ਜੇ_ਅੰਤ /* #if ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

        ਮੂਲ: /* Unknown SVC call. */
            ਰੋਕੋ;
    }
}
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    ਖਾਲੀ vSystemCallEnter( uint32_t * pul_Task_ਢੇਰ,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_ਸੰਖਿਆ ) /* PRIVILEGED_FUNCTION */
    {
        ਬਾਹਰੀ TaskHandle_t pxCurrentTCB;
        ਬਾਹਰੀ UBaseType_t uxSystemCallImplementations[ ਅੰਕ_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_ਢੇਰ;
        uint32_t ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ, ulSystemCallLocation, i;

        #ਜੇ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ਬਾਹਰੀ uint32_t * __syscalls_flash_start__;
            ਬਾਹਰੀ uint32_t * __syscalls_flash_end__;
        #ਨਹੀਂਤਾਂ
            /* Declaration when these variable are exported from linker scripts. */
            ਬਾਹਰੀ uint32_t __syscalls_flash_start__[];
            ਬਾਹਰੀ uint32_t __syscalls_flash_end__[];
        #ਜੇ_ਅੰਤ /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PC ];
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
        ਜੇ( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_ਢੇਰ_Info.pul_Task_ਢੇਰ == ਨਿਰਾ ) &&
            ( uxSystemCallImplementations[ uc_System_Call_ਸੰਖਿਆ ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_ਢੇਰ = pxMpuSettings->x_System_Call_ਢੇਰ_Info.pul_System_Call_ਢੇਰ;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            ਜੇ( ( ulLR & ਪੋਰਟ_EXC_RETURN_ਢੇਰ_ਚੌਖਟਾ_TYPE_ਨਕਾਬ ) == 0UL )
            {
                /* Extended frame i.e. FPU in use. */
                ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ = 26;
                __asm ਅਸਥਿਰ (
                    " vpush {s0}         \n" /* Trigger lazy stacking. */
                    " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                    ::: "memory"
                    );
            }
            ਨਹੀਂਤਾਂ
            {
                /* Standard frame i.e. FPU not in use. */
                ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ = 8;
            }

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_ਢੇਰ = pul_System_Call_ਢੇਰ - ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ;

            /* Copy the stack frame. */
            ਲਈ( i = 0; i < ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ; i++ )
            {
                pul_System_Call_ਢੇਰ[ i ] = pul_Task_ਢੇਰ[ i ];
            }

            /* Use the pulSystemCallStack in thread mode. */
            __asm ਅਸਥਿਰ ( "msr psp, %0" : : "r" ( pul_System_Call_ਢੇਰ ) );

            /* Raise the privilege for the duration of the system call. */
            __asm ਅਸਥਿਰ (
                " mrs r1, control     \n" /* Obtain current control value. */
                " bic r1, #1          \n" /* Clear nPRIV bit. */
                " msr control, r1     \n" /* Write back new control value. */
                ::: "r1", "memory"
                );

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_ਢੇਰ_Info.pul_Task_ਢੇਰ = pul_Task_ਢੇਰ + ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ;

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_ਢੇਰ_Info.ul_Link_ਰਜਿਸਟਰ_At_System_Call_ਇੰਦਰਾਜ = pul_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_LR ];


            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PC ] = uxSystemCallImplementations[ uc_System_Call_ਸੰਖਿਆ ];
            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            ਜੇ( ( pul_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PSR ] & ਪੋਰਟ_PSR_ਢੇਰ_PADDING_ਨਕਾਬ ) == ਪੋਰਟ_PSR_ਢੇਰ_PADDING_ਨਕਾਬ )
            {
                pxMpuSettings->ulTaskFlags |= ਪੋਰਟ_ਢੇਰ_ਚੌਖਟਾ_HAS_PADDING_FLAG;
            }
            ਨਹੀਂਤਾਂ
            {
                pxMpuSettings->ulTaskFlags &= ( ~ਪੋਰਟ_ਢੇਰ_ਚੌਖਟਾ_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PSR ] &= ( ~ਪੋਰਟ_PSR_ਢੇਰ_PADDING_ਨਕਾਬ );
        }
    }

#ਜੇ_ਅੰਤ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    ਖਾਲੀ vRequestSystemCallExit( ਖਾਲੀ ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm ਅਸਥਿਰ ( "svc %0 \n" ::"i" ( ਪੋਰਟ_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#ਜੇ_ਅੰਤ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    ਖਾਲੀ vSystemCallExit( uint32_t * pul_System_Call_ਢੇਰ,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        ਬਾਹਰੀ TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_ਢੇਰ;
        uint32_t ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ, ulSystemCallLocation, i;

        #ਜੇ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ਬਾਹਰੀ uint32_t * __privileged_functions_start__;
            ਬਾਹਰੀ uint32_t * __privileged_functions_end__;
        #ਨਹੀਂਤਾਂ
            /* Declaration when these variable are exported from linker scripts. */
            ਬਾਹਰੀ uint32_t __privileged_functions_start__[];
            ਬਾਹਰੀ uint32_t __privileged_functions_end__[];
        #ਜੇ_ਅੰਤ /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PC ];
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
        ਜੇ( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_ਢੇਰ_Info.pul_Task_ਢੇਰ != ਨਿਰਾ ) )
        {
            pul_Task_ਢੇਰ = pxMpuSettings->x_System_Call_ਢੇਰ_Info.pul_Task_ਢੇਰ;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            ਜੇ( ( ulLR & ਪੋਰਟ_EXC_RETURN_ਢੇਰ_ਚੌਖਟਾ_TYPE_ਨਕਾਬ ) == 0UL )
            {
                /* Extended frame i.e. FPU in use. */
                ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ = 26;
                __asm ਅਸਥਿਰ (
                    " vpush {s0}         \n" /* Trigger lazy stacking. */
                    " vpop  {s0}         \n" /* Nullify the affect of the above instruction. */
                    ::: "memory"
                    );
            }
            ਨਹੀਂਤਾਂ
            {
                /* Standard frame i.e. FPU not in use. */
                ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ = 8;
            }

            /* Make space on the task stack for the stack frame. */
            pul_Task_ਢੇਰ = pul_Task_ਢੇਰ - ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ;

            /* Copy the stack frame. */
            ਲਈ( i = 0; i < ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ; i++ )
            {
                pul_Task_ਢੇਰ[ i ] = pul_System_Call_ਢੇਰ[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm ਅਸਥਿਰ ( "msr psp, %0" : : "r" ( pul_Task_ਢੇਰ ) );

            /* Drop the privilege before returning to the thread mode. */
            __asm ਅਸਥਿਰ (
                " mrs r1, control     \n" /* Obtain current control value. */
                " orr r1, #1          \n" /* Set nPRIV bit. */
                " msr control, r1     \n" /* Write back new control value. */
                ::: "r1", "memory"
                );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PC ] = pxMpuSettings->x_System_Call_ਢੇਰ_Info.ul_Link_ਰਜਿਸਟਰ_At_System_Call_ਇੰਦਰਾਜ;
            /* Ensure that LR has a valid value.*/
            pul_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_LR ] = pxMpuSettings->x_System_Call_ਢੇਰ_Info.ul_Link_ਰਜਿਸਟਰ_At_System_Call_ਇੰਦਰਾਜ;

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            ਜੇ( ( pxMpuSettings->ulTaskFlags & ਪੋਰਟ_ਢੇਰ_ਚੌਖਟਾ_HAS_PADDING_FLAG ) == ਪੋਰਟ_ਢੇਰ_ਚੌਖਟਾ_HAS_PADDING_FLAG )
            {
                pul_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PSR ] |= ਪੋਰਟ_PSR_ਢੇਰ_PADDING_ਨਕਾਬ;
            }
            ਨਹੀਂਤਾਂ
            {
                pul_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PSR ] &= ( ~ਪੋਰਟ_PSR_ਢੇਰ_PADDING_ਨਕਾਬ );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_ਢੇਰ_Info.pul_Task_ਢੇਰ = ਨਿਰਾ;
        }
    }

#ਜੇ_ਅੰਤ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Task_Privileged( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
{
    ਅਧਾਰ_Type_t xTaskIsPrivileged = pdFALSE;
    ਅਚਲ xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ਨਿਰਾ ); /* Calling task's MPU settings. */

    ਜੇ( ( xTaskMpuSettings->ulTaskFlags & ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG ) == ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG )
    {
        xTaskIsPrivileged = pdTRUE;
    }

    ਵਾਪਸ xTaskIsPrivileged;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Switch_ਮੰਜ਼ਿਲ_User_ਬਹੁਲਕ( ਖਾਲੀ )
{
    /* Load the current task's MPU settings from its TCB. */
    xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ਨਿਰਾ );

    /* Mark the task as unprivileged. */
    xTaskMpuSettings->ulTaskFlags &= ( ~( ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG ) );

    /* Lower the processor's privilege level. */
    vResetPrivilege();
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    /* Errata 837070 workaround must only be enabled on Cortex-M7 r0p0
     * and r0p1 cores. */
    #ਜੇ ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        configASSERT( ( ਪੋਰਟ_CPUID == ਪੋਰਟ_CORTEX_M7_r0p1_ID ) || ( ਪੋਰਟ_CPUID == ਪੋਰਟ_CORTEX_M7_r0p0_ID ) );
    #ਨਹੀਂਤਾਂ

        /* When using this port on a Cortex-M7 r0p0 or r0p1 core, define
         * configENABLE_ERRATA_837070_WORKAROUND to 1 in your
         * FreeRTOSConfig.h. */
        configASSERT( ਪੋਰਟ_CPUID != ਪੋਰਟ_CORTEX_M7_r0p1_ID );
        configASSERT( ਪੋਰਟ_CPUID != ਪੋਰਟ_CORTEX_M7_r0p0_ID );
    #ਜੇ_ਅੰਤ

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
    #ਜੇ ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        ਅਚਲ ਪੋਰਟ_ISR_t * ਅਚਲ px_ਸਦਿਸ਼_ਸਾਰਣੀ = ਪੋਰਟ_SCB_VTOR_REG;

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
        configASSERT( px_ਸਦਿਸ਼_ਸਾਰਣੀ[ ਪੋਰਟ_ਸਦਿਸ਼_ਸੂਚਕਾਂਕ_SVC ] == v_ਪੋਰਟ_SVCHandler );
        configASSERT( px_ਸਦਿਸ਼_ਸਾਰਣੀ[ ਪੋਰਟ_ਸਦਿਸ਼_ਸੂਚਕਾਂਕ_PENDSV ] == x_ਪੋਰਟ_Pend_SVHandler );
    }
    #ਜੇ_ਅੰਤ /* configCHECK_HANDLER_INSTALLATION */

    #ਜੇ ( configASSERT_DEFINED == 1 )
    {
        ਅਸਥਿਰ uint8_t uc_Original_ਤਰਜੀਹ;
        ਅਸਥਿਰ uint32_t ul_Implemented_Prio_ਬਿੱਟ = 0;
        ਅਸਥਿਰ uint8_t * ਅਚਲ puc_ਪਹਿਲਾ_User_ਤਰਜੀਹ_ਰਜਿਸਟਰ = ( ਅਸਥਿਰ uint8_t * ਅਚਲ ) ( ਪੋਰਟ_NVIC_IP_REGISTERS_ਵਿੱਥ_16 + ਪੋਰਟ_ਪਹਿਲਾ_USER_ਰੁਕਾਵਟ_ਸੰਖਿਆ );
        ਅਸਥਿਰ uint8_t uc_Max_ਤਰਜੀਹ_ਮੁੱਲ;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
         * functions can be called.  ISR safe functions are those that end in
         * "FromISR".  FreeRTOS maintains separate thread and ISR API functions to
         * ensure interrupt entry is as fast and simple as possible.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_ਤਰਜੀਹ = *puc_ਪਹਿਲਾ_User_ਤਰਜੀਹ_ਰਜਿਸਟਰ;

        /* Determine the number of priority bits available.  First write to all
         * possible bits. */
        *puc_ਪਹਿਲਾ_User_ਤਰਜੀਹ_ਰਜਿਸਟਰ = ਪੋਰਟ_MAX_8_ਦੋਆਧਾਰੀ_ਅੰਕ_ਮੁੱਲ;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ਤਰਜੀਹ_ਮੁੱਲ = *puc_ਪਹਿਲਾ_User_ਤਰਜੀਹ_ਰਜਿਸਟਰ;

        /* Use the same mask on the maximum system call priority. */
        uc_Max_Sys_Call_ਤਰਜੀਹ = config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ & uc_Max_ਤਰਜੀਹ_ਮੁੱਲ;

        /* Check that the maximum system call priority is nonzero after
         * accounting for the number of priority bits supported by the
         * hardware. A priority of 0 is invalid because setting the BASEPRI
         * register to 0 unmasks all interrupts, and interrupts with priority 0
         * cannot be masked using BASEPRI.
         * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( uc_Max_Sys_Call_ਤਰਜੀਹ );

        /* Check that the bits not implemented in hardware are zero in
         * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ & ( uint8_t ) ( ~( uint32_t ) uc_Max_ਤਰਜੀਹ_ਮੁੱਲ ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
         * of bits read back. */

        ਜਦੋਂ( ( uc_Max_ਤਰਜੀਹ_ਮੁੱਲ & ਪੋਰਟ_ਸਿਖਰ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਦਾ_BYTE ) == ਪੋਰਟ_ਸਿਖਰ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਦਾ_BYTE )
        {
            ul_Implemented_Prio_ਬਿੱਟ++;
            uc_Max_ਤਰਜੀਹ_ਮੁੱਲ <<= ( uint8_t ) 0x01;
        }

        ਜੇ( ul_Implemented_Prio_ਬਿੱਟ == 8 )
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
            configASSERT( ( config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        ਨਹੀਂਤਾਂ
        {
            ulMaxPRIGROUPValue = ਪੋਰਟ_MAX_PRIGROUP_ਬਿੱਟ - ul_Implemented_Prio_ਬਿੱਟ;
        }

        /* Shift the priority group value back to its position within the AIRCR
         * register. */
        ulMaxPRIGROUPValue <<= ਪੋਰਟ_PRIGROUP_ਖਿਸਕਾਓ;
        ulMaxPRIGROUPValue &= ਪੋਰਟ_ਤਰਜੀਹ_ਸਮੂਹ_ਨਕਾਬ;

        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_ਪਹਿਲਾ_User_ਤਰਜੀਹ_ਰਜਿਸਟਰ = uc_Original_ਤਰਜੀਹ;
    }
    #ਜੇ_ਅੰਤ /* configASSERT_DEFINED */

    /* Make PendSV and SysTick the lowest priority interrupts, and configure
     * SVCall for sufficient preemption priority. */
    ਪੋਰਟ_NVIC_SHPR3_REG |= ਪੋਰਟ_NVIC_PENDSV_PRI;
    ਪੋਰਟ_NVIC_SHPR3_REG |= ਪੋਰਟ_NVIC_SYSTICK_PRI;
    ਪੋਰਟ_NVIC_SHPR2_REG = ਪੋਰਟ_NVIC_SVC_PRI;

    /* Configure the regions in the MPU that are common to all tasks. */
    prv_ਤਿਆਰੀ_MPU();

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_ਪੋਰਟ_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    #ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        xSchedulerRunning = pdTRUE;
    }
    #ਜੇ_ਅੰਤ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    /* Ensure the VFP is enabled - it should be anyway. */
    v_ਪੋਰਟ_Enable_VFP();

    /* Lazy save always. */
    *( ਪੋਰਟ_FPCCR ) |= ਪੋਰਟ_ASPEN_AND_LSPEN_ਬਿੱਟ;

    /* Start the first task. */
    v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();

    /* Should not get here! */
    ਵਾਪਸ 0;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ )
{
    #ਜੇ ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
        {
            ਪੋਰਟ_RAISE_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            ਪੋਰਟ_DISABLE_INTERRUPTS();
            uxCriticalNesting++;

            /* This is not the interrupt safe version of the enter critical function so
             * assert() if it is being called from an interrupt context.  Only API
             * functions that end in "FromISR" can be used in an interrupt.  Only assert if
             * the critical nesting count is 1 to protect against recursive calls if the
             * assert function also uses a critical section. */
            ਜੇ( uxCriticalNesting == 1 )
            {
                configASSERT( ( ਪੋਰਟ_NVIC_INT_CTRL_REG & ਪੋਰਟ_VECTACTIVE_ਨਕਾਬ ) == 0 );
            }

            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            ਪੋਰਟ_RESET_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
        }
        ਨਹੀਂਤਾਂ
        {
            ਪੋਰਟ_DISABLE_INTERRUPTS();
            uxCriticalNesting++;

            /* This is not the interrupt safe version of the enter critical function so
             * assert() if it is being called from an interrupt context.  Only API
             * functions that end in "FromISR" can be used in an interrupt.  Only assert if
             * the critical nesting count is 1 to protect against recursive calls if the
             * assert function also uses a critical section. */
            ਜੇ( uxCriticalNesting == 1 )
            {
                configASSERT( ( ਪੋਰਟ_NVIC_INT_CTRL_REG & ਪੋਰਟ_VECTACTIVE_ਨਕਾਬ ) == 0 );
            }
        }
    #ਨਹੀਂਤਾਂ /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        ਪੋਰਟ_DISABLE_INTERRUPTS();
        uxCriticalNesting++;

        /* This is not the interrupt safe version of the enter critical function so
         * assert() if it is being called from an interrupt context.  Only API
         * functions that end in "FromISR" can be used in an interrupt.  Only assert if
         * the critical nesting count is 1 to protect against recursive calls if the
         * assert function also uses a critical section. */
        ਜੇ( uxCriticalNesting == 1 )
        {
            configASSERT( ( ਪੋਰਟ_NVIC_INT_CTRL_REG & ਪੋਰਟ_VECTACTIVE_ਨਕਾਬ ) == 0 );
        }
    #ਜੇ_ਅੰਤ /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ )
{
    #ਜੇ ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
        {
            ਪੋਰਟ_RAISE_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            ਜੇ( uxCriticalNesting == 0 )
            {
                ਪੋਰਟ_ENABLE_INTERRUPTS();
            }

            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            ਪੋਰਟ_RESET_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
        }
        ਨਹੀਂਤਾਂ
        {
            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            ਜੇ( uxCriticalNesting == 0 )
            {
                ਪੋਰਟ_ENABLE_INTERRUPTS();
            }
        }
    #ਨਹੀਂਤਾਂ /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        configASSERT( uxCriticalNesting );
        uxCriticalNesting--;

        ਜੇ( uxCriticalNesting == 0 )
        {
            ਪੋਰਟ_ENABLE_INTERRUPTS();
        }
    #ਜੇ_ਅੰਤ /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

ਖਾਲੀ x_ਪੋਰਟ_Sys_Tick_Handler( ਖਾਲੀ )
{
    /* The SysTick runs at the lowest interrupt priority, so when this interrupt
     * executes all interrupts must be unmasked.  There is therefore no need to
     * save and then restore the interrupt mask value as its value is already
     * known. */
    ਪੋਰਟ_DISABLE_INTERRUPTS();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        ਜੇ( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_ਮੰਜ਼ਿਲ_SCHEDULER();

            /* A context switch is required.  Context switching is performed in
             * the PendSV interrupt.  Pend the PendSV interrupt. */
            ਪੋਰਟ_NVIC_INT_CTRL_REG = ਪੋਰਟ_NVIC_PENDSVSET_ਦੋਆਧਾਰੀ_ਅੰਕ;
        }
        ਨਹੀਂਤਾਂ
        {
            traceISR_EXIT();
        }
    }
    ਪੋਰਟ_ENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__weak ਖਾਲੀ v_ਪੋਰਟ_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    /* Stop and clear the SysTick. */
    ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG = 0UL;
    ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_ਦਰ_HZ ) - 1UL;
    ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG = ( ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ | ਪੋਰਟ_NVIC_SYSTICK_INT_ਦੋਆਧਾਰੀ_ਅੰਕ | ਪੋਰਟ_NVIC_SYSTICK_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ );
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_MPU( ਖਾਲੀ )
{
    ਬਾਹਰੀ uint32_t __privileged_functions_start__[];
    ਬਾਹਰੀ uint32_t __privileged_functions_end__[];
    ਬਾਹਰੀ uint32_t __FLASH_segment_start__[];
    ਬਾਹਰੀ uint32_t __FLASH_segment_end__[];
    ਬਾਹਰੀ uint32_t __privileged_data_start__[];
    ਬਾਹਰੀ uint32_t __privileged_data_end__[];

    /* The only permitted number of regions are 8 or 16. */
    configASSERT( ( config_ਕੁੱਲ_MPU_REGIONS == 8 ) || ( config_ਕੁੱਲ_MPU_REGIONS == 16 ) );

    /* Ensure that the configTOTAL_MPU_REGIONS is configured correctly. */
    configASSERT( ਪੋਰਟ_MPU_TYPE_REG == ਪੋਰਟ_EXPECTED_MPU_TYPE_ਮੁੱਲ );

    /* Check the expected MPU is present. */
    ਜੇ( ਪੋਰਟ_MPU_TYPE_REG == ਪੋਰਟ_EXPECTED_MPU_TYPE_ਮੁੱਲ )
    {
        /* First setup the unprivileged flash for unprivileged read only access. */
        ਪੋਰਟ_MPU_REGION_ਅਧਾਰ_ਪਤਾ_REG = ( ( uint32_t ) __FLASH_segment_start__ ) | /* Base address. */
                                          ( ਪੋਰਟ_MPU_REGION_VALID ) |
                                          ( ਪੋਰਟ_UNPRIVILEGED_FLASH_REGION );

        ਪੋਰਟ_MPU_REGION_ATTRIBUTE_REG = ( ਪੋਰਟ_MPU_REGION_READ_ONLY ) |
                                       ( ( configTEX_S_C_B_FLASH & ਪੋਰਟ_MPU_RASR_TEX_S_C_B_ਨਕਾਬ ) << ਪੋਰਟ_MPU_RASR_TEX_S_C_B_LOCATION ) |
                                       ( prv_Get_MPURegion_ਮਾਪ_Setting( ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__ ) ) |
                                       ( ਪੋਰਟ_MPU_REGION_ENABLE );

        /* Setup the privileged flash for privileged only access.  This is where
         * the kernel code is placed. */
        ਪੋਰਟ_MPU_REGION_ਅਧਾਰ_ਪਤਾ_REG = ( ( uint32_t ) __privileged_functions_start__ ) | /* Base address. */
                                          ( ਪੋਰਟ_MPU_REGION_VALID ) |
                                          ( ਪੋਰਟ_PRIVILEGED_FLASH_REGION );

        ਪੋਰਟ_MPU_REGION_ATTRIBUTE_REG = ( ਪੋਰਟ_MPU_REGION_PRIVILEGED_READ_ONLY ) |
                                       ( ( configTEX_S_C_B_FLASH & ਪੋਰਟ_MPU_RASR_TEX_S_C_B_ਨਕਾਬ ) << ਪੋਰਟ_MPU_RASR_TEX_S_C_B_LOCATION ) |
                                       ( prv_Get_MPURegion_ਮਾਪ_Setting( ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__ ) ) |
                                       ( ਪੋਰਟ_MPU_REGION_ENABLE );

        /* Setup the privileged data RAM region.  This is where the kernel data
         * is placed. */
        ਪੋਰਟ_MPU_REGION_ਅਧਾਰ_ਪਤਾ_REG = ( ( uint32_t ) __privileged_data_start__ ) | /* Base address. */
                                          ( ਪੋਰਟ_MPU_REGION_VALID ) |
                                          ( ਪੋਰਟ_PRIVILEGED_RAM_REGION );

        ਪੋਰਟ_MPU_REGION_ATTRIBUTE_REG = ( ਪੋਰਟ_MPU_REGION_PRIVILEGED_READ_WRITE ) |
                                       ( ਪੋਰਟ_MPU_REGION_EXECUTE_NEVER ) |
                                       ( ( configTEX_S_C_B_SRAM & ਪੋਰਟ_MPU_RASR_TEX_S_C_B_ਨਕਾਬ ) << ਪੋਰਟ_MPU_RASR_TEX_S_C_B_LOCATION ) |
                                       prv_Get_MPURegion_ਮਾਪ_Setting( ( uint32_t ) __privileged_data_end__ - ( uint32_t ) __privileged_data_start__ ) |
                                       ( ਪੋਰਟ_MPU_REGION_ENABLE );

        /* By default allow everything to access the general peripherals.  The
         * system peripherals and registers are protected. */
        ਪੋਰਟ_MPU_REGION_ਅਧਾਰ_ਪਤਾ_REG = ( ਪੋਰਟ_PERIPHERALS_ਸ਼ੁਰੂ_ਪਤਾ ) |
                                          ( ਪੋਰਟ_MPU_REGION_VALID ) |
                                          ( ਪੋਰਟ_GENERAL_PERIPHERALS_REGION );

        ਪੋਰਟ_MPU_REGION_ATTRIBUTE_REG = ( ਪੋਰਟ_MPU_REGION_READ_WRITE | ਪੋਰਟ_MPU_REGION_EXECUTE_NEVER ) |
                                       ( prv_Get_MPURegion_ਮਾਪ_Setting( ਪੋਰਟ_PERIPHERALS_ਸਿਰਾ_ਪਤਾ - ਪੋਰਟ_PERIPHERALS_ਸ਼ੁਰੂ_ਪਤਾ ) ) |
                                       ( ਪੋਰਟ_MPU_REGION_ENABLE );

        /* Enable the memory fault exception. */
        ਪੋਰਟ_NVIC_SYS_CTRL_STATE_REG |= ਪੋਰਟ_NVIC_MEM_FAULT_ENABLE;

        /* Enable the MPU with the background region configured. */
        ਪੋਰਟ_MPU_CTRL_REG |= ( ਪੋਰਟ_MPU_ENABLE | ਪੋਰਟ_MPU_BACKGROUND_ENABLE );
    }
}
/*-----------------------------------------------------------*/

ਸਥਿਰ uint32_t prv_Get_MPURegion_ਮਾਪ_Setting( uint32_t ul_Actual_ਮਾਪ_ਵਿੱਚ_ਬਾਈਟਾਂ )
{
    uint32_t ul_Region_ਮਾਪ, ul_Return_ਮੁੱਲ = 4;

    /* 32 is the smallest region size, 31 is the largest valid value for
     * ulReturnValue. */
    ਲਈ( ul_Region_ਮਾਪ = 32UL; ul_Return_ਮੁੱਲ < 31UL; ( ul_Region_ਮਾਪ <<= 1UL ) )
    {
        ਜੇ( ul_Actual_ਮਾਪ_ਵਿੱਚ_ਬਾਈਟਾਂ <= ul_Region_ਮਾਪ )
        {
            ਰੋਕੋ;
        }
        ਨਹੀਂਤਾਂ
        {
            ul_Return_ਮੁੱਲ++;
        }
    }

    /* Shift the code by one before returning so it can be written directly
     * into the correct bit position of the attribute register. */
    ਵਾਪਸ( ul_Return_ਮੁੱਲ << 1UL );
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                ਅਚਲ ਬਣਤਰ x_ਸਮ੍ਰਿਤੀ_REGION * ਅਚਲ xRegions,
                                ਢੇਰ_Type_t * px_Bottom_ਦਾ_ਢੇਰ,
                                config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE ux_ਢੇਰ_ਡੂੰਘਾਈ )
{
    ਬਾਹਰੀ uint32_t __SRAM_segment_start__[];
    ਬਾਹਰੀ uint32_t __SRAM_segment_end__[];
    ਬਾਹਰੀ uint32_t __privileged_data_start__[];
    ਬਾਹਰੀ uint32_t __privileged_data_end__[];
    int32_t l_ਸੂਚਕਾਂਕ;
    uint32_t ul;

    ਜੇ( xRegions == ਨਿਰਾ )
    {
        /* No MPU regions are specified so allow access to all RAM. */
        xMPUSettings->xRegion[ 0 ].ul_Region_ਅਧਾਰ_ਪਤਾ =
            ( ( uint32_t ) __SRAM_segment_start__ ) | /* Base address. */
            ( ਪੋਰਟ_MPU_REGION_VALID ) |
            ( ਪੋਰਟ_ਢੇਰ_REGION );                     /* Region number. */

        xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
            ( ਪੋਰਟ_MPU_REGION_READ_WRITE ) |
            ( ਪੋਰਟ_MPU_REGION_EXECUTE_NEVER ) |
            ( ( configTEX_S_C_B_SRAM & ਪੋਰਟ_MPU_RASR_TEX_S_C_B_ਨਕਾਬ ) << ਪੋਰਟ_MPU_RASR_TEX_S_C_B_LOCATION ) |
            ( prv_Get_MPURegion_ਮਾਪ_Setting( ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__ ) ) |
            ( ਪੋਰਟ_MPU_REGION_ENABLE );

        xMPUSettings->xRegionSettings[ 0 ].ul_Region_ਸ਼ੁਰੂ_ਪਤਾ = ( uint32_t ) __SRAM_segment_start__;
        xMPUSettings->xRegionSettings[ 0 ].ul_Region_ਸਿਰਾ_ਪਤਾ = ( uint32_t ) __SRAM_segment_end__;
        xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                   tskMPU_WRITE_PERMISSION );

        /* Invalidate user configurable regions. */
        ਲਈ( ul = 1UL; ul <= ਪੋਰਟ_ਅੰਕ_CONFIGURABLE_REGIONS; ul++ )
        {
            xMPUSettings->xRegion[ ul ].ul_Region_ਅਧਾਰ_ਪਤਾ = ( ( ul - 1UL ) | ਪੋਰਟ_MPU_REGION_VALID );
            xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ul_Region_ਸ਼ੁਰੂ_ਪਤਾ = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ul_Region_ਸਿਰਾ_ਪਤਾ = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
        }
    }
    ਨਹੀਂਤਾਂ
    {
        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid.  At all other
         * times the stack parameters will not be valid and it is assumed that the
         * stack region has already been configured. */
        ਜੇ( ux_ਢੇਰ_ਡੂੰਘਾਈ > 0 )
        {
            /* Define the region that allows access to the stack. */
            xMPUSettings->xRegion[ 0 ].ul_Region_ਅਧਾਰ_ਪਤਾ =
                ( ( uint32_t ) px_Bottom_ਦਾ_ਢੇਰ ) |
                ( ਪੋਰਟ_MPU_REGION_VALID ) |
                ( ਪੋਰਟ_ਢੇਰ_REGION ); /* Region number. */

            xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
                ( ਪੋਰਟ_MPU_REGION_READ_WRITE ) |
                ( ਪੋਰਟ_MPU_REGION_EXECUTE_NEVER ) |
                ( prv_Get_MPURegion_ਮਾਪ_Setting( ux_ਢੇਰ_ਡੂੰਘਾਈ * ( config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE ) ਆਕਾਰ( ਢੇਰ_Type_t ) ) ) |
                ( ( configTEX_S_C_B_SRAM & ਪੋਰਟ_MPU_RASR_TEX_S_C_B_ਨਕਾਬ ) << ਪੋਰਟ_MPU_RASR_TEX_S_C_B_LOCATION ) |
                ( ਪੋਰਟ_MPU_REGION_ENABLE );

            xMPUSettings->xRegionSettings[ 0 ].ul_Region_ਸ਼ੁਰੂ_ਪਤਾ = ( uint32_t ) px_Bottom_ਦਾ_ਢੇਰ;
            xMPUSettings->xRegionSettings[ 0 ].ul_Region_ਸਿਰਾ_ਪਤਾ = ( uint32_t ) ( ( uint32_t ) ( px_Bottom_ਦਾ_ਢੇਰ ) +
                                                                                   ( ux_ਢੇਰ_ਡੂੰਘਾਈ * ( config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE ) ਆਕਾਰ( ਢੇਰ_Type_t ) ) - 1UL );
            xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                       tskMPU_WRITE_PERMISSION );
        }

        l_ਸੂਚਕਾਂਕ = 0;

        ਲਈ( ul = 1UL; ul <= ਪੋਰਟ_ਅੰਕ_CONFIGURABLE_REGIONS; ul++ )
        {
            ਜੇ( ( xRegions[ l_ਸੂਚਕਾਂਕ ] ).ul_ਲੰਮਾਈ_ਵਿੱਚ_ਬਾਈਟਾਂ > 0UL )
            {
                /* Translate the generic region definition contained in
                 * xRegions into the CM4 specific MPU settings that are then
                 * stored in xMPUSettings. */
                xMPUSettings->xRegion[ ul ].ul_Region_ਅਧਾਰ_ਪਤਾ =
                    ( ( uint32_t ) xRegions[ l_ਸੂਚਕਾਂਕ ].pv_ਅਧਾਰ_ਪਤਾ ) |
                    ( ਪੋਰਟ_MPU_REGION_VALID ) |
                    ( ul - 1UL ); /* Region number. */

                xMPUSettings->xRegion[ ul ].ulRegionAttribute =
                    ( prv_Get_MPURegion_ਮਾਪ_Setting( xRegions[ l_ਸੂਚਕਾਂਕ ].ul_ਲੰਮਾਈ_ਵਿੱਚ_ਬਾਈਟਾਂ ) ) |
                    ( xRegions[ l_ਸੂਚਕਾਂਕ ].ulParameters ) |
                    ( ਪੋਰਟ_MPU_REGION_ENABLE );

                xMPUSettings->xRegionSettings[ ul ].ul_Region_ਸ਼ੁਰੂ_ਪਤਾ = ( uint32_t ) xRegions[ l_ਸੂਚਕਾਂਕ ].pv_ਅਧਾਰ_ਪਤਾ;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_ਸਿਰਾ_ਪਤਾ = ( uint32_t ) ( ( uint32_t ) xRegions[ l_ਸੂਚਕਾਂਕ ].pv_ਅਧਾਰ_ਪਤਾ + xRegions[ l_ਸੂਚਕਾਂਕ ].ul_ਲੰਮਾਈ_ਵਿੱਚ_ਬਾਈਟਾਂ - 1UL );
                xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;

                ਜੇ( ( ( xRegions[ l_ਸੂਚਕਾਂਕ ].ulParameters & ਪੋਰਟ_MPU_REGION_READ_ONLY ) == ਪੋਰਟ_MPU_REGION_READ_ONLY ) ||
                    ( ( xRegions[ l_ਸੂਚਕਾਂਕ ].ulParameters & ਪੋਰਟ_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) == ਪੋਰਟ_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = tskMPU_READ_PERMISSION;
                }

                ਜੇ( ( xRegions[ l_ਸੂਚਕਾਂਕ ].ulParameters & ਪੋਰਟ_MPU_REGION_READ_WRITE ) == ਪੋਰਟ_MPU_REGION_READ_WRITE )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
                }
            }
            ਨਹੀਂਤਾਂ
            {
                /* Invalidate the region. */
                xMPUSettings->xRegion[ ul ].ul_Region_ਅਧਾਰ_ਪਤਾ = ( ( ul - 1UL ) | ਪੋਰਟ_MPU_REGION_VALID );
                xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_ਸ਼ੁਰੂ_ਪਤਾ = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_ਸਿਰਾ_ਪਤਾ = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
            }

            l_ਸੂਚਕਾਂਕ++;
        }
    }
}
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( ਅਚਲ ਖਾਲੀ * pv_ਬਫਰ,
                                                size_t x_ਬਫਰ_ਲੰਮਾਈ,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_ਬਫਰ_ਸ਼ੁਰੂ_ਪਤਾ, ul_ਬਫਰ_ਸਿਰਾ_ਪਤਾ;
        ਅਧਾਰ_Type_t xAccessGranted = pdFALSE;
        ਅਚਲ xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ਨਿਰਾ ); /* Calling task's MPU settings. */

        ਜੇ( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        ਨਹੀਂਤਾਂ ਜੇ( ( xTaskMpuSettings->ulTaskFlags & ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG ) == ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        ਨਹੀਂਤਾਂ
        {
            ਜੇ( ਪੋਰਟ_ਜੋੜੋ_UINT32_WILL_ਉਛਾਲ( ( ( uint32_t ) pv_ਬਫਰ ), ( ( uint32_t ) x_ਬਫਰ_ਲੰਮਾਈ - 1UL ) ) == pdFALSE )
            {
                ul_ਬਫਰ_ਸ਼ੁਰੂ_ਪਤਾ = ( uint32_t ) pv_ਬਫਰ;
                ul_ਬਫਰ_ਸਿਰਾ_ਪਤਾ = ( ( ( uint32_t ) pv_ਬਫਰ ) + ( uint32_t ) x_ਬਫਰ_ਲੰਮਾਈ - 1UL );

                ਲਈ( i = 0; i < ਪੋਰਟ_ਕੁੱਲ_ਅੰਕ_REGIONS_ਵਿੱਚ_TCB; i++ )
                {
                    ਜੇ( ਪੋਰਟ_IS_ਪਤਾ_WITHIN_RANGE( ul_ਬਫਰ_ਸ਼ੁਰੂ_ਪਤਾ,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_ਸ਼ੁਰੂ_ਪਤਾ,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_ਸਿਰਾ_ਪਤਾ ) &&
                        ਪੋਰਟ_IS_ਪਤਾ_WITHIN_RANGE( ul_ਬਫਰ_ਸਿਰਾ_ਪਤਾ,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_ਸ਼ੁਰੂ_ਪਤਾ,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_ਸਿਰਾ_ਪਤਾ ) &&
                        ਪੋਰਟ_IS_AUTHORIZED( ulAccessRequested, xTaskMpuSettings->xRegionSettings[ i ].ulRegionPermissions ) )
                    {
                        xAccessGranted = pdTRUE;
                        ਰੋਕੋ;
                    }
                }
            }
        }

        ਵਾਪਸ xAccessGranted;
    }

#ਜੇ_ਅੰਤ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/


#ਜੇ ( configASSERT_DEFINED == 1 )

    ਖਾਲੀ v_ਪੋਰਟ_Validate_ਰੁਕਾਵਟ_ਤਰਜੀਹ( ਖਾਲੀ )
    {
        uint32_t ul_Current_ਰੁਕਾਵਟ;
        uint8_t uc_Current_ਤਰਜੀਹ;

        /* Obtain the number of the currently executing interrupt. */
        __asm ਅਸਥਿਰ ( "mrs %0, ipsr" : "=r" ( ul_Current_ਰੁਕਾਵਟ )::"memory" );

        /* Is the interrupt number a user defined interrupt? */
        ਜੇ( ul_Current_ਰੁਕਾਵਟ >= ਪੋਰਟ_ਪਹਿਲਾ_USER_ਰੁਕਾਵਟ_ਸੰਖਿਆ )
        {
            /* Look up the interrupt's priority. */
            uc_Current_ਤਰਜੀਹ = pc_ਰੁਕਾਵਟ_ਤਰਜੀਹ_Registers[ ul_Current_ਰੁਕਾਵਟ ];

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
            configASSERT( uc_Current_ਤਰਜੀਹ >= uc_Max_Sys_Call_ਤਰਜੀਹ );
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
        configASSERT( ( ਪੋਰਟ_AIRCR_REG & ਪੋਰਟ_ਤਰਜੀਹ_ਸਮੂਹ_ਨਕਾਬ ) <= ulMaxPRIGROUPValue );
    }

#ਜੇ_ਅੰਤ /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/

#ਜੇ ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    ਖਾਲੀ v_ਪੋਰਟ_Grant_Access_ਮੰਜ਼ਿਲ_Kernel_Object( TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle,
                                         int32_t l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ, ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object / ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );
        ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object % ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );

        xTaskMpuSettings = xTaskGetMPUSettings( x_ਅੰਦਰੂਨੀ_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ ] |= ( 1U << ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ );
    }

#ਜੇ_ਅੰਤ /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#ਜੇ ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    ਖਾਲੀ v_ਪੋਰਟ_Revoke_Access_ਮੰਜ਼ਿਲ_Kernel_Object( TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle,
                                          int32_t l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ, ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object / ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );
        ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object % ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );

        xTaskMpuSettings = xTaskGetMPUSettings( x_ਅੰਦਰੂਨੀ_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ ] &= ~( 1U << ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ );
    }

#ਜੇ_ਅੰਤ /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #ਜੇ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( int32_t l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ, ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ;
            ਅਧਾਰ_Type_t xAccessGranted = pdFALSE;
            ਅਚਲ xMPU_SETTINGS * xTaskMpuSettings;

            ਜੇ( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            ਨਹੀਂਤਾਂ
            {
                xTaskMpuSettings = xTaskGetMPUSettings( ਨਿਰਾ ); /* Calling task's MPU settings. */

                ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object / ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );
                ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object % ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );

                ਜੇ( ( xTaskMpuSettings->ulTaskFlags & ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG ) == ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                ਨਹੀਂਤਾਂ
                {
                    ਜੇ( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ ] & ( 1U << ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            ਵਾਪਸ xAccessGranted;
        }

    #ਨਹੀਂਤਾਂ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( int32_t l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( ਖਾਲੀ ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            ਵਾਪਸ pdTRUE;
        }

    #ਜੇ_ਅੰਤ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#ਜੇ_ਅੰਤ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/
