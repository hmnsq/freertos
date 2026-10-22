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
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers. That should only be done when
 * task.h is included from an application file. */
#ವ್ಯಾಖ್ಯಾನಿಸು MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* MPU includes. */
#ಅನ್ತರ್ಭಾವ "mpu_wrappers.h"
#ಅನ್ತರ್ಭಾವ "mpu_syscall_numbers.h"

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_ಅಡಚಣೆ_CONTROLLER_ತಳ_ವಿಳಾಸ
    #ದೋಷ config_ಅಡಚಣೆ_CONTROLLER_ತಳ_ವಿಳಾಸ must be defined.  Refer ಗಮ್ಯ Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_ಅಡಚಣೆ_CONTROLLER_CPU_INTERFACE_ಸ್ಥಾನಾಂತರ
    #ದೋಷ config_ಅಡಚಣೆ_CONTROLLER_CPU_INTERFACE_ಸ್ಥಾನಾಂತರ must be defined.  Refer ಗಮ್ಯ Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_UNIQUE_ಅಡಚಣೆ_PRIORITIES
    #ದೋಷ config_UNIQUE_ಅಡಚಣೆ_PRIORITIES must be defined.  Refer ಗಮ್ಯ Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_ಸಿದ್ಧತೆ_TICK_ಅಡಚಣೆ
    #ದೋಷ config_ಸಿದ್ಧತೆ_TICK_ಅಡಚಣೆ() must be defined.  Refer ಗಮ್ಯ Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#ಆದರೆ_ಅಂತ್ಯ /* configSETUP_TICK_INTERRUPT */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ
    #ದೋಷ config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ must be defined.  Refer ಗಮ್ಯ Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ == 0
    #ದೋಷ "configMAX_API_CALL_INTERRUPT_PRIORITY must not be set to 0"
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ > config_UNIQUE_ಅಡಚಣೆ_PRIORITIES
    #ದೋಷ "configMAX_API_CALL_INTERRUPT_PRIORITY must be less than or equal to configUNIQUE_INTERRUPT_PRIORITIES as the lower the numeric priority value the higher the logical interrupt priority"
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #ಆದರೆ ( configMAX_PRIORITIES > 32 )
        #ದೋಷ "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 different priorities as tasks that share a priority will time slice."
    #ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#ಆದರೆ config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ <= ( config_UNIQUE_ಅಡಚಣೆ_PRIORITIES / 2 )
    #ದೋಷ "configMAX_API_CALL_INTERRUPT_PRIORITY must be greater than ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )"
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_CLEAR_TICK_ಅಡಚಣೆ
    #ದೋಷ config_CLEAR_TICK_ಅಡಚಣೆ must be defined ಒಳ FreeRTOSConfig.h ಗಮ್ಯ clear which ever ಅಡಚಣೆ was ಬಳಸಿದ ಗಮ್ಯ generate the tick ಅಡಚಣೆ.
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ config_ಸಂಖ್ಯೆ_ದ_CORES < 1
    #ದೋಷ config_ಸಂಖ್ಯೆ_ದ_CORES must be ಗಣ ಗಮ್ಯ 1 or greater.  If the application is not using ಅಪವರ್ತ್ಯ_2 cores then ಗಣ config_ಸಂಖ್ಯೆ_ದ_CORES ಗಮ್ಯ 1.
#ಆದರೆ_ಅಂತ್ಯ /* configNUMBER_OF_CORES < 1 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configENABLE_MPU
    #ದೋಷ configENABLE_MPU must be defined ಒಳ FreeRTOSConfig.h. ಗಣ_2 configENABLE_MPU ಗಮ್ಯ 1 ಗಮ್ಯ enable the MPU or 0 ಗಮ್ಯ disable the MPU.
#ಆದರೆ_ಅಂತ್ಯ /* #if ( configENABLE_MPU == 1 ) */

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 != 0) )
    #ದೋಷ Arm Cortex-R82 ಪೋರ್ಟ್ supports only MPU Wrapper V2.
#ಆದರೆ_ಅಂತ್ಯ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 != 0) */

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_CRITICAL_NESTING    ( ( size_t ) 0 )

/* Macro to unmask all interrupt priorities. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_PRIORITIES_ಮುಖವಾಡ()    __asm ಅಸ್ಥಿರ ( "SVC %0" : : "i" ( ಪೋರ್ಟ್_SVC_UNMASK_ALL_INTERRUPTS ) : "memory" )

/* Macro to unmask all interrupt priorities from EL1. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_PRIORITIES_ಮುಖವಾಡ_FROM_EL1()  \
{                                                       \
    __asm ಅಸ್ಥಿರ (                                    \
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
    : "i" ( ಪೋರ್ಟ್_UNMASK_ಮೌಲ್ಯ )                          \
    );                                                  \
}

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_FLOATING_ಬಿಂದು_CONTEXT    ( ( ರಾಶಿ_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SP_ELx                       ( ( ರಾಶಿ_Type_t ) 0x01 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SP_EL0                       ( ( ರಾಶಿ_Type_t ) 0x00 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EL1                          ( ( ರಾಶಿ_Type_t ) 0x04 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EL0                          ( ( ರಾಶಿ_Type_t ) 0x00 )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_PSTATE_EL0           ( ಪೋರ್ಟ್_EL0 | ಪೋರ್ಟ್_SP_EL0 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_PSTATE_EL1           ( ಪೋರ್ಟ್_EL1 | ಪೋರ್ಟ್_SP_EL0 )

/* Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ದ್ವಿಮಾನ_ಬಿಂದು_ಬಿಟ್ಟುಗಳು            ( ( uint8_t ) 0x03 )

/* Masks all bits in the APSR other than the mode bits. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APSR_ಬಹುಲಕ_ಬಿಟ್ಟುಗಳು_ಮುಖವಾಡ          ( 0x0C )

/* The I bit in the DAIF bits. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DAIF_I                       ( 0x80 )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_8_ಬಿಟ್_ಮೌಲ್ಯ              ( ( uint8_t ) 0xff )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಬಿಟ್_0_ಗಣ                    ( ( uint8_t ) 0x01 )

/* The space on the stack required to hold the FPU registers.
 * There are 32 128-bit plus 2 64-bit status registers. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FPU_ರಿಜಿಸ್ಟರ್_ಪದಗಳು           ( ( 32 * 2 ) + 2 )

/*-----------------------------------------------------------*/

#ಆದರೆ ( configENABLE_MPU == 1 )

    /**
     * @brief Setup the Memory Protection Unit (MPU).
     */
    PRIVILEGED_FUNCTION ಶೂನ್ಯ v_ಸಿದ್ಧತೆ_MPU( ಶೂನ್ಯ );

    /**
     * @brief Enable the Memory Protection Unit (MPU).
     */
    PRIVILEGED_FUNCTION ಶೂನ್ಯ vEnableMPU( ಶೂನ್ಯ );

    /**
     * @brief Called from an ISR and returns the core ID the code is executing on.
     *
     * @return uint8_t The core ID.
     */
    PRIVILEGED_FUNCTION uint8_t uc_ಪೋರ್ಟ್_Get_Core_IDFrom_Isr( ಶೂನ್ಯ );

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    PRIVILEGED_FUNCTION ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Task_Privileged( ಶೂನ್ಯ );

    /**
     * @brief Extract MPU region's access permissions from the Protection Region Base Address Register
     * (PRBAR_EL1) value.
     *
     * @param ullPrbarEl1Value PRBAR_EL1 value for the MPU region.
     *
     * @return uint32_t Access permissions.
     */
    PRIVILEGED_FUNCTION ಸ್ಥಿರ uint32_t prvGetRegionAccessPermissions( uint64_t ull_Prbar_El1_ಮೌಲ್ಯ );

    /**
     * @brief Does the necessary work to enter a system call.
     *
     * @param pullPrivilegedOnlyTaskStack The task's privileged SP when the SVC was raised.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    PRIVILEGED_FUNCTION ಶೂನ್ಯ vSystemCallEnter( uint64_t * pull_Privileged_Only_Task_ರಾಶಿ,
                                               uint8_t uc_System_Call_ಸಂಖ್ಯೆ );

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    PRIVILEGED_FUNCTION __attribute__( ( naked ) ) ಶೂನ್ಯ vRequestSystemCallExit( ಶೂನ್ಯ );

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param ullSystemCallReturnValue The actual system call return value.
     */
    PRIVILEGED_FUNCTION ಶೂನ್ಯ vSystemCallExit( uint64_t ull_System_Call_Return_ಮೌಲ್ಯ );

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configENABLE_MPU == 1 ) */

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Restore_Task_Context( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ vGIC_EnableIRQ( uint32_t ul_ಅಡಚಣೆ_ID );
ಬಾಹ್ಯ ಶೂನ್ಯ v_GIC_ಗಣ_ಆದ್ಯತೆ( uint32_t ul_ಅಡಚಣೆ_ID, uint32_t ul_ಆದ್ಯತೆ );
ಬಾಹ್ಯ ಶೂನ್ಯ v_GIC_Power_ಮೇಲೆ_Redistributor( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ vGIC_EnableCPUInterface( ಶೂನ್ಯ );

/*-----------------------------------------------------------*/

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )

    PRIVILEGED_ದತ್ತಾಂಶ ಅಸ್ಥಿರ uint64_t ullCriticalNesting = 0ULL;

    /* Saved as part of the task context. If ullPortTaskHasFPUContext is non-zero
     * then floating point context must be saved and restored for the task. */
    PRIVILEGED_ದತ್ತಾಂಶ uint64_t ull_ಪೋರ್ಟ್_Task_Has_FPUContext = pdFALSE;

    /* Set to 1 to pend a context switch from an ISR. */
    PRIVILEGED_ದತ್ತಾಂಶ uint64_t ull_ಪೋರ್ಟ್_Yield_Required = pdFALSE;

    /* Counts the interrupt nesting depth. A context switch is only performed if
     * if the nesting depth is 0. */
    PRIVILEGED_ದತ್ತಾಂಶ uint64_t ull_ಪೋರ್ಟ್_ಅಡಚಣೆ_Nesting = 0;

#ಇಲ್ಲದಿದ್ದರೆ /* #if ( configNUMBER_OF_CORES == 1 ) */
    PRIVILEGED_ದತ್ತಾಂಶ ಅಸ್ಥಿರ uint64_t ullCriticalNestings[ config_ಸಂಖ್ಯೆ_ದ_CORES ] = { 0 };

    /* Flags to check if the secondary cores are ready. */
    PRIVILEGED_ದತ್ತಾಂಶ ಅಸ್ಥಿರ uint8_t ucSecondaryCoresReadyFlags[ config_ಸಂಖ್ಯೆ_ದ_CORES - 1 ] = { 0 };

    /* Flag to signal that the primary core has done all the shared initialisations. */
    PRIVILEGED_ದತ್ತಾಂಶ ಅಸ್ಥಿರ uint8_t uc_Primary_Core_Init_ಮುಗಿದ_Flag = 0;

    /* Saved as part of the task context. If ullPortTaskHasFPUContext is non-zero
     * then floating point context must be saved and restored for the task. */
    PRIVILEGED_ದತ್ತಾಂಶ uint64_t ull_ಪೋರ್ಟ್_Task_Has_FPUContext[ config_ಸಂಖ್ಯೆ_ದ_CORES ] = { pdFALSE };

    /* Set to 1 to pend a context switch from an ISR. */
    PRIVILEGED_ದತ್ತಾಂಶ uint64_t ull_ಪೋರ್ಟ್_Yield_Required[ config_ಸಂಖ್ಯೆ_ದ_CORES ] = { pdFALSE };

    /* Counts the interrupt nesting depth. A context switch is only performed if
     * if the nesting depth is 0. */
    PRIVILEGED_ದತ್ತಾಂಶ uint64_t ull_ಪೋರ್ಟ್_ಅಡಚಣೆ_Nestings[ config_ಸಂಖ್ಯೆ_ದ_CORES ] = { 0 };

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configNUMBER_OF_CORES == 1 ) */

