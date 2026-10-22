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
ಶೂನ್ಯ ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( ಶೂನ್ಯ );

/*
 * Load the stack pointer from the TCB of the task which is going to be first
 * to execute.  Then force an IRET so the registers and IP are popped off the
 * stack.
 */
ಶೂನ್ಯ ಪೋರ್ಟ್_ಮೊದಲ_CONTEXT( ಶೂನ್ಯ );

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR()                                         \
                            asm { mov   bx, [pxCurrentTCB]          }   \
                            asm { mov   ಶಬ್ದ ptr [bx], sp           }   \
                            asm { call  far ptr vTaskSwitchContext  }   \
                            asm { mov   bx, [pxCurrentTCB]          }   \
                            asm { mov   sp, [bx]                    }

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಮೊದಲ_CONTEXT()                                         \
                            asm { mov   bx, [pxCurrentTCB]          }   \
                            asm { mov   sp, [bx]                    }   \
                            asm { ತೆಗೆ_2   bp                          }   \
                            asm { ತೆಗೆ_2   di                          }   \
                            asm { ತೆಗೆ_2   si                          }   \
                            asm { ತೆಗೆ_2   ds                          }   \
                            asm { ತೆಗೆ_2   es                          }   \
                            asm { ತೆಗೆ_2   dx                          }   \
                            asm { ತೆಗೆ_2   cx                          }   \
                            asm { ತೆಗೆ_2   bx                          }   \
                            asm { ತೆಗೆ_2   ax                          }   \
                            asm { iret                              }


#ಆದರೆ_ಅಂತ್ಯ
