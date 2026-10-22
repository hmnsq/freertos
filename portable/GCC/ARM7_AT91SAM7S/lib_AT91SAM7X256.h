/** ---------------------------------------------------------------------------- */
/**         ATMEL Microcontroller Software Support  -  ROUSSET  - */
/** ---------------------------------------------------------------------------- */
/** DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR */
/** IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE */
/** DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT, */
/** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, */
/** OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF */
/** LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING */
/** NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/** EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
/** ---------------------------------------------------------------------------- */
/** File Name           : lib_AT91SAM7X256.h */
/** Object              : AT91SAM7X256 inlined functions */
/** Generated           : AT91 SW Application Group  05/20/2005 (16:22:29) */
/** */
/** CVS Reference       : /lib_dbgu.h/1.1/Fri Jan 31 12:18:40 2003// */
/** CVS Reference       : /lib_pmc_SAM7X.h/1.1/Tue Feb  1 08:32:10 2005// */
/** CVS Reference       : /lib_VREG_6085B.h/1.1/Tue Feb  1 16:20:47 2005// */
/** CVS Reference       : /lib_rstc_6098A.h/1.1/Wed Oct  6 10:39:20 2004// */
/** CVS Reference       : /lib_ssc.h/1.4/Fri Jan 31 12:19:20 2003// */
/** CVS Reference       : /lib_wdtc_6080A.h/1.1/Wed Oct  6 10:38:30 2004// */
/** CVS Reference       : /lib_usart.h/1.5/Thu Nov 21 16:01:54 2002// */
/** CVS Reference       : /lib_spi2.h/1.1/Mon Aug 25 14:23:52 2003// */
/** CVS Reference       : /lib_pitc_6079A.h/1.2/Tue Nov  9 14:43:56 2004// */
/** CVS Reference       : /lib_aic_6075b.h/1.1/Fri May 20 14:01:19 2005// */
/** CVS Reference       : /lib_aes_6149a.h/1.1/Mon Jan 17 07:43:09 2005// */
/** CVS Reference       : /lib_twi.h/1.3/Mon Jul 19 14:27:58 2004// */
/** CVS Reference       : /lib_adc.h/1.6/Fri Oct 17 09:12:38 2003// */
/** CVS Reference       : /lib_rttc_6081A.h/1.1/Wed Oct  6 10:39:38 2004// */
/** CVS Reference       : /lib_udp.h/1.4/Wed Feb 16 08:39:34 2005// */
/** CVS Reference       : /lib_des3_6150a.h/1.1/Mon Jan 17 09:19:19 2005// */
/** CVS Reference       : /lib_tc_1753b.h/1.1/Fri Jan 31 12:20:02 2003// */
/** CVS Reference       : /lib_MC_SAM7X.h/1.1/Thu Mar 25 15:19:14 2004// */
/** CVS Reference       : /lib_pio.h/1.3/Fri Jan 31 12:18:56 2003// */
/** CVS Reference       : /lib_can_AT91.h/1.4/Fri Oct 17 09:12:50 2003// */
/** CVS Reference       : /lib_PWM_SAM.h/1.3/Thu Jan 22 10:10:50 2004// */
/** CVS Reference       : /lib_pdc.h/1.2/Tue Jul  2 13:29:40 2002// */
/** ---------------------------------------------------------------------------- */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ lib_AT91SAM7X256_H
    #ವ್ಯಾಖ್ಯಾನಿಸು lib_AT91SAM7X256_H

/* *****************************************************************************
*               SOFTWARE API FOR AIC
***************************************************************************** */
    #ವ್ಯಾಖ್ಯಾನಿಸು AT91C_AIC_BRANCH_OPCODE    ( ( ಶೂನ್ಯ ( * )() ) 0xE51FFF20 ) /* ldr, pc, [pc, #-&F20] */

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_ConfigureIt */
/** \brief Interrupt Handler Initialization */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91F_AIC_ConfigureIt( AT91PS_AIC pAic,                /* \arg pointer to the AIC registers */
                                                 ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ irq_id,            /* \arg interrupt number to initialize */
                                                 ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಆದ್ಯತೆ,          /* \arg priority to give to the interrupt */
                                                 ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ src_type,          /* \arg activation and sense of activation */
                                                 ಶೂನ್ಯ ( * newHandler )( ಶೂನ್ಯ ) ) /* \arg address of the interrupt handler */
    {
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ oldHandler;
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಮುಖವಾಡ;

        oldHandler = pAic->AIC_SVR[ irq_id ];

        ಮುಖವಾಡ = 0x1 << irq_id;
        /** Disable the interrupt on the interrupt controller */
        pAic->AIC_IDCR = ಮುಖವಾಡ;
        /** Save the interrupt handler routine pointer and the interrupt priority */
        pAic->AIC_SVR[ irq_id ] = ( ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ) newHandler;
        /** Store the Source Mode Register */
        pAic->AIC_SMR[ irq_id ] = src_type | ಆದ್ಯತೆ;
        /** Clear the interrupt on the interrupt controller */
        pAic->AIC_ICCR = ಮುಖವಾಡ;

        ಹಿಂತಿರುಗಿ oldHandler;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_EnableIt */
/** \brief Enable corresponding IT number */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_AIC_EnableIt( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                      ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ irq_id ) /* \arg interrupt number to initialize */
    {
        /** Enable the interrupt on the interrupt controller */
        pAic->AIC_IECR = 0x1 << irq_id;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_DisableIt */
/** \brief Disable corresponding IT number */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_AIC_DisableIt( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                       ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ irq_id ) /* \arg interrupt number to initialize */
    {
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಮುಖವಾಡ = 0x1 << irq_id;

        /** Disable the interrupt on the interrupt controller */
        pAic->AIC_IDCR = ಮುಖವಾಡ;
        /** Clear the interrupt on the Interrupt Controller ( if one is pending ) */
        pAic->AIC_ICCR = ಮುಖವಾಡ;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_ClearIt */
/** \brief Clear corresponding IT number */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_AIC_ClearIt( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                     ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ irq_id ) /* \arg interrupt number to initialize */
    {
        /** Clear the interrupt on the Interrupt Controller ( if one is pending ) */
        pAic->AIC_ICCR = ( 0x1 << irq_id );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_AcknowledgeIt */
/** \brief Acknowledge corresponding IT number */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_AIC_AcknowledgeIt( AT91PS_AIC pAic ) /* \arg pointer to the AIC registers */
    {
        pAic->AIC_EOICR = pAic->AIC_EOICR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_SetExceptionVector */
/** \brief Configure vector handler */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_AIC_ಗಣ_Exception_ಸದಿಶ( ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ * p_ಸದಿಶ, /* \arg pointer to the AIC registers */
                                                        ಶೂನ್ಯ ( * Handler )() )  /* \arg Interrupt Handler */
    {
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ old_ಸದಿಶ = *p_ಸದಿಶ;

        ಆದರೆ( ( ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ) Handler == ( ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ) AT91C_AIC_BRANCH_OPCODE )
        {
            *p_ಸದಿಶ = ( ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ) AT91C_AIC_BRANCH_OPCODE;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            *p_ಸದಿಶ = ( ( ( ( ( ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ) Handler ) - ( ( ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ) p_ಸದಿಶ ) - 0x8 ) >> 2 ) & 0x00FFFFFF ) | 0xEA000000;
        }

        ಹಿಂತಿರುಗಿ old_ಸದಿಶ;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_Trig */
/** \brief Trig an IT */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_AIC_Trig( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ irq_id ) /* \arg interrupt number */
    {
        pAic->AIC_ISCR = ( 0x1 << irq_id );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_IsActive */
/** \brief Test if an IT is active */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_AIC_Is_ಸಕ್ರಿಯ( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                              ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ irq_id ) /* \arg Interrupt Number */
    {
        ಹಿಂತಿರುಗಿ( pAic->AIC_ISR & ( 0x1 << irq_id ) );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_IsPending */
/** \brief Test if an IT is pending */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91F_AIC_IsPending( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                               ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ irq_id ) /* \arg Interrupt Number */
    {
        ಹಿಂತಿರುಗಿ( pAic->AIC_IPR & ( 0x1 << irq_id ) );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_Open */
/** \brief Set exception vectors and AIC registers to default values */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_AIC_Open( AT91PS_AIC pAic,              /* \arg pointer to the AIC registers */
                                  ಶೂನ್ಯ ( * IrqHandler )(),      /* \arg Default IRQ vector exception */
                                  ಶೂನ್ಯ ( * FiqHandler )(),      /* \arg Default FIQ vector exception */
                                  ಶೂನ್ಯ ( * DefaultHandler )(),  /* \arg Default Handler set in ISR */
                                  ಶೂನ್ಯ ( * SpuriousHandler )(), /* \arg Default Spurious Handler */
                                  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ protect_ಬಹುಲಕ )    /* \arg Debug Control Register */
    {
        ಪೂರ್ಣಾಂಕ i;

        /* Disable all interrupts and set IVR to the default handler */
        ಗಾಗಿ( i = 0; i < 32; ++i )
        {
            AT91F_AIC_DisableIt( pAic, i );
            AT91F_AIC_ConfigureIt( pAic, i, AT91_C_AIC_ಪೂರ್ವ_ಅತಿಕಡಿಮೆ, AT91_C_AIC_SRCTYPE_ಮೇಲಿನ_LEVEL, DefaultHandler );
        }

        /* Set the IRQ exception vector */
        AT91_F_AIC_ಗಣ_Exception_ಸದಿಶ( ( ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ * ) 0x18, IrqHandler );
        /* Set the Fast Interrupt exception vector */
        AT91_F_AIC_ಗಣ_Exception_ಸದಿಶ( ( ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ * ) 0x1C, FiqHandler );

        pAic->AIC_SPU = ( ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ) SpuriousHandler;
        pAic->AIC_DCR = protect_ಬಹುಲಕ;
    }

/* *****************************************************************************
*               SOFTWARE API FOR PDC
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_SetNextRx */
/** \brief Set the next receive transfer descriptor */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91_F_PDC_ಗಣ_ಮುಂದಿನ_Rx( AT91PS_PDC pPDC,     /* \arg pointer to a PDC controller */
                                       ಅಕ್ಷರ * ವಿಳಾಸ_2,      /* \arg address to the next block to be received */
                                       ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಬೈಟುಗಳು_2 ) /* \arg number of bytes to be received */
    {
        pPDC->PDC_RNPR = ( ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ) ವಿಳಾಸ_2;
        pPDC->PDC_RNCR = ಬೈಟುಗಳು_2;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_SetNextTx */
/** \brief Set the next transmit transfer descriptor */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91_F_PDC_ಗಣ_ಮುಂದಿನ_Tx( AT91PS_PDC pPDC,     /* \arg pointer to a PDC controller */
                                       ಅಕ್ಷರ * ವಿಳಾಸ_2,      /* \arg address to the next block to be transmitted */
                                       ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಬೈಟುಗಳು_2 ) /* \arg number of bytes to be transmitted */
    {
        pPDC->PDC_TNPR = ( ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ) ವಿಳಾಸ_2;
        pPDC->PDC_TNCR = ಬೈಟುಗಳು_2;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_SetRx */
/** \brief Set the receive transfer descriptor */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91_F_PDC_ಗಣ_Rx( AT91PS_PDC pPDC,     /* \arg pointer to a PDC controller */
                                   ಅಕ್ಷರ * ವಿಳಾಸ_2,      /* \arg address to the next block to be received */
                                   ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಬೈಟುಗಳು_2 ) /* \arg number of bytes to be received */
    {
        pPDC->PDC_RPR = ( ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ) ವಿಳಾಸ_2;
        pPDC->PDC_RCR = ಬೈಟುಗಳು_2;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_SetTx */
/** \brief Set the transmit transfer descriptor */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91_F_PDC_ಗಣ_Tx( AT91PS_PDC pPDC,     /* \arg pointer to a PDC controller */
                                   ಅಕ್ಷರ * ವಿಳಾಸ_2,      /* \arg address to the next block to be transmitted */
                                   ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಬೈಟುಗಳು_2 ) /* \arg number of bytes to be transmitted */
    {
        pPDC->PDC_TPR = ( ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ) ವಿಳಾಸ_2;
        pPDC->PDC_TCR = ಬೈಟುಗಳು_2;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_EnableTx */
/** \brief Enable transmit */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PDC_EnableTx( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
    {
        pPDC->PDC_PTCR = AT91C_PDC_TXTEN;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_EnableRx */
/** \brief Enable receive */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PDC_EnableRx( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
    {
        pPDC->PDC_PTCR = AT91C_PDC_RXTEN;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_DisableTx */
/** \brief Disable transmit */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PDC_DisableTx( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
    {
        pPDC->PDC_PTCR = AT91C_PDC_TXTDIS;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_DisableRx */
/** \brief Disable receive */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PDC_DisableRx( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
    {
        pPDC->PDC_PTCR = AT91C_PDC_RXTDIS;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_IsTxEmpty */
/** \brief Test if the current transfer descriptor has been sent */
/**---------------------------------------------------------------------------- */
    __inline ಪೂರ್ಣಾಂಕ AT91_F_PDC_Is_Tx_ಖಾಲಿಗಳು( /* \return return 1 if transfer is complete */
        AT91PS_PDC pPDC )             /* \arg pointer to a PDC controller */
    {
        ಹಿಂತಿರುಗಿ !( pPDC->PDC_TCR );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_IsNextTxEmpty */
/** \brief Test if the next transfer descriptor has been moved to the current td */
/**---------------------------------------------------------------------------- */
    __inline ಪೂರ್ಣಾಂಕ AT91_F_PDC_Is_ಮುಂದಿನ_Tx_ಖಾಲಿಗಳು( /* \return return 1 if transfer is complete */
        AT91PS_PDC pPDC )                 /* \arg pointer to a PDC controller */
    {
        ಹಿಂತಿರುಗಿ !( pPDC->PDC_TNCR );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_IsRxEmpty */
/** \brief Test if the current transfer descriptor has been filled */
/**---------------------------------------------------------------------------- */
    __inline ಪೂರ್ಣಾಂಕ AT91_F_PDC_Is_Rx_ಖಾಲಿಗಳು( /* \return return 1 if transfer is complete */
        AT91PS_PDC pPDC )             /* \arg pointer to a PDC controller */
    {
        ಹಿಂತಿರುಗಿ !( pPDC->PDC_RCR );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_IsNextRxEmpty */
/** \brief Test if the next transfer descriptor has been moved to the current td */
/**---------------------------------------------------------------------------- */
    __inline ಪೂರ್ಣಾಂಕ AT91_F_PDC_Is_ಮುಂದಿನ_Rx_ಖಾಲಿಗಳು( /* \return return 1 if transfer is complete */
        AT91PS_PDC pPDC )                 /* \arg pointer to a PDC controller */
    {
        ಹಿಂತಿರುಗಿ !( pPDC->PDC_RNCR );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_Open */
/** \brief Open PDC: disable TX and RX reset transfer descriptors, re-enable RX and TX */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PDC_Open( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
    {
        /** Disable the RX and TX PDC transfer requests */
        AT91F_PDC_DisableRx( pPDC );
        AT91F_PDC_DisableTx( pPDC );

        /** Reset all Counter register Next buffer first */
        AT91_F_PDC_ಗಣ_ಮುಂದಿನ_Tx( pPDC, ( ಅಕ್ಷರ * ) 0, 0 );
        AT91_F_PDC_ಗಣ_ಮುಂದಿನ_Rx( pPDC, ( ಅಕ್ಷರ * ) 0, 0 );
        AT91_F_PDC_ಗಣ_Tx( pPDC, ( ಅಕ್ಷರ * ) 0, 0 );
        AT91_F_PDC_ಗಣ_Rx( pPDC, ( ಅಕ್ಷರ * ) 0, 0 );

        /** Enable the RX and TX PDC transfer requests */
        AT91F_PDC_EnableRx( pPDC );
        AT91F_PDC_EnableTx( pPDC );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_Close */
/** \brief Close PDC: disable TX and RX reset transfer descriptors */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PDC_Close( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
    {
        /** Disable the RX and TX PDC transfer requests */
        AT91F_PDC_DisableRx( pPDC );
        AT91F_PDC_DisableTx( pPDC );

        /** Reset all Counter register Next buffer first */
        AT91_F_PDC_ಗಣ_ಮುಂದಿನ_Tx( pPDC, ( ಅಕ್ಷರ * ) 0, 0 );
        AT91_F_PDC_ಗಣ_ಮುಂದಿನ_Rx( pPDC, ( ಅಕ್ಷರ * ) 0, 0 );
        AT91_F_PDC_ಗಣ_Tx( pPDC, ( ಅಕ್ಷರ * ) 0, 0 );
        AT91_F_PDC_ಗಣ_Rx( pPDC, ( ಅಕ್ಷರ * ) 0, 0 );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_SendFrame */
/** \brief Close PDC: disable TX and RX reset transfer descriptors */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_PDC_Send_ಚೌಕಟ್ಟು( AT91PS_PDC pPDC,
                                               ಅಕ್ಷರ * p_ಬಫರ್,
                                               ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ sz_ಬಫರ್,
                                               ಅಕ್ಷರ * p_ಮುಂದಿನ_ಬಫರ್,
                                               ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ sz_ಮುಂದಿನ_ಬಫರ್ )
    {
        ಆದರೆ( AT91_F_PDC_Is_Tx_ಖಾಲಿಗಳು( pPDC ) )
        {
            /** Buffer and next buffer can be initialized */
            AT91_F_PDC_ಗಣ_Tx( pPDC, p_ಬಫರ್, sz_ಬಫರ್ );
            AT91_F_PDC_ಗಣ_ಮುಂದಿನ_Tx( pPDC, p_ಮುಂದಿನ_ಬಫರ್, sz_ಮುಂದಿನ_ಬಫರ್ );
            ಹಿಂತಿರುಗಿ 2;
        }
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ( AT91_F_PDC_Is_ಮುಂದಿನ_Tx_ಖಾಲಿಗಳು( pPDC ) )
        {
            /** Only one buffer can be initialized */
            AT91_F_PDC_ಗಣ_ಮುಂದಿನ_Tx( pPDC, p_ಬಫರ್, sz_ಬಫರ್ );
            ಹಿಂತಿರುಗಿ 1;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            /** All buffer are in use... */
            ಹಿಂತಿರುಗಿ 0;
        }
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_ReceiveFrame */
/** \brief Close PDC: disable TX and RX reset transfer descriptors */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_PDC_Receive_ಚೌಕಟ್ಟು( AT91PS_PDC pPDC,
                                                  ಅಕ್ಷರ * p_ಬಫರ್,
                                                  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ sz_ಬಫರ್,
                                                  ಅಕ್ಷರ * p_ಮುಂದಿನ_ಬಫರ್,
                                                  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ sz_ಮುಂದಿನ_ಬಫರ್ )
    {
        ಆದರೆ( AT91_F_PDC_Is_Rx_ಖಾಲಿಗಳು( pPDC ) )
        {
            /** Buffer and next buffer can be initialized */
            AT91_F_PDC_ಗಣ_Rx( pPDC, p_ಬಫರ್, sz_ಬಫರ್ );
            AT91_F_PDC_ಗಣ_ಮುಂದಿನ_Rx( pPDC, p_ಮುಂದಿನ_ಬಫರ್, sz_ಮುಂದಿನ_ಬಫರ್ );
            ಹಿಂತಿರುಗಿ 2;
        }
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ( AT91_F_PDC_Is_ಮುಂದಿನ_Rx_ಖಾಲಿಗಳು( pPDC ) )
        {
            /** Only one buffer can be initialized */
            AT91_F_PDC_ಗಣ_ಮುಂದಿನ_Rx( pPDC, p_ಬಫರ್, sz_ಬಫರ್ );
            ಹಿಂತಿರುಗಿ 1;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            /** All buffer are in use... */
            ಹಿಂತಿರುಗಿ 0;
        }
    }

/* *****************************************************************************
*               SOFTWARE API FOR DBGU
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_DBGU_InterruptEnable */
/** \brief Enable DBGU Interrupt */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91_F_DBGU_ಅಡಚಣೆ_Enable( AT91PS_DBGU pDbgu,  /* \arg  pointer to a DBGU controller */
                                              ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  dbgu interrupt to be enabled */
    {
        pDbgu->DBGU_IER = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_DBGU_InterruptDisable */
/** \brief Disable DBGU Interrupt */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91_F_DBGU_ಅಡಚಣೆ_Disable( AT91PS_DBGU pDbgu,  /* \arg  pointer to a DBGU controller */
                                               ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  dbgu interrupt to be disabled */
    {
        pDbgu->DBGU_IDR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_DBGU_GetInterruptMaskStatus */
/** \brief Return DBGU Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_DBGU_Get_ಅಡಚಣೆ_ಮುಖವಾಡ_ಸ್ಥಿತಿ( /* \return DBGU Interrupt Mask Status */
        AT91PS_DBGU pDbgu )                                  /* \arg  pointer to a DBGU controller */
    {
        ಹಿಂತಿರುಗಿ pDbgu->DBGU_IMR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_DBGU_IsInterruptMasked */
/** \brief Test if DBGU Interrupt is Masked */
/**---------------------------------------------------------------------------- */
    __inline ಪೂರ್ಣಾಂಕ AT91_F_DBGU_Is_ಅಡಚಣೆ_Masked( AT91PS_DBGU pDbgu,  /* \arg  pointer to a DBGU controller */
                                               ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  flag to be tested */
    {
        ಹಿಂತಿರುಗಿ( AT91_F_DBGU_Get_ಅಡಚಣೆ_ಮುಖವಾಡ_ಸ್ಥಿತಿ( pDbgu ) & flag );
    }

/* *****************************************************************************
*               SOFTWARE API FOR PIO
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgPeriph */
/** \brief Enable pins to be derived by peripheral */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PIO_CfgPeriph( AT91PS_PIO pPio,             /* \arg pointer to a PIO controller */
                                       ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ periphAEnable,  /* \arg PERIPH A to enable */
                                       ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ periphBEnable ) /* \arg PERIPH B to enable */

    {
        pPio->PIO_ASR = periphAEnable;
        pPio->PIO_BSR = periphBEnable;
        pPio->PIO_PDR = ( periphAEnable | periphBEnable ); /* Set in Periph mode */
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgOutput */
/** \brief Enable PIO in output mode */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PIO_CfgOutput( AT91PS_PIO pPio,         /* \arg pointer to a PIO controller */
                                       ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ pioEnable ) /* \arg PIO to be enabled */
    {
        pPio->PIO_ಪ್ರತಿ = pioEnable;                              /* Set in PIO mode */
        pPio->PIO_OER = pioEnable;                              /* Configure in Output */
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgInput */
/** \brief Enable PIO in input mode */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91_F_PIO_Cfg_ಒಳಹರಿವು( AT91PS_PIO pPio,           /* \arg pointer to a PIO controller */
                                      ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಒಳಹರಿವು_Enable ) /* \arg PIO to be enabled */
    {
        /* Disable output */
        pPio->PIO_ODR = ಒಳಹರಿವು_Enable;
        pPio->PIO_ಪ್ರತಿ = ಒಳಹರಿವು_Enable;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgOpendrain */
/** \brief Configure PIO in open drain */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PIO_CfgOpendrain( AT91PS_PIO pPio,              /* \arg pointer to a PIO controller */
                                          ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ multiDrvEnable ) /* \arg pio to be configured in open drain */
    {
        /* Configure the multi-drive option */
        pPio->PIO_MDDR = ~multiDrvEnable;
        pPio->PIO_MDER = multiDrvEnable;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgPullup */
/** \brief Enable pullup on PIO */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PIO_CfgPullup( AT91PS_PIO pPio,            /* \arg pointer to a PIO controller */
                                       ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ pullupEnable ) /* \arg enable pullup on PIO */
    {
        /* Connect or not Pullup */
        pPio->PIO_PPUDR = ~pullupEnable;
        pPio->PIO_PPUER = pullupEnable;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgDirectDrive */
/** \brief Enable direct drive on PIO */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91_F_PIO_Cfg_ನೇರ_Drive( AT91PS_PIO pPio,           /* \arg pointer to a PIO controller */
                                            ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ನೇರ_Drive ) /* \arg PIO to be configured with direct drive */

    {
        /* Configure the Direct Drive */
        pPio->PIO_OWDR = ~ನೇರ_Drive;
        pPio->PIO_OWER = ನೇರ_Drive;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgInputFilter */
/** \brief Enable input filter on input PIO */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91_F_PIO_Cfg_ಒಳಹರಿವು_Filter( AT91PS_PIO pPio,           /* \arg pointer to a PIO controller */
                                            ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಒಳಹರಿವು_Filter ) /* \arg PIO to be configured with input filter */

    {
        /* Configure the Direct Drive */
        pPio->PIO_IFDR = ~ಒಳಹರಿವು_Filter;
        pPio->PIO_IFER = ಒಳಹರಿವು_Filter;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetInput */
/** \brief Return PIO input value */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_PIO_Get_ಒಳಹರಿವು( /* \return PIO input */
        AT91PS_PIO pPio )                     /* \arg  pointer to a PIO controller */
    {
        ಹಿಂತಿರುಗಿ pPio->PIO_PDSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsInputSet */
/** \brief Test if PIO is input flag is active */
/**---------------------------------------------------------------------------- */
    __inline ಪೂರ್ಣಾಂಕ AT91_F_PIO_Is_ಒಳಹರಿವು_ಗಣ( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                       ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  flag to be tested */
    {
        ಹಿಂತಿರುಗಿ( AT91_F_PIO_Get_ಒಳಹರಿವು( pPio ) & flag );
    }


/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_SetOutput */
/** \brief Set to 1 output PIO */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91_F_PIO_ಗಣ_Output( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                       ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  output to be set */
    {
        pPio->PIO_SODR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_ClearOutput */
/** \brief Set to 0 output PIO */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PIO_ClearOutput( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                         ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  output to be cleared */
    {
        pPio->PIO_CODR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_ForceOutput */
/** \brief Force output when Direct drive option is enabled */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PIO_ForceOutput( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                         ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  output to be forced */
    {
        pPio->PIO_ODSR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_Enable */
/** \brief Enable PIO */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PIO_Enable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  pio to be enabled */
    {
        pPio->PIO_ಪ್ರತಿ = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_Disable */
/** \brief Disable PIO */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PIO_Disable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                     ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  pio to be disabled */
    {
        pPio->PIO_PDR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetStatus */
/** \brief Return PIO Status */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_PIO_Get_ಸ್ಥಿತಿ( /* \return PIO Status */
        AT91PS_PIO pPio )                      /* \arg  pointer to a PIO controller */
    {
        ಹಿಂತಿರುಗಿ pPio->PIO_PSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsSet */
/** \brief Test if PIO is Set */
/**---------------------------------------------------------------------------- */
    __inline ಪೂರ್ಣಾಂಕ AT91_F_PIO_Is_ಗಣ( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  flag to be tested */
    {
        ಹಿಂತಿರುಗಿ( AT91_F_PIO_Get_ಸ್ಥಿತಿ( pPio ) & flag );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_OutputEnable */
/** \brief Output Enable PIO */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PIO_OutputEnable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                          ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  pio output to be enabled */
    {
        pPio->PIO_OER = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_OutputDisable */
/** \brief Output Enable PIO */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PIO_OutputDisable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                           ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  pio output to be disabled */
    {
        pPio->PIO_ODR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetOutputStatus */
/** \brief Return PIO Output Status */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_PIO_Get_Output_ಸ್ಥಿತಿ( /* \return PIO Output Status */
        AT91PS_PIO pPio )                            /* \arg  pointer to a PIO controller */
    {
        ಹಿಂತಿರುಗಿ pPio->PIO_OSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsOuputSet */
/** \brief Test if PIO Output is Set */
/**---------------------------------------------------------------------------- */
    __inline ಪೂರ್ಣಾಂಕ AT91_F_PIO_Is_Output_ಗಣ( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  flag to be tested */
    {
        ಹಿಂತಿರುಗಿ( AT91_F_PIO_Get_Output_ಸ್ಥಿತಿ( pPio ) & flag );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_InputFilterEnable */
/** \brief Input Filter Enable PIO */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91_F_PIO_ಒಳಹರಿವು_Filter_Enable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                               ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  pio input filter to be enabled */
    {
        pPio->PIO_IFER = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_InputFilterDisable */
/** \brief Input Filter Disable PIO */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91_F_PIO_ಒಳಹರಿವು_Filter_Disable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                                ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  pio input filter to be disabled */
    {
        pPio->PIO_IFDR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetInputFilterStatus */
/** \brief Return PIO Input Filter Status */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_PIO_Get_ಒಳಹರಿವು_Filter_ಸ್ಥಿತಿ( /* \return PIO Input Filter Status */
        AT91PS_PIO pPio )                                 /* \arg  pointer to a PIO controller */
    {
        ಹಿಂತಿರುಗಿ pPio->PIO_IFSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsInputFilterSet */
/** \brief Test if PIO Input filter is Set */
/**---------------------------------------------------------------------------- */
    __inline ಪೂರ್ಣಾಂಕ AT91_F_PIO_Is_ಒಳಹರಿವು_Filter_ಗಣ( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                             ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  flag to be tested */
    {
        ಹಿಂತಿರುಗಿ( AT91_F_PIO_Get_ಒಳಹರಿವು_Filter_ಸ್ಥಿತಿ( pPio ) & flag );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetOutputDataStatus */
/** \brief Return PIO Output Data Status */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_PIO_Get_Output_ದತ್ತಾಂಶ_ಸ್ಥಿತಿ( /* \return PIO Output Data Status */
        AT91PS_PIO pPio )                                /* \arg  pointer to a PIO controller */
    {
        ಹಿಂತಿರುಗಿ pPio->PIO_ODSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_InterruptEnable */
/** \brief Enable PIO Interrupt */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91_F_PIO_ಅಡಚಣೆ_Enable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                             ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  pio interrupt to be enabled */
    {
        pPio->PIO_IER = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_InterruptDisable */
/** \brief Disable PIO Interrupt */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91_F_PIO_ಅಡಚಣೆ_Disable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                              ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  pio interrupt to be disabled */
    {
        pPio->PIO_IDR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetInterruptMaskStatus */
/** \brief Return PIO Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_PIO_Get_ಅಡಚಣೆ_ಮುಖವಾಡ_ಸ್ಥಿತಿ( /* \return PIO Interrupt Mask Status */
        AT91PS_PIO pPio )                                   /* \arg  pointer to a PIO controller */
    {
        ಹಿಂತಿರುಗಿ pPio->PIO_IMR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetInterruptStatus */
/** \brief Return PIO Interrupt Status */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_PIO_Get_ಅಡಚಣೆ_ಸ್ಥಿತಿ( /* \return PIO Interrupt Status */
        AT91PS_PIO pPio )                               /* \arg  pointer to a PIO controller */
    {
        ಹಿಂತಿರುಗಿ pPio->PIO_ISR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsInterruptMasked */
/** \brief Test if PIO Interrupt is Masked */
/**---------------------------------------------------------------------------- */
    __inline ಪೂರ್ಣಾಂಕ AT91_F_PIO_Is_ಅಡಚಣೆ_Masked( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                              ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  flag to be tested */
    {
        ಹಿಂತಿರುಗಿ( AT91_F_PIO_Get_ಅಡಚಣೆ_ಮುಖವಾಡ_ಸ್ಥಿತಿ( pPio ) & flag );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsInterruptSet */
/** \brief Test if PIO Interrupt is Set */
/**---------------------------------------------------------------------------- */
    __inline ಪೂರ್ಣಾಂಕ AT91_F_PIO_Is_ಅಡಚಣೆ_ಗಣ( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                           ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  flag to be tested */
    {
        ಹಿಂತಿರುಗಿ( AT91_F_PIO_Get_ಅಡಚಣೆ_ಸ್ಥಿತಿ( pPio ) & flag );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_MultiDriverEnable */
/** \brief Multi Driver Enable PIO */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PIO_MultiDriverEnable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                               ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  pio to be enabled */
    {
        pPio->PIO_MDER = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_MultiDriverDisable */
/** \brief Multi Driver Disable PIO */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PIO_MultiDriverDisable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                                ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  pio to be disabled */
    {
        pPio->PIO_MDDR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetMultiDriverStatus */
/** \brief Return PIO Multi Driver Status */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_PIO_Get_Multi_Driver_ಸ್ಥಿತಿ( /* \return PIO Multi Driver Status */
        AT91PS_PIO pPio )                                 /* \arg  pointer to a PIO controller */
    {
        ಹಿಂತಿರುಗಿ pPio->PIO_MDSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsMultiDriverSet */
/** \brief Test if PIO MultiDriver is Set */
/**---------------------------------------------------------------------------- */
    __inline ಪೂರ್ಣಾಂಕ AT91_F_PIO_Is_Multi_Driver_ಗಣ( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                             ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  flag to be tested */
    {
        ಹಿಂತಿರುಗಿ( AT91_F_PIO_Get_Multi_Driver_ಸ್ಥಿತಿ( pPio ) & flag );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_A_RegisterSelection */
/** \brief PIO A Register Selection */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91_F_PIO_A_ರಿಜಿಸ್ಟರ್_Selection( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                                 ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  pio A register selection */
    {
        pPio->PIO_ASR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_B_RegisterSelection */
/** \brief PIO B Register Selection */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91_F_PIO_B_ರಿಜಿಸ್ಟರ್_Selection( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                                 ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  pio B register selection */
    {
        pPio->PIO_BSR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_Get_AB_RegisterStatus */
/** \brief Return PIO Interrupt Status */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_PIO_Get_AB_ರಿಜಿಸ್ಟರ್_ಸ್ಥಿತಿ( /* \return PIO AB Register Status */
        AT91PS_PIO pPio )                                  /* \arg  pointer to a PIO controller */
    {
        ಹಿಂತಿರುಗಿ pPio->PIO_ABSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsAB_RegisterSet */
/** \brief Test if PIO AB Register is Set */
/**---------------------------------------------------------------------------- */
    __inline ಪೂರ್ಣಾಂಕ AT91_F_PIO_Is_AB_ರಿಜಿಸ್ಟರ್_ಗಣ( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                             ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  flag to be tested */
    {
        ಹಿಂತಿರುಗಿ( AT91_F_PIO_Get_AB_ರಿಜಿಸ್ಟರ್_ಸ್ಥಿತಿ( pPio ) & flag );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_OutputWriteEnable */
/** \brief Output Write Enable PIO */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PIO_OutputWriteEnable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                               ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  pio output write to be enabled */
    {
        pPio->PIO_OWER = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_OutputWriteDisable */
/** \brief Output Write Disable PIO */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PIO_OutputWriteDisable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                                ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  pio output write to be disabled */
    {
        pPio->PIO_OWDR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetOutputWriteStatus */
/** \brief Return PIO Output Write Status */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_PIO_Get_Output_Write_ಸ್ಥಿತಿ( /* \return PIO Output Write Status */
        AT91PS_PIO pPio )                                 /* \arg  pointer to a PIO controller */
    {
        ಹಿಂತಿರುಗಿ pPio->PIO_OWSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsOutputWriteSet */
/** \brief Test if PIO OutputWrite is Set */
/**---------------------------------------------------------------------------- */
    __inline ಪೂರ್ಣಾಂಕ AT91_F_PIO_Is_Output_Write_ಗಣ( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                             ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  flag to be tested */
    {
        ಹಿಂತಿರುಗಿ( AT91_F_PIO_Get_Output_Write_ಸ್ಥಿತಿ( pPio ) & flag );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetCfgPullup */
/** \brief Return PIO Configuration Pullup */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91F_PIO_GetCfgPullup( /* \return PIO Configuration Pullup */
        AT91PS_PIO pPio )                         /* \arg  pointer to a PIO controller */
    {
        ಹಿಂತಿರುಗಿ pPio->PIO_PPUSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsOutputDataStatusSet */
/** \brief Test if PIO Output Data Status is Set */
/**---------------------------------------------------------------------------- */
    __inline ಪೂರ್ಣಾಂಕ AT91_F_PIO_Is_Output_ದತ್ತಾಂಶ_ಸ್ಥಿತಿ_ಗಣ( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                                  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  flag to be tested */
    {
        ಹಿಂತಿರುಗಿ( AT91_F_PIO_Get_Output_ದತ್ತಾಂಶ_ಸ್ಥಿತಿ( pPio ) & flag );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsCfgPullupStatusSet */
/** \brief Test if PIO Configuration Pullup Status is Set */
/**---------------------------------------------------------------------------- */
    __inline ಪೂರ್ಣಾಂಕ AT91_F_PIO_Is_Cfg_Pullup_ಸ್ಥಿತಿ_ಗಣ( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                                 ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  flag to be tested */
    {
        ಹಿಂತಿರುಗಿ( ~AT91F_PIO_GetCfgPullup( pPio ) & flag );
    }

/* *****************************************************************************
*               SOFTWARE API FOR PMC
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_CfgSysClkEnableReg */
/** \brief Configure the System Clock Enable Register of the PMC controller */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PMC_CfgSysClkEnableReg( AT91PS_PMC pPMC, /* \arg pointer to PMC controller */
                                                ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಬಹುಲಕ_2 )
    {
        /** Write to the SCER register */
        pPMC->PMC_SCER = ಬಹುಲಕ_2;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_CfgSysClkDisableReg */
/** \brief Configure the System Clock Disable Register of the PMC controller */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PMC_CfgSysClkDisableReg( AT91PS_PMC pPMC, /* \arg pointer to PMC controller */
                                                 ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಬಹುಲಕ_2 )
    {
        /** Write to the SCDR register */
        pPMC->PMC_SCDR = ಬಹುಲಕ_2;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_GetSysClkStatusReg */
/** \brief Return the System Clock Status Register of the PMC controller */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_PMC_Get_Sys_Clk_ಸ್ಥಿತಿ_Reg( AT91PS_PMC pPMC /* pointer to a CAN controller */
                                                        )
    {
        ಹಿಂತಿರುಗಿ pPMC->PMC_SCSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_EnablePeriphClock */
/** \brief Enable peripheral clock */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PMC_EnablePeriphClock( AT91PS_PMC pPMC,         /* \arg pointer to PMC controller */
                                               ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ periphIds ) /* \arg IDs of peripherals to enable */
    {
        pPMC->PMC_PCER = periphIds;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_DisablePeriphClock */
/** \brief Disable peripheral clock */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PMC_DisablePeriphClock( AT91PS_PMC pPMC,         /* \arg pointer to PMC controller */
                                                ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ periphIds ) /* \arg IDs of peripherals to enable */
    {
        pPMC->PMC_PCDR = periphIds;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_GetPeriphClock */
/** \brief Get peripheral clock status */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91F_PMC_GetPeriphClock( AT91PS_PMC pPMC ) /* \arg pointer to PMC controller */
    {
        ಹಿಂತಿರುಗಿ pPMC->PMC_PCSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_CfgMainOscillatorReg */
/** \brief Cfg the main oscillator */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_CKGR_CfgMainOscillatorReg( AT91PS_CKGR pCKGR, /* \arg pointer to CKGR controller */
                                                   ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಬಹುಲಕ_2 )
    {
        pCKGR->CKGR_MOR = ಬಹುಲಕ_2;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_GetMainOscillatorReg */
/** \brief Cfg the main oscillator */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91F_CKGR_GetMainOscillatorReg( AT91PS_CKGR pCKGR ) /* \arg pointer to CKGR controller */
    {
        ಹಿಂತಿರುಗಿ pCKGR->CKGR_MOR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_EnableMainOscillator */
/** \brief Enable the main oscillator */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_CKGR_EnableMainOscillator( AT91PS_CKGR pCKGR ) /* \arg pointer to CKGR controller */
    {
        pCKGR->CKGR_MOR |= AT91C_CKGR_MOSCEN;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_DisableMainOscillator */
/** \brief Disable the main oscillator */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_CKGR_DisableMainOscillator( AT91PS_CKGR pCKGR ) /* \arg pointer to CKGR controller */
    {
        pCKGR->CKGR_MOR &= ~AT91C_CKGR_MOSCEN;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_CfgMainOscStartUpTime */
/** \brief Cfg MOR Register according to the main osc startup time */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91_F_CKGR_Cfg_Main_Osc_ಆರಂಭ_ಮೇಲೆ_ಸಮಯ( AT91PS_CKGR pCKGR,         /* \arg pointer to CKGR controller */
                                                    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ startup_ಸಮಯ, /* \arg main osc startup time in microsecond (us) */
                                                    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ slowClock )   /* \arg slowClock in Hz */
    {
        pCKGR->CKGR_MOR &= ~AT91C_CKGR_OSCOUNT;
        pCKGR->CKGR_MOR |= ( ( slowClock * startup_ಸಮಯ ) / ( 8 * 1000000 ) ) << 8;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_GetMainClockFreqReg */
/** \brief Cfg the main oscillator */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91F_CKGR_GetMainClockFreqReg( AT91PS_CKGR pCKGR ) /* \arg pointer to CKGR controller */
    {
        ಹಿಂತಿರುಗಿ pCKGR->CKGR_MCFR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_GetMainClock */
/** \brief Return Main clock in Hz */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91F_CKGR_GetMainClock( AT91PS_CKGR pCKGR,       /* \arg pointer to CKGR controller */
                                                   ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ slowClock ) /* \arg slowClock in Hz */
    {
        ಹಿಂತಿರುಗಿ ( ( pCKGR->CKGR_MCFR & AT91C_CKGR_MAINF ) * slowClock ) >> 4;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_CfgMCKReg */
/** \brief Cfg Master Clock Register */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PMC_CfgMCKReg( AT91PS_PMC pPMC, /* \arg pointer to PMC controller */
                                       ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಬಹುಲಕ_2 )
    {
        pPMC->PMC_MCKR = ಬಹುಲಕ_2;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_GetMCKReg */
/** \brief Return Master Clock Register */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91F_PMC_GetMCKReg( AT91PS_PMC pPMC ) /* \arg pointer to PMC controller */
    {
        ಹಿಂತಿರುಗಿ pPMC->PMC_MCKR;
    }

/**------------------------------------------------------------------------------ */
/** \fn    AT91F_PMC_GetMasterClock */
/** \brief Return master clock in Hz which corresponds to processor clock for ARM7 */
/**------------------------------------------------------------------------------ */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91F_PMC_GetMasterClock( AT91PS_PMC pPMC,         /* \arg pointer to PMC controller */
                                                    AT91PS_CKGR pCKGR,       /* \arg pointer to CKGR controller */
                                                    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ slowClock ) /* \arg slowClock in Hz */
    {
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ reg = pPMC->PMC_MCKR;
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ prescaler = ( 1 << ( ( reg & AT91C_PMC_PRES ) >> 2 ) );
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ pllDivider, pllMultiplier;

        ಆಯ್ಕೆ( reg & AT91C_PMC_CSS )
        {
            ಸ್ಥಿತಿ AT91C_PMC_CSS_SLOW_CLK: /* Slow clock selected */
                ಹಿಂತಿರುಗಿ slowClock / prescaler;

            ಸ್ಥಿತಿ AT91C_PMC_CSS_MAIN_CLK: /* Main clock is selected */
                ಹಿಂತಿರುಗಿ AT91F_CKGR_GetMainClock( pCKGR, slowClock ) / prescaler;

            ಸ್ಥಿತಿ AT91C_PMC_CSS_PLL_CLK: /* PLLB clock is selected */
                reg = pCKGR->CKGR_PLLR;
                pllDivider = ( reg & AT91C_CKGR_DIV );
                pllMultiplier = ( ( reg & AT91C_CKGR_MUL ) >> 16 ) + 1;
                ಹಿಂತಿರುಗಿ AT91F_CKGR_GetMainClock( pCKGR, slowClock ) / pllDivider * pllMultiplier / prescaler;
        }

        ಹಿಂತಿರುಗಿ 0;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_EnablePCK */
/** \brief Enable peripheral clock */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PMC_EnablePCK( AT91PS_PMC pPMC,  /* \arg pointer to PMC controller */
                                       ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ pck, /* \arg Peripheral clock identifier 0 .. 7 */
                                       ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಬಹುಲಕ_2 )
    {
        pPMC->PMC_PCKR[ pck ] = ಬಹುಲಕ_2;
        pPMC->PMC_SCER = ( 1 << pck ) << 8;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_DisablePCK */
/** \brief Enable peripheral clock */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PMC_DisablePCK( AT91PS_PMC pPMC,   /* \arg pointer to PMC controller */
                                        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ pck ) /* \arg Peripheral clock identifier 0 .. 7 */
    {
        pPMC->PMC_SCDR = ( 1 << pck ) << 8;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_EnableIt */
/** \brief Enable PMC interrupt */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PMC_EnableIt( AT91PS_PMC pPMC,    /* pointer to a PMC controller */
                                      ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* IT to be enabled */
    {
        /** Write to the IER register */
        pPMC->PMC_IER = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_DisableIt */
/** \brief Disable PMC interrupt */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_PMC_DisableIt( AT91PS_PMC pPMC,    /* pointer to a PMC controller */
                                       ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* IT to be disabled */
    {
        /** Write to the IDR register */
        pPMC->PMC_IDR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_GetStatus */
/** \brief Return PMC Interrupt Status */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_PMC_Get_ಸ್ಥಿತಿ( /* \return PMC Interrupt Status */
        AT91PS_PMC pPMC )                      /* pointer to a PMC controller */
    {
        ಹಿಂತಿರುಗಿ pPMC->PMC_SR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_GetInterruptMaskStatus */
/** \brief Return PMC Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_PMC_Get_ಅಡಚಣೆ_ಮುಖವಾಡ_ಸ್ಥಿತಿ( /* \return PMC Interrupt Mask Status */
        AT91PS_PMC pPMC )                                   /* pointer to a PMC controller */
    {
        ಹಿಂತಿರುಗಿ pPMC->PMC_IMR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_IsInterruptMasked */
/** \brief Test if PMC Interrupt is Masked */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_PMC_Is_ಅಡಚಣೆ_Masked( AT91PS_PMC pPMC,    /* \arg  pointer to a PMC controller */
                                                       ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  flag to be tested */
    {
        ಹಿಂತಿರುಗಿ( AT91_F_PMC_Get_ಅಡಚಣೆ_ಮುಖವಾಡ_ಸ್ಥಿತಿ( pPMC ) & flag );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_IsStatusSet */
/** \brief Test if PMC Status is Set */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_PMC_Is_ಸ್ಥಿತಿ_ಗಣ( AT91PS_PMC pPMC,    /* \arg  pointer to a PMC controller */
                                                 ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flag ) /* \arg  flag to be tested */
    {
        ಹಿಂತಿರುಗಿ( AT91_F_PMC_Get_ಸ್ಥಿತಿ( pPMC ) & flag );
    } /* *****************************************************************************
      *              SOFTWARE API FOR RSTC
      ***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_RSTSoftReset */
/** \brief Start Software Reset */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_RSTSoftReset( AT91PS_RSTC pRSTC,
                                      ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ reset )
    {
        pRSTC->RSTC_RCR = ( 0xA5000000 | reset );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_RSTSetMode */
/** \brief Set Reset Mode */
/**---------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91_F_RSTSet_ಬಹುಲಕ( AT91PS_RSTC pRSTC,
                                    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಬಹುಲಕ_2 )
    {
        pRSTC->RSTC_RMR = ( 0xA5000000 | ಬಹುಲಕ_2 );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_RSTGetMode */
/** \brief Get Reset Mode */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_RSTGet_ಬಹುಲಕ( AT91PS_RSTC pRSTC )
    {
        ಹಿಂತಿರುಗಿ( pRSTC->RSTC_RMR );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_RSTGetStatus */
/** \brief Get Reset Status */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_RSTGet_ಸ್ಥಿತಿ( AT91PS_RSTC pRSTC )
    {
        ಹಿಂತಿರುಗಿ( pRSTC->RSTC_RSR );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_RSTIsSoftRstActive */
/** \brief Return !=0 if software reset is still not completed */
/**---------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_RSTIs_Soft_Rst_ಸಕ್ರಿಯ( AT91PS_RSTC pRSTC )
    {
        ಹಿಂತಿರುಗಿ( ( pRSTC->RSTC_RSR ) & AT91C_RSTC_SRCMP );
    }

/* *****************************************************************************
*               SOFTWARE API FOR RTTC
***************************************************************************** */
/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_SetRTT_TimeBase() */
/** \brief  Set the RTT prescaler according to the TimeBase in ms */
/**-------------------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_RTTSet_ಸಮಯ_ತಳ( AT91PS_RTTC pRTTC,
                                                ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ms )
    {
        ಆದರೆ( ms > 2000 )
        {
            ಹಿಂತಿರುಗಿ 1; /* AT91C_TIME_OUT_OF_RANGE */
        }

        pRTTC->RTTC_RTMR &= ~0xFFFF;
        pRTTC->RTTC_RTMR |= ( ( ( ms << 15 ) / 1000 ) & 0xFFFF );
        ಹಿಂತಿರುಗಿ 0;
    }

/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_RTTSetPrescaler() */
/** \brief  Set the new prescaler value */
/**-------------------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91F_RTTSetPrescaler( AT91PS_RTTC pRTTC,
                                                 ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ rtpres )
    {
        pRTTC->RTTC_RTMR &= ~0xFFFF;
        pRTTC->RTTC_RTMR |= ( rtpres & 0xFFFF );
        ಹಿಂತಿರುಗಿ( pRTTC->RTTC_RTMR );
    }

/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_RTTRestart() */
/** \brief  Restart the RTT prescaler */
/**-------------------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_RTTRestart( AT91PS_RTTC pRTTC )
    {
        pRTTC->RTTC_RTMR |= AT91C_RTTC_RTTRST;
    }


/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_RTT_SetAlarmINT() */
/** \brief  Enable RTT Alarm Interrupt */
/**-------------------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_RTTSetAlarmINT( AT91PS_RTTC pRTTC )
    {
        pRTTC->RTTC_RTMR |= AT91C_RTTC_ALMIEN;
    }

/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_RTT_ClearAlarmINT() */
/** \brief  Disable RTT Alarm Interrupt */
/**-------------------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_RTTClearAlarmINT( AT91PS_RTTC pRTTC )
    {
        pRTTC->RTTC_RTMR &= ~AT91C_RTTC_ALMIEN;
    }

/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_RTT_SetRttIncINT() */
/** \brief  Enable RTT INC Interrupt */
/**-------------------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_RTTSetRttIncINT( AT91PS_RTTC pRTTC )
    {
        pRTTC->RTTC_RTMR |= AT91C_RTTC_RTTINCIEN;
    }

/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_RTT_ClearRttIncINT() */
/** \brief  Disable RTT INC Interrupt */
/**-------------------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91F_RTTClearRttIncINT( AT91PS_RTTC pRTTC )
    {
        pRTTC->RTTC_RTMR &= ~AT91C_RTTC_RTTINCIEN;
    }

/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_RTT_SetAlarmValue() */
/** \brief  Set RTT Alarm Value */
/**-------------------------------------------------------------------------------------- */
    __inline ಶೂನ್ಯ AT91_F_RTTSet_Alarm_ಮೌಲ್ಯ( AT91PS_RTTC pRTTC,
                                          ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ alarm )
    {
        pRTTC->RTTC_RTAR = alarm;
    }

/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_RTT_GetAlarmValue() */
/** \brief  Get RTT Alarm Value */
/**-------------------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_RTTGet_Alarm_ಮೌಲ್ಯ( AT91PS_RTTC pRTTC )
    {
        ಹಿಂತಿರುಗಿ( pRTTC->RTTC_RTAR );
    }

/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_RTTGetStatus() */
/** \brief  Read the RTT status */
/**-------------------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_RTTGet_ಸ್ಥಿತಿ( AT91PS_RTTC pRTTC )
    {
        ಹಿಂತಿರುಗಿ( pRTTC->RTTC_RTSR );
    }

/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_RTT_ReadValue() */
/** \brief  Read the RTT value */
/**-------------------------------------------------------------------------------------- */
    __inline ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ AT91_F_RTTRead_ಮೌಲ್ಯ( AT91PS_RTTC pRTTC )
    {
        ನೋಂದಣಿ ಅಸ್ಥಿರ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ val1, val2;

        ಮಾಡು
        {
            val1 = pRTTC->RTTC_RTVR;
            val2 = pRTTC->RTTC_RTVR;
        }
        ಆಗ( val1 != val2 );

        ಹಿಂತಿರುಗಿ( val1 );
    }

/* *****************************************************************************
*               SOFTWARE API FOR PITC
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PITInit */
/** \brief System timer init : period in */
