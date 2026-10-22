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
#ಅನ್ತರ್ಭಾವ <stdint.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers. That should only be done when
 * task.h is included from an application file. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MPU_WRAPPERS_INCLUDED_FROM_API_FILE
    #ವ್ಯಾಖ್ಯಾನಿಸು MPU_WRAPPERS_INCLUDED_FROM_API_FILE
#ಆದರೆ_ಅಂತ್ಯ /* MPU_WRAPPERS_INCLUDED_FROM_API_FILE */

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "portmacro.h"
#ಅನ್ತರ್ಭಾವ "task.h"
#ಅನ್ತರ್ಭಾವ "mpu_syscall_numbers.h"

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Max value that fits in a uint32_t type. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೂಡಿಸು_UINT32_WILL_ಅತಿಪ್ರವಾಹ( a, b )    ( ( a ) > ( ಪೋರ್ಟ್_UINT32_MAX - ( b ) ) )
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
PRIVILEGED_ದತ್ತಾಂಶ ಅಸ್ಥಿರ UBaseType_t ulCriticalNesting = 0xFFFF;

/**
 * @brief Set to 1 to pend a context switch from an ISR.
 *
 * @ingroup Interrupt Management
 */
PRIVILEGED_ದತ್ತಾಂಶ ಅಸ್ಥಿರ UBaseType_t ul_ಪೋರ್ಟ್_Yield_Required = pdFALSE;

/**
 * @brief Interrupt nesting depth, used to count the number of interrupts to unwind.
 *
 * @ingroup Interrupt Management
 */
PRIVILEGED_ದತ್ತಾಂಶ ಅಸ್ಥಿರ UBaseType_t ul_ಪೋರ್ಟ್_ಅಡಚಣೆ_Nesting = 0UL;

/**
 * @brief Variable to track whether or not the scheduler has been started.
 *
 * @ingroup Scheduler
 *
 * This is the port specific version of the xSchedulerRunning in tasks.c.
 */
PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ ತಳ_Type_t prv_ಪೋರ್ಟ್_Scheduler_Running = pdFALSE;

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
PRIVILEGED_FUNCTION ಸ್ಥಿರ ತಳ_Type_t prv_MPURegion_Authorizes_ಬಫರ್( ಸ್ಥಿರಾಂಕ xMPU_REGION_REGISTERS * xTaskMPURegion,
                                                                    ಸ್ಥಿರಾಂಕ uint32_t ul_ಬಫರ್_ಆರಂಭ,
                                                                    ಸ್ಥಿರಾಂಕ uint32_t ul_ಬಫರ್_ಉದ್ದಳತೆ,
                                                                    ಸ್ಥಿರಾಂಕ uint32_t ulAccessRequested );

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
PRIVILEGED_FUNCTION ಸ್ಥಿರ uint32_t prv_Get_MPURegion_ಗಾತ್ರ_Encoding( uint32_t ul_Actual_MPURegion_ಗಾತ್ರ );

/**
 * @brief Set up MPU.
 *
 * @ingroup MPU Control
 */
PRIVILEGED_FUNCTION ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_MPU( ಶೂನ್ಯ );

/* -------------------------- Exported Function Declarations -------------------------- */

/**
 * @brief Enter critical section.
 *
 * @ingroup Critical Section
 */
PRIVILEGED_FUNCTION ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ );

/**
 * @brief Exit critical section.
 *
 * @ingroup Critical Section
 */
