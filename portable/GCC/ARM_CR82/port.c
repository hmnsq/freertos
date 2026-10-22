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
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers. That should only be done when
 * task.h is included from an application file. */
#परिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/* MPU includes. */
#अन्तर्भाव "mpu_wrappers.h"
#अन्तर्भाव "mpu_syscall_numbers.h"

#अपरिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#यदि_अपरिभाषितम् config_व्यवधानम्_CONTROLLER_आधारः_स्थानाङ्कः
    #दोषः config_व्यवधानम्_CONTROLLER_आधारः_स्थानाङ्कः must be defined.  Refer गन्तव्यम् Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#यदि_अन्तः

#यदि_अपरिभाषितम् config_व्यवधानम्_CONTROLLER_CPU_INTERFACE_विस्थापनम्
    #दोषः config_व्यवधानम्_CONTROLLER_CPU_INTERFACE_विस्थापनम् must be defined.  Refer गन्तव्यम् Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#यदि_अन्तः

#यदि_अपरिभाषितम् config_UNIQUE_व्यवधानम्_PRIORITIES
    #दोषः config_UNIQUE_व्यवधानम्_PRIORITIES must be defined.  Refer गन्तव्यम् Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#यदि_अन्तः

#यदि_अपरिभाषितम् config_सज्जता_TICK_व्यवधानम्
    #दोषः config_सज्जता_TICK_व्यवधानम्() must be defined.  Refer गन्तव्यम् Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#यदि_अन्तः /* configSETUP_TICK_INTERRUPT */

#यदि_अपरिभाषितम् config_MAX_API_CALL_व्यवधानम्_प्राथमिकता
    #दोषः config_MAX_API_CALL_व्यवधानम्_प्राथमिकता must be defined.  Refer गन्तव्यम् Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#यदि_अन्तः

#यदि config_MAX_API_CALL_व्यवधानम्_प्राथमिकता == 0
    #दोषः "configMAX_API_CALL_INTERRUPT_PRIORITY must not be set to 0"
#यदि_अन्तः

#यदि config_MAX_API_CALL_व्यवधानम्_प्राथमिकता > config_UNIQUE_व्यवधानम्_PRIORITIES
    #दोषः "configMAX_API_CALL_INTERRUPT_PRIORITY must be less than or equal to configUNIQUE_INTERRUPT_PRIORITIES as the lower the numeric priority value the higher the logical interrupt priority"
#यदि_अन्तः

#यदि config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #यदि ( configMAX_PRIORITIES > 32 )
        #दोषः "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 different priorities as tasks that share a priority will time slice."
    #यदि_अन्तः
#यदि_अन्तः /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#यदि config_MAX_API_CALL_व्यवधानम्_प्राथमिकता <= ( config_UNIQUE_व्यवधानम्_PRIORITIES / 2 )
    #दोषः "configMAX_API_CALL_INTERRUPT_PRIORITY must be greater than ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )"
#यदि_अन्तः

#यदि_अपरिभाषितम् config_CLEAR_TICK_व्यवधानम्
    #दोषः config_CLEAR_TICK_व्यवधानम् must be defined अन्तर् FreeRTOSConfig.h गन्तव्यम् clear which ever व्यवधानम् was प्रयुक्तम् गन्तव्यम् generate the tick व्यवधानम्.
#यदि_अन्तः

#यदि config_सङ्ख्या_सम्बन्धि_CORES < 1
    #दोषः config_सङ्ख्या_सम्बन्धि_CORES must be समुच्चयः गन्तव्यम् 1 or greater.  If the application is not using गुणजः_2 cores then समुच्चयः config_सङ्ख्या_सम्बन्धि_CORES गन्तव्यम् 1.
#यदि_अन्तः /* configNUMBER_OF_CORES < 1 */

#यदि_अपरिभाषितम् configENABLE_MPU
    #दोषः configENABLE_MPU must be defined अन्तर् FreeRTOSConfig.h. समुच्चयः_2 configENABLE_MPU गन्तव्यम् 1 गन्तव्यम् enable the MPU or 0 गन्तव्यम् disable the MPU.
#यदि_अन्तः /* #if ( configENABLE_MPU == 1 ) */

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 != 0) )
    #दोषः Arm Cortex-R82 पत्तनम् supports only MPU Wrapper V2.
#यदि_अन्तः /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 != 0) */

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#परिभाषय पत्तनम्_NO_CRITICAL_NESTING    ( ( size_t ) 0 )

/* Macro to unmask all interrupt priorities. */
#परिभाषय पत्तनम्_CLEAR_व्यवधानम्_PRIORITIES_आवरणम्()    __asm चञ्चल ( "SVC %0" : : "i" ( पत्तनम्_SVC_UNMASK_ALL_INTERRUPTS ) : "memory" )

/* Macro to unmask all interrupt priorities from EL1. */
#परिभाषय पत्तनम्_CLEAR_व्यवधानम्_PRIORITIES_आवरणम्_FROM_EL1()  \
{                                                       \
    __asm चञ्चल (                                    \
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
    : "i" ( पत्तनम्_UNMASK_मानम् )                          \
    );                                                  \
}

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#परिभाषय पत्तनम्_NO_FLOATING_POINT_CONTEXT    ( ( राशिः_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#परिभाषय पत्तनम्_SP_ELx                       ( ( राशिः_Type_t ) 0x01 )
#परिभाषय पत्तनम्_SP_EL0                       ( ( राशिः_Type_t ) 0x00 )
#परिभाषय पत्तनम्_EL1                          ( ( राशिः_Type_t ) 0x04 )
#परिभाषय पत्तनम्_EL0                          ( ( राशिः_Type_t ) 0x00 )

#परिभाषय पत्तनम्_INITIAL_PSTATE_EL0           ( पत्तनम्_EL0 | पत्तनम्_SP_EL0 )
#परिभाषय पत्तनम्_INITIAL_PSTATE_EL1           ( पत्तनम्_EL1 | पत्तनम्_SP_EL0 )

/* Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero. */
#परिभाषय पत्तनम्_द्विमान_POINT_द्वयङ्काः            ( ( uint8_t ) 0x03 )

/* Masks all bits in the APSR other than the mode bits. */
#परिभाषय पत्तनम्_APSR_बहुलकम्_द्वयङ्काः_आवरणम्          ( 0x0C )

/* The I bit in the DAIF bits. */
#परिभाषय पत्तनम्_DAIF_I                       ( 0x80 )

#परिभाषय पत्तनम्_MAX_8_BIT_मानम्              ( ( uint8_t ) 0xff )
#परिभाषय पत्तनम्_BIT_0_समुच्चयः                    ( ( uint8_t ) 0x01 )

/* The space on the stack required to hold the FPU registers.
 * There are 32 128-bit plus 2 64-bit status registers. */
#परिभाषय पत्तनम्_FPU_पञ्जिकाकोशः_शब्दाः           ( ( 32 * 2 ) + 2 )

/*-----------------------------------------------------------*/

#यदि ( configENABLE_MPU == 1 )

    /**
     * @brief Setup the Memory Protection Unit (MPU).
     */
    PRIVILEGED_FUNCTION शून्य v_सज्जता_MPU( शून्य );

    /**
     * @brief Enable the Memory Protection Unit (MPU).
     */
    PRIVILEGED_FUNCTION शून्य vEnableMPU( शून्य );

    /**
     * @brief Called from an ISR and returns the core ID the code is executing on.
     *
     * @return uint8_t The core ID.
     */
    PRIVILEGED_FUNCTION uint8_t uc_पत्तनम्_Get_Core_IDFrom_Isr( शून्य );

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    PRIVILEGED_FUNCTION आधारः_Type_t x_पत्तनम्_Is_Task_Privileged( शून्य );

    /**
     * @brief Extract MPU region's access permissions from the Protection Region Base Address Register
     * (PRBAR_EL1) value.
     *
     * @param ullPrbarEl1Value PRBAR_EL1 value for the MPU region.
     *
     * @return uint32_t Access permissions.
     */
    PRIVILEGED_FUNCTION स्थिर uint32_t prvGetRegionAccessPermissions( uint64_t ull_Prbar_El1_मानम् );

    /**
     * @brief Does the necessary work to enter a system call.
     *
     * @param pullPrivilegedOnlyTaskStack The task's privileged SP when the SVC was raised.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    PRIVILEGED_FUNCTION शून्य vSystemCallEnter( uint64_t * pull_Privileged_Only_Task_राशिः,
                                               uint8_t uc_System_Call_सङ्ख्या );

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    PRIVILEGED_FUNCTION __attribute__( ( naked ) ) शून्य vRequestSystemCallExit( शून्य );

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param ullSystemCallReturnValue The actual system call return value.
     */
    PRIVILEGED_FUNCTION शून्य vSystemCallExit( uint64_t ull_System_Call_Return_मानम् );

#यदि_अन्तः /* #if ( configENABLE_MPU == 1 ) */

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
बाह्य शून्य v_पत्तनम्_Restore_Task_Context( शून्य );
बाह्य शून्य vGIC_EnableIRQ( uint32_t ul_व्यवधानम्_ID );
बाह्य शून्य v_GIC_समुच्चयः_प्राथमिकता( uint32_t ul_व्यवधानम्_ID, uint32_t ul_प्राथमिकता );
बाह्य शून्य v_GIC_Power_ऊर्ध्वम्_Redistributor( शून्य );
बाह्य शून्य vGIC_EnableCPUInterface( शून्य );

/*-----------------------------------------------------------*/

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )

    PRIVILEGED_दत्त चञ्चल uint64_t ullCriticalNesting = 0ULL;

    /* Saved as part of the task context. If ullPortTaskHasFPUContext is non-zero
     * then floating point context must be saved and restored for the task. */
    PRIVILEGED_दत्त uint64_t ull_पत्तनम्_Task_Has_FPUContext = pdFALSE;

    /* Set to 1 to pend a context switch from an ISR. */
    PRIVILEGED_दत्त uint64_t ull_पत्तनम्_Yield_Required = pdFALSE;

    /* Counts the interrupt nesting depth. A context switch is only performed if
     * if the nesting depth is 0. */
    PRIVILEGED_दत्त uint64_t ull_पत्तनम्_व्यवधानम्_Nesting = 0;

