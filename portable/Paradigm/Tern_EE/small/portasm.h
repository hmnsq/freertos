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

#यदि_अपरिभाषितम् पत्तनम्_ASM_H
#परिभाषय पत्तनम्_ASM_H

प्रकारनिर्देश शून्य TCB_t;
बाह्य चञ्चल TCB_t * चञ्चल pxCurrentTCB;
बाह्य शून्य vTaskSwitchContext( शून्य );

/*
 * Saves the stack pointer for one task into its TCB, calls
 * vTaskSwitchContext() to update the TCB being used, then restores the stack
 * from the new TCB read to run the task.
 */
शून्य पत्तनम्_अन्तः_SWITCHING_ISR( शून्य );

/*
 * Load the stack pointer from the TCB of the task which is going to be first
 * to execute.  Then force an IRET so the registers and IP are popped off the
 * stack.
 */
शून्य पत्तनम्_FIRST_CONTEXT( शून्य );

#परिभाषय पत्तनम्_अन्तः_SWITCHING_ISR()                                         \
                            asm { mov   bx, [pxCurrentTCB]          }   \
                            asm { mov   word ptr [bx], sp           }   \
                            asm { call  far ptr vTaskSwitchContext  }   \
                            asm { mov   bx, [pxCurrentTCB]          }   \
                            asm { mov   sp, [bx]                    }

#परिभाषय पत्तनम्_FIRST_CONTEXT()                                         \
                            asm { mov   bx, [pxCurrentTCB]          }   \
                            asm { mov   sp, [bx]                    }   \
                            asm { निष्कासय   bp                          }   \
                            asm { निष्कासय   di                          }   \
                            asm { निष्कासय   si                          }   \
                            asm { निष्कासय   ds                          }   \
                            asm { निष्कासय   es                          }   \
                            asm { निष्कासय   dx                          }   \
                            asm { निष्कासय   cx                          }   \
                            asm { निष्कासय   bx                          }   \
                            asm { निष्कासय   ax                          }   \
                            asm { iret                              }


#यदि_अन्तः
