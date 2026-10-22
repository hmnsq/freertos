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
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <string.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers. That should only be done when
 * task.h is included from an application file. */
#define MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#அந்தர்பாவ "FreeRTOS.h"
#அந்தர்பாவ "task.h"

/* MPU includes. */
#அந்தர்பாவ "mpu_wrappers.h"
#அந்தர்பாவ "mpu_syscall_numbers.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ifndef configINTERRUPT_CONTROLLER_BASE_ADDRESS
    #error configINTERRUPT_CONTROLLER_BASE_ADDRESS must be defined.  Refer to Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#endif

#ifndef configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET
    #error configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET must be defined.  Refer to Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#endif

#ifndef configUNIQUE_INTERRUPT_PRIORITIES
    #error configUNIQUE_INTERRUPT_PRIORITIES must be defined.  Refer to Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#endif

#ifndef configSETUP_TICK_INTERRUPT
    #error configSETUP_TICK_INTERRUPT() must be defined.  Refer to Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#endif /* configSETUP_TICK_INTERRUPT */

#ifndef configMAX_API_CALL_INTERRUPT_PRIORITY
    #error configMAX_API_CALL_INTERRUPT_PRIORITY must be defined.  Refer to Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#endif

#எனில் configMAX_API_CALL_INTERRUPT_PRIORITY == 0
    #error "configMAX_API_CALL_INTERRUPT_PRIORITY must not be set to 0"
#endif

#எனில் configMAX_API_CALL_INTERRUPT_PRIORITY > configUNIQUE_INTERRUPT_PRIORITIES
    #error "configMAX_API_CALL_INTERRUPT_PRIORITY must be less than or equal to configUNIQUE_INTERRUPT_PRIORITIES as the lower the numeric priority value the higher the logical interrupt priority"
#endif

#எனில் configUSE_PORT_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #எனில் ( configMAX_PRIORITIES > 32 )
        #error "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 different priorities as tasks that share a priority will time slice."
    #endif
#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#எனில் configMAX_API_CALL_INTERRUPT_PRIORITY <= ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )
    #error "configMAX_API_CALL_INTERRUPT_PRIORITY must be greater than ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )"
#endif

#ifndef configCLEAR_TICK_INTERRUPT
    #error configCLEAR_TICK_INTERRUPT must be defined in FreeRTOSConfig.h to clear which ever interrupt was used to generate the tick interrupt.
#endif

#எனில் config_எண்_OF_CORES < 1
    #error config_எண்_OF_CORES must be set to 1 or greater.  If the application is not using multiple cores then set config_எண்_OF_CORES to 1.
#endif /* configNUMBER_OF_CORES < 1 */

#ifndef configENABLE_MPU
    #error configENABLE_MPU must be defined in FreeRTOSConfig.h. Set configENABLE_MPU to 1 to enable the MPU or 0 to disable the MPU.
#endif /* #if ( configENABLE_MPU == 1 ) */

#எனில் ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 != 0) )
    #error Arm Cortex-R82 port supports only MPU Wrapper V2.
#endif /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 != 0) */

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#define portNO_CRITICAL_NESTING    ( ( size_t ) 0 )

/* Macro to unmask all interrupt priorities. */
#define portCLEAR_INTERRUPT_PRIORITIES_MASK()    __asm நிலையற்ற ( "SVC %0" : : "i" ( portSVC_UNMASK_ALL_INTERRUPTS ) : "memory" )

/* Macro to unmask all interrupt priorities from EL1. */
#define portCLEAR_INTERRUPT_PRIORITIES_MASK_FROM_EL1()  \
{                                                       \
    __asm நிலையற்ற (                                    \
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
    : "i" ( port_UNMASK_மதிப்பு )                          \
    );                                                  \
}

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#define portNO_FLOATING_POINT_CONTEXT    ( ( அடுக்கு_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#define portSP_ELx                       ( ( அடுக்கு_Type_t ) 0x01 )
#define portSP_EL0                       ( ( அடுக்கு_Type_t ) 0x00 )
#define portEL1                          ( ( அடுக்கு_Type_t ) 0x04 )
#define portEL0                          ( ( அடுக்கு_Type_t ) 0x00 )

#define portINITIAL_PSTATE_EL0           ( portEL0 | portSP_EL0 )
#define portINITIAL_PSTATE_EL1           ( portEL1 | portSP_EL0 )

/* Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero. */
#define port_இருமம்_POINT_BITS            ( ( uint8_t ) 0x03 )

/* Masks all bits in the APSR other than the mode bits. */
#define portAPSR_MODE_BITS_MASK          ( 0x0C )

/* The I bit in the DAIF bits. */
#define portDAIF_I                       ( 0x80 )

#define port_MAX_8_BIT_மதிப்பு              ( ( uint8_t ) 0xff )
#define portBIT_0_SET                    ( ( uint8_t ) 0x01 )

/* The space on the stack required to hold the FPU registers.
 * There are 32 128-bit plus 2 64-bit status registers. */
#define port_FPU_REGISTER_சொற்கள்           ( ( 32 * 2 ) + 2 )

/*-----------------------------------------------------------*/

#எனில் ( configENABLE_MPU == 1 )

    /**
     * @brief Setup the Memory Protection Unit (MPU).
     */
    PRIVILEGED_FUNCTION வெறுமை vSetupMPU( வெறுமை );

    /**
     * @brief Enable the Memory Protection Unit (MPU).
     */
    PRIVILEGED_FUNCTION வெறுமை vEnableMPU( வெறுமை );

    /**
     * @brief Called from an ISR and returns the core ID the code is executing on.
     *
     * @return uint8_t The core ID.
     */
    PRIVILEGED_FUNCTION uint8_t ucPortGetCoreIDFromIsr( வெறுமை );

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    PRIVILEGED_FUNCTION BaseType_t xPortIsTaskPrivileged( வெறுமை );

    /**
     * @brief Extract MPU region's access permissions from the Protection Region Base Address Register
     * (PRBAR_EL1) value.
     *
     * @param ullPrbarEl1Value PRBAR_EL1 value for the MPU region.
     *
     * @return uint32_t Access permissions.
     */
    PRIVILEGED_FUNCTION நிலையான uint32_t prvGetRegionAccessPermissions( uint64_t ull_Prbar_El1_மதிப்பு );

    /**
     * @brief Does the necessary work to enter a system call.
     *
     * @param pullPrivilegedOnlyTaskStack The task's privileged SP when the SVC was raised.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    PRIVILEGED_FUNCTION வெறுமை vSystemCallEnter( uint64_t * pull_Privileged_Only_Task_அடுக்கு,
                                               uint8_t uc_System_Call_எண் );

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    PRIVILEGED_FUNCTION __attribute__( ( naked ) ) வெறுமை vRequestSystemCallExit( வெறுமை );

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param ullSystemCallReturnValue The actual system call return value.
     */
    PRIVILEGED_FUNCTION வெறுமை vSystemCallExit( uint64_t ull_System_Call_Return_மதிப்பு );

#endif /* #if ( configENABLE_MPU == 1 ) */

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
வெளி வெறுமை vPortRestoreTaskContext( வெறுமை );
வெளி வெறுமை vGIC_EnableIRQ( uint32_t ulInterruptID );
வெளி வெறுமை vGIC_SetPriority( uint32_t ulInterruptID, uint32_t ulPriority );
வெளி வெறுமை vGIC_PowerUpRedistributor( வெறுமை );
வெளி வெறுமை vGIC_EnableCPUInterface( வெறுமை );

/*-----------------------------------------------------------*/

#எனில் ( config_எண்_OF_CORES == 1 )

    PRIVILEGED_DATA நிலையற்ற uint64_t ullCriticalNesting = 0ULL;

    /* Saved as part of the task context. If ullPortTaskHasFPUContext is non-zero
     * then floating point context must be saved and restored for the task. */
    PRIVILEGED_DATA uint64_t ullPortTaskHasFPUContext = pdFALSE;

    /* Set to 1 to pend a context switch from an ISR. */
    PRIVILEGED_DATA uint64_t ullPortYieldRequired = pdFALSE;

    /* Counts the interrupt nesting depth. A context switch is only performed if
     * if the nesting depth is 0. */
    PRIVILEGED_DATA uint64_t ullPortInterruptNesting = 0;

#இல்லையெனில் /* #if ( configNUMBER_OF_CORES == 1 ) */
    PRIVILEGED_DATA நிலையற்ற uint64_t ullCriticalNestings[ config_எண்_OF_CORES ] = { 0 };

    /* Flags to check if the secondary cores are ready. */
    PRIVILEGED_DATA நிலையற்ற uint8_t ucSecondaryCoresReadyFlags[ config_எண்_OF_CORES - 1 ] = { 0 };

    /* Flag to signal that the primary core has done all the shared initialisations. */
    PRIVILEGED_DATA நிலையற்ற uint8_t ucPrimaryCoreInitDoneFlag = 0;

    /* Saved as part of the task context. If ullPortTaskHasFPUContext is non-zero
     * then floating point context must be saved and restored for the task. */
    PRIVILEGED_DATA uint64_t ullPortTaskHasFPUContext[ config_எண்_OF_CORES ] = { pdFALSE };

    /* Set to 1 to pend a context switch from an ISR. */
    PRIVILEGED_DATA uint64_t ullPortYieldRequired[ config_எண்_OF_CORES ] = { pdFALSE };

    /* Counts the interrupt nesting depth. A context switch is only performed if
     * if the nesting depth is 0. */
    PRIVILEGED_DATA uint64_t ullPortInterruptNestings[ config_எண்_OF_CORES ] = { 0 };

#endif /* #if ( configNUMBER_OF_CORES == 1 ) */