#अन्यथा /* #if ( configNUMBER_OF_CORES == 1 ) */
    PRIVILEGED_दत्त चञ्चल uint64_t ullCriticalNestings[ config_सङ्ख्या_सम्बन्धि_CORES ] = { 0 };

    /* Flags to check if the secondary cores are ready. */
    PRIVILEGED_दत्त चञ्चल uint8_t ucSecondaryCoresReadyFlags[ config_सङ्ख्या_सम्बन्धि_CORES - 1 ] = { 0 };

    /* Flag to signal that the primary core has done all the shared initialisations. */
    PRIVILEGED_दत्त चञ्चल uint8_t uc_Primary_Core_Init_समाप्तम्_Flag = 0;

    /* Saved as part of the task context. If ullPortTaskHasFPUContext is non-zero
     * then floating point context must be saved and restored for the task. */
    PRIVILEGED_दत्त uint64_t ull_पत्तनम्_Task_Has_FPUContext[ config_सङ्ख्या_सम्बन्धि_CORES ] = { pdFALSE };

    /* Set to 1 to pend a context switch from an ISR. */
    PRIVILEGED_दत्त uint64_t ull_पत्तनम्_Yield_Required[ config_सङ्ख्या_सम्बन्धि_CORES ] = { pdFALSE };

    /* Counts the interrupt nesting depth. A context switch is only performed if
     * if the nesting depth is 0. */
    PRIVILEGED_दत्त uint64_t ull_पत्तनम्_व्यवधानम्_Nestings[ config_सङ्ख्या_सम्बन्धि_CORES ] = { 0 };

#यदि_अन्तः /* #if ( configNUMBER_OF_CORES == 1 ) */

#यदि ( configENABLE_MPU == 1 )
    /* Set to pdTRUE when the scheduler is started. */
    PRIVILEGED_दत्त स्थिर आधारः_Type_t xSchedulerRunning = pdFALSE;
#यदि_अन्तः /* ( configENABLE_MPU == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configENABLE_MPU == 1 )

    राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                         TaskFunction_t px_संहिता,
                                         शून्य * pvParameters,
                                         आधारः_Type_t x_सततम्_Privileged,
                                         xMPU_SETTINGS * xMPUSettings )
    {
        uint32_t ul_सूचकांक = 0;

        /* Layout must match portRESTORE_CONTEXT pop order (descending stack):
         * 1) FPU flag, 2) Critical nesting, 3) Optional FPU save area,
         * 4) ELR (PC), 5) SPSR (PSTATE), 6) GPRs in restore order pairs.
         */

        /* 1) FPU flag and 2) Critical nesting. */
        #यदि ( configUSE_TASK_FPU_SUPPORT == पत्तनम्_TASK_NO_FPU_CONTEXT_BY_DEFAULT )
            xMPUSettings->ullContext[ ul_सूचकांक++ ] = पत्तनम्_NO_FLOATING_POINT_CONTEXT; /* FPU flag */
            xMPUSettings->ullContext[ ul_सूचकांक++ ] = पत्तनम्_NO_CRITICAL_NESTING;       /* Critical nesting */
        #नोचेद्यदि ( configUSE_TASK_FPU_SUPPORT == पत्तनम्_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
            xMPUSettings->ullContext[ ul_सूचकांक++ ] = pdTRUE;                        /* FPU flag */
            xMPUSettings->ullContext[ ul_सूचकांक++ ] = पत्तनम्_NO_CRITICAL_NESTING;       /* Critical nesting */
            #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
                ull_पत्तनम्_Task_Has_FPUContext = pdTRUE;
            #अन्यथा
                ull_पत्तनम्_Task_Has_FPUContext[ पत्तनम्_GET_CORE_ID() ] = pdTRUE;
            #यदि_अन्तः
        #अन्यथा
            #दोषः "Invalid configUSE_TASK_FPU_SUPPORT setting - must be 1 or 2."
        #यदि_अन्तः

        /* 3) Optional FPU save area immediately after the flag+critical pair. */
        #यदि ( configUSE_TASK_FPU_SUPPORT == पत्तनम्_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
            स्मृतिं_पूरय( &xMPUSettings->ullContext[ ul_सूचकांक ], 0x00, पत्तनम्_FPU_पञ्जिकाकोशः_शब्दाः * परिमाण( राशिः_Type_t ) );
            ul_सूचकांक += पत्तनम्_FPU_पञ्जिकाकोशः_शब्दाः;
        #यदि_अन्तः

        /* 4) ELR (PC) and 5) SPSR (PSTATE). */
        xMPUSettings->ullContext[ ul_सूचकांक++ ] = ( राशिः_Type_t ) px_संहिता; /* ELR */

        यदि( x_सततम्_Privileged == pdTRUE )
        {
            xMPUSettings->ullContext[ ul_सूचकांक++ ] = पत्तनम्_INITIAL_PSTATE_EL1;    /* SPSR */
        }
        अन्यथा
        {
            xMPUSettings->ullContext[ ul_सूचकांक++ ] = पत्तनम्_INITIAL_PSTATE_EL0;    /* SPSR */
        }

        /* 6) General-purpose registers in the order expected by restoreallgpregisters. */
        xMPUSettings->ullContext[ ul_सूचकांक++ ] = ( राशिः_Type_t ) 0x00;         /* X30 (LR) */
        xMPUSettings->ullContext[ ul_सूचकांक++ ] = ( राशिः_Type_t ) 0x00;         /* XZR (dummy) */

        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x2828282828282828ULL;        /* X28 */
        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x2929292929292929ULL;        /* X29 */

        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x2626262626262626ULL;        /* X26 */
        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x2727272727272727ULL;        /* X27 */

        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x2424242424242424ULL;        /* X24 */
        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x2525252525252525ULL;        /* X25 */

        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x2222222222222222ULL;        /* X22 */
        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x2323232323232323ULL;        /* X23 */

        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x2020202020202020ULL;        /* X20 */
        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x2121212121212121ULL;        /* X21 */

        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x1818181818181818ULL;        /* X18 */
        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x1919191919191919ULL;        /* X19 */

        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x1616161616161616ULL;        /* X16 */
        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x1717171717171717ULL;        /* X17 */

        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x1414141414141414ULL;        /* X14 */
        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x1515151515151515ULL;        /* X15 */

        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x1212121212121212ULL;        /* X12 */
        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x1313131313131313ULL;        /* X13 */

        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x1010101010101010ULL;        /* X10 */
        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x1111111111111111ULL;        /* X11 */

        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x0808080808080808ULL;        /* X8 */
        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x0909090909090909ULL;        /* X9 */

        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x0606060606060606ULL;        /* X6 */
        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x0707070707070707ULL;        /* X7 */

        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x0404040404040404ULL;        /* X4 */
        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x0505050505050505ULL;        /* X5 */

        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x0202020202020202ULL;        /* X2 */
        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x0303030303030303ULL;        /* X3 */

        xMPUSettings->ullContext[ ul_सूचकांक++ ] = ( राशिः_Type_t ) pvParameters; /* X0 */
        xMPUSettings->ullContext[ ul_सूचकांक++ ] = 0x0101010101010101ULL;        /* X1 */

        यदि( x_सततम्_Privileged == pdTRUE )
        {
            xMPUSettings->ullTaskFlags |= पत्तनम्_TASK_IS_PRIVILEGED_FLAG;
        }
        अन्यथा
        {
            xMPUSettings->ullTaskFlags &= ( ~पत्तनम्_TASK_IS_PRIVILEGED_FLAG );
        }

        xMPUSettings->ullTaskUnprivilegedSP = ( ( uint64_t ) px_शिखरम्_सम्बन्धि_राशिः & पत्तनम्_MPU_PRBAR_EL1_स्थानाङ्कः_आवरणम् );

        प्रत्यागम &( xMPUSettings->ullContext[ 0 ] );
    }

#अन्यथा /* #if ( configENABLE_MPU == 1 ) */

    /*
    * See header file for description.
    */
    राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                         TaskFunction_t px_संहिता,
                                         शून्य * pvParameters )
    {
        /* Setup the initial stack of the task.  The stack is set exactly as
        * expected by the portRESTORE_CONTEXT() macro. */

        /* First all the general purpose registers. */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x0101010101010101ULL;        /* R1 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) pvParameters; /* R0 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x0303030303030303ULL;        /* R3 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x0202020202020202ULL;        /* R2 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x0505050505050505ULL;        /* R5 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x0404040404040404ULL;        /* R4 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x0707070707070707ULL;        /* R7 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x0606060606060606ULL;        /* R6 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x0909090909090909ULL;        /* R9 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x0808080808080808ULL;        /* R8 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x1111111111111111ULL;        /* R11 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x1010101010101010ULL;        /* R10 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x1313131313131313ULL;        /* R13 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x1212121212121212ULL;        /* R12 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x1515151515151515ULL;        /* R15 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x1414141414141414ULL;        /* R14 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x1717171717171717ULL;        /* R17 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x1616161616161616ULL;        /* R16 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x1919191919191919ULL;        /* R19 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x1818181818181818ULL;        /* R18 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x2121212121212121ULL;        /* R21 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x2020202020202020ULL;        /* R20 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x2323232323232323ULL;        /* R23 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x2222222222222222ULL;        /* R22 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x2525252525252525ULL;        /* R25 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x2424242424242424ULL;        /* R24 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x2727272727272727ULL;        /* R27 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x2626262626262626ULL;        /* R26 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x2929292929292929ULL;        /* R29 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = 0x2828282828282828ULL;        /* R28 */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x00;         /* XZR - has no effect, used so there are an even number of registers. */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x00;         /* R30 - procedure call link register. */

        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_PSTATE_EL0;

        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) px_संहिता; /* Exception return address. */

        #यदि ( configUSE_TASK_FPU_SUPPORT == पत्तनम्_TASK_NO_FPU_CONTEXT_BY_DEFAULT )
        {
            /* The task will start with a critical nesting count of 0 as interrupts are
            * enabled. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_NO_CRITICAL_NESTING;

            /* The task will start without a floating point context.  A task that
            * uses the floating point hardware must call vPortTaskUsesFPU() before
            * executing any floating point instructions. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_NO_FLOATING_POINT_CONTEXT;
        }
        #नोचेद्यदि ( configUSE_TASK_FPU_SUPPORT == पत्तनम्_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
        {
            /* The task will start with a floating point context.  Leave enough
            * space for the registers - and ensure they are initialised to 0. */
            px_शिखरम्_सम्बन्धि_राशिः -= पत्तनम्_FPU_पञ्जिकाकोशः_शब्दाः;
            स्मृतिं_पूरय( px_शिखरम्_सम्बन्धि_राशिः, 0x00, पत्तनम्_FPU_पञ्जिकाकोशः_शब्दाः * परिमाण( राशिः_Type_t ) );

            /* The task will start with a critical nesting count of 0 as interrupts are
            * enabled. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_NO_CRITICAL_NESTING;

            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = pdTRUE;
            #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
            ull_पत्तनम्_Task_Has_FPUContext = pdTRUE;
            #अन्यथा
            ull_पत्तनम्_Task_Has_FPUContext[ पत्तनम्_GET_CORE_ID() ] = pdTRUE;
            #यदि_अन्तः
        }
        #अन्यथा /* if ( configUSE_TASK_FPU_SUPPORT == portTASK_NO_FPU_CONTEXT_BY_DEFAULT ) */
        {
            #दोषः "Invalid configUSE_TASK_FPU_SUPPORT setting - configUSE_TASK_FPU_SUPPORT must be set to 1, 2, or left undefined."
        }
        #यदि_अन्तः /* if ( configUSE_TASK_FPU_SUPPORT == portTASK_NO_FPU_CONTEXT_BY_DEFAULT ) */

        प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;

    }