#ಆದರೆ ( configENABLE_MPU == 1 )
    /* Set to pdTRUE when the scheduler is started. */
    PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ ತಳ_Type_t xSchedulerRunning = pdFALSE;
#ಆದರೆ_ಅಂತ್ಯ /* ( configENABLE_MPU == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configENABLE_MPU == 1 )

    ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                         TaskFunction_t px_ಸಂಕೇತ,
                                         ಶೂನ್ಯ * pvParameters,
                                         ತಳ_Type_t x_ಸತತ_Privileged,
                                         xMPU_SETTINGS * xMPUSettings )
    {
        uint32_t ul_ಸೂಚ್ಯಂಕ = 0;

        /* Layout must match portRESTORE_CONTEXT pop order (descending stack):
         * 1) FPU flag, 2) Critical nesting, 3) Optional FPU save area,
         * 4) ELR (PC), 5) SPSR (PSTATE), 6) GPRs in restore order pairs.
         */

        /* 1) FPU flag and 2) Critical nesting. */
        #ಆದರೆ ( configUSE_TASK_FPU_SUPPORT == ಪೋರ್ಟ್_TASK_NO_FPU_CONTEXT_BY_DEFAULT )
            xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = ಪೋರ್ಟ್_NO_FLOATING_ಬಿಂದು_CONTEXT; /* FPU flag */
            xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = ಪೋರ್ಟ್_NO_CRITICAL_NESTING;       /* Critical nesting */
        #ಅಥವಾಆದರೆ ( configUSE_TASK_FPU_SUPPORT == ಪೋರ್ಟ್_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
            xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = pdTRUE;                        /* FPU flag */
            xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = ಪೋರ್ಟ್_NO_CRITICAL_NESTING;       /* Critical nesting */
            #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
                ull_ಪೋರ್ಟ್_Task_Has_FPUContext = pdTRUE;
            #ಇಲ್ಲದಿದ್ದರೆ
                ull_ಪೋರ್ಟ್_Task_Has_FPUContext[ ಪೋರ್ಟ್_GET_CORE_ID() ] = pdTRUE;
            #ಆದರೆ_ಅಂತ್ಯ
        #ಇಲ್ಲದಿದ್ದರೆ
            #ದೋಷ "Invalid configUSE_TASK_FPU_SUPPORT setting - must be 1 or 2."
        #ಆದರೆ_ಅಂತ್ಯ

        /* 3) Optional FPU save area immediately after the flag+critical pair. */
        #ಆದರೆ ( configUSE_TASK_FPU_SUPPORT == ಪೋರ್ಟ್_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
            memset( &xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ ], 0x00, ಪೋರ್ಟ್_FPU_ರಿಜಿಸ್ಟರ್_ಪದಗಳು * ಗಾತ್ರ( ರಾಶಿ_Type_t ) );
            ul_ಸೂಚ್ಯಂಕ += ಪೋರ್ಟ್_FPU_ರಿಜಿಸ್ಟರ್_ಪದಗಳು;
        #ಆದರೆ_ಅಂತ್ಯ

        /* 4) ELR (PC) and 5) SPSR (PSTATE). */
        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ; /* ELR */

        ಆದರೆ( x_ಸತತ_Privileged == pdTRUE )
        {
            xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = ಪೋರ್ಟ್_INITIAL_PSTATE_EL1;    /* SPSR */
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = ಪೋರ್ಟ್_INITIAL_PSTATE_EL0;    /* SPSR */
        }

        /* 6) General-purpose registers in the order expected by restoreallgpregisters. */
        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = ( ರಾಶಿ_Type_t ) 0x00;         /* X30 (LR) */
        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = ( ರಾಶಿ_Type_t ) 0x00;         /* XZR (dummy) */

        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x2828282828282828ULL;        /* X28 */
        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x2929292929292929ULL;        /* X29 */

        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x2626262626262626ULL;        /* X26 */
        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x2727272727272727ULL;        /* X27 */

        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x2424242424242424ULL;        /* X24 */
        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x2525252525252525ULL;        /* X25 */

        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x2222222222222222ULL;        /* X22 */
        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x2323232323232323ULL;        /* X23 */

        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x2020202020202020ULL;        /* X20 */
        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x2121212121212121ULL;        /* X21 */

        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x1818181818181818ULL;        /* X18 */
        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x1919191919191919ULL;        /* X19 */

        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x1616161616161616ULL;        /* X16 */
        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x1717171717171717ULL;        /* X17 */

        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x1414141414141414ULL;        /* X14 */
        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x1515151515151515ULL;        /* X15 */

        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x1212121212121212ULL;        /* X12 */
        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x1313131313131313ULL;        /* X13 */

        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x1010101010101010ULL;        /* X10 */
        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x1111111111111111ULL;        /* X11 */

        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x0808080808080808ULL;        /* X8 */
        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x0909090909090909ULL;        /* X9 */

        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x0606060606060606ULL;        /* X6 */
        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x0707070707070707ULL;        /* X7 */

        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x0404040404040404ULL;        /* X4 */
        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x0505050505050505ULL;        /* X5 */

        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x0202020202020202ULL;        /* X2 */
        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x0303030303030303ULL;        /* X3 */

        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = ( ರಾಶಿ_Type_t ) pvParameters; /* X0 */
        xMPUSettings->ullContext[ ul_ಸೂಚ್ಯಂಕ++ ] = 0x0101010101010101ULL;        /* X1 */

        ಆದರೆ( x_ಸತತ_Privileged == pdTRUE )
        {
            xMPUSettings->ullTaskFlags |= ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            xMPUSettings->ullTaskFlags &= ( ~ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG );
        }

        xMPUSettings->ullTaskUnprivilegedSP = ( ( uint64_t ) px_ತುದಿ_ದ_ರಾಶಿ & ಪೋರ್ಟ್_MPU_PRBAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ );

        ಹಿಂತಿರುಗಿ &( xMPUSettings->ullContext[ 0 ] );
    }

