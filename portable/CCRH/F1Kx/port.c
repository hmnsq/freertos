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

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* This port uses xTaskGetCurrentTaskHandle to get TCB stack, it is required to
 * enable this API. */
#ಆದರೆ ( ( INCLUDE_xTaskGetCurrentTaskHandle != 1 ) && ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 ) )
    #ದೋಷ INCLUDE_xTaskGetCurrentTaskHandle must be ಗಣ ಗಮ್ಯ 1 ಒಳ single core.
#ಆದರೆ_ಅಂತ್ಯ

/***********************************************************
* Macro definitions
***********************************************************/

/* Hardware specific macros */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PSW_ರಿಜಿಸ್ಟರ್_ID          ( 5 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FPSR_ರಿಜಿಸ್ಟರ್_ID         ( 6 )

/* PSW.EBV and PSW.CUx bits are kept as current status */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_PSW_ಮುಖವಾಡ         ( 0x000f8000 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CURRENT_PSW_ಮೌಲ್ಯ        ( ಪೋರ್ಟ್_STSR( ಪೋರ್ಟ್_PSW_ರಿಜಿಸ್ಟರ್_ID ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CURRENT_SR_ZERO_ಮೌಲ್ಯ    ( ( ರಾಶಿ_Type_t ) 0x00000000 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CURRENT_FPSR_ಮೌಲ್ಯ       ( ಪೋರ್ಟ್_STSR( ಪೋರ್ಟ್_FPSR_ರಿಜಿಸ್ಟರ್_ID ) )

/* Mask for FPU configuration bits (FN, PEM, RM, FS) */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_FPSR_ಮುಖವಾಡ        ( 0x00ae0000 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PSW_ID_ಮುಖವಾಡ              ( 0x00000020 )

/* Define necessary hardware IO for OSTM timer. OSTM0 is used by default as
 * it is common for almost device variants. If it conflicts with application,
 * the application shall implement another timer.*/
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_OSTM_EIC_ADDR            ( 0xFFFFB0A8 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_OSTM0_CMP_ADDR            ( 0xFFD70000 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_OSTM0_CTL_ADDR            ( 0xFFD70020 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_OSTM0_TS_ADDR             ( 0xFFD70014 )

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )

/* IPIR  base address, the peripheral is used for Inter-Processor communication
 * Hardware supports 4 channels which is offset by 0x0, 0x4, 0x8, 0xC bytes from
 * base address. By default, channel 0 is selected. */
    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ configIPIR_CHANNEL
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IPIR_ತಳ_ADDR    ( ( 0xFFFEEC80 ) + ( configIPIR_CHANNEL << 2 ) )
    #ಇಲ್ಲದಿದ್ದರೆ
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IPIR_ತಳ_ADDR    ( 0xFFFEEC80 )
    #ಆದರೆ_ಅಂತ್ಯ

/*  Address used for exclusive control for variable shared between PEs
 * (common resources), each CPU cores have independent access path to
 * this address. By default, G0MEV0 register is selected*/
    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ config_EXCLUSIVE_ವಿಳಾಸ
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MEV_ತಳ_ADDR    config_EXCLUSIVE_ವಿಳಾಸ
    #ಇಲ್ಲದಿದ್ದರೆ
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MEV_ತಳ_ADDR    ( 0xFFFEEC00 )
    #ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* if ( configNUMBER_OF_CORES > 1 ) */

/* Macros required to set up the initial stack. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1     ( ( ರಾಶಿ_Type_t ) 0x01010101 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R2     ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x02 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R3     ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x03 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R4     ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x04 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R5     ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x05 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R6     ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x06 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R7     ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x07 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R8     ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x08 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R9     ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x09 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R10    ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x10 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R11    ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x11 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R12    ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x12 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R13    ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x13 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R14    ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x14 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R15    ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x15 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R16    ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x16 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R17    ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x17 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R18    ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x18 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R19    ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x19 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R20    ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x20 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R21    ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x21 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R22    ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x22 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R23    ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x23 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R24    ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x24 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R25    ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x25 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R26    ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x26 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R27    ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x27 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R28    ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x28 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R29    ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x29 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R30    ( ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1 * 0x30 )

/***********************************************************
* Typedef definitions
***********************************************************/

/* OSTM Count Start Trigger Register (OSTMnTS) */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_OSTM_COUNTER_ಆರಂಭ              ( 0x01U ) /* Starts the counter */

/* OSTM Count Stop Trigger Register (OSTMnTT) */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_OSTM_COUNTER_STOP               ( 0x01U ) /* Stops the counter */

/* OSTM Control Register (OSTMnCTL) */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_OSTM_ಬಹುಲಕ_INTERVAL_TIMER        ( 0x00U )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_OSTM_ಬಹುಲಕ_FREE_RUNNING          ( 0x02U )

/* Disables or Enable the interrupts when counting starts */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_OSTM_ಆರಂಭ_ಅಡಚಣೆ_DISABLE    ( 0x00U )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_OSTM_ಆರಂಭ_ಅಡಚಣೆ_ENABLE     ( 0x01U )

/* Interrupt vector method select (TBxxx) */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_ನೇರ_ಸದಿಶ               ( 0x0U )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_ಕೋಷ್ಟಕ_ಸದಿಶ                ( 0x1U )

/* Interrupt mask (MKxxx) */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_PROCESSING_ENABLED          ( 0x0U )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_PROCESSING_DISABLED         ( 0x1U )

/* Specify 16 interrupt priority levels */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_ಆದ್ಯತೆ_HIGHEST            ( 0x0000U ) /* Level 0 (highest) */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_ಆದ್ಯತೆ_LEVEL1             ( 0x0001U ) /* Level 1 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_ಆದ್ಯತೆ_LEVEL2             ( 0x0002U ) /* Level 2 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_ಆದ್ಯತೆ_LEVEL3             ( 0x0003U ) /* Level 3 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_ಆದ್ಯತೆ_LEVEL4             ( 0x0004U ) /* Level 4 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_ಆದ್ಯತೆ_LEVEL5             ( 0x0005U ) /* Level 5 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_ಆದ್ಯತೆ_LEVEL6             ( 0x0006U ) /* Level 6 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_ಆದ್ಯತೆ_LEVEL7             ( 0x0007U ) /* Level 7 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_ಆದ್ಯತೆ_LEVEL8             ( 0x0008U ) /* Level 8 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_ಆದ್ಯತೆ_LEVEL9             ( 0x0009U ) /* Level 9 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_ಆದ್ಯತೆ_LEVEL10            ( 0x000AU ) /* Level 10 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_ಆದ್ಯತೆ_LEVEL11            ( 0x000BU ) /* Level 11 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_ಆದ್ಯತೆ_LEVEL12            ( 0x000CU ) /* Level 12 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_ಆದ್ಯತೆ_LEVEL13            ( 0x000DU ) /* Level 13 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_ಆದ್ಯತೆ_LEVEL14            ( 0x000EU ) /* Level 14 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_ಆದ್ಯತೆ_ಅತಿಕಡಿಮೆ             ( 0x000FU ) /* Level 15 (lowest) */

/* Macros indicating status of scheduler request */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SCHEDULER_NOREQUEST            0UL
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SCHEDULER_TASKSWITCH           1UL       /* Do not modify */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SCHEDULER_STARTFIRSTTASK       2UL       /* Do not modify */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_ಸಿದ್ಧತೆ_TICK_ಅಡಚಣೆ

/* The user has not provided their own tick interrupt configuration so use
 * the definition in this file (which uses the interval timer). */
    #ವ್ಯಾಖ್ಯಾನಿಸು config_ಸಿದ್ಧತೆ_TICK_ಅಡಚಣೆ()    prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ()
#ಆದರೆ_ಅಂತ್ಯ /* configSETUP_TICK_INTERRUPT */

#ಆದರೆ ( !defined( configMAX_INT_NESTING ) || ( configMAX_INT_NESTING == 0 ) )

/* Set the default value for depth of nested interrupt. In theory, the
 * microcontroller have mechanism to limit number of nested level of interrupt
 * by priority (maximum 16 levels). However, the large stack memory should be
 * prepared for each task to save resource in interrupt handler. Therefore, it
 * is necessary to limit depth of nesting interrupt to optimize memory usage.
 * In addition, the execution time of interrupt handler should be very short
 * (typically not exceed 20us), this constraint does not impact to system.
 */
    #ವ್ಯಾಖ್ಯಾನಿಸು configMAX_INT_NESTING    2UL
#ಆದರೆ_ಅಂತ್ಯ

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ );

/*
 * Sets up the periodic ISR used for the RTOS tick using the OSTM.
 * The application writer can define configSETUP_TICK_INTERRUPT() (in
 * FreeRTOSConfig.h) such that their own tick interrupt configuration is used
 * in place of prvSetupTimerInterrupt().
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )

/*
 * Functions implement spin-lock between cores by atomic accesses to Exclusive
 * Control Register (G0MEVm). There are separated access path between CPU cores,
 * but they should wait if access to same register
 */
    ಸ್ಥಿರ ಶೂನ್ಯ prv_Exclusive_ಬೀಗ( ತಳ_Type_t xFromIsr );
    ಸ್ಥಿರ ಶೂನ್ಯ prvExclusiveRelease( ತಳ_Type_t xFromIsr );

#ಆದರೆ_ಅಂತ್ಯ

/*
 * Function to start the first task executing
 */
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ );

/* Scheduler request on each cores which are starting first task and switching
 * context */
ಅಸ್ಥಿರ ತಳ_Type_t x_ಪೋರ್ಟ್_ವೇಳಾಪಟ್ಟಿ_ಸ್ಥಿತಿ[ config_ಸಂಖ್ಯೆ_ದ_CORES ] = { 0 };

/* Counts the interrupt nesting depth. A context switch is only performed if
 * the nesting depth is 0. In addition, the interrupt shares same stack
 * allocated for each tasks. With supporting nesting interrupt, the stack
 * may be overflowed.
 * It is necessary to control maximum stack depth.
 */
ಅಸ್ಥಿರ UBaseType_t ux_ಅಡಚಣೆ_Nesting[ config_ಸಂಖ್ಯೆ_ದ_CORES ] = { 0 };
ಅಸ್ಥಿರ ಸ್ಥಿರಾಂಕ UBaseType_t ux_ಪೋರ್ಟ್_Max_ಅಡಚಣೆ_ಆಳ = configMAX_INT_NESTING;

/* Count number of nested locks by same cores. The lock is completely released
 * only if this count is decreased to 0, the lock is separated for task
 * and isr */
UBaseType_t ux_ಬೀಗ_Nesting[ config_ಸಂಖ್ಯೆ_ದ_CORES ][ 2 ] = { 0 };

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )

/* Pointer to exclusive access memory */
    ಅಸ್ಥಿರ ತಳ_Type_t * px_ಪೋರ್ಟ್_Exclusive_Reg = ( ಅಸ್ಥಿರ ತಳ_Type_t * ) ( ಪೋರ್ಟ್_MEV_ತಳ_ADDR );
#ಆದರೆ_ಅಂತ್ಯ

/* Interrupt handler for OSTM timer which handling tick increment and resulting
 * to switch context. */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Tick_ISR( ಶೂನ್ಯ );

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )

/* Yield specific cores by send inter-processor interrupt */
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield_Core( uint32_t xCoreID );

/*
 * Inter-processor interrupt handler. The interrupt is triggered by
 * portYIELD_CORE().
 */
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_IPIHander( ಶೂನ್ಯ );

/* These functions below implement recursive spinlock for exclusive access among
 * cores. The core will wait until lock will be available, whilst the core which
 * already had lock can acquire lock without waiting. This function could be
 * call from task and interrupt context, the critical section is called
 * as in ISR */
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Recursive_ಬೀಗ_Acquire( ತಳ_Type_t xCoreID, ತಳ_Type_t xFromIsr );
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Recursive_ಬೀಗ_Release( ತಳ_Type_t xCoreID, ತಳ_Type_t xFromIsr );

#ಆದರೆ_ಅಂತ್ಯ /* (configNUMBER_OF_CORES > 1) */

/*-----------------------------------------------------------*/

/*
 * These below functions implement interrupt mask from interrupt. They are not
 * called in nesting, it is protected by FreeRTOS kernel.
 */
ಪೋರ್ಟ್_LONG x_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ( ಶೂನ್ಯ )
{
    ಪೋರ್ಟ್_LONG ulPSWValue = ಪೋರ್ಟ್_STSR( ಪೋರ್ಟ್_PSW_ರಿಜಿಸ್ಟರ್_ID );

    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();

    /* It returns current value of Program Status Word register */
    ಹಿಂತಿರುಗಿ ulPSWValue;
}

/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ( ಪೋರ್ಟ್_LONG ux_Saved_ಅಡಚಣೆ_ಸ್ಥಿತಿ )
{
    ಪೋರ್ಟ್_LONG ulPSWValue = ಪೋರ್ಟ್_STSR( ಪೋರ್ಟ್_PSW_ರಿಜಿಸ್ಟರ್_ID );

    /* Interrupt Disable status is indicates by bit#5 of PSW
    * (1: Interrupt is disabled; 0: Interrupt is enabled) */

    /* Revert to the status before interrupt mask. */
    ulPSWValue &= ( ~( ಪೋರ್ಟ್_PSW_ID_ಮುಖವಾಡ ) );
    ulPSWValue |= ( ಪೋರ್ಟ್_PSW_ID_ಮುಖವಾಡ & ux_Saved_ಅಡಚಣೆ_ಸ್ಥಿತಿ );
    ಪೋರ್ಟ್_LDSR( ಪೋರ್ಟ್_PSW_ರಿಜಿಸ್ಟರ್_ID, ulPSWValue );
}

/*-----------------------------------------------------------*/

/*
 * Using CC-RH intrinsic function to get HTCFG0 (regID, selID) = (0,2)
 * Core ID is indicates by bit HTCFG0.PEID located at bit 18 to 16
 * Bit 31 to 19 are read only and always be read as 0. HTCFG0.PEID is 1 and 2
 * corresponding to core 0 (PE1) and core 1 (PE2). It is adjusted to 0 and 1.
 */
ತಳ_Type_t x_ಪೋರ್ಟ್_GET_CORE_ID( ಶೂನ್ಯ )
{
    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )
        ಹಿಂತಿರುಗಿ ( ಪೋರ್ಟ್_STSR_CCRH( 0, 2 ) >> 16 ) - 1;
    #ಇಲ್ಲದಿದ್ದರೆ

        /* In single core, xPortGET_CORE_ID is used in this port only.
         * The dummy core ID could be controlled inside this port. */
        ಹಿಂತಿರುಗಿ 0;
    #ಆದರೆ_ಅಂತ್ಯ
}

/*-----------------------------------------------------------*/

/*
 * This port supports both multi-cores and single-core, whilst TCB stack
 * variables are different which are respectively pxCurrentTCB (single-core)
 * and pxCurrentTCBs[] (multiple-cores). This function is defined to obtains
 * TCBs of current cores. Also, the C function could switch to corresponding
 * pointer by pre-compile conditions.
 */
ಶೂನ್ಯ * pv_ಪೋರ್ಟ್_Get_Current_TCB( ಶೂನ್ಯ )
{
    ಶೂನ್ಯ * pvCurrentTCB = ( ಶೂನ್ಯ * ) xTaskGetCurrentTaskHandle();

    configASSERT( pvCurrentTCB != ಖಾಲಿ );

    ಹಿಂತಿರುಗಿ pvCurrentTCB;
}

/*-----------------------------------------------------------*/

/*
 * This function checks if a context switch is required and, if so, updates
 * the scheduler status for the core on which the function is called. The
 * scheduler status is set to indicate that a task switch should occur.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಗಣ_Switch( ತಳ_Type_t xSwitchRequired )
{
    ಆದರೆ( xSwitchRequired != pdFALSE )
    {
        x_ಪೋರ್ಟ್_ವೇಳಾಪಟ್ಟಿ_ಸ್ಥಿತಿ[ x_ಪೋರ್ಟ್_GET_CORE_ID() ] = ಪೋರ್ಟ್_SCHEDULER_TASKSWITCH;
    }
}

/*-----------------------------------------------------------*/

/*
 * Setup the stack of a new task so it is ready to be placed under the
 * scheduler control. The registers have to be placed on the stack in the
 * order that the port expects to find them.
 *
 * @param[in]  pxTopOfStack  Pointer to top of this task's stack
 * @param[in]  pxCode        Task function, stored as initial PC for the task
 * @param[in]  pvParameters  Parameters for task
 */
ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    /* Simulate the stack frame as it would be created by
     * a context switch interrupt. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) prvTaskExitError;            /* R31 (LP) */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R5;  /* R5 (TP)  */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters;                /* R6       */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R7;  /* R7       */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R8;  /* R8       */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R9;  /* R9       */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R10; /* R10      */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R11; /* R11      */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R12; /* R12      */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R13; /* R13      */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R14; /* R14      */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R15; /* R15      */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R16; /* R16      */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R17; /* R17      */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R18; /* R18      */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R19; /* R19      */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R20; /* R20      */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R21; /* R21      */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R22; /* R22      */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R23; /* R23      */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R24; /* R24      */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R25; /* R25      */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R26; /* R26      */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R27; /* R27      */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R28; /* R28      */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R29; /* R29      */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R30; /* R30 (EP) */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R1;  /* R1        */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_ರಾಶಿ_INITIAL_ಮೌಲ್ಯ_R2;  /* R2        */

    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* Keep System pre-configuration (HV, CUx, EBV) as current setting in
     * PSW register */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ( ಪೋರ್ಟ್_CURRENT_PSW_ಮೌಲ್ಯ & ಪೋರ್ಟ್_INITIAL_PSW_ಮುಖವಾಡ ); /* EIPSW */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ;                                           /* EIPC */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_CURRENT_SR_ZERO_ಮೌಲ್ಯ;                        /* EIIC */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ( ಪೋರ್ಟ್_CURRENT_PSW_ಮೌಲ್ಯ & ಪೋರ್ಟ್_INITIAL_PSW_ಮುಖವಾಡ ); /* CTPSW */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_CURRENT_SR_ZERO_ಮೌಲ್ಯ;                        /* CTPC */

/* __FPU is defined by CCRH compiler if FPU is enabled */
    #ಆದರೆ ( configENABLE_FPU == 1 )
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ( ಪೋರ್ಟ್_CURRENT_FPSR_ಮೌಲ್ಯ & ಪೋರ್ಟ್_INITIAL_FPSR_ಮುಖವಾಡ ); /* FPSR */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_CURRENT_SR_ZERO_ಮೌಲ್ಯ;                          /* FPEPC */
    #ಆದರೆ_ಅಂತ್ಯ /* (configENABLE_FPU == 1) */

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}

/*-----------------------------------------------------------*/

/*
 * Configures the tick frequency and starts the first task.
 */
ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )
        ತಳ_Type_t xCurrentCore = x_ಪೋರ್ಟ್_GET_CORE_ID();
    #ಆದರೆ_ಅಂತ್ಯ

    /* Prevent interrupt by timer interrupt during starting first task.
     * The interrupt shall be enabled automatically by being restored from
     * task stack */
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();

    /* Setup the tick interrupt */
    config_ಸಿದ್ಧತೆ_TICK_ಅಡಚಣೆ();

    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )
        /* Start scheduler on other cores */
        ಗಾಗಿ( uint16_t xCoreID = 0; xCoreID < config_ಸಂಖ್ಯೆ_ದ_CORES; xCoreID++ )
        {
            ಆದರೆ( xCoreID != xCurrentCore )
            {
                /* Send yielding request to other cores with flag to start
                 * first task. TaskContextSwitch is not executed */
                x_ಪೋರ್ಟ್_ವೇಳಾಪಟ್ಟಿ_ಸ್ಥಿತಿ[ xCoreID ] = ಪೋರ್ಟ್_SCHEDULER_STARTFIRSTTASK;
                v_ಪೋರ್ಟ್_Yield_Core( xCoreID );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                /* Nothing to do. The first task is started in this call by
                 * below vPortStartFirstTask() */
                x_ಪೋರ್ಟ್_ವೇಳಾಪಟ್ಟಿ_ಸ್ಥಿತಿ[ xCoreID ] = ಪೋರ್ಟ್_SCHEDULER_NOREQUEST;
            }
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configNUMBER_OF_CORES > 1 ) */

    /* Start first task in primary core */
    v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task();

    /* Should never get here as the tasks will now be executing! */
    prvTaskExitError();

    /* To prevent compiler warnings in the case that the application writer
     * overrides this functionality by defining configTASK_RETURN_ADDRESS.
     * Call vTaskSwitchContext() so link time optimization does not remove
     * the symbol. */
    vTaskSwitchContext(
        #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )
            xCurrentCore
        #ಆದರೆ_ಅಂತ್ಯ
        );

    ಹಿಂತಿರುಗಿ pdFALSE;
}

