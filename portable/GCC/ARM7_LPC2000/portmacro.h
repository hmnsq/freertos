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
#وصف_ڪريو پورٽ_CHAR          حرف
#وصف_ڪريو پورٽ_FLOAT         عائم
#وصف_ڪريو پورٽ_DOUBLE        مزدوج
#وصف_ڪريو پورٽ_LONG          ڊگهو
#وصف_ڪريو پورٽ_SHORT         ننڍو
#وصف_ڪريو پورٽ_ڍير_TYPE    uint32_t
#وصف_ڪريو پورٽ_بنياد_TYPE     پورٽ_LONG

تعريفنوع پورٽ_ڍير_TYPE   ڍير_Type_t;
تعريفنوع ڊگهو             بنياد_Type_t;
تعريفنوع بنانشان ڊگهو    UBaseType_t;

#إذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_16_بٽ )
    تعريفنوع uint16_t     TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_32_بٽ )
    تعريفنوع uint32_t     TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#وإلا
    #غلطي config_TICK_TYPE_ويڪر_اندريون_بٽ سيٽ منزل unsupported tick type ويڪر.
#جيڪڏهن_پورو
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#وصف_ڪريو پورٽ_ڍير_GROWTH      ( -1 )
#وصف_ڪريو پورٽ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#وصف_ڪريو پورٽ_BYTE_ALIGNMENT    8
#وصف_ڪريو پورٽ_NOP()    __asm متطاير ( "NOP" );
/*-----------------------------------------------------------*/


/* Scheduler utilities. */

/*
 * portRESTORE_CONTEXT, portRESTORE_CONTEXT, portENTER_SWITCHING_ISR
 * and portEXIT_SWITCHING_ISR can only be called from ARM mode, but
 * are included here for efficiency.  An attempt to call one from
 * THUMB mode code will result in a compile time error.
 */

#وصف_ڪريو پورٽ_RESTORE_CONTEXT()                                                 \
    {                                                                         \
        خارجي متطاير فراغ * متطاير pxCurrentTCB;                         \
        خارجي متطاير uint32_t ulCriticalNesting;                           \
                                                                              \
        /* Set the LR to the task stack. */                                   \
        __asm متطاير (                                                      \
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
        ( فراغ ) ulCriticalNesting;                                           \
        ( فراغ ) pxCurrentTCB;                                                \
    }
/*-----------------------------------------------------------*/

#وصف_ڪريو پورٽ_SAVE_CONTEXT()                                                    \
    {                                                                         \
        خارجي متطاير فراغ * متطاير pxCurrentTCB;                         \
        خارجي متطاير uint32_t ulCriticalNesting;                           \
                                                                              \
        /* Push R0 as we are going to use the register. */                    \
        __asm متطاير (                                                      \
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
        ( فراغ ) ulCriticalNesting;                                           \
        ( فراغ ) pxCurrentTCB;                                                \
    }

خارجي فراغ vTaskSwitchContext( فراغ );
#وصف_ڪريو پورٽ_YIELD_FROM_ISR()    vTaskSwitchContext()
#وصف_ڪريو پورٽ_YIELD()             __asm متطاير ( "SWI 0" )
/*-----------------------------------------------------------*/


/* Critical section management. */

/*
 * The interrupt management utilities can only be called from ARM mode.  When
 * THUMB_INTERWORK is defined the utilities are defined as functions in
 * portISR.c to ensure a switch to ARM mode.  When THUMB_INTERWORK is not
 * defined then the utilities are defined as macros here - as per other ports.
 */

#جيڪڏهن_وصف_ٿيل THUMB_INTERWORK

    خارجي فراغ v_پورٽ_Disable_Interrupts_From_Thumb( فراغ ) __attribute__( ( naked ) );
    خارجي فراغ v_پورٽ_Enable_Interrupts_From_Thumb( فراغ ) __attribute__( ( naked ) );

    #وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()    v_پورٽ_Disable_Interrupts_From_Thumb()
    #وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()     v_پورٽ_Enable_Interrupts_From_Thumb()

#وإلا

    #وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()                                       \
    __asm متطاير (                                                       \
        "STMDB  SP!, {R0}       \n\t"   /* Push R0.                     */ \
        "MRS    R0, CPSR        \n\t"   /* Get CPSR.                    */ \
        "ORR    R0, R0, #0xC0   \n\t"   /* Disable IRQ, FIQ.            */ \
        "MSR    CPSR, R0        \n\t"   /* Write back modified value.   */ \
        "LDMIA  SP!, {R0}           " ) /* Pop R0.                      */

    #وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()                                        \
    __asm متطاير (                                                       \
        "STMDB  SP!, {R0}       \n\t"   /* Push R0.                     */ \
        "MRS    R0, CPSR        \n\t"   /* Get CPSR.                    */ \
        "BIC    R0, R0, #0xC0   \n\t"   /* Enable IRQ, FIQ.             */ \
        "MSR    CPSR, R0        \n\t"   /* Write back modified value.   */ \
        "LDMIA  SP!, {R0}           " ) /* Pop R0.                      */

#جيڪڏهن_پورو /* THUMB_INTERWORK */

خارجي فراغ v_پورٽ_Enter_Critical( فراغ );
خارجي فراغ v_پورٽ_Exit_Critical( فراغ );

#وصف_ڪريو پورٽ_ENTER_CRITICAL()    v_پورٽ_Enter_Critical();
#وصف_ڪريو پورٽ_EXIT_CRITICAL()     v_پورٽ_Exit_Critical();
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_پورو /* PORTMACRO_H */
