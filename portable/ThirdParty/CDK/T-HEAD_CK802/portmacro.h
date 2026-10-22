/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
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
 */

#جيڪڏهن_وصف_نه_ٿيل PORTMACRO_H
#وصف_ڪريو PORTMACRO_H

#ضمن <stdlib.h>
#ضمن <stdint.h>
#ضمن <csi_core.h>

خارجي فراغ v_پورٽ_Yield( فراغ );

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    class v_پورٽ_Yield;
    خارجي "C" {
#جيڪڏهن_پورو
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
#وصف_ڪريو پورٽ_CHAR          حرف
#وصف_ڪريو پورٽ_FLOAT         عائم
#وصف_ڪريو پورٽ_DOUBLE        مزدوج
#وصف_ڪريو پورٽ_LONG          ڊگهو
#وصف_ڪريو پورٽ_SHORT         ننڍو
#وصف_ڪريو پورٽ_ڍير_TYPE    uint32_t
#وصف_ڪريو پورٽ_بنياد_TYPE     ڊگهو

تعريفنوع پورٽ_ڍير_TYPE   ڍير_Type_t;
تعريفنوع ڊگهو             بنياد_Type_t;
تعريفنوع بنانشان ڊگهو    UBaseType_t;
تعريفنوع فراغ (* portvectorfunc)( فراغ );

#إذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_16_بٽ )
    تعريفنوع uint16_t     TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_32_بٽ )
    تعريفنوع uint32_t     TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #غلطي config_TICK_TYPE_ويڪر_اندريون_بٽ سيٽ منزل unsupported tick type ويڪر.
#جيڪڏهن_پورو


/* Hardware specifics. */
#وصف_ڪريو پورٽ_BYTE_ALIGNMENT    8
#وصف_ڪريو پورٽ_ڍير_GROWTH      -1
#وصف_ڪريو پورٽ_MS_PERIOD_TICK    10
#وصف_ڪريو پورٽ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )


ساكن مضمن فراغ v_پورٽ_Enable_مداخلت( فراغ )
{
    __enable_irq();
}

ساكن مضمن فراغ v_پورٽ_Disable_مداخلت( فراغ )
{
    __disable_irq();
}

ساكن مضمن پورٽ_LONG GetCurrentPSR( فراغ )
{
    أرجع __get_PSR();
}

ساكن مضمن پورٽ_LONG SaveLocalPSR( فراغ )
{
    پورٽ_LONG flags = __get_PSR();

    __disable_irq();
    أرجع flags;
}

ساكن مضمن فراغ RestoreLocalPSR( پورٽ_LONG new_نقاب )
{
    __asm__ __volatile__ (
        "mtcr   %0, psr \n"
        :
        : "r" ( new_نقاب )
        : "memory"
        );
}

خارجي فراغ v_پورٽ_Enter_Critical( فراغ );
خارجي فراغ v_پورٽ_Exit_Critical( فراغ );
خارجي __attribute__( ( naked ) ) فراغ cpu_yeild( فراغ );

#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()                  v_پورٽ_Disable_مداخلت()
#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()                   v_پورٽ_Enable_مداخلت()
#وصف_ڪريو پورٽ_ENTER_CRITICAL()                      v_پورٽ_Enter_Critical()
#وصف_ڪريو پورٽ_EXIT_CRITICAL()                       v_پورٽ_Exit_Critical()
#وصف_ڪريو پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR()         SaveLocalPSR()
#وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( a )    RestoreLocalPSR( a )

#وصف_ڪريو پورٽ_NOP()                                 asm ( "nop" )

خارجي پورٽ_LONG ulCriticalNesting;
خارجي پورٽ_LONG pendsvflag;

#وصف_ڪريو پورٽ_YIELD()              \
    إذا( ulCriticalNesting == 0 ) \
    {                            \
        v_پورٽ_Yield();            \
    }                            \
    وإلا                         \
    {                            \
        pendsvflag = 1;          \
    }                            \
    پورٽ_NOP(); پورٽ_NOP()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters ) __attribute__( ( noreturn ) )
#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/

#وصف_ڪريو پورٽ_پڇاڙي_SWITCHING_ISR( xSwitchRequired ) \
    افعل {                                         \
        إذا( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_منزل_SCHEDULER();        \
            پورٽ_YIELD();                         \
        }                                        \
        وإلا                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } طالما( 0 )

#وصف_ڪريو پورٽ_YIELD_FROM_ISR( a )    vTaskSwitchContext()



/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_پورو /* PORTMACRO_H */
