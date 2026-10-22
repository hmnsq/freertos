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

#اگر_تعریف_نشده PORTMACRO_H
#تعریف_کن PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    خارجي "C" {
#پایان_اگر
/* *INDENT-ON* */

/* System Includes. */
#ضمن <tc1782.h>
#ضمن <machine/intrinsics.h>

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
#تعریف_کن پورت_CHAR          حرف
#تعریف_کن پورت_FLOAT         عائم
#تعریف_کن پورت_DOUBLE        مزدوج
#تعریف_کن پورت_LONG          دراز
#تعریف_کن پورت_SHORT         کوتاه
#تعریف_کن پورت_پشته_TYPE    uint32_t
#تعریف_کن پورت_پایه_TYPE     دراز

تعريفنوع پورت_پشته_TYPE   پشته_Type_t;
تعريفنوع دراز             پایه_Type_t;
تعريفنوع بیعلامت دراز    UBaseType_t;

#إذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_32_بیتها )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کن پورت_TICK_TYPE_IS_ATOMIC    1
#وإلا
    #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
#پایان_اگر
/*---------------------------------------------------------------------------*/

/* Architecture specifics. */
#تعریف_کن پورت_پشته_GROWTH                         ( -1 )
#تعریف_کن پورت_TICK_PERIOD_MS                       ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
#تعریف_کن پورت_BYTE_ALIGNMENT                       4
#تعریف_کن پورت_NOP()    __asm متطاير ( " nop " )
#تعریف_کن پورت_CRITICAL_NESTING_درون_TCB              1
#تعریف_کن پورت_RESTORE_اولی_TASK_اولویت_LEVEL    1


/*---------------------------------------------------------------------------*/

تعريفنوع بنية MPU_SETTINGS
{
    uint32_t ul_Not_استفاده_شده;
} xMPU_SETTINGS;

/* Define away the instruction from the Restore Context Macro. */
#تعریف_کن پورت_PRIVILEGE_بیت    0x0UL

#تعریف_کن پورت_CCPN_ماسک        ( 0x000000FFUL )

خارجي فراغ vTaskEnterCritical( فراغ );
خارجي فراغ vTaskExitCritical( فراغ );
#تعریف_کن پورت_ENTER_CRITICAL()    vTaskEnterCritical()
#تعریف_کن پورت_EXIT_CRITICAL()     vTaskExitCritical()
/*---------------------------------------------------------------------------*/

/* CSA Manipulation. */
#تعریف_کن پورت_CSA_مقصد_آدرس( pCSA )        ( ( uint32_t * ) ( ( ( ( pCSA ) & 0x000F0000 ) << 12 ) | ( ( ( pCSA ) & 0x0000FFFF ) << 6 ) ) )
#تعریف_کن پورت_آدرس_مقصد_CSA( p_آدرس )    ( ( uint32_t ) ( ( ( ( ( uint32_t ) ( p_آدرس ) ) & 0xF0000000 ) >> 12 ) | ( ( ( uint32_t ) ( p_آدرس ) & 0x003FFFC0 ) >> 6 ) ) )
/*---------------------------------------------------------------------------*/

#تعریف_کن پورت_YIELD()                       _syscall( 0 )
/* Port Restore is implicit in the platform when the function is returned from the original PSW is automatically replaced. */
#تعریف_کن پورت_SYSCALL_TASK_YIELD        0
#تعریف_کن پورت_SYSCALL_RAISE_اولویت    1
/*---------------------------------------------------------------------------*/

/* Critical section management. */

/* Set ICR.CCPN to configMAX_SYSCALL_INTERRUPT_PRIORITY. */
#تعریف_کن پورت_DISABLE_INTERRUPTS()                                                                      \
    {                                                                                                 \
        uint32_t ulICR;                                                                               \
        _disable();                                                                                   \
        ulICR = __MFCR( $ICR );                        /* Get current ICR value. */                   \
        ulICR &= ~پورت_CCPN_ماسک;                       /* Clear down mask bits. */                    \
        ulICR |= config_MAX_SYSCALL_وقفه_اولویت; /* Set mask bits to required priority mask. */ \
        _mtcr( $ICR, ulICR );                          /* Write back updated ICR. */                  \
        _isync();                                                                                     \
        _enable();                                                                                    \
    }

/* Clear ICR.CCPN to allow all interrupt priorities. */
#تعریف_کن پورت_ENABLE_INTERRUPTS()                                \
    {                                                          \
        uint32_t ulICR;                                        \
        _disable();                                            \
        ulICR = __MFCR( $ICR );  /* Get current ICR value. */  \
        ulICR &= ~پورت_CCPN_ماسک; /* Clear down mask bits. */   \
        _mtcr( $ICR, ulICR );    /* Write back updated ICR. */ \
        _isync();                                              \
        _enable();                                             \
    }

/* Set ICR.CCPN to uxSavedMaskValue. */
#تعریف_کن پورت_CLEAR_وقفه_ماسک_FROM_ISR( ux_Saved_ماسک_مقدار )                          \
    {                                                                                  \
        uint32_t ulICR;                                                                \
        _disable();                                                                    \
        ulICR = __MFCR( $ICR );    /* Get current ICR value. */                        \
        ulICR &= ~پورت_CCPN_ماسک;   /* Clear down mask bits. */                         \
        ulICR |= ux_Saved_ماسک_مقدار; /* Set mask bits to previously saved mask value. */ \
        _mtcr( $ICR, ulICR );      /* Write back updated ICR. */                       \
        _isync();                                                                      \
        _enable();                                                                     \
    }


/* Set ICR.CCPN to configMAX_SYSCALL_INTERRUPT_PRIORITY */
خارجي uint32_t ux_پورت_مجموعه_وقفه_ماسک_From_ISR( فراغ );
#تعریف_کن پورت_مجموعه_وقفه_ماسک_FROM_ISR()                 ux_پورت_مجموعه_وقفه_ماسک_From_ISR()

/* Pend a priority 1 interrupt, which will take care of the context switch. */
#تعریف_کن پورت_YIELD_FROM_ISR( x_Higher_اولویت_Task_Woken )    افعل { إذا( x_Higher_اولویت_Task_Woken != pdFALSE ) { CPU_SRC0.بیتها_2.SETR = 1; _isync(); } } طالما( 0 )

/*---------------------------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*---------------------------------------------------------------------------*/

/*
 * Port specific clean up macro required to free the CSAs that were consumed by
 * a task that has since been deleted.
 */
فراغ v_پورت_Reclaim_CSA( uint32_t * pxTCB );
#تعریف_کن پورت_CLEAN_به_بالا_TCB( pxTCB )    v_پورت_Reclaim_CSA( ( uint32_t * ) ( pxTCB ) )

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */
