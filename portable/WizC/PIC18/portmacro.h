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
Changes from V3.0.0

Changes from V3.0.1
*/
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PORTMACRO_H
#ವ್ಯಾಖ್ಯಾನಿಸು PORTMACRO_H

#ಆದರೆ !defined(_SERIES) || _SERIES != 18
    #ದೋಷ "WizC supports FreeRTOS on the Microchip PIC18-series only"
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ !defined(QUICKCALL) || QUICKCALL != 1
    #ದೋಷ "QuickCall must be enabled (see ProjectOptions/Optimisations)"
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <pic.h>

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CHAR        ಅಕ್ಷರ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FLOAT       ದಶಮಾಂಶ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DOUBLE      ಪೋರ್ಟ್_FLOAT
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_LONG        ದೀರ್ಘ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SHORT       ಗಿಡ್ಡ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_TYPE  uint8_t
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ತಳ_TYPE   ಅಕ್ಷರ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_ರಾಶಿ_TYPE ರಾಶಿ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆಯುಳ್ಳ ಅಕ್ಷರ ತಳ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ UBaseType_t;


#ಆದರೆ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_16_ಬಿಟ್ಟುಗಳು )
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint16_t TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY ( TickType_t )    ( 0xFFFF )
#ಅಥವಾಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_32_ಬಿಟ್ಟುಗಳು )
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY ( TickType_t )    ( 0xFFFFFFFFUL )
#ಇಲ್ಲದಿದ್ದರೆ
    #ದೋಷ config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು ಗಣ ಗಮ್ಯ unsupported tick type ಅಗಲ.
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_BYTE_ALIGNMENT          1

/*-----------------------------------------------------------*/

/*
 * Constant used for context switch macro when we require the interrupt
 * enable state to be forced when the interrupted task is switched back in.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INTERRUPTS_FORCED               (0x01)

/*
 * Constant used for context switch macro when we require the interrupt
 * enable state to be unchanged when the interrupted task is switched back in.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INTERRUPTS_UNCHANGED            (0x00)

/* Initial interrupt enable state for newly created tasks.  This value is
 * used when a task switches in for the first time.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INTERRUPTS_INITIAL_STATE        (ಪೋರ್ಟ್_INTERRUPTS_FORCED)

/*
 * Macros to modify the global interrupt enable bit in INTCON.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS()    \
    ಮಾಡು                              \
    {                               \
        bGIE=0;                     \
    } ಆಗ(bGIE)   // MicroChip recommends this check!

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_INTERRUPTS()     \
    ಮಾಡು                              \
    {                               \
        bGIE=1;                     \
    } ಆಗ(0)

/*-----------------------------------------------------------*/

/*
 * Critical section macros.
 */
ಬಾಹ್ಯ uint8_t ucCriticalNesting;

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_CRITICAL_SECTION_NESTING     ( ( uint8_t ) 0 )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL()                                        \
    ಮಾಡು                                                              \
    {                                                               \
        ಪೋರ್ಟ್_DISABLE_INTERRUPTS();                                   \
                                                                    \
        /*                                                          \
         * Now interrupts are disabled ucCriticalNesting            \
         * can be accessed directly. Increment                      \
         * ucCriticalNesting to keep a count of how                 \
         * many times portENTER_CRITICAL() has been called.         \
         */                                                         \
        ucCriticalNesting++;                                        \
    } ಆಗ(0)

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL()                                         \
    ಮಾಡು                                                              \
    {                                                               \
        ಆದರೆ(ucCriticalNesting > ಪೋರ್ಟ್_NO_CRITICAL_SECTION_NESTING)     \
        {                                                           \
            /*                                                      \
             * Decrement the nesting count as we are leaving a      \
             * critical section.                                    \
             */                                                     \
            ucCriticalNesting--;                                    \
        }                                                           \
                                                                    \
        /*                                                          \
         * If the nesting level has reached zero then               \
         * interrupts should be re-enabled.                         \
         */                                                         \
        ಆದರೆ( ucCriticalNesting == ಪೋರ್ಟ್_NO_CRITICAL_SECTION_NESTING )  \
        {                                                           \
            ಪೋರ್ಟ್_ENABLE_INTERRUPTS();                                \
        }                                                           \
    } ಆಗ(0)

/*-----------------------------------------------------------*/

/*
 * The minimal stacksize is calculated on the first reference of
 * portMINIMAL_STACK_SIZE. Some input to this calculation is
 * compile time determined, other input is port-defined (see port.c)
 */
