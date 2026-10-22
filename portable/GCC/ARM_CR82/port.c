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
#ضمن <stdlib.h>
#ضمن <string.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers. That should only be done when
 * task.h is included from an application file. */
#تعریف_کړه MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* MPU includes. */
#ضمن "mpu_wrappers.h"
#ضمن "mpu_syscall_numbers.h"

#تعریف_لغوه MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#که_نه_تعریف_شوی config_مداخله_CONTROLLER_بنسټ_پته
    #تېروتنه config_مداخله_CONTROLLER_بنسټ_پته must be defined.  Refer منزل Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#د_که_پای

#که_نه_تعریف_شوی config_مداخله_CONTROLLER_CPU_INTERFACE_دننه_واټن
    #تېروتنه config_مداخله_CONTROLLER_CPU_INTERFACE_دننه_واټن must be defined.  Refer منزل Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#د_که_پای

#که_نه_تعریف_شوی config_UNIQUE_مداخله_PRIORITIES
    #تېروتنه config_UNIQUE_مداخله_PRIORITIES must be defined.  Refer منزل Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#د_که_پای

#که_نه_تعریف_شوی config_تیاری_TICK_مداخله
    #تېروتنه config_تیاری_TICK_مداخله() must be defined.  Refer منزل Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#د_که_پای /* configSETUP_TICK_INTERRUPT */

#که_نه_تعریف_شوی config_MAX_API_CALL_مداخله_لومړیتوب
    #تېروتنه config_MAX_API_CALL_مداخله_لومړیتوب must be defined.  Refer منزل Cortex-A equivalent: /* https://www.freertos.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors */
#د_که_پای

#إذا config_MAX_API_CALL_مداخله_لومړیتوب == 0
    #تېروتنه "configMAX_API_CALL_INTERRUPT_PRIORITY must not be set to 0"
#د_که_پای

#إذا config_MAX_API_CALL_مداخله_لومړیتوب > config_UNIQUE_مداخله_PRIORITIES
    #تېروتنه "configMAX_API_CALL_INTERRUPT_PRIORITY must be less than or equal to configUNIQUE_INTERRUPT_PRIORITIES as the lower the numeric priority value the higher the logical interrupt priority"
#د_که_پای

#إذا config_USE_پورټ_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #تېروتنه "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 different priorities as tasks that share a priority will time slice."
    #د_که_پای
#د_که_پای /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#إذا config_MAX_API_CALL_مداخله_لومړیتوب <= ( config_UNIQUE_مداخله_PRIORITIES / 2 )
    #تېروتنه "configMAX_API_CALL_INTERRUPT_PRIORITY must be greater than ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )"
#د_که_پای

#که_نه_تعریف_شوی config_CLEAR_TICK_مداخله
    #تېروتنه config_CLEAR_TICK_مداخله must be defined دننه FreeRTOSConfig.h منزل clear which ever مداخله was کارول_شوی منزل generate the tick مداخله.
#د_که_پای

#إذا config_شمېره_د_CORES < 1
    #تېروتنه config_شمېره_د_CORES must be سېټ منزل 1 or greater.  If the application is not using مضرب_2 cores then سېټ config_شمېره_د_CORES منزل 1.
#د_که_پای /* configNUMBER_OF_CORES < 1 */

#که_نه_تعریف_شوی configENABLE_MPU
    #تېروتنه configENABLE_MPU must be defined دننه FreeRTOSConfig.h. سېټ_2 configENABLE_MPU منزل 1 منزل enable the MPU or 0 منزل disable the MPU.
#د_که_پای /* #if ( configENABLE_MPU == 1 ) */

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 != 0) )
    #تېروتنه Arm Cortex-R82 پورټ supports only MPU Wrapper V2.
#د_که_پای /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 != 0) */

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#تعریف_کړه پورټ_NO_CRITICAL_NESTING    ( ( size_t ) 0 )

/* Macro to unmask all interrupt priorities. */
#تعریف_کړه پورټ_CLEAR_مداخله_PRIORITIES_ماسک()    __asm متطاير ( "SVC %0" : : "i" ( پورټ_SVC_UNMASK_ALL_INTERRUPTS ) : "memory" )

/* Macro to unmask all interrupt priorities from EL1. */
#تعریف_کړه پورټ_CLEAR_مداخله_PRIORITIES_ماسک_FROM_EL1()  \
{                                                       \
    __asm متطاير (                                    \
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
    : "i" ( پورټ_UNMASK_ارزښت )                          \
    );                                                  \
}

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#تعریف_کړه پورټ_NO_FLOATING_ټکی_CONTEXT    ( ( ډېری_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#تعریف_کړه پورټ_SP_ELx                       ( ( ډېری_Type_t ) 0x01 )
#تعریف_کړه پورټ_SP_EL0                       ( ( ډېری_Type_t ) 0x00 )
#تعریف_کړه پورټ_EL1                          ( ( ډېری_Type_t ) 0x04 )
#تعریف_کړه پورټ_EL0                          ( ( ډېری_Type_t ) 0x00 )

#تعریف_کړه پورټ_INITIAL_PSTATE_EL0           ( پورټ_EL0 | پورټ_SP_EL0 )
#تعریف_کړه پورټ_INITIAL_PSTATE_EL1           ( پورټ_EL1 | پورټ_SP_EL0 )

/* Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero. */
#تعریف_کړه پورټ_دوګونی_ټکی_بټونه            ( ( uint8_t ) 0x03 )

/* Masks all bits in the APSR other than the mode bits. */
#تعریف_کړه پورټ_APSR_ډېرپېښ_بټونه_ماسک          ( 0x0C )

/* The I bit in the DAIF bits. */
#تعریف_کړه پورټ_DAIF_I                       ( 0x80 )

#تعریف_کړه پورټ_MAX_8_بټ_ارزښت              ( ( uint8_t ) 0xff )
#تعریف_کړه پورټ_بټ_0_سېټ                    ( ( uint8_t ) 0x01 )

/* The space on the stack required to hold the FPU registers.
 * There are 32 128-bit plus 2 64-bit status registers. */
#تعریف_کړه پورټ_FPU_ثبتوونکی_ټکي           ( ( 32 * 2 ) + 2 )

/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    /**
     * @brief Setup the Memory Protection Unit (MPU).
     */
    PRIVILEGED_FUNCTION فراغ v_تیاری_MPU( فراغ );

    /**
     * @brief Enable the Memory Protection Unit (MPU).
     */
    PRIVILEGED_FUNCTION فراغ vEnableMPU( فراغ );

    /**
     * @brief Called from an ISR and returns the core ID the code is executing on.
     *
     * @return uint8_t The core ID.
     */
    PRIVILEGED_FUNCTION uint8_t uc_پورټ_Get_Core_IDFrom_Isr( فراغ );

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    PRIVILEGED_FUNCTION بنسټ_Type_t x_پورټ_Is_Task_Privileged( فراغ );

    /**
     * @brief Extract MPU region's access permissions from the Protection Region Base Address Register
     * (PRBAR_EL1) value.
     *
     * @param ullPrbarEl1Value PRBAR_EL1 value for the MPU region.
     *
     * @return uint32_t Access permissions.
     */
    PRIVILEGED_FUNCTION ساكن uint32_t prvGetRegionAccessPermissions( uint64_t ull_Prbar_El1_ارزښت );

    /**
     * @brief Does the necessary work to enter a system call.
     *
     * @param pullPrivilegedOnlyTaskStack The task's privileged SP when the SVC was raised.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    PRIVILEGED_FUNCTION فراغ vSystemCallEnter( uint64_t * pull_Privileged_Only_Task_ډېری,
                                               uint8_t uc_System_Call_شمېره );

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    PRIVILEGED_FUNCTION __attribute__( ( naked ) ) فراغ vRequestSystemCallExit( فراغ );

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param ullSystemCallReturnValue The actual system call return value.
     */
    PRIVILEGED_FUNCTION فراغ vSystemCallExit( uint64_t ull_System_Call_Return_ارزښت );

#د_که_پای /* #if ( configENABLE_MPU == 1 ) */

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
خارجي فراغ v_پورټ_Restore_Task_Context( فراغ );
خارجي فراغ vGIC_EnableIRQ( uint32_t ul_مداخله_ID );
خارجي فراغ v_GIC_سېټ_لومړیتوب( uint32_t ul_مداخله_ID, uint32_t ul_لومړیتوب );
خارجي فراغ v_GIC_Power_پورته_Redistributor( فراغ );
خارجي فراغ vGIC_EnableCPUInterface( فراغ );

/*-----------------------------------------------------------*/

#إذا ( config_شمېره_د_CORES == 1 )

    PRIVILEGED_معلومات متطاير uint64_t ullCriticalNesting = 0ULL;

    /* Saved as part of the task context. If ullPortTaskHasFPUContext is non-zero
     * then floating point context must be saved and restored for the task. */
    PRIVILEGED_معلومات uint64_t ull_پورټ_Task_Has_FPUContext = pdFALSE;

    /* Set to 1 to pend a context switch from an ISR. */
    PRIVILEGED_معلومات uint64_t ull_پورټ_Yield_Required = pdFALSE;

    /* Counts the interrupt nesting depth. A context switch is only performed if
     * if the nesting depth is 0. */
    PRIVILEGED_معلومات uint64_t ull_پورټ_مداخله_Nesting = 0;