#எனில் ( configENABLE_MPU == 1 )
    /* Set to pdTRUE when the scheduler is started. */
    PRIVILEGED_DATA நிலையான BaseType_t xSchedulerRunning = pdFALSE;
#endif /* ( configENABLE_MPU == 1 ) */
/*-----------------------------------------------------------*/

#எனில் ( configENABLE_MPU == 1 )

    அடுக்கு_Type_t * px_Port_Initialise_அடுக்கு( அடுக்கு_Type_t * px_உச்சி_Of_அடுக்கு,
                                         TaskFunction_t pxCode,
                                         வெறுமை * pvParameters,
                                         BaseType_t xRunPrivileged,
                                         xMPU_SETTINGS * xMPUSettings )
    {
        uint32_t ulIndex = 0;

        /* Layout must match portRESTORE_CONTEXT pop order (descending stack):
         * 1) FPU flag, 2) Critical nesting, 3) Optional FPU save area,
         * 4) ELR (PC), 5) SPSR (PSTATE), 6) GPRs in restore order pairs.
         */

        /* 1) FPU flag and 2) Critical nesting. */
        #எனில் ( configUSE_TASK_FPU_SUPPORT == portTASK_NO_FPU_CONTEXT_BY_DEFAULT )
            xMPUSettings->ullContext[ ulIndex++ ] = portNO_FLOATING_POINT_CONTEXT; /* FPU flag */
            xMPUSettings->ullContext[ ulIndex++ ] = portNO_CRITICAL_NESTING;       /* Critical nesting */
        #அல்லதெனில் ( configUSE_TASK_FPU_SUPPORT == portTASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
            xMPUSettings->ullContext[ ulIndex++ ] = pdTRUE;                        /* FPU flag */
            xMPUSettings->ullContext[ ulIndex++ ] = portNO_CRITICAL_NESTING;       /* Critical nesting */
            #எனில் ( config_எண்_OF_CORES == 1 )
                ullPortTaskHasFPUContext = pdTRUE;
            #இல்லையெனில்
                ullPortTaskHasFPUContext[ portGET_CORE_ID() ] = pdTRUE;
            #endif
        #இல்லையெனில்
            #error "Invalid configUSE_TASK_FPU_SUPPORT setting - must be 1 or 2."
        #endif

        /* 3) Optional FPU save area immediately after the flag+critical pair. */
        #எனில் ( configUSE_TASK_FPU_SUPPORT == portTASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
            memset( &xMPUSettings->ullContext[ ulIndex ], 0x00, port_FPU_REGISTER_சொற்கள் * அளவு( அடுக்கு_Type_t ) );
            ulIndex += port_FPU_REGISTER_சொற்கள்;
        #endif

        /* 4) ELR (PC) and 5) SPSR (PSTATE). */
        xMPUSettings->ullContext[ ulIndex++ ] = ( அடுக்கு_Type_t ) pxCode; /* ELR */

        எனில்( xRunPrivileged == pdTRUE )
        {
            xMPUSettings->ullContext[ ulIndex++ ] = portINITIAL_PSTATE_EL1;    /* SPSR */
        }
        இல்லையெனில்
        {
            xMPUSettings->ullContext[ ulIndex++ ] = portINITIAL_PSTATE_EL0;    /* SPSR */
        }

        /* 6) General-purpose registers in the order expected by restoreallgpregisters. */
        xMPUSettings->ullContext[ ulIndex++ ] = ( அடுக்கு_Type_t ) 0x00;         /* X30 (LR) */
        xMPUSettings->ullContext[ ulIndex++ ] = ( அடுக்கு_Type_t ) 0x00;         /* XZR (dummy) */

        xMPUSettings->ullContext[ ulIndex++ ] = 0x2828282828282828ULL;        /* X28 */
        xMPUSettings->ullContext[ ulIndex++ ] = 0x2929292929292929ULL;        /* X29 */

        xMPUSettings->ullContext[ ulIndex++ ] = 0x2626262626262626ULL;        /* X26 */
        xMPUSettings->ullContext[ ulIndex++ ] = 0x2727272727272727ULL;        /* X27 */

        xMPUSettings->ullContext[ ulIndex++ ] = 0x2424242424242424ULL;        /* X24 */
        xMPUSettings->ullContext[ ulIndex++ ] = 0x2525252525252525ULL;        /* X25 */

        xMPUSettings->ullContext[ ulIndex++ ] = 0x2222222222222222ULL;        /* X22 */
        xMPUSettings->ullContext[ ulIndex++ ] = 0x2323232323232323ULL;        /* X23 */

        xMPUSettings->ullContext[ ulIndex++ ] = 0x2020202020202020ULL;        /* X20 */
        xMPUSettings->ullContext[ ulIndex++ ] = 0x2121212121212121ULL;        /* X21 */

        xMPUSettings->ullContext[ ulIndex++ ] = 0x1818181818181818ULL;        /* X18 */
        xMPUSettings->ullContext[ ulIndex++ ] = 0x1919191919191919ULL;        /* X19 */

        xMPUSettings->ullContext[ ulIndex++ ] = 0x1616161616161616ULL;        /* X16 */
        xMPUSettings->ullContext[ ulIndex++ ] = 0x1717171717171717ULL;        /* X17 */

        xMPUSettings->ullContext[ ulIndex++ ] = 0x1414141414141414ULL;        /* X14 */
        xMPUSettings->ullContext[ ulIndex++ ] = 0x1515151515151515ULL;        /* X15 */

        xMPUSettings->ullContext[ ulIndex++ ] = 0x1212121212121212ULL;        /* X12 */
        xMPUSettings->ullContext[ ulIndex++ ] = 0x1313131313131313ULL;        /* X13 */

        xMPUSettings->ullContext[ ulIndex++ ] = 0x1010101010101010ULL;        /* X10 */
        xMPUSettings->ullContext[ ulIndex++ ] = 0x1111111111111111ULL;        /* X11 */

        xMPUSettings->ullContext[ ulIndex++ ] = 0x0808080808080808ULL;        /* X8 */
        xMPUSettings->ullContext[ ulIndex++ ] = 0x0909090909090909ULL;        /* X9 */

        xMPUSettings->ullContext[ ulIndex++ ] = 0x0606060606060606ULL;        /* X6 */
        xMPUSettings->ullContext[ ulIndex++ ] = 0x0707070707070707ULL;        /* X7 */

        xMPUSettings->ullContext[ ulIndex++ ] = 0x0404040404040404ULL;        /* X4 */
        xMPUSettings->ullContext[ ulIndex++ ] = 0x0505050505050505ULL;        /* X5 */

        xMPUSettings->ullContext[ ulIndex++ ] = 0x0202020202020202ULL;        /* X2 */
        xMPUSettings->ullContext[ ulIndex++ ] = 0x0303030303030303ULL;        /* X3 */

        xMPUSettings->ullContext[ ulIndex++ ] = ( அடுக்கு_Type_t ) pvParameters; /* X0 */
        xMPUSettings->ullContext[ ulIndex++ ] = 0x0101010101010101ULL;        /* X1 */

        எனில்( xRunPrivileged == pdTRUE )
        {
            xMPUSettings->ullTaskFlags |= portTASK_IS_PRIVILEGED_FLAG;
        }
        இல்லையெனில்
        {
            xMPUSettings->ullTaskFlags &= ( ~portTASK_IS_PRIVILEGED_FLAG );
        }

        xMPUSettings->ullTaskUnprivilegedSP = ( ( uint64_t ) px_உச்சி_Of_அடுக்கு & portMPU_PRBAR_EL1_ADDRESS_MASK );

        திரும்பு &( xMPUSettings->ullContext[ 0 ] );
    }

