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
 * Implementation of functions defined in portable.h for the Cygnal port.
 *----------------------------------------------------------*/

/* Standard includes. */
#ضمن <string.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Constants required to setup timer 2 to produce the RTOS tick. */
#تعریف_کرو پورٹ_CLOCK_مقسوم_علیہ                               ( ( uint32_t ) 12 )
#تعریف_کرو پورٹ_MAX_TIMER_قدر                             ( ( uint32_t ) 0xffff )
#تعریف_کرو پورٹ_ENABLE_TIMER                                ( ( uint8_t ) 0x04 )
#تعریف_کرو پورٹ_TIMER_2_رکاوٹ_ENABLE                    ( ( uint8_t ) 0x20 )

/* The value used in the IE register when a task first starts. */
#تعریف_کرو پورٹ_GLOBAL_رکاوٹ_ثنائی_ہندسہ                        ( ( ڈھیر_Type_t ) 0x80 )

/* The value used in the PSW register when a task first starts. */
#تعریف_کرو پورٹ_INITIAL_PSW                                 ( ( ڈھیر_Type_t ) 0x00 )

/* Macro to clear the timer 2 interrupt flag. */
#تعریف_کرو پورٹ_CLEAR_رکاوٹ_FLAG()                      TMR2CN &= ~0x80;

/* Used during a context switch to store the size of the stack being copied
to or from XRAM. */
انکڑے_2 ساكن uint8_t uc_ڈھیر_بائٹاں;

/* Used during a context switch to point to the next byte in XRAM from/to which
a RAM byte is to be copied. */
xdata ساكن ڈھیر_Type_t * انکڑے_2 pxXRAMStack;

/* Used during a context switch to point to the next byte in RAM from/to which
an XRAM byte is to be copied. */
انکڑے_2 ساكن ڈھیر_Type_t * انکڑے_2 pxRAMStack;

/* We require the address of the pxCurrentTCB variable, but don't want to know
any details of its type. */
تعريفنوع فراغ TCB_t;
خارجي متطاير TCB_t * متطاير pxCurrentTCB;

/*
 * Setup the hardware to generate an interrupt off timer 2 at the required
 * frequency.
 */
ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ );

/*-----------------------------------------------------------*/
/*
 * Macro that copies the current stack from internal RAM to XRAM.  This is
 * required as the 8051 only contains enough internal RAM for a single stack,
 * but we have a stack for every task.
 */
#تعریف_کرو پورٹ_COPY_ڈھیر_منزل_XRAM()                                                            \
{                                                                                           \
        /* pxCurrentTCB points to a TCB which itself points to the location into            \
        which the first stack byte should be copied. Set pxXRAMStack to point               \
        to the location into which the first stack byte is to be copied. */                 \
        pxXRAMStack = ( xdata ڈھیر_Type_t * ) *( ( xdata ڈھیر_Type_t ** ) pxCurrentTCB );   \
                                                                                            \
        /* Set pxRAMStack to point to the first byte to be coped from the stack. */         \
        pxRAMStack = ( انکڑے_2 ڈھیر_Type_t * انکڑے_2 ) config_ڈھیر_شروع;                         \
                                                                                            \
        /* Calculate the size of the stack we are about to copy from the current            \
        stack pointer value. */                                                             \
        uc_ڈھیر_بائٹاں = SP - ( config_ڈھیر_شروع - 1 );                                      \
                                                                                            \
        /* Before starting to copy the stack, store the calculated stack size so            \
        the stack can be restored when the task is resumed. */                              \
        *pxXRAMStack = uc_ڈھیر_بائٹاں;                                                        \
                                                                                            \
        /* Copy each stack byte in turn.  pxXRAMStack is incremented first as we            \
        have already stored the stack size into XRAM. */                                    \
        طالما( uc_ڈھیر_بائٹاں )                                                               \
        {                                                                                   \
                pxXRAMStack++;                                                              \
                *pxXRAMStack = *pxRAMStack;                                                 \
                pxRAMStack++;                                                               \
                uc_ڈھیر_بائٹاں--;                                                             \
        }                                                                                   \
}
/*-----------------------------------------------------------*/

