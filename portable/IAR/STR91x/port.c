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
#অন্তর্ভাব "91x_lib.h"

/* Standard includes. */
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <assert.h>

/* Scheduler includes. */
#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "task.h"

#ifndef configUSE_WATCHDOG_TICK
    #error configUSE_WATCHDOG_TICK must be set to either 1 or 0 in FreeRTOSConfig.h to use either the Watchdog or timer 2 to generate the tick interrupt respectively.
#endif

/* Constants required to setup the initial stack. */
#ifndef _RUN_TASK_IN_ARM_MODE_
    #define portINITIAL_SPSR       ( ( স্তূপ_Type_t ) 0x3f )      /* System mode, THUMB mode, interrupts enabled. */
#অন্যথা
    #define portINITIAL_SPSR       ( ( স্তূপ_Type_t ) 0x1f )      /* System mode, ARM mode, interrupts enabled. */
#endif

#define port_INSTRUCTION_আকার       ( ( স্তূপ_Type_t ) 4 )

/* Constants required to handle critical sections. */
#define portNO_CRITICAL_NESTING    ( ( uint32_t ) 0 )

#ifndef abs
    #define abs( x )    ( ( x ) > 0 ? ( x ) : -( x ) )
#endif

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
#define TOGGLE_LED( port, pin )                                           \
    যদি( ( ( ( ( port )->DR[ ( pin ) << 2 ] ) ) & ( pin ) ) != Bit_RESET ) \
    {                                                                     \
        ( port )->DR[ ( pin ) << 2 ] = 0x00;                              \
    }                                                                     \
    অন্যথা                                                                  \
    {                                                                     \
        ( port )->DR[ ( pin ) << 2 ] = ( pin );                           \
    }


/*-----------------------------------------------------------*/

/* Setup the watchdog to generate the tick interrupts. */
স্থির শূন্য prvSetupTimerInterrupt( শূন্য );

/* ulCriticalNesting will get set to zero when the first task starts.  It
 * cannot be initialised to 0 as this will cause interrupts to be enabled
 * during the kernel initialisation process. */
uint32_t ulCriticalNesting = ( uint32_t ) 9999;

/* Tick interrupt routines for cooperative and preemptive operation
 * respectively.  The preemptive version is not defined as __irq as it is called
 * from an asm wrapper function. */
শূন্য WDG_IRQHandler( শূন্য );

/* VIC interrupt default handler. */
স্থির শূন্য prvDefaultHandler( শূন্য );

#যদি configUSE_WATCHDOG_TICK == 0
    /* Used to update the OCR timer register */
    স্থির u16 s_n_Pulse_দৈর্ঘ্য;
#endif

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See header file for description.
 */
স্তূপ_Type_t * px_Port_Initialise_স্তূপ( স্তূপ_Type_t * px_শীর্ষ_Of_স্তূপ,
                                     TaskFunction_t pxCode,
                                     শূন্য * pvParameters )
{
    স্তূপ_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_শীর্ষ_Of_স্তূপ;

    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_শীর্ষ_Of_স্তূপ--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) pxCode + port_INSTRUCTION_আকার;
    px_শীর্ষ_Of_স্তূপ--;

    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0xaaaaaaaa;    /* R14 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x12121212;    /* R12 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x11111111;    /* R11 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x10101010;    /* R10 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x09090909;    /* R9 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x08080808;    /* R8 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x07070707;    /* R7 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x06060606;    /* R6 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x05050505;    /* R5 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x04040404;    /* R4 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x03030303;    /* R3 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x02020202;    /* R2 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x01010101;    /* R1 */
    px_শীর্ষ_Of_স্তূপ--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) pvParameters; /* R0 */
    px_শীর্ষ_Of_স্তূপ--;

    /* The status register is set for system mode, with interrupts enabled. */
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) portINITIAL_SPSR;
    px_শীর্ষ_Of_স্তূপ--;

    /* Interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_শীর্ষ_Of_স্তূপ = portNO_CRITICAL_NESTING;

    ফেরত px_শীর্ষ_Of_স্তূপ;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( শূন্য )
{
    বাহ্যিক শূন্য vPortStartFirstTask( শূন্য );

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prvSetupTimerInterrupt();

    /* Start the first task. */
    vPortStartFirstTask();

    /* Should not get here! */
    ফেরত 0;
}
/*-----------------------------------------------------------*/

শূন্য vPortEndScheduler( শূন্য )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/* This function is called from an asm wrapper, so does not require the __irq
 * keyword. */
