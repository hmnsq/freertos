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
#अन्तर्भाव <stdint.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers. That should only be done when
 * task.h is included from an application file. */
#यदि_अपरिभाषितम् MPU_WRAPPERS_INCLUDED_FROM_API_FILE
    #परिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE
#यदि_अन्तः /* MPU_WRAPPERS_INCLUDED_FROM_API_FILE */

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "portmacro.h"
#अन्तर्भाव "task.h"
#अन्तर्भाव "mpu_syscall_numbers.h"

#अपरिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Max value that fits in a uint32_t type. */
#परिभाषय पत्तनम्_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#परिभाषय पत्तनम्_सङ्कलय_UINT32_WILL_अतिप्रवाहः( a, b )    ( ( a ) > ( पत्तनम्_UINT32_MAX - ( b ) ) )
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
PRIVILEGED_दत्त चञ्चल UBaseType_t ulCriticalNesting = 0xFFFF;

/**
 * @brief Set to 1 to pend a context switch from an ISR.
 *
 * @ingroup Interrupt Management
 */
PRIVILEGED_दत्त चञ्चल UBaseType_t ul_पत्तनम्_Yield_Required = pdFALSE;

/**
 * @brief Interrupt nesting depth, used to count the number of interrupts to unwind.
 *
 * @ingroup Interrupt Management
 */
PRIVILEGED_दत्त चञ्चल UBaseType_t ul_पत्तनम्_व्यवधानम्_Nesting = 0UL;

/**
 * @brief Variable to track whether or not the scheduler has been started.
 *
 * @ingroup Scheduler
 *
 * This is the port specific version of the xSchedulerRunning in tasks.c.
 */
PRIVILEGED_दत्त स्थिर आधारः_Type_t prv_पत्तनम्_Scheduler_Running = pdFALSE;

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
PRIVILEGED_FUNCTION स्थिर आधारः_Type_t prv_MPURegion_Authorizes_बफर( ध्रुव xMPU_REGION_REGISTERS * xTaskMPURegion,
                                                                    ध्रुव uint32_t ul_बफर_Start,
                                                                    ध्रुव uint32_t ul_बफर_दीर्घता,
                                                                    ध्रुव uint32_t ulAccessRequested );

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
PRIVILEGED_FUNCTION स्थिर uint32_t prv_Get_MPURegion_आकार_Encoding( uint32_t ul_Actual_MPURegion_आकार );

/**
 * @brief Set up MPU.
 *
 * @ingroup MPU Control
 */
PRIVILEGED_FUNCTION स्थिर शून्य prv_सज्जता_MPU( शून्य );

/* -------------------------- Exported Function Declarations -------------------------- */

/**
 * @brief Enter critical section.
 *
 * @ingroup Critical Section
 */
PRIVILEGED_FUNCTION शून्य v_पत्तनम्_Enter_Critical( शून्य );

/**
 * @brief Exit critical section.
 *
 * @ingroup Critical Section
 */
PRIVILEGED_FUNCTION शून्य v_पत्तनम्_Exit_Critical( शून्य );

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
राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters,
                                     आधारः_Type_t x_सततम्_Privileged,
                                     xMPU_SETTINGS * xMPUSettings )
{
    /* Setup the initial context of the task. The context is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */
    UBaseType_t ul_सूचकांक = CONTEXT_आकार - 1U;

    x_SYSTEM_CALL_राशिः_INFO * xSysCallInfo = रिक्त;

    यदि( x_सततम्_Privileged == pdTRUE )
    {
        xMPUSettings->ulTaskFlags |= पत्तनम्_TASK_IS_PRIVILEGED_FLAG;
        /* Current Program Status Register (CPSR). */
        xMPUSettings->ulContext[ ul_सूचकांक ] = SYS_बहुलकम्;
    }
    अन्यथा
    {
        xMPUSettings->ulTaskFlags &= ( ~पत्तनम्_TASK_IS_PRIVILEGED_FLAG );
        /* Current Program Status Register (CPSR). */
        xMPUSettings->ulContext[ ul_सूचकांक ] = USER_बहुलकम्;
    }

    यदि( ( ( uint32_t ) px_संहिता & पत्तनम्_THUMB_बहुलकम्_स्थानाङ्कः ) != 0x0UL )
    {
        /* The task will cause the processor to start in THUMB state, set the
         * Thumb state bit in the CPSR. */
        xMPUSettings->ulContext[ ul_सूचकांक ] |= पत्तनम्_THUMB_बहुलकम्_BIT;
    }

    ul_सूचकांक--;

    xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) px_संहिता; /* PC. */
    ul_सूचकांक--;

    xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) पत्तनम्_TASK_RETURN_स्थानाङ्कः; /* LR. */
    ul_सूचकांक--;

    xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) px_शिखरम्_सम्बन्धि_राशिः; /* SP. */
    ul_सूचकांक--;

    /* General Purpose Registers. */
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0x12121212; /* R12. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0x11111111; /* R11. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0x10101010; /* R10. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0x09090909; /* R9. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0x08080808; /* R8. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0x07070707; /* R7. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0x06060606; /* R6. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0x05050505; /* R5. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0x04040404; /* R4. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0x03030303; /* R3. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0x02020202; /* R2. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0x01010101; /* R1. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) pvParameters; /* R0. */
    ul_सूचकांक--;

    #यदि( पत्तनम्_ENABLE_FPU == 1 )
    {
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD0000015; /* S31. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD1500000; /* S30. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD0000014; /* S29. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD1400000; /* S28. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD0000013; /* S27. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD1300000; /* S26. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD0000012; /* S25. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD1200000; /* S24. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD0000011; /* S23. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD1100000; /* S22. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD0000010; /* S21. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD1000000; /* S20. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD0000009; /* S19. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD9000000; /* S18. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD0000008; /* S17. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD8000000; /* S16. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD0000007; /* S15. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD7000000; /* S14. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD0000006; /* S13. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD6000000; /* S12. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD0000005; /* S11. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD5000000; /* S10. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD0000004; /* S9. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD4000000; /* S8. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD0000003; /* S7. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD3000000; /* S6. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD0000002; /* S5. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD2000000; /* S4. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD0000001; /* S3. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD1000000; /* S2. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD0000000; /* S1. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0xD0000000; /* S0. */
        ul_सूचकांक--;

        xMPUSettings->ulContext[ ul_सूचकांक ] = ( राशिः_Type_t ) 0x00000000; /* FPSR. */
        ul_सूचकांक--;
    }
    #यदि_अन्तः /* portENABLE_FPU */

    /* The task will start with a critical nesting count of 0. */
    xMPUSettings->ulContext[ ul_सूचकांक ] = पत्तनम्_NO_CRITICAL_NESTING;

    /* Ensure that the system call stack is double word aligned. */
    xSysCallInfo = &( xMPUSettings->x_System_Call_राशिः_Info );
    xSysCallInfo->pul_System_Call_राशिः_Pointer = &( xSysCallInfo->ul_System_Call_राशिः_बफर[ config_SYSTEM_CALL_राशिः_आकार - 1U ] );
    xSysCallInfo->pul_System_Call_राशिः_Pointer = ( uint32_t * ) ( ( ( uint32_t ) ( xSysCallInfo->pul_System_Call_राशिः_Pointer ) ) &
                                                               ( ( uint32_t ) ( ~( पत्तनम्_BYTE_ALIGNMENT_आवरणम् ) ) ) );

    /* This is not NULL only for the duration of a system call. */
    xSysCallInfo->pul_Task_राशिः_Pointer = रिक्त;

    /* Set the System Call to return to vPortSystemCallExit. */
    xSysCallInfo->pul_System_Call_Exit_स्थानाङ्कः = ( uint32_t * ) ( &v_पत्तनम्_System_Call_Exit );

    /* Return the address where this task's context should be restored from. */
    प्रत्यागम &( xMPUSettings->ulContext[ ul_सूचकांक ] );
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
शून्य v_पत्तनम्_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                ध्रुव संरचना x_स्मृतिः_REGION * ध्रुव xRegions,
                                राशिः_Type_t * px_Bottom_सम्बन्धि_राशिः,
                                uint32_t ul_राशिः_गभीरता )
{
    #यदि defined( __ARMCC_VERSION )
        /* Declaration when these variable are defined in code instead of being
         * exported from linker scripts. */
        बाह्य uint32_t * __SRAM_segment_start__;
        बाह्य uint32_t * __SRAM_segment_end__;
    #अन्यथा
        /* Declaration when these variable are exported from linker scripts. */
        बाह्य uint32_t __SRAM_segment_start__[];
        बाह्य uint32_t __SRAM_segment_end__[];
    #यदि_अन्तः /* if defined( __ARMCC_VERSION ) */

    uint32_t ul_सूचकांक = 0x0;
    uint32_t ul_Region_दीर्घता;
    uint32_t ul_Region_दीर्घता_Encoded;
    uint32_t ul_Region_दीर्घता_Decoded;

    यदि( xRegions == रिक्त )
    {
        /* No MPU regions are specified so allow access to all of the RAM. */
        ul_Region_दीर्घता = ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__;
        ul_Region_दीर्घता_Encoded = prv_Get_MPURegion_आकार_Encoding( ul_Region_दीर्घता );
        ul_Region_दीर्घता |= पत्तनम्_MPU_REGION_ENABLE;

        /* MPU Settings is zero'd out in the TCB before this function is called.
         * We, therefore, do not need to explicitly zero out unused MPU regions
         * in xMPUSettings. */
        ul_सूचकांक = पत्तनम्_राशिः_REGION;

        xMPUSettings->xRegion[ ul_सूचकांक ].ul_Region_आधारः_स्थानाङ्कः = ( uint32_t ) __SRAM_segment_start__;
        xMPUSettings->xRegion[ ul_सूचकांक ].ul_Region_आकार = ( ul_Region_दीर्घता_Encoded |
                                                          पत्तनम्_MPU_REGION_ENABLE );
        xMPUSettings->xRegion[ ul_सूचकांक ].ulRegionAttribute = ( पत्तनम्_MPU_REGION_PRIV_RW_USER_RW_NOEXEC |
                                                               पत्तनम्_MPU_REGION_प्रसामान्यम्_OIWTNOWA_SHARED );
    }
    अन्यथा
    {
        प्रति( ul_सूचकांक = 0UL; ul_सूचकांक < पत्तनम्_अङ्कः_CONFIGURABLE_REGIONS; ul_सूचकांक++ )
        {
            /* If a length has been provided, the region is in use. */
            यदि( ( xRegions[ ul_सूचकांक ] ).ul_दीर्घता_अन्तर्_अष्टकानि > 0UL )
            {
                ul_Region_दीर्घता = xRegions[ ul_सूचकांक ].ul_दीर्घता_अन्तर्_अष्टकानि;
                ul_Region_दीर्घता_Encoded = prv_Get_MPURegion_आकार_Encoding( ul_Region_दीर्घता );

                /* MPU region base address must be aligned to the region size
                 * boundary. */
                ul_Region_दीर्घता_Decoded = 2UL << ( ul_Region_दीर्घता_Encoded >> 1UL );
                configASSERT( ( ( ( uint32_t ) xRegions[ ul_सूचकांक ].pv_आधारः_स्थानाङ्कः ) % ( ul_Region_दीर्घता_Decoded ) ) == 0UL );

                xMPUSettings->xRegion[ ul_सूचकांक ].ul_Region_आधारः_स्थानाङ्कः = ( uint32_t ) xRegions[ ul_सूचकांक ].pv_आधारः_स्थानाङ्कः;
                xMPUSettings->xRegion[ ul_सूचकांक ].ul_Region_आकार = ( ul_Region_दीर्घता_Encoded |
                                                                  पत्तनम्_MPU_REGION_ENABLE );
                xMPUSettings->xRegion[ ul_सूचकांक ].ulRegionAttribute = xRegions[ ul_सूचकांक ].ulParameters;
            }
            अन्यथा
            {
                xMPUSettings->xRegion[ ul_सूचकांक ].ul_Region_आधारः_स्थानाङ्कः = 0x0UL;
                xMPUSettings->xRegion[ ul_सूचकांक ].ul_Region_आकार = 0x0UL;
                xMPUSettings->xRegion[ ul_सूचकांक ].ulRegionAttribute = 0x0UL;
            }
        }

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid. At all other
         * times the stack parameters will not be valid and it is assumed that the
         * stack region has already been configured. */
        यदि( ul_राशिः_गभीरता != 0x0UL )
        {
            ul_Region_दीर्घता_Encoded = prv_Get_MPURegion_आकार_Encoding( ul_राशिः_गभीरता * ( uint32_t ) परिमाण( राशिः_Type_t ) );

            /* MPU region base address must be aligned to the region size
             * boundary. */
            ul_Region_दीर्घता_Decoded = 2UL << ( ul_Region_दीर्घता_Encoded >> 1UL );
            configASSERT( ( ( uint32_t ) px_Bottom_सम्बन्धि_राशिः % ( ul_Region_दीर्घता_Decoded ) ) == 0U );

            ul_सूचकांक = पत्तनम्_राशिः_REGION;
            xMPUSettings->xRegion[ ul_सूचकांक ].ul_Region_आधारः_स्थानाङ्कः = ( uint32_t ) px_Bottom_सम्बन्धि_राशिः;
            xMPUSettings->xRegion[ ul_सूचकांक ].ul_Region_आकार = ( ul_Region_दीर्घता_Encoded |
                                                              पत्तनम्_MPU_REGION_ENABLE );
            xMPUSettings->xRegion[ ul_सूचकांक ].ulRegionAttribute = ( पत्तनम्_MPU_REGION_PRIV_RW_USER_RW_NOEXEC |
                                                                   पत्तनम्_MPU_REGION_प्रसामान्यम्_OIWTNOWA_SHARED );
        }
    }
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
आधारः_Type_t x_पत्तनम्_Is_Task_Privileged( शून्य )
{
    आधारः_Type_t xTaskIsPrivileged = pdFALSE;

    /* Calling task's MPU settings. */
    ध्रुव xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( रिक्त );

    यदि( ( xTaskMpuSettings->ulTaskFlags & पत्तनम्_TASK_IS_PRIVILEGED_FLAG ) == पत्तनम्_TASK_IS_PRIVILEGED_FLAG )
    {
        xTaskIsPrivileged = pdTRUE;
    }

    प्रत्यागम xTaskIsPrivileged;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    /* Start the timer that generates the tick ISR. */
    config_सज्जता_TICK_व्यवधानम्();

    /* Configure MPU regions that are common to all tasks. */
    prv_सज्जता_MPU();

    prv_पत्तनम्_Scheduler_Running = pdTRUE;

    /* Load the context of the first task. */
    v_पत्तनम्_Start_First_Task();

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value. prvTaskExitError() is referenced to prevent a compiler
     * warning about it being defined but not referenced in the case that the user
     * defines their own exit address. */
    ( शून्य ) prvTaskExitError();
    प्रत्यागम pdFALSE;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
स्थिर uint32_t prv_Get_MPURegion_आकार_Encoding( uint32_t ul_Actual_MPURegion_आकार )
{
    uint32_t ul_Region_आकार, ul_Return_मानम् = 4U;

    /* 32 bytes is the smallest valid region for Cortex R4 and R5 CPUs. */
    प्रति( ul_Region_आकार = 0x20UL; ul_Return_मानम् < 0x1FUL; ( ul_Region_आकार <<= 1UL ) )
    {
        यदि( ul_Actual_MPURegion_आकार <= ul_Region_आकार )
        {
            भङ्ग;
        }
        अन्यथा
        {
            ul_Return_मानम्++;
        }
    }

    /* Shift the code by one before returning so it can be written directly
     * into the correct bit position of the attribute register. */
    प्रत्यागम ul_Return_मानम् << 1UL;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
स्थिर शून्य prv_सज्जता_MPU( शून्य )
{
#यदि defined( __ARMCC_VERSION )
    /* Declaration when these variable are defined in code. */
    /* Sections used for FLASH. */
    बाह्य uint32_t * __FLASH_segment_start__;
    बाह्य uint32_t * __FLASH_segment_end__;
    बाह्य uint32_t * __privileged_functions_start__;
    बाह्य uint32_t * __privileged_functions_end__;

    /* Sections used for RAM. */
    बाह्य uint32_t * __SRAM_segment_start__;
    बाह्य uint32_t * __SRAM_segment_end__;
    बाह्य uint32_t * __privileged_data_start__;
    बाह्य uint32_t * __privileged_data_end__;
#अन्यथा
    /* Declaration when these variable are exported from linker scripts. */
    /* Sections used for FLASH. */
    बाह्य uint32_t __FLASH_segment_start__[];
    बाह्य uint32_t __FLASH_segment_end__[];
    बाह्य uint32_t __privileged_functions_start__[];
    बाह्य uint32_t __privileged_functions_end__[];

    /* Sections used for RAM. */
    बाह्य uint32_t __SRAM_segment_start__[];
    बाह्य uint32_t __SRAM_segment_end__[];
    बाह्य uint32_t __privileged_data_start__[];
    बाह्य uint32_t __privileged_data_end__[];
#यदि_अन्तः /* if defined( __ARMCC_VERSION ) */

    uint32_t ul_Region_दीर्घता;
    uint32_t ul_Region_दीर्घता_Encoded;

    /* Disable the MPU before programming it. */
    vMPUDisable();

    /* Priv: RX, Unpriv: RX for entire Flash. */
    ul_Region_दीर्घता = ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__;
    ul_Region_दीर्घता_Encoded = prv_Get_MPURegion_आकार_Encoding( ul_Region_दीर्घता );
    vMPUSetRegion( पत्तनम्_UNPRIVILEGED_FLASH_REGION,
                   ( uint32_t ) __FLASH_segment_start__,
                   ( ul_Region_दीर्घता_Encoded | पत्तनम्_MPU_REGION_ENABLE ),
                   ( पत्तनम्_MPU_REGION_PRIV_RO_USER_RO_EXEC |
                     पत्तनम्_MPU_REGION_प्रसामान्यम्_OIWTNOWA_SHARED ) );

    /* Priv: RX, Unpriv: No access for privileged functions. */
    ul_Region_दीर्घता = ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__;
    ul_Region_दीर्घता_Encoded = prv_Get_MPURegion_आकार_Encoding( ul_Region_दीर्घता );
    vMPUSetRegion( पत्तनम्_PRIVILEGED_FLASH_REGION,
                   ( uint32_t ) __privileged_functions_start__,
                   ( ul_Region_दीर्घता_Encoded | पत्तनम्_MPU_REGION_ENABLE ),
                   ( पत्तनम्_MPU_REGION_PRIV_RO_USER_NA_EXEC |
                     पत्तनम्_MPU_REGION_प्रसामान्यम्_OIWTNOWA_SHARED ) );

    /* Priv: RW, Unpriv: No Access for privileged data. */
    ul_Region_दीर्घता = ( uint32_t ) __privileged_data_end__ - ( uint32_t ) __privileged_data_start__;
    ul_Region_दीर्घता_Encoded = prv_Get_MPURegion_आकार_Encoding( ul_Region_दीर्घता );
    vMPUSetRegion( पत्तनम्_PRIVILEGED_RAM_REGION,
                   ( uint32_t ) __privileged_data_start__,
                   ( ul_Region_दीर्घता_Encoded | पत्तनम्_MPU_REGION_ENABLE ),
                   ( पत्तनम्_MPU_REGION_PRIV_RW_USER_NA_NOEXEC |
                     पत्तनम्_MPU_REGION_PRIV_RW_USER_NA_NOEXEC ) );

    /* Enable the MPU background region - it allows privileged operating modes
     * access to unmapped regions of memory without generating a fault. */
    vMPUEnableBackgroundRegion();

    /* After setting default regions, enable the MPU. */
    vMPUEnable();
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
स्थिर आधारः_Type_t prv_MPURegion_Authorizes_बफर( ध्रुव xMPU_REGION_REGISTERS * xTaskMPURegion,
                                                ध्रुव uint32_t ul_बफर_Start,
                                                ध्रुव uint32_t ul_बफर_दीर्घता,
                                                ध्रुव uint32_t ulAccessRequested )
{
    आधारः_Type_t xAccessGranted = pdFALSE;
    uint32_t ul_बफर_अन्तः;
    uint32_t ul_MPURegion_दीर्घता;
    uint32_t ulMPURegionStart;
    uint32_t ul_MPURegion_अन्तः;
    uint32_t ulMPURegionAccessPermissions;

    यदि( पत्तनम्_सङ्कलय_UINT32_WILL_अतिप्रवाहः( ul_बफर_Start, ( ul_बफर_दीर्घता - 1UL ) ) == pdFALSE )
    {
        ul_बफर_अन्तः = ul_बफर_Start + ul_बफर_दीर्घता - 1UL;
        ul_MPURegion_दीर्घता = 2UL << ( xTaskMPURegion->ul_Region_आकार >> 1UL );
        ulMPURegionStart = xTaskMPURegion->ul_Region_आधारः_स्थानाङ्कः;
        ul_MPURegion_अन्तः = xTaskMPURegion->ul_Region_आधारः_स्थानाङ्कः + ul_MPURegion_दीर्घता - 1UL;

        यदि( ( ul_बफर_Start >= ulMPURegionStart ) &&
            ( ul_बफर_अन्तः <= ul_MPURegion_अन्तः ) &&
            ( ul_बफर_Start <= ul_बफर_अन्तः ) )
        {
            ulMPURegionAccessPermissions = xTaskMPURegion->ulRegionAttribute & पत्तनम्_MPU_REGION_AP_BITMASK;

            यदि( ulAccessRequested == tskMPU_READ_PERMISSION ) /* RO. */
            {
                यदि( ( ulMPURegionAccessPermissions == पत्तनम्_MPU_REGION_PRIV_RW_USER_RO ) ||
                    ( ulMPURegionAccessPermissions == पत्तनम्_MPU_REGION_PRIV_RO_USER_RO ) ||
                    ( ulMPURegionAccessPermissions == पत्तनम्_MPU_REGION_PRIV_RW_USER_RW ) )

                {
                    xAccessGranted = pdTRUE;
                }
            }
            अन्यथा यदि( ( ulAccessRequested & tskMPU_WRITE_PERMISSION ) != 0UL ) /* W or RW. */
            {
                यदि( ulMPURegionAccessPermissions == पत्तनम्_MPU_REGION_PRIV_RW_USER_RW )
                {
                    xAccessGranted = pdTRUE;
                }
            }
        }
    }

    प्रत्यागम xAccessGranted;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
आधारः_Type_t x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( ध्रुव शून्य * pv_बफर,
                                            size_t x_बफर_दीर्घता,
                                            uint32_t ulAccessRequested )
{
    आधारः_Type_t xAccessGranted = pdFALSE;
    uint32_t ul_Region_सूचकांक;
    xMPU_SETTINGS * xTaskMPUSettings = रिक्त;

    यदि( prv_पत्तनम्_Scheduler_Running == pdFALSE )
    {
        /* Grant access to all the memory before the scheduler is started. It is
         * necessary because there is no task running yet and therefore, we
         * cannot use the permissions of any task. */
        xAccessGranted = pdTRUE;
    }
    अन्यथा
    {
        /* Calling task's MPU settings. */
        xTaskMPUSettings = xTaskGetMPUSettings( रिक्त );

        यदि( ( xTaskMPUSettings->ulTaskFlags & पत्तनम्_TASK_IS_PRIVILEGED_FLAG ) == पत्तनम्_TASK_IS_PRIVILEGED_FLAG )
        {
            /* Privileged tasks have access to all the memory. */
            xAccessGranted = pdTRUE;
        }
        अन्यथा
        {
            प्रति( ul_Region_सूचकांक = 0x0UL; ul_Region_सूचकांक < पत्तनम्_योग_अङ्कः_REGIONS_अन्तर्_TCB; ul_Region_सूचकांक++ )
            {
                xAccessGranted = prv_MPURegion_Authorizes_बफर( &( xTaskMPUSettings->xRegion[ ul_Region_सूचकांक ] ),
                                                               ( uint32_t ) pv_बफर,
                                                               ( uint32_t ) x_बफर_दीर्घता,
                                                               ulAccessRequested );

                यदि( xAccessGranted == pdTRUE )
                {
                    भङ्ग;
                }
            }
        }
    }

    प्रत्यागम xAccessGranted;
}

/* ----------------------------------------------------------------------------------- */

#यदि( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
आधारः_Type_t x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( int32_t l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object )
{
    uint32_t ul_Access_Control_List_प्रविष्टिः_सूचकांक, ul_Access_Control_List_प्रविष्टिः_Bit;
    आधारः_Type_t xAccessGranted = pdFALSE;
    ध्रुव xMPU_SETTINGS * xTaskMpuSettings;

    यदि( prv_पत्तनम्_Scheduler_Running == pdFALSE )
    {
        /* Grant access to all the kernel objects before the scheduler
         * is started. It is necessary because there is no task running
         * yet and therefore, we cannot use the permissions of any
         * task. */
        xAccessGranted = pdTRUE;
    }
    अन्यथा
    {
        /* Calling task's MPU settings. */
        xTaskMpuSettings = xTaskGetMPUSettings( रिक्त );

        ul_Access_Control_List_प्रविष्टिः_सूचकांक = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object
                                          / पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );
        ul_Access_Control_List_प्रविष्टिः_Bit = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object
                                        % पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );

        यदि( ( xTaskMpuSettings->ulTaskFlags & पत्तनम्_TASK_IS_PRIVILEGED_FLAG ) == पत्तनम्_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        अन्यथा
        {
            यदि( ( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_प्रविष्टिः_सूचकांक ] ) &
                  ( 1U << ul_Access_Control_List_प्रविष्टिः_Bit ) ) != 0UL )
            {
                xAccessGranted = pdTRUE;
            }
        }
    }

    प्रत्यागम xAccessGranted;
}

#अन्यथा

/* PRIVILEGED_FUNCTION */
आधारः_Type_t x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( int32_t l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object )
{
    ( शून्य ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object;

    /* If Access Control List feature is not used, all the tasks have
     * access to all the kernel objects. */
    प्रत्यागम pdTRUE;
}

#यदि_अन्तः /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

#यदि( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
शून्य v_पत्तनम्_Grant_Access_गन्तव्यम्_Kernel_Object( TaskHandle_t x_आन्तरिकम्_Task_Handle,
                                     int32_t l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object )
{
    uint32_t ul_Access_Control_List_प्रविष्टिः_सूचकांक, ul_Access_Control_List_प्रविष्टिः_Bit;
    xMPU_SETTINGS * xTaskMpuSettings;

    ul_Access_Control_List_प्रविष्टिः_सूचकांक = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object
                                      / पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );
    ul_Access_Control_List_प्रविष्टिः_Bit = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object
                                    % पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );

    xTaskMpuSettings = xTaskGetMPUSettings( x_आन्तरिकम्_Task_Handle );

    xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_प्रविष्टिः_सूचकांक ] |= ( 1U << ul_Access_Control_List_प्रविष्टिः_Bit );
}

