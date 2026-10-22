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

#جے_بنا_تعریف configUSE_WATCHDOG_TICK
    #غلطی configUSE_WATCHDOG_TICK must be سیٹ منزل either 1 or 0 وچ FreeRTOSConfig.h منزل use either the Watchdog or timer 2 منزل generate the tick رکاوٹ respectively.
#جے_انت

/* Constants required to setup the initial stack. */
#جے_بنا_تعریف لگاتار_TASK_وچ_ARM_منوال
    #تعریف_کرو پورٹ_INITIAL_SPSR       ( ( ڈھیر_Type_t ) 0x3f )      /* System mode, THUMB mode, interrupts enabled. */
#وإلا
    #تعریف_کرو پورٹ_INITIAL_SPSR       ( ( ڈھیر_Type_t ) 0x1f )      /* System mode, ARM mode, interrupts enabled. */
#جے_انت

#تعریف_کرو پورٹ_INSTRUCTION_ناپ       ( ( ڈھیر_Type_t ) 4 )

/* Constants required to handle critical sections. */
#تعریف_کرو پورٹ_NO_CRITICAL_NESTING    ( ( uint32_t ) 0 )

#جے_بنا_تعریف مطلق_قدر
    #تعریف_کرو مطلق_قدر( x )    ( ( x ) > 0 ? ( x ) : -( x ) )
#جے_انت

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
#تعریف_کرو TOGGLE_LED( پورٹ, pin )                                           \
    إذا( ( ( ( ( پورٹ )->DR[ ( pin ) << 2 ] ) ) & ( pin ) ) != ثنائی_ہندسہ_RESET ) \
    {                                                                     \
        ( پورٹ )->DR[ ( pin ) << 2 ] = 0x00;                              \
    }                                                                     \
    وإلا                                                                  \
    {                                                                     \
        ( پورٹ )->DR[ ( pin ) << 2 ] = ( pin );                           \
    }


/*-----------------------------------------------------------*/

/* Setup the watchdog to generate the tick interrupts. */
ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ );

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
    ساكن u16 s_n_Pulse_لمائی;
#جے_انت

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                     TaskFunction_t px_کوڈ,
                                     فراغ * pvParameters )
{
    ڈھیر_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_چوٹی_دا_ڈھیر;

    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_چوٹی_دا_ڈھیر--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) px_کوڈ + پورٹ_INSTRUCTION_ناپ;
    px_چوٹی_دا_ڈھیر--;

    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0xaaaaaaaa;    /* R14 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x12121212;    /* R12 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x11111111;    /* R11 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x10101010;    /* R10 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x09090909;    /* R9 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x08080808;    /* R8 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x07070707;    /* R7 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x06060606;    /* R6 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x05050505;    /* R5 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x04040404;    /* R4 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x03030303;    /* R3 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x02020202;    /* R2 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x01010101;    /* R1 */
    px_چوٹی_دا_ڈھیر--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) pvParameters; /* R0 */
    px_چوٹی_دا_ڈھیر--;

    /* The status register is set for system mode, with interrupts enabled. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_INITIAL_SPSR;
    px_چوٹی_دا_ڈھیر--;

    /* Interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_چوٹی_دا_ڈھیر = پورٹ_NO_CRITICAL_NESTING;

    أرجع px_چوٹی_دا_ڈھیر;
}
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
    خارجي فراغ v_پورٹ_شروع_پہلا_Task( فراغ );

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_تیاری_Timer_رکاوٹ();

    /* Start the first task. */
    v_پورٹ_شروع_پہلا_Task();

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/* This function is called from an asm wrapper, so does not require the __irq
 * keyword. */
#إذا configUSE_WATCHDOG_TICK == 1

    ساكن فراغ prv_لبھو_Factors( u32 n,
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

            إذا( مطلق_قدر( err ) > ( *a / 2 ) )
            {
                ( *b )++;
                err = ( int32_t ) *a * ( int32_t ) *b - ( int32_t ) n;
            }

            إذا( مطلق_قدر( err ) < مطلق_قدر( err_min ) )
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

    ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ )
    {
        WDG_InitTypeDef xWdg;
        uint16_t a;
        uint32_t n = configCPU_PERIPH_HZ / config_TICK_شرح_HZ, b;

        /* Configure the watchdog as a free running timer that generates a
         * periodic interrupt. */

        SCU_APBPeriphClockConfig( __WDG, ENABLE );
        WDG_DeInit();
        WDG_StructInit( &xWdg );
        prv_لبھو_Factors( n, &a, &b );
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

    ساكن فراغ prv_لبھو_Factors( u32 n,
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

            إذا( مطلق_قدر( err ) > ( *a / 2 ) )
            {
                ( *b )++;
                err = ( int32_t ) *a * ( int32_t ) *b - ( int32_t ) n;
            }

            إذا( مطلق_قدر( err ) < مطلق_قدر( err_min ) )
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

    ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ )
    {
        uint8_t a;
        uint16_t b;
        uint32_t n = configCPU_PERIPH_HZ / config_TICK_شرح_HZ;

        TIM_InitTypeDef timer;

        SCU_APBPeriphClockConfig( __TIM23, ENABLE );
        TIM_DeInit( TIM2 );
        TIM_StructInit( &timer );
        prv_لبھو_Factors( n, &a, &b );

        timer.TIM_منوال = TIM_OCM_CHANNEL_1;
        timer.TIM_OC1_Modes = TIM_TIMING;
        timer.TIM_Clock_سروت = TIM_CLK_APB;
        timer.TIM_Clock_کنارا = TIM_CLK_کنارا_RISING;
        timer.TIM_Prescaler = a - 1;
        timer.TIM_Pulse_Level_1 = TIM_بلند;
        timer.TIM_Pulse_لمائی_1 = s_n_Pulse_لمائی = b - 1;

        TIM_Init( TIM2, &timer );
        TIM_ITConfig( TIM2, TIM_IT_OC1, ENABLE );
        /* Configure the VIC for the WDG interrupt. */
        VIC_Config( TIM2_ITLine, VIC_IRQ, 10 );
        VIC_ITCmd( TIM2_ITLine, ENABLE );

        /* Install the default handlers for both VIC's. */
        VIC0->DVAR = ( uint32_t ) prvDefaultHandler;
        VIC1->DVAR = ( uint32_t ) prvDefaultHandler;

        TIM_CounterCmd( TIM2, TIM_CLEAR );
        TIM_CounterCmd( TIM2, TIM_شروع );
    }
    /*-----------------------------------------------------------*/

    فراغ TIM2_IRQHandler( فراغ )
    {
        /* Reset the timer counter to avoid overflow. */
        TIM2->OC1R += s_n_Pulse_لمائی;

        /* Increment the tick counter. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* Select a new task to run. */
            vTaskSwitchContext();
        }

        /* Clear the interrupt in the watchdog. */
        TIM2->SR &= ~TIM_FLAG_OC1;
    }

#جے_انت /* USE_WATCHDOG_TICK */

/*-----------------------------------------------------------*/

__arm __interwork فراغ v_پورٹ_Enter_Critical( فراغ )
{
    /* Disable interrupts first! */
    پورٹ_DISABLE_INTERRUPTS();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

__arm __interwork فراغ v_پورٹ_Exit_Critical( فراغ )
{
    إذا( ulCriticalNesting > پورٹ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
         * re-enabled. */
        إذا( ulCriticalNesting == پورٹ_NO_CRITICAL_NESTING )
        {
            پورٹ_ENABLE_INTERRUPTS();
        }
    }
}
/*-----------------------------------------------------------*/

ساكن فراغ prvDefaultHandler( فراغ )
{
}
