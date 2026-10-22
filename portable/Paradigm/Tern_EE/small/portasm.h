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

प्रकारनिर्देश शून्य TCB_t;
बाह्य चञ्चल TCB_t * चञ्चल pxCurrentTCB;
बाह्य शून्य vTaskSwitchContext( शून्य );

/*
 * Saves the stack pointer for one task into its TCB, calls
 * vTaskSwitchContext() to update the TCB being used, then restores the stack
 * from the new TCB read to run the task.
 */
शून्य portEND_SWITCHING_ISR( शून्य );

/*
 * Load the stack pointer from the TCB of the task which is going to be first
 * to execute.  Then force an IRET so the registers and IP are popped off the
 * stack.
 */
शून्य portFIRST_CONTEXT( शून्य );

#define portEND_SWITCHING_ISR()                                         \
                            यंत्र { mov   bx, [pxCurrentTCB]          }   \
                            यंत्र { mov   word ptr [bx], sp           }   \
                            यंत्र { call  far ptr vTaskSwitchContext  }   \
                            यंत्र { mov   bx, [pxCurrentTCB]          }   \
                            यंत्र { mov   sp, [bx]                    }

#define portFIRST_CONTEXT()                                         \
                            यंत्र { mov   bx, [pxCurrentTCB]          }   \
                            यंत्र { mov   sp, [bx]                    }   \
                            यंत्र { झिक   bp                          }   \
                            यंत्र { झिक   di                          }   \
                            यंत्र { झिक   si                          }   \
                            यंत्र { झिक   ds                          }   \
                            यंत्र { झिक   es                          }   \
                            यंत्र { झिक   dx                          }   \
                            यंत्र { झिक   cx                          }   \
                            यंत्र { झिक   bx                          }   \
                            यंत्र { झिक   ax                          }   \
                            यंत्र { iret                              }


#endif
