/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Copyright 2025-2026 Arm Limited and/or its affiliates
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

/* Standard includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers. That should only be done when
 * task.h is included from an application file. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

/* MPU includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "mpu_wrappers.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mpu_syscall_numbers.h"

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_ਰੁਕਾਵਟ_CONTROLLER_ਅਧਾਰ_ਪਤਾ
    #ਗਲਤੀ config_ਰੁਕਾਵਟ_CONTROLLER_ਅਧਾਰ_ਪਤਾ must be defined.  Refer ਮੰਜ਼ਿਲ Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_ਰੁਕਾਵਟ_CONTROLLER_CPU_INTERFACE_ਵਿੱਥ
    #ਗਲਤੀ config_ਰੁਕਾਵਟ_CONTROLLER_CPU_INTERFACE_ਵਿੱਥ must be defined.  Refer ਮੰਜ਼ਿਲ Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES
    #ਗਲਤੀ config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES must be defined.  Refer ਮੰਜ਼ਿਲ Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_ਤਿਆਰੀ_TICK_ਰੁਕਾਵਟ
    #ਗਲਤੀ config_ਤਿਆਰੀ_TICK_ਰੁਕਾਵਟ() must be defined.  Refer ਮੰਜ਼ਿਲ Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#ਜੇ_ਅੰਤ /* configSETUP_TICK_INTERRUPT */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ
    #ਗਲਤੀ config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ must be defined.  Refer ਮੰਜ਼ਿਲ Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#ਜੇ_ਅੰਤ

#ਜੇ config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ == 0
    #ਗਲਤੀ "configMAX_API_CALL_INTERRUPT_PRIORITY must not be set to 0"
#ਜੇ_ਅੰਤ

#ਜੇ config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ > config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES
    #ਗਲਤੀ "configMAX_API_CALL_INTERRUPT_PRIORITY must be less than or equal to configUNIQUE_INTERRUPT_PRIORITIES as the lower the numeric priority value the higher the logical interrupt priority"
#ਜੇ_ਅੰਤ

#ਜੇ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #ਜੇ ( configMAX_PRIORITIES > 32 )
        #ਗਲਤੀ "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 different priorities as tasks that share a priority will time slice."
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#ਜੇ config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ <= ( config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES / 2 )
    #ਗਲਤੀ "configMAX_API_CALL_INTERRUPT_PRIORITY must be greater than ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )"
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_CLEAR_TICK_ਰੁਕਾਵਟ
    #ਗਲਤੀ config_CLEAR_TICK_ਰੁਕਾਵਟ must be defined ਵਿੱਚ_2 FreeRTOSConfig.h ਮੰਜ਼ਿਲ clear which ever ਰੁਕਾਵਟ was ਵਰਤਿਆ ਮੰਜ਼ਿਲ generate the tick ਰੁਕਾਵਟ.
#ਜੇ_ਅੰਤ

#ਜੇ config_ਸੰਖਿਆ_ਦਾ_CORES < 1
    #ਗਲਤੀ config_ਸੰਖਿਆ_ਦਾ_CORES must be ਸੈੱਟ ਮੰਜ਼ਿਲ 1 or greater.  If the application is not using ਗੁਣਜ_2 cores then ਸੈੱਟ config_ਸੰਖਿਆ_ਦਾ_CORES ਮੰਜ਼ਿਲ 1.
#ਜੇ_ਅੰਤ /* configNUMBER_OF_CORES < 1 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configENABLE_MPU
    #ਗਲਤੀ configENABLE_MPU must be defined ਵਿੱਚ_2 FreeRTOSConfig.h. ਸੈੱਟ_2 configENABLE_MPU ਮੰਜ਼ਿਲ 1 ਮੰਜ਼ਿਲ enable the MPU or 0 ਮੰਜ਼ਿਲ disable the MPU.
#ਜੇ_ਅੰਤ /* #if ( configENABLE_MPU == 1 ) */

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 != 0) )
    #ਗਲਤੀ Arm Cortex-R82 ਪੋਰਟ supports only MPU Wrapper V2.
#ਜੇ_ਅੰਤ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 != 0) */

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NO_CRITICAL_NESTING    ( ( size_t ) 0 )

/* Macro to unmask all interrupt priorities. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_PRIORITIES_ਨਕਾਬ()    __asm ਅਸਥਿਰ ( "SVC %0" : : "i" ( ਪੋਰਟ_SVC_UNMASK_ALL_INTERRUPTS ) : "memory" )

/* Macro to unmask all interrupt priorities from EL1. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_PRIORITIES_ਨਕਾਬ_FROM_EL1()  \
{                                                       \
    __asm ਅਸਥਿਰ (                                    \
    " MSR DAIFSET, # 2                 \n"              \
    " DSB SY                           \n"              \
    " ISB SY                           \n"              \
    " MOV X0, %0                       \n"              \
    " MSR ICC_PMR_EL1, X0              \n"              \
    " DSB SY                           \n"              \
    " ISB SY                           \n"              \
    " MSR DAIFCLR, # 2                 \n"              \
    " DSB SY                           \n"              \
    " ISB SY                           \n"              \
    :                                                   \
    : "i" ( ਪੋਰਟ_UNMASK_ਮੁੱਲ )                          \
    );                                                  \
}

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NO_FLOATING_ਬਿੰਦੂ_CONTEXT    ( ( ਢੇਰ_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SP_ELx                       ( ( ਢੇਰ_Type_t ) 0x01 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SP_EL0                       ( ( ਢੇਰ_Type_t ) 0x00 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EL1                          ( ( ਢੇਰ_Type_t ) 0x04 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EL0                          ( ( ਢੇਰ_Type_t ) 0x00 )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_PSTATE_EL0           ( ਪੋਰਟ_EL0 | ਪੋਰਟ_SP_EL0 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_PSTATE_EL1           ( ਪੋਰਟ_EL1 | ਪੋਰਟ_SP_EL0 )

/* Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਬਿੱਟ            ( ( uint8_t ) 0x03 )

/* Masks all bits in the APSR other than the mode bits. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APSR_ਬਹੁਲਕ_ਬਿੱਟ_ਨਕਾਬ          ( 0x0C )

/* The I bit in the DAIF bits. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DAIF_I                       ( 0x80 )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_8_ਦੋਆਧਾਰੀ_ਅੰਕ_ਮੁੱਲ              ( ( uint8_t ) 0xff )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_0_ਸੈੱਟ                    ( ( uint8_t ) 0x01 )

/* The space on the stack required to hold the FPU registers.
 * There are 32 128-bit plus 2 64-bit status registers. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FPU_ਰਜਿਸਟਰ_ਸ਼ਬਦ           ( ( 32 * 2 ) + 2 )

/*-----------------------------------------------------------*/

#ਜੇ ( configENABLE_MPU == 1 )

    /**
     * @brief Setup the Memory Protection Unit (MPU).
     */
    PRIVILEGED_FUNCTION ਖਾਲੀ v_ਤਿਆਰੀ_MPU( ਖਾਲੀ );

    /**
     * @brief Enable the Memory Protection Unit (MPU).
     */
    PRIVILEGED_FUNCTION ਖਾਲੀ vEnableMPU( ਖਾਲੀ );

    /**
     * @brief Called from an ISR and returns the core ID the code is executing on.
     *
     * @return uint8_t The core ID.
     */
    PRIVILEGED_FUNCTION uint8_t uc_ਪੋਰਟ_Get_Core_IDFrom_Isr( ਖਾਲੀ );

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    PRIVILEGED_FUNCTION ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Task_Privileged( ਖਾਲੀ );

    /**
     * @brief Extract MPU region's access permissions from the Protection Region Base Address Register
     * (PRBAR_EL1) value.
     *
     * @param ullPrbarEl1Value PRBAR_EL1 value for the MPU region.
     *
     * @return uint32_t Access permissions.
     */
    PRIVILEGED_FUNCTION ਸਥਿਰ uint32_t prvGetRegionAccessPermissions( uint64_t ull_Prbar_El1_ਮੁੱਲ );

    /**
     * @brief Does the necessary work to enter a system call.
     *
     * @param pullPrivilegedOnlyTaskStack The task's privileged SP when the SVC was raised.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    PRIVILEGED_FUNCTION ਖਾਲੀ vSystemCallEnter( uint64_t * pull_Privileged_Only_Task_ਢੇਰ,
                                               uint8_t uc_System_Call_ਸੰਖਿਆ );

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    PRIVILEGED_FUNCTION __attribute__( ( naked ) ) ਖਾਲੀ vRequestSystemCallExit( ਖਾਲੀ );

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param ullSystemCallReturnValue The actual system call return value.
     */
    PRIVILEGED_FUNCTION ਖਾਲੀ vSystemCallExit( uint64_t ull_System_Call_Return_ਮੁੱਲ );

#ਜੇ_ਅੰਤ /* #if ( configENABLE_MPU == 1 ) */

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Restore_Task_Context( ਖਾਲੀ );
ਬਾਹਰੀ ਖਾਲੀ vGIC_EnableIRQ( uint32_t ul_ਰੁਕਾਵਟ_ID );
ਬਾਹਰੀ ਖਾਲੀ v_GIC_ਸੈੱਟ_ਤਰਜੀਹ( uint32_t ul_ਰੁਕਾਵਟ_ID, uint32_t ul_ਤਰਜੀਹ );
ਬਾਹਰੀ ਖਾਲੀ v_GIC_Power_ਉੱਪਰ_Redistributor( ਖਾਲੀ );
ਬਾਹਰੀ ਖਾਲੀ vGIC_EnableCPUInterface( ਖਾਲੀ );

/*-----------------------------------------------------------*/

#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )

    PRIVILEGED_ਅੰਕੜੇ ਅਸਥਿਰ uint64_t ullCriticalNesting = 0ULL;

    /* Saved as part of the task context. If ullPortTaskHasFPUContext is non-zero
     * then floating point context must be saved and restored for the task. */
    PRIVILEGED_ਅੰਕੜੇ uint64_t ull_ਪੋਰਟ_Task_Has_FPUContext = pdFALSE;

    /* Set to 1 to pend a context switch from an ISR. */
    PRIVILEGED_ਅੰਕੜੇ uint64_t ull_ਪੋਰਟ_Yield_Required = pdFALSE;

    /* Counts the interrupt nesting depth. A context switch is only performed if
     * if the nesting depth is 0. */
    PRIVILEGED_ਅੰਕੜੇ uint64_t ull_ਪੋਰਟ_ਰੁਕਾਵਟ_Nesting = 0;

#ਨਹੀਂਤਾਂ /* #if ( configNUMBER_OF_CORES == 1 ) */
    PRIVILEGED_ਅੰਕੜੇ ਅਸਥਿਰ uint64_t ullCriticalNestings[ config_ਸੰਖਿਆ_ਦਾ_CORES ] = { 0 };

    /* Flags to check if the secondary cores are ready. */
    PRIVILEGED_ਅੰਕੜੇ ਅਸਥਿਰ uint8_t ucSecondaryCoresReadyFlags[ config_ਸੰਖਿਆ_ਦਾ_CORES - 1 ] = { 0 };

    /* Flag to signal that the primary core has done all the shared initialisations. */
    PRIVILEGED_ਅੰਕੜੇ ਅਸਥਿਰ uint8_t uc_Primary_Core_Init_ਪੂਰਾ_Flag = 0;

    /* Saved as part of the task context. If ullPortTaskHasFPUContext is non-zero
     * then floating point context must be saved and restored for the task. */
    PRIVILEGED_ਅੰਕੜੇ uint64_t ull_ਪੋਰਟ_Task_Has_FPUContext[ config_ਸੰਖਿਆ_ਦਾ_CORES ] = { pdFALSE };

    /* Set to 1 to pend a context switch from an ISR. */
    PRIVILEGED_ਅੰਕੜੇ uint64_t ull_ਪੋਰਟ_Yield_Required[ config_ਸੰਖਿਆ_ਦਾ_CORES ] = { pdFALSE };

    /* Counts the interrupt nesting depth. A context switch is only performed if
     * if the nesting depth is 0. */
    PRIVILEGED_ਅੰਕੜੇ uint64_t ull_ਪੋਰਟ_ਰੁਕਾਵਟ_Nestings[ config_ਸੰਖਿਆ_ਦਾ_CORES ] = { 0 };

#ਜੇ_ਅੰਤ /* #if ( configNUMBER_OF_CORES == 1 ) */

#ਜੇ ( configENABLE_MPU == 1 )
    /* Set to pdTRUE when the scheduler is started. */
    PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ ਅਧਾਰ_Type_t xSchedulerRunning = pdFALSE;
#ਜੇ_ਅੰਤ /* ( configENABLE_MPU == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configENABLE_MPU == 1 )

    ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                         TaskFunction_t px_ਕੋਡ,
                                         ਖਾਲੀ * pvParameters,
                                         ਅਧਾਰ_Type_t x_ਲੜੀਵਾਰ_Privileged,
                                         xMPU_SETTINGS * xMPUSettings )
    {
        uint32_t ul_ਸੂਚਕਾਂਕ = 0;

        /* Layout must match portRESTORE_CONTEXT pop order (descending stack):
         * 1) FPU flag, 2) Critical nesting, 3) Optional FPU save area,
         * 4) ELR (PC), 5) SPSR (PSTATE), 6) GPRs in restore order pairs.
         */

        /* 1) FPU flag and 2) Critical nesting. */
        #ਜੇ ( configUSE_TASK_FPU_SUPPORT == ਪੋਰਟ_TASK_NO_FPU_CONTEXT_BY_DEFAULT )
            xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = ਪੋਰਟ_NO_FLOATING_ਬਿੰਦੂ_CONTEXT; /* FPU flag */
            xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = ਪੋਰਟ_NO_CRITICAL_NESTING;       /* Critical nesting */
        #ਜਾਂਜੇ ( configUSE_TASK_FPU_SUPPORT == ਪੋਰਟ_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
            xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = pdTRUE;                        /* FPU flag */
            xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = ਪੋਰਟ_NO_CRITICAL_NESTING;       /* Critical nesting */
            #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
                ull_ਪੋਰਟ_Task_Has_FPUContext = pdTRUE;
            #ਨਹੀਂਤਾਂ
                ull_ਪੋਰਟ_Task_Has_FPUContext[ ਪੋਰਟ_GET_CORE_ID() ] = pdTRUE;
            #ਜੇ_ਅੰਤ
        #ਨਹੀਂਤਾਂ
            #ਗਲਤੀ "Invalid configUSE_TASK_FPU_SUPPORT setting - must be 1 or 2."
        #ਜੇ_ਅੰਤ

        /* 3) Optional FPU save area immediately after the flag+critical pair. */
        #ਜੇ ( configUSE_TASK_FPU_SUPPORT == ਪੋਰਟ_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
            memset( &xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ ], 0x00, ਪੋਰਟ_FPU_ਰਜਿਸਟਰ_ਸ਼ਬਦ * ਆਕਾਰ( ਢੇਰ_Type_t ) );
            ul_ਸੂਚਕਾਂਕ += ਪੋਰਟ_FPU_ਰਜਿਸਟਰ_ਸ਼ਬਦ;
        #ਜੇ_ਅੰਤ

        /* 4) ELR (PC) and 5) SPSR (PSTATE). */
        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = ( ਢੇਰ_Type_t ) px_ਕੋਡ; /* ELR */

        ਜੇ( x_ਲੜੀਵਾਰ_Privileged == pdTRUE )
        {
            xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = ਪੋਰਟ_INITIAL_PSTATE_EL1;    /* SPSR */
        }
        ਨਹੀਂਤਾਂ
        {
            xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = ਪੋਰਟ_INITIAL_PSTATE_EL0;    /* SPSR */
        }

        /* 6) General-purpose registers in the order expected by restoreallgpregisters. */
        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = ( ਢੇਰ_Type_t ) 0x00;         /* X30 (LR) */
        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = ( ਢੇਰ_Type_t ) 0x00;         /* XZR (dummy) */

        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x2828282828282828ULL;        /* X28 */
        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x2929292929292929ULL;        /* X29 */

        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x2626262626262626ULL;        /* X26 */
        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x2727272727272727ULL;        /* X27 */

        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x2424242424242424ULL;        /* X24 */
        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x2525252525252525ULL;        /* X25 */

        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x2222222222222222ULL;        /* X22 */
        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x2323232323232323ULL;        /* X23 */

        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x2020202020202020ULL;        /* X20 */
        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x2121212121212121ULL;        /* X21 */

        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x1818181818181818ULL;        /* X18 */
        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x1919191919191919ULL;        /* X19 */

        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x1616161616161616ULL;        /* X16 */
        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x1717171717171717ULL;        /* X17 */

        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x1414141414141414ULL;        /* X14 */
        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x1515151515151515ULL;        /* X15 */

        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x1212121212121212ULL;        /* X12 */
        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x1313131313131313ULL;        /* X13 */

        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x1010101010101010ULL;        /* X10 */
        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x1111111111111111ULL;        /* X11 */

        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x0808080808080808ULL;        /* X8 */
        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x0909090909090909ULL;        /* X9 */

        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x0606060606060606ULL;        /* X6 */
        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x0707070707070707ULL;        /* X7 */

        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x0404040404040404ULL;        /* X4 */
        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x0505050505050505ULL;        /* X5 */

        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x0202020202020202ULL;        /* X2 */
        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x0303030303030303ULL;        /* X3 */

        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = ( ਢੇਰ_Type_t ) pvParameters; /* X0 */
        xMPUSettings->ullContext[ ul_ਸੂਚਕਾਂਕ++ ] = 0x0101010101010101ULL;        /* X1 */

        ਜੇ( x_ਲੜੀਵਾਰ_Privileged == pdTRUE )
        {
            xMPUSettings->ullTaskFlags |= ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG;
        }
        ਨਹੀਂਤਾਂ
        {
            xMPUSettings->ullTaskFlags &= ( ~ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG );
        }

        xMPUSettings->ullTaskUnprivilegedSP = ( ( uint64_t ) px_ਸਿਖਰ_ਦਾ_ਢੇਰ & ਪੋਰਟ_MPU_PRBAR_EL1_ਪਤਾ_ਨਕਾਬ );

        ਵਾਪਸ &( xMPUSettings->ullContext[ 0 ] );
    }

#ਨਹੀਂਤਾਂ /* #if ( configENABLE_MPU == 1 ) */

    /*
    * See header file for description.
    */
    ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                         TaskFunction_t px_ਕੋਡ,
                                         ਖਾਲੀ * pvParameters )
    {
        /* Setup the initial stack of the task.  The stack is set exactly as
        * expected by the portRESTORE_CONTEXT() macro. */

        /* First all the general purpose registers. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x0101010101010101ULL;        /* R1 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters; /* R0 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x0303030303030303ULL;        /* R3 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x0202020202020202ULL;        /* R2 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x0505050505050505ULL;        /* R5 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x0404040404040404ULL;        /* R4 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x0707070707070707ULL;        /* R7 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x0606060606060606ULL;        /* R6 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x0909090909090909ULL;        /* R9 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x0808080808080808ULL;        /* R8 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x1111111111111111ULL;        /* R11 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x1010101010101010ULL;        /* R10 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x1313131313131313ULL;        /* R13 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x1212121212121212ULL;        /* R12 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x1515151515151515ULL;        /* R15 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x1414141414141414ULL;        /* R14 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x1717171717171717ULL;        /* R17 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x1616161616161616ULL;        /* R16 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x1919191919191919ULL;        /* R19 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x1818181818181818ULL;        /* R18 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x2121212121212121ULL;        /* R21 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x2020202020202020ULL;        /* R20 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x2323232323232323ULL;        /* R23 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x2222222222222222ULL;        /* R22 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x2525252525252525ULL;        /* R25 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x2424242424242424ULL;        /* R24 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x2727272727272727ULL;        /* R27 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x2626262626262626ULL;        /* R26 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x2929292929292929ULL;        /* R29 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x2828282828282828ULL;        /* R28 */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x00;         /* XZR - has no effect, used so there are an even number of registers. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x00;         /* R30 - procedure call link register. */

        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_PSTATE_EL0;

        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ; /* Exception return address. */

        #ਜੇ ( configUSE_TASK_FPU_SUPPORT == ਪੋਰਟ_TASK_NO_FPU_CONTEXT_BY_DEFAULT )
        {
            /* The task will start with a critical nesting count of 0 as interrupts are
            * enabled. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_NO_CRITICAL_NESTING;

            /* The task will start without a floating point context.  A task that
            * uses the floating point hardware must call vPortTaskUsesFPU() before
            * executing any floating point instructions. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_NO_FLOATING_ਬਿੰਦੂ_CONTEXT;
        }
        #ਜਾਂਜੇ ( configUSE_TASK_FPU_SUPPORT == ਪੋਰਟ_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
        {
            /* The task will start with a floating point context.  Leave enough
            * space for the registers - and ensure they are initialised to 0. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= ਪੋਰਟ_FPU_ਰਜਿਸਟਰ_ਸ਼ਬਦ;
            memset( px_ਸਿਖਰ_ਦਾ_ਢੇਰ, 0x00, ਪੋਰਟ_FPU_ਰਜਿਸਟਰ_ਸ਼ਬਦ * ਆਕਾਰ( ਢੇਰ_Type_t ) );

            /* The task will start with a critical nesting count of 0 as interrupts are
            * enabled. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_NO_CRITICAL_NESTING;

            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = pdTRUE;
            #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
            ull_ਪੋਰਟ_Task_Has_FPUContext = pdTRUE;
            #ਨਹੀਂਤਾਂ
            ull_ਪੋਰਟ_Task_Has_FPUContext[ ਪੋਰਟ_GET_CORE_ID() ] = pdTRUE;
            #ਜੇ_ਅੰਤ
        }
        #ਨਹੀਂਤਾਂ /* if ( configUSE_TASK_FPU_SUPPORT == portTASK_NO_FPU_CONTEXT_BY_DEFAULT ) */
        {
            #ਗਲਤੀ "Invalid configUSE_TASK_FPU_SUPPORT setting - configUSE_TASK_FPU_SUPPORT must be set to 1, 2, or left undefined."
        }
        #ਜੇ_ਅੰਤ /* if ( configUSE_TASK_FPU_SUPPORT == portTASK_NO_FPU_CONTEXT_BY_DEFAULT ) */

        ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;

    }

#ਜੇ_ਅੰਤ /* #if ( configENABLE_MPU == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configENABLE_MPU == 1 )

    /**
     * @brief Store a task's MPU settings in its TCB.
     *
     * @ingroup Task Context
     * @ingroup MPU Control
     *
     * @param xMPUSettings The MPU settings in TCB.
     * @param xRegions The MPU regions requested by the task.
     * @param pxBottomOfStack The base address of the task's Stack.
     * @param xStackDepth The length of the task's stack.
     */
    ਖਾਲੀ v_ਪੋਰਟ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ਅਚਲ ਬਣਤਰ x_ਸਮ੍ਰਿਤੀ_REGION * ਅਚਲ xRegions,
                                    ਢੇਰ_Type_t * px_Bottom_ਦਾ_ਢੇਰ,
                                    ਢੇਰ_Type_t x_ਢੇਰ_ਡੂੰਘਾਈ )  /* PRIVILEGED_FUNCTION */
    {
        uint64_t ull_Region_ਸ਼ੁਰੂ_ਪਤਾ, ull_Region_ਸਿਰਾ_ਪਤਾ;
        uint8_t  uc_ਸੂਚਕਾਂਕ = 0, uc_Region_ਸੰਖਿਆ;

        #ਜੇ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ਬਾਹਰੀ uint64_t * __privileged_sram_start__;
            ਬਾਹਰੀ uint64_t * __privileged_sram_end__;
        #ਨਹੀਂਤਾਂ
            /* Declaration when these variable are exported from linker scripts. */
            ਬਾਹਰੀ uint64_t __privileged_sram_start__[];
            ਬਾਹਰੀ uint64_t __privileged_sram_end__[];
        #ਜੇ_ਅੰਤ /* defined( __ARMCC_VERSION ) */

        /* Setup MAIR_EL1. */
        xMPUSettings->ullMairEl1 = ( ( ਪੋਰਟ_MPU_ਸਾਧਾਰਨ_ਸਮ੍ਰਿਤੀ_BUFFERABLE_CACHEABLE << ਪੋਰਟ_MPU_MAIR_EL1_ATTR0_POS ) & ਪੋਰਟ_MPU_MAIR_EL1_ATTR0_ਨਕਾਬ );
        xMPUSettings->ullMairEl1 |= ( ( ਪੋਰਟ_MPU_DEVICE_ਸਮ੍ਰਿਤੀ_n_Gn_RE << ਪੋਰਟ_MPU_MAIR_EL1_ATTR1_POS ) & ਪੋਰਟ_MPU_MAIR_EL1_ATTR1_ਨਕਾਬ );

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid. At all other
         * times the stack parameters will not be valid and it is assumed that
         * the stack region has already been configured. */
        ਜੇ( x_ਢੇਰ_ਡੂੰਘਾਈ > 0 )
        {
            ull_Region_ਸ਼ੁਰੂ_ਪਤਾ = ( uint64_t ) px_Bottom_ਦਾ_ਢੇਰ;
            ull_Region_ਸਿਰਾ_ਪਤਾ = ( uint64_t ) px_Bottom_ਦਾ_ਢੇਰ + ( x_ਢੇਰ_ਡੂੰਘਾਈ * ( config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE ) ਆਕਾਰ( ਢੇਰ_Type_t ) ) - 1;

            /* If the stack is within the privileged SRAM, do not protect it
             * using a separate MPU region. This is needed because this
             * region is already protected using an MPU region and ARMv8-R does
             * not allow overlapping MPU regions.
             */
            ਜੇ( ( ull_Region_ਸ਼ੁਰੂ_ਪਤਾ >= ( uint64_t ) __privileged_sram_start__ ) &&
                ( ull_Region_ਸਿਰਾ_ਪਤਾ <= ( uint64_t ) __privileged_sram_end__ ) )
            {
                xMPUSettings->xRegionsSettings[ ਪੋਰਟ_ਢੇਰ_REGION_ਸੂਚਕਾਂਕ ].ullPrbarEl1 = 0;
                xMPUSettings->xRegionsSettings[ ਪੋਰਟ_ਢੇਰ_REGION_ਸੂਚਕਾਂਕ ].ullPrlarEl1 = 0;
            }
            ਨਹੀਂਤਾਂ
            {
                /* Define the region that allows access to the stack. */
                ull_Region_ਸ਼ੁਰੂ_ਪਤਾ &= ਪੋਰਟ_MPU_PRBAR_EL1_ਪਤਾ_ਨਕਾਬ;
                ull_Region_ਸਿਰਾ_ਪਤਾ &= ਪੋਰਟ_MPU_PRLAR_EL1_ਪਤਾ_ਨਕਾਬ;

                xMPUSettings->xRegionsSettings[ ਪੋਰਟ_ਢੇਰ_REGION_ਸੂਚਕਾਂਕ ].ullPrbarEl1 = ( ull_Region_ਸ਼ੁਰੂ_ਪਤਾ ) |
                                                                                 ( ਪੋਰਟ_MPU_REGION_INNER_SHAREABLE ) |
                                                                                 ( ਪੋਰਟ_MPU_REGION_READ_WRITE ) |
                                                                                 ( ਪੋਰਟ_MPU_REGION_EXECUTE_NEVER );

                xMPUSettings->xRegionsSettings[ ਪੋਰਟ_ਢੇਰ_REGION_ਸੂਚਕਾਂਕ ].ullPrlarEl1 = ( ull_Region_ਸਿਰਾ_ਪਤਾ ) |
                                                                                 ( ਪੋਰਟ_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                                                                                 ( ਪੋਰਟ_MPU_PRLAR_EL1_REGION_ENABLE );
            }
        }

        /* User supplied configurable regions. */
        ਲਈ( uc_Region_ਸੰਖਿਆ = 1; uc_Region_ਸੰਖਿਆ <= ਪੋਰਟ_ਅੰਕ_CONFIGURABLE_REGIONS; uc_Region_ਸੰਖਿਆ++ )
        {
            /* If xRegions is NULL i.e. the task has not specified any MPU
             * region, the else part ensures that all the configurable MPU
             * regions are invalidated.
             * The minimum region size is 64 Bytes.
             */
            ਜੇ( xRegions != ਨਿਰਾ )
            {
                /* Configure the region only if the base address is non-NULL.
                 * The user may choose to use only a subset of the available MPU regions.
                 * This check prevents undefined regions (i.e. regions with a NULL base
                 * address) from being configured and from triggering the size-check
                 * assertion below.
                 */
                ਜੇ ( xRegions[ uc_ਸੂਚਕਾਂਕ ].pv_ਅਧਾਰ_ਪਤਾ != ਨਿਰਾ )
                {
                    configASSERT( xRegions[ uc_ਸੂਚਕਾਂਕ ].ul_ਲੰਮਾਈ_ਵਿੱਚ_ਬਾਈਟਾਂ >= 64UL );

                    uint64_t ull_Prbar_El1_Reg_ਮੁੱਲ, ull_Prlar_El1_Reg_ਮੁੱਲ;

                    /* Translate the generic region definition contained in xRegions
                     * into the ARMv8-R specific MPU settings that are then stored in
                     * xMPUSettings.
                     */
                    ull_Region_ਸ਼ੁਰੂ_ਪਤਾ = ( ( uint64_t ) xRegions[ uc_ਸੂਚਕਾਂਕ ].pv_ਅਧਾਰ_ਪਤਾ ) & ਪੋਰਟ_MPU_PRBAR_EL1_ਪਤਾ_ਨਕਾਬ;
                    ull_Region_ਸਿਰਾ_ਪਤਾ = ( uint64_t ) xRegions[ uc_ਸੂਚਕਾਂਕ ].pv_ਅਧਾਰ_ਪਤਾ + xRegions[ uc_ਸੂਚਕਾਂਕ ].ul_ਲੰਮਾਈ_ਵਿੱਚ_ਬਾਈਟਾਂ - 1;
                    ull_Region_ਸਿਰਾ_ਪਤਾ &= ਪੋਰਟ_MPU_PRLAR_EL1_ਪਤਾ_ਨਕਾਬ;

                    /* Checks for overlaps with another user defined regions and stack region, which are already configured. */
                    ਲਈ( uint8_t uc_User_Region_ਸੰਖਿਆ = 0; uc_User_Region_ਸੰਖਿਆ < ਪੋਰਟ_ਅੰਕ_CONFIGURABLE_REGIONS; uc_User_Region_ਸੰਖਿਆ++ )
                    {
                        /* Check for overlap. */
                        ਜੇ( ( ਪੋਰਟ_IS_ਪਤਾ_WITHIN_RANGE( ull_Region_ਸ਼ੁਰੂ_ਪਤਾ,
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_ਸੰਖਿਆ ].ullPrbarEl1 & ਪੋਰਟ_MPU_PRBAR_EL1_ਪਤਾ_ਨਕਾਬ ),
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_ਸੰਖਿਆ ].ullPrlarEl1 & ਪੋਰਟ_MPU_PRLAR_EL1_ਪਤਾ_ਨਕਾਬ ) ) ||
                            ( ਪੋਰਟ_IS_ਪਤਾ_WITHIN_RANGE( ull_Region_ਸਿਰਾ_ਪਤਾ,
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_ਸੰਖਿਆ ].ullPrbarEl1 & ਪੋਰਟ_MPU_PRBAR_EL1_ਪਤਾ_ਨਕਾਬ ),
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_ਸੰਖਿਆ ].ullPrlarEl1 & ਪੋਰਟ_MPU_PRLAR_EL1_ਪਤਾ_ਨਕਾਬ ) ) ) ) )
                        {
                            /* Overlap detected - assert. */
                            configASSERT( ਨਿਰਾ );
                        }
                    }

                    /* Checks for overlaps with kernel programmed regions which are already programmed as part of vSetupMPU. */
                    ਲਈ (uint8_t uc_Programmed_Region_ਸੂਚਕਾਂਕ = 0; uc_Programmed_Region_ਸੂਚਕਾਂਕ < 4; uc_Programmed_Region_ਸੂਚਕਾਂਕ++)
                    {
                        __asm ਅਸਥਿਰ ( "msr PRSELR_EL1, %0" : : "r" ( ( uint64_t ) uc_Programmed_Region_ਸੂਚਕਾਂਕ ) );

                        __asm ਅਸਥਿਰ ( "mrs %0, PRBAR_EL1" : "=r" ( ull_Prbar_El1_Reg_ਮੁੱਲ ) );
                        ull_Prbar_El1_Reg_ਮੁੱਲ &= ਪੋਰਟ_MPU_PRBAR_EL1_ਪਤਾ_ਨਕਾਬ;

                        __asm ਅਸਥਿਰ ( "mrs %0, PRLAR_EL1" : "=r" ( ull_Prlar_El1_Reg_ਮੁੱਲ ) );
                        ull_Prlar_El1_Reg_ਮੁੱਲ &= ਪੋਰਟ_MPU_PRLAR_EL1_ਪਤਾ_ਨਕਾਬ;

                        /* Check for overlap. */
                        ਜੇ( ( ਪੋਰਟ_IS_ਪਤਾ_WITHIN_RANGE( ull_Region_ਸ਼ੁਰੂ_ਪਤਾ,
                                                        ull_Prbar_El1_Reg_ਮੁੱਲ,
                                                        ull_Prlar_El1_Reg_ਮੁੱਲ ) ) ||
                            ( ਪੋਰਟ_IS_ਪਤਾ_WITHIN_RANGE( ull_Region_ਸਿਰਾ_ਪਤਾ,
                                                        ull_Prbar_El1_Reg_ਮੁੱਲ,
                                                        ull_Prlar_El1_Reg_ਮੁੱਲ ) ) )
                        {
                            /* Overlap detected - assert. */
                            configASSERT( ਨਿਰਾ );
                        }
                    }

                    /* Start address. */
                    xMPUSettings->xRegionsSettings[ uc_Region_ਸੰਖਿਆ ].ullPrbarEl1 = ( ull_Region_ਸ਼ੁਰੂ_ਪਤਾ );

                    /* RO/RW. */
                    ਜੇ( ( xRegions[ uc_ਸੂਚਕਾਂਕ ].ulParameters & tskMPU_REGION_READ_ONLY ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_ਸੰਖਿਆ ].ullPrbarEl1 |= ( ਪੋਰਟ_MPU_REGION_READ_ONLY );
                    }
                    ਨਹੀਂਤਾਂ
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_ਸੰਖਿਆ ].ullPrbarEl1 |= ( ਪੋਰਟ_MPU_REGION_READ_WRITE );
                    }

                    /* XN. */
                    ਜੇ( ( xRegions[ uc_ਸੂਚਕਾਂਕ ].ulParameters & tskMPU_REGION_EXECUTE_NEVER ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_ਸੰਖਿਆ ].ullPrbarEl1 |= ( ਪੋਰਟ_MPU_REGION_EXECUTE_NEVER );
                    }

                    /* SH. */
                    ਜੇ( ( xRegions[ uc_ਸੂਚਕਾਂਕ ].ulParameters & tskMPU_REGION_INNER_SHAREABLE ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_ਸੰਖਿਆ ].ullPrbarEl1 |= ( ਪੋਰਟ_MPU_REGION_INNER_SHAREABLE );
                    }
                    ਨਹੀਂਤਾਂ ਜੇ( ( xRegions[ uc_ਸੂਚਕਾਂਕ ].ulParameters & tskMPU_REGION_OUTER_SHAREABLE ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_ਸੰਖਿਆ ].ullPrbarEl1 |= ( ਪੋਰਟ_MPU_REGION_OUTER_SHAREABLE );
                    }
                    ਨਹੀਂਤਾਂ
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_ਸੰਖਿਆ ].ullPrbarEl1 |= ( ਪੋਰਟ_MPU_REGION_NON_SHAREABLE );
                    }

                    /* End Address. */
                    xMPUSettings->xRegionsSettings[ uc_Region_ਸੰਖਿਆ ].ullPrlarEl1 = ( ull_Region_ਸਿਰਾ_ਪਤਾ ) |
                                                                                ( ਪੋਰਟ_MPU_PRLAR_EL1_REGION_ENABLE );

                    /* Normal memory/ Device memory. */
                    ਜੇ( ( xRegions[ uc_ਸੂਚਕਾਂਕ ].ulParameters & tsk_MPU_REGION_DEVICE_ਸਮ੍ਰਿਤੀ ) != 0 )
                    {
                        /* Attr1 in MAIR_EL1 is configured as device memory. */
                        xMPUSettings->xRegionsSettings[ uc_Region_ਸੰਖਿਆ ].ullPrlarEl1 |= ਪੋਰਟ_MPU_PRLAR_EL1_ATTR_INDEX1;
                    }
                    ਨਹੀਂਤਾਂ
                    {
                        /* Attr0 in MAIR_EL1 is configured as normal memory. */
                        xMPUSettings->xRegionsSettings[ uc_Region_ਸੰਖਿਆ ].ullPrlarEl1 |= ਪੋਰਟ_MPU_PRLAR_EL1_ATTR_INDEX0;
                    }
                }
            }
            ਨਹੀਂਤਾਂ
            {
                /* Invalidate the region. */
                xMPUSettings->xRegionsSettings[ uc_Region_ਸੰਖਿਆ ].ullPrbarEl1 = 0UL;
                xMPUSettings->xRegionsSettings[ uc_Region_ਸੰਖਿਆ ].ullPrlarEl1 = 0UL;
            }

            uc_ਸੂਚਕਾਂਕ++;
        }

    }
    /*-----------------------------------------------------------*/

    ਖਾਲੀ v_ਤਿਆਰੀ_MPU( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
    {
        #ਜੇ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts.
             */
            ਬਾਹਰੀ uint64_t * __privileged_functions_start__;
            ਬਾਹਰੀ uint64_t * __privileged_functions_end__;
            ਬਾਹਰੀ uint64_t * __syscalls_flash_start__;
            ਬਾਹਰੀ uint64_t * __syscalls_flash_end__;
            ਬਾਹਰੀ uint64_t * __unprivileged_flash_start__;
            ਬਾਹਰੀ uint64_t * __unprivileged_flash_end__;
            ਬਾਹਰੀ uint64_t * __privileged_sram_start__;
            ਬਾਹਰੀ uint64_t * __privileged_sram_end__;
        #ਨਹੀਂਤਾਂ /* if defined( __ARMCC_VERSION ) */
            /* Declaration when these variable are exported from linker scripts. */
            ਬਾਹਰੀ uint64_t __privileged_functions_start__[];
            ਬਾਹਰੀ uint64_t __privileged_functions_end__[];
            ਬਾਹਰੀ uint64_t __syscalls_flash_start__[];
            ਬਾਹਰੀ uint64_t __syscalls_flash_end__[];
            ਬਾਹਰੀ uint64_t __unprivileged_flash_start__[];
            ਬਾਹਰੀ uint64_t __unprivileged_flash_end__[];
            ਬਾਹਰੀ uint64_t __privileged_sram_start__[];
            ਬਾਹਰੀ uint64_t __privileged_sram_end__[];
        #ਜੇ_ਅੰਤ /* defined( __ARMCC_VERSION ) */

        /* The only permitted number of regions are 16 or 32. */
        configASSERT( ( config_ਕੁੱਲ_MPU_REGIONS == 16 ) || ( config_ਕੁੱਲ_MPU_REGIONS == 32 ) );

        /* MAIR_EL1 - Index 0. */
        uint64_t ull_Mair_El1_Reg_ਮੁੱਲ = ( ( ਪੋਰਟ_MPU_ਸਾਧਾਰਨ_ਸਮ੍ਰਿਤੀ_BUFFERABLE_CACHEABLE << ਪੋਰਟ_MPU_MAIR_EL1_ATTR0_POS ) & ਪੋਰਟ_MPU_MAIR_EL1_ATTR0_ਨਕਾਬ );
        /* MAIR_EL1 - Index 1. */
        ull_Mair_El1_Reg_ਮੁੱਲ |= ( ( ਪੋਰਟ_MPU_DEVICE_ਸਮ੍ਰਿਤੀ_n_Gn_RE << ਪੋਰਟ_MPU_MAIR_EL1_ATTR1_POS ) & ਪੋਰਟ_MPU_MAIR_EL1_ATTR1_ਨਕਾਬ );

        __asm ਅਸਥਿਰ ( "msr MAIR_EL1, %0" : : "r" ( ull_Mair_El1_Reg_ਮੁੱਲ ) );

        /* Setup privileged flash as Read Only so that privileged tasks can
         * read it but not modify.
         */
        uint64_t ull_Prselr_El1_Reg_ਮੁੱਲ = ਪੋਰਟ_PRIVILEGED_FLASH_REGION;
        __asm ਅਸਥਿਰ ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_ਮੁੱਲ ) );

        uint64_t ull_Prbar_El1_Reg_ਮੁੱਲ = ( ( ( uint64_t ) __privileged_functions_start__ ) & ਪੋਰਟ_MPU_PRBAR_EL1_ਪਤਾ_ਨਕਾਬ ) |
                                       ( ਪੋਰਟ_MPU_REGION_NON_SHAREABLE ) |
                                       ( ਪੋਰਟ_MPU_REGION_PRIVILEGED_READ_ONLY );
        __asm ਅਸਥਿਰ ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_ਮੁੱਲ ) );

        uint64_t ull_Prlar_El1_Reg_ਮੁੱਲ = ( ( ( uint64_t ) __privileged_functions_end__ ) & ਪੋਰਟ_MPU_PRLAR_EL1_ਪਤਾ_ਨਕਾਬ ) |
                                       ( ਪੋਰਟ_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                                       ( ਪੋਰਟ_MPU_PRLAR_EL1_REGION_ENABLE );
        __asm ਅਸਥਿਰ ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_ਮੁੱਲ ) );

        /* Setup unprivileged flash as Read Only by both privileged and
         * unprivileged tasks. All tasks can read it but no-one can modify.
         */
        ull_Prselr_El1_Reg_ਮੁੱਲ = ਪੋਰਟ_UNPRIVILEGED_FLASH_REGION;
        __asm ਅਸਥਿਰ ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_ਮੁੱਲ ) );

        ull_Prbar_El1_Reg_ਮੁੱਲ = ( ( ( uint64_t ) __unprivileged_flash_start__ ) & ਪੋਰਟ_MPU_PRBAR_EL1_ਪਤਾ_ਨਕਾਬ ) |
                              ( ਪੋਰਟ_MPU_REGION_NON_SHAREABLE ) |
                              ( ਪੋਰਟ_MPU_REGION_READ_ONLY );
        __asm ਅਸਥਿਰ ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_ਮੁੱਲ ) );

        ull_Prlar_El1_Reg_ਮੁੱਲ = ( ( ( uint64_t ) __unprivileged_flash_end__ ) & ਪੋਰਟ_MPU_PRLAR_EL1_ਪਤਾ_ਨਕਾਬ ) |
                              ( ਪੋਰਟ_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                              ( ਪੋਰਟ_MPU_PRLAR_EL1_REGION_ENABLE );
        __asm ਅਸਥਿਰ ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_ਮੁੱਲ ) );

        /* Setup unprivileged syscalls flash as Read Only by both privileged
         * and unprivileged tasks. All tasks can read it but no-one can modify.
         */
        ull_Prselr_El1_Reg_ਮੁੱਲ = ਪੋਰਟ_UNPRIVILEGED_SYSCALLS_REGION;
        __asm ਅਸਥਿਰ ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_ਮੁੱਲ ) );

        ull_Prbar_El1_Reg_ਮੁੱਲ = ( ( ( uint64_t ) __syscalls_flash_start__ ) & ਪੋਰਟ_MPU_PRBAR_EL1_ਪਤਾ_ਨਕਾਬ ) |
                              ( ਪੋਰਟ_MPU_REGION_NON_SHAREABLE ) |
                              ( ਪੋਰਟ_MPU_REGION_READ_ONLY );
        __asm ਅਸਥਿਰ ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_ਮੁੱਲ ) );

        ull_Prlar_El1_Reg_ਮੁੱਲ = ( ( ( uint64_t ) __syscalls_flash_end__ ) & ਪੋਰਟ_MPU_PRLAR_EL1_ਪਤਾ_ਨਕਾਬ ) |
                              ( ਪੋਰਟ_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                              ( ਪੋਰਟ_MPU_PRLAR_EL1_REGION_ENABLE );
        __asm ਅਸਥਿਰ ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_ਮੁੱਲ ) );

        /* Setup RAM containing kernel data for privileged access only. */
        ull_Prselr_El1_Reg_ਮੁੱਲ = ਪੋਰਟ_PRIVILEGED_RAM_REGION;
        __asm ਅਸਥਿਰ ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_ਮੁੱਲ ) );

        ull_Prbar_El1_Reg_ਮੁੱਲ = ( ( ( uint64_t ) __privileged_sram_start__ ) & ਪੋਰਟ_MPU_PRBAR_EL1_ਪਤਾ_ਨਕਾਬ ) |
                              ( ਪੋਰਟ_MPU_REGION_INNER_SHAREABLE ) |
                              ( ਪੋਰਟ_MPU_REGION_PRIVILEGED_READ_WRITE ) |
                              ( ਪੋਰਟ_MPU_REGION_EXECUTE_NEVER );
        __asm ਅਸਥਿਰ ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_ਮੁੱਲ ) );

        ull_Prlar_El1_Reg_ਮੁੱਲ = ( ( ( uint64_t ) __privileged_sram_end__ ) & ਪੋਰਟ_MPU_PRLAR_EL1_ਪਤਾ_ਨਕਾਬ ) |
                              ( ਪੋਰਟ_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                              ( ਪੋਰਟ_MPU_PRLAR_EL1_REGION_ENABLE );
        __asm ਅਸਥਿਰ ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_ਮੁੱਲ ) );
    }
    /*-----------------------------------------------------------*/

    ਖਾਲੀ vEnableMPU( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
    {
        uint64_t ull_Sctlr_El1_Reg_ਮੁੱਲ;

        __asm ਅਸਥਿਰ ( "mrs %0, SCTLR_EL1" : "=r" ( ull_Sctlr_El1_Reg_ਮੁੱਲ ) );
        /* Enable the MPU. Also enable privileged access to the
         * background region.
         */
        ull_Sctlr_El1_Reg_ਮੁੱਲ |= ( ਪੋਰਟ_MPU_PRIV_BACKGROUND_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ | ਪੋਰਟ_MPU_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ );
        __asm ਅਸਥਿਰ ( "msr SCTLR_EL1, %0" : : "r" ( ull_Sctlr_El1_Reg_ਮੁੱਲ ) );

        /* Ensure the write to SCTLR_EL1 is committed before
         * returning.
         */
        __asm ਅਸਥਿਰ ( "isb" );
    }
    /*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Task_Privileged( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
    {
        ਅਧਾਰ_Type_t xTaskIsPrivileged = pdFALSE;

        #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
            ਬਾਹਰੀ TaskHandle_t pxCurrentTCB;
            xMPU_SETTINGS * pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );
        #ਨਹੀਂਤਾਂ
            ਬਾਹਰੀ TaskHandle_t pxCurrentTCBs[ config_ਸੰਖਿਆ_ਦਾ_CORES ];
            xMPU_SETTINGS * pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCBs[ ਪੋਰਟ_GET_CORE_ID_FROM_ISR() ] );
        #ਜੇ_ਅੰਤ

        ਜੇ( ( pxMpuSettings->ullTaskFlags & ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG ) == ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        ਵਾਪਸ xTaskIsPrivileged;
    }
    /*-----------------------------------------------------------*/

    ਸਥਿਰ uint32_t prvGetRegionAccessPermissions( uint64_t ull_Prbar_El1_ਮੁੱਲ ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ulAccessPermissions = 0;

        ਜੇ( ( ull_Prbar_El1_ਮੁੱਲ & ਪੋਰਟ_MPU_PRBAR_EL1_ACCESS_PERMISSIONS_ਨਕਾਬ ) == ਪੋਰਟ_MPU_REGION_READ_ONLY )
        {
            ulAccessPermissions = tskMPU_READ_PERMISSION;
        }

        ਜੇ( ( ull_Prbar_El1_ਮੁੱਲ & ਪੋਰਟ_MPU_PRBAR_EL1_ACCESS_PERMISSIONS_ਨਕਾਬ ) == ਪੋਰਟ_MPU_REGION_READ_WRITE )
        {
            ulAccessPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
        }

        ਵਾਪਸ ulAccessPermissions;
    }
    /*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( ਅਚਲ ਖਾਲੀ * pv_ਬਫਰ,
                                                size_t x_ਬਫਰ_ਲੰਮਾਈ,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i;
        uint64_t ull_ਬਫਰ_ਸ਼ੁਰੂ_ਪਤਾ, ull_ਬਫਰ_ਸਿਰਾ_ਪਤਾ;
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
        ਨਹੀਂਤਾਂ ਜੇ( ( xTaskMpuSettings->ullTaskFlags & ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG ) == ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        ਨਹੀਂਤਾਂ
        {
            ਜੇ( ਪੋਰਟ_ਜੋੜੋ_UINT64_WILL_ਉਛਾਲ( ( ( uint64_t ) pv_ਬਫਰ ), ( ( uint64_t ) x_ਬਫਰ_ਲੰਮਾਈ - 1ULL ) ) == pdFALSE )
            {
                ull_ਬਫਰ_ਸ਼ੁਰੂ_ਪਤਾ = ( uint64_t ) pv_ਬਫਰ;
                ull_ਬਫਰ_ਸਿਰਾ_ਪਤਾ = ( ( ( uint64_t ) pv_ਬਫਰ ) + ( uint64_t ) x_ਬਫਰ_ਲੰਮਾਈ - 1ULL );

                ਲਈ( i = 0; i < ਪੋਰਟ_ਕੁੱਲ_ਅੰਕ_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    ਜੇ( ( xTaskMpuSettings->xRegionsSettings[ i ].ullPrlarEl1 & ਪੋਰਟ_MPU_PRLAR_EL1_REGION_ENABLE ) == ਪੋਰਟ_MPU_PRLAR_EL1_REGION_ENABLE )
                    {
                        ਜੇ( ਪੋਰਟ_IS_ਪਤਾ_WITHIN_RANGE( ull_ਬਫਰ_ਸ਼ੁਰੂ_ਪਤਾ,
                                                         ਪੋਰਟ_ਕੱਢੋ_ਪਹਿਲਾ_ਪਤਾ_FROM_PRBAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrbarEl1 ),
                                                         ਪੋਰਟ_ਕੱਢੋ_ਆਖਰੀ_ਪਤਾ_FROM_PRLAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrlarEl1 ) ) &&
                            ਪੋਰਟ_IS_ਪਤਾ_WITHIN_RANGE( ull_ਬਫਰ_ਸਿਰਾ_ਪਤਾ,
                                                         ਪੋਰਟ_ਕੱਢੋ_ਪਹਿਲਾ_ਪਤਾ_FROM_PRBAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrbarEl1 ),
                                                         ਪੋਰਟ_ਕੱਢੋ_ਆਖਰੀ_ਪਤਾ_FROM_PRLAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrlarEl1 ) ) &&
                            ਪੋਰਟ_IS_AUTHORIZED( ulAccessRequested,
                                               prvGetRegionAccessPermissions( xTaskMpuSettings->xRegionsSettings[ i ].ullPrbarEl1 ) ) )
                        {
                            xAccessGranted = pdTRUE;
                            ਰੋਕੋ;
                        }
                    }
                }
            }
        }

        ਵਾਪਸ xAccessGranted;
    }
    /*-----------------------------------------------------------*/

    ਖਾਲੀ vSystemCallEnter( uint64_t * pull_Privileged_Only_Task_ਢੇਰ,
                           uint8_t uc_System_Call_ਸੰਖਿਆ ) /* PRIVILEGED_FUNCTION */
    {
        #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
            ਬਾਹਰੀ TaskHandle_t pxCurrentTCB;
        #ਨਹੀਂਤਾਂ
            ਬਾਹਰੀ TaskHandle_t pxCurrentTCBs[ config_ਸੰਖਿਆ_ਦਾ_CORES ];
        #ਜੇ_ਅੰਤ
        ਬਾਹਰੀ UBaseType_t uxSystemCallImplementations[ ਅੰਕ_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint64_t ullSystemCallLocation;  /* Address where SVC was raised. */
        __asm ਅਸਥਿਰ ( "MRS %0, ELR_EL1" : "=r" ( ullSystemCallLocation ) );

        #ਜੇ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts.
             */
            ਬਾਹਰੀ uint64_t * __syscalls_flash_start__;
            ਬਾਹਰੀ uint64_t * __syscalls_flash_end__;
        #ਨਹੀਂਤਾਂ
            /* Declaration when these variable are exported from linker scripts. */
            ਬਾਹਰੀ uint64_t __syscalls_flash_start__[];
            ਬਾਹਰੀ uint64_t __syscalls_flash_end__[];
        #ਜੇ_ਅੰਤ /* #if defined( __ARMCC_VERSION ) */

        #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );
        #ਨਹੀਂਤਾਂ
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCBs[ ਪੋਰਟ_GET_CORE_ID_FROM_ISR() ] );
        #ਜੇ_ਅੰਤ

        /* Checks:
         * 1. SVC is raised from the system call section (i.e. application is
         *    not raising SVC directly).
         * 2. We do not need to check that ucSystemCallNumber is within range
         *    because the assembly SVC handler checks that before calling
         *    this function.
         */
        ਜੇ( ( ullSystemCallLocation >= ( uint64_t ) __syscalls_flash_start__ ) &&
            ( ullSystemCallLocation <= ( uint64_t ) __syscalls_flash_end__ ) &&
            ( uxSystemCallImplementations[ uc_System_Call_ਸੰਖਿਆ ] != 0 ) )
        {
            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call.
             */
            pxMpuSettings->xSystemCallInfo.ull_Link_ਰਜਿਸਟਰ_At_System_Call_ਇੰਦਰਾਜ = pull_Privileged_Only_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_LR ];

            /* Capture user-mode SP at system call entry. */
            uint64_t ull_User_Sp_At_ਇੰਦਰਾਜ;
            __asm ਅਸਥਿਰ ( "MRS %0, SP_EL0" : "=r" ( ull_User_Sp_At_ਇੰਦਰਾਜ ) );
            pxMpuSettings->xSystemCallInfo.ull_User_SPAt_System_Call_ਇੰਦਰਾਜ = ull_User_Sp_At_ਇੰਦਰਾਜ;

            /* Setup the MPU_<API> inputs, the system call stack, and SPSR. */
            __asm ਅਸਥਿਰ (
                "MOV X0, %0         \n"
                "MOV X1, %1         \n"
                "MOV X2, %2         \n"
                "MOV X3, %3         \n"
                "MSR ELR_EL1, %4    \n"
                "MSR SP_EL0, %5     \n"
                "MSR SPSR_EL1, %6   \n"
                :
                : "r" ( pull_Privileged_Only_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_X0 ] ),
                  "r" ( pull_Privileged_Only_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_X1 ] ),
                  "r" ( pull_Privileged_Only_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_X2 ] ),
                  "r" ( pull_Privileged_Only_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_X3 ] ),
                  "r" ( ( uint64_t ) uxSystemCallImplementations[ uc_System_Call_ਸੰਖਿਆ ] ),
                  "r" ( &( pxMpuSettings->ullContext[ MAX_CONTEXT_ਮਾਪ + config_SYSTEM_CALL_ਢੇਰ_ਮਾਪ ] ) ),
                  "r" ( ਪੋਰਟ_INITIAL_PSTATE_EL1 )
                : "memory", "x0", "x1", "x2", "x3"
            );
        }
    }
    /*-----------------------------------------------------------*/

    ਖਾਲੀ vRequestSystemCallExit( ਖਾਲੀ ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm ਅਸਥਿਰ ( "svc %0 \n" ::"i" ( ਪੋਰਟ_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }
    /*-----------------------------------------------------------*/

    ਖਾਲੀ vSystemCallExit( uint64_t ull_System_Call_Return_ਮੁੱਲ ) /* PRIVILEGED_FUNCTION */
    {
        #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
            ਬਾਹਰੀ TaskHandle_t pxCurrentTCB;
        #ਨਹੀਂਤਾਂ
            ਬਾਹਰੀ TaskHandle_t pxCurrentTCBs[ config_ਸੰਖਿਆ_ਦਾ_CORES ];
        #ਜੇ_ਅੰਤ
        xMPU_SETTINGS * pxMpuSettings;
        uint64_t ullSystemCallLocation; /* Address where SVC was raised. */
        __asm ਅਸਥਿਰ ( "MRS %0, ELR_EL1" : "=r" ( ullSystemCallLocation ) );

        #ਜੇ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ਬਾਹਰੀ uint64_t * __privileged_functions_start__;
            ਬਾਹਰੀ uint64_t * __privileged_functions_end__;
        #ਨਹੀਂਤਾਂ
            /* Declaration when these variable are exported from linker scripts. */
            ਬਾਹਰੀ uint64_t __privileged_functions_start__[];
            ਬਾਹਰੀ uint64_t __privileged_functions_end__[];
        #ਜੇ_ਅੰਤ /* #if defined( __ARMCC_VERSION ) */

        #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );
        #ਨਹੀਂਤਾਂ
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCBs[ ਪੋਰਟ_GET_CORE_ID_FROM_ISR() ] );
        #ਜੇ_ਅੰਤ

        /* Check:
         * SVC is raised from the privileged code (i.e. application is not
         * raising SVC directly). This SVC is only raised from
         * vRequestSystemCallExit which is in the privileged code section.
         */
        ਜੇ( ( ullSystemCallLocation >= ( uint64_t ) __privileged_functions_start__ ) &&
            ( ullSystemCallLocation <= ( uint64_t ) __privileged_functions_end__ ) )
        {
            __asm ਅਸਥਿਰ (
                "MSR ELR_EL1, %0    \n" /* Return to the MPU_<API> caller. */
                "MSR SP_EL0, %1     \n" /* Restore user SP saved at syscall entry. */
                "MSR SPSR_EL1, %3   \n" /* Ensure return to EL0. */
                "MOV X0, %2         \n" /* Move the system call return value to X0. */
                :
                : "r" ( pxMpuSettings->xSystemCallInfo.ull_Link_ਰਜਿਸਟਰ_At_System_Call_ਇੰਦਰਾਜ ),
                  "r" ( pxMpuSettings->xSystemCallInfo.ull_User_SPAt_System_Call_ਇੰਦਰਾਜ ),
                  "r" ( ull_System_Call_Return_ਮੁੱਲ ),
                  "r" ( ( uint64_t ) ਪੋਰਟ_INITIAL_PSTATE_EL0 )
                : "memory"
            );
        }
    }
    /*-----------------------------------------------------------*/

    #ਜੇ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        ਖਾਲੀ v_ਪੋਰਟ_Grant_Access_ਮੰਜ਼ਿਲ_Kernel_Object( TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle,
                                             int32_t l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ, ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ;
            xMPU_SETTINGS * xTaskMpuSettings;

            /* Calculate the Access Control List entry index and bit position
             * within that entry. */
            ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object / ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );
            ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object % ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );

            xTaskMpuSettings = xTaskGetMPUSettings( x_ਅੰਦਰੂਨੀ_Task_Handle );

            /* Set the bit corresponding to the kernel object to grant access. */
            xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ ] |= ( 1U << ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ );
        }
        /*-----------------------------------------------------------*/

        ਖਾਲੀ v_ਪੋਰਟ_Revoke_Access_ਮੰਜ਼ਿਲ_Kernel_Object( TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle,
                                              int32_t l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ, ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ;
            xMPU_SETTINGS * xTaskMpuSettings;

            /* Calculate the Access Control List entry index and bit position
             * within that entry. */
            ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object / ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );
            ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object % ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );

            xTaskMpuSettings = xTaskGetMPUSettings( x_ਅੰਦਰੂਨੀ_Task_Handle );

            /* Clear the bit corresponding to the kernel object to revoke access. */
            xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ ] &= ~( 1U << ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ );
        }
        /*-----------------------------------------------------------*/

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

                ਜੇ( ( xTaskMpuSettings->ullTaskFlags & ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG ) == ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG )
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
        /*-----------------------------------------------------------*/
    #ਨਹੀਂਤਾਂ /* configENABLE_ACCESS_CONTROL_LIST == 1 */

        ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( int32_t l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( ਖਾਲੀ ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            ਵਾਪਸ pdTRUE;
        }
        /*-----------------------------------------------------------*/

    #ਜੇ_ਅੰਤ /* configENABLE_ACCESS_CONTROL_LIST == 1 */

#ਜੇ_ਅੰਤ /* #if ( configENABLE_MPU == 1 ) */

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    uint64_t ullAPSR;

    #ਜੇ ( configASSERT_DEFINED == 1 )
    {
        ਅਸਥਿਰ uint8_t uc_Original_ਤਰਜੀਹ;
        ਅਸਥਿਰ uint8_t * ਅਚਲ puc_ਪਹਿਲਾ_User_ਤਰਜੀਹ_ਰਜਿਸਟਰ = ( ਅਸਥਿਰ uint8_t * ਅਚਲ ) ( config_ਰੁਕਾਵਟ_CONTROLLER_ਅਧਾਰ_ਪਤਾ + ਪੋਰਟ_ਰੁਕਾਵਟ_ਤਰਜੀਹ_ਰਜਿਸਟਰ_ਵਿੱਥ );
        ਅਸਥਿਰ uint8_t uc_Max_ਤਰਜੀਹ_ਮੁੱਲ;

        /* Determine how many priority bits are implemented in the GIC.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_ਤਰਜੀਹ = *puc_ਪਹਿਲਾ_User_ਤਰਜੀਹ_ਰਜਿਸਟਰ;

        /* Determine the number of priority bits available.  First write to
         * all possible bits. */
        *puc_ਪਹਿਲਾ_User_ਤਰਜੀਹ_ਰਜਿਸਟਰ = ਪੋਰਟ_MAX_8_ਦੋਆਧਾਰੀ_ਅੰਕ_ਮੁੱਲ;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ਤਰਜੀਹ_ਮੁੱਲ = *puc_ਪਹਿਲਾ_User_ਤਰਜੀਹ_ਰਜਿਸਟਰ;

        /* Shift to the least significant bits. */
        ਜਦੋਂ( ( uc_Max_ਤਰਜੀਹ_ਮੁੱਲ & ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_0_ਸੈੱਟ ) != ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_0_ਸੈੱਟ )
        {
            uc_Max_ਤਰਜੀਹ_ਮੁੱਲ >>= ( uint8_t ) 0x01;
        }

        /* Sanity check configUNIQUE_INTERRUPT_PRIORITIES matches the read
         * value. */
        configASSERT( uc_Max_ਤਰਜੀਹ_ਮੁੱਲ >= ਪੋਰਟ_ਸਭ_ਤੋਂ_ਨੀਵਾਂ_ਰੁਕਾਵਟ_ਤਰਜੀਹ );


        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_ਪਹਿਲਾ_User_ਤਰਜੀਹ_ਰਜਿਸਟਰ = uc_Original_ਤਰਜੀਹ;
    }
    #ਜੇ_ਅੰਤ /* configASSERT_DEFINED */

    __asm ਅਸਥਿਰ ( "MRS %0, CurrentEL" : "=r" ( ullAPSR ) );
    ullAPSR &= ਪੋਰਟ_APSR_ਬਹੁਲਕ_ਬਿੱਟ_ਨਕਾਬ;

    configASSERT( ullAPSR == ਪੋਰਟ_EL1 );

    #ਜੇ ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        v_ਤਿਆਰੀ_MPU();
    }
    #ਜੇ_ਅੰਤ /* #if ( configENABLE_MPU == 1 ) */

    /* Interrupts are turned off in the CPU itself to ensure a tick does
     * not execute while the scheduler is being started.  Interrupts are
     * automatically turned back on in the CPU when the first task starts
     * executing. */
    __asm ਅਸਥਿਰ ( "MSR DAIFSET, #2\n"
                     "DSB SY\n"
                     "ISB SY\n" ::: "memory" );
    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )
        /* Start the timer that generates the tick ISR. */
        config_ਤਿਆਰੀ_TICK_ਰੁਕਾਵਟ();
        uc_Primary_Core_Init_ਪੂਰਾ_Flag = 1;
        __asm ਅਸਥਿਰ ( "SEV                       \n"
                         "DSB SY                    \n"
                         "ISB SY                    \n"
                         ::: "memory" );
        /* Hold the primary core here until all the secondary cores are ready, this would be achieved only when
         * all elements of ucSecondaryCoresReadyFlags are set.
         */
        ਜਦੋਂ( 1 )
        {
            ਅਧਾਰ_Type_t xAllCoresReady = pdTRUE;
            ਲਈ( uint8_t ucCoreID = 0; ucCoreID < ( config_ਸੰਖਿਆ_ਦਾ_CORES - 1 ); ucCoreID++ )
            {
                ਜੇ( ucSecondaryCoresReadyFlags[ ucCoreID ] != pdTRUE )
                {
                    xAllCoresReady = pdFALSE;
                    ਰੋਕੋ;
                }
            }

            ਜੇ ( xAllCoresReady == pdTRUE )
            {
                ਰੋਕੋ;
            }
        }
    #ਨਹੀਂਤਾਂ /* if ( configNUMBER_OF_CORES > 1 ) */
        /* Start the timer that generates the tick ISR. */
        config_ਤਿਆਰੀ_TICK_ਰੁਕਾਵਟ();
    #ਜੇ_ਅੰਤ /* if ( configNUMBER_OF_CORES > 1 ) */

    #ਜੇ ( configENABLE_MPU == 1 )
        xSchedulerRunning = pdTRUE;

        /* Enable the Memory Protection Unit (MPU)
         * MPU is only enabled after the primary and secondary handshakes
         * are done as to prevent inconsistent MPU regions attributes across
         * different cores resulting in unupdated values of the handshake
         * flags. 
         */
        vEnableMPU();
    #ਜੇ_ਅੰਤ /* #if ( configENABLE_MPU == 1 ) */

    /* Start the first task executing. */
    v_ਪੋਰਟ_Restore_Task_Context();

    ਵਾਪਸ 0;
}

/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
{
    /* Stub implementation for ports where there is nothing to return to
     * Artificially force an assert. */
    configASSERT( ਨਿਰਾ );
}

/*-----------------------------------------------------------*/

#ਜੇ  ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
    PRIVILEGED_FUNCTION ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ )
    {
        /* Mask interrupts up to the max syscall interrupt priority. */
        ux_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ();

        /* Now interrupts are disabled ullCriticalNesting can be accessed
         * directly.  Increment ullCriticalNesting to keep a count of how many times
         * portENTER_CRITICAL() has been called. */
        ullCriticalNesting++;

        /* This is not the interrupt safe version of the enter critical function so
         * assert() if it is being called from an interrupt context.  Only API
         * functions that end in "FromISR" can be used in an interrupt.  Only assert if
         * the critical nesting count is 1 to protect against recursive calls if the
         * assert function also uses a critical section. */
        ਜੇ( ullCriticalNesting == 1ULL )
        {
            configASSERT( ull_ਪੋਰਟ_ਰੁਕਾਵਟ_Nesting == 0 );
        }
    }

/*-----------------------------------------------------------*/

    PRIVILEGED_FUNCTION ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ )
    {
        ਜੇ( ullCriticalNesting > ਪੋਰਟ_NO_CRITICAL_NESTING )
        {
            /* Decrement the nesting count as the critical section is being
             * exited. */
            ullCriticalNesting--;

            /* If the nesting level has reached zero then all interrupt
             * priorities must be re-enabled. */
            ਜੇ( ullCriticalNesting == ਪੋਰਟ_NO_CRITICAL_NESTING )
            {
                /* Critical nesting has reached zero so all interrupt priorities
                 * should be unmasked. */
                ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_PRIORITIES_ਨਕਾਬ();
            }
        }
    }