/*
 * Macro that copies the stack of the task being resumed from XRAM into
 * internal RAM.
 */
#تعریف_کرو پورٹ_COPY_XRAM_منزل_ڈھیر()                                                            \
{                                                                                           \
        /* Setup the pointers as per portCOPY_STACK_TO_XRAM(), but this time to             \
        copy the data back out of XRAM and into the stack. */                               \
        pxXRAMStack = ( xdata ڈھیر_Type_t * ) *( ( xdata ڈھیر_Type_t ** ) pxCurrentTCB );   \
        pxRAMStack = ( انکڑے_2 ڈھیر_Type_t * انکڑے_2 ) ( config_ڈھیر_شروع - 1 );                 \
                                                                                            \
        /* The first value stored in XRAM was the size of the stack - i.e. the              \
        number of bytes we need to copy back. */                                            \
        uc_ڈھیر_بائٹاں = pxXRAMStack[ 0 ];                                                    \
                                                                                            \
        /* Copy the required number of bytes back into the stack. */                        \
        افعل                                                                                  \
        {                                                                                   \
                pxXRAMStack++;                                                              \
                pxRAMStack++;                                                               \
                *pxRAMStack = *pxXRAMStack;                                                 \
                uc_ڈھیر_بائٹاں--;                                                             \
        } طالما( uc_ڈھیر_بائٹاں );                                                            \
                                                                                            \
        /* Restore the stack pointer ready to use the restored stack. */                    \
        SP = ( uint8_t ) pxRAMStack;                                                        \
}
/*-----------------------------------------------------------*/

/*
 * Macro to push the current execution context onto the stack, before the stack
 * is moved to XRAM.
 */
#تعریف_کرو پورٹ_SAVE_CONTEXT()                                                                  \
{                                                                                           \
        _asm                                                                                \
                /* Push ACC first, as when restoring the context it must be restored        \
                last (it is used to set the IE register). */                                \
                ڈالو        ACC                                                             \
                /* Store the IE register then disable interrupts. */                        \
                ڈالو        IE                                                              \
                clr                _EA                                                      \
                ڈالو        DPL                                                             \
                ڈالو        DPH                                                             \
                ڈالو        b                                                               \
                ڈالو        ar2                                                             \
                ڈالو        ar3                                                             \
                ڈالو        ar4                                                             \
                ڈالو        ar5                                                             \
                ڈالو        ar6                                                             \
                ڈالو        ar7                                                             \
                ڈالو        ar0                                                             \
                ڈالو        ar1                                                             \
                ڈالو        PSW                                                             \
        _endasm;                                                                            \
                PSW = 0;                                                                    \
        _asm                                                                                \
                ڈالو        _bp                                                             \
        _endasm;                                                                            \
}
/*-----------------------------------------------------------*/

/*
 * Macro that restores the execution context from the stack.  The execution
 * context was saved into the stack before the stack was copied into XRAM.
 */
#تعریف_کرو پورٹ_RESTORE_CONTEXT()                                                               \
{                                                                                           \
        _asm                                                                                \
                نکالو                _bp                                                      \
                نکالو                PSW                                                      \
                نکالو                ar1                                                      \
                نکالو                ar0                                                      \
                نکالو                ar7                                                      \
                نکالو                ar6                                                      \
                نکالو                ar5                                                      \
                نکالو                ar4                                                      \
                نکالو                ar3                                                      \
                نکالو                ar2                                                      \
                نکالو                b                                                        \
                نکالو                DPH                                                      \
                نکالو                DPL                                                      \
                /* The next byte of the stack is the IE register.  Only the global          \
                enable bit forms part of the task context.  Pop off the IE then set         \
                the global enable bit to match that of the stored IE register. */           \
                نکالو                ACC                                                      \
                JB                ACC.7,0098$                                               \
                CLR                IE.7                                                     \
                LJMP        0099$                                                           \
        0098$:                                                                              \
                SETB        IE.7                                                            \
        0099$:                                                                              \
                /* Finally pop off the ACC, which was the first register saved. */          \
                نکالو                ACC                                                      \
                reti                                                                        \
        _endasm;                                                                            \
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t *px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t *px_چوٹی_دا_ڈھیر, TaskFunction_t px_کوڈ, فراغ *pvParameters )
{
uint32_t ul_پتہ;
ڈھیر_Type_t *px_شروع_دا_ڈھیر;

        /* Leave space to write the size of the stack as the first byte. */
        px_شروع_دا_ڈھیر = px_چوٹی_دا_ڈھیر;
        px_چوٹی_دا_ڈھیر++;

        /* Place a few bytes of known values on the bottom of the stack.
        This is just useful for debugging and can be uncommented if required.
        *pxTopOfStack = 0x11;
        pxTopOfStack++;
        *pxTopOfStack = 0x22;
        pxTopOfStack++;
        *pxTopOfStack = 0x33;
        pxTopOfStack++;
        */

        /* Simulate how the stack would look after a call to the scheduler tick
        ISR.

        The return address that would have been pushed by the MCU. */
        ul_پتہ = ( uint32_t ) px_کوڈ;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) ul_پتہ;
        ul_پتہ >>= 8;
        px_چوٹی_دا_ڈھیر++;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) ( ul_پتہ );
        px_چوٹی_دا_ڈھیر++;

        /* Next all the registers will have been pushed by portSAVE_CONTEXT(). */
        *px_چوٹی_دا_ڈھیر = 0xaa;        /* acc */
        px_چوٹی_دا_ڈھیر++;

        /* We want tasks to start with interrupts enabled. */
        *px_چوٹی_دا_ڈھیر = پورٹ_GLOBAL_رکاوٹ_ثنائی_ہندسہ;
        px_چوٹی_دا_ڈھیر++;

        /* The function parameters will be passed in the DPTR and B register as
        a three byte generic pointer is used. */
        ul_پتہ = ( uint32_t ) pvParameters;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) ul_پتہ;        /* DPL */
        ul_پتہ >>= 8;
        *px_چوٹی_دا_ڈھیر++;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) ul_پتہ;        /* DPH */
        ul_پتہ >>= 8;
        px_چوٹی_دا_ڈھیر++;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) ul_پتہ;        /* b */
        px_چوٹی_دا_ڈھیر++;

        /* The remaining registers are straight forward. */
        *px_چوٹی_دا_ڈھیر = 0x02;        /* R2 */
        px_چوٹی_دا_ڈھیر++;
        *px_چوٹی_دا_ڈھیر = 0x03;        /* R3 */
        px_چوٹی_دا_ڈھیر++;
        *px_چوٹی_دا_ڈھیر = 0x04;        /* R4 */
        px_چوٹی_دا_ڈھیر++;
        *px_چوٹی_دا_ڈھیر = 0x05;        /* R5 */
        px_چوٹی_دا_ڈھیر++;
        *px_چوٹی_دا_ڈھیر = 0x06;        /* R6 */
        px_چوٹی_دا_ڈھیر++;
        *px_چوٹی_دا_ڈھیر = 0x07;        /* R7 */
        px_چوٹی_دا_ڈھیر++;
        *px_چوٹی_دا_ڈھیر = 0x00;        /* R0 */
        px_چوٹی_دا_ڈھیر++;
        *px_چوٹی_دا_ڈھیر = 0x01;        /* R1 */
        px_چوٹی_دا_ڈھیر++;
        *px_چوٹی_دا_ڈھیر = 0x00;        /* PSW */
        px_چوٹی_دا_ڈھیر++;
        *px_چوٹی_دا_ڈھیر = 0xbb;        /* BP */

        /* Dont increment the stack size here as we don't want to include
        the stack size byte as part of the stack size count.

        Finally we place the stack size at the beginning. */
        *px_شروع_دا_ڈھیر = ( ڈھیر_Type_t ) ( px_چوٹی_دا_ڈھیر - px_شروع_دا_ڈھیر );

        /* Unlike most ports, we return the start of the stack as this is where the
        size of the stack is stored. */
        أرجع px_شروع_دا_ڈھیر;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
        /* Setup timer 2 to generate the RTOS tick. */
        prv_تیاری_Timer_رکاوٹ();

        /* Make sure we start with the expected SFR page.  This line should not
        really be required. */
        SFRPAGE = 0;

        /* Copy the stack for the first task to execute from XRAM into the stack,
        restore the task context from the new stack, then start running the task. */
        پورٹ_COPY_XRAM_منزل_ڈھیر();
        پورٹ_RESTORE_CONTEXT();

        /* Should never get here! */
        أرجع pdTRUE;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
        /* Not implemented for this port. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch.  The first thing we do is save the registers so we
 * can use a naked attribute.
 */