#यदि_अन्तः /* #if ( configENABLE_MPU == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configENABLE_MPU == 1 )

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
    शून्य v_पत्तनम्_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ध्रुव संरचना x_स्मृतिः_REGION * ध्रुव xRegions,
                                    राशिः_Type_t * px_Bottom_सम्बन्धि_राशिः,
                                    राशिः_Type_t x_राशिः_गभीरता )  /* PRIVILEGED_FUNCTION */
    {
        uint64_t ull_Region_Start_स्थानाङ्कः, ull_Region_अन्तः_स्थानाङ्कः;
        uint8_t  uc_सूचकांक = 0, uc_Region_सङ्ख्या;

        #यदि defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            बाह्य uint64_t * __privileged_sram_start__;
            बाह्य uint64_t * __privileged_sram_end__;
        #अन्यथा
            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint64_t __privileged_sram_start__[];
            बाह्य uint64_t __privileged_sram_end__[];
        #यदि_अन्तः /* defined( __ARMCC_VERSION ) */

        /* Setup MAIR_EL1. */
        xMPUSettings->ullMairEl1 = ( ( पत्तनम्_MPU_प्रसामान्यम्_स्मृतिः_BUFFERABLE_CACHEABLE << पत्तनम्_MPU_MAIR_EL1_ATTR0_POS ) & पत्तनम्_MPU_MAIR_EL1_ATTR0_आवरणम् );
        xMPUSettings->ullMairEl1 |= ( ( पत्तनम्_MPU_DEVICE_स्मृतिः_n_Gn_RE << पत्तनम्_MPU_MAIR_EL1_ATTR1_POS ) & पत्तनम्_MPU_MAIR_EL1_ATTR1_आवरणम् );

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid. At all other
         * times the stack parameters will not be valid and it is assumed that
         * the stack region has already been configured. */
        यदि( x_राशिः_गभीरता > 0 )
        {
            ull_Region_Start_स्थानाङ्कः = ( uint64_t ) px_Bottom_सम्बन्धि_राशिः;
            ull_Region_अन्तः_स्थानाङ्कः = ( uint64_t ) px_Bottom_सम्बन्धि_राशिः + ( x_राशिः_गभीरता * ( config_राशिः_गभीरता_TYPE ) परिमाण( राशिः_Type_t ) ) - 1;

            /* If the stack is within the privileged SRAM, do not protect it
             * using a separate MPU region. This is needed because this
             * region is already protected using an MPU region and ARMv8-R does
             * not allow overlapping MPU regions.
             */
            यदि( ( ull_Region_Start_स्थानाङ्कः >= ( uint64_t ) __privileged_sram_start__ ) &&
                ( ull_Region_अन्तः_स्थानाङ्कः <= ( uint64_t ) __privileged_sram_end__ ) )
            {
                xMPUSettings->xRegionsSettings[ पत्तनम्_राशिः_REGION_सूचकांक ].ullPrbarEl1 = 0;
                xMPUSettings->xRegionsSettings[ पत्तनम्_राशिः_REGION_सूचकांक ].ullPrlarEl1 = 0;
            }
            अन्यथा
            {
                /* Define the region that allows access to the stack. */
                ull_Region_Start_स्थानाङ्कः &= पत्तनम्_MPU_PRBAR_EL1_स्थानाङ्कः_आवरणम्;
                ull_Region_अन्तः_स्थानाङ्कः &= पत्तनम्_MPU_PRLAR_EL1_स्थानाङ्कः_आवरणम्;

                xMPUSettings->xRegionsSettings[ पत्तनम्_राशिः_REGION_सूचकांक ].ullPrbarEl1 = ( ull_Region_Start_स्थानाङ्कः ) |
                                                                                 ( पत्तनम्_MPU_REGION_INNER_SHAREABLE ) |
                                                                                 ( पत्तनम्_MPU_REGION_READ_WRITE ) |
                                                                                 ( पत्तनम्_MPU_REGION_EXECUTE_NEVER );

                xMPUSettings->xRegionsSettings[ पत्तनम्_राशिः_REGION_सूचकांक ].ullPrlarEl1 = ( ull_Region_अन्तः_स्थानाङ्कः ) |
                                                                                 ( पत्तनम्_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                                                                                 ( पत्तनम्_MPU_PRLAR_EL1_REGION_ENABLE );
            }
        }

        /* User supplied configurable regions. */
        प्रति( uc_Region_सङ्ख्या = 1; uc_Region_सङ्ख्या <= पत्तनम्_अङ्कः_CONFIGURABLE_REGIONS; uc_Region_सङ्ख्या++ )
        {
            /* If xRegions is NULL i.e. the task has not specified any MPU
             * region, the else part ensures that all the configurable MPU
             * regions are invalidated.
             * The minimum region size is 64 Bytes.
             */
            यदि( xRegions != रिक्त )
            {
                /* Configure the region only if the base address is non-NULL.
                 * The user may choose to use only a subset of the available MPU regions.
                 * This check prevents undefined regions (i.e. regions with a NULL base
                 * address) from being configured and from triggering the size-check
                 * assertion below.
                 */
                यदि ( xRegions[ uc_सूचकांक ].pv_आधारः_स्थानाङ्कः != रिक्त )
                {
                    configASSERT( xRegions[ uc_सूचकांक ].ul_दीर्घता_अन्तर्_अष्टकानि >= 64UL );

                    uint64_t ull_Prbar_El1_Reg_मानम्, ull_Prlar_El1_Reg_मानम्;

                    /* Translate the generic region definition contained in xRegions
                     * into the ARMv8-R specific MPU settings that are then stored in
                     * xMPUSettings.
                     */
                    ull_Region_Start_स्थानाङ्कः = ( ( uint64_t ) xRegions[ uc_सूचकांक ].pv_आधारः_स्थानाङ्कः ) & पत्तनम्_MPU_PRBAR_EL1_स्थानाङ्कः_आवरणम्;
                    ull_Region_अन्तः_स्थानाङ्कः = ( uint64_t ) xRegions[ uc_सूचकांक ].pv_आधारः_स्थानाङ्कः + xRegions[ uc_सूचकांक ].ul_दीर्घता_अन्तर्_अष्टकानि - 1;
                    ull_Region_अन्तः_स्थानाङ्कः &= पत्तनम्_MPU_PRLAR_EL1_स्थानाङ्कः_आवरणम्;

                    /* Checks for overlaps with another user defined regions and stack region, which are already configured. */
                    प्रति( uint8_t uc_User_Region_सङ्ख्या = 0; uc_User_Region_सङ्ख्या < पत्तनम्_अङ्कः_CONFIGURABLE_REGIONS; uc_User_Region_सङ्ख्या++ )
                    {
                        /* Check for overlap. */
                        यदि( ( पत्तनम्_IS_स्थानाङ्कः_WITHIN_RANGE( ull_Region_Start_स्थानाङ्कः,
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_सङ्ख्या ].ullPrbarEl1 & पत्तनम्_MPU_PRBAR_EL1_स्थानाङ्कः_आवरणम् ),
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_सङ्ख्या ].ullPrlarEl1 & पत्तनम्_MPU_PRLAR_EL1_स्थानाङ्कः_आवरणम् ) ) ||
                            ( पत्तनम्_IS_स्थानाङ्कः_WITHIN_RANGE( ull_Region_अन्तः_स्थानाङ्कः,
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_सङ्ख्या ].ullPrbarEl1 & पत्तनम्_MPU_PRBAR_EL1_स्थानाङ्कः_आवरणम् ),
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_सङ्ख्या ].ullPrlarEl1 & पत्तनम्_MPU_PRLAR_EL1_स्थानाङ्कः_आवरणम् ) ) ) ) )
                        {
                            /* Overlap detected - assert. */
                            configASSERT( रिक्त );
                        }
                    }

                    /* Checks for overlaps with kernel programmed regions which are already programmed as part of vSetupMPU. */
                    प्रति (uint8_t uc_Programmed_Region_सूचकांक = 0; uc_Programmed_Region_सूचकांक < 4; uc_Programmed_Region_सूचकांक++)
                    {
                        __asm चञ्चल ( "msr PRSELR_EL1, %0" : : "r" ( ( uint64_t ) uc_Programmed_Region_सूचकांक ) );

                        __asm चञ्चल ( "mrs %0, PRBAR_EL1" : "=r" ( ull_Prbar_El1_Reg_मानम् ) );
                        ull_Prbar_El1_Reg_मानम् &= पत्तनम्_MPU_PRBAR_EL1_स्थानाङ्कः_आवरणम्;

                        __asm चञ्चल ( "mrs %0, PRLAR_EL1" : "=r" ( ull_Prlar_El1_Reg_मानम् ) );
                        ull_Prlar_El1_Reg_मानम् &= पत्तनम्_MPU_PRLAR_EL1_स्थानाङ्कः_आवरणम्;

                        /* Check for overlap. */
                        यदि( ( पत्तनम्_IS_स्थानाङ्कः_WITHIN_RANGE( ull_Region_Start_स्थानाङ्कः,
                                                        ull_Prbar_El1_Reg_मानम्,
                                                        ull_Prlar_El1_Reg_मानम् ) ) ||
                            ( पत्तनम्_IS_स्थानाङ्कः_WITHIN_RANGE( ull_Region_अन्तः_स्थानाङ्कः,
                                                        ull_Prbar_El1_Reg_मानम्,
                                                        ull_Prlar_El1_Reg_मानम् ) ) )
                        {
                            /* Overlap detected - assert. */
                            configASSERT( रिक्त );
                        }
                    }

                    /* Start address. */
                    xMPUSettings->xRegionsSettings[ uc_Region_सङ्ख्या ].ullPrbarEl1 = ( ull_Region_Start_स्थानाङ्कः );

                    /* RO/RW. */
                    यदि( ( xRegions[ uc_सूचकांक ].ulParameters & tskMPU_REGION_READ_ONLY ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_सङ्ख्या ].ullPrbarEl1 |= ( पत्तनम्_MPU_REGION_READ_ONLY );
                    }
                    अन्यथा
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_सङ्ख्या ].ullPrbarEl1 |= ( पत्तनम्_MPU_REGION_READ_WRITE );
                    }

                    /* XN. */
                    यदि( ( xRegions[ uc_सूचकांक ].ulParameters & tskMPU_REGION_EXECUTE_NEVER ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_सङ्ख्या ].ullPrbarEl1 |= ( पत्तनम्_MPU_REGION_EXECUTE_NEVER );
                    }

                    /* SH. */
                    यदि( ( xRegions[ uc_सूचकांक ].ulParameters & tskMPU_REGION_INNER_SHAREABLE ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_सङ्ख्या ].ullPrbarEl1 |= ( पत्तनम्_MPU_REGION_INNER_SHAREABLE );
                    }
                    अन्यथा यदि( ( xRegions[ uc_सूचकांक ].ulParameters & tskMPU_REGION_OUTER_SHAREABLE ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_सङ्ख्या ].ullPrbarEl1 |= ( पत्तनम्_MPU_REGION_OUTER_SHAREABLE );
                    }
                    अन्यथा
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_सङ्ख्या ].ullPrbarEl1 |= ( पत्तनम्_MPU_REGION_NON_SHAREABLE );
                    }

                    /* End Address. */
                    xMPUSettings->xRegionsSettings[ uc_Region_सङ्ख्या ].ullPrlarEl1 = ( ull_Region_अन्तः_स्थानाङ्कः ) |
                                                                                ( पत्तनम्_MPU_PRLAR_EL1_REGION_ENABLE );

                    /* Normal memory/ Device memory. */
                    यदि( ( xRegions[ uc_सूचकांक ].ulParameters & tsk_MPU_REGION_DEVICE_स्मृतिः ) != 0 )
                    {
                        /* Attr1 in MAIR_EL1 is configured as device memory. */
                        xMPUSettings->xRegionsSettings[ uc_Region_सङ्ख्या ].ullPrlarEl1 |= पत्तनम्_MPU_PRLAR_EL1_ATTR_INDEX1;
                    }
                    अन्यथा
                    {
                        /* Attr0 in MAIR_EL1 is configured as normal memory. */
                        xMPUSettings->xRegionsSettings[ uc_Region_सङ्ख्या ].ullPrlarEl1 |= पत्तनम्_MPU_PRLAR_EL1_ATTR_INDEX0;
                    }
                }
            }
            अन्यथा
            {
                /* Invalidate the region. */
                xMPUSettings->xRegionsSettings[ uc_Region_सङ्ख्या ].ullPrbarEl1 = 0UL;
                xMPUSettings->xRegionsSettings[ uc_Region_सङ्ख्या ].ullPrlarEl1 = 0UL;
            }

            uc_सूचकांक++;
        }

    }
    /*-----------------------------------------------------------*/

    शून्य v_सज्जता_MPU( शून्य ) /* PRIVILEGED_FUNCTION */
    {
        #यदि defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts.
             */
            बाह्य uint64_t * __privileged_functions_start__;
            बाह्य uint64_t * __privileged_functions_end__;
            बाह्य uint64_t * __syscalls_flash_start__;
            बाह्य uint64_t * __syscalls_flash_end__;
            बाह्य uint64_t * __unprivileged_flash_start__;
            बाह्य uint64_t * __unprivileged_flash_end__;
            बाह्य uint64_t * __privileged_sram_start__;
            बाह्य uint64_t * __privileged_sram_end__;
        #अन्यथा /* if defined( __ARMCC_VERSION ) */
            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint64_t __privileged_functions_start__[];
            बाह्य uint64_t __privileged_functions_end__[];
            बाह्य uint64_t __syscalls_flash_start__[];
            बाह्य uint64_t __syscalls_flash_end__[];
            बाह्य uint64_t __unprivileged_flash_start__[];
            बाह्य uint64_t __unprivileged_flash_end__[];
            बाह्य uint64_t __privileged_sram_start__[];
            बाह्य uint64_t __privileged_sram_end__[];
        #यदि_अन्तः /* defined( __ARMCC_VERSION ) */

        /* The only permitted number of regions are 16 or 32. */
        configASSERT( ( config_योग_MPU_REGIONS == 16 ) || ( config_योग_MPU_REGIONS == 32 ) );

        /* MAIR_EL1 - Index 0. */
        uint64_t ull_Mair_El1_Reg_मानम् = ( ( पत्तनम्_MPU_प्रसामान्यम्_स्मृतिः_BUFFERABLE_CACHEABLE << पत्तनम्_MPU_MAIR_EL1_ATTR0_POS ) & पत्तनम्_MPU_MAIR_EL1_ATTR0_आवरणम् );
        /* MAIR_EL1 - Index 1. */
        ull_Mair_El1_Reg_मानम् |= ( ( पत्तनम्_MPU_DEVICE_स्मृतिः_n_Gn_RE << पत्तनम्_MPU_MAIR_EL1_ATTR1_POS ) & पत्तनम्_MPU_MAIR_EL1_ATTR1_आवरणम् );

        __asm चञ्चल ( "msr MAIR_EL1, %0" : : "r" ( ull_Mair_El1_Reg_मानम् ) );

        /* Setup privileged flash as Read Only so that privileged tasks can
         * read it but not modify.
         */
        uint64_t ull_Prselr_El1_Reg_मानम् = पत्तनम्_PRIVILEGED_FLASH_REGION;
        __asm चञ्चल ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_मानम् ) );

        uint64_t ull_Prbar_El1_Reg_मानम् = ( ( ( uint64_t ) __privileged_functions_start__ ) & पत्तनम्_MPU_PRBAR_EL1_स्थानाङ्कः_आवरणम् ) |
                                       ( पत्तनम्_MPU_REGION_NON_SHAREABLE ) |
                                       ( पत्तनम्_MPU_REGION_PRIVILEGED_READ_ONLY );
        __asm चञ्चल ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_मानम् ) );

        uint64_t ull_Prlar_El1_Reg_मानम् = ( ( ( uint64_t ) __privileged_functions_end__ ) & पत्तनम्_MPU_PRLAR_EL1_स्थानाङ्कः_आवरणम् ) |
                                       ( पत्तनम्_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                                       ( पत्तनम्_MPU_PRLAR_EL1_REGION_ENABLE );
        __asm चञ्चल ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_मानम् ) );

        /* Setup unprivileged flash as Read Only by both privileged and
         * unprivileged tasks. All tasks can read it but no-one can modify.
         */
        ull_Prselr_El1_Reg_मानम् = पत्तनम्_UNPRIVILEGED_FLASH_REGION;
        __asm चञ्चल ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_मानम् ) );

        ull_Prbar_El1_Reg_मानम् = ( ( ( uint64_t ) __unprivileged_flash_start__ ) & पत्तनम्_MPU_PRBAR_EL1_स्थानाङ्कः_आवरणम् ) |
                              ( पत्तनम्_MPU_REGION_NON_SHAREABLE ) |
                              ( पत्तनम्_MPU_REGION_READ_ONLY );
        __asm चञ्चल ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_मानम् ) );

        ull_Prlar_El1_Reg_मानम् = ( ( ( uint64_t ) __unprivileged_flash_end__ ) & पत्तनम्_MPU_PRLAR_EL1_स्थानाङ्कः_आवरणम् ) |
                              ( पत्तनम्_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                              ( पत्तनम्_MPU_PRLAR_EL1_REGION_ENABLE );
        __asm चञ्चल ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_मानम् ) );

        /* Setup unprivileged syscalls flash as Read Only by both privileged
         * and unprivileged tasks. All tasks can read it but no-one can modify.
         */
        ull_Prselr_El1_Reg_मानम् = पत्तनम्_UNPRIVILEGED_SYSCALLS_REGION;
        __asm चञ्चल ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_मानम् ) );

        ull_Prbar_El1_Reg_मानम् = ( ( ( uint64_t ) __syscalls_flash_start__ ) & पत्तनम्_MPU_PRBAR_EL1_स्थानाङ्कः_आवरणम् ) |
                              ( पत्तनम्_MPU_REGION_NON_SHAREABLE ) |
                              ( पत्तनम्_MPU_REGION_READ_ONLY );
        __asm चञ्चल ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_मानम् ) );

        ull_Prlar_El1_Reg_मानम् = ( ( ( uint64_t ) __syscalls_flash_end__ ) & पत्तनम्_MPU_PRLAR_EL1_स्थानाङ्कः_आवरणम् ) |
                              ( पत्तनम्_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                              ( पत्तनम्_MPU_PRLAR_EL1_REGION_ENABLE );
        __asm चञ्चल ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_मानम् ) );

        /* Setup RAM containing kernel data for privileged access only. */
        ull_Prselr_El1_Reg_मानम् = पत्तनम्_PRIVILEGED_RAM_REGION;
        __asm चञ्चल ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_मानम् ) );

        ull_Prbar_El1_Reg_मानम् = ( ( ( uint64_t ) __privileged_sram_start__ ) & पत्तनम्_MPU_PRBAR_EL1_स्थानाङ्कः_आवरणम् ) |
                              ( पत्तनम्_MPU_REGION_INNER_SHAREABLE ) |
                              ( पत्तनम्_MPU_REGION_PRIVILEGED_READ_WRITE ) |
                              ( पत्तनम्_MPU_REGION_EXECUTE_NEVER );
        __asm चञ्चल ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_मानम् ) );

        ull_Prlar_El1_Reg_मानम् = ( ( ( uint64_t ) __privileged_sram_end__ ) & पत्तनम्_MPU_PRLAR_EL1_स्थानाङ्कः_आवरणम् ) |
                              ( पत्तनम्_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                              ( पत्तनम्_MPU_PRLAR_EL1_REGION_ENABLE );
        __asm चञ्चल ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_मानम् ) );
    }
    /*-----------------------------------------------------------*/

    शून्य vEnableMPU( शून्य ) /* PRIVILEGED_FUNCTION */
    {
        uint64_t ull_Sctlr_El1_Reg_मानम्;

        __asm चञ्चल ( "mrs %0, SCTLR_EL1" : "=r" ( ull_Sctlr_El1_Reg_मानम् ) );
        /* Enable the MPU. Also enable privileged access to the
         * background region.
         */
        ull_Sctlr_El1_Reg_मानम् |= ( पत्तनम्_MPU_PRIV_BACKGROUND_ENABLE_BIT | पत्तनम्_MPU_ENABLE_BIT );
        __asm चञ्चल ( "msr SCTLR_EL1, %0" : : "r" ( ull_Sctlr_El1_Reg_मानम् ) );

        /* Ensure the write to SCTLR_EL1 is committed before
         * returning.
         */
        __asm चञ्चल ( "isb" );
    }
    /*-----------------------------------------------------------*/

    आधारः_Type_t x_पत्तनम्_Is_Task_Privileged( शून्य ) /* PRIVILEGED_FUNCTION */
    {
        आधारः_Type_t xTaskIsPrivileged = pdFALSE;

        #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
            बाह्य TaskHandle_t pxCurrentTCB;
            xMPU_SETTINGS * pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );
        #अन्यथा
            बाह्य TaskHandle_t pxCurrentTCBs[ config_सङ्ख्या_सम्बन्धि_CORES ];
            xMPU_SETTINGS * pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCBs[ पत्तनम्_GET_CORE_ID_FROM_ISR() ] );
        #यदि_अन्तः

        यदि( ( pxMpuSettings->ullTaskFlags & पत्तनम्_TASK_IS_PRIVILEGED_FLAG ) == पत्तनम्_TASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        प्रत्यागम xTaskIsPrivileged;
    }
    /*-----------------------------------------------------------*/

    स्थिर uint32_t prvGetRegionAccessPermissions( uint64_t ull_Prbar_El1_मानम् ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ulAccessPermissions = 0;

        यदि( ( ull_Prbar_El1_मानम् & पत्तनम्_MPU_PRBAR_EL1_ACCESS_PERMISSIONS_आवरणम् ) == पत्तनम्_MPU_REGION_READ_ONLY )
        {
            ulAccessPermissions = tskMPU_READ_PERMISSION;
        }

        यदि( ( ull_Prbar_El1_मानम् & पत्तनम्_MPU_PRBAR_EL1_ACCESS_PERMISSIONS_आवरणम् ) == पत्तनम्_MPU_REGION_READ_WRITE )
        {
            ulAccessPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
        }

        प्रत्यागम ulAccessPermissions;
    }
    /*-----------------------------------------------------------*/

    आधारः_Type_t x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( ध्रुव शून्य * pv_बफर,
                                                size_t x_बफर_दीर्घता,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i;
        uint64_t ull_बफर_Start_स्थानाङ्कः, ull_बफर_अन्तः_स्थानाङ्कः;
        आधारः_Type_t xAccessGranted = pdFALSE;
        ध्रुव xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( रिक्त ); /* Calling task's MPU settings. */

        यदि( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        अन्यथा यदि( ( xTaskMpuSettings->ullTaskFlags & पत्तनम्_TASK_IS_PRIVILEGED_FLAG ) == पत्तनम्_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        अन्यथा
        {
            यदि( पत्तनम्_सङ्कलय_UINT64_WILL_अतिप्रवाहः( ( ( uint64_t ) pv_बफर ), ( ( uint64_t ) x_बफर_दीर्घता - 1ULL ) ) == pdFALSE )
            {
                ull_बफर_Start_स्थानाङ्कः = ( uint64_t ) pv_बफर;
                ull_बफर_अन्तः_स्थानाङ्कः = ( ( ( uint64_t ) pv_बफर ) + ( uint64_t ) x_बफर_दीर्घता - 1ULL );

                प्रति( i = 0; i < पत्तनम्_योग_अङ्कः_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    यदि( ( xTaskMpuSettings->xRegionsSettings[ i ].ullPrlarEl1 & पत्तनम्_MPU_PRLAR_EL1_REGION_ENABLE ) == पत्तनम्_MPU_PRLAR_EL1_REGION_ENABLE )
                    {
                        यदि( पत्तनम्_IS_स्थानाङ्कः_WITHIN_RANGE( ull_बफर_Start_स्थानाङ्कः,
                                                         पत्तनम्_EXTRACT_FIRST_स्थानाङ्कः_FROM_PRBAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrbarEl1 ),
                                                         पत्तनम्_EXTRACT_चरमः_स्थानाङ्कः_FROM_PRLAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrlarEl1 ) ) &&
                            पत्तनम्_IS_स्थानाङ्कः_WITHIN_RANGE( ull_बफर_अन्तः_स्थानाङ्कः,
                                                         पत्तनम्_EXTRACT_FIRST_स्थानाङ्कः_FROM_PRBAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrbarEl1 ),
                                                         पत्तनम्_EXTRACT_चरमः_स्थानाङ्कः_FROM_PRLAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrlarEl1 ) ) &&
                            पत्तनम्_IS_AUTHORIZED( ulAccessRequested,
                                               prvGetRegionAccessPermissions( xTaskMpuSettings->xRegionsSettings[ i ].ullPrbarEl1 ) ) )
                        {
                            xAccessGranted = pdTRUE;
                            भङ्ग;
                        }
                    }
                }
            }
        }

        प्रत्यागम xAccessGranted;
    }
    /*-----------------------------------------------------------*/

    शून्य vSystemCallEnter( uint64_t * pull_Privileged_Only_Task_राशिः,
                           uint8_t uc_System_Call_सङ्ख्या ) /* PRIVILEGED_FUNCTION */
    {
        #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
            बाह्य TaskHandle_t pxCurrentTCB;
        #अन्यथा
            बाह्य TaskHandle_t pxCurrentTCBs[ config_सङ्ख्या_सम्बन्धि_CORES ];
        #यदि_अन्तः
        बाह्य UBaseType_t uxSystemCallImplementations[ अङ्कः_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint64_t ullSystemCallLocation;  /* Address where SVC was raised. */
        __asm चञ्चल ( "MRS %0, ELR_EL1" : "=r" ( ullSystemCallLocation ) );

        #यदि defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts.
             */
            बाह्य uint64_t * __syscalls_flash_start__;
            बाह्य uint64_t * __syscalls_flash_end__;
        #अन्यथा
            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint64_t __syscalls_flash_start__[];
            बाह्य uint64_t __syscalls_flash_end__[];
        #यदि_अन्तः /* #if defined( __ARMCC_VERSION ) */

        #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );
        #अन्यथा
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCBs[ पत्तनम्_GET_CORE_ID_FROM_ISR() ] );
        #यदि_अन्तः

        /* Checks:
         * 1. SVC is raised from the system call section (i.e. application is
         *    not raising SVC directly).
         * 2. We do not need to check that ucSystemCallNumber is within range
         *    because the assembly SVC handler checks that before calling
         *    this function.
         */
        यदि( ( ullSystemCallLocation >= ( uint64_t ) __syscalls_flash_start__ ) &&
            ( ullSystemCallLocation <= ( uint64_t ) __syscalls_flash_end__ ) &&
            ( uxSystemCallImplementations[ uc_System_Call_सङ्ख्या ] != 0 ) )
        {
            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call.
             */
            pxMpuSettings->xSystemCallInfo.ull_Link_पञ्जिकाकोशः_At_System_Call_प्रविष्टिः = pull_Privileged_Only_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_LR ];

            /* Capture user-mode SP at system call entry. */
            uint64_t ull_User_Sp_At_प्रविष्टिः;
            __asm चञ्चल ( "MRS %0, SP_EL0" : "=r" ( ull_User_Sp_At_प्रविष्टिः ) );
            pxMpuSettings->xSystemCallInfo.ull_User_SPAt_System_Call_प्रविष्टिः = ull_User_Sp_At_प्रविष्टिः;

            /* Setup the MPU_<API> inputs, the system call stack, and SPSR. */
            __asm चञ्चल (
                "MOV X0, %0         \n"
                "MOV X1, %1         \n"
                "MOV X2, %2         \n"
                "MOV X3, %3         \n"
                "MSR ELR_EL1, %4    \n"
                "MSR SP_EL0, %5     \n"
                "MSR SPSR_EL1, %6   \n"
                :
                : "r" ( pull_Privileged_Only_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_X0 ] ),
                  "r" ( pull_Privileged_Only_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_X1 ] ),
                  "r" ( pull_Privileged_Only_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_X2 ] ),
                  "r" ( pull_Privileged_Only_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_X3 ] ),
                  "r" ( ( uint64_t ) uxSystemCallImplementations[ uc_System_Call_सङ्ख्या ] ),
                  "r" ( &( pxMpuSettings->ullContext[ MAX_CONTEXT_आकार + config_SYSTEM_CALL_राशिः_आकार ] ) ),
                  "r" ( पत्तनम्_INITIAL_PSTATE_EL1 )
                : "memory", "x0", "x1", "x2", "x3"
            );
        }
    }
    /*-----------------------------------------------------------*/

    शून्य vRequestSystemCallExit( शून्य ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm चञ्चल ( "svc %0 \n" ::"i" ( पत्तनम्_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }
    /*-----------------------------------------------------------*/

    शून्य vSystemCallExit( uint64_t ull_System_Call_Return_मानम् ) /* PRIVILEGED_FUNCTION */
    {
        #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
            बाह्य TaskHandle_t pxCurrentTCB;
        #अन्यथा
            बाह्य TaskHandle_t pxCurrentTCBs[ config_सङ्ख्या_सम्बन्धि_CORES ];
        #यदि_अन्तः
        xMPU_SETTINGS * pxMpuSettings;
        uint64_t ullSystemCallLocation; /* Address where SVC was raised. */
        __asm चञ्चल ( "MRS %0, ELR_EL1" : "=r" ( ullSystemCallLocation ) );

        #यदि defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            बाह्य uint64_t * __privileged_functions_start__;
            बाह्य uint64_t * __privileged_functions_end__;
        #अन्यथा
            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint64_t __privileged_functions_start__[];
            बाह्य uint64_t __privileged_functions_end__[];
        #यदि_अन्तः /* #if defined( __ARMCC_VERSION ) */

        #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );
        #अन्यथा
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCBs[ पत्तनम्_GET_CORE_ID_FROM_ISR() ] );
        #यदि_अन्तः

        /* Check:
         * SVC is raised from the privileged code (i.e. application is not
         * raising SVC directly). This SVC is only raised from
         * vRequestSystemCallExit which is in the privileged code section.
         */
        यदि( ( ullSystemCallLocation >= ( uint64_t ) __privileged_functions_start__ ) &&
            ( ullSystemCallLocation <= ( uint64_t ) __privileged_functions_end__ ) )
        {
            __asm चञ्चल (
                "MSR ELR_EL1, %0    \n" /* Return to the MPU_<API> caller. */
                "MSR SP_EL0, %1     \n" /* Restore user SP saved at syscall entry. */
                "MSR SPSR_EL1, %3   \n" /* Ensure return to EL0. */
                "MOV X0, %2         \n" /* Move the system call return value to X0. */
                :
                : "r" ( pxMpuSettings->xSystemCallInfo.ull_Link_पञ्जिकाकोशः_At_System_Call_प्रविष्टिः ),
                  "r" ( pxMpuSettings->xSystemCallInfo.ull_User_SPAt_System_Call_प्रविष्टिः ),
                  "r" ( ull_System_Call_Return_मानम् ),
                  "r" ( ( uint64_t ) पत्तनम्_INITIAL_PSTATE_EL0 )
                : "memory"
            );
        }
    }
    /*-----------------------------------------------------------*/

    #यदि ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        शून्य v_पत्तनम्_Grant_Access_गन्तव्यम्_Kernel_Object( TaskHandle_t x_आन्तरिकम्_Task_Handle,
                                             int32_t l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_प्रविष्टिः_सूचकांक, ul_Access_Control_List_प्रविष्टिः_Bit;
            xMPU_SETTINGS * xTaskMpuSettings;

            /* Calculate the Access Control List entry index and bit position
             * within that entry. */
            ul_Access_Control_List_प्रविष्टिः_सूचकांक = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object / पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );
            ul_Access_Control_List_प्रविष्टिः_Bit = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object % पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );

            xTaskMpuSettings = xTaskGetMPUSettings( x_आन्तरिकम्_Task_Handle );

            /* Set the bit corresponding to the kernel object to grant access. */
            xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_प्रविष्टिः_सूचकांक ] |= ( 1U << ul_Access_Control_List_प्रविष्टिः_Bit );
        }
        /*-----------------------------------------------------------*/

        शून्य v_पत्तनम्_Revoke_Access_गन्तव्यम्_Kernel_Object( TaskHandle_t x_आन्तरिकम्_Task_Handle,
                                              int32_t l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_प्रविष्टिः_सूचकांक, ul_Access_Control_List_प्रविष्टिः_Bit;
            xMPU_SETTINGS * xTaskMpuSettings;

            /* Calculate the Access Control List entry index and bit position
             * within that entry. */
            ul_Access_Control_List_प्रविष्टिः_सूचकांक = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object / पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );
            ul_Access_Control_List_प्रविष्टिः_Bit = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object % पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );

            xTaskMpuSettings = xTaskGetMPUSettings( x_आन्तरिकम्_Task_Handle );

            /* Clear the bit corresponding to the kernel object to revoke access. */
            xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_प्रविष्टिः_सूचकांक ] &= ~( 1U << ul_Access_Control_List_प्रविष्टिः_Bit );
        }
        /*-----------------------------------------------------------*/

        आधारः_Type_t x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( int32_t l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_प्रविष्टिः_सूचकांक, ul_Access_Control_List_प्रविष्टिः_Bit;
            आधारः_Type_t xAccessGranted = pdFALSE;
            ध्रुव xMPU_SETTINGS * xTaskMpuSettings;

            यदि( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            अन्यथा
            {
                xTaskMpuSettings = xTaskGetMPUSettings( रिक्त ); /* Calling task's MPU settings. */

                ul_Access_Control_List_प्रविष्टिः_सूचकांक = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object / पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );
                ul_Access_Control_List_प्रविष्टिः_Bit = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object % पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );

                यदि( ( xTaskMpuSettings->ullTaskFlags & पत्तनम्_TASK_IS_PRIVILEGED_FLAG ) == पत्तनम्_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                अन्यथा
                {
                    यदि( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_प्रविष्टिः_सूचकांक ] & ( 1U << ul_Access_Control_List_प्रविष्टिः_Bit ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            प्रत्यागम xAccessGranted;
        }
        /*-----------------------------------------------------------*/
    #अन्यथा /* configENABLE_ACCESS_CONTROL_LIST == 1 */

        आधारः_Type_t x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( int32_t l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( शून्य ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            प्रत्यागम pdTRUE;
        }
        /*-----------------------------------------------------------*/

    #यदि_अन्तः /* configENABLE_ACCESS_CONTROL_LIST == 1 */

#यदि_अन्तः /* #if ( configENABLE_MPU == 1 ) */

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    uint64_t ullAPSR;

    #यदि ( configASSERT_DEFINED == 1 )
    {
        चञ्चल uint8_t uc_Original_प्राथमिकता;
        चञ्चल uint8_t * ध्रुव puc_First_User_प्राथमिकता_पञ्जिकाकोशः = ( चञ्चल uint8_t * ध्रुव ) ( config_व्यवधानम्_CONTROLLER_आधारः_स्थानाङ्कः + पत्तनम्_व्यवधानम्_प्राथमिकता_पञ्जिकाकोशः_विस्थापनम् );
        चञ्चल uint8_t uc_Max_प्राथमिकता_मानम्;

        /* Determine how many priority bits are implemented in the GIC.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_प्राथमिकता = *puc_First_User_प्राथमिकता_पञ्जिकाकोशः;

        /* Determine the number of priority bits available.  First write to
         * all possible bits. */
        *puc_First_User_प्राथमिकता_पञ्जिकाकोशः = पत्तनम्_MAX_8_BIT_मानम्;

        /* Read the value back to see how many bits stuck. */
        uc_Max_प्राथमिकता_मानम् = *puc_First_User_प्राथमिकता_पञ्जिकाकोशः;

        /* Shift to the least significant bits. */
        यावत्( ( uc_Max_प्राथमिकता_मानम् & पत्तनम्_BIT_0_समुच्चयः ) != पत्तनम्_BIT_0_समुच्चयः )
        {
            uc_Max_प्राथमिकता_मानम् >>= ( uint8_t ) 0x01;
        }

        /* Sanity check configUNIQUE_INTERRUPT_PRIORITIES matches the read
         * value. */
        configASSERT( uc_Max_प्राथमिकता_मानम् >= पत्तनम्_निम्नतमम्_व्यवधानम्_प्राथमिकता );


        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_First_User_प्राथमिकता_पञ्जिकाकोशः = uc_Original_प्राथमिकता;
    }
    #यदि_अन्तः /* configASSERT_DEFINED */

    __asm चञ्चल ( "MRS %0, CurrentEL" : "=r" ( ullAPSR ) );
    ullAPSR &= पत्तनम्_APSR_बहुलकम्_द्वयङ्काः_आवरणम्;

    configASSERT( ullAPSR == पत्तनम्_EL1 );

    #यदि ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        v_सज्जता_MPU();
    }
    #यदि_अन्तः /* #if ( configENABLE_MPU == 1 ) */

    /* Interrupts are turned off in the CPU itself to ensure a tick does
     * not execute while the scheduler is being started.  Interrupts are
     * automatically turned back on in the CPU when the first task starts
     * executing. */
    __asm चञ्चल ( "MSR DAIFSET, #2\n"
                     "DSB SY\n"
                     "ISB SY\n" ::: "memory" );
    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )
        /* Start the timer that generates the tick ISR. */
        config_सज्जता_TICK_व्यवधानम्();
        uc_Primary_Core_Init_समाप्तम्_Flag = 1;
        __asm चञ्चल ( "SEV                       \n"
                         "DSB SY                    \n"
                         "ISB SY                    \n"
                         ::: "memory" );
        /* Hold the primary core here until all the secondary cores are ready, this would be achieved only when
         * all elements of ucSecondaryCoresReadyFlags are set.
         */
        यावत्( 1 )
        {
            आधारः_Type_t xAllCoresReady = pdTRUE;
            प्रति( uint8_t ucCoreID = 0; ucCoreID < ( config_सङ्ख्या_सम्बन्धि_CORES - 1 ); ucCoreID++ )
            {
                यदि( ucSecondaryCoresReadyFlags[ ucCoreID ] != pdTRUE )
                {
                    xAllCoresReady = pdFALSE;
                    भङ्ग;
                }
            }

            यदि ( xAllCoresReady == pdTRUE )
            {
                भङ्ग;
            }
        }
    #अन्यथा /* if ( configNUMBER_OF_CORES > 1 ) */
        /* Start the timer that generates the tick ISR. */
        config_सज्जता_TICK_व्यवधानम्();
    #यदि_अन्तः /* if ( configNUMBER_OF_CORES > 1 ) */

    #यदि ( configENABLE_MPU == 1 )
        xSchedulerRunning = pdTRUE;

        /* Enable the Memory Protection Unit (MPU)
         * MPU is only enabled after the primary and secondary handshakes
         * are done as to prevent inconsistent MPU regions attributes across
         * different cores resulting in unupdated values of the handshake
         * flags. 
         */
        vEnableMPU();
    #यदि_अन्तः /* #if ( configENABLE_MPU == 1 ) */

    /* Start the first task executing. */
    v_पत्तनम्_Restore_Task_Context();

    प्रत्यागम 0;
}

/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य ) /* PRIVILEGED_FUNCTION */
{
    /* Stub implementation for ports where there is nothing to return to
     * Artificially force an assert. */
    configASSERT( रिक्त );
}

/*-----------------------------------------------------------*/

#यदि  ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
    PRIVILEGED_FUNCTION शून्य v_पत्तनम्_Enter_Critical( शून्य )
    {
        /* Mask interrupts up to the max syscall interrupt priority. */
        ux_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्();

        /* Now interrupts are disabled ullCriticalNesting can be accessed
         * directly.  Increment ullCriticalNesting to keep a count of how many times
         * portENTER_CRITICAL() has been called. */
        ullCriticalNesting++;

        /* This is not the interrupt safe version of the enter critical function so
         * assert() if it is being called from an interrupt context.  Only API
         * functions that end in "FromISR" can be used in an interrupt.  Only assert if
         * the critical nesting count is 1 to protect against recursive calls if the
         * assert function also uses a critical section. */
        यदि( ullCriticalNesting == 1ULL )
        {
            configASSERT( ull_पत्तनम्_व्यवधानम्_Nesting == 0 );
        }
    }

/*-----------------------------------------------------------*/

    PRIVILEGED_FUNCTION शून्य v_पत्तनम्_Exit_Critical( शून्य )
    {
        यदि( ullCriticalNesting > पत्तनम्_NO_CRITICAL_NESTING )
        {
            /* Decrement the nesting count as the critical section is being
             * exited. */
            ullCriticalNesting--;

            /* If the nesting level has reached zero then all interrupt
             * priorities must be re-enabled. */
            यदि( ullCriticalNesting == पत्तनम्_NO_CRITICAL_NESTING )
            {
                /* Critical nesting has reached zero so all interrupt priorities
                 * should be unmasked. */
                पत्तनम्_CLEAR_व्यवधानम्_PRIORITIES_आवरणम्();
            }
        }
    }