#ਜੇ_ਅੰਤ /* if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/

ਖਾਲੀ FreeRTOS_Tick_Handler( ਖਾਲੀ )
{
    /* Must be the lowest possible priority. */
    uint64_t ull_Running_ਰੁਕਾਵਟ_ਤਰਜੀਹ;
    __asm ਅਸਥਿਰ ( "MRS %0, ICC_RPR_EL1" : "=r" ( ull_Running_ਰੁਕਾਵਟ_ਤਰਜੀਹ ) );

    configASSERT( ull_Running_ਰੁਕਾਵਟ_ਤਰਜੀਹ == ( ਪੋਰਟ_ਸਭ_ਤੋਂ_ਨੀਵਾਂ_USABLE_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ ) );

    /* Interrupts should not be enabled before this point. */
    #ਜੇ ( configASSERT_DEFINED == 1 )
    {
        uint64_t ull_ਨਕਾਬ_ਬਿੱਟ;

        __asm ਅਸਥਿਰ ( "MRS %0, DAIF" : "=r" ( ull_ਨਕਾਬ_ਬਿੱਟ )::"memory" );
        configASSERT( ( ull_ਨਕਾਬ_ਬਿੱਟ & ਪੋਰਟ_DAIF_I ) != 0 );
    }
    #ਜੇ_ਅੰਤ /* configASSERT_DEFINED */

    /* Set interrupt mask before altering scheduler structures. The tick
     * interrupt runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value.  It is
     * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
     * updated.
     */
    UBaseType_t ux_ਰੁਕਾਵਟ_ਸਥਿਤੀ = ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR();

    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )
        UBaseType_t x = ਪੋਰਟ_ENTER_CRITICAL_FROM_ISR();
    #ਜੇ_ਅੰਤ /* if ( configNUMBER_OF_CORES > 1 ) */

    /* Increment the RTOS tick. */
    ਜੇ( xTaskIncrementTick() != pdFALSE )
    {
        #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
            ull_ਪੋਰਟ_Yield_Required = pdTRUE;
        #ਨਹੀਂਤਾਂ
            ull_ਪੋਰਟ_Yield_Required[ ਪੋਰਟ_GET_CORE_ID_FROM_ISR() ] = pdTRUE;
        #ਜੇ_ਅੰਤ
    }
    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )
        ਪੋਰਟ_EXIT_CRITICAL_FROM_ISR(x);
    #ਜੇ_ਅੰਤ /* if ( configNUMBER_OF_CORES > 1 ) */

    /* Ensure all interrupt priorities are active again. */
    ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( ux_ਰੁਕਾਵਟ_ਸਥਿਤੀ );

    /* Ok to enable interrupts after the interrupt source has been cleared. */
    config_CLEAR_TICK_ਰੁਕਾਵਟ();
}

