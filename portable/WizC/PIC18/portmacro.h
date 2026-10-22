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
#اگر_تعریف_نشده PORTMACRO_H
#تعریف_کن PORTMACRO_H

#إذا !defined(_SERIES) || _SERIES != 18
    #خطا "WizC supports FreeRTOS on the Microchip PIC18-series only"
#پایان_اگر

#إذا !defined(QUICKCALL) || QUICKCALL != 1
    #خطا "QuickCall must be enabled (see ProjectOptions/Optimisations)"
#پایان_اگر

#ضمن <stddef.h>
#ضمن <pic.h>

#تعریف_کن پورت_CHAR        حرف
#تعریف_کن پورت_FLOAT       عائم
#تعریف_کن پورت_DOUBLE      پورت_FLOAT
#تعریف_کن پورت_LONG        دراز
#تعریف_کن پورت_SHORT       کوتاه
#تعریف_کن پورت_پشته_TYPE  uint8_t
#تعریف_کن پورت_پایه_TYPE   حرف

تعريفنوع پورت_پشته_TYPE پشته_Type_t;
تعريفنوع علامتدار حرف پایه_Type_t;
تعريفنوع بیعلامت حرف UBaseType_t;


#إذا( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
    تعريفنوع uint16_t TickType_t;
    #تعریف_کن پورت_MAX_DELAY ( TickType_t )    ( 0xFFFF )
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_32_بیتها )
    تعريفنوع uint32_t TickType_t;
    #تعریف_کن پورت_MAX_DELAY ( TickType_t )    ( 0xFFFFFFFFUL )
#وإلا
    #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
#پایان_اگر

#تعریف_کن پورت_BYTE_ALIGNMENT          1

/*-----------------------------------------------------------*/

/*
 * Constant used for context switch macro when we require the interrupt
 * enable state to be forced when the interrupted task is switched back in.
 */
#تعریف_کن پورت_INTERRUPTS_FORCED               (0x01)

/*
 * Constant used for context switch macro when we require the interrupt
 * enable state to be unchanged when the interrupted task is switched back in.
 */
#تعریف_کن پورت_INTERRUPTS_UNCHANGED            (0x00)

/* Initial interrupt enable state for newly created tasks.  This value is
 * used when a task switches in for the first time.
 */
#تعریف_کن پورت_INTERRUPTS_INITIAL_STATE        (پورت_INTERRUPTS_FORCED)

/*
 * Macros to modify the global interrupt enable bit in INTCON.
 */
#تعریف_کن پورت_DISABLE_INTERRUPTS()    \
    افعل                              \
    {                               \
        bGIE=0;                     \
    } طالما(bGIE)   // MicroChip recommends this check!

#تعریف_کن پورت_ENABLE_INTERRUPTS()     \
    افعل                              \
    {                               \
        bGIE=1;                     \
    } طالما(0)

/*-----------------------------------------------------------*/

/*
 * Critical section macros.
 */
خارجي uint8_t ucCriticalNesting;

#تعریف_کن پورت_NO_CRITICAL_SECTION_NESTING     ( ( uint8_t ) 0 )

#تعریف_کن پورت_ENTER_CRITICAL()                                        \
    افعل                                                              \
    {                                                               \
        پورت_DISABLE_INTERRUPTS();                                   \
                                                                    \
        /*                                                          \
         * Now interrupts are disabled ucCriticalNesting            \
         * can be accessed directly. Increment                      \
         * ucCriticalNesting to keep a count of how                 \
         * many times portENTER_CRITICAL() has been called.         \
         */                                                         \
        ucCriticalNesting++;                                        \
    } طالما(0)

#تعریف_کن پورت_EXIT_CRITICAL()                                         \
    افعل                                                              \
    {                                                               \
        إذا(ucCriticalNesting > پورت_NO_CRITICAL_SECTION_NESTING)     \
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
        إذا( ucCriticalNesting == پورت_NO_CRITICAL_SECTION_NESTING )  \
        {                                                           \
            پورت_ENABLE_INTERRUPTS();                                \
        }                                                           \
    } طالما(0)

/*-----------------------------------------------------------*/

/*
 * The minimal stacksize is calculated on the first reference of
 * portMINIMAL_STACK_SIZE. Some input to this calculation is
 * compile time determined, other input is port-defined (see port.c)
 */
خارجي uint16_t us_پورت_CALCULATE_کمینه_پشته_اندازه( فراغ );
خارجي uint16_t us_Calc_Min_پشته_اندازه;

#تعریف_کن پورت_کمینه_پشته_اندازه                  \
    ((us_Calc_Min_پشته_اندازه == 0)                  \
        ? us_پورت_CALCULATE_کمینه_پشته_اندازه()  \
        : us_Calc_Min_پشته_اندازه )

/*
 * WizC uses a downgrowing stack
 */
#تعریف_کن پورت_پشته_GROWTH            ( -1 )

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

