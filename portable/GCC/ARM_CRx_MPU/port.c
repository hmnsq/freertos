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
#شامل <stdint.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers. That should only be done when
 * task.h is included from an application file. */
#اگر_غیر_تعریف_شدہ MPU_WRAPPERS_INCLUDED_FROM_API_FILE
    #تعریف_کرو MPU_WRAPPERS_INCLUDED_FROM_API_FILE
#اگر_ختم /* MPU_WRAPPERS_INCLUDED_FROM_API_FILE */

/* Scheduler includes. */
#شامل "FreeRTOS.h"
#شامل "portmacro.h"
#شامل "task.h"
#شامل "mpu_syscall_numbers.h"

#تعریف_منسوخ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Max value that fits in a uint32_t type. */
#تعریف_کرو پورٹ_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کرو پورٹ_جوڑو_UINT32_WILL_حد_سے_تجاوز( a, b )    ( ( a ) > ( پورٹ_UINT32_MAX - ( b ) ) )
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
PRIVILEGED_ڈیٹا متلون UBaseType_t ulCriticalNesting = 0xFFFF;

/**
 * @brief Set to 1 to pend a context switch from an ISR.
 *
 * @ingroup Interrupt Management
 */
PRIVILEGED_ڈیٹا متلون UBaseType_t ul_پورٹ_Yield_Required = pdFALSE;

/**
 * @brief Interrupt nesting depth, used to count the number of interrupts to unwind.
 *
 * @ingroup Interrupt Management
 */
PRIVILEGED_ڈیٹا متلون UBaseType_t ul_پورٹ_مداخلت_Nesting = 0UL;

/**
 * @brief Variable to track whether or not the scheduler has been started.
 *
 * @ingroup Scheduler
 *
 * This is the port specific version of the xSchedulerRunning in tasks.c.
 */
PRIVILEGED_ڈیٹا ساکن بنیاد_Type_t prv_پورٹ_Scheduler_Running = pdFALSE;

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
PRIVILEGED_FUNCTION ساکن بنیاد_Type_t prv_MPURegion_Authorizes_بفر( ثابت xMPU_REGION_REGISTERS * xTaskMPURegion,
                                                                    ثابت uint32_t ul_بفر_آغاز,
                                                                    ثابت uint32_t ul_بفر_لمبائی,
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
PRIVILEGED_FUNCTION ساکن uint32_t prv_Get_MPURegion_سائز_Encoding( uint32_t ul_Actual_MPURegion_سائز );

/**
 * @brief Set up MPU.
 *
 * @ingroup MPU Control
 */
PRIVILEGED_FUNCTION ساکن خالی prv_تیاری_MPU( خالی );

/* -------------------------- Exported Function Declarations -------------------------- */

/**
 * @brief Enter critical section.
 *
 * @ingroup Critical Section
 */
PRIVILEGED_FUNCTION خالی v_پورٹ_Enter_Critical( خالی );

/**
 * @brief Exit critical section.
 *
 * @ingroup Critical Section
 */
PRIVILEGED_FUNCTION خالی v_پورٹ_Exit_Critical( خالی );

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
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters,
                                     بنیاد_Type_t x_تسلسل_Privileged,
                                     xMPU_SETTINGS * xMPUSettings )
{
    /* Setup the initial context of the task. The context is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */
    UBaseType_t ul_اشاریہ = CONTEXT_سائز - 1U;

    x_SYSTEM_CALL_ڈھیر_INFO * xSysCallInfo = تہی;

    اگر( x_تسلسل_Privileged == pdTRUE )
    {
        xMPUSettings->ulTaskFlags |= پورٹ_TASK_IS_PRIVILEGED_FLAG;
        /* Current Program Status Register (CPSR). */
        xMPUSettings->ulContext[ ul_اشاریہ ] = SYS_منوال;
    }
    ورنہ
    {
        xMPUSettings->ulTaskFlags &= ( ~پورٹ_TASK_IS_PRIVILEGED_FLAG );
        /* Current Program Status Register (CPSR). */
        xMPUSettings->ulContext[ ul_اشاریہ ] = USER_منوال;
    }

    اگر( ( ( uint32_t ) px_رمز & پورٹ_THUMB_منوال_پتہ ) != 0x0UL )
    {
        /* The task will cause the processor to start in THUMB state, set the
         * Thumb state bit in the CPSR. */
        xMPUSettings->ulContext[ ul_اشاریہ ] |= پورٹ_THUMB_منوال_ثنائی_ہندسہ;
    }

    ul_اشاریہ--;

    xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) px_رمز; /* PC. */
    ul_اشاریہ--;

    xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) پورٹ_TASK_RETURN_پتہ; /* LR. */
    ul_اشاریہ--;

    xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) px_چوٹی_کا_ڈھیر; /* SP. */
    ul_اشاریہ--;

    /* General Purpose Registers. */
    xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0x12121212; /* R12. */
    ul_اشاریہ--;
    xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0x11111111; /* R11. */
    ul_اشاریہ--;
    xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0x10101010; /* R10. */
    ul_اشاریہ--;
    xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0x09090909; /* R9. */
    ul_اشاریہ--;
    xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0x08080808; /* R8. */
    ul_اشاریہ--;
    xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0x07070707; /* R7. */
    ul_اشاریہ--;
    xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0x06060606; /* R6. */
    ul_اشاریہ--;
    xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0x05050505; /* R5. */
    ul_اشاریہ--;
    xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0x04040404; /* R4. */
    ul_اشاریہ--;
    xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0x03030303; /* R3. */
    ul_اشاریہ--;
    xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0x02020202; /* R2. */
    ul_اشاریہ--;
    xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0x01010101; /* R1. */
    ul_اشاریہ--;
    xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) pvParameters; /* R0. */
    ul_اشاریہ--;

    #اگر( پورٹ_ENABLE_FPU == 1 )
    {
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD0000015; /* S31. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD1500000; /* S30. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD0000014; /* S29. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD1400000; /* S28. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD0000013; /* S27. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD1300000; /* S26. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD0000012; /* S25. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD1200000; /* S24. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD0000011; /* S23. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD1100000; /* S22. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD0000010; /* S21. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD1000000; /* S20. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD0000009; /* S19. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD9000000; /* S18. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD0000008; /* S17. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD8000000; /* S16. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD0000007; /* S15. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD7000000; /* S14. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD0000006; /* S13. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD6000000; /* S12. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD0000005; /* S11. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD5000000; /* S10. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD0000004; /* S9. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD4000000; /* S8. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD0000003; /* S7. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD3000000; /* S6. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD0000002; /* S5. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD2000000; /* S4. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD0000001; /* S3. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD1000000; /* S2. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD0000000; /* S1. */
        ul_اشاریہ--;
        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0xD0000000; /* S0. */
        ul_اشاریہ--;

        xMPUSettings->ulContext[ ul_اشاریہ ] = ( ڈھیر_Type_t ) 0x00000000; /* FPSR. */
        ul_اشاریہ--;
    }
    #اگر_ختم /* portENABLE_FPU */

    /* The task will start with a critical nesting count of 0. */
    xMPUSettings->ulContext[ ul_اشاریہ ] = پورٹ_NO_CRITICAL_NESTING;

    /* Ensure that the system call stack is double word aligned. */
    xSysCallInfo = &( xMPUSettings->x_System_Call_ڈھیر_Info );
    xSysCallInfo->pul_System_Call_ڈھیر_اشارہ_گر = &( xSysCallInfo->ul_System_Call_ڈھیر_بفر[ config_SYSTEM_CALL_ڈھیر_سائز - 1U ] );
    xSysCallInfo->pul_System_Call_ڈھیر_اشارہ_گر = ( uint32_t * ) ( ( ( uint32_t ) ( xSysCallInfo->pul_System_Call_ڈھیر_اشارہ_گر ) ) &
                                                               ( ( uint32_t ) ( ~( پورٹ_BYTE_ALIGNMENT_نقاب ) ) ) );

    /* This is not NULL only for the duration of a system call. */
    xSysCallInfo->pul_Task_ڈھیر_اشارہ_گر = تہی;

    /* Set the System Call to return to vPortSystemCallExit. */
    xSysCallInfo->pul_System_Call_Exit_پتہ = ( uint32_t * ) ( &v_پورٹ_System_Call_Exit );

    /* Return the address where this task's context should be restored from. */
    واپس &( xMPUSettings->ulContext[ ul_اشاریہ ] );
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
خالی v_پورٹ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                ثابت ساخت x_حافظہ_REGION * ثابت xRegions,
                                ڈھیر_Type_t * px_Bottom_کا_ڈھیر,
                                uint32_t ul_ڈھیر_گہرائی )
{
    #اگر defined( __ARMCC_VERSION )
        /* Declaration when these variable are defined in code instead of being
         * exported from linker scripts. */
        خارجی uint32_t * __SRAM_segment_start__;
        خارجی uint32_t * __SRAM_segment_end__;
    #ورنہ
        /* Declaration when these variable are exported from linker scripts. */
        خارجی uint32_t __SRAM_segment_start__[];
        خارجی uint32_t __SRAM_segment_end__[];
    #اگر_ختم /* if defined( __ARMCC_VERSION ) */

    uint32_t ul_اشاریہ = 0x0;
    uint32_t ul_Region_لمبائی;
    uint32_t ul_Region_لمبائی_Encoded;
    uint32_t ul_Region_لمبائی_Decoded;

    اگر( xRegions == تہی )
    {
        /* No MPU regions are specified so allow access to all of the RAM. */
        ul_Region_لمبائی = ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__;
        ul_Region_لمبائی_Encoded = prv_Get_MPURegion_سائز_Encoding( ul_Region_لمبائی );
        ul_Region_لمبائی |= پورٹ_MPU_REGION_ENABLE;

        /* MPU Settings is zero'd out in the TCB before this function is called.
         * We, therefore, do not need to explicitly zero out unused MPU regions
         * in xMPUSettings. */
        ul_اشاریہ = پورٹ_ڈھیر_REGION;

        xMPUSettings->xRegion[ ul_اشاریہ ].ul_Region_بنیاد_پتہ = ( uint32_t ) __SRAM_segment_start__;
        xMPUSettings->xRegion[ ul_اشاریہ ].ul_Region_سائز = ( ul_Region_لمبائی_Encoded |
                                                          پورٹ_MPU_REGION_ENABLE );
        xMPUSettings->xRegion[ ul_اشاریہ ].ulRegionAttribute = ( پورٹ_MPU_REGION_PRIV_RW_USER_RW_NOEXEC |
                                                               پورٹ_MPU_REGION_معمول_OIWTNOWA_SHARED );
    }
    ورنہ
    {
        برائے( ul_اشاریہ = 0UL; ul_اشاریہ < پورٹ_عدد_CONFIGURABLE_REGIONS; ul_اشاریہ++ )
        {
            /* If a length has been provided, the region is in use. */
            اگر( ( xRegions[ ul_اشاریہ ] ).ul_لمبائی_اندر_بائٹیں > 0UL )
            {
                ul_Region_لمبائی = xRegions[ ul_اشاریہ ].ul_لمبائی_اندر_بائٹیں;
                ul_Region_لمبائی_Encoded = prv_Get_MPURegion_سائز_Encoding( ul_Region_لمبائی );

                /* MPU region base address must be aligned to the region size
                 * boundary. */
                ul_Region_لمبائی_Decoded = 2UL << ( ul_Region_لمبائی_Encoded >> 1UL );
                configASSERT( ( ( ( uint32_t ) xRegions[ ul_اشاریہ ].pv_بنیاد_پتہ ) % ( ul_Region_لمبائی_Decoded ) ) == 0UL );

                xMPUSettings->xRegion[ ul_اشاریہ ].ul_Region_بنیاد_پتہ = ( uint32_t ) xRegions[ ul_اشاریہ ].pv_بنیاد_پتہ;
                xMPUSettings->xRegion[ ul_اشاریہ ].ul_Region_سائز = ( ul_Region_لمبائی_Encoded |
                                                                  پورٹ_MPU_REGION_ENABLE );
                xMPUSettings->xRegion[ ul_اشاریہ ].ulRegionAttribute = xRegions[ ul_اشاریہ ].ulParameters;
            }
            ورنہ
            {
                xMPUSettings->xRegion[ ul_اشاریہ ].ul_Region_بنیاد_پتہ = 0x0UL;
                xMPUSettings->xRegion[ ul_اشاریہ ].ul_Region_سائز = 0x0UL;
                xMPUSettings->xRegion[ ul_اشاریہ ].ulRegionAttribute = 0x0UL;
            }
        }

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid. At all other
         * times the stack parameters will not be valid and it is assumed that the
         * stack region has already been configured. */
        اگر( ul_ڈھیر_گہرائی != 0x0UL )
        {
            ul_Region_لمبائی_Encoded = prv_Get_MPURegion_سائز_Encoding( ul_ڈھیر_گہرائی * ( uint32_t ) حجم( ڈھیر_Type_t ) );

            /* MPU region base address must be aligned to the region size
             * boundary. */
            ul_Region_لمبائی_Decoded = 2UL << ( ul_Region_لمبائی_Encoded >> 1UL );
            configASSERT( ( ( uint32_t ) px_Bottom_کا_ڈھیر % ( ul_Region_لمبائی_Decoded ) ) == 0U );

            ul_اشاریہ = پورٹ_ڈھیر_REGION;
            xMPUSettings->xRegion[ ul_اشاریہ ].ul_Region_بنیاد_پتہ = ( uint32_t ) px_Bottom_کا_ڈھیر;
            xMPUSettings->xRegion[ ul_اشاریہ ].ul_Region_سائز = ( ul_Region_لمبائی_Encoded |
                                                              پورٹ_MPU_REGION_ENABLE );
            xMPUSettings->xRegion[ ul_اشاریہ ].ulRegionAttribute = ( پورٹ_MPU_REGION_PRIV_RW_USER_RW_NOEXEC |
                                                                   پورٹ_MPU_REGION_معمول_OIWTNOWA_SHARED );
        }
    }
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
بنیاد_Type_t x_پورٹ_Is_Task_Privileged( خالی )
{
    بنیاد_Type_t xTaskIsPrivileged = pdFALSE;

    /* Calling task's MPU settings. */
    ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( تہی );

    اگر( ( xTaskMpuSettings->ulTaskFlags & پورٹ_TASK_IS_PRIVILEGED_FLAG ) == پورٹ_TASK_IS_PRIVILEGED_FLAG )
    {
        xTaskIsPrivileged = pdTRUE;
    }

    واپس xTaskIsPrivileged;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    /* Start the timer that generates the tick ISR. */
    config_تیاری_TICK_مداخلت();

    /* Configure MPU regions that are common to all tasks. */
    prv_تیاری_MPU();

    prv_پورٹ_Scheduler_Running = pdTRUE;

    /* Load the context of the first task. */
    v_پورٹ_آغاز_پہلا_Task();

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value. prvTaskExitError() is referenced to prevent a compiler
     * warning about it being defined but not referenced in the case that the user
     * defines their own exit address. */
    ( خالی ) prvTaskExitError();
    واپس pdFALSE;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ساکن uint32_t prv_Get_MPURegion_سائز_Encoding( uint32_t ul_Actual_MPURegion_سائز )
{
    uint32_t ul_Region_سائز, ul_Return_قدر = 4U;

    /* 32 bytes is the smallest valid region for Cortex R4 and R5 CPUs. */
    برائے( ul_Region_سائز = 0x20UL; ul_Return_قدر < 0x1FUL; ( ul_Region_سائز <<= 1UL ) )
    {
        اگر( ul_Actual_MPURegion_سائز <= ul_Region_سائز )
        {
            توڑو;
        }
        ورنہ
        {
            ul_Return_قدر++;
        }
    }

    /* Shift the code by one before returning so it can be written directly
     * into the correct bit position of the attribute register. */
    واپس ul_Return_قدر << 1UL;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ساکن خالی prv_تیاری_MPU( خالی )
{
#اگر defined( __ARMCC_VERSION )
    /* Declaration when these variable are defined in code. */
    /* Sections used for FLASH. */
    خارجی uint32_t * __FLASH_segment_start__;
    خارجی uint32_t * __FLASH_segment_end__;
    خارجی uint32_t * __privileged_functions_start__;
    خارجی uint32_t * __privileged_functions_end__;

    /* Sections used for RAM. */
    خارجی uint32_t * __SRAM_segment_start__;
    خارجی uint32_t * __SRAM_segment_end__;
    خارجی uint32_t * __privileged_data_start__;
    خارجی uint32_t * __privileged_data_end__;
#ورنہ
    /* Declaration when these variable are exported from linker scripts. */
    /* Sections used for FLASH. */
    خارجی uint32_t __FLASH_segment_start__[];
    خارجی uint32_t __FLASH_segment_end__[];
    خارجی uint32_t __privileged_functions_start__[];
    خارجی uint32_t __privileged_functions_end__[];

    /* Sections used for RAM. */
    خارجی uint32_t __SRAM_segment_start__[];
    خارجی uint32_t __SRAM_segment_end__[];
    خارجی uint32_t __privileged_data_start__[];
    خارجی uint32_t __privileged_data_end__[];
#اگر_ختم /* if defined( __ARMCC_VERSION ) */

    uint32_t ul_Region_لمبائی;
    uint32_t ul_Region_لمبائی_Encoded;

    /* Disable the MPU before programming it. */
    vMPUDisable();

    /* Priv: RX, Unpriv: RX for entire Flash. */
    ul_Region_لمبائی = ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__;
    ul_Region_لمبائی_Encoded = prv_Get_MPURegion_سائز_Encoding( ul_Region_لمبائی );
    vMPUSetRegion( پورٹ_UNPRIVILEGED_FLASH_REGION,
                   ( uint32_t ) __FLASH_segment_start__,
                   ( ul_Region_لمبائی_Encoded | پورٹ_MPU_REGION_ENABLE ),
                   ( پورٹ_MPU_REGION_PRIV_RO_USER_RO_EXEC |
                     پورٹ_MPU_REGION_معمول_OIWTNOWA_SHARED ) );

    /* Priv: RX, Unpriv: No access for privileged functions. */
    ul_Region_لمبائی = ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__;
    ul_Region_لمبائی_Encoded = prv_Get_MPURegion_سائز_Encoding( ul_Region_لمبائی );
    vMPUSetRegion( پورٹ_PRIVILEGED_FLASH_REGION,
                   ( uint32_t ) __privileged_functions_start__,
                   ( ul_Region_لمبائی_Encoded | پورٹ_MPU_REGION_ENABLE ),
                   ( پورٹ_MPU_REGION_PRIV_RO_USER_NA_EXEC |
                     پورٹ_MPU_REGION_معمول_OIWTNOWA_SHARED ) );

    /* Priv: RW, Unpriv: No Access for privileged data. */
    ul_Region_لمبائی = ( uint32_t ) __privileged_data_end__ - ( uint32_t ) __privileged_data_start__;
    ul_Region_لمبائی_Encoded = prv_Get_MPURegion_سائز_Encoding( ul_Region_لمبائی );
    vMPUSetRegion( پورٹ_PRIVILEGED_RAM_REGION,
                   ( uint32_t ) __privileged_data_start__,
                   ( ul_Region_لمبائی_Encoded | پورٹ_MPU_REGION_ENABLE ),
                   ( پورٹ_MPU_REGION_PRIV_RW_USER_NA_NOEXEC |
                     پورٹ_MPU_REGION_PRIV_RW_USER_NA_NOEXEC ) );

    /* Enable the MPU background region - it allows privileged operating modes
     * access to unmapped regions of memory without generating a fault. */
    vMPUEnableBackgroundRegion();

    /* After setting default regions, enable the MPU. */
    vMPUEnable();
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
ساکن بنیاد_Type_t prv_MPURegion_Authorizes_بفر( ثابت xMPU_REGION_REGISTERS * xTaskMPURegion,
                                                ثابت uint32_t ul_بفر_آغاز,
                                                ثابت uint32_t ul_بفر_لمبائی,
                                                ثابت uint32_t ulAccessRequested )
{
    بنیاد_Type_t xAccessGranted = pdFALSE;
    uint32_t ul_بفر_انتہا;
    uint32_t ul_MPURegion_لمبائی;
    uint32_t ul_MPURegion_آغاز;
    uint32_t ul_MPURegion_انتہا;
    uint32_t ulMPURegionAccessPermissions;

    اگر( پورٹ_جوڑو_UINT32_WILL_حد_سے_تجاوز( ul_بفر_آغاز, ( ul_بفر_لمبائی - 1UL ) ) == pdFALSE )
    {
        ul_بفر_انتہا = ul_بفر_آغاز + ul_بفر_لمبائی - 1UL;
        ul_MPURegion_لمبائی = 2UL << ( xTaskMPURegion->ul_Region_سائز >> 1UL );
        ul_MPURegion_آغاز = xTaskMPURegion->ul_Region_بنیاد_پتہ;
        ul_MPURegion_انتہا = xTaskMPURegion->ul_Region_بنیاد_پتہ + ul_MPURegion_لمبائی - 1UL;

        اگر( ( ul_بفر_آغاز >= ul_MPURegion_آغاز ) &&
            ( ul_بفر_انتہا <= ul_MPURegion_انتہا ) &&
            ( ul_بفر_آغاز <= ul_بفر_انتہا ) )
        {
            ulMPURegionAccessPermissions = xTaskMPURegion->ulRegionAttribute & پورٹ_MPU_REGION_AP_BITMASK;

            اگر( ulAccessRequested == tskMPU_READ_PERMISSION ) /* RO. */
            {
                اگر( ( ulMPURegionAccessPermissions == پورٹ_MPU_REGION_PRIV_RW_USER_RO ) ||
                    ( ulMPURegionAccessPermissions == پورٹ_MPU_REGION_PRIV_RO_USER_RO ) ||
                    ( ulMPURegionAccessPermissions == پورٹ_MPU_REGION_PRIV_RW_USER_RW ) )

                {
                    xAccessGranted = pdTRUE;
                }
            }
            ورنہ اگر( ( ulAccessRequested & tskMPU_WRITE_PERMISSION ) != 0UL ) /* W or RW. */
            {
                اگر( ulMPURegionAccessPermissions == پورٹ_MPU_REGION_PRIV_RW_USER_RW )
                {
                    xAccessGranted = pdTRUE;
                }
            }
        }
    }

    واپس xAccessGranted;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
بنیاد_Type_t x_پورٹ_Is_Authorized_مقصد_Access_بفر( ثابت خالی * pv_بفر,
                                            size_t x_بفر_لمبائی,
                                            uint32_t ulAccessRequested )
{
    بنیاد_Type_t xAccessGranted = pdFALSE;
    uint32_t ul_Region_اشاریہ;
    xMPU_SETTINGS * xTaskMPUSettings = تہی;

    اگر( prv_پورٹ_Scheduler_Running == pdFALSE )
    {
        /* Grant access to all the memory before the scheduler is started. It is
         * necessary because there is no task running yet and therefore, we
         * cannot use the permissions of any task. */
        xAccessGranted = pdTRUE;
    }
    ورنہ
    {
        /* Calling task's MPU settings. */
        xTaskMPUSettings = xTaskGetMPUSettings( تہی );

        اگر( ( xTaskMPUSettings->ulTaskFlags & پورٹ_TASK_IS_PRIVILEGED_FLAG ) == پورٹ_TASK_IS_PRIVILEGED_FLAG )
        {
            /* Privileged tasks have access to all the memory. */
            xAccessGranted = pdTRUE;
        }
        ورنہ
        {
            برائے( ul_Region_اشاریہ = 0x0UL; ul_Region_اشاریہ < پورٹ_کل_عدد_REGIONS_اندر_TCB; ul_Region_اشاریہ++ )
            {
                xAccessGranted = prv_MPURegion_Authorizes_بفر( &( xTaskMPUSettings->xRegion[ ul_Region_اشاریہ ] ),
                                                               ( uint32_t ) pv_بفر,
                                                               ( uint32_t ) x_بفر_لمبائی,
                                                               ulAccessRequested );

                اگر( xAccessGranted == pdTRUE )
                {
                    توڑو;
                }
            }
        }
    }

    واپس xAccessGranted;
}

/* ----------------------------------------------------------------------------------- */

#اگر( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
بنیاد_Type_t x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( int32_t l_اندرونی_اشاریہ_کا_Kernel_Object )
{
    uint32_t ul_Access_Control_List_اندراج_اشاریہ, ul_Access_Control_List_اندراج_ثنائی_ہندسہ;
    بنیاد_Type_t xAccessGranted = pdFALSE;
    ثابت xMPU_SETTINGS * xTaskMpuSettings;

    اگر( prv_پورٹ_Scheduler_Running == pdFALSE )
    {
        /* Grant access to all the kernel objects before the scheduler
         * is started. It is necessary because there is no task running
         * yet and therefore, we cannot use the permissions of any
         * task. */
        xAccessGranted = pdTRUE;
    }
    ورنہ
    {
        /* Calling task's MPU settings. */
        xTaskMpuSettings = xTaskGetMPUSettings( تہی );

        ul_Access_Control_List_اندراج_اشاریہ = ( ( uint32_t ) l_اندرونی_اشاریہ_کا_Kernel_Object
                                          / پورٹ_ACL_اندراج_سائز_بٹ );
        ul_Access_Control_List_اندراج_ثنائی_ہندسہ = ( ( uint32_t ) l_اندرونی_اشاریہ_کا_Kernel_Object
                                        % پورٹ_ACL_اندراج_سائز_بٹ );

        اگر( ( xTaskMpuSettings->ulTaskFlags & پورٹ_TASK_IS_PRIVILEGED_FLAG ) == پورٹ_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        ورنہ
        {
            اگر( ( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_اندراج_اشاریہ ] ) &
                  ( 1U << ul_Access_Control_List_اندراج_ثنائی_ہندسہ ) ) != 0UL )
            {
                xAccessGranted = pdTRUE;
            }
        }
    }

    واپس xAccessGranted;
}

#ورنہ

/* PRIVILEGED_FUNCTION */
بنیاد_Type_t x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( int32_t l_اندرونی_اشاریہ_کا_Kernel_Object )
{
    ( خالی ) l_اندرونی_اشاریہ_کا_Kernel_Object;

    /* If Access Control List feature is not used, all the tasks have
     * access to all the kernel objects. */
    واپس pdTRUE;
}

#اگر_ختم /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

#اگر( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
خالی v_پورٹ_Grant_Access_مقصد_Kernel_Object( TaskHandle_t x_اندرونی_Task_Handle,
                                     int32_t l_اندرونی_اشاریہ_کا_Kernel_Object )
{
    uint32_t ul_Access_Control_List_اندراج_اشاریہ, ul_Access_Control_List_اندراج_ثنائی_ہندسہ;
    xMPU_SETTINGS * xTaskMpuSettings;

    ul_Access_Control_List_اندراج_اشاریہ = ( ( uint32_t ) l_اندرونی_اشاریہ_کا_Kernel_Object
                                      / پورٹ_ACL_اندراج_سائز_بٹ );
    ul_Access_Control_List_اندراج_ثنائی_ہندسہ = ( ( uint32_t ) l_اندرونی_اشاریہ_کا_Kernel_Object
                                    % پورٹ_ACL_اندراج_سائز_بٹ );

    xTaskMpuSettings = xTaskGetMPUSettings( x_اندرونی_Task_Handle );

    xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_اندراج_اشاریہ ] |= ( 1U << ul_Access_Control_List_اندراج_ثنائی_ہندسہ );
}

#اگر_ختم /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

#اگر( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
خالی v_پورٹ_Revoke_Access_مقصد_Kernel_Object( TaskHandle_t x_اندرونی_Task_Handle,
                                      int32_t l_اندرونی_اشاریہ_کا_Kernel_Object )
{
    uint32_t ul_Access_Control_List_اندراج_اشاریہ, ul_Access_Control_List_اندراج_ثنائی_ہندسہ;
    xMPU_SETTINGS * xTaskMpuSettings;

    ul_Access_Control_List_اندراج_اشاریہ = ( ( uint32_t ) l_اندرونی_اشاریہ_کا_Kernel_Object
                                      / پورٹ_ACL_اندراج_سائز_بٹ );
    ul_Access_Control_List_اندراج_ثنائی_ہندسہ = ( ( uint32_t ) l_اندرونی_اشاریہ_کا_Kernel_Object
                                    % پورٹ_ACL_اندراج_سائز_بٹ );

    xTaskMpuSettings = xTaskGetMPUSettings( x_اندرونی_Task_Handle );

    xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_اندراج_اشاریہ ] &= ~( 1U << ul_Access_Control_List_اندراج_ثنائی_ہندسہ );
}

#اگر_ختم /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

خالی prvTaskExitError( خالی )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ul_پورٹ_مداخلت_Nesting == ~0UL );

    برائے( ;; )
    {
    }
}

/* ----------------------------------------------------------------------------------- */

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    prv_پورٹ_Scheduler_Running = pdFALSE;

    /* Not implemented in this port. Artificially force an assert. */
    configASSERT( prv_پورٹ_Scheduler_Running == pdTRUE );
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
خالی v_پورٹ_Enter_Critical( خالی )
{
    پورٹ_DISABLE_INTERRUPTS();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert
     * if the critical nesting count is 1 to protect against recursive calls if
     * the assert function also uses a critical section. */
    اگر( ulCriticalNesting == 1 )
    {
        configASSERT( ul_پورٹ_مداخلت_Nesting == 0 );
    }
}
/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
خالی v_پورٹ_Exit_Critical( خالی )
{
    اگر( ulCriticalNesting > پورٹ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        اگر( ulCriticalNesting == پورٹ_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            پورٹ_ENABLE_INTERRUPTS();
        }
    }
}
/* ----------------------------------------------------------------------------------- */