/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TASK_FPU_SUPPORT == ਪੋਰਟ_TASK_NO_FPU_CONTEXT_BY_DEFAULT )

    ਖਾਲੀ v_ਪੋਰਟ_Task_ਵਰਤਦਾ_FPU( ਖਾਲੀ )
    {
        /* A task is registering the fact that it needs an FPU context.  Set the
         * FPU flag (which is saved as part of the task context). */
        #ਜੇ  ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
            ull_ਪੋਰਟ_Task_Has_FPUContext = pdTRUE;
        #ਨਹੀਂਤਾਂ
            ull_ਪੋਰਟ_Task_Has_FPUContext[ ਪੋਰਟ_GET_CORE_ID() ] = pdTRUE;
        #ਜੇ_ਅੰਤ

        /* Consider initialising the FPSR here - but probably not necessary in
         * AArch64. */
    }

#ਜੇ_ਅੰਤ /* configUSE_TASK_FPU_SUPPORT */

/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ( UBaseType_t ux_New_ਨਕਾਬ_ਮੁੱਲ )
{
    ਜੇ( ux_New_ਨਕਾਬ_ਮੁੱਲ == ਪੋਰਟ_UNMASK_ਮੁੱਲ )
    {
        /* Unmask all interrupt priorities. */
        ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_PRIORITIES_ਨਕਾਬ();
    }
    ਨਹੀਂਤਾਂ
    {
        __asm ਅਸਥਿਰ (
            "SVC %0 \n"
            :
            : "i" ( ਪੋਰਟ_SVC_UNMASK_INTERRUPTS )
            : "memory"
        );
    }
}