/*-----------------------------------------------------------*/

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */

    /* This statement will always fail, triggering the assert */
    configASSERT( pdFALSE );

    /*
     * The following statement may be unreachable because configASSERT(pdFALSE)
     * always triggers an assertion failure, which typically halts program
     * execution.
     * The warning may be reported to indicate to indicate that the compiler
     * detects the subsequent code will not be executed.
     * The warning is acceptable to ensure program is halt regardless of
     * configASSERT(pdFALSE) implementation
     */
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();

    ಗಾಗಿ( ; ; )
    {
        /* Infinite loop to ensure the function does not return. */
    }
}

/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pdFALSE );
}

/*-----------------------------------------------------------*/

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield_Core( uint32_t xCoreID )
    {
        /* Check if we need to yield on a different core */
        ಆದರೆ( xCoreID != x_ಪೋರ್ಟ್_GET_CORE_ID() )
        {
            ಅಸ್ಥಿರ uint32_t * pulIPIRReg;

            /* Determine the IPI register based on the target core ID */
            pulIPIRReg = ( ಅಸ್ಥಿರ uint32_t * ) ( ಪೋರ್ಟ್_IPIR_ತಳ_ADDR );

            /*Inter-processor interrupt generates an interrupt request by
             * writing 1 to applicable bits of target cores. The interrupt
             * should be enabled by application in  corresponding cores
             * including PSW.ID (EI instruction) and interrupt control setting
             * for ICIPIRn channel (interrupt mask, vector method)
             */
            *pulIPIRReg = ( 1 << xCoreID );
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            /* Yielding current core */
            v_ಪೋರ್ಟ್_Yield();
        }
    }