فراغ v_پورٹ_Yield( فراغ ) _naked
{
        /* Save the execution context onto the stack, then copy the entire stack
        to XRAM.  This is necessary as the internal RAM is only large enough to
        hold one stack, and we want one per task.

        PERFORMANCE COULD BE IMPROVED BY ONLY COPYING TO XRAM IF A TASK SWITCH
        IS REQUIRED. */
        پورٹ_SAVE_CONTEXT();
        پورٹ_COPY_ڈھیر_منزل_XRAM();

        /* Call the standard scheduler context switch function. */
        vTaskSwitchContext();

        /* Copy the stack of the task about to execute from XRAM into RAM and
        restore it's context ready to run on exiting. */
        پورٹ_COPY_XRAM_منزل_ڈھیر();
        پورٹ_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

#إذا configUSE_PREEMPTION == 1
        فراغ vTimer2ISR( فراغ ) رکاوٹ 5 _naked
        {
                /* Preemptive context switch function triggered by the timer 2 ISR.
                This does the same as vPortYield() (see above) with the addition
                of incrementing the RTOS tick count. */

                پورٹ_SAVE_CONTEXT();
                پورٹ_COPY_ڈھیر_منزل_XRAM();

                إذا( xTaskIncrementTick() != pdFALSE )
                {
                        vTaskSwitchContext();
                }

                پورٹ_CLEAR_رکاوٹ_FLAG();
                پورٹ_COPY_XRAM_منزل_ڈھیر();
                پورٹ_RESTORE_CONTEXT();
        }
#وإلا
        فراغ vTimer2ISR( فراغ ) رکاوٹ 5
        {
                /* When using the cooperative scheduler the timer 2 ISR is only
                required to increment the RTOS tick count. */

                xTaskIncrementTick();
                پورٹ_CLEAR_رکاوٹ_FLAG();
        }
#جے_انت
/*-----------------------------------------------------------*/

ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ )
{
uint8_t ucOriginalSFRPage;

/* Constants calculated to give the required timer capture values. */
ثابت uint32_t ul_Ticks_فی_دوجا = configCPU_CLOCK_HZ / پورٹ_CLOCK_مقسوم_علیہ;
ثابت uint32_t ul_Capture_ویلا = ul_Ticks_فی_دوجا / config_TICK_شرح_HZ;
ثابت uint32_t ul_Capture_قدر = پورٹ_MAX_TIMER_قدر - ul_Capture_ویلا;
ثابت uint8_t uc_کم_Capture_Byte = ( uint8_t ) ( ul_Capture_قدر & ( uint32_t ) 0xff );
ثابت uint8_t uc_بلند_Capture_Byte = ( uint8_t ) ( ul_Capture_قدر >> ( uint32_t ) 8 );

        /* NOTE:  This uses a timer only present on 8052 architecture. */

        /* Remember the current SFR page so we can restore it at the end of the
        function. */
        ucOriginalSFRPage = SFRPAGE;
        SFRPAGE = 0;

        /* TMR2CF can be left in its default state. */
        TMR2CF = ( uint8_t ) 0;

        /* Setup the overflow reload value. */
        RCAP2L = uc_کم_Capture_Byte;
        RCAP2H = uc_بلند_Capture_Byte;

        /* The initial load is performed manually. */
        TMR2L = uc_کم_Capture_Byte;
        TMR2H = uc_بلند_Capture_Byte;

        /* Enable the timer 2 interrupts. */
        IE |= پورٹ_TIMER_2_رکاوٹ_ENABLE;

        /* Interrupts are disabled when this is called so the timer can be started
        here. */
        TMR2CN = پورٹ_ENABLE_TIMER;

        /* Restore the original SFR page. */
        SFRPAGE = ucOriginalSFRPage;
}