ਖਾਲੀ v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR( UBaseType_t ux_New_ਨਕਾਬ_ਮੁੱਲ )
{
    __asm ਅਸਥਿਰ (
        "MSR DAIFSET, #2        \n"
        "DSB SY                 \n"
        "ISB SY                 \n"
        "MSR ICC_PMR_EL1, %0    \n"
        "DSB SY                 \n"
        "ISB SY                 \n"
        "MSR DAIFCLR, #2        \n"
        "DSB SY                 \n"
        "ISB SY                 \n"
        :
        : "r" ( ux_New_ਨਕਾਬ_ਮੁੱਲ )
    );
}
/*-----------------------------------------------------------*/

UBaseType_t ux_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ( ਖਾਲੀ )
{
    UBaseType_t ullPMRValue;

    /* Use SVC so this can be called safely from EL0 tasks. */
    __asm ਅਸਥਿਰ (
        "svc %1        \n"
        "mov %0, x0    \n"
        : "=r" ( ullPMRValue )
        : "i" ( ਪੋਰਟ_SVC_ਨਕਾਬ_ALL_INTERRUPTS )
        : "x0", "memory"
    );

    ਵਾਪਸ ullPMRValue;
}

/* EL1/ISR variant to avoid SVC from interrupt context. */
UBaseType_t ux_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR( ਖਾਲੀ )
{
    UBaseType_t ullPMRValue;

    __asm ਅਸਥਿਰ ( "MRS %0, ICC_PMR_EL1" : "=r" ( ullPMRValue ) );

    ਜੇ( ullPMRValue != ( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ ) )
    {
        __asm ਅਸਥਿਰ ( "MSR DAIFSET, #2        \n"
                         "DSB SY                 \n"
                         "ISB SY                 \n"
                         "MSR ICC_PMR_EL1, %0    \n"
                         "DSB SY                 \n"
                         "ISB SY                 \n"
                         "MSR DAIFCLR, #2        \n"
                         "DSB SY                 \n"
                         "ISB SY                 \n"
                         ::"r" ( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ ) : "memory" );
    }

    ਵਾਪਸ ullPMRValue;
}

/*-----------------------------------------------------------*/

#ਜੇ ( configASSERT_DEFINED == 1 )

    ਖਾਲੀ v_ਪੋਰਟ_Validate_ਰੁਕਾਵਟ_ਤਰਜੀਹ( ਖਾਲੀ )
    {
        /* The following assertion will fail if a service routine (ISR) for
         * an interrupt that has been assigned a priority above
         * configMAX_SYSCALL_INTERRUPT_PRIORITY calls an ISR safe FreeRTOS API
         * function. ISR safe FreeRTOS API functions must *only* be called
         * from interrupts that have been assigned a priority at or below
         * configMAX_SYSCALL_INTERRUPT_PRIORITY.
         *
         * Numerically low interrupt priority numbers represent logically high
         * interrupt priorities, therefore the priority of the interrupt must
         * be set to a value equal to or numerically *higher* than
         * configMAX_SYSCALL_INTERRUPT_PRIORITY.
         *
         * FreeRTOS maintains separate thread and ISR API functions to ensure
         * interrupt entry is as fast and simple as possible. */
        uint64_t ull_Running_ਰੁਕਾਵਟ_ਤਰਜੀਹ;
        __asm ਅਸਥਿਰ ( "MRS %0, ICC_RPR_EL1" : "=r" ( ull_Running_ਰੁਕਾਵਟ_ਤਰਜੀਹ ) );
        configASSERT( ull_Running_ਰੁਕਾਵਟ_ਤਰਜੀਹ >= ( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ ) );
    }

#ਜੇ_ਅੰਤ /* configASSERT_DEFINED */

/*-----------------------------------------------------------*/

/*
 * If the application provides an implementation of vApplicationIRQHandler(),
 * then it will get called directly without saving the FPU registers on
 * interrupt entry, and this weak implementation of
 * vApplicationFPUSafeIRQHandler() is just provided to remove linkage errors -
 * it should never actually get called so its implementation contains a
 * call to configASSERT() that will always fail.
 *
 * If the application provides its own implementation of
 * vApplicationFPUSafeIRQHandler() then the implementation of
 * vApplicationIRQHandler() provided in portASM.S will save the FPU registers
 * before calling it.
 *
 * Therefore, if the application writer wants FPU registers to be saved on
 * interrupt entry their IRQ handler must be called
 * vApplicationFPUSafeIRQHandler(), and if the application writer does not want
 * FPU registers to be saved on interrupt entry their IRQ handler must be
 * called vApplicationIRQHandler().
 */
 __attribute__( ( weak ) ) ਖਾਲੀ vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR )
{
    ( ਖਾਲੀ ) ulICCIAR;
    configASSERT( ( ਅਸਥਿਰ ਖਾਲੀ * ) ਨਿਰਾ );
}

/*-----------------------------------------------------------*/

#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )

    /* Which core owns the lock? Keep in privileged, shareable RAM. */
    PRIVILEGED_ਅੰਕੜੇ ਅਸਥਿਰ uint64_t ullOwnedByCore[ ਪੋਰਟ_MAX_CORE_ਗਿਣਤੀ ];
    /* Lock count a core owns. */
    PRIVILEGED_ਅੰਕੜੇ ਅਸਥਿਰ uint64_t ull_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ e_ਤਾਲਾ_ਗਿਣਤੀ ];
    /* Index 0 is used for ISR lock and Index 1 is used for task lock. */
    PRIVILEGED_ਅੰਕੜੇ uint32_t ul_Gate_ਸ਼ਬਦ[ e_ਤਾਲਾ_ਗਿਣਤੀ ];

    ਖਾਲੀ v_ਰੁਕਾਵਟ_Core( uint32_t ul_ਰੁਕਾਵਟ_ID, uint8_t ucCoreID )
    {
        uint64_t ulRegVal = 0;
        uint32_t ul_Core_ਨਕਾਬ = ( 1UL << ucCoreID );
        ulRegVal |= ( (ul_Core_ਨਕਾਬ & 0xFFFF) | ( ( ul_ਰੁਕਾਵਟ_ID & 0xF ) << 24U ) );
        __asm ਅਸਥਿਰ (
            "str  x0, [ sp, #-0x10 ]!       \n"
            "mov  x0, %0                    \n"
            "svc  %1                        \n"
            "ldr  x0, [ sp ], # 0x10        \n"
            :
            : "r" ( ulRegVal ), "i" ( ਪੋਰਟ_SVC_ਰੁਕਾਵਟ_CORE )
            : "memory", "w1"
        );
    }

