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

#अगर_अघोषित PORT_ASM_H
#घोषणा PORT_ASM_H

प्रकार व्योम TCB_t;
बाह्य अस्थिर TCB_t * अस्थिर pxCurrentTCB;
बाह्य व्योम vTaskSwitchContext( व्योम );

/*
 * Saves the stack pointer for one task into its TCB, calls
 * vTaskSwitchContext() to update the TCB being used, then restores the stack
 * from the new TCB read to run the task.
 */
व्योम portEND_SWITCHING_ISR( व्योम );

/*
 * Load the stack pointer from the TCB of the task which is going to be first
 * to execute.  Then force an IRET so the registers and IP are popped off the
 * stack.
 */
व्योम portFIRST_CONTEXT( व्योम );

#घोषणा portEND_SWITCHING_ISR()                                         \
                            यंत्र { mov   bx, [pxCurrentTCB]          }   \
                            यंत्र { mov   word ptr [bx], sp           }   \
                            यंत्र { call  far ptr vTaskSwitchContext  }   \
                            यंत्र { mov   bx, [pxCurrentTCB]          }   \
                            यंत्र { mov   sp, [bx]                    }

#घोषणा portFIRST_CONTEXT()                                         \
                            यंत्र { mov   bx, [pxCurrentTCB]          }   \
                            यंत्र { mov   sp, [bx]                    }   \
                            यंत्र { निकालो   bp                          }   \
                            यंत्र { निकालो   di                          }   \
                            यंत्र { निकालो   si                          }   \
                            यंत्र { निकालो   ds                          }   \
                            यंत्र { निकालो   es                          }   \
                            यंत्र { निकालो   dx                          }   \
                            यंत्र { निकालो   cx                          }   \
                            यंत्र { निकालो   bx                          }   \
                            यंत्र { निकालो   ax                          }   \
                            यंत्र { iret                              }


#पूर्ण_अगर
