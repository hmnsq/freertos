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
#تعریف_کن پورت_CHAR              حرف
#تعریف_کن پورت_FLOAT             عائم
#تعریف_کن پورت_DOUBLE            مزدوج
#تعریف_کن پورت_LONG              دراز
#تعریف_کن پورت_SHORT             کوتاه
#اگر_تعریف_شده __arch64__
    #تعریف_کن پورت_پشته_TYPE    size_t
    تعريفنوع uint64_t        UBaseType_t;
#وإلا
    #تعریف_کن پورت_پشته_TYPE    uint32_t
    تعريفنوع بیعلامت دراز   UBaseType_t;
#پایان_اگر
#تعریف_کن پورت_پایه_TYPE         دراز

تعريفنوع پورت_پشته_TYPE      پشته_Type_t;
تعريفنوع دراز                پایه_Type_t;


#إذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
    تعريفنوع uint16_t        TickType_t;
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

/* Interrupt control macros and functions. */
فراغ microblaze_disable_interrupts( فراغ );
فراغ microblaze_enable_interrupts( فراغ );
#تعریف_کن پورت_DISABLE_INTERRUPTS()    microblaze_disable_interrupts()
#تعریف_کن پورت_ENABLE_INTERRUPTS()     microblaze_enable_interrupts()
/*-----------------------------------------------------------*/

/* Critical section macros. */
فراغ v_پورت_Enter_Critical( فراغ );
فراغ v_پورت_Exit_Critical( فراغ );
#تعریف_کن پورت_ENTER_CRITICAL()                           \
    {                                                  \
        خارجي متطاير UBaseType_t uxCriticalNesting; \
        microblaze_disable_interrupts();               \
        uxCriticalNesting++;                           \
    }

#تعریف_کن پورت_EXIT_CRITICAL()                            \
    {                                                  \
        خارجي متطاير UBaseType_t uxCriticalNesting; \
        /* Interrupts are disabled, so we can */       \
        /* access the variable directly. */            \
        uxCriticalNesting--;                           \
        إذا( uxCriticalNesting == 0 )                   \
        {                                              \
            /* The nesting has unwound and we \
             * can enable interrupts again. */ \
            پورت_ENABLE_INTERRUPTS();           \
        }                                      \
    }

/*-----------------------------------------------------------*/

/* The yield macro maps directly to the vPortYield() function. */
فراغ v_پورت_Yield( فراغ );
#تعریف_کن پورت_YIELD()    v_پورت_Yield()

/* portYIELD_FROM_ISR() does not directly call vTaskSwitchContext(), but instead
 * sets a flag to say that a yield has been requested.  The interrupt exit code
 * then checks this flag, and calls vTaskSwitchContext() before restoring a task
 * context, if the flag is not false.  This is done to prevent multiple calls to
 * vTaskSwitchContext() being made from a single interrupt, as a single interrupt
 * can result in multiple peripherals being serviced. */
خارجي متطاير uint32_t ulTaskSwitchRequested;
#تعریف_کن پورت_YIELD_FROM_ISR( x )                              \
    افعل { إذا( ( x ) != pdFALSE ) ulTaskSwitchRequested = 1; } \
    طالما( 0 )

#إذا ( config_USE_پورت_OPTIMISED_TASK_SELECTION == 1 )

/* Generic helper function. */
    __attribute__( ( always_inline ) ) ساكن مضمن uint8_t uc_پورت_شمار_Leading_Zeros( uint32_t ulBitmap )
    {
        uint8_t ucReturn;

        __asm متطاير ( "clz %0, %1" : "=r" ( ucReturn ) : "r" ( ulBitmap ) );

        أرجع ucReturn;
    }

/* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #خطا config_USE_پورت_OPTIMISED_TASK_SELECTION can only be مجموعه مقصد 1 when configMAX_PRIORITIES is less than or equal مقصد 32.  It is very rare that a system requires بیشتر than 10 مقصد 15 difference priorities as tasks that share a اولویت will time برش.
    #پایان_اگر

/* Store/clear the ready priorities in a bit map. */
    #تعریف_کن پورت_رکورد_READY_اولویت( ux_اولویت, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_اولویت ) )
    #تعریف_کن پورت_RESET_READY_اولویت( ux_اولویت, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_اولویت ) )

/*-----------------------------------------------------------*/

    #تعریف_کن پورت_GET_HIGHEST_اولویت( ux_بالاترین_اولویت, uxReadyPriorities )    ux_بالاترین_اولویت = ( 31UL - ( uint32_t ) uc_پورت_شمار_Leading_Zeros( ( uxReadyPriorities ) ) )

#پایان_اگر /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#اگر_تعریف_شده __arch64__
    #تعریف_کن پورت_BYTE_ALIGNMENT    8
#وإلا
    #تعریف_کن پورت_BYTE_ALIGNMENT    4
#پایان_اگر
#تعریف_کن پورت_پشته_GROWTH          ( -1 )
#تعریف_کن پورت_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
#تعریف_کن پورت_NOP()    asm متطاير ( "NOP" )
#تعریف_کن پورت_حافظه_BARRIER()    asm متطاير ( "" ::: "memory" )
/*-----------------------------------------------------------*/

#إذا ( XPAR_MICROBLAZE_USE_پشته_PROTECTION )
    #تعریف_کن پورت_HAS_پشته_سرریز_CHECKING    1
#پایان_اگر
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/

/* The following structure is used by the FreeRTOS exception handler.  It is
 * filled with the MicroBlaze context as it was at the time the exception occurred.
 * This is done as an aid to debugging exception occurrences. */
تعريفنوع بنية پورت_ثبات_DUMP
{
    /* The following structure members hold the values of the MicroBlaze
     * registers at the time the exception was raised. */
    UINTPTR ulR1_SP;
    UINTPTR ul_R2_small_داده_area;
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
    UINTPTR ul_R13_read_write_small_داده_area;
    UINTPTR ul_R14_return_آدرس_from_وقفه;
    UINTPTR ul_R15_return_آدرس_from_subroutine;
    UINTPTR ul_R16_return_آدرس_from_trap;
    UINTPTR ul_R17_return_آدرس_from_exceptions; /* The exception entry code will copy the BTR into R17 if the exception occurred in the delay slot of a branch instruction. */
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
} x_پورت_ثبات_Dump;


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
پایه_Type_t x_پورت_Install_وقفه_Handler( uint8_t uc_وقفه_ID,
                                         XInterruptHandler pxHandler,
                                         فراغ * pv_Call_پشت_Ref );


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
فراغ v_پورت_Enable_وقفه( uint8_t uc_وقفه_ID );

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
فراغ v_پورت_Disable_وقفه( uint8_t uc_وقفه_ID );

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
فراغ v_Application_راهاندازی_Timer_وقفه( فراغ );

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
فراغ v_Application_Clear_Timer_وقفه( فراغ );

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
فراغ v_پورت_Exceptions_Install_Handlers( فراغ );

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
فراغ v_Application_Exception_ثبات_Dump( x_پورت_ثبات_Dump * x_ثبات_Dump );


/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */