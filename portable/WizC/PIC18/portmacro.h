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
#جے_بنا_تعریف PORTMACRO_H
#تعریف_کرو PORTMACRO_H

#إذا !defined(_SERIES) || _SERIES != 18
    #غلطی "WizC supports FreeRTOS on the Microchip PIC18-series only"
#جے_انت

#إذا !defined(QUICKCALL) || QUICKCALL != 1
    #غلطی "QuickCall must be enabled (see ProjectOptions/Optimisations)"
#جے_انت

#ضمن <stddef.h>
#ضمن <pic.h>

#تعریف_کرو پورٹ_CHAR        حرف
#تعریف_کرو پورٹ_FLOAT       عائم
#تعریف_کرو پورٹ_DOUBLE      پورٹ_FLOAT
#تعریف_کرو پورٹ_LONG        لما
#تعریف_کرو پورٹ_SHORT       چھوٹا
#تعریف_کرو پورٹ_ڈھیر_TYPE  uint8_t
#تعریف_کرو پورٹ_ادھار_TYPE   حرف

تعريفنوع پورٹ_ڈھیر_TYPE ڈھیر_Type_t;
تعريفنوع نشانیوالا حرف ادھار_Type_t;
تعريفنوع بنانشانی حرف UBaseType_t;


#إذا( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    تعريفنوع uint16_t TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY ( TickType_t )    ( 0xFFFF )
#وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    تعريفنوع uint32_t TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY ( TickType_t )    ( 0xFFFFFFFFUL )
#وإلا
    #غلطی config_TICK_TYPE_چوڑائی_وچ_بٹ سیٹ منزل unsupported tick type چوڑائی.
#جے_انت

#تعریف_کرو پورٹ_BYTE_ALIGNMENT          1

/*-----------------------------------------------------------*/

/*
 * Constant used for context switch macro when we require the interrupt
 * enable state to be forced when the interrupted task is switched back in.
 */
#تعریف_کرو پورٹ_INTERRUPTS_FORCED               (0x01)

/*
 * Constant used for context switch macro when we require the interrupt
 * enable state to be unchanged when the interrupted task is switched back in.
 */
#تعریف_کرو پورٹ_INTERRUPTS_UNCHANGED            (0x00)

/* Initial interrupt enable state for newly created tasks.  This value is
 * used when a task switches in for the first time.
 */
#تعریف_کرو پورٹ_INTERRUPTS_INITIAL_STATE        (پورٹ_INTERRUPTS_FORCED)

/*
 * Macros to modify the global interrupt enable bit in INTCON.
 */
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    \
    افعل                              \
    {                               \
        bGIE=0;                     \
    } طالما(bGIE)   // MicroChip recommends this check!

#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     \
    افعل                              \
    {                               \
        bGIE=1;                     \
    } طالما(0)

/*-----------------------------------------------------------*/

/*
 * Critical section macros.
 */
خارجي uint8_t ucCriticalNesting;

#تعریف_کرو پورٹ_NO_CRITICAL_SECTION_NESTING     ( ( uint8_t ) 0 )

#تعریف_کرو پورٹ_ENTER_CRITICAL()                                        \
    افعل                                                              \
    {                                                               \
        پورٹ_DISABLE_INTERRUPTS();                                   \
                                                                    \
        /*                                                          \
         * Now interrupts are disabled ucCriticalNesting            \
         * can be accessed directly. Increment                      \
         * ucCriticalNesting to keep a count of how                 \
         * many times portENTER_CRITICAL() has been called.         \
         */                                                         \
        ucCriticalNesting++;                                        \
    } طالما(0)

#تعریف_کرو پورٹ_EXIT_CRITICAL()                                         \
    افعل                                                              \
    {                                                               \
        إذا(ucCriticalNesting > پورٹ_NO_CRITICAL_SECTION_NESTING)     \
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
        إذا( ucCriticalNesting == پورٹ_NO_CRITICAL_SECTION_NESTING )  \
        {                                                           \
            پورٹ_ENABLE_INTERRUPTS();                                \
        }                                                           \
    } طالما(0)

/*-----------------------------------------------------------*/

/*
 * The minimal stacksize is calculated on the first reference of
 * portMINIMAL_STACK_SIZE. Some input to this calculation is
 * compile time determined, other input is port-defined (see port.c)
 */
خارجي uint16_t us_پورٹ_CALCULATE_اقل_ڈھیر_ناپ( فراغ );
خارجي uint16_t us_Calc_Min_ڈھیر_ناپ;