#यदि_अन्तः /* if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/

शून्य FreeRTOS_Tick_Handler( शून्य )
{
    /* Must be the lowest possible priority. */
    uint64_t ull_Running_व्यवधानम्_प्राथमिकता;
    __asm चञ्चल ( "MRS %0, ICC_RPR_EL1" : "=r" ( ull_Running_व्यवधानम्_प्राथमिकता ) );

    configASSERT( ull_Running_व्यवधानम्_प्राथमिकता == ( पत्तनम्_निम्नतमम्_USABLE_व्यवधानम्_प्राथमिकता << पत्तनम्_प्राथमिकता_सरणम् ) );

    /* Interrupts should not be enabled before this point. */
    #यदि ( configASSERT_DEFINED == 1 )
    {
        uint64_t ull_आवरणम्_द्वयङ्काः;

        __asm चञ्चल ( "MRS %0, DAIF" : "=r" ( ull_आवरणम्_द्वयङ्काः )::"memory" );
        configASSERT( ( ull_आवरणम्_द्वयङ्काः & पत्तनम्_DAIF_I ) != 0 );
    }
    #यदि_अन्तः /* configASSERT_DEFINED */

    /* Set interrupt mask before altering scheduler structures. The tick
     * interrupt runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value.  It is
     * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
     * updated.
     */
    UBaseType_t ux_व्यवधानम्_स्थितिः = पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR();

    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )
        UBaseType_t x = पत्तनम्_ENTER_CRITICAL_FROM_ISR();
    #यदि_अन्तः /* if ( configNUMBER_OF_CORES > 1 ) */

    /* Increment the RTOS tick. */
    यदि( xTaskIncrementTick() != pdFALSE )
    {
        #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
            ull_पत्तनम्_Yield_Required = pdTRUE;
        #अन्यथा
            ull_पत्तनम्_Yield_Required[ पत्तनम्_GET_CORE_ID_FROM_ISR() ] = pdTRUE;
        #यदि_अन्तः
    }
    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )
        पत्तनम्_EXIT_CRITICAL_FROM_ISR(x);
    #यदि_अन्तः /* if ( configNUMBER_OF_CORES > 1 ) */

    /* Ensure all interrupt priorities are active again. */
    पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( ux_व्यवधानम्_स्थितिः );

    /* Ok to enable interrupts after the interrupt source has been cleared. */
    config_CLEAR_TICK_व्यवधानम्();
}

/*-----------------------------------------------------------*/

#यदि ( configUSE_TASK_FPU_SUPPORT == पत्तनम्_TASK_NO_FPU_CONTEXT_BY_DEFAULT )

    शून्य v_पत्तनम्_Task_उपयुङ्क्ते_FPU( शून्य )
    {
        /* A task is registering the fact that it needs an FPU context.  Set the
         * FPU flag (which is saved as part of the task context). */
        #यदि  ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
            ull_पत्तनम्_Task_Has_FPUContext = pdTRUE;
        #अन्यथा
            ull_पत्तनम्_Task_Has_FPUContext[ पत्तनम्_GET_CORE_ID() ] = pdTRUE;
        #यदि_अन्तः

        /* Consider initialising the FPSR here - but probably not necessary in
         * AArch64. */
    }

#यदि_अन्तः /* configUSE_TASK_FPU_SUPPORT */

/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Clear_व्यवधानम्_आवरणम्( UBaseType_t ux_New_आवरणम्_मानम् )
{
    यदि( ux_New_आवरणम्_मानम् == पत्तनम्_UNMASK_मानम् )
    {
        /* Unmask all interrupt priorities. */
        पत्तनम्_CLEAR_व्यवधानम्_PRIORITIES_आवरणम्();
    }
    अन्यथा
    {
        __asm चञ्चल (
            "SVC %0 \n"
            :
            : "i" ( पत्तनम्_SVC_UNMASK_INTERRUPTS )
            : "memory"
        );
    }
}

