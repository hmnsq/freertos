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
#ضمن "91x_lib.h"

/* Standard includes. */
#ضمن <stdlib.h>
#ضمن <assert.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

#که_نه_تعریف_شوی configUSE_WATCHDOG_TICK
    #تېروتنه configUSE_WATCHDOG_TICK must be سېټ منزل either 1 or 0 دننه FreeRTOSConfig.h منزل use either the Watchdog or timer 2 منزل generate the tick مداخله respectively.
#د_که_پای

/* Constants required to setup the initial stack. */
#که_نه_تعریف_شوی پرلپسې_TASK_دننه_ARM_ډېرپېښ
    #تعریف_کړه پورټ_INITIAL_SPSR       ( ( ډېری_Type_t ) 0x3f )      /* System mode, THUMB mode, interrupts enabled. */
#وإلا
    #تعریف_کړه پورټ_INITIAL_SPSR       ( ( ډېری_Type_t ) 0x1f )      /* System mode, ARM mode, interrupts enabled. */
#د_که_پای

#تعریف_کړه پورټ_INSTRUCTION_اندازه       ( ( ډېری_Type_t ) 4 )

/* Constants required to handle critical sections. */
#تعریف_کړه پورټ_NO_CRITICAL_NESTING    ( ( uint32_t ) 0 )

#که_نه_تعریف_شوی مطلق_قیمت
    #تعریف_کړه مطلق_قیمت( x )    ( ( x ) > 0 ? ( x ) : -( x ) )
#د_که_پای

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
#تعریف_کړه TOGGLE_LED( پورټ, pin )                                           \
    إذا( ( ( ( ( پورټ )->DR[ ( pin ) << 2 ] ) ) & ( pin ) ) != بټ_RESET ) \
    {                                                                     \
        ( پورټ )->DR[ ( pin ) << 2 ] = 0x00;                              \
    }                                                                     \
    وإلا                                                                  \
    {                                                                     \
        ( پورټ )->DR[ ( pin ) << 2 ] = ( pin );                           \
    }


/*-----------------------------------------------------------*/

/* Setup the watchdog to generate the tick interrupts. */
ساكن فراغ prv_تیاری_Timer_مداخله( فراغ );

/* ulCriticalNesting will get set to zero when the first task starts.  It
 * cannot be initialised to 0 as this will cause interrupts to be enabled
 * during the kernel initialisation process. */
uint32_t ulCriticalNesting = ( uint32_t ) 9999;

/* Tick interrupt routines for cooperative and preemptive operation
 * respectively.  The preemptive version is not defined as __irq as it is called
 * from an asm wrapper function. */
فراغ WDG_IRQHandler( فراغ );

/* VIC interrupt default handler. */
ساكن فراغ prvDefaultHandler( فراغ );

#إذا configUSE_WATCHDOG_TICK == 0
    /* Used to update the OCR timer register */
    ساكن u16 s_n_Pulse_اوږدتیا;
#د_که_پای

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See header file for description.
 */
ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                     TaskFunction_t px_کوډ,
                                     فراغ * pvParameters )
{
    ډېری_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_سر_د_ډېری;

    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_سر_د_ډېری--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) px_کوډ + پورټ_INSTRUCTION_اندازه;
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = ( ډېری_Type_t ) 0xaaaaaaaa;    /* R14 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x12121212;    /* R12 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x11111111;    /* R11 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x10101010;    /* R10 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x09090909;    /* R9 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x08080808;    /* R8 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x07070707;    /* R7 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x06060606;    /* R6 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x05050505;    /* R5 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x04040404;    /* R4 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x03030303;    /* R3 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x02020202;    /* R2 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x01010101;    /* R1 */
    px_سر_د_ډېری--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters; /* R0 */
    px_سر_د_ډېری--;

    /* The status register is set for system mode, with interrupts enabled. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_INITIAL_SPSR;
    px_سر_د_ډېری--;

    /* Interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_سر_د_ډېری = پورټ_NO_CRITICAL_NESTING;

    أرجع px_سر_د_ډېری;
}
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    خارجي فراغ v_پورټ_پیل_لومړی_Task( فراغ );

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_تیاری_Timer_مداخله();

    /* Start the first task. */
    v_پورټ_پیل_لومړی_Task();

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/* This function is called from an asm wrapper, so does not require the __irq
 * keyword. */
