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

#اگر_غیر_تعریف_شدہ PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    خارجی "C" {
#اگر_ختم
/* *INDENT-ON* */

/* BSP includes. */
#شامل <mb_interface.h>
#شامل <xparameters.h>

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
#تعریف_کرو پورٹ_CHAR              حرف
#تعریف_کرو پورٹ_FLOAT             اعشاری
#تعریف_کرو پورٹ_DOUBLE            دوہرا
#تعریف_کرو پورٹ_LONG              طویل
#تعریف_کرو پورٹ_SHORT             مختصر
#اگر_تعریف_شدہ __arch64__
    #تعریف_کرو پورٹ_ڈھیر_TYPE    size_t
    قسمتعریف uint64_t        UBaseType_t;
#ورنہ
    #تعریف_کرو پورٹ_ڈھیر_TYPE    uint32_t
    قسمتعریف غیرعلامتی طویل   UBaseType_t;
#اگر_ختم
#تعریف_کرو پورٹ_بنیاد_TYPE         طویل

قسمتعریف پورٹ_ڈھیر_TYPE      ڈھیر_Type_t;
قسمتعریف طویل                بنیاد_Type_t;


#اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    قسمتعریف uint16_t        TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffff
#وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    قسمتعریف uint32_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
#ورنہ
    #غلطی config_TICK_TYPE_چوڑائی_اندر_بٹ سیٹ مقصد unsupported tick type چوڑائی.
#اگر_ختم
/*-----------------------------------------------------------*/

/* Interrupt control macros and functions. */
خالی microblaze_disable_interrupts( خالی );
خالی microblaze_enable_interrupts( خالی );
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    microblaze_disable_interrupts()
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     microblaze_enable_interrupts()
/*-----------------------------------------------------------*/

/* Critical section macros. */
خالی v_پورٹ_Enter_Critical( خالی );
خالی v_پورٹ_Exit_Critical( خالی );
#تعریف_کرو پورٹ_ENTER_CRITICAL()                           \
    {                                                  \
        خارجی متلون UBaseType_t uxCriticalNesting; \
        microblaze_disable_interrupts();               \
        uxCriticalNesting++;                           \
    }

#تعریف_کرو پورٹ_EXIT_CRITICAL()                            \
    {                                                  \
        خارجی متلون UBaseType_t uxCriticalNesting; \
        /* Interrupts are disabled, so we can */       \
        /* access the variable directly. */            \
        uxCriticalNesting--;                           \
        اگر( uxCriticalNesting == 0 )                   \
        {                                              \
            /* The nesting has unwound and we \
             * can enable interrupts again. */ \
            پورٹ_ENABLE_INTERRUPTS();           \
        }                                      \
    }

/*-----------------------------------------------------------*/

/* The yield macro maps directly to the vPortYield() function. */
خالی v_پورٹ_Yield( خالی );
#تعریف_کرو پورٹ_YIELD()    v_پورٹ_Yield()

/* portYIELD_FROM_ISR() does not directly call vTaskSwitchContext(), but instead
 * sets a flag to say that a yield has been requested.  The interrupt exit code
 * then checks this flag, and calls vTaskSwitchContext() before restoring a task
 * context, if the flag is not false.  This is done to prevent multiple calls to
 * vTaskSwitchContext() being made from a single interrupt, as a single interrupt
 * can result in multiple peripherals being serviced. */
خارجی متلون uint32_t ulTaskSwitchRequested;
#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )                              \
    کرو { اگر( ( x ) != pdFALSE ) ulTaskSwitchRequested = 1; } \
    جب( 0 )

#اگر ( config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1 )

/* Generic helper function. */
    __attribute__( ( always_inline ) ) ساکن اندرونی uint8_t uc_پورٹ_گنتی_Leading_Zeros( uint32_t ulBitmap )
    {
        uint8_t ucReturn;

        __asm متلون ( "clz %0, %1" : "=r" ( ucReturn ) : "r" ( ulBitmap ) );

        واپس ucReturn;
    }

