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

#اگر_غیر_تعریف_شدہ PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    خارجی "C" {
#اگر_ختم
/* *INDENT-ON* */

/* System Includes. */
#شامل <tc1782.h>
#شامل <machine/intrinsics.h>

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
#تعریف_کرو پورٹ_FLOAT         اعشاری
#تعریف_کرو پورٹ_DOUBLE        دوہرا
#تعریف_کرو پورٹ_LONG          طویل
#تعریف_کرو پورٹ_SHORT         مختصر
#تعریف_کرو پورٹ_ڈھیر_TYPE    uint32_t
#تعریف_کرو پورٹ_بنیاد_TYPE     طویل

قسمتعریف پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
قسمتعریف طویل             بنیاد_Type_t;
قسمتعریف غیرعلامتی طویل    UBaseType_t;

#اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    قسمتعریف uint16_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffff
#وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    قسمتعریف uint32_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
#ورنہ
    #غلطی config_TICK_TYPE_چوڑائی_اندر_بٹ سیٹ مقصد unsupported tick type چوڑائی.
#اگر_ختم
/*---------------------------------------------------------------------------*/

/* Architecture specifics. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH                         ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS                       ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_BYTE_ALIGNMENT                       4
#تعریف_کرو پورٹ_NOP()    __asm متلون ( " nop " )
#تعریف_کرو پورٹ_CRITICAL_NESTING_اندر_TCB              1
#تعریف_کرو پورٹ_RESTORE_پہلا_TASK_ترجیح_LEVEL    1


/*---------------------------------------------------------------------------*/

قسمتعریف ساخت MPU_SETTINGS
{
    uint32_t ul_Not_مستعمل;
} xMPU_SETTINGS;

/* Define away the instruction from the Restore Context Macro. */
#تعریف_کرو پورٹ_PRIVILEGE_ثنائی_ہندسہ    0x0UL

#تعریف_کرو پورٹ_CCPN_نقاب        ( 0x000000FFUL )

خارجی خالی vTaskEnterCritical( خالی );
خارجی خالی vTaskExitCritical( خالی );
#تعریف_کرو پورٹ_ENTER_CRITICAL()    vTaskEnterCritical()
#تعریف_کرو پورٹ_EXIT_CRITICAL()     vTaskExitCritical()
/*---------------------------------------------------------------------------*/

/* CSA Manipulation. */
#تعریف_کرو پورٹ_CSA_مقصد_پتہ( pCSA )        ( ( uint32_t * ) ( ( ( ( pCSA ) & 0x000F0000 ) << 12 ) | ( ( ( pCSA ) & 0x0000FFFF ) << 6 ) ) )
#تعریف_کرو پورٹ_پتہ_مقصد_CSA( p_پتہ )    ( ( uint32_t ) ( ( ( ( ( uint32_t ) ( p_پتہ ) ) & 0xF0000000 ) >> 12 ) | ( ( ( uint32_t ) ( p_پتہ ) & 0x003FFFC0 ) >> 6 ) ) )
/*---------------------------------------------------------------------------*/

#تعریف_کرو پورٹ_YIELD()                       _syscall( 0 )
/* Port Restore is implicit in the platform when the function is returned from the original PSW is automatically replaced. */
#تعریف_کرو پورٹ_SYSCALL_TASK_YIELD        0
#تعریف_کرو پورٹ_SYSCALL_RAISE_ترجیح    1
/*---------------------------------------------------------------------------*/

/* Critical section management. */

/* Set ICR.CCPN to configMAX_SYSCALL_INTERRUPT_PRIORITY. */
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                                                                      \
    {                                                                                                 \
        uint32_t ulICR;                                                                               \
        _disable();                                                                                   \
        ulICR = __MFCR( $ICR );                        /* Get current ICR value. */                   \
        ulICR &= ~پورٹ_CCPN_نقاب;                       /* Clear down mask bits. */                    \
        ulICR |= config_MAX_SYSCALL_مداخلت_ترجیح; /* Set mask bits to required priority mask. */ \
        _mtcr( $ICR, ulICR );                          /* Write back updated ICR. */                  \
        _isync();                                                                                     \
        _enable();                                                                                    \
    }

/* Clear ICR.CCPN to allow all interrupt priorities. */
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                                \
    {                                                          \
        uint32_t ulICR;                                        \
        _disable();                                            \
        ulICR = __MFCR( $ICR );  /* Get current ICR value. */  \
        ulICR &= ~پورٹ_CCPN_نقاب; /* Clear down mask bits. */   \
        _mtcr( $ICR, ulICR );    /* Write back updated ICR. */ \
        _isync();                                              \
        _enable();                                             \
    }

/* Set ICR.CCPN to uxSavedMaskValue. */
#تعریف_کرو پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( ux_Saved_نقاب_قدر )                          \
    {                                                                                  \
        uint32_t ulICR;                                                                \
        _disable();                                                                    \
        ulICR = __MFCR( $ICR );    /* Get current ICR value. */                        \
        ulICR &= ~پورٹ_CCPN_نقاب;   /* Clear down mask bits. */                         \
        ulICR |= ux_Saved_نقاب_قدر; /* Set mask bits to previously saved mask value. */ \
        _mtcr( $ICR, ulICR );      /* Write back updated ICR. */                       \
        _isync();                                                                      \
        _enable();                                                                     \
    }


/* Set ICR.CCPN to configMAX_SYSCALL_INTERRUPT_PRIORITY */
خارجی uint32_t ux_پورٹ_سیٹ_مداخلت_نقاب_From_ISR( خالی );
#تعریف_کرو پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR()                 ux_پورٹ_سیٹ_مداخلت_نقاب_From_ISR()

/* Pend a priority 1 interrupt, which will take care of the context switch. */
#تعریف_کرو پورٹ_YIELD_FROM_ISR( x_Higher_ترجیح_Task_Woken )    کرو { اگر( x_Higher_ترجیح_Task_Woken != pdFALSE ) { CPU_SRC0.بٹ_2.SETR = 1; _isync(); } } جب( 0 )

/*---------------------------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )
/*---------------------------------------------------------------------------*/

/*
 * Port specific clean up macro required to free the CSAs that were consumed by
 * a task that has since been deleted.
 */
خالی v_پورٹ_Reclaim_CSA( uint32_t * pxTCB );
#تعریف_کرو پورٹ_CLEAN_اوپر_TCB( pxTCB )    v_پورٹ_Reclaim_CSA( ( uint32_t * ) ( pxTCB ) )

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    }
#اگر_ختم
/* *INDENT-ON* */

#اگر_ختم /* PORTMACRO_H */
