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
#جے_تعریف_شدہ CONFIG_FREERTOS_PORTMUX_DEBUG
    PORTMUX_AQUIRE_MUX_FN_NAME( پورٹ_MUX_TYPE * mux,
                                صحيح timeout_چکراں,
                                ثابت حرف * fnName,
                                صحيح سطر )
    {
#وإلا
    PORTMUX_AQUIRE_MUX_FN_NAME( پورٹ_MUX_TYPE * mux, صحيح timeout_چکراں )
    {
        #جے_انت


        #إذا !CONFIG_FREERTOS_UNICORE
            uint32_t res;
            پورٹ_ادھار_TYPE coreID, otherCoreID;
            uint32_t ccount_شروع;
            bool سیٹ_timeout = timeout_چکراں > پورٹ_MUX_NO_TIMEOUT;
            #جے_تعریف_شدہ CONFIG_FREERTOS_PORTMUX_DEBUG
                إذا( !سیٹ_timeout )
                {
                    timeout_چکراں = 10000; /* Always set a timeout in debug mode */
                    سیٹ_timeout = true;
                }
            #جے_انت

            إذا( سیٹ_timeout ) /* Timeout */
            {
                RSR( CCOUNT, ccount_شروع );
            }

            #جے_تعریف_شدہ CONFIG_FREERTOS_PORTMUX_DEBUG
                uint32_t owner = mux->owner;

                #إذا ( ESP_IDF_نسخہ < ESP_IDF_نسخہ_VAL( 4, 2, 0 ) )
                    إذا( ( owner != پورٹ_MUX_FREE_VAL ) && ( owner != CORE_ID_PRO ) && ( owner != CORE_ID_APP ) )
                #وإلا
                    إذا( ( owner != پورٹ_MUX_FREE_VAL ) && ( owner != CORE_ID_REGVAL_PRO ) && ( owner != CORE_ID_REGVAL_APP ) )
                #جے_انت
                {
                    ets_printf( "ERROR: vPortCPUAcquireMutex: mux %p is uninitialized (0x%X)! Called from %s line %d.\n", mux, owner, fnName, سطر );
                    mux->owner = پورٹ_MUX_FREE_VAL;
                }
            #جے_انت /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

            /* Spin until we own the core */

            RSR( PRID, coreID );

            /* Note: coreID is the full 32 bit core ID (CORE_ID_PRO/CORE_ID_APP),
             * not the 0/1 value returned by xPortGetCoreID()
             */
            #إذا ( ESP_IDF_نسخہ < ESP_IDF_نسخہ_VAL( 4, 2, 0 ) )
                otherCoreID = CORE_ID_XOR_وٹاندرا ^ coreID;
            #وإلا
                otherCoreID = CORE_ID_REGVAL_XOR_وٹاندرا ^ coreID;
            #جے_انت

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
                PORTMUX_COMPARE_سیٹ_FN_NAME( &mux->owner, پورٹ_MUX_FREE_VAL, &res );

                إذا( res != otherCoreID )
                {
                    اكسر; /* mux->owner is "our" coreID */
                }

                إذا( سیٹ_timeout )
                {
                    uint32_t ccount_now;
                    RSR( CCOUNT, ccount_now );

                    إذا( ccount_now - ccount_شروع > ( بنانشانی ) timeout_چکراں )
                    {
                        #جے_تعریف_شدہ CONFIG_FREERTOS_PORTMUX_DEBUG
                            ets_printf( "Timeout on mux! last non-recursive lock %s line %d, curr %s line %d\n", mux->آخری_Locked_Fn, mux->آخری_Locked_سطر, fnName, سطر );
                            ets_printf( "Owner 0x%x count %d\n", mux->owner, mux->گنتی );
                        #جے_انت
                        أرجع false;
                    }
                }
            } طالما( 1 );

            أكد( res == coreID || res == پورٹ_MUX_FREE_VAL );           /* any other value implies memory corruption or uninitialized mux */
            أكد( ( res == پورٹ_MUX_FREE_VAL ) == ( mux->گنتی == 0 ) ); /* we're first to lock iff count is zero */
            أكد( mux->گنتی < 0xFF );                                  /* Bad count value implies memory corruption */

            /* now we own it, we can increment the refcount */
            mux->گنتی++;


            #جے_تعریف_شدہ CONFIG_FREERTOS_PORTMUX_DEBUG
                إذا( res == پورٹ_MUX_FREE_VAL ) /*initial lock */
                {
                    mux->آخری_Locked_Fn = fnName;
                    mux->آخری_Locked_سطر = سطر;
                }
                وإلا
                {
                    ets_printf( "Recursive lock: count=%d last non-recursive lock %s line %d, curr %s line %d\n", mux->گنتی - 1,
                                mux->آخری_Locked_Fn, mux->آخری_Locked_سطر, fnName, سطر );
                }
            #جے_انت /* CONFIG_FREERTOS_PORTMUX_DEBUG */
        #جے_انت /* CONFIG_FREERTOS_UNICORE */
        أرجع true;
    }

