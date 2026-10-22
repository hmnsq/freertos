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
#నిర్వచితం_కాకపోతే PORTMACRO_H
#నిర్వచించు PORTMACRO_H

#ఒకవేళ !defined(_SERIES) || _SERIES != 18
    #దోషం "WizC supports FreeRTOS on the Microchip PIC18-series only"
#అయితే_ముగింపు

#ఒకవేళ !defined(QUICKCALL) || QUICKCALL != 1
    #దోషం "QuickCall must be enabled (see ProjectOptions/Optimisations)"
#అయితే_ముగింపు

#అన్తర్భావ <stddef.h>
#అన్తర్భావ <pic.h>

#నిర్వచించు పోర్టు_CHAR        అక్షరం
#నిర్వచించు పోర్టు_FLOAT       దశాంశం
#నిర్వచించు పోర్టు_DOUBLE      పోర్టు_FLOAT
#నిర్వచించు పోర్టు_LONG        దీర్ఘ
#నిర్వచించు పోర్టు_SHORT       పొట్టి
#నిర్వచించు పోర్టు_దొంతర_TYPE  uint8_t
#నిర్వచించు పోర్టు_పునాది_TYPE   అక్షరం

రకనిర్వచనం పోర్టు_దొంతర_TYPE దొంతర_Type_t;
రకనిర్వచనం గుర్తుగల అక్షరం పునాది_Type_t;
రకనిర్వచనం గుర్తులేని అక్షరం UBaseType_t;


#ఒకవేళ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_16_బిట్లు )
    రకనిర్వచనం uint16_t TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY ( TickType_t )    ( 0xFFFF )
#లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_32_బిట్లు )
    రకనిర్వచనం uint32_t TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY ( TickType_t )    ( 0xFFFFFFFFUL )
#లేకపోతే
    #దోషం config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు సమితి గమ్యం unsupported tick type వెడల్పు.
#అయితే_ముగింపు

#నిర్వచించు పోర్టు_BYTE_ALIGNMENT          1

/*-----------------------------------------------------------*/

/*
 * Constant used for context switch macro when we require the interrupt
 * enable state to be forced when the interrupted task is switched back in.
 */
#నిర్వచించు పోర్టు_INTERRUPTS_FORCED               (0x01)

/*
 * Constant used for context switch macro when we require the interrupt
 * enable state to be unchanged when the interrupted task is switched back in.
 */
#నిర్వచించు పోర్టు_INTERRUPTS_UNCHANGED            (0x00)

/* Initial interrupt enable state for newly created tasks.  This value is
 * used when a task switches in for the first time.
 */
#నిర్వచించు పోర్టు_INTERRUPTS_INITIAL_STATE        (పోర్టు_INTERRUPTS_FORCED)

/*
 * Macros to modify the global interrupt enable bit in INTCON.
 */
#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()    \
    చేయి                              \
    {                               \
        bGIE=0;                     \
    } అయితే(bGIE)   // MicroChip recommends this check!

#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()     \
    చేయి                              \
    {                               \
        bGIE=1;                     \
    } అయితే(0)

/*-----------------------------------------------------------*/

/*
 * Critical section macros.
 */
బాహ్య uint8_t ucCriticalNesting;

#నిర్వచించు పోర్టు_NO_CRITICAL_SECTION_NESTING     ( ( uint8_t ) 0 )

#నిర్వచించు పోర్టు_ENTER_CRITICAL()                                        \
    చేయి                                                              \
    {                                                               \
        పోర్టు_DISABLE_INTERRUPTS();                                   \
                                                                    \
        /*                                                          \
         * Now interrupts are disabled ucCriticalNesting            \
         * can be accessed directly. Increment                      \
         * ucCriticalNesting to keep a count of how                 \
         * many times portENTER_CRITICAL() has been called.         \
         */                                                         \
        ucCriticalNesting++;                                        \
    } అయితే(0)

#నిర్వచించు పోర్టు_EXIT_CRITICAL()                                         \
    చేయి                                                              \
    {                                                               \
        ఒకవేళ(ucCriticalNesting > పోర్టు_NO_CRITICAL_SECTION_NESTING)     \
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
        ఒకవేళ( ucCriticalNesting == పోర్టు_NO_CRITICAL_SECTION_NESTING )  \
        {                                                           \
            పోర్టు_ENABLE_INTERRUPTS();                                \
        }                                                           \
    } అయితే(0)

/*-----------------------------------------------------------*/

/*
 * The minimal stacksize is calculated on the first reference of
 * portMINIMAL_STACK_SIZE. Some input to this calculation is
 * compile time determined, other input is port-defined (see port.c)
 */
బాహ్య uint16_t us_పోర్టు_CALCULATE_కనీస_దొంతర_కొలత( శూన్య );
బాహ్య uint16_t us_Calc_Min_దొంతర_కొలత;

