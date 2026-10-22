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
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers. That should only be done when
 * task.h is included from an application file. */
#నిర్వచించు MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* MPU includes. */
#అన్తర్భావ "mpu_wrappers.h"
#అన్తర్భావ "mpu_syscall_numbers.h"

#నిర్వచనం_రద్దు MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#నిర్వచితం_కాకపోతే config_అంతరాయం_CONTROLLER_పునాది_చిరునామా
    #దోషం config_అంతరాయం_CONTROLLER_పునాది_చిరునామా must be defined.  Refer గమ్యం Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే config_అంతరాయం_CONTROLLER_CPU_INTERFACE_స్థానభ్రంశం
    #దోషం config_అంతరాయం_CONTROLLER_CPU_INTERFACE_స్థానభ్రంశం must be defined.  Refer గమ్యం Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే config_UNIQUE_అంతరాయం_PRIORITIES
    #దోషం config_UNIQUE_అంతరాయం_PRIORITIES must be defined.  Refer గమ్యం Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే config_అమరిక_TICK_అంతరాయం
    #దోషం config_అమరిక_TICK_అంతరాయం() must be defined.  Refer గమ్యం Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#అయితే_ముగింపు /* configSETUP_TICK_INTERRUPT */

#నిర్వచితం_కాకపోతే config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత
    #దోషం config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత must be defined.  Refer గమ్యం Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#అయితే_ముగింపు

#ఒకవేళ config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత == 0
    #దోషం "configMAX_API_CALL_INTERRUPT_PRIORITY must not be set to 0"
#అయితే_ముగింపు

#ఒకవేళ config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత > config_UNIQUE_అంతరాయం_PRIORITIES
    #దోషం "configMAX_API_CALL_INTERRUPT_PRIORITY must be less than or equal to configUNIQUE_INTERRUPT_PRIORITIES as the lower the numeric priority value the higher the logical interrupt priority"
#అయితే_ముగింపు

#ఒకవేళ config_USE_పోర్టు_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #ఒకవేళ ( configMAX_PRIORITIES > 32 )
        #దోషం "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 different priorities as tasks that share a priority will time slice."
    #అయితే_ముగింపు
#అయితే_ముగింపు /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#ఒకవేళ config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత <= ( config_UNIQUE_అంతరాయం_PRIORITIES / 2 )
    #దోషం "configMAX_API_CALL_INTERRUPT_PRIORITY must be greater than ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )"
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే config_CLEAR_TICK_అంతరాయం
    #దోషం config_CLEAR_TICK_అంతరాయం must be defined లోపల FreeRTOSConfig.h గమ్యం clear which ever అంతరాయం was వాడిన గమ్యం generate the tick అంతరాయం.
#అయితే_ముగింపు

#ఒకవేళ config_సంఖ్య_యొక్క_CORES < 1
    #దోషం config_సంఖ్య_యొక్క_CORES must be సమితి గమ్యం 1 or greater.  If the application is not using గుణిజం_2 cores then సమితి config_సంఖ్య_యొక్క_CORES గమ్యం 1.
#అయితే_ముగింపు /* configNUMBER_OF_CORES < 1 */

#నిర్వచితం_కాకపోతే configENABLE_MPU
    #దోషం configENABLE_MPU must be defined లోపల FreeRTOSConfig.h. సమితి_2 configENABLE_MPU గమ్యం 1 గమ్యం enable the MPU or 0 గమ్యం disable the MPU.
#అయితే_ముగింపు /* #if ( configENABLE_MPU == 1 ) */

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 != 0) )
    #దోషం Arm Cortex-R82 పోర్టు supports only MPU Wrapper V2.
#అయితే_ముగింపు /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 != 0) */

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#నిర్వచించు పోర్టు_NO_CRITICAL_NESTING    ( ( size_t ) 0 )

/* Macro to unmask all interrupt priorities. */
#నిర్వచించు పోర్టు_CLEAR_అంతరాయం_PRIORITIES_ముసుగు()    __asm అస్థిర ( "SVC %0" : : "i" ( పోర్టు_SVC_UNMASK_ALL_INTERRUPTS ) : "memory" )

/* Macro to unmask all interrupt priorities from EL1. */
#నిర్వచించు పోర్టు_CLEAR_అంతరాయం_PRIORITIES_ముసుగు_FROM_EL1()  \
{                                                       \
    __asm అస్థిర (                                    \
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
    : "i" ( పోర్టు_UNMASK_విలువ )                          \
    );                                                  \
}

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#నిర్వచించు పోర్టు_NO_FLOATING_బిందువు_CONTEXT    ( ( దొంతర_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#నిర్వచించు పోర్టు_SP_ELx                       ( ( దొంతర_Type_t ) 0x01 )
#నిర్వచించు పోర్టు_SP_EL0                       ( ( దొంతర_Type_t ) 0x00 )
#నిర్వచించు పోర్టు_EL1                          ( ( దొంతర_Type_t ) 0x04 )
#నిర్వచించు పోర్టు_EL0                          ( ( దొంతర_Type_t ) 0x00 )

#నిర్వచించు పోర్టు_INITIAL_PSTATE_EL0           ( పోర్టు_EL0 | పోర్టు_SP_EL0 )
#నిర్వచించు పోర్టు_INITIAL_PSTATE_EL1           ( పోర్టు_EL1 | పోర్టు_SP_EL0 )

/* Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero. */
#నిర్వచించు పోర్టు_ద్విమాన_బిందువు_బిట్లు            ( ( uint8_t ) 0x03 )

/* Masks all bits in the APSR other than the mode bits. */
#నిర్వచించు పోర్టు_APSR_బహుళకం_బిట్లు_ముసుగు          ( 0x0C )

/* The I bit in the DAIF bits. */
#నిర్వచించు పోర్టు_DAIF_I                       ( 0x80 )

#నిర్వచించు పోర్టు_MAX_8_బిట్టు_విలువ              ( ( uint8_t ) 0xff )
#నిర్వచించు పోర్టు_బిట్టు_0_సమితి                    ( ( uint8_t ) 0x01 )

/* The space on the stack required to hold the FPU registers.
 * There are 32 128-bit plus 2 64-bit status registers. */
#నిర్వచించు పోర్టు_FPU_రిజిస్టరు_పదాలు           ( ( 32 * 2 ) + 2 )

/*-----------------------------------------------------------*/

#ఒకవేళ ( configENABLE_MPU == 1 )

    /**
     * @brief Setup the Memory Protection Unit (MPU).
     */
    PRIVILEGED_FUNCTION శూన్య v_అమరిక_MPU( శూన్య );

    /**
     * @brief Enable the Memory Protection Unit (MPU).
     */
    PRIVILEGED_FUNCTION శూన్య vEnableMPU( శూన్య );

    /**
     * @brief Called from an ISR and returns the core ID the code is executing on.
     *
     * @return uint8_t The core ID.
     */
    PRIVILEGED_FUNCTION uint8_t uc_పోర్టు_Get_Core_IDFrom_Isr( శూన్య );

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    PRIVILEGED_FUNCTION పునాది_Type_t x_పోర్టు_Is_Task_Privileged( శూన్య );

    /**
     * @brief Extract MPU region's access permissions from the Protection Region Base Address Register
     * (PRBAR_EL1) value.
     *
     * @param ullPrbarEl1Value PRBAR_EL1 value for the MPU region.
     *
     * @return uint32_t Access permissions.
     */
    PRIVILEGED_FUNCTION స్థిర uint32_t prvGetRegionAccessPermissions( uint64_t ull_Prbar_El1_విలువ );

    /**
     * @brief Does the necessary work to enter a system call.
     *
     * @param pullPrivilegedOnlyTaskStack The task's privileged SP when the SVC was raised.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    PRIVILEGED_FUNCTION శూన్య vSystemCallEnter( uint64_t * pull_Privileged_Only_Task_దొంతర,
                                               uint8_t uc_System_Call_సంఖ్య );

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    PRIVILEGED_FUNCTION __attribute__( ( naked ) ) శూన్య vRequestSystemCallExit( శూన్య );

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param ullSystemCallReturnValue The actual system call return value.
     */
    PRIVILEGED_FUNCTION శూన్య vSystemCallExit( uint64_t ull_System_Call_Return_విలువ );

#అయితే_ముగింపు /* #if ( configENABLE_MPU == 1 ) */

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
బాహ్య శూన్య v_పోర్టు_Restore_Task_Context( శూన్య );
బాహ్య శూన్య vGIC_EnableIRQ( uint32_t ul_అంతరాయం_ID );
బాహ్య శూన్య v_GIC_సమితి_ప్రాధాన్యత( uint32_t ul_అంతరాయం_ID, uint32_t ul_ప్రాధాన్యత );
బాహ్య శూన్య v_GIC_Power_పైకి_Redistributor( శూన్య );
బాహ్య శూన్య vGIC_EnableCPUInterface( శూన్య );

/*-----------------------------------------------------------*/

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )

    PRIVILEGED_దత్తాంశం అస్థిర uint64_t ullCriticalNesting = 0ULL;

    /* Saved as part of the task context. If ullPortTaskHasFPUContext is non-zero
     * then floating point context must be saved and restored for the task. */
    PRIVILEGED_దత్తాంశం uint64_t ull_పోర్టు_Task_Has_FPUContext = pdFALSE;

    /* Set to 1 to pend a context switch from an ISR. */
    PRIVILEGED_దత్తాంశం uint64_t ull_పోర్టు_Yield_Required = pdFALSE;

    /* Counts the interrupt nesting depth. A context switch is only performed if
     * if the nesting depth is 0. */
    PRIVILEGED_దత్తాంశం uint64_t ull_పోర్టు_అంతరాయం_Nesting = 0;

