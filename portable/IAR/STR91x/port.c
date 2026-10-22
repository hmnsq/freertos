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
* Implementation of functions defined in portable.h for the ST STR91x ARM9
* port.
*----------------------------------------------------------*/

/* Library includes. */
#అన్తర్భావ "91x_lib.h"

/* Standard includes. */
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <assert.h>

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

#నిర్వచితం_కాకపోతే configUSE_WATCHDOG_TICK
    #దోషం configUSE_WATCHDOG_TICK must be సమితి గమ్యం either 1 or 0 లోపల FreeRTOSConfig.h గమ్యం use either the Watchdog or timer 2 గమ్యం generate the tick అంతరాయం respectively.
#అయితే_ముగింపు

/* Constants required to setup the initial stack. */
#నిర్వచితం_కాకపోతే నిరంతరం_TASK_లోపల_ARM_బహుళకం
    #నిర్వచించు పోర్టు_INITIAL_SPSR       ( ( దొంతర_Type_t ) 0x3f )      /* System mode, THUMB mode, interrupts enabled. */
#లేకపోతే
    #నిర్వచించు పోర్టు_INITIAL_SPSR       ( ( దొంతర_Type_t ) 0x1f )      /* System mode, ARM mode, interrupts enabled. */
#అయితే_ముగింపు

#నిర్వచించు పోర్టు_INSTRUCTION_కొలత       ( ( దొంతర_Type_t ) 4 )

/* Constants required to handle critical sections. */
#నిర్వచించు పోర్టు_NO_CRITICAL_NESTING    ( ( uint32_t ) 0 )

#నిర్వచితం_కాకపోతే నిరపేక్ష
    #నిర్వచించు నిరపేక్ష( x )    ( ( x ) > 0 ? ( x ) : -( x ) )
#అయితే_ముగింపు

/**
 * Toggle a led using the following algorithm:
 * if ( GPIO_ReadBit(GPIO9, GPIO_Pin_2) )
 * {
 *   GPIO_WriteBit( GPIO9, GPIO_Pin_2, Bit_RESET );
 * }
 * else
 * {
 *   GPIO_WriteBit( GPIO9, GPIO_Pin_2, Bit_RESET );
 * }
 *
 */
#నిర్వచించు TOGGLE_LED( పోర్టు, pin )                                           \
    ఒకవేళ( ( ( ( ( పోర్టు )->DR[ ( pin ) << 2 ] ) ) & ( pin ) ) != బిట్టు_RESET ) \
    {                                                                     \
        ( పోర్టు )->DR[ ( pin ) << 2 ] = 0x00;                              \
    }                                                                     \
    లేకపోతే                                                                  \
    {                                                                     \
        ( పోర్టు )->DR[ ( pin ) << 2 ] = ( pin );                           \
    }


/*-----------------------------------------------------------*/

/* Setup the watchdog to generate the tick interrupts. */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య );

/* ulCriticalNesting will get set to zero when the first task starts.  It
 * cannot be initialised to 0 as this will cause interrupts to be enabled
 * during the kernel initialisation process. */
uint32_t ulCriticalNesting = ( uint32_t ) 9999;

/* Tick interrupt routines for cooperative and preemptive operation
 * respectively.  The preemptive version is not defined as __irq as it is called
 * from an asm wrapper function. */
శూన్య WDG_IRQHandler( శూన్య );

/* VIC interrupt default handler. */
స్థిర శూన్య prvDefaultHandler( శూన్య );

#ఒకవేళ configUSE_WATCHDOG_TICK == 0
    /* Used to update the OCR timer register */
    స్థిర u16 s_n_Pulse_నిడివి;
