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
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PORTMACRO_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMACRO_H

#ਜੇ !defined(_SERIES) || _SERIES != 18
    #ਗਲਤੀ "WizC supports FreeRTOS on the Microchip PIC18-series only"
#ਜੇ_ਅੰਤ

#ਜੇ !defined(QUICKCALL) || QUICKCALL != 1
    #ਗਲਤੀ "QuickCall must be enabled (see ProjectOptions/Optimisations)"
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <pic.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHAR        ਅੱਖਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FLOAT       ਦਸ਼ਮਲਵ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DOUBLE      ਪੋਰਟ_FLOAT
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_LONG        ਲੰਮਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SHORT       ਛੋਟਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_TYPE  uint8_t
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅਧਾਰ_TYPE   ਅੱਖਰ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੋਰਟ_ਢੇਰ_TYPE ਢੇਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਨਿਸ਼ਾਨੀਵਾਲਾ ਅੱਖਰ ਅਧਾਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ UBaseType_t;


#ਜੇ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_16_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint16_t TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY ( TickType_t )    ( 0xFFFF )
#ਜਾਂਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_32_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY ( TickType_t )    ( 0xFFFFFFFFUL )
#ਨਹੀਂਤਾਂ
    #ਗਲਤੀ config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ ਸੈੱਟ ਮੰਜ਼ਿਲ unsupported tick type ਚੌੜਾਈ.
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_BYTE_ALIGNMENT          1

/*-----------------------------------------------------------*/

/*
 * Constant used for context switch macro when we require the interrupt
 * enable state to be forced when the interrupted task is switched back in.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INTERRUPTS_FORCED               (0x01)

/*
 * Constant used for context switch macro when we require the interrupt
 * enable state to be unchanged when the interrupted task is switched back in.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INTERRUPTS_UNCHANGED            (0x00)

/* Initial interrupt enable state for newly created tasks.  This value is
 * used when a task switches in for the first time.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INTERRUPTS_INITIAL_STATE        (ਪੋਰਟ_INTERRUPTS_FORCED)

/*
 * Macros to modify the global interrupt enable bit in INTCON.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DISABLE_INTERRUPTS()    \
    ਕਰੋ                              \
    {                               \
        bGIE=0;                     \
    } ਜਦੋਂ(bGIE)   // MicroChip recommends this check!

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENABLE_INTERRUPTS()     \
    ਕਰੋ                              \
    {                               \
        bGIE=1;                     \
    } ਜਦੋਂ(0)

/*-----------------------------------------------------------*/

/*
 * Critical section macros.
 */
