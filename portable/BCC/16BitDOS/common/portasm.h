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
शून्य portSWITCH_CONTEXT( शून्य );

/*
 * Load the stack pointer from the TCB of the task which is going to be first
 * to execute.  Then force an IRET so the registers and IP are popped off the
 * stack.
 */
शून्य portFIRST_CONTEXT( शून्य );

/* There are slightly different versions depending on whether you are building
to include debugger information.  If debugger information is used then there
are a couple of extra bytes left of the ISR stack (presumably for use by the
debugger).  The true stack pointer is then stored in the bp register.  We add
2 to the stack pointer to remove the extra bytes before we restore our context. */

#define portSWITCH_CONTEXT()                                            \
                            यंत्र { mov   ax, seg pxCurrentTCB        }   \
                            यंत्र { mov   ds, ax                      }   \
                            यंत्र { les   bx, pxCurrentTCB            }   /* Save the stack pointer into the TCB. */      \
                            यंत्र { mov   es:0x2[ bx ], ss            }   \
                            यंत्र { mov   es:[ bx ], sp               }   \
                            यंत्र { call  far ptr vTaskSwitchContext  }   /* Perform the switch. */                       \
                            यंत्र { mov   ax, seg pxCurrentTCB        }   /* Restore the stack pointer from the TCB. */   \
                            यंत्र { mov   ds, ax                      }   \
                            यंत्र { les   bx, dword ptr pxCurrentTCB  }   \
                            यंत्र { mov   ss, es:[ bx + 2 ]           }   \
                            यंत्र { mov   sp, es:[ bx ]               }

#define portFIRST_CONTEXT()                                             \
                            __asm { mov ax, seg pxCurrentTCB        }   \
                            __asm { mov ds, ax                      }   \
                            __asm { les bx, dword ptr pxCurrentTCB  }   \
                            __asm { mov ss, es:[ bx + 2 ]           }   \
                            __asm { mov sp, es:[ bx ]               }   \
                            __asm { निकालो bp                          }   \
                            __asm { निकालो di                          }   \
                            __asm { निकालो si                          }   \
                            __asm { निकालो ds                          }   \
                            __asm { निकालो es                          }   \
                            __asm { निकालो dx                          }   \
                            __asm { निकालो cx                          }   \
                            __asm { निकालो bx                          }   \
                            __asm { निकालो ax                          }   \
                            __asm { iret                            }


#endif
