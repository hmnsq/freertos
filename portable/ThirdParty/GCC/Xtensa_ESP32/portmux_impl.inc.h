/*
 * SPDX-FileCopyrightText: 2017-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */


/*
 * Warning: funky preprocessor hackery ahead. Including these headers will generate two
 * functions, which names are defined by the preprocessor macros
 * PORTMUX_AQUIRE_MUX_FN_NAME and PORTMUX_RELEASE_MUX_FN_NAME. In order to do the compare
 * and exchange function, they will use whatever PORTMUX_COMPARE_SET_FN_NAME resolves to.
 *
 * In some scenarios, this header is included *twice* in portmux_impl.h: one time
 * for the 'normal' mux code which uses a compare&exchange routine, another time
 * to generate code for a second set of these routines that use a second mux
 * (in internal ram) to fake a compare&exchange on a variable in external memory.
 */



ساكن مضمن bool __attribute__( ( always_inline ) )
#اگر_تعریف_شده CONFIG_FREERTOS_PORTMUX_DEBUG
    PORTMUX_AQUIRE_MUX_FN_NAME( پورت_MUX_TYPE * mux,
                                صحيح timeout_چرخهها,
                                ثابت حرف * fnName,
                                صحيح سطر )
    {
#وإلا
    PORTMUX_AQUIRE_MUX_FN_NAME( پورت_MUX_TYPE * mux, صحيح timeout_چرخهها )
    {
        #پایان_اگر


        #إذا !CONFIG_FREERTOS_UNICORE
            uint32_t res;
            پورت_پایه_TYPE coreID, otherCoreID;
            uint32_t ccount_شروع;
            bool مجموعه_timeout = timeout_چرخهها > پورت_MUX_NO_TIMEOUT;
            #اگر_تعریف_شده CONFIG_FREERTOS_PORTMUX_DEBUG
                إذا( !مجموعه_timeout )
                {
                    timeout_چرخهها = 10000; /* Always set a timeout in debug mode */
                    مجموعه_timeout = true;
                }
            #پایان_اگر

            إذا( مجموعه_timeout ) /* Timeout */
            {
                RSR( CCOUNT, ccount_شروع );
            }

            #اگر_تعریف_شده CONFIG_FREERTOS_PORTMUX_DEBUG
                uint32_t owner = mux->owner;

                #إذا ( ESP_IDF_نسخه < ESP_IDF_نسخه_VAL( 4, 2, 0 ) )
                    إذا( ( owner != پورت_MUX_FREE_VAL ) && ( owner != CORE_ID_PRO ) && ( owner != CORE_ID_APP ) )
                #وإلا
                    إذا( ( owner != پورت_MUX_FREE_VAL ) && ( owner != CORE_ID_REGVAL_PRO ) && ( owner != CORE_ID_REGVAL_APP ) )
                #پایان_اگر
                {
                    ets_printf( "ERROR: vPortCPUAcquireMutex: mux %p is uninitialized (0x%X)! Called from %s line %d.\n", mux, owner, fnName, سطر );
                    mux->owner = پورت_MUX_FREE_VAL;
                }
            #پایان_اگر /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

            /* Spin until we own the core */

            RSR( PRID, coreID );

            /* Note: coreID is the full 32 bit core ID (CORE_ID_PRO/CORE_ID_APP),
             * not the 0/1 value returned by xPortGetCoreID()
             */
            #إذا ( ESP_IDF_نسخه < ESP_IDF_نسخه_VAL( 4, 2, 0 ) )
                otherCoreID = CORE_ID_XOR_جابجا ^ coreID;
            #وإلا
                otherCoreID = CORE_ID_REGVAL_XOR_جابجا ^ coreID;
            #پایان_اگر

            افعل
            {
                /* mux->owner should be one of portMUX_FREE_VAL, CORE_ID_PRO,
                 * CORE_ID_APP:
                 *
                 * - If portMUX_FREE_VAL, we want to atomically set to 'coreID'.
                 * - If "our" coreID, we can drop through immediately.
                 * - If "otherCoreID", we spin here.
                 */
                res = coreID;
                PORTMUX_COMPARE_مجموعه_FN_NAME( &mux->owner, پورت_MUX_FREE_VAL, &res );

                إذا( res != otherCoreID )
                {
                    اكسر; /* mux->owner is "our" coreID */
                }

                إذا( مجموعه_timeout )
                {
                    uint32_t ccount_now;
                    RSR( CCOUNT, ccount_now );

                    إذا( ccount_now - ccount_شروع > ( بیعلامت ) timeout_چرخهها )
                    {
                        #اگر_تعریف_شده CONFIG_FREERTOS_PORTMUX_DEBUG
                            ets_printf( "Timeout on mux! last non-recursive lock %s line %d, curr %s line %d\n", mux->آخرین_Locked_Fn, mux->آخرین_Locked_سطر, fnName, سطر );
                            ets_printf( "Owner 0x%x count %d\n", mux->owner, mux->شمار );
                        #پایان_اگر
                        أرجع false;
                    }
                }
            } طالما( 1 );

            أكد( res == coreID || res == پورت_MUX_FREE_VAL );           /* any other value implies memory corruption or uninitialized mux */
            أكد( ( res == پورت_MUX_FREE_VAL ) == ( mux->شمار == 0 ) ); /* we're first to lock iff count is zero */
            أكد( mux->شمار < 0xFF );                                  /* Bad count value implies memory corruption */

            /* now we own it, we can increment the refcount */
            mux->شمار++;


            #اگر_تعریف_شده CONFIG_FREERTOS_PORTMUX_DEBUG
                إذا( res == پورت_MUX_FREE_VAL ) /*initial lock */
                {
                    mux->آخرین_Locked_Fn = fnName;
                    mux->آخرین_Locked_سطر = سطر;
                }
                وإلا
                {
                    ets_printf( "Recursive lock: count=%d last non-recursive lock %s line %d, curr %s line %d\n", mux->شمار - 1,
                                mux->آخرین_Locked_Fn, mux->آخرین_Locked_سطر, fnName, سطر );
                }
            #پایان_اگر /* CONFIG_FREERTOS_PORTMUX_DEBUG */
        #پایان_اگر /* CONFIG_FREERTOS_UNICORE */
        أرجع true;
    }

#اگر_تعریف_شده CONFIG_FREERTOS_PORTMUX_DEBUG
        ساكن مضمن فراغ PORTMUX_RELEASE_MUX_FN_NAME( پورت_MUX_TYPE * mux,
                                                        ثابت حرف * fnName,
                                                        صحيح سطر )
        {
#وإلا
        ساكن مضمن فراغ PORTMUX_RELEASE_MUX_FN_NAME( پورت_MUX_TYPE * mux )
        {
            #پایان_اگر


            #إذا !CONFIG_FREERTOS_UNICORE
                پورت_پایه_TYPE coreID;
                #اگر_تعریف_شده CONFIG_FREERTOS_PORTMUX_DEBUG
                    ثابت حرف * آخرین_Locked_Fn = mux->آخرین_Locked_Fn;
                    صحيح آخرین_Locked_سطر = mux->آخرین_Locked_سطر;
                    mux->آخرین_Locked_Fn = fnName;
                    mux->آخرین_Locked_سطر = سطر;
                    uint32_t owner = mux->owner;

                    #إذا ( ESP_IDF_نسخه < ESP_IDF_نسخه_VAL( 4, 2, 0 ) )
                        إذا( ( owner != پورت_MUX_FREE_VAL ) && ( owner != CORE_ID_PRO ) && ( owner != CORE_ID_APP ) )
                    #وإلا
                        إذا( ( owner != پورت_MUX_FREE_VAL ) && ( owner != CORE_ID_REGVAL_PRO ) && ( owner != CORE_ID_REGVAL_APP ) )
                    #پایان_اگر
                    {
                        ets_printf( "ERROR: vPortCPUReleaseMutex: mux %p is invalid (0x%x)!\n", mux, mux->owner );
                    }
                #پایان_اگر /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

                #إذا CONFIG_FREERTOS_PORTMUX_DEBUG || !defined( NDEBUG )
                    RSR( PRID, coreID );
                #پایان_اگر

                #اگر_تعریف_شده CONFIG_FREERTOS_PORTMUX_DEBUG
                    إذا( coreID != mux->owner )
                    {
                        ets_printf( "ERROR: vPortCPUReleaseMutex: mux %p was already unlocked!\n", mux );
                        ets_printf( "Last non-recursive unlock %s line %d, curr unlock %s line %d\n", آخرین_Locked_Fn, آخرین_Locked_سطر, fnName, سطر );
                    }
                #پایان_اگر

                أكد( coreID == mux->owner ); /* This is a mutex we didn't lock, or it's corrupt */

                mux->شمار--;

                إذا( mux->شمار == 0 )
                {
                    mux->owner = پورت_MUX_FREE_VAL;
                }
                وإلا
                {
                    أكد( mux->شمار < 0x100 ); /* Indicates memory corruption */
                    #اگر_تعریف_شده CONFIG_FREERTOS_PORTMUX_DEBUG_RECURSIVE
                        ets_printf( "Recursive unlock: count=%d last locked %s line %d, curr %s line %d\n", mux->شمار, آخرین_Locked_Fn, آخرین_Locked_سطر, fnName, سطر );
                    #پایان_اگر
                }
            #پایان_اگر //!CONFIG_FREERTOS_UNICORE
        }
