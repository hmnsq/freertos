/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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


#यदि_अपरिभाषितम् PORTMACRO_H
#परिभाषय PORTMACRO_H


/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    बाह्य "C" {
#यदि_अन्तः
/* *INDENT-ON* */

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#परिभाषय पत्तनम्_CHAR          वर्ण
#परिभाषय पत्तनम्_FLOAT         भिन्न
#परिभाषय पत्तनम्_DOUBLE        द्विगुण
#परिभाषय पत्तनम्_LONG          दीर्घ
#परिभाषय पत्तनम्_SHORT         ह्रस्व
#परिभाषय पत्तनम्_राशिः_TYPE    uint32_t
#परिभाषय पत्तनम्_आधारः_TYPE     दीर्घ

प्रकारनिर्देश पत्तनम्_राशिः_TYPE   राशिः_Type_t;
प्रकारनिर्देश दीर्घ             आधारः_Type_t;
प्रकारनिर्देश अचिह्नित दीर्घ    UBaseType_t;

#यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
    प्रकारनिर्देश uint16_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY              ( TickType_t ) 0xffff
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
    प्रकारनिर्देश uint32_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #परिभाषय पत्तनम्_TICK_TYPE_IS_ATOMIC    1
#अन्यथा
    #दोषः "configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width."
#यदि_अन्तः

/* Errata 837070 workaround must be enabled on Cortex-M7 r0p0
 * and r0p1 cores. */
#यदि_अपरिभाषितम् configENABLE_ERRATA_837070_WORKAROUND
    #परिभाषय configENABLE_ERRATA_837070_WORKAROUND    0
#यदि_अन्तः
/*-----------------------------------------------------------*/

/* MPU specific constants. */
#परिभाषय पत्तनम्_USING_MPU_WRAPPERS                                   1
#परिभाषय पत्तनम्_PRIVILEGE_BIT                                        ( 0x80000000UL )

#परिभाषय पत्तनम्_MPU_REGION_READ_WRITE                                ( 0x03UL << 24UL )
#परिभाषय पत्तनम्_MPU_REGION_PRIVILEGED_READ_ONLY                      ( 0x05UL << 24UL )
#परिभाषय पत्तनम्_MPU_REGION_READ_ONLY                                 ( 0x06UL << 24UL )
#परिभाषय पत्तनम्_MPU_REGION_PRIVILEGED_READ_WRITE                     ( 0x01UL << 24UL )
#परिभाषय पत्तनम्_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY    ( 0x02UL << 24UL )
#परिभाषय पत्तनम्_MPU_REGION_CACHEABLE_BUFFERABLE                      ( 0x07UL << 16UL )
#परिभाषय पत्तनम्_MPU_REGION_EXECUTE_NEVER                             ( 0x01UL << 28UL )

/* Location of the TEX,S,C,B bits in the MPU Region Attribute and Size
 * Register (RASR). */
#परिभाषय पत्तनम्_MPU_RASR_TEX_S_C_B_LOCATION                          ( 16UL )
#परिभाषय पत्तनम्_MPU_RASR_TEX_S_C_B_आवरणम्                              ( 0x3FUL )

/* MPU settings that can be overridden in FreeRTOSConfig.h. */
#यदि_अपरिभाषितम् config_योग_MPU_REGIONS
    /* Define to 8 for backward compatibility. */
    #परिभाषय config_योग_MPU_REGIONS    ( 8UL )
#यदि_अन्तः

/*
 * The TEX, Shareable (S), Cacheable (C) and Bufferable (B) bits define the
 * memory type, and where necessary the cacheable and shareable properties
 * of the memory region.
 *
 * The TEX, C, and B bits together indicate the memory type of the region,
 * and:
 * - For Normal memory, the cacheable properties of the region.
 * - For Device memory, whether the region is shareable.
 *
 * For Normal memory regions, the S bit indicates whether the region is
 * shareable. For Strongly-ordered and Device memory, the S bit is ignored.
 *
 * See the following two tables for setting TEX, S, C and B bits for
 * unprivileged flash, privileged flash and privileged RAM regions.
 *
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | TEX | C | B | Memory type            |  Description or Normal region cacheability             |  Shareable?             |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 000 | 0 | 0 | Strongly-ordered       |  Strongly ordered                                      |  Shareable              |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 000 | 0 | 1 | Device                 |  Shared device                                         |  Shareable              |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 000 | 1 | 0 | Normal                 |  Outer and inner   write-through; no write allocate    |  S bit                  |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 000 | 1 | 1 | Normal                 |  Outer and inner   write-back; no write allocate       |  S bit                  |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 001 | 0 | 0 | Normal                 |  Outer and inner   Non-cacheable                       |  S bit                  |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 001 | 0 | 1 | Reserved               |  Reserved                                              |  Reserved               |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 001 | 1 | 0 | IMPLEMENTATION DEFINED |  IMPLEMENTATION DEFINED                                |  IMPLEMENTATION DEFINED |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 001 | 1 | 1 | Normal                 |  Outer and inner   write-back; write and read allocate |  S bit                  |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 010 | 0 | 0 | Device                 |  Non-shared device                                     |  Not shareable          |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 010 | 0 | 1 | Reserved               |  Reserved                                              |  Reserved               |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 010 | 1 | X | Reserved               |  Reserved                                              |  Reserved               |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 011 | X | X | Reserved               |  Reserved                                              |  Reserved               |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 1BB | A | A | Normal                 | Cached memory, with AA and BB indicating the inner and |  Reserved               |
 |     |   |   |                        | outer cacheability rules that must be exported on the  |                         |
 |     |   |   |                        | bus. See the table below for the cacheability policy   |                         |
 |     |   |   |                        | encoding. memory, BB=Outer policy, AA=Inner policy.    |                         |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 |
 +-----------------------------------------+----------------------------------------+
 | AA or BB subfield of {TEX,C,B} encoding |  Cacheability policy                   |
 +-----------------------------------------+----------------------------------------+
 | 00                                      |  Non-cacheable                         |
 +-----------------------------------------+----------------------------------------+
 | 01                                      |  Write-back, write and   read allocate |
 +-----------------------------------------+----------------------------------------+
 | 10                                      |  Write-through, no write   allocate    |
 +-----------------------------------------+----------------------------------------+
 | 11                                      |  Write-back, no write   allocate       |
 +-----------------------------------------+----------------------------------------+
 */

/* TEX, Shareable (S), Cacheable (C) and Bufferable (B) bits for flash
 * region. */
#यदि_अपरिभाषितम् configTEX_S_C_B_FLASH
    /* Default to TEX=000, S=1, C=1, B=1 for backward compatibility. */
    #परिभाषय configTEX_S_C_B_FLASH    ( 0x07UL )
#यदि_अन्तः

/* TEX, Shareable (S), Cacheable (C) and Bufferable (B) bits for RAM
 * region. */
#यदि_अपरिभाषितम् configTEX_S_C_B_SRAM
    /* Default to TEX=000, S=1, C=1, B=1 for backward compatibility. */
    #परिभाषय configTEX_S_C_B_SRAM          ( 0x07UL )
#यदि_अन्तः

#परिभाषय पत्तनम्_राशिः_REGION                  ( config_योग_MPU_REGIONS - 5UL )
#परिभाषय पत्तनम्_GENERAL_PERIPHERALS_REGION    ( config_योग_MPU_REGIONS - 4UL )
#परिभाषय पत्तनम्_UNPRIVILEGED_FLASH_REGION     ( config_योग_MPU_REGIONS - 3UL )
#परिभाषय पत्तनम्_PRIVILEGED_FLASH_REGION       ( config_योग_MPU_REGIONS - 2UL )
#परिभाषय पत्तनम्_PRIVILEGED_RAM_REGION         ( config_योग_MPU_REGIONS - 1UL )
#परिभाषय पत्तनम्_FIRST_CONFIGURABLE_REGION     ( 0UL )
#परिभाषय पत्तनम्_चरमः_CONFIGURABLE_REGION      ( config_योग_MPU_REGIONS - 6UL )
#परिभाषय पत्तनम्_अङ्कः_CONFIGURABLE_REGIONS      ( config_योग_MPU_REGIONS - 5UL )
#परिभाषय पत्तनम्_योग_अङ्कः_REGIONS_अन्तर्_TCB      ( पत्तनम्_अङ्कः_CONFIGURABLE_REGIONS + 1 ) /* Plus 1 to create space for the stack region. */

प्रकारनिर्देश संरचना MPU_REGION_REGISTERS
{
    uint32_t ul_Region_आधारः_स्थानाङ्कः;
    uint32_t ulRegionAttribute;
} xMPU_REGION_REGISTERS;

प्रकारनिर्देश संरचना MPU_REGION_SETTINGS
{
    uint32_t ul_Region_Start_स्थानाङ्कः;
    uint32_t ul_Region_अन्तः_स्थानाङ्कः;
    uint32_t ulRegionPermissions;
} xMPU_REGION_SETTINGS;

#यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #यदि_अपरिभाषितम् config_SYSTEM_CALL_राशिः_आकार
        #दोषः "configSYSTEM_CALL_STACK_SIZE must be defined to the desired size of the system call stack in words for using MPU wrappers v2."
    #यदि_अन्तः

    प्रकारनिर्देश संरचना SYSTEM_CALL_राशिः_INFO
    {
        uint32_t ul_System_Call_राशिः_बफर[ config_SYSTEM_CALL_राशिः_आकार ];
        uint32_t * pul_System_Call_राशिः;
        uint32_t * pul_Task_राशिः;
        uint32_t ul_Link_पञ्जिकाकोशः_At_System_Call_प्रविष्टिः;
    } x_SYSTEM_CALL_राशिः_INFO;

#यदि_अन्तः /* configUSE_MPU_WRAPPERS_V1 == 0 */

/*
 * +---------+---------------+-----------------+-----------------+-----+
 * | s16-s31 | s0-s15, FPSCR | CONTROL, r4-r11 | PSP, r0-r3, r12 |     |
 * |         |               | EXC_RETURN      | LR, PC, xPSR    |     |
 * +---------+---------------+-----------------+-----------------+-----+
 *
 * <--------><---------------><----------------><----------------><---->
 *     16           17               10                 9           1
 */
#परिभाषय MAX_CONTEXT_आकार                    ( 53 )

/* Size of an Access Control List (ACL) entry in bits. */
#परिभाषय पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः             ( 32U )

/* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
#परिभाषय पत्तनम्_राशिः_FRAME_HAS_PADDING_FLAG    ( 1UL << 0UL )
#परिभाषय पत्तनम्_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

प्रकारनिर्देश संरचना MPU_SETTINGS
{
    xMPU_REGION_REGISTERS xRegion[ पत्तनम्_योग_अङ्कः_REGIONS_अन्तर्_TCB ];
    xMPU_REGION_SETTINGS xRegionSettings[ पत्तनम्_योग_अङ्कः_REGIONS_अन्तर्_TCB ];
    uint32_t ulContext[ MAX_CONTEXT_आकार ];
    uint32_t ulTaskFlags;

    #यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )
        x_SYSTEM_CALL_राशिः_INFO x_System_Call_राशिः_Info;
        #यदि ( configENABLE_ACCESS_CONTROL_LIST == 1 )
            uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_आकार / पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः ) + 1 ];
        #यदि_अन्तः
    #यदि_अन्तः
} xMPU_SETTINGS;

/* Architecture specifics. */
#परिभाषय पत्तनम्_राशिः_GROWTH      ( -1 )
#परिभाषय पत्तनम्_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
#परिभाषय पत्तनम्_BYTE_ALIGNMENT    8
#परिभाषय पत्तनम्_DONT_DISCARD      __attribute__( ( प्रयुक्तम् ) )
/*-----------------------------------------------------------*/

/* SVC numbers for various services. */
#परिभाषय पत्तनम्_SVC_START_SCHEDULER        100
#परिभाषय पत्तनम्_SVC_YIELD                  101
#परिभाषय पत्तनम्_SVC_RAISE_PRIVILEGE        102
#परिभाषय पत्तनम्_SVC_SYSTEM_CALL_EXIT       103

/* Scheduler utilities. */

#परिभाषय पत्तनम्_YIELD()    __asm चञ्चल ( "   SVC %0  \n" ::"i" ( पत्तनम्_SVC_YIELD ) : "memory" )
#परिभाषय पत्तनम्_YIELD_WITHIN_API()                          \
    {                                                   \
        /* Set a PendSV to request a context switch. */ \
        पत्तनम्_NVIC_INT_CTRL_REG = पत्तनम्_NVIC_PENDSVSET_BIT; \
                                                        \
        /* Barriers are normally not required but do ensure the code is completely \
         * within the specified behaviour for the architecture. */ \
        __asm चञ्चल ( "dsb" ::: "memory" );                     \
        __asm चञ्चल ( "isb" );                                  \
    }

#परिभाषय पत्तनम्_NVIC_INT_CTRL_REG     ( *( ( चञ्चल uint32_t * ) 0xe000ed04 ) )
#परिभाषय पत्तनम्_NVIC_PENDSVSET_BIT    ( 1UL << 28UL )
#परिभाषय पत्तनम्_अन्तः_SWITCHING_ISR( xSwitchRequired )            \
    कुरु                                                      \
    {                                                       \
        यदि( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_गन्तव्यम्_SCHEDULER();                   \
            पत्तनम्_NVIC_INT_CTRL_REG = पत्तनम्_NVIC_PENDSVSET_BIT; \
        }                                                   \
        अन्यथा                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } यावत्( 0 )
#परिभाषय पत्तनम्_YIELD_FROM_ISR( x )    पत्तनम्_अन्तः_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
बाह्य शून्य v_पत्तनम्_Enter_Critical( शून्य );
बाह्य शून्य v_पत्तनम्_Exit_Critical( शून्य );
#परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR()         ul_पत्तनम्_Raise_BASEPRI()
#परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( x )    v_पत्तनम्_समुच्चयः_BASEPRI( x )
#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()                  v_पत्तनम्_Raise_BASEPRI()
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()                   v_पत्तनम्_समुच्चयः_BASEPRI( 0 )
#परिभाषय पत्तनम्_ENTER_CRITICAL()                      v_पत्तनम्_Enter_Critical()
#परिभाषय पत्तनम्_EXIT_CRITICAL()                       v_पत्तनम्_Exit_Critical()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#यदि_अपरिभाषितम् config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION
    #परिभाषय config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION    1
#यदि_अन्तः

#यदि config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION == 1

/* Generic helper function. */
    __attribute__( ( always_inline ) ) स्थिर अन्तःस्थ uint8_t uc_पत्तनम्_गणनम्_Leading_Zeros( uint32_t ulBitmap )
    {
        uint8_t ucReturn;

        __asm चञ्चल ( "clz %0, %1" : "=r" ( ucReturn ) : "r" ( ulBitmap ) : "memory" );

        प्रत्यागम ucReturn;
    }

/* Check the configuration. */
    #यदि ( configMAX_PRIORITIES > 32 )
        #दोषः "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #यदि_अन्तः

/* Store/clear the ready priorities in a bit map. */
    #परिभाषय पत्तनम्_लेखः_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_प्राथमिकता ) )
    #परिभाषय पत्तनम्_RESET_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_प्राथमिकता ) )

/*-----------------------------------------------------------*/

    #परिभाषय पत्तनम्_GET_HIGHEST_प्राथमिकता( ux_शिखरम्_प्राथमिकता, uxReadyPriorities )    ux_शिखरम्_प्राथमिकता = ( 31UL - ( uint32_t ) uc_पत्तनम्_गणनम्_Leading_Zeros( ( uxReadyPriorities ) ) )

#यदि_अन्तः /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/*-----------------------------------------------------------*/

#यदि ( configASSERT_DEFINED == 1 )
    शून्य v_पत्तनम्_Validate_व्यवधानम्_प्राथमिकता( शून्य );
    #परिभाषय पत्तनम्_ASSERT_IF_व्यवधानम्_प्राथमिकता_INVALID()    v_पत्तनम्_Validate_व्यवधानम्_प्राथमिकता()
#यदि_अन्तः

/* portNOP() is not required by this port. */
#परिभाषय पत्तनम्_NOP()

#परिभाषय पत्तनम्_INLINE              __inline

#यदि_अपरिभाषितम् पत्तनम्_FORCE_INLINE
    #परिभाषय पत्तनम्_FORCE_INLINE    अन्तःस्थ __attribute__( ( always_inline ) )
#यदि_अन्तः
/*-----------------------------------------------------------*/

बाह्य आधारः_Type_t xIsPrivileged( शून्य );
बाह्य शून्य vResetPrivilege( शून्य );
बाह्य शून्य v_पत्तनम्_Switch_गन्तव्यम्_User_बहुलकम्( शून्य );

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
#परिभाषय पत्तनम्_IS_PRIVILEGED()          xIsPrivileged()

/**
 * @brief Raise an SVC request to raise privilege.
 */
#परिभाषय पत्तनम्_RAISE_PRIVILEGE()        __asm चञ्चल ( "svc %0 \n" ::"i" ( पत्तनम्_SVC_RAISE_PRIVILEGE ) : "memory" );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 */
#परिभाषय पत्तनम्_RESET_PRIVILEGE()        vResetPrivilege()

/**
 * @brief Make a task unprivileged.
 *
 * It must be called from privileged tasks only. Calling it from unprivileged
 * task will result in a memory protection fault.
 */
#परिभाषय पत्तनम्_SWITCH_गन्तव्यम्_USER_बहुलकम्()    v_पत्तनम्_Switch_गन्तव्यम्_User_बहुलकम्()
/*-----------------------------------------------------------*/

बाह्य आधारः_Type_t x_पत्तनम्_Is_Task_Privileged( शून्य );

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
#परिभाषय पत्तनम्_IS_TASK_PRIVILEGED()    x_पत्तनम्_Is_Task_Privileged()
/*-----------------------------------------------------------*/

पत्तनम्_FORCE_INLINE स्थिर आधारः_Type_t x_पत्तनम्_Is_Inside_व्यवधानम्( शून्य )
{
    uint32_t ul_Current_व्यवधानम्;
    आधारः_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    __asm चञ्चल ( "mrs %0, ipsr" : "=r" ( ul_Current_व्यवधानम् )::"memory" );

    यदि( ul_Current_व्यवधानम् == 0 )
    {
        xReturn = pdFALSE;
    }
    अन्यथा
    {
        xReturn = pdTRUE;
    }

    प्रत्यागम xReturn;
}

/*-----------------------------------------------------------*/

पत्तनम्_FORCE_INLINE स्थिर शून्य v_पत्तनम्_Raise_BASEPRI( शून्य )
{
    uint32_t ulNewBASEPRI;

    __asm चञ्चल
    (
        "   mov %0, %1                                              \n"
        #यदि ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
            "   cpsid i                                             \n" /* ARM Cortex-M7 r0p1 Errata 837070 workaround. */
        #यदि_अन्तः
        "   msr basepri, %0                                         \n"
        "   isb                                                     \n"
        "   dsb                                                     \n"
        #यदि ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
            "   cpsie i                                             \n" /* ARM Cortex-M7 r0p1 Errata 837070 workaround. */
        #यदि_अन्तः
        : "=r" ( ulNewBASEPRI ) : "i" ( config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता ) : "memory"
    );
}

/*-----------------------------------------------------------*/

पत्तनम्_FORCE_INLINE स्थिर uint32_t ul_पत्तनम्_Raise_BASEPRI( शून्य )
{
    uint32_t ulOriginalBASEPRI, ulNewBASEPRI;

    __asm चञ्चल
    (
        "   mrs %0, basepri                                         \n"
        "   mov %1, %2                                              \n"
        #यदि ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
            "   cpsid i                                             \n" /* ARM Cortex-M7 r0p1 Errata 837070 workaround. */
        #यदि_अन्तः
        "   msr basepri, %1                                         \n"
        "   isb                                                     \n"
        "   dsb                                                     \n"
        #यदि ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
            "   cpsie i                                             \n" /* ARM Cortex-M7 r0p1 Errata 837070 workaround. */
        #यदि_अन्तः
        : "=r" ( ulOriginalBASEPRI ), "=r" ( ulNewBASEPRI ) : "i" ( config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता ) : "memory"
    );

    /* This return will not be reached but is necessary to prevent compiler
     * warnings. */
    प्रत्यागम ulOriginalBASEPRI;
}
/*-----------------------------------------------------------*/

पत्तनम्_FORCE_INLINE स्थिर शून्य v_पत्तनम्_समुच्चयः_BASEPRI( uint32_t ul_New_आवरणम्_मानम् )
{
    __asm चञ्चल
    (
        "   msr basepri, %0 " ::"r" ( ul_New_आवरणम्_मानम् ) : "memory"
    );
}
/*-----------------------------------------------------------*/

#परिभाषय पत्तनम्_स्मृतिः_BARRIER()    __asm चञ्चल ( "" ::: "memory" )

#यदि_अपरिभाषितम् configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY
    #warning "configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY is not defined. We recommend defining it to 1 in FreeRTOSConfig.h for better security. www.FreeRTOS.org/FreeRTOS-V10.3.x.html"
    #परिभाषय configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY    0
#यदि_अन्तः
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
    #यदि_परिभाषितम् __cplusplus
        }
    #यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
