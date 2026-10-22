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


#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PORTMACRO_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMACRO_H

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ
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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHAR          ਅੱਖਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FLOAT         ਦਸ਼ਮਲਵ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DOUBLE        ਦੁੱਗਣਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_LONG          ਲੰਮਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SHORT         ਛੋਟਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_TYPE    uint32_t
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅਧਾਰ_TYPE     ਲੰਮਾ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੋਰਟ_ਢੇਰ_TYPE   ਢੇਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਲੰਮਾ             ਅਧਾਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ    UBaseType_t;

#ਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_16_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint16_t     TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY              ( TickType_t ) 0xffff
#ਜਾਂਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_32_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t     TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_TYPE_IS_ATOMIC    1
#ਨਹੀਂਤਾਂ
    #ਗਲਤੀ config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ ਸੈੱਟ ਮੰਜ਼ਿਲ unsupported tick type ਚੌੜਾਈ.
#ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

/* MPU specific constants. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_USING_MPU_WRAPPERS                                   1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIVILEGE_ਦੋਆਧਾਰੀ_ਅੰਕ                                        ( 0x80000000UL )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_READ_WRITE                                ( 0x03UL << 24UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_PRIVILEGED_READ_ONLY                      ( 0x05UL << 24UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_READ_ONLY                                 ( 0x06UL << 24UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_PRIVILEGED_READ_WRITE                     ( 0x01UL << 24UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY    ( 0x02UL << 24UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_CACHEABLE_BUFFERABLE                      ( 0x07UL << 16UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_EXECUTE_NEVER                             ( 0x01UL << 28UL )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_REGION                                         ( 3UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GENERAL_PERIPHERALS_REGION                           ( 4UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_UNPRIVILEGED_FLASH_REGION                            ( 5UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIVILEGED_FLASH_REGION                              ( 6UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIVILEGED_RAM_REGION                                ( 7UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਪਹਿਲਾ_CONFIGURABLE_REGION                            ( 0UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਆਖਰੀ_CONFIGURABLE_REGION                             ( 2UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅੰਕ_CONFIGURABLE_REGIONS                             ( ( ਪੋਰਟ_ਆਖਰੀ_CONFIGURABLE_REGION - ਪੋਰਟ_ਪਹਿਲਾ_CONFIGURABLE_REGION ) + 1 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਕੁੱਲ_ਅੰਕ_REGIONS_ਵਿੱਚ_TCB                             ( ਪੋਰਟ_ਅੰਕ_CONFIGURABLE_REGIONS + 1 )     /* Plus one to make space for the stack region. */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ MPU_REGION_REGISTERS
{
    uint32_t ul_Region_ਅਧਾਰ_ਪਤਾ;
    uint32_t ulRegionAttribute;
} xMPU_REGION_REGISTERS;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ MPU_REGION_SETTINGS
{
    uint32_t ul_Region_ਸ਼ੁਰੂ_ਪਤਾ;
    uint32_t ul_Region_ਸਿਰਾ_ਪਤਾ;
    uint32_t ulRegionPermissions;
} xMPU_REGION_SETTINGS;

#ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_SYSTEM_CALL_ਢੇਰ_ਮਾਪ
        #ਗਲਤੀ config_SYSTEM_CALL_ਢੇਰ_ਮਾਪ must be defined ਮੰਜ਼ਿਲ the desired ਮਾਪ ਦਾ the system call ਢੇਰ ਵਿੱਚ_2 ਸ਼ਬਦ ਲਈ using MPU wrappers v2.
    #ਜੇ_ਅੰਤ

    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SYSTEM_CALL_ਢੇਰ_INFO
    {
        uint32_t ul_System_Call_ਢੇਰ_ਬਫਰ[ config_SYSTEM_CALL_ਢੇਰ_ਮਾਪ ];
        uint32_t * pul_System_Call_ਢੇਰ;
        uint32_t * pul_Task_ਢੇਰ;
        uint32_t ul_Link_ਰਜਿਸਟਰ_At_System_Call_ਇੰਦਰਾਜ;
    } x_SYSTEM_CALL_ਢੇਰ_INFO;

#ਜੇ_ਅੰਤ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*
 * +------------------------------+-------------------------------+-----+
 * |  CONTROL, r4-r11, EXC_RETURN | PSP, r0-r3, r12, LR, PC, xPSR |     |
 * +------------------------------+-------------------------------+-----+
 *
 * <-----------------------------><-------------------------------><---->
 *                10                             9                   1
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_CONTEXT_ਮਾਪ                    ( 20 )

