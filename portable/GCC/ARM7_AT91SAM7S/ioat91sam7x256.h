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

#جيڪڏهن_وصف_نه_ٿيل AT91SAM7X256_H
#وصف_ڪريو AT91SAM7X256_H

تعريفنوع متطاير بنانشان صحيح AT91_REG; /* Hardware register definition */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR System Peripherals */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_SYS
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
    AT91_REG PIOA_في;          /* PIO Enable Register */
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
    AT91_REG PIOB_في;          /* PIO Enable Register */
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
تعريفنوع بنية _AT91S_AIC
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
#وصف_ڪريو AT91_C_AIC_اڳواٽ                            ( ( بنانشان صحيح ) 0x7 << 0 ) /* (AIC) Priority Level */
#وصف_ڪريو     AT91_C_AIC_اڳواٽ_سڀ_کان_هيٺ                 ( ( بنانشان صحيح ) 0x0 )      /* (AIC) Lowest priority level */
#وصف_ڪريو     AT91_C_AIC_اڳواٽ_HIGHEST                ( ( بنانشان صحيح ) 0x7 )      /* (AIC) Highest priority level */
#وصف_ڪريو AT91C_AIC_SRCTYPE                          ( ( بنانشان صحيح ) 0x3 << 5 ) /* (AIC) Interrupt Source Type */
#وصف_ڪريو     AT91_C_AIC_SRCTYPE_INT_مٿاهون_LEVEL       ( ( بنانشان صحيح ) 0x0 << 5 ) /* (AIC) Internal Sources Code Label High-level Sensitive */
#وصف_ڪريو     AT91_C_AIC_SRCTYPE_EXT_هيٺيون_LEVEL        ( ( بنانشان صحيح ) 0x0 << 5 ) /* (AIC) External Sources Code Label Low-level Sensitive */
#وصف_ڪريو     AT91_C_AIC_SRCTYPE_INT_مثبت_ڪنارو    ( ( بنانشان صحيح ) 0x1 << 5 ) /* (AIC) Internal Sources Code Label Positive Edge triggered */
#وصف_ڪريو     AT91_C_AIC_SRCTYPE_EXT_NEGATIVE_ڪنارو    ( ( بنانشان صحيح ) 0x1 << 5 ) /* (AIC) External Sources Code Label Negative Edge triggered */
#وصف_ڪريو     AT91_C_AIC_SRCTYPE_مٿاهون_LEVEL           ( ( بنانشان صحيح ) 0x2 << 5 ) /* (AIC) Internal Or External Sources Code Label High-level Sensitive */
#وصف_ڪريو     AT91_C_AIC_SRCTYPE_مثبت_ڪنارو        ( ( بنانشان صحيح ) 0x3 << 5 ) /* (AIC) Internal Or External Sources Code Label Positive Edge triggered */
/* -------- AIC_CISR : (AIC Offset: 0x114) AIC Core Interrupt Status Register -------- */
#وصف_ڪريو AT91C_AIC_NFIQ                             ( ( بنانشان صحيح ) 0x1 << 0 ) /* (AIC) NFIQ Status */
#وصف_ڪريو AT91C_AIC_NIRQ                             ( ( بنانشان صحيح ) 0x1 << 1 ) /* (AIC) NIRQ Status */
/* -------- AIC_DCR : (AIC Offset: 0x138) AIC Debug Control Register (Protect) -------- */
#وصف_ڪريو AT91C_AIC_DCR_PROT                         ( ( بنانشان صحيح ) 0x1 << 0 ) /* (AIC) Protection Mode */
#وصف_ڪريو AT91C_AIC_DCR_GMSK                         ( ( بنانشان صحيح ) 0x1 << 1 ) /* (AIC) General Mask */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Peripheral DMA Controller */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_PDC
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
#وصف_ڪريو AT91C_PDC_RXTEN     ( ( بنانشان صحيح ) 0x1 << 0 ) /* (PDC) Receiver Transfer Enable */
#وصف_ڪريو AT91C_PDC_RXTDIS    ( ( بنانشان صحيح ) 0x1 << 1 ) /* (PDC) Receiver Transfer Disable */
#وصف_ڪريو AT91C_PDC_TXTEN     ( ( بنانشان صحيح ) 0x1 << 8 ) /* (PDC) Transmitter Transfer Enable */
#وصف_ڪريو AT91C_PDC_TXTDIS    ( ( بنانشان صحيح ) 0x1 << 9 ) /* (PDC) Transmitter Transfer Disable */
/* -------- PDC_PTSR : (PDC Offset: 0x24) PDC Transfer Status Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Debug Unit */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_DBGU
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
#وصف_ڪريو AT91C_US_RSTRX                 ( ( بنانشان صحيح ) 0x1 << 2 )  /* (DBGU) Reset Receiver */
#وصف_ڪريو AT91C_US_RSTTX                 ( ( بنانشان صحيح ) 0x1 << 3 )  /* (DBGU) Reset Transmitter */
#وصف_ڪريو AT91C_US_RXEN                  ( ( بنانشان صحيح ) 0x1 << 4 )  /* (DBGU) Receiver Enable */
#وصف_ڪريو AT91C_US_RXDIS                 ( ( بنانشان صحيح ) 0x1 << 5 )  /* (DBGU) Receiver Disable */
#وصف_ڪريو AT91C_US_TXEN                  ( ( بنانشان صحيح ) 0x1 << 6 )  /* (DBGU) Transmitter Enable */
#وصف_ڪريو AT91C_US_TXDIS                 ( ( بنانشان صحيح ) 0x1 << 7 )  /* (DBGU) Transmitter Disable */
#وصف_ڪريو AT91C_US_RSTSTA                ( ( بنانشان صحيح ) 0x1 << 8 )  /* (DBGU) Reset Status Bits */
/* -------- DBGU_MR : (DBGU Offset: 0x4) Debug Unit Mode Register -------- */
#وصف_ڪريو AT91C_US_PAR                   ( ( بنانشان صحيح ) 0x7 << 9 )  /* (DBGU) Parity type */
#وصف_ڪريو     AT91C_US_PAR_EVEN          ( ( بنانشان صحيح ) 0x0 << 9 )  /* (DBGU) Even Parity */
#وصف_ڪريو     AT91C_US_PAR_ODD           ( ( بنانشان صحيح ) 0x1 << 9 )  /* (DBGU) Odd Parity */
#وصف_ڪريو     AT91C_US_PAR_SPACE         ( ( بنانشان صحيح ) 0x2 << 9 )  /* (DBGU) Parity forced to 0 (Space) */
#وصف_ڪريو     AT91C_US_PAR_MARK          ( ( بنانشان صحيح ) 0x3 << 9 )  /* (DBGU) Parity forced to 1 (Mark) */
#وصف_ڪريو     AT91C_US_PAR_NONE          ( ( بنانشان صحيح ) 0x4 << 9 )  /* (DBGU) No Parity */
#وصف_ڪريو     AT91C_US_PAR_MULTI_DROP    ( ( بنانشان صحيح ) 0x6 << 9 )  /* (DBGU) Multi-drop mode */
#وصف_ڪريو AT91C_US_CHMODE                ( ( بنانشان صحيح ) 0x3 << 14 ) /* (DBGU) Channel Mode */
#وصف_ڪريو     AT91_C_US_CHMODE_عام     ( ( بنانشان صحيح ) 0x0 << 14 ) /* (DBGU) Normal Mode: The USART channel operates as an RX/TX USART. */
#وصف_ڪريو     AT91C_US_CHMODE_AUTO       ( ( بنانشان صحيح ) 0x1 << 14 ) /* (DBGU) Automatic Echo: Receiver Data Input is connected to the TXD pin. */
#وصف_ڪريو     AT91C_US_CHMODE_LOCAL      ( ( بنانشان صحيح ) 0x2 << 14 ) /* (DBGU) Local Loopback: Transmitter Output Signal is connected to Receiver Input Signal. */
#وصف_ڪريو     AT91C_US_CHMODE_REMOTE     ( ( بنانشان صحيح ) 0x3 << 14 ) /* (DBGU) Remote Loopback: RXD pin is internally connected to TXD pin. */
/* -------- DBGU_IER : (DBGU Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
#وصف_ڪريو AT91C_US_RXRDY                 ( ( بنانشان صحيح ) 0x1 << 0 )  /* (DBGU) RXRDY Interrupt */
#وصف_ڪريو AT91C_US_TXRDY                 ( ( بنانشان صحيح ) 0x1 << 1 )  /* (DBGU) TXRDY Interrupt */
#وصف_ڪريو AT91C_US_ENDRX                 ( ( بنانشان صحيح ) 0x1 << 3 )  /* (DBGU) End of Receive Transfer Interrupt */
#وصف_ڪريو AT91C_US_ENDTX                 ( ( بنانشان صحيح ) 0x1 << 4 )  /* (DBGU) End of Transmit Interrupt */
#وصف_ڪريو AT91C_US_OVRE                  ( ( بنانشان صحيح ) 0x1 << 5 )  /* (DBGU) Overrun Interrupt */
#وصف_ڪريو AT91_C_US_چوکٺو                 ( ( بنانشان صحيح ) 0x1 << 6 )  /* (DBGU) Framing Error Interrupt */
#وصف_ڪريو AT91C_US_PARE                  ( ( بنانشان صحيح ) 0x1 << 7 )  /* (DBGU) Parity Error Interrupt */
#وصف_ڪريو AT91C_US_TXEMPTY               ( ( بنانشان صحيح ) 0x1 << 9 )  /* (DBGU) TXEMPTY Interrupt */
#وصف_ڪريو AT91C_US_TXBUFE                ( ( بنانشان صحيح ) 0x1 << 11 ) /* (DBGU) TXBUFE Interrupt */
#وصف_ڪريو AT91C_US_RXBUFF                ( ( بنانشان صحيح ) 0x1 << 12 ) /* (DBGU) RXBUFF Interrupt */
#وصف_ڪريو AT91C_US_COMM_TX               ( ( بنانشان صحيح ) 0x1 << 30 ) /* (DBGU) COMM_TX Interrupt */
#وصف_ڪريو AT91C_US_COMM_RX               ( ( بنانشان صحيح ) 0x1 << 31 ) /* (DBGU) COMM_RX Interrupt */
/* -------- DBGU_IDR : (DBGU Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* -------- DBGU_IMR : (DBGU Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* -------- DBGU_CSR : (DBGU Offset: 0x14) Debug Unit Channel Status Register -------- */
/* -------- DBGU_FNTR : (DBGU Offset: 0x48) Debug Unit FORCE_NTRST Register -------- */
#وصف_ڪريو AT91C_US_FORCE_NTRST    ( ( بنانشان صحيح ) 0x1 << 0 ) /* (DBGU) Force NTRST in JTAG */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Parallel Input Output Controller */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_PIO
{
    AT91_REG PIO_في;        /* PIO Enable Register */
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
تعريفنوع بنية _AT91S_CKGR
{
    AT91_REG CKGR_MOR;       /* Main Oscillator Register */
    AT91_REG CKGR_MCFR;      /* Main Clock  Frequency Register */
    AT91_REG Reserved0[ 1 ]; /* */
    AT91_REG CKGR_PLLR;      /* PLL Register */
} AT91S_CKGR, * AT91PS_CKGR;

/* -------- CKGR_MOR : (CKGR Offset: 0x0) Main Oscillator Register -------- */
#وصف_ڪريو AT91C_CKGR_MOSCEN            ( ( بنانشان صحيح ) 0x1 << 0 )    /* (CKGR) Main Oscillator Enable */
#وصف_ڪريو AT91C_CKGR_OSCBYPASS         ( ( بنانشان صحيح ) 0x1 << 1 )    /* (CKGR) Main Oscillator Bypass */
#وصف_ڪريو AT91C_CKGR_OSCOUNT           ( ( بنانشان صحيح ) 0xFF << 8 )   /* (CKGR) Main Oscillator Start-up Time */
/* -------- CKGR_MCFR : (CKGR Offset: 0x4) Main Clock Frequency Register -------- */
#وصف_ڪريو AT91C_CKGR_MAINF             ( ( بنانشان صحيح ) 0xFFFF << 0 ) /* (CKGR) Main Clock Frequency */
#وصف_ڪريو AT91C_CKGR_MAINRDY           ( ( بنانشان صحيح ) 0x1 << 16 )   /* (CKGR) Main Clock Ready */
/* -------- CKGR_PLLR : (CKGR Offset: 0xc) PLL B Register -------- */
#وصف_ڪريو AT91C_CKGR_DIV               ( ( بنانشان صحيح ) 0xFF << 0 )   /* (CKGR) Divider Selected */
#وصف_ڪريو     AT91C_CKGR_DIV_0         ( ( بنانشان صحيح ) 0x0 )         /* (CKGR) Divider output is 0 */
#وصف_ڪريو     AT91C_CKGR_DIV_BYPASS    ( ( بنانشان صحيح ) 0x1 )         /* (CKGR) Divider is bypassed */
#وصف_ڪريو AT91C_CKGR_PLLCOUNT          ( ( بنانشان صحيح ) 0x3F << 8 )   /* (CKGR) PLL Counter */
#وصف_ڪريو AT91_C_CKGR_ٻاهريون               ( ( بنانشان صحيح ) 0x3 << 14 )   /* (CKGR) PLL Output Frequency Range */
#وصف_ڪريو     AT91_C_CKGR_ٻاهريون_0         ( ( بنانشان صحيح ) 0x0 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#وصف_ڪريو     AT91_C_CKGR_ٻاهريون_1         ( ( بنانشان صحيح ) 0x1 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#وصف_ڪريو     AT91_C_CKGR_ٻاهريون_2         ( ( بنانشان صحيح ) 0x2 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#وصف_ڪريو     AT91_C_CKGR_ٻاهريون_3         ( ( بنانشان صحيح ) 0x3 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#وصف_ڪريو AT91C_CKGR_MUL               ( ( بنانشان صحيح ) 0x7FF << 16 ) /* (CKGR) PLL Multiplier */
#وصف_ڪريو AT91C_CKGR_USBDIV            ( ( بنانشان صحيح ) 0x3 << 28 )   /* (CKGR) Divider for USB Clocks */
#وصف_ڪريو     AT91C_CKGR_USBDIV_0      ( ( بنانشان صحيح ) 0x0 << 28 )   /* (CKGR) Divider output is PLL clock output */
#وصف_ڪريو     AT91C_CKGR_USBDIV_1      ( ( بنانشان صحيح ) 0x1 << 28 )   /* (CKGR) Divider output is PLL clock output divided by 2 */
#وصف_ڪريو     AT91C_CKGR_USBDIV_2      ( ( بنانشان صحيح ) 0x2 << 28 )   /* (CKGR) Divider output is PLL clock output divided by 4 */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Power Management Controller */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_PMC
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
#وصف_ڪريو AT91C_PMC_PCK     ( ( بنانشان صحيح ) 0x1 << 0 )  /* (PMC) Processor Clock */
#وصف_ڪريو AT91C_PMC_UDP     ( ( بنانشان صحيح ) 0x1 << 7 )  /* (PMC) USB Device Port Clock */
#وصف_ڪريو AT91C_PMC_PCK0    ( ( بنانشان صحيح ) 0x1 << 8 )  /* (PMC) Programmable Clock Output */
#وصف_ڪريو AT91C_PMC_PCK1    ( ( بنانشان صحيح ) 0x1 << 9 )  /* (PMC) Programmable Clock Output */
#وصف_ڪريو AT91C_PMC_PCK2    ( ( بنانشان صحيح ) 0x1 << 10 ) /* (PMC) Programmable Clock Output */
#وصف_ڪريو AT91C_PMC_PCK3    ( ( بنانشان صحيح ) 0x1 << 11 ) /* (PMC) Programmable Clock Output */
/* -------- PMC_SCDR : (PMC Offset: 0x4) System Clock Disable Register -------- */
/* -------- PMC_SCSR : (PMC Offset: 0x8) System Clock Status Register -------- */
/* -------- CKGR_MOR : (PMC Offset: 0x20) Main Oscillator Register -------- */
/* -------- CKGR_MCFR : (PMC Offset: 0x24) Main Clock Frequency Register -------- */
/* -------- CKGR_PLLR : (PMC Offset: 0x2c) PLL B Register -------- */
/* -------- PMC_MCKR : (PMC Offset: 0x30) Master Clock Register -------- */
#وصف_ڪريو AT91C_PMC_CSS                 ( ( بنانشان صحيح ) 0x3 << 0 ) /* (PMC) Programmable Clock Selection */
#وصف_ڪريو     AT91C_PMC_CSS_SLOW_CLK    ( ( بنانشان صحيح ) 0x0 )      /* (PMC) Slow Clock is selected */
#وصف_ڪريو     AT91C_PMC_CSS_MAIN_CLK    ( ( بنانشان صحيح ) 0x1 )      /* (PMC) Main Clock is selected */
#وصف_ڪريو     AT91C_PMC_CSS_PLL_CLK     ( ( بنانشان صحيح ) 0x3 )      /* (PMC) Clock from PLL is selected */
#وصف_ڪريو AT91C_PMC_PRES                ( ( بنانشان صحيح ) 0x7 << 2 ) /* (PMC) Programmable Clock Prescaler */
#وصف_ڪريو     AT91C_PMC_PRES_CLK        ( ( بنانشان صحيح ) 0x0 << 2 ) /* (PMC) Selected clock */
#وصف_ڪريو     AT91C_PMC_PRES_CLK_2      ( ( بنانشان صحيح ) 0x1 << 2 ) /* (PMC) Selected clock divided by 2 */
#وصف_ڪريو     AT91C_PMC_PRES_CLK_4      ( ( بنانشان صحيح ) 0x2 << 2 ) /* (PMC) Selected clock divided by 4 */
#وصف_ڪريو     AT91C_PMC_PRES_CLK_8      ( ( بنانشان صحيح ) 0x3 << 2 ) /* (PMC) Selected clock divided by 8 */
#وصف_ڪريو     AT91C_PMC_PRES_CLK_16     ( ( بنانشان صحيح ) 0x4 << 2 ) /* (PMC) Selected clock divided by 16 */
#وصف_ڪريو     AT91C_PMC_PRES_CLK_32     ( ( بنانشان صحيح ) 0x5 << 2 ) /* (PMC) Selected clock divided by 32 */
#وصف_ڪريو     AT91C_PMC_PRES_CLK_64     ( ( بنانشان صحيح ) 0x6 << 2 ) /* (PMC) Selected clock divided by 64 */
/* -------- PMC_PCKR : (PMC Offset: 0x40) Programmable Clock Register -------- */
/* -------- PMC_IER : (PMC Offset: 0x60) PMC Interrupt Enable Register -------- */
#وصف_ڪريو AT91C_PMC_MOSCS               ( ( بنانشان صحيح ) 0x1 << 0 )  /* (PMC) MOSC Status/Enable/Disable/Mask */
#وصف_ڪريو AT91_C_PMC_تالو                ( ( بنانشان صحيح ) 0x1 << 2 )  /* (PMC) PLL Status/Enable/Disable/Mask */
#وصف_ڪريو AT91C_PMC_MCKRDY              ( ( بنانشان صحيح ) 0x1 << 3 )  /* (PMC) MCK_RDY Status/Enable/Disable/Mask */
#وصف_ڪريو AT91C_PMC_PCK0RDY             ( ( بنانشان صحيح ) 0x1 << 8 )  /* (PMC) PCK0_RDY Status/Enable/Disable/Mask */
#وصف_ڪريو AT91C_PMC_PCK1RDY             ( ( بنانشان صحيح ) 0x1 << 9 )  /* (PMC) PCK1_RDY Status/Enable/Disable/Mask */
#وصف_ڪريو AT91C_PMC_PCK2RDY             ( ( بنانشان صحيح ) 0x1 << 10 ) /* (PMC) PCK2_RDY Status/Enable/Disable/Mask */
#وصف_ڪريو AT91C_PMC_PCK3RDY             ( ( بنانشان صحيح ) 0x1 << 11 ) /* (PMC) PCK3_RDY Status/Enable/Disable/Mask */
/* -------- PMC_IDR : (PMC Offset: 0x64) PMC Interrupt Disable Register -------- */
/* -------- PMC_SR : (PMC Offset: 0x68) PMC Status Register -------- */
/* -------- PMC_IMR : (PMC Offset: 0x6c) PMC Interrupt Mask Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Reset Controller Interface */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_RSTC
{
    AT91_REG RSTC_RCR; /* Reset Control Register */
    AT91_REG RSTC_RSR; /* Reset Status Register */
    AT91_REG RSTC_RMR; /* Reset Mode Register */
} AT91S_RSTC, * AT91PS_RSTC;

/* -------- RSTC_RCR : (RSTC Offset: 0x0) Reset Control Register -------- */
#وصف_ڪريو AT91C_RSTC_PROCRST                ( ( بنانشان صحيح ) 0x1 << 0 )   /* (RSTC) Processor Reset */
#وصف_ڪريو AT91C_RSTC_PERRST                 ( ( بنانشان صحيح ) 0x1 << 2 )   /* (RSTC) Peripheral Reset */
#وصف_ڪريو AT91C_RSTC_EXTRST                 ( ( بنانشان صحيح ) 0x1 << 3 )   /* (RSTC) External Reset */
#وصف_ڪريو AT91_C_RSTC_ڪنجي                    ( ( بنانشان صحيح ) 0xFF << 24 ) /* (RSTC) Password */
/* -------- RSTC_RSR : (RSTC Offset: 0x4) Reset Status Register -------- */
#وصف_ڪريو AT91C_RSTC_URSTS                  ( ( بنانشان صحيح ) 0x1 << 0 )   /* (RSTC) User Reset Status */
#وصف_ڪريو AT91C_RSTC_BODSTS                 ( ( بنانشان صحيح ) 0x1 << 1 )   /* (RSTC) Brownout Detection Status */
#وصف_ڪريو AT91C_RSTC_RSTTYP                 ( ( بنانشان صحيح ) 0x7 << 8 )   /* (RSTC) Reset Type */
#وصف_ڪريو     AT91C_RSTC_RSTTYP_POWERUP     ( ( بنانشان صحيح ) 0x0 << 8 )   /* (RSTC) Power-up Reset. VDDCORE rising. */
#وصف_ڪريو     AT91C_RSTC_RSTTYP_WAKEUP      ( ( بنانشان صحيح ) 0x1 << 8 )   /* (RSTC) WakeUp Reset. VDDCORE rising. */
#وصف_ڪريو     AT91C_RSTC_RSTTYP_WATCHDOG    ( ( بنانشان صحيح ) 0x2 << 8 )   /* (RSTC) Watchdog Reset. Watchdog overflow occurred. */
#وصف_ڪريو     AT91C_RSTC_RSTTYP_SOFTWARE    ( ( بنانشان صحيح ) 0x3 << 8 )   /* (RSTC) Software Reset. Processor reset required by the software. */
#وصف_ڪريو     AT91C_RSTC_RSTTYP_USER        ( ( بنانشان صحيح ) 0x4 << 8 )   /* (RSTC) User Reset. NRST pin detected low. */
#وصف_ڪريو     AT91C_RSTC_RSTTYP_BROWNOUT    ( ( بنانشان صحيح ) 0x5 << 8 )   /* (RSTC) Brownout Reset occurred. */
#وصف_ڪريو AT91C_RSTC_NRSTL                  ( ( بنانشان صحيح ) 0x1 << 16 )  /* (RSTC) NRST pin level */
#وصف_ڪريو AT91C_RSTC_SRCMP                  ( ( بنانشان صحيح ) 0x1 << 17 )  /* (RSTC) Software Reset Command in Progress. */
/* -------- RSTC_RMR : (RSTC Offset: 0x8) Reset Mode Register -------- */
#وصف_ڪريو AT91C_RSTC_URSTEN                 ( ( بنانشان صحيح ) 0x1 << 0 )   /* (RSTC) User Reset Enable */
#وصف_ڪريو AT91C_RSTC_URSTIEN                ( ( بنانشان صحيح ) 0x1 << 4 )   /* (RSTC) User Reset Interrupt Enable */
#وصف_ڪريو AT91C_RSTC_ERSTL                  ( ( بنانشان صحيح ) 0xF << 8 )   /* (RSTC) User Reset Enable */
#وصف_ڪريو AT91C_RSTC_BODIEN                 ( ( بنانشان صحيح ) 0x1 << 16 )  /* (RSTC) Brownout Detection Interrupt Enable */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Real Time Timer Controller Interface */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_RTTC
{
    AT91_REG RTTC_RTMR; /* Real-time Mode Register */
    AT91_REG RTTC_RTAR; /* Real-time Alarm Register */
    AT91_REG RTTC_RTVR; /* Real-time Value Register */
    AT91_REG RTTC_RTSR; /* Real-time Status Register */
} AT91S_RTTC, * AT91PS_RTTC;

/* -------- RTTC_RTMR : (RTTC Offset: 0x0) Real-time Mode Register -------- */
#وصف_ڪريو AT91C_RTTC_RTPRES       ( ( بنانشان صحيح ) 0xFFFF << 0 ) /* (RTTC) Real-time Timer Prescaler Value */
#وصف_ڪريو AT91C_RTTC_ALMIEN       ( ( بنانشان صحيح ) 0x1 << 16 )   /* (RTTC) Alarm Interrupt Enable */
#وصف_ڪريو AT91C_RTTC_RTTINCIEN    ( ( بنانشان صحيح ) 0x1 << 17 )   /* (RTTC) Real Time Timer Increment Interrupt Enable */
#وصف_ڪريو AT91C_RTTC_RTTRST       ( ( بنانشان صحيح ) 0x1 << 18 )   /* (RTTC) Real Time Timer Restart */
/* -------- RTTC_RTAR : (RTTC Offset: 0x4) Real-time Alarm Register -------- */
#وصف_ڪريو AT91C_RTTC_ALMV         ( ( بنانشان صحيح ) 0x0 << 0 )    /* (RTTC) Alarm Value */
/* -------- RTTC_RTVR : (RTTC Offset: 0x8) Current Real-time Value Register -------- */
#وصف_ڪريو AT91C_RTTC_CRTV         ( ( بنانشان صحيح ) 0x0 << 0 )    /* (RTTC) Current Real-time Value */
/* -------- RTTC_RTSR : (RTTC Offset: 0xc) Real-time Status Register -------- */
#وصف_ڪريو AT91C_RTTC_ALMS         ( ( بنانشان صحيح ) 0x1 << 0 )    /* (RTTC) Real-time Alarm Status */
#وصف_ڪريو AT91C_RTTC_RTTINC       ( ( بنانشان صحيح ) 0x1 << 1 )    /* (RTTC) Real-time Timer Increment */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Periodic Interval Timer Controller Interface */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_PITC
{
    AT91_REG PITC_PIMR; /* Period Interval Mode Register */
    AT91_REG PITC_PISR; /* Period Interval Status Register */
    AT91_REG PITC_PIVR; /* Period Interval Value Register */
    AT91_REG PITC_PIIR; /* Period Interval Image Register */
} AT91S_PITC, * AT91PS_PITC;

/* -------- PITC_PIMR : (PITC Offset: 0x0) Periodic Interval Mode Register -------- */
#وصف_ڪريو AT91C_PITC_PIV       ( ( بنانشان صحيح ) 0xFFFFF << 0 ) /* (PITC) Periodic Interval Value */
#وصف_ڪريو AT91C_PITC_PITEN     ( ( بنانشان صحيح ) 0x1 << 24 )    /* (PITC) Periodic Interval Timer Enabled */
#وصف_ڪريو AT91C_PITC_PITIEN    ( ( بنانشان صحيح ) 0x1 << 25 )    /* (PITC) Periodic Interval Timer Interrupt Enable */
/* -------- PITC_PISR : (PITC Offset: 0x4) Periodic Interval Status Register -------- */
#وصف_ڪريو AT91C_PITC_PITS      ( ( بنانشان صحيح ) 0x1 << 0 )     /* (PITC) Periodic Interval Timer Status */
/* -------- PITC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register -------- */
#وصف_ڪريو AT91C_PITC_CPIV      ( ( بنانشان صحيح ) 0xFFFFF << 0 ) /* (PITC) Current Periodic Interval Value */
#وصف_ڪريو AT91C_PITC_PICNT     ( ( بنانشان صحيح ) 0xFFF << 20 )  /* (PITC) Periodic Interval Counter */
/* -------- PITC_PIIR : (PITC Offset: 0xc) Periodic Interval Image Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Watchdog Timer Controller Interface */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_WDTC
{
    AT91_REG WDTC_WDCR; /* Watchdog Control Register */
    AT91_REG WDTC_WDMR; /* Watchdog Mode Register */
    AT91_REG WDTC_WDSR; /* Watchdog Status Register */
} AT91S_WDTC, * AT91PS_WDTC;

/* -------- WDTC_WDCR : (WDTC Offset: 0x0) Periodic Interval Image Register -------- */
#وصف_ڪريو AT91C_WDTC_WDRSTT       ( ( بنانشان صحيح ) 0x1 << 0 )    /* (WDTC) Watchdog Restart */
#وصف_ڪريو AT91_C_WDTC_ڪنجي          ( ( بنانشان صحيح ) 0xFF << 24 )  /* (WDTC) Watchdog KEY Password */
/* -------- WDTC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register -------- */
#وصف_ڪريو AT91C_WDTC_WDV          ( ( بنانشان صحيح ) 0xFFF << 0 )  /* (WDTC) Watchdog Timer Restart */
#وصف_ڪريو AT91C_WDTC_WDFIEN       ( ( بنانشان صحيح ) 0x1 << 12 )   /* (WDTC) Watchdog Fault Interrupt Enable */
#وصف_ڪريو AT91C_WDTC_WDRSTEN      ( ( بنانشان صحيح ) 0x1 << 13 )   /* (WDTC) Watchdog Reset Enable */
#وصف_ڪريو AT91C_WDTC_WDRPROC      ( ( بنانشان صحيح ) 0x1 << 14 )   /* (WDTC) Watchdog Timer Restart */
#وصف_ڪريو AT91C_WDTC_WDDIS        ( ( بنانشان صحيح ) 0x1 << 15 )   /* (WDTC) Watchdog Disable */
#وصف_ڪريو AT91C_WDTC_WDD          ( ( بنانشان صحيح ) 0xFFF << 16 ) /* (WDTC) Watchdog Delta Value */
#وصف_ڪريو AT91C_WDTC_WDDBGHLT     ( ( بنانشان صحيح ) 0x1 << 28 )   /* (WDTC) Watchdog Debug Halt */
#وصف_ڪريو AT91C_WDTC_WDIDLEHLT    ( ( بنانشان صحيح ) 0x1 << 29 )   /* (WDTC) Watchdog Idle Halt */
/* -------- WDTC_WDSR : (WDTC Offset: 0x8) Watchdog Status Register -------- */
#وصف_ڪريو AT91C_WDTC_WDUNF        ( ( بنانشان صحيح ) 0x1 << 0 )    /* (WDTC) Watchdog Underflow */
#وصف_ڪريو AT91C_WDTC_WDERR        ( ( بنانشان صحيح ) 0x1 << 1 )    /* (WDTC) Watchdog Error */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Voltage Regulator Mode Controller Interface */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_VREG
{
    AT91_REG VREG_MR; /* Voltage Regulator Mode Register */
} AT91S_VREG, * AT91PS_VREG;

/* -------- VREG_MR : (VREG Offset: 0x0) Voltage Regulator Mode Register -------- */
#وصف_ڪريو AT91C_VREG_PSTDBY    ( ( بنانشان صحيح ) 0x1 << 0 ) /* (VREG) Voltage Regulator Power Standby Mode */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Memory Controller Interface */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_MC
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
#وصف_ڪريو AT91C_MC_RCB                       ( ( بنانشان صحيح ) 0x1 << 0 )   /* (MC) Remap Command Bit */
/* -------- MC_ASR : (MC Offset: 0x4) MC Abort Status Register -------- */
#وصف_ڪريو AT91C_MC_UNDADD                    ( ( بنانشان صحيح ) 0x1 << 0 )   /* (MC) Undefined Address Abort Status */
#وصف_ڪريو AT91C_MC_MISADD                    ( ( بنانشان صحيح ) 0x1 << 1 )   /* (MC) Misaligned Address Abort Status */
#وصف_ڪريو AT91C_MC_ABTSZ                     ( ( بنانشان صحيح ) 0x3 << 8 )   /* (MC) Abort Size Status */
#وصف_ڪريو     AT91C_MC_ABTSZ_BYTE            ( ( بنانشان صحيح ) 0x0 << 8 )   /* (MC) Byte */
#وصف_ڪريو     AT91C_MC_ABTSZ_HWORD           ( ( بنانشان صحيح ) 0x1 << 8 )   /* (MC) Half-word */
#وصف_ڪريو     AT91_C_MC_ABTSZ_لفظ            ( ( بنانشان صحيح ) 0x2 << 8 )   /* (MC) Word */
#وصف_ڪريو AT91C_MC_ABTTYP                    ( ( بنانشان صحيح ) 0x3 << 10 )  /* (MC) Abort Type Status */
#وصف_ڪريو     AT91C_MC_ABTTYP_DATAR          ( ( بنانشان صحيح ) 0x0 << 10 )  /* (MC) Data Read */
#وصف_ڪريو     AT91C_MC_ABTTYP_DATAW          ( ( بنانشان صحيح ) 0x1 << 10 )  /* (MC) Data Write */
#وصف_ڪريو     AT91C_MC_ABTTYP_FETCH          ( ( بنانشان صحيح ) 0x2 << 10 )  /* (MC) Code Fetch */
#وصف_ڪريو AT91C_MC_MST0                      ( ( بنانشان صحيح ) 0x1 << 16 )  /* (MC) Master 0 Abort Source */
#وصف_ڪريو AT91C_MC_MST1                      ( ( بنانشان صحيح ) 0x1 << 17 )  /* (MC) Master 1 Abort Source */
#وصف_ڪريو AT91C_MC_SVMST0                    ( ( بنانشان صحيح ) 0x1 << 24 )  /* (MC) Saved Master 0 Abort Source */
#وصف_ڪريو AT91C_MC_SVMST1                    ( ( بنانشان صحيح ) 0x1 << 25 )  /* (MC) Saved Master 1 Abort Source */
/* -------- MC_FMR : (MC Offset: 0x60) MC Flash Mode Register -------- */
#وصف_ڪريو AT91C_MC_FRDY                      ( ( بنانشان صحيح ) 0x1 << 0 )   /* (MC) Flash Ready */
#وصف_ڪريو AT91C_MC_LOCKE                     ( ( بنانشان صحيح ) 0x1 << 2 )   /* (MC) Lock Error */
#وصف_ڪريو AT91C_MC_PROGE                     ( ( بنانشان صحيح ) 0x1 << 3 )   /* (MC) Programming Error */
#وصف_ڪريو AT91C_MC_NEBP                      ( ( بنانشان صحيح ) 0x1 << 7 )   /* (MC) No Erase Before Programming */
#وصف_ڪريو AT91C_MC_FWS                       ( ( بنانشان صحيح ) 0x3 << 8 )   /* (MC) Flash Wait State */
#وصف_ڪريو     AT91C_MC_FWS_0FWS              ( ( بنانشان صحيح ) 0x0 << 8 )   /* (MC) 1 cycle for Read, 2 for Write operations */
#وصف_ڪريو     AT91C_MC_FWS_1FWS              ( ( بنانشان صحيح ) 0x1 << 8 )   /* (MC) 2 cycles for Read, 3 for Write operations */
#وصف_ڪريو     AT91C_MC_FWS_2FWS              ( ( بنانشان صحيح ) 0x2 << 8 )   /* (MC) 3 cycles for Read, 4 for Write operations */
#وصف_ڪريو     AT91C_MC_FWS_3FWS              ( ( بنانشان صحيح ) 0x3 << 8 )   /* (MC) 4 cycles for Read, 4 for Write operations */
#وصف_ڪريو AT91C_MC_FMCN                      ( ( بنانشان صحيح ) 0xFF << 16 ) /* (MC) Flash Microsecond Cycle Number */
/* -------- MC_FCR : (MC Offset: 0x64) MC Flash Command Register -------- */
#وصف_ڪريو AT91C_MC_FCMD                      ( ( بنانشان صحيح ) 0xF << 0 )   /* (MC) Flash Command */
#وصف_ڪريو     AT91_C_MC_FCMD_شروعات_PROG       ( ( بنانشان صحيح ) 0x1 )        /* (MC) Starts the programming of th epage specified by PAGEN. */
#وصف_ڪريو     AT91_C_MC_FCMD_تالو             ( ( بنانشان صحيح ) 0x2 )        /* (MC) Starts a lock sequence of the sector defined by the bits 4 to 7 of the field PAGEN. */
#وصف_ڪريو     AT91_C_MC_FCMD_PROG_AND_تالو    ( ( بنانشان صحيح ) 0x3 )        /* (MC) The lock sequence automatically happens after the programming sequence is completed. */
#وصف_ڪريو     AT91C_MC_FCMD_UNLOCK           ( ( بنانشان صحيح ) 0x4 )        /* (MC) Starts an unlock sequence of the sector defined by the bits 4 to 7 of the field PAGEN. */
#وصف_ڪريو     AT91C_MC_FCMD_ERASE_ALL        ( ( بنانشان صحيح ) 0x8 )        /* (MC) Starts the erase of the entire flash.If at least a page is locked, the command is cancelled. */
#وصف_ڪريو     AT91_C_MC_FCMD_سيٽ_GP_NVM       ( ( بنانشان صحيح ) 0xB )        /* (MC) Set General Purpose NVM bits. */
#وصف_ڪريو     AT91C_MC_FCMD_CLR_GP_NVM       ( ( بنانشان صحيح ) 0xD )        /* (MC) Clear General Purpose NVM bits. */
#وصف_ڪريو     AT91_C_MC_FCMD_سيٽ_SECURITY     ( ( بنانشان صحيح ) 0xF )        /* (MC) Set Security Bit. */
#وصف_ڪريو AT91C_MC_PAGEN                     ( ( بنانشان صحيح ) 0x3FF << 8 ) /* (MC) Page Number */
#وصف_ڪريو AT91_C_MC_ڪنجي                       ( ( بنانشان صحيح ) 0xFF << 24 ) /* (MC) Writing Protect Key */
/* -------- MC_FSR : (MC Offset: 0x68) MC Flash Command Register -------- */
#وصف_ڪريو AT91C_MC_SECURITY                  ( ( بنانشان صحيح ) 0x1 << 4 )   /* (MC) Security Bit Status */
#وصف_ڪريو AT91C_MC_GPNVM0                    ( ( بنانشان صحيح ) 0x1 << 8 )   /* (MC) Sector 0 Lock Status */
#وصف_ڪريو AT91C_MC_GPNVM1                    ( ( بنانشان صحيح ) 0x1 << 9 )   /* (MC) Sector 1 Lock Status */
#وصف_ڪريو AT91C_MC_GPNVM2                    ( ( بنانشان صحيح ) 0x1 << 10 )  /* (MC) Sector 2 Lock Status */
#وصف_ڪريو AT91C_MC_GPNVM3                    ( ( بنانشان صحيح ) 0x1 << 11 )  /* (MC) Sector 3 Lock Status */
#وصف_ڪريو AT91C_MC_GPNVM4                    ( ( بنانشان صحيح ) 0x1 << 12 )  /* (MC) Sector 4 Lock Status */
#وصف_ڪريو AT91C_MC_GPNVM5                    ( ( بنانشان صحيح ) 0x1 << 13 )  /* (MC) Sector 5 Lock Status */
#وصف_ڪريو AT91C_MC_GPNVM6                    ( ( بنانشان صحيح ) 0x1 << 14 )  /* (MC) Sector 6 Lock Status */
#وصف_ڪريو AT91C_MC_GPNVM7                    ( ( بنانشان صحيح ) 0x1 << 15 )  /* (MC) Sector 7 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS0                    ( ( بنانشان صحيح ) 0x1 << 16 )  /* (MC) Sector 0 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS1                    ( ( بنانشان صحيح ) 0x1 << 17 )  /* (MC) Sector 1 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS2                    ( ( بنانشان صحيح ) 0x1 << 18 )  /* (MC) Sector 2 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS3                    ( ( بنانشان صحيح ) 0x1 << 19 )  /* (MC) Sector 3 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS4                    ( ( بنانشان صحيح ) 0x1 << 20 )  /* (MC) Sector 4 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS5                    ( ( بنانشان صحيح ) 0x1 << 21 )  /* (MC) Sector 5 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS6                    ( ( بنانشان صحيح ) 0x1 << 22 )  /* (MC) Sector 6 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS7                    ( ( بنانشان صحيح ) 0x1 << 23 )  /* (MC) Sector 7 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS8                    ( ( بنانشان صحيح ) 0x1 << 24 )  /* (MC) Sector 8 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS9                    ( ( بنانشان صحيح ) 0x1 << 25 )  /* (MC) Sector 9 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS10                   ( ( بنانشان صحيح ) 0x1 << 26 )  /* (MC) Sector 10 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS11                   ( ( بنانشان صحيح ) 0x1 << 27 )  /* (MC) Sector 11 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS12                   ( ( بنانشان صحيح ) 0x1 << 28 )  /* (MC) Sector 12 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS13                   ( ( بنانشان صحيح ) 0x1 << 29 )  /* (MC) Sector 13 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS14                   ( ( بنانشان صحيح ) 0x1 << 30 )  /* (MC) Sector 14 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS15                   ( ( بنانشان صحيح ) 0x1 << 31 )  /* (MC) Sector 15 Lock Status */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Serial Parallel Interface */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_SPI
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
#وصف_ڪريو AT91C_SPI_SPIEN              ( ( بنانشان صحيح ) 0x1 << 0 )    /* (SPI) SPI Enable */
#وصف_ڪريو AT91C_SPI_SPIDIS             ( ( بنانشان صحيح ) 0x1 << 1 )    /* (SPI) SPI Disable */
#وصف_ڪريو AT91C_SPI_SWRST              ( ( بنانشان صحيح ) 0x1 << 7 )    /* (SPI) SPI Software reset */
#وصف_ڪريو AT91C_SPI_LASTXFER           ( ( بنانشان صحيح ) 0x1 << 24 )   /* (SPI) SPI Last Transfer */
/* -------- SPI_MR : (SPI Offset: 0x4) SPI Mode Register -------- */
#وصف_ڪريو AT91C_SPI_MSTR               ( ( بنانشان صحيح ) 0x1 << 0 )    /* (SPI) Master/Slave Mode */
#وصف_ڪريو AT91C_SPI_PS                 ( ( بنانشان صحيح ) 0x1 << 1 )    /* (SPI) Peripheral Select */
#وصف_ڪريو     AT91C_SPI_PS_FIXED       ( ( بنانشان صحيح ) 0x0 << 1 )    /* (SPI) Fixed Peripheral Select */
#وصف_ڪريو     AT91C_SPI_PS_VARIABLE    ( ( بنانشان صحيح ) 0x1 << 1 )    /* (SPI) Variable Peripheral Select */
#وصف_ڪريو AT91C_SPI_PCSDEC             ( ( بنانشان صحيح ) 0x1 << 2 )    /* (SPI) Chip Select Decode */
#وصف_ڪريو AT91C_SPI_FDIV               ( ( بنانشان صحيح ) 0x1 << 3 )    /* (SPI) Clock Selection */
#وصف_ڪريو AT91C_SPI_MODFDIS            ( ( بنانشان صحيح ) 0x1 << 4 )    /* (SPI) Mode Fault Detection */
#وصف_ڪريو AT91C_SPI_LLB                ( ( بنانشان صحيح ) 0x1 << 7 )    /* (SPI) Clock Selection */
#وصف_ڪريو AT91C_SPI_PCS                ( ( بنانشان صحيح ) 0xF << 16 )   /* (SPI) Peripheral Chip Select */
#وصف_ڪريو AT91C_SPI_DLYBCS             ( ( بنانشان صحيح ) 0xFF << 24 )  /* (SPI) Delay Between Chip Selects */
/* -------- SPI_RDR : (SPI Offset: 0x8) Receive Data Register -------- */
#وصف_ڪريو AT91C_SPI_RD                 ( ( بنانشان صحيح ) 0xFFFF << 0 ) /* (SPI) Receive Data */
#وصف_ڪريو AT91C_SPI_RPCS               ( ( بنانشان صحيح ) 0xF << 16 )   /* (SPI) Peripheral Chip Select Status */
/* -------- SPI_TDR : (SPI Offset: 0xc) Transmit Data Register -------- */
#وصف_ڪريو AT91C_SPI_TD                 ( ( بنانشان صحيح ) 0xFFFF << 0 ) /* (SPI) Transmit Data */
#وصف_ڪريو AT91C_SPI_TPCS               ( ( بنانشان صحيح ) 0xF << 16 )   /* (SPI) Peripheral Chip Select Status */
/* -------- SPI_SR : (SPI Offset: 0x10) Status Register -------- */
#وصف_ڪريو AT91C_SPI_RDRF               ( ( بنانشان صحيح ) 0x1 << 0 )    /* (SPI) Receive Data Register Full */
#وصف_ڪريو AT91C_SPI_TDRE               ( ( بنانشان صحيح ) 0x1 << 1 )    /* (SPI) Transmit Data Register Empty */
#وصف_ڪريو AT91C_SPI_MODF               ( ( بنانشان صحيح ) 0x1 << 2 )    /* (SPI) Mode Fault Error */
#وصف_ڪريو AT91C_SPI_OVRES              ( ( بنانشان صحيح ) 0x1 << 3 )    /* (SPI) Overrun Error Status */
#وصف_ڪريو AT91C_SPI_ENDRX              ( ( بنانشان صحيح ) 0x1 << 4 )    /* (SPI) End of Receiver Transfer */
#وصف_ڪريو AT91C_SPI_ENDTX              ( ( بنانشان صحيح ) 0x1 << 5 )    /* (SPI) End of Receiver Transfer */
#وصف_ڪريو AT91C_SPI_RXBUFF             ( ( بنانشان صحيح ) 0x1 << 6 )    /* (SPI) RXBUFF Interrupt */
#وصف_ڪريو AT91C_SPI_TXBUFE             ( ( بنانشان صحيح ) 0x1 << 7 )    /* (SPI) TXBUFE Interrupt */
#وصف_ڪريو AT91C_SPI_NSSR               ( ( بنانشان صحيح ) 0x1 << 8 )    /* (SPI) NSSR Interrupt */
#وصف_ڪريو AT91C_SPI_TXEMPTY            ( ( بنانشان صحيح ) 0x1 << 9 )    /* (SPI) TXEMPTY Interrupt */
#وصف_ڪريو AT91C_SPI_SPIENS             ( ( بنانشان صحيح ) 0x1 << 16 )   /* (SPI) Enable Status */
/* -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- */
/* -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- */
/* -------- SPI_IMR : (SPI Offset: 0x1c) Interrupt Mask Register -------- */
/* -------- SPI_CSR : (SPI Offset: 0x30) Chip Select Register -------- */
#وصف_ڪريو AT91C_SPI_CPOL           ( ( بنانشان صحيح ) 0x1 << 0 )   /* (SPI) Clock Polarity */
#وصف_ڪريو AT91C_SPI_NCPHA          ( ( بنانشان صحيح ) 0x1 << 1 )   /* (SPI) Clock Phase */
#وصف_ڪريو AT91C_SPI_CSAAT          ( ( بنانشان صحيح ) 0x1 << 3 )   /* (SPI) Chip Select Active After Transfer */
#وصف_ڪريو AT91_C_SPI_بٽ           ( ( بنانشان صحيح ) 0xF << 4 )   /* (SPI) Bits Per Transfer */
#وصف_ڪريو     AT91_C_SPI_بٽ_8     ( ( بنانشان صحيح ) 0x0 << 4 )   /* (SPI) 8 Bits Per transfer */
#وصف_ڪريو     AT91_C_SPI_بٽ_9     ( ( بنانشان صحيح ) 0x1 << 4 )   /* (SPI) 9 Bits Per transfer */
#وصف_ڪريو     AT91_C_SPI_بٽ_10    ( ( بنانشان صحيح ) 0x2 << 4 )   /* (SPI) 10 Bits Per transfer */
#وصف_ڪريو     AT91_C_SPI_بٽ_11    ( ( بنانشان صحيح ) 0x3 << 4 )   /* (SPI) 11 Bits Per transfer */
#وصف_ڪريو     AT91_C_SPI_بٽ_12    ( ( بنانشان صحيح ) 0x4 << 4 )   /* (SPI) 12 Bits Per transfer */
#وصف_ڪريو     AT91_C_SPI_بٽ_13    ( ( بنانشان صحيح ) 0x5 << 4 )   /* (SPI) 13 Bits Per transfer */
#وصف_ڪريو     AT91_C_SPI_بٽ_14    ( ( بنانشان صحيح ) 0x6 << 4 )   /* (SPI) 14 Bits Per transfer */
#وصف_ڪريو     AT91_C_SPI_بٽ_15    ( ( بنانشان صحيح ) 0x7 << 4 )   /* (SPI) 15 Bits Per transfer */
#وصف_ڪريو     AT91_C_SPI_بٽ_16    ( ( بنانشان صحيح ) 0x8 << 4 )   /* (SPI) 16 Bits Per transfer */
#وصف_ڪريو AT91C_SPI_SCBR           ( ( بنانشان صحيح ) 0xFF << 8 )  /* (SPI) Serial Clock Baud Rate */
#وصف_ڪريو AT91C_SPI_DLYBS          ( ( بنانشان صحيح ) 0xFF << 16 ) /* (SPI) Delay Before SPCK */
#وصف_ڪريو AT91C_SPI_DLYBCT         ( ( بنانشان صحيح ) 0xFF << 24 ) /* (SPI) Delay Between Consecutive Transfers */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Usart */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_USART
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
#وصف_ڪريو AT91C_US_STTBRK                  ( ( بنانشان صحيح ) 0x1 << 9 )  /* (USART) Start Break */
#وصف_ڪريو AT91C_US_STPBRK                  ( ( بنانشان صحيح ) 0x1 << 10 ) /* (USART) Stop Break */
#وصف_ڪريو AT91C_US_STTTO                   ( ( بنانشان صحيح ) 0x1 << 11 ) /* (USART) Start Time-out */
#وصف_ڪريو AT91C_US_SENDA                   ( ( بنانشان صحيح ) 0x1 << 12 ) /* (USART) Send Address */
#وصف_ڪريو AT91C_US_RSTIT                   ( ( بنانشان صحيح ) 0x1 << 13 ) /* (USART) Reset Iterations */
#وصف_ڪريو AT91C_US_RSTNACK                 ( ( بنانشان صحيح ) 0x1 << 14 ) /* (USART) Reset Non Acknowledge */
#وصف_ڪريو AT91C_US_RETTO                   ( ( بنانشان صحيح ) 0x1 << 15 ) /* (USART) Rearm Time-out */
#وصف_ڪريو AT91C_US_DTREN                   ( ( بنانشان صحيح ) 0x1 << 16 ) /* (USART) Data Terminal ready Enable */
#وصف_ڪريو AT91C_US_DTRDIS                  ( ( بنانشان صحيح ) 0x1 << 17 ) /* (USART) Data Terminal ready Disable */
#وصف_ڪريو AT91C_US_RTSEN                   ( ( بنانشان صحيح ) 0x1 << 18 ) /* (USART) Request to Send enable */
#وصف_ڪريو AT91C_US_RTSDIS                  ( ( بنانشان صحيح ) 0x1 << 19 ) /* (USART) Request to Send Disable */
/* -------- US_MR : (USART Offset: 0x4) Debug Unit Mode Register -------- */
#وصف_ڪريو AT91C_US_USMODE                  ( ( بنانشان صحيح ) 0xF << 0 )  /* (USART) Usart mode */
#وصف_ڪريو     AT91_C_US_USMODE_عام       ( ( بنانشان صحيح ) 0x0 )       /* (USART) Normal */
#وصف_ڪريو     AT91C_US_USMODE_RS485        ( ( بنانشان صحيح ) 0x1 )       /* (USART) RS485 */
#وصف_ڪريو     AT91C_US_USMODE_HWHSH        ( ( بنانشان صحيح ) 0x2 )       /* (USART) Hardware Handshaking */
#وصف_ڪريو     AT91C_US_USMODE_MODEM        ( ( بنانشان صحيح ) 0x3 )       /* (USART) Modem */
#وصف_ڪريو     AT91C_US_USMODE_ISO7816_0    ( ( بنانشان صحيح ) 0x4 )       /* (USART) ISO7816 protocol: T = 0 */
#وصف_ڪريو     AT91C_US_USMODE_ISO7816_1    ( ( بنانشان صحيح ) 0x6 )       /* (USART) ISO7816 protocol: T = 1 */
#وصف_ڪريو     AT91C_US_USMODE_IRDA         ( ( بنانشان صحيح ) 0x8 )       /* (USART) IrDA */
#وصف_ڪريو     AT91C_US_USMODE_SWHSH        ( ( بنانشان صحيح ) 0xC )       /* (USART) Software Handshaking */
#وصف_ڪريو AT91C_US_CLKS                    ( ( بنانشان صحيح ) 0x3 << 4 )  /* (USART) Clock Selection (Baud Rate generator Input Clock */
#وصف_ڪريو     AT91C_US_CLKS_CLOCK          ( ( بنانشان صحيح ) 0x0 << 4 )  /* (USART) Clock */
#وصف_ڪريو     AT91C_US_CLKS_FDIV1          ( ( بنانشان صحيح ) 0x1 << 4 )  /* (USART) fdiv1 */
#وصف_ڪريو     AT91C_US_CLKS_SLOW           ( ( بنانشان صحيح ) 0x2 << 4 )  /* (USART) slow_clock (ARM) */
#وصف_ڪريو     AT91C_US_CLKS_EXT            ( ( بنانشان صحيح ) 0x3 << 4 )  /* (USART) External (SCK) */
#وصف_ڪريو AT91C_US_CHRL                    ( ( بنانشان صحيح ) 0x3 << 6 )  /* (USART) Clock Selection (Baud Rate generator Input Clock */
#وصف_ڪريو     AT91_C_US_CHRL_5_بٽ         ( ( بنانشان صحيح ) 0x0 << 6 )  /* (USART) Character Length: 5 bits */
#وصف_ڪريو     AT91_C_US_CHRL_6_بٽ         ( ( بنانشان صحيح ) 0x1 << 6 )  /* (USART) Character Length: 6 bits */
#وصف_ڪريو     AT91_C_US_CHRL_7_بٽ         ( ( بنانشان صحيح ) 0x2 << 6 )  /* (USART) Character Length: 7 bits */
#وصف_ڪريو     AT91_C_US_CHRL_8_بٽ         ( ( بنانشان صحيح ) 0x3 << 6 )  /* (USART) Character Length: 8 bits */
#وصف_ڪريو AT91C_US_SYNC                    ( ( بنانشان صحيح ) 0x1 << 8 )  /* (USART) Synchronous Mode Select */
#وصف_ڪريو AT91C_US_NBSTOP                  ( ( بنانشان صحيح ) 0x3 << 12 ) /* (USART) Number of Stop bits */
#وصف_ڪريو     AT91_C_US_NBSTOP_1_ٻٽو_انگ        ( ( بنانشان صحيح ) 0x0 << 12 ) /* (USART) 1 stop bit */
#وصف_ڪريو     AT91_C_US_NBSTOP_15_ٻٽو_انگ       ( ( بنانشان صحيح ) 0x1 << 12 ) /* (USART) Asynchronous (SYNC=0) 2 stop bits Synchronous (SYNC=1) 2 stop bits */
#وصف_ڪريو     AT91_C_US_NBSTOP_2_ٻٽو_انگ        ( ( بنانشان صحيح ) 0x2 << 12 ) /* (USART) 2 stop bits */
#وصف_ڪريو AT91C_US_MSBF                    ( ( بنانشان صحيح ) 0x1 << 16 ) /* (USART) Bit Order */
#وصف_ڪريو AT91C_US_MODE9                   ( ( بنانشان صحيح ) 0x1 << 17 ) /* (USART) 9-bit Character length */
#وصف_ڪريو AT91C_US_CKLO                    ( ( بنانشان صحيح ) 0x1 << 18 ) /* (USART) Clock Output Select */
#وصف_ڪريو AT91C_US_OVER                    ( ( بنانشان صحيح ) 0x1 << 19 ) /* (USART) Over Sampling Mode */
#وصف_ڪريو AT91C_US_INACK                   ( ( بنانشان صحيح ) 0x1 << 20 ) /* (USART) Inhibit Non Acknowledge */
#وصف_ڪريو AT91C_US_DSNACK                  ( ( بنانشان صحيح ) 0x1 << 21 ) /* (USART) Disable Successive NACK */
#وصف_ڪريو AT91C_US_MAX_ITER                ( ( بنانشان صحيح ) 0x1 << 24 ) /* (USART) Number of Repetitions */
#وصف_ڪريو AT91C_US_FILTER                  ( ( بنانشان صحيح ) 0x1 << 28 ) /* (USART) Receive Line Filter */
/* -------- US_IER : (USART Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
#وصف_ڪريو AT91C_US_RXBRK                   ( ( بنانشان صحيح ) 0x1 << 2 )  /* (USART) Break Received/End of Break */
#وصف_ڪريو AT91C_US_TIMEOUT                 ( ( بنانشان صحيح ) 0x1 << 8 )  /* (USART) Receiver Time-out */
#وصف_ڪريو AT91C_US_ITERATION               ( ( بنانشان صحيح ) 0x1 << 10 ) /* (USART) Max number of Repetitions Reached */
#وصف_ڪريو AT91C_US_NACK                    ( ( بنانشان صحيح ) 0x1 << 13 ) /* (USART) Non Acknowledge */
#وصف_ڪريو AT91C_US_RIIC                    ( ( بنانشان صحيح ) 0x1 << 16 ) /* (USART) Ring INdicator Input Change Flag */
#وصف_ڪريو AT91C_US_DSRIC                   ( ( بنانشان صحيح ) 0x1 << 17 ) /* (USART) Data Set Ready Input Change Flag */
#وصف_ڪريو AT91C_US_DCDIC                   ( ( بنانشان صحيح ) 0x1 << 18 ) /* (USART) Data Carrier Flag */
#وصف_ڪريو AT91C_US_CTSIC                   ( ( بنانشان صحيح ) 0x1 << 19 ) /* (USART) Clear To Send Input Change Flag */
/* -------- US_IDR : (USART Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* -------- US_IMR : (USART Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* -------- US_CSR : (USART Offset: 0x14) Debug Unit Channel Status Register -------- */
#وصف_ڪريو AT91C_US_RI     ( ( بنانشان صحيح ) 0x1 << 20 )   /* (USART) Image of RI Input */
#وصف_ڪريو AT91C_US_DSR    ( ( بنانشان صحيح ) 0x1 << 21 )   /* (USART) Image of DSR Input */
#وصف_ڪريو AT91C_US_DCD    ( ( بنانشان صحيح ) 0x1 << 22 )   /* (USART) Image of DCD Input */
#وصف_ڪريو AT91C_US_CTS    ( ( بنانشان صحيح ) 0x1 << 23 )   /* (USART) Image of CTS Input */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Synchronous Serial Controller Interface */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_SSC
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
#وصف_ڪريو AT91C_SSC_RXEN                    ( ( بنانشان صحيح ) 0x1 << 0 )   /* (SSC) Receive Enable */
#وصف_ڪريو AT91C_SSC_RXDIS                   ( ( بنانشان صحيح ) 0x1 << 1 )   /* (SSC) Receive Disable */
#وصف_ڪريو AT91C_SSC_TXEN                    ( ( بنانشان صحيح ) 0x1 << 8 )   /* (SSC) Transmit Enable */
#وصف_ڪريو AT91C_SSC_TXDIS                   ( ( بنانشان صحيح ) 0x1 << 9 )   /* (SSC) Transmit Disable */
#وصف_ڪريو AT91C_SSC_SWRST                   ( ( بنانشان صحيح ) 0x1 << 15 )  /* (SSC) Software Reset */
/* -------- SSC_RCMR : (SSC Offset: 0x10) SSC Receive Clock Mode Register -------- */
#وصف_ڪريو AT91C_SSC_CKS                     ( ( بنانشان صحيح ) 0x3 << 0 )   /* (SSC) Receive/Transmit Clock Selection */
#وصف_ڪريو     AT91C_SSC_CKS_DIV             ( ( بنانشان صحيح ) 0x0 )        /* (SSC) Divided Clock */
#وصف_ڪريو     AT91C_SSC_CKS_TK              ( ( بنانشان صحيح ) 0x1 )        /* (SSC) TK Clock signal */
#وصف_ڪريو     AT91C_SSC_CKS_RK              ( ( بنانشان صحيح ) 0x2 )        /* (SSC) RK pin */
#وصف_ڪريو AT91C_SSC_CKO                     ( ( بنانشان صحيح ) 0x7 << 2 )   /* (SSC) Receive/Transmit Clock Output Mode Selection */
#وصف_ڪريو     AT91C_SSC_CKO_NONE            ( ( بنانشان صحيح ) 0x0 << 2 )   /* (SSC) Receive/Transmit Clock Output Mode: None RK pin: Input-only */
#وصف_ڪريو     AT91C_SSC_CKO_CONTINUOUS      ( ( بنانشان صحيح ) 0x1 << 2 )   /* (SSC) Continuous Receive/Transmit Clock RK pin: Output */
#وصف_ڪريو     AT91_C_SSC_CKO_معلومات_TX         ( ( بنانشان صحيح ) 0x2 << 2 )   /* (SSC) Receive/Transmit Clock only during data transfers RK pin: Output */
#وصف_ڪريو AT91C_SSC_CKI                     ( ( بنانشان صحيح ) 0x1 << 5 )   /* (SSC) Receive/Transmit Clock Inversion */
#وصف_ڪريو AT91_C_SSC_شروعات                   ( ( بنانشان صحيح ) 0xF << 8 )   /* (SSC) Receive/Transmit Start Selection */
#وصف_ڪريو     AT91_C_SSC_شروعات_CONTINUOUS    ( ( بنانشان صحيح ) 0x0 << 8 )   /* (SSC) Continuous, as soon as the receiver is enabled, and immediately after the end of transfer of the previous data. */
#وصف_ڪريو     AT91_C_SSC_شروعات_TX            ( ( بنانشان صحيح ) 0x1 << 8 )   /* (SSC) Transmit/Receive start */
#وصف_ڪريو     AT91_C_SSC_شروعات_هيٺيون_RF        ( ( بنانشان صحيح ) 0x2 << 8 )   /* (SSC) Detection of a low level on RF input */
#وصف_ڪريو     AT91_C_SSC_شروعات_مٿاهون_RF       ( ( بنانشان صحيح ) 0x3 << 8 )   /* (SSC) Detection of a high level on RF input */
#وصف_ڪريو     AT91_C_SSC_شروعات_FALL_RF       ( ( بنانشان صحيح ) 0x4 << 8 )   /* (SSC) Detection of a falling edge on RF input */
#وصف_ڪريو     AT91_C_SSC_شروعات_RISE_RF       ( ( بنانشان صحيح ) 0x5 << 8 )   /* (SSC) Detection of a rising edge on RF input */
#وصف_ڪريو     AT91_C_SSC_شروعات_LEVEL_RF      ( ( بنانشان صحيح ) 0x6 << 8 )   /* (SSC) Detection of any level change on RF input */
#وصف_ڪريو     AT91_C_SSC_شروعات_ڪنارو_RF       ( ( بنانشان صحيح ) 0x7 << 8 )   /* (SSC) Detection of any edge on RF input */
#وصف_ڪريو     AT91_C_SSC_شروعات_0             ( ( بنانشان صحيح ) 0x8 << 8 )   /* (SSC) Compare 0 */
#وصف_ڪريو AT91C_SSC_STTDLY                  ( ( بنانشان صحيح ) 0xFF << 16 ) /* (SSC) Receive/Transmit Start Delay */
#وصف_ڪريو AT91C_SSC_PERIOD                  ( ( بنانشان صحيح ) 0xFF << 24 ) /* (SSC) Receive/Transmit Period Divider Selection */
/* -------- SSC_RFMR : (SSC Offset: 0x14) SSC Receive Frame Mode Register -------- */
#وصف_ڪريو AT91C_SSC_DATLEN                  ( ( بنانشان صحيح ) 0x1F << 0 )  /* (SSC) Data Length */
#وصف_ڪريو AT91C_SSC_LOOP                    ( ( بنانشان صحيح ) 0x1 << 5 )   /* (SSC) Loop Mode */
#وصف_ڪريو AT91C_SSC_MSBF                    ( ( بنانشان صحيح ) 0x1 << 7 )   /* (SSC) Most Significant Bit First */
#وصف_ڪريو AT91C_SSC_DATNB                   ( ( بنانشان صحيح ) 0xF << 8 )   /* (SSC) Data Number per Frame */
#وصف_ڪريو AT91C_SSC_FSLEN                   ( ( بنانشان صحيح ) 0xF << 16 )  /* (SSC) Receive/Transmit Frame Sync length */
#وصف_ڪريو AT91C_SSC_FSOS                    ( ( بنانشان صحيح ) 0x7 << 20 )  /* (SSC) Receive/Transmit Frame Sync Output Selection */
#وصف_ڪريو     AT91C_SSC_FSOS_NONE           ( ( بنانشان صحيح ) 0x0 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: None RK pin Input-only */
#وصف_ڪريو     AT91C_SSC_FSOS_NEGATIVE       ( ( بنانشان صحيح ) 0x1 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Negative Pulse */
#وصف_ڪريو     AT91_C_SSC_FSOS_مثبت       ( ( بنانشان صحيح ) 0x2 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Positive Pulse */
#وصف_ڪريو     AT91_C_SSC_FSOS_هيٺيون            ( ( بنانشان صحيح ) 0x3 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Driver Low during data transfer */
#وصف_ڪريو     AT91_C_SSC_FSOS_مٿاهون           ( ( بنانشان صحيح ) 0x4 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Driver High during data transfer */
#وصف_ڪريو     AT91C_SSC_FSOS_TOGGLE         ( ( بنانشان صحيح ) 0x5 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Toggling at each start of data transfer */
#وصف_ڪريو AT91C_SSC_FSEDGE                  ( ( بنانشان صحيح ) 0x1 << 24 )  /* (SSC) Frame Sync Edge Detection */
/* -------- SSC_TCMR : (SSC Offset: 0x18) SSC Transmit Clock Mode Register -------- */
/* -------- SSC_TFMR : (SSC Offset: 0x1c) SSC Transmit Frame Mode Register -------- */
#وصف_ڪريو AT91C_SSC_DATDEF                  ( ( بنانشان صحيح ) 0x1 << 5 )  /* (SSC) Data Default Value */
#وصف_ڪريو AT91C_SSC_FSDEN                   ( ( بنانشان صحيح ) 0x1 << 23 ) /* (SSC) Frame Sync Data Enable */
/* -------- SSC_SR : (SSC Offset: 0x40) SSC Status Register -------- */
#وصف_ڪريو AT91C_SSC_TXRDY                   ( ( بنانشان صحيح ) 0x1 << 0 )  /* (SSC) Transmit Ready */
#وصف_ڪريو AT91C_SSC_TXEMPTY                 ( ( بنانشان صحيح ) 0x1 << 1 )  /* (SSC) Transmit Empty */
#وصف_ڪريو AT91C_SSC_ENDTX                   ( ( بنانشان صحيح ) 0x1 << 2 )  /* (SSC) End Of Transmission */
#وصف_ڪريو AT91C_SSC_TXBUFE                  ( ( بنانشان صحيح ) 0x1 << 3 )  /* (SSC) Transmit Buffer Empty */
#وصف_ڪريو AT91C_SSC_RXRDY                   ( ( بنانشان صحيح ) 0x1 << 4 )  /* (SSC) Receive Ready */
#وصف_ڪريو AT91C_SSC_OVRUN                   ( ( بنانشان صحيح ) 0x1 << 5 )  /* (SSC) Receive Overrun */
#وصف_ڪريو AT91C_SSC_ENDRX                   ( ( بنانشان صحيح ) 0x1 << 6 )  /* (SSC) End of Reception */
#وصف_ڪريو AT91C_SSC_RXBUFF                  ( ( بنانشان صحيح ) 0x1 << 7 )  /* (SSC) Receive Buffer Full */
#وصف_ڪريو AT91C_SSC_TXSYN                   ( ( بنانشان صحيح ) 0x1 << 10 ) /* (SSC) Transmit Sync */
#وصف_ڪريو AT91C_SSC_RXSYN                   ( ( بنانشان صحيح ) 0x1 << 11 ) /* (SSC) Receive Sync */
#وصف_ڪريو AT91C_SSC_TXENA                   ( ( بنانشان صحيح ) 0x1 << 16 ) /* (SSC) Transmit Enable */
#وصف_ڪريو AT91C_SSC_RXENA                   ( ( بنانشان صحيح ) 0x1 << 17 ) /* (SSC) Receive Enable */
/* -------- SSC_IER : (SSC Offset: 0x44) SSC Interrupt Enable Register -------- */
/* -------- SSC_IDR : (SSC Offset: 0x48) SSC Interrupt Disable Register -------- */
/* -------- SSC_IMR : (SSC Offset: 0x4c) SSC Interrupt Mask Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Two-wire Interface */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_TWI
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
#وصف_ڪريو AT91_C_TWI_شروعات                ( ( بنانشان صحيح ) 0x1 << 0 )   /* (TWI) Send a START Condition */
#وصف_ڪريو AT91C_TWI_STOP                 ( ( بنانشان صحيح ) 0x1 << 1 )   /* (TWI) Send a STOP Condition */
#وصف_ڪريو AT91C_TWI_MSEN                 ( ( بنانشان صحيح ) 0x1 << 2 )   /* (TWI) TWI Master Transfer Enabled */
#وصف_ڪريو AT91C_TWI_MSDIS                ( ( بنانشان صحيح ) 0x1 << 3 )   /* (TWI) TWI Master Transfer Disabled */
#وصف_ڪريو AT91C_TWI_SWRST                ( ( بنانشان صحيح ) 0x1 << 7 )   /* (TWI) Software Reset */
/* -------- TWI_MMR : (TWI Offset: 0x4) TWI Master Mode Register -------- */
#وصف_ڪريو AT91C_TWI_IADRSZ               ( ( بنانشان صحيح ) 0x3 << 8 )   /* (TWI) Internal Device Address Size */
#وصف_ڪريو     AT91C_TWI_IADRSZ_NO        ( ( بنانشان صحيح ) 0x0 << 8 )   /* (TWI) No internal device address */
#وصف_ڪريو     AT91C_TWI_IADRSZ_1_BYTE    ( ( بنانشان صحيح ) 0x1 << 8 )   /* (TWI) One-byte internal device address */
#وصف_ڪريو     AT91C_TWI_IADRSZ_2_BYTE    ( ( بنانشان صحيح ) 0x2 << 8 )   /* (TWI) Two-byte internal device address */
#وصف_ڪريو     AT91C_TWI_IADRSZ_3_BYTE    ( ( بنانشان صحيح ) 0x3 << 8 )   /* (TWI) Three-byte internal device address */
#وصف_ڪريو AT91C_TWI_MREAD                ( ( بنانشان صحيح ) 0x1 << 12 )  /* (TWI) Master Read Direction */
#وصف_ڪريو AT91C_TWI_DADR                 ( ( بنانشان صحيح ) 0x7F << 16 ) /* (TWI) Device Address */
/* -------- TWI_CWGR : (TWI Offset: 0x10) TWI Clock Waveform Generator Register -------- */
#وصف_ڪريو AT91C_TWI_CLDIV                ( ( بنانشان صحيح ) 0xFF << 0 )  /* (TWI) Clock Low Divider */
#وصف_ڪريو AT91C_TWI_CHDIV                ( ( بنانشان صحيح ) 0xFF << 8 )  /* (TWI) Clock High Divider */
#وصف_ڪريو AT91C_TWI_CKDIV                ( ( بنانشان صحيح ) 0x7 << 16 )  /* (TWI) Clock Divider */
/* -------- TWI_SR : (TWI Offset: 0x20) TWI Status Register -------- */
#وصف_ڪريو AT91C_TWI_TXCOMP               ( ( بنانشان صحيح ) 0x1 << 0 )   /* (TWI) Transmission Completed */
#وصف_ڪريو AT91C_TWI_RXRDY                ( ( بنانشان صحيح ) 0x1 << 1 )   /* (TWI) Receive holding register ReaDY */
#وصف_ڪريو AT91C_TWI_TXRDY                ( ( بنانشان صحيح ) 0x1 << 2 )   /* (TWI) Transmit holding register ReaDY */
#وصف_ڪريو AT91C_TWI_OVRE                 ( ( بنانشان صحيح ) 0x1 << 6 )   /* (TWI) Overrun Error */
#وصف_ڪريو AT91C_TWI_UNRE                 ( ( بنانشان صحيح ) 0x1 << 7 )   /* (TWI) Underrun Error */
#وصف_ڪريو AT91C_TWI_NACK                 ( ( بنانشان صحيح ) 0x1 << 8 )   /* (TWI) Not Acknowledged */
/* -------- TWI_IER : (TWI Offset: 0x24) TWI Interrupt Enable Register -------- */
/* -------- TWI_IDR : (TWI Offset: 0x28) TWI Interrupt Disable Register -------- */
/* -------- TWI_IMR : (TWI Offset: 0x2c) TWI Interrupt Mask Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR PWMC Channel Interface */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_PWMC_CH
{
    AT91_REG PWMC_CMR;           /* Channel Mode Register */
    AT91_REG PWMC_CDTYR;         /* Channel Duty Cycle Register */
    AT91_REG PWMC_CPRDR;         /* Channel Period Register */
    AT91_REG PWMC_CCNTR;         /* Channel Counter Register */
    AT91_REG PWMC_CUPDR;         /* Channel Update Register */
    AT91_REG PWMC_Reserved[ 3 ]; /* Reserved */
} AT91S_PWMC_CH, * AT91PS_PWMC_CH;

/* -------- PWMC_CMR : (PWMC_CH Offset: 0x0) PWMC Channel Mode Register -------- */
#وصف_ڪريو AT91C_PWMC_CPRE             ( ( بنانشان صحيح ) 0xF << 0 )  /* (PWMC_CH) Channel Pre-scaler : PWMC_CLKx */
#وصف_ڪريو     AT91C_PWMC_CPRE_MCK     ( ( بنانشان صحيح ) 0x0 )       /* (PWMC_CH) */
#وصف_ڪريو     AT91C_PWMC_CPRE_MCKA    ( ( بنانشان صحيح ) 0xB )       /* (PWMC_CH) */
#وصف_ڪريو     AT91C_PWMC_CPRE_MCKB    ( ( بنانشان صحيح ) 0xC )       /* (PWMC_CH) */
#وصف_ڪريو AT91C_PWMC_CALG             ( ( بنانشان صحيح ) 0x1 << 8 )  /* (PWMC_CH) Channel Alignment */
#وصف_ڪريو AT91C_PWMC_CPOL             ( ( بنانشان صحيح ) 0x1 << 9 )  /* (PWMC_CH) Channel Polarity */
#وصف_ڪريو AT91C_PWMC_CPD              ( ( بنانشان صحيح ) 0x1 << 10 ) /* (PWMC_CH) Channel Update Period */
/* -------- PWMC_CDTYR : (PWMC_CH Offset: 0x4) PWMC Channel Duty Cycle Register -------- */
#وصف_ڪريو AT91C_PWMC_CDTY             ( ( بنانشان صحيح ) 0x0 << 0 )  /* (PWMC_CH) Channel Duty Cycle */
/* -------- PWMC_CPRDR : (PWMC_CH Offset: 0x8) PWMC Channel Period Register -------- */
#وصف_ڪريو AT91C_PWMC_CPRD             ( ( بنانشان صحيح ) 0x0 << 0 )  /* (PWMC_CH) Channel Period */
/* -------- PWMC_CCNTR : (PWMC_CH Offset: 0xc) PWMC Channel Counter Register -------- */
#وصف_ڪريو AT91C_PWMC_CCNT             ( ( بنانشان صحيح ) 0x0 << 0 )  /* (PWMC_CH) Channel Counter */
/* -------- PWMC_CUPDR : (PWMC_CH Offset: 0x10) PWMC Channel Update Register -------- */
#وصف_ڪريو AT91C_PWMC_CUPD             ( ( بنانشان صحيح ) 0x0 << 0 )  /* (PWMC_CH) Channel Update */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Pulse Width Modulation Controller Interface */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_PWMC
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
#وصف_ڪريو AT91C_PWMC_DIVA            ( ( بنانشان صحيح ) 0xFF << 0 )  /* (PWMC) CLKA divide factor. */
#وصف_ڪريو AT91C_PWMC_PREA            ( ( بنانشان صحيح ) 0xF << 8 )   /* (PWMC) Divider Input Clock Prescaler A */
#وصف_ڪريو     AT91C_PWMC_PREA_MCK    ( ( بنانشان صحيح ) 0x0 << 8 )   /* (PWMC) */
#وصف_ڪريو AT91C_PWMC_DIVB            ( ( بنانشان صحيح ) 0xFF << 16 ) /* (PWMC) CLKB divide factor. */
#وصف_ڪريو AT91C_PWMC_PREB            ( ( بنانشان صحيح ) 0xF << 24 )  /* (PWMC) Divider Input Clock Prescaler B */
#وصف_ڪريو     AT91C_PWMC_PREB_MCK    ( ( بنانشان صحيح ) 0x0 << 24 )  /* (PWMC) */
/* -------- PWMC_ENA : (PWMC Offset: 0x4) PWMC Enable Register -------- */
#وصف_ڪريو AT91C_PWMC_CHID0           ( ( بنانشان صحيح ) 0x1 << 0 )   /* (PWMC) Channel ID 0 */
#وصف_ڪريو AT91C_PWMC_CHID1           ( ( بنانشان صحيح ) 0x1 << 1 )   /* (PWMC) Channel ID 1 */
#وصف_ڪريو AT91C_PWMC_CHID2           ( ( بنانشان صحيح ) 0x1 << 2 )   /* (PWMC) Channel ID 2 */
#وصف_ڪريو AT91C_PWMC_CHID3           ( ( بنانشان صحيح ) 0x1 << 3 )   /* (PWMC) Channel ID 3 */
/* -------- PWMC_DIS : (PWMC Offset: 0x8) PWMC Disable Register -------- */
/* -------- PWMC_SR : (PWMC Offset: 0xc) PWMC Status Register -------- */
/* -------- PWMC_IER : (PWMC Offset: 0x10) PWMC Interrupt Enable Register -------- */
/* -------- PWMC_IDR : (PWMC Offset: 0x14) PWMC Interrupt Disable Register -------- */
/* -------- PWMC_IMR : (PWMC Offset: 0x18) PWMC Interrupt Mask Register -------- */
/* -------- PWMC_ISR : (PWMC Offset: 0x1c) PWMC Interrupt Status Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR USB Device Interface */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_UDP
{
    AT91_REG UDP_انگ;        /* Frame Number Register */
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
#وصف_ڪريو AT91_C_UDP_FRM_انگ    ( ( بنانشان صحيح ) 0x7FF << 0 ) /* (UDP) Frame Number as Defined in the Packet Field Formats */
#وصف_ڪريو AT91C_UDP_FRM_ERR    ( ( بنانشان صحيح ) 0x1 << 16 )  /* (UDP) Frame Error */
#وصف_ڪريو AT91C_UDP_FRM_OK     ( ( بنانشان صحيح ) 0x1 << 17 )  /* (UDP) Frame OK */
/* -------- UDP_GLB_STATE : (UDP Offset: 0x4) USB Global State Register -------- */
#وصف_ڪريو AT91C_UDP_FADDEN     ( ( بنانشان صحيح ) 0x1 << 0 )   /* (UDP) Function Address Enable */
#وصف_ڪريو AT91C_UDP_CONFG      ( ( بنانشان صحيح ) 0x1 << 1 )   /* (UDP) Configured */
#وصف_ڪريو AT91C_UDP_ESR        ( ( بنانشان صحيح ) 0x1 << 2 )   /* (UDP) Enable Send Resume */
#وصف_ڪريو AT91C_UDP_RSMINPR    ( ( بنانشان صحيح ) 0x1 << 3 )   /* (UDP) A Resume Has Been Sent to the Host */
#وصف_ڪريو AT91C_UDP_RMWUPE     ( ( بنانشان صحيح ) 0x1 << 4 )   /* (UDP) Remote Wake Up Enable */
/* -------- UDP_FADDR : (UDP Offset: 0x8) USB Function Address Register -------- */
#وصف_ڪريو AT91C_UDP_FADD       ( ( بنانشان صحيح ) 0xFF << 0 )  /* (UDP) Function Address Value */
#وصف_ڪريو AT91C_UDP_FEN        ( ( بنانشان صحيح ) 0x1 << 8 )   /* (UDP) Function Enable */
/* -------- UDP_IER : (UDP Offset: 0x10) USB Interrupt Enable Register -------- */
#وصف_ڪريو AT91C_UDP_EPINT0     ( ( بنانشان صحيح ) 0x1 << 0 )   /* (UDP) Endpoint 0 Interrupt */
#وصف_ڪريو AT91C_UDP_EPINT1     ( ( بنانشان صحيح ) 0x1 << 1 )   /* (UDP) Endpoint 0 Interrupt */
#وصف_ڪريو AT91C_UDP_EPINT2     ( ( بنانشان صحيح ) 0x1 << 2 )   /* (UDP) Endpoint 2 Interrupt */
#وصف_ڪريو AT91C_UDP_EPINT3     ( ( بنانشان صحيح ) 0x1 << 3 )   /* (UDP) Endpoint 3 Interrupt */
#وصف_ڪريو AT91C_UDP_EPINT4     ( ( بنانشان صحيح ) 0x1 << 4 )   /* (UDP) Endpoint 4 Interrupt */
#وصف_ڪريو AT91C_UDP_EPINT5     ( ( بنانشان صحيح ) 0x1 << 5 )   /* (UDP) Endpoint 5 Interrupt */
#وصف_ڪريو AT91C_UDP_RXSUSP     ( ( بنانشان صحيح ) 0x1 << 8 )   /* (UDP) USB Suspend Interrupt */
#وصف_ڪريو AT91C_UDP_RXRSM      ( ( بنانشان صحيح ) 0x1 << 9 )   /* (UDP) USB Resume Interrupt */
#وصف_ڪريو AT91C_UDP_EXTRSM     ( ( بنانشان صحيح ) 0x1 << 10 )  /* (UDP) USB External Resume Interrupt */
#وصف_ڪريو AT91C_UDP_SOFINT     ( ( بنانشان صحيح ) 0x1 << 11 )  /* (UDP) USB Start Of frame Interrupt */
#وصف_ڪريو AT91C_UDP_WAKEUP     ( ( بنانشان صحيح ) 0x1 << 13 )  /* (UDP) USB Resume Interrupt */
/* -------- UDP_IDR : (UDP Offset: 0x14) USB Interrupt Disable Register -------- */
/* -------- UDP_IMR : (UDP Offset: 0x18) USB Interrupt Mask Register -------- */
/* -------- UDP_ISR : (UDP Offset: 0x1c) USB Interrupt Status Register -------- */
#وصف_ڪريو AT91C_UDP_ENDBUSRES              ( ( بنانشان صحيح ) 0x1 << 12 ) /* (UDP) USB End Of Bus Reset Interrupt */
/* -------- UDP_ICR : (UDP Offset: 0x20) USB Interrupt Clear Register -------- */
/* -------- UDP_RST_EP : (UDP Offset: 0x28) USB Reset Endpoint Register -------- */
#وصف_ڪريو AT91C_UDP_EP0                    ( ( بنانشان صحيح ) 0x1 << 0 )    /* (UDP) Reset Endpoint 0 */
#وصف_ڪريو AT91C_UDP_EP1                    ( ( بنانشان صحيح ) 0x1 << 1 )    /* (UDP) Reset Endpoint 1 */
#وصف_ڪريو AT91C_UDP_EP2                    ( ( بنانشان صحيح ) 0x1 << 2 )    /* (UDP) Reset Endpoint 2 */
#وصف_ڪريو AT91C_UDP_EP3                    ( ( بنانشان صحيح ) 0x1 << 3 )    /* (UDP) Reset Endpoint 3 */
#وصف_ڪريو AT91C_UDP_EP4                    ( ( بنانشان صحيح ) 0x1 << 4 )    /* (UDP) Reset Endpoint 4 */
#وصف_ڪريو AT91C_UDP_EP5                    ( ( بنانشان صحيح ) 0x1 << 5 )    /* (UDP) Reset Endpoint 5 */
/* -------- UDP_CSR : (UDP Offset: 0x30) USB Endpoint Control and Status Register -------- */
#وصف_ڪريو AT91C_UDP_TXCOMP                 ( ( بنانشان صحيح ) 0x1 << 0 )    /* (UDP) Generates an IN packet with data previously written in the DPR */
#وصف_ڪريو AT91_C_UDP_RX_معلومات_BK0            ( ( بنانشان صحيح ) 0x1 << 1 )    /* (UDP) Receive Data Bank 0 */
#وصف_ڪريو AT91C_UDP_RXSETUP                ( ( بنانشان صحيح ) 0x1 << 2 )    /* (UDP) Sends STALL to the Host (Control endpoints) */
#وصف_ڪريو AT91C_UDP_ISOERROR               ( ( بنانشان صحيح ) 0x1 << 3 )    /* (UDP) Isochronous error (Isochronous endpoints) */
#وصف_ڪريو AT91C_UDP_TXPKTRDY               ( ( بنانشان صحيح ) 0x1 << 4 )    /* (UDP) Transmit Packet Ready */
#وصف_ڪريو AT91C_UDP_FORCESTALL             ( ( بنانشان صحيح ) 0x1 << 5 )    /* (UDP) Force Stall (used by Control, Bulk and Isochronous endpoints). */
#وصف_ڪريو AT91_C_UDP_RX_معلومات_BK1            ( ( بنانشان صحيح ) 0x1 << 6 )    /* (UDP) Receive Data Bank 1 (only used by endpoints with ping-pong attributes). */
#وصف_ڪريو AT91C_UDP_DIR                    ( ( بنانشان صحيح ) 0x1 << 7 )    /* (UDP) Transfer Direction */
#وصف_ڪريو AT91C_UDP_EPTYPE                 ( ( بنانشان صحيح ) 0x7 << 8 )    /* (UDP) Endpoint type */
#وصف_ڪريو     AT91C_UDP_EPTYPE_CTRL        ( ( بنانشان صحيح ) 0x0 << 8 )    /* (UDP) Control */
#وصف_ڪريو     AT91_C_UDP_EPTYPE_ISO_ٻاهريون     ( ( بنانشان صحيح ) 0x1 << 8 )    /* (UDP) Isochronous OUT */
#وصف_ڪريو     AT91_C_UDP_EPTYPE_BULK_ٻاهريون    ( ( بنانشان صحيح ) 0x2 << 8 )    /* (UDP) Bulk OUT */
#وصف_ڪريو     AT91_C_UDP_EPTYPE_INT_ٻاهريون     ( ( بنانشان صحيح ) 0x3 << 8 )    /* (UDP) Interrupt OUT */
#وصف_ڪريو     AT91_C_UDP_EPTYPE_ISO_اندريون      ( ( بنانشان صحيح ) 0x5 << 8 )    /* (UDP) Isochronous IN */
#وصف_ڪريو     AT91_C_UDP_EPTYPE_BULK_اندريون     ( ( بنانشان صحيح ) 0x6 << 8 )    /* (UDP) Bulk IN */
#وصف_ڪريو     AT91_C_UDP_EPTYPE_INT_اندريون      ( ( بنانشان صحيح ) 0x7 << 8 )    /* (UDP) Interrupt IN */
#وصف_ڪريو AT91C_UDP_DTGLE                  ( ( بنانشان صحيح ) 0x1 << 11 )   /* (UDP) Data Toggle */
#وصف_ڪريو AT91C_UDP_EPEDS                  ( ( بنانشان صحيح ) 0x1 << 15 )   /* (UDP) Endpoint Enable Disable */
#وصف_ڪريو AT91C_UDP_RXBYTECNT              ( ( بنانشان صحيح ) 0x7FF << 16 ) /* (UDP) Number Of Bytes Available in the FIFO */
/* -------- UDP_TXVC : (UDP Offset: 0x74) Transceiver Control Register -------- */
#وصف_ڪريو AT91C_UDP_TXVDIS                 ( ( بنانشان صحيح ) 0x1 << 8 )    /* (UDP) */
#وصف_ڪريو AT91C_UDP_PUON                   ( ( بنانشان صحيح ) 0x1 << 9 )    /* (UDP) Pull-up ON */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Timer Counter Channel Interface */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_TC
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
#وصف_ڪريو AT91C_TC_CLKEN                        ( ( بنانشان صحيح ) 0x1 << 0 )  /* (TC) Counter Clock Enable Command */
#وصف_ڪريو AT91C_TC_CLKDIS                       ( ( بنانشان صحيح ) 0x1 << 1 )  /* (TC) Counter Clock Disable Command */
#وصف_ڪريو AT91C_TC_SWTRG                        ( ( بنانشان صحيح ) 0x1 << 2 )  /* (TC) Software Trigger Command */
/* -------- TC_CMR : (TC Offset: 0x4) TC Channel Mode Register: Capture Mode / Waveform Mode -------- */
#وصف_ڪريو AT91C_TC_CLKS                         ( ( بنانشان صحيح ) 0x7 << 0 )  /* (TC) Clock Selection */
#وصف_ڪريو     AT91C_TC_CLKS_TIMER_DIV1_CLOCK    ( ( بنانشان صحيح ) 0x0 )       /* (TC) Clock selected: TIMER_DIV1_CLOCK */
#وصف_ڪريو     AT91C_TC_CLKS_TIMER_DIV2_CLOCK    ( ( بنانشان صحيح ) 0x1 )       /* (TC) Clock selected: TIMER_DIV2_CLOCK */
#وصف_ڪريو     AT91C_TC_CLKS_TIMER_DIV3_CLOCK    ( ( بنانشان صحيح ) 0x2 )       /* (TC) Clock selected: TIMER_DIV3_CLOCK */
#وصف_ڪريو     AT91C_TC_CLKS_TIMER_DIV4_CLOCK    ( ( بنانشان صحيح ) 0x3 )       /* (TC) Clock selected: TIMER_DIV4_CLOCK */
#وصف_ڪريو     AT91C_TC_CLKS_TIMER_DIV5_CLOCK    ( ( بنانشان صحيح ) 0x4 )       /* (TC) Clock selected: TIMER_DIV5_CLOCK */
#وصف_ڪريو     AT91C_TC_CLKS_XC0                 ( ( بنانشان صحيح ) 0x5 )       /* (TC) Clock selected: XC0 */
#وصف_ڪريو     AT91C_TC_CLKS_XC1                 ( ( بنانشان صحيح ) 0x6 )       /* (TC) Clock selected: XC1 */
#وصف_ڪريو     AT91C_TC_CLKS_XC2                 ( ( بنانشان صحيح ) 0x7 )       /* (TC) Clock selected: XC2 */
#وصف_ڪريو AT91C_TC_CLKI                         ( ( بنانشان صحيح ) 0x1 << 3 )  /* (TC) Clock Invert */
#وصف_ڪريو AT91_C_TC_مدو                        ( ( بنانشان صحيح ) 0x3 << 4 )  /* (TC) Burst Signal Selection */
#وصف_ڪريو     AT91_C_TC_مدو_NONE               ( ( بنانشان صحيح ) 0x0 << 4 )  /* (TC) The clock is not gated by an external signal */
#وصف_ڪريو     AT91_C_TC_مدو_XC0                ( ( بنانشان صحيح ) 0x1 << 4 )  /* (TC) XC0 is ANDed with the selected clock */
#وصف_ڪريو     AT91_C_TC_مدو_XC1                ( ( بنانشان صحيح ) 0x2 << 4 )  /* (TC) XC1 is ANDed with the selected clock */
#وصف_ڪريو     AT91_C_TC_مدو_XC2                ( ( بنانشان صحيح ) 0x3 << 4 )  /* (TC) XC2 is ANDed with the selected clock */
#وصف_ڪريو AT91C_TC_CPCSTOP                      ( ( بنانشان صحيح ) 0x1 << 6 )  /* (TC) Counter Clock Stopped with RC Compare */
#وصف_ڪريو AT91C_TC_LDBSTOP                      ( ( بنانشان صحيح ) 0x1 << 6 )  /* (TC) Counter Clock Stopped with RB Loading */
#وصف_ڪريو AT91C_TC_CPCDIS                       ( ( بنانشان صحيح ) 0x1 << 7 )  /* (TC) Counter Clock Disable with RC Compare */
#وصف_ڪريو AT91C_TC_LDBDIS                       ( ( بنانشان صحيح ) 0x1 << 7 )  /* (TC) Counter Clock Disabled with RB Loading */
#وصف_ڪريو AT91C_TC_ETRGEDG                      ( ( بنانشان صحيح ) 0x3 << 8 )  /* (TC) External Trigger Edge Selection */
#وصف_ڪريو     AT91C_TC_ETRGEDG_NONE             ( ( بنانشان صحيح ) 0x0 << 8 )  /* (TC) Edge: None */
#وصف_ڪريو     AT91C_TC_ETRGEDG_RISING           ( ( بنانشان صحيح ) 0x1 << 8 )  /* (TC) Edge: rising edge */
#وصف_ڪريو     AT91C_TC_ETRGEDG_FALLING          ( ( بنانشان صحيح ) 0x2 << 8 )  /* (TC) Edge: falling edge */
#وصف_ڪريو     AT91C_TC_ETRGEDG_BOTH             ( ( بنانشان صحيح ) 0x3 << 8 )  /* (TC) Edge: each edge */
#وصف_ڪريو AT91C_TC_EEVTEDG                      ( ( بنانشان صحيح ) 0x3 << 8 )  /* (TC) External Event Edge Selection */
#وصف_ڪريو     AT91C_TC_EEVTEDG_NONE             ( ( بنانشان صحيح ) 0x0 << 8 )  /* (TC) Edge: None */
#وصف_ڪريو     AT91C_TC_EEVTEDG_RISING           ( ( بنانشان صحيح ) 0x1 << 8 )  /* (TC) Edge: rising edge */
#وصف_ڪريو     AT91C_TC_EEVTEDG_FALLING          ( ( بنانشان صحيح ) 0x2 << 8 )  /* (TC) Edge: falling edge */
#وصف_ڪريو     AT91C_TC_EEVTEDG_BOTH             ( ( بنانشان صحيح ) 0x3 << 8 )  /* (TC) Edge: each edge */
#وصف_ڪريو AT91C_TC_EEVT                         ( ( بنانشان صحيح ) 0x3 << 10 ) /* (TC) External Event  Selection */
#وصف_ڪريو     AT91C_TC_EEVT_TIOB                ( ( بنانشان صحيح ) 0x0 << 10 ) /* (TC) Signal selected as external event: TIOB TIOB direction: input */
#وصف_ڪريو     AT91C_TC_EEVT_XC0                 ( ( بنانشان صحيح ) 0x1 << 10 ) /* (TC) Signal selected as external event: XC0 TIOB direction: output */
#وصف_ڪريو     AT91C_TC_EEVT_XC1                 ( ( بنانشان صحيح ) 0x2 << 10 ) /* (TC) Signal selected as external event: XC1 TIOB direction: output */
#وصف_ڪريو     AT91C_TC_EEVT_XC2                 ( ( بنانشان صحيح ) 0x3 << 10 ) /* (TC) Signal selected as external event: XC2 TIOB direction: output */
#وصف_ڪريو AT91C_TC_ABETRG                       ( ( بنانشان صحيح ) 0x1 << 10 ) /* (TC) TIOA or TIOB External Trigger Selection */
#وصف_ڪريو AT91C_TC_ENETRG                       ( ( بنانشان صحيح ) 0x1 << 12 ) /* (TC) External Event Trigger enable */
#وصف_ڪريو AT91C_TC_WAVESEL                      ( ( بنانشان صحيح ) 0x3 << 13 ) /* (TC) Waveform  Selection */
#وصف_ڪريو     AT91_C_TC_WAVESEL_مٿي               ( ( بنانشان صحيح ) 0x0 << 13 ) /* (TC) UP mode without atomatic trigger on RC Compare */
#وصف_ڪريو     AT91C_TC_WAVESEL_UPDOWN           ( ( بنانشان صحيح ) 0x1 << 13 ) /* (TC) UPDOWN mode without automatic trigger on RC Compare */
#وصف_ڪريو     AT91_C_TC_WAVESEL_مٿي_AUTO          ( ( بنانشان صحيح ) 0x2 << 13 ) /* (TC) UP mode with automatic trigger on RC Compare */
#وصف_ڪريو     AT91C_TC_WAVESEL_UPDOWN_AUTO      ( ( بنانشان صحيح ) 0x3 << 13 ) /* (TC) UPDOWN mode with automatic trigger on RC Compare */
#وصف_ڪريو AT91C_TC_CPCTRG                       ( ( بنانشان صحيح ) 0x1 << 14 ) /* (TC) RC Compare Trigger Enable */
#وصف_ڪريو AT91C_TC_WAVE                         ( ( بنانشان صحيح ) 0x1 << 15 ) /* (TC) */
#وصف_ڪريو AT91C_TC_ACPA                         ( ( بنانشان صحيح ) 0x3 << 16 ) /* (TC) RA Compare Effect on TIOA */
#وصف_ڪريو     AT91C_TC_ACPA_NONE                ( ( بنانشان صحيح ) 0x0 << 16 ) /* (TC) Effect: none */
#وصف_ڪريو     AT91_C_TC_ACPA_سيٽ                 ( ( بنانشان صحيح ) 0x1 << 16 ) /* (TC) Effect: set */
#وصف_ڪريو     AT91C_TC_ACPA_CLEAR               ( ( بنانشان صحيح ) 0x2 << 16 ) /* (TC) Effect: clear */
#وصف_ڪريو     AT91C_TC_ACPA_TOGGLE              ( ( بنانشان صحيح ) 0x3 << 16 ) /* (TC) Effect: toggle */
#وصف_ڪريو AT91C_TC_LDRA                         ( ( بنانشان صحيح ) 0x3 << 16 ) /* (TC) RA Loading Selection */
#وصف_ڪريو     AT91C_TC_LDRA_NONE                ( ( بنانشان صحيح ) 0x0 << 16 ) /* (TC) Edge: None */
#وصف_ڪريو     AT91C_TC_LDRA_RISING              ( ( بنانشان صحيح ) 0x1 << 16 ) /* (TC) Edge: rising edge of TIOA */
#وصف_ڪريو     AT91C_TC_LDRA_FALLING             ( ( بنانشان صحيح ) 0x2 << 16 ) /* (TC) Edge: falling edge of TIOA */
#وصف_ڪريو     AT91C_TC_LDRA_BOTH                ( ( بنانشان صحيح ) 0x3 << 16 ) /* (TC) Edge: each edge of TIOA */
#وصف_ڪريو AT91C_TC_ACPC                         ( ( بنانشان صحيح ) 0x3 << 18 ) /* (TC) RC Compare Effect on TIOA */
#وصف_ڪريو     AT91C_TC_ACPC_NONE                ( ( بنانشان صحيح ) 0x0 << 18 ) /* (TC) Effect: none */
#وصف_ڪريو     AT91_C_TC_ACPC_سيٽ                 ( ( بنانشان صحيح ) 0x1 << 18 ) /* (TC) Effect: set */
#وصف_ڪريو     AT91C_TC_ACPC_CLEAR               ( ( بنانشان صحيح ) 0x2 << 18 ) /* (TC) Effect: clear */
#وصف_ڪريو     AT91C_TC_ACPC_TOGGLE              ( ( بنانشان صحيح ) 0x3 << 18 ) /* (TC) Effect: toggle */
#وصف_ڪريو AT91C_TC_LDRB                         ( ( بنانشان صحيح ) 0x3 << 18 ) /* (TC) RB Loading Selection */
#وصف_ڪريو     AT91C_TC_LDRB_NONE                ( ( بنانشان صحيح ) 0x0 << 18 ) /* (TC) Edge: None */
#وصف_ڪريو     AT91C_TC_LDRB_RISING              ( ( بنانشان صحيح ) 0x1 << 18 ) /* (TC) Edge: rising edge of TIOA */
#وصف_ڪريو     AT91C_TC_LDRB_FALLING             ( ( بنانشان صحيح ) 0x2 << 18 ) /* (TC) Edge: falling edge of TIOA */
#وصف_ڪريو     AT91C_TC_LDRB_BOTH                ( ( بنانشان صحيح ) 0x3 << 18 ) /* (TC) Edge: each edge of TIOA */
#وصف_ڪريو AT91C_TC_AEEVT                        ( ( بنانشان صحيح ) 0x3 << 20 ) /* (TC) External Event Effect on TIOA */
#وصف_ڪريو     AT91C_TC_AEEVT_NONE               ( ( بنانشان صحيح ) 0x0 << 20 ) /* (TC) Effect: none */
#وصف_ڪريو     AT91_C_TC_AEEVT_سيٽ                ( ( بنانشان صحيح ) 0x1 << 20 ) /* (TC) Effect: set */
#وصف_ڪريو     AT91C_TC_AEEVT_CLEAR              ( ( بنانشان صحيح ) 0x2 << 20 ) /* (TC) Effect: clear */
#وصف_ڪريو     AT91C_TC_AEEVT_TOGGLE             ( ( بنانشان صحيح ) 0x3 << 20 ) /* (TC) Effect: toggle */
#وصف_ڪريو AT91C_TC_ASWTRG                       ( ( بنانشان صحيح ) 0x3 << 22 ) /* (TC) Software Trigger Effect on TIOA */
#وصف_ڪريو     AT91C_TC_ASWTRG_NONE              ( ( بنانشان صحيح ) 0x0 << 22 ) /* (TC) Effect: none */
#وصف_ڪريو     AT91_C_TC_ASWTRG_سيٽ               ( ( بنانشان صحيح ) 0x1 << 22 ) /* (TC) Effect: set */
#وصف_ڪريو     AT91C_TC_ASWTRG_CLEAR             ( ( بنانشان صحيح ) 0x2 << 22 ) /* (TC) Effect: clear */
#وصف_ڪريو     AT91C_TC_ASWTRG_TOGGLE            ( ( بنانشان صحيح ) 0x3 << 22 ) /* (TC) Effect: toggle */
#وصف_ڪريو AT91C_TC_BCPB                         ( ( بنانشان صحيح ) 0x3 << 24 ) /* (TC) RB Compare Effect on TIOB */
#وصف_ڪريو     AT91C_TC_BCPB_NONE                ( ( بنانشان صحيح ) 0x0 << 24 ) /* (TC) Effect: none */
#وصف_ڪريو     AT91_C_TC_BCPB_سيٽ                 ( ( بنانشان صحيح ) 0x1 << 24 ) /* (TC) Effect: set */
#وصف_ڪريو     AT91C_TC_BCPB_CLEAR               ( ( بنانشان صحيح ) 0x2 << 24 ) /* (TC) Effect: clear */
#وصف_ڪريو     AT91C_TC_BCPB_TOGGLE              ( ( بنانشان صحيح ) 0x3 << 24 ) /* (TC) Effect: toggle */
#وصف_ڪريو AT91C_TC_BCPC                         ( ( بنانشان صحيح ) 0x3 << 26 ) /* (TC) RC Compare Effect on TIOB */
#وصف_ڪريو     AT91C_TC_BCPC_NONE                ( ( بنانشان صحيح ) 0x0 << 26 ) /* (TC) Effect: none */
#وصف_ڪريو     AT91_C_TC_BCPC_سيٽ                 ( ( بنانشان صحيح ) 0x1 << 26 ) /* (TC) Effect: set */
#وصف_ڪريو     AT91C_TC_BCPC_CLEAR               ( ( بنانشان صحيح ) 0x2 << 26 ) /* (TC) Effect: clear */
#وصف_ڪريو     AT91C_TC_BCPC_TOGGLE              ( ( بنانشان صحيح ) 0x3 << 26 ) /* (TC) Effect: toggle */
#وصف_ڪريو AT91C_TC_BEEVT                        ( ( بنانشان صحيح ) 0x3 << 28 ) /* (TC) External Event Effect on TIOB */
#وصف_ڪريو     AT91C_TC_BEEVT_NONE               ( ( بنانشان صحيح ) 0x0 << 28 ) /* (TC) Effect: none */
#وصف_ڪريو     AT91_C_TC_BEEVT_سيٽ                ( ( بنانشان صحيح ) 0x1 << 28 ) /* (TC) Effect: set */
#وصف_ڪريو     AT91C_TC_BEEVT_CLEAR              ( ( بنانشان صحيح ) 0x2 << 28 ) /* (TC) Effect: clear */
#وصف_ڪريو     AT91C_TC_BEEVT_TOGGLE             ( ( بنانشان صحيح ) 0x3 << 28 ) /* (TC) Effect: toggle */
#وصف_ڪريو AT91C_TC_BSWTRG                       ( ( بنانشان صحيح ) 0x3 << 30 ) /* (TC) Software Trigger Effect on TIOB */
#وصف_ڪريو     AT91C_TC_BSWTRG_NONE              ( ( بنانشان صحيح ) 0x0 << 30 ) /* (TC) Effect: none */
#وصف_ڪريو     AT91_C_TC_BSWTRG_سيٽ               ( ( بنانشان صحيح ) 0x1 << 30 ) /* (TC) Effect: set */
#وصف_ڪريو     AT91C_TC_BSWTRG_CLEAR             ( ( بنانشان صحيح ) 0x2 << 30 ) /* (TC) Effect: clear */
#وصف_ڪريو     AT91C_TC_BSWTRG_TOGGLE            ( ( بنانشان صحيح ) 0x3 << 30 ) /* (TC) Effect: toggle */
/* -------- TC_SR : (TC Offset: 0x20) TC Channel Status Register -------- */
#وصف_ڪريو AT91C_TC_COVFS                        ( ( بنانشان صحيح ) 0x1 << 0 )  /* (TC) Counter Overflow */
#وصف_ڪريو AT91C_TC_LOVRS                        ( ( بنانشان صحيح ) 0x1 << 1 )  /* (TC) Load Overrun */
#وصف_ڪريو AT91C_TC_CPAS                         ( ( بنانشان صحيح ) 0x1 << 2 )  /* (TC) RA Compare */
#وصف_ڪريو AT91C_TC_CPBS                         ( ( بنانشان صحيح ) 0x1 << 3 )  /* (TC) RB Compare */
#وصف_ڪريو AT91C_TC_CPCS                         ( ( بنانشان صحيح ) 0x1 << 4 )  /* (TC) RC Compare */
#وصف_ڪريو AT91C_TC_LDRAS                        ( ( بنانشان صحيح ) 0x1 << 5 )  /* (TC) RA Loading */
#وصف_ڪريو AT91C_TC_LDRBS                        ( ( بنانشان صحيح ) 0x1 << 6 )  /* (TC) RB Loading */
#وصف_ڪريو AT91C_TC_ETRGS                        ( ( بنانشان صحيح ) 0x1 << 7 )  /* (TC) External Trigger */
#وصف_ڪريو AT91C_TC_CLKSTA                       ( ( بنانشان صحيح ) 0x1 << 16 ) /* (TC) Clock Enabling */
#وصف_ڪريو AT91C_TC_MTIOA                        ( ( بنانشان صحيح ) 0x1 << 17 ) /* (TC) TIOA Mirror */
#وصف_ڪريو AT91C_TC_MTIOB                        ( ( بنانشان صحيح ) 0x1 << 18 ) /* (TC) TIOA Mirror */
/* -------- TC_IER : (TC Offset: 0x24) TC Channel Interrupt Enable Register -------- */
/* -------- TC_IDR : (TC Offset: 0x28) TC Channel Interrupt Disable Register -------- */
/* -------- TC_IMR : (TC Offset: 0x2c) TC Channel Interrupt Mask Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Timer Counter Interface */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_TCB
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
#وصف_ڪريو AT91C_TCB_SYNC                 ( ( بنانشان صحيح ) 0x1 << 0 ) /* (TCB) Synchro Command */
/* -------- TCB_BMR : (TCB Offset: 0xc4) TC Block Mode Register -------- */
#وصف_ڪريو AT91C_TCB_TC0XC0S              ( ( بنانشان صحيح ) 0x3 << 0 ) /* (TCB) External Clock Signal 0 Selection */
#وصف_ڪريو     AT91C_TCB_TC0XC0S_TCLK0    ( ( بنانشان صحيح ) 0x0 )      /* (TCB) TCLK0 connected to XC0 */
#وصف_ڪريو     AT91C_TCB_TC0XC0S_NONE     ( ( بنانشان صحيح ) 0x1 )      /* (TCB) None signal connected to XC0 */
#وصف_ڪريو     AT91C_TCB_TC0XC0S_TIOA1    ( ( بنانشان صحيح ) 0x2 )      /* (TCB) TIOA1 connected to XC0 */
#وصف_ڪريو     AT91C_TCB_TC0XC0S_TIOA2    ( ( بنانشان صحيح ) 0x3 )      /* (TCB) TIOA2 connected to XC0 */
#وصف_ڪريو AT91C_TCB_TC1XC1S              ( ( بنانشان صحيح ) 0x3 << 2 ) /* (TCB) External Clock Signal 1 Selection */
#وصف_ڪريو     AT91C_TCB_TC1XC1S_TCLK1    ( ( بنانشان صحيح ) 0x0 << 2 ) /* (TCB) TCLK1 connected to XC1 */
#وصف_ڪريو     AT91C_TCB_TC1XC1S_NONE     ( ( بنانشان صحيح ) 0x1 << 2 ) /* (TCB) None signal connected to XC1 */
#وصف_ڪريو     AT91C_TCB_TC1XC1S_TIOA0    ( ( بنانشان صحيح ) 0x2 << 2 ) /* (TCB) TIOA0 connected to XC1 */
#وصف_ڪريو     AT91C_TCB_TC1XC1S_TIOA2    ( ( بنانشان صحيح ) 0x3 << 2 ) /* (TCB) TIOA2 connected to XC1 */
#وصف_ڪريو AT91C_TCB_TC2XC2S              ( ( بنانشان صحيح ) 0x3 << 4 ) /* (TCB) External Clock Signal 2 Selection */
#وصف_ڪريو     AT91C_TCB_TC2XC2S_TCLK2    ( ( بنانشان صحيح ) 0x0 << 4 ) /* (TCB) TCLK2 connected to XC2 */
#وصف_ڪريو     AT91C_TCB_TC2XC2S_NONE     ( ( بنانشان صحيح ) 0x1 << 4 ) /* (TCB) None signal connected to XC2 */
#وصف_ڪريو     AT91C_TCB_TC2XC2S_TIOA0    ( ( بنانشان صحيح ) 0x2 << 4 ) /* (TCB) TIOA0 connected to XC2 */
#وصف_ڪريو     AT91C_TCB_TC2XC2S_TIOA1    ( ( بنانشان صحيح ) 0x3 << 4 ) /* (TCB) TIOA2 connected to XC2 */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Control Area Network MailBox Interface */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_CAN_MB
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
#وصف_ڪريو AT91C_CAN_MTIMEMARK              ( ( بنانشان صحيح ) 0xFFFF << 0 )  /* (CAN_MB) Mailbox Timemark */
#وصف_ڪريو AT91_C_CAN_اڳواٽ                  ( ( بنانشان صحيح ) 0xF << 16 )    /* (CAN_MB) Mailbox Priority */
#وصف_ڪريو AT91C_CAN_MOT                    ( ( بنانشان صحيح ) 0x7 << 24 )    /* (CAN_MB) Mailbox Object Type */
#وصف_ڪريو     AT91C_CAN_MOT_DIS            ( ( بنانشان صحيح ) 0x0 << 24 )    /* (CAN_MB) */
#وصف_ڪريو     AT91C_CAN_MOT_RX             ( ( بنانشان صحيح ) 0x1 << 24 )    /* (CAN_MB) */
#وصف_ڪريو     AT91C_CAN_MOT_RXOVERWRITE    ( ( بنانشان صحيح ) 0x2 << 24 )    /* (CAN_MB) */
#وصف_ڪريو     AT91C_CAN_MOT_TX             ( ( بنانشان صحيح ) 0x3 << 24 )    /* (CAN_MB) */
#وصف_ڪريو     AT91_C_CAN_MOT_استعمال_ڪندڙ       ( ( بنانشان صحيح ) 0x4 << 24 )    /* (CAN_MB) */
#وصف_ڪريو     AT91_C_CAN_MOT_پيداوار_ڪندڙ       ( ( بنانشان صحيح ) 0x5 << 24 )    /* (CAN_MB) */
/* -------- CAN_MAM : (CAN_MB Offset: 0x4) CAN Message Acceptance Mask Register -------- */
#وصف_ڪريو AT91C_CAN_MIDvB                  ( ( بنانشان صحيح ) 0x3FFFF << 0 ) /* (CAN_MB) Complementary bits for identifier in extended mode */
#وصف_ڪريو AT91C_CAN_MIDvA                  ( ( بنانشان صحيح ) 0x7FF << 18 )  /* (CAN_MB) Identifier for standard frame mode */
#وصف_ڪريو AT91C_CAN_MIDE                   ( ( بنانشان صحيح ) 0x1 << 29 )    /* (CAN_MB) Identifier Version */
/* -------- CAN_MID : (CAN_MB Offset: 0x8) CAN Message ID Register -------- */
/* -------- CAN_MFID : (CAN_MB Offset: 0xc) CAN Message Family ID Register -------- */
/* -------- CAN_MSR : (CAN_MB Offset: 0x10) CAN Message Status Register -------- */
#وصف_ڪريو AT91C_CAN_MTIMESTAMP    ( ( بنانشان صحيح ) 0xFFFF << 0 ) /* (CAN_MB) Timer Value */
#وصف_ڪريو AT91C_CAN_MDLC          ( ( بنانشان صحيح ) 0xF << 16 )   /* (CAN_MB) Mailbox Data Length Code */
#وصف_ڪريو AT91C_CAN_MRTR          ( ( بنانشان صحيح ) 0x1 << 20 )   /* (CAN_MB) Mailbox Remote Transmission Request */
#وصف_ڪريو AT91C_CAN_MABT          ( ( بنانشان صحيح ) 0x1 << 22 )   /* (CAN_MB) Mailbox Message Abort */
#وصف_ڪريو AT91C_CAN_MRDY          ( ( بنانشان صحيح ) 0x1 << 23 )   /* (CAN_MB) Mailbox Ready */
#وصف_ڪريو AT91C_CAN_MMI           ( ( بنانشان صحيح ) 0x1 << 24 )   /* (CAN_MB) Mailbox Message Ignored */
/* -------- CAN_MDL : (CAN_MB Offset: 0x14) CAN Message Data Low Register -------- */
/* -------- CAN_MDH : (CAN_MB Offset: 0x18) CAN Message Data High Register -------- */
/* -------- CAN_MCR : (CAN_MB Offset: 0x1c) CAN Message Control Register -------- */
#وصف_ڪريو AT91C_CAN_MACR    ( ( بنانشان صحيح ) 0x1 << 22 ) /* (CAN_MB) Abort Request for Mailbox */
#وصف_ڪريو AT91C_CAN_MTCR    ( ( بنانشان صحيح ) 0x1 << 23 ) /* (CAN_MB) Mailbox Transfer Command */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Control Area Network Interface */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_CAN
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
#وصف_ڪريو AT91C_CAN_CANEN     ( ( بنانشان صحيح ) 0x1 << 0 )  /* (CAN) CAN Controller Enable */
#وصف_ڪريو AT91C_CAN_LPM       ( ( بنانشان صحيح ) 0x1 << 1 )  /* (CAN) Disable/Enable Low Power Mode */
#وصف_ڪريو AT91C_CAN_ABM       ( ( بنانشان صحيح ) 0x1 << 2 )  /* (CAN) Disable/Enable Autobaud/Listen Mode */
#وصف_ڪريو AT91C_CAN_OVL       ( ( بنانشان صحيح ) 0x1 << 3 )  /* (CAN) Disable/Enable Overload Frame */
#وصف_ڪريو AT91C_CAN_TEOF      ( ( بنانشان صحيح ) 0x1 << 4 )  /* (CAN) Time Stamp messages at each end of Frame */
#وصف_ڪريو AT91C_CAN_TTM       ( ( بنانشان صحيح ) 0x1 << 5 )  /* (CAN) Disable/Enable Time Trigger Mode */
#وصف_ڪريو AT91C_CAN_TIMFRZ    ( ( بنانشان صحيح ) 0x1 << 6 )  /* (CAN) Enable Timer Freeze */
#وصف_ڪريو AT91C_CAN_DRPT      ( ( بنانشان صحيح ) 0x1 << 7 )  /* (CAN) Disable Repeat */
/* -------- CAN_IER : (CAN Offset: 0x4) CAN Interrupt Enable Register -------- */
#وصف_ڪريو AT91C_CAN_MB0       ( ( بنانشان صحيح ) 0x1 << 0 )  /* (CAN) Mailbox 0 Flag */
#وصف_ڪريو AT91C_CAN_MB1       ( ( بنانشان صحيح ) 0x1 << 1 )  /* (CAN) Mailbox 1 Flag */
#وصف_ڪريو AT91C_CAN_MB2       ( ( بنانشان صحيح ) 0x1 << 2 )  /* (CAN) Mailbox 2 Flag */
#وصف_ڪريو AT91C_CAN_MB3       ( ( بنانشان صحيح ) 0x1 << 3 )  /* (CAN) Mailbox 3 Flag */
#وصف_ڪريو AT91C_CAN_MB4       ( ( بنانشان صحيح ) 0x1 << 4 )  /* (CAN) Mailbox 4 Flag */
#وصف_ڪريو AT91C_CAN_MB5       ( ( بنانشان صحيح ) 0x1 << 5 )  /* (CAN) Mailbox 5 Flag */
#وصف_ڪريو AT91C_CAN_MB6       ( ( بنانشان صحيح ) 0x1 << 6 )  /* (CAN) Mailbox 6 Flag */
#وصف_ڪريو AT91C_CAN_MB7       ( ( بنانشان صحيح ) 0x1 << 7 )  /* (CAN) Mailbox 7 Flag */
#وصف_ڪريو AT91C_CAN_MB8       ( ( بنانشان صحيح ) 0x1 << 8 )  /* (CAN) Mailbox 8 Flag */
#وصف_ڪريو AT91C_CAN_MB9       ( ( بنانشان صحيح ) 0x1 << 9 )  /* (CAN) Mailbox 9 Flag */
#وصف_ڪريو AT91C_CAN_MB10      ( ( بنانشان صحيح ) 0x1 << 10 ) /* (CAN) Mailbox 10 Flag */
#وصف_ڪريو AT91C_CAN_MB11      ( ( بنانشان صحيح ) 0x1 << 11 ) /* (CAN) Mailbox 11 Flag */
#وصف_ڪريو AT91C_CAN_MB12      ( ( بنانشان صحيح ) 0x1 << 12 ) /* (CAN) Mailbox 12 Flag */
#وصف_ڪريو AT91C_CAN_MB13      ( ( بنانشان صحيح ) 0x1 << 13 ) /* (CAN) Mailbox 13 Flag */
#وصف_ڪريو AT91C_CAN_MB14      ( ( بنانشان صحيح ) 0x1 << 14 ) /* (CAN) Mailbox 14 Flag */
#وصف_ڪريو AT91C_CAN_MB15      ( ( بنانشان صحيح ) 0x1 << 15 ) /* (CAN) Mailbox 15 Flag */
#وصف_ڪريو AT91C_CAN_ERRA      ( ( بنانشان صحيح ) 0x1 << 16 ) /* (CAN) Error Active Mode Flag */
#وصف_ڪريو AT91C_CAN_WARN      ( ( بنانشان صحيح ) 0x1 << 17 ) /* (CAN) Warning Limit Flag */
#وصف_ڪريو AT91C_CAN_ERRP      ( ( بنانشان صحيح ) 0x1 << 18 ) /* (CAN) Error Passive Mode Flag */
#وصف_ڪريو AT91C_CAN_BOFF      ( ( بنانشان صحيح ) 0x1 << 19 ) /* (CAN) Bus Off Mode Flag */
#وصف_ڪريو AT91C_CAN_SLEEP     ( ( بنانشان صحيح ) 0x1 << 20 ) /* (CAN) Sleep Flag */
#وصف_ڪريو AT91C_CAN_WAKEUP    ( ( بنانشان صحيح ) 0x1 << 21 ) /* (CAN) Wakeup Flag */
#وصف_ڪريو AT91C_CAN_TOVF      ( ( بنانشان صحيح ) 0x1 << 22 ) /* (CAN) Timer Overflow Flag */
#وصف_ڪريو AT91C_CAN_TSTP      ( ( بنانشان صحيح ) 0x1 << 23 ) /* (CAN) Timestamp Flag */
#وصف_ڪريو AT91C_CAN_CERR      ( ( بنانشان صحيح ) 0x1 << 24 ) /* (CAN) CRC Error */
#وصف_ڪريو AT91C_CAN_SERR      ( ( بنانشان صحيح ) 0x1 << 25 ) /* (CAN) Stuffing Error */
#وصف_ڪريو AT91C_CAN_AERR      ( ( بنانشان صحيح ) 0x1 << 26 ) /* (CAN) Acknowledgment Error */
#وصف_ڪريو AT91C_CAN_FERR      ( ( بنانشان صحيح ) 0x1 << 27 ) /* (CAN) Form Error */
#وصف_ڪريو AT91C_CAN_BERR      ( ( بنانشان صحيح ) 0x1 << 28 ) /* (CAN) Bit Error */
/* -------- CAN_IDR : (CAN Offset: 0x8) CAN Interrupt Disable Register -------- */
/* -------- CAN_IMR : (CAN Offset: 0xc) CAN Interrupt Mask Register -------- */
/* -------- CAN_SR : (CAN Offset: 0x10) CAN Status Register -------- */
#وصف_ڪريو AT91C_CAN_RBSY      ( ( بنانشان صحيح ) 0x1 << 29 )   /* (CAN) Receiver Busy */
#وصف_ڪريو AT91C_CAN_TBSY      ( ( بنانشان صحيح ) 0x1 << 30 )   /* (CAN) Transmitter Busy */
#وصف_ڪريو AT91C_CAN_OVLY      ( ( بنانشان صحيح ) 0x1 << 31 )   /* (CAN) Overload Busy */
/* -------- CAN_BR : (CAN Offset: 0x14) CAN Baudrate Register -------- */
#وصف_ڪريو AT91C_CAN_PHASE2    ( ( بنانشان صحيح ) 0x7 << 0 )    /* (CAN) Phase 2 segment */
#وصف_ڪريو AT91C_CAN_PHASE1    ( ( بنانشان صحيح ) 0x7 << 4 )    /* (CAN) Phase 1 segment */
#وصف_ڪريو AT91C_CAN_PROPAG    ( ( بنانشان صحيح ) 0x7 << 8 )    /* (CAN) Programmation time segment */
#وصف_ڪريو AT91C_CAN_SYNC      ( ( بنانشان صحيح ) 0x3 << 12 )   /* (CAN) Re-synchronization jump width segment */
#وصف_ڪريو AT91C_CAN_BRP       ( ( بنانشان صحيح ) 0x7F << 16 )  /* (CAN) Baudrate Prescaler */
#وصف_ڪريو AT91C_CAN_SMP       ( ( بنانشان صحيح ) 0x1 << 24 )   /* (CAN) Sampling mode */
/* -------- CAN_TIM : (CAN Offset: 0x18) CAN Timer Register -------- */
#وصف_ڪريو AT91C_CAN_TIMER     ( ( بنانشان صحيح ) 0xFFFF << 0 ) /* (CAN) Timer field */
/* -------- CAN_TIMESTP : (CAN Offset: 0x1c) CAN Timestamp Register -------- */
/* -------- CAN_ECR : (CAN Offset: 0x20) CAN Error Counter Register -------- */
#وصف_ڪريو AT91C_CAN_REC       ( ( بنانشان صحيح ) 0xFF << 0 )  /* (CAN) Receive Error Counter */
#وصف_ڪريو AT91C_CAN_TEC       ( ( بنانشان صحيح ) 0xFF << 16 ) /* (CAN) Transmit Error Counter */
/* -------- CAN_TCR : (CAN Offset: 0x24) CAN Transfer Command Register -------- */
#وصف_ڪريو AT91C_CAN_TIMRST    ( ( بنانشان صحيح ) 0x1 << 31 )  /* (CAN) Timer Reset Field */
/* -------- CAN_ACR : (CAN Offset: 0x28) CAN Abort Command Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Ethernet MAC 10/100 */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_EMAC
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
#وصف_ڪريو AT91C_EMAC_LB                   ( ( بنانشان صحيح ) 0x1 << 0 )  /* (EMAC) Loopback. Optional. When set, loopback signal is at high level. */
#وصف_ڪريو AT91C_EMAC_LLB                  ( ( بنانشان صحيح ) 0x1 << 1 )  /* (EMAC) Loopback local. */
#وصف_ڪريو AT91C_EMAC_RE                   ( ( بنانشان صحيح ) 0x1 << 2 )  /* (EMAC) Receive enable. */
#وصف_ڪريو AT91C_EMAC_TE                   ( ( بنانشان صحيح ) 0x1 << 3 )  /* (EMAC) Transmit enable. */
#وصف_ڪريو AT91C_EMAC_MPE                  ( ( بنانشان صحيح ) 0x1 << 4 )  /* (EMAC) Management port enable. */
#وصف_ڪريو AT91C_EMAC_CLRSTAT              ( ( بنانشان صحيح ) 0x1 << 5 )  /* (EMAC) Clear statistics registers. */
#وصف_ڪريو AT91C_EMAC_INCSTAT              ( ( بنانشان صحيح ) 0x1 << 6 )  /* (EMAC) Increment statistics registers. */
#وصف_ڪريو AT91C_EMAC_WESTAT               ( ( بنانشان صحيح ) 0x1 << 7 )  /* (EMAC) Write enable for statistics registers. */
#وصف_ڪريو AT91C_EMAC_BP                   ( ( بنانشان صحيح ) 0x1 << 8 )  /* (EMAC) Back pressure. */
#وصف_ڪريو AT91C_EMAC_TSTART               ( ( بنانشان صحيح ) 0x1 << 9 )  /* (EMAC) Start Transmission. */
#وصف_ڪريو AT91C_EMAC_THALT                ( ( بنانشان صحيح ) 0x1 << 10 ) /* (EMAC) Transmission Halt. */
#وصف_ڪريو AT91C_EMAC_TPFR                 ( ( بنانشان صحيح ) 0x1 << 11 ) /* (EMAC) Transmit pause frame */
#وصف_ڪريو AT91C_EMAC_TZQ                  ( ( بنانشان صحيح ) 0x1 << 12 ) /* (EMAC) Transmit zero quantum pause frame */
/* -------- EMAC_NCFGR : (EMAC Offset: 0x4) Network Configuration Register -------- */
#وصف_ڪريو AT91C_EMAC_SPD                  ( ( بنانشان صحيح ) 0x1 << 0 )  /* (EMAC) Speed. */
#وصف_ڪريو AT91C_EMAC_FD                   ( ( بنانشان صحيح ) 0x1 << 1 )  /* (EMAC) Full duplex. */
#وصف_ڪريو AT91C_EMAC_JFRAME               ( ( بنانشان صحيح ) 0x1 << 3 )  /* (EMAC) Jumbo Frames. */
#وصف_ڪريو AT91C_EMAC_CAF                  ( ( بنانشان صحيح ) 0x1 << 4 )  /* (EMAC) Copy all frames. */
#وصف_ڪريو AT91C_EMAC_NBC                  ( ( بنانشان صحيح ) 0x1 << 5 )  /* (EMAC) No broadcast. */
#وصف_ڪريو AT91C_EMAC_MTI                  ( ( بنانشان صحيح ) 0x1 << 6 )  /* (EMAC) Multicast hash event enable */
#وصف_ڪريو AT91C_EMAC_UNI                  ( ( بنانشان صحيح ) 0x1 << 7 )  /* (EMAC) Unicast hash enable. */
#وصف_ڪريو AT91C_EMAC_BIG                  ( ( بنانشان صحيح ) 0x1 << 8 )  /* (EMAC) Receive 1522 bytes. */
#وصف_ڪريو AT91C_EMAC_EAE                  ( ( بنانشان صحيح ) 0x1 << 9 )  /* (EMAC) External address match enable. */
#وصف_ڪريو AT91C_EMAC_CLK                  ( ( بنانشان صحيح ) 0x3 << 10 ) /* (EMAC) */
#وصف_ڪريو     AT91C_EMAC_CLK_HCLK_8       ( ( بنانشان صحيح ) 0x0 << 10 ) /* (EMAC) HCLK divided by 8 */
#وصف_ڪريو     AT91C_EMAC_CLK_HCLK_16      ( ( بنانشان صحيح ) 0x1 << 10 ) /* (EMAC) HCLK divided by 16 */
#وصف_ڪريو     AT91C_EMAC_CLK_HCLK_32      ( ( بنانشان صحيح ) 0x2 << 10 ) /* (EMAC) HCLK divided by 32 */
#وصف_ڪريو     AT91C_EMAC_CLK_HCLK_64      ( ( بنانشان صحيح ) 0x3 << 10 ) /* (EMAC) HCLK divided by 64 */
#وصف_ڪريو AT91C_EMAC_RTY                  ( ( بنانشان صحيح ) 0x1 << 12 ) /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_PAE                  ( ( بنانشان صحيح ) 0x1 << 13 ) /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_RBOF                 ( ( بنانشان صحيح ) 0x3 << 14 ) /* (EMAC) */
#وصف_ڪريو     AT91_C_EMAC_RBOF_وٿي_0    ( ( بنانشان صحيح ) 0x0 << 14 ) /* (EMAC) no offset from start of receive buffer */
#وصف_ڪريو     AT91_C_EMAC_RBOF_وٿي_1    ( ( بنانشان صحيح ) 0x1 << 14 ) /* (EMAC) one byte offset from start of receive buffer */
#وصف_ڪريو     AT91_C_EMAC_RBOF_وٿي_2    ( ( بنانشان صحيح ) 0x2 << 14 ) /* (EMAC) two bytes offset from start of receive buffer */
#وصف_ڪريو     AT91_C_EMAC_RBOF_وٿي_3    ( ( بنانشان صحيح ) 0x3 << 14 ) /* (EMAC) three bytes offset from start of receive buffer */
#وصف_ڪريو AT91C_EMAC_RLCE                 ( ( بنانشان صحيح ) 0x1 << 16 ) /* (EMAC) Receive Length field Checking Enable */
#وصف_ڪريو AT91C_EMAC_DRFCS                ( ( بنانشان صحيح ) 0x1 << 17 ) /* (EMAC) Discard Receive FCS */
#وصف_ڪريو AT91C_EMAC_EFRHD                ( ( بنانشان صحيح ) 0x1 << 18 ) /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_IRXFCS               ( ( بنانشان صحيح ) 0x1 << 19 ) /* (EMAC) Ignore RX FCS */
/* -------- EMAC_NSR : (EMAC Offset: 0x8) Network Status Register -------- */
#وصف_ڪريو AT91C_EMAC_LINKR                ( ( بنانشان صحيح ) 0x1 << 0 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_MDIO                 ( ( بنانشان صحيح ) 0x1 << 1 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_IDLE                 ( ( بنانشان صحيح ) 0x1 << 2 )  /* (EMAC) */
/* -------- EMAC_TSR : (EMAC Offset: 0x14) Transmit Status Register -------- */
#وصف_ڪريو AT91C_EMAC_UBR                  ( ( بنانشان صحيح ) 0x1 << 0 )  /* (EMAC) */
#وصف_ڪريو AT91_C_EMAC_کانو                  ( ( بنانشان صحيح ) 0x1 << 1 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_RLES                 ( ( بنانشان صحيح ) 0x1 << 2 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_TGO                  ( ( بنانشان صحيح ) 0x1 << 3 )  /* (EMAC) Transmit Go */
#وصف_ڪريو AT91C_EMAC_BEX                  ( ( بنانشان صحيح ) 0x1 << 4 )  /* (EMAC) Buffers exhausted mid frame */
#وصف_ڪريو AT91C_EMAC_COMP                 ( ( بنانشان صحيح ) 0x1 << 5 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_UND                  ( ( بنانشان صحيح ) 0x1 << 6 )  /* (EMAC) */
/* -------- EMAC_RSR : (EMAC Offset: 0x20) Receive Status Register -------- */
#وصف_ڪريو AT91C_EMAC_BNA                  ( ( بنانشان صحيح ) 0x1 << 0 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_REC                  ( ( بنانشان صحيح ) 0x1 << 1 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_OVR                  ( ( بنانشان صحيح ) 0x1 << 2 )  /* (EMAC) */
/* -------- EMAC_ISR : (EMAC Offset: 0x24) Interrupt Status Register -------- */
#وصف_ڪريو AT91C_EMAC_MFD                  ( ( بنانشان صحيح ) 0x1 << 0 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_RCOMP                ( ( بنانشان صحيح ) 0x1 << 1 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_RXUBR                ( ( بنانشان صحيح ) 0x1 << 2 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_TXUBR                ( ( بنانشان صحيح ) 0x1 << 3 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_TUNDR                ( ( بنانشان صحيح ) 0x1 << 4 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_RLEX                 ( ( بنانشان صحيح ) 0x1 << 5 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_TXERR                ( ( بنانشان صحيح ) 0x1 << 6 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_TCOMP                ( ( بنانشان صحيح ) 0x1 << 7 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_LINK                 ( ( بنانشان صحيح ) 0x1 << 9 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_ROVR                 ( ( بنانشان صحيح ) 0x1 << 10 ) /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_HRESP                ( ( بنانشان صحيح ) 0x1 << 11 ) /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_PFRE                 ( ( بنانشان صحيح ) 0x1 << 12 ) /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_PTZ                  ( ( بنانشان صحيح ) 0x1 << 13 ) /* (EMAC) */
/* -------- EMAC_IER : (EMAC Offset: 0x28) Interrupt Enable Register -------- */
/* -------- EMAC_IDR : (EMAC Offset: 0x2c) Interrupt Disable Register -------- */
/* -------- EMAC_IMR : (EMAC Offset: 0x30) Interrupt Mask Register -------- */
/* -------- EMAC_MAN : (EMAC Offset: 0x34) PHY Maintenance Register -------- */
#وصف_ڪريو AT91_C_EMAC_معلومات       ( ( بنانشان صحيح ) 0xFFFF << 0 )  /* (EMAC) */
#وصف_ڪريو AT91_C_EMAC_ڪوڊ       ( ( بنانشان صحيح ) 0x3 << 16 )    /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_REGA       ( ( بنانشان صحيح ) 0x1F << 18 )   /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_PHYA       ( ( بنانشان صحيح ) 0x1F << 23 )   /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_RW         ( ( بنانشان صحيح ) 0x3 << 28 )    /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_SOF        ( ( بنانشان صحيح ) 0x3 << 30 )    /* (EMAC) */
/* -------- EMAC_USRIO : (EMAC Offset: 0xc0) USER Input Output Register -------- */
#وصف_ڪريو AT91C_EMAC_RMII       ( ( بنانشان صحيح ) 0x1 << 0 )     /* (EMAC) Reduce MII */
/* -------- EMAC_WOL : (EMAC Offset: 0xc4) Wake On LAN Register -------- */
#وصف_ڪريو AT91C_EMAC_IP         ( ( بنانشان صحيح ) 0xFFFF << 0 )  /* (EMAC) ARP request IP address */
#وصف_ڪريو AT91C_EMAC_MAG        ( ( بنانشان صحيح ) 0x1 << 16 )    /* (EMAC) Magic packet event enable */
#وصف_ڪريو AT91C_EMAC_ARP        ( ( بنانشان صحيح ) 0x1 << 17 )    /* (EMAC) ARP request event enable */
#وصف_ڪريو AT91C_EMAC_SA1        ( ( بنانشان صحيح ) 0x1 << 18 )    /* (EMAC) Specific address register 1 event enable */
/* -------- EMAC_REV : (EMAC Offset: 0xfc) Revision Register -------- */
#وصف_ڪريو AT91C_EMAC_REVREF     ( ( بنانشان صحيح ) 0xFFFF << 0 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_PARTREF    ( ( بنانشان صحيح ) 0xFFFF << 16 ) /* (EMAC) */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Analog to Digital Convertor */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_ADC
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
#وصف_ڪريو AT91C_ADC_SWRST                    ( ( بنانشان صحيح ) 0x1 << 0 )   /* (ADC) Software Reset */
#وصف_ڪريو AT91_C_ADC_شروعات                    ( ( بنانشان صحيح ) 0x1 << 1 )   /* (ADC) Start Conversion */
/* -------- ADC_MR : (ADC Offset: 0x4) ADC Mode Register -------- */
#وصف_ڪريو AT91C_ADC_TRGEN                    ( ( بنانشان صحيح ) 0x1 << 0 )   /* (ADC) Trigger Enable */
#وصف_ڪريو     AT91C_ADC_TRGEN_DIS            ( ( بنانشان صحيح ) 0x0 )        /* (ADC) Hardware triggers are disabled. Starting a conversion is only possible by software */
#وصف_ڪريو     AT91C_ADC_TRGEN_EN             ( ( بنانشان صحيح ) 0x1 )        /* (ADC) Hardware trigger selected by TRGSEL field is enabled. */
#وصف_ڪريو AT91C_ADC_TRGSEL                   ( ( بنانشان صحيح ) 0x7 << 1 )   /* (ADC) Trigger Selection */
#وصف_ڪريو     AT91C_ADC_TRGSEL_TIOA0         ( ( بنانشان صحيح ) 0x0 << 1 )   /* (ADC) Selected TRGSEL = TIAO0 */
#وصف_ڪريو     AT91C_ADC_TRGSEL_TIOA1         ( ( بنانشان صحيح ) 0x1 << 1 )   /* (ADC) Selected TRGSEL = TIAO1 */
#وصف_ڪريو     AT91C_ADC_TRGSEL_TIOA2         ( ( بنانشان صحيح ) 0x2 << 1 )   /* (ADC) Selected TRGSEL = TIAO2 */
#وصف_ڪريو     AT91C_ADC_TRGSEL_TIOA3         ( ( بنانشان صحيح ) 0x3 << 1 )   /* (ADC) Selected TRGSEL = TIAO3 */
#وصف_ڪريو     AT91C_ADC_TRGSEL_TIOA4         ( ( بنانشان صحيح ) 0x4 << 1 )   /* (ADC) Selected TRGSEL = TIAO4 */
#وصف_ڪريو     AT91C_ADC_TRGSEL_TIOA5         ( ( بنانشان صحيح ) 0x5 << 1 )   /* (ADC) Selected TRGSEL = TIAO5 */
#وصف_ڪريو     AT91C_ADC_TRGSEL_EXT           ( ( بنانشان صحيح ) 0x6 << 1 )   /* (ADC) Selected TRGSEL = External Trigger */
#وصف_ڪريو AT91C_ADC_LOWRES                   ( ( بنانشان صحيح ) 0x1 << 4 )   /* (ADC) Resolution. */
#وصف_ڪريو     AT91_C_ADC_LOWRES_10_ٻٽو_انگ        ( ( بنانشان صحيح ) 0x0 << 4 )   /* (ADC) 10-bit resolution */
#وصف_ڪريو     AT91_C_ADC_LOWRES_8_ٻٽو_انگ         ( ( بنانشان صحيح ) 0x1 << 4 )   /* (ADC) 8-bit resolution */
#وصف_ڪريو AT91C_ADC_SLEEP                    ( ( بنانشان صحيح ) 0x1 << 5 )   /* (ADC) Sleep Mode */
#وصف_ڪريو     AT91_C_ADC_SLEEP_عام_گهڻائي    ( ( بنانشان صحيح ) 0x0 << 5 )   /* (ADC) Normal Mode */
#وصف_ڪريو     AT91_C_ADC_SLEEP_گهڻائي           ( ( بنانشان صحيح ) 0x1 << 5 )   /* (ADC) Sleep Mode */
#وصف_ڪريو AT91C_ADC_PRESCAL                  ( ( بنانشان صحيح ) 0x3F << 8 )  /* (ADC) Prescaler rate selection */
#وصف_ڪريو AT91C_ADC_STARTUP                  ( ( بنانشان صحيح ) 0x1F << 16 ) /* (ADC) Startup Time */
#وصف_ڪريو AT91C_ADC_SHTIM                    ( ( بنانشان صحيح ) 0xF << 24 )  /* (ADC) Sample & Hold Time */
/* --------     ADC_CHER : (ADC Offset: 0x10) ADC Channel Enable Register -------- */
#وصف_ڪريو AT91C_ADC_CH0                      ( ( بنانشان صحيح ) 0x1 << 0 )   /* (ADC) Channel 0 */
#وصف_ڪريو AT91C_ADC_CH1                      ( ( بنانشان صحيح ) 0x1 << 1 )   /* (ADC) Channel 1 */
#وصف_ڪريو AT91C_ADC_CH2                      ( ( بنانشان صحيح ) 0x1 << 2 )   /* (ADC) Channel 2 */
#وصف_ڪريو AT91C_ADC_CH3                      ( ( بنانشان صحيح ) 0x1 << 3 )   /* (ADC) Channel 3 */
#وصف_ڪريو AT91C_ADC_CH4                      ( ( بنانشان صحيح ) 0x1 << 4 )   /* (ADC) Channel 4 */
#وصف_ڪريو AT91C_ADC_CH5                      ( ( بنانشان صحيح ) 0x1 << 5 )   /* (ADC) Channel 5 */
#وصف_ڪريو AT91C_ADC_CH6                      ( ( بنانشان صحيح ) 0x1 << 6 )   /* (ADC) Channel 6 */
#وصف_ڪريو AT91C_ADC_CH7                      ( ( بنانشان صحيح ) 0x1 << 7 )   /* (ADC) Channel 7 */
/* --------     ADC_CHDR : (ADC Offset: 0x14) ADC Channel Disable Register -------- */
/* --------     ADC_CHSR : (ADC Offset: 0x18) ADC Channel Status Register -------- */
/* -------- ADC_SR : (ADC Offset: 0x1c) ADC Status Register -------- */
#وصف_ڪريو AT91C_ADC_EOC0      ( ( بنانشان صحيح ) 0x1 << 0 )   /* (ADC) End of Conversion */
#وصف_ڪريو AT91C_ADC_EOC1      ( ( بنانشان صحيح ) 0x1 << 1 )   /* (ADC) End of Conversion */
#وصف_ڪريو AT91C_ADC_EOC2      ( ( بنانشان صحيح ) 0x1 << 2 )   /* (ADC) End of Conversion */
#وصف_ڪريو AT91C_ADC_EOC3      ( ( بنانشان صحيح ) 0x1 << 3 )   /* (ADC) End of Conversion */
#وصف_ڪريو AT91C_ADC_EOC4      ( ( بنانشان صحيح ) 0x1 << 4 )   /* (ADC) End of Conversion */
#وصف_ڪريو AT91C_ADC_EOC5      ( ( بنانشان صحيح ) 0x1 << 5 )   /* (ADC) End of Conversion */
#وصف_ڪريو AT91C_ADC_EOC6      ( ( بنانشان صحيح ) 0x1 << 6 )   /* (ADC) End of Conversion */
#وصف_ڪريو AT91C_ADC_EOC7      ( ( بنانشان صحيح ) 0x1 << 7 )   /* (ADC) End of Conversion */
#وصف_ڪريو AT91C_ADC_OVRE0     ( ( بنانشان صحيح ) 0x1 << 8 )   /* (ADC) Overrun Error */
#وصف_ڪريو AT91C_ADC_OVRE1     ( ( بنانشان صحيح ) 0x1 << 9 )   /* (ADC) Overrun Error */
#وصف_ڪريو AT91C_ADC_OVRE2     ( ( بنانشان صحيح ) 0x1 << 10 )  /* (ADC) Overrun Error */
#وصف_ڪريو AT91C_ADC_OVRE3     ( ( بنانشان صحيح ) 0x1 << 11 )  /* (ADC) Overrun Error */
#وصف_ڪريو AT91C_ADC_OVRE4     ( ( بنانشان صحيح ) 0x1 << 12 )  /* (ADC) Overrun Error */
#وصف_ڪريو AT91C_ADC_OVRE5     ( ( بنانشان صحيح ) 0x1 << 13 )  /* (ADC) Overrun Error */
#وصف_ڪريو AT91C_ADC_OVRE6     ( ( بنانشان صحيح ) 0x1 << 14 )  /* (ADC) Overrun Error */
#وصف_ڪريو AT91C_ADC_OVRE7     ( ( بنانشان صحيح ) 0x1 << 15 )  /* (ADC) Overrun Error */
#وصف_ڪريو AT91C_ADC_DRDY      ( ( بنانشان صحيح ) 0x1 << 16 )  /* (ADC) Data Ready */
#وصف_ڪريو AT91C_ADC_GOVRE     ( ( بنانشان صحيح ) 0x1 << 17 )  /* (ADC) General Overrun */
#وصف_ڪريو AT91C_ADC_ENDRX     ( ( بنانشان صحيح ) 0x1 << 18 )  /* (ADC) End of Receiver Transfer */
#وصف_ڪريو AT91C_ADC_RXBUFF    ( ( بنانشان صحيح ) 0x1 << 19 )  /* (ADC) RXBUFF Interrupt */
/* -------- ADC_LCDR : (ADC Offset: 0x20) ADC Last Converted Data Register -------- */
#وصف_ڪريو AT91C_ADC_LDATA     ( ( بنانشان صحيح ) 0x3FF << 0 ) /* (ADC) Last Data Converted */
/* -------- ADC_IER : (ADC Offset: 0x24) ADC Interrupt Enable Register -------- */
/* -------- ADC_IDR : (ADC Offset: 0x28) ADC Interrupt Disable Register -------- */
/* -------- ADC_IMR : (ADC Offset: 0x2c) ADC Interrupt Mask Register -------- */
/* -------- ADC_CDR0 : (ADC Offset: 0x30) ADC Channel Data Register 0 -------- */
#وصف_ڪريو AT91_C_ADC_معلومات    ( ( بنانشان صحيح ) 0x3FF << 0 )  /* (ADC) Converted Data */
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
تعريفنوع بنية _AT91S_AES
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
#وصف_ڪريو AT91_C_AES_شروعات                 ( ( بنانشان صحيح ) 0x1 << 0 )   /* (AES) Starts Processing */
#وصف_ڪريو AT91C_AES_SWRST                 ( ( بنانشان صحيح ) 0x1 << 8 )   /* (AES) Software Reset */
#وصف_ڪريو AT91C_AES_LOADSEED              ( ( بنانشان صحيح ) 0x1 << 16 )  /* (AES) Random Number Generator Seed Loading */
/* -------- AES_MR : (AES Offset: 0x4) Mode Register -------- */
#وصف_ڪريو AT91C_AES_CIPHER                ( ( بنانشان صحيح ) 0x1 << 0 )   /* (AES) Processing Mode */
#وصف_ڪريو AT91C_AES_PROCDLY               ( ( بنانشان صحيح ) 0xF << 4 )   /* (AES) Processing Delay */
#وصف_ڪريو AT91C_AES_SMOD                  ( ( بنانشان صحيح ) 0x3 << 8 )   /* (AES) Start Mode */
#وصف_ڪريو     AT91C_AES_SMOD_MANUAL       ( ( بنانشان صحيح ) 0x0 << 8 )   /* (AES) Manual Mode: The START bit in register AES_CR must be set to begin encryption or decryption. */
#وصف_ڪريو     AT91C_AES_SMOD_AUTO         ( ( بنانشان صحيح ) 0x1 << 8 )   /* (AES) Auto Mode: no action in AES_CR is necessary (cf datasheet). */
#وصف_ڪريو     AT91C_AES_SMOD_PDC          ( ( بنانشان صحيح ) 0x2 << 8 )   /* (AES) PDC Mode (cf datasheet). */
#وصف_ڪريو AT91C_AES_OPMOD                 ( ( بنانشان صحيح ) 0x7 << 12 )  /* (AES) Operation Mode */
#وصف_ڪريو     AT91C_AES_OPMOD_ECB         ( ( بنانشان صحيح ) 0x0 << 12 )  /* (AES) ECB Electronic CodeBook mode. */
#وصف_ڪريو     AT91C_AES_OPMOD_CBC         ( ( بنانشان صحيح ) 0x1 << 12 )  /* (AES) CBC Cipher Block Chaining mode. */
#وصف_ڪريو     AT91C_AES_OPMOD_OFB         ( ( بنانشان صحيح ) 0x2 << 12 )  /* (AES) OFB Output Feedback mode. */
#وصف_ڪريو     AT91C_AES_OPMOD_CFB         ( ( بنانشان صحيح ) 0x3 << 12 )  /* (AES) CFB Cipher Feedback mode. */
#وصف_ڪريو     AT91C_AES_OPMOD_CTR         ( ( بنانشان صحيح ) 0x4 << 12 )  /* (AES) CTR Counter mode. */
#وصف_ڪريو AT91C_AES_LOD                   ( ( بنانشان صحيح ) 0x1 << 15 )  /* (AES) Last Output Data Mode */
#وصف_ڪريو AT91C_AES_CFBS                  ( ( بنانشان صحيح ) 0x7 << 16 )  /* (AES) Cipher Feedback Data Size */
#وصف_ڪريو     AT91_C_AES_CFBS_128_ٻٽو_انگ      ( ( بنانشان صحيح ) 0x0 << 16 )  /* (AES) 128-bit. */
#وصف_ڪريو     AT91_C_AES_CFBS_64_ٻٽو_انگ       ( ( بنانشان صحيح ) 0x1 << 16 )  /* (AES) 64-bit. */
#وصف_ڪريو     AT91_C_AES_CFBS_32_ٻٽو_انگ       ( ( بنانشان صحيح ) 0x2 << 16 )  /* (AES) 32-bit. */
#وصف_ڪريو     AT91_C_AES_CFBS_16_ٻٽو_انگ       ( ( بنانشان صحيح ) 0x3 << 16 )  /* (AES) 16-bit. */
#وصف_ڪريو     AT91_C_AES_CFBS_8_ٻٽو_انگ        ( ( بنانشان صحيح ) 0x4 << 16 )  /* (AES) 8-bit. */
#وصف_ڪريو AT91C_AES_CKEY                  ( ( بنانشان صحيح ) 0xF << 20 )  /* (AES) Countermeasure Key */
#وصف_ڪريو AT91C_AES_CTYPE                 ( ( بنانشان صحيح ) 0x1F << 24 ) /* (AES) Countermeasure Type */
#وصف_ڪريو     AT91C_AES_CTYPE_TYPE1_EN    ( ( بنانشان صحيح ) 0x1 << 24 )  /* (AES) Countermeasure type 1 is enabled. */
#وصف_ڪريو     AT91C_AES_CTYPE_TYPE2_EN    ( ( بنانشان صحيح ) 0x2 << 24 )  /* (AES) Countermeasure type 2 is enabled. */
#وصف_ڪريو     AT91C_AES_CTYPE_TYPE3_EN    ( ( بنانشان صحيح ) 0x4 << 24 )  /* (AES) Countermeasure type 3 is enabled. */
#وصف_ڪريو     AT91C_AES_CTYPE_TYPE4_EN    ( ( بنانشان صحيح ) 0x8 << 24 )  /* (AES) Countermeasure type 4 is enabled. */
#وصف_ڪريو     AT91C_AES_CTYPE_TYPE5_EN    ( ( بنانشان صحيح ) 0x10 << 24 ) /* (AES) Countermeasure type 5 is enabled. */
/* -------- AES_IER : (AES Offset: 0x10) Interrupt Enable Register -------- */
#وصف_ڪريو AT91C_AES_DATRDY                ( ( بنانشان صحيح ) 0x1 << 0 )   /* (AES) DATRDY */
#وصف_ڪريو AT91C_AES_ENDRX                 ( ( بنانشان صحيح ) 0x1 << 1 )   /* (AES) PDC Read Buffer End */
#وصف_ڪريو AT91C_AES_ENDTX                 ( ( بنانشان صحيح ) 0x1 << 2 )   /* (AES) PDC Write Buffer End */
#وصف_ڪريو AT91C_AES_RXBUFF                ( ( بنانشان صحيح ) 0x1 << 3 )   /* (AES) PDC Read Buffer Full */
#وصف_ڪريو AT91C_AES_TXBUFE                ( ( بنانشان صحيح ) 0x1 << 4 )   /* (AES) PDC Write Buffer Empty */
#وصف_ڪريو AT91C_AES_URAD                  ( ( بنانشان صحيح ) 0x1 << 8 )   /* (AES) Unspecified Register Access Detection */
/* -------- AES_IDR : (AES Offset: 0x14) Interrupt Disable Register -------- */
/* -------- AES_IMR : (AES Offset: 0x18) Interrupt Mask Register -------- */
/* -------- AES_ISR : (AES Offset: 0x1c) Interrupt Status Register -------- */
#وصف_ڪريو AT91C_AES_URAT                              ( ( بنانشان صحيح ) 0x7 << 12 ) /* (AES) Unspecified Register Access Type Status */
#وصف_ڪريو     AT91_C_AES_URAT_اندريون_DAT_WRITE_DATPROC     ( ( بنانشان صحيح ) 0x0 << 12 ) /* (AES) Input data register written during the data processing in PDC mode. */
#وصف_ڪريو     AT91_C_AES_URAT_ٻاهريون_DAT_READ_DATPROC     ( ( بنانشان صحيح ) 0x1 << 12 ) /* (AES) Output data register read during the data processing. */
#وصف_ڪريو     AT91C_AES_URAT_MODEREG_WRITE_DATPROC    ( ( بنانشان صحيح ) 0x2 << 12 ) /* (AES) Mode register written during the data processing. */
#وصف_ڪريو     AT91_C_AES_URAT_ٻاهريون_DAT_READ_SUBKEY      ( ( بنانشان صحيح ) 0x3 << 12 ) /* (AES) Output data register read during the sub-keys generation. */
#وصف_ڪريو     AT91C_AES_URAT_MODEREG_WRITE_SUBKEY     ( ( بنانشان صحيح ) 0x4 << 12 ) /* (AES) Mode register written during the sub-keys generation. */
#وصف_ڪريو     AT91C_AES_URAT_WO_REG_READ              ( ( بنانشان صحيح ) 0x5 << 12 ) /* (AES) Write-only register read access. */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Triple Data Encryption Standard */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_TDES
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
#وصف_ڪريو AT91_C_TDES_شروعات              ( ( بنانشان صحيح ) 0x1 << 0 )  /* (TDES) Starts Processing */
#وصف_ڪريو AT91C_TDES_SWRST              ( ( بنانشان صحيح ) 0x1 << 8 )  /* (TDES) Software Reset */
/* -------- TDES_MR : (TDES Offset: 0x4) Mode Register -------- */
#وصف_ڪريو AT91C_TDES_CIPHER             ( ( بنانشان صحيح ) 0x1 << 0 )  /* (TDES) Processing Mode */
#وصف_ڪريو AT91C_TDES_TDESMOD            ( ( بنانشان صحيح ) 0x1 << 1 )  /* (TDES) Single or Triple DES Mode */
#وصف_ڪريو AT91C_TDES_KEYMOD             ( ( بنانشان صحيح ) 0x1 << 4 )  /* (TDES) Key Mode */
#وصف_ڪريو AT91C_TDES_SMOD               ( ( بنانشان صحيح ) 0x3 << 8 )  /* (TDES) Start Mode */
#وصف_ڪريو     AT91C_TDES_SMOD_MANUAL    ( ( بنانشان صحيح ) 0x0 << 8 )  /* (TDES) Manual Mode: The START bit in register TDES_CR must be set to begin encryption or decryption. */
#وصف_ڪريو     AT91C_TDES_SMOD_AUTO      ( ( بنانشان صحيح ) 0x1 << 8 )  /* (TDES) Auto Mode: no action in TDES_CR is necessary (cf datasheet). */
#وصف_ڪريو     AT91C_TDES_SMOD_PDC       ( ( بنانشان صحيح ) 0x2 << 8 )  /* (TDES) PDC Mode (cf datasheet). */
#وصف_ڪريو AT91C_TDES_OPMOD              ( ( بنانشان صحيح ) 0x3 << 12 ) /* (TDES) Operation Mode */
#وصف_ڪريو     AT91C_TDES_OPMOD_ECB      ( ( بنانشان صحيح ) 0x0 << 12 ) /* (TDES) ECB Electronic CodeBook mode. */
#وصف_ڪريو     AT91C_TDES_OPMOD_CBC      ( ( بنانشان صحيح ) 0x1 << 12 ) /* (TDES) CBC Cipher Block Chaining mode. */
#وصف_ڪريو     AT91C_TDES_OPMOD_OFB      ( ( بنانشان صحيح ) 0x2 << 12 ) /* (TDES) OFB Output Feedback mode. */
#وصف_ڪريو     AT91C_TDES_OPMOD_CFB      ( ( بنانشان صحيح ) 0x3 << 12 ) /* (TDES) CFB Cipher Feedback mode. */
#وصف_ڪريو AT91C_TDES_LOD                ( ( بنانشان صحيح ) 0x1 << 15 ) /* (TDES) Last Output Data Mode */
#وصف_ڪريو AT91C_TDES_CFBS               ( ( بنانشان صحيح ) 0x3 << 16 ) /* (TDES) Cipher Feedback Data Size */
#وصف_ڪريو     AT91_C_TDES_CFBS_64_ٻٽو_انگ    ( ( بنانشان صحيح ) 0x0 << 16 ) /* (TDES) 64-bit. */
#وصف_ڪريو     AT91_C_TDES_CFBS_32_ٻٽو_انگ    ( ( بنانشان صحيح ) 0x1 << 16 ) /* (TDES) 32-bit. */
#وصف_ڪريو     AT91_C_TDES_CFBS_16_ٻٽو_انگ    ( ( بنانشان صحيح ) 0x2 << 16 ) /* (TDES) 16-bit. */
#وصف_ڪريو     AT91_C_TDES_CFBS_8_ٻٽو_انگ     ( ( بنانشان صحيح ) 0x3 << 16 ) /* (TDES) 8-bit. */
/* -------- TDES_IER : (TDES Offset: 0x10) Interrupt Enable Register -------- */
#وصف_ڪريو AT91C_TDES_DATRDY             ( ( بنانشان صحيح ) 0x1 << 0 )  /* (TDES) DATRDY */
#وصف_ڪريو AT91C_TDES_ENDRX              ( ( بنانشان صحيح ) 0x1 << 1 )  /* (TDES) PDC Read Buffer End */
#وصف_ڪريو AT91C_TDES_ENDTX              ( ( بنانشان صحيح ) 0x1 << 2 )  /* (TDES) PDC Write Buffer End */
#وصف_ڪريو AT91C_TDES_RXBUFF             ( ( بنانشان صحيح ) 0x1 << 3 )  /* (TDES) PDC Read Buffer Full */
#وصف_ڪريو AT91C_TDES_TXBUFE             ( ( بنانشان صحيح ) 0x1 << 4 )  /* (TDES) PDC Write Buffer Empty */
#وصف_ڪريو AT91C_TDES_URAD               ( ( بنانشان صحيح ) 0x1 << 8 )  /* (TDES) Unspecified Register Access Detection */
/* -------- TDES_IDR : (TDES Offset: 0x14) Interrupt Disable Register -------- */
/* -------- TDES_IMR : (TDES Offset: 0x18) Interrupt Mask Register -------- */
/* -------- TDES_ISR : (TDES Offset: 0x1c) Interrupt Status Register -------- */
#وصف_ڪريو AT91C_TDES_URAT                              ( ( بنانشان صحيح ) 0x3 << 12 ) /* (TDES) Unspecified Register Access Type Status */
#وصف_ڪريو     AT91_C_TDES_URAT_اندريون_DAT_WRITE_DATPROC     ( ( بنانشان صحيح ) 0x0 << 12 ) /* (TDES) Input data register written during the data processing in PDC mode. */
#وصف_ڪريو     AT91_C_TDES_URAT_ٻاهريون_DAT_READ_DATPROC     ( ( بنانشان صحيح ) 0x1 << 12 ) /* (TDES) Output data register read during the data processing. */
#وصف_ڪريو     AT91C_TDES_URAT_MODEREG_WRITE_DATPROC    ( ( بنانشان صحيح ) 0x2 << 12 ) /* (TDES) Mode register written during the data processing. */
#وصف_ڪريو     AT91C_TDES_URAT_WO_REG_READ              ( ( بنانشان صحيح ) 0x3 << 12 ) /* (TDES) Write-only register read access. */

/* ***************************************************************************** */
/*               REGISTER ADDRESS DEFINITION FOR AT91SAM7X256 */
/* ***************************************************************************** */
/* ========== Register definition for SYS peripheral ========== */
/* ========== Register definition for AIC peripheral ========== */
#وصف_ڪريو AT91C_AIC_IVR              ( ( AT91_REG * ) 0xFFFFF100 ) /* (AIC) IRQ Vector Register */
#وصف_ڪريو AT91C_AIC_SMR              ( ( AT91_REG * ) 0xFFFFF000 ) /* (AIC) Source Mode Register */
#وصف_ڪريو AT91C_AIC_FVR              ( ( AT91_REG * ) 0xFFFFF104 ) /* (AIC) FIQ Vector Register */
#وصف_ڪريو AT91C_AIC_DCR              ( ( AT91_REG * ) 0xFFFFF138 ) /* (AIC) Debug Control Register (Protect) */
#وصف_ڪريو AT91C_AIC_EOICR            ( ( AT91_REG * ) 0xFFFFF130 ) /* (AIC) End of Interrupt Command Register */
#وصف_ڪريو AT91C_AIC_SVR              ( ( AT91_REG * ) 0xFFFFF080 ) /* (AIC) Source Vector Register */
#وصف_ڪريو AT91C_AIC_FFSR             ( ( AT91_REG * ) 0xFFFFF148 ) /* (AIC) Fast Forcing Status Register */
#وصف_ڪريو AT91C_AIC_ICCR             ( ( AT91_REG * ) 0xFFFFF128 ) /* (AIC) Interrupt Clear Command Register */
#وصف_ڪريو AT91C_AIC_ISR              ( ( AT91_REG * ) 0xFFFFF108 ) /* (AIC) Interrupt Status Register */
#وصف_ڪريو AT91C_AIC_IMR              ( ( AT91_REG * ) 0xFFFFF110 ) /* (AIC) Interrupt Mask Register */
#وصف_ڪريو AT91C_AIC_IPR              ( ( AT91_REG * ) 0xFFFFF10C ) /* (AIC) Interrupt Pending Register */
#وصف_ڪريو AT91C_AIC_FFER             ( ( AT91_REG * ) 0xFFFFF140 ) /* (AIC) Fast Forcing Enable Register */
#وصف_ڪريو AT91C_AIC_IECR             ( ( AT91_REG * ) 0xFFFFF120 ) /* (AIC) Interrupt Enable Command Register */
#وصف_ڪريو AT91C_AIC_ISCR             ( ( AT91_REG * ) 0xFFFFF12C ) /* (AIC) Interrupt Set Command Register */
#وصف_ڪريو AT91C_AIC_FFDR             ( ( AT91_REG * ) 0xFFFFF144 ) /* (AIC) Fast Forcing Disable Register */
#وصف_ڪريو AT91C_AIC_CISR             ( ( AT91_REG * ) 0xFFFFF114 ) /* (AIC) Core Interrupt Status Register */
#وصف_ڪريو AT91C_AIC_IDCR             ( ( AT91_REG * ) 0xFFFFF124 ) /* (AIC) Interrupt Disable Command Register */
#وصف_ڪريو AT91C_AIC_SPU              ( ( AT91_REG * ) 0xFFFFF134 ) /* (AIC) Spurious Vector Register */
/* ========== Register definition for PDC_DBGU peripheral ========== */
#وصف_ڪريو AT91C_DBGU_TCR             ( ( AT91_REG * ) 0xFFFFF30C ) /* (PDC_DBGU) Transmit Counter Register */
#وصف_ڪريو AT91C_DBGU_RNPR            ( ( AT91_REG * ) 0xFFFFF310 ) /* (PDC_DBGU) Receive Next Pointer Register */
#وصف_ڪريو AT91C_DBGU_TNPR            ( ( AT91_REG * ) 0xFFFFF318 ) /* (PDC_DBGU) Transmit Next Pointer Register */
#وصف_ڪريو AT91C_DBGU_TPR             ( ( AT91_REG * ) 0xFFFFF308 ) /* (PDC_DBGU) Transmit Pointer Register */
#وصف_ڪريو AT91C_DBGU_RPR             ( ( AT91_REG * ) 0xFFFFF300 ) /* (PDC_DBGU) Receive Pointer Register */
#وصف_ڪريو AT91C_DBGU_RCR             ( ( AT91_REG * ) 0xFFFFF304 ) /* (PDC_DBGU) Receive Counter Register */
#وصف_ڪريو AT91C_DBGU_RNCR            ( ( AT91_REG * ) 0xFFFFF314 ) /* (PDC_DBGU) Receive Next Counter Register */
#وصف_ڪريو AT91C_DBGU_PTCR            ( ( AT91_REG * ) 0xFFFFF320 ) /* (PDC_DBGU) PDC Transfer Control Register */
#وصف_ڪريو AT91C_DBGU_PTSR            ( ( AT91_REG * ) 0xFFFFF324 ) /* (PDC_DBGU) PDC Transfer Status Register */
#وصف_ڪريو AT91C_DBGU_TNCR            ( ( AT91_REG * ) 0xFFFFF31C ) /* (PDC_DBGU) Transmit Next Counter Register */
/* ========== Register definition for DBGU peripheral ========== */
#وصف_ڪريو AT91C_DBGU_EXID            ( ( AT91_REG * ) 0xFFFFF244 ) /* (DBGU) Chip ID Extension Register */
#وصف_ڪريو AT91C_DBGU_BRGR            ( ( AT91_REG * ) 0xFFFFF220 ) /* (DBGU) Baud Rate Generator Register */
#وصف_ڪريو AT91C_DBGU_IDR             ( ( AT91_REG * ) 0xFFFFF20C ) /* (DBGU) Interrupt Disable Register */
#وصف_ڪريو AT91C_DBGU_CSR             ( ( AT91_REG * ) 0xFFFFF214 ) /* (DBGU) Channel Status Register */
#وصف_ڪريو AT91C_DBGU_CIDR            ( ( AT91_REG * ) 0xFFFFF240 ) /* (DBGU) Chip ID Register */
#وصف_ڪريو AT91C_DBGU_MR              ( ( AT91_REG * ) 0xFFFFF204 ) /* (DBGU) Mode Register */
#وصف_ڪريو AT91C_DBGU_IMR             ( ( AT91_REG * ) 0xFFFFF210 ) /* (DBGU) Interrupt Mask Register */
#وصف_ڪريو AT91C_DBGU_CR              ( ( AT91_REG * ) 0xFFFFF200 ) /* (DBGU) Control Register */
#وصف_ڪريو AT91C_DBGU_FNTR            ( ( AT91_REG * ) 0xFFFFF248 ) /* (DBGU) Force NTRST Register */
#وصف_ڪريو AT91C_DBGU_THR             ( ( AT91_REG * ) 0xFFFFF21C ) /* (DBGU) Transmitter Holding Register */
#وصف_ڪريو AT91C_DBGU_RHR             ( ( AT91_REG * ) 0xFFFFF218 ) /* (DBGU) Receiver Holding Register */
#وصف_ڪريو AT91C_DBGU_IER             ( ( AT91_REG * ) 0xFFFFF208 ) /* (DBGU) Interrupt Enable Register */
/* ========== Register definition for PIOA peripheral ========== */
#وصف_ڪريو AT91C_PIOA_ODR             ( ( AT91_REG * ) 0xFFFFF414 ) /* (PIOA) Output Disable Registerr */
#وصف_ڪريو AT91C_PIOA_SODR            ( ( AT91_REG * ) 0xFFFFF430 ) /* (PIOA) Set Output Data Register */
#وصف_ڪريو AT91C_PIOA_ISR             ( ( AT91_REG * ) 0xFFFFF44C ) /* (PIOA) Interrupt Status Register */
#وصف_ڪريو AT91C_PIOA_ABSR            ( ( AT91_REG * ) 0xFFFFF478 ) /* (PIOA) AB Select Status Register */
#وصف_ڪريو AT91C_PIOA_IER             ( ( AT91_REG * ) 0xFFFFF440 ) /* (PIOA) Interrupt Enable Register */
#وصف_ڪريو AT91C_PIOA_PPUDR           ( ( AT91_REG * ) 0xFFFFF460 ) /* (PIOA) Pull-up Disable Register */
#وصف_ڪريو AT91C_PIOA_IMR             ( ( AT91_REG * ) 0xFFFFF448 ) /* (PIOA) Interrupt Mask Register */
#وصف_ڪريو AT91_C_PIOA_في             ( ( AT91_REG * ) 0xFFFFF400 ) /* (PIOA) PIO Enable Register */
#وصف_ڪريو AT91C_PIOA_IFDR            ( ( AT91_REG * ) 0xFFFFF424 ) /* (PIOA) Input Filter Disable Register */
#وصف_ڪريو AT91C_PIOA_OWDR            ( ( AT91_REG * ) 0xFFFFF4A4 ) /* (PIOA) Output Write Disable Register */
#وصف_ڪريو AT91C_PIOA_MDSR            ( ( AT91_REG * ) 0xFFFFF458 ) /* (PIOA) Multi-driver Status Register */
#وصف_ڪريو AT91C_PIOA_IDR             ( ( AT91_REG * ) 0xFFFFF444 ) /* (PIOA) Interrupt Disable Register */
#وصف_ڪريو AT91C_PIOA_ODSR            ( ( AT91_REG * ) 0xFFFFF438 ) /* (PIOA) Output Data Status Register */
#وصف_ڪريو AT91C_PIOA_PPUSR           ( ( AT91_REG * ) 0xFFFFF468 ) /* (PIOA) Pull-up Status Register */
#وصف_ڪريو AT91C_PIOA_OWSR            ( ( AT91_REG * ) 0xFFFFF4A8 ) /* (PIOA) Output Write Status Register */
#وصف_ڪريو AT91C_PIOA_BSR             ( ( AT91_REG * ) 0xFFFFF474 ) /* (PIOA) Select B Register */
#وصف_ڪريو AT91C_PIOA_OWER            ( ( AT91_REG * ) 0xFFFFF4A0 ) /* (PIOA) Output Write Enable Register */
#وصف_ڪريو AT91C_PIOA_IFER            ( ( AT91_REG * ) 0xFFFFF420 ) /* (PIOA) Input Filter Enable Register */
#وصف_ڪريو AT91C_PIOA_PDSR            ( ( AT91_REG * ) 0xFFFFF43C ) /* (PIOA) Pin Data Status Register */
#وصف_ڪريو AT91C_PIOA_PPUER           ( ( AT91_REG * ) 0xFFFFF464 ) /* (PIOA) Pull-up Enable Register */
#وصف_ڪريو AT91C_PIOA_OSR             ( ( AT91_REG * ) 0xFFFFF418 ) /* (PIOA) Output Status Register */
#وصف_ڪريو AT91C_PIOA_ASR             ( ( AT91_REG * ) 0xFFFFF470 ) /* (PIOA) Select A Register */
#وصف_ڪريو AT91C_PIOA_MDDR            ( ( AT91_REG * ) 0xFFFFF454 ) /* (PIOA) Multi-driver Disable Register */
#وصف_ڪريو AT91C_PIOA_CODR            ( ( AT91_REG * ) 0xFFFFF434 ) /* (PIOA) Clear Output Data Register */
#وصف_ڪريو AT91C_PIOA_MDER            ( ( AT91_REG * ) 0xFFFFF450 ) /* (PIOA) Multi-driver Enable Register */
#وصف_ڪريو AT91C_PIOA_PDR             ( ( AT91_REG * ) 0xFFFFF404 ) /* (PIOA) PIO Disable Register */
#وصف_ڪريو AT91C_PIOA_IFSR            ( ( AT91_REG * ) 0xFFFFF428 ) /* (PIOA) Input Filter Status Register */
#وصف_ڪريو AT91C_PIOA_OER             ( ( AT91_REG * ) 0xFFFFF410 ) /* (PIOA) Output Enable Register */
#وصف_ڪريو AT91C_PIOA_PSR             ( ( AT91_REG * ) 0xFFFFF408 ) /* (PIOA) PIO Status Register */
/* ========== Register definition for PIOB peripheral ========== */
#وصف_ڪريو AT91C_PIOB_OWDR            ( ( AT91_REG * ) 0xFFFFF6A4 ) /* (PIOB) Output Write Disable Register */
#وصف_ڪريو AT91C_PIOB_MDER            ( ( AT91_REG * ) 0xFFFFF650 ) /* (PIOB) Multi-driver Enable Register */
#وصف_ڪريو AT91C_PIOB_PPUSR           ( ( AT91_REG * ) 0xFFFFF668 ) /* (PIOB) Pull-up Status Register */
#وصف_ڪريو AT91C_PIOB_IMR             ( ( AT91_REG * ) 0xFFFFF648 ) /* (PIOB) Interrupt Mask Register */
#وصف_ڪريو AT91C_PIOB_ASR             ( ( AT91_REG * ) 0xFFFFF670 ) /* (PIOB) Select A Register */
#وصف_ڪريو AT91C_PIOB_PPUDR           ( ( AT91_REG * ) 0xFFFFF660 ) /* (PIOB) Pull-up Disable Register */
#وصف_ڪريو AT91C_PIOB_PSR             ( ( AT91_REG * ) 0xFFFFF608 ) /* (PIOB) PIO Status Register */
#وصف_ڪريو AT91C_PIOB_IER             ( ( AT91_REG * ) 0xFFFFF640 ) /* (PIOB) Interrupt Enable Register */
#وصف_ڪريو AT91C_PIOB_CODR            ( ( AT91_REG * ) 0xFFFFF634 ) /* (PIOB) Clear Output Data Register */
#وصف_ڪريو AT91C_PIOB_OWER            ( ( AT91_REG * ) 0xFFFFF6A0 ) /* (PIOB) Output Write Enable Register */
#وصف_ڪريو AT91C_PIOB_ABSR            ( ( AT91_REG * ) 0xFFFFF678 ) /* (PIOB) AB Select Status Register */
#وصف_ڪريو AT91C_PIOB_IFDR            ( ( AT91_REG * ) 0xFFFFF624 ) /* (PIOB) Input Filter Disable Register */
#وصف_ڪريو AT91C_PIOB_PDSR            ( ( AT91_REG * ) 0xFFFFF63C ) /* (PIOB) Pin Data Status Register */
#وصف_ڪريو AT91C_PIOB_IDR             ( ( AT91_REG * ) 0xFFFFF644 ) /* (PIOB) Interrupt Disable Register */
#وصف_ڪريو AT91C_PIOB_OWSR            ( ( AT91_REG * ) 0xFFFFF6A8 ) /* (PIOB) Output Write Status Register */
#وصف_ڪريو AT91C_PIOB_PDR             ( ( AT91_REG * ) 0xFFFFF604 ) /* (PIOB) PIO Disable Register */
#وصف_ڪريو AT91C_PIOB_ODR             ( ( AT91_REG * ) 0xFFFFF614 ) /* (PIOB) Output Disable Registerr */
#وصف_ڪريو AT91C_PIOB_IFSR            ( ( AT91_REG * ) 0xFFFFF628 ) /* (PIOB) Input Filter Status Register */
#وصف_ڪريو AT91C_PIOB_PPUER           ( ( AT91_REG * ) 0xFFFFF664 ) /* (PIOB) Pull-up Enable Register */
#وصف_ڪريو AT91C_PIOB_SODR            ( ( AT91_REG * ) 0xFFFFF630 ) /* (PIOB) Set Output Data Register */
#وصف_ڪريو AT91C_PIOB_ISR             ( ( AT91_REG * ) 0xFFFFF64C ) /* (PIOB) Interrupt Status Register */
#وصف_ڪريو AT91C_PIOB_ODSR            ( ( AT91_REG * ) 0xFFFFF638 ) /* (PIOB) Output Data Status Register */
#وصف_ڪريو AT91C_PIOB_OSR             ( ( AT91_REG * ) 0xFFFFF618 ) /* (PIOB) Output Status Register */
#وصف_ڪريو AT91C_PIOB_MDSR            ( ( AT91_REG * ) 0xFFFFF658 ) /* (PIOB) Multi-driver Status Register */
#وصف_ڪريو AT91C_PIOB_IFER            ( ( AT91_REG * ) 0xFFFFF620 ) /* (PIOB) Input Filter Enable Register */
#وصف_ڪريو AT91C_PIOB_BSR             ( ( AT91_REG * ) 0xFFFFF674 ) /* (PIOB) Select B Register */
#وصف_ڪريو AT91C_PIOB_MDDR            ( ( AT91_REG * ) 0xFFFFF654 ) /* (PIOB) Multi-driver Disable Register */
#وصف_ڪريو AT91C_PIOB_OER             ( ( AT91_REG * ) 0xFFFFF610 ) /* (PIOB) Output Enable Register */
#وصف_ڪريو AT91_C_PIOB_في             ( ( AT91_REG * ) 0xFFFFF600 ) /* (PIOB) PIO Enable Register */
/* ========== Register definition for CKGR peripheral ========== */
#وصف_ڪريو AT91C_CKGR_MOR             ( ( AT91_REG * ) 0xFFFFFC20 ) /* (CKGR) Main Oscillator Register */
#وصف_ڪريو AT91C_CKGR_PLLR            ( ( AT91_REG * ) 0xFFFFFC2C ) /* (CKGR) PLL Register */
#وصف_ڪريو AT91C_CKGR_MCFR            ( ( AT91_REG * ) 0xFFFFFC24 ) /* (CKGR) Main Clock  Frequency Register */
/* ========== Register definition for PMC peripheral ========== */
#وصف_ڪريو AT91C_PMC_IDR              ( ( AT91_REG * ) 0xFFFFFC64 ) /* (PMC) Interrupt Disable Register */
#وصف_ڪريو AT91C_PMC_MOR              ( ( AT91_REG * ) 0xFFFFFC20 ) /* (PMC) Main Oscillator Register */
#وصف_ڪريو AT91C_PMC_PLLR             ( ( AT91_REG * ) 0xFFFFFC2C ) /* (PMC) PLL Register */
#وصف_ڪريو AT91C_PMC_PCER             ( ( AT91_REG * ) 0xFFFFFC10 ) /* (PMC) Peripheral Clock Enable Register */
#وصف_ڪريو AT91C_PMC_PCKR             ( ( AT91_REG * ) 0xFFFFFC40 ) /* (PMC) Programmable Clock Register */
#وصف_ڪريو AT91C_PMC_MCKR             ( ( AT91_REG * ) 0xFFFFFC30 ) /* (PMC) Master Clock Register */
#وصف_ڪريو AT91C_PMC_SCDR             ( ( AT91_REG * ) 0xFFFFFC04 ) /* (PMC) System Clock Disable Register */
#وصف_ڪريو AT91C_PMC_PCDR             ( ( AT91_REG * ) 0xFFFFFC14 ) /* (PMC) Peripheral Clock Disable Register */
#وصف_ڪريو AT91C_PMC_SCSR             ( ( AT91_REG * ) 0xFFFFFC08 ) /* (PMC) System Clock Status Register */
#وصف_ڪريو AT91C_PMC_PCSR             ( ( AT91_REG * ) 0xFFFFFC18 ) /* (PMC) Peripheral Clock Status Register */
#وصف_ڪريو AT91C_PMC_MCFR             ( ( AT91_REG * ) 0xFFFFFC24 ) /* (PMC) Main Clock  Frequency Register */
#وصف_ڪريو AT91C_PMC_SCER             ( ( AT91_REG * ) 0xFFFFFC00 ) /* (PMC) System Clock Enable Register */
#وصف_ڪريو AT91C_PMC_IMR              ( ( AT91_REG * ) 0xFFFFFC6C ) /* (PMC) Interrupt Mask Register */
#وصف_ڪريو AT91C_PMC_IER              ( ( AT91_REG * ) 0xFFFFFC60 ) /* (PMC) Interrupt Enable Register */
#وصف_ڪريو AT91C_PMC_SR               ( ( AT91_REG * ) 0xFFFFFC68 ) /* (PMC) Status Register */
/* ========== Register definition for RSTC peripheral ========== */
#وصف_ڪريو AT91C_RSTC_RCR             ( ( AT91_REG * ) 0xFFFFFD00 ) /* (RSTC) Reset Control Register */
#وصف_ڪريو AT91C_RSTC_RMR             ( ( AT91_REG * ) 0xFFFFFD08 ) /* (RSTC) Reset Mode Register */
#وصف_ڪريو AT91C_RSTC_RSR             ( ( AT91_REG * ) 0xFFFFFD04 ) /* (RSTC) Reset Status Register */
/* ========== Register definition for RTTC peripheral ========== */
#وصف_ڪريو AT91C_RTTC_RTSR            ( ( AT91_REG * ) 0xFFFFFD2C ) /* (RTTC) Real-time Status Register */
#وصف_ڪريو AT91C_RTTC_RTMR            ( ( AT91_REG * ) 0xFFFFFD20 ) /* (RTTC) Real-time Mode Register */
#وصف_ڪريو AT91C_RTTC_RTVR            ( ( AT91_REG * ) 0xFFFFFD28 ) /* (RTTC) Real-time Value Register */
#وصف_ڪريو AT91C_RTTC_RTAR            ( ( AT91_REG * ) 0xFFFFFD24 ) /* (RTTC) Real-time Alarm Register */
/* ========== Register definition for PITC peripheral ========== */
#وصف_ڪريو AT91C_PITC_PIVR            ( ( AT91_REG * ) 0xFFFFFD38 ) /* (PITC) Period Interval Value Register */
#وصف_ڪريو AT91C_PITC_PISR            ( ( AT91_REG * ) 0xFFFFFD34 ) /* (PITC) Period Interval Status Register */
#وصف_ڪريو AT91C_PITC_PIIR            ( ( AT91_REG * ) 0xFFFFFD3C ) /* (PITC) Period Interval Image Register */
#وصف_ڪريو AT91C_PITC_PIMR            ( ( AT91_REG * ) 0xFFFFFD30 ) /* (PITC) Period Interval Mode Register */
/* ========== Register definition for WDTC peripheral ========== */
#وصف_ڪريو AT91C_WDTC_WDCR            ( ( AT91_REG * ) 0xFFFFFD40 ) /* (WDTC) Watchdog Control Register */
#وصف_ڪريو AT91C_WDTC_WDSR            ( ( AT91_REG * ) 0xFFFFFD48 ) /* (WDTC) Watchdog Status Register */
#وصف_ڪريو AT91C_WDTC_WDMR            ( ( AT91_REG * ) 0xFFFFFD44 ) /* (WDTC) Watchdog Mode Register */
/* ========== Register definition for VREG peripheral ========== */
#وصف_ڪريو AT91C_VREG_MR              ( ( AT91_REG * ) 0xFFFFFD60 ) /* (VREG) Voltage Regulator Mode Register */
/* ========== Register definition for MC peripheral ========== */
#وصف_ڪريو AT91C_MC_ASR               ( ( AT91_REG * ) 0xFFFFFF04 ) /* (MC) MC Abort Status Register */
#وصف_ڪريو AT91C_MC_RCR               ( ( AT91_REG * ) 0xFFFFFF00 ) /* (MC) MC Remap Control Register */
#وصف_ڪريو AT91C_MC_FCR               ( ( AT91_REG * ) 0xFFFFFF64 ) /* (MC) MC Flash Command Register */
#وصف_ڪريو AT91C_MC_AASR              ( ( AT91_REG * ) 0xFFFFFF08 ) /* (MC) MC Abort Address Status Register */
#وصف_ڪريو AT91C_MC_FSR               ( ( AT91_REG * ) 0xFFFFFF68 ) /* (MC) MC Flash Status Register */
#وصف_ڪريو AT91C_MC_FMR               ( ( AT91_REG * ) 0xFFFFFF60 ) /* (MC) MC Flash Mode Register */
/* ========== Register definition for PDC_SPI1 peripheral ========== */
#وصف_ڪريو AT91C_SPI1_PTCR            ( ( AT91_REG * ) 0xFFFE4120 ) /* (PDC_SPI1) PDC Transfer Control Register */
#وصف_ڪريو AT91C_SPI1_RPR             ( ( AT91_REG * ) 0xFFFE4100 ) /* (PDC_SPI1) Receive Pointer Register */
#وصف_ڪريو AT91C_SPI1_TNCR            ( ( AT91_REG * ) 0xFFFE411C ) /* (PDC_SPI1) Transmit Next Counter Register */
#وصف_ڪريو AT91C_SPI1_TPR             ( ( AT91_REG * ) 0xFFFE4108 ) /* (PDC_SPI1) Transmit Pointer Register */
#وصف_ڪريو AT91C_SPI1_TNPR            ( ( AT91_REG * ) 0xFFFE4118 ) /* (PDC_SPI1) Transmit Next Pointer Register */
#وصف_ڪريو AT91C_SPI1_TCR             ( ( AT91_REG * ) 0xFFFE410C ) /* (PDC_SPI1) Transmit Counter Register */
#وصف_ڪريو AT91C_SPI1_RCR             ( ( AT91_REG * ) 0xFFFE4104 ) /* (PDC_SPI1) Receive Counter Register */
#وصف_ڪريو AT91C_SPI1_RNPR            ( ( AT91_REG * ) 0xFFFE4110 ) /* (PDC_SPI1) Receive Next Pointer Register */
#وصف_ڪريو AT91C_SPI1_RNCR            ( ( AT91_REG * ) 0xFFFE4114 ) /* (PDC_SPI1) Receive Next Counter Register */
#وصف_ڪريو AT91C_SPI1_PTSR            ( ( AT91_REG * ) 0xFFFE4124 ) /* (PDC_SPI1) PDC Transfer Status Register */
/* ========== Register definition for SPI1 peripheral ========== */
#وصف_ڪريو AT91C_SPI1_IMR             ( ( AT91_REG * ) 0xFFFE401C ) /* (SPI1) Interrupt Mask Register */
#وصف_ڪريو AT91C_SPI1_IER             ( ( AT91_REG * ) 0xFFFE4014 ) /* (SPI1) Interrupt Enable Register */
#وصف_ڪريو AT91C_SPI1_MR              ( ( AT91_REG * ) 0xFFFE4004 ) /* (SPI1) Mode Register */
#وصف_ڪريو AT91C_SPI1_RDR             ( ( AT91_REG * ) 0xFFFE4008 ) /* (SPI1) Receive Data Register */
#وصف_ڪريو AT91C_SPI1_IDR             ( ( AT91_REG * ) 0xFFFE4018 ) /* (SPI1) Interrupt Disable Register */
#وصف_ڪريو AT91C_SPI1_SR              ( ( AT91_REG * ) 0xFFFE4010 ) /* (SPI1) Status Register */
#وصف_ڪريو AT91C_SPI1_TDR             ( ( AT91_REG * ) 0xFFFE400C ) /* (SPI1) Transmit Data Register */
#وصف_ڪريو AT91C_SPI1_CR              ( ( AT91_REG * ) 0xFFFE4000 ) /* (SPI1) Control Register */
#وصف_ڪريو AT91C_SPI1_CSR             ( ( AT91_REG * ) 0xFFFE4030 ) /* (SPI1) Chip Select Register */
/* ========== Register definition for PDC_SPI0 peripheral ========== */
#وصف_ڪريو AT91C_SPI0_PTCR            ( ( AT91_REG * ) 0xFFFE0120 ) /* (PDC_SPI0) PDC Transfer Control Register */
#وصف_ڪريو AT91C_SPI0_TPR             ( ( AT91_REG * ) 0xFFFE0108 ) /* (PDC_SPI0) Transmit Pointer Register */
#وصف_ڪريو AT91C_SPI0_TCR             ( ( AT91_REG * ) 0xFFFE010C ) /* (PDC_SPI0) Transmit Counter Register */
#وصف_ڪريو AT91C_SPI0_RCR             ( ( AT91_REG * ) 0xFFFE0104 ) /* (PDC_SPI0) Receive Counter Register */
#وصف_ڪريو AT91C_SPI0_PTSR            ( ( AT91_REG * ) 0xFFFE0124 ) /* (PDC_SPI0) PDC Transfer Status Register */
#وصف_ڪريو AT91C_SPI0_RNPR            ( ( AT91_REG * ) 0xFFFE0110 ) /* (PDC_SPI0) Receive Next Pointer Register */
#وصف_ڪريو AT91C_SPI0_RPR             ( ( AT91_REG * ) 0xFFFE0100 ) /* (PDC_SPI0) Receive Pointer Register */
#وصف_ڪريو AT91C_SPI0_TNCR            ( ( AT91_REG * ) 0xFFFE011C ) /* (PDC_SPI0) Transmit Next Counter Register */
#وصف_ڪريو AT91C_SPI0_RNCR            ( ( AT91_REG * ) 0xFFFE0114 ) /* (PDC_SPI0) Receive Next Counter Register */
#وصف_ڪريو AT91C_SPI0_TNPR            ( ( AT91_REG * ) 0xFFFE0118 ) /* (PDC_SPI0) Transmit Next Pointer Register */
/* ========== Register definition for SPI0 peripheral ========== */
#وصف_ڪريو AT91C_SPI0_IER             ( ( AT91_REG * ) 0xFFFE0014 ) /* (SPI0) Interrupt Enable Register */
#وصف_ڪريو AT91C_SPI0_SR              ( ( AT91_REG * ) 0xFFFE0010 ) /* (SPI0) Status Register */
#وصف_ڪريو AT91C_SPI0_IDR             ( ( AT91_REG * ) 0xFFFE0018 ) /* (SPI0) Interrupt Disable Register */
#وصف_ڪريو AT91C_SPI0_CR              ( ( AT91_REG * ) 0xFFFE0000 ) /* (SPI0) Control Register */
#وصف_ڪريو AT91C_SPI0_MR              ( ( AT91_REG * ) 0xFFFE0004 ) /* (SPI0) Mode Register */
#وصف_ڪريو AT91C_SPI0_IMR             ( ( AT91_REG * ) 0xFFFE001C ) /* (SPI0) Interrupt Mask Register */
#وصف_ڪريو AT91C_SPI0_TDR             ( ( AT91_REG * ) 0xFFFE000C ) /* (SPI0) Transmit Data Register */
#وصف_ڪريو AT91C_SPI0_RDR             ( ( AT91_REG * ) 0xFFFE0008 ) /* (SPI0) Receive Data Register */
#وصف_ڪريو AT91C_SPI0_CSR             ( ( AT91_REG * ) 0xFFFE0030 ) /* (SPI0) Chip Select Register */
/* ========== Register definition for PDC_US1 peripheral ========== */
#وصف_ڪريو AT91C_US1_RNCR             ( ( AT91_REG * ) 0xFFFC4114 ) /* (PDC_US1) Receive Next Counter Register */
#وصف_ڪريو AT91C_US1_PTCR             ( ( AT91_REG * ) 0xFFFC4120 ) /* (PDC_US1) PDC Transfer Control Register */
#وصف_ڪريو AT91C_US1_TCR              ( ( AT91_REG * ) 0xFFFC410C ) /* (PDC_US1) Transmit Counter Register */
#وصف_ڪريو AT91C_US1_PTSR             ( ( AT91_REG * ) 0xFFFC4124 ) /* (PDC_US1) PDC Transfer Status Register */
#وصف_ڪريو AT91C_US1_TNPR             ( ( AT91_REG * ) 0xFFFC4118 ) /* (PDC_US1) Transmit Next Pointer Register */
#وصف_ڪريو AT91C_US1_RCR              ( ( AT91_REG * ) 0xFFFC4104 ) /* (PDC_US1) Receive Counter Register */
#وصف_ڪريو AT91C_US1_RNPR             ( ( AT91_REG * ) 0xFFFC4110 ) /* (PDC_US1) Receive Next Pointer Register */
#وصف_ڪريو AT91C_US1_RPR              ( ( AT91_REG * ) 0xFFFC4100 ) /* (PDC_US1) Receive Pointer Register */
#وصف_ڪريو AT91C_US1_TNCR             ( ( AT91_REG * ) 0xFFFC411C ) /* (PDC_US1) Transmit Next Counter Register */
#وصف_ڪريو AT91C_US1_TPR              ( ( AT91_REG * ) 0xFFFC4108 ) /* (PDC_US1) Transmit Pointer Register */
/* ========== Register definition for US1 peripheral ========== */
#وصف_ڪريو AT91C_US1_IF               ( ( AT91_REG * ) 0xFFFC404C ) /* (US1) IRDA_FILTER Register */
#وصف_ڪريو AT91C_US1_NER              ( ( AT91_REG * ) 0xFFFC4044 ) /* (US1) Nb Errors Register */
#وصف_ڪريو AT91C_US1_RTOR             ( ( AT91_REG * ) 0xFFFC4024 ) /* (US1) Receiver Time-out Register */
#وصف_ڪريو AT91C_US1_CSR              ( ( AT91_REG * ) 0xFFFC4014 ) /* (US1) Channel Status Register */
#وصف_ڪريو AT91C_US1_IDR              ( ( AT91_REG * ) 0xFFFC400C ) /* (US1) Interrupt Disable Register */
#وصف_ڪريو AT91C_US1_IER              ( ( AT91_REG * ) 0xFFFC4008 ) /* (US1) Interrupt Enable Register */
#وصف_ڪريو AT91C_US1_THR              ( ( AT91_REG * ) 0xFFFC401C ) /* (US1) Transmitter Holding Register */
#وصف_ڪريو AT91C_US1_TTGR             ( ( AT91_REG * ) 0xFFFC4028 ) /* (US1) Transmitter Time-guard Register */
#وصف_ڪريو AT91C_US1_RHR              ( ( AT91_REG * ) 0xFFFC4018 ) /* (US1) Receiver Holding Register */
#وصف_ڪريو AT91C_US1_BRGR             ( ( AT91_REG * ) 0xFFFC4020 ) /* (US1) Baud Rate Generator Register */
#وصف_ڪريو AT91C_US1_IMR              ( ( AT91_REG * ) 0xFFFC4010 ) /* (US1) Interrupt Mask Register */
#وصف_ڪريو AT91C_US1_FIDI             ( ( AT91_REG * ) 0xFFFC4040 ) /* (US1) FI_DI_Ratio Register */
#وصف_ڪريو AT91C_US1_CR               ( ( AT91_REG * ) 0xFFFC4000 ) /* (US1) Control Register */
#وصف_ڪريو AT91C_US1_MR               ( ( AT91_REG * ) 0xFFFC4004 ) /* (US1) Mode Register */
/* ========== Register definition for PDC_US0 peripheral ========== */
#وصف_ڪريو AT91C_US0_TNPR             ( ( AT91_REG * ) 0xFFFC0118 ) /* (PDC_US0) Transmit Next Pointer Register */
#وصف_ڪريو AT91C_US0_RNPR             ( ( AT91_REG * ) 0xFFFC0110 ) /* (PDC_US0) Receive Next Pointer Register */
#وصف_ڪريو AT91C_US0_TCR              ( ( AT91_REG * ) 0xFFFC010C ) /* (PDC_US0) Transmit Counter Register */
#وصف_ڪريو AT91C_US0_PTCR             ( ( AT91_REG * ) 0xFFFC0120 ) /* (PDC_US0) PDC Transfer Control Register */
#وصف_ڪريو AT91C_US0_PTSR             ( ( AT91_REG * ) 0xFFFC0124 ) /* (PDC_US0) PDC Transfer Status Register */
#وصف_ڪريو AT91C_US0_TNCR             ( ( AT91_REG * ) 0xFFFC011C ) /* (PDC_US0) Transmit Next Counter Register */
#وصف_ڪريو AT91C_US0_TPR              ( ( AT91_REG * ) 0xFFFC0108 ) /* (PDC_US0) Transmit Pointer Register */
#وصف_ڪريو AT91C_US0_RCR              ( ( AT91_REG * ) 0xFFFC0104 ) /* (PDC_US0) Receive Counter Register */
#وصف_ڪريو AT91C_US0_RPR              ( ( AT91_REG * ) 0xFFFC0100 ) /* (PDC_US0) Receive Pointer Register */
#وصف_ڪريو AT91C_US0_RNCR             ( ( AT91_REG * ) 0xFFFC0114 ) /* (PDC_US0) Receive Next Counter Register */
/* ========== Register definition for US0 peripheral ========== */
#وصف_ڪريو AT91C_US0_BRGR             ( ( AT91_REG * ) 0xFFFC0020 ) /* (US0) Baud Rate Generator Register */
#وصف_ڪريو AT91C_US0_NER              ( ( AT91_REG * ) 0xFFFC0044 ) /* (US0) Nb Errors Register */
#وصف_ڪريو AT91C_US0_CR               ( ( AT91_REG * ) 0xFFFC0000 ) /* (US0) Control Register */
#وصف_ڪريو AT91C_US0_IMR              ( ( AT91_REG * ) 0xFFFC0010 ) /* (US0) Interrupt Mask Register */
#وصف_ڪريو AT91C_US0_FIDI             ( ( AT91_REG * ) 0xFFFC0040 ) /* (US0) FI_DI_Ratio Register */
#وصف_ڪريو AT91C_US0_TTGR             ( ( AT91_REG * ) 0xFFFC0028 ) /* (US0) Transmitter Time-guard Register */
#وصف_ڪريو AT91C_US0_MR               ( ( AT91_REG * ) 0xFFFC0004 ) /* (US0) Mode Register */
#وصف_ڪريو AT91C_US0_RTOR             ( ( AT91_REG * ) 0xFFFC0024 ) /* (US0) Receiver Time-out Register */
#وصف_ڪريو AT91C_US0_CSR              ( ( AT91_REG * ) 0xFFFC0014 ) /* (US0) Channel Status Register */
#وصف_ڪريو AT91C_US0_RHR              ( ( AT91_REG * ) 0xFFFC0018 ) /* (US0) Receiver Holding Register */
#وصف_ڪريو AT91C_US0_IDR              ( ( AT91_REG * ) 0xFFFC000C ) /* (US0) Interrupt Disable Register */
#وصف_ڪريو AT91C_US0_THR              ( ( AT91_REG * ) 0xFFFC001C ) /* (US0) Transmitter Holding Register */
#وصف_ڪريو AT91C_US0_IF               ( ( AT91_REG * ) 0xFFFC004C ) /* (US0) IRDA_FILTER Register */
#وصف_ڪريو AT91C_US0_IER              ( ( AT91_REG * ) 0xFFFC0008 ) /* (US0) Interrupt Enable Register */
/* ========== Register definition for PDC_SSC peripheral ========== */
#وصف_ڪريو AT91C_SSC_TNCR             ( ( AT91_REG * ) 0xFFFD411C ) /* (PDC_SSC) Transmit Next Counter Register */
#وصف_ڪريو AT91C_SSC_RPR              ( ( AT91_REG * ) 0xFFFD4100 ) /* (PDC_SSC) Receive Pointer Register */
#وصف_ڪريو AT91C_SSC_RNCR             ( ( AT91_REG * ) 0xFFFD4114 ) /* (PDC_SSC) Receive Next Counter Register */
#وصف_ڪريو AT91C_SSC_TPR              ( ( AT91_REG * ) 0xFFFD4108 ) /* (PDC_SSC) Transmit Pointer Register */
#وصف_ڪريو AT91C_SSC_PTCR             ( ( AT91_REG * ) 0xFFFD4120 ) /* (PDC_SSC) PDC Transfer Control Register */
#وصف_ڪريو AT91C_SSC_TCR              ( ( AT91_REG * ) 0xFFFD410C ) /* (PDC_SSC) Transmit Counter Register */
#وصف_ڪريو AT91C_SSC_RCR              ( ( AT91_REG * ) 0xFFFD4104 ) /* (PDC_SSC) Receive Counter Register */
#وصف_ڪريو AT91C_SSC_RNPR             ( ( AT91_REG * ) 0xFFFD4110 ) /* (PDC_SSC) Receive Next Pointer Register */
#وصف_ڪريو AT91C_SSC_TNPR             ( ( AT91_REG * ) 0xFFFD4118 ) /* (PDC_SSC) Transmit Next Pointer Register */
#وصف_ڪريو AT91C_SSC_PTSR             ( ( AT91_REG * ) 0xFFFD4124 ) /* (PDC_SSC) PDC Transfer Status Register */
/* ========== Register definition for SSC peripheral ========== */
#وصف_ڪريو AT91C_SSC_RHR              ( ( AT91_REG * ) 0xFFFD4020 ) /* (SSC) Receive Holding Register */
#وصف_ڪريو AT91C_SSC_RSHR             ( ( AT91_REG * ) 0xFFFD4030 ) /* (SSC) Receive Sync Holding Register */
#وصف_ڪريو AT91C_SSC_TFMR             ( ( AT91_REG * ) 0xFFFD401C ) /* (SSC) Transmit Frame Mode Register */
#وصف_ڪريو AT91C_SSC_IDR              ( ( AT91_REG * ) 0xFFFD4048 ) /* (SSC) Interrupt Disable Register */
#وصف_ڪريو AT91C_SSC_THR              ( ( AT91_REG * ) 0xFFFD4024 ) /* (SSC) Transmit Holding Register */
#وصف_ڪريو AT91C_SSC_RCMR             ( ( AT91_REG * ) 0xFFFD4010 ) /* (SSC) Receive Clock ModeRegister */
#وصف_ڪريو AT91C_SSC_IER              ( ( AT91_REG * ) 0xFFFD4044 ) /* (SSC) Interrupt Enable Register */
#وصف_ڪريو AT91C_SSC_TSHR             ( ( AT91_REG * ) 0xFFFD4034 ) /* (SSC) Transmit Sync Holding Register */
#وصف_ڪريو AT91C_SSC_SR               ( ( AT91_REG * ) 0xFFFD4040 ) /* (SSC) Status Register */
#وصف_ڪريو AT91C_SSC_CMR              ( ( AT91_REG * ) 0xFFFD4004 ) /* (SSC) Clock Mode Register */
#وصف_ڪريو AT91C_SSC_TCMR             ( ( AT91_REG * ) 0xFFFD4018 ) /* (SSC) Transmit Clock Mode Register */
#وصف_ڪريو AT91C_SSC_CR               ( ( AT91_REG * ) 0xFFFD4000 ) /* (SSC) Control Register */
#وصف_ڪريو AT91C_SSC_IMR              ( ( AT91_REG * ) 0xFFFD404C ) /* (SSC) Interrupt Mask Register */
#وصف_ڪريو AT91C_SSC_RFMR             ( ( AT91_REG * ) 0xFFFD4014 ) /* (SSC) Receive Frame Mode Register */
/* ========== Register definition for TWI peripheral ========== */
#وصف_ڪريو AT91C_TWI_IER              ( ( AT91_REG * ) 0xFFFB8024 ) /* (TWI) Interrupt Enable Register */
#وصف_ڪريو AT91C_TWI_CR               ( ( AT91_REG * ) 0xFFFB8000 ) /* (TWI) Control Register */
#وصف_ڪريو AT91C_TWI_SR               ( ( AT91_REG * ) 0xFFFB8020 ) /* (TWI) Status Register */
#وصف_ڪريو AT91C_TWI_IMR              ( ( AT91_REG * ) 0xFFFB802C ) /* (TWI) Interrupt Mask Register */
#وصف_ڪريو AT91C_TWI_THR              ( ( AT91_REG * ) 0xFFFB8034 ) /* (TWI) Transmit Holding Register */
#وصف_ڪريو AT91C_TWI_IDR              ( ( AT91_REG * ) 0xFFFB8028 ) /* (TWI) Interrupt Disable Register */
#وصف_ڪريو AT91C_TWI_IADR             ( ( AT91_REG * ) 0xFFFB800C ) /* (TWI) Internal Address Register */
#وصف_ڪريو AT91C_TWI_MMR              ( ( AT91_REG * ) 0xFFFB8004 ) /* (TWI) Master Mode Register */
#وصف_ڪريو AT91C_TWI_CWGR             ( ( AT91_REG * ) 0xFFFB8010 ) /* (TWI) Clock Waveform Generator Register */
#وصف_ڪريو AT91C_TWI_RHR              ( ( AT91_REG * ) 0xFFFB8030 ) /* (TWI) Receive Holding Register */
/* ========== Register definition for PWMC_CH3 peripheral ========== */
#وصف_ڪريو AT91C_PWMC_CH3_CUPDR       ( ( AT91_REG * ) 0xFFFCC270 ) /* (PWMC_CH3) Channel Update Register */
#وصف_ڪريو AT91C_PWMC_CH3_Reserved    ( ( AT91_REG * ) 0xFFFCC274 ) /* (PWMC_CH3) Reserved */
#وصف_ڪريو AT91C_PWMC_CH3_CPRDR       ( ( AT91_REG * ) 0xFFFCC268 ) /* (PWMC_CH3) Channel Period Register */
#وصف_ڪريو AT91C_PWMC_CH3_CDTYR       ( ( AT91_REG * ) 0xFFFCC264 ) /* (PWMC_CH3) Channel Duty Cycle Register */
#وصف_ڪريو AT91C_PWMC_CH3_CCNTR       ( ( AT91_REG * ) 0xFFFCC26C ) /* (PWMC_CH3) Channel Counter Register */
#وصف_ڪريو AT91C_PWMC_CH3_CMR         ( ( AT91_REG * ) 0xFFFCC260 ) /* (PWMC_CH3) Channel Mode Register */
/* ========== Register definition for PWMC_CH2 peripheral ========== */
#وصف_ڪريو AT91C_PWMC_CH2_Reserved    ( ( AT91_REG * ) 0xFFFCC254 ) /* (PWMC_CH2) Reserved */
#وصف_ڪريو AT91C_PWMC_CH2_CMR         ( ( AT91_REG * ) 0xFFFCC240 ) /* (PWMC_CH2) Channel Mode Register */
#وصف_ڪريو AT91C_PWMC_CH2_CCNTR       ( ( AT91_REG * ) 0xFFFCC24C ) /* (PWMC_CH2) Channel Counter Register */
#وصف_ڪريو AT91C_PWMC_CH2_CPRDR       ( ( AT91_REG * ) 0xFFFCC248 ) /* (PWMC_CH2) Channel Period Register */
#وصف_ڪريو AT91C_PWMC_CH2_CUPDR       ( ( AT91_REG * ) 0xFFFCC250 ) /* (PWMC_CH2) Channel Update Register */
#وصف_ڪريو AT91C_PWMC_CH2_CDTYR       ( ( AT91_REG * ) 0xFFFCC244 ) /* (PWMC_CH2) Channel Duty Cycle Register */
/* ========== Register definition for PWMC_CH1 peripheral ========== */
#وصف_ڪريو AT91C_PWMC_CH1_Reserved    ( ( AT91_REG * ) 0xFFFCC234 ) /* (PWMC_CH1) Reserved */
#وصف_ڪريو AT91C_PWMC_CH1_CUPDR       ( ( AT91_REG * ) 0xFFFCC230 ) /* (PWMC_CH1) Channel Update Register */
#وصف_ڪريو AT91C_PWMC_CH1_CPRDR       ( ( AT91_REG * ) 0xFFFCC228 ) /* (PWMC_CH1) Channel Period Register */
#وصف_ڪريو AT91C_PWMC_CH1_CCNTR       ( ( AT91_REG * ) 0xFFFCC22C ) /* (PWMC_CH1) Channel Counter Register */
#وصف_ڪريو AT91C_PWMC_CH1_CDTYR       ( ( AT91_REG * ) 0xFFFCC224 ) /* (PWMC_CH1) Channel Duty Cycle Register */
#وصف_ڪريو AT91C_PWMC_CH1_CMR         ( ( AT91_REG * ) 0xFFFCC220 ) /* (PWMC_CH1) Channel Mode Register */
/* ========== Register definition for PWMC_CH0 peripheral ========== */
#وصف_ڪريو AT91C_PWMC_CH0_Reserved    ( ( AT91_REG * ) 0xFFFCC214 ) /* (PWMC_CH0) Reserved */
#وصف_ڪريو AT91C_PWMC_CH0_CPRDR       ( ( AT91_REG * ) 0xFFFCC208 ) /* (PWMC_CH0) Channel Period Register */
#وصف_ڪريو AT91C_PWMC_CH0_CDTYR       ( ( AT91_REG * ) 0xFFFCC204 ) /* (PWMC_CH0) Channel Duty Cycle Register */
#وصف_ڪريو AT91C_PWMC_CH0_CMR         ( ( AT91_REG * ) 0xFFFCC200 ) /* (PWMC_CH0) Channel Mode Register */
#وصف_ڪريو AT91C_PWMC_CH0_CUPDR       ( ( AT91_REG * ) 0xFFFCC210 ) /* (PWMC_CH0) Channel Update Register */
#وصف_ڪريو AT91C_PWMC_CH0_CCNTR       ( ( AT91_REG * ) 0xFFFCC20C ) /* (PWMC_CH0) Channel Counter Register */
/* ========== Register definition for PWMC peripheral ========== */
#وصف_ڪريو AT91C_PWMC_IDR             ( ( AT91_REG * ) 0xFFFCC014 ) /* (PWMC) PWMC Interrupt Disable Register */
#وصف_ڪريو AT91C_PWMC_DIS             ( ( AT91_REG * ) 0xFFFCC008 ) /* (PWMC) PWMC Disable Register */
#وصف_ڪريو AT91C_PWMC_IER             ( ( AT91_REG * ) 0xFFFCC010 ) /* (PWMC) PWMC Interrupt Enable Register */
#وصف_ڪريو AT91C_PWMC_VR              ( ( AT91_REG * ) 0xFFFCC0FC ) /* (PWMC) PWMC Version Register */
#وصف_ڪريو AT91C_PWMC_ISR             ( ( AT91_REG * ) 0xFFFCC01C ) /* (PWMC) PWMC Interrupt Status Register */
#وصف_ڪريو AT91C_PWMC_SR              ( ( AT91_REG * ) 0xFFFCC00C ) /* (PWMC) PWMC Status Register */
#وصف_ڪريو AT91C_PWMC_IMR             ( ( AT91_REG * ) 0xFFFCC018 ) /* (PWMC) PWMC Interrupt Mask Register */
#وصف_ڪريو AT91C_PWMC_MR              ( ( AT91_REG * ) 0xFFFCC000 ) /* (PWMC) PWMC Mode Register */
#وصف_ڪريو AT91C_PWMC_ENA             ( ( AT91_REG * ) 0xFFFCC004 ) /* (PWMC) PWMC Enable Register */
/* ========== Register definition for UDP peripheral ========== */
#وصف_ڪريو AT91C_UDP_IMR              ( ( AT91_REG * ) 0xFFFB0018 ) /* (UDP) Interrupt Mask Register */
#وصف_ڪريو AT91C_UDP_FADDR            ( ( AT91_REG * ) 0xFFFB0008 ) /* (UDP) Function Address Register */
#وصف_ڪريو AT91_C_UDP_انگ              ( ( AT91_REG * ) 0xFFFB0000 ) /* (UDP) Frame Number Register */
#وصف_ڪريو AT91C_UDP_FDR              ( ( AT91_REG * ) 0xFFFB0050 ) /* (UDP) Endpoint FIFO Data Register */
#وصف_ڪريو AT91C_UDP_ISR              ( ( AT91_REG * ) 0xFFFB001C ) /* (UDP) Interrupt Status Register */
#وصف_ڪريو AT91C_UDP_CSR              ( ( AT91_REG * ) 0xFFFB0030 ) /* (UDP) Endpoint Control and Status Register */
#وصف_ڪريو AT91C_UDP_IDR              ( ( AT91_REG * ) 0xFFFB0014 ) /* (UDP) Interrupt Disable Register */
#وصف_ڪريو AT91C_UDP_ICR              ( ( AT91_REG * ) 0xFFFB0020 ) /* (UDP) Interrupt Clear Register */
#وصف_ڪريو AT91C_UDP_RSTEP            ( ( AT91_REG * ) 0xFFFB0028 ) /* (UDP) Reset Endpoint Register */
#وصف_ڪريو AT91C_UDP_TXVC             ( ( AT91_REG * ) 0xFFFB0074 ) /* (UDP) Transceiver Control Register */
#وصف_ڪريو AT91C_UDP_GLBSTATE         ( ( AT91_REG * ) 0xFFFB0004 ) /* (UDP) Global State Register */
#وصف_ڪريو AT91C_UDP_IER              ( ( AT91_REG * ) 0xFFFB0010 ) /* (UDP) Interrupt Enable Register */
/* ========== Register definition for TC0 peripheral ========== */
#وصف_ڪريو AT91C_TC0_SR               ( ( AT91_REG * ) 0xFFFA0020 ) /* (TC0) Status Register */
#وصف_ڪريو AT91C_TC0_RC               ( ( AT91_REG * ) 0xFFFA001C ) /* (TC0) Register C */
#وصف_ڪريو AT91C_TC0_RB               ( ( AT91_REG * ) 0xFFFA0018 ) /* (TC0) Register B */
#وصف_ڪريو AT91C_TC0_CCR              ( ( AT91_REG * ) 0xFFFA0000 ) /* (TC0) Channel Control Register */
#وصف_ڪريو AT91C_TC0_CMR              ( ( AT91_REG * ) 0xFFFA0004 ) /* (TC0) Channel Mode Register (Capture Mode / Waveform Mode) */
#وصف_ڪريو AT91C_TC0_IER              ( ( AT91_REG * ) 0xFFFA0024 ) /* (TC0) Interrupt Enable Register */
#وصف_ڪريو AT91C_TC0_RA               ( ( AT91_REG * ) 0xFFFA0014 ) /* (TC0) Register A */
#وصف_ڪريو AT91C_TC0_IDR              ( ( AT91_REG * ) 0xFFFA0028 ) /* (TC0) Interrupt Disable Register */
#وصف_ڪريو AT91C_TC0_CV               ( ( AT91_REG * ) 0xFFFA0010 ) /* (TC0) Counter Value */
#وصف_ڪريو AT91C_TC0_IMR              ( ( AT91_REG * ) 0xFFFA002C ) /* (TC0) Interrupt Mask Register */
/* ========== Register definition for TC1 peripheral ========== */
#وصف_ڪريو AT91C_TC1_RB               ( ( AT91_REG * ) 0xFFFA0058 ) /* (TC1) Register B */
#وصف_ڪريو AT91C_TC1_CCR              ( ( AT91_REG * ) 0xFFFA0040 ) /* (TC1) Channel Control Register */
#وصف_ڪريو AT91C_TC1_IER              ( ( AT91_REG * ) 0xFFFA0064 ) /* (TC1) Interrupt Enable Register */
#وصف_ڪريو AT91C_TC1_IDR              ( ( AT91_REG * ) 0xFFFA0068 ) /* (TC1) Interrupt Disable Register */
#وصف_ڪريو AT91C_TC1_SR               ( ( AT91_REG * ) 0xFFFA0060 ) /* (TC1) Status Register */
#وصف_ڪريو AT91C_TC1_CMR              ( ( AT91_REG * ) 0xFFFA0044 ) /* (TC1) Channel Mode Register (Capture Mode / Waveform Mode) */
#وصف_ڪريو AT91C_TC1_RA               ( ( AT91_REG * ) 0xFFFA0054 ) /* (TC1) Register A */
#وصف_ڪريو AT91C_TC1_RC               ( ( AT91_REG * ) 0xFFFA005C ) /* (TC1) Register C */
#وصف_ڪريو AT91C_TC1_IMR              ( ( AT91_REG * ) 0xFFFA006C ) /* (TC1) Interrupt Mask Register */
#وصف_ڪريو AT91C_TC1_CV               ( ( AT91_REG * ) 0xFFFA0050 ) /* (TC1) Counter Value */
/* ========== Register definition for TC2 peripheral ========== */
#وصف_ڪريو AT91C_TC2_CMR              ( ( AT91_REG * ) 0xFFFA0084 ) /* (TC2) Channel Mode Register (Capture Mode / Waveform Mode) */
#وصف_ڪريو AT91C_TC2_CCR              ( ( AT91_REG * ) 0xFFFA0080 ) /* (TC2) Channel Control Register */
#وصف_ڪريو AT91C_TC2_CV               ( ( AT91_REG * ) 0xFFFA0090 ) /* (TC2) Counter Value */
#وصف_ڪريو AT91C_TC2_RA               ( ( AT91_REG * ) 0xFFFA0094 ) /* (TC2) Register A */
#وصف_ڪريو AT91C_TC2_RB               ( ( AT91_REG * ) 0xFFFA0098 ) /* (TC2) Register B */
#وصف_ڪريو AT91C_TC2_IDR              ( ( AT91_REG * ) 0xFFFA00A8 ) /* (TC2) Interrupt Disable Register */
#وصف_ڪريو AT91C_TC2_IMR              ( ( AT91_REG * ) 0xFFFA00AC ) /* (TC2) Interrupt Mask Register */
#وصف_ڪريو AT91C_TC2_RC               ( ( AT91_REG * ) 0xFFFA009C ) /* (TC2) Register C */
#وصف_ڪريو AT91C_TC2_IER              ( ( AT91_REG * ) 0xFFFA00A4 ) /* (TC2) Interrupt Enable Register */
#وصف_ڪريو AT91C_TC2_SR               ( ( AT91_REG * ) 0xFFFA00A0 ) /* (TC2) Status Register */
/* ========== Register definition for TCB peripheral ========== */
#وصف_ڪريو AT91C_TCB_BMR              ( ( AT91_REG * ) 0xFFFA00C4 ) /* (TCB) TC Block Mode Register */
#وصف_ڪريو AT91C_TCB_BCR              ( ( AT91_REG * ) 0xFFFA00C0 ) /* (TCB) TC Block Control Register */
/* ========== Register definition for CAN_MB0 peripheral ========== */
#وصف_ڪريو AT91C_CAN_MB0_MDL          ( ( AT91_REG * ) 0xFFFD0214 ) /* (CAN_MB0) MailBox Data Low Register */
#وصف_ڪريو AT91C_CAN_MB0_MAM          ( ( AT91_REG * ) 0xFFFD0204 ) /* (CAN_MB0) MailBox Acceptance Mask Register */
#وصف_ڪريو AT91C_CAN_MB0_MCR          ( ( AT91_REG * ) 0xFFFD021C ) /* (CAN_MB0) MailBox Control Register */
#وصف_ڪريو AT91C_CAN_MB0_MID          ( ( AT91_REG * ) 0xFFFD0208 ) /* (CAN_MB0) MailBox ID Register */
#وصف_ڪريو AT91C_CAN_MB0_MSR          ( ( AT91_REG * ) 0xFFFD0210 ) /* (CAN_MB0) MailBox Status Register */
#وصف_ڪريو AT91C_CAN_MB0_MFID         ( ( AT91_REG * ) 0xFFFD020C ) /* (CAN_MB0) MailBox Family ID Register */
#وصف_ڪريو AT91C_CAN_MB0_MDH          ( ( AT91_REG * ) 0xFFFD0218 ) /* (CAN_MB0) MailBox Data High Register */
#وصف_ڪريو AT91C_CAN_MB0_MMR          ( ( AT91_REG * ) 0xFFFD0200 ) /* (CAN_MB0) MailBox Mode Register */
/* ========== Register definition for CAN_MB1 peripheral ========== */
#وصف_ڪريو AT91C_CAN_MB1_MDL          ( ( AT91_REG * ) 0xFFFD0234 ) /* (CAN_MB1) MailBox Data Low Register */
#وصف_ڪريو AT91C_CAN_MB1_MID          ( ( AT91_REG * ) 0xFFFD0228 ) /* (CAN_MB1) MailBox ID Register */
#وصف_ڪريو AT91C_CAN_MB1_MMR          ( ( AT91_REG * ) 0xFFFD0220 ) /* (CAN_MB1) MailBox Mode Register */
#وصف_ڪريو AT91C_CAN_MB1_MSR          ( ( AT91_REG * ) 0xFFFD0230 ) /* (CAN_MB1) MailBox Status Register */
#وصف_ڪريو AT91C_CAN_MB1_MAM          ( ( AT91_REG * ) 0xFFFD0224 ) /* (CAN_MB1) MailBox Acceptance Mask Register */
#وصف_ڪريو AT91C_CAN_MB1_MDH          ( ( AT91_REG * ) 0xFFFD0238 ) /* (CAN_MB1) MailBox Data High Register */
#وصف_ڪريو AT91C_CAN_MB1_MCR          ( ( AT91_REG * ) 0xFFFD023C ) /* (CAN_MB1) MailBox Control Register */
#وصف_ڪريو AT91C_CAN_MB1_MFID         ( ( AT91_REG * ) 0xFFFD022C ) /* (CAN_MB1) MailBox Family ID Register */
/* ========== Register definition for CAN_MB2 peripheral ========== */
#وصف_ڪريو AT91C_CAN_MB2_MCR          ( ( AT91_REG * ) 0xFFFD025C ) /* (CAN_MB2) MailBox Control Register */
#وصف_ڪريو AT91C_CAN_MB2_MDH          ( ( AT91_REG * ) 0xFFFD0258 ) /* (CAN_MB2) MailBox Data High Register */
#وصف_ڪريو AT91C_CAN_MB2_MID          ( ( AT91_REG * ) 0xFFFD0248 ) /* (CAN_MB2) MailBox ID Register */
#وصف_ڪريو AT91C_CAN_MB2_MDL          ( ( AT91_REG * ) 0xFFFD0254 ) /* (CAN_MB2) MailBox Data Low Register */
#وصف_ڪريو AT91C_CAN_MB2_MMR          ( ( AT91_REG * ) 0xFFFD0240 ) /* (CAN_MB2) MailBox Mode Register */
#وصف_ڪريو AT91C_CAN_MB2_MAM          ( ( AT91_REG * ) 0xFFFD0244 ) /* (CAN_MB2) MailBox Acceptance Mask Register */
#وصف_ڪريو AT91C_CAN_MB2_MFID         ( ( AT91_REG * ) 0xFFFD024C ) /* (CAN_MB2) MailBox Family ID Register */
#وصف_ڪريو AT91C_CAN_MB2_MSR          ( ( AT91_REG * ) 0xFFFD0250 ) /* (CAN_MB2) MailBox Status Register */
/* ========== Register definition for CAN_MB3 peripheral ========== */
#وصف_ڪريو AT91C_CAN_MB3_MFID         ( ( AT91_REG * ) 0xFFFD026C ) /* (CAN_MB3) MailBox Family ID Register */
#وصف_ڪريو AT91C_CAN_MB3_MAM          ( ( AT91_REG * ) 0xFFFD0264 ) /* (CAN_MB3) MailBox Acceptance Mask Register */
#وصف_ڪريو AT91C_CAN_MB3_MID          ( ( AT91_REG * ) 0xFFFD0268 ) /* (CAN_MB3) MailBox ID Register */
#وصف_ڪريو AT91C_CAN_MB3_MCR          ( ( AT91_REG * ) 0xFFFD027C ) /* (CAN_MB3) MailBox Control Register */
#وصف_ڪريو AT91C_CAN_MB3_MMR          ( ( AT91_REG * ) 0xFFFD0260 ) /* (CAN_MB3) MailBox Mode Register */
#وصف_ڪريو AT91C_CAN_MB3_MSR          ( ( AT91_REG * ) 0xFFFD0270 ) /* (CAN_MB3) MailBox Status Register */
#وصف_ڪريو AT91C_CAN_MB3_MDL          ( ( AT91_REG * ) 0xFFFD0274 ) /* (CAN_MB3) MailBox Data Low Register */
#وصف_ڪريو AT91C_CAN_MB3_MDH          ( ( AT91_REG * ) 0xFFFD0278 ) /* (CAN_MB3) MailBox Data High Register */
/* ========== Register definition for CAN_MB4 peripheral ========== */
#وصف_ڪريو AT91C_CAN_MB4_MID          ( ( AT91_REG * ) 0xFFFD0288 ) /* (CAN_MB4) MailBox ID Register */
#وصف_ڪريو AT91C_CAN_MB4_MMR          ( ( AT91_REG * ) 0xFFFD0280 ) /* (CAN_MB4) MailBox Mode Register */
#وصف_ڪريو AT91C_CAN_MB4_MDH          ( ( AT91_REG * ) 0xFFFD0298 ) /* (CAN_MB4) MailBox Data High Register */
#وصف_ڪريو AT91C_CAN_MB4_MFID         ( ( AT91_REG * ) 0xFFFD028C ) /* (CAN_MB4) MailBox Family ID Register */
#وصف_ڪريو AT91C_CAN_MB4_MSR          ( ( AT91_REG * ) 0xFFFD0290 ) /* (CAN_MB4) MailBox Status Register */
#وصف_ڪريو AT91C_CAN_MB4_MCR          ( ( AT91_REG * ) 0xFFFD029C ) /* (CAN_MB4) MailBox Control Register */
#وصف_ڪريو AT91C_CAN_MB4_MDL          ( ( AT91_REG * ) 0xFFFD0294 ) /* (CAN_MB4) MailBox Data Low Register */
#وصف_ڪريو AT91C_CAN_MB4_MAM          ( ( AT91_REG * ) 0xFFFD0284 ) /* (CAN_MB4) MailBox Acceptance Mask Register */
/* ========== Register definition for CAN_MB5 peripheral ========== */
#وصف_ڪريو AT91C_CAN_MB5_MSR          ( ( AT91_REG * ) 0xFFFD02B0 ) /* (CAN_MB5) MailBox Status Register */
#وصف_ڪريو AT91C_CAN_MB5_MCR          ( ( AT91_REG * ) 0xFFFD02BC ) /* (CAN_MB5) MailBox Control Register */
#وصف_ڪريو AT91C_CAN_MB5_MFID         ( ( AT91_REG * ) 0xFFFD02AC ) /* (CAN_MB5) MailBox Family ID Register */
#وصف_ڪريو AT91C_CAN_MB5_MDH          ( ( AT91_REG * ) 0xFFFD02B8 ) /* (CAN_MB5) MailBox Data High Register */
#وصف_ڪريو AT91C_CAN_MB5_MID          ( ( AT91_REG * ) 0xFFFD02A8 ) /* (CAN_MB5) MailBox ID Register */
#وصف_ڪريو AT91C_CAN_MB5_MMR          ( ( AT91_REG * ) 0xFFFD02A0 ) /* (CAN_MB5) MailBox Mode Register */
#وصف_ڪريو AT91C_CAN_MB5_MDL          ( ( AT91_REG * ) 0xFFFD02B4 ) /* (CAN_MB5) MailBox Data Low Register */
#وصف_ڪريو AT91C_CAN_MB5_MAM          ( ( AT91_REG * ) 0xFFFD02A4 ) /* (CAN_MB5) MailBox Acceptance Mask Register */
/* ========== Register definition for CAN_MB6 peripheral ========== */
#وصف_ڪريو AT91C_CAN_MB6_MFID         ( ( AT91_REG * ) 0xFFFD02CC ) /* (CAN_MB6) MailBox Family ID Register */
#وصف_ڪريو AT91C_CAN_MB6_MID          ( ( AT91_REG * ) 0xFFFD02C8 ) /* (CAN_MB6) MailBox ID Register */
#وصف_ڪريو AT91C_CAN_MB6_MAM          ( ( AT91_REG * ) 0xFFFD02C4 ) /* (CAN_MB6) MailBox Acceptance Mask Register */
#وصف_ڪريو AT91C_CAN_MB6_MSR          ( ( AT91_REG * ) 0xFFFD02D0 ) /* (CAN_MB6) MailBox Status Register */
#وصف_ڪريو AT91C_CAN_MB6_MDL          ( ( AT91_REG * ) 0xFFFD02D4 ) /* (CAN_MB6) MailBox Data Low Register */
#وصف_ڪريو AT91C_CAN_MB6_MCR          ( ( AT91_REG * ) 0xFFFD02DC ) /* (CAN_MB6) MailBox Control Register */
#وصف_ڪريو AT91C_CAN_MB6_MDH          ( ( AT91_REG * ) 0xFFFD02D8 ) /* (CAN_MB6) MailBox Data High Register */
#وصف_ڪريو AT91C_CAN_MB6_MMR          ( ( AT91_REG * ) 0xFFFD02C0 ) /* (CAN_MB6) MailBox Mode Register */
/* ========== Register definition for CAN_MB7 peripheral ========== */
#وصف_ڪريو AT91C_CAN_MB7_MCR          ( ( AT91_REG * ) 0xFFFD02FC ) /* (CAN_MB7) MailBox Control Register */
#وصف_ڪريو AT91C_CAN_MB7_MDH          ( ( AT91_REG * ) 0xFFFD02F8 ) /* (CAN_MB7) MailBox Data High Register */
#وصف_ڪريو AT91C_CAN_MB7_MFID         ( ( AT91_REG * ) 0xFFFD02EC ) /* (CAN_MB7) MailBox Family ID Register */
#وصف_ڪريو AT91C_CAN_MB7_MDL          ( ( AT91_REG * ) 0xFFFD02F4 ) /* (CAN_MB7) MailBox Data Low Register */
#وصف_ڪريو AT91C_CAN_MB7_MID          ( ( AT91_REG * ) 0xFFFD02E8 ) /* (CAN_MB7) MailBox ID Register */
#وصف_ڪريو AT91C_CAN_MB7_MMR          ( ( AT91_REG * ) 0xFFFD02E0 ) /* (CAN_MB7) MailBox Mode Register */
#وصف_ڪريو AT91C_CAN_MB7_MAM          ( ( AT91_REG * ) 0xFFFD02E4 ) /* (CAN_MB7) MailBox Acceptance Mask Register */
#وصف_ڪريو AT91C_CAN_MB7_MSR          ( ( AT91_REG * ) 0xFFFD02F0 ) /* (CAN_MB7) MailBox Status Register */
/* ========== Register definition for CAN peripheral ========== */
#وصف_ڪريو AT91C_CAN_TCR              ( ( AT91_REG * ) 0xFFFD0024 ) /* (CAN) Transfer Command Register */
#وصف_ڪريو AT91C_CAN_IMR              ( ( AT91_REG * ) 0xFFFD000C ) /* (CAN) Interrupt Mask Register */
#وصف_ڪريو AT91C_CAN_IER              ( ( AT91_REG * ) 0xFFFD0004 ) /* (CAN) Interrupt Enable Register */
#وصف_ڪريو AT91C_CAN_ECR              ( ( AT91_REG * ) 0xFFFD0020 ) /* (CAN) Error Counter Register */
#وصف_ڪريو AT91C_CAN_TIMESTP          ( ( AT91_REG * ) 0xFFFD001C ) /* (CAN) Time Stamp Register */
#وصف_ڪريو AT91C_CAN_MR               ( ( AT91_REG * ) 0xFFFD0000 ) /* (CAN) Mode Register */
#وصف_ڪريو AT91C_CAN_IDR              ( ( AT91_REG * ) 0xFFFD0008 ) /* (CAN) Interrupt Disable Register */
#وصف_ڪريو AT91C_CAN_ACR              ( ( AT91_REG * ) 0xFFFD0028 ) /* (CAN) Abort Command Register */
#وصف_ڪريو AT91C_CAN_TIM              ( ( AT91_REG * ) 0xFFFD0018 ) /* (CAN) Timer Register */
#وصف_ڪريو AT91C_CAN_SR               ( ( AT91_REG * ) 0xFFFD0010 ) /* (CAN) Status Register */
#وصف_ڪريو AT91C_CAN_BR               ( ( AT91_REG * ) 0xFFFD0014 ) /* (CAN) Baudrate Register */
#وصف_ڪريو AT91C_CAN_VR               ( ( AT91_REG * ) 0xFFFD00FC ) /* (CAN) Version Register */
/* ========== Register definition for EMAC peripheral ========== */
#وصف_ڪريو AT91C_EMAC_ISR             ( ( AT91_REG * ) 0xFFFDC024 ) /* (EMAC) Interrupt Status Register */
#وصف_ڪريو AT91C_EMAC_SA4H            ( ( AT91_REG * ) 0xFFFDC0B4 ) /* (EMAC) Specific Address 4 Top, Last 2 bytes */
#وصف_ڪريو AT91C_EMAC_SA1L            ( ( AT91_REG * ) 0xFFFDC098 ) /* (EMAC) Specific Address 1 Bottom, First 4 bytes */
#وصف_ڪريو AT91C_EMAC_ELE             ( ( AT91_REG * ) 0xFFFDC078 ) /* (EMAC) Excessive Length Errors Register */
#وصف_ڪريو AT91C_EMAC_LCOL            ( ( AT91_REG * ) 0xFFFDC05C ) /* (EMAC) Late Collision Register */
#وصف_ڪريو AT91C_EMAC_RLE             ( ( AT91_REG * ) 0xFFFDC088 ) /* (EMAC) Receive Length Field Mismatch Register */
#وصف_ڪريو AT91C_EMAC_WOL             ( ( AT91_REG * ) 0xFFFDC0C4 ) /* (EMAC) Wake On LAN Register */
#وصف_ڪريو AT91C_EMAC_DTF             ( ( AT91_REG * ) 0xFFFDC058 ) /* (EMAC) Deferred Transmission Frame Register */
#وصف_ڪريو AT91C_EMAC_TUND            ( ( AT91_REG * ) 0xFFFDC064 ) /* (EMAC) Transmit Underrun Error Register */
#وصف_ڪريو AT91C_EMAC_NCR             ( ( AT91_REG * ) 0xFFFDC000 ) /* (EMAC) Network Control Register */
#وصف_ڪريو AT91C_EMAC_SA4L            ( ( AT91_REG * ) 0xFFFDC0B0 ) /* (EMAC) Specific Address 4 Bottom, First 4 bytes */
#وصف_ڪريو AT91C_EMAC_RSR             ( ( AT91_REG * ) 0xFFFDC020 ) /* (EMAC) Receive Status Register */
#وصف_ڪريو AT91C_EMAC_SA3L            ( ( AT91_REG * ) 0xFFFDC0A8 ) /* (EMAC) Specific Address 3 Bottom, First 4 bytes */
#وصف_ڪريو AT91C_EMAC_TSR             ( ( AT91_REG * ) 0xFFFDC014 ) /* (EMAC) Transmit Status Register */
#وصف_ڪريو AT91C_EMAC_IDR             ( ( AT91_REG * ) 0xFFFDC02C ) /* (EMAC) Interrupt Disable Register */
#وصف_ڪريو AT91C_EMAC_RSE             ( ( AT91_REG * ) 0xFFFDC074 ) /* (EMAC) Receive Symbol Errors Register */
#وصف_ڪريو AT91C_EMAC_ECOL            ( ( AT91_REG * ) 0xFFFDC060 ) /* (EMAC) Excessive Collision Register */
#وصف_ڪريو AT91C_EMAC_TID             ( ( AT91_REG * ) 0xFFFDC0B8 ) /* (EMAC) Type ID Checking Register */
#وصف_ڪريو AT91C_EMAC_HRB             ( ( AT91_REG * ) 0xFFFDC090 ) /* (EMAC) Hash Address Bottom[31:0] */
#وصف_ڪريو AT91C_EMAC_TBQP            ( ( AT91_REG * ) 0xFFFDC01C ) /* (EMAC) Transmit Buffer Queue Pointer */
#وصف_ڪريو AT91C_EMAC_USRIO           ( ( AT91_REG * ) 0xFFFDC0C0 ) /* (EMAC) USER Input/Output Register */
#وصف_ڪريو AT91C_EMAC_PTR             ( ( AT91_REG * ) 0xFFFDC038 ) /* (EMAC) Pause Time Register */
#وصف_ڪريو AT91C_EMAC_SA2H            ( ( AT91_REG * ) 0xFFFDC0A4 ) /* (EMAC) Specific Address 2 Top, Last 2 bytes */
#وصف_ڪريو AT91C_EMAC_ROV             ( ( AT91_REG * ) 0xFFFDC070 ) /* (EMAC) Receive Overrun Errors Register */
#وصف_ڪريو AT91C_EMAC_ALE             ( ( AT91_REG * ) 0xFFFDC054 ) /* (EMAC) Alignment Error Register */
#وصف_ڪريو AT91C_EMAC_RJA             ( ( AT91_REG * ) 0xFFFDC07C ) /* (EMAC) Receive Jabbers Register */
#وصف_ڪريو AT91C_EMAC_RBQP            ( ( AT91_REG * ) 0xFFFDC018 ) /* (EMAC) Receive Buffer Queue Pointer */
#وصف_ڪريو AT91C_EMAC_TPF             ( ( AT91_REG * ) 0xFFFDC08C ) /* (EMAC) Transmitted Pause Frames Register */
#وصف_ڪريو AT91C_EMAC_NCFGR           ( ( AT91_REG * ) 0xFFFDC004 ) /* (EMAC) Network Configuration Register */
#وصف_ڪريو AT91C_EMAC_HRT             ( ( AT91_REG * ) 0xFFFDC094 ) /* (EMAC) Hash Address Top[63:32] */
#وصف_ڪريو AT91C_EMAC_USF             ( ( AT91_REG * ) 0xFFFDC080 ) /* (EMAC) Undersize Frames Register */
#وصف_ڪريو AT91C_EMAC_FCSE            ( ( AT91_REG * ) 0xFFFDC050 ) /* (EMAC) Frame Check Sequence Error Register */
#وصف_ڪريو AT91C_EMAC_TPQ             ( ( AT91_REG * ) 0xFFFDC0BC ) /* (EMAC) Transmit Pause Quantum Register */
#وصف_ڪريو AT91C_EMAC_MAN             ( ( AT91_REG * ) 0xFFFDC034 ) /* (EMAC) PHY Maintenance Register */
#وصف_ڪريو AT91C_EMAC_FTO             ( ( AT91_REG * ) 0xFFFDC040 ) /* (EMAC) Frames Transmitted OK Register */
#وصف_ڪريو AT91C_EMAC_REV             ( ( AT91_REG * ) 0xFFFDC0FC ) /* (EMAC) Revision Register */
#وصف_ڪريو AT91C_EMAC_IMR             ( ( AT91_REG * ) 0xFFFDC030 ) /* (EMAC) Interrupt Mask Register */
#وصف_ڪريو AT91C_EMAC_SCF             ( ( AT91_REG * ) 0xFFFDC044 ) /* (EMAC) Single Collision Frame Register */
#وصف_ڪريو AT91C_EMAC_PFR             ( ( AT91_REG * ) 0xFFFDC03C ) /* (EMAC) Pause Frames received Register */
#وصف_ڪريو AT91C_EMAC_MCF             ( ( AT91_REG * ) 0xFFFDC048 ) /* (EMAC) Multiple Collision Frame Register */
#وصف_ڪريو AT91C_EMAC_NSR             ( ( AT91_REG * ) 0xFFFDC008 ) /* (EMAC) Network Status Register */
#وصف_ڪريو AT91C_EMAC_SA2L            ( ( AT91_REG * ) 0xFFFDC0A0 ) /* (EMAC) Specific Address 2 Bottom, First 4 bytes */
#وصف_ڪريو AT91C_EMAC_FRO             ( ( AT91_REG * ) 0xFFFDC04C ) /* (EMAC) Frames Received OK Register */
#وصف_ڪريو AT91C_EMAC_IER             ( ( AT91_REG * ) 0xFFFDC028 ) /* (EMAC) Interrupt Enable Register */
#وصف_ڪريو AT91C_EMAC_SA1H            ( ( AT91_REG * ) 0xFFFDC09C ) /* (EMAC) Specific Address 1 Top, Last 2 bytes */
#وصف_ڪريو AT91C_EMAC_CSE             ( ( AT91_REG * ) 0xFFFDC068 ) /* (EMAC) Carrier Sense Error Register */
#وصف_ڪريو AT91C_EMAC_SA3H            ( ( AT91_REG * ) 0xFFFDC0AC ) /* (EMAC) Specific Address 3 Top, Last 2 bytes */
#وصف_ڪريو AT91C_EMAC_RRE             ( ( AT91_REG * ) 0xFFFDC06C ) /* (EMAC) Receive Resource Error Register */
#وصف_ڪريو AT91C_EMAC_STE             ( ( AT91_REG * ) 0xFFFDC084 ) /* (EMAC) SQE Test Error Register */
/* ========== Register definition for PDC_ADC peripheral ========== */
#وصف_ڪريو AT91C_ADC_PTSR             ( ( AT91_REG * ) 0xFFFD8124 ) /* (PDC_ADC) PDC Transfer Status Register */
#وصف_ڪريو AT91C_ADC_PTCR             ( ( AT91_REG * ) 0xFFFD8120 ) /* (PDC_ADC) PDC Transfer Control Register */
#وصف_ڪريو AT91C_ADC_TNPR             ( ( AT91_REG * ) 0xFFFD8118 ) /* (PDC_ADC) Transmit Next Pointer Register */
#وصف_ڪريو AT91C_ADC_TNCR             ( ( AT91_REG * ) 0xFFFD811C ) /* (PDC_ADC) Transmit Next Counter Register */
#وصف_ڪريو AT91C_ADC_RNPR             ( ( AT91_REG * ) 0xFFFD8110 ) /* (PDC_ADC) Receive Next Pointer Register */
#وصف_ڪريو AT91C_ADC_RNCR             ( ( AT91_REG * ) 0xFFFD8114 ) /* (PDC_ADC) Receive Next Counter Register */
#وصف_ڪريو AT91C_ADC_RPR              ( ( AT91_REG * ) 0xFFFD8100 ) /* (PDC_ADC) Receive Pointer Register */
#وصف_ڪريو AT91C_ADC_TCR              ( ( AT91_REG * ) 0xFFFD810C ) /* (PDC_ADC) Transmit Counter Register */
#وصف_ڪريو AT91C_ADC_TPR              ( ( AT91_REG * ) 0xFFFD8108 ) /* (PDC_ADC) Transmit Pointer Register */
#وصف_ڪريو AT91C_ADC_RCR              ( ( AT91_REG * ) 0xFFFD8104 ) /* (PDC_ADC) Receive Counter Register */
/* ========== Register definition for ADC peripheral ========== */
#وصف_ڪريو AT91C_ADC_CDR2             ( ( AT91_REG * ) 0xFFFD8038 ) /* (ADC) ADC Channel Data Register 2 */
#وصف_ڪريو AT91C_ADC_CDR3             ( ( AT91_REG * ) 0xFFFD803C ) /* (ADC) ADC Channel Data Register 3 */
#وصف_ڪريو AT91C_ADC_CDR0             ( ( AT91_REG * ) 0xFFFD8030 ) /* (ADC) ADC Channel Data Register 0 */
#وصف_ڪريو AT91C_ADC_CDR5             ( ( AT91_REG * ) 0xFFFD8044 ) /* (ADC) ADC Channel Data Register 5 */
#وصف_ڪريو AT91C_ADC_CHDR             ( ( AT91_REG * ) 0xFFFD8014 ) /* (ADC) ADC Channel Disable Register */
#وصف_ڪريو AT91C_ADC_SR               ( ( AT91_REG * ) 0xFFFD801C ) /* (ADC) ADC Status Register */
#وصف_ڪريو AT91C_ADC_CDR4             ( ( AT91_REG * ) 0xFFFD8040 ) /* (ADC) ADC Channel Data Register 4 */
#وصف_ڪريو AT91C_ADC_CDR1             ( ( AT91_REG * ) 0xFFFD8034 ) /* (ADC) ADC Channel Data Register 1 */
#وصف_ڪريو AT91C_ADC_LCDR             ( ( AT91_REG * ) 0xFFFD8020 ) /* (ADC) ADC Last Converted Data Register */
#وصف_ڪريو AT91C_ADC_IDR              ( ( AT91_REG * ) 0xFFFD8028 ) /* (ADC) ADC Interrupt Disable Register */
#وصف_ڪريو AT91C_ADC_CR               ( ( AT91_REG * ) 0xFFFD8000 ) /* (ADC) ADC Control Register */
#وصف_ڪريو AT91C_ADC_CDR7             ( ( AT91_REG * ) 0xFFFD804C ) /* (ADC) ADC Channel Data Register 7 */
#وصف_ڪريو AT91C_ADC_CDR6             ( ( AT91_REG * ) 0xFFFD8048 ) /* (ADC) ADC Channel Data Register 6 */
#وصف_ڪريو AT91C_ADC_IER              ( ( AT91_REG * ) 0xFFFD8024 ) /* (ADC) ADC Interrupt Enable Register */
#وصف_ڪريو AT91C_ADC_CHER             ( ( AT91_REG * ) 0xFFFD8010 ) /* (ADC) ADC Channel Enable Register */
#وصف_ڪريو AT91C_ADC_CHSR             ( ( AT91_REG * ) 0xFFFD8018 ) /* (ADC) ADC Channel Status Register */
#وصف_ڪريو AT91C_ADC_MR               ( ( AT91_REG * ) 0xFFFD8004 ) /* (ADC) ADC Mode Register */
#وصف_ڪريو AT91C_ADC_IMR              ( ( AT91_REG * ) 0xFFFD802C ) /* (ADC) ADC Interrupt Mask Register */
/* ========== Register definition for PDC_AES peripheral ========== */
#وصف_ڪريو AT91C_AES_TPR              ( ( AT91_REG * ) 0xFFFA4108 ) /* (PDC_AES) Transmit Pointer Register */
#وصف_ڪريو AT91C_AES_PTCR             ( ( AT91_REG * ) 0xFFFA4120 ) /* (PDC_AES) PDC Transfer Control Register */
#وصف_ڪريو AT91C_AES_RNPR             ( ( AT91_REG * ) 0xFFFA4110 ) /* (PDC_AES) Receive Next Pointer Register */
#وصف_ڪريو AT91C_AES_TNCR             ( ( AT91_REG * ) 0xFFFA411C ) /* (PDC_AES) Transmit Next Counter Register */
#وصف_ڪريو AT91C_AES_TCR              ( ( AT91_REG * ) 0xFFFA410C ) /* (PDC_AES) Transmit Counter Register */
#وصف_ڪريو AT91C_AES_RCR              ( ( AT91_REG * ) 0xFFFA4104 ) /* (PDC_AES) Receive Counter Register */
#وصف_ڪريو AT91C_AES_RNCR             ( ( AT91_REG * ) 0xFFFA4114 ) /* (PDC_AES) Receive Next Counter Register */
#وصف_ڪريو AT91C_AES_TNPR             ( ( AT91_REG * ) 0xFFFA4118 ) /* (PDC_AES) Transmit Next Pointer Register */
#وصف_ڪريو AT91C_AES_RPR              ( ( AT91_REG * ) 0xFFFA4100 ) /* (PDC_AES) Receive Pointer Register */
#وصف_ڪريو AT91C_AES_PTSR             ( ( AT91_REG * ) 0xFFFA4124 ) /* (PDC_AES) PDC Transfer Status Register */
/* ========== Register definition for AES peripheral ========== */
#وصف_ڪريو AT91C_AES_IVxR             ( ( AT91_REG * ) 0xFFFA4060 ) /* (AES) Initialization Vector x Register */
#وصف_ڪريو AT91C_AES_MR               ( ( AT91_REG * ) 0xFFFA4004 ) /* (AES) Mode Register */
#وصف_ڪريو AT91C_AES_VR               ( ( AT91_REG * ) 0xFFFA40FC ) /* (AES) AES Version Register */
#وصف_ڪريو AT91C_AES_ODATAxR          ( ( AT91_REG * ) 0xFFFA4050 ) /* (AES) Output Data x Register */
#وصف_ڪريو AT91C_AES_IDATAxR          ( ( AT91_REG * ) 0xFFFA4040 ) /* (AES) Input Data x Register */
#وصف_ڪريو AT91C_AES_CR               ( ( AT91_REG * ) 0xFFFA4000 ) /* (AES) Control Register */
#وصف_ڪريو AT91C_AES_IDR              ( ( AT91_REG * ) 0xFFFA4014 ) /* (AES) Interrupt Disable Register */
#وصف_ڪريو AT91C_AES_IMR              ( ( AT91_REG * ) 0xFFFA4018 ) /* (AES) Interrupt Mask Register */
#وصف_ڪريو AT91C_AES_IER              ( ( AT91_REG * ) 0xFFFA4010 ) /* (AES) Interrupt Enable Register */
#وصف_ڪريو AT91C_AES_KEYWxR           ( ( AT91_REG * ) 0xFFFA4020 ) /* (AES) Key Word x Register */
#وصف_ڪريو AT91C_AES_ISR              ( ( AT91_REG * ) 0xFFFA401C ) /* (AES) Interrupt Status Register */
/* ========== Register definition for PDC_TDES peripheral ========== */
#وصف_ڪريو AT91C_TDES_RNCR            ( ( AT91_REG * ) 0xFFFA8114 ) /* (PDC_TDES) Receive Next Counter Register */
#وصف_ڪريو AT91C_TDES_TCR             ( ( AT91_REG * ) 0xFFFA810C ) /* (PDC_TDES) Transmit Counter Register */
#وصف_ڪريو AT91C_TDES_RCR             ( ( AT91_REG * ) 0xFFFA8104 ) /* (PDC_TDES) Receive Counter Register */
#وصف_ڪريو AT91C_TDES_TNPR            ( ( AT91_REG * ) 0xFFFA8118 ) /* (PDC_TDES) Transmit Next Pointer Register */
#وصف_ڪريو AT91C_TDES_RNPR            ( ( AT91_REG * ) 0xFFFA8110 ) /* (PDC_TDES) Receive Next Pointer Register */
#وصف_ڪريو AT91C_TDES_RPR             ( ( AT91_REG * ) 0xFFFA8100 ) /* (PDC_TDES) Receive Pointer Register */
#وصف_ڪريو AT91C_TDES_TNCR            ( ( AT91_REG * ) 0xFFFA811C ) /* (PDC_TDES) Transmit Next Counter Register */
#وصف_ڪريو AT91C_TDES_TPR             ( ( AT91_REG * ) 0xFFFA8108 ) /* (PDC_TDES) Transmit Pointer Register */
#وصف_ڪريو AT91C_TDES_PTSR            ( ( AT91_REG * ) 0xFFFA8124 ) /* (PDC_TDES) PDC Transfer Status Register */
#وصف_ڪريو AT91C_TDES_PTCR            ( ( AT91_REG * ) 0xFFFA8120 ) /* (PDC_TDES) PDC Transfer Control Register */
/* ========== Register definition for TDES peripheral ========== */
#وصف_ڪريو AT91C_TDES_KEY2WxR         ( ( AT91_REG * ) 0xFFFA8028 ) /* (TDES) Key 2 Word x Register */
#وصف_ڪريو AT91C_TDES_KEY3WxR         ( ( AT91_REG * ) 0xFFFA8030 ) /* (TDES) Key 3 Word x Register */
#وصف_ڪريو AT91C_TDES_IDR             ( ( AT91_REG * ) 0xFFFA8014 ) /* (TDES) Interrupt Disable Register */
#وصف_ڪريو AT91C_TDES_VR              ( ( AT91_REG * ) 0xFFFA80FC ) /* (TDES) TDES Version Register */
#وصف_ڪريو AT91C_TDES_IVxR            ( ( AT91_REG * ) 0xFFFA8060 ) /* (TDES) Initialization Vector x Register */
#وصف_ڪريو AT91C_TDES_ODATAxR         ( ( AT91_REG * ) 0xFFFA8050 ) /* (TDES) Output Data x Register */
#وصف_ڪريو AT91C_TDES_IMR             ( ( AT91_REG * ) 0xFFFA8018 ) /* (TDES) Interrupt Mask Register */
#وصف_ڪريو AT91C_TDES_MR              ( ( AT91_REG * ) 0xFFFA8004 ) /* (TDES) Mode Register */
#وصف_ڪريو AT91C_TDES_CR              ( ( AT91_REG * ) 0xFFFA8000 ) /* (TDES) Control Register */
#وصف_ڪريو AT91C_TDES_IER             ( ( AT91_REG * ) 0xFFFA8010 ) /* (TDES) Interrupt Enable Register */
#وصف_ڪريو AT91C_TDES_ISR             ( ( AT91_REG * ) 0xFFFA801C ) /* (TDES) Interrupt Status Register */
#وصف_ڪريو AT91C_TDES_IDATAxR         ( ( AT91_REG * ) 0xFFFA8040 ) /* (TDES) Input Data x Register */
#وصف_ڪريو AT91C_TDES_KEY1WxR         ( ( AT91_REG * ) 0xFFFA8020 ) /* (TDES) Key 1 Word x Register */

/* ***************************************************************************** */
/*               PIO DEFINITIONS FOR AT91SAM7X256 */
/* ***************************************************************************** */
#وصف_ڪريو AT91C_PIO_PA0             ( ( بنانشان صحيح ) 1 << 0 )         /* Pin Controlled by PA0 */
#وصف_ڪريو AT91C_PA0_RXD0            ( ( بنانشان صحيح ) AT91C_PIO_PA0 )  /*  USART 0 Receive Data */
#وصف_ڪريو AT91C_PIO_PA1             ( ( بنانشان صحيح ) 1 << 1 )         /* Pin Controlled by PA1 */
#وصف_ڪريو AT91C_PA1_TXD0            ( ( بنانشان صحيح ) AT91C_PIO_PA1 )  /*  USART 0 Transmit Data */
#وصف_ڪريو AT91C_PIO_PA10            ( ( بنانشان صحيح ) 1 << 10 )        /* Pin Controlled by PA10 */
#وصف_ڪريو AT91C_PA10_TWD            ( ( بنانشان صحيح ) AT91C_PIO_PA10 ) /*  TWI Two-wire Serial Data */
#وصف_ڪريو AT91C_PIO_PA11            ( ( بنانشان صحيح ) 1 << 11 )        /* Pin Controlled by PA11 */
#وصف_ڪريو AT91C_PA11_TWCK           ( ( بنانشان صحيح ) AT91C_PIO_PA11 ) /*  TWI Two-wire Serial Clock */
#وصف_ڪريو AT91C_PIO_PA12            ( ( بنانشان صحيح ) 1 << 12 )        /* Pin Controlled by PA12 */
#وصف_ڪريو AT91C_PA12_NPCS00         ( ( بنانشان صحيح ) AT91C_PIO_PA12 ) /*  SPI 0 Peripheral Chip Select 0 */
#وصف_ڪريو AT91C_PIO_PA13            ( ( بنانشان صحيح ) 1 << 13 )        /* Pin Controlled by PA13 */
#وصف_ڪريو AT91C_PA13_NPCS01         ( ( بنانشان صحيح ) AT91C_PIO_PA13 ) /*  SPI 0 Peripheral Chip Select 1 */
#وصف_ڪريو AT91C_PA13_PCK1           ( ( بنانشان صحيح ) AT91C_PIO_PA13 ) /*  PMC Programmable Clock Output 1 */
#وصف_ڪريو AT91C_PIO_PA14            ( ( بنانشان صحيح ) 1 << 14 )        /* Pin Controlled by PA14 */
#وصف_ڪريو AT91C_PA14_NPCS02         ( ( بنانشان صحيح ) AT91C_PIO_PA14 ) /*  SPI 0 Peripheral Chip Select 2 */
#وصف_ڪريو AT91C_PA14_IRQ1           ( ( بنانشان صحيح ) AT91C_PIO_PA14 ) /*  External Interrupt 1 */
#وصف_ڪريو AT91C_PIO_PA15            ( ( بنانشان صحيح ) 1 << 15 )        /* Pin Controlled by PA15 */
#وصف_ڪريو AT91C_PA15_NPCS03         ( ( بنانشان صحيح ) AT91C_PIO_PA15 ) /*  SPI 0 Peripheral Chip Select 3 */
#وصف_ڪريو AT91C_PA15_TCLK2          ( ( بنانشان صحيح ) AT91C_PIO_PA15 ) /*  Timer Counter 2 external clock input */
#وصف_ڪريو AT91C_PIO_PA16            ( ( بنانشان صحيح ) 1 << 16 )        /* Pin Controlled by PA16 */
#وصف_ڪريو AT91C_PA16_MISO0          ( ( بنانشان صحيح ) AT91C_PIO_PA16 ) /*  SPI 0 Master In Slave */
#وصف_ڪريو AT91C_PIO_PA17            ( ( بنانشان صحيح ) 1 << 17 )        /* Pin Controlled by PA17 */
#وصف_ڪريو AT91C_PA17_MOSI0          ( ( بنانشان صحيح ) AT91C_PIO_PA17 ) /*  SPI 0 Master Out Slave */
#وصف_ڪريو AT91C_PIO_PA18            ( ( بنانشان صحيح ) 1 << 18 )        /* Pin Controlled by PA18 */
#وصف_ڪريو AT91C_PA18_SPCK0          ( ( بنانشان صحيح ) AT91C_PIO_PA18 ) /*  SPI 0 Serial Clock */
#وصف_ڪريو AT91C_PIO_PA19            ( ( بنانشان صحيح ) 1 << 19 )        /* Pin Controlled by PA19 */
#وصف_ڪريو AT91C_PA19_CANRX          ( ( بنانشان صحيح ) AT91C_PIO_PA19 ) /*  CAN Receive */
#وصف_ڪريو AT91C_PIO_PA2             ( ( بنانشان صحيح ) 1 << 2 )         /* Pin Controlled by PA2 */
#وصف_ڪريو AT91C_PA2_SCK0            ( ( بنانشان صحيح ) AT91C_PIO_PA2 )  /*  USART 0 Serial Clock */
#وصف_ڪريو AT91C_PA2_NPCS11          ( ( بنانشان صحيح ) AT91C_PIO_PA2 )  /*  SPI 1 Peripheral Chip Select 1 */
#وصف_ڪريو AT91C_PIO_PA20            ( ( بنانشان صحيح ) 1 << 20 )        /* Pin Controlled by PA20 */
#وصف_ڪريو AT91C_PA20_CANTX          ( ( بنانشان صحيح ) AT91C_PIO_PA20 ) /*  CAN Transmit */
#وصف_ڪريو AT91C_PIO_PA21            ( ( بنانشان صحيح ) 1 << 21 )        /* Pin Controlled by PA21 */
#وصف_ڪريو AT91C_PA21_TF             ( ( بنانشان صحيح ) AT91C_PIO_PA21 ) /*  SSC Transmit Frame Sync */
#وصف_ڪريو AT91C_PA21_NPCS10         ( ( بنانشان صحيح ) AT91C_PIO_PA21 ) /*  SPI 1 Peripheral Chip Select 0 */
#وصف_ڪريو AT91C_PIO_PA22            ( ( بنانشان صحيح ) 1 << 22 )        /* Pin Controlled by PA22 */
#وصف_ڪريو AT91C_PA22_TK             ( ( بنانشان صحيح ) AT91C_PIO_PA22 ) /*  SSC Transmit Clock */
#وصف_ڪريو AT91C_PA22_SPCK1          ( ( بنانشان صحيح ) AT91C_PIO_PA22 ) /*  SPI 1 Serial Clock */
#وصف_ڪريو AT91C_PIO_PA23            ( ( بنانشان صحيح ) 1 << 23 )        /* Pin Controlled by PA23 */
#وصف_ڪريو AT91C_PA23_TD             ( ( بنانشان صحيح ) AT91C_PIO_PA23 ) /*  SSC Transmit data */
#وصف_ڪريو AT91C_PA23_MOSI1          ( ( بنانشان صحيح ) AT91C_PIO_PA23 ) /*  SPI 1 Master Out Slave */
#وصف_ڪريو AT91C_PIO_PA24            ( ( بنانشان صحيح ) 1 << 24 )        /* Pin Controlled by PA24 */
#وصف_ڪريو AT91C_PA24_RD             ( ( بنانشان صحيح ) AT91C_PIO_PA24 ) /*  SSC Receive Data */
#وصف_ڪريو AT91C_PA24_MISO1          ( ( بنانشان صحيح ) AT91C_PIO_PA24 ) /*  SPI 1 Master In Slave */
#وصف_ڪريو AT91C_PIO_PA25            ( ( بنانشان صحيح ) 1 << 25 )        /* Pin Controlled by PA25 */
#وصف_ڪريو AT91C_PA25_RK             ( ( بنانشان صحيح ) AT91C_PIO_PA25 ) /*  SSC Receive Clock */
#وصف_ڪريو AT91C_PA25_NPCS11         ( ( بنانشان صحيح ) AT91C_PIO_PA25 ) /*  SPI 1 Peripheral Chip Select 1 */
#وصف_ڪريو AT91C_PIO_PA26            ( ( بنانشان صحيح ) 1 << 26 )        /* Pin Controlled by PA26 */
#وصف_ڪريو AT91C_PA26_RF             ( ( بنانشان صحيح ) AT91C_PIO_PA26 ) /*  SSC Receive Frame Sync */
#وصف_ڪريو AT91C_PA26_NPCS12         ( ( بنانشان صحيح ) AT91C_PIO_PA26 ) /*  SPI 1 Peripheral Chip Select 2 */
#وصف_ڪريو AT91C_PIO_PA27            ( ( بنانشان صحيح ) 1 << 27 )        /* Pin Controlled by PA27 */
#وصف_ڪريو AT91C_PA27_DRXD           ( ( بنانشان صحيح ) AT91C_PIO_PA27 ) /*  DBGU Debug Receive Data */
#وصف_ڪريو AT91C_PA27_PCK3           ( ( بنانشان صحيح ) AT91C_PIO_PA27 ) /*  PMC Programmable Clock Output 3 */
#وصف_ڪريو AT91C_PIO_PA28            ( ( بنانشان صحيح ) 1 << 28 )        /* Pin Controlled by PA28 */
#وصف_ڪريو AT91C_PA28_DTXD           ( ( بنانشان صحيح ) AT91C_PIO_PA28 ) /*  DBGU Debug Transmit Data */
#وصف_ڪريو AT91C_PIO_PA29            ( ( بنانشان صحيح ) 1 << 29 )        /* Pin Controlled by PA29 */
#وصف_ڪريو AT91C_PA29_FIQ            ( ( بنانشان صحيح ) AT91C_PIO_PA29 ) /*  AIC Fast Interrupt Input */
#وصف_ڪريو AT91C_PA29_NPCS13         ( ( بنانشان صحيح ) AT91C_PIO_PA29 ) /*  SPI 1 Peripheral Chip Select 3 */
#وصف_ڪريو AT91C_PIO_PA3             ( ( بنانشان صحيح ) 1 << 3 )         /* Pin Controlled by PA3 */
#وصف_ڪريو AT91C_PA3_RTS0            ( ( بنانشان صحيح ) AT91C_PIO_PA3 )  /*  USART 0 Ready To Send */
#وصف_ڪريو AT91C_PA3_NPCS12          ( ( بنانشان صحيح ) AT91C_PIO_PA3 )  /*  SPI 1 Peripheral Chip Select 2 */
#وصف_ڪريو AT91C_PIO_PA30            ( ( بنانشان صحيح ) 1 << 30 )        /* Pin Controlled by PA30 */
#وصف_ڪريو AT91C_PA30_IRQ0           ( ( بنانشان صحيح ) AT91C_PIO_PA30 ) /*  External Interrupt 0 */
#وصف_ڪريو AT91C_PA30_PCK2           ( ( بنانشان صحيح ) AT91C_PIO_PA30 ) /*  PMC Programmable Clock Output 2 */
#وصف_ڪريو AT91C_PIO_PA4             ( ( بنانشان صحيح ) 1 << 4 )         /* Pin Controlled by PA4 */
#وصف_ڪريو AT91C_PA4_CTS0            ( ( بنانشان صحيح ) AT91C_PIO_PA4 )  /*  USART 0 Clear To Send */
#وصف_ڪريو AT91C_PA4_NPCS13          ( ( بنانشان صحيح ) AT91C_PIO_PA4 )  /*  SPI 1 Peripheral Chip Select 3 */
#وصف_ڪريو AT91C_PIO_PA5             ( ( بنانشان صحيح ) 1 << 5 )         /* Pin Controlled by PA5 */
#وصف_ڪريو AT91C_PA5_RXD1            ( ( بنانشان صحيح ) AT91C_PIO_PA5 )  /*  USART 1 Receive Data */
#وصف_ڪريو AT91C_PIO_PA6             ( ( بنانشان صحيح ) 1 << 6 )         /* Pin Controlled by PA6 */
#وصف_ڪريو AT91C_PA6_TXD1            ( ( بنانشان صحيح ) AT91C_PIO_PA6 )  /*  USART 1 Transmit Data */
#وصف_ڪريو AT91C_PIO_PA7             ( ( بنانشان صحيح ) 1 << 7 )         /* Pin Controlled by PA7 */
#وصف_ڪريو AT91C_PA7_SCK1            ( ( بنانشان صحيح ) AT91C_PIO_PA7 )  /*  USART 1 Serial Clock */
#وصف_ڪريو AT91C_PA7_NPCS01          ( ( بنانشان صحيح ) AT91C_PIO_PA7 )  /*  SPI 0 Peripheral Chip Select 1 */
#وصف_ڪريو AT91C_PIO_PA8             ( ( بنانشان صحيح ) 1 << 8 )         /* Pin Controlled by PA8 */
#وصف_ڪريو AT91C_PA8_RTS1            ( ( بنانشان صحيح ) AT91C_PIO_PA8 )  /*  USART 1 Ready To Send */
#وصف_ڪريو AT91C_PA8_NPCS02          ( ( بنانشان صحيح ) AT91C_PIO_PA8 )  /*  SPI 0 Peripheral Chip Select 2 */
#وصف_ڪريو AT91C_PIO_PA9             ( ( بنانشان صحيح ) 1 << 9 )         /* Pin Controlled by PA9 */
#وصف_ڪريو AT91C_PA9_CTS1            ( ( بنانشان صحيح ) AT91C_PIO_PA9 )  /*  USART 1 Clear To Send */
#وصف_ڪريو AT91C_PA9_NPCS03          ( ( بنانشان صحيح ) AT91C_PIO_PA9 )  /*  SPI 0 Peripheral Chip Select 3 */
#وصف_ڪريو AT91C_PIO_PB0             ( ( بنانشان صحيح ) 1 << 0 )         /* Pin Controlled by PB0 */
#وصف_ڪريو AT91C_PB0_ETXCK_EREFCK    ( ( بنانشان صحيح ) AT91C_PIO_PB0 )  /*  Ethernet MAC Transmit Clock/Reference Clock */
#وصف_ڪريو AT91C_PB0_PCK0            ( ( بنانشان صحيح ) AT91C_PIO_PB0 )  /*  PMC Programmable Clock Output 0 */
#وصف_ڪريو AT91C_PIO_PB1             ( ( بنانشان صحيح ) 1 << 1 )         /* Pin Controlled by PB1 */
#وصف_ڪريو AT91C_PB1_ETXEN           ( ( بنانشان صحيح ) AT91C_PIO_PB1 )  /*  Ethernet MAC Transmit Enable */
#وصف_ڪريو AT91C_PIO_PB10            ( ( بنانشان صحيح ) 1 << 10 )        /* Pin Controlled by PB10 */
#وصف_ڪريو AT91C_PB10_ETX2           ( ( بنانشان صحيح ) AT91C_PIO_PB10 ) /*  Ethernet MAC Transmit Data 2 */
#وصف_ڪريو AT91C_PB10_NPCS11         ( ( بنانشان صحيح ) AT91C_PIO_PB10 ) /*  SPI 1 Peripheral Chip Select 1 */
#وصف_ڪريو AT91C_PIO_PB11            ( ( بنانشان صحيح ) 1 << 11 )        /* Pin Controlled by PB11 */
#وصف_ڪريو AT91C_PB11_ETX3           ( ( بنانشان صحيح ) AT91C_PIO_PB11 ) /*  Ethernet MAC Transmit Data 3 */
#وصف_ڪريو AT91C_PB11_NPCS12         ( ( بنانشان صحيح ) AT91C_PIO_PB11 ) /*  SPI 1 Peripheral Chip Select 2 */
#وصف_ڪريو AT91C_PIO_PB12            ( ( بنانشان صحيح ) 1 << 12 )        /* Pin Controlled by PB12 */
#وصف_ڪريو AT91C_PB12_ETXER          ( ( بنانشان صحيح ) AT91C_PIO_PB12 ) /*  Ethernet MAC Transmit Coding Error */
#وصف_ڪريو AT91C_PB12_TCLK0          ( ( بنانشان صحيح ) AT91C_PIO_PB12 ) /*  Timer Counter 0 external clock input */
#وصف_ڪريو AT91C_PIO_PB13            ( ( بنانشان صحيح ) 1 << 13 )        /* Pin Controlled by PB13 */
#وصف_ڪريو AT91C_PB13_ERX2           ( ( بنانشان صحيح ) AT91C_PIO_PB13 ) /*  Ethernet MAC Receive Data 2 */
#وصف_ڪريو AT91C_PB13_NPCS01         ( ( بنانشان صحيح ) AT91C_PIO_PB13 ) /*  SPI 0 Peripheral Chip Select 1 */
#وصف_ڪريو AT91C_PIO_PB14            ( ( بنانشان صحيح ) 1 << 14 )        /* Pin Controlled by PB14 */
#وصف_ڪريو AT91C_PB14_ERX3           ( ( بنانشان صحيح ) AT91C_PIO_PB14 ) /*  Ethernet MAC Receive Data 3 */
#وصف_ڪريو AT91C_PB14_NPCS02         ( ( بنانشان صحيح ) AT91C_PIO_PB14 ) /*  SPI 0 Peripheral Chip Select 2 */
#وصف_ڪريو AT91C_PIO_PB15            ( ( بنانشان صحيح ) 1 << 15 )        /* Pin Controlled by PB15 */
#وصف_ڪريو AT91C_PB15_ERXDV          ( ( بنانشان صحيح ) AT91C_PIO_PB15 ) /*  Ethernet MAC Receive Data Valid */
#وصف_ڪريو AT91C_PIO_PB16            ( ( بنانشان صحيح ) 1 << 16 )        /* Pin Controlled by PB16 */
#وصف_ڪريو AT91C_PB16_ECOL           ( ( بنانشان صحيح ) AT91C_PIO_PB16 ) /*  Ethernet MAC Collision Detected */
#وصف_ڪريو AT91C_PB16_NPCS13         ( ( بنانشان صحيح ) AT91C_PIO_PB16 ) /*  SPI 1 Peripheral Chip Select 3 */
#وصف_ڪريو AT91C_PIO_PB17            ( ( بنانشان صحيح ) 1 << 17 )        /* Pin Controlled by PB17 */
#وصف_ڪريو AT91C_PB17_ERXCK          ( ( بنانشان صحيح ) AT91C_PIO_PB17 ) /*  Ethernet MAC Receive Clock */
#وصف_ڪريو AT91C_PB17_NPCS03         ( ( بنانشان صحيح ) AT91C_PIO_PB17 ) /*  SPI 0 Peripheral Chip Select 3 */
#وصف_ڪريو AT91C_PIO_PB18            ( ( بنانشان صحيح ) 1 << 18 )        /* Pin Controlled by PB18 */
#وصف_ڪريو AT91C_PB18_EF100          ( ( بنانشان صحيح ) AT91C_PIO_PB18 ) /*  Ethernet MAC Force 100 Mbits/sec */
#وصف_ڪريو AT91C_PB18_ADTRG          ( ( بنانشان صحيح ) AT91C_PIO_PB18 ) /*  ADC External Trigger */
#وصف_ڪريو AT91C_PIO_PB19            ( ( بنانشان صحيح ) 1 << 19 )        /* Pin Controlled by PB19 */
#وصف_ڪريو AT91C_PB19_PWM0           ( ( بنانشان صحيح ) AT91C_PIO_PB19 ) /*  PWM Channel 0 */
#وصف_ڪريو AT91C_PB19_TCLK1          ( ( بنانشان صحيح ) AT91C_PIO_PB19 ) /*  Timer Counter 1 external clock input */
#وصف_ڪريو AT91C_PIO_PB2             ( ( بنانشان صحيح ) 1 << 2 )         /* Pin Controlled by PB2 */
#وصف_ڪريو AT91C_PB2_ETX0            ( ( بنانشان صحيح ) AT91C_PIO_PB2 )  /*  Ethernet MAC Transmit Data 0 */
#وصف_ڪريو AT91C_PIO_PB20            ( ( بنانشان صحيح ) 1 << 20 )        /* Pin Controlled by PB20 */
#وصف_ڪريو AT91C_PB20_PWM1           ( ( بنانشان صحيح ) AT91C_PIO_PB20 ) /*  PWM Channel 1 */
#وصف_ڪريو AT91C_PB20_PCK0           ( ( بنانشان صحيح ) AT91C_PIO_PB20 ) /*  PMC Programmable Clock Output 0 */
#وصف_ڪريو AT91C_PIO_PB21            ( ( بنانشان صحيح ) 1 << 21 )        /* Pin Controlled by PB21 */
#وصف_ڪريو AT91C_PB21_PWM2           ( ( بنانشان صحيح ) AT91C_PIO_PB21 ) /*  PWM Channel 2 */
#وصف_ڪريو AT91C_PB21_PCK1           ( ( بنانشان صحيح ) AT91C_PIO_PB21 ) /*  PMC Programmable Clock Output 1 */
#وصف_ڪريو AT91C_PIO_PB22            ( ( بنانشان صحيح ) 1 << 22 )        /* Pin Controlled by PB22 */
#وصف_ڪريو AT91C_PB22_PWM3           ( ( بنانشان صحيح ) AT91C_PIO_PB22 ) /*  PWM Channel 3 */
#وصف_ڪريو AT91C_PB22_PCK2           ( ( بنانشان صحيح ) AT91C_PIO_PB22 ) /*  PMC Programmable Clock Output 2 */
#وصف_ڪريو AT91C_PIO_PB23            ( ( بنانشان صحيح ) 1 << 23 )        /* Pin Controlled by PB23 */
#وصف_ڪريو AT91C_PB23_TIOA0          ( ( بنانشان صحيح ) AT91C_PIO_PB23 ) /*  Timer Counter 0 Multipurpose Timer I/O Pin A */
#وصف_ڪريو AT91C_PB23_DCD1           ( ( بنانشان صحيح ) AT91C_PIO_PB23 ) /*  USART 1 Data Carrier Detect */
#وصف_ڪريو AT91C_PIO_PB24            ( ( بنانشان صحيح ) 1 << 24 )        /* Pin Controlled by PB24 */
#وصف_ڪريو AT91C_PB24_TIOB0          ( ( بنانشان صحيح ) AT91C_PIO_PB24 ) /*  Timer Counter 0 Multipurpose Timer I/O Pin B */
#وصف_ڪريو AT91C_PB24_DSR1           ( ( بنانشان صحيح ) AT91C_PIO_PB24 ) /*  USART 1 Data Set ready */
#وصف_ڪريو AT91C_PIO_PB25            ( ( بنانشان صحيح ) 1 << 25 )        /* Pin Controlled by PB25 */
#وصف_ڪريو AT91C_PB25_TIOA1          ( ( بنانشان صحيح ) AT91C_PIO_PB25 ) /*  Timer Counter 1 Multipurpose Timer I/O Pin A */
#وصف_ڪريو AT91C_PB25_DTR1           ( ( بنانشان صحيح ) AT91C_PIO_PB25 ) /*  USART 1 Data Terminal ready */
#وصف_ڪريو AT91C_PIO_PB26            ( ( بنانشان صحيح ) 1 << 26 )        /* Pin Controlled by PB26 */
#وصف_ڪريو AT91C_PB26_TIOB1          ( ( بنانشان صحيح ) AT91C_PIO_PB26 ) /*  Timer Counter 1 Multipurpose Timer I/O Pin B */
#وصف_ڪريو AT91C_PB26_RI1            ( ( بنانشان صحيح ) AT91C_PIO_PB26 ) /*  USART 1 Ring Indicator */
#وصف_ڪريو AT91C_PIO_PB27            ( ( بنانشان صحيح ) 1 << 27 )        /* Pin Controlled by PB27 */
#وصف_ڪريو AT91C_PB27_TIOA2          ( ( بنانشان صحيح ) AT91C_PIO_PB27 ) /*  Timer Counter 2 Multipurpose Timer I/O Pin A */
#وصف_ڪريو AT91C_PB27_PWM0           ( ( بنانشان صحيح ) AT91C_PIO_PB27 ) /*  PWM Channel 0 */
#وصف_ڪريو AT91C_PIO_PB28            ( ( بنانشان صحيح ) 1 << 28 )        /* Pin Controlled by PB28 */
#وصف_ڪريو AT91C_PB28_TIOB2          ( ( بنانشان صحيح ) AT91C_PIO_PB28 ) /*  Timer Counter 2 Multipurpose Timer I/O Pin B */
#وصف_ڪريو AT91C_PB28_PWM1           ( ( بنانشان صحيح ) AT91C_PIO_PB28 ) /*  PWM Channel 1 */
#وصف_ڪريو AT91C_PIO_PB29            ( ( بنانشان صحيح ) 1 << 29 )        /* Pin Controlled by PB29 */
#وصف_ڪريو AT91C_PB29_PCK1           ( ( بنانشان صحيح ) AT91C_PIO_PB29 ) /*  PMC Programmable Clock Output 1 */
#وصف_ڪريو AT91C_PB29_PWM2           ( ( بنانشان صحيح ) AT91C_PIO_PB29 ) /*  PWM Channel 2 */
#وصف_ڪريو AT91C_PIO_PB3             ( ( بنانشان صحيح ) 1 << 3 )         /* Pin Controlled by PB3 */
#وصف_ڪريو AT91C_PB3_ETX1            ( ( بنانشان صحيح ) AT91C_PIO_PB3 )  /*  Ethernet MAC Transmit Data 1 */
#وصف_ڪريو AT91C_PIO_PB30            ( ( بنانشان صحيح ) 1 << 30 )        /* Pin Controlled by PB30 */
#وصف_ڪريو AT91C_PB30_PCK2           ( ( بنانشان صحيح ) AT91C_PIO_PB30 ) /*  PMC Programmable Clock Output 2 */
#وصف_ڪريو AT91C_PB30_PWM3           ( ( بنانشان صحيح ) AT91C_PIO_PB30 ) /*  PWM Channel 3 */
#وصف_ڪريو AT91C_PIO_PB4             ( ( بنانشان صحيح ) 1 << 4 )         /* Pin Controlled by PB4 */
#وصف_ڪريو AT91C_PB4_ECRS_ECRSDV     ( ( بنانشان صحيح ) AT91C_PIO_PB4 )  /*  Ethernet MAC Carrier Sense/Carrier Sense and Data Valid */
#وصف_ڪريو AT91C_PIO_PB5             ( ( بنانشان صحيح ) 1 << 5 )         /* Pin Controlled by PB5 */
#وصف_ڪريو AT91C_PB5_ERX0            ( ( بنانشان صحيح ) AT91C_PIO_PB5 )  /*  Ethernet MAC Receive Data 0 */
#وصف_ڪريو AT91C_PIO_PB6             ( ( بنانشان صحيح ) 1 << 6 )         /* Pin Controlled by PB6 */
#وصف_ڪريو AT91C_PB6_ERX1            ( ( بنانشان صحيح ) AT91C_PIO_PB6 )  /*  Ethernet MAC Receive Data 1 */
#وصف_ڪريو AT91C_PIO_PB7             ( ( بنانشان صحيح ) 1 << 7 )         /* Pin Controlled by PB7 */
#وصف_ڪريو AT91C_PB7_ERXER           ( ( بنانشان صحيح ) AT91C_PIO_PB7 )  /*  Ethernet MAC Receive Error */
#وصف_ڪريو AT91C_PIO_PB8             ( ( بنانشان صحيح ) 1 << 8 )         /* Pin Controlled by PB8 */
#وصف_ڪريو AT91C_PB8_EMDC            ( ( بنانشان صحيح ) AT91C_PIO_PB8 )  /*  Ethernet MAC Management Data Clock */
#وصف_ڪريو AT91C_PIO_PB9             ( ( بنانشان صحيح ) 1 << 9 )         /* Pin Controlled by PB9 */
#وصف_ڪريو AT91C_PB9_EMDIO           ( ( بنانشان صحيح ) AT91C_PIO_PB9 )  /*  Ethernet MAC Management Data Input/Output */

/* ***************************************************************************** */
/*               PERIPHERAL ID DEFINITIONS FOR AT91SAM7X256 */
/* ***************************************************************************** */
#وصف_ڪريو AT91C_ID_FIQ            ( ( بنانشان صحيح ) 0 )  /* Advanced Interrupt Controller (FIQ) */
#وصف_ڪريو AT91C_ID_SYS            ( ( بنانشان صحيح ) 1 )  /* System Peripheral */
#وصف_ڪريو AT91C_ID_PIOA           ( ( بنانشان صحيح ) 2 )  /* Parallel IO Controller A */
#وصف_ڪريو AT91C_ID_PIOB           ( ( بنانشان صحيح ) 3 )  /* Parallel IO Controller B */
#وصف_ڪريو AT91C_ID_SPI0           ( ( بنانشان صحيح ) 4 )  /* Serial Peripheral Interface 0 */
#وصف_ڪريو AT91C_ID_SPI1           ( ( بنانشان صحيح ) 5 )  /* Serial Peripheral Interface 1 */
#وصف_ڪريو AT91C_ID_US0            ( ( بنانشان صحيح ) 6 )  /* USART 0 */
#وصف_ڪريو AT91C_ID_US1            ( ( بنانشان صحيح ) 7 )  /* USART 1 */
#وصف_ڪريو AT91C_ID_SSC            ( ( بنانشان صحيح ) 8 )  /* Serial Synchronous Controller */
#وصف_ڪريو AT91C_ID_TWI            ( ( بنانشان صحيح ) 9 )  /* Two-Wire Interface */
#وصف_ڪريو AT91C_ID_PWMC           ( ( بنانشان صحيح ) 10 ) /* PWM Controller */
#وصف_ڪريو AT91C_ID_UDP            ( ( بنانشان صحيح ) 11 ) /* USB Device Port */
#وصف_ڪريو AT91C_ID_TC0            ( ( بنانشان صحيح ) 12 ) /* Timer Counter 0 */
#وصف_ڪريو AT91C_ID_TC1            ( ( بنانشان صحيح ) 13 ) /* Timer Counter 1 */
#وصف_ڪريو AT91C_ID_TC2            ( ( بنانشان صحيح ) 14 ) /* Timer Counter 2 */
#وصف_ڪريو AT91C_ID_CAN            ( ( بنانشان صحيح ) 15 ) /* Control Area Network Controller */
#وصف_ڪريو AT91C_ID_EMAC           ( ( بنانشان صحيح ) 16 ) /* Ethernet MAC */
#وصف_ڪريو AT91C_ID_ADC            ( ( بنانشان صحيح ) 17 ) /* Analog-to-Digital Converter */
#وصف_ڪريو AT91C_ID_AES            ( ( بنانشان صحيح ) 18 ) /* Advanced Encryption Standard 128-bit */
#وصف_ڪريو AT91C_ID_TDES           ( ( بنانشان صحيح ) 19 ) /* Triple Data Encryption Standard */
#وصف_ڪريو AT91C_ID_20_Reserved    ( ( بنانشان صحيح ) 20 ) /* Reserved */
#وصف_ڪريو AT91C_ID_21_Reserved    ( ( بنانشان صحيح ) 21 ) /* Reserved */
#وصف_ڪريو AT91C_ID_22_Reserved    ( ( بنانشان صحيح ) 22 ) /* Reserved */
#وصف_ڪريو AT91C_ID_23_Reserved    ( ( بنانشان صحيح ) 23 ) /* Reserved */
#وصف_ڪريو AT91C_ID_24_Reserved    ( ( بنانشان صحيح ) 24 ) /* Reserved */
#وصف_ڪريو AT91C_ID_25_Reserved    ( ( بنانشان صحيح ) 25 ) /* Reserved */
#وصف_ڪريو AT91C_ID_26_Reserved    ( ( بنانشان صحيح ) 26 ) /* Reserved */
#وصف_ڪريو AT91C_ID_27_Reserved    ( ( بنانشان صحيح ) 27 ) /* Reserved */
#وصف_ڪريو AT91C_ID_28_Reserved    ( ( بنانشان صحيح ) 28 ) /* Reserved */
#وصف_ڪريو AT91C_ID_29_Reserved    ( ( بنانشان صحيح ) 29 ) /* Reserved */
#وصف_ڪريو AT91C_ID_IRQ0           ( ( بنانشان صحيح ) 30 ) /* Advanced Interrupt Controller (IRQ0) */
#وصف_ڪريو AT91C_ID_IRQ1           ( ( بنانشان صحيح ) 31 ) /* Advanced Interrupt Controller (IRQ1) */

/* ***************************************************************************** */
/*               BASE ADDRESS DEFINITIONS FOR AT91SAM7X256 */
/* ***************************************************************************** */
#وصف_ڪريو AT91_C_بنياد_SYS         ( ( AT91PS_SYS ) 0xFFFFF000 )     /* (SYS) Base Address */
#وصف_ڪريو AT91_C_بنياد_AIC         ( ( AT91PS_AIC ) 0xFFFFF000 )     /* (AIC) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_DBGU    ( ( AT91PS_PDC ) 0xFFFFF300 )     /* (PDC_DBGU) Base Address */
#وصف_ڪريو AT91_C_بنياد_DBGU        ( ( AT91PS_DBGU ) 0xFFFFF200 )    /* (DBGU) Base Address */
#وصف_ڪريو AT91_C_بنياد_PIOA        ( ( AT91PS_PIO ) 0xFFFFF400 )     /* (PIOA) Base Address */
#وصف_ڪريو AT91_C_بنياد_PIOB        ( ( AT91PS_PIO ) 0xFFFFF600 )     /* (PIOB) Base Address */
#وصف_ڪريو AT91_C_بنياد_CKGR        ( ( AT91PS_CKGR ) 0xFFFFFC20 )    /* (CKGR) Base Address */
#وصف_ڪريو AT91_C_بنياد_PMC         ( ( AT91PS_PMC ) 0xFFFFFC00 )     /* (PMC) Base Address */
#وصف_ڪريو AT91_C_بنياد_RSTC        ( ( AT91PS_RSTC ) 0xFFFFFD00 )    /* (RSTC) Base Address */
#وصف_ڪريو AT91_C_بنياد_RTTC        ( ( AT91PS_RTTC ) 0xFFFFFD20 )    /* (RTTC) Base Address */
#وصف_ڪريو AT91_C_بنياد_PITC        ( ( AT91PS_PITC ) 0xFFFFFD30 )    /* (PITC) Base Address */
#وصف_ڪريو AT91_C_بنياد_WDTC        ( ( AT91PS_WDTC ) 0xFFFFFD40 )    /* (WDTC) Base Address */
#وصف_ڪريو AT91_C_بنياد_VREG        ( ( AT91PS_VREG ) 0xFFFFFD60 )    /* (VREG) Base Address */
#وصف_ڪريو AT91_C_بنياد_MC          ( ( AT91PS_MC ) 0xFFFFFF00 )      /* (MC) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_SPI1    ( ( AT91PS_PDC ) 0xFFFE4100 )     /* (PDC_SPI1) Base Address */
#وصف_ڪريو AT91_C_بنياد_SPI1        ( ( AT91PS_SPI ) 0xFFFE4000 )     /* (SPI1) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_SPI0    ( ( AT91PS_PDC ) 0xFFFE0100 )     /* (PDC_SPI0) Base Address */
#وصف_ڪريو AT91_C_بنياد_SPI0        ( ( AT91PS_SPI ) 0xFFFE0000 )     /* (SPI0) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_US1     ( ( AT91PS_PDC ) 0xFFFC4100 )     /* (PDC_US1) Base Address */
#وصف_ڪريو AT91_C_بنياد_US1         ( ( AT91PS_USART ) 0xFFFC4000 )   /* (US1) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_US0     ( ( AT91PS_PDC ) 0xFFFC0100 )     /* (PDC_US0) Base Address */
#وصف_ڪريو AT91_C_بنياد_US0         ( ( AT91PS_USART ) 0xFFFC0000 )   /* (US0) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_SSC     ( ( AT91PS_PDC ) 0xFFFD4100 )     /* (PDC_SSC) Base Address */
#وصف_ڪريو AT91_C_بنياد_SSC         ( ( AT91PS_SSC ) 0xFFFD4000 )     /* (SSC) Base Address */
#وصف_ڪريو AT91_C_بنياد_TWI         ( ( AT91PS_TWI ) 0xFFFB8000 )     /* (TWI) Base Address */
#وصف_ڪريو AT91_C_بنياد_PWMC_CH3    ( ( AT91PS_PWMC_CH ) 0xFFFCC260 ) /* (PWMC_CH3) Base Address */
#وصف_ڪريو AT91_C_بنياد_PWMC_CH2    ( ( AT91PS_PWMC_CH ) 0xFFFCC240 ) /* (PWMC_CH2) Base Address */
#وصف_ڪريو AT91_C_بنياد_PWMC_CH1    ( ( AT91PS_PWMC_CH ) 0xFFFCC220 ) /* (PWMC_CH1) Base Address */
#وصف_ڪريو AT91_C_بنياد_PWMC_CH0    ( ( AT91PS_PWMC_CH ) 0xFFFCC200 ) /* (PWMC_CH0) Base Address */
#وصف_ڪريو AT91_C_بنياد_PWMC        ( ( AT91PS_PWMC ) 0xFFFCC000 )    /* (PWMC) Base Address */
#وصف_ڪريو AT91_C_بنياد_UDP         ( ( AT91PS_UDP ) 0xFFFB0000 )     /* (UDP) Base Address */
#وصف_ڪريو AT91_C_بنياد_TC0         ( ( AT91PS_TC ) 0xFFFA0000 )      /* (TC0) Base Address */
#وصف_ڪريو AT91_C_بنياد_TC1         ( ( AT91PS_TC ) 0xFFFA0040 )      /* (TC1) Base Address */
#وصف_ڪريو AT91_C_بنياد_TC2         ( ( AT91PS_TC ) 0xFFFA0080 )      /* (TC2) Base Address */
#وصف_ڪريو AT91_C_بنياد_TCB         ( ( AT91PS_TCB ) 0xFFFA0000 )     /* (TCB) Base Address */
#وصف_ڪريو AT91_C_بنياد_CAN_MB0     ( ( AT91PS_CAN_MB ) 0xFFFD0200 )  /* (CAN_MB0) Base Address */
#وصف_ڪريو AT91_C_بنياد_CAN_MB1     ( ( AT91PS_CAN_MB ) 0xFFFD0220 )  /* (CAN_MB1) Base Address */
#وصف_ڪريو AT91_C_بنياد_CAN_MB2     ( ( AT91PS_CAN_MB ) 0xFFFD0240 )  /* (CAN_MB2) Base Address */
#وصف_ڪريو AT91_C_بنياد_CAN_MB3     ( ( AT91PS_CAN_MB ) 0xFFFD0260 )  /* (CAN_MB3) Base Address */
#وصف_ڪريو AT91_C_بنياد_CAN_MB4     ( ( AT91PS_CAN_MB ) 0xFFFD0280 )  /* (CAN_MB4) Base Address */
#وصف_ڪريو AT91_C_بنياد_CAN_MB5     ( ( AT91PS_CAN_MB ) 0xFFFD02A0 )  /* (CAN_MB5) Base Address */
#وصف_ڪريو AT91_C_بنياد_CAN_MB6     ( ( AT91PS_CAN_MB ) 0xFFFD02C0 )  /* (CAN_MB6) Base Address */
#وصف_ڪريو AT91_C_بنياد_CAN_MB7     ( ( AT91PS_CAN_MB ) 0xFFFD02E0 )  /* (CAN_MB7) Base Address */
#وصف_ڪريو AT91_C_بنياد_CAN         ( ( AT91PS_CAN ) 0xFFFD0000 )     /* (CAN) Base Address */
#وصف_ڪريو AT91_C_بنياد_EMAC        ( ( AT91PS_EMAC ) 0xFFFDC000 )    /* (EMAC) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_ADC     ( ( AT91PS_PDC ) 0xFFFD8100 )     /* (PDC_ADC) Base Address */
#وصف_ڪريو AT91_C_بنياد_ADC         ( ( AT91PS_ADC ) 0xFFFD8000 )     /* (ADC) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_AES     ( ( AT91PS_PDC ) 0xFFFA4100 )     /* (PDC_AES) Base Address */
#وصف_ڪريو AT91_C_بنياد_AES         ( ( AT91PS_AES ) 0xFFFA4000 )     /* (AES) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_TDES    ( ( AT91PS_PDC ) 0xFFFA8100 )     /* (PDC_TDES) Base Address */
#وصف_ڪريو AT91_C_بنياد_TDES        ( ( AT91PS_TDES ) 0xFFFA8000 )    /* (TDES) Base Address */

/* ***************************************************************************** */
/*               MEMORY MAPPING DEFINITIONS FOR AT91SAM7X256 */
/* ***************************************************************************** */
#وصف_ڪريو AT91C_ISRAM          ( ( حرف * ) 0x00200000 )       /* Internal SRAM base address */
#وصف_ڪريو AT91_C_ISRAM_سائيز     ( ( بنانشان صحيح ) 0x00010000 ) /* Internal SRAM size in byte (64 Kbyte) */
#وصف_ڪريو AT91C_IFLASH         ( ( حرف * ) 0x00100000 )       /* Internal ROM base address */
#وصف_ڪريو AT91_C_IFLASH_سائيز    ( ( بنانشان صحيح ) 0x00040000 ) /* Internal ROM size in byte (256 Kbyte) */



/* - Hardware register definition */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR System Peripherals */
/* - ***************************************************************************** */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Advanced Interrupt Controller */
/* - ***************************************************************************** */
/* - -------- AIC_SMR : (AIC Offset: 0x0) Control Register -------- */
#إذا 0 /*_RB_*/
    AT91_C_AIC_اڳواٽ EQU( 0x7 << 0 );
    -( AIC ) ترجيح_2 Level
    AT91_C_AIC_اڳواٽ_سڀ_کان_هيٺ EQU( 0x0 );
    -( AIC ) سڀ_کان_هيٺ ترجيح level
    AT91_C_AIC_اڳواٽ_HIGHEST EQU( 0x7 );
    -( AIC ) Highest ترجيح level
    AT91C_AIC_SRCTYPE EQU( 0x3 << 5 );
    -( AIC ) مداخلت_2 ذريعو_2 Type
    AT91_C_AIC_SRCTYPE_INT_مٿاهون_LEVEL EQU( 0x0 << 5 );
    -( AIC ) اندروني Sources ڪوڊ_2 Label مٿاهون - level Sensitive
    AT91_C_AIC_SRCTYPE_EXT_هيٺيون_LEVEL EQU( 0x0 << 5 );
    -( AIC ) External Sources ڪوڊ_2 Label هيٺيون - level Sensitive
    AT91_C_AIC_SRCTYPE_INT_مثبت_ڪنارو EQU( 0x1 << 5 );
    -( AIC ) اندروني Sources ڪوڊ_2 Label مثبت ڪنارو triggered
    AT91_C_AIC_SRCTYPE_EXT_NEGATIVE_ڪنارو EQU( 0x1 << 5 );
    -( AIC ) External Sources ڪوڊ_2 Label Negative ڪنارو triggered
    AT91_C_AIC_SRCTYPE_مٿاهون_LEVEL EQU( 0x2 << 5 );
    -( AIC ) اندروني Or External Sources ڪوڊ_2 Label مٿاهون - level Sensitive
    AT91_C_AIC_SRCTYPE_مثبت_ڪنارو EQU( 0x3 << 5 );
    -( AIC ) اندروني Or External Sources ڪوڊ_2 Label مثبت ڪنارو triggered
/* - -------- AIC_CISR : (AIC Offset: 0x114) AIC Core Interrupt Status Register -------- */
    AT91C_AIC_NFIQ EQU( 0x1 << 0 );
    -( AIC ) NFIQ حالت
    AT91C_AIC_NIRQ EQU( 0x1 << 1 );
    -( AIC ) NIRQ حالت
/* - -------- AIC_DCR : (AIC Offset: 0x138) AIC Debug Control Register (Protect) -------- */
    AT91C_AIC_DCR_PROT EQU( 0x1 << 0 );
    -( AIC ) Protection گهڻائي
    AT91C_AIC_DCR_GMSK EQU( 0x1 << 1 );
    -( AIC ) General نقاب_2
#جيڪڏهن_پورو /* if 0 */
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
-( DBGU ) Reset حالت بٽ
/* - -------- DBGU_MR : (DBGU Offset: 0x4) Debug Unit Mode Register -------- */
AT91C_US_PAR EQU( 0x7 << 9 );
-( DBGU ) Parity type
AT91C_US_PAR_EVEN EQU( 0x0 << 9 );
-( DBGU ) Even Parity
AT91C_US_PAR_ODD EQU( 0x1 << 9 );
-( DBGU ) Odd Parity
AT91C_US_PAR_SPACE EQU( 0x2 << 9 );
-( DBGU ) Parity forced منزل 0 ( Space )
AT91C_US_PAR_MARK EQU( 0x3 << 9 );
-( DBGU ) Parity forced منزل 1 ( Mark )
AT91C_US_PAR_NONE EQU( 0x4 << 9 );
-( DBGU ) No Parity
AT91C_US_PAR_MULTI_DROP EQU( 0x6 << 9 );
-( DBGU ) Multi - drop گهڻائي_2
AT91C_US_CHMODE EQU( 0x3 << 14 );
-( DBGU ) Channel گهڻائي
AT91_C_US_CHMODE_عام EQU( 0x0 << 14 );
-( DBGU ) عام_2 گهڻائي: The USART channel operates as an RX / TX USART.
   AT91C_US_CHMODE_AUTO EQU( 0x1 << 14 );
-( DBGU ) Automatic Echo: Receiver معلومات داخلا is connected منزل the TXD pin.
   AT91C_US_CHMODE_LOCAL EQU( 0x2 << 14 );
-( DBGU ) Local Loopback: Transmitter Output Signal is connected منزل Receiver داخلا Signal.
   AT91C_US_CHMODE_REMOTE EQU( 0x3 << 14 );
-( DBGU ) Remote Loopback: RXD pin is internally connected منزل TXD pin.
/* - -------- DBGU_IER : (DBGU Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
   AT91C_US_RXRDY EQU( 0x1 << 0 );
-( DBGU ) RXRDY مداخلت_2
AT91C_US_TXRDY EQU( 0x1 << 1 );
-( DBGU ) TXRDY مداخلت_2
AT91C_US_ENDRX EQU( 0x1 << 3 );
-( DBGU ) پڇاڙي_2 جو Receive Transfer مداخلت_2
AT91C_US_ENDTX EQU( 0x1 << 4 );
-( DBGU ) پڇاڙي_2 جو Transmit مداخلت_2
AT91C_US_OVRE EQU( 0x1 << 5 );
-( DBGU ) Overrun مداخلت_2
AT91_C_US_چوکٺو EQU( 0x1 << 6 );
-( DBGU ) Framing Error مداخلت_2
AT91C_US_PARE EQU( 0x1 << 7 );
-( DBGU ) Parity Error مداخلت_2
AT91C_US_TXEMPTY EQU( 0x1 << 9 );
-( DBGU ) TXEMPTY مداخلت_2
AT91C_US_TXBUFE EQU( 0x1 << 11 );
-( DBGU ) TXBUFE مداخلت_2
AT91C_US_RXBUFF EQU( 0x1 << 12 );
-( DBGU ) RXBUFF مداخلت_2
AT91C_US_COMM_TX EQU( 0x1 << 30 );
-( DBGU ) COMM_TX مداخلت_2
AT91C_US_COMM_RX EQU( 0x1 << 31 );
-( DBGU ) COMM_RX مداخلت_2
/* - -------- DBGU_IDR : (DBGU Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* - -------- DBGU_IMR : (DBGU Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* - -------- DBGU_CSR : (DBGU Offset: 0x14) Debug Unit Channel Status Register -------- */
/* - -------- DBGU_FNTR : (DBGU Offset: 0x48) Debug Unit FORCE_NTRST Register -------- */
AT91C_US_FORCE_NTRST EQU( 0x1 << 0 );
-( DBGU ) Force NTRST اندريون JTAG

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
-( CKGR ) Main Oscillator شروعات_2 - مٿي وقت
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
AT91_C_CKGR_ٻاهريون EQU( 0x3 << 14 );
-( CKGR ) PLL Output Frequency Range
AT91_C_CKGR_ٻاهريون_0 EQU( 0x0 << 14 );
-( CKGR ) Please refer منزل the PLL datasheet
AT91_C_CKGR_ٻاهريون_1 EQU( 0x1 << 14 );
-( CKGR ) Please refer منزل the PLL datasheet
AT91_C_CKGR_ٻاهريون_2 EQU( 0x2 << 14 );
-( CKGR ) Please refer منزل the PLL datasheet
AT91_C_CKGR_ٻاهريون_3 EQU( 0x3 << 14 );
-( CKGR ) Please refer منزل the PLL datasheet
AT91C_CKGR_MUL EQU( 0x7FF << 16 );
-( CKGR ) PLL Multiplier
AT91C_CKGR_USBDIV EQU( 0x3 << 28 );
-( CKGR ) Divider

لكل USB Clocks
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
-( PMC ) USB Device پورٽ_2 Clock
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
-( PMC ) MOSC حالت / Enable / Disable / نقاب_2
AT91_C_PMC_تالو EQU( 0x1 << 2 );
-( PMC ) PLL حالت / Enable / Disable / نقاب_2
AT91C_PMC_MCKRDY EQU( 0x1 << 3 );
-( PMC ) MCK_RDY حالت / Enable / Disable / نقاب_2
AT91C_PMC_PCK0RDY EQU( 0x1 << 8 );
-( PMC ) PCK0_RDY حالت / Enable / Disable / نقاب_2
AT91C_PMC_PCK1RDY EQU( 0x1 << 9 );
-( PMC ) PCK1_RDY حالت / Enable / Disable / نقاب_2
AT91C_PMC_PCK2RDY EQU( 0x1 << 10 );
-( PMC ) PCK2_RDY حالت / Enable / Disable / نقاب_2
AT91C_PMC_PCK3RDY EQU( 0x1 << 11 );
-( PMC ) PCK3_RDY حالت / Enable / Disable / نقاب_2
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
AT91_C_RSTC_ڪنجي EQU( 0xFF << 24 );
-( RSTC ) Password
/* - -------- RSTC_RSR : (RSTC Offset: 0x4) Reset Status Register -------- */
AT91C_RSTC_URSTS EQU( 0x1 << 0 );
-( RSTC ) User Reset حالت
AT91C_RSTC_BODSTS EQU( 0x1 << 1 );
-( RSTC ) Brownout Detection حالت
AT91C_RSTC_RSTTYP EQU( 0x7 << 8 );
-( RSTC ) Reset Type
AT91C_RSTC_RSTTYP_POWERUP EQU( 0x0 << 8 );
-( RSTC ) Power - مٿي Reset.VDDCORE rising.
   AT91C_RSTC_RSTTYP_WAKEUP EQU( 0x1 << 8 );
-( RSTC ) Wake_مٿي Reset.VDDCORE rising.
   AT91C_RSTC_RSTTYP_WATCHDOG EQU( 0x2 << 8 );
-( RSTC ) Watchdog Reset.Watchdog حد_کان_مٿي occurred.
   AT91C_RSTC_RSTTYP_SOFTWARE EQU( 0x3 << 8 );
-( RSTC ) Software Reset.Processor reset required by the software.
   AT91C_RSTC_RSTTYP_USER EQU( 0x4 << 8 );
-( RSTC ) User Reset.NRST pin detected هيٺيون_2.
   AT91C_RSTC_RSTTYP_BROWNOUT EQU( 0x5 << 8 );
-( RSTC ) Brownout Reset occurred.
   AT91C_RSTC_NRSTL EQU( 0x1 << 16 );
-( RSTC ) NRST pin level
AT91C_RSTC_SRCMP EQU( 0x1 << 17 );
-( RSTC ) Software Reset Command اندريون ترقي.
/* - -------- RSTC_RMR : (RSTC Offset: 0x8) Reset Mode Register -------- */
   AT91C_RSTC_URSTEN EQU( 0x1 << 0 );
-( RSTC ) User Reset Enable
AT91C_RSTC_URSTIEN EQU( 0x1 << 4 );
-( RSTC ) User Reset مداخلت_2 Enable
AT91C_RSTC_ERSTL EQU( 0xF << 8 );
-( RSTC ) User Reset Enable
AT91C_RSTC_BODIEN EQU( 0x1 << 16 );
-( RSTC ) Brownout Detection مداخلت_2 Enable

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Real Time Timer Controller Interface */
/* - ***************************************************************************** */
/* - -------- RTTC_RTMR : (RTTC Offset: 0x0) Real-time Mode Register -------- */
AT91C_RTTC_RTPRES EQU( 0xFFFF << 0 );
-( RTTC ) Real - time Timer Prescaler قدر_2
AT91C_RTTC_ALMIEN EQU( 0x1 << 16 );
-( RTTC ) Alarm مداخلت_2 Enable
AT91C_RTTC_RTTINCIEN EQU( 0x1 << 17 );
-( RTTC ) Real وقت Timer Increment مداخلت_2 Enable
AT91C_RTTC_RTTRST EQU( 0x1 << 18 );
-( RTTC ) Real وقت Timer Restart
/* - -------- RTTC_RTAR : (RTTC Offset: 0x4) Real-time Alarm Register -------- */
AT91C_RTTC_ALMV EQU( 0x0 << 0 );
-( RTTC ) Alarm قدر_2
/* - -------- RTTC_RTVR : (RTTC Offset: 0x8) Current Real-time Value Register -------- */
AT91C_RTTC_CRTV EQU( 0x0 << 0 );
-( RTTC ) Current Real - time قدر_2
/* - -------- RTTC_RTSR : (RTTC Offset: 0xc) Real-time Status Register -------- */
AT91C_RTTC_ALMS EQU( 0x1 << 0 );
-( RTTC ) Real - time Alarm حالت
AT91C_RTTC_RTTINC EQU( 0x1 << 1 );
-( RTTC ) Real - time Timer Increment

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Periodic Interval Timer Controller Interface */
/* - ***************************************************************************** */
/* - -------- PITC_PIMR : (PITC Offset: 0x0) Periodic Interval Mode Register -------- */
AT91C_PITC_PIV EQU( 0xFFFFF << 0 );
-( PITC ) Periodic Interval قدر_2
AT91C_PITC_PITEN EQU( 0x1 << 24 );
-( PITC ) Periodic Interval Timer Enabled
AT91C_PITC_PITIEN EQU( 0x1 << 25 );
-( PITC ) Periodic Interval Timer مداخلت_2 Enable
/* - -------- PITC_PISR : (PITC Offset: 0x4) Periodic Interval Status Register -------- */
AT91C_PITC_PITS EQU( 0x1 << 0 );
-( PITC ) Periodic Interval Timer حالت
/* - -------- PITC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register -------- */
AT91C_PITC_CPIV EQU( 0xFFFFF << 0 );
-( PITC ) Current Periodic Interval قدر_2
AT91C_PITC_PICNT EQU( 0xFFF << 20 );
-( PITC ) Periodic Interval Counter
/* - -------- PITC_PIIR : (PITC Offset: 0xc) Periodic Interval Image Register -------- */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Watchdog Timer Controller Interface */
/* - ***************************************************************************** */
/* - -------- WDTC_WDCR : (WDTC Offset: 0x0) Periodic Interval Image Register -------- */
AT91C_WDTC_WDRSTT EQU( 0x1 << 0 );
-( WDTC ) Watchdog Restart
AT91_C_WDTC_ڪنجي EQU( 0xFF << 24 );
-( WDTC ) Watchdog ڪنجي Password
/* - -------- WDTC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register -------- */
AT91C_WDTC_WDV EQU( 0xFFF << 0 );
-( WDTC ) Watchdog Timer Restart
AT91C_WDTC_WDFIEN EQU( 0x1 << 12 );
-( WDTC ) Watchdog Fault مداخلت_2 Enable
AT91C_WDTC_WDRSTEN EQU( 0x1 << 13 );
-( WDTC ) Watchdog Reset Enable
AT91C_WDTC_WDRPROC EQU( 0x1 << 14 );
-( WDTC ) Watchdog Timer Restart
AT91C_WDTC_WDDIS EQU( 0x1 << 15 );
-( WDTC ) Watchdog Disable
AT91C_WDTC_WDD EQU( 0xFFF << 16 );
-( WDTC ) Watchdog Delta قدر_2
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
-( VREG ) Voltage Regulator Power Standby گهڻائي

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Memory Controller Interface */
/* - ***************************************************************************** */
/* - -------- MC_RCR : (MC Offset: 0x0) MC Remap Control Register -------- */
AT91C_MC_RCB EQU( 0x1 << 0 );
-( MC ) Remap Command ٻٽو_انگ
/* - -------- MC_ASR : (MC Offset: 0x4) MC Abort Status Register -------- */
AT91C_MC_UNDADD EQU( 0x1 << 0 );
-( MC ) Undefined پتو Abort حالت
AT91C_MC_MISADD EQU( 0x1 << 1 );
-( MC ) Misaligned پتو Abort حالت
AT91C_MC_ABTSZ EQU( 0x3 << 8 );
-( MC ) Abort سائيز_2 حالت
AT91C_MC_ABTSZ_BYTE EQU( 0x0 << 8 );
-( MC ) Byte
AT91C_MC_ABTSZ_HWORD EQU( 0x1 << 8 );
-( MC ) Half - لفظ_2
AT91_C_MC_ABTSZ_لفظ EQU( 0x2 << 8 );
-( MC ) لفظ_3
AT91C_MC_ABTTYP EQU( 0x3 << 10 );
-( MC ) Abort Type حالت
AT91C_MC_ABTTYP_DATAR EQU( 0x0 << 10 );
-( MC ) معلومات Read
AT91C_MC_ABTTYP_DATAW EQU( 0x1 << 10 );
-( MC ) معلومات Write
AT91C_MC_ABTTYP_FETCH EQU( 0x2 << 10 );
-( MC ) ڪوڊ_2 Fetch
AT91C_MC_MST0 EQU( 0x1 << 16 );
-( MC ) Master 0 Abort ذريعو_2
AT91C_MC_MST1 EQU( 0x1 << 17 );
-( MC ) Master 1 Abort ذريعو_2
AT91C_MC_SVMST0 EQU( 0x1 << 24 );
-( MC ) Saved Master 0 Abort ذريعو_2
AT91C_MC_SVMST1 EQU( 0x1 << 25 );
-( MC ) Saved Master 1 Abort ذريعو_2
/* - -------- MC_FMR : (MC Offset: 0x60) MC Flash Mode Register -------- */
AT91C_MC_FRDY EQU( 0x1 << 0 );
-( MC ) Flash Ready
AT91C_MC_LOCKE EQU( 0x1 << 2 );
-( MC ) تالو Error
AT91C_MC_PROGE EQU( 0x1 << 3 );
-( MC ) Programming Error
AT91C_MC_NEBP EQU( 0x1 << 7 );
-( MC ) No Erase Before Programming
AT91C_MC_FWS EQU( 0x3 << 8 );
-( MC ) Flash Wait State
AT91C_MC_FWS_0FWS EQU( 0x0 << 8 );
-( MC ) 1 چڪر

لكل Read, 2

لكل Write operations
AT91C_MC_FWS_1FWS EQU( 0x1 << 8 );
-( MC ) 2 چڪرن

لكل Read, 3

لكل Write operations
AT91C_MC_FWS_2FWS EQU( 0x2 << 8 );
-( MC ) 3 چڪرن

لكل Read, 4

لكل Write operations
AT91C_MC_FWS_3FWS EQU( 0x3 << 8 );
-( MC ) 4 چڪرن

لكل Read, 4

لكل Write operations
AT91C_MC_FMCN EQU( 0xFF << 16 );
-( MC ) Flash Microsecond چڪر_2 عدد_2
/* - -------- MC_FCR : (MC Offset: 0x64) MC Flash Command Register -------- */
AT91C_MC_FCMD EQU( 0xF << 0 );
-( MC ) Flash Command
AT91_C_MC_FCMD_شروعات_PROG EQU( 0x1 );
-( MC ) Starts the programming جو th epage specified by PAGEN.
   AT91_C_MC_FCMD_تالو EQU( 0x2 );
-( MC ) Starts a تالو_2 sequence جو the sector defined by the بٽ_2 4 منزل 7 جو the ميدان PAGEN.
   AT91_C_MC_FCMD_PROG_AND_تالو EQU( 0x3 );
-( MC ) The تالو_2 sequence automatically happens after the programming sequence is completed.
   AT91C_MC_FCMD_UNLOCK EQU( 0x4 );
-( MC ) Starts an unlock sequence جو the sector defined by the بٽ_2 4 منزل 7 جو the ميدان PAGEN.
   AT91C_MC_FCMD_ERASE_ALL EQU( 0x8 );
-( MC ) Starts the erase جو the entire flash.If at گهٽ_کان_گهٽ a صفحو is locked, the command is cancelled.
   AT91_C_MC_FCMD_سيٽ_GP_NVM EQU( 0xB );
-( MC ) سيٽ_2 General Purpose NVM بٽ_2.
   AT91C_MC_FCMD_CLR_GP_NVM EQU( 0xD );
-( MC ) Clear General Purpose NVM بٽ_2.
   AT91_C_MC_FCMD_سيٽ_SECURITY EQU( 0xF );
-( MC ) سيٽ_2 Security ٻٽو_انگ.
   AT91C_MC_PAGEN EQU( 0x3FF << 8 );
-( MC ) صفحو_2 عدد_2
AT91_C_MC_ڪنجي EQU( 0xFF << 24 );
-( MC ) Writing Protect ڪنجي_2
/* - -------- MC_FSR : (MC Offset: 0x68) MC Flash Command Register -------- */
AT91C_MC_SECURITY EQU( 0x1 << 4 );
-( MC ) Security ٻٽو_انگ حالت
AT91C_MC_GPNVM0 EQU( 0x1 << 8 );
-( MC ) Sector 0 تالو حالت
AT91C_MC_GPNVM1 EQU( 0x1 << 9 );
-( MC ) Sector 1 تالو حالت
AT91C_MC_GPNVM2 EQU( 0x1 << 10 );
-( MC ) Sector 2 تالو حالت
AT91C_MC_GPNVM3 EQU( 0x1 << 11 );
-( MC ) Sector 3 تالو حالت
AT91C_MC_GPNVM4 EQU( 0x1 << 12 );
-( MC ) Sector 4 تالو حالت
AT91C_MC_GPNVM5 EQU( 0x1 << 13 );
-( MC ) Sector 5 تالو حالت
AT91C_MC_GPNVM6 EQU( 0x1 << 14 );
-( MC ) Sector 6 تالو حالت
AT91C_MC_GPNVM7 EQU( 0x1 << 15 );
-( MC ) Sector 7 تالو حالت
AT91C_MC_LOCKS0 EQU( 0x1 << 16 );
-( MC ) Sector 0 تالو حالت
AT91C_MC_LOCKS1 EQU( 0x1 << 17 );
-( MC ) Sector 1 تالو حالت
AT91C_MC_LOCKS2 EQU( 0x1 << 18 );
-( MC ) Sector 2 تالو حالت
AT91C_MC_LOCKS3 EQU( 0x1 << 19 );
-( MC ) Sector 3 تالو حالت
AT91C_MC_LOCKS4 EQU( 0x1 << 20 );
-( MC ) Sector 4 تالو حالت
AT91C_MC_LOCKS5 EQU( 0x1 << 21 );
-( MC ) Sector 5 تالو حالت
AT91C_MC_LOCKS6 EQU( 0x1 << 22 );
-( MC ) Sector 6 تالو حالت
AT91C_MC_LOCKS7 EQU( 0x1 << 23 );
-( MC ) Sector 7 تالو حالت
AT91C_MC_LOCKS8 EQU( 0x1 << 24 );
-( MC ) Sector 8 تالو حالت
AT91C_MC_LOCKS9 EQU( 0x1 << 25 );
-( MC ) Sector 9 تالو حالت
AT91C_MC_LOCKS10 EQU( 0x1 << 26 );
-( MC ) Sector 10 تالو حالت
AT91C_MC_LOCKS11 EQU( 0x1 << 27 );
-( MC ) Sector 11 تالو حالت
AT91C_MC_LOCKS12 EQU( 0x1 << 28 );
-( MC ) Sector 12 تالو حالت
AT91C_MC_LOCKS13 EQU( 0x1 << 29 );
-( MC ) Sector 13 تالو حالت
AT91C_MC_LOCKS14 EQU( 0x1 << 30 );
-( MC ) Sector 14 تالو حالت
AT91C_MC_LOCKS15 EQU( 0x1 << 31 );
-( MC ) Sector 15 تالو حالت

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
-( SPI ) SPI آخري Transfer
/* - -------- SPI_MR : (SPI Offset: 0x4) SPI Mode Register -------- */
AT91C_SPI_MSTR EQU( 0x1 << 0 );
-( SPI ) Master / Slave گهڻائي
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
-( SPI ) گهڻائي Fault Detection
AT91C_SPI_LLB EQU( 0x1 << 7 );
-( SPI ) Clock Selection
AT91C_SPI_PCS EQU( 0xF << 16 );
-( SPI ) Peripheral Chip Select
AT91C_SPI_DLYBCS EQU( 0xFF << 24 );
-( SPI ) Delay Between Chip Selects
/* - -------- SPI_RDR : (SPI Offset: 0x8) Receive Data Register -------- */
AT91C_SPI_RD EQU( 0xFFFF << 0 );
-( SPI ) Receive معلومات
AT91C_SPI_RPCS EQU( 0xF << 16 );
-( SPI ) Peripheral Chip Select حالت
/* - -------- SPI_TDR : (SPI Offset: 0xc) Transmit Data Register -------- */
AT91C_SPI_TD EQU( 0xFFFF << 0 );
-( SPI ) Transmit معلومات
AT91C_SPI_TPCS EQU( 0xF << 16 );
-( SPI ) Peripheral Chip Select حالت
/* - -------- SPI_SR : (SPI Offset: 0x10) Status Register -------- */
AT91C_SPI_RDRF EQU( 0x1 << 0 );
-( SPI ) Receive معلومات رجسٽر ڀريل
AT91C_SPI_TDRE EQU( 0x1 << 1 );
-( SPI ) Transmit معلومات رجسٽر خالي_جايون
AT91C_SPI_MODF EQU( 0x1 << 2 );
-( SPI ) گهڻائي Fault Error
AT91C_SPI_OVRES EQU( 0x1 << 3 );
-( SPI ) Overrun Error حالت
AT91C_SPI_ENDRX EQU( 0x1 << 4 );
-( SPI ) پڇاڙي_2 جو Receiver Transfer
AT91C_SPI_ENDTX EQU( 0x1 << 5 );
-( SPI ) پڇاڙي_2 جو Receiver Transfer
AT91C_SPI_RXBUFF EQU( 0x1 << 6 );
-( SPI ) RXBUFF مداخلت_2
AT91C_SPI_TXBUFE EQU( 0x1 << 7 );
-( SPI ) TXBUFE مداخلت_2
AT91C_SPI_NSSR EQU( 0x1 << 8 );
-( SPI ) NSSR مداخلت_2
AT91C_SPI_TXEMPTY EQU( 0x1 << 9 );
-( SPI ) TXEMPTY مداخلت_2
AT91C_SPI_SPIENS EQU( 0x1 << 16 );
-( SPI ) Enable حالت
/* - -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- */
/* - -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- */
/* - -------- SPI_IMR : (SPI Offset: 0x1c) Interrupt Mask Register -------- */
/* - -------- SPI_CSR : (SPI Offset: 0x30) Chip Select Register -------- */
AT91C_SPI_CPOL EQU( 0x1 << 0 );
-( SPI ) Clock Polarity
AT91C_SPI_NCPHA EQU( 0x1 << 1 );
-( SPI ) Clock Phase
AT91C_SPI_CSAAT EQU( 0x1 << 3 );
-( SPI ) Chip Select سرگرم After Transfer
AT91_C_SPI_بٽ EQU( 0xF << 4 );
-( SPI ) بٽ في_2 Transfer
AT91_C_SPI_بٽ_8 EQU( 0x0 << 4 );
-( SPI ) 8 بٽ في_2 transfer
AT91_C_SPI_بٽ_9 EQU( 0x1 << 4 );
-( SPI ) 9 بٽ في_2 transfer
AT91_C_SPI_بٽ_10 EQU( 0x2 << 4 );
-( SPI ) 10 بٽ في_2 transfer
AT91_C_SPI_بٽ_11 EQU( 0x3 << 4 );
-( SPI ) 11 بٽ في_2 transfer
AT91_C_SPI_بٽ_12 EQU( 0x4 << 4 );
-( SPI ) 12 بٽ في_2 transfer
AT91_C_SPI_بٽ_13 EQU( 0x5 << 4 );
-( SPI ) 13 بٽ في_2 transfer
AT91_C_SPI_بٽ_14 EQU( 0x6 << 4 );
-( SPI ) 14 بٽ في_2 transfer
AT91_C_SPI_بٽ_15 EQU( 0x7 << 4 );
-( SPI ) 15 بٽ في_2 transfer
AT91_C_SPI_بٽ_16 EQU( 0x8 << 4 );
-( SPI ) 16 بٽ في_2 transfer
AT91C_SPI_SCBR EQU( 0xFF << 8 );
-( SPI ) Serial Clock Baud شرح
AT91C_SPI_DLYBS EQU( 0xFF << 16 );
-( SPI ) Delay Before SPCK
AT91C_SPI_DLYBCT EQU( 0xFF << 24 );
-( SPI ) Delay Between Consecutive Transfers

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Usart */
/* - ***************************************************************************** */
/* - -------- US_CR : (USART Offset: 0x0) Debug Unit Control Register -------- */
AT91C_US_STTBRK EQU( 0x1 << 9 );
-( USART ) شروعات_2 Break
AT91C_US_STPBRK EQU( 0x1 << 10 );
-( USART ) Stop Break
AT91C_US_STTTO EQU( 0x1 << 11 );
-( USART ) شروعات_2 وقت - ٻاهريون
AT91C_US_SENDA EQU( 0x1 << 12 );
-( USART ) Send پتو
AT91C_US_RSTIT EQU( 0x1 << 13 );
-( USART ) Reset Iterations
AT91C_US_RSTNACK EQU( 0x1 << 14 );
-( USART ) Reset Non Acknowledge
AT91C_US_RETTO EQU( 0x1 << 15 );
-( USART ) Rearm وقت - ٻاهريون
AT91C_US_DTREN EQU( 0x1 << 16 );
-( USART ) معلومات Terminal ready Enable
AT91C_US_DTRDIS EQU( 0x1 << 17 );
-( USART ) معلومات Terminal ready Disable
AT91C_US_RTSEN EQU( 0x1 << 18 );
-( USART ) Request منزل Send enable
AT91C_US_RTSDIS EQU( 0x1 << 19 );
-( USART ) Request منزل Send Disable
/* - -------- US_MR : (USART Offset: 0x4) Debug Unit Mode Register -------- */
AT91C_US_USMODE EQU( 0xF << 0 );
-( USART ) Usart گهڻائي_2
AT91_C_US_USMODE_عام EQU( 0x0 );
-( USART ) عام_2
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
-( USART ) Clock Selection ( Baud شرح generator داخلا Clock
                             AT91C_US_CLKS_CLOCK EQU( 0x0 << 4 );
                             -( USART ) Clock
                             AT91C_US_CLKS_FDIV1 EQU( 0x1 << 4 );
                             -( USART ) fdiv1
                             AT91C_US_CLKS_SLOW EQU( 0x2 << 4 );
                             -( USART ) slow_clock( ARM )
                             AT91C_US_CLKS_EXT EQU( 0x3 << 4 );
                             -( USART ) External( SCK )
                             AT91C_US_CHRL EQU( 0x3 << 6 );
                             -( USART ) Clock Selection ( Baud شرح generator داخلا Clock
                                                          AT91_C_US_CHRL_5_بٽ EQU( 0x0 << 6 );
                                                          -( USART ) Character ڊيگهائي : 5 بٽ_2
                                                          AT91_C_US_CHRL_6_بٽ EQU( 0x1 << 6 );
                                                          -( USART ) Character ڊيگهائي : 6 بٽ_2
                                                          AT91_C_US_CHRL_7_بٽ EQU( 0x2 << 6 );
                                                          -( USART ) Character ڊيگهائي : 7 بٽ_2
                                                          AT91_C_US_CHRL_8_بٽ EQU( 0x3 << 6 );
                                                          -( USART ) Character ڊيگهائي : 8 بٽ_2
                                                          AT91C_US_SYNC EQU( 0x1 << 8 );
                                                          -( USART ) Synchronous گهڻائي Select
                                                          AT91C_US_NBSTOP EQU( 0x3 << 12 );
                                                          -( USART ) عدد_2 جو Stop بٽ_2
                                                          AT91_C_US_NBSTOP_1_ٻٽو_انگ EQU( 0x0 << 12 );
                                                          -( USART ) 1 stop ٻٽو_انگ_2
                                                          AT91_C_US_NBSTOP_15_ٻٽو_انگ EQU( 0x1 << 12 );
                                                          -( USART ) Asynchronous( SYNC = 0 ) 2 stop بٽ_2 Synchronous( SYNC = 1 ) 2 stop بٽ_2
                                                          AT91_C_US_NBSTOP_2_ٻٽو_انگ EQU( 0x2 << 12 );
                                                          -( USART ) 2 stop بٽ_2
                                                          AT91C_US_MSBF EQU( 0x1 << 16 );
                                                          -( USART ) ٻٽو_انگ ترتيب_2
                                                          AT91C_US_MODE9 EQU( 0x1 << 17 );
                                                          -( USART ) 9 - ٻٽو_انگ_2 Character ڊيگهائي_2
                                                          AT91C_US_CKLO EQU( 0x1 << 18 );
                                                          -( USART ) Clock Output Select
                                                          AT91C_US_OVER EQU( 0x1 << 19 );
                                                          -( USART ) Over Sampling گهڻائي
                                                          AT91C_US_INACK EQU( 0x1 << 20 );
                                                          -( USART ) Inhibit Non Acknowledge
                                                          AT91C_US_DSNACK EQU( 0x1 << 21 );
                                                          -( USART ) Disable Successive NACK
                                                          AT91C_US_MAX_ITER EQU( 0x1 << 24 );
                                                          -( USART ) عدد_2 جو Repetitions
                                                          AT91C_US_FILTER EQU( 0x1 << 28 );
                                                          -( USART ) Receive سٽ_2 Filter
/* - -------- US_IER : (USART Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
                                                          AT91C_US_RXBRK EQU( 0x1 << 2 );
                                                          -( USART ) Break Received / پڇاڙي_2 جو Break
                                                          AT91C_US_TIMEOUT EQU( 0x1 << 8 );
                                                          -( USART ) Receiver وقت - ٻاهريون
                                                          AT91C_US_ITERATION EQU( 0x1 << 10 );
                                                          -( USART ) Max عدد جو Repetitions Reached
                                                          AT91C_US_NACK EQU( 0x1 << 13 );
                                                          -( USART ) Non Acknowledge
                                                          AT91C_US_RIIC EQU( 0x1 << 16 );
                                                          -( USART ) Ring INdicator داخلا Change Flag
                                                          AT91C_US_DSRIC EQU( 0x1 << 17 );
                                                          -( USART ) معلومات سيٽ_2 Ready داخلا Change Flag
                                                          AT91C_US_DCDIC EQU( 0x1 << 18 );
                                                          -( USART ) معلومات Carrier Flag
                                                          AT91C_US_CTSIC EQU( 0x1 << 19 );
                                                          -( USART ) Clear منزل_2 Send داخلا Change Flag
/* - -------- US_IDR : (USART Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* - -------- US_IMR : (USART Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* - -------- US_CSR : (USART Offset: 0x14) Debug Unit Channel Status Register -------- */
                                                          AT91C_US_RI EQU( 0x1 << 20 );
                                                          -( USART ) Image جو RI داخلا
                                                          AT91C_US_DSR EQU( 0x1 << 21 );
                                                          -( USART ) Image جو DSR داخلا
                                                          AT91C_US_DCD EQU( 0x1 << 22 );
                                                          -( USART ) Image جو DCD داخلا
                                                          AT91C_US_CTS EQU( 0x1 << 23 );
                                                          -( USART ) Image جو CTS داخلا

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
                                                          -( SSC ) TK Clock إشارة
                                                          AT91C_SSC_CKS_RK EQU( 0x2 );
                                                          -( SSC ) RK pin
                                                          AT91C_SSC_CKO EQU( 0x7 << 2 );
                                                          -( SSC ) Receive / Transmit Clock Output گهڻائي Selection
                                                          AT91C_SSC_CKO_NONE EQU( 0x0 << 2 );
                                                          -( SSC ) Receive / Transmit Clock Output گهڻائي:None RK pin: داخلا - only
                                                          AT91C_SSC_CKO_CONTINUOUS EQU( 0x1 << 2 );
                                                          -( SSC ) Continuous Receive / Transmit Clock RK pin:Output
                                                          AT91_C_SSC_CKO_معلومات_TX EQU( 0x2 << 2 );
                                                          -( SSC ) Receive / Transmit Clock only during معلومات_2 transfers RK pin:Output
                                                          AT91C_SSC_CKI EQU( 0x1 << 5 );
                                                          -( SSC ) Receive / Transmit Clock Inversion
                                                          AT91_C_SSC_شروعات EQU( 0xF << 8 );
                                                          -( SSC ) Receive / Transmit شروعات_2 Selection
                                                          AT91_C_SSC_شروعات_CONTINUOUS EQU( 0x0 << 8 );
                                                          -( SSC ) Continuous, as soon as the receiver is enabled, and immediately after the پڇاڙي جو transfer جو the اڳيون معلومات_2.
                                                             AT91_C_SSC_شروعات_TX EQU( 0x1 << 8 );
                                                          -( SSC ) Transmit / Receive شروعات
                                                          AT91_C_SSC_شروعات_هيٺيون_RF EQU( 0x2 << 8 );
                                                          -( SSC ) Detection جو a هيٺيون_2 level on RF داخلا_2
                                                          AT91_C_SSC_شروعات_مٿاهون_RF EQU( 0x3 << 8 );
                                                          -( SSC ) Detection جو a مٿاهون_2 level on RF داخلا_2
                                                          AT91_C_SSC_شروعات_FALL_RF EQU( 0x4 << 8 );
                                                          -( SSC ) Detection جو a falling ڪنارو_2 on RF داخلا_2
                                                          AT91_C_SSC_شروعات_RISE_RF EQU( 0x5 << 8 );
                                                          -( SSC ) Detection جو a rising ڪنارو_2 on RF داخلا_2
                                                          AT91_C_SSC_شروعات_LEVEL_RF EQU( 0x6 << 8 );
                                                          -( SSC ) Detection جو any level change on RF داخلا_2
                                                          AT91_C_SSC_شروعات_ڪنارو_RF EQU( 0x7 << 8 );
                                                          -( SSC ) Detection جو any ڪنارو_2 on RF داخلا_2
                                                          AT91_C_SSC_شروعات_0 EQU( 0x8 << 8 );
                                                          -( SSC ) Compare 0
                                                          AT91C_SSC_STTDLY EQU( 0xFF << 16 );
                                                          -( SSC ) Receive / Transmit شروعات_2 Delay
                                                          AT91C_SSC_PERIOD EQU( 0xFF << 24 );
                                                          -( SSC ) Receive / Transmit Period Divider Selection
/* - -------- SSC_RFMR : (SSC Offset: 0x14) SSC Receive Frame Mode Register -------- */
                                                          AT91C_SSC_DATLEN EQU( 0x1F << 0 );
                                                          -( SSC ) معلومات ڊيگهائي
                                                          AT91C_SSC_LOOP EQU( 0x1 << 5 );
                                                          -( SSC ) Loop گهڻائي
                                                          AT91C_SSC_MSBF EQU( 0x1 << 7 );
                                                          -( SSC ) Most Significant ٻٽو_انگ پهريون
                                                          AT91C_SSC_DATNB EQU( 0xF << 8 );
                                                          -( SSC ) معلومات عدد_2 في_3 چوکٺو
                                                          AT91C_SSC_FSLEN EQU( 0xF << 16 );
                                                          -( SSC ) Receive / Transmit چوکٺو Sync ڊيگهائي_2
                                                          AT91C_SSC_FSOS EQU( 0x7 << 20 );
                                                          -( SSC ) Receive / Transmit چوکٺو Sync Output Selection
                                                          AT91C_SSC_FSOS_NONE EQU( 0x0 << 20 );
                                                          -( SSC ) Selected Receive / Transmit چوکٺو Sync Signal:None RK pin داخلا - only
                                                          AT91C_SSC_FSOS_NEGATIVE EQU( 0x1 << 20 );
                                                          -( SSC ) Selected Receive / Transmit چوکٺو Sync Signal:Negative Pulse
                                                          AT91_C_SSC_FSOS_مثبت EQU( 0x2 << 20 );
                                                          -( SSC ) Selected Receive / Transmit چوکٺو Sync Signal:مثبت Pulse
                                                          AT91_C_SSC_FSOS_هيٺيون EQU( 0x3 << 20 );
                                                          -( SSC ) Selected Receive / Transmit چوکٺو Sync Signal:Driver هيٺيون during معلومات_2 transfer
                                                          AT91_C_SSC_FSOS_مٿاهون EQU( 0x4 << 20 );
                                                          -( SSC ) Selected Receive / Transmit چوکٺو Sync Signal:Driver مٿاهون during معلومات_2 transfer
                                                          AT91C_SSC_FSOS_TOGGLE EQU( 0x5 << 20 );
                                                          -( SSC ) Selected Receive / Transmit چوکٺو Sync Signal:Toggling at each شروعات جو معلومات_2 transfer
                                                          AT91C_SSC_FSEDGE EQU( 0x1 << 24 );
                                                          -( SSC ) چوکٺو Sync ڪنارو Detection
/* - -------- SSC_TCMR : (SSC Offset: 0x18) SSC Transmit Clock Mode Register -------- */
/* - -------- SSC_TFMR : (SSC Offset: 0x1c) SSC Transmit Frame Mode Register -------- */
                                                          AT91C_SSC_DATDEF EQU( 0x1 << 5 );
                                                          -( SSC ) معلومات Default قدر_2
                                                          AT91C_SSC_FSDEN EQU( 0x1 << 23 );
                                                          -( SSC ) چوکٺو Sync معلومات Enable
/* - -------- SSC_SR : (SSC Offset: 0x40) SSC Status Register -------- */
                                                          AT91C_SSC_TXRDY EQU( 0x1 << 0 );
                                                          -( SSC ) Transmit Ready
                                                          AT91C_SSC_TXEMPTY EQU( 0x1 << 1 );
                                                          -( SSC ) Transmit خالي_جايون
                                                          AT91C_SSC_ENDTX EQU( 0x1 << 2 );
                                                          -( SSC ) پڇاڙي_2 جو_2 ترسيل
                                                          AT91C_SSC_TXBUFE EQU( 0x1 << 3 );
                                                          -( SSC ) Transmit بفر خالي_جايون
                                                          AT91C_SSC_RXRDY EQU( 0x1 << 4 );
                                                          -( SSC ) Receive Ready
                                                          AT91C_SSC_OVRUN EQU( 0x1 << 5 );
                                                          -( SSC ) Receive Overrun
                                                          AT91C_SSC_ENDRX EQU( 0x1 << 6 );
                                                          -( SSC ) پڇاڙي_2 جو Reception
                                                          AT91C_SSC_RXBUFF EQU( 0x1 << 7 );
                                                          -( SSC ) Receive بفر ڀريل
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
                                                          AT91_C_TWI_شروعات EQU( 0x1 << 0 );
                                                          -( TWI ) Send a شروعات_3 Condition
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
                                                          -( TWI ) اندروني Device پتو سائيز_2
                                                          AT91C_TWI_IADRSZ_NO EQU( 0x0 << 8 );
                                                          -( TWI ) No اندروني_2 device پتو_2
                                                          AT91C_TWI_IADRSZ_1_BYTE EQU( 0x1 << 8 );
                                                          -( TWI ) One - byte اندروني_2 device پتو_2
                                                          AT91C_TWI_IADRSZ_2_BYTE EQU( 0x2 << 8 );
                                                          -( TWI ) Two - byte اندروني_2 device پتو_2
                                                          AT91C_TWI_IADRSZ_3_BYTE EQU( 0x3 << 8 );
                                                          -( TWI ) Three - byte اندروني_2 device پتو_2
                                                          AT91C_TWI_MREAD EQU( 0x1 << 12 );
                                                          -( TWI ) Master Read Direction
                                                          AT91C_TWI_DADR EQU( 0x7F << 16 );
                                                          -( TWI ) Device پتو
/* - -------- TWI_CWGR : (TWI Offset: 0x10) TWI Clock Waveform Generator Register -------- */
                                                          AT91C_TWI_CLDIV EQU( 0xFF << 0 );
                                                          -( TWI ) Clock هيٺيون Divider
                                                          AT91C_TWI_CHDIV EQU( 0xFF << 8 );
                                                          -( TWI ) Clock مٿاهون Divider
                                                          AT91C_TWI_CKDIV EQU( 0x7 << 16 );
                                                          -( TWI ) Clock Divider
/* - -------- TWI_SR : (TWI Offset: 0x20) TWI Status Register -------- */
                                                          AT91C_TWI_TXCOMP EQU( 0x1 << 0 );
                                                          -( TWI ) ترسيل Completed
                                                          AT91C_TWI_RXRDY EQU( 0x1 << 1 );
                                                          -( TWI ) Receive holding سجل ReaDY
                                                          AT91C_TWI_TXRDY EQU( 0x1 << 2 );
                                                          -( TWI ) Transmit holding سجل ReaDY
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
                                                          -( PWMC_CH ) Channel Duty چڪر_2
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
                                                          -( PWMC ) CLKA divide ضرب_ڪندڙ.
                                                             AT91C_PWMC_PREA EQU( 0xF << 8 );
                                                          -( PWMC ) Divider داخلا Clock Prescaler A
                                                          AT91C_PWMC_PREA_MCK EQU( 0x0 << 8 );
                                                          -( PWMC )
                                                          AT91C_PWMC_DIVB EQU( 0xFF << 16 );
                                                          -( PWMC ) CLKB divide ضرب_ڪندڙ.
                                                             AT91C_PWMC_PREB EQU( 0xF << 24 );
                                                          -( PWMC ) Divider داخلا Clock Prescaler B
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
                                                          AT91_C_UDP_FRM_انگ EQU( 0x7FF << 0 );
                                                          -( UDP ) چوکٺو عدد_2 as Defined اندريون the Packet ميدان_2 Formats
                                                          AT91C_UDP_FRM_ERR EQU( 0x1 << 16 );
                                                          -( UDP ) چوکٺو Error
                                                          AT91C_UDP_FRM_OK EQU( 0x1 << 17 );
                                                          -( UDP ) چوکٺو OK
/* - -------- UDP_GLB_STATE : (UDP Offset: 0x4) USB Global State Register -------- */
                                                          AT91C_UDP_FADDEN EQU( 0x1 << 0 );
                                                          -( UDP ) Function پتو Enable
                                                          AT91C_UDP_CONFG EQU( 0x1 << 1 );
                                                          -( UDP ) Configured
                                                          AT91C_UDP_ESR EQU( 0x1 << 2 );
                                                          -( UDP ) Enable Send Resume
                                                          AT91C_UDP_RSMINPR EQU( 0x1 << 3 );
                                                          -( UDP ) A Resume Has Been موڪليل منزل the Host
                                                          AT91C_UDP_RMWUPE EQU( 0x1 << 4 );
                                                          -( UDP ) Remote Wake مٿي_2 Enable
/* - -------- UDP_FADDR : (UDP Offset: 0x8) USB Function Address Register -------- */
                                                          AT91C_UDP_FADD EQU( 0xFF << 0 );
                                                          -( UDP ) Function پتو قدر_2
                                                          AT91C_UDP_FEN EQU( 0x1 << 8 );
                                                          -( UDP ) Function Enable
/* - -------- UDP_IER : (UDP Offset: 0x10) USB Interrupt Enable Register -------- */
                                                          AT91C_UDP_EPINT0 EQU( 0x1 << 0 );
                                                          -( UDP ) Endpoint 0 مداخلت_2
                                                          AT91C_UDP_EPINT1 EQU( 0x1 << 1 );
                                                          -( UDP ) Endpoint 0 مداخلت_2
                                                          AT91C_UDP_EPINT2 EQU( 0x1 << 2 );
                                                          -( UDP ) Endpoint 2 مداخلت_2
                                                          AT91C_UDP_EPINT3 EQU( 0x1 << 3 );
                                                          -( UDP ) Endpoint 3 مداخلت_2
                                                          AT91C_UDP_EPINT4 EQU( 0x1 << 4 );
                                                          -( UDP ) Endpoint 4 مداخلت_2
                                                          AT91C_UDP_EPINT5 EQU( 0x1 << 5 );
                                                          -( UDP ) Endpoint 5 مداخلت_2
                                                          AT91C_UDP_RXSUSP EQU( 0x1 << 8 );
                                                          -( UDP ) USB Suspend مداخلت_2
                                                          AT91C_UDP_RXRSM EQU( 0x1 << 9 );
                                                          -( UDP ) USB Resume مداخلت_2
                                                          AT91C_UDP_EXTRSM EQU( 0x1 << 10 );
                                                          -( UDP ) USB External Resume مداخلت_2
                                                          AT91C_UDP_SOFINT EQU( 0x1 << 11 );
                                                          -( UDP ) USB شروعات_2 جو_2 چوکٺو_2 مداخلت_2
                                                          AT91C_UDP_WAKEUP EQU( 0x1 << 13 );
                                                          -( UDP ) USB Resume مداخلت_2
/* - -------- UDP_IDR : (UDP Offset: 0x14) USB Interrupt Disable Register -------- */
/* - -------- UDP_IMR : (UDP Offset: 0x18) USB Interrupt Mask Register -------- */
/* - -------- UDP_ISR : (UDP Offset: 0x1c) USB Interrupt Status Register -------- */
                                                          AT91C_UDP_ENDBUSRES EQU( 0x1 << 12 );
                                                          -( UDP ) USB پڇاڙي_2 جو_2 Bus Reset مداخلت_2
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
                                                          -( UDP ) Generates an اندريون_2 packet with معلومات_2 previously written اندريون the DPR
                                                          AT91_C_UDP_RX_معلومات_BK0 EQU( 0x1 << 1 );
                                                          -( UDP ) Receive معلومات Bank 0
                                                          AT91C_UDP_RXSETUP EQU( 0x1 << 2 );
                                                          -( UDP ) Sends STALL منزل the Host( Control endpoints )
                                                          AT91C_UDP_ISOERROR EQU( 0x1 << 3 );
                                                          -( UDP ) Isochronous error( Isochronous endpoints )
                                                          AT91C_UDP_TXPKTRDY EQU( 0x1 << 4 );
                                                          -( UDP ) Transmit Packet Ready
                                                          AT91C_UDP_FORCESTALL EQU( 0x1 << 5 );
                                                          -( UDP ) Force Stall( استعمال_ٿيل by Control, Bulk and Isochronous endpoints ).
                                                             AT91_C_UDP_RX_معلومات_BK1 EQU( 0x1 << 6 );
                                                          -( UDP ) Receive معلومات Bank 1 ( only استعمال_ٿيل by endpoints with ping - pong خاصيتون ).
                                                             AT91C_UDP_DIR EQU( 0x1 << 7 );
                                                          -( UDP ) Transfer Direction
                                                          AT91C_UDP_EPTYPE EQU( 0x7 << 8 );
                                                          -( UDP ) Endpoint type
                                                          AT91C_UDP_EPTYPE_CTRL EQU( 0x0 << 8 );
                                                          -( UDP ) Control
                                                          AT91_C_UDP_EPTYPE_ISO_ٻاهريون EQU( 0x1 << 8 );
                                                          -( UDP ) Isochronous ٻاهريون_2
                                                          AT91_C_UDP_EPTYPE_BULK_ٻاهريون EQU( 0x2 << 8 );
                                                          -( UDP ) Bulk ٻاهريون_2
                                                          AT91_C_UDP_EPTYPE_INT_ٻاهريون EQU( 0x3 << 8 );
                                                          -( UDP ) مداخلت_2 ٻاهريون_2
                                                          AT91_C_UDP_EPTYPE_ISO_اندريون EQU( 0x5 << 8 );
                                                          -( UDP ) Isochronous اندريون_2
                                                          AT91_C_UDP_EPTYPE_BULK_اندريون EQU( 0x6 << 8 );
                                                          -( UDP ) Bulk اندريون_2
                                                          AT91_C_UDP_EPTYPE_INT_اندريون EQU( 0x7 << 8 );
                                                          -( UDP ) مداخلت_2 اندريون_2
                                                          AT91C_UDP_DTGLE EQU( 0x1 << 11 );
                                                          -( UDP ) معلومات Toggle
                                                          AT91C_UDP_EPEDS EQU( 0x1 << 15 );
                                                          -( UDP ) Endpoint Enable Disable
                                                          AT91C_UDP_RXBYTECNT EQU( 0x7FF << 16 );
                                                          -( UDP ) عدد_2 جو_2 بائيٽون موجود_2 اندريون the FIFO
/* - -------- UDP_TXVC : (UDP Offset: 0x74) Transceiver Control Register -------- */
                                                          AT91C_UDP_TXVDIS EQU( 0x1 << 8 );
                                                          -( UDP )
                                                          AT91C_UDP_PUON EQU( 0x1 << 9 );
                                                          -( UDP ) Pull - مٿي ON

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
                                                          AT91_C_TC_مدو EQU( 0x3 << 4 );
                                                          -( TC ) مدو Signal Selection
                                                          AT91_C_TC_مدو_NONE EQU( 0x0 << 4 );
                                                          -( TC ) The clock is not gated by an external إشارة
                                                          AT91_C_TC_مدو_XC0 EQU( 0x1 << 4 );
                                                          -( TC ) XC0 is ANDed with the selected clock
                                                          AT91_C_TC_مدو_XC1 EQU( 0x2 << 4 );
                                                          -( TC ) XC1 is ANDed with the selected clock
                                                          AT91_C_TC_مدو_XC2 EQU( 0x3 << 4 );
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
                                                          -( TC ) External Trigger ڪنارو Selection
                                                          AT91C_TC_ETRGEDG_NONE EQU( 0x0 << 8 );
                                                          -( TC ) ڪنارو:None
                                                          AT91C_TC_ETRGEDG_RISING EQU( 0x1 << 8 );
                                                          -( TC ) ڪنارو:rising ڪنارو_2
                                                          AT91C_TC_ETRGEDG_FALLING EQU( 0x2 << 8 );
                                                          -( TC ) ڪنارو:falling ڪنارو_2
                                                          AT91C_TC_ETRGEDG_BOTH EQU( 0x3 << 8 );
                                                          -( TC ) ڪنارو:each ڪنارو_2
                                                          AT91C_TC_EEVTEDG EQU( 0x3 << 8 );
                                                          -( TC ) External Event ڪنارو Selection
                                                          AT91C_TC_EEVTEDG_NONE EQU( 0x0 << 8 );
                                                          -( TC ) ڪنارو:None
                                                          AT91C_TC_EEVTEDG_RISING EQU( 0x1 << 8 );
                                                          -( TC ) ڪنارو:rising ڪنارو_2
                                                          AT91C_TC_EEVTEDG_FALLING EQU( 0x2 << 8 );
                                                          -( TC ) ڪنارو:falling ڪنارو_2
                                                          AT91C_TC_EEVTEDG_BOTH EQU( 0x3 << 8 );
                                                          -( TC ) ڪنارو:each ڪنارو_2
                                                          AT91C_TC_EEVT EQU( 0x3 << 10 );
                                                          -( TC ) External Event Selection
                                                          AT91C_TC_EEVT_TIOB EQU( 0x0 << 10 );
                                                          -( TC ) Signal selected as external event:TIOB TIOB direction: داخلا_2
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
                                                          AT91_C_TC_WAVESEL_مٿي EQU( 0x0 << 13 );
                                                          -( TC ) مٿي_3 گهڻائي_2 without atomatic trigger on RC Compare
                                                          AT91C_TC_WAVESEL_UPDOWN EQU( 0x1 << 13 );
                                                          -( TC ) UPDOWN گهڻائي_2 without automatic trigger on RC Compare
                                                          AT91_C_TC_WAVESEL_مٿي_AUTO EQU( 0x2 << 13 );
                                                          -( TC ) مٿي_3 گهڻائي_2 with automatic trigger on RC Compare
                                                          AT91C_TC_WAVESEL_UPDOWN_AUTO EQU( 0x3 << 13 );
                                                          -( TC ) UPDOWN گهڻائي_2 with automatic trigger on RC Compare
                                                          AT91C_TC_CPCTRG EQU( 0x1 << 14 );
                                                          -( TC ) RC Compare Trigger Enable
                                                          AT91C_TC_WAVE EQU( 0x1 << 15 );
                                                          -( TC )
                                                          AT91C_TC_ACPA EQU( 0x3 << 16 );
                                                          -( TC ) RA Compare Effect on TIOA
                                                          AT91C_TC_ACPA_NONE EQU( 0x0 << 16 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_ACPA_سيٽ EQU( 0x1 << 16 );
                                                          -( TC ) Effect:سيٽ
                                                          AT91C_TC_ACPA_CLEAR EQU( 0x2 << 16 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_ACPA_TOGGLE EQU( 0x3 << 16 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_LDRA EQU( 0x3 << 16 );
                                                          -( TC ) RA Loading Selection
                                                          AT91C_TC_LDRA_NONE EQU( 0x0 << 16 );
                                                          -( TC ) ڪنارو:None
                                                          AT91C_TC_LDRA_RISING EQU( 0x1 << 16 );
                                                          -( TC ) ڪنارو:rising ڪنارو_2 جو TIOA
                                                          AT91C_TC_LDRA_FALLING EQU( 0x2 << 16 );
                                                          -( TC ) ڪنارو:falling ڪنارو_2 جو TIOA
                                                          AT91C_TC_LDRA_BOTH EQU( 0x3 << 16 );
                                                          -( TC ) ڪنارو:each ڪنارو_2 جو TIOA
                                                          AT91C_TC_ACPC EQU( 0x3 << 18 );
                                                          -( TC ) RC Compare Effect on TIOA
                                                          AT91C_TC_ACPC_NONE EQU( 0x0 << 18 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_ACPC_سيٽ EQU( 0x1 << 18 );
                                                          -( TC ) Effect:سيٽ
                                                          AT91C_TC_ACPC_CLEAR EQU( 0x2 << 18 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_ACPC_TOGGLE EQU( 0x3 << 18 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_LDRB EQU( 0x3 << 18 );
                                                          -( TC ) RB Loading Selection
                                                          AT91C_TC_LDRB_NONE EQU( 0x0 << 18 );
                                                          -( TC ) ڪنارو:None
                                                          AT91C_TC_LDRB_RISING EQU( 0x1 << 18 );
                                                          -( TC ) ڪنارو:rising ڪنارو_2 جو TIOA
                                                          AT91C_TC_LDRB_FALLING EQU( 0x2 << 18 );
                                                          -( TC ) ڪنارو:falling ڪنارو_2 جو TIOA
                                                          AT91C_TC_LDRB_BOTH EQU( 0x3 << 18 );
                                                          -( TC ) ڪنارو:each ڪنارو_2 جو TIOA
                                                          AT91C_TC_AEEVT EQU( 0x3 << 20 );
                                                          -( TC ) External Event Effect on TIOA
                                                          AT91C_TC_AEEVT_NONE EQU( 0x0 << 20 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_AEEVT_سيٽ EQU( 0x1 << 20 );
                                                          -( TC ) Effect:سيٽ
                                                          AT91C_TC_AEEVT_CLEAR EQU( 0x2 << 20 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_AEEVT_TOGGLE EQU( 0x3 << 20 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_ASWTRG EQU( 0x3 << 22 );
                                                          -( TC ) Software Trigger Effect on TIOA
                                                          AT91C_TC_ASWTRG_NONE EQU( 0x0 << 22 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_ASWTRG_سيٽ EQU( 0x1 << 22 );
                                                          -( TC ) Effect:سيٽ
                                                          AT91C_TC_ASWTRG_CLEAR EQU( 0x2 << 22 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_ASWTRG_TOGGLE EQU( 0x3 << 22 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_BCPB EQU( 0x3 << 24 );
                                                          -( TC ) RB Compare Effect on TIOB
                                                          AT91C_TC_BCPB_NONE EQU( 0x0 << 24 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_BCPB_سيٽ EQU( 0x1 << 24 );
                                                          -( TC ) Effect:سيٽ
                                                          AT91C_TC_BCPB_CLEAR EQU( 0x2 << 24 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_BCPB_TOGGLE EQU( 0x3 << 24 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_BCPC EQU( 0x3 << 26 );
                                                          -( TC ) RC Compare Effect on TIOB
                                                          AT91C_TC_BCPC_NONE EQU( 0x0 << 26 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_BCPC_سيٽ EQU( 0x1 << 26 );
                                                          -( TC ) Effect:سيٽ
                                                          AT91C_TC_BCPC_CLEAR EQU( 0x2 << 26 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_BCPC_TOGGLE EQU( 0x3 << 26 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_BEEVT EQU( 0x3 << 28 );
                                                          -( TC ) External Event Effect on TIOB
                                                          AT91C_TC_BEEVT_NONE EQU( 0x0 << 28 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_BEEVT_سيٽ EQU( 0x1 << 28 );
                                                          -( TC ) Effect:سيٽ
                                                          AT91C_TC_BEEVT_CLEAR EQU( 0x2 << 28 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_BEEVT_TOGGLE EQU( 0x3 << 28 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_BSWTRG EQU( 0x3 << 30 );
                                                          -( TC ) Software Trigger Effect on TIOB
                                                          AT91C_TC_BSWTRG_NONE EQU( 0x0 << 30 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_BSWTRG_سيٽ EQU( 0x1 << 30 );
                                                          -( TC ) Effect:سيٽ
                                                          AT91C_TC_BSWTRG_CLEAR EQU( 0x2 << 30 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_BSWTRG_TOGGLE EQU( 0x3 << 30 );
                                                          -( TC ) Effect:toggle
/* - -------- TC_SR : (TC Offset: 0x20) TC Channel Status Register -------- */
                                                          AT91C_TC_COVFS EQU( 0x1 << 0 );
                                                          -( TC ) Counter حد_کان_مٿي_2
                                                          AT91C_TC_LOVRS EQU( 0x1 << 1 );
                                                          -( TC ) ڀريو Overrun
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
                                                          -( TCB ) TCLK0 connected منزل XC0
                                                          AT91C_TCB_TC0XC0S_NONE EQU( 0x1 );
                                                          -( TCB ) None إشارة connected منزل XC0
                                                          AT91C_TCB_TC0XC0S_TIOA1 EQU( 0x2 );
                                                          -( TCB ) TIOA1 connected منزل XC0
                                                          AT91C_TCB_TC0XC0S_TIOA2 EQU( 0x3 );
                                                          -( TCB ) TIOA2 connected منزل XC0
                                                          AT91C_TCB_TC1XC1S EQU( 0x3 << 2 );
                                                          -( TCB ) External Clock Signal 1 Selection
                                                          AT91C_TCB_TC1XC1S_TCLK1 EQU( 0x0 << 2 );
                                                          -( TCB ) TCLK1 connected منزل XC1
                                                          AT91C_TCB_TC1XC1S_NONE EQU( 0x1 << 2 );
                                                          -( TCB ) None إشارة connected منزل XC1
                                                          AT91C_TCB_TC1XC1S_TIOA0 EQU( 0x2 << 2 );
                                                          -( TCB ) TIOA0 connected منزل XC1
                                                          AT91C_TCB_TC1XC1S_TIOA2 EQU( 0x3 << 2 );
                                                          -( TCB ) TIOA2 connected منزل XC1
                                                          AT91C_TCB_TC2XC2S EQU( 0x3 << 4 );
                                                          -( TCB ) External Clock Signal 2 Selection
                                                          AT91C_TCB_TC2XC2S_TCLK2 EQU( 0x0 << 4 );
                                                          -( TCB ) TCLK2 connected منزل XC2
                                                          AT91C_TCB_TC2XC2S_NONE EQU( 0x1 << 4 );
                                                          -( TCB ) None إشارة connected منزل XC2
                                                          AT91C_TCB_TC2XC2S_TIOA0 EQU( 0x2 << 4 );
                                                          -( TCB ) TIOA0 connected منزل XC2
                                                          AT91C_TCB_TC2XC2S_TIOA1 EQU( 0x3 << 4 );
                                                          -( TCB ) TIOA2 connected منزل XC2

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Control Area Network MailBox Interface */
/* - ***************************************************************************** */
/* - -------- CAN_MMR : (CAN_MB Offset: 0x0) CAN Message Mode Register -------- */
                                                          AT91C_CAN_MTIMEMARK EQU( 0xFFFF << 0 );
                                                          -( CAN_MB ) Mailbox Timemark
                                                          AT91_C_CAN_اڳواٽ EQU( 0xF << 16 );
                                                          -( CAN_MB ) Mailbox ترجيح_2
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
                                                          AT91_C_CAN_MOT_استعمال_ڪندڙ EQU( 0x4 << 24 );
                                                          -( CAN_MB )
                                                          AT91_C_CAN_MOT_پيداوار_ڪندڙ EQU( 0x5 << 24 );
                                                          -( CAN_MB )
/* - -------- CAN_MAM : (CAN_MB Offset: 0x4) CAN Message Acceptance Mask Register -------- */
                                                          AT91C_CAN_MIDvB EQU( 0x3FFFF << 0 );
                                                          -( CAN_MB ) Complementary بٽ_2

                                                          لكل identifier اندريون extended گهڻائي_2
                                                          AT91C_CAN_MIDvA EQU( 0x7FF << 18 );
                                                          -( CAN_MB ) Identifier

                                                          لكل standard چوکٺو_2 گهڻائي_2
                                                          AT91C_CAN_MIDE EQU( 0x1 << 29 );
                                                          -( CAN_MB ) Identifier نسخو_2
/* - -------- CAN_MID : (CAN_MB Offset: 0x8) CAN Message ID Register -------- */
/* - -------- CAN_MFID : (CAN_MB Offset: 0xc) CAN Message Family ID Register -------- */
/* - -------- CAN_MSR : (CAN_MB Offset: 0x10) CAN Message Status Register -------- */
                                                          AT91C_CAN_MTIMESTAMP EQU( 0xFFFF << 0 );
                                                          -( CAN_MB ) Timer قدر_2
                                                          AT91C_CAN_MDLC EQU( 0xF << 16 );
                                                          -( CAN_MB ) Mailbox معلومات ڊيگهائي ڪوڊ_2
                                                          AT91C_CAN_MRTR EQU( 0x1 << 20 );
                                                          -( CAN_MB ) Mailbox Remote ترسيل Request
                                                          AT91C_CAN_MABT EQU( 0x1 << 22 );
                                                          -( CAN_MB ) Mailbox پيغام Abort
                                                          AT91C_CAN_MRDY EQU( 0x1 << 23 );
                                                          -( CAN_MB ) Mailbox Ready
                                                          AT91C_CAN_MMI EQU( 0x1 << 24 );
                                                          -( CAN_MB ) Mailbox پيغام Ignored
/* - -------- CAN_MDL : (CAN_MB Offset: 0x14) CAN Message Data Low Register -------- */
/* - -------- CAN_MDH : (CAN_MB Offset: 0x18) CAN Message Data High Register -------- */
/* - -------- CAN_MCR : (CAN_MB Offset: 0x1c) CAN Message Control Register -------- */
                                                          AT91C_CAN_MACR EQU( 0x1 << 22 );
                                                          -( CAN_MB ) Abort Request

                                                          لكل Mailbox
                                                          AT91C_CAN_MTCR EQU( 0x1 << 23 );
                                                          -( CAN_MB ) Mailbox Transfer Command

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Control Area Network Interface */
/* - ***************************************************************************** */
/* - -------- CAN_MR : (CAN Offset: 0x0) CAN Mode Register -------- */
                                                          AT91C_CAN_CANEN EQU( 0x1 << 0 );
                                                          -( CAN ) CAN Controller Enable
                                                          AT91C_CAN_LPM EQU( 0x1 << 1 );
                                                          -( CAN ) Disable / Enable هيٺيون Power گهڻائي
                                                          AT91C_CAN_ABM EQU( 0x1 << 2 );
                                                          -( CAN ) Disable / Enable Autobaud / Listen گهڻائي
                                                          AT91C_CAN_OVL EQU( 0x1 << 3 );
                                                          -( CAN ) Disable / Enable Overload چوکٺو
                                                          AT91C_CAN_TEOF EQU( 0x1 << 4 );
                                                          -( CAN ) وقت Stamp messages at each پڇاڙي جو چوکٺو
                                                          AT91C_CAN_TTM EQU( 0x1 << 5 );
                                                          -( CAN ) Disable / Enable وقت Trigger گهڻائي
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
                                                          -( CAN ) Error سرگرم گهڻائي Flag
                                                          AT91C_CAN_WARN EQU( 0x1 << 17 );
                                                          -( CAN ) Warning حد_بندي Flag
                                                          AT91C_CAN_ERRP EQU( 0x1 << 18 );
                                                          -( CAN ) Error Passive گهڻائي Flag
                                                          AT91C_CAN_BOFF EQU( 0x1 << 19 );
                                                          -( CAN ) Bus Off گهڻائي Flag
                                                          AT91C_CAN_SLEEP EQU( 0x1 << 20 );
                                                          -( CAN ) Sleep Flag
                                                          AT91C_CAN_WAKEUP EQU( 0x1 << 21 );
                                                          -( CAN ) Wakeup Flag
                                                          AT91C_CAN_TOVF EQU( 0x1 << 22 );
                                                          -( CAN ) Timer حد_کان_مٿي_2 Flag
                                                          AT91C_CAN_TSTP EQU( 0x1 << 23 );
                                                          -( CAN ) Timestamp Flag
                                                          AT91C_CAN_CERR EQU( 0x1 << 24 );
                                                          -( CAN ) چڪري_جاچ Error
                                                          AT91C_CAN_SERR EQU( 0x1 << 25 );
                                                          -( CAN ) Stuffing Error
                                                          AT91C_CAN_AERR EQU( 0x1 << 26 );
                                                          -( CAN ) Acknowledgment Error
                                                          AT91C_CAN_FERR EQU( 0x1 << 27 );
                                                          -( CAN ) Form Error
                                                          AT91C_CAN_BERR EQU( 0x1 << 28 );
                                                          -( CAN ) ٻٽو_انگ Error
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
                                                          -( CAN ) Re - synchronization jump ويڪر segment
                                                          AT91C_CAN_BRP EQU( 0x7F << 16 );
                                                          -( CAN ) Baudrate Prescaler
                                                          AT91C_CAN_SMP EQU( 0x1 << 24 );
                                                          -( CAN ) Sampling گهڻائي_2
/* - -------- CAN_TIM : (CAN Offset: 0x18) CAN Timer Register -------- */
                                                          AT91C_CAN_TIMER EQU( 0xFFFF << 0 );
                                                          -( CAN ) Timer ميدان
/* - -------- CAN_TIMESTP : (CAN Offset: 0x1c) CAN Timestamp Register -------- */
/* - -------- CAN_ECR : (CAN Offset: 0x20) CAN Error Counter Register -------- */
                                                          AT91C_CAN_REC EQU( 0xFF << 0 );
                                                          -( CAN ) Receive Error Counter
                                                          AT91C_CAN_TEC EQU( 0xFF << 16 );
                                                          -( CAN ) Transmit Error Counter
/* - -------- CAN_TCR : (CAN Offset: 0x24) CAN Transfer Command Register -------- */
                                                          AT91C_CAN_TIMRST EQU( 0x1 << 31 );
                                                          -( CAN ) Timer Reset ميدان_2
/* - -------- CAN_ACR : (CAN Offset: 0x28) CAN Abort Command Register -------- */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Ethernet MAC 10/100 */
/* - ***************************************************************************** */
/* - -------- EMAC_NCR : (EMAC Offset: 0x0)  -------- */
                                                          AT91C_EMAC_LB EQU( 0x1 << 0 );
                                                          -( EMAC ) Loopback.Optional.When سيٽ, loopback إشارة is at مٿاهون_2 level.
                                                             AT91C_EMAC_LLB EQU( 0x1 << 1 );
                                                          -( EMAC ) Loopback local.
                                                             AT91C_EMAC_RE EQU( 0x1 << 2 );
                                                          -( EMAC ) Receive enable.
                                                             AT91C_EMAC_TE EQU( 0x1 << 3 );
                                                          -( EMAC ) Transmit enable.
                                                             AT91C_EMAC_MPE EQU( 0x1 << 4 );
                                                          -( EMAC ) Management پورٽ enable.
                                                             AT91C_EMAC_CLRSTAT EQU( 0x1 << 5 );
                                                          -( EMAC ) Clear statistics registers.
                                                             AT91C_EMAC_INCSTAT EQU( 0x1 << 6 );
                                                          -( EMAC ) Increment statistics registers.
                                                             AT91C_EMAC_WESTAT EQU( 0x1 << 7 );
                                                          -( EMAC ) Write enable

                                                          لكل statistics registers.
                                                             AT91C_EMAC_BP EQU( 0x1 << 8 );
                                                          -( EMAC ) پٺ pressure.
                                                             AT91C_EMAC_TSTART EQU( 0x1 << 9 );
                                                          -( EMAC ) شروعات_2 ترسيل.
                                                             AT91C_EMAC_THALT EQU( 0x1 << 10 );
                                                          -( EMAC ) ترسيل Halt.
                                                             AT91C_EMAC_TPFR EQU( 0x1 << 11 );
                                                          -( EMAC ) Transmit pause چوکٺو_2
                                                          AT91C_EMAC_TZQ EQU( 0x1 << 12 );
                                                          -( EMAC ) Transmit zero وقتي_حصو pause چوکٺو_2
/* - -------- EMAC_NCFGR : (EMAC Offset: 0x4) Network Configuration Register -------- */
                                                          AT91C_EMAC_SPD EQU( 0x1 << 0 );
                                                          -( EMAC ) رفتار.
                                                             AT91C_EMAC_FD EQU( 0x1 << 1 );
                                                          -( EMAC ) ڀريل duplex.
                                                             AT91C_EMAC_JFRAME EQU( 0x1 << 3 );
                                                          -( EMAC ) Jumbo چوکٺا.
                                                             AT91C_EMAC_CAF EQU( 0x1 << 4 );
                                                          -( EMAC ) Copy all چوکٺا_2.
                                                             AT91C_EMAC_NBC EQU( 0x1 << 5 );
                                                          -( EMAC ) No نشر.
                                                             AT91C_EMAC_MTI EQU( 0x1 << 6 );
                                                          -( EMAC ) Multicast hash event enable
                                                          AT91C_EMAC_UNI EQU( 0x1 << 7 );
                                                          -( EMAC ) Unicast hash enable.
                                                             AT91C_EMAC_BIG EQU( 0x1 << 8 );
                                                          -( EMAC ) Receive 1522 بائيٽون_2.
                                                             AT91C_EMAC_EAE EQU( 0x1 << 9 );
                                                          -( EMAC ) External پتو_2 ميلاپ enable.
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
                                                          AT91_C_EMAC_RBOF_وٿي_0 EQU( 0x0 << 14 );
                                                          -( EMAC ) no offset from شروعات جو receive بفر_2
                                                          AT91_C_EMAC_RBOF_وٿي_1 EQU( 0x1 << 14 );
                                                          -( EMAC ) one byte offset from شروعات جو receive بفر_2
                                                          AT91_C_EMAC_RBOF_وٿي_2 EQU( 0x2 << 14 );
                                                          -( EMAC ) two بائيٽون_2 offset from شروعات جو receive بفر_2
                                                          AT91_C_EMAC_RBOF_وٿي_3 EQU( 0x3 << 14 );
                                                          -( EMAC ) three بائيٽون_2 offset from شروعات جو receive بفر_2
                                                          AT91C_EMAC_RLCE EQU( 0x1 << 16 );
                                                          -( EMAC ) Receive ڊيگهائي ميدان Checking Enable
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
                                                          AT91_C_EMAC_کانو EQU( 0x1 << 1 );
                                                          -( EMAC )
                                                          AT91C_EMAC_RLES EQU( 0x1 << 2 );
                                                          -( EMAC )
                                                          AT91C_EMAC_TGO EQU( 0x1 << 3 );
                                                          -( EMAC ) Transmit Go
                                                          AT91C_EMAC_BEX EQU( 0x1 << 4 );
                                                          -( EMAC ) Buffers exhausted mid چوکٺو_2
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
                                                          AT91_C_EMAC_معلومات EQU( 0xFFFF << 0 );
                                                          -( EMAC )
                                                          AT91_C_EMAC_ڪوڊ EQU( 0x3 << 16 );
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
                                                          -( EMAC ) ARP request IP پتو_2
                                                          AT91C_EMAC_MAG EQU( 0x1 << 16 );
                                                          -( EMAC ) Magic packet event enable
                                                          AT91C_EMAC_ARP EQU( 0x1 << 17 );
                                                          -( EMAC ) ARP request event enable
                                                          AT91C_EMAC_SA1 EQU( 0x1 << 18 );
                                                          -( EMAC ) Specific پتو_2 سجل 1 event enable
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
                                                          AT91_C_ADC_شروعات EQU( 0x1 << 1 );
                                                          -( ADC ) شروعات_2 Conversion
/* - -------- ADC_MR : (ADC Offset: 0x4) ADC Mode Register -------- */
                                                          AT91C_ADC_TRGEN EQU( 0x1 << 0 );
                                                          -( ADC ) Trigger Enable
                                                          AT91C_ADC_TRGEN_DIS EQU( 0x0 );
                                                          -( ADC ) Hardware triggers are disabled.Starting a conversion is only possible by software
                                                          AT91C_ADC_TRGEN_EN EQU( 0x1 );
                                                          -( ADC ) Hardware trigger selected by TRGSEL ميدان is enabled.
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
                                                             AT91_C_ADC_LOWRES_10_ٻٽو_انگ EQU( 0x0 << 4 );
                                                          -( ADC ) 10 - ٻٽو_انگ_2 resolution
                                                          AT91_C_ADC_LOWRES_8_ٻٽو_انگ EQU( 0x1 << 4 );
                                                          -( ADC ) 8 - ٻٽو_انگ_2 resolution
                                                          AT91C_ADC_SLEEP EQU( 0x1 << 5 );
                                                          -( ADC ) Sleep گهڻائي
                                                          AT91_C_ADC_SLEEP_عام_گهڻائي EQU( 0x0 << 5 );
                                                          -( ADC ) عام_2 گهڻائي
                                                          AT91_C_ADC_SLEEP_گهڻائي EQU( 0x1 << 5 );
                                                          -( ADC ) Sleep گهڻائي
                                                          AT91C_ADC_PRESCAL EQU( 0x3F << 8 );
                                                          -( ADC ) Prescaler شرح_2 selection
                                                          AT91C_ADC_STARTUP EQU( 0x1F << 16 );
                                                          -( ADC ) Startup وقت
                                                          AT91C_ADC_SHTIM EQU( 0xF << 24 );
                                                          -( ADC ) Sample & Hold وقت
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
                                                          -( ADC ) پڇاڙي_2 جو Conversion
                                                          AT91C_ADC_EOC1 EQU( 0x1 << 1 );
                                                          -( ADC ) پڇاڙي_2 جو Conversion
                                                          AT91C_ADC_EOC2 EQU( 0x1 << 2 );
                                                          -( ADC ) پڇاڙي_2 جو Conversion
                                                          AT91C_ADC_EOC3 EQU( 0x1 << 3 );
                                                          -( ADC ) پڇاڙي_2 جو Conversion
                                                          AT91C_ADC_EOC4 EQU( 0x1 << 4 );
                                                          -( ADC ) پڇاڙي_2 جو Conversion
                                                          AT91C_ADC_EOC5 EQU( 0x1 << 5 );
                                                          -( ADC ) پڇاڙي_2 جو Conversion
                                                          AT91C_ADC_EOC6 EQU( 0x1 << 6 );
                                                          -( ADC ) پڇاڙي_2 جو Conversion
                                                          AT91C_ADC_EOC7 EQU( 0x1 << 7 );
                                                          -( ADC ) پڇاڙي_2 جو Conversion
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
                                                          -( ADC ) معلومات Ready
                                                          AT91C_ADC_GOVRE EQU( 0x1 << 17 );
                                                          -( ADC ) General Overrun
                                                          AT91C_ADC_ENDRX EQU( 0x1 << 18 );
                                                          -( ADC ) پڇاڙي_2 جو Receiver Transfer
                                                          AT91C_ADC_RXBUFF EQU( 0x1 << 19 );
                                                          -( ADC ) RXBUFF مداخلت_2
/* - -------- ADC_LCDR : (ADC Offset: 0x20) ADC Last Converted Data Register -------- */
                                                          AT91C_ADC_LDATA EQU( 0x3FF << 0 );
                                                          -( ADC ) آخري معلومات Converted
/* - -------- ADC_IER : (ADC Offset: 0x24) ADC Interrupt Enable Register -------- */
/* - -------- ADC_IDR : (ADC Offset: 0x28) ADC Interrupt Disable Register -------- */
/* - -------- ADC_IMR : (ADC Offset: 0x2c) ADC Interrupt Mask Register -------- */
/* - -------- ADC_CDR0 : (ADC Offset: 0x30) ADC Channel Data Register 0 -------- */
                                                          AT91_C_ADC_معلومات EQU( 0x3FF << 0 );
                                                          -( ADC ) Converted معلومات
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
                                                          AT91_C_AES_شروعات EQU( 0x1 << 0 );
                                                          -( AES ) Starts Processing
                                                          AT91C_AES_SWRST EQU( 0x1 << 8 );
                                                          -( AES ) Software Reset
                                                          AT91C_AES_LOADSEED EQU( 0x1 << 16 );
                                                          -( AES ) Random عدد_2 Generator ٻج Loading
/* - -------- AES_MR : (AES Offset: 0x4) Mode Register -------- */
                                                          AT91C_AES_CIPHER EQU( 0x1 << 0 );
                                                          -( AES ) Processing گهڻائي
                                                          AT91C_AES_PROCDLY EQU( 0xF << 4 );
                                                          -( AES ) Processing Delay
                                                          AT91C_AES_SMOD EQU( 0x3 << 8 );
                                                          -( AES ) شروعات_2 گهڻائي
                                                          AT91C_AES_SMOD_MANUAL EQU( 0x0 << 8 );
                                                          -( AES ) Manual گهڻائي:The شروعات_3 ٻٽو_انگ_2 اندريون سجل AES_CR must be سيٽ منزل begin encryption or decryption.
                                                             AT91C_AES_SMOD_AUTO EQU( 0x1 << 8 );
                                                          -( AES ) Auto گهڻائي:no action اندريون AES_CR is necessary( cf datasheet ).
                                                             AT91C_AES_SMOD_PDC EQU( 0x2 << 8 );
                                                          -( AES ) PDC گهڻائي( cf datasheet ).
                                                             AT91C_AES_OPMOD EQU( 0x7 << 12 );
                                                          -( AES ) Operation گهڻائي
                                                          AT91C_AES_OPMOD_ECB EQU( 0x0 << 12 );
                                                          -( AES ) ECB Electronic ڪوڊ_Book گهڻائي_2.
                                                             AT91C_AES_OPMOD_CBC EQU( 0x1 << 12 );
                                                          -( AES ) CBC Cipher بلاڪ Chaining گهڻائي_2.
                                                             AT91C_AES_OPMOD_OFB EQU( 0x2 << 12 );
                                                          -( AES ) OFB Output Feedback گهڻائي_2.
                                                             AT91C_AES_OPMOD_CFB EQU( 0x3 << 12 );
                                                          -( AES ) CFB Cipher Feedback گهڻائي_2.
                                                             AT91C_AES_OPMOD_CTR EQU( 0x4 << 12 );
                                                          -( AES ) CTR Counter گهڻائي_2.
                                                             AT91C_AES_LOD EQU( 0x1 << 15 );
                                                          -( AES ) آخري Output معلومات گهڻائي
                                                          AT91C_AES_CFBS EQU( 0x7 << 16 );
                                                          -( AES ) Cipher Feedback معلومات سائيز_2
                                                          AT91_C_AES_CFBS_128_ٻٽو_انگ EQU( 0x0 << 16 );
                                                          -( AES ) 128 - ٻٽو_انگ_2.
                                                             AT91_C_AES_CFBS_64_ٻٽو_انگ EQU( 0x1 << 16 );
                                                          -( AES ) 64 - ٻٽو_انگ_2.
                                                             AT91_C_AES_CFBS_32_ٻٽو_انگ EQU( 0x2 << 16 );
                                                          -( AES ) 32 - ٻٽو_انگ_2.
                                                             AT91_C_AES_CFBS_16_ٻٽو_انگ EQU( 0x3 << 16 );
                                                          -( AES ) 16 - ٻٽو_انگ_2.
                                                             AT91_C_AES_CFBS_8_ٻٽو_انگ EQU( 0x4 << 16 );
                                                          -( AES ) 8 - ٻٽو_انگ_2.
                                                             AT91C_AES_CKEY EQU( 0xF << 20 );
                                                          -( AES ) Countermeasure ڪنجي_2
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
                                                          -( AES ) PDC Read بفر پڇاڙي_2
                                                          AT91C_AES_ENDTX EQU( 0x1 << 2 );
                                                          -( AES ) PDC Write بفر پڇاڙي_2
                                                          AT91C_AES_RXBUFF EQU( 0x1 << 3 );
                                                          -( AES ) PDC Read بفر ڀريل
                                                          AT91C_AES_TXBUFE EQU( 0x1 << 4 );
                                                          -( AES ) PDC Write بفر خالي_جايون
                                                          AT91C_AES_URAD EQU( 0x1 << 8 );
                                                          -( AES ) Unspecified رجسٽر Access Detection
/* - -------- AES_IDR : (AES Offset: 0x14) Interrupt Disable Register -------- */
/* - -------- AES_IMR : (AES Offset: 0x18) Interrupt Mask Register -------- */
/* - -------- AES_ISR : (AES Offset: 0x1c) Interrupt Status Register -------- */
                                                          AT91C_AES_URAT EQU( 0x7 << 12 );
                                                          -( AES ) Unspecified رجسٽر Access Type حالت
                                                          AT91_C_AES_URAT_اندريون_DAT_WRITE_DATPROC EQU( 0x0 << 12 );
                                                          -( AES ) داخلا معلومات_2 سجل written during the معلومات_2 processing اندريون PDC گهڻائي_2.
                                                             AT91_C_AES_URAT_ٻاهريون_DAT_READ_DATPROC EQU( 0x1 << 12 );
                                                          -( AES ) Output معلومات_2 سجل اقرأ during the معلومات_2 processing.
                                                             AT91C_AES_URAT_MODEREG_WRITE_DATPROC EQU( 0x2 << 12 );
                                                          -( AES ) گهڻائي سجل written during the معلومات_2 processing.
                                                             AT91_C_AES_URAT_ٻاهريون_DAT_READ_SUBKEY EQU( 0x3 << 12 );
                                                          -( AES ) Output معلومات_2 سجل اقرأ during the sub - ڪنجيون generation.
                                                             AT91C_AES_URAT_MODEREG_WRITE_SUBKEY EQU( 0x4 << 12 );
                                                          -( AES ) گهڻائي سجل written during the sub - ڪنجيون generation.
                                                             AT91C_AES_URAT_WO_REG_READ EQU( 0x5 << 12 );
                                                          -( AES ) Write - only سجل اقرأ access.

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Triple Data Encryption Standard */
/* - ***************************************************************************** */
/* - -------- TDES_CR : (TDES Offset: 0x0) Control Register -------- */
                                                             AT91_C_TDES_شروعات EQU( 0x1 << 0 );
                                                          -( TDES ) Starts Processing
                                                          AT91C_TDES_SWRST EQU( 0x1 << 8 );
                                                          -( TDES ) Software Reset
/* - -------- TDES_MR : (TDES Offset: 0x4) Mode Register -------- */
                                                          AT91C_TDES_CIPHER EQU( 0x1 << 0 );
                                                          -( TDES ) Processing گهڻائي
                                                          AT91C_TDES_TDESMOD EQU( 0x1 << 1 );
                                                          -( TDES ) Single or Triple DES گهڻائي
                                                          AT91C_TDES_KEYMOD EQU( 0x1 << 4 );
                                                          -( TDES ) ڪنجي_2 گهڻائي
                                                          AT91C_TDES_SMOD EQU( 0x3 << 8 );
                                                          -( TDES ) شروعات_2 گهڻائي
                                                          AT91C_TDES_SMOD_MANUAL EQU( 0x0 << 8 );
                                                          -( TDES ) Manual گهڻائي:The شروعات_3 ٻٽو_انگ_2 اندريون سجل TDES_CR must be سيٽ منزل begin encryption or decryption.
                                                             AT91C_TDES_SMOD_AUTO EQU( 0x1 << 8 );
                                                          -( TDES ) Auto گهڻائي:no action اندريون TDES_CR is necessary( cf datasheet ).
                                                             AT91C_TDES_SMOD_PDC EQU( 0x2 << 8 );
                                                          -( TDES ) PDC گهڻائي( cf datasheet ).
                                                             AT91C_TDES_OPMOD EQU( 0x3 << 12 );
                                                          -( TDES ) Operation گهڻائي
                                                          AT91C_TDES_OPMOD_ECB EQU( 0x0 << 12 );
                                                          -( TDES ) ECB Electronic ڪوڊ_Book گهڻائي_2.
                                                             AT91C_TDES_OPMOD_CBC EQU( 0x1 << 12 );
                                                          -( TDES ) CBC Cipher بلاڪ Chaining گهڻائي_2.
                                                             AT91C_TDES_OPMOD_OFB EQU( 0x2 << 12 );
                                                          -( TDES ) OFB Output Feedback گهڻائي_2.
                                                             AT91C_TDES_OPMOD_CFB EQU( 0x3 << 12 );
                                                          -( TDES ) CFB Cipher Feedback گهڻائي_2.
                                                             AT91C_TDES_LOD EQU( 0x1 << 15 );
                                                          -( TDES ) آخري Output معلومات گهڻائي
                                                          AT91C_TDES_CFBS EQU( 0x3 << 16 );
                                                          -( TDES ) Cipher Feedback معلومات سائيز_2
                                                          AT91_C_TDES_CFBS_64_ٻٽو_انگ EQU( 0x0 << 16 );
                                                          -( TDES ) 64 - ٻٽو_انگ_2.
                                                             AT91_C_TDES_CFBS_32_ٻٽو_انگ EQU( 0x1 << 16 );
                                                          -( TDES ) 32 - ٻٽو_انگ_2.
                                                             AT91_C_TDES_CFBS_16_ٻٽو_انگ EQU( 0x2 << 16 );
                                                          -( TDES ) 16 - ٻٽو_انگ_2.
                                                             AT91_C_TDES_CFBS_8_ٻٽو_انگ EQU( 0x3 << 16 );
                                                          -( TDES ) 8 - ٻٽو_انگ_2.
/* - -------- TDES_IER : (TDES Offset: 0x10) Interrupt Enable Register -------- */
                                                             AT91C_TDES_DATRDY EQU( 0x1 << 0 );
                                                          -( TDES ) DATRDY
                                                          AT91C_TDES_ENDRX EQU( 0x1 << 1 );
                                                          -( TDES ) PDC Read بفر پڇاڙي_2
                                                          AT91C_TDES_ENDTX EQU( 0x1 << 2 );
                                                          -( TDES ) PDC Write بفر پڇاڙي_2
                                                          AT91C_TDES_RXBUFF EQU( 0x1 << 3 );
                                                          -( TDES ) PDC Read بفر ڀريل
                                                          AT91C_TDES_TXBUFE EQU( 0x1 << 4 );
                                                          -( TDES ) PDC Write بفر خالي_جايون
                                                          AT91C_TDES_URAD EQU( 0x1 << 8 );
                                                          -( TDES ) Unspecified رجسٽر Access Detection
/* - -------- TDES_IDR : (TDES Offset: 0x14) Interrupt Disable Register -------- */
/* - -------- TDES_IMR : (TDES Offset: 0x18) Interrupt Mask Register -------- */
/* - -------- TDES_ISR : (TDES Offset: 0x1c) Interrupt Status Register -------- */
                                                          AT91C_TDES_URAT EQU( 0x3 << 12 );
                                                          -( TDES ) Unspecified رجسٽر Access Type حالت
                                                          AT91_C_TDES_URAT_اندريون_DAT_WRITE_DATPROC EQU( 0x0 << 12 );
                                                          -( TDES ) داخلا معلومات_2 سجل written during the معلومات_2 processing اندريون PDC گهڻائي_2.
                                                             AT91_C_TDES_URAT_ٻاهريون_DAT_READ_DATPROC EQU( 0x1 << 12 );
                                                          -( TDES ) Output معلومات_2 سجل اقرأ during the معلومات_2 processing.
                                                             AT91C_TDES_URAT_MODEREG_WRITE_DATPROC EQU( 0x2 << 12 );
                                                          -( TDES ) گهڻائي سجل written during the معلومات_2 processing.
                                                             AT91C_TDES_URAT_WO_REG_READ EQU( 0x3 << 12 );
                                                          -( TDES ) Write - only سجل اقرأ access.

/* - ***************************************************************************** */
/* -               REGISTER ADDRESS DEFINITION FOR AT91SAM7X256 */
/* - ***************************************************************************** */
/* - ========== Register definition for SYS peripheral ========== */
/* - ========== Register definition for AIC peripheral ========== */
                                                             AT91C_AIC_IVR EQU( 0xFFFFF100 );
                                                          -( AIC ) IRQ ويڪٽر_2 رجسٽر
                                                          AT91C_AIC_SMR EQU( 0xFFFFF000 );
                                                          -( AIC ) ذريعو_2 گهڻائي رجسٽر
                                                          AT91C_AIC_FVR EQU( 0xFFFFF104 );
                                                          -( AIC ) FIQ ويڪٽر_2 رجسٽر
                                                          AT91C_AIC_DCR EQU( 0xFFFFF138 );
                                                          -( AIC ) Debug Control رجسٽر( Protect )
                                                          AT91C_AIC_EOICR EQU( 0xFFFFF130 );
                                                          -( AIC ) پڇاڙي_2 جو مداخلت_2 Command رجسٽر
                                                          AT91C_AIC_SVR EQU( 0xFFFFF080 );
                                                          -( AIC ) ذريعو_2 ويڪٽر_2 رجسٽر
                                                          AT91C_AIC_FFSR EQU( 0xFFFFF148 );
                                                          -( AIC ) Fast Forcing حالت رجسٽر
                                                          AT91C_AIC_ICCR EQU( 0xFFFFF128 );
                                                          -( AIC ) مداخلت_2 Clear Command رجسٽر
                                                          AT91C_AIC_ISR EQU( 0xFFFFF108 );
                                                          -( AIC ) مداخلت_2 حالت رجسٽر
                                                          AT91C_AIC_IMR EQU( 0xFFFFF110 );
                                                          -( AIC ) مداخلت_2 نقاب_2 رجسٽر
                                                          AT91C_AIC_IPR EQU( 0xFFFFF10C );
                                                          -( AIC ) مداخلت_2 Pending رجسٽر
                                                          AT91C_AIC_FFER EQU( 0xFFFFF140 );
                                                          -( AIC ) Fast Forcing Enable رجسٽر
                                                          AT91C_AIC_IECR EQU( 0xFFFFF120 );
                                                          -( AIC ) مداخلت_2 Enable Command رجسٽر
                                                          AT91C_AIC_ISCR EQU( 0xFFFFF12C );
                                                          -( AIC ) مداخلت_2 سيٽ_2 Command رجسٽر
                                                          AT91C_AIC_FFDR EQU( 0xFFFFF144 );
                                                          -( AIC ) Fast Forcing Disable رجسٽر
                                                          AT91C_AIC_CISR EQU( 0xFFFFF114 );
                                                          -( AIC ) Core مداخلت_2 حالت رجسٽر
                                                          AT91C_AIC_IDCR EQU( 0xFFFFF124 );
                                                          -( AIC ) مداخلت_2 Disable Command رجسٽر
                                                          AT91C_AIC_SPU EQU( 0xFFFFF134 );
                                                          -( AIC ) Spurious ويڪٽر_2 رجسٽر
/* - ========== Register definition for PDC_DBGU peripheral ========== */
                                                          AT91C_DBGU_TCR EQU( 0xFFFFF30C );
                                                          -( PDC_DBGU ) Transmit Counter رجسٽر
                                                          AT91C_DBGU_RNPR EQU( 0xFFFFF310 );
                                                          -( PDC_DBGU ) Receive ايندڙ اشارو رجسٽر
                                                          AT91C_DBGU_TNPR EQU( 0xFFFFF318 );
                                                          -( PDC_DBGU ) Transmit ايندڙ اشارو رجسٽر
                                                          AT91C_DBGU_TPR EQU( 0xFFFFF308 );
                                                          -( PDC_DBGU ) Transmit اشارو رجسٽر
                                                          AT91C_DBGU_RPR EQU( 0xFFFFF300 );
                                                          -( PDC_DBGU ) Receive اشارو رجسٽر
                                                          AT91C_DBGU_RCR EQU( 0xFFFFF304 );
                                                          -( PDC_DBGU ) Receive Counter رجسٽر
                                                          AT91C_DBGU_RNCR EQU( 0xFFFFF314 );
                                                          -( PDC_DBGU ) Receive ايندڙ Counter رجسٽر
                                                          AT91C_DBGU_PTCR EQU( 0xFFFFF320 );
                                                          -( PDC_DBGU ) PDC Transfer Control رجسٽر
                                                          AT91C_DBGU_PTSR EQU( 0xFFFFF324 );
                                                          -( PDC_DBGU ) PDC Transfer حالت رجسٽر
                                                          AT91C_DBGU_TNCR EQU( 0xFFFFF31C );
                                                          -( PDC_DBGU ) Transmit ايندڙ Counter رجسٽر
/* - ========== Register definition for DBGU peripheral ========== */
                                                          AT91C_DBGU_EXID EQU( 0xFFFFF244 );
                                                          -( DBGU ) Chip ID Extension رجسٽر
                                                          AT91C_DBGU_BRGR EQU( 0xFFFFF220 );
                                                          -( DBGU ) Baud شرح Generator رجسٽر
                                                          AT91C_DBGU_IDR EQU( 0xFFFFF20C );
                                                          -( DBGU ) مداخلت_2 Disable رجسٽر
                                                          AT91C_DBGU_CSR EQU( 0xFFFFF214 );
                                                          -( DBGU ) Channel حالت رجسٽر
                                                          AT91C_DBGU_CIDR EQU( 0xFFFFF240 );
                                                          -( DBGU ) Chip ID رجسٽر
                                                          AT91C_DBGU_MR EQU( 0xFFFFF204 );
                                                          -( DBGU ) گهڻائي رجسٽر
                                                          AT91C_DBGU_IMR EQU( 0xFFFFF210 );
                                                          -( DBGU ) مداخلت_2 نقاب_2 رجسٽر
                                                          AT91C_DBGU_CR EQU( 0xFFFFF200 );
                                                          -( DBGU ) Control رجسٽر
                                                          AT91C_DBGU_FNTR EQU( 0xFFFFF248 );
                                                          -( DBGU ) Force NTRST رجسٽر
                                                          AT91C_DBGU_THR EQU( 0xFFFFF21C );
                                                          -( DBGU ) Transmitter Holding رجسٽر
                                                          AT91C_DBGU_RHR EQU( 0xFFFFF218 );
                                                          -( DBGU ) Receiver Holding رجسٽر
                                                          AT91C_DBGU_IER EQU( 0xFFFFF208 );
                                                          -( DBGU ) مداخلت_2 Enable رجسٽر
/* - ========== Register definition for PIOA peripheral ========== */
                                                          AT91C_PIOA_ODR EQU( 0xFFFFF414 );
                                                          -( PIOA ) Output Disable Registerr
                                                          AT91C_PIOA_SODR EQU( 0xFFFFF430 );
                                                          -( PIOA ) سيٽ_2 Output معلومات رجسٽر
                                                          AT91C_PIOA_ISR EQU( 0xFFFFF44C );
                                                          -( PIOA ) مداخلت_2 حالت رجسٽر
                                                          AT91C_PIOA_ABSR EQU( 0xFFFFF478 );
                                                          -( PIOA ) AB Select حالت رجسٽر
                                                          AT91C_PIOA_IER EQU( 0xFFFFF440 );
                                                          -( PIOA ) مداخلت_2 Enable رجسٽر
                                                          AT91C_PIOA_PPUDR EQU( 0xFFFFF460 );
                                                          -( PIOA ) Pull - مٿي Disable رجسٽر
                                                          AT91C_PIOA_IMR EQU( 0xFFFFF448 );
                                                          -( PIOA ) مداخلت_2 نقاب_2 رجسٽر
                                                          AT91_C_PIOA_في EQU( 0xFFFFF400 );
                                                          -( PIOA ) PIO Enable رجسٽر
                                                          AT91C_PIOA_IFDR EQU( 0xFFFFF424 );
                                                          -( PIOA ) داخلا Filter Disable رجسٽر
                                                          AT91C_PIOA_OWDR EQU( 0xFFFFF4A4 );
                                                          -( PIOA ) Output Write Disable رجسٽر
                                                          AT91C_PIOA_MDSR EQU( 0xFFFFF458 );
                                                          -( PIOA ) Multi - driver حالت رجسٽر
                                                          AT91C_PIOA_IDR EQU( 0xFFFFF444 );
                                                          -( PIOA ) مداخلت_2 Disable رجسٽر
                                                          AT91C_PIOA_ODSR EQU( 0xFFFFF438 );
                                                          -( PIOA ) Output معلومات حالت رجسٽر
                                                          AT91C_PIOA_PPUSR EQU( 0xFFFFF468 );
                                                          -( PIOA ) Pull - مٿي حالت رجسٽر
                                                          AT91C_PIOA_OWSR EQU( 0xFFFFF4A8 );
                                                          -( PIOA ) Output Write حالت رجسٽر
                                                          AT91C_PIOA_BSR EQU( 0xFFFFF474 );
                                                          -( PIOA ) Select B رجسٽر
                                                          AT91C_PIOA_OWER EQU( 0xFFFFF4A0 );
                                                          -( PIOA ) Output Write Enable رجسٽر
                                                          AT91C_PIOA_IFER EQU( 0xFFFFF420 );
                                                          -( PIOA ) داخلا Filter Enable رجسٽر
                                                          AT91C_PIOA_PDSR EQU( 0xFFFFF43C );
                                                          -( PIOA ) Pin معلومات حالت رجسٽر
                                                          AT91C_PIOA_PPUER EQU( 0xFFFFF464 );
                                                          -( PIOA ) Pull - مٿي Enable رجسٽر
                                                          AT91C_PIOA_OSR EQU( 0xFFFFF418 );
                                                          -( PIOA ) Output حالت رجسٽر
                                                          AT91C_PIOA_ASR EQU( 0xFFFFF470 );
                                                          -( PIOA ) Select A رجسٽر
                                                          AT91C_PIOA_MDDR EQU( 0xFFFFF454 );
                                                          -( PIOA ) Multi - driver Disable رجسٽر
                                                          AT91C_PIOA_CODR EQU( 0xFFFFF434 );
                                                          -( PIOA ) Clear Output معلومات رجسٽر
                                                          AT91C_PIOA_MDER EQU( 0xFFFFF450 );
                                                          -( PIOA ) Multi - driver Enable رجسٽر
                                                          AT91C_PIOA_PDR EQU( 0xFFFFF404 );
                                                          -( PIOA ) PIO Disable رجسٽر
                                                          AT91C_PIOA_IFSR EQU( 0xFFFFF428 );
                                                          -( PIOA ) داخلا Filter حالت رجسٽر
                                                          AT91C_PIOA_OER EQU( 0xFFFFF410 );
                                                          -( PIOA ) Output Enable رجسٽر
                                                          AT91C_PIOA_PSR EQU( 0xFFFFF408 );
                                                          -( PIOA ) PIO حالت رجسٽر
/* - ========== Register definition for PIOB peripheral ========== */
                                                          AT91C_PIOB_OWDR EQU( 0xFFFFF6A4 );
                                                          -( PIOB ) Output Write Disable رجسٽر
                                                          AT91C_PIOB_MDER EQU( 0xFFFFF650 );
                                                          -( PIOB ) Multi - driver Enable رجسٽر
                                                          AT91C_PIOB_PPUSR EQU( 0xFFFFF668 );
                                                          -( PIOB ) Pull - مٿي حالت رجسٽر
                                                          AT91C_PIOB_IMR EQU( 0xFFFFF648 );
                                                          -( PIOB ) مداخلت_2 نقاب_2 رجسٽر
                                                          AT91C_PIOB_ASR EQU( 0xFFFFF670 );
                                                          -( PIOB ) Select A رجسٽر
                                                          AT91C_PIOB_PPUDR EQU( 0xFFFFF660 );
                                                          -( PIOB ) Pull - مٿي Disable رجسٽر
                                                          AT91C_PIOB_PSR EQU( 0xFFFFF608 );
                                                          -( PIOB ) PIO حالت رجسٽر
                                                          AT91C_PIOB_IER EQU( 0xFFFFF640 );
                                                          -( PIOB ) مداخلت_2 Enable رجسٽر
                                                          AT91C_PIOB_CODR EQU( 0xFFFFF634 );
                                                          -( PIOB ) Clear Output معلومات رجسٽر
                                                          AT91C_PIOB_OWER EQU( 0xFFFFF6A0 );
                                                          -( PIOB ) Output Write Enable رجسٽر
                                                          AT91C_PIOB_ABSR EQU( 0xFFFFF678 );
                                                          -( PIOB ) AB Select حالت رجسٽر
                                                          AT91C_PIOB_IFDR EQU( 0xFFFFF624 );
                                                          -( PIOB ) داخلا Filter Disable رجسٽر
                                                          AT91C_PIOB_PDSR EQU( 0xFFFFF63C );
                                                          -( PIOB ) Pin معلومات حالت رجسٽر
                                                          AT91C_PIOB_IDR EQU( 0xFFFFF644 );
                                                          -( PIOB ) مداخلت_2 Disable رجسٽر
                                                          AT91C_PIOB_OWSR EQU( 0xFFFFF6A8 );
                                                          -( PIOB ) Output Write حالت رجسٽر
                                                          AT91C_PIOB_PDR EQU( 0xFFFFF604 );
                                                          -( PIOB ) PIO Disable رجسٽر
                                                          AT91C_PIOB_ODR EQU( 0xFFFFF614 );
                                                          -( PIOB ) Output Disable Registerr
                                                          AT91C_PIOB_IFSR EQU( 0xFFFFF628 );
                                                          -( PIOB ) داخلا Filter حالت رجسٽر
                                                          AT91C_PIOB_PPUER EQU( 0xFFFFF664 );
                                                          -( PIOB ) Pull - مٿي Enable رجسٽر
                                                          AT91C_PIOB_SODR EQU( 0xFFFFF630 );
                                                          -( PIOB ) سيٽ_2 Output معلومات رجسٽر
                                                          AT91C_PIOB_ISR EQU( 0xFFFFF64C );
                                                          -( PIOB ) مداخلت_2 حالت رجسٽر
                                                          AT91C_PIOB_ODSR EQU( 0xFFFFF638 );
                                                          -( PIOB ) Output معلومات حالت رجسٽر
                                                          AT91C_PIOB_OSR EQU( 0xFFFFF618 );
                                                          -( PIOB ) Output حالت رجسٽر
                                                          AT91C_PIOB_MDSR EQU( 0xFFFFF658 );
                                                          -( PIOB ) Multi - driver حالت رجسٽر
                                                          AT91C_PIOB_IFER EQU( 0xFFFFF620 );
                                                          -( PIOB ) داخلا Filter Enable رجسٽر
                                                          AT91C_PIOB_BSR EQU( 0xFFFFF674 );
                                                          -( PIOB ) Select B رجسٽر
                                                          AT91C_PIOB_MDDR EQU( 0xFFFFF654 );
                                                          -( PIOB ) Multi - driver Disable رجسٽر
                                                          AT91C_PIOB_OER EQU( 0xFFFFF610 );
                                                          -( PIOB ) Output Enable رجسٽر
                                                          AT91_C_PIOB_في EQU( 0xFFFFF600 );
                                                          -( PIOB ) PIO Enable رجسٽر
/* - ========== Register definition for CKGR peripheral ========== */
                                                          AT91C_CKGR_MOR EQU( 0xFFFFFC20 );
                                                          -( CKGR ) Main Oscillator رجسٽر
                                                          AT91C_CKGR_PLLR EQU( 0xFFFFFC2C );
                                                          -( CKGR ) PLL رجسٽر
                                                          AT91C_CKGR_MCFR EQU( 0xFFFFFC24 );
                                                          -( CKGR ) Main Clock Frequency رجسٽر
/* - ========== Register definition for PMC peripheral ========== */
                                                          AT91C_PMC_IDR EQU( 0xFFFFFC64 );
                                                          -( PMC ) مداخلت_2 Disable رجسٽر
                                                          AT91C_PMC_MOR EQU( 0xFFFFFC20 );
                                                          -( PMC ) Main Oscillator رجسٽر
                                                          AT91C_PMC_PLLR EQU( 0xFFFFFC2C );
                                                          -( PMC ) PLL رجسٽر
                                                          AT91C_PMC_PCER EQU( 0xFFFFFC10 );
                                                          -( PMC ) Peripheral Clock Enable رجسٽر
                                                          AT91C_PMC_PCKR EQU( 0xFFFFFC40 );
                                                          -( PMC ) Programmable Clock رجسٽر
                                                          AT91C_PMC_MCKR EQU( 0xFFFFFC30 );
                                                          -( PMC ) Master Clock رجسٽر
                                                          AT91C_PMC_SCDR EQU( 0xFFFFFC04 );
                                                          -( PMC ) System Clock Disable رجسٽر
                                                          AT91C_PMC_PCDR EQU( 0xFFFFFC14 );
                                                          -( PMC ) Peripheral Clock Disable رجسٽر
                                                          AT91C_PMC_SCSR EQU( 0xFFFFFC08 );
                                                          -( PMC ) System Clock حالت رجسٽر
                                                          AT91C_PMC_PCSR EQU( 0xFFFFFC18 );
                                                          -( PMC ) Peripheral Clock حالت رجسٽر
                                                          AT91C_PMC_MCFR EQU( 0xFFFFFC24 );
                                                          -( PMC ) Main Clock Frequency رجسٽر
                                                          AT91C_PMC_SCER EQU( 0xFFFFFC00 );
                                                          -( PMC ) System Clock Enable رجسٽر
                                                          AT91C_PMC_IMR EQU( 0xFFFFFC6C );
                                                          -( PMC ) مداخلت_2 نقاب_2 رجسٽر
                                                          AT91C_PMC_IER EQU( 0xFFFFFC60 );
                                                          -( PMC ) مداخلت_2 Enable رجسٽر
                                                          AT91C_PMC_SR EQU( 0xFFFFFC68 );
                                                          -( PMC ) حالت رجسٽر
/* - ========== Register definition for RSTC peripheral ========== */
                                                          AT91C_RSTC_RCR EQU( 0xFFFFFD00 );
                                                          -( RSTC ) Reset Control رجسٽر
                                                          AT91C_RSTC_RMR EQU( 0xFFFFFD08 );
                                                          -( RSTC ) Reset گهڻائي رجسٽر
                                                          AT91C_RSTC_RSR EQU( 0xFFFFFD04 );
                                                          -( RSTC ) Reset حالت رجسٽر
/* - ========== Register definition for RTTC peripheral ========== */
                                                          AT91C_RTTC_RTSR EQU( 0xFFFFFD2C );
                                                          -( RTTC ) Real - time حالت رجسٽر
                                                          AT91C_RTTC_RTMR EQU( 0xFFFFFD20 );
                                                          -( RTTC ) Real - time گهڻائي رجسٽر
                                                          AT91C_RTTC_RTVR EQU( 0xFFFFFD28 );
                                                          -( RTTC ) Real - time قدر_2 رجسٽر
                                                          AT91C_RTTC_RTAR EQU( 0xFFFFFD24 );
                                                          -( RTTC ) Real - time Alarm رجسٽر
/* - ========== Register definition for PITC peripheral ========== */
                                                          AT91C_PITC_PIVR EQU( 0xFFFFFD38 );
                                                          -( PITC ) Period Interval قدر_2 رجسٽر
                                                          AT91C_PITC_PISR EQU( 0xFFFFFD34 );
                                                          -( PITC ) Period Interval حالت رجسٽر
                                                          AT91C_PITC_PIIR EQU( 0xFFFFFD3C );
                                                          -( PITC ) Period Interval Image رجسٽر
                                                          AT91C_PITC_PIMR EQU( 0xFFFFFD30 );
                                                          -( PITC ) Period Interval گهڻائي رجسٽر
/* - ========== Register definition for WDTC peripheral ========== */
                                                          AT91C_WDTC_WDCR EQU( 0xFFFFFD40 );
                                                          -( WDTC ) Watchdog Control رجسٽر
                                                          AT91C_WDTC_WDSR EQU( 0xFFFFFD48 );
                                                          -( WDTC ) Watchdog حالت رجسٽر
                                                          AT91C_WDTC_WDMR EQU( 0xFFFFFD44 );
                                                          -( WDTC ) Watchdog گهڻائي رجسٽر
/* - ========== Register definition for VREG peripheral ========== */
                                                          AT91C_VREG_MR EQU( 0xFFFFFD60 );
                                                          -( VREG ) Voltage Regulator گهڻائي رجسٽر
/* - ========== Register definition for MC peripheral ========== */
                                                          AT91C_MC_ASR EQU( 0xFFFFFF04 );
                                                          -( MC ) MC Abort حالت رجسٽر
                                                          AT91C_MC_RCR EQU( 0xFFFFFF00 );
                                                          -( MC ) MC Remap Control رجسٽر
                                                          AT91C_MC_FCR EQU( 0xFFFFFF64 );
                                                          -( MC ) MC Flash Command رجسٽر
                                                          AT91C_MC_AASR EQU( 0xFFFFFF08 );
                                                          -( MC ) MC Abort پتو حالت رجسٽر
                                                          AT91C_MC_FSR EQU( 0xFFFFFF68 );
                                                          -( MC ) MC Flash حالت رجسٽر
                                                          AT91C_MC_FMR EQU( 0xFFFFFF60 );
                                                          -( MC ) MC Flash گهڻائي رجسٽر
/* - ========== Register definition for PDC_SPI1 peripheral ========== */
                                                          AT91C_SPI1_PTCR EQU( 0xFFFE4120 );
                                                          -( PDC_SPI1 ) PDC Transfer Control رجسٽر
                                                          AT91C_SPI1_RPR EQU( 0xFFFE4100 );
                                                          -( PDC_SPI1 ) Receive اشارو رجسٽر
                                                          AT91C_SPI1_TNCR EQU( 0xFFFE411C );
                                                          -( PDC_SPI1 ) Transmit ايندڙ Counter رجسٽر
                                                          AT91C_SPI1_TPR EQU( 0xFFFE4108 );
                                                          -( PDC_SPI1 ) Transmit اشارو رجسٽر
                                                          AT91C_SPI1_TNPR EQU( 0xFFFE4118 );
                                                          -( PDC_SPI1 ) Transmit ايندڙ اشارو رجسٽر
                                                          AT91C_SPI1_TCR EQU( 0xFFFE410C );
                                                          -( PDC_SPI1 ) Transmit Counter رجسٽر
                                                          AT91C_SPI1_RCR EQU( 0xFFFE4104 );
                                                          -( PDC_SPI1 ) Receive Counter رجسٽر
                                                          AT91C_SPI1_RNPR EQU( 0xFFFE4110 );
                                                          -( PDC_SPI1 ) Receive ايندڙ اشارو رجسٽر
                                                          AT91C_SPI1_RNCR EQU( 0xFFFE4114 );
                                                          -( PDC_SPI1 ) Receive ايندڙ Counter رجسٽر
                                                          AT91C_SPI1_PTSR EQU( 0xFFFE4124 );
                                                          -( PDC_SPI1 ) PDC Transfer حالت رجسٽر
/* - ========== Register definition for SPI1 peripheral ========== */
                                                          AT91C_SPI1_IMR EQU( 0xFFFE401C );
                                                          -( SPI1 ) مداخلت_2 نقاب_2 رجسٽر
                                                          AT91C_SPI1_IER EQU( 0xFFFE4014 );
                                                          -( SPI1 ) مداخلت_2 Enable رجسٽر
                                                          AT91C_SPI1_MR EQU( 0xFFFE4004 );
                                                          -( SPI1 ) گهڻائي رجسٽر
                                                          AT91C_SPI1_RDR EQU( 0xFFFE4008 );
                                                          -( SPI1 ) Receive معلومات رجسٽر
                                                          AT91C_SPI1_IDR EQU( 0xFFFE4018 );
                                                          -( SPI1 ) مداخلت_2 Disable رجسٽر
                                                          AT91C_SPI1_SR EQU( 0xFFFE4010 );
                                                          -( SPI1 ) حالت رجسٽر
                                                          AT91C_SPI1_TDR EQU( 0xFFFE400C );
                                                          -( SPI1 ) Transmit معلومات رجسٽر
                                                          AT91C_SPI1_CR EQU( 0xFFFE4000 );
                                                          -( SPI1 ) Control رجسٽر
                                                          AT91C_SPI1_CSR EQU( 0xFFFE4030 );
                                                          -( SPI1 ) Chip Select رجسٽر
/* - ========== Register definition for PDC_SPI0 peripheral ========== */
                                                          AT91C_SPI0_PTCR EQU( 0xFFFE0120 );
                                                          -( PDC_SPI0 ) PDC Transfer Control رجسٽر
                                                          AT91C_SPI0_TPR EQU( 0xFFFE0108 );
                                                          -( PDC_SPI0 ) Transmit اشارو رجسٽر
                                                          AT91C_SPI0_TCR EQU( 0xFFFE010C );
                                                          -( PDC_SPI0 ) Transmit Counter رجسٽر
                                                          AT91C_SPI0_RCR EQU( 0xFFFE0104 );
                                                          -( PDC_SPI0 ) Receive Counter رجسٽر
                                                          AT91C_SPI0_PTSR EQU( 0xFFFE0124 );
                                                          -( PDC_SPI0 ) PDC Transfer حالت رجسٽر
                                                          AT91C_SPI0_RNPR EQU( 0xFFFE0110 );
                                                          -( PDC_SPI0 ) Receive ايندڙ اشارو رجسٽر
                                                          AT91C_SPI0_RPR EQU( 0xFFFE0100 );
                                                          -( PDC_SPI0 ) Receive اشارو رجسٽر
                                                          AT91C_SPI0_TNCR EQU( 0xFFFE011C );
                                                          -( PDC_SPI0 ) Transmit ايندڙ Counter رجسٽر
                                                          AT91C_SPI0_RNCR EQU( 0xFFFE0114 );
                                                          -( PDC_SPI0 ) Receive ايندڙ Counter رجسٽر
                                                          AT91C_SPI0_TNPR EQU( 0xFFFE0118 );
                                                          -( PDC_SPI0 ) Transmit ايندڙ اشارو رجسٽر
/* - ========== Register definition for SPI0 peripheral ========== */
                                                          AT91C_SPI0_IER EQU( 0xFFFE0014 );
                                                          -( SPI0 ) مداخلت_2 Enable رجسٽر
                                                          AT91C_SPI0_SR EQU( 0xFFFE0010 );
                                                          -( SPI0 ) حالت رجسٽر
                                                          AT91C_SPI0_IDR EQU( 0xFFFE0018 );
                                                          -( SPI0 ) مداخلت_2 Disable رجسٽر
                                                          AT91C_SPI0_CR EQU( 0xFFFE0000 );
                                                          -( SPI0 ) Control رجسٽر
                                                          AT91C_SPI0_MR EQU( 0xFFFE0004 );
                                                          -( SPI0 ) گهڻائي رجسٽر
                                                          AT91C_SPI0_IMR EQU( 0xFFFE001C );
                                                          -( SPI0 ) مداخلت_2 نقاب_2 رجسٽر
                                                          AT91C_SPI0_TDR EQU( 0xFFFE000C );
                                                          -( SPI0 ) Transmit معلومات رجسٽر
                                                          AT91C_SPI0_RDR EQU( 0xFFFE0008 );
                                                          -( SPI0 ) Receive معلومات رجسٽر
                                                          AT91C_SPI0_CSR EQU( 0xFFFE0030 );
                                                          -( SPI0 ) Chip Select رجسٽر
/* - ========== Register definition for PDC_US1 peripheral ========== */
                                                          AT91C_US1_RNCR EQU( 0xFFFC4114 );
                                                          -( PDC_US1 ) Receive ايندڙ Counter رجسٽر
                                                          AT91C_US1_PTCR EQU( 0xFFFC4120 );
                                                          -( PDC_US1 ) PDC Transfer Control رجسٽر
                                                          AT91C_US1_TCR EQU( 0xFFFC410C );
                                                          -( PDC_US1 ) Transmit Counter رجسٽر
                                                          AT91C_US1_PTSR EQU( 0xFFFC4124 );
                                                          -( PDC_US1 ) PDC Transfer حالت رجسٽر
                                                          AT91C_US1_TNPR EQU( 0xFFFC4118 );
                                                          -( PDC_US1 ) Transmit ايندڙ اشارو رجسٽر
                                                          AT91C_US1_RCR EQU( 0xFFFC4104 );
                                                          -( PDC_US1 ) Receive Counter رجسٽر
                                                          AT91C_US1_RNPR EQU( 0xFFFC4110 );
                                                          -( PDC_US1 ) Receive ايندڙ اشارو رجسٽر
                                                          AT91C_US1_RPR EQU( 0xFFFC4100 );
                                                          -( PDC_US1 ) Receive اشارو رجسٽر
                                                          AT91C_US1_TNCR EQU( 0xFFFC411C );
                                                          -( PDC_US1 ) Transmit ايندڙ Counter رجسٽر
                                                          AT91C_US1_TPR EQU( 0xFFFC4108 );
                                                          -( PDC_US1 ) Transmit اشارو رجسٽر
/* - ========== Register definition for US1 peripheral ========== */
                                                          AT91C_US1_IF EQU( 0xFFFC404C );
                                                          -( US1 ) IRDA_FILTER رجسٽر
                                                          AT91C_US1_NER EQU( 0xFFFC4044 );
                                                          -( US1 ) Nb Errors رجسٽر
                                                          AT91C_US1_RTOR EQU( 0xFFFC4024 );
                                                          -( US1 ) Receiver وقت - ٻاهريون رجسٽر
                                                          AT91C_US1_CSR EQU( 0xFFFC4014 );
                                                          -( US1 ) Channel حالت رجسٽر
                                                          AT91C_US1_IDR EQU( 0xFFFC400C );
                                                          -( US1 ) مداخلت_2 Disable رجسٽر
                                                          AT91C_US1_IER EQU( 0xFFFC4008 );
                                                          -( US1 ) مداخلت_2 Enable رجسٽر
                                                          AT91C_US1_THR EQU( 0xFFFC401C );
                                                          -( US1 ) Transmitter Holding رجسٽر
                                                          AT91C_US1_TTGR EQU( 0xFFFC4028 );
                                                          -( US1 ) Transmitter وقت - guard رجسٽر
                                                          AT91C_US1_RHR EQU( 0xFFFC4018 );
                                                          -( US1 ) Receiver Holding رجسٽر
                                                          AT91C_US1_BRGR EQU( 0xFFFC4020 );
                                                          -( US1 ) Baud شرح Generator رجسٽر
                                                          AT91C_US1_IMR EQU( 0xFFFC4010 );
                                                          -( US1 ) مداخلت_2 نقاب_2 رجسٽر
                                                          AT91C_US1_FIDI EQU( 0xFFFC4040 );
                                                          -( US1 ) FI_DI_تناسب رجسٽر
                                                          AT91C_US1_CR EQU( 0xFFFC4000 );
                                                          -( US1 ) Control رجسٽر
                                                          AT91C_US1_MR EQU( 0xFFFC4004 );
                                                          -( US1 ) گهڻائي رجسٽر
/* - ========== Register definition for PDC_US0 peripheral ========== */
                                                          AT91C_US0_TNPR EQU( 0xFFFC0118 );
                                                          -( PDC_US0 ) Transmit ايندڙ اشارو رجسٽر
                                                          AT91C_US0_RNPR EQU( 0xFFFC0110 );
                                                          -( PDC_US0 ) Receive ايندڙ اشارو رجسٽر
                                                          AT91C_US0_TCR EQU( 0xFFFC010C );
                                                          -( PDC_US0 ) Transmit Counter رجسٽر
                                                          AT91C_US0_PTCR EQU( 0xFFFC0120 );
                                                          -( PDC_US0 ) PDC Transfer Control رجسٽر
                                                          AT91C_US0_PTSR EQU( 0xFFFC0124 );
                                                          -( PDC_US0 ) PDC Transfer حالت رجسٽر
                                                          AT91C_US0_TNCR EQU( 0xFFFC011C );
                                                          -( PDC_US0 ) Transmit ايندڙ Counter رجسٽر
                                                          AT91C_US0_TPR EQU( 0xFFFC0108 );
                                                          -( PDC_US0 ) Transmit اشارو رجسٽر
                                                          AT91C_US0_RCR EQU( 0xFFFC0104 );
                                                          -( PDC_US0 ) Receive Counter رجسٽر
                                                          AT91C_US0_RPR EQU( 0xFFFC0100 );
                                                          -( PDC_US0 ) Receive اشارو رجسٽر
                                                          AT91C_US0_RNCR EQU( 0xFFFC0114 );
                                                          -( PDC_US0 ) Receive ايندڙ Counter رجسٽر
/* - ========== Register definition for US0 peripheral ========== */
                                                          AT91C_US0_BRGR EQU( 0xFFFC0020 );
                                                          -( US0 ) Baud شرح Generator رجسٽر
                                                          AT91C_US0_NER EQU( 0xFFFC0044 );
                                                          -( US0 ) Nb Errors رجسٽر
                                                          AT91C_US0_CR EQU( 0xFFFC0000 );
                                                          -( US0 ) Control رجسٽر
                                                          AT91C_US0_IMR EQU( 0xFFFC0010 );
                                                          -( US0 ) مداخلت_2 نقاب_2 رجسٽر
                                                          AT91C_US0_FIDI EQU( 0xFFFC0040 );
                                                          -( US0 ) FI_DI_تناسب رجسٽر
                                                          AT91C_US0_TTGR EQU( 0xFFFC0028 );
                                                          -( US0 ) Transmitter وقت - guard رجسٽر
                                                          AT91C_US0_MR EQU( 0xFFFC0004 );
                                                          -( US0 ) گهڻائي رجسٽر
                                                          AT91C_US0_RTOR EQU( 0xFFFC0024 );
                                                          -( US0 ) Receiver وقت - ٻاهريون رجسٽر
                                                          AT91C_US0_CSR EQU( 0xFFFC0014 );
                                                          -( US0 ) Channel حالت رجسٽر
                                                          AT91C_US0_RHR EQU( 0xFFFC0018 );
                                                          -( US0 ) Receiver Holding رجسٽر
                                                          AT91C_US0_IDR EQU( 0xFFFC000C );
                                                          -( US0 ) مداخلت_2 Disable رجسٽر
                                                          AT91C_US0_THR EQU( 0xFFFC001C );
                                                          -( US0 ) Transmitter Holding رجسٽر
                                                          AT91C_US0_IF EQU( 0xFFFC004C );
                                                          -( US0 ) IRDA_FILTER رجسٽر
                                                          AT91C_US0_IER EQU( 0xFFFC0008 );
                                                          -( US0 ) مداخلت_2 Enable رجسٽر
/* - ========== Register definition for PDC_SSC peripheral ========== */
                                                          AT91C_SSC_TNCR EQU( 0xFFFD411C );
                                                          -( PDC_SSC ) Transmit ايندڙ Counter رجسٽر
                                                          AT91C_SSC_RPR EQU( 0xFFFD4100 );
                                                          -( PDC_SSC ) Receive اشارو رجسٽر
                                                          AT91C_SSC_RNCR EQU( 0xFFFD4114 );
                                                          -( PDC_SSC ) Receive ايندڙ Counter رجسٽر
                                                          AT91C_SSC_TPR EQU( 0xFFFD4108 );
                                                          -( PDC_SSC ) Transmit اشارو رجسٽر
                                                          AT91C_SSC_PTCR EQU( 0xFFFD4120 );
                                                          -( PDC_SSC ) PDC Transfer Control رجسٽر
                                                          AT91C_SSC_TCR EQU( 0xFFFD410C );
                                                          -( PDC_SSC ) Transmit Counter رجسٽر
                                                          AT91C_SSC_RCR EQU( 0xFFFD4104 );
                                                          -( PDC_SSC ) Receive Counter رجسٽر
                                                          AT91C_SSC_RNPR EQU( 0xFFFD4110 );
                                                          -( PDC_SSC ) Receive ايندڙ اشارو رجسٽر
                                                          AT91C_SSC_TNPR EQU( 0xFFFD4118 );
                                                          -( PDC_SSC ) Transmit ايندڙ اشارو رجسٽر
                                                          AT91C_SSC_PTSR EQU( 0xFFFD4124 );
                                                          -( PDC_SSC ) PDC Transfer حالت رجسٽر
/* - ========== Register definition for SSC peripheral ========== */
                                                          AT91C_SSC_RHR EQU( 0xFFFD4020 );
                                                          -( SSC ) Receive Holding رجسٽر
                                                          AT91C_SSC_RSHR EQU( 0xFFFD4030 );
                                                          -( SSC ) Receive Sync Holding رجسٽر
                                                          AT91C_SSC_TFMR EQU( 0xFFFD401C );
                                                          -( SSC ) Transmit چوکٺو گهڻائي رجسٽر
                                                          AT91C_SSC_IDR EQU( 0xFFFD4048 );
                                                          -( SSC ) مداخلت_2 Disable رجسٽر
                                                          AT91C_SSC_THR EQU( 0xFFFD4024 );
                                                          -( SSC ) Transmit Holding رجسٽر
                                                          AT91C_SSC_RCMR EQU( 0xFFFD4010 );
                                                          -( SSC ) Receive Clock گهڻائي_رجسٽر
                                                          AT91C_SSC_IER EQU( 0xFFFD4044 );
                                                          -( SSC ) مداخلت_2 Enable رجسٽر
                                                          AT91C_SSC_TSHR EQU( 0xFFFD4034 );
                                                          -( SSC ) Transmit Sync Holding رجسٽر
                                                          AT91C_SSC_SR EQU( 0xFFFD4040 );
                                                          -( SSC ) حالت رجسٽر
                                                          AT91C_SSC_CMR EQU( 0xFFFD4004 );
                                                          -( SSC ) Clock گهڻائي رجسٽر
                                                          AT91C_SSC_TCMR EQU( 0xFFFD4018 );
                                                          -( SSC ) Transmit Clock گهڻائي رجسٽر
                                                          AT91C_SSC_CR EQU( 0xFFFD4000 );
                                                          -( SSC ) Control رجسٽر
                                                          AT91C_SSC_IMR EQU( 0xFFFD404C );
                                                          -( SSC ) مداخلت_2 نقاب_2 رجسٽر
                                                          AT91C_SSC_RFMR EQU( 0xFFFD4014 );
                                                          -( SSC ) Receive چوکٺو گهڻائي رجسٽر
/* - ========== Register definition for TWI peripheral ========== */
                                                          AT91C_TWI_IER EQU( 0xFFFB8024 );
                                                          -( TWI ) مداخلت_2 Enable رجسٽر
                                                          AT91C_TWI_CR EQU( 0xFFFB8000 );
                                                          -( TWI ) Control رجسٽر
                                                          AT91C_TWI_SR EQU( 0xFFFB8020 );
                                                          -( TWI ) حالت رجسٽر
                                                          AT91C_TWI_IMR EQU( 0xFFFB802C );
                                                          -( TWI ) مداخلت_2 نقاب_2 رجسٽر
                                                          AT91C_TWI_THR EQU( 0xFFFB8034 );
                                                          -( TWI ) Transmit Holding رجسٽر
                                                          AT91C_TWI_IDR EQU( 0xFFFB8028 );
                                                          -( TWI ) مداخلت_2 Disable رجسٽر
                                                          AT91C_TWI_IADR EQU( 0xFFFB800C );
                                                          -( TWI ) اندروني پتو رجسٽر
                                                          AT91C_TWI_MMR EQU( 0xFFFB8004 );
                                                          -( TWI ) Master گهڻائي رجسٽر
                                                          AT91C_TWI_CWGR EQU( 0xFFFB8010 );
                                                          -( TWI ) Clock Waveform Generator رجسٽر
                                                          AT91C_TWI_RHR EQU( 0xFFFB8030 );
                                                          -( TWI ) Receive Holding رجسٽر
/* - ========== Register definition for PWMC_CH3 peripheral ========== */
                                                          AT91C_PWMC_CH3_CUPDR EQU( 0xFFFCC270 );
                                                          -( PWMC_CH3 ) Channel Update رجسٽر
                                                          AT91C_PWMC_CH3_Reserved EQU( 0xFFFCC274 );
                                                          -( PWMC_CH3 ) Reserved
                                                          AT91C_PWMC_CH3_CPRDR EQU( 0xFFFCC268 );
                                                          -( PWMC_CH3 ) Channel Period رجسٽر
                                                          AT91C_PWMC_CH3_CDTYR EQU( 0xFFFCC264 );
                                                          -( PWMC_CH3 ) Channel Duty چڪر_2 رجسٽر
                                                          AT91C_PWMC_CH3_CCNTR EQU( 0xFFFCC26C );
                                                          -( PWMC_CH3 ) Channel Counter رجسٽر
                                                          AT91C_PWMC_CH3_CMR EQU( 0xFFFCC260 );
                                                          -( PWMC_CH3 ) Channel گهڻائي رجسٽر
/* - ========== Register definition for PWMC_CH2 peripheral ========== */
                                                          AT91C_PWMC_CH2_Reserved EQU( 0xFFFCC254 );
                                                          -( PWMC_CH2 ) Reserved
                                                          AT91C_PWMC_CH2_CMR EQU( 0xFFFCC240 );
                                                          -( PWMC_CH2 ) Channel گهڻائي رجسٽر
                                                          AT91C_PWMC_CH2_CCNTR EQU( 0xFFFCC24C );
                                                          -( PWMC_CH2 ) Channel Counter رجسٽر
                                                          AT91C_PWMC_CH2_CPRDR EQU( 0xFFFCC248 );
                                                          -( PWMC_CH2 ) Channel Period رجسٽر
                                                          AT91C_PWMC_CH2_CUPDR EQU( 0xFFFCC250 );
                                                          -( PWMC_CH2 ) Channel Update رجسٽر
                                                          AT91C_PWMC_CH2_CDTYR EQU( 0xFFFCC244 );
                                                          -( PWMC_CH2 ) Channel Duty چڪر_2 رجسٽر
/* - ========== Register definition for PWMC_CH1 peripheral ========== */
                                                          AT91C_PWMC_CH1_Reserved EQU( 0xFFFCC234 );
                                                          -( PWMC_CH1 ) Reserved
                                                          AT91C_PWMC_CH1_CUPDR EQU( 0xFFFCC230 );
                                                          -( PWMC_CH1 ) Channel Update رجسٽر
                                                          AT91C_PWMC_CH1_CPRDR EQU( 0xFFFCC228 );
                                                          -( PWMC_CH1 ) Channel Period رجسٽر
                                                          AT91C_PWMC_CH1_CCNTR EQU( 0xFFFCC22C );
                                                          -( PWMC_CH1 ) Channel Counter رجسٽر
                                                          AT91C_PWMC_CH1_CDTYR EQU( 0xFFFCC224 );
                                                          -( PWMC_CH1 ) Channel Duty چڪر_2 رجسٽر
                                                          AT91C_PWMC_CH1_CMR EQU( 0xFFFCC220 );
                                                          -( PWMC_CH1 ) Channel گهڻائي رجسٽر
/* - ========== Register definition for PWMC_CH0 peripheral ========== */
                                                          AT91C_PWMC_CH0_Reserved EQU( 0xFFFCC214 );
                                                          -( PWMC_CH0 ) Reserved
                                                          AT91C_PWMC_CH0_CPRDR EQU( 0xFFFCC208 );
                                                          -( PWMC_CH0 ) Channel Period رجسٽر
                                                          AT91C_PWMC_CH0_CDTYR EQU( 0xFFFCC204 );
                                                          -( PWMC_CH0 ) Channel Duty چڪر_2 رجسٽر
                                                          AT91C_PWMC_CH0_CMR EQU( 0xFFFCC200 );
                                                          -( PWMC_CH0 ) Channel گهڻائي رجسٽر
                                                          AT91C_PWMC_CH0_CUPDR EQU( 0xFFFCC210 );
                                                          -( PWMC_CH0 ) Channel Update رجسٽر
                                                          AT91C_PWMC_CH0_CCNTR EQU( 0xFFFCC20C );
                                                          -( PWMC_CH0 ) Channel Counter رجسٽر
/* - ========== Register definition for PWMC peripheral ========== */
                                                          AT91C_PWMC_IDR EQU( 0xFFFCC014 );
                                                          -( PWMC ) PWMC مداخلت_2 Disable رجسٽر
                                                          AT91C_PWMC_DIS EQU( 0xFFFCC008 );
                                                          -( PWMC ) PWMC Disable رجسٽر
                                                          AT91C_PWMC_IER EQU( 0xFFFCC010 );
                                                          -( PWMC ) PWMC مداخلت_2 Enable رجسٽر
                                                          AT91C_PWMC_VR EQU( 0xFFFCC0FC );
                                                          -( PWMC ) PWMC نسخو_2 رجسٽر
                                                          AT91C_PWMC_ISR EQU( 0xFFFCC01C );
                                                          -( PWMC ) PWMC مداخلت_2 حالت رجسٽر
                                                          AT91C_PWMC_SR EQU( 0xFFFCC00C );
                                                          -( PWMC ) PWMC حالت رجسٽر
                                                          AT91C_PWMC_IMR EQU( 0xFFFCC018 );
                                                          -( PWMC ) PWMC مداخلت_2 نقاب_2 رجسٽر
                                                          AT91C_PWMC_MR EQU( 0xFFFCC000 );
                                                          -( PWMC ) PWMC گهڻائي رجسٽر
                                                          AT91C_PWMC_ENA EQU( 0xFFFCC004 );
                                                          -( PWMC ) PWMC Enable رجسٽر
/* - ========== Register definition for UDP peripheral ========== */
                                                          AT91C_UDP_IMR EQU( 0xFFFB0018 );
                                                          -( UDP ) مداخلت_2 نقاب_2 رجسٽر
                                                          AT91C_UDP_FADDR EQU( 0xFFFB0008 );
                                                          -( UDP ) Function پتو رجسٽر
                                                          AT91_C_UDP_انگ EQU( 0xFFFB0000 );
                                                          -( UDP ) چوکٺو عدد_2 رجسٽر
                                                          AT91C_UDP_FDR EQU( 0xFFFB0050 );
                                                          -( UDP ) Endpoint FIFO معلومات رجسٽر
                                                          AT91C_UDP_ISR EQU( 0xFFFB001C );
                                                          -( UDP ) مداخلت_2 حالت رجسٽر
                                                          AT91C_UDP_CSR EQU( 0xFFFB0030 );
                                                          -( UDP ) Endpoint Control and حالت رجسٽر
                                                          AT91C_UDP_IDR EQU( 0xFFFB0014 );
                                                          -( UDP ) مداخلت_2 Disable رجسٽر
                                                          AT91C_UDP_ICR EQU( 0xFFFB0020 );
                                                          -( UDP ) مداخلت_2 Clear رجسٽر
                                                          AT91C_UDP_RSTEP EQU( 0xFFFB0028 );
                                                          -( UDP ) Reset Endpoint رجسٽر
                                                          AT91C_UDP_TXVC EQU( 0xFFFB0074 );
                                                          -( UDP ) Transceiver Control رجسٽر
                                                          AT91C_UDP_GLBSTATE EQU( 0xFFFB0004 );
                                                          -( UDP ) Global State رجسٽر
                                                          AT91C_UDP_IER EQU( 0xFFFB0010 );
                                                          -( UDP ) مداخلت_2 Enable رجسٽر
/* - ========== Register definition for TC0 peripheral ========== */
                                                          AT91C_TC0_SR EQU( 0xFFFA0020 );
                                                          -( TC0 ) حالت رجسٽر
                                                          AT91C_TC0_RC EQU( 0xFFFA001C );
                                                          -( TC0 ) رجسٽر C
                                                          AT91C_TC0_RB EQU( 0xFFFA0018 );
                                                          -( TC0 ) رجسٽر B
                                                          AT91C_TC0_CCR EQU( 0xFFFA0000 );
                                                          -( TC0 ) Channel Control رجسٽر
                                                          AT91C_TC0_CMR EQU( 0xFFFA0004 );
                                                          -( TC0 ) Channel گهڻائي رجسٽر( Capture گهڻائي / Waveform گهڻائي )
                                                          AT91C_TC0_IER EQU( 0xFFFA0024 );
                                                          -( TC0 ) مداخلت_2 Enable رجسٽر
                                                          AT91C_TC0_RA EQU( 0xFFFA0014 );
                                                          -( TC0 ) رجسٽر A
                                                          AT91C_TC0_IDR EQU( 0xFFFA0028 );
                                                          -( TC0 ) مداخلت_2 Disable رجسٽر
                                                          AT91C_TC0_CV EQU( 0xFFFA0010 );
                                                          -( TC0 ) Counter قدر_2
                                                          AT91C_TC0_IMR EQU( 0xFFFA002C );
                                                          -( TC0 ) مداخلت_2 نقاب_2 رجسٽر
/* - ========== Register definition for TC1 peripheral ========== */
                                                          AT91C_TC1_RB EQU( 0xFFFA0058 );
                                                          -( TC1 ) رجسٽر B
                                                          AT91C_TC1_CCR EQU( 0xFFFA0040 );
                                                          -( TC1 ) Channel Control رجسٽر
                                                          AT91C_TC1_IER EQU( 0xFFFA0064 );
                                                          -( TC1 ) مداخلت_2 Enable رجسٽر
                                                          AT91C_TC1_IDR EQU( 0xFFFA0068 );
                                                          -( TC1 ) مداخلت_2 Disable رجسٽر
                                                          AT91C_TC1_SR EQU( 0xFFFA0060 );
                                                          -( TC1 ) حالت رجسٽر
                                                          AT91C_TC1_CMR EQU( 0xFFFA0044 );
                                                          -( TC1 ) Channel گهڻائي رجسٽر( Capture گهڻائي / Waveform گهڻائي )
                                                          AT91C_TC1_RA EQU( 0xFFFA0054 );
                                                          -( TC1 ) رجسٽر A
                                                          AT91C_TC1_RC EQU( 0xFFFA005C );
                                                          -( TC1 ) رجسٽر C
                                                          AT91C_TC1_IMR EQU( 0xFFFA006C );
                                                          -( TC1 ) مداخلت_2 نقاب_2 رجسٽر
                                                          AT91C_TC1_CV EQU( 0xFFFA0050 );
                                                          -( TC1 ) Counter قدر_2
/* - ========== Register definition for TC2 peripheral ========== */
                                                          AT91C_TC2_CMR EQU( 0xFFFA0084 );
                                                          -( TC2 ) Channel گهڻائي رجسٽر( Capture گهڻائي / Waveform گهڻائي )
                                                          AT91C_TC2_CCR EQU( 0xFFFA0080 );
                                                          -( TC2 ) Channel Control رجسٽر
                                                          AT91C_TC2_CV EQU( 0xFFFA0090 );
                                                          -( TC2 ) Counter قدر_2
                                                          AT91C_TC2_RA EQU( 0xFFFA0094 );
                                                          -( TC2 ) رجسٽر A
                                                          AT91C_TC2_RB EQU( 0xFFFA0098 );
                                                          -( TC2 ) رجسٽر B
                                                          AT91C_TC2_IDR EQU( 0xFFFA00A8 );
                                                          -( TC2 ) مداخلت_2 Disable رجسٽر
                                                          AT91C_TC2_IMR EQU( 0xFFFA00AC );
                                                          -( TC2 ) مداخلت_2 نقاب_2 رجسٽر
                                                          AT91C_TC2_RC EQU( 0xFFFA009C );
                                                          -( TC2 ) رجسٽر C
                                                          AT91C_TC2_IER EQU( 0xFFFA00A4 );
                                                          -( TC2 ) مداخلت_2 Enable رجسٽر
                                                          AT91C_TC2_SR EQU( 0xFFFA00A0 );
                                                          -( TC2 ) حالت رجسٽر
/* - ========== Register definition for TCB peripheral ========== */
                                                          AT91C_TCB_BMR EQU( 0xFFFA00C4 );
                                                          -( TCB ) TC بلاڪ گهڻائي رجسٽر
                                                          AT91C_TCB_BCR EQU( 0xFFFA00C0 );
                                                          -( TCB ) TC بلاڪ Control رجسٽر
/* - ========== Register definition for CAN_MB0 peripheral ========== */
                                                          AT91C_CAN_MB0_MDL EQU( 0xFFFD0214 );
                                                          -( CAN_MB0 ) MailBox معلومات هيٺيون رجسٽر
                                                          AT91C_CAN_MB0_MAM EQU( 0xFFFD0204 );
                                                          -( CAN_MB0 ) MailBox Acceptance نقاب_2 رجسٽر
                                                          AT91C_CAN_MB0_MCR EQU( 0xFFFD021C );
                                                          -( CAN_MB0 ) MailBox Control رجسٽر
                                                          AT91C_CAN_MB0_MID EQU( 0xFFFD0208 );
                                                          -( CAN_MB0 ) MailBox ID رجسٽر
                                                          AT91C_CAN_MB0_MSR EQU( 0xFFFD0210 );
                                                          -( CAN_MB0 ) MailBox حالت رجسٽر
                                                          AT91C_CAN_MB0_MFID EQU( 0xFFFD020C );
                                                          -( CAN_MB0 ) MailBox Family ID رجسٽر
                                                          AT91C_CAN_MB0_MDH EQU( 0xFFFD0218 );
                                                          -( CAN_MB0 ) MailBox معلومات مٿاهون رجسٽر
                                                          AT91C_CAN_MB0_MMR EQU( 0xFFFD0200 );
                                                          -( CAN_MB0 ) MailBox گهڻائي رجسٽر
/* - ========== Register definition for CAN_MB1 peripheral ========== */
                                                          AT91C_CAN_MB1_MDL EQU( 0xFFFD0234 );
                                                          -( CAN_MB1 ) MailBox معلومات هيٺيون رجسٽر
                                                          AT91C_CAN_MB1_MID EQU( 0xFFFD0228 );
                                                          -( CAN_MB1 ) MailBox ID رجسٽر
                                                          AT91C_CAN_MB1_MMR EQU( 0xFFFD0220 );
                                                          -( CAN_MB1 ) MailBox گهڻائي رجسٽر
                                                          AT91C_CAN_MB1_MSR EQU( 0xFFFD0230 );
                                                          -( CAN_MB1 ) MailBox حالت رجسٽر
                                                          AT91C_CAN_MB1_MAM EQU( 0xFFFD0224 );
                                                          -( CAN_MB1 ) MailBox Acceptance نقاب_2 رجسٽر
                                                          AT91C_CAN_MB1_MDH EQU( 0xFFFD0238 );
                                                          -( CAN_MB1 ) MailBox معلومات مٿاهون رجسٽر
                                                          AT91C_CAN_MB1_MCR EQU( 0xFFFD023C );
                                                          -( CAN_MB1 ) MailBox Control رجسٽر
                                                          AT91C_CAN_MB1_MFID EQU( 0xFFFD022C );
                                                          -( CAN_MB1 ) MailBox Family ID رجسٽر
/* - ========== Register definition for CAN_MB2 peripheral ========== */
                                                          AT91C_CAN_MB2_MCR EQU( 0xFFFD025C );
                                                          -( CAN_MB2 ) MailBox Control رجسٽر
                                                          AT91C_CAN_MB2_MDH EQU( 0xFFFD0258 );
                                                          -( CAN_MB2 ) MailBox معلومات مٿاهون رجسٽر
                                                          AT91C_CAN_MB2_MID EQU( 0xFFFD0248 );
                                                          -( CAN_MB2 ) MailBox ID رجسٽر
                                                          AT91C_CAN_MB2_MDL EQU( 0xFFFD0254 );
                                                          -( CAN_MB2 ) MailBox معلومات هيٺيون رجسٽر
                                                          AT91C_CAN_MB2_MMR EQU( 0xFFFD0240 );
                                                          -( CAN_MB2 ) MailBox گهڻائي رجسٽر
                                                          AT91C_CAN_MB2_MAM EQU( 0xFFFD0244 );
                                                          -( CAN_MB2 ) MailBox Acceptance نقاب_2 رجسٽر
                                                          AT91C_CAN_MB2_MFID EQU( 0xFFFD024C );
                                                          -( CAN_MB2 ) MailBox Family ID رجسٽر
                                                          AT91C_CAN_MB2_MSR EQU( 0xFFFD0250 );
                                                          -( CAN_MB2 ) MailBox حالت رجسٽر
/* - ========== Register definition for CAN_MB3 peripheral ========== */
                                                          AT91C_CAN_MB3_MFID EQU( 0xFFFD026C );
                                                          -( CAN_MB3 ) MailBox Family ID رجسٽر
                                                          AT91C_CAN_MB3_MAM EQU( 0xFFFD0264 );
                                                          -( CAN_MB3 ) MailBox Acceptance نقاب_2 رجسٽر
                                                          AT91C_CAN_MB3_MID EQU( 0xFFFD0268 );
                                                          -( CAN_MB3 ) MailBox ID رجسٽر
                                                          AT91C_CAN_MB3_MCR EQU( 0xFFFD027C );
                                                          -( CAN_MB3 ) MailBox Control رجسٽر
                                                          AT91C_CAN_MB3_MMR EQU( 0xFFFD0260 );
                                                          -( CAN_MB3 ) MailBox گهڻائي رجسٽر
                                                          AT91C_CAN_MB3_MSR EQU( 0xFFFD0270 );
                                                          -( CAN_MB3 ) MailBox حالت رجسٽر
                                                          AT91C_CAN_MB3_MDL EQU( 0xFFFD0274 );
                                                          -( CAN_MB3 ) MailBox معلومات هيٺيون رجسٽر
                                                          AT91C_CAN_MB3_MDH EQU( 0xFFFD0278 );
                                                          -( CAN_MB3 ) MailBox معلومات مٿاهون رجسٽر
/* - ========== Register definition for CAN_MB4 peripheral ========== */
                                                          AT91C_CAN_MB4_MID EQU( 0xFFFD0288 );
                                                          -( CAN_MB4 ) MailBox ID رجسٽر
                                                          AT91C_CAN_MB4_MMR EQU( 0xFFFD0280 );
                                                          -( CAN_MB4 ) MailBox گهڻائي رجسٽر
                                                          AT91C_CAN_MB4_MDH EQU( 0xFFFD0298 );
                                                          -( CAN_MB4 ) MailBox معلومات مٿاهون رجسٽر
                                                          AT91C_CAN_MB4_MFID EQU( 0xFFFD028C );
                                                          -( CAN_MB4 ) MailBox Family ID رجسٽر
                                                          AT91C_CAN_MB4_MSR EQU( 0xFFFD0290 );
                                                          -( CAN_MB4 ) MailBox حالت رجسٽر
                                                          AT91C_CAN_MB4_MCR EQU( 0xFFFD029C );
                                                          -( CAN_MB4 ) MailBox Control رجسٽر
                                                          AT91C_CAN_MB4_MDL EQU( 0xFFFD0294 );
                                                          -( CAN_MB4 ) MailBox معلومات هيٺيون رجسٽر
                                                          AT91C_CAN_MB4_MAM EQU( 0xFFFD0284 );
                                                          -( CAN_MB4 ) MailBox Acceptance نقاب_2 رجسٽر
/* - ========== Register definition for CAN_MB5 peripheral ========== */
                                                          AT91C_CAN_MB5_MSR EQU( 0xFFFD02B0 );
                                                          -( CAN_MB5 ) MailBox حالت رجسٽر
                                                          AT91C_CAN_MB5_MCR EQU( 0xFFFD02BC );
                                                          -( CAN_MB5 ) MailBox Control رجسٽر
                                                          AT91C_CAN_MB5_MFID EQU( 0xFFFD02AC );
                                                          -( CAN_MB5 ) MailBox Family ID رجسٽر
                                                          AT91C_CAN_MB5_MDH EQU( 0xFFFD02B8 );
                                                          -( CAN_MB5 ) MailBox معلومات مٿاهون رجسٽر
                                                          AT91C_CAN_MB5_MID EQU( 0xFFFD02A8 );
                                                          -( CAN_MB5 ) MailBox ID رجسٽر
                                                          AT91C_CAN_MB5_MMR EQU( 0xFFFD02A0 );
                                                          -( CAN_MB5 ) MailBox گهڻائي رجسٽر
                                                          AT91C_CAN_MB5_MDL EQU( 0xFFFD02B4 );
                                                          -( CAN_MB5 ) MailBox معلومات هيٺيون رجسٽر
                                                          AT91C_CAN_MB5_MAM EQU( 0xFFFD02A4 );
                                                          -( CAN_MB5 ) MailBox Acceptance نقاب_2 رجسٽر
/* - ========== Register definition for CAN_MB6 peripheral ========== */
                                                          AT91C_CAN_MB6_MFID EQU( 0xFFFD02CC );
                                                          -( CAN_MB6 ) MailBox Family ID رجسٽر
                                                          AT91C_CAN_MB6_MID EQU( 0xFFFD02C8 );
                                                          -( CAN_MB6 ) MailBox ID رجسٽر
                                                          AT91C_CAN_MB6_MAM EQU( 0xFFFD02C4 );
                                                          -( CAN_MB6 ) MailBox Acceptance نقاب_2 رجسٽر
                                                          AT91C_CAN_MB6_MSR EQU( 0xFFFD02D0 );
                                                          -( CAN_MB6 ) MailBox حالت رجسٽر
                                                          AT91C_CAN_MB6_MDL EQU( 0xFFFD02D4 );
                                                          -( CAN_MB6 ) MailBox معلومات هيٺيون رجسٽر
                                                          AT91C_CAN_MB6_MCR EQU( 0xFFFD02DC );
                                                          -( CAN_MB6 ) MailBox Control رجسٽر
                                                          AT91C_CAN_MB6_MDH EQU( 0xFFFD02D8 );
                                                          -( CAN_MB6 ) MailBox معلومات مٿاهون رجسٽر
                                                          AT91C_CAN_MB6_MMR EQU( 0xFFFD02C0 );
                                                          -( CAN_MB6 ) MailBox گهڻائي رجسٽر
/* - ========== Register definition for CAN_MB7 peripheral ========== */
                                                          AT91C_CAN_MB7_MCR EQU( 0xFFFD02FC );
                                                          -( CAN_MB7 ) MailBox Control رجسٽر
                                                          AT91C_CAN_MB7_MDH EQU( 0xFFFD02F8 );
                                                          -( CAN_MB7 ) MailBox معلومات مٿاهون رجسٽر
                                                          AT91C_CAN_MB7_MFID EQU( 0xFFFD02EC );
                                                          -( CAN_MB7 ) MailBox Family ID رجسٽر
                                                          AT91C_CAN_MB7_MDL EQU( 0xFFFD02F4 );
                                                          -( CAN_MB7 ) MailBox معلومات هيٺيون رجسٽر
                                                          AT91C_CAN_MB7_MID EQU( 0xFFFD02E8 );
                                                          -( CAN_MB7 ) MailBox ID رجسٽر
                                                          AT91C_CAN_MB7_MMR EQU( 0xFFFD02E0 );
                                                          -( CAN_MB7 ) MailBox گهڻائي رجسٽر
                                                          AT91C_CAN_MB7_MAM EQU( 0xFFFD02E4 );
                                                          -( CAN_MB7 ) MailBox Acceptance نقاب_2 رجسٽر
                                                          AT91C_CAN_MB7_MSR EQU( 0xFFFD02F0 );
                                                          -( CAN_MB7 ) MailBox حالت رجسٽر
/* - ========== Register definition for CAN peripheral ========== */
                                                          AT91C_CAN_TCR EQU( 0xFFFD0024 );
                                                          -( CAN ) Transfer Command رجسٽر
                                                          AT91C_CAN_IMR EQU( 0xFFFD000C );
                                                          -( CAN ) مداخلت_2 نقاب_2 رجسٽر
                                                          AT91C_CAN_IER EQU( 0xFFFD0004 );
                                                          -( CAN ) مداخلت_2 Enable رجسٽر
                                                          AT91C_CAN_ECR EQU( 0xFFFD0020 );
                                                          -( CAN ) Error Counter رجسٽر
                                                          AT91C_CAN_TIMESTP EQU( 0xFFFD001C );
                                                          -( CAN ) وقت Stamp رجسٽر
                                                          AT91C_CAN_MR EQU( 0xFFFD0000 );
                                                          -( CAN ) گهڻائي رجسٽر
                                                          AT91C_CAN_IDR EQU( 0xFFFD0008 );
                                                          -( CAN ) مداخلت_2 Disable رجسٽر
                                                          AT91C_CAN_ACR EQU( 0xFFFD0028 );
                                                          -( CAN ) Abort Command رجسٽر
                                                          AT91C_CAN_TIM EQU( 0xFFFD0018 );
                                                          -( CAN ) Timer رجسٽر
                                                          AT91C_CAN_SR EQU( 0xFFFD0010 );
                                                          -( CAN ) حالت رجسٽر
                                                          AT91C_CAN_BR EQU( 0xFFFD0014 );
                                                          -( CAN ) Baudrate رجسٽر
                                                          AT91C_CAN_VR EQU( 0xFFFD00FC );
                                                          -( CAN ) نسخو_2 رجسٽر
/* - ========== Register definition for EMAC peripheral ========== */
                                                          AT91C_EMAC_ISR EQU( 0xFFFDC024 );
                                                          -( EMAC ) مداخلت_2 حالت رجسٽر
                                                          AT91C_EMAC_SA4H EQU( 0xFFFDC0B4 );
                                                          -( EMAC ) Specific پتو 4 چوٽي, آخري 2 بائيٽون_2
                                                          AT91C_EMAC_SA1L EQU( 0xFFFDC098 );
                                                          -( EMAC ) Specific پتو 1 Bottom, پهريون 4 بائيٽون_2
                                                          AT91C_EMAC_ELE EQU( 0xFFFDC078 );
                                                          -( EMAC ) Excessive ڊيگهائي Errors رجسٽر
                                                          AT91C_EMAC_LCOL EQU( 0xFFFDC05C );
                                                          -( EMAC ) Late Collision رجسٽر
                                                          AT91C_EMAC_RLE EQU( 0xFFFDC088 );
                                                          -( EMAC ) Receive ڊيگهائي ميدان_2 Mismatch رجسٽر
                                                          AT91C_EMAC_WOL EQU( 0xFFFDC0C4 );
                                                          -( EMAC ) Wake On LAN رجسٽر
                                                          AT91C_EMAC_DTF EQU( 0xFFFDC058 );
                                                          -( EMAC ) Deferred ترسيل چوکٺو رجسٽر
                                                          AT91C_EMAC_TUND EQU( 0xFFFDC064 );
                                                          -( EMAC ) Transmit Underrun Error رجسٽر
                                                          AT91C_EMAC_NCR EQU( 0xFFFDC000 );
                                                          -( EMAC ) ڄار Control رجسٽر
                                                          AT91C_EMAC_SA4L EQU( 0xFFFDC0B0 );
                                                          -( EMAC ) Specific پتو 4 Bottom, پهريون 4 بائيٽون_2
                                                          AT91C_EMAC_RSR EQU( 0xFFFDC020 );
                                                          -( EMAC ) Receive حالت رجسٽر
                                                          AT91C_EMAC_SA3L EQU( 0xFFFDC0A8 );
                                                          -( EMAC ) Specific پتو 3 Bottom, پهريون 4 بائيٽون_2
                                                          AT91C_EMAC_TSR EQU( 0xFFFDC014 );
                                                          -( EMAC ) Transmit حالت رجسٽر
                                                          AT91C_EMAC_IDR EQU( 0xFFFDC02C );
                                                          -( EMAC ) مداخلت_2 Disable رجسٽر
                                                          AT91C_EMAC_RSE EQU( 0xFFFDC074 );
                                                          -( EMAC ) Receive نشان Errors رجسٽر
                                                          AT91C_EMAC_ECOL EQU( 0xFFFDC060 );
                                                          -( EMAC ) Excessive Collision رجسٽر
                                                          AT91C_EMAC_TID EQU( 0xFFFDC0B8 );
                                                          -( EMAC ) Type ID Checking رجسٽر
                                                          AT91C_EMAC_HRB EQU( 0xFFFDC090 );
                                                          -( EMAC ) Hash پتو Bottom[ 31 : 0 ]
                                                          AT91C_EMAC_TBQP EQU( 0xFFFDC01C );
                                                          -( EMAC ) Transmit بفر قطار اشارو
                                                          AT91C_EMAC_USRIO EQU( 0xFFFDC0C0 );
                                                          -( EMAC ) USER داخلا / Output رجسٽر
                                                          AT91C_EMAC_PTR EQU( 0xFFFDC038 );
                                                          -( EMAC ) Pause وقت رجسٽر
                                                          AT91C_EMAC_SA2H EQU( 0xFFFDC0A4 );
                                                          -( EMAC ) Specific پتو 2 چوٽي, آخري 2 بائيٽون_2
                                                          AT91C_EMAC_ROV EQU( 0xFFFDC070 );
                                                          -( EMAC ) Receive Overrun Errors رجسٽر
                                                          AT91C_EMAC_ALE EQU( 0xFFFDC054 );
                                                          -( EMAC ) Alignment Error رجسٽر
                                                          AT91C_EMAC_RJA EQU( 0xFFFDC07C );
                                                          -( EMAC ) Receive Jabbers رجسٽر
                                                          AT91C_EMAC_RBQP EQU( 0xFFFDC018 );
                                                          -( EMAC ) Receive بفر قطار اشارو
                                                          AT91C_EMAC_TPF EQU( 0xFFFDC08C );
                                                          -( EMAC ) Transmitted Pause چوکٺا رجسٽر
                                                          AT91C_EMAC_NCFGR EQU( 0xFFFDC004 );
                                                          -( EMAC ) ڄار Configuration رجسٽر
                                                          AT91C_EMAC_HRT EQU( 0xFFFDC094 );
                                                          -( EMAC ) Hash پتو چوٽي[ 63 : 32 ]
                                                          AT91C_EMAC_USF EQU( 0xFFFDC080 );
                                                          -( EMAC ) Undersize چوکٺا رجسٽر
                                                          AT91C_EMAC_FCSE EQU( 0xFFFDC050 );
                                                          -( EMAC ) چوکٺو Check Sequence Error رجسٽر
                                                          AT91C_EMAC_TPQ EQU( 0xFFFDC0BC );
                                                          -( EMAC ) Transmit Pause وقتي_حصو_2 رجسٽر
                                                          AT91C_EMAC_MAN EQU( 0xFFFDC034 );
                                                          -( EMAC ) PHY Maintenance رجسٽر
                                                          AT91C_EMAC_FTO EQU( 0xFFFDC040 );
                                                          -( EMAC ) چوکٺا Transmitted OK رجسٽر
                                                          AT91C_EMAC_REV EQU( 0xFFFDC0FC );
                                                          -( EMAC ) Revision رجسٽر
                                                          AT91C_EMAC_IMR EQU( 0xFFFDC030 );
                                                          -( EMAC ) مداخلت_2 نقاب_2 رجسٽر
                                                          AT91C_EMAC_SCF EQU( 0xFFFDC044 );
                                                          -( EMAC ) Single Collision چوکٺو رجسٽر
                                                          AT91C_EMAC_PFR EQU( 0xFFFDC03C );
                                                          -( EMAC ) Pause چوکٺا received رجسٽر
                                                          AT91C_EMAC_MCF EQU( 0xFFFDC048 );
                                                          -( EMAC ) گڻو Collision چوکٺو رجسٽر
                                                          AT91C_EMAC_NSR EQU( 0xFFFDC008 );
                                                          -( EMAC ) ڄار حالت رجسٽر
                                                          AT91C_EMAC_SA2L EQU( 0xFFFDC0A0 );
                                                          -( EMAC ) Specific پتو 2 Bottom, پهريون 4 بائيٽون_2
                                                          AT91C_EMAC_FRO EQU( 0xFFFDC04C );
                                                          -( EMAC ) چوکٺا Received OK رجسٽر
                                                          AT91C_EMAC_IER EQU( 0xFFFDC028 );
                                                          -( EMAC ) مداخلت_2 Enable رجسٽر
                                                          AT91C_EMAC_SA1H EQU( 0xFFFDC09C );
                                                          -( EMAC ) Specific پتو 1 چوٽي, آخري 2 بائيٽون_2
                                                          AT91C_EMAC_CSE EQU( 0xFFFDC068 );
                                                          -( EMAC ) Carrier Sense Error رجسٽر
                                                          AT91C_EMAC_SA3H EQU( 0xFFFDC0AC );
                                                          -( EMAC ) Specific پتو 3 چوٽي, آخري 2 بائيٽون_2
                                                          AT91C_EMAC_RRE EQU( 0xFFFDC06C );
                                                          -( EMAC ) Receive Resource Error رجسٽر
                                                          AT91C_EMAC_STE EQU( 0xFFFDC084 );
                                                          -( EMAC ) SQE Test Error رجسٽر
/* - ========== Register definition for PDC_ADC peripheral ========== */
                                                          AT91C_ADC_PTSR EQU( 0xFFFD8124 );
                                                          -( PDC_ADC ) PDC Transfer حالت رجسٽر
                                                          AT91C_ADC_PTCR EQU( 0xFFFD8120 );
                                                          -( PDC_ADC ) PDC Transfer Control رجسٽر
                                                          AT91C_ADC_TNPR EQU( 0xFFFD8118 );
                                                          -( PDC_ADC ) Transmit ايندڙ اشارو رجسٽر
                                                          AT91C_ADC_TNCR EQU( 0xFFFD811C );
                                                          -( PDC_ADC ) Transmit ايندڙ Counter رجسٽر
                                                          AT91C_ADC_RNPR EQU( 0xFFFD8110 );
                                                          -( PDC_ADC ) Receive ايندڙ اشارو رجسٽر
                                                          AT91C_ADC_RNCR EQU( 0xFFFD8114 );
                                                          -( PDC_ADC ) Receive ايندڙ Counter رجسٽر
                                                          AT91C_ADC_RPR EQU( 0xFFFD8100 );
                                                          -( PDC_ADC ) Receive اشارو رجسٽر
                                                          AT91C_ADC_TCR EQU( 0xFFFD810C );
                                                          -( PDC_ADC ) Transmit Counter رجسٽر
                                                          AT91C_ADC_TPR EQU( 0xFFFD8108 );
                                                          -( PDC_ADC ) Transmit اشارو رجسٽر
                                                          AT91C_ADC_RCR EQU( 0xFFFD8104 );
                                                          -( PDC_ADC ) Receive Counter رجسٽر
/* - ========== Register definition for ADC peripheral ========== */
                                                          AT91C_ADC_CDR2 EQU( 0xFFFD8038 );
                                                          -( ADC ) ADC Channel معلومات رجسٽر 2
                                                          AT91C_ADC_CDR3 EQU( 0xFFFD803C );
                                                          -( ADC ) ADC Channel معلومات رجسٽر 3
                                                          AT91C_ADC_CDR0 EQU( 0xFFFD8030 );
                                                          -( ADC ) ADC Channel معلومات رجسٽر 0
                                                          AT91C_ADC_CDR5 EQU( 0xFFFD8044 );
                                                          -( ADC ) ADC Channel معلومات رجسٽر 5
                                                          AT91C_ADC_CHDR EQU( 0xFFFD8014 );
                                                          -( ADC ) ADC Channel Disable رجسٽر
                                                          AT91C_ADC_SR EQU( 0xFFFD801C );
                                                          -( ADC ) ADC حالت رجسٽر
                                                          AT91C_ADC_CDR4 EQU( 0xFFFD8040 );
                                                          -( ADC ) ADC Channel معلومات رجسٽر 4
                                                          AT91C_ADC_CDR1 EQU( 0xFFFD8034 );
                                                          -( ADC ) ADC Channel معلومات رجسٽر 1
                                                          AT91C_ADC_LCDR EQU( 0xFFFD8020 );
                                                          -( ADC ) ADC آخري Converted معلومات رجسٽر
                                                          AT91C_ADC_IDR EQU( 0xFFFD8028 );
                                                          -( ADC ) ADC مداخلت_2 Disable رجسٽر
                                                          AT91C_ADC_CR EQU( 0xFFFD8000 );
                                                          -( ADC ) ADC Control رجسٽر
                                                          AT91C_ADC_CDR7 EQU( 0xFFFD804C );
                                                          -( ADC ) ADC Channel معلومات رجسٽر 7
                                                          AT91C_ADC_CDR6 EQU( 0xFFFD8048 );
                                                          -( ADC ) ADC Channel معلومات رجسٽر 6
                                                          AT91C_ADC_IER EQU( 0xFFFD8024 );
                                                          -( ADC ) ADC مداخلت_2 Enable رجسٽر
                                                          AT91C_ADC_CHER EQU( 0xFFFD8010 );
                                                          -( ADC ) ADC Channel Enable رجسٽر
                                                          AT91C_ADC_CHSR EQU( 0xFFFD8018 );
                                                          -( ADC ) ADC Channel حالت رجسٽر
                                                          AT91C_ADC_MR EQU( 0xFFFD8004 );
                                                          -( ADC ) ADC گهڻائي رجسٽر
                                                          AT91C_ADC_IMR EQU( 0xFFFD802C );
                                                          -( ADC ) ADC مداخلت_2 نقاب_2 رجسٽر
/* - ========== Register definition for PDC_AES peripheral ========== */
                                                          AT91C_AES_TPR EQU( 0xFFFA4108 );
                                                          -( PDC_AES ) Transmit اشارو رجسٽر
                                                          AT91C_AES_PTCR EQU( 0xFFFA4120 );
                                                          -( PDC_AES ) PDC Transfer Control رجسٽر
                                                          AT91C_AES_RNPR EQU( 0xFFFA4110 );
                                                          -( PDC_AES ) Receive ايندڙ اشارو رجسٽر
                                                          AT91C_AES_TNCR EQU( 0xFFFA411C );
                                                          -( PDC_AES ) Transmit ايندڙ Counter رجسٽر
                                                          AT91C_AES_TCR EQU( 0xFFFA410C );
                                                          -( PDC_AES ) Transmit Counter رجسٽر
                                                          AT91C_AES_RCR EQU( 0xFFFA4104 );
                                                          -( PDC_AES ) Receive Counter رجسٽر
                                                          AT91C_AES_RNCR EQU( 0xFFFA4114 );
                                                          -( PDC_AES ) Receive ايندڙ Counter رجسٽر
                                                          AT91C_AES_TNPR EQU( 0xFFFA4118 );
                                                          -( PDC_AES ) Transmit ايندڙ اشارو رجسٽر
                                                          AT91C_AES_RPR EQU( 0xFFFA4100 );
                                                          -( PDC_AES ) Receive اشارو رجسٽر
                                                          AT91C_AES_PTSR EQU( 0xFFFA4124 );
                                                          -( PDC_AES ) PDC Transfer حالت رجسٽر
/* - ========== Register definition for AES peripheral ========== */
                                                          AT91C_AES_IVxR EQU( 0xFFFA4060 );
                                                          -( AES ) Initialization ويڪٽر_2 x رجسٽر
                                                          AT91C_AES_MR EQU( 0xFFFA4004 );
                                                          -( AES ) گهڻائي رجسٽر
                                                          AT91C_AES_VR EQU( 0xFFFA40FC );
                                                          -( AES ) AES نسخو_2 رجسٽر
                                                          AT91C_AES_ODATAxR EQU( 0xFFFA4050 );
                                                          -( AES ) Output معلومات x رجسٽر
                                                          AT91C_AES_IDATAxR EQU( 0xFFFA4040 );
                                                          -( AES ) داخلا معلومات x رجسٽر
                                                          AT91C_AES_CR EQU( 0xFFFA4000 );
                                                          -( AES ) Control رجسٽر
                                                          AT91C_AES_IDR EQU( 0xFFFA4014 );
                                                          -( AES ) مداخلت_2 Disable رجسٽر
                                                          AT91C_AES_IMR EQU( 0xFFFA4018 );
                                                          -( AES ) مداخلت_2 نقاب_2 رجسٽر
                                                          AT91C_AES_IER EQU( 0xFFFA4010 );
                                                          -( AES ) مداخلت_2 Enable رجسٽر
                                                          AT91C_AES_KEYWxR EQU( 0xFFFA4020 );
                                                          -( AES ) ڪنجي_2 لفظ_3 x رجسٽر
                                                          AT91C_AES_ISR EQU( 0xFFFA401C );
                                                          -( AES ) مداخلت_2 حالت رجسٽر
/* - ========== Register definition for PDC_TDES peripheral ========== */
                                                          AT91C_TDES_RNCR EQU( 0xFFFA8114 );
                                                          -( PDC_TDES ) Receive ايندڙ Counter رجسٽر
                                                          AT91C_TDES_TCR EQU( 0xFFFA810C );
                                                          -( PDC_TDES ) Transmit Counter رجسٽر
                                                          AT91C_TDES_RCR EQU( 0xFFFA8104 );
                                                          -( PDC_TDES ) Receive Counter رجسٽر
                                                          AT91C_TDES_TNPR EQU( 0xFFFA8118 );
                                                          -( PDC_TDES ) Transmit ايندڙ اشارو رجسٽر
                                                          AT91C_TDES_RNPR EQU( 0xFFFA8110 );
                                                          -( PDC_TDES ) Receive ايندڙ اشارو رجسٽر
                                                          AT91C_TDES_RPR EQU( 0xFFFA8100 );
                                                          -( PDC_TDES ) Receive اشارو رجسٽر
                                                          AT91C_TDES_TNCR EQU( 0xFFFA811C );
                                                          -( PDC_TDES ) Transmit ايندڙ Counter رجسٽر
                                                          AT91C_TDES_TPR EQU( 0xFFFA8108 );
                                                          -( PDC_TDES ) Transmit اشارو رجسٽر
                                                          AT91C_TDES_PTSR EQU( 0xFFFA8124 );
                                                          -( PDC_TDES ) PDC Transfer حالت رجسٽر
                                                          AT91C_TDES_PTCR EQU( 0xFFFA8120 );
                                                          -( PDC_TDES ) PDC Transfer Control رجسٽر
/* - ========== Register definition for TDES peripheral ========== */
                                                          AT91C_TDES_KEY2WxR EQU( 0xFFFA8028 );
                                                          -( TDES ) ڪنجي_2 2 لفظ_3 x رجسٽر
                                                          AT91C_TDES_KEY3WxR EQU( 0xFFFA8030 );
                                                          -( TDES ) ڪنجي_2 3 لفظ_3 x رجسٽر
                                                          AT91C_TDES_IDR EQU( 0xFFFA8014 );
                                                          -( TDES ) مداخلت_2 Disable رجسٽر
                                                          AT91C_TDES_VR EQU( 0xFFFA80FC );
                                                          -( TDES ) TDES نسخو_2 رجسٽر
                                                          AT91C_TDES_IVxR EQU( 0xFFFA8060 );
                                                          -( TDES ) Initialization ويڪٽر_2 x رجسٽر
                                                          AT91C_TDES_ODATAxR EQU( 0xFFFA8050 );
                                                          -( TDES ) Output معلومات x رجسٽر
                                                          AT91C_TDES_IMR EQU( 0xFFFA8018 );
                                                          -( TDES ) مداخلت_2 نقاب_2 رجسٽر
                                                          AT91C_TDES_MR EQU( 0xFFFA8004 );
                                                          -( TDES ) گهڻائي رجسٽر
                                                          AT91C_TDES_CR EQU( 0xFFFA8000 );
                                                          -( TDES ) Control رجسٽر
                                                          AT91C_TDES_IER EQU( 0xFFFA8010 );
                                                          -( TDES ) مداخلت_2 Enable رجسٽر
                                                          AT91C_TDES_ISR EQU( 0xFFFA801C );
                                                          -( TDES ) مداخلت_2 حالت رجسٽر
                                                          AT91C_TDES_IDATAxR EQU( 0xFFFA8040 );
                                                          -( TDES ) داخلا معلومات x رجسٽر
                                                          AT91C_TDES_KEY1WxR EQU( 0xFFFA8020 );
                                                          -( TDES ) ڪنجي_2 1 لفظ_3 x رجسٽر

/* - ***************************************************************************** */
/* -               PIO DEFINITIONS FOR AT91SAM7X256 */
/* - ***************************************************************************** */
                                                          AT91C_PIO_PA0 EQU( 1 << 0 );
                                                          -Pin Controlled by PA0
                                                          AT91C_PA0_RXD0 EQU( AT91C_PIO_PA0 );
                                                          -USART 0 Receive معلومات
                                                          AT91C_PIO_PA1 EQU( 1 << 1 );
                                                          -Pin Controlled by PA1
                                                          AT91C_PA1_TXD0 EQU( AT91C_PIO_PA1 );
                                                          -USART 0 Transmit معلومات
                                                          AT91C_PIO_PA10 EQU( 1 << 10 );
                                                          -Pin Controlled by PA10
                                                          AT91C_PA10_TWD EQU( AT91C_PIO_PA10 );
                                                          -TWI Two - wire Serial معلومات
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
                                                          -External مداخلت_2 1
                                                          AT91C_PIO_PA15 EQU( 1 << 15 );
                                                          -Pin Controlled by PA15
                                                          AT91C_PA15_NPCS03 EQU( AT91C_PIO_PA15 );
                                                          -SPI 0 Peripheral Chip Select 3
                                                          AT91C_PA15_TCLK2 EQU( AT91C_PIO_PA15 );
                                                          -Timer Counter 2 external clock داخلا_2
                                                          AT91C_PIO_PA16 EQU( 1 << 16 );
                                                          -Pin Controlled by PA16
                                                          AT91C_PA16_MISO0 EQU( AT91C_PIO_PA16 );
                                                          -SPI 0 Master اندريون_3 Slave
                                                          AT91C_PIO_PA17 EQU( 1 << 17 );
                                                          -Pin Controlled by PA17
                                                          AT91C_PA17_MOSI0 EQU( AT91C_PIO_PA17 );
                                                          -SPI 0 Master ٻاهريون_3 Slave
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
                                                          -SSC Transmit چوکٺو Sync
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
                                                          -SSC Transmit معلومات_2
                                                          AT91C_PA23_MOSI1 EQU( AT91C_PIO_PA23 );
                                                          -SPI 1 Master ٻاهريون_3 Slave
                                                          AT91C_PIO_PA24 EQU( 1 << 24 );
                                                          -Pin Controlled by PA24
                                                          AT91C_PA24_RD EQU( AT91C_PIO_PA24 );
                                                          -SSC Receive معلومات
                                                          AT91C_PA24_MISO1 EQU( AT91C_PIO_PA24 );
                                                          -SPI 1 Master اندريون_3 Slave
                                                          AT91C_PIO_PA25 EQU( 1 << 25 );
                                                          -Pin Controlled by PA25
                                                          AT91C_PA25_RK EQU( AT91C_PIO_PA25 );
                                                          -SSC Receive Clock
                                                          AT91C_PA25_NPCS11 EQU( AT91C_PIO_PA25 );
                                                          -SPI 1 Peripheral Chip Select 1
                                                          AT91C_PIO_PA26 EQU( 1 << 26 );
                                                          -Pin Controlled by PA26
                                                          AT91C_PA26_RF EQU( AT91C_PIO_PA26 );
                                                          -SSC Receive چوکٺو Sync
                                                          AT91C_PA26_NPCS12 EQU( AT91C_PIO_PA26 );
                                                          -SPI 1 Peripheral Chip Select 2
                                                          AT91C_PIO_PA27 EQU( 1 << 27 );
                                                          -Pin Controlled by PA27
                                                          AT91C_PA27_DRXD EQU( AT91C_PIO_PA27 );
                                                          -DBGU Debug Receive معلومات
                                                          AT91C_PA27_PCK3 EQU( AT91C_PIO_PA27 );
                                                          -PMC Programmable Clock Output 3
                                                          AT91C_PIO_PA28 EQU( 1 << 28 );
                                                          -Pin Controlled by PA28
                                                          AT91C_PA28_DTXD EQU( AT91C_PIO_PA28 );
                                                          -DBGU Debug Transmit معلومات
                                                          AT91C_PIO_PA29 EQU( 1 << 29 );
                                                          -Pin Controlled by PA29
                                                          AT91C_PA29_FIQ EQU( AT91C_PIO_PA29 );
                                                          -AIC Fast مداخلت_2 داخلا
                                                          AT91C_PA29_NPCS13 EQU( AT91C_PIO_PA29 );
                                                          -SPI 1 Peripheral Chip Select 3
                                                          AT91C_PIO_PA3 EQU( 1 << 3 );
                                                          -Pin Controlled by PA3
                                                          AT91C_PA3_RTS0 EQU( AT91C_PIO_PA3 );
                                                          -USART 0 Ready منزل_2 Send
                                                          AT91C_PA3_NPCS12 EQU( AT91C_PIO_PA3 );
                                                          -SPI 1 Peripheral Chip Select 2
                                                          AT91C_PIO_PA30 EQU( 1 << 30 );
                                                          -Pin Controlled by PA30
                                                          AT91C_PA30_IRQ0 EQU( AT91C_PIO_PA30 );
                                                          -External مداخلت_2 0
                                                          AT91C_PA30_PCK2 EQU( AT91C_PIO_PA30 );
                                                          -PMC Programmable Clock Output 2
                                                          AT91C_PIO_PA4 EQU( 1 << 4 );
                                                          -Pin Controlled by PA4
                                                          AT91C_PA4_CTS0 EQU( AT91C_PIO_PA4 );
                                                          -USART 0 Clear منزل_2 Send
                                                          AT91C_PA4_NPCS13 EQU( AT91C_PIO_PA4 );
                                                          -SPI 1 Peripheral Chip Select 3
                                                          AT91C_PIO_PA5 EQU( 1 << 5 );
                                                          -Pin Controlled by PA5
                                                          AT91C_PA5_RXD1 EQU( AT91C_PIO_PA5 );
                                                          -USART 1 Receive معلومات
                                                          AT91C_PIO_PA6 EQU( 1 << 6 );
                                                          -Pin Controlled by PA6
                                                          AT91C_PA6_TXD1 EQU( AT91C_PIO_PA6 );
                                                          -USART 1 Transmit معلومات
                                                          AT91C_PIO_PA7 EQU( 1 << 7 );
                                                          -Pin Controlled by PA7
                                                          AT91C_PA7_SCK1 EQU( AT91C_PIO_PA7 );
                                                          -USART 1 Serial Clock
                                                          AT91C_PA7_NPCS01 EQU( AT91C_PIO_PA7 );
                                                          -SPI 0 Peripheral Chip Select 1
                                                          AT91C_PIO_PA8 EQU( 1 << 8 );
                                                          -Pin Controlled by PA8
                                                          AT91C_PA8_RTS1 EQU( AT91C_PIO_PA8 );
                                                          -USART 1 Ready منزل_2 Send
                                                          AT91C_PA8_NPCS02 EQU( AT91C_PIO_PA8 );
                                                          -SPI 0 Peripheral Chip Select 2
                                                          AT91C_PIO_PA9 EQU( 1 << 9 );
                                                          -Pin Controlled by PA9
                                                          AT91C_PA9_CTS1 EQU( AT91C_PIO_PA9 );
                                                          -USART 1 Clear منزل_2 Send
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
                                                          -Ethernet MAC Transmit معلومات 2
                                                          AT91C_PB10_NPCS11 EQU( AT91C_PIO_PB10 );
                                                          -SPI 1 Peripheral Chip Select 1
                                                          AT91C_PIO_PB11 EQU( 1 << 11 );
                                                          -Pin Controlled by PB11
                                                          AT91C_PB11_ETX3 EQU( AT91C_PIO_PB11 );
                                                          -Ethernet MAC Transmit معلومات 3
                                                          AT91C_PB11_NPCS12 EQU( AT91C_PIO_PB11 );
                                                          -SPI 1 Peripheral Chip Select 2
                                                          AT91C_PIO_PB12 EQU( 1 << 12 );
                                                          -Pin Controlled by PB12
                                                          AT91C_PB12_ETXER EQU( AT91C_PIO_PB12 );
                                                          -Ethernet MAC Transmit Coding Error
                                                          AT91C_PB12_TCLK0 EQU( AT91C_PIO_PB12 );
                                                          -Timer Counter 0 external clock داخلا_2
                                                          AT91C_PIO_PB13 EQU( 1 << 13 );
                                                          -Pin Controlled by PB13
                                                          AT91C_PB13_ERX2 EQU( AT91C_PIO_PB13 );
                                                          -Ethernet MAC Receive معلومات 2
                                                          AT91C_PB13_NPCS01 EQU( AT91C_PIO_PB13 );
                                                          -SPI 0 Peripheral Chip Select 1
                                                          AT91C_PIO_PB14 EQU( 1 << 14 );
                                                          -Pin Controlled by PB14
                                                          AT91C_PB14_ERX3 EQU( AT91C_PIO_PB14 );
                                                          -Ethernet MAC Receive معلومات 3
                                                          AT91C_PB14_NPCS02 EQU( AT91C_PIO_PB14 );
                                                          -SPI 0 Peripheral Chip Select 2
                                                          AT91C_PIO_PB15 EQU( 1 << 15 );
                                                          -Pin Controlled by PB15
                                                          AT91C_PB15_ERXDV EQU( AT91C_PIO_PB15 );
                                                          -Ethernet MAC Receive معلومات Valid
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
                                                          -Timer Counter 1 external clock داخلا_2
                                                          AT91C_PIO_PB2 EQU( 1 << 2 );
                                                          -Pin Controlled by PB2
                                                          AT91C_PB2_ETX0 EQU( AT91C_PIO_PB2 );
                                                          -Ethernet MAC Transmit معلومات 0
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
                                                          -USART 1 معلومات Carrier Detect
                                                          AT91C_PIO_PB24 EQU( 1 << 24 );
                                                          -Pin Controlled by PB24
                                                          AT91C_PB24_TIOB0 EQU( AT91C_PIO_PB24 );
                                                          -Timer Counter 0 Multipurpose Timer I / O Pin B
                                                          AT91C_PB24_DSR1 EQU( AT91C_PIO_PB24 );
                                                          -USART 1 معلومات سيٽ_2 ready
                                                          AT91C_PIO_PB25 EQU( 1 << 25 );
                                                          -Pin Controlled by PB25
                                                          AT91C_PB25_TIOA1 EQU( AT91C_PIO_PB25 );
                                                          -Timer Counter 1 Multipurpose Timer I / O Pin A
                                                          AT91C_PB25_DTR1 EQU( AT91C_PIO_PB25 );
                                                          -USART 1 معلومات Terminal ready
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
                                                          -Ethernet MAC Transmit معلومات 1
                                                          AT91C_PIO_PB30 EQU( 1 << 30 );
                                                          -Pin Controlled by PB30
                                                          AT91C_PB30_PCK2 EQU( AT91C_PIO_PB30 );
                                                          -PMC Programmable Clock Output 2
                                                          AT91C_PB30_PWM3 EQU( AT91C_PIO_PB30 );
                                                          -PWM Channel 3
                                                          AT91C_PIO_PB4 EQU( 1 << 4 );
                                                          -Pin Controlled by PB4
                                                          AT91C_PB4_ECRS_ECRSDV EQU( AT91C_PIO_PB4 );
                                                          -Ethernet MAC Carrier Sense / Carrier Sense and معلومات Valid
                                                          AT91C_PIO_PB5 EQU( 1 << 5 );
                                                          -Pin Controlled by PB5
                                                          AT91C_PB5_ERX0 EQU( AT91C_PIO_PB5 );
                                                          -Ethernet MAC Receive معلومات 0
                                                          AT91C_PIO_PB6 EQU( 1 << 6 );
                                                          -Pin Controlled by PB6
                                                          AT91C_PB6_ERX1 EQU( AT91C_PIO_PB6 );
                                                          -Ethernet MAC Receive معلومات 1
                                                          AT91C_PIO_PB7 EQU( 1 << 7 );
                                                          -Pin Controlled by PB7
                                                          AT91C_PB7_ERXER EQU( AT91C_PIO_PB7 );
                                                          -Ethernet MAC Receive Error
                                                          AT91C_PIO_PB8 EQU( 1 << 8 );
                                                          -Pin Controlled by PB8
                                                          AT91C_PB8_EMDC EQU( AT91C_PIO_PB8 );
                                                          -Ethernet MAC Management معلومات Clock
                                                          AT91C_PIO_PB9 EQU( 1 << 9 );
                                                          -Pin Controlled by PB9
                                                          AT91C_PB9_EMDIO EQU( AT91C_PIO_PB9 );
                                                          -Ethernet MAC Management معلومات داخلا / Output

/* - ***************************************************************************** */
/* -               PERIPHERAL ID DEFINITIONS FOR AT91SAM7X256 */
/* - ***************************************************************************** */
                                                          AT91C_ID_FIQ EQU( 0 );
                                                          -Advanced مداخلت_2 Controller( FIQ )
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
                                                          -USB Device پورٽ_2
                                                          AT91C_ID_TC0 EQU( 12 );
                                                          -Timer Counter 0
                                                          AT91C_ID_TC1 EQU( 13 );
                                                          -Timer Counter 1
                                                          AT91C_ID_TC2 EQU( 14 );
                                                          -Timer Counter 2
                                                          AT91C_ID_CAN EQU( 15 );
                                                          -Control Area ڄار Controller
                                                          AT91C_ID_EMAC EQU( 16 );
                                                          -Ethernet MAC
                                                          AT91C_ID_ADC EQU( 17 );
                                                          -Analog - منزل - Digital Converter
                                                          AT91C_ID_AES EQU( 18 );
                                                          -Advanced Encryption Standard 128 - ٻٽو_انگ_2
                                                          AT91C_ID_TDES EQU( 19 );
                                                          -Triple معلومات Encryption Standard
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
                                                          -Advanced مداخلت_2 Controller( IRQ0 )
                                                          AT91C_ID_IRQ1 EQU( 31 );
                                                          -Advanced مداخلت_2 Controller( IRQ1 )

/* - ***************************************************************************** */
/* -               BASE ADDRESS DEFINITIONS FOR AT91SAM7X256 */
/* - ***************************************************************************** */
                                                          AT91_C_بنياد_SYS EQU( 0xFFFFF000 );
                                                          -( SYS ) بنياد_2 پتو
                                                          AT91_C_بنياد_AIC EQU( 0xFFFFF000 );
                                                          -( AIC ) بنياد_2 پتو
                                                          AT91_C_بنياد_PDC_DBGU EQU( 0xFFFFF300 );
                                                          -( PDC_DBGU ) بنياد_2 پتو
                                                          AT91_C_بنياد_DBGU EQU( 0xFFFFF200 );
                                                          -( DBGU ) بنياد_2 پتو
                                                          AT91_C_بنياد_PIOA EQU( 0xFFFFF400 );
                                                          -( PIOA ) بنياد_2 پتو
                                                          AT91_C_بنياد_PIOB EQU( 0xFFFFF600 );
                                                          -( PIOB ) بنياد_2 پتو
                                                          AT91_C_بنياد_CKGR EQU( 0xFFFFFC20 );
                                                          -( CKGR ) بنياد_2 پتو
                                                          AT91_C_بنياد_PMC EQU( 0xFFFFFC00 );
                                                          -( PMC ) بنياد_2 پتو
                                                          AT91_C_بنياد_RSTC EQU( 0xFFFFFD00 );
                                                          -( RSTC ) بنياد_2 پتو
                                                          AT91_C_بنياد_RTTC EQU( 0xFFFFFD20 );
                                                          -( RTTC ) بنياد_2 پتو
                                                          AT91_C_بنياد_PITC EQU( 0xFFFFFD30 );
                                                          -( PITC ) بنياد_2 پتو
                                                          AT91_C_بنياد_WDTC EQU( 0xFFFFFD40 );
                                                          -( WDTC ) بنياد_2 پتو
                                                          AT91_C_بنياد_VREG EQU( 0xFFFFFD60 );
                                                          -( VREG ) بنياد_2 پتو
                                                          AT91_C_بنياد_MC EQU( 0xFFFFFF00 );
                                                          -( MC ) بنياد_2 پتو
                                                          AT91_C_بنياد_PDC_SPI1 EQU( 0xFFFE4100 );
                                                          -( PDC_SPI1 ) بنياد_2 پتو
                                                          AT91_C_بنياد_SPI1 EQU( 0xFFFE4000 );
                                                          -( SPI1 ) بنياد_2 پتو
                                                          AT91_C_بنياد_PDC_SPI0 EQU( 0xFFFE0100 );
                                                          -( PDC_SPI0 ) بنياد_2 پتو
                                                          AT91_C_بنياد_SPI0 EQU( 0xFFFE0000 );
                                                          -( SPI0 ) بنياد_2 پتو
                                                          AT91_C_بنياد_PDC_US1 EQU( 0xFFFC4100 );
                                                          -( PDC_US1 ) بنياد_2 پتو
                                                          AT91_C_بنياد_US1 EQU( 0xFFFC4000 );
                                                          -( US1 ) بنياد_2 پتو
                                                          AT91_C_بنياد_PDC_US0 EQU( 0xFFFC0100 );
                                                          -( PDC_US0 ) بنياد_2 پتو
                                                          AT91_C_بنياد_US0 EQU( 0xFFFC0000 );
                                                          -( US0 ) بنياد_2 پتو
                                                          AT91_C_بنياد_PDC_SSC EQU( 0xFFFD4100 );
                                                          -( PDC_SSC ) بنياد_2 پتو
                                                          AT91_C_بنياد_SSC EQU( 0xFFFD4000 );
                                                          -( SSC ) بنياد_2 پتو
                                                          AT91_C_بنياد_TWI EQU( 0xFFFB8000 );
                                                          -( TWI ) بنياد_2 پتو
                                                          AT91_C_بنياد_PWMC_CH3 EQU( 0xFFFCC260 );
                                                          -( PWMC_CH3 ) بنياد_2 پتو
                                                          AT91_C_بنياد_PWMC_CH2 EQU( 0xFFFCC240 );
                                                          -( PWMC_CH2 ) بنياد_2 پتو
                                                          AT91_C_بنياد_PWMC_CH1 EQU( 0xFFFCC220 );
                                                          -( PWMC_CH1 ) بنياد_2 پتو
                                                          AT91_C_بنياد_PWMC_CH0 EQU( 0xFFFCC200 );
                                                          -( PWMC_CH0 ) بنياد_2 پتو
                                                          AT91_C_بنياد_PWMC EQU( 0xFFFCC000 );
                                                          -( PWMC ) بنياد_2 پتو
                                                          AT91_C_بنياد_UDP EQU( 0xFFFB0000 );
                                                          -( UDP ) بنياد_2 پتو
                                                          AT91_C_بنياد_TC0 EQU( 0xFFFA0000 );
                                                          -( TC0 ) بنياد_2 پتو
                                                          AT91_C_بنياد_TC1 EQU( 0xFFFA0040 );
                                                          -( TC1 ) بنياد_2 پتو
                                                          AT91_C_بنياد_TC2 EQU( 0xFFFA0080 );
                                                          -( TC2 ) بنياد_2 پتو
                                                          AT91_C_بنياد_TCB EQU( 0xFFFA0000 );
                                                          -( TCB ) بنياد_2 پتو
                                                          AT91_C_بنياد_CAN_MB0 EQU( 0xFFFD0200 );
                                                          -( CAN_MB0 ) بنياد_2 پتو
                                                          AT91_C_بنياد_CAN_MB1 EQU( 0xFFFD0220 );
                                                          -( CAN_MB1 ) بنياد_2 پتو
                                                          AT91_C_بنياد_CAN_MB2 EQU( 0xFFFD0240 );
                                                          -( CAN_MB2 ) بنياد_2 پتو
                                                          AT91_C_بنياد_CAN_MB3 EQU( 0xFFFD0260 );
                                                          -( CAN_MB3 ) بنياد_2 پتو
                                                          AT91_C_بنياد_CAN_MB4 EQU( 0xFFFD0280 );
                                                          -( CAN_MB4 ) بنياد_2 پتو
                                                          AT91_C_بنياد_CAN_MB5 EQU( 0xFFFD02A0 );
                                                          -( CAN_MB5 ) بنياد_2 پتو
                                                          AT91_C_بنياد_CAN_MB6 EQU( 0xFFFD02C0 );
                                                          -( CAN_MB6 ) بنياد_2 پتو
                                                          AT91_C_بنياد_CAN_MB7 EQU( 0xFFFD02E0 );
                                                          -( CAN_MB7 ) بنياد_2 پتو
                                                          AT91_C_بنياد_CAN EQU( 0xFFFD0000 );
                                                          -( CAN ) بنياد_2 پتو
                                                          AT91_C_بنياد_EMAC EQU( 0xFFFDC000 );
                                                          -( EMAC ) بنياد_2 پتو
                                                          AT91_C_بنياد_PDC_ADC EQU( 0xFFFD8100 );
                                                          -( PDC_ADC ) بنياد_2 پتو
                                                          AT91_C_بنياد_ADC EQU( 0xFFFD8000 );
                                                          -( ADC ) بنياد_2 پتو
                                                          AT91_C_بنياد_PDC_AES EQU( 0xFFFA4100 );
                                                          -( PDC_AES ) بنياد_2 پتو
                                                          AT91_C_بنياد_AES EQU( 0xFFFA4000 );
                                                          -( AES ) بنياد_2 پتو
                                                          AT91_C_بنياد_PDC_TDES EQU( 0xFFFA8100 );
                                                          -( PDC_TDES ) بنياد_2 پتو
                                                          AT91_C_بنياد_TDES EQU( 0xFFFA8000 );
                                                          -( TDES ) بنياد_2 پتو

/* - ***************************************************************************** */
/* -               MEMORY MAPPING DEFINITIONS FOR AT91SAM7X256 */
/* - ***************************************************************************** */
                                                          AT91C_ISRAM EQU( 0x00200000 );
                                                          -اندروني SRAM بنياد پتو_2
                                                          AT91_C_ISRAM_سائيز EQU( 0x00010000 );
                                                          -اندروني SRAM سائيز اندريون byte( 64 Kbyte )
                                                          AT91C_IFLASH EQU( 0x00100000 );
                                                          -اندروني ROM بنياد پتو_2
                                                          AT91_C_IFLASH_سائيز EQU( 0x00040000 );
                                                          -اندروني ROM سائيز اندريون byte( 256 Kbyte )



#جيڪڏهن_پورو /* AT91SAM7X256_H */
