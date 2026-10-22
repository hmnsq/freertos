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
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#وصف_ڪريو پورٽ_CHAR        حرف
#وصف_ڪريو پورٽ_FLOAT       عائم
#وصف_ڪريو پورٽ_DOUBLE      ڊگهو
#وصف_ڪريو پورٽ_LONG        ڊگهو
#وصف_ڪريو پورٽ_SHORT       صحيح
#وصف_ڪريو پورٽ_ڍير_TYPE  uint16_t
#وصف_ڪريو پورٽ_بنياد_TYPE   ننڍو

تعريفنوع پورٽ_ڍير_TYPE ڍير_Type_t;
تعريفنوع ننڍو بنياد_Type_t;
تعريفنوع بنانشان ننڍو UBaseType_t;


#إذا( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_16_بٽ )
    تعريفنوع uint16_t TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ  == TICK_TYPE_ويڪر_32_بٽ )
    تعريفنوع uint32_t             TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #غلطي config_TICK_TYPE_ويڪر_اندريون_بٽ سيٽ منزل unsupported tick type ويڪر.
#جيڪڏهن_پورو
/*-----------------------------------------------------------*/

/* Critical section handling. */
#وصف_ڪريو پورٽ_ENTER_CRITICAL()            __asm{ pushf }  \
                                        __asm{ cli   }  \

#وصف_ڪريو پورٽ_EXIT_CRITICAL()             __asm{ popf }

#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()        __asm{ cli }

#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()         __asm{ sti }
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#وصف_ڪريو پورٽ_NOP()                       __asm{ nop }
#وصف_ڪريو پورٽ_ڍير_GROWTH                ( -1 )
#وصف_ڪريو پورٽ_SWITCH_INT_عدد           0x80
#وصف_ڪريو پورٽ_YIELD()                     __asm{ صحيح پورٽ_SWITCH_INT_عدد }
#وصف_ڪريو پورٽ_TICK_PERIOD_MS              ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#وصف_ڪريو پورٽ_BYTE_ALIGNMENT              2
#وصف_ڪريو پورٽ_INITIAL_SW                  ( ( پورٽ_ڍير_TYPE ) 0x0202 )   /* Start the tasks with interrupts enabled. */
/*-----------------------------------------------------------*/

/* Compiler specifics. */
#وصف_ڪريو پورٽ_داخلا_BYTE( xAddr )             inp( xAddr )
#وصف_ڪريو پورٽ_OUTPUT_BYTE( xAddr, uc_قدر )   outp( xAddr, uc_قدر )
#وصف_ڪريو پورٽ_داخلا_لفظ( xAddr )             inpw( xAddr )
#وصف_ڪريو پورٽ_OUTPUT_لفظ( xAddr, us_قدر )   outpw( xAddr, us_قدر )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vTaskFunction, vParameters ) فراغ vTaskFunction( فراغ *pvParameters )
#وصف_ڪريو پورٽ_TASK_FUNCTION( vTaskFunction, vParameters ) فراغ vTaskFunction( فراغ *pvParameters )

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */


#جيڪڏهن_پورو /* PORTMACRO_H */