#లేకపోతే /* #if ( configNUMBER_OF_CORES == 1 ) */
    PRIVILEGED_దత్తాంశం అస్థిర uint64_t ullCriticalNestings[ config_సంఖ్య_యొక్క_CORES ] = { 0 };

    /* Flags to check if the secondary cores are ready. */
    PRIVILEGED_దత్తాంశం అస్థిర uint8_t ucSecondaryCoresReadyFlags[ config_సంఖ్య_యొక్క_CORES - 1 ] = { 0 };

    /* Flag to signal that the primary core has done all the shared initialisations. */
    PRIVILEGED_దత్తాంశం అస్థిర uint8_t uc_Primary_Core_Init_పూర్తి_Flag = 0;

    /* Saved as part of the task context. If ullPortTaskHasFPUContext is non-zero
     * then floating point context must be saved and restored for the task. */
    PRIVILEGED_దత్తాంశం uint64_t ull_పోర్టు_Task_Has_FPUContext[ config_సంఖ్య_యొక్క_CORES ] = { pdFALSE };

    /* Set to 1 to pend a context switch from an ISR. */
    PRIVILEGED_దత్తాంశం uint64_t ull_పోర్టు_Yield_Required[ config_సంఖ్య_యొక్క_CORES ] = { pdFALSE };

    /* Counts the interrupt nesting depth. A context switch is only performed if
     * if the nesting depth is 0. */
    PRIVILEGED_దత్తాంశం uint64_t ull_పోర్టు_అంతరాయం_Nestings[ config_సంఖ్య_యొక్క_CORES ] = { 0 };

#అయితే_ముగింపు /* #if ( configNUMBER_OF_CORES == 1 ) */

#ఒకవేళ ( configENABLE_MPU == 1 )
    /* Set to pdTRUE when the scheduler is started. */
    PRIVILEGED_దత్తాంశం స్థిర పునాది_Type_t xSchedulerRunning = pdFALSE;
#అయితే_ముగింపు /* ( configENABLE_MPU == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configENABLE_MPU == 1 )

    దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                         TaskFunction_t px_సంకేతం,
                                         శూన్య * pvParameters,
                                         పునాది_Type_t x_నిరంతరం_Privileged,
                                         xMPU_SETTINGS * xMPUSettings )
    {
        uint32_t ul_సూచీ = 0;

        /* Layout must match portRESTORE_CONTEXT pop order (descending stack):
         * 1) FPU flag, 2) Critical nesting, 3) Optional FPU save area,
         * 4) ELR (PC), 5) SPSR (PSTATE), 6) GPRs in restore order pairs.
         */

        /* 1) FPU flag and 2) Critical nesting. */
        #ఒకవేళ ( configUSE_TASK_FPU_SUPPORT == పోర్టు_TASK_NO_FPU_CONTEXT_BY_DEFAULT )
            xMPUSettings->ullContext[ ul_సూచీ++ ] = పోర్టు_NO_FLOATING_బిందువు_CONTEXT; /* FPU flag */
            xMPUSettings->ullContext[ ul_సూచీ++ ] = పోర్టు_NO_CRITICAL_NESTING;       /* Critical nesting */
        #లేదావేళ ( configUSE_TASK_FPU_SUPPORT == పోర్టు_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
            xMPUSettings->ullContext[ ul_సూచీ++ ] = pdTRUE;                        /* FPU flag */
            xMPUSettings->ullContext[ ul_సూచీ++ ] = పోర్టు_NO_CRITICAL_NESTING;       /* Critical nesting */
            #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
                ull_పోర్టు_Task_Has_FPUContext = pdTRUE;
            #లేకపోతే
                ull_పోర్టు_Task_Has_FPUContext[ పోర్టు_GET_CORE_ID() ] = pdTRUE;
            #అయితే_ముగింపు
        #లేకపోతే
            #దోషం "Invalid configUSE_TASK_FPU_SUPPORT setting - must be 1 or 2."
        #అయితే_ముగింపు

        /* 3) Optional FPU save area immediately after the flag+critical pair. */
        #ఒకవేళ ( configUSE_TASK_FPU_SUPPORT == పోర్టు_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
            memset( &xMPUSettings->ullContext[ ul_సూచీ ], 0x00, పోర్టు_FPU_రిజిస్టరు_పదాలు * పరిమాణం( దొంతర_Type_t ) );
            ul_సూచీ += పోర్టు_FPU_రిజిస్టరు_పదాలు;
        #అయితే_ముగింపు

        /* 4) ELR (PC) and 5) SPSR (PSTATE). */
        xMPUSettings->ullContext[ ul_సూచీ++ ] = ( దొంతర_Type_t ) px_సంకేతం; /* ELR */

        ఒకవేళ( x_నిరంతరం_Privileged == pdTRUE )
        {
            xMPUSettings->ullContext[ ul_సూచీ++ ] = పోర్టు_INITIAL_PSTATE_EL1;    /* SPSR */
        }
        లేకపోతే
        {
            xMPUSettings->ullContext[ ul_సూచీ++ ] = పోర్టు_INITIAL_PSTATE_EL0;    /* SPSR */
        }

        /* 6) General-purpose registers in the order expected by restoreallgpregisters. */
        xMPUSettings->ullContext[ ul_సూచీ++ ] = ( దొంతర_Type_t ) 0x00;         /* X30 (LR) */
        xMPUSettings->ullContext[ ul_సూచీ++ ] = ( దొంతర_Type_t ) 0x00;         /* XZR (dummy) */

        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x2828282828282828ULL;        /* X28 */
        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x2929292929292929ULL;        /* X29 */

        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x2626262626262626ULL;        /* X26 */
        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x2727272727272727ULL;        /* X27 */

        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x2424242424242424ULL;        /* X24 */
        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x2525252525252525ULL;        /* X25 */

        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x2222222222222222ULL;        /* X22 */
        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x2323232323232323ULL;        /* X23 */

        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x2020202020202020ULL;        /* X20 */
        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x2121212121212121ULL;        /* X21 */

        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x1818181818181818ULL;        /* X18 */
        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x1919191919191919ULL;        /* X19 */

        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x1616161616161616ULL;        /* X16 */
        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x1717171717171717ULL;        /* X17 */

        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x1414141414141414ULL;        /* X14 */
        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x1515151515151515ULL;        /* X15 */

        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x1212121212121212ULL;        /* X12 */
        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x1313131313131313ULL;        /* X13 */

        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x1010101010101010ULL;        /* X10 */
        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x1111111111111111ULL;        /* X11 */

        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x0808080808080808ULL;        /* X8 */
        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x0909090909090909ULL;        /* X9 */

        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x0606060606060606ULL;        /* X6 */
        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x0707070707070707ULL;        /* X7 */

        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x0404040404040404ULL;        /* X4 */
        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x0505050505050505ULL;        /* X5 */

        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x0202020202020202ULL;        /* X2 */
        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x0303030303030303ULL;        /* X3 */

        xMPUSettings->ullContext[ ul_సూచీ++ ] = ( దొంతర_Type_t ) pvParameters; /* X0 */
        xMPUSettings->ullContext[ ul_సూచీ++ ] = 0x0101010101010101ULL;        /* X1 */

        ఒకవేళ( x_నిరంతరం_Privileged == pdTRUE )
        {
            xMPUSettings->ullTaskFlags |= పోర్టు_TASK_IS_PRIVILEGED_FLAG;
        }
        లేకపోతే
        {
            xMPUSettings->ullTaskFlags &= ( ~పోర్టు_TASK_IS_PRIVILEGED_FLAG );
        }

        xMPUSettings->ullTaskUnprivilegedSP = ( ( uint64_t ) px_శిఖరం_యొక్క_దొంతర & పోర్టు_MPU_PRBAR_EL1_చిరునామా_ముసుగు );

        తిరిగి &( xMPUSettings->ullContext[ 0 ] );
    }

