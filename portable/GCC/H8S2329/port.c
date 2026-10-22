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
#شامل "FreeRTOS.h"
#شامل "task.h"


/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the H8S port.
*----------------------------------------------------------*/


/*-----------------------------------------------------------*/

/* When the task starts interrupts should be enabled. */
#تعریف_کرو پورٹ_INITIAL_CCR                    ( ( ڈھیر_Type_t ) 0x00 )

/* Hardware specific constants used to generate the RTOS tick from the TPU. */
#تعریف_کرو پورٹ_CLEAR_ON_TGRA_COMPARE_مطابقت    ( ( uint8_t ) 0x20 )
#تعریف_کرو پورٹ_CLOCK_DIV_64                   ( ( uint8_t ) 0x03 )
#تعریف_کرو پورٹ_CLOCK_DIV                      ( ( uint32_t ) 64 )
#تعریف_کرو پورٹ_TGRA_مداخلت_ENABLE          ( ( uint8_t ) 0x01 )
#تعریف_کرو پورٹ_TIMER_CHANNEL                  ( ( uint8_t ) 0x02 )
#تعریف_کرو پورٹ_MSTP13                         ( ( uint16_t ) 0x2000 )

/*
 * Setup TPU channel one for the RTOS tick at the requested frequency.
 */
ساکن خالی prv_تیاری_Timer_مداخلت( خالی );

/*
 * The ISR used by portYIELD(). This is installed as a trap handler.
 */
خالی v_پورٹ_Yield( خالی ) __attribute__( ( saveall, مداخلت_handler ) );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters )
{
    uint32_t ul_قدر;

    /* This requires an even address. */
    ul_قدر = ( uint32_t ) px_چوٹی_کا_ڈھیر;

    اگر( ul_قدر & 1UL )
    {
        px_چوٹی_کا_ڈھیر = px_چوٹی_کا_ڈھیر - 1;
    }

    /* Place a few bytes of known values on the bottom of the stack.
     * This is just useful for debugging. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0xaa;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0xbb;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0xcc;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0xdd;

    /* The initial stack mimics an interrupt stack.  First there is the program
     * counter (24 bits). */
    ul_قدر = ( uint32_t ) px_رمز;

    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ( ul_قدر & 0xff );
    px_چوٹی_کا_ڈھیر--;
    ul_قدر >>= 8UL;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ( ul_قدر & 0xff );
    px_چوٹی_کا_ڈھیر--;
    ul_قدر >>= 8UL;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ( ul_قدر & 0xff );

    /* Followed by the CCR. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = پورٹ_INITIAL_CCR;

    /* Next all the general purpose registers - with the parameters being passed
     * in ER0.  The parameter order must match that used by the compiler when the
     * "saveall" function attribute is used. */

    /* ER6 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x66;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x66;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x66;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x66;

    /* ER0 */
    ul_قدر = ( uint32_t ) pvParameters;

    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ( ul_قدر & 0xff );
    px_چوٹی_کا_ڈھیر--;
    ul_قدر >>= 8UL;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ( ul_قدر & 0xff );
    px_چوٹی_کا_ڈھیر--;
    ul_قدر >>= 8UL;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ( ul_قدر & 0xff );
    px_چوٹی_کا_ڈھیر--;
    ul_قدر >>= 8UL;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ( ul_قدر & 0xff );

    /* ER1 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x11;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x11;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x11;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x11;

    /* ER2 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x22;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x22;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x22;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x22;

    /* ER3 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x33;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x33;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x33;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x33;

    /* ER4 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x44;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x44;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x44;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x44;

    /* ER5 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x55;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x55;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x55;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x55;

    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    خارجی خالی * pxCurrentTCB;

    /* Setup the hardware to generate the tick. */
    prv_تیاری_Timer_مداخلت();

    /* Restore the context of the first task that is going to run.  This
     * mirrors the function epilogue code generated by the compiler when the
     * "saveall" function attribute is used. */
    asm متلون (
        "MOV.L      @_pxCurrentTCB, ER6         \n\t"
        "MOV.L      @ER6, ER7                   \n\t"
        "LDM.L      @SP+, (ER4-ER5)             \n\t"
        "LDM.L      @SP+, (ER0-ER3)             \n\t"
        "MOV.L      @ER7+, ER6                  \n\t"
        "RTE                                    \n\t"
        );

    ( خالی ) pxCurrentTCB;

    /* Should not get here. */
    واپس pdTRUE;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* It is unlikely that the h8 port will get stopped. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch.  This is a trap handler.  The "saveall" function
 * attribute is used so the context is saved by the compiler prologue.  All
 * we have to do is save the stack pointer.
 */
خالی v_پورٹ_Yield( خالی )
{
    پورٹ_SAVE_ڈھیر_اشارہ_گر();
    vTaskSwitchContext();
    پورٹ_RESTORE_ڈھیر_اشارہ_گر();
}
/*-----------------------------------------------------------*/

/*
 * The interrupt handler installed for the RTOS tick depends on whether the
 * preemptive or cooperative scheduler is being used.
 */
#اگر ( configUSE_PREEMPTION == 1 )

/*
 * The preemptive scheduler is used so the ISR calls vTaskSwitchContext().
 * The function prologue saves the context so all we have to do is save
 * the stack pointer.
 */
    خالی vTickISR( خالی ) __attribute__( ( saveall, مداخلت_handler ) );
    خالی vTickISR( خالی )
    {
        پورٹ_SAVE_ڈھیر_اشارہ_گر();

        اگر( xTaskIncrementTick() != pdFALSE )
        {
            vTaskSwitchContext();
        }

        /* Clear the interrupt. */
        TSR1 &= ~0x01;

        پورٹ_RESTORE_ڈھیر_اشارہ_گر();
    }

#ورنہ /* if ( configUSE_PREEMPTION == 1 ) */

/*
 * The cooperative scheduler is being used so all we have to do is
 * periodically increment the tick.  This can just be a normal ISR and
 * the "saveall" attribute is not required.
 */
    خالی vTickISR( خالی ) __attribute__( ( مداخلت_handler ) );
    خالی vTickISR( خالی )
    {
        xTaskIncrementTick();

        /* Clear the interrupt. */
        TSR1 &= ~0x01;
    }

#اگر_ختم /* if ( configUSE_PREEMPTION == 1 ) */
/*-----------------------------------------------------------*/

/*
 * Setup timer 1 compare match to generate a tick interrupt.
 */
ساکن خالی prv_تیاری_Timer_مداخلت( خالی )
{
    ثابت uint32_t ul_Compare_مطابقت = ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ ) / پورٹ_CLOCK_DIV;

    /* Turn the module on. */
    MSTPCR &= ~پورٹ_MSTP13;

    /* Configure timer 1. */
    TCR1 = پورٹ_CLEAR_ON_TGRA_COMPARE_مطابقت | پورٹ_CLOCK_DIV_64;

    /* Configure the compare match value for a tick of configTICK_RATE_HZ. */
    TGR1A = ul_Compare_مطابقت;

    /* Start the timer and enable the interrupt - we can do this here as
     * interrupts are globally disabled when this function is called. */
    TIER1 |= پورٹ_TGRA_مداخلت_ENABLE;
    TSTR |= پورٹ_TIMER_CHANNEL;
}
/*-----------------------------------------------------------*/
