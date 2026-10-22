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
#ଅନ୍ତର୍ଭାଵ <string.h>

/* Scheduler includes. */
#ଅନ୍ତର୍ଭାଵ "FreeRTOS.h"
#ଅନ୍ତର୍ଭାଵ "task.h"

/* Constants required to setup timer 2 to produce the RTOS tick. */
#define port_CLOCK_ଭାଜକ                               ( ( uint32_t ) 12 )
#define port_MAX_TIMER_ମୂଲ୍ୟ                             ( ( uint32_t ) 0xffff )
#define portENABLE_TIMER                                ( ( uint8_t ) 0x04 )
#define portTIMER_2_INTERRUPT_ENABLE                    ( ( uint8_t ) 0x20 )

/* The value used in the IE register when a task first starts. */
#define portGLOBAL_INTERRUPT_BIT                        ( ( ଗଦା_Type_t ) 0x80 )

/* The value used in the PSW register when a task first starts. */
#define portINITIAL_PSW                                 ( ( ଗଦା_Type_t ) 0x00 )

/* Macro to clear the timer 2 interrupt flag. */
#define portCLEAR_INTERRUPT_FLAG()                      TMR2CN &= ~0x80;

/* Used during a context switch to store the size of the stack being copied
to or from XRAM. */
data ସ୍ଥିର uint8_t uc_ଗଦା_Bytes;

/* Used during a context switch to point to the next byte in XRAM from/to which
a RAM byte is to be copied. */
xdata ସ୍ଥିର ଗଦା_Type_t * data pxXRAMStack;

/* Used during a context switch to point to the next byte in RAM from/to which
an XRAM byte is to be copied. */
data ସ୍ଥିର ଗଦା_Type_t * data pxRAMStack;

/* We require the address of the pxCurrentTCB variable, but don't want to know
any details of its type. */
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ TCB_t;
ବାହ୍ୟ ଅସ୍ଥିର TCB_t * ଅସ୍ଥିର pxCurrentTCB;

/*
 * Setup the hardware to generate an interrupt off timer 2 at the required
 * frequency.
 */
ସ୍ଥିର ଶୂନ୍ୟ prvSetupTimerInterrupt( ଶୂନ୍ୟ );

/*-----------------------------------------------------------*/
/*
 * Macro that copies the current stack from internal RAM to XRAM.  This is
 * required as the 8051 only contains enough internal RAM for a single stack,
 * but we have a stack for every task.
 */
#define port_COPY_ଗଦା_TO_XRAM()                                                            \
{                                                                                           \
        /* pxCurrentTCB points to a TCB which itself points to the location into            \
        which the first stack byte should be copied. Set pxXRAMStack to point               \
        to the location into which the first stack byte is to be copied. */                 \
        pxXRAMStack = ( xdata ଗଦା_Type_t * ) *( ( xdata ଗଦା_Type_t ** ) pxCurrentTCB );   \
                                                                                            \
        /* Set pxRAMStack to point to the first byte to be coped from the stack. */         \
        pxRAMStack = ( data ଗଦା_Type_t * data ) config_ଗଦା_START;                         \
                                                                                            \
        /* Calculate the size of the stack we are about to copy from the current            \
        stack pointer value. */                                                             \
        uc_ଗଦା_Bytes = SP - ( config_ଗଦା_START - 1 );                                      \
                                                                                            \
        /* Before starting to copy the stack, store the calculated stack size so            \
        the stack can be restored when the task is resumed. */                              \
        *pxXRAMStack = uc_ଗଦା_Bytes;                                                        \
                                                                                            \
        /* Copy each stack byte in turn.  pxXRAMStack is incremented first as we            \
        have already stored the stack size into XRAM. */                                    \
        ଯେତେବେଳେ( uc_ଗଦା_Bytes )                                                               \
        {                                                                                   \
                pxXRAMStack++;                                                              \
                *pxXRAMStack = *pxRAMStack;                                                 \
                pxRAMStack++;                                                               \
                uc_ଗଦା_Bytes--;                                                             \
        }                                                                                   \
}
/*-----------------------------------------------------------*/

/*
 * Macro that copies the stack of the task being resumed from XRAM into
 * internal RAM.
 */