#అయితే_ముగింపు

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See header file for description.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    దొంతర_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_శిఖరం_యొక్క_దొంతర;

    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_శిఖరం_యొక్క_దొంతర--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం + పోర్టు_INSTRUCTION_కొలత;
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xaaaaaaaa;    /* R14 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x12121212;    /* R12 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x11111111;    /* R11 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x10101010;    /* R10 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x09090909;    /* R9 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x08080808;    /* R8 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x07070707;    /* R7 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x06060606;    /* R6 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x05050505;    /* R5 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x04040404;    /* R4 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x03030303;    /* R3 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x02020202;    /* R2 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x01010101;    /* R1 */
    px_శిఖరం_యొక్క_దొంతర--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters; /* R0 */
    px_శిఖరం_యొక్క_దొంతర--;

    /* The status register is set for system mode, with interrupts enabled. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_INITIAL_SPSR;
    px_శిఖరం_యొక్క_దొంతర--;

    /* Interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_NO_CRITICAL_NESTING;

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    బాహ్య శూన్య v_పోర్టు_ప్రారంభం_మొదటి_Task( శూన్య );

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_అమరిక_Timer_అంతరాయం();

    /* Start the first task. */
    v_పోర్టు_ప్రారంభం_మొదటి_Task();

    /* Should not get here! */
    తిరిగి 0;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/* This function is called from an asm wrapper, so does not require the __irq
 * keyword. */
#ఒకవేళ configUSE_WATCHDOG_TICK == 1

    స్థిర శూన్య prv_కనుగొను_Factors( u32 n,
                                u16 * a,
                                u32 * b )
    {
        /* This function is copied from the ST STR7 library and is
         * copyright STMicroelectronics.  Reproduced with permission. */

        u32 b0;
        u16 a0;
        int32_t err, err_min = n;

        *a = a0 = ( ( n - 1 ) / 65536ul ) + 1;
        *b = b0 = n / *a;

        కొరకు( ; *a <= 256; ( *a )++ )
        {
            *b = n / *a;
            err = ( int32_t ) *a * ( int32_t ) *b - ( int32_t ) n;

            ఒకవేళ( నిరపేక్ష( err ) > ( *a / 2 ) )
            {
                ( *b )++;
                err = ( int32_t ) *a * ( int32_t ) *b - ( int32_t ) n;
            }

            ఒకవేళ( నిరపేక్ష( err ) < నిరపేక్ష( err_min ) )
            {
                err_min = err;
                a0 = *a;
                b0 = *b;

                ఒకవేళ( err == 0 )
                {
                    ఆపు;
                }
            }
        }

        *a = a0;
        *b = b0;
    }
    /*-----------------------------------------------------------*/

    స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
    {
        WDG_InitTypeDef xWdg;
        uint16_t a;
        uint32_t n = configCPU_PERIPH_HZ / config_TICK_రేటు_HZ, b;

        /* Configure the watchdog as a free running timer that generates a
         * periodic interrupt. */

        SCU_APBPeriphClockConfig( __WDG, ENABLE );
        WDG_DeInit();
        WDG_StructInit( &xWdg );
        prv_కనుగొను_Factors( n, &a, &b );
        xWdg.WDG_Prescaler = a - 1;
        xWdg.WDG_Preload = b - 1;
        WDG_Init( &xWdg );
        WDG_ITConfig( ENABLE );

        /* Configure the VIC for the WDG interrupt. */
        VIC_Config( WDG_ITLine, VIC_IRQ, 10 );
        VIC_ITCmd( WDG_ITLine, ENABLE );

        /* Install the default handlers for both VIC's. */
        VIC0->DVAR = ( uint32_t ) prvDefaultHandler;
        VIC1->DVAR = ( uint32_t ) prvDefaultHandler;

        WDG_Cmd( ENABLE );
    }
    /*-----------------------------------------------------------*/

    శూన్య WDG_IRQHandler( శూన్య )
    {
        {
            /* Increment the tick counter. */
            ఒకవేళ( xTaskIncrementTick() != pdFALSE )
            {
                /* Select a new task to execute. */
                vTaskSwitchContext();
            }

            /* Clear the interrupt in the watchdog. */
            WDG->SR &= ~0x0001;
        }
    }

