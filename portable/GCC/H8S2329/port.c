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
#ضمن "FreeRTOS.h"
#ضمن "task.h"


/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the H8S port.
*----------------------------------------------------------*/


/*-----------------------------------------------------------*/

/* When the task starts interrupts should be enabled. */
#تعریف_کړه پورټ_INITIAL_CCR                    ( ( ډېری_Type_t ) 0x00 )

/* Hardware specific constants used to generate the RTOS tick from the TPU. */
#تعریف_کړه پورټ_CLEAR_ON_TGRA_COMPARE_سمون    ( ( uint8_t ) 0x20 )
#تعریف_کړه پورټ_CLOCK_DIV_64                   ( ( uint8_t ) 0x03 )
#تعریف_کړه پورټ_CLOCK_DIV                      ( ( uint32_t ) 64 )
#تعریف_کړه پورټ_TGRA_مداخله_ENABLE          ( ( uint8_t ) 0x01 )
#تعریف_کړه پورټ_TIMER_CHANNEL                  ( ( uint8_t ) 0x02 )
#تعریف_کړه پورټ_MSTP13                         ( ( uint16_t ) 0x2000 )

/*
 * Setup TPU channel one for the RTOS tick at the requested frequency.
 */
ساكن فراغ prv_تیاری_Timer_مداخله( فراغ );

/*
 * The ISR used by portYIELD(). This is installed as a trap handler.
 */
فراغ v_پورټ_Yield( فراغ ) __attribute__( ( saveall, مداخله_handler ) );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                     TaskFunction_t px_کوډ,
                                     فراغ * pvParameters )
{
    uint32_t ul_ارزښت;

    /* This requires an even address. */
    ul_ارزښت = ( uint32_t ) px_سر_د_ډېری;

    إذا( ul_ارزښت & 1UL )
    {
        px_سر_د_ډېری = px_سر_د_ډېری - 1;
    }

    /* Place a few bytes of known values on the bottom of the stack.
     * This is just useful for debugging. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0xaa;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0xbb;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0xcc;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0xdd;

    /* The initial stack mimics an interrupt stack.  First there is the program
     * counter (24 bits). */
    ul_ارزښت = ( uint32_t ) px_کوډ;

    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) ( ul_ارزښت & 0xff );
    px_سر_د_ډېری--;
    ul_ارزښت >>= 8UL;
    *px_سر_د_ډېری = ( ډېری_Type_t ) ( ul_ارزښت & 0xff );
    px_سر_د_ډېری--;
    ul_ارزښت >>= 8UL;
    *px_سر_د_ډېری = ( ډېری_Type_t ) ( ul_ارزښت & 0xff );

    /* Followed by the CCR. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = پورټ_INITIAL_CCR;

    /* Next all the general purpose registers - with the parameters being passed
     * in ER0.  The parameter order must match that used by the compiler when the
     * "saveall" function attribute is used. */

    /* ER6 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x66;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x66;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x66;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x66;

    /* ER0 */
    ul_ارزښت = ( uint32_t ) pvParameters;

    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) ( ul_ارزښت & 0xff );
    px_سر_د_ډېری--;
    ul_ارزښت >>= 8UL;
    *px_سر_د_ډېری = ( ډېری_Type_t ) ( ul_ارزښت & 0xff );
    px_سر_د_ډېری--;
    ul_ارزښت >>= 8UL;
    *px_سر_د_ډېری = ( ډېری_Type_t ) ( ul_ارزښت & 0xff );
    px_سر_د_ډېری--;
    ul_ارزښت >>= 8UL;
    *px_سر_د_ډېری = ( ډېری_Type_t ) ( ul_ارزښت & 0xff );

    /* ER1 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x11;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x11;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x11;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x11;

    /* ER2 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x22;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x22;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x22;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x22;

    /* ER3 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x33;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x33;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x33;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x33;

    /* ER4 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x44;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x44;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x44;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x44;

    /* ER5 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x55;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x55;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x55;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x55;

    أرجع px_سر_د_ډېری;
}
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    خارجي فراغ * pxCurrentTCB;

    /* Setup the hardware to generate the tick. */
    prv_تیاری_Timer_مداخله();

    /* Restore the context of the first task that is going to run.  This
     * mirrors the function epilogue code generated by the compiler when the
     * "saveall" function attribute is used. */
    asm متطاير (
        "MOV.L      @_pxCurrentTCB, ER6         \n\t"
        "MOV.L      @ER6, ER7                   \n\t"
        "LDM.L      @SP+, (ER4-ER5)             \n\t"
        "LDM.L      @SP+, (ER0-ER3)             \n\t"
        "MOV.L      @ER7+, ER6                  \n\t"
        "RTE                                    \n\t"
        );

    ( فراغ ) pxCurrentTCB;

    /* Should not get here. */
    أرجع pdTRUE;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* It is unlikely that the h8 port will get stopped. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch.  This is a trap handler.  The "saveall" function
 * attribute is used so the context is saved by the compiler prologue.  All
 * we have to do is save the stack pointer.
 */
فراغ v_پورټ_Yield( فراغ )
{
    پورټ_SAVE_ډېری_اشاره_ګر();
    vTaskSwitchContext();
    پورټ_RESTORE_ډېری_اشاره_ګر();
}
/*-----------------------------------------------------------*/

/*
 * The interrupt handler installed for the RTOS tick depends on whether the
 * preemptive or cooperative scheduler is being used.
 */
#إذا ( configUSE_PREEMPTION == 1 )

/*
 * The preemptive scheduler is used so the ISR calls vTaskSwitchContext().
 * The function prologue saves the context so all we have to do is save
 * the stack pointer.
 */
    فراغ vTickISR( فراغ ) __attribute__( ( saveall, مداخله_handler ) );
    فراغ vTickISR( فراغ )
    {
        پورټ_SAVE_ډېری_اشاره_ګر();

        إذا( xTaskIncrementTick() != pdFALSE )
        {
            vTaskSwitchContext();
        }

        /* Clear the interrupt. */
        TSR1 &= ~0x01;

        پورټ_RESTORE_ډېری_اشاره_ګر();
    }

#وإلا /* if ( configUSE_PREEMPTION == 1 ) */

/*
 * The cooperative scheduler is being used so all we have to do is
 * periodically increment the tick.  This can just be a normal ISR and
 * the "saveall" attribute is not required.
 */
    فراغ vTickISR( فراغ ) __attribute__( ( مداخله_handler ) );
    فراغ vTickISR( فراغ )
    {
        xTaskIncrementTick();

        /* Clear the interrupt. */
        TSR1 &= ~0x01;
    }

#د_که_پای /* if ( configUSE_PREEMPTION == 1 ) */
/*-----------------------------------------------------------*/

/*
 * Setup timer 1 compare match to generate a tick interrupt.
 */
ساكن فراغ prv_تیاری_Timer_مداخله( فراغ )
{
    ثابت uint32_t ul_Compare_سمون = ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ ) / پورټ_CLOCK_DIV;

    /* Turn the module on. */
    MSTPCR &= ~پورټ_MSTP13;

    /* Configure timer 1. */
    TCR1 = پورټ_CLEAR_ON_TGRA_COMPARE_سمون | پورټ_CLOCK_DIV_64;

    /* Configure the compare match value for a tick of configTICK_RATE_HZ. */
    TGR1A = ul_Compare_سمون;

    /* Start the timer and enable the interrupt - we can do this here as
     * interrupts are globally disabled when this function is called. */
    TIER1 |= پورټ_TGRA_مداخله_ENABLE;
    TSTR |= پورټ_TIMER_CHANNEL;
}
/*-----------------------------------------------------------*/
