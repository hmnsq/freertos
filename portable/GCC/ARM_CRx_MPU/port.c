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
#అన్తర్భావ <stdint.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers. That should only be done when
 * task.h is included from an application file. */
#నిర్వచితం_కాకపోతే MPU_WRAPPERS_INCLUDED_FROM_API_FILE
    #నిర్వచించు MPU_WRAPPERS_INCLUDED_FROM_API_FILE
#అయితే_ముగింపు /* MPU_WRAPPERS_INCLUDED_FROM_API_FILE */

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "portmacro.h"
#అన్తర్భావ "task.h"
#అన్తర్భావ "mpu_syscall_numbers.h"

#నిర్వచనం_రద్దు MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Max value that fits in a uint32_t type. */
#నిర్వచించు పోర్టు_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#నిర్వచించు పోర్టు_కూడు_UINT32_WILL_అధికప్రవాహం( a, b )    ( ( a ) > ( పోర్టు_UINT32_MAX - ( b ) ) )
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
PRIVILEGED_దత్తాంశం అస్థిర UBaseType_t ulCriticalNesting = 0xFFFF;

/**
 * @brief Set to 1 to pend a context switch from an ISR.
 *
 * @ingroup Interrupt Management
 */
PRIVILEGED_దత్తాంశం అస్థిర UBaseType_t ul_పోర్టు_Yield_Required = pdFALSE;

/**
 * @brief Interrupt nesting depth, used to count the number of interrupts to unwind.
 *
 * @ingroup Interrupt Management
 */
PRIVILEGED_దత్తాంశం అస్థిర UBaseType_t ul_పోర్టు_అంతరాయం_Nesting = 0UL;

/**
 * @brief Variable to track whether or not the scheduler has been started.
 *
 * @ingroup Scheduler
 *
 * This is the port specific version of the xSchedulerRunning in tasks.c.
 */
PRIVILEGED_దత్తాంశం స్థిర పునాది_Type_t prv_పోర్టు_Scheduler_Running = pdFALSE;

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
PRIVILEGED_FUNCTION స్థిర పునాది_Type_t prv_MPURegion_Authorizes_బఫరు( స్థిరరాశి xMPU_REGION_REGISTERS * xTaskMPURegion,
                                                                    స్థిరరాశి uint32_t ul_బఫరు_ప్రారంభం,
                                                                    స్థిరరాశి uint32_t ul_బఫరు_నిడివి,
                                                                    స్థిరరాశి uint32_t ulAccessRequested );

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
PRIVILEGED_FUNCTION స్థిర uint32_t prv_Get_MPURegion_కొలత_Encoding( uint32_t ul_Actual_MPURegion_కొలత );

/**
 * @brief Set up MPU.
 *
 * @ingroup MPU Control
 */
PRIVILEGED_FUNCTION స్థిర శూన్య prv_అమరిక_MPU( శూన్య );

/* -------------------------- Exported Function Declarations -------------------------- */

/**
 * @brief Enter critical section.
 *
 * @ingroup Critical Section
 */
PRIVILEGED_FUNCTION శూన్య v_పోర్టు_Enter_Critical( శూన్య );

/**
 * @brief Exit critical section.
 *
 * @ingroup Critical Section
 */
