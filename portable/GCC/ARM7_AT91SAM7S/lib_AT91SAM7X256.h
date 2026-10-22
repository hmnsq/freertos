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

#నిర్వచితం_కాకపోతే lib_AT91SAM7X256_H
    #నిర్వచించు lib_AT91SAM7X256_H

/* *****************************************************************************
*               SOFTWARE API FOR AIC
***************************************************************************** */
    #నిర్వచించు AT91C_AIC_BRANCH_OPCODE    ( ( శూన్య ( * )() ) 0xE51FFF20 ) /* ldr, pc, [pc, #-&F20] */

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_ConfigureIt */
/** \brief Interrupt Handler Initialization */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91F_AIC_ConfigureIt( AT91PS_AIC pAic,                /* \arg pointer to the AIC registers */
                                                 గుర్తులేని పూర్ణాంకం irq_id,            /* \arg interrupt number to initialize */
                                                 గుర్తులేని పూర్ణాంకం ప్రాధాన్యత,          /* \arg priority to give to the interrupt */
                                                 గుర్తులేని పూర్ణాంకం src_type,          /* \arg activation and sense of activation */
                                                 శూన్య ( * newHandler )( శూన్య ) ) /* \arg address of the interrupt handler */
    {
        గుర్తులేని పూర్ణాంకం oldHandler;
        గుర్తులేని పూర్ణాంకం ముసుగు;

        oldHandler = pAic->AIC_SVR[ irq_id ];

        ముసుగు = 0x1 << irq_id;
        /** Disable the interrupt on the interrupt controller */
        pAic->AIC_IDCR = ముసుగు;
        /** Save the interrupt handler routine pointer and the interrupt priority */
        pAic->AIC_SVR[ irq_id ] = ( గుర్తులేని పూర్ణాంకం ) newHandler;
        /** Store the Source Mode Register */
        pAic->AIC_SMR[ irq_id ] = src_type | ప్రాధాన్యత;
        /** Clear the interrupt on the interrupt controller */
        pAic->AIC_ICCR = ముసుగు;

        తిరిగి oldHandler;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_EnableIt */
/** \brief Enable corresponding IT number */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_AIC_EnableIt( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                      గుర్తులేని పూర్ణాంకం irq_id ) /* \arg interrupt number to initialize */
    {
        /** Enable the interrupt on the interrupt controller */
        pAic->AIC_IECR = 0x1 << irq_id;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_DisableIt */
/** \brief Disable corresponding IT number */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_AIC_DisableIt( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                       గుర్తులేని పూర్ణాంకం irq_id ) /* \arg interrupt number to initialize */
    {
        గుర్తులేని పూర్ణాంకం ముసుగు = 0x1 << irq_id;

        /** Disable the interrupt on the interrupt controller */
        pAic->AIC_IDCR = ముసుగు;
        /** Clear the interrupt on the Interrupt Controller ( if one is pending ) */
        pAic->AIC_ICCR = ముసుగు;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_ClearIt */
/** \brief Clear corresponding IT number */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_AIC_ClearIt( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                     గుర్తులేని పూర్ణాంకం irq_id ) /* \arg interrupt number to initialize */
    {
        /** Clear the interrupt on the Interrupt Controller ( if one is pending ) */
        pAic->AIC_ICCR = ( 0x1 << irq_id );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_AcknowledgeIt */
/** \brief Acknowledge corresponding IT number */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_AIC_AcknowledgeIt( AT91PS_AIC pAic ) /* \arg pointer to the AIC registers */
    {
        pAic->AIC_EOICR = pAic->AIC_EOICR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_SetExceptionVector */
/** \brief Configure vector handler */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_AIC_సమితి_Exception_సదిశ( గుర్తులేని పూర్ణాంకం * p_సదిశ, /* \arg pointer to the AIC registers */
                                                        శూన్య ( * Handler )() )  /* \arg Interrupt Handler */
    {
        గుర్తులేని పూర్ణాంకం old_సదిశ = *p_సదిశ;

        ఒకవేళ( ( గుర్తులేని పూర్ణాంకం ) Handler == ( గుర్తులేని పూర్ణాంకం ) AT91C_AIC_BRANCH_OPCODE )
        {
            *p_సదిశ = ( గుర్తులేని పూర్ణాంకం ) AT91C_AIC_BRANCH_OPCODE;
        }
        లేకపోతే
        {
            *p_సదిశ = ( ( ( ( ( గుర్తులేని పూర్ణాంకం ) Handler ) - ( ( గుర్తులేని పూర్ణాంకం ) p_సదిశ ) - 0x8 ) >> 2 ) & 0x00FFFFFF ) | 0xEA000000;
        }

        తిరిగి old_సదిశ;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_Trig */
/** \brief Trig an IT */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_AIC_Trig( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                  గుర్తులేని పూర్ణాంకం irq_id ) /* \arg interrupt number */
    {
        pAic->AIC_ISCR = ( 0x1 << irq_id );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_IsActive */
/** \brief Test if an IT is active */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_AIC_Is_చురుకైన( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                              గుర్తులేని పూర్ణాంకం irq_id ) /* \arg Interrupt Number */
    {
        తిరిగి( pAic->AIC_ISR & ( 0x1 << irq_id ) );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_IsPending */
/** \brief Test if an IT is pending */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91F_AIC_IsPending( AT91PS_AIC pAic,      /* \arg pointer to the AIC registers */
                                               గుర్తులేని పూర్ణాంకం irq_id ) /* \arg Interrupt Number */
    {
        తిరిగి( pAic->AIC_IPR & ( 0x1 << irq_id ) );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_AIC_Open */
/** \brief Set exception vectors and AIC registers to default values */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_AIC_Open( AT91PS_AIC pAic,              /* \arg pointer to the AIC registers */
                                  శూన్య ( * IrqHandler )(),      /* \arg Default IRQ vector exception */
                                  శూన్య ( * FiqHandler )(),      /* \arg Default FIQ vector exception */
                                  శూన్య ( * DefaultHandler )(),  /* \arg Default Handler set in ISR */
                                  శూన్య ( * SpuriousHandler )(), /* \arg Default Spurious Handler */
                                  గుర్తులేని పూర్ణాంకం protect_బహుళకం )    /* \arg Debug Control Register */
    {
        పూర్ణాంకం i;

        /* Disable all interrupts and set IVR to the default handler */
        కొరకు( i = 0; i < 32; ++i )
        {
            AT91F_AIC_DisableIt( pAic, i );
            AT91F_AIC_ConfigureIt( pAic, i, AT91_C_AIC_పూర్వ_అత్యల్ప, AT91_C_AIC_SRCTYPE_ఎగువ_LEVEL, DefaultHandler );
        }

        /* Set the IRQ exception vector */
        AT91_F_AIC_సమితి_Exception_సదిశ( ( గుర్తులేని పూర్ణాంకం * ) 0x18, IrqHandler );
        /* Set the Fast Interrupt exception vector */
        AT91_F_AIC_సమితి_Exception_సదిశ( ( గుర్తులేని పూర్ణాంకం * ) 0x1C, FiqHandler );

        pAic->AIC_SPU = ( గుర్తులేని పూర్ణాంకం ) SpuriousHandler;
        pAic->AIC_DCR = protect_బహుళకం;
    }

/* *****************************************************************************
*               SOFTWARE API FOR PDC
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_SetNextRx */
/** \brief Set the next receive transfer descriptor */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91_F_PDC_సమితి_తదుపరి_Rx( AT91PS_PDC pPDC,     /* \arg pointer to a PDC controller */
                                       అక్షరం * చిరునామా_2,      /* \arg address to the next block to be received */
                                       గుర్తులేని పూర్ణాంకం బైట్లు_2 ) /* \arg number of bytes to be received */
    {
        pPDC->PDC_RNPR = ( గుర్తులేని పూర్ణాంకం ) చిరునామా_2;
        pPDC->PDC_RNCR = బైట్లు_2;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_SetNextTx */
/** \brief Set the next transmit transfer descriptor */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91_F_PDC_సమితి_తదుపరి_Tx( AT91PS_PDC pPDC,     /* \arg pointer to a PDC controller */
                                       అక్షరం * చిరునామా_2,      /* \arg address to the next block to be transmitted */
                                       గుర్తులేని పూర్ణాంకం బైట్లు_2 ) /* \arg number of bytes to be transmitted */
    {
        pPDC->PDC_TNPR = ( గుర్తులేని పూర్ణాంకం ) చిరునామా_2;
        pPDC->PDC_TNCR = బైట్లు_2;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_SetRx */
/** \brief Set the receive transfer descriptor */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91_F_PDC_సమితి_Rx( AT91PS_PDC pPDC,     /* \arg pointer to a PDC controller */
                                   అక్షరం * చిరునామా_2,      /* \arg address to the next block to be received */
                                   గుర్తులేని పూర్ణాంకం బైట్లు_2 ) /* \arg number of bytes to be received */
    {
        pPDC->PDC_RPR = ( గుర్తులేని పూర్ణాంకం ) చిరునామా_2;
        pPDC->PDC_RCR = బైట్లు_2;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_SetTx */
/** \brief Set the transmit transfer descriptor */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91_F_PDC_సమితి_Tx( AT91PS_PDC pPDC,     /* \arg pointer to a PDC controller */
                                   అక్షరం * చిరునామా_2,      /* \arg address to the next block to be transmitted */
                                   గుర్తులేని పూర్ణాంకం బైట్లు_2 ) /* \arg number of bytes to be transmitted */
    {
        pPDC->PDC_TPR = ( గుర్తులేని పూర్ణాంకం ) చిరునామా_2;
        pPDC->PDC_TCR = బైట్లు_2;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_EnableTx */
/** \brief Enable transmit */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PDC_EnableTx( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
    {
        pPDC->PDC_PTCR = AT91C_PDC_TXTEN;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_EnableRx */
/** \brief Enable receive */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PDC_EnableRx( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
    {
        pPDC->PDC_PTCR = AT91C_PDC_RXTEN;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_DisableTx */
/** \brief Disable transmit */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PDC_DisableTx( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
    {
        pPDC->PDC_PTCR = AT91C_PDC_TXTDIS;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_DisableRx */
/** \brief Disable receive */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PDC_DisableRx( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
    {
        pPDC->PDC_PTCR = AT91C_PDC_RXTDIS;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_IsTxEmpty */
/** \brief Test if the current transfer descriptor has been sent */
/**---------------------------------------------------------------------------- */
    __inline పూర్ణాంకం AT91_F_PDC_Is_Tx_ఖాళీలు( /* \return return 1 if transfer is complete */
        AT91PS_PDC pPDC )             /* \arg pointer to a PDC controller */
    {
        తిరిగి !( pPDC->PDC_TCR );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_IsNextTxEmpty */
/** \brief Test if the next transfer descriptor has been moved to the current td */
/**---------------------------------------------------------------------------- */
    __inline పూర్ణాంకం AT91_F_PDC_Is_తదుపరి_Tx_ఖాళీలు( /* \return return 1 if transfer is complete */
        AT91PS_PDC pPDC )                 /* \arg pointer to a PDC controller */
    {
        తిరిగి !( pPDC->PDC_TNCR );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_IsRxEmpty */
/** \brief Test if the current transfer descriptor has been filled */
/**---------------------------------------------------------------------------- */
    __inline పూర్ణాంకం AT91_F_PDC_Is_Rx_ఖాళీలు( /* \return return 1 if transfer is complete */
        AT91PS_PDC pPDC )             /* \arg pointer to a PDC controller */
    {
        తిరిగి !( pPDC->PDC_RCR );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_IsNextRxEmpty */
/** \brief Test if the next transfer descriptor has been moved to the current td */
/**---------------------------------------------------------------------------- */
    __inline పూర్ణాంకం AT91_F_PDC_Is_తదుపరి_Rx_ఖాళీలు( /* \return return 1 if transfer is complete */
        AT91PS_PDC pPDC )                 /* \arg pointer to a PDC controller */
    {
        తిరిగి !( pPDC->PDC_RNCR );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_Open */
/** \brief Open PDC: disable TX and RX reset transfer descriptors, re-enable RX and TX */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PDC_Open( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
    {
        /** Disable the RX and TX PDC transfer requests */
        AT91F_PDC_DisableRx( pPDC );
        AT91F_PDC_DisableTx( pPDC );

        /** Reset all Counter register Next buffer first */
        AT91_F_PDC_సమితి_తదుపరి_Tx( pPDC, ( అక్షరం * ) 0, 0 );
        AT91_F_PDC_సమితి_తదుపరి_Rx( pPDC, ( అక్షరం * ) 0, 0 );
        AT91_F_PDC_సమితి_Tx( pPDC, ( అక్షరం * ) 0, 0 );
        AT91_F_PDC_సమితి_Rx( pPDC, ( అక్షరం * ) 0, 0 );

        /** Enable the RX and TX PDC transfer requests */
        AT91F_PDC_EnableRx( pPDC );
        AT91F_PDC_EnableTx( pPDC );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_Close */
/** \brief Close PDC: disable TX and RX reset transfer descriptors */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PDC_Close( AT91PS_PDC pPDC ) /* \arg pointer to a PDC controller */
    {
        /** Disable the RX and TX PDC transfer requests */
        AT91F_PDC_DisableRx( pPDC );
        AT91F_PDC_DisableTx( pPDC );

        /** Reset all Counter register Next buffer first */
        AT91_F_PDC_సమితి_తదుపరి_Tx( pPDC, ( అక్షరం * ) 0, 0 );
        AT91_F_PDC_సమితి_తదుపరి_Rx( pPDC, ( అక్షరం * ) 0, 0 );
        AT91_F_PDC_సమితి_Tx( pPDC, ( అక్షరం * ) 0, 0 );
        AT91_F_PDC_సమితి_Rx( pPDC, ( అక్షరం * ) 0, 0 );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_SendFrame */
/** \brief Close PDC: disable TX and RX reset transfer descriptors */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_PDC_Send_చట్రం( AT91PS_PDC pPDC,
                                               అక్షరం * p_బఫరు,
                                               గుర్తులేని పూర్ణాంకం sz_బఫరు,
                                               అక్షరం * p_తదుపరి_బఫరు,
                                               గుర్తులేని పూర్ణాంకం sz_తదుపరి_బఫరు )
    {
        ఒకవేళ( AT91_F_PDC_Is_Tx_ఖాళీలు( pPDC ) )
        {
            /** Buffer and next buffer can be initialized */
            AT91_F_PDC_సమితి_Tx( pPDC, p_బఫరు, sz_బఫరు );
            AT91_F_PDC_సమితి_తదుపరి_Tx( pPDC, p_తదుపరి_బఫరు, sz_తదుపరి_బఫరు );
            తిరిగి 2;
        }
        లేకపోతే ఒకవేళ( AT91_F_PDC_Is_తదుపరి_Tx_ఖాళీలు( pPDC ) )
        {
            /** Only one buffer can be initialized */
            AT91_F_PDC_సమితి_తదుపరి_Tx( pPDC, p_బఫరు, sz_బఫరు );
            తిరిగి 1;
        }
        లేకపోతే
        {
            /** All buffer are in use... */
            తిరిగి 0;
        }
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PDC_ReceiveFrame */
/** \brief Close PDC: disable TX and RX reset transfer descriptors */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_PDC_Receive_చట్రం( AT91PS_PDC pPDC,
                                                  అక్షరం * p_బఫరు,
                                                  గుర్తులేని పూర్ణాంకం sz_బఫరు,
                                                  అక్షరం * p_తదుపరి_బఫరు,
                                                  గుర్తులేని పూర్ణాంకం sz_తదుపరి_బఫరు )
    {
        ఒకవేళ( AT91_F_PDC_Is_Rx_ఖాళీలు( pPDC ) )
        {
            /** Buffer and next buffer can be initialized */
            AT91_F_PDC_సమితి_Rx( pPDC, p_బఫరు, sz_బఫరు );
            AT91_F_PDC_సమితి_తదుపరి_Rx( pPDC, p_తదుపరి_బఫరు, sz_తదుపరి_బఫరు );
            తిరిగి 2;
        }
        లేకపోతే ఒకవేళ( AT91_F_PDC_Is_తదుపరి_Rx_ఖాళీలు( pPDC ) )
        {
            /** Only one buffer can be initialized */
            AT91_F_PDC_సమితి_తదుపరి_Rx( pPDC, p_బఫరు, sz_బఫరు );
            తిరిగి 1;
        }
        లేకపోతే
        {
            /** All buffer are in use... */
            తిరిగి 0;
        }
    }

/* *****************************************************************************
*               SOFTWARE API FOR DBGU
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_DBGU_InterruptEnable */
/** \brief Enable DBGU Interrupt */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91_F_DBGU_అంతరాయం_Enable( AT91PS_DBGU pDbgu,  /* \arg  pointer to a DBGU controller */
                                              గుర్తులేని పూర్ణాంకం flag ) /* \arg  dbgu interrupt to be enabled */
    {
        pDbgu->DBGU_IER = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_DBGU_InterruptDisable */
/** \brief Disable DBGU Interrupt */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91_F_DBGU_అంతరాయం_Disable( AT91PS_DBGU pDbgu,  /* \arg  pointer to a DBGU controller */
                                               గుర్తులేని పూర్ణాంకం flag ) /* \arg  dbgu interrupt to be disabled */
    {
        pDbgu->DBGU_IDR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_DBGU_GetInterruptMaskStatus */
/** \brief Return DBGU Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_DBGU_Get_అంతరాయం_ముసుగు_స్థితి( /* \return DBGU Interrupt Mask Status */
        AT91PS_DBGU pDbgu )                                  /* \arg  pointer to a DBGU controller */
    {
        తిరిగి pDbgu->DBGU_IMR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_DBGU_IsInterruptMasked */
/** \brief Test if DBGU Interrupt is Masked */
/**---------------------------------------------------------------------------- */
    __inline పూర్ణాంకం AT91_F_DBGU_Is_అంతరాయం_Masked( AT91PS_DBGU pDbgu,  /* \arg  pointer to a DBGU controller */
                                               గుర్తులేని పూర్ణాంకం flag ) /* \arg  flag to be tested */
    {
        తిరిగి( AT91_F_DBGU_Get_అంతరాయం_ముసుగు_స్థితి( pDbgu ) & flag );
    }

/* *****************************************************************************
*               SOFTWARE API FOR PIO
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgPeriph */
/** \brief Enable pins to be derived by peripheral */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PIO_CfgPeriph( AT91PS_PIO pPio,             /* \arg pointer to a PIO controller */
                                       గుర్తులేని పూర్ణాంకం periphAEnable,  /* \arg PERIPH A to enable */
                                       గుర్తులేని పూర్ణాంకం periphBEnable ) /* \arg PERIPH B to enable */

    {
        pPio->PIO_ASR = periphAEnable;
        pPio->PIO_BSR = periphBEnable;
        pPio->PIO_PDR = ( periphAEnable | periphBEnable ); /* Set in Periph mode */
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgOutput */
/** \brief Enable PIO in output mode */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PIO_CfgOutput( AT91PS_PIO pPio,         /* \arg pointer to a PIO controller */
                                       గుర్తులేని పూర్ణాంకం pioEnable ) /* \arg PIO to be enabled */
    {
        pPio->PIO_చొప్పున = pioEnable;                              /* Set in PIO mode */
        pPio->PIO_OER = pioEnable;                              /* Configure in Output */
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgInput */
/** \brief Enable PIO in input mode */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91_F_PIO_Cfg_ఆదానం( AT91PS_PIO pPio,           /* \arg pointer to a PIO controller */
                                      గుర్తులేని పూర్ణాంకం ఆదానం_Enable ) /* \arg PIO to be enabled */
    {
        /* Disable output */
        pPio->PIO_ODR = ఆదానం_Enable;
        pPio->PIO_చొప్పున = ఆదానం_Enable;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgOpendrain */
/** \brief Configure PIO in open drain */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PIO_CfgOpendrain( AT91PS_PIO pPio,              /* \arg pointer to a PIO controller */
                                          గుర్తులేని పూర్ణాంకం multiDrvEnable ) /* \arg pio to be configured in open drain */
    {
        /* Configure the multi-drive option */
        pPio->PIO_MDDR = ~multiDrvEnable;
        pPio->PIO_MDER = multiDrvEnable;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgPullup */
/** \brief Enable pullup on PIO */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PIO_CfgPullup( AT91PS_PIO pPio,            /* \arg pointer to a PIO controller */
                                       గుర్తులేని పూర్ణాంకం pullupEnable ) /* \arg enable pullup on PIO */
    {
        /* Connect or not Pullup */
        pPio->PIO_PPUDR = ~pullupEnable;
        pPio->PIO_PPUER = pullupEnable;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgDirectDrive */
/** \brief Enable direct drive on PIO */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91_F_PIO_Cfg_ప్రత్యక్ష_Drive( AT91PS_PIO pPio,           /* \arg pointer to a PIO controller */
                                            గుర్తులేని పూర్ణాంకం ప్రత్యక్ష_Drive ) /* \arg PIO to be configured with direct drive */

    {
        /* Configure the Direct Drive */
        pPio->PIO_OWDR = ~ప్రత్యక్ష_Drive;
        pPio->PIO_OWER = ప్రత్యక్ష_Drive;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_CfgInputFilter */
/** \brief Enable input filter on input PIO */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91_F_PIO_Cfg_ఆదానం_Filter( AT91PS_PIO pPio,           /* \arg pointer to a PIO controller */
                                            గుర్తులేని పూర్ణాంకం ఆదానం_Filter ) /* \arg PIO to be configured with input filter */

    {
        /* Configure the Direct Drive */
        pPio->PIO_IFDR = ~ఆదానం_Filter;
        pPio->PIO_IFER = ఆదానం_Filter;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetInput */
/** \brief Return PIO input value */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_PIO_Get_ఆదానం( /* \return PIO input */
        AT91PS_PIO pPio )                     /* \arg  pointer to a PIO controller */
    {
        తిరిగి pPio->PIO_PDSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsInputSet */
/** \brief Test if PIO is input flag is active */
/**---------------------------------------------------------------------------- */
    __inline పూర్ణాంకం AT91_F_PIO_Is_ఆదానం_సమితి( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                       గుర్తులేని పూర్ణాంకం flag ) /* \arg  flag to be tested */
    {
        తిరిగి( AT91_F_PIO_Get_ఆదానం( pPio ) & flag );
    }


/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_SetOutput */
/** \brief Set to 1 output PIO */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91_F_PIO_సమితి_Output( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                       గుర్తులేని పూర్ణాంకం flag ) /* \arg  output to be set */
    {
        pPio->PIO_SODR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_ClearOutput */
/** \brief Set to 0 output PIO */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PIO_ClearOutput( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                         గుర్తులేని పూర్ణాంకం flag ) /* \arg  output to be cleared */
    {
        pPio->PIO_CODR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_ForceOutput */
/** \brief Force output when Direct drive option is enabled */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PIO_ForceOutput( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                         గుర్తులేని పూర్ణాంకం flag ) /* \arg  output to be forced */
    {
        pPio->PIO_ODSR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_Enable */
/** \brief Enable PIO */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PIO_Enable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                    గుర్తులేని పూర్ణాంకం flag ) /* \arg  pio to be enabled */
    {
        pPio->PIO_చొప్పున = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_Disable */
/** \brief Disable PIO */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PIO_Disable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                     గుర్తులేని పూర్ణాంకం flag ) /* \arg  pio to be disabled */
    {
        pPio->PIO_PDR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetStatus */
/** \brief Return PIO Status */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_PIO_Get_స్థితి( /* \return PIO Status */
        AT91PS_PIO pPio )                      /* \arg  pointer to a PIO controller */
    {
        తిరిగి pPio->PIO_PSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsSet */
/** \brief Test if PIO is Set */
/**---------------------------------------------------------------------------- */
    __inline పూర్ణాంకం AT91_F_PIO_Is_సమితి( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                  గుర్తులేని పూర్ణాంకం flag ) /* \arg  flag to be tested */
    {
        తిరిగి( AT91_F_PIO_Get_స్థితి( pPio ) & flag );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_OutputEnable */
/** \brief Output Enable PIO */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PIO_OutputEnable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                          గుర్తులేని పూర్ణాంకం flag ) /* \arg  pio output to be enabled */
    {
        pPio->PIO_OER = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_OutputDisable */
/** \brief Output Enable PIO */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PIO_OutputDisable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                           గుర్తులేని పూర్ణాంకం flag ) /* \arg  pio output to be disabled */
    {
        pPio->PIO_ODR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetOutputStatus */
/** \brief Return PIO Output Status */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_PIO_Get_Output_స్థితి( /* \return PIO Output Status */
        AT91PS_PIO pPio )                            /* \arg  pointer to a PIO controller */
    {
        తిరిగి pPio->PIO_OSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsOuputSet */
/** \brief Test if PIO Output is Set */
/**---------------------------------------------------------------------------- */
    __inline పూర్ణాంకం AT91_F_PIO_Is_Output_సమితి( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                        గుర్తులేని పూర్ణాంకం flag ) /* \arg  flag to be tested */
    {
        తిరిగి( AT91_F_PIO_Get_Output_స్థితి( pPio ) & flag );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_InputFilterEnable */
/** \brief Input Filter Enable PIO */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91_F_PIO_ఆదానం_Filter_Enable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                               గుర్తులేని పూర్ణాంకం flag ) /* \arg  pio input filter to be enabled */
    {
        pPio->PIO_IFER = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_InputFilterDisable */
/** \brief Input Filter Disable PIO */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91_F_PIO_ఆదానం_Filter_Disable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                                గుర్తులేని పూర్ణాంకం flag ) /* \arg  pio input filter to be disabled */
    {
        pPio->PIO_IFDR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetInputFilterStatus */
/** \brief Return PIO Input Filter Status */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_PIO_Get_ఆదానం_Filter_స్థితి( /* \return PIO Input Filter Status */
        AT91PS_PIO pPio )                                 /* \arg  pointer to a PIO controller */
    {
        తిరిగి pPio->PIO_IFSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsInputFilterSet */
/** \brief Test if PIO Input filter is Set */
/**---------------------------------------------------------------------------- */
    __inline పూర్ణాంకం AT91_F_PIO_Is_ఆదానం_Filter_సమితి( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                             గుర్తులేని పూర్ణాంకం flag ) /* \arg  flag to be tested */
    {
        తిరిగి( AT91_F_PIO_Get_ఆదానం_Filter_స్థితి( pPio ) & flag );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetOutputDataStatus */
/** \brief Return PIO Output Data Status */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_PIO_Get_Output_దత్తాంశం_స్థితి( /* \return PIO Output Data Status */
        AT91PS_PIO pPio )                                /* \arg  pointer to a PIO controller */
    {
        తిరిగి pPio->PIO_ODSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_InterruptEnable */
/** \brief Enable PIO Interrupt */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91_F_PIO_అంతరాయం_Enable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                             గుర్తులేని పూర్ణాంకం flag ) /* \arg  pio interrupt to be enabled */
    {
        pPio->PIO_IER = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_InterruptDisable */
/** \brief Disable PIO Interrupt */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91_F_PIO_అంతరాయం_Disable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                              గుర్తులేని పూర్ణాంకం flag ) /* \arg  pio interrupt to be disabled */
    {
        pPio->PIO_IDR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetInterruptMaskStatus */
/** \brief Return PIO Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_PIO_Get_అంతరాయం_ముసుగు_స్థితి( /* \return PIO Interrupt Mask Status */
        AT91PS_PIO pPio )                                   /* \arg  pointer to a PIO controller */
    {
        తిరిగి pPio->PIO_IMR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetInterruptStatus */
/** \brief Return PIO Interrupt Status */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_PIO_Get_అంతరాయం_స్థితి( /* \return PIO Interrupt Status */
        AT91PS_PIO pPio )                               /* \arg  pointer to a PIO controller */
    {
        తిరిగి pPio->PIO_ISR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsInterruptMasked */
/** \brief Test if PIO Interrupt is Masked */
/**---------------------------------------------------------------------------- */
    __inline పూర్ణాంకం AT91_F_PIO_Is_అంతరాయం_Masked( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                              గుర్తులేని పూర్ణాంకం flag ) /* \arg  flag to be tested */
    {
        తిరిగి( AT91_F_PIO_Get_అంతరాయం_ముసుగు_స్థితి( pPio ) & flag );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsInterruptSet */
/** \brief Test if PIO Interrupt is Set */
/**---------------------------------------------------------------------------- */
    __inline పూర్ణాంకం AT91_F_PIO_Is_అంతరాయం_సమితి( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                           గుర్తులేని పూర్ణాంకం flag ) /* \arg  flag to be tested */
    {
        తిరిగి( AT91_F_PIO_Get_అంతరాయం_స్థితి( pPio ) & flag );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_MultiDriverEnable */
/** \brief Multi Driver Enable PIO */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PIO_MultiDriverEnable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                               గుర్తులేని పూర్ణాంకం flag ) /* \arg  pio to be enabled */
    {
        pPio->PIO_MDER = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_MultiDriverDisable */
/** \brief Multi Driver Disable PIO */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PIO_MultiDriverDisable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                                గుర్తులేని పూర్ణాంకం flag ) /* \arg  pio to be disabled */
    {
        pPio->PIO_MDDR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetMultiDriverStatus */
/** \brief Return PIO Multi Driver Status */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_PIO_Get_Multi_Driver_స్థితి( /* \return PIO Multi Driver Status */
        AT91PS_PIO pPio )                                 /* \arg  pointer to a PIO controller */
    {
        తిరిగి pPio->PIO_MDSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsMultiDriverSet */
/** \brief Test if PIO MultiDriver is Set */
/**---------------------------------------------------------------------------- */
    __inline పూర్ణాంకం AT91_F_PIO_Is_Multi_Driver_సమితి( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                             గుర్తులేని పూర్ణాంకం flag ) /* \arg  flag to be tested */
    {
        తిరిగి( AT91_F_PIO_Get_Multi_Driver_స్థితి( pPio ) & flag );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_A_RegisterSelection */
/** \brief PIO A Register Selection */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91_F_PIO_A_రిజిస్టరు_Selection( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                                 గుర్తులేని పూర్ణాంకం flag ) /* \arg  pio A register selection */
    {
        pPio->PIO_ASR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_B_RegisterSelection */
/** \brief PIO B Register Selection */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91_F_PIO_B_రిజిస్టరు_Selection( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                                 గుర్తులేని పూర్ణాంకం flag ) /* \arg  pio B register selection */
    {
        pPio->PIO_BSR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_Get_AB_RegisterStatus */
/** \brief Return PIO Interrupt Status */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_PIO_Get_AB_రిజిస్టరు_స్థితి( /* \return PIO AB Register Status */
        AT91PS_PIO pPio )                                  /* \arg  pointer to a PIO controller */
    {
        తిరిగి pPio->PIO_ABSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsAB_RegisterSet */
/** \brief Test if PIO AB Register is Set */
/**---------------------------------------------------------------------------- */
    __inline పూర్ణాంకం AT91_F_PIO_Is_AB_రిజిస్టరు_సమితి( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                             గుర్తులేని పూర్ణాంకం flag ) /* \arg  flag to be tested */
    {
        తిరిగి( AT91_F_PIO_Get_AB_రిజిస్టరు_స్థితి( pPio ) & flag );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_OutputWriteEnable */
/** \brief Output Write Enable PIO */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PIO_OutputWriteEnable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                               గుర్తులేని పూర్ణాంకం flag ) /* \arg  pio output write to be enabled */
    {
        pPio->PIO_OWER = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_OutputWriteDisable */
/** \brief Output Write Disable PIO */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PIO_OutputWriteDisable( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                                గుర్తులేని పూర్ణాంకం flag ) /* \arg  pio output write to be disabled */
    {
        pPio->PIO_OWDR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetOutputWriteStatus */
/** \brief Return PIO Output Write Status */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_PIO_Get_Output_Write_స్థితి( /* \return PIO Output Write Status */
        AT91PS_PIO pPio )                                 /* \arg  pointer to a PIO controller */
    {
        తిరిగి pPio->PIO_OWSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsOutputWriteSet */
/** \brief Test if PIO OutputWrite is Set */
/**---------------------------------------------------------------------------- */
    __inline పూర్ణాంకం AT91_F_PIO_Is_Output_Write_సమితి( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                             గుర్తులేని పూర్ణాంకం flag ) /* \arg  flag to be tested */
    {
        తిరిగి( AT91_F_PIO_Get_Output_Write_స్థితి( pPio ) & flag );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_GetCfgPullup */
/** \brief Return PIO Configuration Pullup */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91F_PIO_GetCfgPullup( /* \return PIO Configuration Pullup */
        AT91PS_PIO pPio )                         /* \arg  pointer to a PIO controller */
    {
        తిరిగి pPio->PIO_PPUSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsOutputDataStatusSet */
/** \brief Test if PIO Output Data Status is Set */
/**---------------------------------------------------------------------------- */
    __inline పూర్ణాంకం AT91_F_PIO_Is_Output_దత్తాంశం_స్థితి_సమితి( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                                  గుర్తులేని పూర్ణాంకం flag ) /* \arg  flag to be tested */
    {
        తిరిగి( AT91_F_PIO_Get_Output_దత్తాంశం_స్థితి( pPio ) & flag );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PIO_IsCfgPullupStatusSet */
/** \brief Test if PIO Configuration Pullup Status is Set */
/**---------------------------------------------------------------------------- */
    __inline పూర్ణాంకం AT91_F_PIO_Is_Cfg_Pullup_స్థితి_సమితి( AT91PS_PIO pPio,    /* \arg  pointer to a PIO controller */
                                                 గుర్తులేని పూర్ణాంకం flag ) /* \arg  flag to be tested */
    {
        తిరిగి( ~AT91F_PIO_GetCfgPullup( pPio ) & flag );
    }

/* *****************************************************************************
*               SOFTWARE API FOR PMC
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_CfgSysClkEnableReg */
/** \brief Configure the System Clock Enable Register of the PMC controller */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PMC_CfgSysClkEnableReg( AT91PS_PMC pPMC, /* \arg pointer to PMC controller */
                                                గుర్తులేని పూర్ణాంకం బహుళకం_2 )
    {
        /** Write to the SCER register */
        pPMC->PMC_SCER = బహుళకం_2;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_CfgSysClkDisableReg */
/** \brief Configure the System Clock Disable Register of the PMC controller */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PMC_CfgSysClkDisableReg( AT91PS_PMC pPMC, /* \arg pointer to PMC controller */
                                                 గుర్తులేని పూర్ణాంకం బహుళకం_2 )
    {
        /** Write to the SCDR register */
        pPMC->PMC_SCDR = బహుళకం_2;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_GetSysClkStatusReg */
/** \brief Return the System Clock Status Register of the PMC controller */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_PMC_Get_Sys_Clk_స్థితి_Reg( AT91PS_PMC pPMC /* pointer to a CAN controller */
                                                        )
    {
        తిరిగి pPMC->PMC_SCSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_EnablePeriphClock */
/** \brief Enable peripheral clock */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PMC_EnablePeriphClock( AT91PS_PMC pPMC,         /* \arg pointer to PMC controller */
                                               గుర్తులేని పూర్ణాంకం periphIds ) /* \arg IDs of peripherals to enable */
    {
        pPMC->PMC_PCER = periphIds;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_DisablePeriphClock */
/** \brief Disable peripheral clock */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PMC_DisablePeriphClock( AT91PS_PMC pPMC,         /* \arg pointer to PMC controller */
                                                గుర్తులేని పూర్ణాంకం periphIds ) /* \arg IDs of peripherals to enable */
    {
        pPMC->PMC_PCDR = periphIds;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_GetPeriphClock */
/** \brief Get peripheral clock status */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91F_PMC_GetPeriphClock( AT91PS_PMC pPMC ) /* \arg pointer to PMC controller */
    {
        తిరిగి pPMC->PMC_PCSR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_CfgMainOscillatorReg */
/** \brief Cfg the main oscillator */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_CKGR_CfgMainOscillatorReg( AT91PS_CKGR pCKGR, /* \arg pointer to CKGR controller */
                                                   గుర్తులేని పూర్ణాంకం బహుళకం_2 )
    {
        pCKGR->CKGR_MOR = బహుళకం_2;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_GetMainOscillatorReg */
/** \brief Cfg the main oscillator */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91F_CKGR_GetMainOscillatorReg( AT91PS_CKGR pCKGR ) /* \arg pointer to CKGR controller */
    {
        తిరిగి pCKGR->CKGR_MOR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_EnableMainOscillator */
/** \brief Enable the main oscillator */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_CKGR_EnableMainOscillator( AT91PS_CKGR pCKGR ) /* \arg pointer to CKGR controller */
    {
        pCKGR->CKGR_MOR |= AT91C_CKGR_MOSCEN;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_DisableMainOscillator */
/** \brief Disable the main oscillator */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_CKGR_DisableMainOscillator( AT91PS_CKGR pCKGR ) /* \arg pointer to CKGR controller */
    {
        pCKGR->CKGR_MOR &= ~AT91C_CKGR_MOSCEN;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_CfgMainOscStartUpTime */
/** \brief Cfg MOR Register according to the main osc startup time */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91_F_CKGR_Cfg_Main_Osc_ప్రారంభం_పైకి_సమయం( AT91PS_CKGR pCKGR,         /* \arg pointer to CKGR controller */
                                                    గుర్తులేని పూర్ణాంకం startup_సమయం, /* \arg main osc startup time in microsecond (us) */
                                                    గుర్తులేని పూర్ణాంకం slowClock )   /* \arg slowClock in Hz */
    {
        pCKGR->CKGR_MOR &= ~AT91C_CKGR_OSCOUNT;
        pCKGR->CKGR_MOR |= ( ( slowClock * startup_సమయం ) / ( 8 * 1000000 ) ) << 8;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_GetMainClockFreqReg */
/** \brief Cfg the main oscillator */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91F_CKGR_GetMainClockFreqReg( AT91PS_CKGR pCKGR ) /* \arg pointer to CKGR controller */
    {
        తిరిగి pCKGR->CKGR_MCFR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_CKGR_GetMainClock */
/** \brief Return Main clock in Hz */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91F_CKGR_GetMainClock( AT91PS_CKGR pCKGR,       /* \arg pointer to CKGR controller */
                                                   గుర్తులేని పూర్ణాంకం slowClock ) /* \arg slowClock in Hz */
    {
        తిరిగి ( ( pCKGR->CKGR_MCFR & AT91C_CKGR_MAINF ) * slowClock ) >> 4;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_CfgMCKReg */
/** \brief Cfg Master Clock Register */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PMC_CfgMCKReg( AT91PS_PMC pPMC, /* \arg pointer to PMC controller */
                                       గుర్తులేని పూర్ణాంకం బహుళకం_2 )
    {
        pPMC->PMC_MCKR = బహుళకం_2;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_GetMCKReg */
/** \brief Return Master Clock Register */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91F_PMC_GetMCKReg( AT91PS_PMC pPMC ) /* \arg pointer to PMC controller */
    {
        తిరిగి pPMC->PMC_MCKR;
    }

/**------------------------------------------------------------------------------ */
/** \fn    AT91F_PMC_GetMasterClock */
/** \brief Return master clock in Hz which corresponds to processor clock for ARM7 */
/**------------------------------------------------------------------------------ */
    __inline గుర్తులేని పూర్ణాంకం AT91F_PMC_GetMasterClock( AT91PS_PMC pPMC,         /* \arg pointer to PMC controller */
                                                    AT91PS_CKGR pCKGR,       /* \arg pointer to CKGR controller */
                                                    గుర్తులేని పూర్ణాంకం slowClock ) /* \arg slowClock in Hz */
    {
        గుర్తులేని పూర్ణాంకం reg = pPMC->PMC_MCKR;
        గుర్తులేని పూర్ణాంకం prescaler = ( 1 << ( ( reg & AT91C_PMC_PRES ) >> 2 ) );
        గుర్తులేని పూర్ణాంకం pllDivider, pllMultiplier;

        ఎంపిక( reg & AT91C_PMC_CSS )
        {
            స్థితి AT91C_PMC_CSS_SLOW_CLK: /* Slow clock selected */
                తిరిగి slowClock / prescaler;

            స్థితి AT91C_PMC_CSS_MAIN_CLK: /* Main clock is selected */
                తిరిగి AT91F_CKGR_GetMainClock( pCKGR, slowClock ) / prescaler;

            స్థితి AT91C_PMC_CSS_PLL_CLK: /* PLLB clock is selected */
                reg = pCKGR->CKGR_PLLR;
                pllDivider = ( reg & AT91C_CKGR_DIV );
                pllMultiplier = ( ( reg & AT91C_CKGR_MUL ) >> 16 ) + 1;
                తిరిగి AT91F_CKGR_GetMainClock( pCKGR, slowClock ) / pllDivider * pllMultiplier / prescaler;
        }

        తిరిగి 0;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_EnablePCK */
/** \brief Enable peripheral clock */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PMC_EnablePCK( AT91PS_PMC pPMC,  /* \arg pointer to PMC controller */
                                       గుర్తులేని పూర్ణాంకం pck, /* \arg Peripheral clock identifier 0 .. 7 */
                                       గుర్తులేని పూర్ణాంకం బహుళకం_2 )
    {
        pPMC->PMC_PCKR[ pck ] = బహుళకం_2;
        pPMC->PMC_SCER = ( 1 << pck ) << 8;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_DisablePCK */
/** \brief Enable peripheral clock */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PMC_DisablePCK( AT91PS_PMC pPMC,   /* \arg pointer to PMC controller */
                                        గుర్తులేని పూర్ణాంకం pck ) /* \arg Peripheral clock identifier 0 .. 7 */
    {
        pPMC->PMC_SCDR = ( 1 << pck ) << 8;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_EnableIt */
/** \brief Enable PMC interrupt */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PMC_EnableIt( AT91PS_PMC pPMC,    /* pointer to a PMC controller */
                                      గుర్తులేని పూర్ణాంకం flag ) /* IT to be enabled */
    {
        /** Write to the IER register */
        pPMC->PMC_IER = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_DisableIt */
/** \brief Disable PMC interrupt */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_PMC_DisableIt( AT91PS_PMC pPMC,    /* pointer to a PMC controller */
                                       గుర్తులేని పూర్ణాంకం flag ) /* IT to be disabled */
    {
        /** Write to the IDR register */
        pPMC->PMC_IDR = flag;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_GetStatus */
/** \brief Return PMC Interrupt Status */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_PMC_Get_స్థితి( /* \return PMC Interrupt Status */
        AT91PS_PMC pPMC )                      /* pointer to a PMC controller */
    {
        తిరిగి pPMC->PMC_SR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_GetInterruptMaskStatus */
/** \brief Return PMC Interrupt Mask Status */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_PMC_Get_అంతరాయం_ముసుగు_స్థితి( /* \return PMC Interrupt Mask Status */
        AT91PS_PMC pPMC )                                   /* pointer to a PMC controller */
    {
        తిరిగి pPMC->PMC_IMR;
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_IsInterruptMasked */
/** \brief Test if PMC Interrupt is Masked */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_PMC_Is_అంతరాయం_Masked( AT91PS_PMC pPMC,    /* \arg  pointer to a PMC controller */
                                                       గుర్తులేని పూర్ణాంకం flag ) /* \arg  flag to be tested */
    {
        తిరిగి( AT91_F_PMC_Get_అంతరాయం_ముసుగు_స్థితి( pPMC ) & flag );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PMC_IsStatusSet */
/** \brief Test if PMC Status is Set */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_PMC_Is_స్థితి_సమితి( AT91PS_PMC pPMC,    /* \arg  pointer to a PMC controller */
                                                 గుర్తులేని పూర్ణాంకం flag ) /* \arg  flag to be tested */
    {
        తిరిగి( AT91_F_PMC_Get_స్థితి( pPMC ) & flag );
    } /* *****************************************************************************
      *              SOFTWARE API FOR RSTC
      ***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_RSTSoftReset */
/** \brief Start Software Reset */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91F_RSTSoftReset( AT91PS_RSTC pRSTC,
                                      గుర్తులేని పూర్ణాంకం reset )
    {
        pRSTC->RSTC_RCR = ( 0xA5000000 | reset );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_RSTSetMode */
/** \brief Set Reset Mode */
/**---------------------------------------------------------------------------- */
    __inline శూన్య AT91_F_RSTSet_బహుళకం( AT91PS_RSTC pRSTC,
                                    గుర్తులేని పూర్ణాంకం బహుళకం_2 )
    {
        pRSTC->RSTC_RMR = ( 0xA5000000 | బహుళకం_2 );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_RSTGetMode */
/** \brief Get Reset Mode */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_RSTGet_బహుళకం( AT91PS_RSTC pRSTC )
    {
        తిరిగి( pRSTC->RSTC_RMR );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_RSTGetStatus */
/** \brief Get Reset Status */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_RSTGet_స్థితి( AT91PS_RSTC pRSTC )
    {
        తిరిగి( pRSTC->RSTC_RSR );
    }

/**---------------------------------------------------------------------------- */
/** \fn    AT91F_RSTIsSoftRstActive */
/** \brief Return !=0 if software reset is still not completed */
/**---------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_RSTIs_Soft_Rst_చురుకైన( AT91PS_RSTC pRSTC )
    {
        తిరిగి( ( pRSTC->RSTC_RSR ) & AT91C_RSTC_SRCMP );
    }

/* *****************************************************************************
*               SOFTWARE API FOR RTTC
***************************************************************************** */
/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_SetRTT_TimeBase() */
/** \brief  Set the RTT prescaler according to the TimeBase in ms */
/**-------------------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_RTTSet_సమయం_పునాది( AT91PS_RTTC pRTTC,
                                                గుర్తులేని పూర్ణాంకం ms )
    {
        ఒకవేళ( ms > 2000 )
        {
            తిరిగి 1; /* AT91C_TIME_OUT_OF_RANGE */
        }

        pRTTC->RTTC_RTMR &= ~0xFFFF;
        pRTTC->RTTC_RTMR |= ( ( ( ms << 15 ) / 1000 ) & 0xFFFF );
        తిరిగి 0;
    }

/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_RTTSetPrescaler() */
/** \brief  Set the new prescaler value */
/**-------------------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91F_RTTSetPrescaler( AT91PS_RTTC pRTTC,
                                                 గుర్తులేని పూర్ణాంకం rtpres )
    {
        pRTTC->RTTC_RTMR &= ~0xFFFF;
        pRTTC->RTTC_RTMR |= ( rtpres & 0xFFFF );
        తిరిగి( pRTTC->RTTC_RTMR );
    }

/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_RTTRestart() */
/** \brief  Restart the RTT prescaler */
/**-------------------------------------------------------------------------------------- */
    __inline శూన్య AT91F_RTTRestart( AT91PS_RTTC pRTTC )
    {
        pRTTC->RTTC_RTMR |= AT91C_RTTC_RTTRST;
    }


/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_RTT_SetAlarmINT() */
/** \brief  Enable RTT Alarm Interrupt */
/**-------------------------------------------------------------------------------------- */
    __inline శూన్య AT91F_RTTSetAlarmINT( AT91PS_RTTC pRTTC )
    {
        pRTTC->RTTC_RTMR |= AT91C_RTTC_ALMIEN;
    }

/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_RTT_ClearAlarmINT() */
/** \brief  Disable RTT Alarm Interrupt */
/**-------------------------------------------------------------------------------------- */
    __inline శూన్య AT91F_RTTClearAlarmINT( AT91PS_RTTC pRTTC )
    {
        pRTTC->RTTC_RTMR &= ~AT91C_RTTC_ALMIEN;
    }

/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_RTT_SetRttIncINT() */
/** \brief  Enable RTT INC Interrupt */
/**-------------------------------------------------------------------------------------- */
    __inline శూన్య AT91F_RTTSetRttIncINT( AT91PS_RTTC pRTTC )
    {
        pRTTC->RTTC_RTMR |= AT91C_RTTC_RTTINCIEN;
    }

/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_RTT_ClearRttIncINT() */
/** \brief  Disable RTT INC Interrupt */
/**-------------------------------------------------------------------------------------- */
    __inline శూన్య AT91F_RTTClearRttIncINT( AT91PS_RTTC pRTTC )
    {
        pRTTC->RTTC_RTMR &= ~AT91C_RTTC_RTTINCIEN;
    }

/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_RTT_SetAlarmValue() */
/** \brief  Set RTT Alarm Value */
/**-------------------------------------------------------------------------------------- */
    __inline శూన్య AT91_F_RTTSet_Alarm_విలువ( AT91PS_RTTC pRTTC,
                                          గుర్తులేని పూర్ణాంకం alarm )
    {
        pRTTC->RTTC_RTAR = alarm;
    }

/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_RTT_GetAlarmValue() */
/** \brief  Get RTT Alarm Value */
/**-------------------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_RTTGet_Alarm_విలువ( AT91PS_RTTC pRTTC )
    {
        తిరిగి( pRTTC->RTTC_RTAR );
    }

/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_RTTGetStatus() */
/** \brief  Read the RTT status */
/**-------------------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_RTTGet_స్థితి( AT91PS_RTTC pRTTC )
    {
        తిరిగి( pRTTC->RTTC_RTSR );
    }

/**-------------------------------------------------------------------------------------- */
/** \fn     AT91F_RTT_ReadValue() */
/** \brief  Read the RTT value */
/**-------------------------------------------------------------------------------------- */
    __inline గుర్తులేని పూర్ణాంకం AT91_F_RTTRead_విలువ( AT91PS_RTTC pRTTC )
    {
        నమోదు అస్థిర గుర్తులేని పూర్ణాంకం val1, val2;

        చేయి
        {
            val1 = pRTTC->RTTC_RTVR;
            val2 = pRTTC->RTTC_RTVR;
        }
        అయితే( val1 != val2 );

        తిరిగి( val1 );
    }

/* *****************************************************************************
*               SOFTWARE API FOR PITC
***************************************************************************** */
/**---------------------------------------------------------------------------- */
/** \fn    AT91F_PITInit */
/** \brief System timer init : period in */