#إذا configUSE_WATCHDOG_TICK == 1

    ساكن فراغ prv_پیدا_کړه_Factors( u32 n,
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

        لكل( ; *a <= 256; ( *a )++ )
        {
            *b = n / *a;
            err = ( int32_t ) *a * ( int32_t ) *b - ( int32_t ) n;

            إذا( مطلق_قیمت( err ) > ( *a / 2 ) )
            {
                ( *b )++;
                err = ( int32_t ) *a * ( int32_t ) *b - ( int32_t ) n;
            }

            إذا( مطلق_قیمت( err ) < مطلق_قیمت( err_min ) )
            {
                err_min = err;
                a0 = *a;
                b0 = *b;

                إذا( err == 0 )
                {
                    اكسر;
                }
            }
        }

        *a = a0;
        *b = b0;
    }
    /*-----------------------------------------------------------*/

    ساكن فراغ prv_تیاری_Timer_مداخله( فراغ )
    {
        WDG_InitTypeDef xWdg;
        uint16_t a;
        uint32_t n = configCPU_PERIPH_HZ / config_TICK_شرح_HZ, b;

        /* Configure the watchdog as a free running timer that generates a
         * periodic interrupt. */

        SCU_APBPeriphClockConfig( __WDG, ENABLE );
        WDG_DeInit();
        WDG_StructInit( &xWdg );
        prv_پیدا_کړه_Factors( n, &a, &b );
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

    فراغ WDG_IRQHandler( فراغ )
    {
        {
            /* Increment the tick counter. */
            إذا( xTaskIncrementTick() != pdFALSE )
            {
                /* Select a new task to execute. */
                vTaskSwitchContext();
            }

            /* Clear the interrupt in the watchdog. */
            WDG->SR &= ~0x0001;
        }
    }

#وإلا /* if configUSE_WATCHDOG_TICK == 1 */

    ساكن فراغ prv_پیدا_کړه_Factors( u32 n,
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

        لكل( ; *a <= 256; ( *a )++ )
        {
            *b = n / *a;
            err = ( int32_t ) *a * ( int32_t ) *b - ( int32_t ) n;

            إذا( مطلق_قیمت( err ) > ( *a / 2 ) )
            {
                ( *b )++;
                err = ( int32_t ) *a * ( int32_t ) *b - ( int32_t ) n;
            }

            إذا( مطلق_قیمت( err ) < مطلق_قیمت( err_min ) )
            {
                err_min = err;
                a0 = *a;
                b0 = *b;

                إذا( err == 0 )
                {
                    اكسر;
                }
            }
        }

        *a = a0;
        *b = b0;
    }
    /*-----------------------------------------------------------*/

    ساكن فراغ prv_تیاری_Timer_مداخله( فراغ )
    {
        uint8_t a;
        uint16_t b;
        uint32_t n = configCPU_PERIPH_HZ / config_TICK_شرح_HZ;

        TIM_InitTypeDef timer;

        SCU_APBPeriphClockConfig( __TIM23, ENABLE );
        TIM_DeInit( TIM2 );
        TIM_StructInit( &timer );
        prv_پیدا_کړه_Factors( n, &a, &b );

        timer.TIM_ډېرپېښ = TIM_OCM_CHANNEL_1;
        timer.TIM_OC1_Modes = TIM_TIMING;
        timer.TIM_Clock_سرچینه = TIM_CLK_APB;
        timer.TIM_Clock_څنډه = TIM_CLK_څنډه_RISING;
        timer.TIM_Prescaler = a - 1;
        timer.TIM_Pulse_Level_1 = TIM_لوړ;
        timer.TIM_Pulse_اوږدتیا_1 = s_n_Pulse_اوږدتیا = b - 1;

        TIM_Init( TIM2, &timer );
        TIM_ITConfig( TIM2, TIM_IT_OC1, ENABLE );
        /* Configure the VIC for the WDG interrupt. */
        VIC_Config( TIM2_ITLine, VIC_IRQ, 10 );
        VIC_ITCmd( TIM2_ITLine, ENABLE );

        /* Install the default handlers for both VIC's. */
        VIC0->DVAR = ( uint32_t ) prvDefaultHandler;
        VIC1->DVAR = ( uint32_t ) prvDefaultHandler;

        TIM_CounterCmd( TIM2, TIM_CLEAR );
        TIM_CounterCmd( TIM2, TIM_پیل );
    }
    /*-----------------------------------------------------------*/

    فراغ TIM2_IRQHandler( فراغ )
    {
        /* Reset the timer counter to avoid overflow. */
        TIM2->OC1R += s_n_Pulse_اوږدتیا;

        /* Increment the tick counter. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* Select a new task to run. */
            vTaskSwitchContext();
        }

        /* Clear the interrupt in the watchdog. */
        TIM2->SR &= ~TIM_FLAG_OC1;
    }

#د_که_پای /* USE_WATCHDOG_TICK */

/*-----------------------------------------------------------*/

__arm __interwork فراغ v_پورټ_Enter_Critical( فراغ )
{
    /* Disable interrupts first! */
    پورټ_DISABLE_INTERRUPTS();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

__arm __interwork فراغ v_پورټ_Exit_Critical( فراغ )
{
    إذا( ulCriticalNesting > پورټ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
         * re-enabled. */
        إذا( ulCriticalNesting == پورټ_NO_CRITICAL_NESTING )
        {
            پورټ_ENABLE_INTERRUPTS();
        }
    }
}
/*-----------------------------------------------------------*/

ساكن فراغ prvDefaultHandler( فراغ )
{
}
