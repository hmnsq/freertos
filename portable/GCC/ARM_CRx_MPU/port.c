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
#समावेश <stdint.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers. That should only be done when
 * task.h is included from an application file. */
#अगर_अघोषित MPU_WRAPPERS_INCLUDED_FROM_API_FILE
    #घोषणा MPU_WRAPPERS_INCLUDED_FROM_API_FILE
#पूर्ण_अगर /* MPU_WRAPPERS_INCLUDED_FROM_API_FILE */

/* Scheduler includes. */
#समावेश "FreeRTOS.h"
#समावेश "portmacro.h"
#समावेश "task.h"
#समावेश "mpu_syscall_numbers.h"

#अघोषित MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Max value that fits in a uint32_t type. */
#घोषणा portUINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#घोषणा portADD_UINT32_WILL_OVERFLOW( a, b )    ( ( a ) > ( portUINT32_MAX - ( b ) ) )
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
PRIVILEGED_तथ्य अस्थिर UBaseType_t ulCriticalNesting = 0xFFFF;

/**
 * @brief Set to 1 to pend a context switch from an ISR.
 *
 * @ingroup Interrupt Management
 */
PRIVILEGED_तथ्य अस्थिर UBaseType_t ulPortYieldRequired = pdFALSE;

/**
 * @brief Interrupt nesting depth, used to count the number of interrupts to unwind.
 *
 * @ingroup Interrupt Management
 */
PRIVILEGED_तथ्य अस्थिर UBaseType_t ulPortInterruptNesting = 0UL;

/**
 * @brief Variable to track whether or not the scheduler has been started.
 *
 * @ingroup Scheduler
 *
 * This is the port specific version of the xSchedulerRunning in tasks.c.
 */
PRIVILEGED_तथ्य अटल BaseType_t prvPortSchedulerRunning = pdFALSE;

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
PRIVILEGED_FUNCTION अटल BaseType_t prv_MPURegion_Authorizes_बफर( स्थिर xMPU_REGION_REGISTERS * xTaskMPURegion,
                                                                    स्थिर uint32_t ul_बफर_Start,
                                                                    स्थिर uint32_t ul_बफर_लंबाई,
                                                                    स्थिर uint32_t ulAccessRequested );

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
PRIVILEGED_FUNCTION अटल uint32_t prv_Get_MPURegion_आकार_Encoding( uint32_t ul_Actual_MPURegion_आकार );

/**
 * @brief Set up MPU.
 *
 * @ingroup MPU Control
 */
PRIVILEGED_FUNCTION अटल व्योम prvSetupMPU( व्योम );

/* -------------------------- Exported Function Declarations -------------------------- */

/**
 * @brief Enter critical section.
 *
 * @ingroup Critical Section
 */
PRIVILEGED_FUNCTION व्योम vPortEnterCritical( व्योम );

/**
 * @brief Exit critical section.
 *
 * @ingroup Critical Section
 */
