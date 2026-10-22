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


#अगर_अघोषित PORTMACRO_H
#घोषणा PORTMACRO_H

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    बाह्य "C" {
#पूर्ण_अगर
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
#घोषणा portCHAR          अक्षर
#घोषणा portFLOAT         भग्न
#घोषणा portDOUBLE        द्विगुन
#घोषणा portLONG          दीर्घ
#घोषणा portSHORT         लघु
#घोषणा port_ढेर_TYPE    uint32_t
#घोषणा portBASE_TYPE     दीर्घ

प्रकार port_ढेर_TYPE   ढेर_Type_t;
प्रकार दीर्घ             BaseType_t;
प्रकार अचिन्हित दीर्घ    UBaseType_t;

#अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    प्रकार uint16_t     TickType_t;
    #घोषणा portMAX_DELAY              ( TickType_t ) 0xffff
#या_अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    प्रकार uint32_t     TickType_t;
    #घोषणा portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #घोषणा portTICK_TYPE_IS_ATOMIC    1
#अन्यथा
    #त्रुटि configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#पूर्ण_अगर
/*-----------------------------------------------------------*/

/* MPU specific constants. */
#घोषणा portUSING_MPU_WRAPPERS                                   1
#घोषणा portPRIVILEGE_BIT                                        ( 0x80000000UL )

#घोषणा portMPU_REGION_READ_WRITE                                ( 0x03UL << 24UL )
#घोषणा portMPU_REGION_PRIVILEGED_READ_ONLY                      ( 0x05UL << 24UL )
#घोषणा portMPU_REGION_READ_ONLY                                 ( 0x06UL << 24UL )
#घोषणा portMPU_REGION_PRIVILEGED_READ_WRITE                     ( 0x01UL << 24UL )
#घोषणा portMPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY    ( 0x02UL << 24UL )
#घोषणा portMPU_REGION_CACHEABLE_BUFFERABLE                      ( 0x07UL << 16UL )
#घोषणा portMPU_REGION_EXECUTE_NEVER                             ( 0x01UL << 28UL )

#घोषणा port_ढेर_REGION                                         ( 3UL )
#घोषणा portGENERAL_PERIPHERALS_REGION                           ( 4UL )
#घोषणा portUNPRIVILEGED_FLASH_REGION                            ( 5UL )
#घोषणा portPRIVILEGED_FLASH_REGION                              ( 6UL )
#घोषणा portPRIVILEGED_RAM_REGION                                ( 7UL )
#घोषणा portFIRST_CONFIGURABLE_REGION                            ( 0UL )
#घोषणा portLAST_CONFIGURABLE_REGION                             ( 2UL )
#घोषणा port_अंक_CONFIGURABLE_REGIONS                             ( ( portLAST_CONFIGURABLE_REGION - portFIRST_CONFIGURABLE_REGION ) + 1 )
#घोषणा port_योग_अंक_REGIONS_IN_TCB                             ( port_अंक_CONFIGURABLE_REGIONS + 1 )     /* Plus one to make space for the stack region. */

प्रकार काष्ठा MPU_REGION_REGISTERS
{
    uint32_t ulRegionBaseAddress;
    uint32_t ulRegionAttribute;
} xMPU_REGION_REGISTERS;

प्रकार काष्ठा MPU_REGION_SETTINGS
{
    uint32_t ulRegionStartAddress;
    uint32_t ulRegionEndAddress;
    uint32_t ulRegionPermissions;
} xMPU_REGION_SETTINGS;

#अगर ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #अगर_अघोषित config_SYSTEM_CALL_ढेर_आकार
        #त्रुटि config_SYSTEM_CALL_ढेर_आकार must be defined to the desired आकार of the प्रणाली call ढेर in शब्दगण क्रम using MPU wrappers v2.
    #पूर्ण_अगर

    प्रकार काष्ठा SYSTEM_CALL_ढेर_INFO
    {
        uint32_t ul_System_Call_ढेर_बफर[ config_SYSTEM_CALL_ढेर_आकार ];
        uint32_t * pul_System_Call_ढेर;
        uint32_t * pul_Task_ढेर;
        uint32_t ulLinkRegisterAtSystemCallEntry;
    } x_SYSTEM_CALL_ढेर_INFO;

#पूर्ण_अगर /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*
 * +------------------------------+-------------------------------+-----+
 * |  CONTROL, r4-r11, EXC_RETURN | PSP, r0-r3, r12, LR, PC, xPSR |     |
 * +------------------------------+-------------------------------+-----+
 *
 * <-----------------------------><-------------------------------><---->
 *                10                             9                   1
 */
#घोषणा MAX_CONTEXT_आकार                    ( 20 )

/* Size of an Access Control List (ACL) entry in bits. */
#घोषणा port_ACL_ENTRY_आकार_BITS             ( 32U )

/* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
#घोषणा port_ढेर_FRAME_HAS_PADDING_FLAG    ( 1UL << 0UL )
#घोषणा portTASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

प्रकार काष्ठा MPU_SETTINGS
{
    xMPU_REGION_REGISTERS xRegion[ port_योग_अंक_REGIONS_IN_TCB ];
    xMPU_REGION_SETTINGS xRegionSettings[ port_योग_अंक_REGIONS_IN_TCB ];
    uint32_t ulContext[ MAX_CONTEXT_आकार ];
    uint32_t ulTaskFlags;

    #अगर ( configUSE_MPU_WRAPPERS_V1 == 0 )
        x_SYSTEM_CALL_ढेर_INFO x_System_Call_ढेर_Info;
        #अगर ( configENABLE_ACCESS_CONTROL_LIST == 1 )
            uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_आकार / port_ACL_ENTRY_आकार_BITS ) + 1 ];
        #पूर्ण_अगर
    #पूर्ण_अगर
} xMPU_SETTINGS;

/* Architecture specifics. */
#घोषणा port_ढेर_GROWTH      ( -1 )
#घोषणा portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#घोषणा portBYTE_ALIGNMENT    8
#घोषणा portDONT_DISCARD      __attribute__( ( used ) )
/*-----------------------------------------------------------*/

/* SVC numbers for various services. */
#घोषणा portSVC_START_SCHEDULER        100
#घोषणा portSVC_YIELD                  101
#घोषणा portSVC_RAISE_PRIVILEGE        102
#घोषणा portSVC_SYSTEM_CALL_EXIT       103

/* Scheduler utilities. */

#घोषणा portYIELD()    __asm अस्थिर ( "   SVC %0  \n" ::"i" ( portSVC_YIELD ) : "memory" )
#घोषणा portYIELD_WITHIN_API()                          \
    {                                                   \
        /* Set a PendSV to request a context switch. */ \
        portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT; \
                                                        \
        /* Barriers are normally not required but do ensure the code is completely \
         * within the specified behaviour for the architecture. */ \
        __asm अस्थिर ( "dsb" ::: "memory" );                     \
        __asm अस्थिर ( "isb" );                                  \
    }

#घोषणा portNVIC_INT_CTRL_REG     ( *( ( अस्थिर uint32_t * ) 0xe000ed04 ) )
#घोषणा portNVIC_PENDSVSET_BIT    ( 1UL << 28UL )
#घोषणा portEND_SWITCHING_ISR( xSwitchRequired )            \
    करो                                                      \
    {                                                       \
        अगर( xSwitchRequired )                               \
        {                                                   \
            traceISR_EXIT_TO_SCHEDULER();                   \
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT; \
        }                                                   \
        अन्यथा                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } जबतक( 0 )
#घोषणा portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
बाह्य व्योम vPortEnterCritical( व्योम );
बाह्य व्योम vPortExitCritical( व्योम );
#घोषणा portSET_INTERRUPT_MASK_FROM_ISR()         ulPortRaiseBASEPRI()
#घोषणा portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    vPortSetBASEPRI( x )
#घोषणा portDISABLE_INTERRUPTS()                  vPortRaiseBASEPRI()
#घोषणा portENABLE_INTERRUPTS()                   vPortSetBASEPRI( 0 )
#घोषणा portENTER_CRITICAL()                      vPortEnterCritical()
#घोषणा portEXIT_CRITICAL()                       vPortExitCritical()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
#घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )    व्योम vFunction( व्योम * pvParameters )
#घोषणा portTASK_FUNCTION( vFunction, pvParameters )          व्योम vFunction( व्योम * pvParameters )
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#अगर_अघोषित configUSE_PORT_OPTIMISED_TASK_SELECTION
    #घोषणा configUSE_PORT_OPTIMISED_TASK_SELECTION    1
#पूर्ण_अगर

#अगर configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

/* Generic helper function. */
    __attribute__( ( always_inline ) ) अटल अंतरभूत uint8_t uc_Port_गिनती_Leading_Zeros( uint32_t ulBitmap )
    {
        uint8_t ucReturn;

        __asm अस्थिर ( "clz %0, %1" : "=r" ( ucReturn ) : "r" ( ulBitmap ) : "memory" );

        वापस ucReturn;
    }

/* Check the configuration. */
    #अगर ( configMAX_PRIORITIES > 32 )
        #त्रुटि configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a प्रणाली requires more than 10 to 15 difference priorities as tasks that share a priority will समय slice.
    #पूर्ण_अगर

/* Store/clear the ready priorities in a bit map. */
    #घोषणा portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #घोषणा portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

/*-----------------------------------------------------------*/

    #घोषणा portGET_HIGHEST_PRIORITY( ux_शीर्ष_Priority, uxReadyPriorities )    ux_शीर्ष_Priority = ( 31UL - ( uint32_t ) uc_Port_गिनती_Leading_Zeros( ( uxReadyPriorities ) ) )

#पूर्ण_अगर /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/*-----------------------------------------------------------*/

#अगर ( configASSERT_DEFINED == 1 )
    व्योम vPortValidateInterruptPriority( व्योम );
    #घोषणा portASSERT_IF_INTERRUPT_PRIORITY_INVALID()    vPortValidateInterruptPriority()
#पूर्ण_अगर

/* portNOP() is not required by this port. */
#घोषणा portNOP()

#घोषणा portINLINE              __inline

#अगर_अघोषित portFORCE_INLINE
    #घोषणा portFORCE_INLINE    अंतरभूत __attribute__( ( always_inline ) )
#पूर्ण_अगर
/*-----------------------------------------------------------*/

बाह्य BaseType_t xIsPrivileged( व्योम );
बाह्य व्योम vResetPrivilege( व्योम );
बाह्य व्योम vPortSwitchToUserMode( व्योम );

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
#घोषणा portIS_PRIVILEGED()          xIsPrivileged()

/**
 * @brief Raise an SVC request to raise privilege.
 */
#घोषणा portRAISE_PRIVILEGE()        __asm अस्थिर ( "svc %0 \n" ::"i" ( portSVC_RAISE_PRIVILEGE ) : "memory" );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 */
#घोषणा portRESET_PRIVILEGE()        vResetPrivilege()

/**
 * @brief Make a task unprivileged.
 *
 * It must be called from privileged tasks only. Calling it from unprivileged
 * task will result in a memory protection fault.
 */
#घोषणा portSWITCH_TO_USER_MODE()    vPortSwitchToUserMode()
/*-----------------------------------------------------------*/

बाह्य BaseType_t xPortIsTaskPrivileged( व्योम );

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
#घोषणा portIS_TASK_PRIVILEGED()    xPortIsTaskPrivileged()
/*-----------------------------------------------------------*/

portFORCE_INLINE अटल BaseType_t xPortIsInsideInterrupt( व्योम )
{
    uint32_t ulCurrentInterrupt;
    BaseType_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    __asm अस्थिर ( "mrs %0, ipsr" : "=r" ( ulCurrentInterrupt )::"memory" );

    अगर( ulCurrentInterrupt == 0 )
    {
        xReturn = pdFALSE;
    }
    अन्यथा
    {
        xReturn = pdTRUE;
    }

    वापस xReturn;
}

/*-----------------------------------------------------------*/

portFORCE_INLINE अटल व्योम vPortRaiseBASEPRI( व्योम )
{
    uint32_t ulNewBASEPRI;

    __asm अस्थिर
    (
        "   mov %0, %1                                              \n" \
        "   msr basepri, %0                                         \n" \
        "   isb                                                     \n" \
        "   dsb                                                     \n" \
        : "=r" ( ulNewBASEPRI ) : "i" ( configMAX_SYSCALL_INTERRUPT_PRIORITY ) : "memory"
    );
}

/*-----------------------------------------------------------*/

portFORCE_INLINE अटल uint32_t ulPortRaiseBASEPRI( व्योम )
{
    uint32_t ulOriginalBASEPRI, ulNewBASEPRI;

    __asm अस्थिर
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
    वापस ulOriginalBASEPRI;
}
/*-----------------------------------------------------------*/

portFORCE_INLINE अटल व्योम vPortSetBASEPRI( uint32_t ul_New_Mask_मूल्य )
{
    __asm अस्थिर
    (
        "   msr basepri, %0 " ::"r" ( ul_New_Mask_मूल्य ) : "memory"
    );
}
/*-----------------------------------------------------------*/

#घोषणा portMEMORY_BARRIER()    __asm अस्थिर ( "" ::: "memory" )

#अगर_अघोषित configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY
    #warning "configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY is not defined. We recommend defining it to 1 in FreeRTOSConfig.h for better security. *www.FreeRTOS.org/FreeRTOS-V10.3.x.html"
    #घोषणा configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY    0
#पूर्ण_अगर
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* PORTMACRO_H */
