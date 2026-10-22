/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2024 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers. That should only be done when
 * task.h is included from an application file. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MPU_WRAPPERS_INCLUDED_FROM_API_FILE
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_WRAPPERS_INCLUDED_FROM_API_FILE
#ਜੇ_ਅੰਤ /* MPU_WRAPPERS_INCLUDED_FROM_API_FILE */

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "portmacro.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mpu_syscall_numbers.h"

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Max value that fits in a uint32_t type. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਜੋੜੋ_UINT32_WILL_ਉਛਾਲ( a, b )    ( ( a ) > ( ਪੋਰਟ_UINT32_MAX - ( b ) ) )
/* ----------------------------------------------------------------------------------- */

/**
 * @brief Variable used to keep track of critical section nesting.
 *
 * @ingroup Critical Sections
 *
 * This variable is stored as part of the task context and must be initialised
 * to a non zero value to ensure interrupts don't inadvertently become unmasked
 * before the scheduler starts. As it is stored as part of the task context, it
 * will be set to 0 when the first task is started.
 */
PRIVILEGED_ਅੰਕੜੇ ਅਸਥਿਰ UBaseType_t ulCriticalNesting = 0xFFFF;

/**
 * @brief Set to 1 to pend a context switch from an ISR.
 *
 * @ingroup Interrupt Management
 */
PRIVILEGED_ਅੰਕੜੇ ਅਸਥਿਰ UBaseType_t ul_ਪੋਰਟ_Yield_Required = pdFALSE;

/**
 * @brief Interrupt nesting depth, used to count the number of interrupts to unwind.
 *
 * @ingroup Interrupt Management
 */
PRIVILEGED_ਅੰਕੜੇ ਅਸਥਿਰ UBaseType_t ul_ਪੋਰਟ_ਰੁਕਾਵਟ_Nesting = 0UL;

/**
 * @brief Variable to track whether or not the scheduler has been started.
 *
 * @ingroup Scheduler
 *
 * This is the port specific version of the xSchedulerRunning in tasks.c.
 */
PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ ਅਧਾਰ_Type_t prv_ਪੋਰਟ_Scheduler_Running = pdFALSE;

/* -------------------------- Private Function Declarations -------------------------- */

/**
 * @brief Determine if the given MPU region settings authorizes the requested
 * access to the given buffer.
 *
 * @ingroup Task Context
 * @ingroup MPU Control
 *
 * @param xTaskMPURegion MPU region settings.
 * @param ulBufferStart Start address of the given buffer.
 * @param ulBufferLength Length of the given buffer.
 * @param ulAccessRequested Access requested.
 *
 * @return pdTRUE if MPU region settings authorizes the requested access to the
 * given buffer, pdFALSE otherwise.
 */
PRIVILEGED_FUNCTION ਸਥਿਰ ਅਧਾਰ_Type_t prv_MPURegion_Authorizes_ਬਫਰ( ਅਚਲ xMPU_REGION_REGISTERS * xTaskMPURegion,
                                                                    ਅਚਲ uint32_t ul_ਬਫਰ_ਸ਼ੁਰੂ,
                                                                    ਅਚਲ uint32_t ul_ਬਫਰ_ਲੰਮਾਈ,
                                                                    ਅਚਲ uint32_t ulAccessRequested );

/**
 * @brief Determine the smallest MPU Region Size Encoding for the given MPU
 * region size.
 *
 * @ingroup MPU Control
 *
 * @param ulActualMPURegionSize MPU region size in bytes.
 *
 * @return The smallest MPU Region Size Encoding for the given MPU region size.
 */
PRIVILEGED_FUNCTION ਸਥਿਰ uint32_t prv_Get_MPURegion_ਮਾਪ_Encoding( uint32_t ul_Actual_MPURegion_ਮਾਪ );

/**
 * @brief Set up MPU.
 *
 * @ingroup MPU Control
 */
PRIVILEGED_FUNCTION ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_MPU( ਖਾਲੀ );

/* -------------------------- Exported Function Declarations -------------------------- */

/**
 * @brief Enter critical section.
 *
 * @ingroup Critical Section
 */
PRIVILEGED_FUNCTION ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ );

/**
 * @brief Exit critical section.
 *
 * @ingroup Critical Section
 */
PRIVILEGED_FUNCTION ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ );

/* ----------------------------------------------------------------------------------- */