#இல்லையெனில் /* #if ( configENABLE_MPU == 1 ) */

    /*
    * See header file for description.
    */
    அடுக்கு_Type_t * px_Port_Initialise_அடுக்கு( அடுக்கு_Type_t * px_உச்சி_Of_அடுக்கு,
                                         TaskFunction_t pxCode,
                                         வெறுமை * pvParameters )
    {
        /* Setup the initial stack of the task.  The stack is set exactly as
        * expected by the portRESTORE_CONTEXT() macro. */

        /* First all the general purpose registers. */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x0101010101010101ULL;        /* R1 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) pvParameters; /* R0 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x0303030303030303ULL;        /* R3 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x0202020202020202ULL;        /* R2 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x0505050505050505ULL;        /* R5 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x0404040404040404ULL;        /* R4 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x0707070707070707ULL;        /* R7 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x0606060606060606ULL;        /* R6 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x0909090909090909ULL;        /* R9 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x0808080808080808ULL;        /* R8 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x1111111111111111ULL;        /* R11 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x1010101010101010ULL;        /* R10 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x1313131313131313ULL;        /* R13 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x1212121212121212ULL;        /* R12 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x1515151515151515ULL;        /* R15 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x1414141414141414ULL;        /* R14 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x1717171717171717ULL;        /* R17 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x1616161616161616ULL;        /* R16 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x1919191919191919ULL;        /* R19 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x1818181818181818ULL;        /* R18 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x2121212121212121ULL;        /* R21 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x2020202020202020ULL;        /* R20 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x2323232323232323ULL;        /* R23 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x2222222222222222ULL;        /* R22 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x2525252525252525ULL;        /* R25 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x2424242424242424ULL;        /* R24 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x2727272727272727ULL;        /* R27 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x2626262626262626ULL;        /* R26 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x2929292929292929ULL;        /* R29 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x2828282828282828ULL;        /* R28 */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) 0x00;         /* XZR - has no effect, used so there are an even number of registers. */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) 0x00;         /* R30 - procedure call link register. */

        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = portINITIAL_PSTATE_EL0;

        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) pxCode; /* Exception return address. */

        #எனில் ( configUSE_TASK_FPU_SUPPORT == portTASK_NO_FPU_CONTEXT_BY_DEFAULT )
        {
            /* The task will start with a critical nesting count of 0 as interrupts are
            * enabled. */
            px_உச்சி_Of_அடுக்கு--;
            *px_உச்சி_Of_அடுக்கு = portNO_CRITICAL_NESTING;

            /* The task will start without a floating point context.  A task that
            * uses the floating point hardware must call vPortTaskUsesFPU() before
            * executing any floating point instructions. */
            px_உச்சி_Of_அடுக்கு--;
            *px_உச்சி_Of_அடுக்கு = portNO_FLOATING_POINT_CONTEXT;
        }
        #அல்லதெனில் ( configUSE_TASK_FPU_SUPPORT == portTASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
        {
            /* The task will start with a floating point context.  Leave enough
            * space for the registers - and ensure they are initialised to 0. */
            px_உச்சி_Of_அடுக்கு -= port_FPU_REGISTER_சொற்கள்;
            memset( px_உச்சி_Of_அடுக்கு, 0x00, port_FPU_REGISTER_சொற்கள் * அளவு( அடுக்கு_Type_t ) );

            /* The task will start with a critical nesting count of 0 as interrupts are
            * enabled. */
            px_உச்சி_Of_அடுக்கு--;
            *px_உச்சி_Of_அடுக்கு = portNO_CRITICAL_NESTING;

            px_உச்சி_Of_அடுக்கு--;
            *px_உச்சி_Of_அடுக்கு = pdTRUE;
            #எனில் ( config_எண்_OF_CORES == 1 )
            ullPortTaskHasFPUContext = pdTRUE;
            #இல்லையெனில்
            ullPortTaskHasFPUContext[ portGET_CORE_ID() ] = pdTRUE;
            #endif
        }
        #இல்லையெனில் /* if ( configUSE_TASK_FPU_SUPPORT == portTASK_NO_FPU_CONTEXT_BY_DEFAULT ) */
        {
            #error "Invalid configUSE_TASK_FPU_SUPPORT setting - configUSE_TASK_FPU_SUPPORT must be set to 1, 2, or left undefined."
        }
        #endif /* if ( configUSE_TASK_FPU_SUPPORT == portTASK_NO_FPU_CONTEXT_BY_DEFAULT ) */

        திரும்பு px_உச்சி_Of_அடுக்கு;

    }

#endif /* #if ( configENABLE_MPU == 1 ) */
/*-----------------------------------------------------------*/