/*-----------------------------------------------------------*/

/*
 * Handler for inter-processor interrupt in second cores. The interrupt is
 * triggered by portYIELD_CORE(). vTaskSwitchContext() is invoked to
 * switch tasks
 */
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_IPIHander( ಶೂನ್ಯ )
    {
        ತಳ_Type_t xCurrentCore = x_ಪೋರ್ಟ್_GET_CORE_ID();

        /* 1st execution starts 1st task, TaskSwitchContext is not executed */
        ಆದರೆ( ಪೋರ್ಟ್_SCHEDULER_STARTFIRSTTASK != x_ಪೋರ್ಟ್_ವೇಳಾಪಟ್ಟಿ_ಸ್ಥಿತಿ[ xCurrentCore ] )
        {
            x_ಪೋರ್ಟ್_ವೇಳಾಪಟ್ಟಿ_ಸ್ಥಿತಿ[ xCurrentCore ] = ಪೋರ್ಟ್_SCHEDULER_TASKSWITCH;
        }
    }

/*-----------------------------------------------------------*/

#ಆದರೆ_ಅಂತ್ಯ /* (configNUMBER_OF_CORES > 1) */

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Tick_ISR( ಶೂನ್ಯ )
{
    /* In case of multicores with SMP,  xTaskIncrementTick is required to
     * called in critical section to avoid conflict resource as this function
     * could be called by xTaskResumeAll() from any cores. */
    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )
        ತಳ_Type_t x_Saved_ಅಡಚಣೆ_ಸ್ಥಿತಿ;

        x_Saved_ಅಡಚಣೆ_ಸ್ಥಿತಿ = ಪೋರ್ಟ್_ENTER_CRITICAL_FROM_ISR();
    #ಆದರೆ_ಅಂತ್ಯ
    {
        /* Increment the RTOS tick. */
        ಆದರೆ( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            x_ಪೋರ್ಟ್_ವೇಳಾಪಟ್ಟಿ_ಸ್ಥಿತಿ[ x_ಪೋರ್ಟ್_GET_CORE_ID() ] = ಪೋರ್ಟ್_SCHEDULER_TASKSWITCH;
        }
    }
    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )
        ಪೋರ್ಟ್_EXIT_CRITICAL_FROM_ISR( x_Saved_ಅಡಚಣೆ_ಸ್ಥಿತಿ );
    #ಆದರೆ_ಅಂತ್ಯ
}