PRIVILEGED_FUNCTION శూన్య v_పోర్టు_Exit_Critical( శూన్య );

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
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters,
                                     పునాది_Type_t x_నిరంతరం_Privileged,
                                     xMPU_SETTINGS * xMPUSettings )
{
    /* Setup the initial context of the task. The context is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */
    UBaseType_t ul_సూచీ = CONTEXT_కొలత - 1U;

    x_SYSTEM_CALL_దొంతర_INFO * xSysCallInfo = ఖాళీ;

    ఒకవేళ( x_నిరంతరం_Privileged == pdTRUE )
    {
        xMPUSettings->ulTaskFlags |= పోర్టు_TASK_IS_PRIVILEGED_FLAG;
        /* Current Program Status Register (CPSR). */
        xMPUSettings->ulContext[ ul_సూచీ ] = SYS_బహుళకం;
    }
    లేకపోతే
    {
        xMPUSettings->ulTaskFlags &= ( ~పోర్టు_TASK_IS_PRIVILEGED_FLAG );
        /* Current Program Status Register (CPSR). */
        xMPUSettings->ulContext[ ul_సూచీ ] = USER_బహుళకం;
    }

    ఒకవేళ( ( ( uint32_t ) px_సంకేతం & పోర్టు_THUMB_బహుళకం_చిరునామా ) != 0x0UL )
    {
        /* The task will cause the processor to start in THUMB state, set the
         * Thumb state bit in the CPSR. */
        xMPUSettings->ulContext[ ul_సూచీ ] |= పోర్టు_THUMB_బహుళకం_బిట్టు;
    }

    ul_సూచీ--;

    xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) px_సంకేతం; /* PC. */
    ul_సూచీ--;

    xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) పోర్టు_TASK_RETURN_చిరునామా; /* LR. */
    ul_సూచీ--;

    xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) px_శిఖరం_యొక్క_దొంతర; /* SP. */
    ul_సూచీ--;

    /* General Purpose Registers. */
    xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0x12121212; /* R12. */
    ul_సూచీ--;
    xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0x11111111; /* R11. */
    ul_సూచీ--;
    xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0x10101010; /* R10. */
    ul_సూచీ--;
    xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0x09090909; /* R9. */
    ul_సూచీ--;
    xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0x08080808; /* R8. */
    ul_సూచీ--;
    xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0x07070707; /* R7. */
    ul_సూచీ--;
    xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0x06060606; /* R6. */
    ul_సూచీ--;
    xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0x05050505; /* R5. */
    ul_సూచీ--;
    xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0x04040404; /* R4. */
    ul_సూచీ--;
    xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0x03030303; /* R3. */
    ul_సూచీ--;
    xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0x02020202; /* R2. */
    ul_సూచీ--;
    xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0x01010101; /* R1. */
    ul_సూచీ--;
    xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) pvParameters; /* R0. */
    ul_సూచీ--;

    #ఒకవేళ( పోర్టు_ENABLE_FPU == 1 )
    {
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD0000015; /* S31. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD1500000; /* S30. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD0000014; /* S29. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD1400000; /* S28. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD0000013; /* S27. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD1300000; /* S26. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD0000012; /* S25. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD1200000; /* S24. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD0000011; /* S23. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD1100000; /* S22. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD0000010; /* S21. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD1000000; /* S20. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD0000009; /* S19. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD9000000; /* S18. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD0000008; /* S17. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD8000000; /* S16. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD0000007; /* S15. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD7000000; /* S14. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD0000006; /* S13. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD6000000; /* S12. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD0000005; /* S11. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD5000000; /* S10. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD0000004; /* S9. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD4000000; /* S8. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD0000003; /* S7. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD3000000; /* S6. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD0000002; /* S5. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD2000000; /* S4. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD0000001; /* S3. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD1000000; /* S2. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD0000000; /* S1. */
        ul_సూచీ--;
        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0xD0000000; /* S0. */
        ul_సూచీ--;

        xMPUSettings->ulContext[ ul_సూచీ ] = ( దొంతర_Type_t ) 0x00000000; /* FPSR. */
        ul_సూచీ--;
    }
    #అయితే_ముగింపు /* portENABLE_FPU */

    /* The task will start with a critical nesting count of 0. */
    xMPUSettings->ulContext[ ul_సూచీ ] = పోర్టు_NO_CRITICAL_NESTING;

    /* Ensure that the system call stack is double word aligned. */
    xSysCallInfo = &( xMPUSettings->x_System_Call_దొంతర_Info );
    xSysCallInfo->pul_System_Call_దొంతర_సూచిక = &( xSysCallInfo->ul_System_Call_దొంతర_బఫరు[ config_SYSTEM_CALL_దొంతర_కొలత - 1U ] );
    xSysCallInfo->pul_System_Call_దొంతర_సూచిక = ( uint32_t * ) ( ( ( uint32_t ) ( xSysCallInfo->pul_System_Call_దొంతర_సూచిక ) ) &
                                                               ( ( uint32_t ) ( ~( పోర్టు_BYTE_ALIGNMENT_ముసుగు ) ) ) );

    /* This is not NULL only for the duration of a system call. */
    xSysCallInfo->pul_Task_దొంతర_సూచిక = ఖాళీ;

    /* Set the System Call to return to vPortSystemCallExit. */
    xSysCallInfo->pul_System_Call_Exit_చిరునామా = ( uint32_t * ) ( &v_పోర్టు_System_Call_Exit );

    /* Return the address where this task's context should be restored from. */
    తిరిగి &( xMPUSettings->ulContext[ ul_సూచీ ] );
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
శూన్య v_పోర్టు_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                స్థిరరాశి నిర్మాణం x_జ్ఞాపకం_REGION * స్థిరరాశి xRegions,
                                దొంతర_Type_t * px_Bottom_యొక్క_దొంతర,
                                uint32_t ul_దొంతర_లోతు )
{
    #ఒకవేళ defined( __ARMCC_VERSION )
        /* Declaration when these variable are defined in code instead of being
         * exported from linker scripts. */
        బాహ్య uint32_t * __SRAM_segment_start__;
        బాహ్య uint32_t * __SRAM_segment_end__;
    #లేకపోతే
        /* Declaration when these variable are exported from linker scripts. */
        బాహ్య uint32_t __SRAM_segment_start__[];
        బాహ్య uint32_t __SRAM_segment_end__[];
    #అయితే_ముగింపు /* if defined( __ARMCC_VERSION ) */

    uint32_t ul_సూచీ = 0x0;
    uint32_t ul_Region_నిడివి;
    uint32_t ul_Region_నిడివి_Encoded;
    uint32_t ul_Region_నిడివి_Decoded;

    ఒకవేళ( xRegions == ఖాళీ )
    {
        /* No MPU regions are specified so allow access to all of the RAM. */
        ul_Region_నిడివి = ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__;
        ul_Region_నిడివి_Encoded = prv_Get_MPURegion_కొలత_Encoding( ul_Region_నిడివి );
        ul_Region_నిడివి |= పోర్టు_MPU_REGION_ENABLE;

        /* MPU Settings is zero'd out in the TCB before this function is called.
         * We, therefore, do not need to explicitly zero out unused MPU regions
         * in xMPUSettings. */
        ul_సూచీ = పోర్టు_దొంతర_REGION;

        xMPUSettings->xRegion[ ul_సూచీ ].ul_Region_పునాది_చిరునామా = ( uint32_t ) __SRAM_segment_start__;
        xMPUSettings->xRegion[ ul_సూచీ ].ul_Region_కొలత = ( ul_Region_నిడివి_Encoded |
                                                          పోర్టు_MPU_REGION_ENABLE );
        xMPUSettings->xRegion[ ul_సూచీ ].ulRegionAttribute = ( పోర్టు_MPU_REGION_PRIV_RW_USER_RW_NOEXEC |
                                                               పోర్టు_MPU_REGION_సాధారణ_OIWTNOWA_SHARED );
    }
    లేకపోతే
    {
        కొరకు( ul_సూచీ = 0UL; ul_సూచీ < పోర్టు_అంకె_CONFIGURABLE_REGIONS; ul_సూచీ++ )
        {
            /* If a length has been provided, the region is in use. */
            ఒకవేళ( ( xRegions[ ul_సూచీ ] ).ul_నిడివి_లోపల_బైట్లు > 0UL )
            {
                ul_Region_నిడివి = xRegions[ ul_సూచీ ].ul_నిడివి_లోపల_బైట్లు;
                ul_Region_నిడివి_Encoded = prv_Get_MPURegion_కొలత_Encoding( ul_Region_నిడివి );

                /* MPU region base address must be aligned to the region size
                 * boundary. */
                ul_Region_నిడివి_Decoded = 2UL << ( ul_Region_నిడివి_Encoded >> 1UL );
                configASSERT( ( ( ( uint32_t ) xRegions[ ul_సూచీ ].pv_పునాది_చిరునామా ) % ( ul_Region_నిడివి_Decoded ) ) == 0UL );

                xMPUSettings->xRegion[ ul_సూచీ ].ul_Region_పునాది_చిరునామా = ( uint32_t ) xRegions[ ul_సూచీ ].pv_పునాది_చిరునామా;
                xMPUSettings->xRegion[ ul_సూచీ ].ul_Region_కొలత = ( ul_Region_నిడివి_Encoded |
                                                                  పోర్టు_MPU_REGION_ENABLE );
                xMPUSettings->xRegion[ ul_సూచీ ].ulRegionAttribute = xRegions[ ul_సూచీ ].ulParameters;
            }
            లేకపోతే
            {
                xMPUSettings->xRegion[ ul_సూచీ ].ul_Region_పునాది_చిరునామా = 0x0UL;
                xMPUSettings->xRegion[ ul_సూచీ ].ul_Region_కొలత = 0x0UL;
                xMPUSettings->xRegion[ ul_సూచీ ].ulRegionAttribute = 0x0UL;
            }
        }

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid. At all other
         * times the stack parameters will not be valid and it is assumed that the
         * stack region has already been configured. */
        ఒకవేళ( ul_దొంతర_లోతు != 0x0UL )
        {
            ul_Region_నిడివి_Encoded = prv_Get_MPURegion_కొలత_Encoding( ul_దొంతర_లోతు * ( uint32_t ) పరిమాణం( దొంతర_Type_t ) );

            /* MPU region base address must be aligned to the region size
             * boundary. */
            ul_Region_నిడివి_Decoded = 2UL << ( ul_Region_నిడివి_Encoded >> 1UL );
            configASSERT( ( ( uint32_t ) px_Bottom_యొక్క_దొంతర % ( ul_Region_నిడివి_Decoded ) ) == 0U );

            ul_సూచీ = పోర్టు_దొంతర_REGION;
            xMPUSettings->xRegion[ ul_సూచీ ].ul_Region_పునాది_చిరునామా = ( uint32_t ) px_Bottom_యొక్క_దొంతర;
            xMPUSettings->xRegion[ ul_సూచీ ].ul_Region_కొలత = ( ul_Region_నిడివి_Encoded |
                                                              పోర్టు_MPU_REGION_ENABLE );
            xMPUSettings->xRegion[ ul_సూచీ ].ulRegionAttribute = ( పోర్టు_MPU_REGION_PRIV_RW_USER_RW_NOEXEC |
                                                                   పోర్టు_MPU_REGION_సాధారణ_OIWTNOWA_SHARED );
        }
    }
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
పునాది_Type_t x_పోర్టు_Is_Task_Privileged( శూన్య )
{
    పునాది_Type_t xTaskIsPrivileged = pdFALSE;

    /* Calling task's MPU settings. */
    స్థిరరాశి xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ఖాళీ );

    ఒకవేళ( ( xTaskMpuSettings->ulTaskFlags & పోర్టు_TASK_IS_PRIVILEGED_FLAG ) == పోర్టు_TASK_IS_PRIVILEGED_FLAG )
    {
        xTaskIsPrivileged = pdTRUE;
    }

    తిరిగి xTaskIsPrivileged;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    /* Start the timer that generates the tick ISR. */
    config_అమరిక_TICK_అంతరాయం();

    /* Configure MPU regions that are common to all tasks. */
    prv_అమరిక_MPU();

    prv_పోర్టు_Scheduler_Running = pdTRUE;

    /* Load the context of the first task. */
    v_పోర్టు_ప్రారంభం_మొదటి_Task();

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value. prvTaskExitError() is referenced to prevent a compiler
     * warning about it being defined but not referenced in the case that the user
     * defines their own exit address. */
    ( శూన్య ) prvTaskExitError();
    తిరిగి pdFALSE;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
స్థిర uint32_t prv_Get_MPURegion_కొలత_Encoding( uint32_t ul_Actual_MPURegion_కొలత )
{
    uint32_t ul_Region_కొలత, ul_Return_విలువ = 4U;

    /* 32 bytes is the smallest valid region for Cortex R4 and R5 CPUs. */
    కొరకు( ul_Region_కొలత = 0x20UL; ul_Return_విలువ < 0x1FUL; ( ul_Region_కొలత <<= 1UL ) )
    {
        ఒకవేళ( ul_Actual_MPURegion_కొలత <= ul_Region_కొలత )
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
    తిరిగి ul_Return_విలువ << 1UL;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
స్థిర శూన్య prv_అమరిక_MPU( శూన్య )
{
#ఒకవేళ defined( __ARMCC_VERSION )
    /* Declaration when these variable are defined in code. */
    /* Sections used for FLASH. */
    బాహ్య uint32_t * __FLASH_segment_start__;
    బాహ్య uint32_t * __FLASH_segment_end__;
    బాహ్య uint32_t * __privileged_functions_start__;
    బాహ్య uint32_t * __privileged_functions_end__;

    /* Sections used for RAM. */
    బాహ్య uint32_t * __SRAM_segment_start__;
    బాహ్య uint32_t * __SRAM_segment_end__;
    బాహ్య uint32_t * __privileged_data_start__;
    బాహ్య uint32_t * __privileged_data_end__;
#లేకపోతే
    /* Declaration when these variable are exported from linker scripts. */
    /* Sections used for FLASH. */
    బాహ్య uint32_t __FLASH_segment_start__[];
    బాహ్య uint32_t __FLASH_segment_end__[];
    బాహ్య uint32_t __privileged_functions_start__[];
    బాహ్య uint32_t __privileged_functions_end__[];

    /* Sections used for RAM. */
    బాహ్య uint32_t __SRAM_segment_start__[];
    బాహ్య uint32_t __SRAM_segment_end__[];
    బాహ్య uint32_t __privileged_data_start__[];
    బాహ్య uint32_t __privileged_data_end__[];
#అయితే_ముగింపు /* if defined( __ARMCC_VERSION ) */

    uint32_t ul_Region_నిడివి;
    uint32_t ul_Region_నిడివి_Encoded;

    /* Disable the MPU before programming it. */
    vMPUDisable();

    /* Priv: RX, Unpriv: RX for entire Flash. */
    ul_Region_నిడివి = ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__;
    ul_Region_నిడివి_Encoded = prv_Get_MPURegion_కొలత_Encoding( ul_Region_నిడివి );
    vMPUSetRegion( పోర్టు_UNPRIVILEGED_FLASH_REGION,
                   ( uint32_t ) __FLASH_segment_start__,
                   ( ul_Region_నిడివి_Encoded | పోర్టు_MPU_REGION_ENABLE ),
                   ( పోర్టు_MPU_REGION_PRIV_RO_USER_RO_EXEC |
                     పోర్టు_MPU_REGION_సాధారణ_OIWTNOWA_SHARED ) );

    /* Priv: RX, Unpriv: No access for privileged functions. */
    ul_Region_నిడివి = ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__;
    ul_Region_నిడివి_Encoded = prv_Get_MPURegion_కొలత_Encoding( ul_Region_నిడివి );
    vMPUSetRegion( పోర్టు_PRIVILEGED_FLASH_REGION,
                   ( uint32_t ) __privileged_functions_start__,
                   ( ul_Region_నిడివి_Encoded | పోర్టు_MPU_REGION_ENABLE ),
                   ( పోర్టు_MPU_REGION_PRIV_RO_USER_NA_EXEC |
                     పోర్టు_MPU_REGION_సాధారణ_OIWTNOWA_SHARED ) );

    /* Priv: RW, Unpriv: No Access for privileged data. */
    ul_Region_నిడివి = ( uint32_t ) __privileged_data_end__ - ( uint32_t ) __privileged_data_start__;
    ul_Region_నిడివి_Encoded = prv_Get_MPURegion_కొలత_Encoding( ul_Region_నిడివి );
    vMPUSetRegion( పోర్టు_PRIVILEGED_RAM_REGION,
                   ( uint32_t ) __privileged_data_start__,
                   ( ul_Region_నిడివి_Encoded | పోర్టు_MPU_REGION_ENABLE ),
                   ( పోర్టు_MPU_REGION_PRIV_RW_USER_NA_NOEXEC |
                     పోర్టు_MPU_REGION_PRIV_RW_USER_NA_NOEXEC ) );

    /* Enable the MPU background region - it allows privileged operating modes
     * access to unmapped regions of memory without generating a fault. */
    vMPUEnableBackgroundRegion();

    /* After setting default regions, enable the MPU. */
    vMPUEnable();
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
స్థిర పునాది_Type_t prv_MPURegion_Authorizes_బఫరు( స్థిరరాశి xMPU_REGION_REGISTERS * xTaskMPURegion,
                                                స్థిరరాశి uint32_t ul_బఫరు_ప్రారంభం,
                                                స్థిరరాశి uint32_t ul_బఫరు_నిడివి,
                                                స్థిరరాశి uint32_t ulAccessRequested )
{
    పునాది_Type_t xAccessGranted = pdFALSE;
    uint32_t ul_బఫరు_చివర;
    uint32_t ul_MPURegion_నిడివి;
    uint32_t ul_MPURegion_ప్రారంభం;
    uint32_t ul_MPURegion_చివర;
    uint32_t ulMPURegionAccessPermissions;

    ఒకవేళ( పోర్టు_కూడు_UINT32_WILL_అధికప్రవాహం( ul_బఫరు_ప్రారంభం, ( ul_బఫరు_నిడివి - 1UL ) ) == pdFALSE )
    {
        ul_బఫరు_చివర = ul_బఫరు_ప్రారంభం + ul_బఫరు_నిడివి - 1UL;
        ul_MPURegion_నిడివి = 2UL << ( xTaskMPURegion->ul_Region_కొలత >> 1UL );
        ul_MPURegion_ప్రారంభం = xTaskMPURegion->ul_Region_పునాది_చిరునామా;
        ul_MPURegion_చివర = xTaskMPURegion->ul_Region_పునాది_చిరునామా + ul_MPURegion_నిడివి - 1UL;

        ఒకవేళ( ( ul_బఫరు_ప్రారంభం >= ul_MPURegion_ప్రారంభం ) &&
            ( ul_బఫరు_చివర <= ul_MPURegion_చివర ) &&
            ( ul_బఫరు_ప్రారంభం <= ul_బఫరు_చివర ) )
        {
            ulMPURegionAccessPermissions = xTaskMPURegion->ulRegionAttribute & పోర్టు_MPU_REGION_AP_BITMASK;

            ఒకవేళ( ulAccessRequested == tskMPU_READ_PERMISSION ) /* RO. */
            {
                ఒకవేళ( ( ulMPURegionAccessPermissions == పోర్టు_MPU_REGION_PRIV_RW_USER_RO ) ||
                    ( ulMPURegionAccessPermissions == పోర్టు_MPU_REGION_PRIV_RO_USER_RO ) ||
                    ( ulMPURegionAccessPermissions == పోర్టు_MPU_REGION_PRIV_RW_USER_RW ) )

                {
                    xAccessGranted = pdTRUE;
                }
            }
            లేకపోతే ఒకవేళ( ( ulAccessRequested & tskMPU_WRITE_PERMISSION ) != 0UL ) /* W or RW. */
            {
                ఒకవేళ( ulMPURegionAccessPermissions == పోర్టు_MPU_REGION_PRIV_RW_USER_RW )
                {
                    xAccessGranted = pdTRUE;
                }
            }
        }
    }

    తిరిగి xAccessGranted;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
పునాది_Type_t x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( స్థిరరాశి శూన్య * pv_బఫరు,
                                            size_t x_బఫరు_నిడివి,
                                            uint32_t ulAccessRequested )
{
    పునాది_Type_t xAccessGranted = pdFALSE;
    uint32_t ul_Region_సూచీ;
    xMPU_SETTINGS * xTaskMPUSettings = ఖాళీ;

    ఒకవేళ( prv_పోర్టు_Scheduler_Running == pdFALSE )
    {
        /* Grant access to all the memory before the scheduler is started. It is
         * necessary because there is no task running yet and therefore, we
         * cannot use the permissions of any task. */
        xAccessGranted = pdTRUE;
    }
    లేకపోతే
    {
        /* Calling task's MPU settings. */
        xTaskMPUSettings = xTaskGetMPUSettings( ఖాళీ );

        ఒకవేళ( ( xTaskMPUSettings->ulTaskFlags & పోర్టు_TASK_IS_PRIVILEGED_FLAG ) == పోర్టు_TASK_IS_PRIVILEGED_FLAG )
        {
            /* Privileged tasks have access to all the memory. */
            xAccessGranted = pdTRUE;
        }
        లేకపోతే
        {
            కొరకు( ul_Region_సూచీ = 0x0UL; ul_Region_సూచీ < పోర్టు_మొత్తం_అంకె_REGIONS_లోపల_TCB; ul_Region_సూచీ++ )
            {
                xAccessGranted = prv_MPURegion_Authorizes_బఫరు( &( xTaskMPUSettings->xRegion[ ul_Region_సూచీ ] ),
                                                               ( uint32_t ) pv_బఫరు,
                                                               ( uint32_t ) x_బఫరు_నిడివి,
                                                               ulAccessRequested );

                ఒకవేళ( xAccessGranted == pdTRUE )
                {
                    ఆపు;
                }
            }
        }
    }

    తిరిగి xAccessGranted;
}

/* ----------------------------------------------------------------------------------- */

#ఒకవేళ( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
పునాది_Type_t x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( int32_t l_అంతర్గత_సూచీ_యొక్క_Kernel_Object )
{
    uint32_t ul_Access_Control_List_నమోదు_సూచీ, ul_Access_Control_List_నమోదు_బిట్టు;
    పునాది_Type_t xAccessGranted = pdFALSE;
    స్థిరరాశి xMPU_SETTINGS * xTaskMpuSettings;

    ఒకవేళ( prv_పోర్టు_Scheduler_Running == pdFALSE )
    {
        /* Grant access to all the kernel objects before the scheduler
         * is started. It is necessary because there is no task running
         * yet and therefore, we cannot use the permissions of any
         * task. */
        xAccessGranted = pdTRUE;
    }
    లేకపోతే
    {
        /* Calling task's MPU settings. */
        xTaskMpuSettings = xTaskGetMPUSettings( ఖాళీ );

        ul_Access_Control_List_నమోదు_సూచీ = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object
                                          / పోర్టు_ACL_నమోదు_కొలత_బిట్లు );
        ul_Access_Control_List_నమోదు_బిట్టు = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object
                                        % పోర్టు_ACL_నమోదు_కొలత_బిట్లు );

        ఒకవేళ( ( xTaskMpuSettings->ulTaskFlags & పోర్టు_TASK_IS_PRIVILEGED_FLAG ) == పోర్టు_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        లేకపోతే
        {
            ఒకవేళ( ( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_నమోదు_సూచీ ] ) &
                  ( 1U << ul_Access_Control_List_నమోదు_బిట్టు ) ) != 0UL )
            {
                xAccessGranted = pdTRUE;
            }
        }
    }

    తిరిగి xAccessGranted;
}

#లేకపోతే

/* PRIVILEGED_FUNCTION */
పునాది_Type_t x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( int32_t l_అంతర్గత_సూచీ_యొక్క_Kernel_Object )
{
    ( శూన్య ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object;

    /* If Access Control List feature is not used, all the tasks have
     * access to all the kernel objects. */
    తిరిగి pdTRUE;
}

#అయితే_ముగింపు /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

#ఒకవేళ( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
శూన్య v_పోర్టు_Grant_Access_గమ్యం_Kernel_Object( TaskHandle_t x_అంతర్గత_Task_Handle,
                                     int32_t l_అంతర్గత_సూచీ_యొక్క_Kernel_Object )
{
    uint32_t ul_Access_Control_List_నమోదు_సూచీ, ul_Access_Control_List_నమోదు_బిట్టు;
    xMPU_SETTINGS * xTaskMpuSettings;

    ul_Access_Control_List_నమోదు_సూచీ = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object
                                      / పోర్టు_ACL_నమోదు_కొలత_బిట్లు );
    ul_Access_Control_List_నమోదు_బిట్టు = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object
                                    % పోర్టు_ACL_నమోదు_కొలత_బిట్లు );

    xTaskMpuSettings = xTaskGetMPUSettings( x_అంతర్గత_Task_Handle );

    xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_నమోదు_సూచీ ] |= ( 1U << ul_Access_Control_List_నమోదు_బిట్టు );
}