#ಇಲ್ಲದಿದ್ದರೆ /* #if ( configENABLE_MPU == 1 ) */

    /*
    * See header file for description.
    */
    ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                         TaskFunction_t px_ಸಂಕೇತ,
                                         ಶೂನ್ಯ * pvParameters )
    {
        /* Setup the initial stack of the task.  The stack is set exactly as
        * expected by the portRESTORE_CONTEXT() macro. */

        /* First all the general purpose registers. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x0101010101010101ULL;        /* R1 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters; /* R0 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x0303030303030303ULL;        /* R3 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x0202020202020202ULL;        /* R2 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x0505050505050505ULL;        /* R5 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x0404040404040404ULL;        /* R4 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x0707070707070707ULL;        /* R7 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x0606060606060606ULL;        /* R6 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x0909090909090909ULL;        /* R9 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x0808080808080808ULL;        /* R8 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x1111111111111111ULL;        /* R11 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x1010101010101010ULL;        /* R10 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x1313131313131313ULL;        /* R13 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x1212121212121212ULL;        /* R12 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x1515151515151515ULL;        /* R15 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x1414141414141414ULL;        /* R14 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x1717171717171717ULL;        /* R17 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x1616161616161616ULL;        /* R16 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x1919191919191919ULL;        /* R19 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x1818181818181818ULL;        /* R18 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x2121212121212121ULL;        /* R21 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x2020202020202020ULL;        /* R20 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x2323232323232323ULL;        /* R23 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x2222222222222222ULL;        /* R22 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x2525252525252525ULL;        /* R25 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x2424242424242424ULL;        /* R24 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x2727272727272727ULL;        /* R27 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x2626262626262626ULL;        /* R26 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x2929292929292929ULL;        /* R29 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x2828282828282828ULL;        /* R28 */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x00;         /* XZR - has no effect, used so there are an even number of registers. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x00;         /* R30 - procedure call link register. */

        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_PSTATE_EL0;

        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ; /* Exception return address. */

        #ಆದರೆ ( configUSE_TASK_FPU_SUPPORT == ಪೋರ್ಟ್_TASK_NO_FPU_CONTEXT_BY_DEFAULT )
        {
            /* The task will start with a critical nesting count of 0 as interrupts are
            * enabled. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_NO_CRITICAL_NESTING;

            /* The task will start without a floating point context.  A task that
            * uses the floating point hardware must call vPortTaskUsesFPU() before
            * executing any floating point instructions. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_NO_FLOATING_ಬಿಂದು_CONTEXT;
        }
        #ಅಥವಾಆದರೆ ( configUSE_TASK_FPU_SUPPORT == ಪೋರ್ಟ್_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
        {
            /* The task will start with a floating point context.  Leave enough
            * space for the registers - and ensure they are initialised to 0. */
            px_ತುದಿ_ದ_ರಾಶಿ -= ಪೋರ್ಟ್_FPU_ರಿಜಿಸ್ಟರ್_ಪದಗಳು;
            memset( px_ತುದಿ_ದ_ರಾಶಿ, 0x00, ಪೋರ್ಟ್_FPU_ರಿಜಿಸ್ಟರ್_ಪದಗಳು * ಗಾತ್ರ( ರಾಶಿ_Type_t ) );

            /* The task will start with a critical nesting count of 0 as interrupts are
            * enabled. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_NO_CRITICAL_NESTING;

            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = pdTRUE;
            #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
            ull_ಪೋರ್ಟ್_Task_Has_FPUContext = pdTRUE;
            #ಇಲ್ಲದಿದ್ದರೆ
            ull_ಪೋರ್ಟ್_Task_Has_FPUContext[ ಪೋರ್ಟ್_GET_CORE_ID() ] = pdTRUE;
            #ಆದರೆ_ಅಂತ್ಯ
        }
        #ಇಲ್ಲದಿದ್ದರೆ /* if ( configUSE_TASK_FPU_SUPPORT == portTASK_NO_FPU_CONTEXT_BY_DEFAULT ) */
        {
            #ದೋಷ "Invalid configUSE_TASK_FPU_SUPPORT setting - configUSE_TASK_FPU_SUPPORT must be set to 1, 2, or left undefined."
        }
        #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_FPU_SUPPORT == portTASK_NO_FPU_CONTEXT_BY_DEFAULT ) */

        ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;

    }

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configENABLE_MPU == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configENABLE_MPU == 1 )

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
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ಸ್ಥಿರಾಂಕ ರಚನೆ x_ಸ್ಮರಣೆ_REGION * ಸ್ಥಿರಾಂಕ xRegions,
                                    ರಾಶಿ_Type_t * px_Bottom_ದ_ರಾಶಿ,
                                    ರಾಶಿ_Type_t x_ರಾಶಿ_ಆಳ )  /* PRIVILEGED_FUNCTION */
    {
        uint64_t ull_Region_ಆರಂಭ_ವಿಳಾಸ, ull_Region_ಕೊನೆ_ವಿಳಾಸ;
        uint8_t  uc_ಸೂಚ್ಯಂಕ = 0, uc_Region_ಸಂಖ್ಯೆ;

        #ಆದರೆ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ಬಾಹ್ಯ uint64_t * __privileged_sram_start__;
            ಬಾಹ್ಯ uint64_t * __privileged_sram_end__;
        #ಇಲ್ಲದಿದ್ದರೆ
            /* Declaration when these variable are exported from linker scripts. */
            ಬಾಹ್ಯ uint64_t __privileged_sram_start__[];
            ಬಾಹ್ಯ uint64_t __privileged_sram_end__[];
        #ಆದರೆ_ಅಂತ್ಯ /* defined( __ARMCC_VERSION ) */

        /* Setup MAIR_EL1. */
        xMPUSettings->ullMairEl1 = ( ( ಪೋರ್ಟ್_MPU_ಸಾಮಾನ್ಯ_ಸ್ಮರಣೆ_BUFFERABLE_CACHEABLE << ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR0_POS ) & ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR0_ಮುಖವಾಡ );
        xMPUSettings->ullMairEl1 |= ( ( ಪೋರ್ಟ್_MPU_DEVICE_ಸ್ಮರಣೆ_n_Gn_RE << ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR1_POS ) & ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR1_ಮುಖವಾಡ );

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid. At all other
         * times the stack parameters will not be valid and it is assumed that
         * the stack region has already been configured. */
        ಆದರೆ( x_ರಾಶಿ_ಆಳ > 0 )
        {
            ull_Region_ಆರಂಭ_ವಿಳಾಸ = ( uint64_t ) px_Bottom_ದ_ರಾಶಿ;
            ull_Region_ಕೊನೆ_ವಿಳಾಸ = ( uint64_t ) px_Bottom_ದ_ರಾಶಿ + ( x_ರಾಶಿ_ಆಳ * ( config_ರಾಶಿ_ಆಳ_TYPE ) ಗಾತ್ರ( ರಾಶಿ_Type_t ) ) - 1;

            /* If the stack is within the privileged SRAM, do not protect it
             * using a separate MPU region. This is needed because this
             * region is already protected using an MPU region and ARMv8-R does
             * not allow overlapping MPU regions.
             */
            ಆದರೆ( ( ull_Region_ಆರಂಭ_ವಿಳಾಸ >= ( uint64_t ) __privileged_sram_start__ ) &&
                ( ull_Region_ಕೊನೆ_ವಿಳಾಸ <= ( uint64_t ) __privileged_sram_end__ ) )
            {
                xMPUSettings->xRegionsSettings[ ಪೋರ್ಟ್_ರಾಶಿ_REGION_ಸೂಚ್ಯಂಕ ].ullPrbarEl1 = 0;
                xMPUSettings->xRegionsSettings[ ಪೋರ್ಟ್_ರಾಶಿ_REGION_ಸೂಚ್ಯಂಕ ].ullPrlarEl1 = 0;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                /* Define the region that allows access to the stack. */
                ull_Region_ಆರಂಭ_ವಿಳಾಸ &= ಪೋರ್ಟ್_MPU_PRBAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ;
                ull_Region_ಕೊನೆ_ವಿಳಾಸ &= ಪೋರ್ಟ್_MPU_PRLAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ;

                xMPUSettings->xRegionsSettings[ ಪೋರ್ಟ್_ರಾಶಿ_REGION_ಸೂಚ್ಯಂಕ ].ullPrbarEl1 = ( ull_Region_ಆರಂಭ_ವಿಳಾಸ ) |
                                                                                 ( ಪೋರ್ಟ್_MPU_REGION_INNER_SHAREABLE ) |
                                                                                 ( ಪೋರ್ಟ್_MPU_REGION_READ_WRITE ) |
                                                                                 ( ಪೋರ್ಟ್_MPU_REGION_EXECUTE_NEVER );

                xMPUSettings->xRegionsSettings[ ಪೋರ್ಟ್_ರಾಶಿ_REGION_ಸೂಚ್ಯಂಕ ].ullPrlarEl1 = ( ull_Region_ಕೊನೆ_ವಿಳಾಸ ) |
                                                                                 ( ಪೋರ್ಟ್_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                                                                                 ( ಪೋರ್ಟ್_MPU_PRLAR_EL1_REGION_ENABLE );
            }
        }

        /* User supplied configurable regions. */
        ಗಾಗಿ( uc_Region_ಸಂಖ್ಯೆ = 1; uc_Region_ಸಂಖ್ಯೆ <= ಪೋರ್ಟ್_ಅಂಕೆ_CONFIGURABLE_REGIONS; uc_Region_ಸಂಖ್ಯೆ++ )
        {
            /* If xRegions is NULL i.e. the task has not specified any MPU
             * region, the else part ensures that all the configurable MPU
             * regions are invalidated.
             * The minimum region size is 64 Bytes.
             */
            ಆದರೆ( xRegions != ಖಾಲಿ )
            {
                /* Configure the region only if the base address is non-NULL.
                 * The user may choose to use only a subset of the available MPU regions.
                 * This check prevents undefined regions (i.e. regions with a NULL base
                 * address) from being configured and from triggering the size-check
                 * assertion below.
                 */
                ಆದರೆ ( xRegions[ uc_ಸೂಚ್ಯಂಕ ].pv_ತಳ_ವಿಳಾಸ != ಖಾಲಿ )
                {
                    configASSERT( xRegions[ uc_ಸೂಚ್ಯಂಕ ].ul_ಉದ್ದಳತೆ_ಒಳ_ಬೈಟುಗಳು >= 64UL );

                    uint64_t ull_Prbar_El1_Reg_ಮೌಲ್ಯ, ull_Prlar_El1_Reg_ಮೌಲ್ಯ;

                    /* Translate the generic region definition contained in xRegions
                     * into the ARMv8-R specific MPU settings that are then stored in
                     * xMPUSettings.
                     */
                    ull_Region_ಆರಂಭ_ವಿಳಾಸ = ( ( uint64_t ) xRegions[ uc_ಸೂಚ್ಯಂಕ ].pv_ತಳ_ವಿಳಾಸ ) & ಪೋರ್ಟ್_MPU_PRBAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ;
                    ull_Region_ಕೊನೆ_ವಿಳಾಸ = ( uint64_t ) xRegions[ uc_ಸೂಚ್ಯಂಕ ].pv_ತಳ_ವಿಳಾಸ + xRegions[ uc_ಸೂಚ್ಯಂಕ ].ul_ಉದ್ದಳತೆ_ಒಳ_ಬೈಟುಗಳು - 1;
                    ull_Region_ಕೊನೆ_ವಿಳಾಸ &= ಪೋರ್ಟ್_MPU_PRLAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ;

                    /* Checks for overlaps with another user defined regions and stack region, which are already configured. */
                    ಗಾಗಿ( uint8_t uc_User_Region_ಸಂಖ್ಯೆ = 0; uc_User_Region_ಸಂಖ್ಯೆ < ಪೋರ್ಟ್_ಅಂಕೆ_CONFIGURABLE_REGIONS; uc_User_Region_ಸಂಖ್ಯೆ++ )
                    {
                        /* Check for overlap. */
                        ಆದರೆ( ( ಪೋರ್ಟ್_IS_ವಿಳಾಸ_WITHIN_RANGE( ull_Region_ಆರಂಭ_ವಿಳಾಸ,
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_ಸಂಖ್ಯೆ ].ullPrbarEl1 & ಪೋರ್ಟ್_MPU_PRBAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ ),
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_ಸಂಖ್ಯೆ ].ullPrlarEl1 & ಪೋರ್ಟ್_MPU_PRLAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ ) ) ||
                            ( ಪೋರ್ಟ್_IS_ವಿಳಾಸ_WITHIN_RANGE( ull_Region_ಕೊನೆ_ವಿಳಾಸ,
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_ಸಂಖ್ಯೆ ].ullPrbarEl1 & ಪೋರ್ಟ್_MPU_PRBAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ ),
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_ಸಂಖ್ಯೆ ].ullPrlarEl1 & ಪೋರ್ಟ್_MPU_PRLAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ ) ) ) ) )
                        {
                            /* Overlap detected - assert. */
                            configASSERT( ಖಾಲಿ );
                        }
                    }

                    /* Checks for overlaps with kernel programmed regions which are already programmed as part of vSetupMPU. */
                    ಗಾಗಿ (uint8_t uc_Programmed_Region_ಸೂಚ್ಯಂಕ = 0; uc_Programmed_Region_ಸೂಚ್ಯಂಕ < 4; uc_Programmed_Region_ಸೂಚ್ಯಂಕ++)
                    {
                        __asm ಅಸ್ಥಿರ ( "msr PRSELR_EL1, %0" : : "r" ( ( uint64_t ) uc_Programmed_Region_ಸೂಚ್ಯಂಕ ) );

                        __asm ಅಸ್ಥಿರ ( "mrs %0, PRBAR_EL1" : "=r" ( ull_Prbar_El1_Reg_ಮೌಲ್ಯ ) );
                        ull_Prbar_El1_Reg_ಮೌಲ್ಯ &= ಪೋರ್ಟ್_MPU_PRBAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ;

                        __asm ಅಸ್ಥಿರ ( "mrs %0, PRLAR_EL1" : "=r" ( ull_Prlar_El1_Reg_ಮೌಲ್ಯ ) );
                        ull_Prlar_El1_Reg_ಮೌಲ್ಯ &= ಪೋರ್ಟ್_MPU_PRLAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ;

                        /* Check for overlap. */
                        ಆದರೆ( ( ಪೋರ್ಟ್_IS_ವಿಳಾಸ_WITHIN_RANGE( ull_Region_ಆರಂಭ_ವಿಳಾಸ,
                                                        ull_Prbar_El1_Reg_ಮೌಲ್ಯ,
                                                        ull_Prlar_El1_Reg_ಮೌಲ್ಯ ) ) ||
                            ( ಪೋರ್ಟ್_IS_ವಿಳಾಸ_WITHIN_RANGE( ull_Region_ಕೊನೆ_ವಿಳಾಸ,
                                                        ull_Prbar_El1_Reg_ಮೌಲ್ಯ,
                                                        ull_Prlar_El1_Reg_ಮೌಲ್ಯ ) ) )
                        {
                            /* Overlap detected - assert. */
                            configASSERT( ಖಾಲಿ );
                        }
                    }

                    /* Start address. */
                    xMPUSettings->xRegionsSettings[ uc_Region_ಸಂಖ್ಯೆ ].ullPrbarEl1 = ( ull_Region_ಆರಂಭ_ವಿಳಾಸ );

                    /* RO/RW. */
                    ಆದರೆ( ( xRegions[ uc_ಸೂಚ್ಯಂಕ ].ulParameters & tskMPU_REGION_READ_ONLY ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_ಸಂಖ್ಯೆ ].ullPrbarEl1 |= ( ಪೋರ್ಟ್_MPU_REGION_READ_ONLY );
                    }
                    ಇಲ್ಲದಿದ್ದರೆ
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_ಸಂಖ್ಯೆ ].ullPrbarEl1 |= ( ಪೋರ್ಟ್_MPU_REGION_READ_WRITE );
                    }

                    /* XN. */
                    ಆದರೆ( ( xRegions[ uc_ಸೂಚ್ಯಂಕ ].ulParameters & tskMPU_REGION_EXECUTE_NEVER ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_ಸಂಖ್ಯೆ ].ullPrbarEl1 |= ( ಪೋರ್ಟ್_MPU_REGION_EXECUTE_NEVER );
                    }

                    /* SH. */
                    ಆದರೆ( ( xRegions[ uc_ಸೂಚ್ಯಂಕ ].ulParameters & tskMPU_REGION_INNER_SHAREABLE ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_ಸಂಖ್ಯೆ ].ullPrbarEl1 |= ( ಪೋರ್ಟ್_MPU_REGION_INNER_SHAREABLE );
                    }
                    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ( ( xRegions[ uc_ಸೂಚ್ಯಂಕ ].ulParameters & tskMPU_REGION_OUTER_SHAREABLE ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_ಸಂಖ್ಯೆ ].ullPrbarEl1 |= ( ಪೋರ್ಟ್_MPU_REGION_OUTER_SHAREABLE );
                    }
                    ಇಲ್ಲದಿದ್ದರೆ
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_ಸಂಖ್ಯೆ ].ullPrbarEl1 |= ( ಪೋರ್ಟ್_MPU_REGION_NON_SHAREABLE );
                    }

                    /* End Address. */
                    xMPUSettings->xRegionsSettings[ uc_Region_ಸಂಖ್ಯೆ ].ullPrlarEl1 = ( ull_Region_ಕೊನೆ_ವಿಳಾಸ ) |
                                                                                ( ಪೋರ್ಟ್_MPU_PRLAR_EL1_REGION_ENABLE );

                    /* Normal memory/ Device memory. */
                    ಆದರೆ( ( xRegions[ uc_ಸೂಚ್ಯಂಕ ].ulParameters & tsk_MPU_REGION_DEVICE_ಸ್ಮರಣೆ ) != 0 )
                    {
                        /* Attr1 in MAIR_EL1 is configured as device memory. */
                        xMPUSettings->xRegionsSettings[ uc_Region_ಸಂಖ್ಯೆ ].ullPrlarEl1 |= ಪೋರ್ಟ್_MPU_PRLAR_EL1_ATTR_INDEX1;
                    }
                    ಇಲ್ಲದಿದ್ದರೆ
                    {
                        /* Attr0 in MAIR_EL1 is configured as normal memory. */
                        xMPUSettings->xRegionsSettings[ uc_Region_ಸಂಖ್ಯೆ ].ullPrlarEl1 |= ಪೋರ್ಟ್_MPU_PRLAR_EL1_ATTR_INDEX0;
                    }
                }
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                /* Invalidate the region. */
                xMPUSettings->xRegionsSettings[ uc_Region_ಸಂಖ್ಯೆ ].ullPrbarEl1 = 0UL;
                xMPUSettings->xRegionsSettings[ uc_Region_ಸಂಖ್ಯೆ ].ullPrlarEl1 = 0UL;
            }

            uc_ಸೂಚ್ಯಂಕ++;
        }

    }
    /*-----------------------------------------------------------*/

    ಶೂನ್ಯ v_ಸಿದ್ಧತೆ_MPU( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
    {
        #ಆದರೆ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts.
             */
            ಬಾಹ್ಯ uint64_t * __privileged_functions_start__;
            ಬಾಹ್ಯ uint64_t * __privileged_functions_end__;
            ಬಾಹ್ಯ uint64_t * __syscalls_flash_start__;
            ಬಾಹ್ಯ uint64_t * __syscalls_flash_end__;
            ಬಾಹ್ಯ uint64_t * __unprivileged_flash_start__;
            ಬಾಹ್ಯ uint64_t * __unprivileged_flash_end__;
            ಬಾಹ್ಯ uint64_t * __privileged_sram_start__;
            ಬಾಹ್ಯ uint64_t * __privileged_sram_end__;
        #ಇಲ್ಲದಿದ್ದರೆ /* if defined( __ARMCC_VERSION ) */
            /* Declaration when these variable are exported from linker scripts. */
            ಬಾಹ್ಯ uint64_t __privileged_functions_start__[];
            ಬಾಹ್ಯ uint64_t __privileged_functions_end__[];
            ಬಾಹ್ಯ uint64_t __syscalls_flash_start__[];
            ಬಾಹ್ಯ uint64_t __syscalls_flash_end__[];
            ಬಾಹ್ಯ uint64_t __unprivileged_flash_start__[];
            ಬಾಹ್ಯ uint64_t __unprivileged_flash_end__[];
            ಬಾಹ್ಯ uint64_t __privileged_sram_start__[];
            ಬಾಹ್ಯ uint64_t __privileged_sram_end__[];
        #ಆದರೆ_ಅಂತ್ಯ /* defined( __ARMCC_VERSION ) */

        /* The only permitted number of regions are 16 or 32. */
        configASSERT( ( config_ಒಟ್ಟು_MPU_REGIONS == 16 ) || ( config_ಒಟ್ಟು_MPU_REGIONS == 32 ) );

        /* MAIR_EL1 - Index 0. */
        uint64_t ull_Mair_El1_Reg_ಮೌಲ್ಯ = ( ( ಪೋರ್ಟ್_MPU_ಸಾಮಾನ್ಯ_ಸ್ಮರಣೆ_BUFFERABLE_CACHEABLE << ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR0_POS ) & ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR0_ಮುಖವಾಡ );
        /* MAIR_EL1 - Index 1. */
        ull_Mair_El1_Reg_ಮೌಲ್ಯ |= ( ( ಪೋರ್ಟ್_MPU_DEVICE_ಸ್ಮರಣೆ_n_Gn_RE << ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR1_POS ) & ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR1_ಮುಖವಾಡ );

        __asm ಅಸ್ಥಿರ ( "msr MAIR_EL1, %0" : : "r" ( ull_Mair_El1_Reg_ಮೌಲ್ಯ ) );

        /* Setup privileged flash as Read Only so that privileged tasks can
         * read it but not modify.
         */
        uint64_t ull_Prselr_El1_Reg_ಮೌಲ್ಯ = ಪೋರ್ಟ್_PRIVILEGED_FLASH_REGION;
        __asm ಅಸ್ಥಿರ ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_ಮೌಲ್ಯ ) );

        uint64_t ull_Prbar_El1_Reg_ಮೌಲ್ಯ = ( ( ( uint64_t ) __privileged_functions_start__ ) & ಪೋರ್ಟ್_MPU_PRBAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ ) |
                                       ( ಪೋರ್ಟ್_MPU_REGION_NON_SHAREABLE ) |
                                       ( ಪೋರ್ಟ್_MPU_REGION_PRIVILEGED_READ_ONLY );
        __asm ಅಸ್ಥಿರ ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_ಮೌಲ್ಯ ) );

        uint64_t ull_Prlar_El1_Reg_ಮೌಲ್ಯ = ( ( ( uint64_t ) __privileged_functions_end__ ) & ಪೋರ್ಟ್_MPU_PRLAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ ) |
                                       ( ಪೋರ್ಟ್_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                                       ( ಪೋರ್ಟ್_MPU_PRLAR_EL1_REGION_ENABLE );
        __asm ಅಸ್ಥಿರ ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_ಮೌಲ್ಯ ) );

        /* Setup unprivileged flash as Read Only by both privileged and
         * unprivileged tasks. All tasks can read it but no-one can modify.
         */
        ull_Prselr_El1_Reg_ಮೌಲ್ಯ = ಪೋರ್ಟ್_UNPRIVILEGED_FLASH_REGION;
        __asm ಅಸ್ಥಿರ ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_ಮೌಲ್ಯ ) );

        ull_Prbar_El1_Reg_ಮೌಲ್ಯ = ( ( ( uint64_t ) __unprivileged_flash_start__ ) & ಪೋರ್ಟ್_MPU_PRBAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ ) |
                              ( ಪೋರ್ಟ್_MPU_REGION_NON_SHAREABLE ) |
                              ( ಪೋರ್ಟ್_MPU_REGION_READ_ONLY );
        __asm ಅಸ್ಥಿರ ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_ಮೌಲ್ಯ ) );

        ull_Prlar_El1_Reg_ಮೌಲ್ಯ = ( ( ( uint64_t ) __unprivileged_flash_end__ ) & ಪೋರ್ಟ್_MPU_PRLAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ ) |
                              ( ಪೋರ್ಟ್_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                              ( ಪೋರ್ಟ್_MPU_PRLAR_EL1_REGION_ENABLE );
        __asm ಅಸ್ಥಿರ ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_ಮೌಲ್ಯ ) );

        /* Setup unprivileged syscalls flash as Read Only by both privileged
         * and unprivileged tasks. All tasks can read it but no-one can modify.
         */
        ull_Prselr_El1_Reg_ಮೌಲ್ಯ = ಪೋರ್ಟ್_UNPRIVILEGED_SYSCALLS_REGION;
        __asm ಅಸ್ಥಿರ ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_ಮೌಲ್ಯ ) );

        ull_Prbar_El1_Reg_ಮೌಲ್ಯ = ( ( ( uint64_t ) __syscalls_flash_start__ ) & ಪೋರ್ಟ್_MPU_PRBAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ ) |
                              ( ಪೋರ್ಟ್_MPU_REGION_NON_SHAREABLE ) |
                              ( ಪೋರ್ಟ್_MPU_REGION_READ_ONLY );
        __asm ಅಸ್ಥಿರ ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_ಮೌಲ್ಯ ) );

        ull_Prlar_El1_Reg_ಮೌಲ್ಯ = ( ( ( uint64_t ) __syscalls_flash_end__ ) & ಪೋರ್ಟ್_MPU_PRLAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ ) |
                              ( ಪೋರ್ಟ್_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                              ( ಪೋರ್ಟ್_MPU_PRLAR_EL1_REGION_ENABLE );
        __asm ಅಸ್ಥಿರ ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_ಮೌಲ್ಯ ) );

        /* Setup RAM containing kernel data for privileged access only. */
        ull_Prselr_El1_Reg_ಮೌಲ್ಯ = ಪೋರ್ಟ್_PRIVILEGED_RAM_REGION;
        __asm ಅಸ್ಥಿರ ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_ಮೌಲ್ಯ ) );

        ull_Prbar_El1_Reg_ಮೌಲ್ಯ = ( ( ( uint64_t ) __privileged_sram_start__ ) & ಪೋರ್ಟ್_MPU_PRBAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ ) |
                              ( ಪೋರ್ಟ್_MPU_REGION_INNER_SHAREABLE ) |
                              ( ಪೋರ್ಟ್_MPU_REGION_PRIVILEGED_READ_WRITE ) |
                              ( ಪೋರ್ಟ್_MPU_REGION_EXECUTE_NEVER );
        __asm ಅಸ್ಥಿರ ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_ಮೌಲ್ಯ ) );

        ull_Prlar_El1_Reg_ಮೌಲ್ಯ = ( ( ( uint64_t ) __privileged_sram_end__ ) & ಪೋರ್ಟ್_MPU_PRLAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ ) |
                              ( ಪೋರ್ಟ್_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                              ( ಪೋರ್ಟ್_MPU_PRLAR_EL1_REGION_ENABLE );
        __asm ಅಸ್ಥಿರ ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_ಮೌಲ್ಯ ) );
    }
    /*-----------------------------------------------------------*/

    ಶೂನ್ಯ vEnableMPU( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
    {
        uint64_t ull_Sctlr_El1_Reg_ಮೌಲ್ಯ;

        __asm ಅಸ್ಥಿರ ( "mrs %0, SCTLR_EL1" : "=r" ( ull_Sctlr_El1_Reg_ಮೌಲ್ಯ ) );
        /* Enable the MPU. Also enable privileged access to the
         * background region.
         */
        ull_Sctlr_El1_Reg_ಮೌಲ್ಯ |= ( ಪೋರ್ಟ್_MPU_PRIV_BACKGROUND_ENABLE_ಬಿಟ್ | ಪೋರ್ಟ್_MPU_ENABLE_ಬಿಟ್ );
        __asm ಅಸ್ಥಿರ ( "msr SCTLR_EL1, %0" : : "r" ( ull_Sctlr_El1_Reg_ಮೌಲ್ಯ ) );

        /* Ensure the write to SCTLR_EL1 is committed before
         * returning.
         */
        __asm ಅಸ್ಥಿರ ( "isb" );
    }
    /*-----------------------------------------------------------*/

    ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Task_Privileged( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
    {
        ತಳ_Type_t xTaskIsPrivileged = pdFALSE;

        #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
            ಬಾಹ್ಯ TaskHandle_t pxCurrentTCB;
            xMPU_SETTINGS * pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );
        #ಇಲ್ಲದಿದ್ದರೆ
            ಬಾಹ್ಯ TaskHandle_t pxCurrentTCBs[ config_ಸಂಖ್ಯೆ_ದ_CORES ];
            xMPU_SETTINGS * pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCBs[ ಪೋರ್ಟ್_GET_CORE_ID_FROM_ISR() ] );
        #ಆದರೆ_ಅಂತ್ಯ

        ಆದರೆ( ( pxMpuSettings->ullTaskFlags & ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG ) == ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        ಹಿಂತಿರುಗಿ xTaskIsPrivileged;
    }
    /*-----------------------------------------------------------*/

    ಸ್ಥಿರ uint32_t prvGetRegionAccessPermissions( uint64_t ull_Prbar_El1_ಮೌಲ್ಯ ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ulAccessPermissions = 0;

        ಆದರೆ( ( ull_Prbar_El1_ಮೌಲ್ಯ & ಪೋರ್ಟ್_MPU_PRBAR_EL1_ACCESS_PERMISSIONS_ಮುಖವಾಡ ) == ಪೋರ್ಟ್_MPU_REGION_READ_ONLY )
        {
            ulAccessPermissions = tskMPU_READ_PERMISSION;
        }

        ಆದರೆ( ( ull_Prbar_El1_ಮೌಲ್ಯ & ಪೋರ್ಟ್_MPU_PRBAR_EL1_ACCESS_PERMISSIONS_ಮುಖವಾಡ ) == ಪೋರ್ಟ್_MPU_REGION_READ_WRITE )
        {
            ulAccessPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
        }

        ಹಿಂತಿರುಗಿ ulAccessPermissions;
    }
    /*-----------------------------------------------------------*/

    ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * pv_ಬಫರ್,
                                                size_t x_ಬಫರ್_ಉದ್ದಳತೆ,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i;
        uint64_t ull_ಬಫರ್_ಆರಂಭ_ವಿಳಾಸ, ull_ಬಫರ್_ಕೊನೆ_ವಿಳಾಸ;
        ತಳ_Type_t xAccessGranted = pdFALSE;
        ಸ್ಥಿರಾಂಕ xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ಖಾಲಿ ); /* Calling task's MPU settings. */

        ಆದರೆ( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ( ( xTaskMpuSettings->ullTaskFlags & ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG ) == ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            ಆದರೆ( ಪೋರ್ಟ್_ಕೂಡಿಸು_UINT64_WILL_ಅತಿಪ್ರವಾಹ( ( ( uint64_t ) pv_ಬಫರ್ ), ( ( uint64_t ) x_ಬಫರ್_ಉದ್ದಳತೆ - 1ULL ) ) == pdFALSE )
            {
                ull_ಬಫರ್_ಆರಂಭ_ವಿಳಾಸ = ( uint64_t ) pv_ಬಫರ್;
                ull_ಬಫರ್_ಕೊನೆ_ವಿಳಾಸ = ( ( ( uint64_t ) pv_ಬಫರ್ ) + ( uint64_t ) x_ಬಫರ್_ಉದ್ದಳತೆ - 1ULL );

                ಗಾಗಿ( i = 0; i < ಪೋರ್ಟ್_ಒಟ್ಟು_ಅಂಕೆ_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    ಆದರೆ( ( xTaskMpuSettings->xRegionsSettings[ i ].ullPrlarEl1 & ಪೋರ್ಟ್_MPU_PRLAR_EL1_REGION_ENABLE ) == ಪೋರ್ಟ್_MPU_PRLAR_EL1_REGION_ENABLE )
                    {
                        ಆದರೆ( ಪೋರ್ಟ್_IS_ವಿಳಾಸ_WITHIN_RANGE( ull_ಬಫರ್_ಆರಂಭ_ವಿಳಾಸ,
                                                         ಪೋರ್ಟ್_ಹೊರತೆಗೆ_ಮೊದಲ_ವಿಳಾಸ_FROM_PRBAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrbarEl1 ),
                                                         ಪೋರ್ಟ್_ಹೊರತೆಗೆ_ಕೊನೆಯ_ವಿಳಾಸ_FROM_PRLAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrlarEl1 ) ) &&
                            ಪೋರ್ಟ್_IS_ವಿಳಾಸ_WITHIN_RANGE( ull_ಬಫರ್_ಕೊನೆ_ವಿಳಾಸ,
                                                         ಪೋರ್ಟ್_ಹೊರತೆಗೆ_ಮೊದಲ_ವಿಳಾಸ_FROM_PRBAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrbarEl1 ),
                                                         ಪೋರ್ಟ್_ಹೊರತೆಗೆ_ಕೊನೆಯ_ವಿಳಾಸ_FROM_PRLAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrlarEl1 ) ) &&
                            ಪೋರ್ಟ್_IS_AUTHORIZED( ulAccessRequested,
                                               prvGetRegionAccessPermissions( xTaskMpuSettings->xRegionsSettings[ i ].ullPrbarEl1 ) ) )
                        {
                            xAccessGranted = pdTRUE;
                            ನಿಲ್ಲಿಸು;
                        }
                    }
                }
            }
        }

        ಹಿಂತಿರುಗಿ xAccessGranted;
    }
    /*-----------------------------------------------------------*/

    ಶೂನ್ಯ vSystemCallEnter( uint64_t * pull_Privileged_Only_Task_ರಾಶಿ,
                           uint8_t uc_System_Call_ಸಂಖ್ಯೆ ) /* PRIVILEGED_FUNCTION */
    {
        #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
            ಬಾಹ್ಯ TaskHandle_t pxCurrentTCB;
        #ಇಲ್ಲದಿದ್ದರೆ
            ಬಾಹ್ಯ TaskHandle_t pxCurrentTCBs[ config_ಸಂಖ್ಯೆ_ದ_CORES ];
        #ಆದರೆ_ಅಂತ್ಯ
        ಬಾಹ್ಯ UBaseType_t uxSystemCallImplementations[ ಅಂಕೆ_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint64_t ullSystemCallLocation;  /* Address where SVC was raised. */
        __asm ಅಸ್ಥಿರ ( "MRS %0, ELR_EL1" : "=r" ( ullSystemCallLocation ) );

        #ಆದರೆ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts.
             */
            ಬಾಹ್ಯ uint64_t * __syscalls_flash_start__;
            ಬಾಹ್ಯ uint64_t * __syscalls_flash_end__;
        #ಇಲ್ಲದಿದ್ದರೆ
            /* Declaration when these variable are exported from linker scripts. */
            ಬಾಹ್ಯ uint64_t __syscalls_flash_start__[];
            ಬಾಹ್ಯ uint64_t __syscalls_flash_end__[];
        #ಆದರೆ_ಅಂತ್ಯ /* #if defined( __ARMCC_VERSION ) */

        #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );
        #ಇಲ್ಲದಿದ್ದರೆ
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCBs[ ಪೋರ್ಟ್_GET_CORE_ID_FROM_ISR() ] );
        #ಆದರೆ_ಅಂತ್ಯ

        /* Checks:
         * 1. SVC is raised from the system call section (i.e. application is
         *    not raising SVC directly).
         * 2. We do not need to check that ucSystemCallNumber is within range
         *    because the assembly SVC handler checks that before calling
         *    this function.
         */
        ಆದರೆ( ( ullSystemCallLocation >= ( uint64_t ) __syscalls_flash_start__ ) &&
            ( ullSystemCallLocation <= ( uint64_t ) __syscalls_flash_end__ ) &&
            ( uxSystemCallImplementations[ uc_System_Call_ಸಂಖ್ಯೆ ] != 0 ) )
        {
            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call.
             */
            pxMpuSettings->xSystemCallInfo.ull_Link_ರಿಜಿಸ್ಟರ್_At_System_Call_ನಮೂದು = pull_Privileged_Only_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_LR ];

            /* Capture user-mode SP at system call entry. */
            uint64_t ull_User_Sp_At_ನಮೂದು;
            __asm ಅಸ್ಥಿರ ( "MRS %0, SP_EL0" : "=r" ( ull_User_Sp_At_ನಮೂದು ) );
            pxMpuSettings->xSystemCallInfo.ull_User_SPAt_System_Call_ನಮೂದು = ull_User_Sp_At_ನಮೂದು;

            /* Setup the MPU_<API> inputs, the system call stack, and SPSR. */
            __asm ಅಸ್ಥಿರ (
                "MOV X0, %0         \n"
                "MOV X1, %1         \n"
                "MOV X2, %2         \n"
                "MOV X3, %3         \n"
                "MSR ELR_EL1, %4    \n"
                "MSR SP_EL0, %5     \n"
                "MSR SPSR_EL1, %6   \n"
                :
                : "r" ( pull_Privileged_Only_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_X0 ] ),
                  "r" ( pull_Privileged_Only_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_X1 ] ),
                  "r" ( pull_Privileged_Only_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_X2 ] ),
                  "r" ( pull_Privileged_Only_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_X3 ] ),
                  "r" ( ( uint64_t ) uxSystemCallImplementations[ uc_System_Call_ಸಂಖ್ಯೆ ] ),
                  "r" ( &( pxMpuSettings->ullContext[ MAX_CONTEXT_ಗಾತ್ರ + config_SYSTEM_CALL_ರಾಶಿ_ಗಾತ್ರ ] ) ),
                  "r" ( ಪೋರ್ಟ್_INITIAL_PSTATE_EL1 )
                : "memory", "x0", "x1", "x2", "x3"
            );
        }
    }
    /*-----------------------------------------------------------*/

    ಶೂನ್ಯ vRequestSystemCallExit( ಶೂನ್ಯ ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm ಅಸ್ಥಿರ ( "svc %0 \n" ::"i" ( ಪೋರ್ಟ್_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }
    /*-----------------------------------------------------------*/

    ಶೂನ್ಯ vSystemCallExit( uint64_t ull_System_Call_Return_ಮೌಲ್ಯ ) /* PRIVILEGED_FUNCTION */
    {
        #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
            ಬಾಹ್ಯ TaskHandle_t pxCurrentTCB;
        #ಇಲ್ಲದಿದ್ದರೆ
            ಬಾಹ್ಯ TaskHandle_t pxCurrentTCBs[ config_ಸಂಖ್ಯೆ_ದ_CORES ];
        #ಆದರೆ_ಅಂತ್ಯ
        xMPU_SETTINGS * pxMpuSettings;
        uint64_t ullSystemCallLocation; /* Address where SVC was raised. */
        __asm ಅಸ್ಥಿರ ( "MRS %0, ELR_EL1" : "=r" ( ullSystemCallLocation ) );

        #ಆದರೆ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ಬಾಹ್ಯ uint64_t * __privileged_functions_start__;
            ಬಾಹ್ಯ uint64_t * __privileged_functions_end__;
        #ಇಲ್ಲದಿದ್ದರೆ
            /* Declaration when these variable are exported from linker scripts. */
            ಬಾಹ್ಯ uint64_t __privileged_functions_start__[];
            ಬಾಹ್ಯ uint64_t __privileged_functions_end__[];
        #ಆದರೆ_ಅಂತ್ಯ /* #if defined( __ARMCC_VERSION ) */

        #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );
        #ಇಲ್ಲದಿದ್ದರೆ
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCBs[ ಪೋರ್ಟ್_GET_CORE_ID_FROM_ISR() ] );
        #ಆದರೆ_ಅಂತ್ಯ

        /* Check:
         * SVC is raised from the privileged code (i.e. application is not
         * raising SVC directly). This SVC is only raised from
         * vRequestSystemCallExit which is in the privileged code section.
         */
        ಆದರೆ( ( ullSystemCallLocation >= ( uint64_t ) __privileged_functions_start__ ) &&
            ( ullSystemCallLocation <= ( uint64_t ) __privileged_functions_end__ ) )
        {
            __asm ಅಸ್ಥಿರ (
                "MSR ELR_EL1, %0    \n" /* Return to the MPU_<API> caller. */
                "MSR SP_EL0, %1     \n" /* Restore user SP saved at syscall entry. */
                "MSR SPSR_EL1, %3   \n" /* Ensure return to EL0. */
                "MOV X0, %2         \n" /* Move the system call return value to X0. */
                :
                : "r" ( pxMpuSettings->xSystemCallInfo.ull_Link_ರಿಜಿಸ್ಟರ್_At_System_Call_ನಮೂದು ),
                  "r" ( pxMpuSettings->xSystemCallInfo.ull_User_SPAt_System_Call_ನಮೂದು ),
                  "r" ( ull_System_Call_Return_ಮೌಲ್ಯ ),
                  "r" ( ( uint64_t ) ಪೋರ್ಟ್_INITIAL_PSTATE_EL0 )
                : "memory"
            );
        }
    }
    /*-----------------------------------------------------------*/

    #ಆದರೆ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        ಶೂನ್ಯ v_ಪೋರ್ಟ್_Grant_Access_ಗಮ್ಯ_Kernel_Object( TaskHandle_t x_ಆಂತರಿಕ_Task_Handle,
                                             int32_t l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ, ul_Access_Control_List_ನಮೂದು_ಬಿಟ್;
            xMPU_SETTINGS * xTaskMpuSettings;

            /* Calculate the Access Control List entry index and bit position
             * within that entry. */
            ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object / ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );
            ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object % ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );

            xTaskMpuSettings = xTaskGetMPUSettings( x_ಆಂತರಿಕ_Task_Handle );

            /* Set the bit corresponding to the kernel object to grant access. */
            xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ ] |= ( 1U << ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ );
        }
        /*-----------------------------------------------------------*/

        ಶೂನ್ಯ v_ಪೋರ್ಟ್_Revoke_Access_ಗಮ್ಯ_Kernel_Object( TaskHandle_t x_ಆಂತರಿಕ_Task_Handle,
                                              int32_t l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ, ul_Access_Control_List_ನಮೂದು_ಬಿಟ್;
            xMPU_SETTINGS * xTaskMpuSettings;

            /* Calculate the Access Control List entry index and bit position
             * within that entry. */
            ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object / ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );
            ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object % ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );

            xTaskMpuSettings = xTaskGetMPUSettings( x_ಆಂತರಿಕ_Task_Handle );

            /* Clear the bit corresponding to the kernel object to revoke access. */
            xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ ] &= ~( 1U << ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ );
        }
        /*-----------------------------------------------------------*/

        ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( int32_t l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ, ul_Access_Control_List_ನಮೂದು_ಬಿಟ್;
            ತಳ_Type_t xAccessGranted = pdFALSE;
            ಸ್ಥಿರಾಂಕ xMPU_SETTINGS * xTaskMpuSettings;

            ಆದರೆ( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xTaskMpuSettings = xTaskGetMPUSettings( ಖಾಲಿ ); /* Calling task's MPU settings. */

                ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object / ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );
                ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object % ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );

                ಆದರೆ( ( xTaskMpuSettings->ullTaskFlags & ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG ) == ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    ಆದರೆ( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ ] & ( 1U << ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xAccessGranted;
        }
        /*-----------------------------------------------------------*/
    #ಇಲ್ಲದಿದ್ದರೆ /* configENABLE_ACCESS_CONTROL_LIST == 1 */

        ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( int32_t l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( ಶೂನ್ಯ ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            ಹಿಂತಿರುಗಿ pdTRUE;
        }
        /*-----------------------------------------------------------*/

    #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_ACCESS_CONTROL_LIST == 1 */

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configENABLE_MPU == 1 ) */

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    uint64_t ullAPSR;

    #ಆದರೆ ( configASSERT_DEFINED == 1 )
    {
        ಅಸ್ಥಿರ uint8_t uc_Original_ಆದ್ಯತೆ;
        ಅಸ್ಥಿರ uint8_t * ಸ್ಥಿರಾಂಕ puc_ಮೊದಲ_User_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್ = ( ಅಸ್ಥಿರ uint8_t * ಸ್ಥಿರಾಂಕ ) ( config_ಅಡಚಣೆ_CONTROLLER_ತಳ_ವಿಳಾಸ + ಪೋರ್ಟ್_ಅಡಚಣೆ_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್_ಸ್ಥಾನಾಂತರ );
        ಅಸ್ಥಿರ uint8_t uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ;

        /* Determine how many priority bits are implemented in the GIC.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_ಆದ್ಯತೆ = *puc_ಮೊದಲ_User_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್;

        /* Determine the number of priority bits available.  First write to
         * all possible bits. */
        *puc_ಮೊದಲ_User_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್ = ಪೋರ್ಟ್_MAX_8_ಬಿಟ್_ಮೌಲ್ಯ;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ = *puc_ಮೊದಲ_User_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್;

        /* Shift to the least significant bits. */
        ಆಗ( ( uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ & ಪೋರ್ಟ್_ಬಿಟ್_0_ಗಣ ) != ಪೋರ್ಟ್_ಬಿಟ್_0_ಗಣ )
        {
            uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ >>= ( uint8_t ) 0x01;
        }

        /* Sanity check configUNIQUE_INTERRUPT_PRIORITIES matches the read
         * value. */
        configASSERT( uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ >= ಪೋರ್ಟ್_ಅತಿಕಡಿಮೆ_ಅಡಚಣೆ_ಆದ್ಯತೆ );


        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_ಮೊದಲ_User_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್ = uc_Original_ಆದ್ಯತೆ;
    }
    #ಆದರೆ_ಅಂತ್ಯ /* configASSERT_DEFINED */

    __asm ಅಸ್ಥಿರ ( "MRS %0, CurrentEL" : "=r" ( ullAPSR ) );
    ullAPSR &= ಪೋರ್ಟ್_APSR_ಬಹುಲಕ_ಬಿಟ್ಟುಗಳು_ಮುಖವಾಡ;

    configASSERT( ullAPSR == ಪೋರ್ಟ್_EL1 );

    #ಆದರೆ ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        v_ಸಿದ್ಧತೆ_MPU();
    }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configENABLE_MPU == 1 ) */

    /* Interrupts are turned off in the CPU itself to ensure a tick does
     * not execute while the scheduler is being started.  Interrupts are
     * automatically turned back on in the CPU when the first task starts
     * executing. */
    __asm ಅಸ್ಥಿರ ( "MSR DAIFSET, #2\n"
                     "DSB SY\n"
                     "ISB SY\n" ::: "memory" );
    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )
        /* Start the timer that generates the tick ISR. */
        config_ಸಿದ್ಧತೆ_TICK_ಅಡಚಣೆ();
        uc_Primary_Core_Init_ಮುಗಿದ_Flag = 1;
        __asm ಅಸ್ಥಿರ ( "SEV                       \n"
                         "DSB SY                    \n"
                         "ISB SY                    \n"
                         ::: "memory" );
        /* Hold the primary core here until all the secondary cores are ready, this would be achieved only when
         * all elements of ucSecondaryCoresReadyFlags are set.
         */
        ಆಗ( 1 )
        {
            ತಳ_Type_t xAllCoresReady = pdTRUE;
            ಗಾಗಿ( uint8_t ucCoreID = 0; ucCoreID < ( config_ಸಂಖ್ಯೆ_ದ_CORES - 1 ); ucCoreID++ )
            {
                ಆದರೆ( ucSecondaryCoresReadyFlags[ ucCoreID ] != pdTRUE )
                {
                    xAllCoresReady = pdFALSE;
                    ನಿಲ್ಲಿಸು;
                }
            }

            ಆದರೆ ( xAllCoresReady == pdTRUE )
            {
                ನಿಲ್ಲಿಸು;
            }
        }
    #ಇಲ್ಲದಿದ್ದರೆ /* if ( configNUMBER_OF_CORES > 1 ) */
        /* Start the timer that generates the tick ISR. */
        config_ಸಿದ್ಧತೆ_TICK_ಅಡಚಣೆ();
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configNUMBER_OF_CORES > 1 ) */

    #ಆದರೆ ( configENABLE_MPU == 1 )
        xSchedulerRunning = pdTRUE;

        /* Enable the Memory Protection Unit (MPU)
         * MPU is only enabled after the primary and secondary handshakes
         * are done as to prevent inconsistent MPU regions attributes across
         * different cores resulting in unupdated values of the handshake
         * flags. 
         */
        vEnableMPU();
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configENABLE_MPU == 1 ) */

    /* Start the first task executing. */
    v_ಪೋರ್ಟ್_Restore_Task_Context();

    ಹಿಂತಿರುಗಿ 0;
}

/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
{
    /* Stub implementation for ports where there is nothing to return to
     * Artificially force an assert. */
    configASSERT( ಖಾಲಿ );
}

/*-----------------------------------------------------------*/

#ಆದರೆ  ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
    PRIVILEGED_FUNCTION ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ )
    {
        /* Mask interrupts up to the max syscall interrupt priority. */
        ux_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ();

        /* Now interrupts are disabled ullCriticalNesting can be accessed
         * directly.  Increment ullCriticalNesting to keep a count of how many times
         * portENTER_CRITICAL() has been called. */
        ullCriticalNesting++;

        /* This is not the interrupt safe version of the enter critical function so
         * assert() if it is being called from an interrupt context.  Only API
         * functions that end in "FromISR" can be used in an interrupt.  Only assert if
         * the critical nesting count is 1 to protect against recursive calls if the
         * assert function also uses a critical section. */
        ಆದರೆ( ullCriticalNesting == 1ULL )
        {
            configASSERT( ull_ಪೋರ್ಟ್_ಅಡಚಣೆ_Nesting == 0 );
        }
    }

/*-----------------------------------------------------------*/

    PRIVILEGED_FUNCTION ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ )
    {
        ಆದರೆ( ullCriticalNesting > ಪೋರ್ಟ್_NO_CRITICAL_NESTING )
        {
            /* Decrement the nesting count as the critical section is being
             * exited. */
            ullCriticalNesting--;

            /* If the nesting level has reached zero then all interrupt
             * priorities must be re-enabled. */
            ಆದರೆ( ullCriticalNesting == ಪೋರ್ಟ್_NO_CRITICAL_NESTING )
            {
                /* Critical nesting has reached zero so all interrupt priorities
                 * should be unmasked. */
                ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_PRIORITIES_ಮುಖವಾಡ();
            }
        }
    }