/* Check the configuration. */
    #اگر ( configMAX_PRIORITIES > 32 )
        #غلطی config_USE_پورٹ_OPTIMISED_TASK_SELECTION can only be سیٹ مقصد 1 when configMAX_PRIORITIES is less than or equal مقصد 32.  It is very rare that a system requires مزید than 10 مقصد 15 difference priorities as tasks that share a ترجیح will time قاش.
    #اگر_ختم

/* Store/clear the ready priorities in a bit map. */
    #تعریف_کرو پورٹ_ریکارڈ_READY_ترجیح( ux_ترجیح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجیح ) )
    #تعریف_کرو پورٹ_RESET_READY_ترجیح( ux_ترجیح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجیح ) )

/*-----------------------------------------------------------*/

    #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities )    ux_چوٹی_ترجیح = ( 31UL - ( uint32_t ) uc_پورٹ_گنتی_Leading_Zeros( ( uxReadyPriorities ) ) )

#اگر_ختم /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#اگر_تعریف_شدہ __arch64__
    #تعریف_کرو پورٹ_BYTE_ALIGNMENT    8
#ورنہ
    #تعریف_کرو پورٹ_BYTE_ALIGNMENT    4
#اگر_ختم
#تعریف_کرو پورٹ_ڈھیر_GROWTH          ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_NOP()    asm متلون ( "NOP" )
#تعریف_کرو پورٹ_حافظہ_BARRIER()    asm متلون ( "" ::: "memory" )
/*-----------------------------------------------------------*/

#اگر ( XPAR_MICROBLAZE_USE_ڈھیر_PROTECTION )
    #تعریف_کرو پورٹ_HAS_ڈھیر_حد_سے_تجاوز_CHECKING    1
#اگر_ختم
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )
/*-----------------------------------------------------------*/

/* The following structure is used by the FreeRTOS exception handler.  It is
 * filled with the MicroBlaze context as it was at the time the exception occurred.
 * This is done as an aid to debugging exception occurrences. */
قسمتعریف ساخت پورٹ_رجسٹر_DUMP
{
    /* The following structure members hold the values of the MicroBlaze
     * registers at the time the exception was raised. */
    UINTPTR ulR1_SP;
    UINTPTR ul_R2_small_ڈیٹا_area;
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
    UINTPTR ul_R13_read_write_small_ڈیٹا_area;
    UINTPTR ul_R14_return_پتہ_from_مداخلت;
    UINTPTR ul_R15_return_پتہ_from_subroutine;
    UINTPTR ul_R16_return_پتہ_from_trap;
    UINTPTR ul_R17_return_پتہ_from_exceptions; /* The exception entry code will copy the BTR into R17 if the exception occurred in the delay slot of a branch instruction. */
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
    خالی * xCurrentTaskHandle;
} x_پورٹ_رجسٹر_Dump;


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
بنیاد_Type_t x_پورٹ_Install_مداخلت_Handler( uint8_t uc_مداخلت_ID,
                                         XInterruptHandler pxHandler,
                                         خالی * pv_Call_عقب_Ref );


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
خالی v_پورٹ_Enable_مداخلت( uint8_t uc_مداخلت_ID );

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
خالی v_پورٹ_Disable_مداخلت( uint8_t uc_مداخلت_ID );

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
خالی v_Application_تیاری_Timer_مداخلت( خالی );

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
خالی v_Application_Clear_Timer_مداخلت( خالی );

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
خالی v_پورٹ_Exceptions_Install_Handlers( خالی );

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
خالی v_Application_Exception_رجسٹر_Dump( x_پورٹ_رجسٹر_Dump * x_رجسٹر_Dump );


/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    }
#اگر_ختم
/* *INDENT-ON* */

#اگر_ختم /* PORTMACRO_H */