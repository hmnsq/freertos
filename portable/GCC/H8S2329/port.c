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

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"


/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the H8S port.
*----------------------------------------------------------*/


/*-----------------------------------------------------------*/

/* When the task starts interrupts should be enabled. */
#define portINITIAL_CCR                    ( ( ರಾಶಿ_Type_t ) 0x00 )

/* Hardware specific constants used to generate the RTOS tick from the TPU. */
#define portCLEAR_ON_TGRA_COMPARE_MATCH    ( ( uint8_t ) 0x20 )
#define portCLOCK_DIV_64                   ( ( uint8_t ) 0x03 )
#define portCLOCK_DIV                      ( ( uint32_t ) 64 )
#define portTGRA_INTERRUPT_ENABLE          ( ( uint8_t ) 0x01 )
#define portTIMER_CHANNEL                  ( ( uint8_t ) 0x02 )
#define portMSTP13                         ( ( uint16_t ) 0x2000 )

/*
 * Setup TPU channel one for the RTOS tick at the requested frequency.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvSetupTimerInterrupt( ಶೂನ್ಯ );

/*
 * The ISR used by portYIELD(). This is installed as a trap handler.
 */
ಶೂನ್ಯ vPortYield( ಶೂನ್ಯ ) __attribute__( ( saveall, interrupt_handler ) );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t * px_Port_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_Of_ರಾಶಿ,
                                     TaskFunction_t pxCode,
                                     ಶೂನ್ಯ * pvParameters )
{
    uint32_t ul_ಮೌಲ್ಯ;

    /* This requires an even address. */
    ul_ಮೌಲ್ಯ = ( uint32_t ) px_ತುದಿ_Of_ರಾಶಿ;

    ಯದಿ( ul_ಮೌಲ್ಯ & 1UL )
    {
        px_ತುದಿ_Of_ರಾಶಿ = px_ತುದಿ_Of_ರಾಶಿ - 1;
    }

    /* Place a few bytes of known values on the bottom of the stack.
     * This is just useful for debugging. */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0xaa;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0xbb;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0xcc;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0xdd;

    /* The initial stack mimics an interrupt stack.  First there is the program
     * counter (24 bits). */
    ul_ಮೌಲ್ಯ = ( uint32_t ) pxCode;

    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ( ul_ಮೌಲ್ಯ & 0xff );
    px_ತುದಿ_Of_ರಾಶಿ--;
    ul_ಮೌಲ್ಯ >>= 8UL;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ( ul_ಮೌಲ್ಯ & 0xff );
    px_ತುದಿ_Of_ರಾಶಿ--;
    ul_ಮೌಲ್ಯ >>= 8UL;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ( ul_ಮೌಲ್ಯ & 0xff );

    /* Followed by the CCR. */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = portINITIAL_CCR;

    /* Next all the general purpose registers - with the parameters being passed
     * in ER0.  The parameter order must match that used by the compiler when the
     * "saveall" function attribute is used. */

    /* ER6 */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x66;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x66;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x66;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x66;

    /* ER0 */
    ul_ಮೌಲ್ಯ = ( uint32_t ) pvParameters;

    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ( ul_ಮೌಲ್ಯ & 0xff );
    px_ತುದಿ_Of_ರಾಶಿ--;
    ul_ಮೌಲ್ಯ >>= 8UL;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ( ul_ಮೌಲ್ಯ & 0xff );
    px_ತುದಿ_Of_ರಾಶಿ--;
    ul_ಮೌಲ್ಯ >>= 8UL;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ( ul_ಮೌಲ್ಯ & 0xff );
    px_ತುದಿ_Of_ರಾಶಿ--;
    ul_ಮೌಲ್ಯ >>= 8UL;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ( ul_ಮೌಲ್ಯ & 0xff );

    /* ER1 */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x11;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x11;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x11;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x11;

    /* ER2 */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x22;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x22;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x22;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x22;

    /* ER3 */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x33;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x33;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x33;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x33;

    /* ER4 */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x44;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x44;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x44;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x44;

    /* ER5 */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x55;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x55;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x55;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = 0x55;

    ಪ್ರತ್ಯಾಗಮ px_ತುದಿ_Of_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( ಶೂನ್ಯ )
{
    ಬಾಹ್ಯ ಶೂನ್ಯ * pxCurrentTCB;

    /* Setup the hardware to generate the tick. */
    prvSetupTimerInterrupt();

    /* Restore the context of the first task that is going to run.  This
     * mirrors the function epilogue code generated by the compiler when the
     * "saveall" function attribute is used. */
    asm ಚಞ್ಚಲ (
        "MOV.L      @_pxCurrentTCB, ER6         \n\t"
        "MOV.L      @ER6, ER7                   \n\t"
        "LDM.L      @SP+, (ER4-ER5)             \n\t"
        "LDM.L      @SP+, (ER0-ER3)             \n\t"
        "MOV.L      @ER7+, ER6                  \n\t"
        "RTE                                    \n\t"
        );

    ( ಶೂನ್ಯ ) pxCurrentTCB;

    /* Should not get here. */
    ಪ್ರತ್ಯಾಗಮ pdTRUE;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortEndScheduler( ಶೂನ್ಯ )
{
    /* It is unlikely that the h8 port will get stopped. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch.  This is a trap handler.  The "saveall" function
 * attribute is used so the context is saved by the compiler prologue.  All
 * we have to do is save the stack pointer.
 */
ಶೂನ್ಯ vPortYield( ಶೂನ್ಯ )
{
    port_SAVE_ರಾಶಿ_POINTER();
    vTaskSwitchContext();
    port_RESTORE_ರಾಶಿ_POINTER();
}
/*-----------------------------------------------------------*/

/*
 * The interrupt handler installed for the RTOS tick depends on whether the
 * preemptive or cooperative scheduler is being used.
 */
#ಯದಿ ( configUSE_PREEMPTION == 1 )

/*
 * The preemptive scheduler is used so the ISR calls vTaskSwitchContext().
 * The function prologue saves the context so all we have to do is save
 * the stack pointer.
 */
    ಶೂನ್ಯ vTickISR( ಶೂನ್ಯ ) __attribute__( ( saveall, interrupt_handler ) );
    ಶೂನ್ಯ vTickISR( ಶೂನ್ಯ )
    {
        port_SAVE_ರಾಶಿ_POINTER();

        ಯದಿ( xTaskIncrementTick() != pdFALSE )
        {
            vTaskSwitchContext();
        }

        /* Clear the interrupt. */
        TSR1 &= ~0x01;

        port_RESTORE_ರಾಶಿ_POINTER();
    }

#ಅನ್ಯಥಾ /* if ( configUSE_PREEMPTION == 1 ) */

/*
 * The cooperative scheduler is being used so all we have to do is
 * periodically increment the tick.  This can just be a normal ISR and
 * the "saveall" attribute is not required.
 */
    ಶೂನ್ಯ vTickISR( ಶೂನ್ಯ ) __attribute__( ( interrupt_handler ) );
    ಶೂನ್ಯ vTickISR( ಶೂನ್ಯ )
    {
        xTaskIncrementTick();

        /* Clear the interrupt. */
        TSR1 &= ~0x01;
    }

#endif /* if ( configUSE_PREEMPTION == 1 ) */
/*-----------------------------------------------------------*/

/*
 * Setup timer 1 compare match to generate a tick interrupt.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvSetupTimerInterrupt( ಶೂನ್ಯ )
{
    ಧ್ರುವ uint32_t ulCompareMatch = ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) / portCLOCK_DIV;

    /* Turn the module on. */
    MSTPCR &= ~portMSTP13;

    /* Configure timer 1. */
    TCR1 = portCLEAR_ON_TGRA_COMPARE_MATCH | portCLOCK_DIV_64;

    /* Configure the compare match value for a tick of configTICK_RATE_HZ. */
    TGR1A = ulCompareMatch;

    /* Start the timer and enable the interrupt - we can do this here as
     * interrupts are globally disabled when this function is called. */
    TIER1 |= portTGRA_INTERRUPT_ENABLE;
    TSTR |= portTIMER_CHANNEL;
}
/*-----------------------------------------------------------*/
