/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
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
 */

#నిర్వచితం_కాకపోతే FREERTOS_SDK_CONFIG_H
#నిర్వచించు FREERTOS_SDK_CONFIG_H

#నిర్వచితం_కాకపోతే __ASSEMBLER__
    #అన్తర్భావ "FreeRTOSConfig.h"
    #అన్తర్భావ "rp2040_config.h"
    #నిర్వచితం_కాకపోతే PICO_USE_MALLOC_MUTEX
        /* malloc needs to be made thread safe */
        #నిర్వచించు PICO_USE_MALLOC_MUTEX    1
    #అయితే_ముగింపు /* PICO_USE_MALLOC_MUTEX */
    #ఒకవేళ ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
        /* increase the amount of time it may reasonably take to wake us up */
        #నిర్వచితం_కాకపోతే PICO_సమయం_SLEEP_OVERHEAD_ADJUST_US
            #నిర్వచించు PICO_సమయం_SLEEP_OVERHEAD_ADJUST_US    150
        #అయితే_ముగింపు

        #నిర్వచించు తాళం_owner_id_t                           uint32_t
        బాహ్య uint32_t ul_పోర్టు_తాళం_Get_Current_Owner_Id( శూన్య );
        #నిర్వచించు తాళం_get_caller_owner_id()    ul_పోర్టు_తాళం_Get_Current_Owner_Id()
        #నిర్వచించు తాళం_INVALID_OWNER_ID                     ( ( uint32_t ) -1 )

        నిర్మాణం తాళం_core;
        #నిర్వచితం_కాకపోతే తాళం_అంతర్గత_spin_unlock_with_wait
            బాహ్య శూన్య v_పోర్టు_తాళం_అంతర్గత_Spin_Unlock_With_Wait( నిర్మాణం తాళం_core * px_తాళం,
                                                             uint32_t ulSave );
            #నిర్వచించు తాళం_అంతర్గత_spin_unlock_with_wait( తాళం_3, save )    v_పోర్టు_తాళం_అంతర్గత_Spin_Unlock_With_Wait( తాళం_3, save )
        #అయితే_ముగింపు

        #నిర్వచితం_కాకపోతే తాళం_అంతర్గత_spin_unlock_with_notify
            బాహ్య శూన్య v_పోర్టు_తాళం_అంతర్గత_Spin_Unlock_With_Notify( నిర్మాణం తాళం_core * px_తాళం,
                                                               uint32_t save );
            #నిర్వచించు తాళం_అంతర్గత_spin_unlock_with_notify( తాళం_3, save )    v_పోర్టు_తాళం_అంతర్గత_Spin_Unlock_With_Notify( తాళం_3, save );
        #అయితే_ముగింపు

        #నిర్వచితం_కాకపోతే తాళం_అంతర్గత_spin_unlock_with_ఉత్తమ_effort_wait_or_timeout
            బాహ్య bool x_పోర్టు_తాళం_అంతర్గత_Spin_Unlock_With_ఉత్తమ_Effort_Wait_Or_Timeout( నిర్మాణం తాళం_core * px_తాళం,
                                                                                uint32_t ulSave,
                                                                                absolute_సమయం_t uxUntil );
            #నిర్వచించు తాళం_అంతర్గత_spin_unlock_with_ఉత్తమ_effort_wait_or_timeout( తాళం_3, save, until ) \
    x_పోర్టు_తాళం_అంతర్గత_Spin_Unlock_With_ఉత్తమ_Effort_Wait_Or_Timeout( తాళం_3, save, until )
        #అయితే_ముగింపు
    #అయితే_ముగింపు /* configSUPPORT_PICO_SYNC_INTEROP */

    #ఒకవేళ ( config_SUPPORT_PICO_సమయం_INTEROP == 1 )
        బాహ్య శూన్య x_పోర్టు_Sync_అంతర్గత_Yield_Until_Before( absolute_సమయం_t t );
        #నిర్వచించు sync_అంతర్గత_yield_until_before( t )    x_పోర్టు_Sync_అంతర్గత_Yield_Until_Before( t )
    #అయితే_ముగింపు /* configSUPPORT_PICO_TIME_INTEROP */
#అయితే_ముగింపు /* __ASSEMBLER__ */
#అయితే_ముగింపు /* ifndef FREERTOS_SDK_CONFIG_H */