#అయితే_ముగింపు /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

#ఒకవేళ( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
శూన్య v_పోర్టు_Revoke_Access_గమ్యం_Kernel_Object( TaskHandle_t x_అంతర్గత_Task_Handle,
                                      int32_t l_అంతర్గత_సూచీ_యొక్క_Kernel_Object )
{
    uint32_t ul_Access_Control_List_నమోదు_సూచీ, ul_Access_Control_List_నమోదు_బిట్టు;
    xMPU_SETTINGS * xTaskMpuSettings;

    ul_Access_Control_List_నమోదు_సూచీ = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object
                                      / పోర్టు_ACL_నమోదు_కొలత_బిట్లు );
    ul_Access_Control_List_నమోదు_బిట్టు = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object
                                    % పోర్టు_ACL_నమోదు_కొలత_బిట్లు );

    xTaskMpuSettings = xTaskGetMPUSettings( x_అంతర్గత_Task_Handle );

    xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_నమోదు_సూచీ ] &= ~( 1U << ul_Access_Control_List_నమోదు_బిట్టు );
}

#అయితే_ముగింపు /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

శూన్య prvTaskExitError( శూన్య )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ul_పోర్టు_అంతరాయం_Nesting == ~0UL );

    కొరకు( ;; )
    {
    }
}

/* ----------------------------------------------------------------------------------- */

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    prv_పోర్టు_Scheduler_Running = pdFALSE;

    /* Not implemented in this port. Artificially force an assert. */
    configASSERT( prv_పోర్టు_Scheduler_Running == pdTRUE );
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
శూన్య v_పోర్టు_Enter_Critical( శూన్య )
{
    పోర్టు_DISABLE_INTERRUPTS();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert
     * if the critical nesting count is 1 to protect against recursive calls if
     * the assert function also uses a critical section. */
    ఒకవేళ( ulCriticalNesting == 1 )
    {
        configASSERT( ul_పోర్టు_అంతరాయం_Nesting == 0 );
    }
}
/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
శూన్య v_పోర్టు_Exit_Critical( శూన్య )
{
    ఒకవేళ( ulCriticalNesting > పోర్టు_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        ఒకవేళ( ulCriticalNesting == పోర్టు_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            పోర్టు_ENABLE_INTERRUPTS();
        }
    }
}
/* ----------------------------------------------------------------------------------- */