PRIVILEGED_FUNCTION व्योम vPortExitCritical( व्योम );

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
ढेर_Type_t * px_Port_Initialise_ढेर( ढेर_Type_t * px_शीर्ष_Of_ढेर,
                                     TaskFunction_t pxCode,
                                     व्योम * pvParameters,
                                     BaseType_t xRunPrivileged,
                                     xMPU_SETTINGS * xMPUSettings )
{
    /* Setup the initial context of the task. The context is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */
    UBaseType_t ul_सूचकांक = CONTEXT_आकार - 1U;

    x_SYSTEM_CALL_ढेर_INFO * xSysCallInfo = शून्य;

    अगर( xRunPrivileged == pdTRUE )
    {
        xMPUSettings->ulTaskFlags |= portTASK_IS_PRIVILEGED_FLAG;
        /* Current Program Status Register (CPSR). */
        xMPUSettings->ulContext[ ul_सूचकांक ] = SYS_MODE;
    }
    अन्यथा
    {
        xMPUSettings->ulTaskFlags &= ( ~portTASK_IS_PRIVILEGED_FLAG );
        /* Current Program Status Register (CPSR). */
        xMPUSettings->ulContext[ ul_सूचकांक ] = USER_MODE;
    }

    अगर( ( ( uint32_t ) pxCode & portTHUMB_MODE_ADDRESS ) != 0x0UL )
    {
        /* The task will cause the processor to start in THUMB state, set the
         * Thumb state bit in the CPSR. */
        xMPUSettings->ulContext[ ul_सूचकांक ] |= portTHUMB_MODE_BIT;
    }

    ul_सूचकांक--;

    xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) pxCode; /* PC. */
    ul_सूचकांक--;

    xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) portTASK_RETURN_ADDRESS; /* LR. */
    ul_सूचकांक--;

    xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) px_शीर्ष_Of_ढेर; /* SP. */
    ul_सूचकांक--;

    /* General Purpose Registers. */
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0x12121212; /* R12. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0x11111111; /* R11. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0x10101010; /* R10. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0x09090909; /* R9. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0x08080808; /* R8. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0x07070707; /* R7. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0x06060606; /* R6. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0x05050505; /* R5. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0x04040404; /* R4. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0x03030303; /* R3. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0x02020202; /* R2. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0x01010101; /* R1. */
    ul_सूचकांक--;
    xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) pvParameters; /* R0. */
    ul_सूचकांक--;

    #अगर( portENABLE_FPU == 1 )
    {
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD0000015; /* S31. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD1500000; /* S30. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD0000014; /* S29. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD1400000; /* S28. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD0000013; /* S27. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD1300000; /* S26. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD0000012; /* S25. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD1200000; /* S24. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD0000011; /* S23. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD1100000; /* S22. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD0000010; /* S21. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD1000000; /* S20. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD0000009; /* S19. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD9000000; /* S18. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD0000008; /* S17. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD8000000; /* S16. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD0000007; /* S15. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD7000000; /* S14. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD0000006; /* S13. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD6000000; /* S12. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD0000005; /* S11. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD5000000; /* S10. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD0000004; /* S9. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD4000000; /* S8. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD0000003; /* S7. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD3000000; /* S6. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD0000002; /* S5. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD2000000; /* S4. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD0000001; /* S3. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD1000000; /* S2. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD0000000; /* S1. */
        ul_सूचकांक--;
        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0xD0000000; /* S0. */
        ul_सूचकांक--;

        xMPUSettings->ulContext[ ul_सूचकांक ] = ( ढेर_Type_t ) 0x00000000; /* FPSR. */
        ul_सूचकांक--;
    }
    #पूर्ण_अगर /* portENABLE_FPU */

    /* The task will start with a critical nesting count of 0. */
    xMPUSettings->ulContext[ ul_सूचकांक ] = portNO_CRITICAL_NESTING;

    /* Ensure that the system call stack is double word aligned. */
    xSysCallInfo = &( xMPUSettings->x_System_Call_ढेर_Info );
    xSysCallInfo->pul_System_Call_ढेर_Pointer = &( xSysCallInfo->ul_System_Call_ढेर_बफर[ config_SYSTEM_CALL_ढेर_आकार - 1U ] );
    xSysCallInfo->pul_System_Call_ढेर_Pointer = ( uint32_t * ) ( ( ( uint32_t ) ( xSysCallInfo->pul_System_Call_ढेर_Pointer ) ) &
                                                               ( ( uint32_t ) ( ~( portBYTE_ALIGNMENT_MASK ) ) ) );

    /* This is not NULL only for the duration of a system call. */
    xSysCallInfo->pul_Task_ढेर_Pointer = शून्य;

    /* Set the System Call to return to vPortSystemCallExit. */
    xSysCallInfo->pulSystemCallExitAddress = ( uint32_t * ) ( &vPortSystemCallExit );

    /* Return the address where this task's context should be restored from. */
    वापस &( xMPUSettings->ulContext[ ul_सूचकांक ] );
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
व्योम vPortStoreTaskMPUSettings( xMPU_SETTINGS * xMPUSettings,
                                स्थिर काष्ठा xMEMORY_REGION * स्थिर xRegions,
                                ढेर_Type_t * px_Bottom_Of_ढेर,
                                uint32_t ul_ढेर_Depth )
{
    #अगर defined( __ARMCC_VERSION )
        /* Declaration when these variable are defined in code instead of being
         * exported from linker scripts. */
        बाह्य uint32_t * __SRAM_segment_start__;
        बाह्य uint32_t * __SRAM_segment_end__;
    #अन्यथा
        /* Declaration when these variable are exported from linker scripts. */
        बाह्य uint32_t __SRAM_segment_start__[];
        बाह्य uint32_t __SRAM_segment_end__[];
    #पूर्ण_अगर /* if defined( __ARMCC_VERSION ) */

    uint32_t ul_सूचकांक = 0x0;
    uint32_t ul_Region_लंबाई;
    uint32_t ul_Region_लंबाई_Encoded;
    uint32_t ul_Region_लंबाई_Decoded;

    अगर( xRegions == शून्य )
    {
        /* No MPU regions are specified so allow access to all of the RAM. */
        ul_Region_लंबाई = ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__;
        ul_Region_लंबाई_Encoded = prv_Get_MPURegion_आकार_Encoding( ul_Region_लंबाई );
        ul_Region_लंबाई |= portMPU_REGION_ENABLE;

        /* MPU Settings is zero'd out in the TCB before this function is called.
         * We, therefore, do not need to explicitly zero out unused MPU regions
         * in xMPUSettings. */
        ul_सूचकांक = port_ढेर_REGION;

        xMPUSettings->xRegion[ ul_सूचकांक ].ulRegionBaseAddress = ( uint32_t ) __SRAM_segment_start__;
        xMPUSettings->xRegion[ ul_सूचकांक ].ul_Region_आकार = ( ul_Region_लंबाई_Encoded |
                                                          portMPU_REGION_ENABLE );
        xMPUSettings->xRegion[ ul_सूचकांक ].ulRegionAttribute = ( portMPU_REGION_PRIV_RW_USER_RW_NOEXEC |
                                                               portMPU_REGION_NORMAL_OIWTNOWA_SHARED );
    }
    अन्यथा
    {
        क्रम( ul_सूचकांक = 0UL; ul_सूचकांक < port_अंक_CONFIGURABLE_REGIONS; ul_सूचकांक++ )
        {
            /* If a length has been provided, the region is in use. */
            अगर( ( xRegions[ ul_सूचकांक ] ).ul_लंबाई_In_Bytes > 0UL )
            {
                ul_Region_लंबाई = xRegions[ ul_सूचकांक ].ul_लंबाई_In_Bytes;
                ul_Region_लंबाई_Encoded = prv_Get_MPURegion_आकार_Encoding( ul_Region_लंबाई );

                /* MPU region base address must be aligned to the region size
                 * boundary. */
                ul_Region_लंबाई_Decoded = 2UL << ( ul_Region_लंबाई_Encoded >> 1UL );
                configASSERT( ( ( ( uint32_t ) xRegions[ ul_सूचकांक ].pvBaseAddress ) % ( ul_Region_लंबाई_Decoded ) ) == 0UL );

                xMPUSettings->xRegion[ ul_सूचकांक ].ulRegionBaseAddress = ( uint32_t ) xRegions[ ul_सूचकांक ].pvBaseAddress;
                xMPUSettings->xRegion[ ul_सूचकांक ].ul_Region_आकार = ( ul_Region_लंबाई_Encoded |
                                                                  portMPU_REGION_ENABLE );
                xMPUSettings->xRegion[ ul_सूचकांक ].ulRegionAttribute = xRegions[ ul_सूचकांक ].ulParameters;
            }
            अन्यथा
            {
                xMPUSettings->xRegion[ ul_सूचकांक ].ulRegionBaseAddress = 0x0UL;
                xMPUSettings->xRegion[ ul_सूचकांक ].ul_Region_आकार = 0x0UL;
                xMPUSettings->xRegion[ ul_सूचकांक ].ulRegionAttribute = 0x0UL;
            }
        }

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid. At all other
         * times the stack parameters will not be valid and it is assumed that the
         * stack region has already been configured. */
        अगर( ul_ढेर_Depth != 0x0UL )
        {
            ul_Region_लंबाई_Encoded = prv_Get_MPURegion_आकार_Encoding( ul_ढेर_Depth * ( uint32_t ) माप( ढेर_Type_t ) );

            /* MPU region base address must be aligned to the region size
             * boundary. */
            ul_Region_लंबाई_Decoded = 2UL << ( ul_Region_लंबाई_Encoded >> 1UL );
            configASSERT( ( ( uint32_t ) px_Bottom_Of_ढेर % ( ul_Region_लंबाई_Decoded ) ) == 0U );

            ul_सूचकांक = port_ढेर_REGION;
            xMPUSettings->xRegion[ ul_सूचकांक ].ulRegionBaseAddress = ( uint32_t ) px_Bottom_Of_ढेर;
            xMPUSettings->xRegion[ ul_सूचकांक ].ul_Region_आकार = ( ul_Region_लंबाई_Encoded |
                                                              portMPU_REGION_ENABLE );
            xMPUSettings->xRegion[ ul_सूचकांक ].ulRegionAttribute = ( portMPU_REGION_PRIV_RW_USER_RW_NOEXEC |
                                                                   portMPU_REGION_NORMAL_OIWTNOWA_SHARED );
        }
    }
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
BaseType_t xPortIsTaskPrivileged( व्योम )
{
    BaseType_t xTaskIsPrivileged = pdFALSE;

    /* Calling task's MPU settings. */
    स्थिर xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( शून्य );

    अगर( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
    {
        xTaskIsPrivileged = pdTRUE;
    }

    वापस xTaskIsPrivileged;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
BaseType_t xPortStartScheduler( व्योम )
{
    /* Start the timer that generates the tick ISR. */
    configSETUP_TICK_INTERRUPT();

    /* Configure MPU regions that are common to all tasks. */
    prvSetupMPU();

    prvPortSchedulerRunning = pdTRUE;

    /* Load the context of the first task. */
    vPortStartFirstTask();

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value. prvTaskExitError() is referenced to prevent a compiler
     * warning about it being defined but not referenced in the case that the user
     * defines their own exit address. */
    ( व्योम ) prvTaskExitError();
    वापस pdFALSE;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
अटल uint32_t prv_Get_MPURegion_आकार_Encoding( uint32_t ul_Actual_MPURegion_आकार )
{
    uint32_t ul_Region_आकार, ul_Return_मूल्य = 4U;

    /* 32 bytes is the smallest valid region for Cortex R4 and R5 CPUs. */
    क्रम( ul_Region_आकार = 0x20UL; ul_Return_मूल्य < 0x1FUL; ( ul_Region_आकार <<= 1UL ) )
    {
        अगर( ul_Actual_MPURegion_आकार <= ul_Region_आकार )
        {
            अवरोध;
        }
        अन्यथा
        {
            ul_Return_मूल्य++;
        }
    }

    /* Shift the code by one before returning so it can be written directly
     * into the correct bit position of the attribute register. */
    वापस ul_Return_मूल्य << 1UL;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
अटल व्योम prvSetupMPU( व्योम )
{
#अगर defined( __ARMCC_VERSION )
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
#पूर्ण_अगर /* if defined( __ARMCC_VERSION ) */

    uint32_t ul_Region_लंबाई;
    uint32_t ul_Region_लंबाई_Encoded;

    /* Disable the MPU before programming it. */
    vMPUDisable();

    /* Priv: RX, Unpriv: RX for entire Flash. */
    ul_Region_लंबाई = ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__;
    ul_Region_लंबाई_Encoded = prv_Get_MPURegion_आकार_Encoding( ul_Region_लंबाई );
    vMPUSetRegion( portUNPRIVILEGED_FLASH_REGION,
                   ( uint32_t ) __FLASH_segment_start__,
                   ( ul_Region_लंबाई_Encoded | portMPU_REGION_ENABLE ),
                   ( portMPU_REGION_PRIV_RO_USER_RO_EXEC |
                     portMPU_REGION_NORMAL_OIWTNOWA_SHARED ) );

    /* Priv: RX, Unpriv: No access for privileged functions. */
    ul_Region_लंबाई = ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__;
    ul_Region_लंबाई_Encoded = prv_Get_MPURegion_आकार_Encoding( ul_Region_लंबाई );
    vMPUSetRegion( portPRIVILEGED_FLASH_REGION,
                   ( uint32_t ) __privileged_functions_start__,
                   ( ul_Region_लंबाई_Encoded | portMPU_REGION_ENABLE ),
                   ( portMPU_REGION_PRIV_RO_USER_NA_EXEC |
                     portMPU_REGION_NORMAL_OIWTNOWA_SHARED ) );

    /* Priv: RW, Unpriv: No Access for privileged data. */
    ul_Region_लंबाई = ( uint32_t ) __privileged_data_end__ - ( uint32_t ) __privileged_data_start__;
    ul_Region_लंबाई_Encoded = prv_Get_MPURegion_आकार_Encoding( ul_Region_लंबाई );
    vMPUSetRegion( portPRIVILEGED_RAM_REGION,
                   ( uint32_t ) __privileged_data_start__,
                   ( ul_Region_लंबाई_Encoded | portMPU_REGION_ENABLE ),
                   ( portMPU_REGION_PRIV_RW_USER_NA_NOEXEC |
                     portMPU_REGION_PRIV_RW_USER_NA_NOEXEC ) );

    /* Enable the MPU background region - it allows privileged operating modes
     * access to unmapped regions of memory without generating a fault. */
    vMPUEnableBackgroundRegion();

    /* After setting default regions, enable the MPU. */
    vMPUEnable();
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
अटल BaseType_t prv_MPURegion_Authorizes_बफर( स्थिर xMPU_REGION_REGISTERS * xTaskMPURegion,
                                                स्थिर uint32_t ul_बफर_Start,
                                                स्थिर uint32_t ul_बफर_लंबाई,
                                                स्थिर uint32_t ulAccessRequested )
{
    BaseType_t xAccessGranted = pdFALSE;
    uint32_t ul_बफर_End;
    uint32_t ul_MPURegion_लंबाई;
    uint32_t ulMPURegionStart;
    uint32_t ulMPURegionEnd;
    uint32_t ulMPURegionAccessPermissions;

    अगर( portADD_UINT32_WILL_OVERFLOW( ul_बफर_Start, ( ul_बफर_लंबाई - 1UL ) ) == pdFALSE )
    {
        ul_बफर_End = ul_बफर_Start + ul_बफर_लंबाई - 1UL;
        ul_MPURegion_लंबाई = 2UL << ( xTaskMPURegion->ul_Region_आकार >> 1UL );
        ulMPURegionStart = xTaskMPURegion->ulRegionBaseAddress;
        ulMPURegionEnd = xTaskMPURegion->ulRegionBaseAddress + ul_MPURegion_लंबाई - 1UL;

        अगर( ( ul_बफर_Start >= ulMPURegionStart ) &&
            ( ul_बफर_End <= ulMPURegionEnd ) &&
            ( ul_बफर_Start <= ul_बफर_End ) )
        {
            ulMPURegionAccessPermissions = xTaskMPURegion->ulRegionAttribute & portMPU_REGION_AP_BITMASK;

            अगर( ulAccessRequested == tskMPU_READ_PERMISSION ) /* RO. */
            {
                अगर( ( ulMPURegionAccessPermissions == portMPU_REGION_PRIV_RW_USER_RO ) ||
                    ( ulMPURegionAccessPermissions == portMPU_REGION_PRIV_RO_USER_RO ) ||
                    ( ulMPURegionAccessPermissions == portMPU_REGION_PRIV_RW_USER_RW ) )

                {
                    xAccessGranted = pdTRUE;
                }
            }
            अन्यथा अगर( ( ulAccessRequested & tskMPU_WRITE_PERMISSION ) != 0UL ) /* W or RW. */
            {
                अगर( ulMPURegionAccessPermissions == portMPU_REGION_PRIV_RW_USER_RW )
                {
                    xAccessGranted = pdTRUE;
                }
            }
        }
    }

    वापस xAccessGranted;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
BaseType_t x_Port_Is_Authorized_To_Access_बफर( स्थिर व्योम * pv_बफर,
                                            माप_प्रकार x_बफर_लंबाई,
                                            uint32_t ulAccessRequested )
{
    BaseType_t xAccessGranted = pdFALSE;
    uint32_t ul_Region_सूचकांक;
    xMPU_SETTINGS * xTaskMPUSettings = शून्य;

    अगर( prvPortSchedulerRunning == pdFALSE )
    {
        /* Grant access to all the memory before the scheduler is started. It is
         * necessary because there is no task running yet and therefore, we
         * cannot use the permissions of any task. */
        xAccessGranted = pdTRUE;
    }
    अन्यथा
    {
        /* Calling task's MPU settings. */
        xTaskMPUSettings = xTaskGetMPUSettings( शून्य );

        अगर( ( xTaskMPUSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
        {
            /* Privileged tasks have access to all the memory. */
            xAccessGranted = pdTRUE;
        }
        अन्यथा
        {
            क्रम( ul_Region_सूचकांक = 0x0UL; ul_Region_सूचकांक < port_योग_अंक_REGIONS_IN_TCB; ul_Region_सूचकांक++ )
            {
                xAccessGranted = prv_MPURegion_Authorizes_बफर( &( xTaskMPUSettings->xRegion[ ul_Region_सूचकांक ] ),
                                                               ( uint32_t ) pv_बफर,
                                                               ( uint32_t ) x_बफर_लंबाई,
                                                               ulAccessRequested );

                अगर( xAccessGranted == pdTRUE )
                {
                    अवरोध;
                }
            }
        }
    }

    वापस xAccessGranted;
}

/* ----------------------------------------------------------------------------------- */

#अगर( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
BaseType_t xPortIsAuthorizedToAccessKernelObject( int32_t l_Internal_सूचकांक_Of_Kernel_Object )
{
    uint32_t ul_Access_Control_List_Entry_सूचकांक, ulAccessControlListEntryBit;
    BaseType_t xAccessGranted = pdFALSE;
    स्थिर xMPU_SETTINGS * xTaskMpuSettings;

    अगर( prvPortSchedulerRunning == pdFALSE )
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
        xTaskMpuSettings = xTaskGetMPUSettings( शून्य );

        ul_Access_Control_List_Entry_सूचकांक = ( ( uint32_t ) l_Internal_सूचकांक_Of_Kernel_Object
                                          / port_ACL_ENTRY_आकार_BITS );
        ulAccessControlListEntryBit = ( ( uint32_t ) l_Internal_सूचकांक_Of_Kernel_Object
                                        % port_ACL_ENTRY_आकार_BITS );

        अगर( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        अन्यथा
        {
            अगर( ( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_Entry_सूचकांक ] ) &
                  ( 1U << ulAccessControlListEntryBit ) ) != 0UL )
            {
                xAccessGranted = pdTRUE;
            }
        }
    }

    वापस xAccessGranted;
}

#अन्यथा

/* PRIVILEGED_FUNCTION */
BaseType_t xPortIsAuthorizedToAccessKernelObject( int32_t l_Internal_सूचकांक_Of_Kernel_Object )
{
    ( व्योम ) l_Internal_सूचकांक_Of_Kernel_Object;

    /* If Access Control List feature is not used, all the tasks have
     * access to all the kernel objects. */
    वापस pdTRUE;
}

#पूर्ण_अगर /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

#अगर( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
व्योम vPortGrantAccessToKernelObject( TaskHandle_t xInternalTaskHandle,
                                     int32_t l_Internal_सूचकांक_Of_Kernel_Object )
{
    uint32_t ul_Access_Control_List_Entry_सूचकांक, ulAccessControlListEntryBit;
    xMPU_SETTINGS * xTaskMpuSettings;

    ul_Access_Control_List_Entry_सूचकांक = ( ( uint32_t ) l_Internal_सूचकांक_Of_Kernel_Object
                                      / port_ACL_ENTRY_आकार_BITS );
    ulAccessControlListEntryBit = ( ( uint32_t ) l_Internal_सूचकांक_Of_Kernel_Object
                                    % port_ACL_ENTRY_आकार_BITS );

    xTaskMpuSettings = xTaskGetMPUSettings( xInternalTaskHandle );

    xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_Entry_सूचकांक ] |= ( 1U << ulAccessControlListEntryBit );
}

#पूर्ण_अगर /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

#अगर( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
व्योम vPortRevokeAccessToKernelObject( TaskHandle_t xInternalTaskHandle,
                                      int32_t l_Internal_सूचकांक_Of_Kernel_Object )
{
    uint32_t ul_Access_Control_List_Entry_सूचकांक, ulAccessControlListEntryBit;
    xMPU_SETTINGS * xTaskMpuSettings;

    ul_Access_Control_List_Entry_सूचकांक = ( ( uint32_t ) l_Internal_सूचकांक_Of_Kernel_Object
                                      / port_ACL_ENTRY_आकार_BITS );
    ulAccessControlListEntryBit = ( ( uint32_t ) l_Internal_सूचकांक_Of_Kernel_Object
                                    % port_ACL_ENTRY_आकार_BITS );

    xTaskMpuSettings = xTaskGetMPUSettings( xInternalTaskHandle );

    xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_Entry_सूचकांक ] &= ~( 1U << ulAccessControlListEntryBit );
}

#पूर्ण_अगर /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

व्योम prvTaskExitError( व्योम )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ulPortInterruptNesting == ~0UL );

    क्रम( ;; )
    {
    }
}

/* ----------------------------------------------------------------------------------- */

व्योम vPortEndScheduler( व्योम )
{
    prvPortSchedulerRunning = pdFALSE;

    /* Not implemented in this port. Artificially force an assert. */
    configASSERT( prvPortSchedulerRunning == pdTRUE );
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
व्योम vPortEnterCritical( व्योम )
{
    portDISABLE_INTERRUPTS();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert
     * if the critical nesting count is 1 to protect against recursive calls if
     * the assert function also uses a critical section. */
    अगर( ulCriticalNesting == 1 )
    {
        configASSERT( ulPortInterruptNesting == 0 );
    }
}
/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
व्योम vPortExitCritical( व्योम )
{
    अगर( ulCriticalNesting > portNO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        अगर( ulCriticalNesting == portNO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            portENABLE_INTERRUPTS();
        }
    }
}
/* ----------------------------------------------------------------------------------- */