#నిర్వచించు పోర్టు_కనీస_దొంతర_కొలత                  \
    ((us_Calc_Min_దొంతర_కొలత == 0)                  \
        ? us_పోర్టు_CALCULATE_కనీస_దొంతర_కొలత()  \
        : us_Calc_Min_దొంతర_కొలత )

/*
 * WizC uses a downgrowing stack
 */
#నిర్వచించు పోర్టు_దొంతర_GROWTH            ( -1 )

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

#నిర్వచించు పోర్టు_SAVE_CONTEXT( uc_అంతరాయం_Forced )                       \
    చేయి                                                              \
    {                                                               \
        పోర్టు_DISABLE_INTERRUPTS();                                   \
                                                                    \
        _Pragma("asm")                                              \
            ;                                                       \
            ; నెట్టు_3 the relevant SFR's onto the task's దొంతర         \
            ;                                                       \
            movff   స్థితి_3,POSTDEC2                                 \
            movff   WREG,POSTDEC2                                   \
            movff   BSR,POSTDEC2                                    \
            movff   PRODH,POSTDEC2                                  \
            movff   PRODL,POSTDEC2                                  \
            movff   FSR0H,POSTDEC2                                  \
            movff   FSR0L,POSTDEC2                                  \
            movff   FSR1H,POSTDEC2                                  \
            movff   FSR1L,POSTDEC2                                  \
            movff   TABLAT,POSTDEC2                                 \
            ఒకవేళ __ROMSIZE > 0x8000                                   \
                movff   TBLPTRU,POSTDEC2                            \
            endif                                                   \
            movff   TBLPTRH,POSTDEC2                                \
            movff   TBLPTRL,POSTDEC2                                \
            ఒకవేళ __ROMSIZE > 0x8000                                   \
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
            ; Save the pic call/తిరిగి-దొంతర belonging గమ్యం the       \
            ; current task by copying it గమ్యం the task's software-    \
            ; దొంతర. We save the hardware దొంతర సూచిక_3 (which      \
            ; is the సంఖ్య యొక్క చిరునామాలు on the దొంతర) లోపల the       \
            ; W-నమోదు మొదటి_2 because we need it later and it      \
            ; is modified లోపల the save-loop by executing తీయి's.      \
            ; After the loop the W-నమోదు is stored on the        \
            ; దొంతర, too.                                           \
            ;                                                       \
            movf    STKPTR,W,ACCESS                                 \
            bz      _rtos_s3                                        \
        _rtos_S2:                                                   \
            ఒకవేళ __ROMSIZE > 0x8000                                   \
                movff   TOSU,POSTDEC2                               \
            endif                                                   \
            movff   TOSH,POSTDEC2                                   \
            movff   TOSL,POSTDEC2                                   \
            తీయి                                                     \
            tstfsz  STKPTR,ACCESS                                   \
            SMARTJUMP _rtos_S2                                      \
        _rtos_s3:                                                   \
            movwf   POSTDEC2,ACCESS                                 \
            ;                                                       \
            ; తదుపరి the విలువ కొరకు ucCriticalNesting వాడిన by the      \
            ; task is stored on the దొంతర. When                     \
            ; (uc_అంతరాయం_Forced == పోర్టు_INTERRUPTS_FORCED), we save \
            ; it as 0 (పోర్టు_NO_CRITICAL_SECTION_NESTING).            \
            ;                                                       \
            ఒకవేళ uc_అంతరాయం_Forced == పోర్టు_INTERRUPTS_FORCED           \
                clrf POSTDEC2,ACCESS                                \
            లేకపోతే                                                    \
                movff   ucCriticalNesting,POSTDEC2                  \
            endif                                                   \
            ;                                                       \
            ; Save the new శిఖరం_2 యొక్క the software దొంతర లోపల the TCB.    \
            ;                                                       \
            movff   pxCurrentTCB,FSR0L                              \
            movff   pxCurrentTCB+1,FSR0H                            \
            movff   FSR2L,POSTINC0                                  \
            movff   FSR2H,POSTINC0                                  \
        _Pragma("asmend")                                           \
    } అయితే(0)

/************************************************************/

/*
 * This is the reverse of portSAVE_CONTEXT.
 */
