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

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    خارجي "C" {
#د_که_پای
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
#تعریف_کړه پورټ_CHAR          حرف
#تعریف_کړه پورټ_FLOAT         عائم
#تعریف_کړه پورټ_DOUBLE        مزدوج
#تعریف_کړه پورټ_LONG          اوږد
#تعریف_کړه پورټ_SHORT         لنډ
#تعریف_کړه پورټ_ډېری_TYPE    uint32_t
#تعریف_کړه پورټ_بنسټ_TYPE     اوږد

تعريفنوع پورټ_ډېری_TYPE   ډېری_Type_t;
تعريفنوع اوږد             بنسټ_Type_t;
تعريفنوع بینښه اوږد    UBaseType_t;

#إذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کړه پورټ_TICK_TYPE_IS_ATOMIC    1
#وإلا
    #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
#د_که_پای
/*-----------------------------------------------------------*/

/* Interrupt control macros and functions. */
فراغ microblaze_disable_interrupts( فراغ );
فراغ microblaze_enable_interrupts( فراغ );
#تعریف_کړه پورټ_DISABLE_INTERRUPTS()    microblaze_disable_interrupts()
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()     microblaze_enable_interrupts()
/*-----------------------------------------------------------*/

/* Critical section macros. */
فراغ v_پورټ_Enter_Critical( فراغ );
فراغ v_پورټ_Exit_Critical( فراغ );
#تعریف_کړه پورټ_ENTER_CRITICAL()                           \
    {                                                  \
        خارجي متطاير UBaseType_t uxCriticalNesting; \
        microblaze_disable_interrupts();               \
        uxCriticalNesting++;                           \
    }

#تعریف_کړه پورټ_EXIT_CRITICAL()                            \
    {                                                  \
        خارجي متطاير UBaseType_t uxCriticalNesting; \
        /* Interrupts are disabled, so we can */       \
        /* access the variable directly. */            \
        uxCriticalNesting--;                           \
        إذا( uxCriticalNesting == 0 )                   \
        {                                              \
            /* The nesting has unwound and we \
             * can enable interrupts again. */ \
            پورټ_ENABLE_INTERRUPTS();           \
        }                                      \
    }

/*-----------------------------------------------------------*/

/* The yield macro maps directly to the vPortYield() function. */
فراغ v_پورټ_Yield( فراغ );
#تعریف_کړه پورټ_YIELD()    v_پورټ_Yield()

/* portYIELD_FROM_ISR() does not directly call vTaskSwitchContext(), but instead
 * sets a flag to say that a yield has been requested.  The interrupt exit code
 * then checks this flag, and calls vTaskSwitchContext() before restoring a task
 * context, if the flag is not false.  This is done to prevent multiple calls to
 * vTaskSwitchContext() being made from a single interrupt, as a single interrupt
 * can result in multiple peripherals being serviced. */
خارجي متطاير uint32_t ulTaskSwitchRequested;
#تعریف_کړه پورټ_YIELD_FROM_ISR( x )                              \
    افعل { إذا( ( x ) != pdFALSE ) ulTaskSwitchRequested = 1; } \
    طالما( 0 )

#إذا ( config_USE_پورټ_OPTIMISED_TASK_SELECTION == 1 )

/* Generic helper function. */
    __attribute__( ( always_inline ) ) ساكن مضمن uint8_t uc_پورټ_شمېر_Leading_Zeros( uint32_t ulBitmap )
    {
        uint8_t ucReturn;

        __asm متطاير ( "clz %0, %1" : "=r" ( ucReturn ) : "r" ( ulBitmap ) );

        أرجع ucReturn;
    }

/* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #تېروتنه config_USE_پورټ_OPTIMISED_TASK_SELECTION can only be سېټ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires نور than 10 منزل 15 difference priorities as tasks that share a لومړیتوب will time ټوټه.
    #د_که_پای

/* Store/clear the ready priorities in a bit map. */
    #تعریف_کړه پورټ_ریکارډ_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_لومړیتوب ) )
    #تعریف_کړه پورټ_RESET_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_لومړیتوب ) )

/*-----------------------------------------------------------*/

    #تعریف_کړه پورټ_GET_HIGHEST_لومړیتوب( ux_سر_لومړیتوب, uxReadyPriorities )    ux_سر_لومړیتوب = ( 31UL - ( uint32_t ) uc_پورټ_شمېر_Leading_Zeros( ( uxReadyPriorities ) ) )

#د_که_پای /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کړه پورټ_BYTE_ALIGNMENT    4
#تعریف_کړه پورټ_ډېری_GROWTH      ( -1 )
#تعریف_کړه پورټ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کړه پورټ_NOP()               asm متطاير ( "NOP" )
#تعریف_کړه پورټ_حافظه_BARRIER()    asm متطاير ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/

/* The following structure is used by the FreeRTOS exception handler.  It is
 * filled with the MicroBlaze context as it was at the time the exception occurred.
 * This is done as an aid to debugging exception occurrences. */
تعريفنوع بنية پورټ_ثبتوونکی_DUMP
{
    /* The following structure members hold the values of the MicroBlaze
     * registers at the time the exception was raised. */
    uint32_t ulR1_SP;
    uint32_t ul_R2_small_معلومات_area;
    uint32_t ulR3;
    uint32_t ulR4;
    uint32_t ulR5;
    uint32_t ulR6;
    uint32_t ulR7;
    uint32_t ulR8;
    uint32_t ulR9;
    uint32_t ulR10;
    uint32_t ulR11;
    uint32_t ulR12;
    uint32_t ul_R13_read_write_small_معلومات_area;
    uint32_t ul_R14_return_پته_from_مداخله;
    uint32_t ul_R15_return_پته_from_subroutine;
    uint32_t ul_R16_return_پته_from_trap;
    uint32_t ul_R17_return_پته_from_exceptions; /* The exception entry code will copy the BTR into R17 if the exception occurred in the delay slot of a branch instruction. */
    uint32_t ulR18;
    uint32_t ulR19;
    uint32_t ulR20;
    uint32_t ulR21;
    uint32_t ulR22;
    uint32_t ulR23;
    uint32_t ulR24;
    uint32_t ulR25;
    uint32_t ulR26;
    uint32_t ulR27;
    uint32_t ulR28;
    uint32_t ulR29;
    uint32_t ulR30;
    uint32_t ulR31;
    uint32_t ulPC;
    uint32_t ulESR;
    uint32_t ulMSR;
    uint32_t ulEAR;
    uint32_t ulFSR;
    uint32_t ulEDR;

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
} x_پورټ_ثبتوونکی_Dump;


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
بنسټ_Type_t x_پورټ_Install_مداخله_Handler( uint8_t uc_مداخله_ID,
                                         XInterruptHandler pxHandler,
                                         فراغ * pv_Call_شا_Ref );


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
فراغ v_پورټ_Enable_مداخله( uint8_t uc_مداخله_ID );

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
فراغ v_پورټ_Disable_مداخله( uint8_t uc_مداخله_ID );

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
فراغ v_Application_تیاری_Timer_مداخله( فراغ );

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
فراغ v_Application_Clear_Timer_مداخله( فراغ );

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
فراغ v_پورټ_Exceptions_Install_Handlers( فراغ );

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
فراغ v_Application_Exception_ثبتوونکی_Dump( x_پورټ_ثبتوونکی_Dump * x_ثبتوونکی_Dump );


/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
