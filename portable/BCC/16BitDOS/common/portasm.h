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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ಪೋರ್ಟ್_ASM_H
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ASM_H

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ TCB_t;
ಬಾಹ್ಯ ಅಸ್ಥಿರ TCB_t * ಅಸ್ಥಿರ pxCurrentTCB;
ಬಾಹ್ಯ ಶೂನ್ಯ vTaskSwitchContext( ಶೂನ್ಯ );

/*
 * Saves the stack pointer for one task into its TCB, calls
 * vTaskSwitchContext() to update the TCB being used, then restores the stack
 * from the new TCB read to run the task.
 */
ಶೂನ್ಯ ಪೋರ್ಟ್_SWITCH_CONTEXT( ಶೂನ್ಯ );

/*
 * Load the stack pointer from the TCB of the task which is going to be first
 * to execute.  Then force an IRET so the registers and IP are popped off the
 * stack.
 */
ಶೂನ್ಯ ಪೋರ್ಟ್_ಮೊದಲ_CONTEXT( ಶೂನ್ಯ );

/* There are slightly different versions depending on whether you are building
to include debugger information.  If debugger information is used then there
are a couple of extra bytes left of the ISR stack (presumably for use by the
debugger).  The true stack pointer is then stored in the bp register.  We add
2 to the stack pointer to remove the extra bytes before we restore our context. */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SWITCH_CONTEXT()                                            \
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

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಮೊದಲ_CONTEXT()                                             \
                            __asm { mov ax, seg pxCurrentTCB        }   \
                            __asm { mov ds, ax                      }   \
                            __asm { les bx, dword ptr pxCurrentTCB  }   \
                            __asm { mov ss, es:[ bx + 2 ]           }   \
                            __asm { mov sp, es:[ bx ]               }   \
                            __asm { ತೆಗೆ_2 bp                          }   \
                            __asm { ತೆಗೆ_2 di                          }   \
                            __asm { ತೆಗೆ_2 si                          }   \
                            __asm { ತೆಗೆ_2 ds                          }   \
                            __asm { ತೆಗೆ_2 es                          }   \
                            __asm { ತೆಗೆ_2 dx                          }   \
                            __asm { ತೆಗೆ_2 cx                          }   \
                            __asm { ತೆಗೆ_2 bx                          }   \
                            __asm { ತೆಗೆ_2 ax                          }   \
                            __asm { iret                            }


#ಆದರೆ_ಅಂತ್ಯ