#define port_COPY_XRAM_TO_ଗଦା()                                                            \
{                                                                                           \
        /* Setup the pointers as per portCOPY_STACK_TO_XRAM(), but this time to             \
        copy the data back out of XRAM and into the stack. */                               \
        pxXRAMStack = ( xdata ଗଦା_Type_t * ) *( ( xdata ଗଦା_Type_t ** ) pxCurrentTCB );   \
        pxRAMStack = ( data ଗଦା_Type_t * data ) ( config_ଗଦା_START - 1 );                 \
                                                                                            \
        /* The first value stored in XRAM was the size of the stack - i.e. the              \
        number of bytes we need to copy back. */                                            \
        uc_ଗଦା_Bytes = pxXRAMStack[ 0 ];                                                    \
                                                                                            \
        /* Copy the required number of bytes back into the stack. */                        \
        କର                                                                                  \
        {                                                                                   \
                pxXRAMStack++;                                                              \
                pxRAMStack++;                                                               \
                *pxRAMStack = *pxXRAMStack;                                                 \
                uc_ଗଦା_Bytes--;                                                             \
        } ଯେତେବେଳେ( uc_ଗଦା_Bytes );                                                            \
                                                                                            \
        /* Restore the stack pointer ready to use the restored stack. */                    \
        SP = ( uint8_t ) pxRAMStack;                                                        \
}
/*-----------------------------------------------------------*/

/*
 * Macro to push the current execution context onto the stack, before the stack
 * is moved to XRAM.
 */
#define portSAVE_CONTEXT()                                                                  \
{                                                                                           \
        _asm                                                                                \
                /* Push ACC first, as when restoring the context it must be restored        \
                last (it is used to set the IE register). */                                \
                ଠେଲ        ACC                                                             \
                /* Store the IE register then disable interrupts. */                        \
                ଠେଲ        IE                                                              \
                clr                _EA                                                      \
                ଠେଲ        DPL                                                             \
                ଠେଲ        DPH                                                             \
                ଠେଲ        b                                                               \
                ଠେଲ        ar2                                                             \
                ଠେଲ        ar3                                                             \
                ଠେଲ        ar4                                                             \
                ଠେଲ        ar5                                                             \
                ଠେଲ        ar6                                                             \
                ଠେଲ        ar7                                                             \
                ଠେଲ        ar0                                                             \
                ଠେଲ        ar1                                                             \
                ଠେଲ        PSW                                                             \
        _endasm;                                                                            \
                PSW = 0;                                                                    \
        _asm                                                                                \
                ଠେଲ        _bp                                                             \
        _endasm;                                                                            \
}
/*-----------------------------------------------------------*/

/*
 * Macro that restores the execution context from the stack.  The execution
 * context was saved into the stack before the stack was copied into XRAM.
 */
#define portRESTORE_CONTEXT()                                                               \
{                                                                                           \
        _asm                                                                                \
                କାଢ଼                _bp                                                      \
                କାଢ଼                PSW                                                      \
                କାଢ଼                ar1                                                      \
                କାଢ଼                ar0                                                      \
                କାଢ଼                ar7                                                      \
                କାଢ଼                ar6                                                      \
                କାଢ଼                ar5                                                      \
                କାଢ଼                ar4                                                      \
                କାଢ଼                ar3                                                      \
                କାଢ଼                ar2                                                      \
                କାଢ଼                b                                                        \
                କାଢ଼                DPH                                                      \
                କାଢ଼                DPL                                                      \
                /* The next byte of the stack is the IE register.  Only the global          \
                enable bit forms part of the task context.  Pop off the IE then set         \
                the global enable bit to match that of the stored IE register. */           \
                କାଢ଼                ACC                                                      \
                JB                ACC.7,0098$                                               \
                CLR                IE.7                                                     \
                LJMP        0099$                                                           \
        0098$:                                                                              \
                SETB        IE.7                                                            \
        0099$:                                                                              \
                /* Finally pop off the ACC, which was the first register saved. */          \
                କାଢ଼                ACC                                                      \
                reti                                                                        \
        _endasm;                                                                            \
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ଗଦା_Type_t *px_Port_Initialise_ଗଦା( ଗଦା_Type_t *px_ଶୀର୍ଷ_Of_ଗଦା, TaskFunction_t pxCode, ଶୂନ୍ୟ *pvParameters )
{
uint32_t ulAddress;
ଗଦା_Type_t *px_Start_Of_ଗଦା;

        /* Leave space to write the size of the stack as the first byte. */
        px_Start_Of_ଗଦା = px_ଶୀର୍ଷ_Of_ଗଦା;
        px_ଶୀର୍ଷ_Of_ଗଦା++;

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
        ulAddress = ( uint32_t ) pxCode;
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) ulAddress;
        ulAddress >>= 8;
        px_ଶୀର୍ଷ_Of_ଗଦା++;
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) ( ulAddress );
        px_ଶୀର୍ଷ_Of_ଗଦା++;

        /* Next all the registers will have been pushed by portSAVE_CONTEXT(). */
        *px_ଶୀର୍ଷ_Of_ଗଦା = 0xaa;        /* acc */
        px_ଶୀର୍ଷ_Of_ଗଦା++;

        /* We want tasks to start with interrupts enabled. */
        *px_ଶୀର୍ଷ_Of_ଗଦା = portGLOBAL_INTERRUPT_BIT;
        px_ଶୀର୍ଷ_Of_ଗଦା++;

        /* The function parameters will be passed in the DPTR and B register as
        a three byte generic pointer is used. */
        ulAddress = ( uint32_t ) pvParameters;
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) ulAddress;        /* DPL */
        ulAddress >>= 8;
        *px_ଶୀର୍ଷ_Of_ଗଦା++;
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) ulAddress;        /* DPH */
        ulAddress >>= 8;
        px_ଶୀର୍ଷ_Of_ଗଦା++;
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) ulAddress;        /* b */
        px_ଶୀର୍ଷ_Of_ଗଦା++;

        /* The remaining registers are straight forward. */
        *px_ଶୀର୍ଷ_Of_ଗଦା = 0x02;        /* R2 */
        px_ଶୀର୍ଷ_Of_ଗଦା++;
        *px_ଶୀର୍ଷ_Of_ଗଦା = 0x03;        /* R3 */
        px_ଶୀର୍ଷ_Of_ଗଦା++;
        *px_ଶୀର୍ଷ_Of_ଗଦା = 0x04;        /* R4 */
        px_ଶୀର୍ଷ_Of_ଗଦା++;
        *px_ଶୀର୍ଷ_Of_ଗଦା = 0x05;        /* R5 */
        px_ଶୀର୍ଷ_Of_ଗଦା++;
        *px_ଶୀର୍ଷ_Of_ଗଦା = 0x06;        /* R6 */
        px_ଶୀର୍ଷ_Of_ଗଦା++;
        *px_ଶୀର୍ଷ_Of_ଗଦା = 0x07;        /* R7 */
        px_ଶୀର୍ଷ_Of_ଗଦା++;
        *px_ଶୀର୍ଷ_Of_ଗଦା = 0x00;        /* R0 */
        px_ଶୀର୍ଷ_Of_ଗଦା++;
        *px_ଶୀର୍ଷ_Of_ଗଦା = 0x01;        /* R1 */
        px_ଶୀର୍ଷ_Of_ଗଦା++;
        *px_ଶୀର୍ଷ_Of_ଗଦା = 0x00;        /* PSW */
        px_ଶୀର୍ଷ_Of_ଗଦା++;
        *px_ଶୀର୍ଷ_Of_ଗଦା = 0xbb;        /* BP */

        /* Dont increment the stack size here as we don't want to include
        the stack size byte as part of the stack size count.

        Finally we place the stack size at the beginning. */
        *px_Start_Of_ଗଦା = ( ଗଦା_Type_t ) ( px_ଶୀର୍ଷ_Of_ଗଦା - px_Start_Of_ଗଦା );

        /* Unlike most ports, we return the start of the stack as this is where the
        size of the stack is stored. */
        ଫେରନ୍ତୁ px_Start_Of_ଗଦା;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( ଶୂନ୍ୟ )
{
        /* Setup timer 2 to generate the RTOS tick. */
        prvSetupTimerInterrupt();

        /* Make sure we start with the expected SFR page.  This line should not
        really be required. */
        SFRPAGE = 0;

        /* Copy the stack for the first task to execute from XRAM into the stack,
        restore the task context from the new stack, then start running the task. */
        port_COPY_XRAM_TO_ଗଦା();
        portRESTORE_CONTEXT();

        /* Should never get here! */
        ଫେରନ୍ତୁ pdTRUE;
}
/*-----------------------------------------------------------*/

ଶୂନ୍ୟ vPortEndScheduler( ଶୂନ୍ୟ )
{
        /* Not implemented for this port. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch.  The first thing we do is save the registers so we
 * can use a naked attribute.
 */
ଶୂନ୍ୟ vPortYield( ଶୂନ୍ୟ ) _naked
{
        /* Save the execution context onto the stack, then copy the entire stack
        to XRAM.  This is necessary as the internal RAM is only large enough to
        hold one stack, and we want one per task.

        PERFORMANCE COULD BE IMPROVED BY ONLY COPYING TO XRAM IF A TASK SWITCH
        IS REQUIRED. */
        portSAVE_CONTEXT();
        port_COPY_ଗଦା_TO_XRAM();

        /* Call the standard scheduler context switch function. */
        vTaskSwitchContext();

        /* Copy the stack of the task about to execute from XRAM into RAM and
        restore it's context ready to run on exiting. */
        port_COPY_XRAM_TO_ଗଦା();
        portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

#ଯଦି configUSE_PREEMPTION == 1
        ଶୂନ୍ୟ vTimer2ISR( ଶୂନ୍ୟ ) interrupt 5 _naked
        {
                /* Preemptive context switch function triggered by the timer 2 ISR.
                This does the same as vPortYield() (see above) with the addition
                of incrementing the RTOS tick count. */

                portSAVE_CONTEXT();
                port_COPY_ଗଦା_TO_XRAM();

                ଯଦି( xTaskIncrementTick() != pdFALSE )
                {
                        vTaskSwitchContext();
                }

                portCLEAR_INTERRUPT_FLAG();
                port_COPY_XRAM_TO_ଗଦା();
                portRESTORE_CONTEXT();
        }
#ଅନ୍ୟଥା
        ଶୂନ୍ୟ vTimer2ISR( ଶୂନ୍ୟ ) interrupt 5
        {
                /* When using the cooperative scheduler the timer 2 ISR is only
                required to increment the RTOS tick count. */

                xTaskIncrementTick();
                portCLEAR_INTERRUPT_FLAG();
        }
#endif
/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ prvSetupTimerInterrupt( ଶୂନ୍ୟ )
{
uint8_t ucOriginalSFRPage;

/* Constants calculated to give the required timer capture values. */
ଅଚଳ uint32_t ulTicksPerSecond = configCPU_CLOCK_HZ / port_CLOCK_ଭାଜକ;
ଅଚଳ uint32_t ulCaptureTime = ulTicksPerSecond / configTICK_RATE_HZ;
ଅଚଳ uint32_t ul_Capture_ମୂଲ୍ୟ = port_MAX_TIMER_ମୂଲ୍ୟ - ulCaptureTime;
ଅଚଳ uint8_t uc_ତଳ_Capture_Byte = ( uint8_t ) ( ul_Capture_ମୂଲ୍ୟ & ( uint32_t ) 0xff );
ଅଚଳ uint8_t uc_ଉପର_Capture_Byte = ( uint8_t ) ( ul_Capture_ମୂଲ୍ୟ >> ( uint32_t ) 8 );

        /* NOTE:  This uses a timer only present on 8052 architecture. */

        /* Remember the current SFR page so we can restore it at the end of the
        function. */
        ucOriginalSFRPage = SFRPAGE;
        SFRPAGE = 0;

        /* TMR2CF can be left in its default state. */
        TMR2CF = ( uint8_t ) 0;

        /* Setup the overflow reload value. */
        RCAP2L = uc_ତଳ_Capture_Byte;
        RCAP2H = uc_ଉପର_Capture_Byte;

        /* The initial load is performed manually. */
        TMR2L = uc_ତଳ_Capture_Byte;
        TMR2H = uc_ଉପର_Capture_Byte;

        /* Enable the timer 2 interrupts. */
        IE |= portTIMER_2_INTERRUPT_ENABLE;

        /* Interrupts are disabled when this is called so the timer can be started
        here. */
        TMR2CN = portENABLE_TIMER;

        /* Restore the original SFR page. */
        SFRPAGE = ucOriginalSFRPage;
}