#లేకపోతే /* #if ( configENABLE_MPU == 1 ) */

    /*
    * See header file for description.
    */
    దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                         TaskFunction_t px_సంకేతం,
                                         శూన్య * pvParameters )
    {
        /* Setup the initial stack of the task.  The stack is set exactly as
        * expected by the portRESTORE_CONTEXT() macro. */

        /* First all the general purpose registers. */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x0101010101010101ULL;        /* R1 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters; /* R0 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x0303030303030303ULL;        /* R3 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x0202020202020202ULL;        /* R2 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x0505050505050505ULL;        /* R5 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x0404040404040404ULL;        /* R4 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x0707070707070707ULL;        /* R7 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x0606060606060606ULL;        /* R6 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x0909090909090909ULL;        /* R9 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x0808080808080808ULL;        /* R8 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x1111111111111111ULL;        /* R11 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x1010101010101010ULL;        /* R10 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x1313131313131313ULL;        /* R13 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x1212121212121212ULL;        /* R12 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x1515151515151515ULL;        /* R15 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x1414141414141414ULL;        /* R14 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x1717171717171717ULL;        /* R17 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x1616161616161616ULL;        /* R16 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x1919191919191919ULL;        /* R19 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x1818181818181818ULL;        /* R18 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x2121212121212121ULL;        /* R21 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x2020202020202020ULL;        /* R20 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x2323232323232323ULL;        /* R23 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x2222222222222222ULL;        /* R22 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x2525252525252525ULL;        /* R25 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x2424242424242424ULL;        /* R24 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x2727272727272727ULL;        /* R27 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x2626262626262626ULL;        /* R26 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x2929292929292929ULL;        /* R29 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x2828282828282828ULL;        /* R28 */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x00;         /* XZR - has no effect, used so there are an even number of registers. */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x00;         /* R30 - procedure call link register. */

        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_PSTATE_EL0;

        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం; /* Exception return address. */

        #ఒకవేళ ( configUSE_TASK_FPU_SUPPORT == పోర్టు_TASK_NO_FPU_CONTEXT_BY_DEFAULT )
        {
            /* The task will start with a critical nesting count of 0 as interrupts are
            * enabled. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = పోర్టు_NO_CRITICAL_NESTING;

            /* The task will start without a floating point context.  A task that
            * uses the floating point hardware must call vPortTaskUsesFPU() before
            * executing any floating point instructions. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = పోర్టు_NO_FLOATING_బిందువు_CONTEXT;
        }
        #లేదావేళ ( configUSE_TASK_FPU_SUPPORT == పోర్టు_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
        {
            /* The task will start with a floating point context.  Leave enough
            * space for the registers - and ensure they are initialised to 0. */
            px_శిఖరం_యొక్క_దొంతర -= పోర్టు_FPU_రిజిస్టరు_పదాలు;
            memset( px_శిఖరం_యొక్క_దొంతర, 0x00, పోర్టు_FPU_రిజిస్టరు_పదాలు * పరిమాణం( దొంతర_Type_t ) );

            /* The task will start with a critical nesting count of 0 as interrupts are
            * enabled. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = పోర్టు_NO_CRITICAL_NESTING;

            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = pdTRUE;
            #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
            ull_పోర్టు_Task_Has_FPUContext = pdTRUE;
            #లేకపోతే
            ull_పోర్టు_Task_Has_FPUContext[ పోర్టు_GET_CORE_ID() ] = pdTRUE;
            #అయితే_ముగింపు
        }
        #లేకపోతే /* if ( configUSE_TASK_FPU_SUPPORT == portTASK_NO_FPU_CONTEXT_BY_DEFAULT ) */
        {
            #దోషం "Invalid configUSE_TASK_FPU_SUPPORT setting - configUSE_TASK_FPU_SUPPORT must be set to 1, 2, or left undefined."
        }
        #అయితే_ముగింపు /* if ( configUSE_TASK_FPU_SUPPORT == portTASK_NO_FPU_CONTEXT_BY_DEFAULT ) */

        తిరిగి px_శిఖరం_యొక్క_దొంతర;

    }

#అయితే_ముగింపు /* #if ( configENABLE_MPU == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configENABLE_MPU == 1 )

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
    శూన్య v_పోర్టు_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    స్థిరరాశి నిర్మాణం x_జ్ఞాపకం_REGION * స్థిరరాశి xRegions,
                                    దొంతర_Type_t * px_Bottom_యొక్క_దొంతర,
                                    దొంతర_Type_t x_దొంతర_లోతు )  /* PRIVILEGED_FUNCTION */
    {
        uint64_t ull_Region_ప్రారంభం_చిరునామా, ull_Region_చివర_చిరునామా;
        uint8_t  uc_సూచీ = 0, uc_Region_సంఖ్య;

        #ఒకవేళ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            బాహ్య uint64_t * __privileged_sram_start__;
            బాహ్య uint64_t * __privileged_sram_end__;
        #లేకపోతే
            /* Declaration when these variable are exported from linker scripts. */
            బాహ్య uint64_t __privileged_sram_start__[];
            బాహ్య uint64_t __privileged_sram_end__[];
        #అయితే_ముగింపు /* defined( __ARMCC_VERSION ) */

        /* Setup MAIR_EL1. */
        xMPUSettings->ullMairEl1 = ( ( పోర్టు_MPU_సాధారణ_జ్ఞాపకం_BUFFERABLE_CACHEABLE << పోర్టు_MPU_MAIR_EL1_ATTR0_POS ) & పోర్టు_MPU_MAIR_EL1_ATTR0_ముసుగు );
        xMPUSettings->ullMairEl1 |= ( ( పోర్టు_MPU_DEVICE_జ్ఞాపకం_n_Gn_RE << పోర్టు_MPU_MAIR_EL1_ATTR1_POS ) & పోర్టు_MPU_MAIR_EL1_ATTR1_ముసుగు );

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid. At all other
         * times the stack parameters will not be valid and it is assumed that
         * the stack region has already been configured. */
        ఒకవేళ( x_దొంతర_లోతు > 0 )
        {
            ull_Region_ప్రారంభం_చిరునామా = ( uint64_t ) px_Bottom_యొక్క_దొంతర;
            ull_Region_చివర_చిరునామా = ( uint64_t ) px_Bottom_యొక్క_దొంతర + ( x_దొంతర_లోతు * ( config_దొంతర_లోతు_TYPE ) పరిమాణం( దొంతర_Type_t ) ) - 1;

            /* If the stack is within the privileged SRAM, do not protect it
             * using a separate MPU region. This is needed because this
             * region is already protected using an MPU region and ARMv8-R does
             * not allow overlapping MPU regions.
             */
            ఒకవేళ( ( ull_Region_ప్రారంభం_చిరునామా >= ( uint64_t ) __privileged_sram_start__ ) &&
                ( ull_Region_చివర_చిరునామా <= ( uint64_t ) __privileged_sram_end__ ) )
            {
                xMPUSettings->xRegionsSettings[ పోర్టు_దొంతర_REGION_సూచీ ].ullPrbarEl1 = 0;
                xMPUSettings->xRegionsSettings[ పోర్టు_దొంతర_REGION_సూచీ ].ullPrlarEl1 = 0;
            }
            లేకపోతే
            {
                /* Define the region that allows access to the stack. */
                ull_Region_ప్రారంభం_చిరునామా &= పోర్టు_MPU_PRBAR_EL1_చిరునామా_ముసుగు;
                ull_Region_చివర_చిరునామా &= పోర్టు_MPU_PRLAR_EL1_చిరునామా_ముసుగు;

                xMPUSettings->xRegionsSettings[ పోర్టు_దొంతర_REGION_సూచీ ].ullPrbarEl1 = ( ull_Region_ప్రారంభం_చిరునామా ) |
                                                                                 ( పోర్టు_MPU_REGION_INNER_SHAREABLE ) |
                                                                                 ( పోర్టు_MPU_REGION_READ_WRITE ) |
                                                                                 ( పోర్టు_MPU_REGION_EXECUTE_NEVER );

                xMPUSettings->xRegionsSettings[ పోర్టు_దొంతర_REGION_సూచీ ].ullPrlarEl1 = ( ull_Region_చివర_చిరునామా ) |
                                                                                 ( పోర్టు_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                                                                                 ( పోర్టు_MPU_PRLAR_EL1_REGION_ENABLE );
            }
        }

        /* User supplied configurable regions. */
        కొరకు( uc_Region_సంఖ్య = 1; uc_Region_సంఖ్య <= పోర్టు_అంకె_CONFIGURABLE_REGIONS; uc_Region_సంఖ్య++ )
        {
            /* If xRegions is NULL i.e. the task has not specified any MPU
             * region, the else part ensures that all the configurable MPU
             * regions are invalidated.
             * The minimum region size is 64 Bytes.
             */
            ఒకవేళ( xRegions != ఖాళీ )
            {
                /* Configure the region only if the base address is non-NULL.
                 * The user may choose to use only a subset of the available MPU regions.
                 * This check prevents undefined regions (i.e. regions with a NULL base
                 * address) from being configured and from triggering the size-check
                 * assertion below.
                 */
                ఒకవేళ ( xRegions[ uc_సూచీ ].pv_పునాది_చిరునామా != ఖాళీ )
                {
                    configASSERT( xRegions[ uc_సూచీ ].ul_నిడివి_లోపల_బైట్లు >= 64UL );

                    uint64_t ull_Prbar_El1_Reg_విలువ, ull_Prlar_El1_Reg_విలువ;

                    /* Translate the generic region definition contained in xRegions
                     * into the ARMv8-R specific MPU settings that are then stored in
                     * xMPUSettings.
                     */
                    ull_Region_ప్రారంభం_చిరునామా = ( ( uint64_t ) xRegions[ uc_సూచీ ].pv_పునాది_చిరునామా ) & పోర్టు_MPU_PRBAR_EL1_చిరునామా_ముసుగు;
                    ull_Region_చివర_చిరునామా = ( uint64_t ) xRegions[ uc_సూచీ ].pv_పునాది_చిరునామా + xRegions[ uc_సూచీ ].ul_నిడివి_లోపల_బైట్లు - 1;
                    ull_Region_చివర_చిరునామా &= పోర్టు_MPU_PRLAR_EL1_చిరునామా_ముసుగు;

                    /* Checks for overlaps with another user defined regions and stack region, which are already configured. */
                    కొరకు( uint8_t uc_User_Region_సంఖ్య = 0; uc_User_Region_సంఖ్య < పోర్టు_అంకె_CONFIGURABLE_REGIONS; uc_User_Region_సంఖ్య++ )
                    {
                        /* Check for overlap. */
                        ఒకవేళ( ( పోర్టు_IS_చిరునామా_WITHIN_RANGE( ull_Region_ప్రారంభం_చిరునామా,
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_సంఖ్య ].ullPrbarEl1 & పోర్టు_MPU_PRBAR_EL1_చిరునామా_ముసుగు ),
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_సంఖ్య ].ullPrlarEl1 & పోర్టు_MPU_PRLAR_EL1_చిరునామా_ముసుగు ) ) ||
                            ( పోర్టు_IS_చిరునామా_WITHIN_RANGE( ull_Region_చివర_చిరునామా,
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_సంఖ్య ].ullPrbarEl1 & పోర్టు_MPU_PRBAR_EL1_చిరునామా_ముసుగు ),
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_సంఖ్య ].ullPrlarEl1 & పోర్టు_MPU_PRLAR_EL1_చిరునామా_ముసుగు ) ) ) ) )
                        {
                            /* Overlap detected - assert. */
                            configASSERT( ఖాళీ );
                        }
                    }

                    /* Checks for overlaps with kernel programmed regions which are already programmed as part of vSetupMPU. */
                    కొరకు (uint8_t uc_Programmed_Region_సూచీ = 0; uc_Programmed_Region_సూచీ < 4; uc_Programmed_Region_సూచీ++)
                    {
                        __asm అస్థిర ( "msr PRSELR_EL1, %0" : : "r" ( ( uint64_t ) uc_Programmed_Region_సూచీ ) );

                        __asm అస్థిర ( "mrs %0, PRBAR_EL1" : "=r" ( ull_Prbar_El1_Reg_విలువ ) );
                        ull_Prbar_El1_Reg_విలువ &= పోర్టు_MPU_PRBAR_EL1_చిరునామా_ముసుగు;

                        __asm అస్థిర ( "mrs %0, PRLAR_EL1" : "=r" ( ull_Prlar_El1_Reg_విలువ ) );
                        ull_Prlar_El1_Reg_విలువ &= పోర్టు_MPU_PRLAR_EL1_చిరునామా_ముసుగు;

                        /* Check for overlap. */
                        ఒకవేళ( ( పోర్టు_IS_చిరునామా_WITHIN_RANGE( ull_Region_ప్రారంభం_చిరునామా,
                                                        ull_Prbar_El1_Reg_విలువ,
                                                        ull_Prlar_El1_Reg_విలువ ) ) ||
                            ( పోర్టు_IS_చిరునామా_WITHIN_RANGE( ull_Region_చివర_చిరునామా,
                                                        ull_Prbar_El1_Reg_విలువ,
                                                        ull_Prlar_El1_Reg_విలువ ) ) )
                        {
                            /* Overlap detected - assert. */
                            configASSERT( ఖాళీ );
                        }
                    }

                    /* Start address. */
                    xMPUSettings->xRegionsSettings[ uc_Region_సంఖ్య ].ullPrbarEl1 = ( ull_Region_ప్రారంభం_చిరునామా );

                    /* RO/RW. */
                    ఒకవేళ( ( xRegions[ uc_సూచీ ].ulParameters & tskMPU_REGION_READ_ONLY ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_సంఖ్య ].ullPrbarEl1 |= ( పోర్టు_MPU_REGION_READ_ONLY );
                    }
                    లేకపోతే
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_సంఖ్య ].ullPrbarEl1 |= ( పోర్టు_MPU_REGION_READ_WRITE );
                    }

                    /* XN. */
                    ఒకవేళ( ( xRegions[ uc_సూచీ ].ulParameters & tskMPU_REGION_EXECUTE_NEVER ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_సంఖ్య ].ullPrbarEl1 |= ( పోర్టు_MPU_REGION_EXECUTE_NEVER );
                    }

                    /* SH. */
                    ఒకవేళ( ( xRegions[ uc_సూచీ ].ulParameters & tskMPU_REGION_INNER_SHAREABLE ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_సంఖ్య ].ullPrbarEl1 |= ( పోర్టు_MPU_REGION_INNER_SHAREABLE );
                    }
                    లేకపోతే ఒకవేళ( ( xRegions[ uc_సూచీ ].ulParameters & tskMPU_REGION_OUTER_SHAREABLE ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_సంఖ్య ].ullPrbarEl1 |= ( పోర్టు_MPU_REGION_OUTER_SHAREABLE );
                    }
                    లేకపోతే
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_సంఖ్య ].ullPrbarEl1 |= ( పోర్టు_MPU_REGION_NON_SHAREABLE );
                    }

                    /* End Address. */
                    xMPUSettings->xRegionsSettings[ uc_Region_సంఖ్య ].ullPrlarEl1 = ( ull_Region_చివర_చిరునామా ) |
                                                                                ( పోర్టు_MPU_PRLAR_EL1_REGION_ENABLE );

                    /* Normal memory/ Device memory. */
                    ఒకవేళ( ( xRegions[ uc_సూచీ ].ulParameters & tsk_MPU_REGION_DEVICE_జ్ఞాపకం ) != 0 )
                    {
                        /* Attr1 in MAIR_EL1 is configured as device memory. */
                        xMPUSettings->xRegionsSettings[ uc_Region_సంఖ్య ].ullPrlarEl1 |= పోర్టు_MPU_PRLAR_EL1_ATTR_INDEX1;
                    }
                    లేకపోతే
                    {
                        /* Attr0 in MAIR_EL1 is configured as normal memory. */
                        xMPUSettings->xRegionsSettings[ uc_Region_సంఖ్య ].ullPrlarEl1 |= పోర్టు_MPU_PRLAR_EL1_ATTR_INDEX0;
                    }
                }
            }
            లేకపోతే
            {
                /* Invalidate the region. */
                xMPUSettings->xRegionsSettings[ uc_Region_సంఖ్య ].ullPrbarEl1 = 0UL;
                xMPUSettings->xRegionsSettings[ uc_Region_సంఖ్య ].ullPrlarEl1 = 0UL;
            }

            uc_సూచీ++;
        }

    }
    /*-----------------------------------------------------------*/

    శూన్య v_అమరిక_MPU( శూన్య ) /* PRIVILEGED_FUNCTION */
    {
        #ఒకవేళ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts.
             */
            బాహ్య uint64_t * __privileged_functions_start__;
            బాహ్య uint64_t * __privileged_functions_end__;
            బాహ్య uint64_t * __syscalls_flash_start__;
            బాహ్య uint64_t * __syscalls_flash_end__;
            బాహ్య uint64_t * __unprivileged_flash_start__;
            బాహ్య uint64_t * __unprivileged_flash_end__;
            బాహ్య uint64_t * __privileged_sram_start__;
            బాహ్య uint64_t * __privileged_sram_end__;
        #లేకపోతే /* if defined( __ARMCC_VERSION ) */
            /* Declaration when these variable are exported from linker scripts. */
            బాహ్య uint64_t __privileged_functions_start__[];
            బాహ్య uint64_t __privileged_functions_end__[];
            బాహ్య uint64_t __syscalls_flash_start__[];
            బాహ్య uint64_t __syscalls_flash_end__[];
            బాహ్య uint64_t __unprivileged_flash_start__[];
            బాహ్య uint64_t __unprivileged_flash_end__[];
            బాహ్య uint64_t __privileged_sram_start__[];
            బాహ్య uint64_t __privileged_sram_end__[];
        #అయితే_ముగింపు /* defined( __ARMCC_VERSION ) */

        /* The only permitted number of regions are 16 or 32. */
        configASSERT( ( config_మొత్తం_MPU_REGIONS == 16 ) || ( config_మొత్తం_MPU_REGIONS == 32 ) );

        /* MAIR_EL1 - Index 0. */
        uint64_t ull_Mair_El1_Reg_విలువ = ( ( పోర్టు_MPU_సాధారణ_జ్ఞాపకం_BUFFERABLE_CACHEABLE << పోర్టు_MPU_MAIR_EL1_ATTR0_POS ) & పోర్టు_MPU_MAIR_EL1_ATTR0_ముసుగు );
        /* MAIR_EL1 - Index 1. */
        ull_Mair_El1_Reg_విలువ |= ( ( పోర్టు_MPU_DEVICE_జ్ఞాపకం_n_Gn_RE << పోర్టు_MPU_MAIR_EL1_ATTR1_POS ) & పోర్టు_MPU_MAIR_EL1_ATTR1_ముసుగు );

        __asm అస్థిర ( "msr MAIR_EL1, %0" : : "r" ( ull_Mair_El1_Reg_విలువ ) );

        /* Setup privileged flash as Read Only so that privileged tasks can
         * read it but not modify.
         */
        uint64_t ull_Prselr_El1_Reg_విలువ = పోర్టు_PRIVILEGED_FLASH_REGION;
        __asm అస్థిర ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_విలువ ) );

        uint64_t ull_Prbar_El1_Reg_విలువ = ( ( ( uint64_t ) __privileged_functions_start__ ) & పోర్టు_MPU_PRBAR_EL1_చిరునామా_ముసుగు ) |
                                       ( పోర్టు_MPU_REGION_NON_SHAREABLE ) |
                                       ( పోర్టు_MPU_REGION_PRIVILEGED_READ_ONLY );
        __asm అస్థిర ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_విలువ ) );

        uint64_t ull_Prlar_El1_Reg_విలువ = ( ( ( uint64_t ) __privileged_functions_end__ ) & పోర్టు_MPU_PRLAR_EL1_చిరునామా_ముసుగు ) |
                                       ( పోర్టు_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                                       ( పోర్టు_MPU_PRLAR_EL1_REGION_ENABLE );
        __asm అస్థిర ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_విలువ ) );

        /* Setup unprivileged flash as Read Only by both privileged and
         * unprivileged tasks. All tasks can read it but no-one can modify.
         */
        ull_Prselr_El1_Reg_విలువ = పోర్టు_UNPRIVILEGED_FLASH_REGION;
        __asm అస్థిర ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_విలువ ) );

        ull_Prbar_El1_Reg_విలువ = ( ( ( uint64_t ) __unprivileged_flash_start__ ) & పోర్టు_MPU_PRBAR_EL1_చిరునామా_ముసుగు ) |
                              ( పోర్టు_MPU_REGION_NON_SHAREABLE ) |
                              ( పోర్టు_MPU_REGION_READ_ONLY );
        __asm అస్థిర ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_విలువ ) );

        ull_Prlar_El1_Reg_విలువ = ( ( ( uint64_t ) __unprivileged_flash_end__ ) & పోర్టు_MPU_PRLAR_EL1_చిరునామా_ముసుగు ) |
                              ( పోర్టు_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                              ( పోర్టు_MPU_PRLAR_EL1_REGION_ENABLE );
        __asm అస్థిర ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_విలువ ) );

        /* Setup unprivileged syscalls flash as Read Only by both privileged
         * and unprivileged tasks. All tasks can read it but no-one can modify.
         */
        ull_Prselr_El1_Reg_విలువ = పోర్టు_UNPRIVILEGED_SYSCALLS_REGION;
        __asm అస్థిర ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_విలువ ) );

        ull_Prbar_El1_Reg_విలువ = ( ( ( uint64_t ) __syscalls_flash_start__ ) & పోర్టు_MPU_PRBAR_EL1_చిరునామా_ముసుగు ) |
                              ( పోర్టు_MPU_REGION_NON_SHAREABLE ) |
                              ( పోర్టు_MPU_REGION_READ_ONLY );
        __asm అస్థిర ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_విలువ ) );

        ull_Prlar_El1_Reg_విలువ = ( ( ( uint64_t ) __syscalls_flash_end__ ) & పోర్టు_MPU_PRLAR_EL1_చిరునామా_ముసుగు ) |
                              ( పోర్టు_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                              ( పోర్టు_MPU_PRLAR_EL1_REGION_ENABLE );
        __asm అస్థిర ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_విలువ ) );

        /* Setup RAM containing kernel data for privileged access only. */
        ull_Prselr_El1_Reg_విలువ = పోర్టు_PRIVILEGED_RAM_REGION;
        __asm అస్థిర ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_విలువ ) );

        ull_Prbar_El1_Reg_విలువ = ( ( ( uint64_t ) __privileged_sram_start__ ) & పోర్టు_MPU_PRBAR_EL1_చిరునామా_ముసుగు ) |
                              ( పోర్టు_MPU_REGION_INNER_SHAREABLE ) |
                              ( పోర్టు_MPU_REGION_PRIVILEGED_READ_WRITE ) |
                              ( పోర్టు_MPU_REGION_EXECUTE_NEVER );
        __asm అస్థిర ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_విలువ ) );

        ull_Prlar_El1_Reg_విలువ = ( ( ( uint64_t ) __privileged_sram_end__ ) & పోర్టు_MPU_PRLAR_EL1_చిరునామా_ముసుగు ) |
                              ( పోర్టు_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                              ( పోర్టు_MPU_PRLAR_EL1_REGION_ENABLE );
        __asm అస్థిర ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_విలువ ) );
    }
    /*-----------------------------------------------------------*/

    శూన్య vEnableMPU( శూన్య ) /* PRIVILEGED_FUNCTION */
    {
        uint64_t ull_Sctlr_El1_Reg_విలువ;

        __asm అస్థిర ( "mrs %0, SCTLR_EL1" : "=r" ( ull_Sctlr_El1_Reg_విలువ ) );
        /* Enable the MPU. Also enable privileged access to the
         * background region.
         */
        ull_Sctlr_El1_Reg_విలువ |= ( పోర్టు_MPU_PRIV_BACKGROUND_ENABLE_బిట్టు | పోర్టు_MPU_ENABLE_బిట్టు );
        __asm అస్థిర ( "msr SCTLR_EL1, %0" : : "r" ( ull_Sctlr_El1_Reg_విలువ ) );

        /* Ensure the write to SCTLR_EL1 is committed before
         * returning.
         */
        __asm అస్థిర ( "isb" );
    }
    /*-----------------------------------------------------------*/

    పునాది_Type_t x_పోర్టు_Is_Task_Privileged( శూన్య ) /* PRIVILEGED_FUNCTION */
    {
        పునాది_Type_t xTaskIsPrivileged = pdFALSE;

        #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
            బాహ్య TaskHandle_t pxCurrentTCB;
            xMPU_SETTINGS * pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );
        #లేకపోతే
            బాహ్య TaskHandle_t pxCurrentTCBs[ config_సంఖ్య_యొక్క_CORES ];
            xMPU_SETTINGS * pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCBs[ పోర్టు_GET_CORE_ID_FROM_ISR() ] );
        #అయితే_ముగింపు

        ఒకవేళ( ( pxMpuSettings->ullTaskFlags & పోర్టు_TASK_IS_PRIVILEGED_FLAG ) == పోర్టు_TASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        తిరిగి xTaskIsPrivileged;
    }
    /*-----------------------------------------------------------*/

    స్థిర uint32_t prvGetRegionAccessPermissions( uint64_t ull_Prbar_El1_విలువ ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ulAccessPermissions = 0;

        ఒకవేళ( ( ull_Prbar_El1_విలువ & పోర్టు_MPU_PRBAR_EL1_ACCESS_PERMISSIONS_ముసుగు ) == పోర్టు_MPU_REGION_READ_ONLY )
        {
            ulAccessPermissions = tskMPU_READ_PERMISSION;
        }

        ఒకవేళ( ( ull_Prbar_El1_విలువ & పోర్టు_MPU_PRBAR_EL1_ACCESS_PERMISSIONS_ముసుగు ) == పోర్టు_MPU_REGION_READ_WRITE )
        {
            ulAccessPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
        }

        తిరిగి ulAccessPermissions;
    }
    /*-----------------------------------------------------------*/

    పునాది_Type_t x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( స్థిరరాశి శూన్య * pv_బఫరు,
                                                size_t x_బఫరు_నిడివి,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i;
        uint64_t ull_బఫరు_ప్రారంభం_చిరునామా, ull_బఫరు_చివర_చిరునామా;
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
        లేకపోతే ఒకవేళ( ( xTaskMpuSettings->ullTaskFlags & పోర్టు_TASK_IS_PRIVILEGED_FLAG ) == పోర్టు_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        లేకపోతే
        {
            ఒకవేళ( పోర్టు_కూడు_UINT64_WILL_అధికప్రవాహం( ( ( uint64_t ) pv_బఫరు ), ( ( uint64_t ) x_బఫరు_నిడివి - 1ULL ) ) == pdFALSE )
            {
                ull_బఫరు_ప్రారంభం_చిరునామా = ( uint64_t ) pv_బఫరు;
                ull_బఫరు_చివర_చిరునామా = ( ( ( uint64_t ) pv_బఫరు ) + ( uint64_t ) x_బఫరు_నిడివి - 1ULL );

                కొరకు( i = 0; i < పోర్టు_మొత్తం_అంకె_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    ఒకవేళ( ( xTaskMpuSettings->xRegionsSettings[ i ].ullPrlarEl1 & పోర్టు_MPU_PRLAR_EL1_REGION_ENABLE ) == పోర్టు_MPU_PRLAR_EL1_REGION_ENABLE )
                    {
                        ఒకవేళ( పోర్టు_IS_చిరునామా_WITHIN_RANGE( ull_బఫరు_ప్రారంభం_చిరునామా,
                                                         పోర్టు_వెలికితీయి_మొదటి_చిరునామా_FROM_PRBAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrbarEl1 ),
                                                         పోర్టు_వెలికితీయి_చివరి_చిరునామా_FROM_PRLAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrlarEl1 ) ) &&
                            పోర్టు_IS_చిరునామా_WITHIN_RANGE( ull_బఫరు_చివర_చిరునామా,
                                                         పోర్టు_వెలికితీయి_మొదటి_చిరునామా_FROM_PRBAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrbarEl1 ),
                                                         పోర్టు_వెలికితీయి_చివరి_చిరునామా_FROM_PRLAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrlarEl1 ) ) &&
                            పోర్టు_IS_AUTHORIZED( ulAccessRequested,
                                               prvGetRegionAccessPermissions( xTaskMpuSettings->xRegionsSettings[ i ].ullPrbarEl1 ) ) )
                        {
                            xAccessGranted = pdTRUE;
                            ఆపు;
                        }
                    }
                }
            }
        }

        తిరిగి xAccessGranted;
    }
    /*-----------------------------------------------------------*/

    శూన్య vSystemCallEnter( uint64_t * pull_Privileged_Only_Task_దొంతర,
                           uint8_t uc_System_Call_సంఖ్య ) /* PRIVILEGED_FUNCTION */
    {
        #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
            బాహ్య TaskHandle_t pxCurrentTCB;
        #లేకపోతే
            బాహ్య TaskHandle_t pxCurrentTCBs[ config_సంఖ్య_యొక్క_CORES ];
        #అయితే_ముగింపు
        బాహ్య UBaseType_t uxSystemCallImplementations[ అంకె_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint64_t ullSystemCallLocation;  /* Address where SVC was raised. */
        __asm అస్థిర ( "MRS %0, ELR_EL1" : "=r" ( ullSystemCallLocation ) );

        #ఒకవేళ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts.
             */
            బాహ్య uint64_t * __syscalls_flash_start__;
            బాహ్య uint64_t * __syscalls_flash_end__;
        #లేకపోతే
            /* Declaration when these variable are exported from linker scripts. */
            బాహ్య uint64_t __syscalls_flash_start__[];
            బాహ్య uint64_t __syscalls_flash_end__[];
        #అయితే_ముగింపు /* #if defined( __ARMCC_VERSION ) */

        #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );
        #లేకపోతే
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCBs[ పోర్టు_GET_CORE_ID_FROM_ISR() ] );
        #అయితే_ముగింపు

        /* Checks:
         * 1. SVC is raised from the system call section (i.e. application is
         *    not raising SVC directly).
         * 2. We do not need to check that ucSystemCallNumber is within range
         *    because the assembly SVC handler checks that before calling
         *    this function.
         */
        ఒకవేళ( ( ullSystemCallLocation >= ( uint64_t ) __syscalls_flash_start__ ) &&
            ( ullSystemCallLocation <= ( uint64_t ) __syscalls_flash_end__ ) &&
            ( uxSystemCallImplementations[ uc_System_Call_సంఖ్య ] != 0 ) )
        {
            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call.
             */
            pxMpuSettings->xSystemCallInfo.ull_Link_రిజిస్టరు_At_System_Call_నమోదు = pull_Privileged_Only_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_LR ];

            /* Capture user-mode SP at system call entry. */
            uint64_t ull_User_Sp_At_నమోదు;
            __asm అస్థిర ( "MRS %0, SP_EL0" : "=r" ( ull_User_Sp_At_నమోదు ) );
            pxMpuSettings->xSystemCallInfo.ull_User_SPAt_System_Call_నమోదు = ull_User_Sp_At_నమోదు;

            /* Setup the MPU_<API> inputs, the system call stack, and SPSR. */
            __asm అస్థిర (
                "MOV X0, %0         \n"
                "MOV X1, %1         \n"
                "MOV X2, %2         \n"
                "MOV X3, %3         \n"
                "MSR ELR_EL1, %4    \n"
                "MSR SP_EL0, %5     \n"
                "MSR SPSR_EL1, %6   \n"
                :
                : "r" ( pull_Privileged_Only_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_X0 ] ),
                  "r" ( pull_Privileged_Only_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_X1 ] ),
                  "r" ( pull_Privileged_Only_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_X2 ] ),
                  "r" ( pull_Privileged_Only_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_X3 ] ),
                  "r" ( ( uint64_t ) uxSystemCallImplementations[ uc_System_Call_సంఖ్య ] ),
                  "r" ( &( pxMpuSettings->ullContext[ MAX_CONTEXT_కొలత + config_SYSTEM_CALL_దొంతర_కొలత ] ) ),
                  "r" ( పోర్టు_INITIAL_PSTATE_EL1 )
                : "memory", "x0", "x1", "x2", "x3"
            );
        }
    }
    /*-----------------------------------------------------------*/

    శూన్య vRequestSystemCallExit( శూన్య ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm అస్థిర ( "svc %0 \n" ::"i" ( పోర్టు_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }
    /*-----------------------------------------------------------*/

    శూన్య vSystemCallExit( uint64_t ull_System_Call_Return_విలువ ) /* PRIVILEGED_FUNCTION */
    {
        #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
            బాహ్య TaskHandle_t pxCurrentTCB;
        #లేకపోతే
            బాహ్య TaskHandle_t pxCurrentTCBs[ config_సంఖ్య_యొక్క_CORES ];
        #అయితే_ముగింపు
        xMPU_SETTINGS * pxMpuSettings;
        uint64_t ullSystemCallLocation; /* Address where SVC was raised. */
        __asm అస్థిర ( "MRS %0, ELR_EL1" : "=r" ( ullSystemCallLocation ) );

        #ఒకవేళ defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            బాహ్య uint64_t * __privileged_functions_start__;
            బాహ్య uint64_t * __privileged_functions_end__;
        #లేకపోతే
            /* Declaration when these variable are exported from linker scripts. */
            బాహ్య uint64_t __privileged_functions_start__[];
            బాహ్య uint64_t __privileged_functions_end__[];
        #అయితే_ముగింపు /* #if defined( __ARMCC_VERSION ) */

        #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );
        #లేకపోతే
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCBs[ పోర్టు_GET_CORE_ID_FROM_ISR() ] );
        #అయితే_ముగింపు

        /* Check:
         * SVC is raised from the privileged code (i.e. application is not
         * raising SVC directly). This SVC is only raised from
         * vRequestSystemCallExit which is in the privileged code section.
         */
        ఒకవేళ( ( ullSystemCallLocation >= ( uint64_t ) __privileged_functions_start__ ) &&
            ( ullSystemCallLocation <= ( uint64_t ) __privileged_functions_end__ ) )
        {
            __asm అస్థిర (
                "MSR ELR_EL1, %0    \n" /* Return to the MPU_<API> caller. */
                "MSR SP_EL0, %1     \n" /* Restore user SP saved at syscall entry. */
                "MSR SPSR_EL1, %3   \n" /* Ensure return to EL0. */
                "MOV X0, %2         \n" /* Move the system call return value to X0. */
                :
                : "r" ( pxMpuSettings->xSystemCallInfo.ull_Link_రిజిస్టరు_At_System_Call_నమోదు ),
                  "r" ( pxMpuSettings->xSystemCallInfo.ull_User_SPAt_System_Call_నమోదు ),
                  "r" ( ull_System_Call_Return_విలువ ),
                  "r" ( ( uint64_t ) పోర్టు_INITIAL_PSTATE_EL0 )
                : "memory"
            );
        }
    }
    /*-----------------------------------------------------------*/

    #ఒకవేళ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        శూన్య v_పోర్టు_Grant_Access_గమ్యం_Kernel_Object( TaskHandle_t x_అంతర్గత_Task_Handle,
                                             int32_t l_అంతర్గత_సూచీ_యొక్క_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_నమోదు_సూచీ, ul_Access_Control_List_నమోదు_బిట్టు;
            xMPU_SETTINGS * xTaskMpuSettings;

            /* Calculate the Access Control List entry index and bit position
             * within that entry. */
            ul_Access_Control_List_నమోదు_సూచీ = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object / పోర్టు_ACL_నమోదు_కొలత_బిట్లు );
            ul_Access_Control_List_నమోదు_బిట్టు = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object % పోర్టు_ACL_నమోదు_కొలత_బిట్లు );

            xTaskMpuSettings = xTaskGetMPUSettings( x_అంతర్గత_Task_Handle );

            /* Set the bit corresponding to the kernel object to grant access. */
            xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_నమోదు_సూచీ ] |= ( 1U << ul_Access_Control_List_నమోదు_బిట్టు );
        }
        /*-----------------------------------------------------------*/

        శూన్య v_పోర్టు_Revoke_Access_గమ్యం_Kernel_Object( TaskHandle_t x_అంతర్గత_Task_Handle,
                                              int32_t l_అంతర్గత_సూచీ_యొక్క_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_నమోదు_సూచీ, ul_Access_Control_List_నమోదు_బిట్టు;
            xMPU_SETTINGS * xTaskMpuSettings;

            /* Calculate the Access Control List entry index and bit position
             * within that entry. */
            ul_Access_Control_List_నమోదు_సూచీ = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object / పోర్టు_ACL_నమోదు_కొలత_బిట్లు );
            ul_Access_Control_List_నమోదు_బిట్టు = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object % పోర్టు_ACL_నమోదు_కొలత_బిట్లు );

            xTaskMpuSettings = xTaskGetMPUSettings( x_అంతర్గత_Task_Handle );

            /* Clear the bit corresponding to the kernel object to revoke access. */
            xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_నమోదు_సూచీ ] &= ~( 1U << ul_Access_Control_List_నమోదు_బిట్టు );
        }
        /*-----------------------------------------------------------*/

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

                ఒకవేళ( ( xTaskMpuSettings->ullTaskFlags & పోర్టు_TASK_IS_PRIVILEGED_FLAG ) == పోర్టు_TASK_IS_PRIVILEGED_FLAG )
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
        /*-----------------------------------------------------------*/
    #లేకపోతే /* configENABLE_ACCESS_CONTROL_LIST == 1 */

        పునాది_Type_t x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( int32_t l_అంతర్గత_సూచీ_యొక్క_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( శూన్య ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            తిరిగి pdTRUE;
        }
        /*-----------------------------------------------------------*/

    #అయితే_ముగింపు /* configENABLE_ACCESS_CONTROL_LIST == 1 */

#అయితే_ముగింపు /* #if ( configENABLE_MPU == 1 ) */

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    uint64_t ullAPSR;

    #ఒకవేళ ( configASSERT_DEFINED == 1 )
    {
        అస్థిర uint8_t uc_Original_ప్రాధాన్యత;
        అస్థిర uint8_t * స్థిరరాశి puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు = ( అస్థిర uint8_t * స్థిరరాశి ) ( config_అంతరాయం_CONTROLLER_పునాది_చిరునామా + పోర్టు_అంతరాయం_ప్రాధాన్యత_రిజిస్టరు_స్థానభ్రంశం );
        అస్థిర uint8_t uc_Max_ప్రాధాన్యత_విలువ;

        /* Determine how many priority bits are implemented in the GIC.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_ప్రాధాన్యత = *puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు;

        /* Determine the number of priority bits available.  First write to
         * all possible bits. */
        *puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు = పోర్టు_MAX_8_బిట్టు_విలువ;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ప్రాధాన్యత_విలువ = *puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు;

        /* Shift to the least significant bits. */
        అయితే( ( uc_Max_ప్రాధాన్యత_విలువ & పోర్టు_బిట్టు_0_సమితి ) != పోర్టు_బిట్టు_0_సమితి )
        {
            uc_Max_ప్రాధాన్యత_విలువ >>= ( uint8_t ) 0x01;
        }

        /* Sanity check configUNIQUE_INTERRUPT_PRIORITIES matches the read
         * value. */
        configASSERT( uc_Max_ప్రాధాన్యత_విలువ >= పోర్టు_అత్యల్ప_అంతరాయం_ప్రాధాన్యత );


        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు = uc_Original_ప్రాధాన్యత;
    }
    #అయితే_ముగింపు /* configASSERT_DEFINED */

    __asm అస్థిర ( "MRS %0, CurrentEL" : "=r" ( ullAPSR ) );
    ullAPSR &= పోర్టు_APSR_బహుళకం_బిట్లు_ముసుగు;

    configASSERT( ullAPSR == పోర్టు_EL1 );

    #ఒకవేళ ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        v_అమరిక_MPU();
    }
    #అయితే_ముగింపు /* #if ( configENABLE_MPU == 1 ) */

    /* Interrupts are turned off in the CPU itself to ensure a tick does
     * not execute while the scheduler is being started.  Interrupts are
     * automatically turned back on in the CPU when the first task starts
     * executing. */
    __asm అస్థిర ( "MSR DAIFSET, #2\n"
                     "DSB SY\n"
                     "ISB SY\n" ::: "memory" );
    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )
        /* Start the timer that generates the tick ISR. */
        config_అమరిక_TICK_అంతరాయం();
        uc_Primary_Core_Init_పూర్తి_Flag = 1;
        __asm అస్థిర ( "SEV                       \n"
                         "DSB SY                    \n"
                         "ISB SY                    \n"
                         ::: "memory" );
        /* Hold the primary core here until all the secondary cores are ready, this would be achieved only when
         * all elements of ucSecondaryCoresReadyFlags are set.
         */
        అయితే( 1 )
        {
            పునాది_Type_t xAllCoresReady = pdTRUE;
            కొరకు( uint8_t ucCoreID = 0; ucCoreID < ( config_సంఖ్య_యొక్క_CORES - 1 ); ucCoreID++ )
            {
                ఒకవేళ( ucSecondaryCoresReadyFlags[ ucCoreID ] != pdTRUE )
                {
                    xAllCoresReady = pdFALSE;
                    ఆపు;
                }
            }

            ఒకవేళ ( xAllCoresReady == pdTRUE )
            {
                ఆపు;
            }
        }
    #లేకపోతే /* if ( configNUMBER_OF_CORES > 1 ) */
        /* Start the timer that generates the tick ISR. */
        config_అమరిక_TICK_అంతరాయం();
    #అయితే_ముగింపు /* if ( configNUMBER_OF_CORES > 1 ) */

    #ఒకవేళ ( configENABLE_MPU == 1 )
        xSchedulerRunning = pdTRUE;

        /* Enable the Memory Protection Unit (MPU)
         * MPU is only enabled after the primary and secondary handshakes
         * are done as to prevent inconsistent MPU regions attributes across
         * different cores resulting in unupdated values of the handshake
         * flags. 
         */
        vEnableMPU();
    #అయితే_ముగింపు /* #if ( configENABLE_MPU == 1 ) */

    /* Start the first task executing. */
    v_పోర్టు_Restore_Task_Context();

    తిరిగి 0;
}