PRIVILEGED_FUNCTION ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ );

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
ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters,
                                     ತಳ_Type_t x_ಸತತ_Privileged,
                                     xMPU_SETTINGS * xMPUSettings )
{
    /* Setup the initial context of the task. The context is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */
    UBaseType_t ul_ಸೂಚ್ಯಂಕ = CONTEXT_ಗಾತ್ರ - 1U;

    x_SYSTEM_CALL_ರಾಶಿ_INFO * xSysCallInfo = ಖಾಲಿ;

    ಆದರೆ( x_ಸತತ_Privileged == pdTRUE )
    {
        xMPUSettings->ulTaskFlags |= ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG;
        /* Current Program Status Register (CPSR). */
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = SYS_ಬಹುಲಕ;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        xMPUSettings->ulTaskFlags &= ( ~ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG );
        /* Current Program Status Register (CPSR). */
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = USER_ಬಹುಲಕ;
    }

    ಆದರೆ( ( ( uint32_t ) px_ಸಂಕೇತ & ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ವಿಳಾಸ ) != 0x0UL )
    {
        /* The task will cause the processor to start in THUMB state, set the
         * Thumb state bit in the CPSR. */
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] |= ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ಬಿಟ್;
    }

    ul_ಸೂಚ್ಯಂಕ--;

    xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ; /* PC. */
    ul_ಸೂಚ್ಯಂಕ--;

    xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ; /* LR. */
    ul_ಸೂಚ್ಯಂಕ--;

    xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) px_ತುದಿ_ದ_ರಾಶಿ; /* SP. */
    ul_ಸೂಚ್ಯಂಕ--;

    /* General Purpose Registers. */
    xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0x12121212; /* R12. */
    ul_ಸೂಚ್ಯಂಕ--;
    xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0x11111111; /* R11. */
    ul_ಸೂಚ್ಯಂಕ--;
    xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0x10101010; /* R10. */
    ul_ಸೂಚ್ಯಂಕ--;
    xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0x09090909; /* R9. */
    ul_ಸೂಚ್ಯಂಕ--;
    xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0x08080808; /* R8. */
    ul_ಸೂಚ್ಯಂಕ--;
    xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0x07070707; /* R7. */
    ul_ಸೂಚ್ಯಂಕ--;
    xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0x06060606; /* R6. */
    ul_ಸೂಚ್ಯಂಕ--;
    xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0x05050505; /* R5. */
    ul_ಸೂಚ್ಯಂಕ--;
    xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0x04040404; /* R4. */
    ul_ಸೂಚ್ಯಂಕ--;
    xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0x03030303; /* R3. */
    ul_ಸೂಚ್ಯಂಕ--;
    xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0x02020202; /* R2. */
    ul_ಸೂಚ್ಯಂಕ--;
    xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0x01010101; /* R1. */
    ul_ಸೂಚ್ಯಂಕ--;
    xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) pvParameters; /* R0. */
    ul_ಸೂಚ್ಯಂಕ--;

    #ಆದರೆ( ಪೋರ್ಟ್_ENABLE_FPU == 1 )
    {
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD0000015; /* S31. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD1500000; /* S30. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD0000014; /* S29. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD1400000; /* S28. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD0000013; /* S27. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD1300000; /* S26. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD0000012; /* S25. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD1200000; /* S24. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD0000011; /* S23. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD1100000; /* S22. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD0000010; /* S21. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD1000000; /* S20. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD0000009; /* S19. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD9000000; /* S18. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD0000008; /* S17. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD8000000; /* S16. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD0000007; /* S15. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD7000000; /* S14. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD0000006; /* S13. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD6000000; /* S12. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD0000005; /* S11. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD5000000; /* S10. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD0000004; /* S9. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD4000000; /* S8. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD0000003; /* S7. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD3000000; /* S6. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD0000002; /* S5. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD2000000; /* S4. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD0000001; /* S3. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD1000000; /* S2. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD0000000; /* S1. */
        ul_ಸೂಚ್ಯಂಕ--;
        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0xD0000000; /* S0. */
        ul_ಸೂಚ್ಯಂಕ--;

        xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ( ರಾಶಿ_Type_t ) 0x00000000; /* FPSR. */
        ul_ಸೂಚ್ಯಂಕ--;
    }
    #ಆದರೆ_ಅಂತ್ಯ /* portENABLE_FPU */

    /* The task will start with a critical nesting count of 0. */
    xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] = ಪೋರ್ಟ್_NO_CRITICAL_NESTING;

    /* Ensure that the system call stack is double word aligned. */
    xSysCallInfo = &( xMPUSettings->x_System_Call_ರಾಶಿ_Info );
    xSysCallInfo->pul_System_Call_ರಾಶಿ_ಸೂಚಕ = &( xSysCallInfo->ul_System_Call_ರಾಶಿ_ಬಫರ್[ config_SYSTEM_CALL_ರಾಶಿ_ಗಾತ್ರ - 1U ] );
    xSysCallInfo->pul_System_Call_ರಾಶಿ_ಸೂಚಕ = ( uint32_t * ) ( ( ( uint32_t ) ( xSysCallInfo->pul_System_Call_ರಾಶಿ_ಸೂಚಕ ) ) &
                                                               ( ( uint32_t ) ( ~( ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ ) ) ) );

    /* This is not NULL only for the duration of a system call. */
    xSysCallInfo->pul_Task_ರಾಶಿ_ಸೂಚಕ = ಖಾಲಿ;

    /* Set the System Call to return to vPortSystemCallExit. */
    xSysCallInfo->pul_System_Call_Exit_ವಿಳಾಸ = ( uint32_t * ) ( &v_ಪೋರ್ಟ್_System_Call_Exit );

    /* Return the address where this task's context should be restored from. */
    ಹಿಂತಿರುಗಿ &( xMPUSettings->ulContext[ ul_ಸೂಚ್ಯಂಕ ] );
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
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                ಸ್ಥಿರಾಂಕ ರಚನೆ x_ಸ್ಮರಣೆ_REGION * ಸ್ಥಿರಾಂಕ xRegions,
                                ರಾಶಿ_Type_t * px_Bottom_ದ_ರಾಶಿ,
                                uint32_t ul_ರಾಶಿ_ಆಳ )
{
    #ಆದರೆ defined( __ARMCC_VERSION )
        /* Declaration when these variable are defined in code instead of being
         * exported from linker scripts. */
        ಬಾಹ್ಯ uint32_t * __SRAM_segment_start__;
        ಬಾಹ್ಯ uint32_t * __SRAM_segment_end__;
    #ಇಲ್ಲದಿದ್ದರೆ
        /* Declaration when these variable are exported from linker scripts. */
        ಬಾಹ್ಯ uint32_t __SRAM_segment_start__[];
        ಬಾಹ್ಯ uint32_t __SRAM_segment_end__[];
    #ಆದರೆ_ಅಂತ್ಯ /* if defined( __ARMCC_VERSION ) */

    uint32_t ul_ಸೂಚ್ಯಂಕ = 0x0;
    uint32_t ul_Region_ಉದ್ದಳತೆ;
    uint32_t ul_Region_ಉದ್ದಳತೆ_Encoded;
    uint32_t ul_Region_ಉದ್ದಳತೆ_Decoded;

    ಆದರೆ( xRegions == ಖಾಲಿ )
    {
        /* No MPU regions are specified so allow access to all of the RAM. */
        ul_Region_ಉದ್ದಳತೆ = ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__;
        ul_Region_ಉದ್ದಳತೆ_Encoded = prv_Get_MPURegion_ಗಾತ್ರ_Encoding( ul_Region_ಉದ್ದಳತೆ );
        ul_Region_ಉದ್ದಳತೆ |= ಪೋರ್ಟ್_MPU_REGION_ENABLE;

        /* MPU Settings is zero'd out in the TCB before this function is called.
         * We, therefore, do not need to explicitly zero out unused MPU regions
         * in xMPUSettings. */
        ul_ಸೂಚ್ಯಂಕ = ಪೋರ್ಟ್_ರಾಶಿ_REGION;

        xMPUSettings->xRegion[ ul_ಸೂಚ್ಯಂಕ ].ul_Region_ತಳ_ವಿಳಾಸ = ( uint32_t ) __SRAM_segment_start__;
        xMPUSettings->xRegion[ ul_ಸೂಚ್ಯಂಕ ].ul_Region_ಗಾತ್ರ = ( ul_Region_ಉದ್ದಳತೆ_Encoded |
                                                          ಪೋರ್ಟ್_MPU_REGION_ENABLE );
        xMPUSettings->xRegion[ ul_ಸೂಚ್ಯಂಕ ].ulRegionAttribute = ( ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_RW_NOEXEC |
                                                               ಪೋರ್ಟ್_MPU_REGION_ಸಾಮಾನ್ಯ_OIWTNOWA_SHARED );
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        ಗಾಗಿ( ul_ಸೂಚ್ಯಂಕ = 0UL; ul_ಸೂಚ್ಯಂಕ < ಪೋರ್ಟ್_ಅಂಕೆ_CONFIGURABLE_REGIONS; ul_ಸೂಚ್ಯಂಕ++ )
        {
            /* If a length has been provided, the region is in use. */
            ಆದರೆ( ( xRegions[ ul_ಸೂಚ್ಯಂಕ ] ).ul_ಉದ್ದಳತೆ_ಒಳ_ಬೈಟುಗಳು > 0UL )
            {
                ul_Region_ಉದ್ದಳತೆ = xRegions[ ul_ಸೂಚ್ಯಂಕ ].ul_ಉದ್ದಳತೆ_ಒಳ_ಬೈಟುಗಳು;
                ul_Region_ಉದ್ದಳತೆ_Encoded = prv_Get_MPURegion_ಗಾತ್ರ_Encoding( ul_Region_ಉದ್ದಳತೆ );

                /* MPU region base address must be aligned to the region size
                 * boundary. */
                ul_Region_ಉದ್ದಳತೆ_Decoded = 2UL << ( ul_Region_ಉದ್ದಳತೆ_Encoded >> 1UL );
                configASSERT( ( ( ( uint32_t ) xRegions[ ul_ಸೂಚ್ಯಂಕ ].pv_ತಳ_ವಿಳಾಸ ) % ( ul_Region_ಉದ್ದಳತೆ_Decoded ) ) == 0UL );

                xMPUSettings->xRegion[ ul_ಸೂಚ್ಯಂಕ ].ul_Region_ತಳ_ವಿಳಾಸ = ( uint32_t ) xRegions[ ul_ಸೂಚ್ಯಂಕ ].pv_ತಳ_ವಿಳಾಸ;
                xMPUSettings->xRegion[ ul_ಸೂಚ್ಯಂಕ ].ul_Region_ಗಾತ್ರ = ( ul_Region_ಉದ್ದಳತೆ_Encoded |
                                                                  ಪೋರ್ಟ್_MPU_REGION_ENABLE );
                xMPUSettings->xRegion[ ul_ಸೂಚ್ಯಂಕ ].ulRegionAttribute = xRegions[ ul_ಸೂಚ್ಯಂಕ ].ulParameters;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xMPUSettings->xRegion[ ul_ಸೂಚ್ಯಂಕ ].ul_Region_ತಳ_ವಿಳಾಸ = 0x0UL;
                xMPUSettings->xRegion[ ul_ಸೂಚ್ಯಂಕ ].ul_Region_ಗಾತ್ರ = 0x0UL;
                xMPUSettings->xRegion[ ul_ಸೂಚ್ಯಂಕ ].ulRegionAttribute = 0x0UL;
            }
        }

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid. At all other
         * times the stack parameters will not be valid and it is assumed that the
         * stack region has already been configured. */
        ಆದರೆ( ul_ರಾಶಿ_ಆಳ != 0x0UL )
        {
            ul_Region_ಉದ್ದಳತೆ_Encoded = prv_Get_MPURegion_ಗಾತ್ರ_Encoding( ul_ರಾಶಿ_ಆಳ * ( uint32_t ) ಗಾತ್ರ( ರಾಶಿ_Type_t ) );

            /* MPU region base address must be aligned to the region size
             * boundary. */
            ul_Region_ಉದ್ದಳತೆ_Decoded = 2UL << ( ul_Region_ಉದ್ದಳತೆ_Encoded >> 1UL );
            configASSERT( ( ( uint32_t ) px_Bottom_ದ_ರಾಶಿ % ( ul_Region_ಉದ್ದಳತೆ_Decoded ) ) == 0U );

            ul_ಸೂಚ್ಯಂಕ = ಪೋರ್ಟ್_ರಾಶಿ_REGION;
            xMPUSettings->xRegion[ ul_ಸೂಚ್ಯಂಕ ].ul_Region_ತಳ_ವಿಳಾಸ = ( uint32_t ) px_Bottom_ದ_ರಾಶಿ;
            xMPUSettings->xRegion[ ul_ಸೂಚ್ಯಂಕ ].ul_Region_ಗಾತ್ರ = ( ul_Region_ಉದ್ದಳತೆ_Encoded |
                                                              ಪೋರ್ಟ್_MPU_REGION_ENABLE );
            xMPUSettings->xRegion[ ul_ಸೂಚ್ಯಂಕ ].ulRegionAttribute = ( ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_RW_NOEXEC |
                                                                   ಪೋರ್ಟ್_MPU_REGION_ಸಾಮಾನ್ಯ_OIWTNOWA_SHARED );
        }
    }
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Task_Privileged( ಶೂನ್ಯ )
{
    ತಳ_Type_t xTaskIsPrivileged = pdFALSE;

    /* Calling task's MPU settings. */
    ಸ್ಥಿರಾಂಕ xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ಖಾಲಿ );

    ಆದರೆ( ( xTaskMpuSettings->ulTaskFlags & ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG ) == ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG )
    {
        xTaskIsPrivileged = pdTRUE;
    }

    ಹಿಂತಿರುಗಿ xTaskIsPrivileged;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    /* Start the timer that generates the tick ISR. */
    config_ಸಿದ್ಧತೆ_TICK_ಅಡಚಣೆ();

    /* Configure MPU regions that are common to all tasks. */
    prv_ಸಿದ್ಧತೆ_MPU();

    prv_ಪೋರ್ಟ್_Scheduler_Running = pdTRUE;

    /* Load the context of the first task. */
    v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task();

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value. prvTaskExitError() is referenced to prevent a compiler
     * warning about it being defined but not referenced in the case that the user
     * defines their own exit address. */
    ( ಶೂನ್ಯ ) prvTaskExitError();
    ಹಿಂತಿರುಗಿ pdFALSE;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ಸ್ಥಿರ uint32_t prv_Get_MPURegion_ಗಾತ್ರ_Encoding( uint32_t ul_Actual_MPURegion_ಗಾತ್ರ )
{
    uint32_t ul_Region_ಗಾತ್ರ, ul_Return_ಮೌಲ್ಯ = 4U;

    /* 32 bytes is the smallest valid region for Cortex R4 and R5 CPUs. */
    ಗಾಗಿ( ul_Region_ಗಾತ್ರ = 0x20UL; ul_Return_ಮೌಲ್ಯ < 0x1FUL; ( ul_Region_ಗಾತ್ರ <<= 1UL ) )
    {
        ಆದರೆ( ul_Actual_MPURegion_ಗಾತ್ರ <= ul_Region_ಗಾತ್ರ )
        {
            ನಿಲ್ಲಿಸು;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            ul_Return_ಮೌಲ್ಯ++;
        }
    }

    /* Shift the code by one before returning so it can be written directly
     * into the correct bit position of the attribute register. */
    ಹಿಂತಿರುಗಿ ul_Return_ಮೌಲ್ಯ << 1UL;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_MPU( ಶೂನ್ಯ )
{
#ಆದರೆ defined( __ARMCC_VERSION )
    /* Declaration when these variable are defined in code. */
    /* Sections used for FLASH. */
    ಬಾಹ್ಯ uint32_t * __FLASH_segment_start__;
    ಬಾಹ್ಯ uint32_t * __FLASH_segment_end__;
    ಬಾಹ್ಯ uint32_t * __privileged_functions_start__;
    ಬಾಹ್ಯ uint32_t * __privileged_functions_end__;

    /* Sections used for RAM. */
    ಬಾಹ್ಯ uint32_t * __SRAM_segment_start__;
    ಬಾಹ್ಯ uint32_t * __SRAM_segment_end__;
    ಬಾಹ್ಯ uint32_t * __privileged_data_start__;
    ಬಾಹ್ಯ uint32_t * __privileged_data_end__;
#ಇಲ್ಲದಿದ್ದರೆ
    /* Declaration when these variable are exported from linker scripts. */
    /* Sections used for FLASH. */
    ಬಾಹ್ಯ uint32_t __FLASH_segment_start__[];
    ಬಾಹ್ಯ uint32_t __FLASH_segment_end__[];
    ಬಾಹ್ಯ uint32_t __privileged_functions_start__[];
    ಬಾಹ್ಯ uint32_t __privileged_functions_end__[];

    /* Sections used for RAM. */
    ಬಾಹ್ಯ uint32_t __SRAM_segment_start__[];
    ಬಾಹ್ಯ uint32_t __SRAM_segment_end__[];
    ಬಾಹ್ಯ uint32_t __privileged_data_start__[];
    ಬಾಹ್ಯ uint32_t __privileged_data_end__[];
#ಆದರೆ_ಅಂತ್ಯ /* if defined( __ARMCC_VERSION ) */

    uint32_t ul_Region_ಉದ್ದಳತೆ;
    uint32_t ul_Region_ಉದ್ದಳತೆ_Encoded;

    /* Disable the MPU before programming it. */
    vMPUDisable();

    /* Priv: RX, Unpriv: RX for entire Flash. */
    ul_Region_ಉದ್ದಳತೆ = ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__;
    ul_Region_ಉದ್ದಳತೆ_Encoded = prv_Get_MPURegion_ಗಾತ್ರ_Encoding( ul_Region_ಉದ್ದಳತೆ );
    vMPUSetRegion( ಪೋರ್ಟ್_UNPRIVILEGED_FLASH_REGION,
                   ( uint32_t ) __FLASH_segment_start__,
                   ( ul_Region_ಉದ್ದಳತೆ_Encoded | ಪೋರ್ಟ್_MPU_REGION_ENABLE ),
                   ( ಪೋರ್ಟ್_MPU_REGION_PRIV_RO_USER_RO_EXEC |
                     ಪೋರ್ಟ್_MPU_REGION_ಸಾಮಾನ್ಯ_OIWTNOWA_SHARED ) );

    /* Priv: RX, Unpriv: No access for privileged functions. */
    ul_Region_ಉದ್ದಳತೆ = ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__;
    ul_Region_ಉದ್ದಳತೆ_Encoded = prv_Get_MPURegion_ಗಾತ್ರ_Encoding( ul_Region_ಉದ್ದಳತೆ );
    vMPUSetRegion( ಪೋರ್ಟ್_PRIVILEGED_FLASH_REGION,
                   ( uint32_t ) __privileged_functions_start__,
                   ( ul_Region_ಉದ್ದಳತೆ_Encoded | ಪೋರ್ಟ್_MPU_REGION_ENABLE ),
                   ( ಪೋರ್ಟ್_MPU_REGION_PRIV_RO_USER_NA_EXEC |
                     ಪೋರ್ಟ್_MPU_REGION_ಸಾಮಾನ್ಯ_OIWTNOWA_SHARED ) );

    /* Priv: RW, Unpriv: No Access for privileged data. */
    ul_Region_ಉದ್ದಳತೆ = ( uint32_t ) __privileged_data_end__ - ( uint32_t ) __privileged_data_start__;
    ul_Region_ಉದ್ದಳತೆ_Encoded = prv_Get_MPURegion_ಗಾತ್ರ_Encoding( ul_Region_ಉದ್ದಳತೆ );
    vMPUSetRegion( ಪೋರ್ಟ್_PRIVILEGED_RAM_REGION,
                   ( uint32_t ) __privileged_data_start__,
                   ( ul_Region_ಉದ್ದಳತೆ_Encoded | ಪೋರ್ಟ್_MPU_REGION_ENABLE ),
                   ( ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_NA_NOEXEC |
                     ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_NA_NOEXEC ) );

    /* Enable the MPU background region - it allows privileged operating modes
     * access to unmapped regions of memory without generating a fault. */
    vMPUEnableBackgroundRegion();

    /* After setting default regions, enable the MPU. */
    vMPUEnable();
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ಸ್ಥಿರ ತಳ_Type_t prv_MPURegion_Authorizes_ಬಫರ್( ಸ್ಥಿರಾಂಕ xMPU_REGION_REGISTERS * xTaskMPURegion,
                                                ಸ್ಥಿರಾಂಕ uint32_t ul_ಬಫರ್_ಆರಂಭ,
                                                ಸ್ಥಿರಾಂಕ uint32_t ul_ಬಫರ್_ಉದ್ದಳತೆ,
                                                ಸ್ಥಿರಾಂಕ uint32_t ulAccessRequested )
{
    ತಳ_Type_t xAccessGranted = pdFALSE;
    uint32_t ul_ಬಫರ್_ಕೊನೆ;
    uint32_t ul_MPURegion_ಉದ್ದಳತೆ;
    uint32_t ul_MPURegion_ಆರಂಭ;
    uint32_t ul_MPURegion_ಕೊನೆ;
    uint32_t ulMPURegionAccessPermissions;

    ಆದರೆ( ಪೋರ್ಟ್_ಕೂಡಿಸು_UINT32_WILL_ಅತಿಪ್ರವಾಹ( ul_ಬಫರ್_ಆರಂಭ, ( ul_ಬಫರ್_ಉದ್ದಳತೆ - 1UL ) ) == pdFALSE )
    {
        ul_ಬಫರ್_ಕೊನೆ = ul_ಬಫರ್_ಆರಂಭ + ul_ಬಫರ್_ಉದ್ದಳತೆ - 1UL;
        ul_MPURegion_ಉದ್ದಳತೆ = 2UL << ( xTaskMPURegion->ul_Region_ಗಾತ್ರ >> 1UL );
        ul_MPURegion_ಆರಂಭ = xTaskMPURegion->ul_Region_ತಳ_ವಿಳಾಸ;
        ul_MPURegion_ಕೊನೆ = xTaskMPURegion->ul_Region_ತಳ_ವಿಳಾಸ + ul_MPURegion_ಉದ್ದಳತೆ - 1UL;

        ಆದರೆ( ( ul_ಬಫರ್_ಆರಂಭ >= ul_MPURegion_ಆರಂಭ ) &&
            ( ul_ಬಫರ್_ಕೊನೆ <= ul_MPURegion_ಕೊನೆ ) &&
            ( ul_ಬಫರ್_ಆರಂಭ <= ul_ಬಫರ್_ಕೊನೆ ) )
        {
            ulMPURegionAccessPermissions = xTaskMPURegion->ulRegionAttribute & ಪೋರ್ಟ್_MPU_REGION_AP_BITMASK;

            ಆದರೆ( ulAccessRequested == tskMPU_READ_PERMISSION ) /* RO. */
            {
                ಆದರೆ( ( ulMPURegionAccessPermissions == ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_RO ) ||
                    ( ulMPURegionAccessPermissions == ಪೋರ್ಟ್_MPU_REGION_PRIV_RO_USER_RO ) ||
                    ( ulMPURegionAccessPermissions == ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_RW ) )

                {
                    xAccessGranted = pdTRUE;
                }
            }
            ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ( ( ulAccessRequested & tskMPU_WRITE_PERMISSION ) != 0UL ) /* W or RW. */
            {
                ಆದರೆ( ulMPURegionAccessPermissions == ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_USER_RW )
                {
                    xAccessGranted = pdTRUE;
                }
            }
        }
    }

    ಹಿಂತಿರುಗಿ xAccessGranted;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * pv_ಬಫರ್,
                                            size_t x_ಬಫರ್_ಉದ್ದಳತೆ,
                                            uint32_t ulAccessRequested )
{
    ತಳ_Type_t xAccessGranted = pdFALSE;
    uint32_t ul_Region_ಸೂಚ್ಯಂಕ;
    xMPU_SETTINGS * xTaskMPUSettings = ಖಾಲಿ;

    ಆದರೆ( prv_ಪೋರ್ಟ್_Scheduler_Running == pdFALSE )
    {
        /* Grant access to all the memory before the scheduler is started. It is
         * necessary because there is no task running yet and therefore, we
         * cannot use the permissions of any task. */
        xAccessGranted = pdTRUE;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        /* Calling task's MPU settings. */
        xTaskMPUSettings = xTaskGetMPUSettings( ಖಾಲಿ );

        ಆದರೆ( ( xTaskMPUSettings->ulTaskFlags & ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG ) == ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG )
        {
            /* Privileged tasks have access to all the memory. */
            xAccessGranted = pdTRUE;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            ಗಾಗಿ( ul_Region_ಸೂಚ್ಯಂಕ = 0x0UL; ul_Region_ಸೂಚ್ಯಂಕ < ಪೋರ್ಟ್_ಒಟ್ಟು_ಅಂಕೆ_REGIONS_ಒಳ_TCB; ul_Region_ಸೂಚ್ಯಂಕ++ )
            {
                xAccessGranted = prv_MPURegion_Authorizes_ಬಫರ್( &( xTaskMPUSettings->xRegion[ ul_Region_ಸೂಚ್ಯಂಕ ] ),
                                                               ( uint32_t ) pv_ಬಫರ್,
                                                               ( uint32_t ) x_ಬಫರ್_ಉದ್ದಳತೆ,
                                                               ulAccessRequested );

                ಆದರೆ( xAccessGranted == pdTRUE )
                {
                    ನಿಲ್ಲಿಸು;
                }
            }
        }
    }

    ಹಿಂತಿರುಗಿ xAccessGranted;
}

/* ----------------------------------------------------------------------------------- */

#ಆದರೆ( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( int32_t l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object )
{
    uint32_t ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ, ul_Access_Control_List_ನಮೂದು_ಬಿಟ್;
    ತಳ_Type_t xAccessGranted = pdFALSE;
    ಸ್ಥಿರಾಂಕ xMPU_SETTINGS * xTaskMpuSettings;

    ಆದರೆ( prv_ಪೋರ್ಟ್_Scheduler_Running == pdFALSE )
    {
        /* Grant access to all the kernel objects before the scheduler
         * is started. It is necessary because there is no task running
         * yet and therefore, we cannot use the permissions of any
         * task. */
        xAccessGranted = pdTRUE;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        /* Calling task's MPU settings. */
        xTaskMpuSettings = xTaskGetMPUSettings( ಖಾಲಿ );

        ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object
                                          / ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );
        ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object
                                        % ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );

        ಆದರೆ( ( xTaskMpuSettings->ulTaskFlags & ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG ) == ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            ಆದರೆ( ( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ ] ) &
                  ( 1U << ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ ) ) != 0UL )
            {
                xAccessGranted = pdTRUE;
            }
        }
    }

    ಹಿಂತಿರುಗಿ xAccessGranted;
}

#ಇಲ್ಲದಿದ್ದರೆ

/* PRIVILEGED_FUNCTION */
ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( int32_t l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object )
{
    ( ಶೂನ್ಯ ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object;

    /* If Access Control List feature is not used, all the tasks have
     * access to all the kernel objects. */
    ಹಿಂತಿರುಗಿ pdTRUE;
}

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

#ಆದರೆ( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Grant_Access_ಗಮ್ಯ_Kernel_Object( TaskHandle_t x_ಆಂತರಿಕ_Task_Handle,
                                     int32_t l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object )
{
    uint32_t ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ, ul_Access_Control_List_ನಮೂದು_ಬಿಟ್;
    xMPU_SETTINGS * xTaskMpuSettings;

    ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object
                                      / ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );
    ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object
                                    % ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );

    xTaskMpuSettings = xTaskGetMPUSettings( x_ಆಂತರಿಕ_Task_Handle );

    xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ ] |= ( 1U << ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ );
}

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

#ಆದರೆ( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Revoke_Access_ಗಮ್ಯ_Kernel_Object( TaskHandle_t x_ಆಂತರಿಕ_Task_Handle,
                                      int32_t l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object )
{
    uint32_t ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ, ul_Access_Control_List_ನಮೂದು_ಬಿಟ್;
    xMPU_SETTINGS * xTaskMpuSettings;

    ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object
                                      / ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );
    ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object
                                    % ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );

    xTaskMpuSettings = xTaskGetMPUSettings( x_ಆಂತರಿಕ_Task_Handle );

    xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ ] &= ~( 1U << ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ );
}

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ul_ಪೋರ್ಟ್_ಅಡಚಣೆ_Nesting == ~0UL );

    ಗಾಗಿ( ;; )
    {
    }
}

/* ----------------------------------------------------------------------------------- */

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    prv_ಪೋರ್ಟ್_Scheduler_Running = pdFALSE;

    /* Not implemented in this port. Artificially force an assert. */
    configASSERT( prv_ಪೋರ್ಟ್_Scheduler_Running == pdTRUE );
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ )
{
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert
     * if the critical nesting count is 1 to protect against recursive calls if
     * the assert function also uses a critical section. */
    ಆದರೆ( ulCriticalNesting == 1 )
    {
        configASSERT( ul_ಪೋರ್ಟ್_ಅಡಚಣೆ_Nesting == 0 );
    }
}
/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ )
{
    ಆದರೆ( ulCriticalNesting > ಪೋರ್ಟ್_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        ಆದರೆ( ulCriticalNesting == ಪೋರ್ಟ್_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            ಪೋರ್ಟ್_ENABLE_INTERRUPTS();
        }
    }
}
/* ----------------------------------------------------------------------------------- */
