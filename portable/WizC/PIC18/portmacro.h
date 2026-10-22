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
#यदि_अपरिभाषितम् PORTMACRO_H
#परिभाषय PORTMACRO_H

#यदि !defined(_SERIES) || _SERIES != 18
    #दोषः "WizC supports FreeRTOS on the Microchip PIC18-series only"
#यदि_अन्तः

#यदि !defined(QUICKCALL) || QUICKCALL != 1
    #दोषः "QuickCall must be enabled (see ProjectOptions/Optimisations)"
#यदि_अन्तः

#अन्तर्भाव <stddef.h>
#अन्तर्भाव <pic.h>

#परिभाषय पत्तनम्_CHAR        वर्ण
#परिभाषय पत्तनम्_FLOAT       भिन्न
#परिभाषय पत्तनम्_DOUBLE      पत्तनम्_FLOAT
#परिभाषय पत्तनम्_LONG        दीर्घ
#परिभाषय पत्तनम्_SHORT       ह्रस्व
#परिभाषय पत्तनम्_राशिः_TYPE  uint8_t
#परिभाषय पत्तनम्_आधारः_TYPE   वर्ण

प्रकारनिर्देश पत्तनम्_राशिः_TYPE राशिः_Type_t;
प्रकारनिर्देश चिह्नित वर्ण आधारः_Type_t;
प्रकारनिर्देश अचिह्नित वर्ण UBaseType_t;


#यदि( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
    प्रकारनिर्देश uint16_t TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY ( TickType_t )    ( 0xFFFF )
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
    प्रकारनिर्देश uint32_t TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY ( TickType_t )    ( 0xFFFFFFFFUL )
#अन्यथा
    #दोषः config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः समुच्चयः गन्तव्यम् unsupported tick type विस्तारः.
#यदि_अन्तः

#परिभाषय पत्तनम्_BYTE_ALIGNMENT          1

/*-----------------------------------------------------------*/

/*
 * Constant used for context switch macro when we require the interrupt
 * enable state to be forced when the interrupted task is switched back in.
 */
#परिभाषय पत्तनम्_INTERRUPTS_FORCED               (0x01)

/*
 * Constant used for context switch macro when we require the interrupt
 * enable state to be unchanged when the interrupted task is switched back in.
 */
#परिभाषय पत्तनम्_INTERRUPTS_UNCHANGED            (0x00)

/* Initial interrupt enable state for newly created tasks.  This value is
 * used when a task switches in for the first time.
 */
#परिभाषय पत्तनम्_INTERRUPTS_INITIAL_STATE        (पत्तनम्_INTERRUPTS_FORCED)

/*
 * Macros to modify the global interrupt enable bit in INTCON.
 */
#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()    \
    कुरु                              \
    {                               \
        bGIE=0;                     \
    } यावत्(bGIE)   // MicroChip recommends this check!

#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()     \
    कुरु                              \
    {                               \
        bGIE=1;                     \
    } यावत्(0)

/*-----------------------------------------------------------*/

/*
 * Critical section macros.
 */
बाह्य uint8_t ucCriticalNesting;

#परिभाषय पत्तनम्_NO_CRITICAL_SECTION_NESTING     ( ( uint8_t ) 0 )

#परिभाषय पत्तनम्_ENTER_CRITICAL()                                        \
    कुरु                                                              \
    {                                                               \
        पत्तनम्_DISABLE_INTERRUPTS();                                   \
                                                                    \
        /*                                                          \
         * Now interrupts are disabled ucCriticalNesting            \
         * can be accessed directly. Increment                      \
         * ucCriticalNesting to keep a count of how                 \
         * many times portENTER_CRITICAL() has been called.         \
         */                                                         \
        ucCriticalNesting++;                                        \
    } यावत्(0)

#परिभाषय पत्तनम्_EXIT_CRITICAL()                                         \
    कुरु                                                              \
    {                                                               \
        यदि(ucCriticalNesting > पत्तनम्_NO_CRITICAL_SECTION_NESTING)     \
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
        यदि( ucCriticalNesting == पत्तनम्_NO_CRITICAL_SECTION_NESTING )  \
        {                                                           \
            पत्तनम्_ENABLE_INTERRUPTS();                                \
        }                                                           \
    } यावत्(0)

/*-----------------------------------------------------------*/

/*
 * The minimal stacksize is calculated on the first reference of
 * portMINIMAL_STACK_SIZE. Some input to this calculation is
 * compile time determined, other input is port-defined (see port.c)
 */
बाह्य uint16_t us_पत्तनम्_CALCULATE_अल्पिष्ठम्_राशिः_आकार( शून्य );
बाह्य uint16_t us_Calc_Min_राशिः_आकार;