ಬಾಹ್ಯ uint16_t us_ಪೋರ್ಟ್_CALCULATE_ಕನಿಷ್ಠತಮ_ರಾಶಿ_ಗಾತ್ರ( ಶೂನ್ಯ );
ಬಾಹ್ಯ uint16_t us_Calc_Min_ರಾಶಿ_ಗಾತ್ರ;

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕನಿಷ್ಠತಮ_ರಾಶಿ_ಗಾತ್ರ                  \
    ((us_Calc_Min_ರಾಶಿ_ಗಾತ್ರ == 0)                  \
        ? us_ಪೋರ್ಟ್_CALCULATE_ಕನಿಷ್ಠತಮ_ರಾಶಿ_ಗಾತ್ರ()  \
        : us_Calc_Min_ರಾಶಿ_ಗಾತ್ರ )

/*
 * WizC uses a downgrowing stack
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_GROWTH            ( -1 )

/*-----------------------------------------------------------*/

/*
 * Macro's that pushes all the registers that make up the context of a task onto
 * the stack, then saves the new top of stack into the TCB. TOSU and TBLPTRU
 * are only saved/restored on devices with more than 64kB (32k Words) ROM.
 *
 * The stackpointer is held by WizC in FSR2 and points to the first free byte.
 * WizC uses a "downgrowing" stack. There is no framepointer.
 *
 * We keep track of the interruptstatus using ucCriticalNesting. When this
 * value equals zero, interrupts have to be enabled upon exit from the
 * portRESTORE_CONTEXT macro.
 *
 * If this is called from an ISR then the interrupt enable bits must have been
 * set for the ISR to ever get called.  Therefore we want to save
 * ucCriticalNesting with value zero. This means the interrupts will again be
 * re-enabled when the interrupted task is switched back in.
 *
 * If this is called from a manual context switch (i.e. from a call to yield),
 * then we want to keep the current value of ucCriticalNesting so it is restored
 * with its current value. This allows a yield from within a critical section.
 *
 * The compiler uses some locations at the bottom of RAM for temporary
 * storage. The compiler may also have been instructed to optimize
 * function-parameters and local variables to global storage. The compiler
 * uses an area called LocOpt for this wizC feature.
 * The total overheadstorage has to be saved in it's entirety as part of
 * a task context. These macro's store/restore from data address 0x0000 to
 * (OVERHEADPAGE0-LOCOPTSIZE+MAXLOCOPTSIZE - 1).
 * OVERHEADPAGE0, LOCOPTSIZE and MAXLOCOPTSIZE are compiler-generated
 * assembler definitions.
 */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SAVE_CONTEXT( uc_ಅಡಚಣೆ_Forced )                       \
    ಮಾಡು                                                              \
    {                                                               \
        ಪೋರ್ಟ್_DISABLE_INTERRUPTS();                                   \
                                                                    \
        _Pragma("asm")                                              \
            ;                                                       \
            ; ತಳ್ಳು_3 the relevant SFR's onto the task's ರಾಶಿ         \
            ;                                                       \
            movff   ಸ್ಥಿತಿ_3,POSTDEC2                                 \
            movff   WREG,POSTDEC2                                   \
            movff   BSR,POSTDEC2                                    \
            movff   PRODH,POSTDEC2                                  \
            movff   PRODL,POSTDEC2                                  \
            movff   FSR0H,POSTDEC2                                  \
            movff   FSR0L,POSTDEC2                                  \
            movff   FSR1H,POSTDEC2                                  \
            movff   FSR1L,POSTDEC2                                  \
            movff   TABLAT,POSTDEC2                                 \
            ಆದರೆ __ROMSIZE > 0x8000                                   \
                movff   TBLPTRU,POSTDEC2                            \
            endif                                                   \
            movff   TBLPTRH,POSTDEC2                                \
            movff   TBLPTRL,POSTDEC2                                \
            ಆದರೆ __ROMSIZE > 0x8000                                   \
                movff   PCLATU,POSTDEC2                             \
            endif                                                   \
            movff   PCLATH,POSTDEC2                                 \
            ;                                                       \
            ; Store the compiler-scratch-area as described above.   \
            ;                                                       \
            movlw   OVERHEADPAGE0-LOCOPTSIZE+MAXLOCOPTSIZE          \
            clrf    FSR0L,ACCESS                                    \
            clrf    FSR0H,ACCESS                                    \
        _rtos_S1:                                                   \
            movff   POSTINC0,POSTDEC2                               \
            decfsz  WREG,W,ACCESS                                   \
            SMARTJUMP _rtos_S1                                      \
            ;                                                       \
            ; Save the pic call/ಹಿಂತಿರುಗಿ-ರಾಶಿ belonging ಗಮ್ಯ the       \
            ; current task by copying it ಗಮ್ಯ the task's software-    \
            ; ರಾಶಿ. We save the hardware ರಾಶಿ ಸೂಚಕ_3 (which      \
            ; is the ಸಂಖ್ಯೆ ದ ವಿಳಾಸಗಳು on the ರಾಶಿ) ಒಳ the       \
            ; W-ನೋಂದಣಿ ಮೊದಲ_2 because we need it later and it      \
            ; is modified ಒಳ the save-loop by executing ತೆಗೆ_2's.      \
            ; After the loop the W-ನೋಂದಣಿ is stored on the        \
            ; ರಾಶಿ, too.                                           \
            ;                                                       \
            movf    STKPTR,W,ACCESS                                 \
            bz      _rtos_s3                                        \
        _rtos_S2:                                                   \
            ಆದರೆ __ROMSIZE > 0x8000                                   \
                movff   TOSU,POSTDEC2                               \
            endif                                                   \
            movff   TOSH,POSTDEC2                                   \
            movff   TOSL,POSTDEC2                                   \
            ತೆಗೆ_2                                                     \
            tstfsz  STKPTR,ACCESS                                   \
            SMARTJUMP _rtos_S2                                      \
        _rtos_s3:                                                   \
            movwf   POSTDEC2,ACCESS                                 \
            ;                                                       \
            ; ಮುಂದಿನ the ಮೌಲ್ಯ ಗಾಗಿ ucCriticalNesting ಬಳಸಿದ by the      \
            ; task is stored on the ರಾಶಿ. When                     \
            ; (uc_ಅಡಚಣೆ_Forced == ಪೋರ್ಟ್_INTERRUPTS_FORCED), we save \
            ; it as 0 (ಪೋರ್ಟ್_NO_CRITICAL_SECTION_NESTING).            \
            ;                                                       \
            ಆದರೆ uc_ಅಡಚಣೆ_Forced == ಪೋರ್ಟ್_INTERRUPTS_FORCED           \
                clrf POSTDEC2,ACCESS                                \
            ಇಲ್ಲದಿದ್ದರೆ                                                    \
                movff   ucCriticalNesting,POSTDEC2                  \
            endif                                                   \
            ;                                                       \
            ; Save the new ತುದಿ_2 ದ the software ರಾಶಿ ಒಳ the TCB.    \
            ;                                                       \
            movff   pxCurrentTCB,FSR0L                              \
            movff   pxCurrentTCB+1,FSR0H                            \
            movff   FSR2L,POSTINC0                                  \
            movff   FSR2H,POSTINC0                                  \
        _Pragma("asmend")                                           \
    } ಆಗ(0)

