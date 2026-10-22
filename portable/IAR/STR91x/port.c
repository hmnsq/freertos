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
#ਅਨ੍ਤਰ੍ਭਾਵ "91x_lib.h"

/* Standard includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <assert.h>

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configUSE_WATCHDOG_TICK
    #ਗਲਤੀ configUSE_WATCHDOG_TICK must be ਸੈੱਟ ਮੰਜ਼ਿਲ either 1 or 0 ਵਿੱਚ_2 FreeRTOSConfig.h ਮੰਜ਼ਿਲ use either the Watchdog or timer 2 ਮੰਜ਼ਿਲ generate the tick ਰੁਕਾਵਟ respectively.
#ਜੇ_ਅੰਤ

/* Constants required to setup the initial stack. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ਲੜੀਵਾਰ_TASK_ਵਿੱਚ_ARM_ਬਹੁਲਕ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_SPSR       ( ( ਢੇਰ_Type_t ) 0x3f )      /* System mode, THUMB mode, interrupts enabled. */
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_SPSR       ( ( ਢੇਰ_Type_t ) 0x1f )      /* System mode, ARM mode, interrupts enabled. */
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INSTRUCTION_ਮਾਪ       ( ( ਢੇਰ_Type_t ) 4 )

/* Constants required to handle critical sections. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NO_CRITICAL_NESTING    ( ( uint32_t ) 0 )

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ਨਿਰਪੇਖ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਨਿਰਪੇਖ( x )    ( ( x ) > 0 ? ( x ) : -( x ) )
#ਜੇ_ਅੰਤ

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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TOGGLE_LED( ਪੋਰਟ, pin )                                           \
    ਜੇ( ( ( ( ( ਪੋਰਟ )->DR[ ( pin ) << 2 ] ) ) & ( pin ) ) != ਦੋਆਧਾਰੀ_ਅੰਕ_RESET ) \
    {                                                                     \
        ( ਪੋਰਟ )->DR[ ( pin ) << 2 ] = 0x00;                              \
    }                                                                     \
    ਨਹੀਂਤਾਂ                                                                  \
    {                                                                     \
        ( ਪੋਰਟ )->DR[ ( pin ) << 2 ] = ( pin );                           \
    }


/*-----------------------------------------------------------*/

/* Setup the watchdog to generate the tick interrupts. */
ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );

/* ulCriticalNesting will get set to zero when the first task starts.  It
 * cannot be initialised to 0 as this will cause interrupts to be enabled
 * during the kernel initialisation process. */
uint32_t ulCriticalNesting = ( uint32_t ) 9999;

/* Tick interrupt routines for cooperative and preemptive operation
 * respectively.  The preemptive version is not defined as __irq as it is called
 * from an asm wrapper function. */
ਖਾਲੀ WDG_IRQHandler( ਖਾਲੀ );

/* VIC interrupt default handler. */
ਸਥਿਰ ਖਾਲੀ prvDefaultHandler( ਖਾਲੀ );

#ਜੇ configUSE_WATCHDOG_TICK == 0
    /* Used to update the OCR timer register */
    ਸਥਿਰ u16 s_n_Pulse_ਲੰਮਾਈ;
#ਜੇ_ਅੰਤ

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See header file for description.
 */
ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    ਢੇਰ_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_ਸਿਖਰ_ਦਾ_ਢੇਰ;

    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ + ਪੋਰਟ_INSTRUCTION_ਮਾਪ;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0xaaaaaaaa;    /* R14 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x12121212;    /* R12 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x11111111;    /* R11 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x10101010;    /* R10 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x09090909;    /* R9 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x08080808;    /* R8 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x07070707;    /* R7 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x06060606;    /* R6 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x05050505;    /* R5 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x04040404;    /* R4 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x03030303;    /* R3 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x02020202;    /* R2 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x01010101;    /* R1 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters; /* R0 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* The status register is set for system mode, with interrupts enabled. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_INITIAL_SPSR;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* Interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_NO_CRITICAL_NESTING;

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task( ਖਾਲੀ );

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

    /* Start the first task. */
    v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();

    /* Should not get here! */
    ਵਾਪਸ 0;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/* This function is called from an asm wrapper, so does not require the __irq
 * keyword. */
