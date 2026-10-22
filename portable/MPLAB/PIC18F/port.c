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

/*
Changes between V1.2.4 and V1.2.5

    + Introduced portGLOBAL_INTERRUPT_FLAG definition to test the global
      interrupt flag setting.  Using the two bits defined within
      portINITAL_INTERRUPT_STATE was causing the w register to get clobbered
      before the test was performed.

Changes from V1.2.5

    + Set the interrupt vector address to 0x08.  Previously it was at the
      incorrect address for compatibility mode of 0x18.

Changes from V2.1.1

    + PCLATU and PCLATH are now saved as part of the context.  This allows
      function pointers to be used within tasks.  Thanks to Javier Espeche
      for the enhancement.

Changes from V2.3.1

    + TABLAT is now saved as part of the task context.

Changes from V3.2.0

    + TBLPTRU is now initialised to zero as the MPLAB compiler expects this
      value and does not write to the register.
*/

/* Scheduler include files. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* MPLAB library include file. */
#ಅನ್ತರ್ಭಾವ "timers.h"

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the PIC port.
 *----------------------------------------------------------*/

/* Hardware setup for tick. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_FOSC_SCALE            ( ( uint32_t ) 4 )

/* Initial interrupt enable state for newly created tasks.  This value is
copied into INTCON when a task switches in for the first time. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITAL_ಅಡಚಣೆ_STATE          0xc0

/* Just the bit within INTCON for the global interrupt flag. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GLOBAL_ಅಡಚಣೆ_FLAG           0x80

/* Constant used for context switch macro when we require the interrupt
enable state to be unchanged when the interrupted task is switched back in. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INTERRUPTS_UNCHANGED            0x00

/* Some memory areas get saved as part of the task context.  These memory
area's get used by the compiler for temporary storage, especially when
performing mathematical operations, or when using 32bit data types.  This
constant defines the size of memory area which must be saved. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_COMPILER_MANAGED_ಸ್ಮರಣೆ_ಗಾತ್ರ    ( ( uint8_t ) 0x13 )

/* We require the address of the pxCurrentTCB variable, but don't want to know
any details of its type. */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ TCB_t;
ಬಾಹ್ಯ ಅಸ್ಥಿರ TCB_t * ಅಸ್ಥಿರ pxCurrentTCB;

/* IO port constants. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಬಿಟ್_ಗಣ     ( ( uint8_t ) 1 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಬಿಟ್_CLEAR   ( ( uint8_t ) 0 )

/*
 * The serial port ISR's are defined in serial.c, but are called from portable
 * as they use the same vector as the tick ISR.
 */
ಶೂನ್ಯ vSerialTxISR( ಶೂನ್ಯ );
ಶೂನ್ಯ vSerialRxISR( ಶೂನ್ಯ );

