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



స్థిర అంతఃవరుస bool __attribute__( ( always_inline ) )
#నిర్వచితమైతే CONFIG_FREERTOS_PORTMUX_DEBUG
    PORTMUX_AQUIRE_MUX_FN_NAME( పోర్టు_MUX_TYPE * mux,
                                పూర్ణాంకం timeout_చక్రాలు,
                                స్థిరరాశి అక్షరం * fnName,
                                పూర్ణాంకం పంక్తి )
    {
#లేకపోతే
    PORTMUX_AQUIRE_MUX_FN_NAME( పోర్టు_MUX_TYPE * mux, పూర్ణాంకం timeout_చక్రాలు )
    {
        #అయితే_ముగింపు


        #ఒకవేళ !CONFIG_FREERTOS_UNICORE
            uint32_t res;
            పోర్టు_పునాది_TYPE coreID, otherCoreID;
            uint32_t ccount_ప్రారంభం;
            bool సమితి_timeout = timeout_చక్రాలు > పోర్టు_MUX_NO_TIMEOUT;
            #నిర్వచితమైతే CONFIG_FREERTOS_PORTMUX_DEBUG
                ఒకవేళ( !సమితి_timeout )
                {
                    timeout_చక్రాలు = 10000; /* Always set a timeout in debug mode */
                    సమితి_timeout = true;
                }
            #అయితే_ముగింపు

            ఒకవేళ( సమితి_timeout ) /* Timeout */
            {
                RSR( CCOUNT, ccount_ప్రారంభం );
            }

            #నిర్వచితమైతే CONFIG_FREERTOS_PORTMUX_DEBUG
                uint32_t owner = mux->owner;

                #ఒకవేళ ( ESP_IDF_సంస్కరణ < ESP_IDF_సంస్కరణ_VAL( 4, 2, 0 ) )
                    ఒకవేళ( ( owner != పోర్టు_MUX_FREE_VAL ) && ( owner != CORE_ID_PRO ) && ( owner != CORE_ID_APP ) )
                #లేకపోతే
                    ఒకవేళ( ( owner != పోర్టు_MUX_FREE_VAL ) && ( owner != CORE_ID_REGVAL_PRO ) && ( owner != CORE_ID_REGVAL_APP ) )
                #అయితే_ముగింపు
                {
                    ets_printf( "ERROR: vPortCPUAcquireMutex: mux %p is uninitialized (0x%X)! Called from %s line %d.\n", mux, owner, fnName, పంక్తి );
                    mux->owner = పోర్టు_MUX_FREE_VAL;
                }
            #అయితే_ముగింపు /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

            /* Spin until we own the core */

            RSR( PRID, coreID );

            /* Note: coreID is the full 32 bit core ID (CORE_ID_PRO/CORE_ID_APP),
             * not the 0/1 value returned by xPortGetCoreID()
             */
            #ఒకవేళ ( ESP_IDF_సంస్కరణ < ESP_IDF_సంస్కరణ_VAL( 4, 2, 0 ) )
                otherCoreID = CORE_ID_XOR_మార్పిడి ^ coreID;
            #లేకపోతే
                otherCoreID = CORE_ID_REGVAL_XOR_మార్పిడి ^ coreID;
            #అయితే_ముగింపు

            చేయి
            {
                /* mux->owner should be one of portMUX_FREE_VAL, CORE_ID_PRO,
                 * CORE_ID_APP:
                 *
                 * - If portMUX_FREE_VAL, we want to atomically set to 'coreID'.
                 * - If "our" coreID, we can drop through immediately.
                 * - If "otherCoreID", we spin here.
                 */
                res = coreID;
                PORTMUX_COMPARE_సమితి_FN_NAME( &mux->owner, పోర్టు_MUX_FREE_VAL, &res );

                ఒకవేళ( res != otherCoreID )
                {
                    ఆపు; /* mux->owner is "our" coreID */
                }

                ఒకవేళ( సమితి_timeout )
                {
                    uint32_t ccount_now;
                    RSR( CCOUNT, ccount_now );

                    ఒకవేళ( ccount_now - ccount_ప్రారంభం > ( గుర్తులేని ) timeout_చక్రాలు )
                    {
                        #నిర్వచితమైతే CONFIG_FREERTOS_PORTMUX_DEBUG
                            ets_printf( "Timeout on mux! last non-recursive lock %s line %d, curr %s line %d\n", mux->చివరి_Locked_Fn, mux->చివరి_Locked_పంక్తి, fnName, పంక్తి );
                            ets_printf( "Owner 0x%x count %d\n", mux->owner, mux->లెక్క );
                        #అయితే_ముగింపు
                        తిరిగి false;
                    }
                }
            } అయితే( 1 );

            ప్రతిజ్ఞా( res == coreID || res == పోర్టు_MUX_FREE_VAL );           /* any other value implies memory corruption or uninitialized mux */
            ప్రతిజ్ఞా( ( res == పోర్టు_MUX_FREE_VAL ) == ( mux->లెక్క == 0 ) ); /* we're first to lock iff count is zero */
            ప్రతిజ్ఞా( mux->లెక్క < 0xFF );                                  /* Bad count value implies memory corruption */

            /* now we own it, we can increment the refcount */
            mux->లెక్క++;


            #నిర్వచితమైతే CONFIG_FREERTOS_PORTMUX_DEBUG
                ఒకవేళ( res == పోర్టు_MUX_FREE_VAL ) /*initial lock */
                {
                    mux->చివరి_Locked_Fn = fnName;
                    mux->చివరి_Locked_పంక్తి = పంక్తి;
                }
                లేకపోతే
                {
                    ets_printf( "Recursive lock: count=%d last non-recursive lock %s line %d, curr %s line %d\n", mux->లెక్క - 1,
                                mux->చివరి_Locked_Fn, mux->చివరి_Locked_పంక్తి, fnName, పంక్తి );
                }
            #అయితే_ముగింపు /* CONFIG_FREERTOS_PORTMUX_DEBUG */
        #అయితే_ముగింపు /* CONFIG_FREERTOS_UNICORE */
        తిరిగి true;
    }

#నిర్వచితమైతే CONFIG_FREERTOS_PORTMUX_DEBUG
        స్థిర అంతఃవరుస శూన్య PORTMUX_RELEASE_MUX_FN_NAME( పోర్టు_MUX_TYPE * mux,
                                                        స్థిరరాశి అక్షరం * fnName,
                                                        పూర్ణాంకం పంక్తి )
        {
#లేకపోతే
        స్థిర అంతఃవరుస శూన్య PORTMUX_RELEASE_MUX_FN_NAME( పోర్టు_MUX_TYPE * mux )
        {
            #అయితే_ముగింపు


            #ఒకవేళ !CONFIG_FREERTOS_UNICORE
                పోర్టు_పునాది_TYPE coreID;
                #నిర్వచితమైతే CONFIG_FREERTOS_PORTMUX_DEBUG
                    స్థిరరాశి అక్షరం * చివరి_Locked_Fn = mux->చివరి_Locked_Fn;
                    పూర్ణాంకం చివరి_Locked_పంక్తి = mux->చివరి_Locked_పంక్తి;
                    mux->చివరి_Locked_Fn = fnName;
                    mux->చివరి_Locked_పంక్తి = పంక్తి;
                    uint32_t owner = mux->owner;

                    #ఒకవేళ ( ESP_IDF_సంస్కరణ < ESP_IDF_సంస్కరణ_VAL( 4, 2, 0 ) )
                        ఒకవేళ( ( owner != పోర్టు_MUX_FREE_VAL ) && ( owner != CORE_ID_PRO ) && ( owner != CORE_ID_APP ) )
                    #లేకపోతే
                        ఒకవేళ( ( owner != పోర్టు_MUX_FREE_VAL ) && ( owner != CORE_ID_REGVAL_PRO ) && ( owner != CORE_ID_REGVAL_APP ) )
                    #అయితే_ముగింపు
                    {
                        ets_printf( "ERROR: vPortCPUReleaseMutex: mux %p is invalid (0x%x)!\n", mux, mux->owner );
                    }
                #అయితే_ముగింపు /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

                #ఒకవేళ CONFIG_FREERTOS_PORTMUX_DEBUG || !defined( NDEBUG )
                    RSR( PRID, coreID );
                #అయితే_ముగింపు

                #నిర్వచితమైతే CONFIG_FREERTOS_PORTMUX_DEBUG
                    ఒకవేళ( coreID != mux->owner )
                    {
                        ets_printf( "ERROR: vPortCPUReleaseMutex: mux %p was already unlocked!\n", mux );
                        ets_printf( "Last non-recursive unlock %s line %d, curr unlock %s line %d\n", చివరి_Locked_Fn, చివరి_Locked_పంక్తి, fnName, పంక్తి );
                    }
                #అయితే_ముగింపు

                ప్రతిజ్ఞా( coreID == mux->owner ); /* This is a mutex we didn't lock, or it's corrupt */

                mux->లెక్క--;

                ఒకవేళ( mux->లెక్క == 0 )
                {
                    mux->owner = పోర్టు_MUX_FREE_VAL;
                }
                లేకపోతే
                {
                    ప్రతిజ్ఞా( mux->లెక్క < 0x100 ); /* Indicates memory corruption */
                    #నిర్వచితమైతే CONFIG_FREERTOS_PORTMUX_DEBUG_RECURSIVE
                        ets_printf( "Recursive unlock: count=%d last locked %s line %d, curr %s line %d\n", mux->లెక్క, చివరి_Locked_Fn, చివరి_Locked_పంక్తి, fnName, పంక్తి );
                    #అయితే_ముగింపు
                }
            #అయితే_ముగింపు //!CONFIG_FREERTOS_UNICORE
        }
