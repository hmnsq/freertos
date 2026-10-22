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


#جے_بنا_تعریف PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    خارجي "C" {
#جے_انت
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
#تعریف_کرو پورٹ_CHAR          حرف
#تعریف_کرو پورٹ_FLOAT         عائم
#تعریف_کرو پورٹ_DOUBLE        مزدوج
#تعریف_کرو پورٹ_LONG          لما
#تعریف_کرو پورٹ_SHORT         چھوٹا
#تعریف_کرو پورٹ_ڈھیر_TYPE    uint32_t
#تعریف_کرو پورٹ_ادھار_TYPE     لما

تعريفنوع پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
تعريفنوع لما             ادھار_Type_t;
تعريفنوع بنانشانی لما    UBaseType_t;

#إذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
#وإلا
    #غلطی config_TICK_TYPE_چوڑائی_وچ_بٹ سیٹ منزل unsupported tick type چوڑائی.
#جے_انت
/*-----------------------------------------------------------*/

/* MPU specific constants. */
#تعریف_کرو پورٹ_USING_MPU_WRAPPERS                                   1
#تعریف_کرو پورٹ_PRIVILEGE_ثنائی_ہندسہ                                        ( 0x80000000UL )

#تعریف_کرو پورٹ_MPU_REGION_READ_WRITE                                ( 0x03UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_PRIVILEGED_READ_ONLY                      ( 0x05UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_READ_ONLY                                 ( 0x06UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_PRIVILEGED_READ_WRITE                     ( 0x01UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY    ( 0x02UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_CACHEABLE_BUFFERABLE                      ( 0x07UL << 16UL )
#تعریف_کرو پورٹ_MPU_REGION_EXECUTE_NEVER                             ( 0x01UL << 28UL )

#تعریف_کرو پورٹ_ڈھیر_REGION                                         ( 3UL )
#تعریف_کرو پورٹ_GENERAL_PERIPHERALS_REGION                           ( 4UL )
#تعریف_کرو پورٹ_UNPRIVILEGED_FLASH_REGION                            ( 5UL )
#تعریف_کرو پورٹ_PRIVILEGED_FLASH_REGION                              ( 6UL )
#تعریف_کرو پورٹ_PRIVILEGED_RAM_REGION                                ( 7UL )
#تعریف_کرو پورٹ_پہلا_CONFIGURABLE_REGION                            ( 0UL )
#تعریف_کرو پورٹ_آخری_CONFIGURABLE_REGION                             ( 2UL )
#تعریف_کرو پورٹ_عدد_CONFIGURABLE_REGIONS                             ( ( پورٹ_آخری_CONFIGURABLE_REGION - پورٹ_پہلا_CONFIGURABLE_REGION ) + 1 )
#تعریف_کرو پورٹ_کل_عدد_REGIONS_وچ_TCB                             ( پورٹ_عدد_CONFIGURABLE_REGIONS + 1 )     /* Plus one to make space for the stack region. */

تعريفنوع بنية MPU_REGION_REGISTERS
{
    uint32_t ul_Region_ادھار_پتہ;
    uint32_t ulRegionAttribute;
} xMPU_REGION_REGISTERS;

تعريفنوع بنية MPU_REGION_SETTINGS
{
    uint32_t ul_Region_شروع_پتہ;
    uint32_t ul_Region_سرا_پتہ;
    uint32_t ulRegionPermissions;
} xMPU_REGION_SETTINGS;

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #جے_بنا_تعریف config_SYSTEM_CALL_ڈھیر_ناپ
        #غلطی config_SYSTEM_CALL_ڈھیر_ناپ must be defined منزل the desired ناپ دا the system call ڈھیر وچ الفاظ لكل using MPU wrappers v2.
    #جے_انت

    تعريفنوع بنية SYSTEM_CALL_ڈھیر_INFO
    {
        uint32_t ul_System_Call_ڈھیر_بفر[ config_SYSTEM_CALL_ڈھیر_ناپ ];
        uint32_t * pul_System_Call_ڈھیر;
        uint32_t * pul_Task_ڈھیر;
        uint32_t ul_Link_رجسٹر_At_System_Call_اندراج;
    } x_SYSTEM_CALL_ڈھیر_INFO;

#جے_انت /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*
 * +------------------------------+-------------------------------+-----+
 * |  CONTROL, r4-r11, EXC_RETURN | PSP, r0-r3, r12, LR, PC, xPSR |     |
 * +------------------------------+-------------------------------+-----+
 *
 * <-----------------------------><-------------------------------><---->
 *                10                             9                   1
 */
#تعریف_کرو MAX_CONTEXT_ناپ                    ( 20 )

/* Size of an Access Control List (ACL) entry in bits. */
#تعریف_کرو پورٹ_ACL_اندراج_ناپ_بٹ             ( 32U )

/* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
#تعریف_کرو پورٹ_ڈھیر_چوکھٹا_HAS_PADDING_FLAG    ( 1UL << 0UL )
#تعریف_کرو پورٹ_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

تعريفنوع بنية MPU_SETTINGS
{
    xMPU_REGION_REGISTERS xRegion[ پورٹ_کل_عدد_REGIONS_وچ_TCB ];
    xMPU_REGION_SETTINGS xRegionSettings[ پورٹ_کل_عدد_REGIONS_وچ_TCB ];
    uint32_t ulContext[ MAX_CONTEXT_ناپ ];
    uint32_t ulTaskFlags;

    #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
        x_SYSTEM_CALL_ڈھیر_INFO x_System_Call_ڈھیر_Info;
        #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
            uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_ناپ / پورٹ_ACL_اندراج_ناپ_بٹ ) + 1 ];
        #جے_انت
    #جے_انت
} xMPU_SETTINGS;

/* Architecture specifics. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH      ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_BYTE_ALIGNMENT    8
#تعریف_کرو پورٹ_DONT_DISCARD      __attribute__( ( ورتیا ) )
/*-----------------------------------------------------------*/

/* SVC numbers for various services. */
#تعریف_کرو پورٹ_SVC_شروع_SCHEDULER        100
#تعریف_کرو پورٹ_SVC_YIELD                  101
#تعریف_کرو پورٹ_SVC_RAISE_PRIVILEGE        102
#تعریف_کرو پورٹ_SVC_SYSTEM_CALL_EXIT       103

/* Scheduler utilities. */

#تعریف_کرو پورٹ_YIELD()    __asm متطاير ( "   SVC %0  \n" ::"i" ( پورٹ_SVC_YIELD ) : "memory" )
#تعریف_کرو پورٹ_YIELD_WITHIN_API()                          \
    {                                                   \
        /* Set a PendSV to request a context switch. */ \
        پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ; \
                                                        \
        /* Barriers are normally not required but do ensure the code is completely \
         * within the specified behaviour for the architecture. */ \
        __asm متطاير ( "dsb" ::: "memory" );                     \
        __asm متطاير ( "isb" );                                  \
    }

#تعریف_کرو پورٹ_NVIC_INT_CTRL_REG     ( *( ( متطاير uint32_t * ) 0xe000ed04 ) )
#تعریف_کرو پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ    ( 1UL << 28UL )
#تعریف_کرو پورٹ_سرا_SWITCHING_ISR( xSwitchRequired )            \
    افعل                                                      \
    {                                                       \
        إذا( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_منزل_SCHEDULER();                   \
            پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ; \
        }                                                   \
        وإلا                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } طالما( 0 )
#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )    پورٹ_سرا_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
خارجي فراغ v_پورٹ_Enter_Critical( فراغ );
خارجي فراغ v_پورٹ_Exit_Critical( فراغ );
#تعریف_کرو پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR()         ul_پورٹ_Raise_BASEPRI()
#تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( x )    v_پورٹ_سیٹ_BASEPRI( x )
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                  v_پورٹ_Raise_BASEPRI()
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                   v_پورٹ_سیٹ_BASEPRI( 0 )
#تعریف_کرو پورٹ_ENTER_CRITICAL()                      v_پورٹ_Enter_Critical()
#تعریف_کرو پورٹ_EXIT_CRITICAL()                       v_پورٹ_Exit_Critical()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#جے_بنا_تعریف config_USE_پورٹ_OPTIMISED_TASK_SELECTION
    #تعریف_کرو config_USE_پورٹ_OPTIMISED_TASK_SELECTION    1
#جے_انت

#إذا config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1

/* Generic helper function. */
    __attribute__( ( always_inline ) ) ساكن مضمن uint8_t uc_پورٹ_گنتی_Leading_Zeros( uint32_t ulBitmap )
    {
        uint8_t ucReturn;

        __asm متطاير ( "clz %0, %1" : "=r" ( ucReturn ) : "r" ( ulBitmap ) : "memory" );

        أرجع ucReturn;
    }

/* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #غلطی config_USE_پورٹ_OPTIMISED_TASK_SELECTION can only be سیٹ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires ہور than 10 منزل 15 difference priorities as tasks that share a ترجیح will time ٹکڑا.
    #جے_انت

/* Store/clear the ready priorities in a bit map. */
    #تعریف_کرو پورٹ_ریکارڈ_READY_ترجیح( ux_ترجیح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجیح ) )
    #تعریف_کرو پورٹ_RESET_READY_ترجیح( ux_ترجیح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجیح ) )

/*-----------------------------------------------------------*/

    #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities )    ux_چوٹی_ترجیح = ( 31UL - ( uint32_t ) uc_پورٹ_گنتی_Leading_Zeros( ( uxReadyPriorities ) ) )

#جے_انت /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/*-----------------------------------------------------------*/

#إذا ( configASSERT_DEFINED == 1 )
    فراغ v_پورٹ_Validate_رکاوٹ_ترجیح( فراغ );
    #تعریف_کرو پورٹ_ASSERT_IF_رکاوٹ_ترجیح_INVALID()    v_پورٹ_Validate_رکاوٹ_ترجیح()
#جے_انت

/* portNOP() is not required by this port. */
#تعریف_کرو پورٹ_NOP()

#تعریف_کرو پورٹ_INLINE              __inline

#جے_بنا_تعریف پورٹ_FORCE_INLINE
    #تعریف_کرو پورٹ_FORCE_INLINE    مضمن __attribute__( ( always_inline ) )
#جے_انت
/*-----------------------------------------------------------*/

خارجي ادھار_Type_t xIsPrivileged( فراغ );
خارجي فراغ vResetPrivilege( فراغ );
خارجي فراغ v_پورٹ_Switch_منزل_User_منوال( فراغ );

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
#تعریف_کرو پورٹ_IS_PRIVILEGED()          xIsPrivileged()

/**
 * @brief Raise an SVC request to raise privilege.
 */
#تعریف_کرو پورٹ_RAISE_PRIVILEGE()        __asm متطاير ( "svc %0 \n" ::"i" ( پورٹ_SVC_RAISE_PRIVILEGE ) : "memory" );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 */
#تعریف_کرو پورٹ_RESET_PRIVILEGE()        vResetPrivilege()

/**
 * @brief Make a task unprivileged.
 *
 * It must be called from privileged tasks only. Calling it from unprivileged
 * task will result in a memory protection fault.
 */
#تعریف_کرو پورٹ_SWITCH_منزل_USER_منوال()    v_پورٹ_Switch_منزل_User_منوال()
/*-----------------------------------------------------------*/

خارجي ادھار_Type_t x_پورٹ_Is_Task_Privileged( فراغ );

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
#تعریف_کرو پورٹ_IS_TASK_PRIVILEGED()    x_پورٹ_Is_Task_Privileged()
/*-----------------------------------------------------------*/

پورٹ_FORCE_INLINE ساكن ادھار_Type_t x_پورٹ_Is_Inside_رکاوٹ( فراغ )
{
    uint32_t ul_Current_رکاوٹ;
    ادھار_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    __asm متطاير ( "mrs %0, ipsr" : "=r" ( ul_Current_رکاوٹ )::"memory" );

    إذا( ul_Current_رکاوٹ == 0 )
    {
        xReturn = pdFALSE;
    }
    وإلا
    {
        xReturn = pdTRUE;
    }

    أرجع xReturn;
}

/*-----------------------------------------------------------*/

پورٹ_FORCE_INLINE ساكن فراغ v_پورٹ_Raise_BASEPRI( فراغ )
{
    uint32_t ulNewBASEPRI;

    __asm متطاير
    (
        "   mov %0, %1                                              \n" \
        "   msr basepri, %0                                         \n" \
        "   isb                                                     \n" \
        "   dsb                                                     \n" \
        : "=r" ( ulNewBASEPRI ) : "i" ( config_MAX_SYSCALL_رکاوٹ_ترجیح ) : "memory"
    );
}

/*-----------------------------------------------------------*/

پورٹ_FORCE_INLINE ساكن uint32_t ul_پورٹ_Raise_BASEPRI( فراغ )
{
    uint32_t ulOriginalBASEPRI, ulNewBASEPRI;

    __asm متطاير
    (
        "   mrs %0, basepri                                         \n" \
        "   mov %1, %2                                              \n" \
        "   msr basepri, %1                                         \n" \
        "   isb                                                     \n" \
        "   dsb                                                     \n" \
        : "=r" ( ulOriginalBASEPRI ), "=r" ( ulNewBASEPRI ) : "i" ( config_MAX_SYSCALL_رکاوٹ_ترجیح ) : "memory"
    );

    /* This return will not be reached but is necessary to prevent compiler
     * warnings. */
    أرجع ulOriginalBASEPRI;
}
/*-----------------------------------------------------------*/

پورٹ_FORCE_INLINE ساكن فراغ v_پورٹ_سیٹ_BASEPRI( uint32_t ul_New_نقاب_قدر )
{
    __asm متطاير
    (
        "   msr basepri, %0 " ::"r" ( ul_New_نقاب_قدر ) : "memory"
    );
}
/*-----------------------------------------------------------*/

#تعریف_کرو پورٹ_حافظہ_BARRIER()    __asm متطاير ( "" ::: "memory" )

#جے_بنا_تعریف configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY
    #warning "configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY is not defined. We recommend defining it to 1 in FreeRTOSConfig.h for better security. *www.FreeRTOS.org/FreeRTOS-V10.3.x.html"
    #تعریف_کرو configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY    0
#جے_انت
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    }
#جے_انت
/* *INDENT-ON* */

#جے_انت /* PORTMACRO_H */
