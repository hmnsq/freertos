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
#جيڪڏهن_وصف_نه_ٿيل PORTMACRO_H
#وصف_ڪريو PORTMACRO_H

#إذا !defined(_SERIES) || _SERIES != 18
    #غلطي "WizC supports FreeRTOS on the Microchip PIC18-series only"
#جيڪڏهن_پورو

#إذا !defined(QUICKCALL) || QUICKCALL != 1
    #غلطي "QuickCall must be enabled (see ProjectOptions/Optimisations)"
#جيڪڏهن_پورو

#ضمن <stddef.h>
#ضمن <pic.h>

#وصف_ڪريو پورٽ_CHAR        حرف
#وصف_ڪريو پورٽ_FLOAT       عائم
#وصف_ڪريو پورٽ_DOUBLE      پورٽ_FLOAT
#وصف_ڪريو پورٽ_LONG        ڊگهو
#وصف_ڪريو پورٽ_SHORT       ننڍو
#وصف_ڪريو پورٽ_ڍير_TYPE  uint8_t
#وصف_ڪريو پورٽ_بنياد_TYPE   حرف

تعريفنوع پورٽ_ڍير_TYPE ڍير_Type_t;
تعريفنوع نشانوارو حرف بنياد_Type_t;
تعريفنوع بنانشان حرف UBaseType_t;


#إذا( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_16_بٽ )
    تعريفنوع uint16_t TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY ( TickType_t )    ( 0xFFFF )
#وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_32_بٽ )
    تعريفنوع uint32_t TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY ( TickType_t )    ( 0xFFFFFFFFUL )
#وإلا
    #غلطي config_TICK_TYPE_ويڪر_اندريون_بٽ سيٽ منزل unsupported tick type ويڪر.
#جيڪڏهن_پورو

#وصف_ڪريو پورٽ_BYTE_ALIGNMENT          1

/*-----------------------------------------------------------*/

/*
 * Constant used for context switch macro when we require the interrupt
 * enable state to be forced when the interrupted task is switched back in.
 */
#وصف_ڪريو پورٽ_INTERRUPTS_FORCED               (0x01)

/*
 * Constant used for context switch macro when we require the interrupt
 * enable state to be unchanged when the interrupted task is switched back in.
 */
#وصف_ڪريو پورٽ_INTERRUPTS_UNCHANGED            (0x00)

/* Initial interrupt enable state for newly created tasks.  This value is
 * used when a task switches in for the first time.
 */
#وصف_ڪريو پورٽ_INTERRUPTS_INITIAL_STATE        (پورٽ_INTERRUPTS_FORCED)

/*
 * Macros to modify the global interrupt enable bit in INTCON.
 */
#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()    \
    افعل                              \
    {                               \
        bGIE=0;                     \
    } طالما(bGIE)   // MicroChip recommends this check!

#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()     \
    افعل                              \
    {                               \
        bGIE=1;                     \
    } طالما(0)

/*-----------------------------------------------------------*/

/*
 * Critical section macros.
 */
خارجي uint8_t ucCriticalNesting;

#وصف_ڪريو پورٽ_NO_CRITICAL_SECTION_NESTING     ( ( uint8_t ) 0 )

#وصف_ڪريو پورٽ_ENTER_CRITICAL()                                        \
    افعل                                                              \
    {                                                               \
        پورٽ_DISABLE_INTERRUPTS();                                   \
                                                                    \
        /*                                                          \
         * Now interrupts are disabled ucCriticalNesting            \
         * can be accessed directly. Increment                      \
         * ucCriticalNesting to keep a count of how                 \
         * many times portENTER_CRITICAL() has been called.         \
         */                                                         \
        ucCriticalNesting++;                                        \
    } طالما(0)

#وصف_ڪريو پورٽ_EXIT_CRITICAL()                                         \
    افعل                                                              \
    {                                                               \
        إذا(ucCriticalNesting > پورٽ_NO_CRITICAL_SECTION_NESTING)     \
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
        إذا( ucCriticalNesting == پورٽ_NO_CRITICAL_SECTION_NESTING )  \
        {                                                           \
            پورٽ_ENABLE_INTERRUPTS();                                \
        }                                                           \
    } طالما(0)

/*-----------------------------------------------------------*/

/*
 * The minimal stacksize is calculated on the first reference of
 * portMINIMAL_STACK_SIZE. Some input to this calculation is
 * compile time determined, other input is port-defined (see port.c)
 */
خارجي uint16_t us_پورٽ_CALCULATE_گهٽتر_ڍير_سائيز( فراغ );
خارجي uint16_t us_Calc_Min_ڍير_سائيز;

#وصف_ڪريو پورٽ_گهٽتر_ڍير_سائيز                  \
    ((us_Calc_Min_ڍير_سائيز == 0)                  \
        ? us_پورٽ_CALCULATE_گهٽتر_ڍير_سائيز()  \
        : us_Calc_Min_ڍير_سائيز )

/*
 * WizC uses a downgrowing stack
 */
#وصف_ڪريو پورٽ_ڍير_GROWTH            ( -1 )

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