#परिभाषय पत्तनम्_अल्पिष्ठम्_राशिः_आकार                  \
    ((us_Calc_Min_राशिः_आकार == 0)                  \
        ? us_पत्तनम्_CALCULATE_अल्पिष्ठम्_राशिः_आकार()  \
        : us_Calc_Min_राशिः_आकार )

/*
 * WizC uses a downgrowing stack
 */
#परिभाषय पत्तनम्_राशिः_GROWTH            ( -1 )

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

#परिभाषय पत्तनम्_SAVE_CONTEXT( uc_व्यवधानम्_Forced )                       \
    कुरु                                                              \
    {                                                               \
        पत्तनम्_DISABLE_INTERRUPTS();                                   \
                                                                    \
        _Pragma("asm")                                              \
            ;                                                       \
            ; प्रक्षिप_3 the relevant SFR's onto the task's राशिः         \
            ;                                                       \
            movff   स्थितिः_2,POSTDEC2                                 \
            movff   WREG,POSTDEC2                                   \
            movff   BSR,POSTDEC2                                    \
            movff   PRODH,POSTDEC2                                  \
            movff   PRODL,POSTDEC2                                  \
            movff   FSR0H,POSTDEC2                                  \
            movff   FSR0L,POSTDEC2                                  \
            movff   FSR1H,POSTDEC2                                  \
            movff   FSR1L,POSTDEC2                                  \
            movff   TABLAT,POSTDEC2                                 \
            यदि __ROMSIZE > 0x8000                                   \
                movff   TBLPTRU,POSTDEC2                            \
            endif                                                   \
            movff   TBLPTRH,POSTDEC2                                \
            movff   TBLPTRL,POSTDEC2                                \
            यदि __ROMSIZE > 0x8000                                   \
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
            ; Save the pic call/प्रत्यागम-राशिः belonging गन्तव्यम् the       \
            ; current task by copying it गन्तव्यम् the task's software-    \
            ; राशिः. We save the hardware राशिः pointer (which      \
            ; is the सङ्ख्या सम्बन्धि स्थानाङ्काः on the राशिः) अन्तर् the       \
            ; W-पञ्जिका first because we need it later and it      \
            ; is modified अन्तर् the save-loop by executing निष्कासय's.      \
            ; After the loop the W-पञ्जिका is stored on the        \
            ; राशिः, too.                                           \
            ;                                                       \
            movf    STKPTR,W,ACCESS                                 \
            bz      _rtos_s3                                        \
        _rtos_S2:                                                   \
            यदि __ROMSIZE > 0x8000                                   \
                movff   TOSU,POSTDEC2                               \
            endif                                                   \
            movff   TOSH,POSTDEC2                                   \
            movff   TOSL,POSTDEC2                                   \
            निष्कासय                                                     \
            tstfsz  STKPTR,ACCESS                                   \
            SMARTJUMP _rtos_S2                                      \
        _rtos_s3:                                                   \
            movwf   POSTDEC2,ACCESS                                 \
            ;                                                       \
            ; अग्र the मानम् प्रति ucCriticalNesting प्रयुक्तम् by the      \
            ; task is stored on the राशिः. When                     \
            ; (uc_व्यवधानम्_Forced == पत्तनम्_INTERRUPTS_FORCED), we save \
            ; it as 0 (पत्तनम्_NO_CRITICAL_SECTION_NESTING).            \
            ;                                                       \
            यदि uc_व्यवधानम्_Forced == पत्तनम्_INTERRUPTS_FORCED           \
                clrf POSTDEC2,ACCESS                                \
            अन्यथा                                                    \
                movff   ucCriticalNesting,POSTDEC2                  \
            endif                                                   \
            ;                                                       \
            ; Save the new शिखरम्_2 सम्बन्धि the software राशिः अन्तर् the TCB.    \
            ;                                                       \
            movff   pxCurrentTCB,FSR0L                              \
            movff   pxCurrentTCB+1,FSR0H                            \
            movff   FSR2L,POSTINC0                                  \
            movff   FSR2H,POSTINC0                                  \
        _Pragma("asmend")                                           \
    } यावत्(0)

/************************************************************/

/*
 * This is the reverse of portSAVE_CONTEXT.
 */
#परिभाषय पत्तनम्_RESTORE_CONTEXT()                                       \
    कुरु                                                              \
    {                                                               \
        _Pragma("asm")                                              \
            ;                                                       \
            ; समुच्चयः_2 FSR0 गन्तव्यम् point गन्तव्यम् pxCurrentTCB->px_शिखरम्_सम्बन्धि_राशिः.      \
            ;                                                       \
            movff   pxCurrentTCB,FSR0L                              \
            movff   pxCurrentTCB+1,FSR0H                            \
            ;                                                       \
            ; De-reference FSR0 गन्तव्यम् समुच्चयः the स्थानाङ्कः_2 it holds into    \
            ; FSR2 (i.e. *( pxCurrentTCB->px_शिखरम्_सम्बन्धि_राशिः ) ). FSR2    \
            ; is प्रयुक्तम् by wizC as stackpointer.                      \
            ;                                                       \
            movff   POSTINC0,FSR2L                                  \
            movff   POSTINC0,FSR2H                                  \
            ;                                                       \
            ; अग्र, the मानम् प्रति ucCriticalNesting प्रयुक्तम् by the     \
            ; task is retrieved from the राशिः.                     \
            ;                                                       \
            movff   PREINC2,ucCriticalNesting                       \
            ;                                                       \
            ; Rebuild the pic call/प्रत्यागम-राशिः. The सङ्ख्या सम्बन्धि      \
            ; प्रत्यागम स्थानाङ्काः is the अग्र_2 item on the task राशिः.  \
            ; Save this सङ्ख्या अन्तर् PRODL. Then fetch the स्थानाङ्काः   \
            ; and store them on the hardwarestack.                  \
            ; The datasheets say we can't use movff अत्र...         \
            ;                                                       \
            movff   PREINC2,PRODL   // Use PRODL as tempregister    \
            clrf    STKPTR,ACCESS                                   \
        _rtos_R1:                                                   \
            प्रक्षिप                                                    \
            movf    PREINC2,W,ACCESS                                \
            movwf   TOSL,ACCESS                                     \
            movf    PREINC2,W,ACCESS                                \
            movwf   TOSH,ACCESS                                     \
            यदि __ROMSIZE > 0x8000                                   \
                movf    PREINC2,W,ACCESS                            \
                movwf   TOSU,ACCESS                                 \
            अन्यथा                                                    \
                clrf    TOSU,ACCESS                                 \
            endif                                                   \
            decfsz  PRODL,F,ACCESS                                  \
            SMARTJUMP _rtos_R1                                      \
            ;                                                       \
            ; Restore the compiler's working storage area गन्तव्यम् page 0 \
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
            ; we need these registers प्रति a final test.             \
            ;                                                       \
            movff   PREINC2,PCLATH                                  \
            यदि __ROMSIZE > 0x8000                                   \
                movff   PREINC2,PCLATU                              \
            अन्यथा                                                    \
                clrf    PCLATU,ACCESS                               \
            endif                                                   \
            movff   PREINC2,TBLPTRL                                 \
            movff   PREINC2,TBLPTRH                                 \
            यदि __ROMSIZE > 0x8000                                   \
                movff   PREINC2,TBLPTRU                             \
            अन्यथा                                                    \
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
            ; The प्रत्यागम from पत्तनम्_RESTORE_CONTEXT() depends on      \
            ; the मानम् सम्बन्धि ucCriticalNesting. When it is zero,      \
            ; interrupts need गन्तव्यम् be enabled. This is समाप्तम् द्वारा a     \
            ; retfie instruction because we need the                \
            ; व्यवधानम्-enabling and the प्रत्यागम गन्तव्यम् the restored     \
            ; task गन्तव्यम् be uninterruptible.                           \
            ; Because bsr, status and W are affected by the test    \
            ; they are restored after the test.                     \
            ;                                                       \
            movlb   ucCriticalNesting>>8                            \
            tstfsz  ucCriticalNesting,BANKED                        \
            SMARTJUMP _rtos_R4                                      \
        _rtos_R3:                                                   \
            movff   PREINC2,BSR                                     \
            movff   PREINC2,WREG                                    \
            movff   PREINC2,स्थितिः_2                                  \
            retfie  0       ; Return enabling interrupts            \
        _rtos_R4:                                                   \
            movff   PREINC2,BSR                                     \
            movff   PREINC2,WREG                                    \
            movff   PREINC2,स्थितिः_2                                  \
            प्रत्यागम  0       ; Return without affecting interrupts   \
        _Pragma("asmend")                                           \
    } यावत्(0)

/*-----------------------------------------------------------*/

#परिभाषय पत्तनम्_TICK_PERIOD_MS  ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )

/*-----------------------------------------------------------*/

बाह्य शून्य v_पत्तनम्_Yield( शून्य );
#परिभाषय पत्तनम्_YIELD()             v_पत्तनम्_Yield()

#परिभाषय पत्तनम्_NOP()   _Pragma("asm")                                  \
                        nop                                         \
                    _Pragma("asmend")

/*-----------------------------------------------------------*/

#परिभाषय पत्तनम्_TASK_FUNCTION( xFunction, pvParameters )        \
    शून्य pointed xFunction( शून्य *pvParameters )        \
    _Pragma(asmfunc xFunction)

#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO     पत्तनम्_TASK_FUNCTION
/*-----------------------------------------------------------*/


#परिभाषय चञ्चल
#परिभाषय पञ्जिका

#यदि_अन्तः /* PORTMACRO_H */
