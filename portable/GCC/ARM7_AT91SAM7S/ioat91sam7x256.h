/* - ---------------------------------------------------------------------------- */
/* -          ATMEL Microcontroller Software Support  -  ROUSSET  - */
/* - ---------------------------------------------------------------------------- */
/* -  DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR */
/* -  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/* -  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE */
/* -  DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT, */
/* -  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* -  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, */
/* -  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF */
/* -  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING */
/* -  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/* -  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
/* - ---------------------------------------------------------------------------- */
/* - File Name           : AT91SAM7X256.h */
/* - Object              : AT91SAM7X256 definitions */
/* - Generated           : AT91 SW Application Group  05/20/2005 (16:22:29) */
/* - */
/* - CVS Reference       : /AT91SAM7X256.pl/1.11/Tue May 10 12:15:32 2005// */
/* - CVS Reference       : /SYS_SAM7X.pl/1.3/Tue Feb  1 17:01:43 2005// */
/* - CVS Reference       : /MC_SAM7X.pl/1.2/Fri May 20 14:13:04 2005// */
/* - CVS Reference       : /PMC_SAM7X.pl/1.4/Tue Feb  8 13:58:10 2005// */
/* - CVS Reference       : /RSTC_SAM7X.pl/1.1/Tue Feb  1 16:16:26 2005// */
/* - CVS Reference       : /UDP_SAM7X.pl/1.1/Tue May 10 11:35:35 2005// */
/* - CVS Reference       : /PWM_SAM7X.pl/1.1/Tue May 10 11:53:07 2005// */
/* - CVS Reference       : /AIC_6075B.pl/1.3/Fri May 20 14:01:30 2005// */
/* - CVS Reference       : /PIO_6057A.pl/1.2/Thu Feb  3 10:18:28 2005// */
/* - CVS Reference       : /RTTC_6081A.pl/1.2/Tue Nov  9 14:43:58 2004// */
/* - CVS Reference       : /PITC_6079A.pl/1.2/Tue Nov  9 14:43:56 2004// */
/* - CVS Reference       : /WDTC_6080A.pl/1.3/Tue Nov  9 14:44:00 2004// */
/* - CVS Reference       : /VREG_6085B.pl/1.1/Tue Feb  1 16:05:48 2005// */
/* - CVS Reference       : /PDC_6074C.pl/1.2/Thu Feb  3 08:48:54 2005// */
/* - CVS Reference       : /DBGU_6059D.pl/1.1/Mon Jan 31 13:15:32 2005// */
/* - CVS Reference       : /SPI_6088D.pl/1.3/Fri May 20 14:08:59 2005// */
/* - CVS Reference       : /US_6089C.pl/1.1/Mon Jul 12 18:23:26 2004// */
/* - CVS Reference       : /SSC_6078A.pl/1.1/Tue Jul 13 07:45:40 2004// */
/* - CVS Reference       : /TWI_6061A.pl/1.1/Tue Jul 13 07:38:06 2004// */
/* - CVS Reference       : /TC_6082A.pl/1.7/Fri Mar 11 12:52:17 2005// */
/* - CVS Reference       : /CAN_6019B.pl/1.1/Tue Mar  8 12:42:22 2005// */
/* - CVS Reference       : /EMACB_6119A.pl/1.5/Thu Feb  3 15:52:04 2005// */
/* - CVS Reference       : /ADC_6051C.pl/1.1/Fri Oct 17 09:12:38 2003// */
/* - CVS Reference       : /AES_6149A.pl/1.10/Mon Feb  7 09:44:25 2005// */
/* - CVS Reference       : /DES3_6150A.pl/1.1/Mon Jan 17 08:34:31 2005// */
/* - ---------------------------------------------------------------------------- */

#నిర్వచితం_కాకపోతే AT91SAM7X256_H
#నిర్వచించు AT91SAM7X256_H

రకనిర్వచనం అస్థిర గుర్తులేని పూర్ణాంకం AT91_REG; /* Hardware register definition */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR System Peripherals */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_SYS
{
    AT91_REG AIC_SMR[ 32 ];     /* Source Mode Register */
    AT91_REG AIC_SVR[ 32 ];     /* Source Vector Register */
    AT91_REG AIC_IVR;           /* IRQ Vector Register */
    AT91_REG AIC_FVR;           /* FIQ Vector Register */
    AT91_REG AIC_ISR;           /* Interrupt Status Register */
    AT91_REG AIC_IPR;           /* Interrupt Pending Register */
    AT91_REG AIC_IMR;           /* Interrupt Mask Register */
    AT91_REG AIC_CISR;          /* Core Interrupt Status Register */
    AT91_REG Reserved0[ 2 ];    /* */
    AT91_REG AIC_IECR;          /* Interrupt Enable Command Register */
    AT91_REG AIC_IDCR;          /* Interrupt Disable Command Register */
    AT91_REG AIC_ICCR;          /* Interrupt Clear Command Register */
    AT91_REG AIC_ISCR;          /* Interrupt Set Command Register */
    AT91_REG AIC_EOICR;         /* End of Interrupt Command Register */
    AT91_REG AIC_SPU;           /* Spurious Vector Register */
    AT91_REG AIC_DCR;           /* Debug Control Register (Protect) */
    AT91_REG Reserved1[ 1 ];    /* */
    AT91_REG AIC_FFER;          /* Fast Forcing Enable Register */
    AT91_REG AIC_FFDR;          /* Fast Forcing Disable Register */
    AT91_REG AIC_FFSR;          /* Fast Forcing Status Register */
    AT91_REG Reserved2[ 45 ];   /* */
    AT91_REG DBGU_CR;           /* Control Register */
    AT91_REG DBGU_MR;           /* Mode Register */
    AT91_REG DBGU_IER;          /* Interrupt Enable Register */
    AT91_REG DBGU_IDR;          /* Interrupt Disable Register */
    AT91_REG DBGU_IMR;          /* Interrupt Mask Register */
    AT91_REG DBGU_CSR;          /* Channel Status Register */
    AT91_REG DBGU_RHR;          /* Receiver Holding Register */
    AT91_REG DBGU_THR;          /* Transmitter Holding Register */
    AT91_REG DBGU_BRGR;         /* Baud Rate Generator Register */
    AT91_REG Reserved3[ 7 ];    /* */
    AT91_REG DBGU_CIDR;         /* Chip ID Register */
    AT91_REG DBGU_EXID;         /* Chip ID Extension Register */
    AT91_REG DBGU_FNTR;         /* Force NTRST Register */
    AT91_REG Reserved4[ 45 ];   /* */
    AT91_REG DBGU_RPR;          /* Receive Pointer Register */
    AT91_REG DBGU_RCR;          /* Receive Counter Register */
    AT91_REG DBGU_TPR;          /* Transmit Pointer Register */
    AT91_REG DBGU_TCR;          /* Transmit Counter Register */
    AT91_REG DBGU_RNPR;         /* Receive Next Pointer Register */
    AT91_REG DBGU_RNCR;         /* Receive Next Counter Register */
    AT91_REG DBGU_TNPR;         /* Transmit Next Pointer Register */
    AT91_REG DBGU_TNCR;         /* Transmit Next Counter Register */
    AT91_REG DBGU_PTCR;         /* PDC Transfer Control Register */
    AT91_REG DBGU_PTSR;         /* PDC Transfer Status Register */
    AT91_REG Reserved5[ 54 ];   /* */
    AT91_REG PIOA_చొప్పున;          /* PIO Enable Register */
    AT91_REG PIOA_PDR;          /* PIO Disable Register */
    AT91_REG PIOA_PSR;          /* PIO Status Register */
    AT91_REG Reserved6[ 1 ];    /* */
    AT91_REG PIOA_OER;          /* Output Enable Register */
    AT91_REG PIOA_ODR;          /* Output Disable Registerr */
    AT91_REG PIOA_OSR;          /* Output Status Register */
    AT91_REG Reserved7[ 1 ];    /* */
    AT91_REG PIOA_IFER;         /* Input Filter Enable Register */
    AT91_REG PIOA_IFDR;         /* Input Filter Disable Register */
    AT91_REG PIOA_IFSR;         /* Input Filter Status Register */
    AT91_REG Reserved8[ 1 ];    /* */
    AT91_REG PIOA_SODR;         /* Set Output Data Register */
    AT91_REG PIOA_CODR;         /* Clear Output Data Register */
    AT91_REG PIOA_ODSR;         /* Output Data Status Register */
    AT91_REG PIOA_PDSR;         /* Pin Data Status Register */
    AT91_REG PIOA_IER;          /* Interrupt Enable Register */
    AT91_REG PIOA_IDR;          /* Interrupt Disable Register */
    AT91_REG PIOA_IMR;          /* Interrupt Mask Register */
    AT91_REG PIOA_ISR;          /* Interrupt Status Register */
    AT91_REG PIOA_MDER;         /* Multi-driver Enable Register */
    AT91_REG PIOA_MDDR;         /* Multi-driver Disable Register */
    AT91_REG PIOA_MDSR;         /* Multi-driver Status Register */
    AT91_REG Reserved9[ 1 ];    /* */
    AT91_REG PIOA_PPUDR;        /* Pull-up Disable Register */
    AT91_REG PIOA_PPUER;        /* Pull-up Enable Register */
    AT91_REG PIOA_PPUSR;        /* Pull-up Status Register */
    AT91_REG Reserved10[ 1 ];   /* */
    AT91_REG PIOA_ASR;          /* Select A Register */
    AT91_REG PIOA_BSR;          /* Select B Register */
    AT91_REG PIOA_ABSR;         /* AB Select Status Register */
    AT91_REG Reserved11[ 9 ];   /* */
    AT91_REG PIOA_OWER;         /* Output Write Enable Register */
    AT91_REG PIOA_OWDR;         /* Output Write Disable Register */
    AT91_REG PIOA_OWSR;         /* Output Write Status Register */
    AT91_REG Reserved12[ 85 ];  /* */
    AT91_REG PIOB_చొప్పున;          /* PIO Enable Register */
    AT91_REG PIOB_PDR;          /* PIO Disable Register */
    AT91_REG PIOB_PSR;          /* PIO Status Register */
    AT91_REG Reserved13[ 1 ];   /* */
    AT91_REG PIOB_OER;          /* Output Enable Register */
    AT91_REG PIOB_ODR;          /* Output Disable Registerr */
    AT91_REG PIOB_OSR;          /* Output Status Register */
    AT91_REG Reserved14[ 1 ];   /* */
    AT91_REG PIOB_IFER;         /* Input Filter Enable Register */
    AT91_REG PIOB_IFDR;         /* Input Filter Disable Register */
    AT91_REG PIOB_IFSR;         /* Input Filter Status Register */
    AT91_REG Reserved15[ 1 ];   /* */
    AT91_REG PIOB_SODR;         /* Set Output Data Register */
    AT91_REG PIOB_CODR;         /* Clear Output Data Register */
    AT91_REG PIOB_ODSR;         /* Output Data Status Register */
    AT91_REG PIOB_PDSR;         /* Pin Data Status Register */
    AT91_REG PIOB_IER;          /* Interrupt Enable Register */
    AT91_REG PIOB_IDR;          /* Interrupt Disable Register */
    AT91_REG PIOB_IMR;          /* Interrupt Mask Register */
    AT91_REG PIOB_ISR;          /* Interrupt Status Register */
    AT91_REG PIOB_MDER;         /* Multi-driver Enable Register */
    AT91_REG PIOB_MDDR;         /* Multi-driver Disable Register */
    AT91_REG PIOB_MDSR;         /* Multi-driver Status Register */
    AT91_REG Reserved16[ 1 ];   /* */
    AT91_REG PIOB_PPUDR;        /* Pull-up Disable Register */
    AT91_REG PIOB_PPUER;        /* Pull-up Enable Register */
    AT91_REG PIOB_PPUSR;        /* Pull-up Status Register */
    AT91_REG Reserved17[ 1 ];   /* */
    AT91_REG PIOB_ASR;          /* Select A Register */
    AT91_REG PIOB_BSR;          /* Select B Register */
    AT91_REG PIOB_ABSR;         /* AB Select Status Register */
    AT91_REG Reserved18[ 9 ];   /* */
    AT91_REG PIOB_OWER;         /* Output Write Enable Register */
    AT91_REG PIOB_OWDR;         /* Output Write Disable Register */
    AT91_REG PIOB_OWSR;         /* Output Write Status Register */
    AT91_REG Reserved19[ 341 ]; /* */
    AT91_REG PMC_SCER;          /* System Clock Enable Register */
    AT91_REG PMC_SCDR;          /* System Clock Disable Register */
    AT91_REG PMC_SCSR;          /* System Clock Status Register */
    AT91_REG Reserved20[ 1 ];   /* */
    AT91_REG PMC_PCER;          /* Peripheral Clock Enable Register */
    AT91_REG PMC_PCDR;          /* Peripheral Clock Disable Register */
    AT91_REG PMC_PCSR;          /* Peripheral Clock Status Register */
    AT91_REG Reserved21[ 1 ];   /* */
    AT91_REG PMC_MOR;           /* Main Oscillator Register */
    AT91_REG PMC_MCFR;          /* Main Clock  Frequency Register */
    AT91_REG Reserved22[ 1 ];   /* */
    AT91_REG PMC_PLLR;          /* PLL Register */
    AT91_REG PMC_MCKR;          /* Master Clock Register */
    AT91_REG Reserved23[ 3 ];   /* */
    AT91_REG PMC_PCKR[ 4 ];     /* Programmable Clock Register */
    AT91_REG Reserved24[ 4 ];   /* */
    AT91_REG PMC_IER;           /* Interrupt Enable Register */
    AT91_REG PMC_IDR;           /* Interrupt Disable Register */
    AT91_REG PMC_SR;            /* Status Register */
    AT91_REG PMC_IMR;           /* Interrupt Mask Register */
    AT91_REG Reserved25[ 36 ];  /* */
    AT91_REG RSTC_RCR;          /* Reset Control Register */
    AT91_REG RSTC_RSR;          /* Reset Status Register */
    AT91_REG RSTC_RMR;          /* Reset Mode Register */
    AT91_REG Reserved26[ 5 ];   /* */
    AT91_REG RTTC_RTMR;         /* Real-time Mode Register */
    AT91_REG RTTC_RTAR;         /* Real-time Alarm Register */
    AT91_REG RTTC_RTVR;         /* Real-time Value Register */
    AT91_REG RTTC_RTSR;         /* Real-time Status Register */
    AT91_REG PITC_PIMR;         /* Period Interval Mode Register */
    AT91_REG PITC_PISR;         /* Period Interval Status Register */
    AT91_REG PITC_PIVR;         /* Period Interval Value Register */
    AT91_REG PITC_PIIR;         /* Period Interval Image Register */
    AT91_REG WDTC_WDCR;         /* Watchdog Control Register */
    AT91_REG WDTC_WDMR;         /* Watchdog Mode Register */
    AT91_REG WDTC_WDSR;         /* Watchdog Status Register */
    AT91_REG Reserved27[ 5 ];   /* */
    AT91_REG VREG_MR;           /* Voltage Regulator Mode Register */
} AT91S_SYS, * AT91PS_SYS;


/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Advanced Interrupt Controller */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_AIC
{
    AT91_REG AIC_SMR[ 32 ];  /* Source Mode Register */
    AT91_REG AIC_SVR[ 32 ];  /* Source Vector Register */
    AT91_REG AIC_IVR;        /* IRQ Vector Register */
    AT91_REG AIC_FVR;        /* FIQ Vector Register */
    AT91_REG AIC_ISR;        /* Interrupt Status Register */
    AT91_REG AIC_IPR;        /* Interrupt Pending Register */
    AT91_REG AIC_IMR;        /* Interrupt Mask Register */
    AT91_REG AIC_CISR;       /* Core Interrupt Status Register */
    AT91_REG Reserved0[ 2 ]; /* */
    AT91_REG AIC_IECR;       /* Interrupt Enable Command Register */
    AT91_REG AIC_IDCR;       /* Interrupt Disable Command Register */
    AT91_REG AIC_ICCR;       /* Interrupt Clear Command Register */
    AT91_REG AIC_ISCR;       /* Interrupt Set Command Register */
    AT91_REG AIC_EOICR;      /* End of Interrupt Command Register */
    AT91_REG AIC_SPU;        /* Spurious Vector Register */
    AT91_REG AIC_DCR;        /* Debug Control Register (Protect) */
    AT91_REG Reserved1[ 1 ]; /* */
    AT91_REG AIC_FFER;       /* Fast Forcing Enable Register */
    AT91_REG AIC_FFDR;       /* Fast Forcing Disable Register */
    AT91_REG AIC_FFSR;       /* Fast Forcing Status Register */
} AT91S_AIC, * AT91PS_AIC;

/* -------- AIC_SMR : (AIC Offset: 0x0) Control Register -------- */
#నిర్వచించు AT91_C_AIC_పూర్వ                            ( ( గుర్తులేని పూర్ణాంకం ) 0x7 << 0 ) /* (AIC) Priority Level */
#నిర్వచించు     AT91_C_AIC_పూర్వ_అత్యల్ప                 ( ( గుర్తులేని పూర్ణాంకం ) 0x0 )      /* (AIC) Lowest priority level */
#నిర్వచించు     AT91_C_AIC_పూర్వ_HIGHEST                ( ( గుర్తులేని పూర్ణాంకం ) 0x7 )      /* (AIC) Highest priority level */
#నిర్వచించు AT91C_AIC_SRCTYPE                          ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 5 ) /* (AIC) Interrupt Source Type */
#నిర్వచించు     AT91_C_AIC_SRCTYPE_INT_ఎగువ_LEVEL       ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 5 ) /* (AIC) Internal Sources Code Label High-level Sensitive */
#నిర్వచించు     AT91_C_AIC_SRCTYPE_EXT_దిగువ_LEVEL        ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 5 ) /* (AIC) External Sources Code Label Low-level Sensitive */
#నిర్వచించు     AT91_C_AIC_SRCTYPE_INT_ధనాత్మక_అంచు    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 ) /* (AIC) Internal Sources Code Label Positive Edge triggered */
#నిర్వచించు     AT91_C_AIC_SRCTYPE_EXT_NEGATIVE_అంచు    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 ) /* (AIC) External Sources Code Label Negative Edge triggered */
#నిర్వచించు     AT91_C_AIC_SRCTYPE_ఎగువ_LEVEL           ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 5 ) /* (AIC) Internal Or External Sources Code Label High-level Sensitive */
#నిర్వచించు     AT91_C_AIC_SRCTYPE_ధనాత్మక_అంచు        ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 5 ) /* (AIC) Internal Or External Sources Code Label Positive Edge triggered */
/* -------- AIC_CISR : (AIC Offset: 0x114) AIC Core Interrupt Status Register -------- */
#నిర్వచించు AT91C_AIC_NFIQ                             ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 ) /* (AIC) NFIQ Status */
#నిర్వచించు AT91C_AIC_NIRQ                             ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 ) /* (AIC) NIRQ Status */
/* -------- AIC_DCR : (AIC Offset: 0x138) AIC Debug Control Register (Protect) -------- */
#నిర్వచించు AT91C_AIC_DCR_PROT                         ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 ) /* (AIC) Protection Mode */
#నిర్వచించు AT91C_AIC_DCR_GMSK                         ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 ) /* (AIC) General Mask */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Peripheral DMA Controller */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_PDC
{
    AT91_REG PDC_RPR;  /* Receive Pointer Register */
    AT91_REG PDC_RCR;  /* Receive Counter Register */
    AT91_REG PDC_TPR;  /* Transmit Pointer Register */
    AT91_REG PDC_TCR;  /* Transmit Counter Register */
    AT91_REG PDC_RNPR; /* Receive Next Pointer Register */
    AT91_REG PDC_RNCR; /* Receive Next Counter Register */
    AT91_REG PDC_TNPR; /* Transmit Next Pointer Register */
    AT91_REG PDC_TNCR; /* Transmit Next Counter Register */
    AT91_REG PDC_PTCR; /* PDC Transfer Control Register */
    AT91_REG PDC_PTSR; /* PDC Transfer Status Register */
} AT91S_PDC, * AT91PS_PDC;

/* -------- PDC_PTCR : (PDC Offset: 0x20) PDC Transfer Control Register -------- */
#నిర్వచించు AT91C_PDC_RXTEN     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 ) /* (PDC) Receiver Transfer Enable */
#నిర్వచించు AT91C_PDC_RXTDIS    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 ) /* (PDC) Receiver Transfer Disable */
#నిర్వచించు AT91C_PDC_TXTEN     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 ) /* (PDC) Transmitter Transfer Enable */
#నిర్వచించు AT91C_PDC_TXTDIS    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 9 ) /* (PDC) Transmitter Transfer Disable */
/* -------- PDC_PTSR : (PDC Offset: 0x24) PDC Transfer Status Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Debug Unit */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_DBGU
{
    AT91_REG DBGU_CR;         /* Control Register */
    AT91_REG DBGU_MR;         /* Mode Register */
    AT91_REG DBGU_IER;        /* Interrupt Enable Register */
    AT91_REG DBGU_IDR;        /* Interrupt Disable Register */
    AT91_REG DBGU_IMR;        /* Interrupt Mask Register */
    AT91_REG DBGU_CSR;        /* Channel Status Register */
    AT91_REG DBGU_RHR;        /* Receiver Holding Register */
    AT91_REG DBGU_THR;        /* Transmitter Holding Register */
    AT91_REG DBGU_BRGR;       /* Baud Rate Generator Register */
    AT91_REG Reserved0[ 7 ];  /* */
    AT91_REG DBGU_CIDR;       /* Chip ID Register */
    AT91_REG DBGU_EXID;       /* Chip ID Extension Register */
    AT91_REG DBGU_FNTR;       /* Force NTRST Register */
    AT91_REG Reserved1[ 45 ]; /* */
    AT91_REG DBGU_RPR;        /* Receive Pointer Register */
    AT91_REG DBGU_RCR;        /* Receive Counter Register */
    AT91_REG DBGU_TPR;        /* Transmit Pointer Register */
    AT91_REG DBGU_TCR;        /* Transmit Counter Register */
    AT91_REG DBGU_RNPR;       /* Receive Next Pointer Register */
    AT91_REG DBGU_RNCR;       /* Receive Next Counter Register */
    AT91_REG DBGU_TNPR;       /* Transmit Next Pointer Register */
    AT91_REG DBGU_TNCR;       /* Transmit Next Counter Register */
    AT91_REG DBGU_PTCR;       /* PDC Transfer Control Register */
    AT91_REG DBGU_PTSR;       /* PDC Transfer Status Register */
} AT91S_DBGU, * AT91PS_DBGU;

/* -------- DBGU_CR : (DBGU Offset: 0x0) Debug Unit Control Register -------- */
#నిర్వచించు AT91C_US_RSTRX                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )  /* (DBGU) Reset Receiver */
#నిర్వచించు AT91C_US_RSTTX                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )  /* (DBGU) Reset Transmitter */
#నిర్వచించు AT91C_US_RXEN                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )  /* (DBGU) Receiver Enable */
#నిర్వచించు AT91C_US_RXDIS                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 )  /* (DBGU) Receiver Disable */
#నిర్వచించు AT91C_US_TXEN                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 6 )  /* (DBGU) Transmitter Enable */
#నిర్వచించు AT91C_US_TXDIS                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )  /* (DBGU) Transmitter Disable */
#నిర్వచించు AT91C_US_RSTSTA                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )  /* (DBGU) Reset Status Bits */
/* -------- DBGU_MR : (DBGU Offset: 0x4) Debug Unit Mode Register -------- */
#నిర్వచించు AT91C_US_PAR                   ( ( గుర్తులేని పూర్ణాంకం ) 0x7 << 9 )  /* (DBGU) Parity type */
#నిర్వచించు     AT91C_US_PAR_EVEN          ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 9 )  /* (DBGU) Even Parity */
#నిర్వచించు     AT91C_US_PAR_ODD           ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 9 )  /* (DBGU) Odd Parity */
#నిర్వచించు     AT91C_US_PAR_SPACE         ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 9 )  /* (DBGU) Parity forced to 0 (Space) */
#నిర్వచించు     AT91C_US_PAR_MARK          ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 9 )  /* (DBGU) Parity forced to 1 (Mark) */
#నిర్వచించు     AT91C_US_PAR_NONE          ( ( గుర్తులేని పూర్ణాంకం ) 0x4 << 9 )  /* (DBGU) No Parity */
#నిర్వచించు     AT91C_US_PAR_MULTI_DROP    ( ( గుర్తులేని పూర్ణాంకం ) 0x6 << 9 )  /* (DBGU) Multi-drop mode */
#నిర్వచించు AT91C_US_CHMODE                ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 14 ) /* (DBGU) Channel Mode */
#నిర్వచించు     AT91_C_US_CHMODE_సాధారణ     ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 14 ) /* (DBGU) Normal Mode: The USART channel operates as an RX/TX USART. */
#నిర్వచించు     AT91C_US_CHMODE_AUTO       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 14 ) /* (DBGU) Automatic Echo: Receiver Data Input is connected to the TXD pin. */
#నిర్వచించు     AT91C_US_CHMODE_LOCAL      ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 14 ) /* (DBGU) Local Loopback: Transmitter Output Signal is connected to Receiver Input Signal. */
#నిర్వచించు     AT91C_US_CHMODE_REMOTE     ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 14 ) /* (DBGU) Remote Loopback: RXD pin is internally connected to TXD pin. */
/* -------- DBGU_IER : (DBGU Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
#నిర్వచించు AT91C_US_RXRDY                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )  /* (DBGU) RXRDY Interrupt */
#నిర్వచించు AT91C_US_TXRDY                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )  /* (DBGU) TXRDY Interrupt */
#నిర్వచించు AT91C_US_ENDRX                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )  /* (DBGU) End of Receive Transfer Interrupt */
#నిర్వచించు AT91C_US_ENDTX                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )  /* (DBGU) End of Transmit Interrupt */
#నిర్వచించు AT91C_US_OVRE                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 )  /* (DBGU) Overrun Interrupt */
#నిర్వచించు AT91_C_US_చట్రం                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 6 )  /* (DBGU) Framing Error Interrupt */
#నిర్వచించు AT91C_US_PARE                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )  /* (DBGU) Parity Error Interrupt */
#నిర్వచించు AT91C_US_TXEMPTY               ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 9 )  /* (DBGU) TXEMPTY Interrupt */
#నిర్వచించు AT91C_US_TXBUFE                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 11 ) /* (DBGU) TXBUFE Interrupt */
#నిర్వచించు AT91C_US_RXBUFF                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 12 ) /* (DBGU) RXBUFF Interrupt */
#నిర్వచించు AT91C_US_COMM_TX               ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 30 ) /* (DBGU) COMM_TX Interrupt */
#నిర్వచించు AT91C_US_COMM_RX               ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 31 ) /* (DBGU) COMM_RX Interrupt */
/* -------- DBGU_IDR : (DBGU Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* -------- DBGU_IMR : (DBGU Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* -------- DBGU_CSR : (DBGU Offset: 0x14) Debug Unit Channel Status Register -------- */
/* -------- DBGU_FNTR : (DBGU Offset: 0x48) Debug Unit FORCE_NTRST Register -------- */
#నిర్వచించు AT91C_US_FORCE_NTRST    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 ) /* (DBGU) Force NTRST in JTAG */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Parallel Input Output Controller */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_PIO
{
    AT91_REG PIO_చొప్పున;        /* PIO Enable Register */
    AT91_REG PIO_PDR;        /* PIO Disable Register */
    AT91_REG PIO_PSR;        /* PIO Status Register */
    AT91_REG Reserved0[ 1 ]; /* */
    AT91_REG PIO_OER;        /* Output Enable Register */
    AT91_REG PIO_ODR;        /* Output Disable Registerr */
    AT91_REG PIO_OSR;        /* Output Status Register */
    AT91_REG Reserved1[ 1 ]; /* */
    AT91_REG PIO_IFER;       /* Input Filter Enable Register */
    AT91_REG PIO_IFDR;       /* Input Filter Disable Register */
    AT91_REG PIO_IFSR;       /* Input Filter Status Register */
    AT91_REG Reserved2[ 1 ]; /* */
    AT91_REG PIO_SODR;       /* Set Output Data Register */
    AT91_REG PIO_CODR;       /* Clear Output Data Register */
    AT91_REG PIO_ODSR;       /* Output Data Status Register */
    AT91_REG PIO_PDSR;       /* Pin Data Status Register */
    AT91_REG PIO_IER;        /* Interrupt Enable Register */
    AT91_REG PIO_IDR;        /* Interrupt Disable Register */
    AT91_REG PIO_IMR;        /* Interrupt Mask Register */
    AT91_REG PIO_ISR;        /* Interrupt Status Register */
    AT91_REG PIO_MDER;       /* Multi-driver Enable Register */
    AT91_REG PIO_MDDR;       /* Multi-driver Disable Register */
    AT91_REG PIO_MDSR;       /* Multi-driver Status Register */
    AT91_REG Reserved3[ 1 ]; /* */
    AT91_REG PIO_PPUDR;      /* Pull-up Disable Register */
    AT91_REG PIO_PPUER;      /* Pull-up Enable Register */
    AT91_REG PIO_PPUSR;      /* Pull-up Status Register */
    AT91_REG Reserved4[ 1 ]; /* */
    AT91_REG PIO_ASR;        /* Select A Register */
    AT91_REG PIO_BSR;        /* Select B Register */
    AT91_REG PIO_ABSR;       /* AB Select Status Register */
    AT91_REG Reserved5[ 9 ]; /* */
    AT91_REG PIO_OWER;       /* Output Write Enable Register */
    AT91_REG PIO_OWDR;       /* Output Write Disable Register */
    AT91_REG PIO_OWSR;       /* Output Write Status Register */
} AT91S_PIO, * AT91PS_PIO;


/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Clock Generator Controller */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_CKGR
{
    AT91_REG CKGR_MOR;       /* Main Oscillator Register */
    AT91_REG CKGR_MCFR;      /* Main Clock  Frequency Register */
    AT91_REG Reserved0[ 1 ]; /* */
    AT91_REG CKGR_PLLR;      /* PLL Register */
} AT91S_CKGR, * AT91PS_CKGR;

/* -------- CKGR_MOR : (CKGR Offset: 0x0) Main Oscillator Register -------- */
#నిర్వచించు AT91C_CKGR_MOSCEN            ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )    /* (CKGR) Main Oscillator Enable */
#నిర్వచించు AT91C_CKGR_OSCBYPASS         ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )    /* (CKGR) Main Oscillator Bypass */
#నిర్వచించు AT91C_CKGR_OSCOUNT           ( ( గుర్తులేని పూర్ణాంకం ) 0xFF << 8 )   /* (CKGR) Main Oscillator Start-up Time */
/* -------- CKGR_MCFR : (CKGR Offset: 0x4) Main Clock Frequency Register -------- */
#నిర్వచించు AT91C_CKGR_MAINF             ( ( గుర్తులేని పూర్ణాంకం ) 0xFFFF << 0 ) /* (CKGR) Main Clock Frequency */
#నిర్వచించు AT91C_CKGR_MAINRDY           ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 )   /* (CKGR) Main Clock Ready */
/* -------- CKGR_PLLR : (CKGR Offset: 0xc) PLL B Register -------- */
#నిర్వచించు AT91C_CKGR_DIV               ( ( గుర్తులేని పూర్ణాంకం ) 0xFF << 0 )   /* (CKGR) Divider Selected */
#నిర్వచించు     AT91C_CKGR_DIV_0         ( ( గుర్తులేని పూర్ణాంకం ) 0x0 )         /* (CKGR) Divider output is 0 */
#నిర్వచించు     AT91C_CKGR_DIV_BYPASS    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 )         /* (CKGR) Divider is bypassed */
#నిర్వచించు AT91C_CKGR_PLLCOUNT          ( ( గుర్తులేని పూర్ణాంకం ) 0x3F << 8 )   /* (CKGR) PLL Counter */
#నిర్వచించు AT91_C_CKGR_బహిర్గతం               ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 14 )   /* (CKGR) PLL Output Frequency Range */
#నిర్వచించు     AT91_C_CKGR_బహిర్గతం_0         ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#నిర్వచించు     AT91_C_CKGR_బహిర్గతం_1         ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#నిర్వచించు     AT91_C_CKGR_బహిర్గతం_2         ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#నిర్వచించు     AT91_C_CKGR_బహిర్గతం_3         ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#నిర్వచించు AT91C_CKGR_MUL               ( ( గుర్తులేని పూర్ణాంకం ) 0x7FF << 16 ) /* (CKGR) PLL Multiplier */
#నిర్వచించు AT91C_CKGR_USBDIV            ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 28 )   /* (CKGR) Divider for USB Clocks */
#నిర్వచించు     AT91C_CKGR_USBDIV_0      ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 28 )   /* (CKGR) Divider output is PLL clock output */
#నిర్వచించు     AT91C_CKGR_USBDIV_1      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 28 )   /* (CKGR) Divider output is PLL clock output divided by 2 */
#నిర్వచించు     AT91C_CKGR_USBDIV_2      ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 28 )   /* (CKGR) Divider output is PLL clock output divided by 4 */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Power Management Controller */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_PMC
{
    AT91_REG PMC_SCER;       /* System Clock Enable Register */
    AT91_REG PMC_SCDR;       /* System Clock Disable Register */
    AT91_REG PMC_SCSR;       /* System Clock Status Register */
    AT91_REG Reserved0[ 1 ]; /* */
    AT91_REG PMC_PCER;       /* Peripheral Clock Enable Register */
    AT91_REG PMC_PCDR;       /* Peripheral Clock Disable Register */
    AT91_REG PMC_PCSR;       /* Peripheral Clock Status Register */
    AT91_REG Reserved1[ 1 ]; /* */
    AT91_REG PMC_MOR;        /* Main Oscillator Register */
    AT91_REG PMC_MCFR;       /* Main Clock  Frequency Register */
    AT91_REG Reserved2[ 1 ]; /* */
    AT91_REG PMC_PLLR;       /* PLL Register */
    AT91_REG PMC_MCKR;       /* Master Clock Register */
    AT91_REG Reserved3[ 3 ]; /* */
    AT91_REG PMC_PCKR[ 4 ];  /* Programmable Clock Register */
    AT91_REG Reserved4[ 4 ]; /* */
    AT91_REG PMC_IER;        /* Interrupt Enable Register */
    AT91_REG PMC_IDR;        /* Interrupt Disable Register */
    AT91_REG PMC_SR;         /* Status Register */
    AT91_REG PMC_IMR;        /* Interrupt Mask Register */
} AT91S_PMC, * AT91PS_PMC;

/* -------- PMC_SCER : (PMC Offset: 0x0) System Clock Enable Register -------- */
#నిర్వచించు AT91C_PMC_PCK     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )  /* (PMC) Processor Clock */
#నిర్వచించు AT91C_PMC_UDP     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )  /* (PMC) USB Device Port Clock */
#నిర్వచించు AT91C_PMC_PCK0    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )  /* (PMC) Programmable Clock Output */
#నిర్వచించు AT91C_PMC_PCK1    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 9 )  /* (PMC) Programmable Clock Output */
#నిర్వచించు AT91C_PMC_PCK2    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 10 ) /* (PMC) Programmable Clock Output */
#నిర్వచించు AT91C_PMC_PCK3    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 11 ) /* (PMC) Programmable Clock Output */
/* -------- PMC_SCDR : (PMC Offset: 0x4) System Clock Disable Register -------- */
/* -------- PMC_SCSR : (PMC Offset: 0x8) System Clock Status Register -------- */
/* -------- CKGR_MOR : (PMC Offset: 0x20) Main Oscillator Register -------- */
/* -------- CKGR_MCFR : (PMC Offset: 0x24) Main Clock Frequency Register -------- */
/* -------- CKGR_PLLR : (PMC Offset: 0x2c) PLL B Register -------- */
/* -------- PMC_MCKR : (PMC Offset: 0x30) Master Clock Register -------- */
#నిర్వచించు AT91C_PMC_CSS                 ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 0 ) /* (PMC) Programmable Clock Selection */
#నిర్వచించు     AT91C_PMC_CSS_SLOW_CLK    ( ( గుర్తులేని పూర్ణాంకం ) 0x0 )      /* (PMC) Slow Clock is selected */
#నిర్వచించు     AT91C_PMC_CSS_MAIN_CLK    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 )      /* (PMC) Main Clock is selected */
#నిర్వచించు     AT91C_PMC_CSS_PLL_CLK     ( ( గుర్తులేని పూర్ణాంకం ) 0x3 )      /* (PMC) Clock from PLL is selected */
#నిర్వచించు AT91C_PMC_PRES                ( ( గుర్తులేని పూర్ణాంకం ) 0x7 << 2 ) /* (PMC) Programmable Clock Prescaler */
#నిర్వచించు     AT91C_PMC_PRES_CLK        ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 2 ) /* (PMC) Selected clock */
#నిర్వచించు     AT91C_PMC_PRES_CLK_2      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 ) /* (PMC) Selected clock divided by 2 */
#నిర్వచించు     AT91C_PMC_PRES_CLK_4      ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 2 ) /* (PMC) Selected clock divided by 4 */
#నిర్వచించు     AT91C_PMC_PRES_CLK_8      ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 2 ) /* (PMC) Selected clock divided by 8 */
#నిర్వచించు     AT91C_PMC_PRES_CLK_16     ( ( గుర్తులేని పూర్ణాంకం ) 0x4 << 2 ) /* (PMC) Selected clock divided by 16 */
#నిర్వచించు     AT91C_PMC_PRES_CLK_32     ( ( గుర్తులేని పూర్ణాంకం ) 0x5 << 2 ) /* (PMC) Selected clock divided by 32 */
#నిర్వచించు     AT91C_PMC_PRES_CLK_64     ( ( గుర్తులేని పూర్ణాంకం ) 0x6 << 2 ) /* (PMC) Selected clock divided by 64 */
/* -------- PMC_PCKR : (PMC Offset: 0x40) Programmable Clock Register -------- */
/* -------- PMC_IER : (PMC Offset: 0x60) PMC Interrupt Enable Register -------- */
#నిర్వచించు AT91C_PMC_MOSCS               ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )  /* (PMC) MOSC Status/Enable/Disable/Mask */
#నిర్వచించు AT91_C_PMC_తాళం                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )  /* (PMC) PLL Status/Enable/Disable/Mask */
#నిర్వచించు AT91C_PMC_MCKRDY              ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )  /* (PMC) MCK_RDY Status/Enable/Disable/Mask */
#నిర్వచించు AT91C_PMC_PCK0RDY             ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )  /* (PMC) PCK0_RDY Status/Enable/Disable/Mask */
#నిర్వచించు AT91C_PMC_PCK1RDY             ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 9 )  /* (PMC) PCK1_RDY Status/Enable/Disable/Mask */
#నిర్వచించు AT91C_PMC_PCK2RDY             ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 10 ) /* (PMC) PCK2_RDY Status/Enable/Disable/Mask */
#నిర్వచించు AT91C_PMC_PCK3RDY             ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 11 ) /* (PMC) PCK3_RDY Status/Enable/Disable/Mask */
/* -------- PMC_IDR : (PMC Offset: 0x64) PMC Interrupt Disable Register -------- */
/* -------- PMC_SR : (PMC Offset: 0x68) PMC Status Register -------- */
/* -------- PMC_IMR : (PMC Offset: 0x6c) PMC Interrupt Mask Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Reset Controller Interface */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_RSTC
{
    AT91_REG RSTC_RCR; /* Reset Control Register */
    AT91_REG RSTC_RSR; /* Reset Status Register */
    AT91_REG RSTC_RMR; /* Reset Mode Register */
} AT91S_RSTC, * AT91PS_RSTC;

/* -------- RSTC_RCR : (RSTC Offset: 0x0) Reset Control Register -------- */
#నిర్వచించు AT91C_RSTC_PROCRST                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )   /* (RSTC) Processor Reset */
#నిర్వచించు AT91C_RSTC_PERRST                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )   /* (RSTC) Peripheral Reset */
#నిర్వచించు AT91C_RSTC_EXTRST                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )   /* (RSTC) External Reset */
#నిర్వచించు AT91_C_RSTC_కీలకం                    ( ( గుర్తులేని పూర్ణాంకం ) 0xFF << 24 ) /* (RSTC) Password */
/* -------- RSTC_RSR : (RSTC Offset: 0x4) Reset Status Register -------- */
#నిర్వచించు AT91C_RSTC_URSTS                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )   /* (RSTC) User Reset Status */
#నిర్వచించు AT91C_RSTC_BODSTS                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )   /* (RSTC) Brownout Detection Status */
#నిర్వచించు AT91C_RSTC_RSTTYP                 ( ( గుర్తులేని పూర్ణాంకం ) 0x7 << 8 )   /* (RSTC) Reset Type */
#నిర్వచించు     AT91C_RSTC_RSTTYP_POWERUP     ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 8 )   /* (RSTC) Power-up Reset. VDDCORE rising. */
#నిర్వచించు     AT91C_RSTC_RSTTYP_WAKEUP      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )   /* (RSTC) WakeUp Reset. VDDCORE rising. */
#నిర్వచించు     AT91C_RSTC_RSTTYP_WATCHDOG    ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 8 )   /* (RSTC) Watchdog Reset. Watchdog overflow occurred. */
#నిర్వచించు     AT91C_RSTC_RSTTYP_SOFTWARE    ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 8 )   /* (RSTC) Software Reset. Processor reset required by the software. */
#నిర్వచించు     AT91C_RSTC_RSTTYP_USER        ( ( గుర్తులేని పూర్ణాంకం ) 0x4 << 8 )   /* (RSTC) User Reset. NRST pin detected low. */
#నిర్వచించు     AT91C_RSTC_RSTTYP_BROWNOUT    ( ( గుర్తులేని పూర్ణాంకం ) 0x5 << 8 )   /* (RSTC) Brownout Reset occurred. */
#నిర్వచించు AT91C_RSTC_NRSTL                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 )  /* (RSTC) NRST pin level */
#నిర్వచించు AT91C_RSTC_SRCMP                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 17 )  /* (RSTC) Software Reset Command in Progress. */
/* -------- RSTC_RMR : (RSTC Offset: 0x8) Reset Mode Register -------- */
#నిర్వచించు AT91C_RSTC_URSTEN                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )   /* (RSTC) User Reset Enable */
#నిర్వచించు AT91C_RSTC_URSTIEN                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )   /* (RSTC) User Reset Interrupt Enable */
#నిర్వచించు AT91C_RSTC_ERSTL                  ( ( గుర్తులేని పూర్ణాంకం ) 0xF << 8 )   /* (RSTC) User Reset Enable */
#నిర్వచించు AT91C_RSTC_BODIEN                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 )  /* (RSTC) Brownout Detection Interrupt Enable */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Real Time Timer Controller Interface */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_RTTC
{
    AT91_REG RTTC_RTMR; /* Real-time Mode Register */
    AT91_REG RTTC_RTAR; /* Real-time Alarm Register */
    AT91_REG RTTC_RTVR; /* Real-time Value Register */
    AT91_REG RTTC_RTSR; /* Real-time Status Register */
} AT91S_RTTC, * AT91PS_RTTC;

/* -------- RTTC_RTMR : (RTTC Offset: 0x0) Real-time Mode Register -------- */
#నిర్వచించు AT91C_RTTC_RTPRES       ( ( గుర్తులేని పూర్ణాంకం ) 0xFFFF << 0 ) /* (RTTC) Real-time Timer Prescaler Value */
#నిర్వచించు AT91C_RTTC_ALMIEN       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 )   /* (RTTC) Alarm Interrupt Enable */
#నిర్వచించు AT91C_RTTC_RTTINCIEN    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 17 )   /* (RTTC) Real Time Timer Increment Interrupt Enable */
#నిర్వచించు AT91C_RTTC_RTTRST       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 18 )   /* (RTTC) Real Time Timer Restart */
/* -------- RTTC_RTAR : (RTTC Offset: 0x4) Real-time Alarm Register -------- */
#నిర్వచించు AT91C_RTTC_ALMV         ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 0 )    /* (RTTC) Alarm Value */
/* -------- RTTC_RTVR : (RTTC Offset: 0x8) Current Real-time Value Register -------- */
#నిర్వచించు AT91C_RTTC_CRTV         ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 0 )    /* (RTTC) Current Real-time Value */
/* -------- RTTC_RTSR : (RTTC Offset: 0xc) Real-time Status Register -------- */
#నిర్వచించు AT91C_RTTC_ALMS         ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )    /* (RTTC) Real-time Alarm Status */
#నిర్వచించు AT91C_RTTC_RTTINC       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )    /* (RTTC) Real-time Timer Increment */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Periodic Interval Timer Controller Interface */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_PITC
{
    AT91_REG PITC_PIMR; /* Period Interval Mode Register */
    AT91_REG PITC_PISR; /* Period Interval Status Register */
    AT91_REG PITC_PIVR; /* Period Interval Value Register */
    AT91_REG PITC_PIIR; /* Period Interval Image Register */
} AT91S_PITC, * AT91PS_PITC;

/* -------- PITC_PIMR : (PITC Offset: 0x0) Periodic Interval Mode Register -------- */
#నిర్వచించు AT91C_PITC_PIV       ( ( గుర్తులేని పూర్ణాంకం ) 0xFFFFF << 0 ) /* (PITC) Periodic Interval Value */
#నిర్వచించు AT91C_PITC_PITEN     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 24 )    /* (PITC) Periodic Interval Timer Enabled */
#నిర్వచించు AT91C_PITC_PITIEN    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 25 )    /* (PITC) Periodic Interval Timer Interrupt Enable */
/* -------- PITC_PISR : (PITC Offset: 0x4) Periodic Interval Status Register -------- */
#నిర్వచించు AT91C_PITC_PITS      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )     /* (PITC) Periodic Interval Timer Status */
/* -------- PITC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register -------- */
#నిర్వచించు AT91C_PITC_CPIV      ( ( గుర్తులేని పూర్ణాంకం ) 0xFFFFF << 0 ) /* (PITC) Current Periodic Interval Value */
#నిర్వచించు AT91C_PITC_PICNT     ( ( గుర్తులేని పూర్ణాంకం ) 0xFFF << 20 )  /* (PITC) Periodic Interval Counter */
/* -------- PITC_PIIR : (PITC Offset: 0xc) Periodic Interval Image Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Watchdog Timer Controller Interface */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_WDTC
{
    AT91_REG WDTC_WDCR; /* Watchdog Control Register */
    AT91_REG WDTC_WDMR; /* Watchdog Mode Register */
    AT91_REG WDTC_WDSR; /* Watchdog Status Register */
} AT91S_WDTC, * AT91PS_WDTC;

/* -------- WDTC_WDCR : (WDTC Offset: 0x0) Periodic Interval Image Register -------- */
#నిర్వచించు AT91C_WDTC_WDRSTT       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )    /* (WDTC) Watchdog Restart */
#నిర్వచించు AT91_C_WDTC_కీలకం          ( ( గుర్తులేని పూర్ణాంకం ) 0xFF << 24 )  /* (WDTC) Watchdog KEY Password */
/* -------- WDTC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register -------- */
#నిర్వచించు AT91C_WDTC_WDV          ( ( గుర్తులేని పూర్ణాంకం ) 0xFFF << 0 )  /* (WDTC) Watchdog Timer Restart */
#నిర్వచించు AT91C_WDTC_WDFIEN       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 12 )   /* (WDTC) Watchdog Fault Interrupt Enable */
#నిర్వచించు AT91C_WDTC_WDRSTEN      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 13 )   /* (WDTC) Watchdog Reset Enable */
#నిర్వచించు AT91C_WDTC_WDRPROC      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 14 )   /* (WDTC) Watchdog Timer Restart */
#నిర్వచించు AT91C_WDTC_WDDIS        ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 15 )   /* (WDTC) Watchdog Disable */
#నిర్వచించు AT91C_WDTC_WDD          ( ( గుర్తులేని పూర్ణాంకం ) 0xFFF << 16 ) /* (WDTC) Watchdog Delta Value */
#నిర్వచించు AT91C_WDTC_WDDBGHLT     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 28 )   /* (WDTC) Watchdog Debug Halt */
#నిర్వచించు AT91C_WDTC_WDIDLEHLT    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 29 )   /* (WDTC) Watchdog Idle Halt */
/* -------- WDTC_WDSR : (WDTC Offset: 0x8) Watchdog Status Register -------- */
#నిర్వచించు AT91C_WDTC_WDUNF        ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )    /* (WDTC) Watchdog Underflow */
#నిర్వచించు AT91C_WDTC_WDERR        ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )    /* (WDTC) Watchdog Error */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Voltage Regulator Mode Controller Interface */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_VREG
{
    AT91_REG VREG_MR; /* Voltage Regulator Mode Register */
} AT91S_VREG, * AT91PS_VREG;

/* -------- VREG_MR : (VREG Offset: 0x0) Voltage Regulator Mode Register -------- */
#నిర్వచించు AT91C_VREG_PSTDBY    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 ) /* (VREG) Voltage Regulator Power Standby Mode */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Memory Controller Interface */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_MC
{
    AT91_REG MC_RCR;          /* MC Remap Control Register */
    AT91_REG MC_ASR;          /* MC Abort Status Register */
    AT91_REG MC_AASR;         /* MC Abort Address Status Register */
    AT91_REG Reserved0[ 21 ]; /* */
    AT91_REG MC_FMR;          /* MC Flash Mode Register */
    AT91_REG MC_FCR;          /* MC Flash Command Register */
    AT91_REG MC_FSR;          /* MC Flash Status Register */
} AT91S_MC, * AT91PS_MC;

/* -------- MC_RCR : (MC Offset: 0x0) MC Remap Control Register -------- */
#నిర్వచించు AT91C_MC_RCB                       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )   /* (MC) Remap Command Bit */
/* -------- MC_ASR : (MC Offset: 0x4) MC Abort Status Register -------- */
#నిర్వచించు AT91C_MC_UNDADD                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )   /* (MC) Undefined Address Abort Status */
#నిర్వచించు AT91C_MC_MISADD                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )   /* (MC) Misaligned Address Abort Status */
#నిర్వచించు AT91C_MC_ABTSZ                     ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 8 )   /* (MC) Abort Size Status */
#నిర్వచించు     AT91C_MC_ABTSZ_BYTE            ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 8 )   /* (MC) Byte */
#నిర్వచించు     AT91C_MC_ABTSZ_HWORD           ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )   /* (MC) Half-word */
#నిర్వచించు     AT91_C_MC_ABTSZ_మాట            ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 8 )   /* (MC) Word */
#నిర్వచించు AT91C_MC_ABTTYP                    ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 10 )  /* (MC) Abort Type Status */
#నిర్వచించు     AT91C_MC_ABTTYP_DATAR          ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 10 )  /* (MC) Data Read */
#నిర్వచించు     AT91C_MC_ABTTYP_DATAW          ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 10 )  /* (MC) Data Write */
#నిర్వచించు     AT91C_MC_ABTTYP_FETCH          ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 10 )  /* (MC) Code Fetch */
#నిర్వచించు AT91C_MC_MST0                      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 )  /* (MC) Master 0 Abort Source */
#నిర్వచించు AT91C_MC_MST1                      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 17 )  /* (MC) Master 1 Abort Source */
#నిర్వచించు AT91C_MC_SVMST0                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 24 )  /* (MC) Saved Master 0 Abort Source */
#నిర్వచించు AT91C_MC_SVMST1                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 25 )  /* (MC) Saved Master 1 Abort Source */
/* -------- MC_FMR : (MC Offset: 0x60) MC Flash Mode Register -------- */
#నిర్వచించు AT91C_MC_FRDY                      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )   /* (MC) Flash Ready */
#నిర్వచించు AT91C_MC_LOCKE                     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )   /* (MC) Lock Error */
#నిర్వచించు AT91C_MC_PROGE                     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )   /* (MC) Programming Error */
#నిర్వచించు AT91C_MC_NEBP                      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )   /* (MC) No Erase Before Programming */
#నిర్వచించు AT91C_MC_FWS                       ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 8 )   /* (MC) Flash Wait State */
#నిర్వచించు     AT91C_MC_FWS_0FWS              ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 8 )   /* (MC) 1 cycle for Read, 2 for Write operations */
#నిర్వచించు     AT91C_MC_FWS_1FWS              ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )   /* (MC) 2 cycles for Read, 3 for Write operations */
#నిర్వచించు     AT91C_MC_FWS_2FWS              ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 8 )   /* (MC) 3 cycles for Read, 4 for Write operations */
#నిర్వచించు     AT91C_MC_FWS_3FWS              ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 8 )   /* (MC) 4 cycles for Read, 4 for Write operations */
#నిర్వచించు AT91C_MC_FMCN                      ( ( గుర్తులేని పూర్ణాంకం ) 0xFF << 16 ) /* (MC) Flash Microsecond Cycle Number */
/* -------- MC_FCR : (MC Offset: 0x64) MC Flash Command Register -------- */
#నిర్వచించు AT91C_MC_FCMD                      ( ( గుర్తులేని పూర్ణాంకం ) 0xF << 0 )   /* (MC) Flash Command */
#నిర్వచించు     AT91_C_MC_FCMD_ప్రారంభం_PROG       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 )        /* (MC) Starts the programming of th epage specified by PAGEN. */
#నిర్వచించు     AT91_C_MC_FCMD_తాళం             ( ( గుర్తులేని పూర్ణాంకం ) 0x2 )        /* (MC) Starts a lock sequence of the sector defined by the bits 4 to 7 of the field PAGEN. */
#నిర్వచించు     AT91_C_MC_FCMD_PROG_AND_తాళం    ( ( గుర్తులేని పూర్ణాంకం ) 0x3 )        /* (MC) The lock sequence automatically happens after the programming sequence is completed. */
#నిర్వచించు     AT91C_MC_FCMD_UNLOCK           ( ( గుర్తులేని పూర్ణాంకం ) 0x4 )        /* (MC) Starts an unlock sequence of the sector defined by the bits 4 to 7 of the field PAGEN. */
#నిర్వచించు     AT91C_MC_FCMD_ERASE_ALL        ( ( గుర్తులేని పూర్ణాంకం ) 0x8 )        /* (MC) Starts the erase of the entire flash.If at least a page is locked, the command is cancelled. */
#నిర్వచించు     AT91_C_MC_FCMD_సమితి_GP_NVM       ( ( గుర్తులేని పూర్ణాంకం ) 0xB )        /* (MC) Set General Purpose NVM bits. */
#నిర్వచించు     AT91C_MC_FCMD_CLR_GP_NVM       ( ( గుర్తులేని పూర్ణాంకం ) 0xD )        /* (MC) Clear General Purpose NVM bits. */
#నిర్వచించు     AT91_C_MC_FCMD_సమితి_SECURITY     ( ( గుర్తులేని పూర్ణాంకం ) 0xF )        /* (MC) Set Security Bit. */
#నిర్వచించు AT91C_MC_PAGEN                     ( ( గుర్తులేని పూర్ణాంకం ) 0x3FF << 8 ) /* (MC) Page Number */
#నిర్వచించు AT91_C_MC_కీలకం                       ( ( గుర్తులేని పూర్ణాంకం ) 0xFF << 24 ) /* (MC) Writing Protect Key */
/* -------- MC_FSR : (MC Offset: 0x68) MC Flash Command Register -------- */
#నిర్వచించు AT91C_MC_SECURITY                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )   /* (MC) Security Bit Status */
#నిర్వచించు AT91C_MC_GPNVM0                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )   /* (MC) Sector 0 Lock Status */
#నిర్వచించు AT91C_MC_GPNVM1                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 9 )   /* (MC) Sector 1 Lock Status */
#నిర్వచించు AT91C_MC_GPNVM2                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 10 )  /* (MC) Sector 2 Lock Status */
#నిర్వచించు AT91C_MC_GPNVM3                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 11 )  /* (MC) Sector 3 Lock Status */
#నిర్వచించు AT91C_MC_GPNVM4                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 12 )  /* (MC) Sector 4 Lock Status */
#నిర్వచించు AT91C_MC_GPNVM5                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 13 )  /* (MC) Sector 5 Lock Status */
#నిర్వచించు AT91C_MC_GPNVM6                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 14 )  /* (MC) Sector 6 Lock Status */
#నిర్వచించు AT91C_MC_GPNVM7                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 15 )  /* (MC) Sector 7 Lock Status */
#నిర్వచించు AT91C_MC_LOCKS0                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 )  /* (MC) Sector 0 Lock Status */
#నిర్వచించు AT91C_MC_LOCKS1                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 17 )  /* (MC) Sector 1 Lock Status */
#నిర్వచించు AT91C_MC_LOCKS2                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 18 )  /* (MC) Sector 2 Lock Status */
#నిర్వచించు AT91C_MC_LOCKS3                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 19 )  /* (MC) Sector 3 Lock Status */
#నిర్వచించు AT91C_MC_LOCKS4                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 20 )  /* (MC) Sector 4 Lock Status */
#నిర్వచించు AT91C_MC_LOCKS5                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 21 )  /* (MC) Sector 5 Lock Status */
#నిర్వచించు AT91C_MC_LOCKS6                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 22 )  /* (MC) Sector 6 Lock Status */
#నిర్వచించు AT91C_MC_LOCKS7                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 23 )  /* (MC) Sector 7 Lock Status */
#నిర్వచించు AT91C_MC_LOCKS8                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 24 )  /* (MC) Sector 8 Lock Status */
#నిర్వచించు AT91C_MC_LOCKS9                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 25 )  /* (MC) Sector 9 Lock Status */
#నిర్వచించు AT91C_MC_LOCKS10                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 26 )  /* (MC) Sector 10 Lock Status */
#నిర్వచించు AT91C_MC_LOCKS11                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 27 )  /* (MC) Sector 11 Lock Status */
#నిర్వచించు AT91C_MC_LOCKS12                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 28 )  /* (MC) Sector 12 Lock Status */
#నిర్వచించు AT91C_MC_LOCKS13                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 29 )  /* (MC) Sector 13 Lock Status */
#నిర్వచించు AT91C_MC_LOCKS14                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 30 )  /* (MC) Sector 14 Lock Status */
#నిర్వచించు AT91C_MC_LOCKS15                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 31 )  /* (MC) Sector 15 Lock Status */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Serial Parallel Interface */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_SPI
{
    AT91_REG SPI_CR;          /* Control Register */
    AT91_REG SPI_MR;          /* Mode Register */
    AT91_REG SPI_RDR;         /* Receive Data Register */
    AT91_REG SPI_TDR;         /* Transmit Data Register */
    AT91_REG SPI_SR;          /* Status Register */
    AT91_REG SPI_IER;         /* Interrupt Enable Register */
    AT91_REG SPI_IDR;         /* Interrupt Disable Register */
    AT91_REG SPI_IMR;         /* Interrupt Mask Register */
    AT91_REG Reserved0[ 4 ];  /* */
    AT91_REG SPI_CSR[ 4 ];    /* Chip Select Register */
    AT91_REG Reserved1[ 48 ]; /* */
    AT91_REG SPI_RPR;         /* Receive Pointer Register */
    AT91_REG SPI_RCR;         /* Receive Counter Register */
    AT91_REG SPI_TPR;         /* Transmit Pointer Register */
    AT91_REG SPI_TCR;         /* Transmit Counter Register */
    AT91_REG SPI_RNPR;        /* Receive Next Pointer Register */
    AT91_REG SPI_RNCR;        /* Receive Next Counter Register */
    AT91_REG SPI_TNPR;        /* Transmit Next Pointer Register */
    AT91_REG SPI_TNCR;        /* Transmit Next Counter Register */
    AT91_REG SPI_PTCR;        /* PDC Transfer Control Register */
    AT91_REG SPI_PTSR;        /* PDC Transfer Status Register */
} AT91S_SPI, * AT91PS_SPI;

/* -------- SPI_CR : (SPI Offset: 0x0) SPI Control Register -------- */
#నిర్వచించు AT91C_SPI_SPIEN              ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )    /* (SPI) SPI Enable */
#నిర్వచించు AT91C_SPI_SPIDIS             ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )    /* (SPI) SPI Disable */
#నిర్వచించు AT91C_SPI_SWRST              ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )    /* (SPI) SPI Software reset */
#నిర్వచించు AT91C_SPI_LASTXFER           ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 24 )   /* (SPI) SPI Last Transfer */
/* -------- SPI_MR : (SPI Offset: 0x4) SPI Mode Register -------- */
#నిర్వచించు AT91C_SPI_MSTR               ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )    /* (SPI) Master/Slave Mode */
#నిర్వచించు AT91C_SPI_PS                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )    /* (SPI) Peripheral Select */
#నిర్వచించు     AT91C_SPI_PS_FIXED       ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 1 )    /* (SPI) Fixed Peripheral Select */
#నిర్వచించు     AT91C_SPI_PS_VARIABLE    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )    /* (SPI) Variable Peripheral Select */
#నిర్వచించు AT91C_SPI_PCSDEC             ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )    /* (SPI) Chip Select Decode */
#నిర్వచించు AT91C_SPI_FDIV               ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )    /* (SPI) Clock Selection */
#నిర్వచించు AT91C_SPI_MODFDIS            ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )    /* (SPI) Mode Fault Detection */
#నిర్వచించు AT91C_SPI_LLB                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )    /* (SPI) Clock Selection */
#నిర్వచించు AT91C_SPI_PCS                ( ( గుర్తులేని పూర్ణాంకం ) 0xF << 16 )   /* (SPI) Peripheral Chip Select */
#నిర్వచించు AT91C_SPI_DLYBCS             ( ( గుర్తులేని పూర్ణాంకం ) 0xFF << 24 )  /* (SPI) Delay Between Chip Selects */
/* -------- SPI_RDR : (SPI Offset: 0x8) Receive Data Register -------- */
#నిర్వచించు AT91C_SPI_RD                 ( ( గుర్తులేని పూర్ణాంకం ) 0xFFFF << 0 ) /* (SPI) Receive Data */
#నిర్వచించు AT91C_SPI_RPCS               ( ( గుర్తులేని పూర్ణాంకం ) 0xF << 16 )   /* (SPI) Peripheral Chip Select Status */
/* -------- SPI_TDR : (SPI Offset: 0xc) Transmit Data Register -------- */
#నిర్వచించు AT91C_SPI_TD                 ( ( గుర్తులేని పూర్ణాంకం ) 0xFFFF << 0 ) /* (SPI) Transmit Data */
#నిర్వచించు AT91C_SPI_TPCS               ( ( గుర్తులేని పూర్ణాంకం ) 0xF << 16 )   /* (SPI) Peripheral Chip Select Status */
/* -------- SPI_SR : (SPI Offset: 0x10) Status Register -------- */
#నిర్వచించు AT91C_SPI_RDRF               ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )    /* (SPI) Receive Data Register Full */
#నిర్వచించు AT91C_SPI_TDRE               ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )    /* (SPI) Transmit Data Register Empty */
#నిర్వచించు AT91C_SPI_MODF               ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )    /* (SPI) Mode Fault Error */
#నిర్వచించు AT91C_SPI_OVRES              ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )    /* (SPI) Overrun Error Status */
#నిర్వచించు AT91C_SPI_ENDRX              ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )    /* (SPI) End of Receiver Transfer */
#నిర్వచించు AT91C_SPI_ENDTX              ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 )    /* (SPI) End of Receiver Transfer */
#నిర్వచించు AT91C_SPI_RXBUFF             ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 6 )    /* (SPI) RXBUFF Interrupt */
#నిర్వచించు AT91C_SPI_TXBUFE             ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )    /* (SPI) TXBUFE Interrupt */
#నిర్వచించు AT91C_SPI_NSSR               ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )    /* (SPI) NSSR Interrupt */
#నిర్వచించు AT91C_SPI_TXEMPTY            ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 9 )    /* (SPI) TXEMPTY Interrupt */
#నిర్వచించు AT91C_SPI_SPIENS             ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 )   /* (SPI) Enable Status */
/* -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- */
/* -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- */
/* -------- SPI_IMR : (SPI Offset: 0x1c) Interrupt Mask Register -------- */
/* -------- SPI_CSR : (SPI Offset: 0x30) Chip Select Register -------- */
#నిర్వచించు AT91C_SPI_CPOL           ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )   /* (SPI) Clock Polarity */
#నిర్వచించు AT91C_SPI_NCPHA          ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )   /* (SPI) Clock Phase */
#నిర్వచించు AT91C_SPI_CSAAT          ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )   /* (SPI) Chip Select Active After Transfer */
#నిర్వచించు AT91_C_SPI_బిట్లు           ( ( గుర్తులేని పూర్ణాంకం ) 0xF << 4 )   /* (SPI) Bits Per Transfer */
#నిర్వచించు     AT91_C_SPI_బిట్లు_8     ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 4 )   /* (SPI) 8 Bits Per transfer */
#నిర్వచించు     AT91_C_SPI_బిట్లు_9     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )   /* (SPI) 9 Bits Per transfer */
#నిర్వచించు     AT91_C_SPI_బిట్లు_10    ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 4 )   /* (SPI) 10 Bits Per transfer */
#నిర్వచించు     AT91_C_SPI_బిట్లు_11    ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 4 )   /* (SPI) 11 Bits Per transfer */
#నిర్వచించు     AT91_C_SPI_బిట్లు_12    ( ( గుర్తులేని పూర్ణాంకం ) 0x4 << 4 )   /* (SPI) 12 Bits Per transfer */
#నిర్వచించు     AT91_C_SPI_బిట్లు_13    ( ( గుర్తులేని పూర్ణాంకం ) 0x5 << 4 )   /* (SPI) 13 Bits Per transfer */
#నిర్వచించు     AT91_C_SPI_బిట్లు_14    ( ( గుర్తులేని పూర్ణాంకం ) 0x6 << 4 )   /* (SPI) 14 Bits Per transfer */
#నిర్వచించు     AT91_C_SPI_బిట్లు_15    ( ( గుర్తులేని పూర్ణాంకం ) 0x7 << 4 )   /* (SPI) 15 Bits Per transfer */
#నిర్వచించు     AT91_C_SPI_బిట్లు_16    ( ( గుర్తులేని పూర్ణాంకం ) 0x8 << 4 )   /* (SPI) 16 Bits Per transfer */
#నిర్వచించు AT91C_SPI_SCBR           ( ( గుర్తులేని పూర్ణాంకం ) 0xFF << 8 )  /* (SPI) Serial Clock Baud Rate */
#నిర్వచించు AT91C_SPI_DLYBS          ( ( గుర్తులేని పూర్ణాంకం ) 0xFF << 16 ) /* (SPI) Delay Before SPCK */
#నిర్వచించు AT91C_SPI_DLYBCT         ( ( గుర్తులేని పూర్ణాంకం ) 0xFF << 24 ) /* (SPI) Delay Between Consecutive Transfers */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Usart */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_USART
{
    AT91_REG US_CR;           /* Control Register */
    AT91_REG US_MR;           /* Mode Register */
    AT91_REG US_IER;          /* Interrupt Enable Register */
    AT91_REG US_IDR;          /* Interrupt Disable Register */
    AT91_REG US_IMR;          /* Interrupt Mask Register */
    AT91_REG US_CSR;          /* Channel Status Register */
    AT91_REG US_RHR;          /* Receiver Holding Register */
    AT91_REG US_THR;          /* Transmitter Holding Register */
    AT91_REG US_BRGR;         /* Baud Rate Generator Register */
    AT91_REG US_RTOR;         /* Receiver Time-out Register */
    AT91_REG US_TTGR;         /* Transmitter Time-guard Register */
    AT91_REG Reserved0[ 5 ];  /* */
    AT91_REG US_FIDI;         /* FI_DI_Ratio Register */
    AT91_REG US_NER;          /* Nb Errors Register */
    AT91_REG Reserved1[ 1 ];  /* */
    AT91_REG US_IF;           /* IRDA_FILTER Register */
    AT91_REG Reserved2[ 44 ]; /* */
    AT91_REG US_RPR;          /* Receive Pointer Register */
    AT91_REG US_RCR;          /* Receive Counter Register */
    AT91_REG US_TPR;          /* Transmit Pointer Register */
    AT91_REG US_TCR;          /* Transmit Counter Register */
    AT91_REG US_RNPR;         /* Receive Next Pointer Register */
    AT91_REG US_RNCR;         /* Receive Next Counter Register */
    AT91_REG US_TNPR;         /* Transmit Next Pointer Register */
    AT91_REG US_TNCR;         /* Transmit Next Counter Register */
    AT91_REG US_PTCR;         /* PDC Transfer Control Register */
    AT91_REG US_PTSR;         /* PDC Transfer Status Register */
} AT91S_USART, * AT91PS_USART;

/* -------- US_CR : (USART Offset: 0x0) Debug Unit Control Register -------- */
#నిర్వచించు AT91C_US_STTBRK                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 9 )  /* (USART) Start Break */
#నిర్వచించు AT91C_US_STPBRK                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 10 ) /* (USART) Stop Break */
#నిర్వచించు AT91C_US_STTTO                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 11 ) /* (USART) Start Time-out */
#నిర్వచించు AT91C_US_SENDA                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 12 ) /* (USART) Send Address */
#నిర్వచించు AT91C_US_RSTIT                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 13 ) /* (USART) Reset Iterations */
#నిర్వచించు AT91C_US_RSTNACK                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 14 ) /* (USART) Reset Non Acknowledge */
#నిర్వచించు AT91C_US_RETTO                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 15 ) /* (USART) Rearm Time-out */
#నిర్వచించు AT91C_US_DTREN                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 ) /* (USART) Data Terminal ready Enable */
#నిర్వచించు AT91C_US_DTRDIS                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 17 ) /* (USART) Data Terminal ready Disable */
#నిర్వచించు AT91C_US_RTSEN                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 18 ) /* (USART) Request to Send enable */
#నిర్వచించు AT91C_US_RTSDIS                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 19 ) /* (USART) Request to Send Disable */
/* -------- US_MR : (USART Offset: 0x4) Debug Unit Mode Register -------- */
#నిర్వచించు AT91C_US_USMODE                  ( ( గుర్తులేని పూర్ణాంకం ) 0xF << 0 )  /* (USART) Usart mode */
#నిర్వచించు     AT91_C_US_USMODE_సాధారణ       ( ( గుర్తులేని పూర్ణాంకం ) 0x0 )       /* (USART) Normal */
#నిర్వచించు     AT91C_US_USMODE_RS485        ( ( గుర్తులేని పూర్ణాంకం ) 0x1 )       /* (USART) RS485 */
#నిర్వచించు     AT91C_US_USMODE_HWHSH        ( ( గుర్తులేని పూర్ణాంకం ) 0x2 )       /* (USART) Hardware Handshaking */
#నిర్వచించు     AT91C_US_USMODE_MODEM        ( ( గుర్తులేని పూర్ణాంకం ) 0x3 )       /* (USART) Modem */
#నిర్వచించు     AT91C_US_USMODE_ISO7816_0    ( ( గుర్తులేని పూర్ణాంకం ) 0x4 )       /* (USART) ISO7816 protocol: T = 0 */
#నిర్వచించు     AT91C_US_USMODE_ISO7816_1    ( ( గుర్తులేని పూర్ణాంకం ) 0x6 )       /* (USART) ISO7816 protocol: T = 1 */
#నిర్వచించు     AT91C_US_USMODE_IRDA         ( ( గుర్తులేని పూర్ణాంకం ) 0x8 )       /* (USART) IrDA */
#నిర్వచించు     AT91C_US_USMODE_SWHSH        ( ( గుర్తులేని పూర్ణాంకం ) 0xC )       /* (USART) Software Handshaking */
#నిర్వచించు AT91C_US_CLKS                    ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 4 )  /* (USART) Clock Selection (Baud Rate generator Input Clock */
#నిర్వచించు     AT91C_US_CLKS_CLOCK          ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 4 )  /* (USART) Clock */
#నిర్వచించు     AT91C_US_CLKS_FDIV1          ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )  /* (USART) fdiv1 */
#నిర్వచించు     AT91C_US_CLKS_SLOW           ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 4 )  /* (USART) slow_clock (ARM) */
#నిర్వచించు     AT91C_US_CLKS_EXT            ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 4 )  /* (USART) External (SCK) */
#నిర్వచించు AT91C_US_CHRL                    ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 6 )  /* (USART) Clock Selection (Baud Rate generator Input Clock */
#నిర్వచించు     AT91_C_US_CHRL_5_బిట్లు         ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 6 )  /* (USART) Character Length: 5 bits */
#నిర్వచించు     AT91_C_US_CHRL_6_బిట్లు         ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 6 )  /* (USART) Character Length: 6 bits */
#నిర్వచించు     AT91_C_US_CHRL_7_బిట్లు         ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 6 )  /* (USART) Character Length: 7 bits */
#నిర్వచించు     AT91_C_US_CHRL_8_బిట్లు         ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 6 )  /* (USART) Character Length: 8 bits */
#నిర్వచించు AT91C_US_SYNC                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )  /* (USART) Synchronous Mode Select */
#నిర్వచించు AT91C_US_NBSTOP                  ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 12 ) /* (USART) Number of Stop bits */
#నిర్వచించు     AT91_C_US_NBSTOP_1_బిట్టు        ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 12 ) /* (USART) 1 stop bit */
#నిర్వచించు     AT91_C_US_NBSTOP_15_బిట్టు       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 12 ) /* (USART) Asynchronous (SYNC=0) 2 stop bits Synchronous (SYNC=1) 2 stop bits */
#నిర్వచించు     AT91_C_US_NBSTOP_2_బిట్టు        ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 12 ) /* (USART) 2 stop bits */
#నిర్వచించు AT91C_US_MSBF                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 ) /* (USART) Bit Order */
#నిర్వచించు AT91C_US_MODE9                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 17 ) /* (USART) 9-bit Character length */
#నిర్వచించు AT91C_US_CKLO                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 18 ) /* (USART) Clock Output Select */
#నిర్వచించు AT91C_US_OVER                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 19 ) /* (USART) Over Sampling Mode */
#నిర్వచించు AT91C_US_INACK                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 20 ) /* (USART) Inhibit Non Acknowledge */
#నిర్వచించు AT91C_US_DSNACK                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 21 ) /* (USART) Disable Successive NACK */
#నిర్వచించు AT91C_US_MAX_ITER                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 24 ) /* (USART) Number of Repetitions */
#నిర్వచించు AT91C_US_FILTER                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 28 ) /* (USART) Receive Line Filter */
/* -------- US_IER : (USART Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
#నిర్వచించు AT91C_US_RXBRK                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )  /* (USART) Break Received/End of Break */
#నిర్వచించు AT91C_US_TIMEOUT                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )  /* (USART) Receiver Time-out */
#నిర్వచించు AT91C_US_ITERATION               ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 10 ) /* (USART) Max number of Repetitions Reached */
#నిర్వచించు AT91C_US_NACK                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 13 ) /* (USART) Non Acknowledge */
#నిర్వచించు AT91C_US_RIIC                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 ) /* (USART) Ring INdicator Input Change Flag */
#నిర్వచించు AT91C_US_DSRIC                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 17 ) /* (USART) Data Set Ready Input Change Flag */
#నిర్వచించు AT91C_US_DCDIC                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 18 ) /* (USART) Data Carrier Flag */
#నిర్వచించు AT91C_US_CTSIC                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 19 ) /* (USART) Clear To Send Input Change Flag */
/* -------- US_IDR : (USART Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* -------- US_IMR : (USART Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* -------- US_CSR : (USART Offset: 0x14) Debug Unit Channel Status Register -------- */
#నిర్వచించు AT91C_US_RI     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 20 )   /* (USART) Image of RI Input */
#నిర్వచించు AT91C_US_DSR    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 21 )   /* (USART) Image of DSR Input */
#నిర్వచించు AT91C_US_DCD    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 22 )   /* (USART) Image of DCD Input */
#నిర్వచించు AT91C_US_CTS    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 23 )   /* (USART) Image of CTS Input */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Synchronous Serial Controller Interface */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_SSC
{
    AT91_REG SSC_CR;          /* Control Register */
    AT91_REG SSC_CMR;         /* Clock Mode Register */
    AT91_REG Reserved0[ 2 ];  /* */
    AT91_REG SSC_RCMR;        /* Receive Clock ModeRegister */
    AT91_REG SSC_RFMR;        /* Receive Frame Mode Register */
    AT91_REG SSC_TCMR;        /* Transmit Clock Mode Register */
    AT91_REG SSC_TFMR;        /* Transmit Frame Mode Register */
    AT91_REG SSC_RHR;         /* Receive Holding Register */
    AT91_REG SSC_THR;         /* Transmit Holding Register */
    AT91_REG Reserved1[ 2 ];  /* */
    AT91_REG SSC_RSHR;        /* Receive Sync Holding Register */
    AT91_REG SSC_TSHR;        /* Transmit Sync Holding Register */
    AT91_REG Reserved2[ 2 ];  /* */
    AT91_REG SSC_SR;          /* Status Register */
    AT91_REG SSC_IER;         /* Interrupt Enable Register */
    AT91_REG SSC_IDR;         /* Interrupt Disable Register */
    AT91_REG SSC_IMR;         /* Interrupt Mask Register */
    AT91_REG Reserved3[ 44 ]; /* */
    AT91_REG SSC_RPR;         /* Receive Pointer Register */
    AT91_REG SSC_RCR;         /* Receive Counter Register */
    AT91_REG SSC_TPR;         /* Transmit Pointer Register */
    AT91_REG SSC_TCR;         /* Transmit Counter Register */
    AT91_REG SSC_RNPR;        /* Receive Next Pointer Register */
    AT91_REG SSC_RNCR;        /* Receive Next Counter Register */
    AT91_REG SSC_TNPR;        /* Transmit Next Pointer Register */
    AT91_REG SSC_TNCR;        /* Transmit Next Counter Register */
    AT91_REG SSC_PTCR;        /* PDC Transfer Control Register */
    AT91_REG SSC_PTSR;        /* PDC Transfer Status Register */
} AT91S_SSC, * AT91PS_SSC;

/* -------- SSC_CR : (SSC Offset: 0x0) SSC Control Register -------- */
#నిర్వచించు AT91C_SSC_RXEN                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )   /* (SSC) Receive Enable */
#నిర్వచించు AT91C_SSC_RXDIS                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )   /* (SSC) Receive Disable */
#నిర్వచించు AT91C_SSC_TXEN                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )   /* (SSC) Transmit Enable */
#నిర్వచించు AT91C_SSC_TXDIS                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 9 )   /* (SSC) Transmit Disable */
#నిర్వచించు AT91C_SSC_SWRST                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 15 )  /* (SSC) Software Reset */
/* -------- SSC_RCMR : (SSC Offset: 0x10) SSC Receive Clock Mode Register -------- */
#నిర్వచించు AT91C_SSC_CKS                     ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 0 )   /* (SSC) Receive/Transmit Clock Selection */
#నిర్వచించు     AT91C_SSC_CKS_DIV             ( ( గుర్తులేని పూర్ణాంకం ) 0x0 )        /* (SSC) Divided Clock */
#నిర్వచించు     AT91C_SSC_CKS_TK              ( ( గుర్తులేని పూర్ణాంకం ) 0x1 )        /* (SSC) TK Clock signal */
#నిర్వచించు     AT91C_SSC_CKS_RK              ( ( గుర్తులేని పూర్ణాంకం ) 0x2 )        /* (SSC) RK pin */
#నిర్వచించు AT91C_SSC_CKO                     ( ( గుర్తులేని పూర్ణాంకం ) 0x7 << 2 )   /* (SSC) Receive/Transmit Clock Output Mode Selection */
#నిర్వచించు     AT91C_SSC_CKO_NONE            ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 2 )   /* (SSC) Receive/Transmit Clock Output Mode: None RK pin: Input-only */
#నిర్వచించు     AT91C_SSC_CKO_CONTINUOUS      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )   /* (SSC) Continuous Receive/Transmit Clock RK pin: Output */
#నిర్వచించు     AT91_C_SSC_CKO_దత్తాంశం_TX         ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 2 )   /* (SSC) Receive/Transmit Clock only during data transfers RK pin: Output */
#నిర్వచించు AT91C_SSC_CKI                     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 )   /* (SSC) Receive/Transmit Clock Inversion */
#నిర్వచించు AT91_C_SSC_ప్రారంభం                   ( ( గుర్తులేని పూర్ణాంకం ) 0xF << 8 )   /* (SSC) Receive/Transmit Start Selection */
#నిర్వచించు     AT91_C_SSC_ప్రారంభం_CONTINUOUS    ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 8 )   /* (SSC) Continuous, as soon as the receiver is enabled, and immediately after the end of transfer of the previous data. */
#నిర్వచించు     AT91_C_SSC_ప్రారంభం_TX            ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )   /* (SSC) Transmit/Receive start */
#నిర్వచించు     AT91_C_SSC_ప్రారంభం_దిగువ_RF        ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 8 )   /* (SSC) Detection of a low level on RF input */
#నిర్వచించు     AT91_C_SSC_ప్రారంభం_ఎగువ_RF       ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 8 )   /* (SSC) Detection of a high level on RF input */
#నిర్వచించు     AT91_C_SSC_ప్రారంభం_FALL_RF       ( ( గుర్తులేని పూర్ణాంకం ) 0x4 << 8 )   /* (SSC) Detection of a falling edge on RF input */
#నిర్వచించు     AT91_C_SSC_ప్రారంభం_RISE_RF       ( ( గుర్తులేని పూర్ణాంకం ) 0x5 << 8 )   /* (SSC) Detection of a rising edge on RF input */
#నిర్వచించు     AT91_C_SSC_ప్రారంభం_LEVEL_RF      ( ( గుర్తులేని పూర్ణాంకం ) 0x6 << 8 )   /* (SSC) Detection of any level change on RF input */
#నిర్వచించు     AT91_C_SSC_ప్రారంభం_అంచు_RF       ( ( గుర్తులేని పూర్ణాంకం ) 0x7 << 8 )   /* (SSC) Detection of any edge on RF input */
#నిర్వచించు     AT91_C_SSC_ప్రారంభం_0             ( ( గుర్తులేని పూర్ణాంకం ) 0x8 << 8 )   /* (SSC) Compare 0 */
#నిర్వచించు AT91C_SSC_STTDLY                  ( ( గుర్తులేని పూర్ణాంకం ) 0xFF << 16 ) /* (SSC) Receive/Transmit Start Delay */
#నిర్వచించు AT91C_SSC_PERIOD                  ( ( గుర్తులేని పూర్ణాంకం ) 0xFF << 24 ) /* (SSC) Receive/Transmit Period Divider Selection */
/* -------- SSC_RFMR : (SSC Offset: 0x14) SSC Receive Frame Mode Register -------- */
#నిర్వచించు AT91C_SSC_DATLEN                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1F << 0 )  /* (SSC) Data Length */
#నిర్వచించు AT91C_SSC_LOOP                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 )   /* (SSC) Loop Mode */
#నిర్వచించు AT91C_SSC_MSBF                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )   /* (SSC) Most Significant Bit First */
#నిర్వచించు AT91C_SSC_DATNB                   ( ( గుర్తులేని పూర్ణాంకం ) 0xF << 8 )   /* (SSC) Data Number per Frame */
#నిర్వచించు AT91C_SSC_FSLEN                   ( ( గుర్తులేని పూర్ణాంకం ) 0xF << 16 )  /* (SSC) Receive/Transmit Frame Sync length */
#నిర్వచించు AT91C_SSC_FSOS                    ( ( గుర్తులేని పూర్ణాంకం ) 0x7 << 20 )  /* (SSC) Receive/Transmit Frame Sync Output Selection */
#నిర్వచించు     AT91C_SSC_FSOS_NONE           ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: None RK pin Input-only */
#నిర్వచించు     AT91C_SSC_FSOS_NEGATIVE       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Negative Pulse */
#నిర్వచించు     AT91_C_SSC_FSOS_ధనాత్మక       ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Positive Pulse */
#నిర్వచించు     AT91_C_SSC_FSOS_దిగువ            ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Driver Low during data transfer */
#నిర్వచించు     AT91_C_SSC_FSOS_ఎగువ           ( ( గుర్తులేని పూర్ణాంకం ) 0x4 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Driver High during data transfer */
#నిర్వచించు     AT91C_SSC_FSOS_TOGGLE         ( ( గుర్తులేని పూర్ణాంకం ) 0x5 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Toggling at each start of data transfer */
#నిర్వచించు AT91C_SSC_FSEDGE                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 24 )  /* (SSC) Frame Sync Edge Detection */
/* -------- SSC_TCMR : (SSC Offset: 0x18) SSC Transmit Clock Mode Register -------- */
/* -------- SSC_TFMR : (SSC Offset: 0x1c) SSC Transmit Frame Mode Register -------- */
#నిర్వచించు AT91C_SSC_DATDEF                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 )  /* (SSC) Data Default Value */
#నిర్వచించు AT91C_SSC_FSDEN                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 23 ) /* (SSC) Frame Sync Data Enable */
/* -------- SSC_SR : (SSC Offset: 0x40) SSC Status Register -------- */
#నిర్వచించు AT91C_SSC_TXRDY                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )  /* (SSC) Transmit Ready */
#నిర్వచించు AT91C_SSC_TXEMPTY                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )  /* (SSC) Transmit Empty */
#నిర్వచించు AT91C_SSC_ENDTX                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )  /* (SSC) End Of Transmission */
#నిర్వచించు AT91C_SSC_TXBUFE                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )  /* (SSC) Transmit Buffer Empty */
#నిర్వచించు AT91C_SSC_RXRDY                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )  /* (SSC) Receive Ready */
#నిర్వచించు AT91C_SSC_OVRUN                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 )  /* (SSC) Receive Overrun */
#నిర్వచించు AT91C_SSC_ENDRX                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 6 )  /* (SSC) End of Reception */
#నిర్వచించు AT91C_SSC_RXBUFF                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )  /* (SSC) Receive Buffer Full */
#నిర్వచించు AT91C_SSC_TXSYN                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 10 ) /* (SSC) Transmit Sync */
#నిర్వచించు AT91C_SSC_RXSYN                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 11 ) /* (SSC) Receive Sync */
#నిర్వచించు AT91C_SSC_TXENA                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 ) /* (SSC) Transmit Enable */
#నిర్వచించు AT91C_SSC_RXENA                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 17 ) /* (SSC) Receive Enable */
/* -------- SSC_IER : (SSC Offset: 0x44) SSC Interrupt Enable Register -------- */
/* -------- SSC_IDR : (SSC Offset: 0x48) SSC Interrupt Disable Register -------- */
/* -------- SSC_IMR : (SSC Offset: 0x4c) SSC Interrupt Mask Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Two-wire Interface */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_TWI
{
    AT91_REG TWI_CR;         /* Control Register */
    AT91_REG TWI_MMR;        /* Master Mode Register */
    AT91_REG Reserved0[ 1 ]; /* */
    AT91_REG TWI_IADR;       /* Internal Address Register */
    AT91_REG TWI_CWGR;       /* Clock Waveform Generator Register */
    AT91_REG Reserved1[ 3 ]; /* */
    AT91_REG TWI_SR;         /* Status Register */
    AT91_REG TWI_IER;        /* Interrupt Enable Register */
    AT91_REG TWI_IDR;        /* Interrupt Disable Register */
    AT91_REG TWI_IMR;        /* Interrupt Mask Register */
    AT91_REG TWI_RHR;        /* Receive Holding Register */
    AT91_REG TWI_THR;        /* Transmit Holding Register */
} AT91S_TWI, * AT91PS_TWI;

/* -------- TWI_CR : (TWI Offset: 0x0) TWI Control Register -------- */
#నిర్వచించు AT91_C_TWI_ప్రారంభం                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )   /* (TWI) Send a START Condition */
#నిర్వచించు AT91C_TWI_STOP                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )   /* (TWI) Send a STOP Condition */
#నిర్వచించు AT91C_TWI_MSEN                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )   /* (TWI) TWI Master Transfer Enabled */
#నిర్వచించు AT91C_TWI_MSDIS                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )   /* (TWI) TWI Master Transfer Disabled */
#నిర్వచించు AT91C_TWI_SWRST                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )   /* (TWI) Software Reset */
/* -------- TWI_MMR : (TWI Offset: 0x4) TWI Master Mode Register -------- */
#నిర్వచించు AT91C_TWI_IADRSZ               ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 8 )   /* (TWI) Internal Device Address Size */
#నిర్వచించు     AT91C_TWI_IADRSZ_NO        ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 8 )   /* (TWI) No internal device address */
#నిర్వచించు     AT91C_TWI_IADRSZ_1_BYTE    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )   /* (TWI) One-byte internal device address */
#నిర్వచించు     AT91C_TWI_IADRSZ_2_BYTE    ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 8 )   /* (TWI) Two-byte internal device address */
#నిర్వచించు     AT91C_TWI_IADRSZ_3_BYTE    ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 8 )   /* (TWI) Three-byte internal device address */
#నిర్వచించు AT91C_TWI_MREAD                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 12 )  /* (TWI) Master Read Direction */
#నిర్వచించు AT91C_TWI_DADR                 ( ( గుర్తులేని పూర్ణాంకం ) 0x7F << 16 ) /* (TWI) Device Address */
/* -------- TWI_CWGR : (TWI Offset: 0x10) TWI Clock Waveform Generator Register -------- */
#నిర్వచించు AT91C_TWI_CLDIV                ( ( గుర్తులేని పూర్ణాంకం ) 0xFF << 0 )  /* (TWI) Clock Low Divider */
#నిర్వచించు AT91C_TWI_CHDIV                ( ( గుర్తులేని పూర్ణాంకం ) 0xFF << 8 )  /* (TWI) Clock High Divider */
#నిర్వచించు AT91C_TWI_CKDIV                ( ( గుర్తులేని పూర్ణాంకం ) 0x7 << 16 )  /* (TWI) Clock Divider */
/* -------- TWI_SR : (TWI Offset: 0x20) TWI Status Register -------- */
#నిర్వచించు AT91C_TWI_TXCOMP               ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )   /* (TWI) Transmission Completed */
#నిర్వచించు AT91C_TWI_RXRDY                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )   /* (TWI) Receive holding register ReaDY */
#నిర్వచించు AT91C_TWI_TXRDY                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )   /* (TWI) Transmit holding register ReaDY */
#నిర్వచించు AT91C_TWI_OVRE                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 6 )   /* (TWI) Overrun Error */
#నిర్వచించు AT91C_TWI_UNRE                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )   /* (TWI) Underrun Error */
#నిర్వచించు AT91C_TWI_NACK                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )   /* (TWI) Not Acknowledged */
/* -------- TWI_IER : (TWI Offset: 0x24) TWI Interrupt Enable Register -------- */
/* -------- TWI_IDR : (TWI Offset: 0x28) TWI Interrupt Disable Register -------- */
/* -------- TWI_IMR : (TWI Offset: 0x2c) TWI Interrupt Mask Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR PWMC Channel Interface */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_PWMC_CH
{
    AT91_REG PWMC_CMR;           /* Channel Mode Register */
    AT91_REG PWMC_CDTYR;         /* Channel Duty Cycle Register */
    AT91_REG PWMC_CPRDR;         /* Channel Period Register */
    AT91_REG PWMC_CCNTR;         /* Channel Counter Register */
    AT91_REG PWMC_CUPDR;         /* Channel Update Register */
    AT91_REG PWMC_Reserved[ 3 ]; /* Reserved */
} AT91S_PWMC_CH, * AT91PS_PWMC_CH;

/* -------- PWMC_CMR : (PWMC_CH Offset: 0x0) PWMC Channel Mode Register -------- */
#నిర్వచించు AT91C_PWMC_CPRE             ( ( గుర్తులేని పూర్ణాంకం ) 0xF << 0 )  /* (PWMC_CH) Channel Pre-scaler : PWMC_CLKx */
#నిర్వచించు     AT91C_PWMC_CPRE_MCK     ( ( గుర్తులేని పూర్ణాంకం ) 0x0 )       /* (PWMC_CH) */
#నిర్వచించు     AT91C_PWMC_CPRE_MCKA    ( ( గుర్తులేని పూర్ణాంకం ) 0xB )       /* (PWMC_CH) */
#నిర్వచించు     AT91C_PWMC_CPRE_MCKB    ( ( గుర్తులేని పూర్ణాంకం ) 0xC )       /* (PWMC_CH) */
#నిర్వచించు AT91C_PWMC_CALG             ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )  /* (PWMC_CH) Channel Alignment */
#నిర్వచించు AT91C_PWMC_CPOL             ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 9 )  /* (PWMC_CH) Channel Polarity */
#నిర్వచించు AT91C_PWMC_CPD              ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 10 ) /* (PWMC_CH) Channel Update Period */
/* -------- PWMC_CDTYR : (PWMC_CH Offset: 0x4) PWMC Channel Duty Cycle Register -------- */
#నిర్వచించు AT91C_PWMC_CDTY             ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 0 )  /* (PWMC_CH) Channel Duty Cycle */
/* -------- PWMC_CPRDR : (PWMC_CH Offset: 0x8) PWMC Channel Period Register -------- */
#నిర్వచించు AT91C_PWMC_CPRD             ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 0 )  /* (PWMC_CH) Channel Period */
/* -------- PWMC_CCNTR : (PWMC_CH Offset: 0xc) PWMC Channel Counter Register -------- */
#నిర్వచించు AT91C_PWMC_CCNT             ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 0 )  /* (PWMC_CH) Channel Counter */
/* -------- PWMC_CUPDR : (PWMC_CH Offset: 0x10) PWMC Channel Update Register -------- */
#నిర్వచించు AT91C_PWMC_CUPD             ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 0 )  /* (PWMC_CH) Channel Update */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Pulse Width Modulation Controller Interface */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_PWMC
{
    AT91_REG PWMC_MR;           /* PWMC Mode Register */
    AT91_REG PWMC_ENA;          /* PWMC Enable Register */
    AT91_REG PWMC_DIS;          /* PWMC Disable Register */
    AT91_REG PWMC_SR;           /* PWMC Status Register */
    AT91_REG PWMC_IER;          /* PWMC Interrupt Enable Register */
    AT91_REG PWMC_IDR;          /* PWMC Interrupt Disable Register */
    AT91_REG PWMC_IMR;          /* PWMC Interrupt Mask Register */
    AT91_REG PWMC_ISR;          /* PWMC Interrupt Status Register */
    AT91_REG Reserved0[ 55 ];   /* */
    AT91_REG PWMC_VR;           /* PWMC Version Register */
    AT91_REG Reserved1[ 64 ];   /* */
    AT91S_PWMC_CH PWMC_CH[ 4 ]; /* PWMC Channel */
} AT91S_PWMC, * AT91PS_PWMC;

/* -------- PWMC_MR : (PWMC Offset: 0x0) PWMC Mode Register -------- */
#నిర్వచించు AT91C_PWMC_DIVA            ( ( గుర్తులేని పూర్ణాంకం ) 0xFF << 0 )  /* (PWMC) CLKA divide factor. */
#నిర్వచించు AT91C_PWMC_PREA            ( ( గుర్తులేని పూర్ణాంకం ) 0xF << 8 )   /* (PWMC) Divider Input Clock Prescaler A */
#నిర్వచించు     AT91C_PWMC_PREA_MCK    ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 8 )   /* (PWMC) */
#నిర్వచించు AT91C_PWMC_DIVB            ( ( గుర్తులేని పూర్ణాంకం ) 0xFF << 16 ) /* (PWMC) CLKB divide factor. */
#నిర్వచించు AT91C_PWMC_PREB            ( ( గుర్తులేని పూర్ణాంకం ) 0xF << 24 )  /* (PWMC) Divider Input Clock Prescaler B */
#నిర్వచించు     AT91C_PWMC_PREB_MCK    ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 24 )  /* (PWMC) */
/* -------- PWMC_ENA : (PWMC Offset: 0x4) PWMC Enable Register -------- */
#నిర్వచించు AT91C_PWMC_CHID0           ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )   /* (PWMC) Channel ID 0 */
#నిర్వచించు AT91C_PWMC_CHID1           ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )   /* (PWMC) Channel ID 1 */
#నిర్వచించు AT91C_PWMC_CHID2           ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )   /* (PWMC) Channel ID 2 */
#నిర్వచించు AT91C_PWMC_CHID3           ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )   /* (PWMC) Channel ID 3 */
/* -------- PWMC_DIS : (PWMC Offset: 0x8) PWMC Disable Register -------- */
/* -------- PWMC_SR : (PWMC Offset: 0xc) PWMC Status Register -------- */
/* -------- PWMC_IER : (PWMC Offset: 0x10) PWMC Interrupt Enable Register -------- */
/* -------- PWMC_IDR : (PWMC Offset: 0x14) PWMC Interrupt Disable Register -------- */
/* -------- PWMC_IMR : (PWMC Offset: 0x18) PWMC Interrupt Mask Register -------- */
/* -------- PWMC_ISR : (PWMC Offset: 0x1c) PWMC Interrupt Status Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR USB Device Interface */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_UDP
{
    AT91_REG UDP_అంకె;        /* Frame Number Register */
    AT91_REG UDP_GLBSTATE;   /* Global State Register */
    AT91_REG UDP_FADDR;      /* Function Address Register */
    AT91_REG Reserved0[ 1 ]; /* */
    AT91_REG UDP_IER;        /* Interrupt Enable Register */
    AT91_REG UDP_IDR;        /* Interrupt Disable Register */
    AT91_REG UDP_IMR;        /* Interrupt Mask Register */
    AT91_REG UDP_ISR;        /* Interrupt Status Register */
    AT91_REG UDP_ICR;        /* Interrupt Clear Register */
    AT91_REG Reserved1[ 1 ]; /* */
    AT91_REG UDP_RSTEP;      /* Reset Endpoint Register */
    AT91_REG Reserved2[ 1 ]; /* */
    AT91_REG UDP_CSR[ 6 ];   /* Endpoint Control and Status Register */
    AT91_REG Reserved3[ 2 ]; /* */
    AT91_REG UDP_FDR[ 6 ];   /* Endpoint FIFO Data Register */
    AT91_REG Reserved4[ 3 ]; /* */
    AT91_REG UDP_TXVC;       /* Transceiver Control Register */
} AT91S_UDP, * AT91PS_UDP;

/* -------- UDP_FRM_NUM : (UDP Offset: 0x0) USB Frame Number Register -------- */
#నిర్వచించు AT91_C_UDP_FRM_అంకె    ( ( గుర్తులేని పూర్ణాంకం ) 0x7FF << 0 ) /* (UDP) Frame Number as Defined in the Packet Field Formats */
#నిర్వచించు AT91C_UDP_FRM_ERR    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 )  /* (UDP) Frame Error */
#నిర్వచించు AT91C_UDP_FRM_OK     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 17 )  /* (UDP) Frame OK */
/* -------- UDP_GLB_STATE : (UDP Offset: 0x4) USB Global State Register -------- */
#నిర్వచించు AT91C_UDP_FADDEN     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )   /* (UDP) Function Address Enable */
#నిర్వచించు AT91C_UDP_CONFG      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )   /* (UDP) Configured */
#నిర్వచించు AT91C_UDP_ESR        ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )   /* (UDP) Enable Send Resume */
#నిర్వచించు AT91C_UDP_RSMINPR    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )   /* (UDP) A Resume Has Been Sent to the Host */
#నిర్వచించు AT91C_UDP_RMWUPE     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )   /* (UDP) Remote Wake Up Enable */
/* -------- UDP_FADDR : (UDP Offset: 0x8) USB Function Address Register -------- */
#నిర్వచించు AT91C_UDP_FADD       ( ( గుర్తులేని పూర్ణాంకం ) 0xFF << 0 )  /* (UDP) Function Address Value */
#నిర్వచించు AT91C_UDP_FEN        ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )   /* (UDP) Function Enable */
/* -------- UDP_IER : (UDP Offset: 0x10) USB Interrupt Enable Register -------- */
#నిర్వచించు AT91C_UDP_EPINT0     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )   /* (UDP) Endpoint 0 Interrupt */
#నిర్వచించు AT91C_UDP_EPINT1     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )   /* (UDP) Endpoint 0 Interrupt */
#నిర్వచించు AT91C_UDP_EPINT2     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )   /* (UDP) Endpoint 2 Interrupt */
#నిర్వచించు AT91C_UDP_EPINT3     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )   /* (UDP) Endpoint 3 Interrupt */
#నిర్వచించు AT91C_UDP_EPINT4     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )   /* (UDP) Endpoint 4 Interrupt */
#నిర్వచించు AT91C_UDP_EPINT5     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 )   /* (UDP) Endpoint 5 Interrupt */
#నిర్వచించు AT91C_UDP_RXSUSP     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )   /* (UDP) USB Suspend Interrupt */
#నిర్వచించు AT91C_UDP_RXRSM      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 9 )   /* (UDP) USB Resume Interrupt */
#నిర్వచించు AT91C_UDP_EXTRSM     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 10 )  /* (UDP) USB External Resume Interrupt */
#నిర్వచించు AT91C_UDP_SOFINT     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 11 )  /* (UDP) USB Start Of frame Interrupt */
#నిర్వచించు AT91C_UDP_WAKEUP     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 13 )  /* (UDP) USB Resume Interrupt */
/* -------- UDP_IDR : (UDP Offset: 0x14) USB Interrupt Disable Register -------- */
/* -------- UDP_IMR : (UDP Offset: 0x18) USB Interrupt Mask Register -------- */
/* -------- UDP_ISR : (UDP Offset: 0x1c) USB Interrupt Status Register -------- */
#నిర్వచించు AT91C_UDP_ENDBUSRES              ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 12 ) /* (UDP) USB End Of Bus Reset Interrupt */
/* -------- UDP_ICR : (UDP Offset: 0x20) USB Interrupt Clear Register -------- */
/* -------- UDP_RST_EP : (UDP Offset: 0x28) USB Reset Endpoint Register -------- */
#నిర్వచించు AT91C_UDP_EP0                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )    /* (UDP) Reset Endpoint 0 */
#నిర్వచించు AT91C_UDP_EP1                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )    /* (UDP) Reset Endpoint 1 */
#నిర్వచించు AT91C_UDP_EP2                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )    /* (UDP) Reset Endpoint 2 */
#నిర్వచించు AT91C_UDP_EP3                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )    /* (UDP) Reset Endpoint 3 */
#నిర్వచించు AT91C_UDP_EP4                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )    /* (UDP) Reset Endpoint 4 */
#నిర్వచించు AT91C_UDP_EP5                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 )    /* (UDP) Reset Endpoint 5 */
/* -------- UDP_CSR : (UDP Offset: 0x30) USB Endpoint Control and Status Register -------- */
#నిర్వచించు AT91C_UDP_TXCOMP                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )    /* (UDP) Generates an IN packet with data previously written in the DPR */
#నిర్వచించు AT91_C_UDP_RX_దత్తాంశం_BK0            ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )    /* (UDP) Receive Data Bank 0 */
#నిర్వచించు AT91C_UDP_RXSETUP                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )    /* (UDP) Sends STALL to the Host (Control endpoints) */
#నిర్వచించు AT91C_UDP_ISOERROR               ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )    /* (UDP) Isochronous error (Isochronous endpoints) */
#నిర్వచించు AT91C_UDP_TXPKTRDY               ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )    /* (UDP) Transmit Packet Ready */
#నిర్వచించు AT91C_UDP_FORCESTALL             ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 )    /* (UDP) Force Stall (used by Control, Bulk and Isochronous endpoints). */
#నిర్వచించు AT91_C_UDP_RX_దత్తాంశం_BK1            ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 6 )    /* (UDP) Receive Data Bank 1 (only used by endpoints with ping-pong attributes). */
#నిర్వచించు AT91C_UDP_DIR                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )    /* (UDP) Transfer Direction */
#నిర్వచించు AT91C_UDP_EPTYPE                 ( ( గుర్తులేని పూర్ణాంకం ) 0x7 << 8 )    /* (UDP) Endpoint type */
#నిర్వచించు     AT91C_UDP_EPTYPE_CTRL        ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 8 )    /* (UDP) Control */
#నిర్వచించు     AT91_C_UDP_EPTYPE_ISO_బహిర్గతం     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )    /* (UDP) Isochronous OUT */
#నిర్వచించు     AT91_C_UDP_EPTYPE_BULK_బహిర్గతం    ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 8 )    /* (UDP) Bulk OUT */
#నిర్వచించు     AT91_C_UDP_EPTYPE_INT_బహిర్గతం     ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 8 )    /* (UDP) Interrupt OUT */
#నిర్వచించు     AT91_C_UDP_EPTYPE_ISO_లోపల      ( ( గుర్తులేని పూర్ణాంకం ) 0x5 << 8 )    /* (UDP) Isochronous IN */
#నిర్వచించు     AT91_C_UDP_EPTYPE_BULK_లోపల     ( ( గుర్తులేని పూర్ణాంకం ) 0x6 << 8 )    /* (UDP) Bulk IN */
#నిర్వచించు     AT91_C_UDP_EPTYPE_INT_లోపల      ( ( గుర్తులేని పూర్ణాంకం ) 0x7 << 8 )    /* (UDP) Interrupt IN */
#నిర్వచించు AT91C_UDP_DTGLE                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 11 )   /* (UDP) Data Toggle */
#నిర్వచించు AT91C_UDP_EPEDS                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 15 )   /* (UDP) Endpoint Enable Disable */
#నిర్వచించు AT91C_UDP_RXBYTECNT              ( ( గుర్తులేని పూర్ణాంకం ) 0x7FF << 16 ) /* (UDP) Number Of Bytes Available in the FIFO */
/* -------- UDP_TXVC : (UDP Offset: 0x74) Transceiver Control Register -------- */
#నిర్వచించు AT91C_UDP_TXVDIS                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )    /* (UDP) */
#నిర్వచించు AT91C_UDP_PUON                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 9 )    /* (UDP) Pull-up ON */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Timer Counter Channel Interface */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_TC
{
    AT91_REG TC_CCR;         /* Channel Control Register */
    AT91_REG TC_CMR;         /* Channel Mode Register (Capture Mode / Waveform Mode) */
    AT91_REG Reserved0[ 2 ]; /* */
    AT91_REG TC_CV;          /* Counter Value */
    AT91_REG TC_RA;          /* Register A */
    AT91_REG TC_RB;          /* Register B */
    AT91_REG TC_RC;          /* Register C */
    AT91_REG TC_SR;          /* Status Register */
    AT91_REG TC_IER;         /* Interrupt Enable Register */
    AT91_REG TC_IDR;         /* Interrupt Disable Register */
    AT91_REG TC_IMR;         /* Interrupt Mask Register */
} AT91S_TC, * AT91PS_TC;

/* -------- TC_CCR : (TC Offset: 0x0) TC Channel Control Register -------- */
#నిర్వచించు AT91C_TC_CLKEN                        ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )  /* (TC) Counter Clock Enable Command */
#నిర్వచించు AT91C_TC_CLKDIS                       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )  /* (TC) Counter Clock Disable Command */
#నిర్వచించు AT91C_TC_SWTRG                        ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )  /* (TC) Software Trigger Command */
/* -------- TC_CMR : (TC Offset: 0x4) TC Channel Mode Register: Capture Mode / Waveform Mode -------- */
#నిర్వచించు AT91C_TC_CLKS                         ( ( గుర్తులేని పూర్ణాంకం ) 0x7 << 0 )  /* (TC) Clock Selection */
#నిర్వచించు     AT91C_TC_CLKS_TIMER_DIV1_CLOCK    ( ( గుర్తులేని పూర్ణాంకం ) 0x0 )       /* (TC) Clock selected: TIMER_DIV1_CLOCK */
#నిర్వచించు     AT91C_TC_CLKS_TIMER_DIV2_CLOCK    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 )       /* (TC) Clock selected: TIMER_DIV2_CLOCK */
#నిర్వచించు     AT91C_TC_CLKS_TIMER_DIV3_CLOCK    ( ( గుర్తులేని పూర్ణాంకం ) 0x2 )       /* (TC) Clock selected: TIMER_DIV3_CLOCK */
#నిర్వచించు     AT91C_TC_CLKS_TIMER_DIV4_CLOCK    ( ( గుర్తులేని పూర్ణాంకం ) 0x3 )       /* (TC) Clock selected: TIMER_DIV4_CLOCK */
#నిర్వచించు     AT91C_TC_CLKS_TIMER_DIV5_CLOCK    ( ( గుర్తులేని పూర్ణాంకం ) 0x4 )       /* (TC) Clock selected: TIMER_DIV5_CLOCK */
#నిర్వచించు     AT91C_TC_CLKS_XC0                 ( ( గుర్తులేని పూర్ణాంకం ) 0x5 )       /* (TC) Clock selected: XC0 */
#నిర్వచించు     AT91C_TC_CLKS_XC1                 ( ( గుర్తులేని పూర్ణాంకం ) 0x6 )       /* (TC) Clock selected: XC1 */
#నిర్వచించు     AT91C_TC_CLKS_XC2                 ( ( గుర్తులేని పూర్ణాంకం ) 0x7 )       /* (TC) Clock selected: XC2 */
#నిర్వచించు AT91C_TC_CLKI                         ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )  /* (TC) Clock Invert */
#నిర్వచించు AT91_C_TC_వ్యవధి                        ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 4 )  /* (TC) Burst Signal Selection */
#నిర్వచించు     AT91_C_TC_వ్యవధి_NONE               ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 4 )  /* (TC) The clock is not gated by an external signal */
#నిర్వచించు     AT91_C_TC_వ్యవధి_XC0                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )  /* (TC) XC0 is ANDed with the selected clock */
#నిర్వచించు     AT91_C_TC_వ్యవధి_XC1                ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 4 )  /* (TC) XC1 is ANDed with the selected clock */
#నిర్వచించు     AT91_C_TC_వ్యవధి_XC2                ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 4 )  /* (TC) XC2 is ANDed with the selected clock */
#నిర్వచించు AT91C_TC_CPCSTOP                      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 6 )  /* (TC) Counter Clock Stopped with RC Compare */
#నిర్వచించు AT91C_TC_LDBSTOP                      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 6 )  /* (TC) Counter Clock Stopped with RB Loading */
#నిర్వచించు AT91C_TC_CPCDIS                       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )  /* (TC) Counter Clock Disable with RC Compare */
#నిర్వచించు AT91C_TC_LDBDIS                       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )  /* (TC) Counter Clock Disabled with RB Loading */
#నిర్వచించు AT91C_TC_ETRGEDG                      ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 8 )  /* (TC) External Trigger Edge Selection */
#నిర్వచించు     AT91C_TC_ETRGEDG_NONE             ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 8 )  /* (TC) Edge: None */
#నిర్వచించు     AT91C_TC_ETRGEDG_RISING           ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )  /* (TC) Edge: rising edge */
#నిర్వచించు     AT91C_TC_ETRGEDG_FALLING          ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 8 )  /* (TC) Edge: falling edge */
#నిర్వచించు     AT91C_TC_ETRGEDG_BOTH             ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 8 )  /* (TC) Edge: each edge */
#నిర్వచించు AT91C_TC_EEVTEDG                      ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 8 )  /* (TC) External Event Edge Selection */
#నిర్వచించు     AT91C_TC_EEVTEDG_NONE             ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 8 )  /* (TC) Edge: None */
#నిర్వచించు     AT91C_TC_EEVTEDG_RISING           ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )  /* (TC) Edge: rising edge */
#నిర్వచించు     AT91C_TC_EEVTEDG_FALLING          ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 8 )  /* (TC) Edge: falling edge */
#నిర్వచించు     AT91C_TC_EEVTEDG_BOTH             ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 8 )  /* (TC) Edge: each edge */
#నిర్వచించు AT91C_TC_EEVT                         ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 10 ) /* (TC) External Event  Selection */
#నిర్వచించు     AT91C_TC_EEVT_TIOB                ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 10 ) /* (TC) Signal selected as external event: TIOB TIOB direction: input */
#నిర్వచించు     AT91C_TC_EEVT_XC0                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 10 ) /* (TC) Signal selected as external event: XC0 TIOB direction: output */
#నిర్వచించు     AT91C_TC_EEVT_XC1                 ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 10 ) /* (TC) Signal selected as external event: XC1 TIOB direction: output */
#నిర్వచించు     AT91C_TC_EEVT_XC2                 ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 10 ) /* (TC) Signal selected as external event: XC2 TIOB direction: output */
#నిర్వచించు AT91C_TC_ABETRG                       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 10 ) /* (TC) TIOA or TIOB External Trigger Selection */
#నిర్వచించు AT91C_TC_ENETRG                       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 12 ) /* (TC) External Event Trigger enable */
#నిర్వచించు AT91C_TC_WAVESEL                      ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 13 ) /* (TC) Waveform  Selection */
#నిర్వచించు     AT91_C_TC_WAVESEL_పైకి               ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 13 ) /* (TC) UP mode without atomatic trigger on RC Compare */
#నిర్వచించు     AT91C_TC_WAVESEL_UPDOWN           ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 13 ) /* (TC) UPDOWN mode without automatic trigger on RC Compare */
#నిర్వచించు     AT91_C_TC_WAVESEL_పైకి_AUTO          ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 13 ) /* (TC) UP mode with automatic trigger on RC Compare */
#నిర్వచించు     AT91C_TC_WAVESEL_UPDOWN_AUTO      ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 13 ) /* (TC) UPDOWN mode with automatic trigger on RC Compare */
#నిర్వచించు AT91C_TC_CPCTRG                       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 14 ) /* (TC) RC Compare Trigger Enable */
#నిర్వచించు AT91C_TC_WAVE                         ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 15 ) /* (TC) */
#నిర్వచించు AT91C_TC_ACPA                         ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 16 ) /* (TC) RA Compare Effect on TIOA */
#నిర్వచించు     AT91C_TC_ACPA_NONE                ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 16 ) /* (TC) Effect: none */
#నిర్వచించు     AT91_C_TC_ACPA_సమితి                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 ) /* (TC) Effect: set */
#నిర్వచించు     AT91C_TC_ACPA_CLEAR               ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 16 ) /* (TC) Effect: clear */
#నిర్వచించు     AT91C_TC_ACPA_TOGGLE              ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 16 ) /* (TC) Effect: toggle */
#నిర్వచించు AT91C_TC_LDRA                         ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 16 ) /* (TC) RA Loading Selection */
#నిర్వచించు     AT91C_TC_LDRA_NONE                ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 16 ) /* (TC) Edge: None */
#నిర్వచించు     AT91C_TC_LDRA_RISING              ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 ) /* (TC) Edge: rising edge of TIOA */
#నిర్వచించు     AT91C_TC_LDRA_FALLING             ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 16 ) /* (TC) Edge: falling edge of TIOA */
#నిర్వచించు     AT91C_TC_LDRA_BOTH                ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 16 ) /* (TC) Edge: each edge of TIOA */
#నిర్వచించు AT91C_TC_ACPC                         ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 18 ) /* (TC) RC Compare Effect on TIOA */
#నిర్వచించు     AT91C_TC_ACPC_NONE                ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 18 ) /* (TC) Effect: none */
#నిర్వచించు     AT91_C_TC_ACPC_సమితి                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 18 ) /* (TC) Effect: set */
#నిర్వచించు     AT91C_TC_ACPC_CLEAR               ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 18 ) /* (TC) Effect: clear */
#నిర్వచించు     AT91C_TC_ACPC_TOGGLE              ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 18 ) /* (TC) Effect: toggle */
#నిర్వచించు AT91C_TC_LDRB                         ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 18 ) /* (TC) RB Loading Selection */
#నిర్వచించు     AT91C_TC_LDRB_NONE                ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 18 ) /* (TC) Edge: None */
#నిర్వచించు     AT91C_TC_LDRB_RISING              ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 18 ) /* (TC) Edge: rising edge of TIOA */
#నిర్వచించు     AT91C_TC_LDRB_FALLING             ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 18 ) /* (TC) Edge: falling edge of TIOA */
#నిర్వచించు     AT91C_TC_LDRB_BOTH                ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 18 ) /* (TC) Edge: each edge of TIOA */
#నిర్వచించు AT91C_TC_AEEVT                        ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 20 ) /* (TC) External Event Effect on TIOA */
#నిర్వచించు     AT91C_TC_AEEVT_NONE               ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 20 ) /* (TC) Effect: none */
#నిర్వచించు     AT91_C_TC_AEEVT_సమితి                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 20 ) /* (TC) Effect: set */
#నిర్వచించు     AT91C_TC_AEEVT_CLEAR              ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 20 ) /* (TC) Effect: clear */
#నిర్వచించు     AT91C_TC_AEEVT_TOGGLE             ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 20 ) /* (TC) Effect: toggle */
#నిర్వచించు AT91C_TC_ASWTRG                       ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 22 ) /* (TC) Software Trigger Effect on TIOA */
#నిర్వచించు     AT91C_TC_ASWTRG_NONE              ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 22 ) /* (TC) Effect: none */
#నిర్వచించు     AT91_C_TC_ASWTRG_సమితి               ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 22 ) /* (TC) Effect: set */
#నిర్వచించు     AT91C_TC_ASWTRG_CLEAR             ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 22 ) /* (TC) Effect: clear */
#నిర్వచించు     AT91C_TC_ASWTRG_TOGGLE            ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 22 ) /* (TC) Effect: toggle */
#నిర్వచించు AT91C_TC_BCPB                         ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 24 ) /* (TC) RB Compare Effect on TIOB */
#నిర్వచించు     AT91C_TC_BCPB_NONE                ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 24 ) /* (TC) Effect: none */
#నిర్వచించు     AT91_C_TC_BCPB_సమితి                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 24 ) /* (TC) Effect: set */
#నిర్వచించు     AT91C_TC_BCPB_CLEAR               ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 24 ) /* (TC) Effect: clear */
#నిర్వచించు     AT91C_TC_BCPB_TOGGLE              ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 24 ) /* (TC) Effect: toggle */
#నిర్వచించు AT91C_TC_BCPC                         ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 26 ) /* (TC) RC Compare Effect on TIOB */
#నిర్వచించు     AT91C_TC_BCPC_NONE                ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 26 ) /* (TC) Effect: none */
#నిర్వచించు     AT91_C_TC_BCPC_సమితి                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 26 ) /* (TC) Effect: set */
#నిర్వచించు     AT91C_TC_BCPC_CLEAR               ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 26 ) /* (TC) Effect: clear */
#నిర్వచించు     AT91C_TC_BCPC_TOGGLE              ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 26 ) /* (TC) Effect: toggle */
#నిర్వచించు AT91C_TC_BEEVT                        ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 28 ) /* (TC) External Event Effect on TIOB */
#నిర్వచించు     AT91C_TC_BEEVT_NONE               ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 28 ) /* (TC) Effect: none */
#నిర్వచించు     AT91_C_TC_BEEVT_సమితి                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 28 ) /* (TC) Effect: set */
#నిర్వచించు     AT91C_TC_BEEVT_CLEAR              ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 28 ) /* (TC) Effect: clear */
#నిర్వచించు     AT91C_TC_BEEVT_TOGGLE             ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 28 ) /* (TC) Effect: toggle */
#నిర్వచించు AT91C_TC_BSWTRG                       ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 30 ) /* (TC) Software Trigger Effect on TIOB */
#నిర్వచించు     AT91C_TC_BSWTRG_NONE              ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 30 ) /* (TC) Effect: none */
#నిర్వచించు     AT91_C_TC_BSWTRG_సమితి               ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 30 ) /* (TC) Effect: set */
#నిర్వచించు     AT91C_TC_BSWTRG_CLEAR             ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 30 ) /* (TC) Effect: clear */
#నిర్వచించు     AT91C_TC_BSWTRG_TOGGLE            ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 30 ) /* (TC) Effect: toggle */
/* -------- TC_SR : (TC Offset: 0x20) TC Channel Status Register -------- */
#నిర్వచించు AT91C_TC_COVFS                        ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )  /* (TC) Counter Overflow */
#నిర్వచించు AT91C_TC_LOVRS                        ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )  /* (TC) Load Overrun */
#నిర్వచించు AT91C_TC_CPAS                         ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )  /* (TC) RA Compare */
#నిర్వచించు AT91C_TC_CPBS                         ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )  /* (TC) RB Compare */
#నిర్వచించు AT91C_TC_CPCS                         ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )  /* (TC) RC Compare */
#నిర్వచించు AT91C_TC_LDRAS                        ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 )  /* (TC) RA Loading */
#నిర్వచించు AT91C_TC_LDRBS                        ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 6 )  /* (TC) RB Loading */
#నిర్వచించు AT91C_TC_ETRGS                        ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )  /* (TC) External Trigger */
#నిర్వచించు AT91C_TC_CLKSTA                       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 ) /* (TC) Clock Enabling */
#నిర్వచించు AT91C_TC_MTIOA                        ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 17 ) /* (TC) TIOA Mirror */
#నిర్వచించు AT91C_TC_MTIOB                        ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 18 ) /* (TC) TIOA Mirror */
/* -------- TC_IER : (TC Offset: 0x24) TC Channel Interrupt Enable Register -------- */
/* -------- TC_IDR : (TC Offset: 0x28) TC Channel Interrupt Disable Register -------- */
/* -------- TC_IMR : (TC Offset: 0x2c) TC Channel Interrupt Mask Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Timer Counter Interface */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_TCB
{
    AT91S_TC TCB_TC0;        /* TC Channel 0 */
    AT91_REG Reserved0[ 4 ]; /* */
    AT91S_TC TCB_TC1;        /* TC Channel 1 */
    AT91_REG Reserved1[ 4 ]; /* */
    AT91S_TC TCB_TC2;        /* TC Channel 2 */
    AT91_REG Reserved2[ 4 ]; /* */
    AT91_REG TCB_BCR;        /* TC Block Control Register */
    AT91_REG TCB_BMR;        /* TC Block Mode Register */
} AT91S_TCB, * AT91PS_TCB;

/* -------- TCB_BCR : (TCB Offset: 0xc0) TC Block Control Register -------- */
#నిర్వచించు AT91C_TCB_SYNC                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 ) /* (TCB) Synchro Command */
/* -------- TCB_BMR : (TCB Offset: 0xc4) TC Block Mode Register -------- */
#నిర్వచించు AT91C_TCB_TC0XC0S              ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 0 ) /* (TCB) External Clock Signal 0 Selection */
#నిర్వచించు     AT91C_TCB_TC0XC0S_TCLK0    ( ( గుర్తులేని పూర్ణాంకం ) 0x0 )      /* (TCB) TCLK0 connected to XC0 */
#నిర్వచించు     AT91C_TCB_TC0XC0S_NONE     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 )      /* (TCB) None signal connected to XC0 */
#నిర్వచించు     AT91C_TCB_TC0XC0S_TIOA1    ( ( గుర్తులేని పూర్ణాంకం ) 0x2 )      /* (TCB) TIOA1 connected to XC0 */
#నిర్వచించు     AT91C_TCB_TC0XC0S_TIOA2    ( ( గుర్తులేని పూర్ణాంకం ) 0x3 )      /* (TCB) TIOA2 connected to XC0 */
#నిర్వచించు AT91C_TCB_TC1XC1S              ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 2 ) /* (TCB) External Clock Signal 1 Selection */
#నిర్వచించు     AT91C_TCB_TC1XC1S_TCLK1    ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 2 ) /* (TCB) TCLK1 connected to XC1 */
#నిర్వచించు     AT91C_TCB_TC1XC1S_NONE     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 ) /* (TCB) None signal connected to XC1 */
#నిర్వచించు     AT91C_TCB_TC1XC1S_TIOA0    ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 2 ) /* (TCB) TIOA0 connected to XC1 */
#నిర్వచించు     AT91C_TCB_TC1XC1S_TIOA2    ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 2 ) /* (TCB) TIOA2 connected to XC1 */
#నిర్వచించు AT91C_TCB_TC2XC2S              ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 4 ) /* (TCB) External Clock Signal 2 Selection */
#నిర్వచించు     AT91C_TCB_TC2XC2S_TCLK2    ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 4 ) /* (TCB) TCLK2 connected to XC2 */
#నిర్వచించు     AT91C_TCB_TC2XC2S_NONE     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 ) /* (TCB) None signal connected to XC2 */
#నిర్వచించు     AT91C_TCB_TC2XC2S_TIOA0    ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 4 ) /* (TCB) TIOA0 connected to XC2 */
#నిర్వచించు     AT91C_TCB_TC2XC2S_TIOA1    ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 4 ) /* (TCB) TIOA2 connected to XC2 */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Control Area Network MailBox Interface */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_CAN_MB
{
    AT91_REG CAN_MB_MMR;  /* MailBox Mode Register */
    AT91_REG CAN_MB_MAM;  /* MailBox Acceptance Mask Register */
    AT91_REG CAN_MB_MID;  /* MailBox ID Register */
    AT91_REG CAN_MB_MFID; /* MailBox Family ID Register */
    AT91_REG CAN_MB_MSR;  /* MailBox Status Register */
    AT91_REG CAN_MB_MDL;  /* MailBox Data Low Register */
    AT91_REG CAN_MB_MDH;  /* MailBox Data High Register */
    AT91_REG CAN_MB_MCR;  /* MailBox Control Register */
} AT91S_CAN_MB, * AT91PS_CAN_MB;

/* -------- CAN_MMR : (CAN_MB Offset: 0x0) CAN Message Mode Register -------- */
#నిర్వచించు AT91C_CAN_MTIMEMARK              ( ( గుర్తులేని పూర్ణాంకం ) 0xFFFF << 0 )  /* (CAN_MB) Mailbox Timemark */
#నిర్వచించు AT91_C_CAN_పూర్వ                  ( ( గుర్తులేని పూర్ణాంకం ) 0xF << 16 )    /* (CAN_MB) Mailbox Priority */
#నిర్వచించు AT91C_CAN_MOT                    ( ( గుర్తులేని పూర్ణాంకం ) 0x7 << 24 )    /* (CAN_MB) Mailbox Object Type */
#నిర్వచించు     AT91C_CAN_MOT_DIS            ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 24 )    /* (CAN_MB) */
#నిర్వచించు     AT91C_CAN_MOT_RX             ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 24 )    /* (CAN_MB) */
#నిర్వచించు     AT91C_CAN_MOT_RXOVERWRITE    ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 24 )    /* (CAN_MB) */
#నిర్వచించు     AT91C_CAN_MOT_TX             ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 24 )    /* (CAN_MB) */
#నిర్వచించు     AT91_C_CAN_MOT_వినియోగదారు       ( ( గుర్తులేని పూర్ణాంకం ) 0x4 << 24 )    /* (CAN_MB) */
#నిర్వచించు     AT91_C_CAN_MOT_ఉత్పాదకుడు       ( ( గుర్తులేని పూర్ణాంకం ) 0x5 << 24 )    /* (CAN_MB) */
/* -------- CAN_MAM : (CAN_MB Offset: 0x4) CAN Message Acceptance Mask Register -------- */
#నిర్వచించు AT91C_CAN_MIDvB                  ( ( గుర్తులేని పూర్ణాంకం ) 0x3FFFF << 0 ) /* (CAN_MB) Complementary bits for identifier in extended mode */
#నిర్వచించు AT91C_CAN_MIDvA                  ( ( గుర్తులేని పూర్ణాంకం ) 0x7FF << 18 )  /* (CAN_MB) Identifier for standard frame mode */
#నిర్వచించు AT91C_CAN_MIDE                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 29 )    /* (CAN_MB) Identifier Version */
/* -------- CAN_MID : (CAN_MB Offset: 0x8) CAN Message ID Register -------- */
/* -------- CAN_MFID : (CAN_MB Offset: 0xc) CAN Message Family ID Register -------- */
/* -------- CAN_MSR : (CAN_MB Offset: 0x10) CAN Message Status Register -------- */
#నిర్వచించు AT91C_CAN_MTIMESTAMP    ( ( గుర్తులేని పూర్ణాంకం ) 0xFFFF << 0 ) /* (CAN_MB) Timer Value */
#నిర్వచించు AT91C_CAN_MDLC          ( ( గుర్తులేని పూర్ణాంకం ) 0xF << 16 )   /* (CAN_MB) Mailbox Data Length Code */
#నిర్వచించు AT91C_CAN_MRTR          ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 20 )   /* (CAN_MB) Mailbox Remote Transmission Request */
#నిర్వచించు AT91C_CAN_MABT          ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 22 )   /* (CAN_MB) Mailbox Message Abort */
#నిర్వచించు AT91C_CAN_MRDY          ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 23 )   /* (CAN_MB) Mailbox Ready */
#నిర్వచించు AT91C_CAN_MMI           ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 24 )   /* (CAN_MB) Mailbox Message Ignored */
/* -------- CAN_MDL : (CAN_MB Offset: 0x14) CAN Message Data Low Register -------- */
/* -------- CAN_MDH : (CAN_MB Offset: 0x18) CAN Message Data High Register -------- */
/* -------- CAN_MCR : (CAN_MB Offset: 0x1c) CAN Message Control Register -------- */
#నిర్వచించు AT91C_CAN_MACR    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 22 ) /* (CAN_MB) Abort Request for Mailbox */
#నిర్వచించు AT91C_CAN_MTCR    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 23 ) /* (CAN_MB) Mailbox Transfer Command */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Control Area Network Interface */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_CAN
{
    AT91_REG CAN_MR;          /* Mode Register */
    AT91_REG CAN_IER;         /* Interrupt Enable Register */
    AT91_REG CAN_IDR;         /* Interrupt Disable Register */
    AT91_REG CAN_IMR;         /* Interrupt Mask Register */
    AT91_REG CAN_SR;          /* Status Register */
    AT91_REG CAN_BR;          /* Baudrate Register */
    AT91_REG CAN_TIM;         /* Timer Register */
    AT91_REG CAN_TIMESTP;     /* Time Stamp Register */
    AT91_REG CAN_ECR;         /* Error Counter Register */
    AT91_REG CAN_TCR;         /* Transfer Command Register */
    AT91_REG CAN_ACR;         /* Abort Command Register */
    AT91_REG Reserved0[ 52 ]; /* */
    AT91_REG CAN_VR;          /* Version Register */
    AT91_REG Reserved1[ 64 ]; /* */
    AT91S_CAN_MB CAN_MB0;     /* CAN Mailbox 0 */
    AT91S_CAN_MB CAN_MB1;     /* CAN Mailbox 1 */
    AT91S_CAN_MB CAN_MB2;     /* CAN Mailbox 2 */
    AT91S_CAN_MB CAN_MB3;     /* CAN Mailbox 3 */
    AT91S_CAN_MB CAN_MB4;     /* CAN Mailbox 4 */
    AT91S_CAN_MB CAN_MB5;     /* CAN Mailbox 5 */
    AT91S_CAN_MB CAN_MB6;     /* CAN Mailbox 6 */
    AT91S_CAN_MB CAN_MB7;     /* CAN Mailbox 7 */
    AT91S_CAN_MB CAN_MB8;     /* CAN Mailbox 8 */
    AT91S_CAN_MB CAN_MB9;     /* CAN Mailbox 9 */
    AT91S_CAN_MB CAN_MB10;    /* CAN Mailbox 10 */
    AT91S_CAN_MB CAN_MB11;    /* CAN Mailbox 11 */
    AT91S_CAN_MB CAN_MB12;    /* CAN Mailbox 12 */
    AT91S_CAN_MB CAN_MB13;    /* CAN Mailbox 13 */
    AT91S_CAN_MB CAN_MB14;    /* CAN Mailbox 14 */
    AT91S_CAN_MB CAN_MB15;    /* CAN Mailbox 15 */
} AT91S_CAN, * AT91PS_CAN;

/* -------- CAN_MR : (CAN Offset: 0x0) CAN Mode Register -------- */
#నిర్వచించు AT91C_CAN_CANEN     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )  /* (CAN) CAN Controller Enable */
#నిర్వచించు AT91C_CAN_LPM       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )  /* (CAN) Disable/Enable Low Power Mode */
#నిర్వచించు AT91C_CAN_ABM       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )  /* (CAN) Disable/Enable Autobaud/Listen Mode */
#నిర్వచించు AT91C_CAN_OVL       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )  /* (CAN) Disable/Enable Overload Frame */
#నిర్వచించు AT91C_CAN_TEOF      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )  /* (CAN) Time Stamp messages at each end of Frame */
#నిర్వచించు AT91C_CAN_TTM       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 )  /* (CAN) Disable/Enable Time Trigger Mode */
#నిర్వచించు AT91C_CAN_TIMFRZ    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 6 )  /* (CAN) Enable Timer Freeze */
#నిర్వచించు AT91C_CAN_DRPT      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )  /* (CAN) Disable Repeat */
/* -------- CAN_IER : (CAN Offset: 0x4) CAN Interrupt Enable Register -------- */
#నిర్వచించు AT91C_CAN_MB0       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )  /* (CAN) Mailbox 0 Flag */
#నిర్వచించు AT91C_CAN_MB1       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )  /* (CAN) Mailbox 1 Flag */
#నిర్వచించు AT91C_CAN_MB2       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )  /* (CAN) Mailbox 2 Flag */
#నిర్వచించు AT91C_CAN_MB3       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )  /* (CAN) Mailbox 3 Flag */
#నిర్వచించు AT91C_CAN_MB4       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )  /* (CAN) Mailbox 4 Flag */
#నిర్వచించు AT91C_CAN_MB5       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 )  /* (CAN) Mailbox 5 Flag */
#నిర్వచించు AT91C_CAN_MB6       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 6 )  /* (CAN) Mailbox 6 Flag */
#నిర్వచించు AT91C_CAN_MB7       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )  /* (CAN) Mailbox 7 Flag */
#నిర్వచించు AT91C_CAN_MB8       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )  /* (CAN) Mailbox 8 Flag */
#నిర్వచించు AT91C_CAN_MB9       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 9 )  /* (CAN) Mailbox 9 Flag */
#నిర్వచించు AT91C_CAN_MB10      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 10 ) /* (CAN) Mailbox 10 Flag */
#నిర్వచించు AT91C_CAN_MB11      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 11 ) /* (CAN) Mailbox 11 Flag */
#నిర్వచించు AT91C_CAN_MB12      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 12 ) /* (CAN) Mailbox 12 Flag */
#నిర్వచించు AT91C_CAN_MB13      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 13 ) /* (CAN) Mailbox 13 Flag */
#నిర్వచించు AT91C_CAN_MB14      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 14 ) /* (CAN) Mailbox 14 Flag */
#నిర్వచించు AT91C_CAN_MB15      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 15 ) /* (CAN) Mailbox 15 Flag */
#నిర్వచించు AT91C_CAN_ERRA      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 ) /* (CAN) Error Active Mode Flag */
#నిర్వచించు AT91C_CAN_WARN      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 17 ) /* (CAN) Warning Limit Flag */
#నిర్వచించు AT91C_CAN_ERRP      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 18 ) /* (CAN) Error Passive Mode Flag */
#నిర్వచించు AT91C_CAN_BOFF      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 19 ) /* (CAN) Bus Off Mode Flag */
#నిర్వచించు AT91C_CAN_SLEEP     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 20 ) /* (CAN) Sleep Flag */
#నిర్వచించు AT91C_CAN_WAKEUP    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 21 ) /* (CAN) Wakeup Flag */
#నిర్వచించు AT91C_CAN_TOVF      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 22 ) /* (CAN) Timer Overflow Flag */
#నిర్వచించు AT91C_CAN_TSTP      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 23 ) /* (CAN) Timestamp Flag */
#నిర్వచించు AT91C_CAN_CERR      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 24 ) /* (CAN) CRC Error */
#నిర్వచించు AT91C_CAN_SERR      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 25 ) /* (CAN) Stuffing Error */
#నిర్వచించు AT91C_CAN_AERR      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 26 ) /* (CAN) Acknowledgment Error */
#నిర్వచించు AT91C_CAN_FERR      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 27 ) /* (CAN) Form Error */
#నిర్వచించు AT91C_CAN_BERR      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 28 ) /* (CAN) Bit Error */
/* -------- CAN_IDR : (CAN Offset: 0x8) CAN Interrupt Disable Register -------- */
/* -------- CAN_IMR : (CAN Offset: 0xc) CAN Interrupt Mask Register -------- */
/* -------- CAN_SR : (CAN Offset: 0x10) CAN Status Register -------- */
#నిర్వచించు AT91C_CAN_RBSY      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 29 )   /* (CAN) Receiver Busy */
#నిర్వచించు AT91C_CAN_TBSY      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 30 )   /* (CAN) Transmitter Busy */
#నిర్వచించు AT91C_CAN_OVLY      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 31 )   /* (CAN) Overload Busy */
/* -------- CAN_BR : (CAN Offset: 0x14) CAN Baudrate Register -------- */
#నిర్వచించు AT91C_CAN_PHASE2    ( ( గుర్తులేని పూర్ణాంకం ) 0x7 << 0 )    /* (CAN) Phase 2 segment */
#నిర్వచించు AT91C_CAN_PHASE1    ( ( గుర్తులేని పూర్ణాంకం ) 0x7 << 4 )    /* (CAN) Phase 1 segment */
#నిర్వచించు AT91C_CAN_PROPAG    ( ( గుర్తులేని పూర్ణాంకం ) 0x7 << 8 )    /* (CAN) Programmation time segment */
#నిర్వచించు AT91C_CAN_SYNC      ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 12 )   /* (CAN) Re-synchronization jump width segment */
#నిర్వచించు AT91C_CAN_BRP       ( ( గుర్తులేని పూర్ణాంకం ) 0x7F << 16 )  /* (CAN) Baudrate Prescaler */
#నిర్వచించు AT91C_CAN_SMP       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 24 )   /* (CAN) Sampling mode */
/* -------- CAN_TIM : (CAN Offset: 0x18) CAN Timer Register -------- */
#నిర్వచించు AT91C_CAN_TIMER     ( ( గుర్తులేని పూర్ణాంకం ) 0xFFFF << 0 ) /* (CAN) Timer field */
/* -------- CAN_TIMESTP : (CAN Offset: 0x1c) CAN Timestamp Register -------- */
/* -------- CAN_ECR : (CAN Offset: 0x20) CAN Error Counter Register -------- */
#నిర్వచించు AT91C_CAN_REC       ( ( గుర్తులేని పూర్ణాంకం ) 0xFF << 0 )  /* (CAN) Receive Error Counter */
#నిర్వచించు AT91C_CAN_TEC       ( ( గుర్తులేని పూర్ణాంకం ) 0xFF << 16 ) /* (CAN) Transmit Error Counter */
/* -------- CAN_TCR : (CAN Offset: 0x24) CAN Transfer Command Register -------- */
#నిర్వచించు AT91C_CAN_TIMRST    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 31 )  /* (CAN) Timer Reset Field */
/* -------- CAN_ACR : (CAN Offset: 0x28) CAN Abort Command Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Ethernet MAC 10/100 */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_EMAC
{
    AT91_REG EMAC_NCR;        /* Network Control Register */
    AT91_REG EMAC_NCFGR;      /* Network Configuration Register */
    AT91_REG EMAC_NSR;        /* Network Status Register */
    AT91_REG Reserved0[ 2 ];  /* */
    AT91_REG EMAC_TSR;        /* Transmit Status Register */
    AT91_REG EMAC_RBQP;       /* Receive Buffer Queue Pointer */
    AT91_REG EMAC_TBQP;       /* Transmit Buffer Queue Pointer */
    AT91_REG EMAC_RSR;        /* Receive Status Register */
    AT91_REG EMAC_ISR;        /* Interrupt Status Register */
    AT91_REG EMAC_IER;        /* Interrupt Enable Register */
    AT91_REG EMAC_IDR;        /* Interrupt Disable Register */
    AT91_REG EMAC_IMR;        /* Interrupt Mask Register */
    AT91_REG EMAC_MAN;        /* PHY Maintenance Register */
    AT91_REG EMAC_PTR;        /* Pause Time Register */
    AT91_REG EMAC_PFR;        /* Pause Frames received Register */
    AT91_REG EMAC_FTO;        /* Frames Transmitted OK Register */
    AT91_REG EMAC_SCF;        /* Single Collision Frame Register */
    AT91_REG EMAC_MCF;        /* Multiple Collision Frame Register */
    AT91_REG EMAC_FRO;        /* Frames Received OK Register */
    AT91_REG EMAC_FCSE;       /* Frame Check Sequence Error Register */
    AT91_REG EMAC_ALE;        /* Alignment Error Register */
    AT91_REG EMAC_DTF;        /* Deferred Transmission Frame Register */
    AT91_REG EMAC_LCOL;       /* Late Collision Register */
    AT91_REG EMAC_ECOL;       /* Excessive Collision Register */
    AT91_REG EMAC_TUND;       /* Transmit Underrun Error Register */
    AT91_REG EMAC_CSE;        /* Carrier Sense Error Register */
    AT91_REG EMAC_RRE;        /* Receive Resource Error Register */
    AT91_REG EMAC_ROV;        /* Receive Overrun Errors Register */
    AT91_REG EMAC_RSE;        /* Receive Symbol Errors Register */
    AT91_REG EMAC_ELE;        /* Excessive Length Errors Register */
    AT91_REG EMAC_RJA;        /* Receive Jabbers Register */
    AT91_REG EMAC_USF;        /* Undersize Frames Register */
    AT91_REG EMAC_STE;        /* SQE Test Error Register */
    AT91_REG EMAC_RLE;        /* Receive Length Field Mismatch Register */
    AT91_REG EMAC_TPF;        /* Transmitted Pause Frames Register */
    AT91_REG EMAC_HRB;        /* Hash Address Bottom[31:0] */
    AT91_REG EMAC_HRT;        /* Hash Address Top[63:32] */
    AT91_REG EMAC_SA1L;       /* Specific Address 1 Bottom, First 4 bytes */
    AT91_REG EMAC_SA1H;       /* Specific Address 1 Top, Last 2 bytes */
    AT91_REG EMAC_SA2L;       /* Specific Address 2 Bottom, First 4 bytes */
    AT91_REG EMAC_SA2H;       /* Specific Address 2 Top, Last 2 bytes */
    AT91_REG EMAC_SA3L;       /* Specific Address 3 Bottom, First 4 bytes */
    AT91_REG EMAC_SA3H;       /* Specific Address 3 Top, Last 2 bytes */
    AT91_REG EMAC_SA4L;       /* Specific Address 4 Bottom, First 4 bytes */
    AT91_REG EMAC_SA4H;       /* Specific Address 4 Top, Last 2 bytes */
    AT91_REG EMAC_TID;        /* Type ID Checking Register */
    AT91_REG EMAC_TPQ;        /* Transmit Pause Quantum Register */
    AT91_REG EMAC_USRIO;      /* USER Input/Output Register */
    AT91_REG EMAC_WOL;        /* Wake On LAN Register */
    AT91_REG Reserved1[ 13 ]; /* */
    AT91_REG EMAC_REV;        /* Revision Register */
} AT91S_EMAC, * AT91PS_EMAC;

/* -------- EMAC_NCR : (EMAC Offset: 0x0)  -------- */
#నిర్వచించు AT91C_EMAC_LB                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )  /* (EMAC) Loopback. Optional. When set, loopback signal is at high level. */
#నిర్వచించు AT91C_EMAC_LLB                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )  /* (EMAC) Loopback local. */
#నిర్వచించు AT91C_EMAC_RE                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )  /* (EMAC) Receive enable. */
#నిర్వచించు AT91C_EMAC_TE                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )  /* (EMAC) Transmit enable. */
#నిర్వచించు AT91C_EMAC_MPE                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )  /* (EMAC) Management port enable. */
#నిర్వచించు AT91C_EMAC_CLRSTAT              ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 )  /* (EMAC) Clear statistics registers. */
#నిర్వచించు AT91C_EMAC_INCSTAT              ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 6 )  /* (EMAC) Increment statistics registers. */
#నిర్వచించు AT91C_EMAC_WESTAT               ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )  /* (EMAC) Write enable for statistics registers. */
#నిర్వచించు AT91C_EMAC_BP                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )  /* (EMAC) Back pressure. */
#నిర్వచించు AT91C_EMAC_TSTART               ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 9 )  /* (EMAC) Start Transmission. */
#నిర్వచించు AT91C_EMAC_THALT                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 10 ) /* (EMAC) Transmission Halt. */
#నిర్వచించు AT91C_EMAC_TPFR                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 11 ) /* (EMAC) Transmit pause frame */
#నిర్వచించు AT91C_EMAC_TZQ                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 12 ) /* (EMAC) Transmit zero quantum pause frame */
/* -------- EMAC_NCFGR : (EMAC Offset: 0x4) Network Configuration Register -------- */
#నిర్వచించు AT91C_EMAC_SPD                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )  /* (EMAC) Speed. */
#నిర్వచించు AT91C_EMAC_FD                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )  /* (EMAC) Full duplex. */
#నిర్వచించు AT91C_EMAC_JFRAME               ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )  /* (EMAC) Jumbo Frames. */
#నిర్వచించు AT91C_EMAC_CAF                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )  /* (EMAC) Copy all frames. */
#నిర్వచించు AT91C_EMAC_NBC                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 )  /* (EMAC) No broadcast. */
#నిర్వచించు AT91C_EMAC_MTI                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 6 )  /* (EMAC) Multicast hash event enable */
#నిర్వచించు AT91C_EMAC_UNI                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )  /* (EMAC) Unicast hash enable. */
#నిర్వచించు AT91C_EMAC_BIG                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )  /* (EMAC) Receive 1522 bytes. */
#నిర్వచించు AT91C_EMAC_EAE                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 9 )  /* (EMAC) External address match enable. */
#నిర్వచించు AT91C_EMAC_CLK                  ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 10 ) /* (EMAC) */
#నిర్వచించు     AT91C_EMAC_CLK_HCLK_8       ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 10 ) /* (EMAC) HCLK divided by 8 */
#నిర్వచించు     AT91C_EMAC_CLK_HCLK_16      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 10 ) /* (EMAC) HCLK divided by 16 */
#నిర్వచించు     AT91C_EMAC_CLK_HCLK_32      ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 10 ) /* (EMAC) HCLK divided by 32 */
#నిర్వచించు     AT91C_EMAC_CLK_HCLK_64      ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 10 ) /* (EMAC) HCLK divided by 64 */
#నిర్వచించు AT91C_EMAC_RTY                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 12 ) /* (EMAC) */
#నిర్వచించు AT91C_EMAC_PAE                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 13 ) /* (EMAC) */
#నిర్వచించు AT91C_EMAC_RBOF                 ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 14 ) /* (EMAC) */
#నిర్వచించు     AT91_C_EMAC_RBOF_స్థానభ్రంశం_0    ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 14 ) /* (EMAC) no offset from start of receive buffer */
#నిర్వచించు     AT91_C_EMAC_RBOF_స్థానభ్రంశం_1    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 14 ) /* (EMAC) one byte offset from start of receive buffer */
#నిర్వచించు     AT91_C_EMAC_RBOF_స్థానభ్రంశం_2    ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 14 ) /* (EMAC) two bytes offset from start of receive buffer */
#నిర్వచించు     AT91_C_EMAC_RBOF_స్థానభ్రంశం_3    ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 14 ) /* (EMAC) three bytes offset from start of receive buffer */
#నిర్వచించు AT91C_EMAC_RLCE                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 ) /* (EMAC) Receive Length field Checking Enable */
#నిర్వచించు AT91C_EMAC_DRFCS                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 17 ) /* (EMAC) Discard Receive FCS */
#నిర్వచించు AT91C_EMAC_EFRHD                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 18 ) /* (EMAC) */
#నిర్వచించు AT91C_EMAC_IRXFCS               ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 19 ) /* (EMAC) Ignore RX FCS */
/* -------- EMAC_NSR : (EMAC Offset: 0x8) Network Status Register -------- */
#నిర్వచించు AT91C_EMAC_LINKR                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )  /* (EMAC) */
#నిర్వచించు AT91C_EMAC_MDIO                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )  /* (EMAC) */
#నిర్వచించు AT91C_EMAC_IDLE                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )  /* (EMAC) */
/* -------- EMAC_TSR : (EMAC Offset: 0x14) Transmit Status Register -------- */
#నిర్వచించు AT91C_EMAC_UBR                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )  /* (EMAC) */
#నిర్వచించు AT91_C_EMAC_నిలువు                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )  /* (EMAC) */
#నిర్వచించు AT91C_EMAC_RLES                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )  /* (EMAC) */
#నిర్వచించు AT91C_EMAC_TGO                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )  /* (EMAC) Transmit Go */
#నిర్వచించు AT91C_EMAC_BEX                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )  /* (EMAC) Buffers exhausted mid frame */
#నిర్వచించు AT91C_EMAC_COMP                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 )  /* (EMAC) */
#నిర్వచించు AT91C_EMAC_UND                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 6 )  /* (EMAC) */
/* -------- EMAC_RSR : (EMAC Offset: 0x20) Receive Status Register -------- */
#నిర్వచించు AT91C_EMAC_BNA                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )  /* (EMAC) */
#నిర్వచించు AT91C_EMAC_REC                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )  /* (EMAC) */
#నిర్వచించు AT91C_EMAC_OVR                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )  /* (EMAC) */
/* -------- EMAC_ISR : (EMAC Offset: 0x24) Interrupt Status Register -------- */
#నిర్వచించు AT91C_EMAC_MFD                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )  /* (EMAC) */
#నిర్వచించు AT91C_EMAC_RCOMP                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )  /* (EMAC) */
#నిర్వచించు AT91C_EMAC_RXUBR                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )  /* (EMAC) */
#నిర్వచించు AT91C_EMAC_TXUBR                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )  /* (EMAC) */
#నిర్వచించు AT91C_EMAC_TUNDR                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )  /* (EMAC) */
#నిర్వచించు AT91C_EMAC_RLEX                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 )  /* (EMAC) */
#నిర్వచించు AT91C_EMAC_TXERR                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 6 )  /* (EMAC) */
#నిర్వచించు AT91C_EMAC_TCOMP                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )  /* (EMAC) */
#నిర్వచించు AT91C_EMAC_LINK                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 9 )  /* (EMAC) */
#నిర్వచించు AT91C_EMAC_ROVR                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 10 ) /* (EMAC) */
#నిర్వచించు AT91C_EMAC_HRESP                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 11 ) /* (EMAC) */
#నిర్వచించు AT91C_EMAC_PFRE                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 12 ) /* (EMAC) */
#నిర్వచించు AT91C_EMAC_PTZ                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 13 ) /* (EMAC) */
/* -------- EMAC_IER : (EMAC Offset: 0x28) Interrupt Enable Register -------- */
/* -------- EMAC_IDR : (EMAC Offset: 0x2c) Interrupt Disable Register -------- */
/* -------- EMAC_IMR : (EMAC Offset: 0x30) Interrupt Mask Register -------- */
/* -------- EMAC_MAN : (EMAC Offset: 0x34) PHY Maintenance Register -------- */
#నిర్వచించు AT91_C_EMAC_దత్తాంశం       ( ( గుర్తులేని పూర్ణాంకం ) 0xFFFF << 0 )  /* (EMAC) */
#నిర్వచించు AT91_C_EMAC_సంకేతం       ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 16 )    /* (EMAC) */
#నిర్వచించు AT91C_EMAC_REGA       ( ( గుర్తులేని పూర్ణాంకం ) 0x1F << 18 )   /* (EMAC) */
#నిర్వచించు AT91C_EMAC_PHYA       ( ( గుర్తులేని పూర్ణాంకం ) 0x1F << 23 )   /* (EMAC) */
#నిర్వచించు AT91C_EMAC_RW         ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 28 )    /* (EMAC) */
#నిర్వచించు AT91C_EMAC_SOF        ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 30 )    /* (EMAC) */
/* -------- EMAC_USRIO : (EMAC Offset: 0xc0) USER Input Output Register -------- */
#నిర్వచించు AT91C_EMAC_RMII       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )     /* (EMAC) Reduce MII */
/* -------- EMAC_WOL : (EMAC Offset: 0xc4) Wake On LAN Register -------- */
#నిర్వచించు AT91C_EMAC_IP         ( ( గుర్తులేని పూర్ణాంకం ) 0xFFFF << 0 )  /* (EMAC) ARP request IP address */
#నిర్వచించు AT91C_EMAC_MAG        ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 )    /* (EMAC) Magic packet event enable */
#నిర్వచించు AT91C_EMAC_ARP        ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 17 )    /* (EMAC) ARP request event enable */
#నిర్వచించు AT91C_EMAC_SA1        ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 18 )    /* (EMAC) Specific address register 1 event enable */
/* -------- EMAC_REV : (EMAC Offset: 0xfc) Revision Register -------- */
#నిర్వచించు AT91C_EMAC_REVREF     ( ( గుర్తులేని పూర్ణాంకం ) 0xFFFF << 0 )  /* (EMAC) */
#నిర్వచించు AT91C_EMAC_PARTREF    ( ( గుర్తులేని పూర్ణాంకం ) 0xFFFF << 16 ) /* (EMAC) */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Analog to Digital Convertor */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_ADC
{
    AT91_REG ADC_CR;          /* ADC Control Register */
    AT91_REG ADC_MR;          /* ADC Mode Register */
    AT91_REG Reserved0[ 2 ];  /* */
    AT91_REG ADC_CHER;        /* ADC Channel Enable Register */
    AT91_REG ADC_CHDR;        /* ADC Channel Disable Register */
    AT91_REG ADC_CHSR;        /* ADC Channel Status Register */
    AT91_REG ADC_SR;          /* ADC Status Register */
    AT91_REG ADC_LCDR;        /* ADC Last Converted Data Register */
    AT91_REG ADC_IER;         /* ADC Interrupt Enable Register */
    AT91_REG ADC_IDR;         /* ADC Interrupt Disable Register */
    AT91_REG ADC_IMR;         /* ADC Interrupt Mask Register */
    AT91_REG ADC_CDR0;        /* ADC Channel Data Register 0 */
    AT91_REG ADC_CDR1;        /* ADC Channel Data Register 1 */
    AT91_REG ADC_CDR2;        /* ADC Channel Data Register 2 */
    AT91_REG ADC_CDR3;        /* ADC Channel Data Register 3 */
    AT91_REG ADC_CDR4;        /* ADC Channel Data Register 4 */
    AT91_REG ADC_CDR5;        /* ADC Channel Data Register 5 */
    AT91_REG ADC_CDR6;        /* ADC Channel Data Register 6 */
    AT91_REG ADC_CDR7;        /* ADC Channel Data Register 7 */
    AT91_REG Reserved1[ 44 ]; /* */
    AT91_REG ADC_RPR;         /* Receive Pointer Register */
    AT91_REG ADC_RCR;         /* Receive Counter Register */
    AT91_REG ADC_TPR;         /* Transmit Pointer Register */
    AT91_REG ADC_TCR;         /* Transmit Counter Register */
    AT91_REG ADC_RNPR;        /* Receive Next Pointer Register */
    AT91_REG ADC_RNCR;        /* Receive Next Counter Register */
    AT91_REG ADC_TNPR;        /* Transmit Next Pointer Register */
    AT91_REG ADC_TNCR;        /* Transmit Next Counter Register */
    AT91_REG ADC_PTCR;        /* PDC Transfer Control Register */
    AT91_REG ADC_PTSR;        /* PDC Transfer Status Register */
} AT91S_ADC, * AT91PS_ADC;

/* -------- ADC_CR : (ADC Offset: 0x0) ADC Control Register -------- */
#నిర్వచించు AT91C_ADC_SWRST                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )   /* (ADC) Software Reset */
#నిర్వచించు AT91_C_ADC_ప్రారంభం                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )   /* (ADC) Start Conversion */
/* -------- ADC_MR : (ADC Offset: 0x4) ADC Mode Register -------- */
#నిర్వచించు AT91C_ADC_TRGEN                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )   /* (ADC) Trigger Enable */
#నిర్వచించు     AT91C_ADC_TRGEN_DIS            ( ( గుర్తులేని పూర్ణాంకం ) 0x0 )        /* (ADC) Hardware triggers are disabled. Starting a conversion is only possible by software */
#నిర్వచించు     AT91C_ADC_TRGEN_EN             ( ( గుర్తులేని పూర్ణాంకం ) 0x1 )        /* (ADC) Hardware trigger selected by TRGSEL field is enabled. */
#నిర్వచించు AT91C_ADC_TRGSEL                   ( ( గుర్తులేని పూర్ణాంకం ) 0x7 << 1 )   /* (ADC) Trigger Selection */
#నిర్వచించు     AT91C_ADC_TRGSEL_TIOA0         ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 1 )   /* (ADC) Selected TRGSEL = TIAO0 */
#నిర్వచించు     AT91C_ADC_TRGSEL_TIOA1         ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )   /* (ADC) Selected TRGSEL = TIAO1 */
#నిర్వచించు     AT91C_ADC_TRGSEL_TIOA2         ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 1 )   /* (ADC) Selected TRGSEL = TIAO2 */
#నిర్వచించు     AT91C_ADC_TRGSEL_TIOA3         ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 1 )   /* (ADC) Selected TRGSEL = TIAO3 */
#నిర్వచించు     AT91C_ADC_TRGSEL_TIOA4         ( ( గుర్తులేని పూర్ణాంకం ) 0x4 << 1 )   /* (ADC) Selected TRGSEL = TIAO4 */
#నిర్వచించు     AT91C_ADC_TRGSEL_TIOA5         ( ( గుర్తులేని పూర్ణాంకం ) 0x5 << 1 )   /* (ADC) Selected TRGSEL = TIAO5 */
#నిర్వచించు     AT91C_ADC_TRGSEL_EXT           ( ( గుర్తులేని పూర్ణాంకం ) 0x6 << 1 )   /* (ADC) Selected TRGSEL = External Trigger */
#నిర్వచించు AT91C_ADC_LOWRES                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )   /* (ADC) Resolution. */
#నిర్వచించు     AT91_C_ADC_LOWRES_10_బిట్టు        ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 4 )   /* (ADC) 10-bit resolution */
#నిర్వచించు     AT91_C_ADC_LOWRES_8_బిట్టు         ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )   /* (ADC) 8-bit resolution */
#నిర్వచించు AT91C_ADC_SLEEP                    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 )   /* (ADC) Sleep Mode */
#నిర్వచించు     AT91_C_ADC_SLEEP_సాధారణ_బహుళకం    ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 5 )   /* (ADC) Normal Mode */
#నిర్వచించు     AT91_C_ADC_SLEEP_బహుళకం           ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 )   /* (ADC) Sleep Mode */
#నిర్వచించు AT91C_ADC_PRESCAL                  ( ( గుర్తులేని పూర్ణాంకం ) 0x3F << 8 )  /* (ADC) Prescaler rate selection */
#నిర్వచించు AT91C_ADC_STARTUP                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1F << 16 ) /* (ADC) Startup Time */
#నిర్వచించు AT91C_ADC_SHTIM                    ( ( గుర్తులేని పూర్ణాంకం ) 0xF << 24 )  /* (ADC) Sample & Hold Time */
/* --------     ADC_CHER : (ADC Offset: 0x10) ADC Channel Enable Register -------- */
#నిర్వచించు AT91C_ADC_CH0                      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )   /* (ADC) Channel 0 */
#నిర్వచించు AT91C_ADC_CH1                      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )   /* (ADC) Channel 1 */
#నిర్వచించు AT91C_ADC_CH2                      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )   /* (ADC) Channel 2 */
#నిర్వచించు AT91C_ADC_CH3                      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )   /* (ADC) Channel 3 */
#నిర్వచించు AT91C_ADC_CH4                      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )   /* (ADC) Channel 4 */
#నిర్వచించు AT91C_ADC_CH5                      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 )   /* (ADC) Channel 5 */
#నిర్వచించు AT91C_ADC_CH6                      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 6 )   /* (ADC) Channel 6 */
#నిర్వచించు AT91C_ADC_CH7                      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )   /* (ADC) Channel 7 */
/* --------     ADC_CHDR : (ADC Offset: 0x14) ADC Channel Disable Register -------- */
/* --------     ADC_CHSR : (ADC Offset: 0x18) ADC Channel Status Register -------- */
/* -------- ADC_SR : (ADC Offset: 0x1c) ADC Status Register -------- */
#నిర్వచించు AT91C_ADC_EOC0      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )   /* (ADC) End of Conversion */
#నిర్వచించు AT91C_ADC_EOC1      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )   /* (ADC) End of Conversion */
#నిర్వచించు AT91C_ADC_EOC2      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )   /* (ADC) End of Conversion */
#నిర్వచించు AT91C_ADC_EOC3      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )   /* (ADC) End of Conversion */
#నిర్వచించు AT91C_ADC_EOC4      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )   /* (ADC) End of Conversion */
#నిర్వచించు AT91C_ADC_EOC5      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 5 )   /* (ADC) End of Conversion */
#నిర్వచించు AT91C_ADC_EOC6      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 6 )   /* (ADC) End of Conversion */
#నిర్వచించు AT91C_ADC_EOC7      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 7 )   /* (ADC) End of Conversion */
#నిర్వచించు AT91C_ADC_OVRE0     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )   /* (ADC) Overrun Error */
#నిర్వచించు AT91C_ADC_OVRE1     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 9 )   /* (ADC) Overrun Error */
#నిర్వచించు AT91C_ADC_OVRE2     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 10 )  /* (ADC) Overrun Error */
#నిర్వచించు AT91C_ADC_OVRE3     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 11 )  /* (ADC) Overrun Error */
#నిర్వచించు AT91C_ADC_OVRE4     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 12 )  /* (ADC) Overrun Error */
#నిర్వచించు AT91C_ADC_OVRE5     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 13 )  /* (ADC) Overrun Error */
#నిర్వచించు AT91C_ADC_OVRE6     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 14 )  /* (ADC) Overrun Error */
#నిర్వచించు AT91C_ADC_OVRE7     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 15 )  /* (ADC) Overrun Error */
#నిర్వచించు AT91C_ADC_DRDY      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 )  /* (ADC) Data Ready */
#నిర్వచించు AT91C_ADC_GOVRE     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 17 )  /* (ADC) General Overrun */
#నిర్వచించు AT91C_ADC_ENDRX     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 18 )  /* (ADC) End of Receiver Transfer */
#నిర్వచించు AT91C_ADC_RXBUFF    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 19 )  /* (ADC) RXBUFF Interrupt */
/* -------- ADC_LCDR : (ADC Offset: 0x20) ADC Last Converted Data Register -------- */
#నిర్వచించు AT91C_ADC_LDATA     ( ( గుర్తులేని పూర్ణాంకం ) 0x3FF << 0 ) /* (ADC) Last Data Converted */
/* -------- ADC_IER : (ADC Offset: 0x24) ADC Interrupt Enable Register -------- */
/* -------- ADC_IDR : (ADC Offset: 0x28) ADC Interrupt Disable Register -------- */
/* -------- ADC_IMR : (ADC Offset: 0x2c) ADC Interrupt Mask Register -------- */
/* -------- ADC_CDR0 : (ADC Offset: 0x30) ADC Channel Data Register 0 -------- */
#నిర్వచించు AT91_C_ADC_దత్తాంశం    ( ( గుర్తులేని పూర్ణాంకం ) 0x3FF << 0 )  /* (ADC) Converted Data */
/* -------- ADC_CDR1 : (ADC Offset: 0x34) ADC Channel Data Register 1 -------- */
/* -------- ADC_CDR2 : (ADC Offset: 0x38) ADC Channel Data Register 2 -------- */
/* -------- ADC_CDR3 : (ADC Offset: 0x3c) ADC Channel Data Register 3 -------- */
/* -------- ADC_CDR4 : (ADC Offset: 0x40) ADC Channel Data Register 4 -------- */
/* -------- ADC_CDR5 : (ADC Offset: 0x44) ADC Channel Data Register 5 -------- */
/* -------- ADC_CDR6 : (ADC Offset: 0x48) ADC Channel Data Register 6 -------- */
/* -------- ADC_CDR7 : (ADC Offset: 0x4c) ADC Channel Data Register 7 -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Advanced  Encryption Standard */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_AES
{
    AT91_REG AES_CR;           /* Control Register */
    AT91_REG AES_MR;           /* Mode Register */
    AT91_REG Reserved0[ 2 ];   /* */
    AT91_REG AES_IER;          /* Interrupt Enable Register */
    AT91_REG AES_IDR;          /* Interrupt Disable Register */
    AT91_REG AES_IMR;          /* Interrupt Mask Register */
    AT91_REG AES_ISR;          /* Interrupt Status Register */
    AT91_REG AES_KEYWxR[ 4 ];  /* Key Word x Register */
    AT91_REG Reserved1[ 4 ];   /* */
    AT91_REG AES_IDATAxR[ 4 ]; /* Input Data x Register */
    AT91_REG AES_ODATAxR[ 4 ]; /* Output Data x Register */
    AT91_REG AES_IVxR[ 4 ];    /* Initialization Vector x Register */
    AT91_REG Reserved2[ 35 ];  /* */
    AT91_REG AES_VR;           /* AES Version Register */
    AT91_REG AES_RPR;          /* Receive Pointer Register */
    AT91_REG AES_RCR;          /* Receive Counter Register */
    AT91_REG AES_TPR;          /* Transmit Pointer Register */
    AT91_REG AES_TCR;          /* Transmit Counter Register */
    AT91_REG AES_RNPR;         /* Receive Next Pointer Register */
    AT91_REG AES_RNCR;         /* Receive Next Counter Register */
    AT91_REG AES_TNPR;         /* Transmit Next Pointer Register */
    AT91_REG AES_TNCR;         /* Transmit Next Counter Register */
    AT91_REG AES_PTCR;         /* PDC Transfer Control Register */
    AT91_REG AES_PTSR;         /* PDC Transfer Status Register */
} AT91S_AES, * AT91PS_AES;

/* -------- AES_CR : (AES Offset: 0x0) Control Register -------- */
#నిర్వచించు AT91_C_AES_ప్రారంభం                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )   /* (AES) Starts Processing */
#నిర్వచించు AT91C_AES_SWRST                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )   /* (AES) Software Reset */
#నిర్వచించు AT91C_AES_LOADSEED              ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 )  /* (AES) Random Number Generator Seed Loading */
/* -------- AES_MR : (AES Offset: 0x4) Mode Register -------- */
#నిర్వచించు AT91C_AES_CIPHER                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )   /* (AES) Processing Mode */
#నిర్వచించు AT91C_AES_PROCDLY               ( ( గుర్తులేని పూర్ణాంకం ) 0xF << 4 )   /* (AES) Processing Delay */
#నిర్వచించు AT91C_AES_SMOD                  ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 8 )   /* (AES) Start Mode */
#నిర్వచించు     AT91C_AES_SMOD_MANUAL       ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 8 )   /* (AES) Manual Mode: The START bit in register AES_CR must be set to begin encryption or decryption. */
#నిర్వచించు     AT91C_AES_SMOD_AUTO         ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )   /* (AES) Auto Mode: no action in AES_CR is necessary (cf datasheet). */
#నిర్వచించు     AT91C_AES_SMOD_PDC          ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 8 )   /* (AES) PDC Mode (cf datasheet). */
#నిర్వచించు AT91C_AES_OPMOD                 ( ( గుర్తులేని పూర్ణాంకం ) 0x7 << 12 )  /* (AES) Operation Mode */
#నిర్వచించు     AT91C_AES_OPMOD_ECB         ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 12 )  /* (AES) ECB Electronic CodeBook mode. */
#నిర్వచించు     AT91C_AES_OPMOD_CBC         ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 12 )  /* (AES) CBC Cipher Block Chaining mode. */
#నిర్వచించు     AT91C_AES_OPMOD_OFB         ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 12 )  /* (AES) OFB Output Feedback mode. */
#నిర్వచించు     AT91C_AES_OPMOD_CFB         ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 12 )  /* (AES) CFB Cipher Feedback mode. */
#నిర్వచించు     AT91C_AES_OPMOD_CTR         ( ( గుర్తులేని పూర్ణాంకం ) 0x4 << 12 )  /* (AES) CTR Counter mode. */
#నిర్వచించు AT91C_AES_LOD                   ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 15 )  /* (AES) Last Output Data Mode */
#నిర్వచించు AT91C_AES_CFBS                  ( ( గుర్తులేని పూర్ణాంకం ) 0x7 << 16 )  /* (AES) Cipher Feedback Data Size */
#నిర్వచించు     AT91_C_AES_CFBS_128_బిట్టు      ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 16 )  /* (AES) 128-bit. */
#నిర్వచించు     AT91_C_AES_CFBS_64_బిట్టు       ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 )  /* (AES) 64-bit. */
#నిర్వచించు     AT91_C_AES_CFBS_32_బిట్టు       ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 16 )  /* (AES) 32-bit. */
#నిర్వచించు     AT91_C_AES_CFBS_16_బిట్టు       ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 16 )  /* (AES) 16-bit. */
#నిర్వచించు     AT91_C_AES_CFBS_8_బిట్టు        ( ( గుర్తులేని పూర్ణాంకం ) 0x4 << 16 )  /* (AES) 8-bit. */
#నిర్వచించు AT91C_AES_CKEY                  ( ( గుర్తులేని పూర్ణాంకం ) 0xF << 20 )  /* (AES) Countermeasure Key */
#నిర్వచించు AT91C_AES_CTYPE                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1F << 24 ) /* (AES) Countermeasure Type */
#నిర్వచించు     AT91C_AES_CTYPE_TYPE1_EN    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 24 )  /* (AES) Countermeasure type 1 is enabled. */
#నిర్వచించు     AT91C_AES_CTYPE_TYPE2_EN    ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 24 )  /* (AES) Countermeasure type 2 is enabled. */
#నిర్వచించు     AT91C_AES_CTYPE_TYPE3_EN    ( ( గుర్తులేని పూర్ణాంకం ) 0x4 << 24 )  /* (AES) Countermeasure type 3 is enabled. */
#నిర్వచించు     AT91C_AES_CTYPE_TYPE4_EN    ( ( గుర్తులేని పూర్ణాంకం ) 0x8 << 24 )  /* (AES) Countermeasure type 4 is enabled. */
#నిర్వచించు     AT91C_AES_CTYPE_TYPE5_EN    ( ( గుర్తులేని పూర్ణాంకం ) 0x10 << 24 ) /* (AES) Countermeasure type 5 is enabled. */
/* -------- AES_IER : (AES Offset: 0x10) Interrupt Enable Register -------- */
#నిర్వచించు AT91C_AES_DATRDY                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )   /* (AES) DATRDY */
#నిర్వచించు AT91C_AES_ENDRX                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )   /* (AES) PDC Read Buffer End */
#నిర్వచించు AT91C_AES_ENDTX                 ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )   /* (AES) PDC Write Buffer End */
#నిర్వచించు AT91C_AES_RXBUFF                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )   /* (AES) PDC Read Buffer Full */
#నిర్వచించు AT91C_AES_TXBUFE                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )   /* (AES) PDC Write Buffer Empty */
#నిర్వచించు AT91C_AES_URAD                  ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )   /* (AES) Unspecified Register Access Detection */
/* -------- AES_IDR : (AES Offset: 0x14) Interrupt Disable Register -------- */
/* -------- AES_IMR : (AES Offset: 0x18) Interrupt Mask Register -------- */
/* -------- AES_ISR : (AES Offset: 0x1c) Interrupt Status Register -------- */
#నిర్వచించు AT91C_AES_URAT                              ( ( గుర్తులేని పూర్ణాంకం ) 0x7 << 12 ) /* (AES) Unspecified Register Access Type Status */
#నిర్వచించు     AT91_C_AES_URAT_లోపల_DAT_WRITE_DATPROC     ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 12 ) /* (AES) Input data register written during the data processing in PDC mode. */
#నిర్వచించు     AT91_C_AES_URAT_బహిర్గతం_DAT_READ_DATPROC     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 12 ) /* (AES) Output data register read during the data processing. */
#నిర్వచించు     AT91C_AES_URAT_MODEREG_WRITE_DATPROC    ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 12 ) /* (AES) Mode register written during the data processing. */
#నిర్వచించు     AT91_C_AES_URAT_బహిర్గతం_DAT_READ_SUBKEY      ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 12 ) /* (AES) Output data register read during the sub-keys generation. */
#నిర్వచించు     AT91C_AES_URAT_MODEREG_WRITE_SUBKEY     ( ( గుర్తులేని పూర్ణాంకం ) 0x4 << 12 ) /* (AES) Mode register written during the sub-keys generation. */
#నిర్వచించు     AT91C_AES_URAT_WO_REG_READ              ( ( గుర్తులేని పూర్ణాంకం ) 0x5 << 12 ) /* (AES) Write-only register read access. */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Triple Data Encryption Standard */
/* ***************************************************************************** */
రకనిర్వచనం నిర్మాణం _AT91S_TDES
{
    AT91_REG TDES_CR;           /* Control Register */
    AT91_REG TDES_MR;           /* Mode Register */
    AT91_REG Reserved0[ 2 ];    /* */
    AT91_REG TDES_IER;          /* Interrupt Enable Register */
    AT91_REG TDES_IDR;          /* Interrupt Disable Register */
    AT91_REG TDES_IMR;          /* Interrupt Mask Register */
    AT91_REG TDES_ISR;          /* Interrupt Status Register */
    AT91_REG TDES_KEY1WxR[ 2 ]; /* Key 1 Word x Register */
    AT91_REG TDES_KEY2WxR[ 2 ]; /* Key 2 Word x Register */
    AT91_REG TDES_KEY3WxR[ 2 ]; /* Key 3 Word x Register */
    AT91_REG Reserved1[ 2 ];    /* */
    AT91_REG TDES_IDATAxR[ 2 ]; /* Input Data x Register */
    AT91_REG Reserved2[ 2 ];    /* */
    AT91_REG TDES_ODATAxR[ 2 ]; /* Output Data x Register */
    AT91_REG Reserved3[ 2 ];    /* */
    AT91_REG TDES_IVxR[ 2 ];    /* Initialization Vector x Register */
    AT91_REG Reserved4[ 37 ];   /* */
    AT91_REG TDES_VR;           /* TDES Version Register */
    AT91_REG TDES_RPR;          /* Receive Pointer Register */
    AT91_REG TDES_RCR;          /* Receive Counter Register */
    AT91_REG TDES_TPR;          /* Transmit Pointer Register */
    AT91_REG TDES_TCR;          /* Transmit Counter Register */
    AT91_REG TDES_RNPR;         /* Receive Next Pointer Register */
    AT91_REG TDES_RNCR;         /* Receive Next Counter Register */
    AT91_REG TDES_TNPR;         /* Transmit Next Pointer Register */
    AT91_REG TDES_TNCR;         /* Transmit Next Counter Register */
    AT91_REG TDES_PTCR;         /* PDC Transfer Control Register */
    AT91_REG TDES_PTSR;         /* PDC Transfer Status Register */
} AT91S_TDES, * AT91PS_TDES;

/* -------- TDES_CR : (TDES Offset: 0x0) Control Register -------- */
#నిర్వచించు AT91_C_TDES_ప్రారంభం              ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )  /* (TDES) Starts Processing */
#నిర్వచించు AT91C_TDES_SWRST              ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )  /* (TDES) Software Reset */
/* -------- TDES_MR : (TDES Offset: 0x4) Mode Register -------- */
#నిర్వచించు AT91C_TDES_CIPHER             ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )  /* (TDES) Processing Mode */
#నిర్వచించు AT91C_TDES_TDESMOD            ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )  /* (TDES) Single or Triple DES Mode */
#నిర్వచించు AT91C_TDES_KEYMOD             ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )  /* (TDES) Key Mode */
#నిర్వచించు AT91C_TDES_SMOD               ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 8 )  /* (TDES) Start Mode */
#నిర్వచించు     AT91C_TDES_SMOD_MANUAL    ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 8 )  /* (TDES) Manual Mode: The START bit in register TDES_CR must be set to begin encryption or decryption. */
#నిర్వచించు     AT91C_TDES_SMOD_AUTO      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )  /* (TDES) Auto Mode: no action in TDES_CR is necessary (cf datasheet). */
#నిర్వచించు     AT91C_TDES_SMOD_PDC       ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 8 )  /* (TDES) PDC Mode (cf datasheet). */
#నిర్వచించు AT91C_TDES_OPMOD              ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 12 ) /* (TDES) Operation Mode */
#నిర్వచించు     AT91C_TDES_OPMOD_ECB      ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 12 ) /* (TDES) ECB Electronic CodeBook mode. */
#నిర్వచించు     AT91C_TDES_OPMOD_CBC      ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 12 ) /* (TDES) CBC Cipher Block Chaining mode. */
#నిర్వచించు     AT91C_TDES_OPMOD_OFB      ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 12 ) /* (TDES) OFB Output Feedback mode. */
#నిర్వచించు     AT91C_TDES_OPMOD_CFB      ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 12 ) /* (TDES) CFB Cipher Feedback mode. */
#నిర్వచించు AT91C_TDES_LOD                ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 15 ) /* (TDES) Last Output Data Mode */
#నిర్వచించు AT91C_TDES_CFBS               ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 16 ) /* (TDES) Cipher Feedback Data Size */
#నిర్వచించు     AT91_C_TDES_CFBS_64_బిట్టు    ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 16 ) /* (TDES) 64-bit. */
#నిర్వచించు     AT91_C_TDES_CFBS_32_బిట్టు    ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 16 ) /* (TDES) 32-bit. */
#నిర్వచించు     AT91_C_TDES_CFBS_16_బిట్టు    ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 16 ) /* (TDES) 16-bit. */
#నిర్వచించు     AT91_C_TDES_CFBS_8_బిట్టు     ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 16 ) /* (TDES) 8-bit. */
/* -------- TDES_IER : (TDES Offset: 0x10) Interrupt Enable Register -------- */
#నిర్వచించు AT91C_TDES_DATRDY             ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 0 )  /* (TDES) DATRDY */
#నిర్వచించు AT91C_TDES_ENDRX              ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 1 )  /* (TDES) PDC Read Buffer End */
#నిర్వచించు AT91C_TDES_ENDTX              ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 2 )  /* (TDES) PDC Write Buffer End */
#నిర్వచించు AT91C_TDES_RXBUFF             ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 3 )  /* (TDES) PDC Read Buffer Full */
#నిర్వచించు AT91C_TDES_TXBUFE             ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 4 )  /* (TDES) PDC Write Buffer Empty */
#నిర్వచించు AT91C_TDES_URAD               ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 8 )  /* (TDES) Unspecified Register Access Detection */
/* -------- TDES_IDR : (TDES Offset: 0x14) Interrupt Disable Register -------- */
/* -------- TDES_IMR : (TDES Offset: 0x18) Interrupt Mask Register -------- */
/* -------- TDES_ISR : (TDES Offset: 0x1c) Interrupt Status Register -------- */
#నిర్వచించు AT91C_TDES_URAT                              ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 12 ) /* (TDES) Unspecified Register Access Type Status */
#నిర్వచించు     AT91_C_TDES_URAT_లోపల_DAT_WRITE_DATPROC     ( ( గుర్తులేని పూర్ణాంకం ) 0x0 << 12 ) /* (TDES) Input data register written during the data processing in PDC mode. */
#నిర్వచించు     AT91_C_TDES_URAT_బహిర్గతం_DAT_READ_DATPROC     ( ( గుర్తులేని పూర్ణాంకం ) 0x1 << 12 ) /* (TDES) Output data register read during the data processing. */
#నిర్వచించు     AT91C_TDES_URAT_MODEREG_WRITE_DATPROC    ( ( గుర్తులేని పూర్ణాంకం ) 0x2 << 12 ) /* (TDES) Mode register written during the data processing. */
#నిర్వచించు     AT91C_TDES_URAT_WO_REG_READ              ( ( గుర్తులేని పూర్ణాంకం ) 0x3 << 12 ) /* (TDES) Write-only register read access. */

/* ***************************************************************************** */
/*               REGISTER ADDRESS DEFINITION FOR AT91SAM7X256 */
/* ***************************************************************************** */
/* ========== Register definition for SYS peripheral ========== */
/* ========== Register definition for AIC peripheral ========== */
#నిర్వచించు AT91C_AIC_IVR              ( ( AT91_REG * ) 0xFFFFF100 ) /* (AIC) IRQ Vector Register */
#నిర్వచించు AT91C_AIC_SMR              ( ( AT91_REG * ) 0xFFFFF000 ) /* (AIC) Source Mode Register */
#నిర్వచించు AT91C_AIC_FVR              ( ( AT91_REG * ) 0xFFFFF104 ) /* (AIC) FIQ Vector Register */
#నిర్వచించు AT91C_AIC_DCR              ( ( AT91_REG * ) 0xFFFFF138 ) /* (AIC) Debug Control Register (Protect) */
#నిర్వచించు AT91C_AIC_EOICR            ( ( AT91_REG * ) 0xFFFFF130 ) /* (AIC) End of Interrupt Command Register */
#నిర్వచించు AT91C_AIC_SVR              ( ( AT91_REG * ) 0xFFFFF080 ) /* (AIC) Source Vector Register */
#నిర్వచించు AT91C_AIC_FFSR             ( ( AT91_REG * ) 0xFFFFF148 ) /* (AIC) Fast Forcing Status Register */
#నిర్వచించు AT91C_AIC_ICCR             ( ( AT91_REG * ) 0xFFFFF128 ) /* (AIC) Interrupt Clear Command Register */
#నిర్వచించు AT91C_AIC_ISR              ( ( AT91_REG * ) 0xFFFFF108 ) /* (AIC) Interrupt Status Register */
#నిర్వచించు AT91C_AIC_IMR              ( ( AT91_REG * ) 0xFFFFF110 ) /* (AIC) Interrupt Mask Register */
#నిర్వచించు AT91C_AIC_IPR              ( ( AT91_REG * ) 0xFFFFF10C ) /* (AIC) Interrupt Pending Register */
#నిర్వచించు AT91C_AIC_FFER             ( ( AT91_REG * ) 0xFFFFF140 ) /* (AIC) Fast Forcing Enable Register */
#నిర్వచించు AT91C_AIC_IECR             ( ( AT91_REG * ) 0xFFFFF120 ) /* (AIC) Interrupt Enable Command Register */
#నిర్వచించు AT91C_AIC_ISCR             ( ( AT91_REG * ) 0xFFFFF12C ) /* (AIC) Interrupt Set Command Register */
#నిర్వచించు AT91C_AIC_FFDR             ( ( AT91_REG * ) 0xFFFFF144 ) /* (AIC) Fast Forcing Disable Register */
#నిర్వచించు AT91C_AIC_CISR             ( ( AT91_REG * ) 0xFFFFF114 ) /* (AIC) Core Interrupt Status Register */
#నిర్వచించు AT91C_AIC_IDCR             ( ( AT91_REG * ) 0xFFFFF124 ) /* (AIC) Interrupt Disable Command Register */
#నిర్వచించు AT91C_AIC_SPU              ( ( AT91_REG * ) 0xFFFFF134 ) /* (AIC) Spurious Vector Register */
/* ========== Register definition for PDC_DBGU peripheral ========== */
#నిర్వచించు AT91C_DBGU_TCR             ( ( AT91_REG * ) 0xFFFFF30C ) /* (PDC_DBGU) Transmit Counter Register */
#నిర్వచించు AT91C_DBGU_RNPR            ( ( AT91_REG * ) 0xFFFFF310 ) /* (PDC_DBGU) Receive Next Pointer Register */
#నిర్వచించు AT91C_DBGU_TNPR            ( ( AT91_REG * ) 0xFFFFF318 ) /* (PDC_DBGU) Transmit Next Pointer Register */
#నిర్వచించు AT91C_DBGU_TPR             ( ( AT91_REG * ) 0xFFFFF308 ) /* (PDC_DBGU) Transmit Pointer Register */
#నిర్వచించు AT91C_DBGU_RPR             ( ( AT91_REG * ) 0xFFFFF300 ) /* (PDC_DBGU) Receive Pointer Register */
#నిర్వచించు AT91C_DBGU_RCR             ( ( AT91_REG * ) 0xFFFFF304 ) /* (PDC_DBGU) Receive Counter Register */
#నిర్వచించు AT91C_DBGU_RNCR            ( ( AT91_REG * ) 0xFFFFF314 ) /* (PDC_DBGU) Receive Next Counter Register */
#నిర్వచించు AT91C_DBGU_PTCR            ( ( AT91_REG * ) 0xFFFFF320 ) /* (PDC_DBGU) PDC Transfer Control Register */
#నిర్వచించు AT91C_DBGU_PTSR            ( ( AT91_REG * ) 0xFFFFF324 ) /* (PDC_DBGU) PDC Transfer Status Register */
#నిర్వచించు AT91C_DBGU_TNCR            ( ( AT91_REG * ) 0xFFFFF31C ) /* (PDC_DBGU) Transmit Next Counter Register */
/* ========== Register definition for DBGU peripheral ========== */
#నిర్వచించు AT91C_DBGU_EXID            ( ( AT91_REG * ) 0xFFFFF244 ) /* (DBGU) Chip ID Extension Register */
#నిర్వచించు AT91C_DBGU_BRGR            ( ( AT91_REG * ) 0xFFFFF220 ) /* (DBGU) Baud Rate Generator Register */
#నిర్వచించు AT91C_DBGU_IDR             ( ( AT91_REG * ) 0xFFFFF20C ) /* (DBGU) Interrupt Disable Register */
#నిర్వచించు AT91C_DBGU_CSR             ( ( AT91_REG * ) 0xFFFFF214 ) /* (DBGU) Channel Status Register */
#నిర్వచించు AT91C_DBGU_CIDR            ( ( AT91_REG * ) 0xFFFFF240 ) /* (DBGU) Chip ID Register */
#నిర్వచించు AT91C_DBGU_MR              ( ( AT91_REG * ) 0xFFFFF204 ) /* (DBGU) Mode Register */
#నిర్వచించు AT91C_DBGU_IMR             ( ( AT91_REG * ) 0xFFFFF210 ) /* (DBGU) Interrupt Mask Register */
#నిర్వచించు AT91C_DBGU_CR              ( ( AT91_REG * ) 0xFFFFF200 ) /* (DBGU) Control Register */
#నిర్వచించు AT91C_DBGU_FNTR            ( ( AT91_REG * ) 0xFFFFF248 ) /* (DBGU) Force NTRST Register */
#నిర్వచించు AT91C_DBGU_THR             ( ( AT91_REG * ) 0xFFFFF21C ) /* (DBGU) Transmitter Holding Register */
#నిర్వచించు AT91C_DBGU_RHR             ( ( AT91_REG * ) 0xFFFFF218 ) /* (DBGU) Receiver Holding Register */
#నిర్వచించు AT91C_DBGU_IER             ( ( AT91_REG * ) 0xFFFFF208 ) /* (DBGU) Interrupt Enable Register */
/* ========== Register definition for PIOA peripheral ========== */
#నిర్వచించు AT91C_PIOA_ODR             ( ( AT91_REG * ) 0xFFFFF414 ) /* (PIOA) Output Disable Registerr */
#నిర్వచించు AT91C_PIOA_SODR            ( ( AT91_REG * ) 0xFFFFF430 ) /* (PIOA) Set Output Data Register */
#నిర్వచించు AT91C_PIOA_ISR             ( ( AT91_REG * ) 0xFFFFF44C ) /* (PIOA) Interrupt Status Register */
#నిర్వచించు AT91C_PIOA_ABSR            ( ( AT91_REG * ) 0xFFFFF478 ) /* (PIOA) AB Select Status Register */
#నిర్వచించు AT91C_PIOA_IER             ( ( AT91_REG * ) 0xFFFFF440 ) /* (PIOA) Interrupt Enable Register */
#నిర్వచించు AT91C_PIOA_PPUDR           ( ( AT91_REG * ) 0xFFFFF460 ) /* (PIOA) Pull-up Disable Register */
#నిర్వచించు AT91C_PIOA_IMR             ( ( AT91_REG * ) 0xFFFFF448 ) /* (PIOA) Interrupt Mask Register */
#నిర్వచించు AT91_C_PIOA_చొప్పున             ( ( AT91_REG * ) 0xFFFFF400 ) /* (PIOA) PIO Enable Register */
#నిర్వచించు AT91C_PIOA_IFDR            ( ( AT91_REG * ) 0xFFFFF424 ) /* (PIOA) Input Filter Disable Register */
#నిర్వచించు AT91C_PIOA_OWDR            ( ( AT91_REG * ) 0xFFFFF4A4 ) /* (PIOA) Output Write Disable Register */
#నిర్వచించు AT91C_PIOA_MDSR            ( ( AT91_REG * ) 0xFFFFF458 ) /* (PIOA) Multi-driver Status Register */
#నిర్వచించు AT91C_PIOA_IDR             ( ( AT91_REG * ) 0xFFFFF444 ) /* (PIOA) Interrupt Disable Register */
#నిర్వచించు AT91C_PIOA_ODSR            ( ( AT91_REG * ) 0xFFFFF438 ) /* (PIOA) Output Data Status Register */
#నిర్వచించు AT91C_PIOA_PPUSR           ( ( AT91_REG * ) 0xFFFFF468 ) /* (PIOA) Pull-up Status Register */
#నిర్వచించు AT91C_PIOA_OWSR            ( ( AT91_REG * ) 0xFFFFF4A8 ) /* (PIOA) Output Write Status Register */
#నిర్వచించు AT91C_PIOA_BSR             ( ( AT91_REG * ) 0xFFFFF474 ) /* (PIOA) Select B Register */
#నిర్వచించు AT91C_PIOA_OWER            ( ( AT91_REG * ) 0xFFFFF4A0 ) /* (PIOA) Output Write Enable Register */
#నిర్వచించు AT91C_PIOA_IFER            ( ( AT91_REG * ) 0xFFFFF420 ) /* (PIOA) Input Filter Enable Register */
#నిర్వచించు AT91C_PIOA_PDSR            ( ( AT91_REG * ) 0xFFFFF43C ) /* (PIOA) Pin Data Status Register */
#నిర్వచించు AT91C_PIOA_PPUER           ( ( AT91_REG * ) 0xFFFFF464 ) /* (PIOA) Pull-up Enable Register */
#నిర్వచించు AT91C_PIOA_OSR             ( ( AT91_REG * ) 0xFFFFF418 ) /* (PIOA) Output Status Register */
#నిర్వచించు AT91C_PIOA_ASR             ( ( AT91_REG * ) 0xFFFFF470 ) /* (PIOA) Select A Register */
#నిర్వచించు AT91C_PIOA_MDDR            ( ( AT91_REG * ) 0xFFFFF454 ) /* (PIOA) Multi-driver Disable Register */
#నిర్వచించు AT91C_PIOA_CODR            ( ( AT91_REG * ) 0xFFFFF434 ) /* (PIOA) Clear Output Data Register */
#నిర్వచించు AT91C_PIOA_MDER            ( ( AT91_REG * ) 0xFFFFF450 ) /* (PIOA) Multi-driver Enable Register */
#నిర్వచించు AT91C_PIOA_PDR             ( ( AT91_REG * ) 0xFFFFF404 ) /* (PIOA) PIO Disable Register */
#నిర్వచించు AT91C_PIOA_IFSR            ( ( AT91_REG * ) 0xFFFFF428 ) /* (PIOA) Input Filter Status Register */
#నిర్వచించు AT91C_PIOA_OER             ( ( AT91_REG * ) 0xFFFFF410 ) /* (PIOA) Output Enable Register */
#నిర్వచించు AT91C_PIOA_PSR             ( ( AT91_REG * ) 0xFFFFF408 ) /* (PIOA) PIO Status Register */
/* ========== Register definition for PIOB peripheral ========== */
#నిర్వచించు AT91C_PIOB_OWDR            ( ( AT91_REG * ) 0xFFFFF6A4 ) /* (PIOB) Output Write Disable Register */
#నిర్వచించు AT91C_PIOB_MDER            ( ( AT91_REG * ) 0xFFFFF650 ) /* (PIOB) Multi-driver Enable Register */
#నిర్వచించు AT91C_PIOB_PPUSR           ( ( AT91_REG * ) 0xFFFFF668 ) /* (PIOB) Pull-up Status Register */
#నిర్వచించు AT91C_PIOB_IMR             ( ( AT91_REG * ) 0xFFFFF648 ) /* (PIOB) Interrupt Mask Register */
#నిర్వచించు AT91C_PIOB_ASR             ( ( AT91_REG * ) 0xFFFFF670 ) /* (PIOB) Select A Register */
#నిర్వచించు AT91C_PIOB_PPUDR           ( ( AT91_REG * ) 0xFFFFF660 ) /* (PIOB) Pull-up Disable Register */
#నిర్వచించు AT91C_PIOB_PSR             ( ( AT91_REG * ) 0xFFFFF608 ) /* (PIOB) PIO Status Register */
#నిర్వచించు AT91C_PIOB_IER             ( ( AT91_REG * ) 0xFFFFF640 ) /* (PIOB) Interrupt Enable Register */
#నిర్వచించు AT91C_PIOB_CODR            ( ( AT91_REG * ) 0xFFFFF634 ) /* (PIOB) Clear Output Data Register */
#నిర్వచించు AT91C_PIOB_OWER            ( ( AT91_REG * ) 0xFFFFF6A0 ) /* (PIOB) Output Write Enable Register */
#నిర్వచించు AT91C_PIOB_ABSR            ( ( AT91_REG * ) 0xFFFFF678 ) /* (PIOB) AB Select Status Register */
#నిర్వచించు AT91C_PIOB_IFDR            ( ( AT91_REG * ) 0xFFFFF624 ) /* (PIOB) Input Filter Disable Register */
#నిర్వచించు AT91C_PIOB_PDSR            ( ( AT91_REG * ) 0xFFFFF63C ) /* (PIOB) Pin Data Status Register */
#నిర్వచించు AT91C_PIOB_IDR             ( ( AT91_REG * ) 0xFFFFF644 ) /* (PIOB) Interrupt Disable Register */
#నిర్వచించు AT91C_PIOB_OWSR            ( ( AT91_REG * ) 0xFFFFF6A8 ) /* (PIOB) Output Write Status Register */
#నిర్వచించు AT91C_PIOB_PDR             ( ( AT91_REG * ) 0xFFFFF604 ) /* (PIOB) PIO Disable Register */
#నిర్వచించు AT91C_PIOB_ODR             ( ( AT91_REG * ) 0xFFFFF614 ) /* (PIOB) Output Disable Registerr */
#నిర్వచించు AT91C_PIOB_IFSR            ( ( AT91_REG * ) 0xFFFFF628 ) /* (PIOB) Input Filter Status Register */
#నిర్వచించు AT91C_PIOB_PPUER           ( ( AT91_REG * ) 0xFFFFF664 ) /* (PIOB) Pull-up Enable Register */
#నిర్వచించు AT91C_PIOB_SODR            ( ( AT91_REG * ) 0xFFFFF630 ) /* (PIOB) Set Output Data Register */
#నిర్వచించు AT91C_PIOB_ISR             ( ( AT91_REG * ) 0xFFFFF64C ) /* (PIOB) Interrupt Status Register */
#నిర్వచించు AT91C_PIOB_ODSR            ( ( AT91_REG * ) 0xFFFFF638 ) /* (PIOB) Output Data Status Register */
#నిర్వచించు AT91C_PIOB_OSR             ( ( AT91_REG * ) 0xFFFFF618 ) /* (PIOB) Output Status Register */
#నిర్వచించు AT91C_PIOB_MDSR            ( ( AT91_REG * ) 0xFFFFF658 ) /* (PIOB) Multi-driver Status Register */
#నిర్వచించు AT91C_PIOB_IFER            ( ( AT91_REG * ) 0xFFFFF620 ) /* (PIOB) Input Filter Enable Register */
#నిర్వచించు AT91C_PIOB_BSR             ( ( AT91_REG * ) 0xFFFFF674 ) /* (PIOB) Select B Register */
#నిర్వచించు AT91C_PIOB_MDDR            ( ( AT91_REG * ) 0xFFFFF654 ) /* (PIOB) Multi-driver Disable Register */
#నిర్వచించు AT91C_PIOB_OER             ( ( AT91_REG * ) 0xFFFFF610 ) /* (PIOB) Output Enable Register */
#నిర్వచించు AT91_C_PIOB_చొప్పున             ( ( AT91_REG * ) 0xFFFFF600 ) /* (PIOB) PIO Enable Register */
/* ========== Register definition for CKGR peripheral ========== */
#నిర్వచించు AT91C_CKGR_MOR             ( ( AT91_REG * ) 0xFFFFFC20 ) /* (CKGR) Main Oscillator Register */
#నిర్వచించు AT91C_CKGR_PLLR            ( ( AT91_REG * ) 0xFFFFFC2C ) /* (CKGR) PLL Register */
#నిర్వచించు AT91C_CKGR_MCFR            ( ( AT91_REG * ) 0xFFFFFC24 ) /* (CKGR) Main Clock  Frequency Register */
/* ========== Register definition for PMC peripheral ========== */
#నిర్వచించు AT91C_PMC_IDR              ( ( AT91_REG * ) 0xFFFFFC64 ) /* (PMC) Interrupt Disable Register */
#నిర్వచించు AT91C_PMC_MOR              ( ( AT91_REG * ) 0xFFFFFC20 ) /* (PMC) Main Oscillator Register */
#నిర్వచించు AT91C_PMC_PLLR             ( ( AT91_REG * ) 0xFFFFFC2C ) /* (PMC) PLL Register */
#నిర్వచించు AT91C_PMC_PCER             ( ( AT91_REG * ) 0xFFFFFC10 ) /* (PMC) Peripheral Clock Enable Register */
#నిర్వచించు AT91C_PMC_PCKR             ( ( AT91_REG * ) 0xFFFFFC40 ) /* (PMC) Programmable Clock Register */
#నిర్వచించు AT91C_PMC_MCKR             ( ( AT91_REG * ) 0xFFFFFC30 ) /* (PMC) Master Clock Register */
#నిర్వచించు AT91C_PMC_SCDR             ( ( AT91_REG * ) 0xFFFFFC04 ) /* (PMC) System Clock Disable Register */
#నిర్వచించు AT91C_PMC_PCDR             ( ( AT91_REG * ) 0xFFFFFC14 ) /* (PMC) Peripheral Clock Disable Register */
#నిర్వచించు AT91C_PMC_SCSR             ( ( AT91_REG * ) 0xFFFFFC08 ) /* (PMC) System Clock Status Register */
#నిర్వచించు AT91C_PMC_PCSR             ( ( AT91_REG * ) 0xFFFFFC18 ) /* (PMC) Peripheral Clock Status Register */
#నిర్వచించు AT91C_PMC_MCFR             ( ( AT91_REG * ) 0xFFFFFC24 ) /* (PMC) Main Clock  Frequency Register */
#నిర్వచించు AT91C_PMC_SCER             ( ( AT91_REG * ) 0xFFFFFC00 ) /* (PMC) System Clock Enable Register */
#నిర్వచించు AT91C_PMC_IMR              ( ( AT91_REG * ) 0xFFFFFC6C ) /* (PMC) Interrupt Mask Register */
#నిర్వచించు AT91C_PMC_IER              ( ( AT91_REG * ) 0xFFFFFC60 ) /* (PMC) Interrupt Enable Register */
#నిర్వచించు AT91C_PMC_SR               ( ( AT91_REG * ) 0xFFFFFC68 ) /* (PMC) Status Register */
/* ========== Register definition for RSTC peripheral ========== */
#నిర్వచించు AT91C_RSTC_RCR             ( ( AT91_REG * ) 0xFFFFFD00 ) /* (RSTC) Reset Control Register */
#నిర్వచించు AT91C_RSTC_RMR             ( ( AT91_REG * ) 0xFFFFFD08 ) /* (RSTC) Reset Mode Register */
#నిర్వచించు AT91C_RSTC_RSR             ( ( AT91_REG * ) 0xFFFFFD04 ) /* (RSTC) Reset Status Register */
/* ========== Register definition for RTTC peripheral ========== */
#నిర్వచించు AT91C_RTTC_RTSR            ( ( AT91_REG * ) 0xFFFFFD2C ) /* (RTTC) Real-time Status Register */
#నిర్వచించు AT91C_RTTC_RTMR            ( ( AT91_REG * ) 0xFFFFFD20 ) /* (RTTC) Real-time Mode Register */
#నిర్వచించు AT91C_RTTC_RTVR            ( ( AT91_REG * ) 0xFFFFFD28 ) /* (RTTC) Real-time Value Register */
#నిర్వచించు AT91C_RTTC_RTAR            ( ( AT91_REG * ) 0xFFFFFD24 ) /* (RTTC) Real-time Alarm Register */
/* ========== Register definition for PITC peripheral ========== */
#నిర్వచించు AT91C_PITC_PIVR            ( ( AT91_REG * ) 0xFFFFFD38 ) /* (PITC) Period Interval Value Register */
#నిర్వచించు AT91C_PITC_PISR            ( ( AT91_REG * ) 0xFFFFFD34 ) /* (PITC) Period Interval Status Register */
#నిర్వచించు AT91C_PITC_PIIR            ( ( AT91_REG * ) 0xFFFFFD3C ) /* (PITC) Period Interval Image Register */
#నిర్వచించు AT91C_PITC_PIMR            ( ( AT91_REG * ) 0xFFFFFD30 ) /* (PITC) Period Interval Mode Register */
/* ========== Register definition for WDTC peripheral ========== */
#నిర్వచించు AT91C_WDTC_WDCR            ( ( AT91_REG * ) 0xFFFFFD40 ) /* (WDTC) Watchdog Control Register */
#నిర్వచించు AT91C_WDTC_WDSR            ( ( AT91_REG * ) 0xFFFFFD48 ) /* (WDTC) Watchdog Status Register */
#నిర్వచించు AT91C_WDTC_WDMR            ( ( AT91_REG * ) 0xFFFFFD44 ) /* (WDTC) Watchdog Mode Register */
/* ========== Register definition for VREG peripheral ========== */
#నిర్వచించు AT91C_VREG_MR              ( ( AT91_REG * ) 0xFFFFFD60 ) /* (VREG) Voltage Regulator Mode Register */
/* ========== Register definition for MC peripheral ========== */
#నిర్వచించు AT91C_MC_ASR               ( ( AT91_REG * ) 0xFFFFFF04 ) /* (MC) MC Abort Status Register */
#నిర్వచించు AT91C_MC_RCR               ( ( AT91_REG * ) 0xFFFFFF00 ) /* (MC) MC Remap Control Register */
#నిర్వచించు AT91C_MC_FCR               ( ( AT91_REG * ) 0xFFFFFF64 ) /* (MC) MC Flash Command Register */
#నిర్వచించు AT91C_MC_AASR              ( ( AT91_REG * ) 0xFFFFFF08 ) /* (MC) MC Abort Address Status Register */
#నిర్వచించు AT91C_MC_FSR               ( ( AT91_REG * ) 0xFFFFFF68 ) /* (MC) MC Flash Status Register */
#నిర్వచించు AT91C_MC_FMR               ( ( AT91_REG * ) 0xFFFFFF60 ) /* (MC) MC Flash Mode Register */
/* ========== Register definition for PDC_SPI1 peripheral ========== */
#నిర్వచించు AT91C_SPI1_PTCR            ( ( AT91_REG * ) 0xFFFE4120 ) /* (PDC_SPI1) PDC Transfer Control Register */
#నిర్వచించు AT91C_SPI1_RPR             ( ( AT91_REG * ) 0xFFFE4100 ) /* (PDC_SPI1) Receive Pointer Register */
#నిర్వచించు AT91C_SPI1_TNCR            ( ( AT91_REG * ) 0xFFFE411C ) /* (PDC_SPI1) Transmit Next Counter Register */
#నిర్వచించు AT91C_SPI1_TPR             ( ( AT91_REG * ) 0xFFFE4108 ) /* (PDC_SPI1) Transmit Pointer Register */
#నిర్వచించు AT91C_SPI1_TNPR            ( ( AT91_REG * ) 0xFFFE4118 ) /* (PDC_SPI1) Transmit Next Pointer Register */
#నిర్వచించు AT91C_SPI1_TCR             ( ( AT91_REG * ) 0xFFFE410C ) /* (PDC_SPI1) Transmit Counter Register */
#నిర్వచించు AT91C_SPI1_RCR             ( ( AT91_REG * ) 0xFFFE4104 ) /* (PDC_SPI1) Receive Counter Register */
#నిర్వచించు AT91C_SPI1_RNPR            ( ( AT91_REG * ) 0xFFFE4110 ) /* (PDC_SPI1) Receive Next Pointer Register */
#నిర్వచించు AT91C_SPI1_RNCR            ( ( AT91_REG * ) 0xFFFE4114 ) /* (PDC_SPI1) Receive Next Counter Register */
#నిర్వచించు AT91C_SPI1_PTSR            ( ( AT91_REG * ) 0xFFFE4124 ) /* (PDC_SPI1) PDC Transfer Status Register */
/* ========== Register definition for SPI1 peripheral ========== */
#నిర్వచించు AT91C_SPI1_IMR             ( ( AT91_REG * ) 0xFFFE401C ) /* (SPI1) Interrupt Mask Register */
#నిర్వచించు AT91C_SPI1_IER             ( ( AT91_REG * ) 0xFFFE4014 ) /* (SPI1) Interrupt Enable Register */
#నిర్వచించు AT91C_SPI1_MR              ( ( AT91_REG * ) 0xFFFE4004 ) /* (SPI1) Mode Register */
#నిర్వచించు AT91C_SPI1_RDR             ( ( AT91_REG * ) 0xFFFE4008 ) /* (SPI1) Receive Data Register */
#నిర్వచించు AT91C_SPI1_IDR             ( ( AT91_REG * ) 0xFFFE4018 ) /* (SPI1) Interrupt Disable Register */
#నిర్వచించు AT91C_SPI1_SR              ( ( AT91_REG * ) 0xFFFE4010 ) /* (SPI1) Status Register */
#నిర్వచించు AT91C_SPI1_TDR             ( ( AT91_REG * ) 0xFFFE400C ) /* (SPI1) Transmit Data Register */
#నిర్వచించు AT91C_SPI1_CR              ( ( AT91_REG * ) 0xFFFE4000 ) /* (SPI1) Control Register */
#నిర్వచించు AT91C_SPI1_CSR             ( ( AT91_REG * ) 0xFFFE4030 ) /* (SPI1) Chip Select Register */
/* ========== Register definition for PDC_SPI0 peripheral ========== */
#నిర్వచించు AT91C_SPI0_PTCR            ( ( AT91_REG * ) 0xFFFE0120 ) /* (PDC_SPI0) PDC Transfer Control Register */
#నిర్వచించు AT91C_SPI0_TPR             ( ( AT91_REG * ) 0xFFFE0108 ) /* (PDC_SPI0) Transmit Pointer Register */
#నిర్వచించు AT91C_SPI0_TCR             ( ( AT91_REG * ) 0xFFFE010C ) /* (PDC_SPI0) Transmit Counter Register */
#నిర్వచించు AT91C_SPI0_RCR             ( ( AT91_REG * ) 0xFFFE0104 ) /* (PDC_SPI0) Receive Counter Register */
#నిర్వచించు AT91C_SPI0_PTSR            ( ( AT91_REG * ) 0xFFFE0124 ) /* (PDC_SPI0) PDC Transfer Status Register */
#నిర్వచించు AT91C_SPI0_RNPR            ( ( AT91_REG * ) 0xFFFE0110 ) /* (PDC_SPI0) Receive Next Pointer Register */
#నిర్వచించు AT91C_SPI0_RPR             ( ( AT91_REG * ) 0xFFFE0100 ) /* (PDC_SPI0) Receive Pointer Register */
#నిర్వచించు AT91C_SPI0_TNCR            ( ( AT91_REG * ) 0xFFFE011C ) /* (PDC_SPI0) Transmit Next Counter Register */
#నిర్వచించు AT91C_SPI0_RNCR            ( ( AT91_REG * ) 0xFFFE0114 ) /* (PDC_SPI0) Receive Next Counter Register */
#నిర్వచించు AT91C_SPI0_TNPR            ( ( AT91_REG * ) 0xFFFE0118 ) /* (PDC_SPI0) Transmit Next Pointer Register */
/* ========== Register definition for SPI0 peripheral ========== */
#నిర్వచించు AT91C_SPI0_IER             ( ( AT91_REG * ) 0xFFFE0014 ) /* (SPI0) Interrupt Enable Register */
#నిర్వచించు AT91C_SPI0_SR              ( ( AT91_REG * ) 0xFFFE0010 ) /* (SPI0) Status Register */
#నిర్వచించు AT91C_SPI0_IDR             ( ( AT91_REG * ) 0xFFFE0018 ) /* (SPI0) Interrupt Disable Register */
#నిర్వచించు AT91C_SPI0_CR              ( ( AT91_REG * ) 0xFFFE0000 ) /* (SPI0) Control Register */
#నిర్వచించు AT91C_SPI0_MR              ( ( AT91_REG * ) 0xFFFE0004 ) /* (SPI0) Mode Register */
#నిర్వచించు AT91C_SPI0_IMR             ( ( AT91_REG * ) 0xFFFE001C ) /* (SPI0) Interrupt Mask Register */
#నిర్వచించు AT91C_SPI0_TDR             ( ( AT91_REG * ) 0xFFFE000C ) /* (SPI0) Transmit Data Register */
#నిర్వచించు AT91C_SPI0_RDR             ( ( AT91_REG * ) 0xFFFE0008 ) /* (SPI0) Receive Data Register */
#నిర్వచించు AT91C_SPI0_CSR             ( ( AT91_REG * ) 0xFFFE0030 ) /* (SPI0) Chip Select Register */
/* ========== Register definition for PDC_US1 peripheral ========== */
#నిర్వచించు AT91C_US1_RNCR             ( ( AT91_REG * ) 0xFFFC4114 ) /* (PDC_US1) Receive Next Counter Register */
#నిర్వచించు AT91C_US1_PTCR             ( ( AT91_REG * ) 0xFFFC4120 ) /* (PDC_US1) PDC Transfer Control Register */
#నిర్వచించు AT91C_US1_TCR              ( ( AT91_REG * ) 0xFFFC410C ) /* (PDC_US1) Transmit Counter Register */
#నిర్వచించు AT91C_US1_PTSR             ( ( AT91_REG * ) 0xFFFC4124 ) /* (PDC_US1) PDC Transfer Status Register */
#నిర్వచించు AT91C_US1_TNPR             ( ( AT91_REG * ) 0xFFFC4118 ) /* (PDC_US1) Transmit Next Pointer Register */
#నిర్వచించు AT91C_US1_RCR              ( ( AT91_REG * ) 0xFFFC4104 ) /* (PDC_US1) Receive Counter Register */
#నిర్వచించు AT91C_US1_RNPR             ( ( AT91_REG * ) 0xFFFC4110 ) /* (PDC_US1) Receive Next Pointer Register */
#నిర్వచించు AT91C_US1_RPR              ( ( AT91_REG * ) 0xFFFC4100 ) /* (PDC_US1) Receive Pointer Register */
#నిర్వచించు AT91C_US1_TNCR             ( ( AT91_REG * ) 0xFFFC411C ) /* (PDC_US1) Transmit Next Counter Register */
#నిర్వచించు AT91C_US1_TPR              ( ( AT91_REG * ) 0xFFFC4108 ) /* (PDC_US1) Transmit Pointer Register */
/* ========== Register definition for US1 peripheral ========== */
#నిర్వచించు AT91C_US1_IF               ( ( AT91_REG * ) 0xFFFC404C ) /* (US1) IRDA_FILTER Register */
#నిర్వచించు AT91C_US1_NER              ( ( AT91_REG * ) 0xFFFC4044 ) /* (US1) Nb Errors Register */
#నిర్వచించు AT91C_US1_RTOR             ( ( AT91_REG * ) 0xFFFC4024 ) /* (US1) Receiver Time-out Register */
#నిర్వచించు AT91C_US1_CSR              ( ( AT91_REG * ) 0xFFFC4014 ) /* (US1) Channel Status Register */
#నిర్వచించు AT91C_US1_IDR              ( ( AT91_REG * ) 0xFFFC400C ) /* (US1) Interrupt Disable Register */
#నిర్వచించు AT91C_US1_IER              ( ( AT91_REG * ) 0xFFFC4008 ) /* (US1) Interrupt Enable Register */
#నిర్వచించు AT91C_US1_THR              ( ( AT91_REG * ) 0xFFFC401C ) /* (US1) Transmitter Holding Register */
#నిర్వచించు AT91C_US1_TTGR             ( ( AT91_REG * ) 0xFFFC4028 ) /* (US1) Transmitter Time-guard Register */
#నిర్వచించు AT91C_US1_RHR              ( ( AT91_REG * ) 0xFFFC4018 ) /* (US1) Receiver Holding Register */
#నిర్వచించు AT91C_US1_BRGR             ( ( AT91_REG * ) 0xFFFC4020 ) /* (US1) Baud Rate Generator Register */
#నిర్వచించు AT91C_US1_IMR              ( ( AT91_REG * ) 0xFFFC4010 ) /* (US1) Interrupt Mask Register */
#నిర్వచించు AT91C_US1_FIDI             ( ( AT91_REG * ) 0xFFFC4040 ) /* (US1) FI_DI_Ratio Register */
#నిర్వచించు AT91C_US1_CR               ( ( AT91_REG * ) 0xFFFC4000 ) /* (US1) Control Register */
#నిర్వచించు AT91C_US1_MR               ( ( AT91_REG * ) 0xFFFC4004 ) /* (US1) Mode Register */
/* ========== Register definition for PDC_US0 peripheral ========== */
#నిర్వచించు AT91C_US0_TNPR             ( ( AT91_REG * ) 0xFFFC0118 ) /* (PDC_US0) Transmit Next Pointer Register */
#నిర్వచించు AT91C_US0_RNPR             ( ( AT91_REG * ) 0xFFFC0110 ) /* (PDC_US0) Receive Next Pointer Register */
#నిర్వచించు AT91C_US0_TCR              ( ( AT91_REG * ) 0xFFFC010C ) /* (PDC_US0) Transmit Counter Register */
#నిర్వచించు AT91C_US0_PTCR             ( ( AT91_REG * ) 0xFFFC0120 ) /* (PDC_US0) PDC Transfer Control Register */
#నిర్వచించు AT91C_US0_PTSR             ( ( AT91_REG * ) 0xFFFC0124 ) /* (PDC_US0) PDC Transfer Status Register */
#నిర్వచించు AT91C_US0_TNCR             ( ( AT91_REG * ) 0xFFFC011C ) /* (PDC_US0) Transmit Next Counter Register */
#నిర్వచించు AT91C_US0_TPR              ( ( AT91_REG * ) 0xFFFC0108 ) /* (PDC_US0) Transmit Pointer Register */
#నిర్వచించు AT91C_US0_RCR              ( ( AT91_REG * ) 0xFFFC0104 ) /* (PDC_US0) Receive Counter Register */
#నిర్వచించు AT91C_US0_RPR              ( ( AT91_REG * ) 0xFFFC0100 ) /* (PDC_US0) Receive Pointer Register */
#నిర్వచించు AT91C_US0_RNCR             ( ( AT91_REG * ) 0xFFFC0114 ) /* (PDC_US0) Receive Next Counter Register */
/* ========== Register definition for US0 peripheral ========== */
#నిర్వచించు AT91C_US0_BRGR             ( ( AT91_REG * ) 0xFFFC0020 ) /* (US0) Baud Rate Generator Register */
#నిర్వచించు AT91C_US0_NER              ( ( AT91_REG * ) 0xFFFC0044 ) /* (US0) Nb Errors Register */
#నిర్వచించు AT91C_US0_CR               ( ( AT91_REG * ) 0xFFFC0000 ) /* (US0) Control Register */
#నిర్వచించు AT91C_US0_IMR              ( ( AT91_REG * ) 0xFFFC0010 ) /* (US0) Interrupt Mask Register */
#నిర్వచించు AT91C_US0_FIDI             ( ( AT91_REG * ) 0xFFFC0040 ) /* (US0) FI_DI_Ratio Register */
#నిర్వచించు AT91C_US0_TTGR             ( ( AT91_REG * ) 0xFFFC0028 ) /* (US0) Transmitter Time-guard Register */
#నిర్వచించు AT91C_US0_MR               ( ( AT91_REG * ) 0xFFFC0004 ) /* (US0) Mode Register */
#నిర్వచించు AT91C_US0_RTOR             ( ( AT91_REG * ) 0xFFFC0024 ) /* (US0) Receiver Time-out Register */
#నిర్వచించు AT91C_US0_CSR              ( ( AT91_REG * ) 0xFFFC0014 ) /* (US0) Channel Status Register */
#నిర్వచించు AT91C_US0_RHR              ( ( AT91_REG * ) 0xFFFC0018 ) /* (US0) Receiver Holding Register */
#నిర్వచించు AT91C_US0_IDR              ( ( AT91_REG * ) 0xFFFC000C ) /* (US0) Interrupt Disable Register */
#నిర్వచించు AT91C_US0_THR              ( ( AT91_REG * ) 0xFFFC001C ) /* (US0) Transmitter Holding Register */
#నిర్వచించు AT91C_US0_IF               ( ( AT91_REG * ) 0xFFFC004C ) /* (US0) IRDA_FILTER Register */
#నిర్వచించు AT91C_US0_IER              ( ( AT91_REG * ) 0xFFFC0008 ) /* (US0) Interrupt Enable Register */
/* ========== Register definition for PDC_SSC peripheral ========== */
#నిర్వచించు AT91C_SSC_TNCR             ( ( AT91_REG * ) 0xFFFD411C ) /* (PDC_SSC) Transmit Next Counter Register */
#నిర్వచించు AT91C_SSC_RPR              ( ( AT91_REG * ) 0xFFFD4100 ) /* (PDC_SSC) Receive Pointer Register */
#నిర్వచించు AT91C_SSC_RNCR             ( ( AT91_REG * ) 0xFFFD4114 ) /* (PDC_SSC) Receive Next Counter Register */
#నిర్వచించు AT91C_SSC_TPR              ( ( AT91_REG * ) 0xFFFD4108 ) /* (PDC_SSC) Transmit Pointer Register */
#నిర్వచించు AT91C_SSC_PTCR             ( ( AT91_REG * ) 0xFFFD4120 ) /* (PDC_SSC) PDC Transfer Control Register */
#నిర్వచించు AT91C_SSC_TCR              ( ( AT91_REG * ) 0xFFFD410C ) /* (PDC_SSC) Transmit Counter Register */
#నిర్వచించు AT91C_SSC_RCR              ( ( AT91_REG * ) 0xFFFD4104 ) /* (PDC_SSC) Receive Counter Register */
#నిర్వచించు AT91C_SSC_RNPR             ( ( AT91_REG * ) 0xFFFD4110 ) /* (PDC_SSC) Receive Next Pointer Register */
#నిర్వచించు AT91C_SSC_TNPR             ( ( AT91_REG * ) 0xFFFD4118 ) /* (PDC_SSC) Transmit Next Pointer Register */
#నిర్వచించు AT91C_SSC_PTSR             ( ( AT91_REG * ) 0xFFFD4124 ) /* (PDC_SSC) PDC Transfer Status Register */
/* ========== Register definition for SSC peripheral ========== */
#నిర్వచించు AT91C_SSC_RHR              ( ( AT91_REG * ) 0xFFFD4020 ) /* (SSC) Receive Holding Register */
#నిర్వచించు AT91C_SSC_RSHR             ( ( AT91_REG * ) 0xFFFD4030 ) /* (SSC) Receive Sync Holding Register */
#నిర్వచించు AT91C_SSC_TFMR             ( ( AT91_REG * ) 0xFFFD401C ) /* (SSC) Transmit Frame Mode Register */
#నిర్వచించు AT91C_SSC_IDR              ( ( AT91_REG * ) 0xFFFD4048 ) /* (SSC) Interrupt Disable Register */
#నిర్వచించు AT91C_SSC_THR              ( ( AT91_REG * ) 0xFFFD4024 ) /* (SSC) Transmit Holding Register */
#నిర్వచించు AT91C_SSC_RCMR             ( ( AT91_REG * ) 0xFFFD4010 ) /* (SSC) Receive Clock ModeRegister */
#నిర్వచించు AT91C_SSC_IER              ( ( AT91_REG * ) 0xFFFD4044 ) /* (SSC) Interrupt Enable Register */
#నిర్వచించు AT91C_SSC_TSHR             ( ( AT91_REG * ) 0xFFFD4034 ) /* (SSC) Transmit Sync Holding Register */
#నిర్వచించు AT91C_SSC_SR               ( ( AT91_REG * ) 0xFFFD4040 ) /* (SSC) Status Register */
#నిర్వచించు AT91C_SSC_CMR              ( ( AT91_REG * ) 0xFFFD4004 ) /* (SSC) Clock Mode Register */
#నిర్వచించు AT91C_SSC_TCMR             ( ( AT91_REG * ) 0xFFFD4018 ) /* (SSC) Transmit Clock Mode Register */
#నిర్వచించు AT91C_SSC_CR               ( ( AT91_REG * ) 0xFFFD4000 ) /* (SSC) Control Register */
#నిర్వచించు AT91C_SSC_IMR              ( ( AT91_REG * ) 0xFFFD404C ) /* (SSC) Interrupt Mask Register */
#నిర్వచించు AT91C_SSC_RFMR             ( ( AT91_REG * ) 0xFFFD4014 ) /* (SSC) Receive Frame Mode Register */
/* ========== Register definition for TWI peripheral ========== */
#నిర్వచించు AT91C_TWI_IER              ( ( AT91_REG * ) 0xFFFB8024 ) /* (TWI) Interrupt Enable Register */
#నిర్వచించు AT91C_TWI_CR               ( ( AT91_REG * ) 0xFFFB8000 ) /* (TWI) Control Register */
#నిర్వచించు AT91C_TWI_SR               ( ( AT91_REG * ) 0xFFFB8020 ) /* (TWI) Status Register */
#నిర్వచించు AT91C_TWI_IMR              ( ( AT91_REG * ) 0xFFFB802C ) /* (TWI) Interrupt Mask Register */
#నిర్వచించు AT91C_TWI_THR              ( ( AT91_REG * ) 0xFFFB8034 ) /* (TWI) Transmit Holding Register */
#నిర్వచించు AT91C_TWI_IDR              ( ( AT91_REG * ) 0xFFFB8028 ) /* (TWI) Interrupt Disable Register */
#నిర్వచించు AT91C_TWI_IADR             ( ( AT91_REG * ) 0xFFFB800C ) /* (TWI) Internal Address Register */
#నిర్వచించు AT91C_TWI_MMR              ( ( AT91_REG * ) 0xFFFB8004 ) /* (TWI) Master Mode Register */
#నిర్వచించు AT91C_TWI_CWGR             ( ( AT91_REG * ) 0xFFFB8010 ) /* (TWI) Clock Waveform Generator Register */
#నిర్వచించు AT91C_TWI_RHR              ( ( AT91_REG * ) 0xFFFB8030 ) /* (TWI) Receive Holding Register */
/* ========== Register definition for PWMC_CH3 peripheral ========== */
#నిర్వచించు AT91C_PWMC_CH3_CUPDR       ( ( AT91_REG * ) 0xFFFCC270 ) /* (PWMC_CH3) Channel Update Register */
#నిర్వచించు AT91C_PWMC_CH3_Reserved    ( ( AT91_REG * ) 0xFFFCC274 ) /* (PWMC_CH3) Reserved */
#నిర్వచించు AT91C_PWMC_CH3_CPRDR       ( ( AT91_REG * ) 0xFFFCC268 ) /* (PWMC_CH3) Channel Period Register */
#నిర్వచించు AT91C_PWMC_CH3_CDTYR       ( ( AT91_REG * ) 0xFFFCC264 ) /* (PWMC_CH3) Channel Duty Cycle Register */
#నిర్వచించు AT91C_PWMC_CH3_CCNTR       ( ( AT91_REG * ) 0xFFFCC26C ) /* (PWMC_CH3) Channel Counter Register */
#నిర్వచించు AT91C_PWMC_CH3_CMR         ( ( AT91_REG * ) 0xFFFCC260 ) /* (PWMC_CH3) Channel Mode Register */
/* ========== Register definition for PWMC_CH2 peripheral ========== */
#నిర్వచించు AT91C_PWMC_CH2_Reserved    ( ( AT91_REG * ) 0xFFFCC254 ) /* (PWMC_CH2) Reserved */
#నిర్వచించు AT91C_PWMC_CH2_CMR         ( ( AT91_REG * ) 0xFFFCC240 ) /* (PWMC_CH2) Channel Mode Register */
#నిర్వచించు AT91C_PWMC_CH2_CCNTR       ( ( AT91_REG * ) 0xFFFCC24C ) /* (PWMC_CH2) Channel Counter Register */
#నిర్వచించు AT91C_PWMC_CH2_CPRDR       ( ( AT91_REG * ) 0xFFFCC248 ) /* (PWMC_CH2) Channel Period Register */
#నిర్వచించు AT91C_PWMC_CH2_CUPDR       ( ( AT91_REG * ) 0xFFFCC250 ) /* (PWMC_CH2) Channel Update Register */
#నిర్వచించు AT91C_PWMC_CH2_CDTYR       ( ( AT91_REG * ) 0xFFFCC244 ) /* (PWMC_CH2) Channel Duty Cycle Register */
/* ========== Register definition for PWMC_CH1 peripheral ========== */
#నిర్వచించు AT91C_PWMC_CH1_Reserved    ( ( AT91_REG * ) 0xFFFCC234 ) /* (PWMC_CH1) Reserved */
#నిర్వచించు AT91C_PWMC_CH1_CUPDR       ( ( AT91_REG * ) 0xFFFCC230 ) /* (PWMC_CH1) Channel Update Register */
#నిర్వచించు AT91C_PWMC_CH1_CPRDR       ( ( AT91_REG * ) 0xFFFCC228 ) /* (PWMC_CH1) Channel Period Register */
#నిర్వచించు AT91C_PWMC_CH1_CCNTR       ( ( AT91_REG * ) 0xFFFCC22C ) /* (PWMC_CH1) Channel Counter Register */
#నిర్వచించు AT91C_PWMC_CH1_CDTYR       ( ( AT91_REG * ) 0xFFFCC224 ) /* (PWMC_CH1) Channel Duty Cycle Register */
#నిర్వచించు AT91C_PWMC_CH1_CMR         ( ( AT91_REG * ) 0xFFFCC220 ) /* (PWMC_CH1) Channel Mode Register */
/* ========== Register definition for PWMC_CH0 peripheral ========== */
#నిర్వచించు AT91C_PWMC_CH0_Reserved    ( ( AT91_REG * ) 0xFFFCC214 ) /* (PWMC_CH0) Reserved */
#నిర్వచించు AT91C_PWMC_CH0_CPRDR       ( ( AT91_REG * ) 0xFFFCC208 ) /* (PWMC_CH0) Channel Period Register */
#నిర్వచించు AT91C_PWMC_CH0_CDTYR       ( ( AT91_REG * ) 0xFFFCC204 ) /* (PWMC_CH0) Channel Duty Cycle Register */
#నిర్వచించు AT91C_PWMC_CH0_CMR         ( ( AT91_REG * ) 0xFFFCC200 ) /* (PWMC_CH0) Channel Mode Register */
#నిర్వచించు AT91C_PWMC_CH0_CUPDR       ( ( AT91_REG * ) 0xFFFCC210 ) /* (PWMC_CH0) Channel Update Register */
#నిర్వచించు AT91C_PWMC_CH0_CCNTR       ( ( AT91_REG * ) 0xFFFCC20C ) /* (PWMC_CH0) Channel Counter Register */
/* ========== Register definition for PWMC peripheral ========== */
#నిర్వచించు AT91C_PWMC_IDR             ( ( AT91_REG * ) 0xFFFCC014 ) /* (PWMC) PWMC Interrupt Disable Register */
#నిర్వచించు AT91C_PWMC_DIS             ( ( AT91_REG * ) 0xFFFCC008 ) /* (PWMC) PWMC Disable Register */
#నిర్వచించు AT91C_PWMC_IER             ( ( AT91_REG * ) 0xFFFCC010 ) /* (PWMC) PWMC Interrupt Enable Register */
#నిర్వచించు AT91C_PWMC_VR              ( ( AT91_REG * ) 0xFFFCC0FC ) /* (PWMC) PWMC Version Register */
#నిర్వచించు AT91C_PWMC_ISR             ( ( AT91_REG * ) 0xFFFCC01C ) /* (PWMC) PWMC Interrupt Status Register */
#నిర్వచించు AT91C_PWMC_SR              ( ( AT91_REG * ) 0xFFFCC00C ) /* (PWMC) PWMC Status Register */
#నిర్వచించు AT91C_PWMC_IMR             ( ( AT91_REG * ) 0xFFFCC018 ) /* (PWMC) PWMC Interrupt Mask Register */
#నిర్వచించు AT91C_PWMC_MR              ( ( AT91_REG * ) 0xFFFCC000 ) /* (PWMC) PWMC Mode Register */
#నిర్వచించు AT91C_PWMC_ENA             ( ( AT91_REG * ) 0xFFFCC004 ) /* (PWMC) PWMC Enable Register */
/* ========== Register definition for UDP peripheral ========== */
#నిర్వచించు AT91C_UDP_IMR              ( ( AT91_REG * ) 0xFFFB0018 ) /* (UDP) Interrupt Mask Register */
#నిర్వచించు AT91C_UDP_FADDR            ( ( AT91_REG * ) 0xFFFB0008 ) /* (UDP) Function Address Register */
#నిర్వచించు AT91_C_UDP_అంకె              ( ( AT91_REG * ) 0xFFFB0000 ) /* (UDP) Frame Number Register */
#నిర్వచించు AT91C_UDP_FDR              ( ( AT91_REG * ) 0xFFFB0050 ) /* (UDP) Endpoint FIFO Data Register */
#నిర్వచించు AT91C_UDP_ISR              ( ( AT91_REG * ) 0xFFFB001C ) /* (UDP) Interrupt Status Register */
#నిర్వచించు AT91C_UDP_CSR              ( ( AT91_REG * ) 0xFFFB0030 ) /* (UDP) Endpoint Control and Status Register */
#నిర్వచించు AT91C_UDP_IDR              ( ( AT91_REG * ) 0xFFFB0014 ) /* (UDP) Interrupt Disable Register */
#నిర్వచించు AT91C_UDP_ICR              ( ( AT91_REG * ) 0xFFFB0020 ) /* (UDP) Interrupt Clear Register */
#నిర్వచించు AT91C_UDP_RSTEP            ( ( AT91_REG * ) 0xFFFB0028 ) /* (UDP) Reset Endpoint Register */
#నిర్వచించు AT91C_UDP_TXVC             ( ( AT91_REG * ) 0xFFFB0074 ) /* (UDP) Transceiver Control Register */
#నిర్వచించు AT91C_UDP_GLBSTATE         ( ( AT91_REG * ) 0xFFFB0004 ) /* (UDP) Global State Register */
#నిర్వచించు AT91C_UDP_IER              ( ( AT91_REG * ) 0xFFFB0010 ) /* (UDP) Interrupt Enable Register */
/* ========== Register definition for TC0 peripheral ========== */
#నిర్వచించు AT91C_TC0_SR               ( ( AT91_REG * ) 0xFFFA0020 ) /* (TC0) Status Register */
#నిర్వచించు AT91C_TC0_RC               ( ( AT91_REG * ) 0xFFFA001C ) /* (TC0) Register C */
#నిర్వచించు AT91C_TC0_RB               ( ( AT91_REG * ) 0xFFFA0018 ) /* (TC0) Register B */
#నిర్వచించు AT91C_TC0_CCR              ( ( AT91_REG * ) 0xFFFA0000 ) /* (TC0) Channel Control Register */
#నిర్వచించు AT91C_TC0_CMR              ( ( AT91_REG * ) 0xFFFA0004 ) /* (TC0) Channel Mode Register (Capture Mode / Waveform Mode) */
#నిర్వచించు AT91C_TC0_IER              ( ( AT91_REG * ) 0xFFFA0024 ) /* (TC0) Interrupt Enable Register */
#నిర్వచించు AT91C_TC0_RA               ( ( AT91_REG * ) 0xFFFA0014 ) /* (TC0) Register A */
#నిర్వచించు AT91C_TC0_IDR              ( ( AT91_REG * ) 0xFFFA0028 ) /* (TC0) Interrupt Disable Register */
#నిర్వచించు AT91C_TC0_CV               ( ( AT91_REG * ) 0xFFFA0010 ) /* (TC0) Counter Value */
#నిర్వచించు AT91C_TC0_IMR              ( ( AT91_REG * ) 0xFFFA002C ) /* (TC0) Interrupt Mask Register */
/* ========== Register definition for TC1 peripheral ========== */
#నిర్వచించు AT91C_TC1_RB               ( ( AT91_REG * ) 0xFFFA0058 ) /* (TC1) Register B */
#నిర్వచించు AT91C_TC1_CCR              ( ( AT91_REG * ) 0xFFFA0040 ) /* (TC1) Channel Control Register */
#నిర్వచించు AT91C_TC1_IER              ( ( AT91_REG * ) 0xFFFA0064 ) /* (TC1) Interrupt Enable Register */
#నిర్వచించు AT91C_TC1_IDR              ( ( AT91_REG * ) 0xFFFA0068 ) /* (TC1) Interrupt Disable Register */
#నిర్వచించు AT91C_TC1_SR               ( ( AT91_REG * ) 0xFFFA0060 ) /* (TC1) Status Register */
#నిర్వచించు AT91C_TC1_CMR              ( ( AT91_REG * ) 0xFFFA0044 ) /* (TC1) Channel Mode Register (Capture Mode / Waveform Mode) */
#నిర్వచించు AT91C_TC1_RA               ( ( AT91_REG * ) 0xFFFA0054 ) /* (TC1) Register A */
#నిర్వచించు AT91C_TC1_RC               ( ( AT91_REG * ) 0xFFFA005C ) /* (TC1) Register C */
#నిర్వచించు AT91C_TC1_IMR              ( ( AT91_REG * ) 0xFFFA006C ) /* (TC1) Interrupt Mask Register */
#నిర్వచించు AT91C_TC1_CV               ( ( AT91_REG * ) 0xFFFA0050 ) /* (TC1) Counter Value */
/* ========== Register definition for TC2 peripheral ========== */
#నిర్వచించు AT91C_TC2_CMR              ( ( AT91_REG * ) 0xFFFA0084 ) /* (TC2) Channel Mode Register (Capture Mode / Waveform Mode) */
#నిర్వచించు AT91C_TC2_CCR              ( ( AT91_REG * ) 0xFFFA0080 ) /* (TC2) Channel Control Register */
#నిర్వచించు AT91C_TC2_CV               ( ( AT91_REG * ) 0xFFFA0090 ) /* (TC2) Counter Value */
#నిర్వచించు AT91C_TC2_RA               ( ( AT91_REG * ) 0xFFFA0094 ) /* (TC2) Register A */
#నిర్వచించు AT91C_TC2_RB               ( ( AT91_REG * ) 0xFFFA0098 ) /* (TC2) Register B */
#నిర్వచించు AT91C_TC2_IDR              ( ( AT91_REG * ) 0xFFFA00A8 ) /* (TC2) Interrupt Disable Register */
#నిర్వచించు AT91C_TC2_IMR              ( ( AT91_REG * ) 0xFFFA00AC ) /* (TC2) Interrupt Mask Register */
#నిర్వచించు AT91C_TC2_RC               ( ( AT91_REG * ) 0xFFFA009C ) /* (TC2) Register C */
#నిర్వచించు AT91C_TC2_IER              ( ( AT91_REG * ) 0xFFFA00A4 ) /* (TC2) Interrupt Enable Register */
#నిర్వచించు AT91C_TC2_SR               ( ( AT91_REG * ) 0xFFFA00A0 ) /* (TC2) Status Register */
/* ========== Register definition for TCB peripheral ========== */
#నిర్వచించు AT91C_TCB_BMR              ( ( AT91_REG * ) 0xFFFA00C4 ) /* (TCB) TC Block Mode Register */
#నిర్వచించు AT91C_TCB_BCR              ( ( AT91_REG * ) 0xFFFA00C0 ) /* (TCB) TC Block Control Register */
/* ========== Register definition for CAN_MB0 peripheral ========== */
#నిర్వచించు AT91C_CAN_MB0_MDL          ( ( AT91_REG * ) 0xFFFD0214 ) /* (CAN_MB0) MailBox Data Low Register */
#నిర్వచించు AT91C_CAN_MB0_MAM          ( ( AT91_REG * ) 0xFFFD0204 ) /* (CAN_MB0) MailBox Acceptance Mask Register */
#నిర్వచించు AT91C_CAN_MB0_MCR          ( ( AT91_REG * ) 0xFFFD021C ) /* (CAN_MB0) MailBox Control Register */
#నిర్వచించు AT91C_CAN_MB0_MID          ( ( AT91_REG * ) 0xFFFD0208 ) /* (CAN_MB0) MailBox ID Register */
#నిర్వచించు AT91C_CAN_MB0_MSR          ( ( AT91_REG * ) 0xFFFD0210 ) /* (CAN_MB0) MailBox Status Register */
#నిర్వచించు AT91C_CAN_MB0_MFID         ( ( AT91_REG * ) 0xFFFD020C ) /* (CAN_MB0) MailBox Family ID Register */
#నిర్వచించు AT91C_CAN_MB0_MDH          ( ( AT91_REG * ) 0xFFFD0218 ) /* (CAN_MB0) MailBox Data High Register */
#నిర్వచించు AT91C_CAN_MB0_MMR          ( ( AT91_REG * ) 0xFFFD0200 ) /* (CAN_MB0) MailBox Mode Register */
/* ========== Register definition for CAN_MB1 peripheral ========== */
#నిర్వచించు AT91C_CAN_MB1_MDL          ( ( AT91_REG * ) 0xFFFD0234 ) /* (CAN_MB1) MailBox Data Low Register */
#నిర్వచించు AT91C_CAN_MB1_MID          ( ( AT91_REG * ) 0xFFFD0228 ) /* (CAN_MB1) MailBox ID Register */
#నిర్వచించు AT91C_CAN_MB1_MMR          ( ( AT91_REG * ) 0xFFFD0220 ) /* (CAN_MB1) MailBox Mode Register */
#నిర్వచించు AT91C_CAN_MB1_MSR          ( ( AT91_REG * ) 0xFFFD0230 ) /* (CAN_MB1) MailBox Status Register */
#నిర్వచించు AT91C_CAN_MB1_MAM          ( ( AT91_REG * ) 0xFFFD0224 ) /* (CAN_MB1) MailBox Acceptance Mask Register */
#నిర్వచించు AT91C_CAN_MB1_MDH          ( ( AT91_REG * ) 0xFFFD0238 ) /* (CAN_MB1) MailBox Data High Register */
#నిర్వచించు AT91C_CAN_MB1_MCR          ( ( AT91_REG * ) 0xFFFD023C ) /* (CAN_MB1) MailBox Control Register */
#నిర్వచించు AT91C_CAN_MB1_MFID         ( ( AT91_REG * ) 0xFFFD022C ) /* (CAN_MB1) MailBox Family ID Register */
/* ========== Register definition for CAN_MB2 peripheral ========== */
#నిర్వచించు AT91C_CAN_MB2_MCR          ( ( AT91_REG * ) 0xFFFD025C ) /* (CAN_MB2) MailBox Control Register */
#నిర్వచించు AT91C_CAN_MB2_MDH          ( ( AT91_REG * ) 0xFFFD0258 ) /* (CAN_MB2) MailBox Data High Register */
#నిర్వచించు AT91C_CAN_MB2_MID          ( ( AT91_REG * ) 0xFFFD0248 ) /* (CAN_MB2) MailBox ID Register */
#నిర్వచించు AT91C_CAN_MB2_MDL          ( ( AT91_REG * ) 0xFFFD0254 ) /* (CAN_MB2) MailBox Data Low Register */
#నిర్వచించు AT91C_CAN_MB2_MMR          ( ( AT91_REG * ) 0xFFFD0240 ) /* (CAN_MB2) MailBox Mode Register */
#నిర్వచించు AT91C_CAN_MB2_MAM          ( ( AT91_REG * ) 0xFFFD0244 ) /* (CAN_MB2) MailBox Acceptance Mask Register */
#నిర్వచించు AT91C_CAN_MB2_MFID         ( ( AT91_REG * ) 0xFFFD024C ) /* (CAN_MB2) MailBox Family ID Register */
#నిర్వచించు AT91C_CAN_MB2_MSR          ( ( AT91_REG * ) 0xFFFD0250 ) /* (CAN_MB2) MailBox Status Register */
/* ========== Register definition for CAN_MB3 peripheral ========== */
#నిర్వచించు AT91C_CAN_MB3_MFID         ( ( AT91_REG * ) 0xFFFD026C ) /* (CAN_MB3) MailBox Family ID Register */
#నిర్వచించు AT91C_CAN_MB3_MAM          ( ( AT91_REG * ) 0xFFFD0264 ) /* (CAN_MB3) MailBox Acceptance Mask Register */
#నిర్వచించు AT91C_CAN_MB3_MID          ( ( AT91_REG * ) 0xFFFD0268 ) /* (CAN_MB3) MailBox ID Register */
#నిర్వచించు AT91C_CAN_MB3_MCR          ( ( AT91_REG * ) 0xFFFD027C ) /* (CAN_MB3) MailBox Control Register */
#నిర్వచించు AT91C_CAN_MB3_MMR          ( ( AT91_REG * ) 0xFFFD0260 ) /* (CAN_MB3) MailBox Mode Register */
#నిర్వచించు AT91C_CAN_MB3_MSR          ( ( AT91_REG * ) 0xFFFD0270 ) /* (CAN_MB3) MailBox Status Register */
#నిర్వచించు AT91C_CAN_MB3_MDL          ( ( AT91_REG * ) 0xFFFD0274 ) /* (CAN_MB3) MailBox Data Low Register */
#నిర్వచించు AT91C_CAN_MB3_MDH          ( ( AT91_REG * ) 0xFFFD0278 ) /* (CAN_MB3) MailBox Data High Register */
/* ========== Register definition for CAN_MB4 peripheral ========== */
#నిర్వచించు AT91C_CAN_MB4_MID          ( ( AT91_REG * ) 0xFFFD0288 ) /* (CAN_MB4) MailBox ID Register */
#నిర్వచించు AT91C_CAN_MB4_MMR          ( ( AT91_REG * ) 0xFFFD0280 ) /* (CAN_MB4) MailBox Mode Register */
#నిర్వచించు AT91C_CAN_MB4_MDH          ( ( AT91_REG * ) 0xFFFD0298 ) /* (CAN_MB4) MailBox Data High Register */
#నిర్వచించు AT91C_CAN_MB4_MFID         ( ( AT91_REG * ) 0xFFFD028C ) /* (CAN_MB4) MailBox Family ID Register */
#నిర్వచించు AT91C_CAN_MB4_MSR          ( ( AT91_REG * ) 0xFFFD0290 ) /* (CAN_MB4) MailBox Status Register */
#నిర్వచించు AT91C_CAN_MB4_MCR          ( ( AT91_REG * ) 0xFFFD029C ) /* (CAN_MB4) MailBox Control Register */
#నిర్వచించు AT91C_CAN_MB4_MDL          ( ( AT91_REG * ) 0xFFFD0294 ) /* (CAN_MB4) MailBox Data Low Register */
#నిర్వచించు AT91C_CAN_MB4_MAM          ( ( AT91_REG * ) 0xFFFD0284 ) /* (CAN_MB4) MailBox Acceptance Mask Register */
/* ========== Register definition for CAN_MB5 peripheral ========== */
#నిర్వచించు AT91C_CAN_MB5_MSR          ( ( AT91_REG * ) 0xFFFD02B0 ) /* (CAN_MB5) MailBox Status Register */
#నిర్వచించు AT91C_CAN_MB5_MCR          ( ( AT91_REG * ) 0xFFFD02BC ) /* (CAN_MB5) MailBox Control Register */
#నిర్వచించు AT91C_CAN_MB5_MFID         ( ( AT91_REG * ) 0xFFFD02AC ) /* (CAN_MB5) MailBox Family ID Register */
#నిర్వచించు AT91C_CAN_MB5_MDH          ( ( AT91_REG * ) 0xFFFD02B8 ) /* (CAN_MB5) MailBox Data High Register */
#నిర్వచించు AT91C_CAN_MB5_MID          ( ( AT91_REG * ) 0xFFFD02A8 ) /* (CAN_MB5) MailBox ID Register */
#నిర్వచించు AT91C_CAN_MB5_MMR          ( ( AT91_REG * ) 0xFFFD02A0 ) /* (CAN_MB5) MailBox Mode Register */
#నిర్వచించు AT91C_CAN_MB5_MDL          ( ( AT91_REG * ) 0xFFFD02B4 ) /* (CAN_MB5) MailBox Data Low Register */
#నిర్వచించు AT91C_CAN_MB5_MAM          ( ( AT91_REG * ) 0xFFFD02A4 ) /* (CAN_MB5) MailBox Acceptance Mask Register */
/* ========== Register definition for CAN_MB6 peripheral ========== */
#నిర్వచించు AT91C_CAN_MB6_MFID         ( ( AT91_REG * ) 0xFFFD02CC ) /* (CAN_MB6) MailBox Family ID Register */
#నిర్వచించు AT91C_CAN_MB6_MID          ( ( AT91_REG * ) 0xFFFD02C8 ) /* (CAN_MB6) MailBox ID Register */
#నిర్వచించు AT91C_CAN_MB6_MAM          ( ( AT91_REG * ) 0xFFFD02C4 ) /* (CAN_MB6) MailBox Acceptance Mask Register */
#నిర్వచించు AT91C_CAN_MB6_MSR          ( ( AT91_REG * ) 0xFFFD02D0 ) /* (CAN_MB6) MailBox Status Register */
#నిర్వచించు AT91C_CAN_MB6_MDL          ( ( AT91_REG * ) 0xFFFD02D4 ) /* (CAN_MB6) MailBox Data Low Register */
#నిర్వచించు AT91C_CAN_MB6_MCR          ( ( AT91_REG * ) 0xFFFD02DC ) /* (CAN_MB6) MailBox Control Register */
#నిర్వచించు AT91C_CAN_MB6_MDH          ( ( AT91_REG * ) 0xFFFD02D8 ) /* (CAN_MB6) MailBox Data High Register */
#నిర్వచించు AT91C_CAN_MB6_MMR          ( ( AT91_REG * ) 0xFFFD02C0 ) /* (CAN_MB6) MailBox Mode Register */
/* ========== Register definition for CAN_MB7 peripheral ========== */
#నిర్వచించు AT91C_CAN_MB7_MCR          ( ( AT91_REG * ) 0xFFFD02FC ) /* (CAN_MB7) MailBox Control Register */
#నిర్వచించు AT91C_CAN_MB7_MDH          ( ( AT91_REG * ) 0xFFFD02F8 ) /* (CAN_MB7) MailBox Data High Register */
#నిర్వచించు AT91C_CAN_MB7_MFID         ( ( AT91_REG * ) 0xFFFD02EC ) /* (CAN_MB7) MailBox Family ID Register */
#నిర్వచించు AT91C_CAN_MB7_MDL          ( ( AT91_REG * ) 0xFFFD02F4 ) /* (CAN_MB7) MailBox Data Low Register */
#నిర్వచించు AT91C_CAN_MB7_MID          ( ( AT91_REG * ) 0xFFFD02E8 ) /* (CAN_MB7) MailBox ID Register */
#నిర్వచించు AT91C_CAN_MB7_MMR          ( ( AT91_REG * ) 0xFFFD02E0 ) /* (CAN_MB7) MailBox Mode Register */
#నిర్వచించు AT91C_CAN_MB7_MAM          ( ( AT91_REG * ) 0xFFFD02E4 ) /* (CAN_MB7) MailBox Acceptance Mask Register */
#నిర్వచించు AT91C_CAN_MB7_MSR          ( ( AT91_REG * ) 0xFFFD02F0 ) /* (CAN_MB7) MailBox Status Register */
/* ========== Register definition for CAN peripheral ========== */
#నిర్వచించు AT91C_CAN_TCR              ( ( AT91_REG * ) 0xFFFD0024 ) /* (CAN) Transfer Command Register */
#నిర్వచించు AT91C_CAN_IMR              ( ( AT91_REG * ) 0xFFFD000C ) /* (CAN) Interrupt Mask Register */
#నిర్వచించు AT91C_CAN_IER              ( ( AT91_REG * ) 0xFFFD0004 ) /* (CAN) Interrupt Enable Register */
#నిర్వచించు AT91C_CAN_ECR              ( ( AT91_REG * ) 0xFFFD0020 ) /* (CAN) Error Counter Register */
#నిర్వచించు AT91C_CAN_TIMESTP          ( ( AT91_REG * ) 0xFFFD001C ) /* (CAN) Time Stamp Register */
#నిర్వచించు AT91C_CAN_MR               ( ( AT91_REG * ) 0xFFFD0000 ) /* (CAN) Mode Register */
#నిర్వచించు AT91C_CAN_IDR              ( ( AT91_REG * ) 0xFFFD0008 ) /* (CAN) Interrupt Disable Register */
#నిర్వచించు AT91C_CAN_ACR              ( ( AT91_REG * ) 0xFFFD0028 ) /* (CAN) Abort Command Register */
#నిర్వచించు AT91C_CAN_TIM              ( ( AT91_REG * ) 0xFFFD0018 ) /* (CAN) Timer Register */
#నిర్వచించు AT91C_CAN_SR               ( ( AT91_REG * ) 0xFFFD0010 ) /* (CAN) Status Register */
#నిర్వచించు AT91C_CAN_BR               ( ( AT91_REG * ) 0xFFFD0014 ) /* (CAN) Baudrate Register */
#నిర్వచించు AT91C_CAN_VR               ( ( AT91_REG * ) 0xFFFD00FC ) /* (CAN) Version Register */
/* ========== Register definition for EMAC peripheral ========== */
#నిర్వచించు AT91C_EMAC_ISR             ( ( AT91_REG * ) 0xFFFDC024 ) /* (EMAC) Interrupt Status Register */
#నిర్వచించు AT91C_EMAC_SA4H            ( ( AT91_REG * ) 0xFFFDC0B4 ) /* (EMAC) Specific Address 4 Top, Last 2 bytes */
#నిర్వచించు AT91C_EMAC_SA1L            ( ( AT91_REG * ) 0xFFFDC098 ) /* (EMAC) Specific Address 1 Bottom, First 4 bytes */
#నిర్వచించు AT91C_EMAC_ELE             ( ( AT91_REG * ) 0xFFFDC078 ) /* (EMAC) Excessive Length Errors Register */
#నిర్వచించు AT91C_EMAC_LCOL            ( ( AT91_REG * ) 0xFFFDC05C ) /* (EMAC) Late Collision Register */
#నిర్వచించు AT91C_EMAC_RLE             ( ( AT91_REG * ) 0xFFFDC088 ) /* (EMAC) Receive Length Field Mismatch Register */
#నిర్వచించు AT91C_EMAC_WOL             ( ( AT91_REG * ) 0xFFFDC0C4 ) /* (EMAC) Wake On LAN Register */
#నిర్వచించు AT91C_EMAC_DTF             ( ( AT91_REG * ) 0xFFFDC058 ) /* (EMAC) Deferred Transmission Frame Register */
#నిర్వచించు AT91C_EMAC_TUND            ( ( AT91_REG * ) 0xFFFDC064 ) /* (EMAC) Transmit Underrun Error Register */
#నిర్వచించు AT91C_EMAC_NCR             ( ( AT91_REG * ) 0xFFFDC000 ) /* (EMAC) Network Control Register */
#నిర్వచించు AT91C_EMAC_SA4L            ( ( AT91_REG * ) 0xFFFDC0B0 ) /* (EMAC) Specific Address 4 Bottom, First 4 bytes */
#నిర్వచించు AT91C_EMAC_RSR             ( ( AT91_REG * ) 0xFFFDC020 ) /* (EMAC) Receive Status Register */
#నిర్వచించు AT91C_EMAC_SA3L            ( ( AT91_REG * ) 0xFFFDC0A8 ) /* (EMAC) Specific Address 3 Bottom, First 4 bytes */
#నిర్వచించు AT91C_EMAC_TSR             ( ( AT91_REG * ) 0xFFFDC014 ) /* (EMAC) Transmit Status Register */
#నిర్వచించు AT91C_EMAC_IDR             ( ( AT91_REG * ) 0xFFFDC02C ) /* (EMAC) Interrupt Disable Register */
#నిర్వచించు AT91C_EMAC_RSE             ( ( AT91_REG * ) 0xFFFDC074 ) /* (EMAC) Receive Symbol Errors Register */
#నిర్వచించు AT91C_EMAC_ECOL            ( ( AT91_REG * ) 0xFFFDC060 ) /* (EMAC) Excessive Collision Register */
#నిర్వచించు AT91C_EMAC_TID             ( ( AT91_REG * ) 0xFFFDC0B8 ) /* (EMAC) Type ID Checking Register */
#నిర్వచించు AT91C_EMAC_HRB             ( ( AT91_REG * ) 0xFFFDC090 ) /* (EMAC) Hash Address Bottom[31:0] */
#నిర్వచించు AT91C_EMAC_TBQP            ( ( AT91_REG * ) 0xFFFDC01C ) /* (EMAC) Transmit Buffer Queue Pointer */
#నిర్వచించు AT91C_EMAC_USRIO           ( ( AT91_REG * ) 0xFFFDC0C0 ) /* (EMAC) USER Input/Output Register */
#నిర్వచించు AT91C_EMAC_PTR             ( ( AT91_REG * ) 0xFFFDC038 ) /* (EMAC) Pause Time Register */
#నిర్వచించు AT91C_EMAC_SA2H            ( ( AT91_REG * ) 0xFFFDC0A4 ) /* (EMAC) Specific Address 2 Top, Last 2 bytes */
#నిర్వచించు AT91C_EMAC_ROV             ( ( AT91_REG * ) 0xFFFDC070 ) /* (EMAC) Receive Overrun Errors Register */
#నిర్వచించు AT91C_EMAC_ALE             ( ( AT91_REG * ) 0xFFFDC054 ) /* (EMAC) Alignment Error Register */
#నిర్వచించు AT91C_EMAC_RJA             ( ( AT91_REG * ) 0xFFFDC07C ) /* (EMAC) Receive Jabbers Register */
#నిర్వచించు AT91C_EMAC_RBQP            ( ( AT91_REG * ) 0xFFFDC018 ) /* (EMAC) Receive Buffer Queue Pointer */
#నిర్వచించు AT91C_EMAC_TPF             ( ( AT91_REG * ) 0xFFFDC08C ) /* (EMAC) Transmitted Pause Frames Register */
#నిర్వచించు AT91C_EMAC_NCFGR           ( ( AT91_REG * ) 0xFFFDC004 ) /* (EMAC) Network Configuration Register */
#నిర్వచించు AT91C_EMAC_HRT             ( ( AT91_REG * ) 0xFFFDC094 ) /* (EMAC) Hash Address Top[63:32] */
#నిర్వచించు AT91C_EMAC_USF             ( ( AT91_REG * ) 0xFFFDC080 ) /* (EMAC) Undersize Frames Register */
#నిర్వచించు AT91C_EMAC_FCSE            ( ( AT91_REG * ) 0xFFFDC050 ) /* (EMAC) Frame Check Sequence Error Register */
#నిర్వచించు AT91C_EMAC_TPQ             ( ( AT91_REG * ) 0xFFFDC0BC ) /* (EMAC) Transmit Pause Quantum Register */
#నిర్వచించు AT91C_EMAC_MAN             ( ( AT91_REG * ) 0xFFFDC034 ) /* (EMAC) PHY Maintenance Register */
#నిర్వచించు AT91C_EMAC_FTO             ( ( AT91_REG * ) 0xFFFDC040 ) /* (EMAC) Frames Transmitted OK Register */
#నిర్వచించు AT91C_EMAC_REV             ( ( AT91_REG * ) 0xFFFDC0FC ) /* (EMAC) Revision Register */
#నిర్వచించు AT91C_EMAC_IMR             ( ( AT91_REG * ) 0xFFFDC030 ) /* (EMAC) Interrupt Mask Register */
#నిర్వచించు AT91C_EMAC_SCF             ( ( AT91_REG * ) 0xFFFDC044 ) /* (EMAC) Single Collision Frame Register */
#నిర్వచించు AT91C_EMAC_PFR             ( ( AT91_REG * ) 0xFFFDC03C ) /* (EMAC) Pause Frames received Register */
#నిర్వచించు AT91C_EMAC_MCF             ( ( AT91_REG * ) 0xFFFDC048 ) /* (EMAC) Multiple Collision Frame Register */
#నిర్వచించు AT91C_EMAC_NSR             ( ( AT91_REG * ) 0xFFFDC008 ) /* (EMAC) Network Status Register */
#నిర్వచించు AT91C_EMAC_SA2L            ( ( AT91_REG * ) 0xFFFDC0A0 ) /* (EMAC) Specific Address 2 Bottom, First 4 bytes */
#నిర్వచించు AT91C_EMAC_FRO             ( ( AT91_REG * ) 0xFFFDC04C ) /* (EMAC) Frames Received OK Register */
#నిర్వచించు AT91C_EMAC_IER             ( ( AT91_REG * ) 0xFFFDC028 ) /* (EMAC) Interrupt Enable Register */
#నిర్వచించు AT91C_EMAC_SA1H            ( ( AT91_REG * ) 0xFFFDC09C ) /* (EMAC) Specific Address 1 Top, Last 2 bytes */
#నిర్వచించు AT91C_EMAC_CSE             ( ( AT91_REG * ) 0xFFFDC068 ) /* (EMAC) Carrier Sense Error Register */
#నిర్వచించు AT91C_EMAC_SA3H            ( ( AT91_REG * ) 0xFFFDC0AC ) /* (EMAC) Specific Address 3 Top, Last 2 bytes */
#నిర్వచించు AT91C_EMAC_RRE             ( ( AT91_REG * ) 0xFFFDC06C ) /* (EMAC) Receive Resource Error Register */
#నిర్వచించు AT91C_EMAC_STE             ( ( AT91_REG * ) 0xFFFDC084 ) /* (EMAC) SQE Test Error Register */
/* ========== Register definition for PDC_ADC peripheral ========== */
#నిర్వచించు AT91C_ADC_PTSR             ( ( AT91_REG * ) 0xFFFD8124 ) /* (PDC_ADC) PDC Transfer Status Register */
#నిర్వచించు AT91C_ADC_PTCR             ( ( AT91_REG * ) 0xFFFD8120 ) /* (PDC_ADC) PDC Transfer Control Register */
#నిర్వచించు AT91C_ADC_TNPR             ( ( AT91_REG * ) 0xFFFD8118 ) /* (PDC_ADC) Transmit Next Pointer Register */
#నిర్వచించు AT91C_ADC_TNCR             ( ( AT91_REG * ) 0xFFFD811C ) /* (PDC_ADC) Transmit Next Counter Register */
#నిర్వచించు AT91C_ADC_RNPR             ( ( AT91_REG * ) 0xFFFD8110 ) /* (PDC_ADC) Receive Next Pointer Register */
#నిర్వచించు AT91C_ADC_RNCR             ( ( AT91_REG * ) 0xFFFD8114 ) /* (PDC_ADC) Receive Next Counter Register */
#నిర్వచించు AT91C_ADC_RPR              ( ( AT91_REG * ) 0xFFFD8100 ) /* (PDC_ADC) Receive Pointer Register */
#నిర్వచించు AT91C_ADC_TCR              ( ( AT91_REG * ) 0xFFFD810C ) /* (PDC_ADC) Transmit Counter Register */
#నిర్వచించు AT91C_ADC_TPR              ( ( AT91_REG * ) 0xFFFD8108 ) /* (PDC_ADC) Transmit Pointer Register */
#నిర్వచించు AT91C_ADC_RCR              ( ( AT91_REG * ) 0xFFFD8104 ) /* (PDC_ADC) Receive Counter Register */
/* ========== Register definition for ADC peripheral ========== */
#నిర్వచించు AT91C_ADC_CDR2             ( ( AT91_REG * ) 0xFFFD8038 ) /* (ADC) ADC Channel Data Register 2 */
#నిర్వచించు AT91C_ADC_CDR3             ( ( AT91_REG * ) 0xFFFD803C ) /* (ADC) ADC Channel Data Register 3 */
#నిర్వచించు AT91C_ADC_CDR0             ( ( AT91_REG * ) 0xFFFD8030 ) /* (ADC) ADC Channel Data Register 0 */
#నిర్వచించు AT91C_ADC_CDR5             ( ( AT91_REG * ) 0xFFFD8044 ) /* (ADC) ADC Channel Data Register 5 */
#నిర్వచించు AT91C_ADC_CHDR             ( ( AT91_REG * ) 0xFFFD8014 ) /* (ADC) ADC Channel Disable Register */
#నిర్వచించు AT91C_ADC_SR               ( ( AT91_REG * ) 0xFFFD801C ) /* (ADC) ADC Status Register */
#నిర్వచించు AT91C_ADC_CDR4             ( ( AT91_REG * ) 0xFFFD8040 ) /* (ADC) ADC Channel Data Register 4 */
#నిర్వచించు AT91C_ADC_CDR1             ( ( AT91_REG * ) 0xFFFD8034 ) /* (ADC) ADC Channel Data Register 1 */
#నిర్వచించు AT91C_ADC_LCDR             ( ( AT91_REG * ) 0xFFFD8020 ) /* (ADC) ADC Last Converted Data Register */
#నిర్వచించు AT91C_ADC_IDR              ( ( AT91_REG * ) 0xFFFD8028 ) /* (ADC) ADC Interrupt Disable Register */
#నిర్వచించు AT91C_ADC_CR               ( ( AT91_REG * ) 0xFFFD8000 ) /* (ADC) ADC Control Register */
#నిర్వచించు AT91C_ADC_CDR7             ( ( AT91_REG * ) 0xFFFD804C ) /* (ADC) ADC Channel Data Register 7 */
#నిర్వచించు AT91C_ADC_CDR6             ( ( AT91_REG * ) 0xFFFD8048 ) /* (ADC) ADC Channel Data Register 6 */
#నిర్వచించు AT91C_ADC_IER              ( ( AT91_REG * ) 0xFFFD8024 ) /* (ADC) ADC Interrupt Enable Register */
#నిర్వచించు AT91C_ADC_CHER             ( ( AT91_REG * ) 0xFFFD8010 ) /* (ADC) ADC Channel Enable Register */
#నిర్వచించు AT91C_ADC_CHSR             ( ( AT91_REG * ) 0xFFFD8018 ) /* (ADC) ADC Channel Status Register */
#నిర్వచించు AT91C_ADC_MR               ( ( AT91_REG * ) 0xFFFD8004 ) /* (ADC) ADC Mode Register */
#నిర్వచించు AT91C_ADC_IMR              ( ( AT91_REG * ) 0xFFFD802C ) /* (ADC) ADC Interrupt Mask Register */
/* ========== Register definition for PDC_AES peripheral ========== */
#నిర్వచించు AT91C_AES_TPR              ( ( AT91_REG * ) 0xFFFA4108 ) /* (PDC_AES) Transmit Pointer Register */
#నిర్వచించు AT91C_AES_PTCR             ( ( AT91_REG * ) 0xFFFA4120 ) /* (PDC_AES) PDC Transfer Control Register */
#నిర్వచించు AT91C_AES_RNPR             ( ( AT91_REG * ) 0xFFFA4110 ) /* (PDC_AES) Receive Next Pointer Register */
#నిర్వచించు AT91C_AES_TNCR             ( ( AT91_REG * ) 0xFFFA411C ) /* (PDC_AES) Transmit Next Counter Register */
#నిర్వచించు AT91C_AES_TCR              ( ( AT91_REG * ) 0xFFFA410C ) /* (PDC_AES) Transmit Counter Register */
#నిర్వచించు AT91C_AES_RCR              ( ( AT91_REG * ) 0xFFFA4104 ) /* (PDC_AES) Receive Counter Register */
#నిర్వచించు AT91C_AES_RNCR             ( ( AT91_REG * ) 0xFFFA4114 ) /* (PDC_AES) Receive Next Counter Register */
#నిర్వచించు AT91C_AES_TNPR             ( ( AT91_REG * ) 0xFFFA4118 ) /* (PDC_AES) Transmit Next Pointer Register */
#నిర్వచించు AT91C_AES_RPR              ( ( AT91_REG * ) 0xFFFA4100 ) /* (PDC_AES) Receive Pointer Register */
#నిర్వచించు AT91C_AES_PTSR             ( ( AT91_REG * ) 0xFFFA4124 ) /* (PDC_AES) PDC Transfer Status Register */
/* ========== Register definition for AES peripheral ========== */
#నిర్వచించు AT91C_AES_IVxR             ( ( AT91_REG * ) 0xFFFA4060 ) /* (AES) Initialization Vector x Register */
#నిర్వచించు AT91C_AES_MR               ( ( AT91_REG * ) 0xFFFA4004 ) /* (AES) Mode Register */
#నిర్వచించు AT91C_AES_VR               ( ( AT91_REG * ) 0xFFFA40FC ) /* (AES) AES Version Register */
#నిర్వచించు AT91C_AES_ODATAxR          ( ( AT91_REG * ) 0xFFFA4050 ) /* (AES) Output Data x Register */
#నిర్వచించు AT91C_AES_IDATAxR          ( ( AT91_REG * ) 0xFFFA4040 ) /* (AES) Input Data x Register */
#నిర్వచించు AT91C_AES_CR               ( ( AT91_REG * ) 0xFFFA4000 ) /* (AES) Control Register */
#నిర్వచించు AT91C_AES_IDR              ( ( AT91_REG * ) 0xFFFA4014 ) /* (AES) Interrupt Disable Register */
#నిర్వచించు AT91C_AES_IMR              ( ( AT91_REG * ) 0xFFFA4018 ) /* (AES) Interrupt Mask Register */
#నిర్వచించు AT91C_AES_IER              ( ( AT91_REG * ) 0xFFFA4010 ) /* (AES) Interrupt Enable Register */
#నిర్వచించు AT91C_AES_KEYWxR           ( ( AT91_REG * ) 0xFFFA4020 ) /* (AES) Key Word x Register */
#నిర్వచించు AT91C_AES_ISR              ( ( AT91_REG * ) 0xFFFA401C ) /* (AES) Interrupt Status Register */
/* ========== Register definition for PDC_TDES peripheral ========== */
#నిర్వచించు AT91C_TDES_RNCR            ( ( AT91_REG * ) 0xFFFA8114 ) /* (PDC_TDES) Receive Next Counter Register */
#నిర్వచించు AT91C_TDES_TCR             ( ( AT91_REG * ) 0xFFFA810C ) /* (PDC_TDES) Transmit Counter Register */
#నిర్వచించు AT91C_TDES_RCR             ( ( AT91_REG * ) 0xFFFA8104 ) /* (PDC_TDES) Receive Counter Register */
#నిర్వచించు AT91C_TDES_TNPR            ( ( AT91_REG * ) 0xFFFA8118 ) /* (PDC_TDES) Transmit Next Pointer Register */
#నిర్వచించు AT91C_TDES_RNPR            ( ( AT91_REG * ) 0xFFFA8110 ) /* (PDC_TDES) Receive Next Pointer Register */
#నిర్వచించు AT91C_TDES_RPR             ( ( AT91_REG * ) 0xFFFA8100 ) /* (PDC_TDES) Receive Pointer Register */
#నిర్వచించు AT91C_TDES_TNCR            ( ( AT91_REG * ) 0xFFFA811C ) /* (PDC_TDES) Transmit Next Counter Register */
#నిర్వచించు AT91C_TDES_TPR             ( ( AT91_REG * ) 0xFFFA8108 ) /* (PDC_TDES) Transmit Pointer Register */
#నిర్వచించు AT91C_TDES_PTSR            ( ( AT91_REG * ) 0xFFFA8124 ) /* (PDC_TDES) PDC Transfer Status Register */
#నిర్వచించు AT91C_TDES_PTCR            ( ( AT91_REG * ) 0xFFFA8120 ) /* (PDC_TDES) PDC Transfer Control Register */
/* ========== Register definition for TDES peripheral ========== */
#నిర్వచించు AT91C_TDES_KEY2WxR         ( ( AT91_REG * ) 0xFFFA8028 ) /* (TDES) Key 2 Word x Register */
#నిర్వచించు AT91C_TDES_KEY3WxR         ( ( AT91_REG * ) 0xFFFA8030 ) /* (TDES) Key 3 Word x Register */
#నిర్వచించు AT91C_TDES_IDR             ( ( AT91_REG * ) 0xFFFA8014 ) /* (TDES) Interrupt Disable Register */
#నిర్వచించు AT91C_TDES_VR              ( ( AT91_REG * ) 0xFFFA80FC ) /* (TDES) TDES Version Register */
#నిర్వచించు AT91C_TDES_IVxR            ( ( AT91_REG * ) 0xFFFA8060 ) /* (TDES) Initialization Vector x Register */
#నిర్వచించు AT91C_TDES_ODATAxR         ( ( AT91_REG * ) 0xFFFA8050 ) /* (TDES) Output Data x Register */
#నిర్వచించు AT91C_TDES_IMR             ( ( AT91_REG * ) 0xFFFA8018 ) /* (TDES) Interrupt Mask Register */
#నిర్వచించు AT91C_TDES_MR              ( ( AT91_REG * ) 0xFFFA8004 ) /* (TDES) Mode Register */
#నిర్వచించు AT91C_TDES_CR              ( ( AT91_REG * ) 0xFFFA8000 ) /* (TDES) Control Register */
#నిర్వచించు AT91C_TDES_IER             ( ( AT91_REG * ) 0xFFFA8010 ) /* (TDES) Interrupt Enable Register */
#నిర్వచించు AT91C_TDES_ISR             ( ( AT91_REG * ) 0xFFFA801C ) /* (TDES) Interrupt Status Register */
#నిర్వచించు AT91C_TDES_IDATAxR         ( ( AT91_REG * ) 0xFFFA8040 ) /* (TDES) Input Data x Register */
#నిర్వచించు AT91C_TDES_KEY1WxR         ( ( AT91_REG * ) 0xFFFA8020 ) /* (TDES) Key 1 Word x Register */

/* ***************************************************************************** */
/*               PIO DEFINITIONS FOR AT91SAM7X256 */
/* ***************************************************************************** */
#నిర్వచించు AT91C_PIO_PA0             ( ( గుర్తులేని పూర్ణాంకం ) 1 << 0 )         /* Pin Controlled by PA0 */
#నిర్వచించు AT91C_PA0_RXD0            ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA0 )  /*  USART 0 Receive Data */
#నిర్వచించు AT91C_PIO_PA1             ( ( గుర్తులేని పూర్ణాంకం ) 1 << 1 )         /* Pin Controlled by PA1 */
#నిర్వచించు AT91C_PA1_TXD0            ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA1 )  /*  USART 0 Transmit Data */
#నిర్వచించు AT91C_PIO_PA10            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 10 )        /* Pin Controlled by PA10 */
#నిర్వచించు AT91C_PA10_TWD            ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA10 ) /*  TWI Two-wire Serial Data */
#నిర్వచించు AT91C_PIO_PA11            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 11 )        /* Pin Controlled by PA11 */
#నిర్వచించు AT91C_PA11_TWCK           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA11 ) /*  TWI Two-wire Serial Clock */
#నిర్వచించు AT91C_PIO_PA12            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 12 )        /* Pin Controlled by PA12 */
#నిర్వచించు AT91C_PA12_NPCS00         ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA12 ) /*  SPI 0 Peripheral Chip Select 0 */
#నిర్వచించు AT91C_PIO_PA13            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 13 )        /* Pin Controlled by PA13 */
#నిర్వచించు AT91C_PA13_NPCS01         ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA13 ) /*  SPI 0 Peripheral Chip Select 1 */
#నిర్వచించు AT91C_PA13_PCK1           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA13 ) /*  PMC Programmable Clock Output 1 */
#నిర్వచించు AT91C_PIO_PA14            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 14 )        /* Pin Controlled by PA14 */
#నిర్వచించు AT91C_PA14_NPCS02         ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA14 ) /*  SPI 0 Peripheral Chip Select 2 */
#నిర్వచించు AT91C_PA14_IRQ1           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA14 ) /*  External Interrupt 1 */
#నిర్వచించు AT91C_PIO_PA15            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 15 )        /* Pin Controlled by PA15 */
#నిర్వచించు AT91C_PA15_NPCS03         ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA15 ) /*  SPI 0 Peripheral Chip Select 3 */
#నిర్వచించు AT91C_PA15_TCLK2          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA15 ) /*  Timer Counter 2 external clock input */
#నిర్వచించు AT91C_PIO_PA16            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 16 )        /* Pin Controlled by PA16 */
#నిర్వచించు AT91C_PA16_MISO0          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA16 ) /*  SPI 0 Master In Slave */
#నిర్వచించు AT91C_PIO_PA17            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 17 )        /* Pin Controlled by PA17 */
#నిర్వచించు AT91C_PA17_MOSI0          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA17 ) /*  SPI 0 Master Out Slave */
#నిర్వచించు AT91C_PIO_PA18            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 18 )        /* Pin Controlled by PA18 */
#నిర్వచించు AT91C_PA18_SPCK0          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA18 ) /*  SPI 0 Serial Clock */
#నిర్వచించు AT91C_PIO_PA19            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 19 )        /* Pin Controlled by PA19 */
#నిర్వచించు AT91C_PA19_CANRX          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA19 ) /*  CAN Receive */
#నిర్వచించు AT91C_PIO_PA2             ( ( గుర్తులేని పూర్ణాంకం ) 1 << 2 )         /* Pin Controlled by PA2 */
#నిర్వచించు AT91C_PA2_SCK0            ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA2 )  /*  USART 0 Serial Clock */
#నిర్వచించు AT91C_PA2_NPCS11          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA2 )  /*  SPI 1 Peripheral Chip Select 1 */
#నిర్వచించు AT91C_PIO_PA20            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 20 )        /* Pin Controlled by PA20 */
#నిర్వచించు AT91C_PA20_CANTX          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA20 ) /*  CAN Transmit */
#నిర్వచించు AT91C_PIO_PA21            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 21 )        /* Pin Controlled by PA21 */
#నిర్వచించు AT91C_PA21_TF             ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA21 ) /*  SSC Transmit Frame Sync */
#నిర్వచించు AT91C_PA21_NPCS10         ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA21 ) /*  SPI 1 Peripheral Chip Select 0 */
#నిర్వచించు AT91C_PIO_PA22            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 22 )        /* Pin Controlled by PA22 */
#నిర్వచించు AT91C_PA22_TK             ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA22 ) /*  SSC Transmit Clock */
#నిర్వచించు AT91C_PA22_SPCK1          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA22 ) /*  SPI 1 Serial Clock */
#నిర్వచించు AT91C_PIO_PA23            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 23 )        /* Pin Controlled by PA23 */
#నిర్వచించు AT91C_PA23_TD             ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA23 ) /*  SSC Transmit data */
#నిర్వచించు AT91C_PA23_MOSI1          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA23 ) /*  SPI 1 Master Out Slave */
#నిర్వచించు AT91C_PIO_PA24            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 24 )        /* Pin Controlled by PA24 */
#నిర్వచించు AT91C_PA24_RD             ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA24 ) /*  SSC Receive Data */
#నిర్వచించు AT91C_PA24_MISO1          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA24 ) /*  SPI 1 Master In Slave */
#నిర్వచించు AT91C_PIO_PA25            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 25 )        /* Pin Controlled by PA25 */
#నిర్వచించు AT91C_PA25_RK             ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA25 ) /*  SSC Receive Clock */
#నిర్వచించు AT91C_PA25_NPCS11         ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA25 ) /*  SPI 1 Peripheral Chip Select 1 */
#నిర్వచించు AT91C_PIO_PA26            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 26 )        /* Pin Controlled by PA26 */
#నిర్వచించు AT91C_PA26_RF             ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA26 ) /*  SSC Receive Frame Sync */
#నిర్వచించు AT91C_PA26_NPCS12         ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA26 ) /*  SPI 1 Peripheral Chip Select 2 */
#నిర్వచించు AT91C_PIO_PA27            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 27 )        /* Pin Controlled by PA27 */
#నిర్వచించు AT91C_PA27_DRXD           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA27 ) /*  DBGU Debug Receive Data */
#నిర్వచించు AT91C_PA27_PCK3           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA27 ) /*  PMC Programmable Clock Output 3 */
#నిర్వచించు AT91C_PIO_PA28            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 28 )        /* Pin Controlled by PA28 */
#నిర్వచించు AT91C_PA28_DTXD           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA28 ) /*  DBGU Debug Transmit Data */
#నిర్వచించు AT91C_PIO_PA29            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 29 )        /* Pin Controlled by PA29 */
#నిర్వచించు AT91C_PA29_FIQ            ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA29 ) /*  AIC Fast Interrupt Input */
#నిర్వచించు AT91C_PA29_NPCS13         ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA29 ) /*  SPI 1 Peripheral Chip Select 3 */
#నిర్వచించు AT91C_PIO_PA3             ( ( గుర్తులేని పూర్ణాంకం ) 1 << 3 )         /* Pin Controlled by PA3 */
#నిర్వచించు AT91C_PA3_RTS0            ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA3 )  /*  USART 0 Ready To Send */
#నిర్వచించు AT91C_PA3_NPCS12          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA3 )  /*  SPI 1 Peripheral Chip Select 2 */
#నిర్వచించు AT91C_PIO_PA30            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 30 )        /* Pin Controlled by PA30 */
#నిర్వచించు AT91C_PA30_IRQ0           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA30 ) /*  External Interrupt 0 */
#నిర్వచించు AT91C_PA30_PCK2           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA30 ) /*  PMC Programmable Clock Output 2 */
#నిర్వచించు AT91C_PIO_PA4             ( ( గుర్తులేని పూర్ణాంకం ) 1 << 4 )         /* Pin Controlled by PA4 */
#నిర్వచించు AT91C_PA4_CTS0            ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA4 )  /*  USART 0 Clear To Send */
#నిర్వచించు AT91C_PA4_NPCS13          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA4 )  /*  SPI 1 Peripheral Chip Select 3 */
#నిర్వచించు AT91C_PIO_PA5             ( ( గుర్తులేని పూర్ణాంకం ) 1 << 5 )         /* Pin Controlled by PA5 */
#నిర్వచించు AT91C_PA5_RXD1            ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA5 )  /*  USART 1 Receive Data */
#నిర్వచించు AT91C_PIO_PA6             ( ( గుర్తులేని పూర్ణాంకం ) 1 << 6 )         /* Pin Controlled by PA6 */
#నిర్వచించు AT91C_PA6_TXD1            ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA6 )  /*  USART 1 Transmit Data */
#నిర్వచించు AT91C_PIO_PA7             ( ( గుర్తులేని పూర్ణాంకం ) 1 << 7 )         /* Pin Controlled by PA7 */
#నిర్వచించు AT91C_PA7_SCK1            ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA7 )  /*  USART 1 Serial Clock */
#నిర్వచించు AT91C_PA7_NPCS01          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA7 )  /*  SPI 0 Peripheral Chip Select 1 */
#నిర్వచించు AT91C_PIO_PA8             ( ( గుర్తులేని పూర్ణాంకం ) 1 << 8 )         /* Pin Controlled by PA8 */
#నిర్వచించు AT91C_PA8_RTS1            ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA8 )  /*  USART 1 Ready To Send */
#నిర్వచించు AT91C_PA8_NPCS02          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA8 )  /*  SPI 0 Peripheral Chip Select 2 */
#నిర్వచించు AT91C_PIO_PA9             ( ( గుర్తులేని పూర్ణాంకం ) 1 << 9 )         /* Pin Controlled by PA9 */
#నిర్వచించు AT91C_PA9_CTS1            ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA9 )  /*  USART 1 Clear To Send */
#నిర్వచించు AT91C_PA9_NPCS03          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PA9 )  /*  SPI 0 Peripheral Chip Select 3 */
#నిర్వచించు AT91C_PIO_PB0             ( ( గుర్తులేని పూర్ణాంకం ) 1 << 0 )         /* Pin Controlled by PB0 */
#నిర్వచించు AT91C_PB0_ETXCK_EREFCK    ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB0 )  /*  Ethernet MAC Transmit Clock/Reference Clock */
#నిర్వచించు AT91C_PB0_PCK0            ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB0 )  /*  PMC Programmable Clock Output 0 */
#నిర్వచించు AT91C_PIO_PB1             ( ( గుర్తులేని పూర్ణాంకం ) 1 << 1 )         /* Pin Controlled by PB1 */
#నిర్వచించు AT91C_PB1_ETXEN           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB1 )  /*  Ethernet MAC Transmit Enable */
#నిర్వచించు AT91C_PIO_PB10            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 10 )        /* Pin Controlled by PB10 */
#నిర్వచించు AT91C_PB10_ETX2           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB10 ) /*  Ethernet MAC Transmit Data 2 */
#నిర్వచించు AT91C_PB10_NPCS11         ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB10 ) /*  SPI 1 Peripheral Chip Select 1 */
#నిర్వచించు AT91C_PIO_PB11            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 11 )        /* Pin Controlled by PB11 */
#నిర్వచించు AT91C_PB11_ETX3           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB11 ) /*  Ethernet MAC Transmit Data 3 */
#నిర్వచించు AT91C_PB11_NPCS12         ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB11 ) /*  SPI 1 Peripheral Chip Select 2 */
#నిర్వచించు AT91C_PIO_PB12            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 12 )        /* Pin Controlled by PB12 */
#నిర్వచించు AT91C_PB12_ETXER          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB12 ) /*  Ethernet MAC Transmit Coding Error */
#నిర్వచించు AT91C_PB12_TCLK0          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB12 ) /*  Timer Counter 0 external clock input */
#నిర్వచించు AT91C_PIO_PB13            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 13 )        /* Pin Controlled by PB13 */
#నిర్వచించు AT91C_PB13_ERX2           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB13 ) /*  Ethernet MAC Receive Data 2 */
#నిర్వచించు AT91C_PB13_NPCS01         ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB13 ) /*  SPI 0 Peripheral Chip Select 1 */
#నిర్వచించు AT91C_PIO_PB14            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 14 )        /* Pin Controlled by PB14 */
#నిర్వచించు AT91C_PB14_ERX3           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB14 ) /*  Ethernet MAC Receive Data 3 */
#నిర్వచించు AT91C_PB14_NPCS02         ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB14 ) /*  SPI 0 Peripheral Chip Select 2 */
#నిర్వచించు AT91C_PIO_PB15            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 15 )        /* Pin Controlled by PB15 */
#నిర్వచించు AT91C_PB15_ERXDV          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB15 ) /*  Ethernet MAC Receive Data Valid */
#నిర్వచించు AT91C_PIO_PB16            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 16 )        /* Pin Controlled by PB16 */
#నిర్వచించు AT91C_PB16_ECOL           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB16 ) /*  Ethernet MAC Collision Detected */
#నిర్వచించు AT91C_PB16_NPCS13         ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB16 ) /*  SPI 1 Peripheral Chip Select 3 */
#నిర్వచించు AT91C_PIO_PB17            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 17 )        /* Pin Controlled by PB17 */
#నిర్వచించు AT91C_PB17_ERXCK          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB17 ) /*  Ethernet MAC Receive Clock */
#నిర్వచించు AT91C_PB17_NPCS03         ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB17 ) /*  SPI 0 Peripheral Chip Select 3 */
#నిర్వచించు AT91C_PIO_PB18            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 18 )        /* Pin Controlled by PB18 */
#నిర్వచించు AT91C_PB18_EF100          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB18 ) /*  Ethernet MAC Force 100 Mbits/sec */
#నిర్వచించు AT91C_PB18_ADTRG          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB18 ) /*  ADC External Trigger */
#నిర్వచించు AT91C_PIO_PB19            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 19 )        /* Pin Controlled by PB19 */
#నిర్వచించు AT91C_PB19_PWM0           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB19 ) /*  PWM Channel 0 */
#నిర్వచించు AT91C_PB19_TCLK1          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB19 ) /*  Timer Counter 1 external clock input */
#నిర్వచించు AT91C_PIO_PB2             ( ( గుర్తులేని పూర్ణాంకం ) 1 << 2 )         /* Pin Controlled by PB2 */
#నిర్వచించు AT91C_PB2_ETX0            ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB2 )  /*  Ethernet MAC Transmit Data 0 */
#నిర్వచించు AT91C_PIO_PB20            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 20 )        /* Pin Controlled by PB20 */
#నిర్వచించు AT91C_PB20_PWM1           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB20 ) /*  PWM Channel 1 */
#నిర్వచించు AT91C_PB20_PCK0           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB20 ) /*  PMC Programmable Clock Output 0 */
#నిర్వచించు AT91C_PIO_PB21            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 21 )        /* Pin Controlled by PB21 */
#నిర్వచించు AT91C_PB21_PWM2           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB21 ) /*  PWM Channel 2 */
#నిర్వచించు AT91C_PB21_PCK1           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB21 ) /*  PMC Programmable Clock Output 1 */
#నిర్వచించు AT91C_PIO_PB22            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 22 )        /* Pin Controlled by PB22 */
#నిర్వచించు AT91C_PB22_PWM3           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB22 ) /*  PWM Channel 3 */
#నిర్వచించు AT91C_PB22_PCK2           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB22 ) /*  PMC Programmable Clock Output 2 */
#నిర్వచించు AT91C_PIO_PB23            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 23 )        /* Pin Controlled by PB23 */
#నిర్వచించు AT91C_PB23_TIOA0          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB23 ) /*  Timer Counter 0 Multipurpose Timer I/O Pin A */
#నిర్వచించు AT91C_PB23_DCD1           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB23 ) /*  USART 1 Data Carrier Detect */
#నిర్వచించు AT91C_PIO_PB24            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 24 )        /* Pin Controlled by PB24 */
#నిర్వచించు AT91C_PB24_TIOB0          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB24 ) /*  Timer Counter 0 Multipurpose Timer I/O Pin B */
#నిర్వచించు AT91C_PB24_DSR1           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB24 ) /*  USART 1 Data Set ready */
#నిర్వచించు AT91C_PIO_PB25            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 25 )        /* Pin Controlled by PB25 */
#నిర్వచించు AT91C_PB25_TIOA1          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB25 ) /*  Timer Counter 1 Multipurpose Timer I/O Pin A */
#నిర్వచించు AT91C_PB25_DTR1           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB25 ) /*  USART 1 Data Terminal ready */
#నిర్వచించు AT91C_PIO_PB26            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 26 )        /* Pin Controlled by PB26 */
#నిర్వచించు AT91C_PB26_TIOB1          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB26 ) /*  Timer Counter 1 Multipurpose Timer I/O Pin B */
#నిర్వచించు AT91C_PB26_RI1            ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB26 ) /*  USART 1 Ring Indicator */
#నిర్వచించు AT91C_PIO_PB27            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 27 )        /* Pin Controlled by PB27 */
#నిర్వచించు AT91C_PB27_TIOA2          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB27 ) /*  Timer Counter 2 Multipurpose Timer I/O Pin A */
#నిర్వచించు AT91C_PB27_PWM0           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB27 ) /*  PWM Channel 0 */
#నిర్వచించు AT91C_PIO_PB28            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 28 )        /* Pin Controlled by PB28 */
#నిర్వచించు AT91C_PB28_TIOB2          ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB28 ) /*  Timer Counter 2 Multipurpose Timer I/O Pin B */
#నిర్వచించు AT91C_PB28_PWM1           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB28 ) /*  PWM Channel 1 */
#నిర్వచించు AT91C_PIO_PB29            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 29 )        /* Pin Controlled by PB29 */
#నిర్వచించు AT91C_PB29_PCK1           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB29 ) /*  PMC Programmable Clock Output 1 */
#నిర్వచించు AT91C_PB29_PWM2           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB29 ) /*  PWM Channel 2 */
#నిర్వచించు AT91C_PIO_PB3             ( ( గుర్తులేని పూర్ణాంకం ) 1 << 3 )         /* Pin Controlled by PB3 */
#నిర్వచించు AT91C_PB3_ETX1            ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB3 )  /*  Ethernet MAC Transmit Data 1 */
#నిర్వచించు AT91C_PIO_PB30            ( ( గుర్తులేని పూర్ణాంకం ) 1 << 30 )        /* Pin Controlled by PB30 */
#నిర్వచించు AT91C_PB30_PCK2           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB30 ) /*  PMC Programmable Clock Output 2 */
#నిర్వచించు AT91C_PB30_PWM3           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB30 ) /*  PWM Channel 3 */
#నిర్వచించు AT91C_PIO_PB4             ( ( గుర్తులేని పూర్ణాంకం ) 1 << 4 )         /* Pin Controlled by PB4 */
#నిర్వచించు AT91C_PB4_ECRS_ECRSDV     ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB4 )  /*  Ethernet MAC Carrier Sense/Carrier Sense and Data Valid */
#నిర్వచించు AT91C_PIO_PB5             ( ( గుర్తులేని పూర్ణాంకం ) 1 << 5 )         /* Pin Controlled by PB5 */
#నిర్వచించు AT91C_PB5_ERX0            ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB5 )  /*  Ethernet MAC Receive Data 0 */
#నిర్వచించు AT91C_PIO_PB6             ( ( గుర్తులేని పూర్ణాంకం ) 1 << 6 )         /* Pin Controlled by PB6 */
#నిర్వచించు AT91C_PB6_ERX1            ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB6 )  /*  Ethernet MAC Receive Data 1 */
#నిర్వచించు AT91C_PIO_PB7             ( ( గుర్తులేని పూర్ణాంకం ) 1 << 7 )         /* Pin Controlled by PB7 */
#నిర్వచించు AT91C_PB7_ERXER           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB7 )  /*  Ethernet MAC Receive Error */
#నిర్వచించు AT91C_PIO_PB8             ( ( గుర్తులేని పూర్ణాంకం ) 1 << 8 )         /* Pin Controlled by PB8 */
#నిర్వచించు AT91C_PB8_EMDC            ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB8 )  /*  Ethernet MAC Management Data Clock */
#నిర్వచించు AT91C_PIO_PB9             ( ( గుర్తులేని పూర్ణాంకం ) 1 << 9 )         /* Pin Controlled by PB9 */
#నిర్వచించు AT91C_PB9_EMDIO           ( ( గుర్తులేని పూర్ణాంకం ) AT91C_PIO_PB9 )  /*  Ethernet MAC Management Data Input/Output */

/* ***************************************************************************** */
/*               PERIPHERAL ID DEFINITIONS FOR AT91SAM7X256 */
/* ***************************************************************************** */
#నిర్వచించు AT91C_ID_FIQ            ( ( గుర్తులేని పూర్ణాంకం ) 0 )  /* Advanced Interrupt Controller (FIQ) */
#నిర్వచించు AT91C_ID_SYS            ( ( గుర్తులేని పూర్ణాంకం ) 1 )  /* System Peripheral */
#నిర్వచించు AT91C_ID_PIOA           ( ( గుర్తులేని పూర్ణాంకం ) 2 )  /* Parallel IO Controller A */
#నిర్వచించు AT91C_ID_PIOB           ( ( గుర్తులేని పూర్ణాంకం ) 3 )  /* Parallel IO Controller B */
#నిర్వచించు AT91C_ID_SPI0           ( ( గుర్తులేని పూర్ణాంకం ) 4 )  /* Serial Peripheral Interface 0 */
#నిర్వచించు AT91C_ID_SPI1           ( ( గుర్తులేని పూర్ణాంకం ) 5 )  /* Serial Peripheral Interface 1 */
#నిర్వచించు AT91C_ID_US0            ( ( గుర్తులేని పూర్ణాంకం ) 6 )  /* USART 0 */
#నిర్వచించు AT91C_ID_US1            ( ( గుర్తులేని పూర్ణాంకం ) 7 )  /* USART 1 */
#నిర్వచించు AT91C_ID_SSC            ( ( గుర్తులేని పూర్ణాంకం ) 8 )  /* Serial Synchronous Controller */
#నిర్వచించు AT91C_ID_TWI            ( ( గుర్తులేని పూర్ణాంకం ) 9 )  /* Two-Wire Interface */
#నిర్వచించు AT91C_ID_PWMC           ( ( గుర్తులేని పూర్ణాంకం ) 10 ) /* PWM Controller */
#నిర్వచించు AT91C_ID_UDP            ( ( గుర్తులేని పూర్ణాంకం ) 11 ) /* USB Device Port */
#నిర్వచించు AT91C_ID_TC0            ( ( గుర్తులేని పూర్ణాంకం ) 12 ) /* Timer Counter 0 */
#నిర్వచించు AT91C_ID_TC1            ( ( గుర్తులేని పూర్ణాంకం ) 13 ) /* Timer Counter 1 */
#నిర్వచించు AT91C_ID_TC2            ( ( గుర్తులేని పూర్ణాంకం ) 14 ) /* Timer Counter 2 */
#నిర్వచించు AT91C_ID_CAN            ( ( గుర్తులేని పూర్ణాంకం ) 15 ) /* Control Area Network Controller */
#నిర్వచించు AT91C_ID_EMAC           ( ( గుర్తులేని పూర్ణాంకం ) 16 ) /* Ethernet MAC */
#నిర్వచించు AT91C_ID_ADC            ( ( గుర్తులేని పూర్ణాంకం ) 17 ) /* Analog-to-Digital Converter */
#నిర్వచించు AT91C_ID_AES            ( ( గుర్తులేని పూర్ణాంకం ) 18 ) /* Advanced Encryption Standard 128-bit */
#నిర్వచించు AT91C_ID_TDES           ( ( గుర్తులేని పూర్ణాంకం ) 19 ) /* Triple Data Encryption Standard */
#నిర్వచించు AT91C_ID_20_Reserved    ( ( గుర్తులేని పూర్ణాంకం ) 20 ) /* Reserved */
#నిర్వచించు AT91C_ID_21_Reserved    ( ( గుర్తులేని పూర్ణాంకం ) 21 ) /* Reserved */
#నిర్వచించు AT91C_ID_22_Reserved    ( ( గుర్తులేని పూర్ణాంకం ) 22 ) /* Reserved */
#నిర్వచించు AT91C_ID_23_Reserved    ( ( గుర్తులేని పూర్ణాంకం ) 23 ) /* Reserved */
#నిర్వచించు AT91C_ID_24_Reserved    ( ( గుర్తులేని పూర్ణాంకం ) 24 ) /* Reserved */
#నిర్వచించు AT91C_ID_25_Reserved    ( ( గుర్తులేని పూర్ణాంకం ) 25 ) /* Reserved */
#నిర్వచించు AT91C_ID_26_Reserved    ( ( గుర్తులేని పూర్ణాంకం ) 26 ) /* Reserved */
#నిర్వచించు AT91C_ID_27_Reserved    ( ( గుర్తులేని పూర్ణాంకం ) 27 ) /* Reserved */
#నిర్వచించు AT91C_ID_28_Reserved    ( ( గుర్తులేని పూర్ణాంకం ) 28 ) /* Reserved */
#నిర్వచించు AT91C_ID_29_Reserved    ( ( గుర్తులేని పూర్ణాంకం ) 29 ) /* Reserved */
#నిర్వచించు AT91C_ID_IRQ0           ( ( గుర్తులేని పూర్ణాంకం ) 30 ) /* Advanced Interrupt Controller (IRQ0) */
#నిర్వచించు AT91C_ID_IRQ1           ( ( గుర్తులేని పూర్ణాంకం ) 31 ) /* Advanced Interrupt Controller (IRQ1) */

/* ***************************************************************************** */
/*               BASE ADDRESS DEFINITIONS FOR AT91SAM7X256 */
/* ***************************************************************************** */
#నిర్వచించు AT91_C_పునాది_SYS         ( ( AT91PS_SYS ) 0xFFFFF000 )     /* (SYS) Base Address */
#నిర్వచించు AT91_C_పునాది_AIC         ( ( AT91PS_AIC ) 0xFFFFF000 )     /* (AIC) Base Address */
#నిర్వచించు AT91_C_పునాది_PDC_DBGU    ( ( AT91PS_PDC ) 0xFFFFF300 )     /* (PDC_DBGU) Base Address */
#నిర్వచించు AT91_C_పునాది_DBGU        ( ( AT91PS_DBGU ) 0xFFFFF200 )    /* (DBGU) Base Address */
#నిర్వచించు AT91_C_పునాది_PIOA        ( ( AT91PS_PIO ) 0xFFFFF400 )     /* (PIOA) Base Address */
#నిర్వచించు AT91_C_పునాది_PIOB        ( ( AT91PS_PIO ) 0xFFFFF600 )     /* (PIOB) Base Address */
#నిర్వచించు AT91_C_పునాది_CKGR        ( ( AT91PS_CKGR ) 0xFFFFFC20 )    /* (CKGR) Base Address */
#నిర్వచించు AT91_C_పునాది_PMC         ( ( AT91PS_PMC ) 0xFFFFFC00 )     /* (PMC) Base Address */
#నిర్వచించు AT91_C_పునాది_RSTC        ( ( AT91PS_RSTC ) 0xFFFFFD00 )    /* (RSTC) Base Address */
#నిర్వచించు AT91_C_పునాది_RTTC        ( ( AT91PS_RTTC ) 0xFFFFFD20 )    /* (RTTC) Base Address */
#నిర్వచించు AT91_C_పునాది_PITC        ( ( AT91PS_PITC ) 0xFFFFFD30 )    /* (PITC) Base Address */
#నిర్వచించు AT91_C_పునాది_WDTC        ( ( AT91PS_WDTC ) 0xFFFFFD40 )    /* (WDTC) Base Address */
#నిర్వచించు AT91_C_పునాది_VREG        ( ( AT91PS_VREG ) 0xFFFFFD60 )    /* (VREG) Base Address */
#నిర్వచించు AT91_C_పునాది_MC          ( ( AT91PS_MC ) 0xFFFFFF00 )      /* (MC) Base Address */
#నిర్వచించు AT91_C_పునాది_PDC_SPI1    ( ( AT91PS_PDC ) 0xFFFE4100 )     /* (PDC_SPI1) Base Address */
#నిర్వచించు AT91_C_పునాది_SPI1        ( ( AT91PS_SPI ) 0xFFFE4000 )     /* (SPI1) Base Address */
#నిర్వచించు AT91_C_పునాది_PDC_SPI0    ( ( AT91PS_PDC ) 0xFFFE0100 )     /* (PDC_SPI0) Base Address */
#నిర్వచించు AT91_C_పునాది_SPI0        ( ( AT91PS_SPI ) 0xFFFE0000 )     /* (SPI0) Base Address */
#నిర్వచించు AT91_C_పునాది_PDC_US1     ( ( AT91PS_PDC ) 0xFFFC4100 )     /* (PDC_US1) Base Address */
#నిర్వచించు AT91_C_పునాది_US1         ( ( AT91PS_USART ) 0xFFFC4000 )   /* (US1) Base Address */
#నిర్వచించు AT91_C_పునాది_PDC_US0     ( ( AT91PS_PDC ) 0xFFFC0100 )     /* (PDC_US0) Base Address */
#నిర్వచించు AT91_C_పునాది_US0         ( ( AT91PS_USART ) 0xFFFC0000 )   /* (US0) Base Address */
#నిర్వచించు AT91_C_పునాది_PDC_SSC     ( ( AT91PS_PDC ) 0xFFFD4100 )     /* (PDC_SSC) Base Address */
#నిర్వచించు AT91_C_పునాది_SSC         ( ( AT91PS_SSC ) 0xFFFD4000 )     /* (SSC) Base Address */
#నిర్వచించు AT91_C_పునాది_TWI         ( ( AT91PS_TWI ) 0xFFFB8000 )     /* (TWI) Base Address */
#నిర్వచించు AT91_C_పునాది_PWMC_CH3    ( ( AT91PS_PWMC_CH ) 0xFFFCC260 ) /* (PWMC_CH3) Base Address */
#నిర్వచించు AT91_C_పునాది_PWMC_CH2    ( ( AT91PS_PWMC_CH ) 0xFFFCC240 ) /* (PWMC_CH2) Base Address */
#నిర్వచించు AT91_C_పునాది_PWMC_CH1    ( ( AT91PS_PWMC_CH ) 0xFFFCC220 ) /* (PWMC_CH1) Base Address */
#నిర్వచించు AT91_C_పునాది_PWMC_CH0    ( ( AT91PS_PWMC_CH ) 0xFFFCC200 ) /* (PWMC_CH0) Base Address */
#నిర్వచించు AT91_C_పునాది_PWMC        ( ( AT91PS_PWMC ) 0xFFFCC000 )    /* (PWMC) Base Address */
#నిర్వచించు AT91_C_పునాది_UDP         ( ( AT91PS_UDP ) 0xFFFB0000 )     /* (UDP) Base Address */
#నిర్వచించు AT91_C_పునాది_TC0         ( ( AT91PS_TC ) 0xFFFA0000 )      /* (TC0) Base Address */
#నిర్వచించు AT91_C_పునాది_TC1         ( ( AT91PS_TC ) 0xFFFA0040 )      /* (TC1) Base Address */
#నిర్వచించు AT91_C_పునాది_TC2         ( ( AT91PS_TC ) 0xFFFA0080 )      /* (TC2) Base Address */
#నిర్వచించు AT91_C_పునాది_TCB         ( ( AT91PS_TCB ) 0xFFFA0000 )     /* (TCB) Base Address */
#నిర్వచించు AT91_C_పునాది_CAN_MB0     ( ( AT91PS_CAN_MB ) 0xFFFD0200 )  /* (CAN_MB0) Base Address */
#నిర్వచించు AT91_C_పునాది_CAN_MB1     ( ( AT91PS_CAN_MB ) 0xFFFD0220 )  /* (CAN_MB1) Base Address */
#నిర్వచించు AT91_C_పునాది_CAN_MB2     ( ( AT91PS_CAN_MB ) 0xFFFD0240 )  /* (CAN_MB2) Base Address */
#నిర్వచించు AT91_C_పునాది_CAN_MB3     ( ( AT91PS_CAN_MB ) 0xFFFD0260 )  /* (CAN_MB3) Base Address */
#నిర్వచించు AT91_C_పునాది_CAN_MB4     ( ( AT91PS_CAN_MB ) 0xFFFD0280 )  /* (CAN_MB4) Base Address */
#నిర్వచించు AT91_C_పునాది_CAN_MB5     ( ( AT91PS_CAN_MB ) 0xFFFD02A0 )  /* (CAN_MB5) Base Address */
#నిర్వచించు AT91_C_పునాది_CAN_MB6     ( ( AT91PS_CAN_MB ) 0xFFFD02C0 )  /* (CAN_MB6) Base Address */
#నిర్వచించు AT91_C_పునాది_CAN_MB7     ( ( AT91PS_CAN_MB ) 0xFFFD02E0 )  /* (CAN_MB7) Base Address */
#నిర్వచించు AT91_C_పునాది_CAN         ( ( AT91PS_CAN ) 0xFFFD0000 )     /* (CAN) Base Address */
#నిర్వచించు AT91_C_పునాది_EMAC        ( ( AT91PS_EMAC ) 0xFFFDC000 )    /* (EMAC) Base Address */
#నిర్వచించు AT91_C_పునాది_PDC_ADC     ( ( AT91PS_PDC ) 0xFFFD8100 )     /* (PDC_ADC) Base Address */
#నిర్వచించు AT91_C_పునాది_ADC         ( ( AT91PS_ADC ) 0xFFFD8000 )     /* (ADC) Base Address */
#నిర్వచించు AT91_C_పునాది_PDC_AES     ( ( AT91PS_PDC ) 0xFFFA4100 )     /* (PDC_AES) Base Address */
#నిర్వచించు AT91_C_పునాది_AES         ( ( AT91PS_AES ) 0xFFFA4000 )     /* (AES) Base Address */
#నిర్వచించు AT91_C_పునాది_PDC_TDES    ( ( AT91PS_PDC ) 0xFFFA8100 )     /* (PDC_TDES) Base Address */
#నిర్వచించు AT91_C_పునాది_TDES        ( ( AT91PS_TDES ) 0xFFFA8000 )    /* (TDES) Base Address */

/* ***************************************************************************** */
/*               MEMORY MAPPING DEFINITIONS FOR AT91SAM7X256 */
/* ***************************************************************************** */
#నిర్వచించు AT91C_ISRAM          ( ( అక్షరం * ) 0x00200000 )       /* Internal SRAM base address */
#నిర్వచించు AT91_C_ISRAM_కొలత     ( ( గుర్తులేని పూర్ణాంకం ) 0x00010000 ) /* Internal SRAM size in byte (64 Kbyte) */
#నిర్వచించు AT91C_IFLASH         ( ( అక్షరం * ) 0x00100000 )       /* Internal ROM base address */
#నిర్వచించు AT91_C_IFLASH_కొలత    ( ( గుర్తులేని పూర్ణాంకం ) 0x00040000 ) /* Internal ROM size in byte (256 Kbyte) */



/* - Hardware register definition */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR System Peripherals */
/* - ***************************************************************************** */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Advanced Interrupt Controller */
/* - ***************************************************************************** */
/* - -------- AIC_SMR : (AIC Offset: 0x0) Control Register -------- */
#ఒకవేళ 0 /*_RB_*/
    AT91_C_AIC_పూర్వ EQU( 0x7 << 0 );
    -( AIC ) ప్రాధాన్యత_2 Level
    AT91_C_AIC_పూర్వ_అత్యల్ప EQU( 0x0 );
    -( AIC ) అత్యల్ప ప్రాధాన్యత level
    AT91_C_AIC_పూర్వ_HIGHEST EQU( 0x7 );
    -( AIC ) Highest ప్రాధాన్యత level
    AT91C_AIC_SRCTYPE EQU( 0x3 << 5 );
    -( AIC ) అంతరాయం_2 ఆధారం_2 Type
    AT91_C_AIC_SRCTYPE_INT_ఎగువ_LEVEL EQU( 0x0 << 5 );
    -( AIC ) అంతర్గత Sources సంకేతం_3 Label ఎగువ - level Sensitive
    AT91_C_AIC_SRCTYPE_EXT_దిగువ_LEVEL EQU( 0x0 << 5 );
    -( AIC ) External Sources సంకేతం_3 Label దిగువ - level Sensitive
    AT91_C_AIC_SRCTYPE_INT_ధనాత్మక_అంచు EQU( 0x1 << 5 );
    -( AIC ) అంతర్గత Sources సంకేతం_3 Label ధనాత్మక అంచు triggered
    AT91_C_AIC_SRCTYPE_EXT_NEGATIVE_అంచు EQU( 0x1 << 5 );
    -( AIC ) External Sources సంకేతం_3 Label Negative అంచు triggered
    AT91_C_AIC_SRCTYPE_ఎగువ_LEVEL EQU( 0x2 << 5 );
    -( AIC ) అంతర్గత Or External Sources సంకేతం_3 Label ఎగువ - level Sensitive
    AT91_C_AIC_SRCTYPE_ధనాత్మక_అంచు EQU( 0x3 << 5 );
    -( AIC ) అంతర్గత Or External Sources సంకేతం_3 Label ధనాత్మక అంచు triggered
/* - -------- AIC_CISR : (AIC Offset: 0x114) AIC Core Interrupt Status Register -------- */
    AT91C_AIC_NFIQ EQU( 0x1 << 0 );
    -( AIC ) NFIQ స్థితి_2
    AT91C_AIC_NIRQ EQU( 0x1 << 1 );
    -( AIC ) NIRQ స్థితి_2
/* - -------- AIC_DCR : (AIC Offset: 0x138) AIC Debug Control Register (Protect) -------- */
    AT91C_AIC_DCR_PROT EQU( 0x1 << 0 );
    -( AIC ) Protection బహుళకం
    AT91C_AIC_DCR_GMSK EQU( 0x1 << 1 );
    -( AIC ) General ముసుగు_2
#అయితే_ముగింపు /* if 0 */
/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Peripheral DMA Controller */
/* - ***************************************************************************** */
/* - -------- PDC_PTCR : (PDC Offset: 0x20) PDC Transfer Control Register -------- */
AT91C_PDC_RXTEN EQU( 0x1 << 0 );
-( PDC ) Receiver Transfer Enable
AT91C_PDC_RXTDIS EQU( 0x1 << 1 );
-( PDC ) Receiver Transfer Disable
AT91C_PDC_TXTEN EQU( 0x1 << 8 );
-( PDC ) Transmitter Transfer Enable
AT91C_PDC_TXTDIS EQU( 0x1 << 9 );
-( PDC ) Transmitter Transfer Disable
/* - -------- PDC_PTSR : (PDC Offset: 0x24) PDC Transfer Status Register -------- */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Debug Unit */
/* - ***************************************************************************** */
/* - -------- DBGU_CR : (DBGU Offset: 0x0) Debug Unit Control Register -------- */
AT91C_US_RSTRX EQU( 0x1 << 2 );
-( DBGU ) Reset Receiver
AT91C_US_RSTTX EQU( 0x1 << 3 );
-( DBGU ) Reset Transmitter
AT91C_US_RXEN EQU( 0x1 << 4 );
-( DBGU ) Receiver Enable
AT91C_US_RXDIS EQU( 0x1 << 5 );
-( DBGU ) Receiver Disable
AT91C_US_TXEN EQU( 0x1 << 6 );
-( DBGU ) Transmitter Enable
AT91C_US_TXDIS EQU( 0x1 << 7 );
-( DBGU ) Transmitter Disable
AT91C_US_RSTSTA EQU( 0x1 << 8 );
-( DBGU ) Reset స్థితి_2 బిట్లు
/* - -------- DBGU_MR : (DBGU Offset: 0x4) Debug Unit Mode Register -------- */
AT91C_US_PAR EQU( 0x7 << 9 );
-( DBGU ) Parity type
AT91C_US_PAR_EVEN EQU( 0x0 << 9 );
-( DBGU ) Even Parity
AT91C_US_PAR_ODD EQU( 0x1 << 9 );
-( DBGU ) Odd Parity
AT91C_US_PAR_SPACE EQU( 0x2 << 9 );
-( DBGU ) Parity forced గమ్యం 0 ( Space )
AT91C_US_PAR_MARK EQU( 0x3 << 9 );
-( DBGU ) Parity forced గమ్యం 1 ( Mark )
AT91C_US_PAR_NONE EQU( 0x4 << 9 );
-( DBGU ) No Parity
AT91C_US_PAR_MULTI_DROP EQU( 0x6 << 9 );
-( DBGU ) Multi - drop బహుళకం_2
AT91C_US_CHMODE EQU( 0x3 << 14 );
-( DBGU ) Channel బహుళకం
AT91_C_US_CHMODE_సాధారణ EQU( 0x0 << 14 );
-( DBGU ) సాధారణ బహుళకం: The USART channel operates as an RX / TX USART.
   AT91C_US_CHMODE_AUTO EQU( 0x1 << 14 );
-( DBGU ) Automatic Echo: Receiver దత్తాంశం ఆదానం is connected గమ్యం the TXD pin.
   AT91C_US_CHMODE_LOCAL EQU( 0x2 << 14 );
-( DBGU ) Local Loopback: Transmitter Output Signal is connected గమ్యం Receiver ఆదానం Signal.
   AT91C_US_CHMODE_REMOTE EQU( 0x3 << 14 );
-( DBGU ) Remote Loopback: RXD pin is internally connected గమ్యం TXD pin.
/* - -------- DBGU_IER : (DBGU Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
   AT91C_US_RXRDY EQU( 0x1 << 0 );
-( DBGU ) RXRDY అంతరాయం_2
AT91C_US_TXRDY EQU( 0x1 << 1 );
-( DBGU ) TXRDY అంతరాయం_2
AT91C_US_ENDRX EQU( 0x1 << 3 );
-( DBGU ) చివర_2 యొక్క Receive Transfer అంతరాయం_2
AT91C_US_ENDTX EQU( 0x1 << 4 );
-( DBGU ) చివర_2 యొక్క Transmit అంతరాయం_2
AT91C_US_OVRE EQU( 0x1 << 5 );
-( DBGU ) Overrun అంతరాయం_2
AT91_C_US_చట్రం EQU( 0x1 << 6 );
-( DBGU ) Framing Error అంతరాయం_2
AT91C_US_PARE EQU( 0x1 << 7 );
-( DBGU ) Parity Error అంతరాయం_2
AT91C_US_TXEMPTY EQU( 0x1 << 9 );
-( DBGU ) TXEMPTY అంతరాయం_2
AT91C_US_TXBUFE EQU( 0x1 << 11 );
-( DBGU ) TXBUFE అంతరాయం_2
AT91C_US_RXBUFF EQU( 0x1 << 12 );
-( DBGU ) RXBUFF అంతరాయం_2
AT91C_US_COMM_TX EQU( 0x1 << 30 );
-( DBGU ) COMM_TX అంతరాయం_2
AT91C_US_COMM_RX EQU( 0x1 << 31 );
-( DBGU ) COMM_RX అంతరాయం_2
/* - -------- DBGU_IDR : (DBGU Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* - -------- DBGU_IMR : (DBGU Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* - -------- DBGU_CSR : (DBGU Offset: 0x14) Debug Unit Channel Status Register -------- */
/* - -------- DBGU_FNTR : (DBGU Offset: 0x48) Debug Unit FORCE_NTRST Register -------- */
AT91C_US_FORCE_NTRST EQU( 0x1 << 0 );
-( DBGU ) Force NTRST లోపల JTAG

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Parallel Input Output Controller */
/* - ***************************************************************************** */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Clock Generator Controller */
/* - ***************************************************************************** */
/* - -------- CKGR_MOR : (CKGR Offset: 0x0) Main Oscillator Register -------- */
AT91C_CKGR_MOSCEN EQU( 0x1 << 0 );
-( CKGR ) Main Oscillator Enable
AT91C_CKGR_OSCBYPASS EQU( 0x1 << 1 );
-( CKGR ) Main Oscillator Bypass
AT91C_CKGR_OSCOUNT EQU( 0xFF << 8 );
-( CKGR ) Main Oscillator ప్రారంభం_2 - పైకి సమయం
/* - -------- CKGR_MCFR : (CKGR Offset: 0x4) Main Clock Frequency Register -------- */
AT91C_CKGR_MAINF EQU( 0xFFFF << 0 );
-( CKGR ) Main Clock Frequency
AT91C_CKGR_MAINRDY EQU( 0x1 << 16 );
-( CKGR ) Main Clock Ready
/* - -------- CKGR_PLLR : (CKGR Offset: 0xc) PLL B Register -------- */
AT91C_CKGR_DIV EQU( 0xFF << 0 );
-( CKGR ) Divider Selected
AT91C_CKGR_DIV_0 EQU( 0x0 );
-( CKGR ) Divider output is 0
AT91C_CKGR_DIV_BYPASS EQU( 0x1 );
-( CKGR ) Divider is bypassed
AT91C_CKGR_PLLCOUNT EQU( 0x3F << 8 );
-( CKGR ) PLL Counter
AT91_C_CKGR_బహిర్గతం EQU( 0x3 << 14 );
-( CKGR ) PLL Output Frequency Range
AT91_C_CKGR_బహిర్గతం_0 EQU( 0x0 << 14 );
-( CKGR ) Please refer గమ్యం the PLL datasheet
AT91_C_CKGR_బహిర్గతం_1 EQU( 0x1 << 14 );
-( CKGR ) Please refer గమ్యం the PLL datasheet
AT91_C_CKGR_బహిర్గతం_2 EQU( 0x2 << 14 );
-( CKGR ) Please refer గమ్యం the PLL datasheet
AT91_C_CKGR_బహిర్గతం_3 EQU( 0x3 << 14 );
-( CKGR ) Please refer గమ్యం the PLL datasheet
AT91C_CKGR_MUL EQU( 0x7FF << 16 );
-( CKGR ) PLL Multiplier
AT91C_CKGR_USBDIV EQU( 0x3 << 28 );
-( CKGR ) Divider

కొరకు USB Clocks
AT91C_CKGR_USBDIV_0 EQU( 0x0 << 28 );
-( CKGR ) Divider output is PLL clock output
AT91C_CKGR_USBDIV_1 EQU( 0x1 << 28 );
-( CKGR ) Divider output is PLL clock output divided by 2
AT91C_CKGR_USBDIV_2 EQU( 0x2 << 28 );
-( CKGR ) Divider output is PLL clock output divided by 4

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Power Management Controller */
/* - ***************************************************************************** */
/* - -------- PMC_SCER : (PMC Offset: 0x0) System Clock Enable Register -------- */
AT91C_PMC_PCK EQU( 0x1 << 0 );
-( PMC ) Processor Clock
AT91C_PMC_UDP EQU( 0x1 << 7 );
-( PMC ) USB Device పోర్టు_2 Clock
AT91C_PMC_PCK0 EQU( 0x1 << 8 );
-( PMC ) Programmable Clock Output
AT91C_PMC_PCK1 EQU( 0x1 << 9 );
-( PMC ) Programmable Clock Output
AT91C_PMC_PCK2 EQU( 0x1 << 10 );
-( PMC ) Programmable Clock Output
AT91C_PMC_PCK3 EQU( 0x1 << 11 );
-( PMC ) Programmable Clock Output
/* - -------- PMC_SCDR : (PMC Offset: 0x4) System Clock Disable Register -------- */
/* - -------- PMC_SCSR : (PMC Offset: 0x8) System Clock Status Register -------- */
/* - -------- CKGR_MOR : (PMC Offset: 0x20) Main Oscillator Register -------- */
/* - -------- CKGR_MCFR : (PMC Offset: 0x24) Main Clock Frequency Register -------- */
/* - -------- CKGR_PLLR : (PMC Offset: 0x2c) PLL B Register -------- */
/* - -------- PMC_MCKR : (PMC Offset: 0x30) Master Clock Register -------- */
AT91C_PMC_CSS EQU( 0x3 << 0 );
-( PMC ) Programmable Clock Selection
AT91C_PMC_CSS_SLOW_CLK EQU( 0x0 );
-( PMC ) Slow Clock is selected
AT91C_PMC_CSS_MAIN_CLK EQU( 0x1 );
-( PMC ) Main Clock is selected
AT91C_PMC_CSS_PLL_CLK EQU( 0x3 );
-( PMC ) Clock from PLL is selected
AT91C_PMC_PRES EQU( 0x7 << 2 );
-( PMC ) Programmable Clock Prescaler
AT91C_PMC_PRES_CLK EQU( 0x0 << 2 );
-( PMC ) Selected clock
AT91C_PMC_PRES_CLK_2 EQU( 0x1 << 2 );
-( PMC ) Selected clock divided by 2
AT91C_PMC_PRES_CLK_4 EQU( 0x2 << 2 );
-( PMC ) Selected clock divided by 4
AT91C_PMC_PRES_CLK_8 EQU( 0x3 << 2 );
-( PMC ) Selected clock divided by 8
AT91C_PMC_PRES_CLK_16 EQU( 0x4 << 2 );
-( PMC ) Selected clock divided by 16
AT91C_PMC_PRES_CLK_32 EQU( 0x5 << 2 );
-( PMC ) Selected clock divided by 32
AT91C_PMC_PRES_CLK_64 EQU( 0x6 << 2 );
-( PMC ) Selected clock divided by 64
/* - -------- PMC_PCKR : (PMC Offset: 0x40) Programmable Clock Register -------- */
/* - -------- PMC_IER : (PMC Offset: 0x60) PMC Interrupt Enable Register -------- */
AT91C_PMC_MOSCS EQU( 0x1 << 0 );
-( PMC ) MOSC స్థితి_2 / Enable / Disable / ముసుగు_2
AT91_C_PMC_తాళం EQU( 0x1 << 2 );
-( PMC ) PLL స్థితి_2 / Enable / Disable / ముసుగు_2
AT91C_PMC_MCKRDY EQU( 0x1 << 3 );
-( PMC ) MCK_RDY స్థితి_2 / Enable / Disable / ముసుగు_2
AT91C_PMC_PCK0RDY EQU( 0x1 << 8 );
-( PMC ) PCK0_RDY స్థితి_2 / Enable / Disable / ముసుగు_2
AT91C_PMC_PCK1RDY EQU( 0x1 << 9 );
-( PMC ) PCK1_RDY స్థితి_2 / Enable / Disable / ముసుగు_2
AT91C_PMC_PCK2RDY EQU( 0x1 << 10 );
-( PMC ) PCK2_RDY స్థితి_2 / Enable / Disable / ముసుగు_2
AT91C_PMC_PCK3RDY EQU( 0x1 << 11 );
-( PMC ) PCK3_RDY స్థితి_2 / Enable / Disable / ముసుగు_2
/* - -------- PMC_IDR : (PMC Offset: 0x64) PMC Interrupt Disable Register -------- */
/* - -------- PMC_SR : (PMC Offset: 0x68) PMC Status Register -------- */
/* - -------- PMC_IMR : (PMC Offset: 0x6c) PMC Interrupt Mask Register -------- */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Reset Controller Interface */
/* - ***************************************************************************** */
/* - -------- RSTC_RCR : (RSTC Offset: 0x0) Reset Control Register -------- */
AT91C_RSTC_PROCRST EQU( 0x1 << 0 );
-( RSTC ) Processor Reset
AT91C_RSTC_PERRST EQU( 0x1 << 2 );
-( RSTC ) Peripheral Reset
AT91C_RSTC_EXTRST EQU( 0x1 << 3 );
-( RSTC ) External Reset
AT91_C_RSTC_కీలకం EQU( 0xFF << 24 );
-( RSTC ) Password
/* - -------- RSTC_RSR : (RSTC Offset: 0x4) Reset Status Register -------- */
AT91C_RSTC_URSTS EQU( 0x1 << 0 );
-( RSTC ) User Reset స్థితి_2
AT91C_RSTC_BODSTS EQU( 0x1 << 1 );
-( RSTC ) Brownout Detection స్థితి_2
AT91C_RSTC_RSTTYP EQU( 0x7 << 8 );
-( RSTC ) Reset Type
AT91C_RSTC_RSTTYP_POWERUP EQU( 0x0 << 8 );
-( RSTC ) Power - పైకి Reset.VDDCORE rising.
   AT91C_RSTC_RSTTYP_WAKEUP EQU( 0x1 << 8 );
-( RSTC ) Wake_పైకి Reset.VDDCORE rising.
   AT91C_RSTC_RSTTYP_WATCHDOG EQU( 0x2 << 8 );
-( RSTC ) Watchdog Reset.Watchdog అధికప్రవాహం occurred.
   AT91C_RSTC_RSTTYP_SOFTWARE EQU( 0x3 << 8 );
-( RSTC ) Software Reset.Processor reset required by the software.
   AT91C_RSTC_RSTTYP_USER EQU( 0x4 << 8 );
-( RSTC ) User Reset.NRST pin detected దిగువ_2.
   AT91C_RSTC_RSTTYP_BROWNOUT EQU( 0x5 << 8 );
-( RSTC ) Brownout Reset occurred.
   AT91C_RSTC_NRSTL EQU( 0x1 << 16 );
-( RSTC ) NRST pin level
AT91C_RSTC_SRCMP EQU( 0x1 << 17 );
-( RSTC ) Software Reset Command లోపల పురోగతి.
/* - -------- RSTC_RMR : (RSTC Offset: 0x8) Reset Mode Register -------- */
   AT91C_RSTC_URSTEN EQU( 0x1 << 0 );
-( RSTC ) User Reset Enable
AT91C_RSTC_URSTIEN EQU( 0x1 << 4 );
-( RSTC ) User Reset అంతరాయం_2 Enable
AT91C_RSTC_ERSTL EQU( 0xF << 8 );
-( RSTC ) User Reset Enable
AT91C_RSTC_BODIEN EQU( 0x1 << 16 );
-( RSTC ) Brownout Detection అంతరాయం_2 Enable

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Real Time Timer Controller Interface */
/* - ***************************************************************************** */
/* - -------- RTTC_RTMR : (RTTC Offset: 0x0) Real-time Mode Register -------- */
AT91C_RTTC_RTPRES EQU( 0xFFFF << 0 );
-( RTTC ) Real - time Timer Prescaler విలువ_2
AT91C_RTTC_ALMIEN EQU( 0x1 << 16 );
-( RTTC ) Alarm అంతరాయం_2 Enable
AT91C_RTTC_RTTINCIEN EQU( 0x1 << 17 );
-( RTTC ) Real సమయం Timer Increment అంతరాయం_2 Enable
AT91C_RTTC_RTTRST EQU( 0x1 << 18 );
-( RTTC ) Real సమయం Timer Restart
/* - -------- RTTC_RTAR : (RTTC Offset: 0x4) Real-time Alarm Register -------- */
AT91C_RTTC_ALMV EQU( 0x0 << 0 );
-( RTTC ) Alarm విలువ_2
/* - -------- RTTC_RTVR : (RTTC Offset: 0x8) Current Real-time Value Register -------- */
AT91C_RTTC_CRTV EQU( 0x0 << 0 );
-( RTTC ) Current Real - time విలువ_2
/* - -------- RTTC_RTSR : (RTTC Offset: 0xc) Real-time Status Register -------- */
AT91C_RTTC_ALMS EQU( 0x1 << 0 );
-( RTTC ) Real - time Alarm స్థితి_2
AT91C_RTTC_RTTINC EQU( 0x1 << 1 );
-( RTTC ) Real - time Timer Increment

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Periodic Interval Timer Controller Interface */
/* - ***************************************************************************** */
/* - -------- PITC_PIMR : (PITC Offset: 0x0) Periodic Interval Mode Register -------- */
AT91C_PITC_PIV EQU( 0xFFFFF << 0 );
-( PITC ) Periodic Interval విలువ_2
AT91C_PITC_PITEN EQU( 0x1 << 24 );
-( PITC ) Periodic Interval Timer Enabled
AT91C_PITC_PITIEN EQU( 0x1 << 25 );
-( PITC ) Periodic Interval Timer అంతరాయం_2 Enable
/* - -------- PITC_PISR : (PITC Offset: 0x4) Periodic Interval Status Register -------- */
AT91C_PITC_PITS EQU( 0x1 << 0 );
-( PITC ) Periodic Interval Timer స్థితి_2
/* - -------- PITC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register -------- */
AT91C_PITC_CPIV EQU( 0xFFFFF << 0 );
-( PITC ) Current Periodic Interval విలువ_2
AT91C_PITC_PICNT EQU( 0xFFF << 20 );
-( PITC ) Periodic Interval Counter
/* - -------- PITC_PIIR : (PITC Offset: 0xc) Periodic Interval Image Register -------- */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Watchdog Timer Controller Interface */
/* - ***************************************************************************** */
/* - -------- WDTC_WDCR : (WDTC Offset: 0x0) Periodic Interval Image Register -------- */
AT91C_WDTC_WDRSTT EQU( 0x1 << 0 );
-( WDTC ) Watchdog Restart
AT91_C_WDTC_కీలకం EQU( 0xFF << 24 );
-( WDTC ) Watchdog కీలకం Password
/* - -------- WDTC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register -------- */
AT91C_WDTC_WDV EQU( 0xFFF << 0 );
-( WDTC ) Watchdog Timer Restart
AT91C_WDTC_WDFIEN EQU( 0x1 << 12 );
-( WDTC ) Watchdog Fault అంతరాయం_2 Enable
AT91C_WDTC_WDRSTEN EQU( 0x1 << 13 );
-( WDTC ) Watchdog Reset Enable
AT91C_WDTC_WDRPROC EQU( 0x1 << 14 );
-( WDTC ) Watchdog Timer Restart
AT91C_WDTC_WDDIS EQU( 0x1 << 15 );
-( WDTC ) Watchdog Disable
AT91C_WDTC_WDD EQU( 0xFFF << 16 );
-( WDTC ) Watchdog Delta విలువ_2
AT91C_WDTC_WDDBGHLT EQU( 0x1 << 28 );
-( WDTC ) Watchdog Debug Halt
AT91C_WDTC_WDIDLEHLT EQU( 0x1 << 29 );
-( WDTC ) Watchdog Idle Halt
/* - -------- WDTC_WDSR : (WDTC Offset: 0x8) Watchdog Status Register -------- */
AT91C_WDTC_WDUNF EQU( 0x1 << 0 );
-( WDTC ) Watchdog Underflow
AT91C_WDTC_WDERR EQU( 0x1 << 1 );
-( WDTC ) Watchdog Error

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Voltage Regulator Mode Controller Interface */
/* - ***************************************************************************** */
/* - -------- VREG_MR : (VREG Offset: 0x0) Voltage Regulator Mode Register -------- */
AT91C_VREG_PSTDBY EQU( 0x1 << 0 );
-( VREG ) Voltage Regulator Power Standby బహుళకం

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Memory Controller Interface */
/* - ***************************************************************************** */
/* - -------- MC_RCR : (MC Offset: 0x0) MC Remap Control Register -------- */
AT91C_MC_RCB EQU( 0x1 << 0 );
-( MC ) Remap Command బిట్టు
/* - -------- MC_ASR : (MC Offset: 0x4) MC Abort Status Register -------- */
AT91C_MC_UNDADD EQU( 0x1 << 0 );
-( MC ) Undefined చిరునామా Abort స్థితి_2
AT91C_MC_MISADD EQU( 0x1 << 1 );
-( MC ) Misaligned చిరునామా Abort స్థితి_2
AT91C_MC_ABTSZ EQU( 0x3 << 8 );
-( MC ) Abort కొలత_2 స్థితి_2
AT91C_MC_ABTSZ_BYTE EQU( 0x0 << 8 );
-( MC ) Byte
AT91C_MC_ABTSZ_HWORD EQU( 0x1 << 8 );
-( MC ) Half - మాట
AT91_C_MC_ABTSZ_మాట EQU( 0x2 << 8 );
-( MC ) మాట_2
AT91C_MC_ABTTYP EQU( 0x3 << 10 );
-( MC ) Abort Type స్థితి_2
AT91C_MC_ABTTYP_DATAR EQU( 0x0 << 10 );
-( MC ) దత్తాంశం Read
AT91C_MC_ABTTYP_DATAW EQU( 0x1 << 10 );
-( MC ) దత్తాంశం Write
AT91C_MC_ABTTYP_FETCH EQU( 0x2 << 10 );
-( MC ) సంకేతం_3 Fetch
AT91C_MC_MST0 EQU( 0x1 << 16 );
-( MC ) Master 0 Abort ఆధారం_2
AT91C_MC_MST1 EQU( 0x1 << 17 );
-( MC ) Master 1 Abort ఆధారం_2
AT91C_MC_SVMST0 EQU( 0x1 << 24 );
-( MC ) Saved Master 0 Abort ఆధారం_2
AT91C_MC_SVMST1 EQU( 0x1 << 25 );
-( MC ) Saved Master 1 Abort ఆధారం_2
/* - -------- MC_FMR : (MC Offset: 0x60) MC Flash Mode Register -------- */
AT91C_MC_FRDY EQU( 0x1 << 0 );
-( MC ) Flash Ready
AT91C_MC_LOCKE EQU( 0x1 << 2 );
-( MC ) తాళం_2 Error
AT91C_MC_PROGE EQU( 0x1 << 3 );
-( MC ) Programming Error
AT91C_MC_NEBP EQU( 0x1 << 7 );
-( MC ) No Erase Before Programming
AT91C_MC_FWS EQU( 0x3 << 8 );
-( MC ) Flash Wait State
AT91C_MC_FWS_0FWS EQU( 0x0 << 8 );
-( MC ) 1 చక్రం

కొరకు Read, 2

కొరకు Write operations
AT91C_MC_FWS_1FWS EQU( 0x1 << 8 );
-( MC ) 2 చక్రాలు

కొరకు Read, 3

కొరకు Write operations
AT91C_MC_FWS_2FWS EQU( 0x2 << 8 );
-( MC ) 3 చక్రాలు

కొరకు Read, 4

కొరకు Write operations
AT91C_MC_FWS_3FWS EQU( 0x3 << 8 );
-( MC ) 4 చక్రాలు

కొరకు Read, 4

కొరకు Write operations
AT91C_MC_FMCN EQU( 0xFF << 16 );
-( MC ) Flash Microsecond చక్రం_2 సంఖ్య_2
/* - -------- MC_FCR : (MC Offset: 0x64) MC Flash Command Register -------- */
AT91C_MC_FCMD EQU( 0xF << 0 );
-( MC ) Flash Command
AT91_C_MC_FCMD_ప్రారంభం_PROG EQU( 0x1 );
-( MC ) Starts the programming యొక్క th epage specified by PAGEN.
   AT91_C_MC_FCMD_తాళం EQU( 0x2 );
-( MC ) Starts a తాళం_3 sequence యొక్క the sector defined by the బిట్లు_2 4 గమ్యం 7 యొక్క the క్షేత్రం PAGEN.
   AT91_C_MC_FCMD_PROG_AND_తాళం EQU( 0x3 );
-( MC ) The తాళం_3 sequence automatically happens after the programming sequence is completed.
   AT91C_MC_FCMD_UNLOCK EQU( 0x4 );
-( MC ) Starts an unlock sequence యొక్క the sector defined by the బిట్లు_2 4 గమ్యం 7 యొక్క the క్షేత్రం PAGEN.
   AT91C_MC_FCMD_ERASE_ALL EQU( 0x8 );
-( MC ) Starts the erase యొక్క the entire flash.If at కనిష్ఠ a పుట is locked, the command is cancelled.
   AT91_C_MC_FCMD_సమితి_GP_NVM EQU( 0xB );
-( MC ) సమితి_2 General Purpose NVM బిట్లు_2.
   AT91C_MC_FCMD_CLR_GP_NVM EQU( 0xD );
-( MC ) Clear General Purpose NVM బిట్లు_2.
   AT91_C_MC_FCMD_సమితి_SECURITY EQU( 0xF );
-( MC ) సమితి_2 Security బిట్టు.
   AT91C_MC_PAGEN EQU( 0x3FF << 8 );
-( MC ) పుట_2 సంఖ్య_2
AT91_C_MC_కీలకం EQU( 0xFF << 24 );
-( MC ) Writing Protect కీలకం_2
/* - -------- MC_FSR : (MC Offset: 0x68) MC Flash Command Register -------- */
AT91C_MC_SECURITY EQU( 0x1 << 4 );
-( MC ) Security బిట్టు స్థితి_2
AT91C_MC_GPNVM0 EQU( 0x1 << 8 );
-( MC ) Sector 0 తాళం_2 స్థితి_2
AT91C_MC_GPNVM1 EQU( 0x1 << 9 );
-( MC ) Sector 1 తాళం_2 స్థితి_2
AT91C_MC_GPNVM2 EQU( 0x1 << 10 );
-( MC ) Sector 2 తాళం_2 స్థితి_2
AT91C_MC_GPNVM3 EQU( 0x1 << 11 );
-( MC ) Sector 3 తాళం_2 స్థితి_2
AT91C_MC_GPNVM4 EQU( 0x1 << 12 );
-( MC ) Sector 4 తాళం_2 స్థితి_2
AT91C_MC_GPNVM5 EQU( 0x1 << 13 );
-( MC ) Sector 5 తాళం_2 స్థితి_2
AT91C_MC_GPNVM6 EQU( 0x1 << 14 );
-( MC ) Sector 6 తాళం_2 స్థితి_2
AT91C_MC_GPNVM7 EQU( 0x1 << 15 );
-( MC ) Sector 7 తాళం_2 స్థితి_2
AT91C_MC_LOCKS0 EQU( 0x1 << 16 );
-( MC ) Sector 0 తాళం_2 స్థితి_2
AT91C_MC_LOCKS1 EQU( 0x1 << 17 );
-( MC ) Sector 1 తాళం_2 స్థితి_2
AT91C_MC_LOCKS2 EQU( 0x1 << 18 );
-( MC ) Sector 2 తాళం_2 స్థితి_2
AT91C_MC_LOCKS3 EQU( 0x1 << 19 );
-( MC ) Sector 3 తాళం_2 స్థితి_2
AT91C_MC_LOCKS4 EQU( 0x1 << 20 );
-( MC ) Sector 4 తాళం_2 స్థితి_2
AT91C_MC_LOCKS5 EQU( 0x1 << 21 );
-( MC ) Sector 5 తాళం_2 స్థితి_2
AT91C_MC_LOCKS6 EQU( 0x1 << 22 );
-( MC ) Sector 6 తాళం_2 స్థితి_2
AT91C_MC_LOCKS7 EQU( 0x1 << 23 );
-( MC ) Sector 7 తాళం_2 స్థితి_2
AT91C_MC_LOCKS8 EQU( 0x1 << 24 );
-( MC ) Sector 8 తాళం_2 స్థితి_2
AT91C_MC_LOCKS9 EQU( 0x1 << 25 );
-( MC ) Sector 9 తాళం_2 స్థితి_2
AT91C_MC_LOCKS10 EQU( 0x1 << 26 );
-( MC ) Sector 10 తాళం_2 స్థితి_2
AT91C_MC_LOCKS11 EQU( 0x1 << 27 );
-( MC ) Sector 11 తాళం_2 స్థితి_2
AT91C_MC_LOCKS12 EQU( 0x1 << 28 );
-( MC ) Sector 12 తాళం_2 స్థితి_2
AT91C_MC_LOCKS13 EQU( 0x1 << 29 );
-( MC ) Sector 13 తాళం_2 స్థితి_2
AT91C_MC_LOCKS14 EQU( 0x1 << 30 );
-( MC ) Sector 14 తాళం_2 స్థితి_2
AT91C_MC_LOCKS15 EQU( 0x1 << 31 );
-( MC ) Sector 15 తాళం_2 స్థితి_2

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Serial Parallel Interface */
/* - ***************************************************************************** */
/* - -------- SPI_CR : (SPI Offset: 0x0) SPI Control Register -------- */
AT91C_SPI_SPIEN EQU( 0x1 << 0 );
-( SPI ) SPI Enable
AT91C_SPI_SPIDIS EQU( 0x1 << 1 );
-( SPI ) SPI Disable
AT91C_SPI_SWRST EQU( 0x1 << 7 );
-( SPI ) SPI Software reset
AT91C_SPI_LASTXFER EQU( 0x1 << 24 );
-( SPI ) SPI చివరి Transfer
/* - -------- SPI_MR : (SPI Offset: 0x4) SPI Mode Register -------- */
AT91C_SPI_MSTR EQU( 0x1 << 0 );
-( SPI ) Master / Slave బహుళకం
AT91C_SPI_PS EQU( 0x1 << 1 );
-( SPI ) Peripheral Select
AT91C_SPI_PS_FIXED EQU( 0x0 << 1 );
-( SPI ) Fixed Peripheral Select
AT91C_SPI_PS_VARIABLE EQU( 0x1 << 1 );
-( SPI ) Variable Peripheral Select
AT91C_SPI_PCSDEC EQU( 0x1 << 2 );
-( SPI ) Chip Select Decode
AT91C_SPI_FDIV EQU( 0x1 << 3 );
-( SPI ) Clock Selection
AT91C_SPI_MODFDIS EQU( 0x1 << 4 );
-( SPI ) బహుళకం Fault Detection
AT91C_SPI_LLB EQU( 0x1 << 7 );
-( SPI ) Clock Selection
AT91C_SPI_PCS EQU( 0xF << 16 );
-( SPI ) Peripheral Chip Select
AT91C_SPI_DLYBCS EQU( 0xFF << 24 );
-( SPI ) Delay Between Chip Selects
/* - -------- SPI_RDR : (SPI Offset: 0x8) Receive Data Register -------- */
AT91C_SPI_RD EQU( 0xFFFF << 0 );
-( SPI ) Receive దత్తాంశం
AT91C_SPI_RPCS EQU( 0xF << 16 );
-( SPI ) Peripheral Chip Select స్థితి_2
/* - -------- SPI_TDR : (SPI Offset: 0xc) Transmit Data Register -------- */
AT91C_SPI_TD EQU( 0xFFFF << 0 );
-( SPI ) Transmit దత్తాంశం
AT91C_SPI_TPCS EQU( 0xF << 16 );
-( SPI ) Peripheral Chip Select స్థితి_2
/* - -------- SPI_SR : (SPI Offset: 0x10) Status Register -------- */
AT91C_SPI_RDRF EQU( 0x1 << 0 );
-( SPI ) Receive దత్తాంశం రిజిస్టరు నిండిన
AT91C_SPI_TDRE EQU( 0x1 << 1 );
-( SPI ) Transmit దత్తాంశం రిజిస్టరు ఖాళీలు
AT91C_SPI_MODF EQU( 0x1 << 2 );
-( SPI ) బహుళకం Fault Error
AT91C_SPI_OVRES EQU( 0x1 << 3 );
-( SPI ) Overrun Error స్థితి_2
AT91C_SPI_ENDRX EQU( 0x1 << 4 );
-( SPI ) చివర_2 యొక్క Receiver Transfer
AT91C_SPI_ENDTX EQU( 0x1 << 5 );
-( SPI ) చివర_2 యొక్క Receiver Transfer
AT91C_SPI_RXBUFF EQU( 0x1 << 6 );
-( SPI ) RXBUFF అంతరాయం_2
AT91C_SPI_TXBUFE EQU( 0x1 << 7 );
-( SPI ) TXBUFE అంతరాయం_2
AT91C_SPI_NSSR EQU( 0x1 << 8 );
-( SPI ) NSSR అంతరాయం_2
AT91C_SPI_TXEMPTY EQU( 0x1 << 9 );
-( SPI ) TXEMPTY అంతరాయం_2
AT91C_SPI_SPIENS EQU( 0x1 << 16 );
-( SPI ) Enable స్థితి_2
/* - -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- */
/* - -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- */
/* - -------- SPI_IMR : (SPI Offset: 0x1c) Interrupt Mask Register -------- */
/* - -------- SPI_CSR : (SPI Offset: 0x30) Chip Select Register -------- */
AT91C_SPI_CPOL EQU( 0x1 << 0 );
-( SPI ) Clock Polarity
AT91C_SPI_NCPHA EQU( 0x1 << 1 );
-( SPI ) Clock Phase
AT91C_SPI_CSAAT EQU( 0x1 << 3 );
-( SPI ) Chip Select చురుకైన After Transfer
AT91_C_SPI_బిట్లు EQU( 0xF << 4 );
-( SPI ) బిట్లు చొప్పున Transfer
AT91_C_SPI_బిట్లు_8 EQU( 0x0 << 4 );
-( SPI ) 8 బిట్లు చొప్పున transfer
AT91_C_SPI_బిట్లు_9 EQU( 0x1 << 4 );
-( SPI ) 9 బిట్లు చొప్పున transfer
AT91_C_SPI_బిట్లు_10 EQU( 0x2 << 4 );
-( SPI ) 10 బిట్లు చొప్పున transfer
AT91_C_SPI_బిట్లు_11 EQU( 0x3 << 4 );
-( SPI ) 11 బిట్లు చొప్పున transfer
AT91_C_SPI_బిట్లు_12 EQU( 0x4 << 4 );
-( SPI ) 12 బిట్లు చొప్పున transfer
AT91_C_SPI_బిట్లు_13 EQU( 0x5 << 4 );
-( SPI ) 13 బిట్లు చొప్పున transfer
AT91_C_SPI_బిట్లు_14 EQU( 0x6 << 4 );
-( SPI ) 14 బిట్లు చొప్పున transfer
AT91_C_SPI_బిట్లు_15 EQU( 0x7 << 4 );
-( SPI ) 15 బిట్లు చొప్పున transfer
AT91_C_SPI_బిట్లు_16 EQU( 0x8 << 4 );
-( SPI ) 16 బిట్లు చొప్పున transfer
AT91C_SPI_SCBR EQU( 0xFF << 8 );
-( SPI ) Serial Clock Baud రేటు
AT91C_SPI_DLYBS EQU( 0xFF << 16 );
-( SPI ) Delay Before SPCK
AT91C_SPI_DLYBCT EQU( 0xFF << 24 );
-( SPI ) Delay Between Consecutive Transfers

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Usart */
/* - ***************************************************************************** */
/* - -------- US_CR : (USART Offset: 0x0) Debug Unit Control Register -------- */
AT91C_US_STTBRK EQU( 0x1 << 9 );
-( USART ) ప్రారంభం_2 Break
AT91C_US_STPBRK EQU( 0x1 << 10 );
-( USART ) Stop Break
AT91C_US_STTTO EQU( 0x1 << 11 );
-( USART ) ప్రారంభం_2 సమయం - బహిర్గతం
AT91C_US_SENDA EQU( 0x1 << 12 );
-( USART ) Send చిరునామా
AT91C_US_RSTIT EQU( 0x1 << 13 );
-( USART ) Reset Iterations
AT91C_US_RSTNACK EQU( 0x1 << 14 );
-( USART ) Reset Non Acknowledge
AT91C_US_RETTO EQU( 0x1 << 15 );
-( USART ) Rearm సమయం - బహిర్గతం
AT91C_US_DTREN EQU( 0x1 << 16 );
-( USART ) దత్తాంశం Terminal ready Enable
AT91C_US_DTRDIS EQU( 0x1 << 17 );
-( USART ) దత్తాంశం Terminal ready Disable
AT91C_US_RTSEN EQU( 0x1 << 18 );
-( USART ) Request గమ్యం Send enable
AT91C_US_RTSDIS EQU( 0x1 << 19 );
-( USART ) Request గమ్యం Send Disable
/* - -------- US_MR : (USART Offset: 0x4) Debug Unit Mode Register -------- */
AT91C_US_USMODE EQU( 0xF << 0 );
-( USART ) Usart బహుళకం_2
AT91_C_US_USMODE_సాధారణ EQU( 0x0 );
-( USART ) సాధారణ
AT91C_US_USMODE_RS485 EQU( 0x1 );
-( USART ) RS485
AT91C_US_USMODE_HWHSH EQU( 0x2 );
-( USART ) Hardware Handshaking
AT91C_US_USMODE_MODEM EQU( 0x3 );
-( USART ) Modem
AT91C_US_USMODE_ISO7816_0 EQU( 0x4 );
-( USART ) ISO7816 protocol: T = 0
                                 AT91C_US_USMODE_ISO7816_1 EQU( 0x6 );
-( USART ) ISO7816 protocol: T = 1
                                 AT91C_US_USMODE_IRDA EQU( 0x8 );
-( USART ) IrDA
AT91C_US_USMODE_SWHSH EQU( 0xC );
-( USART ) Software Handshaking
AT91C_US_CLKS EQU( 0x3 << 4 );
-( USART ) Clock Selection ( Baud రేటు generator ఆదానం Clock
                             AT91C_US_CLKS_CLOCK EQU( 0x0 << 4 );
                             -( USART ) Clock
                             AT91C_US_CLKS_FDIV1 EQU( 0x1 << 4 );
                             -( USART ) fdiv1
                             AT91C_US_CLKS_SLOW EQU( 0x2 << 4 );
                             -( USART ) slow_clock( ARM )
                             AT91C_US_CLKS_EXT EQU( 0x3 << 4 );
                             -( USART ) External( SCK )
                             AT91C_US_CHRL EQU( 0x3 << 6 );
                             -( USART ) Clock Selection ( Baud రేటు generator ఆదానం Clock
                                                          AT91_C_US_CHRL_5_బిట్లు EQU( 0x0 << 6 );
                                                          -( USART ) Character నిడివి : 5 బిట్లు_2
                                                          AT91_C_US_CHRL_6_బిట్లు EQU( 0x1 << 6 );
                                                          -( USART ) Character నిడివి : 6 బిట్లు_2
                                                          AT91_C_US_CHRL_7_బిట్లు EQU( 0x2 << 6 );
                                                          -( USART ) Character నిడివి : 7 బిట్లు_2
                                                          AT91_C_US_CHRL_8_బిట్లు EQU( 0x3 << 6 );
                                                          -( USART ) Character నిడివి : 8 బిట్లు_2
                                                          AT91C_US_SYNC EQU( 0x1 << 8 );
                                                          -( USART ) Synchronous బహుళకం Select
                                                          AT91C_US_NBSTOP EQU( 0x3 << 12 );
                                                          -( USART ) సంఖ్య_2 యొక్క Stop బిట్లు_2
                                                          AT91_C_US_NBSTOP_1_బిట్టు EQU( 0x0 << 12 );
                                                          -( USART ) 1 stop బిట్టు_2
                                                          AT91_C_US_NBSTOP_15_బిట్టు EQU( 0x1 << 12 );
                                                          -( USART ) Asynchronous( SYNC = 0 ) 2 stop బిట్లు_2 Synchronous( SYNC = 1 ) 2 stop బిట్లు_2
                                                          AT91_C_US_NBSTOP_2_బిట్టు EQU( 0x2 << 12 );
                                                          -( USART ) 2 stop బిట్లు_2
                                                          AT91C_US_MSBF EQU( 0x1 << 16 );
                                                          -( USART ) బిట్టు క్రమం_2
                                                          AT91C_US_MODE9 EQU( 0x1 << 17 );
                                                          -( USART ) 9 - బిట్టు_2 Character నిడివి_2
                                                          AT91C_US_CKLO EQU( 0x1 << 18 );
                                                          -( USART ) Clock Output Select
                                                          AT91C_US_OVER EQU( 0x1 << 19 );
                                                          -( USART ) Over Sampling బహుళకం
                                                          AT91C_US_INACK EQU( 0x1 << 20 );
                                                          -( USART ) Inhibit Non Acknowledge
                                                          AT91C_US_DSNACK EQU( 0x1 << 21 );
                                                          -( USART ) Disable Successive NACK
                                                          AT91C_US_MAX_ITER EQU( 0x1 << 24 );
                                                          -( USART ) సంఖ్య_2 యొక్క Repetitions
                                                          AT91C_US_FILTER EQU( 0x1 << 28 );
                                                          -( USART ) Receive పంక్తి_2 Filter
/* - -------- US_IER : (USART Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
                                                          AT91C_US_RXBRK EQU( 0x1 << 2 );
                                                          -( USART ) Break Received / చివర_2 యొక్క Break
                                                          AT91C_US_TIMEOUT EQU( 0x1 << 8 );
                                                          -( USART ) Receiver సమయం - బహిర్గతం
                                                          AT91C_US_ITERATION EQU( 0x1 << 10 );
                                                          -( USART ) Max సంఖ్య యొక్క Repetitions Reached
                                                          AT91C_US_NACK EQU( 0x1 << 13 );
                                                          -( USART ) Non Acknowledge
                                                          AT91C_US_RIIC EQU( 0x1 << 16 );
                                                          -( USART ) Ring INdicator ఆదానం Change Flag
                                                          AT91C_US_DSRIC EQU( 0x1 << 17 );
                                                          -( USART ) దత్తాంశం సమితి_2 Ready ఆదానం Change Flag
                                                          AT91C_US_DCDIC EQU( 0x1 << 18 );
                                                          -( USART ) దత్తాంశం Carrier Flag
                                                          AT91C_US_CTSIC EQU( 0x1 << 19 );
                                                          -( USART ) Clear గమ్యం_2 Send ఆదానం Change Flag
/* - -------- US_IDR : (USART Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* - -------- US_IMR : (USART Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* - -------- US_CSR : (USART Offset: 0x14) Debug Unit Channel Status Register -------- */
                                                          AT91C_US_RI EQU( 0x1 << 20 );
                                                          -( USART ) Image యొక్క RI ఆదానం
                                                          AT91C_US_DSR EQU( 0x1 << 21 );
                                                          -( USART ) Image యొక్క DSR ఆదానం
                                                          AT91C_US_DCD EQU( 0x1 << 22 );
                                                          -( USART ) Image యొక్క DCD ఆదానం
                                                          AT91C_US_CTS EQU( 0x1 << 23 );
                                                          -( USART ) Image యొక్క CTS ఆదానం

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Synchronous Serial Controller Interface */
/* - ***************************************************************************** */
/* - -------- SSC_CR : (SSC Offset: 0x0) SSC Control Register -------- */
                                                          AT91C_SSC_RXEN EQU( 0x1 << 0 );
                                                          -( SSC ) Receive Enable
                                                          AT91C_SSC_RXDIS EQU( 0x1 << 1 );
                                                          -( SSC ) Receive Disable
                                                          AT91C_SSC_TXEN EQU( 0x1 << 8 );
                                                          -( SSC ) Transmit Enable
                                                          AT91C_SSC_TXDIS EQU( 0x1 << 9 );
                                                          -( SSC ) Transmit Disable
                                                          AT91C_SSC_SWRST EQU( 0x1 << 15 );
                                                          -( SSC ) Software Reset
/* - -------- SSC_RCMR : (SSC Offset: 0x10) SSC Receive Clock Mode Register -------- */
                                                          AT91C_SSC_CKS EQU( 0x3 << 0 );
                                                          -( SSC ) Receive / Transmit Clock Selection
                                                          AT91C_SSC_CKS_DIV EQU( 0x0 );
                                                          -( SSC ) Divided Clock
                                                          AT91C_SSC_CKS_TK EQU( 0x1 );
                                                          -( SSC ) TK Clock సంకేతం
                                                          AT91C_SSC_CKS_RK EQU( 0x2 );
                                                          -( SSC ) RK pin
                                                          AT91C_SSC_CKO EQU( 0x7 << 2 );
                                                          -( SSC ) Receive / Transmit Clock Output బహుళకం Selection
                                                          AT91C_SSC_CKO_NONE EQU( 0x0 << 2 );
                                                          -( SSC ) Receive / Transmit Clock Output బహుళకం:None RK pin: ఆదానం - only
                                                          AT91C_SSC_CKO_CONTINUOUS EQU( 0x1 << 2 );
                                                          -( SSC ) Continuous Receive / Transmit Clock RK pin:Output
                                                          AT91_C_SSC_CKO_దత్తాంశం_TX EQU( 0x2 << 2 );
                                                          -( SSC ) Receive / Transmit Clock only during దత్తాంశం_2 transfers RK pin:Output
                                                          AT91C_SSC_CKI EQU( 0x1 << 5 );
                                                          -( SSC ) Receive / Transmit Clock Inversion
                                                          AT91_C_SSC_ప్రారంభం EQU( 0xF << 8 );
                                                          -( SSC ) Receive / Transmit ప్రారంభం_2 Selection
                                                          AT91_C_SSC_ప్రారంభం_CONTINUOUS EQU( 0x0 << 8 );
                                                          -( SSC ) Continuous, as soon as the receiver is enabled, and immediately after the చివర యొక్క transfer యొక్క the మునుపటి దత్తాంశం_2.
                                                             AT91_C_SSC_ప్రారంభం_TX EQU( 0x1 << 8 );
                                                          -( SSC ) Transmit / Receive ప్రారంభం
                                                          AT91_C_SSC_ప్రారంభం_దిగువ_RF EQU( 0x2 << 8 );
                                                          -( SSC ) Detection యొక్క a దిగువ_2 level on RF ఆదానం_2
                                                          AT91_C_SSC_ప్రారంభం_ఎగువ_RF EQU( 0x3 << 8 );
                                                          -( SSC ) Detection యొక్క a ఎగువ_2 level on RF ఆదానం_2
                                                          AT91_C_SSC_ప్రారంభం_FALL_RF EQU( 0x4 << 8 );
                                                          -( SSC ) Detection యొక్క a falling అంచు_2 on RF ఆదానం_2
                                                          AT91_C_SSC_ప్రారంభం_RISE_RF EQU( 0x5 << 8 );
                                                          -( SSC ) Detection యొక్క a rising అంచు_2 on RF ఆదానం_2
                                                          AT91_C_SSC_ప్రారంభం_LEVEL_RF EQU( 0x6 << 8 );
                                                          -( SSC ) Detection యొక్క any level change on RF ఆదానం_2
                                                          AT91_C_SSC_ప్రారంభం_అంచు_RF EQU( 0x7 << 8 );
                                                          -( SSC ) Detection యొక్క any అంచు_2 on RF ఆదానం_2
                                                          AT91_C_SSC_ప్రారంభం_0 EQU( 0x8 << 8 );
                                                          -( SSC ) Compare 0
                                                          AT91C_SSC_STTDLY EQU( 0xFF << 16 );
                                                          -( SSC ) Receive / Transmit ప్రారంభం_2 Delay
                                                          AT91C_SSC_PERIOD EQU( 0xFF << 24 );
                                                          -( SSC ) Receive / Transmit Period Divider Selection
/* - -------- SSC_RFMR : (SSC Offset: 0x14) SSC Receive Frame Mode Register -------- */
                                                          AT91C_SSC_DATLEN EQU( 0x1F << 0 );
                                                          -( SSC ) దత్తాంశం నిడివి
                                                          AT91C_SSC_LOOP EQU( 0x1 << 5 );
                                                          -( SSC ) Loop బహుళకం
                                                          AT91C_SSC_MSBF EQU( 0x1 << 7 );
                                                          -( SSC ) Most Significant బిట్టు మొదటి
                                                          AT91C_SSC_DATNB EQU( 0xF << 8 );
                                                          -( SSC ) దత్తాంశం సంఖ్య_2 చొప్పున_2 చట్రం
                                                          AT91C_SSC_FSLEN EQU( 0xF << 16 );
                                                          -( SSC ) Receive / Transmit చట్రం Sync నిడివి_2
                                                          AT91C_SSC_FSOS EQU( 0x7 << 20 );
                                                          -( SSC ) Receive / Transmit చట్రం Sync Output Selection
                                                          AT91C_SSC_FSOS_NONE EQU( 0x0 << 20 );
                                                          -( SSC ) Selected Receive / Transmit చట్రం Sync Signal:None RK pin ఆదానం - only
                                                          AT91C_SSC_FSOS_NEGATIVE EQU( 0x1 << 20 );
                                                          -( SSC ) Selected Receive / Transmit చట్రం Sync Signal:Negative Pulse
                                                          AT91_C_SSC_FSOS_ధనాత్మక EQU( 0x2 << 20 );
                                                          -( SSC ) Selected Receive / Transmit చట్రం Sync Signal:ధనాత్మక Pulse
                                                          AT91_C_SSC_FSOS_దిగువ EQU( 0x3 << 20 );
                                                          -( SSC ) Selected Receive / Transmit చట్రం Sync Signal:Driver దిగువ during దత్తాంశం_2 transfer
                                                          AT91_C_SSC_FSOS_ఎగువ EQU( 0x4 << 20 );
                                                          -( SSC ) Selected Receive / Transmit చట్రం Sync Signal:Driver ఎగువ during దత్తాంశం_2 transfer
                                                          AT91C_SSC_FSOS_TOGGLE EQU( 0x5 << 20 );
                                                          -( SSC ) Selected Receive / Transmit చట్రం Sync Signal:Toggling at each ప్రారంభం యొక్క దత్తాంశం_2 transfer
                                                          AT91C_SSC_FSEDGE EQU( 0x1 << 24 );
                                                          -( SSC ) చట్రం Sync అంచు Detection
/* - -------- SSC_TCMR : (SSC Offset: 0x18) SSC Transmit Clock Mode Register -------- */
/* - -------- SSC_TFMR : (SSC Offset: 0x1c) SSC Transmit Frame Mode Register -------- */
                                                          AT91C_SSC_DATDEF EQU( 0x1 << 5 );
                                                          -( SSC ) దత్తాంశం Default విలువ_2
                                                          AT91C_SSC_FSDEN EQU( 0x1 << 23 );
                                                          -( SSC ) చట్రం Sync దత్తాంశం Enable
/* - -------- SSC_SR : (SSC Offset: 0x40) SSC Status Register -------- */
                                                          AT91C_SSC_TXRDY EQU( 0x1 << 0 );
                                                          -( SSC ) Transmit Ready
                                                          AT91C_SSC_TXEMPTY EQU( 0x1 << 1 );
                                                          -( SSC ) Transmit ఖాళీలు
                                                          AT91C_SSC_ENDTX EQU( 0x1 << 2 );
                                                          -( SSC ) చివర_2 యొక్క_2 సంప్రేషణ
                                                          AT91C_SSC_TXBUFE EQU( 0x1 << 3 );
                                                          -( SSC ) Transmit బఫరు ఖాళీలు
                                                          AT91C_SSC_RXRDY EQU( 0x1 << 4 );
                                                          -( SSC ) Receive Ready
                                                          AT91C_SSC_OVRUN EQU( 0x1 << 5 );
                                                          -( SSC ) Receive Overrun
                                                          AT91C_SSC_ENDRX EQU( 0x1 << 6 );
                                                          -( SSC ) చివర_2 యొక్క Reception
                                                          AT91C_SSC_RXBUFF EQU( 0x1 << 7 );
                                                          -( SSC ) Receive బఫరు నిండిన
                                                          AT91C_SSC_TXSYN EQU( 0x1 << 10 );
                                                          -( SSC ) Transmit Sync
                                                          AT91C_SSC_RXSYN EQU( 0x1 << 11 );
                                                          -( SSC ) Receive Sync
                                                          AT91C_SSC_TXENA EQU( 0x1 << 16 );
                                                          -( SSC ) Transmit Enable
                                                          AT91C_SSC_RXENA EQU( 0x1 << 17 );
                                                          -( SSC ) Receive Enable
/* - -------- SSC_IER : (SSC Offset: 0x44) SSC Interrupt Enable Register -------- */
/* - -------- SSC_IDR : (SSC Offset: 0x48) SSC Interrupt Disable Register -------- */
/* - -------- SSC_IMR : (SSC Offset: 0x4c) SSC Interrupt Mask Register -------- */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Two-wire Interface */
/* - ***************************************************************************** */
/* - -------- TWI_CR : (TWI Offset: 0x0) TWI Control Register -------- */
                                                          AT91_C_TWI_ప్రారంభం EQU( 0x1 << 0 );
                                                          -( TWI ) Send a ప్రారంభం_3 Condition
                                                          AT91C_TWI_STOP EQU( 0x1 << 1 );
                                                          -( TWI ) Send a STOP Condition
                                                          AT91C_TWI_MSEN EQU( 0x1 << 2 );
                                                          -( TWI ) TWI Master Transfer Enabled
                                                          AT91C_TWI_MSDIS EQU( 0x1 << 3 );
                                                          -( TWI ) TWI Master Transfer Disabled
                                                          AT91C_TWI_SWRST EQU( 0x1 << 7 );
                                                          -( TWI ) Software Reset
/* - -------- TWI_MMR : (TWI Offset: 0x4) TWI Master Mode Register -------- */
                                                          AT91C_TWI_IADRSZ EQU( 0x3 << 8 );
                                                          -( TWI ) అంతర్గత Device చిరునామా కొలత_2
                                                          AT91C_TWI_IADRSZ_NO EQU( 0x0 << 8 );
                                                          -( TWI ) No అంతర్గత_2 device చిరునామా_2
                                                          AT91C_TWI_IADRSZ_1_BYTE EQU( 0x1 << 8 );
                                                          -( TWI ) One - byte అంతర్గత_2 device చిరునామా_2
                                                          AT91C_TWI_IADRSZ_2_BYTE EQU( 0x2 << 8 );
                                                          -( TWI ) Two - byte అంతర్గత_2 device చిరునామా_2
                                                          AT91C_TWI_IADRSZ_3_BYTE EQU( 0x3 << 8 );
                                                          -( TWI ) Three - byte అంతర్గత_2 device చిరునామా_2
                                                          AT91C_TWI_MREAD EQU( 0x1 << 12 );
                                                          -( TWI ) Master Read Direction
                                                          AT91C_TWI_DADR EQU( 0x7F << 16 );
                                                          -( TWI ) Device చిరునామా
/* - -------- TWI_CWGR : (TWI Offset: 0x10) TWI Clock Waveform Generator Register -------- */
                                                          AT91C_TWI_CLDIV EQU( 0xFF << 0 );
                                                          -( TWI ) Clock దిగువ Divider
                                                          AT91C_TWI_CHDIV EQU( 0xFF << 8 );
                                                          -( TWI ) Clock ఎగువ Divider
                                                          AT91C_TWI_CKDIV EQU( 0x7 << 16 );
                                                          -( TWI ) Clock Divider
/* - -------- TWI_SR : (TWI Offset: 0x20) TWI Status Register -------- */
                                                          AT91C_TWI_TXCOMP EQU( 0x1 << 0 );
                                                          -( TWI ) సంప్రేషణ Completed
                                                          AT91C_TWI_RXRDY EQU( 0x1 << 1 );
                                                          -( TWI ) Receive holding నమోదు ReaDY
                                                          AT91C_TWI_TXRDY EQU( 0x1 << 2 );
                                                          -( TWI ) Transmit holding నమోదు ReaDY
                                                          AT91C_TWI_OVRE EQU( 0x1 << 6 );
                                                          -( TWI ) Overrun Error
                                                          AT91C_TWI_UNRE EQU( 0x1 << 7 );
                                                          -( TWI ) Underrun Error
                                                          AT91C_TWI_NACK EQU( 0x1 << 8 );
                                                          -( TWI ) Not Acknowledged
/* - -------- TWI_IER : (TWI Offset: 0x24) TWI Interrupt Enable Register -------- */
/* - -------- TWI_IDR : (TWI Offset: 0x28) TWI Interrupt Disable Register -------- */
/* - -------- TWI_IMR : (TWI Offset: 0x2c) TWI Interrupt Mask Register -------- */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR PWMC Channel Interface */
/* - ***************************************************************************** */
/* - -------- PWMC_CMR : (PWMC_CH Offset: 0x0) PWMC Channel Mode Register -------- */
                                                          AT91C_PWMC_CPRE EQU( 0xF << 0 );
                                                          -( PWMC_CH ) Channel Pre - scaler:PWMC_CLKx
                                                          AT91C_PWMC_CPRE_MCK EQU( 0x0 );
                                                          -( PWMC_CH )
                                                          AT91C_PWMC_CPRE_MCKA EQU( 0xB );
                                                          -( PWMC_CH )
                                                          AT91C_PWMC_CPRE_MCKB EQU( 0xC );
                                                          -( PWMC_CH )
                                                          AT91C_PWMC_CALG EQU( 0x1 << 8 );
                                                          -( PWMC_CH ) Channel Alignment
                                                          AT91C_PWMC_CPOL EQU( 0x1 << 9 );
                                                          -( PWMC_CH ) Channel Polarity
                                                          AT91C_PWMC_CPD EQU( 0x1 << 10 );
                                                          -( PWMC_CH ) Channel Update Period
/* - -------- PWMC_CDTYR : (PWMC_CH Offset: 0x4) PWMC Channel Duty Cycle Register -------- */
                                                          AT91C_PWMC_CDTY EQU( 0x0 << 0 );
                                                          -( PWMC_CH ) Channel Duty చక్రం_2
/* - -------- PWMC_CPRDR : (PWMC_CH Offset: 0x8) PWMC Channel Period Register -------- */
                                                          AT91C_PWMC_CPRD EQU( 0x0 << 0 );
                                                          -( PWMC_CH ) Channel Period
/* - -------- PWMC_CCNTR : (PWMC_CH Offset: 0xc) PWMC Channel Counter Register -------- */
                                                          AT91C_PWMC_CCNT EQU( 0x0 << 0 );
                                                          -( PWMC_CH ) Channel Counter
/* - -------- PWMC_CUPDR : (PWMC_CH Offset: 0x10) PWMC Channel Update Register -------- */
                                                          AT91C_PWMC_CUPD EQU( 0x0 << 0 );
                                                          -( PWMC_CH ) Channel Update

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Pulse Width Modulation Controller Interface */
/* - ***************************************************************************** */
/* - -------- PWMC_MR : (PWMC Offset: 0x0) PWMC Mode Register -------- */
                                                          AT91C_PWMC_DIVA EQU( 0xFF << 0 );
                                                          -( PWMC ) CLKA divide గుణకం.
                                                             AT91C_PWMC_PREA EQU( 0xF << 8 );
                                                          -( PWMC ) Divider ఆదానం Clock Prescaler A
                                                          AT91C_PWMC_PREA_MCK EQU( 0x0 << 8 );
                                                          -( PWMC )
                                                          AT91C_PWMC_DIVB EQU( 0xFF << 16 );
                                                          -( PWMC ) CLKB divide గుణకం.
                                                             AT91C_PWMC_PREB EQU( 0xF << 24 );
                                                          -( PWMC ) Divider ఆదానం Clock Prescaler B
                                                          AT91C_PWMC_PREB_MCK EQU( 0x0 << 24 );
                                                          -( PWMC )
/* - -------- PWMC_ENA : (PWMC Offset: 0x4) PWMC Enable Register -------- */
                                                          AT91C_PWMC_CHID0 EQU( 0x1 << 0 );
                                                          -( PWMC ) Channel ID 0
                                                          AT91C_PWMC_CHID1 EQU( 0x1 << 1 );
                                                          -( PWMC ) Channel ID 1
                                                          AT91C_PWMC_CHID2 EQU( 0x1 << 2 );
                                                          -( PWMC ) Channel ID 2
                                                          AT91C_PWMC_CHID3 EQU( 0x1 << 3 );
                                                          -( PWMC ) Channel ID 3
/* - -------- PWMC_DIS : (PWMC Offset: 0x8) PWMC Disable Register -------- */
/* - -------- PWMC_SR : (PWMC Offset: 0xc) PWMC Status Register -------- */
/* - -------- PWMC_IER : (PWMC Offset: 0x10) PWMC Interrupt Enable Register -------- */
/* - -------- PWMC_IDR : (PWMC Offset: 0x14) PWMC Interrupt Disable Register -------- */
/* - -------- PWMC_IMR : (PWMC Offset: 0x18) PWMC Interrupt Mask Register -------- */
/* - -------- PWMC_ISR : (PWMC Offset: 0x1c) PWMC Interrupt Status Register -------- */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR USB Device Interface */
/* - ***************************************************************************** */
/* - -------- UDP_FRM_NUM : (UDP Offset: 0x0) USB Frame Number Register -------- */
                                                          AT91_C_UDP_FRM_అంకె EQU( 0x7FF << 0 );
                                                          -( UDP ) చట్రం సంఖ్య_2 as Defined లోపల the Packet క్షేత్రం_2 Formats
                                                          AT91C_UDP_FRM_ERR EQU( 0x1 << 16 );
                                                          -( UDP ) చట్రం Error
                                                          AT91C_UDP_FRM_OK EQU( 0x1 << 17 );
                                                          -( UDP ) చట్రం OK
/* - -------- UDP_GLB_STATE : (UDP Offset: 0x4) USB Global State Register -------- */
                                                          AT91C_UDP_FADDEN EQU( 0x1 << 0 );
                                                          -( UDP ) Function చిరునామా Enable
                                                          AT91C_UDP_CONFG EQU( 0x1 << 1 );
                                                          -( UDP ) Configured
                                                          AT91C_UDP_ESR EQU( 0x1 << 2 );
                                                          -( UDP ) Enable Send Resume
                                                          AT91C_UDP_RSMINPR EQU( 0x1 << 3 );
                                                          -( UDP ) A Resume Has Been పంపిన గమ్యం the Host
                                                          AT91C_UDP_RMWUPE EQU( 0x1 << 4 );
                                                          -( UDP ) Remote Wake పైకి_2 Enable
/* - -------- UDP_FADDR : (UDP Offset: 0x8) USB Function Address Register -------- */
                                                          AT91C_UDP_FADD EQU( 0xFF << 0 );
                                                          -( UDP ) Function చిరునామా విలువ_2
                                                          AT91C_UDP_FEN EQU( 0x1 << 8 );
                                                          -( UDP ) Function Enable
/* - -------- UDP_IER : (UDP Offset: 0x10) USB Interrupt Enable Register -------- */
                                                          AT91C_UDP_EPINT0 EQU( 0x1 << 0 );
                                                          -( UDP ) Endpoint 0 అంతరాయం_2
                                                          AT91C_UDP_EPINT1 EQU( 0x1 << 1 );
                                                          -( UDP ) Endpoint 0 అంతరాయం_2
                                                          AT91C_UDP_EPINT2 EQU( 0x1 << 2 );
                                                          -( UDP ) Endpoint 2 అంతరాయం_2
                                                          AT91C_UDP_EPINT3 EQU( 0x1 << 3 );
                                                          -( UDP ) Endpoint 3 అంతరాయం_2
                                                          AT91C_UDP_EPINT4 EQU( 0x1 << 4 );
                                                          -( UDP ) Endpoint 4 అంతరాయం_2
                                                          AT91C_UDP_EPINT5 EQU( 0x1 << 5 );
                                                          -( UDP ) Endpoint 5 అంతరాయం_2
                                                          AT91C_UDP_RXSUSP EQU( 0x1 << 8 );
                                                          -( UDP ) USB Suspend అంతరాయం_2
                                                          AT91C_UDP_RXRSM EQU( 0x1 << 9 );
                                                          -( UDP ) USB Resume అంతరాయం_2
                                                          AT91C_UDP_EXTRSM EQU( 0x1 << 10 );
                                                          -( UDP ) USB External Resume అంతరాయం_2
                                                          AT91C_UDP_SOFINT EQU( 0x1 << 11 );
                                                          -( UDP ) USB ప్రారంభం_2 యొక్క_2 చట్రం_2 అంతరాయం_2
                                                          AT91C_UDP_WAKEUP EQU( 0x1 << 13 );
                                                          -( UDP ) USB Resume అంతరాయం_2
/* - -------- UDP_IDR : (UDP Offset: 0x14) USB Interrupt Disable Register -------- */
/* - -------- UDP_IMR : (UDP Offset: 0x18) USB Interrupt Mask Register -------- */
/* - -------- UDP_ISR : (UDP Offset: 0x1c) USB Interrupt Status Register -------- */
                                                          AT91C_UDP_ENDBUSRES EQU( 0x1 << 12 );
                                                          -( UDP ) USB చివర_2 యొక్క_2 Bus Reset అంతరాయం_2
/* - -------- UDP_ICR : (UDP Offset: 0x20) USB Interrupt Clear Register -------- */
/* - -------- UDP_RST_EP : (UDP Offset: 0x28) USB Reset Endpoint Register -------- */
                                                          AT91C_UDP_EP0 EQU( 0x1 << 0 );
                                                          -( UDP ) Reset Endpoint 0
                                                          AT91C_UDP_EP1 EQU( 0x1 << 1 );
                                                          -( UDP ) Reset Endpoint 1
                                                          AT91C_UDP_EP2 EQU( 0x1 << 2 );
                                                          -( UDP ) Reset Endpoint 2
                                                          AT91C_UDP_EP3 EQU( 0x1 << 3 );
                                                          -( UDP ) Reset Endpoint 3
                                                          AT91C_UDP_EP4 EQU( 0x1 << 4 );
                                                          -( UDP ) Reset Endpoint 4
                                                          AT91C_UDP_EP5 EQU( 0x1 << 5 );
                                                          -( UDP ) Reset Endpoint 5
/* - -------- UDP_CSR : (UDP Offset: 0x30) USB Endpoint Control and Status Register -------- */
                                                          AT91C_UDP_TXCOMP EQU( 0x1 << 0 );
                                                          -( UDP ) Generates an లోపల_2 packet with దత్తాంశం_2 previously written లోపల the DPR
                                                          AT91_C_UDP_RX_దత్తాంశం_BK0 EQU( 0x1 << 1 );
                                                          -( UDP ) Receive దత్తాంశం Bank 0
                                                          AT91C_UDP_RXSETUP EQU( 0x1 << 2 );
                                                          -( UDP ) Sends STALL గమ్యం the Host( Control endpoints )
                                                          AT91C_UDP_ISOERROR EQU( 0x1 << 3 );
                                                          -( UDP ) Isochronous error( Isochronous endpoints )
                                                          AT91C_UDP_TXPKTRDY EQU( 0x1 << 4 );
                                                          -( UDP ) Transmit Packet Ready
                                                          AT91C_UDP_FORCESTALL EQU( 0x1 << 5 );
                                                          -( UDP ) Force Stall( వాడిన by Control, Bulk and Isochronous endpoints ).
                                                             AT91_C_UDP_RX_దత్తాంశం_BK1 EQU( 0x1 << 6 );
                                                          -( UDP ) Receive దత్తాంశం Bank 1 ( only వాడిన by endpoints with ping - pong లక్షణాలు ).
                                                             AT91C_UDP_DIR EQU( 0x1 << 7 );
                                                          -( UDP ) Transfer Direction
                                                          AT91C_UDP_EPTYPE EQU( 0x7 << 8 );
                                                          -( UDP ) Endpoint type
                                                          AT91C_UDP_EPTYPE_CTRL EQU( 0x0 << 8 );
                                                          -( UDP ) Control
                                                          AT91_C_UDP_EPTYPE_ISO_బహిర్గతం EQU( 0x1 << 8 );
                                                          -( UDP ) Isochronous బహిర్గతం_2
                                                          AT91_C_UDP_EPTYPE_BULK_బహిర్గతం EQU( 0x2 << 8 );
                                                          -( UDP ) Bulk బహిర్గతం_2
                                                          AT91_C_UDP_EPTYPE_INT_బహిర్గతం EQU( 0x3 << 8 );
                                                          -( UDP ) అంతరాయం_2 బహిర్గతం_2
                                                          AT91_C_UDP_EPTYPE_ISO_లోపల EQU( 0x5 << 8 );
                                                          -( UDP ) Isochronous లోపల_2
                                                          AT91_C_UDP_EPTYPE_BULK_లోపల EQU( 0x6 << 8 );
                                                          -( UDP ) Bulk లోపల_2
                                                          AT91_C_UDP_EPTYPE_INT_లోపల EQU( 0x7 << 8 );
                                                          -( UDP ) అంతరాయం_2 లోపల_2
                                                          AT91C_UDP_DTGLE EQU( 0x1 << 11 );
                                                          -( UDP ) దత్తాంశం Toggle
                                                          AT91C_UDP_EPEDS EQU( 0x1 << 15 );
                                                          -( UDP ) Endpoint Enable Disable
                                                          AT91C_UDP_RXBYTECNT EQU( 0x7FF << 16 );
                                                          -( UDP ) సంఖ్య_2 యొక్క_2 బైట్లు అందుబాటు_2 లోపల the FIFO
/* - -------- UDP_TXVC : (UDP Offset: 0x74) Transceiver Control Register -------- */
                                                          AT91C_UDP_TXVDIS EQU( 0x1 << 8 );
                                                          -( UDP )
                                                          AT91C_UDP_PUON EQU( 0x1 << 9 );
                                                          -( UDP ) Pull - పైకి ON

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Timer Counter Channel Interface */
/* - ***************************************************************************** */
/* - -------- TC_CCR : (TC Offset: 0x0) TC Channel Control Register -------- */
                                                          AT91C_TC_CLKEN EQU( 0x1 << 0 );
                                                          -( TC ) Counter Clock Enable Command
                                                          AT91C_TC_CLKDIS EQU( 0x1 << 1 );
                                                          -( TC ) Counter Clock Disable Command
                                                          AT91C_TC_SWTRG EQU( 0x1 << 2 );
                                                          -( TC ) Software Trigger Command
/* - -------- TC_CMR : (TC Offset: 0x4) TC Channel Mode Register: Capture Mode / Waveform Mode -------- */
                                                          AT91C_TC_CLKS EQU( 0x7 << 0 );
                                                          -( TC ) Clock Selection
                                                          AT91C_TC_CLKS_TIMER_DIV1_CLOCK EQU( 0x0 );
                                                          -( TC ) Clock selected:TIMER_DIV1_CLOCK
                                                          AT91C_TC_CLKS_TIMER_DIV2_CLOCK EQU( 0x1 );
                                                          -( TC ) Clock selected:TIMER_DIV2_CLOCK
                                                          AT91C_TC_CLKS_TIMER_DIV3_CLOCK EQU( 0x2 );
                                                          -( TC ) Clock selected:TIMER_DIV3_CLOCK
                                                          AT91C_TC_CLKS_TIMER_DIV4_CLOCK EQU( 0x3 );
                                                          -( TC ) Clock selected:TIMER_DIV4_CLOCK
                                                          AT91C_TC_CLKS_TIMER_DIV5_CLOCK EQU( 0x4 );
                                                          -( TC ) Clock selected:TIMER_DIV5_CLOCK
                                                          AT91C_TC_CLKS_XC0 EQU( 0x5 );
                                                          -( TC ) Clock selected:XC0
                                                          AT91C_TC_CLKS_XC1 EQU( 0x6 );
                                                          -( TC ) Clock selected:XC1
                                                          AT91C_TC_CLKS_XC2 EQU( 0x7 );
                                                          -( TC ) Clock selected:XC2
                                                          AT91C_TC_CLKI EQU( 0x1 << 3 );
                                                          -( TC ) Clock Invert
                                                          AT91_C_TC_వ్యవధి EQU( 0x3 << 4 );
                                                          -( TC ) వ్యవధి Signal Selection
                                                          AT91_C_TC_వ్యవధి_NONE EQU( 0x0 << 4 );
                                                          -( TC ) The clock is not gated by an external సంకేతం
                                                          AT91_C_TC_వ్యవధి_XC0 EQU( 0x1 << 4 );
                                                          -( TC ) XC0 is ANDed with the selected clock
                                                          AT91_C_TC_వ్యవధి_XC1 EQU( 0x2 << 4 );
                                                          -( TC ) XC1 is ANDed with the selected clock
                                                          AT91_C_TC_వ్యవధి_XC2 EQU( 0x3 << 4 );
                                                          -( TC ) XC2 is ANDed with the selected clock
                                                          AT91C_TC_CPCSTOP EQU( 0x1 << 6 );
                                                          -( TC ) Counter Clock Stopped with RC Compare
                                                          AT91C_TC_LDBSTOP EQU( 0x1 << 6 );
                                                          -( TC ) Counter Clock Stopped with RB Loading
                                                          AT91C_TC_CPCDIS EQU( 0x1 << 7 );
                                                          -( TC ) Counter Clock Disable with RC Compare
                                                          AT91C_TC_LDBDIS EQU( 0x1 << 7 );
                                                          -( TC ) Counter Clock Disabled with RB Loading
                                                          AT91C_TC_ETRGEDG EQU( 0x3 << 8 );
                                                          -( TC ) External Trigger అంచు Selection
                                                          AT91C_TC_ETRGEDG_NONE EQU( 0x0 << 8 );
                                                          -( TC ) అంచు:None
                                                          AT91C_TC_ETRGEDG_RISING EQU( 0x1 << 8 );
                                                          -( TC ) అంచు:rising అంచు_2
                                                          AT91C_TC_ETRGEDG_FALLING EQU( 0x2 << 8 );
                                                          -( TC ) అంచు:falling అంచు_2
                                                          AT91C_TC_ETRGEDG_BOTH EQU( 0x3 << 8 );
                                                          -( TC ) అంచు:each అంచు_2
                                                          AT91C_TC_EEVTEDG EQU( 0x3 << 8 );
                                                          -( TC ) External Event అంచు Selection
                                                          AT91C_TC_EEVTEDG_NONE EQU( 0x0 << 8 );
                                                          -( TC ) అంచు:None
                                                          AT91C_TC_EEVTEDG_RISING EQU( 0x1 << 8 );
                                                          -( TC ) అంచు:rising అంచు_2
                                                          AT91C_TC_EEVTEDG_FALLING EQU( 0x2 << 8 );
                                                          -( TC ) అంచు:falling అంచు_2
                                                          AT91C_TC_EEVTEDG_BOTH EQU( 0x3 << 8 );
                                                          -( TC ) అంచు:each అంచు_2
                                                          AT91C_TC_EEVT EQU( 0x3 << 10 );
                                                          -( TC ) External Event Selection
                                                          AT91C_TC_EEVT_TIOB EQU( 0x0 << 10 );
                                                          -( TC ) Signal selected as external event:TIOB TIOB direction: ఆదానం_2
                                                          AT91C_TC_EEVT_XC0 EQU( 0x1 << 10 );
                                                          -( TC ) Signal selected as external event:XC0 TIOB direction: output
                                                          AT91C_TC_EEVT_XC1 EQU( 0x2 << 10 );
                                                          -( TC ) Signal selected as external event:XC1 TIOB direction: output
                                                          AT91C_TC_EEVT_XC2 EQU( 0x3 << 10 );
                                                          -( TC ) Signal selected as external event:XC2 TIOB direction: output
                                                          AT91C_TC_ABETRG EQU( 0x1 << 10 );
                                                          -( TC ) TIOA or TIOB External Trigger Selection
                                                          AT91C_TC_ENETRG EQU( 0x1 << 12 );
                                                          -( TC ) External Event Trigger enable
                                                          AT91C_TC_WAVESEL EQU( 0x3 << 13 );
                                                          -( TC ) Waveform Selection
                                                          AT91_C_TC_WAVESEL_పైకి EQU( 0x0 << 13 );
                                                          -( TC ) పైకి_3 బహుళకం_2 without atomatic trigger on RC Compare
                                                          AT91C_TC_WAVESEL_UPDOWN EQU( 0x1 << 13 );
                                                          -( TC ) UPDOWN బహుళకం_2 without automatic trigger on RC Compare
                                                          AT91_C_TC_WAVESEL_పైకి_AUTO EQU( 0x2 << 13 );
                                                          -( TC ) పైకి_3 బహుళకం_2 with automatic trigger on RC Compare
                                                          AT91C_TC_WAVESEL_UPDOWN_AUTO EQU( 0x3 << 13 );
                                                          -( TC ) UPDOWN బహుళకం_2 with automatic trigger on RC Compare
                                                          AT91C_TC_CPCTRG EQU( 0x1 << 14 );
                                                          -( TC ) RC Compare Trigger Enable
                                                          AT91C_TC_WAVE EQU( 0x1 << 15 );
                                                          -( TC )
                                                          AT91C_TC_ACPA EQU( 0x3 << 16 );
                                                          -( TC ) RA Compare Effect on TIOA
                                                          AT91C_TC_ACPA_NONE EQU( 0x0 << 16 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_ACPA_సమితి EQU( 0x1 << 16 );
                                                          -( TC ) Effect:సమితి
                                                          AT91C_TC_ACPA_CLEAR EQU( 0x2 << 16 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_ACPA_TOGGLE EQU( 0x3 << 16 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_LDRA EQU( 0x3 << 16 );
                                                          -( TC ) RA Loading Selection
                                                          AT91C_TC_LDRA_NONE EQU( 0x0 << 16 );
                                                          -( TC ) అంచు:None
                                                          AT91C_TC_LDRA_RISING EQU( 0x1 << 16 );
                                                          -( TC ) అంచు:rising అంచు_2 యొక్క TIOA
                                                          AT91C_TC_LDRA_FALLING EQU( 0x2 << 16 );
                                                          -( TC ) అంచు:falling అంచు_2 యొక్క TIOA
                                                          AT91C_TC_LDRA_BOTH EQU( 0x3 << 16 );
                                                          -( TC ) అంచు:each అంచు_2 యొక్క TIOA
                                                          AT91C_TC_ACPC EQU( 0x3 << 18 );
                                                          -( TC ) RC Compare Effect on TIOA
                                                          AT91C_TC_ACPC_NONE EQU( 0x0 << 18 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_ACPC_సమితి EQU( 0x1 << 18 );
                                                          -( TC ) Effect:సమితి
                                                          AT91C_TC_ACPC_CLEAR EQU( 0x2 << 18 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_ACPC_TOGGLE EQU( 0x3 << 18 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_LDRB EQU( 0x3 << 18 );
                                                          -( TC ) RB Loading Selection
                                                          AT91C_TC_LDRB_NONE EQU( 0x0 << 18 );
                                                          -( TC ) అంచు:None
                                                          AT91C_TC_LDRB_RISING EQU( 0x1 << 18 );
                                                          -( TC ) అంచు:rising అంచు_2 యొక్క TIOA
                                                          AT91C_TC_LDRB_FALLING EQU( 0x2 << 18 );
                                                          -( TC ) అంచు:falling అంచు_2 యొక్క TIOA
                                                          AT91C_TC_LDRB_BOTH EQU( 0x3 << 18 );
                                                          -( TC ) అంచు:each అంచు_2 యొక్క TIOA
                                                          AT91C_TC_AEEVT EQU( 0x3 << 20 );
                                                          -( TC ) External Event Effect on TIOA
                                                          AT91C_TC_AEEVT_NONE EQU( 0x0 << 20 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_AEEVT_సమితి EQU( 0x1 << 20 );
                                                          -( TC ) Effect:సమితి
                                                          AT91C_TC_AEEVT_CLEAR EQU( 0x2 << 20 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_AEEVT_TOGGLE EQU( 0x3 << 20 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_ASWTRG EQU( 0x3 << 22 );
                                                          -( TC ) Software Trigger Effect on TIOA
                                                          AT91C_TC_ASWTRG_NONE EQU( 0x0 << 22 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_ASWTRG_సమితి EQU( 0x1 << 22 );
                                                          -( TC ) Effect:సమితి
                                                          AT91C_TC_ASWTRG_CLEAR EQU( 0x2 << 22 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_ASWTRG_TOGGLE EQU( 0x3 << 22 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_BCPB EQU( 0x3 << 24 );
                                                          -( TC ) RB Compare Effect on TIOB
                                                          AT91C_TC_BCPB_NONE EQU( 0x0 << 24 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_BCPB_సమితి EQU( 0x1 << 24 );
                                                          -( TC ) Effect:సమితి
                                                          AT91C_TC_BCPB_CLEAR EQU( 0x2 << 24 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_BCPB_TOGGLE EQU( 0x3 << 24 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_BCPC EQU( 0x3 << 26 );
                                                          -( TC ) RC Compare Effect on TIOB
                                                          AT91C_TC_BCPC_NONE EQU( 0x0 << 26 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_BCPC_సమితి EQU( 0x1 << 26 );
                                                          -( TC ) Effect:సమితి
                                                          AT91C_TC_BCPC_CLEAR EQU( 0x2 << 26 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_BCPC_TOGGLE EQU( 0x3 << 26 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_BEEVT EQU( 0x3 << 28 );
                                                          -( TC ) External Event Effect on TIOB
                                                          AT91C_TC_BEEVT_NONE EQU( 0x0 << 28 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_BEEVT_సమితి EQU( 0x1 << 28 );
                                                          -( TC ) Effect:సమితి
                                                          AT91C_TC_BEEVT_CLEAR EQU( 0x2 << 28 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_BEEVT_TOGGLE EQU( 0x3 << 28 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_BSWTRG EQU( 0x3 << 30 );
                                                          -( TC ) Software Trigger Effect on TIOB
                                                          AT91C_TC_BSWTRG_NONE EQU( 0x0 << 30 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_BSWTRG_సమితి EQU( 0x1 << 30 );
                                                          -( TC ) Effect:సమితి
                                                          AT91C_TC_BSWTRG_CLEAR EQU( 0x2 << 30 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_BSWTRG_TOGGLE EQU( 0x3 << 30 );
                                                          -( TC ) Effect:toggle
/* - -------- TC_SR : (TC Offset: 0x20) TC Channel Status Register -------- */
                                                          AT91C_TC_COVFS EQU( 0x1 << 0 );
                                                          -( TC ) Counter అధికప్రవాహం_2
                                                          AT91C_TC_LOVRS EQU( 0x1 << 1 );
                                                          -( TC ) ఎక్కించు Overrun
                                                          AT91C_TC_CPAS EQU( 0x1 << 2 );
                                                          -( TC ) RA Compare
                                                          AT91C_TC_CPBS EQU( 0x1 << 3 );
                                                          -( TC ) RB Compare
                                                          AT91C_TC_CPCS EQU( 0x1 << 4 );
                                                          -( TC ) RC Compare
                                                          AT91C_TC_LDRAS EQU( 0x1 << 5 );
                                                          -( TC ) RA Loading
                                                          AT91C_TC_LDRBS EQU( 0x1 << 6 );
                                                          -( TC ) RB Loading
                                                          AT91C_TC_ETRGS EQU( 0x1 << 7 );
                                                          -( TC ) External Trigger
                                                          AT91C_TC_CLKSTA EQU( 0x1 << 16 );
                                                          -( TC ) Clock Enabling
                                                          AT91C_TC_MTIOA EQU( 0x1 << 17 );
                                                          -( TC ) TIOA Mirror
                                                          AT91C_TC_MTIOB EQU( 0x1 << 18 );
                                                          -( TC ) TIOA Mirror
/* - -------- TC_IER : (TC Offset: 0x24) TC Channel Interrupt Enable Register -------- */
/* - -------- TC_IDR : (TC Offset: 0x28) TC Channel Interrupt Disable Register -------- */
/* - -------- TC_IMR : (TC Offset: 0x2c) TC Channel Interrupt Mask Register -------- */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Timer Counter Interface */
/* - ***************************************************************************** */
/* - -------- TCB_BCR : (TCB Offset: 0xc0) TC Block Control Register -------- */
                                                          AT91C_TCB_SYNC EQU( 0x1 << 0 );
                                                          -( TCB ) Synchro Command
/* - -------- TCB_BMR : (TCB Offset: 0xc4) TC Block Mode Register -------- */
                                                          AT91C_TCB_TC0XC0S EQU( 0x3 << 0 );
                                                          -( TCB ) External Clock Signal 0 Selection
                                                          AT91C_TCB_TC0XC0S_TCLK0 EQU( 0x0 );
                                                          -( TCB ) TCLK0 connected గమ్యం XC0
                                                          AT91C_TCB_TC0XC0S_NONE EQU( 0x1 );
                                                          -( TCB ) None సంకేతం connected గమ్యం XC0
                                                          AT91C_TCB_TC0XC0S_TIOA1 EQU( 0x2 );
                                                          -( TCB ) TIOA1 connected గమ్యం XC0
                                                          AT91C_TCB_TC0XC0S_TIOA2 EQU( 0x3 );
                                                          -( TCB ) TIOA2 connected గమ్యం XC0
                                                          AT91C_TCB_TC1XC1S EQU( 0x3 << 2 );
                                                          -( TCB ) External Clock Signal 1 Selection
                                                          AT91C_TCB_TC1XC1S_TCLK1 EQU( 0x0 << 2 );
                                                          -( TCB ) TCLK1 connected గమ్యం XC1
                                                          AT91C_TCB_TC1XC1S_NONE EQU( 0x1 << 2 );
                                                          -( TCB ) None సంకేతం connected గమ్యం XC1
                                                          AT91C_TCB_TC1XC1S_TIOA0 EQU( 0x2 << 2 );
                                                          -( TCB ) TIOA0 connected గమ్యం XC1
                                                          AT91C_TCB_TC1XC1S_TIOA2 EQU( 0x3 << 2 );
                                                          -( TCB ) TIOA2 connected గమ్యం XC1
                                                          AT91C_TCB_TC2XC2S EQU( 0x3 << 4 );
                                                          -( TCB ) External Clock Signal 2 Selection
                                                          AT91C_TCB_TC2XC2S_TCLK2 EQU( 0x0 << 4 );
                                                          -( TCB ) TCLK2 connected గమ్యం XC2
                                                          AT91C_TCB_TC2XC2S_NONE EQU( 0x1 << 4 );
                                                          -( TCB ) None సంకేతం connected గమ్యం XC2
                                                          AT91C_TCB_TC2XC2S_TIOA0 EQU( 0x2 << 4 );
                                                          -( TCB ) TIOA0 connected గమ్యం XC2
                                                          AT91C_TCB_TC2XC2S_TIOA1 EQU( 0x3 << 4 );
                                                          -( TCB ) TIOA2 connected గమ్యం XC2

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Control Area Network MailBox Interface */
/* - ***************************************************************************** */
/* - -------- CAN_MMR : (CAN_MB Offset: 0x0) CAN Message Mode Register -------- */
                                                          AT91C_CAN_MTIMEMARK EQU( 0xFFFF << 0 );
                                                          -( CAN_MB ) Mailbox Timemark
                                                          AT91_C_CAN_పూర్వ EQU( 0xF << 16 );
                                                          -( CAN_MB ) Mailbox ప్రాధాన్యత_2
                                                          AT91C_CAN_MOT EQU( 0x7 << 24 );
                                                          -( CAN_MB ) Mailbox Object Type
                                                          AT91C_CAN_MOT_DIS EQU( 0x0 << 24 );
                                                          -( CAN_MB )
                                                          AT91C_CAN_MOT_RX EQU( 0x1 << 24 );
                                                          -( CAN_MB )
                                                          AT91C_CAN_MOT_RXOVERWRITE EQU( 0x2 << 24 );
                                                          -( CAN_MB )
                                                          AT91C_CAN_MOT_TX EQU( 0x3 << 24 );
                                                          -( CAN_MB )
                                                          AT91_C_CAN_MOT_వినియోగదారు EQU( 0x4 << 24 );
                                                          -( CAN_MB )
                                                          AT91_C_CAN_MOT_ఉత్పాదకుడు EQU( 0x5 << 24 );
                                                          -( CAN_MB )
/* - -------- CAN_MAM : (CAN_MB Offset: 0x4) CAN Message Acceptance Mask Register -------- */
                                                          AT91C_CAN_MIDvB EQU( 0x3FFFF << 0 );
                                                          -( CAN_MB ) Complementary బిట్లు_2

                                                          కొరకు identifier లోపల extended బహుళకం_2
                                                          AT91C_CAN_MIDvA EQU( 0x7FF << 18 );
                                                          -( CAN_MB ) Identifier

                                                          కొరకు standard చట్రం_2 బహుళకం_2
                                                          AT91C_CAN_MIDE EQU( 0x1 << 29 );
                                                          -( CAN_MB ) Identifier సంస్కరణ_2
/* - -------- CAN_MID : (CAN_MB Offset: 0x8) CAN Message ID Register -------- */
/* - -------- CAN_MFID : (CAN_MB Offset: 0xc) CAN Message Family ID Register -------- */
/* - -------- CAN_MSR : (CAN_MB Offset: 0x10) CAN Message Status Register -------- */
                                                          AT91C_CAN_MTIMESTAMP EQU( 0xFFFF << 0 );
                                                          -( CAN_MB ) Timer విలువ_2
                                                          AT91C_CAN_MDLC EQU( 0xF << 16 );
                                                          -( CAN_MB ) Mailbox దత్తాంశం నిడివి సంకేతం_3
                                                          AT91C_CAN_MRTR EQU( 0x1 << 20 );
                                                          -( CAN_MB ) Mailbox Remote సంప్రేషణ Request
                                                          AT91C_CAN_MABT EQU( 0x1 << 22 );
                                                          -( CAN_MB ) Mailbox సందేశం Abort
                                                          AT91C_CAN_MRDY EQU( 0x1 << 23 );
                                                          -( CAN_MB ) Mailbox Ready
                                                          AT91C_CAN_MMI EQU( 0x1 << 24 );
                                                          -( CAN_MB ) Mailbox సందేశం Ignored
/* - -------- CAN_MDL : (CAN_MB Offset: 0x14) CAN Message Data Low Register -------- */
/* - -------- CAN_MDH : (CAN_MB Offset: 0x18) CAN Message Data High Register -------- */
/* - -------- CAN_MCR : (CAN_MB Offset: 0x1c) CAN Message Control Register -------- */
                                                          AT91C_CAN_MACR EQU( 0x1 << 22 );
                                                          -( CAN_MB ) Abort Request

                                                          కొరకు Mailbox
                                                          AT91C_CAN_MTCR EQU( 0x1 << 23 );
                                                          -( CAN_MB ) Mailbox Transfer Command

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Control Area Network Interface */
/* - ***************************************************************************** */
/* - -------- CAN_MR : (CAN Offset: 0x0) CAN Mode Register -------- */
                                                          AT91C_CAN_CANEN EQU( 0x1 << 0 );
                                                          -( CAN ) CAN Controller Enable
                                                          AT91C_CAN_LPM EQU( 0x1 << 1 );
                                                          -( CAN ) Disable / Enable దిగువ Power బహుళకం
                                                          AT91C_CAN_ABM EQU( 0x1 << 2 );
                                                          -( CAN ) Disable / Enable Autobaud / Listen బహుళకం
                                                          AT91C_CAN_OVL EQU( 0x1 << 3 );
                                                          -( CAN ) Disable / Enable Overload చట్రం
                                                          AT91C_CAN_TEOF EQU( 0x1 << 4 );
                                                          -( CAN ) సమయం Stamp messages at each చివర యొక్క చట్రం
                                                          AT91C_CAN_TTM EQU( 0x1 << 5 );
                                                          -( CAN ) Disable / Enable సమయం Trigger బహుళకం
                                                          AT91C_CAN_TIMFRZ EQU( 0x1 << 6 );
                                                          -( CAN ) Enable Timer Freeze
                                                          AT91C_CAN_DRPT EQU( 0x1 << 7 );
                                                          -( CAN ) Disable Repeat
/* - -------- CAN_IER : (CAN Offset: 0x4) CAN Interrupt Enable Register -------- */
                                                          AT91C_CAN_MB0 EQU( 0x1 << 0 );
                                                          -( CAN ) Mailbox 0 Flag
                                                          AT91C_CAN_MB1 EQU( 0x1 << 1 );
                                                          -( CAN ) Mailbox 1 Flag
                                                          AT91C_CAN_MB2 EQU( 0x1 << 2 );
                                                          -( CAN ) Mailbox 2 Flag
                                                          AT91C_CAN_MB3 EQU( 0x1 << 3 );
                                                          -( CAN ) Mailbox 3 Flag
                                                          AT91C_CAN_MB4 EQU( 0x1 << 4 );
                                                          -( CAN ) Mailbox 4 Flag
                                                          AT91C_CAN_MB5 EQU( 0x1 << 5 );
                                                          -( CAN ) Mailbox 5 Flag
                                                          AT91C_CAN_MB6 EQU( 0x1 << 6 );
                                                          -( CAN ) Mailbox 6 Flag
                                                          AT91C_CAN_MB7 EQU( 0x1 << 7 );
                                                          -( CAN ) Mailbox 7 Flag
                                                          AT91C_CAN_MB8 EQU( 0x1 << 8 );
                                                          -( CAN ) Mailbox 8 Flag
                                                          AT91C_CAN_MB9 EQU( 0x1 << 9 );
                                                          -( CAN ) Mailbox 9 Flag
                                                          AT91C_CAN_MB10 EQU( 0x1 << 10 );
                                                          -( CAN ) Mailbox 10 Flag
                                                          AT91C_CAN_MB11 EQU( 0x1 << 11 );
                                                          -( CAN ) Mailbox 11 Flag
                                                          AT91C_CAN_MB12 EQU( 0x1 << 12 );
                                                          -( CAN ) Mailbox 12 Flag
                                                          AT91C_CAN_MB13 EQU( 0x1 << 13 );
                                                          -( CAN ) Mailbox 13 Flag
                                                          AT91C_CAN_MB14 EQU( 0x1 << 14 );
                                                          -( CAN ) Mailbox 14 Flag
                                                          AT91C_CAN_MB15 EQU( 0x1 << 15 );
                                                          -( CAN ) Mailbox 15 Flag
                                                          AT91C_CAN_ERRA EQU( 0x1 << 16 );
                                                          -( CAN ) Error చురుకైన బహుళకం Flag
                                                          AT91C_CAN_WARN EQU( 0x1 << 17 );
                                                          -( CAN ) Warning హద్దు Flag
                                                          AT91C_CAN_ERRP EQU( 0x1 << 18 );
                                                          -( CAN ) Error Passive బహుళకం Flag
                                                          AT91C_CAN_BOFF EQU( 0x1 << 19 );
                                                          -( CAN ) Bus Off బహుళకం Flag
                                                          AT91C_CAN_SLEEP EQU( 0x1 << 20 );
                                                          -( CAN ) Sleep Flag
                                                          AT91C_CAN_WAKEUP EQU( 0x1 << 21 );
                                                          -( CAN ) Wakeup Flag
                                                          AT91C_CAN_TOVF EQU( 0x1 << 22 );
                                                          -( CAN ) Timer అధికప్రవాహం_2 Flag
                                                          AT91C_CAN_TSTP EQU( 0x1 << 23 );
                                                          -( CAN ) Timestamp Flag
                                                          AT91C_CAN_CERR EQU( 0x1 << 24 );
                                                          -( CAN ) చక్రీయ_తనిఖీ Error
                                                          AT91C_CAN_SERR EQU( 0x1 << 25 );
                                                          -( CAN ) Stuffing Error
                                                          AT91C_CAN_AERR EQU( 0x1 << 26 );
                                                          -( CAN ) Acknowledgment Error
                                                          AT91C_CAN_FERR EQU( 0x1 << 27 );
                                                          -( CAN ) Form Error
                                                          AT91C_CAN_BERR EQU( 0x1 << 28 );
                                                          -( CAN ) బిట్టు Error
/* - -------- CAN_IDR : (CAN Offset: 0x8) CAN Interrupt Disable Register -------- */
/* - -------- CAN_IMR : (CAN Offset: 0xc) CAN Interrupt Mask Register -------- */
/* - -------- CAN_SR : (CAN Offset: 0x10) CAN Status Register -------- */
                                                          AT91C_CAN_RBSY EQU( 0x1 << 29 );
                                                          -( CAN ) Receiver Busy
                                                          AT91C_CAN_TBSY EQU( 0x1 << 30 );
                                                          -( CAN ) Transmitter Busy
                                                          AT91C_CAN_OVLY EQU( 0x1 << 31 );
                                                          -( CAN ) Overload Busy
/* - -------- CAN_BR : (CAN Offset: 0x14) CAN Baudrate Register -------- */
                                                          AT91C_CAN_PHASE2 EQU( 0x7 << 0 );
                                                          -( CAN ) Phase 2 segment
                                                          AT91C_CAN_PHASE1 EQU( 0x7 << 4 );
                                                          -( CAN ) Phase 1 segment
                                                          AT91C_CAN_PROPAG EQU( 0x7 << 8 );
                                                          -( CAN ) Programmation time segment
                                                          AT91C_CAN_SYNC EQU( 0x3 << 12 );
                                                          -( CAN ) Re - synchronization jump వెడల్పు segment
                                                          AT91C_CAN_BRP EQU( 0x7F << 16 );
                                                          -( CAN ) Baudrate Prescaler
                                                          AT91C_CAN_SMP EQU( 0x1 << 24 );
                                                          -( CAN ) Sampling బహుళకం_2
/* - -------- CAN_TIM : (CAN Offset: 0x18) CAN Timer Register -------- */
                                                          AT91C_CAN_TIMER EQU( 0xFFFF << 0 );
                                                          -( CAN ) Timer క్షేత్రం
/* - -------- CAN_TIMESTP : (CAN Offset: 0x1c) CAN Timestamp Register -------- */
/* - -------- CAN_ECR : (CAN Offset: 0x20) CAN Error Counter Register -------- */
                                                          AT91C_CAN_REC EQU( 0xFF << 0 );
                                                          -( CAN ) Receive Error Counter
                                                          AT91C_CAN_TEC EQU( 0xFF << 16 );
                                                          -( CAN ) Transmit Error Counter
/* - -------- CAN_TCR : (CAN Offset: 0x24) CAN Transfer Command Register -------- */
                                                          AT91C_CAN_TIMRST EQU( 0x1 << 31 );
                                                          -( CAN ) Timer Reset క్షేత్రం_2
/* - -------- CAN_ACR : (CAN Offset: 0x28) CAN Abort Command Register -------- */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Ethernet MAC 10/100 */
/* - ***************************************************************************** */
/* - -------- EMAC_NCR : (EMAC Offset: 0x0)  -------- */
                                                          AT91C_EMAC_LB EQU( 0x1 << 0 );
                                                          -( EMAC ) Loopback.Optional.When సమితి, loopback సంకేతం is at ఎగువ_2 level.
                                                             AT91C_EMAC_LLB EQU( 0x1 << 1 );
                                                          -( EMAC ) Loopback local.
                                                             AT91C_EMAC_RE EQU( 0x1 << 2 );
                                                          -( EMAC ) Receive enable.
                                                             AT91C_EMAC_TE EQU( 0x1 << 3 );
                                                          -( EMAC ) Transmit enable.
                                                             AT91C_EMAC_MPE EQU( 0x1 << 4 );
                                                          -( EMAC ) Management పోర్టు enable.
                                                             AT91C_EMAC_CLRSTAT EQU( 0x1 << 5 );
                                                          -( EMAC ) Clear statistics registers.
                                                             AT91C_EMAC_INCSTAT EQU( 0x1 << 6 );
                                                          -( EMAC ) Increment statistics registers.
                                                             AT91C_EMAC_WESTAT EQU( 0x1 << 7 );
                                                          -( EMAC ) Write enable

                                                          కొరకు statistics registers.
                                                             AT91C_EMAC_BP EQU( 0x1 << 8 );
                                                          -( EMAC ) వెనుక pressure.
                                                             AT91C_EMAC_TSTART EQU( 0x1 << 9 );
                                                          -( EMAC ) ప్రారంభం_2 సంప్రేషణ.
                                                             AT91C_EMAC_THALT EQU( 0x1 << 10 );
                                                          -( EMAC ) సంప్రేషణ Halt.
                                                             AT91C_EMAC_TPFR EQU( 0x1 << 11 );
                                                          -( EMAC ) Transmit pause చట్రం_2
                                                          AT91C_EMAC_TZQ EQU( 0x1 << 12 );
                                                          -( EMAC ) Transmit zero కాలాంశం pause చట్రం_2
/* - -------- EMAC_NCFGR : (EMAC Offset: 0x4) Network Configuration Register -------- */
                                                          AT91C_EMAC_SPD EQU( 0x1 << 0 );
                                                          -( EMAC ) వేగం.
                                                             AT91C_EMAC_FD EQU( 0x1 << 1 );
                                                          -( EMAC ) నిండిన duplex.
                                                             AT91C_EMAC_JFRAME EQU( 0x1 << 3 );
                                                          -( EMAC ) Jumbo చట్రాలు.
                                                             AT91C_EMAC_CAF EQU( 0x1 << 4 );
                                                          -( EMAC ) Copy all చట్రాలు_2.
                                                             AT91C_EMAC_NBC EQU( 0x1 << 5 );
                                                          -( EMAC ) No ప్రసారం.
                                                             AT91C_EMAC_MTI EQU( 0x1 << 6 );
                                                          -( EMAC ) Multicast hash event enable
                                                          AT91C_EMAC_UNI EQU( 0x1 << 7 );
                                                          -( EMAC ) Unicast hash enable.
                                                             AT91C_EMAC_BIG EQU( 0x1 << 8 );
                                                          -( EMAC ) Receive 1522 బైట్లు_2.
                                                             AT91C_EMAC_EAE EQU( 0x1 << 9 );
                                                          -( EMAC ) External చిరునామా_2 సరిపోలిక enable.
                                                             AT91C_EMAC_CLK EQU( 0x3 << 10 );
                                                          -( EMAC )
                                                          AT91C_EMAC_CLK_HCLK_8 EQU( 0x0 << 10 );
                                                          -( EMAC ) HCLK divided by 8
                                                          AT91C_EMAC_CLK_HCLK_16 EQU( 0x1 << 10 );
                                                          -( EMAC ) HCLK divided by 16
                                                          AT91C_EMAC_CLK_HCLK_32 EQU( 0x2 << 10 );
                                                          -( EMAC ) HCLK divided by 32
                                                          AT91C_EMAC_CLK_HCLK_64 EQU( 0x3 << 10 );
                                                          -( EMAC ) HCLK divided by 64
                                                          AT91C_EMAC_RTY EQU( 0x1 << 12 );
                                                          -( EMAC )
                                                          AT91C_EMAC_PAE EQU( 0x1 << 13 );
                                                          -( EMAC )
                                                          AT91C_EMAC_RBOF EQU( 0x3 << 14 );
                                                          -( EMAC )
                                                          AT91_C_EMAC_RBOF_స్థానభ్రంశం_0 EQU( 0x0 << 14 );
                                                          -( EMAC ) no offset from ప్రారంభం యొక్క receive బఫరు_2
                                                          AT91_C_EMAC_RBOF_స్థానభ్రంశం_1 EQU( 0x1 << 14 );
                                                          -( EMAC ) one byte offset from ప్రారంభం యొక్క receive బఫరు_2
                                                          AT91_C_EMAC_RBOF_స్థానభ్రంశం_2 EQU( 0x2 << 14 );
                                                          -( EMAC ) two బైట్లు_2 offset from ప్రారంభం యొక్క receive బఫరు_2
                                                          AT91_C_EMAC_RBOF_స్థానభ్రంశం_3 EQU( 0x3 << 14 );
                                                          -( EMAC ) three బైట్లు_2 offset from ప్రారంభం యొక్క receive బఫరు_2
                                                          AT91C_EMAC_RLCE EQU( 0x1 << 16 );
                                                          -( EMAC ) Receive నిడివి క్షేత్రం Checking Enable
                                                          AT91C_EMAC_DRFCS EQU( 0x1 << 17 );
                                                          -( EMAC ) Discard Receive FCS
                                                          AT91C_EMAC_EFRHD EQU( 0x1 << 18 );
                                                          -( EMAC )
                                                          AT91C_EMAC_IRXFCS EQU( 0x1 << 19 );
                                                          -( EMAC ) Ignore RX FCS
/* - -------- EMAC_NSR : (EMAC Offset: 0x8) Network Status Register -------- */
                                                          AT91C_EMAC_LINKR EQU( 0x1 << 0 );
                                                          -( EMAC )
                                                          AT91C_EMAC_MDIO EQU( 0x1 << 1 );
                                                          -( EMAC )
                                                          AT91C_EMAC_IDLE EQU( 0x1 << 2 );
                                                          -( EMAC )
/* - -------- EMAC_TSR : (EMAC Offset: 0x14) Transmit Status Register -------- */
                                                          AT91C_EMAC_UBR EQU( 0x1 << 0 );
                                                          -( EMAC )
                                                          AT91_C_EMAC_నిలువు EQU( 0x1 << 1 );
                                                          -( EMAC )
                                                          AT91C_EMAC_RLES EQU( 0x1 << 2 );
                                                          -( EMAC )
                                                          AT91C_EMAC_TGO EQU( 0x1 << 3 );
                                                          -( EMAC ) Transmit Go
                                                          AT91C_EMAC_BEX EQU( 0x1 << 4 );
                                                          -( EMAC ) Buffers exhausted mid చట్రం_2
                                                          AT91C_EMAC_COMP EQU( 0x1 << 5 );
                                                          -( EMAC )
                                                          AT91C_EMAC_UND EQU( 0x1 << 6 );
                                                          -( EMAC )
/* - -------- EMAC_RSR : (EMAC Offset: 0x20) Receive Status Register -------- */
                                                          AT91C_EMAC_BNA EQU( 0x1 << 0 );
                                                          -( EMAC )
                                                          AT91C_EMAC_REC EQU( 0x1 << 1 );
                                                          -( EMAC )
                                                          AT91C_EMAC_OVR EQU( 0x1 << 2 );
                                                          -( EMAC )
/* - -------- EMAC_ISR : (EMAC Offset: 0x24) Interrupt Status Register -------- */
                                                          AT91C_EMAC_MFD EQU( 0x1 << 0 );
                                                          -( EMAC )
                                                          AT91C_EMAC_RCOMP EQU( 0x1 << 1 );
                                                          -( EMAC )
                                                          AT91C_EMAC_RXUBR EQU( 0x1 << 2 );
                                                          -( EMAC )
                                                          AT91C_EMAC_TXUBR EQU( 0x1 << 3 );
                                                          -( EMAC )
                                                          AT91C_EMAC_TUNDR EQU( 0x1 << 4 );
                                                          -( EMAC )
                                                          AT91C_EMAC_RLEX EQU( 0x1 << 5 );
                                                          -( EMAC )
                                                          AT91C_EMAC_TXERR EQU( 0x1 << 6 );
                                                          -( EMAC )
                                                          AT91C_EMAC_TCOMP EQU( 0x1 << 7 );
                                                          -( EMAC )
                                                          AT91C_EMAC_LINK EQU( 0x1 << 9 );
                                                          -( EMAC )
                                                          AT91C_EMAC_ROVR EQU( 0x1 << 10 );
                                                          -( EMAC )
                                                          AT91C_EMAC_HRESP EQU( 0x1 << 11 );
                                                          -( EMAC )
                                                          AT91C_EMAC_PFRE EQU( 0x1 << 12 );
                                                          -( EMAC )
                                                          AT91C_EMAC_PTZ EQU( 0x1 << 13 );
                                                          -( EMAC )
/* - -------- EMAC_IER : (EMAC Offset: 0x28) Interrupt Enable Register -------- */
/* - -------- EMAC_IDR : (EMAC Offset: 0x2c) Interrupt Disable Register -------- */
/* - -------- EMAC_IMR : (EMAC Offset: 0x30) Interrupt Mask Register -------- */
/* - -------- EMAC_MAN : (EMAC Offset: 0x34) PHY Maintenance Register -------- */
                                                          AT91_C_EMAC_దత్తాంశం EQU( 0xFFFF << 0 );
                                                          -( EMAC )
                                                          AT91_C_EMAC_సంకేతం EQU( 0x3 << 16 );
                                                          -( EMAC )
                                                          AT91C_EMAC_REGA EQU( 0x1F << 18 );
                                                          -( EMAC )
                                                          AT91C_EMAC_PHYA EQU( 0x1F << 23 );
                                                          -( EMAC )
                                                          AT91C_EMAC_RW EQU( 0x3 << 28 );
                                                          -( EMAC )
                                                          AT91C_EMAC_SOF EQU( 0x3 << 30 );
                                                          -( EMAC )
/* - -------- EMAC_USRIO : (EMAC Offset: 0xc0) USER Input Output Register -------- */
                                                          AT91C_EMAC_RMII EQU( 0x1 << 0 );
                                                          -( EMAC ) Reduce MII
/* - -------- EMAC_WOL : (EMAC Offset: 0xc4) Wake On LAN Register -------- */
                                                          AT91C_EMAC_IP EQU( 0xFFFF << 0 );
                                                          -( EMAC ) ARP request IP చిరునామా_2
                                                          AT91C_EMAC_MAG EQU( 0x1 << 16 );
                                                          -( EMAC ) Magic packet event enable
                                                          AT91C_EMAC_ARP EQU( 0x1 << 17 );
                                                          -( EMAC ) ARP request event enable
                                                          AT91C_EMAC_SA1 EQU( 0x1 << 18 );
                                                          -( EMAC ) Specific చిరునామా_2 నమోదు 1 event enable
/* - -------- EMAC_REV : (EMAC Offset: 0xfc) Revision Register -------- */
                                                          AT91C_EMAC_REVREF EQU( 0xFFFF << 0 );
                                                          -( EMAC )
                                                          AT91C_EMAC_PARTREF EQU( 0xFFFF << 16 );
                                                          -( EMAC )

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Analog to Digital Convertor */
/* - ***************************************************************************** */
/* - -------- ADC_CR : (ADC Offset: 0x0) ADC Control Register -------- */
                                                          AT91C_ADC_SWRST EQU( 0x1 << 0 );
                                                          -( ADC ) Software Reset
                                                          AT91_C_ADC_ప్రారంభం EQU( 0x1 << 1 );
                                                          -( ADC ) ప్రారంభం_2 Conversion
/* - -------- ADC_MR : (ADC Offset: 0x4) ADC Mode Register -------- */
                                                          AT91C_ADC_TRGEN EQU( 0x1 << 0 );
                                                          -( ADC ) Trigger Enable
                                                          AT91C_ADC_TRGEN_DIS EQU( 0x0 );
                                                          -( ADC ) Hardware triggers are disabled.Starting a conversion is only possible by software
                                                          AT91C_ADC_TRGEN_EN EQU( 0x1 );
                                                          -( ADC ) Hardware trigger selected by TRGSEL క్షేత్రం is enabled.
                                                             AT91C_ADC_TRGSEL EQU( 0x7 << 1 );
                                                          -( ADC ) Trigger Selection
                                                          AT91C_ADC_TRGSEL_TIOA0 EQU( 0x0 << 1 );
                                                          -( ADC ) Selected TRGSEL = TIAO0
                                                                                     AT91C_ADC_TRGSEL_TIOA1 EQU( 0x1 << 1 );
                                                          -( ADC ) Selected TRGSEL = TIAO1
                                                                                     AT91C_ADC_TRGSEL_TIOA2 EQU( 0x2 << 1 );
                                                          -( ADC ) Selected TRGSEL = TIAO2
                                                                                     AT91C_ADC_TRGSEL_TIOA3 EQU( 0x3 << 1 );
                                                          -( ADC ) Selected TRGSEL = TIAO3
                                                                                     AT91C_ADC_TRGSEL_TIOA4 EQU( 0x4 << 1 );
                                                          -( ADC ) Selected TRGSEL = TIAO4
                                                                                     AT91C_ADC_TRGSEL_TIOA5 EQU( 0x5 << 1 );
                                                          -( ADC ) Selected TRGSEL = TIAO5
                                                                                     AT91C_ADC_TRGSEL_EXT EQU( 0x6 << 1 );
                                                          -( ADC ) Selected TRGSEL = External Trigger
                                                                                     AT91C_ADC_LOWRES EQU( 0x1 << 4 );
                                                          -( ADC ) Resolution.
                                                             AT91_C_ADC_LOWRES_10_బిట్టు EQU( 0x0 << 4 );
                                                          -( ADC ) 10 - బిట్టు_2 resolution
                                                          AT91_C_ADC_LOWRES_8_బిట్టు EQU( 0x1 << 4 );
                                                          -( ADC ) 8 - బిట్టు_2 resolution
                                                          AT91C_ADC_SLEEP EQU( 0x1 << 5 );
                                                          -( ADC ) Sleep బహుళకం
                                                          AT91_C_ADC_SLEEP_సాధారణ_బహుళకం EQU( 0x0 << 5 );
                                                          -( ADC ) సాధారణ బహుళకం
                                                          AT91_C_ADC_SLEEP_బహుళకం EQU( 0x1 << 5 );
                                                          -( ADC ) Sleep బహుళకం
                                                          AT91C_ADC_PRESCAL EQU( 0x3F << 8 );
                                                          -( ADC ) Prescaler రేటు_2 selection
                                                          AT91C_ADC_STARTUP EQU( 0x1F << 16 );
                                                          -( ADC ) Startup సమయం
                                                          AT91C_ADC_SHTIM EQU( 0xF << 24 );
                                                          -( ADC ) Sample & Hold సమయం
/* - --------   ADC_CHER : (ADC Offset: 0x10) ADC Channel Enable Register -------- */
                                                          AT91C_ADC_CH0 EQU( 0x1 << 0 );
                                                          -( ADC ) Channel 0
                                                          AT91C_ADC_CH1 EQU( 0x1 << 1 );
                                                          -( ADC ) Channel 1
                                                          AT91C_ADC_CH2 EQU( 0x1 << 2 );
                                                          -( ADC ) Channel 2
                                                          AT91C_ADC_CH3 EQU( 0x1 << 3 );
                                                          -( ADC ) Channel 3
                                                          AT91C_ADC_CH4 EQU( 0x1 << 4 );
                                                          -( ADC ) Channel 4
                                                          AT91C_ADC_CH5 EQU( 0x1 << 5 );
                                                          -( ADC ) Channel 5
                                                          AT91C_ADC_CH6 EQU( 0x1 << 6 );
                                                          -( ADC ) Channel 6
                                                          AT91C_ADC_CH7 EQU( 0x1 << 7 );
                                                          -( ADC ) Channel 7
/* - --------   ADC_CHDR : (ADC Offset: 0x14) ADC Channel Disable Register -------- */
/* - --------   ADC_CHSR : (ADC Offset: 0x18) ADC Channel Status Register -------- */
/* - -------- ADC_SR : (ADC Offset: 0x1c) ADC Status Register -------- */
                                                          AT91C_ADC_EOC0 EQU( 0x1 << 0 );
                                                          -( ADC ) చివర_2 యొక్క Conversion
                                                          AT91C_ADC_EOC1 EQU( 0x1 << 1 );
                                                          -( ADC ) చివర_2 యొక్క Conversion
                                                          AT91C_ADC_EOC2 EQU( 0x1 << 2 );
                                                          -( ADC ) చివర_2 యొక్క Conversion
                                                          AT91C_ADC_EOC3 EQU( 0x1 << 3 );
                                                          -( ADC ) చివర_2 యొక్క Conversion
                                                          AT91C_ADC_EOC4 EQU( 0x1 << 4 );
                                                          -( ADC ) చివర_2 యొక్క Conversion
                                                          AT91C_ADC_EOC5 EQU( 0x1 << 5 );
                                                          -( ADC ) చివర_2 యొక్క Conversion
                                                          AT91C_ADC_EOC6 EQU( 0x1 << 6 );
                                                          -( ADC ) చివర_2 యొక్క Conversion
                                                          AT91C_ADC_EOC7 EQU( 0x1 << 7 );
                                                          -( ADC ) చివర_2 యొక్క Conversion
                                                          AT91C_ADC_OVRE0 EQU( 0x1 << 8 );
                                                          -( ADC ) Overrun Error
                                                          AT91C_ADC_OVRE1 EQU( 0x1 << 9 );
                                                          -( ADC ) Overrun Error
                                                          AT91C_ADC_OVRE2 EQU( 0x1 << 10 );
                                                          -( ADC ) Overrun Error
                                                          AT91C_ADC_OVRE3 EQU( 0x1 << 11 );
                                                          -( ADC ) Overrun Error
                                                          AT91C_ADC_OVRE4 EQU( 0x1 << 12 );
                                                          -( ADC ) Overrun Error
                                                          AT91C_ADC_OVRE5 EQU( 0x1 << 13 );
                                                          -( ADC ) Overrun Error
                                                          AT91C_ADC_OVRE6 EQU( 0x1 << 14 );
                                                          -( ADC ) Overrun Error
                                                          AT91C_ADC_OVRE7 EQU( 0x1 << 15 );
                                                          -( ADC ) Overrun Error
                                                          AT91C_ADC_DRDY EQU( 0x1 << 16 );
                                                          -( ADC ) దత్తాంశం Ready
                                                          AT91C_ADC_GOVRE EQU( 0x1 << 17 );
                                                          -( ADC ) General Overrun
                                                          AT91C_ADC_ENDRX EQU( 0x1 << 18 );
                                                          -( ADC ) చివర_2 యొక్క Receiver Transfer
                                                          AT91C_ADC_RXBUFF EQU( 0x1 << 19 );
                                                          -( ADC ) RXBUFF అంతరాయం_2
/* - -------- ADC_LCDR : (ADC Offset: 0x20) ADC Last Converted Data Register -------- */
                                                          AT91C_ADC_LDATA EQU( 0x3FF << 0 );
                                                          -( ADC ) చివరి దత్తాంశం Converted
/* - -------- ADC_IER : (ADC Offset: 0x24) ADC Interrupt Enable Register -------- */
/* - -------- ADC_IDR : (ADC Offset: 0x28) ADC Interrupt Disable Register -------- */
/* - -------- ADC_IMR : (ADC Offset: 0x2c) ADC Interrupt Mask Register -------- */
/* - -------- ADC_CDR0 : (ADC Offset: 0x30) ADC Channel Data Register 0 -------- */
                                                          AT91_C_ADC_దత్తాంశం EQU( 0x3FF << 0 );
                                                          -( ADC ) Converted దత్తాంశం
/* - -------- ADC_CDR1 : (ADC Offset: 0x34) ADC Channel Data Register 1 -------- */
/* - -------- ADC_CDR2 : (ADC Offset: 0x38) ADC Channel Data Register 2 -------- */
/* - -------- ADC_CDR3 : (ADC Offset: 0x3c) ADC Channel Data Register 3 -------- */
/* - -------- ADC_CDR4 : (ADC Offset: 0x40) ADC Channel Data Register 4 -------- */
/* - -------- ADC_CDR5 : (ADC Offset: 0x44) ADC Channel Data Register 5 -------- */
/* - -------- ADC_CDR6 : (ADC Offset: 0x48) ADC Channel Data Register 6 -------- */
/* - -------- ADC_CDR7 : (ADC Offset: 0x4c) ADC Channel Data Register 7 -------- */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Advanced  Encryption Standard */
/* - ***************************************************************************** */
/* - -------- AES_CR : (AES Offset: 0x0) Control Register -------- */
                                                          AT91_C_AES_ప్రారంభం EQU( 0x1 << 0 );
                                                          -( AES ) Starts Processing
                                                          AT91C_AES_SWRST EQU( 0x1 << 8 );
                                                          -( AES ) Software Reset
                                                          AT91C_AES_LOADSEED EQU( 0x1 << 16 );
                                                          -( AES ) Random సంఖ్య_2 Generator విత్తనం Loading
/* - -------- AES_MR : (AES Offset: 0x4) Mode Register -------- */
                                                          AT91C_AES_CIPHER EQU( 0x1 << 0 );
                                                          -( AES ) Processing బహుళకం
                                                          AT91C_AES_PROCDLY EQU( 0xF << 4 );
                                                          -( AES ) Processing Delay
                                                          AT91C_AES_SMOD EQU( 0x3 << 8 );
                                                          -( AES ) ప్రారంభం_2 బహుళకం
                                                          AT91C_AES_SMOD_MANUAL EQU( 0x0 << 8 );
                                                          -( AES ) Manual బహుళకం:The ప్రారంభం_3 బిట్టు_2 లోపల నమోదు AES_CR must be సమితి గమ్యం begin encryption or decryption.
                                                             AT91C_AES_SMOD_AUTO EQU( 0x1 << 8 );
                                                          -( AES ) Auto బహుళకం:no action లోపల AES_CR is necessary( cf datasheet ).
                                                             AT91C_AES_SMOD_PDC EQU( 0x2 << 8 );
                                                          -( AES ) PDC బహుళకం( cf datasheet ).
                                                             AT91C_AES_OPMOD EQU( 0x7 << 12 );
                                                          -( AES ) Operation బహుళకం
                                                          AT91C_AES_OPMOD_ECB EQU( 0x0 << 12 );
                                                          -( AES ) ECB Electronic సంకేతం_Book బహుళకం_2.
                                                             AT91C_AES_OPMOD_CBC EQU( 0x1 << 12 );
                                                          -( AES ) CBC Cipher ఖండం Chaining బహుళకం_2.
                                                             AT91C_AES_OPMOD_OFB EQU( 0x2 << 12 );
                                                          -( AES ) OFB Output Feedback బహుళకం_2.
                                                             AT91C_AES_OPMOD_CFB EQU( 0x3 << 12 );
                                                          -( AES ) CFB Cipher Feedback బహుళకం_2.
                                                             AT91C_AES_OPMOD_CTR EQU( 0x4 << 12 );
                                                          -( AES ) CTR Counter బహుళకం_2.
                                                             AT91C_AES_LOD EQU( 0x1 << 15 );
                                                          -( AES ) చివరి Output దత్తాంశం బహుళకం
                                                          AT91C_AES_CFBS EQU( 0x7 << 16 );
                                                          -( AES ) Cipher Feedback దత్తాంశం కొలత_2
                                                          AT91_C_AES_CFBS_128_బిట్టు EQU( 0x0 << 16 );
                                                          -( AES ) 128 - బిట్టు_2.
                                                             AT91_C_AES_CFBS_64_బిట్టు EQU( 0x1 << 16 );
                                                          -( AES ) 64 - బిట్టు_2.
                                                             AT91_C_AES_CFBS_32_బిట్టు EQU( 0x2 << 16 );
                                                          -( AES ) 32 - బిట్టు_2.
                                                             AT91_C_AES_CFBS_16_బిట్టు EQU( 0x3 << 16 );
                                                          -( AES ) 16 - బిట్టు_2.
                                                             AT91_C_AES_CFBS_8_బిట్టు EQU( 0x4 << 16 );
                                                          -( AES ) 8 - బిట్టు_2.
                                                             AT91C_AES_CKEY EQU( 0xF << 20 );
                                                          -( AES ) Countermeasure కీలకం_2
                                                          AT91C_AES_CTYPE EQU( 0x1F << 24 );
                                                          -( AES ) Countermeasure Type
                                                          AT91C_AES_CTYPE_TYPE1_EN EQU( 0x1 << 24 );
                                                          -( AES ) Countermeasure type 1 is enabled.
                                                             AT91C_AES_CTYPE_TYPE2_EN EQU( 0x2 << 24 );
                                                          -( AES ) Countermeasure type 2 is enabled.
                                                             AT91C_AES_CTYPE_TYPE3_EN EQU( 0x4 << 24 );
                                                          -( AES ) Countermeasure type 3 is enabled.
                                                             AT91C_AES_CTYPE_TYPE4_EN EQU( 0x8 << 24 );
                                                          -( AES ) Countermeasure type 4 is enabled.
                                                             AT91C_AES_CTYPE_TYPE5_EN EQU( 0x10 << 24 );
                                                          -( AES ) Countermeasure type 5 is enabled.
/* - -------- AES_IER : (AES Offset: 0x10) Interrupt Enable Register -------- */
                                                             AT91C_AES_DATRDY EQU( 0x1 << 0 );
                                                          -( AES ) DATRDY
                                                          AT91C_AES_ENDRX EQU( 0x1 << 1 );
                                                          -( AES ) PDC Read బఫరు చివర_2
                                                          AT91C_AES_ENDTX EQU( 0x1 << 2 );
                                                          -( AES ) PDC Write బఫరు చివర_2
                                                          AT91C_AES_RXBUFF EQU( 0x1 << 3 );
                                                          -( AES ) PDC Read బఫరు నిండిన
                                                          AT91C_AES_TXBUFE EQU( 0x1 << 4 );
                                                          -( AES ) PDC Write బఫరు ఖాళీలు
                                                          AT91C_AES_URAD EQU( 0x1 << 8 );
                                                          -( AES ) Unspecified రిజిస్టరు Access Detection
/* - -------- AES_IDR : (AES Offset: 0x14) Interrupt Disable Register -------- */
/* - -------- AES_IMR : (AES Offset: 0x18) Interrupt Mask Register -------- */
/* - -------- AES_ISR : (AES Offset: 0x1c) Interrupt Status Register -------- */
                                                          AT91C_AES_URAT EQU( 0x7 << 12 );
                                                          -( AES ) Unspecified రిజిస్టరు Access Type స్థితి_2
                                                          AT91_C_AES_URAT_లోపల_DAT_WRITE_DATPROC EQU( 0x0 << 12 );
                                                          -( AES ) ఆదానం దత్తాంశం_2 నమోదు written during the దత్తాంశం_2 processing లోపల PDC బహుళకం_2.
                                                             AT91_C_AES_URAT_బహిర్గతం_DAT_READ_DATPROC EQU( 0x1 << 12 );
                                                          -( AES ) Output దత్తాంశం_2 నమోదు పఠ during the దత్తాంశం_2 processing.
                                                             AT91C_AES_URAT_MODEREG_WRITE_DATPROC EQU( 0x2 << 12 );
                                                          -( AES ) బహుళకం నమోదు written during the దత్తాంశం_2 processing.
                                                             AT91_C_AES_URAT_బహిర్గతం_DAT_READ_SUBKEY EQU( 0x3 << 12 );
                                                          -( AES ) Output దత్తాంశం_2 నమోదు పఠ during the sub - కీలకాలు generation.
                                                             AT91C_AES_URAT_MODEREG_WRITE_SUBKEY EQU( 0x4 << 12 );
                                                          -( AES ) బహుళకం నమోదు written during the sub - కీలకాలు generation.
                                                             AT91C_AES_URAT_WO_REG_READ EQU( 0x5 << 12 );
                                                          -( AES ) Write - only నమోదు పఠ access.

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Triple Data Encryption Standard */
/* - ***************************************************************************** */
/* - -------- TDES_CR : (TDES Offset: 0x0) Control Register -------- */
                                                             AT91_C_TDES_ప్రారంభం EQU( 0x1 << 0 );
                                                          -( TDES ) Starts Processing
                                                          AT91C_TDES_SWRST EQU( 0x1 << 8 );
                                                          -( TDES ) Software Reset
/* - -------- TDES_MR : (TDES Offset: 0x4) Mode Register -------- */
                                                          AT91C_TDES_CIPHER EQU( 0x1 << 0 );
                                                          -( TDES ) Processing బహుళకం
                                                          AT91C_TDES_TDESMOD EQU( 0x1 << 1 );
                                                          -( TDES ) Single or Triple DES బహుళకం
                                                          AT91C_TDES_KEYMOD EQU( 0x1 << 4 );
                                                          -( TDES ) కీలకం_2 బహుళకం
                                                          AT91C_TDES_SMOD EQU( 0x3 << 8 );
                                                          -( TDES ) ప్రారంభం_2 బహుళకం
                                                          AT91C_TDES_SMOD_MANUAL EQU( 0x0 << 8 );
                                                          -( TDES ) Manual బహుళకం:The ప్రారంభం_3 బిట్టు_2 లోపల నమోదు TDES_CR must be సమితి గమ్యం begin encryption or decryption.
                                                             AT91C_TDES_SMOD_AUTO EQU( 0x1 << 8 );
                                                          -( TDES ) Auto బహుళకం:no action లోపల TDES_CR is necessary( cf datasheet ).
                                                             AT91C_TDES_SMOD_PDC EQU( 0x2 << 8 );
                                                          -( TDES ) PDC బహుళకం( cf datasheet ).
                                                             AT91C_TDES_OPMOD EQU( 0x3 << 12 );
                                                          -( TDES ) Operation బహుళకం
                                                          AT91C_TDES_OPMOD_ECB EQU( 0x0 << 12 );
                                                          -( TDES ) ECB Electronic సంకేతం_Book బహుళకం_2.
                                                             AT91C_TDES_OPMOD_CBC EQU( 0x1 << 12 );
                                                          -( TDES ) CBC Cipher ఖండం Chaining బహుళకం_2.
                                                             AT91C_TDES_OPMOD_OFB EQU( 0x2 << 12 );
                                                          -( TDES ) OFB Output Feedback బహుళకం_2.
                                                             AT91C_TDES_OPMOD_CFB EQU( 0x3 << 12 );
                                                          -( TDES ) CFB Cipher Feedback బహుళకం_2.
                                                             AT91C_TDES_LOD EQU( 0x1 << 15 );
                                                          -( TDES ) చివరి Output దత్తాంశం బహుళకం
                                                          AT91C_TDES_CFBS EQU( 0x3 << 16 );
                                                          -( TDES ) Cipher Feedback దత్తాంశం కొలత_2
                                                          AT91_C_TDES_CFBS_64_బిట్టు EQU( 0x0 << 16 );
                                                          -( TDES ) 64 - బిట్టు_2.
                                                             AT91_C_TDES_CFBS_32_బిట్టు EQU( 0x1 << 16 );
                                                          -( TDES ) 32 - బిట్టు_2.
                                                             AT91_C_TDES_CFBS_16_బిట్టు EQU( 0x2 << 16 );
                                                          -( TDES ) 16 - బిట్టు_2.
                                                             AT91_C_TDES_CFBS_8_బిట్టు EQU( 0x3 << 16 );
                                                          -( TDES ) 8 - బిట్టు_2.
/* - -------- TDES_IER : (TDES Offset: 0x10) Interrupt Enable Register -------- */
                                                             AT91C_TDES_DATRDY EQU( 0x1 << 0 );
                                                          -( TDES ) DATRDY
                                                          AT91C_TDES_ENDRX EQU( 0x1 << 1 );
                                                          -( TDES ) PDC Read బఫరు చివర_2
                                                          AT91C_TDES_ENDTX EQU( 0x1 << 2 );
                                                          -( TDES ) PDC Write బఫరు చివర_2
                                                          AT91C_TDES_RXBUFF EQU( 0x1 << 3 );
                                                          -( TDES ) PDC Read బఫరు నిండిన
                                                          AT91C_TDES_TXBUFE EQU( 0x1 << 4 );
                                                          -( TDES ) PDC Write బఫరు ఖాళీలు
                                                          AT91C_TDES_URAD EQU( 0x1 << 8 );
                                                          -( TDES ) Unspecified రిజిస్టరు Access Detection
/* - -------- TDES_IDR : (TDES Offset: 0x14) Interrupt Disable Register -------- */
/* - -------- TDES_IMR : (TDES Offset: 0x18) Interrupt Mask Register -------- */
/* - -------- TDES_ISR : (TDES Offset: 0x1c) Interrupt Status Register -------- */
                                                          AT91C_TDES_URAT EQU( 0x3 << 12 );
                                                          -( TDES ) Unspecified రిజిస్టరు Access Type స్థితి_2
                                                          AT91_C_TDES_URAT_లోపల_DAT_WRITE_DATPROC EQU( 0x0 << 12 );
                                                          -( TDES ) ఆదానం దత్తాంశం_2 నమోదు written during the దత్తాంశం_2 processing లోపల PDC బహుళకం_2.
                                                             AT91_C_TDES_URAT_బహిర్గతం_DAT_READ_DATPROC EQU( 0x1 << 12 );
                                                          -( TDES ) Output దత్తాంశం_2 నమోదు పఠ during the దత్తాంశం_2 processing.
                                                             AT91C_TDES_URAT_MODEREG_WRITE_DATPROC EQU( 0x2 << 12 );
                                                          -( TDES ) బహుళకం నమోదు written during the దత్తాంశం_2 processing.
                                                             AT91C_TDES_URAT_WO_REG_READ EQU( 0x3 << 12 );
                                                          -( TDES ) Write - only నమోదు పఠ access.

/* - ***************************************************************************** */
/* -               REGISTER ADDRESS DEFINITION FOR AT91SAM7X256 */
/* - ***************************************************************************** */
/* - ========== Register definition for SYS peripheral ========== */
/* - ========== Register definition for AIC peripheral ========== */
                                                             AT91C_AIC_IVR EQU( 0xFFFFF100 );
                                                          -( AIC ) IRQ సదిశ_2 రిజిస్టరు
                                                          AT91C_AIC_SMR EQU( 0xFFFFF000 );
                                                          -( AIC ) ఆధారం_2 బహుళకం రిజిస్టరు
                                                          AT91C_AIC_FVR EQU( 0xFFFFF104 );
                                                          -( AIC ) FIQ సదిశ_2 రిజిస్టరు
                                                          AT91C_AIC_DCR EQU( 0xFFFFF138 );
                                                          -( AIC ) Debug Control రిజిస్టరు( Protect )
                                                          AT91C_AIC_EOICR EQU( 0xFFFFF130 );
                                                          -( AIC ) చివర_2 యొక్క అంతరాయం_2 Command రిజిస్టరు
                                                          AT91C_AIC_SVR EQU( 0xFFFFF080 );
                                                          -( AIC ) ఆధారం_2 సదిశ_2 రిజిస్టరు
                                                          AT91C_AIC_FFSR EQU( 0xFFFFF148 );
                                                          -( AIC ) Fast Forcing స్థితి_2 రిజిస్టరు
                                                          AT91C_AIC_ICCR EQU( 0xFFFFF128 );
                                                          -( AIC ) అంతరాయం_2 Clear Command రిజిస్టరు
                                                          AT91C_AIC_ISR EQU( 0xFFFFF108 );
                                                          -( AIC ) అంతరాయం_2 స్థితి_2 రిజిస్టరు
                                                          AT91C_AIC_IMR EQU( 0xFFFFF110 );
                                                          -( AIC ) అంతరాయం_2 ముసుగు_2 రిజిస్టరు
                                                          AT91C_AIC_IPR EQU( 0xFFFFF10C );
                                                          -( AIC ) అంతరాయం_2 Pending రిజిస్టరు
                                                          AT91C_AIC_FFER EQU( 0xFFFFF140 );
                                                          -( AIC ) Fast Forcing Enable రిజిస్టరు
                                                          AT91C_AIC_IECR EQU( 0xFFFFF120 );
                                                          -( AIC ) అంతరాయం_2 Enable Command రిజిస్టరు
                                                          AT91C_AIC_ISCR EQU( 0xFFFFF12C );
                                                          -( AIC ) అంతరాయం_2 సమితి_2 Command రిజిస్టరు
                                                          AT91C_AIC_FFDR EQU( 0xFFFFF144 );
                                                          -( AIC ) Fast Forcing Disable రిజిస్టరు
                                                          AT91C_AIC_CISR EQU( 0xFFFFF114 );
                                                          -( AIC ) Core అంతరాయం_2 స్థితి_2 రిజిస్టరు
                                                          AT91C_AIC_IDCR EQU( 0xFFFFF124 );
                                                          -( AIC ) అంతరాయం_2 Disable Command రిజిస్టరు
                                                          AT91C_AIC_SPU EQU( 0xFFFFF134 );
                                                          -( AIC ) Spurious సదిశ_2 రిజిస్టరు
/* - ========== Register definition for PDC_DBGU peripheral ========== */
                                                          AT91C_DBGU_TCR EQU( 0xFFFFF30C );
                                                          -( PDC_DBGU ) Transmit Counter రిజిస్టరు
                                                          AT91C_DBGU_RNPR EQU( 0xFFFFF310 );
                                                          -( PDC_DBGU ) Receive తదుపరి సూచిక_2 రిజిస్టరు
                                                          AT91C_DBGU_TNPR EQU( 0xFFFFF318 );
                                                          -( PDC_DBGU ) Transmit తదుపరి సూచిక_2 రిజిస్టరు
                                                          AT91C_DBGU_TPR EQU( 0xFFFFF308 );
                                                          -( PDC_DBGU ) Transmit సూచిక_2 రిజిస్టరు
                                                          AT91C_DBGU_RPR EQU( 0xFFFFF300 );
                                                          -( PDC_DBGU ) Receive సూచిక_2 రిజిస్టరు
                                                          AT91C_DBGU_RCR EQU( 0xFFFFF304 );
                                                          -( PDC_DBGU ) Receive Counter రిజిస్టరు
                                                          AT91C_DBGU_RNCR EQU( 0xFFFFF314 );
                                                          -( PDC_DBGU ) Receive తదుపరి Counter రిజిస్టరు
                                                          AT91C_DBGU_PTCR EQU( 0xFFFFF320 );
                                                          -( PDC_DBGU ) PDC Transfer Control రిజిస్టరు
                                                          AT91C_DBGU_PTSR EQU( 0xFFFFF324 );
                                                          -( PDC_DBGU ) PDC Transfer స్థితి_2 రిజిస్టరు
                                                          AT91C_DBGU_TNCR EQU( 0xFFFFF31C );
                                                          -( PDC_DBGU ) Transmit తదుపరి Counter రిజిస్టరు
/* - ========== Register definition for DBGU peripheral ========== */
                                                          AT91C_DBGU_EXID EQU( 0xFFFFF244 );
                                                          -( DBGU ) Chip ID Extension రిజిస్టరు
                                                          AT91C_DBGU_BRGR EQU( 0xFFFFF220 );
                                                          -( DBGU ) Baud రేటు Generator రిజిస్టరు
                                                          AT91C_DBGU_IDR EQU( 0xFFFFF20C );
                                                          -( DBGU ) అంతరాయం_2 Disable రిజిస్టరు
                                                          AT91C_DBGU_CSR EQU( 0xFFFFF214 );
                                                          -( DBGU ) Channel స్థితి_2 రిజిస్టరు
                                                          AT91C_DBGU_CIDR EQU( 0xFFFFF240 );
                                                          -( DBGU ) Chip ID రిజిస్టరు
                                                          AT91C_DBGU_MR EQU( 0xFFFFF204 );
                                                          -( DBGU ) బహుళకం రిజిస్టరు
                                                          AT91C_DBGU_IMR EQU( 0xFFFFF210 );
                                                          -( DBGU ) అంతరాయం_2 ముసుగు_2 రిజిస్టరు
                                                          AT91C_DBGU_CR EQU( 0xFFFFF200 );
                                                          -( DBGU ) Control రిజిస్టరు
                                                          AT91C_DBGU_FNTR EQU( 0xFFFFF248 );
                                                          -( DBGU ) Force NTRST రిజిస్టరు
                                                          AT91C_DBGU_THR EQU( 0xFFFFF21C );
                                                          -( DBGU ) Transmitter Holding రిజిస్టరు
                                                          AT91C_DBGU_RHR EQU( 0xFFFFF218 );
                                                          -( DBGU ) Receiver Holding రిజిస్టరు
                                                          AT91C_DBGU_IER EQU( 0xFFFFF208 );
                                                          -( DBGU ) అంతరాయం_2 Enable రిజిస్టరు
/* - ========== Register definition for PIOA peripheral ========== */
                                                          AT91C_PIOA_ODR EQU( 0xFFFFF414 );
                                                          -( PIOA ) Output Disable Registerr
                                                          AT91C_PIOA_SODR EQU( 0xFFFFF430 );
                                                          -( PIOA ) సమితి_2 Output దత్తాంశం రిజిస్టరు
                                                          AT91C_PIOA_ISR EQU( 0xFFFFF44C );
                                                          -( PIOA ) అంతరాయం_2 స్థితి_2 రిజిస్టరు
                                                          AT91C_PIOA_ABSR EQU( 0xFFFFF478 );
                                                          -( PIOA ) AB Select స్థితి_2 రిజిస్టరు
                                                          AT91C_PIOA_IER EQU( 0xFFFFF440 );
                                                          -( PIOA ) అంతరాయం_2 Enable రిజిస్టరు
                                                          AT91C_PIOA_PPUDR EQU( 0xFFFFF460 );
                                                          -( PIOA ) Pull - పైకి Disable రిజిస్టరు
                                                          AT91C_PIOA_IMR EQU( 0xFFFFF448 );
                                                          -( PIOA ) అంతరాయం_2 ముసుగు_2 రిజిస్టరు
                                                          AT91_C_PIOA_చొప్పున EQU( 0xFFFFF400 );
                                                          -( PIOA ) PIO Enable రిజిస్టరు
                                                          AT91C_PIOA_IFDR EQU( 0xFFFFF424 );
                                                          -( PIOA ) ఆదానం Filter Disable రిజిస్టరు
                                                          AT91C_PIOA_OWDR EQU( 0xFFFFF4A4 );
                                                          -( PIOA ) Output Write Disable రిజిస్టరు
                                                          AT91C_PIOA_MDSR EQU( 0xFFFFF458 );
                                                          -( PIOA ) Multi - driver స్థితి_2 రిజిస్టరు
                                                          AT91C_PIOA_IDR EQU( 0xFFFFF444 );
                                                          -( PIOA ) అంతరాయం_2 Disable రిజిస్టరు
                                                          AT91C_PIOA_ODSR EQU( 0xFFFFF438 );
                                                          -( PIOA ) Output దత్తాంశం స్థితి_2 రిజిస్టరు
                                                          AT91C_PIOA_PPUSR EQU( 0xFFFFF468 );
                                                          -( PIOA ) Pull - పైకి స్థితి_2 రిజిస్టరు
                                                          AT91C_PIOA_OWSR EQU( 0xFFFFF4A8 );
                                                          -( PIOA ) Output Write స్థితి_2 రిజిస్టరు
                                                          AT91C_PIOA_BSR EQU( 0xFFFFF474 );
                                                          -( PIOA ) Select B రిజిస్టరు
                                                          AT91C_PIOA_OWER EQU( 0xFFFFF4A0 );
                                                          -( PIOA ) Output Write Enable రిజిస్టరు
                                                          AT91C_PIOA_IFER EQU( 0xFFFFF420 );
                                                          -( PIOA ) ఆదానం Filter Enable రిజిస్టరు
                                                          AT91C_PIOA_PDSR EQU( 0xFFFFF43C );
                                                          -( PIOA ) Pin దత్తాంశం స్థితి_2 రిజిస్టరు
                                                          AT91C_PIOA_PPUER EQU( 0xFFFFF464 );
                                                          -( PIOA ) Pull - పైకి Enable రిజిస్టరు
                                                          AT91C_PIOA_OSR EQU( 0xFFFFF418 );
                                                          -( PIOA ) Output స్థితి_2 రిజిస్టరు
                                                          AT91C_PIOA_ASR EQU( 0xFFFFF470 );
                                                          -( PIOA ) Select A రిజిస్టరు
                                                          AT91C_PIOA_MDDR EQU( 0xFFFFF454 );
                                                          -( PIOA ) Multi - driver Disable రిజిస్టరు
                                                          AT91C_PIOA_CODR EQU( 0xFFFFF434 );
                                                          -( PIOA ) Clear Output దత్తాంశం రిజిస్టరు
                                                          AT91C_PIOA_MDER EQU( 0xFFFFF450 );
                                                          -( PIOA ) Multi - driver Enable రిజిస్టరు
                                                          AT91C_PIOA_PDR EQU( 0xFFFFF404 );
                                                          -( PIOA ) PIO Disable రిజిస్టరు
                                                          AT91C_PIOA_IFSR EQU( 0xFFFFF428 );
                                                          -( PIOA ) ఆదానం Filter స్థితి_2 రిజిస్టరు
                                                          AT91C_PIOA_OER EQU( 0xFFFFF410 );
                                                          -( PIOA ) Output Enable రిజిస్టరు
                                                          AT91C_PIOA_PSR EQU( 0xFFFFF408 );
                                                          -( PIOA ) PIO స్థితి_2 రిజిస్టరు
/* - ========== Register definition for PIOB peripheral ========== */
                                                          AT91C_PIOB_OWDR EQU( 0xFFFFF6A4 );
                                                          -( PIOB ) Output Write Disable రిజిస్టరు
                                                          AT91C_PIOB_MDER EQU( 0xFFFFF650 );
                                                          -( PIOB ) Multi - driver Enable రిజిస్టరు
                                                          AT91C_PIOB_PPUSR EQU( 0xFFFFF668 );
                                                          -( PIOB ) Pull - పైకి స్థితి_2 రిజిస్టరు
                                                          AT91C_PIOB_IMR EQU( 0xFFFFF648 );
                                                          -( PIOB ) అంతరాయం_2 ముసుగు_2 రిజిస్టరు
                                                          AT91C_PIOB_ASR EQU( 0xFFFFF670 );
                                                          -( PIOB ) Select A రిజిస్టరు
                                                          AT91C_PIOB_PPUDR EQU( 0xFFFFF660 );
                                                          -( PIOB ) Pull - పైకి Disable రిజిస్టరు
                                                          AT91C_PIOB_PSR EQU( 0xFFFFF608 );
                                                          -( PIOB ) PIO స్థితి_2 రిజిస్టరు
                                                          AT91C_PIOB_IER EQU( 0xFFFFF640 );
                                                          -( PIOB ) అంతరాయం_2 Enable రిజిస్టరు
                                                          AT91C_PIOB_CODR EQU( 0xFFFFF634 );
                                                          -( PIOB ) Clear Output దత్తాంశం రిజిస్టరు
                                                          AT91C_PIOB_OWER EQU( 0xFFFFF6A0 );
                                                          -( PIOB ) Output Write Enable రిజిస్టరు
                                                          AT91C_PIOB_ABSR EQU( 0xFFFFF678 );
                                                          -( PIOB ) AB Select స్థితి_2 రిజిస్టరు
                                                          AT91C_PIOB_IFDR EQU( 0xFFFFF624 );
                                                          -( PIOB ) ఆదానం Filter Disable రిజిస్టరు
                                                          AT91C_PIOB_PDSR EQU( 0xFFFFF63C );
                                                          -( PIOB ) Pin దత్తాంశం స్థితి_2 రిజిస్టరు
                                                          AT91C_PIOB_IDR EQU( 0xFFFFF644 );
                                                          -( PIOB ) అంతరాయం_2 Disable రిజిస్టరు
                                                          AT91C_PIOB_OWSR EQU( 0xFFFFF6A8 );
                                                          -( PIOB ) Output Write స్థితి_2 రిజిస్టరు
                                                          AT91C_PIOB_PDR EQU( 0xFFFFF604 );
                                                          -( PIOB ) PIO Disable రిజిస్టరు
                                                          AT91C_PIOB_ODR EQU( 0xFFFFF614 );
                                                          -( PIOB ) Output Disable Registerr
                                                          AT91C_PIOB_IFSR EQU( 0xFFFFF628 );
                                                          -( PIOB ) ఆదానం Filter స్థితి_2 రిజిస్టరు
                                                          AT91C_PIOB_PPUER EQU( 0xFFFFF664 );
                                                          -( PIOB ) Pull - పైకి Enable రిజిస్టరు
                                                          AT91C_PIOB_SODR EQU( 0xFFFFF630 );
                                                          -( PIOB ) సమితి_2 Output దత్తాంశం రిజిస్టరు
                                                          AT91C_PIOB_ISR EQU( 0xFFFFF64C );
                                                          -( PIOB ) అంతరాయం_2 స్థితి_2 రిజిస్టరు
                                                          AT91C_PIOB_ODSR EQU( 0xFFFFF638 );
                                                          -( PIOB ) Output దత్తాంశం స్థితి_2 రిజిస్టరు
                                                          AT91C_PIOB_OSR EQU( 0xFFFFF618 );
                                                          -( PIOB ) Output స్థితి_2 రిజిస్టరు
                                                          AT91C_PIOB_MDSR EQU( 0xFFFFF658 );
                                                          -( PIOB ) Multi - driver స్థితి_2 రిజిస్టరు
                                                          AT91C_PIOB_IFER EQU( 0xFFFFF620 );
                                                          -( PIOB ) ఆదానం Filter Enable రిజిస్టరు
                                                          AT91C_PIOB_BSR EQU( 0xFFFFF674 );
                                                          -( PIOB ) Select B రిజిస్టరు
                                                          AT91C_PIOB_MDDR EQU( 0xFFFFF654 );
                                                          -( PIOB ) Multi - driver Disable రిజిస్టరు
                                                          AT91C_PIOB_OER EQU( 0xFFFFF610 );
                                                          -( PIOB ) Output Enable రిజిస్టరు
                                                          AT91_C_PIOB_చొప్పున EQU( 0xFFFFF600 );
                                                          -( PIOB ) PIO Enable రిజిస్టరు
/* - ========== Register definition for CKGR peripheral ========== */
                                                          AT91C_CKGR_MOR EQU( 0xFFFFFC20 );
                                                          -( CKGR ) Main Oscillator రిజిస్టరు
                                                          AT91C_CKGR_PLLR EQU( 0xFFFFFC2C );
                                                          -( CKGR ) PLL రిజిస్టరు
                                                          AT91C_CKGR_MCFR EQU( 0xFFFFFC24 );
                                                          -( CKGR ) Main Clock Frequency రిజిస్టరు
/* - ========== Register definition for PMC peripheral ========== */
                                                          AT91C_PMC_IDR EQU( 0xFFFFFC64 );
                                                          -( PMC ) అంతరాయం_2 Disable రిజిస్టరు
                                                          AT91C_PMC_MOR EQU( 0xFFFFFC20 );
                                                          -( PMC ) Main Oscillator రిజిస్టరు
                                                          AT91C_PMC_PLLR EQU( 0xFFFFFC2C );
                                                          -( PMC ) PLL రిజిస్టరు
                                                          AT91C_PMC_PCER EQU( 0xFFFFFC10 );
                                                          -( PMC ) Peripheral Clock Enable రిజిస్టరు
                                                          AT91C_PMC_PCKR EQU( 0xFFFFFC40 );
                                                          -( PMC ) Programmable Clock రిజిస్టరు
                                                          AT91C_PMC_MCKR EQU( 0xFFFFFC30 );
                                                          -( PMC ) Master Clock రిజిస్టరు
                                                          AT91C_PMC_SCDR EQU( 0xFFFFFC04 );
                                                          -( PMC ) System Clock Disable రిజిస్టరు
                                                          AT91C_PMC_PCDR EQU( 0xFFFFFC14 );
                                                          -( PMC ) Peripheral Clock Disable రిజిస్టరు
                                                          AT91C_PMC_SCSR EQU( 0xFFFFFC08 );
                                                          -( PMC ) System Clock స్థితి_2 రిజిస్టరు
                                                          AT91C_PMC_PCSR EQU( 0xFFFFFC18 );
                                                          -( PMC ) Peripheral Clock స్థితి_2 రిజిస్టరు
                                                          AT91C_PMC_MCFR EQU( 0xFFFFFC24 );
                                                          -( PMC ) Main Clock Frequency రిజిస్టరు
                                                          AT91C_PMC_SCER EQU( 0xFFFFFC00 );
                                                          -( PMC ) System Clock Enable రిజిస్టరు
                                                          AT91C_PMC_IMR EQU( 0xFFFFFC6C );
                                                          -( PMC ) అంతరాయం_2 ముసుగు_2 రిజిస్టరు
                                                          AT91C_PMC_IER EQU( 0xFFFFFC60 );
                                                          -( PMC ) అంతరాయం_2 Enable రిజిస్టరు
                                                          AT91C_PMC_SR EQU( 0xFFFFFC68 );
                                                          -( PMC ) స్థితి_2 రిజిస్టరు
/* - ========== Register definition for RSTC peripheral ========== */
                                                          AT91C_RSTC_RCR EQU( 0xFFFFFD00 );
                                                          -( RSTC ) Reset Control రిజిస్టరు
                                                          AT91C_RSTC_RMR EQU( 0xFFFFFD08 );
                                                          -( RSTC ) Reset బహుళకం రిజిస్టరు
                                                          AT91C_RSTC_RSR EQU( 0xFFFFFD04 );
                                                          -( RSTC ) Reset స్థితి_2 రిజిస్టరు
/* - ========== Register definition for RTTC peripheral ========== */
                                                          AT91C_RTTC_RTSR EQU( 0xFFFFFD2C );
                                                          -( RTTC ) Real - time స్థితి_2 రిజిస్టరు
                                                          AT91C_RTTC_RTMR EQU( 0xFFFFFD20 );
                                                          -( RTTC ) Real - time బహుళకం రిజిస్టరు
                                                          AT91C_RTTC_RTVR EQU( 0xFFFFFD28 );
                                                          -( RTTC ) Real - time విలువ_2 రిజిస్టరు
                                                          AT91C_RTTC_RTAR EQU( 0xFFFFFD24 );
                                                          -( RTTC ) Real - time Alarm రిజిస్టరు
/* - ========== Register definition for PITC peripheral ========== */
                                                          AT91C_PITC_PIVR EQU( 0xFFFFFD38 );
                                                          -( PITC ) Period Interval విలువ_2 రిజిస్టరు
                                                          AT91C_PITC_PISR EQU( 0xFFFFFD34 );
                                                          -( PITC ) Period Interval స్థితి_2 రిజిస్టరు
                                                          AT91C_PITC_PIIR EQU( 0xFFFFFD3C );
                                                          -( PITC ) Period Interval Image రిజిస్టరు
                                                          AT91C_PITC_PIMR EQU( 0xFFFFFD30 );
                                                          -( PITC ) Period Interval బహుళకం రిజిస్టరు
/* - ========== Register definition for WDTC peripheral ========== */
                                                          AT91C_WDTC_WDCR EQU( 0xFFFFFD40 );
                                                          -( WDTC ) Watchdog Control రిజిస్టరు
                                                          AT91C_WDTC_WDSR EQU( 0xFFFFFD48 );
                                                          -( WDTC ) Watchdog స్థితి_2 రిజిస్టరు
                                                          AT91C_WDTC_WDMR EQU( 0xFFFFFD44 );
                                                          -( WDTC ) Watchdog బహుళకం రిజిస్టరు
/* - ========== Register definition for VREG peripheral ========== */
                                                          AT91C_VREG_MR EQU( 0xFFFFFD60 );
                                                          -( VREG ) Voltage Regulator బహుళకం రిజిస్టరు
/* - ========== Register definition for MC peripheral ========== */
                                                          AT91C_MC_ASR EQU( 0xFFFFFF04 );
                                                          -( MC ) MC Abort స్థితి_2 రిజిస్టరు
                                                          AT91C_MC_RCR EQU( 0xFFFFFF00 );
                                                          -( MC ) MC Remap Control రిజిస్టరు
                                                          AT91C_MC_FCR EQU( 0xFFFFFF64 );
                                                          -( MC ) MC Flash Command రిజిస్టరు
                                                          AT91C_MC_AASR EQU( 0xFFFFFF08 );
                                                          -( MC ) MC Abort చిరునామా స్థితి_2 రిజిస్టరు
                                                          AT91C_MC_FSR EQU( 0xFFFFFF68 );
                                                          -( MC ) MC Flash స్థితి_2 రిజిస్టరు
                                                          AT91C_MC_FMR EQU( 0xFFFFFF60 );
                                                          -( MC ) MC Flash బహుళకం రిజిస్టరు
/* - ========== Register definition for PDC_SPI1 peripheral ========== */
                                                          AT91C_SPI1_PTCR EQU( 0xFFFE4120 );
                                                          -( PDC_SPI1 ) PDC Transfer Control రిజిస్టరు
                                                          AT91C_SPI1_RPR EQU( 0xFFFE4100 );
                                                          -( PDC_SPI1 ) Receive సూచిక_2 రిజిస్టరు
                                                          AT91C_SPI1_TNCR EQU( 0xFFFE411C );
                                                          -( PDC_SPI1 ) Transmit తదుపరి Counter రిజిస్టరు
                                                          AT91C_SPI1_TPR EQU( 0xFFFE4108 );
                                                          -( PDC_SPI1 ) Transmit సూచిక_2 రిజిస్టరు
                                                          AT91C_SPI1_TNPR EQU( 0xFFFE4118 );
                                                          -( PDC_SPI1 ) Transmit తదుపరి సూచిక_2 రిజిస్టరు
                                                          AT91C_SPI1_TCR EQU( 0xFFFE410C );
                                                          -( PDC_SPI1 ) Transmit Counter రిజిస్టరు
                                                          AT91C_SPI1_RCR EQU( 0xFFFE4104 );
                                                          -( PDC_SPI1 ) Receive Counter రిజిస్టరు
                                                          AT91C_SPI1_RNPR EQU( 0xFFFE4110 );
                                                          -( PDC_SPI1 ) Receive తదుపరి సూచిక_2 రిజిస్టరు
                                                          AT91C_SPI1_RNCR EQU( 0xFFFE4114 );
                                                          -( PDC_SPI1 ) Receive తదుపరి Counter రిజిస్టరు
                                                          AT91C_SPI1_PTSR EQU( 0xFFFE4124 );
                                                          -( PDC_SPI1 ) PDC Transfer స్థితి_2 రిజిస్టరు
/* - ========== Register definition for SPI1 peripheral ========== */
                                                          AT91C_SPI1_IMR EQU( 0xFFFE401C );
                                                          -( SPI1 ) అంతరాయం_2 ముసుగు_2 రిజిస్టరు
                                                          AT91C_SPI1_IER EQU( 0xFFFE4014 );
                                                          -( SPI1 ) అంతరాయం_2 Enable రిజిస్టరు
                                                          AT91C_SPI1_MR EQU( 0xFFFE4004 );
                                                          -( SPI1 ) బహుళకం రిజిస్టరు
                                                          AT91C_SPI1_RDR EQU( 0xFFFE4008 );
                                                          -( SPI1 ) Receive దత్తాంశం రిజిస్టరు
                                                          AT91C_SPI1_IDR EQU( 0xFFFE4018 );
                                                          -( SPI1 ) అంతరాయం_2 Disable రిజిస్టరు
                                                          AT91C_SPI1_SR EQU( 0xFFFE4010 );
                                                          -( SPI1 ) స్థితి_2 రిజిస్టరు
                                                          AT91C_SPI1_TDR EQU( 0xFFFE400C );
                                                          -( SPI1 ) Transmit దత్తాంశం రిజిస్టరు
                                                          AT91C_SPI1_CR EQU( 0xFFFE4000 );
                                                          -( SPI1 ) Control రిజిస్టరు
                                                          AT91C_SPI1_CSR EQU( 0xFFFE4030 );
                                                          -( SPI1 ) Chip Select రిజిస్టరు
/* - ========== Register definition for PDC_SPI0 peripheral ========== */
                                                          AT91C_SPI0_PTCR EQU( 0xFFFE0120 );
                                                          -( PDC_SPI0 ) PDC Transfer Control రిజిస్టరు
                                                          AT91C_SPI0_TPR EQU( 0xFFFE0108 );
                                                          -( PDC_SPI0 ) Transmit సూచిక_2 రిజిస్టరు
                                                          AT91C_SPI0_TCR EQU( 0xFFFE010C );
                                                          -( PDC_SPI0 ) Transmit Counter రిజిస్టరు
                                                          AT91C_SPI0_RCR EQU( 0xFFFE0104 );
                                                          -( PDC_SPI0 ) Receive Counter రిజిస్టరు
                                                          AT91C_SPI0_PTSR EQU( 0xFFFE0124 );
                                                          -( PDC_SPI0 ) PDC Transfer స్థితి_2 రిజిస్టరు
                                                          AT91C_SPI0_RNPR EQU( 0xFFFE0110 );
                                                          -( PDC_SPI0 ) Receive తదుపరి సూచిక_2 రిజిస్టరు
                                                          AT91C_SPI0_RPR EQU( 0xFFFE0100 );
                                                          -( PDC_SPI0 ) Receive సూచిక_2 రిజిస్టరు
                                                          AT91C_SPI0_TNCR EQU( 0xFFFE011C );
                                                          -( PDC_SPI0 ) Transmit తదుపరి Counter రిజిస్టరు
                                                          AT91C_SPI0_RNCR EQU( 0xFFFE0114 );
                                                          -( PDC_SPI0 ) Receive తదుపరి Counter రిజిస్టరు
                                                          AT91C_SPI0_TNPR EQU( 0xFFFE0118 );
                                                          -( PDC_SPI0 ) Transmit తదుపరి సూచిక_2 రిజిస్టరు
/* - ========== Register definition for SPI0 peripheral ========== */
                                                          AT91C_SPI0_IER EQU( 0xFFFE0014 );
                                                          -( SPI0 ) అంతరాయం_2 Enable రిజిస్టరు
                                                          AT91C_SPI0_SR EQU( 0xFFFE0010 );
                                                          -( SPI0 ) స్థితి_2 రిజిస్టరు
                                                          AT91C_SPI0_IDR EQU( 0xFFFE0018 );
                                                          -( SPI0 ) అంతరాయం_2 Disable రిజిస్టరు
                                                          AT91C_SPI0_CR EQU( 0xFFFE0000 );
                                                          -( SPI0 ) Control రిజిస్టరు
                                                          AT91C_SPI0_MR EQU( 0xFFFE0004 );
                                                          -( SPI0 ) బహుళకం రిజిస్టరు
                                                          AT91C_SPI0_IMR EQU( 0xFFFE001C );
                                                          -( SPI0 ) అంతరాయం_2 ముసుగు_2 రిజిస్టరు
                                                          AT91C_SPI0_TDR EQU( 0xFFFE000C );
                                                          -( SPI0 ) Transmit దత్తాంశం రిజిస్టరు
                                                          AT91C_SPI0_RDR EQU( 0xFFFE0008 );
                                                          -( SPI0 ) Receive దత్తాంశం రిజిస్టరు
                                                          AT91C_SPI0_CSR EQU( 0xFFFE0030 );
                                                          -( SPI0 ) Chip Select రిజిస్టరు
/* - ========== Register definition for PDC_US1 peripheral ========== */
                                                          AT91C_US1_RNCR EQU( 0xFFFC4114 );
                                                          -( PDC_US1 ) Receive తదుపరి Counter రిజిస్టరు
                                                          AT91C_US1_PTCR EQU( 0xFFFC4120 );
                                                          -( PDC_US1 ) PDC Transfer Control రిజిస్టరు
                                                          AT91C_US1_TCR EQU( 0xFFFC410C );
                                                          -( PDC_US1 ) Transmit Counter రిజిస్టరు
                                                          AT91C_US1_PTSR EQU( 0xFFFC4124 );
                                                          -( PDC_US1 ) PDC Transfer స్థితి_2 రిజిస్టరు
                                                          AT91C_US1_TNPR EQU( 0xFFFC4118 );
                                                          -( PDC_US1 ) Transmit తదుపరి సూచిక_2 రిజిస్టరు
                                                          AT91C_US1_RCR EQU( 0xFFFC4104 );
                                                          -( PDC_US1 ) Receive Counter రిజిస్టరు
                                                          AT91C_US1_RNPR EQU( 0xFFFC4110 );
                                                          -( PDC_US1 ) Receive తదుపరి సూచిక_2 రిజిస్టరు
                                                          AT91C_US1_RPR EQU( 0xFFFC4100 );
                                                          -( PDC_US1 ) Receive సూచిక_2 రిజిస్టరు
                                                          AT91C_US1_TNCR EQU( 0xFFFC411C );
                                                          -( PDC_US1 ) Transmit తదుపరి Counter రిజిస్టరు
                                                          AT91C_US1_TPR EQU( 0xFFFC4108 );
                                                          -( PDC_US1 ) Transmit సూచిక_2 రిజిస్టరు
/* - ========== Register definition for US1 peripheral ========== */
                                                          AT91C_US1_IF EQU( 0xFFFC404C );
                                                          -( US1 ) IRDA_FILTER రిజిస్టరు
                                                          AT91C_US1_NER EQU( 0xFFFC4044 );
                                                          -( US1 ) Nb Errors రిజిస్టరు
                                                          AT91C_US1_RTOR EQU( 0xFFFC4024 );
                                                          -( US1 ) Receiver సమయం - బహిర్గతం రిజిస్టరు
                                                          AT91C_US1_CSR EQU( 0xFFFC4014 );
                                                          -( US1 ) Channel స్థితి_2 రిజిస్టరు
                                                          AT91C_US1_IDR EQU( 0xFFFC400C );
                                                          -( US1 ) అంతరాయం_2 Disable రిజిస్టరు
                                                          AT91C_US1_IER EQU( 0xFFFC4008 );
                                                          -( US1 ) అంతరాయం_2 Enable రిజిస్టరు
                                                          AT91C_US1_THR EQU( 0xFFFC401C );
                                                          -( US1 ) Transmitter Holding రిజిస్టరు
                                                          AT91C_US1_TTGR EQU( 0xFFFC4028 );
                                                          -( US1 ) Transmitter సమయం - guard రిజిస్టరు
                                                          AT91C_US1_RHR EQU( 0xFFFC4018 );
                                                          -( US1 ) Receiver Holding రిజిస్టరు
                                                          AT91C_US1_BRGR EQU( 0xFFFC4020 );
                                                          -( US1 ) Baud రేటు Generator రిజిస్టరు
                                                          AT91C_US1_IMR EQU( 0xFFFC4010 );
                                                          -( US1 ) అంతరాయం_2 ముసుగు_2 రిజిస్టరు
                                                          AT91C_US1_FIDI EQU( 0xFFFC4040 );
                                                          -( US1 ) FI_DI_నిష్పత్తి రిజిస్టరు
                                                          AT91C_US1_CR EQU( 0xFFFC4000 );
                                                          -( US1 ) Control రిజిస్టరు
                                                          AT91C_US1_MR EQU( 0xFFFC4004 );
                                                          -( US1 ) బహుళకం రిజిస్టరు
/* - ========== Register definition for PDC_US0 peripheral ========== */
                                                          AT91C_US0_TNPR EQU( 0xFFFC0118 );
                                                          -( PDC_US0 ) Transmit తదుపరి సూచిక_2 రిజిస్టరు
                                                          AT91C_US0_RNPR EQU( 0xFFFC0110 );
                                                          -( PDC_US0 ) Receive తదుపరి సూచిక_2 రిజిస్టరు
                                                          AT91C_US0_TCR EQU( 0xFFFC010C );
                                                          -( PDC_US0 ) Transmit Counter రిజిస్టరు
                                                          AT91C_US0_PTCR EQU( 0xFFFC0120 );
                                                          -( PDC_US0 ) PDC Transfer Control రిజిస్టరు
                                                          AT91C_US0_PTSR EQU( 0xFFFC0124 );
                                                          -( PDC_US0 ) PDC Transfer స్థితి_2 రిజిస్టరు
                                                          AT91C_US0_TNCR EQU( 0xFFFC011C );
                                                          -( PDC_US0 ) Transmit తదుపరి Counter రిజిస్టరు
                                                          AT91C_US0_TPR EQU( 0xFFFC0108 );
                                                          -( PDC_US0 ) Transmit సూచిక_2 రిజిస్టరు
                                                          AT91C_US0_RCR EQU( 0xFFFC0104 );
                                                          -( PDC_US0 ) Receive Counter రిజిస్టరు
                                                          AT91C_US0_RPR EQU( 0xFFFC0100 );
                                                          -( PDC_US0 ) Receive సూచిక_2 రిజిస్టరు
                                                          AT91C_US0_RNCR EQU( 0xFFFC0114 );
                                                          -( PDC_US0 ) Receive తదుపరి Counter రిజిస్టరు
/* - ========== Register definition for US0 peripheral ========== */
                                                          AT91C_US0_BRGR EQU( 0xFFFC0020 );
                                                          -( US0 ) Baud రేటు Generator రిజిస్టరు
                                                          AT91C_US0_NER EQU( 0xFFFC0044 );
                                                          -( US0 ) Nb Errors రిజిస్టరు
                                                          AT91C_US0_CR EQU( 0xFFFC0000 );
                                                          -( US0 ) Control రిజిస్టరు
                                                          AT91C_US0_IMR EQU( 0xFFFC0010 );
                                                          -( US0 ) అంతరాయం_2 ముసుగు_2 రిజిస్టరు
                                                          AT91C_US0_FIDI EQU( 0xFFFC0040 );
                                                          -( US0 ) FI_DI_నిష్పత్తి రిజిస్టరు
                                                          AT91C_US0_TTGR EQU( 0xFFFC0028 );
                                                          -( US0 ) Transmitter సమయం - guard రిజిస్టరు
                                                          AT91C_US0_MR EQU( 0xFFFC0004 );
                                                          -( US0 ) బహుళకం రిజిస్టరు
                                                          AT91C_US0_RTOR EQU( 0xFFFC0024 );
                                                          -( US0 ) Receiver సమయం - బహిర్గతం రిజిస్టరు
                                                          AT91C_US0_CSR EQU( 0xFFFC0014 );
                                                          -( US0 ) Channel స్థితి_2 రిజిస్టరు
                                                          AT91C_US0_RHR EQU( 0xFFFC0018 );
                                                          -( US0 ) Receiver Holding రిజిస్టరు
                                                          AT91C_US0_IDR EQU( 0xFFFC000C );
                                                          -( US0 ) అంతరాయం_2 Disable రిజిస్టరు
                                                          AT91C_US0_THR EQU( 0xFFFC001C );
                                                          -( US0 ) Transmitter Holding రిజిస్టరు
                                                          AT91C_US0_IF EQU( 0xFFFC004C );
                                                          -( US0 ) IRDA_FILTER రిజిస్టరు
                                                          AT91C_US0_IER EQU( 0xFFFC0008 );
                                                          -( US0 ) అంతరాయం_2 Enable రిజిస్టరు
/* - ========== Register definition for PDC_SSC peripheral ========== */
                                                          AT91C_SSC_TNCR EQU( 0xFFFD411C );
                                                          -( PDC_SSC ) Transmit తదుపరి Counter రిజిస్టరు
                                                          AT91C_SSC_RPR EQU( 0xFFFD4100 );
                                                          -( PDC_SSC ) Receive సూచిక_2 రిజిస్టరు
                                                          AT91C_SSC_RNCR EQU( 0xFFFD4114 );
                                                          -( PDC_SSC ) Receive తదుపరి Counter రిజిస్టరు
                                                          AT91C_SSC_TPR EQU( 0xFFFD4108 );
                                                          -( PDC_SSC ) Transmit సూచిక_2 రిజిస్టరు
                                                          AT91C_SSC_PTCR EQU( 0xFFFD4120 );
                                                          -( PDC_SSC ) PDC Transfer Control రిజిస్టరు
                                                          AT91C_SSC_TCR EQU( 0xFFFD410C );
                                                          -( PDC_SSC ) Transmit Counter రిజిస్టరు
                                                          AT91C_SSC_RCR EQU( 0xFFFD4104 );
                                                          -( PDC_SSC ) Receive Counter రిజిస్టరు
                                                          AT91C_SSC_RNPR EQU( 0xFFFD4110 );
                                                          -( PDC_SSC ) Receive తదుపరి సూచిక_2 రిజిస్టరు
                                                          AT91C_SSC_TNPR EQU( 0xFFFD4118 );
                                                          -( PDC_SSC ) Transmit తదుపరి సూచిక_2 రిజిస్టరు
                                                          AT91C_SSC_PTSR EQU( 0xFFFD4124 );
                                                          -( PDC_SSC ) PDC Transfer స్థితి_2 రిజిస్టరు
/* - ========== Register definition for SSC peripheral ========== */
                                                          AT91C_SSC_RHR EQU( 0xFFFD4020 );
                                                          -( SSC ) Receive Holding రిజిస్టరు
                                                          AT91C_SSC_RSHR EQU( 0xFFFD4030 );
                                                          -( SSC ) Receive Sync Holding రిజిస్టరు
                                                          AT91C_SSC_TFMR EQU( 0xFFFD401C );
                                                          -( SSC ) Transmit చట్రం బహుళకం రిజిస్టరు
                                                          AT91C_SSC_IDR EQU( 0xFFFD4048 );
                                                          -( SSC ) అంతరాయం_2 Disable రిజిస్టరు
                                                          AT91C_SSC_THR EQU( 0xFFFD4024 );
                                                          -( SSC ) Transmit Holding రిజిస్టరు
                                                          AT91C_SSC_RCMR EQU( 0xFFFD4010 );
                                                          -( SSC ) Receive Clock బహుళకం_రిజిస్టరు
                                                          AT91C_SSC_IER EQU( 0xFFFD4044 );
                                                          -( SSC ) అంతరాయం_2 Enable రిజిస్టరు
                                                          AT91C_SSC_TSHR EQU( 0xFFFD4034 );
                                                          -( SSC ) Transmit Sync Holding రిజిస్టరు
                                                          AT91C_SSC_SR EQU( 0xFFFD4040 );
                                                          -( SSC ) స్థితి_2 రిజిస్టరు
                                                          AT91C_SSC_CMR EQU( 0xFFFD4004 );
                                                          -( SSC ) Clock బహుళకం రిజిస్టరు
                                                          AT91C_SSC_TCMR EQU( 0xFFFD4018 );
                                                          -( SSC ) Transmit Clock బహుళకం రిజిస్టరు
                                                          AT91C_SSC_CR EQU( 0xFFFD4000 );
                                                          -( SSC ) Control రిజిస్టరు
                                                          AT91C_SSC_IMR EQU( 0xFFFD404C );
                                                          -( SSC ) అంతరాయం_2 ముసుగు_2 రిజిస్టరు
                                                          AT91C_SSC_RFMR EQU( 0xFFFD4014 );
                                                          -( SSC ) Receive చట్రం బహుళకం రిజిస్టరు
/* - ========== Register definition for TWI peripheral ========== */
                                                          AT91C_TWI_IER EQU( 0xFFFB8024 );
                                                          -( TWI ) అంతరాయం_2 Enable రిజిస్టరు
                                                          AT91C_TWI_CR EQU( 0xFFFB8000 );
                                                          -( TWI ) Control రిజిస్టరు
                                                          AT91C_TWI_SR EQU( 0xFFFB8020 );
                                                          -( TWI ) స్థితి_2 రిజిస్టరు
                                                          AT91C_TWI_IMR EQU( 0xFFFB802C );
                                                          -( TWI ) అంతరాయం_2 ముసుగు_2 రిజిస్టరు
                                                          AT91C_TWI_THR EQU( 0xFFFB8034 );
                                                          -( TWI ) Transmit Holding రిజిస్టరు
                                                          AT91C_TWI_IDR EQU( 0xFFFB8028 );
                                                          -( TWI ) అంతరాయం_2 Disable రిజిస్టరు
                                                          AT91C_TWI_IADR EQU( 0xFFFB800C );
                                                          -( TWI ) అంతర్గత చిరునామా రిజిస్టరు
                                                          AT91C_TWI_MMR EQU( 0xFFFB8004 );
                                                          -( TWI ) Master బహుళకం రిజిస్టరు
                                                          AT91C_TWI_CWGR EQU( 0xFFFB8010 );
                                                          -( TWI ) Clock Waveform Generator రిజిస్టరు
                                                          AT91C_TWI_RHR EQU( 0xFFFB8030 );
                                                          -( TWI ) Receive Holding రిజిస్టరు
/* - ========== Register definition for PWMC_CH3 peripheral ========== */
                                                          AT91C_PWMC_CH3_CUPDR EQU( 0xFFFCC270 );
                                                          -( PWMC_CH3 ) Channel Update రిజిస్టరు
                                                          AT91C_PWMC_CH3_Reserved EQU( 0xFFFCC274 );
                                                          -( PWMC_CH3 ) Reserved
                                                          AT91C_PWMC_CH3_CPRDR EQU( 0xFFFCC268 );
                                                          -( PWMC_CH3 ) Channel Period రిజిస్టరు
                                                          AT91C_PWMC_CH3_CDTYR EQU( 0xFFFCC264 );
                                                          -( PWMC_CH3 ) Channel Duty చక్రం_2 రిజిస్టరు
                                                          AT91C_PWMC_CH3_CCNTR EQU( 0xFFFCC26C );
                                                          -( PWMC_CH3 ) Channel Counter రిజిస్టరు
                                                          AT91C_PWMC_CH3_CMR EQU( 0xFFFCC260 );
                                                          -( PWMC_CH3 ) Channel బహుళకం రిజిస్టరు
/* - ========== Register definition for PWMC_CH2 peripheral ========== */
                                                          AT91C_PWMC_CH2_Reserved EQU( 0xFFFCC254 );
                                                          -( PWMC_CH2 ) Reserved
                                                          AT91C_PWMC_CH2_CMR EQU( 0xFFFCC240 );
                                                          -( PWMC_CH2 ) Channel బహుళకం రిజిస్టరు
                                                          AT91C_PWMC_CH2_CCNTR EQU( 0xFFFCC24C );
                                                          -( PWMC_CH2 ) Channel Counter రిజిస్టరు
                                                          AT91C_PWMC_CH2_CPRDR EQU( 0xFFFCC248 );
                                                          -( PWMC_CH2 ) Channel Period రిజిస్టరు
                                                          AT91C_PWMC_CH2_CUPDR EQU( 0xFFFCC250 );
                                                          -( PWMC_CH2 ) Channel Update రిజిస్టరు
                                                          AT91C_PWMC_CH2_CDTYR EQU( 0xFFFCC244 );
                                                          -( PWMC_CH2 ) Channel Duty చక్రం_2 రిజిస్టరు
/* - ========== Register definition for PWMC_CH1 peripheral ========== */
                                                          AT91C_PWMC_CH1_Reserved EQU( 0xFFFCC234 );
                                                          -( PWMC_CH1 ) Reserved
                                                          AT91C_PWMC_CH1_CUPDR EQU( 0xFFFCC230 );
                                                          -( PWMC_CH1 ) Channel Update రిజిస్టరు
                                                          AT91C_PWMC_CH1_CPRDR EQU( 0xFFFCC228 );
                                                          -( PWMC_CH1 ) Channel Period రిజిస్టరు
                                                          AT91C_PWMC_CH1_CCNTR EQU( 0xFFFCC22C );
                                                          -( PWMC_CH1 ) Channel Counter రిజిస్టరు
                                                          AT91C_PWMC_CH1_CDTYR EQU( 0xFFFCC224 );
                                                          -( PWMC_CH1 ) Channel Duty చక్రం_2 రిజిస్టరు
                                                          AT91C_PWMC_CH1_CMR EQU( 0xFFFCC220 );
                                                          -( PWMC_CH1 ) Channel బహుళకం రిజిస్టరు
/* - ========== Register definition for PWMC_CH0 peripheral ========== */
                                                          AT91C_PWMC_CH0_Reserved EQU( 0xFFFCC214 );
                                                          -( PWMC_CH0 ) Reserved
                                                          AT91C_PWMC_CH0_CPRDR EQU( 0xFFFCC208 );
                                                          -( PWMC_CH0 ) Channel Period రిజిస్టరు
                                                          AT91C_PWMC_CH0_CDTYR EQU( 0xFFFCC204 );
                                                          -( PWMC_CH0 ) Channel Duty చక్రం_2 రిజిస్టరు
                                                          AT91C_PWMC_CH0_CMR EQU( 0xFFFCC200 );
                                                          -( PWMC_CH0 ) Channel బహుళకం రిజిస్టరు
                                                          AT91C_PWMC_CH0_CUPDR EQU( 0xFFFCC210 );
                                                          -( PWMC_CH0 ) Channel Update రిజిస్టరు
                                                          AT91C_PWMC_CH0_CCNTR EQU( 0xFFFCC20C );
                                                          -( PWMC_CH0 ) Channel Counter రిజిస్టరు
/* - ========== Register definition for PWMC peripheral ========== */
                                                          AT91C_PWMC_IDR EQU( 0xFFFCC014 );
                                                          -( PWMC ) PWMC అంతరాయం_2 Disable రిజిస్టరు
                                                          AT91C_PWMC_DIS EQU( 0xFFFCC008 );
                                                          -( PWMC ) PWMC Disable రిజిస్టరు
                                                          AT91C_PWMC_IER EQU( 0xFFFCC010 );
                                                          -( PWMC ) PWMC అంతరాయం_2 Enable రిజిస్టరు
                                                          AT91C_PWMC_VR EQU( 0xFFFCC0FC );
                                                          -( PWMC ) PWMC సంస్కరణ_2 రిజిస్టరు
                                                          AT91C_PWMC_ISR EQU( 0xFFFCC01C );
                                                          -( PWMC ) PWMC అంతరాయం_2 స్థితి_2 రిజిస్టరు
                                                          AT91C_PWMC_SR EQU( 0xFFFCC00C );
                                                          -( PWMC ) PWMC స్థితి_2 రిజిస్టరు
                                                          AT91C_PWMC_IMR EQU( 0xFFFCC018 );
                                                          -( PWMC ) PWMC అంతరాయం_2 ముసుగు_2 రిజిస్టరు
                                                          AT91C_PWMC_MR EQU( 0xFFFCC000 );
                                                          -( PWMC ) PWMC బహుళకం రిజిస్టరు
                                                          AT91C_PWMC_ENA EQU( 0xFFFCC004 );
                                                          -( PWMC ) PWMC Enable రిజిస్టరు
/* - ========== Register definition for UDP peripheral ========== */
                                                          AT91C_UDP_IMR EQU( 0xFFFB0018 );
                                                          -( UDP ) అంతరాయం_2 ముసుగు_2 రిజిస్టరు
                                                          AT91C_UDP_FADDR EQU( 0xFFFB0008 );
                                                          -( UDP ) Function చిరునామా రిజిస్టరు
                                                          AT91_C_UDP_అంకె EQU( 0xFFFB0000 );
                                                          -( UDP ) చట్రం సంఖ్య_2 రిజిస్టరు
                                                          AT91C_UDP_FDR EQU( 0xFFFB0050 );
                                                          -( UDP ) Endpoint FIFO దత్తాంశం రిజిస్టరు
                                                          AT91C_UDP_ISR EQU( 0xFFFB001C );
                                                          -( UDP ) అంతరాయం_2 స్థితి_2 రిజిస్టరు
                                                          AT91C_UDP_CSR EQU( 0xFFFB0030 );
                                                          -( UDP ) Endpoint Control and స్థితి_2 రిజిస్టరు
                                                          AT91C_UDP_IDR EQU( 0xFFFB0014 );
                                                          -( UDP ) అంతరాయం_2 Disable రిజిస్టరు
                                                          AT91C_UDP_ICR EQU( 0xFFFB0020 );
                                                          -( UDP ) అంతరాయం_2 Clear రిజిస్టరు
                                                          AT91C_UDP_RSTEP EQU( 0xFFFB0028 );
                                                          -( UDP ) Reset Endpoint రిజిస్టరు
                                                          AT91C_UDP_TXVC EQU( 0xFFFB0074 );
                                                          -( UDP ) Transceiver Control రిజిస్టరు
                                                          AT91C_UDP_GLBSTATE EQU( 0xFFFB0004 );
                                                          -( UDP ) Global State రిజిస్టరు
                                                          AT91C_UDP_IER EQU( 0xFFFB0010 );
                                                          -( UDP ) అంతరాయం_2 Enable రిజిస్టరు
/* - ========== Register definition for TC0 peripheral ========== */
                                                          AT91C_TC0_SR EQU( 0xFFFA0020 );
                                                          -( TC0 ) స్థితి_2 రిజిస్టరు
                                                          AT91C_TC0_RC EQU( 0xFFFA001C );
                                                          -( TC0 ) రిజిస్టరు C
                                                          AT91C_TC0_RB EQU( 0xFFFA0018 );
                                                          -( TC0 ) రిజిస్టరు B
                                                          AT91C_TC0_CCR EQU( 0xFFFA0000 );
                                                          -( TC0 ) Channel Control రిజిస్టరు
                                                          AT91C_TC0_CMR EQU( 0xFFFA0004 );
                                                          -( TC0 ) Channel బహుళకం రిజిస్టరు( Capture బహుళకం / Waveform బహుళకం )
                                                          AT91C_TC0_IER EQU( 0xFFFA0024 );
                                                          -( TC0 ) అంతరాయం_2 Enable రిజిస్టరు
                                                          AT91C_TC0_RA EQU( 0xFFFA0014 );
                                                          -( TC0 ) రిజిస్టరు A
                                                          AT91C_TC0_IDR EQU( 0xFFFA0028 );
                                                          -( TC0 ) అంతరాయం_2 Disable రిజిస్టరు
                                                          AT91C_TC0_CV EQU( 0xFFFA0010 );
                                                          -( TC0 ) Counter విలువ_2
                                                          AT91C_TC0_IMR EQU( 0xFFFA002C );
                                                          -( TC0 ) అంతరాయం_2 ముసుగు_2 రిజిస్టరు
/* - ========== Register definition for TC1 peripheral ========== */
                                                          AT91C_TC1_RB EQU( 0xFFFA0058 );
                                                          -( TC1 ) రిజిస్టరు B
                                                          AT91C_TC1_CCR EQU( 0xFFFA0040 );
                                                          -( TC1 ) Channel Control రిజిస్టరు
                                                          AT91C_TC1_IER EQU( 0xFFFA0064 );
                                                          -( TC1 ) అంతరాయం_2 Enable రిజిస్టరు
                                                          AT91C_TC1_IDR EQU( 0xFFFA0068 );
                                                          -( TC1 ) అంతరాయం_2 Disable రిజిస్టరు
                                                          AT91C_TC1_SR EQU( 0xFFFA0060 );
                                                          -( TC1 ) స్థితి_2 రిజిస్టరు
                                                          AT91C_TC1_CMR EQU( 0xFFFA0044 );
                                                          -( TC1 ) Channel బహుళకం రిజిస్టరు( Capture బహుళకం / Waveform బహుళకం )
                                                          AT91C_TC1_RA EQU( 0xFFFA0054 );
                                                          -( TC1 ) రిజిస్టరు A
                                                          AT91C_TC1_RC EQU( 0xFFFA005C );
                                                          -( TC1 ) రిజిస్టరు C
                                                          AT91C_TC1_IMR EQU( 0xFFFA006C );
                                                          -( TC1 ) అంతరాయం_2 ముసుగు_2 రిజిస్టరు
                                                          AT91C_TC1_CV EQU( 0xFFFA0050 );
                                                          -( TC1 ) Counter విలువ_2
/* - ========== Register definition for TC2 peripheral ========== */
                                                          AT91C_TC2_CMR EQU( 0xFFFA0084 );
                                                          -( TC2 ) Channel బహుళకం రిజిస్టరు( Capture బహుళకం / Waveform బహుళకం )
                                                          AT91C_TC2_CCR EQU( 0xFFFA0080 );
                                                          -( TC2 ) Channel Control రిజిస్టరు
                                                          AT91C_TC2_CV EQU( 0xFFFA0090 );
                                                          -( TC2 ) Counter విలువ_2
                                                          AT91C_TC2_RA EQU( 0xFFFA0094 );
                                                          -( TC2 ) రిజిస్టరు A
                                                          AT91C_TC2_RB EQU( 0xFFFA0098 );
                                                          -( TC2 ) రిజిస్టరు B
                                                          AT91C_TC2_IDR EQU( 0xFFFA00A8 );
                                                          -( TC2 ) అంతరాయం_2 Disable రిజిస్టరు
                                                          AT91C_TC2_IMR EQU( 0xFFFA00AC );
                                                          -( TC2 ) అంతరాయం_2 ముసుగు_2 రిజిస్టరు
                                                          AT91C_TC2_RC EQU( 0xFFFA009C );
                                                          -( TC2 ) రిజిస్టరు C
                                                          AT91C_TC2_IER EQU( 0xFFFA00A4 );
                                                          -( TC2 ) అంతరాయం_2 Enable రిజిస్టరు
                                                          AT91C_TC2_SR EQU( 0xFFFA00A0 );
                                                          -( TC2 ) స్థితి_2 రిజిస్టరు
/* - ========== Register definition for TCB peripheral ========== */
                                                          AT91C_TCB_BMR EQU( 0xFFFA00C4 );
                                                          -( TCB ) TC ఖండం బహుళకం రిజిస్టరు
                                                          AT91C_TCB_BCR EQU( 0xFFFA00C0 );
                                                          -( TCB ) TC ఖండం Control రిజిస్టరు
/* - ========== Register definition for CAN_MB0 peripheral ========== */
                                                          AT91C_CAN_MB0_MDL EQU( 0xFFFD0214 );
                                                          -( CAN_MB0 ) MailBox దత్తాంశం దిగువ రిజిస్టరు
                                                          AT91C_CAN_MB0_MAM EQU( 0xFFFD0204 );
                                                          -( CAN_MB0 ) MailBox Acceptance ముసుగు_2 రిజిస్టరు
                                                          AT91C_CAN_MB0_MCR EQU( 0xFFFD021C );
                                                          -( CAN_MB0 ) MailBox Control రిజిస్టరు
                                                          AT91C_CAN_MB0_MID EQU( 0xFFFD0208 );
                                                          -( CAN_MB0 ) MailBox ID రిజిస్టరు
                                                          AT91C_CAN_MB0_MSR EQU( 0xFFFD0210 );
                                                          -( CAN_MB0 ) MailBox స్థితి_2 రిజిస్టరు
                                                          AT91C_CAN_MB0_MFID EQU( 0xFFFD020C );
                                                          -( CAN_MB0 ) MailBox Family ID రిజిస్టరు
                                                          AT91C_CAN_MB0_MDH EQU( 0xFFFD0218 );
                                                          -( CAN_MB0 ) MailBox దత్తాంశం ఎగువ రిజిస్టరు
                                                          AT91C_CAN_MB0_MMR EQU( 0xFFFD0200 );
                                                          -( CAN_MB0 ) MailBox బహుళకం రిజిస్టరు
/* - ========== Register definition for CAN_MB1 peripheral ========== */
                                                          AT91C_CAN_MB1_MDL EQU( 0xFFFD0234 );
                                                          -( CAN_MB1 ) MailBox దత్తాంశం దిగువ రిజిస్టరు
                                                          AT91C_CAN_MB1_MID EQU( 0xFFFD0228 );
                                                          -( CAN_MB1 ) MailBox ID రిజిస్టరు
                                                          AT91C_CAN_MB1_MMR EQU( 0xFFFD0220 );
                                                          -( CAN_MB1 ) MailBox బహుళకం రిజిస్టరు
                                                          AT91C_CAN_MB1_MSR EQU( 0xFFFD0230 );
                                                          -( CAN_MB1 ) MailBox స్థితి_2 రిజిస్టరు
                                                          AT91C_CAN_MB1_MAM EQU( 0xFFFD0224 );
                                                          -( CAN_MB1 ) MailBox Acceptance ముసుగు_2 రిజిస్టరు
                                                          AT91C_CAN_MB1_MDH EQU( 0xFFFD0238 );
                                                          -( CAN_MB1 ) MailBox దత్తాంశం ఎగువ రిజిస్టరు
                                                          AT91C_CAN_MB1_MCR EQU( 0xFFFD023C );
                                                          -( CAN_MB1 ) MailBox Control రిజిస్టరు
                                                          AT91C_CAN_MB1_MFID EQU( 0xFFFD022C );
                                                          -( CAN_MB1 ) MailBox Family ID రిజిస్టరు
/* - ========== Register definition for CAN_MB2 peripheral ========== */
                                                          AT91C_CAN_MB2_MCR EQU( 0xFFFD025C );
                                                          -( CAN_MB2 ) MailBox Control రిజిస్టరు
                                                          AT91C_CAN_MB2_MDH EQU( 0xFFFD0258 );
                                                          -( CAN_MB2 ) MailBox దత్తాంశం ఎగువ రిజిస్టరు
                                                          AT91C_CAN_MB2_MID EQU( 0xFFFD0248 );
                                                          -( CAN_MB2 ) MailBox ID రిజిస్టరు
                                                          AT91C_CAN_MB2_MDL EQU( 0xFFFD0254 );
                                                          -( CAN_MB2 ) MailBox దత్తాంశం దిగువ రిజిస్టరు
                                                          AT91C_CAN_MB2_MMR EQU( 0xFFFD0240 );
                                                          -( CAN_MB2 ) MailBox బహుళకం రిజిస్టరు
                                                          AT91C_CAN_MB2_MAM EQU( 0xFFFD0244 );
                                                          -( CAN_MB2 ) MailBox Acceptance ముసుగు_2 రిజిస్టరు
                                                          AT91C_CAN_MB2_MFID EQU( 0xFFFD024C );
                                                          -( CAN_MB2 ) MailBox Family ID రిజిస్టరు
                                                          AT91C_CAN_MB2_MSR EQU( 0xFFFD0250 );
                                                          -( CAN_MB2 ) MailBox స్థితి_2 రిజిస్టరు
/* - ========== Register definition for CAN_MB3 peripheral ========== */
                                                          AT91C_CAN_MB3_MFID EQU( 0xFFFD026C );
                                                          -( CAN_MB3 ) MailBox Family ID రిజిస్టరు
                                                          AT91C_CAN_MB3_MAM EQU( 0xFFFD0264 );
                                                          -( CAN_MB3 ) MailBox Acceptance ముసుగు_2 రిజిస్టరు
                                                          AT91C_CAN_MB3_MID EQU( 0xFFFD0268 );
                                                          -( CAN_MB3 ) MailBox ID రిజిస్టరు
                                                          AT91C_CAN_MB3_MCR EQU( 0xFFFD027C );
                                                          -( CAN_MB3 ) MailBox Control రిజిస్టరు
                                                          AT91C_CAN_MB3_MMR EQU( 0xFFFD0260 );
                                                          -( CAN_MB3 ) MailBox బహుళకం రిజిస్టరు
                                                          AT91C_CAN_MB3_MSR EQU( 0xFFFD0270 );
                                                          -( CAN_MB3 ) MailBox స్థితి_2 రిజిస్టరు
                                                          AT91C_CAN_MB3_MDL EQU( 0xFFFD0274 );
                                                          -( CAN_MB3 ) MailBox దత్తాంశం దిగువ రిజిస్టరు
                                                          AT91C_CAN_MB3_MDH EQU( 0xFFFD0278 );
                                                          -( CAN_MB3 ) MailBox దత్తాంశం ఎగువ రిజిస్టరు
/* - ========== Register definition for CAN_MB4 peripheral ========== */
                                                          AT91C_CAN_MB4_MID EQU( 0xFFFD0288 );
                                                          -( CAN_MB4 ) MailBox ID రిజిస్టరు
                                                          AT91C_CAN_MB4_MMR EQU( 0xFFFD0280 );
                                                          -( CAN_MB4 ) MailBox బహుళకం రిజిస్టరు
                                                          AT91C_CAN_MB4_MDH EQU( 0xFFFD0298 );
                                                          -( CAN_MB4 ) MailBox దత్తాంశం ఎగువ రిజిస్టరు
                                                          AT91C_CAN_MB4_MFID EQU( 0xFFFD028C );
                                                          -( CAN_MB4 ) MailBox Family ID రిజిస్టరు
                                                          AT91C_CAN_MB4_MSR EQU( 0xFFFD0290 );
                                                          -( CAN_MB4 ) MailBox స్థితి_2 రిజిస్టరు
                                                          AT91C_CAN_MB4_MCR EQU( 0xFFFD029C );
                                                          -( CAN_MB4 ) MailBox Control రిజిస్టరు
                                                          AT91C_CAN_MB4_MDL EQU( 0xFFFD0294 );
                                                          -( CAN_MB4 ) MailBox దత్తాంశం దిగువ రిజిస్టరు
                                                          AT91C_CAN_MB4_MAM EQU( 0xFFFD0284 );
                                                          -( CAN_MB4 ) MailBox Acceptance ముసుగు_2 రిజిస్టరు
/* - ========== Register definition for CAN_MB5 peripheral ========== */
                                                          AT91C_CAN_MB5_MSR EQU( 0xFFFD02B0 );
                                                          -( CAN_MB5 ) MailBox స్థితి_2 రిజిస్టరు
                                                          AT91C_CAN_MB5_MCR EQU( 0xFFFD02BC );
                                                          -( CAN_MB5 ) MailBox Control రిజిస్టరు
                                                          AT91C_CAN_MB5_MFID EQU( 0xFFFD02AC );
                                                          -( CAN_MB5 ) MailBox Family ID రిజిస్టరు
                                                          AT91C_CAN_MB5_MDH EQU( 0xFFFD02B8 );
                                                          -( CAN_MB5 ) MailBox దత్తాంశం ఎగువ రిజిస్టరు
                                                          AT91C_CAN_MB5_MID EQU( 0xFFFD02A8 );
                                                          -( CAN_MB5 ) MailBox ID రిజిస్టరు
                                                          AT91C_CAN_MB5_MMR EQU( 0xFFFD02A0 );
                                                          -( CAN_MB5 ) MailBox బహుళకం రిజిస్టరు
                                                          AT91C_CAN_MB5_MDL EQU( 0xFFFD02B4 );
                                                          -( CAN_MB5 ) MailBox దత్తాంశం దిగువ రిజిస్టరు
                                                          AT91C_CAN_MB5_MAM EQU( 0xFFFD02A4 );
                                                          -( CAN_MB5 ) MailBox Acceptance ముసుగు_2 రిజిస్టరు
/* - ========== Register definition for CAN_MB6 peripheral ========== */
                                                          AT91C_CAN_MB6_MFID EQU( 0xFFFD02CC );
                                                          -( CAN_MB6 ) MailBox Family ID రిజిస్టరు
                                                          AT91C_CAN_MB6_MID EQU( 0xFFFD02C8 );
                                                          -( CAN_MB6 ) MailBox ID రిజిస్టరు
                                                          AT91C_CAN_MB6_MAM EQU( 0xFFFD02C4 );
                                                          -( CAN_MB6 ) MailBox Acceptance ముసుగు_2 రిజిస్టరు
                                                          AT91C_CAN_MB6_MSR EQU( 0xFFFD02D0 );
                                                          -( CAN_MB6 ) MailBox స్థితి_2 రిజిస్టరు
                                                          AT91C_CAN_MB6_MDL EQU( 0xFFFD02D4 );
                                                          -( CAN_MB6 ) MailBox దత్తాంశం దిగువ రిజిస్టరు
                                                          AT91C_CAN_MB6_MCR EQU( 0xFFFD02DC );
                                                          -( CAN_MB6 ) MailBox Control రిజిస్టరు
                                                          AT91C_CAN_MB6_MDH EQU( 0xFFFD02D8 );
                                                          -( CAN_MB6 ) MailBox దత్తాంశం ఎగువ రిజిస్టరు
                                                          AT91C_CAN_MB6_MMR EQU( 0xFFFD02C0 );
                                                          -( CAN_MB6 ) MailBox బహుళకం రిజిస్టరు
/* - ========== Register definition for CAN_MB7 peripheral ========== */
                                                          AT91C_CAN_MB7_MCR EQU( 0xFFFD02FC );
                                                          -( CAN_MB7 ) MailBox Control రిజిస్టరు
                                                          AT91C_CAN_MB7_MDH EQU( 0xFFFD02F8 );
                                                          -( CAN_MB7 ) MailBox దత్తాంశం ఎగువ రిజిస్టరు
                                                          AT91C_CAN_MB7_MFID EQU( 0xFFFD02EC );
                                                          -( CAN_MB7 ) MailBox Family ID రిజిస్టరు
                                                          AT91C_CAN_MB7_MDL EQU( 0xFFFD02F4 );
                                                          -( CAN_MB7 ) MailBox దత్తాంశం దిగువ రిజిస్టరు
                                                          AT91C_CAN_MB7_MID EQU( 0xFFFD02E8 );
                                                          -( CAN_MB7 ) MailBox ID రిజిస్టరు
                                                          AT91C_CAN_MB7_MMR EQU( 0xFFFD02E0 );
                                                          -( CAN_MB7 ) MailBox బహుళకం రిజిస్టరు
                                                          AT91C_CAN_MB7_MAM EQU( 0xFFFD02E4 );
                                                          -( CAN_MB7 ) MailBox Acceptance ముసుగు_2 రిజిస్టరు
                                                          AT91C_CAN_MB7_MSR EQU( 0xFFFD02F0 );
                                                          -( CAN_MB7 ) MailBox స్థితి_2 రిజిస్టరు
/* - ========== Register definition for CAN peripheral ========== */
                                                          AT91C_CAN_TCR EQU( 0xFFFD0024 );
                                                          -( CAN ) Transfer Command రిజిస్టరు
                                                          AT91C_CAN_IMR EQU( 0xFFFD000C );
                                                          -( CAN ) అంతరాయం_2 ముసుగు_2 రిజిస్టరు
                                                          AT91C_CAN_IER EQU( 0xFFFD0004 );
                                                          -( CAN ) అంతరాయం_2 Enable రిజిస్టరు
                                                          AT91C_CAN_ECR EQU( 0xFFFD0020 );
                                                          -( CAN ) Error Counter రిజిస్టరు
                                                          AT91C_CAN_TIMESTP EQU( 0xFFFD001C );
                                                          -( CAN ) సమయం Stamp రిజిస్టరు
                                                          AT91C_CAN_MR EQU( 0xFFFD0000 );
                                                          -( CAN ) బహుళకం రిజిస్టరు
                                                          AT91C_CAN_IDR EQU( 0xFFFD0008 );
                                                          -( CAN ) అంతరాయం_2 Disable రిజిస్టరు
                                                          AT91C_CAN_ACR EQU( 0xFFFD0028 );
                                                          -( CAN ) Abort Command రిజిస్టరు
                                                          AT91C_CAN_TIM EQU( 0xFFFD0018 );
                                                          -( CAN ) Timer రిజిస్టరు
                                                          AT91C_CAN_SR EQU( 0xFFFD0010 );
                                                          -( CAN ) స్థితి_2 రిజిస్టరు
                                                          AT91C_CAN_BR EQU( 0xFFFD0014 );
                                                          -( CAN ) Baudrate రిజిస్టరు
                                                          AT91C_CAN_VR EQU( 0xFFFD00FC );
                                                          -( CAN ) సంస్కరణ_2 రిజిస్టరు
/* - ========== Register definition for EMAC peripheral ========== */
                                                          AT91C_EMAC_ISR EQU( 0xFFFDC024 );
                                                          -( EMAC ) అంతరాయం_2 స్థితి_2 రిజిస్టరు
                                                          AT91C_EMAC_SA4H EQU( 0xFFFDC0B4 );
                                                          -( EMAC ) Specific చిరునామా 4 శిఖరం, చివరి 2 బైట్లు_2
                                                          AT91C_EMAC_SA1L EQU( 0xFFFDC098 );
                                                          -( EMAC ) Specific చిరునామా 1 Bottom, మొదటి 4 బైట్లు_2
                                                          AT91C_EMAC_ELE EQU( 0xFFFDC078 );
                                                          -( EMAC ) Excessive నిడివి Errors రిజిస్టరు
                                                          AT91C_EMAC_LCOL EQU( 0xFFFDC05C );
                                                          -( EMAC ) Late Collision రిజిస్టరు
                                                          AT91C_EMAC_RLE EQU( 0xFFFDC088 );
                                                          -( EMAC ) Receive నిడివి క్షేత్రం_2 Mismatch రిజిస్టరు
                                                          AT91C_EMAC_WOL EQU( 0xFFFDC0C4 );
                                                          -( EMAC ) Wake On LAN రిజిస్టరు
                                                          AT91C_EMAC_DTF EQU( 0xFFFDC058 );
                                                          -( EMAC ) Deferred సంప్రేషణ చట్రం రిజిస్టరు
                                                          AT91C_EMAC_TUND EQU( 0xFFFDC064 );
                                                          -( EMAC ) Transmit Underrun Error రిజిస్టరు
                                                          AT91C_EMAC_NCR EQU( 0xFFFDC000 );
                                                          -( EMAC ) జాలం Control రిజిస్టరు
                                                          AT91C_EMAC_SA4L EQU( 0xFFFDC0B0 );
                                                          -( EMAC ) Specific చిరునామా 4 Bottom, మొదటి 4 బైట్లు_2
                                                          AT91C_EMAC_RSR EQU( 0xFFFDC020 );
                                                          -( EMAC ) Receive స్థితి_2 రిజిస్టరు
                                                          AT91C_EMAC_SA3L EQU( 0xFFFDC0A8 );
                                                          -( EMAC ) Specific చిరునామా 3 Bottom, మొదటి 4 బైట్లు_2
                                                          AT91C_EMAC_TSR EQU( 0xFFFDC014 );
                                                          -( EMAC ) Transmit స్థితి_2 రిజిస్టరు
                                                          AT91C_EMAC_IDR EQU( 0xFFFDC02C );
                                                          -( EMAC ) అంతరాయం_2 Disable రిజిస్టరు
                                                          AT91C_EMAC_RSE EQU( 0xFFFDC074 );
                                                          -( EMAC ) Receive చిహ్నం Errors రిజిస్టరు
                                                          AT91C_EMAC_ECOL EQU( 0xFFFDC060 );
                                                          -( EMAC ) Excessive Collision రిజిస్టరు
                                                          AT91C_EMAC_TID EQU( 0xFFFDC0B8 );
                                                          -( EMAC ) Type ID Checking రిజిస్టరు
                                                          AT91C_EMAC_HRB EQU( 0xFFFDC090 );
                                                          -( EMAC ) Hash చిరునామా Bottom[ 31 : 0 ]
                                                          AT91C_EMAC_TBQP EQU( 0xFFFDC01C );
                                                          -( EMAC ) Transmit బఫరు వరుస సూచిక_2
                                                          AT91C_EMAC_USRIO EQU( 0xFFFDC0C0 );
                                                          -( EMAC ) USER ఆదానం / Output రిజిస్టరు
                                                          AT91C_EMAC_PTR EQU( 0xFFFDC038 );
                                                          -( EMAC ) Pause సమయం రిజిస్టరు
                                                          AT91C_EMAC_SA2H EQU( 0xFFFDC0A4 );
                                                          -( EMAC ) Specific చిరునామా 2 శిఖరం, చివరి 2 బైట్లు_2
                                                          AT91C_EMAC_ROV EQU( 0xFFFDC070 );
                                                          -( EMAC ) Receive Overrun Errors రిజిస్టరు
                                                          AT91C_EMAC_ALE EQU( 0xFFFDC054 );
                                                          -( EMAC ) Alignment Error రిజిస్టరు
                                                          AT91C_EMAC_RJA EQU( 0xFFFDC07C );
                                                          -( EMAC ) Receive Jabbers రిజిస్టరు
                                                          AT91C_EMAC_RBQP EQU( 0xFFFDC018 );
                                                          -( EMAC ) Receive బఫరు వరుస సూచిక_2
                                                          AT91C_EMAC_TPF EQU( 0xFFFDC08C );
                                                          -( EMAC ) Transmitted Pause చట్రాలు రిజిస్టరు
                                                          AT91C_EMAC_NCFGR EQU( 0xFFFDC004 );
                                                          -( EMAC ) జాలం Configuration రిజిస్టరు
                                                          AT91C_EMAC_HRT EQU( 0xFFFDC094 );
                                                          -( EMAC ) Hash చిరునామా శిఖరం[ 63 : 32 ]
                                                          AT91C_EMAC_USF EQU( 0xFFFDC080 );
                                                          -( EMAC ) Undersize చట్రాలు రిజిస్టరు
                                                          AT91C_EMAC_FCSE EQU( 0xFFFDC050 );
                                                          -( EMAC ) చట్రం Check Sequence Error రిజిస్టరు
                                                          AT91C_EMAC_TPQ EQU( 0xFFFDC0BC );
                                                          -( EMAC ) Transmit Pause కాలాంశం_2 రిజిస్టరు
                                                          AT91C_EMAC_MAN EQU( 0xFFFDC034 );
                                                          -( EMAC ) PHY Maintenance రిజిస్టరు
                                                          AT91C_EMAC_FTO EQU( 0xFFFDC040 );
                                                          -( EMAC ) చట్రాలు Transmitted OK రిజిస్టరు
                                                          AT91C_EMAC_REV EQU( 0xFFFDC0FC );
                                                          -( EMAC ) Revision రిజిస్టరు
                                                          AT91C_EMAC_IMR EQU( 0xFFFDC030 );
                                                          -( EMAC ) అంతరాయం_2 ముసుగు_2 రిజిస్టరు
                                                          AT91C_EMAC_SCF EQU( 0xFFFDC044 );
                                                          -( EMAC ) Single Collision చట్రం రిజిస్టరు
                                                          AT91C_EMAC_PFR EQU( 0xFFFDC03C );
                                                          -( EMAC ) Pause చట్రాలు received రిజిస్టరు
                                                          AT91C_EMAC_MCF EQU( 0xFFFDC048 );
                                                          -( EMAC ) గుణిజం Collision చట్రం రిజిస్టరు
                                                          AT91C_EMAC_NSR EQU( 0xFFFDC008 );
                                                          -( EMAC ) జాలం స్థితి_2 రిజిస్టరు
                                                          AT91C_EMAC_SA2L EQU( 0xFFFDC0A0 );
                                                          -( EMAC ) Specific చిరునామా 2 Bottom, మొదటి 4 బైట్లు_2
                                                          AT91C_EMAC_FRO EQU( 0xFFFDC04C );
                                                          -( EMAC ) చట్రాలు Received OK రిజిస్టరు
                                                          AT91C_EMAC_IER EQU( 0xFFFDC028 );
                                                          -( EMAC ) అంతరాయం_2 Enable రిజిస్టరు
                                                          AT91C_EMAC_SA1H EQU( 0xFFFDC09C );
                                                          -( EMAC ) Specific చిరునామా 1 శిఖరం, చివరి 2 బైట్లు_2
                                                          AT91C_EMAC_CSE EQU( 0xFFFDC068 );
                                                          -( EMAC ) Carrier Sense Error రిజిస్టరు
                                                          AT91C_EMAC_SA3H EQU( 0xFFFDC0AC );
                                                          -( EMAC ) Specific చిరునామా 3 శిఖరం, చివరి 2 బైట్లు_2
                                                          AT91C_EMAC_RRE EQU( 0xFFFDC06C );
                                                          -( EMAC ) Receive Resource Error రిజిస్టరు
                                                          AT91C_EMAC_STE EQU( 0xFFFDC084 );
                                                          -( EMAC ) SQE Test Error రిజిస్టరు
/* - ========== Register definition for PDC_ADC peripheral ========== */
                                                          AT91C_ADC_PTSR EQU( 0xFFFD8124 );
                                                          -( PDC_ADC ) PDC Transfer స్థితి_2 రిజిస్టరు
                                                          AT91C_ADC_PTCR EQU( 0xFFFD8120 );
                                                          -( PDC_ADC ) PDC Transfer Control రిజిస్టరు
                                                          AT91C_ADC_TNPR EQU( 0xFFFD8118 );
                                                          -( PDC_ADC ) Transmit తదుపరి సూచిక_2 రిజిస్టరు
                                                          AT91C_ADC_TNCR EQU( 0xFFFD811C );
                                                          -( PDC_ADC ) Transmit తదుపరి Counter రిజిస్టరు
                                                          AT91C_ADC_RNPR EQU( 0xFFFD8110 );
                                                          -( PDC_ADC ) Receive తదుపరి సూచిక_2 రిజిస్టరు
                                                          AT91C_ADC_RNCR EQU( 0xFFFD8114 );
                                                          -( PDC_ADC ) Receive తదుపరి Counter రిజిస్టరు
                                                          AT91C_ADC_RPR EQU( 0xFFFD8100 );
                                                          -( PDC_ADC ) Receive సూచిక_2 రిజిస్టరు
                                                          AT91C_ADC_TCR EQU( 0xFFFD810C );
                                                          -( PDC_ADC ) Transmit Counter రిజిస్టరు
                                                          AT91C_ADC_TPR EQU( 0xFFFD8108 );
                                                          -( PDC_ADC ) Transmit సూచిక_2 రిజిస్టరు
                                                          AT91C_ADC_RCR EQU( 0xFFFD8104 );
                                                          -( PDC_ADC ) Receive Counter రిజిస్టరు
/* - ========== Register definition for ADC peripheral ========== */
                                                          AT91C_ADC_CDR2 EQU( 0xFFFD8038 );
                                                          -( ADC ) ADC Channel దత్తాంశం రిజిస్టరు 2
                                                          AT91C_ADC_CDR3 EQU( 0xFFFD803C );
                                                          -( ADC ) ADC Channel దత్తాంశం రిజిస్టరు 3
                                                          AT91C_ADC_CDR0 EQU( 0xFFFD8030 );
                                                          -( ADC ) ADC Channel దత్తాంశం రిజిస్టరు 0
                                                          AT91C_ADC_CDR5 EQU( 0xFFFD8044 );
                                                          -( ADC ) ADC Channel దత్తాంశం రిజిస్టరు 5
                                                          AT91C_ADC_CHDR EQU( 0xFFFD8014 );
                                                          -( ADC ) ADC Channel Disable రిజిస్టరు
                                                          AT91C_ADC_SR EQU( 0xFFFD801C );
                                                          -( ADC ) ADC స్థితి_2 రిజిస్టరు
                                                          AT91C_ADC_CDR4 EQU( 0xFFFD8040 );
                                                          -( ADC ) ADC Channel దత్తాంశం రిజిస్టరు 4
                                                          AT91C_ADC_CDR1 EQU( 0xFFFD8034 );
                                                          -( ADC ) ADC Channel దత్తాంశం రిజిస్టరు 1
                                                          AT91C_ADC_LCDR EQU( 0xFFFD8020 );
                                                          -( ADC ) ADC చివరి Converted దత్తాంశం రిజిస్టరు
                                                          AT91C_ADC_IDR EQU( 0xFFFD8028 );
                                                          -( ADC ) ADC అంతరాయం_2 Disable రిజిస్టరు
                                                          AT91C_ADC_CR EQU( 0xFFFD8000 );
                                                          -( ADC ) ADC Control రిజిస్టరు
                                                          AT91C_ADC_CDR7 EQU( 0xFFFD804C );
                                                          -( ADC ) ADC Channel దత్తాంశం రిజిస్టరు 7
                                                          AT91C_ADC_CDR6 EQU( 0xFFFD8048 );
                                                          -( ADC ) ADC Channel దత్తాంశం రిజిస్టరు 6
                                                          AT91C_ADC_IER EQU( 0xFFFD8024 );
                                                          -( ADC ) ADC అంతరాయం_2 Enable రిజిస్టరు
                                                          AT91C_ADC_CHER EQU( 0xFFFD8010 );
                                                          -( ADC ) ADC Channel Enable రిజిస్టరు
                                                          AT91C_ADC_CHSR EQU( 0xFFFD8018 );
                                                          -( ADC ) ADC Channel స్థితి_2 రిజిస్టరు
                                                          AT91C_ADC_MR EQU( 0xFFFD8004 );
                                                          -( ADC ) ADC బహుళకం రిజిస్టరు
                                                          AT91C_ADC_IMR EQU( 0xFFFD802C );
                                                          -( ADC ) ADC అంతరాయం_2 ముసుగు_2 రిజిస్టరు
/* - ========== Register definition for PDC_AES peripheral ========== */
                                                          AT91C_AES_TPR EQU( 0xFFFA4108 );
                                                          -( PDC_AES ) Transmit సూచిక_2 రిజిస్టరు
                                                          AT91C_AES_PTCR EQU( 0xFFFA4120 );
                                                          -( PDC_AES ) PDC Transfer Control రిజిస్టరు
                                                          AT91C_AES_RNPR EQU( 0xFFFA4110 );
                                                          -( PDC_AES ) Receive తదుపరి సూచిక_2 రిజిస్టరు
                                                          AT91C_AES_TNCR EQU( 0xFFFA411C );
                                                          -( PDC_AES ) Transmit తదుపరి Counter రిజిస్టరు
                                                          AT91C_AES_TCR EQU( 0xFFFA410C );
                                                          -( PDC_AES ) Transmit Counter రిజిస్టరు
                                                          AT91C_AES_RCR EQU( 0xFFFA4104 );
                                                          -( PDC_AES ) Receive Counter రిజిస్టరు
                                                          AT91C_AES_RNCR EQU( 0xFFFA4114 );
                                                          -( PDC_AES ) Receive తదుపరి Counter రిజిస్టరు
                                                          AT91C_AES_TNPR EQU( 0xFFFA4118 );
                                                          -( PDC_AES ) Transmit తదుపరి సూచిక_2 రిజిస్టరు
                                                          AT91C_AES_RPR EQU( 0xFFFA4100 );
                                                          -( PDC_AES ) Receive సూచిక_2 రిజిస్టరు
                                                          AT91C_AES_PTSR EQU( 0xFFFA4124 );
                                                          -( PDC_AES ) PDC Transfer స్థితి_2 రిజిస్టరు
/* - ========== Register definition for AES peripheral ========== */
                                                          AT91C_AES_IVxR EQU( 0xFFFA4060 );
                                                          -( AES ) Initialization సదిశ_2 x రిజిస్టరు
                                                          AT91C_AES_MR EQU( 0xFFFA4004 );
                                                          -( AES ) బహుళకం రిజిస్టరు
                                                          AT91C_AES_VR EQU( 0xFFFA40FC );
                                                          -( AES ) AES సంస్కరణ_2 రిజిస్టరు
                                                          AT91C_AES_ODATAxR EQU( 0xFFFA4050 );
                                                          -( AES ) Output దత్తాంశం x రిజిస్టరు
                                                          AT91C_AES_IDATAxR EQU( 0xFFFA4040 );
                                                          -( AES ) ఆదానం దత్తాంశం x రిజిస్టరు
                                                          AT91C_AES_CR EQU( 0xFFFA4000 );
                                                          -( AES ) Control రిజిస్టరు
                                                          AT91C_AES_IDR EQU( 0xFFFA4014 );
                                                          -( AES ) అంతరాయం_2 Disable రిజిస్టరు
                                                          AT91C_AES_IMR EQU( 0xFFFA4018 );
                                                          -( AES ) అంతరాయం_2 ముసుగు_2 రిజిస్టరు
                                                          AT91C_AES_IER EQU( 0xFFFA4010 );
                                                          -( AES ) అంతరాయం_2 Enable రిజిస్టరు
                                                          AT91C_AES_KEYWxR EQU( 0xFFFA4020 );
                                                          -( AES ) కీలకం_2 మాట_2 x రిజిస్టరు
                                                          AT91C_AES_ISR EQU( 0xFFFA401C );
                                                          -( AES ) అంతరాయం_2 స్థితి_2 రిజిస్టరు
/* - ========== Register definition for PDC_TDES peripheral ========== */
                                                          AT91C_TDES_RNCR EQU( 0xFFFA8114 );
                                                          -( PDC_TDES ) Receive తదుపరి Counter రిజిస్టరు
                                                          AT91C_TDES_TCR EQU( 0xFFFA810C );
                                                          -( PDC_TDES ) Transmit Counter రిజిస్టరు
                                                          AT91C_TDES_RCR EQU( 0xFFFA8104 );
                                                          -( PDC_TDES ) Receive Counter రిజిస్టరు
                                                          AT91C_TDES_TNPR EQU( 0xFFFA8118 );
                                                          -( PDC_TDES ) Transmit తదుపరి సూచిక_2 రిజిస్టరు
                                                          AT91C_TDES_RNPR EQU( 0xFFFA8110 );
                                                          -( PDC_TDES ) Receive తదుపరి సూచిక_2 రిజిస్టరు
                                                          AT91C_TDES_RPR EQU( 0xFFFA8100 );
                                                          -( PDC_TDES ) Receive సూచిక_2 రిజిస్టరు
                                                          AT91C_TDES_TNCR EQU( 0xFFFA811C );
                                                          -( PDC_TDES ) Transmit తదుపరి Counter రిజిస్టరు
                                                          AT91C_TDES_TPR EQU( 0xFFFA8108 );
                                                          -( PDC_TDES ) Transmit సూచిక_2 రిజిస్టరు
                                                          AT91C_TDES_PTSR EQU( 0xFFFA8124 );
                                                          -( PDC_TDES ) PDC Transfer స్థితి_2 రిజిస్టరు
                                                          AT91C_TDES_PTCR EQU( 0xFFFA8120 );
                                                          -( PDC_TDES ) PDC Transfer Control రిజిస్టరు
/* - ========== Register definition for TDES peripheral ========== */
                                                          AT91C_TDES_KEY2WxR EQU( 0xFFFA8028 );
                                                          -( TDES ) కీలకం_2 2 మాట_2 x రిజిస్టరు
                                                          AT91C_TDES_KEY3WxR EQU( 0xFFFA8030 );
                                                          -( TDES ) కీలకం_2 3 మాట_2 x రిజిస్టరు
                                                          AT91C_TDES_IDR EQU( 0xFFFA8014 );
                                                          -( TDES ) అంతరాయం_2 Disable రిజిస్టరు
                                                          AT91C_TDES_VR EQU( 0xFFFA80FC );
                                                          -( TDES ) TDES సంస్కరణ_2 రిజిస్టరు
                                                          AT91C_TDES_IVxR EQU( 0xFFFA8060 );
                                                          -( TDES ) Initialization సదిశ_2 x రిజిస్టరు
                                                          AT91C_TDES_ODATAxR EQU( 0xFFFA8050 );
                                                          -( TDES ) Output దత్తాంశం x రిజిస్టరు
                                                          AT91C_TDES_IMR EQU( 0xFFFA8018 );
                                                          -( TDES ) అంతరాయం_2 ముసుగు_2 రిజిస్టరు
                                                          AT91C_TDES_MR EQU( 0xFFFA8004 );
                                                          -( TDES ) బహుళకం రిజిస్టరు
                                                          AT91C_TDES_CR EQU( 0xFFFA8000 );
                                                          -( TDES ) Control రిజిస్టరు
                                                          AT91C_TDES_IER EQU( 0xFFFA8010 );
                                                          -( TDES ) అంతరాయం_2 Enable రిజిస్టరు
                                                          AT91C_TDES_ISR EQU( 0xFFFA801C );
                                                          -( TDES ) అంతరాయం_2 స్థితి_2 రిజిస్టరు
                                                          AT91C_TDES_IDATAxR EQU( 0xFFFA8040 );
                                                          -( TDES ) ఆదానం దత్తాంశం x రిజిస్టరు
                                                          AT91C_TDES_KEY1WxR EQU( 0xFFFA8020 );
                                                          -( TDES ) కీలకం_2 1 మాట_2 x రిజిస్టరు

/* - ***************************************************************************** */
/* -               PIO DEFINITIONS FOR AT91SAM7X256 */
/* - ***************************************************************************** */
                                                          AT91C_PIO_PA0 EQU( 1 << 0 );
                                                          -Pin Controlled by PA0
                                                          AT91C_PA0_RXD0 EQU( AT91C_PIO_PA0 );
                                                          -USART 0 Receive దత్తాంశం
                                                          AT91C_PIO_PA1 EQU( 1 << 1 );
                                                          -Pin Controlled by PA1
                                                          AT91C_PA1_TXD0 EQU( AT91C_PIO_PA1 );
                                                          -USART 0 Transmit దత్తాంశం
                                                          AT91C_PIO_PA10 EQU( 1 << 10 );
                                                          -Pin Controlled by PA10
                                                          AT91C_PA10_TWD EQU( AT91C_PIO_PA10 );
                                                          -TWI Two - wire Serial దత్తాంశం
                                                          AT91C_PIO_PA11 EQU( 1 << 11 );
                                                          -Pin Controlled by PA11
                                                          AT91C_PA11_TWCK EQU( AT91C_PIO_PA11 );
                                                          -TWI Two - wire Serial Clock
                                                          AT91C_PIO_PA12 EQU( 1 << 12 );
                                                          -Pin Controlled by PA12
                                                          AT91C_PA12_NPCS00 EQU( AT91C_PIO_PA12 );
                                                          -SPI 0 Peripheral Chip Select 0
                                                          AT91C_PIO_PA13 EQU( 1 << 13 );
                                                          -Pin Controlled by PA13
                                                          AT91C_PA13_NPCS01 EQU( AT91C_PIO_PA13 );
                                                          -SPI 0 Peripheral Chip Select 1
                                                          AT91C_PA13_PCK1 EQU( AT91C_PIO_PA13 );
                                                          -PMC Programmable Clock Output 1
                                                          AT91C_PIO_PA14 EQU( 1 << 14 );
                                                          -Pin Controlled by PA14
                                                          AT91C_PA14_NPCS02 EQU( AT91C_PIO_PA14 );
                                                          -SPI 0 Peripheral Chip Select 2
                                                          AT91C_PA14_IRQ1 EQU( AT91C_PIO_PA14 );
                                                          -External అంతరాయం_2 1
                                                          AT91C_PIO_PA15 EQU( 1 << 15 );
                                                          -Pin Controlled by PA15
                                                          AT91C_PA15_NPCS03 EQU( AT91C_PIO_PA15 );
                                                          -SPI 0 Peripheral Chip Select 3
                                                          AT91C_PA15_TCLK2 EQU( AT91C_PIO_PA15 );
                                                          -Timer Counter 2 external clock ఆదానం_2
                                                          AT91C_PIO_PA16 EQU( 1 << 16 );
                                                          -Pin Controlled by PA16
                                                          AT91C_PA16_MISO0 EQU( AT91C_PIO_PA16 );
                                                          -SPI 0 Master లోపల_3 Slave
                                                          AT91C_PIO_PA17 EQU( 1 << 17 );
                                                          -Pin Controlled by PA17
                                                          AT91C_PA17_MOSI0 EQU( AT91C_PIO_PA17 );
                                                          -SPI 0 Master బహిర్గతం_3 Slave
                                                          AT91C_PIO_PA18 EQU( 1 << 18 );
                                                          -Pin Controlled by PA18
                                                          AT91C_PA18_SPCK0 EQU( AT91C_PIO_PA18 );
                                                          -SPI 0 Serial Clock
                                                          AT91C_PIO_PA19 EQU( 1 << 19 );
                                                          -Pin Controlled by PA19
                                                          AT91C_PA19_CANRX EQU( AT91C_PIO_PA19 );
                                                          -CAN Receive
                                                          AT91C_PIO_PA2 EQU( 1 << 2 );
                                                          -Pin Controlled by PA2
                                                          AT91C_PA2_SCK0 EQU( AT91C_PIO_PA2 );
                                                          -USART 0 Serial Clock
                                                          AT91C_PA2_NPCS11 EQU( AT91C_PIO_PA2 );
                                                          -SPI 1 Peripheral Chip Select 1
                                                          AT91C_PIO_PA20 EQU( 1 << 20 );
                                                          -Pin Controlled by PA20
                                                          AT91C_PA20_CANTX EQU( AT91C_PIO_PA20 );
                                                          -CAN Transmit
                                                          AT91C_PIO_PA21 EQU( 1 << 21 );
                                                          -Pin Controlled by PA21
                                                          AT91C_PA21_TF EQU( AT91C_PIO_PA21 );
                                                          -SSC Transmit చట్రం Sync
                                                          AT91C_PA21_NPCS10 EQU( AT91C_PIO_PA21 );
                                                          -SPI 1 Peripheral Chip Select 0
                                                          AT91C_PIO_PA22 EQU( 1 << 22 );
                                                          -Pin Controlled by PA22
                                                          AT91C_PA22_TK EQU( AT91C_PIO_PA22 );
                                                          -SSC Transmit Clock
                                                          AT91C_PA22_SPCK1 EQU( AT91C_PIO_PA22 );
                                                          -SPI 1 Serial Clock
                                                          AT91C_PIO_PA23 EQU( 1 << 23 );
                                                          -Pin Controlled by PA23
                                                          AT91C_PA23_TD EQU( AT91C_PIO_PA23 );
                                                          -SSC Transmit దత్తాంశం_2
                                                          AT91C_PA23_MOSI1 EQU( AT91C_PIO_PA23 );
                                                          -SPI 1 Master బహిర్గతం_3 Slave
                                                          AT91C_PIO_PA24 EQU( 1 << 24 );
                                                          -Pin Controlled by PA24
                                                          AT91C_PA24_RD EQU( AT91C_PIO_PA24 );
                                                          -SSC Receive దత్తాంశం
                                                          AT91C_PA24_MISO1 EQU( AT91C_PIO_PA24 );
                                                          -SPI 1 Master లోపల_3 Slave
                                                          AT91C_PIO_PA25 EQU( 1 << 25 );
                                                          -Pin Controlled by PA25
                                                          AT91C_PA25_RK EQU( AT91C_PIO_PA25 );
                                                          -SSC Receive Clock
                                                          AT91C_PA25_NPCS11 EQU( AT91C_PIO_PA25 );
                                                          -SPI 1 Peripheral Chip Select 1
                                                          AT91C_PIO_PA26 EQU( 1 << 26 );
                                                          -Pin Controlled by PA26
                                                          AT91C_PA26_RF EQU( AT91C_PIO_PA26 );
                                                          -SSC Receive చట్రం Sync
                                                          AT91C_PA26_NPCS12 EQU( AT91C_PIO_PA26 );
                                                          -SPI 1 Peripheral Chip Select 2
                                                          AT91C_PIO_PA27 EQU( 1 << 27 );
                                                          -Pin Controlled by PA27
                                                          AT91C_PA27_DRXD EQU( AT91C_PIO_PA27 );
                                                          -DBGU Debug Receive దత్తాంశం
                                                          AT91C_PA27_PCK3 EQU( AT91C_PIO_PA27 );
                                                          -PMC Programmable Clock Output 3
                                                          AT91C_PIO_PA28 EQU( 1 << 28 );
                                                          -Pin Controlled by PA28
                                                          AT91C_PA28_DTXD EQU( AT91C_PIO_PA28 );
                                                          -DBGU Debug Transmit దత్తాంశం
                                                          AT91C_PIO_PA29 EQU( 1 << 29 );
                                                          -Pin Controlled by PA29
                                                          AT91C_PA29_FIQ EQU( AT91C_PIO_PA29 );
                                                          -AIC Fast అంతరాయం_2 ఆదానం
                                                          AT91C_PA29_NPCS13 EQU( AT91C_PIO_PA29 );
                                                          -SPI 1 Peripheral Chip Select 3
                                                          AT91C_PIO_PA3 EQU( 1 << 3 );
                                                          -Pin Controlled by PA3
                                                          AT91C_PA3_RTS0 EQU( AT91C_PIO_PA3 );
                                                          -USART 0 Ready గమ్యం_2 Send
                                                          AT91C_PA3_NPCS12 EQU( AT91C_PIO_PA3 );
                                                          -SPI 1 Peripheral Chip Select 2
                                                          AT91C_PIO_PA30 EQU( 1 << 30 );
                                                          -Pin Controlled by PA30
                                                          AT91C_PA30_IRQ0 EQU( AT91C_PIO_PA30 );
                                                          -External అంతరాయం_2 0
                                                          AT91C_PA30_PCK2 EQU( AT91C_PIO_PA30 );
                                                          -PMC Programmable Clock Output 2
                                                          AT91C_PIO_PA4 EQU( 1 << 4 );
                                                          -Pin Controlled by PA4
                                                          AT91C_PA4_CTS0 EQU( AT91C_PIO_PA4 );
                                                          -USART 0 Clear గమ్యం_2 Send
                                                          AT91C_PA4_NPCS13 EQU( AT91C_PIO_PA4 );
                                                          -SPI 1 Peripheral Chip Select 3
                                                          AT91C_PIO_PA5 EQU( 1 << 5 );
                                                          -Pin Controlled by PA5
                                                          AT91C_PA5_RXD1 EQU( AT91C_PIO_PA5 );
                                                          -USART 1 Receive దత్తాంశం
                                                          AT91C_PIO_PA6 EQU( 1 << 6 );
                                                          -Pin Controlled by PA6
                                                          AT91C_PA6_TXD1 EQU( AT91C_PIO_PA6 );
                                                          -USART 1 Transmit దత్తాంశం
                                                          AT91C_PIO_PA7 EQU( 1 << 7 );
                                                          -Pin Controlled by PA7
                                                          AT91C_PA7_SCK1 EQU( AT91C_PIO_PA7 );
                                                          -USART 1 Serial Clock
                                                          AT91C_PA7_NPCS01 EQU( AT91C_PIO_PA7 );
                                                          -SPI 0 Peripheral Chip Select 1
                                                          AT91C_PIO_PA8 EQU( 1 << 8 );
                                                          -Pin Controlled by PA8
                                                          AT91C_PA8_RTS1 EQU( AT91C_PIO_PA8 );
                                                          -USART 1 Ready గమ్యం_2 Send
                                                          AT91C_PA8_NPCS02 EQU( AT91C_PIO_PA8 );
                                                          -SPI 0 Peripheral Chip Select 2
                                                          AT91C_PIO_PA9 EQU( 1 << 9 );
                                                          -Pin Controlled by PA9
                                                          AT91C_PA9_CTS1 EQU( AT91C_PIO_PA9 );
                                                          -USART 1 Clear గమ్యం_2 Send
                                                          AT91C_PA9_NPCS03 EQU( AT91C_PIO_PA9 );
                                                          -SPI 0 Peripheral Chip Select 3
                                                          AT91C_PIO_PB0 EQU( 1 << 0 );
                                                          -Pin Controlled by PB0
                                                          AT91C_PB0_ETXCK_EREFCK EQU( AT91C_PIO_PB0 );
                                                          -Ethernet MAC Transmit Clock / Reference Clock
                                                          AT91C_PB0_PCK0 EQU( AT91C_PIO_PB0 );
                                                          -PMC Programmable Clock Output 0
                                                          AT91C_PIO_PB1 EQU( 1 << 1 );
                                                          -Pin Controlled by PB1
                                                          AT91C_PB1_ETXEN EQU( AT91C_PIO_PB1 );
                                                          -Ethernet MAC Transmit Enable
                                                          AT91C_PIO_PB10 EQU( 1 << 10 );
                                                          -Pin Controlled by PB10
                                                          AT91C_PB10_ETX2 EQU( AT91C_PIO_PB10 );
                                                          -Ethernet MAC Transmit దత్తాంశం 2
                                                          AT91C_PB10_NPCS11 EQU( AT91C_PIO_PB10 );
                                                          -SPI 1 Peripheral Chip Select 1
                                                          AT91C_PIO_PB11 EQU( 1 << 11 );
                                                          -Pin Controlled by PB11
                                                          AT91C_PB11_ETX3 EQU( AT91C_PIO_PB11 );
                                                          -Ethernet MAC Transmit దత్తాంశం 3
                                                          AT91C_PB11_NPCS12 EQU( AT91C_PIO_PB11 );
                                                          -SPI 1 Peripheral Chip Select 2
                                                          AT91C_PIO_PB12 EQU( 1 << 12 );
                                                          -Pin Controlled by PB12
                                                          AT91C_PB12_ETXER EQU( AT91C_PIO_PB12 );
                                                          -Ethernet MAC Transmit Coding Error
                                                          AT91C_PB12_TCLK0 EQU( AT91C_PIO_PB12 );
                                                          -Timer Counter 0 external clock ఆదానం_2
                                                          AT91C_PIO_PB13 EQU( 1 << 13 );
                                                          -Pin Controlled by PB13
                                                          AT91C_PB13_ERX2 EQU( AT91C_PIO_PB13 );
                                                          -Ethernet MAC Receive దత్తాంశం 2
                                                          AT91C_PB13_NPCS01 EQU( AT91C_PIO_PB13 );
                                                          -SPI 0 Peripheral Chip Select 1
                                                          AT91C_PIO_PB14 EQU( 1 << 14 );
                                                          -Pin Controlled by PB14
                                                          AT91C_PB14_ERX3 EQU( AT91C_PIO_PB14 );
                                                          -Ethernet MAC Receive దత్తాంశం 3
                                                          AT91C_PB14_NPCS02 EQU( AT91C_PIO_PB14 );
                                                          -SPI 0 Peripheral Chip Select 2
                                                          AT91C_PIO_PB15 EQU( 1 << 15 );
                                                          -Pin Controlled by PB15
                                                          AT91C_PB15_ERXDV EQU( AT91C_PIO_PB15 );
                                                          -Ethernet MAC Receive దత్తాంశం Valid
                                                          AT91C_PIO_PB16 EQU( 1 << 16 );
                                                          -Pin Controlled by PB16
                                                          AT91C_PB16_ECOL EQU( AT91C_PIO_PB16 );
                                                          -Ethernet MAC Collision Detected
                                                          AT91C_PB16_NPCS13 EQU( AT91C_PIO_PB16 );
                                                          -SPI 1 Peripheral Chip Select 3
                                                          AT91C_PIO_PB17 EQU( 1 << 17 );
                                                          -Pin Controlled by PB17
                                                          AT91C_PB17_ERXCK EQU( AT91C_PIO_PB17 );
                                                          -Ethernet MAC Receive Clock
                                                          AT91C_PB17_NPCS03 EQU( AT91C_PIO_PB17 );
                                                          -SPI 0 Peripheral Chip Select 3
                                                          AT91C_PIO_PB18 EQU( 1 << 18 );
                                                          -Pin Controlled by PB18
                                                          AT91C_PB18_EF100 EQU( AT91C_PIO_PB18 );
                                                          -Ethernet MAC Force 100 Mbits / sec
                                                          AT91C_PB18_ADTRG EQU( AT91C_PIO_PB18 );
                                                          -ADC External Trigger
                                                          AT91C_PIO_PB19 EQU( 1 << 19 );
                                                          -Pin Controlled by PB19
                                                          AT91C_PB19_PWM0 EQU( AT91C_PIO_PB19 );
                                                          -PWM Channel 0
                                                          AT91C_PB19_TCLK1 EQU( AT91C_PIO_PB19 );
                                                          -Timer Counter 1 external clock ఆదానం_2
                                                          AT91C_PIO_PB2 EQU( 1 << 2 );
                                                          -Pin Controlled by PB2
                                                          AT91C_PB2_ETX0 EQU( AT91C_PIO_PB2 );
                                                          -Ethernet MAC Transmit దత్తాంశం 0
                                                          AT91C_PIO_PB20 EQU( 1 << 20 );
                                                          -Pin Controlled by PB20
                                                          AT91C_PB20_PWM1 EQU( AT91C_PIO_PB20 );
                                                          -PWM Channel 1
                                                          AT91C_PB20_PCK0 EQU( AT91C_PIO_PB20 );
                                                          -PMC Programmable Clock Output 0
                                                          AT91C_PIO_PB21 EQU( 1 << 21 );
                                                          -Pin Controlled by PB21
                                                          AT91C_PB21_PWM2 EQU( AT91C_PIO_PB21 );
                                                          -PWM Channel 2
                                                          AT91C_PB21_PCK1 EQU( AT91C_PIO_PB21 );
                                                          -PMC Programmable Clock Output 1
                                                          AT91C_PIO_PB22 EQU( 1 << 22 );
                                                          -Pin Controlled by PB22
                                                          AT91C_PB22_PWM3 EQU( AT91C_PIO_PB22 );
                                                          -PWM Channel 3
                                                          AT91C_PB22_PCK2 EQU( AT91C_PIO_PB22 );
                                                          -PMC Programmable Clock Output 2
                                                          AT91C_PIO_PB23 EQU( 1 << 23 );
                                                          -Pin Controlled by PB23
                                                          AT91C_PB23_TIOA0 EQU( AT91C_PIO_PB23 );
                                                          -Timer Counter 0 Multipurpose Timer I / O Pin A
                                                          AT91C_PB23_DCD1 EQU( AT91C_PIO_PB23 );
                                                          -USART 1 దత్తాంశం Carrier Detect
                                                          AT91C_PIO_PB24 EQU( 1 << 24 );
                                                          -Pin Controlled by PB24
                                                          AT91C_PB24_TIOB0 EQU( AT91C_PIO_PB24 );
                                                          -Timer Counter 0 Multipurpose Timer I / O Pin B
                                                          AT91C_PB24_DSR1 EQU( AT91C_PIO_PB24 );
                                                          -USART 1 దత్తాంశం సమితి_2 ready
                                                          AT91C_PIO_PB25 EQU( 1 << 25 );
                                                          -Pin Controlled by PB25
                                                          AT91C_PB25_TIOA1 EQU( AT91C_PIO_PB25 );
                                                          -Timer Counter 1 Multipurpose Timer I / O Pin A
                                                          AT91C_PB25_DTR1 EQU( AT91C_PIO_PB25 );
                                                          -USART 1 దత్తాంశం Terminal ready
                                                          AT91C_PIO_PB26 EQU( 1 << 26 );
                                                          -Pin Controlled by PB26
                                                          AT91C_PB26_TIOB1 EQU( AT91C_PIO_PB26 );
                                                          -Timer Counter 1 Multipurpose Timer I / O Pin B
                                                          AT91C_PB26_RI1 EQU( AT91C_PIO_PB26 );
                                                          -USART 1 Ring Indicator
                                                          AT91C_PIO_PB27 EQU( 1 << 27 );
                                                          -Pin Controlled by PB27
                                                          AT91C_PB27_TIOA2 EQU( AT91C_PIO_PB27 );
                                                          -Timer Counter 2 Multipurpose Timer I / O Pin A
                                                          AT91C_PB27_PWM0 EQU( AT91C_PIO_PB27 );
                                                          -PWM Channel 0
                                                          AT91C_PIO_PB28 EQU( 1 << 28 );
                                                          -Pin Controlled by PB28
                                                          AT91C_PB28_TIOB2 EQU( AT91C_PIO_PB28 );
                                                          -Timer Counter 2 Multipurpose Timer I / O Pin B
                                                          AT91C_PB28_PWM1 EQU( AT91C_PIO_PB28 );
                                                          -PWM Channel 1
                                                          AT91C_PIO_PB29 EQU( 1 << 29 );
                                                          -Pin Controlled by PB29
                                                          AT91C_PB29_PCK1 EQU( AT91C_PIO_PB29 );
                                                          -PMC Programmable Clock Output 1
                                                          AT91C_PB29_PWM2 EQU( AT91C_PIO_PB29 );
                                                          -PWM Channel 2
                                                          AT91C_PIO_PB3 EQU( 1 << 3 );
                                                          -Pin Controlled by PB3
                                                          AT91C_PB3_ETX1 EQU( AT91C_PIO_PB3 );
                                                          -Ethernet MAC Transmit దత్తాంశం 1
                                                          AT91C_PIO_PB30 EQU( 1 << 30 );
                                                          -Pin Controlled by PB30
                                                          AT91C_PB30_PCK2 EQU( AT91C_PIO_PB30 );
                                                          -PMC Programmable Clock Output 2
                                                          AT91C_PB30_PWM3 EQU( AT91C_PIO_PB30 );
                                                          -PWM Channel 3
                                                          AT91C_PIO_PB4 EQU( 1 << 4 );
                                                          -Pin Controlled by PB4
                                                          AT91C_PB4_ECRS_ECRSDV EQU( AT91C_PIO_PB4 );
                                                          -Ethernet MAC Carrier Sense / Carrier Sense and దత్తాంశం Valid
                                                          AT91C_PIO_PB5 EQU( 1 << 5 );
                                                          -Pin Controlled by PB5
                                                          AT91C_PB5_ERX0 EQU( AT91C_PIO_PB5 );
                                                          -Ethernet MAC Receive దత్తాంశం 0
                                                          AT91C_PIO_PB6 EQU( 1 << 6 );
                                                          -Pin Controlled by PB6
                                                          AT91C_PB6_ERX1 EQU( AT91C_PIO_PB6 );
                                                          -Ethernet MAC Receive దత్తాంశం 1
                                                          AT91C_PIO_PB7 EQU( 1 << 7 );
                                                          -Pin Controlled by PB7
                                                          AT91C_PB7_ERXER EQU( AT91C_PIO_PB7 );
                                                          -Ethernet MAC Receive Error
                                                          AT91C_PIO_PB8 EQU( 1 << 8 );
                                                          -Pin Controlled by PB8
                                                          AT91C_PB8_EMDC EQU( AT91C_PIO_PB8 );
                                                          -Ethernet MAC Management దత్తాంశం Clock
                                                          AT91C_PIO_PB9 EQU( 1 << 9 );
                                                          -Pin Controlled by PB9
                                                          AT91C_PB9_EMDIO EQU( AT91C_PIO_PB9 );
                                                          -Ethernet MAC Management దత్తాంశం ఆదానం / Output

/* - ***************************************************************************** */
/* -               PERIPHERAL ID DEFINITIONS FOR AT91SAM7X256 */
/* - ***************************************************************************** */
                                                          AT91C_ID_FIQ EQU( 0 );
                                                          -Advanced అంతరాయం_2 Controller( FIQ )
                                                          AT91C_ID_SYS EQU( 1 );
                                                          -System Peripheral
                                                          AT91C_ID_PIOA EQU( 2 );
                                                          -Parallel IO Controller A
                                                          AT91C_ID_PIOB EQU( 3 );
                                                          -Parallel IO Controller B
                                                          AT91C_ID_SPI0 EQU( 4 );
                                                          -Serial Peripheral Interface 0
                                                          AT91C_ID_SPI1 EQU( 5 );
                                                          -Serial Peripheral Interface 1
                                                          AT91C_ID_US0 EQU( 6 );
                                                          -USART 0
                                                          AT91C_ID_US1 EQU( 7 );
                                                          -USART 1
                                                          AT91C_ID_SSC EQU( 8 );
                                                          -Serial Synchronous Controller
                                                          AT91C_ID_TWI EQU( 9 );
                                                          -Two - Wire Interface
                                                          AT91C_ID_PWMC EQU( 10 );
                                                          -PWM Controller
                                                          AT91C_ID_UDP EQU( 11 );
                                                          -USB Device పోర్టు_2
                                                          AT91C_ID_TC0 EQU( 12 );
                                                          -Timer Counter 0
                                                          AT91C_ID_TC1 EQU( 13 );
                                                          -Timer Counter 1
                                                          AT91C_ID_TC2 EQU( 14 );
                                                          -Timer Counter 2
                                                          AT91C_ID_CAN EQU( 15 );
                                                          -Control Area జాలం Controller
                                                          AT91C_ID_EMAC EQU( 16 );
                                                          -Ethernet MAC
                                                          AT91C_ID_ADC EQU( 17 );
                                                          -Analog - గమ్యం - Digital Converter
                                                          AT91C_ID_AES EQU( 18 );
                                                          -Advanced Encryption Standard 128 - బిట్టు_2
                                                          AT91C_ID_TDES EQU( 19 );
                                                          -Triple దత్తాంశం Encryption Standard
                                                          AT91C_ID_20_Reserved EQU( 20 );
                                                          -Reserved
                                                          AT91C_ID_21_Reserved EQU( 21 );
                                                          -Reserved
                                                          AT91C_ID_22_Reserved EQU( 22 );
                                                          -Reserved
                                                          AT91C_ID_23_Reserved EQU( 23 );
                                                          -Reserved
                                                          AT91C_ID_24_Reserved EQU( 24 );
                                                          -Reserved
                                                          AT91C_ID_25_Reserved EQU( 25 );
                                                          -Reserved
                                                          AT91C_ID_26_Reserved EQU( 26 );
                                                          -Reserved
                                                          AT91C_ID_27_Reserved EQU( 27 );
                                                          -Reserved
                                                          AT91C_ID_28_Reserved EQU( 28 );
                                                          -Reserved
                                                          AT91C_ID_29_Reserved EQU( 29 );
                                                          -Reserved
                                                          AT91C_ID_IRQ0 EQU( 30 );
                                                          -Advanced అంతరాయం_2 Controller( IRQ0 )
                                                          AT91C_ID_IRQ1 EQU( 31 );
                                                          -Advanced అంతరాయం_2 Controller( IRQ1 )

/* - ***************************************************************************** */
/* -               BASE ADDRESS DEFINITIONS FOR AT91SAM7X256 */
/* - ***************************************************************************** */
                                                          AT91_C_పునాది_SYS EQU( 0xFFFFF000 );
                                                          -( SYS ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_AIC EQU( 0xFFFFF000 );
                                                          -( AIC ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_PDC_DBGU EQU( 0xFFFFF300 );
                                                          -( PDC_DBGU ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_DBGU EQU( 0xFFFFF200 );
                                                          -( DBGU ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_PIOA EQU( 0xFFFFF400 );
                                                          -( PIOA ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_PIOB EQU( 0xFFFFF600 );
                                                          -( PIOB ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_CKGR EQU( 0xFFFFFC20 );
                                                          -( CKGR ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_PMC EQU( 0xFFFFFC00 );
                                                          -( PMC ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_RSTC EQU( 0xFFFFFD00 );
                                                          -( RSTC ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_RTTC EQU( 0xFFFFFD20 );
                                                          -( RTTC ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_PITC EQU( 0xFFFFFD30 );
                                                          -( PITC ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_WDTC EQU( 0xFFFFFD40 );
                                                          -( WDTC ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_VREG EQU( 0xFFFFFD60 );
                                                          -( VREG ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_MC EQU( 0xFFFFFF00 );
                                                          -( MC ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_PDC_SPI1 EQU( 0xFFFE4100 );
                                                          -( PDC_SPI1 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_SPI1 EQU( 0xFFFE4000 );
                                                          -( SPI1 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_PDC_SPI0 EQU( 0xFFFE0100 );
                                                          -( PDC_SPI0 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_SPI0 EQU( 0xFFFE0000 );
                                                          -( SPI0 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_PDC_US1 EQU( 0xFFFC4100 );
                                                          -( PDC_US1 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_US1 EQU( 0xFFFC4000 );
                                                          -( US1 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_PDC_US0 EQU( 0xFFFC0100 );
                                                          -( PDC_US0 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_US0 EQU( 0xFFFC0000 );
                                                          -( US0 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_PDC_SSC EQU( 0xFFFD4100 );
                                                          -( PDC_SSC ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_SSC EQU( 0xFFFD4000 );
                                                          -( SSC ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_TWI EQU( 0xFFFB8000 );
                                                          -( TWI ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_PWMC_CH3 EQU( 0xFFFCC260 );
                                                          -( PWMC_CH3 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_PWMC_CH2 EQU( 0xFFFCC240 );
                                                          -( PWMC_CH2 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_PWMC_CH1 EQU( 0xFFFCC220 );
                                                          -( PWMC_CH1 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_PWMC_CH0 EQU( 0xFFFCC200 );
                                                          -( PWMC_CH0 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_PWMC EQU( 0xFFFCC000 );
                                                          -( PWMC ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_UDP EQU( 0xFFFB0000 );
                                                          -( UDP ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_TC0 EQU( 0xFFFA0000 );
                                                          -( TC0 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_TC1 EQU( 0xFFFA0040 );
                                                          -( TC1 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_TC2 EQU( 0xFFFA0080 );
                                                          -( TC2 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_TCB EQU( 0xFFFA0000 );
                                                          -( TCB ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_CAN_MB0 EQU( 0xFFFD0200 );
                                                          -( CAN_MB0 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_CAN_MB1 EQU( 0xFFFD0220 );
                                                          -( CAN_MB1 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_CAN_MB2 EQU( 0xFFFD0240 );
                                                          -( CAN_MB2 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_CAN_MB3 EQU( 0xFFFD0260 );
                                                          -( CAN_MB3 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_CAN_MB4 EQU( 0xFFFD0280 );
                                                          -( CAN_MB4 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_CAN_MB5 EQU( 0xFFFD02A0 );
                                                          -( CAN_MB5 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_CAN_MB6 EQU( 0xFFFD02C0 );
                                                          -( CAN_MB6 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_CAN_MB7 EQU( 0xFFFD02E0 );
                                                          -( CAN_MB7 ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_CAN EQU( 0xFFFD0000 );
                                                          -( CAN ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_EMAC EQU( 0xFFFDC000 );
                                                          -( EMAC ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_PDC_ADC EQU( 0xFFFD8100 );
                                                          -( PDC_ADC ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_ADC EQU( 0xFFFD8000 );
                                                          -( ADC ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_PDC_AES EQU( 0xFFFA4100 );
                                                          -( PDC_AES ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_AES EQU( 0xFFFA4000 );
                                                          -( AES ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_PDC_TDES EQU( 0xFFFA8100 );
                                                          -( PDC_TDES ) పునాది_2 చిరునామా
                                                          AT91_C_పునాది_TDES EQU( 0xFFFA8000 );
                                                          -( TDES ) పునాది_2 చిరునామా

/* - ***************************************************************************** */
/* -               MEMORY MAPPING DEFINITIONS FOR AT91SAM7X256 */
/* - ***************************************************************************** */
                                                          AT91C_ISRAM EQU( 0x00200000 );
                                                          -అంతర్గత SRAM పునాది చిరునామా_2
                                                          AT91_C_ISRAM_కొలత EQU( 0x00010000 );
                                                          -అంతర్గత SRAM కొలత లోపల byte( 64 Kbyte )
                                                          AT91C_IFLASH EQU( 0x00100000 );
                                                          -అంతర్గత ROM పునాది చిరునామా_2
                                                          AT91_C_IFLASH_కొలత EQU( 0x00040000 );
                                                          -అంతర్గత ROM కొలత లోపల byte( 256 Kbyte )



#అయితే_ముగింపు /* AT91SAM7X256_H */