#ಆದರೆ_ಅಂತ್ಯ /* if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/

ಶೂನ್ಯ FreeRTOS_Tick_Handler( ಶೂನ್ಯ )
{
    /* Must be the lowest possible priority. */
    uint64_t ull_Running_ಅಡಚಣೆ_ಆದ್ಯತೆ;
    __asm ಅಸ್ಥಿರ ( "MRS %0, ICC_RPR_EL1" : "=r" ( ull_Running_ಅಡಚಣೆ_ಆದ್ಯತೆ ) );

    configASSERT( ull_Running_ಅಡಚಣೆ_ಆದ್ಯತೆ == ( ಪೋರ್ಟ್_ಅತಿಕಡಿಮೆ_USABLE_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು ) );

    /* Interrupts should not be enabled before this point. */
    #ಆದರೆ ( configASSERT_DEFINED == 1 )
    {
        uint64_t ull_ಮುಖವಾಡ_ಬಿಟ್ಟುಗಳು;

        __asm ಅಸ್ಥಿರ ( "MRS %0, DAIF" : "=r" ( ull_ಮುಖವಾಡ_ಬಿಟ್ಟುಗಳು )::"memory" );
        configASSERT( ( ull_ಮುಖವಾಡ_ಬಿಟ್ಟುಗಳು & ಪೋರ್ಟ್_DAIF_I ) != 0 );
    }
    #ಆದರೆ_ಅಂತ್ಯ /* configASSERT_DEFINED */

    /* Set interrupt mask before altering scheduler structures. The tick
     * interrupt runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value.  It is
     * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
     * updated.
     */
    UBaseType_t ux_ಅಡಚಣೆ_ಸ್ಥಿತಿ = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();

    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )
        UBaseType_t x = ಪೋರ್ಟ್_ENTER_CRITICAL_FROM_ISR();
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configNUMBER_OF_CORES > 1 ) */

    /* Increment the RTOS tick. */
    ಆದರೆ( xTaskIncrementTick() != pdFALSE )
    {
        #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
            ull_ಪೋರ್ಟ್_Yield_Required = pdTRUE;
        #ಇಲ್ಲದಿದ್ದರೆ
            ull_ಪೋರ್ಟ್_Yield_Required[ ಪೋರ್ಟ್_GET_CORE_ID_FROM_ISR() ] = pdTRUE;
        #ಆದರೆ_ಅಂತ್ಯ
    }
    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )
        ಪೋರ್ಟ್_EXIT_CRITICAL_FROM_ISR(x);
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configNUMBER_OF_CORES > 1 ) */

    /* Ensure all interrupt priorities are active again. */
    ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( ux_ಅಡಚಣೆ_ಸ್ಥಿತಿ );

    /* Ok to enable interrupts after the interrupt source has been cleared. */
    config_CLEAR_TICK_ಅಡಚಣೆ();
}

