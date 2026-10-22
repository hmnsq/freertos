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

#که_نه_تعریف_شوی PORTMACRO_H
#تعریف_کړه PORTMACRO_H

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    خارجي "C" {
#د_که_پای
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
#تعریف_کړه پورټ_CHAR          حرف
#تعریف_کړه پورټ_FLOAT         عائم
#تعریف_کړه پورټ_DOUBLE        مزدوج
#تعریف_کړه پورټ_LONG          اوږد
#تعریف_کړه پورټ_SHORT         لنډ
#تعریف_کړه پورټ_ډېری_TYPE    uint32_t
#تعریف_کړه پورټ_بنسټ_TYPE     اوږد

تعريفنوع پورټ_ډېری_TYPE   ډېری_Type_t;
تعريفنوع اوږد             بنسټ_Type_t;
تعريفنوع بینښه اوږد    UBaseType_t;

#إذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کړه پورټ_TICK_TYPE_IS_ATOMIC    1
#وإلا
    #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
#د_که_پای
/*---------------------------------------------------------------------------*/

/* Architecture specifics. */
#تعریف_کړه پورټ_ډېری_GROWTH                         ( -1 )
#تعریف_کړه پورټ_TICK_PERIOD_MS                       ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کړه پورټ_BYTE_ALIGNMENT                       4
#تعریف_کړه پورټ_NOP()    __asm متطاير ( " nop " )
#تعریف_کړه پورټ_CRITICAL_NESTING_دننه_TCB              1
#تعریف_کړه پورټ_RESTORE_لومړی_TASK_لومړیتوب_LEVEL    1


/*---------------------------------------------------------------------------*/

تعريفنوع بنية MPU_SETTINGS
{
    uint32_t ul_Not_کارول_شوی;
} xMPU_SETTINGS;

/* Define away the instruction from the Restore Context Macro. */
#تعریف_کړه پورټ_PRIVILEGE_بټ    0x0UL

#تعریف_کړه پورټ_CCPN_ماسک        ( 0x000000FFUL )

خارجي فراغ vTaskEnterCritical( فراغ );
خارجي فراغ vTaskExitCritical( فراغ );
#تعریف_کړه پورټ_ENTER_CRITICAL()    vTaskEnterCritical()
#تعریف_کړه پورټ_EXIT_CRITICAL()     vTaskExitCritical()
/*---------------------------------------------------------------------------*/

/* CSA Manipulation. */
#تعریف_کړه پورټ_CSA_منزل_پته( pCSA )        ( ( uint32_t * ) ( ( ( ( pCSA ) & 0x000F0000 ) << 12 ) | ( ( ( pCSA ) & 0x0000FFFF ) << 6 ) ) )
#تعریف_کړه پورټ_پته_منزل_CSA( p_پته )    ( ( uint32_t ) ( ( ( ( ( uint32_t ) ( p_پته ) ) & 0xF0000000 ) >> 12 ) | ( ( ( uint32_t ) ( p_پته ) & 0x003FFFC0 ) >> 6 ) ) )
/*---------------------------------------------------------------------------*/

#تعریف_کړه پورټ_YIELD()                       _syscall( 0 )
/* Port Restore is implicit in the platform when the function is returned from the original PSW is automatically replaced. */
#تعریف_کړه پورټ_SYSCALL_TASK_YIELD        0
#تعریف_کړه پورټ_SYSCALL_RAISE_لومړیتوب    1
/*---------------------------------------------------------------------------*/

/* Critical section management. */

/* Set ICR.CCPN to configMAX_SYSCALL_INTERRUPT_PRIORITY. */
#تعریف_کړه پورټ_DISABLE_INTERRUPTS()                                                                      \
    {                                                                                                 \
        uint32_t ulICR;                                                                               \
        _disable();                                                                                   \
        ulICR = __MFCR( $ICR );                        /* Get current ICR value. */                   \
        ulICR &= ~پورټ_CCPN_ماسک;                       /* Clear down mask bits. */                    \
        ulICR |= config_MAX_SYSCALL_مداخله_لومړیتوب; /* Set mask bits to required priority mask. */ \
        _mtcr( $ICR, ulICR );                          /* Write back updated ICR. */                  \
        _isync();                                                                                     \
        _enable();                                                                                    \
    }

/* Clear ICR.CCPN to allow all interrupt priorities. */
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()                                \
    {                                                          \
        uint32_t ulICR;                                        \
        _disable();                                            \
        ulICR = __MFCR( $ICR );  /* Get current ICR value. */  \
        ulICR &= ~پورټ_CCPN_ماسک; /* Clear down mask bits. */   \
        _mtcr( $ICR, ulICR );    /* Write back updated ICR. */ \
        _isync();                                              \
        _enable();                                             \
    }

/* Set ICR.CCPN to uxSavedMaskValue. */
#تعریف_کړه پورټ_CLEAR_مداخله_ماسک_FROM_ISR( ux_Saved_ماسک_ارزښت )                          \
    {                                                                                  \
        uint32_t ulICR;                                                                \
        _disable();                                                                    \
        ulICR = __MFCR( $ICR );    /* Get current ICR value. */                        \
        ulICR &= ~پورټ_CCPN_ماسک;   /* Clear down mask bits. */                         \
        ulICR |= ux_Saved_ماسک_ارزښت; /* Set mask bits to previously saved mask value. */ \
        _mtcr( $ICR, ulICR );      /* Write back updated ICR. */                       \
        _isync();                                                                      \
        _enable();                                                                     \
    }


/* Set ICR.CCPN to configMAX_SYSCALL_INTERRUPT_PRIORITY */
خارجي uint32_t ux_پورټ_سېټ_مداخله_ماسک_From_ISR( فراغ );
#تعریف_کړه پورټ_سېټ_مداخله_ماسک_FROM_ISR()                 ux_پورټ_سېټ_مداخله_ماسک_From_ISR()

/* Pend a priority 1 interrupt, which will take care of the context switch. */
#تعریف_کړه پورټ_YIELD_FROM_ISR( x_Higher_لومړیتوب_Task_Woken )    افعل { إذا( x_Higher_لومړیتوب_Task_Woken != pdFALSE ) { CPU_SRC0.بټونه_2.SETR = 1; _isync(); } } طالما( 0 )

/*---------------------------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*---------------------------------------------------------------------------*/

/*
 * Port specific clean up macro required to free the CSAs that were consumed by
 * a task that has since been deleted.
 */
فراغ v_پورټ_Reclaim_CSA( uint32_t * pxTCB );
#تعریف_کړه پورټ_CLEAN_پورته_TCB( pxTCB )    v_پورټ_Reclaim_CSA( ( uint32_t * ) ( pxTCB ) )

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