/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య ) /* PRIVILEGED_FUNCTION */
{
    /* Stub implementation for ports where there is nothing to return to
     * Artificially force an assert. */
    configASSERT( ఖాళీ );
}

/*-----------------------------------------------------------*/

#ఒకవేళ  ( config_సంఖ్య_యొక్క_CORES == 1 )
    PRIVILEGED_FUNCTION శూన్య v_పోర్టు_Enter_Critical( శూన్య )
    {
        /* Mask interrupts up to the max syscall interrupt priority. */
        ux_పోర్టు_సమితి_అంతరాయం_ముసుగు();

        /* Now interrupts are disabled ullCriticalNesting can be accessed
         * directly.  Increment ullCriticalNesting to keep a count of how many times
         * portENTER_CRITICAL() has been called. */
        ullCriticalNesting++;

        /* This is not the interrupt safe version of the enter critical function so
         * assert() if it is being called from an interrupt context.  Only API
         * functions that end in "FromISR" can be used in an interrupt.  Only assert if
         * the critical nesting count is 1 to protect against recursive calls if the
         * assert function also uses a critical section. */
        ఒకవేళ( ullCriticalNesting == 1ULL )
        {
            configASSERT( ull_పోర్టు_అంతరాయం_Nesting == 0 );
        }
    }

/*-----------------------------------------------------------*/

    PRIVILEGED_FUNCTION శూన్య v_పోర్టు_Exit_Critical( శూన్య )
    {
        ఒకవేళ( ullCriticalNesting > పోర్టు_NO_CRITICAL_NESTING )
        {
            /* Decrement the nesting count as the critical section is being
             * exited. */
            ullCriticalNesting--;

            /* If the nesting level has reached zero then all interrupt
             * priorities must be re-enabled. */
            ఒకవేళ( ullCriticalNesting == పోర్టు_NO_CRITICAL_NESTING )
            {
                /* Critical nesting has reached zero so all interrupt priorities
                 * should be unmasked. */
                పోర్టు_CLEAR_అంతరాయం_PRIORITIES_ముసుగు();
            }
        }
    }
#అయితే_ముగింపు /* if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/

శూన్య FreeRTOS_Tick_Handler( శూన్య )
{
    /* Must be the lowest possible priority. */
    uint64_t ull_Running_అంతరాయం_ప్రాధాన్యత;
    __asm అస్థిర ( "MRS %0, ICC_RPR_EL1" : "=r" ( ull_Running_అంతరాయం_ప్రాధాన్యత ) );

    configASSERT( ull_Running_అంతరాయం_ప్రాధాన్యత == ( పోర్టు_అత్యల్ప_USABLE_అంతరాయం_ప్రాధాన్యత << పోర్టు_ప్రాధాన్యత_జరుపు ) );

    /* Interrupts should not be enabled before this point. */
    #ఒకవేళ ( configASSERT_DEFINED == 1 )
    {
        uint64_t ull_ముసుగు_బిట్లు;

        __asm అస్థిర ( "MRS %0, DAIF" : "=r" ( ull_ముసుగు_బిట్లు )::"memory" );
        configASSERT( ( ull_ముసుగు_బిట్లు & పోర్టు_DAIF_I ) != 0 );
    }
    #అయితే_ముగింపు /* configASSERT_DEFINED */

    /* Set interrupt mask before altering scheduler structures. The tick
     * interrupt runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value.  It is
     * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
     * updated.
     */
    UBaseType_t ux_అంతరాయం_స్థితి = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();

    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )
        UBaseType_t x = పోర్టు_ENTER_CRITICAL_FROM_ISR();
    #అయితే_ముగింపు /* if ( configNUMBER_OF_CORES > 1 ) */

    /* Increment the RTOS tick. */
    ఒకవేళ( xTaskIncrementTick() != pdFALSE )
    {
        #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
            ull_పోర్టు_Yield_Required = pdTRUE;
        #లేకపోతే
            ull_పోర్టు_Yield_Required[ పోర్టు_GET_CORE_ID_FROM_ISR() ] = pdTRUE;
        #అయితే_ముగింపు
    }
    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )
        పోర్టు_EXIT_CRITICAL_FROM_ISR(x);
    #అయితే_ముగింపు /* if ( configNUMBER_OF_CORES > 1 ) */

    /* Ensure all interrupt priorities are active again. */
    పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( ux_అంతరాయం_స్థితి );

    /* Ok to enable interrupts after the interrupt source has been cleared. */
    config_CLEAR_TICK_అంతరాయం();
}