/*
 * Perform hardware setup to enable ticks.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );

/*
 * ISR to maintain the tick, and perform tick context switches if the
 * preemptive scheduler is being used.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvTickISR( ಶೂನ್ಯ );

/*
 * ISR placed on the low priority vector.  This calls the appropriate ISR for
 * the actual interrupt.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಕೆಳಗಿನ_ಅಡಚಣೆ( ಶೂನ್ಯ );

/*
 * Macro that pushes all the registers that make up the context of a task onto
 * the stack, then saves the new top of stack into the TCB.
 *
 * If this is called from an ISR then the interrupt enable bits must have been
 * set for the ISR to ever get called.  Therefore we want to save the INTCON
 * register with the enable bits forced to be set - and ucForcedInterruptFlags
 * must contain these bit settings.  This means the interrupts will again be
 * enabled when the interrupted task is switched back in.
 *
 * If this is called from a manual context switch (i.e. from a call to yield),
 * then we want to save the INTCON so it is restored with its current state,
 * and ucForcedInterruptFlags must be 0.  This allows a yield from within
 * a critical section.
 *
 * The compiler uses some locations at the bottom of the memory for temporary
 * storage during math and other computations.  This is especially true if
 * 32bit data types are utilized (as they are by the scheduler).  The .tmpdata
 * and MATH_DATA sections have to be stored in there entirety as part of a task
 * context.  This macro stores from data address 0x00 to
 * portCOMPILER_MANAGED_MEMORY_SIZE.  This is sufficient for the demo
 * applications but you should check the map file for your project to ensure
 * this is sufficient for your needs.  It is not clear whether this size is
 * fixed for all compilations or has the potential to be program specific.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SAVE_CONTEXT( uc_Forced_ಅಡಚಣೆ_Flags )                              \
{                                                                               \
    _asm                                                                        \
        /* Save the status and WREG registers first, as these will get modified \
        by the operations below. */                                             \
        MOVFF   WREG, PREINC1                                                   \
        MOVFF   ಸ್ಥಿತಿ_3, PREINC1                                                 \
        /* Save the INTCON register with the appropriate bits forced if         \
        necessary - as described above. */                                      \
        MOVFF   INTCON, WREG                                                    \
        IORLW   uc_Forced_ಅಡಚಣೆ_Flags                                          \
        MOVFF   WREG, PREINC1                                                   \
    _endasm                                                                     \
                                                                                \
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();                                                   \
                                                                                \
    _asm                                                                        \
        /* Store the necessary registers to the stack. */                       \
        MOVFF   BSR, PREINC1                                                    \
        MOVFF   FSR2L, PREINC1                                                  \
        MOVFF   FSR2H, PREINC1                                                  \
        MOVFF   FSR0L, PREINC1                                                  \
        MOVFF   FSR0H, PREINC1                                                  \
        MOVFF   TABLAT, PREINC1                                                 \
        MOVFF   TBLPTRU, PREINC1                                                \
        MOVFF   TBLPTRH, PREINC1                                                \
        MOVFF   TBLPTRL, PREINC1                                                \
        MOVFF   PRODH, PREINC1                                                  \
        MOVFF   PRODL, PREINC1                                                  \
        MOVFF   PCLATU, PREINC1                                                 \
        MOVFF   PCLATH, PREINC1                                                 \
        /* Store the .tempdata and MATH_DATA areas as described above. */       \
        CLRF    FSR0L, 0                                                        \
        CLRF    FSR0H, 0                                                        \
        MOVFF   POSTINC0, PREINC1                                               \
        MOVFF   POSTINC0, PREINC1                                               \
        MOVFF   POSTINC0, PREINC1                                               \
        MOVFF   POSTINC0, PREINC1                                               \
        MOVFF   POSTINC0, PREINC1                                               \
        MOVFF   POSTINC0, PREINC1                                               \
        MOVFF   POSTINC0, PREINC1                                               \
        MOVFF   POSTINC0, PREINC1                                               \
        MOVFF   POSTINC0, PREINC1                                               \
        MOVFF   POSTINC0, PREINC1                                               \
        MOVFF   POSTINC0, PREINC1                                               \
        MOVFF   POSTINC0, PREINC1                                               \
        MOVFF   POSTINC0, PREINC1                                               \
        MOVFF   POSTINC0, PREINC1                                               \
        MOVFF   POSTINC0, PREINC1                                               \
        MOVFF   POSTINC0, PREINC1                                               \
        MOVFF   POSTINC0, PREINC1                                               \
        MOVFF   POSTINC0, PREINC1                                               \
        MOVFF   POSTINC0, PREINC1                                               \
        MOVFF   INDF0, PREINC1                                                  \
        MOVFF   FSR0L, PREINC1                                                  \
        MOVFF   FSR0H, PREINC1                                                  \
        /* Store the hardware stack pointer in a temp register before we        \
        modify it. */                                                           \
        MOVFF   STKPTR, FSR0L                                                   \
    _endasm                                                                     \
                                                                                \
        /* Store each address from the hardware stack. */                       \
        ಆಗ( STKPTR > ( uint8_t ) 0 )                             \
        {                                                                       \
            _asm                                                                \
                MOVFF   TOSL, PREINC1                                           \
                MOVFF   TOSH, PREINC1                                           \
                MOVFF   TOSU, PREINC1                                           \
                ತೆಗೆ_3                                                             \
            _endasm                                                             \
        }                                                                       \
                                                                                \
    _asm                                                                        \
        /* Store the number of addresses on the hardware stack (from the        \
        temporary register). */                                                 \
        MOVFF   FSR0L, PREINC1                                                  \
        MOVF    PREINC1, 1, 0                                                   \
    _endasm                                                                     \
                                                                                \
    /* Save the new top of the software stack in the TCB. */                    \
    _asm                                                                        \
        MOVFF   pxCurrentTCB, FSR0L                                             \
        MOVFF   pxCurrentTCB + 1, FSR0H                                         \
        MOVFF   FSR1L, POSTINC0                                                 \
        MOVFF   FSR1H, POSTINC0                                                 \
    _endasm                                                                     \
}
/*-----------------------------------------------------------*/

/*
 * This is the reverse of portSAVE_CONTEXT.  See portSAVE_CONTEXT for more
 * details.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESTORE_CONTEXT()                                                   \
{                                                                               \
    _asm                                                                        \
        /* Set FSR0 to point to pxCurrentTCB->pxTopOfStack. */                  \
        MOVFF   pxCurrentTCB, FSR0L                                             \
        MOVFF   pxCurrentTCB + 1, FSR0H                                         \
                                                                                \
        /* De-reference FSR0 to set the address it holds into FSR1.             \
        (i.e. *( pxCurrentTCB->pxTopOfStack ) ). */                             \
        MOVFF   POSTINC0, FSR1L                                                 \
        MOVFF   POSTINC0, FSR1H                                                 \
                                                                                \
        /* How many return addresses are there on the hardware stack?  Discard  \
        the first byte as we are pointing to the next free space. */            \
        MOVFF   POSTDEC1, FSR0L                                                 \
        MOVFF   POSTDEC1, FSR0L                                                 \
    _endasm                                                                     \
                                                                                \
    /* Fill the hardware stack from our software stack. */                      \
    STKPTR = 0;                                                                 \
                                                                                \
    ಆಗ( STKPTR < FSR0L )                                                     \
    {                                                                           \
        _asm                                                                    \
            ತಳ್ಳು_2                                                                \
            MOVF    POSTDEC1, 0, 0                                              \
            MOVWF   TOSU, 0                                                     \
            MOVF    POSTDEC1, 0, 0                                              \
            MOVWF   TOSH, 0                                                     \
            MOVF    POSTDEC1, 0, 0                                              \
            MOVWF   TOSL, 0                                                     \
        _endasm                                                                 \
    }                                                                           \
                                                                                \
    _asm                                                                        \
        /* Restore the .tmpdata and MATH_DATA memory. */                        \
        MOVFF   POSTDEC1, FSR0H                                                 \
        MOVFF   POSTDEC1, FSR0L                                                 \
        MOVFF   POSTDEC1, POSTDEC0                                              \
        MOVFF   POSTDEC1, POSTDEC0                                              \
        MOVFF   POSTDEC1, POSTDEC0                                              \
        MOVFF   POSTDEC1, POSTDEC0                                              \
        MOVFF   POSTDEC1, POSTDEC0                                              \
        MOVFF   POSTDEC1, POSTDEC0                                              \
        MOVFF   POSTDEC1, POSTDEC0                                              \
        MOVFF   POSTDEC1, POSTDEC0                                              \
        MOVFF   POSTDEC1, POSTDEC0                                              \
        MOVFF   POSTDEC1, POSTDEC0                                              \
        MOVFF   POSTDEC1, POSTDEC0                                              \
        MOVFF   POSTDEC1, POSTDEC0                                              \
        MOVFF   POSTDEC1, POSTDEC0                                              \
        MOVFF   POSTDEC1, POSTDEC0                                              \
        MOVFF   POSTDEC1, POSTDEC0                                              \
        MOVFF   POSTDEC1, POSTDEC0                                              \
        MOVFF   POSTDEC1, POSTDEC0                                              \
        MOVFF   POSTDEC1, POSTDEC0                                              \
        MOVFF   POSTDEC1, POSTDEC0                                              \
        MOVFF   POSTDEC1, INDF0                                                 \
        /* Restore the other registers forming the tasks context. */            \
        MOVFF   POSTDEC1, PCLATH                                                \
        MOVFF   POSTDEC1, PCLATU                                                \
        MOVFF   POSTDEC1, PRODL                                                 \
        MOVFF   POSTDEC1, PRODH                                                 \
        MOVFF   POSTDEC1, TBLPTRL                                               \
        MOVFF   POSTDEC1, TBLPTRH                                               \
        MOVFF   POSTDEC1, TBLPTRU                                               \
        MOVFF   POSTDEC1, TABLAT                                                \
        MOVFF   POSTDEC1, FSR0H                                                 \
        MOVFF   POSTDEC1, FSR0L                                                 \
        MOVFF   POSTDEC1, FSR2H                                                 \
        MOVFF   POSTDEC1, FSR2L                                                 \
        MOVFF   POSTDEC1, BSR                                                   \
        /* The next byte is the INTCON register.  Read this into WREG as some   \
        manipulation is required. */                                            \
        MOVFF   POSTDEC1, WREG                                                  \
    _endasm                                                                     \
                                                                                \
    /* From the INTCON register, only the interrupt enable bits form part       \
    of the tasks context.  It is perfectly legitimate for another task to       \
    have modified any other bits.  We therefore only restore the top two bits.  \
    */                                                                          \
    ಆದರೆ( WREG & ಪೋರ್ಟ್_GLOBAL_ಅಡಚಣೆ_FLAG )                                      \
    {                                                                           \
        _asm                                                                    \
            MOVFF   POSTDEC1, ಸ್ಥಿತಿ_3                                            \
            MOVFF   POSTDEC1, WREG                                              \
            /* Return enabling interrupts. */                                   \
            RETFIE  0                                                           \
        _endasm                                                                 \
    }                                                                           \
    ಇಲ್ಲದಿದ್ದರೆ                                                                        \
    {                                                                           \
        _asm                                                                    \
            MOVFF   POSTDEC1, ಸ್ಥಿತಿ_3                                            \
            MOVFF   POSTDEC1, WREG                                              \
            /* Return without effecting interrupts.  The context may have       \
            been saved from a critical region. */                               \
            RETURN  0                                                           \
        _endasm                                                                 \
    }                                                                           \
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t *px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t *px_ತುದಿ_ದ_ರಾಶಿ, TaskFunction_t px_ಸಂಕೇತ, ಶೂನ್ಯ *pvParameters )
{
uint32_t ul_ವಿಳಾಸ;
uint8_t uc_ಖಂಡ;

    /* Place a few bytes of known values on the bottom of the stack.
    This is just useful for debugging. */

    *px_ತುದಿ_ದ_ರಾಶಿ = 0x11;
    px_ತುದಿ_ದ_ರಾಶಿ++;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x22;
    px_ತುದಿ_ದ_ರಾಶಿ++;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x33;
    px_ತುದಿ_ದ_ರಾಶಿ++;


    /* Simulate how the stack would look after a call to vPortYield() generated
    by the compiler.

    First store the function parameters.  This is where the task will expect to
    find them when it starts running. */
    ul_ವಿಳಾಸ = ( uint32_t ) pvParameters;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ( ul_ವಿಳಾಸ & ( uint32_t ) 0x00ff );
    px_ತುದಿ_ದ_ರಾಶಿ++;

    ul_ವಿಳಾಸ >>= 8;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ( ul_ವಿಳಾಸ & ( uint32_t ) 0x00ff );
    px_ತುದಿ_ದ_ರಾಶಿ++;

    /* Next we just leave a space.  When a context is saved the stack pointer
    is incremented before it is used so as not to corrupt whatever the stack
    pointer is actually pointing to.  This is especially necessary during
    function epilogue code generated by the compiler. */
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x44;
    px_ತುದಿ_ದ_ರಾಶಿ++;

    /* Next are all the registers that form part of the task context. */

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x66; /* WREG. */
    px_ತುದಿ_ದ_ರಾಶಿ++;

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xcc; /* Status. */
    px_ತುದಿ_ದ_ರಾಶಿ++;

    /* INTCON is saved with interrupts enabled. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_INITAL_ಅಡಚಣೆ_STATE; /* INTCON */
    px_ತುದಿ_ದ_ರಾಶಿ++;

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x11; /* BSR. */
    px_ತುದಿ_ದ_ರಾಶಿ++;

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x22; /* FSR2L. */
    px_ತುದಿ_ದ_ರಾಶಿ++;

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x33; /* FSR2H. */
    px_ತುದಿ_ದ_ರಾಶಿ++;

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x44; /* FSR0L. */
    px_ತುದಿ_ದ_ರಾಶಿ++;

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x55; /* FSR0H. */
    px_ತುದಿ_ದ_ರಾಶಿ++;

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x66; /* TABLAT. */
    px_ತುದಿ_ದ_ರಾಶಿ++;

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x00; /* TBLPTRU. */
    px_ತುದಿ_ದ_ರಾಶಿ++;

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x88; /* TBLPTRUH. */
    px_ತುದಿ_ದ_ರಾಶಿ++;

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x99; /* TBLPTRUL. */
    px_ತುದಿ_ದ_ರಾಶಿ++;

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xaa; /* PRODH. */
    px_ತುದಿ_ದ_ರಾಶಿ++;

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xbb; /* PRODL. */
    px_ತುದಿ_ದ_ರಾಶಿ++;

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x00; /* PCLATU. */
    px_ತುದಿ_ದ_ರಾಶಿ++;

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x00; /* PCLATH. */
    px_ತುದಿ_ದ_ರಾಶಿ++;

    /* Next the .tmpdata and MATH_DATA sections. */
    ಗಾಗಿ( uc_ಖಂಡ = 0; uc_ಖಂಡ <= ಪೋರ್ಟ್_COMPILER_MANAGED_ಸ್ಮರಣೆ_ಗಾತ್ರ; uc_ಖಂಡ++ )
    {
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) uc_ಖಂಡ;
        *px_ತುದಿ_ದ_ರಾಶಿ++;
    }

    /* Store the top of the global data section. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_COMPILER_MANAGED_ಸ್ಮರಣೆ_ಗಾತ್ರ; /* Low. */
    px_ತುದಿ_ದ_ರಾಶಿ++;

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x00; /* High. */
    px_ತುದಿ_ದ_ರಾಶಿ++;

    /* The only function return address so far is the address of the
    task. */
    ul_ವಿಳಾಸ = ( uint32_t ) px_ಸಂಕೇತ;

    /* TOS low. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ( ul_ವಿಳಾಸ & ( uint32_t ) 0x00ff );
    px_ತುದಿ_ದ_ರಾಶಿ++;
    ul_ವಿಳಾಸ >>= 8;

    /* TOS high. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ( ul_ವಿಳಾಸ & ( uint32_t ) 0x00ff );
    px_ತುದಿ_ದ_ರಾಶಿ++;
    ul_ವಿಳಾಸ >>= 8;

    /* TOS even higher. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ( ul_ವಿಳಾಸ & ( uint32_t ) 0x00ff );
    px_ತುದಿ_ದ_ರಾಶಿ++;

    /* Store the number of return addresses on the hardware stack - so far only
    the address of the task entry point. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 1;
    px_ತುದಿ_ದ_ರಾಶಿ++;

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    /* Setup a timer for the tick ISR is using the preemptive scheduler. */
    prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    /* Restore the context of the first task to run. */
    ಪೋರ್ಟ್_RESTORE_CONTEXT();

    /* Should not get here.  Use the function name to stop compiler warnings. */
    ( ಶೂನ್ಯ ) prv_ಕೆಳಗಿನ_ಅಡಚಣೆ;
    ( ಶೂನ್ಯ ) prvTickISR;

    ಹಿಂತಿರುಗಿ pdTRUE;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* It is unlikely that the scheduler for the PIC port will get stopped
    once running.  If required disable the tick interrupt here, then return
    to xPortStartScheduler(). */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch.  This is similar to the tick context switch,
 * but does not increment the tick count.  It must be identical to the
 * tick context switch in how it stores the stack of a task.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ )
{
    /* This can get called with interrupts either enabled or disabled.  We
    will save the INTCON register with the interrupt enable bits unmodified. */
    ಪೋರ್ಟ್_SAVE_CONTEXT( ಪೋರ್ಟ್_INTERRUPTS_UNCHANGED );

    /* Switch to the highest priority task that is ready to run. */
    vTaskSwitchContext();

    /* Start executing the task we have just switched to. */
    ಪೋರ್ಟ್_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

/*
 * Vector for ISR.  Nothing here must alter any registers!
 */
#ಸೂಚನೆ ಸಂಕೇತ_2 ಮೇಲಿನ_ಸದಿಶ=0x08
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಕೆಳಗಿನ_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    /* Was the interrupt the tick? */
    ಆದರೆ( PIR1bits.CCP1IF )
    {
        _asm
            ಹೋಗು prvTickISR
        _endasm
    }

    /* Was the interrupt a byte being received? */
    ಆದರೆ( PIR1bits.RCIF )
    {
        _asm
            ಹೋಗು vSerialRxISR
        _endasm
    }

    /* Was the interrupt the Tx register becoming empty? */
    ಆದರೆ( PIR1bits.TXIF )
    {
        ಆದರೆ( PIE1bits.TXIE )
        {
            _asm
                ಹೋಗು vSerialTxISR
            _endasm
        }
    }
}
#ಸೂಚನೆ ಸಂಕೇತ_2

/*-----------------------------------------------------------*/

/*
 * ISR for the tick.
 * This increments the tick count and, if using the preemptive scheduler,
 * performs a context switch.  This must be identical to the manual
 * context switch in how it stores the context of a task.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvTickISR( ಶೂನ್ಯ )
{
    /* Interrupts must have been enabled for the ISR to fire, so we have to
    save the context with interrupts enabled. */
    ಪೋರ್ಟ್_SAVE_CONTEXT( ಪೋರ್ಟ್_GLOBAL_ಅಡಚಣೆ_FLAG );
    PIR1bits.CCP1IF = 0;

    /* Maintain the tick count. */
    ಆದರೆ( xTaskIncrementTick() != pdFALSE )
    {
        /* Switch to the highest priority task that is ready to run. */
        vTaskSwitchContext();
    }

    ಪೋರ್ಟ್_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

/*
 * Setup a timer for a regular tick.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
ಸ್ಥಿರಾಂಕ uint32_t ul_Const_Compare_ಮೌಲ್ಯ = ( ( configCPU_CLOCK_HZ / ಪೋರ್ಟ್_TIMER_FOSC_SCALE ) / config_TICK_ದರ_HZ );
uint32_t ul_Compare_ಮೌಲ್ಯ;
uint8_t ucByte;

    /* Interrupts are disabled when this function is called.

    Setup CCP1 to provide the tick interrupt using a compare match on timer
    1.

    Clear the time count then setup timer. */
    TMR1H = ( uint8_t ) 0x00;
    TMR1L = ( uint8_t ) 0x00;

    /* Set the compare match value. */
    ul_Compare_ಮೌಲ್ಯ = ul_Const_Compare_ಮೌಲ್ಯ;
    CCPR1L = ( uint8_t ) ( ul_Compare_ಮೌಲ್ಯ & ( uint32_t ) 0xff );
    ul_Compare_ಮೌಲ್ಯ >>= ( uint32_t ) 8;
    CCPR1H = ( uint8_t ) ( ul_Compare_ಮೌಲ್ಯ & ( uint32_t ) 0xff );

    CCP1CONbits.CCP1M0 = ಪೋರ್ಟ್_ಬಿಟ್_ಗಣ;   /*< Compare match mode. */
    CCP1CONbits.CCP1M1 = ಪೋರ್ಟ್_ಬಿಟ್_ಗಣ;   /*< Compare match mode. */
    CCP1CONbits.CCP1M2 = ಪೋರ್ಟ್_ಬಿಟ್_CLEAR; /*< Compare match mode. */
    CCP1CONbits.CCP1M3 = ಪೋರ್ಟ್_ಬಿಟ್_ಗಣ;   /*< Compare match mode. */
    PIE1bits.CCP1IE = ಪೋರ್ಟ್_ಬಿಟ್_ಗಣ;      /*< Interrupt enable. */

    /* We are only going to use the global interrupt bit, so set the peripheral
    bit to true. */
    INTCONbits.GIEL = ಪೋರ್ಟ್_ಬಿಟ್_ಗಣ;

    /* Provided library function for setting up the timer that will produce the
    tick. */
    OpenTimer1( T1_16_ಬಿಟ್_RW & T1_ಮೂಲ_INT & T1_PS_1_1 & T1_CCP1_T3_CCP2 );
}
