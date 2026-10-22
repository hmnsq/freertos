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
#که_نه_تعریف_شوی PORTMACRO_H
#تعریف_کړه PORTMACRO_H

#إذا !defined(_SERIES) || _SERIES != 18
    #تېروتنه "WizC supports FreeRTOS on the Microchip PIC18-series only"
#د_که_پای

#إذا !defined(QUICKCALL) || QUICKCALL != 1
    #تېروتنه "QuickCall must be enabled (see ProjectOptions/Optimisations)"
#د_که_پای

#ضمن <stddef.h>
#ضمن <pic.h>

#تعریف_کړه پورټ_CHAR        حرف
#تعریف_کړه پورټ_FLOAT       عائم
#تعریف_کړه پورټ_DOUBLE      پورټ_FLOAT
#تعریف_کړه پورټ_LONG        اوږد
#تعریف_کړه پورټ_SHORT       لنډ
#تعریف_کړه پورټ_ډېری_TYPE  uint8_t
#تعریف_کړه پورټ_بنسټ_TYPE   حرف

تعريفنوع پورټ_ډېری_TYPE ډېری_Type_t;
تعريفنوع نښهدار حرف بنسټ_Type_t;
تعريفنوع بینښه حرف UBaseType_t;


#إذا( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
    تعريفنوع uint16_t TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY ( TickType_t )    ( 0xFFFF )
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY ( TickType_t )    ( 0xFFFFFFFFUL )
#وإلا
    #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
#د_که_پای

#تعریف_کړه پورټ_BYTE_ALIGNMENT          1

/*-----------------------------------------------------------*/

/*
 * Constant used for context switch macro when we require the interrupt
 * enable state to be forced when the interrupted task is switched back in.
 */
#تعریف_کړه پورټ_INTERRUPTS_FORCED               (0x01)

/*
 * Constant used for context switch macro when we require the interrupt
 * enable state to be unchanged when the interrupted task is switched back in.
 */
#تعریف_کړه پورټ_INTERRUPTS_UNCHANGED            (0x00)

/* Initial interrupt enable state for newly created tasks.  This value is
 * used when a task switches in for the first time.
 */
#تعریف_کړه پورټ_INTERRUPTS_INITIAL_STATE        (پورټ_INTERRUPTS_FORCED)

/*
 * Macros to modify the global interrupt enable bit in INTCON.
 */
#تعریف_کړه پورټ_DISABLE_INTERRUPTS()    \
    افعل                              \
    {                               \
        bGIE=0;                     \
    } طالما(bGIE)   // MicroChip recommends this check!

#تعریف_کړه پورټ_ENABLE_INTERRUPTS()     \
    افعل                              \
    {                               \
        bGIE=1;                     \
    } طالما(0)

/*-----------------------------------------------------------*/

/*
 * Critical section macros.
 */
خارجي uint8_t ucCriticalNesting;

#تعریف_کړه پورټ_NO_CRITICAL_SECTION_NESTING     ( ( uint8_t ) 0 )

#تعریف_کړه پورټ_ENTER_CRITICAL()                                        \
    افعل                                                              \
    {                                                               \
        پورټ_DISABLE_INTERRUPTS();                                   \
                                                                    \
        /*                                                          \
         * Now interrupts are disabled ucCriticalNesting            \
         * can be accessed directly. Increment                      \
         * ucCriticalNesting to keep a count of how                 \
         * many times portENTER_CRITICAL() has been called.         \
         */                                                         \
        ucCriticalNesting++;                                        \
    } طالما(0)

#تعریف_کړه پورټ_EXIT_CRITICAL()                                         \
    افعل                                                              \
    {                                                               \
        إذا(ucCriticalNesting > پورټ_NO_CRITICAL_SECTION_NESTING)     \
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
        إذا( ucCriticalNesting == پورټ_NO_CRITICAL_SECTION_NESTING )  \
        {                                                           \
            پورټ_ENABLE_INTERRUPTS();                                \
        }                                                           \
    } طالما(0)

/*-----------------------------------------------------------*/

/*
 * The minimal stacksize is calculated on the first reference of
 * portMINIMAL_STACK_SIZE. Some input to this calculation is
 * compile time determined, other input is port-defined (see port.c)
 */
خارجي uint16_t us_پورټ_CALCULATE_اصغري_ډېری_اندازه( فراغ );
خارجي uint16_t us_Calc_Min_ډېری_اندازه;

#تعریف_کړه پورټ_اصغري_ډېری_اندازه                  \
    ((us_Calc_Min_ډېری_اندازه == 0)                  \
        ? us_پورټ_CALCULATE_اصغري_ډېری_اندازه()  \
        : us_Calc_Min_ډېری_اندازه )

/*
 * WizC uses a downgrowing stack
 */
#تعریف_کړه پورټ_ډېری_GROWTH            ( -1 )

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