#وإلا /* #if ( configNUMBER_OF_CORES == 1 ) */
    PRIVILEGED_معلومات متطاير uint64_t ullCriticalNestings[ config_شمېره_د_CORES ] = { 0 };

    /* Flags to check if the secondary cores are ready. */
    PRIVILEGED_معلومات متطاير uint8_t ucSecondaryCoresReadyFlags[ config_شمېره_د_CORES - 1 ] = { 0 };

    /* Flag to signal that the primary core has done all the shared initialisations. */
    PRIVILEGED_معلومات متطاير uint8_t uc_Primary_Core_Init_بشپړ_Flag = 0;

    /* Saved as part of the task context. If ullPortTaskHasFPUContext is non-zero
     * then floating point context must be saved and restored for the task. */
    PRIVILEGED_معلومات uint64_t ull_پورټ_Task_Has_FPUContext[ config_شمېره_د_CORES ] = { pdFALSE };

    /* Set to 1 to pend a context switch from an ISR. */
    PRIVILEGED_معلومات uint64_t ull_پورټ_Yield_Required[ config_شمېره_د_CORES ] = { pdFALSE };

    /* Counts the interrupt nesting depth. A context switch is only performed if
     * if the nesting depth is 0. */
    PRIVILEGED_معلومات uint64_t ull_پورټ_مداخله_Nestings[ config_شمېره_د_CORES ] = { 0 };

#د_که_پای /* #if ( configNUMBER_OF_CORES == 1 ) */

#إذا ( configENABLE_MPU == 1 )
    /* Set to pdTRUE when the scheduler is started. */
    PRIVILEGED_معلومات ساكن بنسټ_Type_t xSchedulerRunning = pdFALSE;
#د_که_پای /* ( configENABLE_MPU == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                         TaskFunction_t px_کوډ,
                                         فراغ * pvParameters,
                                         بنسټ_Type_t x_پرلپسې_Privileged,
                                         xMPU_SETTINGS * xMPUSettings )
    {
        uint32_t ul_شاخص = 0;

        /* Layout must match portRESTORE_CONTEXT pop order (descending stack):
         * 1) FPU flag, 2) Critical nesting, 3) Optional FPU save area,
         * 4) ELR (PC), 5) SPSR (PSTATE), 6) GPRs in restore order pairs.
         */

        /* 1) FPU flag and 2) Critical nesting. */
        #إذا ( configUSE_TASK_FPU_SUPPORT == پورټ_TASK_NO_FPU_CONTEXT_BY_DEFAULT )
            xMPUSettings->ullContext[ ul_شاخص++ ] = پورټ_NO_FLOATING_ټکی_CONTEXT; /* FPU flag */
            xMPUSettings->ullContext[ ul_شاخص++ ] = پورټ_NO_CRITICAL_NESTING;       /* Critical nesting */
        #وإلاإذا ( configUSE_TASK_FPU_SUPPORT == پورټ_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
            xMPUSettings->ullContext[ ul_شاخص++ ] = pdTRUE;                        /* FPU flag */
            xMPUSettings->ullContext[ ul_شاخص++ ] = پورټ_NO_CRITICAL_NESTING;       /* Critical nesting */
            #إذا ( config_شمېره_د_CORES == 1 )
                ull_پورټ_Task_Has_FPUContext = pdTRUE;
            #وإلا
                ull_پورټ_Task_Has_FPUContext[ پورټ_GET_CORE_ID() ] = pdTRUE;
            #د_که_پای
        #وإلا
            #تېروتنه "Invalid configUSE_TASK_FPU_SUPPORT setting - must be 1 or 2."
        #د_که_پای

        /* 3) Optional FPU save area immediately after the flag+critical pair. */
        #إذا ( configUSE_TASK_FPU_SUPPORT == پورټ_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
            memset( &xMPUSettings->ullContext[ ul_شاخص ], 0x00, پورټ_FPU_ثبتوونکی_ټکي * حجم( ډېری_Type_t ) );
            ul_شاخص += پورټ_FPU_ثبتوونکی_ټکي;
        #د_که_پای

        /* 4) ELR (PC) and 5) SPSR (PSTATE). */
        xMPUSettings->ullContext[ ul_شاخص++ ] = ( ډېری_Type_t ) px_کوډ; /* ELR */

        إذا( x_پرلپسې_Privileged == pdTRUE )
        {
            xMPUSettings->ullContext[ ul_شاخص++ ] = پورټ_INITIAL_PSTATE_EL1;    /* SPSR */
        }
        وإلا
        {
            xMPUSettings->ullContext[ ul_شاخص++ ] = پورټ_INITIAL_PSTATE_EL0;    /* SPSR */
        }

        /* 6) General-purpose registers in the order expected by restoreallgpregisters. */
        xMPUSettings->ullContext[ ul_شاخص++ ] = ( ډېری_Type_t ) 0x00;         /* X30 (LR) */
        xMPUSettings->ullContext[ ul_شاخص++ ] = ( ډېری_Type_t ) 0x00;         /* XZR (dummy) */

        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x2828282828282828ULL;        /* X28 */
        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x2929292929292929ULL;        /* X29 */

        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x2626262626262626ULL;        /* X26 */
        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x2727272727272727ULL;        /* X27 */

        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x2424242424242424ULL;        /* X24 */
        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x2525252525252525ULL;        /* X25 */

        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x2222222222222222ULL;        /* X22 */
        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x2323232323232323ULL;        /* X23 */

        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x2020202020202020ULL;        /* X20 */
        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x2121212121212121ULL;        /* X21 */

        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x1818181818181818ULL;        /* X18 */
        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x1919191919191919ULL;        /* X19 */

        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x1616161616161616ULL;        /* X16 */
        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x1717171717171717ULL;        /* X17 */

        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x1414141414141414ULL;        /* X14 */
        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x1515151515151515ULL;        /* X15 */

        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x1212121212121212ULL;        /* X12 */
        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x1313131313131313ULL;        /* X13 */

        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x1010101010101010ULL;        /* X10 */
        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x1111111111111111ULL;        /* X11 */

        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x0808080808080808ULL;        /* X8 */
        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x0909090909090909ULL;        /* X9 */

        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x0606060606060606ULL;        /* X6 */
        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x0707070707070707ULL;        /* X7 */

        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x0404040404040404ULL;        /* X4 */
        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x0505050505050505ULL;        /* X5 */

        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x0202020202020202ULL;        /* X2 */
        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x0303030303030303ULL;        /* X3 */

        xMPUSettings->ullContext[ ul_شاخص++ ] = ( ډېری_Type_t ) pvParameters; /* X0 */
        xMPUSettings->ullContext[ ul_شاخص++ ] = 0x0101010101010101ULL;        /* X1 */

        إذا( x_پرلپسې_Privileged == pdTRUE )
        {
            xMPUSettings->ullTaskFlags |= پورټ_TASK_IS_PRIVILEGED_FLAG;
        }
        وإلا
        {
            xMPUSettings->ullTaskFlags &= ( ~پورټ_TASK_IS_PRIVILEGED_FLAG );
        }

        xMPUSettings->ullTaskUnprivilegedSP = ( ( uint64_t ) px_سر_د_ډېری & پورټ_MPU_PRBAR_EL1_پته_ماسک );

        أرجع &( xMPUSettings->ullContext[ 0 ] );
    }

#وإلا /* #if ( configENABLE_MPU == 1 ) */

    /*
    * See header file for description.
    */
    ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                         TaskFunction_t px_کوډ,
                                         فراغ * pvParameters )
    {
        /* Setup the initial stack of the task.  The stack is set exactly as
        * expected by the portRESTORE_CONTEXT() macro. */

        /* First all the general purpose registers. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x0101010101010101ULL;        /* R1 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters; /* R0 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x0303030303030303ULL;        /* R3 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x0202020202020202ULL;        /* R2 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x0505050505050505ULL;        /* R5 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x0404040404040404ULL;        /* R4 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x0707070707070707ULL;        /* R7 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x0606060606060606ULL;        /* R6 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x0909090909090909ULL;        /* R9 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x0808080808080808ULL;        /* R8 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x1111111111111111ULL;        /* R11 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x1010101010101010ULL;        /* R10 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x1313131313131313ULL;        /* R13 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x1212121212121212ULL;        /* R12 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x1515151515151515ULL;        /* R15 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x1414141414141414ULL;        /* R14 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x1717171717171717ULL;        /* R17 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x1616161616161616ULL;        /* R16 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x1919191919191919ULL;        /* R19 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x1818181818181818ULL;        /* R18 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x2121212121212121ULL;        /* R21 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x2020202020202020ULL;        /* R20 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x2323232323232323ULL;        /* R23 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x2222222222222222ULL;        /* R22 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x2525252525252525ULL;        /* R25 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x2424242424242424ULL;        /* R24 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x2727272727272727ULL;        /* R27 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x2626262626262626ULL;        /* R26 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x2929292929292929ULL;        /* R29 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x2828282828282828ULL;        /* R28 */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x00;         /* XZR - has no effect, used so there are an even number of registers. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x00;         /* R30 - procedure call link register. */

        px_سر_د_ډېری--;
        *px_سر_د_ډېری = پورټ_INITIAL_PSTATE_EL0;

        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) px_کوډ; /* Exception return address. */

        #إذا ( configUSE_TASK_FPU_SUPPORT == پورټ_TASK_NO_FPU_CONTEXT_BY_DEFAULT )
        {
            /* The task will start with a critical nesting count of 0 as interrupts are
            * enabled. */
            px_سر_د_ډېری--;
            *px_سر_د_ډېری = پورټ_NO_CRITICAL_NESTING;

            /* The task will start without a floating point context.  A task that
            * uses the floating point hardware must call vPortTaskUsesFPU() before
            * executing any floating point instructions. */
            px_سر_د_ډېری--;
            *px_سر_د_ډېری = پورټ_NO_FLOATING_ټکی_CONTEXT;
        }
        #وإلاإذا ( configUSE_TASK_FPU_SUPPORT == پورټ_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
        {
            /* The task will start with a floating point context.  Leave enough
            * space for the registers - and ensure they are initialised to 0. */
            px_سر_د_ډېری -= پورټ_FPU_ثبتوونکی_ټکي;
            memset( px_سر_د_ډېری, 0x00, پورټ_FPU_ثبتوونکی_ټکي * حجم( ډېری_Type_t ) );

            /* The task will start with a critical nesting count of 0 as interrupts are
            * enabled. */
            px_سر_د_ډېری--;
            *px_سر_د_ډېری = پورټ_NO_CRITICAL_NESTING;

            px_سر_د_ډېری--;
            *px_سر_د_ډېری = pdTRUE;
            #إذا ( config_شمېره_د_CORES == 1 )
            ull_پورټ_Task_Has_FPUContext = pdTRUE;
            #وإلا
            ull_پورټ_Task_Has_FPUContext[ پورټ_GET_CORE_ID() ] = pdTRUE;
            #د_که_پای
        }
        #وإلا /* if ( configUSE_TASK_FPU_SUPPORT == portTASK_NO_FPU_CONTEXT_BY_DEFAULT ) */
        {
            #تېروتنه "Invalid configUSE_TASK_FPU_SUPPORT setting - configUSE_TASK_FPU_SUPPORT must be set to 1, 2, or left undefined."
        }
        #د_که_پای /* if ( configUSE_TASK_FPU_SUPPORT == portTASK_NO_FPU_CONTEXT_BY_DEFAULT ) */

        أرجع px_سر_د_ډېری;

    }

