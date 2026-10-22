/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright 2020 Cambridge Consultants Ltd.
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


#جيڪڏهن_وصف_نه_ٿيل PORTMACRO_H
#وصف_ڪريو PORTMACRO_H

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    خارجي "C" {
#جيڪڏهن_پورو
/* *INDENT-ON* */

#ضمن <limits.h>
#ضمن <stdint.h>

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
#وصف_ڪريو پورٽ_CHAR                 حرف
#وصف_ڪريو پورٽ_FLOAT                عائم
#وصف_ڪريو پورٽ_DOUBLE               مزدوج
#وصف_ڪريو پورٽ_LONG                 ڊگهو
#وصف_ڪريو پورٽ_SHORT                ننڍو
#وصف_ڪريو پورٽ_ڍير_TYPE           بنانشان ڊگهو
#وصف_ڪريو پورٽ_بنياد_TYPE            ڊگهو
#وصف_ڪريو پورٽ_اشارو_سائيز_TYPE    intptr_t

تعريفنوع پورٽ_ڍير_TYPE   ڍير_Type_t;
تعريفنوع ڊگهو             بنياد_Type_t;
تعريفنوع بنانشان ڊگهو    UBaseType_t;

تعريفنوع بنانشان ڊگهو    TickType_t;
#وصف_ڪريو پورٽ_MAX_DELAY              ( ( TickType_t ) ULONG_MAX )

#وصف_ڪريو پورٽ_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Architecture specifics. */
#وصف_ڪريو پورٽ_ڍير_GROWTH                   ( -1 )
#وصف_ڪريو پورٽ_HAS_ڍير_حد_کان_مٿي_CHECKING    ( 1 )
#وصف_ڪريو پورٽ_TICK_PERIOD_MS                 ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#وصف_ڪريو پورٽ_TICK_شرح_MICROSECONDS         ( ( TickType_t ) 1000000 / config_TICK_شرح_HZ )
#وصف_ڪريو پورٽ_BYTE_ALIGNMENT                 8
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
خارجي فراغ v_پورٽ_Yield( فراغ );

#وصف_ڪريو پورٽ_YIELD()                v_پورٽ_Yield()

#وصف_ڪريو پورٽ_پڇاڙي_SWITCHING_ISR( xSwitchRequired ) \
    افعل                                           \
    {                                            \
        إذا( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_منزل_SCHEDULER();        \
            v_پورٽ_Yield();                        \
        }                                        \
        وإلا                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } طالما( 0 )
#وصف_ڪريو پورٽ_YIELD_FROM_ISR( x )    پورٽ_پڇاڙي_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
خارجي فراغ v_پورٽ_Disable_Interrupts( فراغ );
خارجي فراغ v_پورٽ_Enable_Interrupts( فراغ );
#وصف_ڪريو پورٽ_سيٽ_مداخلت_نقاب()      ( v_پورٽ_Disable_Interrupts() )
#وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب()    ( v_پورٽ_Enable_Interrupts() )

خارجي UBaseType_t x_پورٽ_سيٽ_مداخلت_نقاب( فراغ );
خارجي فراغ v_پورٽ_Clear_مداخلت_نقاب( UBaseType_t x_نقاب );

خارجي فراغ v_پورٽ_Enter_Critical( فراغ );
خارجي فراغ v_پورٽ_Exit_Critical( فراغ );
#وصف_ڪريو پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR()         x_پورٽ_سيٽ_مداخلت_نقاب()
#وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( x )    v_پورٽ_Clear_مداخلت_نقاب( x )
#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()                  پورٽ_سيٽ_مداخلت_نقاب()
#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()                   پورٽ_CLEAR_مداخلت_نقاب()
#وصف_ڪريو پورٽ_ENTER_CRITICAL()                      v_پورٽ_Enter_Critical()
#وصف_ڪريو پورٽ_EXIT_CRITICAL()                       v_پورٽ_Exit_Critical()

/*-----------------------------------------------------------*/

خارجي فراغ v_پورٽ_Thread_Dying( فراغ * px_Task_منزل_Delete,
                              متطاير بنياد_Type_t * pxPendYield );
خارجي فراغ v_پورٽ_Cancel_Thread( فراغ * px_Task_منزل_Delete );
#وصف_ڪريو پورٽ_PRE_TASK_DELETE_HOOK( pv_Task_منزل_Delete, pxPendYield )    v_پورٽ_Thread_Dying( ( pv_Task_منزل_Delete ), ( pxPendYield ) )
#وصف_ڪريو پورٽ_CLEAN_مٿي_TCB( pxTCB )                                  v_پورٽ_Cancel_Thread( pxTCB )
/*-----------------------------------------------------------*/

#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )         فراغ vFunction( فراغ * pvParameters ) __attribute__( ( noreturn ) )
#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )               فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/

/*
 * Tasks run in their own pthreads and context switches between them
 * are always a full memory barrier. ISRs are emulated as signals
 * which also imply a full memory barrier.
 *
 * Thus, only a compiler barrier is needed to prevent the compiler
 * reordering.
 */
#وصف_ڪريو پورٽ_يادگيري_BARRIER()                        __asm متطاير ( "" ::: "memory" )

خارجي uint32_t ul_پورٽ_Get_لاڳيتو_وقت( فراغ );
#وصف_ڪريو پورٽ_CONFIGURE_TIMER_FOR_لاڳيتو_وقت_STATS()    /* no-op */
#وصف_ڪريو پورٽ_GET_لاڳيتو_وقت_COUNTER_قدر()            ul_پورٽ_Get_لاڳيتو_وقت()

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_پورو /* PORTMACRO_H */
