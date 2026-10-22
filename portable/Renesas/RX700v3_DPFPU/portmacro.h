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


#اگر_تعریف_نشده PORTMACRO_H
    #تعریف_کن PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    خارجي "C" {
#پایان_اگر
/* *INDENT-ON* */

/* Hardware specifics. */
    #ضمن <machine.h>

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* When the FIT configurator or the Smart Configurator is used, platform.h has to be
 * used. */
    #اگر_تعریف_نشده config_INCLUDE_PLATFORM_H_INSTEAD_از_IODEFINE_H
        #تعریف_کن config_INCLUDE_PLATFORM_H_INSTEAD_از_IODEFINE_H 0
    #پایان_اگر

/* If configUSE_TASK_DPFPU_SUPPORT is set to 1 (or undefined) then each task will
 * be created without a DPFPU context, and a task must call vTaskUsesDPFPU() before
 * making use of any DPFPU registers.  If configUSE_TASK_DPFPU_SUPPORT is set to 2 then
 * tasks are created with a DPFPU context by default, and calling vTaskUsesDPFPU() has
 * no effect.  If configUSE_TASK_DPFPU_SUPPORT is set to 0 then tasks never take care
 * of any DPFPU context (even if DPFPU registers are used). */
    #اگر_تعریف_نشده configUSE_TASK_DPFPU_SUPPORT
        #تعریف_کن configUSE_TASK_DPFPU_SUPPORT 1
    #پایان_اگر

/*-----------------------------------------------------------*/

/* Type definitions - these are a bit legacy and not really used now, other than
 * portSTACK_TYPE and portBASE_TYPE. */
    #تعریف_کن پورت_CHAR          حرف
    #تعریف_کن پورت_FLOAT         عائم
    #تعریف_کن پورت_DOUBLE        مزدوج
    #تعریف_کن پورت_LONG          دراز
    #تعریف_کن پورت_SHORT         کوتاه
    #تعریف_کن پورت_پشته_TYPE    uint32_t
    #تعریف_کن پورت_پایه_TYPE     دراز

    تعريفنوع پورت_پشته_TYPE   پشته_Type_t;
    تعريفنوع دراز             پایه_Type_t;
    تعريفنوع بیعلامت دراز    UBaseType_t;

    #إذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
        تعريفنوع uint16_t     TickType_t;
        #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffff
    #وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_32_بیتها )
        تعريفنوع uint32_t     TickType_t;
        #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
        #تعریف_کن پورت_TICK_TYPE_IS_ATOMIC    1
    #وإلا
        #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
    #پایان_اگر

/*-----------------------------------------------------------*/

/* Hardware specifics. */
    #تعریف_کن پورت_BYTE_ALIGNMENT    8     /* Could make four, according to manual. */
    #تعریف_کن پورت_پشته_GROWTH      -1
    #تعریف_کن پورت_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
    #تعریف_کن پورت_NOP()    nop()

/* Yield equivalent to "*portITU_SWINTR = 0x01; ( void ) *portITU_SWINTR;"
 * where portITU_SWINTR is the location of the software interrupt register
 * (0x000872E0).  Don't rely on the assembler to select a register, so instead
 * save and restore clobbered registers manually. */
    #رهنمود inline_asm v_پورت_Yield
    ساكن فراغ v_پورت_Yield( فراغ )
    {
    #اگر_تعریف_نشده __CDT_PARSER__
        /* Save clobbered register - may not actually be necessary if inline asm
         * functions are considered to use the same rules as function calls by the
         * compiler. */
        افزودن_2.L R5
        /* Set ITU SWINTR. */
        MOV.L # 000872E0H, R5
        MOV.B # 1, [ R5 ]
        /* Read back to ensure the value is taken before proceeding. */
        CMP [ R5 ].UB, R5
        /* Restore clobbered register to its previous value. */
        برداشت_2 R5
    #پایان_اگر
    }

    #تعریف_کن پورت_YIELD()                                       v_پورت_Yield()
    #تعریف_کن پورت_YIELD_FROM_ISR( x )                           افعل { إذا( ( x ) != pdFALSE ) پورت_YIELD(); } طالما( 0 )

/* These macros should not be called directly, but through the
 * taskENTER_CRITICAL() and taskEXIT_CRITICAL() macros.  An extra check is
 * performed if configASSERT() is defined to ensure an assertion handler does not
 * inadvertently attempt to lower the IPL when the call to assert was triggered
 * because the IPL value was found to be above  configMAX_SYSCALL_INTERRUPT_PRIORITY
 * when an ISR safe FreeRTOS API function was executed.  ISR safe FreeRTOS API
 * functions are those that end in FromISR.  FreeRTOS maintains a separate
 * interrupt API to ensure API function and interrupt entry is as fast and as
 * simple as possible. */
    #تعریف_کن پورت_ENABLE_INTERRUPTS()                           مجموعه_ipl( ( دراز ) 0 )
    #إذا ( configASSERT_DEFINED == 1 )
        #تعریف_کن پورت_ASSERT_IF_وقفه_اولویت_INVALID()    configASSERT( ( get_ipl() <= config_MAX_SYSCALL_وقفه_اولویت ) )
        #تعریف_کن پورت_DISABLE_INTERRUPTS()                      إذا( get_ipl() < config_MAX_SYSCALL_وقفه_اولویت ) مجموعه_ipl( ( دراز ) config_MAX_SYSCALL_وقفه_اولویت )
    #وإلا
        #تعریف_کن پورت_DISABLE_INTERRUPTS()                      مجموعه_ipl( ( دراز ) config_MAX_SYSCALL_وقفه_اولویت )
    #پایان_اگر

/* Critical nesting counts are stored in the TCB. */
    #تعریف_کن پورت_CRITICAL_NESTING_درون_TCB    ( 1 )

/* The critical nesting functions defined within tasks.c. */
    خارجي فراغ vTaskEnterCritical( فراغ );
    خارجي فراغ vTaskExitCritical( فراغ );
    #تعریف_کن پورت_ENTER_CRITICAL()    vTaskEnterCritical()
    #تعریف_کن پورت_EXIT_CRITICAL()     vTaskExitCritical()

/* As this port allows interrupt nesting... */
    #تعریف_کن پورت_مجموعه_وقفه_ماسک_FROM_ISR()                              ( UBaseType_t ) get_ipl(); مجموعه_ipl( ( دراز ) config_MAX_SYSCALL_وقفه_اولویت )
    #تعریف_کن پورت_CLEAR_وقفه_ماسک_FROM_ISR( ux_Saved_وقفه_وضعیت )    مجموعه_ipl( ( دراز ) ux_Saved_وقفه_وضعیت )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
    #تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/*-----------------------------------------------------------*/

/* If configUSE_TASK_DPFPU_SUPPORT is set to 1 (or left undefined) then tasks are
 * created without a DPFPU context and must call vPortTaskUsesDPFPU() to give
 * themselves a DPFPU context before using any DPFPU instructions.  If
 * configUSE_TASK_DPFPU_SUPPORT is set to 2 then all tasks will have a DPFPU context
 * by default. */
    #إذا( configUSE_TASK_DPFPU_SUPPORT == 1 )
        فراغ v_پورت_Task_استفاده_میکند_DPFPU( فراغ );
    #وإلا
/* Each task has a DPFPU context already, so define this function away to
 * nothing to prevent it being called accidentally. */
        #تعریف_کن v_پورت_Task_استفاده_میکند_DPFPU()
    #پایان_اگر
    #تعریف_کن پورت_TASK_استفاده_میکند_DPFPU() v_پورت_Task_استفاده_میکند_DPFPU()

/* Definition to allow compatibility with existing FreeRTOS Demo using flop.c. */
    #تعریف_کن پورت_TASK_استفاده_میکند_FLOATING_نقطه() v_پورت_Task_استفاده_میکند_DPFPU()

#رهنمود inline_asm v_پورت_حافظه_Barrier
ساكن فراغ v_پورت_حافظه_Barrier( فراغ )
{
}

#تعریف_کن پورت_حافظه_BARRIER()    v_پورت_حافظه_Barrier()

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */
