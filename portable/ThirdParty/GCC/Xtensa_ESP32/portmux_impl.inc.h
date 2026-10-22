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



स्थिर अन्तःस्थ bool __attribute__( ( always_inline ) )
#यदि_परिभाषितम् CONFIG_FREERTOS_PORTMUX_DEBUG
    PORTMUX_AQUIRE_MUX_FN_NAME( पत्तनम्_MUX_TYPE * mux,
                                पूर्णाङ्क timeout_आवृत्तयः,
                                ध्रुव वर्ण * fnName,
                                पूर्णाङ्क पङ्क्तिः )
    {
#अन्यथा
    PORTMUX_AQUIRE_MUX_FN_NAME( पत्तनम्_MUX_TYPE * mux, पूर्णाङ्क timeout_आवृत्तयः )
    {
        #यदि_अन्तः


        #यदि !CONFIG_FREERTOS_UNICORE
            uint32_t res;
            पत्तनम्_आधारः_TYPE coreID, otherCoreID;
            uint32_t ccount_start;
            bool समुच्चयः_timeout = timeout_आवृत्तयः > पत्तनम्_MUX_NO_TIMEOUT;
            #यदि_परिभाषितम् CONFIG_FREERTOS_PORTMUX_DEBUG
                यदि( !समुच्चयः_timeout )
                {
                    timeout_आवृत्तयः = 10000; /* Always set a timeout in debug mode */
                    समुच्चयः_timeout = true;
                }
            #यदि_अन्तः

            यदि( समुच्चयः_timeout ) /* Timeout */
            {
                RSR( CCOUNT, ccount_start );
            }

            #यदि_परिभाषितम् CONFIG_FREERTOS_PORTMUX_DEBUG
                uint32_t owner = mux->owner;

                #यदि ( ESP_IDF_संस्करणम् < ESP_IDF_संस्करणम्_VAL( 4, 2, 0 ) )
                    यदि( ( owner != पत्तनम्_MUX_FREE_VAL ) && ( owner != CORE_ID_PRO ) && ( owner != CORE_ID_APP ) )
                #अन्यथा
                    यदि( ( owner != पत्तनम्_MUX_FREE_VAL ) && ( owner != CORE_ID_REGVAL_PRO ) && ( owner != CORE_ID_REGVAL_APP ) )
                #यदि_अन्तः
                {
                    ets_printf( "ERROR: vPortCPUAcquireMutex: mux %p is uninitialized (0x%X)! Called from %s line %d.\n", mux, owner, fnName, पङ्क्तिः );
                    mux->owner = पत्तनम्_MUX_FREE_VAL;
                }
            #यदि_अन्तः /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

            /* Spin until we own the core */

            RSR( PRID, coreID );

            /* Note: coreID is the full 32 bit core ID (CORE_ID_PRO/CORE_ID_APP),
             * not the 0/1 value returned by xPortGetCoreID()
             */
            #यदि ( ESP_IDF_संस्करणम् < ESP_IDF_संस्करणम्_VAL( 4, 2, 0 ) )
                otherCoreID = CORE_ID_XOR_SWAP ^ coreID;
            #अन्यथा
                otherCoreID = CORE_ID_REGVAL_XOR_SWAP ^ coreID;
            #यदि_अन्तः

            कुरु
            {
                /* mux->owner should be one of portMUX_FREE_VAL, CORE_ID_PRO,
                 * CORE_ID_APP:
                 *
                 * - If portMUX_FREE_VAL, we want to atomically set to 'coreID'.
                 * - If "our" coreID, we can drop through immediately.
                 * - If "otherCoreID", we spin here.
                 */
                res = coreID;
                PORTMUX_COMPARE_समुच्चयः_FN_NAME( &mux->owner, पत्तनम्_MUX_FREE_VAL, &res );

                यदि( res != otherCoreID )
                {
                    भङ्ग; /* mux->owner is "our" coreID */
                }

                यदि( समुच्चयः_timeout )
                {
                    uint32_t ccount_now;
                    RSR( CCOUNT, ccount_now );

                    यदि( ccount_now - ccount_start > ( अचिह्नित ) timeout_आवृत्तयः )
                    {
                        #यदि_परिभाषितम् CONFIG_FREERTOS_PORTMUX_DEBUG
                            ets_printf( "Timeout on mux! last non-recursive lock %s line %d, curr %s line %d\n", mux->चरमः_Locked_Fn, mux->चरमः_Locked_पङ्क्तिः, fnName, पङ्क्तिः );
                            ets_printf( "Owner 0x%x count %d\n", mux->owner, mux->गणनम् );
                        #यदि_अन्तः
                        प्रत्यागम false;
                    }
                }
            } यावत्( 1 );

            प्रतिज्ञा( res == coreID || res == पत्तनम्_MUX_FREE_VAL );           /* any other value implies memory corruption or uninitialized mux */
            प्रतिज्ञा( ( res == पत्तनम्_MUX_FREE_VAL ) == ( mux->गणनम् == 0 ) ); /* we're first to lock iff count is zero */
            प्रतिज्ञा( mux->गणनम् < 0xFF );                                  /* Bad count value implies memory corruption */

            /* now we own it, we can increment the refcount */
            mux->गणनम्++;


            #यदि_परिभाषितम् CONFIG_FREERTOS_PORTMUX_DEBUG
                यदि( res == पत्तनम्_MUX_FREE_VAL ) /*initial lock */
                {
                    mux->चरमः_Locked_Fn = fnName;
                    mux->चरमः_Locked_पङ्क्तिः = पङ्क्तिः;
                }
                अन्यथा
                {
                    ets_printf( "Recursive lock: count=%d last non-recursive lock %s line %d, curr %s line %d\n", mux->गणनम् - 1,
                                mux->चरमः_Locked_Fn, mux->चरमः_Locked_पङ्क्तिः, fnName, पङ्क्तिः );
                }
            #यदि_अन्तः /* CONFIG_FREERTOS_PORTMUX_DEBUG */
        #यदि_अन्तः /* CONFIG_FREERTOS_UNICORE */
        प्रत्यागम true;
    }

#यदि_परिभाषितम् CONFIG_FREERTOS_PORTMUX_DEBUG
        स्थिर अन्तःस्थ शून्य PORTMUX_RELEASE_MUX_FN_NAME( पत्तनम्_MUX_TYPE * mux,
                                                        ध्रुव वर्ण * fnName,
                                                        पूर्णाङ्क पङ्क्तिः )
        {
#अन्यथा
        स्थिर अन्तःस्थ शून्य PORTMUX_RELEASE_MUX_FN_NAME( पत्तनम्_MUX_TYPE * mux )
        {
            #यदि_अन्तः


            #यदि !CONFIG_FREERTOS_UNICORE
                पत्तनम्_आधारः_TYPE coreID;
                #यदि_परिभाषितम् CONFIG_FREERTOS_PORTMUX_DEBUG
                    ध्रुव वर्ण * चरमः_Locked_Fn = mux->चरमः_Locked_Fn;
                    पूर्णाङ्क चरमः_Locked_पङ्क्तिः = mux->चरमः_Locked_पङ्क्तिः;
                    mux->चरमः_Locked_Fn = fnName;
                    mux->चरमः_Locked_पङ्क्तिः = पङ्क्तिः;
                    uint32_t owner = mux->owner;

                    #यदि ( ESP_IDF_संस्करणम् < ESP_IDF_संस्करणम्_VAL( 4, 2, 0 ) )
                        यदि( ( owner != पत्तनम्_MUX_FREE_VAL ) && ( owner != CORE_ID_PRO ) && ( owner != CORE_ID_APP ) )
                    #अन्यथा
                        यदि( ( owner != पत्तनम्_MUX_FREE_VAL ) && ( owner != CORE_ID_REGVAL_PRO ) && ( owner != CORE_ID_REGVAL_APP ) )
                    #यदि_अन्तः
                    {
                        ets_printf( "ERROR: vPortCPUReleaseMutex: mux %p is invalid (0x%x)!\n", mux, mux->owner );
                    }
                #यदि_अन्तः /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

                #यदि CONFIG_FREERTOS_PORTMUX_DEBUG || !defined( NDEBUG )
                    RSR( PRID, coreID );
                #यदि_अन्तः

                #यदि_परिभाषितम् CONFIG_FREERTOS_PORTMUX_DEBUG
                    यदि( coreID != mux->owner )
                    {
                        ets_printf( "ERROR: vPortCPUReleaseMutex: mux %p was already unlocked!\n", mux );
                        ets_printf( "Last non-recursive unlock %s line %d, curr unlock %s line %d\n", चरमः_Locked_Fn, चरमः_Locked_पङ्क्तिः, fnName, पङ्क्तिः );
                    }
                #यदि_अन्तः

                प्रतिज्ञा( coreID == mux->owner ); /* This is a mutex we didn't lock, or it's corrupt */

                mux->गणनम्--;

                यदि( mux->गणनम् == 0 )
                {
                    mux->owner = पत्तनम्_MUX_FREE_VAL;
                }
                अन्यथा
                {
                    प्रतिज्ञा( mux->गणनम् < 0x100 ); /* Indicates memory corruption */
                    #यदि_परिभाषितम् CONFIG_FREERTOS_PORTMUX_DEBUG_RECURSIVE
                        ets_printf( "Recursive unlock: count=%d last locked %s line %d, curr %s line %d\n", mux->गणनम्, चरमः_Locked_Fn, चरमः_Locked_पङ्क्तिः, fnName, पङ्क्तिः );
                    #यदि_अन्तः
                }
            #यदि_अन्तः //!CONFIG_FREERTOS_UNICORE
        }