/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TASK_FPU_SUPPORT == పోర్టు_TASK_NO_FPU_CONTEXT_BY_DEFAULT )

    శూన్య v_పోర్టు_Task_ఉపయోగిస్తుంది_FPU( శూన్య )
    {
        /* A task is registering the fact that it needs an FPU context.  Set the
         * FPU flag (which is saved as part of the task context). */
        #ఒకవేళ  ( config_సంఖ్య_యొక్క_CORES == 1 )
            ull_పోర్టు_Task_Has_FPUContext = pdTRUE;
        #లేకపోతే
            ull_పోర్టు_Task_Has_FPUContext[ పోర్టు_GET_CORE_ID() ] = pdTRUE;
        #అయితే_ముగింపు

        /* Consider initialising the FPSR here - but probably not necessary in
         * AArch64. */
    }

#అయితే_ముగింపు /* configUSE_TASK_FPU_SUPPORT */

/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Clear_అంతరాయం_ముసుగు( UBaseType_t ux_New_ముసుగు_విలువ )
{
    ఒకవేళ( ux_New_ముసుగు_విలువ == పోర్టు_UNMASK_విలువ )
    {
        /* Unmask all interrupt priorities. */
        పోర్టు_CLEAR_అంతరాయం_PRIORITIES_ముసుగు();
    }
    లేకపోతే
    {
        __asm అస్థిర (
            "SVC %0 \n"
            :
            : "i" ( పోర్టు_SVC_UNMASK_INTERRUPTS )
            : "memory"
        );
    }
}

