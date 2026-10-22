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

/* System Includes. */
#अन्तर्भाव <tc1782.h>
#अन्तर्भाव <machine/intrinsics.h>

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
    #दोषः config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः समुच्चयः गन्तव्यम् unsupported tick type विस्तारः.
#यदि_अन्तः
/*---------------------------------------------------------------------------*/

/* Architecture specifics. */
#परिभाषय पत्तनम्_राशिः_GROWTH                         ( -1 )
#परिभाषय पत्तनम्_TICK_PERIOD_MS                       ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
#परिभाषय पत्तनम्_BYTE_ALIGNMENT                       4
#परिभाषय पत्तनम्_NOP()    __asm चञ्चल ( " nop " )
#परिभाषय पत्तनम्_CRITICAL_NESTING_अन्तर्_TCB              1
#परिभाषय पत्तनम्_RESTORE_FIRST_TASK_प्राथमिकता_LEVEL    1


/*---------------------------------------------------------------------------*/

प्रकारनिर्देश संरचना MPU_SETTINGS
{
    uint32_t ul_Not_प्रयुक्तम्;
} xMPU_SETTINGS;

/* Define away the instruction from the Restore Context Macro. */
#परिभाषय पत्तनम्_PRIVILEGE_BIT    0x0UL

#परिभाषय पत्तनम्_CCPN_आवरणम्        ( 0x000000FFUL )

बाह्य शून्य vTaskEnterCritical( शून्य );
बाह्य शून्य vTaskExitCritical( शून्य );
#परिभाषय पत्तनम्_ENTER_CRITICAL()    vTaskEnterCritical()
#परिभाषय पत्तनम्_EXIT_CRITICAL()     vTaskExitCritical()
/*---------------------------------------------------------------------------*/

/* CSA Manipulation. */
#परिभाषय पत्तनम्_CSA_गन्तव्यम्_स्थानाङ्कः( pCSA )        ( ( uint32_t * ) ( ( ( ( pCSA ) & 0x000F0000 ) << 12 ) | ( ( ( pCSA ) & 0x0000FFFF ) << 6 ) ) )
#परिभाषय पत्तनम्_स्थानाङ्कः_गन्तव्यम्_CSA( p_स्थानाङ्कः )    ( ( uint32_t ) ( ( ( ( ( uint32_t ) ( p_स्थानाङ्कः ) ) & 0xF0000000 ) >> 12 ) | ( ( ( uint32_t ) ( p_स्थानाङ्कः ) & 0x003FFFC0 ) >> 6 ) ) )
/*---------------------------------------------------------------------------*/

#परिभाषय पत्तनम्_YIELD()                       _syscall( 0 )
/* Port Restore is implicit in the platform when the function is returned from the original PSW is automatically replaced. */
#परिभाषय पत्तनम्_SYSCALL_TASK_YIELD        0
#परिभाषय पत्तनम्_SYSCALL_RAISE_प्राथमिकता    1
/*---------------------------------------------------------------------------*/

/* Critical section management. */

/* Set ICR.CCPN to configMAX_SYSCALL_INTERRUPT_PRIORITY. */
#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()                                                                      \
    {                                                                                                 \
        uint32_t ulICR;                                                                               \
        _disable();                                                                                   \
        ulICR = __MFCR( $ICR );                        /* Get current ICR value. */                   \
        ulICR &= ~पत्तनम्_CCPN_आवरणम्;                       /* Clear down mask bits. */                    \
        ulICR |= config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता; /* Set mask bits to required priority mask. */ \
        _mtcr( $ICR, ulICR );                          /* Write back updated ICR. */                  \
        _isync();                                                                                     \
        _enable();                                                                                    \
    }

/* Clear ICR.CCPN to allow all interrupt priorities. */
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()                                \
    {                                                          \
        uint32_t ulICR;                                        \
        _disable();                                            \
        ulICR = __MFCR( $ICR );  /* Get current ICR value. */  \
        ulICR &= ~पत्तनम्_CCPN_आवरणम्; /* Clear down mask bits. */   \
        _mtcr( $ICR, ulICR );    /* Write back updated ICR. */ \
        _isync();                                              \
        _enable();                                             \
    }

/* Set ICR.CCPN to uxSavedMaskValue. */
#परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( ux_Saved_आवरणम्_मानम् )                          \
    {                                                                                  \
        uint32_t ulICR;                                                                \
        _disable();                                                                    \
        ulICR = __MFCR( $ICR );    /* Get current ICR value. */                        \
        ulICR &= ~पत्तनम्_CCPN_आवरणम्;   /* Clear down mask bits. */                         \
        ulICR |= ux_Saved_आवरणम्_मानम्; /* Set mask bits to previously saved mask value. */ \
        _mtcr( $ICR, ulICR );      /* Write back updated ICR. */                       \
        _isync();                                                                      \
        _enable();                                                                     \
    }


/* Set ICR.CCPN to configMAX_SYSCALL_INTERRUPT_PRIORITY */
बाह्य uint32_t ux_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_From_ISR( शून्य );
#परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR()                 ux_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_From_ISR()

/* Pend a priority 1 interrupt, which will take care of the context switch. */
#परिभाषय पत्तनम्_YIELD_FROM_ISR( x_Higher_प्राथमिकता_Task_Woken )    कुरु { यदि( x_Higher_प्राथमिकता_Task_Woken != pdFALSE ) { CPU_SRC0.द्वयङ्काः_2.SETR = 1; _isync(); } } यावत्( 0 )

/*---------------------------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )
/*---------------------------------------------------------------------------*/

/*
 * Port specific clean up macro required to free the CSAs that were consumed by
 * a task that has since been deleted.
 */
शून्य v_पत्तनम्_Reclaim_CSA( uint32_t * pxTCB );
#परिभाषय पत्तनम्_CLEAN_ऊर्ध्वम्_TCB( pxTCB )    v_पत्तनम्_Reclaim_CSA( ( uint32_t * ) ( pxTCB ) )

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
