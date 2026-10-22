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



ಸ್ಥಿರ ಸಾಲೊಳಗೆ bool __attribute__( ( always_inline ) )
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_PORTMUX_DEBUG
    PORTMUX_AQUIRE_MUX_FN_NAME( ಪೋರ್ಟ್_MUX_TYPE * mux,
                                ಪೂರ್ಣಾಂಕ timeout_ಚಕ್ರಗಳು,
                                ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * fnName,
                                ಪೂರ್ಣಾಂಕ ಸಾಲು )
    {
#ಇಲ್ಲದಿದ್ದರೆ
    PORTMUX_AQUIRE_MUX_FN_NAME( ಪೋರ್ಟ್_MUX_TYPE * mux, ಪೂರ್ಣಾಂಕ timeout_ಚಕ್ರಗಳು )
    {
        #ಆದರೆ_ಅಂತ್ಯ


        #ಆದರೆ !CONFIG_FREERTOS_UNICORE
            uint32_t res;
            ಪೋರ್ಟ್_ತಳ_TYPE coreID, otherCoreID;
            uint32_t ccount_ಆರಂಭ;
            bool ಗಣ_timeout = timeout_ಚಕ್ರಗಳು > ಪೋರ್ಟ್_MUX_NO_TIMEOUT;
            #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_PORTMUX_DEBUG
                ಆದರೆ( !ಗಣ_timeout )
                {
                    timeout_ಚಕ್ರಗಳು = 10000; /* Always set a timeout in debug mode */
                    ಗಣ_timeout = true;
                }
            #ಆದರೆ_ಅಂತ್ಯ

            ಆದರೆ( ಗಣ_timeout ) /* Timeout */
            {
                RSR( CCOUNT, ccount_ಆರಂಭ );
            }

            #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_PORTMUX_DEBUG
                uint32_t owner = mux->owner;

                #ಆದರೆ ( ESP_IDF_ಆವೃತ್ತಿ < ESP_IDF_ಆವೃತ್ತಿ_VAL( 4, 2, 0 ) )
                    ಆದರೆ( ( owner != ಪೋರ್ಟ್_MUX_FREE_VAL ) && ( owner != CORE_ID_PRO ) && ( owner != CORE_ID_APP ) )
                #ಇಲ್ಲದಿದ್ದರೆ
                    ಆದರೆ( ( owner != ಪೋರ್ಟ್_MUX_FREE_VAL ) && ( owner != CORE_ID_REGVAL_PRO ) && ( owner != CORE_ID_REGVAL_APP ) )
                #ಆದರೆ_ಅಂತ್ಯ
                {
                    ets_printf( "ERROR: vPortCPUAcquireMutex: mux %p is uninitialized (0x%X)! Called from %s line %d.\n", mux, owner, fnName, ಸಾಲು );
                    mux->owner = ಪೋರ್ಟ್_MUX_FREE_VAL;
                }
            #ಆದರೆ_ಅಂತ್ಯ /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

            /* Spin until we own the core */

            RSR( PRID, coreID );

            /* Note: coreID is the full 32 bit core ID (CORE_ID_PRO/CORE_ID_APP),
             * not the 0/1 value returned by xPortGetCoreID()
             */
            #ಆದರೆ ( ESP_IDF_ಆವೃತ್ತಿ < ESP_IDF_ಆವೃತ್ತಿ_VAL( 4, 2, 0 ) )
                otherCoreID = CORE_ID_XOR_ಅದಲುಬದಲು ^ coreID;
            #ಇಲ್ಲದಿದ್ದರೆ
                otherCoreID = CORE_ID_REGVAL_XOR_ಅದಲುಬದಲು ^ coreID;
            #ಆದರೆ_ಅಂತ್ಯ

            ಮಾಡು
            {
                /* mux->owner should be one of portMUX_FREE_VAL, CORE_ID_PRO,
                 * CORE_ID_APP:
                 *
                 * - If portMUX_FREE_VAL, we want to atomically set to 'coreID'.
                 * - If "our" coreID, we can drop through immediately.
                 * - If "otherCoreID", we spin here.
                 */
                res = coreID;
                PORTMUX_COMPARE_ಗಣ_FN_NAME( &mux->owner, ಪೋರ್ಟ್_MUX_FREE_VAL, &res );

                ಆದರೆ( res != otherCoreID )
                {
                    ನಿಲ್ಲಿಸು; /* mux->owner is "our" coreID */
                }

                ಆದರೆ( ಗಣ_timeout )
                {
                    uint32_t ccount_now;
                    RSR( CCOUNT, ccount_now );

                    ಆದರೆ( ccount_now - ccount_ಆರಂಭ > ( ಚಿಹ್ನೆರಹಿತ ) timeout_ಚಕ್ರಗಳು )
                    {
                        #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_PORTMUX_DEBUG
                            ets_printf( "Timeout on mux! last non-recursive lock %s line %d, curr %s line %d\n", mux->ಕೊನೆಯ_Locked_Fn, mux->ಕೊನೆಯ_Locked_ಸಾಲು, fnName, ಸಾಲು );
                            ets_printf( "Owner 0x%x count %d\n", mux->owner, mux->ಎಣಿಕೆ_2 );
                        #ಆದರೆ_ಅಂತ್ಯ
                        ಹಿಂತಿರುಗಿ false;
                    }
                }
            } ಆಗ( 1 );

            ಪ್ರತಿಜ್ಞಾ( res == coreID || res == ಪೋರ್ಟ್_MUX_FREE_VAL );           /* any other value implies memory corruption or uninitialized mux */
            ಪ್ರತಿಜ್ಞಾ( ( res == ಪೋರ್ಟ್_MUX_FREE_VAL ) == ( mux->ಎಣಿಕೆ_2 == 0 ) ); /* we're first to lock iff count is zero */
            ಪ್ರತಿಜ್ಞಾ( mux->ಎಣಿಕೆ_2 < 0xFF );                                  /* Bad count value implies memory corruption */

            /* now we own it, we can increment the refcount */
            mux->ಎಣಿಕೆ_2++;


            #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_PORTMUX_DEBUG
                ಆದರೆ( res == ಪೋರ್ಟ್_MUX_FREE_VAL ) /*initial lock */
                {
                    mux->ಕೊನೆಯ_Locked_Fn = fnName;
                    mux->ಕೊನೆಯ_Locked_ಸಾಲು = ಸಾಲು;
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    ets_printf( "Recursive lock: count=%d last non-recursive lock %s line %d, curr %s line %d\n", mux->ಎಣಿಕೆ_2 - 1,
                                mux->ಕೊನೆಯ_Locked_Fn, mux->ಕೊನೆಯ_Locked_ಸಾಲು, fnName, ಸಾಲು );
                }
            #ಆದರೆ_ಅಂತ್ಯ /* CONFIG_FREERTOS_PORTMUX_DEBUG */
        #ಆದರೆ_ಅಂತ್ಯ /* CONFIG_FREERTOS_UNICORE */
        ಹಿಂತಿರುಗಿ true;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_PORTMUX_DEBUG
        ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ PORTMUX_RELEASE_MUX_FN_NAME( ಪೋರ್ಟ್_MUX_TYPE * mux,
                                                        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * fnName,
                                                        ಪೂರ್ಣಾಂಕ ಸಾಲು )
        {
#ಇಲ್ಲದಿದ್ದರೆ
        ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ PORTMUX_RELEASE_MUX_FN_NAME( ಪೋರ್ಟ್_MUX_TYPE * mux )
        {
            #ಆದರೆ_ಅಂತ್ಯ


            #ಆದರೆ !CONFIG_FREERTOS_UNICORE
                ಪೋರ್ಟ್_ತಳ_TYPE coreID;
                #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_PORTMUX_DEBUG
                    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಕೊನೆಯ_Locked_Fn = mux->ಕೊನೆಯ_Locked_Fn;
                    ಪೂರ್ಣಾಂಕ ಕೊನೆಯ_Locked_ಸಾಲು = mux->ಕೊನೆಯ_Locked_ಸಾಲು;
                    mux->ಕೊನೆಯ_Locked_Fn = fnName;
                    mux->ಕೊನೆಯ_Locked_ಸಾಲು = ಸಾಲು;
                    uint32_t owner = mux->owner;

                    #ಆದರೆ ( ESP_IDF_ಆವೃತ್ತಿ < ESP_IDF_ಆವೃತ್ತಿ_VAL( 4, 2, 0 ) )
                        ಆದರೆ( ( owner != ಪೋರ್ಟ್_MUX_FREE_VAL ) && ( owner != CORE_ID_PRO ) && ( owner != CORE_ID_APP ) )
                    #ಇಲ್ಲದಿದ್ದರೆ
                        ಆದರೆ( ( owner != ಪೋರ್ಟ್_MUX_FREE_VAL ) && ( owner != CORE_ID_REGVAL_PRO ) && ( owner != CORE_ID_REGVAL_APP ) )
                    #ಆದರೆ_ಅಂತ್ಯ
                    {
                        ets_printf( "ERROR: vPortCPUReleaseMutex: mux %p is invalid (0x%x)!\n", mux, mux->owner );
                    }
                #ಆದರೆ_ಅಂತ್ಯ /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

                #ಆದರೆ CONFIG_FREERTOS_PORTMUX_DEBUG || !defined( NDEBUG )
                    RSR( PRID, coreID );
                #ಆದರೆ_ಅಂತ್ಯ

                #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_PORTMUX_DEBUG
                    ಆದರೆ( coreID != mux->owner )
                    {
                        ets_printf( "ERROR: vPortCPUReleaseMutex: mux %p was already unlocked!\n", mux );
                        ets_printf( "Last non-recursive unlock %s line %d, curr unlock %s line %d\n", ಕೊನೆಯ_Locked_Fn, ಕೊನೆಯ_Locked_ಸಾಲು, fnName, ಸಾಲು );
                    }
                #ಆದರೆ_ಅಂತ್ಯ

                ಪ್ರತಿಜ್ಞಾ( coreID == mux->owner ); /* This is a mutex we didn't lock, or it's corrupt */

                mux->ಎಣಿಕೆ_2--;

                ಆದರೆ( mux->ಎಣಿಕೆ_2 == 0 )
                {
                    mux->owner = ಪೋರ್ಟ್_MUX_FREE_VAL;
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    ಪ್ರತಿಜ್ಞಾ( mux->ಎಣಿಕೆ_2 < 0x100 ); /* Indicates memory corruption */
                    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_PORTMUX_DEBUG_RECURSIVE
                        ets_printf( "Recursive unlock: count=%d last locked %s line %d, curr %s line %d\n", mux->ಎಣಿಕೆ_2, ಕೊನೆಯ_Locked_Fn, ಕೊನೆಯ_Locked_ಸಾಲು, fnName, ಸಾಲು );
                    #ಆದರೆ_ಅಂತ್ಯ
                }
            #ಆದರೆ_ಅಂತ್ಯ //!CONFIG_FREERTOS_UNICORE
        }