शून्य v_पत्तनम्_Clear_व्यवधानम्_आवरणम्_From_ISR( UBaseType_t ux_New_आवरणम्_मानम् )
{
    __asm चञ्चल (
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
        : "r" ( ux_New_आवरणम्_मानम् )
    );
}
/*-----------------------------------------------------------*/

UBaseType_t ux_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्( शून्य )
{
    UBaseType_t ullPMRValue;

    /* Use SVC so this can be called safely from EL0 tasks. */
    __asm चञ्चल (
        "svc %1        \n"
        "mov %0, x0    \n"
        : "=r" ( ullPMRValue )
        : "i" ( पत्तनम्_SVC_आवरणम्_ALL_INTERRUPTS )
        : "x0", "memory"
    );

    प्रत्यागम ullPMRValue;
}

/* EL1/ISR variant to avoid SVC from interrupt context. */
UBaseType_t ux_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_From_ISR( शून्य )
{
    UBaseType_t ullPMRValue;

    __asm चञ्चल ( "MRS %0, ICC_PMR_EL1" : "=r" ( ullPMRValue ) );

    यदि( ullPMRValue != ( config_MAX_API_CALL_व्यवधानम्_प्राथमिकता << पत्तनम्_प्राथमिकता_सरणम् ) )
    {
        __asm चञ्चल ( "MSR DAIFSET, #2        \n"
                         "DSB SY                 \n"
                         "ISB SY                 \n"
                         "MSR ICC_PMR_EL1, %0    \n"
                         "DSB SY                 \n"
                         "ISB SY                 \n"
                         "MSR DAIFCLR, #2        \n"
                         "DSB SY                 \n"
                         "ISB SY                 \n"
                         ::"r" ( config_MAX_API_CALL_व्यवधानम्_प्राथमिकता << पत्तनम्_प्राथमिकता_सरणम् ) : "memory" );
    }

    प्रत्यागम ullPMRValue;
}

/*-----------------------------------------------------------*/

#यदि ( configASSERT_DEFINED == 1 )

    शून्य v_पत्तनम्_Validate_व्यवधानम्_प्राथमिकता( शून्य )
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
        uint64_t ull_Running_व्यवधानम्_प्राथमिकता;
        __asm चञ्चल ( "MRS %0, ICC_RPR_EL1" : "=r" ( ull_Running_व्यवधानम्_प्राथमिकता ) );
        configASSERT( ull_Running_व्यवधानम्_प्राथमिकता >= ( config_MAX_API_CALL_व्यवधानम्_प्राथमिकता << पत्तनम्_प्राथमिकता_सरणम् ) );
    }

#यदि_अन्तः /* configASSERT_DEFINED */

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
 __attribute__( ( weak ) ) शून्य vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR )
{
    ( शून्य ) ulICCIAR;
    configASSERT( ( चञ्चल शून्य * ) रिक्त );
}

/*-----------------------------------------------------------*/

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )

    /* Which core owns the lock? Keep in privileged, shareable RAM. */
    PRIVILEGED_दत्त चञ्चल uint64_t ullOwnedByCore[ पत्तनम्_MAX_CORE_गणनम् ];
    /* Lock count a core owns. */
    PRIVILEGED_दत्त चञ्चल uint64_t ull_Recursion_गणनम्_By_तालकम्[ e_तालकम्_गणनम् ];
    /* Index 0 is used for ISR lock and Index 1 is used for task lock. */
    PRIVILEGED_दत्त uint32_t ulGateWord[ e_तालकम्_गणनम् ];

    शून्य v_व्यवधानम्_Core( uint32_t ul_व्यवधानम्_ID, uint8_t ucCoreID )
    {
        uint64_t ulRegVal = 0;
        uint32_t ul_Core_आवरणम् = ( 1UL << ucCoreID );
        ulRegVal |= ( (ul_Core_आवरणम् & 0xFFFF) | ( ( ul_व्यवधानम्_ID & 0xF ) << 24U ) );
        __asm चञ्चल (
            "str  x0, [ sp, #-0x10 ]!       \n"
            "mov  x0, %0                    \n"
            "svc  %1                        \n"
            "ldr  x0, [ sp ], # 0x10        \n"
            :
            : "r" ( ulRegVal ), "i" ( पत्तनम्_SVC_व्यवधानम्_CORE )
            : "memory", "w1"
        );
    }

/*-----------------------------------------------------------*/

    स्थिर अन्तःस्थ शून्य prvSpinUnlock( uint32_t * ul_तालकम् )
    {
        /* Conservative unlock: preserve original barriers for broad HW/FVP. */
        __asm चञ्चल (
            "dmb sy         \n"
            "mov w1, #0     \n"
            "str w1, [%x0]  \n"
            "sev            \n"
            "dsb sy         \n"
            "isb sy         \n"
            :
            : "r" ( ul_तालकम् )
            : "memory", "w1"
        );
    }

/*-----------------------------------------------------------*/

    स्थिर अन्तःस्थ uint32_t prvSpinTrylock( uint32_t * ul_तालकम् )
    {
        /*
         * Conservative LDXR/STXR trylock:
         * - Return 1 immediately if busy, clearing exclusive state (CLREX).
         * - Retry STXR only on spurious failure when observed free.
         * - DMB on success to preserve expected acquire semantics.
         */
        पञ्जिका uint32_t ulRet;
        __asm चञ्चल (
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
            : "r" ( ul_तालकम् )
            : "memory", "w1", "w2", "w3"
        );

        प्रत्यागम ulRet;
    }

/*-----------------------------------------------------------*/

    /* Read 64b value shared between cores. */
    स्थिर अन्तःस्थ uint64_t prvGet64( चञ्चल uint64_t * x )
    {
        __asm( "dsb sy" );
        प्रत्यागम *x;
    }

/*-----------------------------------------------------------*/

    /* Write 64b value shared between cores. */
    स्थिर अन्तःस्थ शून्य prvSet64( चञ्चल uint64_t * x,
                                 uint64_t मानम् )
    {
        *x = मानम्;
        __asm( "dsb sy" );
    }

/*-----------------------------------------------------------*/

    शून्य v_पत्तनम्_Recursive_तालकम्( uint8_t ucCoreID,
                             e_पत्तनम्_RTOSLock e_तालकम्_अङ्कः,
                             आधारः_Type_t uxAcquire )
    {
        /* Validate the core ID and lock number. */
        configASSERT( ucCoreID < पत्तनम्_MAX_CORE_गणनम् );
        configASSERT( e_तालकम्_अङ्कः < e_तालकम्_गणनम् );

        uint32_t ul_तालकम्_Bit = 1u << e_तालकम्_अङ्कः;

        /* Lock acquire */
        यदि( uxAcquire )
        {
            /* Check if spinlock is available.
             * If spinlock is not available check if the core owns the lock.
             * If the core owns the lock wait increment the lock count by the core.
             * If core does not own the lock wait for the spinlock.
             */
            यदि( prvSpinTrylock( &ulGateWord[ e_तालकम्_अङ्कः ] ) != 0 )
            {
                /* Check if the core owns the spinlock. */
                यदि( prvGet64( &ullOwnedByCore[ ucCoreID ] ) & ul_तालकम्_Bit )
                {
                    configASSERT( prvGet64( &ull_Recursion_गणनम्_By_तालकम्[ e_तालकम्_अङ्कः ] ) != 255u );
                    prvSet64( &ull_Recursion_गणनम्_By_तालकम्[ e_तालकम्_अङ्कः ], ( prvGet64( &ull_Recursion_गणनम्_By_तालकम्[ e_तालकम्_अङ्कः ] ) + 1 ) );
                    प्रत्यागम;
                }

                /* Preload the gate word into the cache. */
                uint32_t dummy = ulGateWord[ e_तालकम्_अङ्कः ];
                dummy++;

                यावत्( prvSpinTrylock( &ulGateWord[ e_तालकम्_अङ्कः ] ) != 0 )
                {
                   /* Follow Arm's recommended way of sleeping
                    * sevl is used to prime the wait loop.
                    * The first wfe wakes immediately because sevl has set the flag.
                    * Check the lock, if it's not available, issue a second wfe to sleep.
                    * This guarantees the core actually goes to sleep.
                    */
                    __asm चञ्चल (
                        "sevl            \n"
                        "1: wfe          \n"
                        "ldr w2, [%x0]   \n"
                        "cbnz w2, 1b     \n"
                        :
                        : "r" ( &ulGateWord[ e_तालकम्_अङ्कः ] )
                        : "memory", "w2"
                    );
                }
            }

            /* Add barrier to ensure lock is taken before we proceed. */
            __asm__ __volatile__ ( "dmb sy" ::: "memory" );

            /* Assert the lock count is 0 when the spinlock is free and is acquired. */
            configASSERT( prvGet64( &ull_Recursion_गणनम्_By_तालकम्[ e_तालकम्_अङ्कः ] ) == 0 );

            /* Set lock count as 1. */
            prvSet64( &ull_Recursion_गणनम्_By_तालकम्[ e_तालकम्_अङ्कः ], 1 );
            /* Set ullOwnedByCore. */
            prvSet64( &ullOwnedByCore[ ucCoreID ], ( prvGet64( &ullOwnedByCore[ ucCoreID ] ) | ul_तालकम्_Bit ) );
        }
        /* Lock release. */
        अन्यथा
        {
            /* Assert the lock is not free already. */
            configASSERT( ( prvGet64( &ullOwnedByCore[ ucCoreID ] ) & ul_तालकम्_Bit ) != 0 );
            configASSERT( prvGet64( &ull_Recursion_गणनम्_By_तालकम्[ e_तालकम्_अङ्कः ] ) != 0 );

            /* Reduce ullRecursionCountByLock by 1. */
            prvSet64( &ull_Recursion_गणनम्_By_तालकम्[ e_तालकम्_अङ्कः ], ( prvGet64( &ull_Recursion_गणनम्_By_तालकम्[ e_तालकम्_अङ्कः ] ) - 1 ) );

            यदि( !prvGet64( &ull_Recursion_गणनम्_By_तालकम्[ e_तालकम्_अङ्कः ] ) )
            {
                prvSet64( &ullOwnedByCore[ ucCoreID ], ( prvGet64( &ullOwnedByCore[ ucCoreID ] ) & ~ul_तालकम्_Bit ) );
                prvSpinUnlock( &ulGateWord[ e_तालकम्_अङ्कः ] );
                /* Add barrier to ensure lock status is reflected before we proceed. */
                __asm__ __volatile__ ( "dmb sy" ::: "memory" );
            }
        }
    }

/*-----------------------------------------------------------*/

    uint8_t uc_पत्तनम्_Get_Core_ID( शून्य )
    {
        /* Use SVC to obtain the core ID in a way that is safe when called
         * from EL0 tasks. ISRs and EL1 code should use
         * ucPortGetCoreIDFromIsr()/portGET_CORE_ID_FROM_ISR().
         */
        uint8_t ucCoreID;
        __asm चञ्चल (
            "svc %1             \n"
            "mov %w0, w0        \n"
            : "=r" ( ucCoreID )
            : "i" ( पत्तनम्_SVC_GET_CORE_ID )
            : "x0", "memory"
        );
        प्रत्यागम ucCoreID;
    }

/*-----------------------------------------------------------*/

    uint8_t uc_पत्तनम्_Get_Core_IDFrom_Isr ( शून्य ) /* PRIVILEGED_FUNCTION */
    {
        uint64_t ullMpidrEl1;
        __asm चञ्चल ( "MRS %0, MPIDR_EL1" : "=r" ( ullMpidrEl1 ) );

        प्रत्यागम ( uint8_t ) ( ullMpidrEl1 & 0xff );
    }

/*------------------------------------------------------------*/
    शून्य FreeRTOS_SGI_Handler( शून्य )
    {
        /* Must be the lowest possible priority. */
        uint64_t ull_Running_व्यवधानम्_प्राथमिकता;
        __asm चञ्चल ( "MRS %0, ICC_RPR_EL1" : "=r" ( ull_Running_व्यवधानम्_प्राथमिकता ) );

        configASSERT( ull_Running_व्यवधानम्_प्राथमिकता == ( पत्तनम्_निम्नतमम्_USABLE_व्यवधानम्_प्राथमिकता << पत्तनम्_प्राथमिकता_सरणम् ) );
        /* Interrupts should not be enabled before this point. */
        #यदि ( configASSERT_DEFINED == 1 )
        {
            uint64_t ull_आवरणम्_द्वयङ्काः;

            __asm चञ्चल ( "mrs %0, DAIF" : "=r" ( ull_आवरणम्_द्वयङ्काः )::"memory" );
            configASSERT( ( ull_आवरणम्_द्वयङ्काः & पत्तनम्_DAIF_I ) != 0 );
        }
        #यदि_अन्तः /* configASSERT_DEFINED */

        /* Set interrupt mask before altering scheduler structures. The SGI
         * interrupt runs at the lowest priority, so interrupts cannot already be masked,
         * so there is no need to save and restore the current mask value.  It is
         * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
         * updated.
         */
        UBaseType_t ux_व्यवधानम्_स्थितिः = पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR();

        UBaseType_t ux_Saved_व्यवधानम्_स्थितिः = पत्तनम्_ENTER_CRITICAL_FROM_ISR();
        #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
            ull_पत्तनम्_Yield_Required = pdTRUE;
        #अन्यथा
            ull_पत्तनम्_Yield_Required[ पत्तनम्_GET_CORE_ID_FROM_ISR() ] = pdTRUE;
        #यदि_अन्तः
        पत्तनम्_EXIT_CRITICAL_FROM_ISR( ux_Saved_व्यवधानम्_स्थितिः );
        पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( ux_व्यवधानम्_स्थितिः );
    }

/*-----------------------------------------------------------*/

#यदि_अन्तः /* if( configNUMBER_OF_CORES > 1 ) */
