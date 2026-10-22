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
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

/* This port uses xTaskGetCurrentTaskHandle to get TCB stack, it is required to
 * enable this API. */
#ਜੇ ( ( INCLUDE_xTaskGetCurrentTaskHandle != 1 ) && ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 ) )
    #ਗਲਤੀ INCLUDE_xTaskGetCurrentTaskHandle must be ਸੈੱਟ ਮੰਜ਼ਿਲ 1 ਵਿੱਚ_2 single core.
#ਜੇ_ਅੰਤ

/***********************************************************
* Macro definitions
***********************************************************/

/* Hardware specific macros */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PSW_ਰਜਿਸਟਰ_ID          ( 5 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FPSR_ਰਜਿਸਟਰ_ID         ( 6 )

/* PSW.EBV and PSW.CUx bits are kept as current status */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_PSW_ਨਕਾਬ         ( 0x000f8000 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CURRENT_PSW_ਮੁੱਲ        ( ਪੋਰਟ_STSR( ਪੋਰਟ_PSW_ਰਜਿਸਟਰ_ID ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CURRENT_SR_ZERO_ਮੁੱਲ    ( ( ਢੇਰ_Type_t ) 0x00000000 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CURRENT_FPSR_ਮੁੱਲ       ( ਪੋਰਟ_STSR( ਪੋਰਟ_FPSR_ਰਜਿਸਟਰ_ID ) )

/* Mask for FPU configuration bits (FN, PEM, RM, FS) */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_FPSR_ਨਕਾਬ        ( 0x00ae0000 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PSW_ID_ਨਕਾਬ              ( 0x00000020 )

/* Define necessary hardware IO for OSTM timer. OSTM0 is used by default as
 * it is common for almost device variants. If it conflicts with application,
 * the application shall implement another timer.*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_OSTM_EIC_ADDR            ( 0xFFFFB0A8 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_OSTM0_CMP_ADDR            ( 0xFFD70000 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_OSTM0_CTL_ADDR            ( 0xFFD70020 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_OSTM0_TS_ADDR             ( 0xFFD70014 )

#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )

/* IPIR  base address, the peripheral is used for Inter-Processor communication
 * Hardware supports 4 channels which is offset by 0x0, 0x4, 0x8, 0xC bytes from
 * base address. By default, channel 0 is selected. */
    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ configIPIR_CHANNEL
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IPIR_ਅਧਾਰ_ADDR    ( ( 0xFFFEEC80 ) + ( configIPIR_CHANNEL << 2 ) )
    #ਨਹੀਂਤਾਂ
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IPIR_ਅਧਾਰ_ADDR    ( 0xFFFEEC80 )
    #ਜੇ_ਅੰਤ

/*  Address used for exclusive control for variable shared between PEs
 * (common resources), each CPU cores have independent access path to
 * this address. By default, G0MEV0 register is selected*/
    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ config_EXCLUSIVE_ਪਤਾ
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MEV_ਅਧਾਰ_ADDR    config_EXCLUSIVE_ਪਤਾ
    #ਨਹੀਂਤਾਂ
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MEV_ਅਧਾਰ_ADDR    ( 0xFFFEEC00 )
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* if ( configNUMBER_OF_CORES > 1 ) */

/* Macros required to set up the initial stack. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1     ( ( ਢੇਰ_Type_t ) 0x01010101 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R2     ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x02 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R3     ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x03 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R4     ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x04 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R5     ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x05 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R6     ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x06 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R7     ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x07 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R8     ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x08 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R9     ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x09 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R10    ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x10 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R11    ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x11 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R12    ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x12 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R13    ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x13 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R14    ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x14 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R15    ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x15 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R16    ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x16 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R17    ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x17 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R18    ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x18 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R19    ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x19 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R20    ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x20 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R21    ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x21 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R22    ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x22 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R23    ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x23 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R24    ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x24 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R25    ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x25 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R26    ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x26 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R27    ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x27 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R28    ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x28 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R29    ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x29 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R30    ( ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1 * 0x30 )

/***********************************************************
* Typedef definitions
***********************************************************/

/* OSTM Count Start Trigger Register (OSTMnTS) */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_OSTM_COUNTER_ਸ਼ੁਰੂ              ( 0x01U ) /* Starts the counter */

/* OSTM Count Stop Trigger Register (OSTMnTT) */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_OSTM_COUNTER_STOP               ( 0x01U ) /* Stops the counter */

/* OSTM Control Register (OSTMnCTL) */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_OSTM_ਬਹੁਲਕ_INTERVAL_TIMER        ( 0x00U )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_OSTM_ਬਹੁਲਕ_FREE_RUNNING          ( 0x02U )

/* Disables or Enable the interrupts when counting starts */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_OSTM_ਸ਼ੁਰੂ_ਰੁਕਾਵਟ_DISABLE    ( 0x00U )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_OSTM_ਸ਼ੁਰੂ_ਰੁਕਾਵਟ_ENABLE     ( 0x01U )

/* Interrupt vector method select (TBxxx) */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INT_ਸਿੱਧਾ_ਸਦਿਸ਼               ( 0x0U )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INT_ਸਾਰਣੀ_ਸਦਿਸ਼                ( 0x1U )

/* Interrupt mask (MKxxx) */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INT_PROCESSING_ENABLED          ( 0x0U )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INT_PROCESSING_DISABLED         ( 0x1U )

/* Specify 16 interrupt priority levels */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INT_ਤਰਜੀਹ_HIGHEST            ( 0x0000U ) /* Level 0 (highest) */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INT_ਤਰਜੀਹ_LEVEL1             ( 0x0001U ) /* Level 1 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INT_ਤਰਜੀਹ_LEVEL2             ( 0x0002U ) /* Level 2 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INT_ਤਰਜੀਹ_LEVEL3             ( 0x0003U ) /* Level 3 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INT_ਤਰਜੀਹ_LEVEL4             ( 0x0004U ) /* Level 4 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INT_ਤਰਜੀਹ_LEVEL5             ( 0x0005U ) /* Level 5 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INT_ਤਰਜੀਹ_LEVEL6             ( 0x0006U ) /* Level 6 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INT_ਤਰਜੀਹ_LEVEL7             ( 0x0007U ) /* Level 7 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INT_ਤਰਜੀਹ_LEVEL8             ( 0x0008U ) /* Level 8 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INT_ਤਰਜੀਹ_LEVEL9             ( 0x0009U ) /* Level 9 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INT_ਤਰਜੀਹ_LEVEL10            ( 0x000AU ) /* Level 10 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INT_ਤਰਜੀਹ_LEVEL11            ( 0x000BU ) /* Level 11 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INT_ਤਰਜੀਹ_LEVEL12            ( 0x000CU ) /* Level 12 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INT_ਤਰਜੀਹ_LEVEL13            ( 0x000DU ) /* Level 13 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INT_ਤਰਜੀਹ_LEVEL14            ( 0x000EU ) /* Level 14 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INT_ਤਰਜੀਹ_ਸਭ_ਤੋਂ_ਨੀਵਾਂ             ( 0x000FU ) /* Level 15 (lowest) */

/* Macros indicating status of scheduler request */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SCHEDULER_NOREQUEST            0UL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SCHEDULER_TASKSWITCH           1UL       /* Do not modify */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SCHEDULER_STARTFIRSTTASK       2UL       /* Do not modify */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_ਤਿਆਰੀ_TICK_ਰੁਕਾਵਟ

/* The user has not provided their own tick interrupt configuration so use
 * the definition in this file (which uses the interval timer). */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_ਤਿਆਰੀ_TICK_ਰੁਕਾਵਟ()    prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ()
#ਜੇ_ਅੰਤ /* configSETUP_TICK_INTERRUPT */

#ਜੇ ( !defined( configMAX_INT_NESTING ) || ( configMAX_INT_NESTING == 0 ) )

/* Set the default value for depth of nested interrupt. In theory, the
 * microcontroller have mechanism to limit number of nested level of interrupt
 * by priority (maximum 16 levels). However, the large stack memory should be
 * prepared for each task to save resource in interrupt handler. Therefore, it
 * is necessary to limit depth of nesting interrupt to optimize memory usage.
 * In addition, the execution time of interrupt handler should be very short
 * (typically not exceed 20us), this constraint does not impact to system.
 */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configMAX_INT_NESTING    2UL
#ਜੇ_ਅੰਤ

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ਸਥਿਰ ਖਾਲੀ prvTaskExitError( ਖਾਲੀ );

/*
 * Sets up the periodic ISR used for the RTOS tick using the OSTM.
 * The application writer can define configSETUP_TICK_INTERRUPT() (in
 * FreeRTOSConfig.h) such that their own tick interrupt configuration is used
 * in place of prvSetupTimerInterrupt().
 */
ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );

#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )

/*
 * Functions implement spin-lock between cores by atomic accesses to Exclusive
 * Control Register (G0MEVm). There are separated access path between CPU cores,
 * but they should wait if access to same register
 */
    ਸਥਿਰ ਖਾਲੀ prv_Exclusive_ਤਾਲਾ( ਅਧਾਰ_Type_t xFromIsr );
    ਸਥਿਰ ਖਾਲੀ prvExclusiveRelease( ਅਧਾਰ_Type_t xFromIsr );

#ਜੇ_ਅੰਤ

/*
 * Function to start the first task executing
 */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task( ਖਾਲੀ );

/* Scheduler request on each cores which are starting first task and switching
 * context */
ਅਸਥਿਰ ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸਮਾਂ_ਸਾਰਣੀ_ਸਥਿਤੀ[ config_ਸੰਖਿਆ_ਦਾ_CORES ] = { 0 };

/* Counts the interrupt nesting depth. A context switch is only performed if
 * the nesting depth is 0. In addition, the interrupt shares same stack
 * allocated for each tasks. With supporting nesting interrupt, the stack
 * may be overflowed.
 * It is necessary to control maximum stack depth.
 */
ਅਸਥਿਰ UBaseType_t ux_ਰੁਕਾਵਟ_Nesting[ config_ਸੰਖਿਆ_ਦਾ_CORES ] = { 0 };
ਅਸਥਿਰ ਅਚਲ UBaseType_t ux_ਪੋਰਟ_Max_ਰੁਕਾਵਟ_ਡੂੰਘਾਈ = configMAX_INT_NESTING;

/* Count number of nested locks by same cores. The lock is completely released
 * only if this count is decreased to 0, the lock is separated for task
 * and isr */
UBaseType_t ux_ਤਾਲਾ_Nesting[ config_ਸੰਖਿਆ_ਦਾ_CORES ][ 2 ] = { 0 };

#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )

/* Pointer to exclusive access memory */
    ਅਸਥਿਰ ਅਧਾਰ_Type_t * px_ਪੋਰਟ_Exclusive_Reg = ( ਅਸਥਿਰ ਅਧਾਰ_Type_t * ) ( ਪੋਰਟ_MEV_ਅਧਾਰ_ADDR );
#ਜੇ_ਅੰਤ

/* Interrupt handler for OSTM timer which handling tick increment and resulting
 * to switch context. */
ਖਾਲੀ v_ਪੋਰਟ_Tick_ISR( ਖਾਲੀ );

#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )

/* Yield specific cores by send inter-processor interrupt */
    ਖਾਲੀ v_ਪੋਰਟ_Yield_Core( uint32_t xCoreID );

/*
 * Inter-processor interrupt handler. The interrupt is triggered by
 * portYIELD_CORE().
 */
    ਖਾਲੀ v_ਪੋਰਟ_IPIHander( ਖਾਲੀ );

/* These functions below implement recursive spinlock for exclusive access among
 * cores. The core will wait until lock will be available, whilst the core which
 * already had lock can acquire lock without waiting. This function could be
 * call from task and interrupt context, the critical section is called
 * as in ISR */
    ਖਾਲੀ v_ਪੋਰਟ_Recursive_ਤਾਲਾ_Acquire( ਅਧਾਰ_Type_t xCoreID, ਅਧਾਰ_Type_t xFromIsr );
    ਖਾਲੀ v_ਪੋਰਟ_Recursive_ਤਾਲਾ_Release( ਅਧਾਰ_Type_t xCoreID, ਅਧਾਰ_Type_t xFromIsr );

#ਜੇ_ਅੰਤ /* (configNUMBER_OF_CORES > 1) */

/*-----------------------------------------------------------*/

/*
 * These below functions implement interrupt mask from interrupt. They are not
 * called in nesting, it is protected by FreeRTOS kernel.
 */
ਪੋਰਟ_LONG x_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ( ਖਾਲੀ )
{
    ਪੋਰਟ_LONG ulPSWValue = ਪੋਰਟ_STSR( ਪੋਰਟ_PSW_ਰਜਿਸਟਰ_ID );

    ਪੋਰਟ_DISABLE_INTERRUPTS();

    /* It returns current value of Program Status Word register */
    ਵਾਪਸ ulPSWValue;
}

/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ( ਪੋਰਟ_LONG ux_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ )
{
    ਪੋਰਟ_LONG ulPSWValue = ਪੋਰਟ_STSR( ਪੋਰਟ_PSW_ਰਜਿਸਟਰ_ID );

    /* Interrupt Disable status is indicates by bit#5 of PSW
    * (1: Interrupt is disabled; 0: Interrupt is enabled) */

    /* Revert to the status before interrupt mask. */
    ulPSWValue &= ( ~( ਪੋਰਟ_PSW_ID_ਨਕਾਬ ) );
    ulPSWValue |= ( ਪੋਰਟ_PSW_ID_ਨਕਾਬ & ux_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ );
    ਪੋਰਟ_LDSR( ਪੋਰਟ_PSW_ਰਜਿਸਟਰ_ID, ulPSWValue );
}

/*-----------------------------------------------------------*/

/*
 * Using CC-RH intrinsic function to get HTCFG0 (regID, selID) = (0,2)
 * Core ID is indicates by bit HTCFG0.PEID located at bit 18 to 16
 * Bit 31 to 19 are read only and always be read as 0. HTCFG0.PEID is 1 and 2
 * corresponding to core 0 (PE1) and core 1 (PE2). It is adjusted to 0 and 1.
 */
ਅਧਾਰ_Type_t x_ਪੋਰਟ_GET_CORE_ID( ਖਾਲੀ )
{
    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )
        ਵਾਪਸ ( ਪੋਰਟ_STSR_CCRH( 0, 2 ) >> 16 ) - 1;
    #ਨਹੀਂਤਾਂ

        /* In single core, xPortGET_CORE_ID is used in this port only.
         * The dummy core ID could be controlled inside this port. */
        ਵਾਪਸ 0;
    #ਜੇ_ਅੰਤ
}

/*-----------------------------------------------------------*/

/*
 * This port supports both multi-cores and single-core, whilst TCB stack
 * variables are different which are respectively pxCurrentTCB (single-core)
 * and pxCurrentTCBs[] (multiple-cores). This function is defined to obtains
 * TCBs of current cores. Also, the C function could switch to corresponding
 * pointer by pre-compile conditions.
 */
ਖਾਲੀ * pv_ਪੋਰਟ_Get_Current_TCB( ਖਾਲੀ )
{
    ਖਾਲੀ * pvCurrentTCB = ( ਖਾਲੀ * ) xTaskGetCurrentTaskHandle();

    configASSERT( pvCurrentTCB != ਨਿਰਾ );

    ਵਾਪਸ pvCurrentTCB;
}

/*-----------------------------------------------------------*/

/*
 * This function checks if a context switch is required and, if so, updates
 * the scheduler status for the core on which the function is called. The
 * scheduler status is set to indicate that a task switch should occur.
 */
ਖਾਲੀ v_ਪੋਰਟ_ਸੈੱਟ_Switch( ਅਧਾਰ_Type_t xSwitchRequired )
{
    ਜੇ( xSwitchRequired != pdFALSE )
    {
        x_ਪੋਰਟ_ਸਮਾਂ_ਸਾਰਣੀ_ਸਥਿਤੀ[ x_ਪੋਰਟ_GET_CORE_ID() ] = ਪੋਰਟ_SCHEDULER_TASKSWITCH;
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
ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    /* Simulate the stack frame as it would be created by
     * a context switch interrupt. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) prvTaskExitError;            /* R31 (LP) */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R5;  /* R5 (TP)  */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters;                /* R6       */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R7;  /* R7       */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R8;  /* R8       */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R9;  /* R9       */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R10; /* R10      */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R11; /* R11      */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R12; /* R12      */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R13; /* R13      */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R14; /* R14      */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R15; /* R15      */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R16; /* R16      */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R17; /* R17      */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R18; /* R18      */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R19; /* R19      */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R20; /* R20      */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R21; /* R21      */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R22; /* R22      */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R23; /* R23      */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R24; /* R24      */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R25; /* R25      */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R26; /* R26      */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R27; /* R27      */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R28; /* R28      */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R29; /* R29      */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R30; /* R30 (EP) */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R1;  /* R1        */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_ਢੇਰ_INITIAL_ਮੁੱਲ_R2;  /* R2        */

    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* Keep System pre-configuration (HV, CUx, EBV) as current setting in
     * PSW register */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ( ਪੋਰਟ_CURRENT_PSW_ਮੁੱਲ & ਪੋਰਟ_INITIAL_PSW_ਨਕਾਬ ); /* EIPSW */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ;                                           /* EIPC */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_CURRENT_SR_ZERO_ਮੁੱਲ;                        /* EIIC */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ( ਪੋਰਟ_CURRENT_PSW_ਮੁੱਲ & ਪੋਰਟ_INITIAL_PSW_ਨਕਾਬ ); /* CTPSW */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_CURRENT_SR_ZERO_ਮੁੱਲ;                        /* CTPC */

/* __FPU is defined by CCRH compiler if FPU is enabled */
    #ਜੇ ( configENABLE_FPU == 1 )
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ( ਪੋਰਟ_CURRENT_FPSR_ਮੁੱਲ & ਪੋਰਟ_INITIAL_FPSR_ਨਕਾਬ ); /* FPSR */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_CURRENT_SR_ZERO_ਮੁੱਲ;                          /* FPEPC */
    #ਜੇ_ਅੰਤ /* (configENABLE_FPU == 1) */

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}

/*-----------------------------------------------------------*/

/*
 * Configures the tick frequency and starts the first task.
 */
ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )
        ਅਧਾਰ_Type_t xCurrentCore = x_ਪੋਰਟ_GET_CORE_ID();
    #ਜੇ_ਅੰਤ

    /* Prevent interrupt by timer interrupt during starting first task.
     * The interrupt shall be enabled automatically by being restored from
     * task stack */
    ਪੋਰਟ_DISABLE_INTERRUPTS();

    /* Setup the tick interrupt */
    config_ਤਿਆਰੀ_TICK_ਰੁਕਾਵਟ();

    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )
        /* Start scheduler on other cores */
        ਲਈ( uint16_t xCoreID = 0; xCoreID < config_ਸੰਖਿਆ_ਦਾ_CORES; xCoreID++ )
        {
            ਜੇ( xCoreID != xCurrentCore )
            {
                /* Send yielding request to other cores with flag to start
                 * first task. TaskContextSwitch is not executed */
                x_ਪੋਰਟ_ਸਮਾਂ_ਸਾਰਣੀ_ਸਥਿਤੀ[ xCoreID ] = ਪੋਰਟ_SCHEDULER_STARTFIRSTTASK;
                v_ਪੋਰਟ_Yield_Core( xCoreID );
            }
            ਨਹੀਂਤਾਂ
            {
                /* Nothing to do. The first task is started in this call by
                 * below vPortStartFirstTask() */
                x_ਪੋਰਟ_ਸਮਾਂ_ਸਾਰਣੀ_ਸਥਿਤੀ[ xCoreID ] = ਪੋਰਟ_SCHEDULER_NOREQUEST;
            }
        }
    #ਜੇ_ਅੰਤ /* if ( configNUMBER_OF_CORES > 1 ) */

    /* Start first task in primary core */
    v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();

    /* Should never get here as the tasks will now be executing! */
    prvTaskExitError();

    /* To prevent compiler warnings in the case that the application writer
     * overrides this functionality by defining configTASK_RETURN_ADDRESS.
     * Call vTaskSwitchContext() so link time optimization does not remove
     * the symbol. */
    vTaskSwitchContext(
        #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )
            xCurrentCore
        #ਜੇ_ਅੰਤ
        );

    ਵਾਪਸ pdFALSE;
}

/*-----------------------------------------------------------*/

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ਸਥਿਰ ਖਾਲੀ prvTaskExitError( ਖਾਲੀ )
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
    ਪੋਰਟ_DISABLE_INTERRUPTS();

    ਲਈ( ; ; )
    {
        /* Infinite loop to ensure the function does not return. */
    }
}

/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pdFALSE );
}

/*-----------------------------------------------------------*/

#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )

    ਖਾਲੀ v_ਪੋਰਟ_Yield_Core( uint32_t xCoreID )
    {
        /* Check if we need to yield on a different core */
        ਜੇ( xCoreID != x_ਪੋਰਟ_GET_CORE_ID() )
        {
            ਅਸਥਿਰ uint32_t * pulIPIRReg;

            /* Determine the IPI register based on the target core ID */
            pulIPIRReg = ( ਅਸਥਿਰ uint32_t * ) ( ਪੋਰਟ_IPIR_ਅਧਾਰ_ADDR );

            /*Inter-processor interrupt generates an interrupt request by
             * writing 1 to applicable bits of target cores. The interrupt
             * should be enabled by application in  corresponding cores
             * including PSW.ID (EI instruction) and interrupt control setting
             * for ICIPIRn channel (interrupt mask, vector method)
             */
            *pulIPIRReg = ( 1 << xCoreID );
        }
        ਨਹੀਂਤਾਂ
        {
            /* Yielding current core */
            v_ਪੋਰਟ_Yield();
        }
    }

/*-----------------------------------------------------------*/

/*
 * Handler for inter-processor interrupt in second cores. The interrupt is
 * triggered by portYIELD_CORE(). vTaskSwitchContext() is invoked to
 * switch tasks
 */
    ਖਾਲੀ v_ਪੋਰਟ_IPIHander( ਖਾਲੀ )
    {
        ਅਧਾਰ_Type_t xCurrentCore = x_ਪੋਰਟ_GET_CORE_ID();

        /* 1st execution starts 1st task, TaskSwitchContext is not executed */
        ਜੇ( ਪੋਰਟ_SCHEDULER_STARTFIRSTTASK != x_ਪੋਰਟ_ਸਮਾਂ_ਸਾਰਣੀ_ਸਥਿਤੀ[ xCurrentCore ] )
        {
            x_ਪੋਰਟ_ਸਮਾਂ_ਸਾਰਣੀ_ਸਥਿਤੀ[ xCurrentCore ] = ਪੋਰਟ_SCHEDULER_TASKSWITCH;
        }
    }

/*-----------------------------------------------------------*/

#ਜੇ_ਅੰਤ /* (configNUMBER_OF_CORES > 1) */

ਖਾਲੀ v_ਪੋਰਟ_Tick_ISR( ਖਾਲੀ )
{
    /* In case of multicores with SMP,  xTaskIncrementTick is required to
     * called in critical section to avoid conflict resource as this function
     * could be called by xTaskResumeAll() from any cores. */
    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )
        ਅਧਾਰ_Type_t x_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ;

        x_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ = ਪੋਰਟ_ENTER_CRITICAL_FROM_ISR();
    #ਜੇ_ਅੰਤ
    {
        /* Increment the RTOS tick. */
        ਜੇ( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            x_ਪੋਰਟ_ਸਮਾਂ_ਸਾਰਣੀ_ਸਥਿਤੀ[ x_ਪੋਰਟ_GET_CORE_ID() ] = ਪੋਰਟ_SCHEDULER_TASKSWITCH;
        }
    }
    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )
        ਪੋਰਟ_EXIT_CRITICAL_FROM_ISR( x_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ );
    #ਜੇ_ਅੰਤ
}

/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    ਅਸਥਿਰ uint32_t * pulOSTMIntReg;

    /* Interrupt configuration for OSTM Timer
     * By default, the second lowest priority is set for timer interrupt to
     * avoid blocking other interrupt. Normally, user could set the lowest
     * priority for non-critical event. It try to keep timer on time.
     * In addition, direct vector table is used by default.
     */
    pulOSTMIntReg = ( ਅਸਥਿਰ uint32_t * ) ਪੋਰਟ_OSTM_EIC_ADDR;
    *pulOSTMIntReg = ( ਪੋਰਟ_INT_PROCESSING_ENABLED | ਪੋਰਟ_INT_ਸਿੱਧਾ_ਸਦਿਸ਼ | ਪੋਰਟ_INT_ਤਰਜੀਹ_LEVEL14 );

    /* Set OSTM0 control setting */
    *( ( ਅਸਥਿਰ uint32_t * ) ਪੋਰਟ_OSTM0_CTL_ADDR ) =
        ( ਪੋਰਟ_OSTM_ਬਹੁਲਕ_INTERVAL_TIMER | ਪੋਰਟ_OSTM_ਸ਼ੁਰੂ_ਰੁਕਾਵਟ_DISABLE );
    *( ( ਅਸਥਿਰ uint32_t * ) ਪੋਰਟ_OSTM0_CMP_ADDR ) =
        ( ( configCPU_CLOCK_HZ / configTIMER_PRESCALE ) / config_TICK_ਦਰ_HZ ) - 1;

    /* Enable OSTM0 operation */
    *( ( ਅਸਥਿਰ uint32_t * ) ਪੋਰਟ_OSTM0_TS_ADDR ) = ਪੋਰਟ_OSTM_COUNTER_ਸ਼ੁਰੂ;
}

/*-----------------------------------------------------------*/

#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )

/*
 * These functions implement spin-lock mechanism among cores using hardware
 * exclusive control with atomic access by CLR1 and SET1 instruction.
 * Nesting calls to these APIs are possible.
 */
    #ਹਦਾਇਤ inline_asm prv_Exclusive_ਤਾਲਾ
    ਸਥਿਰ ਖਾਲੀ prv_Exclusive_ਤਾਲਾ( ਅਧਾਰ_Type_t x_ਦੋਆਧਾਰੀ_ਅੰਕ_Position )
    {
        /* No problem with r19, CCRH does not required to restore same value
         * before and after function call. */
        mov     # px_ਪੋਰਟ_Exclusive_Reg_2, r19
        ld.w    0[ r19 ], r19

prv_Exclusive_ਤਾਲਾ_ਤਾਲਾ:

        /* r6 is xBitPosition */
        set1 r6, [ r19 ]
        bz prv_Exclusive_ਤਾਲਾ_ਤਾਲਾ_success
        snooze
        br prv_Exclusive_ਤਾਲਾ_ਤਾਲਾ

prv_Exclusive_ਤਾਲਾ_ਤਾਲਾ_success:
    }

/*-----------------------------------------------------------*/

    #ਹਦਾਇਤ inline_asm prvExclusiveRelease
    ਸਥਿਰ ਖਾਲੀ prvExclusiveRelease( ਅਧਾਰ_Type_t x_ਦੋਆਧਾਰੀ_ਅੰਕ_Position )
    {
        mov     # px_ਪੋਰਟ_Exclusive_Reg_2, r19
        ld.w    0[ r19 ], r19

        /* r6 is xBitPosition */
        clr1 r6, [ r19 ]
    }

/*-----------------------------------------------------------*/
    ਖਾਲੀ v_ਪੋਰਟ_Recursive_ਤਾਲਾ_Acquire( ਅਧਾਰ_Type_t xCoreID, ਅਧਾਰ_Type_t xFromIsr )
    {
        ਅਧਾਰ_Type_t x_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ;
        ਅਧਾਰ_Type_t x_ਦੋਆਧਾਰੀ_ਅੰਕ_Position = ( xFromIsr == pdTRUE );

        x_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ = ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR();

        ਜੇ( ux_ਤਾਲਾ_Nesting[ xCoreID ][ x_ਦੋਆਧਾਰੀ_ਅੰਕ_Position ] == 0 )
        {
            prv_Exclusive_ਤਾਲਾ( x_ਦੋਆਧਾਰੀ_ਅੰਕ_Position );
        }

        ux_ਤਾਲਾ_Nesting[ xCoreID ][ x_ਦੋਆਧਾਰੀ_ਅੰਕ_Position ]++;
        ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( x_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ );
    }

    ਖਾਲੀ v_ਪੋਰਟ_Recursive_ਤਾਲਾ_Release( ਅਧਾਰ_Type_t xCoreID, ਅਧਾਰ_Type_t xFromIsr )
    {
        ਅਧਾਰ_Type_t x_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ;
        ਅਧਾਰ_Type_t x_ਦੋਆਧਾਰੀ_ਅੰਕ_Position = ( xFromIsr == pdTRUE );

        x_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ = ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR();

        /* Sync memory */
        ਪੋਰਟ_SYNCM();

        /* Error check whether vPortRecursiveLockRelease() is not called in
         * pair with vPortRecursiveLockAcquire() */
        configASSERT( ( ux_ਤਾਲਾ_Nesting[ xCoreID ][ x_ਦੋਆਧਾਰੀ_ਅੰਕ_Position ] > 0 ) );
        ux_ਤਾਲਾ_Nesting[ xCoreID ][ x_ਦੋਆਧਾਰੀ_ਅੰਕ_Position ]--;

        ਜੇ( ux_ਤਾਲਾ_Nesting[ xCoreID ][ x_ਦੋਆਧਾਰੀ_ਅੰਕ_Position ] == 0 )
        {
            prvExclusiveRelease( x_ਦੋਆਧਾਰੀ_ਅੰਕ_Position );
        }

        ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( x_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ );
    }

/*-----------------------------------------------------------*/

#ਜੇ_ਅੰਤ /* (configNUMBER_OF_CORES > 1) */
