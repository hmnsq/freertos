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

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the MicroBlaze port.
*----------------------------------------------------------*/


/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Standard includes. */
#ضمن <string.h>

/* Hardware includes. */
#ضمن <xintc.h>
#ضمن <xintc_i.h>
#ضمن <xtmrctr.h>

#إذا ( configSUPPORT_DYNAMIC_ALLOCATION == 0 )
    #error configSUPPORT_DYNAMIC_ALLOCATION must be set to 1 to use this port.
#endif

/* Tasks are started with interrupts enabled. */
#define portINITIAL_MSR_STATE        ( ( مكدس_Type_t ) 0x02 )

/* Tasks are started with a critical section nesting of 0 - however prior
 * to the scheduler being commenced we don't want the critical nesting level
 * to reach zero, so it is initialised to a high value. */
#define port_INITIAL_NESTING_قيمة    ( 0xff )

/* Our hardware setup only uses one counter. */
#define portCOUNTER_0                0

/* The stack used by the ISR is filled with a known value to assist in
 * debugging. */
#define port_ISR_مكدس_FILL_قيمة     0x55555555

/* Counts the nesting depth of calls to portENTER_CRITICAL().  Each task
 * maintains its own count, so this variable is saved as part of the task
 * context. */
متطاير UBaseType_t uxCriticalNesting = port_INITIAL_NESTING_قيمة;

/* To limit the amount of stack required by each task, this port uses a
 * separate stack for interrupts. */
uint32_t * pulISRStack;

/*-----------------------------------------------------------*/

/*
 * Sets up the periodic ISR used for the RTOS tick.  This uses timer 0, but
 * could have alternatively used the watchdog timer or timer 1.
 */
ساكن فراغ prvSetupTimerInterrupt( فراغ );
/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been made.
 *
 * See the header file portable.h.
 */
مكدس_Type_t * px_Port_Initialise_مكدس( مكدس_Type_t * px_قمة_Of_مكدس,
                                     TaskFunction_t pxCode,
                                     فراغ * pvParameters )
{
    خارجي فراغ * _SDA2_BASE_;
    خارجي فراغ * _SDA_BASE_;
    ثابت uint32_t ulR2 = ( uint32_t ) &_SDA2_BASE_;
    ثابت uint32_t ulR13 = ( uint32_t ) &_SDA_BASE_;

    /* Place a few bytes of known values on the bottom of the stack.
     * This is essential for the Microblaze port and these lines must
     * not be omitted.  The parameter value will overwrite the
     * 0x22222222 value during the function prologue. */
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x11111111;
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x22222222;
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x33333333;
    px_قمة_Of_مكدس--;

    /* First stack an initial value for the critical section nesting.  This
     *  is initialised to zero as tasks are started with interrupts enabled. */
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x00; /* R0. */

    /* Place an initial value for all the general purpose registers. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) ulR2;         /* R2 - small data area. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x03;         /* R3. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x04;         /* R4. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) pvParameters; /* R5 contains the function call parameters. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x06;         /* R6. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x07;         /* R7. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x08;         /* R8. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x09;         /* R9. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x0a;         /* R10. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x0b;         /* R11. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x0c;         /* R12. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) ulR13;        /* R13 - small data read write area. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) pxCode;       /* R14. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x0f;         /* R15. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x10;         /* R16. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x11;         /* R17. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x12;         /* R18. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x13;         /* R19. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x14;         /* R20. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x15;         /* R21. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x16;         /* R22. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x17;         /* R23. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x18;         /* R24. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x19;         /* R25. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x1a;         /* R26. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x1b;         /* R27. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x1c;         /* R28. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x1d;         /* R29. */
    px_قمة_Of_مكدس--;
    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x1e;         /* R30. */
    px_قمة_Of_مكدس--;

    /* The MSR is stacked between R30 and R31. */
    *px_قمة_Of_مكدس = portINITIAL_MSR_STATE;
    px_قمة_Of_مكدس--;

    *px_قمة_Of_مكدس = ( مكدس_Type_t ) 0x1f; /* R31. */
    px_قمة_Of_مكدس--;

    /* Return a pointer to the top of the stack we have generated so this can
     * be stored in the task control block for the task. */
    إرجاع px_قمة_Of_مكدس;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( فراغ )
{
    خارجي فراغ( __FreeRTOS_interrupt_Handler )( فراغ );
    خارجي فراغ( vStartFirstTask )( فراغ );


    /* Setup the FreeRTOS interrupt handler.  Code copied from crt0.s. */
    asm متطاير ( "la r6, r0, __FreeRTOS_interrupt_handler        \n\t" \
                   "sw r6, r1, r0                                  \n\t" \
                   "lhu r7, r1, r0                                 \n\t" \
                   "shi r7, r0, 0x12                               \n\t" \
                   "shi r6, r0, 0x16 " );

    /* Setup the hardware to generate the tick.  Interrupts are disabled when
     * this function is called. */
    prvSetupTimerInterrupt();

    /* Allocate the stack to be used by the interrupt handler. */
    pulISRStack = ( uint32_t * ) pvPortMalloc( config_MINIMAL_مكدس_SIZE * حجم( مكدس_Type_t ) );

    /* Restore the context of the first task that is going to run. */
    إذا( pulISRStack != عدم )
    {
        /* Fill the ISR stack with a known value to facilitate debugging. */
        memset( pulISRStack, port_ISR_مكدس_FILL_قيمة, config_MINIMAL_مكدس_SIZE * حجم( مكدس_Type_t ) );
        pulISRStack += ( config_MINIMAL_مكدس_SIZE - 1 );

        /* Kick off the first task. */
        vStartFirstTask();
    }

    /* Should not get here as the tasks are now running! */
    إرجاع pdFALSE;
}
/*-----------------------------------------------------------*/

فراغ vPortEndScheduler( فراغ )
{
    /* Not implemented. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch called by portYIELD or taskYIELD.
 */
فراغ vPortYield( فراغ )
{
    خارجي فراغ VPortYieldASM( فراغ );

    /* Perform the context switch in a critical section to assure it is
     * not interrupted by the tick ISR.  It is not a problem to do this as
     * each task maintains its own interrupt status. */
    portENTER_CRITICAL();

    /* Jump directly to the yield function to ensure there is no
     * compiler generated prologue code. */
    asm متطاير ( "bralid r14, VPortYieldASM      \n\t" \
                   "or r0, r0, r0                  \n\t" );
    portEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
ساكن فراغ prvSetupTimerInterrupt( فراغ )
{
    XTmrCtr xTimer;
    ثابت uint32_t ul_Counter_قيمة = configCPU_CLOCK_HZ / configTICK_RATE_HZ;
    UBaseType_t uxMask;

    /* The OPB timer1 is used to generate the tick.  Use the provided library
     * functions to enable the timer and set the tick frequency. */
    XTmrCtr_mDisable( XPAR_OPB_TIMER_1_BASEADDR, XPAR_OPB_TIMER_1_DEVICE_ID );
    XTmrCtr_Initialize( &xTimer, XPAR_OPB_TIMER_1_DEVICE_ID );
    XTmrCtr_mSetLoadReg( XPAR_OPB_TIMER_1_BASEADDR, portCOUNTER_0, ul_Counter_قيمة );
    XTmrCtr_mSetControlStatusReg( XPAR_OPB_TIMER_1_BASEADDR, portCOUNTER_0, XTC_CSR_LOAD_MASK | XTC_CSR_INT_occurred_MASK );

    /* Set the timer interrupt enable bit while maintaining the other bit
     * states. */
    uxMask = XIntc_In32( ( XPAR_OPB_INTC_0_BASEADDR + XIN_IER_OFFSET ) );
    uxMask |= XPAR_OPB_TIMER_1_INTERRUPT_MASK;
    XIntc_Out32( ( XPAR_OPB_INTC_0_BASEADDR + XIN_IER_OFFSET ), ( uxMask ) );

    XTmrCtr_Start( &xTimer, XPAR_OPB_TIMER_1_DEVICE_ID );
    XTmrCtr_mSetControlStatusReg( XPAR_OPB_TIMER_1_BASEADDR, portCOUNTER_0, XTC_CSR_ENABLE_TMR_MASK | XTC_CSR_ENABLE_INT_MASK | XTC_CSR_AUTO_RELOAD_MASK | XTC_CSR_DOWN_تعداد_MASK | XTC_CSR_INT_occurred_MASK );
    XIntc_mAckIntr( XPAR_INTC_SINGLE_BASEADDR, 1 );
}
/*-----------------------------------------------------------*/

/*
 * The interrupt handler placed in the interrupt vector when the scheduler is
 * started.  The task context has already been saved when this is called.
 * This handler determines the interrupt source and calls the relevant
 * peripheral handler.
 */
فراغ vTaskISRHandler( فراغ )
{
    ساكن uint32_t ulPending;

    /* Which interrupts are pending? */
    ulPending = XIntc_In32( ( XPAR_INTC_SINGLE_BASEADDR + XIN_IVR_OFFSET ) );

    إذا( ulPending < XPAR_INTC_MAX_رقم_INTR_INPUTS )
    {
        ساكن XIntc_VectorTableEntry * pxTablePtr;
        ساكن XIntc_Config * pxConfig;
        ساكن uint32_t ulInterruptMask;

        ulInterruptMask = ( uint32_t ) 1 << ulPending;

        /* Get the configuration data using the device ID */
        pxConfig = &XIntc_ConfigTable[ ( uint32_t ) XPAR_INTC_SINGLE_DEVICE_ID ];

        pxTablePtr = &( pxConfig->HandlerTable[ ulPending ] );

        إذا( pxConfig->AckBeforeService & ( ulInterruptMask ) )
        {
            XIntc_mAckIntr( pxConfig->BaseAddress, ulInterruptMask );
            pxTablePtr->Handler( pxTablePtr->CallBackRef );
        }
        وإلا
        {
            pxTablePtr->Handler( pxTablePtr->CallBackRef );
            XIntc_mAckIntr( pxConfig->BaseAddress, ulInterruptMask );
        }
    }
}
/*-----------------------------------------------------------*/

/*
 * Handler for the timer interrupt.
 */
فراغ vTickISR( فراغ * pvBaseAddress )
{
    uint32_t ulCSR;

    /* Increment the RTOS tick - this might cause a task to unblock. */
    إذا( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the timer interrupt */
    ulCSR = XTmrCtr_mGetControlStatusReg( XPAR_OPB_TIMER_1_BASEADDR, 0 );
    XTmrCtr_mSetControlStatusReg( XPAR_OPB_TIMER_1_BASEADDR, portCOUNTER_0, ulCSR );
}
/*-----------------------------------------------------------*/
