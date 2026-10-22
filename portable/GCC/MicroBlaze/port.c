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
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* Standard includes. */
#ಅನ್ತರ್ಭಾವ <string.h>

/* Hardware includes. */
#ಅನ್ತರ್ಭಾವ <xintc.h>
#ಅನ್ತರ್ಭಾವ <xintc_i.h>
#ಅನ್ತರ್ಭಾವ <xtmrctr.h>

#ಆದರೆ ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 0 )
    #ದೋಷ config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ must be ಗಣ ಗಮ್ಯ 1 ಗಮ್ಯ use this ಪೋರ್ಟ್.
#ಆದರೆ_ಅಂತ್ಯ

/* Tasks are started with interrupts enabled. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_MSR_STATE        ( ( ರಾಶಿ_Type_t ) 0x02 )

/* Tasks are started with a critical section nesting of 0 - however prior
 * to the scheduler being commenced we don't want the critical nesting level
 * to reach zero, so it is initialised to a high value. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_NESTING_ಮೌಲ್ಯ    ( 0xff )

/* Our hardware setup only uses one counter. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_COUNTER_0                0

/* The stack used by the ISR is filled with a known value to assist in
 * debugging. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_ಮೌಲ್ಯ     0x55555555

/* Counts the nesting depth of calls to portENTER_CRITICAL().  Each task
 * maintains its own count, so this variable is saved as part of the task
 * context. */
ಅಸ್ಥಿರ UBaseType_t uxCriticalNesting = ಪೋರ್ಟ್_INITIAL_NESTING_ಮೌಲ್ಯ;

/* To limit the amount of stack required by each task, this port uses a
 * separate stack for interrupts. */
uint32_t * pulISRStack;

/*-----------------------------------------------------------*/