/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TASK_FPU_SUPPORT == ಪೋರ್ಟ್_TASK_NO_FPU_CONTEXT_BY_DEFAULT )

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Task_ಬಳಸುತ್ತದೆ_FPU( ಶೂನ್ಯ )
    {
        /* A task is registering the fact that it needs an FPU context.  Set the
         * FPU flag (which is saved as part of the task context). */
        #ಆದರೆ  ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
            ull_ಪೋರ್ಟ್_Task_Has_FPUContext = pdTRUE;
        #ಇಲ್ಲದಿದ್ದರೆ
            ull_ಪೋರ್ಟ್_Task_Has_FPUContext[ ಪೋರ್ಟ್_GET_CORE_ID() ] = pdTRUE;
        #ಆದರೆ_ಅಂತ್ಯ

        /* Consider initialising the FPSR here - but probably not necessary in
         * AArch64. */
    }

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TASK_FPU_SUPPORT */

/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ( UBaseType_t ux_New_ಮುಖವಾಡ_ಮೌಲ್ಯ )
{
    ಆದರೆ( ux_New_ಮುಖವಾಡ_ಮೌಲ್ಯ == ಪೋರ್ಟ್_UNMASK_ಮೌಲ್ಯ )
    {
        /* Unmask all interrupt priorities. */
        ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_PRIORITIES_ಮುಖವಾಡ();
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        __asm ಅಸ್ಥಿರ (
            "SVC %0 \n"
            :
            : "i" ( ಪೋರ್ಟ್_SVC_UNMASK_INTERRUPTS )
            : "memory"
        );
    }
}

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR( UBaseType_t ux_New_ಮುಖವಾಡ_ಮೌಲ್ಯ )
{
    __asm ಅಸ್ಥಿರ (
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
        : "r" ( ux_New_ಮುಖವಾಡ_ಮೌಲ್ಯ )
    );
}
/*-----------------------------------------------------------*/

UBaseType_t ux_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ( ಶೂನ್ಯ )
{
    UBaseType_t ullPMRValue;

    /* Use SVC so this can be called safely from EL0 tasks. */
    __asm ಅಸ್ಥಿರ (
        "svc %1        \n"
        "mov %0, x0    \n"
        : "=r" ( ullPMRValue )
        : "i" ( ಪೋರ್ಟ್_SVC_ಮುಖವಾಡ_ALL_INTERRUPTS )
        : "x0", "memory"
    );

    ಹಿಂತಿರುಗಿ ullPMRValue;
}

/* EL1/ISR variant to avoid SVC from interrupt context. */
UBaseType_t ux_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR( ಶೂನ್ಯ )
{
    UBaseType_t ullPMRValue;

    __asm ಅಸ್ಥಿರ ( "MRS %0, ICC_PMR_EL1" : "=r" ( ullPMRValue ) );

    ಆದರೆ( ullPMRValue != ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು ) )
    {
        __asm ಅಸ್ಥಿರ ( "MSR DAIFSET, #2        \n"
                         "DSB SY                 \n"
                         "ISB SY                 \n"
                         "MSR ICC_PMR_EL1, %0    \n"
                         "DSB SY                 \n"
                         "ISB SY                 \n"
                         "MSR DAIFCLR, #2        \n"
                         "DSB SY                 \n"
                         "ISB SY                 \n"
                         ::"r" ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು ) : "memory" );
    }

    ಹಿಂತಿರುಗಿ ullPMRValue;
}

/*-----------------------------------------------------------*/

#ಆದರೆ ( configASSERT_DEFINED == 1 )

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Validate_ಅಡಚಣೆ_ಆದ್ಯತೆ( ಶೂನ್ಯ )
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
        uint64_t ull_Running_ಅಡಚಣೆ_ಆದ್ಯತೆ;
        __asm ಅಸ್ಥಿರ ( "MRS %0, ICC_RPR_EL1" : "=r" ( ull_Running_ಅಡಚಣೆ_ಆದ್ಯತೆ ) );
        configASSERT( ull_Running_ಅಡಚಣೆ_ಆದ್ಯತೆ >= ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು ) );
    }

#ಆದರೆ_ಅಂತ್ಯ /* configASSERT_DEFINED */

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
 __attribute__( ( weak ) ) ಶೂನ್ಯ vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR )
{
    ( ಶೂನ್ಯ ) ulICCIAR;
    configASSERT( ( ಅಸ್ಥಿರ ಶೂನ್ಯ * ) ಖಾಲಿ );
}

/*-----------------------------------------------------------*/

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )

    /* Which core owns the lock? Keep in privileged, shareable RAM. */
    PRIVILEGED_ದತ್ತಾಂಶ ಅಸ್ಥಿರ uint64_t ullOwnedByCore[ ಪೋರ್ಟ್_MAX_CORE_ಎಣಿಕೆ ];
    /* Lock count a core owns. */
    PRIVILEGED_ದತ್ತಾಂಶ ಅಸ್ಥಿರ uint64_t ull_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ e_ಬೀಗ_ಎಣಿಕೆ ];
    /* Index 0 is used for ISR lock and Index 1 is used for task lock. */
    PRIVILEGED_ದತ್ತಾಂಶ uint32_t ul_Gate_ಶಬ್ದ[ e_ಬೀಗ_ಎಣಿಕೆ ];

    ಶೂನ್ಯ v_ಅಡಚಣೆ_Core( uint32_t ul_ಅಡಚಣೆ_ID, uint8_t ucCoreID )
    {
        uint64_t ulRegVal = 0;
        uint32_t ul_Core_ಮುಖವಾಡ = ( 1UL << ucCoreID );
        ulRegVal |= ( (ul_Core_ಮುಖವಾಡ & 0xFFFF) | ( ( ul_ಅಡಚಣೆ_ID & 0xF ) << 24U ) );
        __asm ಅಸ್ಥಿರ (
            "str  x0, [ sp, #-0x10 ]!       \n"
            "mov  x0, %0                    \n"
            "svc  %1                        \n"
            "ldr  x0, [ sp ], # 0x10        \n"
            :
            : "r" ( ulRegVal ), "i" ( ಪೋರ್ಟ್_SVC_ಅಡಚಣೆ_CORE )
            : "memory", "w1"
        );
    }

/*-----------------------------------------------------------*/

    ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ prvSpinUnlock( uint32_t * ul_ಬೀಗ )
    {
        /* Conservative unlock: preserve original barriers for broad HW/FVP. */
        __asm ಅಸ್ಥಿರ (
            "dmb sy         \n"
            "mov w1, #0     \n"
            "str w1, [%x0]  \n"
            "sev            \n"
            "dsb sy         \n"
            "isb sy         \n"
            :
            : "r" ( ul_ಬೀಗ )
            : "memory", "w1"
        );
    }

/*-----------------------------------------------------------*/

    ಸ್ಥಿರ ಸಾಲೊಳಗೆ uint32_t prvSpinTrylock( uint32_t * ul_ಬೀಗ )
    {
        /*
         * Conservative LDXR/STXR trylock:
         * - Return 1 immediately if busy, clearing exclusive state (CLREX).
         * - Retry STXR only on spurious failure when observed free.
         * - DMB on success to preserve expected acquire semantics.
         */
        ನೋಂದಣಿ uint32_t ulRet;
        __asm ಅಸ್ಥಿರ (
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
            : "r" ( ul_ಬೀಗ )
            : "memory", "w1", "w2", "w3"
        );

        ಹಿಂತಿರುಗಿ ulRet;
    }

/*-----------------------------------------------------------*/

    /* Read 64b value shared between cores. */
    ಸ್ಥಿರ ಸಾಲೊಳಗೆ uint64_t prvGet64( ಅಸ್ಥಿರ uint64_t * x )
    {
        __asm( "dsb sy" );
        ಹಿಂತಿರುಗಿ *x;
    }

/*-----------------------------------------------------------*/

    /* Write 64b value shared between cores. */
    ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ prvSet64( ಅಸ್ಥಿರ uint64_t * x,
                                 uint64_t ಮೌಲ್ಯ )
    {
        *x = ಮೌಲ್ಯ;
        __asm( "dsb sy" );
    }

/*-----------------------------------------------------------*/

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Recursive_ಬೀಗ( uint8_t ucCoreID,
                             e_ಪೋರ್ಟ್_RTOSLock e_ಬೀಗ_ಅಂಕೆ,
                             ತಳ_Type_t uxAcquire )
    {
        /* Validate the core ID and lock number. */
        configASSERT( ucCoreID < ಪೋರ್ಟ್_MAX_CORE_ಎಣಿಕೆ );
        configASSERT( e_ಬೀಗ_ಅಂಕೆ < e_ಬೀಗ_ಎಣಿಕೆ );

        uint32_t ul_ಬೀಗ_ಬಿಟ್ = 1u << e_ಬೀಗ_ಅಂಕೆ;

        /* Lock acquire */
        ಆದರೆ( uxAcquire )
        {
            /* Check if spinlock is available.
             * If spinlock is not available check if the core owns the lock.
             * If the core owns the lock wait increment the lock count by the core.
             * If core does not own the lock wait for the spinlock.
             */
            ಆದರೆ( prvSpinTrylock( &ul_Gate_ಶಬ್ದ[ e_ಬೀಗ_ಅಂಕೆ ] ) != 0 )
            {
                /* Check if the core owns the spinlock. */
                ಆದರೆ( prvGet64( &ullOwnedByCore[ ucCoreID ] ) & ul_ಬೀಗ_ಬಿಟ್ )
                {
                    configASSERT( prvGet64( &ull_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ e_ಬೀಗ_ಅಂಕೆ ] ) != 255u );
                    prvSet64( &ull_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ e_ಬೀಗ_ಅಂಕೆ ], ( prvGet64( &ull_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ e_ಬೀಗ_ಅಂಕೆ ] ) + 1 ) );
                    ಹಿಂತಿರುಗಿ;
                }

                /* Preload the gate word into the cache. */
                uint32_t dummy = ul_Gate_ಶಬ್ದ[ e_ಬೀಗ_ಅಂಕೆ ];
                dummy++;

                ಆಗ( prvSpinTrylock( &ul_Gate_ಶಬ್ದ[ e_ಬೀಗ_ಅಂಕೆ ] ) != 0 )
                {
                   /* Follow Arm's recommended way of sleeping
                    * sevl is used to prime the wait loop.
                    * The first wfe wakes immediately because sevl has set the flag.
                    * Check the lock, if it's not available, issue a second wfe to sleep.
                    * This guarantees the core actually goes to sleep.
                    */
                    __asm ಅಸ್ಥಿರ (
                        "sevl            \n"
                        "1: wfe          \n"
                        "ldr w2, [%x0]   \n"
                        "cbnz w2, 1b     \n"
                        :
                        : "r" ( &ul_Gate_ಶಬ್ದ[ e_ಬೀಗ_ಅಂಕೆ ] )
                        : "memory", "w2"
                    );
                }
            }

            /* Add barrier to ensure lock is taken before we proceed. */
            __asm__ __volatile__ ( "dmb sy" ::: "memory" );

            /* Assert the lock count is 0 when the spinlock is free and is acquired. */
            configASSERT( prvGet64( &ull_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ e_ಬೀಗ_ಅಂಕೆ ] ) == 0 );

            /* Set lock count as 1. */
            prvSet64( &ull_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ e_ಬೀಗ_ಅಂಕೆ ], 1 );
            /* Set ullOwnedByCore. */
            prvSet64( &ullOwnedByCore[ ucCoreID ], ( prvGet64( &ullOwnedByCore[ ucCoreID ] ) | ul_ಬೀಗ_ಬಿಟ್ ) );
        }
        /* Lock release. */
        ಇಲ್ಲದಿದ್ದರೆ
        {
            /* Assert the lock is not free already. */
            configASSERT( ( prvGet64( &ullOwnedByCore[ ucCoreID ] ) & ul_ಬೀಗ_ಬಿಟ್ ) != 0 );
            configASSERT( prvGet64( &ull_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ e_ಬೀಗ_ಅಂಕೆ ] ) != 0 );

            /* Reduce ullRecursionCountByLock by 1. */
            prvSet64( &ull_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ e_ಬೀಗ_ಅಂಕೆ ], ( prvGet64( &ull_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ e_ಬೀಗ_ಅಂಕೆ ] ) - 1 ) );

            ಆದರೆ( !prvGet64( &ull_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ e_ಬೀಗ_ಅಂಕೆ ] ) )
            {
                prvSet64( &ullOwnedByCore[ ucCoreID ], ( prvGet64( &ullOwnedByCore[ ucCoreID ] ) & ~ul_ಬೀಗ_ಬಿಟ್ ) );
                prvSpinUnlock( &ul_Gate_ಶಬ್ದ[ e_ಬೀಗ_ಅಂಕೆ ] );
                /* Add barrier to ensure lock status is reflected before we proceed. */
                __asm__ __volatile__ ( "dmb sy" ::: "memory" );
            }
        }
    }

/*-----------------------------------------------------------*/

    uint8_t uc_ಪೋರ್ಟ್_Get_Core_ID( ಶೂನ್ಯ )
    {
        /* Use SVC to obtain the core ID in a way that is safe when called
         * from EL0 tasks. ISRs and EL1 code should use
         * ucPortGetCoreIDFromIsr()/portGET_CORE_ID_FROM_ISR().
         */
        uint8_t ucCoreID;
        __asm ಅಸ್ಥಿರ (
            "svc %1             \n"
            "mov %w0, w0        \n"
            : "=r" ( ucCoreID )
            : "i" ( ಪೋರ್ಟ್_SVC_GET_CORE_ID )
            : "x0", "memory"
        );
        ಹಿಂತಿರುಗಿ ucCoreID;
    }

/*-----------------------------------------------------------*/

    uint8_t uc_ಪೋರ್ಟ್_Get_Core_IDFrom_Isr ( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
    {
        uint64_t ullMpidrEl1;
        __asm ಅಸ್ಥಿರ ( "MRS %0, MPIDR_EL1" : "=r" ( ullMpidrEl1 ) );

        ಹಿಂತಿರುಗಿ ( uint8_t ) ( ullMpidrEl1 & 0xff );
    }

/*------------------------------------------------------------*/
    ಶೂನ್ಯ FreeRTOS_SGI_Handler( ಶೂನ್ಯ )
    {
        /* Must be the lowest possible priority. */
        uint64_t ull_Running_ಅಡಚಣೆ_ಆದ್ಯತೆ;
        __asm ಅಸ್ಥಿರ ( "MRS %0, ICC_RPR_EL1" : "=r" ( ull_Running_ಅಡಚಣೆ_ಆದ್ಯತೆ ) );

        configASSERT( ull_Running_ಅಡಚಣೆ_ಆದ್ಯತೆ == ( ಪೋರ್ಟ್_ಅತಿಕಡಿಮೆ_USABLE_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು ) );
        /* Interrupts should not be enabled before this point. */
        #ಆದರೆ ( configASSERT_DEFINED == 1 )
        {
            uint64_t ull_ಮುಖವಾಡ_ಬಿಟ್ಟುಗಳು;

            __asm ಅಸ್ಥಿರ ( "mrs %0, DAIF" : "=r" ( ull_ಮುಖವಾಡ_ಬಿಟ್ಟುಗಳು )::"memory" );
            configASSERT( ( ull_ಮುಖವಾಡ_ಬಿಟ್ಟುಗಳು & ಪೋರ್ಟ್_DAIF_I ) != 0 );
        }
        #ಆದರೆ_ಅಂತ್ಯ /* configASSERT_DEFINED */

        /* Set interrupt mask before altering scheduler structures. The SGI
         * interrupt runs at the lowest priority, so interrupts cannot already be masked,
         * so there is no need to save and restore the current mask value.  It is
         * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
         * updated.
         */
        UBaseType_t ux_ಅಡಚಣೆ_ಸ್ಥಿತಿ = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();

        UBaseType_t ux_Saved_ಅಡಚಣೆ_ಸ್ಥಿತಿ = ಪೋರ್ಟ್_ENTER_CRITICAL_FROM_ISR();
        #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
            ull_ಪೋರ್ಟ್_Yield_Required = pdTRUE;
        #ಇಲ್ಲದಿದ್ದರೆ
            ull_ಪೋರ್ಟ್_Yield_Required[ ಪೋರ್ಟ್_GET_CORE_ID_FROM_ISR() ] = pdTRUE;
        #ಆದರೆ_ಅಂತ್ಯ
        ಪೋರ್ಟ್_EXIT_CRITICAL_FROM_ISR( ux_Saved_ಅಡಚಣೆ_ಸ್ಥಿತಿ );
        ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( ux_ಅಡಚಣೆ_ಸ್ಥಿತಿ );
    }

/*-----------------------------------------------------------*/

#ಆದರೆ_ಅಂತ್ಯ /* if( configNUMBER_OF_CORES > 1 ) */