#جے_تعریف_شدہ CONFIG_FREERTOS_PORTMUX_DEBUG
        ساكن مضمن فراغ PORTMUX_RELEASE_MUX_FN_NAME( پورٹ_MUX_TYPE * mux,
                                                        ثابت حرف * fnName,
                                                        صحيح سطر )
        {
#وإلا
        ساكن مضمن فراغ PORTMUX_RELEASE_MUX_FN_NAME( پورٹ_MUX_TYPE * mux )
        {
            #جے_انت


            #إذا !CONFIG_FREERTOS_UNICORE
                پورٹ_ادھار_TYPE coreID;
                #جے_تعریف_شدہ CONFIG_FREERTOS_PORTMUX_DEBUG
                    ثابت حرف * آخری_Locked_Fn = mux->آخری_Locked_Fn;
                    صحيح آخری_Locked_سطر = mux->آخری_Locked_سطر;
                    mux->آخری_Locked_Fn = fnName;
                    mux->آخری_Locked_سطر = سطر;
                    uint32_t owner = mux->owner;

                    #إذا ( ESP_IDF_نسخہ < ESP_IDF_نسخہ_VAL( 4, 2, 0 ) )
                        إذا( ( owner != پورٹ_MUX_FREE_VAL ) && ( owner != CORE_ID_PRO ) && ( owner != CORE_ID_APP ) )
                    #وإلا
                        إذا( ( owner != پورٹ_MUX_FREE_VAL ) && ( owner != CORE_ID_REGVAL_PRO ) && ( owner != CORE_ID_REGVAL_APP ) )
                    #جے_انت
                    {
                        ets_printf( "ERROR: vPortCPUReleaseMutex: mux %p is invalid (0x%x)!\n", mux, mux->owner );
                    }
                #جے_انت /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

                #إذا CONFIG_FREERTOS_PORTMUX_DEBUG || !defined( NDEBUG )
                    RSR( PRID, coreID );
                #جے_انت

                #جے_تعریف_شدہ CONFIG_FREERTOS_PORTMUX_DEBUG
                    إذا( coreID != mux->owner )
                    {
                        ets_printf( "ERROR: vPortCPUReleaseMutex: mux %p was already unlocked!\n", mux );
                        ets_printf( "Last non-recursive unlock %s line %d, curr unlock %s line %d\n", آخری_Locked_Fn, آخری_Locked_سطر, fnName, سطر );
                    }
                #جے_انت

                أكد( coreID == mux->owner ); /* This is a mutex we didn't lock, or it's corrupt */

                mux->گنتی--;

                إذا( mux->گنتی == 0 )
                {
                    mux->owner = پورٹ_MUX_FREE_VAL;
                }
                وإلا
                {
                    أكد( mux->گنتی < 0x100 ); /* Indicates memory corruption */
                    #جے_تعریف_شدہ CONFIG_FREERTOS_PORTMUX_DEBUG_RECURSIVE
                        ets_printf( "Recursive unlock: count=%d last locked %s line %d, curr %s line %d\n", mux->گنتی, آخری_Locked_Fn, آخری_Locked_سطر, fnName, سطر );
                    #جے_انت
                }
            #جے_انت //!CONFIG_FREERTOS_UNICORE
        }
