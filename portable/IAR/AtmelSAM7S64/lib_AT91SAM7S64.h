/**---------------------------------------------------------------------------- */
/**         ATMEL Microcontroller Software Support  -  ROUSSET  - */
/**---------------------------------------------------------------------------- */
/** The software is delivered "AS IS" without warranty or condition of any */
/** kind, either express, implied or statutory. This includes without */
/** limitation any warranty or condition with respect to merchantability or */
/** fitness for any particular purpose, or against the infringements of */
/** intellectual property rights of others. */
/**---------------------------------------------------------------------------- */
/** File Name           : lib_AT91SAM7S64.h */
/** Object              : AT91SAM7S64 inlined functions */
/** Generated           : AT91 SW Application Group  07/16/2004 (07:43:09) */
/** */
/** CVS Reference       : /lib_MC_SAM.h/1.3/Thu Mar 25 15:19:14 2004// */
/** CVS Reference       : /lib_pdc_1363d.h/1.2/Wed Feb 19 09:25:22 2003// */
/** CVS Reference       : /lib_dbgu.h/1.1/Fri Jan 31 12:18:40 2003// */
/** CVS Reference       : /lib_ssc.h/1.4/Fri Jan 31 12:19:20 2003// */
/** CVS Reference       : /lib_spi2.h/1.1/Mon Aug 25 13:23:52 2003// */
/** CVS Reference       : /lib_PWM_SAM.h/1.3/Thu Jan 22 10:10:50 2004// */
/** CVS Reference       : /lib_tc_1753b.h/1.1/Fri Jan 31 12:20:02 2003// */
/** CVS Reference       : /lib_pmc_SAM.h/1.6/Tue Apr 27 13:53:52 2004// */
/** CVS Reference       : /lib_adc.h/1.6/Fri Oct 17 08:12:38 2003// */
/** CVS Reference       : /lib_pio.h/1.3/Fri Jan 31 12:18:56 2003// */
/** CVS Reference       : /lib_twi.h/1.2/Fri Jan 31 12:19:38 2003// */
/** CVS Reference       : /lib_usart.h/1.5/Thu Nov 21 16:01:54 2002// */
/** CVS Reference       : /lib_udp.h/1.3/Fri Jan 31 12:19:48 2003// */
/** CVS Reference       : /lib_aic.h/1.3/Fri Jul 12 07:46:12 2002// */
/**---------------------------------------------------------------------------- */

#यदि_अपरिभाषितम् lib_AT91SAM7S64_H
#परिभाषय lib_AT91SAM7S64_H

/* *****************************************************************************
*               SOFTWARE API FOR MC
***************************************************************************** */