/*-----------------------------------------------------------*/

    ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ prvSpinUnlock( uint32_t * ul_ਤਾਲਾ )
    {
        /* Conservative unlock: preserve original barriers for broad HW/FVP. */
        __asm ਅਸਥਿਰ (
            "dmb sy         \n"
            "mov w1, #0     \n"
            "str w1, [%x0]  \n"
            "sev            \n"
            "dsb sy         \n"
            "isb sy         \n"
            :
            : "r" ( ul_ਤਾਲਾ )
            : "memory", "w1"
        );
    }

/*-----------------------------------------------------------*/

    ਸਥਿਰ ਸਤਰਅੰਦਰ uint32_t prvSpinTrylock( uint32_t * ul_ਤਾਲਾ )
    {
        /*
         * Conservative LDXR/STXR trylock:
         * - Return 1 immediately if busy, clearing exclusive state (CLREX).
         * - Retry STXR only on spurious failure when observed free.
         * - DMB on success to preserve expected acquire semantics.
         */
        ਰਜਿਸਟਰ uint32_t ulRet;
        __asm ਅਸਥਿਰ (
            "1:                     \n"
            "ldxr w1, [%x1]         \n"
            "cbnz w1, 2f            \n" /* Busy -> return 1 */
            "mov  w2, #1            \n"
            "stxr w3, w2, [%x1]     \n" /* w3 = status */
            "cbnz w3, 1b            \n" /* Retry on STXR failure */
            "dmb  sy                \n" /* Acquire barrier on success */
            "mov %w0, #0            \n" /* Success */
            "b    3f                \n"
            "2:                     \n"
            "clrex                  \n" /* Clear monitor when busy */
            "mov %w0, #1            \n" /* Busy */
            "3:                     \n"
            : "=r" ( ulRet )
            : "r" ( ul_ਤਾਲਾ )
            : "memory", "w1", "w2", "w3"
        );

        ਵਾਪਸ ulRet;
    }

/*-----------------------------------------------------------*/

    /* Read 64b value shared between cores. */
    ਸਥਿਰ ਸਤਰਅੰਦਰ uint64_t prvGet64( ਅਸਥਿਰ uint64_t * x )
    {
        __asm( "dsb sy" );
        ਵਾਪਸ *x;
    }

/*-----------------------------------------------------------*/

    /* Write 64b value shared between cores. */
    ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ prvSet64( ਅਸਥਿਰ uint64_t * x,
                                 uint64_t ਮੁੱਲ )
    {
        *x = ਮੁੱਲ;
        __asm( "dsb sy" );
    }

/*-----------------------------------------------------------*/

    ਖਾਲੀ v_ਪੋਰਟ_Recursive_ਤਾਲਾ( uint8_t ucCoreID,
                             e_ਪੋਰਟ_RTOSLock e_ਤਾਲਾ_ਅੰਕ,
                             ਅਧਾਰ_Type_t uxAcquire )
    {
        /* Validate the core ID and lock number. */
        configASSERT( ucCoreID < ਪੋਰਟ_MAX_CORE_ਗਿਣਤੀ );
        configASSERT( e_ਤਾਲਾ_ਅੰਕ < e_ਤਾਲਾ_ਗਿਣਤੀ );

        uint32_t ul_ਤਾਲਾ_ਦੋਆਧਾਰੀ_ਅੰਕ = 1u << e_ਤਾਲਾ_ਅੰਕ;

        /* Lock acquire */
        ਜੇ( uxAcquire )
        {
            /* Check if spinlock is available.
             * If spinlock is not available check if the core owns the lock.
             * If the core owns the lock wait increment the lock count by the core.
             * If core does not own the lock wait for the spinlock.
             */
            ਜੇ( prvSpinTrylock( &ul_Gate_ਸ਼ਬਦ[ e_ਤਾਲਾ_ਅੰਕ ] ) != 0 )
            {
                /* Check if the core owns the spinlock. */
                ਜੇ( prvGet64( &ullOwnedByCore[ ucCoreID ] ) & ul_ਤਾਲਾ_ਦੋਆਧਾਰੀ_ਅੰਕ )
                {
                    configASSERT( prvGet64( &ull_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ e_ਤਾਲਾ_ਅੰਕ ] ) != 255u );
                    prvSet64( &ull_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ e_ਤਾਲਾ_ਅੰਕ ], ( prvGet64( &ull_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ e_ਤਾਲਾ_ਅੰਕ ] ) + 1 ) );
                    ਵਾਪਸ;
                }

                /* Preload the gate word into the cache. */
                uint32_t dummy = ul_Gate_ਸ਼ਬਦ[ e_ਤਾਲਾ_ਅੰਕ ];
                dummy++;

                ਜਦੋਂ( prvSpinTrylock( &ul_Gate_ਸ਼ਬਦ[ e_ਤਾਲਾ_ਅੰਕ ] ) != 0 )
                {
                   /* Follow Arm's recommended way of sleeping
                    * sevl is used to prime the wait loop.
                    * The first wfe wakes immediately because sevl has set the flag.
                    * Check the lock, if it's not available, issue a second wfe to sleep.
                    * This guarantees the core actually goes to sleep.
                    */
                    __asm ਅਸਥਿਰ (
                        "sevl            \n"
                        "1: wfe          \n"
                        "ldr w2, [%x0]   \n"
                        "cbnz w2, 1b     \n"
                        :
                        : "r" ( &ul_Gate_ਸ਼ਬਦ[ e_ਤਾਲਾ_ਅੰਕ ] )
                        : "memory", "w2"
                    );
                }
            }

            /* Add barrier to ensure lock is taken before we proceed. */
            __asm__ __volatile__ ( "dmb sy" ::: "memory" );

            /* Assert the lock count is 0 when the spinlock is free and is acquired. */
            configASSERT( prvGet64( &ull_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ e_ਤਾਲਾ_ਅੰਕ ] ) == 0 );

            /* Set lock count as 1. */
            prvSet64( &ull_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ e_ਤਾਲਾ_ਅੰਕ ], 1 );
            /* Set ullOwnedByCore. */
            prvSet64( &ullOwnedByCore[ ucCoreID ], ( prvGet64( &ullOwnedByCore[ ucCoreID ] ) | ul_ਤਾਲਾ_ਦੋਆਧਾਰੀ_ਅੰਕ ) );
        }
        /* Lock release. */
        ਨਹੀਂਤਾਂ
        {
            /* Assert the lock is not free already. */
            configASSERT( ( prvGet64( &ullOwnedByCore[ ucCoreID ] ) & ul_ਤਾਲਾ_ਦੋਆਧਾਰੀ_ਅੰਕ ) != 0 );
            configASSERT( prvGet64( &ull_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ e_ਤਾਲਾ_ਅੰਕ ] ) != 0 );

            /* Reduce ullRecursionCountByLock by 1. */
            prvSet64( &ull_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ e_ਤਾਲਾ_ਅੰਕ ], ( prvGet64( &ull_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ e_ਤਾਲਾ_ਅੰਕ ] ) - 1 ) );

            ਜੇ( !prvGet64( &ull_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ e_ਤਾਲਾ_ਅੰਕ ] ) )
            {
                prvSet64( &ullOwnedByCore[ ucCoreID ], ( prvGet64( &ullOwnedByCore[ ucCoreID ] ) & ~ul_ਤਾਲਾ_ਦੋਆਧਾਰੀ_ਅੰਕ ) );
                prvSpinUnlock( &ul_Gate_ਸ਼ਬਦ[ e_ਤਾਲਾ_ਅੰਕ ] );
                /* Add barrier to ensure lock status is reflected before we proceed. */
                __asm__ __volatile__ ( "dmb sy" ::: "memory" );
            }
        }
    }

/*-----------------------------------------------------------*/

    uint8_t uc_ਪੋਰਟ_Get_Core_ID( ਖਾਲੀ )
    {
        /* Use SVC to obtain the core ID in a way that is safe when called
         * from EL0 tasks. ISRs and EL1 code should use
         * ucPortGetCoreIDFromIsr()/portGET_CORE_ID_FROM_ISR().
         */
        uint8_t ucCoreID;
        __asm ਅਸਥਿਰ (
            "svc %1             \n"
            "mov %w0, w0        \n"
            : "=r" ( ucCoreID )
            : "i" ( ਪੋਰਟ_SVC_GET_CORE_ID )
            : "x0", "memory"
        );
        ਵਾਪਸ ucCoreID;
    }

/*-----------------------------------------------------------*/

    uint8_t uc_ਪੋਰਟ_Get_Core_IDFrom_Isr ( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
    {
        uint64_t ullMpidrEl1;
        __asm ਅਸਥਿਰ ( "MRS %0, MPIDR_EL1" : "=r" ( ullMpidrEl1 ) );

        ਵਾਪਸ ( uint8_t ) ( ullMpidrEl1 & 0xff );
    }

/*------------------------------------------------------------*/
    ਖਾਲੀ FreeRTOS_SGI_Handler( ਖਾਲੀ )
    {
        /* Must be the lowest possible priority. */
        uint64_t ull_Running_ਰੁਕਾਵਟ_ਤਰਜੀਹ;
        __asm ਅਸਥਿਰ ( "MRS %0, ICC_RPR_EL1" : "=r" ( ull_Running_ਰੁਕਾਵਟ_ਤਰਜੀਹ ) );

        configASSERT( ull_Running_ਰੁਕਾਵਟ_ਤਰਜੀਹ == ( ਪੋਰਟ_ਸਭ_ਤੋਂ_ਨੀਵਾਂ_USABLE_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ ) );
        /* Interrupts should not be enabled before this point. */
        #ਜੇ ( configASSERT_DEFINED == 1 )
        {
            uint64_t ull_ਨਕਾਬ_ਬਿੱਟ;

            __asm ਅਸਥਿਰ ( "mrs %0, DAIF" : "=r" ( ull_ਨਕਾਬ_ਬਿੱਟ )::"memory" );
            configASSERT( ( ull_ਨਕਾਬ_ਬਿੱਟ & ਪੋਰਟ_DAIF_I ) != 0 );
        }
        #ਜੇ_ਅੰਤ /* configASSERT_DEFINED */

        /* Set interrupt mask before altering scheduler structures. The SGI
         * interrupt runs at the lowest priority, so interrupts cannot already be masked,
         * so there is no need to save and restore the current mask value.  It is
         * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
         * updated.
         */
        UBaseType_t ux_ਰੁਕਾਵਟ_ਸਥਿਤੀ = ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR();

        UBaseType_t ux_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ = ਪੋਰਟ_ENTER_CRITICAL_FROM_ISR();
        #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
            ull_ਪੋਰਟ_Yield_Required = pdTRUE;
        #ਨਹੀਂਤਾਂ
            ull_ਪੋਰਟ_Yield_Required[ ਪੋਰਟ_GET_CORE_ID_FROM_ISR() ] = pdTRUE;
        #ਜੇ_ਅੰਤ
        ਪੋਰਟ_EXIT_CRITICAL_FROM_ISR( ux_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ );
        ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( ux_ਰੁਕਾਵਟ_ਸਥਿਤੀ );
    }

/*-----------------------------------------------------------*/

#ਜੇ_ਅੰਤ /* if( configNUMBER_OF_CORES > 1 ) */
