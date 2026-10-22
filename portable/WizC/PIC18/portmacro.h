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
#اگر_غیر_تعریف_شدہ PORTMACRO_H
#تعریف_کرو PORTMACRO_H

#اگر !defined(_SERIES) || _SERIES != 18
    #غلطی "WizC supports FreeRTOS on the Microchip PIC18-series only"
#اگر_ختم

#اگر !defined(QUICKCALL) || QUICKCALL != 1
    #غلطی "QuickCall must be enabled (see ProjectOptions/Optimisations)"
#اگر_ختم

#شامل <stddef.h>
#شامل <pic.h>

#تعریف_کرو پورٹ_CHAR        حرف
#تعریف_کرو پورٹ_FLOAT       اعشاری
#تعریف_کرو پورٹ_DOUBLE      پورٹ_FLOAT
#تعریف_کرو پورٹ_LONG        طویل
#تعریف_کرو پورٹ_SHORT       مختصر
#تعریف_کرو پورٹ_ڈھیر_TYPE  uint8_t
#تعریف_کرو پورٹ_بنیاد_TYPE   حرف

قسمتعریف پورٹ_ڈھیر_TYPE ڈھیر_Type_t;
قسمتعریف علامتی حرف بنیاد_Type_t;
قسمتعریف غیرعلامتی حرف UBaseType_t;


#اگر( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    قسمتعریف uint16_t TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY ( TickType_t )    ( 0xFFFF )
#وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    قسمتعریف uint32_t TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY ( TickType_t )    ( 0xFFFFFFFFUL )
#ورنہ
    #غلطی config_TICK_TYPE_چوڑائی_اندر_بٹ سیٹ مقصد unsupported tick type چوڑائی.
#اگر_ختم

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
    کرو                              \
    {                               \
        bGIE=0;                     \
    } جب(bGIE)   // MicroChip recommends this check!

#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     \
    کرو                              \
    {                               \
        bGIE=1;                     \
    } جب(0)

/*-----------------------------------------------------------*/

/*
 * Critical section macros.
 */
خارجی uint8_t ucCriticalNesting;

#تعریف_کرو پورٹ_NO_CRITICAL_SECTION_NESTING     ( ( uint8_t ) 0 )

#تعریف_کرو پورٹ_ENTER_CRITICAL()                                        \
    کرو                                                              \
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
    } جب(0)

#تعریف_کرو پورٹ_EXIT_CRITICAL()                                         \
    کرو                                                              \
    {                                                               \
        اگر(ucCriticalNesting > پورٹ_NO_CRITICAL_SECTION_NESTING)     \
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
        اگر( ucCriticalNesting == پورٹ_NO_CRITICAL_SECTION_NESTING )  \
        {                                                           \
            پورٹ_ENABLE_INTERRUPTS();                                \
        }                                                           \
    } جب(0)

/*-----------------------------------------------------------*/

/*
 * The minimal stacksize is calculated on the first reference of
 * portMINIMAL_STACK_SIZE. Some input to this calculation is
 * compile time determined, other input is port-defined (see port.c)
 */
خارجی uint16_t us_پورٹ_CALCULATE_اقل_ڈھیر_سائز( خالی );
خارجی uint16_t us_Calc_Min_ڈھیر_سائز;

#تعریف_کرو پورٹ_اقل_ڈھیر_سائز                  \
    ((us_Calc_Min_ڈھیر_سائز == 0)                  \
        ? us_پورٹ_CALCULATE_اقل_ڈھیر_سائز()  \
        : us_Calc_Min_ڈھیر_سائز )

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

#تعریف_کرو پورٹ_SAVE_CONTEXT( uc_مداخلت_Forced )                       \
    کرو                                                              \
    {                                                               \
        پورٹ_DISABLE_INTERRUPTS();                                   \
                                                                    \
        _Pragma("asm")                                              \
            ;                                                       \
            ; ڈالو_3 the relevant SFR's onto the task's ڈھیر         \
            ;                                                       \
            movff   حالت_3,POSTDEC2                                 \
            movff   WREG,POSTDEC2                                   \
            movff   BSR,POSTDEC2                                    \
            movff   PRODH,POSTDEC2                                  \
            movff   PRODL,POSTDEC2                                  \
            movff   FSR0H,POSTDEC2                                  \
            movff   FSR0L,POSTDEC2                                  \
            movff   FSR1H,POSTDEC2                                  \
            movff   FSR1L,POSTDEC2                                  \
            movff   TABLAT,POSTDEC2                                 \
            اگر __ROMSIZE > 0x8000                                   \
                movff   TBLPTRU,POSTDEC2                            \
            endif                                                   \
            movff   TBLPTRH,POSTDEC2                                \
            movff   TBLPTRL,POSTDEC2                                \
            اگر __ROMSIZE > 0x8000                                   \
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
            ; Save the pic call/واپس-ڈھیر belonging مقصد the       \
            ; current task by copying it مقصد the task's software-    \
            ; ڈھیر. We save the hardware ڈھیر اشارہ_گر_2 (which      \
            ; is the نمبر کا پتے on the ڈھیر) اندر the       \
            ; W-اندراج پہلا_2 because we need it later and it      \
            ; is modified اندر the save-loop by executing نکالو's.      \
            ; After the loop the W-اندراج is stored on the        \
            ; ڈھیر, too.                                           \
            ;                                                       \
            movf    STKPTR,W,ACCESS                                 \
            bz      _rtos_s3                                        \
        _rtos_S2:                                                   \
            اگر __ROMSIZE > 0x8000                                   \
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
            ; اگلا the قدر برائے ucCriticalNesting مستعمل by the      \
            ; task is stored on the ڈھیر. When                     \
            ; (uc_مداخلت_Forced == پورٹ_INTERRUPTS_FORCED), we save \
            ; it as 0 (پورٹ_NO_CRITICAL_SECTION_NESTING).            \
            ;                                                       \
            اگر uc_مداخلت_Forced == پورٹ_INTERRUPTS_FORCED           \
                clrf POSTDEC2,ACCESS                                \
            ورنہ                                                    \
                movff   ucCriticalNesting,POSTDEC2                  \
            endif                                                   \
            ;                                                       \
            ; Save the new چوٹی_2 کا the software ڈھیر اندر the TCB.    \
            ;                                                       \
            movff   pxCurrentTCB,FSR0L                              \
            movff   pxCurrentTCB+1,FSR0H                            \
            movff   FSR2L,POSTINC0                                  \
            movff   FSR2H,POSTINC0                                  \
        _Pragma("asmend")                                           \
    } جب(0)

/************************************************************/

/*
 * This is the reverse of portSAVE_CONTEXT.
 */
#تعریف_کرو پورٹ_RESTORE_CONTEXT()                                       \
    کرو                                                              \
    {                                                               \
        _Pragma("asm")                                              \
            ;                                                       \
            ; سیٹ_2 FSR0 مقصد نقطہ_2 مقصد pxCurrentTCB->px_چوٹی_کا_ڈھیر.      \
            ;                                                       \
            movff   pxCurrentTCB,FSR0L                              \
            movff   pxCurrentTCB+1,FSR0H                            \
            ;                                                       \
            ; De-reference FSR0 مقصد سیٹ the پتہ_2 it holds into    \
            ; FSR2 (i.e. *( pxCurrentTCB->px_چوٹی_کا_ڈھیر ) ). FSR2    \
            ; is مستعمل by wizC as stackpointer.                      \
            ;                                                       \
            movff   POSTINC0,FSR2L                                  \
            movff   POSTINC0,FSR2H                                  \
            ;                                                       \
            ; اگلا, the قدر برائے ucCriticalNesting مستعمل by the     \
            ; task is retrieved from the ڈھیر.                     \
            ;                                                       \
            movff   PREINC2,ucCriticalNesting                       \
            ;                                                       \
            ; Rebuild the pic call/واپس-ڈھیر. The نمبر کا      \
            ; واپس پتے is the اگلا_2 شے_2 on the task ڈھیر.  \
            ; Save this نمبر اندر PRODL. Then fetch the پتے   \
            ; and store them on the hardwarestack.                  \
            ; The datasheets say we can't use movff یہاں...         \
            ;                                                       \
            movff   PREINC2,PRODL   // Use PRODL as tempregister    \
            clrf    STKPTR,ACCESS                                   \
        _rtos_R1:                                                   \
            ڈالو                                                    \
            movf    PREINC2,W,ACCESS                                \
            movwf   TOSL,ACCESS                                     \
            movf    PREINC2,W,ACCESS                                \
            movwf   TOSH,ACCESS                                     \
            اگر __ROMSIZE > 0x8000                                   \
                movf    PREINC2,W,ACCESS                            \
                movwf   TOSU,ACCESS                                 \
            ورنہ                                                    \
                clrf    TOSU,ACCESS                                 \
            endif                                                   \
            decfsz  PRODL,F,ACCESS                                  \
            SMARTJUMP _rtos_R1                                      \
            ;                                                       \
            ; Restore the compiler's working storage area مقصد صفحہ 0 \
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
            ; we need these registers برائے a final test.             \
            ;                                                       \
            movff   PREINC2,PCLATH                                  \
            اگر __ROMSIZE > 0x8000                                   \
                movff   PREINC2,PCLATU                              \
            ورنہ                                                    \
                clrf    PCLATU,ACCESS                               \
            endif                                                   \
            movff   PREINC2,TBLPTRL                                 \
            movff   PREINC2,TBLPTRH                                 \
            اگر __ROMSIZE > 0x8000                                   \
                movff   PREINC2,TBLPTRU                             \
            ورنہ                                                    \
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
            ; The واپس from پورٹ_RESTORE_CONTEXT() depends on      \
            ; the قدر کا ucCriticalNesting. When it is zero,      \
            ; interrupts need مقصد be enabled. This is مکمل بذریعہ a     \
            ; retfie instruction because we need the                \
            ; مداخلت-enabling and the واپس مقصد the restored     \
            ; task مقصد be uninterruptible.                           \
            ; Because bsr, status and W are affected by the test    \
            ; they are restored after the test.                     \
            ;                                                       \
            movlb   ucCriticalNesting>>8                            \
            tstfsz  ucCriticalNesting,BANKED                        \
            SMARTJUMP _rtos_R4                                      \
        _rtos_R3:                                                   \
            movff   PREINC2,BSR                                     \
            movff   PREINC2,WREG                                    \
            movff   PREINC2,حالت_3                                  \
            retfie  0       ; Return enabling interrupts            \
        _rtos_R4:                                                   \
            movff   PREINC2,BSR                                     \
            movff   PREINC2,WREG                                    \
            movff   PREINC2,حالت_3                                  \
            واپس  0       ; Return without affecting interrupts   \
        _Pragma("asmend")                                           \
    } جب(0)

/*-----------------------------------------------------------*/

#تعریف_کرو پورٹ_TICK_PERIOD_MS  ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )

/*-----------------------------------------------------------*/

خارجی خالی v_پورٹ_Yield( خالی );
#تعریف_کرو پورٹ_YIELD()             v_پورٹ_Yield()

#تعریف_کرو پورٹ_NOP()   _Pragma("asm")                                  \
                        nop                                         \
                    _Pragma("asmend")

/*-----------------------------------------------------------*/

#تعریف_کرو پورٹ_TASK_FUNCTION( xFunction, pvParameters )        \
    خالی pointed xFunction( خالی *pvParameters )        \
    _Pragma(asmfunc xFunction)

#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO     پورٹ_TASK_FUNCTION
/*-----------------------------------------------------------*/


#تعریف_کرو متلون
#تعریف_کرو اندراج

#اگر_ختم /* PORTMACRO_H */