శూన్య v_పోర్టు_Clear_అంతరాయం_ముసుగు_From_ISR( UBaseType_t ux_New_ముసుగు_విలువ )
{
    __asm అస్థిర (
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
        : "r" ( ux_New_ముసుగు_విలువ )
    );
}
/*-----------------------------------------------------------*/

UBaseType_t ux_పోర్టు_సమితి_అంతరాయం_ముసుగు( శూన్య )
{
    UBaseType_t ullPMRValue;

    /* Use SVC so this can be called safely from EL0 tasks. */
    __asm అస్థిర (
        "svc %1        \n"
        "mov %0, x0    \n"
        : "=r" ( ullPMRValue )
        : "i" ( పోర్టు_SVC_ముసుగు_ALL_INTERRUPTS )
        : "x0", "memory"
    );

    తిరిగి ullPMRValue;
}

/* EL1/ISR variant to avoid SVC from interrupt context. */
UBaseType_t ux_పోర్టు_సమితి_అంతరాయం_ముసుగు_From_ISR( శూన్య )
{
    UBaseType_t ullPMRValue;

    __asm అస్థిర ( "MRS %0, ICC_PMR_EL1" : "=r" ( ullPMRValue ) );

    ఒకవేళ( ullPMRValue != ( config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత << పోర్టు_ప్రాధాన్యత_జరుపు ) )
    {
        __asm అస్థిర ( "MSR DAIFSET, #2        \n"
                         "DSB SY                 \n"
                         "ISB SY                 \n"
                         "MSR ICC_PMR_EL1, %0    \n"
                         "DSB SY                 \n"
                         "ISB SY                 \n"
                         "MSR DAIFCLR, #2        \n"
                         "DSB SY                 \n"
                         "ISB SY                 \n"
                         ::"r" ( config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత << పోర్టు_ప్రాధాన్యత_జరుపు ) : "memory" );
    }

    తిరిగి ullPMRValue;
}

/*-----------------------------------------------------------*/

#ఒకవేళ ( configASSERT_DEFINED == 1 )

    శూన్య v_పోర్టు_Validate_అంతరాయం_ప్రాధాన్యత( శూన్య )
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
        uint64_t ull_Running_అంతరాయం_ప్రాధాన్యత;
        __asm అస్థిర ( "MRS %0, ICC_RPR_EL1" : "=r" ( ull_Running_అంతరాయం_ప్రాధాన్యత ) );
        configASSERT( ull_Running_అంతరాయం_ప్రాధాన్యత >= ( config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత << పోర్టు_ప్రాధాన్యత_జరుపు ) );
    }

#అయితే_ముగింపు /* configASSERT_DEFINED */

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
 __attribute__( ( weak ) ) శూన్య vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR )
{
    ( శూన్య ) ulICCIAR;
    configASSERT( ( అస్థిర శూన్య * ) ఖాళీ );
}

/*-----------------------------------------------------------*/

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )

    /* Which core owns the lock? Keep in privileged, shareable RAM. */
    PRIVILEGED_దత్తాంశం అస్థిర uint64_t ullOwnedByCore[ పోర్టు_MAX_CORE_లెక్క ];
    /* Lock count a core owns. */
    PRIVILEGED_దత్తాంశం అస్థిర uint64_t ull_Recursion_లెక్క_By_తాళం[ e_తాళం_లెక్క ];
    /* Index 0 is used for ISR lock and Index 1 is used for task lock. */
    PRIVILEGED_దత్తాంశం uint32_t ul_Gate_మాట[ e_తాళం_లెక్క ];

    శూన్య v_అంతరాయం_Core( uint32_t ul_అంతరాయం_ID, uint8_t ucCoreID )
    {
        uint64_t ulRegVal = 0;
        uint32_t ul_Core_ముసుగు = ( 1UL << ucCoreID );
        ulRegVal |= ( (ul_Core_ముసుగు & 0xFFFF) | ( ( ul_అంతరాయం_ID & 0xF ) << 24U ) );
        __asm అస్థిర (
            "str  x0, [ sp, #-0x10 ]!       \n"
            "mov  x0, %0                    \n"
            "svc  %1                        \n"
            "ldr  x0, [ sp ], # 0x10        \n"
            :
            : "r" ( ulRegVal ), "i" ( పోర్టు_SVC_అంతరాయం_CORE )
            : "memory", "w1"
        );
    }

/*-----------------------------------------------------------*/

    స్థిర అంతఃవరుస శూన్య prvSpinUnlock( uint32_t * ul_తాళం )
    {
        /* Conservative unlock: preserve original barriers for broad HW/FVP. */
        __asm అస్థిర (
            "dmb sy         \n"
            "mov w1, #0     \n"
            "str w1, [%x0]  \n"
            "sev            \n"
            "dsb sy         \n"
            "isb sy         \n"
            :
            : "r" ( ul_తాళం )
            : "memory", "w1"
        );
    }

/*-----------------------------------------------------------*/

    స్థిర అంతఃవరుస uint32_t prvSpinTrylock( uint32_t * ul_తాళం )
    {
        /*
         * Conservative LDXR/STXR trylock:
         * - Return 1 immediately if busy, clearing exclusive state (CLREX).
         * - Retry STXR only on spurious failure when observed free.
         * - DMB on success to preserve expected acquire semantics.
         */
        నమోదు uint32_t ulRet;
        __asm అస్థిర (
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
            : "r" ( ul_తాళం )
            : "memory", "w1", "w2", "w3"
        );

        తిరిగి ulRet;
    }

/*-----------------------------------------------------------*/

    /* Read 64b value shared between cores. */
    స్థిర అంతఃవరుస uint64_t prvGet64( అస్థిర uint64_t * x )
    {
        __asm( "dsb sy" );
        తిరిగి *x;
    }

/*-----------------------------------------------------------*/

    /* Write 64b value shared between cores. */
    స్థిర అంతఃవరుస శూన్య prvSet64( అస్థిర uint64_t * x,
                                 uint64_t విలువ )
    {
        *x = విలువ;
        __asm( "dsb sy" );
    }

/*-----------------------------------------------------------*/

    శూన్య v_పోర్టు_Recursive_తాళం( uint8_t ucCoreID,
                             e_పోర్టు_RTOSLock e_తాళం_అంకె,
                             పునాది_Type_t uxAcquire )
    {
        /* Validate the core ID and lock number. */
        configASSERT( ucCoreID < పోర్టు_MAX_CORE_లెక్క );
        configASSERT( e_తాళం_అంకె < e_తాళం_లెక్క );

        uint32_t ul_తాళం_బిట్టు = 1u << e_తాళం_అంకె;

        /* Lock acquire */
        ఒకవేళ( uxAcquire )
        {
            /* Check if spinlock is available.
             * If spinlock is not available check if the core owns the lock.
             * If the core owns the lock wait increment the lock count by the core.
             * If core does not own the lock wait for the spinlock.
             */
            ఒకవేళ( prvSpinTrylock( &ul_Gate_మాట[ e_తాళం_అంకె ] ) != 0 )
            {
                /* Check if the core owns the spinlock. */
                ఒకవేళ( prvGet64( &ullOwnedByCore[ ucCoreID ] ) & ul_తాళం_బిట్టు )
                {
                    configASSERT( prvGet64( &ull_Recursion_లెక్క_By_తాళం[ e_తాళం_అంకె ] ) != 255u );
                    prvSet64( &ull_Recursion_లెక్క_By_తాళం[ e_తాళం_అంకె ], ( prvGet64( &ull_Recursion_లెక్క_By_తాళం[ e_తాళం_అంకె ] ) + 1 ) );
                    తిరిగి;
                }

                /* Preload the gate word into the cache. */
                uint32_t dummy = ul_Gate_మాట[ e_తాళం_అంకె ];
                dummy++;

                అయితే( prvSpinTrylock( &ul_Gate_మాట[ e_తాళం_అంకె ] ) != 0 )
                {
                   /* Follow Arm's recommended way of sleeping
                    * sevl is used to prime the wait loop.
                    * The first wfe wakes immediately because sevl has set the flag.
                    * Check the lock, if it's not available, issue a second wfe to sleep.
                    * This guarantees the core actually goes to sleep.
                    */
                    __asm అస్థిర (
                        "sevl            \n"
                        "1: wfe          \n"
                        "ldr w2, [%x0]   \n"
                        "cbnz w2, 1b     \n"
                        :
                        : "r" ( &ul_Gate_మాట[ e_తాళం_అంకె ] )
                        : "memory", "w2"
                    );
                }
            }

            /* Add barrier to ensure lock is taken before we proceed. */
            __asm__ __volatile__ ( "dmb sy" ::: "memory" );

            /* Assert the lock count is 0 when the spinlock is free and is acquired. */
            configASSERT( prvGet64( &ull_Recursion_లెక్క_By_తాళం[ e_తాళం_అంకె ] ) == 0 );

            /* Set lock count as 1. */
            prvSet64( &ull_Recursion_లెక్క_By_తాళం[ e_తాళం_అంకె ], 1 );
            /* Set ullOwnedByCore. */
            prvSet64( &ullOwnedByCore[ ucCoreID ], ( prvGet64( &ullOwnedByCore[ ucCoreID ] ) | ul_తాళం_బిట్టు ) );
        }
        /* Lock release. */
        లేకపోతే
        {
            /* Assert the lock is not free already. */
            configASSERT( ( prvGet64( &ullOwnedByCore[ ucCoreID ] ) & ul_తాళం_బిట్టు ) != 0 );
            configASSERT( prvGet64( &ull_Recursion_లెక్క_By_తాళం[ e_తాళం_అంకె ] ) != 0 );

            /* Reduce ullRecursionCountByLock by 1. */
            prvSet64( &ull_Recursion_లెక్క_By_తాళం[ e_తాళం_అంకె ], ( prvGet64( &ull_Recursion_లెక్క_By_తాళం[ e_తాళం_అంకె ] ) - 1 ) );

            ఒకవేళ( !prvGet64( &ull_Recursion_లెక్క_By_తాళం[ e_తాళం_అంకె ] ) )
            {
                prvSet64( &ullOwnedByCore[ ucCoreID ], ( prvGet64( &ullOwnedByCore[ ucCoreID ] ) & ~ul_తాళం_బిట్టు ) );
                prvSpinUnlock( &ul_Gate_మాట[ e_తాళం_అంకె ] );
                /* Add barrier to ensure lock status is reflected before we proceed. */
                __asm__ __volatile__ ( "dmb sy" ::: "memory" );
            }
        }
    }

/*-----------------------------------------------------------*/

    uint8_t uc_పోర్టు_Get_Core_ID( శూన్య )
    {
        /* Use SVC to obtain the core ID in a way that is safe when called
         * from EL0 tasks. ISRs and EL1 code should use
         * ucPortGetCoreIDFromIsr()/portGET_CORE_ID_FROM_ISR().
         */
        uint8_t ucCoreID;
        __asm అస్థిర (
            "svc %1             \n"
            "mov %w0, w0        \n"
            : "=r" ( ucCoreID )
            : "i" ( పోర్టు_SVC_GET_CORE_ID )
            : "x0", "memory"
        );
        తిరిగి ucCoreID;
    }

/*-----------------------------------------------------------*/

    uint8_t uc_పోర్టు_Get_Core_IDFrom_Isr ( శూన్య ) /* PRIVILEGED_FUNCTION */
    {
        uint64_t ullMpidrEl1;
        __asm అస్థిర ( "MRS %0, MPIDR_EL1" : "=r" ( ullMpidrEl1 ) );

        తిరిగి ( uint8_t ) ( ullMpidrEl1 & 0xff );
    }

/*------------------------------------------------------------*/
    శూన్య FreeRTOS_SGI_Handler( శూన్య )
    {
        /* Must be the lowest possible priority. */
        uint64_t ull_Running_అంతరాయం_ప్రాధాన్యత;
        __asm అస్థిర ( "MRS %0, ICC_RPR_EL1" : "=r" ( ull_Running_అంతరాయం_ప్రాధాన్యత ) );

        configASSERT( ull_Running_అంతరాయం_ప్రాధాన్యత == ( పోర్టు_అత్యల్ప_USABLE_అంతరాయం_ప్రాధాన్యత << పోర్టు_ప్రాధాన్యత_జరుపు ) );
        /* Interrupts should not be enabled before this point. */
        #ఒకవేళ ( configASSERT_DEFINED == 1 )
        {
            uint64_t ull_ముసుగు_బిట్లు;

            __asm అస్థిర ( "mrs %0, DAIF" : "=r" ( ull_ముసుగు_బిట్లు )::"memory" );
            configASSERT( ( ull_ముసుగు_బిట్లు & పోర్టు_DAIF_I ) != 0 );
        }
        #అయితే_ముగింపు /* configASSERT_DEFINED */

        /* Set interrupt mask before altering scheduler structures. The SGI
         * interrupt runs at the lowest priority, so interrupts cannot already be masked,
         * so there is no need to save and restore the current mask value.  It is
         * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
         * updated.
         */
        UBaseType_t ux_అంతరాయం_స్థితి = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();

        UBaseType_t ux_Saved_అంతరాయం_స్థితి = పోర్టు_ENTER_CRITICAL_FROM_ISR();
        #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
            ull_పోర్టు_Yield_Required = pdTRUE;
        #లేకపోతే
            ull_పోర్టు_Yield_Required[ పోర్టు_GET_CORE_ID_FROM_ISR() ] = pdTRUE;
        #అయితే_ముగింపు
        పోర్టు_EXIT_CRITICAL_FROM_ISR( ux_Saved_అంతరాయం_స్థితి );
        పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( ux_అంతరాయం_స్థితి );
    }

/*-----------------------------------------------------------*/

#అయితే_ముగింపు /* if( configNUMBER_OF_CORES > 1 ) */
