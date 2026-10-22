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
#অন্তর্ভাব <stdint.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers. That should only be done when
 * task.h is included from an application file. */
#ifndef MPU_WRAPPERS_INCLUDED_FROM_API_FILE
    #define MPU_WRAPPERS_INCLUDED_FROM_API_FILE
#endif /* MPU_WRAPPERS_INCLUDED_FROM_API_FILE */

/* Scheduler includes. */
#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "portmacro.h"
#অন্তর্ভাব "task.h"
#অন্তর্ভাব "mpu_syscall_numbers.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Max value that fits in a uint32_t type. */
#define portUINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#define portADD_UINT32_WILL_OVERFLOW( a, b )    ( ( a ) > ( portUINT32_MAX - ( b ) ) )
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
PRIVILEGED_DATA চঞ্চল UBaseType_t ulCriticalNesting = 0xFFFF;

/**
 * @brief Set to 1 to pend a context switch from an ISR.
 *
 * @ingroup Interrupt Management
 */
PRIVILEGED_DATA চঞ্চল UBaseType_t ulPortYieldRequired = pdFALSE;

/**
 * @brief Interrupt nesting depth, used to count the number of interrupts to unwind.
 *
 * @ingroup Interrupt Management
 */
PRIVILEGED_DATA চঞ্চল UBaseType_t ulPortInterruptNesting = 0UL;

/**
 * @brief Variable to track whether or not the scheduler has been started.
 *
 * @ingroup Scheduler
 *
 * This is the port specific version of the xSchedulerRunning in tasks.c.
 */
PRIVILEGED_DATA স্থির BaseType_t prvPortSchedulerRunning = pdFALSE;

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
PRIVILEGED_FUNCTION স্থির BaseType_t prvMPURegionAuthorizesBuffer( ধ্রুব xMPU_REGION_REGISTERS * xTaskMPURegion,
                                                                    ধ্রুব uint32_t ulBufferStart,
                                                                    ধ্রুব uint32_t ulBufferLength,
                                                                    ধ্রুব uint32_t ulAccessRequested );

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
PRIVILEGED_FUNCTION স্থির uint32_t prvGetMPURegionSizeEncoding( uint32_t ulActualMPURegionSize );

/**
 * @brief Set up MPU.
 *
 * @ingroup MPU Control
 */
PRIVILEGED_FUNCTION স্থির শূন্য prvSetupMPU( শূন্য );

/* -------------------------- Exported Function Declarations -------------------------- */

/**
 * @brief Enter critical section.
 *
 * @ingroup Critical Section
 */
PRIVILEGED_FUNCTION শূন্য vPortEnterCritical( শূন্য );

/**
 * @brief Exit critical section.
 *
 * @ingroup Critical Section
 */