#परिभाषय AT91_C_MC_CORRECT_कुञ्चिका    ( ( अचिह्नित पूर्णाङ्क ) 0x5A << 24 ) /* (MC) Correct Protect Key */

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_MC_Remap */
/** \brief Make Remap */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_MC_Remap( शून्य ) /* */
{
    AT91PS_MC pMC = ( AT91PS_MC ) AT91_C_आधारः_MC;

    pMC->MC_RCR = AT91C_MC_RCB;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_MC_EFC_CfgModeReg */
/** \brief Configure the EFC Mode Register of the MC controller */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_MC_EFC_Cfg_बहुलकम्_Reg( AT91PS_MC pMC,      /* pointer to a MC controller */
                                       अचिह्नित पूर्णाङ्क बहुलकम्_2 ) /* mode register */
{
    /* Write to the FMR register */
    pMC->MC_FMR = बहुलकम्_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_MC_EFC_GetModeReg */
/** \brief Return MC EFC Mode Register */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_MC_EFC_Get_बहुलकम्_Reg( AT91PS_MC pMC ) /* pointer to a MC controller */
{
    प्रत्यागम pMC->MC_FMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_MC_EFC_ComputeFMCN */
/** \brief Return MC EFC Mode Register */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_MC_EFC_ComputeFMCN( पूर्णाङ्क master_clock ) /* master clock in Hz */
{
    प्रत्यागम( master_clock / 1000000 + 2 );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_MC_EFC_PerformCmd */
/** \brief Perform EFC Command */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_MC_EFC_PerformCmd( AT91PS_MC pMC, /* pointer to a MC controller */
                                       अचिह्नित पूर्णाङ्क transfer_cmd )
{
    pMC->MC_FCR = transfer_cmd;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_MC_EFC_GetStatus */
/** \brief Return MC EFC Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_MC_EFC_Get_स्थितिः( AT91PS_MC pMC ) /* pointer to a MC controller */
{
    प्रत्यागम pMC->MC_FSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_MC_EFC_IsInterruptMasked */
/** \brief Test if EFC MC Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_MC_EFC_Is_व्यवधानम्_Masked( AT91PS_MC pMC,      /* \arg  pointer to a MC controller */
                                                      अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_MC_EFC_Get_बहुलकम्_Reg( pMC ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_MC_EFC_IsInterruptSet */
/** \brief Test if EFC MC Interrupt is Set */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_MC_EFC_Is_व्यवधानम्_समुच्चयः( AT91PS_MC pMC,      /* \arg  pointer to a MC controller */
                                                   अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_MC_EFC_Get_स्थितिः( pMC ) & flag );
}

/* *****************************************************************************
*               SOFTWARE API FOR PDC
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_SetNextRx */
/** \brief Set the next receive transfer descriptor */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_PDC_समुच्चयः_अग्र_Rx( AT91PS_PDC pPDC,     /* \arg pointer to a PDC controller */
                                   वर्ण * स्थानाङ्कः_2,      /* \arg address to the next block to be received */
                                   अचिह्नित पूर्णाङ्क अष्टकानि_2 ) /* \arg number of bytes to be received */
{
    pPDC->PDC_RNPR = ( अचिह्नित पूर्णाङ्क ) स्थानाङ्कः_2;
    pPDC->PDC_RNCR = अष्टकानि_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_SetNextTx */
/** \brief Set the next transmit transfer descriptor */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_PDC_समुच्चयः_अग्र_Tx( AT91PS_PDC pPDC,     /* \arg pointer to a PDC controller */
                                   वर्ण * स्थानाङ्कः_2,      /* \arg address to the next block to be transmitted */
                                   अचिह्नित पूर्णाङ्क अष्टकानि_2 ) /* \arg number of bytes to be transmitted */
{
    pPDC->PDC_TNPR = ( अचिह्नित पूर्णाङ्क ) स्थानाङ्कः_2;
    pPDC->PDC_TNCR = अष्टकानि_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_SetRx */
/** \brief Set the receive transfer descriptor */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_PDC_समुच्चयः_Rx( AT91PS_PDC pPDC,     /* \arg pointer to a PDC controller */
                               वर्ण * स्थानाङ्कः_2,      /* \arg address to the next block to be received */
                               अचिह्नित पूर्णाङ्क अष्टकानि_2 ) /* \arg number of bytes to be received */
{
    pPDC->PDC_RPR = ( अचिह्नित पूर्णाङ्क ) स्थानाङ्कः_2;
    pPDC->PDC_RCR = अष्टकानि_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_SetTx */
/** \brief Set the transmit transfer descriptor */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_PDC_समुच्चयः_Tx( AT91PS_PDC pPDC,     /* \arg pointer to a PDC controller */
                               वर्ण * स्थानाङ्कः_2,      /* \arg address to the next block to be transmitted */
                               अचिह्नित पूर्णाङ्क अष्टकानि_2 ) /* \arg number of bytes to be transmitted */
{
    pPDC->PDC_TPR = ( अचिह्नित पूर्णाङ्क ) स्थानाङ्कः_2;
    pPDC->PDC_TCR = अष्टकानि_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_EnableTx */
/** \brief Enable transmit */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PDC_EnableTx( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
{
    pPDC->PDC_PTCR = AT91C_PDC_TXTEN;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_EnableRx */
/** \brief Enable receive */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PDC_EnableRx( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
{
    pPDC->PDC_PTCR = AT91C_PDC_RXTEN;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_DisableTx */
/** \brief Disable transmit */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PDC_DisableTx( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
{
    pPDC->PDC_PTCR = AT91C_PDC_TXTDIS;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_DisableRx */
/** \brief Disable receive */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PDC_DisableRx( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
{
    pPDC->PDC_PTCR = AT91C_PDC_RXTDIS;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_IsTxEmpty */
/** \brief Test if the current transfer descriptor has been sent */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91_F_PDC_Is_Tx_रिक्तानि( /* \return return 1 if transfer is complete */
    AT91PS_PDC pPDC )             /* \arg pointer to a PDC controller */
{
    प्रत्यागम !( pPDC->PDC_TCR );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_IsNextTxEmpty */
/** \brief Test if the next transfer descriptor has been moved to the current td */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91_F_PDC_Is_अग्र_Tx_रिक्तानि( /* \return return 1 if transfer is complete */
    AT91PS_PDC pPDC )                 /* \arg pointer to a PDC controller */
{
    प्रत्यागम !( pPDC->PDC_TNCR );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_IsRxEmpty */
/** \brief Test if the current transfer descriptor has been filled */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91_F_PDC_Is_Rx_रिक्तानि( /* \return return 1 if transfer is complete */
    AT91PS_PDC pPDC )             /* \arg pointer to a PDC controller */
{
    प्रत्यागम !( pPDC->PDC_RCR );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_IsNextRxEmpty */
/** \brief Test if the next transfer descriptor has been moved to the current td */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91_F_PDC_Is_अग्र_Rx_रिक्तानि( /* \return return 1 if transfer is complete */
    AT91PS_PDC pPDC )                 /* \arg pointer to a PDC controller */
{
    प्रत्यागम !( pPDC->PDC_RNCR );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_Open */
/** \brief Open PDC: disable TX and RX reset transfer descriptors, re-enable RX and TX */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PDC_Open( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
{
    /** Disable the RX and TX PDC transfer requests */
    AT91F_PDC_DisableRx( pPDC );
    AT91F_PDC_DisableTx( pPDC );

    /** Reset all Counter register Next buffer first */
    AT91_F_PDC_समुच्चयः_अग्र_Tx( pPDC, ( वर्ण * ) 0, 0 );
    AT91_F_PDC_समुच्चयः_अग्र_Rx( pPDC, ( वर्ण * ) 0, 0 );
    AT91_F_PDC_समुच्चयः_Tx( pPDC, ( वर्ण * ) 0, 0 );
    AT91_F_PDC_समुच्चयः_Rx( pPDC, ( वर्ण * ) 0, 0 );

    /** Enable the RX and TX PDC transfer requests */
    AT91F_PDC_EnableRx( pPDC );
    AT91F_PDC_EnableTx( pPDC );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_Close */
/** \brief Close PDC: disable TX and RX reset transfer descriptors */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PDC_Close( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
{
    /** Disable the RX and TX PDC transfer requests */
    AT91F_PDC_DisableRx( pPDC );
    AT91F_PDC_DisableTx( pPDC );

    /** Reset all Counter register Next buffer first */
    AT91_F_PDC_समुच्चयः_अग्र_Tx( pPDC, ( वर्ण * ) 0, 0 );
    AT91_F_PDC_समुच्चयः_अग्र_Rx( pPDC, ( वर्ण * ) 0, 0 );
    AT91_F_PDC_समुच्चयः_Tx( pPDC, ( वर्ण * ) 0, 0 );
    AT91_F_PDC_समुच्चयः_Rx( pPDC, ( वर्ण * ) 0, 0 );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_SendFrame */
/** \brief Close PDC: disable TX and RX reset transfer descriptors */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_PDC_SendFrame( AT91PS_PDC pPDC,
                                           वर्ण * p_बफर,
                                           अचिह्नित पूर्णाङ्क sz_बफर,
                                           वर्ण * p_अग्र_बफर,
                                           अचिह्नित पूर्णाङ्क sz_अग्र_बफर )
{
    यदि( AT91_F_PDC_Is_Tx_रिक्तानि( pPDC ) )
    {
        /** Buffer and next buffer can be initialized */
        AT91_F_PDC_समुच्चयः_Tx( pPDC, p_बफर, sz_बफर );
        AT91_F_PDC_समुच्चयः_अग्र_Tx( pPDC, p_अग्र_बफर, sz_अग्र_बफर );
        प्रत्यागम 2;
    }
    अन्यथा यदि( AT91_F_PDC_Is_अग्र_Tx_रिक्तानि( pPDC ) )
    {
        /** Only one buffer can be initialized */
        AT91_F_PDC_समुच्चयः_अग्र_Tx( pPDC, p_बफर, sz_बफर );
        प्रत्यागम 1;
    }
    अन्यथा
    {
        /** All buffer are in use... */
        प्रत्यागम 0;
    }
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_ReceiveFrame */
/** \brief Close PDC: disable TX and RX reset transfer descriptors */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_PDC_ReceiveFrame( AT91PS_PDC pPDC,
                                              वर्ण * p_बफर,
                                              अचिह्नित पूर्णाङ्क sz_बफर,
                                              वर्ण * p_अग्र_बफर,
                                              अचिह्नित पूर्णाङ्क sz_अग्र_बफर )
{
    यदि( AT91_F_PDC_Is_Rx_रिक्तानि( pPDC ) )
    {
        /** Buffer and next buffer can be initialized */
        AT91_F_PDC_समुच्चयः_Rx( pPDC, p_बफर, sz_बफर );
        AT91_F_PDC_समुच्चयः_अग्र_Rx( pPDC, p_अग्र_बफर, sz_अग्र_बफर );
        प्रत्यागम 2;
    }
    अन्यथा यदि( AT91_F_PDC_Is_अग्र_Rx_रिक्तानि( pPDC ) )
    {
        /** Only one buffer can be initialized */
        AT91_F_PDC_समुच्चयः_अग्र_Rx( pPDC, p_बफर, sz_बफर );
        प्रत्यागम 1;
    }
    अन्यथा
    {
        /** All buffer are in use... */
        प्रत्यागम 0;
    }
}

/* *****************************************************************************
*               SOFTWARE API FOR DBGU
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_DBGU_InterruptEnable */
/** \brief Enable DBGU Interrupt */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_DBGU_व्यवधानम्_Enable( AT91PS_DBGU pDbgu,  /* \arg  pointer to a DBGU controller */
                                          अचिह्नित पूर्णाङ्क flag ) /* \arg  dbgu interrupt to be enabled */
{
    pDbgu->DBGU_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_DBGU_InterruptDisable */
/** \brief Disable DBGU Interrupt */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_DBGU_व्यवधानम्_Disable( AT91PS_DBGU pDbgu,  /* \arg  pointer to a DBGU controller */
                                           अचिह्नित पूर्णाङ्क flag ) /* \arg  dbgu interrupt to be disabled */
{
    pDbgu->DBGU_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_DBGU_GetInterruptMaskStatus */
/** \brief Return DBGU Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_DBGU_Get_व्यवधानम्_आवरणम्_स्थितिः( /* \return DBGU Interrupt Mask Status */
    AT91PS_DBGU pDbgu )                                  /* \arg  pointer to a DBGU controller */
{
    प्रत्यागम pDbgu->DBGU_IMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_DBGU_IsInterruptMasked */
/** \brief Test if DBGU Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91_F_DBGU_Is_व्यवधानम्_Masked( AT91PS_DBGU pDbgu,  /* \arg  pointer to a DBGU controller */
                                           अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_DBGU_Get_व्यवधानम्_आवरणम्_स्थितिः( pDbgu ) & flag );
}

/* *****************************************************************************
*               SOFTWARE API FOR SSC
***************************************************************************** */
/** Define the standard I2S mode configuration */

/** Configuration to set in the SSC Transmit Clock Mode Register */
/** Parameters :  nb_bit_by_slot : 8, 16 or 32 bits */
/**               nb_slot_by_frame : number of channels */
#परिभाषय AT91C_I2S_ASY_MASTER_TX_SETTING( nb_bit_by_slot, nb_slot_by_frame ) \
    ( +                                                                     \
      AT91C_SSC_CKS_DIV +                                                   \
      AT91C_SSC_CKO_CONTINUOUS +                                            \
      AT91C_SSC_CKG_NONE +                                                  \
      AT91C_SSC_START_FALL_RF +                                             \
      AT91C_SSC_STTOUT +                                                    \
      ( ( 1 << 16 ) & AT91C_SSC_STTDLY ) +                                  \
      ( ( ( ( nb_bit_by_slot * nb_slot_by_frame ) / 2 ) - 1 ) << 24 ) )


/** Configuration to set in the SSC Transmit Frame Mode Register */
/** Parameters : nb_bit_by_slot : 8, 16 or 32 bits */
/**              nb_slot_by_frame : number of channels */
#परिभाषय AT91C_I2S_ASY_TX_FRAME_SETTING( nb_bit_by_slot, nb_slot_by_frame ) \
    ( +                                                                    \
      ( nb_bit_by_slot - 1 ) +                                             \
      AT91C_SSC_MSBF +                                                     \
      ( ( ( nb_slot_by_frame - 1 ) << 8 ) & AT91C_SSC_DATNB ) +            \
      ( ( ( nb_bit_by_slot - 1 ) << 16 ) & AT91C_SSC_FSLEN ) +             \
      AT91C_SSC_FSOS_NEGATIVE )


/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_SetBaudrate */
/** \brief Set the baudrate according to the CPU clock */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_SSC_समुच्चयः_Baudrate( AT91PS_SSC pSSC,        /* \arg pointer to a SSC controller */
                                     अचिह्नित पूर्णाङ्क mainClock, /* \arg peripheral clock */
                                     अचिह्नित पूर्णाङ्क जवः_2 )    /* \arg SSC baudrate */
{
    अचिह्नित पूर्णाङ्क baud_मानम्;

    /** Define the baud rate divisor register */
    यदि( जवः_2 == 0 )
    {
        baud_मानम् = 0;
    }
    अन्यथा
    {
        baud_मानम् = ( अचिह्नित पूर्णाङ्क ) ( mainClock * 10 ) / ( 2 * जवः_2 );

        यदि( ( baud_मानम् % 10 ) >= 5 )
        {
            baud_मानम् = ( baud_मानम् / 10 ) + 1;
        }
        अन्यथा
        {
            baud_मानम् /= 10;
        }
    }

    pSSC->SSC_CMR = baud_मानम्;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_Configure */
/** \brief Configure SSC */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_SSC_Configure( AT91PS_SSC pSSC,         /* \arg pointer to a SSC controller */
                                   अचिह्नित पूर्णाङ्क syst_clock, /* \arg System Clock Frequency */
                                   अचिह्नित पूर्णाङ्क baud_दरः,  /* \arg Expected Baud Rate Frequency */
                                   अचिह्नित पूर्णाङ्क clock_rx,   /* \arg Receiver Clock Parameters */
                                   अचिह्नित पूर्णाङ्क बहुलकम्_rx,    /* \arg mode Register to be programmed */
                                   अचिह्नित पूर्णाङ्क clock_tx,   /* \arg Transmitter Clock Parameters */
                                   अचिह्नित पूर्णाङ्क बहुलकम्_tx )   /* \arg mode Register to be programmed */
{
    /** Disable interrupts */
    pSSC->SSC_IDR = ( अचिह्नित पूर्णाङ्क ) -1;

    /** Reset receiver and transmitter */
    pSSC->SSC_CR = AT91C_SSC_SWRST | AT91C_SSC_RXDIS | AT91C_SSC_TXDIS;

    /** Define the Clock Mode Register */
    AT91_F_SSC_समुच्चयः_Baudrate( pSSC, syst_clock, baud_दरः );

    /** Write the Receive Clock Mode Register */
    pSSC->SSC_RCMR = clock_rx;

    /** Write the Transmit Clock Mode Register */
    pSSC->SSC_TCMR = clock_tx;

    /** Write the Receive Frame Mode Register */
    pSSC->SSC_RFMR = बहुलकम्_rx;

    /** Write the Transmit Frame Mode Register */
    pSSC->SSC_TFMR = बहुलकम्_tx;

    /** Clear Transmit and Receive Counters */
    AT91F_PDC_Open( ( AT91PS_PDC ) &( pSSC->SSC_RPR ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_EnableRx */
/** \brief Enable receiving data */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_SSC_EnableRx( AT91PS_SSC pSSC ) /* \arg pointer to a SSC controller */
{
    /** Enable receiver */
    pSSC->SSC_CR = AT91C_SSC_RXEN;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_DisableRx */
/** \brief Disable receiving data */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_SSC_DisableRx( AT91PS_SSC pSSC ) /* \arg pointer to a SSC controller */
{
    /** Disable receiver */
    pSSC->SSC_CR = AT91C_SSC_RXDIS;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_EnableTx */
/** \brief Enable sending data */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_SSC_EnableTx( AT91PS_SSC pSSC ) /* \arg pointer to a SSC controller */
{
    /** Enable  transmitter */
    pSSC->SSC_CR = AT91C_SSC_TXEN;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_DisableTx */
/** \brief Disable sending data */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_SSC_DisableTx( AT91PS_SSC pSSC ) /* \arg pointer to a SSC controller */
{
    /** Disable  transmitter */
    pSSC->SSC_CR = AT91C_SSC_TXDIS;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_EnableIt */
/** \brief Enable SSC IT */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_SSC_EnableIt( AT91PS_SSC pSSC,    /* \arg pointer to a SSC controller */
                                  अचिह्नित पूर्णाङ्क flag ) /* \arg IT to be enabled */
{
    /** Write to the IER register */
    pSSC->SSC_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_DisableIt */
/** \brief Disable SSC IT */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_SSC_DisableIt( AT91PS_SSC pSSC,    /* \arg pointer to a SSC controller */
                                   अचिह्नित पूर्णाङ्क flag ) /* \arg IT to be disabled */
{
    /** Write to the IDR register */
    pSSC->SSC_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_ReceiveFrame */
/** \brief Return 2 if PDC has been initialized with Buffer and Next Buffer, 1 if PDC has been initialized with Next Buffer, 0 if PDC is busy */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_SSC_ReceiveFrame( AT91PS_SSC pSSC,
                                              वर्ण * p_बफर,
                                              अचिह्नित पूर्णाङ्क sz_बफर,
                                              वर्ण * p_अग्र_बफर,
                                              अचिह्नित पूर्णाङ्क sz_अग्र_बफर )
{
    प्रत्यागम AT91F_PDC_ReceiveFrame(
        ( AT91PS_PDC ) &( pSSC->SSC_RPR ),
        p_बफर,
        sz_बफर,
        p_अग्र_बफर,
        sz_अग्र_बफर );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_SendFrame */
/** \brief Return 2 if PDC has been initialized with Buffer and Next Buffer, 1 if PDC has been initialized with Next Buffer, 0 if PDC is busy */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_SSC_SendFrame( AT91PS_SSC pSSC,
                                           वर्ण * p_बफर,
                                           अचिह्नित पूर्णाङ्क sz_बफर,
                                           वर्ण * p_अग्र_बफर,
                                           अचिह्नित पूर्णाङ्क sz_अग्र_बफर )
{
    प्रत्यागम AT91F_PDC_SendFrame(
        ( AT91PS_PDC ) &( pSSC->SSC_RPR ),
        p_बफर,
        sz_बफर,
        p_अग्र_बफर,
        sz_अग्र_बफर );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_GetInterruptMaskStatus */
/** \brief Return SSC Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_SSC_Get_व्यवधानम्_आवरणम्_स्थितिः( /* \return SSC Interrupt Mask Status */
    AT91PS_SSC pSsc )                                   /* \arg  pointer to a SSC controller */
{
    प्रत्यागम pSsc->SSC_IMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_IsInterruptMasked */
/** \brief Test if SSC Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91_F_SSC_Is_व्यवधानम्_Masked( AT91PS_SSC pSsc,    /* \arg  pointer to a SSC controller */
                                          अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_SSC_Get_व्यवधानम्_आवरणम्_स्थितिः( pSsc ) & flag );
}

/* *****************************************************************************
*               SOFTWARE API FOR SPI
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_Open */
/** \brief Open a SPI Port */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_SPI_Open( ध्रुव अचिह्नित पूर्णाङ्क null ) /* \arg */
{
    /* NOT DEFINED AT THIS MOMENT */
    प्रत्यागम( 0 );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_CfgCs */
/** \brief Configure SPI chip select register */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_SPI_CfgCs( AT91PS_SPI pSPI, /* pointer to a SPI controller */
                               पूर्णाङ्क cs,          /* SPI cs number (0 to 3) */
                               पूर्णाङ्क val )        /*  chip select register */
{
    /** Write to the CSR register */
    *( pSPI->SPI_CSR + cs ) = val;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_EnableIt */
/** \brief Enable SPI interrupt */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_SPI_EnableIt( AT91PS_SPI pSPI,    /* pointer to a SPI controller */
                                  अचिह्नित पूर्णाङ्क flag ) /* IT to be enabled */
{
    /** Write to the IER register */
    pSPI->SPI_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_DisableIt */
/** \brief Disable SPI interrupt */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_SPI_DisableIt( AT91PS_SPI pSPI,    /* pointer to a SPI controller */
                                   अचिह्नित पूर्णाङ्क flag ) /* IT to be disabled */
{
    /** Write to the IDR register */
    pSPI->SPI_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_Reset */
/** \brief Reset the SPI controller */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_SPI_Reset( AT91PS_SPI pSPI /* pointer to a SPI controller */
                               )
{
    /** Write to the CR register */
    pSPI->SPI_CR = AT91C_SPI_SWRST;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_Enable */
/** \brief Enable the SPI controller */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_SPI_Enable( AT91PS_SPI pSPI /* pointer to a SPI controller */
                                )
{
    /** Write to the CR register */
    pSPI->SPI_CR = AT91C_SPI_SPIEN;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_Disable */
/** \brief Disable the SPI controller */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_SPI_Disable( AT91PS_SPI pSPI /* pointer to a SPI controller */
                                 )
{
    /** Write to the CR register */
    pSPI->SPI_CR = AT91C_SPI_SPIDIS;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_CfgMode */
/** \brief Enable the SPI controller */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_SPI_Cfg_बहुलकम्( AT91PS_SPI pSPI, /* pointer to a SPI controller */
                                 पूर्णाङ्क बहुलकम्_2 )       /* mode register */
{
    /** Write to the MR register */
    pSPI->SPI_MR = बहुलकम्_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_CfgPCS */
/** \brief Switch to the correct PCS of SPI Mode Register : Fixed Peripheral Selected */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_SPI_CfgPCS( AT91PS_SPI pSPI,  /* pointer to a SPI controller */
                                वर्ण PCS_Device ) /* PCS of the Device */
{
    /** Write to the MR register */
    pSPI->SPI_MR &= 0xFFF0FFFF;
    pSPI->SPI_MR |= ( ( PCS_Device << 16 ) & AT91C_SPI_PCS );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_ReceiveFrame */
/** \brief Return 2 if PDC has been initialized with Buffer and Next Buffer, 1 if PDC has been initialized with Next Buffer, 0 if PDC is busy */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_SPI_ReceiveFrame( AT91PS_SPI pSPI,
                                              वर्ण * p_बफर,
                                              अचिह्नित पूर्णाङ्क sz_बफर,
                                              वर्ण * p_अग्र_बफर,
                                              अचिह्नित पूर्णाङ्क sz_अग्र_बफर )
{
    प्रत्यागम AT91F_PDC_ReceiveFrame(
        ( AT91PS_PDC ) &( pSPI->SPI_RPR ),
        p_बफर,
        sz_बफर,
        p_अग्र_बफर,
        sz_अग्र_बफर );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_SendFrame */
/** \brief Return 2 if PDC has been initialized with Buffer and Next Buffer, 1 if PDC has been initialized with Next Buffer, 0 if PDC is bSPIy */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_SPI_SendFrame( AT91PS_SPI pSPI,
                                           वर्ण * p_बफर,
                                           अचिह्नित पूर्णाङ्क sz_बफर,
                                           वर्ण * p_अग्र_बफर,
                                           अचिह्नित पूर्णाङ्क sz_अग्र_बफर )
{
    प्रत्यागम AT91F_PDC_SendFrame(
        ( AT91PS_PDC ) &( pSPI->SPI_RPR ),
        p_बफर,
        sz_बफर,
        p_अग्र_बफर,
        sz_अग्र_बफर );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_Close */
/** \brief Close SPI: disable IT disable transfer, close PDC */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_SPI_Close( AT91PS_SPI pSPI ) /* \arg pointer to a SPI controller */
{
    /** Reset all the Chip Select register */
    pSPI->SPI_CSR[ 0 ] = 0;
    pSPI->SPI_CSR[ 1 ] = 0;
    pSPI->SPI_CSR[ 2 ] = 0;
    pSPI->SPI_CSR[ 3 ] = 0;

    /** Reset the SPI mode */
    pSPI->SPI_MR = 0;

    /** Disable all interrupts */
    pSPI->SPI_IDR = 0xFFFFFFFF;

    /** Abort the Peripheral Data Transfers */
    AT91F_PDC_Close( ( AT91PS_PDC ) &( pSPI->SPI_RPR ) );

    /** Disable receiver and transmitter and stop any activity immediately */
    pSPI->SPI_CR = AT91C_SPI_SPIDIS;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_PutChar */
/** \brief Send a character,does not check if ready to send */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_SPI_PutChar( AT91PS_SPI pSPI,
                                 अचिह्नित पूर्णाङ्क character,
                                 अचिह्नित पूर्णाङ्क cs_सङ्ख्या )
{
    अचिह्नित पूर्णाङ्क मानम्_for_cs;

    मानम्_for_cs = ( ~( 1 << cs_सङ्ख्या ) ) & 0xF; /*Place a zero among a 4 ONEs number */
    pSPI->SPI_TDR = ( character & 0xFFFF ) | ( मानम्_for_cs << 16 );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_GetChar */
/** \brief Receive a character,does not check if a character is available */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91F_SPI_GetChar( ध्रुव AT91PS_SPI pSPI )
{
    प्रत्यागम( ( pSPI->SPI_RDR ) & 0xFFFF );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_GetInterruptMaskStatus */
/** \brief Return SPI Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_SPI_Get_व्यवधानम्_आवरणम्_स्थितिः( /* \return SPI Interrupt Mask Status */
    AT91PS_SPI pSpi )                                   /* \arg  pointer to a SPI controller */
{
    प्रत्यागम pSpi->SPI_IMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_IsInterruptMasked */
/** \brief Test if SPI Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91_F_SPI_Is_व्यवधानम्_Masked( AT91PS_SPI pSpi,    /* \arg  pointer to a SPI controller */
                                          अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_SPI_Get_व्यवधानम्_आवरणम्_स्थितिः( pSpi ) & flag );
}

/* *****************************************************************************
*               SOFTWARE API FOR PWMC
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWM_GetStatus */
/** \brief Return PWM Interrupt Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_PWMC_Get_स्थितिः( /* \return PWM Interrupt Status */
    AT91PS_PWMC pPWM )                      /* pointer to a PWM controller */
{
    प्रत्यागम pPWM->PWMC_SR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWM_InterruptEnable */
/** \brief Enable PWM Interrupt */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_PWMC_व्यवधानम्_Enable( AT91PS_PWMC pPwm,   /* \arg  pointer to a PWM controller */
                                          अचिह्नित पूर्णाङ्क flag ) /* \arg  PWM interrupt to be enabled */
{
    pPwm->PWMC_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWM_InterruptDisable */
/** \brief Disable PWM Interrupt */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_PWMC_व्यवधानम्_Disable( AT91PS_PWMC pPwm,   /* \arg  pointer to a PWM controller */
                                           अचिह्नित पूर्णाङ्क flag ) /* \arg  PWM interrupt to be disabled */
{
    pPwm->PWMC_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWM_GetInterruptMaskStatus */
/** \brief Return PWM Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_PWMC_Get_व्यवधानम्_आवरणम्_स्थितिः( /* \return PWM Interrupt Mask Status */
    AT91PS_PWMC pPwm )                                   /* \arg  pointer to a PWM controller */
{
    प्रत्यागम pPwm->PWMC_IMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWM_IsInterruptMasked */
/** \brief Test if PWM Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_PWMC_Is_व्यवधानम्_Masked( AT91PS_PWMC pPWM,   /* \arg  pointer to a PWM controller */
                                                    अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_PWMC_Get_व्यवधानम्_आवरणम्_स्थितिः( pPWM ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWM_IsStatusSet */
/** \brief Test if PWM Interrupt is Set */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_PWMC_Is_स्थितिः_समुच्चयः( AT91PS_PWMC pPWM,   /* \arg  pointer to a PWM controller */
                                              अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_PWMC_Get_स्थितिः( pPWM ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWM_CfgChannel */
/** \brief Test if PWM Interrupt is Set */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PWMC_CfgChannel( AT91PS_PWMC pPWM,       /* \arg  pointer to a PWM controller */
                                     अचिह्नित पूर्णाङ्क channelId, /* \arg PWM channel ID */
                                     अचिह्नित पूर्णाङ्क बहुलकम्_2,      /* \arg  PWM mode */
                                     अचिह्नित पूर्णाङ्क period,    /* \arg PWM period */
                                     अचिह्नित पूर्णाङ्क duty )     /* \arg PWM duty cycle */
{
    pPWM->PWMC_CH[ channelId ].PWMC_CMR = बहुलकम्_2;
    pPWM->PWMC_CH[ channelId ].PWMC_CDTYR = duty;
    pPWM->PWMC_CH[ channelId ].PWMC_CPRDR = period;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWM_StartChannel */
/** \brief Enable channel */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PWMC_StartChannel( AT91PS_PWMC pPWM,   /* \arg  pointer to a PWM controller */
                                       अचिह्नित पूर्णाङ्क flag ) /* \arg  Channels IDs to be enabled */
{
    pPWM->PWMC_ENA = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWM_StopChannel */
/** \brief Disable channel */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PWMC_StopChannel( AT91PS_PWMC pPWM,   /* \arg  pointer to a PWM controller */
                                      अचिह्नित पूर्णाङ्क flag ) /* \arg  Channels IDs to be enabled */
{
    pPWM->PWMC_DIS = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWM_UpdateChannel */
/** \brief Update Period or Duty Cycle */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PWMC_UpdateChannel( AT91PS_PWMC pPWM,       /* \arg  pointer to a PWM controller */
                                        अचिह्नित पूर्णाङ्क channelId, /* \arg PWM channel ID */
                                        अचिह्नित पूर्णाङ्क update )   /* \arg  Channels IDs to be enabled */
{
    pPWM->PWMC_CH[ channelId ].PWMC_CUPDR = update;
}

/* *****************************************************************************
*               SOFTWARE API FOR TC
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TC_InterruptEnable */
/** \brief Enable TC Interrupt */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_TC_व्यवधानम्_Enable( AT91PS_TC pTc,      /* \arg  pointer to a TC controller */
                                        अचिह्नित पूर्णाङ्क flag ) /* \arg  TC interrupt to be enabled */
{
    pTc->TC_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TC_InterruptDisable */
/** \brief Disable TC Interrupt */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_TC_व्यवधानम्_Disable( AT91PS_TC pTc,      /* \arg  pointer to a TC controller */
                                         अचिह्नित पूर्णाङ्क flag ) /* \arg  TC interrupt to be disabled */
{
    pTc->TC_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TC_GetInterruptMaskStatus */
/** \brief Return TC Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_TC_Get_व्यवधानम्_आवरणम्_स्थितिः( /* \return TC Interrupt Mask Status */
    AT91PS_TC pTc )                                    /* \arg  pointer to a TC controller */
{
    प्रत्यागम pTc->TC_IMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TC_IsInterruptMasked */
/** \brief Test if TC Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91_F_TC_Is_व्यवधानम्_Masked( AT91PS_TC pTc,      /* \arg  pointer to a TC controller */
                                         अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_TC_Get_व्यवधानम्_आवरणम्_स्थितिः( pTc ) & flag );
}

/* *****************************************************************************
*               SOFTWARE API FOR PMC
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_CfgSysClkEnableReg */
/** \brief Configure the System Clock Enable Register of the PMC controller */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PMC_CfgSysClkEnableReg( AT91PS_PMC pPMC, /* \arg pointer to PMC controller */
                                            अचिह्नित पूर्णाङ्क बहुलकम्_2 )
{
    /** Write to the SCER register */
    pPMC->PMC_SCER = बहुलकम्_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_CfgSysClkDisableReg */
/** \brief Configure the System Clock Disable Register of the PMC controller */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PMC_CfgSysClkDisableReg( AT91PS_PMC pPMC, /* \arg pointer to PMC controller */
                                             अचिह्नित पूर्णाङ्क बहुलकम्_2 )
{
    /** Write to the SCDR register */
    pPMC->PMC_SCDR = बहुलकम्_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_GetSysClkStatusReg */
/** \brief Return the System Clock Status Register of the PMC controller */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_PMC_Get_Sys_Clk_स्थितिः_Reg( AT91PS_PMC pPMC /* pointer to a CAN controller */
                                                    )
{
    प्रत्यागम pPMC->PMC_SCSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_EnablePeriphClock */
/** \brief Enable peripheral clock */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PMC_EnablePeriphClock( AT91PS_PMC pPMC,         /* \arg pointer to PMC controller */
                                           अचिह्नित पूर्णाङ्क periphIds ) /* \arg IDs of peripherals to enable */
{
    pPMC->PMC_PCER = periphIds;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_DisablePeriphClock */
/** \brief Disable peripheral clock */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PMC_DisablePeriphClock( AT91PS_PMC pPMC,         /* \arg pointer to PMC controller */
                                            अचिह्नित पूर्णाङ्क periphIds ) /* \arg IDs of peripherals to enable */
{
    pPMC->PMC_PCDR = periphIds;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_GetPeriphClock */
/** \brief Get peripheral clock status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_PMC_GetPeriphClock( AT91PS_PMC pPMC ) /* \arg pointer to PMC controller */
{
    प्रत्यागम pPMC->PMC_PCSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_CfgMainOscillatorReg */
/** \brief Cfg the main oscillator */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_CKGR_CfgMainOscillatorReg( AT91PS_CKGR pCKGR, /* \arg pointer to CKGR controller */
                                               अचिह्नित पूर्णाङ्क बहुलकम्_2 )
{
    pCKGR->CKGR_MOR = बहुलकम्_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_GetMainOscillatorReg */
/** \brief Cfg the main oscillator */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_CKGR_GetMainOscillatorReg( AT91PS_CKGR pCKGR ) /* \arg pointer to CKGR controller */
{
    प्रत्यागम pCKGR->CKGR_MOR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_EnableMainOscillator */
/** \brief Enable the main oscillator */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_CKGR_EnableMainOscillator( AT91PS_CKGR pCKGR ) /* \arg pointer to CKGR controller */
{
    pCKGR->CKGR_MOR |= AT91C_CKGR_MOSCEN;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_DisableMainOscillator */
/** \brief Disable the main oscillator */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_CKGR_DisableMainOscillator( AT91PS_CKGR pCKGR ) /* \arg pointer to CKGR controller */
{
    pCKGR->CKGR_MOR &= ~AT91C_CKGR_MOSCEN;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_CfgMainOscStartUpTime */
/** \brief Cfg MORE Register according to the main osc startup time */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_CKGR_Cfg_Main_Osc_Start_ऊर्ध्वम्_Time( AT91PS_CKGR pCKGR,         /* \arg pointer to CKGR controller */
                                                अचिह्नित पूर्णाङ्क startup_time, /* \arg main osc startup time in microsecond (us) */
                                                अचिह्नित पूर्णाङ्क slowClock )   /* \arg slowClock in Hz */
{
    pCKGR->CKGR_MOR &= ~AT91C_CKGR_OSCOUNT;
    pCKGR->CKGR_MOR |= ( ( slowClock * startup_time ) / ( 8 * 1000000 ) ) << 8;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_GetMainClockFreqReg */
/** \brief Cfg the main oscillator */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_CKGR_GetMainClockFreqReg( AT91PS_CKGR pCKGR ) /* \arg pointer to CKGR controller */
{
    प्रत्यागम pCKGR->CKGR_MCFR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_GetMainClock */
/** \brief Return Main clock in Hz */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_CKGR_GetMainClock( AT91PS_CKGR pCKGR,       /* \arg pointer to CKGR controller */
                                               अचिह्नित पूर्णाङ्क slowClock ) /* \arg slowClock in Hz */
{
    प्रत्यागम ( ( pCKGR->CKGR_MCFR & AT91C_CKGR_MAINF ) * slowClock ) >> 4;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_CfgMCKReg */
/** \brief Cfg Master Clock Register */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PMC_CfgMCKReg( AT91PS_PMC pPMC, /* \arg pointer to PMC controller */
                                   अचिह्नित पूर्णाङ्क बहुलकम्_2 )
{
    pPMC->PMC_MCKR = बहुलकम्_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_GetMCKReg */
/** \brief Return Master Clock Register */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_PMC_GetMCKReg( AT91PS_PMC pPMC ) /* \arg pointer to PMC controller */
{
    प्रत्यागम pPMC->PMC_MCKR;
}

/**------------------------------------------------------------------------------ */
/** \fn    AT91F_PMC_GetMasterClock */
/** \brief Return master clock in Hz which corresponds to processor clock for ARM7 */
/**------------------------------------------------------------------------------ */
__inline अचिह्नित पूर्णाङ्क AT91F_PMC_GetMasterClock( AT91PS_PMC pPMC,         /* \arg pointer to PMC controller */
                                                AT91PS_CKGR pCKGR,       /* \arg pointer to CKGR controller */
                                                अचिह्नित पूर्णाङ्क slowClock ) /* \arg slowClock in Hz */
{
    अचिह्नित पूर्णाङ्क reg = pPMC->PMC_MCKR;
    अचिह्नित पूर्णाङ्क prescaler = ( 1 << ( ( reg & AT91C_PMC_PRES ) >> 2 ) );
    अचिह्नित पूर्णाङ्क pllDivider, pllMultiplier;

    विकल्प( reg & AT91C_PMC_CSS )
    {
        पक्ष AT91C_PMC_CSS_SLOW_CLK: /* Slow clock selected */
            प्रत्यागम slowClock / prescaler;

        पक्ष AT91C_PMC_CSS_MAIN_CLK: /* Main clock is selected */
            प्रत्यागम AT91F_CKGR_GetMainClock( pCKGR, slowClock ) / prescaler;

        पक्ष AT91C_PMC_CSS_PLL_CLK: /* PLLB clock is selected */
            reg = pCKGR->CKGR_PLLR;
            pllDivider = ( reg & AT91C_CKGR_DIV );
            pllMultiplier = ( ( reg & AT91C_CKGR_MUL ) >> 16 ) + 1;
            प्रत्यागम AT91F_CKGR_GetMainClock( pCKGR, slowClock ) / pllDivider * pllMultiplier / prescaler;
    }

    प्रत्यागम 0;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_EnablePCK */
/** \brief Enable peripheral clock */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PMC_EnablePCK( AT91PS_PMC pPMC,  /* \arg pointer to PMC controller */
                                   अचिह्नित पूर्णाङ्क pck, /* \arg Peripheral clock identifier 0 .. 7 */
                                   अचिह्नित पूर्णाङ्क बहुलकम्_2 )
{
    pPMC->PMC_PCKR[ pck ] = बहुलकम्_2;
    pPMC->PMC_SCER = ( 1 << pck ) << 8;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_DisablePCK */
/** \brief Enable peripheral clock */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PMC_DisablePCK( AT91PS_PMC pPMC,   /* \arg pointer to PMC controller */
                                    अचिह्नित पूर्णाङ्क pck ) /* \arg Peripheral clock identifier 0 .. 7 */
{
    pPMC->PMC_SCDR = ( 1 << pck ) << 8;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_EnableIt */
/** \brief Enable PMC interrupt */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PMC_EnableIt( AT91PS_PMC pPMC,    /* pointer to a PMC controller */
                                  अचिह्नित पूर्णाङ्क flag ) /* IT to be enabled */
{
    /** Write to the IER register */
    pPMC->PMC_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_DisableIt */
/** \brief Disable PMC interrupt */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PMC_DisableIt( AT91PS_PMC pPMC,    /* pointer to a PMC controller */
                                   अचिह्नित पूर्णाङ्क flag ) /* IT to be disabled */
{
    /** Write to the IDR register */
    pPMC->PMC_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_GetStatus */
/** \brief Return PMC Interrupt Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_PMC_Get_स्थितिः( /* \return PMC Interrupt Status */
    AT91PS_PMC pPMC )                      /* pointer to a PMC controller */
{
    प्रत्यागम pPMC->PMC_SR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_GetInterruptMaskStatus */
/** \brief Return PMC Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_PMC_Get_व्यवधानम्_आवरणम्_स्थितिः( /* \return PMC Interrupt Mask Status */
    AT91PS_PMC pPMC )                                   /* pointer to a PMC controller */
{
    प्रत्यागम pPMC->PMC_IMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_IsInterruptMasked */
/** \brief Test if PMC Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_PMC_Is_व्यवधानम्_Masked( AT91PS_PMC pPMC,    /* \arg  pointer to a PMC controller */
                                                   अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_PMC_Get_व्यवधानम्_आवरणम्_स्थितिः( pPMC ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_IsStatusSet */
/** \brief Test if PMC Status is Set */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_PMC_Is_स्थितिः_समुच्चयः( AT91PS_PMC pPMC,    /* \arg  pointer to a PMC controller */
                                             अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_PMC_Get_स्थितिः( pPMC ) & flag );
} /* *****************************************************************************
  *              SOFTWARE API FOR ADC
  ***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_EnableIt */
/** \brief Enable ADC interrupt */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_ADC_EnableIt( AT91PS_ADC pADC,    /* pointer to a ADC controller */
                                  अचिह्नित पूर्णाङ्क flag ) /* IT to be enabled */
{
    /** Write to the IER register */
    pADC->ADC_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_DisableIt */
/** \brief Disable ADC interrupt */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_ADC_DisableIt( AT91PS_ADC pADC,    /* pointer to a ADC controller */
                                   अचिह्नित पूर्णाङ्क flag ) /* IT to be disabled */
{
    /** Write to the IDR register */
    pADC->ADC_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetStatus */
/** \brief Return ADC Interrupt Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_ADC_Get_स्थितिः( /* \return ADC Interrupt Status */
    AT91PS_ADC pADC )                      /* pointer to a ADC controller */
{
    प्रत्यागम pADC->ADC_SR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetInterruptMaskStatus */
/** \brief Return ADC Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_ADC_Get_व्यवधानम्_आवरणम्_स्थितिः( /* \return ADC Interrupt Mask Status */
    AT91PS_ADC pADC )                                   /* pointer to a ADC controller */
{
    प्रत्यागम pADC->ADC_IMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_IsInterruptMasked */
/** \brief Test if ADC Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_ADC_Is_व्यवधानम्_Masked( AT91PS_ADC pADC,    /* \arg  pointer to a ADC controller */
                                                   अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_ADC_Get_व्यवधानम्_आवरणम्_स्थितिः( pADC ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_IsStatusSet */
/** \brief Test if ADC Status is Set */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_ADC_Is_स्थितिः_समुच्चयः( AT91PS_ADC pADC,    /* \arg  pointer to a ADC controller */
                                             अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_ADC_Get_स्थितिः( pADC ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_CfgModeReg */
/** \brief Configure the Mode Register of the ADC controller */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_ADC_Cfg_बहुलकम्_Reg( AT91PS_ADC pADC,    /* pointer to a ADC controller */
                                    अचिह्नित पूर्णाङ्क बहुलकम्_2 ) /* mode register */
{
    /** Write to the MR register */
    pADC->ADC_MR = बहुलकम्_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetModeReg */
/** \brief Return the Mode Register of the ADC controller value */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_ADC_Get_बहुलकम्_Reg( AT91PS_ADC pADC /* pointer to a ADC controller */
                                            )
{
    प्रत्यागम pADC->ADC_MR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_CfgTimings */
/** \brief Configure the different necessary timings of the ADC controller */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_ADC_CfgTimings( AT91PS_ADC pADC,                    /* pointer to a ADC controller */
                                    अचिह्नित पूर्णाङ्क mck_clock,             /* in MHz */
                                    अचिह्नित पूर्णाङ्क adc_clock,             /* in MHz */
                                    अचिह्नित पूर्णाङ्क startup_time,          /* in us */
                                    अचिह्नित पूर्णाङ्क sample_and_hold_time ) /* in ns */
{
    अचिह्नित पूर्णाङ्क prescal, startup, shtim;

    prescal = mck_clock / ( 2 * adc_clock ) - 1;
    startup = adc_clock * startup_time / 8 - 1;
    shtim = adc_clock * sample_and_hold_time / 1000 - 1;

    /** Write to the MR register */
    pADC->ADC_MR = ( ( prescal << 8 ) & AT91C_ADC_PRESCAL ) | ( ( startup << 16 ) & AT91C_ADC_STARTUP ) | ( ( shtim << 24 ) & AT91C_ADC_SHTIM );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_EnableChannel */
/** \brief Return ADC Timer Register Value */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_ADC_EnableChannel( AT91PS_ADC pADC,       /* pointer to a ADC controller */
                                       अचिह्नित पूर्णाङ्क channel ) /* mode register */
{
    /** Write to the CHER register */
    pADC->ADC_CHER = channel;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_DisableChannel */
/** \brief Return ADC Timer Register Value */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_ADC_DisableChannel( AT91PS_ADC pADC,       /* pointer to a ADC controller */
                                        अचिह्नित पूर्णाङ्क channel ) /* mode register */
{
    /** Write to the CHDR register */
    pADC->ADC_CHDR = channel;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetChannelStatus */
/** \brief Return ADC Timer Register Value */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_ADC_Get_Channel_स्थितिः( AT91PS_ADC pADC /* pointer to a ADC controller */
                                                  )
{
    प्रत्यागम pADC->ADC_CHSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_StartConversion */
/** \brief Software request for a analog to digital conversion */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_ADC_StartConversion( AT91PS_ADC pADC /* pointer to a ADC controller */
                                         )
{
    pADC->ADC_CR = AT91C_ADC_START;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_SoftReset */
/** \brief Software reset */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_ADC_SoftReset( AT91PS_ADC pADC /* pointer to a ADC controller */
                                   )
{
    pADC->ADC_CR = AT91C_ADC_SWRST;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetLastConvertedData */
/** \brief Return the Last Converted Data */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_ADC_Get_चरमः_Converted_दत्त( AT91PS_ADC pADC /* pointer to a ADC controller */
                                                      )
{
    प्रत्यागम pADC->ADC_LCDR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetConvertedDataCH0 */
/** \brief Return the Channel 0 Converted Data */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_ADC_Get_Converted_दत्त_CH0( AT91PS_ADC pADC /* pointer to a ADC controller */
                                                     )
{
    प्रत्यागम pADC->ADC_CDR0;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetConvertedDataCH1 */
/** \brief Return the Channel 1 Converted Data */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_ADC_Get_Converted_दत्त_CH1( AT91PS_ADC pADC /* pointer to a ADC controller */
                                                     )
{
    प्रत्यागम pADC->ADC_CDR1;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetConvertedDataCH2 */
/** \brief Return the Channel 2 Converted Data */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_ADC_Get_Converted_दत्त_CH2( AT91PS_ADC pADC /* pointer to a ADC controller */
                                                     )
{
    प्रत्यागम pADC->ADC_CDR2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetConvertedDataCH3 */
/** \brief Return the Channel 3 Converted Data */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_ADC_Get_Converted_दत्त_CH3( AT91PS_ADC pADC /* pointer to a ADC controller */
                                                     )
{
    प्रत्यागम pADC->ADC_CDR3;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetConvertedDataCH4 */
/** \brief Return the Channel 4 Converted Data */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_ADC_Get_Converted_दत्त_CH4( AT91PS_ADC pADC /* pointer to a ADC controller */
                                                     )
{
    प्रत्यागम pADC->ADC_CDR4;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetConvertedDataCH5 */
/** \brief Return the Channel 5 Converted Data */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_ADC_Get_Converted_दत्त_CH5( AT91PS_ADC pADC /* pointer to a ADC controller */
                                                     )
{
    प्रत्यागम pADC->ADC_CDR5;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetConvertedDataCH6 */
/** \brief Return the Channel 6 Converted Data */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_ADC_Get_Converted_दत्त_CH6( AT91PS_ADC pADC /* pointer to a ADC controller */
                                                     )
{
    प्रत्यागम pADC->ADC_CDR6;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetConvertedDataCH7 */
/** \brief Return the Channel 7 Converted Data */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_ADC_Get_Converted_दत्त_CH7( AT91PS_ADC pADC /* pointer to a ADC controller */
                                                     )
{
    प्रत्यागम pADC->ADC_CDR7;
}

/* *****************************************************************************
*               SOFTWARE API FOR PIO
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgPeriph */
/** \brief Enable pins to be derived by peripheral */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PIO_CfgPeriph( AT91PS_PIO pPio,             /* \arg pointer to a PIO controller */
                                   अचिह्नित पूर्णाङ्क periphAEnable,  /* \arg PERIPH A to enable */
                                   अचिह्नित पूर्णाङ्क periphBEnable ) /* \arg PERIPH B to enable */

{
    pPio->PIO_ASR = periphAEnable;
    pPio->PIO_BSR = periphBEnable;
    pPio->PIO_PDR = ( periphAEnable | periphBEnable ); /* Set in Periph mode */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgOutput */
/** \brief Enable PIO in output mode */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PIO_CfgOutput( AT91PS_PIO pPio,         /* \arg pointer to a PIO controller */
                                   अचिह्नित पूर्णाङ्क pioEnable ) /* \arg PIO to be enabled */
{
    pPio->PIO_प्रत्येकम् = pioEnable;                              /* Set in PIO mode */
    pPio->PIO_OER = pioEnable;                              /* Configure in Output */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgInput */
/** \brief Enable PIO in input mode */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_PIO_Cfg_निवेशः( AT91PS_PIO pPio,           /* \arg pointer to a PIO controller */
                                  अचिह्नित पूर्णाङ्क निवेशः_Enable ) /* \arg PIO to be enabled */
{
    /* Disable output */
    pPio->PIO_ODR = निवेशः_Enable;
    pPio->PIO_प्रत्येकम् = निवेशः_Enable;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgOpendrain */
/** \brief Configure PIO in open drain */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PIO_CfgOpendrain( AT91PS_PIO pPio,              /* \arg pointer to a PIO controller */
                                      अचिह्नित पूर्णाङ्क multiDrvEnable ) /* \arg pio to be configured in open drain */
{
    /* Configure the multi-drive option */
    pPio->PIO_MDDR = ~multiDrvEnable;
    pPio->PIO_MDER = multiDrvEnable;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgPullup */
/** \brief Enable pullup on PIO */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PIO_CfgPullup( AT91PS_PIO pPio,            /* \arg pointer to a PIO controller */
                                   अचिह्नित पूर्णाङ्क pullupEnable ) /* \arg enable pullup on PIO */
{
    /* Connect or not Pullup */
    pPio->PIO_PPUDR = ~pullupEnable;
    pPio->PIO_PPUER = pullupEnable;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgDirectDrive */
/** \brief Enable direct drive on PIO */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_PIO_Cfg_प्रत्यक्षम्_Drive( AT91PS_PIO pPio,           /* \arg pointer to a PIO controller */
                                        अचिह्नित पूर्णाङ्क प्रत्यक्षम्_Drive ) /* \arg PIO to be configured with direct drive */

{
    /* Configure the Direct Drive */
    pPio->PIO_OWDR = ~प्रत्यक्षम्_Drive;
    pPio->PIO_OWER = प्रत्यक्षम्_Drive;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgInputFilter */
/** \brief Enable input filter on input PIO */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_PIO_Cfg_निवेशः_Filter( AT91PS_PIO pPio,           /* \arg pointer to a PIO controller */
                                        अचिह्नित पूर्णाङ्क निवेशः_Filter ) /* \arg PIO to be configured with input filter */

{
    /* Configure the Direct Drive */
    pPio->PIO_IFDR = ~निवेशः_Filter;
    pPio->PIO_IFER = निवेशः_Filter;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetInput */
/** \brief Return PIO input value */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_PIO_Get_निवेशः( /* \return PIO input */
    AT91PS_PIO pPio )                     /* \arg  pointer to a PIO controller */
{
    प्रत्यागम pPio->PIO_PDSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsInputSet */
/** \brief Test if PIO is input flag is active */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91_F_PIO_Is_निवेशः_समुच्चयः( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                   अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_PIO_Get_निवेशः( pPio ) & flag );
}


/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_SetOutput */
/** \brief Set to 1 output PIO */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_PIO_समुच्चयः_Output( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                   अचिह्नित पूर्णाङ्क flag ) /* \arg  output to be set */
{
    pPio->PIO_SODR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_ClearOutput */
/** \brief Set to 0 output PIO */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PIO_ClearOutput( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                     अचिह्नित पूर्णाङ्क flag ) /* \arg  output to be cleared */
{
    pPio->PIO_CODR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_ForceOutput */
/** \brief Force output when Direct drive option is enabled */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PIO_ForceOutput( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                     अचिह्नित पूर्णाङ्क flag ) /* \arg  output to be forced */
{
    pPio->PIO_ODSR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_Enable */
/** \brief Enable PIO */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PIO_Enable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                अचिह्नित पूर्णाङ्क flag ) /* \arg  pio to be enabled */
{
    pPio->PIO_प्रत्येकम् = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_Disable */
/** \brief Disable PIO */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PIO_Disable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                 अचिह्नित पूर्णाङ्क flag ) /* \arg  pio to be disabled */
{
    pPio->PIO_PDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetStatus */
/** \brief Return PIO Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_PIO_Get_स्थितिः( /* \return PIO Status */
    AT91PS_PIO pPio )                      /* \arg  pointer to a PIO controller */
{
    प्रत्यागम pPio->PIO_PSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsSet */
/** \brief Test if PIO is Set */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91_F_PIO_Is_समुच्चयः( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                              अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_PIO_Get_स्थितिः( pPio ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_OutputEnable */
/** \brief Output Enable PIO */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PIO_OutputEnable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                      अचिह्नित पूर्णाङ्क flag ) /* \arg  pio output to be enabled */
{
    pPio->PIO_OER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_OutputDisable */
/** \brief Output Enable PIO */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PIO_OutputDisable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                       अचिह्नित पूर्णाङ्क flag ) /* \arg  pio output to be disabled */
{
    pPio->PIO_ODR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetOutputStatus */
/** \brief Return PIO Output Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_PIO_Get_Output_स्थितिः( /* \return PIO Output Status */
    AT91PS_PIO pPio )                            /* \arg  pointer to a PIO controller */
{
    प्रत्यागम pPio->PIO_OSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsOuputSet */
/** \brief Test if PIO Output is Set */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91_F_PIO_Is_Output_समुच्चयः( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                    अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_PIO_Get_Output_स्थितिः( pPio ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_InputFilterEnable */
/** \brief Input Filter Enable PIO */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_PIO_निवेशः_Filter_Enable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                           अचिह्नित पूर्णाङ्क flag ) /* \arg  pio input filter to be enabled */
{
    pPio->PIO_IFER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_InputFilterDisable */
/** \brief Input Filter Disable PIO */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_PIO_निवेशः_Filter_Disable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                            अचिह्नित पूर्णाङ्क flag ) /* \arg  pio input filter to be disabled */
{
    pPio->PIO_IFDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetInputFilterStatus */
/** \brief Return PIO Input Filter Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_PIO_Get_निवेशः_Filter_स्थितिः( /* \return PIO Input Filter Status */
    AT91PS_PIO pPio )                                 /* \arg  pointer to a PIO controller */
{
    प्रत्यागम pPio->PIO_IFSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsInputFilterSet */
/** \brief Test if PIO Input filter is Set */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91_F_PIO_Is_निवेशः_Filter_समुच्चयः( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                         अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_PIO_Get_निवेशः_Filter_स्थितिः( pPio ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetOutputDataStatus */
/** \brief Return PIO Output Data Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_PIO_Get_Output_दत्त_स्थितिः( /* \return PIO Output Data Status */
    AT91PS_PIO pPio )                                /* \arg  pointer to a PIO controller */
{
    प्रत्यागम pPio->PIO_ODSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_InterruptEnable */
/** \brief Enable PIO Interrupt */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_PIO_व्यवधानम्_Enable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                         अचिह्नित पूर्णाङ्क flag ) /* \arg  pio interrupt to be enabled */
{
    pPio->PIO_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_InterruptDisable */
/** \brief Disable PIO Interrupt */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_PIO_व्यवधानम्_Disable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                          अचिह्नित पूर्णाङ्क flag ) /* \arg  pio interrupt to be disabled */
{
    pPio->PIO_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetInterruptMaskStatus */
/** \brief Return PIO Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_PIO_Get_व्यवधानम्_आवरणम्_स्थितिः( /* \return PIO Interrupt Mask Status */
    AT91PS_PIO pPio )                                   /* \arg  pointer to a PIO controller */
{
    प्रत्यागम pPio->PIO_IMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetInterruptStatus */
/** \brief Return PIO Interrupt Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_PIO_Get_व्यवधानम्_स्थितिः( /* \return PIO Interrupt Status */
    AT91PS_PIO pPio )                               /* \arg  pointer to a PIO controller */
{
    प्रत्यागम pPio->PIO_ISR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsInterruptMasked */
/** \brief Test if PIO Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91_F_PIO_Is_व्यवधानम्_Masked( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                          अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_PIO_Get_व्यवधानम्_आवरणम्_स्थितिः( pPio ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsInterruptSet */
/** \brief Test if PIO Interrupt is Set */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91_F_PIO_Is_व्यवधानम्_समुच्चयः( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                       अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_PIO_Get_व्यवधानम्_स्थितिः( pPio ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_MultiDriverEnable */
/** \brief Multi Driver Enable PIO */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PIO_MultiDriverEnable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                           अचिह्नित पूर्णाङ्क flag ) /* \arg  pio to be enabled */
{
    pPio->PIO_MDER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_MultiDriverDisable */
/** \brief Multi Driver Disable PIO */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PIO_MultiDriverDisable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                            अचिह्नित पूर्णाङ्क flag ) /* \arg  pio to be disabled */
{
    pPio->PIO_MDDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetMultiDriverStatus */
/** \brief Return PIO Multi Driver Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_PIO_Get_Multi_Driver_स्थितिः( /* \return PIO Multi Driver Status */
    AT91PS_PIO pPio )                                 /* \arg  pointer to a PIO controller */
{
    प्रत्यागम pPio->PIO_MDSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsMultiDriverSet */
/** \brief Test if PIO MultiDriver is Set */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91_F_PIO_Is_Multi_Driver_समुच्चयः( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                         अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_PIO_Get_Multi_Driver_स्थितिः( pPio ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_A_RegisterSelection */
/** \brief PIO A Register Selection */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_PIO_A_पञ्जिकाकोशः_Selection( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                             अचिह्नित पूर्णाङ्क flag ) /* \arg  pio A register selection */
{
    pPio->PIO_ASR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_B_RegisterSelection */
/** \brief PIO B Register Selection */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_PIO_B_पञ्जिकाकोशः_Selection( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                             अचिह्नित पूर्णाङ्क flag ) /* \arg  pio B register selection */
{
    pPio->PIO_BSR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_Get_AB_RegisterStatus */
/** \brief Return PIO Interrupt Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_PIO_Get_AB_पञ्जिकाकोशः_स्थितिः( /* \return PIO AB Register Status */
    AT91PS_PIO pPio )                                  /* \arg  pointer to a PIO controller */
{
    प्रत्यागम pPio->PIO_ABSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsAB_RegisterSet */
/** \brief Test if PIO AB Register is Set */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91_F_PIO_Is_AB_पञ्जिकाकोशः_समुच्चयः( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                         अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_PIO_Get_AB_पञ्जिकाकोशः_स्थितिः( pPio ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_OutputWriteEnable */
/** \brief Output Write Enable PIO */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PIO_OutputWriteEnable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                           अचिह्नित पूर्णाङ्क flag ) /* \arg  pio output write to be enabled */
{
    pPio->PIO_OWER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_OutputWriteDisable */
/** \brief Output Write Disable PIO */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PIO_OutputWriteDisable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                            अचिह्नित पूर्णाङ्क flag ) /* \arg  pio output write to be disabled */
{
    pPio->PIO_OWDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetOutputWriteStatus */
/** \brief Return PIO Output Write Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_PIO_Get_Output_Write_स्थितिः( /* \return PIO Output Write Status */
    AT91PS_PIO pPio )                                 /* \arg  pointer to a PIO controller */
{
    प्रत्यागम pPio->PIO_OWSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsOutputWriteSet */
/** \brief Test if PIO OutputWrite is Set */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91_F_PIO_Is_Output_Write_समुच्चयः( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                         अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_PIO_Get_Output_Write_स्थितिः( pPio ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetCfgPullup */
/** \brief Return PIO Configuration Pullup */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_PIO_GetCfgPullup( /* \return PIO Configuration Pullup */
    AT91PS_PIO pPio )                         /* \arg  pointer to a PIO controller */
{
    प्रत्यागम pPio->PIO_PPUSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsOutputDataStatusSet */
/** \brief Test if PIO Output Data Status is Set */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91_F_PIO_Is_Output_दत्त_स्थितिः_समुच्चयः( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                              अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_PIO_Get_Output_दत्त_स्थितिः( pPio ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsCfgPullupStatusSet */
/** \brief Test if PIO Configuration Pullup Status is Set */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91_F_PIO_Is_Cfg_Pullup_स्थितिः_समुच्चयः( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                             अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( ~AT91F_PIO_GetCfgPullup( pPio ) & flag );
}

/* *****************************************************************************
*               SOFTWARE API FOR TWI
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TWI_EnableIt */
/** \brief Enable TWI IT */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_TWI_EnableIt( AT91PS_TWI pTWI,    /* \arg pointer to a TWI controller */
                                  अचिह्नित पूर्णाङ्क flag ) /* \arg IT to be enabled */
{
    /** Write to the IER register */
    pTWI->TWI_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TWI_DisableIt */
/** \brief Disable TWI IT */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_TWI_DisableIt( AT91PS_TWI pTWI,    /* \arg pointer to a TWI controller */
                                   अचिह्नित पूर्णाङ्क flag ) /* \arg IT to be disabled */
{
    /** Write to the IDR register */
    pTWI->TWI_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TWI_Configure */
/** \brief Configure TWI in master mode */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_TWI_Configure( AT91PS_TWI pTWI ) /* \arg pointer to a TWI controller */
{
    /** Disable interrupts */
    pTWI->TWI_IDR = ( अचिह्नित पूर्णाङ्क ) -1;

    /** Reset peripheral */
    pTWI->TWI_CR = AT91C_TWI_SWRST;

    /** Set Master mode */
    pTWI->TWI_CR = AT91C_TWI_MSEN | AT91C_TWI_SVDIS;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TWI_GetInterruptMaskStatus */
/** \brief Return TWI Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_TWI_Get_व्यवधानम्_आवरणम्_स्थितिः( /* \return TWI Interrupt Mask Status */
    AT91PS_TWI pTwi )                                   /* \arg  pointer to a TWI controller */
{
    प्रत्यागम pTwi->TWI_IMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TWI_IsInterruptMasked */
/** \brief Test if TWI Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91_F_TWI_Is_व्यवधानम्_Masked( AT91PS_TWI pTwi,    /* \arg  pointer to a TWI controller */
                                          अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_TWI_Get_व्यवधानम्_आवरणम्_स्थितिः( pTwi ) & flag );
}

/* *****************************************************************************
*               SOFTWARE API FOR USART
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_Baudrate */
/** \brief Calculate the baudrate */
/** Standard Asynchronous Mode : 8 bits , 1 stop , no parity */
#परिभाषय AT91_C_US_ASYNC_बहुलकम्    \
    ( AT91_C_US_USMODE_प्रसामान्यम् + \
      AT91C_US_NBSTOP_1_BIT +  \
      AT91C_US_PAR_NONE +      \
      AT91_C_US_CHRL_8_द्वयङ्काः +   \
      AT91C_US_CLKS_CLOCK )

/** Standard External Asynchronous Mode : 8 bits , 1 stop , no parity */
#परिभाषय AT91_C_US_ASYNC_SCK_बहुलकम् \
    ( AT91_C_US_USMODE_प्रसामान्यम् +  \
      AT91C_US_NBSTOP_1_BIT +   \
      AT91C_US_PAR_NONE +       \
      AT91_C_US_CHRL_8_द्वयङ्काः +    \
      AT91C_US_CLKS_EXT )

/** Standard Synchronous Mode : 8 bits , 1 stop , no parity */
#परिभाषय AT91_C_US_SYNC_बहुलकम्     \
    ( AT91C_US_SYNC +          \
      AT91_C_US_USMODE_प्रसामान्यम् + \
      AT91C_US_NBSTOP_1_BIT +  \
      AT91C_US_PAR_NONE +      \
      AT91_C_US_CHRL_8_द्वयङ्काः +   \
      AT91C_US_CLKS_CLOCK )

/** SCK used Label */
#परिभाषय AT91_C_US_SCK_प्रयुक्तम्    ( AT91C_US_CKLO | AT91C_US_CLKS_EXT )

/** Standard ISO T=0 Mode : 8 bits , 1 stop , parity */
#परिभाषय AT91_C_US_ISO_READER_बहुलकम्  \
    ( AT91C_US_USMODE_ISO7816_0 + \
      AT91C_US_CLKS_CLOCK +       \
      AT91C_US_NBSTOP_1_BIT +     \
      AT91C_US_PAR_EVEN +         \
      AT91_C_US_CHRL_8_द्वयङ्काः +      \
      AT91C_US_CKLO +             \
      AT91C_US_OVER )

/** Standard IRDA mode */
#परिभाषय AT91_C_US_ASYNC_IRDA_बहुलकम् \
    ( AT91C_US_USMODE_IRDA +     \
      AT91C_US_NBSTOP_1_BIT +    \
      AT91C_US_PAR_NONE +        \
      AT91_C_US_CHRL_8_द्वयङ्काः +     \
      AT91C_US_CLKS_CLOCK )

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_Baudrate */
/** \brief Calculate baud_value according to the main clock and the baud rate */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_US_Baudrate( ध्रुव अचिह्नित पूर्णाङ्क main_clock, /* \arg peripheral clock */
                                         ध्रुव अचिह्नित पूर्णाङ्क baud_दरः ) /* \arg UART baudrate */
{
    अचिह्नित पूर्णाङ्क baud_मानम् = ( ( main_clock * 10 ) / ( baud_दरः * 16 ) );

    यदि( ( baud_मानम् % 10 ) >= 5 )
    {
        baud_मानम् = ( baud_मानम् / 10 ) + 1;
    }
    अन्यथा
    {
        baud_मानम् /= 10;
    }

    प्रत्यागम baud_मानम्;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_SetBaudrate */
/** \brief Set the baudrate according to the CPU clock */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_US_समुच्चयः_Baudrate( AT91PS_USART pUSART,    /* \arg pointer to a USART controller */
                                    अचिह्नित पूर्णाङ्क mainClock, /* \arg peripheral clock */
                                    अचिह्नित पूर्णाङ्क जवः_2 )    /* \arg UART baudrate */
{
    /** Define the baud rate divisor register */
    pUSART->US_BRGR = AT91F_US_Baudrate( mainClock, जवः_2 );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_SetTimeguard */
/** \brief Set USART timeguard */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_US_समुच्चयः_Timeguard( AT91PS_USART pUSART,     /* \arg pointer to a USART controller */
                                     अचिह्नित पूर्णाङ्क timeguard ) /* \arg timeguard value */
{
    /** Write the Timeguard Register */
    pUSART->US_TTGR = timeguard;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_EnableIt */
/** \brief Enable USART IT */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_US_EnableIt( AT91PS_USART pUSART, /* \arg pointer to a USART controller */
                                 अचिह्नित पूर्णाङ्क flag )  /* \arg IT to be enabled */
{
    /** Write to the IER register */
    pUSART->US_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_DisableIt */
/** \brief Disable USART IT */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_US_DisableIt( AT91PS_USART pUSART, /* \arg pointer to a USART controller */
                                  अचिह्नित पूर्णाङ्क flag )  /* \arg IT to be disabled */
{
    /** Write to the IER register */
    pUSART->US_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_Configure */
/** \brief Configure USART */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_US_Configure( AT91PS_USART pUSART,     /* \arg pointer to a USART controller */
                                  अचिह्नित पूर्णाङ्क mainClock,  /* \arg peripheral clock */
                                  अचिह्नित पूर्णाङ्क बहुलकम्_2,       /* \arg mode Register to be programmed */
                                  अचिह्नित पूर्णाङ्क baud_दरः_2,   /* \arg baudrate to be programmed */
                                  अचिह्नित पूर्णाङ्क timeguard ) /* \arg timeguard to be programmed */
{
    /** Disable interrupts */
    pUSART->US_IDR = ( अचिह्नित पूर्णाङ्क ) -1;

    /** Reset receiver and transmitter */
    pUSART->US_CR = AT91C_US_RSTRX | AT91C_US_RSTTX | AT91C_US_RXDIS | AT91C_US_TXDIS;

    /** Define the baud rate divisor register */
    AT91_F_US_समुच्चयः_Baudrate( pUSART, mainClock, baud_दरः_2 );

    /** Write the Timeguard Register */
    AT91_F_US_समुच्चयः_Timeguard( pUSART, timeguard );

    /** Clear Transmit and Receive Counters */
    AT91F_PDC_Open( ( AT91PS_PDC ) &( pUSART->US_RPR ) );

    /** Define the USART mode */
    pUSART->US_MR = बहुलकम्_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_EnableRx */
/** \brief Enable receiving characters */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_US_EnableRx( AT91PS_USART pUSART ) /* \arg pointer to a USART controller */
{
    /** Enable receiver */
    pUSART->US_CR = AT91C_US_RXEN;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_EnableTx */
/** \brief Enable sending characters */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_US_EnableTx( AT91PS_USART pUSART ) /* \arg pointer to a USART controller */
{
    /** Enable  transmitter */
    pUSART->US_CR = AT91C_US_TXEN;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_ResetRx */
/** \brief Reset Receiver and re-enable it */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_US_ResetRx( AT91PS_USART pUSART ) /* \arg pointer to a USART controller */
{
    /** Reset receiver */
    pUSART->US_CR = AT91C_US_RSTRX;
    /** Re-Enable receiver */
    pUSART->US_CR = AT91C_US_RXEN;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_ResetTx */
/** \brief Reset Transmitter and re-enable it */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_US_ResetTx( AT91PS_USART pUSART ) /* \arg pointer to a USART controller */
{
    /** Reset transmitter */
    pUSART->US_CR = AT91C_US_RSTTX;
    /** Enable transmitter */
    pUSART->US_CR = AT91C_US_TXEN;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_DisableRx */
/** \brief Disable Receiver */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_US_DisableRx( AT91PS_USART pUSART ) /* \arg pointer to a USART controller */
{
    /** Disable receiver */
    pUSART->US_CR = AT91C_US_RXDIS;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_DisableTx */
/** \brief Disable Transmitter */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_US_DisableTx( AT91PS_USART pUSART ) /* \arg pointer to a USART controller */
{
    /** Disable transmitter */
    pUSART->US_CR = AT91C_US_TXDIS;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_Close */
/** \brief Close USART: disable IT disable receiver and transmitter, close PDC */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_US_Close( AT91PS_USART pUSART ) /* \arg pointer to a USART controller */
{
    /** Reset the baud rate divisor register */
    pUSART->US_BRGR = 0;

    /** Reset the USART mode */
    pUSART->US_MR = 0;

    /** Reset the Timeguard Register */
    pUSART->US_TTGR = 0;

    /** Disable all interrupts */
    pUSART->US_IDR = 0xFFFFFFFF;

    /** Abort the Peripheral Data Transfers */
    AT91F_PDC_Close( ( AT91PS_PDC ) &( pUSART->US_RPR ) );

    /** Disable receiver and transmitter and stop any activity immediately */
    pUSART->US_CR = AT91C_US_TXDIS | AT91C_US_RXDIS | AT91C_US_RSTTX | AT91C_US_RSTRX;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_TxReady */
/** \brief Return 1 if a character can be written in US_THR */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_US_TxReady( AT91PS_USART pUSART ) /* \arg pointer to a USART controller */
{
    प्रत्यागम( pUSART->US_CSR & AT91C_US_TXRDY );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_RxReady */
/** \brief Return 1 if a character can be read in US_RHR */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_US_RxReady( AT91PS_USART pUSART ) /* \arg pointer to a USART controller */
{
    प्रत्यागम( pUSART->US_CSR & AT91C_US_RXRDY );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_Error */
/** \brief Return the error flag */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_US_Error( AT91PS_USART pUSART ) /* \arg pointer to a USART controller */
{
    प्रत्यागम( pUSART->US_CSR &
            ( AT91C_US_OVRE |    /* Overrun error */
              AT91C_US_FRAME |   /* Framing error */
              AT91C_US_PARE ) ); /* Parity error */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_PutChar */
/** \brief Send a character,does not check if ready to send */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_US_PutChar( AT91PS_USART pUSART,
                                पूर्णाङ्क character )
{
    pUSART->US_THR = ( character & 0x1FF );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_GetChar */
/** \brief Receive a character,does not check if a character is available */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91F_US_GetChar( ध्रुव AT91PS_USART pUSART )
{
    प्रत्यागम( ( pUSART->US_RHR ) & 0x1FF );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_SendFrame */
/** \brief Return 2 if PDC has been initialized with Buffer and Next Buffer, 1 if PDC has been initialized with Next Buffer, 0 if PDC is busy */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_US_SendFrame( AT91PS_USART pUSART,
                                          वर्ण * p_बफर,
                                          अचिह्नित पूर्णाङ्क sz_बफर,
                                          वर्ण * p_अग्र_बफर,
                                          अचिह्नित पूर्णाङ्क sz_अग्र_बफर )
{
    प्रत्यागम AT91F_PDC_SendFrame(
        ( AT91PS_PDC ) &( pUSART->US_RPR ),
        p_बफर,
        sz_बफर,
        p_अग्र_बफर,
        sz_अग्र_बफर );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_ReceiveFrame */
/** \brief Return 2 if PDC has been initialized with Buffer and Next Buffer, 1 if PDC has been initialized with Next Buffer, 0 if PDC is busy */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_US_ReceiveFrame( AT91PS_USART pUSART,
                                             वर्ण * p_बफर,
                                             अचिह्नित पूर्णाङ्क sz_बफर,
                                             वर्ण * p_अग्र_बफर,
                                             अचिह्नित पूर्णाङ्क sz_अग्र_बफर )
{
    प्रत्यागम AT91F_PDC_ReceiveFrame(
        ( AT91PS_PDC ) &( pUSART->US_RPR ),
        p_बफर,
        sz_बफर,
        p_अग्र_बफर,
        sz_अग्र_बफर );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_SetIrdaFilter */
/** \brief Set the value of IrDa filter register */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_US_समुच्चयः_Irda_Filter( AT91PS_USART pUSART,
                                      अचिह्नित वर्ण मानम् )
{
    pUSART->US_IF = मानम्;
}

/* *****************************************************************************
*               SOFTWARE API FOR UDP
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_EnableIt */
/** \brief Enable UDP IT */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_UDP_EnableIt( AT91PS_UDP pUDP,    /* \arg pointer to a UDP controller */
                                  अचिह्नित पूर्णाङ्क flag ) /* \arg IT to be enabled */
{
    /** Write to the IER register */
    pUDP->UDP_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_DisableIt */
/** \brief Disable UDP IT */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_UDP_DisableIt( AT91PS_UDP pUDP,    /* \arg pointer to a UDP controller */
                                   अचिह्नित पूर्णाङ्क flag ) /* \arg IT to be disabled */
{
    /** Write to the IDR register */
    pUDP->UDP_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_SetAddress */
/** \brief Set UDP functional address */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_UDP_समुच्चयः_स्थानाङ्कः( AT91PS_UDP pUDP,        /* \arg pointer to a UDP controller */
                                    अचिह्नित वर्ण स्थानाङ्कः_2 ) /* \arg new UDP address */
{
    pUDP->UDP_FADDR = ( AT91C_UDP_FEN | स्थानाङ्कः_2 );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_EnableEp */
/** \brief Enable Endpoint */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_UDP_EnableEp( AT91PS_UDP pUDP,    /* \arg pointer to a UDP controller */
                                  अचिह्नित पूर्णाङ्क flag ) /* \arg endpoints to be enabled */
{
    pUDP->UDP_GLBSTATE |= flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_DisableEp */
/** \brief Enable Endpoint */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_UDP_DisableEp( AT91PS_UDP pUDP,    /* \arg pointer to a UDP controller */
                                   अचिह्नित पूर्णाङ्क flag ) /* \arg endpoints to be enabled */
{
    pUDP->UDP_GLBSTATE &= ~( flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_SetState */
/** \brief Set UDP Device state */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_UDP_समुच्चयः_State( AT91PS_UDP pUDP,    /* \arg pointer to a UDP controller */
                                  अचिह्नित पूर्णाङ्क flag ) /* \arg new UDP address */
{
    pUDP->UDP_GLBSTATE &= ~( AT91C_UDP_FADDEN | AT91C_UDP_CONFG );
    pUDP->UDP_GLBSTATE |= flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_GetState */
/** \brief return UDP Device state */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_UDP_GetState( /* \return the UDP device state */
    AT91PS_UDP pUDP )                     /* \arg pointer to a UDP controller */
{
    प्रत्यागम( pUDP->UDP_GLBSTATE & ( AT91C_UDP_FADDEN | AT91C_UDP_CONFG ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_ResetEp */
/** \brief Reset UDP endpoint */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_UDP_ResetEp( /* \return the UDP device state */
    AT91PS_UDP pUDP,             /* \arg pointer to a UDP controller */
    अचिह्नित पूर्णाङ्क flag )          /* \arg Endpoints to be reset */
{
    pUDP->UDP_RSTEP = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_EpStall */
/** \brief Endpoint will STALL requests */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_UDP_EpStall( AT91PS_UDP pUDP,         /* \arg pointer to a UDP controller */
                                 अचिह्नित वर्ण endpoint ) /* \arg endpoint number */
{
    pUDP->UDP_CSR[ endpoint ] |= AT91C_UDP_FORCESTALL;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_EpWrite */
/** \brief Write value in the DPR */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_UDP_EpWrite( AT91PS_UDP pUDP,        /* \arg pointer to a UDP controller */
                                 अचिह्नित वर्ण endpoint, /* \arg endpoint number */
                                 अचिह्नित वर्ण मानम् )   /* \arg value to be written in the DPR */
{
    pUDP->UDP_FDR[ endpoint ] = मानम्;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_EpRead */
/** \brief Return value from the DPR */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_UDP_EpRead( AT91PS_UDP pUDP,         /* \arg pointer to a UDP controller */
                                        अचिह्नित वर्ण endpoint ) /* \arg endpoint number */
{
    प्रत्यागम pUDP->UDP_FDR[ endpoint ];
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_EpEndOfWr */
/** \brief Notify the UDP that values in DPR are ready to be sent */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_UDP_Ep_अन्तः_सम्बन्धि_Wr( AT91PS_UDP pUDP,         /* \arg pointer to a UDP controller */
                                   अचिह्नित वर्ण endpoint ) /* \arg endpoint number */
{
    pUDP->UDP_CSR[ endpoint ] |= AT91C_UDP_TXPKTRDY;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_EpClear */
/** \brief Clear flag in the endpoint CSR register */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_UDP_EpClear( AT91PS_UDP pUDP,        /* \arg pointer to a UDP controller */
                                 अचिह्नित वर्ण endpoint, /* \arg endpoint number */
                                 अचिह्नित पूर्णाङ्क flag )     /* \arg flag to be cleared */
{
    pUDP->UDP_CSR[ endpoint ] &= ~( flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_EpSet */
/** \brief Set flag in the endpoint CSR register */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91_F_UDP_Ep_समुच्चयः( AT91PS_UDP pUDP,        /* \arg pointer to a UDP controller */
                               अचिह्नित वर्ण endpoint, /* \arg endpoint number */
                               अचिह्नित पूर्णाङ्क flag )     /* \arg flag to be cleared */
{
    pUDP->UDP_CSR[ endpoint ] |= flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_EpStatus */
/** \brief Return the endpoint CSR register */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_UDP_Ep_स्थितिः( AT91PS_UDP pUDP,         /* \arg pointer to a UDP controller */
                                          अचिह्नित वर्ण endpoint ) /* \arg endpoint number */
{
    प्रत्यागम pUDP->UDP_CSR[ endpoint ];
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_GetInterruptMaskStatus */
/** \brief Return UDP Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_UDP_Get_व्यवधानम्_आवरणम्_स्थितिः( /* \return UDP Interrupt Mask Status */
    AT91PS_UDP pUdp )                                   /* \arg  pointer to a UDP controller */
{
    प्रत्यागम pUdp->UDP_IMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_IsInterruptMasked */
/** \brief Test if UDP Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline पूर्णाङ्क AT91_F_UDP_Is_व्यवधानम्_Masked( AT91PS_UDP pUdp,    /* \arg  pointer to a UDP controller */
                                          अचिह्नित पूर्णाङ्क flag ) /* \arg  flag to be tested */
{
    प्रत्यागम( AT91_F_UDP_Get_व्यवधानम्_आवरणम्_स्थितिः( pUdp ) & flag );
}

/* *****************************************************************************
*               SOFTWARE API FOR AIC
***************************************************************************** */
#परिभाषय AT91C_AIC_BRANCH_OPCODE    ( ( शून्य ( * )() ) 0xE51FFF20 ) /* ldr, pc, [pc, #-&F20] */

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_ConfigureIt */
/** \brief Interrupt Handler Initialization */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_AIC_ConfigureIt( AT91PS_AIC pAic,                /* \arg pointer to the AIC registers */
                                             अचिह्नित पूर्णाङ्क irq_id,            /* \arg interrupt number to initialize */
                                             अचिह्नित पूर्णाङ्क प्राथमिकता,          /* \arg priority to give to the interrupt */
                                             अचिह्नित पूर्णाङ्क src_type,          /* \arg activation and sense of activation */
                                             शून्य ( * newHandler )( शून्य ) ) /* \arg address of the interrupt handler */
{
    अचिह्नित पूर्णाङ्क oldHandler;
    अचिह्नित पूर्णाङ्क आवरणम्;

    oldHandler = pAic->AIC_SVR[ irq_id ];

    आवरणम् = 0x1 << irq_id;
    /** Disable the interrupt on the interrupt controller */
    pAic->AIC_IDCR = आवरणम्;
    /** Save the interrupt handler routine pointer and the interrupt priority */
    pAic->AIC_SVR[ irq_id ] = ( अचिह्नित पूर्णाङ्क ) newHandler;
    /** Store the Source Mode Register */
    pAic->AIC_SMR[ irq_id ] = src_type | प्राथमिकता;
    /** Clear the interrupt on the interrupt controller */
    pAic->AIC_ICCR = आवरणम्;

    प्रत्यागम oldHandler;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_EnableIt */
/** \brief Enable corresponding IT number */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_AIC_EnableIt( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                  अचिह्नित पूर्णाङ्क irq_id ) /* \arg interrupt number to initialize */
{
    /** Enable the interrupt on the interrupt controller */
    pAic->AIC_IECR = 0x1 << irq_id;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_DisableIt */
/** \brief Disable corresponding IT number */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_AIC_DisableIt( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                   अचिह्नित पूर्णाङ्क irq_id ) /* \arg interrupt number to initialize */
{
    अचिह्नित पूर्णाङ्क आवरणम् = 0x1 << irq_id;

    /** Disable the interrupt on the interrupt controller */
    pAic->AIC_IDCR = आवरणम्;
    /** Clear the interrupt on the Interrupt Controller ( if one is pending ) */
    pAic->AIC_ICCR = आवरणम्;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_ClearIt */
/** \brief Clear corresponding IT number */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_AIC_ClearIt( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                 अचिह्नित पूर्णाङ्क irq_id ) /* \arg interrupt number to initialize */
{
    /** Clear the interrupt on the Interrupt Controller ( if one is pending ) */
    pAic->AIC_ICCR = ( 0x1 << irq_id );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_AcknowledgeIt */
/** \brief Acknowledge corresponding IT number */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_AIC_AcknowledgeIt( AT91PS_AIC pAic ) /* \arg pointer to the AIC registers */
{
    pAic->AIC_EOICR = pAic->AIC_EOICR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_SetExceptionVector */
/** \brief Configure vector handler */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_AIC_समुच्चयः_Exception_सदिशम्( अचिह्नित पूर्णाङ्क * p_सदिशम्, /* \arg pointer to the AIC registers */
                                                    शून्य ( * Handler )() )  /* \arg Interrupt Handler */
{
    अचिह्नित पूर्णाङ्क old_सदिशम् = *p_सदिशम्;

    यदि( ( अचिह्नित पूर्णाङ्क ) Handler == ( अचिह्नित पूर्णाङ्क ) AT91C_AIC_BRANCH_OPCODE )
    {
        *p_सदिशम् = ( अचिह्नित पूर्णाङ्क ) AT91C_AIC_BRANCH_OPCODE;
    }
    अन्यथा
    {
        *p_सदिशम् = ( ( ( ( ( अचिह्नित पूर्णाङ्क ) Handler ) - ( ( अचिह्नित पूर्णाङ्क ) p_सदिशम् ) - 0x8 ) >> 2 ) & 0x00FFFFFF ) | 0xEA000000;
    }

    प्रत्यागम old_सदिशम्;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_Trig */
/** \brief Trig an IT */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_AIC_Trig( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                              अचिह्नित पूर्णाङ्क irq_id ) /* \arg interrupt number */
{
    pAic->AIC_ISCR = ( 0x1 << irq_id );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_IsActive */
/** \brief Test if an IT is active */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91_F_AIC_Is_सक्रिय( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                          अचिह्नित पूर्णाङ्क irq_id ) /* \arg Interrupt Number */
{
    प्रत्यागम( pAic->AIC_ISR & ( 0x1 << irq_id ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_IsPending */
/** \brief Test if an IT is pending */
/**---------------------------------------------------------------------------- */
__inline अचिह्नित पूर्णाङ्क AT91F_AIC_IsPending( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                           अचिह्नित पूर्णाङ्क irq_id ) /* \arg Interrupt Number */
{
    प्रत्यागम( pAic->AIC_IPR & ( 0x1 << irq_id ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_Open */
/** \brief Set exception vectors and AIC registers to default values */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_AIC_Open( AT91PS_AIC pAic,              /* \arg pointer to the AIC registers */
                              शून्य ( * IrqHandler )(),      /* \arg Default IRQ vector exception */
                              शून्य ( * FiqHandler )(),      /* \arg Default FIQ vector exception */
                              शून्य ( * DefaultHandler )(),  /* \arg Default Handler set in ISR */
                              शून्य ( * SpuriousHandler )(), /* \arg Default Spurious Handler */
                              अचिह्नित पूर्णाङ्क protect_बहुलकम् )    /* \arg Debug Control Register */
{
    पूर्णाङ्क i;

    /* Disable all interrupts and set IVR to the default handler */
    प्रति( i = 0; i < 32; ++i )
    {
        AT91F_AIC_DisableIt( pAic, i );
        AT91F_AIC_ConfigureIt( pAic, i, AT91_C_AIC_प्राक्_निम्नतमम्, AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE, DefaultHandler );
    }

    /* Set the IRQ exception vector */
    AT91_F_AIC_समुच्चयः_Exception_सदिशम्( ( अचिह्नित पूर्णाङ्क * ) 0x18, IrqHandler );
    /* Set the Fast Interrupt exception vector */
    AT91_F_AIC_समुच्चयः_Exception_सदिशम्( ( अचिह्नित पूर्णाङ्क * ) 0x1C, FiqHandler );

    pAic->AIC_SPU = ( अचिह्नित पूर्णाङ्क ) SpuriousHandler;
    pAic->AIC_DCR = protect_बहुलकम्;
}
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_MC_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  MC */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_MC_CfgPMC( शून्य )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_आधारः_PMC, /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) 1 << AT91C_ID_SYS ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_DBGU_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  DBGU */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_DBGU_CfgPMC( शून्य )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_आधारः_PMC, /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) 1 << AT91C_ID_SYS ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_DBGU_CfgPIO */
/** \brief Configure PIO controllers to drive DBGU signals */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_DBGU_CfgPIO( शून्य )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_आधारः_PIOA,                     /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA10_DTXD ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA9_DRXD ), /* Peripheral A */
        0 );                                 /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWMC_CH3_CfgPIO */
/** \brief Configure PIO controllers to drive PWMC_CH3 signals */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PWMC_CH3_CfgPIO( शून्य )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_आधारः_PIOA,                       /* PIO controller base address */
        0,                                     /* Peripheral A */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA14_PWM3 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA7_PWM3 ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWMC_CH2_CfgPIO */
/** \brief Configure PIO controllers to drive PWMC_CH2 signals */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PWMC_CH2_CfgPIO( शून्य )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_आधारः_PIOA,                        /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA2_PWM2 ),    /* Peripheral A */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA25_PWM2 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA13_PWM2 ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWMC_CH1_CfgPIO */
/** \brief Configure PIO controllers to drive PWMC_CH1 signals */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PWMC_CH1_CfgPIO( शून्य )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_आधारः_PIOA,                        /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA1_PWM1 ),    /* Peripheral A */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA24_PWM1 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA12_PWM1 ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWMC_CH0_CfgPIO */
/** \brief Configure PIO controllers to drive PWMC_CH0 signals */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PWMC_CH0_CfgPIO( शून्य )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_आधारः_PIOA,                        /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA0_PWM0 ),    /* Peripheral A */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA23_PWM0 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA11_PWM0 ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  SSC */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_SSC_CfgPMC( शून्य )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_आधारः_PMC, /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) 1 << AT91C_ID_SSC ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_CfgPIO */
/** \brief Configure PIO controllers to drive SSC signals */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_SSC_CfgPIO( शून्य )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_आधारः_PIOA, /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA17_TD ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA15_TF ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA19_RK ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA18_RD ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA20_RF ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA16_TK ), /* Peripheral A */
        0 );                                /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  SPI */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_SPI_CfgPMC( शून्य )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_आधारः_PMC, /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) 1 << AT91C_ID_SPI ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_CfgPIO */
/** \brief Configure PIO controllers to drive SPI signals */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_SPI_CfgPIO( शून्य )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_आधारः_PIOA, /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA11_NPCS0 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA13_MOSI ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA31_NPCS1 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA12_MISO ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA14_SPCK ), /* Peripheral A */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA9_NPCS1 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA30_NPCS2 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA10_NPCS2 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA22_NPCS3 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA3_NPCS3 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA5_NPCS3 ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWMC_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  PWMC */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PWMC_CfgPMC( शून्य )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_आधारः_PMC, /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) 1 << AT91C_ID_PWMC ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TC2_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  TC2 */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_TC2_CfgPMC( शून्य )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_आधारः_PMC, /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) 1 << AT91C_ID_TC2 ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TC2_CfgPIO */
/** \brief Configure PIO controllers to drive TC2 signals */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_TC2_CfgPIO( शून्य )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_आधारः_PIOA, /* PIO controller base address */
        0,               /* Peripheral A */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA26_TIOA2 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA27_TIOB2 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA29_TCLK2 ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TC1_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  TC1 */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_TC1_CfgPMC( शून्य )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_आधारः_PMC, /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) 1 << AT91C_ID_TC1 ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TC1_CfgPIO */
/** \brief Configure PIO controllers to drive TC1 signals */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_TC1_CfgPIO( शून्य )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_आधारः_PIOA, /* PIO controller base address */
        0,               /* Peripheral A */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA15_TIOA1 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA16_TIOB1 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA28_TCLK1 ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TC0_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  TC0 */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_TC0_CfgPMC( शून्य )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_आधारः_PMC, /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) 1 << AT91C_ID_TC0 ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TC0_CfgPIO */
/** \brief Configure PIO controllers to drive TC0 signals */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_TC0_CfgPIO( शून्य )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_आधारः_PIOA, /* PIO controller base address */
        0,               /* Peripheral A */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA0_TIOA0 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA1_TIOB0 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA4_TCLK0 ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  PMC */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PMC_CfgPMC( शून्य )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_आधारः_PMC, /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) 1 << AT91C_ID_SYS ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_CfgPIO */
/** \brief Configure PIO controllers to drive PMC signals */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PMC_CfgPIO( शून्य )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_आधारः_PIOA, /* PIO controller base address */
        0,               /* Peripheral A */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA17_PCK1 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA21_PCK1 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA31_PCK2 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA18_PCK2 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA6_PCK0 ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  ADC */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_ADC_CfgPMC( शून्य )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_आधारः_PMC, /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) 1 << AT91C_ID_ADC ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_CfgPIO */
/** \brief Configure PIO controllers to drive ADC signals */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_ADC_CfgPIO( शून्य )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_आधारः_PIOA,                        /* PIO controller base address */
        0,                                      /* Peripheral A */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA8_ADTRG ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIOA_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  PIOA */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_PIOA_CfgPMC( शून्य )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_आधारः_PMC, /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) 1 << AT91C_ID_PIOA ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TWI_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  TWI */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_TWI_CfgPMC( शून्य )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_आधारः_PMC, /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) 1 << AT91C_ID_TWI ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TWI_CfgPIO */
/** \brief Configure PIO controllers to drive TWI signals */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_TWI_CfgPIO( शून्य )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_आधारः_PIOA,                     /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA3_TWD ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA4_TWCK ), /* Peripheral A */
        0 );                                 /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US1_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  US1 */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_US1_CfgPMC( शून्य )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_आधारः_PMC, /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) 1 << AT91C_ID_US1 ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US1_CfgPIO */
/** \brief Configure PIO controllers to drive US1 signals */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_US1_CfgPIO( शून्य )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_आधारः_PIOA, /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA21_RXD1 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA27_DTR1 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA26_DCD1 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA22_TXD1 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA24_RTS1 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA23_SCK1 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA28_DSR1 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA29_RI1 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA25_CTS1 ), /* Peripheral A */
        0 );                                  /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US0_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  US0 */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_US0_CfgPMC( शून्य )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_आधारः_PMC, /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) 1 << AT91C_ID_US0 ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US0_CfgPIO */
/** \brief Configure PIO controllers to drive US0 signals */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_US0_CfgPIO( शून्य )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_आधारः_PIOA, /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA5_RXD0 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA6_TXD0 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA7_RTS0 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA8_CTS0 ),   /* Peripheral A */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA2_SCK0 ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  UDP */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_UDP_CfgPMC( शून्य )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_आधारः_PMC, /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) 1 << AT91C_ID_UDP ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  AIC */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_AIC_CfgPMC( शून्य )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_आधारः_PMC, /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) 1 << AT91C_ID_IRQ0 ) |
        ( ( अचिह्नित पूर्णाङ्क ) 1 << AT91C_ID_FIQ ) |
        ( ( अचिह्नित पूर्णाङ्क ) 1 << AT91C_ID_IRQ1 ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_CfgPIO */
/** \brief Configure PIO controllers to drive AIC signals */
/**---------------------------------------------------------------------------- */
__inline शून्य AT91F_AIC_CfgPIO( शून्य )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_आधारः_PIOA,                       /* PIO controller base address */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA30_IRQ1 ),  /* Peripheral A */
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA20_IRQ0 ) |
        ( ( अचिह्नित पूर्णाङ्क ) AT91C_PA19_FIQ ) ); /* Peripheral B */
}

#यदि_अन्तः // lib_AT91SAM7S64_H