/************************************************************/

/*
 * This is the reverse of portSAVE_CONTEXT.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESTORE_CONTEXT()                                       \
    ಮಾಡು                                                              \
    {                                                               \
        _Pragma("asm")                                              \
            ;                                                       \
            ; ಗಣ_2 FSR0 ಗಮ್ಯ ಬಿಂದು_2 ಗಮ್ಯ pxCurrentTCB->px_ತುದಿ_ದ_ರಾಶಿ.      \
            ;                                                       \
            movff   pxCurrentTCB,FSR0L                              \
            movff   pxCurrentTCB+1,FSR0H                            \
            ;                                                       \
            ; De-reference FSR0 ಗಮ್ಯ ಗಣ the ವಿಳಾಸ_2 it holds into    \
            ; FSR2 (i.e. *( pxCurrentTCB->px_ತುದಿ_ದ_ರಾಶಿ ) ). FSR2    \
            ; is ಬಳಸಿದ by wizC as stackpointer.                      \
            ;                                                       \
            movff   POSTINC0,FSR2L                                  \
            movff   POSTINC0,FSR2H                                  \
            ;                                                       \
            ; ಮುಂದಿನ, the ಮೌಲ್ಯ ಗಾಗಿ ucCriticalNesting ಬಳಸಿದ by the     \
            ; task is retrieved from the ರಾಶಿ.                     \
            ;                                                       \
            movff   PREINC2,ucCriticalNesting                       \
            ;                                                       \
            ; Rebuild the pic call/ಹಿಂತಿರುಗಿ-ರಾಶಿ. The ಸಂಖ್ಯೆ ದ      \
            ; ಹಿಂತಿರುಗಿ ವಿಳಾಸಗಳು is the ಮುಂದಿನ_2 ಅಂಶ on the task ರಾಶಿ.  \
            ; Save this ಸಂಖ್ಯೆ ಒಳ PRODL. Then fetch the ವಿಳಾಸಗಳು   \
            ; and store them on the hardwarestack.                  \
            ; The datasheets say we can't use movff ಇಲ್ಲಿ...         \
            ;                                                       \
            movff   PREINC2,PRODL   // Use PRODL as tempregister    \
            clrf    STKPTR,ACCESS                                   \
        _rtos_R1:                                                   \
            ತಳ್ಳು                                                    \
            movf    PREINC2,W,ACCESS                                \
            movwf   TOSL,ACCESS                                     \
            movf    PREINC2,W,ACCESS                                \
            movwf   TOSH,ACCESS                                     \
            ಆದರೆ __ROMSIZE > 0x8000                                   \
                movf    PREINC2,W,ACCESS                            \
                movwf   TOSU,ACCESS                                 \
            ಇಲ್ಲದಿದ್ದರೆ                                                    \
                clrf    TOSU,ACCESS                                 \
            endif                                                   \
            decfsz  PRODL,F,ACCESS                                  \
            SMARTJUMP _rtos_R1                                      \
            ;                                                       \
            ; Restore the compiler's working storage area ಗಮ್ಯ ಪುಟ 0 \
            ;                                                       \
            movlw   OVERHEADPAGE0-LOCOPTSIZE+MAXLOCOPTSIZE          \
            movwf   FSR0L,ACCESS                                    \
            clrf    FSR0H,ACCESS                                    \
        _rtos_R2:                                                   \
            decf    FSR0L,F,ACCESS                                  \
            movff   PREINC2,INDF0                                   \
            tstfsz  FSR0L,ACCESS                                    \
            SMARTJUMP _rtos_R2                                      \
            ;                                                       \
            ; Restore the sfr's forming the tasks context.          \
            ; We cannot yet restore bsr, w and status because       \
            ; we need these registers ಗಾಗಿ a final test.             \
            ;                                                       \
            movff   PREINC2,PCLATH                                  \
            ಆದರೆ __ROMSIZE > 0x8000                                   \
                movff   PREINC2,PCLATU                              \
            ಇಲ್ಲದಿದ್ದರೆ                                                    \
                clrf    PCLATU,ACCESS                               \
            endif                                                   \
            movff   PREINC2,TBLPTRL                                 \
            movff   PREINC2,TBLPTRH                                 \
            ಆದರೆ __ROMSIZE > 0x8000                                   \
                movff   PREINC2,TBLPTRU                             \
            ಇಲ್ಲದಿದ್ದರೆ                                                    \
                clrf    TBLPTRU,ACCESS                              \
            endif                                                   \
            movff   PREINC2,TABLAT                                  \
            movff   PREINC2,FSR1L                                   \
            movff   PREINC2,FSR1H                                   \
            movff   PREINC2,FSR0L                                   \
            movff   PREINC2,FSR0H                                   \
            movff   PREINC2,PRODL                                   \
            movff   PREINC2,PRODH                                   \
            ;                                                       \
            ; The ಹಿಂತಿರುಗಿ from ಪೋರ್ಟ್_RESTORE_CONTEXT() depends on      \
            ; the ಮೌಲ್ಯ ದ ucCriticalNesting. When it is zero,      \
            ; interrupts need ಗಮ್ಯ be enabled. This is ಮುಗಿದ ಮೂಲಕ a     \
            ; retfie instruction because we need the                \
            ; ಅಡಚಣೆ-enabling and the ಹಿಂತಿರುಗಿ ಗಮ್ಯ the restored     \
            ; task ಗಮ್ಯ be uninterruptible.                           \
            ; Because bsr, status and W are affected by the test    \
            ; they are restored after the test.                     \
            ;                                                       \
            movlb   ucCriticalNesting>>8                            \
            tstfsz  ucCriticalNesting,BANKED                        \
            SMARTJUMP _rtos_R4                                      \
        _rtos_R3:                                                   \
            movff   PREINC2,BSR                                     \
            movff   PREINC2,WREG                                    \
            movff   PREINC2,ಸ್ಥಿತಿ_3                                  \
            retfie  0       ; Return enabling interrupts            \
        _rtos_R4:                                                   \
            movff   PREINC2,BSR                                     \
            movff   PREINC2,WREG                                    \
            movff   PREINC2,ಸ್ಥಿತಿ_3                                  \
            ಹಿಂತಿರುಗಿ  0       ; Return without affecting interrupts   \
        _Pragma("asmend")                                           \
    } ಆಗ(0)

/*-----------------------------------------------------------*/

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_PERIOD_MS  ( ( TickType_t ) 1000 / config_TICK_ದರ_HZ )

/*-----------------------------------------------------------*/

ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ );
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD()             v_ಪೋರ್ಟ್_Yield()

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NOP()   _Pragma("asm")                                  \
                        nop                                         \
                    _Pragma("asmend")

/*-----------------------------------------------------------*/

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION( xFunction, pvParameters )        \
    ಶೂನ್ಯ pointed xFunction( ಶೂನ್ಯ *pvParameters )        \
    _Pragma(asmfunc xFunction)

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION_PROTO     ಪೋರ್ಟ್_TASK_FUNCTION
/*-----------------------------------------------------------*/


#ವ್ಯಾಖ್ಯಾನಿಸು ಅಸ್ಥಿರ
#ವ್ಯಾಖ್ಯಾನಿಸು ನೋಂದಣಿ

#ಆದರೆ_ಅಂತ್ಯ /* PORTMACRO_H */