ਬਾਹਰੀ uint8_t ucCriticalNesting;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NO_CRITICAL_SECTION_NESTING     ( ( uint8_t ) 0 )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL()                                        \
    ਕਰੋ                                                              \
    {                                                               \
        ਪੋਰਟ_DISABLE_INTERRUPTS();                                   \
                                                                    \
        /*                                                          \
         * Now interrupts are disabled ucCriticalNesting            \
         * can be accessed directly. Increment                      \
         * ucCriticalNesting to keep a count of how                 \
         * many times portENTER_CRITICAL() has been called.         \
         */                                                         \
        ucCriticalNesting++;                                        \
    } ਜਦੋਂ(0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL()                                         \
    ਕਰੋ                                                              \
    {                                                               \
        ਜੇ(ucCriticalNesting > ਪੋਰਟ_NO_CRITICAL_SECTION_NESTING)     \
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
        ਜੇ( ucCriticalNesting == ਪੋਰਟ_NO_CRITICAL_SECTION_NESTING )  \
        {                                                           \
            ਪੋਰਟ_ENABLE_INTERRUPTS();                                \
        }                                                           \
    } ਜਦੋਂ(0)

/*-----------------------------------------------------------*/

/*
 * The minimal stacksize is calculated on the first reference of
 * portMINIMAL_STACK_SIZE. Some input to this calculation is
 * compile time determined, other input is port-defined (see port.c)
 */
ਬਾਹਰੀ uint16_t us_ਪੋਰਟ_CALCULATE_ਨਿਊਨਤਮ_ਢੇਰ_ਮਾਪ( ਖਾਲੀ );
ਬਾਹਰੀ uint16_t us_Calc_Min_ਢੇਰ_ਮਾਪ;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਨਿਊਨਤਮ_ਢੇਰ_ਮਾਪ                  \
    ((us_Calc_Min_ਢੇਰ_ਮਾਪ == 0)                  \
        ? us_ਪੋਰਟ_CALCULATE_ਨਿਊਨਤਮ_ਢੇਰ_ਮਾਪ()  \
        : us_Calc_Min_ਢੇਰ_ਮਾਪ )

/*
 * WizC uses a downgrowing stack
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_GROWTH            ( -1 )

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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SAVE_CONTEXT( uc_ਰੁਕਾਵਟ_Forced )                       \
    ਕਰੋ                                                              \
    {                                                               \
        ਪੋਰਟ_DISABLE_INTERRUPTS();                                   \
                                                                    \
        _Pragma("asm")                                              \
            ;                                                       \
            ; ਧੱਕੋ_3 the relevant SFR's onto the task's ਢੇਰ         \
            ;                                                       \
            movff   ਸਥਿਤੀ_2,POSTDEC2                                 \
            movff   WREG,POSTDEC2                                   \
            movff   BSR,POSTDEC2                                    \
            movff   PRODH,POSTDEC2                                  \
            movff   PRODL,POSTDEC2                                  \
            movff   FSR0H,POSTDEC2                                  \
            movff   FSR0L,POSTDEC2                                  \
            movff   FSR1H,POSTDEC2                                  \
            movff   FSR1L,POSTDEC2                                  \
            movff   TABLAT,POSTDEC2                                 \
            ਜੇ __ROMSIZE > 0x8000                                   \
                movff   TBLPTRU,POSTDEC2                            \
            endif                                                   \
            movff   TBLPTRH,POSTDEC2                                \
            movff   TBLPTRL,POSTDEC2                                \
            ਜੇ __ROMSIZE > 0x8000                                   \
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
            ; Save the pic call/ਵਾਪਸ-ਢੇਰ belonging ਮੰਜ਼ਿਲ the       \
            ; current task by copying it ਮੰਜ਼ਿਲ the task's software-    \
            ; ਢੇਰ. We save the hardware ਢੇਰ ਸੂਚਕ_2 (which      \
            ; is the ਸੰਖਿਆ ਦਾ ਪਤੇ on the ਢੇਰ) ਵਿੱਚ_2 the       \
            ; W-ਰਜਿਸਟਰ ਪਹਿਲਾ_2 because we need it later and it      \
            ; is modified ਵਿੱਚ_2 the save-loop by executing ਕੱਢੋ's.      \
            ; After the loop the W-ਰਜਿਸਟਰ is stored on the        \
            ; ਢੇਰ, too.                                           \
            ;                                                       \
            movf    STKPTR,W,ACCESS                                 \
            bz      _rtos_s3                                        \
        _rtos_S2:                                                   \
            ਜੇ __ROMSIZE > 0x8000                                   \
                movff   TOSU,POSTDEC2                               \
            endif                                                   \
            movff   TOSH,POSTDEC2                                   \
            movff   TOSL,POSTDEC2                                   \
            ਕੱਢੋ                                                     \
            tstfsz  STKPTR,ACCESS                                   \
            SMARTJUMP _rtos_S2                                      \
        _rtos_s3:                                                   \
            movwf   POSTDEC2,ACCESS                                 \
            ;                                                       \
            ; ਅਗਲਾ the ਮੁੱਲ ਲਈ ucCriticalNesting ਵਰਤਿਆ by the      \
            ; task is stored on the ਢੇਰ. When                     \
            ; (uc_ਰੁਕਾਵਟ_Forced == ਪੋਰਟ_INTERRUPTS_FORCED), we save \
            ; it as 0 (ਪੋਰਟ_NO_CRITICAL_SECTION_NESTING).            \
            ;                                                       \
            ਜੇ uc_ਰੁਕਾਵਟ_Forced == ਪੋਰਟ_INTERRUPTS_FORCED           \
                clrf POSTDEC2,ACCESS                                \
            ਨਹੀਂਤਾਂ                                                    \
                movff   ucCriticalNesting,POSTDEC2                  \
            endif                                                   \
            ;                                                       \
            ; Save the new ਸਿਖਰ_2 ਦਾ the software ਢੇਰ ਵਿੱਚ_2 the TCB.    \
            ;                                                       \
            movff   pxCurrentTCB,FSR0L                              \
            movff   pxCurrentTCB+1,FSR0H                            \
            movff   FSR2L,POSTINC0                                  \
            movff   FSR2H,POSTINC0                                  \
        _Pragma("asmend")                                           \
    } ਜਦੋਂ(0)

/************************************************************/

/*
 * This is the reverse of portSAVE_CONTEXT.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESTORE_CONTEXT()                                       \
    ਕਰੋ                                                              \
    {                                                               \
        _Pragma("asm")                                              \
            ;                                                       \
            ; ਸੈੱਟ_2 FSR0 ਮੰਜ਼ਿਲ ਬਿੰਦੂ_2 ਮੰਜ਼ਿਲ pxCurrentTCB->px_ਸਿਖਰ_ਦਾ_ਢੇਰ.      \
            ;                                                       \
            movff   pxCurrentTCB,FSR0L                              \
            movff   pxCurrentTCB+1,FSR0H                            \
            ;                                                       \
            ; De-reference FSR0 ਮੰਜ਼ਿਲ ਸੈੱਟ the ਪਤਾ_2 it holds into    \
            ; FSR2 (i.e. *( pxCurrentTCB->px_ਸਿਖਰ_ਦਾ_ਢੇਰ ) ). FSR2    \
            ; is ਵਰਤਿਆ by wizC as stackpointer.                      \
            ;                                                       \
            movff   POSTINC0,FSR2L                                  \
            movff   POSTINC0,FSR2H                                  \
            ;                                                       \
            ; ਅਗਲਾ, the ਮੁੱਲ ਲਈ ucCriticalNesting ਵਰਤਿਆ by the     \
            ; task is retrieved from the ਢੇਰ.                     \
            ;                                                       \
            movff   PREINC2,ucCriticalNesting                       \
            ;                                                       \
            ; Rebuild the pic call/ਵਾਪਸ-ਢੇਰ. The ਸੰਖਿਆ ਦਾ      \
            ; ਵਾਪਸ ਪਤੇ is the ਅਗਲਾ_2 ਵਸਤੂ_2 on the task ਢੇਰ.  \
            ; Save this ਸੰਖਿਆ ਵਿੱਚ_2 PRODL. Then fetch the ਪਤੇ   \
            ; and store them on the hardwarestack.                  \
            ; The datasheets say we can't use movff ਇੱਥੇ...         \
            ;                                                       \
            movff   PREINC2,PRODL   // Use PRODL as tempregister    \
            clrf    STKPTR,ACCESS                                   \
        _rtos_R1:                                                   \
            ਧੱਕੋ                                                    \
            movf    PREINC2,W,ACCESS                                \
            movwf   TOSL,ACCESS                                     \
            movf    PREINC2,W,ACCESS                                \
            movwf   TOSH,ACCESS                                     \
            ਜੇ __ROMSIZE > 0x8000                                   \
                movf    PREINC2,W,ACCESS                            \
                movwf   TOSU,ACCESS                                 \
            ਨਹੀਂਤਾਂ                                                    \
                clrf    TOSU,ACCESS                                 \
            endif                                                   \
            decfsz  PRODL,F,ACCESS                                  \
            SMARTJUMP _rtos_R1                                      \
            ;                                                       \
            ; Restore the compiler's working storage area ਮੰਜ਼ਿਲ ਪੰਨਾ 0 \
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
            ; we need these registers ਲਈ a final test.             \
            ;                                                       \
            movff   PREINC2,PCLATH                                  \
            ਜੇ __ROMSIZE > 0x8000                                   \
                movff   PREINC2,PCLATU                              \
            ਨਹੀਂਤਾਂ                                                    \
                clrf    PCLATU,ACCESS                               \
            endif                                                   \
            movff   PREINC2,TBLPTRL                                 \
            movff   PREINC2,TBLPTRH                                 \
            ਜੇ __ROMSIZE > 0x8000                                   \
                movff   PREINC2,TBLPTRU                             \
            ਨਹੀਂਤਾਂ                                                    \
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
            ; The ਵਾਪਸ from ਪੋਰਟ_RESTORE_CONTEXT() depends on      \
            ; the ਮੁੱਲ ਦਾ ucCriticalNesting. When it is zero,      \
            ; interrupts need ਮੰਜ਼ਿਲ be enabled. This is ਪੂਰਾ ਰਾਹੀਂ a     \
            ; retfie instruction because we need the                \
            ; ਰੁਕਾਵਟ-enabling and the ਵਾਪਸ ਮੰਜ਼ਿਲ the restored     \
            ; task ਮੰਜ਼ਿਲ be uninterruptible.                           \
            ; Because bsr, status and W are affected by the test    \
            ; they are restored after the test.                     \
            ;                                                       \
            movlb   ucCriticalNesting>>8                            \
            tstfsz  ucCriticalNesting,BANKED                        \
            SMARTJUMP _rtos_R4                                      \
        _rtos_R3:                                                   \
            movff   PREINC2,BSR                                     \
            movff   PREINC2,WREG                                    \
            movff   PREINC2,ਸਥਿਤੀ_2                                  \
            retfie  0       ; Return enabling interrupts            \
        _rtos_R4:                                                   \
            movff   PREINC2,BSR                                     \
            movff   PREINC2,WREG                                    \
            movff   PREINC2,ਸਥਿਤੀ_2                                  \
            ਵਾਪਸ  0       ; Return without affecting interrupts   \
        _Pragma("asmend")                                           \
    } ਜਦੋਂ(0)

/*-----------------------------------------------------------*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_PERIOD_MS  ( ( TickType_t ) 1000 / config_TICK_ਦਰ_HZ )

/*-----------------------------------------------------------*/

ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ );
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD()             v_ਪੋਰਟ_Yield()

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NOP()   _Pragma("asm")                                  \
                        nop                                         \
                    _Pragma("asmend")

/*-----------------------------------------------------------*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION( xFunction, pvParameters )        \
    ਖਾਲੀ pointed xFunction( ਖਾਲੀ *pvParameters )        \
    _Pragma(asmfunc xFunction)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION_PROTO     ਪੋਰਟ_TASK_FUNCTION
/*-----------------------------------------------------------*/


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਅਸਥਿਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਰਜਿਸਟਰ

#ਜੇ_ਅੰਤ /* PORTMACRO_H */