#د_که_پای /* #if ( configENABLE_MPU == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

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
    فراغ v_پورټ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ثابت بنية x_حافظه_REGION * ثابت xRegions,
                                    ډېری_Type_t * px_Bottom_د_ډېری,
                                    ډېری_Type_t x_ډېری_ژوروالی )  /* PRIVILEGED_FUNCTION */
    {
        uint64_t ull_Region_پیل_پته, ull_Region_پای_ټکی_پته;
        uint8_t  uc_شاخص = 0, uc_Region_شمېره;

        #إذا defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint64_t * __privileged_sram_start__;
            خارجي uint64_t * __privileged_sram_end__;
        #وإلا
            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint64_t __privileged_sram_start__[];
            خارجي uint64_t __privileged_sram_end__[];
        #د_که_پای /* defined( __ARMCC_VERSION ) */

        /* Setup MAIR_EL1. */
        xMPUSettings->ullMairEl1 = ( ( پورټ_MPU_نورمال_حافظه_BUFFERABLE_CACHEABLE << پورټ_MPU_MAIR_EL1_ATTR0_POS ) & پورټ_MPU_MAIR_EL1_ATTR0_ماسک );
        xMPUSettings->ullMairEl1 |= ( ( پورټ_MPU_DEVICE_حافظه_n_Gn_RE << پورټ_MPU_MAIR_EL1_ATTR1_POS ) & پورټ_MPU_MAIR_EL1_ATTR1_ماسک );

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid. At all other
         * times the stack parameters will not be valid and it is assumed that
         * the stack region has already been configured. */
        إذا( x_ډېری_ژوروالی > 0 )
        {
            ull_Region_پیل_پته = ( uint64_t ) px_Bottom_د_ډېری;
            ull_Region_پای_ټکی_پته = ( uint64_t ) px_Bottom_د_ډېری + ( x_ډېری_ژوروالی * ( config_ډېری_ژوروالی_TYPE ) حجم( ډېری_Type_t ) ) - 1;

            /* If the stack is within the privileged SRAM, do not protect it
             * using a separate MPU region. This is needed because this
             * region is already protected using an MPU region and ARMv8-R does
             * not allow overlapping MPU regions.
             */
            إذا( ( ull_Region_پیل_پته >= ( uint64_t ) __privileged_sram_start__ ) &&
                ( ull_Region_پای_ټکی_پته <= ( uint64_t ) __privileged_sram_end__ ) )
            {
                xMPUSettings->xRegionsSettings[ پورټ_ډېری_REGION_شاخص ].ullPrbarEl1 = 0;
                xMPUSettings->xRegionsSettings[ پورټ_ډېری_REGION_شاخص ].ullPrlarEl1 = 0;
            }
            وإلا
            {
                /* Define the region that allows access to the stack. */
                ull_Region_پیل_پته &= پورټ_MPU_PRBAR_EL1_پته_ماسک;
                ull_Region_پای_ټکی_پته &= پورټ_MPU_PRLAR_EL1_پته_ماسک;

                xMPUSettings->xRegionsSettings[ پورټ_ډېری_REGION_شاخص ].ullPrbarEl1 = ( ull_Region_پیل_پته ) |
                                                                                 ( پورټ_MPU_REGION_INNER_SHAREABLE ) |
                                                                                 ( پورټ_MPU_REGION_READ_WRITE ) |
                                                                                 ( پورټ_MPU_REGION_EXECUTE_NEVER );

                xMPUSettings->xRegionsSettings[ پورټ_ډېری_REGION_شاخص ].ullPrlarEl1 = ( ull_Region_پای_ټکی_پته ) |
                                                                                 ( پورټ_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                                                                                 ( پورټ_MPU_PRLAR_EL1_REGION_ENABLE );
            }
        }

        /* User supplied configurable regions. */
        لكل( uc_Region_شمېره = 1; uc_Region_شمېره <= پورټ_عدد_CONFIGURABLE_REGIONS; uc_Region_شمېره++ )
        {
            /* If xRegions is NULL i.e. the task has not specified any MPU
             * region, the else part ensures that all the configurable MPU
             * regions are invalidated.
             * The minimum region size is 64 Bytes.
             */
            إذا( xRegions != عدم )
            {
                /* Configure the region only if the base address is non-NULL.
                 * The user may choose to use only a subset of the available MPU regions.
                 * This check prevents undefined regions (i.e. regions with a NULL base
                 * address) from being configured and from triggering the size-check
                 * assertion below.
                 */
                إذا ( xRegions[ uc_شاخص ].pv_بنسټ_پته != عدم )
                {
                    configASSERT( xRegions[ uc_شاخص ].ul_اوږدتیا_دننه_بایټونه >= 64UL );

                    uint64_t ull_Prbar_El1_Reg_ارزښت, ull_Prlar_El1_Reg_ارزښت;

                    /* Translate the generic region definition contained in xRegions
                     * into the ARMv8-R specific MPU settings that are then stored in
                     * xMPUSettings.
                     */
                    ull_Region_پیل_پته = ( ( uint64_t ) xRegions[ uc_شاخص ].pv_بنسټ_پته ) & پورټ_MPU_PRBAR_EL1_پته_ماسک;
                    ull_Region_پای_ټکی_پته = ( uint64_t ) xRegions[ uc_شاخص ].pv_بنسټ_پته + xRegions[ uc_شاخص ].ul_اوږدتیا_دننه_بایټونه - 1;
                    ull_Region_پای_ټکی_پته &= پورټ_MPU_PRLAR_EL1_پته_ماسک;

                    /* Checks for overlaps with another user defined regions and stack region, which are already configured. */
                    لكل( uint8_t uc_User_Region_شمېره = 0; uc_User_Region_شمېره < پورټ_عدد_CONFIGURABLE_REGIONS; uc_User_Region_شمېره++ )
                    {
                        /* Check for overlap. */
                        إذا( ( پورټ_IS_پته_WITHIN_RANGE( ull_Region_پیل_پته,
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_شمېره ].ullPrbarEl1 & پورټ_MPU_PRBAR_EL1_پته_ماسک ),
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_شمېره ].ullPrlarEl1 & پورټ_MPU_PRLAR_EL1_پته_ماسک ) ) ||
                            ( پورټ_IS_پته_WITHIN_RANGE( ull_Region_پای_ټکی_پته,
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_شمېره ].ullPrbarEl1 & پورټ_MPU_PRBAR_EL1_پته_ماسک ),
                                                        ( xMPUSettings->xRegionsSettings[ uc_User_Region_شمېره ].ullPrlarEl1 & پورټ_MPU_PRLAR_EL1_پته_ماسک ) ) ) ) )
                        {
                            /* Overlap detected - assert. */
                            configASSERT( عدم );
                        }
                    }

                    /* Checks for overlaps with kernel programmed regions which are already programmed as part of vSetupMPU. */
                    لكل (uint8_t uc_Programmed_Region_شاخص = 0; uc_Programmed_Region_شاخص < 4; uc_Programmed_Region_شاخص++)
                    {
                        __asm متطاير ( "msr PRSELR_EL1, %0" : : "r" ( ( uint64_t ) uc_Programmed_Region_شاخص ) );

                        __asm متطاير ( "mrs %0, PRBAR_EL1" : "=r" ( ull_Prbar_El1_Reg_ارزښت ) );
                        ull_Prbar_El1_Reg_ارزښت &= پورټ_MPU_PRBAR_EL1_پته_ماسک;

                        __asm متطاير ( "mrs %0, PRLAR_EL1" : "=r" ( ull_Prlar_El1_Reg_ارزښت ) );
                        ull_Prlar_El1_Reg_ارزښت &= پورټ_MPU_PRLAR_EL1_پته_ماسک;

                        /* Check for overlap. */
                        إذا( ( پورټ_IS_پته_WITHIN_RANGE( ull_Region_پیل_پته,
                                                        ull_Prbar_El1_Reg_ارزښت,
                                                        ull_Prlar_El1_Reg_ارزښت ) ) ||
                            ( پورټ_IS_پته_WITHIN_RANGE( ull_Region_پای_ټکی_پته,
                                                        ull_Prbar_El1_Reg_ارزښت,
                                                        ull_Prlar_El1_Reg_ارزښت ) ) )
                        {
                            /* Overlap detected - assert. */
                            configASSERT( عدم );
                        }
                    }

                    /* Start address. */
                    xMPUSettings->xRegionsSettings[ uc_Region_شمېره ].ullPrbarEl1 = ( ull_Region_پیل_پته );

                    /* RO/RW. */
                    إذا( ( xRegions[ uc_شاخص ].ulParameters & tskMPU_REGION_READ_ONLY ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_شمېره ].ullPrbarEl1 |= ( پورټ_MPU_REGION_READ_ONLY );
                    }
                    وإلا
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_شمېره ].ullPrbarEl1 |= ( پورټ_MPU_REGION_READ_WRITE );
                    }

                    /* XN. */
                    إذا( ( xRegions[ uc_شاخص ].ulParameters & tskMPU_REGION_EXECUTE_NEVER ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_شمېره ].ullPrbarEl1 |= ( پورټ_MPU_REGION_EXECUTE_NEVER );
                    }

                    /* SH. */
                    إذا( ( xRegions[ uc_شاخص ].ulParameters & tskMPU_REGION_INNER_SHAREABLE ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_شمېره ].ullPrbarEl1 |= ( پورټ_MPU_REGION_INNER_SHAREABLE );
                    }
                    وإلا إذا( ( xRegions[ uc_شاخص ].ulParameters & tskMPU_REGION_OUTER_SHAREABLE ) != 0 )
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_شمېره ].ullPrbarEl1 |= ( پورټ_MPU_REGION_OUTER_SHAREABLE );
                    }
                    وإلا
                    {
                        xMPUSettings->xRegionsSettings[ uc_Region_شمېره ].ullPrbarEl1 |= ( پورټ_MPU_REGION_NON_SHAREABLE );
                    }

                    /* End Address. */
                    xMPUSettings->xRegionsSettings[ uc_Region_شمېره ].ullPrlarEl1 = ( ull_Region_پای_ټکی_پته ) |
                                                                                ( پورټ_MPU_PRLAR_EL1_REGION_ENABLE );

                    /* Normal memory/ Device memory. */
                    إذا( ( xRegions[ uc_شاخص ].ulParameters & tsk_MPU_REGION_DEVICE_حافظه ) != 0 )
                    {
                        /* Attr1 in MAIR_EL1 is configured as device memory. */
                        xMPUSettings->xRegionsSettings[ uc_Region_شمېره ].ullPrlarEl1 |= پورټ_MPU_PRLAR_EL1_ATTR_INDEX1;
                    }
                    وإلا
                    {
                        /* Attr0 in MAIR_EL1 is configured as normal memory. */
                        xMPUSettings->xRegionsSettings[ uc_Region_شمېره ].ullPrlarEl1 |= پورټ_MPU_PRLAR_EL1_ATTR_INDEX0;
                    }
                }
            }
            وإلا
            {
                /* Invalidate the region. */
                xMPUSettings->xRegionsSettings[ uc_Region_شمېره ].ullPrbarEl1 = 0UL;
                xMPUSettings->xRegionsSettings[ uc_Region_شمېره ].ullPrlarEl1 = 0UL;
            }

            uc_شاخص++;
        }

    }
    /*-----------------------------------------------------------*/

    فراغ v_تیاری_MPU( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        #إذا defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts.
             */
            خارجي uint64_t * __privileged_functions_start__;
            خارجي uint64_t * __privileged_functions_end__;
            خارجي uint64_t * __syscalls_flash_start__;
            خارجي uint64_t * __syscalls_flash_end__;
            خارجي uint64_t * __unprivileged_flash_start__;
            خارجي uint64_t * __unprivileged_flash_end__;
            خارجي uint64_t * __privileged_sram_start__;
            خارجي uint64_t * __privileged_sram_end__;
        #وإلا /* if defined( __ARMCC_VERSION ) */
            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint64_t __privileged_functions_start__[];
            خارجي uint64_t __privileged_functions_end__[];
            خارجي uint64_t __syscalls_flash_start__[];
            خارجي uint64_t __syscalls_flash_end__[];
            خارجي uint64_t __unprivileged_flash_start__[];
            خارجي uint64_t __unprivileged_flash_end__[];
            خارجي uint64_t __privileged_sram_start__[];
            خارجي uint64_t __privileged_sram_end__[];
        #د_که_پای /* defined( __ARMCC_VERSION ) */

        /* The only permitted number of regions are 16 or 32. */
        configASSERT( ( config_ټول_MPU_REGIONS == 16 ) || ( config_ټول_MPU_REGIONS == 32 ) );

        /* MAIR_EL1 - Index 0. */
        uint64_t ull_Mair_El1_Reg_ارزښت = ( ( پورټ_MPU_نورمال_حافظه_BUFFERABLE_CACHEABLE << پورټ_MPU_MAIR_EL1_ATTR0_POS ) & پورټ_MPU_MAIR_EL1_ATTR0_ماسک );
        /* MAIR_EL1 - Index 1. */
        ull_Mair_El1_Reg_ارزښت |= ( ( پورټ_MPU_DEVICE_حافظه_n_Gn_RE << پورټ_MPU_MAIR_EL1_ATTR1_POS ) & پورټ_MPU_MAIR_EL1_ATTR1_ماسک );

        __asm متطاير ( "msr MAIR_EL1, %0" : : "r" ( ull_Mair_El1_Reg_ارزښت ) );

        /* Setup privileged flash as Read Only so that privileged tasks can
         * read it but not modify.
         */
        uint64_t ull_Prselr_El1_Reg_ارزښت = پورټ_PRIVILEGED_FLASH_REGION;
        __asm متطاير ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_ارزښت ) );

        uint64_t ull_Prbar_El1_Reg_ارزښت = ( ( ( uint64_t ) __privileged_functions_start__ ) & پورټ_MPU_PRBAR_EL1_پته_ماسک ) |
                                       ( پورټ_MPU_REGION_NON_SHAREABLE ) |
                                       ( پورټ_MPU_REGION_PRIVILEGED_READ_ONLY );
        __asm متطاير ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_ارزښت ) );

        uint64_t ull_Prlar_El1_Reg_ارزښت = ( ( ( uint64_t ) __privileged_functions_end__ ) & پورټ_MPU_PRLAR_EL1_پته_ماسک ) |
                                       ( پورټ_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                                       ( پورټ_MPU_PRLAR_EL1_REGION_ENABLE );
        __asm متطاير ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_ارزښت ) );

        /* Setup unprivileged flash as Read Only by both privileged and
         * unprivileged tasks. All tasks can read it but no-one can modify.
         */
        ull_Prselr_El1_Reg_ارزښت = پورټ_UNPRIVILEGED_FLASH_REGION;
        __asm متطاير ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_ارزښت ) );

        ull_Prbar_El1_Reg_ارزښت = ( ( ( uint64_t ) __unprivileged_flash_start__ ) & پورټ_MPU_PRBAR_EL1_پته_ماسک ) |
                              ( پورټ_MPU_REGION_NON_SHAREABLE ) |
                              ( پورټ_MPU_REGION_READ_ONLY );
        __asm متطاير ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_ارزښت ) );

        ull_Prlar_El1_Reg_ارزښت = ( ( ( uint64_t ) __unprivileged_flash_end__ ) & پورټ_MPU_PRLAR_EL1_پته_ماسک ) |
                              ( پورټ_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                              ( پورټ_MPU_PRLAR_EL1_REGION_ENABLE );
        __asm متطاير ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_ارزښت ) );

        /* Setup unprivileged syscalls flash as Read Only by both privileged
         * and unprivileged tasks. All tasks can read it but no-one can modify.
         */
        ull_Prselr_El1_Reg_ارزښت = پورټ_UNPRIVILEGED_SYSCALLS_REGION;
        __asm متطاير ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_ارزښت ) );

        ull_Prbar_El1_Reg_ارزښت = ( ( ( uint64_t ) __syscalls_flash_start__ ) & پورټ_MPU_PRBAR_EL1_پته_ماسک ) |
                              ( پورټ_MPU_REGION_NON_SHAREABLE ) |
                              ( پورټ_MPU_REGION_READ_ONLY );
        __asm متطاير ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_ارزښت ) );

        ull_Prlar_El1_Reg_ارزښت = ( ( ( uint64_t ) __syscalls_flash_end__ ) & پورټ_MPU_PRLAR_EL1_پته_ماسک ) |
                              ( پورټ_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                              ( پورټ_MPU_PRLAR_EL1_REGION_ENABLE );
        __asm متطاير ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_ارزښت ) );

        /* Setup RAM containing kernel data for privileged access only. */
        ull_Prselr_El1_Reg_ارزښت = پورټ_PRIVILEGED_RAM_REGION;
        __asm متطاير ( "msr PRSELR_EL1, %0" : : "r" ( ull_Prselr_El1_Reg_ارزښت ) );

        ull_Prbar_El1_Reg_ارزښت = ( ( ( uint64_t ) __privileged_sram_start__ ) & پورټ_MPU_PRBAR_EL1_پته_ماسک ) |
                              ( پورټ_MPU_REGION_INNER_SHAREABLE ) |
                              ( پورټ_MPU_REGION_PRIVILEGED_READ_WRITE ) |
                              ( پورټ_MPU_REGION_EXECUTE_NEVER );
        __asm متطاير ( "msr PRBAR_EL1, %0" : : "r" ( ull_Prbar_El1_Reg_ارزښت ) );

        ull_Prlar_El1_Reg_ارزښت = ( ( ( uint64_t ) __privileged_sram_end__ ) & پورټ_MPU_PRLAR_EL1_پته_ماسک ) |
                              ( پورټ_MPU_PRLAR_EL1_ATTR_INDEX0 ) |
                              ( پورټ_MPU_PRLAR_EL1_REGION_ENABLE );
        __asm متطاير ( "msr PRLAR_EL1, %0" : : "r" ( ull_Prlar_El1_Reg_ارزښت ) );
    }
    /*-----------------------------------------------------------*/

    فراغ vEnableMPU( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        uint64_t ull_Sctlr_El1_Reg_ارزښت;

        __asm متطاير ( "mrs %0, SCTLR_EL1" : "=r" ( ull_Sctlr_El1_Reg_ارزښت ) );
        /* Enable the MPU. Also enable privileged access to the
         * background region.
         */
        ull_Sctlr_El1_Reg_ارزښت |= ( پورټ_MPU_PRIV_BACKGROUND_ENABLE_بټ | پورټ_MPU_ENABLE_بټ );
        __asm متطاير ( "msr SCTLR_EL1, %0" : : "r" ( ull_Sctlr_El1_Reg_ارزښت ) );

        /* Ensure the write to SCTLR_EL1 is committed before
         * returning.
         */
        __asm متطاير ( "isb" );
    }
    /*-----------------------------------------------------------*/

    بنسټ_Type_t x_پورټ_Is_Task_Privileged( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        بنسټ_Type_t xTaskIsPrivileged = pdFALSE;

        #إذا ( config_شمېره_د_CORES == 1 )
            خارجي TaskHandle_t pxCurrentTCB;
            xMPU_SETTINGS * pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );
        #وإلا
            خارجي TaskHandle_t pxCurrentTCBs[ config_شمېره_د_CORES ];
            xMPU_SETTINGS * pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCBs[ پورټ_GET_CORE_ID_FROM_ISR() ] );
        #د_که_پای

        إذا( ( pxMpuSettings->ullTaskFlags & پورټ_TASK_IS_PRIVILEGED_FLAG ) == پورټ_TASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        أرجع xTaskIsPrivileged;
    }
    /*-----------------------------------------------------------*/

    ساكن uint32_t prvGetRegionAccessPermissions( uint64_t ull_Prbar_El1_ارزښت ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ulAccessPermissions = 0;

        إذا( ( ull_Prbar_El1_ارزښت & پورټ_MPU_PRBAR_EL1_ACCESS_PERMISSIONS_ماسک ) == پورټ_MPU_REGION_READ_ONLY )
        {
            ulAccessPermissions = tskMPU_READ_PERMISSION;
        }

        إذا( ( ull_Prbar_El1_ارزښت & پورټ_MPU_PRBAR_EL1_ACCESS_PERMISSIONS_ماسک ) == پورټ_MPU_REGION_READ_WRITE )
        {
            ulAccessPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
        }

        أرجع ulAccessPermissions;
    }
    /*-----------------------------------------------------------*/

    بنسټ_Type_t x_پورټ_Is_Authorized_منزل_Access_بفر( ثابت فراغ * pv_بفر,
                                                size_t x_بفر_اوږدتیا,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i;
        uint64_t ull_بفر_پیل_پته, ull_بفر_پای_ټکی_پته;
        بنسټ_Type_t xAccessGranted = pdFALSE;
        ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( عدم ); /* Calling task's MPU settings. */

        إذا( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        وإلا إذا( ( xTaskMpuSettings->ullTaskFlags & پورټ_TASK_IS_PRIVILEGED_FLAG ) == پورټ_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        وإلا
        {
            إذا( پورټ_جمع_کړه_UINT64_WILL_ډکېدنه( ( ( uint64_t ) pv_بفر ), ( ( uint64_t ) x_بفر_اوږدتیا - 1ULL ) ) == pdFALSE )
            {
                ull_بفر_پیل_پته = ( uint64_t ) pv_بفر;
                ull_بفر_پای_ټکی_پته = ( ( ( uint64_t ) pv_بفر ) + ( uint64_t ) x_بفر_اوږدتیا - 1ULL );

                لكل( i = 0; i < پورټ_ټول_عدد_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    إذا( ( xTaskMpuSettings->xRegionsSettings[ i ].ullPrlarEl1 & پورټ_MPU_PRLAR_EL1_REGION_ENABLE ) == پورټ_MPU_PRLAR_EL1_REGION_ENABLE )
                    {
                        إذا( پورټ_IS_پته_WITHIN_RANGE( ull_بفر_پیل_پته,
                                                         پورټ_ایستل_لومړی_پته_FROM_PRBAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrbarEl1 ),
                                                         پورټ_ایستل_وروستی_پته_FROM_PRLAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrlarEl1 ) ) &&
                            پورټ_IS_پته_WITHIN_RANGE( ull_بفر_پای_ټکی_پته,
                                                         پورټ_ایستل_لومړی_پته_FROM_PRBAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrbarEl1 ),
                                                         پورټ_ایستل_وروستی_پته_FROM_PRLAR_EL1( xTaskMpuSettings->xRegionsSettings[ i ].ullPrlarEl1 ) ) &&
                            پورټ_IS_AUTHORIZED( ulAccessRequested,
                                               prvGetRegionAccessPermissions( xTaskMpuSettings->xRegionsSettings[ i ].ullPrbarEl1 ) ) )
                        {
                            xAccessGranted = pdTRUE;
                            اكسر;
                        }
                    }
                }
            }
        }

        أرجع xAccessGranted;
    }
    /*-----------------------------------------------------------*/

    فراغ vSystemCallEnter( uint64_t * pull_Privileged_Only_Task_ډېری,
                           uint8_t uc_System_Call_شمېره ) /* PRIVILEGED_FUNCTION */
    {
        #إذا ( config_شمېره_د_CORES == 1 )
            خارجي TaskHandle_t pxCurrentTCB;
        #وإلا
            خارجي TaskHandle_t pxCurrentTCBs[ config_شمېره_د_CORES ];
        #د_که_پای
        خارجي UBaseType_t uxSystemCallImplementations[ عدد_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint64_t ullSystemCallLocation;  /* Address where SVC was raised. */
        __asm متطاير ( "MRS %0, ELR_EL1" : "=r" ( ullSystemCallLocation ) );

        #إذا defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts.
             */
            خارجي uint64_t * __syscalls_flash_start__;
            خارجي uint64_t * __syscalls_flash_end__;
        #وإلا
            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint64_t __syscalls_flash_start__[];
            خارجي uint64_t __syscalls_flash_end__[];
        #د_که_پای /* #if defined( __ARMCC_VERSION ) */

        #إذا ( config_شمېره_د_CORES == 1 )
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );
        #وإلا
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCBs[ پورټ_GET_CORE_ID_FROM_ISR() ] );
        #د_که_پای

        /* Checks:
         * 1. SVC is raised from the system call section (i.e. application is
         *    not raising SVC directly).
         * 2. We do not need to check that ucSystemCallNumber is within range
         *    because the assembly SVC handler checks that before calling
         *    this function.
         */
        إذا( ( ullSystemCallLocation >= ( uint64_t ) __syscalls_flash_start__ ) &&
            ( ullSystemCallLocation <= ( uint64_t ) __syscalls_flash_end__ ) &&
            ( uxSystemCallImplementations[ uc_System_Call_شمېره ] != 0 ) )
        {
            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call.
             */
            pxMpuSettings->xSystemCallInfo.ull_Link_ثبتوونکی_At_System_Call_ثبت = pull_Privileged_Only_Task_ډېری[ پورټ_دننه_واټن_منزل_LR ];

            /* Capture user-mode SP at system call entry. */
            uint64_t ull_User_Sp_At_ثبت;
            __asm متطاير ( "MRS %0, SP_EL0" : "=r" ( ull_User_Sp_At_ثبت ) );
            pxMpuSettings->xSystemCallInfo.ull_User_SPAt_System_Call_ثبت = ull_User_Sp_At_ثبت;

            /* Setup the MPU_<API> inputs, the system call stack, and SPSR. */
            __asm متطاير (
                "MOV X0, %0         \n"
                "MOV X1, %1         \n"
                "MOV X2, %2         \n"
                "MOV X3, %3         \n"
                "MSR ELR_EL1, %4    \n"
                "MSR SP_EL0, %5     \n"
                "MSR SPSR_EL1, %6   \n"
                :
                : "r" ( pull_Privileged_Only_Task_ډېری[ پورټ_دننه_واټن_منزل_X0 ] ),
                  "r" ( pull_Privileged_Only_Task_ډېری[ پورټ_دننه_واټن_منزل_X1 ] ),
                  "r" ( pull_Privileged_Only_Task_ډېری[ پورټ_دننه_واټن_منزل_X2 ] ),
                  "r" ( pull_Privileged_Only_Task_ډېری[ پورټ_دننه_واټن_منزل_X3 ] ),
                  "r" ( ( uint64_t ) uxSystemCallImplementations[ uc_System_Call_شمېره ] ),
                  "r" ( &( pxMpuSettings->ullContext[ MAX_CONTEXT_اندازه + config_SYSTEM_CALL_ډېری_اندازه ] ) ),
                  "r" ( پورټ_INITIAL_PSTATE_EL1 )
                : "memory", "x0", "x1", "x2", "x3"
            );
        }
    }
    /*-----------------------------------------------------------*/

    فراغ vRequestSystemCallExit( فراغ ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm متطاير ( "svc %0 \n" ::"i" ( پورټ_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }
    /*-----------------------------------------------------------*/

    فراغ vSystemCallExit( uint64_t ull_System_Call_Return_ارزښت ) /* PRIVILEGED_FUNCTION */
    {
        #إذا ( config_شمېره_د_CORES == 1 )
            خارجي TaskHandle_t pxCurrentTCB;
        #وإلا
            خارجي TaskHandle_t pxCurrentTCBs[ config_شمېره_د_CORES ];
        #د_که_پای
        xMPU_SETTINGS * pxMpuSettings;
        uint64_t ullSystemCallLocation; /* Address where SVC was raised. */
        __asm متطاير ( "MRS %0, ELR_EL1" : "=r" ( ullSystemCallLocation ) );

        #إذا defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint64_t * __privileged_functions_start__;
            خارجي uint64_t * __privileged_functions_end__;
        #وإلا
            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint64_t __privileged_functions_start__[];
            خارجي uint64_t __privileged_functions_end__[];
        #د_که_پای /* #if defined( __ARMCC_VERSION ) */

        #إذا ( config_شمېره_د_CORES == 1 )
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );
        #وإلا
            pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCBs[ پورټ_GET_CORE_ID_FROM_ISR() ] );
        #د_که_پای

        /* Check:
         * SVC is raised from the privileged code (i.e. application is not
         * raising SVC directly). This SVC is only raised from
         * vRequestSystemCallExit which is in the privileged code section.
         */
        إذا( ( ullSystemCallLocation >= ( uint64_t ) __privileged_functions_start__ ) &&
            ( ullSystemCallLocation <= ( uint64_t ) __privileged_functions_end__ ) )
        {
            __asm متطاير (
                "MSR ELR_EL1, %0    \n" /* Return to the MPU_<API> caller. */
                "MSR SP_EL0, %1     \n" /* Restore user SP saved at syscall entry. */
                "MSR SPSR_EL1, %3   \n" /* Ensure return to EL0. */
                "MOV X0, %2         \n" /* Move the system call return value to X0. */
                :
                : "r" ( pxMpuSettings->xSystemCallInfo.ull_Link_ثبتوونکی_At_System_Call_ثبت ),
                  "r" ( pxMpuSettings->xSystemCallInfo.ull_User_SPAt_System_Call_ثبت ),
                  "r" ( ull_System_Call_Return_ارزښت ),
                  "r" ( ( uint64_t ) پورټ_INITIAL_PSTATE_EL0 )
                : "memory"
            );
        }
    }
    /*-----------------------------------------------------------*/

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        فراغ v_پورټ_Grant_Access_منزل_Kernel_Object( TaskHandle_t x_دننی_Task_Handle,
                                             int32_t l_دننی_شاخص_د_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_ثبت_شاخص, ul_Access_Control_List_ثبت_بټ;
            xMPU_SETTINGS * xTaskMpuSettings;

            /* Calculate the Access Control List entry index and bit position
             * within that entry. */
            ul_Access_Control_List_ثبت_شاخص = ( ( uint32_t ) l_دننی_شاخص_د_Kernel_Object / پورټ_ACL_ثبت_اندازه_بټونه );
            ul_Access_Control_List_ثبت_بټ = ( ( uint32_t ) l_دننی_شاخص_د_Kernel_Object % پورټ_ACL_ثبت_اندازه_بټونه );

            xTaskMpuSettings = xTaskGetMPUSettings( x_دننی_Task_Handle );

            /* Set the bit corresponding to the kernel object to grant access. */
            xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ثبت_شاخص ] |= ( 1U << ul_Access_Control_List_ثبت_بټ );
        }
        /*-----------------------------------------------------------*/

        فراغ v_پورټ_Revoke_Access_منزل_Kernel_Object( TaskHandle_t x_دننی_Task_Handle,
                                              int32_t l_دننی_شاخص_د_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_ثبت_شاخص, ul_Access_Control_List_ثبت_بټ;
            xMPU_SETTINGS * xTaskMpuSettings;

            /* Calculate the Access Control List entry index and bit position
             * within that entry. */
            ul_Access_Control_List_ثبت_شاخص = ( ( uint32_t ) l_دننی_شاخص_د_Kernel_Object / پورټ_ACL_ثبت_اندازه_بټونه );
            ul_Access_Control_List_ثبت_بټ = ( ( uint32_t ) l_دننی_شاخص_د_Kernel_Object % پورټ_ACL_ثبت_اندازه_بټونه );

            xTaskMpuSettings = xTaskGetMPUSettings( x_دننی_Task_Handle );

            /* Clear the bit corresponding to the kernel object to revoke access. */
            xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ثبت_شاخص ] &= ~( 1U << ul_Access_Control_List_ثبت_بټ );
        }
        /*-----------------------------------------------------------*/

        بنسټ_Type_t x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( int32_t l_دننی_شاخص_د_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_ثبت_شاخص, ul_Access_Control_List_ثبت_بټ;
            بنسټ_Type_t xAccessGranted = pdFALSE;
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

                ul_Access_Control_List_ثبت_شاخص = ( ( uint32_t ) l_دننی_شاخص_د_Kernel_Object / پورټ_ACL_ثبت_اندازه_بټونه );
                ul_Access_Control_List_ثبت_بټ = ( ( uint32_t ) l_دننی_شاخص_د_Kernel_Object % پورټ_ACL_ثبت_اندازه_بټونه );

                إذا( ( xTaskMpuSettings->ullTaskFlags & پورټ_TASK_IS_PRIVILEGED_FLAG ) == پورټ_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                وإلا
                {
                    إذا( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ثبت_شاخص ] & ( 1U << ul_Access_Control_List_ثبت_بټ ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            أرجع xAccessGranted;
        }
        /*-----------------------------------------------------------*/
    #وإلا /* configENABLE_ACCESS_CONTROL_LIST == 1 */

        بنسټ_Type_t x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( int32_t l_دننی_شاخص_د_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( فراغ ) l_دننی_شاخص_د_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            أرجع pdTRUE;
        }
        /*-----------------------------------------------------------*/

    #د_که_پای /* configENABLE_ACCESS_CONTROL_LIST == 1 */

#د_که_پای /* #if ( configENABLE_MPU == 1 ) */

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    uint64_t ullAPSR;

    #إذا ( configASSERT_DEFINED == 1 )
    {
        متطاير uint8_t uc_Original_لومړیتوب;
        متطاير uint8_t * ثابت puc_لومړی_User_لومړیتوب_ثبتوونکی = ( متطاير uint8_t * ثابت ) ( config_مداخله_CONTROLLER_بنسټ_پته + پورټ_مداخله_لومړیتوب_ثبتوونکی_دننه_واټن );
        متطاير uint8_t uc_Max_لومړیتوب_ارزښت;

        /* Determine how many priority bits are implemented in the GIC.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_لومړیتوب = *puc_لومړی_User_لومړیتوب_ثبتوونکی;

        /* Determine the number of priority bits available.  First write to
         * all possible bits. */
        *puc_لومړی_User_لومړیتوب_ثبتوونکی = پورټ_MAX_8_بټ_ارزښت;

        /* Read the value back to see how many bits stuck. */
        uc_Max_لومړیتوب_ارزښت = *puc_لومړی_User_لومړیتوب_ثبتوونکی;

        /* Shift to the least significant bits. */
        طالما( ( uc_Max_لومړیتوب_ارزښت & پورټ_بټ_0_سېټ ) != پورټ_بټ_0_سېټ )
        {
            uc_Max_لومړیتوب_ارزښت >>= ( uint8_t ) 0x01;
        }

        /* Sanity check configUNIQUE_INTERRUPT_PRIORITIES matches the read
         * value. */
        configASSERT( uc_Max_لومړیتوب_ارزښت >= پورټ_ټیټ_ترین_مداخله_لومړیتوب );


        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_لومړی_User_لومړیتوب_ثبتوونکی = uc_Original_لومړیتوب;
    }
    #د_که_پای /* configASSERT_DEFINED */

    __asm متطاير ( "MRS %0, CurrentEL" : "=r" ( ullAPSR ) );
    ullAPSR &= پورټ_APSR_ډېرپېښ_بټونه_ماسک;

    configASSERT( ullAPSR == پورټ_EL1 );

    #إذا ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        v_تیاری_MPU();
    }
    #د_که_پای /* #if ( configENABLE_MPU == 1 ) */

    /* Interrupts are turned off in the CPU itself to ensure a tick does
     * not execute while the scheduler is being started.  Interrupts are
     * automatically turned back on in the CPU when the first task starts
     * executing. */
    __asm متطاير ( "MSR DAIFSET, #2\n"
                     "DSB SY\n"
                     "ISB SY\n" ::: "memory" );
    #إذا ( config_شمېره_د_CORES > 1 )
        /* Start the timer that generates the tick ISR. */
        config_تیاری_TICK_مداخله();
        uc_Primary_Core_Init_بشپړ_Flag = 1;
        __asm متطاير ( "SEV                       \n"
                         "DSB SY                    \n"
                         "ISB SY                    \n"
                         ::: "memory" );
        /* Hold the primary core here until all the secondary cores are ready, this would be achieved only when
         * all elements of ucSecondaryCoresReadyFlags are set.
         */
        طالما( 1 )
        {
            بنسټ_Type_t xAllCoresReady = pdTRUE;
            لكل( uint8_t ucCoreID = 0; ucCoreID < ( config_شمېره_د_CORES - 1 ); ucCoreID++ )
            {
                إذا( ucSecondaryCoresReadyFlags[ ucCoreID ] != pdTRUE )
                {
                    xAllCoresReady = pdFALSE;
                    اكسر;
                }
            }

            إذا ( xAllCoresReady == pdTRUE )
            {
                اكسر;
            }
        }
    #وإلا /* if ( configNUMBER_OF_CORES > 1 ) */
        /* Start the timer that generates the tick ISR. */
        config_تیاری_TICK_مداخله();
    #د_که_پای /* if ( configNUMBER_OF_CORES > 1 ) */

    #إذا ( configENABLE_MPU == 1 )
        xSchedulerRunning = pdTRUE;

        /* Enable the Memory Protection Unit (MPU)
         * MPU is only enabled after the primary and secondary handshakes
         * are done as to prevent inconsistent MPU regions attributes across
         * different cores resulting in unupdated values of the handshake
         * flags. 
         */
        vEnableMPU();
    #د_که_پای /* #if ( configENABLE_MPU == 1 ) */

    /* Start the first task executing. */
    v_پورټ_Restore_Task_Context();

    أرجع 0;
}

/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ ) /* PRIVILEGED_FUNCTION */
{
    /* Stub implementation for ports where there is nothing to return to
     * Artificially force an assert. */
    configASSERT( عدم );
}

