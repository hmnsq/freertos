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


#ifndef PORTMACRO_H
#define PORTMACRO_H

/* *INDENT-OFF* */
#ifdef __cplusplus
    बाह्य "C" {
#endif
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
#define portCHAR          वर्ण
#define portFLOAT         भिन्न
#define portDOUBLE        द्विगुण
#define portLONG          दीर्घ
#define portSHORT         लघु
#define port_थाक_TYPE    uint32_t
#define portBASE_TYPE     दीर्घ

प्रकारनिर्देश port_थाक_TYPE   थाक_Type_t;
प्रकारनिर्देश दीर्घ             BaseType_t;
प्रकारनिर्देश अचिन्हित दीर्घ    UBaseType_t;

#यदि ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    प्रकारनिर्देश uint16_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffff
#अथवायदि ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    प्रकारनिर्देश uint32_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #define portTICK_TYPE_IS_ATOMIC    1
#अन्यथा
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* MPU specific constants. */
#define portUSING_MPU_WRAPPERS                                   1
#define portPRIVILEGE_BIT                                        ( 0x80000000UL )

#define portMPU_REGION_READ_WRITE                                ( 0x03UL << 24UL )
#define portMPU_REGION_PRIVILEGED_READ_ONLY                      ( 0x05UL << 24UL )
#define portMPU_REGION_READ_ONLY                                 ( 0x06UL << 24UL )
#define portMPU_REGION_PRIVILEGED_READ_WRITE                     ( 0x01UL << 24UL )
#define portMPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY    ( 0x02UL << 24UL )
#define portMPU_REGION_CACHEABLE_BUFFERABLE                      ( 0x07UL << 16UL )
#define portMPU_REGION_EXECUTE_NEVER                             ( 0x01UL << 28UL )

#define port_थाक_REGION                                         ( 3UL )
#define portGENERAL_PERIPHERALS_REGION                           ( 4UL )
#define portUNPRIVILEGED_FLASH_REGION                            ( 5UL )
#define portPRIVILEGED_FLASH_REGION                              ( 6UL )
#define portPRIVILEGED_RAM_REGION                                ( 7UL )
#define portFIRST_CONFIGURABLE_REGION                            ( 0UL )
#define portLAST_CONFIGURABLE_REGION                             ( 2UL )
#define port_अङ्क_CONFIGURABLE_REGIONS                             ( ( portLAST_CONFIGURABLE_REGION - portFIRST_CONFIGURABLE_REGION ) + 1 )
#define port_TOTAL_अङ्क_REGIONS_IN_TCB                             ( port_अङ्क_CONFIGURABLE_REGIONS + 1 )     /* Plus one to make space for the stack region. */

प्रकारनिर्देश संरचना MPU_REGION_REGISTERS
{
    uint32_t ulRegionBaseAddress;
    uint32_t ulRegionAttribute;
} xMPU_REGION_REGISTERS;

प्रकारनिर्देश संरचना MPU_REGION_SETTINGS
{
    uint32_t ulRegionStartAddress;
    uint32_t ulRegionEndAddress;
    uint32_t ulRegionPermissions;
} xMPU_REGION_SETTINGS;

#यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #ifndef config_SYSTEM_CALL_थाक_SIZE
        #error config_SYSTEM_CALL_थाक_SIZE must be defined to the desired size of the प्रणाली call थाक in शब्दहरू लागि using MPU wrappers v2.
    #endif

    प्रकारनिर्देश संरचना SYSTEM_CALL_थाक_INFO
    {
        uint32_t ul_System_Call_थाक_Buffer[ config_SYSTEM_CALL_थाक_SIZE ];
        uint32_t * pul_System_Call_थाक;
        uint32_t * pul_Task_थाक;
        uint32_t ulLinkRegisterAtSystemCallEntry;
    } x_SYSTEM_CALL_थाक_INFO;

#endif /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*
 * +------------------------------+-------------------------------+-----+
 * |  CONTROL, r4-r11, EXC_RETURN | PSP, r0-r3, r12, LR, PC, xPSR |     |
 * +------------------------------+-------------------------------+-----+
 *
 * <-----------------------------><-------------------------------><---->
 *                10                             9                   1
 */
#define MAX_CONTEXT_SIZE                    ( 20 )

/* Size of an Access Control List (ACL) entry in bits. */
#define portACL_ENTRY_SIZE_BITS             ( 32U )

/* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
#define port_थाक_FRAME_HAS_PADDING_FLAG    ( 1UL << 0UL )
#define portTASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

प्रकारनिर्देश संरचना MPU_SETTINGS
{
    xMPU_REGION_REGISTERS xRegion[ port_TOTAL_अङ्क_REGIONS_IN_TCB ];
    xMPU_REGION_SETTINGS xRegionSettings[ port_TOTAL_अङ्क_REGIONS_IN_TCB ];
    uint32_t ulContext[ MAX_CONTEXT_SIZE ];
    uint32_t ulTaskFlags;

    #यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )
        x_SYSTEM_CALL_थाक_INFO x_System_Call_थाक_Info;
        #यदि ( configENABLE_ACCESS_CONTROL_LIST == 1 )
            uint32_t ulAccessControlList[ ( configPROTECTED_KERNEL_OBJECT_POOL_SIZE / portACL_ENTRY_SIZE_BITS ) + 1 ];
        #endif
    #endif
} xMPU_SETTINGS;

/* Architecture specifics. */
#define port_थाक_GROWTH      ( -1 )
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT    8
#define portDONT_DISCARD      __attribute__( ( used ) )
/*-----------------------------------------------------------*/

/* SVC numbers for various services. */
#define portSVC_START_SCHEDULER        100
#define portSVC_YIELD                  101
#define portSVC_RAISE_PRIVILEGE        102
#define portSVC_SYSTEM_CALL_EXIT       103

/* Scheduler utilities. */

#define portYIELD()    __asm चञ्चल ( "   SVC %0  \n" ::"i" ( portSVC_YIELD ) : "memory" )
#define portYIELD_WITHIN_API()                          \
    {                                                   \
        /* Set a PendSV to request a context switch. */ \
        portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT; \
                                                        \
        /* Barriers are normally not required but do ensure the code is completely \
         * within the specified behaviour for the architecture. */ \
        __asm चञ्चल ( "dsb" ::: "memory" );                     \
        __asm चञ्चल ( "isb" );                                  \
    }

#define portNVIC_INT_CTRL_REG     ( *( ( चञ्चल uint32_t * ) 0xe000ed04 ) )
#define portNVIC_PENDSVSET_BIT    ( 1UL << 28UL )
#define portEND_SWITCHING_ISR( xSwitchRequired )            \
    गर                                                      \
    {                                                       \
        यदि( xSwitchRequired )                               \
        {                                                   \
            traceISR_EXIT_TO_SCHEDULER();                   \
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT; \
        }                                                   \
        अन्यथा                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } जबसम्म( 0 )
#define portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
बाह्य शून्य vPortEnterCritical( शून्य );
बाह्य शून्य vPortExitCritical( शून्य );
#define portSET_INTERRUPT_MASK_FROM_ISR()         ulPortRaiseBASEPRI()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    vPortSetBASEPRI( x )
#define portDISABLE_INTERRUPTS()                  vPortRaiseBASEPRI()
#define portENABLE_INTERRUPTS()                   vPortSetBASEPRI( 0 )
#define portENTER_CRITICAL()                      vPortEnterCritical()
#define portEXIT_CRITICAL()                       vPortExitCritical()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION
    #define configUSE_PORT_OPTIMISED_TASK_SELECTION    1
#endif

#यदि configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

/* Generic helper function. */
    __attribute__( ( always_inline ) ) स्थिर अन्तःस्थ uint8_t uc_Port_गन्ती_Leading_Zeros( uint32_t ulBitmap )
    {
        uint8_t ucReturn;

        __asm चञ्चल ( "clz %0, %1" : "=r" ( ucReturn ) : "r" ( ulBitmap ) : "memory" );

        फर्काऊ ucReturn;
    }

/* Check the configuration. */
    #यदि ( configMAX_PRIORITIES > 32 )
        #error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a प्रणाली requires more than 10 to 15 difference priorities as tasks that share a priority will समय slice.
    #endif

/* Store/clear the ready priorities in a bit map. */
    #define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

/*-----------------------------------------------------------*/

    #define portGET_HIGHEST_PRIORITY( ux_शीर्ष_Priority, uxReadyPriorities )    ux_शीर्ष_Priority = ( 31UL - ( uint32_t ) uc_Port_गन्ती_Leading_Zeros( ( uxReadyPriorities ) ) )

#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/*-----------------------------------------------------------*/

#यदि ( configASSERT_DEFINED == 1 )
    शून्य vPortValidateInterruptPriority( शून्य );
    #define portASSERT_IF_INTERRUPT_PRIORITY_INVALID()    vPortValidateInterruptPriority()
#endif

/* portNOP() is not required by this port. */
#define portNOP()

#define portINLINE              __inline

#ifndef portFORCE_INLINE
    #define portFORCE_INLINE    अन्तःस्थ __attribute__( ( always_inline ) )
#endif
/*-----------------------------------------------------------*/

बाह्य BaseType_t xIsPrivileged( शून्य );
बाह्य शून्य vResetPrivilege( शून्य );
बाह्य शून्य vPortSwitchToUserMode( शून्य );

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
#define portIS_PRIVILEGED()          xIsPrivileged()

/**
 * @brief Raise an SVC request to raise privilege.
 */
#define portRAISE_PRIVILEGE()        __asm चञ्चल ( "svc %0 \n" ::"i" ( portSVC_RAISE_PRIVILEGE ) : "memory" );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 */
#define portRESET_PRIVILEGE()        vResetPrivilege()

/**
 * @brief Make a task unprivileged.
 *
 * It must be called from privileged tasks only. Calling it from unprivileged
 * task will result in a memory protection fault.
 */
#define portSWITCH_TO_USER_MODE()    vPortSwitchToUserMode()
/*-----------------------------------------------------------*/

बाह्य BaseType_t xPortIsTaskPrivileged( शून्य );

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
#define portIS_TASK_PRIVILEGED()    xPortIsTaskPrivileged()
/*-----------------------------------------------------------*/

portFORCE_INLINE स्थिर BaseType_t xPortIsInsideInterrupt( शून्य )
{
    uint32_t ulCurrentInterrupt;
    BaseType_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    __asm चञ्चल ( "mrs %0, ipsr" : "=r" ( ulCurrentInterrupt )::"memory" );

    यदि( ulCurrentInterrupt == 0 )
    {
        xReturn = pdFALSE;
    }
    अन्यथा
    {
        xReturn = pdTRUE;
    }

    फर्काऊ xReturn;
}

/*-----------------------------------------------------------*/

portFORCE_INLINE स्थिर शून्य vPortRaiseBASEPRI( शून्य )
{
    uint32_t ulNewBASEPRI;

    __asm चञ्चल
    (
        "   mov %0, %1                                              \n" \
        "   msr basepri, %0                                         \n" \
        "   isb                                                     \n" \
        "   dsb                                                     \n" \
        : "=r" ( ulNewBASEPRI ) : "i" ( configMAX_SYSCALL_INTERRUPT_PRIORITY ) : "memory"
    );
}

/*-----------------------------------------------------------*/

portFORCE_INLINE स्थिर uint32_t ulPortRaiseBASEPRI( शून्य )
{
    uint32_t ulOriginalBASEPRI, ulNewBASEPRI;

    __asm चञ्चल
    (
        "   mrs %0, basepri                                         \n" \
        "   mov %1, %2                                              \n" \
        "   msr basepri, %1                                         \n" \
        "   isb                                                     \n" \
        "   dsb                                                     \n" \
        : "=r" ( ulOriginalBASEPRI ), "=r" ( ulNewBASEPRI ) : "i" ( configMAX_SYSCALL_INTERRUPT_PRIORITY ) : "memory"
    );

    /* This return will not be reached but is necessary to prevent compiler
     * warnings. */
    फर्काऊ ulOriginalBASEPRI;
}
/*-----------------------------------------------------------*/

portFORCE_INLINE स्थिर शून्य vPortSetBASEPRI( uint32_t ul_New_Mask_मान )
{
    __asm चञ्चल
    (
        "   msr basepri, %0 " ::"r" ( ul_New_Mask_मान ) : "memory"
    );
}
/*-----------------------------------------------------------*/

#define portMEMORY_BARRIER()    __asm चञ्चल ( "" ::: "memory" )

#ifndef configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY
    #warning "configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY is not defined. We recommend defining it to 1 in FreeRTOSConfig.h for better security. *www.FreeRTOS.org/FreeRTOS-V10.3.x.html"
    #define configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY    0
#endif
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
