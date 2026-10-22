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

#جيڪڏهن_وصف_نه_ٿيل PORTMACRO_H
#وصف_ڪريو PORTMACRO_H

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    خارجي "C" {
#جيڪڏهن_پورو
/* *INDENT-ON* */

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the given hardware
 * and compiler.
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

تعريفنوع uint32_t         TickType_t;
#وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#وصف_ڪريو پورٽ_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#وصف_ڪريو پورٽ_ڍير_GROWTH      ( -1 )
#وصف_ڪريو پورٽ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#وصف_ڪريو پورٽ_BYTE_ALIGNMENT    8

/*-----------------------------------------------------------*/

/* Task utilities. */

/* Called at the end of an ISR that can cause a context switch. */
#وصف_ڪريو پورٽ_پڇاڙي_SWITCHING_ISR( xSwitchRequired )      \
    {                                                 \
        خارجي متطاير uint32_t ul_پورٽ_Yield_Required; \
                                                      \
        إذا( xSwitchRequired != pdFALSE )              \
        {                                             \
            ul_پورٽ_Yield_Required = pdTRUE;             \
        }                                             \
    }

#وصف_ڪريو پورٽ_YIELD_FROM_ISR( x )    پورٽ_پڇاڙي_SWITCHING_ISR( x )

فراغ v_پورٽ_Yield( فراغ );

#وصف_ڪريو پورٽ_YIELD()     v_پورٽ_Yield();

/*-----------------------------------------------------------*/

/*
 * Critical section management.
 */

خارجي فراغ v_پورٽ_Enter_Critical( فراغ );
خارجي فراغ v_پورٽ_Exit_Critical( فراغ );
خارجي فراغ v_پورٽ_Enable_Interrupts( فراغ );
خارجي فراغ v_پورٽ_Disable_Interrupts( فراغ );
خارجي uint32_t ul_پورٽ_سيٽ_مداخلت_نقاب_From_ISR( فراغ );

/* In the absence of a priority mask register, these functions and macros
 * globally enable and disable interrupts. */
#وصف_ڪريو پورٽ_ENTER_CRITICAL()                    v_پورٽ_Enter_Critical();
#وصف_ڪريو پورٽ_EXIT_CRITICAL()                     v_پورٽ_Exit_Critical();
#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()                 v_پورٽ_Enable_Interrupts();
#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()                v_پورٽ_Disable_Interrupts();
#وصف_ڪريو پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR()       ul_پورٽ_سيٽ_مداخلت_نقاب_From_ISR();
#وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( x )  افعل { إذا( x == 0 ) پورٽ_ENABLE_INTERRUPTS(); } طالما( 0 )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* Tickless idle/low power functionality. */
#جيڪڏهن_وصف_نه_ٿيل پورٽ_SUPPRESS_TICKS_AND_SLEEP
    خارجي فراغ v_پورٽ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وقت );
    #وصف_ڪريو پورٽ_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_وقت )    v_پورٽ_Suppress_Ticks_And_Sleep( x_Expected_Idle_وقت )
#جيڪڏهن_پورو

/* Prototype of the FreeRTOS tick handler.  This must be installed as the
 * handler for whichever peripheral is used to generate the RTOS tick. */
فراغ FreeRTOS_Tick_Handler( فراغ );

/**
 * @brief Returns the number of leading zeros in a 32 bit variable.
 *
 * @param[in] ulBitmap 32-Bit number to count leading zeros in.
 *
 * @return The number of leading zeros in ulBitmap.
 */
UBaseType_t ul_پورٽ_ڳڻپ_Leading_Zeros( UBaseType_t ulBitmap );

/* If configUSE_TASK_FPU_SUPPORT is set to 1 (or left undefined) then tasks are
 * created without an FPU context and must call vPortTaskUsesFPU() to give
 * themselves an FPU context before using any FPU instructions.  If
 * configUSE_TASK_FPU_SUPPORT is set to 2 then all tasks will have an FPU
 * context by default. */
#إذا ( configUSE_TASK_FPU_SUPPORT != 2 )
    فراغ v_پورٽ_Task_استعمال_ڪري_FPU( فراغ );
#وإلا
    /* Each task has an FPU context already, so define this function as a
     * no-op. */
    #وصف_ڪريو v_پورٽ_Task_استعمال_ڪري_FPU()
#جيڪڏهن_پورو
#وصف_ڪريو پورٽ_TASK_استعمال_ڪري_FLOATING_نقطو()    v_پورٽ_Task_استعمال_ڪري_FPU()

#وصف_ڪريو پورٽ_سڀ_کان_هيٺ_مداخلت_ترجيح           ( ( ( uint32_t ) config_UNIQUE_مداخلت_PRIORITIES ) - 1UL )
#وصف_ڪريو پورٽ_سڀ_کان_هيٺ_USABLE_مداخلت_ترجيح    ( پورٽ_سڀ_کان_هيٺ_مداخلت_ترجيح - 1UL )

/* Architecture specific optimisations. */
#جيڪڏهن_وصف_نه_ٿيل config_USE_پورٽ_OPTIMISED_TASK_SELECTION
    #وصف_ڪريو config_USE_پورٽ_OPTIMISED_TASK_SELECTION    1
#جيڪڏهن_پورو

#إذا config_USE_پورٽ_OPTIMISED_TASK_SELECTION == 1

    /* Store, clear and get the ready priorities in a bit map. */
    #وصف_ڪريو پورٽ_رڪارڊ_READY_ترجيح( ux_ترجيح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجيح ) )
    #وصف_ڪريو پورٽ_RESET_READY_ترجيح( ux_ترجيح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجيح ) )
    #وصف_ڪريو پورٽ_GET_HIGHEST_ترجيح( ux_چوٽي_ترجيح, uxReadyPriorities )  ux_چوٽي_ترجيح = ( 31UL - ul_پورٽ_ڳڻپ_Leading_Zeros( ( ux_چوٽي_Ready_ترجيح ) ) )

#جيڪڏهن_پورو /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#وصف_ڪريو پورٽ_NOP()               __asm متطاير ( "NOP" )
#وصف_ڪريو پورٽ_INLINE              __inline
#وصف_ڪريو پورٽ_يادگيري_BARRIER()    __asm متطاير ( "" ::: "memory" )

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_پورو /* PORTMACRO_H */