/**
 * @brief Setup a FreeRTOS task's initial context.
 *
 * @ingroup Task Context
 *
 * @param pxTopOfStack Top of stack.
 * @param pxCode The task function.
 * @param pvParameters Argument passed to the task function.
 * @param xRunPrivileged Marks if the task is privileged.
 * @param xMPUSettings MPU settings of the task.
 *
 * @return Location where to restore the task's context from.
 */
/* PRIVILEGED_FUNCTION */
ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters,
                                     ਅਧਾਰ_Type_t x_ਲੜੀਵਾਰ_Privileged,
                                     xMPU_SETTINGS * xMPUSettings )
{
    /* Setup the initial context of the task. The context is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */
    UBaseType_t ul_ਸੂਚਕਾਂਕ = CONTEXT_ਮਾਪ - 1U;

    x_SYSTEM_CALL_ਢੇਰ_INFO * xSysCallInfo = ਨਿਰਾ;

    ਜੇ( x_ਲੜੀਵਾਰ_Privileged == pdTRUE )
    {
        xMPUSettings->ulTaskFlags |= ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG;
        /* Current Program Status Register (CPSR). */
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = SYS_ਬਹੁਲਕ;
    }
    ਨਹੀਂਤਾਂ
    {
        xMPUSettings->ulTaskFlags &= ( ~ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG );
        /* Current Program Status Register (CPSR). */
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = USER_ਬਹੁਲਕ;
    }

    ਜੇ( ( ( uint32_t ) px_ਕੋਡ & ਪੋਰਟ_THUMB_ਬਹੁਲਕ_ਪਤਾ ) != 0x0UL )
    {
        /* The task will cause the processor to start in THUMB state, set the
         * Thumb state bit in the CPSR. */
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] |= ਪੋਰਟ_THUMB_ਬਹੁਲਕ_ਦੋਆਧਾਰੀ_ਅੰਕ;
    }

    ul_ਸੂਚਕਾਂਕ--;

    xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) px_ਕੋਡ; /* PC. */
    ul_ਸੂਚਕਾਂਕ--;

    xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) ਪੋਰਟ_TASK_RETURN_ਪਤਾ; /* LR. */
    ul_ਸੂਚਕਾਂਕ--;

    xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) px_ਸਿਖਰ_ਦਾ_ਢੇਰ; /* SP. */
    ul_ਸੂਚਕਾਂਕ--;

    /* General Purpose Registers. */
    xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0x12121212; /* R12. */
    ul_ਸੂਚਕਾਂਕ--;
    xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0x11111111; /* R11. */
    ul_ਸੂਚਕਾਂਕ--;
    xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0x10101010; /* R10. */
    ul_ਸੂਚਕਾਂਕ--;
    xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0x09090909; /* R9. */
    ul_ਸੂਚਕਾਂਕ--;
    xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0x08080808; /* R8. */
    ul_ਸੂਚਕਾਂਕ--;
    xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0x07070707; /* R7. */
    ul_ਸੂਚਕਾਂਕ--;
    xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0x06060606; /* R6. */
    ul_ਸੂਚਕਾਂਕ--;
    xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0x05050505; /* R5. */
    ul_ਸੂਚਕਾਂਕ--;
    xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0x04040404; /* R4. */
    ul_ਸੂਚਕਾਂਕ--;
    xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0x03030303; /* R3. */
    ul_ਸੂਚਕਾਂਕ--;
    xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0x02020202; /* R2. */
    ul_ਸੂਚਕਾਂਕ--;
    xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0x01010101; /* R1. */
    ul_ਸੂਚਕਾਂਕ--;
    xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) pvParameters; /* R0. */
    ul_ਸੂਚਕਾਂਕ--;

    #ਜੇ( ਪੋਰਟ_ENABLE_FPU == 1 )
    {
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD0000015; /* S31. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD1500000; /* S30. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD0000014; /* S29. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD1400000; /* S28. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD0000013; /* S27. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD1300000; /* S26. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD0000012; /* S25. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD1200000; /* S24. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD0000011; /* S23. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD1100000; /* S22. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD0000010; /* S21. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD1000000; /* S20. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD0000009; /* S19. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD9000000; /* S18. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD0000008; /* S17. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD8000000; /* S16. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD0000007; /* S15. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD7000000; /* S14. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD0000006; /* S13. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD6000000; /* S12. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD0000005; /* S11. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD5000000; /* S10. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD0000004; /* S9. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD4000000; /* S8. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD0000003; /* S7. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD3000000; /* S6. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD0000002; /* S5. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD2000000; /* S4. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD0000001; /* S3. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD1000000; /* S2. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD0000000; /* S1. */
        ul_ਸੂਚਕਾਂਕ--;
        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0xD0000000; /* S0. */
        ul_ਸੂਚਕਾਂਕ--;

        xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ( ਢੇਰ_Type_t ) 0x00000000; /* FPSR. */
        ul_ਸੂਚਕਾਂਕ--;
    }
    #ਜੇ_ਅੰਤ /* portENABLE_FPU */

    /* The task will start with a critical nesting count of 0. */
    xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] = ਪੋਰਟ_NO_CRITICAL_NESTING;

    /* Ensure that the system call stack is double word aligned. */
    xSysCallInfo = &( xMPUSettings->x_System_Call_ਢੇਰ_Info );
    xSysCallInfo->pul_System_Call_ਢੇਰ_ਸੂਚਕ = &( xSysCallInfo->ul_System_Call_ਢੇਰ_ਬਫਰ[ config_SYSTEM_CALL_ਢੇਰ_ਮਾਪ - 1U ] );
    xSysCallInfo->pul_System_Call_ਢੇਰ_ਸੂਚਕ = ( uint32_t * ) ( ( ( uint32_t ) ( xSysCallInfo->pul_System_Call_ਢੇਰ_ਸੂਚਕ ) ) &
                                                               ( ( uint32_t ) ( ~( ਪੋਰਟ_BYTE_ALIGNMENT_ਨਕਾਬ ) ) ) );

    /* This is not NULL only for the duration of a system call. */
    xSysCallInfo->pul_Task_ਢੇਰ_ਸੂਚਕ = ਨਿਰਾ;

    /* Set the System Call to return to vPortSystemCallExit. */
    xSysCallInfo->pul_System_Call_Exit_ਪਤਾ = ( uint32_t * ) ( &v_ਪੋਰਟ_System_Call_Exit );

    /* Return the address where this task's context should be restored from. */
    ਵਾਪਸ &( xMPUSettings->ulContext[ ul_ਸੂਚਕਾਂਕ ] );
}