/*-----------------------------------------------------------*/

#إذا  ( config_شمېره_د_CORES == 1 )
    PRIVILEGED_FUNCTION فراغ v_پورټ_Enter_Critical( فراغ )
    {
        /* Mask interrupts up to the max syscall interrupt priority. */
        ux_پورټ_سېټ_مداخله_ماسک();

        /* Now interrupts are disabled ullCriticalNesting can be accessed
         * directly.  Increment ullCriticalNesting to keep a count of how many times
         * portENTER_CRITICAL() has been called. */
        ullCriticalNesting++;

        /* This is not the interrupt safe version of the enter critical function so
         * assert() if it is being called from an interrupt context.  Only API
         * functions that end in "FromISR" can be used in an interrupt.  Only assert if
         * the critical nesting count is 1 to protect against recursive calls if the
         * assert function also uses a critical section. */
        إذا( ullCriticalNesting == 1ULL )
        {
            configASSERT( ull_پورټ_مداخله_Nesting == 0 );
        }
    }

/*-----------------------------------------------------------*/

    PRIVILEGED_FUNCTION فراغ v_پورټ_Exit_Critical( فراغ )
    {
        إذا( ullCriticalNesting > پورټ_NO_CRITICAL_NESTING )
        {
            /* Decrement the nesting count as the critical section is being
             * exited. */
            ullCriticalNesting--;

            /* If the nesting level has reached zero then all interrupt
             * priorities must be re-enabled. */
            إذا( ullCriticalNesting == پورټ_NO_CRITICAL_NESTING )
            {
                /* Critical nesting has reached zero so all interrupt priorities
                 * should be unmasked. */
                پورټ_CLEAR_مداخله_PRIORITIES_ماسک();
            }
        }
    }