PRIVILEGED_FUNCTION শূন্য vPortExitCritical( শূন্য );

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
স্তূপ_Type_t * px_Port_Initialise_স্তূপ( স্তূপ_Type_t * px_শীর্ষ_Of_স্তূপ,
                                     TaskFunction_t pxCode,
                                     শূন্য * pvParameters,
                                     BaseType_t xRunPrivileged,
                                     xMPU_SETTINGS * xMPUSettings )
{
    /* Setup the initial context of the task. The context is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */
    UBaseType_t ulIndex = CONTEXT_SIZE - 1U;

    x_SYSTEM_CALL_স্তূপ_INFO * xSysCallInfo = রিক্ত;

    যদি( xRunPrivileged == pdTRUE )
    {
        xMPUSettings->ulTaskFlags |= portTASK_IS_PRIVILEGED_FLAG;
        /* Current Program Status Register (CPSR). */
        xMPUSettings->ulContext[ ulIndex ] = SYS_MODE;
    }
    অন্যথা
    {
        xMPUSettings->ulTaskFlags &= ( ~portTASK_IS_PRIVILEGED_FLAG );
        /* Current Program Status Register (CPSR). */
        xMPUSettings->ulContext[ ulIndex ] = USER_MODE;
    }

    যদি( ( ( uint32_t ) pxCode & portTHUMB_MODE_ADDRESS ) != 0x0UL )
    {
        /* The task will cause the processor to start in THUMB state, set the
         * Thumb state bit in the CPSR. */
        xMPUSettings->ulContext[ ulIndex ] |= portTHUMB_MODE_BIT;
    }

    ulIndex--;

    xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) pxCode; /* PC. */
    ulIndex--;

    xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) portTASK_RETURN_ADDRESS; /* LR. */
    ulIndex--;

    xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) px_শীর্ষ_Of_স্তূপ; /* SP. */
    ulIndex--;

    /* General Purpose Registers. */
    xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0x12121212; /* R12. */
    ulIndex--;
    xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0x11111111; /* R11. */
    ulIndex--;
    xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0x10101010; /* R10. */
    ulIndex--;
    xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0x09090909; /* R9. */
    ulIndex--;
    xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0x08080808; /* R8. */
    ulIndex--;
    xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0x07070707; /* R7. */
    ulIndex--;
    xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0x06060606; /* R6. */
    ulIndex--;
    xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0x05050505; /* R5. */
    ulIndex--;
    xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0x04040404; /* R4. */
    ulIndex--;
    xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0x03030303; /* R3. */
    ulIndex--;
    xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0x02020202; /* R2. */
    ulIndex--;
    xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0x01010101; /* R1. */
    ulIndex--;
    xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) pvParameters; /* R0. */
    ulIndex--;

    #যদি( portENABLE_FPU == 1 )
    {
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD0000015; /* S31. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD1500000; /* S30. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD0000014; /* S29. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD1400000; /* S28. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD0000013; /* S27. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD1300000; /* S26. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD0000012; /* S25. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD1200000; /* S24. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD0000011; /* S23. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD1100000; /* S22. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD0000010; /* S21. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD1000000; /* S20. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD0000009; /* S19. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD9000000; /* S18. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD0000008; /* S17. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD8000000; /* S16. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD0000007; /* S15. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD7000000; /* S14. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD0000006; /* S13. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD6000000; /* S12. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD0000005; /* S11. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD5000000; /* S10. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD0000004; /* S9. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD4000000; /* S8. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD0000003; /* S7. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD3000000; /* S6. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD0000002; /* S5. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD2000000; /* S4. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD0000001; /* S3. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD1000000; /* S2. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD0000000; /* S1. */
        ulIndex--;
        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0xD0000000; /* S0. */
        ulIndex--;

        xMPUSettings->ulContext[ ulIndex ] = ( স্তূপ_Type_t ) 0x00000000; /* FPSR. */
        ulIndex--;
    }
    #endif /* portENABLE_FPU */

    /* The task will start with a critical nesting count of 0. */
    xMPUSettings->ulContext[ ulIndex ] = portNO_CRITICAL_NESTING;

    /* Ensure that the system call stack is double word aligned. */
    xSysCallInfo = &( xMPUSettings->x_System_Call_স্তূপ_Info );
    xSysCallInfo->pul_System_Call_স্তূপ_Pointer = &( xSysCallInfo->ul_System_Call_স্তূপ_Buffer[ config_SYSTEM_CALL_স্তূপ_SIZE - 1U ] );
    xSysCallInfo->pul_System_Call_স্তূপ_Pointer = ( uint32_t * ) ( ( ( uint32_t ) ( xSysCallInfo->pul_System_Call_স্তূপ_Pointer ) ) &
                                                               ( ( uint32_t ) ( ~( portBYTE_ALIGNMENT_MASK ) ) ) );

    /* This is not NULL only for the duration of a system call. */
    xSysCallInfo->pul_Task_স্তূপ_Pointer = রিক্ত;

    /* Set the System Call to return to vPortSystemCallExit. */
    xSysCallInfo->pulSystemCallExitAddress = ( uint32_t * ) ( &vPortSystemCallExit );

    /* Return the address where this task's context should be restored from. */
    প্রত্যাগম &( xMPUSettings->ulContext[ ulIndex ] );
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
শূন্য vPortStoreTaskMPUSettings( xMPU_SETTINGS * xMPUSettings,
                                ধ্রুব সংরচনা xMEMORY_REGION * ধ্রুব xRegions,
                                স্তূপ_Type_t * px_Bottom_Of_স্তূপ,
                                uint32_t ul_স্তূপ_Depth )
{
    #যদি defined( __ARMCC_VERSION )
        /* Declaration when these variable are defined in code instead of being
         * exported from linker scripts. */
        বাহ্য uint32_t * __SRAM_segment_start__;
        বাহ্য uint32_t * __SRAM_segment_end__;
    #অন্যথা
        /* Declaration when these variable are exported from linker scripts. */
        বাহ্য uint32_t __SRAM_segment_start__[];
        বাহ্য uint32_t __SRAM_segment_end__[];
    #endif /* if defined( __ARMCC_VERSION ) */

    uint32_t ulIndex = 0x0;
    uint32_t ulRegionLength;
    uint32_t ulRegionLengthEncoded;
    uint32_t ulRegionLengthDecoded;

    যদি( xRegions == রিক্ত )
    {
        /* No MPU regions are specified so allow access to all of the RAM. */
        ulRegionLength = ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__;
        ulRegionLengthEncoded = prvGetMPURegionSizeEncoding( ulRegionLength );
        ulRegionLength |= portMPU_REGION_ENABLE;

        /* MPU Settings is zero'd out in the TCB before this function is called.
         * We, therefore, do not need to explicitly zero out unused MPU regions
         * in xMPUSettings. */
        ulIndex = port_স্তূপ_REGION;

        xMPUSettings->xRegion[ ulIndex ].ulRegionBaseAddress = ( uint32_t ) __SRAM_segment_start__;
        xMPUSettings->xRegion[ ulIndex ].ulRegionSize = ( ulRegionLengthEncoded |
                                                          portMPU_REGION_ENABLE );
        xMPUSettings->xRegion[ ulIndex ].ulRegionAttribute = ( portMPU_REGION_PRIV_RW_USER_RW_NOEXEC |
                                                               portMPU_REGION_NORMAL_OIWTNOWA_SHARED );
    }
    অন্যথা
    {
        প্রতি( ulIndex = 0UL; ulIndex < port_অঙ্ক_CONFIGURABLE_REGIONS; ulIndex++ )
        {
            /* If a length has been provided, the region is in use. */
            যদি( ( xRegions[ ulIndex ] ).ulLengthInBytes > 0UL )
            {
                ulRegionLength = xRegions[ ulIndex ].ulLengthInBytes;
                ulRegionLengthEncoded = prvGetMPURegionSizeEncoding( ulRegionLength );

                /* MPU region base address must be aligned to the region size
                 * boundary. */
                ulRegionLengthDecoded = 2UL << ( ulRegionLengthEncoded >> 1UL );
                configASSERT( ( ( ( uint32_t ) xRegions[ ulIndex ].pvBaseAddress ) % ( ulRegionLengthDecoded ) ) == 0UL );

                xMPUSettings->xRegion[ ulIndex ].ulRegionBaseAddress = ( uint32_t ) xRegions[ ulIndex ].pvBaseAddress;
                xMPUSettings->xRegion[ ulIndex ].ulRegionSize = ( ulRegionLengthEncoded |
                                                                  portMPU_REGION_ENABLE );
                xMPUSettings->xRegion[ ulIndex ].ulRegionAttribute = xRegions[ ulIndex ].ulParameters;
            }
            অন্যথা
            {
                xMPUSettings->xRegion[ ulIndex ].ulRegionBaseAddress = 0x0UL;
                xMPUSettings->xRegion[ ulIndex ].ulRegionSize = 0x0UL;
                xMPUSettings->xRegion[ ulIndex ].ulRegionAttribute = 0x0UL;
            }
        }

        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid. At all other
         * times the stack parameters will not be valid and it is assumed that the
         * stack region has already been configured. */
        যদি( ul_স্তূপ_Depth != 0x0UL )
        {
            ulRegionLengthEncoded = prvGetMPURegionSizeEncoding( ul_স্তূপ_Depth * ( uint32_t ) পরিমাণ( স্তূপ_Type_t ) );

            /* MPU region base address must be aligned to the region size
             * boundary. */
            ulRegionLengthDecoded = 2UL << ( ulRegionLengthEncoded >> 1UL );
            configASSERT( ( ( uint32_t ) px_Bottom_Of_স্তূপ % ( ulRegionLengthDecoded ) ) == 0U );

            ulIndex = port_স্তূপ_REGION;
            xMPUSettings->xRegion[ ulIndex ].ulRegionBaseAddress = ( uint32_t ) px_Bottom_Of_স্তূপ;
            xMPUSettings->xRegion[ ulIndex ].ulRegionSize = ( ulRegionLengthEncoded |
                                                              portMPU_REGION_ENABLE );
            xMPUSettings->xRegion[ ulIndex ].ulRegionAttribute = ( portMPU_REGION_PRIV_RW_USER_RW_NOEXEC |
                                                                   portMPU_REGION_NORMAL_OIWTNOWA_SHARED );
        }
    }
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
BaseType_t xPortIsTaskPrivileged( শূন্য )
{
    BaseType_t xTaskIsPrivileged = pdFALSE;

    /* Calling task's MPU settings. */
    ধ্রুব xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( রিক্ত );

    যদি( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
    {
        xTaskIsPrivileged = pdTRUE;
    }

    প্রত্যাগম xTaskIsPrivileged;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
BaseType_t xPortStartScheduler( শূন্য )
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
    ( শূন্য ) prvTaskExitError();
    প্রত্যাগম pdFALSE;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
স্থির uint32_t prvGetMPURegionSizeEncoding( uint32_t ulActualMPURegionSize )
{
    uint32_t ulRegionSize, ul_Return_মান = 4U;

    /* 32 bytes is the smallest valid region for Cortex R4 and R5 CPUs. */
    প্রতি( ulRegionSize = 0x20UL; ul_Return_মান < 0x1FUL; ( ulRegionSize <<= 1UL ) )
    {
        যদি( ulActualMPURegionSize <= ulRegionSize )
        {
            ভঙ্গ;
        }
        অন্যথা
        {
            ul_Return_মান++;
        }
    }

    /* Shift the code by one before returning so it can be written directly
     * into the correct bit position of the attribute register. */
    প্রত্যাগম ul_Return_মান << 1UL;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
স্থির শূন্য prvSetupMPU( শূন্য )
{
#যদি defined( __ARMCC_VERSION )
    /* Declaration when these variable are defined in code. */
    /* Sections used for FLASH. */
    বাহ্য uint32_t * __FLASH_segment_start__;
    বাহ্য uint32_t * __FLASH_segment_end__;
    বাহ্য uint32_t * __privileged_functions_start__;
    বাহ্য uint32_t * __privileged_functions_end__;

    /* Sections used for RAM. */
    বাহ্য uint32_t * __SRAM_segment_start__;
    বাহ্য uint32_t * __SRAM_segment_end__;
    বাহ্য uint32_t * __privileged_data_start__;
    বাহ্য uint32_t * __privileged_data_end__;
#অন্যথা
    /* Declaration when these variable are exported from linker scripts. */
    /* Sections used for FLASH. */
    বাহ্য uint32_t __FLASH_segment_start__[];
    বাহ্য uint32_t __FLASH_segment_end__[];
    বাহ্য uint32_t __privileged_functions_start__[];
    বাহ্য uint32_t __privileged_functions_end__[];

    /* Sections used for RAM. */
    বাহ্য uint32_t __SRAM_segment_start__[];
    বাহ্য uint32_t __SRAM_segment_end__[];
    বাহ্য uint32_t __privileged_data_start__[];
    বাহ্য uint32_t __privileged_data_end__[];
#endif /* if defined( __ARMCC_VERSION ) */

    uint32_t ulRegionLength;
    uint32_t ulRegionLengthEncoded;

    /* Disable the MPU before programming it. */
    vMPUDisable();

    /* Priv: RX, Unpriv: RX for entire Flash. */
    ulRegionLength = ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__;
    ulRegionLengthEncoded = prvGetMPURegionSizeEncoding( ulRegionLength );
    vMPUSetRegion( portUNPRIVILEGED_FLASH_REGION,
                   ( uint32_t ) __FLASH_segment_start__,
                   ( ulRegionLengthEncoded | portMPU_REGION_ENABLE ),
                   ( portMPU_REGION_PRIV_RO_USER_RO_EXEC |
                     portMPU_REGION_NORMAL_OIWTNOWA_SHARED ) );

    /* Priv: RX, Unpriv: No access for privileged functions. */
    ulRegionLength = ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__;
    ulRegionLengthEncoded = prvGetMPURegionSizeEncoding( ulRegionLength );
    vMPUSetRegion( portPRIVILEGED_FLASH_REGION,
                   ( uint32_t ) __privileged_functions_start__,
                   ( ulRegionLengthEncoded | portMPU_REGION_ENABLE ),
                   ( portMPU_REGION_PRIV_RO_USER_NA_EXEC |
                     portMPU_REGION_NORMAL_OIWTNOWA_SHARED ) );

    /* Priv: RW, Unpriv: No Access for privileged data. */
    ulRegionLength = ( uint32_t ) __privileged_data_end__ - ( uint32_t ) __privileged_data_start__;
    ulRegionLengthEncoded = prvGetMPURegionSizeEncoding( ulRegionLength );
    vMPUSetRegion( portPRIVILEGED_RAM_REGION,
                   ( uint32_t ) __privileged_data_start__,
                   ( ulRegionLengthEncoded | portMPU_REGION_ENABLE ),
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
স্থির BaseType_t prvMPURegionAuthorizesBuffer( ধ্রুব xMPU_REGION_REGISTERS * xTaskMPURegion,
                                                ধ্রুব uint32_t ulBufferStart,
                                                ধ্রুব uint32_t ulBufferLength,
                                                ধ্রুব uint32_t ulAccessRequested )
{
    BaseType_t xAccessGranted = pdFALSE;
    uint32_t ulBufferEnd;
    uint32_t ulMPURegionLength;
    uint32_t ulMPURegionStart;
    uint32_t ulMPURegionEnd;
    uint32_t ulMPURegionAccessPermissions;

    যদি( portADD_UINT32_WILL_OVERFLOW( ulBufferStart, ( ulBufferLength - 1UL ) ) == pdFALSE )
    {
        ulBufferEnd = ulBufferStart + ulBufferLength - 1UL;
        ulMPURegionLength = 2UL << ( xTaskMPURegion->ulRegionSize >> 1UL );
        ulMPURegionStart = xTaskMPURegion->ulRegionBaseAddress;
        ulMPURegionEnd = xTaskMPURegion->ulRegionBaseAddress + ulMPURegionLength - 1UL;

        যদি( ( ulBufferStart >= ulMPURegionStart ) &&
            ( ulBufferEnd <= ulMPURegionEnd ) &&
            ( ulBufferStart <= ulBufferEnd ) )
        {
            ulMPURegionAccessPermissions = xTaskMPURegion->ulRegionAttribute & portMPU_REGION_AP_BITMASK;

            যদি( ulAccessRequested == tskMPU_READ_PERMISSION ) /* RO. */
            {
                যদি( ( ulMPURegionAccessPermissions == portMPU_REGION_PRIV_RW_USER_RO ) ||
                    ( ulMPURegionAccessPermissions == portMPU_REGION_PRIV_RO_USER_RO ) ||
                    ( ulMPURegionAccessPermissions == portMPU_REGION_PRIV_RW_USER_RW ) )

                {
                    xAccessGranted = pdTRUE;
                }
            }
            অন্যথা যদি( ( ulAccessRequested & tskMPU_WRITE_PERMISSION ) != 0UL ) /* W or RW. */
            {
                যদি( ulMPURegionAccessPermissions == portMPU_REGION_PRIV_RW_USER_RW )
                {
                    xAccessGranted = pdTRUE;
                }
            }
        }
    }

    প্রত্যাগম xAccessGranted;
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
BaseType_t xPortIsAuthorizedToAccessBuffer( ধ্রুব শূন্য * pvBuffer,
                                            size_t xBufferLength,
                                            uint32_t ulAccessRequested )
{
    BaseType_t xAccessGranted = pdFALSE;
    uint32_t ulRegionIndex;
    xMPU_SETTINGS * xTaskMPUSettings = রিক্ত;

    যদি( prvPortSchedulerRunning == pdFALSE )
    {
        /* Grant access to all the memory before the scheduler is started. It is
         * necessary because there is no task running yet and therefore, we
         * cannot use the permissions of any task. */
        xAccessGranted = pdTRUE;
    }
    অন্যথা
    {
        /* Calling task's MPU settings. */
        xTaskMPUSettings = xTaskGetMPUSettings( রিক্ত );

        যদি( ( xTaskMPUSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
        {
            /* Privileged tasks have access to all the memory. */
            xAccessGranted = pdTRUE;
        }
        অন্যথা
        {
            প্রতি( ulRegionIndex = 0x0UL; ulRegionIndex < port_TOTAL_অঙ্ক_REGIONS_IN_TCB; ulRegionIndex++ )
            {
                xAccessGranted = prvMPURegionAuthorizesBuffer( &( xTaskMPUSettings->xRegion[ ulRegionIndex ] ),
                                                               ( uint32_t ) pvBuffer,
                                                               ( uint32_t ) xBufferLength,
                                                               ulAccessRequested );

                যদি( xAccessGranted == pdTRUE )
                {
                    ভঙ্গ;
                }
            }
        }
    }

    প্রত্যাগম xAccessGranted;
}

/* ----------------------------------------------------------------------------------- */

#যদি( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
BaseType_t xPortIsAuthorizedToAccessKernelObject( int32_t lInternalIndexOfKernelObject )
{
    uint32_t ulAccessControlListEntryIndex, ulAccessControlListEntryBit;
    BaseType_t xAccessGranted = pdFALSE;
    ধ্রুব xMPU_SETTINGS * xTaskMpuSettings;

    যদি( prvPortSchedulerRunning == pdFALSE )
    {
        /* Grant access to all the kernel objects before the scheduler
         * is started. It is necessary because there is no task running
         * yet and therefore, we cannot use the permissions of any
         * task. */
        xAccessGranted = pdTRUE;
    }
    অন্যথা
    {
        /* Calling task's MPU settings. */
        xTaskMpuSettings = xTaskGetMPUSettings( রিক্ত );

        ulAccessControlListEntryIndex = ( ( uint32_t ) lInternalIndexOfKernelObject
                                          / portACL_ENTRY_SIZE_BITS );
        ulAccessControlListEntryBit = ( ( uint32_t ) lInternalIndexOfKernelObject
                                        % portACL_ENTRY_SIZE_BITS );

        যদি( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        অন্যথা
        {
            যদি( ( ( xTaskMpuSettings->ulAccessControlList[ ulAccessControlListEntryIndex ] ) &
                  ( 1U << ulAccessControlListEntryBit ) ) != 0UL )
            {
                xAccessGranted = pdTRUE;
            }
        }
    }

    প্রত্যাগম xAccessGranted;
}

#অন্যথা

/* PRIVILEGED_FUNCTION */
BaseType_t xPortIsAuthorizedToAccessKernelObject( int32_t lInternalIndexOfKernelObject )
{
    ( শূন্য ) lInternalIndexOfKernelObject;

    /* If Access Control List feature is not used, all the tasks have
     * access to all the kernel objects. */
    প্রত্যাগম pdTRUE;
}

#endif /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

#যদি( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
শূন্য vPortGrantAccessToKernelObject( TaskHandle_t xInternalTaskHandle,
                                     int32_t lInternalIndexOfKernelObject )
{
    uint32_t ulAccessControlListEntryIndex, ulAccessControlListEntryBit;
    xMPU_SETTINGS * xTaskMpuSettings;

    ulAccessControlListEntryIndex = ( ( uint32_t ) lInternalIndexOfKernelObject
                                      / portACL_ENTRY_SIZE_BITS );
    ulAccessControlListEntryBit = ( ( uint32_t ) lInternalIndexOfKernelObject
                                    % portACL_ENTRY_SIZE_BITS );

    xTaskMpuSettings = xTaskGetMPUSettings( xInternalTaskHandle );

    xTaskMpuSettings->ulAccessControlList[ ulAccessControlListEntryIndex ] |= ( 1U << ulAccessControlListEntryBit );
}

#endif /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

#যদি( configENABLE_ACCESS_CONTROL_LIST == 1 )

/* PRIVILEGED_FUNCTION */
শূন্য vPortRevokeAccessToKernelObject( TaskHandle_t xInternalTaskHandle,
                                      int32_t lInternalIndexOfKernelObject )
{
    uint32_t ulAccessControlListEntryIndex, ulAccessControlListEntryBit;
    xMPU_SETTINGS * xTaskMpuSettings;

    ulAccessControlListEntryIndex = ( ( uint32_t ) lInternalIndexOfKernelObject
                                      / portACL_ENTRY_SIZE_BITS );
    ulAccessControlListEntryBit = ( ( uint32_t ) lInternalIndexOfKernelObject
                                    % portACL_ENTRY_SIZE_BITS );

    xTaskMpuSettings = xTaskGetMPUSettings( xInternalTaskHandle );

    xTaskMpuSettings->ulAccessControlList[ ulAccessControlListEntryIndex ] &= ~( 1U << ulAccessControlListEntryBit );
}

#endif /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

/* ----------------------------------------------------------------------------------- */

শূন্য prvTaskExitError( শূন্য )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ulPortInterruptNesting == ~0UL );

    প্রতি( ;; )
    {
    }
}

/* ----------------------------------------------------------------------------------- */

শূন্য vPortEndScheduler( শূন্য )
{
    prvPortSchedulerRunning = pdFALSE;

    /* Not implemented in this port. Artificially force an assert. */
    configASSERT( prvPortSchedulerRunning == pdTRUE );
}

/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
শূন্য vPortEnterCritical( শূন্য )
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
    যদি( ulCriticalNesting == 1 )
    {
        configASSERT( ulPortInterruptNesting == 0 );
    }
}
/* ----------------------------------------------------------------------------------- */

/* PRIVILEGED_FUNCTION */
শূন্য vPortExitCritical( শূন্য )
{
    যদি( ulCriticalNesting > portNO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        যদি( ulCriticalNesting == portNO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            portENABLE_INTERRUPTS();
        }
    }
}
/* ----------------------------------------------------------------------------------- */