/*
 * Sets up the periodic ISR used for the RTOS tick.  This uses timer 0, but
 * could have alternatively used the watchdog timer or timer 1.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );
/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been made.
 *
 * See the header file portable.h.
 */
ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    ಬಾಹ್ಯ ಶೂನ್ಯ * SDA2_ತಳ;
    ಬಾಹ್ಯ ಶೂನ್ಯ * SDA_ತಳ;
    ಸ್ಥಿರಾಂಕ uint32_t ulR2 = ( uint32_t ) &SDA2_ತಳ;
    ಸ್ಥಿರಾಂಕ uint32_t ulR13 = ( uint32_t ) &SDA_ತಳ;

    /* Place a few bytes of known values on the bottom of the stack.
     * This is essential for the Microblaze port and these lines must
     * not be omitted.  The parameter value will overwrite the
     * 0x22222222 value during the function prologue. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x11111111;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x22222222;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x33333333;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* First stack an initial value for the critical section nesting.  This
     *  is initialised to zero as tasks are started with interrupts enabled. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x00; /* R0. */

    /* Place an initial value for all the general purpose registers. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ulR2;         /* R2 - small data area. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x03;         /* R3. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x04;         /* R4. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters; /* R5 contains the function call parameters. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x06;         /* R6. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x07;         /* R7. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x08;         /* R8. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x09;         /* R9. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x0a;         /* R10. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x0b;         /* R11. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x0c;         /* R12. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ulR13;        /* R13 - small data read write area. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ;       /* R14. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x0f;         /* R15. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x10;         /* R16. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x11;         /* R17. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x12;         /* R18. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x13;         /* R19. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x14;         /* R20. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x15;         /* R21. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x16;         /* R22. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x17;         /* R23. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x18;         /* R24. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x19;         /* R25. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x1a;         /* R26. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x1b;         /* R27. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x1c;         /* R28. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x1d;         /* R29. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x1e;         /* R30. */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* The MSR is stacked between R30 and R31. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_MSR_STATE;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x1f; /* R31. */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* Return a pointer to the top of the stack we have generated so this can
     * be stored in the task control block for the task. */
    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    ಬಾಹ್ಯ ಶೂನ್ಯ( __FreeRTOS_interrupt_Handler )( ಶೂನ್ಯ );
    ಬಾಹ್ಯ ಶೂನ್ಯ( v_ಆರಂಭ_ಮೊದಲ_Task )( ಶೂನ್ಯ );


    /* Setup the FreeRTOS interrupt handler.  Code copied from crt0.s. */
    asm ಅಸ್ಥಿರ ( "la r6, r0, __FreeRTOS_interrupt_handler        \n\t" \
                   "sw r6, r1, r0                                  \n\t" \
                   "lhu r7, r1, r0                                 \n\t" \
                   "shi r7, r0, 0x12                               \n\t" \
                   "shi r6, r0, 0x16 " );

    /* Setup the hardware to generate the tick.  Interrupts are disabled when
     * this function is called. */
    prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    /* Allocate the stack to be used by the interrupt handler. */
    pulISRStack = ( uint32_t * ) pv_ಪೋರ್ಟ್_Malloc( config_ಕನಿಷ್ಠತಮ_ರಾಶಿ_ಗಾತ್ರ * ಗಾತ್ರ( ರಾಶಿ_Type_t ) );

    /* Restore the context of the first task that is going to run. */
    ಆದರೆ( pulISRStack != ಖಾಲಿ )
    {
        /* Fill the ISR stack with a known value to facilitate debugging. */
        memset( pulISRStack, ಪೋರ್ಟ್_ISR_ರಾಶಿ_FILL_ಮೌಲ್ಯ, config_ಕನಿಷ್ಠತಮ_ರಾಶಿ_ಗಾತ್ರ * ಗಾತ್ರ( ರಾಶಿ_Type_t ) );
        pulISRStack += ( config_ಕನಿಷ್ಠತಮ_ರಾಶಿ_ಗಾತ್ರ - 1 );

        /* Kick off the first task. */
        v_ಆರಂಭ_ಮೊದಲ_Task();
    }

    /* Should not get here as the tasks are now running! */
    ಹಿಂತಿರುಗಿ pdFALSE;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch called by portYIELD or taskYIELD.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ )
{
    ಬಾಹ್ಯ ಶೂನ್ಯ VPortYieldASM( ಶೂನ್ಯ );

    /* Perform the context switch in a critical section to assure it is
     * not interrupted by the tick ISR.  It is not a problem to do this as
     * each task maintains its own interrupt status. */
    ಪೋರ್ಟ್_ENTER_CRITICAL();

    /* Jump directly to the yield function to ensure there is no
     * compiler generated prologue code. */
    asm ಅಸ್ಥಿರ ( "bralid r14, VPortYieldASM      \n\t" \
                   "or r0, r0, r0                  \n\t" );
    ಪೋರ್ಟ್_EXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    XTmrCtr xTimer;
    ಸ್ಥಿರಾಂಕ uint32_t ul_Counter_ಮೌಲ್ಯ = configCPU_CLOCK_HZ / config_TICK_ದರ_HZ;
    UBaseType_t ux_ಮುಖವಾಡ;

    /* The OPB timer1 is used to generate the tick.  Use the provided library
     * functions to enable the timer and set the tick frequency. */
    XTmrCtr_mDisable( XPAR_OPB_TIMER_1_BASEADDR, XPAR_OPB_TIMER_1_DEVICE_ID );
    XTmrCtr_Initialize( &xTimer, XPAR_OPB_TIMER_1_DEVICE_ID );
    XTmr_Ctr_m_ಗಣ_ತುಂಬು_Reg( XPAR_OPB_TIMER_1_BASEADDR, ಪೋರ್ಟ್_COUNTER_0, ul_Counter_ಮೌಲ್ಯ );
    XTmr_Ctr_m_ಗಣ_Control_ಸ್ಥಿತಿ_Reg( XPAR_OPB_TIMER_1_BASEADDR, ಪೋರ್ಟ್_COUNTER_0, XTC_CSR_ತುಂಬು_ಮುಖವಾಡ | XTC_CSR_INT_occurred_ಮುಖವಾಡ );

    /* Set the timer interrupt enable bit while maintaining the other bit
     * states. */
    ux_ಮುಖವಾಡ = XIntc_In32( ( XPAR_OPB_INTC_0_BASEADDR + XIN_IER_ಸ್ಥಾನಾಂತರ ) );
    ux_ಮುಖವಾಡ |= XPAR_OPB_TIMER_1_ಅಡಚಣೆ_ಮುಖವಾಡ;
    XIntc_Out32( ( XPAR_OPB_INTC_0_BASEADDR + XIN_IER_ಸ್ಥಾನಾಂತರ ), ( ux_ಮುಖವಾಡ ) );

    XTmr_Ctr_ಆರಂಭ( &xTimer, XPAR_OPB_TIMER_1_DEVICE_ID );
    XTmr_Ctr_m_ಗಣ_Control_ಸ್ಥಿತಿ_Reg( XPAR_OPB_TIMER_1_BASEADDR, ಪೋರ್ಟ್_COUNTER_0, XTC_CSR_ENABLE_TMR_ಮುಖವಾಡ | XTC_CSR_ENABLE_INT_ಮುಖವಾಡ | XTC_CSR_AUTO_RELOAD_ಮುಖವಾಡ | XTC_CSR_ಕೆಳಕ್ಕೆ_ಎಣಿಕೆ_ಮುಖವಾಡ | XTC_CSR_INT_occurred_ಮುಖವಾಡ );
    XIntc_mAckIntr( XPAR_INTC_SINGLE_BASEADDR, 1 );
}
/*-----------------------------------------------------------*/