#यदि_अन्तः /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

#यदि( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
शून्य v_पत्तनम्_Revoke_Access_गन्तव्यम्_Kernel_Object( TaskHandle_t x_आन्तरिकम्_Task_Handle,
                                      int32_t l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object )
{
    uint32_t ul_Access_Control_List_प्रविष्टिः_सूचकांक, ul_Access_Control_List_प्रविष्टिः_Bit;
    xMPU_SETTINGS * xTaskMpuSettings;

    ul_Access_Control_List_प्रविष्टिः_सूचकांक = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object
                                      / पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );
    ul_Access_Control_List_प्रविष्टिः_Bit = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object
                                    % पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );

    xTaskMpuSettings = xTaskGetMPUSettings( x_आन्तरिकम्_Task_Handle );

    xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_प्रविष्टिः_सूचकांक ] &= ~( 1U << ul_Access_Control_List_प्रविष्टिः_Bit );
}

#यदि_अन्तः /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

शून्य prvTaskExitError( शून्य )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ul_पत्तनम्_व्यवधानम्_Nesting == ~0UL );

    प्रति( ;; )
    {
    }
}

/* ----------------------------------------------------------------------------------- */

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    prv_पत्तनम्_Scheduler_Running = pdFALSE;

    /* Not implemented in this port. Artificially force an assert. */
    configASSERT( prv_पत्तनम्_Scheduler_Running == pdTRUE );
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
शून्य v_पत्तनम्_Enter_Critical( शून्य )
{
    पत्तनम्_DISABLE_INTERRUPTS();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert
     * if the critical nesting count is 1 to protect against recursive calls if
     * the assert function also uses a critical section. */
    यदि( ulCriticalNesting == 1 )
    {
        configASSERT( ul_पत्तनम्_व्यवधानम्_Nesting == 0 );
    }
}
/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
शून्य v_पत्तनम्_Exit_Critical( शून्य )
{
    यदि( ulCriticalNesting > पत्तनम्_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        यदि( ulCriticalNesting == पत्तनम्_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            पत्तनम्_ENABLE_INTERRUPTS();
        }
    }
}
/* ----------------------------------------------------------------------------------- */
