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
#تعریف_کړه پورټ_CHAR        حرف
#تعریف_کړه پورټ_FLOAT       عائم
#تعریف_کړه پورټ_DOUBLE      مزدوج
#تعریف_کړه پورټ_LONG        اوږد
#تعریف_کړه پورټ_SHORT       صحيح
#تعریف_کړه پورټ_ډېری_TYPE  uint8_t
#تعریف_کړه پورټ_بنسټ_TYPE   حرف

تعريفنوع پورټ_ډېری_TYPE ډېری_Type_t;
تعريفنوع نښهدار حرف بنسټ_Type_t;
تعريفنوع بینښه حرف UBaseType_t;

#إذا( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
    تعريفنوع uint16_t TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه  == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t             TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
#د_که_پای
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کړه پورټ_BYTE_ALIGNMENT          1
#تعریف_کړه پورټ_GLOBAL_INT_ENABLE_بټ   0x80
#تعریف_کړه پورټ_ډېری_GROWTH            1
#تعریف_کړه پورټ_TICK_PERIOD_MS          ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
/*-----------------------------------------------------------*/

/* Critical section management. */
#تعریف_کړه پورټ_DISABLE_INTERRUPTS()    INTCONbits.GIEH = 0;
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()     INTCONbits.GIEH = 1;

/* Push the INTCON register onto the stack, then disable interrupts. */
#تعریف_کړه پورټ_ENTER_CRITICAL()        POSTINC1 = INTCON;              \
                                    INTCONbits.GIEH = 0;

/* Retrieve the INTCON register from the stack, and enable interrupts
if they were saved as being enabled.  Don't modify any other bits
within the INTCON register as these may have legitimately have been
modified within the critical region. */
#تعریف_کړه پورټ_EXIT_CRITICAL()         _asm                                    \
                                        MOVF    POSTDEC1, 1, 0              \
                                    _endasm                                 \
                                    إذا( INDF1 & پورټ_GLOBAL_INT_ENABLE_بټ ) \
                                    {                                       \
                                        پورټ_ENABLE_INTERRUPTS();            \
                                    }
/*-----------------------------------------------------------*/

/* Task utilities. */
خارجي فراغ v_پورټ_Yield( فراغ );
#تعریف_کړه پورټ_YIELD()             v_پورټ_Yield()
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )
/*-----------------------------------------------------------*/

/* Required by the kernel aware debugger. */
#که_تعریف_شوی __DEBUG
    #تعریف_کړه پورټ_REMOVE_STATIC_QUALIFIER
#د_که_پای


#تعریف_کړه پورټ_NOP()               _asm    \
                                    NOP \
                                _endasm

#د_که_پای /* PORTMACRO_H */