/* ----------------------------------------------------------------------------------- */

/**
 * @brief Store a FreeRTOS task's MPU settings in its TCB.
 *
 * @ingroup Task Context
 * @ingroup MPU Control
 *
 * @param xMPUSettings The MPU settings in TCB.
 * @param xRegions The updated MPU settings requested by the task.
 * @param pxBottomOfStack The base address of the task's Stack.
 * @param ulStackDepth The length of the task's stack.
 */
/* PRIVILEGED_FUNCTION */
ਖਾਲੀ v_ਪੋਰਟ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                ਅਚਲ ਬਣਤਰ x_ਸਮ੍ਰਿਤੀ_REGION * ਅਚਲ xRegions,
                                ਢੇਰ_Type_t * px_Bottom_ਦਾ_ਢੇਰ,
                                uint32_t ul_ਢੇਰ_ਡੂੰਘਾਈ )
{
    #ਜੇ defined( __ARMCC_VERSION )
        /* Declaration when these variable are defined in code instead of being
         * exported from linker scripts. */
        ਬਾਹਰੀ uint32_t * __SRAM_segment_start__;
        ਬਾਹਰੀ uint32_t * __SRAM_segment_end__;
    #ਨਹੀਂਤਾਂ
        /* Declaration when these variable are exported from linker scripts. */
        ਬਾਹਰੀ uint32_t __SRAM_segment_start__[];
        ਬਾਹਰੀ uint32_t __SRAM_segment_end__[];
    #ਜੇ_ਅੰਤ /* if defined( __ARMCC_VERSION ) */

    uint32_t ul_ਸੂਚਕਾਂਕ = 0x0;
    uint32_t ul_Region_ਲੰਮਾਈ;
    uint32_t ul_Region_ਲੰਮਾਈ_Encoded;
    uint32_t ul_Region_ਲੰਮਾਈ_Decoded;

    ਜੇ( xRegions == ਨਿਰਾ )
    {
        /* No MPU regions are specified so allow access to all of the RAM. */
        ul_Region_ਲੰਮਾਈ = ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__;
        ul_Region_ਲੰਮਾਈ_Encoded = prv_Get_MPURegion_ਮਾਪ_Encoding( ul_Region_ਲੰਮਾਈ );
        ul_Region_ਲੰਮਾਈ |= ਪੋਰਟ_MPU_REGION_ENABLE;

        /* MPU Settings is zero'd out in the TCB before this function is called.
         * We, therefore, do not need to explicitly zero out unused MPU regions
         * in xMPUSettings. */
        ul_ਸੂਚਕਾਂਕ = ਪੋਰਟ_ਢੇਰ_REGION;

        xMPUSettings->xRegion[ ul_ਸੂਚਕਾਂਕ ].ul_Region_ਅਧਾਰ_ਪਤਾ = ( uint32_t ) __SRAM_segment_start__;
        xMPUSettings->xRegion[ ul_ਸੂਚਕਾਂਕ ].ul_Region_ਮਾਪ = ( ul_Region_ਲੰਮਾਈ_Encoded |
                                                          ਪੋਰਟ_MPU_REGION_ENABLE );
        xMPUSettings->xRegion[ ul_ਸੂਚਕਾਂਕ ].ulRegionAttribute = ( ਪੋਰਟ_MPU_REGION_PRIV_RW_USER_RW_NOEXEC |
                                                               ਪੋਰਟ_MPU_REGION_ਸਾਧਾਰਨ_OIWTNOWA_SHARED );
    }
    ਨਹੀਂਤਾਂ
    {
        ਲਈ( ul_ਸੂਚਕਾਂਕ = 0UL; ul_ਸੂਚਕਾਂਕ < ਪੋਰਟ_ਅੰਕ_CONFIGURABLE_REGIONS; ul_ਸੂਚਕਾਂਕ++ )
        {
            /* If a length has been provided, the region is in use. */
            ਜੇ( ( xRegions[ ul_ਸੂਚਕਾਂਕ ] ).ul_ਲੰਮਾਈ_ਵਿੱਚ_ਬਾਈਟਾਂ > 0UL )
            {
                ul_Region_ਲੰਮਾਈ = xRegions[ ul_ਸੂਚਕਾਂਕ ].ul_ਲੰਮਾਈ_ਵਿੱਚ_ਬਾਈਟਾਂ;
                ul_Region_ਲੰਮਾਈ_Encoded = prv_Get_MPURegion_ਮਾਪ_Encoding( ul_Region_ਲੰਮਾਈ );

                /* MPU region base address must be aligned to the region size
                 * boundary. */
                ul_Region_ਲੰਮਾਈ_Decoded = 2UL << ( ul_Region_ਲੰਮਾਈ_Encoded >> 1UL );
                configASSERT( ( ( ( uint32_t ) xRegions[ ul_ਸੂਚਕਾਂਕ ].pv_ਅਧਾਰ_ਪਤਾ ) % ( ul_Region_ਲੰਮਾਈ_Decoded ) ) == 0UL );

                xMPUSettings->xRegion[ ul_ਸੂਚਕਾਂਕ ].ul_Region_ਅਧਾਰ_ਪਤਾ = ( uint32_t ) xRegions[ ul_ਸੂਚਕਾਂਕ ].pv_ਅਧਾਰ_ਪਤਾ;
                xMPUSettings->xRegion[ ul_ਸੂਚਕਾਂਕ ].ul_Region_ਮਾਪ = ( ul_Region_ਲੰਮਾਈ_Encoded |
                                                                  ਪੋਰਟ_MPU_REGION_ENABLE );
                xMPUSettings->xRegion[ ul_ਸੂਚਕਾਂਕ ].ulRegionAttribute = xRegions[ ul_ਸੂਚਕਾਂਕ ].ulParameters;
            }
            ਨਹੀਂਤਾਂ
            {
                xMPUSettings->xRegion[ ul_ਸੂਚਕਾਂਕ ].ul_Region_ਅਧਾਰ_ਪਤਾ = 0x0UL;
                xMPUSettings->xRegion[ ul_ਸੂਚਕਾਂਕ ].ul_Region_ਮਾਪ = 0x0UL;
                xMPUSettings->xRegion[ ul_ਸੂਚਕਾਂਕ ].ulRegionAttribute = 0x0UL;
            }
        }

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid. At all other
         * times the stack parameters will not be valid and it is assumed that the
         * stack region has already been configured. */
        ਜੇ( ul_ਢੇਰ_ਡੂੰਘਾਈ != 0x0UL )
        {
            ul_Region_ਲੰਮਾਈ_Encoded = prv_Get_MPURegion_ਮਾਪ_Encoding( ul_ਢੇਰ_ਡੂੰਘਾਈ * ( uint32_t ) ਆਕਾਰ( ਢੇਰ_Type_t ) );

            /* MPU region base address must be aligned to the region size
             * boundary. */
            ul_Region_ਲੰਮਾਈ_Decoded = 2UL << ( ul_Region_ਲੰਮਾਈ_Encoded >> 1UL );
            configASSERT( ( ( uint32_t ) px_Bottom_ਦਾ_ਢੇਰ % ( ul_Region_ਲੰਮਾਈ_Decoded ) ) == 0U );

            ul_ਸੂਚਕਾਂਕ = ਪੋਰਟ_ਢੇਰ_REGION;
            xMPUSettings->xRegion[ ul_ਸੂਚਕਾਂਕ ].ul_Region_ਅਧਾਰ_ਪਤਾ = ( uint32_t ) px_Bottom_ਦਾ_ਢੇਰ;
            xMPUSettings->xRegion[ ul_ਸੂਚਕਾਂਕ ].ul_Region_ਮਾਪ = ( ul_Region_ਲੰਮਾਈ_Encoded |
                                                              ਪੋਰਟ_MPU_REGION_ENABLE );
            xMPUSettings->xRegion[ ul_ਸੂਚਕਾਂਕ ].ulRegionAttribute = ( ਪੋਰਟ_MPU_REGION_PRIV_RW_USER_RW_NOEXEC |
                                                                   ਪੋਰਟ_MPU_REGION_ਸਾਧਾਰਨ_OIWTNOWA_SHARED );
        }
    }
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Task_Privileged( ਖਾਲੀ )
{
    ਅਧਾਰ_Type_t xTaskIsPrivileged = pdFALSE;

    /* Calling task's MPU settings. */
    ਅਚਲ xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ਨਿਰਾ );

    ਜੇ( ( xTaskMpuSettings->ulTaskFlags & ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG ) == ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG )
    {
        xTaskIsPrivileged = pdTRUE;
    }

    ਵਾਪਸ xTaskIsPrivileged;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    /* Start the timer that generates the tick ISR. */
    config_ਤਿਆਰੀ_TICK_ਰੁਕਾਵਟ();

    /* Configure MPU regions that are common to all tasks. */
    prv_ਤਿਆਰੀ_MPU();

    prv_ਪੋਰਟ_Scheduler_Running = pdTRUE;

    /* Load the context of the first task. */
    v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value. prvTaskExitError() is referenced to prevent a compiler
     * warning about it being defined but not referenced in the case that the user
     * defines their own exit address. */
    ( ਖਾਲੀ ) prvTaskExitError();
    ਵਾਪਸ pdFALSE;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ਸਥਿਰ uint32_t prv_Get_MPURegion_ਮਾਪ_Encoding( uint32_t ul_Actual_MPURegion_ਮਾਪ )
{
    uint32_t ul_Region_ਮਾਪ, ul_Return_ਮੁੱਲ = 4U;

    /* 32 bytes is the smallest valid region for Cortex R4 and R5 CPUs. */
    ਲਈ( ul_Region_ਮਾਪ = 0x20UL; ul_Return_ਮੁੱਲ < 0x1FUL; ( ul_Region_ਮਾਪ <<= 1UL ) )
    {
        ਜੇ( ul_Actual_MPURegion_ਮਾਪ <= ul_Region_ਮਾਪ )
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
    ਵਾਪਸ ul_Return_ਮੁੱਲ << 1UL;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_MPU( ਖਾਲੀ )
{
#ਜੇ defined( __ARMCC_VERSION )
    /* Declaration when these variable are defined in code. */
    /* Sections used for FLASH. */
    ਬਾਹਰੀ uint32_t * __FLASH_segment_start__;
    ਬਾਹਰੀ uint32_t * __FLASH_segment_end__;
    ਬਾਹਰੀ uint32_t * __privileged_functions_start__;
    ਬਾਹਰੀ uint32_t * __privileged_functions_end__;

    /* Sections used for RAM. */
    ਬਾਹਰੀ uint32_t * __SRAM_segment_start__;
    ਬਾਹਰੀ uint32_t * __SRAM_segment_end__;
    ਬਾਹਰੀ uint32_t * __privileged_data_start__;
    ਬਾਹਰੀ uint32_t * __privileged_data_end__;
#ਨਹੀਂਤਾਂ
    /* Declaration when these variable are exported from linker scripts. */
    /* Sections used for FLASH. */
    ਬਾਹਰੀ uint32_t __FLASH_segment_start__[];
    ਬਾਹਰੀ uint32_t __FLASH_segment_end__[];
    ਬਾਹਰੀ uint32_t __privileged_functions_start__[];
    ਬਾਹਰੀ uint32_t __privileged_functions_end__[];

    /* Sections used for RAM. */
    ਬਾਹਰੀ uint32_t __SRAM_segment_start__[];
    ਬਾਹਰੀ uint32_t __SRAM_segment_end__[];
    ਬਾਹਰੀ uint32_t __privileged_data_start__[];
    ਬਾਹਰੀ uint32_t __privileged_data_end__[];
#ਜੇ_ਅੰਤ /* if defined( __ARMCC_VERSION ) */

    uint32_t ul_Region_ਲੰਮਾਈ;
    uint32_t ul_Region_ਲੰਮਾਈ_Encoded;

    /* Disable the MPU before programming it. */
    vMPUDisable();

    /* Priv: RX, Unpriv: RX for entire Flash. */
    ul_Region_ਲੰਮਾਈ = ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__;
    ul_Region_ਲੰਮਾਈ_Encoded = prv_Get_MPURegion_ਮਾਪ_Encoding( ul_Region_ਲੰਮਾਈ );
    vMPUSetRegion( ਪੋਰਟ_UNPRIVILEGED_FLASH_REGION,
                   ( uint32_t ) __FLASH_segment_start__,
                   ( ul_Region_ਲੰਮਾਈ_Encoded | ਪੋਰਟ_MPU_REGION_ENABLE ),
                   ( ਪੋਰਟ_MPU_REGION_PRIV_RO_USER_RO_EXEC |
                     ਪੋਰਟ_MPU_REGION_ਸਾਧਾਰਨ_OIWTNOWA_SHARED ) );

    /* Priv: RX, Unpriv: No access for privileged functions. */
    ul_Region_ਲੰਮਾਈ = ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__;
    ul_Region_ਲੰਮਾਈ_Encoded = prv_Get_MPURegion_ਮਾਪ_Encoding( ul_Region_ਲੰਮਾਈ );
    vMPUSetRegion( ਪੋਰਟ_PRIVILEGED_FLASH_REGION,
                   ( uint32_t ) __privileged_functions_start__,
                   ( ul_Region_ਲੰਮਾਈ_Encoded | ਪੋਰਟ_MPU_REGION_ENABLE ),
                   ( ਪੋਰਟ_MPU_REGION_PRIV_RO_USER_NA_EXEC |
                     ਪੋਰਟ_MPU_REGION_ਸਾਧਾਰਨ_OIWTNOWA_SHARED ) );

    /* Priv: RW, Unpriv: No Access for privileged data. */
    ul_Region_ਲੰਮਾਈ = ( uint32_t ) __privileged_data_end__ - ( uint32_t ) __privileged_data_start__;
    ul_Region_ਲੰਮਾਈ_Encoded = prv_Get_MPURegion_ਮਾਪ_Encoding( ul_Region_ਲੰਮਾਈ );
    vMPUSetRegion( ਪੋਰਟ_PRIVILEGED_RAM_REGION,
                   ( uint32_t ) __privileged_data_start__,
                   ( ul_Region_ਲੰਮਾਈ_Encoded | ਪੋਰਟ_MPU_REGION_ENABLE ),
                   ( ਪੋਰਟ_MPU_REGION_PRIV_RW_USER_NA_NOEXEC |
                     ਪੋਰਟ_MPU_REGION_PRIV_RW_USER_NA_NOEXEC ) );

    /* Enable the MPU background region - it allows privileged operating modes
     * access to unmapped regions of memory without generating a fault. */
    vMPUEnableBackgroundRegion();

    /* After setting default regions, enable the MPU. */
    vMPUEnable();
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ਸਥਿਰ ਅਧਾਰ_Type_t prv_MPURegion_Authorizes_ਬਫਰ( ਅਚਲ xMPU_REGION_REGISTERS * xTaskMPURegion,
                                                ਅਚਲ uint32_t ul_ਬਫਰ_ਸ਼ੁਰੂ,
                                                ਅਚਲ uint32_t ul_ਬਫਰ_ਲੰਮਾਈ,
                                                ਅਚਲ uint32_t ulAccessRequested )
{
    ਅਧਾਰ_Type_t xAccessGranted = pdFALSE;
    uint32_t ul_ਬਫਰ_ਸਿਰਾ;
    uint32_t ul_MPURegion_ਲੰਮਾਈ;
    uint32_t ul_MPURegion_ਸ਼ੁਰੂ;
    uint32_t ul_MPURegion_ਸਿਰਾ;
    uint32_t ulMPURegionAccessPermissions;

    ਜੇ( ਪੋਰਟ_ਜੋੜੋ_UINT32_WILL_ਉਛਾਲ( ul_ਬਫਰ_ਸ਼ੁਰੂ, ( ul_ਬਫਰ_ਲੰਮਾਈ - 1UL ) ) == pdFALSE )
    {
        ul_ਬਫਰ_ਸਿਰਾ = ul_ਬਫਰ_ਸ਼ੁਰੂ + ul_ਬਫਰ_ਲੰਮਾਈ - 1UL;
        ul_MPURegion_ਲੰਮਾਈ = 2UL << ( xTaskMPURegion->ul_Region_ਮਾਪ >> 1UL );
        ul_MPURegion_ਸ਼ੁਰੂ = xTaskMPURegion->ul_Region_ਅਧਾਰ_ਪਤਾ;
        ul_MPURegion_ਸਿਰਾ = xTaskMPURegion->ul_Region_ਅਧਾਰ_ਪਤਾ + ul_MPURegion_ਲੰਮਾਈ - 1UL;

        ਜੇ( ( ul_ਬਫਰ_ਸ਼ੁਰੂ >= ul_MPURegion_ਸ਼ੁਰੂ ) &&
            ( ul_ਬਫਰ_ਸਿਰਾ <= ul_MPURegion_ਸਿਰਾ ) &&
            ( ul_ਬਫਰ_ਸ਼ੁਰੂ <= ul_ਬਫਰ_ਸਿਰਾ ) )
        {
            ulMPURegionAccessPermissions = xTaskMPURegion->ulRegionAttribute & ਪੋਰਟ_MPU_REGION_AP_BITMASK;

            ਜੇ( ulAccessRequested == tskMPU_READ_PERMISSION ) /* RO. */
            {
                ਜੇ( ( ulMPURegionAccessPermissions == ਪੋਰਟ_MPU_REGION_PRIV_RW_USER_RO ) ||
                    ( ulMPURegionAccessPermissions == ਪੋਰਟ_MPU_REGION_PRIV_RO_USER_RO ) ||
                    ( ulMPURegionAccessPermissions == ਪੋਰਟ_MPU_REGION_PRIV_RW_USER_RW ) )

                {
                    xAccessGranted = pdTRUE;
                }
            }
            ਨਹੀਂਤਾਂ ਜੇ( ( ulAccessRequested & tskMPU_WRITE_PERMISSION ) != 0UL ) /* W or RW. */
            {
                ਜੇ( ulMPURegionAccessPermissions == ਪੋਰਟ_MPU_REGION_PRIV_RW_USER_RW )
                {
                    xAccessGranted = pdTRUE;
                }
            }
        }
    }

    ਵਾਪਸ xAccessGranted;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( ਅਚਲ ਖਾਲੀ * pv_ਬਫਰ,
                                            size_t x_ਬਫਰ_ਲੰਮਾਈ,
                                            uint32_t ulAccessRequested )
{
    ਅਧਾਰ_Type_t xAccessGranted = pdFALSE;
    uint32_t ul_Region_ਸੂਚਕਾਂਕ;
    xMPU_SETTINGS * xTaskMPUSettings = ਨਿਰਾ;

    ਜੇ( prv_ਪੋਰਟ_Scheduler_Running == pdFALSE )
    {
        /* Grant access to all the memory before the scheduler is started. It is
         * necessary because there is no task running yet and therefore, we
         * cannot use the permissions of any task. */
        xAccessGranted = pdTRUE;
    }
    ਨਹੀਂਤਾਂ
    {
        /* Calling task's MPU settings. */
        xTaskMPUSettings = xTaskGetMPUSettings( ਨਿਰਾ );

        ਜੇ( ( xTaskMPUSettings->ulTaskFlags & ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG ) == ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG )
        {
            /* Privileged tasks have access to all the memory. */
            xAccessGranted = pdTRUE;
        }
        ਨਹੀਂਤਾਂ
        {
            ਲਈ( ul_Region_ਸੂਚਕਾਂਕ = 0x0UL; ul_Region_ਸੂਚਕਾਂਕ < ਪੋਰਟ_ਕੁੱਲ_ਅੰਕ_REGIONS_ਵਿੱਚ_TCB; ul_Region_ਸੂਚਕਾਂਕ++ )
            {
                xAccessGranted = prv_MPURegion_Authorizes_ਬਫਰ( &( xTaskMPUSettings->xRegion[ ul_Region_ਸੂਚਕਾਂਕ ] ),
                                                               ( uint32_t ) pv_ਬਫਰ,
                                                               ( uint32_t ) x_ਬਫਰ_ਲੰਮਾਈ,
                                                               ulAccessRequested );

                ਜੇ( xAccessGranted == pdTRUE )
                {
                    ਰੋਕੋ;
                }
            }
        }
    }

    ਵਾਪਸ xAccessGranted;
}

/* ----------------------------------------------------------------------------------- */

#ਜੇ( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( int32_t l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object )
{
    uint32_t ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ, ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ;
    ਅਧਾਰ_Type_t xAccessGranted = pdFALSE;
    ਅਚਲ xMPU_SETTINGS * xTaskMpuSettings;

    ਜੇ( prv_ਪੋਰਟ_Scheduler_Running == pdFALSE )
    {
        /* Grant access to all the kernel objects before the scheduler
         * is started. It is necessary because there is no task running
         * yet and therefore, we cannot use the permissions of any
         * task. */
        xAccessGranted = pdTRUE;
    }
    ਨਹੀਂਤਾਂ
    {
        /* Calling task's MPU settings. */
        xTaskMpuSettings = xTaskGetMPUSettings( ਨਿਰਾ );

        ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object
                                          / ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );
        ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object
                                        % ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );

        ਜੇ( ( xTaskMpuSettings->ulTaskFlags & ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG ) == ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        ਨਹੀਂਤਾਂ
        {
            ਜੇ( ( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ ] ) &
                  ( 1U << ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ ) ) != 0UL )
            {
                xAccessGranted = pdTRUE;
            }
        }
    }

    ਵਾਪਸ xAccessGranted;
}

#ਨਹੀਂਤਾਂ

/* PRIVILEGED_FUNCTION */
ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( int32_t l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object )
{
    ( ਖਾਲੀ ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object;

    /* If Access Control List feature is not used, all the tasks have
     * access to all the kernel objects. */
    ਵਾਪਸ pdTRUE;
}

#ਜੇ_ਅੰਤ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

#ਜੇ( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
ਖਾਲੀ v_ਪੋਰਟ_Grant_Access_ਮੰਜ਼ਿਲ_Kernel_Object( TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle,
                                     int32_t l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object )
{
    uint32_t ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ, ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ;
    xMPU_SETTINGS * xTaskMpuSettings;

    ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object
                                      / ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );
    ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object
                                    % ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );

    xTaskMpuSettings = xTaskGetMPUSettings( x_ਅੰਦਰੂਨੀ_Task_Handle );

    xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ ] |= ( 1U << ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ );
}