/* Size of an Access Control List (ACL) entry in bits. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ             ( 32U )

/* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_ਚੌਖਟਾ_HAS_PADDING_FLAG    ( 1UL << 0UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ MPU_SETTINGS
{
    xMPU_REGION_REGISTERS xRegion[ ਪੋਰਟ_ਕੁੱਲ_ਅੰਕ_REGIONS_ਵਿੱਚ_TCB ];
    xMPU_REGION_SETTINGS xRegionSettings[ ਪੋਰਟ_ਕੁੱਲ_ਅੰਕ_REGIONS_ਵਿੱਚ_TCB ];
    uint32_t ulContext[ MAX_CONTEXT_ਮਾਪ ];
    uint32_t ulTaskFlags;

    #ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 0 )
        x_SYSTEM_CALL_ਢੇਰ_INFO x_System_Call_ਢੇਰ_Info;
        #ਜੇ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
            uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_ਮਾਪ / ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ ) + 1 ];
        #ਜੇ_ਅੰਤ
    #ਜੇ_ਅੰਤ
} xMPU_SETTINGS;

/* Architecture specifics. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_GROWTH      ( -1 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_ਦਰ_HZ )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_BYTE_ALIGNMENT    8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DONT_DISCARD      __attribute__( ( ਵਰਤਿਆ ) )
/*-----------------------------------------------------------*/

/* SVC numbers for various services. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_ਸ਼ੁਰੂ_SCHEDULER        100
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_YIELD                  101
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_RAISE_PRIVILEGE        102
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_SYSTEM_CALL_EXIT       103

/* Scheduler utilities. */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD()    __asm ਅਸਥਿਰ ( "   SVC %0  \n" ::"i" ( ਪੋਰਟ_SVC_YIELD ) : "memory" )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_WITHIN_API()                          \
    {                                                   \
        /* Set a PendSV to request a context switch. */ \
        ਪੋਰਟ_NVIC_INT_CTRL_REG = ਪੋਰਟ_NVIC_PENDSVSET_ਦੋਆਧਾਰੀ_ਅੰਕ; \
                                                        \
        /* Barriers are normally not required but do ensure the code is completely \
         * within the specified behaviour for the architecture. */ \
        __asm ਅਸਥਿਰ ( "dsb" ::: "memory" );                     \
        __asm ਅਸਥਿਰ ( "isb" );                                  \
    }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_INT_CTRL_REG     ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed04 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_PENDSVSET_ਦੋਆਧਾਰੀ_ਅੰਕ    ( 1UL << 28UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਿਰਾ_SWITCHING_ISR( xSwitchRequired )            \
    ਕਰੋ                                                      \
    {                                                       \
        ਜੇ( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_ਮੰਜ਼ਿਲ_SCHEDULER();                   \
            ਪੋਰਟ_NVIC_INT_CTRL_REG = ਪੋਰਟ_NVIC_PENDSVSET_ਦੋਆਧਾਰੀ_ਅੰਕ; \
        }                                                   \
        ਨਹੀਂਤਾਂ                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } ਜਦੋਂ( 0 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_FROM_ISR( x )    ਪੋਰਟ_ਸਿਰਾ_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ );
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ );
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR()         ul_ਪੋਰਟ_Raise_BASEPRI()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( x )    v_ਪੋਰਟ_ਸੈੱਟ_BASEPRI( x )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DISABLE_INTERRUPTS()                  v_ਪੋਰਟ_Raise_BASEPRI()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENABLE_INTERRUPTS()                   v_ਪੋਰਟ_ਸੈੱਟ_BASEPRI( 0 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL()                      v_ਪੋਰਟ_Enter_Critical()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL()                       v_ਪੋਰਟ_Exit_Critical()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION( vFunction, pvParameters )          ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION    1
#ਜੇ_ਅੰਤ

#ਜੇ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION == 1

/* Generic helper function. */
    __attribute__( ( always_inline ) ) ਸਥਿਰ ਸਤਰਅੰਦਰ uint8_t uc_ਪੋਰਟ_ਗਿਣਤੀ_Leading_Zeros( uint32_t ulBitmap )
    {
        uint8_t ucReturn;

        __asm ਅਸਥਿਰ ( "clz %0, %1" : "=r" ( ucReturn ) : "r" ( ulBitmap ) : "memory" );

        ਵਾਪਸ ucReturn;
    }

/* Check the configuration. */
    #ਜੇ ( configMAX_PRIORITIES > 32 )
        #ਗਲਤੀ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION can only be ਸੈੱਟ ਮੰਜ਼ਿਲ 1 when configMAX_PRIORITIES is less than or equal ਮੰਜ਼ਿਲ 32.  It is very rare that a system requires ਹੋਰ than 10 ਮੰਜ਼ਿਲ 15 difference priorities as tasks that share a ਤਰਜੀਹ will time ਟੁਕੜਾ.
    #ਜੇ_ਅੰਤ

/* Store/clear the ready priorities in a bit map. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਰਿਕਾਰਡ_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ਤਰਜੀਹ ) )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESET_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ਤਰਜੀਹ ) )

/*-----------------------------------------------------------*/

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_HIGHEST_ਤਰਜੀਹ( ux_ਸਿਖਰ_ਤਰਜੀਹ, uxReadyPriorities )    ux_ਸਿਖਰ_ਤਰਜੀਹ = ( 31UL - ( uint32_t ) uc_ਪੋਰਟ_ਗਿਣਤੀ_Leading_Zeros( ( uxReadyPriorities ) ) )

#ਜੇ_ਅੰਤ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/*-----------------------------------------------------------*/

#ਜੇ ( configASSERT_DEFINED == 1 )
    ਖਾਲੀ v_ਪੋਰਟ_Validate_ਰੁਕਾਵਟ_ਤਰਜੀਹ( ਖਾਲੀ );
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ASSERT_IF_ਰੁਕਾਵਟ_ਤਰਜੀਹ_INVALID()    v_ਪੋਰਟ_Validate_ਰੁਕਾਵਟ_ਤਰਜੀਹ()
#ਜੇ_ਅੰਤ

/* portNOP() is not required by this port. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NOP()

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INLINE              __inline

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ਪੋਰਟ_FORCE_INLINE
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FORCE_INLINE    ਸਤਰਅੰਦਰ __attribute__( ( always_inline ) )
#ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

ਬਾਹਰੀ ਅਧਾਰ_Type_t xIsPrivileged( ਖਾਲੀ );
ਬਾਹਰੀ ਖਾਲੀ vResetPrivilege( ਖਾਲੀ );
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Switch_ਮੰਜ਼ਿਲ_User_ਬਹੁਲਕ( ਖਾਲੀ );

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IS_PRIVILEGED()          xIsPrivileged()

/**
 * @brief Raise an SVC request to raise privilege.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RAISE_PRIVILEGE()        __asm ਅਸਥਿਰ ( "svc %0 \n" ::"i" ( ਪੋਰਟ_SVC_RAISE_PRIVILEGE ) : "memory" );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESET_PRIVILEGE()        vResetPrivilege()

/**
 * @brief Make a task unprivileged.
 *
 * It must be called from privileged tasks only. Calling it from unprivileged
 * task will result in a memory protection fault.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SWITCH_ਮੰਜ਼ਿਲ_USER_ਬਹੁਲਕ()    v_ਪੋਰਟ_Switch_ਮੰਜ਼ਿਲ_User_ਬਹੁਲਕ()
/*-----------------------------------------------------------*/

ਬਾਹਰੀ ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Task_Privileged( ਖਾਲੀ );

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IS_TASK_PRIVILEGED()    x_ਪੋਰਟ_Is_Task_Privileged()
/*-----------------------------------------------------------*/

ਪੋਰਟ_FORCE_INLINE ਸਥਿਰ ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Inside_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    uint32_t ul_Current_ਰੁਕਾਵਟ;
    ਅਧਾਰ_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    __asm ਅਸਥਿਰ ( "mrs %0, ipsr" : "=r" ( ul_Current_ਰੁਕਾਵਟ )::"memory" );

    ਜੇ( ul_Current_ਰੁਕਾਵਟ == 0 )
    {
        xReturn = pdFALSE;
    }
    ਨਹੀਂਤਾਂ
    {
        xReturn = pdTRUE;
    }

    ਵਾਪਸ xReturn;
}

/*-----------------------------------------------------------*/

ਪੋਰਟ_FORCE_INLINE ਸਥਿਰ ਖਾਲੀ v_ਪੋਰਟ_Raise_BASEPRI( ਖਾਲੀ )
{
    uint32_t ulNewBASEPRI;

    __asm ਅਸਥਿਰ
    (
        "   mov %0, %1                                              \n" \
        "   msr basepri, %0                                         \n" \
        "   isb                                                     \n" \
        "   dsb                                                     \n" \
        : "=r" ( ulNewBASEPRI ) : "i" ( config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ ) : "memory"
    );
}

/*-----------------------------------------------------------*/

ਪੋਰਟ_FORCE_INLINE ਸਥਿਰ uint32_t ul_ਪੋਰਟ_Raise_BASEPRI( ਖਾਲੀ )
{
    uint32_t ulOriginalBASEPRI, ulNewBASEPRI;

    __asm ਅਸਥਿਰ
    (
        "   mrs %0, basepri                                         \n" \
        "   mov %1, %2                                              \n" \
        "   msr basepri, %1                                         \n" \
        "   isb                                                     \n" \
        "   dsb                                                     \n" \
        : "=r" ( ulOriginalBASEPRI ), "=r" ( ulNewBASEPRI ) : "i" ( config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ ) : "memory"
    );

    /* This return will not be reached but is necessary to prevent compiler
     * warnings. */
    ਵਾਪਸ ulOriginalBASEPRI;
}
/*-----------------------------------------------------------*/

ਪੋਰਟ_FORCE_INLINE ਸਥਿਰ ਖਾਲੀ v_ਪੋਰਟ_ਸੈੱਟ_BASEPRI( uint32_t ul_New_ਨਕਾਬ_ਮੁੱਲ )
{
    __asm ਅਸਥਿਰ
    (
        "   msr basepri, %0 " ::"r" ( ul_New_ਨਕਾਬ_ਮੁੱਲ ) : "memory"
    );
}
/*-----------------------------------------------------------*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER()    __asm ਅਸਥਿਰ ( "" ::: "memory" )

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY
    #warning "configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY is not defined. We recommend defining it to 1 in FreeRTOSConfig.h for better security. *www.FreeRTOS.org/FreeRTOS-V10.3.x.html"
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY    0
#ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    }
#ਜੇ_ਅੰਤ
/* *INDENT-ON* */

#ਜੇ_ਅੰਤ /* PORTMACRO_H */
