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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ਪੋਰਟ_ASM_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ASM_H

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ TCB_t;
ਬਾਹਰੀ ਅਸਥਿਰ TCB_t * ਅਸਥਿਰ pxCurrentTCB;
ਬਾਹਰੀ ਖਾਲੀ vTaskSwitchContext( ਖਾਲੀ );

/*
 * Saves the stack pointer for one task into its TCB, calls
 * vTaskSwitchContext() to update the TCB being used, then restores the stack
 * from the new TCB read to run the task.
 */
ਖਾਲੀ ਪੋਰਟ_SWITCH_CONTEXT( ਖਾਲੀ );

/*
 * Load the stack pointer from the TCB of the task which is going to be first
 * to execute.  Then force an IRET so the registers and IP are popped off the
 * stack.
 */
ਖਾਲੀ ਪੋਰਟ_ਪਹਿਲਾ_CONTEXT( ਖਾਲੀ );

/* There are slightly different versions depending on whether you are building
to include debugger information.  If debugger information is used then there
are a couple of extra bytes left of the ISR stack (presumably for use by the
debugger).  The true stack pointer is then stored in the bp register.  We add
2 to the stack pointer to remove the extra bytes before we restore our context. */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SWITCH_CONTEXT()                                            \
                            asm { mov   ax, seg pxCurrentTCB        }   \
                            asm { mov   ds, ax                      }   \
                            asm { les   bx, pxCurrentTCB            }   /* Save the stack pointer into the TCB. */      \
                            asm { mov   es:0x2[ bx ], ss            }   \
                            asm { mov   es:[ bx ], sp               }   \
                            asm { call  far ptr vTaskSwitchContext  }   /* Perform the switch. */                       \
                            asm { mov   ax, seg pxCurrentTCB        }   /* Restore the stack pointer from the TCB. */   \
                            asm { mov   ds, ax                      }   \
                            asm { les   bx, dword ptr pxCurrentTCB  }   \
                            asm { mov   ss, es:[ bx + 2 ]           }   \
                            asm { mov   sp, es:[ bx ]               }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਪਹਿਲਾ_CONTEXT()                                             \
                            __asm { mov ax, seg pxCurrentTCB        }   \
                            __asm { mov ds, ax                      }   \
                            __asm { les bx, dword ptr pxCurrentTCB  }   \
                            __asm { mov ss, es:[ bx + 2 ]           }   \
                            __asm { mov sp, es:[ bx ]               }   \
                            __asm { ਕੱਢੋ bp                          }   \
                            __asm { ਕੱਢੋ di                          }   \
                            __asm { ਕੱਢੋ si                          }   \
                            __asm { ਕੱਢੋ ds                          }   \
                            __asm { ਕੱਢੋ es                          }   \
                            __asm { ਕੱਢੋ dx                          }   \
                            __asm { ਕੱਢੋ cx                          }   \
                            __asm { ਕੱਢੋ bx                          }   \
                            __asm { ਕੱਢੋ ax                          }   \
                            __asm { iret                            }


#ਜੇ_ਅੰਤ