#تعریف_کن پورت_SAVE_CONTEXT( uc_وقفه_Forced )                       \
    افعل                                                              \
    {                                                               \
        پورت_DISABLE_INTERRUPTS();                                   \
                                                                    \
        _Pragma("asm")                                              \
            ;                                                       \
            ; افزودن_3 the relevant SFR's onto the task's پشته         \
            ;                                                       \
            movff   وضعیت_2,POSTDEC2                                 \
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
            ; Save the pic call/أرجع-پشته belonging مقصد the       \
            ; current task by copying it مقصد the task's software-    \
            ; پشته. We save the hardware پشته اشاره_گر_2 (which      \
            ; is the عدد از آدرسها on the پشته) درون the       \
            ; W-سجل اولی_2 because we need it later and it      \
            ; is modified درون the save-loop by executing برداشت's.      \
            ; After the loop the W-سجل is stored on the        \
            ; پشته, too.                                           \
            ;                                                       \
            movf    STKPTR,W,ACCESS                                 \
            bz      _rtos_s3                                        \
        _rtos_S2:                                                   \
            إذا __ROMSIZE > 0x8000                                   \
                movff   TOSU,POSTDEC2                               \
            endif                                                   \
            movff   TOSH,POSTDEC2                                   \
            movff   TOSL,POSTDEC2                                   \
            برداشت                                                     \
            tstfsz  STKPTR,ACCESS                                   \
            SMARTJUMP _rtos_S2                                      \
        _rtos_s3:                                                   \
            movwf   POSTDEC2,ACCESS                                 \
            ;                                                       \
            ; بعدی the مقدار لكل ucCriticalNesting استفاده_شده by the      \
            ; task is stored on the پشته. When                     \
            ; (uc_وقفه_Forced == پورت_INTERRUPTS_FORCED), we save \
            ; it as 0 (پورت_NO_CRITICAL_SECTION_NESTING).            \
            ;                                                       \
            إذا uc_وقفه_Forced == پورت_INTERRUPTS_FORCED           \
                clrf POSTDEC2,ACCESS                                \
            وإلا                                                    \
                movff   ucCriticalNesting,POSTDEC2                  \
            endif                                                   \
            ;                                                       \
            ; Save the new بالاترین_2 از the software پشته درون the TCB.    \
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
#تعریف_کن پورت_RESTORE_CONTEXT()                                       \
    افعل                                                              \
    {                                                               \
        _Pragma("asm")                                              \
            ;                                                       \
            ; مجموعه_2 FSR0 مقصد نقطه_2 مقصد pxCurrentTCB->px_بالاترین_از_پشته.      \
            ;                                                       \
            movff   pxCurrentTCB,FSR0L                              \
            movff   pxCurrentTCB+1,FSR0H                            \
            ;                                                       \
            ; De-reference FSR0 مقصد مجموعه the آدرس_2 it holds into    \
            ; FSR2 (i.e. *( pxCurrentTCB->px_بالاترین_از_پشته ) ). FSR2    \
            ; is استفاده_شده by wizC as stackpointer.                      \
            ;                                                       \
            movff   POSTINC0,FSR2L                                  \
            movff   POSTINC0,FSR2H                                  \
            ;                                                       \
            ; بعدی, the مقدار لكل ucCriticalNesting استفاده_شده by the     \
            ; task is retrieved from the پشته.                     \
            ;                                                       \
            movff   PREINC2,ucCriticalNesting                       \
            ;                                                       \
            ; Rebuild the pic call/أرجع-پشته. The عدد از      \
            ; أرجع آدرسها is the بعدی_2 قلم on the task پشته.  \
            ; Save this عدد درون PRODL. Then fetch the آدرسها   \
            ; and store them on the hardwarestack.                  \
            ; The datasheets say we can't use movff اینجا...         \
            ;                                                       \
            movff   PREINC2,PRODL   // Use PRODL as tempregister    \
            clrf    STKPTR,ACCESS                                   \
        _rtos_R1:                                                   \
            افزودن                                                    \
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
            ; Restore the compiler's working storage area مقصد صفحه 0 \
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
            ; The أرجع from پورت_RESTORE_CONTEXT() depends on      \
            ; the مقدار از ucCriticalNesting. When it is zero,      \
            ; interrupts need مقصد be enabled. This is انجامشده از_طریق a     \
            ; retfie instruction because we need the                \
            ; وقفه-enabling and the أرجع مقصد the restored     \
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
            movff   PREINC2,وضعیت_2                                  \
            retfie  0       ; Return enabling interrupts            \
        _rtos_R4:                                                   \
            movff   PREINC2,BSR                                     \
            movff   PREINC2,WREG                                    \
            movff   PREINC2,وضعیت_2                                  \
            أرجع  0       ; Return without affecting interrupts   \
        _Pragma("asmend")                                           \
    } طالما(0)

/*-----------------------------------------------------------*/

#تعریف_کن پورت_TICK_PERIOD_MS  ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )

/*-----------------------------------------------------------*/

خارجي فراغ v_پورت_Yield( فراغ );
#تعریف_کن پورت_YIELD()             v_پورت_Yield()

#تعریف_کن پورت_NOP()   _Pragma("asm")                                  \
                        nop                                         \
                    _Pragma("asmend")

/*-----------------------------------------------------------*/

#تعریف_کن پورت_TASK_FUNCTION( xFunction, pvParameters )        \
    فراغ pointed xFunction( فراغ *pvParameters )        \
    _Pragma(asmfunc xFunction)

#تعریف_کن پورت_TASK_FUNCTION_PROTO     پورت_TASK_FUNCTION
/*-----------------------------------------------------------*/


#تعریف_کن متطاير
#تعریف_کن سجل

#پایان_اگر /* PORTMACRO_H */
