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

#यदि_अपरिभाषितम् PORTMACRO_H
#परिभाषय PORTMACRO_H

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    बाह्य "C" {
#यदि_अन्तः
/* *INDENT-ON* */

/* BSP includes. */
#अन्तर्भाव <mb_interface.h>
#अन्तर्भाव <xparameters.h>

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
#परिभाषय पत्तनम्_CHAR              वर्ण
#परिभाषय पत्तनम्_FLOAT             भिन्न
#परिभाषय पत्तनम्_DOUBLE            द्विगुण
#परिभाषय पत्तनम्_LONG              दीर्घ
#परिभाषय पत्तनम्_SHORT             ह्रस्व
#यदि_परिभाषितम् __arch64__
    #परिभाषय पत्तनम्_राशिः_TYPE    size_t
    प्रकारनिर्देश uint64_t        UBaseType_t;
#अन्यथा
    #परिभाषय पत्तनम्_राशिः_TYPE    uint32_t
    प्रकारनिर्देश अचिह्नित दीर्घ   UBaseType_t;
#यदि_अन्तः
#परिभाषय पत्तनम्_आधारः_TYPE         दीर्घ

प्रकारनिर्देश पत्तनम्_राशिः_TYPE      राशिः_Type_t;
प्रकारनिर्देश दीर्घ                आधारः_Type_t;


#यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
    प्रकारनिर्देश uint16_t        TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY              ( TickType_t ) 0xffff
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
    प्रकारनिर्देश uint32_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #परिभाषय पत्तनम्_TICK_TYPE_IS_ATOMIC    1
#अन्यथा
    #दोषः config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः समुच्चयः गन्तव्यम् unsupported tick type विस्तारः.
#यदि_अन्तः
/*-----------------------------------------------------------*/

/* Interrupt control macros and functions. */
शून्य microblaze_disable_interrupts( शून्य );
शून्य microblaze_enable_interrupts( शून्य );
#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()    microblaze_disable_interrupts()
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()     microblaze_enable_interrupts()
/*-----------------------------------------------------------*/

/* Critical section macros. */
शून्य v_पत्तनम्_Enter_Critical( शून्य );
शून्य v_पत्तनम्_Exit_Critical( शून्य );
#परिभाषय पत्तनम्_ENTER_CRITICAL()                           \
    {                                                  \
        बाह्य चञ्चल UBaseType_t uxCriticalNesting; \
        microblaze_disable_interrupts();               \
        uxCriticalNesting++;                           \
    }

#परिभाषय पत्तनम्_EXIT_CRITICAL()                            \
    {                                                  \
        बाह्य चञ्चल UBaseType_t uxCriticalNesting; \
        /* Interrupts are disabled, so we can */       \
        /* access the variable directly. */            \
        uxCriticalNesting--;                           \
        यदि( uxCriticalNesting == 0 )                   \
        {                                              \
            /* The nesting has unwound and we \
             * can enable interrupts again. */ \
            पत्तनम्_ENABLE_INTERRUPTS();           \
        }                                      \
    }

/*-----------------------------------------------------------*/

/* The yield macro maps directly to the vPortYield() function. */
शून्य v_पत्तनम्_Yield( शून्य );
#परिभाषय पत्तनम्_YIELD()    v_पत्तनम्_Yield()

/* portYIELD_FROM_ISR() does not directly call vTaskSwitchContext(), but instead
 * sets a flag to say that a yield has been requested.  The interrupt exit code
 * then checks this flag, and calls vTaskSwitchContext() before restoring a task
 * context, if the flag is not false.  This is done to prevent multiple calls to
 * vTaskSwitchContext() being made from a single interrupt, as a single interrupt
 * can result in multiple peripherals being serviced. */
बाह्य चञ्चल uint32_t ulTaskSwitchRequested;
#परिभाषय पत्तनम्_YIELD_FROM_ISR( x )                              \
    कुरु { यदि( ( x ) != pdFALSE ) ulTaskSwitchRequested = 1; } \
    यावत्( 0 )

#यदि ( config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION == 1 )

/* Generic helper function. */
    __attribute__( ( always_inline ) ) स्थिर अन्तःस्थ uint8_t uc_पत्तनम्_गणनम्_Leading_Zeros( uint32_t ulBitmap )
    {
        uint8_t ucReturn;

        __asm चञ्चल ( "clz %0, %1" : "=r" ( ucReturn ) : "r" ( ulBitmap ) );

        प्रत्यागम ucReturn;
    }

/* Check the configuration. */
    #यदि ( configMAX_PRIORITIES > 32 )
        #दोषः config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION can only be समुच्चयः गन्तव्यम् 1 when configMAX_PRIORITIES is less than or equal गन्तव्यम् 32.  It is very rare that a system requires अधिकम् than 10 गन्तव्यम् 15 difference priorities as tasks that share a प्राथमिकता will time खण्डिका.
    #यदि_अन्तः

/* Store/clear the ready priorities in a bit map. */
    #परिभाषय पत्तनम्_लेखः_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_प्राथमिकता ) )
    #परिभाषय पत्तनम्_RESET_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_प्राथमिकता ) )

/*-----------------------------------------------------------*/

    #परिभाषय पत्तनम्_GET_HIGHEST_प्राथमिकता( ux_शिखरम्_प्राथमिकता, uxReadyPriorities )    ux_शिखरम्_प्राथमिकता = ( 31UL - ( uint32_t ) uc_पत्तनम्_गणनम्_Leading_Zeros( ( uxReadyPriorities ) ) )

#यदि_अन्तः /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#यदि_परिभाषितम् __arch64__
    #परिभाषय पत्तनम्_BYTE_ALIGNMENT    8
#अन्यथा
    #परिभाषय पत्तनम्_BYTE_ALIGNMENT    4
#यदि_अन्तः
#परिभाषय पत्तनम्_राशिः_GROWTH          ( -1 )
#परिभाषय पत्तनम्_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
#परिभाषय पत्तनम्_NOP()    asm चञ्चल ( "NOP" )
#परिभाषय पत्तनम्_स्मृतिः_BARRIER()    asm चञ्चल ( "" ::: "memory" )
/*-----------------------------------------------------------*/

#यदि ( XPAR_MICROBLAZE_USE_राशिः_PROTECTION )
    #परिभाषय पत्तनम्_HAS_राशिः_अतिप्रवाहः_CHECKING    1
#यदि_अन्तः
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )
/*-----------------------------------------------------------*/

/* The following structure is used by the FreeRTOS exception handler.  It is
 * filled with the MicroBlaze context as it was at the time the exception occurred.
 * This is done as an aid to debugging exception occurrences. */
प्रकारनिर्देश संरचना पत्तनम्_पञ्जिकाकोशः_DUMP
{
    /* The following structure members hold the values of the MicroBlaze
     * registers at the time the exception was raised. */
    UINTPTR ulR1_SP;
    UINTPTR ul_R2_small_दत्त_area;
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
    UINTPTR ul_R13_read_write_small_दत्त_area;
    UINTPTR ul_R14_return_स्थानाङ्कः_from_व्यवधानम्;
    UINTPTR ul_R15_return_स्थानाङ्कः_from_subroutine;
    UINTPTR ul_R16_return_स्थानाङ्कः_from_trap;
    UINTPTR ul_R17_return_स्थानाङ्कः_from_exceptions; /* The exception entry code will copy the BTR into R17 if the exception occurred in the delay slot of a branch instruction. */
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
    वर्ण * pcCurrentTaskName;

    /* The handle of the task that was running a the time the exception
     * occurred. */
    शून्य * xCurrentTaskHandle;
} x_पत्तनम्_पञ्जिकाकोशः_Dump;


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
आधारः_Type_t x_पत्तनम्_Install_व्यवधानम्_Handler( uint8_t uc_व्यवधानम्_ID,
                                         XInterruptHandler pxHandler,
                                         शून्य * pv_Call_पृष्ठभागः_Ref );


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
शून्य v_पत्तनम्_Enable_व्यवधानम्( uint8_t uc_व्यवधानम्_ID );

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
शून्य v_पत्तनम्_Disable_व्यवधानम्( uint8_t uc_व्यवधानम्_ID );

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
शून्य v_Application_सज्जता_Timer_व्यवधानम्( शून्य );

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
शून्य v_Application_Clear_Timer_व्यवधानम्( शून्य );

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
शून्य v_पत्तनम्_Exceptions_Install_Handlers( शून्य );

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
शून्य v_Application_Exception_पञ्जिकाकोशः_Dump( x_पत्तनम्_पञ्जिकाकोशः_Dump * x_पञ्जिकाकोशः_Dump );


/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */