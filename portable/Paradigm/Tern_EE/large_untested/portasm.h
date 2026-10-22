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

തരനിർവചനം ശൂന്യം TCB_t;
ബാഹ്യ അസ്ഥിര TCB_t * അസ്ഥിര pxCurrentTCB;
ബാഹ്യ ശൂന്യം vTaskSwitchContext( ശൂന്യം );

/*
 * Saves the stack pointer for one task into its TCB, calls
 * vTaskSwitchContext() to update the TCB being used, then restores the stack
 * from the new TCB read to run the task.
 */
ശൂന്യം portSWITCH_CONTEXT( ശൂന്യം );

/*
 * Load the stack pointer from the TCB of the task which is going to be first
 * to execute.  Then force an IRET so the registers and IP are popped off the
 * stack.
 */
ശൂന്യം portFIRST_CONTEXT( ശൂന്യം );

#define portSWITCH_CONTEXT()                                         \
                        asm { mov   ax, seg pxCurrentTCB        } \
                            asm { mov   ds, ax                      }  \
                            asm { les   bx, pxCurrentTCB            }   /* Save the stack pointer into the TCB. */    \
                            asm { mov   es:0x2[ bx ], ss            }   \
                            asm { mov   es:[ bx ], sp               }   \
                            asm { call  far ptr vTaskSwitchContext  }   /* Perform the switch. */   \
                            asm { mov   ax, seg pxCurrentTCB        }   /* Restore the stack pointer from the TCB. */  \
                            asm { mov   ds, ax                      }   \
                            asm { les   bx, dword ptr pxCurrentTCB  }   \
                            asm { mov   ss, es:[ bx + 2 ]           }      \
                            asm { mov   sp, es:[ bx ]               }

#define portFIRST_CONTEXT()                                             \
                            asm { mov   ax, seg pxCurrentTCB        }   \
                            asm { mov   ds, ax                      }   \
                            asm { les   bx, dword ptr pxCurrentTCB  }   \
                            asm { mov   ss, es:[ bx + 2 ]           }   \
                            asm { mov   sp, es:[ bx ]               }   \
                            asm { എടുക്കുക   bp                          }   \
                            asm { എടുക്കുക   di                          }   \
                            asm { എടുക്കുക   si                          }   \
                            asm { എടുക്കുക   ds                          }   \
                            asm { എടുക്കുക   es                          }   \
                            asm { എടുക്കുക   dx                          }   \
                            asm { എടുക്കുക   cx                          }   \
                            asm { എടുക്കുക   bx                          }   \
                            asm { എടുക്കുക   ax                          }   \
                            asm { iret                              }
