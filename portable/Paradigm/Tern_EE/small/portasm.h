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

#ifndef PORT_ASM_H
#define PORT_ASM_H

প্রকারলেখ শূন্য TCB_t;
বাহ্যিক অস্থির TCB_t * অস্থির pxCurrentTCB;
বাহ্যিক শূন্য vTaskSwitchContext( শূন্য );

/*
 * Saves the stack pointer for one task into its TCB, calls
 * vTaskSwitchContext() to update the TCB being used, then restores the stack
 * from the new TCB read to run the task.
 */
শূন্য portEND_SWITCHING_ISR( শূন্য );

/*
 * Load the stack pointer from the TCB of the task which is going to be first
 * to execute.  Then force an IRET so the registers and IP are popped off the
 * stack.
 */
শূন্য portFIRST_CONTEXT( শূন্য );

#define portEND_SWITCHING_ISR()                                         \
                            asm { mov   bx, [pxCurrentTCB]          }   \
                            asm { mov   word ptr [bx], sp           }   \
                            asm { call  far ptr vTaskSwitchContext  }   \
                            asm { mov   bx, [pxCurrentTCB]          }   \
                            asm { mov   sp, [bx]                    }

#define portFIRST_CONTEXT()                                         \
                            asm { mov   bx, [pxCurrentTCB]          }   \
                            asm { mov   sp, [bx]                    }   \
                            asm { বের_করো   bp                          }   \
                            asm { বের_করো   di                          }   \
                            asm { বের_করো   si                          }   \
                            asm { বের_করো   ds                          }   \
                            asm { বের_করো   es                          }   \
                            asm { বের_করো   dx                          }   \
                            asm { বের_করো   cx                          }   \
                            asm { বের_করো   bx                          }   \
                            asm { বের_করো   ax                          }   \
                            asm { iret                              }


#endif