#د_که_پای /* if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/

فراغ FreeRTOS_Tick_Handler( فراغ )
{
    /* Must be the lowest possible priority. */
    uint64_t ull_Running_مداخله_لومړیتوب;
    __asm متطاير ( "MRS %0, ICC_RPR_EL1" : "=r" ( ull_Running_مداخله_لومړیتوب ) );

    configASSERT( ull_Running_مداخله_لومړیتوب == ( پورټ_ټیټ_ترین_USABLE_مداخله_لومړیتوب << پورټ_لومړیتوب_ښويدنه ) );

    /* Interrupts should not be enabled before this point. */
    #إذا ( configASSERT_DEFINED == 1 )
    {
        uint64_t ull_ماسک_بټونه;

        __asm متطاير ( "MRS %0, DAIF" : "=r" ( ull_ماسک_بټونه )::"memory" );
        configASSERT( ( ull_ماسک_بټونه & پورټ_DAIF_I ) != 0 );
    }
    #د_که_پای /* configASSERT_DEFINED */

    /* Set interrupt mask before altering scheduler structures. The tick
     * interrupt runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value.  It is
     * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
     * updated.
     */
    UBaseType_t ux_مداخله_حالت = پورټ_سېټ_مداخله_ماسک_FROM_ISR();

    #إذا ( config_شمېره_د_CORES > 1 )
        UBaseType_t x = پورټ_ENTER_CRITICAL_FROM_ISR();
    #د_که_پای /* if ( configNUMBER_OF_CORES > 1 ) */

    /* Increment the RTOS tick. */
    إذا( xTaskIncrementTick() != pdFALSE )
    {
        #إذا ( config_شمېره_د_CORES == 1 )
            ull_پورټ_Yield_Required = pdTRUE;
        #وإلا
            ull_پورټ_Yield_Required[ پورټ_GET_CORE_ID_FROM_ISR() ] = pdTRUE;
        #د_که_پای
    }
    #إذا ( config_شمېره_د_CORES > 1 )
        پورټ_EXIT_CRITICAL_FROM_ISR(x);
    #د_که_پای /* if ( configNUMBER_OF_CORES > 1 ) */

    /* Ensure all interrupt priorities are active again. */
    پورټ_CLEAR_مداخله_ماسک_FROM_ISR( ux_مداخله_حالت );

    /* Ok to enable interrupts after the interrupt source has been cleared. */
    config_CLEAR_TICK_مداخله();
}

/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_FPU_SUPPORT == پورټ_TASK_NO_FPU_CONTEXT_BY_DEFAULT )

    فراغ v_پورټ_Task_کاروي_FPU( فراغ )
    {
        /* A task is registering the fact that it needs an FPU context.  Set the
         * FPU flag (which is saved as part of the task context). */
        #إذا  ( config_شمېره_د_CORES == 1 )
            ull_پورټ_Task_Has_FPUContext = pdTRUE;
        #وإلا
            ull_پورټ_Task_Has_FPUContext[ پورټ_GET_CORE_ID() ] = pdTRUE;
        #د_که_پای

        /* Consider initialising the FPSR here - but probably not necessary in
         * AArch64. */
    }

#د_که_پای /* configUSE_TASK_FPU_SUPPORT */

/*-----------------------------------------------------------*/

فراغ v_پورټ_Clear_مداخله_ماسک( UBaseType_t ux_New_ماسک_ارزښت )
{
    إذا( ux_New_ماسک_ارزښت == پورټ_UNMASK_ارزښت )
    {
        /* Unmask all interrupt priorities. */
        پورټ_CLEAR_مداخله_PRIORITIES_ماسک();
    }
    وإلا
    {
        __asm متطاير (
            "SVC %0 \n"
            :
            : "i" ( پورټ_SVC_UNMASK_INTERRUPTS )
            : "memory"
        );
    }
}

فراغ v_پورټ_Clear_مداخله_ماسک_From_ISR( UBaseType_t ux_New_ماسک_ارزښت )
{
    __asm متطاير (
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
        : "r" ( ux_New_ماسک_ارزښت )
    );
}
/*-----------------------------------------------------------*/

UBaseType_t ux_پورټ_سېټ_مداخله_ماسک( فراغ )
{
    UBaseType_t ullPMRValue;

    /* Use SVC so this can be called safely from EL0 tasks. */
    __asm متطاير (
        "svc %1        \n"
        "mov %0, x0    \n"
        : "=r" ( ullPMRValue )
        : "i" ( پورټ_SVC_ماسک_ALL_INTERRUPTS )
        : "x0", "memory"
    );

    أرجع ullPMRValue;
}

/* EL1/ISR variant to avoid SVC from interrupt context. */
UBaseType_t ux_پورټ_سېټ_مداخله_ماسک_From_ISR( فراغ )
{
    UBaseType_t ullPMRValue;

    __asm متطاير ( "MRS %0, ICC_PMR_EL1" : "=r" ( ullPMRValue ) );

    إذا( ullPMRValue != ( config_MAX_API_CALL_مداخله_لومړیتوب << پورټ_لومړیتوب_ښويدنه ) )
    {
        __asm متطاير ( "MSR DAIFSET, #2        \n"
                         "DSB SY                 \n"
                         "ISB SY                 \n"
                         "MSR ICC_PMR_EL1, %0    \n"
                         "DSB SY                 \n"
                         "ISB SY                 \n"
                         "MSR DAIFCLR, #2        \n"
                         "DSB SY                 \n"
                         "ISB SY                 \n"
                         ::"r" ( config_MAX_API_CALL_مداخله_لومړیتوب << پورټ_لومړیتوب_ښويدنه ) : "memory" );
    }

    أرجع ullPMRValue;
}

/*-----------------------------------------------------------*/

#إذا ( configASSERT_DEFINED == 1 )

    فراغ v_پورټ_Validate_مداخله_لومړیتوب( فراغ )
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
        uint64_t ull_Running_مداخله_لومړیتوب;
        __asm متطاير ( "MRS %0, ICC_RPR_EL1" : "=r" ( ull_Running_مداخله_لومړیتوب ) );
        configASSERT( ull_Running_مداخله_لومړیتوب >= ( config_MAX_API_CALL_مداخله_لومړیتوب << پورټ_لومړیتوب_ښويدنه ) );
    }

#د_که_پای /* configASSERT_DEFINED */

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
 __attribute__( ( weak ) ) فراغ vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR )
{
    ( فراغ ) ulICCIAR;
    configASSERT( ( متطاير فراغ * ) عدم );
}

/*-----------------------------------------------------------*/

#إذا ( config_شمېره_د_CORES > 1 )

    /* Which core owns the lock? Keep in privileged, shareable RAM. */
    PRIVILEGED_معلومات متطاير uint64_t ullOwnedByCore[ پورټ_MAX_CORE_شمېر ];
    /* Lock count a core owns. */
    PRIVILEGED_معلومات متطاير uint64_t ull_Recursion_شمېر_By_قلف[ e_قلف_شمېر ];
    /* Index 0 is used for ISR lock and Index 1 is used for task lock. */
    PRIVILEGED_معلومات uint32_t ul_Gate_کلمه[ e_قلف_شمېر ];

    فراغ v_مداخله_Core( uint32_t ul_مداخله_ID, uint8_t ucCoreID )
    {
        uint64_t ulRegVal = 0;
        uint32_t ul_Core_ماسک = ( 1UL << ucCoreID );
        ulRegVal |= ( (ul_Core_ماسک & 0xFFFF) | ( ( ul_مداخله_ID & 0xF ) << 24U ) );
        __asm متطاير (
            "str  x0, [ sp, #-0x10 ]!       \n"
            "mov  x0, %0                    \n"
            "svc  %1                        \n"
            "ldr  x0, [ sp ], # 0x10        \n"
            :
            : "r" ( ulRegVal ), "i" ( پورټ_SVC_مداخله_CORE )
            : "memory", "w1"
        );
    }

/*-----------------------------------------------------------*/

    ساكن مضمن فراغ prvSpinUnlock( uint32_t * ul_قلف )
    {
        /* Conservative unlock: preserve original barriers for broad HW/FVP. */
        __asm متطاير (
            "dmb sy         \n"
            "mov w1, #0     \n"
            "str w1, [%x0]  \n"
            "sev            \n"
            "dsb sy         \n"
            "isb sy         \n"
            :
            : "r" ( ul_قلف )
            : "memory", "w1"
        );
    }

/*-----------------------------------------------------------*/

    ساكن مضمن uint32_t prvSpinTrylock( uint32_t * ul_قلف )
    {
        /*
         * Conservative LDXR/STXR trylock:
         * - Return 1 immediately if busy, clearing exclusive state (CLREX).
         * - Retry STXR only on spurious failure when observed free.
         * - DMB on success to preserve expected acquire semantics.
         */
        سجل uint32_t ulRet;
        __asm متطاير (
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
            : "r" ( ul_قلف )
            : "memory", "w1", "w2", "w3"
        );

        أرجع ulRet;
    }

/*-----------------------------------------------------------*/

    /* Read 64b value shared between cores. */
    ساكن مضمن uint64_t prvGet64( متطاير uint64_t * x )
    {
        __asm( "dsb sy" );
        أرجع *x;
    }

/*-----------------------------------------------------------*/

    /* Write 64b value shared between cores. */
    ساكن مضمن فراغ prvSet64( متطاير uint64_t * x,
                                 uint64_t ارزښت )
    {
        *x = ارزښت;
        __asm( "dsb sy" );
    }

/*-----------------------------------------------------------*/

    فراغ v_پورټ_Recursive_قلف( uint8_t ucCoreID,
                             e_پورټ_RTOSLock e_قلف_عدد,
                             بنسټ_Type_t uxAcquire )
    {
        /* Validate the core ID and lock number. */
        configASSERT( ucCoreID < پورټ_MAX_CORE_شمېر );
        configASSERT( e_قلف_عدد < e_قلف_شمېر );

        uint32_t ul_قلف_بټ = 1u << e_قلف_عدد;

        /* Lock acquire */
        إذا( uxAcquire )
        {
            /* Check if spinlock is available.
             * If spinlock is not available check if the core owns the lock.
             * If the core owns the lock wait increment the lock count by the core.
             * If core does not own the lock wait for the spinlock.
             */
            إذا( prvSpinTrylock( &ul_Gate_کلمه[ e_قلف_عدد ] ) != 0 )
            {
                /* Check if the core owns the spinlock. */
                إذا( prvGet64( &ullOwnedByCore[ ucCoreID ] ) & ul_قلف_بټ )
                {
                    configASSERT( prvGet64( &ull_Recursion_شمېر_By_قلف[ e_قلف_عدد ] ) != 255u );
                    prvSet64( &ull_Recursion_شمېر_By_قلف[ e_قلف_عدد ], ( prvGet64( &ull_Recursion_شمېر_By_قلف[ e_قلف_عدد ] ) + 1 ) );
                    أرجع;
                }

                /* Preload the gate word into the cache. */
                uint32_t dummy = ul_Gate_کلمه[ e_قلف_عدد ];
                dummy++;

                طالما( prvSpinTrylock( &ul_Gate_کلمه[ e_قلف_عدد ] ) != 0 )
                {
                   /* Follow Arm's recommended way of sleeping
                    * sevl is used to prime the wait loop.
                    * The first wfe wakes immediately because sevl has set the flag.
                    * Check the lock, if it's not available, issue a second wfe to sleep.
                    * This guarantees the core actually goes to sleep.
                    */
                    __asm متطاير (
                        "sevl            \n"
                        "1: wfe          \n"
                        "ldr w2, [%x0]   \n"
                        "cbnz w2, 1b     \n"
                        :
                        : "r" ( &ul_Gate_کلمه[ e_قلف_عدد ] )
                        : "memory", "w2"
                    );
                }
            }

            /* Add barrier to ensure lock is taken before we proceed. */
            __asm__ __volatile__ ( "dmb sy" ::: "memory" );

            /* Assert the lock count is 0 when the spinlock is free and is acquired. */
            configASSERT( prvGet64( &ull_Recursion_شمېر_By_قلف[ e_قلف_عدد ] ) == 0 );

            /* Set lock count as 1. */
            prvSet64( &ull_Recursion_شمېر_By_قلف[ e_قلف_عدد ], 1 );
            /* Set ullOwnedByCore. */
            prvSet64( &ullOwnedByCore[ ucCoreID ], ( prvGet64( &ullOwnedByCore[ ucCoreID ] ) | ul_قلف_بټ ) );
        }
        /* Lock release. */
        وإلا
        {
            /* Assert the lock is not free already. */
            configASSERT( ( prvGet64( &ullOwnedByCore[ ucCoreID ] ) & ul_قلف_بټ ) != 0 );
            configASSERT( prvGet64( &ull_Recursion_شمېر_By_قلف[ e_قلف_عدد ] ) != 0 );

            /* Reduce ullRecursionCountByLock by 1. */
            prvSet64( &ull_Recursion_شمېر_By_قلف[ e_قلف_عدد ], ( prvGet64( &ull_Recursion_شمېر_By_قلف[ e_قلف_عدد ] ) - 1 ) );

            إذا( !prvGet64( &ull_Recursion_شمېر_By_قلف[ e_قلف_عدد ] ) )
            {
                prvSet64( &ullOwnedByCore[ ucCoreID ], ( prvGet64( &ullOwnedByCore[ ucCoreID ] ) & ~ul_قلف_بټ ) );
                prvSpinUnlock( &ul_Gate_کلمه[ e_قلف_عدد ] );
                /* Add barrier to ensure lock status is reflected before we proceed. */
                __asm__ __volatile__ ( "dmb sy" ::: "memory" );
            }
        }
    }

/*-----------------------------------------------------------*/

    uint8_t uc_پورټ_Get_Core_ID( فراغ )
    {
        /* Use SVC to obtain the core ID in a way that is safe when called
         * from EL0 tasks. ISRs and EL1 code should use
         * ucPortGetCoreIDFromIsr()/portGET_CORE_ID_FROM_ISR().
         */
        uint8_t ucCoreID;
        __asm متطاير (
            "svc %1             \n"
            "mov %w0, w0        \n"
            : "=r" ( ucCoreID )
            : "i" ( پورټ_SVC_GET_CORE_ID )
            : "x0", "memory"
        );
        أرجع ucCoreID;
    }

/*-----------------------------------------------------------*/

    uint8_t uc_پورټ_Get_Core_IDFrom_Isr ( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        uint64_t ullMpidrEl1;
        __asm متطاير ( "MRS %0, MPIDR_EL1" : "=r" ( ullMpidrEl1 ) );

        أرجع ( uint8_t ) ( ullMpidrEl1 & 0xff );
    }

/*------------------------------------------------------------*/
    فراغ FreeRTOS_SGI_Handler( فراغ )
    {
        /* Must be the lowest possible priority. */
        uint64_t ull_Running_مداخله_لومړیتوب;
        __asm متطاير ( "MRS %0, ICC_RPR_EL1" : "=r" ( ull_Running_مداخله_لومړیتوب ) );

        configASSERT( ull_Running_مداخله_لومړیتوب == ( پورټ_ټیټ_ترین_USABLE_مداخله_لومړیتوب << پورټ_لومړیتوب_ښويدنه ) );
        /* Interrupts should not be enabled before this point. */
        #إذا ( configASSERT_DEFINED == 1 )
        {
            uint64_t ull_ماسک_بټونه;

            __asm متطاير ( "mrs %0, DAIF" : "=r" ( ull_ماسک_بټونه )::"memory" );
            configASSERT( ( ull_ماسک_بټونه & پورټ_DAIF_I ) != 0 );
        }
        #د_که_پای /* configASSERT_DEFINED */

        /* Set interrupt mask before altering scheduler structures. The SGI
         * interrupt runs at the lowest priority, so interrupts cannot already be masked,
         * so there is no need to save and restore the current mask value.  It is
         * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
         * updated.
         */
        UBaseType_t ux_مداخله_حالت = پورټ_سېټ_مداخله_ماسک_FROM_ISR();

        UBaseType_t ux_Saved_مداخله_حالت = پورټ_ENTER_CRITICAL_FROM_ISR();
        #إذا ( config_شمېره_د_CORES == 1 )
            ull_پورټ_Yield_Required = pdTRUE;
        #وإلا
            ull_پورټ_Yield_Required[ پورټ_GET_CORE_ID_FROM_ISR() ] = pdTRUE;
        #د_که_پای
        پورټ_EXIT_CRITICAL_FROM_ISR( ux_Saved_مداخله_حالت );
        پورټ_CLEAR_مداخله_ماسک_FROM_ISR( ux_مداخله_حالت );
    }

/*-----------------------------------------------------------*/

#د_که_پای /* if( configNUMBER_OF_CORES > 1 ) */