/*
 * The interrupt handler placed in the interrupt vector when the scheduler is
 * started.  The task context has already been saved when this is called.
 * This handler determines the interrupt source and calls the relevant
 * peripheral handler.
 */
ಶೂನ್ಯ vTaskISRHandler( ಶೂನ್ಯ )
{
    ಸ್ಥಿರ uint32_t ulPending;

    /* Which interrupts are pending? */
    ulPending = XIntc_In32( ( XPAR_INTC_SINGLE_BASEADDR + XIN_IVR_ಸ್ಥಾನಾಂತರ ) );

    ಆದರೆ( ulPending < XPAR_INTC_MAX_ಅಂಕೆ_INTR_INPUTS )
    {
        ಸ್ಥಿರ XIntc_ಸದಿಶ_ಕೋಷ್ಟಕ_ನಮೂದು * px_ಕೋಷ್ಟಕ_Ptr;
        ಸ್ಥಿರ XIntc_Config * pxConfig;
        ಸ್ಥಿರ uint32_t ul_ಅಡಚಣೆ_ಮುಖವಾಡ;

        ul_ಅಡಚಣೆ_ಮುಖವಾಡ = ( uint32_t ) 1 << ulPending;

        /* Get the configuration data using the device ID */
        pxConfig = &XIntc_Config_ಕೋಷ್ಟಕ[ ( uint32_t ) XPAR_INTC_SINGLE_DEVICE_ID ];

        px_ಕೋಷ್ಟಕ_Ptr = &( pxConfig->Handler_ಕೋಷ್ಟಕ[ ulPending ] );

        ಆದರೆ( pxConfig->AckBeforeService & ( ul_ಅಡಚಣೆ_ಮುಖವಾಡ ) )
        {
            XIntc_mAckIntr( pxConfig->ತಳ_ವಿಳಾಸ, ul_ಅಡಚಣೆ_ಮುಖವಾಡ );
            px_ಕೋಷ್ಟಕ_Ptr->Handler( px_ಕೋಷ್ಟಕ_Ptr->Call_ಹಿಂಭಾಗ_Ref );
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            px_ಕೋಷ್ಟಕ_Ptr->Handler( px_ಕೋಷ್ಟಕ_Ptr->Call_ಹಿಂಭಾಗ_Ref );
            XIntc_mAckIntr( pxConfig->ತಳ_ವಿಳಾಸ, ul_ಅಡಚಣೆ_ಮುಖವಾಡ );
        }
    }
}
/*-----------------------------------------------------------*/

/*
 * Handler for the timer interrupt.
 */
ಶೂನ್ಯ vTickISR( ಶೂನ್ಯ * pv_ತಳ_ವಿಳಾಸ )
{
    uint32_t ulCSR;

    /* Increment the RTOS tick - this might cause a task to unblock. */
    ಆದರೆ( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the timer interrupt */
    ulCSR = XTmr_Ctr_m_Get_Control_ಸ್ಥಿತಿ_Reg( XPAR_OPB_TIMER_1_BASEADDR, 0 );
    XTmr_Ctr_m_ಗಣ_Control_ಸ್ಥಿತಿ_Reg( XPAR_OPB_TIMER_1_BASEADDR, ಪೋರ್ಟ್_COUNTER_0, ulCSR );
}
/*-----------------------------------------------------------*/