#లేకపోతే /* if configUSE_WATCHDOG_TICK == 1 */

    స్థిర శూన్య prv_కనుగొను_Factors( u32 n,
                                u8 * a,
                                u16 * b )
    {
        /* This function is copied from the ST STR7 library and is
         * copyright STMicroelectronics.  Reproduced with permission. */

        u16 b0;
        u8 a0;
        int32_t err, err_min = n;


        *a = a0 = ( ( n - 1 ) / 256 ) + 1;
        *b = b0 = n / *a;

        కొరకు( ; *a <= 256; ( *a )++ )
        {
            *b = n / *a;
            err = ( int32_t ) *a * ( int32_t ) *b - ( int32_t ) n;

            ఒకవేళ( నిరపేక్ష( err ) > ( *a / 2 ) )
            {
                ( *b )++;
                err = ( int32_t ) *a * ( int32_t ) *b - ( int32_t ) n;
            }

            ఒకవేళ( నిరపేక్ష( err ) < నిరపేక్ష( err_min ) )
            {
                err_min = err;
                a0 = *a;
                b0 = *b;

                ఒకవేళ( err == 0 )
                {
                    ఆపు;
                }
            }
        }

        *a = a0;
        *b = b0;
    }
    /*-----------------------------------------------------------*/

    స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
    {
        uint8_t a;
        uint16_t b;
        uint32_t n = configCPU_PERIPH_HZ / config_TICK_రేటు_HZ;

        TIM_InitTypeDef timer;

        SCU_APBPeriphClockConfig( __TIM23, ENABLE );
        TIM_DeInit( TIM2 );
        TIM_StructInit( &timer );
        prv_కనుగొను_Factors( n, &a, &b );

        timer.TIM_బహుళకం = TIM_OCM_CHANNEL_1;
        timer.TIM_OC1_Modes = TIM_TIMING;
        timer.TIM_Clock_ఆధారం = TIM_CLK_APB;
        timer.TIM_Clock_అంచు = TIM_CLK_అంచు_RISING;
        timer.TIM_Prescaler = a - 1;
        timer.TIM_Pulse_Level_1 = TIM_ఎగువ;
        timer.TIM_Pulse_నిడివి_1 = s_n_Pulse_నిడివి = b - 1;

        TIM_Init( TIM2, &timer );
        TIM_ITConfig( TIM2, TIM_IT_OC1, ENABLE );
        /* Configure the VIC for the WDG interrupt. */
        VIC_Config( TIM2_ITLine, VIC_IRQ, 10 );
        VIC_ITCmd( TIM2_ITLine, ENABLE );

        /* Install the default handlers for both VIC's. */
        VIC0->DVAR = ( uint32_t ) prvDefaultHandler;
        VIC1->DVAR = ( uint32_t ) prvDefaultHandler;

        TIM_CounterCmd( TIM2, TIM_CLEAR );
        TIM_CounterCmd( TIM2, TIM_ప్రారంభం );
    }
    /*-----------------------------------------------------------*/

    శూన్య TIM2_IRQHandler( శూన్య )
    {
        /* Reset the timer counter to avoid overflow. */
        TIM2->OC1R += s_n_Pulse_నిడివి;

        /* Increment the tick counter. */
        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            /* Select a new task to run. */
            vTaskSwitchContext();
        }

        /* Clear the interrupt in the watchdog. */
        TIM2->SR &= ~TIM_FLAG_OC1;
    }

#అయితే_ముగింపు /* USE_WATCHDOG_TICK */

/*-----------------------------------------------------------*/

__arm __interwork శూన్య v_పోర్టు_Enter_Critical( శూన్య )
{
    /* Disable interrupts first! */
    పోర్టు_DISABLE_INTERRUPTS();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

__arm __interwork శూన్య v_పోర్టు_Exit_Critical( శూన్య )
{
    ఒకవేళ( ulCriticalNesting > పోర్టు_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
         * re-enabled. */
        ఒకవేళ( ulCriticalNesting == పోర్టు_NO_CRITICAL_NESTING )
        {
            పోర్టు_ENABLE_INTERRUPTS();
        }
    }
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prvDefaultHandler( శూన్య )
{
}