/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    ಅಸ್ಥಿರ uint32_t * pulOSTMIntReg;

    /* Interrupt configuration for OSTM Timer
     * By default, the second lowest priority is set for timer interrupt to
     * avoid blocking other interrupt. Normally, user could set the lowest
     * priority for non-critical event. It try to keep timer on time.
     * In addition, direct vector table is used by default.
     */
    pulOSTMIntReg = ( ಅಸ್ಥಿರ uint32_t * ) ಪೋರ್ಟ್_OSTM_EIC_ADDR;
    *pulOSTMIntReg = ( ಪೋರ್ಟ್_INT_PROCESSING_ENABLED | ಪೋರ್ಟ್_INT_ನೇರ_ಸದಿಶ | ಪೋರ್ಟ್_INT_ಆದ್ಯತೆ_LEVEL14 );

    /* Set OSTM0 control setting */
    *( ( ಅಸ್ಥಿರ uint32_t * ) ಪೋರ್ಟ್_OSTM0_CTL_ADDR ) =
        ( ಪೋರ್ಟ್_OSTM_ಬಹುಲಕ_INTERVAL_TIMER | ಪೋರ್ಟ್_OSTM_ಆರಂಭ_ಅಡಚಣೆ_DISABLE );
    *( ( ಅಸ್ಥಿರ uint32_t * ) ಪೋರ್ಟ್_OSTM0_CMP_ADDR ) =
        ( ( configCPU_CLOCK_HZ / configTIMER_PRESCALE ) / config_TICK_ದರ_HZ ) - 1;

    /* Enable OSTM0 operation */
    *( ( ಅಸ್ಥಿರ uint32_t * ) ಪೋರ್ಟ್_OSTM0_TS_ADDR ) = ಪೋರ್ಟ್_OSTM_COUNTER_ಆರಂಭ;
}

/*-----------------------------------------------------------*/

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )

/*
 * These functions implement spin-lock mechanism among cores using hardware
 * exclusive control with atomic access by CLR1 and SET1 instruction.
 * Nesting calls to these APIs are possible.
 */
    #ಸೂಚನೆ inline_asm prv_Exclusive_ಬೀಗ
    ಸ್ಥಿರ ಶೂನ್ಯ prv_Exclusive_ಬೀಗ( ತಳ_Type_t x_ಬಿಟ್_Position )
    {
        /* No problem with r19, CCRH does not required to restore same value
         * before and after function call. */
        mov     # px_ಪೋರ್ಟ್_Exclusive_Reg_2, r19
        ld.w    0[ r19 ], r19

prv_Exclusive_ಬೀಗ_ಬೀಗ:

        /* r6 is xBitPosition */
        set1 r6, [ r19 ]
        bz prv_Exclusive_ಬೀಗ_ಬೀಗ_success
        snooze
        br prv_Exclusive_ಬೀಗ_ಬೀಗ

prv_Exclusive_ಬೀಗ_ಬೀಗ_success:
    }

/*-----------------------------------------------------------*/

    #ಸೂಚನೆ inline_asm prvExclusiveRelease
    ಸ್ಥಿರ ಶೂನ್ಯ prvExclusiveRelease( ತಳ_Type_t x_ಬಿಟ್_Position )
    {
        mov     # px_ಪೋರ್ಟ್_Exclusive_Reg_2, r19
        ld.w    0[ r19 ], r19

        /* r6 is xBitPosition */
        clr1 r6, [ r19 ]
    }

/*-----------------------------------------------------------*/
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Recursive_ಬೀಗ_Acquire( ತಳ_Type_t xCoreID, ತಳ_Type_t xFromIsr )
    {
        ತಳ_Type_t x_Saved_ಅಡಚಣೆ_ಸ್ಥಿತಿ;
        ತಳ_Type_t x_ಬಿಟ್_Position = ( xFromIsr == pdTRUE );

        x_Saved_ಅಡಚಣೆ_ಸ್ಥಿತಿ = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();

        ಆದರೆ( ux_ಬೀಗ_Nesting[ xCoreID ][ x_ಬಿಟ್_Position ] == 0 )
        {
            prv_Exclusive_ಬೀಗ( x_ಬಿಟ್_Position );
        }

        ux_ಬೀಗ_Nesting[ xCoreID ][ x_ಬಿಟ್_Position ]++;
        ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( x_Saved_ಅಡಚಣೆ_ಸ್ಥಿತಿ );
    }

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Recursive_ಬೀಗ_Release( ತಳ_Type_t xCoreID, ತಳ_Type_t xFromIsr )
    {
        ತಳ_Type_t x_Saved_ಅಡಚಣೆ_ಸ್ಥಿತಿ;
        ತಳ_Type_t x_ಬಿಟ್_Position = ( xFromIsr == pdTRUE );

        x_Saved_ಅಡಚಣೆ_ಸ್ಥಿತಿ = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();

        /* Sync memory */
        ಪೋರ್ಟ್_SYNCM();

        /* Error check whether vPortRecursiveLockRelease() is not called in
         * pair with vPortRecursiveLockAcquire() */
        configASSERT( ( ux_ಬೀಗ_Nesting[ xCoreID ][ x_ಬಿಟ್_Position ] > 0 ) );
        ux_ಬೀಗ_Nesting[ xCoreID ][ x_ಬಿಟ್_Position ]--;

        ಆದರೆ( ux_ಬೀಗ_Nesting[ xCoreID ][ x_ಬಿಟ್_Position ] == 0 )
        {
            prvExclusiveRelease( x_ಬಿಟ್_Position );
        }

        ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( x_Saved_ಅಡಚಣೆ_ಸ್ಥಿತಿ );
    }

/*-----------------------------------------------------------*/

#ಆದರೆ_ಅಂತ್ಯ /* (configNUMBER_OF_CORES > 1) */
