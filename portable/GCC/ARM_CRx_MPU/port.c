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
#ضمن <stdint.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers. That should only be done when
 * task.h is included from an application file. */
#جيڪڏهن_وصف_نه_ٿيل MPU_WRAPPERS_INCLUDED_FROM_API_FILE
    #وصف_ڪريو MPU_WRAPPERS_INCLUDED_FROM_API_FILE
#جيڪڏهن_پورو /* MPU_WRAPPERS_INCLUDED_FROM_API_FILE */

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "portmacro.h"
#ضمن "task.h"
#ضمن "mpu_syscall_numbers.h"

#وصف_رد MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Max value that fits in a uint32_t type. */
#وصف_ڪريو پورٽ_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#وصف_ڪريو پورٽ_جوڙيو_UINT32_WILL_حد_کان_مٿي( a, b )    ( ( a ) > ( پورٽ_UINT32_MAX - ( b ) ) )
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
PRIVILEGED_معلومات متطاير UBaseType_t ulCriticalNesting = 0xFFFF;

/**
 * @brief Set to 1 to pend a context switch from an ISR.
 *
 * @ingroup Interrupt Management
 */
PRIVILEGED_معلومات متطاير UBaseType_t ul_پورٽ_Yield_Required = pdFALSE;

/**
 * @brief Interrupt nesting depth, used to count the number of interrupts to unwind.
 *
 * @ingroup Interrupt Management
 */
PRIVILEGED_معلومات متطاير UBaseType_t ul_پورٽ_مداخلت_Nesting = 0UL;

/**
 * @brief Variable to track whether or not the scheduler has been started.
 *
 * @ingroup Scheduler
 *
 * This is the port specific version of the xSchedulerRunning in tasks.c.
 */
PRIVILEGED_معلومات ساكن بنياد_Type_t prv_پورٽ_Scheduler_Running = pdFALSE;

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
PRIVILEGED_FUNCTION ساكن بنياد_Type_t prv_MPURegion_Authorizes_بفر( ثابت xMPU_REGION_REGISTERS * xTaskMPURegion,
                                                                    ثابت uint32_t ul_بفر_شروعات,
                                                                    ثابت uint32_t ul_بفر_ڊيگهائي,
                                                                    ثابت uint32_t ulAccessRequested );

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
PRIVILEGED_FUNCTION ساكن uint32_t prv_Get_MPURegion_سائيز_Encoding( uint32_t ul_Actual_MPURegion_سائيز );

/**
 * @brief Set up MPU.
 *
 * @ingroup MPU Control
 */
PRIVILEGED_FUNCTION ساكن فراغ prv_تياري_MPU( فراغ );

/* -------------------------- Exported Function Declarations -------------------------- */

/**
 * @brief Enter critical section.
 *
 * @ingroup Critical Section
 */
PRIVILEGED_FUNCTION فراغ v_پورٽ_Enter_Critical( فراغ );

/**
 * @brief Exit critical section.
 *
 * @ingroup Critical Section
 */
