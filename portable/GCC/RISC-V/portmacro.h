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


#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PORTMACRO_H
#ವ್ಯಾಖ್ಯಾನಿಸು PORTMACRO_H

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ
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
#ಆದರೆ __riscv_xlen == 64
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_TYPE           uint64_t
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ತಳ_TYPE            int64_t
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_UBASE_TYPE           uint64_t
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY            ( TickType_t ) 0xffffffffffffffffUL
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE    uint64_t
#ಅಥವಾಆದರೆ __riscv_xlen == 32
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_TYPE           uint32_t
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ತಳ_TYPE            int32_t
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_UBASE_TYPE           uint32_t
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY            ( TickType_t ) 0xffffffffUL
#ಇಲ್ಲದಿದ್ದರೆ /* if __riscv_xlen == 64 */
    #ದೋಷ "Assembler did not define __riscv_xlen"
#ಆದರೆ_ಅಂತ್ಯ /* if __riscv_xlen == 64 */

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_ರಾಶಿ_TYPE   ರಾಶಿ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_ತಳ_TYPE    ತಳ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_UBASE_TYPE   UBaseType_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_UBASE_TYPE   TickType_t;

/* Legacy type definitions. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CHAR                   ಅಕ್ಷರ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FLOAT                  ದಶಮಾಂಶ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DOUBLE                 ದ್ವಿಗುಣ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_LONG                   ದೀರ್ಘ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SHORT                  ಗಿಡ್ಡ

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_TYPE_IS_ATOMIC    1
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_GROWTH          ( -1 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_ದರ_HZ )
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __riscv_32e
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_BYTE_ALIGNMENT    8     /* RV32E uses RISC-V EABI with reduced stack alignment requirements */
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_BYTE_ALIGNMENT    16
#ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
ಬಾಹ್ಯ ಶೂನ್ಯ vTaskSwitchContext( ಶೂನ್ಯ );
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD()                __asm ಅಸ್ಥಿರ ( "ecall" );
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( xSwitchRequired ) \
    ಮಾಡು                                           \
    {                                            \
        ಆದರೆ( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_ಗಮ್ಯ_SCHEDULER();        \
            vTaskSwitchContext();                \
        }                                        \
        ಇಲ್ಲದಿದ್ದರೆ                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } ಆಗ( 0 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_FROM_ISR( x )    ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CRITICAL_NESTING_ಒಳ_TCB    0

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS()                                   __asm ಅಸ್ಥಿರ ( "csrc mstatus, 8" )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_INTERRUPTS()                                    __asm ಅಸ್ಥಿರ ( "csrs mstatus, 8" )

ಬಾಹ್ಯ size_t xCriticalNesting;
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL()      \
    {                             \
        ಪೋರ್ಟ್_DISABLE_INTERRUPTS(); \
        xCriticalNesting++;       \
    }

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL()          \
    {                                \
        xCriticalNesting--;          \
        ಆದರೆ( xCriticalNesting == 0 )  \
        {                            \
            ಪೋರ್ಟ್_ENABLE_INTERRUPTS(); \
        }                            \
    }

/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION
    #ವ್ಯಾಖ್ಯಾನಿಸು config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION    1
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ ( config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION == 1 )

/* Check the configuration. */
    #ಆದರೆ ( configMAX_PRIORITIES > 32 )
        #ದೋಷ "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #ಆದರೆ_ಅಂತ್ಯ

/* Store/clear the ready priorities in a bit map. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ದಾಖಲೆ_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ಆದ್ಯತೆ ) )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESET_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ಆದ್ಯತೆ ) )

/*-----------------------------------------------------------*/

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_HIGHEST_ಆದ್ಯತೆ( ux_ತುದಿ_ಆದ್ಯತೆ, uxReadyPriorities )    ux_ತುದಿ_ಆದ್ಯತೆ = ( 31UL - __builtin_clz( uxReadyPriorities ) )

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */


/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. These are
 * not necessary for to use this port.  They are defined so the common demo
 * files (which build with all the ports) will build. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION( vFunction, pvParameters )          ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )

/*-----------------------------------------------------------*/

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NOP()    __asm ಅಸ್ಥಿರ ( " nop " )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INLINE              __inline

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ಪೋರ್ಟ್_FORCE_INLINE
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FORCE_INLINE    ಸಾಲೊಳಗೆ __attribute__( ( always_inline ) )
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER()    __asm ಅಸ್ಥಿರ ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* configCLINT_BASE_ADDRESS is a legacy definition that was replaced by the
 * configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS definitions.  For
 * backward compatibility derive the newer definitions from the old if the old
 * definition is found. */
#ಆದರೆ defined( config_CLINT_ತಳ_ವಿಳಾಸ ) && !defined( config_MTIME_ತಳ_ವಿಳಾಸ ) && ( config_CLINT_ತಳ_ವಿಳಾಸ == 0 )

/* Legacy case where configCLINT_BASE_ADDRESS was defined as 0 to indicate
 * there was no CLINT.  Equivalent now is to set the MTIME and MTIMECMP
 * addresses to 0. */
    #ವ್ಯಾಖ್ಯಾನಿಸು config_MTIME_ತಳ_ವಿಳಾಸ       ( 0 )
    #ವ್ಯಾಖ್ಯಾನಿಸು config_MTIMECMP_ತಳ_ವಿಳಾಸ    ( 0 )
#ಅಥವಾಆದರೆ defined( config_CLINT_ತಳ_ವಿಳಾಸ ) && !defined( config_MTIME_ತಳ_ವಿಳಾಸ )

/* Legacy case where configCLINT_BASE_ADDRESS was set to the base address of
 * the CLINT.  Equivalent now is to derive the MTIME and MTIMECMP addresses
 * from the CLINT address. */
    #ವ್ಯಾಖ್ಯಾನಿಸು config_MTIME_ತಳ_ವಿಳಾಸ       ( ( config_CLINT_ತಳ_ವಿಳಾಸ ) + 0xBFF8UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು config_MTIMECMP_ತಳ_ವಿಳಾಸ    ( ( config_CLINT_ತಳ_ವಿಳಾಸ ) + 0x4000UL )
#ಅಥವಾಆದರೆ !defined( config_MTIME_ತಳ_ವಿಳಾಸ ) || !defined( config_MTIMECMP_ತಳ_ವಿಳಾಸ )
    #ದೋಷ "configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  Set them to zero if there is no MTIME (machine time) clock.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#ಆದರೆ_ಅಂತ್ಯ /* if defined( configCLINT_BASE_ADDRESS ) && !defined( configMTIME_BASE_ADDRESS ) && ( configCLINT_BASE_ADDRESS == 0 ) */

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    }
#ಆದರೆ_ಅಂತ್ಯ
/* *INDENT-ON* */

#ಆದರೆ_ಅಂತ್ಯ /* PORTMACRO_H */
