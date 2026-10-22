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

/*
 *  Changes from V3.2.3
 *
 + Modified portENTER_SWITCHING_ISR() to allow use with GCC V4.0.1.
 +
 +  Changes from V3.2.4
 +
 + Removed the use of the %0 parameter within the assembler macros and
 +    replaced them with hard coded registers.  This will ensure the
 +    assembler does not select the link register as the temp register as
 +    was occasionally happening previously.
 +
 + The assembler statements are now included in a single asm block rather
 +    than each line having its own asm block.
 +
 +  Changes from V4.5.0
 +
 + Removed the portENTER_SWITCHING_ISR() and portEXIT_SWITCHING_ISR() macros
 +    and replaced them with portYIELD_FROM_ISR() macro.  Application code
 +    should now make use of the portSAVE_CONTEXT() and portRESTORE_CONTEXT()
 +    macros as per the V4.5.1 demo code.
 */

#اگر_غیر_تعریف_شدہ PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    خارجی "C" {
#اگر_ختم
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
#تعریف_کرو پورٹ_FLOAT         اعشاری
#تعریف_کرو پورٹ_DOUBLE        دوہرا
#تعریف_کرو پورٹ_LONG          طویل
#تعریف_کرو پورٹ_SHORT         مختصر
#تعریف_کرو پورٹ_ڈھیر_TYPE    uint32_t
#تعریف_کرو پورٹ_بنیاد_TYPE     پورٹ_LONG

قسمتعریف پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
قسمتعریف طویل             بنیاد_Type_t;
قسمتعریف غیرعلامتی طویل    UBaseType_t;

#اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    قسمتعریف uint16_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffff
#وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    قسمتعریف uint32_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#ورنہ
    #غلطی config_TICK_TYPE_چوڑائی_اندر_بٹ سیٹ مقصد unsupported tick type چوڑائی.
#اگر_ختم
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH      ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_BYTE_ALIGNMENT    8
#تعریف_کرو پورٹ_NOP()    __asm متلون ( "NOP" );
/*-----------------------------------------------------------*/


/* Scheduler utilities. */

/*
 * portRESTORE_CONTEXT, portRESTORE_CONTEXT, portENTER_SWITCHING_ISR
 * and portEXIT_SWITCHING_ISR can only be called from ARM mode, but
 * are included here for efficiency.  An attempt to call one from
 * THUMB mode code will result in a compile time error.
 */

#تعریف_کرو پورٹ_RESTORE_CONTEXT()                                                 \
    {                                                                         \
        خارجی متلون خالی * متلون pxCurrentTCB;                         \
        خارجی متلون uint32_t ulCriticalNesting;                           \
                                                                              \
        /* Set the LR to the task stack. */                                   \
        __asm متلون (                                                      \
            "LDR        R0, =pxCurrentTCB                               \n\t" \
            "LDR        R0, [R0]                                        \n\t" \
            "LDR        LR, [R0]                                        \n\t" \
                                                                              \
            /* The critical nesting depth is the first item on the stack. */  \
            /* Load it into the ulCriticalNesting variable. */                \
            "LDR        R0, =ulCriticalNesting                          \n\t" \
            "LDMFD  LR!, {R1}                                           \n\t" \
            "STR        R1, [R0]                                        \n\t" \
                                                                              \
            /* Get the SPSR from the stack. */                                \
            "LDMFD  LR!, {R0}                                           \n\t" \
            "MSR        SPSR, R0                                        \n\t" \
                                                                              \
            /* Restore all system mode registers for the task. */             \
            "LDMFD  LR, {R0-R14}^                                       \n\t" \
            "NOP                                                        \n\t" \
                                                                              \
            /* Restore the return address. */                                 \
            "LDR        LR, [LR, #+60]                                  \n\t" \
                                                                              \
            /* And return - correcting the offset in the LR to obtain the */  \
            /* correct address. */                                            \
            "SUBS   PC, LR, #4                                          \n\t" \
            );                                                                \
        ( خالی ) ulCriticalNesting;                                           \
        ( خالی ) pxCurrentTCB;                                                \
    }
/*-----------------------------------------------------------*/

#تعریف_کرو پورٹ_SAVE_CONTEXT()                                                    \
    {                                                                         \
        خارجی متلون خالی * متلون pxCurrentTCB;                         \
        خارجی متلون uint32_t ulCriticalNesting;                           \
                                                                              \
        /* Push R0 as we are going to use the register. */                    \
        __asm متلون (                                                      \
            "STMDB  SP!, {R0}                                           \n\t" \
                                                                              \
            /* Set R0 to point to the task stack pointer. */                  \
            "STMDB  SP,{SP}^                                            \n\t" \
            "NOP                                                        \n\t" \
            "SUB    SP, SP, #4                                          \n\t" \
            "LDMIA  SP!,{R0}                                            \n\t" \
                                                                              \
            /* Push the return address onto the stack. */                     \
            "STMDB  R0!, {LR}                                           \n\t" \
                                                                              \
            /* Now we have saved LR we can use it instead of R0. */           \
            "MOV    LR, R0                                              \n\t" \
                                                                              \
            /* Pop R0 so we can save it onto the system mode stack. */        \
            "LDMIA  SP!, {R0}                                           \n\t" \
                                                                              \
            /* Push all the system mode registers onto the task stack. */     \
            "STMDB  LR,{R0-LR}^                                         \n\t" \
            "NOP                                                        \n\t" \
            "SUB    LR, LR, #60                                         \n\t" \
                                                                              \
            /* Push the SPSR onto the task stack. */                          \
            "MRS    R0, SPSR                                            \n\t" \
            "STMDB  LR!, {R0}                                           \n\t" \
                                                                              \
            "LDR    R0, =ulCriticalNesting                              \n\t" \
            "LDR    R0, [R0]                                            \n\t" \
            "STMDB  LR!, {R0}                                           \n\t" \
                                                                              \
            /* Store the new top of stack for the task. */                    \
            "LDR    R0, =pxCurrentTCB                                   \n\t" \
            "LDR    R0, [R0]                                            \n\t" \
            "STR    LR, [R0]                                            \n\t" \
            );                                                                \
        ( خالی ) ulCriticalNesting;                                           \
        ( خالی ) pxCurrentTCB;                                                \
    }


#تعریف_کرو پورٹ_YIELD_FROM_ISR()    vTaskSwitchContext()
#تعریف_کرو پورٹ_YIELD()             __asm متلون ( "SWI 0" )
/*-----------------------------------------------------------*/


/* Critical section management. */

/*
 * The interrupt management utilities can only be called from ARM mode.  When
 * THUMB_INTERWORK is defined the utilities are defined as functions in
 * portISR.c to ensure a switch to ARM mode.  When THUMB_INTERWORK is not
 * defined then the utilities are defined as macros here - as per other ports.
 */

#اگر_تعریف_شدہ THUMB_INTERWORK

    خارجی خالی v_پورٹ_Disable_Interrupts_From_Thumb( خالی ) __attribute__( ( naked ) );
    خارجی خالی v_پورٹ_Enable_Interrupts_From_Thumb( خالی ) __attribute__( ( naked ) );

    #تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    v_پورٹ_Disable_Interrupts_From_Thumb()
    #تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     v_پورٹ_Enable_Interrupts_From_Thumb()

#ورنہ

    #تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                                       \
    __asm متلون (                                                       \
        "STMDB  SP!, {R0}       \n\t"   /* Push R0.                     */ \
        "MRS    R0, CPSR        \n\t"   /* Get CPSR.                    */ \
        "ORR    R0, R0, #0xC0   \n\t"   /* Disable IRQ, FIQ.            */ \
        "MSR    CPSR, R0        \n\t"   /* Write back modified value.   */ \
        "LDMIA  SP!, {R0}           " ) /* Pop R0.                      */

    #تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                                        \
    __asm متلون (                                                       \
        "STMDB  SP!, {R0}       \n\t"   /* Push R0.                     */ \
        "MRS    R0, CPSR        \n\t"   /* Get CPSR.                    */ \
        "BIC    R0, R0, #0xC0   \n\t"   /* Enable IRQ, FIQ.             */ \
        "MSR    CPSR, R0        \n\t"   /* Write back modified value.   */ \
        "LDMIA  SP!, {R0}           " ) /* Pop R0.                      */

#اگر_ختم /* THUMB_INTERWORK */

خارجی خالی v_پورٹ_Enter_Critical( خالی );
خارجی خالی v_پورٹ_Exit_Critical( خالی );

#تعریف_کرو پورٹ_ENTER_CRITICAL()    v_پورٹ_Enter_Critical();
#تعریف_کرو پورٹ_EXIT_CRITICAL()     v_پورٹ_Exit_Critical();
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    }
#اگر_ختم
/* *INDENT-ON* */

#اگر_ختم /* PORTMACRO_H */