PRIVILEGED_FUNCTION فراغ v_پورٽ_Exit_Critical( فراغ );

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
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters,
                                     بنياد_Type_t x_لاڳيتو_Privileged,
                                     xMPU_SETTINGS * xMPUSettings )
{
    /* Setup the initial context of the task. The context is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */
    UBaseType_t ul_اشاريو = CONTEXT_سائيز - 1U;

    x_SYSTEM_CALL_ڍير_INFO * xSysCallInfo = عدم;

    إذا( x_لاڳيتو_Privileged == pdTRUE )
    {
        xMPUSettings->ulTaskFlags |= پورٽ_TASK_IS_PRIVILEGED_FLAG;
        /* Current Program Status Register (CPSR). */
        xMPUSettings->ulContext[ ul_اشاريو ] = SYS_گهڻائي;
    }
    وإلا
    {
        xMPUSettings->ulTaskFlags &= ( ~پورٽ_TASK_IS_PRIVILEGED_FLAG );
        /* Current Program Status Register (CPSR). */
        xMPUSettings->ulContext[ ul_اشاريو ] = USER_گهڻائي;
    }

    إذا( ( ( uint32_t ) px_ڪوڊ & پورٽ_THUMB_گهڻائي_پتو ) != 0x0UL )
    {
        /* The task will cause the processor to start in THUMB state, set the
         * Thumb state bit in the CPSR. */
        xMPUSettings->ulContext[ ul_اشاريو ] |= پورٽ_THUMB_گهڻائي_ٻٽو_انگ;
    }

    ul_اشاريو--;

    xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) px_ڪوڊ; /* PC. */
    ul_اشاريو--;

    xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) پورٽ_TASK_RETURN_پتو; /* LR. */
    ul_اشاريو--;

    xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) px_چوٽي_جو_ڍير; /* SP. */
    ul_اشاريو--;

    /* General Purpose Registers. */
    xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0x12121212; /* R12. */
    ul_اشاريو--;
    xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0x11111111; /* R11. */
    ul_اشاريو--;
    xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0x10101010; /* R10. */
    ul_اشاريو--;
    xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0x09090909; /* R9. */
    ul_اشاريو--;
    xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0x08080808; /* R8. */
    ul_اشاريو--;
    xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0x07070707; /* R7. */
    ul_اشاريو--;
    xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0x06060606; /* R6. */
    ul_اشاريو--;
    xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0x05050505; /* R5. */
    ul_اشاريو--;
    xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0x04040404; /* R4. */
    ul_اشاريو--;
    xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0x03030303; /* R3. */
    ul_اشاريو--;
    xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0x02020202; /* R2. */
    ul_اشاريو--;
    xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0x01010101; /* R1. */
    ul_اشاريو--;
    xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) pvParameters; /* R0. */
    ul_اشاريو--;

    #إذا( پورٽ_ENABLE_FPU == 1 )
    {
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD0000015; /* S31. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD1500000; /* S30. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD0000014; /* S29. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD1400000; /* S28. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD0000013; /* S27. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD1300000; /* S26. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD0000012; /* S25. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD1200000; /* S24. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD0000011; /* S23. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD1100000; /* S22. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD0000010; /* S21. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD1000000; /* S20. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD0000009; /* S19. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD9000000; /* S18. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD0000008; /* S17. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD8000000; /* S16. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD0000007; /* S15. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD7000000; /* S14. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD0000006; /* S13. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD6000000; /* S12. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD0000005; /* S11. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD5000000; /* S10. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD0000004; /* S9. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD4000000; /* S8. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD0000003; /* S7. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD3000000; /* S6. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD0000002; /* S5. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD2000000; /* S4. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD0000001; /* S3. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD1000000; /* S2. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD0000000; /* S1. */
        ul_اشاريو--;
        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0xD0000000; /* S0. */
        ul_اشاريو--;

        xMPUSettings->ulContext[ ul_اشاريو ] = ( ڍير_Type_t ) 0x00000000; /* FPSR. */
        ul_اشاريو--;
    }
    #جيڪڏهن_پورو /* portENABLE_FPU */

    /* The task will start with a critical nesting count of 0. */
    xMPUSettings->ulContext[ ul_اشاريو ] = پورٽ_NO_CRITICAL_NESTING;

    /* Ensure that the system call stack is double word aligned. */
    xSysCallInfo = &( xMPUSettings->x_System_Call_ڍير_Info );
    xSysCallInfo->pul_System_Call_ڍير_اشارو = &( xSysCallInfo->ul_System_Call_ڍير_بفر[ config_SYSTEM_CALL_ڍير_سائيز - 1U ] );
    xSysCallInfo->pul_System_Call_ڍير_اشارو = ( uint32_t * ) ( ( ( uint32_t ) ( xSysCallInfo->pul_System_Call_ڍير_اشارو ) ) &
                                                               ( ( uint32_t ) ( ~( پورٽ_BYTE_ALIGNMENT_نقاب ) ) ) );

    /* This is not NULL only for the duration of a system call. */
    xSysCallInfo->pul_Task_ڍير_اشارو = عدم;

    /* Set the System Call to return to vPortSystemCallExit. */
    xSysCallInfo->pul_System_Call_Exit_پتو = ( uint32_t * ) ( &v_پورٽ_System_Call_Exit );

    /* Return the address where this task's context should be restored from. */
    أرجع &( xMPUSettings->ulContext[ ul_اشاريو ] );
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
فراغ v_پورٽ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                ثابت بنية x_يادگيري_REGION * ثابت xRegions,
                                ڍير_Type_t * px_Bottom_جو_ڍير,
                                uint32_t ul_ڍير_اونهائي )
{
    #إذا defined( __ARMCC_VERSION )
        /* Declaration when these variable are defined in code instead of being
         * exported from linker scripts. */
        خارجي uint32_t * __SRAM_segment_start__;
        خارجي uint32_t * __SRAM_segment_end__;
    #وإلا
        /* Declaration when these variable are exported from linker scripts. */
        خارجي uint32_t __SRAM_segment_start__[];
        خارجي uint32_t __SRAM_segment_end__[];
    #جيڪڏهن_پورو /* if defined( __ARMCC_VERSION ) */

    uint32_t ul_اشاريو = 0x0;
    uint32_t ul_Region_ڊيگهائي;
    uint32_t ul_Region_ڊيگهائي_Encoded;
    uint32_t ul_Region_ڊيگهائي_Decoded;

    إذا( xRegions == عدم )
    {
        /* No MPU regions are specified so allow access to all of the RAM. */
        ul_Region_ڊيگهائي = ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__;
        ul_Region_ڊيگهائي_Encoded = prv_Get_MPURegion_سائيز_Encoding( ul_Region_ڊيگهائي );
        ul_Region_ڊيگهائي |= پورٽ_MPU_REGION_ENABLE;

        /* MPU Settings is zero'd out in the TCB before this function is called.
         * We, therefore, do not need to explicitly zero out unused MPU regions
         * in xMPUSettings. */
        ul_اشاريو = پورٽ_ڍير_REGION;

        xMPUSettings->xRegion[ ul_اشاريو ].ul_Region_بنياد_پتو = ( uint32_t ) __SRAM_segment_start__;
        xMPUSettings->xRegion[ ul_اشاريو ].ul_Region_سائيز = ( ul_Region_ڊيگهائي_Encoded |
                                                          پورٽ_MPU_REGION_ENABLE );
        xMPUSettings->xRegion[ ul_اشاريو ].ulRegionAttribute = ( پورٽ_MPU_REGION_PRIV_RW_USER_RW_NOEXEC |
                                                               پورٽ_MPU_REGION_عام_OIWTNOWA_SHARED );
    }
    وإلا
    {
        لكل( ul_اشاريو = 0UL; ul_اشاريو < پورٽ_انگ_CONFIGURABLE_REGIONS; ul_اشاريو++ )
        {
            /* If a length has been provided, the region is in use. */
            إذا( ( xRegions[ ul_اشاريو ] ).ul_ڊيگهائي_اندريون_بائيٽون > 0UL )
            {
                ul_Region_ڊيگهائي = xRegions[ ul_اشاريو ].ul_ڊيگهائي_اندريون_بائيٽون;
                ul_Region_ڊيگهائي_Encoded = prv_Get_MPURegion_سائيز_Encoding( ul_Region_ڊيگهائي );

                /* MPU region base address must be aligned to the region size
                 * boundary. */
                ul_Region_ڊيگهائي_Decoded = 2UL << ( ul_Region_ڊيگهائي_Encoded >> 1UL );
                configASSERT( ( ( ( uint32_t ) xRegions[ ul_اشاريو ].pv_بنياد_پتو ) % ( ul_Region_ڊيگهائي_Decoded ) ) == 0UL );

                xMPUSettings->xRegion[ ul_اشاريو ].ul_Region_بنياد_پتو = ( uint32_t ) xRegions[ ul_اشاريو ].pv_بنياد_پتو;
                xMPUSettings->xRegion[ ul_اشاريو ].ul_Region_سائيز = ( ul_Region_ڊيگهائي_Encoded |
                                                                  پورٽ_MPU_REGION_ENABLE );
                xMPUSettings->xRegion[ ul_اشاريو ].ulRegionAttribute = xRegions[ ul_اشاريو ].ulParameters;
            }
            وإلا
            {
                xMPUSettings->xRegion[ ul_اشاريو ].ul_Region_بنياد_پتو = 0x0UL;
                xMPUSettings->xRegion[ ul_اشاريو ].ul_Region_سائيز = 0x0UL;
                xMPUSettings->xRegion[ ul_اشاريو ].ulRegionAttribute = 0x0UL;
            }
        }

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid. At all other
         * times the stack parameters will not be valid and it is assumed that the
         * stack region has already been configured. */
        إذا( ul_ڍير_اونهائي != 0x0UL )
        {
            ul_Region_ڊيگهائي_Encoded = prv_Get_MPURegion_سائيز_Encoding( ul_ڍير_اونهائي * ( uint32_t ) حجم( ڍير_Type_t ) );

            /* MPU region base address must be aligned to the region size
             * boundary. */
            ul_Region_ڊيگهائي_Decoded = 2UL << ( ul_Region_ڊيگهائي_Encoded >> 1UL );
            configASSERT( ( ( uint32_t ) px_Bottom_جو_ڍير % ( ul_Region_ڊيگهائي_Decoded ) ) == 0U );

            ul_اشاريو = پورٽ_ڍير_REGION;
            xMPUSettings->xRegion[ ul_اشاريو ].ul_Region_بنياد_پتو = ( uint32_t ) px_Bottom_جو_ڍير;
            xMPUSettings->xRegion[ ul_اشاريو ].ul_Region_سائيز = ( ul_Region_ڊيگهائي_Encoded |
                                                              پورٽ_MPU_REGION_ENABLE );
            xMPUSettings->xRegion[ ul_اشاريو ].ulRegionAttribute = ( پورٽ_MPU_REGION_PRIV_RW_USER_RW_NOEXEC |
                                                                   پورٽ_MPU_REGION_عام_OIWTNOWA_SHARED );
        }
    }
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
بنياد_Type_t x_پورٽ_Is_Task_Privileged( فراغ )
{
    بنياد_Type_t xTaskIsPrivileged = pdFALSE;

    /* Calling task's MPU settings. */
    ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( عدم );

    إذا( ( xTaskMpuSettings->ulTaskFlags & پورٽ_TASK_IS_PRIVILEGED_FLAG ) == پورٽ_TASK_IS_PRIVILEGED_FLAG )
    {
        xTaskIsPrivileged = pdTRUE;
    }

    أرجع xTaskIsPrivileged;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    /* Start the timer that generates the tick ISR. */
    config_تياري_TICK_مداخلت();

    /* Configure MPU regions that are common to all tasks. */
    prv_تياري_MPU();

    prv_پورٽ_Scheduler_Running = pdTRUE;

    /* Load the context of the first task. */
    v_پورٽ_شروعات_پهريون_Task();

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value. prvTaskExitError() is referenced to prevent a compiler
     * warning about it being defined but not referenced in the case that the user
     * defines their own exit address. */
    ( فراغ ) prvTaskExitError();
    أرجع pdFALSE;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ساكن uint32_t prv_Get_MPURegion_سائيز_Encoding( uint32_t ul_Actual_MPURegion_سائيز )
{
    uint32_t ul_Region_سائيز, ul_Return_قدر = 4U;

    /* 32 bytes is the smallest valid region for Cortex R4 and R5 CPUs. */
    لكل( ul_Region_سائيز = 0x20UL; ul_Return_قدر < 0x1FUL; ( ul_Region_سائيز <<= 1UL ) )
    {
        إذا( ul_Actual_MPURegion_سائيز <= ul_Region_سائيز )
        {
            اكسر;
        }
        وإلا
        {
            ul_Return_قدر++;
        }
    }

    /* Shift the code by one before returning so it can be written directly
     * into the correct bit position of the attribute register. */
    أرجع ul_Return_قدر << 1UL;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ساكن فراغ prv_تياري_MPU( فراغ )
{
#إذا defined( __ARMCC_VERSION )
    /* Declaration when these variable are defined in code. */
    /* Sections used for FLASH. */
    خارجي uint32_t * __FLASH_segment_start__;
    خارجي uint32_t * __FLASH_segment_end__;
    خارجي uint32_t * __privileged_functions_start__;
    خارجي uint32_t * __privileged_functions_end__;

    /* Sections used for RAM. */
    خارجي uint32_t * __SRAM_segment_start__;
    خارجي uint32_t * __SRAM_segment_end__;
    خارجي uint32_t * __privileged_data_start__;
    خارجي uint32_t * __privileged_data_end__;
#وإلا
    /* Declaration when these variable are exported from linker scripts. */
    /* Sections used for FLASH. */
    خارجي uint32_t __FLASH_segment_start__[];
    خارجي uint32_t __FLASH_segment_end__[];
    خارجي uint32_t __privileged_functions_start__[];
    خارجي uint32_t __privileged_functions_end__[];

    /* Sections used for RAM. */
    خارجي uint32_t __SRAM_segment_start__[];
    خارجي uint32_t __SRAM_segment_end__[];
    خارجي uint32_t __privileged_data_start__[];
    خارجي uint32_t __privileged_data_end__[];
#جيڪڏهن_پورو /* if defined( __ARMCC_VERSION ) */

    uint32_t ul_Region_ڊيگهائي;
    uint32_t ul_Region_ڊيگهائي_Encoded;

    /* Disable the MPU before programming it. */
    vMPUDisable();

    /* Priv: RX, Unpriv: RX for entire Flash. */
    ul_Region_ڊيگهائي = ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__;
    ul_Region_ڊيگهائي_Encoded = prv_Get_MPURegion_سائيز_Encoding( ul_Region_ڊيگهائي );
    vMPUSetRegion( پورٽ_UNPRIVILEGED_FLASH_REGION,
                   ( uint32_t ) __FLASH_segment_start__,
                   ( ul_Region_ڊيگهائي_Encoded | پورٽ_MPU_REGION_ENABLE ),
                   ( پورٽ_MPU_REGION_PRIV_RO_USER_RO_EXEC |
                     پورٽ_MPU_REGION_عام_OIWTNOWA_SHARED ) );

    /* Priv: RX, Unpriv: No access for privileged functions. */
    ul_Region_ڊيگهائي = ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__;
    ul_Region_ڊيگهائي_Encoded = prv_Get_MPURegion_سائيز_Encoding( ul_Region_ڊيگهائي );
    vMPUSetRegion( پورٽ_PRIVILEGED_FLASH_REGION,
                   ( uint32_t ) __privileged_functions_start__,
                   ( ul_Region_ڊيگهائي_Encoded | پورٽ_MPU_REGION_ENABLE ),
                   ( پورٽ_MPU_REGION_PRIV_RO_USER_NA_EXEC |
                     پورٽ_MPU_REGION_عام_OIWTNOWA_SHARED ) );

    /* Priv: RW, Unpriv: No Access for privileged data. */
    ul_Region_ڊيگهائي = ( uint32_t ) __privileged_data_end__ - ( uint32_t ) __privileged_data_start__;
    ul_Region_ڊيگهائي_Encoded = prv_Get_MPURegion_سائيز_Encoding( ul_Region_ڊيگهائي );
    vMPUSetRegion( پورٽ_PRIVILEGED_RAM_REGION,
                   ( uint32_t ) __privileged_data_start__,
                   ( ul_Region_ڊيگهائي_Encoded | پورٽ_MPU_REGION_ENABLE ),
                   ( پورٽ_MPU_REGION_PRIV_RW_USER_NA_NOEXEC |
                     پورٽ_MPU_REGION_PRIV_RW_USER_NA_NOEXEC ) );

    /* Enable the MPU background region - it allows privileged operating modes
     * access to unmapped regions of memory without generating a fault. */
    vMPUEnableBackgroundRegion();

    /* After setting default regions, enable the MPU. */
    vMPUEnable();
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ساكن بنياد_Type_t prv_MPURegion_Authorizes_بفر( ثابت xMPU_REGION_REGISTERS * xTaskMPURegion,
                                                ثابت uint32_t ul_بفر_شروعات,
                                                ثابت uint32_t ul_بفر_ڊيگهائي,
                                                ثابت uint32_t ulAccessRequested )
{
    بنياد_Type_t xAccessGranted = pdFALSE;
    uint32_t ul_بفر_پڇاڙي;
    uint32_t ul_MPURegion_ڊيگهائي;
    uint32_t ul_MPURegion_شروعات;
    uint32_t ul_MPURegion_پڇاڙي;
    uint32_t ulMPURegionAccessPermissions;

    إذا( پورٽ_جوڙيو_UINT32_WILL_حد_کان_مٿي( ul_بفر_شروعات, ( ul_بفر_ڊيگهائي - 1UL ) ) == pdFALSE )
    {
        ul_بفر_پڇاڙي = ul_بفر_شروعات + ul_بفر_ڊيگهائي - 1UL;
        ul_MPURegion_ڊيگهائي = 2UL << ( xTaskMPURegion->ul_Region_سائيز >> 1UL );
        ul_MPURegion_شروعات = xTaskMPURegion->ul_Region_بنياد_پتو;
        ul_MPURegion_پڇاڙي = xTaskMPURegion->ul_Region_بنياد_پتو + ul_MPURegion_ڊيگهائي - 1UL;

        إذا( ( ul_بفر_شروعات >= ul_MPURegion_شروعات ) &&
            ( ul_بفر_پڇاڙي <= ul_MPURegion_پڇاڙي ) &&
            ( ul_بفر_شروعات <= ul_بفر_پڇاڙي ) )
        {
            ulMPURegionAccessPermissions = xTaskMPURegion->ulRegionAttribute & پورٽ_MPU_REGION_AP_BITMASK;

            إذا( ulAccessRequested == tskMPU_READ_PERMISSION ) /* RO. */
            {
                إذا( ( ulMPURegionAccessPermissions == پورٽ_MPU_REGION_PRIV_RW_USER_RO ) ||
                    ( ulMPURegionAccessPermissions == پورٽ_MPU_REGION_PRIV_RO_USER_RO ) ||
                    ( ulMPURegionAccessPermissions == پورٽ_MPU_REGION_PRIV_RW_USER_RW ) )

                {
                    xAccessGranted = pdTRUE;
                }
            }
            وإلا إذا( ( ulAccessRequested & tskMPU_WRITE_PERMISSION ) != 0UL ) /* W or RW. */
            {
                إذا( ulMPURegionAccessPermissions == پورٽ_MPU_REGION_PRIV_RW_USER_RW )
                {
                    xAccessGranted = pdTRUE;
                }
            }
        }
    }

    أرجع xAccessGranted;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
بنياد_Type_t x_پورٽ_Is_Authorized_منزل_Access_بفر( ثابت فراغ * pv_بفر,
                                            size_t x_بفر_ڊيگهائي,
                                            uint32_t ulAccessRequested )
{
    بنياد_Type_t xAccessGranted = pdFALSE;
    uint32_t ul_Region_اشاريو;
    xMPU_SETTINGS * xTaskMPUSettings = عدم;

    إذا( prv_پورٽ_Scheduler_Running == pdFALSE )
    {
        /* Grant access to all the memory before the scheduler is started. It is
         * necessary because there is no task running yet and therefore, we
         * cannot use the permissions of any task. */
        xAccessGranted = pdTRUE;
    }
    وإلا
    {
        /* Calling task's MPU settings. */
        xTaskMPUSettings = xTaskGetMPUSettings( عدم );

        إذا( ( xTaskMPUSettings->ulTaskFlags & پورٽ_TASK_IS_PRIVILEGED_FLAG ) == پورٽ_TASK_IS_PRIVILEGED_FLAG )
        {
            /* Privileged tasks have access to all the memory. */
            xAccessGranted = pdTRUE;
        }
        وإلا
        {
            لكل( ul_Region_اشاريو = 0x0UL; ul_Region_اشاريو < پورٽ_ڪل_انگ_REGIONS_اندريون_TCB; ul_Region_اشاريو++ )
            {
                xAccessGranted = prv_MPURegion_Authorizes_بفر( &( xTaskMPUSettings->xRegion[ ul_Region_اشاريو ] ),
                                                               ( uint32_t ) pv_بفر,
                                                               ( uint32_t ) x_بفر_ڊيگهائي,
                                                               ulAccessRequested );

                إذا( xAccessGranted == pdTRUE )
                {
                    اكسر;
                }
            }
        }
    }

    أرجع xAccessGranted;
}

/* ----------------------------------------------------------------------------------- */

#إذا( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
بنياد_Type_t x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( int32_t l_اندروني_اشاريو_جو_Kernel_Object )
{
    uint32_t ul_Access_Control_List_داخلا_اشاريو, ul_Access_Control_List_داخلا_ٻٽو_انگ;
    بنياد_Type_t xAccessGranted = pdFALSE;
    ثابت xMPU_SETTINGS * xTaskMpuSettings;

    إذا( prv_پورٽ_Scheduler_Running == pdFALSE )
    {
        /* Grant access to all the kernel objects before the scheduler
         * is started. It is necessary because there is no task running
         * yet and therefore, we cannot use the permissions of any
         * task. */
        xAccessGranted = pdTRUE;
    }
    وإلا
    {
        /* Calling task's MPU settings. */
        xTaskMpuSettings = xTaskGetMPUSettings( عدم );

        ul_Access_Control_List_داخلا_اشاريو = ( ( uint32_t ) l_اندروني_اشاريو_جو_Kernel_Object
                                          / پورٽ_ACL_داخلا_سائيز_بٽ );
        ul_Access_Control_List_داخلا_ٻٽو_انگ = ( ( uint32_t ) l_اندروني_اشاريو_جو_Kernel_Object
                                        % پورٽ_ACL_داخلا_سائيز_بٽ );

        إذا( ( xTaskMpuSettings->ulTaskFlags & پورٽ_TASK_IS_PRIVILEGED_FLAG ) == پورٽ_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        وإلا
        {
            إذا( ( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_داخلا_اشاريو ] ) &
                  ( 1U << ul_Access_Control_List_داخلا_ٻٽو_انگ ) ) != 0UL )
            {
                xAccessGranted = pdTRUE;
            }
        }
    }

    أرجع xAccessGranted;
}

#وإلا

/* PRIVILEGED_FUNCTION */
بنياد_Type_t x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( int32_t l_اندروني_اشاريو_جو_Kernel_Object )
{
    ( فراغ ) l_اندروني_اشاريو_جو_Kernel_Object;

    /* If Access Control List feature is not used, all the tasks have
     * access to all the kernel objects. */
    أرجع pdTRUE;
}

#جيڪڏهن_پورو /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

#إذا( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
فراغ v_پورٽ_Grant_Access_منزل_Kernel_Object( TaskHandle_t x_اندروني_Task_Handle,
                                     int32_t l_اندروني_اشاريو_جو_Kernel_Object )
{
    uint32_t ul_Access_Control_List_داخلا_اشاريو, ul_Access_Control_List_داخلا_ٻٽو_انگ;
    xMPU_SETTINGS * xTaskMpuSettings;

    ul_Access_Control_List_داخلا_اشاريو = ( ( uint32_t ) l_اندروني_اشاريو_جو_Kernel_Object
                                      / پورٽ_ACL_داخلا_سائيز_بٽ );
    ul_Access_Control_List_داخلا_ٻٽو_انگ = ( ( uint32_t ) l_اندروني_اشاريو_جو_Kernel_Object
                                    % پورٽ_ACL_داخلا_سائيز_بٽ );

    xTaskMpuSettings = xTaskGetMPUSettings( x_اندروني_Task_Handle );

    xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_داخلا_اشاريو ] |= ( 1U << ul_Access_Control_List_داخلا_ٻٽو_انگ );
}

#جيڪڏهن_پورو /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

#إذا( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
فراغ v_پورٽ_Revoke_Access_منزل_Kernel_Object( TaskHandle_t x_اندروني_Task_Handle,
                                      int32_t l_اندروني_اشاريو_جو_Kernel_Object )
{
    uint32_t ul_Access_Control_List_داخلا_اشاريو, ul_Access_Control_List_داخلا_ٻٽو_انگ;
    xMPU_SETTINGS * xTaskMpuSettings;

    ul_Access_Control_List_داخلا_اشاريو = ( ( uint32_t ) l_اندروني_اشاريو_جو_Kernel_Object
                                      / پورٽ_ACL_داخلا_سائيز_بٽ );
    ul_Access_Control_List_داخلا_ٻٽو_انگ = ( ( uint32_t ) l_اندروني_اشاريو_جو_Kernel_Object
                                    % پورٽ_ACL_داخلا_سائيز_بٽ );

    xTaskMpuSettings = xTaskGetMPUSettings( x_اندروني_Task_Handle );

    xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_داخلا_اشاريو ] &= ~( 1U << ul_Access_Control_List_داخلا_ٻٽو_انگ );
}

#جيڪڏهن_پورو /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

فراغ prvTaskExitError( فراغ )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ul_پورٽ_مداخلت_Nesting == ~0UL );

    لكل( ;; )
    {
    }
}

/* ----------------------------------------------------------------------------------- */

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    prv_پورٽ_Scheduler_Running = pdFALSE;

    /* Not implemented in this port. Artificially force an assert. */
    configASSERT( prv_پورٽ_Scheduler_Running == pdTRUE );
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
فراغ v_پورٽ_Enter_Critical( فراغ )
{
    پورٽ_DISABLE_INTERRUPTS();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert
     * if the critical nesting count is 1 to protect against recursive calls if
     * the assert function also uses a critical section. */
    إذا( ulCriticalNesting == 1 )
    {
        configASSERT( ul_پورٽ_مداخلت_Nesting == 0 );
    }
}
/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
فراغ v_پورٽ_Exit_Critical( فراغ )
{
    إذا( ulCriticalNesting > پورٽ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        إذا( ulCriticalNesting == پورٽ_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            پورٽ_ENABLE_INTERRUPTS();
        }
    }
}
/* ----------------------------------------------------------------------------------- */