#تعریف_کړه پورټ_SAVE_CONTEXT( uc_مداخله_Forced )                       \
    افعل                                                              \
    {                                                               \
        پورټ_DISABLE_INTERRUPTS();                                   \
                                                                    \
        _Pragma("asm")                                              \
            ;                                                       \
            ; ټېل_3 the relevant SFR's onto the task's ډېری         \
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
            ; Save the pic call/أرجع-ډېری belonging منزل the       \
            ; current task by copying it منزل the task's software-    \
            ; ډېری. We save the hardware ډېری اشاره_ګر_2 (which      \
            ; is the شمېره د پتې on the ډېری) دننه the       \
            ; W-سجل لومړی_2 because we need it later and it      \
            ; is modified دننه the save-loop by executing راوباسه's.      \
            ; After the loop the W-سجل is stored on the        \
            ; ډېری, too.                                           \
            ;                                                       \
            movf    STKPTR,W,ACCESS                                 \
            bz      _rtos_s3                                        \
        _rtos_S2:                                                   \
            إذا __ROMSIZE > 0x8000                                   \
                movff   TOSU,POSTDEC2                               \
            endif                                                   \
            movff   TOSH,POSTDEC2                                   \
            movff   TOSL,POSTDEC2                                   \
            راوباسه                                                     \
            tstfsz  STKPTR,ACCESS                                   \
            SMARTJUMP _rtos_S2                                      \
        _rtos_s3:                                                   \
            movwf   POSTDEC2,ACCESS                                 \
            ;                                                       \
            ; بل the ارزښت لكل ucCriticalNesting کارول_شوی by the      \
            ; task is stored on the ډېری. When                     \
            ; (uc_مداخله_Forced == پورټ_INTERRUPTS_FORCED), we save \
            ; it as 0 (پورټ_NO_CRITICAL_SECTION_NESTING).            \
            ;                                                       \
            إذا uc_مداخله_Forced == پورټ_INTERRUPTS_FORCED           \
                clrf POSTDEC2,ACCESS                                \
            وإلا                                                    \
                movff   ucCriticalNesting,POSTDEC2                  \
            endif                                                   \
            ;                                                       \
            ; Save the new سر_2 د the software ډېری دننه the TCB.    \
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
#تعریف_کړه پورټ_RESTORE_CONTEXT()                                       \
    افعل                                                              \
    {                                                               \
        _Pragma("asm")                                              \
            ;                                                       \
            ; سېټ_2 FSR0 منزل ټکی_2 منزل pxCurrentTCB->px_سر_د_ډېری.      \
            ;                                                       \
            movff   pxCurrentTCB,FSR0L                              \
            movff   pxCurrentTCB+1,FSR0H                            \
            ;                                                       \
            ; De-reference FSR0 منزل سېټ the پته_2 it holds into    \
            ; FSR2 (i.e. *( pxCurrentTCB->px_سر_د_ډېری ) ). FSR2    \
            ; is کارول_شوی by wizC as stackpointer.                      \
            ;                                                       \
            movff   POSTINC0,FSR2L                                  \
            movff   POSTINC0,FSR2H                                  \
            ;                                                       \
            ; بل, the ارزښت لكل ucCriticalNesting کارول_شوی by the     \
            ; task is retrieved from the ډېری.                     \
            ;                                                       \
            movff   PREINC2,ucCriticalNesting                       \
            ;                                                       \
            ; Rebuild the pic call/أرجع-ډېری. The شمېره د      \
            ; أرجع پتې is the بل_2 توکی on the task ډېری.  \
            ; Save this شمېره دننه PRODL. Then fetch the پتې   \
            ; and store them on the hardwarestack.                  \
            ; The datasheets say we can't use movff دلته...         \
            ;                                                       \
            movff   PREINC2,PRODL   // Use PRODL as tempregister    \
            clrf    STKPTR,ACCESS                                   \
        _rtos_R1:                                                   \
            ټېل                                                    \
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
            ; Restore the compiler's working storage area منزل پاڼه 0 \
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
            ; The أرجع from پورټ_RESTORE_CONTEXT() depends on      \
            ; the ارزښت د ucCriticalNesting. When it is zero,      \
            ; interrupts need منزل be enabled. This is بشپړ له_لارې a     \
            ; retfie instruction because we need the                \
            ; مداخله-enabling and the أرجع منزل the restored     \
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

#تعریف_کړه پورټ_TICK_PERIOD_MS  ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )

/*-----------------------------------------------------------*/

خارجي فراغ v_پورټ_Yield( فراغ );
#تعریف_کړه پورټ_YIELD()             v_پورټ_Yield()

#تعریف_کړه پورټ_NOP()   _Pragma("asm")                                  \
                        nop                                         \
                    _Pragma("asmend")

/*-----------------------------------------------------------*/

#تعریف_کړه پورټ_TASK_FUNCTION( xFunction, pvParameters )        \
    فراغ pointed xFunction( فراغ *pvParameters )        \
    _Pragma(asmfunc xFunction)

#تعریف_کړه پورټ_TASK_FUNCTION_PROTO     پورټ_TASK_FUNCTION
/*-----------------------------------------------------------*/


#تعریف_کړه متطاير
#تعریف_کړه سجل

#د_که_پای /* PORTMACRO_H */