#وصف_ڪريو پورٽ_SAVE_CONTEXT( uc_مداخلت_Forced )                       \
    افعل                                                              \
    {                                                               \
        پورٽ_DISABLE_INTERRUPTS();                                   \
                                                                    \
        _Pragma("asm")                                              \
            ;                                                       \
            ; ڌڪو_3 the relevant SFR's onto the task's ڍير         \
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
            ; Save the pic call/أرجع-ڍير belonging منزل the       \
            ; current task by copying it منزل the task's software-    \
            ; ڍير. We save the hardware ڍير اشارو_2 (which      \
            ; is the عدد جو پتا on the ڍير) اندريون the       \
            ; W-سجل پهريون_2 because we need it later and it      \
            ; is modified اندريون the save-loop by executing ڪڍو's.      \
            ; After the loop the W-سجل is stored on the        \
            ; ڍير, too.                                           \
            ;                                                       \
            movf    STKPTR,W,ACCESS                                 \
            bz      _rtos_s3                                        \
        _rtos_S2:                                                   \
            إذا __ROMSIZE > 0x8000                                   \
                movff   TOSU,POSTDEC2                               \
            endif                                                   \
            movff   TOSH,POSTDEC2                                   \
            movff   TOSL,POSTDEC2                                   \
            ڪڍو                                                     \
            tstfsz  STKPTR,ACCESS                                   \
            SMARTJUMP _rtos_S2                                      \
        _rtos_s3:                                                   \
            movwf   POSTDEC2,ACCESS                                 \
            ;                                                       \
            ; ايندڙ the قدر لكل ucCriticalNesting استعمال_ٿيل by the      \
            ; task is stored on the ڍير. When                     \
            ; (uc_مداخلت_Forced == پورٽ_INTERRUPTS_FORCED), we save \
            ; it as 0 (پورٽ_NO_CRITICAL_SECTION_NESTING).            \
            ;                                                       \
            إذا uc_مداخلت_Forced == پورٽ_INTERRUPTS_FORCED           \
                clrf POSTDEC2,ACCESS                                \
            وإلا                                                    \
                movff   ucCriticalNesting,POSTDEC2                  \
            endif                                                   \
            ;                                                       \
            ; Save the new چوٽي_2 جو the software ڍير اندريون the TCB.    \
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
#وصف_ڪريو پورٽ_RESTORE_CONTEXT()                                       \
    افعل                                                              \
    {                                                               \
        _Pragma("asm")                                              \
            ;                                                       \
            ; سيٽ_2 FSR0 منزل نقطو_2 منزل pxCurrentTCB->px_چوٽي_جو_ڍير.      \
            ;                                                       \
            movff   pxCurrentTCB,FSR0L                              \
            movff   pxCurrentTCB+1,FSR0H                            \
            ;                                                       \
            ; De-reference FSR0 منزل سيٽ the پتو_2 it holds into    \
            ; FSR2 (i.e. *( pxCurrentTCB->px_چوٽي_جو_ڍير ) ). FSR2    \
            ; is استعمال_ٿيل by wizC as stackpointer.                      \
            ;                                                       \
            movff   POSTINC0,FSR2L                                  \
            movff   POSTINC0,FSR2H                                  \
            ;                                                       \
            ; ايندڙ, the قدر لكل ucCriticalNesting استعمال_ٿيل by the     \
            ; task is retrieved from the ڍير.                     \
            ;                                                       \
            movff   PREINC2,ucCriticalNesting                       \
            ;                                                       \
            ; Rebuild the pic call/أرجع-ڍير. The عدد جو      \
            ; أرجع پتا is the ايندڙ_2 شي on the task ڍير.  \
            ; Save this عدد اندريون PRODL. Then fetch the پتا   \
            ; and store them on the hardwarestack.                  \
            ; The datasheets say we can't use movff هتي...         \
            ;                                                       \
            movff   PREINC2,PRODL   // Use PRODL as tempregister    \
            clrf    STKPTR,ACCESS                                   \
        _rtos_R1:                                                   \
            ڌڪو                                                    \
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
            ; Restore the compiler's working storage area منزل صفحو 0 \
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
            ; The أرجع from پورٽ_RESTORE_CONTEXT() depends on      \
            ; the قدر جو ucCriticalNesting. When it is zero,      \
            ; interrupts need منزل be enabled. This is پورو ذريعي a     \
            ; retfie instruction because we need the                \
            ; مداخلت-enabling and the أرجع منزل the restored     \
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

#وصف_ڪريو پورٽ_TICK_PERIOD_MS  ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )

/*-----------------------------------------------------------*/

خارجي فراغ v_پورٽ_Yield( فراغ );
#وصف_ڪريو پورٽ_YIELD()             v_پورٽ_Yield()

#وصف_ڪريو پورٽ_NOP()   _Pragma("asm")                                  \
                        nop                                         \
                    _Pragma("asmend")

/*-----------------------------------------------------------*/

#وصف_ڪريو پورٽ_TASK_FUNCTION( xFunction, pvParameters )        \
    فراغ pointed xFunction( فراغ *pvParameters )        \
    _Pragma(asmfunc xFunction)

#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO     پورٽ_TASK_FUNCTION
/*-----------------------------------------------------------*/


#وصف_ڪريو متطاير
#وصف_ڪريو سجل

#جيڪڏهن_پورو /* PORTMACRO_H */
