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

#ifndef PORTMACRO_H
#define PORTMACRO_H

/* *INDENT-OFF* */
#ifdef __cplusplus
    خارجي "C" {
#endif
/* *INDENT-ON* */

/* BSP includes. */
#ضمن <mb_interface.h>
#ضمن <xparameters.h>

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
#define portCHAR              حرف
#define portFLOAT             عائم
#define portDOUBLE            مزدوج
#define portLONG              long
#define portSHORT             short
#ifdef __arch64__
    #define port_تيندنن_TYPE    size_t
    تعريفنوع uint64_t        UBaseType_t;
#وإلا
    #define port_تيندنن_TYPE    uint32_t
    تعريفنوع unsigned long   UBaseType_t;
#endif
#define portBASE_TYPE         long

تعريفنوع port_تيندنن_TYPE      تيندنن_Type_t;
تعريفنوع long                BaseType_t;


#إذا ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    تعريفنوع uint16_t        TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    تعريفنوع uint32_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #define portTICK_TYPE_IS_ATOMIC    1
#وإلا
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Interrupt control macros and functions. */
فراغ microblaze_disable_interrupts( فراغ );
فراغ microblaze_enable_interrupts( فراغ );
#define portDISABLE_INTERRUPTS()    microblaze_disable_interrupts()
#define portENABLE_INTERRUPTS()     microblaze_enable_interrupts()
/*-----------------------------------------------------------*/

/* Critical section macros. */
فراغ vPortEnterCritical( فراغ );
فراغ vPortExitCritical( فراغ );
#define portENTER_CRITICAL()                           \
    {                                                  \
        خارجي متطاير UBaseType_t uxCriticalNesting; \
        microblaze_disable_interrupts();               \
        uxCriticalNesting++;                           \
    }

#define portEXIT_CRITICAL()                            \
    {                                                  \
        خارجي متطاير UBaseType_t uxCriticalNesting; \
        /* Interrupts are disabled, so we can */       \
        /* access the variable directly. */            \
        uxCriticalNesting--;                           \
        إذا( uxCriticalNesting == 0 )                   \
        {                                              \
            /* The nesting has unwound and we \
             * can enable interrupts again. */ \
            portENABLE_INTERRUPTS();           \
        }                                      \
    }

/*-----------------------------------------------------------*/

/* The yield macro maps directly to the vPortYield() function. */
فراغ vPortYield( فراغ );
#define portYIELD()    vPortYield()

/* portYIELD_FROM_ISR() does not directly call vTaskSwitchContext(), but instead
 * sets a flag to say that a yield has been requested.  The interrupt exit code
 * then checks this flag, and calls vTaskSwitchContext() before restoring a task
 * context, if the flag is not false.  This is done to prevent multiple calls to
 * vTaskSwitchContext() being made from a single interrupt, as a single interrupt
 * can result in multiple peripherals being serviced. */
خارجي متطاير uint32_t ulTaskSwitchRequested;
#define portYIELD_FROM_ISR( x )                              \
    افعل { إذا( ( x ) != pdFALSE ) ulTaskSwitchRequested = 1; } \
    طالما( 0 )

#إذا ( configUSE_PORT_OPTIMISED_TASK_SELECTION == 1 )

/* Generic helper function. */
    __attribute__( ( always_inline ) ) ساكن مضمن uint8_t uc_Port_کيراءن_Leading_Zeros( uint32_t ulBitmap )
    {
        uint8_t ucReturn;

        __asm متطاير ( "clz %0, %1" : "=r" ( ucReturn ) : "r" ( ulBitmap ) );

        أرجع ucReturn;
    }

/* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice.
    #endif

/* Store/clear the ready priorities in a bit map. */
    #define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

/*-----------------------------------------------------------*/

    #define portGET_HIGHEST_PRIORITY( ux_اتس_Priority, uxReadyPriorities )    ux_اتس_Priority = ( 31UL - ( uint32_t ) uc_Port_کيراءن_Leading_Zeros( ( uxReadyPriorities ) ) )

#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#ifdef __arch64__
    #define portBYTE_ALIGNMENT    8
#وإلا
    #define portBYTE_ALIGNMENT    4
#endif
#define port_تيندنن_GROWTH          ( -1 )
#define portTICK_PERIOD_MS        ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portNOP()    asm متطاير ( "NOP" )
#define portMEMORY_BARRIER()    asm متطاير ( "" ::: "memory" )
/*-----------------------------------------------------------*/

#إذا ( XPAR_MICROBLAZE_USE_تيندنن_PROTECTION )
    #define port_HAS_تيندنن_OVERFLOW_CHECKING    1
#endif
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/

/* The following structure is used by the FreeRTOS exception handler.  It is
 * filled with the MicroBlaze context as it was at the time the exception occurred.
 * This is done as an aid to debugging exception occurrences. */
تعريفنوع بنية PORT_REGISTER_DUMP
{
    /* The following structure members hold the values of the MicroBlaze
     * registers at the time the exception was raised. */
    UINTPTR ulR1_SP;
    UINTPTR ulR2_small_data_area;
    UINTPTR ulR3;
    UINTPTR ulR4;
    UINTPTR ulR5;
    UINTPTR ulR6;
    UINTPTR ulR7;
    UINTPTR ulR8;
    UINTPTR ulR9;
    UINTPTR ulR10;
    UINTPTR ulR11;
    UINTPTR ulR12;
    UINTPTR ulR13_read_write_small_data_area;
    UINTPTR ulR14_return_address_from_interrupt;
    UINTPTR ulR15_return_address_from_subroutine;
    UINTPTR ulR16_return_address_from_trap;
    UINTPTR ulR17_return_address_from_exceptions; /* The exception entry code will copy the BTR into R17 if the exception occurred in the delay slot of a branch instruction. */
    UINTPTR ulR18;
    UINTPTR ulR19;
    UINTPTR ulR20;
    UINTPTR ulR21;
    UINTPTR ulR22;
    UINTPTR ulR23;
    UINTPTR ulR24;
    UINTPTR ulR25;
    UINTPTR ulR26;
    UINTPTR ulR27;
    UINTPTR ulR28;
    UINTPTR ulR29;
    UINTPTR ulR30;
    UINTPTR ulR31;
    UINTPTR ulPC;
    UINTPTR ulESR;
    UINTPTR ulMSR;
    UINTPTR ulEAR;
    UINTPTR ulFSR;
    UINTPTR ulEDR;

    /* A human readable description of the exception cause.  The strings used
     * are the same as the #define constant names found in the
     * microblaze_exceptions_i.h header file */
    int8_t * pcExceptionCause;

    /* The human readable name of the task that was running at the time the
     * exception occurred.  This is the name that was given to the task when the
     * task was created using the FreeRTOS xTaskCreate() API function. */
    حرف * pcCurrentTaskName;

    /* The handle of the task that was running a the time the exception
     * occurred. */
    فراغ * xCurrentTaskHandle;
} xPortRegisterDump;


/*
 * Installs pxHandler as the interrupt handler for the peripheral specified by
 * the ucInterruptID parameter.
 *
 * ucInterruptID:
 *
 * The ID of the peripheral that will have pxHandler assigned as its interrupt
 * handler.  Peripheral IDs are defined in the xparameters.h header file, which
 * is itself part of the BSP project.  For example, in the official demo
 * application for this port, xparameters.h defines the following IDs for the
 * four possible interrupt sources:
 *
 * XPAR_INTC_0_UARTLITE_1_VEC_ID  -  for the UARTlite peripheral.
 * XPAR_INTC_0_TMRCTR_0_VEC_ID    -  for the AXI Timer 0 peripheral.
 * XPAR_INTC_0_EMACLITE_0_VEC_ID  -  for the Ethernet lite peripheral.
 * XPAR_INTC_0_GPIO_1_VEC_ID      -  for the button inputs.
 *
 *
 * pxHandler:
 *
 * A pointer to the interrupt handler function itself.  This must be a void
 * function that takes a (void *) parameter.
 *
 *
 * pvCallBackRef:
 *
 * The parameter passed into the handler function.  In many cases this will not
 * be used and can be NULL.  Some times it is used to pass in a reference to
 * the peripheral instance variable, so it can be accessed from inside the
 * handler function.
 *
 *
 * pdPASS is returned if the function executes successfully.  Any other value
 * being returned indicates that the function did not execute correctly.
 */
BaseType_t xPortInstallInterruptHandler( uint8_t ucInterruptID,
                                         XInterruptHandler pxHandler,
                                         فراغ * pvCallBackRef );


/*
 * Enables the interrupt, within the interrupt controller, for the peripheral
 * specified by the ucInterruptID parameter.
 *
 * ucInterruptID:
 *
 * The ID of the peripheral that will have its interrupt enabled in the
 * interrupt controller.  Peripheral IDs are defined in the xparameters.h header
 * file, which is itself part of the BSP project.  For example, in the official
 * demo application for this port, xparameters.h defines the following IDs for
 * the four possible interrupt sources:
 *
 * XPAR_INTC_0_UARTLITE_1_VEC_ID  -  for the UARTlite peripheral.
 * XPAR_INTC_0_TMRCTR_0_VEC_ID    -  for the AXI Timer 0 peripheral.
 * XPAR_INTC_0_EMACLITE_0_VEC_ID  -  for the Ethernet lite peripheral.
 * XPAR_INTC_0_GPIO_1_VEC_ID      -  for the button inputs.
 *
 */
فراغ vPortEnableInterrupt( uint8_t ucInterruptID );

/*
 * Disables the interrupt, within the interrupt controller, for the peripheral
 * specified by the ucInterruptID parameter.
 *
 * ucInterruptID:
 *
 * The ID of the peripheral that will have its interrupt disabled in the
 * interrupt controller.  Peripheral IDs are defined in the xparameters.h header
 * file, which is itself part of the BSP project.  For example, in the official
 * demo application for this port, xparameters.h defines the following IDs for
 * the four possible interrupt sources:
 *
 * XPAR_INTC_0_UARTLITE_1_VEC_ID  -  for the UARTlite peripheral.
 * XPAR_INTC_0_TMRCTR_0_VEC_ID    -  for the AXI Timer 0 peripheral.
 * XPAR_INTC_0_EMACLITE_0_VEC_ID  -  for the Ethernet lite peripheral.
 * XPAR_INTC_0_GPIO_1_VEC_ID      -  for the button inputs.
 *
 */
فراغ vPortDisableInterrupt( uint8_t ucInterruptID );

/*
 * This is an application defined callback function used to install the tick
 * interrupt handler.  It is provided as an application callback because the
 * kernel will run on lots of different MicroBlaze and FPGA configurations - not
 * all of which will have the same timer peripherals defined or available.  This
 * example uses the AXI Timer 0.  If that is available on your hardware platform
 * then this example callback implementation should not require modification.
 * The name of the interrupt handler that should be installed is vPortTickISR(),
 * which the function below declares as an extern.
 */
فراغ vApplicationSetupTimerInterrupt( فراغ );

/*
 * This is an application defined callback function used to clear whichever
 * interrupt was installed by the vApplicationSetupTimerInterrupt() callback
 * function - in this case the interrupt generated by the AXI timer.  It is
 * provided as an application callback because the kernel will run on lots of
 * different MicroBlaze and FPGA configurations - not all of which will have the
 * same timer peripherals defined or available.  This example uses the AXI Timer 0.
 * If that is available on your hardware platform then this example callback
 * implementation should not require modification provided the example definition
 * of vApplicationSetupTimerInterrupt() is also not modified.
 */
فراغ vApplicationClearTimerInterrupt( فراغ );

/*
 * vPortExceptionsInstallHandlers() is only available when the MicroBlaze
 * is configured to include exception functionality, and
 * configINSTALL_EXCEPTION_HANDLERS is set to 1 in FreeRTOSConfig.h.
 *
 * vPortExceptionsInstallHandlers() installs the FreeRTOS exception handler
 * for every possible exception cause.
 *
 * vPortExceptionsInstallHandlers() can be called explicitly from application
 * code.  After that is done, the default FreeRTOS exception handler that will
 * have been installed can be replaced for any specific exception cause by using
 * the standard Xilinx library function microblaze_register_exception_handler().
 *
 * If vPortExceptionsInstallHandlers() is not called explicitly by the
 * application, it will be called automatically by the kernel the first time
 * xPortInstallInterruptHandler() is called.  At that time, any exception
 * handlers that may have already been installed will be replaced.
 *
 * See the description of vApplicationExceptionRegisterDump() for information
 * on the processing performed by the FreeRTOS exception handler.
 */
فراغ vPortExceptionsInstallHandlers( فراغ );

/*
 * The FreeRTOS exception handler fills an xPortRegisterDump structure (defined
 * in portmacro.h) with the MicroBlaze context, as it was at the time the
 * exception occurred.  The exception handler then calls
 * vApplicationExceptionRegisterDump(), passing in the completed
 * xPortRegisterDump structure as its parameter.
 *
 * The FreeRTOS kernel provides its own implementation of
 * vApplicationExceptionRegisterDump(), but the kernel provided implementation
 * is declared as being 'weak'.  The weak definition allows the application
 * writer to provide their own implementation, should they wish to use the
 * register dump information.  For example, an implementation could be provided
 * that wrote the register dump data to a display, or a UART port.
 */
فراغ vApplicationExceptionRegisterDump( xPortRegisterDump * xRegisterDump );


/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */