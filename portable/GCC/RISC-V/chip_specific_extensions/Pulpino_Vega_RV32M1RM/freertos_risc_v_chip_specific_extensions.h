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
 * The FreeRTOS kernel's RISC-V port is split between the code that is
 * common across all currently supported RISC-V chips (implementations of the
 * RISC-V ISA), and code that tailors the port to a specific RISC-V chip:
 *
 * + FreeRTOS\Source\portable\GCC\RISC-V\portASM.S contains the code that
 *   is common to all currently supported RISC-V chips.  There is only one
 *   portASM.S file because the same file is built for all RISC-V target chips.
 *
 * + Header files called freertos_risc_v_chip_specific_extensions.h contain the
 *   code that tailors the FreeRTOS kernel's RISC-V port to a specific RISC-V
 *   chip.  There are multiple freertos_risc_v_chip_specific_extensions.h files
 *   as there are multiple RISC-V chip implementations.
 *
 * !!!NOTE!!!
 * TAKE CARE TO INCLUDE THE CORRECT freertos_risc_v_chip_specific_extensions.h
 * HEADER FILE FOR THE CHIP IN USE.  This is done using the assembler's (not the
 * compiler's!) include path.  For example, if the chip in use includes a core
 * local interrupter (CLINT) and does not include any chip specific register
 * extensions then add the path below to the assembler's include path:
 * FreeRTOS\Source\portable\GCC\RISC-V\chip_specific_extensions\RV32I_CLINT_no_extensions
 *
 */

/*
 * This freertos_risc_v_chip_specific_extensions.h is for use with Pulpino Ri5cy
 * devices, developed and tested using the Vega board RV32M1RM.
 */

#నిర్వచితం_కాకపోతే __FREERTOS_RISC_V_EXTENSIONS_H__
#నిర్వచించు __FREERTOS_RISC_V_EXTENSIONS_H__

#నిర్వచించు portasmHAS_MTIME                  0

/* Constants to define the additional registers found on the Pulpino RI5KY. */
#నిర్వచించు lpstart0                          0x7b0
#నిర్వచించు lpend0                            0x7b1
#నిర్వచించు lpcount0                          0x7b2
#నిర్వచించు lpstart1                          0x7b4
#నిర్వచించు lpend1                            0x7b5
#నిర్వచించు lpcount1                          0x7b6

/* Six additional registers to save and restore, as per the #defines above. */
#నిర్వచించు portasm_ADDITIONAL_CONTEXT_కొలత    6 /* Must be even number on 32-bit cores. */

/* Save additional registers found on the Pulpino. */
.macro portasmSAVE_ADDITIONAL_REGISTERS
addi sp, sp, -( portasm_ADDITIONAL_CONTEXT_కొలత * పోర్టు_మాట_కొలత ) /* Make room for the additional registers. */
csrr t0, lpstart0                                                /* Load additional registers into accessible temporary registers. */
csrr t1, lpend0
csrr t2, lpcount0
csrr t3, lpstart1
csrr t4, lpend1
csrr t5, lpcount1
sw t0, 1 * పోర్టు_మాట_కొలత( sp )
sw t1, 2 * పోర్టు_మాట_కొలత( sp )
sw t2, 3 * పోర్టు_మాట_కొలత( sp )
sw t3, 4 * పోర్టు_మాట_కొలత( sp )
sw t4, 5 * పోర్టు_మాట_కొలత( sp )
sw t5, 6 * పోర్టు_మాట_కొలత( sp )
   .endm

/* Restore the additional registers found on the Pulpino. */
   .macro portasmRESTORE_ADDITIONAL_REGISTERS
lw t0, 1 * పోర్టు_మాట_కొలత( sp ) /* Load additional registers into accessible temporary registers. */
lw t1, 2 * పోర్టు_మాట_కొలత( sp )
lw t2, 3 * పోర్టు_మాట_కొలత( sp )
lw t3, 4 * పోర్టు_మాట_కొలత( sp )
lw t4, 5 * పోర్టు_మాట_కొలత( sp )
lw t5, 6 * పోర్టు_మాట_కొలత( sp )
csrw lpstart0, t0
csrw lpend0, t1
csrw lpcount0, t2
csrw lpstart1, t3
csrw lpend1, t4
csrw lpcount1, t5
addi sp, sp, ( portasm_ADDITIONAL_CONTEXT_కొలత * పోర్టు_మాట_కొలత ) /* Remove space added for additional registers. */
   .endm

#అయితే_ముగింపు /* __FREERTOS_RISC_V_EXTENSIONS_H__ */