#تعریف_کرو پورٹ_اقل_ڈھیر_ناپ                  \
    ((us_Calc_Min_ڈھیر_ناپ == 0)                  \
        ? us_پورٹ_CALCULATE_اقل_ڈھیر_ناپ()  \
        : us_Calc_Min_ڈھیر_ناپ )

/*
 * WizC uses a downgrowing stack
 */
#تعریف_کرو پورٹ_ڈھیر_GROWTH            ( -1 )

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

#تعریف_کرو پورٹ_SAVE_CONTEXT( uc_رکاوٹ_Forced )                       \
    افعل                                                              \
    {                                                               \
        پورٹ_DISABLE_INTERRUPTS();                                   \
                                                                    \
        _Pragma("asm")                                              \
            ;                                                       \
            ; ڈالو_3 the relevant SFR's onto the task's ڈھیر         \
            ;                                                       \
            movff   حالت_2,POSTDEC2                                 \
            movff   WREG,POSTDEC2                                   \
            movff   BSR,POSTDEC2                                    \
            movff   PRODH,POSTDEC2                                  \
            movff   PRODL,POSTDEC2                                  \
            movff   FSR0H,POSTDEC2                                  \
            movff   FSR0L,POSTDEC2                                  \
            movff   FSR1H,POSTDEC2                                  \
            movff   FSR1L,POSTDEC2                                  \
            movff   TABLAT,POSTDEC2                                 \
            إذا __ROMSIZE > 0x8000                                   \
                movff   TBLPTRU,POSTDEC2                            \
            endif                                                   \
            movff   TBLPTRH,POSTDEC2                                \
            movff   TBLPTRL,POSTDEC2                                \
            إذا __ROMSIZE > 0x8000                                   \
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
            ; Save the pic call/أرجع-ڈھیر belonging منزل the       \
            ; current task by copying it منزل the task's software-    \
            ; ڈھیر. We save the hardware ڈھیر اشارہ_گر_2 (which      \
            ; is the نمبر دا پتے on the ڈھیر) وچ the       \
            ; W-سجل پہلا_2 because we need it later and it      \
            ; is modified وچ the save-loop by executing نکالو's.      \
            ; After the loop the W-سجل is stored on the        \
            ; ڈھیر, too.                                           \
            ;                                                       \
            movf    STKPTR,W,ACCESS                                 \
            bz      _rtos_s3                                        \
        _rtos_S2:                                                   \
            إذا __ROMSIZE > 0x8000                                   \
                movff   TOSU,POSTDEC2                               \
            endif                                                   \
            movff   TOSH,POSTDEC2                                   \
            movff   TOSL,POSTDEC2                                   \
            نکالو                                                     \
            tstfsz  STKPTR,ACCESS                                   \
            SMARTJUMP _rtos_S2                                      \
        _rtos_s3:                                                   \
            movwf   POSTDEC2,ACCESS                                 \
            ;                                                       \
            ; اگلا the قدر لكل ucCriticalNesting ورتیا by the      \
            ; task is stored on the ڈھیر. When                     \
            ; (uc_رکاوٹ_Forced == پورٹ_INTERRUPTS_FORCED), we save \
            ; it as 0 (پورٹ_NO_CRITICAL_SECTION_NESTING).            \
            ;                                                       \
            إذا uc_رکاوٹ_Forced == پورٹ_INTERRUPTS_FORCED           \
                clrf POSTDEC2,ACCESS                                \
            وإلا                                                    \
                movff   ucCriticalNesting,POSTDEC2                  \
            endif                                                   \
            ;                                                       \
            ; Save the new چوٹی_2 دا the software ڈھیر وچ the TCB.    \
            ;                                                       \
            movff   pxCurrentTCB,FSR0L                              \
            movff   pxCurrentTCB+1,FSR0H                            \
            movff   FSR2L,POSTINC0                                  \
            movff   FSR2H,POSTINC0                                  \
        _Pragma("asmend")                                           \
    } طالما(0)

/************************************************************/

/*
 * This is the reverse of portSAVE_CONTEXT.
 */