#যদি configUSE_WATCHDOG_TICK == 1

    স্থির শূন্য prvFindFactors( u32 n,
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

        জন্য( ; *a <= 256; ( *a )++ )
        {
            *b = n / *a;
            err = ( int32_t ) *a * ( int32_t ) *b - ( int32_t ) n;

            যদি( abs( err ) > ( *a / 2 ) )
            {
                ( *b )++;
                err = ( int32_t ) *a * ( int32_t ) *b - ( int32_t ) n;
            }

            যদি( abs( err ) < abs( err_min ) )
            {
                err_min = err;
                a0 = *a;
                b0 = *b;

                যদি( err == 0 )
                {
                    বিরতি;
                }
            }
        }

        *a = a0;
        *b = b0;
    }
    /*-----------------------------------------------------------*/

    স্থির শূন্য prvSetupTimerInterrupt( শূন্য )
    {
        WDG_InitTypeDef xWdg;
        uint16_t a;
        uint32_t n = configCPU_PERIPH_HZ / configTICK_RATE_HZ, b;

        /* Configure the watchdog as a free running timer that generates a
         * periodic interrupt. */

        SCU_APBPeriphClockConfig( __WDG, ENABLE );
        WDG_DeInit();
        WDG_StructInit( &xWdg );
        prvFindFactors( n, &a, &b );
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

    শূন্য WDG_IRQHandler( শূন্য )
    {
        {
            /* Increment the tick counter. */
            যদি( xTaskIncrementTick() != pdFALSE )
            {
                /* Select a new task to execute. */
                vTaskSwitchContext();
            }

            /* Clear the interrupt in the watchdog. */
            WDG->SR &= ~0x0001;
        }
    }

#অন্যথা /* if configUSE_WATCHDOG_TICK == 1 */

    স্থির শূন্য prvFindFactors( u32 n,
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

        জন্য( ; *a <= 256; ( *a )++ )
        {
            *b = n / *a;
            err = ( int32_t ) *a * ( int32_t ) *b - ( int32_t ) n;

            যদি( abs( err ) > ( *a / 2 ) )
            {
                ( *b )++;
                err = ( int32_t ) *a * ( int32_t ) *b - ( int32_t ) n;
            }

            যদি( abs( err ) < abs( err_min ) )
            {
                err_min = err;
                a0 = *a;
                b0 = *b;

                যদি( err == 0 )
                {
                    বিরতি;
                }
            }
        }

        *a = a0;
        *b = b0;
    }
    /*-----------------------------------------------------------*/

    স্থির শূন্য prvSetupTimerInterrupt( শূন্য )
    {
        uint8_t a;
        uint16_t b;
        uint32_t n = configCPU_PERIPH_HZ / configTICK_RATE_HZ;

        TIM_InitTypeDef timer;

        SCU_APBPeriphClockConfig( __TIM23, ENABLE );
        TIM_DeInit( TIM2 );
        TIM_StructInit( &timer );
        prvFindFactors( n, &a, &b );

        timer.TIM_Mode = TIM_OCM_CHANNEL_1;
        timer.TIM_OC1_Modes = TIM_TIMING;
        timer.TIM_Clock_Source = TIM_CLK_APB;
        timer.TIM_Clock_Edge = TIM_CLK_EDGE_RISING;
        timer.TIM_Prescaler = a - 1;
        timer.TIM_Pulse_Level_1 = TIM_উপরের;
        timer.TIM_Pulse_দৈর্ঘ্য_1 = s_n_Pulse_দৈর্ঘ্য = b - 1;

        TIM_Init( TIM2, &timer );
        TIM_ITConfig( TIM2, TIM_IT_OC1, ENABLE );
        /* Configure the VIC for the WDG interrupt. */
        VIC_Config( TIM2_ITLine, VIC_IRQ, 10 );
        VIC_ITCmd( TIM2_ITLine, ENABLE );

        /* Install the default handlers for both VIC's. */
        VIC0->DVAR = ( uint32_t ) prvDefaultHandler;
        VIC1->DVAR = ( uint32_t ) prvDefaultHandler;

        TIM_গণক_Cmd( TIM2, TIM_CLEAR );
        TIM_গণক_Cmd( TIM2, TIM_START );
    }
    /*-----------------------------------------------------------*/

    শূন্য TIM2_IRQHandler( শূন্য )
    {
        /* Reset the timer counter to avoid overflow. */
        TIM2->OC1R += s_n_Pulse_দৈর্ঘ্য;

        /* Increment the tick counter. */
        যদি( xTaskIncrementTick() != pdFALSE )
        {
            /* Select a new task to run. */
            vTaskSwitchContext();
        }

        /* Clear the interrupt in the watchdog. */
        TIM2->SR &= ~TIM_FLAG_OC1;
    }

#endif /* USE_WATCHDOG_TICK */

/*-----------------------------------------------------------*/

__arm __interwork শূন্য vPortEnterCritical( শূন্য )
{
    /* Disable interrupts first! */
    portDISABLE_INTERRUPTS();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

__arm __interwork শূন্য vPortExitCritical( শূন্য )
{
    যদি( ulCriticalNesting > portNO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
         * re-enabled. */
        যদি( ulCriticalNesting == portNO_CRITICAL_NESTING )
        {
            portENABLE_INTERRUPTS();
        }
    }
}
/*-----------------------------------------------------------*/

স্থির শূন্য prvDefaultHandler( শূন্য )
{
}