#எனில் ( configENABLE_MPU == 1 )

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
    வெறுமை vPortStoreTaskMPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    மாறிலி கட்டமைப்பு xMEMORY_REGION * மாறிலி xRegions,
                                    அடுக்கு_Type_t * px_Bottom_Of_அடுக்கு,
                                    அடுக்கு_Type_t x_அடுக்கு_Depth )  /* PRIVILEGED_FUNCTION */
    {
        uint64_t ullRegionStartAddress, ullRegionEndAddress;
        uint8_t  ucIndex = 0, uc_Region_எண்;

        #எனில் defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            வெளி uint64_t * __privileged_sram_start__;
            வெளி uint64_t * __privileged_sram_end__;
        #இல்லையெனில்
            /* Declaration when these variable are exported from linker scripts. */
            வெளி uint64_t __privileged_sram_start__[];
            வெளி uint64_t __privileged_sram_end__[];
        #endif /* defined( __ARMCC_VERSION ) */

        /* Setup MAIR_EL1. */
        xMPUSettings->ullMairEl1 = ( ( portMPU_NORMAL_MEMORY_BUFFERABLE_CACHEABLE << portMPU_MAIR_EL1_ATTR0_POS ) & portMPU_MAIR_EL1_ATTR0_MASK );
        xMPUSettings->ullMairEl1 |= ( ( portMPU_DEVICE_MEMORY_nGnRE << portMPU_MAIR_EL1_ATTR1_POS ) & portMPU_MAIR_EL1_ATTR1_MASK );

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid. At all other
         * times the stack parameters will not be valid and it is assumed that
         * the stack region has already been configured. */
        எனில்( x_அடுக்கு_Depth > 0 )
        {
            ullRegionStartAddress = ( uint64_t ) px_Bottom_Of_அடுக்கு;
            ullRegionEndAddress = ( uint64_t ) px_Bottom_Of_அடுக்கு + ( x_அடுக்கு_Depth * ( config_அடுக்கு_DEPTH_TYPE ) அளவு( அடுக்கு_Type_t ) ) - 1;

            /* If the stack is within the privileged SRAM, do not protect it
             * using a separate MPU region. This is needed because this
             * region is already protected using an MPU region and ARMv8-R does
             * not allow overlapping MPU regions.
             */
            எனில்( ( ullRegionStartAddress >= ( uint64_t ) __privileged_sram_start__ ) &&
                ( ullRegionEndAddress <= ( uint64_t ) __privileged_sram_end__ ) )
            {
                xMPUSettings->xRegionsSettings[ port_அடுக்கு_REGION_INDEX ].ullPrbarEl1 = 0;
                xMPUSettings->xRegionsSettings[ port_அடுக்கு_REGION_INDEX ].ullPrlarEl1 = 0;
            }
            இல்லையெனில்
            {
                /* Define the region that allows access to the stack. */
                ullRegionStartAddress &= portMPU_PRBAR_EL1_ADDRESS_MASK;
                ullRegionEndAddress &= portMPU_PRLAR_EL1_ADDRESS_MASK;

                xMPUSettings->xRegionsSettings[ port_அடுக்கு_REGION_INDEX ].ullPrbarEl1 = ( ullRegionStartAddress ) |
                                                                                 ( portMPU_REGION_INNER_SHAREABLE ) |
                                                                                 ( portMPU_REGION_READ_WRITE ) |
                                                                                 ( portMPU_REGION_EXECUTE_NEVER );

                xMPUSettings->xRegionsSettings[ port_அடுக்கு_REGION_INDEX ].ullPrlarEl1 = ( ullRegionEndAddress ) |
                                                                                 ( portMPU_PRLAR_EL1_ATTR_INDEX0 ) |
                                                                                 ( portMPU_PRLAR_EL1_REGION_ENABLE );
            }
        }

        /* User supplied configurable regions. */
        க்கு( uc_Region_எண் = 1; uc_Region_எண் <= port_இலக்கம்_CONFIGURABLE_REGIONS; uc_Region_எண்++ )
        {
            /* If xRegions is NULL i.e. the task has not specified any MPU
             * region, the else part ensures that all the configurable MPU
             * regions are invalidated.
             * The minimum region size is 64 Bytes.
             */
            எனில்( xRegions != வெற்று )
            {
                /* Configure the region only if the base address is non-NULL.
                 * The user may choose to use only a subset of the available MPU regions.
                 * This check prevents undefined regions (i.e. regions with a NULL base
                 * address) from being configured and from triggering the size-check
                 * assertion below.
                 */
                எனில் ( xRegions[ ucIndex ].pvBaseAddress != வெற்று )
                {
                    configASSERT( xRegions[ ucIndex ].ulLengthInBytes >= 64UL );

                    uint64_t ull_Prbar_El1_Reg_மதிப்பு, ull_Prlar_El1_Reg_மதிப்பு;

                    /* Translate the generic region definition contained in xRegions
                     * into the ARMv8-R specific MPU settings that are then stored in
                     * xMPUSettings.
                     */
                    ullRegionStartAddress = ( ( uint64_t ) xRegions[ ucIndex ].pvBaseAddress ) & portMPU_PRBAR_EL1_ADDRESS_MASK;
                    ullRegionEndAddress = ( uint64_t ) xRegions[ ucIndex ].pvBaseAddress + xRegions[ ucIndex ].ulLengthInBytes - 1;
                    ullRegionEndAddress &= portMPU_PRLAR_EL1_ADDRESS_MASK;

                    /* Checks for overlaps with another user defined regions and stack region, which are already configured. */
                    க்கு( uint8_t uc_User_Region_எண் = 0; uc_User_Region_எண் < port_இலக்கம்_CONFIGURABLE_REGIONS; uc_User_Region_எண்++ )
                    {
                        /* Check for overlap. */
                        எனில்( ( portIS_ADDRESS_WITHIN_RANGE( ullRegionStartAddress,
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_எண் ].ullPrbarEl1 & portMPU_PRBAR_EL1_ADDRESS_MASK ),
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_எண் ].ullPrlarEl1 & portMPU_PRLAR_EL1_ADDRESS_MASK ) ) ||
                            ( portIS_ADDRESS_WITHIN_RANGE( ullRegionEndAddress,
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_எண் ].ullPrbarEl1 & portMPU_PRBAR_EL1_ADDRESS_MASK ),
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_எண் ].ullPrlarEl1 & portMPU_PRLAR_EL1_ADDRESS_MASK ) ) ) ) )
                        {
                            /* Overlap detected - assert. */
                            configASSERT( வெற்று );
                        }
                    }

                    /* Checks for overlaps with kernel programmed regions which are already programmed as part of vSetupMPU. */
                    க்கு (uint8_t ucProgrammedRegionIndex = 0; ucProgrammedRegionIndex < 4; ucProgrammedRegionIndex++)
                    {
                        __asm நிலையற்ற ( "msr PRSELR_EL1, %0" : : "r" ( ( uint64_t ) ucProgrammedRegionIndex ) );

                        __asm நிலையற்ற ( "mrs %0, PRBAR_EL1" : "=r" ( ull_Prbar_El1_Reg_மதிப்பு ) );
                        ull_Prbar_El1_Reg_மதிப்பு &= portMPU_PRBAR_EL1_ADDRESS_MASK;

                        __asm நிலையற்ற ( "mrs %0, PRLAR_EL1" : "=r" ( ull_Prlar_El1_Reg_மதிப்பு ) );
                        ull_Prlar_El1_Reg_மதிப்பு &= portMPU_PRLAR_EL1_ADDRESS_MASK;

                        /* Check for overlap. */
                        எனில்( ( portIS_ADDRESS_WITHIN_RANGE( ullRegionStartAddress,
                                                        ull_Prbar_El1_Reg_மதிப்பு,
                                                        ull_Prlar_El1_Reg_மதிப்பு ) ) ||
                            ( portIS_ADDRESS_WITHIN_RANGE( ullRegionEndAddress,
                                                        ull_Prbar_El1_Reg_மதிப்பு,
                                                        ull_Prlar_El1_Reg_மதிப்பு ) ) )
                        {
                            /* Overlap detected - assert. */
                            configASSERT( வெற்று );
                        }
                    }

                    /* Start address. */
                    xMPUSettings->xRegionsSettings[ uc_Region_எண் ].ullPrbarEl1 = ( ullRegionStartAddress );

                    /* RO/RW. */
                    எனில்( ( xRegions[ ucIndex ].ulParameters & tskMPU_REGION_READ_ONLY ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_எண் ].ullPrbarEl1 |= ( portMPU_REGION_READ_ONLY );
                    }
                    இல்லையெனில்
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_எண் ].ullPrbarEl1 |= ( portMPU_REGION_READ_WRITE );
                    }

                    /* XN. */
                    எனில்( ( xRegions[ ucIndex ].ulParameters & tskMPU_REGION_EXECUTE_NEVER ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_எண் ].ullPrbarEl1 |= ( portMPU_REGION_EXECUTE_NEVER );
                    }

                    /* SH. */
                    எனில்( ( xRegions[ ucIndex ].ulParameters & tskMPU_REGION_INNER_SHAREABLE ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_எண் ].ullPrbarEl1 |= ( portMPU_REGION_INNER_SHAREABLE );
                    }
                    இல்லையெனில் எனில்( ( xRegions[ ucIndex ].ulParameters & tskMPU_REGION_OUTER_SHAREABLE ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_எண் ].ullPrbarEl1 |= ( portMPU_REGION_OUTER_SHAREABLE );
                    }
                    இல்லையெனில்
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_எண் ].ullPrbarEl1 |= ( portMPU_REGION_NON_SHAREABLE );
                    }

                    /* End Address. */
                    xMPUSettings->xRegionsSettings[ uc_Region_எண் ].ullPrlarEl1 = ( ullRegionEndAddress ) |
                                                                                ( portMPU_PRLAR_EL1_REGION_ENABLE );

                    /* Normal memory/ Device memory. */
                    எனில்( ( xRegions[ ucIndex ].ulParameters & tskMPU_REGION_DEVICE_MEMORY ) != 0 )
                    {
                        /* Attr1 in MAIR_EL1 is configured as device memory. */
                        xMPUSettings->xRegionsSettings[ uc_Region_எண் ].ullPrlarEl1 |= portMPU_PRLAR_EL1_ATTR_INDEX1;
                    }
                    இல்லையெனில்
                    {
                        /* Attr0 in MAIR_EL1 is configured as normal memory. */
                        xMPUSettings->xRegionsSettings[ uc_Region_எண் ].ullPrlarEl1 |= portMPU_PRLAR_EL1_ATTR_INDEX0;
                    }
                }
            }
            இல்லையெனில்
            {
                /* Invalidate the region. */
                xMPUSettings->xRegionsSettings[ uc_Region_எண் ].ullPrbarEl1 = 0UL;
                xMPUSettings->xRegionsSettings[ uc_Region_எண் ].ullPrlarEl1 = 0UL;
            }

            ucIndex++;
        }

    }
    /*-----------------------------------------------------------*/

    வெறுமை vSetupMPU( வெறுமை ) /* PRIVILEGED_FUNCTION */
    {
        #எனில் defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts.
             */
            வெளி uint64_t * __privileged_functions_start__;
            வெளி uint64_t * __privileged_functions_end__;
            வெளி uint64_t * __syscalls_flash_start__;
            வெளி uint64_t * __syscalls_flash_end__;
            வெளி uint64_t * __unprivileged_flash_start__;
            வெளி uint64_t * __unprivileged_flash_end__;
            வெளி uint64_t * __privileged_sram_start__;
            வெளி uint64_t * __privileged_sram_end__;
        #இல்லையெனில் /* if defined( __ARMCC_VERSION ) */
            /* Declaration when these variable are exported from linker scripts. */
            வெளி uint64_t __privileged_functions_start__[];
            வெளி uint64_t __privileged_functions_end__[];
            வெளி uint64_t __syscalls_flash_start__[];
            வெளி uint64_t __syscalls_flash_end__[];
            வெளி uint64_t __unprivileged_flash_start__[];
            வெளி uint64_t __unprivileged_flash_end__[];
            வெளி uint64_t __privileged_sram_start__[];
            வெளி uint64_t __privileged_sram_end__[];
        #endif /* defined( __ARMCC_VERSION ) */

        /* The only permitted number of regions are 16 or 32. */
        configASSERT( ( configTOTAL_MPU_REGIONS == 16 ) || ( configTOTAL_MPU_REGIONS == 32 ) );

        /* MAIR_EL1 - Index 0. */
        uint64_t ull_Mair_El1_Reg_மதிப்பு = ( ( portMPU_NORMAL_MEMORY_BUFFERABLE_CACHEABLE << portMPU_MAIR_EL1_ATTR0_POS ) & portMPU_MAIR_EL1_ATTR0_MASK );
        /* MAIR_EL1 - Index 1. */
        ull_Mair_El1_Reg_மதிப்பு |= ( ( portMPU_DEVICE_MEMORY_nGnRE << portMPU_MAIR_EL1_ATTR1_POS ) & portMPU_MAIR_EL1_ATTR1_MASK );

        __asm நிலையற்ற ( "msr MAIR_EL1, %0" : : "r" ( ull_Mair_El1_Reg_மதிப்பு ) );

        /* Setup privileged flash as Read Only so that privileged tasks can
         * read it but not modify.
         */
        uint64_t ull_Prselr_El1_Reg_மதிப்பு = portPRIVILEGED_FLASH_REGION;
        __asm நிலையற்ற ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_மதிப்பு ) );

        uint64_t ull_Prbar_El1_Reg_மதிப்பு = ( ( ( uint64_t ) __privileged_functions_start__ ) & portMPU_PRBAR_EL1_ADDRESS_MASK ) |
                                       ( portMPU_REGION_NON_SHAREABLE ) |
                                       ( portMPU_REGION_PRIVILEGED_READ_ONLY );
        __asm நிலையற்ற ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_மதிப்பு ) );

        uint64_t ull_Prlar_El1_Reg_மதிப்பு = ( ( ( uint64_t ) __privileged_functions_end__ ) & portMPU_PRLAR_EL1_ADDRESS_MASK ) |
                                       ( portMPU_PRLAR_EL1_ATTR_INDEX0 ) |
                                       ( portMPU_PRLAR_EL1_REGION_ENABLE );
        __asm நிலையற்ற ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_மதிப்பு ) );

        /* Setup unprivileged flash as Read Only by both privileged and
         * unprivileged tasks. All tasks can read it but no-one can modify.
         */
        ull_Prselr_El1_Reg_மதிப்பு = portUNPRIVILEGED_FLASH_REGION;
        __asm நிலையற்ற ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_மதிப்பு ) );

        ull_Prbar_El1_Reg_மதிப்பு = ( ( ( uint64_t ) __unprivileged_flash_start__ ) & portMPU_PRBAR_EL1_ADDRESS_MASK ) |
                              ( portMPU_REGION_NON_SHAREABLE ) |
                              ( portMPU_REGION_READ_ONLY );
        __asm நிலையற்ற ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_மதிப்பு ) );

        ull_Prlar_El1_Reg_மதிப்பு = ( ( ( uint64_t ) __unprivileged_flash_end__ ) & portMPU_PRLAR_EL1_ADDRESS_MASK ) |
                              ( portMPU_PRLAR_EL1_ATTR_INDEX0 ) |
                              ( portMPU_PRLAR_EL1_REGION_ENABLE );
        __asm நிலையற்ற ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_மதிப்பு ) );

        /* Setup unprivileged syscalls flash as Read Only by both privileged
         * and unprivileged tasks. All tasks can read it but no-one can modify.
         */
        ull_Prselr_El1_Reg_மதிப்பு = portUNPRIVILEGED_SYSCALLS_REGION;
        __asm நிலையற்ற ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_மதிப்பு ) );

        ull_Prbar_El1_Reg_மதிப்பு = ( ( ( uint64_t ) __syscalls_flash_start__ ) & portMPU_PRBAR_EL1_ADDRESS_MASK ) |
                              ( portMPU_REGION_NON_SHAREABLE ) |
                              ( portMPU_REGION_READ_ONLY );
        __asm நிலையற்ற ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_மதிப்பு ) );

        ull_Prlar_El1_Reg_மதிப்பு = ( ( ( uint64_t ) __syscalls_flash_end__ ) & portMPU_PRLAR_EL1_ADDRESS_MASK ) |
                              ( portMPU_PRLAR_EL1_ATTR_INDEX0 ) |
                              ( portMPU_PRLAR_EL1_REGION_ENABLE );
        __asm நிலையற்ற ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_மதிப்பு ) );

        /* Setup RAM containing kernel data for privileged access only. */
        ull_Prselr_El1_Reg_மதிப்பு = portPRIVILEGED_RAM_REGION;
        __asm நிலையற்ற ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_மதிப்பு ) );

        ull_Prbar_El1_Reg_மதிப்பு = ( ( ( uint64_t ) __privileged_sram_start__ ) & portMPU_PRBAR_EL1_ADDRESS_MASK ) |
                              ( portMPU_REGION_INNER_SHAREABLE ) |
                              ( portMPU_REGION_PRIVILEGED_READ_WRITE ) |
                              ( portMPU_REGION_EXECUTE_NEVER );
        __asm நிலையற்ற ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_மதிப்பு ) );

        ull_Prlar_El1_Reg_மதிப்பு = ( ( ( uint64_t ) __privileged_sram_end__ ) & portMPU_PRLAR_EL1_ADDRESS_MASK ) |
                              ( portMPU_PRLAR_EL1_ATTR_INDEX0 ) |
                              ( portMPU_PRLAR_EL1_REGION_ENABLE );
        __asm நிலையற்ற ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_மதிப்பு ) );
    }
    /*-----------------------------------------------------------*/

    வெறுமை vEnableMPU( வெறுமை ) /* PRIVILEGED_FUNCTION */
    {
        uint64_t ull_Sctlr_El1_Reg_மதிப்பு;

        __asm நிலையற்ற ( "mrs %0, SCTLR_EL1" : "=r" ( ull_Sctlr_El1_Reg_மதிப்பு ) );
        /* Enable the MPU. Also enable privileged access to the
         * background region.
         */
        ull_Sctlr_El1_Reg_மதிப்பு |= ( portMPU_PRIV_BACKGROUND_ENABLE_BIT | portMPU_ENABLE_BIT );
        __asm நிலையற்ற ( "msr SCTLR_EL1, %0" : : "r" ( ull_Sctlr_El1_Reg_மதிப்பு ) );

        /* Ensure the write to SCTLR_EL1 is committed before
         * returning.
         */
        __asm நிலையற்ற ( "isb" );
    }
    /*-----------------------------------------------------------*/

    BaseType_t xPortIsTaskPrivileged( வெறுமை ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xTaskIsPrivileged = pdFALSE;

        #எனில் ( config_எண்_OF_CORES == 1 )
            வெளி TaskHandle_t pxCurrentTCB;
            xMPU_SETTINGS * pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );
        #இல்லையெனில்
            வெளி TaskHandle_t pxCurrentTCBs[ config_எண்_OF_CORES ];
            xMPU_SETTINGS * pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCBs[ portGET_CORE_ID_FROM_ISR() ] );
        #endif

        எனில்( ( pxMpuSettings->ullTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        திரும்பு xTaskIsPrivileged;
    }
    /*-----------------------------------------------------------*/

    நிலையான uint32_t prvGetRegionAccessPermissions( uint64_t ull_Prbar_El1_மதிப்பு ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ulAccessPermissions = 0;

        எனில்( ( ull_Prbar_El1_மதிப்பு & portMPU_PRBAR_EL1_ACCESS_PERMISSIONS_MASK ) == portMPU_REGION_READ_ONLY )
        {
            ulAccessPermissions = tskMPU_READ_PERMISSION;
        }

        எனில்( ( ull_Prbar_El1_மதிப்பு & portMPU_PRBAR_EL1_ACCESS_PERMISSIONS_MASK ) == portMPU_REGION_READ_WRITE )
        {
            ulAccessPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
        }

        திரும்பு ulAccessPermissions;
    }
    /*-----------------------------------------------------------*/

    BaseType_t xPortIsAuthorizedToAccessBuffer( மாறிலி வெறுமை * pvBuffer,
                                                size_t xBufferLength,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i;
        uint64_t ullBufferStartAddress, ullBufferEndAddress;
        BaseType_t xAccessGranted = pdFALSE;
        மாறிலி xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( வெற்று ); /* Calling task's MPU settings. */

        எனில்( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        இல்லையெனில் எனில்( ( xTaskMpuSettings->ullTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        இல்லையெனில்
        {
            எனில்( portADD_UINT64_WILL_OVERFLOW( ( ( uint64_t ) pvBuffer ), ( ( uint64_t ) xBufferLength - 1ULL ) ) == pdFALSE )
            {
                ullBufferStartAddress = ( uint64_t ) pvBuffer;
                ullBufferEndAddress = ( ( ( uint64_t ) pvBuffer ) + ( uint64_t ) xBufferLength - 1ULL );

                க்கு( i = 0; i < port_TOTAL_இலக்கம்_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    எனில்( ( xTaskMpuSettings->xRegionsSettings[ i ].ullPrlarEl1 & portMPU_PRLAR_EL1_REGION_ENABLE ) == portMPU_PRLAR_EL1_REGION_ENABLE )
                    {
                        எனில்( portIS_ADDRESS_WITHIN_RANGE( ullBufferStartAddress,
                                                         portEXTRACT_FIRST_ADDRESS_FROM_PRBAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrbarEl1 ),
                                                         portEXTRACT_LAST_ADDRESS_FROM_PRLAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrlarEl1 ) ) &&
                            portIS_ADDRESS_WITHIN_RANGE( ullBufferEndAddress,
                                                         portEXTRACT_FIRST_ADDRESS_FROM_PRBAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrbarEl1 ),
                                                         portEXTRACT_LAST_ADDRESS_FROM_PRLAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrlarEl1 ) ) &&
                            portIS_AUTHORIZED( ulAccessRequested,
                                               prvGetRegionAccessPermissions( xTaskMpuSettings->xRegionsSettings[ i ].ullPrbarEl1 ) ) )
                        {
                            xAccessGranted = pdTRUE;
                            நிறுத்து;
                        }
                    }
                }
            }
        }

        திரும்பு xAccessGranted;
    }
    /*-----------------------------------------------------------*/

    வெறுமை vSystemCallEnter( uint64_t * pull_Privileged_Only_Task_அடுக்கு,
                           uint8_t uc_System_Call_எண் ) /* PRIVILEGED_FUNCTION */
    {
        #எனில் ( config_எண்_OF_CORES == 1 )
            வெளி TaskHandle_t pxCurrentTCB;
        #இல்லையெனில்
            வெளி TaskHandle_t pxCurrentTCBs[ config_எண்_OF_CORES ];
        #endif
        வெளி UBaseType_t uxSystemCallImplementations[ இலக்கம்_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint64_t ullSystemCallLocation;  /* Address where SVC was raised. */
        __asm நிலையற்ற ( "MRS %0, ELR_EL1" : "=r" ( ullSystemCallLocation ) );

        #எனில் defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts.
             */
            வெளி uint64_t * __syscalls_flash_start__;
            வெளி uint64_t * __syscalls_flash_end__;
        #இல்லையெனில்
            /* Declaration when these variable are exported from linker scripts. */
            வெளி uint64_t __syscalls_flash_start__[];
            வெளி uint64_t __syscalls_flash_end__[];
        #endif /* #if defined( __ARMCC_VERSION ) */

        #எனில் ( config_எண்_OF_CORES == 1 )
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );
        #இல்லையெனில்
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCBs[ portGET_CORE_ID_FROM_ISR() ] );
        #endif

        /* Checks:
         * 1. SVC is raised from the system call section (i.e. application is
         *    not raising SVC directly).
         * 2. We do not need to check that ucSystemCallNumber is within range
         *    because the assembly SVC handler checks that before calling
         *    this function.
         */
        எனில்( ( ullSystemCallLocation >= ( uint64_t ) __syscalls_flash_start__ ) &&
            ( ullSystemCallLocation <= ( uint64_t ) __syscalls_flash_end__ ) &&
            ( uxSystemCallImplementations[ uc_System_Call_எண் ] != 0 ) )
        {
            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call.
             */
            pxMpuSettings->xSystemCallInfo.ullLinkRegisterAtSystemCallEntry = pull_Privileged_Only_Task_அடுக்கு[ portOFFSET_TO_LR ];

            /* Capture user-mode SP at system call entry. */
            uint64_t ullUserSpAtEntry;
            __asm நிலையற்ற ( "MRS %0, SP_EL0" : "=r" ( ullUserSpAtEntry ) );
            pxMpuSettings->xSystemCallInfo.ullUserSPAtSystemCallEntry = ullUserSpAtEntry;

            /* Setup the MPU_<API> inputs, the system call stack, and SPSR. */
            __asm நிலையற்ற (
                "MOV X0, %0         \n"
                "MOV X1, %1         \n"
                "MOV X2, %2         \n"
                "MOV X3, %3         \n"
                "MSR ELR_EL1, %4    \n"
                "MSR SP_EL0, %5     \n"
                "MSR SPSR_EL1, %6   \n"
                :
                : "r" ( pull_Privileged_Only_Task_அடுக்கு[ portOFFSET_TO_X0 ] ),
                  "r" ( pull_Privileged_Only_Task_அடுக்கு[ portOFFSET_TO_X1 ] ),
                  "r" ( pull_Privileged_Only_Task_அடுக்கு[ portOFFSET_TO_X2 ] ),
                  "r" ( pull_Privileged_Only_Task_அடுக்கு[ portOFFSET_TO_X3 ] ),
                  "r" ( ( uint64_t ) uxSystemCallImplementations[ uc_System_Call_எண் ] ),
                  "r" ( &( pxMpuSettings->ullContext[ MAX_CONTEXT_SIZE + config_SYSTEM_CALL_அடுக்கு_SIZE ] ) ),
                  "r" ( portINITIAL_PSTATE_EL1 )
                : "memory", "x0", "x1", "x2", "x3"
            );
        }
    }
    /*-----------------------------------------------------------*/

    வெறுமை vRequestSystemCallExit( வெறுமை ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm நிலையற்ற ( "svc %0 \n" ::"i" ( portSVC_SYSTEM_CALL_EXIT ) : "memory" );
    }
    /*-----------------------------------------------------------*/

    வெறுமை vSystemCallExit( uint64_t ull_System_Call_Return_மதிப்பு ) /* PRIVILEGED_FUNCTION */
    {
        #எனில் ( config_எண்_OF_CORES == 1 )
            வெளி TaskHandle_t pxCurrentTCB;
        #இல்லையெனில்
            வெளி TaskHandle_t pxCurrentTCBs[ config_எண்_OF_CORES ];
        #endif
        xMPU_SETTINGS * pxMpuSettings;
        uint64_t ullSystemCallLocation; /* Address where SVC was raised. */
        __asm நிலையற்ற ( "MRS %0, ELR_EL1" : "=r" ( ullSystemCallLocation ) );

        #எனில் defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            வெளி uint64_t * __privileged_functions_start__;
            வெளி uint64_t * __privileged_functions_end__;
        #இல்லையெனில்
            /* Declaration when these variable are exported from linker scripts. */
            வெளி uint64_t __privileged_functions_start__[];
            வெளி uint64_t __privileged_functions_end__[];
        #endif /* #if defined( __ARMCC_VERSION ) */

        #எனில் ( config_எண்_OF_CORES == 1 )
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );
        #இல்லையெனில்
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCBs[ portGET_CORE_ID_FROM_ISR() ] );
        #endif

        /* Check:
         * SVC is raised from the privileged code (i.e. application is not
         * raising SVC directly). This SVC is only raised from
         * vRequestSystemCallExit which is in the privileged code section.
         */
        எனில்( ( ullSystemCallLocation >= ( uint64_t ) __privileged_functions_start__ ) &&
            ( ullSystemCallLocation <= ( uint64_t ) __privileged_functions_end__ ) )
        {
            __asm நிலையற்ற (
                "MSR ELR_EL1, %0    \n" /* Return to the MPU_<API> caller. */
                "MSR SP_EL0, %1     \n" /* Restore user SP saved at syscall entry. */
                "MSR SPSR_EL1, %3   \n" /* Ensure return to EL0. */
                "MOV X0, %2         \n" /* Move the system call return value to X0. */
                :
                : "r" ( pxMpuSettings->xSystemCallInfo.ullLinkRegisterAtSystemCallEntry ),
                  "r" ( pxMpuSettings->xSystemCallInfo.ullUserSPAtSystemCallEntry ),
                  "r" ( ull_System_Call_Return_மதிப்பு ),
                  "r" ( ( uint64_t ) portINITIAL_PSTATE_EL0 )
                : "memory"
            );
        }
    }
    /*-----------------------------------------------------------*/

    #எனில் ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        வெறுமை vPortGrantAccessToKernelObject( TaskHandle_t xInternalTaskHandle,
                                             int32_t lInternalIndexOfKernelObject ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulAccessControlListEntryIndex, ulAccessControlListEntryBit;
            xMPU_SETTINGS * xTaskMpuSettings;

            /* Calculate the Access Control List entry index and bit position
             * within that entry. */
            ulAccessControlListEntryIndex = ( ( uint32_t ) lInternalIndexOfKernelObject / portACL_ENTRY_SIZE_BITS );
            ulAccessControlListEntryBit = ( ( uint32_t ) lInternalIndexOfKernelObject % portACL_ENTRY_SIZE_BITS );

            xTaskMpuSettings = xTaskGetMPUSettings( xInternalTaskHandle );

            /* Set the bit corresponding to the kernel object to grant access. */
            xTaskMpuSettings->ulAccessControlList[ ulAccessControlListEntryIndex ] |= ( 1U << ulAccessControlListEntryBit );
        }
        /*-----------------------------------------------------------*/

        வெறுமை vPortRevokeAccessToKernelObject( TaskHandle_t xInternalTaskHandle,
                                              int32_t lInternalIndexOfKernelObject ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulAccessControlListEntryIndex, ulAccessControlListEntryBit;
            xMPU_SETTINGS * xTaskMpuSettings;

            /* Calculate the Access Control List entry index and bit position
             * within that entry. */
            ulAccessControlListEntryIndex = ( ( uint32_t ) lInternalIndexOfKernelObject / portACL_ENTRY_SIZE_BITS );
            ulAccessControlListEntryBit = ( ( uint32_t ) lInternalIndexOfKernelObject % portACL_ENTRY_SIZE_BITS );

            xTaskMpuSettings = xTaskGetMPUSettings( xInternalTaskHandle );

            /* Clear the bit corresponding to the kernel object to revoke access. */
            xTaskMpuSettings->ulAccessControlList[ ulAccessControlListEntryIndex ] &= ~( 1U << ulAccessControlListEntryBit );
        }
        /*-----------------------------------------------------------*/

        BaseType_t xPortIsAuthorizedToAccessKernelObject( int32_t lInternalIndexOfKernelObject ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulAccessControlListEntryIndex, ulAccessControlListEntryBit;
            BaseType_t xAccessGranted = pdFALSE;
            மாறிலி xMPU_SETTINGS * xTaskMpuSettings;

            எனில்( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            இல்லையெனில்
            {
                xTaskMpuSettings = xTaskGetMPUSettings( வெற்று ); /* Calling task's MPU settings. */

                ulAccessControlListEntryIndex = ( ( uint32_t ) lInternalIndexOfKernelObject / portACL_ENTRY_SIZE_BITS );
                ulAccessControlListEntryBit = ( ( uint32_t ) lInternalIndexOfKernelObject % portACL_ENTRY_SIZE_BITS );

                எனில்( ( xTaskMpuSettings->ullTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                இல்லையெனில்
                {
                    எனில்( ( xTaskMpuSettings->ulAccessControlList[ ulAccessControlListEntryIndex ] & ( 1U << ulAccessControlListEntryBit ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            திரும்பு xAccessGranted;
        }
        /*-----------------------------------------------------------*/
    #இல்லையெனில் /* configENABLE_ACCESS_CONTROL_LIST == 1 */

        BaseType_t xPortIsAuthorizedToAccessKernelObject( int32_t lInternalIndexOfKernelObject ) /* PRIVILEGED_FUNCTION */
        {
            ( வெறுமை ) lInternalIndexOfKernelObject;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            திரும்பு pdTRUE;
        }
        /*-----------------------------------------------------------*/

    #endif /* configENABLE_ACCESS_CONTROL_LIST == 1 */

#endif /* #if ( configENABLE_MPU == 1 ) */

BaseType_t xPortStartScheduler( வெறுமை )
{
    uint64_t ullAPSR;

    #எனில் ( configASSERT_DEFINED == 1 )
    {
        நிலையற்ற uint8_t ucOriginalPriority;
        நிலையற்ற uint8_t * மாறிலி pucFirstUserPriorityRegister = ( நிலையற்ற uint8_t * மாறிலி ) ( configINTERRUPT_CONTROLLER_BASE_ADDRESS + portINTERRUPT_PRIORITY_REGISTER_OFFSET );
        நிலையற்ற uint8_t uc_Max_Priority_மதிப்பு;

        /* Determine how many priority bits are implemented in the GIC.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        ucOriginalPriority = *pucFirstUserPriorityRegister;

        /* Determine the number of priority bits available.  First write to
         * all possible bits. */
        *pucFirstUserPriorityRegister = port_MAX_8_BIT_மதிப்பு;

        /* Read the value back to see how many bits stuck. */
        uc_Max_Priority_மதிப்பு = *pucFirstUserPriorityRegister;

        /* Shift to the least significant bits. */
        போது( ( uc_Max_Priority_மதிப்பு & portBIT_0_SET ) != portBIT_0_SET )
        {
            uc_Max_Priority_மதிப்பு >>= ( uint8_t ) 0x01;
        }

        /* Sanity check configUNIQUE_INTERRUPT_PRIORITIES matches the read
         * value. */
        configASSERT( uc_Max_Priority_மதிப்பு >= portLOWEST_INTERRUPT_PRIORITY );


        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *pucFirstUserPriorityRegister = ucOriginalPriority;
    }
    #endif /* configASSERT_DEFINED */

    __asm நிலையற்ற ( "MRS %0, CurrentEL" : "=r" ( ullAPSR ) );
    ullAPSR &= portAPSR_MODE_BITS_MASK;

    configASSERT( ullAPSR == portEL1 );

    #எனில் ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        vSetupMPU();
    }
    #endif /* #if ( configENABLE_MPU == 1 ) */

    /* Interrupts are turned off in the CPU itself to ensure a tick does
     * not execute while the scheduler is being started.  Interrupts are
     * automatically turned back on in the CPU when the first task starts
     * executing. */
    __asm நிலையற்ற ( "MSR DAIFSET, #2\n"
                     "DSB SY\n"
                     "ISB SY\n" ::: "memory" );
    #எனில் ( config_எண்_OF_CORES > 1 )
        /* Start the timer that generates the tick ISR. */
        configSETUP_TICK_INTERRUPT();
        ucPrimaryCoreInitDoneFlag = 1;
        __asm நிலையற்ற ( "SEV                       \n"
                         "DSB SY                    \n"
                         "ISB SY                    \n"
                         ::: "memory" );
        /* Hold the primary core here until all the secondary cores are ready, this would be achieved only when
         * all elements of ucSecondaryCoresReadyFlags are set.
         */
        போது( 1 )
        {
            BaseType_t xAllCoresReady = pdTRUE;
            க்கு( uint8_t ucCoreID = 0; ucCoreID < ( config_எண்_OF_CORES - 1 ); ucCoreID++ )
            {
                எனில்( ucSecondaryCoresReadyFlags[ ucCoreID ] != pdTRUE )
                {
                    xAllCoresReady = pdFALSE;
                    நிறுத்து;
                }
            }

            எனில் ( xAllCoresReady == pdTRUE )
            {
                நிறுத்து;
            }
        }
    #இல்லையெனில் /* if ( configNUMBER_OF_CORES > 1 ) */
        /* Start the timer that generates the tick ISR. */
        configSETUP_TICK_INTERRUPT();
    #endif /* if ( configNUMBER_OF_CORES > 1 ) */

    #எனில் ( configENABLE_MPU == 1 )
        xSchedulerRunning = pdTRUE;

        /* Enable the Memory Protection Unit (MPU)
         * MPU is only enabled after the primary and secondary handshakes
         * are done as to prevent inconsistent MPU regions attributes across
         * different cores resulting in unupdated values of the handshake
         * flags. 
         */
        vEnableMPU();
    #endif /* #if ( configENABLE_MPU == 1 ) */

    /* Start the first task executing. */
    vPortRestoreTaskContext();

    திரும்பு 0;
}

/*-----------------------------------------------------------*/

வெறுமை vPortEndScheduler( வெறுமை ) /* PRIVILEGED_FUNCTION */
{
    /* Stub implementation for ports where there is nothing to return to
     * Artificially force an assert. */
    configASSERT( வெற்று );
}

/*-----------------------------------------------------------*/

#எனில்  ( config_எண்_OF_CORES == 1 )
    PRIVILEGED_FUNCTION வெறுமை vPortEnterCritical( வெறுமை )
    {
        /* Mask interrupts up to the max syscall interrupt priority. */
        uxPortSetInterruptMask();

        /* Now interrupts are disabled ullCriticalNesting can be accessed
         * directly.  Increment ullCriticalNesting to keep a count of how many times
         * portENTER_CRITICAL() has been called. */
        ullCriticalNesting++;

        /* This is not the interrupt safe version of the enter critical function so
         * assert() if it is being called from an interrupt context.  Only API
         * functions that end in "FromISR" can be used in an interrupt.  Only assert if
         * the critical nesting count is 1 to protect against recursive calls if the
         * assert function also uses a critical section. */
        எனில்( ullCriticalNesting == 1ULL )
        {
            configASSERT( ullPortInterruptNesting == 0 );
        }
    }

/*-----------------------------------------------------------*/

    PRIVILEGED_FUNCTION வெறுமை vPortExitCritical( வெறுமை )
    {
        எனில்( ullCriticalNesting > portNO_CRITICAL_NESTING )
        {
            /* Decrement the nesting count as the critical section is being
             * exited. */
            ullCriticalNesting--;

            /* If the nesting level has reached zero then all interrupt
             * priorities must be re-enabled. */
            எனில்( ullCriticalNesting == portNO_CRITICAL_NESTING )
            {
                /* Critical nesting has reached zero so all interrupt priorities
                 * should be unmasked. */
                portCLEAR_INTERRUPT_PRIORITIES_MASK();
            }
        }
    }
#endif /* if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/

வெறுமை FreeRTOS_Tick_Handler( வெறுமை )
{
    /* Must be the lowest possible priority. */
    uint64_t ullRunningInterruptPriority;
    __asm நிலையற்ற ( "MRS %0, ICC_RPR_EL1" : "=r" ( ullRunningInterruptPriority ) );

    configASSERT( ullRunningInterruptPriority == ( portLOWEST_USABLE_INTERRUPT_PRIORITY << portPRIORITY_SHIFT ) );

    /* Interrupts should not be enabled before this point. */
    #எனில் ( configASSERT_DEFINED == 1 )
    {
        uint64_t ullMaskBits;

        __asm நிலையற்ற ( "MRS %0, DAIF" : "=r" ( ullMaskBits )::"memory" );
        configASSERT( ( ullMaskBits & portDAIF_I ) != 0 );
    }
    #endif /* configASSERT_DEFINED */

    /* Set interrupt mask before altering scheduler structures. The tick
     * interrupt runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value.  It is
     * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
     * updated.
     */
    UBaseType_t uxInterruptStatus = portSET_INTERRUPT_MASK_FROM_ISR();

    #எனில் ( config_எண்_OF_CORES > 1 )
        UBaseType_t x = portENTER_CRITICAL_FROM_ISR();
    #endif /* if ( configNUMBER_OF_CORES > 1 ) */

    /* Increment the RTOS tick. */
    எனில்( xTaskIncrementTick() != pdFALSE )
    {
        #எனில் ( config_எண்_OF_CORES == 1 )
            ullPortYieldRequired = pdTRUE;
        #இல்லையெனில்
            ullPortYieldRequired[ portGET_CORE_ID_FROM_ISR() ] = pdTRUE;
        #endif
    }
    #எனில் ( config_எண்_OF_CORES > 1 )
        portEXIT_CRITICAL_FROM_ISR(x);
    #endif /* if ( configNUMBER_OF_CORES > 1 ) */

    /* Ensure all interrupt priorities are active again. */
    portCLEAR_INTERRUPT_MASK_FROM_ISR( uxInterruptStatus );

    /* Ok to enable interrupts after the interrupt source has been cleared. */
    configCLEAR_TICK_INTERRUPT();
}

/*-----------------------------------------------------------*/

#எனில் ( configUSE_TASK_FPU_SUPPORT == portTASK_NO_FPU_CONTEXT_BY_DEFAULT )

    வெறுமை vPortTaskUsesFPU( வெறுமை )
    {
        /* A task is registering the fact that it needs an FPU context.  Set the
         * FPU flag (which is saved as part of the task context). */
        #எனில்  ( config_எண்_OF_CORES == 1 )
            ullPortTaskHasFPUContext = pdTRUE;
        #இல்லையெனில்
            ullPortTaskHasFPUContext[ portGET_CORE_ID() ] = pdTRUE;
        #endif

        /* Consider initialising the FPSR here - but probably not necessary in
         * AArch64. */
    }

#endif /* configUSE_TASK_FPU_SUPPORT */

/*-----------------------------------------------------------*/

வெறுமை vPortClearInterruptMask( UBaseType_t ux_New_Mask_மதிப்பு )
{
    எனில்( ux_New_Mask_மதிப்பு == port_UNMASK_மதிப்பு )
    {
        /* Unmask all interrupt priorities. */
        portCLEAR_INTERRUPT_PRIORITIES_MASK();
    }
    இல்லையெனில்
    {
        __asm நிலையற்ற (
            "SVC %0 \n"
            :
            : "i" ( portSVC_UNMASK_INTERRUPTS )
            : "memory"
        );
    }
}

வெறுமை vPortClearInterruptMaskFromISR( UBaseType_t ux_New_Mask_மதிப்பு )
{
    __asm நிலையற்ற (
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
        : "r" ( ux_New_Mask_மதிப்பு )
    );
}
/*-----------------------------------------------------------*/

UBaseType_t uxPortSetInterruptMask( வெறுமை )
{
    UBaseType_t ullPMRValue;

    /* Use SVC so this can be called safely from EL0 tasks. */
    __asm நிலையற்ற (
        "svc %1        \n"
        "mov %0, x0    \n"
        : "=r" ( ullPMRValue )
        : "i" ( portSVC_MASK_ALL_INTERRUPTS )
        : "x0", "memory"
    );

    திரும்பு ullPMRValue;
}

/* EL1/ISR variant to avoid SVC from interrupt context. */
UBaseType_t uxPortSetInterruptMaskFromISR( வெறுமை )
{
    UBaseType_t ullPMRValue;

    __asm நிலையற்ற ( "MRS %0, ICC_PMR_EL1" : "=r" ( ullPMRValue ) );

    எனில்( ullPMRValue != ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT ) )
    {
        __asm நிலையற்ற ( "MSR DAIFSET, #2        \n"
                         "DSB SY                 \n"
                         "ISB SY                 \n"
                         "MSR ICC_PMR_EL1, %0    \n"
                         "DSB SY                 \n"
                         "ISB SY                 \n"
                         "MSR DAIFCLR, #2        \n"
                         "DSB SY                 \n"
                         "ISB SY                 \n"
                         ::"r" ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT ) : "memory" );
    }

    திரும்பு ullPMRValue;
}

/*-----------------------------------------------------------*/

#எனில் ( configASSERT_DEFINED == 1 )

    வெறுமை vPortValidateInterruptPriority( வெறுமை )
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
        uint64_t ullRunningInterruptPriority;
        __asm நிலையற்ற ( "MRS %0, ICC_RPR_EL1" : "=r" ( ullRunningInterruptPriority ) );
        configASSERT( ullRunningInterruptPriority >= ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT ) );
    }

#endif /* configASSERT_DEFINED */

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
 __attribute__( ( weak ) ) வெறுமை vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR )
{
    ( வெறுமை ) ulICCIAR;
    configASSERT( ( நிலையற்ற வெறுமை * ) வெற்று );
}

/*-----------------------------------------------------------*/

#எனில் ( config_எண்_OF_CORES > 1 )

    /* Which core owns the lock? Keep in privileged, shareable RAM. */
    PRIVILEGED_DATA நிலையற்ற uint64_t ullOwnedByCore[ port_MAX_CORE_மொத்தம் ];
    /* Lock count a core owns. */
    PRIVILEGED_DATA நிலையற்ற uint64_t ull_Recursion_மொத்தம்_By_Lock[ e_Lock_மொத்தம் ];
    /* Index 0 is used for ISR lock and Index 1 is used for task lock. */
    PRIVILEGED_DATA uint32_t ulGateWord[ e_Lock_மொத்தம் ];

    வெறுமை vInterruptCore( uint32_t ulInterruptID, uint8_t ucCoreID )
    {
        uint64_t ulRegVal = 0;
        uint32_t ulCoreMask = ( 1UL << ucCoreID );
        ulRegVal |= ( (ulCoreMask & 0xFFFF) | ( ( ulInterruptID & 0xF ) << 24U ) );
        __asm நிலையற்ற (
            "str  x0, [ sp, #-0x10 ]!       \n"
            "mov  x0, %0                    \n"
            "svc  %1                        \n"
            "ldr  x0, [ sp ], # 0x10        \n"
            :
            : "r" ( ulRegVal ), "i" ( portSVC_INTERRUPT_CORE )
            : "memory", "w1"
        );
    }

/*-----------------------------------------------------------*/

    நிலையான உள்வரி வெறுமை prvSpinUnlock( uint32_t * ulLock )
    {
        /* Conservative unlock: preserve original barriers for broad HW/FVP. */
        __asm நிலையற்ற (
            "dmb sy         \n"
            "mov w1, #0     \n"
            "str w1, [%x0]  \n"
            "sev            \n"
            "dsb sy         \n"
            "isb sy         \n"
            :
            : "r" ( ulLock )
            : "memory", "w1"
        );
    }

/*-----------------------------------------------------------*/

    நிலையான உள்வரி uint32_t prvSpinTrylock( uint32_t * ulLock )
    {
        /*
         * Conservative LDXR/STXR trylock:
         * - Return 1 immediately if busy, clearing exclusive state (CLREX).
         * - Retry STXR only on spurious failure when observed free.
         * - DMB on success to preserve expected acquire semantics.
         */
        பதிவு uint32_t ulRet;
        __asm நிலையற்ற (
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
            : "r" ( ulLock )
            : "memory", "w1", "w2", "w3"
        );

        திரும்பு ulRet;
    }

/*-----------------------------------------------------------*/

    /* Read 64b value shared between cores. */
    நிலையான உள்வரி uint64_t prvGet64( நிலையற்ற uint64_t * x )
    {
        __asm( "dsb sy" );
        திரும்பு *x;
    }

/*-----------------------------------------------------------*/

    /* Write 64b value shared between cores. */
    நிலையான உள்வரி வெறுமை prvSet64( நிலையற்ற uint64_t * x,
                                 uint64_t மதிப்பு )
    {
        *x = மதிப்பு;
        __asm( "dsb sy" );
    }

/*-----------------------------------------------------------*/

    வெறுமை vPortRecursiveLock( uint8_t ucCoreID,
                             ePortRTOSLock e_Lock_இலக்கம்,
                             BaseType_t uxAcquire )
    {
        /* Validate the core ID and lock number. */
        configASSERT( ucCoreID < port_MAX_CORE_மொத்தம் );
        configASSERT( e_Lock_இலக்கம் < e_Lock_மொத்தம் );

        uint32_t ulLockBit = 1u << e_Lock_இலக்கம்;

        /* Lock acquire */
        எனில்( uxAcquire )
        {
            /* Check if spinlock is available.
             * If spinlock is not available check if the core owns the lock.
             * If the core owns the lock wait increment the lock count by the core.
             * If core does not own the lock wait for the spinlock.
             */
            எனில்( prvSpinTrylock( &ulGateWord[ e_Lock_இலக்கம் ] ) != 0 )
            {
                /* Check if the core owns the spinlock. */
                எனில்( prvGet64( &ullOwnedByCore[ ucCoreID ] ) & ulLockBit )
                {
                    configASSERT( prvGet64( &ull_Recursion_மொத்தம்_By_Lock[ e_Lock_இலக்கம் ] ) != 255u );
                    prvSet64( &ull_Recursion_மொத்தம்_By_Lock[ e_Lock_இலக்கம் ], ( prvGet64( &ull_Recursion_மொத்தம்_By_Lock[ e_Lock_இலக்கம் ] ) + 1 ) );
                    திரும்பு;
                }

                /* Preload the gate word into the cache. */
                uint32_t dummy = ulGateWord[ e_Lock_இலக்கம் ];
                dummy++;

                போது( prvSpinTrylock( &ulGateWord[ e_Lock_இலக்கம் ] ) != 0 )
                {
                   /* Follow Arm's recommended way of sleeping
                    * sevl is used to prime the wait loop.
                    * The first wfe wakes immediately because sevl has set the flag.
                    * Check the lock, if it's not available, issue a second wfe to sleep.
                    * This guarantees the core actually goes to sleep.
                    */
                    __asm நிலையற்ற (
                        "sevl            \n"
                        "1: wfe          \n"
                        "ldr w2, [%x0]   \n"
                        "cbnz w2, 1b     \n"
                        :
                        : "r" ( &ulGateWord[ e_Lock_இலக்கம் ] )
                        : "memory", "w2"
                    );
                }
            }

            /* Add barrier to ensure lock is taken before we proceed. */
            __asm__ __volatile__ ( "dmb sy" ::: "memory" );

            /* Assert the lock count is 0 when the spinlock is free and is acquired. */
            configASSERT( prvGet64( &ull_Recursion_மொத்தம்_By_Lock[ e_Lock_இலக்கம் ] ) == 0 );

            /* Set lock count as 1. */
            prvSet64( &ull_Recursion_மொத்தம்_By_Lock[ e_Lock_இலக்கம் ], 1 );
            /* Set ullOwnedByCore. */
            prvSet64( &ullOwnedByCore[ ucCoreID ], ( prvGet64( &ullOwnedByCore[ ucCoreID ] ) | ulLockBit ) );
        }
        /* Lock release. */
        இல்லையெனில்
        {
            /* Assert the lock is not free already. */
            configASSERT( ( prvGet64( &ullOwnedByCore[ ucCoreID ] ) & ulLockBit ) != 0 );
            configASSERT( prvGet64( &ull_Recursion_மொத்தம்_By_Lock[ e_Lock_இலக்கம் ] ) != 0 );

            /* Reduce ullRecursionCountByLock by 1. */
            prvSet64( &ull_Recursion_மொத்தம்_By_Lock[ e_Lock_இலக்கம் ], ( prvGet64( &ull_Recursion_மொத்தம்_By_Lock[ e_Lock_இலக்கம் ] ) - 1 ) );

            எனில்( !prvGet64( &ull_Recursion_மொத்தம்_By_Lock[ e_Lock_இலக்கம் ] ) )
            {
                prvSet64( &ullOwnedByCore[ ucCoreID ], ( prvGet64( &ullOwnedByCore[ ucCoreID ] ) & ~ulLockBit ) );
                prvSpinUnlock( &ulGateWord[ e_Lock_இலக்கம் ] );
                /* Add barrier to ensure lock status is reflected before we proceed. */
                __asm__ __volatile__ ( "dmb sy" ::: "memory" );
            }
        }
    }

/*-----------------------------------------------------------*/

    uint8_t ucPortGetCoreID( வெறுமை )
    {
        /* Use SVC to obtain the core ID in a way that is safe when called
         * from EL0 tasks. ISRs and EL1 code should use
         * ucPortGetCoreIDFromIsr()/portGET_CORE_ID_FROM_ISR().
         */
        uint8_t ucCoreID;
        __asm நிலையற்ற (
            "svc %1             \n"
            "mov %w0, w0        \n"
            : "=r" ( ucCoreID )
            : "i" ( portSVC_GET_CORE_ID )
            : "x0", "memory"
        );
        திரும்பு ucCoreID;
    }

/*-----------------------------------------------------------*/

    uint8_t ucPortGetCoreIDFromIsr ( வெறுமை ) /* PRIVILEGED_FUNCTION */
    {
        uint64_t ullMpidrEl1;
        __asm நிலையற்ற ( "MRS %0, MPIDR_EL1" : "=r" ( ullMpidrEl1 ) );

        திரும்பு ( uint8_t ) ( ullMpidrEl1 & 0xff );
    }

/*------------------------------------------------------------*/
    வெறுமை FreeRTOS_SGI_Handler( வெறுமை )
    {
        /* Must be the lowest possible priority. */
        uint64_t ullRunningInterruptPriority;
        __asm நிலையற்ற ( "MRS %0, ICC_RPR_EL1" : "=r" ( ullRunningInterruptPriority ) );

        configASSERT( ullRunningInterruptPriority == ( portLOWEST_USABLE_INTERRUPT_PRIORITY << portPRIORITY_SHIFT ) );
        /* Interrupts should not be enabled before this point. */
        #எனில் ( configASSERT_DEFINED == 1 )
        {
            uint64_t ullMaskBits;

            __asm நிலையற்ற ( "mrs %0, DAIF" : "=r" ( ullMaskBits )::"memory" );
            configASSERT( ( ullMaskBits & portDAIF_I ) != 0 );
        }
        #endif /* configASSERT_DEFINED */

        /* Set interrupt mask before altering scheduler structures. The SGI
         * interrupt runs at the lowest priority, so interrupts cannot already be masked,
         * so there is no need to save and restore the current mask value.  It is
         * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
         * updated.
         */
        UBaseType_t uxInterruptStatus = portSET_INTERRUPT_MASK_FROM_ISR();

        UBaseType_t uxSavedInterruptStatus = portENTER_CRITICAL_FROM_ISR();
        #எனில் ( config_எண்_OF_CORES == 1 )
            ullPortYieldRequired = pdTRUE;
        #இல்லையெனில்
            ullPortYieldRequired[ portGET_CORE_ID_FROM_ISR() ] = pdTRUE;
        #endif
        portEXIT_CRITICAL_FROM_ISR( uxSavedInterruptStatus );
        portCLEAR_INTERRUPT_MASK_FROM_ISR( uxInterruptStatus );
    }

/*-----------------------------------------------------------*/

#endif /* if( configNUMBER_OF_CORES > 1 ) */