#تعریف_کرو پورٹ_RESTORE_CONTEXT()                                       \
    افعل                                                              \
    {                                                               \
        _Pragma("asm")                                              \
            ;                                                       \
            ; سیٹ_2 FSR0 منزل نقطہ_2 منزل pxCurrentTCB->px_چوٹی_دا_ڈھیر.      \
            ;                                                       \
            movff   pxCurrentTCB,FSR0L                              \
            movff   pxCurrentTCB+1,FSR0H                            \
            ;                                                       \
            ; De-reference FSR0 منزل سیٹ the پتہ_2 it holds into    \
            ; FSR2 (i.e. *( pxCurrentTCB->px_چوٹی_دا_ڈھیر ) ). FSR2    \
            ; is ورتیا by wizC as stackpointer.                      \
            ;                                                       \
            movff   POSTINC0,FSR2L                                  \
            movff   POSTINC0,FSR2H                                  \
            ;                                                       \
            ; اگلا, the قدر لكل ucCriticalNesting ورتیا by the     \
            ; task is retrieved from the ڈھیر.                     \
            ;                                                       \
            movff   PREINC2,ucCriticalNesting                       \
            ;                                                       \
            ; Rebuild the pic call/أرجع-ڈھیر. The نمبر دا      \
            ; أرجع پتے is the اگلا_2 شے on the task ڈھیر.  \
            ; Save this نمبر وچ PRODL. Then fetch the پتے   \
            ; and store them on the hardwarestack.                  \
            ; The datasheets say we can't use movff ایتھے...         \
            ;                                                       \
            movff   PREINC2,PRODL   // Use PRODL as tempregister    \
            clrf    STKPTR,ACCESS                                   \
        _rtos_R1:                                                   \
            ڈالو                                                    \
            movf    PREINC2,W,ACCESS                                \
            movwf   TOSL,ACCESS                                     \
            movf    PREINC2,W,ACCESS                                \
            movwf   TOSH,ACCESS                                     \
            إذا __ROMSIZE > 0x8000                                   \
                movf    PREINC2,W,ACCESS                            \
                movwf   TOSU,ACCESS                                 \
            وإلا                                                    \
                clrf    TOSU,ACCESS                                 \
            endif                                                   \
            decfsz  PRODL,F,ACCESS                                  \
            SMARTJUMP _rtos_R1                                      \
            ;                                                       \
            ; Restore the compiler's working storage area منزل ورقہ 0 \
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
            ; we need these registers لكل a final test.             \
            ;                                                       \
            movff   PREINC2,PCLATH                                  \
            إذا __ROMSIZE > 0x8000                                   \
                movff   PREINC2,PCLATU                              \
            وإلا                                                    \
                clrf    PCLATU,ACCESS                               \
            endif                                                   \
            movff   PREINC2,TBLPTRL                                 \
            movff   PREINC2,TBLPTRH                                 \
            إذا __ROMSIZE > 0x8000                                   \
                movff   PREINC2,TBLPTRU                             \
            وإلا                                                    \
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
            ; The أرجع from پورٹ_RESTORE_CONTEXT() depends on      \
            ; the قدر دا ucCriticalNesting. When it is zero,      \
            ; interrupts need منزل be enabled. This is پورا راہیں a     \
            ; retfie instruction because we need the                \
            ; رکاوٹ-enabling and the أرجع منزل the restored     \
            ; task منزل be uninterruptible.                           \
            ; Because bsr, status and W are affected by the test    \
            ; they are restored after the test.                     \
            ;                                                       \
            movlb   ucCriticalNesting>>8                            \
            tstfsz  ucCriticalNesting,BANKED                        \
            SMARTJUMP _rtos_R4                                      \
        _rtos_R3:                                                   \
            movff   PREINC2,BSR                                     \
            movff   PREINC2,WREG                                    \
            movff   PREINC2,حالت_2                                  \
            retfie  0       ; Return enabling interrupts            \
        _rtos_R4:                                                   \
            movff   PREINC2,BSR                                     \
            movff   PREINC2,WREG                                    \
            movff   PREINC2,حالت_2                                  \
            أرجع  0       ; Return without affecting interrupts   \
        _Pragma("asmend")                                           \
    } طالما(0)

/*-----------------------------------------------------------*/

#تعریف_کرو پورٹ_TICK_PERIOD_MS  ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )

/*-----------------------------------------------------------*/

خارجي فراغ v_پورٹ_Yield( فراغ );
#تعریف_کرو پورٹ_YIELD()             v_پورٹ_Yield()

#تعریف_کرو پورٹ_NOP()   _Pragma("asm")                                  \
                        nop                                         \
                    _Pragma("asmend")

/*-----------------------------------------------------------*/

#تعریف_کرو پورٹ_TASK_FUNCTION( xFunction, pvParameters )        \
    فراغ pointed xFunction( فراغ *pvParameters )        \
    _Pragma(asmfunc xFunction)

#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO     پورٹ_TASK_FUNCTION
/*-----------------------------------------------------------*/


#تعریف_کرو متطاير
#تعریف_کرو سجل

#جے_انت /* PORTMACRO_H */