#నిర్వచించు పోర్టు_RESTORE_CONTEXT()                                       \
    చేయి                                                              \
    {                                                               \
        _Pragma("asm")                                              \
            ;                                                       \
            ; సమితి_2 FSR0 గమ్యం బిందువు_2 గమ్యం pxCurrentTCB->px_శిఖరం_యొక్క_దొంతర.      \
            ;                                                       \
            movff   pxCurrentTCB,FSR0L                              \
            movff   pxCurrentTCB+1,FSR0H                            \
            ;                                                       \
            ; De-reference FSR0 గమ్యం సమితి the చిరునామా_2 it holds into    \
            ; FSR2 (i.e. *( pxCurrentTCB->px_శిఖరం_యొక్క_దొంతర ) ). FSR2    \
            ; is వాడిన by wizC as stackpointer.                      \
            ;                                                       \
            movff   POSTINC0,FSR2L                                  \
            movff   POSTINC0,FSR2H                                  \
            ;                                                       \
            ; తదుపరి, the విలువ కొరకు ucCriticalNesting వాడిన by the     \
            ; task is retrieved from the దొంతర.                     \
            ;                                                       \
            movff   PREINC2,ucCriticalNesting                       \
            ;                                                       \
            ; Rebuild the pic call/తిరిగి-దొంతర. The సంఖ్య యొక్క      \
            ; తిరిగి చిరునామాలు is the తదుపరి_2 అంశం on the task దొంతర.  \
            ; Save this సంఖ్య లోపల PRODL. Then fetch the చిరునామాలు   \
            ; and store them on the hardwarestack.                  \
            ; The datasheets say we can't use movff ఇక్కడ...         \
            ;                                                       \
            movff   PREINC2,PRODL   // Use PRODL as tempregister    \
            clrf    STKPTR,ACCESS                                   \
        _rtos_R1:                                                   \
            నెట్టు                                                    \
            movf    PREINC2,W,ACCESS                                \
            movwf   TOSL,ACCESS                                     \
            movf    PREINC2,W,ACCESS                                \
            movwf   TOSH,ACCESS                                     \
            ఒకవేళ __ROMSIZE > 0x8000                                   \
                movf    PREINC2,W,ACCESS                            \
                movwf   TOSU,ACCESS                                 \
            లేకపోతే                                                    \
                clrf    TOSU,ACCESS                                 \
            endif                                                   \
            decfsz  PRODL,F,ACCESS                                  \
            SMARTJUMP _rtos_R1                                      \
            ;                                                       \
            ; Restore the compiler's working storage area గమ్యం పుట 0 \
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
            ; we need these registers కొరకు a final test.             \
            ;                                                       \
            movff   PREINC2,PCLATH                                  \
            ఒకవేళ __ROMSIZE > 0x8000                                   \
                movff   PREINC2,PCLATU                              \
            లేకపోతే                                                    \
                clrf    PCLATU,ACCESS                               \
            endif                                                   \
            movff   PREINC2,TBLPTRL                                 \
            movff   PREINC2,TBLPTRH                                 \
            ఒకవేళ __ROMSIZE > 0x8000                                   \
                movff   PREINC2,TBLPTRU                             \
            లేకపోతే                                                    \
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
            ; The తిరిగి from పోర్టు_RESTORE_CONTEXT() depends on      \
            ; the విలువ యొక్క ucCriticalNesting. When it is zero,      \
            ; interrupts need గమ్యం be enabled. This is పూర్తి ద్వారా a     \
            ; retfie instruction because we need the                \
            ; అంతరాయం-enabling and the తిరిగి గమ్యం the restored     \
            ; task గమ్యం be uninterruptible.                           \
            ; Because bsr, status and W are affected by the test    \
            ; they are restored after the test.                     \
            ;                                                       \
            movlb   ucCriticalNesting>>8                            \
            tstfsz  ucCriticalNesting,BANKED                        \
            SMARTJUMP _rtos_R4                                      \
        _rtos_R3:                                                   \
            movff   PREINC2,BSR                                     \
            movff   PREINC2,WREG                                    \
            movff   PREINC2,స్థితి_3                                  \
            retfie  0       ; Return enabling interrupts            \
        _rtos_R4:                                                   \
            movff   PREINC2,BSR                                     \
            movff   PREINC2,WREG                                    \
            movff   PREINC2,స్థితి_3                                  \
            తిరిగి  0       ; Return without affecting interrupts   \
        _Pragma("asmend")                                           \
    } అయితే(0)

/*-----------------------------------------------------------*/

#నిర్వచించు పోర్టు_TICK_PERIOD_MS  ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )

/*-----------------------------------------------------------*/

బాహ్య శూన్య v_పోర్టు_Yield( శూన్య );
#నిర్వచించు పోర్టు_YIELD()             v_పోర్టు_Yield()

#నిర్వచించు పోర్టు_NOP()   _Pragma("asm")                                  \
                        nop                                         \
                    _Pragma("asmend")

/*-----------------------------------------------------------*/

#నిర్వచించు పోర్టు_TASK_FUNCTION( xFunction, pvParameters )        \
    శూన్య pointed xFunction( శూన్య *pvParameters )        \
    _Pragma(asmfunc xFunction)

#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO     పోర్టు_TASK_FUNCTION
/*-----------------------------------------------------------*/


#నిర్వచించు అస్థిర
#నిర్వచించు నమోదు

#అయితే_ముగింపు /* PORTMACRO_H */
