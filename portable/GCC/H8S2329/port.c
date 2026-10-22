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
#समावेश "FreeRTOS.h"
#समावेश "task.h"


/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the H8S port.
*----------------------------------------------------------*/


/*-----------------------------------------------------------*/

/* When the task starts interrupts should be enabled. */
#घोषणा portINITIAL_CCR                    ( ( ढेर_Type_t ) 0x00 )

/* Hardware specific constants used to generate the RTOS tick from the TPU. */
#घोषणा portCLEAR_ON_TGRA_COMPARE_MATCH    ( ( uint8_t ) 0x20 )
#घोषणा portCLOCK_DIV_64                   ( ( uint8_t ) 0x03 )
#घोषणा portCLOCK_DIV                      ( ( uint32_t ) 64 )
#घोषणा portTGRA_INTERRUPT_ENABLE          ( ( uint8_t ) 0x01 )
#घोषणा portTIMER_CHANNEL                  ( ( uint8_t ) 0x02 )
#घोषणा portMSTP13                         ( ( uint16_t ) 0x2000 )

/*
 * Setup TPU channel one for the RTOS tick at the requested frequency.
 */
अटल व्योम prvSetupTimerInterrupt( व्योम );

/*
 * The ISR used by portYIELD(). This is installed as a trap handler.
 */
व्योम vPortYield( व्योम ) __attribute__( ( saveall, interrupt_handler ) );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ढेर_Type_t * px_Port_Initialise_ढेर( ढेर_Type_t * px_शीर्ष_Of_ढेर,
                                     TaskFunction_t pxCode,
                                     व्योम * pvParameters )
{
    uint32_t ul_मूल्य;

    /* This requires an even address. */
    ul_मूल्य = ( uint32_t ) px_शीर्ष_Of_ढेर;

    अगर( ul_मूल्य & 1UL )
    {
        px_शीर्ष_Of_ढेर = px_शीर्ष_Of_ढेर - 1;
    }

    /* Place a few bytes of known values on the bottom of the stack.
     * This is just useful for debugging. */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0xaa;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0xbb;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0xcc;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0xdd;

    /* The initial stack mimics an interrupt stack.  First there is the program
     * counter (24 bits). */
    ul_मूल्य = ( uint32_t ) pxCode;

    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) ( ul_मूल्य & 0xff );
    px_शीर्ष_Of_ढेर--;
    ul_मूल्य >>= 8UL;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) ( ul_मूल्य & 0xff );
    px_शीर्ष_Of_ढेर--;
    ul_मूल्य >>= 8UL;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) ( ul_मूल्य & 0xff );

    /* Followed by the CCR. */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = portINITIAL_CCR;

    /* Next all the general purpose registers - with the parameters being passed
     * in ER0.  The parameter order must match that used by the compiler when the
     * "saveall" function attribute is used. */

    /* ER6 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x66;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x66;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x66;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x66;

    /* ER0 */
    ul_मूल्य = ( uint32_t ) pvParameters;

    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) ( ul_मूल्य & 0xff );
    px_शीर्ष_Of_ढेर--;
    ul_मूल्य >>= 8UL;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) ( ul_मूल्य & 0xff );
    px_शीर्ष_Of_ढेर--;
    ul_मूल्य >>= 8UL;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) ( ul_मूल्य & 0xff );
    px_शीर्ष_Of_ढेर--;
    ul_मूल्य >>= 8UL;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) ( ul_मूल्य & 0xff );

    /* ER1 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x11;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x11;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x11;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x11;

    /* ER2 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x22;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x22;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x22;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x22;

    /* ER3 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x33;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x33;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x33;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x33;

    /* ER4 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x44;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x44;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x44;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x44;

    /* ER5 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x55;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x55;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x55;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x55;

    वापस px_शीर्ष_Of_ढेर;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( व्योम )
{
    बाह्य व्योम * pxCurrentTCB;

    /* Setup the hardware to generate the tick. */
    prvSetupTimerInterrupt();

    /* Restore the context of the first task that is going to run.  This
     * mirrors the function epilogue code generated by the compiler when the
     * "saveall" function attribute is used. */
    यंत्र अस्थिर (
        "MOV.L      @_pxCurrentTCB, ER6         \n\t"
        "MOV.L      @ER6, ER7                   \n\t"
        "LDM.L      @SP+, (ER4-ER5)             \n\t"
        "LDM.L      @SP+, (ER0-ER3)             \n\t"
        "MOV.L      @ER7+, ER6                  \n\t"
        "RTE                                    \n\t"
        );

    ( व्योम ) pxCurrentTCB;

    /* Should not get here. */
    वापस pdTRUE;
}
/*-----------------------------------------------------------*/

व्योम vPortEndScheduler( व्योम )
{
    /* It is unlikely that the h8 port will get stopped. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch.  This is a trap handler.  The "saveall" function
 * attribute is used so the context is saved by the compiler prologue.  All
 * we have to do is save the stack pointer.
 */
व्योम vPortYield( व्योम )
{
    port_SAVE_ढेर_POINTER();
    vTaskSwitchContext();
    port_RESTORE_ढेर_POINTER();
}
/*-----------------------------------------------------------*/

/*
 * The interrupt handler installed for the RTOS tick depends on whether the
 * preemptive or cooperative scheduler is being used.
 */
#अगर ( configUSE_PREEMPTION == 1 )

/*
 * The preemptive scheduler is used so the ISR calls vTaskSwitchContext().
 * The function prologue saves the context so all we have to do is save
 * the stack pointer.
 */
    व्योम vTickISR( व्योम ) __attribute__( ( saveall, interrupt_handler ) );
    व्योम vTickISR( व्योम )
    {
        port_SAVE_ढेर_POINTER();

        अगर( xTaskIncrementTick() != pdFALSE )
        {
            vTaskSwitchContext();
        }

        /* Clear the interrupt. */
        TSR1 &= ~0x01;

        port_RESTORE_ढेर_POINTER();
    }

#अन्यथा /* if ( configUSE_PREEMPTION == 1 ) */

/*
 * The cooperative scheduler is being used so all we have to do is
 * periodically increment the tick.  This can just be a normal ISR and
 * the "saveall" attribute is not required.
 */
    व्योम vTickISR( व्योम ) __attribute__( ( interrupt_handler ) );
    व्योम vTickISR( व्योम )
    {
        xTaskIncrementTick();

        /* Clear the interrupt. */
        TSR1 &= ~0x01;
    }

#पूर्ण_अगर /* if ( configUSE_PREEMPTION == 1 ) */
/*-----------------------------------------------------------*/

/*
 * Setup timer 1 compare match to generate a tick interrupt.
 */
अटल व्योम prvSetupTimerInterrupt( व्योम )
{
    स्थिर uint32_t ulCompareMatch = ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) / portCLOCK_DIV;

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