#ਜੇ_ਅੰਤ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

#ਜੇ( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
ਖਾਲੀ v_ਪੋਰਟ_Revoke_Access_ਮੰਜ਼ਿਲ_Kernel_Object( TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle,
                                      int32_t l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object )
{
    uint32_t ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ, ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ;
    xMPU_SETTINGS * xTaskMpuSettings;

    ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object
                                      / ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );
    ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object
                                    % ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );

    xTaskMpuSettings = xTaskGetMPUSettings( x_ਅੰਦਰੂਨੀ_Task_Handle );

    xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ ] &= ~( 1U << ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ );
}

#ਜੇ_ਅੰਤ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

ਖਾਲੀ prvTaskExitError( ਖਾਲੀ )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ul_ਪੋਰਟ_ਰੁਕਾਵਟ_Nesting == ~0UL );

    ਲਈ( ;; )
    {
    }
}

/* ----------------------------------------------------------------------------------- */

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    prv_ਪੋਰਟ_Scheduler_Running = pdFALSE;

    /* Not implemented in this port. Artificially force an assert. */
    configASSERT( prv_ਪੋਰਟ_Scheduler_Running == pdTRUE );
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ )
{
    ਪੋਰਟ_DISABLE_INTERRUPTS();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert
     * if the critical nesting count is 1 to protect against recursive calls if
     * the assert function also uses a critical section. */
    ਜੇ( ulCriticalNesting == 1 )
    {
        configASSERT( ul_ਪੋਰਟ_ਰੁਕਾਵਟ_Nesting == 0 );
    }
}
/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ )
{
    ਜੇ( ulCriticalNesting > ਪੋਰਟ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        ਜੇ( ulCriticalNesting == ਪੋਰਟ_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            ਪੋਰਟ_ENABLE_INTERRUPTS();
        }
    }
}
/* ----------------------------------------------------------------------------------- */
