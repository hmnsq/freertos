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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ lib_AT91SAM7S64_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ lib_AT91SAM7S64_H

/* *****************************************************************************
*               SOFTWARE API FOR MC
***************************************************************************** */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AT91_C_MC_CORRECT_ਕੁੰਜੀ    ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) 0x5A << 24 ) /* (MC) Correct Protect Key */

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_MC_Remap */
/** \brief Make Remap */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_MC_Remap( ਖਾਲੀ ) /* */
{
    AT91PS_MC pMC = ( AT91PS_MC ) AT91_C_ਅਧਾਰ_MC;

    pMC->MC_RCR = AT91C_MC_RCB;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_MC_EFC_CfgModeReg */
/** \brief Configure the EFC Mode Register of the MC controller */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_MC_EFC_Cfg_ਬਹੁਲਕ_Reg( AT91PS_MC pMC,      /* pointer to a MC controller */
                                       ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਬਹੁਲਕ_2 ) /* mode register */
{
    /* Write to the FMR register */
    pMC->MC_FMR = ਬਹੁਲਕ_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_MC_EFC_GetModeReg */
/** \brief Return MC EFC Mode Register */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_MC_EFC_Get_ਬਹੁਲਕ_Reg( AT91PS_MC pMC ) /* pointer to a MC controller */
{
    ਵਾਪਸ pMC->MC_FMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_MC_EFC_ComputeFMCN */
/** \brief Return MC EFC Mode Register */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91F_MC_EFC_ComputeFMCN( ਪੂਰਨ master_clock ) /* master clock in Hz */
{
    ਵਾਪਸ( master_clock / 1000000 + 2 );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_MC_EFC_PerformCmd */
/** \brief Perform EFC Command */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_MC_EFC_PerformCmd( AT91PS_MC pMC, /* pointer to a MC controller */
                                       ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ transfer_cmd )
{
    pMC->MC_FCR = transfer_cmd;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_MC_EFC_GetStatus */
/** \brief Return MC EFC Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_MC_EFC_Get_ਸਥਿਤੀ( AT91PS_MC pMC ) /* pointer to a MC controller */
{
    ਵਾਪਸ pMC->MC_FSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_MC_EFC_IsInterruptMasked */
/** \brief Test if EFC MC Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_MC_EFC_Is_ਰੁਕਾਵਟ_Masked( AT91PS_MC pMC,      /* \arg  pointer to a MC controller */
                                                      ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_MC_EFC_Get_ਬਹੁਲਕ_Reg( pMC ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_MC_EFC_IsInterruptSet */
/** \brief Test if EFC MC Interrupt is Set */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_MC_EFC_Is_ਰੁਕਾਵਟ_ਸੈੱਟ( AT91PS_MC pMC,      /* \arg  pointer to a MC controller */
                                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_MC_EFC_Get_ਸਥਿਤੀ( pMC ) & flag );
}

/* *****************************************************************************
*               SOFTWARE API FOR PDC
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_SetNextRx */
/** \brief Set the next receive transfer descriptor */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_PDC_ਸੈੱਟ_ਅਗਲਾ_Rx( AT91PS_PDC pPDC,     /* \arg pointer to a PDC controller */
                                   ਅੱਖਰ * ਪਤਾ_2,      /* \arg address to the next block to be received */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਬਾਈਟਾਂ_2 ) /* \arg number of bytes to be received */
{
    pPDC->PDC_RNPR = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) ਪਤਾ_2;
    pPDC->PDC_RNCR = ਬਾਈਟਾਂ_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_SetNextTx */
/** \brief Set the next transmit transfer descriptor */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_PDC_ਸੈੱਟ_ਅਗਲਾ_Tx( AT91PS_PDC pPDC,     /* \arg pointer to a PDC controller */
                                   ਅੱਖਰ * ਪਤਾ_2,      /* \arg address to the next block to be transmitted */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਬਾਈਟਾਂ_2 ) /* \arg number of bytes to be transmitted */
{
    pPDC->PDC_TNPR = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) ਪਤਾ_2;
    pPDC->PDC_TNCR = ਬਾਈਟਾਂ_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_SetRx */
/** \brief Set the receive transfer descriptor */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_PDC_ਸੈੱਟ_Rx( AT91PS_PDC pPDC,     /* \arg pointer to a PDC controller */
                               ਅੱਖਰ * ਪਤਾ_2,      /* \arg address to the next block to be received */
                               ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਬਾਈਟਾਂ_2 ) /* \arg number of bytes to be received */
{
    pPDC->PDC_RPR = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) ਪਤਾ_2;
    pPDC->PDC_RCR = ਬਾਈਟਾਂ_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_SetTx */
/** \brief Set the transmit transfer descriptor */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_PDC_ਸੈੱਟ_Tx( AT91PS_PDC pPDC,     /* \arg pointer to a PDC controller */
                               ਅੱਖਰ * ਪਤਾ_2,      /* \arg address to the next block to be transmitted */
                               ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਬਾਈਟਾਂ_2 ) /* \arg number of bytes to be transmitted */
{
    pPDC->PDC_TPR = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) ਪਤਾ_2;
    pPDC->PDC_TCR = ਬਾਈਟਾਂ_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_EnableTx */
/** \brief Enable transmit */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PDC_EnableTx( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
{
    pPDC->PDC_PTCR = AT91C_PDC_TXTEN;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_EnableRx */
/** \brief Enable receive */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PDC_EnableRx( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
{
    pPDC->PDC_PTCR = AT91C_PDC_RXTEN;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_DisableTx */
/** \brief Disable transmit */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PDC_DisableTx( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
{
    pPDC->PDC_PTCR = AT91C_PDC_TXTDIS;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_DisableRx */
/** \brief Disable receive */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PDC_DisableRx( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
{
    pPDC->PDC_PTCR = AT91C_PDC_RXTDIS;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_IsTxEmpty */
/** \brief Test if the current transfer descriptor has been sent */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91_F_PDC_Is_Tx_ਖਾਲੀ_ਥਾਵਾਂ( /* \return return 1 if transfer is complete */
    AT91PS_PDC pPDC )             /* \arg pointer to a PDC controller */
{
    ਵਾਪਸ !( pPDC->PDC_TCR );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_IsNextTxEmpty */
/** \brief Test if the next transfer descriptor has been moved to the current td */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91_F_PDC_Is_ਅਗਲਾ_Tx_ਖਾਲੀ_ਥਾਵਾਂ( /* \return return 1 if transfer is complete */
    AT91PS_PDC pPDC )                 /* \arg pointer to a PDC controller */
{
    ਵਾਪਸ !( pPDC->PDC_TNCR );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_IsRxEmpty */
/** \brief Test if the current transfer descriptor has been filled */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91_F_PDC_Is_Rx_ਖਾਲੀ_ਥਾਵਾਂ( /* \return return 1 if transfer is complete */
    AT91PS_PDC pPDC )             /* \arg pointer to a PDC controller */
{
    ਵਾਪਸ !( pPDC->PDC_RCR );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_IsNextRxEmpty */
/** \brief Test if the next transfer descriptor has been moved to the current td */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91_F_PDC_Is_ਅਗਲਾ_Rx_ਖਾਲੀ_ਥਾਵਾਂ( /* \return return 1 if transfer is complete */
    AT91PS_PDC pPDC )                 /* \arg pointer to a PDC controller */
{
    ਵਾਪਸ !( pPDC->PDC_RNCR );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_Open */
/** \brief Open PDC: disable TX and RX reset transfer descriptors, re-enable RX and TX */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PDC_Open( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
{
    /** Disable the RX and TX PDC transfer requests */
    AT91F_PDC_DisableRx( pPDC );
    AT91F_PDC_DisableTx( pPDC );

    /** Reset all Counter register Next buffer first */
    AT91_F_PDC_ਸੈੱਟ_ਅਗਲਾ_Tx( pPDC, ( ਅੱਖਰ * ) 0, 0 );
    AT91_F_PDC_ਸੈੱਟ_ਅਗਲਾ_Rx( pPDC, ( ਅੱਖਰ * ) 0, 0 );
    AT91_F_PDC_ਸੈੱਟ_Tx( pPDC, ( ਅੱਖਰ * ) 0, 0 );
    AT91_F_PDC_ਸੈੱਟ_Rx( pPDC, ( ਅੱਖਰ * ) 0, 0 );

    /** Enable the RX and TX PDC transfer requests */
    AT91F_PDC_EnableRx( pPDC );
    AT91F_PDC_EnableTx( pPDC );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_Close */
/** \brief Close PDC: disable TX and RX reset transfer descriptors */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PDC_Close( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
{
    /** Disable the RX and TX PDC transfer requests */
    AT91F_PDC_DisableRx( pPDC );
    AT91F_PDC_DisableTx( pPDC );

    /** Reset all Counter register Next buffer first */
    AT91_F_PDC_ਸੈੱਟ_ਅਗਲਾ_Tx( pPDC, ( ਅੱਖਰ * ) 0, 0 );
    AT91_F_PDC_ਸੈੱਟ_ਅਗਲਾ_Rx( pPDC, ( ਅੱਖਰ * ) 0, 0 );
    AT91_F_PDC_ਸੈੱਟ_Tx( pPDC, ( ਅੱਖਰ * ) 0, 0 );
    AT91_F_PDC_ਸੈੱਟ_Rx( pPDC, ( ਅੱਖਰ * ) 0, 0 );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_SendFrame */
/** \brief Close PDC: disable TX and RX reset transfer descriptors */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_PDC_Send_ਚੌਖਟਾ( AT91PS_PDC pPDC,
                                           ਅੱਖਰ * p_ਬਫਰ,
                                           ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ sz_ਬਫਰ,
                                           ਅੱਖਰ * p_ਅਗਲਾ_ਬਫਰ,
                                           ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ sz_ਅਗਲਾ_ਬਫਰ )
{
    ਜੇ( AT91_F_PDC_Is_Tx_ਖਾਲੀ_ਥਾਵਾਂ( pPDC ) )
    {
        /** Buffer and next buffer can be initialized */
        AT91_F_PDC_ਸੈੱਟ_Tx( pPDC, p_ਬਫਰ, sz_ਬਫਰ );
        AT91_F_PDC_ਸੈੱਟ_ਅਗਲਾ_Tx( pPDC, p_ਅਗਲਾ_ਬਫਰ, sz_ਅਗਲਾ_ਬਫਰ );
        ਵਾਪਸ 2;
    }
    ਨਹੀਂਤਾਂ ਜੇ( AT91_F_PDC_Is_ਅਗਲਾ_Tx_ਖਾਲੀ_ਥਾਵਾਂ( pPDC ) )
    {
        /** Only one buffer can be initialized */
        AT91_F_PDC_ਸੈੱਟ_ਅਗਲਾ_Tx( pPDC, p_ਬਫਰ, sz_ਬਫਰ );
        ਵਾਪਸ 1;
    }
    ਨਹੀਂਤਾਂ
    {
        /** All buffer are in use... */
        ਵਾਪਸ 0;
    }
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_ReceiveFrame */
/** \brief Close PDC: disable TX and RX reset transfer descriptors */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_PDC_Receive_ਚੌਖਟਾ( AT91PS_PDC pPDC,
                                              ਅੱਖਰ * p_ਬਫਰ,
                                              ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ sz_ਬਫਰ,
                                              ਅੱਖਰ * p_ਅਗਲਾ_ਬਫਰ,
                                              ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ sz_ਅਗਲਾ_ਬਫਰ )
{
    ਜੇ( AT91_F_PDC_Is_Rx_ਖਾਲੀ_ਥਾਵਾਂ( pPDC ) )
    {
        /** Buffer and next buffer can be initialized */
        AT91_F_PDC_ਸੈੱਟ_Rx( pPDC, p_ਬਫਰ, sz_ਬਫਰ );
        AT91_F_PDC_ਸੈੱਟ_ਅਗਲਾ_Rx( pPDC, p_ਅਗਲਾ_ਬਫਰ, sz_ਅਗਲਾ_ਬਫਰ );
        ਵਾਪਸ 2;
    }
    ਨਹੀਂਤਾਂ ਜੇ( AT91_F_PDC_Is_ਅਗਲਾ_Rx_ਖਾਲੀ_ਥਾਵਾਂ( pPDC ) )
    {
        /** Only one buffer can be initialized */
        AT91_F_PDC_ਸੈੱਟ_ਅਗਲਾ_Rx( pPDC, p_ਬਫਰ, sz_ਬਫਰ );
        ਵਾਪਸ 1;
    }
    ਨਹੀਂਤਾਂ
    {
        /** All buffer are in use... */
        ਵਾਪਸ 0;
    }
}

/* *****************************************************************************
*               SOFTWARE API FOR DBGU
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_DBGU_InterruptEnable */
/** \brief Enable DBGU Interrupt */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_DBGU_ਰੁਕਾਵਟ_Enable( AT91PS_DBGU pDbgu,  /* \arg  pointer to a DBGU controller */
                                          ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  dbgu interrupt to be enabled */
{
    pDbgu->DBGU_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_DBGU_InterruptDisable */
/** \brief Disable DBGU Interrupt */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_DBGU_ਰੁਕਾਵਟ_Disable( AT91PS_DBGU pDbgu,  /* \arg  pointer to a DBGU controller */
                                           ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  dbgu interrupt to be disabled */
{
    pDbgu->DBGU_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_DBGU_GetInterruptMaskStatus */
/** \brief Return DBGU Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_DBGU_Get_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸਥਿਤੀ( /* \return DBGU Interrupt Mask Status */
    AT91PS_DBGU pDbgu )                                  /* \arg  pointer to a DBGU controller */
{
    ਵਾਪਸ pDbgu->DBGU_IMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_DBGU_IsInterruptMasked */
/** \brief Test if DBGU Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91_F_DBGU_Is_ਰੁਕਾਵਟ_Masked( AT91PS_DBGU pDbgu,  /* \arg  pointer to a DBGU controller */
                                           ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_DBGU_Get_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸਥਿਤੀ( pDbgu ) & flag );
}

/* *****************************************************************************
*               SOFTWARE API FOR SSC
***************************************************************************** */
/** Define the standard I2S mode configuration */

/** Configuration to set in the SSC Transmit Clock Mode Register */
/** Parameters :  nb_bit_by_slot : 8, 16 or 32 bits */
/**               nb_slot_by_frame : number of channels */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AT91C_I2S_ASY_MASTER_TX_SETTING( nb_ਦੋਆਧਾਰੀ_ਅੰਕ_by_ਥਾਂ, nb_ਥਾਂ_by_ਚੌਖਟਾ ) \
    ( +                                                                     \
      AT91C_SSC_CKS_DIV +                                                   \
      AT91C_SSC_CKO_CONTINUOUS +                                            \
      AT91C_SSC_CKG_NONE +                                                  \
      AT91_C_SSC_ਸ਼ੁਰੂ_FALL_RF +                                             \
      AT91C_SSC_STTOUT +                                                    \
      ( ( 1 << 16 ) & AT91C_SSC_STTDLY ) +                                  \
      ( ( ( ( nb_ਦੋਆਧਾਰੀ_ਅੰਕ_by_ਥਾਂ * nb_ਥਾਂ_by_ਚੌਖਟਾ ) / 2 ) - 1 ) << 24 ) )


/** Configuration to set in the SSC Transmit Frame Mode Register */
/** Parameters : nb_bit_by_slot : 8, 16 or 32 bits */
/**              nb_slot_by_frame : number of channels */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AT91_C_I2_S_ASY_TX_ਚੌਖਟਾ_SETTING( nb_ਦੋਆਧਾਰੀ_ਅੰਕ_by_ਥਾਂ, nb_ਥਾਂ_by_ਚੌਖਟਾ ) \
    ( +                                                                    \
      ( nb_ਦੋਆਧਾਰੀ_ਅੰਕ_by_ਥਾਂ - 1 ) +                                             \
      AT91C_SSC_MSBF +                                                     \
      ( ( ( nb_ਥਾਂ_by_ਚੌਖਟਾ - 1 ) << 8 ) & AT91C_SSC_DATNB ) +            \
      ( ( ( nb_ਦੋਆਧਾਰੀ_ਅੰਕ_by_ਥਾਂ - 1 ) << 16 ) & AT91C_SSC_FSLEN ) +             \
      AT91C_SSC_FSOS_NEGATIVE )


/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_SetBaudrate */
/** \brief Set the baudrate according to the CPU clock */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_SSC_ਸੈੱਟ_Baudrate( AT91PS_SSC pSSC,        /* \arg pointer to a SSC controller */
                                     ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ mainClock, /* \arg peripheral clock */
                                     ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਰਫਤਾਰ_2 )    /* \arg SSC baudrate */
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ baud_ਮੁੱਲ;

    /** Define the baud rate divisor register */
    ਜੇ( ਰਫਤਾਰ_2 == 0 )
    {
        baud_ਮੁੱਲ = 0;
    }
    ਨਹੀਂਤਾਂ
    {
        baud_ਮੁੱਲ = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) ( mainClock * 10 ) / ( 2 * ਰਫਤਾਰ_2 );

        ਜੇ( ( baud_ਮੁੱਲ % 10 ) >= 5 )
        {
            baud_ਮੁੱਲ = ( baud_ਮੁੱਲ / 10 ) + 1;
        }
        ਨਹੀਂਤਾਂ
        {
            baud_ਮੁੱਲ /= 10;
        }
    }

    pSSC->SSC_CMR = baud_ਮੁੱਲ;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_Configure */
/** \brief Configure SSC */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_SSC_Configure( AT91PS_SSC pSSC,         /* \arg pointer to a SSC controller */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ syst_clock, /* \arg System Clock Frequency */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ baud_ਦਰ,  /* \arg Expected Baud Rate Frequency */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ clock_rx,   /* \arg Receiver Clock Parameters */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਬਹੁਲਕ_rx,    /* \arg mode Register to be programmed */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ clock_tx,   /* \arg Transmitter Clock Parameters */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਬਹੁਲਕ_tx )   /* \arg mode Register to be programmed */
{
    /** Disable interrupts */
    pSSC->SSC_IDR = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) -1;

    /** Reset receiver and transmitter */
    pSSC->SSC_CR = AT91C_SSC_SWRST | AT91C_SSC_RXDIS | AT91C_SSC_TXDIS;

    /** Define the Clock Mode Register */
    AT91_F_SSC_ਸੈੱਟ_Baudrate( pSSC, syst_clock, baud_ਦਰ );

    /** Write the Receive Clock Mode Register */
    pSSC->SSC_RCMR = clock_rx;

    /** Write the Transmit Clock Mode Register */
    pSSC->SSC_TCMR = clock_tx;

    /** Write the Receive Frame Mode Register */
    pSSC->SSC_RFMR = ਬਹੁਲਕ_rx;

    /** Write the Transmit Frame Mode Register */
    pSSC->SSC_TFMR = ਬਹੁਲਕ_tx;

    /** Clear Transmit and Receive Counters */
    AT91F_PDC_Open( ( AT91PS_PDC ) &( pSSC->SSC_RPR ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_EnableRx */
/** \brief Enable receiving data */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_SSC_EnableRx( AT91PS_SSC pSSC ) /* \arg pointer to a SSC controller */
{
    /** Enable receiver */
    pSSC->SSC_CR = AT91C_SSC_RXEN;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_DisableRx */
/** \brief Disable receiving data */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_SSC_DisableRx( AT91PS_SSC pSSC ) /* \arg pointer to a SSC controller */
{
    /** Disable receiver */
    pSSC->SSC_CR = AT91C_SSC_RXDIS;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_EnableTx */
/** \brief Enable sending data */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_SSC_EnableTx( AT91PS_SSC pSSC ) /* \arg pointer to a SSC controller */
{
    /** Enable  transmitter */
    pSSC->SSC_CR = AT91C_SSC_TXEN;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_DisableTx */
/** \brief Disable sending data */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_SSC_DisableTx( AT91PS_SSC pSSC ) /* \arg pointer to a SSC controller */
{
    /** Disable  transmitter */
    pSSC->SSC_CR = AT91C_SSC_TXDIS;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_EnableIt */
/** \brief Enable SSC IT */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_SSC_EnableIt( AT91PS_SSC pSSC,    /* \arg pointer to a SSC controller */
                                  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg IT to be enabled */
{
    /** Write to the IER register */
    pSSC->SSC_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_DisableIt */
/** \brief Disable SSC IT */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_SSC_DisableIt( AT91PS_SSC pSSC,    /* \arg pointer to a SSC controller */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg IT to be disabled */
{
    /** Write to the IDR register */
    pSSC->SSC_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_ReceiveFrame */
/** \brief Return 2 if PDC has been initialized with Buffer and Next Buffer, 1 if PDC has been initialized with Next Buffer, 0 if PDC is busy */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_SSC_Receive_ਚੌਖਟਾ( AT91PS_SSC pSSC,
                                              ਅੱਖਰ * p_ਬਫਰ,
                                              ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ sz_ਬਫਰ,
                                              ਅੱਖਰ * p_ਅਗਲਾ_ਬਫਰ,
                                              ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ sz_ਅਗਲਾ_ਬਫਰ )
{
    ਵਾਪਸ AT91_F_PDC_Receive_ਚੌਖਟਾ(
        ( AT91PS_PDC ) &( pSSC->SSC_RPR ),
        p_ਬਫਰ,
        sz_ਬਫਰ,
        p_ਅਗਲਾ_ਬਫਰ,
        sz_ਅਗਲਾ_ਬਫਰ );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_SendFrame */
/** \brief Return 2 if PDC has been initialized with Buffer and Next Buffer, 1 if PDC has been initialized with Next Buffer, 0 if PDC is busy */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_SSC_Send_ਚੌਖਟਾ( AT91PS_SSC pSSC,
                                           ਅੱਖਰ * p_ਬਫਰ,
                                           ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ sz_ਬਫਰ,
                                           ਅੱਖਰ * p_ਅਗਲਾ_ਬਫਰ,
                                           ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ sz_ਅਗਲਾ_ਬਫਰ )
{
    ਵਾਪਸ AT91_F_PDC_Send_ਚੌਖਟਾ(
        ( AT91PS_PDC ) &( pSSC->SSC_RPR ),
        p_ਬਫਰ,
        sz_ਬਫਰ,
        p_ਅਗਲਾ_ਬਫਰ,
        sz_ਅਗਲਾ_ਬਫਰ );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_GetInterruptMaskStatus */
/** \brief Return SSC Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_SSC_Get_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸਥਿਤੀ( /* \return SSC Interrupt Mask Status */
    AT91PS_SSC pSsc )                                   /* \arg  pointer to a SSC controller */
{
    ਵਾਪਸ pSsc->SSC_IMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_IsInterruptMasked */
/** \brief Test if SSC Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91_F_SSC_Is_ਰੁਕਾਵਟ_Masked( AT91PS_SSC pSsc,    /* \arg  pointer to a SSC controller */
                                          ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_SSC_Get_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸਥਿਤੀ( pSsc ) & flag );
}

/* *****************************************************************************
*               SOFTWARE API FOR SPI
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_Open */
/** \brief Open a SPI Port */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91F_SPI_Open( ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ null ) /* \arg */
{
    /* NOT DEFINED AT THIS MOMENT */
    ਵਾਪਸ( 0 );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_CfgCs */
/** \brief Configure SPI chip select register */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_SPI_CfgCs( AT91PS_SPI pSPI, /* pointer to a SPI controller */
                               ਪੂਰਨ cs,          /* SPI cs number (0 to 3) */
                               ਪੂਰਨ val )        /*  chip select register */
{
    /** Write to the CSR register */
    *( pSPI->SPI_CSR + cs ) = val;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_EnableIt */
/** \brief Enable SPI interrupt */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_SPI_EnableIt( AT91PS_SPI pSPI,    /* pointer to a SPI controller */
                                  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* IT to be enabled */
{
    /** Write to the IER register */
    pSPI->SPI_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_DisableIt */
/** \brief Disable SPI interrupt */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_SPI_DisableIt( AT91PS_SPI pSPI,    /* pointer to a SPI controller */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* IT to be disabled */
{
    /** Write to the IDR register */
    pSPI->SPI_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_Reset */
/** \brief Reset the SPI controller */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_SPI_Reset( AT91PS_SPI pSPI /* pointer to a SPI controller */
                               )
{
    /** Write to the CR register */
    pSPI->SPI_CR = AT91C_SPI_SWRST;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_Enable */
/** \brief Enable the SPI controller */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_SPI_Enable( AT91PS_SPI pSPI /* pointer to a SPI controller */
                                )
{
    /** Write to the CR register */
    pSPI->SPI_CR = AT91C_SPI_SPIEN;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_Disable */
/** \brief Disable the SPI controller */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_SPI_Disable( AT91PS_SPI pSPI /* pointer to a SPI controller */
                                 )
{
    /** Write to the CR register */
    pSPI->SPI_CR = AT91C_SPI_SPIDIS;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_CfgMode */
/** \brief Enable the SPI controller */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_SPI_Cfg_ਬਹੁਲਕ( AT91PS_SPI pSPI, /* pointer to a SPI controller */
                                 ਪੂਰਨ ਬਹੁਲਕ_2 )       /* mode register */
{
    /** Write to the MR register */
    pSPI->SPI_MR = ਬਹੁਲਕ_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_CfgPCS */
/** \brief Switch to the correct PCS of SPI Mode Register : Fixed Peripheral Selected */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_SPI_CfgPCS( AT91PS_SPI pSPI,  /* pointer to a SPI controller */
                                ਅੱਖਰ PCS_Device ) /* PCS of the Device */
{
    /** Write to the MR register */
    pSPI->SPI_MR &= 0xFFF0FFFF;
    pSPI->SPI_MR |= ( ( PCS_Device << 16 ) & AT91C_SPI_PCS );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_ReceiveFrame */
/** \brief Return 2 if PDC has been initialized with Buffer and Next Buffer, 1 if PDC has been initialized with Next Buffer, 0 if PDC is busy */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_SPI_Receive_ਚੌਖਟਾ( AT91PS_SPI pSPI,
                                              ਅੱਖਰ * p_ਬਫਰ,
                                              ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ sz_ਬਫਰ,
                                              ਅੱਖਰ * p_ਅਗਲਾ_ਬਫਰ,
                                              ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ sz_ਅਗਲਾ_ਬਫਰ )
{
    ਵਾਪਸ AT91_F_PDC_Receive_ਚੌਖਟਾ(
        ( AT91PS_PDC ) &( pSPI->SPI_RPR ),
        p_ਬਫਰ,
        sz_ਬਫਰ,
        p_ਅਗਲਾ_ਬਫਰ,
        sz_ਅਗਲਾ_ਬਫਰ );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_SendFrame */
/** \brief Return 2 if PDC has been initialized with Buffer and Next Buffer, 1 if PDC has been initialized with Next Buffer, 0 if PDC is bSPIy */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_SPI_Send_ਚੌਖਟਾ( AT91PS_SPI pSPI,
                                           ਅੱਖਰ * p_ਬਫਰ,
                                           ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ sz_ਬਫਰ,
                                           ਅੱਖਰ * p_ਅਗਲਾ_ਬਫਰ,
                                           ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ sz_ਅਗਲਾ_ਬਫਰ )
{
    ਵਾਪਸ AT91_F_PDC_Send_ਚੌਖਟਾ(
        ( AT91PS_PDC ) &( pSPI->SPI_RPR ),
        p_ਬਫਰ,
        sz_ਬਫਰ,
        p_ਅਗਲਾ_ਬਫਰ,
        sz_ਅਗਲਾ_ਬਫਰ );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_Close */
/** \brief Close SPI: disable IT disable transfer, close PDC */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_SPI_Close( AT91PS_SPI pSPI ) /* \arg pointer to a SPI controller */
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
__inline ਖਾਲੀ AT91F_SPI_PutChar( AT91PS_SPI pSPI,
                                 ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ character,
                                 ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ cs_ਸੰਖਿਆ )
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਮੁੱਲ_for_cs;

    ਮੁੱਲ_for_cs = ( ~( 1 << cs_ਸੰਖਿਆ ) ) & 0xF; /*Place a zero among a 4 ONEs number */
    pSPI->SPI_TDR = ( character & 0xFFFF ) | ( ਮੁੱਲ_for_cs << 16 );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_GetChar */
/** \brief Receive a character,does not check if a character is available */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91F_SPI_GetChar( ਅਚਲ AT91PS_SPI pSPI )
{
    ਵਾਪਸ( ( pSPI->SPI_RDR ) & 0xFFFF );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_GetInterruptMaskStatus */
/** \brief Return SPI Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_SPI_Get_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸਥਿਤੀ( /* \return SPI Interrupt Mask Status */
    AT91PS_SPI pSpi )                                   /* \arg  pointer to a SPI controller */
{
    ਵਾਪਸ pSpi->SPI_IMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_IsInterruptMasked */
/** \brief Test if SPI Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91_F_SPI_Is_ਰੁਕਾਵਟ_Masked( AT91PS_SPI pSpi,    /* \arg  pointer to a SPI controller */
                                          ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_SPI_Get_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸਥਿਤੀ( pSpi ) & flag );
}

/* *****************************************************************************
*               SOFTWARE API FOR PWMC
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWM_GetStatus */
/** \brief Return PWM Interrupt Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_PWMC_Get_ਸਥਿਤੀ( /* \return PWM Interrupt Status */
    AT91PS_PWMC pPWM )                      /* pointer to a PWM controller */
{
    ਵਾਪਸ pPWM->PWMC_SR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWM_InterruptEnable */
/** \brief Enable PWM Interrupt */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_PWMC_ਰੁਕਾਵਟ_Enable( AT91PS_PWMC pPwm,   /* \arg  pointer to a PWM controller */
                                          ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  PWM interrupt to be enabled */
{
    pPwm->PWMC_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWM_InterruptDisable */
/** \brief Disable PWM Interrupt */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_PWMC_ਰੁਕਾਵਟ_Disable( AT91PS_PWMC pPwm,   /* \arg  pointer to a PWM controller */
                                           ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  PWM interrupt to be disabled */
{
    pPwm->PWMC_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWM_GetInterruptMaskStatus */
/** \brief Return PWM Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_PWMC_Get_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸਥਿਤੀ( /* \return PWM Interrupt Mask Status */
    AT91PS_PWMC pPwm )                                   /* \arg  pointer to a PWM controller */
{
    ਵਾਪਸ pPwm->PWMC_IMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWM_IsInterruptMasked */
/** \brief Test if PWM Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_PWMC_Is_ਰੁਕਾਵਟ_Masked( AT91PS_PWMC pPWM,   /* \arg  pointer to a PWM controller */
                                                    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_PWMC_Get_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸਥਿਤੀ( pPWM ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWM_IsStatusSet */
/** \brief Test if PWM Interrupt is Set */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_PWMC_Is_ਸਥਿਤੀ_ਸੈੱਟ( AT91PS_PWMC pPWM,   /* \arg  pointer to a PWM controller */
                                              ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_PWMC_Get_ਸਥਿਤੀ( pPWM ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWM_CfgChannel */
/** \brief Test if PWM Interrupt is Set */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PWMC_CfgChannel( AT91PS_PWMC pPWM,       /* \arg  pointer to a PWM controller */
                                     ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ channelId, /* \arg PWM channel ID */
                                     ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਬਹੁਲਕ_2,      /* \arg  PWM mode */
                                     ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ period,    /* \arg PWM period */
                                     ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ duty )     /* \arg PWM duty cycle */
{
    pPWM->PWMC_CH[ channelId ].PWMC_CMR = ਬਹੁਲਕ_2;
    pPWM->PWMC_CH[ channelId ].PWMC_CDTYR = duty;
    pPWM->PWMC_CH[ channelId ].PWMC_CPRDR = period;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWM_StartChannel */
/** \brief Enable channel */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_PWMC_ਸ਼ੁਰੂ_Channel( AT91PS_PWMC pPWM,   /* \arg  pointer to a PWM controller */
                                       ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  Channels IDs to be enabled */
{
    pPWM->PWMC_ENA = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWM_StopChannel */
/** \brief Disable channel */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PWMC_StopChannel( AT91PS_PWMC pPWM,   /* \arg  pointer to a PWM controller */
                                      ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  Channels IDs to be enabled */
{
    pPWM->PWMC_DIS = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWM_UpdateChannel */
/** \brief Update Period or Duty Cycle */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PWMC_UpdateChannel( AT91PS_PWMC pPWM,       /* \arg  pointer to a PWM controller */
                                        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ channelId, /* \arg PWM channel ID */
                                        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ update )   /* \arg  Channels IDs to be enabled */
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
__inline ਖਾਲੀ AT91_F_TC_ਰੁਕਾਵਟ_Enable( AT91PS_TC pTc,      /* \arg  pointer to a TC controller */
                                        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  TC interrupt to be enabled */
{
    pTc->TC_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TC_InterruptDisable */
/** \brief Disable TC Interrupt */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_TC_ਰੁਕਾਵਟ_Disable( AT91PS_TC pTc,      /* \arg  pointer to a TC controller */
                                         ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  TC interrupt to be disabled */
{
    pTc->TC_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TC_GetInterruptMaskStatus */
/** \brief Return TC Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_TC_Get_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸਥਿਤੀ( /* \return TC Interrupt Mask Status */
    AT91PS_TC pTc )                                    /* \arg  pointer to a TC controller */
{
    ਵਾਪਸ pTc->TC_IMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TC_IsInterruptMasked */
/** \brief Test if TC Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91_F_TC_Is_ਰੁਕਾਵਟ_Masked( AT91PS_TC pTc,      /* \arg  pointer to a TC controller */
                                         ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_TC_Get_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸਥਿਤੀ( pTc ) & flag );
}

/* *****************************************************************************
*               SOFTWARE API FOR PMC
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_CfgSysClkEnableReg */
/** \brief Configure the System Clock Enable Register of the PMC controller */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PMC_CfgSysClkEnableReg( AT91PS_PMC pPMC, /* \arg pointer to PMC controller */
                                            ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਬਹੁਲਕ_2 )
{
    /** Write to the SCER register */
    pPMC->PMC_SCER = ਬਹੁਲਕ_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_CfgSysClkDisableReg */
/** \brief Configure the System Clock Disable Register of the PMC controller */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PMC_CfgSysClkDisableReg( AT91PS_PMC pPMC, /* \arg pointer to PMC controller */
                                             ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਬਹੁਲਕ_2 )
{
    /** Write to the SCDR register */
    pPMC->PMC_SCDR = ਬਹੁਲਕ_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_GetSysClkStatusReg */
/** \brief Return the System Clock Status Register of the PMC controller */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_PMC_Get_Sys_Clk_ਸਥਿਤੀ_Reg( AT91PS_PMC pPMC /* pointer to a CAN controller */
                                                    )
{
    ਵਾਪਸ pPMC->PMC_SCSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_EnablePeriphClock */
/** \brief Enable peripheral clock */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PMC_EnablePeriphClock( AT91PS_PMC pPMC,         /* \arg pointer to PMC controller */
                                           ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ periphIds ) /* \arg IDs of peripherals to enable */
{
    pPMC->PMC_PCER = periphIds;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_DisablePeriphClock */
/** \brief Disable peripheral clock */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PMC_DisablePeriphClock( AT91PS_PMC pPMC,         /* \arg pointer to PMC controller */
                                            ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ periphIds ) /* \arg IDs of peripherals to enable */
{
    pPMC->PMC_PCDR = periphIds;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_GetPeriphClock */
/** \brief Get peripheral clock status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91F_PMC_GetPeriphClock( AT91PS_PMC pPMC ) /* \arg pointer to PMC controller */
{
    ਵਾਪਸ pPMC->PMC_PCSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_CfgMainOscillatorReg */
/** \brief Cfg the main oscillator */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_CKGR_CfgMainOscillatorReg( AT91PS_CKGR pCKGR, /* \arg pointer to CKGR controller */
                                               ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਬਹੁਲਕ_2 )
{
    pCKGR->CKGR_MOR = ਬਹੁਲਕ_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_GetMainOscillatorReg */
/** \brief Cfg the main oscillator */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91F_CKGR_GetMainOscillatorReg( AT91PS_CKGR pCKGR ) /* \arg pointer to CKGR controller */
{
    ਵਾਪਸ pCKGR->CKGR_MOR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_EnableMainOscillator */
/** \brief Enable the main oscillator */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_CKGR_EnableMainOscillator( AT91PS_CKGR pCKGR ) /* \arg pointer to CKGR controller */
{
    pCKGR->CKGR_MOR |= AT91C_CKGR_MOSCEN;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_DisableMainOscillator */
/** \brief Disable the main oscillator */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_CKGR_DisableMainOscillator( AT91PS_CKGR pCKGR ) /* \arg pointer to CKGR controller */
{
    pCKGR->CKGR_MOR &= ~AT91C_CKGR_MOSCEN;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_CfgMainOscStartUpTime */
/** \brief Cfg MORE Register according to the main osc startup time */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_CKGR_Cfg_Main_Osc_ਸ਼ੁਰੂ_ਉੱਪਰ_ਸਮਾਂ( AT91PS_CKGR pCKGR,         /* \arg pointer to CKGR controller */
                                                ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ startup_ਸਮਾਂ, /* \arg main osc startup time in microsecond (us) */
                                                ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ slowClock )   /* \arg slowClock in Hz */
{
    pCKGR->CKGR_MOR &= ~AT91C_CKGR_OSCOUNT;
    pCKGR->CKGR_MOR |= ( ( slowClock * startup_ਸਮਾਂ ) / ( 8 * 1000000 ) ) << 8;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_GetMainClockFreqReg */
/** \brief Cfg the main oscillator */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91F_CKGR_GetMainClockFreqReg( AT91PS_CKGR pCKGR ) /* \arg pointer to CKGR controller */
{
    ਵਾਪਸ pCKGR->CKGR_MCFR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_GetMainClock */
/** \brief Return Main clock in Hz */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91F_CKGR_GetMainClock( AT91PS_CKGR pCKGR,       /* \arg pointer to CKGR controller */
                                               ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ slowClock ) /* \arg slowClock in Hz */
{
    ਵਾਪਸ ( ( pCKGR->CKGR_MCFR & AT91C_CKGR_MAINF ) * slowClock ) >> 4;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_CfgMCKReg */
/** \brief Cfg Master Clock Register */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PMC_CfgMCKReg( AT91PS_PMC pPMC, /* \arg pointer to PMC controller */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਬਹੁਲਕ_2 )
{
    pPMC->PMC_MCKR = ਬਹੁਲਕ_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_GetMCKReg */
/** \brief Return Master Clock Register */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91F_PMC_GetMCKReg( AT91PS_PMC pPMC ) /* \arg pointer to PMC controller */
{
    ਵਾਪਸ pPMC->PMC_MCKR;
}

/**------------------------------------------------------------------------------ */
/** \fn    AT91F_PMC_GetMasterClock */
/** \brief Return master clock in Hz which corresponds to processor clock for ARM7 */
/**------------------------------------------------------------------------------ */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91F_PMC_GetMasterClock( AT91PS_PMC pPMC,         /* \arg pointer to PMC controller */
                                                AT91PS_CKGR pCKGR,       /* \arg pointer to CKGR controller */
                                                ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ slowClock ) /* \arg slowClock in Hz */
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ reg = pPMC->PMC_MCKR;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ prescaler = ( 1 << ( ( reg & AT91C_PMC_PRES ) >> 2 ) );
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ pllDivider, pllMultiplier;

    ਚੋਣ( reg & AT91C_PMC_CSS )
    {
        ਹਾਲਤ AT91C_PMC_CSS_SLOW_CLK: /* Slow clock selected */
            ਵਾਪਸ slowClock / prescaler;

        ਹਾਲਤ AT91C_PMC_CSS_MAIN_CLK: /* Main clock is selected */
            ਵਾਪਸ AT91F_CKGR_GetMainClock( pCKGR, slowClock ) / prescaler;

        ਹਾਲਤ AT91C_PMC_CSS_PLL_CLK: /* PLLB clock is selected */
            reg = pCKGR->CKGR_PLLR;
            pllDivider = ( reg & AT91C_CKGR_DIV );
            pllMultiplier = ( ( reg & AT91C_CKGR_MUL ) >> 16 ) + 1;
            ਵਾਪਸ AT91F_CKGR_GetMainClock( pCKGR, slowClock ) / pllDivider * pllMultiplier / prescaler;
    }

    ਵਾਪਸ 0;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_EnablePCK */
/** \brief Enable peripheral clock */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PMC_EnablePCK( AT91PS_PMC pPMC,  /* \arg pointer to PMC controller */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ pck, /* \arg Peripheral clock identifier 0 .. 7 */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਬਹੁਲਕ_2 )
{
    pPMC->PMC_PCKR[ pck ] = ਬਹੁਲਕ_2;
    pPMC->PMC_SCER = ( 1 << pck ) << 8;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_DisablePCK */
/** \brief Enable peripheral clock */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PMC_DisablePCK( AT91PS_PMC pPMC,   /* \arg pointer to PMC controller */
                                    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ pck ) /* \arg Peripheral clock identifier 0 .. 7 */
{
    pPMC->PMC_SCDR = ( 1 << pck ) << 8;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_EnableIt */
/** \brief Enable PMC interrupt */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PMC_EnableIt( AT91PS_PMC pPMC,    /* pointer to a PMC controller */
                                  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* IT to be enabled */
{
    /** Write to the IER register */
    pPMC->PMC_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_DisableIt */
/** \brief Disable PMC interrupt */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PMC_DisableIt( AT91PS_PMC pPMC,    /* pointer to a PMC controller */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* IT to be disabled */
{
    /** Write to the IDR register */
    pPMC->PMC_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_GetStatus */
/** \brief Return PMC Interrupt Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_PMC_Get_ਸਥਿਤੀ( /* \return PMC Interrupt Status */
    AT91PS_PMC pPMC )                      /* pointer to a PMC controller */
{
    ਵਾਪਸ pPMC->PMC_SR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_GetInterruptMaskStatus */
/** \brief Return PMC Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_PMC_Get_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸਥਿਤੀ( /* \return PMC Interrupt Mask Status */
    AT91PS_PMC pPMC )                                   /* pointer to a PMC controller */
{
    ਵਾਪਸ pPMC->PMC_IMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_IsInterruptMasked */
/** \brief Test if PMC Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_PMC_Is_ਰੁਕਾਵਟ_Masked( AT91PS_PMC pPMC,    /* \arg  pointer to a PMC controller */
                                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_PMC_Get_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸਥਿਤੀ( pPMC ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_IsStatusSet */
/** \brief Test if PMC Status is Set */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_PMC_Is_ਸਥਿਤੀ_ਸੈੱਟ( AT91PS_PMC pPMC,    /* \arg  pointer to a PMC controller */
                                             ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_PMC_Get_ਸਥਿਤੀ( pPMC ) & flag );
} /* *****************************************************************************
  *              SOFTWARE API FOR ADC
  ***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_EnableIt */
/** \brief Enable ADC interrupt */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_ADC_EnableIt( AT91PS_ADC pADC,    /* pointer to a ADC controller */
                                  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* IT to be enabled */
{
    /** Write to the IER register */
    pADC->ADC_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_DisableIt */
/** \brief Disable ADC interrupt */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_ADC_DisableIt( AT91PS_ADC pADC,    /* pointer to a ADC controller */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* IT to be disabled */
{
    /** Write to the IDR register */
    pADC->ADC_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetStatus */
/** \brief Return ADC Interrupt Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_ADC_Get_ਸਥਿਤੀ( /* \return ADC Interrupt Status */
    AT91PS_ADC pADC )                      /* pointer to a ADC controller */
{
    ਵਾਪਸ pADC->ADC_SR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetInterruptMaskStatus */
/** \brief Return ADC Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_ADC_Get_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸਥਿਤੀ( /* \return ADC Interrupt Mask Status */
    AT91PS_ADC pADC )                                   /* pointer to a ADC controller */
{
    ਵਾਪਸ pADC->ADC_IMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_IsInterruptMasked */
/** \brief Test if ADC Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_ADC_Is_ਰੁਕਾਵਟ_Masked( AT91PS_ADC pADC,    /* \arg  pointer to a ADC controller */
                                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_ADC_Get_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸਥਿਤੀ( pADC ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_IsStatusSet */
/** \brief Test if ADC Status is Set */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_ADC_Is_ਸਥਿਤੀ_ਸੈੱਟ( AT91PS_ADC pADC,    /* \arg  pointer to a ADC controller */
                                             ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_ADC_Get_ਸਥਿਤੀ( pADC ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_CfgModeReg */
/** \brief Configure the Mode Register of the ADC controller */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_ADC_Cfg_ਬਹੁਲਕ_Reg( AT91PS_ADC pADC,    /* pointer to a ADC controller */
                                    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਬਹੁਲਕ_2 ) /* mode register */
{
    /** Write to the MR register */
    pADC->ADC_MR = ਬਹੁਲਕ_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetModeReg */
/** \brief Return the Mode Register of the ADC controller value */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_ADC_Get_ਬਹੁਲਕ_Reg( AT91PS_ADC pADC /* pointer to a ADC controller */
                                            )
{
    ਵਾਪਸ pADC->ADC_MR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_CfgTimings */
/** \brief Configure the different necessary timings of the ADC controller */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_ADC_CfgTimings( AT91PS_ADC pADC,                    /* pointer to a ADC controller */
                                    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ mck_clock,             /* in MHz */
                                    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ adc_clock,             /* in MHz */
                                    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ startup_ਸਮਾਂ,          /* in us */
                                    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ sample_and_hold_ਸਮਾਂ ) /* in ns */
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ prescal, startup, shtim;

    prescal = mck_clock / ( 2 * adc_clock ) - 1;
    startup = adc_clock * startup_ਸਮਾਂ / 8 - 1;
    shtim = adc_clock * sample_and_hold_ਸਮਾਂ / 1000 - 1;

    /** Write to the MR register */
    pADC->ADC_MR = ( ( prescal << 8 ) & AT91C_ADC_PRESCAL ) | ( ( startup << 16 ) & AT91C_ADC_STARTUP ) | ( ( shtim << 24 ) & AT91C_ADC_SHTIM );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_EnableChannel */
/** \brief Return ADC Timer Register Value */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_ADC_EnableChannel( AT91PS_ADC pADC,       /* pointer to a ADC controller */
                                       ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ channel ) /* mode register */
{
    /** Write to the CHER register */
    pADC->ADC_CHER = channel;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_DisableChannel */
/** \brief Return ADC Timer Register Value */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_ADC_DisableChannel( AT91PS_ADC pADC,       /* pointer to a ADC controller */
                                        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ channel ) /* mode register */
{
    /** Write to the CHDR register */
    pADC->ADC_CHDR = channel;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetChannelStatus */
/** \brief Return ADC Timer Register Value */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_ADC_Get_Channel_ਸਥਿਤੀ( AT91PS_ADC pADC /* pointer to a ADC controller */
                                                  )
{
    ਵਾਪਸ pADC->ADC_CHSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_StartConversion */
/** \brief Software request for a analog to digital conversion */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_ADC_ਸ਼ੁਰੂ_Conversion( AT91PS_ADC pADC /* pointer to a ADC controller */
                                         )
{
    pADC->ADC_CR = AT91_C_ADC_ਸ਼ੁਰੂ;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_SoftReset */
/** \brief Software reset */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_ADC_SoftReset( AT91PS_ADC pADC /* pointer to a ADC controller */
                                   )
{
    pADC->ADC_CR = AT91C_ADC_SWRST;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetLastConvertedData */
/** \brief Return the Last Converted Data */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_ADC_Get_ਆਖਰੀ_Converted_ਅੰਕੜੇ( AT91PS_ADC pADC /* pointer to a ADC controller */
                                                      )
{
    ਵਾਪਸ pADC->ADC_LCDR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetConvertedDataCH0 */
/** \brief Return the Channel 0 Converted Data */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_ADC_Get_Converted_ਅੰਕੜੇ_CH0( AT91PS_ADC pADC /* pointer to a ADC controller */
                                                     )
{
    ਵਾਪਸ pADC->ADC_CDR0;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetConvertedDataCH1 */
/** \brief Return the Channel 1 Converted Data */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_ADC_Get_Converted_ਅੰਕੜੇ_CH1( AT91PS_ADC pADC /* pointer to a ADC controller */
                                                     )
{
    ਵਾਪਸ pADC->ADC_CDR1;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetConvertedDataCH2 */
/** \brief Return the Channel 2 Converted Data */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_ADC_Get_Converted_ਅੰਕੜੇ_CH2( AT91PS_ADC pADC /* pointer to a ADC controller */
                                                     )
{
    ਵਾਪਸ pADC->ADC_CDR2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetConvertedDataCH3 */
/** \brief Return the Channel 3 Converted Data */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_ADC_Get_Converted_ਅੰਕੜੇ_CH3( AT91PS_ADC pADC /* pointer to a ADC controller */
                                                     )
{
    ਵਾਪਸ pADC->ADC_CDR3;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetConvertedDataCH4 */
/** \brief Return the Channel 4 Converted Data */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_ADC_Get_Converted_ਅੰਕੜੇ_CH4( AT91PS_ADC pADC /* pointer to a ADC controller */
                                                     )
{
    ਵਾਪਸ pADC->ADC_CDR4;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetConvertedDataCH5 */
/** \brief Return the Channel 5 Converted Data */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_ADC_Get_Converted_ਅੰਕੜੇ_CH5( AT91PS_ADC pADC /* pointer to a ADC controller */
                                                     )
{
    ਵਾਪਸ pADC->ADC_CDR5;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetConvertedDataCH6 */
/** \brief Return the Channel 6 Converted Data */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_ADC_Get_Converted_ਅੰਕੜੇ_CH6( AT91PS_ADC pADC /* pointer to a ADC controller */
                                                     )
{
    ਵਾਪਸ pADC->ADC_CDR6;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_GetConvertedDataCH7 */
/** \brief Return the Channel 7 Converted Data */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_ADC_Get_Converted_ਅੰਕੜੇ_CH7( AT91PS_ADC pADC /* pointer to a ADC controller */
                                                     )
{
    ਵਾਪਸ pADC->ADC_CDR7;
}

/* *****************************************************************************
*               SOFTWARE API FOR PIO
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgPeriph */
/** \brief Enable pins to be derived by peripheral */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PIO_CfgPeriph( AT91PS_PIO pPio,             /* \arg pointer to a PIO controller */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ periphAEnable,  /* \arg PERIPH A to enable */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ periphBEnable ) /* \arg PERIPH B to enable */

{
    pPio->PIO_ASR = periphAEnable;
    pPio->PIO_BSR = periphBEnable;
    pPio->PIO_PDR = ( periphAEnable | periphBEnable ); /* Set in Periph mode */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgOutput */
/** \brief Enable PIO in output mode */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PIO_CfgOutput( AT91PS_PIO pPio,         /* \arg pointer to a PIO controller */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ pioEnable ) /* \arg PIO to be enabled */
{
    pPio->PIO_ਪ੍ਰਤੀ = pioEnable;                              /* Set in PIO mode */
    pPio->PIO_OER = pioEnable;                              /* Configure in Output */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgInput */
/** \brief Enable PIO in input mode */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_PIO_Cfg_ਨਿਵੇਸ਼( AT91PS_PIO pPio,           /* \arg pointer to a PIO controller */
                                  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਨਿਵੇਸ਼_Enable ) /* \arg PIO to be enabled */
{
    /* Disable output */
    pPio->PIO_ODR = ਨਿਵੇਸ਼_Enable;
    pPio->PIO_ਪ੍ਰਤੀ = ਨਿਵੇਸ਼_Enable;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgOpendrain */
/** \brief Configure PIO in open drain */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PIO_CfgOpendrain( AT91PS_PIO pPio,              /* \arg pointer to a PIO controller */
                                      ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ multiDrvEnable ) /* \arg pio to be configured in open drain */
{
    /* Configure the multi-drive option */
    pPio->PIO_MDDR = ~multiDrvEnable;
    pPio->PIO_MDER = multiDrvEnable;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgPullup */
/** \brief Enable pullup on PIO */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PIO_CfgPullup( AT91PS_PIO pPio,            /* \arg pointer to a PIO controller */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ pullupEnable ) /* \arg enable pullup on PIO */
{
    /* Connect or not Pullup */
    pPio->PIO_PPUDR = ~pullupEnable;
    pPio->PIO_PPUER = pullupEnable;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgDirectDrive */
/** \brief Enable direct drive on PIO */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_PIO_Cfg_ਸਿੱਧਾ_Drive( AT91PS_PIO pPio,           /* \arg pointer to a PIO controller */
                                        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਸਿੱਧਾ_Drive ) /* \arg PIO to be configured with direct drive */

{
    /* Configure the Direct Drive */
    pPio->PIO_OWDR = ~ਸਿੱਧਾ_Drive;
    pPio->PIO_OWER = ਸਿੱਧਾ_Drive;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgInputFilter */
/** \brief Enable input filter on input PIO */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_PIO_Cfg_ਨਿਵੇਸ਼_Filter( AT91PS_PIO pPio,           /* \arg pointer to a PIO controller */
                                        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਨਿਵੇਸ਼_Filter ) /* \arg PIO to be configured with input filter */

{
    /* Configure the Direct Drive */
    pPio->PIO_IFDR = ~ਨਿਵੇਸ਼_Filter;
    pPio->PIO_IFER = ਨਿਵੇਸ਼_Filter;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetInput */
/** \brief Return PIO input value */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_PIO_Get_ਨਿਵੇਸ਼( /* \return PIO input */
    AT91PS_PIO pPio )                     /* \arg  pointer to a PIO controller */
{
    ਵਾਪਸ pPio->PIO_PDSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsInputSet */
/** \brief Test if PIO is input flag is active */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91_F_PIO_Is_ਨਿਵੇਸ਼_ਸੈੱਟ( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_PIO_Get_ਨਿਵੇਸ਼( pPio ) & flag );
}


/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_SetOutput */
/** \brief Set to 1 output PIO */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_PIO_ਸੈੱਟ_Output( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  output to be set */
{
    pPio->PIO_SODR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_ClearOutput */
/** \brief Set to 0 output PIO */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PIO_ClearOutput( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                     ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  output to be cleared */
{
    pPio->PIO_CODR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_ForceOutput */
/** \brief Force output when Direct drive option is enabled */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PIO_ForceOutput( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                     ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  output to be forced */
{
    pPio->PIO_ODSR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_Enable */
/** \brief Enable PIO */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PIO_Enable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  pio to be enabled */
{
    pPio->PIO_ਪ੍ਰਤੀ = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_Disable */
/** \brief Disable PIO */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PIO_Disable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                 ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  pio to be disabled */
{
    pPio->PIO_PDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetStatus */
/** \brief Return PIO Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_PIO_Get_ਸਥਿਤੀ( /* \return PIO Status */
    AT91PS_PIO pPio )                      /* \arg  pointer to a PIO controller */
{
    ਵਾਪਸ pPio->PIO_PSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsSet */
/** \brief Test if PIO is Set */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91_F_PIO_Is_ਸੈੱਟ( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                              ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_PIO_Get_ਸਥਿਤੀ( pPio ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_OutputEnable */
/** \brief Output Enable PIO */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PIO_OutputEnable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                      ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  pio output to be enabled */
{
    pPio->PIO_OER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_OutputDisable */
/** \brief Output Enable PIO */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PIO_OutputDisable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                       ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  pio output to be disabled */
{
    pPio->PIO_ODR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetOutputStatus */
/** \brief Return PIO Output Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_PIO_Get_Output_ਸਥਿਤੀ( /* \return PIO Output Status */
    AT91PS_PIO pPio )                            /* \arg  pointer to a PIO controller */
{
    ਵਾਪਸ pPio->PIO_OSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsOuputSet */
/** \brief Test if PIO Output is Set */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91_F_PIO_Is_Output_ਸੈੱਟ( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_PIO_Get_Output_ਸਥਿਤੀ( pPio ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_InputFilterEnable */
/** \brief Input Filter Enable PIO */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_PIO_ਨਿਵੇਸ਼_Filter_Enable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                           ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  pio input filter to be enabled */
{
    pPio->PIO_IFER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_InputFilterDisable */
/** \brief Input Filter Disable PIO */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_PIO_ਨਿਵੇਸ਼_Filter_Disable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                            ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  pio input filter to be disabled */
{
    pPio->PIO_IFDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetInputFilterStatus */
/** \brief Return PIO Input Filter Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_PIO_Get_ਨਿਵੇਸ਼_Filter_ਸਥਿਤੀ( /* \return PIO Input Filter Status */
    AT91PS_PIO pPio )                                 /* \arg  pointer to a PIO controller */
{
    ਵਾਪਸ pPio->PIO_IFSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsInputFilterSet */
/** \brief Test if PIO Input filter is Set */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91_F_PIO_Is_ਨਿਵੇਸ਼_Filter_ਸੈੱਟ( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                         ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_PIO_Get_ਨਿਵੇਸ਼_Filter_ਸਥਿਤੀ( pPio ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetOutputDataStatus */
/** \brief Return PIO Output Data Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_PIO_Get_Output_ਅੰਕੜੇ_ਸਥਿਤੀ( /* \return PIO Output Data Status */
    AT91PS_PIO pPio )                                /* \arg  pointer to a PIO controller */
{
    ਵਾਪਸ pPio->PIO_ODSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_InterruptEnable */
/** \brief Enable PIO Interrupt */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_PIO_ਰੁਕਾਵਟ_Enable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                         ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  pio interrupt to be enabled */
{
    pPio->PIO_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_InterruptDisable */
/** \brief Disable PIO Interrupt */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_PIO_ਰੁਕਾਵਟ_Disable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                          ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  pio interrupt to be disabled */
{
    pPio->PIO_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetInterruptMaskStatus */
/** \brief Return PIO Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_PIO_Get_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸਥਿਤੀ( /* \return PIO Interrupt Mask Status */
    AT91PS_PIO pPio )                                   /* \arg  pointer to a PIO controller */
{
    ਵਾਪਸ pPio->PIO_IMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetInterruptStatus */
/** \brief Return PIO Interrupt Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_PIO_Get_ਰੁਕਾਵਟ_ਸਥਿਤੀ( /* \return PIO Interrupt Status */
    AT91PS_PIO pPio )                               /* \arg  pointer to a PIO controller */
{
    ਵਾਪਸ pPio->PIO_ISR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsInterruptMasked */
/** \brief Test if PIO Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91_F_PIO_Is_ਰੁਕਾਵਟ_Masked( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                          ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_PIO_Get_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸਥਿਤੀ( pPio ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsInterruptSet */
/** \brief Test if PIO Interrupt is Set */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91_F_PIO_Is_ਰੁਕਾਵਟ_ਸੈੱਟ( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                       ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_PIO_Get_ਰੁਕਾਵਟ_ਸਥਿਤੀ( pPio ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_MultiDriverEnable */
/** \brief Multi Driver Enable PIO */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PIO_MultiDriverEnable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                           ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  pio to be enabled */
{
    pPio->PIO_MDER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_MultiDriverDisable */
/** \brief Multi Driver Disable PIO */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PIO_MultiDriverDisable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                            ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  pio to be disabled */
{
    pPio->PIO_MDDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetMultiDriverStatus */
/** \brief Return PIO Multi Driver Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_PIO_Get_Multi_Driver_ਸਥਿਤੀ( /* \return PIO Multi Driver Status */
    AT91PS_PIO pPio )                                 /* \arg  pointer to a PIO controller */
{
    ਵਾਪਸ pPio->PIO_MDSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsMultiDriverSet */
/** \brief Test if PIO MultiDriver is Set */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91_F_PIO_Is_Multi_Driver_ਸੈੱਟ( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                         ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_PIO_Get_Multi_Driver_ਸਥਿਤੀ( pPio ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_A_RegisterSelection */
/** \brief PIO A Register Selection */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_PIO_A_ਰਜਿਸਟਰ_Selection( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                             ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  pio A register selection */
{
    pPio->PIO_ASR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_B_RegisterSelection */
/** \brief PIO B Register Selection */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_PIO_B_ਰਜਿਸਟਰ_Selection( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                             ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  pio B register selection */
{
    pPio->PIO_BSR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_Get_AB_RegisterStatus */
/** \brief Return PIO Interrupt Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_PIO_Get_AB_ਰਜਿਸਟਰ_ਸਥਿਤੀ( /* \return PIO AB Register Status */
    AT91PS_PIO pPio )                                  /* \arg  pointer to a PIO controller */
{
    ਵਾਪਸ pPio->PIO_ABSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsAB_RegisterSet */
/** \brief Test if PIO AB Register is Set */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91_F_PIO_Is_AB_ਰਜਿਸਟਰ_ਸੈੱਟ( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                         ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_PIO_Get_AB_ਰਜਿਸਟਰ_ਸਥਿਤੀ( pPio ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_OutputWriteEnable */
/** \brief Output Write Enable PIO */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PIO_OutputWriteEnable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                           ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  pio output write to be enabled */
{
    pPio->PIO_OWER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_OutputWriteDisable */
/** \brief Output Write Disable PIO */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PIO_OutputWriteDisable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                            ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  pio output write to be disabled */
{
    pPio->PIO_OWDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetOutputWriteStatus */
/** \brief Return PIO Output Write Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_PIO_Get_Output_Write_ਸਥਿਤੀ( /* \return PIO Output Write Status */
    AT91PS_PIO pPio )                                 /* \arg  pointer to a PIO controller */
{
    ਵਾਪਸ pPio->PIO_OWSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsOutputWriteSet */
/** \brief Test if PIO OutputWrite is Set */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91_F_PIO_Is_Output_Write_ਸੈੱਟ( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                         ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_PIO_Get_Output_Write_ਸਥਿਤੀ( pPio ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetCfgPullup */
/** \brief Return PIO Configuration Pullup */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91F_PIO_GetCfgPullup( /* \return PIO Configuration Pullup */
    AT91PS_PIO pPio )                         /* \arg  pointer to a PIO controller */
{
    ਵਾਪਸ pPio->PIO_PPUSR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsOutputDataStatusSet */
/** \brief Test if PIO Output Data Status is Set */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91_F_PIO_Is_Output_ਅੰਕੜੇ_ਸਥਿਤੀ_ਸੈੱਟ( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                              ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_PIO_Get_Output_ਅੰਕੜੇ_ਸਥਿਤੀ( pPio ) & flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsCfgPullupStatusSet */
/** \brief Test if PIO Configuration Pullup Status is Set */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91_F_PIO_Is_Cfg_Pullup_ਸਥਿਤੀ_ਸੈੱਟ( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                             ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( ~AT91F_PIO_GetCfgPullup( pPio ) & flag );
}

/* *****************************************************************************
*               SOFTWARE API FOR TWI
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TWI_EnableIt */
/** \brief Enable TWI IT */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_TWI_EnableIt( AT91PS_TWI pTWI,    /* \arg pointer to a TWI controller */
                                  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg IT to be enabled */
{
    /** Write to the IER register */
    pTWI->TWI_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TWI_DisableIt */
/** \brief Disable TWI IT */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_TWI_DisableIt( AT91PS_TWI pTWI,    /* \arg pointer to a TWI controller */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg IT to be disabled */
{
    /** Write to the IDR register */
    pTWI->TWI_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TWI_Configure */
/** \brief Configure TWI in master mode */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_TWI_Configure( AT91PS_TWI pTWI ) /* \arg pointer to a TWI controller */
{
    /** Disable interrupts */
    pTWI->TWI_IDR = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) -1;

    /** Reset peripheral */
    pTWI->TWI_CR = AT91C_TWI_SWRST;

    /** Set Master mode */
    pTWI->TWI_CR = AT91C_TWI_MSEN | AT91C_TWI_SVDIS;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TWI_GetInterruptMaskStatus */
/** \brief Return TWI Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_TWI_Get_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸਥਿਤੀ( /* \return TWI Interrupt Mask Status */
    AT91PS_TWI pTwi )                                   /* \arg  pointer to a TWI controller */
{
    ਵਾਪਸ pTwi->TWI_IMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TWI_IsInterruptMasked */
/** \brief Test if TWI Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91_F_TWI_Is_ਰੁਕਾਵਟ_Masked( AT91PS_TWI pTwi,    /* \arg  pointer to a TWI controller */
                                          ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_TWI_Get_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸਥਿਤੀ( pTwi ) & flag );
}

/* *****************************************************************************
*               SOFTWARE API FOR USART
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_Baudrate */
/** \brief Calculate the baudrate */
/** Standard Asynchronous Mode : 8 bits , 1 stop , no parity */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AT91_C_US_ASYNC_ਬਹੁਲਕ    \
    ( AT91_C_US_USMODE_ਸਾਧਾਰਨ + \
      AT91_C_US_NBSTOP_1_ਦੋਆਧਾਰੀ_ਅੰਕ +  \
      AT91C_US_PAR_NONE +      \
      AT91_C_US_CHRL_8_ਬਿੱਟ +   \
      AT91C_US_CLKS_CLOCK )

/** Standard External Asynchronous Mode : 8 bits , 1 stop , no parity */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AT91_C_US_ASYNC_SCK_ਬਹੁਲਕ \
    ( AT91_C_US_USMODE_ਸਾਧਾਰਨ +  \
      AT91_C_US_NBSTOP_1_ਦੋਆਧਾਰੀ_ਅੰਕ +   \
      AT91C_US_PAR_NONE +       \
      AT91_C_US_CHRL_8_ਬਿੱਟ +    \
      AT91C_US_CLKS_EXT )

/** Standard Synchronous Mode : 8 bits , 1 stop , no parity */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AT91_C_US_SYNC_ਬਹੁਲਕ     \
    ( AT91C_US_SYNC +          \
      AT91_C_US_USMODE_ਸਾਧਾਰਨ + \
      AT91_C_US_NBSTOP_1_ਦੋਆਧਾਰੀ_ਅੰਕ +  \
      AT91C_US_PAR_NONE +      \
      AT91_C_US_CHRL_8_ਬਿੱਟ +   \
      AT91C_US_CLKS_CLOCK )

/** SCK used Label */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AT91_C_US_SCK_ਵਰਤਿਆ    ( AT91C_US_CKLO | AT91C_US_CLKS_EXT )

/** Standard ISO T=0 Mode : 8 bits , 1 stop , parity */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AT91_C_US_ISO_READER_ਬਹੁਲਕ  \
    ( AT91C_US_USMODE_ISO7816_0 + \
      AT91C_US_CLKS_CLOCK +       \
      AT91_C_US_NBSTOP_1_ਦੋਆਧਾਰੀ_ਅੰਕ +     \
      AT91C_US_PAR_EVEN +         \
      AT91_C_US_CHRL_8_ਬਿੱਟ +      \
      AT91C_US_CKLO +             \
      AT91C_US_OVER )

/** Standard IRDA mode */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AT91_C_US_ASYNC_IRDA_ਬਹੁਲਕ \
    ( AT91C_US_USMODE_IRDA +     \
      AT91_C_US_NBSTOP_1_ਦੋਆਧਾਰੀ_ਅੰਕ +    \
      AT91C_US_PAR_NONE +        \
      AT91_C_US_CHRL_8_ਬਿੱਟ +     \
      AT91C_US_CLKS_CLOCK )

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_Baudrate */
/** \brief Calculate baud_value according to the main clock and the baud rate */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91F_US_Baudrate( ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ main_clock, /* \arg peripheral clock */
                                         ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ baud_ਦਰ ) /* \arg UART baudrate */
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ baud_ਮੁੱਲ = ( ( main_clock * 10 ) / ( baud_ਦਰ * 16 ) );

    ਜੇ( ( baud_ਮੁੱਲ % 10 ) >= 5 )
    {
        baud_ਮੁੱਲ = ( baud_ਮੁੱਲ / 10 ) + 1;
    }
    ਨਹੀਂਤਾਂ
    {
        baud_ਮੁੱਲ /= 10;
    }

    ਵਾਪਸ baud_ਮੁੱਲ;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_SetBaudrate */
/** \brief Set the baudrate according to the CPU clock */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_US_ਸੈੱਟ_Baudrate( AT91PS_USART pUSART,    /* \arg pointer to a USART controller */
                                    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ mainClock, /* \arg peripheral clock */
                                    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਰਫਤਾਰ_2 )    /* \arg UART baudrate */
{
    /** Define the baud rate divisor register */
    pUSART->US_BRGR = AT91F_US_Baudrate( mainClock, ਰਫਤਾਰ_2 );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_SetTimeguard */
/** \brief Set USART timeguard */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_US_ਸੈੱਟ_Timeguard( AT91PS_USART pUSART,     /* \arg pointer to a USART controller */
                                     ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ timeguard ) /* \arg timeguard value */
{
    /** Write the Timeguard Register */
    pUSART->US_TTGR = timeguard;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_EnableIt */
/** \brief Enable USART IT */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_US_EnableIt( AT91PS_USART pUSART, /* \arg pointer to a USART controller */
                                 ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag )  /* \arg IT to be enabled */
{
    /** Write to the IER register */
    pUSART->US_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_DisableIt */
/** \brief Disable USART IT */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_US_DisableIt( AT91PS_USART pUSART, /* \arg pointer to a USART controller */
                                  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag )  /* \arg IT to be disabled */
{
    /** Write to the IER register */
    pUSART->US_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_Configure */
/** \brief Configure USART */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_US_Configure( AT91PS_USART pUSART,     /* \arg pointer to a USART controller */
                                  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ mainClock,  /* \arg peripheral clock */
                                  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਬਹੁਲਕ_2,       /* \arg mode Register to be programmed */
                                  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ baud_ਦਰ_2,   /* \arg baudrate to be programmed */
                                  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ timeguard ) /* \arg timeguard to be programmed */
{
    /** Disable interrupts */
    pUSART->US_IDR = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) -1;

    /** Reset receiver and transmitter */
    pUSART->US_CR = AT91C_US_RSTRX | AT91C_US_RSTTX | AT91C_US_RXDIS | AT91C_US_TXDIS;

    /** Define the baud rate divisor register */
    AT91_F_US_ਸੈੱਟ_Baudrate( pUSART, mainClock, baud_ਦਰ_2 );

    /** Write the Timeguard Register */
    AT91_F_US_ਸੈੱਟ_Timeguard( pUSART, timeguard );

    /** Clear Transmit and Receive Counters */
    AT91F_PDC_Open( ( AT91PS_PDC ) &( pUSART->US_RPR ) );

    /** Define the USART mode */
    pUSART->US_MR = ਬਹੁਲਕ_2;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_EnableRx */
/** \brief Enable receiving characters */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_US_EnableRx( AT91PS_USART pUSART ) /* \arg pointer to a USART controller */
{
    /** Enable receiver */
    pUSART->US_CR = AT91C_US_RXEN;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_EnableTx */
/** \brief Enable sending characters */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_US_EnableTx( AT91PS_USART pUSART ) /* \arg pointer to a USART controller */
{
    /** Enable  transmitter */
    pUSART->US_CR = AT91C_US_TXEN;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_ResetRx */
/** \brief Reset Receiver and re-enable it */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_US_ResetRx( AT91PS_USART pUSART ) /* \arg pointer to a USART controller */
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
__inline ਖਾਲੀ AT91F_US_ResetTx( AT91PS_USART pUSART ) /* \arg pointer to a USART controller */
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
__inline ਖਾਲੀ AT91F_US_DisableRx( AT91PS_USART pUSART ) /* \arg pointer to a USART controller */
{
    /** Disable receiver */
    pUSART->US_CR = AT91C_US_RXDIS;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_DisableTx */
/** \brief Disable Transmitter */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_US_DisableTx( AT91PS_USART pUSART ) /* \arg pointer to a USART controller */
{
    /** Disable transmitter */
    pUSART->US_CR = AT91C_US_TXDIS;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_Close */
/** \brief Close USART: disable IT disable receiver and transmitter, close PDC */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_US_Close( AT91PS_USART pUSART ) /* \arg pointer to a USART controller */
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
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91F_US_TxReady( AT91PS_USART pUSART ) /* \arg pointer to a USART controller */
{
    ਵਾਪਸ( pUSART->US_CSR & AT91C_US_TXRDY );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_RxReady */
/** \brief Return 1 if a character can be read in US_RHR */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91F_US_RxReady( AT91PS_USART pUSART ) /* \arg pointer to a USART controller */
{
    ਵਾਪਸ( pUSART->US_CSR & AT91C_US_RXRDY );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_Error */
/** \brief Return the error flag */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91F_US_Error( AT91PS_USART pUSART ) /* \arg pointer to a USART controller */
{
    ਵਾਪਸ( pUSART->US_CSR &
            ( AT91C_US_OVRE |    /* Overrun error */
              AT91_C_US_ਚੌਖਟਾ |   /* Framing error */
              AT91C_US_PARE ) ); /* Parity error */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_PutChar */
/** \brief Send a character,does not check if ready to send */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_US_PutChar( AT91PS_USART pUSART,
                                ਪੂਰਨ character )
{
    pUSART->US_THR = ( character & 0x1FF );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_GetChar */
/** \brief Receive a character,does not check if a character is available */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91F_US_GetChar( ਅਚਲ AT91PS_USART pUSART )
{
    ਵਾਪਸ( ( pUSART->US_RHR ) & 0x1FF );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_SendFrame */
/** \brief Return 2 if PDC has been initialized with Buffer and Next Buffer, 1 if PDC has been initialized with Next Buffer, 0 if PDC is busy */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_US_Send_ਚੌਖਟਾ( AT91PS_USART pUSART,
                                          ਅੱਖਰ * p_ਬਫਰ,
                                          ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ sz_ਬਫਰ,
                                          ਅੱਖਰ * p_ਅਗਲਾ_ਬਫਰ,
                                          ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ sz_ਅਗਲਾ_ਬਫਰ )
{
    ਵਾਪਸ AT91_F_PDC_Send_ਚੌਖਟਾ(
        ( AT91PS_PDC ) &( pUSART->US_RPR ),
        p_ਬਫਰ,
        sz_ਬਫਰ,
        p_ਅਗਲਾ_ਬਫਰ,
        sz_ਅਗਲਾ_ਬਫਰ );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_ReceiveFrame */
/** \brief Return 2 if PDC has been initialized with Buffer and Next Buffer, 1 if PDC has been initialized with Next Buffer, 0 if PDC is busy */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_US_Receive_ਚੌਖਟਾ( AT91PS_USART pUSART,
                                             ਅੱਖਰ * p_ਬਫਰ,
                                             ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ sz_ਬਫਰ,
                                             ਅੱਖਰ * p_ਅਗਲਾ_ਬਫਰ,
                                             ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ sz_ਅਗਲਾ_ਬਫਰ )
{
    ਵਾਪਸ AT91_F_PDC_Receive_ਚੌਖਟਾ(
        ( AT91PS_PDC ) &( pUSART->US_RPR ),
        p_ਬਫਰ,
        sz_ਬਫਰ,
        p_ਅਗਲਾ_ਬਫਰ,
        sz_ਅਗਲਾ_ਬਫਰ );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US_SetIrdaFilter */
/** \brief Set the value of IrDa filter register */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_US_ਸੈੱਟ_Irda_Filter( AT91PS_USART pUSART,
                                      ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਮੁੱਲ )
{
    pUSART->US_IF = ਮੁੱਲ;
}

/* *****************************************************************************
*               SOFTWARE API FOR UDP
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_EnableIt */
/** \brief Enable UDP IT */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_UDP_EnableIt( AT91PS_UDP pUDP,    /* \arg pointer to a UDP controller */
                                  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg IT to be enabled */
{
    /** Write to the IER register */
    pUDP->UDP_IER = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_DisableIt */
/** \brief Disable UDP IT */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_UDP_DisableIt( AT91PS_UDP pUDP,    /* \arg pointer to a UDP controller */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg IT to be disabled */
{
    /** Write to the IDR register */
    pUDP->UDP_IDR = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_SetAddress */
/** \brief Set UDP functional address */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_UDP_ਸੈੱਟ_ਪਤਾ( AT91PS_UDP pUDP,        /* \arg pointer to a UDP controller */
                                    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਪਤਾ_2 ) /* \arg new UDP address */
{
    pUDP->UDP_FADDR = ( AT91C_UDP_FEN | ਪਤਾ_2 );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_EnableEp */
/** \brief Enable Endpoint */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_UDP_EnableEp( AT91PS_UDP pUDP,    /* \arg pointer to a UDP controller */
                                  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg endpoints to be enabled */
{
    pUDP->UDP_GLBSTATE |= flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_DisableEp */
/** \brief Enable Endpoint */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_UDP_DisableEp( AT91PS_UDP pUDP,    /* \arg pointer to a UDP controller */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg endpoints to be enabled */
{
    pUDP->UDP_GLBSTATE &= ~( flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_SetState */
/** \brief Set UDP Device state */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_UDP_ਸੈੱਟ_State( AT91PS_UDP pUDP,    /* \arg pointer to a UDP controller */
                                  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg new UDP address */
{
    pUDP->UDP_GLBSTATE &= ~( AT91C_UDP_FADDEN | AT91C_UDP_CONFG );
    pUDP->UDP_GLBSTATE |= flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_GetState */
/** \brief return UDP Device state */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91F_UDP_GetState( /* \return the UDP device state */
    AT91PS_UDP pUDP )                     /* \arg pointer to a UDP controller */
{
    ਵਾਪਸ( pUDP->UDP_GLBSTATE & ( AT91C_UDP_FADDEN | AT91C_UDP_CONFG ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_ResetEp */
/** \brief Reset UDP endpoint */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_UDP_ResetEp( /* \return the UDP device state */
    AT91PS_UDP pUDP,             /* \arg pointer to a UDP controller */
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag )          /* \arg Endpoints to be reset */
{
    pUDP->UDP_RSTEP = flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_EpStall */
/** \brief Endpoint will STALL requests */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_UDP_EpStall( AT91PS_UDP pUDP,         /* \arg pointer to a UDP controller */
                                 ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ endpoint ) /* \arg endpoint number */
{
    pUDP->UDP_CSR[ endpoint ] |= AT91C_UDP_FORCESTALL;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_EpWrite */
/** \brief Write value in the DPR */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_UDP_EpWrite( AT91PS_UDP pUDP,        /* \arg pointer to a UDP controller */
                                 ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ endpoint, /* \arg endpoint number */
                                 ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਮੁੱਲ )   /* \arg value to be written in the DPR */
{
    pUDP->UDP_FDR[ endpoint ] = ਮੁੱਲ;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_EpRead */
/** \brief Return value from the DPR */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91F_UDP_EpRead( AT91PS_UDP pUDP,         /* \arg pointer to a UDP controller */
                                        ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ endpoint ) /* \arg endpoint number */
{
    ਵਾਪਸ pUDP->UDP_FDR[ endpoint ];
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_EpEndOfWr */
/** \brief Notify the UDP that values in DPR are ready to be sent */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_UDP_Ep_ਸਿਰਾ_ਦਾ_Wr( AT91PS_UDP pUDP,         /* \arg pointer to a UDP controller */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ endpoint ) /* \arg endpoint number */
{
    pUDP->UDP_CSR[ endpoint ] |= AT91C_UDP_TXPKTRDY;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_EpClear */
/** \brief Clear flag in the endpoint CSR register */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_UDP_EpClear( AT91PS_UDP pUDP,        /* \arg pointer to a UDP controller */
                                 ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ endpoint, /* \arg endpoint number */
                                 ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag )     /* \arg flag to be cleared */
{
    pUDP->UDP_CSR[ endpoint ] &= ~( flag );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_EpSet */
/** \brief Set flag in the endpoint CSR register */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91_F_UDP_Ep_ਸੈੱਟ( AT91PS_UDP pUDP,        /* \arg pointer to a UDP controller */
                               ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ endpoint, /* \arg endpoint number */
                               ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag )     /* \arg flag to be cleared */
{
    pUDP->UDP_CSR[ endpoint ] |= flag;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_EpStatus */
/** \brief Return the endpoint CSR register */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_UDP_Ep_ਸਥਿਤੀ( AT91PS_UDP pUDP,         /* \arg pointer to a UDP controller */
                                          ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ endpoint ) /* \arg endpoint number */
{
    ਵਾਪਸ pUDP->UDP_CSR[ endpoint ];
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_GetInterruptMaskStatus */
/** \brief Return UDP Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_UDP_Get_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸਥਿਤੀ( /* \return UDP Interrupt Mask Status */
    AT91PS_UDP pUdp )                                   /* \arg  pointer to a UDP controller */
{
    ਵਾਪਸ pUdp->UDP_IMR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_IsInterruptMasked */
/** \brief Test if UDP Interrupt is Masked */
/**---------------------------------------------------------------------------- */
__inline ਪੂਰਨ AT91_F_UDP_Is_ਰੁਕਾਵਟ_Masked( AT91PS_UDP pUdp,    /* \arg  pointer to a UDP controller */
                                          ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flag ) /* \arg  flag to be tested */
{
    ਵਾਪਸ( AT91_F_UDP_Get_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸਥਿਤੀ( pUdp ) & flag );
}

/* *****************************************************************************
*               SOFTWARE API FOR AIC
***************************************************************************** */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AT91C_AIC_BRANCH_OPCODE    ( ( ਖਾਲੀ ( * )() ) 0xE51FFF20 ) /* ldr, pc, [pc, #-&F20] */

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_ConfigureIt */
/** \brief Interrupt Handler Initialization */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91F_AIC_ConfigureIt( AT91PS_AIC pAic,                /* \arg pointer to the AIC registers */
                                             ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ irq_id,            /* \arg interrupt number to initialize */
                                             ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਤਰਜੀਹ,          /* \arg priority to give to the interrupt */
                                             ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ src_type,          /* \arg activation and sense of activation */
                                             ਖਾਲੀ ( * newHandler )( ਖਾਲੀ ) ) /* \arg address of the interrupt handler */
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ oldHandler;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਨਕਾਬ;

    oldHandler = pAic->AIC_SVR[ irq_id ];

    ਨਕਾਬ = 0x1 << irq_id;
    /** Disable the interrupt on the interrupt controller */
    pAic->AIC_IDCR = ਨਕਾਬ;
    /** Save the interrupt handler routine pointer and the interrupt priority */
    pAic->AIC_SVR[ irq_id ] = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) newHandler;
    /** Store the Source Mode Register */
    pAic->AIC_SMR[ irq_id ] = src_type | ਤਰਜੀਹ;
    /** Clear the interrupt on the interrupt controller */
    pAic->AIC_ICCR = ਨਕਾਬ;

    ਵਾਪਸ oldHandler;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_EnableIt */
/** \brief Enable corresponding IT number */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_AIC_EnableIt( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ irq_id ) /* \arg interrupt number to initialize */
{
    /** Enable the interrupt on the interrupt controller */
    pAic->AIC_IECR = 0x1 << irq_id;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_DisableIt */
/** \brief Disable corresponding IT number */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_AIC_DisableIt( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ irq_id ) /* \arg interrupt number to initialize */
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਨਕਾਬ = 0x1 << irq_id;

    /** Disable the interrupt on the interrupt controller */
    pAic->AIC_IDCR = ਨਕਾਬ;
    /** Clear the interrupt on the Interrupt Controller ( if one is pending ) */
    pAic->AIC_ICCR = ਨਕਾਬ;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_ClearIt */
/** \brief Clear corresponding IT number */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_AIC_ClearIt( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                 ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ irq_id ) /* \arg interrupt number to initialize */
{
    /** Clear the interrupt on the Interrupt Controller ( if one is pending ) */
    pAic->AIC_ICCR = ( 0x1 << irq_id );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_AcknowledgeIt */
/** \brief Acknowledge corresponding IT number */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_AIC_AcknowledgeIt( AT91PS_AIC pAic ) /* \arg pointer to the AIC registers */
{
    pAic->AIC_EOICR = pAic->AIC_EOICR;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_SetExceptionVector */
/** \brief Configure vector handler */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_AIC_ਸੈੱਟ_Exception_ਸਦਿਸ਼( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ * p_ਸਦਿਸ਼, /* \arg pointer to the AIC registers */
                                                    ਖਾਲੀ ( * Handler )() )  /* \arg Interrupt Handler */
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ old_ਸਦਿਸ਼ = *p_ਸਦਿਸ਼;

    ਜੇ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) Handler == ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_AIC_BRANCH_OPCODE )
    {
        *p_ਸਦਿਸ਼ = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_AIC_BRANCH_OPCODE;
    }
    ਨਹੀਂਤਾਂ
    {
        *p_ਸਦਿਸ਼ = ( ( ( ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) Handler ) - ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) p_ਸਦਿਸ਼ ) - 0x8 ) >> 2 ) & 0x00FFFFFF ) | 0xEA000000;
    }

    ਵਾਪਸ old_ਸਦਿਸ਼;
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_Trig */
/** \brief Trig an IT */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_AIC_Trig( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                              ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ irq_id ) /* \arg interrupt number */
{
    pAic->AIC_ISCR = ( 0x1 << irq_id );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_IsActive */
/** \brief Test if an IT is active */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91_F_AIC_Is_ਸਰਗਰਮ( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                          ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ irq_id ) /* \arg Interrupt Number */
{
    ਵਾਪਸ( pAic->AIC_ISR & ( 0x1 << irq_id ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_IsPending */
/** \brief Test if an IT is pending */
/**---------------------------------------------------------------------------- */
__inline ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ AT91F_AIC_IsPending( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                           ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ irq_id ) /* \arg Interrupt Number */
{
    ਵਾਪਸ( pAic->AIC_IPR & ( 0x1 << irq_id ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_Open */
/** \brief Set exception vectors and AIC registers to default values */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_AIC_Open( AT91PS_AIC pAic,              /* \arg pointer to the AIC registers */
                              ਖਾਲੀ ( * IrqHandler )(),      /* \arg Default IRQ vector exception */
                              ਖਾਲੀ ( * FiqHandler )(),      /* \arg Default FIQ vector exception */
                              ਖਾਲੀ ( * DefaultHandler )(),  /* \arg Default Handler set in ISR */
                              ਖਾਲੀ ( * SpuriousHandler )(), /* \arg Default Spurious Handler */
                              ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ protect_ਬਹੁਲਕ )    /* \arg Debug Control Register */
{
    ਪੂਰਨ i;

    /* Disable all interrupts and set IVR to the default handler */
    ਲਈ( i = 0; i < 32; ++i )
    {
        AT91F_AIC_DisableIt( pAic, i );
        AT91F_AIC_ConfigureIt( pAic, i, AT91_C_AIC_ਪੂਰਵ_ਸਭ_ਤੋਂ_ਨੀਵਾਂ, AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE, DefaultHandler );
    }

    /* Set the IRQ exception vector */
    AT91_F_AIC_ਸੈੱਟ_Exception_ਸਦਿਸ਼( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ * ) 0x18, IrqHandler );
    /* Set the Fast Interrupt exception vector */
    AT91_F_AIC_ਸੈੱਟ_Exception_ਸਦਿਸ਼( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ * ) 0x1C, FiqHandler );

    pAic->AIC_SPU = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) SpuriousHandler;
    pAic->AIC_DCR = protect_ਬਹੁਲਕ;
}
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_MC_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  MC */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_MC_CfgPMC( ਖਾਲੀ )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_ਅਧਾਰ_PMC, /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) 1 << AT91C_ID_SYS ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_DBGU_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  DBGU */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_DBGU_CfgPMC( ਖਾਲੀ )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_ਅਧਾਰ_PMC, /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) 1 << AT91C_ID_SYS ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_DBGU_CfgPIO */
/** \brief Configure PIO controllers to drive DBGU signals */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_DBGU_CfgPIO( ਖਾਲੀ )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_ਅਧਾਰ_PIOA,                     /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA10_DTXD ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA9_DRXD ), /* Peripheral A */
        0 );                                 /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWMC_CH3_CfgPIO */
/** \brief Configure PIO controllers to drive PWMC_CH3 signals */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PWMC_CH3_CfgPIO( ਖਾਲੀ )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_ਅਧਾਰ_PIOA,                       /* PIO controller base address */
        0,                                     /* Peripheral A */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA14_PWM3 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA7_PWM3 ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWMC_CH2_CfgPIO */
/** \brief Configure PIO controllers to drive PWMC_CH2 signals */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PWMC_CH2_CfgPIO( ਖਾਲੀ )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_ਅਧਾਰ_PIOA,                        /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA2_PWM2 ),    /* Peripheral A */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA25_PWM2 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA13_PWM2 ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWMC_CH1_CfgPIO */
/** \brief Configure PIO controllers to drive PWMC_CH1 signals */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PWMC_CH1_CfgPIO( ਖਾਲੀ )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_ਅਧਾਰ_PIOA,                        /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA1_PWM1 ),    /* Peripheral A */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA24_PWM1 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA12_PWM1 ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWMC_CH0_CfgPIO */
/** \brief Configure PIO controllers to drive PWMC_CH0 signals */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PWMC_CH0_CfgPIO( ਖਾਲੀ )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_ਅਧਾਰ_PIOA,                        /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA0_PWM0 ),    /* Peripheral A */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA23_PWM0 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA11_PWM0 ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  SSC */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_SSC_CfgPMC( ਖਾਲੀ )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_ਅਧਾਰ_PMC, /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) 1 << AT91C_ID_SSC ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SSC_CfgPIO */
/** \brief Configure PIO controllers to drive SSC signals */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_SSC_CfgPIO( ਖਾਲੀ )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_ਅਧਾਰ_PIOA, /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA17_TD ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA15_TF ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA19_RK ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA18_RD ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA20_RF ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA16_TK ), /* Peripheral A */
        0 );                                /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  SPI */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_SPI_CfgPMC( ਖਾਲੀ )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_ਅਧਾਰ_PMC, /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) 1 << AT91C_ID_SPI ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_SPI_CfgPIO */
/** \brief Configure PIO controllers to drive SPI signals */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_SPI_CfgPIO( ਖਾਲੀ )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_ਅਧਾਰ_PIOA, /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA11_NPCS0 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA13_MOSI ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA31_NPCS1 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA12_MISO ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA14_SPCK ), /* Peripheral A */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA9_NPCS1 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA30_NPCS2 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA10_NPCS2 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA22_NPCS3 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA3_NPCS3 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA5_NPCS3 ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PWMC_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  PWMC */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PWMC_CfgPMC( ਖਾਲੀ )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_ਅਧਾਰ_PMC, /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) 1 << AT91C_ID_PWMC ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TC2_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  TC2 */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_TC2_CfgPMC( ਖਾਲੀ )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_ਅਧਾਰ_PMC, /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) 1 << AT91C_ID_TC2 ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TC2_CfgPIO */
/** \brief Configure PIO controllers to drive TC2 signals */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_TC2_CfgPIO( ਖਾਲੀ )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_ਅਧਾਰ_PIOA, /* PIO controller base address */
        0,               /* Peripheral A */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA26_TIOA2 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA27_TIOB2 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA29_TCLK2 ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TC1_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  TC1 */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_TC1_CfgPMC( ਖਾਲੀ )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_ਅਧਾਰ_PMC, /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) 1 << AT91C_ID_TC1 ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TC1_CfgPIO */
/** \brief Configure PIO controllers to drive TC1 signals */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_TC1_CfgPIO( ਖਾਲੀ )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_ਅਧਾਰ_PIOA, /* PIO controller base address */
        0,               /* Peripheral A */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA15_TIOA1 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA16_TIOB1 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA28_TCLK1 ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TC0_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  TC0 */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_TC0_CfgPMC( ਖਾਲੀ )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_ਅਧਾਰ_PMC, /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) 1 << AT91C_ID_TC0 ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TC0_CfgPIO */
/** \brief Configure PIO controllers to drive TC0 signals */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_TC0_CfgPIO( ਖਾਲੀ )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_ਅਧਾਰ_PIOA, /* PIO controller base address */
        0,               /* Peripheral A */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA0_TIOA0 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA1_TIOB0 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA4_TCLK0 ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  PMC */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PMC_CfgPMC( ਖਾਲੀ )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_ਅਧਾਰ_PMC, /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) 1 << AT91C_ID_SYS ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_CfgPIO */
/** \brief Configure PIO controllers to drive PMC signals */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PMC_CfgPIO( ਖਾਲੀ )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_ਅਧਾਰ_PIOA, /* PIO controller base address */
        0,               /* Peripheral A */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA17_PCK1 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA21_PCK1 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA31_PCK2 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA18_PCK2 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA6_PCK0 ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  ADC */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_ADC_CfgPMC( ਖਾਲੀ )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_ਅਧਾਰ_PMC, /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) 1 << AT91C_ID_ADC ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_ADC_CfgPIO */
/** \brief Configure PIO controllers to drive ADC signals */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_ADC_CfgPIO( ਖਾਲੀ )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_ਅਧਾਰ_PIOA,                        /* PIO controller base address */
        0,                                      /* Peripheral A */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA8_ADTRG ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIOA_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  PIOA */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_PIOA_CfgPMC( ਖਾਲੀ )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_ਅਧਾਰ_PMC, /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) 1 << AT91C_ID_PIOA ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TWI_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  TWI */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_TWI_CfgPMC( ਖਾਲੀ )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_ਅਧਾਰ_PMC, /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) 1 << AT91C_ID_TWI ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_TWI_CfgPIO */
/** \brief Configure PIO controllers to drive TWI signals */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_TWI_CfgPIO( ਖਾਲੀ )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_ਅਧਾਰ_PIOA,                     /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA3_TWD ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA4_TWCK ), /* Peripheral A */
        0 );                                 /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US1_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  US1 */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_US1_CfgPMC( ਖਾਲੀ )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_ਅਧਾਰ_PMC, /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) 1 << AT91C_ID_US1 ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US1_CfgPIO */
/** \brief Configure PIO controllers to drive US1 signals */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_US1_CfgPIO( ਖਾਲੀ )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_ਅਧਾਰ_PIOA, /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA21_RXD1 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA27_DTR1 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA26_DCD1 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA22_TXD1 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA24_RTS1 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA23_SCK1 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA28_DSR1 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA29_RI1 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA25_CTS1 ), /* Peripheral A */
        0 );                                  /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US0_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  US0 */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_US0_CfgPMC( ਖਾਲੀ )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_ਅਧਾਰ_PMC, /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) 1 << AT91C_ID_US0 ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_US0_CfgPIO */
/** \brief Configure PIO controllers to drive US0 signals */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_US0_CfgPIO( ਖਾਲੀ )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_ਅਧਾਰ_PIOA, /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA5_RXD0 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA6_TXD0 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA7_RTS0 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA8_CTS0 ),   /* Peripheral A */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA2_SCK0 ) ); /* Peripheral B */
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_UDP_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  UDP */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_UDP_CfgPMC( ਖਾਲੀ )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_ਅਧਾਰ_PMC, /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) 1 << AT91C_ID_UDP ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_CfgPMC */
/** \brief Enable Peripheral clock in PMC for  AIC */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_AIC_CfgPMC( ਖਾਲੀ )
{
    AT91F_PMC_EnablePeriphClock(
        AT91_C_ਅਧਾਰ_PMC, /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) 1 << AT91C_ID_IRQ0 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) 1 << AT91C_ID_FIQ ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) 1 << AT91C_ID_IRQ1 ) );
}

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_CfgPIO */
/** \brief Configure PIO controllers to drive AIC signals */
/**---------------------------------------------------------------------------- */
__inline ਖਾਲੀ AT91F_AIC_CfgPIO( ਖਾਲੀ )
{
    /* Configure PIO controllers to periph mode */
    AT91F_PIO_CfgPeriph(
        AT91_C_ਅਧਾਰ_PIOA,                       /* PIO controller base address */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA30_IRQ1 ),  /* Peripheral A */
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA20_IRQ0 ) |
        ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ) AT91C_PA19_FIQ ) ); /* Peripheral B */
}

#ਜੇ_ਅੰਤ // lib_AT91SAM7S64_H
