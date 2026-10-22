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
#अगर_अघोषित PORTMACRO_H
#घोषणा PORTMACRO_H

#अगर !defined(_SERIES) || _SERIES != 18
    #त्रुटि "WizC supports FreeRTOS on the Microchip PIC18-series only"
#पूर्ण_अगर

#अगर !defined(QUICKCALL) || QUICKCALL != 1
    #त्रुटि "QuickCall must be enabled (see ProjectOptions/Optimisations)"
#पूर्ण_अगर

#समावेश <stddef.h>
#समावेश <pic.h>

#घोषणा portCHAR        अक्षर
#घोषणा portFLOAT       भग्न
#घोषणा portDOUBLE      portFLOAT
#घोषणा portLONG        दीर्घ
#घोषणा portSHORT       लघु
#घोषणा port_ढेर_TYPE  uint8_t
#घोषणा portBASE_TYPE   अक्षर

प्रकार port_ढेर_TYPE ढेर_Type_t;
प्रकार चिन्हित अक्षर BaseType_t;
प्रकार अचिन्हित अक्षर UBaseType_t;


#अगर( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    प्रकार uint16_t TickType_t;
    #घोषणा portMAX_DELAY ( TickType_t )    ( 0xFFFF )
#या_अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    प्रकार uint32_t TickType_t;
    #घोषणा portMAX_DELAY ( TickType_t )    ( 0xFFFFFFFFUL )
#अन्यथा
    #त्रुटि configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#पूर्ण_अगर

#घोषणा portBYTE_ALIGNMENT          1

/*-----------------------------------------------------------*/

/*
 * Constant used for context switch macro when we require the interrupt
 * enable state to be forced when the interrupted task is switched back in.
 */
#घोषणा portINTERRUPTS_FORCED               (0x01)

/*
 * Constant used for context switch macro when we require the interrupt
 * enable state to be unchanged when the interrupted task is switched back in.
 */
#घोषणा portINTERRUPTS_UNCHANGED            (0x00)

/* Initial interrupt enable state for newly created tasks.  This value is
 * used when a task switches in for the first time.
 */
#घोषणा portINTERRUPTS_INITIAL_STATE        (portINTERRUPTS_FORCED)

/*
 * Macros to modify the global interrupt enable bit in INTCON.
 */
#घोषणा portDISABLE_INTERRUPTS()    \
    करो                              \
    {                               \
        bGIE=0;                     \
    } जबतक(bGIE)   // MicroChip recommends this check!

#घोषणा portENABLE_INTERRUPTS()     \
    करो                              \
    {                               \
        bGIE=1;                     \
    } जबतक(0)

/*-----------------------------------------------------------*/

/*
 * Critical section macros.
 */
बाह्य uint8_t ucCriticalNesting;

#घोषणा portNO_CRITICAL_SECTION_NESTING     ( ( uint8_t ) 0 )

#घोषणा portENTER_CRITICAL()                                        \
    करो                                                              \
    {                                                               \
        portDISABLE_INTERRUPTS();                                   \
                                                                    \
        /*                                                          \
         * Now interrupts are disabled ucCriticalNesting            \
         * can be accessed directly. Increment                      \
         * ucCriticalNesting to keep a count of how                 \
         * many times portENTER_CRITICAL() has been called.         \
         */                                                         \
        ucCriticalNesting++;                                        \
    } जबतक(0)

#घोषणा portEXIT_CRITICAL()                                         \
    करो                                                              \
    {                                                               \
        अगर(ucCriticalNesting > portNO_CRITICAL_SECTION_NESTING)     \
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
        अगर( ucCriticalNesting == portNO_CRITICAL_SECTION_NESTING )  \
        {                                                           \
            portENABLE_INTERRUPTS();                                \
        }                                                           \
    } जबतक(0)

/*-----------------------------------------------------------*/

/*
 * The minimal stacksize is calculated on the first reference of
 * portMINIMAL_STACK_SIZE. Some input to this calculation is
 * compile time determined, other input is port-defined (see port.c)
 */
बाह्य uint16_t us_Port_CALCULATE_MINIMAL_ढेर_आकार( व्योम );
बाह्य uint16_t us_Calc_Min_ढेर_आकार;

#घोषणा port_MINIMAL_ढेर_आकार                  \
    ((us_Calc_Min_ढेर_आकार == 0)                  \
        ? us_Port_CALCULATE_MINIMAL_ढेर_आकार()  \
        : us_Calc_Min_ढेर_आकार )

/*
 * WizC uses a downgrowing stack
 */
#घोषणा port_ढेर_GROWTH            ( -1 )

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

#घोषणा portSAVE_CONTEXT( ucInterruptForced )                       \
    करो                                                              \
    {                                                               \
        portDISABLE_INTERRUPTS();                                   \
                                                                    \
        _Pragma("asm")                                              \
            ;                                                       \
            ; धकेलो_3 the relevant SFR's onto the task's ढेर         \
            ;                                                       \
            movff   STATUS,POSTDEC2                                 \
            movff   WREG,POSTDEC2                                   \
            movff   BSR,POSTDEC2                                    \
            movff   PRODH,POSTDEC2                                  \
            movff   PRODL,POSTDEC2                                  \
            movff   FSR0H,POSTDEC2                                  \
            movff   FSR0L,POSTDEC2                                  \
            movff   FSR1H,POSTDEC2                                  \
            movff   FSR1L,POSTDEC2                                  \
            movff   TABLAT,POSTDEC2                                 \
            अगर __ROMSIZE > 0x8000                                   \
                movff   TBLPTRU,POSTDEC2                            \
            endif                                                   \
            movff   TBLPTRH,POSTDEC2                                \
            movff   TBLPTRL,POSTDEC2                                \
            अगर __ROMSIZE > 0x8000                                   \
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
            ; Save the pic call/वापस-ढेर belonging to the       \
            ; current task by copying it to the task's software-    \
            ; ढेर. We save the hardware ढेर pointer (which      \
            ; is the संख्या of addresses on the ढेर) in the       \
            ; W-रेजिस्टर first because we need it later and it      \
            ; is modified in the save-loop by executing निकालो's.      \
            ; After the loop the W-रेजिस्टर is stored on the        \
            ; ढेर, too.                                           \
            ;                                                       \
            movf    STKPTR,W,ACCESS                                 \
            bz      _rtos_s3                                        \
        _rtos_S2:                                                   \
            अगर __ROMSIZE > 0x8000                                   \
                movff   TOSU,POSTDEC2                               \
            endif                                                   \
            movff   TOSH,POSTDEC2                                   \
            movff   TOSL,POSTDEC2                                   \
            निकालो                                                     \
            tstfsz  STKPTR,ACCESS                                   \
            SMARTJUMP _rtos_S2                                      \
        _rtos_s3:                                                   \
            movwf   POSTDEC2,ACCESS                                 \
            ;                                                       \
            ; अग्र the मूल्य क्रम ucCriticalNesting used by the      \
            ; task is stored on the ढेर. When                     \
            ; (ucInterruptForced == portINTERRUPTS_FORCED), we save \
            ; it as 0 (portNO_CRITICAL_SECTION_NESTING).            \
            ;                                                       \
            अगर ucInterruptForced == portINTERRUPTS_FORCED           \
                clrf POSTDEC2,ACCESS                                \
            अन्यथा                                                    \
                movff   ucCriticalNesting,POSTDEC2                  \
            endif                                                   \
            ;                                                       \
            ; Save the new शीर्ष_2 of the software ढेर in the TCB.    \
            ;                                                       \
            movff   pxCurrentTCB,FSR0L                              \
            movff   pxCurrentTCB+1,FSR0H                            \
            movff   FSR2L,POSTINC0                                  \
            movff   FSR2H,POSTINC0                                  \
        _Pragma("asmend")                                           \
    } जबतक(0)

/************************************************************/

/*
 * This is the reverse of portSAVE_CONTEXT.
 */
#घोषणा portRESTORE_CONTEXT()                                       \
    करो                                                              \
    {                                                               \
        _Pragma("asm")                                              \
            ;                                                       \
            ; Set FSR0 to point to pxCurrentTCB->px_शीर्ष_Of_ढेर.      \
            ;                                                       \
            movff   pxCurrentTCB,FSR0L                              \
            movff   pxCurrentTCB+1,FSR0H                            \
            ;                                                       \
            ; De-reference FSR0 to set the address it holds into    \
            ; FSR2 (i.e. *( pxCurrentTCB->px_शीर्ष_Of_ढेर ) ). FSR2    \
            ; is used by wizC as stackpointer.                      \
            ;                                                       \
            movff   POSTINC0,FSR2L                                  \
            movff   POSTINC0,FSR2H                                  \
            ;                                                       \
            ; अग्र, the मूल्य क्रम ucCriticalNesting used by the     \
            ; task is retrieved from the ढेर.                     \
            ;                                                       \
            movff   PREINC2,ucCriticalNesting                       \
            ;                                                       \
            ; Rebuild the pic call/वापस-ढेर. The संख्या of      \
            ; वापस addresses is the अग्र_2 item on the task ढेर.  \
            ; Save this संख्या in PRODL. Then fetch the addresses   \
            ; and store them on the hardwarestack.                  \
            ; The datasheets say we can't use movff here...         \
            ;                                                       \
            movff   PREINC2,PRODL   // Use PRODL as tempregister    \
            clrf    STKPTR,ACCESS                                   \
        _rtos_R1:                                                   \
            धकेलो                                                    \
            movf    PREINC2,W,ACCESS                                \
            movwf   TOSL,ACCESS                                     \
            movf    PREINC2,W,ACCESS                                \
            movwf   TOSH,ACCESS                                     \
            अगर __ROMSIZE > 0x8000                                   \
                movf    PREINC2,W,ACCESS                            \
                movwf   TOSU,ACCESS                                 \
            अन्यथा                                                    \
                clrf    TOSU,ACCESS                                 \
            endif                                                   \
            decfsz  PRODL,F,ACCESS                                  \
            SMARTJUMP _rtos_R1                                      \
            ;                                                       \
            ; Restore the compiler's working storage area to page 0 \
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
            ; we need these registers क्रम a final test.             \
            ;                                                       \
            movff   PREINC2,PCLATH                                  \
            अगर __ROMSIZE > 0x8000                                   \
                movff   PREINC2,PCLATU                              \
            अन्यथा                                                    \
                clrf    PCLATU,ACCESS                               \
            endif                                                   \
            movff   PREINC2,TBLPTRL                                 \
            movff   PREINC2,TBLPTRH                                 \
            अगर __ROMSIZE > 0x8000                                   \
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
            ; The वापस from portRESTORE_CONTEXT() depends on      \
            ; the मूल्य of ucCriticalNesting. When it is zero,      \
            ; interrupts need to be enabled. This is done via a     \
            ; retfie instruction because we need the                \
            ; interrupt-enabling and the वापस to the restored     \
            ; task to be uninterruptible.                           \
            ; Because bsr, status and W are affected by the test    \
            ; they are restored after the test.                     \
            ;                                                       \
            movlb   ucCriticalNesting>>8                            \
            tstfsz  ucCriticalNesting,BANKED                        \
            SMARTJUMP _rtos_R4                                      \
        _rtos_R3:                                                   \
            movff   PREINC2,BSR                                     \
            movff   PREINC2,WREG                                    \
            movff   PREINC2,STATUS                                  \
            retfie  0       ; Return enabling interrupts            \
        _rtos_R4:                                                   \
            movff   PREINC2,BSR                                     \
            movff   PREINC2,WREG                                    \
            movff   PREINC2,STATUS                                  \
            वापस  0       ; Return without affecting interrupts   \
        _Pragma("asmend")                                           \
    } जबतक(0)

/*-----------------------------------------------------------*/

#घोषणा portTICK_PERIOD_MS  ( ( TickType_t ) 1000 / configTICK_RATE_HZ )

/*-----------------------------------------------------------*/

बाह्य व्योम vPortYield( व्योम );
#घोषणा portYIELD()             vPortYield()

#घोषणा portNOP()   _Pragma("asm")                                  \
                        nop                                         \
                    _Pragma("asmend")

/*-----------------------------------------------------------*/

#घोषणा portTASK_FUNCTION( xFunction, pvParameters )        \
    व्योम pointed xFunction( व्योम *pvParameters )        \
    _Pragma(asmfunc xFunction)

#घोषणा portTASK_FUNCTION_PROTO     portTASK_FUNCTION
/*-----------------------------------------------------------*/


#घोषणा अस्थिर
#घोषणा रेजिस्टर

#पूर्ण_अगर /* PORTMACRO_H */