#ਜੇ configUSE_WATCHDOG_TICK == 1

    ਸਥਿਰ ਖਾਲੀ prv_ਲੱਭੋ_Factors( u32 n,
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

        ਲਈ( ; *a <= 256; ( *a )++ )
        {
            *b = n / *a;
            err = ( int32_t ) *a * ( int32_t ) *b - ( int32_t ) n;

            ਜੇ( ਨਿਰਪੇਖ( err ) > ( *a / 2 ) )
            {
                ( *b )++;
                err = ( int32_t ) *a * ( int32_t ) *b - ( int32_t ) n;
            }

            ਜੇ( ਨਿਰਪੇਖ( err ) < ਨਿਰਪੇਖ( err_min ) )
            {
                err_min = err;
                a0 = *a;
                b0 = *b;

                ਜੇ( err == 0 )
                {
                    ਰੋਕੋ;
                }
            }
        }

        *a = a0;
        *b = b0;
    }
    /*-----------------------------------------------------------*/

    ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
    {
        WDG_InitTypeDef xWdg;
        uint16_t a;
        uint32_t n = configCPU_PERIPH_HZ / config_TICK_ਦਰ_HZ, b;

        /* Configure the watchdog as a free running timer that generates a
         * periodic interrupt. */

        SCU_APBPeriphClockConfig( __WDG, ENABLE );
        WDG_DeInit();
        WDG_StructInit( &xWdg );
        prv_ਲੱਭੋ_Factors( n, &a, &b );
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

    ਖਾਲੀ WDG_IRQHandler( ਖਾਲੀ )
    {
        {
            /* Increment the tick counter. */
            ਜੇ( xTaskIncrementTick() != pdFALSE )
            {
                /* Select a new task to execute. */
                vTaskSwitchContext();
            }

            /* Clear the interrupt in the watchdog. */
            WDG->SR &= ~0x0001;
        }
    }

#ਨਹੀਂਤਾਂ /* if configUSE_WATCHDOG_TICK == 1 */

    ਸਥਿਰ ਖਾਲੀ prv_ਲੱਭੋ_Factors( u32 n,
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

        ਲਈ( ; *a <= 256; ( *a )++ )
        {
            *b = n / *a;
            err = ( int32_t ) *a * ( int32_t ) *b - ( int32_t ) n;

            ਜੇ( ਨਿਰਪੇਖ( err ) > ( *a / 2 ) )
            {
                ( *b )++;
                err = ( int32_t ) *a * ( int32_t ) *b - ( int32_t ) n;
            }

            ਜੇ( ਨਿਰਪੇਖ( err ) < ਨਿਰਪੇਖ( err_min ) )
            {
                err_min = err;
                a0 = *a;
                b0 = *b;

                ਜੇ( err == 0 )
                {
                    ਰੋਕੋ;
                }
            }
        }

        *a = a0;
        *b = b0;
    }
    /*-----------------------------------------------------------*/

    ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
    {
        uint8_t a;
        uint16_t b;
        uint32_t n = configCPU_PERIPH_HZ / config_TICK_ਦਰ_HZ;

        TIM_InitTypeDef timer;

        SCU_APBPeriphClockConfig( __TIM23, ENABLE );
        TIM_DeInit( TIM2 );
        TIM_StructInit( &timer );
        prv_ਲੱਭੋ_Factors( n, &a, &b );

        timer.TIM_ਬਹੁਲਕ = TIM_OCM_CHANNEL_1;
        timer.TIM_OC1_Modes = TIM_TIMING;
        timer.TIM_Clock_ਸਰੋਤ = TIM_CLK_APB;
        timer.TIM_Clock_ਕਿਨਾਰਾ = TIM_CLK_ਕਿਨਾਰਾ_RISING;
        timer.TIM_Prescaler = a - 1;
        timer.TIM_Pulse_Level_1 = TIM_ਉੱਚਾ;
        timer.TIM_Pulse_ਲੰਮਾਈ_1 = s_n_Pulse_ਲੰਮਾਈ = b - 1;

        TIM_Init( TIM2, &timer );
        TIM_ITConfig( TIM2, TIM_IT_OC1, ENABLE );
        /* Configure the VIC for the WDG interrupt. */
        VIC_Config( TIM2_ITLine, VIC_IRQ, 10 );
        VIC_ITCmd( TIM2_ITLine, ENABLE );

        /* Install the default handlers for both VIC's. */
        VIC0->DVAR = ( uint32_t ) prvDefaultHandler;
        VIC1->DVAR = ( uint32_t ) prvDefaultHandler;

        TIM_CounterCmd( TIM2, TIM_CLEAR );
        TIM_CounterCmd( TIM2, TIM_ਸ਼ੁਰੂ );
    }
    /*-----------------------------------------------------------*/

    ਖਾਲੀ TIM2_IRQHandler( ਖਾਲੀ )
    {
        /* Reset the timer counter to avoid overflow. */
        TIM2->OC1R += s_n_Pulse_ਲੰਮਾਈ;

        /* Increment the tick counter. */
        ਜੇ( xTaskIncrementTick() != pdFALSE )
        {
            /* Select a new task to run. */
            vTaskSwitchContext();
        }

        /* Clear the interrupt in the watchdog. */
        TIM2->SR &= ~TIM_FLAG_OC1;
    }

#ਜੇ_ਅੰਤ /* USE_WATCHDOG_TICK */

/*-----------------------------------------------------------*/

__arm __interwork ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ )
{
    /* Disable interrupts first! */
    ਪੋਰਟ_DISABLE_INTERRUPTS();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

__arm __interwork ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ )
{
    ਜੇ( ulCriticalNesting > ਪੋਰਟ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
         * re-enabled. */
        ਜੇ( ulCriticalNesting == ਪੋਰਟ_NO_CRITICAL_NESTING )
        {
            ਪੋਰਟ_ENABLE_INTERRUPTS();
        }
    }
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prvDefaultHandler( ਖਾਲੀ )
{
}
