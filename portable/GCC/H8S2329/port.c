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
#تعریف_کن پورت_INITIAL_CCR                    ( ( پشته_Type_t ) 0x00 )

/* Hardware specific constants used to generate the RTOS tick from the TPU. */
#تعریف_کن پورت_CLEAR_ON_TGRA_COMPARE_تطابق    ( ( uint8_t ) 0x20 )
#تعریف_کن پورت_CLOCK_DIV_64                   ( ( uint8_t ) 0x03 )
#تعریف_کن پورت_CLOCK_DIV                      ( ( uint32_t ) 64 )
#تعریف_کن پورت_TGRA_وقفه_ENABLE          ( ( uint8_t ) 0x01 )
#تعریف_کن پورت_TIMER_CHANNEL                  ( ( uint8_t ) 0x02 )
#تعریف_کن پورت_MSTP13                         ( ( uint16_t ) 0x2000 )

/*
 * Setup TPU channel one for the RTOS tick at the requested frequency.
 */
ساكن فراغ prv_راهاندازی_Timer_وقفه( فراغ );

/*
 * The ISR used by portYIELD(). This is installed as a trap handler.
 */
فراغ v_پورت_Yield( فراغ ) __attribute__( ( saveall, وقفه_handler ) );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
پشته_Type_t * px_پورت_Initialise_پشته( پشته_Type_t * px_بالاترین_از_پشته,
                                     TaskFunction_t px_کد,
                                     فراغ * pvParameters )
{
    uint32_t ul_مقدار;

    /* This requires an even address. */
    ul_مقدار = ( uint32_t ) px_بالاترین_از_پشته;

    إذا( ul_مقدار & 1UL )
    {
        px_بالاترین_از_پشته = px_بالاترین_از_پشته - 1;
    }

    /* Place a few bytes of known values on the bottom of the stack.
     * This is just useful for debugging. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0xaa;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0xbb;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0xcc;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0xdd;

    /* The initial stack mimics an interrupt stack.  First there is the program
     * counter (24 bits). */
    ul_مقدار = ( uint32_t ) px_کد;

    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) ( ul_مقدار & 0xff );
    px_بالاترین_از_پشته--;
    ul_مقدار >>= 8UL;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) ( ul_مقدار & 0xff );
    px_بالاترین_از_پشته--;
    ul_مقدار >>= 8UL;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) ( ul_مقدار & 0xff );

    /* Followed by the CCR. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = پورت_INITIAL_CCR;

    /* Next all the general purpose registers - with the parameters being passed
     * in ER0.  The parameter order must match that used by the compiler when the
     * "saveall" function attribute is used. */

    /* ER6 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x66;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x66;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x66;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x66;

    /* ER0 */
    ul_مقدار = ( uint32_t ) pvParameters;

    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) ( ul_مقدار & 0xff );
    px_بالاترین_از_پشته--;
    ul_مقدار >>= 8UL;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) ( ul_مقدار & 0xff );
    px_بالاترین_از_پشته--;
    ul_مقدار >>= 8UL;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) ( ul_مقدار & 0xff );
    px_بالاترین_از_پشته--;
    ul_مقدار >>= 8UL;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) ( ul_مقدار & 0xff );

    /* ER1 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x11;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x11;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x11;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x11;

    /* ER2 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x22;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x22;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x22;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x22;

    /* ER3 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x33;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x33;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x33;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x33;

    /* ER4 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x44;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x44;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x44;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x44;

    /* ER5 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x55;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x55;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x55;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x55;

    أرجع px_بالاترین_از_پشته;
}
/*-----------------------------------------------------------*/

پایه_Type_t x_پورت_شروع_Scheduler( فراغ )
{
    خارجي فراغ * pxCurrentTCB;

    /* Setup the hardware to generate the tick. */
    prv_راهاندازی_Timer_وقفه();

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

فراغ v_پورت_انتها_Scheduler( فراغ )
{
    /* It is unlikely that the h8 port will get stopped. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch.  This is a trap handler.  The "saveall" function
 * attribute is used so the context is saved by the compiler prologue.  All
 * we have to do is save the stack pointer.
 */
فراغ v_پورت_Yield( فراغ )
{
    پورت_SAVE_پشته_اشاره_گر();
    vTaskSwitchContext();
    پورت_RESTORE_پشته_اشاره_گر();
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
    فراغ vTickISR( فراغ ) __attribute__( ( saveall, وقفه_handler ) );
    فراغ vTickISR( فراغ )
    {
        پورت_SAVE_پشته_اشاره_گر();

        إذا( xTaskIncrementTick() != pdFALSE )
        {
            vTaskSwitchContext();
        }

        /* Clear the interrupt. */
        TSR1 &= ~0x01;

        پورت_RESTORE_پشته_اشاره_گر();
    }

#وإلا /* if ( configUSE_PREEMPTION == 1 ) */

/*
 * The cooperative scheduler is being used so all we have to do is
 * periodically increment the tick.  This can just be a normal ISR and
 * the "saveall" attribute is not required.
 */
    فراغ vTickISR( فراغ ) __attribute__( ( وقفه_handler ) );
    فراغ vTickISR( فراغ )
    {
        xTaskIncrementTick();

        /* Clear the interrupt. */
        TSR1 &= ~0x01;
    }

#پایان_اگر /* if ( configUSE_PREEMPTION == 1 ) */
/*-----------------------------------------------------------*/

/*
 * Setup timer 1 compare match to generate a tick interrupt.
 */
ساكن فراغ prv_راهاندازی_Timer_وقفه( فراغ )
{
    ثابت uint32_t ul_Compare_تطابق = ( configCPU_CLOCK_HZ / config_TICK_نرخ_HZ ) / پورت_CLOCK_DIV;

    /* Turn the module on. */
    MSTPCR &= ~پورت_MSTP13;

    /* Configure timer 1. */
    TCR1 = پورت_CLEAR_ON_TGRA_COMPARE_تطابق | پورت_CLOCK_DIV_64;

    /* Configure the compare match value for a tick of configTICK_RATE_HZ. */
    TGR1A = ul_Compare_تطابق;

    /* Start the timer and enable the interrupt - we can do this here as
     * interrupts are globally disabled when this function is called. */
    TIER1 |= پورت_TGRA_وقفه_ENABLE;
    TSTR |= پورت_TIMER_CHANNEL;
}
/*-----------------------------------------------------------*/
