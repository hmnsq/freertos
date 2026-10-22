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

#यदि_अपरिभाषितम् AT91SAM7X256_H
#परिभाषय AT91SAM7X256_H

प्रकारनिर्देश चञ्चल अचिह्नित पूर्णाङ्क AT91_REG; /* Hardware register definition */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR System Peripherals */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_SYS
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
    AT91_REG PIOA_प्रत्येकम्;          /* PIO Enable Register */
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
    AT91_REG PIOB_प्रत्येकम्;          /* PIO Enable Register */
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
प्रकारनिर्देश संरचना _AT91S_AIC
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
#परिभाषय AT91_C_AIC_प्राक्                            ( ( अचिह्नित पूर्णाङ्क ) 0x7 << 0 ) /* (AIC) Priority Level */
#परिभाषय     AT91_C_AIC_प्राक्_निम्नतमम्                 ( ( अचिह्नित पूर्णाङ्क ) 0x0 )      /* (AIC) Lowest priority level */
#परिभाषय     AT91_C_AIC_प्राक्_HIGHEST                ( ( अचिह्नित पूर्णाङ्क ) 0x7 )      /* (AIC) Highest priority level */
#परिभाषय AT91C_AIC_SRCTYPE                          ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 5 ) /* (AIC) Interrupt Source Type */
#परिभाषय     AT91_C_AIC_SRCTYPE_INT_उच्चः_LEVEL       ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 5 ) /* (AIC) Internal Sources Code Label High-level Sensitive */
#परिभाषय     AT91_C_AIC_SRCTYPE_EXT_नीचः_LEVEL        ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 5 ) /* (AIC) External Sources Code Label Low-level Sensitive */
#परिभाषय     AT91_C_AIC_SRCTYPE_INT_धनात्मकम्_EDGE    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 ) /* (AIC) Internal Sources Code Label Positive Edge triggered */
#परिभाषय     AT91C_AIC_SRCTYPE_EXT_NEGATIVE_EDGE    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 ) /* (AIC) External Sources Code Label Negative Edge triggered */
#परिभाषय     AT91_C_AIC_SRCTYPE_उच्चः_LEVEL           ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 5 ) /* (AIC) Internal Or External Sources Code Label High-level Sensitive */
#परिभाषय     AT91_C_AIC_SRCTYPE_धनात्मकम्_EDGE        ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 5 ) /* (AIC) Internal Or External Sources Code Label Positive Edge triggered */
/* -------- AIC_CISR : (AIC Offset: 0x114) AIC Core Interrupt Status Register -------- */
#परिभाषय AT91C_AIC_NFIQ                             ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 ) /* (AIC) NFIQ Status */
#परिभाषय AT91C_AIC_NIRQ                             ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 ) /* (AIC) NIRQ Status */
/* -------- AIC_DCR : (AIC Offset: 0x138) AIC Debug Control Register (Protect) -------- */
#परिभाषय AT91C_AIC_DCR_PROT                         ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 ) /* (AIC) Protection Mode */
#परिभाषय AT91C_AIC_DCR_GMSK                         ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 ) /* (AIC) General Mask */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Peripheral DMA Controller */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_PDC
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
#परिभाषय AT91C_PDC_RXTEN     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 ) /* (PDC) Receiver Transfer Enable */
#परिभाषय AT91C_PDC_RXTDIS    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 ) /* (PDC) Receiver Transfer Disable */
#परिभाषय AT91C_PDC_TXTEN     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 ) /* (PDC) Transmitter Transfer Enable */
#परिभाषय AT91C_PDC_TXTDIS    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 9 ) /* (PDC) Transmitter Transfer Disable */
/* -------- PDC_PTSR : (PDC Offset: 0x24) PDC Transfer Status Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Debug Unit */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_DBGU
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
#परिभाषय AT91C_US_RSTRX                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )  /* (DBGU) Reset Receiver */
#परिभाषय AT91C_US_RSTTX                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )  /* (DBGU) Reset Transmitter */
#परिभाषय AT91C_US_RXEN                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )  /* (DBGU) Receiver Enable */
#परिभाषय AT91C_US_RXDIS                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 )  /* (DBGU) Receiver Disable */
#परिभाषय AT91C_US_TXEN                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 6 )  /* (DBGU) Transmitter Enable */
#परिभाषय AT91C_US_TXDIS                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )  /* (DBGU) Transmitter Disable */
#परिभाषय AT91C_US_RSTSTA                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )  /* (DBGU) Reset Status Bits */
/* -------- DBGU_MR : (DBGU Offset: 0x4) Debug Unit Mode Register -------- */
#परिभाषय AT91C_US_PAR                   ( ( अचिह्नित पूर्णाङ्क ) 0x7 << 9 )  /* (DBGU) Parity type */
#परिभाषय     AT91C_US_PAR_EVEN          ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 9 )  /* (DBGU) Even Parity */
#परिभाषय     AT91C_US_PAR_ODD           ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 9 )  /* (DBGU) Odd Parity */
#परिभाषय     AT91C_US_PAR_SPACE         ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 9 )  /* (DBGU) Parity forced to 0 (Space) */
#परिभाषय     AT91C_US_PAR_MARK          ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 9 )  /* (DBGU) Parity forced to 1 (Mark) */
#परिभाषय     AT91C_US_PAR_NONE          ( ( अचिह्नित पूर्णाङ्क ) 0x4 << 9 )  /* (DBGU) No Parity */
#परिभाषय     AT91C_US_PAR_MULTI_DROP    ( ( अचिह्नित पूर्णाङ्क ) 0x6 << 9 )  /* (DBGU) Multi-drop mode */
#परिभाषय AT91C_US_CHMODE                ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 14 ) /* (DBGU) Channel Mode */
#परिभाषय     AT91_C_US_CHMODE_प्रसामान्यम्     ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 14 ) /* (DBGU) Normal Mode: The USART channel operates as an RX/TX USART. */
#परिभाषय     AT91C_US_CHMODE_AUTO       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 14 ) /* (DBGU) Automatic Echo: Receiver Data Input is connected to the TXD pin. */
#परिभाषय     AT91C_US_CHMODE_LOCAL      ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 14 ) /* (DBGU) Local Loopback: Transmitter Output Signal is connected to Receiver Input Signal. */
#परिभाषय     AT91C_US_CHMODE_REMOTE     ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 14 ) /* (DBGU) Remote Loopback: RXD pin is internally connected to TXD pin. */
/* -------- DBGU_IER : (DBGU Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
#परिभाषय AT91C_US_RXRDY                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )  /* (DBGU) RXRDY Interrupt */
#परिभाषय AT91C_US_TXRDY                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )  /* (DBGU) TXRDY Interrupt */
#परिभाषय AT91C_US_ENDRX                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )  /* (DBGU) End of Receive Transfer Interrupt */
#परिभाषय AT91C_US_ENDTX                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )  /* (DBGU) End of Transmit Interrupt */
#परिभाषय AT91C_US_OVRE                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 )  /* (DBGU) Overrun Interrupt */
#परिभाषय AT91C_US_FRAME                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 6 )  /* (DBGU) Framing Error Interrupt */
#परिभाषय AT91C_US_PARE                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )  /* (DBGU) Parity Error Interrupt */
#परिभाषय AT91C_US_TXEMPTY               ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 9 )  /* (DBGU) TXEMPTY Interrupt */
#परिभाषय AT91C_US_TXBUFE                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 11 ) /* (DBGU) TXBUFE Interrupt */
#परिभाषय AT91C_US_RXBUFF                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 12 ) /* (DBGU) RXBUFF Interrupt */
#परिभाषय AT91C_US_COMM_TX               ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 30 ) /* (DBGU) COMM_TX Interrupt */
#परिभाषय AT91C_US_COMM_RX               ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 31 ) /* (DBGU) COMM_RX Interrupt */
/* -------- DBGU_IDR : (DBGU Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* -------- DBGU_IMR : (DBGU Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* -------- DBGU_CSR : (DBGU Offset: 0x14) Debug Unit Channel Status Register -------- */
/* -------- DBGU_FNTR : (DBGU Offset: 0x48) Debug Unit FORCE_NTRST Register -------- */
#परिभाषय AT91C_US_FORCE_NTRST    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 ) /* (DBGU) Force NTRST in JTAG */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Parallel Input Output Controller */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_PIO
{
    AT91_REG PIO_प्रत्येकम्;        /* PIO Enable Register */
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
प्रकारनिर्देश संरचना _AT91S_CKGR
{
    AT91_REG CKGR_MOR;       /* Main Oscillator Register */
    AT91_REG CKGR_MCFR;      /* Main Clock  Frequency Register */
    AT91_REG Reserved0[ 1 ]; /* */
    AT91_REG CKGR_PLLR;      /* PLL Register */
} AT91S_CKGR, * AT91PS_CKGR;

/* -------- CKGR_MOR : (CKGR Offset: 0x0) Main Oscillator Register -------- */
#परिभाषय AT91C_CKGR_MOSCEN            ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )    /* (CKGR) Main Oscillator Enable */
#परिभाषय AT91C_CKGR_OSCBYPASS         ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )    /* (CKGR) Main Oscillator Bypass */
#परिभाषय AT91C_CKGR_OSCOUNT           ( ( अचिह्नित पूर्णाङ्क ) 0xFF << 8 )   /* (CKGR) Main Oscillator Start-up Time */
/* -------- CKGR_MCFR : (CKGR Offset: 0x4) Main Clock Frequency Register -------- */
#परिभाषय AT91C_CKGR_MAINF             ( ( अचिह्नित पूर्णाङ्क ) 0xFFFF << 0 ) /* (CKGR) Main Clock Frequency */
#परिभाषय AT91C_CKGR_MAINRDY           ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 )   /* (CKGR) Main Clock Ready */
/* -------- CKGR_PLLR : (CKGR Offset: 0xc) PLL B Register -------- */
#परिभाषय AT91C_CKGR_DIV               ( ( अचिह्नित पूर्णाङ्क ) 0xFF << 0 )   /* (CKGR) Divider Selected */
#परिभाषय     AT91C_CKGR_DIV_0         ( ( अचिह्नित पूर्णाङ्क ) 0x0 )         /* (CKGR) Divider output is 0 */
#परिभाषय     AT91C_CKGR_DIV_BYPASS    ( ( अचिह्नित पूर्णाङ्क ) 0x1 )         /* (CKGR) Divider is bypassed */
#परिभाषय AT91C_CKGR_PLLCOUNT          ( ( अचिह्नित पूर्णाङ्क ) 0x3F << 8 )   /* (CKGR) PLL Counter */
#परिभाषय AT91_C_CKGR_बहिर्गमनम्               ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 14 )   /* (CKGR) PLL Output Frequency Range */
#परिभाषय     AT91_C_CKGR_बहिर्गमनम्_0         ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#परिभाषय     AT91_C_CKGR_बहिर्गमनम्_1         ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#परिभाषय     AT91_C_CKGR_बहिर्गमनम्_2         ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#परिभाषय     AT91_C_CKGR_बहिर्गमनम्_3         ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#परिभाषय AT91C_CKGR_MUL               ( ( अचिह्नित पूर्णाङ्क ) 0x7FF << 16 ) /* (CKGR) PLL Multiplier */
#परिभाषय AT91C_CKGR_USBDIV            ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 28 )   /* (CKGR) Divider for USB Clocks */
#परिभाषय     AT91C_CKGR_USBDIV_0      ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 28 )   /* (CKGR) Divider output is PLL clock output */
#परिभाषय     AT91C_CKGR_USBDIV_1      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 28 )   /* (CKGR) Divider output is PLL clock output divided by 2 */
#परिभाषय     AT91C_CKGR_USBDIV_2      ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 28 )   /* (CKGR) Divider output is PLL clock output divided by 4 */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Power Management Controller */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_PMC
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
#परिभाषय AT91C_PMC_PCK     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )  /* (PMC) Processor Clock */
#परिभाषय AT91C_PMC_UDP     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )  /* (PMC) USB Device Port Clock */
#परिभाषय AT91C_PMC_PCK0    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )  /* (PMC) Programmable Clock Output */
#परिभाषय AT91C_PMC_PCK1    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 9 )  /* (PMC) Programmable Clock Output */
#परिभाषय AT91C_PMC_PCK2    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 10 ) /* (PMC) Programmable Clock Output */
#परिभाषय AT91C_PMC_PCK3    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 11 ) /* (PMC) Programmable Clock Output */
/* -------- PMC_SCDR : (PMC Offset: 0x4) System Clock Disable Register -------- */
/* -------- PMC_SCSR : (PMC Offset: 0x8) System Clock Status Register -------- */
/* -------- CKGR_MOR : (PMC Offset: 0x20) Main Oscillator Register -------- */
/* -------- CKGR_MCFR : (PMC Offset: 0x24) Main Clock Frequency Register -------- */
/* -------- CKGR_PLLR : (PMC Offset: 0x2c) PLL B Register -------- */
/* -------- PMC_MCKR : (PMC Offset: 0x30) Master Clock Register -------- */
#परिभाषय AT91C_PMC_CSS                 ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 0 ) /* (PMC) Programmable Clock Selection */
#परिभाषय     AT91C_PMC_CSS_SLOW_CLK    ( ( अचिह्नित पूर्णाङ्क ) 0x0 )      /* (PMC) Slow Clock is selected */
#परिभाषय     AT91C_PMC_CSS_MAIN_CLK    ( ( अचिह्नित पूर्णाङ्क ) 0x1 )      /* (PMC) Main Clock is selected */
#परिभाषय     AT91C_PMC_CSS_PLL_CLK     ( ( अचिह्नित पूर्णाङ्क ) 0x3 )      /* (PMC) Clock from PLL is selected */
#परिभाषय AT91C_PMC_PRES                ( ( अचिह्नित पूर्णाङ्क ) 0x7 << 2 ) /* (PMC) Programmable Clock Prescaler */
#परिभाषय     AT91C_PMC_PRES_CLK        ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 2 ) /* (PMC) Selected clock */
#परिभाषय     AT91C_PMC_PRES_CLK_2      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 ) /* (PMC) Selected clock divided by 2 */
#परिभाषय     AT91C_PMC_PRES_CLK_4      ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 2 ) /* (PMC) Selected clock divided by 4 */
#परिभाषय     AT91C_PMC_PRES_CLK_8      ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 2 ) /* (PMC) Selected clock divided by 8 */
#परिभाषय     AT91C_PMC_PRES_CLK_16     ( ( अचिह्नित पूर्णाङ्क ) 0x4 << 2 ) /* (PMC) Selected clock divided by 16 */
#परिभाषय     AT91C_PMC_PRES_CLK_32     ( ( अचिह्नित पूर्णाङ्क ) 0x5 << 2 ) /* (PMC) Selected clock divided by 32 */
#परिभाषय     AT91C_PMC_PRES_CLK_64     ( ( अचिह्नित पूर्णाङ्क ) 0x6 << 2 ) /* (PMC) Selected clock divided by 64 */
/* -------- PMC_PCKR : (PMC Offset: 0x40) Programmable Clock Register -------- */
/* -------- PMC_IER : (PMC Offset: 0x60) PMC Interrupt Enable Register -------- */
#परिभाषय AT91C_PMC_MOSCS               ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )  /* (PMC) MOSC Status/Enable/Disable/Mask */
#परिभाषय AT91_C_PMC_तालकम्                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )  /* (PMC) PLL Status/Enable/Disable/Mask */
#परिभाषय AT91C_PMC_MCKRDY              ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )  /* (PMC) MCK_RDY Status/Enable/Disable/Mask */
#परिभाषय AT91C_PMC_PCK0RDY             ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )  /* (PMC) PCK0_RDY Status/Enable/Disable/Mask */
#परिभाषय AT91C_PMC_PCK1RDY             ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 9 )  /* (PMC) PCK1_RDY Status/Enable/Disable/Mask */
#परिभाषय AT91C_PMC_PCK2RDY             ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 10 ) /* (PMC) PCK2_RDY Status/Enable/Disable/Mask */
#परिभाषय AT91C_PMC_PCK3RDY             ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 11 ) /* (PMC) PCK3_RDY Status/Enable/Disable/Mask */
/* -------- PMC_IDR : (PMC Offset: 0x64) PMC Interrupt Disable Register -------- */
/* -------- PMC_SR : (PMC Offset: 0x68) PMC Status Register -------- */
/* -------- PMC_IMR : (PMC Offset: 0x6c) PMC Interrupt Mask Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Reset Controller Interface */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_RSTC
{
    AT91_REG RSTC_RCR; /* Reset Control Register */
    AT91_REG RSTC_RSR; /* Reset Status Register */
    AT91_REG RSTC_RMR; /* Reset Mode Register */
} AT91S_RSTC, * AT91PS_RSTC;

/* -------- RSTC_RCR : (RSTC Offset: 0x0) Reset Control Register -------- */
#परिभाषय AT91C_RSTC_PROCRST                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )   /* (RSTC) Processor Reset */
#परिभाषय AT91C_RSTC_PERRST                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )   /* (RSTC) Peripheral Reset */
#परिभाषय AT91C_RSTC_EXTRST                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )   /* (RSTC) External Reset */
#परिभाषय AT91_C_RSTC_कुञ्चिका                    ( ( अचिह्नित पूर्णाङ्क ) 0xFF << 24 ) /* (RSTC) Password */
/* -------- RSTC_RSR : (RSTC Offset: 0x4) Reset Status Register -------- */
#परिभाषय AT91C_RSTC_URSTS                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )   /* (RSTC) User Reset Status */
#परिभाषय AT91C_RSTC_BODSTS                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )   /* (RSTC) Brownout Detection Status */
#परिभाषय AT91C_RSTC_RSTTYP                 ( ( अचिह्नित पूर्णाङ्क ) 0x7 << 8 )   /* (RSTC) Reset Type */
#परिभाषय     AT91C_RSTC_RSTTYP_POWERUP     ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 8 )   /* (RSTC) Power-up Reset. VDDCORE rising. */
#परिभाषय     AT91C_RSTC_RSTTYP_WAKEUP      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )   /* (RSTC) WakeUp Reset. VDDCORE rising. */
#परिभाषय     AT91C_RSTC_RSTTYP_WATCHDOG    ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 8 )   /* (RSTC) Watchdog Reset. Watchdog overflow occurred. */
#परिभाषय     AT91C_RSTC_RSTTYP_SOFTWARE    ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 8 )   /* (RSTC) Software Reset. Processor reset required by the software. */
#परिभाषय     AT91C_RSTC_RSTTYP_USER        ( ( अचिह्नित पूर्णाङ्क ) 0x4 << 8 )   /* (RSTC) User Reset. NRST pin detected low. */
#परिभाषय     AT91C_RSTC_RSTTYP_BROWNOUT    ( ( अचिह्नित पूर्णाङ्क ) 0x5 << 8 )   /* (RSTC) Brownout Reset occurred. */
#परिभाषय AT91C_RSTC_NRSTL                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 )  /* (RSTC) NRST pin level */
#परिभाषय AT91C_RSTC_SRCMP                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 17 )  /* (RSTC) Software Reset Command in Progress. */
/* -------- RSTC_RMR : (RSTC Offset: 0x8) Reset Mode Register -------- */
#परिभाषय AT91C_RSTC_URSTEN                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )   /* (RSTC) User Reset Enable */
#परिभाषय AT91C_RSTC_URSTIEN                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )   /* (RSTC) User Reset Interrupt Enable */
#परिभाषय AT91C_RSTC_ERSTL                  ( ( अचिह्नित पूर्णाङ्क ) 0xF << 8 )   /* (RSTC) User Reset Enable */
#परिभाषय AT91C_RSTC_BODIEN                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 )  /* (RSTC) Brownout Detection Interrupt Enable */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Real Time Timer Controller Interface */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_RTTC
{
    AT91_REG RTTC_RTMR; /* Real-time Mode Register */
    AT91_REG RTTC_RTAR; /* Real-time Alarm Register */
    AT91_REG RTTC_RTVR; /* Real-time Value Register */
    AT91_REG RTTC_RTSR; /* Real-time Status Register */
} AT91S_RTTC, * AT91PS_RTTC;

/* -------- RTTC_RTMR : (RTTC Offset: 0x0) Real-time Mode Register -------- */
#परिभाषय AT91C_RTTC_RTPRES       ( ( अचिह्नित पूर्णाङ्क ) 0xFFFF << 0 ) /* (RTTC) Real-time Timer Prescaler Value */
#परिभाषय AT91C_RTTC_ALMIEN       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 )   /* (RTTC) Alarm Interrupt Enable */
#परिभाषय AT91C_RTTC_RTTINCIEN    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 17 )   /* (RTTC) Real Time Timer Increment Interrupt Enable */
#परिभाषय AT91C_RTTC_RTTRST       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 18 )   /* (RTTC) Real Time Timer Restart */
/* -------- RTTC_RTAR : (RTTC Offset: 0x4) Real-time Alarm Register -------- */
#परिभाषय AT91C_RTTC_ALMV         ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 0 )    /* (RTTC) Alarm Value */
/* -------- RTTC_RTVR : (RTTC Offset: 0x8) Current Real-time Value Register -------- */
#परिभाषय AT91C_RTTC_CRTV         ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 0 )    /* (RTTC) Current Real-time Value */
/* -------- RTTC_RTSR : (RTTC Offset: 0xc) Real-time Status Register -------- */
#परिभाषय AT91C_RTTC_ALMS         ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )    /* (RTTC) Real-time Alarm Status */
#परिभाषय AT91C_RTTC_RTTINC       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )    /* (RTTC) Real-time Timer Increment */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Periodic Interval Timer Controller Interface */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_PITC
{
    AT91_REG PITC_PIMR; /* Period Interval Mode Register */
    AT91_REG PITC_PISR; /* Period Interval Status Register */
    AT91_REG PITC_PIVR; /* Period Interval Value Register */
    AT91_REG PITC_PIIR; /* Period Interval Image Register */
} AT91S_PITC, * AT91PS_PITC;

/* -------- PITC_PIMR : (PITC Offset: 0x0) Periodic Interval Mode Register -------- */
#परिभाषय AT91C_PITC_PIV       ( ( अचिह्नित पूर्णाङ्क ) 0xFFFFF << 0 ) /* (PITC) Periodic Interval Value */
#परिभाषय AT91C_PITC_PITEN     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 24 )    /* (PITC) Periodic Interval Timer Enabled */
#परिभाषय AT91C_PITC_PITIEN    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 25 )    /* (PITC) Periodic Interval Timer Interrupt Enable */
/* -------- PITC_PISR : (PITC Offset: 0x4) Periodic Interval Status Register -------- */
#परिभाषय AT91C_PITC_PITS      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )     /* (PITC) Periodic Interval Timer Status */
/* -------- PITC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register -------- */
#परिभाषय AT91C_PITC_CPIV      ( ( अचिह्नित पूर्णाङ्क ) 0xFFFFF << 0 ) /* (PITC) Current Periodic Interval Value */
#परिभाषय AT91C_PITC_PICNT     ( ( अचिह्नित पूर्णाङ्क ) 0xFFF << 20 )  /* (PITC) Periodic Interval Counter */
/* -------- PITC_PIIR : (PITC Offset: 0xc) Periodic Interval Image Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Watchdog Timer Controller Interface */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_WDTC
{
    AT91_REG WDTC_WDCR; /* Watchdog Control Register */
    AT91_REG WDTC_WDMR; /* Watchdog Mode Register */
    AT91_REG WDTC_WDSR; /* Watchdog Status Register */
} AT91S_WDTC, * AT91PS_WDTC;

/* -------- WDTC_WDCR : (WDTC Offset: 0x0) Periodic Interval Image Register -------- */
#परिभाषय AT91C_WDTC_WDRSTT       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )    /* (WDTC) Watchdog Restart */
#परिभाषय AT91_C_WDTC_कुञ्चिका          ( ( अचिह्नित पूर्णाङ्क ) 0xFF << 24 )  /* (WDTC) Watchdog KEY Password */
/* -------- WDTC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register -------- */
#परिभाषय AT91C_WDTC_WDV          ( ( अचिह्नित पूर्णाङ्क ) 0xFFF << 0 )  /* (WDTC) Watchdog Timer Restart */
#परिभाषय AT91C_WDTC_WDFIEN       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 12 )   /* (WDTC) Watchdog Fault Interrupt Enable */
#परिभाषय AT91C_WDTC_WDRSTEN      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 13 )   /* (WDTC) Watchdog Reset Enable */
#परिभाषय AT91C_WDTC_WDRPROC      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 14 )   /* (WDTC) Watchdog Timer Restart */
#परिभाषय AT91C_WDTC_WDDIS        ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 15 )   /* (WDTC) Watchdog Disable */
#परिभाषय AT91C_WDTC_WDD          ( ( अचिह्नित पूर्णाङ्क ) 0xFFF << 16 ) /* (WDTC) Watchdog Delta Value */
#परिभाषय AT91C_WDTC_WDDBGHLT     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 28 )   /* (WDTC) Watchdog Debug Halt */
#परिभाषय AT91C_WDTC_WDIDLEHLT    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 29 )   /* (WDTC) Watchdog Idle Halt */
/* -------- WDTC_WDSR : (WDTC Offset: 0x8) Watchdog Status Register -------- */
#परिभाषय AT91C_WDTC_WDUNF        ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )    /* (WDTC) Watchdog Underflow */
#परिभाषय AT91C_WDTC_WDERR        ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )    /* (WDTC) Watchdog Error */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Voltage Regulator Mode Controller Interface */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_VREG
{
    AT91_REG VREG_MR; /* Voltage Regulator Mode Register */
} AT91S_VREG, * AT91PS_VREG;

/* -------- VREG_MR : (VREG Offset: 0x0) Voltage Regulator Mode Register -------- */
#परिभाषय AT91C_VREG_PSTDBY    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 ) /* (VREG) Voltage Regulator Power Standby Mode */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Memory Controller Interface */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_MC
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
#परिभाषय AT91C_MC_RCB                       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )   /* (MC) Remap Command Bit */
/* -------- MC_ASR : (MC Offset: 0x4) MC Abort Status Register -------- */
#परिभाषय AT91C_MC_UNDADD                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )   /* (MC) Undefined Address Abort Status */
#परिभाषय AT91C_MC_MISADD                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )   /* (MC) Misaligned Address Abort Status */
#परिभाषय AT91C_MC_ABTSZ                     ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 8 )   /* (MC) Abort Size Status */
#परिभाषय     AT91C_MC_ABTSZ_BYTE            ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 8 )   /* (MC) Byte */
#परिभाषय     AT91C_MC_ABTSZ_HWORD           ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )   /* (MC) Half-word */
#परिभाषय     AT91C_MC_ABTSZ_WORD            ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 8 )   /* (MC) Word */
#परिभाषय AT91C_MC_ABTTYP                    ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 10 )  /* (MC) Abort Type Status */
#परिभाषय     AT91C_MC_ABTTYP_DATAR          ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 10 )  /* (MC) Data Read */
#परिभाषय     AT91C_MC_ABTTYP_DATAW          ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 10 )  /* (MC) Data Write */
#परिभाषय     AT91C_MC_ABTTYP_FETCH          ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 10 )  /* (MC) Code Fetch */
#परिभाषय AT91C_MC_MST0                      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 )  /* (MC) Master 0 Abort Source */
#परिभाषय AT91C_MC_MST1                      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 17 )  /* (MC) Master 1 Abort Source */
#परिभाषय AT91C_MC_SVMST0                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 24 )  /* (MC) Saved Master 0 Abort Source */
#परिभाषय AT91C_MC_SVMST1                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 25 )  /* (MC) Saved Master 1 Abort Source */
/* -------- MC_FMR : (MC Offset: 0x60) MC Flash Mode Register -------- */
#परिभाषय AT91C_MC_FRDY                      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )   /* (MC) Flash Ready */
#परिभाषय AT91C_MC_LOCKE                     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )   /* (MC) Lock Error */
#परिभाषय AT91C_MC_PROGE                     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )   /* (MC) Programming Error */
#परिभाषय AT91C_MC_NEBP                      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )   /* (MC) No Erase Before Programming */
#परिभाषय AT91C_MC_FWS                       ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 8 )   /* (MC) Flash Wait State */
#परिभाषय     AT91C_MC_FWS_0FWS              ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 8 )   /* (MC) 1 cycle for Read, 2 for Write operations */
#परिभाषय     AT91C_MC_FWS_1FWS              ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )   /* (MC) 2 cycles for Read, 3 for Write operations */
#परिभाषय     AT91C_MC_FWS_2FWS              ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 8 )   /* (MC) 3 cycles for Read, 4 for Write operations */
#परिभाषय     AT91C_MC_FWS_3FWS              ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 8 )   /* (MC) 4 cycles for Read, 4 for Write operations */
#परिभाषय AT91C_MC_FMCN                      ( ( अचिह्नित पूर्णाङ्क ) 0xFF << 16 ) /* (MC) Flash Microsecond Cycle Number */
/* -------- MC_FCR : (MC Offset: 0x64) MC Flash Command Register -------- */
#परिभाषय AT91C_MC_FCMD                      ( ( अचिह्नित पूर्णाङ्क ) 0xF << 0 )   /* (MC) Flash Command */
#परिभाषय     AT91C_MC_FCMD_START_PROG       ( ( अचिह्नित पूर्णाङ्क ) 0x1 )        /* (MC) Starts the programming of th epage specified by PAGEN. */
#परिभाषय     AT91_C_MC_FCMD_तालकम्             ( ( अचिह्नित पूर्णाङ्क ) 0x2 )        /* (MC) Starts a lock sequence of the sector defined by the bits 4 to 7 of the field PAGEN. */
#परिभाषय     AT91_C_MC_FCMD_PROG_AND_तालकम्    ( ( अचिह्नित पूर्णाङ्क ) 0x3 )        /* (MC) The lock sequence automatically happens after the programming sequence is completed. */
#परिभाषय     AT91C_MC_FCMD_UNLOCK           ( ( अचिह्नित पूर्णाङ्क ) 0x4 )        /* (MC) Starts an unlock sequence of the sector defined by the bits 4 to 7 of the field PAGEN. */
#परिभाषय     AT91C_MC_FCMD_ERASE_ALL        ( ( अचिह्नित पूर्णाङ्क ) 0x8 )        /* (MC) Starts the erase of the entire flash.If at least a page is locked, the command is cancelled. */
#परिभाषय     AT91_C_MC_FCMD_समुच्चयः_GP_NVM       ( ( अचिह्नित पूर्णाङ्क ) 0xB )        /* (MC) Set General Purpose NVM bits. */
#परिभाषय     AT91C_MC_FCMD_CLR_GP_NVM       ( ( अचिह्नित पूर्णाङ्क ) 0xD )        /* (MC) Clear General Purpose NVM bits. */
#परिभाषय     AT91_C_MC_FCMD_समुच्चयः_SECURITY     ( ( अचिह्नित पूर्णाङ्क ) 0xF )        /* (MC) Set Security Bit. */
#परिभाषय AT91C_MC_PAGEN                     ( ( अचिह्नित पूर्णाङ्क ) 0x3FF << 8 ) /* (MC) Page Number */
#परिभाषय AT91_C_MC_कुञ्चिका                       ( ( अचिह्नित पूर्णाङ्क ) 0xFF << 24 ) /* (MC) Writing Protect Key */
/* -------- MC_FSR : (MC Offset: 0x68) MC Flash Command Register -------- */
#परिभाषय AT91C_MC_SECURITY                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )   /* (MC) Security Bit Status */
#परिभाषय AT91C_MC_GPNVM0                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )   /* (MC) Sector 0 Lock Status */
#परिभाषय AT91C_MC_GPNVM1                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 9 )   /* (MC) Sector 1 Lock Status */
#परिभाषय AT91C_MC_GPNVM2                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 10 )  /* (MC) Sector 2 Lock Status */
#परिभाषय AT91C_MC_GPNVM3                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 11 )  /* (MC) Sector 3 Lock Status */
#परिभाषय AT91C_MC_GPNVM4                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 12 )  /* (MC) Sector 4 Lock Status */
#परिभाषय AT91C_MC_GPNVM5                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 13 )  /* (MC) Sector 5 Lock Status */
#परिभाषय AT91C_MC_GPNVM6                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 14 )  /* (MC) Sector 6 Lock Status */
#परिभाषय AT91C_MC_GPNVM7                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 15 )  /* (MC) Sector 7 Lock Status */
#परिभाषय AT91C_MC_LOCKS0                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 )  /* (MC) Sector 0 Lock Status */
#परिभाषय AT91C_MC_LOCKS1                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 17 )  /* (MC) Sector 1 Lock Status */
#परिभाषय AT91C_MC_LOCKS2                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 18 )  /* (MC) Sector 2 Lock Status */
#परिभाषय AT91C_MC_LOCKS3                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 19 )  /* (MC) Sector 3 Lock Status */
#परिभाषय AT91C_MC_LOCKS4                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 20 )  /* (MC) Sector 4 Lock Status */
#परिभाषय AT91C_MC_LOCKS5                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 21 )  /* (MC) Sector 5 Lock Status */
#परिभाषय AT91C_MC_LOCKS6                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 22 )  /* (MC) Sector 6 Lock Status */
#परिभाषय AT91C_MC_LOCKS7                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 23 )  /* (MC) Sector 7 Lock Status */
#परिभाषय AT91C_MC_LOCKS8                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 24 )  /* (MC) Sector 8 Lock Status */
#परिभाषय AT91C_MC_LOCKS9                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 25 )  /* (MC) Sector 9 Lock Status */
#परिभाषय AT91C_MC_LOCKS10                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 26 )  /* (MC) Sector 10 Lock Status */
#परिभाषय AT91C_MC_LOCKS11                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 27 )  /* (MC) Sector 11 Lock Status */
#परिभाषय AT91C_MC_LOCKS12                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 28 )  /* (MC) Sector 12 Lock Status */
#परिभाषय AT91C_MC_LOCKS13                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 29 )  /* (MC) Sector 13 Lock Status */
#परिभाषय AT91C_MC_LOCKS14                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 30 )  /* (MC) Sector 14 Lock Status */
#परिभाषय AT91C_MC_LOCKS15                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 31 )  /* (MC) Sector 15 Lock Status */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Serial Parallel Interface */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_SPI
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
#परिभाषय AT91C_SPI_SPIEN              ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )    /* (SPI) SPI Enable */
#परिभाषय AT91C_SPI_SPIDIS             ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )    /* (SPI) SPI Disable */
#परिभाषय AT91C_SPI_SWRST              ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )    /* (SPI) SPI Software reset */
#परिभाषय AT91C_SPI_LASTXFER           ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 24 )   /* (SPI) SPI Last Transfer */
/* -------- SPI_MR : (SPI Offset: 0x4) SPI Mode Register -------- */
#परिभाषय AT91C_SPI_MSTR               ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )    /* (SPI) Master/Slave Mode */
#परिभाषय AT91C_SPI_PS                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )    /* (SPI) Peripheral Select */
#परिभाषय     AT91C_SPI_PS_FIXED       ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 1 )    /* (SPI) Fixed Peripheral Select */
#परिभाषय     AT91C_SPI_PS_VARIABLE    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )    /* (SPI) Variable Peripheral Select */
#परिभाषय AT91C_SPI_PCSDEC             ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )    /* (SPI) Chip Select Decode */
#परिभाषय AT91C_SPI_FDIV               ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )    /* (SPI) Clock Selection */
#परिभाषय AT91C_SPI_MODFDIS            ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )    /* (SPI) Mode Fault Detection */
#परिभाषय AT91C_SPI_LLB                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )    /* (SPI) Clock Selection */
#परिभाषय AT91C_SPI_PCS                ( ( अचिह्नित पूर्णाङ्क ) 0xF << 16 )   /* (SPI) Peripheral Chip Select */
#परिभाषय AT91C_SPI_DLYBCS             ( ( अचिह्नित पूर्णाङ्क ) 0xFF << 24 )  /* (SPI) Delay Between Chip Selects */
/* -------- SPI_RDR : (SPI Offset: 0x8) Receive Data Register -------- */
#परिभाषय AT91C_SPI_RD                 ( ( अचिह्नित पूर्णाङ्क ) 0xFFFF << 0 ) /* (SPI) Receive Data */
#परिभाषय AT91C_SPI_RPCS               ( ( अचिह्नित पूर्णाङ्क ) 0xF << 16 )   /* (SPI) Peripheral Chip Select Status */
/* -------- SPI_TDR : (SPI Offset: 0xc) Transmit Data Register -------- */
#परिभाषय AT91C_SPI_TD                 ( ( अचिह्नित पूर्णाङ्क ) 0xFFFF << 0 ) /* (SPI) Transmit Data */
#परिभाषय AT91C_SPI_TPCS               ( ( अचिह्नित पूर्णाङ्क ) 0xF << 16 )   /* (SPI) Peripheral Chip Select Status */
/* -------- SPI_SR : (SPI Offset: 0x10) Status Register -------- */
#परिभाषय AT91C_SPI_RDRF               ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )    /* (SPI) Receive Data Register Full */
#परिभाषय AT91C_SPI_TDRE               ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )    /* (SPI) Transmit Data Register Empty */
#परिभाषय AT91C_SPI_MODF               ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )    /* (SPI) Mode Fault Error */
#परिभाषय AT91C_SPI_OVRES              ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )    /* (SPI) Overrun Error Status */
#परिभाषय AT91C_SPI_ENDRX              ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )    /* (SPI) End of Receiver Transfer */
#परिभाषय AT91C_SPI_ENDTX              ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 )    /* (SPI) End of Receiver Transfer */
#परिभाषय AT91C_SPI_RXBUFF             ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 6 )    /* (SPI) RXBUFF Interrupt */
#परिभाषय AT91C_SPI_TXBUFE             ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )    /* (SPI) TXBUFE Interrupt */
#परिभाषय AT91C_SPI_NSSR               ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )    /* (SPI) NSSR Interrupt */
#परिभाषय AT91C_SPI_TXEMPTY            ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 9 )    /* (SPI) TXEMPTY Interrupt */
#परिभाषय AT91C_SPI_SPIENS             ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 )   /* (SPI) Enable Status */
/* -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- */
/* -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- */
/* -------- SPI_IMR : (SPI Offset: 0x1c) Interrupt Mask Register -------- */
/* -------- SPI_CSR : (SPI Offset: 0x30) Chip Select Register -------- */
#परिभाषय AT91C_SPI_CPOL           ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )   /* (SPI) Clock Polarity */
#परिभाषय AT91C_SPI_NCPHA          ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )   /* (SPI) Clock Phase */
#परिभाषय AT91C_SPI_CSAAT          ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )   /* (SPI) Chip Select Active After Transfer */
#परिभाषय AT91_C_SPI_द्वयङ्काः           ( ( अचिह्नित पूर्णाङ्क ) 0xF << 4 )   /* (SPI) Bits Per Transfer */
#परिभाषय     AT91_C_SPI_द्वयङ्काः_8     ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 4 )   /* (SPI) 8 Bits Per transfer */
#परिभाषय     AT91_C_SPI_द्वयङ्काः_9     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )   /* (SPI) 9 Bits Per transfer */
#परिभाषय     AT91_C_SPI_द्वयङ्काः_10    ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 4 )   /* (SPI) 10 Bits Per transfer */
#परिभाषय     AT91_C_SPI_द्वयङ्काः_11    ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 4 )   /* (SPI) 11 Bits Per transfer */
#परिभाषय     AT91_C_SPI_द्वयङ्काः_12    ( ( अचिह्नित पूर्णाङ्क ) 0x4 << 4 )   /* (SPI) 12 Bits Per transfer */
#परिभाषय     AT91_C_SPI_द्वयङ्काः_13    ( ( अचिह्नित पूर्णाङ्क ) 0x5 << 4 )   /* (SPI) 13 Bits Per transfer */
#परिभाषय     AT91_C_SPI_द्वयङ्काः_14    ( ( अचिह्नित पूर्णाङ्क ) 0x6 << 4 )   /* (SPI) 14 Bits Per transfer */
#परिभाषय     AT91_C_SPI_द्वयङ्काः_15    ( ( अचिह्नित पूर्णाङ्क ) 0x7 << 4 )   /* (SPI) 15 Bits Per transfer */
#परिभाषय     AT91_C_SPI_द्वयङ्काः_16    ( ( अचिह्नित पूर्णाङ्क ) 0x8 << 4 )   /* (SPI) 16 Bits Per transfer */
#परिभाषय AT91C_SPI_SCBR           ( ( अचिह्नित पूर्णाङ्क ) 0xFF << 8 )  /* (SPI) Serial Clock Baud Rate */
#परिभाषय AT91C_SPI_DLYBS          ( ( अचिह्नित पूर्णाङ्क ) 0xFF << 16 ) /* (SPI) Delay Before SPCK */
#परिभाषय AT91C_SPI_DLYBCT         ( ( अचिह्नित पूर्णाङ्क ) 0xFF << 24 ) /* (SPI) Delay Between Consecutive Transfers */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Usart */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_USART
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
#परिभाषय AT91C_US_STTBRK                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 9 )  /* (USART) Start Break */
#परिभाषय AT91C_US_STPBRK                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 10 ) /* (USART) Stop Break */
#परिभाषय AT91C_US_STTTO                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 11 ) /* (USART) Start Time-out */
#परिभाषय AT91C_US_SENDA                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 12 ) /* (USART) Send Address */
#परिभाषय AT91C_US_RSTIT                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 13 ) /* (USART) Reset Iterations */
#परिभाषय AT91C_US_RSTNACK                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 14 ) /* (USART) Reset Non Acknowledge */
#परिभाषय AT91C_US_RETTO                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 15 ) /* (USART) Rearm Time-out */
#परिभाषय AT91C_US_DTREN                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 ) /* (USART) Data Terminal ready Enable */
#परिभाषय AT91C_US_DTRDIS                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 17 ) /* (USART) Data Terminal ready Disable */
#परिभाषय AT91C_US_RTSEN                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 18 ) /* (USART) Request to Send enable */
#परिभाषय AT91C_US_RTSDIS                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 19 ) /* (USART) Request to Send Disable */
/* -------- US_MR : (USART Offset: 0x4) Debug Unit Mode Register -------- */
#परिभाषय AT91C_US_USMODE                  ( ( अचिह्नित पूर्णाङ्क ) 0xF << 0 )  /* (USART) Usart mode */
#परिभाषय     AT91_C_US_USMODE_प्रसामान्यम्       ( ( अचिह्नित पूर्णाङ्क ) 0x0 )       /* (USART) Normal */
#परिभाषय     AT91C_US_USMODE_RS485        ( ( अचिह्नित पूर्णाङ्क ) 0x1 )       /* (USART) RS485 */
#परिभाषय     AT91C_US_USMODE_HWHSH        ( ( अचिह्नित पूर्णाङ्क ) 0x2 )       /* (USART) Hardware Handshaking */
#परिभाषय     AT91C_US_USMODE_MODEM        ( ( अचिह्नित पूर्णाङ्क ) 0x3 )       /* (USART) Modem */
#परिभाषय     AT91C_US_USMODE_ISO7816_0    ( ( अचिह्नित पूर्णाङ्क ) 0x4 )       /* (USART) ISO7816 protocol: T = 0 */
#परिभाषय     AT91C_US_USMODE_ISO7816_1    ( ( अचिह्नित पूर्णाङ्क ) 0x6 )       /* (USART) ISO7816 protocol: T = 1 */
#परिभाषय     AT91C_US_USMODE_IRDA         ( ( अचिह्नित पूर्णाङ्क ) 0x8 )       /* (USART) IrDA */
#परिभाषय     AT91C_US_USMODE_SWHSH        ( ( अचिह्नित पूर्णाङ्क ) 0xC )       /* (USART) Software Handshaking */
#परिभाषय AT91C_US_CLKS                    ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 4 )  /* (USART) Clock Selection (Baud Rate generator Input Clock */
#परिभाषय     AT91C_US_CLKS_CLOCK          ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 4 )  /* (USART) Clock */
#परिभाषय     AT91C_US_CLKS_FDIV1          ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )  /* (USART) fdiv1 */
#परिभाषय     AT91C_US_CLKS_SLOW           ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 4 )  /* (USART) slow_clock (ARM) */
#परिभाषय     AT91C_US_CLKS_EXT            ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 4 )  /* (USART) External (SCK) */
#परिभाषय AT91C_US_CHRL                    ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 6 )  /* (USART) Clock Selection (Baud Rate generator Input Clock */
#परिभाषय     AT91_C_US_CHRL_5_द्वयङ्काः         ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 6 )  /* (USART) Character Length: 5 bits */
#परिभाषय     AT91_C_US_CHRL_6_द्वयङ्काः         ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 6 )  /* (USART) Character Length: 6 bits */
#परिभाषय     AT91_C_US_CHRL_7_द्वयङ्काः         ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 6 )  /* (USART) Character Length: 7 bits */
#परिभाषय     AT91_C_US_CHRL_8_द्वयङ्काः         ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 6 )  /* (USART) Character Length: 8 bits */
#परिभाषय AT91C_US_SYNC                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )  /* (USART) Synchronous Mode Select */
#परिभाषय AT91C_US_NBSTOP                  ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 12 ) /* (USART) Number of Stop bits */
#परिभाषय     AT91C_US_NBSTOP_1_BIT        ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 12 ) /* (USART) 1 stop bit */
#परिभाषय     AT91C_US_NBSTOP_15_BIT       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 12 ) /* (USART) Asynchronous (SYNC=0) 2 stop bits Synchronous (SYNC=1) 2 stop bits */
#परिभाषय     AT91C_US_NBSTOP_2_BIT        ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 12 ) /* (USART) 2 stop bits */
#परिभाषय AT91C_US_MSBF                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 ) /* (USART) Bit Order */
#परिभाषय AT91C_US_MODE9                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 17 ) /* (USART) 9-bit Character length */
#परिभाषय AT91C_US_CKLO                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 18 ) /* (USART) Clock Output Select */
#परिभाषय AT91C_US_OVER                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 19 ) /* (USART) Over Sampling Mode */
#परिभाषय AT91C_US_INACK                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 20 ) /* (USART) Inhibit Non Acknowledge */
#परिभाषय AT91C_US_DSNACK                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 21 ) /* (USART) Disable Successive NACK */
#परिभाषय AT91C_US_MAX_ITER                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 24 ) /* (USART) Number of Repetitions */
#परिभाषय AT91C_US_FILTER                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 28 ) /* (USART) Receive Line Filter */
/* -------- US_IER : (USART Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
#परिभाषय AT91C_US_RXBRK                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )  /* (USART) Break Received/End of Break */
#परिभाषय AT91C_US_TIMEOUT                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )  /* (USART) Receiver Time-out */
#परिभाषय AT91C_US_ITERATION               ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 10 ) /* (USART) Max number of Repetitions Reached */
#परिभाषय AT91C_US_NACK                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 13 ) /* (USART) Non Acknowledge */
#परिभाषय AT91C_US_RIIC                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 ) /* (USART) Ring INdicator Input Change Flag */
#परिभाषय AT91C_US_DSRIC                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 17 ) /* (USART) Data Set Ready Input Change Flag */
#परिभाषय AT91C_US_DCDIC                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 18 ) /* (USART) Data Carrier Flag */
#परिभाषय AT91C_US_CTSIC                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 19 ) /* (USART) Clear To Send Input Change Flag */
/* -------- US_IDR : (USART Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* -------- US_IMR : (USART Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* -------- US_CSR : (USART Offset: 0x14) Debug Unit Channel Status Register -------- */
#परिभाषय AT91C_US_RI     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 20 )   /* (USART) Image of RI Input */
#परिभाषय AT91C_US_DSR    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 21 )   /* (USART) Image of DSR Input */
#परिभाषय AT91C_US_DCD    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 22 )   /* (USART) Image of DCD Input */
#परिभाषय AT91C_US_CTS    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 23 )   /* (USART) Image of CTS Input */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Synchronous Serial Controller Interface */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_SSC
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
#परिभाषय AT91C_SSC_RXEN                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )   /* (SSC) Receive Enable */
#परिभाषय AT91C_SSC_RXDIS                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )   /* (SSC) Receive Disable */
#परिभाषय AT91C_SSC_TXEN                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )   /* (SSC) Transmit Enable */
#परिभाषय AT91C_SSC_TXDIS                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 9 )   /* (SSC) Transmit Disable */
#परिभाषय AT91C_SSC_SWRST                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 15 )  /* (SSC) Software Reset */
/* -------- SSC_RCMR : (SSC Offset: 0x10) SSC Receive Clock Mode Register -------- */
#परिभाषय AT91C_SSC_CKS                     ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 0 )   /* (SSC) Receive/Transmit Clock Selection */
#परिभाषय     AT91C_SSC_CKS_DIV             ( ( अचिह्नित पूर्णाङ्क ) 0x0 )        /* (SSC) Divided Clock */
#परिभाषय     AT91C_SSC_CKS_TK              ( ( अचिह्नित पूर्णाङ्क ) 0x1 )        /* (SSC) TK Clock signal */
#परिभाषय     AT91C_SSC_CKS_RK              ( ( अचिह्नित पूर्णाङ्क ) 0x2 )        /* (SSC) RK pin */
#परिभाषय AT91C_SSC_CKO                     ( ( अचिह्नित पूर्णाङ्क ) 0x7 << 2 )   /* (SSC) Receive/Transmit Clock Output Mode Selection */
#परिभाषय     AT91C_SSC_CKO_NONE            ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 2 )   /* (SSC) Receive/Transmit Clock Output Mode: None RK pin: Input-only */
#परिभाषय     AT91C_SSC_CKO_CONTINUOUS      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )   /* (SSC) Continuous Receive/Transmit Clock RK pin: Output */
#परिभाषय     AT91_C_SSC_CKO_दत्त_TX         ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 2 )   /* (SSC) Receive/Transmit Clock only during data transfers RK pin: Output */
#परिभाषय AT91C_SSC_CKI                     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 )   /* (SSC) Receive/Transmit Clock Inversion */
#परिभाषय AT91C_SSC_START                   ( ( अचिह्नित पूर्णाङ्क ) 0xF << 8 )   /* (SSC) Receive/Transmit Start Selection */
#परिभाषय     AT91C_SSC_START_CONTINUOUS    ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 8 )   /* (SSC) Continuous, as soon as the receiver is enabled, and immediately after the end of transfer of the previous data. */
#परिभाषय     AT91C_SSC_START_TX            ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )   /* (SSC) Transmit/Receive start */
#परिभाषय     AT91_C_SSC_START_नीचः_RF        ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 8 )   /* (SSC) Detection of a low level on RF input */
#परिभाषय     AT91_C_SSC_START_उच्चः_RF       ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 8 )   /* (SSC) Detection of a high level on RF input */
#परिभाषय     AT91C_SSC_START_FALL_RF       ( ( अचिह्नित पूर्णाङ्क ) 0x4 << 8 )   /* (SSC) Detection of a falling edge on RF input */
#परिभाषय     AT91C_SSC_START_RISE_RF       ( ( अचिह्नित पूर्णाङ्क ) 0x5 << 8 )   /* (SSC) Detection of a rising edge on RF input */
#परिभाषय     AT91C_SSC_START_LEVEL_RF      ( ( अचिह्नित पूर्णाङ्क ) 0x6 << 8 )   /* (SSC) Detection of any level change on RF input */
#परिभाषय     AT91C_SSC_START_EDGE_RF       ( ( अचिह्नित पूर्णाङ्क ) 0x7 << 8 )   /* (SSC) Detection of any edge on RF input */
#परिभाषय     AT91C_SSC_START_0             ( ( अचिह्नित पूर्णाङ्क ) 0x8 << 8 )   /* (SSC) Compare 0 */
#परिभाषय AT91C_SSC_STTDLY                  ( ( अचिह्नित पूर्णाङ्क ) 0xFF << 16 ) /* (SSC) Receive/Transmit Start Delay */
#परिभाषय AT91C_SSC_PERIOD                  ( ( अचिह्नित पूर्णाङ्क ) 0xFF << 24 ) /* (SSC) Receive/Transmit Period Divider Selection */
/* -------- SSC_RFMR : (SSC Offset: 0x14) SSC Receive Frame Mode Register -------- */
#परिभाषय AT91C_SSC_DATLEN                  ( ( अचिह्नित पूर्णाङ्क ) 0x1F << 0 )  /* (SSC) Data Length */
#परिभाषय AT91C_SSC_LOOP                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 )   /* (SSC) Loop Mode */
#परिभाषय AT91C_SSC_MSBF                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )   /* (SSC) Most Significant Bit First */
#परिभाषय AT91C_SSC_DATNB                   ( ( अचिह्नित पूर्णाङ्क ) 0xF << 8 )   /* (SSC) Data Number per Frame */
#परिभाषय AT91C_SSC_FSLEN                   ( ( अचिह्नित पूर्णाङ्क ) 0xF << 16 )  /* (SSC) Receive/Transmit Frame Sync length */
#परिभाषय AT91C_SSC_FSOS                    ( ( अचिह्नित पूर्णाङ्क ) 0x7 << 20 )  /* (SSC) Receive/Transmit Frame Sync Output Selection */
#परिभाषय     AT91C_SSC_FSOS_NONE           ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: None RK pin Input-only */
#परिभाषय     AT91C_SSC_FSOS_NEGATIVE       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Negative Pulse */
#परिभाषय     AT91_C_SSC_FSOS_धनात्मकम्       ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Positive Pulse */
#परिभाषय     AT91_C_SSC_FSOS_नीचः            ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Driver Low during data transfer */
#परिभाषय     AT91_C_SSC_FSOS_उच्चः           ( ( अचिह्नित पूर्णाङ्क ) 0x4 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Driver High during data transfer */
#परिभाषय     AT91C_SSC_FSOS_TOGGLE         ( ( अचिह्नित पूर्णाङ्क ) 0x5 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Toggling at each start of data transfer */
#परिभाषय AT91C_SSC_FSEDGE                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 24 )  /* (SSC) Frame Sync Edge Detection */
/* -------- SSC_TCMR : (SSC Offset: 0x18) SSC Transmit Clock Mode Register -------- */
/* -------- SSC_TFMR : (SSC Offset: 0x1c) SSC Transmit Frame Mode Register -------- */
#परिभाषय AT91C_SSC_DATDEF                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 )  /* (SSC) Data Default Value */
#परिभाषय AT91C_SSC_FSDEN                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 23 ) /* (SSC) Frame Sync Data Enable */
/* -------- SSC_SR : (SSC Offset: 0x40) SSC Status Register -------- */
#परिभाषय AT91C_SSC_TXRDY                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )  /* (SSC) Transmit Ready */
#परिभाषय AT91C_SSC_TXEMPTY                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )  /* (SSC) Transmit Empty */
#परिभाषय AT91C_SSC_ENDTX                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )  /* (SSC) End Of Transmission */
#परिभाषय AT91C_SSC_TXBUFE                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )  /* (SSC) Transmit Buffer Empty */
#परिभाषय AT91C_SSC_RXRDY                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )  /* (SSC) Receive Ready */
#परिभाषय AT91C_SSC_OVRUN                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 )  /* (SSC) Receive Overrun */
#परिभाषय AT91C_SSC_ENDRX                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 6 )  /* (SSC) End of Reception */
#परिभाषय AT91C_SSC_RXBUFF                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )  /* (SSC) Receive Buffer Full */
#परिभाषय AT91C_SSC_TXSYN                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 10 ) /* (SSC) Transmit Sync */
#परिभाषय AT91C_SSC_RXSYN                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 11 ) /* (SSC) Receive Sync */
#परिभाषय AT91C_SSC_TXENA                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 ) /* (SSC) Transmit Enable */
#परिभाषय AT91C_SSC_RXENA                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 17 ) /* (SSC) Receive Enable */
/* -------- SSC_IER : (SSC Offset: 0x44) SSC Interrupt Enable Register -------- */
/* -------- SSC_IDR : (SSC Offset: 0x48) SSC Interrupt Disable Register -------- */
/* -------- SSC_IMR : (SSC Offset: 0x4c) SSC Interrupt Mask Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Two-wire Interface */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_TWI
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
#परिभाषय AT91C_TWI_START                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )   /* (TWI) Send a START Condition */
#परिभाषय AT91C_TWI_STOP                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )   /* (TWI) Send a STOP Condition */
#परिभाषय AT91C_TWI_MSEN                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )   /* (TWI) TWI Master Transfer Enabled */
#परिभाषय AT91C_TWI_MSDIS                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )   /* (TWI) TWI Master Transfer Disabled */
#परिभाषय AT91C_TWI_SWRST                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )   /* (TWI) Software Reset */
/* -------- TWI_MMR : (TWI Offset: 0x4) TWI Master Mode Register -------- */
#परिभाषय AT91C_TWI_IADRSZ               ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 8 )   /* (TWI) Internal Device Address Size */
#परिभाषय     AT91C_TWI_IADRSZ_NO        ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 8 )   /* (TWI) No internal device address */
#परिभाषय     AT91C_TWI_IADRSZ_1_BYTE    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )   /* (TWI) One-byte internal device address */
#परिभाषय     AT91C_TWI_IADRSZ_2_BYTE    ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 8 )   /* (TWI) Two-byte internal device address */
#परिभाषय     AT91C_TWI_IADRSZ_3_BYTE    ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 8 )   /* (TWI) Three-byte internal device address */
#परिभाषय AT91C_TWI_MREAD                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 12 )  /* (TWI) Master Read Direction */
#परिभाषय AT91C_TWI_DADR                 ( ( अचिह्नित पूर्णाङ्क ) 0x7F << 16 ) /* (TWI) Device Address */
/* -------- TWI_CWGR : (TWI Offset: 0x10) TWI Clock Waveform Generator Register -------- */
#परिभाषय AT91C_TWI_CLDIV                ( ( अचिह्नित पूर्णाङ्क ) 0xFF << 0 )  /* (TWI) Clock Low Divider */
#परिभाषय AT91C_TWI_CHDIV                ( ( अचिह्नित पूर्णाङ्क ) 0xFF << 8 )  /* (TWI) Clock High Divider */
#परिभाषय AT91C_TWI_CKDIV                ( ( अचिह्नित पूर्णाङ्क ) 0x7 << 16 )  /* (TWI) Clock Divider */
/* -------- TWI_SR : (TWI Offset: 0x20) TWI Status Register -------- */
#परिभाषय AT91C_TWI_TXCOMP               ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )   /* (TWI) Transmission Completed */
#परिभाषय AT91C_TWI_RXRDY                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )   /* (TWI) Receive holding register ReaDY */
#परिभाषय AT91C_TWI_TXRDY                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )   /* (TWI) Transmit holding register ReaDY */
#परिभाषय AT91C_TWI_OVRE                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 6 )   /* (TWI) Overrun Error */
#परिभाषय AT91C_TWI_UNRE                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )   /* (TWI) Underrun Error */
#परिभाषय AT91C_TWI_NACK                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )   /* (TWI) Not Acknowledged */
/* -------- TWI_IER : (TWI Offset: 0x24) TWI Interrupt Enable Register -------- */
/* -------- TWI_IDR : (TWI Offset: 0x28) TWI Interrupt Disable Register -------- */
/* -------- TWI_IMR : (TWI Offset: 0x2c) TWI Interrupt Mask Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR PWMC Channel Interface */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_PWMC_CH
{
    AT91_REG PWMC_CMR;           /* Channel Mode Register */
    AT91_REG PWMC_CDTYR;         /* Channel Duty Cycle Register */
    AT91_REG PWMC_CPRDR;         /* Channel Period Register */
    AT91_REG PWMC_CCNTR;         /* Channel Counter Register */
    AT91_REG PWMC_CUPDR;         /* Channel Update Register */
    AT91_REG PWMC_Reserved[ 3 ]; /* Reserved */
} AT91S_PWMC_CH, * AT91PS_PWMC_CH;

/* -------- PWMC_CMR : (PWMC_CH Offset: 0x0) PWMC Channel Mode Register -------- */
#परिभाषय AT91C_PWMC_CPRE             ( ( अचिह्नित पूर्णाङ्क ) 0xF << 0 )  /* (PWMC_CH) Channel Pre-scaler : PWMC_CLKx */
#परिभाषय     AT91C_PWMC_CPRE_MCK     ( ( अचिह्नित पूर्णाङ्क ) 0x0 )       /* (PWMC_CH) */
#परिभाषय     AT91C_PWMC_CPRE_MCKA    ( ( अचिह्नित पूर्णाङ्क ) 0xB )       /* (PWMC_CH) */
#परिभाषय     AT91C_PWMC_CPRE_MCKB    ( ( अचिह्नित पूर्णाङ्क ) 0xC )       /* (PWMC_CH) */
#परिभाषय AT91C_PWMC_CALG             ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )  /* (PWMC_CH) Channel Alignment */
#परिभाषय AT91C_PWMC_CPOL             ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 9 )  /* (PWMC_CH) Channel Polarity */
#परिभाषय AT91C_PWMC_CPD              ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 10 ) /* (PWMC_CH) Channel Update Period */
/* -------- PWMC_CDTYR : (PWMC_CH Offset: 0x4) PWMC Channel Duty Cycle Register -------- */
#परिभाषय AT91C_PWMC_CDTY             ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 0 )  /* (PWMC_CH) Channel Duty Cycle */
/* -------- PWMC_CPRDR : (PWMC_CH Offset: 0x8) PWMC Channel Period Register -------- */
#परिभाषय AT91C_PWMC_CPRD             ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 0 )  /* (PWMC_CH) Channel Period */
/* -------- PWMC_CCNTR : (PWMC_CH Offset: 0xc) PWMC Channel Counter Register -------- */
#परिभाषय AT91C_PWMC_CCNT             ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 0 )  /* (PWMC_CH) Channel Counter */
/* -------- PWMC_CUPDR : (PWMC_CH Offset: 0x10) PWMC Channel Update Register -------- */
#परिभाषय AT91C_PWMC_CUPD             ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 0 )  /* (PWMC_CH) Channel Update */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Pulse Width Modulation Controller Interface */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_PWMC
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
#परिभाषय AT91C_PWMC_DIVA            ( ( अचिह्नित पूर्णाङ्क ) 0xFF << 0 )  /* (PWMC) CLKA divide factor. */
#परिभाषय AT91C_PWMC_PREA            ( ( अचिह्नित पूर्णाङ्क ) 0xF << 8 )   /* (PWMC) Divider Input Clock Prescaler A */
#परिभाषय     AT91C_PWMC_PREA_MCK    ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 8 )   /* (PWMC) */
#परिभाषय AT91C_PWMC_DIVB            ( ( अचिह्नित पूर्णाङ्क ) 0xFF << 16 ) /* (PWMC) CLKB divide factor. */
#परिभाषय AT91C_PWMC_PREB            ( ( अचिह्नित पूर्णाङ्क ) 0xF << 24 )  /* (PWMC) Divider Input Clock Prescaler B */
#परिभाषय     AT91C_PWMC_PREB_MCK    ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 24 )  /* (PWMC) */
/* -------- PWMC_ENA : (PWMC Offset: 0x4) PWMC Enable Register -------- */
#परिभाषय AT91C_PWMC_CHID0           ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )   /* (PWMC) Channel ID 0 */
#परिभाषय AT91C_PWMC_CHID1           ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )   /* (PWMC) Channel ID 1 */
#परिभाषय AT91C_PWMC_CHID2           ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )   /* (PWMC) Channel ID 2 */
#परिभाषय AT91C_PWMC_CHID3           ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )   /* (PWMC) Channel ID 3 */
/* -------- PWMC_DIS : (PWMC Offset: 0x8) PWMC Disable Register -------- */
/* -------- PWMC_SR : (PWMC Offset: 0xc) PWMC Status Register -------- */
/* -------- PWMC_IER : (PWMC Offset: 0x10) PWMC Interrupt Enable Register -------- */
/* -------- PWMC_IDR : (PWMC Offset: 0x14) PWMC Interrupt Disable Register -------- */
/* -------- PWMC_IMR : (PWMC Offset: 0x18) PWMC Interrupt Mask Register -------- */
/* -------- PWMC_ISR : (PWMC Offset: 0x1c) PWMC Interrupt Status Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR USB Device Interface */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_UDP
{
    AT91_REG UDP_अङ्कः;        /* Frame Number Register */
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
#परिभाषय AT91_C_UDP_FRM_अङ्कः    ( ( अचिह्नित पूर्णाङ्क ) 0x7FF << 0 ) /* (UDP) Frame Number as Defined in the Packet Field Formats */
#परिभाषय AT91C_UDP_FRM_ERR    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 )  /* (UDP) Frame Error */
#परिभाषय AT91C_UDP_FRM_OK     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 17 )  /* (UDP) Frame OK */
/* -------- UDP_GLB_STATE : (UDP Offset: 0x4) USB Global State Register -------- */
#परिभाषय AT91C_UDP_FADDEN     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )   /* (UDP) Function Address Enable */
#परिभाषय AT91C_UDP_CONFG      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )   /* (UDP) Configured */
#परिभाषय AT91C_UDP_ESR        ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )   /* (UDP) Enable Send Resume */
#परिभाषय AT91C_UDP_RSMINPR    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )   /* (UDP) A Resume Has Been Sent to the Host */
#परिभाषय AT91C_UDP_RMWUPE     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )   /* (UDP) Remote Wake Up Enable */
/* -------- UDP_FADDR : (UDP Offset: 0x8) USB Function Address Register -------- */
#परिभाषय AT91C_UDP_FADD       ( ( अचिह्नित पूर्णाङ्क ) 0xFF << 0 )  /* (UDP) Function Address Value */
#परिभाषय AT91C_UDP_FEN        ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )   /* (UDP) Function Enable */
/* -------- UDP_IER : (UDP Offset: 0x10) USB Interrupt Enable Register -------- */
#परिभाषय AT91C_UDP_EPINT0     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )   /* (UDP) Endpoint 0 Interrupt */
#परिभाषय AT91C_UDP_EPINT1     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )   /* (UDP) Endpoint 0 Interrupt */
#परिभाषय AT91C_UDP_EPINT2     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )   /* (UDP) Endpoint 2 Interrupt */
#परिभाषय AT91C_UDP_EPINT3     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )   /* (UDP) Endpoint 3 Interrupt */
#परिभाषय AT91C_UDP_EPINT4     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )   /* (UDP) Endpoint 4 Interrupt */
#परिभाषय AT91C_UDP_EPINT5     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 )   /* (UDP) Endpoint 5 Interrupt */
#परिभाषय AT91C_UDP_RXSUSP     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )   /* (UDP) USB Suspend Interrupt */
#परिभाषय AT91C_UDP_RXRSM      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 9 )   /* (UDP) USB Resume Interrupt */
#परिभाषय AT91C_UDP_EXTRSM     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 10 )  /* (UDP) USB External Resume Interrupt */
#परिभाषय AT91C_UDP_SOFINT     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 11 )  /* (UDP) USB Start Of frame Interrupt */
#परिभाषय AT91C_UDP_WAKEUP     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 13 )  /* (UDP) USB Resume Interrupt */
/* -------- UDP_IDR : (UDP Offset: 0x14) USB Interrupt Disable Register -------- */
/* -------- UDP_IMR : (UDP Offset: 0x18) USB Interrupt Mask Register -------- */
/* -------- UDP_ISR : (UDP Offset: 0x1c) USB Interrupt Status Register -------- */
#परिभाषय AT91C_UDP_ENDBUSRES              ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 12 ) /* (UDP) USB End Of Bus Reset Interrupt */
/* -------- UDP_ICR : (UDP Offset: 0x20) USB Interrupt Clear Register -------- */
/* -------- UDP_RST_EP : (UDP Offset: 0x28) USB Reset Endpoint Register -------- */
#परिभाषय AT91C_UDP_EP0                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )    /* (UDP) Reset Endpoint 0 */
#परिभाषय AT91C_UDP_EP1                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )    /* (UDP) Reset Endpoint 1 */
#परिभाषय AT91C_UDP_EP2                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )    /* (UDP) Reset Endpoint 2 */
#परिभाषय AT91C_UDP_EP3                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )    /* (UDP) Reset Endpoint 3 */
#परिभाषय AT91C_UDP_EP4                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )    /* (UDP) Reset Endpoint 4 */
#परिभाषय AT91C_UDP_EP5                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 )    /* (UDP) Reset Endpoint 5 */
/* -------- UDP_CSR : (UDP Offset: 0x30) USB Endpoint Control and Status Register -------- */
#परिभाषय AT91C_UDP_TXCOMP                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )    /* (UDP) Generates an IN packet with data previously written in the DPR */
#परिभाषय AT91_C_UDP_RX_दत्त_BK0            ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )    /* (UDP) Receive Data Bank 0 */
#परिभाषय AT91C_UDP_RXSETUP                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )    /* (UDP) Sends STALL to the Host (Control endpoints) */
#परिभाषय AT91C_UDP_ISOERROR               ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )    /* (UDP) Isochronous error (Isochronous endpoints) */
#परिभाषय AT91C_UDP_TXPKTRDY               ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )    /* (UDP) Transmit Packet Ready */
#परिभाषय AT91C_UDP_FORCESTALL             ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 )    /* (UDP) Force Stall (used by Control, Bulk and Isochronous endpoints). */
#परिभाषय AT91_C_UDP_RX_दत्त_BK1            ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 6 )    /* (UDP) Receive Data Bank 1 (only used by endpoints with ping-pong attributes). */
#परिभाषय AT91C_UDP_DIR                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )    /* (UDP) Transfer Direction */
#परिभाषय AT91C_UDP_EPTYPE                 ( ( अचिह्नित पूर्णाङ्क ) 0x7 << 8 )    /* (UDP) Endpoint type */
#परिभाषय     AT91C_UDP_EPTYPE_CTRL        ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 8 )    /* (UDP) Control */
#परिभाषय     AT91_C_UDP_EPTYPE_ISO_बहिर्गमनम्     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )    /* (UDP) Isochronous OUT */
#परिभाषय     AT91_C_UDP_EPTYPE_BULK_बहिर्गमनम्    ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 8 )    /* (UDP) Bulk OUT */
#परिभाषय     AT91_C_UDP_EPTYPE_INT_बहिर्गमनम्     ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 8 )    /* (UDP) Interrupt OUT */
#परिभाषय     AT91_C_UDP_EPTYPE_ISO_अन्तर्      ( ( अचिह्नित पूर्णाङ्क ) 0x5 << 8 )    /* (UDP) Isochronous IN */
#परिभाषय     AT91_C_UDP_EPTYPE_BULK_अन्तर्     ( ( अचिह्नित पूर्णाङ्क ) 0x6 << 8 )    /* (UDP) Bulk IN */
#परिभाषय     AT91_C_UDP_EPTYPE_INT_अन्तर्      ( ( अचिह्नित पूर्णाङ्क ) 0x7 << 8 )    /* (UDP) Interrupt IN */
#परिभाषय AT91C_UDP_DTGLE                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 11 )   /* (UDP) Data Toggle */
#परिभाषय AT91C_UDP_EPEDS                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 15 )   /* (UDP) Endpoint Enable Disable */
#परिभाषय AT91C_UDP_RXBYTECNT              ( ( अचिह्नित पूर्णाङ्क ) 0x7FF << 16 ) /* (UDP) Number Of Bytes Available in the FIFO */
/* -------- UDP_TXVC : (UDP Offset: 0x74) Transceiver Control Register -------- */
#परिभाषय AT91C_UDP_TXVDIS                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )    /* (UDP) */
#परिभाषय AT91C_UDP_PUON                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 9 )    /* (UDP) Pull-up ON */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Timer Counter Channel Interface */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_TC
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
#परिभाषय AT91C_TC_CLKEN                        ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )  /* (TC) Counter Clock Enable Command */
#परिभाषय AT91C_TC_CLKDIS                       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )  /* (TC) Counter Clock Disable Command */
#परिभाषय AT91C_TC_SWTRG                        ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )  /* (TC) Software Trigger Command */
/* -------- TC_CMR : (TC Offset: 0x4) TC Channel Mode Register: Capture Mode / Waveform Mode -------- */
#परिभाषय AT91C_TC_CLKS                         ( ( अचिह्नित पूर्णाङ्क ) 0x7 << 0 )  /* (TC) Clock Selection */
#परिभाषय     AT91C_TC_CLKS_TIMER_DIV1_CLOCK    ( ( अचिह्नित पूर्णाङ्क ) 0x0 )       /* (TC) Clock selected: TIMER_DIV1_CLOCK */
#परिभाषय     AT91C_TC_CLKS_TIMER_DIV2_CLOCK    ( ( अचिह्नित पूर्णाङ्क ) 0x1 )       /* (TC) Clock selected: TIMER_DIV2_CLOCK */
#परिभाषय     AT91C_TC_CLKS_TIMER_DIV3_CLOCK    ( ( अचिह्नित पूर्णाङ्क ) 0x2 )       /* (TC) Clock selected: TIMER_DIV3_CLOCK */
#परिभाषय     AT91C_TC_CLKS_TIMER_DIV4_CLOCK    ( ( अचिह्नित पूर्णाङ्क ) 0x3 )       /* (TC) Clock selected: TIMER_DIV4_CLOCK */
#परिभाषय     AT91C_TC_CLKS_TIMER_DIV5_CLOCK    ( ( अचिह्नित पूर्णाङ्क ) 0x4 )       /* (TC) Clock selected: TIMER_DIV5_CLOCK */
#परिभाषय     AT91C_TC_CLKS_XC0                 ( ( अचिह्नित पूर्णाङ्क ) 0x5 )       /* (TC) Clock selected: XC0 */
#परिभाषय     AT91C_TC_CLKS_XC1                 ( ( अचिह्नित पूर्णाङ्क ) 0x6 )       /* (TC) Clock selected: XC1 */
#परिभाषय     AT91C_TC_CLKS_XC2                 ( ( अचिह्नित पूर्णाङ्क ) 0x7 )       /* (TC) Clock selected: XC2 */
#परिभाषय AT91C_TC_CLKI                         ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )  /* (TC) Clock Invert */
#परिभाषय AT91C_TC_BURST                        ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 4 )  /* (TC) Burst Signal Selection */
#परिभाषय     AT91C_TC_BURST_NONE               ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 4 )  /* (TC) The clock is not gated by an external signal */
#परिभाषय     AT91C_TC_BURST_XC0                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )  /* (TC) XC0 is ANDed with the selected clock */
#परिभाषय     AT91C_TC_BURST_XC1                ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 4 )  /* (TC) XC1 is ANDed with the selected clock */
#परिभाषय     AT91C_TC_BURST_XC2                ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 4 )  /* (TC) XC2 is ANDed with the selected clock */
#परिभाषय AT91C_TC_CPCSTOP                      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 6 )  /* (TC) Counter Clock Stopped with RC Compare */
#परिभाषय AT91C_TC_LDBSTOP                      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 6 )  /* (TC) Counter Clock Stopped with RB Loading */
#परिभाषय AT91C_TC_CPCDIS                       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )  /* (TC) Counter Clock Disable with RC Compare */
#परिभाषय AT91C_TC_LDBDIS                       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )  /* (TC) Counter Clock Disabled with RB Loading */
#परिभाषय AT91C_TC_ETRGEDG                      ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 8 )  /* (TC) External Trigger Edge Selection */
#परिभाषय     AT91C_TC_ETRGEDG_NONE             ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 8 )  /* (TC) Edge: None */
#परिभाषय     AT91C_TC_ETRGEDG_RISING           ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )  /* (TC) Edge: rising edge */
#परिभाषय     AT91C_TC_ETRGEDG_FALLING          ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 8 )  /* (TC) Edge: falling edge */
#परिभाषय     AT91C_TC_ETRGEDG_BOTH             ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 8 )  /* (TC) Edge: each edge */
#परिभाषय AT91C_TC_EEVTEDG                      ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 8 )  /* (TC) External Event Edge Selection */
#परिभाषय     AT91C_TC_EEVTEDG_NONE             ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 8 )  /* (TC) Edge: None */
#परिभाषय     AT91C_TC_EEVTEDG_RISING           ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )  /* (TC) Edge: rising edge */
#परिभाषय     AT91C_TC_EEVTEDG_FALLING          ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 8 )  /* (TC) Edge: falling edge */
#परिभाषय     AT91C_TC_EEVTEDG_BOTH             ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 8 )  /* (TC) Edge: each edge */
#परिभाषय AT91C_TC_EEVT                         ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 10 ) /* (TC) External Event  Selection */
#परिभाषय     AT91C_TC_EEVT_TIOB                ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 10 ) /* (TC) Signal selected as external event: TIOB TIOB direction: input */
#परिभाषय     AT91C_TC_EEVT_XC0                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 10 ) /* (TC) Signal selected as external event: XC0 TIOB direction: output */
#परिभाषय     AT91C_TC_EEVT_XC1                 ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 10 ) /* (TC) Signal selected as external event: XC1 TIOB direction: output */
#परिभाषय     AT91C_TC_EEVT_XC2                 ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 10 ) /* (TC) Signal selected as external event: XC2 TIOB direction: output */
#परिभाषय AT91C_TC_ABETRG                       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 10 ) /* (TC) TIOA or TIOB External Trigger Selection */
#परिभाषय AT91C_TC_ENETRG                       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 12 ) /* (TC) External Event Trigger enable */
#परिभाषय AT91C_TC_WAVESEL                      ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 13 ) /* (TC) Waveform  Selection */
#परिभाषय     AT91_C_TC_WAVESEL_ऊर्ध्वम्               ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 13 ) /* (TC) UP mode without atomatic trigger on RC Compare */
#परिभाषय     AT91C_TC_WAVESEL_UPDOWN           ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 13 ) /* (TC) UPDOWN mode without automatic trigger on RC Compare */
#परिभाषय     AT91_C_TC_WAVESEL_ऊर्ध्वम्_AUTO          ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 13 ) /* (TC) UP mode with automatic trigger on RC Compare */
#परिभाषय     AT91C_TC_WAVESEL_UPDOWN_AUTO      ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 13 ) /* (TC) UPDOWN mode with automatic trigger on RC Compare */
#परिभाषय AT91C_TC_CPCTRG                       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 14 ) /* (TC) RC Compare Trigger Enable */
#परिभाषय AT91C_TC_WAVE                         ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 15 ) /* (TC) */
#परिभाषय AT91C_TC_ACPA                         ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 16 ) /* (TC) RA Compare Effect on TIOA */
#परिभाषय     AT91C_TC_ACPA_NONE                ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 16 ) /* (TC) Effect: none */
#परिभाषय     AT91_C_TC_ACPA_समुच्चयः                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 ) /* (TC) Effect: set */
#परिभाषय     AT91C_TC_ACPA_CLEAR               ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 16 ) /* (TC) Effect: clear */
#परिभाषय     AT91C_TC_ACPA_TOGGLE              ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 16 ) /* (TC) Effect: toggle */
#परिभाषय AT91C_TC_LDRA                         ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 16 ) /* (TC) RA Loading Selection */
#परिभाषय     AT91C_TC_LDRA_NONE                ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 16 ) /* (TC) Edge: None */
#परिभाषय     AT91C_TC_LDRA_RISING              ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 ) /* (TC) Edge: rising edge of TIOA */
#परिभाषय     AT91C_TC_LDRA_FALLING             ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 16 ) /* (TC) Edge: falling edge of TIOA */
#परिभाषय     AT91C_TC_LDRA_BOTH                ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 16 ) /* (TC) Edge: each edge of TIOA */
#परिभाषय AT91C_TC_ACPC                         ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 18 ) /* (TC) RC Compare Effect on TIOA */
#परिभाषय     AT91C_TC_ACPC_NONE                ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 18 ) /* (TC) Effect: none */
#परिभाषय     AT91_C_TC_ACPC_समुच्चयः                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 18 ) /* (TC) Effect: set */
#परिभाषय     AT91C_TC_ACPC_CLEAR               ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 18 ) /* (TC) Effect: clear */
#परिभाषय     AT91C_TC_ACPC_TOGGLE              ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 18 ) /* (TC) Effect: toggle */
#परिभाषय AT91C_TC_LDRB                         ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 18 ) /* (TC) RB Loading Selection */
#परिभाषय     AT91C_TC_LDRB_NONE                ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 18 ) /* (TC) Edge: None */
#परिभाषय     AT91C_TC_LDRB_RISING              ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 18 ) /* (TC) Edge: rising edge of TIOA */
#परिभाषय     AT91C_TC_LDRB_FALLING             ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 18 ) /* (TC) Edge: falling edge of TIOA */
#परिभाषय     AT91C_TC_LDRB_BOTH                ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 18 ) /* (TC) Edge: each edge of TIOA */
#परिभाषय AT91C_TC_AEEVT                        ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 20 ) /* (TC) External Event Effect on TIOA */
#परिभाषय     AT91C_TC_AEEVT_NONE               ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 20 ) /* (TC) Effect: none */
#परिभाषय     AT91_C_TC_AEEVT_समुच्चयः                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 20 ) /* (TC) Effect: set */
#परिभाषय     AT91C_TC_AEEVT_CLEAR              ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 20 ) /* (TC) Effect: clear */
#परिभाषय     AT91C_TC_AEEVT_TOGGLE             ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 20 ) /* (TC) Effect: toggle */
#परिभाषय AT91C_TC_ASWTRG                       ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 22 ) /* (TC) Software Trigger Effect on TIOA */
#परिभाषय     AT91C_TC_ASWTRG_NONE              ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 22 ) /* (TC) Effect: none */
#परिभाषय     AT91_C_TC_ASWTRG_समुच्चयः               ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 22 ) /* (TC) Effect: set */
#परिभाषय     AT91C_TC_ASWTRG_CLEAR             ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 22 ) /* (TC) Effect: clear */
#परिभाषय     AT91C_TC_ASWTRG_TOGGLE            ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 22 ) /* (TC) Effect: toggle */
#परिभाषय AT91C_TC_BCPB                         ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 24 ) /* (TC) RB Compare Effect on TIOB */
#परिभाषय     AT91C_TC_BCPB_NONE                ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 24 ) /* (TC) Effect: none */
#परिभाषय     AT91_C_TC_BCPB_समुच्चयः                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 24 ) /* (TC) Effect: set */
#परिभाषय     AT91C_TC_BCPB_CLEAR               ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 24 ) /* (TC) Effect: clear */
#परिभाषय     AT91C_TC_BCPB_TOGGLE              ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 24 ) /* (TC) Effect: toggle */
#परिभाषय AT91C_TC_BCPC                         ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 26 ) /* (TC) RC Compare Effect on TIOB */
#परिभाषय     AT91C_TC_BCPC_NONE                ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 26 ) /* (TC) Effect: none */
#परिभाषय     AT91_C_TC_BCPC_समुच्चयः                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 26 ) /* (TC) Effect: set */
#परिभाषय     AT91C_TC_BCPC_CLEAR               ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 26 ) /* (TC) Effect: clear */
#परिभाषय     AT91C_TC_BCPC_TOGGLE              ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 26 ) /* (TC) Effect: toggle */
#परिभाषय AT91C_TC_BEEVT                        ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 28 ) /* (TC) External Event Effect on TIOB */
#परिभाषय     AT91C_TC_BEEVT_NONE               ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 28 ) /* (TC) Effect: none */
#परिभाषय     AT91_C_TC_BEEVT_समुच्चयः                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 28 ) /* (TC) Effect: set */
#परिभाषय     AT91C_TC_BEEVT_CLEAR              ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 28 ) /* (TC) Effect: clear */
#परिभाषय     AT91C_TC_BEEVT_TOGGLE             ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 28 ) /* (TC) Effect: toggle */
#परिभाषय AT91C_TC_BSWTRG                       ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 30 ) /* (TC) Software Trigger Effect on TIOB */
#परिभाषय     AT91C_TC_BSWTRG_NONE              ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 30 ) /* (TC) Effect: none */
#परिभाषय     AT91_C_TC_BSWTRG_समुच्चयः               ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 30 ) /* (TC) Effect: set */
#परिभाषय     AT91C_TC_BSWTRG_CLEAR             ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 30 ) /* (TC) Effect: clear */
#परिभाषय     AT91C_TC_BSWTRG_TOGGLE            ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 30 ) /* (TC) Effect: toggle */
/* -------- TC_SR : (TC Offset: 0x20) TC Channel Status Register -------- */
#परिभाषय AT91C_TC_COVFS                        ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )  /* (TC) Counter Overflow */
#परिभाषय AT91C_TC_LOVRS                        ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )  /* (TC) Load Overrun */
#परिभाषय AT91C_TC_CPAS                         ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )  /* (TC) RA Compare */
#परिभाषय AT91C_TC_CPBS                         ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )  /* (TC) RB Compare */
#परिभाषय AT91C_TC_CPCS                         ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )  /* (TC) RC Compare */
#परिभाषय AT91C_TC_LDRAS                        ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 )  /* (TC) RA Loading */
#परिभाषय AT91C_TC_LDRBS                        ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 6 )  /* (TC) RB Loading */
#परिभाषय AT91C_TC_ETRGS                        ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )  /* (TC) External Trigger */
#परिभाषय AT91C_TC_CLKSTA                       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 ) /* (TC) Clock Enabling */
#परिभाषय AT91C_TC_MTIOA                        ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 17 ) /* (TC) TIOA Mirror */
#परिभाषय AT91C_TC_MTIOB                        ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 18 ) /* (TC) TIOA Mirror */
/* -------- TC_IER : (TC Offset: 0x24) TC Channel Interrupt Enable Register -------- */
/* -------- TC_IDR : (TC Offset: 0x28) TC Channel Interrupt Disable Register -------- */
/* -------- TC_IMR : (TC Offset: 0x2c) TC Channel Interrupt Mask Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Timer Counter Interface */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_TCB
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
#परिभाषय AT91C_TCB_SYNC                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 ) /* (TCB) Synchro Command */
/* -------- TCB_BMR : (TCB Offset: 0xc4) TC Block Mode Register -------- */
#परिभाषय AT91C_TCB_TC0XC0S              ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 0 ) /* (TCB) External Clock Signal 0 Selection */
#परिभाषय     AT91C_TCB_TC0XC0S_TCLK0    ( ( अचिह्नित पूर्णाङ्क ) 0x0 )      /* (TCB) TCLK0 connected to XC0 */
#परिभाषय     AT91C_TCB_TC0XC0S_NONE     ( ( अचिह्नित पूर्णाङ्क ) 0x1 )      /* (TCB) None signal connected to XC0 */
#परिभाषय     AT91C_TCB_TC0XC0S_TIOA1    ( ( अचिह्नित पूर्णाङ्क ) 0x2 )      /* (TCB) TIOA1 connected to XC0 */
#परिभाषय     AT91C_TCB_TC0XC0S_TIOA2    ( ( अचिह्नित पूर्णाङ्क ) 0x3 )      /* (TCB) TIOA2 connected to XC0 */
#परिभाषय AT91C_TCB_TC1XC1S              ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 2 ) /* (TCB) External Clock Signal 1 Selection */
#परिभाषय     AT91C_TCB_TC1XC1S_TCLK1    ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 2 ) /* (TCB) TCLK1 connected to XC1 */
#परिभाषय     AT91C_TCB_TC1XC1S_NONE     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 ) /* (TCB) None signal connected to XC1 */
#परिभाषय     AT91C_TCB_TC1XC1S_TIOA0    ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 2 ) /* (TCB) TIOA0 connected to XC1 */
#परिभाषय     AT91C_TCB_TC1XC1S_TIOA2    ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 2 ) /* (TCB) TIOA2 connected to XC1 */
#परिभाषय AT91C_TCB_TC2XC2S              ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 4 ) /* (TCB) External Clock Signal 2 Selection */
#परिभाषय     AT91C_TCB_TC2XC2S_TCLK2    ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 4 ) /* (TCB) TCLK2 connected to XC2 */
#परिभाषय     AT91C_TCB_TC2XC2S_NONE     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 ) /* (TCB) None signal connected to XC2 */
#परिभाषय     AT91C_TCB_TC2XC2S_TIOA0    ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 4 ) /* (TCB) TIOA0 connected to XC2 */
#परिभाषय     AT91C_TCB_TC2XC2S_TIOA1    ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 4 ) /* (TCB) TIOA2 connected to XC2 */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Control Area Network MailBox Interface */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_CAN_MB
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
#परिभाषय AT91C_CAN_MTIMEMARK              ( ( अचिह्नित पूर्णाङ्क ) 0xFFFF << 0 )  /* (CAN_MB) Mailbox Timemark */
#परिभाषय AT91_C_CAN_प्राक्                  ( ( अचिह्नित पूर्णाङ्क ) 0xF << 16 )    /* (CAN_MB) Mailbox Priority */
#परिभाषय AT91C_CAN_MOT                    ( ( अचिह्नित पूर्णाङ्क ) 0x7 << 24 )    /* (CAN_MB) Mailbox Object Type */
#परिभाषय     AT91C_CAN_MOT_DIS            ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 24 )    /* (CAN_MB) */
#परिभाषय     AT91C_CAN_MOT_RX             ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 24 )    /* (CAN_MB) */
#परिभाषय     AT91C_CAN_MOT_RXOVERWRITE    ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 24 )    /* (CAN_MB) */
#परिभाषय     AT91C_CAN_MOT_TX             ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 24 )    /* (CAN_MB) */
#परिभाषय     AT91_C_CAN_MOT_उपभोक्ता       ( ( अचिह्नित पूर्णाङ्क ) 0x4 << 24 )    /* (CAN_MB) */
#परिभाषय     AT91_C_CAN_MOT_उत्पादकः       ( ( अचिह्नित पूर्णाङ्क ) 0x5 << 24 )    /* (CAN_MB) */
/* -------- CAN_MAM : (CAN_MB Offset: 0x4) CAN Message Acceptance Mask Register -------- */
#परिभाषय AT91C_CAN_MIDvB                  ( ( अचिह्नित पूर्णाङ्क ) 0x3FFFF << 0 ) /* (CAN_MB) Complementary bits for identifier in extended mode */
#परिभाषय AT91C_CAN_MIDvA                  ( ( अचिह्नित पूर्णाङ्क ) 0x7FF << 18 )  /* (CAN_MB) Identifier for standard frame mode */
#परिभाषय AT91C_CAN_MIDE                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 29 )    /* (CAN_MB) Identifier Version */
/* -------- CAN_MID : (CAN_MB Offset: 0x8) CAN Message ID Register -------- */
/* -------- CAN_MFID : (CAN_MB Offset: 0xc) CAN Message Family ID Register -------- */
/* -------- CAN_MSR : (CAN_MB Offset: 0x10) CAN Message Status Register -------- */
#परिभाषय AT91C_CAN_MTIMESTAMP    ( ( अचिह्नित पूर्णाङ्क ) 0xFFFF << 0 ) /* (CAN_MB) Timer Value */
#परिभाषय AT91C_CAN_MDLC          ( ( अचिह्नित पूर्णाङ्क ) 0xF << 16 )   /* (CAN_MB) Mailbox Data Length Code */
#परिभाषय AT91C_CAN_MRTR          ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 20 )   /* (CAN_MB) Mailbox Remote Transmission Request */
#परिभाषय AT91C_CAN_MABT          ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 22 )   /* (CAN_MB) Mailbox Message Abort */
#परिभाषय AT91C_CAN_MRDY          ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 23 )   /* (CAN_MB) Mailbox Ready */
#परिभाषय AT91C_CAN_MMI           ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 24 )   /* (CAN_MB) Mailbox Message Ignored */
/* -------- CAN_MDL : (CAN_MB Offset: 0x14) CAN Message Data Low Register -------- */
/* -------- CAN_MDH : (CAN_MB Offset: 0x18) CAN Message Data High Register -------- */
/* -------- CAN_MCR : (CAN_MB Offset: 0x1c) CAN Message Control Register -------- */
#परिभाषय AT91C_CAN_MACR    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 22 ) /* (CAN_MB) Abort Request for Mailbox */
#परिभाषय AT91C_CAN_MTCR    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 23 ) /* (CAN_MB) Mailbox Transfer Command */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Control Area Network Interface */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_CAN
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
#परिभाषय AT91C_CAN_CANEN     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )  /* (CAN) CAN Controller Enable */
#परिभाषय AT91C_CAN_LPM       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )  /* (CAN) Disable/Enable Low Power Mode */
#परिभाषय AT91C_CAN_ABM       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )  /* (CAN) Disable/Enable Autobaud/Listen Mode */
#परिभाषय AT91C_CAN_OVL       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )  /* (CAN) Disable/Enable Overload Frame */
#परिभाषय AT91C_CAN_TEOF      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )  /* (CAN) Time Stamp messages at each end of Frame */
#परिभाषय AT91C_CAN_TTM       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 )  /* (CAN) Disable/Enable Time Trigger Mode */
#परिभाषय AT91C_CAN_TIMFRZ    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 6 )  /* (CAN) Enable Timer Freeze */
#परिभाषय AT91C_CAN_DRPT      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )  /* (CAN) Disable Repeat */
/* -------- CAN_IER : (CAN Offset: 0x4) CAN Interrupt Enable Register -------- */
#परिभाषय AT91C_CAN_MB0       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )  /* (CAN) Mailbox 0 Flag */
#परिभाषय AT91C_CAN_MB1       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )  /* (CAN) Mailbox 1 Flag */
#परिभाषय AT91C_CAN_MB2       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )  /* (CAN) Mailbox 2 Flag */
#परिभाषय AT91C_CAN_MB3       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )  /* (CAN) Mailbox 3 Flag */
#परिभाषय AT91C_CAN_MB4       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )  /* (CAN) Mailbox 4 Flag */
#परिभाषय AT91C_CAN_MB5       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 )  /* (CAN) Mailbox 5 Flag */
#परिभाषय AT91C_CAN_MB6       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 6 )  /* (CAN) Mailbox 6 Flag */
#परिभाषय AT91C_CAN_MB7       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )  /* (CAN) Mailbox 7 Flag */
#परिभाषय AT91C_CAN_MB8       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )  /* (CAN) Mailbox 8 Flag */
#परिभाषय AT91C_CAN_MB9       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 9 )  /* (CAN) Mailbox 9 Flag */
#परिभाषय AT91C_CAN_MB10      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 10 ) /* (CAN) Mailbox 10 Flag */
#परिभाषय AT91C_CAN_MB11      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 11 ) /* (CAN) Mailbox 11 Flag */
#परिभाषय AT91C_CAN_MB12      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 12 ) /* (CAN) Mailbox 12 Flag */
#परिभाषय AT91C_CAN_MB13      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 13 ) /* (CAN) Mailbox 13 Flag */
#परिभाषय AT91C_CAN_MB14      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 14 ) /* (CAN) Mailbox 14 Flag */
#परिभाषय AT91C_CAN_MB15      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 15 ) /* (CAN) Mailbox 15 Flag */
#परिभाषय AT91C_CAN_ERRA      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 ) /* (CAN) Error Active Mode Flag */
#परिभाषय AT91C_CAN_WARN      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 17 ) /* (CAN) Warning Limit Flag */
#परिभाषय AT91C_CAN_ERRP      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 18 ) /* (CAN) Error Passive Mode Flag */
#परिभाषय AT91C_CAN_BOFF      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 19 ) /* (CAN) Bus Off Mode Flag */
#परिभाषय AT91C_CAN_SLEEP     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 20 ) /* (CAN) Sleep Flag */
#परिभाषय AT91C_CAN_WAKEUP    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 21 ) /* (CAN) Wakeup Flag */
#परिभाषय AT91C_CAN_TOVF      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 22 ) /* (CAN) Timer Overflow Flag */
#परिभाषय AT91C_CAN_TSTP      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 23 ) /* (CAN) Timestamp Flag */
#परिभाषय AT91C_CAN_CERR      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 24 ) /* (CAN) CRC Error */
#परिभाषय AT91C_CAN_SERR      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 25 ) /* (CAN) Stuffing Error */
#परिभाषय AT91C_CAN_AERR      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 26 ) /* (CAN) Acknowledgment Error */
#परिभाषय AT91C_CAN_FERR      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 27 ) /* (CAN) Form Error */
#परिभाषय AT91C_CAN_BERR      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 28 ) /* (CAN) Bit Error */
/* -------- CAN_IDR : (CAN Offset: 0x8) CAN Interrupt Disable Register -------- */
/* -------- CAN_IMR : (CAN Offset: 0xc) CAN Interrupt Mask Register -------- */
/* -------- CAN_SR : (CAN Offset: 0x10) CAN Status Register -------- */
#परिभाषय AT91C_CAN_RBSY      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 29 )   /* (CAN) Receiver Busy */
#परिभाषय AT91C_CAN_TBSY      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 30 )   /* (CAN) Transmitter Busy */
#परिभाषय AT91C_CAN_OVLY      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 31 )   /* (CAN) Overload Busy */
/* -------- CAN_BR : (CAN Offset: 0x14) CAN Baudrate Register -------- */
#परिभाषय AT91C_CAN_PHASE2    ( ( अचिह्नित पूर्णाङ्क ) 0x7 << 0 )    /* (CAN) Phase 2 segment */
#परिभाषय AT91C_CAN_PHASE1    ( ( अचिह्नित पूर्णाङ्क ) 0x7 << 4 )    /* (CAN) Phase 1 segment */
#परिभाषय AT91C_CAN_PROPAG    ( ( अचिह्नित पूर्णाङ्क ) 0x7 << 8 )    /* (CAN) Programmation time segment */
#परिभाषय AT91C_CAN_SYNC      ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 12 )   /* (CAN) Re-synchronization jump width segment */
#परिभाषय AT91C_CAN_BRP       ( ( अचिह्नित पूर्णाङ्क ) 0x7F << 16 )  /* (CAN) Baudrate Prescaler */
#परिभाषय AT91C_CAN_SMP       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 24 )   /* (CAN) Sampling mode */
/* -------- CAN_TIM : (CAN Offset: 0x18) CAN Timer Register -------- */
#परिभाषय AT91C_CAN_TIMER     ( ( अचिह्नित पूर्णाङ्क ) 0xFFFF << 0 ) /* (CAN) Timer field */
/* -------- CAN_TIMESTP : (CAN Offset: 0x1c) CAN Timestamp Register -------- */
/* -------- CAN_ECR : (CAN Offset: 0x20) CAN Error Counter Register -------- */
#परिभाषय AT91C_CAN_REC       ( ( अचिह्नित पूर्णाङ्क ) 0xFF << 0 )  /* (CAN) Receive Error Counter */
#परिभाषय AT91C_CAN_TEC       ( ( अचिह्नित पूर्णाङ्क ) 0xFF << 16 ) /* (CAN) Transmit Error Counter */
/* -------- CAN_TCR : (CAN Offset: 0x24) CAN Transfer Command Register -------- */
#परिभाषय AT91C_CAN_TIMRST    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 31 )  /* (CAN) Timer Reset Field */
/* -------- CAN_ACR : (CAN Offset: 0x28) CAN Abort Command Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Ethernet MAC 10/100 */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_EMAC
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
#परिभाषय AT91C_EMAC_LB                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )  /* (EMAC) Loopback. Optional. When set, loopback signal is at high level. */
#परिभाषय AT91C_EMAC_LLB                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )  /* (EMAC) Loopback local. */
#परिभाषय AT91C_EMAC_RE                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )  /* (EMAC) Receive enable. */
#परिभाषय AT91C_EMAC_TE                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )  /* (EMAC) Transmit enable. */
#परिभाषय AT91C_EMAC_MPE                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )  /* (EMAC) Management port enable. */
#परिभाषय AT91C_EMAC_CLRSTAT              ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 )  /* (EMAC) Clear statistics registers. */
#परिभाषय AT91C_EMAC_INCSTAT              ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 6 )  /* (EMAC) Increment statistics registers. */
#परिभाषय AT91C_EMAC_WESTAT               ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )  /* (EMAC) Write enable for statistics registers. */
#परिभाषय AT91C_EMAC_BP                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )  /* (EMAC) Back pressure. */
#परिभाषय AT91C_EMAC_TSTART               ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 9 )  /* (EMAC) Start Transmission. */
#परिभाषय AT91C_EMAC_THALT                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 10 ) /* (EMAC) Transmission Halt. */
#परिभाषय AT91C_EMAC_TPFR                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 11 ) /* (EMAC) Transmit pause frame */
#परिभाषय AT91C_EMAC_TZQ                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 12 ) /* (EMAC) Transmit zero quantum pause frame */
/* -------- EMAC_NCFGR : (EMAC Offset: 0x4) Network Configuration Register -------- */
#परिभाषय AT91C_EMAC_SPD                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )  /* (EMAC) Speed. */
#परिभाषय AT91C_EMAC_FD                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )  /* (EMAC) Full duplex. */
#परिभाषय AT91C_EMAC_JFRAME               ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )  /* (EMAC) Jumbo Frames. */
#परिभाषय AT91C_EMAC_CAF                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )  /* (EMAC) Copy all frames. */
#परिभाषय AT91C_EMAC_NBC                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 )  /* (EMAC) No broadcast. */
#परिभाषय AT91C_EMAC_MTI                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 6 )  /* (EMAC) Multicast hash event enable */
#परिभाषय AT91C_EMAC_UNI                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )  /* (EMAC) Unicast hash enable. */
#परिभाषय AT91C_EMAC_BIG                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )  /* (EMAC) Receive 1522 bytes. */
#परिभाषय AT91C_EMAC_EAE                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 9 )  /* (EMAC) External address match enable. */
#परिभाषय AT91C_EMAC_CLK                  ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 10 ) /* (EMAC) */
#परिभाषय     AT91C_EMAC_CLK_HCLK_8       ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 10 ) /* (EMAC) HCLK divided by 8 */
#परिभाषय     AT91C_EMAC_CLK_HCLK_16      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 10 ) /* (EMAC) HCLK divided by 16 */
#परिभाषय     AT91C_EMAC_CLK_HCLK_32      ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 10 ) /* (EMAC) HCLK divided by 32 */
#परिभाषय     AT91C_EMAC_CLK_HCLK_64      ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 10 ) /* (EMAC) HCLK divided by 64 */
#परिभाषय AT91C_EMAC_RTY                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 12 ) /* (EMAC) */
#परिभाषय AT91C_EMAC_PAE                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 13 ) /* (EMAC) */
#परिभाषय AT91C_EMAC_RBOF                 ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 14 ) /* (EMAC) */
#परिभाषय     AT91_C_EMAC_RBOF_विस्थापनम्_0    ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 14 ) /* (EMAC) no offset from start of receive buffer */
#परिभाषय     AT91_C_EMAC_RBOF_विस्थापनम्_1    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 14 ) /* (EMAC) one byte offset from start of receive buffer */
#परिभाषय     AT91_C_EMAC_RBOF_विस्थापनम्_2    ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 14 ) /* (EMAC) two bytes offset from start of receive buffer */
#परिभाषय     AT91_C_EMAC_RBOF_विस्थापनम्_3    ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 14 ) /* (EMAC) three bytes offset from start of receive buffer */
#परिभाषय AT91C_EMAC_RLCE                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 ) /* (EMAC) Receive Length field Checking Enable */
#परिभाषय AT91C_EMAC_DRFCS                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 17 ) /* (EMAC) Discard Receive FCS */
#परिभाषय AT91C_EMAC_EFRHD                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 18 ) /* (EMAC) */
#परिभाषय AT91C_EMAC_IRXFCS               ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 19 ) /* (EMAC) Ignore RX FCS */
/* -------- EMAC_NSR : (EMAC Offset: 0x8) Network Status Register -------- */
#परिभाषय AT91C_EMAC_LINKR                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )  /* (EMAC) */
#परिभाषय AT91C_EMAC_MDIO                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )  /* (EMAC) */
#परिभाषय AT91C_EMAC_IDLE                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )  /* (EMAC) */
/* -------- EMAC_TSR : (EMAC Offset: 0x14) Transmit Status Register -------- */
#परिभाषय AT91C_EMAC_UBR                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )  /* (EMAC) */
#परिभाषय AT91C_EMAC_COL                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )  /* (EMAC) */
#परिभाषय AT91C_EMAC_RLES                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )  /* (EMAC) */
#परिभाषय AT91C_EMAC_TGO                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )  /* (EMAC) Transmit Go */
#परिभाषय AT91C_EMAC_BEX                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )  /* (EMAC) Buffers exhausted mid frame */
#परिभाषय AT91C_EMAC_COMP                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 )  /* (EMAC) */
#परिभाषय AT91C_EMAC_UND                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 6 )  /* (EMAC) */
/* -------- EMAC_RSR : (EMAC Offset: 0x20) Receive Status Register -------- */
#परिभाषय AT91C_EMAC_BNA                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )  /* (EMAC) */
#परिभाषय AT91C_EMAC_REC                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )  /* (EMAC) */
#परिभाषय AT91C_EMAC_OVR                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )  /* (EMAC) */
/* -------- EMAC_ISR : (EMAC Offset: 0x24) Interrupt Status Register -------- */
#परिभाषय AT91C_EMAC_MFD                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )  /* (EMAC) */
#परिभाषय AT91C_EMAC_RCOMP                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )  /* (EMAC) */
#परिभाषय AT91C_EMAC_RXUBR                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )  /* (EMAC) */
#परिभाषय AT91C_EMAC_TXUBR                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )  /* (EMAC) */
#परिभाषय AT91C_EMAC_TUNDR                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )  /* (EMAC) */
#परिभाषय AT91C_EMAC_RLEX                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 )  /* (EMAC) */
#परिभाषय AT91C_EMAC_TXERR                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 6 )  /* (EMAC) */
#परिभाषय AT91C_EMAC_TCOMP                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )  /* (EMAC) */
#परिभाषय AT91C_EMAC_LINK                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 9 )  /* (EMAC) */
#परिभाषय AT91C_EMAC_ROVR                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 10 ) /* (EMAC) */
#परिभाषय AT91C_EMAC_HRESP                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 11 ) /* (EMAC) */
#परिभाषय AT91C_EMAC_PFRE                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 12 ) /* (EMAC) */
#परिभाषय AT91C_EMAC_PTZ                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 13 ) /* (EMAC) */
/* -------- EMAC_IER : (EMAC Offset: 0x28) Interrupt Enable Register -------- */
/* -------- EMAC_IDR : (EMAC Offset: 0x2c) Interrupt Disable Register -------- */
/* -------- EMAC_IMR : (EMAC Offset: 0x30) Interrupt Mask Register -------- */
/* -------- EMAC_MAN : (EMAC Offset: 0x34) PHY Maintenance Register -------- */
#परिभाषय AT91_C_EMAC_दत्त       ( ( अचिह्नित पूर्णाङ्क ) 0xFFFF << 0 )  /* (EMAC) */
#परिभाषय AT91_C_EMAC_संहिता       ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 16 )    /* (EMAC) */
#परिभाषय AT91C_EMAC_REGA       ( ( अचिह्नित पूर्णाङ्क ) 0x1F << 18 )   /* (EMAC) */
#परिभाषय AT91C_EMAC_PHYA       ( ( अचिह्नित पूर्णाङ्क ) 0x1F << 23 )   /* (EMAC) */
#परिभाषय AT91C_EMAC_RW         ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 28 )    /* (EMAC) */
#परिभाषय AT91C_EMAC_SOF        ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 30 )    /* (EMAC) */
/* -------- EMAC_USRIO : (EMAC Offset: 0xc0) USER Input Output Register -------- */
#परिभाषय AT91C_EMAC_RMII       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )     /* (EMAC) Reduce MII */
/* -------- EMAC_WOL : (EMAC Offset: 0xc4) Wake On LAN Register -------- */
#परिभाषय AT91C_EMAC_IP         ( ( अचिह्नित पूर्णाङ्क ) 0xFFFF << 0 )  /* (EMAC) ARP request IP address */
#परिभाषय AT91C_EMAC_MAG        ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 )    /* (EMAC) Magic packet event enable */
#परिभाषय AT91C_EMAC_ARP        ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 17 )    /* (EMAC) ARP request event enable */
#परिभाषय AT91C_EMAC_SA1        ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 18 )    /* (EMAC) Specific address register 1 event enable */
/* -------- EMAC_REV : (EMAC Offset: 0xfc) Revision Register -------- */
#परिभाषय AT91C_EMAC_REVREF     ( ( अचिह्नित पूर्णाङ्क ) 0xFFFF << 0 )  /* (EMAC) */
#परिभाषय AT91C_EMAC_PARTREF    ( ( अचिह्नित पूर्णाङ्क ) 0xFFFF << 16 ) /* (EMAC) */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Analog to Digital Convertor */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_ADC
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
#परिभाषय AT91C_ADC_SWRST                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )   /* (ADC) Software Reset */
#परिभाषय AT91C_ADC_START                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )   /* (ADC) Start Conversion */
/* -------- ADC_MR : (ADC Offset: 0x4) ADC Mode Register -------- */
#परिभाषय AT91C_ADC_TRGEN                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )   /* (ADC) Trigger Enable */
#परिभाषय     AT91C_ADC_TRGEN_DIS            ( ( अचिह्नित पूर्णाङ्क ) 0x0 )        /* (ADC) Hardware triggers are disabled. Starting a conversion is only possible by software */
#परिभाषय     AT91C_ADC_TRGEN_EN             ( ( अचिह्नित पूर्णाङ्क ) 0x1 )        /* (ADC) Hardware trigger selected by TRGSEL field is enabled. */
#परिभाषय AT91C_ADC_TRGSEL                   ( ( अचिह्नित पूर्णाङ्क ) 0x7 << 1 )   /* (ADC) Trigger Selection */
#परिभाषय     AT91C_ADC_TRGSEL_TIOA0         ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 1 )   /* (ADC) Selected TRGSEL = TIAO0 */
#परिभाषय     AT91C_ADC_TRGSEL_TIOA1         ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )   /* (ADC) Selected TRGSEL = TIAO1 */
#परिभाषय     AT91C_ADC_TRGSEL_TIOA2         ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 1 )   /* (ADC) Selected TRGSEL = TIAO2 */
#परिभाषय     AT91C_ADC_TRGSEL_TIOA3         ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 1 )   /* (ADC) Selected TRGSEL = TIAO3 */
#परिभाषय     AT91C_ADC_TRGSEL_TIOA4         ( ( अचिह्नित पूर्णाङ्क ) 0x4 << 1 )   /* (ADC) Selected TRGSEL = TIAO4 */
#परिभाषय     AT91C_ADC_TRGSEL_TIOA5         ( ( अचिह्नित पूर्णाङ्क ) 0x5 << 1 )   /* (ADC) Selected TRGSEL = TIAO5 */
#परिभाषय     AT91C_ADC_TRGSEL_EXT           ( ( अचिह्नित पूर्णाङ्क ) 0x6 << 1 )   /* (ADC) Selected TRGSEL = External Trigger */
#परिभाषय AT91C_ADC_LOWRES                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )   /* (ADC) Resolution. */
#परिभाषय     AT91C_ADC_LOWRES_10_BIT        ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 4 )   /* (ADC) 10-bit resolution */
#परिभाषय     AT91C_ADC_LOWRES_8_BIT         ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )   /* (ADC) 8-bit resolution */
#परिभाषय AT91C_ADC_SLEEP                    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 )   /* (ADC) Sleep Mode */
#परिभाषय     AT91_C_ADC_SLEEP_प्रसामान्यम्_बहुलकम्    ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 5 )   /* (ADC) Normal Mode */
#परिभाषय     AT91_C_ADC_SLEEP_बहुलकम्           ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 )   /* (ADC) Sleep Mode */
#परिभाषय AT91C_ADC_PRESCAL                  ( ( अचिह्नित पूर्णाङ्क ) 0x3F << 8 )  /* (ADC) Prescaler rate selection */
#परिभाषय AT91C_ADC_STARTUP                  ( ( अचिह्नित पूर्णाङ्क ) 0x1F << 16 ) /* (ADC) Startup Time */
#परिभाषय AT91C_ADC_SHTIM                    ( ( अचिह्नित पूर्णाङ्क ) 0xF << 24 )  /* (ADC) Sample & Hold Time */
/* --------     ADC_CHER : (ADC Offset: 0x10) ADC Channel Enable Register -------- */
#परिभाषय AT91C_ADC_CH0                      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )   /* (ADC) Channel 0 */
#परिभाषय AT91C_ADC_CH1                      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )   /* (ADC) Channel 1 */
#परिभाषय AT91C_ADC_CH2                      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )   /* (ADC) Channel 2 */
#परिभाषय AT91C_ADC_CH3                      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )   /* (ADC) Channel 3 */
#परिभाषय AT91C_ADC_CH4                      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )   /* (ADC) Channel 4 */
#परिभाषय AT91C_ADC_CH5                      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 )   /* (ADC) Channel 5 */
#परिभाषय AT91C_ADC_CH6                      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 6 )   /* (ADC) Channel 6 */
#परिभाषय AT91C_ADC_CH7                      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )   /* (ADC) Channel 7 */
/* --------     ADC_CHDR : (ADC Offset: 0x14) ADC Channel Disable Register -------- */
/* --------     ADC_CHSR : (ADC Offset: 0x18) ADC Channel Status Register -------- */
/* -------- ADC_SR : (ADC Offset: 0x1c) ADC Status Register -------- */
#परिभाषय AT91C_ADC_EOC0      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )   /* (ADC) End of Conversion */
#परिभाषय AT91C_ADC_EOC1      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )   /* (ADC) End of Conversion */
#परिभाषय AT91C_ADC_EOC2      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )   /* (ADC) End of Conversion */
#परिभाषय AT91C_ADC_EOC3      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )   /* (ADC) End of Conversion */
#परिभाषय AT91C_ADC_EOC4      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )   /* (ADC) End of Conversion */
#परिभाषय AT91C_ADC_EOC5      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 5 )   /* (ADC) End of Conversion */
#परिभाषय AT91C_ADC_EOC6      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 6 )   /* (ADC) End of Conversion */
#परिभाषय AT91C_ADC_EOC7      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 7 )   /* (ADC) End of Conversion */
#परिभाषय AT91C_ADC_OVRE0     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )   /* (ADC) Overrun Error */
#परिभाषय AT91C_ADC_OVRE1     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 9 )   /* (ADC) Overrun Error */
#परिभाषय AT91C_ADC_OVRE2     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 10 )  /* (ADC) Overrun Error */
#परिभाषय AT91C_ADC_OVRE3     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 11 )  /* (ADC) Overrun Error */
#परिभाषय AT91C_ADC_OVRE4     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 12 )  /* (ADC) Overrun Error */
#परिभाषय AT91C_ADC_OVRE5     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 13 )  /* (ADC) Overrun Error */
#परिभाषय AT91C_ADC_OVRE6     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 14 )  /* (ADC) Overrun Error */
#परिभाषय AT91C_ADC_OVRE7     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 15 )  /* (ADC) Overrun Error */
#परिभाषय AT91C_ADC_DRDY      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 )  /* (ADC) Data Ready */
#परिभाषय AT91C_ADC_GOVRE     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 17 )  /* (ADC) General Overrun */
#परिभाषय AT91C_ADC_ENDRX     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 18 )  /* (ADC) End of Receiver Transfer */
#परिभाषय AT91C_ADC_RXBUFF    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 19 )  /* (ADC) RXBUFF Interrupt */
/* -------- ADC_LCDR : (ADC Offset: 0x20) ADC Last Converted Data Register -------- */
#परिभाषय AT91C_ADC_LDATA     ( ( अचिह्नित पूर्णाङ्क ) 0x3FF << 0 ) /* (ADC) Last Data Converted */
/* -------- ADC_IER : (ADC Offset: 0x24) ADC Interrupt Enable Register -------- */
/* -------- ADC_IDR : (ADC Offset: 0x28) ADC Interrupt Disable Register -------- */
/* -------- ADC_IMR : (ADC Offset: 0x2c) ADC Interrupt Mask Register -------- */
/* -------- ADC_CDR0 : (ADC Offset: 0x30) ADC Channel Data Register 0 -------- */
#परिभाषय AT91_C_ADC_दत्त    ( ( अचिह्नित पूर्णाङ्क ) 0x3FF << 0 )  /* (ADC) Converted Data */
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
प्रकारनिर्देश संरचना _AT91S_AES
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
#परिभाषय AT91C_AES_START                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )   /* (AES) Starts Processing */
#परिभाषय AT91C_AES_SWRST                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )   /* (AES) Software Reset */
#परिभाषय AT91C_AES_LOADSEED              ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 )  /* (AES) Random Number Generator Seed Loading */
/* -------- AES_MR : (AES Offset: 0x4) Mode Register -------- */
#परिभाषय AT91C_AES_CIPHER                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )   /* (AES) Processing Mode */
#परिभाषय AT91C_AES_PROCDLY               ( ( अचिह्नित पूर्णाङ्क ) 0xF << 4 )   /* (AES) Processing Delay */
#परिभाषय AT91C_AES_SMOD                  ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 8 )   /* (AES) Start Mode */
#परिभाषय     AT91C_AES_SMOD_MANUAL       ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 8 )   /* (AES) Manual Mode: The START bit in register AES_CR must be set to begin encryption or decryption. */
#परिभाषय     AT91C_AES_SMOD_AUTO         ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )   /* (AES) Auto Mode: no action in AES_CR is necessary (cf datasheet). */
#परिभाषय     AT91C_AES_SMOD_PDC          ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 8 )   /* (AES) PDC Mode (cf datasheet). */
#परिभाषय AT91C_AES_OPMOD                 ( ( अचिह्नित पूर्णाङ्क ) 0x7 << 12 )  /* (AES) Operation Mode */
#परिभाषय     AT91C_AES_OPMOD_ECB         ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 12 )  /* (AES) ECB Electronic CodeBook mode. */
#परिभाषय     AT91C_AES_OPMOD_CBC         ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 12 )  /* (AES) CBC Cipher Block Chaining mode. */
#परिभाषय     AT91C_AES_OPMOD_OFB         ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 12 )  /* (AES) OFB Output Feedback mode. */
#परिभाषय     AT91C_AES_OPMOD_CFB         ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 12 )  /* (AES) CFB Cipher Feedback mode. */
#परिभाषय     AT91C_AES_OPMOD_CTR         ( ( अचिह्नित पूर्णाङ्क ) 0x4 << 12 )  /* (AES) CTR Counter mode. */
#परिभाषय AT91C_AES_LOD                   ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 15 )  /* (AES) Last Output Data Mode */
#परिभाषय AT91C_AES_CFBS                  ( ( अचिह्नित पूर्णाङ्क ) 0x7 << 16 )  /* (AES) Cipher Feedback Data Size */
#परिभाषय     AT91C_AES_CFBS_128_BIT      ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 16 )  /* (AES) 128-bit. */
#परिभाषय     AT91C_AES_CFBS_64_BIT       ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 )  /* (AES) 64-bit. */
#परिभाषय     AT91C_AES_CFBS_32_BIT       ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 16 )  /* (AES) 32-bit. */
#परिभाषय     AT91C_AES_CFBS_16_BIT       ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 16 )  /* (AES) 16-bit. */
#परिभाषय     AT91C_AES_CFBS_8_BIT        ( ( अचिह्नित पूर्णाङ्क ) 0x4 << 16 )  /* (AES) 8-bit. */
#परिभाषय AT91C_AES_CKEY                  ( ( अचिह्नित पूर्णाङ्क ) 0xF << 20 )  /* (AES) Countermeasure Key */
#परिभाषय AT91C_AES_CTYPE                 ( ( अचिह्नित पूर्णाङ्क ) 0x1F << 24 ) /* (AES) Countermeasure Type */
#परिभाषय     AT91C_AES_CTYPE_TYPE1_EN    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 24 )  /* (AES) Countermeasure type 1 is enabled. */
#परिभाषय     AT91C_AES_CTYPE_TYPE2_EN    ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 24 )  /* (AES) Countermeasure type 2 is enabled. */
#परिभाषय     AT91C_AES_CTYPE_TYPE3_EN    ( ( अचिह्नित पूर्णाङ्क ) 0x4 << 24 )  /* (AES) Countermeasure type 3 is enabled. */
#परिभाषय     AT91C_AES_CTYPE_TYPE4_EN    ( ( अचिह्नित पूर्णाङ्क ) 0x8 << 24 )  /* (AES) Countermeasure type 4 is enabled. */
#परिभाषय     AT91C_AES_CTYPE_TYPE5_EN    ( ( अचिह्नित पूर्णाङ्क ) 0x10 << 24 ) /* (AES) Countermeasure type 5 is enabled. */
/* -------- AES_IER : (AES Offset: 0x10) Interrupt Enable Register -------- */
#परिभाषय AT91C_AES_DATRDY                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )   /* (AES) DATRDY */
#परिभाषय AT91C_AES_ENDRX                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )   /* (AES) PDC Read Buffer End */
#परिभाषय AT91C_AES_ENDTX                 ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )   /* (AES) PDC Write Buffer End */
#परिभाषय AT91C_AES_RXBUFF                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )   /* (AES) PDC Read Buffer Full */
#परिभाषय AT91C_AES_TXBUFE                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )   /* (AES) PDC Write Buffer Empty */
#परिभाषय AT91C_AES_URAD                  ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )   /* (AES) Unspecified Register Access Detection */
/* -------- AES_IDR : (AES Offset: 0x14) Interrupt Disable Register -------- */
/* -------- AES_IMR : (AES Offset: 0x18) Interrupt Mask Register -------- */
/* -------- AES_ISR : (AES Offset: 0x1c) Interrupt Status Register -------- */
#परिभाषय AT91C_AES_URAT                              ( ( अचिह्नित पूर्णाङ्क ) 0x7 << 12 ) /* (AES) Unspecified Register Access Type Status */
#परिभाषय     AT91_C_AES_URAT_अन्तर्_DAT_WRITE_DATPROC     ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 12 ) /* (AES) Input data register written during the data processing in PDC mode. */
#परिभाषय     AT91_C_AES_URAT_बहिर्गमनम्_DAT_READ_DATPROC     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 12 ) /* (AES) Output data register read during the data processing. */
#परिभाषय     AT91C_AES_URAT_MODEREG_WRITE_DATPROC    ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 12 ) /* (AES) Mode register written during the data processing. */
#परिभाषय     AT91_C_AES_URAT_बहिर्गमनम्_DAT_READ_SUBKEY      ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 12 ) /* (AES) Output data register read during the sub-keys generation. */
#परिभाषय     AT91C_AES_URAT_MODEREG_WRITE_SUBKEY     ( ( अचिह्नित पूर्णाङ्क ) 0x4 << 12 ) /* (AES) Mode register written during the sub-keys generation. */
#परिभाषय     AT91C_AES_URAT_WO_REG_READ              ( ( अचिह्नित पूर्णाङ्क ) 0x5 << 12 ) /* (AES) Write-only register read access. */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Triple Data Encryption Standard */
/* ***************************************************************************** */
प्रकारनिर्देश संरचना _AT91S_TDES
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
#परिभाषय AT91C_TDES_START              ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )  /* (TDES) Starts Processing */
#परिभाषय AT91C_TDES_SWRST              ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )  /* (TDES) Software Reset */
/* -------- TDES_MR : (TDES Offset: 0x4) Mode Register -------- */
#परिभाषय AT91C_TDES_CIPHER             ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )  /* (TDES) Processing Mode */
#परिभाषय AT91C_TDES_TDESMOD            ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )  /* (TDES) Single or Triple DES Mode */
#परिभाषय AT91C_TDES_KEYMOD             ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )  /* (TDES) Key Mode */
#परिभाषय AT91C_TDES_SMOD               ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 8 )  /* (TDES) Start Mode */
#परिभाषय     AT91C_TDES_SMOD_MANUAL    ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 8 )  /* (TDES) Manual Mode: The START bit in register TDES_CR must be set to begin encryption or decryption. */
#परिभाषय     AT91C_TDES_SMOD_AUTO      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )  /* (TDES) Auto Mode: no action in TDES_CR is necessary (cf datasheet). */
#परिभाषय     AT91C_TDES_SMOD_PDC       ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 8 )  /* (TDES) PDC Mode (cf datasheet). */
#परिभाषय AT91C_TDES_OPMOD              ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 12 ) /* (TDES) Operation Mode */
#परिभाषय     AT91C_TDES_OPMOD_ECB      ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 12 ) /* (TDES) ECB Electronic CodeBook mode. */
#परिभाषय     AT91C_TDES_OPMOD_CBC      ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 12 ) /* (TDES) CBC Cipher Block Chaining mode. */
#परिभाषय     AT91C_TDES_OPMOD_OFB      ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 12 ) /* (TDES) OFB Output Feedback mode. */
#परिभाषय     AT91C_TDES_OPMOD_CFB      ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 12 ) /* (TDES) CFB Cipher Feedback mode. */
#परिभाषय AT91C_TDES_LOD                ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 15 ) /* (TDES) Last Output Data Mode */
#परिभाषय AT91C_TDES_CFBS               ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 16 ) /* (TDES) Cipher Feedback Data Size */
#परिभाषय     AT91C_TDES_CFBS_64_BIT    ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 16 ) /* (TDES) 64-bit. */
#परिभाषय     AT91C_TDES_CFBS_32_BIT    ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 16 ) /* (TDES) 32-bit. */
#परिभाषय     AT91C_TDES_CFBS_16_BIT    ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 16 ) /* (TDES) 16-bit. */
#परिभाषय     AT91C_TDES_CFBS_8_BIT     ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 16 ) /* (TDES) 8-bit. */
/* -------- TDES_IER : (TDES Offset: 0x10) Interrupt Enable Register -------- */
#परिभाषय AT91C_TDES_DATRDY             ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 0 )  /* (TDES) DATRDY */
#परिभाषय AT91C_TDES_ENDRX              ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 1 )  /* (TDES) PDC Read Buffer End */
#परिभाषय AT91C_TDES_ENDTX              ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 2 )  /* (TDES) PDC Write Buffer End */
#परिभाषय AT91C_TDES_RXBUFF             ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 3 )  /* (TDES) PDC Read Buffer Full */
#परिभाषय AT91C_TDES_TXBUFE             ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 4 )  /* (TDES) PDC Write Buffer Empty */
#परिभाषय AT91C_TDES_URAD               ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 8 )  /* (TDES) Unspecified Register Access Detection */
/* -------- TDES_IDR : (TDES Offset: 0x14) Interrupt Disable Register -------- */
/* -------- TDES_IMR : (TDES Offset: 0x18) Interrupt Mask Register -------- */
/* -------- TDES_ISR : (TDES Offset: 0x1c) Interrupt Status Register -------- */
#परिभाषय AT91C_TDES_URAT                              ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 12 ) /* (TDES) Unspecified Register Access Type Status */
#परिभाषय     AT91_C_TDES_URAT_अन्तर्_DAT_WRITE_DATPROC     ( ( अचिह्नित पूर्णाङ्क ) 0x0 << 12 ) /* (TDES) Input data register written during the data processing in PDC mode. */
#परिभाषय     AT91_C_TDES_URAT_बहिर्गमनम्_DAT_READ_DATPROC     ( ( अचिह्नित पूर्णाङ्क ) 0x1 << 12 ) /* (TDES) Output data register read during the data processing. */
#परिभाषय     AT91C_TDES_URAT_MODEREG_WRITE_DATPROC    ( ( अचिह्नित पूर्णाङ्क ) 0x2 << 12 ) /* (TDES) Mode register written during the data processing. */
#परिभाषय     AT91C_TDES_URAT_WO_REG_READ              ( ( अचिह्नित पूर्णाङ्क ) 0x3 << 12 ) /* (TDES) Write-only register read access. */

/* ***************************************************************************** */
/*               REGISTER ADDRESS DEFINITION FOR AT91SAM7X256 */
/* ***************************************************************************** */
/* ========== Register definition for SYS peripheral ========== */
/* ========== Register definition for AIC peripheral ========== */
#परिभाषय AT91C_AIC_IVR              ( ( AT91_REG * ) 0xFFFFF100 ) /* (AIC) IRQ Vector Register */
#परिभाषय AT91C_AIC_SMR              ( ( AT91_REG * ) 0xFFFFF000 ) /* (AIC) Source Mode Register */
#परिभाषय AT91C_AIC_FVR              ( ( AT91_REG * ) 0xFFFFF104 ) /* (AIC) FIQ Vector Register */
#परिभाषय AT91C_AIC_DCR              ( ( AT91_REG * ) 0xFFFFF138 ) /* (AIC) Debug Control Register (Protect) */
#परिभाषय AT91C_AIC_EOICR            ( ( AT91_REG * ) 0xFFFFF130 ) /* (AIC) End of Interrupt Command Register */
#परिभाषय AT91C_AIC_SVR              ( ( AT91_REG * ) 0xFFFFF080 ) /* (AIC) Source Vector Register */
#परिभाषय AT91C_AIC_FFSR             ( ( AT91_REG * ) 0xFFFFF148 ) /* (AIC) Fast Forcing Status Register */
#परिभाषय AT91C_AIC_ICCR             ( ( AT91_REG * ) 0xFFFFF128 ) /* (AIC) Interrupt Clear Command Register */
#परिभाषय AT91C_AIC_ISR              ( ( AT91_REG * ) 0xFFFFF108 ) /* (AIC) Interrupt Status Register */
#परिभाषय AT91C_AIC_IMR              ( ( AT91_REG * ) 0xFFFFF110 ) /* (AIC) Interrupt Mask Register */
#परिभाषय AT91C_AIC_IPR              ( ( AT91_REG * ) 0xFFFFF10C ) /* (AIC) Interrupt Pending Register */
#परिभाषय AT91C_AIC_FFER             ( ( AT91_REG * ) 0xFFFFF140 ) /* (AIC) Fast Forcing Enable Register */
#परिभाषय AT91C_AIC_IECR             ( ( AT91_REG * ) 0xFFFFF120 ) /* (AIC) Interrupt Enable Command Register */
#परिभाषय AT91C_AIC_ISCR             ( ( AT91_REG * ) 0xFFFFF12C ) /* (AIC) Interrupt Set Command Register */
#परिभाषय AT91C_AIC_FFDR             ( ( AT91_REG * ) 0xFFFFF144 ) /* (AIC) Fast Forcing Disable Register */
#परिभाषय AT91C_AIC_CISR             ( ( AT91_REG * ) 0xFFFFF114 ) /* (AIC) Core Interrupt Status Register */
#परिभाषय AT91C_AIC_IDCR             ( ( AT91_REG * ) 0xFFFFF124 ) /* (AIC) Interrupt Disable Command Register */
#परिभाषय AT91C_AIC_SPU              ( ( AT91_REG * ) 0xFFFFF134 ) /* (AIC) Spurious Vector Register */
/* ========== Register definition for PDC_DBGU peripheral ========== */
#परिभाषय AT91C_DBGU_TCR             ( ( AT91_REG * ) 0xFFFFF30C ) /* (PDC_DBGU) Transmit Counter Register */
#परिभाषय AT91C_DBGU_RNPR            ( ( AT91_REG * ) 0xFFFFF310 ) /* (PDC_DBGU) Receive Next Pointer Register */
#परिभाषय AT91C_DBGU_TNPR            ( ( AT91_REG * ) 0xFFFFF318 ) /* (PDC_DBGU) Transmit Next Pointer Register */
#परिभाषय AT91C_DBGU_TPR             ( ( AT91_REG * ) 0xFFFFF308 ) /* (PDC_DBGU) Transmit Pointer Register */
#परिभाषय AT91C_DBGU_RPR             ( ( AT91_REG * ) 0xFFFFF300 ) /* (PDC_DBGU) Receive Pointer Register */
#परिभाषय AT91C_DBGU_RCR             ( ( AT91_REG * ) 0xFFFFF304 ) /* (PDC_DBGU) Receive Counter Register */
#परिभाषय AT91C_DBGU_RNCR            ( ( AT91_REG * ) 0xFFFFF314 ) /* (PDC_DBGU) Receive Next Counter Register */
#परिभाषय AT91C_DBGU_PTCR            ( ( AT91_REG * ) 0xFFFFF320 ) /* (PDC_DBGU) PDC Transfer Control Register */
#परिभाषय AT91C_DBGU_PTSR            ( ( AT91_REG * ) 0xFFFFF324 ) /* (PDC_DBGU) PDC Transfer Status Register */
#परिभाषय AT91C_DBGU_TNCR            ( ( AT91_REG * ) 0xFFFFF31C ) /* (PDC_DBGU) Transmit Next Counter Register */
/* ========== Register definition for DBGU peripheral ========== */
#परिभाषय AT91C_DBGU_EXID            ( ( AT91_REG * ) 0xFFFFF244 ) /* (DBGU) Chip ID Extension Register */
#परिभाषय AT91C_DBGU_BRGR            ( ( AT91_REG * ) 0xFFFFF220 ) /* (DBGU) Baud Rate Generator Register */
#परिभाषय AT91C_DBGU_IDR             ( ( AT91_REG * ) 0xFFFFF20C ) /* (DBGU) Interrupt Disable Register */
#परिभाषय AT91C_DBGU_CSR             ( ( AT91_REG * ) 0xFFFFF214 ) /* (DBGU) Channel Status Register */
#परिभाषय AT91C_DBGU_CIDR            ( ( AT91_REG * ) 0xFFFFF240 ) /* (DBGU) Chip ID Register */
#परिभाषय AT91C_DBGU_MR              ( ( AT91_REG * ) 0xFFFFF204 ) /* (DBGU) Mode Register */
#परिभाषय AT91C_DBGU_IMR             ( ( AT91_REG * ) 0xFFFFF210 ) /* (DBGU) Interrupt Mask Register */
#परिभाषय AT91C_DBGU_CR              ( ( AT91_REG * ) 0xFFFFF200 ) /* (DBGU) Control Register */
#परिभाषय AT91C_DBGU_FNTR            ( ( AT91_REG * ) 0xFFFFF248 ) /* (DBGU) Force NTRST Register */
#परिभाषय AT91C_DBGU_THR             ( ( AT91_REG * ) 0xFFFFF21C ) /* (DBGU) Transmitter Holding Register */
#परिभाषय AT91C_DBGU_RHR             ( ( AT91_REG * ) 0xFFFFF218 ) /* (DBGU) Receiver Holding Register */
#परिभाषय AT91C_DBGU_IER             ( ( AT91_REG * ) 0xFFFFF208 ) /* (DBGU) Interrupt Enable Register */
/* ========== Register definition for PIOA peripheral ========== */
#परिभाषय AT91C_PIOA_ODR             ( ( AT91_REG * ) 0xFFFFF414 ) /* (PIOA) Output Disable Registerr */
#परिभाषय AT91C_PIOA_SODR            ( ( AT91_REG * ) 0xFFFFF430 ) /* (PIOA) Set Output Data Register */
#परिभाषय AT91C_PIOA_ISR             ( ( AT91_REG * ) 0xFFFFF44C ) /* (PIOA) Interrupt Status Register */
#परिभाषय AT91C_PIOA_ABSR            ( ( AT91_REG * ) 0xFFFFF478 ) /* (PIOA) AB Select Status Register */
#परिभाषय AT91C_PIOA_IER             ( ( AT91_REG * ) 0xFFFFF440 ) /* (PIOA) Interrupt Enable Register */
#परिभाषय AT91C_PIOA_PPUDR           ( ( AT91_REG * ) 0xFFFFF460 ) /* (PIOA) Pull-up Disable Register */
#परिभाषय AT91C_PIOA_IMR             ( ( AT91_REG * ) 0xFFFFF448 ) /* (PIOA) Interrupt Mask Register */
#परिभाषय AT91_C_PIOA_प्रत्येकम्             ( ( AT91_REG * ) 0xFFFFF400 ) /* (PIOA) PIO Enable Register */
#परिभाषय AT91C_PIOA_IFDR            ( ( AT91_REG * ) 0xFFFFF424 ) /* (PIOA) Input Filter Disable Register */
#परिभाषय AT91C_PIOA_OWDR            ( ( AT91_REG * ) 0xFFFFF4A4 ) /* (PIOA) Output Write Disable Register */
#परिभाषय AT91C_PIOA_MDSR            ( ( AT91_REG * ) 0xFFFFF458 ) /* (PIOA) Multi-driver Status Register */
#परिभाषय AT91C_PIOA_IDR             ( ( AT91_REG * ) 0xFFFFF444 ) /* (PIOA) Interrupt Disable Register */
#परिभाषय AT91C_PIOA_ODSR            ( ( AT91_REG * ) 0xFFFFF438 ) /* (PIOA) Output Data Status Register */
#परिभाषय AT91C_PIOA_PPUSR           ( ( AT91_REG * ) 0xFFFFF468 ) /* (PIOA) Pull-up Status Register */
#परिभाषय AT91C_PIOA_OWSR            ( ( AT91_REG * ) 0xFFFFF4A8 ) /* (PIOA) Output Write Status Register */
#परिभाषय AT91C_PIOA_BSR             ( ( AT91_REG * ) 0xFFFFF474 ) /* (PIOA) Select B Register */
#परिभाषय AT91C_PIOA_OWER            ( ( AT91_REG * ) 0xFFFFF4A0 ) /* (PIOA) Output Write Enable Register */
#परिभाषय AT91C_PIOA_IFER            ( ( AT91_REG * ) 0xFFFFF420 ) /* (PIOA) Input Filter Enable Register */
#परिभाषय AT91C_PIOA_PDSR            ( ( AT91_REG * ) 0xFFFFF43C ) /* (PIOA) Pin Data Status Register */
#परिभाषय AT91C_PIOA_PPUER           ( ( AT91_REG * ) 0xFFFFF464 ) /* (PIOA) Pull-up Enable Register */
#परिभाषय AT91C_PIOA_OSR             ( ( AT91_REG * ) 0xFFFFF418 ) /* (PIOA) Output Status Register */
#परिभाषय AT91C_PIOA_ASR             ( ( AT91_REG * ) 0xFFFFF470 ) /* (PIOA) Select A Register */
#परिभाषय AT91C_PIOA_MDDR            ( ( AT91_REG * ) 0xFFFFF454 ) /* (PIOA) Multi-driver Disable Register */
#परिभाषय AT91C_PIOA_CODR            ( ( AT91_REG * ) 0xFFFFF434 ) /* (PIOA) Clear Output Data Register */
#परिभाषय AT91C_PIOA_MDER            ( ( AT91_REG * ) 0xFFFFF450 ) /* (PIOA) Multi-driver Enable Register */
#परिभाषय AT91C_PIOA_PDR             ( ( AT91_REG * ) 0xFFFFF404 ) /* (PIOA) PIO Disable Register */
#परिभाषय AT91C_PIOA_IFSR            ( ( AT91_REG * ) 0xFFFFF428 ) /* (PIOA) Input Filter Status Register */
#परिभाषय AT91C_PIOA_OER             ( ( AT91_REG * ) 0xFFFFF410 ) /* (PIOA) Output Enable Register */
#परिभाषय AT91C_PIOA_PSR             ( ( AT91_REG * ) 0xFFFFF408 ) /* (PIOA) PIO Status Register */
/* ========== Register definition for PIOB peripheral ========== */
#परिभाषय AT91C_PIOB_OWDR            ( ( AT91_REG * ) 0xFFFFF6A4 ) /* (PIOB) Output Write Disable Register */
#परिभाषय AT91C_PIOB_MDER            ( ( AT91_REG * ) 0xFFFFF650 ) /* (PIOB) Multi-driver Enable Register */
#परिभाषय AT91C_PIOB_PPUSR           ( ( AT91_REG * ) 0xFFFFF668 ) /* (PIOB) Pull-up Status Register */
#परिभाषय AT91C_PIOB_IMR             ( ( AT91_REG * ) 0xFFFFF648 ) /* (PIOB) Interrupt Mask Register */
#परिभाषय AT91C_PIOB_ASR             ( ( AT91_REG * ) 0xFFFFF670 ) /* (PIOB) Select A Register */
#परिभाषय AT91C_PIOB_PPUDR           ( ( AT91_REG * ) 0xFFFFF660 ) /* (PIOB) Pull-up Disable Register */
#परिभाषय AT91C_PIOB_PSR             ( ( AT91_REG * ) 0xFFFFF608 ) /* (PIOB) PIO Status Register */
#परिभाषय AT91C_PIOB_IER             ( ( AT91_REG * ) 0xFFFFF640 ) /* (PIOB) Interrupt Enable Register */
#परिभाषय AT91C_PIOB_CODR            ( ( AT91_REG * ) 0xFFFFF634 ) /* (PIOB) Clear Output Data Register */
#परिभाषय AT91C_PIOB_OWER            ( ( AT91_REG * ) 0xFFFFF6A0 ) /* (PIOB) Output Write Enable Register */
#परिभाषय AT91C_PIOB_ABSR            ( ( AT91_REG * ) 0xFFFFF678 ) /* (PIOB) AB Select Status Register */
#परिभाषय AT91C_PIOB_IFDR            ( ( AT91_REG * ) 0xFFFFF624 ) /* (PIOB) Input Filter Disable Register */
#परिभाषय AT91C_PIOB_PDSR            ( ( AT91_REG * ) 0xFFFFF63C ) /* (PIOB) Pin Data Status Register */
#परिभाषय AT91C_PIOB_IDR             ( ( AT91_REG * ) 0xFFFFF644 ) /* (PIOB) Interrupt Disable Register */
#परिभाषय AT91C_PIOB_OWSR            ( ( AT91_REG * ) 0xFFFFF6A8 ) /* (PIOB) Output Write Status Register */
#परिभाषय AT91C_PIOB_PDR             ( ( AT91_REG * ) 0xFFFFF604 ) /* (PIOB) PIO Disable Register */
#परिभाषय AT91C_PIOB_ODR             ( ( AT91_REG * ) 0xFFFFF614 ) /* (PIOB) Output Disable Registerr */
#परिभाषय AT91C_PIOB_IFSR            ( ( AT91_REG * ) 0xFFFFF628 ) /* (PIOB) Input Filter Status Register */
#परिभाषय AT91C_PIOB_PPUER           ( ( AT91_REG * ) 0xFFFFF664 ) /* (PIOB) Pull-up Enable Register */
#परिभाषय AT91C_PIOB_SODR            ( ( AT91_REG * ) 0xFFFFF630 ) /* (PIOB) Set Output Data Register */
#परिभाषय AT91C_PIOB_ISR             ( ( AT91_REG * ) 0xFFFFF64C ) /* (PIOB) Interrupt Status Register */
#परिभाषय AT91C_PIOB_ODSR            ( ( AT91_REG * ) 0xFFFFF638 ) /* (PIOB) Output Data Status Register */
#परिभाषय AT91C_PIOB_OSR             ( ( AT91_REG * ) 0xFFFFF618 ) /* (PIOB) Output Status Register */
#परिभाषय AT91C_PIOB_MDSR            ( ( AT91_REG * ) 0xFFFFF658 ) /* (PIOB) Multi-driver Status Register */
#परिभाषय AT91C_PIOB_IFER            ( ( AT91_REG * ) 0xFFFFF620 ) /* (PIOB) Input Filter Enable Register */
#परिभाषय AT91C_PIOB_BSR             ( ( AT91_REG * ) 0xFFFFF674 ) /* (PIOB) Select B Register */
#परिभाषय AT91C_PIOB_MDDR            ( ( AT91_REG * ) 0xFFFFF654 ) /* (PIOB) Multi-driver Disable Register */
#परिभाषय AT91C_PIOB_OER             ( ( AT91_REG * ) 0xFFFFF610 ) /* (PIOB) Output Enable Register */
#परिभाषय AT91_C_PIOB_प्रत्येकम्             ( ( AT91_REG * ) 0xFFFFF600 ) /* (PIOB) PIO Enable Register */
/* ========== Register definition for CKGR peripheral ========== */
#परिभाषय AT91C_CKGR_MOR             ( ( AT91_REG * ) 0xFFFFFC20 ) /* (CKGR) Main Oscillator Register */
#परिभाषय AT91C_CKGR_PLLR            ( ( AT91_REG * ) 0xFFFFFC2C ) /* (CKGR) PLL Register */
#परिभाषय AT91C_CKGR_MCFR            ( ( AT91_REG * ) 0xFFFFFC24 ) /* (CKGR) Main Clock  Frequency Register */
/* ========== Register definition for PMC peripheral ========== */
#परिभाषय AT91C_PMC_IDR              ( ( AT91_REG * ) 0xFFFFFC64 ) /* (PMC) Interrupt Disable Register */
#परिभाषय AT91C_PMC_MOR              ( ( AT91_REG * ) 0xFFFFFC20 ) /* (PMC) Main Oscillator Register */
#परिभाषय AT91C_PMC_PLLR             ( ( AT91_REG * ) 0xFFFFFC2C ) /* (PMC) PLL Register */
#परिभाषय AT91C_PMC_PCER             ( ( AT91_REG * ) 0xFFFFFC10 ) /* (PMC) Peripheral Clock Enable Register */
#परिभाषय AT91C_PMC_PCKR             ( ( AT91_REG * ) 0xFFFFFC40 ) /* (PMC) Programmable Clock Register */
#परिभाषय AT91C_PMC_MCKR             ( ( AT91_REG * ) 0xFFFFFC30 ) /* (PMC) Master Clock Register */
#परिभाषय AT91C_PMC_SCDR             ( ( AT91_REG * ) 0xFFFFFC04 ) /* (PMC) System Clock Disable Register */
#परिभाषय AT91C_PMC_PCDR             ( ( AT91_REG * ) 0xFFFFFC14 ) /* (PMC) Peripheral Clock Disable Register */
#परिभाषय AT91C_PMC_SCSR             ( ( AT91_REG * ) 0xFFFFFC08 ) /* (PMC) System Clock Status Register */
#परिभाषय AT91C_PMC_PCSR             ( ( AT91_REG * ) 0xFFFFFC18 ) /* (PMC) Peripheral Clock Status Register */
#परिभाषय AT91C_PMC_MCFR             ( ( AT91_REG * ) 0xFFFFFC24 ) /* (PMC) Main Clock  Frequency Register */
#परिभाषय AT91C_PMC_SCER             ( ( AT91_REG * ) 0xFFFFFC00 ) /* (PMC) System Clock Enable Register */
#परिभाषय AT91C_PMC_IMR              ( ( AT91_REG * ) 0xFFFFFC6C ) /* (PMC) Interrupt Mask Register */
#परिभाषय AT91C_PMC_IER              ( ( AT91_REG * ) 0xFFFFFC60 ) /* (PMC) Interrupt Enable Register */
#परिभाषय AT91C_PMC_SR               ( ( AT91_REG * ) 0xFFFFFC68 ) /* (PMC) Status Register */
/* ========== Register definition for RSTC peripheral ========== */
#परिभाषय AT91C_RSTC_RCR             ( ( AT91_REG * ) 0xFFFFFD00 ) /* (RSTC) Reset Control Register */
#परिभाषय AT91C_RSTC_RMR             ( ( AT91_REG * ) 0xFFFFFD08 ) /* (RSTC) Reset Mode Register */
#परिभाषय AT91C_RSTC_RSR             ( ( AT91_REG * ) 0xFFFFFD04 ) /* (RSTC) Reset Status Register */
/* ========== Register definition for RTTC peripheral ========== */
#परिभाषय AT91C_RTTC_RTSR            ( ( AT91_REG * ) 0xFFFFFD2C ) /* (RTTC) Real-time Status Register */
#परिभाषय AT91C_RTTC_RTMR            ( ( AT91_REG * ) 0xFFFFFD20 ) /* (RTTC) Real-time Mode Register */
#परिभाषय AT91C_RTTC_RTVR            ( ( AT91_REG * ) 0xFFFFFD28 ) /* (RTTC) Real-time Value Register */
#परिभाषय AT91C_RTTC_RTAR            ( ( AT91_REG * ) 0xFFFFFD24 ) /* (RTTC) Real-time Alarm Register */
/* ========== Register definition for PITC peripheral ========== */
#परिभाषय AT91C_PITC_PIVR            ( ( AT91_REG * ) 0xFFFFFD38 ) /* (PITC) Period Interval Value Register */
#परिभाषय AT91C_PITC_PISR            ( ( AT91_REG * ) 0xFFFFFD34 ) /* (PITC) Period Interval Status Register */
#परिभाषय AT91C_PITC_PIIR            ( ( AT91_REG * ) 0xFFFFFD3C ) /* (PITC) Period Interval Image Register */
#परिभाषय AT91C_PITC_PIMR            ( ( AT91_REG * ) 0xFFFFFD30 ) /* (PITC) Period Interval Mode Register */
/* ========== Register definition for WDTC peripheral ========== */
#परिभाषय AT91C_WDTC_WDCR            ( ( AT91_REG * ) 0xFFFFFD40 ) /* (WDTC) Watchdog Control Register */
#परिभाषय AT91C_WDTC_WDSR            ( ( AT91_REG * ) 0xFFFFFD48 ) /* (WDTC) Watchdog Status Register */
#परिभाषय AT91C_WDTC_WDMR            ( ( AT91_REG * ) 0xFFFFFD44 ) /* (WDTC) Watchdog Mode Register */
/* ========== Register definition for VREG peripheral ========== */
#परिभाषय AT91C_VREG_MR              ( ( AT91_REG * ) 0xFFFFFD60 ) /* (VREG) Voltage Regulator Mode Register */
/* ========== Register definition for MC peripheral ========== */
#परिभाषय AT91C_MC_ASR               ( ( AT91_REG * ) 0xFFFFFF04 ) /* (MC) MC Abort Status Register */
#परिभाषय AT91C_MC_RCR               ( ( AT91_REG * ) 0xFFFFFF00 ) /* (MC) MC Remap Control Register */
#परिभाषय AT91C_MC_FCR               ( ( AT91_REG * ) 0xFFFFFF64 ) /* (MC) MC Flash Command Register */
#परिभाषय AT91C_MC_AASR              ( ( AT91_REG * ) 0xFFFFFF08 ) /* (MC) MC Abort Address Status Register */
#परिभाषय AT91C_MC_FSR               ( ( AT91_REG * ) 0xFFFFFF68 ) /* (MC) MC Flash Status Register */
#परिभाषय AT91C_MC_FMR               ( ( AT91_REG * ) 0xFFFFFF60 ) /* (MC) MC Flash Mode Register */
/* ========== Register definition for PDC_SPI1 peripheral ========== */
#परिभाषय AT91C_SPI1_PTCR            ( ( AT91_REG * ) 0xFFFE4120 ) /* (PDC_SPI1) PDC Transfer Control Register */
#परिभाषय AT91C_SPI1_RPR             ( ( AT91_REG * ) 0xFFFE4100 ) /* (PDC_SPI1) Receive Pointer Register */
#परिभाषय AT91C_SPI1_TNCR            ( ( AT91_REG * ) 0xFFFE411C ) /* (PDC_SPI1) Transmit Next Counter Register */
#परिभाषय AT91C_SPI1_TPR             ( ( AT91_REG * ) 0xFFFE4108 ) /* (PDC_SPI1) Transmit Pointer Register */
#परिभाषय AT91C_SPI1_TNPR            ( ( AT91_REG * ) 0xFFFE4118 ) /* (PDC_SPI1) Transmit Next Pointer Register */
#परिभाषय AT91C_SPI1_TCR             ( ( AT91_REG * ) 0xFFFE410C ) /* (PDC_SPI1) Transmit Counter Register */
#परिभाषय AT91C_SPI1_RCR             ( ( AT91_REG * ) 0xFFFE4104 ) /* (PDC_SPI1) Receive Counter Register */
#परिभाषय AT91C_SPI1_RNPR            ( ( AT91_REG * ) 0xFFFE4110 ) /* (PDC_SPI1) Receive Next Pointer Register */
#परिभाषय AT91C_SPI1_RNCR            ( ( AT91_REG * ) 0xFFFE4114 ) /* (PDC_SPI1) Receive Next Counter Register */
#परिभाषय AT91C_SPI1_PTSR            ( ( AT91_REG * ) 0xFFFE4124 ) /* (PDC_SPI1) PDC Transfer Status Register */
/* ========== Register definition for SPI1 peripheral ========== */
#परिभाषय AT91C_SPI1_IMR             ( ( AT91_REG * ) 0xFFFE401C ) /* (SPI1) Interrupt Mask Register */
#परिभाषय AT91C_SPI1_IER             ( ( AT91_REG * ) 0xFFFE4014 ) /* (SPI1) Interrupt Enable Register */
#परिभाषय AT91C_SPI1_MR              ( ( AT91_REG * ) 0xFFFE4004 ) /* (SPI1) Mode Register */
#परिभाषय AT91C_SPI1_RDR             ( ( AT91_REG * ) 0xFFFE4008 ) /* (SPI1) Receive Data Register */
#परिभाषय AT91C_SPI1_IDR             ( ( AT91_REG * ) 0xFFFE4018 ) /* (SPI1) Interrupt Disable Register */
#परिभाषय AT91C_SPI1_SR              ( ( AT91_REG * ) 0xFFFE4010 ) /* (SPI1) Status Register */
#परिभाषय AT91C_SPI1_TDR             ( ( AT91_REG * ) 0xFFFE400C ) /* (SPI1) Transmit Data Register */
#परिभाषय AT91C_SPI1_CR              ( ( AT91_REG * ) 0xFFFE4000 ) /* (SPI1) Control Register */
#परिभाषय AT91C_SPI1_CSR             ( ( AT91_REG * ) 0xFFFE4030 ) /* (SPI1) Chip Select Register */
/* ========== Register definition for PDC_SPI0 peripheral ========== */
#परिभाषय AT91C_SPI0_PTCR            ( ( AT91_REG * ) 0xFFFE0120 ) /* (PDC_SPI0) PDC Transfer Control Register */
#परिभाषय AT91C_SPI0_TPR             ( ( AT91_REG * ) 0xFFFE0108 ) /* (PDC_SPI0) Transmit Pointer Register */
#परिभाषय AT91C_SPI0_TCR             ( ( AT91_REG * ) 0xFFFE010C ) /* (PDC_SPI0) Transmit Counter Register */
#परिभाषय AT91C_SPI0_RCR             ( ( AT91_REG * ) 0xFFFE0104 ) /* (PDC_SPI0) Receive Counter Register */
#परिभाषय AT91C_SPI0_PTSR            ( ( AT91_REG * ) 0xFFFE0124 ) /* (PDC_SPI0) PDC Transfer Status Register */
#परिभाषय AT91C_SPI0_RNPR            ( ( AT91_REG * ) 0xFFFE0110 ) /* (PDC_SPI0) Receive Next Pointer Register */
#परिभाषय AT91C_SPI0_RPR             ( ( AT91_REG * ) 0xFFFE0100 ) /* (PDC_SPI0) Receive Pointer Register */
#परिभाषय AT91C_SPI0_TNCR            ( ( AT91_REG * ) 0xFFFE011C ) /* (PDC_SPI0) Transmit Next Counter Register */
#परिभाषय AT91C_SPI0_RNCR            ( ( AT91_REG * ) 0xFFFE0114 ) /* (PDC_SPI0) Receive Next Counter Register */
#परिभाषय AT91C_SPI0_TNPR            ( ( AT91_REG * ) 0xFFFE0118 ) /* (PDC_SPI0) Transmit Next Pointer Register */
/* ========== Register definition for SPI0 peripheral ========== */
#परिभाषय AT91C_SPI0_IER             ( ( AT91_REG * ) 0xFFFE0014 ) /* (SPI0) Interrupt Enable Register */
#परिभाषय AT91C_SPI0_SR              ( ( AT91_REG * ) 0xFFFE0010 ) /* (SPI0) Status Register */
#परिभाषय AT91C_SPI0_IDR             ( ( AT91_REG * ) 0xFFFE0018 ) /* (SPI0) Interrupt Disable Register */
#परिभाषय AT91C_SPI0_CR              ( ( AT91_REG * ) 0xFFFE0000 ) /* (SPI0) Control Register */
#परिभाषय AT91C_SPI0_MR              ( ( AT91_REG * ) 0xFFFE0004 ) /* (SPI0) Mode Register */
#परिभाषय AT91C_SPI0_IMR             ( ( AT91_REG * ) 0xFFFE001C ) /* (SPI0) Interrupt Mask Register */
#परिभाषय AT91C_SPI0_TDR             ( ( AT91_REG * ) 0xFFFE000C ) /* (SPI0) Transmit Data Register */
#परिभाषय AT91C_SPI0_RDR             ( ( AT91_REG * ) 0xFFFE0008 ) /* (SPI0) Receive Data Register */
#परिभाषय AT91C_SPI0_CSR             ( ( AT91_REG * ) 0xFFFE0030 ) /* (SPI0) Chip Select Register */
/* ========== Register definition for PDC_US1 peripheral ========== */
#परिभाषय AT91C_US1_RNCR             ( ( AT91_REG * ) 0xFFFC4114 ) /* (PDC_US1) Receive Next Counter Register */
#परिभाषय AT91C_US1_PTCR             ( ( AT91_REG * ) 0xFFFC4120 ) /* (PDC_US1) PDC Transfer Control Register */
#परिभाषय AT91C_US1_TCR              ( ( AT91_REG * ) 0xFFFC410C ) /* (PDC_US1) Transmit Counter Register */
#परिभाषय AT91C_US1_PTSR             ( ( AT91_REG * ) 0xFFFC4124 ) /* (PDC_US1) PDC Transfer Status Register */
#परिभाषय AT91C_US1_TNPR             ( ( AT91_REG * ) 0xFFFC4118 ) /* (PDC_US1) Transmit Next Pointer Register */
#परिभाषय AT91C_US1_RCR              ( ( AT91_REG * ) 0xFFFC4104 ) /* (PDC_US1) Receive Counter Register */
#परिभाषय AT91C_US1_RNPR             ( ( AT91_REG * ) 0xFFFC4110 ) /* (PDC_US1) Receive Next Pointer Register */
#परिभाषय AT91C_US1_RPR              ( ( AT91_REG * ) 0xFFFC4100 ) /* (PDC_US1) Receive Pointer Register */
#परिभाषय AT91C_US1_TNCR             ( ( AT91_REG * ) 0xFFFC411C ) /* (PDC_US1) Transmit Next Counter Register */
#परिभाषय AT91C_US1_TPR              ( ( AT91_REG * ) 0xFFFC4108 ) /* (PDC_US1) Transmit Pointer Register */
/* ========== Register definition for US1 peripheral ========== */
#परिभाषय AT91C_US1_IF               ( ( AT91_REG * ) 0xFFFC404C ) /* (US1) IRDA_FILTER Register */
#परिभाषय AT91C_US1_NER              ( ( AT91_REG * ) 0xFFFC4044 ) /* (US1) Nb Errors Register */
#परिभाषय AT91C_US1_RTOR             ( ( AT91_REG * ) 0xFFFC4024 ) /* (US1) Receiver Time-out Register */
#परिभाषय AT91C_US1_CSR              ( ( AT91_REG * ) 0xFFFC4014 ) /* (US1) Channel Status Register */
#परिभाषय AT91C_US1_IDR              ( ( AT91_REG * ) 0xFFFC400C ) /* (US1) Interrupt Disable Register */
#परिभाषय AT91C_US1_IER              ( ( AT91_REG * ) 0xFFFC4008 ) /* (US1) Interrupt Enable Register */
#परिभाषय AT91C_US1_THR              ( ( AT91_REG * ) 0xFFFC401C ) /* (US1) Transmitter Holding Register */
#परिभाषय AT91C_US1_TTGR             ( ( AT91_REG * ) 0xFFFC4028 ) /* (US1) Transmitter Time-guard Register */
#परिभाषय AT91C_US1_RHR              ( ( AT91_REG * ) 0xFFFC4018 ) /* (US1) Receiver Holding Register */
#परिभाषय AT91C_US1_BRGR             ( ( AT91_REG * ) 0xFFFC4020 ) /* (US1) Baud Rate Generator Register */
#परिभाषय AT91C_US1_IMR              ( ( AT91_REG * ) 0xFFFC4010 ) /* (US1) Interrupt Mask Register */
#परिभाषय AT91C_US1_FIDI             ( ( AT91_REG * ) 0xFFFC4040 ) /* (US1) FI_DI_Ratio Register */
#परिभाषय AT91C_US1_CR               ( ( AT91_REG * ) 0xFFFC4000 ) /* (US1) Control Register */
#परिभाषय AT91C_US1_MR               ( ( AT91_REG * ) 0xFFFC4004 ) /* (US1) Mode Register */
/* ========== Register definition for PDC_US0 peripheral ========== */
#परिभाषय AT91C_US0_TNPR             ( ( AT91_REG * ) 0xFFFC0118 ) /* (PDC_US0) Transmit Next Pointer Register */
#परिभाषय AT91C_US0_RNPR             ( ( AT91_REG * ) 0xFFFC0110 ) /* (PDC_US0) Receive Next Pointer Register */
#परिभाषय AT91C_US0_TCR              ( ( AT91_REG * ) 0xFFFC010C ) /* (PDC_US0) Transmit Counter Register */
#परिभाषय AT91C_US0_PTCR             ( ( AT91_REG * ) 0xFFFC0120 ) /* (PDC_US0) PDC Transfer Control Register */
#परिभाषय AT91C_US0_PTSR             ( ( AT91_REG * ) 0xFFFC0124 ) /* (PDC_US0) PDC Transfer Status Register */
#परिभाषय AT91C_US0_TNCR             ( ( AT91_REG * ) 0xFFFC011C ) /* (PDC_US0) Transmit Next Counter Register */
#परिभाषय AT91C_US0_TPR              ( ( AT91_REG * ) 0xFFFC0108 ) /* (PDC_US0) Transmit Pointer Register */
#परिभाषय AT91C_US0_RCR              ( ( AT91_REG * ) 0xFFFC0104 ) /* (PDC_US0) Receive Counter Register */
#परिभाषय AT91C_US0_RPR              ( ( AT91_REG * ) 0xFFFC0100 ) /* (PDC_US0) Receive Pointer Register */
#परिभाषय AT91C_US0_RNCR             ( ( AT91_REG * ) 0xFFFC0114 ) /* (PDC_US0) Receive Next Counter Register */
/* ========== Register definition for US0 peripheral ========== */
#परिभाषय AT91C_US0_BRGR             ( ( AT91_REG * ) 0xFFFC0020 ) /* (US0) Baud Rate Generator Register */
#परिभाषय AT91C_US0_NER              ( ( AT91_REG * ) 0xFFFC0044 ) /* (US0) Nb Errors Register */
#परिभाषय AT91C_US0_CR               ( ( AT91_REG * ) 0xFFFC0000 ) /* (US0) Control Register */
#परिभाषय AT91C_US0_IMR              ( ( AT91_REG * ) 0xFFFC0010 ) /* (US0) Interrupt Mask Register */
#परिभाषय AT91C_US0_FIDI             ( ( AT91_REG * ) 0xFFFC0040 ) /* (US0) FI_DI_Ratio Register */
#परिभाषय AT91C_US0_TTGR             ( ( AT91_REG * ) 0xFFFC0028 ) /* (US0) Transmitter Time-guard Register */
#परिभाषय AT91C_US0_MR               ( ( AT91_REG * ) 0xFFFC0004 ) /* (US0) Mode Register */
#परिभाषय AT91C_US0_RTOR             ( ( AT91_REG * ) 0xFFFC0024 ) /* (US0) Receiver Time-out Register */
#परिभाषय AT91C_US0_CSR              ( ( AT91_REG * ) 0xFFFC0014 ) /* (US0) Channel Status Register */
#परिभाषय AT91C_US0_RHR              ( ( AT91_REG * ) 0xFFFC0018 ) /* (US0) Receiver Holding Register */
#परिभाषय AT91C_US0_IDR              ( ( AT91_REG * ) 0xFFFC000C ) /* (US0) Interrupt Disable Register */
#परिभाषय AT91C_US0_THR              ( ( AT91_REG * ) 0xFFFC001C ) /* (US0) Transmitter Holding Register */
#परिभाषय AT91C_US0_IF               ( ( AT91_REG * ) 0xFFFC004C ) /* (US0) IRDA_FILTER Register */
#परिभाषय AT91C_US0_IER              ( ( AT91_REG * ) 0xFFFC0008 ) /* (US0) Interrupt Enable Register */
/* ========== Register definition for PDC_SSC peripheral ========== */
#परिभाषय AT91C_SSC_TNCR             ( ( AT91_REG * ) 0xFFFD411C ) /* (PDC_SSC) Transmit Next Counter Register */
#परिभाषय AT91C_SSC_RPR              ( ( AT91_REG * ) 0xFFFD4100 ) /* (PDC_SSC) Receive Pointer Register */
#परिभाषय AT91C_SSC_RNCR             ( ( AT91_REG * ) 0xFFFD4114 ) /* (PDC_SSC) Receive Next Counter Register */
#परिभाषय AT91C_SSC_TPR              ( ( AT91_REG * ) 0xFFFD4108 ) /* (PDC_SSC) Transmit Pointer Register */
#परिभाषय AT91C_SSC_PTCR             ( ( AT91_REG * ) 0xFFFD4120 ) /* (PDC_SSC) PDC Transfer Control Register */
#परिभाषय AT91C_SSC_TCR              ( ( AT91_REG * ) 0xFFFD410C ) /* (PDC_SSC) Transmit Counter Register */
#परिभाषय AT91C_SSC_RCR              ( ( AT91_REG * ) 0xFFFD4104 ) /* (PDC_SSC) Receive Counter Register */
#परिभाषय AT91C_SSC_RNPR             ( ( AT91_REG * ) 0xFFFD4110 ) /* (PDC_SSC) Receive Next Pointer Register */
#परिभाषय AT91C_SSC_TNPR             ( ( AT91_REG * ) 0xFFFD4118 ) /* (PDC_SSC) Transmit Next Pointer Register */
#परिभाषय AT91C_SSC_PTSR             ( ( AT91_REG * ) 0xFFFD4124 ) /* (PDC_SSC) PDC Transfer Status Register */
/* ========== Register definition for SSC peripheral ========== */
#परिभाषय AT91C_SSC_RHR              ( ( AT91_REG * ) 0xFFFD4020 ) /* (SSC) Receive Holding Register */
#परिभाषय AT91C_SSC_RSHR             ( ( AT91_REG * ) 0xFFFD4030 ) /* (SSC) Receive Sync Holding Register */
#परिभाषय AT91C_SSC_TFMR             ( ( AT91_REG * ) 0xFFFD401C ) /* (SSC) Transmit Frame Mode Register */
#परिभाषय AT91C_SSC_IDR              ( ( AT91_REG * ) 0xFFFD4048 ) /* (SSC) Interrupt Disable Register */
#परिभाषय AT91C_SSC_THR              ( ( AT91_REG * ) 0xFFFD4024 ) /* (SSC) Transmit Holding Register */
#परिभाषय AT91C_SSC_RCMR             ( ( AT91_REG * ) 0xFFFD4010 ) /* (SSC) Receive Clock ModeRegister */
#परिभाषय AT91C_SSC_IER              ( ( AT91_REG * ) 0xFFFD4044 ) /* (SSC) Interrupt Enable Register */
#परिभाषय AT91C_SSC_TSHR             ( ( AT91_REG * ) 0xFFFD4034 ) /* (SSC) Transmit Sync Holding Register */
#परिभाषय AT91C_SSC_SR               ( ( AT91_REG * ) 0xFFFD4040 ) /* (SSC) Status Register */
#परिभाषय AT91C_SSC_CMR              ( ( AT91_REG * ) 0xFFFD4004 ) /* (SSC) Clock Mode Register */
#परिभाषय AT91C_SSC_TCMR             ( ( AT91_REG * ) 0xFFFD4018 ) /* (SSC) Transmit Clock Mode Register */
#परिभाषय AT91C_SSC_CR               ( ( AT91_REG * ) 0xFFFD4000 ) /* (SSC) Control Register */
#परिभाषय AT91C_SSC_IMR              ( ( AT91_REG * ) 0xFFFD404C ) /* (SSC) Interrupt Mask Register */
#परिभाषय AT91C_SSC_RFMR             ( ( AT91_REG * ) 0xFFFD4014 ) /* (SSC) Receive Frame Mode Register */
/* ========== Register definition for TWI peripheral ========== */
#परिभाषय AT91C_TWI_IER              ( ( AT91_REG * ) 0xFFFB8024 ) /* (TWI) Interrupt Enable Register */
#परिभाषय AT91C_TWI_CR               ( ( AT91_REG * ) 0xFFFB8000 ) /* (TWI) Control Register */
#परिभाषय AT91C_TWI_SR               ( ( AT91_REG * ) 0xFFFB8020 ) /* (TWI) Status Register */
#परिभाषय AT91C_TWI_IMR              ( ( AT91_REG * ) 0xFFFB802C ) /* (TWI) Interrupt Mask Register */
#परिभाषय AT91C_TWI_THR              ( ( AT91_REG * ) 0xFFFB8034 ) /* (TWI) Transmit Holding Register */
#परिभाषय AT91C_TWI_IDR              ( ( AT91_REG * ) 0xFFFB8028 ) /* (TWI) Interrupt Disable Register */
#परिभाषय AT91C_TWI_IADR             ( ( AT91_REG * ) 0xFFFB800C ) /* (TWI) Internal Address Register */
#परिभाषय AT91C_TWI_MMR              ( ( AT91_REG * ) 0xFFFB8004 ) /* (TWI) Master Mode Register */
#परिभाषय AT91C_TWI_CWGR             ( ( AT91_REG * ) 0xFFFB8010 ) /* (TWI) Clock Waveform Generator Register */
#परिभाषय AT91C_TWI_RHR              ( ( AT91_REG * ) 0xFFFB8030 ) /* (TWI) Receive Holding Register */
/* ========== Register definition for PWMC_CH3 peripheral ========== */
#परिभाषय AT91C_PWMC_CH3_CUPDR       ( ( AT91_REG * ) 0xFFFCC270 ) /* (PWMC_CH3) Channel Update Register */
#परिभाषय AT91C_PWMC_CH3_Reserved    ( ( AT91_REG * ) 0xFFFCC274 ) /* (PWMC_CH3) Reserved */
#परिभाषय AT91C_PWMC_CH3_CPRDR       ( ( AT91_REG * ) 0xFFFCC268 ) /* (PWMC_CH3) Channel Period Register */
#परिभाषय AT91C_PWMC_CH3_CDTYR       ( ( AT91_REG * ) 0xFFFCC264 ) /* (PWMC_CH3) Channel Duty Cycle Register */
#परिभाषय AT91C_PWMC_CH3_CCNTR       ( ( AT91_REG * ) 0xFFFCC26C ) /* (PWMC_CH3) Channel Counter Register */
#परिभाषय AT91C_PWMC_CH3_CMR         ( ( AT91_REG * ) 0xFFFCC260 ) /* (PWMC_CH3) Channel Mode Register */
/* ========== Register definition for PWMC_CH2 peripheral ========== */
#परिभाषय AT91C_PWMC_CH2_Reserved    ( ( AT91_REG * ) 0xFFFCC254 ) /* (PWMC_CH2) Reserved */
#परिभाषय AT91C_PWMC_CH2_CMR         ( ( AT91_REG * ) 0xFFFCC240 ) /* (PWMC_CH2) Channel Mode Register */
#परिभाषय AT91C_PWMC_CH2_CCNTR       ( ( AT91_REG * ) 0xFFFCC24C ) /* (PWMC_CH2) Channel Counter Register */
#परिभाषय AT91C_PWMC_CH2_CPRDR       ( ( AT91_REG * ) 0xFFFCC248 ) /* (PWMC_CH2) Channel Period Register */
#परिभाषय AT91C_PWMC_CH2_CUPDR       ( ( AT91_REG * ) 0xFFFCC250 ) /* (PWMC_CH2) Channel Update Register */
#परिभाषय AT91C_PWMC_CH2_CDTYR       ( ( AT91_REG * ) 0xFFFCC244 ) /* (PWMC_CH2) Channel Duty Cycle Register */
/* ========== Register definition for PWMC_CH1 peripheral ========== */
#परिभाषय AT91C_PWMC_CH1_Reserved    ( ( AT91_REG * ) 0xFFFCC234 ) /* (PWMC_CH1) Reserved */
#परिभाषय AT91C_PWMC_CH1_CUPDR       ( ( AT91_REG * ) 0xFFFCC230 ) /* (PWMC_CH1) Channel Update Register */
#परिभाषय AT91C_PWMC_CH1_CPRDR       ( ( AT91_REG * ) 0xFFFCC228 ) /* (PWMC_CH1) Channel Period Register */
#परिभाषय AT91C_PWMC_CH1_CCNTR       ( ( AT91_REG * ) 0xFFFCC22C ) /* (PWMC_CH1) Channel Counter Register */
#परिभाषय AT91C_PWMC_CH1_CDTYR       ( ( AT91_REG * ) 0xFFFCC224 ) /* (PWMC_CH1) Channel Duty Cycle Register */
#परिभाषय AT91C_PWMC_CH1_CMR         ( ( AT91_REG * ) 0xFFFCC220 ) /* (PWMC_CH1) Channel Mode Register */
/* ========== Register definition for PWMC_CH0 peripheral ========== */
#परिभाषय AT91C_PWMC_CH0_Reserved    ( ( AT91_REG * ) 0xFFFCC214 ) /* (PWMC_CH0) Reserved */
#परिभाषय AT91C_PWMC_CH0_CPRDR       ( ( AT91_REG * ) 0xFFFCC208 ) /* (PWMC_CH0) Channel Period Register */
#परिभाषय AT91C_PWMC_CH0_CDTYR       ( ( AT91_REG * ) 0xFFFCC204 ) /* (PWMC_CH0) Channel Duty Cycle Register */
#परिभाषय AT91C_PWMC_CH0_CMR         ( ( AT91_REG * ) 0xFFFCC200 ) /* (PWMC_CH0) Channel Mode Register */
#परिभाषय AT91C_PWMC_CH0_CUPDR       ( ( AT91_REG * ) 0xFFFCC210 ) /* (PWMC_CH0) Channel Update Register */
#परिभाषय AT91C_PWMC_CH0_CCNTR       ( ( AT91_REG * ) 0xFFFCC20C ) /* (PWMC_CH0) Channel Counter Register */
/* ========== Register definition for PWMC peripheral ========== */
#परिभाषय AT91C_PWMC_IDR             ( ( AT91_REG * ) 0xFFFCC014 ) /* (PWMC) PWMC Interrupt Disable Register */
#परिभाषय AT91C_PWMC_DIS             ( ( AT91_REG * ) 0xFFFCC008 ) /* (PWMC) PWMC Disable Register */
#परिभाषय AT91C_PWMC_IER             ( ( AT91_REG * ) 0xFFFCC010 ) /* (PWMC) PWMC Interrupt Enable Register */
#परिभाषय AT91C_PWMC_VR              ( ( AT91_REG * ) 0xFFFCC0FC ) /* (PWMC) PWMC Version Register */
#परिभाषय AT91C_PWMC_ISR             ( ( AT91_REG * ) 0xFFFCC01C ) /* (PWMC) PWMC Interrupt Status Register */
#परिभाषय AT91C_PWMC_SR              ( ( AT91_REG * ) 0xFFFCC00C ) /* (PWMC) PWMC Status Register */
#परिभाषय AT91C_PWMC_IMR             ( ( AT91_REG * ) 0xFFFCC018 ) /* (PWMC) PWMC Interrupt Mask Register */
#परिभाषय AT91C_PWMC_MR              ( ( AT91_REG * ) 0xFFFCC000 ) /* (PWMC) PWMC Mode Register */
#परिभाषय AT91C_PWMC_ENA             ( ( AT91_REG * ) 0xFFFCC004 ) /* (PWMC) PWMC Enable Register */
/* ========== Register definition for UDP peripheral ========== */
#परिभाषय AT91C_UDP_IMR              ( ( AT91_REG * ) 0xFFFB0018 ) /* (UDP) Interrupt Mask Register */
#परिभाषय AT91C_UDP_FADDR            ( ( AT91_REG * ) 0xFFFB0008 ) /* (UDP) Function Address Register */
#परिभाषय AT91_C_UDP_अङ्कः              ( ( AT91_REG * ) 0xFFFB0000 ) /* (UDP) Frame Number Register */
#परिभाषय AT91C_UDP_FDR              ( ( AT91_REG * ) 0xFFFB0050 ) /* (UDP) Endpoint FIFO Data Register */
#परिभाषय AT91C_UDP_ISR              ( ( AT91_REG * ) 0xFFFB001C ) /* (UDP) Interrupt Status Register */
#परिभाषय AT91C_UDP_CSR              ( ( AT91_REG * ) 0xFFFB0030 ) /* (UDP) Endpoint Control and Status Register */
#परिभाषय AT91C_UDP_IDR              ( ( AT91_REG * ) 0xFFFB0014 ) /* (UDP) Interrupt Disable Register */
#परिभाषय AT91C_UDP_ICR              ( ( AT91_REG * ) 0xFFFB0020 ) /* (UDP) Interrupt Clear Register */
#परिभाषय AT91C_UDP_RSTEP            ( ( AT91_REG * ) 0xFFFB0028 ) /* (UDP) Reset Endpoint Register */
#परिभाषय AT91C_UDP_TXVC             ( ( AT91_REG * ) 0xFFFB0074 ) /* (UDP) Transceiver Control Register */
#परिभाषय AT91C_UDP_GLBSTATE         ( ( AT91_REG * ) 0xFFFB0004 ) /* (UDP) Global State Register */
#परिभाषय AT91C_UDP_IER              ( ( AT91_REG * ) 0xFFFB0010 ) /* (UDP) Interrupt Enable Register */
/* ========== Register definition for TC0 peripheral ========== */
#परिभाषय AT91C_TC0_SR               ( ( AT91_REG * ) 0xFFFA0020 ) /* (TC0) Status Register */
#परिभाषय AT91C_TC0_RC               ( ( AT91_REG * ) 0xFFFA001C ) /* (TC0) Register C */
#परिभाषय AT91C_TC0_RB               ( ( AT91_REG * ) 0xFFFA0018 ) /* (TC0) Register B */
#परिभाषय AT91C_TC0_CCR              ( ( AT91_REG * ) 0xFFFA0000 ) /* (TC0) Channel Control Register */
#परिभाषय AT91C_TC0_CMR              ( ( AT91_REG * ) 0xFFFA0004 ) /* (TC0) Channel Mode Register (Capture Mode / Waveform Mode) */
#परिभाषय AT91C_TC0_IER              ( ( AT91_REG * ) 0xFFFA0024 ) /* (TC0) Interrupt Enable Register */
#परिभाषय AT91C_TC0_RA               ( ( AT91_REG * ) 0xFFFA0014 ) /* (TC0) Register A */
#परिभाषय AT91C_TC0_IDR              ( ( AT91_REG * ) 0xFFFA0028 ) /* (TC0) Interrupt Disable Register */
#परिभाषय AT91C_TC0_CV               ( ( AT91_REG * ) 0xFFFA0010 ) /* (TC0) Counter Value */
#परिभाषय AT91C_TC0_IMR              ( ( AT91_REG * ) 0xFFFA002C ) /* (TC0) Interrupt Mask Register */
/* ========== Register definition for TC1 peripheral ========== */
#परिभाषय AT91C_TC1_RB               ( ( AT91_REG * ) 0xFFFA0058 ) /* (TC1) Register B */
#परिभाषय AT91C_TC1_CCR              ( ( AT91_REG * ) 0xFFFA0040 ) /* (TC1) Channel Control Register */
#परिभाषय AT91C_TC1_IER              ( ( AT91_REG * ) 0xFFFA0064 ) /* (TC1) Interrupt Enable Register */
#परिभाषय AT91C_TC1_IDR              ( ( AT91_REG * ) 0xFFFA0068 ) /* (TC1) Interrupt Disable Register */
#परिभाषय AT91C_TC1_SR               ( ( AT91_REG * ) 0xFFFA0060 ) /* (TC1) Status Register */
#परिभाषय AT91C_TC1_CMR              ( ( AT91_REG * ) 0xFFFA0044 ) /* (TC1) Channel Mode Register (Capture Mode / Waveform Mode) */
#परिभाषय AT91C_TC1_RA               ( ( AT91_REG * ) 0xFFFA0054 ) /* (TC1) Register A */
#परिभाषय AT91C_TC1_RC               ( ( AT91_REG * ) 0xFFFA005C ) /* (TC1) Register C */
#परिभाषय AT91C_TC1_IMR              ( ( AT91_REG * ) 0xFFFA006C ) /* (TC1) Interrupt Mask Register */
#परिभाषय AT91C_TC1_CV               ( ( AT91_REG * ) 0xFFFA0050 ) /* (TC1) Counter Value */
/* ========== Register definition for TC2 peripheral ========== */
#परिभाषय AT91C_TC2_CMR              ( ( AT91_REG * ) 0xFFFA0084 ) /* (TC2) Channel Mode Register (Capture Mode / Waveform Mode) */
#परिभाषय AT91C_TC2_CCR              ( ( AT91_REG * ) 0xFFFA0080 ) /* (TC2) Channel Control Register */
#परिभाषय AT91C_TC2_CV               ( ( AT91_REG * ) 0xFFFA0090 ) /* (TC2) Counter Value */
#परिभाषय AT91C_TC2_RA               ( ( AT91_REG * ) 0xFFFA0094 ) /* (TC2) Register A */
#परिभाषय AT91C_TC2_RB               ( ( AT91_REG * ) 0xFFFA0098 ) /* (TC2) Register B */
#परिभाषय AT91C_TC2_IDR              ( ( AT91_REG * ) 0xFFFA00A8 ) /* (TC2) Interrupt Disable Register */
#परिभाषय AT91C_TC2_IMR              ( ( AT91_REG * ) 0xFFFA00AC ) /* (TC2) Interrupt Mask Register */
#परिभाषय AT91C_TC2_RC               ( ( AT91_REG * ) 0xFFFA009C ) /* (TC2) Register C */
#परिभाषय AT91C_TC2_IER              ( ( AT91_REG * ) 0xFFFA00A4 ) /* (TC2) Interrupt Enable Register */
#परिभाषय AT91C_TC2_SR               ( ( AT91_REG * ) 0xFFFA00A0 ) /* (TC2) Status Register */
/* ========== Register definition for TCB peripheral ========== */
#परिभाषय AT91C_TCB_BMR              ( ( AT91_REG * ) 0xFFFA00C4 ) /* (TCB) TC Block Mode Register */
#परिभाषय AT91C_TCB_BCR              ( ( AT91_REG * ) 0xFFFA00C0 ) /* (TCB) TC Block Control Register */
/* ========== Register definition for CAN_MB0 peripheral ========== */
#परिभाषय AT91C_CAN_MB0_MDL          ( ( AT91_REG * ) 0xFFFD0214 ) /* (CAN_MB0) MailBox Data Low Register */
#परिभाषय AT91C_CAN_MB0_MAM          ( ( AT91_REG * ) 0xFFFD0204 ) /* (CAN_MB0) MailBox Acceptance Mask Register */
#परिभाषय AT91C_CAN_MB0_MCR          ( ( AT91_REG * ) 0xFFFD021C ) /* (CAN_MB0) MailBox Control Register */
#परिभाषय AT91C_CAN_MB0_MID          ( ( AT91_REG * ) 0xFFFD0208 ) /* (CAN_MB0) MailBox ID Register */
#परिभाषय AT91C_CAN_MB0_MSR          ( ( AT91_REG * ) 0xFFFD0210 ) /* (CAN_MB0) MailBox Status Register */
#परिभाषय AT91C_CAN_MB0_MFID         ( ( AT91_REG * ) 0xFFFD020C ) /* (CAN_MB0) MailBox Family ID Register */
#परिभाषय AT91C_CAN_MB0_MDH          ( ( AT91_REG * ) 0xFFFD0218 ) /* (CAN_MB0) MailBox Data High Register */
#परिभाषय AT91C_CAN_MB0_MMR          ( ( AT91_REG * ) 0xFFFD0200 ) /* (CAN_MB0) MailBox Mode Register */
/* ========== Register definition for CAN_MB1 peripheral ========== */
#परिभाषय AT91C_CAN_MB1_MDL          ( ( AT91_REG * ) 0xFFFD0234 ) /* (CAN_MB1) MailBox Data Low Register */
#परिभाषय AT91C_CAN_MB1_MID          ( ( AT91_REG * ) 0xFFFD0228 ) /* (CAN_MB1) MailBox ID Register */
#परिभाषय AT91C_CAN_MB1_MMR          ( ( AT91_REG * ) 0xFFFD0220 ) /* (CAN_MB1) MailBox Mode Register */
#परिभाषय AT91C_CAN_MB1_MSR          ( ( AT91_REG * ) 0xFFFD0230 ) /* (CAN_MB1) MailBox Status Register */
#परिभाषय AT91C_CAN_MB1_MAM          ( ( AT91_REG * ) 0xFFFD0224 ) /* (CAN_MB1) MailBox Acceptance Mask Register */
#परिभाषय AT91C_CAN_MB1_MDH          ( ( AT91_REG * ) 0xFFFD0238 ) /* (CAN_MB1) MailBox Data High Register */
#परिभाषय AT91C_CAN_MB1_MCR          ( ( AT91_REG * ) 0xFFFD023C ) /* (CAN_MB1) MailBox Control Register */
#परिभाषय AT91C_CAN_MB1_MFID         ( ( AT91_REG * ) 0xFFFD022C ) /* (CAN_MB1) MailBox Family ID Register */
/* ========== Register definition for CAN_MB2 peripheral ========== */
#परिभाषय AT91C_CAN_MB2_MCR          ( ( AT91_REG * ) 0xFFFD025C ) /* (CAN_MB2) MailBox Control Register */
#परिभाषय AT91C_CAN_MB2_MDH          ( ( AT91_REG * ) 0xFFFD0258 ) /* (CAN_MB2) MailBox Data High Register */
#परिभाषय AT91C_CAN_MB2_MID          ( ( AT91_REG * ) 0xFFFD0248 ) /* (CAN_MB2) MailBox ID Register */
#परिभाषय AT91C_CAN_MB2_MDL          ( ( AT91_REG * ) 0xFFFD0254 ) /* (CAN_MB2) MailBox Data Low Register */
#परिभाषय AT91C_CAN_MB2_MMR          ( ( AT91_REG * ) 0xFFFD0240 ) /* (CAN_MB2) MailBox Mode Register */
#परिभाषय AT91C_CAN_MB2_MAM          ( ( AT91_REG * ) 0xFFFD0244 ) /* (CAN_MB2) MailBox Acceptance Mask Register */
#परिभाषय AT91C_CAN_MB2_MFID         ( ( AT91_REG * ) 0xFFFD024C ) /* (CAN_MB2) MailBox Family ID Register */
#परिभाषय AT91C_CAN_MB2_MSR          ( ( AT91_REG * ) 0xFFFD0250 ) /* (CAN_MB2) MailBox Status Register */
/* ========== Register definition for CAN_MB3 peripheral ========== */
#परिभाषय AT91C_CAN_MB3_MFID         ( ( AT91_REG * ) 0xFFFD026C ) /* (CAN_MB3) MailBox Family ID Register */
#परिभाषय AT91C_CAN_MB3_MAM          ( ( AT91_REG * ) 0xFFFD0264 ) /* (CAN_MB3) MailBox Acceptance Mask Register */
#परिभाषय AT91C_CAN_MB3_MID          ( ( AT91_REG * ) 0xFFFD0268 ) /* (CAN_MB3) MailBox ID Register */
#परिभाषय AT91C_CAN_MB3_MCR          ( ( AT91_REG * ) 0xFFFD027C ) /* (CAN_MB3) MailBox Control Register */
#परिभाषय AT91C_CAN_MB3_MMR          ( ( AT91_REG * ) 0xFFFD0260 ) /* (CAN_MB3) MailBox Mode Register */
#परिभाषय AT91C_CAN_MB3_MSR          ( ( AT91_REG * ) 0xFFFD0270 ) /* (CAN_MB3) MailBox Status Register */
#परिभाषय AT91C_CAN_MB3_MDL          ( ( AT91_REG * ) 0xFFFD0274 ) /* (CAN_MB3) MailBox Data Low Register */
#परिभाषय AT91C_CAN_MB3_MDH          ( ( AT91_REG * ) 0xFFFD0278 ) /* (CAN_MB3) MailBox Data High Register */
/* ========== Register definition for CAN_MB4 peripheral ========== */
#परिभाषय AT91C_CAN_MB4_MID          ( ( AT91_REG * ) 0xFFFD0288 ) /* (CAN_MB4) MailBox ID Register */
#परिभाषय AT91C_CAN_MB4_MMR          ( ( AT91_REG * ) 0xFFFD0280 ) /* (CAN_MB4) MailBox Mode Register */
#परिभाषय AT91C_CAN_MB4_MDH          ( ( AT91_REG * ) 0xFFFD0298 ) /* (CAN_MB4) MailBox Data High Register */
#परिभाषय AT91C_CAN_MB4_MFID         ( ( AT91_REG * ) 0xFFFD028C ) /* (CAN_MB4) MailBox Family ID Register */
#परिभाषय AT91C_CAN_MB4_MSR          ( ( AT91_REG * ) 0xFFFD0290 ) /* (CAN_MB4) MailBox Status Register */
#परिभाषय AT91C_CAN_MB4_MCR          ( ( AT91_REG * ) 0xFFFD029C ) /* (CAN_MB4) MailBox Control Register */
#परिभाषय AT91C_CAN_MB4_MDL          ( ( AT91_REG * ) 0xFFFD0294 ) /* (CAN_MB4) MailBox Data Low Register */
#परिभाषय AT91C_CAN_MB4_MAM          ( ( AT91_REG * ) 0xFFFD0284 ) /* (CAN_MB4) MailBox Acceptance Mask Register */
/* ========== Register definition for CAN_MB5 peripheral ========== */
#परिभाषय AT91C_CAN_MB5_MSR          ( ( AT91_REG * ) 0xFFFD02B0 ) /* (CAN_MB5) MailBox Status Register */
#परिभाषय AT91C_CAN_MB5_MCR          ( ( AT91_REG * ) 0xFFFD02BC ) /* (CAN_MB5) MailBox Control Register */
#परिभाषय AT91C_CAN_MB5_MFID         ( ( AT91_REG * ) 0xFFFD02AC ) /* (CAN_MB5) MailBox Family ID Register */
#परिभाषय AT91C_CAN_MB5_MDH          ( ( AT91_REG * ) 0xFFFD02B8 ) /* (CAN_MB5) MailBox Data High Register */
#परिभाषय AT91C_CAN_MB5_MID          ( ( AT91_REG * ) 0xFFFD02A8 ) /* (CAN_MB5) MailBox ID Register */
#परिभाषय AT91C_CAN_MB5_MMR          ( ( AT91_REG * ) 0xFFFD02A0 ) /* (CAN_MB5) MailBox Mode Register */
#परिभाषय AT91C_CAN_MB5_MDL          ( ( AT91_REG * ) 0xFFFD02B4 ) /* (CAN_MB5) MailBox Data Low Register */
#परिभाषय AT91C_CAN_MB5_MAM          ( ( AT91_REG * ) 0xFFFD02A4 ) /* (CAN_MB5) MailBox Acceptance Mask Register */
/* ========== Register definition for CAN_MB6 peripheral ========== */
#परिभाषय AT91C_CAN_MB6_MFID         ( ( AT91_REG * ) 0xFFFD02CC ) /* (CAN_MB6) MailBox Family ID Register */
#परिभाषय AT91C_CAN_MB6_MID          ( ( AT91_REG * ) 0xFFFD02C8 ) /* (CAN_MB6) MailBox ID Register */
#परिभाषय AT91C_CAN_MB6_MAM          ( ( AT91_REG * ) 0xFFFD02C4 ) /* (CAN_MB6) MailBox Acceptance Mask Register */
#परिभाषय AT91C_CAN_MB6_MSR          ( ( AT91_REG * ) 0xFFFD02D0 ) /* (CAN_MB6) MailBox Status Register */
#परिभाषय AT91C_CAN_MB6_MDL          ( ( AT91_REG * ) 0xFFFD02D4 ) /* (CAN_MB6) MailBox Data Low Register */
#परिभाषय AT91C_CAN_MB6_MCR          ( ( AT91_REG * ) 0xFFFD02DC ) /* (CAN_MB6) MailBox Control Register */
#परिभाषय AT91C_CAN_MB6_MDH          ( ( AT91_REG * ) 0xFFFD02D8 ) /* (CAN_MB6) MailBox Data High Register */
#परिभाषय AT91C_CAN_MB6_MMR          ( ( AT91_REG * ) 0xFFFD02C0 ) /* (CAN_MB6) MailBox Mode Register */
/* ========== Register definition for CAN_MB7 peripheral ========== */
#परिभाषय AT91C_CAN_MB7_MCR          ( ( AT91_REG * ) 0xFFFD02FC ) /* (CAN_MB7) MailBox Control Register */
#परिभाषय AT91C_CAN_MB7_MDH          ( ( AT91_REG * ) 0xFFFD02F8 ) /* (CAN_MB7) MailBox Data High Register */
#परिभाषय AT91C_CAN_MB7_MFID         ( ( AT91_REG * ) 0xFFFD02EC ) /* (CAN_MB7) MailBox Family ID Register */
#परिभाषय AT91C_CAN_MB7_MDL          ( ( AT91_REG * ) 0xFFFD02F4 ) /* (CAN_MB7) MailBox Data Low Register */
#परिभाषय AT91C_CAN_MB7_MID          ( ( AT91_REG * ) 0xFFFD02E8 ) /* (CAN_MB7) MailBox ID Register */
#परिभाषय AT91C_CAN_MB7_MMR          ( ( AT91_REG * ) 0xFFFD02E0 ) /* (CAN_MB7) MailBox Mode Register */
#परिभाषय AT91C_CAN_MB7_MAM          ( ( AT91_REG * ) 0xFFFD02E4 ) /* (CAN_MB7) MailBox Acceptance Mask Register */
#परिभाषय AT91C_CAN_MB7_MSR          ( ( AT91_REG * ) 0xFFFD02F0 ) /* (CAN_MB7) MailBox Status Register */
/* ========== Register definition for CAN peripheral ========== */
#परिभाषय AT91C_CAN_TCR              ( ( AT91_REG * ) 0xFFFD0024 ) /* (CAN) Transfer Command Register */
#परिभाषय AT91C_CAN_IMR              ( ( AT91_REG * ) 0xFFFD000C ) /* (CAN) Interrupt Mask Register */
#परिभाषय AT91C_CAN_IER              ( ( AT91_REG * ) 0xFFFD0004 ) /* (CAN) Interrupt Enable Register */
#परिभाषय AT91C_CAN_ECR              ( ( AT91_REG * ) 0xFFFD0020 ) /* (CAN) Error Counter Register */
#परिभाषय AT91C_CAN_TIMESTP          ( ( AT91_REG * ) 0xFFFD001C ) /* (CAN) Time Stamp Register */
#परिभाषय AT91C_CAN_MR               ( ( AT91_REG * ) 0xFFFD0000 ) /* (CAN) Mode Register */
#परिभाषय AT91C_CAN_IDR              ( ( AT91_REG * ) 0xFFFD0008 ) /* (CAN) Interrupt Disable Register */
#परिभाषय AT91C_CAN_ACR              ( ( AT91_REG * ) 0xFFFD0028 ) /* (CAN) Abort Command Register */
#परिभाषय AT91C_CAN_TIM              ( ( AT91_REG * ) 0xFFFD0018 ) /* (CAN) Timer Register */
#परिभाषय AT91C_CAN_SR               ( ( AT91_REG * ) 0xFFFD0010 ) /* (CAN) Status Register */
#परिभाषय AT91C_CAN_BR               ( ( AT91_REG * ) 0xFFFD0014 ) /* (CAN) Baudrate Register */
#परिभाषय AT91C_CAN_VR               ( ( AT91_REG * ) 0xFFFD00FC ) /* (CAN) Version Register */
/* ========== Register definition for EMAC peripheral ========== */
#परिभाषय AT91C_EMAC_ISR             ( ( AT91_REG * ) 0xFFFDC024 ) /* (EMAC) Interrupt Status Register */
#परिभाषय AT91C_EMAC_SA4H            ( ( AT91_REG * ) 0xFFFDC0B4 ) /* (EMAC) Specific Address 4 Top, Last 2 bytes */
#परिभाषय AT91C_EMAC_SA1L            ( ( AT91_REG * ) 0xFFFDC098 ) /* (EMAC) Specific Address 1 Bottom, First 4 bytes */
#परिभाषय AT91C_EMAC_ELE             ( ( AT91_REG * ) 0xFFFDC078 ) /* (EMAC) Excessive Length Errors Register */
#परिभाषय AT91C_EMAC_LCOL            ( ( AT91_REG * ) 0xFFFDC05C ) /* (EMAC) Late Collision Register */
#परिभाषय AT91C_EMAC_RLE             ( ( AT91_REG * ) 0xFFFDC088 ) /* (EMAC) Receive Length Field Mismatch Register */
#परिभाषय AT91C_EMAC_WOL             ( ( AT91_REG * ) 0xFFFDC0C4 ) /* (EMAC) Wake On LAN Register */
#परिभाषय AT91C_EMAC_DTF             ( ( AT91_REG * ) 0xFFFDC058 ) /* (EMAC) Deferred Transmission Frame Register */
#परिभाषय AT91C_EMAC_TUND            ( ( AT91_REG * ) 0xFFFDC064 ) /* (EMAC) Transmit Underrun Error Register */
#परिभाषय AT91C_EMAC_NCR             ( ( AT91_REG * ) 0xFFFDC000 ) /* (EMAC) Network Control Register */
#परिभाषय AT91C_EMAC_SA4L            ( ( AT91_REG * ) 0xFFFDC0B0 ) /* (EMAC) Specific Address 4 Bottom, First 4 bytes */
#परिभाषय AT91C_EMAC_RSR             ( ( AT91_REG * ) 0xFFFDC020 ) /* (EMAC) Receive Status Register */
#परिभाषय AT91C_EMAC_SA3L            ( ( AT91_REG * ) 0xFFFDC0A8 ) /* (EMAC) Specific Address 3 Bottom, First 4 bytes */
#परिभाषय AT91C_EMAC_TSR             ( ( AT91_REG * ) 0xFFFDC014 ) /* (EMAC) Transmit Status Register */
#परिभाषय AT91C_EMAC_IDR             ( ( AT91_REG * ) 0xFFFDC02C ) /* (EMAC) Interrupt Disable Register */
#परिभाषय AT91C_EMAC_RSE             ( ( AT91_REG * ) 0xFFFDC074 ) /* (EMAC) Receive Symbol Errors Register */
#परिभाषय AT91C_EMAC_ECOL            ( ( AT91_REG * ) 0xFFFDC060 ) /* (EMAC) Excessive Collision Register */
#परिभाषय AT91C_EMAC_TID             ( ( AT91_REG * ) 0xFFFDC0B8 ) /* (EMAC) Type ID Checking Register */
#परिभाषय AT91C_EMAC_HRB             ( ( AT91_REG * ) 0xFFFDC090 ) /* (EMAC) Hash Address Bottom[31:0] */
#परिभाषय AT91C_EMAC_TBQP            ( ( AT91_REG * ) 0xFFFDC01C ) /* (EMAC) Transmit Buffer Queue Pointer */
#परिभाषय AT91C_EMAC_USRIO           ( ( AT91_REG * ) 0xFFFDC0C0 ) /* (EMAC) USER Input/Output Register */
#परिभाषय AT91C_EMAC_PTR             ( ( AT91_REG * ) 0xFFFDC038 ) /* (EMAC) Pause Time Register */
#परिभाषय AT91C_EMAC_SA2H            ( ( AT91_REG * ) 0xFFFDC0A4 ) /* (EMAC) Specific Address 2 Top, Last 2 bytes */
#परिभाषय AT91C_EMAC_ROV             ( ( AT91_REG * ) 0xFFFDC070 ) /* (EMAC) Receive Overrun Errors Register */
#परिभाषय AT91C_EMAC_ALE             ( ( AT91_REG * ) 0xFFFDC054 ) /* (EMAC) Alignment Error Register */
#परिभाषय AT91C_EMAC_RJA             ( ( AT91_REG * ) 0xFFFDC07C ) /* (EMAC) Receive Jabbers Register */
#परिभाषय AT91C_EMAC_RBQP            ( ( AT91_REG * ) 0xFFFDC018 ) /* (EMAC) Receive Buffer Queue Pointer */
#परिभाषय AT91C_EMAC_TPF             ( ( AT91_REG * ) 0xFFFDC08C ) /* (EMAC) Transmitted Pause Frames Register */
#परिभाषय AT91C_EMAC_NCFGR           ( ( AT91_REG * ) 0xFFFDC004 ) /* (EMAC) Network Configuration Register */
#परिभाषय AT91C_EMAC_HRT             ( ( AT91_REG * ) 0xFFFDC094 ) /* (EMAC) Hash Address Top[63:32] */
#परिभाषय AT91C_EMAC_USF             ( ( AT91_REG * ) 0xFFFDC080 ) /* (EMAC) Undersize Frames Register */
#परिभाषय AT91C_EMAC_FCSE            ( ( AT91_REG * ) 0xFFFDC050 ) /* (EMAC) Frame Check Sequence Error Register */
#परिभाषय AT91C_EMAC_TPQ             ( ( AT91_REG * ) 0xFFFDC0BC ) /* (EMAC) Transmit Pause Quantum Register */
#परिभाषय AT91C_EMAC_MAN             ( ( AT91_REG * ) 0xFFFDC034 ) /* (EMAC) PHY Maintenance Register */
#परिभाषय AT91C_EMAC_FTO             ( ( AT91_REG * ) 0xFFFDC040 ) /* (EMAC) Frames Transmitted OK Register */
#परिभाषय AT91C_EMAC_REV             ( ( AT91_REG * ) 0xFFFDC0FC ) /* (EMAC) Revision Register */
#परिभाषय AT91C_EMAC_IMR             ( ( AT91_REG * ) 0xFFFDC030 ) /* (EMAC) Interrupt Mask Register */
#परिभाषय AT91C_EMAC_SCF             ( ( AT91_REG * ) 0xFFFDC044 ) /* (EMAC) Single Collision Frame Register */
#परिभाषय AT91C_EMAC_PFR             ( ( AT91_REG * ) 0xFFFDC03C ) /* (EMAC) Pause Frames received Register */
#परिभाषय AT91C_EMAC_MCF             ( ( AT91_REG * ) 0xFFFDC048 ) /* (EMAC) Multiple Collision Frame Register */
#परिभाषय AT91C_EMAC_NSR             ( ( AT91_REG * ) 0xFFFDC008 ) /* (EMAC) Network Status Register */
#परिभाषय AT91C_EMAC_SA2L            ( ( AT91_REG * ) 0xFFFDC0A0 ) /* (EMAC) Specific Address 2 Bottom, First 4 bytes */
#परिभाषय AT91C_EMAC_FRO             ( ( AT91_REG * ) 0xFFFDC04C ) /* (EMAC) Frames Received OK Register */
#परिभाषय AT91C_EMAC_IER             ( ( AT91_REG * ) 0xFFFDC028 ) /* (EMAC) Interrupt Enable Register */
#परिभाषय AT91C_EMAC_SA1H            ( ( AT91_REG * ) 0xFFFDC09C ) /* (EMAC) Specific Address 1 Top, Last 2 bytes */
#परिभाषय AT91C_EMAC_CSE             ( ( AT91_REG * ) 0xFFFDC068 ) /* (EMAC) Carrier Sense Error Register */
#परिभाषय AT91C_EMAC_SA3H            ( ( AT91_REG * ) 0xFFFDC0AC ) /* (EMAC) Specific Address 3 Top, Last 2 bytes */
#परिभाषय AT91C_EMAC_RRE             ( ( AT91_REG * ) 0xFFFDC06C ) /* (EMAC) Receive Resource Error Register */
#परिभाषय AT91C_EMAC_STE             ( ( AT91_REG * ) 0xFFFDC084 ) /* (EMAC) SQE Test Error Register */
/* ========== Register definition for PDC_ADC peripheral ========== */
#परिभाषय AT91C_ADC_PTSR             ( ( AT91_REG * ) 0xFFFD8124 ) /* (PDC_ADC) PDC Transfer Status Register */
#परिभाषय AT91C_ADC_PTCR             ( ( AT91_REG * ) 0xFFFD8120 ) /* (PDC_ADC) PDC Transfer Control Register */
#परिभाषय AT91C_ADC_TNPR             ( ( AT91_REG * ) 0xFFFD8118 ) /* (PDC_ADC) Transmit Next Pointer Register */
#परिभाषय AT91C_ADC_TNCR             ( ( AT91_REG * ) 0xFFFD811C ) /* (PDC_ADC) Transmit Next Counter Register */
#परिभाषय AT91C_ADC_RNPR             ( ( AT91_REG * ) 0xFFFD8110 ) /* (PDC_ADC) Receive Next Pointer Register */
#परिभाषय AT91C_ADC_RNCR             ( ( AT91_REG * ) 0xFFFD8114 ) /* (PDC_ADC) Receive Next Counter Register */
#परिभाषय AT91C_ADC_RPR              ( ( AT91_REG * ) 0xFFFD8100 ) /* (PDC_ADC) Receive Pointer Register */
#परिभाषय AT91C_ADC_TCR              ( ( AT91_REG * ) 0xFFFD810C ) /* (PDC_ADC) Transmit Counter Register */
#परिभाषय AT91C_ADC_TPR              ( ( AT91_REG * ) 0xFFFD8108 ) /* (PDC_ADC) Transmit Pointer Register */
#परिभाषय AT91C_ADC_RCR              ( ( AT91_REG * ) 0xFFFD8104 ) /* (PDC_ADC) Receive Counter Register */
/* ========== Register definition for ADC peripheral ========== */
#परिभाषय AT91C_ADC_CDR2             ( ( AT91_REG * ) 0xFFFD8038 ) /* (ADC) ADC Channel Data Register 2 */
#परिभाषय AT91C_ADC_CDR3             ( ( AT91_REG * ) 0xFFFD803C ) /* (ADC) ADC Channel Data Register 3 */
#परिभाषय AT91C_ADC_CDR0             ( ( AT91_REG * ) 0xFFFD8030 ) /* (ADC) ADC Channel Data Register 0 */
#परिभाषय AT91C_ADC_CDR5             ( ( AT91_REG * ) 0xFFFD8044 ) /* (ADC) ADC Channel Data Register 5 */
#परिभाषय AT91C_ADC_CHDR             ( ( AT91_REG * ) 0xFFFD8014 ) /* (ADC) ADC Channel Disable Register */
#परिभाषय AT91C_ADC_SR               ( ( AT91_REG * ) 0xFFFD801C ) /* (ADC) ADC Status Register */
#परिभाषय AT91C_ADC_CDR4             ( ( AT91_REG * ) 0xFFFD8040 ) /* (ADC) ADC Channel Data Register 4 */
#परिभाषय AT91C_ADC_CDR1             ( ( AT91_REG * ) 0xFFFD8034 ) /* (ADC) ADC Channel Data Register 1 */
#परिभाषय AT91C_ADC_LCDR             ( ( AT91_REG * ) 0xFFFD8020 ) /* (ADC) ADC Last Converted Data Register */
#परिभाषय AT91C_ADC_IDR              ( ( AT91_REG * ) 0xFFFD8028 ) /* (ADC) ADC Interrupt Disable Register */
#परिभाषय AT91C_ADC_CR               ( ( AT91_REG * ) 0xFFFD8000 ) /* (ADC) ADC Control Register */
#परिभाषय AT91C_ADC_CDR7             ( ( AT91_REG * ) 0xFFFD804C ) /* (ADC) ADC Channel Data Register 7 */
#परिभाषय AT91C_ADC_CDR6             ( ( AT91_REG * ) 0xFFFD8048 ) /* (ADC) ADC Channel Data Register 6 */
#परिभाषय AT91C_ADC_IER              ( ( AT91_REG * ) 0xFFFD8024 ) /* (ADC) ADC Interrupt Enable Register */
#परिभाषय AT91C_ADC_CHER             ( ( AT91_REG * ) 0xFFFD8010 ) /* (ADC) ADC Channel Enable Register */
#परिभाषय AT91C_ADC_CHSR             ( ( AT91_REG * ) 0xFFFD8018 ) /* (ADC) ADC Channel Status Register */
#परिभाषय AT91C_ADC_MR               ( ( AT91_REG * ) 0xFFFD8004 ) /* (ADC) ADC Mode Register */
#परिभाषय AT91C_ADC_IMR              ( ( AT91_REG * ) 0xFFFD802C ) /* (ADC) ADC Interrupt Mask Register */
/* ========== Register definition for PDC_AES peripheral ========== */
#परिभाषय AT91C_AES_TPR              ( ( AT91_REG * ) 0xFFFA4108 ) /* (PDC_AES) Transmit Pointer Register */
#परिभाषय AT91C_AES_PTCR             ( ( AT91_REG * ) 0xFFFA4120 ) /* (PDC_AES) PDC Transfer Control Register */
#परिभाषय AT91C_AES_RNPR             ( ( AT91_REG * ) 0xFFFA4110 ) /* (PDC_AES) Receive Next Pointer Register */
#परिभाषय AT91C_AES_TNCR             ( ( AT91_REG * ) 0xFFFA411C ) /* (PDC_AES) Transmit Next Counter Register */
#परिभाषय AT91C_AES_TCR              ( ( AT91_REG * ) 0xFFFA410C ) /* (PDC_AES) Transmit Counter Register */
#परिभाषय AT91C_AES_RCR              ( ( AT91_REG * ) 0xFFFA4104 ) /* (PDC_AES) Receive Counter Register */
#परिभाषय AT91C_AES_RNCR             ( ( AT91_REG * ) 0xFFFA4114 ) /* (PDC_AES) Receive Next Counter Register */
#परिभाषय AT91C_AES_TNPR             ( ( AT91_REG * ) 0xFFFA4118 ) /* (PDC_AES) Transmit Next Pointer Register */
#परिभाषय AT91C_AES_RPR              ( ( AT91_REG * ) 0xFFFA4100 ) /* (PDC_AES) Receive Pointer Register */
#परिभाषय AT91C_AES_PTSR             ( ( AT91_REG * ) 0xFFFA4124 ) /* (PDC_AES) PDC Transfer Status Register */
/* ========== Register definition for AES peripheral ========== */
#परिभाषय AT91C_AES_IVxR             ( ( AT91_REG * ) 0xFFFA4060 ) /* (AES) Initialization Vector x Register */
#परिभाषय AT91C_AES_MR               ( ( AT91_REG * ) 0xFFFA4004 ) /* (AES) Mode Register */
#परिभाषय AT91C_AES_VR               ( ( AT91_REG * ) 0xFFFA40FC ) /* (AES) AES Version Register */
#परिभाषय AT91C_AES_ODATAxR          ( ( AT91_REG * ) 0xFFFA4050 ) /* (AES) Output Data x Register */
#परिभाषय AT91C_AES_IDATAxR          ( ( AT91_REG * ) 0xFFFA4040 ) /* (AES) Input Data x Register */
#परिभाषय AT91C_AES_CR               ( ( AT91_REG * ) 0xFFFA4000 ) /* (AES) Control Register */
#परिभाषय AT91C_AES_IDR              ( ( AT91_REG * ) 0xFFFA4014 ) /* (AES) Interrupt Disable Register */
#परिभाषय AT91C_AES_IMR              ( ( AT91_REG * ) 0xFFFA4018 ) /* (AES) Interrupt Mask Register */
#परिभाषय AT91C_AES_IER              ( ( AT91_REG * ) 0xFFFA4010 ) /* (AES) Interrupt Enable Register */
#परिभाषय AT91C_AES_KEYWxR           ( ( AT91_REG * ) 0xFFFA4020 ) /* (AES) Key Word x Register */
#परिभाषय AT91C_AES_ISR              ( ( AT91_REG * ) 0xFFFA401C ) /* (AES) Interrupt Status Register */
/* ========== Register definition for PDC_TDES peripheral ========== */
#परिभाषय AT91C_TDES_RNCR            ( ( AT91_REG * ) 0xFFFA8114 ) /* (PDC_TDES) Receive Next Counter Register */
#परिभाषय AT91C_TDES_TCR             ( ( AT91_REG * ) 0xFFFA810C ) /* (PDC_TDES) Transmit Counter Register */
#परिभाषय AT91C_TDES_RCR             ( ( AT91_REG * ) 0xFFFA8104 ) /* (PDC_TDES) Receive Counter Register */
#परिभाषय AT91C_TDES_TNPR            ( ( AT91_REG * ) 0xFFFA8118 ) /* (PDC_TDES) Transmit Next Pointer Register */
#परिभाषय AT91C_TDES_RNPR            ( ( AT91_REG * ) 0xFFFA8110 ) /* (PDC_TDES) Receive Next Pointer Register */
#परिभाषय AT91C_TDES_RPR             ( ( AT91_REG * ) 0xFFFA8100 ) /* (PDC_TDES) Receive Pointer Register */
#परिभाषय AT91C_TDES_TNCR            ( ( AT91_REG * ) 0xFFFA811C ) /* (PDC_TDES) Transmit Next Counter Register */
#परिभाषय AT91C_TDES_TPR             ( ( AT91_REG * ) 0xFFFA8108 ) /* (PDC_TDES) Transmit Pointer Register */
#परिभाषय AT91C_TDES_PTSR            ( ( AT91_REG * ) 0xFFFA8124 ) /* (PDC_TDES) PDC Transfer Status Register */
#परिभाषय AT91C_TDES_PTCR            ( ( AT91_REG * ) 0xFFFA8120 ) /* (PDC_TDES) PDC Transfer Control Register */
/* ========== Register definition for TDES peripheral ========== */
#परिभाषय AT91C_TDES_KEY2WxR         ( ( AT91_REG * ) 0xFFFA8028 ) /* (TDES) Key 2 Word x Register */
#परिभाषय AT91C_TDES_KEY3WxR         ( ( AT91_REG * ) 0xFFFA8030 ) /* (TDES) Key 3 Word x Register */
#परिभाषय AT91C_TDES_IDR             ( ( AT91_REG * ) 0xFFFA8014 ) /* (TDES) Interrupt Disable Register */
#परिभाषय AT91C_TDES_VR              ( ( AT91_REG * ) 0xFFFA80FC ) /* (TDES) TDES Version Register */
#परिभाषय AT91C_TDES_IVxR            ( ( AT91_REG * ) 0xFFFA8060 ) /* (TDES) Initialization Vector x Register */
#परिभाषय AT91C_TDES_ODATAxR         ( ( AT91_REG * ) 0xFFFA8050 ) /* (TDES) Output Data x Register */
#परिभाषय AT91C_TDES_IMR             ( ( AT91_REG * ) 0xFFFA8018 ) /* (TDES) Interrupt Mask Register */
#परिभाषय AT91C_TDES_MR              ( ( AT91_REG * ) 0xFFFA8004 ) /* (TDES) Mode Register */
#परिभाषय AT91C_TDES_CR              ( ( AT91_REG * ) 0xFFFA8000 ) /* (TDES) Control Register */
#परिभाषय AT91C_TDES_IER             ( ( AT91_REG * ) 0xFFFA8010 ) /* (TDES) Interrupt Enable Register */
#परिभाषय AT91C_TDES_ISR             ( ( AT91_REG * ) 0xFFFA801C ) /* (TDES) Interrupt Status Register */
#परिभाषय AT91C_TDES_IDATAxR         ( ( AT91_REG * ) 0xFFFA8040 ) /* (TDES) Input Data x Register */
#परिभाषय AT91C_TDES_KEY1WxR         ( ( AT91_REG * ) 0xFFFA8020 ) /* (TDES) Key 1 Word x Register */

/* ***************************************************************************** */
/*               PIO DEFINITIONS FOR AT91SAM7X256 */
/* ***************************************************************************** */
#परिभाषय AT91C_PIO_PA0             ( ( अचिह्नित पूर्णाङ्क ) 1 << 0 )         /* Pin Controlled by PA0 */
#परिभाषय AT91C_PA0_RXD0            ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA0 )  /*  USART 0 Receive Data */
#परिभाषय AT91C_PIO_PA1             ( ( अचिह्नित पूर्णाङ्क ) 1 << 1 )         /* Pin Controlled by PA1 */
#परिभाषय AT91C_PA1_TXD0            ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA1 )  /*  USART 0 Transmit Data */
#परिभाषय AT91C_PIO_PA10            ( ( अचिह्नित पूर्णाङ्क ) 1 << 10 )        /* Pin Controlled by PA10 */
#परिभाषय AT91C_PA10_TWD            ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA10 ) /*  TWI Two-wire Serial Data */
#परिभाषय AT91C_PIO_PA11            ( ( अचिह्नित पूर्णाङ्क ) 1 << 11 )        /* Pin Controlled by PA11 */
#परिभाषय AT91C_PA11_TWCK           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA11 ) /*  TWI Two-wire Serial Clock */
#परिभाषय AT91C_PIO_PA12            ( ( अचिह्नित पूर्णाङ्क ) 1 << 12 )        /* Pin Controlled by PA12 */
#परिभाषय AT91C_PA12_NPCS00         ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA12 ) /*  SPI 0 Peripheral Chip Select 0 */
#परिभाषय AT91C_PIO_PA13            ( ( अचिह्नित पूर्णाङ्क ) 1 << 13 )        /* Pin Controlled by PA13 */
#परिभाषय AT91C_PA13_NPCS01         ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA13 ) /*  SPI 0 Peripheral Chip Select 1 */
#परिभाषय AT91C_PA13_PCK1           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA13 ) /*  PMC Programmable Clock Output 1 */
#परिभाषय AT91C_PIO_PA14            ( ( अचिह्नित पूर्णाङ्क ) 1 << 14 )        /* Pin Controlled by PA14 */
#परिभाषय AT91C_PA14_NPCS02         ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA14 ) /*  SPI 0 Peripheral Chip Select 2 */
#परिभाषय AT91C_PA14_IRQ1           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA14 ) /*  External Interrupt 1 */
#परिभाषय AT91C_PIO_PA15            ( ( अचिह्नित पूर्णाङ्क ) 1 << 15 )        /* Pin Controlled by PA15 */
#परिभाषय AT91C_PA15_NPCS03         ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA15 ) /*  SPI 0 Peripheral Chip Select 3 */
#परिभाषय AT91C_PA15_TCLK2          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA15 ) /*  Timer Counter 2 external clock input */
#परिभाषय AT91C_PIO_PA16            ( ( अचिह्नित पूर्णाङ्क ) 1 << 16 )        /* Pin Controlled by PA16 */
#परिभाषय AT91C_PA16_MISO0          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA16 ) /*  SPI 0 Master In Slave */
#परिभाषय AT91C_PIO_PA17            ( ( अचिह्नित पूर्णाङ्क ) 1 << 17 )        /* Pin Controlled by PA17 */
#परिभाषय AT91C_PA17_MOSI0          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA17 ) /*  SPI 0 Master Out Slave */
#परिभाषय AT91C_PIO_PA18            ( ( अचिह्नित पूर्णाङ्क ) 1 << 18 )        /* Pin Controlled by PA18 */
#परिभाषय AT91C_PA18_SPCK0          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA18 ) /*  SPI 0 Serial Clock */
#परिभाषय AT91C_PIO_PA19            ( ( अचिह्नित पूर्णाङ्क ) 1 << 19 )        /* Pin Controlled by PA19 */
#परिभाषय AT91C_PA19_CANRX          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA19 ) /*  CAN Receive */
#परिभाषय AT91C_PIO_PA2             ( ( अचिह्नित पूर्णाङ्क ) 1 << 2 )         /* Pin Controlled by PA2 */
#परिभाषय AT91C_PA2_SCK0            ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA2 )  /*  USART 0 Serial Clock */
#परिभाषय AT91C_PA2_NPCS11          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA2 )  /*  SPI 1 Peripheral Chip Select 1 */
#परिभाषय AT91C_PIO_PA20            ( ( अचिह्नित पूर्णाङ्क ) 1 << 20 )        /* Pin Controlled by PA20 */
#परिभाषय AT91C_PA20_CANTX          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA20 ) /*  CAN Transmit */
#परिभाषय AT91C_PIO_PA21            ( ( अचिह्नित पूर्णाङ्क ) 1 << 21 )        /* Pin Controlled by PA21 */
#परिभाषय AT91C_PA21_TF             ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA21 ) /*  SSC Transmit Frame Sync */
#परिभाषय AT91C_PA21_NPCS10         ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA21 ) /*  SPI 1 Peripheral Chip Select 0 */
#परिभाषय AT91C_PIO_PA22            ( ( अचिह्नित पूर्णाङ्क ) 1 << 22 )        /* Pin Controlled by PA22 */
#परिभाषय AT91C_PA22_TK             ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA22 ) /*  SSC Transmit Clock */
#परिभाषय AT91C_PA22_SPCK1          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA22 ) /*  SPI 1 Serial Clock */
#परिभाषय AT91C_PIO_PA23            ( ( अचिह्नित पूर्णाङ्क ) 1 << 23 )        /* Pin Controlled by PA23 */
#परिभाषय AT91C_PA23_TD             ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA23 ) /*  SSC Transmit data */
#परिभाषय AT91C_PA23_MOSI1          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA23 ) /*  SPI 1 Master Out Slave */
#परिभाषय AT91C_PIO_PA24            ( ( अचिह्नित पूर्णाङ्क ) 1 << 24 )        /* Pin Controlled by PA24 */
#परिभाषय AT91C_PA24_RD             ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA24 ) /*  SSC Receive Data */
#परिभाषय AT91C_PA24_MISO1          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA24 ) /*  SPI 1 Master In Slave */
#परिभाषय AT91C_PIO_PA25            ( ( अचिह्नित पूर्णाङ्क ) 1 << 25 )        /* Pin Controlled by PA25 */
#परिभाषय AT91C_PA25_RK             ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA25 ) /*  SSC Receive Clock */
#परिभाषय AT91C_PA25_NPCS11         ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA25 ) /*  SPI 1 Peripheral Chip Select 1 */
#परिभाषय AT91C_PIO_PA26            ( ( अचिह्नित पूर्णाङ्क ) 1 << 26 )        /* Pin Controlled by PA26 */
#परिभाषय AT91C_PA26_RF             ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA26 ) /*  SSC Receive Frame Sync */
#परिभाषय AT91C_PA26_NPCS12         ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA26 ) /*  SPI 1 Peripheral Chip Select 2 */
#परिभाषय AT91C_PIO_PA27            ( ( अचिह्नित पूर्णाङ्क ) 1 << 27 )        /* Pin Controlled by PA27 */
#परिभाषय AT91C_PA27_DRXD           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA27 ) /*  DBGU Debug Receive Data */
#परिभाषय AT91C_PA27_PCK3           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA27 ) /*  PMC Programmable Clock Output 3 */
#परिभाषय AT91C_PIO_PA28            ( ( अचिह्नित पूर्णाङ्क ) 1 << 28 )        /* Pin Controlled by PA28 */
#परिभाषय AT91C_PA28_DTXD           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA28 ) /*  DBGU Debug Transmit Data */
#परिभाषय AT91C_PIO_PA29            ( ( अचिह्नित पूर्णाङ्क ) 1 << 29 )        /* Pin Controlled by PA29 */
#परिभाषय AT91C_PA29_FIQ            ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA29 ) /*  AIC Fast Interrupt Input */
#परिभाषय AT91C_PA29_NPCS13         ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA29 ) /*  SPI 1 Peripheral Chip Select 3 */
#परिभाषय AT91C_PIO_PA3             ( ( अचिह्नित पूर्णाङ्क ) 1 << 3 )         /* Pin Controlled by PA3 */
#परिभाषय AT91C_PA3_RTS0            ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA3 )  /*  USART 0 Ready To Send */
#परिभाषय AT91C_PA3_NPCS12          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA3 )  /*  SPI 1 Peripheral Chip Select 2 */
#परिभाषय AT91C_PIO_PA30            ( ( अचिह्नित पूर्णाङ्क ) 1 << 30 )        /* Pin Controlled by PA30 */
#परिभाषय AT91C_PA30_IRQ0           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA30 ) /*  External Interrupt 0 */
#परिभाषय AT91C_PA30_PCK2           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA30 ) /*  PMC Programmable Clock Output 2 */
#परिभाषय AT91C_PIO_PA4             ( ( अचिह्नित पूर्णाङ्क ) 1 << 4 )         /* Pin Controlled by PA4 */
#परिभाषय AT91C_PA4_CTS0            ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA4 )  /*  USART 0 Clear To Send */
#परिभाषय AT91C_PA4_NPCS13          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA4 )  /*  SPI 1 Peripheral Chip Select 3 */
#परिभाषय AT91C_PIO_PA5             ( ( अचिह्नित पूर्णाङ्क ) 1 << 5 )         /* Pin Controlled by PA5 */
#परिभाषय AT91C_PA5_RXD1            ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA5 )  /*  USART 1 Receive Data */
#परिभाषय AT91C_PIO_PA6             ( ( अचिह्नित पूर्णाङ्क ) 1 << 6 )         /* Pin Controlled by PA6 */
#परिभाषय AT91C_PA6_TXD1            ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA6 )  /*  USART 1 Transmit Data */
#परिभाषय AT91C_PIO_PA7             ( ( अचिह्नित पूर्णाङ्क ) 1 << 7 )         /* Pin Controlled by PA7 */
#परिभाषय AT91C_PA7_SCK1            ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA7 )  /*  USART 1 Serial Clock */
#परिभाषय AT91C_PA7_NPCS01          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA7 )  /*  SPI 0 Peripheral Chip Select 1 */
#परिभाषय AT91C_PIO_PA8             ( ( अचिह्नित पूर्णाङ्क ) 1 << 8 )         /* Pin Controlled by PA8 */
#परिभाषय AT91C_PA8_RTS1            ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA8 )  /*  USART 1 Ready To Send */
#परिभाषय AT91C_PA8_NPCS02          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA8 )  /*  SPI 0 Peripheral Chip Select 2 */
#परिभाषय AT91C_PIO_PA9             ( ( अचिह्नित पूर्णाङ्क ) 1 << 9 )         /* Pin Controlled by PA9 */
#परिभाषय AT91C_PA9_CTS1            ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA9 )  /*  USART 1 Clear To Send */
#परिभाषय AT91C_PA9_NPCS03          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PA9 )  /*  SPI 0 Peripheral Chip Select 3 */
#परिभाषय AT91C_PIO_PB0             ( ( अचिह्नित पूर्णाङ्क ) 1 << 0 )         /* Pin Controlled by PB0 */
#परिभाषय AT91C_PB0_ETXCK_EREFCK    ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB0 )  /*  Ethernet MAC Transmit Clock/Reference Clock */
#परिभाषय AT91C_PB0_PCK0            ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB0 )  /*  PMC Programmable Clock Output 0 */
#परिभाषय AT91C_PIO_PB1             ( ( अचिह्नित पूर्णाङ्क ) 1 << 1 )         /* Pin Controlled by PB1 */
#परिभाषय AT91C_PB1_ETXEN           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB1 )  /*  Ethernet MAC Transmit Enable */
#परिभाषय AT91C_PIO_PB10            ( ( अचिह्नित पूर्णाङ्क ) 1 << 10 )        /* Pin Controlled by PB10 */
#परिभाषय AT91C_PB10_ETX2           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB10 ) /*  Ethernet MAC Transmit Data 2 */
#परिभाषय AT91C_PB10_NPCS11         ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB10 ) /*  SPI 1 Peripheral Chip Select 1 */
#परिभाषय AT91C_PIO_PB11            ( ( अचिह्नित पूर्णाङ्क ) 1 << 11 )        /* Pin Controlled by PB11 */
#परिभाषय AT91C_PB11_ETX3           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB11 ) /*  Ethernet MAC Transmit Data 3 */
#परिभाषय AT91C_PB11_NPCS12         ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB11 ) /*  SPI 1 Peripheral Chip Select 2 */
#परिभाषय AT91C_PIO_PB12            ( ( अचिह्नित पूर्णाङ्क ) 1 << 12 )        /* Pin Controlled by PB12 */
#परिभाषय AT91C_PB12_ETXER          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB12 ) /*  Ethernet MAC Transmit Coding Error */
#परिभाषय AT91C_PB12_TCLK0          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB12 ) /*  Timer Counter 0 external clock input */
#परिभाषय AT91C_PIO_PB13            ( ( अचिह्नित पूर्णाङ्क ) 1 << 13 )        /* Pin Controlled by PB13 */
#परिभाषय AT91C_PB13_ERX2           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB13 ) /*  Ethernet MAC Receive Data 2 */
#परिभाषय AT91C_PB13_NPCS01         ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB13 ) /*  SPI 0 Peripheral Chip Select 1 */
#परिभाषय AT91C_PIO_PB14            ( ( अचिह्नित पूर्णाङ्क ) 1 << 14 )        /* Pin Controlled by PB14 */
#परिभाषय AT91C_PB14_ERX3           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB14 ) /*  Ethernet MAC Receive Data 3 */
#परिभाषय AT91C_PB14_NPCS02         ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB14 ) /*  SPI 0 Peripheral Chip Select 2 */
#परिभाषय AT91C_PIO_PB15            ( ( अचिह्नित पूर्णाङ्क ) 1 << 15 )        /* Pin Controlled by PB15 */
#परिभाषय AT91C_PB15_ERXDV          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB15 ) /*  Ethernet MAC Receive Data Valid */
#परिभाषय AT91C_PIO_PB16            ( ( अचिह्नित पूर्णाङ्क ) 1 << 16 )        /* Pin Controlled by PB16 */
#परिभाषय AT91C_PB16_ECOL           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB16 ) /*  Ethernet MAC Collision Detected */
#परिभाषय AT91C_PB16_NPCS13         ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB16 ) /*  SPI 1 Peripheral Chip Select 3 */
#परिभाषय AT91C_PIO_PB17            ( ( अचिह्नित पूर्णाङ्क ) 1 << 17 )        /* Pin Controlled by PB17 */
#परिभाषय AT91C_PB17_ERXCK          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB17 ) /*  Ethernet MAC Receive Clock */
#परिभाषय AT91C_PB17_NPCS03         ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB17 ) /*  SPI 0 Peripheral Chip Select 3 */
#परिभाषय AT91C_PIO_PB18            ( ( अचिह्नित पूर्णाङ्क ) 1 << 18 )        /* Pin Controlled by PB18 */
#परिभाषय AT91C_PB18_EF100          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB18 ) /*  Ethernet MAC Force 100 Mbits/sec */
#परिभाषय AT91C_PB18_ADTRG          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB18 ) /*  ADC External Trigger */
#परिभाषय AT91C_PIO_PB19            ( ( अचिह्नित पूर्णाङ्क ) 1 << 19 )        /* Pin Controlled by PB19 */
#परिभाषय AT91C_PB19_PWM0           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB19 ) /*  PWM Channel 0 */
#परिभाषय AT91C_PB19_TCLK1          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB19 ) /*  Timer Counter 1 external clock input */
#परिभाषय AT91C_PIO_PB2             ( ( अचिह्नित पूर्णाङ्क ) 1 << 2 )         /* Pin Controlled by PB2 */
#परिभाषय AT91C_PB2_ETX0            ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB2 )  /*  Ethernet MAC Transmit Data 0 */
#परिभाषय AT91C_PIO_PB20            ( ( अचिह्नित पूर्णाङ्क ) 1 << 20 )        /* Pin Controlled by PB20 */
#परिभाषय AT91C_PB20_PWM1           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB20 ) /*  PWM Channel 1 */
#परिभाषय AT91C_PB20_PCK0           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB20 ) /*  PMC Programmable Clock Output 0 */
#परिभाषय AT91C_PIO_PB21            ( ( अचिह्नित पूर्णाङ्क ) 1 << 21 )        /* Pin Controlled by PB21 */
#परिभाषय AT91C_PB21_PWM2           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB21 ) /*  PWM Channel 2 */
#परिभाषय AT91C_PB21_PCK1           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB21 ) /*  PMC Programmable Clock Output 1 */
#परिभाषय AT91C_PIO_PB22            ( ( अचिह्नित पूर्णाङ्क ) 1 << 22 )        /* Pin Controlled by PB22 */
#परिभाषय AT91C_PB22_PWM3           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB22 ) /*  PWM Channel 3 */
#परिभाषय AT91C_PB22_PCK2           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB22 ) /*  PMC Programmable Clock Output 2 */
#परिभाषय AT91C_PIO_PB23            ( ( अचिह्नित पूर्णाङ्क ) 1 << 23 )        /* Pin Controlled by PB23 */
#परिभाषय AT91C_PB23_TIOA0          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB23 ) /*  Timer Counter 0 Multipurpose Timer I/O Pin A */
#परिभाषय AT91C_PB23_DCD1           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB23 ) /*  USART 1 Data Carrier Detect */
#परिभाषय AT91C_PIO_PB24            ( ( अचिह्नित पूर्णाङ्क ) 1 << 24 )        /* Pin Controlled by PB24 */
#परिभाषय AT91C_PB24_TIOB0          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB24 ) /*  Timer Counter 0 Multipurpose Timer I/O Pin B */
#परिभाषय AT91C_PB24_DSR1           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB24 ) /*  USART 1 Data Set ready */
#परिभाषय AT91C_PIO_PB25            ( ( अचिह्नित पूर्णाङ्क ) 1 << 25 )        /* Pin Controlled by PB25 */
#परिभाषय AT91C_PB25_TIOA1          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB25 ) /*  Timer Counter 1 Multipurpose Timer I/O Pin A */
#परिभाषय AT91C_PB25_DTR1           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB25 ) /*  USART 1 Data Terminal ready */
#परिभाषय AT91C_PIO_PB26            ( ( अचिह्नित पूर्णाङ्क ) 1 << 26 )        /* Pin Controlled by PB26 */
#परिभाषय AT91C_PB26_TIOB1          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB26 ) /*  Timer Counter 1 Multipurpose Timer I/O Pin B */
#परिभाषय AT91C_PB26_RI1            ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB26 ) /*  USART 1 Ring Indicator */
#परिभाषय AT91C_PIO_PB27            ( ( अचिह्नित पूर्णाङ्क ) 1 << 27 )        /* Pin Controlled by PB27 */
#परिभाषय AT91C_PB27_TIOA2          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB27 ) /*  Timer Counter 2 Multipurpose Timer I/O Pin A */
#परिभाषय AT91C_PB27_PWM0           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB27 ) /*  PWM Channel 0 */
#परिभाषय AT91C_PIO_PB28            ( ( अचिह्नित पूर्णाङ्क ) 1 << 28 )        /* Pin Controlled by PB28 */
#परिभाषय AT91C_PB28_TIOB2          ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB28 ) /*  Timer Counter 2 Multipurpose Timer I/O Pin B */
#परिभाषय AT91C_PB28_PWM1           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB28 ) /*  PWM Channel 1 */
#परिभाषय AT91C_PIO_PB29            ( ( अचिह्नित पूर्णाङ्क ) 1 << 29 )        /* Pin Controlled by PB29 */
#परिभाषय AT91C_PB29_PCK1           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB29 ) /*  PMC Programmable Clock Output 1 */
#परिभाषय AT91C_PB29_PWM2           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB29 ) /*  PWM Channel 2 */
#परिभाषय AT91C_PIO_PB3             ( ( अचिह्नित पूर्णाङ्क ) 1 << 3 )         /* Pin Controlled by PB3 */
#परिभाषय AT91C_PB3_ETX1            ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB3 )  /*  Ethernet MAC Transmit Data 1 */
#परिभाषय AT91C_PIO_PB30            ( ( अचिह्नित पूर्णाङ्क ) 1 << 30 )        /* Pin Controlled by PB30 */
#परिभाषय AT91C_PB30_PCK2           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB30 ) /*  PMC Programmable Clock Output 2 */
#परिभाषय AT91C_PB30_PWM3           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB30 ) /*  PWM Channel 3 */
#परिभाषय AT91C_PIO_PB4             ( ( अचिह्नित पूर्णाङ्क ) 1 << 4 )         /* Pin Controlled by PB4 */
#परिभाषय AT91C_PB4_ECRS_ECRSDV     ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB4 )  /*  Ethernet MAC Carrier Sense/Carrier Sense and Data Valid */
#परिभाषय AT91C_PIO_PB5             ( ( अचिह्नित पूर्णाङ्क ) 1 << 5 )         /* Pin Controlled by PB5 */
#परिभाषय AT91C_PB5_ERX0            ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB5 )  /*  Ethernet MAC Receive Data 0 */
#परिभाषय AT91C_PIO_PB6             ( ( अचिह्नित पूर्णाङ्क ) 1 << 6 )         /* Pin Controlled by PB6 */
#परिभाषय AT91C_PB6_ERX1            ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB6 )  /*  Ethernet MAC Receive Data 1 */
#परिभाषय AT91C_PIO_PB7             ( ( अचिह्नित पूर्णाङ्क ) 1 << 7 )         /* Pin Controlled by PB7 */
#परिभाषय AT91C_PB7_ERXER           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB7 )  /*  Ethernet MAC Receive Error */
#परिभाषय AT91C_PIO_PB8             ( ( अचिह्नित पूर्णाङ्क ) 1 << 8 )         /* Pin Controlled by PB8 */
#परिभाषय AT91C_PB8_EMDC            ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB8 )  /*  Ethernet MAC Management Data Clock */
#परिभाषय AT91C_PIO_PB9             ( ( अचिह्नित पूर्णाङ्क ) 1 << 9 )         /* Pin Controlled by PB9 */
#परिभाषय AT91C_PB9_EMDIO           ( ( अचिह्नित पूर्णाङ्क ) AT91C_PIO_PB9 )  /*  Ethernet MAC Management Data Input/Output */

/* ***************************************************************************** */
/*               PERIPHERAL ID DEFINITIONS FOR AT91SAM7X256 */
/* ***************************************************************************** */
#परिभाषय AT91C_ID_FIQ            ( ( अचिह्नित पूर्णाङ्क ) 0 )  /* Advanced Interrupt Controller (FIQ) */
#परिभाषय AT91C_ID_SYS            ( ( अचिह्नित पूर्णाङ्क ) 1 )  /* System Peripheral */
#परिभाषय AT91C_ID_PIOA           ( ( अचिह्नित पूर्णाङ्क ) 2 )  /* Parallel IO Controller A */
#परिभाषय AT91C_ID_PIOB           ( ( अचिह्नित पूर्णाङ्क ) 3 )  /* Parallel IO Controller B */
#परिभाषय AT91C_ID_SPI0           ( ( अचिह्नित पूर्णाङ्क ) 4 )  /* Serial Peripheral Interface 0 */
#परिभाषय AT91C_ID_SPI1           ( ( अचिह्नित पूर्णाङ्क ) 5 )  /* Serial Peripheral Interface 1 */
#परिभाषय AT91C_ID_US0            ( ( अचिह्नित पूर्णाङ्क ) 6 )  /* USART 0 */
#परिभाषय AT91C_ID_US1            ( ( अचिह्नित पूर्णाङ्क ) 7 )  /* USART 1 */
#परिभाषय AT91C_ID_SSC            ( ( अचिह्नित पूर्णाङ्क ) 8 )  /* Serial Synchronous Controller */
#परिभाषय AT91C_ID_TWI            ( ( अचिह्नित पूर्णाङ्क ) 9 )  /* Two-Wire Interface */
#परिभाषय AT91C_ID_PWMC           ( ( अचिह्नित पूर्णाङ्क ) 10 ) /* PWM Controller */
#परिभाषय AT91C_ID_UDP            ( ( अचिह्नित पूर्णाङ्क ) 11 ) /* USB Device Port */
#परिभाषय AT91C_ID_TC0            ( ( अचिह्नित पूर्णाङ्क ) 12 ) /* Timer Counter 0 */
#परिभाषय AT91C_ID_TC1            ( ( अचिह्नित पूर्णाङ्क ) 13 ) /* Timer Counter 1 */
#परिभाषय AT91C_ID_TC2            ( ( अचिह्नित पूर्णाङ्क ) 14 ) /* Timer Counter 2 */
#परिभाषय AT91C_ID_CAN            ( ( अचिह्नित पूर्णाङ्क ) 15 ) /* Control Area Network Controller */
#परिभाषय AT91C_ID_EMAC           ( ( अचिह्नित पूर्णाङ्क ) 16 ) /* Ethernet MAC */
#परिभाषय AT91C_ID_ADC            ( ( अचिह्नित पूर्णाङ्क ) 17 ) /* Analog-to-Digital Converter */
#परिभाषय AT91C_ID_AES            ( ( अचिह्नित पूर्णाङ्क ) 18 ) /* Advanced Encryption Standard 128-bit */
#परिभाषय AT91C_ID_TDES           ( ( अचिह्नित पूर्णाङ्क ) 19 ) /* Triple Data Encryption Standard */
#परिभाषय AT91C_ID_20_Reserved    ( ( अचिह्नित पूर्णाङ्क ) 20 ) /* Reserved */
#परिभाषय AT91C_ID_21_Reserved    ( ( अचिह्नित पूर्णाङ्क ) 21 ) /* Reserved */
#परिभाषय AT91C_ID_22_Reserved    ( ( अचिह्नित पूर्णाङ्क ) 22 ) /* Reserved */
#परिभाषय AT91C_ID_23_Reserved    ( ( अचिह्नित पूर्णाङ्क ) 23 ) /* Reserved */
#परिभाषय AT91C_ID_24_Reserved    ( ( अचिह्नित पूर्णाङ्क ) 24 ) /* Reserved */
#परिभाषय AT91C_ID_25_Reserved    ( ( अचिह्नित पूर्णाङ्क ) 25 ) /* Reserved */
#परिभाषय AT91C_ID_26_Reserved    ( ( अचिह्नित पूर्णाङ्क ) 26 ) /* Reserved */
#परिभाषय AT91C_ID_27_Reserved    ( ( अचिह्नित पूर्णाङ्क ) 27 ) /* Reserved */
#परिभाषय AT91C_ID_28_Reserved    ( ( अचिह्नित पूर्णाङ्क ) 28 ) /* Reserved */
#परिभाषय AT91C_ID_29_Reserved    ( ( अचिह्नित पूर्णाङ्क ) 29 ) /* Reserved */
#परिभाषय AT91C_ID_IRQ0           ( ( अचिह्नित पूर्णाङ्क ) 30 ) /* Advanced Interrupt Controller (IRQ0) */
#परिभाषय AT91C_ID_IRQ1           ( ( अचिह्नित पूर्णाङ्क ) 31 ) /* Advanced Interrupt Controller (IRQ1) */

/* ***************************************************************************** */
/*               BASE ADDRESS DEFINITIONS FOR AT91SAM7X256 */
/* ***************************************************************************** */
#परिभाषय AT91_C_आधारः_SYS         ( ( AT91PS_SYS ) 0xFFFFF000 )     /* (SYS) Base Address */
#परिभाषय AT91_C_आधारः_AIC         ( ( AT91PS_AIC ) 0xFFFFF000 )     /* (AIC) Base Address */
#परिभाषय AT91_C_आधारः_PDC_DBGU    ( ( AT91PS_PDC ) 0xFFFFF300 )     /* (PDC_DBGU) Base Address */
#परिभाषय AT91_C_आधारः_DBGU        ( ( AT91PS_DBGU ) 0xFFFFF200 )    /* (DBGU) Base Address */
#परिभाषय AT91_C_आधारः_PIOA        ( ( AT91PS_PIO ) 0xFFFFF400 )     /* (PIOA) Base Address */
#परिभाषय AT91_C_आधारः_PIOB        ( ( AT91PS_PIO ) 0xFFFFF600 )     /* (PIOB) Base Address */
#परिभाषय AT91_C_आधारः_CKGR        ( ( AT91PS_CKGR ) 0xFFFFFC20 )    /* (CKGR) Base Address */
#परिभाषय AT91_C_आधारः_PMC         ( ( AT91PS_PMC ) 0xFFFFFC00 )     /* (PMC) Base Address */
#परिभाषय AT91_C_आधारः_RSTC        ( ( AT91PS_RSTC ) 0xFFFFFD00 )    /* (RSTC) Base Address */
#परिभाषय AT91_C_आधारः_RTTC        ( ( AT91PS_RTTC ) 0xFFFFFD20 )    /* (RTTC) Base Address */
#परिभाषय AT91_C_आधारः_PITC        ( ( AT91PS_PITC ) 0xFFFFFD30 )    /* (PITC) Base Address */
#परिभाषय AT91_C_आधारः_WDTC        ( ( AT91PS_WDTC ) 0xFFFFFD40 )    /* (WDTC) Base Address */
#परिभाषय AT91_C_आधारः_VREG        ( ( AT91PS_VREG ) 0xFFFFFD60 )    /* (VREG) Base Address */
#परिभाषय AT91_C_आधारः_MC          ( ( AT91PS_MC ) 0xFFFFFF00 )      /* (MC) Base Address */
#परिभाषय AT91_C_आधारः_PDC_SPI1    ( ( AT91PS_PDC ) 0xFFFE4100 )     /* (PDC_SPI1) Base Address */
#परिभाषय AT91_C_आधारः_SPI1        ( ( AT91PS_SPI ) 0xFFFE4000 )     /* (SPI1) Base Address */
#परिभाषय AT91_C_आधारः_PDC_SPI0    ( ( AT91PS_PDC ) 0xFFFE0100 )     /* (PDC_SPI0) Base Address */
#परिभाषय AT91_C_आधारः_SPI0        ( ( AT91PS_SPI ) 0xFFFE0000 )     /* (SPI0) Base Address */
#परिभाषय AT91_C_आधारः_PDC_US1     ( ( AT91PS_PDC ) 0xFFFC4100 )     /* (PDC_US1) Base Address */
#परिभाषय AT91_C_आधारः_US1         ( ( AT91PS_USART ) 0xFFFC4000 )   /* (US1) Base Address */
#परिभाषय AT91_C_आधारः_PDC_US0     ( ( AT91PS_PDC ) 0xFFFC0100 )     /* (PDC_US0) Base Address */
#परिभाषय AT91_C_आधारः_US0         ( ( AT91PS_USART ) 0xFFFC0000 )   /* (US0) Base Address */
#परिभाषय AT91_C_आधारः_PDC_SSC     ( ( AT91PS_PDC ) 0xFFFD4100 )     /* (PDC_SSC) Base Address */
#परिभाषय AT91_C_आधारः_SSC         ( ( AT91PS_SSC ) 0xFFFD4000 )     /* (SSC) Base Address */
#परिभाषय AT91_C_आधारः_TWI         ( ( AT91PS_TWI ) 0xFFFB8000 )     /* (TWI) Base Address */
#परिभाषय AT91_C_आधारः_PWMC_CH3    ( ( AT91PS_PWMC_CH ) 0xFFFCC260 ) /* (PWMC_CH3) Base Address */
#परिभाषय AT91_C_आधारः_PWMC_CH2    ( ( AT91PS_PWMC_CH ) 0xFFFCC240 ) /* (PWMC_CH2) Base Address */
#परिभाषय AT91_C_आधारः_PWMC_CH1    ( ( AT91PS_PWMC_CH ) 0xFFFCC220 ) /* (PWMC_CH1) Base Address */
#परिभाषय AT91_C_आधारः_PWMC_CH0    ( ( AT91PS_PWMC_CH ) 0xFFFCC200 ) /* (PWMC_CH0) Base Address */
#परिभाषय AT91_C_आधारः_PWMC        ( ( AT91PS_PWMC ) 0xFFFCC000 )    /* (PWMC) Base Address */
#परिभाषय AT91_C_आधारः_UDP         ( ( AT91PS_UDP ) 0xFFFB0000 )     /* (UDP) Base Address */
#परिभाषय AT91_C_आधारः_TC0         ( ( AT91PS_TC ) 0xFFFA0000 )      /* (TC0) Base Address */
#परिभाषय AT91_C_आधारः_TC1         ( ( AT91PS_TC ) 0xFFFA0040 )      /* (TC1) Base Address */
#परिभाषय AT91_C_आधारः_TC2         ( ( AT91PS_TC ) 0xFFFA0080 )      /* (TC2) Base Address */
#परिभाषय AT91_C_आधारः_TCB         ( ( AT91PS_TCB ) 0xFFFA0000 )     /* (TCB) Base Address */
#परिभाषय AT91_C_आधारः_CAN_MB0     ( ( AT91PS_CAN_MB ) 0xFFFD0200 )  /* (CAN_MB0) Base Address */
#परिभाषय AT91_C_आधारः_CAN_MB1     ( ( AT91PS_CAN_MB ) 0xFFFD0220 )  /* (CAN_MB1) Base Address */
#परिभाषय AT91_C_आधारः_CAN_MB2     ( ( AT91PS_CAN_MB ) 0xFFFD0240 )  /* (CAN_MB2) Base Address */
#परिभाषय AT91_C_आधारः_CAN_MB3     ( ( AT91PS_CAN_MB ) 0xFFFD0260 )  /* (CAN_MB3) Base Address */
#परिभाषय AT91_C_आधारः_CAN_MB4     ( ( AT91PS_CAN_MB ) 0xFFFD0280 )  /* (CAN_MB4) Base Address */
#परिभाषय AT91_C_आधारः_CAN_MB5     ( ( AT91PS_CAN_MB ) 0xFFFD02A0 )  /* (CAN_MB5) Base Address */
#परिभाषय AT91_C_आधारः_CAN_MB6     ( ( AT91PS_CAN_MB ) 0xFFFD02C0 )  /* (CAN_MB6) Base Address */
#परिभाषय AT91_C_आधारः_CAN_MB7     ( ( AT91PS_CAN_MB ) 0xFFFD02E0 )  /* (CAN_MB7) Base Address */
#परिभाषय AT91_C_आधारः_CAN         ( ( AT91PS_CAN ) 0xFFFD0000 )     /* (CAN) Base Address */
#परिभाषय AT91_C_आधारः_EMAC        ( ( AT91PS_EMAC ) 0xFFFDC000 )    /* (EMAC) Base Address */
#परिभाषय AT91_C_आधारः_PDC_ADC     ( ( AT91PS_PDC ) 0xFFFD8100 )     /* (PDC_ADC) Base Address */
#परिभाषय AT91_C_आधारः_ADC         ( ( AT91PS_ADC ) 0xFFFD8000 )     /* (ADC) Base Address */
#परिभाषय AT91_C_आधारः_PDC_AES     ( ( AT91PS_PDC ) 0xFFFA4100 )     /* (PDC_AES) Base Address */
#परिभाषय AT91_C_आधारः_AES         ( ( AT91PS_AES ) 0xFFFA4000 )     /* (AES) Base Address */
#परिभाषय AT91_C_आधारः_PDC_TDES    ( ( AT91PS_PDC ) 0xFFFA8100 )     /* (PDC_TDES) Base Address */
#परिभाषय AT91_C_आधारः_TDES        ( ( AT91PS_TDES ) 0xFFFA8000 )    /* (TDES) Base Address */

/* ***************************************************************************** */
/*               MEMORY MAPPING DEFINITIONS FOR AT91SAM7X256 */
/* ***************************************************************************** */
#परिभाषय AT91C_ISRAM          ( ( वर्ण * ) 0x00200000 )       /* Internal SRAM base address */
#परिभाषय AT91_C_ISRAM_आकार     ( ( अचिह्नित पूर्णाङ्क ) 0x00010000 ) /* Internal SRAM size in byte (64 Kbyte) */
#परिभाषय AT91C_IFLASH         ( ( वर्ण * ) 0x00100000 )       /* Internal ROM base address */
#परिभाषय AT91_C_IFLASH_आकार    ( ( अचिह्नित पूर्णाङ्क ) 0x00040000 ) /* Internal ROM size in byte (256 Kbyte) */



/* - Hardware register definition */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR System Peripherals */
/* - ***************************************************************************** */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Advanced Interrupt Controller */
/* - ***************************************************************************** */
/* - -------- AIC_SMR : (AIC Offset: 0x0) Control Register -------- */
#यदि 0 /*_RB_*/
    AT91_C_AIC_प्राक् EQU( 0x7 << 0 );
    -( AIC ) प्राथमिकता_2 Level
    AT91_C_AIC_प्राक्_निम्नतमम् EQU( 0x0 );
    -( AIC ) निम्नतमम् प्राथमिकता level
    AT91_C_AIC_प्राक्_HIGHEST EQU( 0x7 );
    -( AIC ) Highest प्राथमिकता level
    AT91C_AIC_SRCTYPE EQU( 0x3 << 5 );
    -( AIC ) व्यवधानम्_2 Source Type
    AT91_C_AIC_SRCTYPE_INT_उच्चः_LEVEL EQU( 0x0 << 5 );
    -( AIC ) आन्तरिकम् Sources संहिता_2 Label उच्चः - level Sensitive
    AT91_C_AIC_SRCTYPE_EXT_नीचः_LEVEL EQU( 0x0 << 5 );
    -( AIC ) External Sources संहिता_2 Label नीचः - level Sensitive
    AT91_C_AIC_SRCTYPE_INT_धनात्मकम्_EDGE EQU( 0x1 << 5 );
    -( AIC ) आन्तरिकम् Sources संहिता_2 Label धनात्मकम् Edge triggered
    AT91C_AIC_SRCTYPE_EXT_NEGATIVE_EDGE EQU( 0x1 << 5 );
    -( AIC ) External Sources संहिता_2 Label Negative Edge triggered
    AT91_C_AIC_SRCTYPE_उच्चः_LEVEL EQU( 0x2 << 5 );
    -( AIC ) आन्तरिकम् Or External Sources संहिता_2 Label उच्चः - level Sensitive
    AT91_C_AIC_SRCTYPE_धनात्मकम्_EDGE EQU( 0x3 << 5 );
    -( AIC ) आन्तरिकम् Or External Sources संहिता_2 Label धनात्मकम् Edge triggered
/* - -------- AIC_CISR : (AIC Offset: 0x114) AIC Core Interrupt Status Register -------- */
    AT91C_AIC_NFIQ EQU( 0x1 << 0 );
    -( AIC ) NFIQ स्थितिः
    AT91C_AIC_NIRQ EQU( 0x1 << 1 );
    -( AIC ) NIRQ स्थितिः
/* - -------- AIC_DCR : (AIC Offset: 0x138) AIC Debug Control Register (Protect) -------- */
    AT91C_AIC_DCR_PROT EQU( 0x1 << 0 );
    -( AIC ) Protection बहुलकम्
    AT91C_AIC_DCR_GMSK EQU( 0x1 << 1 );
    -( AIC ) General आवरणम्_2
#यदि_अन्तः /* if 0 */
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
-( DBGU ) Reset स्थितिः द्वयङ्काः
/* - -------- DBGU_MR : (DBGU Offset: 0x4) Debug Unit Mode Register -------- */
AT91C_US_PAR EQU( 0x7 << 9 );
-( DBGU ) Parity type
AT91C_US_PAR_EVEN EQU( 0x0 << 9 );
-( DBGU ) Even Parity
AT91C_US_PAR_ODD EQU( 0x1 << 9 );
-( DBGU ) Odd Parity
AT91C_US_PAR_SPACE EQU( 0x2 << 9 );
-( DBGU ) Parity forced गन्तव्यम् 0 ( Space )
AT91C_US_PAR_MARK EQU( 0x3 << 9 );
-( DBGU ) Parity forced गन्तव्यम् 1 ( Mark )
AT91C_US_PAR_NONE EQU( 0x4 << 9 );
-( DBGU ) No Parity
AT91C_US_PAR_MULTI_DROP EQU( 0x6 << 9 );
-( DBGU ) Multi - drop बहुलकम्_2
AT91C_US_CHMODE EQU( 0x3 << 14 );
-( DBGU ) Channel बहुलकम्
AT91_C_US_CHMODE_प्रसामान्यम् EQU( 0x0 << 14 );
-( DBGU ) प्रसामान्यम् बहुलकम्: The USART channel operates as an RX / TX USART.
   AT91C_US_CHMODE_AUTO EQU( 0x1 << 14 );
-( DBGU ) Automatic Echo: Receiver दत्त निवेशः is connected गन्तव्यम् the TXD pin.
   AT91C_US_CHMODE_LOCAL EQU( 0x2 << 14 );
-( DBGU ) Local Loopback: Transmitter Output Signal is connected गन्तव्यम् Receiver निवेशः Signal.
   AT91C_US_CHMODE_REMOTE EQU( 0x3 << 14 );
-( DBGU ) Remote Loopback: RXD pin is internally connected गन्तव्यम् TXD pin.
/* - -------- DBGU_IER : (DBGU Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
   AT91C_US_RXRDY EQU( 0x1 << 0 );
-( DBGU ) RXRDY व्यवधानम्_2
AT91C_US_TXRDY EQU( 0x1 << 1 );
-( DBGU ) TXRDY व्यवधानम्_2
AT91C_US_ENDRX EQU( 0x1 << 3 );
-( DBGU ) अन्तः_3 सम्बन्धि Receive Transfer व्यवधानम्_2
AT91C_US_ENDTX EQU( 0x1 << 4 );
-( DBGU ) अन्तः_3 सम्बन्धि Transmit व्यवधानम्_2
AT91C_US_OVRE EQU( 0x1 << 5 );
-( DBGU ) Overrun व्यवधानम्_2
AT91C_US_FRAME EQU( 0x1 << 6 );
-( DBGU ) Framing Error व्यवधानम्_2
AT91C_US_PARE EQU( 0x1 << 7 );
-( DBGU ) Parity Error व्यवधानम्_2
AT91C_US_TXEMPTY EQU( 0x1 << 9 );
-( DBGU ) TXEMPTY व्यवधानम्_2
AT91C_US_TXBUFE EQU( 0x1 << 11 );
-( DBGU ) TXBUFE व्यवधानम्_2
AT91C_US_RXBUFF EQU( 0x1 << 12 );
-( DBGU ) RXBUFF व्यवधानम्_2
AT91C_US_COMM_TX EQU( 0x1 << 30 );
-( DBGU ) COMM_TX व्यवधानम्_2
AT91C_US_COMM_RX EQU( 0x1 << 31 );
-( DBGU ) COMM_RX व्यवधानम्_2
/* - -------- DBGU_IDR : (DBGU Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* - -------- DBGU_IMR : (DBGU Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* - -------- DBGU_CSR : (DBGU Offset: 0x14) Debug Unit Channel Status Register -------- */
/* - -------- DBGU_FNTR : (DBGU Offset: 0x48) Debug Unit FORCE_NTRST Register -------- */
AT91C_US_FORCE_NTRST EQU( 0x1 << 0 );
-( DBGU ) Force NTRST अन्तर् JTAG

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
-( CKGR ) Main Oscillator Start - ऊर्ध्वम् Time
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
-( CKGR ) PLL गणक_2
AT91_C_CKGR_बहिर्गमनम् EQU( 0x3 << 14 );
-( CKGR ) PLL Output Frequency Range
AT91_C_CKGR_बहिर्गमनम्_0 EQU( 0x0 << 14 );
-( CKGR ) Please refer गन्तव्यम् the PLL datasheet
AT91_C_CKGR_बहिर्गमनम्_1 EQU( 0x1 << 14 );
-( CKGR ) Please refer गन्तव्यम् the PLL datasheet
AT91_C_CKGR_बहिर्गमनम्_2 EQU( 0x2 << 14 );
-( CKGR ) Please refer गन्तव्यम् the PLL datasheet
AT91_C_CKGR_बहिर्गमनम्_3 EQU( 0x3 << 14 );
-( CKGR ) Please refer गन्तव्यम् the PLL datasheet
AT91C_CKGR_MUL EQU( 0x7FF << 16 );
-( CKGR ) PLL Multiplier
AT91C_CKGR_USBDIV EQU( 0x3 << 28 );
-( CKGR ) Divider

प्रति USB Clocks
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
-( PMC ) USB Device पत्तनम्_2 Clock
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
-( PMC ) MOSC स्थितिः / Enable / Disable / आवरणम्_2
AT91_C_PMC_तालकम् EQU( 0x1 << 2 );
-( PMC ) PLL स्थितिः / Enable / Disable / आवरणम्_2
AT91C_PMC_MCKRDY EQU( 0x1 << 3 );
-( PMC ) MCK_RDY स्थितिः / Enable / Disable / आवरणम्_2
AT91C_PMC_PCK0RDY EQU( 0x1 << 8 );
-( PMC ) PCK0_RDY स्थितिः / Enable / Disable / आवरणम्_2
AT91C_PMC_PCK1RDY EQU( 0x1 << 9 );
-( PMC ) PCK1_RDY स्थितिः / Enable / Disable / आवरणम्_2
AT91C_PMC_PCK2RDY EQU( 0x1 << 10 );
-( PMC ) PCK2_RDY स्थितिः / Enable / Disable / आवरणम्_2
AT91C_PMC_PCK3RDY EQU( 0x1 << 11 );
-( PMC ) PCK3_RDY स्थितिः / Enable / Disable / आवरणम्_2
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
AT91_C_RSTC_कुञ्चिका EQU( 0xFF << 24 );
-( RSTC ) Password
/* - -------- RSTC_RSR : (RSTC Offset: 0x4) Reset Status Register -------- */
AT91C_RSTC_URSTS EQU( 0x1 << 0 );
-( RSTC ) User Reset स्थितिः
AT91C_RSTC_BODSTS EQU( 0x1 << 1 );
-( RSTC ) Brownout Detection स्थितिः
AT91C_RSTC_RSTTYP EQU( 0x7 << 8 );
-( RSTC ) Reset Type
AT91C_RSTC_RSTTYP_POWERUP EQU( 0x0 << 8 );
-( RSTC ) Power - ऊर्ध्वम् Reset.VDDCORE rising.
   AT91C_RSTC_RSTTYP_WAKEUP EQU( 0x1 << 8 );
-( RSTC ) Wake_ऊर्ध्वम् Reset.VDDCORE rising.
   AT91C_RSTC_RSTTYP_WATCHDOG EQU( 0x2 << 8 );
-( RSTC ) Watchdog Reset.Watchdog अतिप्रवाहः occurred.
   AT91C_RSTC_RSTTYP_SOFTWARE EQU( 0x3 << 8 );
-( RSTC ) Software Reset.Processor reset required by the software.
   AT91C_RSTC_RSTTYP_USER EQU( 0x4 << 8 );
-( RSTC ) User Reset.NRST pin detected नीचः_2.
   AT91C_RSTC_RSTTYP_BROWNOUT EQU( 0x5 << 8 );
-( RSTC ) Brownout Reset occurred.
   AT91C_RSTC_NRSTL EQU( 0x1 << 16 );
-( RSTC ) NRST pin level
AT91C_RSTC_SRCMP EQU( 0x1 << 17 );
-( RSTC ) Software Reset Command अन्तर् प्रगतिः.
/* - -------- RSTC_RMR : (RSTC Offset: 0x8) Reset Mode Register -------- */
   AT91C_RSTC_URSTEN EQU( 0x1 << 0 );
-( RSTC ) User Reset Enable
AT91C_RSTC_URSTIEN EQU( 0x1 << 4 );
-( RSTC ) User Reset व्यवधानम्_2 Enable
AT91C_RSTC_ERSTL EQU( 0xF << 8 );
-( RSTC ) User Reset Enable
AT91C_RSTC_BODIEN EQU( 0x1 << 16 );
-( RSTC ) Brownout Detection व्यवधानम्_2 Enable

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Real Time Timer Controller Interface */
/* - ***************************************************************************** */
/* - -------- RTTC_RTMR : (RTTC Offset: 0x0) Real-time Mode Register -------- */
AT91C_RTTC_RTPRES EQU( 0xFFFF << 0 );
-( RTTC ) Real - time Timer Prescaler मानम्_2
AT91C_RTTC_ALMIEN EQU( 0x1 << 16 );
-( RTTC ) Alarm व्यवधानम्_2 Enable
AT91C_RTTC_RTTINCIEN EQU( 0x1 << 17 );
-( RTTC ) Real Time Timer Increment व्यवधानम्_2 Enable
AT91C_RTTC_RTTRST EQU( 0x1 << 18 );
-( RTTC ) Real Time Timer Restart
/* - -------- RTTC_RTAR : (RTTC Offset: 0x4) Real-time Alarm Register -------- */
AT91C_RTTC_ALMV EQU( 0x0 << 0 );
-( RTTC ) Alarm मानम्_2
/* - -------- RTTC_RTVR : (RTTC Offset: 0x8) Current Real-time Value Register -------- */
AT91C_RTTC_CRTV EQU( 0x0 << 0 );
-( RTTC ) Current Real - time मानम्_2
/* - -------- RTTC_RTSR : (RTTC Offset: 0xc) Real-time Status Register -------- */
AT91C_RTTC_ALMS EQU( 0x1 << 0 );
-( RTTC ) Real - time Alarm स्थितिः
AT91C_RTTC_RTTINC EQU( 0x1 << 1 );
-( RTTC ) Real - time Timer Increment

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Periodic Interval Timer Controller Interface */
/* - ***************************************************************************** */
/* - -------- PITC_PIMR : (PITC Offset: 0x0) Periodic Interval Mode Register -------- */
AT91C_PITC_PIV EQU( 0xFFFFF << 0 );
-( PITC ) Periodic Interval मानम्_2
AT91C_PITC_PITEN EQU( 0x1 << 24 );
-( PITC ) Periodic Interval Timer Enabled
AT91C_PITC_PITIEN EQU( 0x1 << 25 );
-( PITC ) Periodic Interval Timer व्यवधानम्_2 Enable
/* - -------- PITC_PISR : (PITC Offset: 0x4) Periodic Interval Status Register -------- */
AT91C_PITC_PITS EQU( 0x1 << 0 );
-( PITC ) Periodic Interval Timer स्थितिः
/* - -------- PITC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register -------- */
AT91C_PITC_CPIV EQU( 0xFFFFF << 0 );
-( PITC ) Current Periodic Interval मानम्_2
AT91C_PITC_PICNT EQU( 0xFFF << 20 );
-( PITC ) Periodic Interval गणक_2
/* - -------- PITC_PIIR : (PITC Offset: 0xc) Periodic Interval Image Register -------- */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Watchdog Timer Controller Interface */
/* - ***************************************************************************** */
/* - -------- WDTC_WDCR : (WDTC Offset: 0x0) Periodic Interval Image Register -------- */
AT91C_WDTC_WDRSTT EQU( 0x1 << 0 );
-( WDTC ) Watchdog Restart
AT91_C_WDTC_कुञ्चिका EQU( 0xFF << 24 );
-( WDTC ) Watchdog कुञ्चिका Password
/* - -------- WDTC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register -------- */
AT91C_WDTC_WDV EQU( 0xFFF << 0 );
-( WDTC ) Watchdog Timer Restart
AT91C_WDTC_WDFIEN EQU( 0x1 << 12 );
-( WDTC ) Watchdog Fault व्यवधानम्_2 Enable
AT91C_WDTC_WDRSTEN EQU( 0x1 << 13 );
-( WDTC ) Watchdog Reset Enable
AT91C_WDTC_WDRPROC EQU( 0x1 << 14 );
-( WDTC ) Watchdog Timer Restart
AT91C_WDTC_WDDIS EQU( 0x1 << 15 );
-( WDTC ) Watchdog Disable
AT91C_WDTC_WDD EQU( 0xFFF << 16 );
-( WDTC ) Watchdog Delta मानम्_2
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
-( VREG ) Voltage Regulator Power Standby बहुलकम्

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Memory Controller Interface */
/* - ***************************************************************************** */
/* - -------- MC_RCR : (MC Offset: 0x0) MC Remap Control Register -------- */
AT91C_MC_RCB EQU( 0x1 << 0 );
-( MC ) Remap Command Bit
/* - -------- MC_ASR : (MC Offset: 0x4) MC Abort Status Register -------- */
AT91C_MC_UNDADD EQU( 0x1 << 0 );
-( MC ) Undefined स्थानाङ्कः Abort स्थितिः
AT91C_MC_MISADD EQU( 0x1 << 1 );
-( MC ) Misaligned स्थानाङ्कः Abort स्थितिः
AT91C_MC_ABTSZ EQU( 0x3 << 8 );
-( MC ) Abort आकार_2 स्थितिः
AT91C_MC_ABTSZ_BYTE EQU( 0x0 << 8 );
-( MC ) Byte
AT91C_MC_ABTSZ_HWORD EQU( 0x1 << 8 );
-( MC ) Half - word
AT91C_MC_ABTSZ_WORD EQU( 0x2 << 8 );
-( MC ) Word
AT91C_MC_ABTTYP EQU( 0x3 << 10 );
-( MC ) Abort Type स्थितिः
AT91C_MC_ABTTYP_DATAR EQU( 0x0 << 10 );
-( MC ) दत्त Read
AT91C_MC_ABTTYP_DATAW EQU( 0x1 << 10 );
-( MC ) दत्त Write
AT91C_MC_ABTTYP_FETCH EQU( 0x2 << 10 );
-( MC ) संहिता_2 Fetch
AT91C_MC_MST0 EQU( 0x1 << 16 );
-( MC ) Master 0 Abort Source
AT91C_MC_MST1 EQU( 0x1 << 17 );
-( MC ) Master 1 Abort Source
AT91C_MC_SVMST0 EQU( 0x1 << 24 );
-( MC ) Saved Master 0 Abort Source
AT91C_MC_SVMST1 EQU( 0x1 << 25 );
-( MC ) Saved Master 1 Abort Source
/* - -------- MC_FMR : (MC Offset: 0x60) MC Flash Mode Register -------- */
AT91C_MC_FRDY EQU( 0x1 << 0 );
-( MC ) Flash Ready
AT91C_MC_LOCKE EQU( 0x1 << 2 );
-( MC ) तालकम् Error
AT91C_MC_PROGE EQU( 0x1 << 3 );
-( MC ) Programming Error
AT91C_MC_NEBP EQU( 0x1 << 7 );
-( MC ) No Erase Before Programming
AT91C_MC_FWS EQU( 0x3 << 8 );
-( MC ) Flash Wait State
AT91C_MC_FWS_0FWS EQU( 0x0 << 8 );
-( MC ) 1 आवृत्तिः

प्रति Read, 2

प्रति Write operations
AT91C_MC_FWS_1FWS EQU( 0x1 << 8 );
-( MC ) 2 आवृत्तयः

प्रति Read, 3

प्रति Write operations
AT91C_MC_FWS_2FWS EQU( 0x2 << 8 );
-( MC ) 3 आवृत्तयः

प्रति Read, 4

प्रति Write operations
AT91C_MC_FWS_3FWS EQU( 0x3 << 8 );
-( MC ) 4 आवृत्तयः

प्रति Read, 4

प्रति Write operations
AT91C_MC_FMCN EQU( 0xFF << 16 );
-( MC ) Flash Microsecond आवृत्तिः_2 सङ्ख्या_2
/* - -------- MC_FCR : (MC Offset: 0x64) MC Flash Command Register -------- */
AT91C_MC_FCMD EQU( 0xF << 0 );
-( MC ) Flash Command
AT91C_MC_FCMD_START_PROG EQU( 0x1 );
-( MC ) Starts the programming सम्बन्धि th epage specified by PAGEN.
   AT91_C_MC_FCMD_तालकम् EQU( 0x2 );
-( MC ) Starts a तालकम्_2 sequence सम्बन्धि the sector defined by the द्वयङ्काः_2 4 गन्तव्यम् 7 सम्बन्धि the क्षेत्रम् PAGEN.
   AT91_C_MC_FCMD_PROG_AND_तालकम् EQU( 0x3 );
-( MC ) The तालकम्_2 sequence automatically happens after the programming sequence is completed.
   AT91C_MC_FCMD_UNLOCK EQU( 0x4 );
-( MC ) Starts an unlock sequence सम्बन्धि the sector defined by the द्वयङ्काः_2 4 गन्तव्यम् 7 सम्बन्धि the क्षेत्रम् PAGEN.
   AT91C_MC_FCMD_ERASE_ALL EQU( 0x8 );
-( MC ) Starts the erase सम्बन्धि the entire flash.If at न्यूनतमम् a page is locked, the command is cancelled.
   AT91_C_MC_FCMD_समुच्चयः_GP_NVM EQU( 0xB );
-( MC ) समुच्चयः_2 General Purpose NVM द्वयङ्काः_2.
   AT91C_MC_FCMD_CLR_GP_NVM EQU( 0xD );
-( MC ) Clear General Purpose NVM द्वयङ्काः_2.
   AT91_C_MC_FCMD_समुच्चयः_SECURITY EQU( 0xF );
-( MC ) समुच्चयः_2 Security Bit.
   AT91C_MC_PAGEN EQU( 0x3FF << 8 );
-( MC ) Page सङ्ख्या_2
AT91_C_MC_कुञ्चिका EQU( 0xFF << 24 );
-( MC ) Writing Protect कुञ्चिका_2
/* - -------- MC_FSR : (MC Offset: 0x68) MC Flash Command Register -------- */
AT91C_MC_SECURITY EQU( 0x1 << 4 );
-( MC ) Security Bit स्थितिः
AT91C_MC_GPNVM0 EQU( 0x1 << 8 );
-( MC ) Sector 0 तालकम् स्थितिः
AT91C_MC_GPNVM1 EQU( 0x1 << 9 );
-( MC ) Sector 1 तालकम् स्थितिः
AT91C_MC_GPNVM2 EQU( 0x1 << 10 );
-( MC ) Sector 2 तालकम् स्थितिः
AT91C_MC_GPNVM3 EQU( 0x1 << 11 );
-( MC ) Sector 3 तालकम् स्थितिः
AT91C_MC_GPNVM4 EQU( 0x1 << 12 );
-( MC ) Sector 4 तालकम् स्थितिः
AT91C_MC_GPNVM5 EQU( 0x1 << 13 );
-( MC ) Sector 5 तालकम् स्थितिः
AT91C_MC_GPNVM6 EQU( 0x1 << 14 );
-( MC ) Sector 6 तालकम् स्थितिः
AT91C_MC_GPNVM7 EQU( 0x1 << 15 );
-( MC ) Sector 7 तालकम् स्थितिः
AT91C_MC_LOCKS0 EQU( 0x1 << 16 );
-( MC ) Sector 0 तालकम् स्थितिः
AT91C_MC_LOCKS1 EQU( 0x1 << 17 );
-( MC ) Sector 1 तालकम् स्थितिः
AT91C_MC_LOCKS2 EQU( 0x1 << 18 );
-( MC ) Sector 2 तालकम् स्थितिः
AT91C_MC_LOCKS3 EQU( 0x1 << 19 );
-( MC ) Sector 3 तालकम् स्थितिः
AT91C_MC_LOCKS4 EQU( 0x1 << 20 );
-( MC ) Sector 4 तालकम् स्थितिः
AT91C_MC_LOCKS5 EQU( 0x1 << 21 );
-( MC ) Sector 5 तालकम् स्थितिः
AT91C_MC_LOCKS6 EQU( 0x1 << 22 );
-( MC ) Sector 6 तालकम् स्थितिः
AT91C_MC_LOCKS7 EQU( 0x1 << 23 );
-( MC ) Sector 7 तालकम् स्थितिः
AT91C_MC_LOCKS8 EQU( 0x1 << 24 );
-( MC ) Sector 8 तालकम् स्थितिः
AT91C_MC_LOCKS9 EQU( 0x1 << 25 );
-( MC ) Sector 9 तालकम् स्थितिः
AT91C_MC_LOCKS10 EQU( 0x1 << 26 );
-( MC ) Sector 10 तालकम् स्थितिः
AT91C_MC_LOCKS11 EQU( 0x1 << 27 );
-( MC ) Sector 11 तालकम् स्थितिः
AT91C_MC_LOCKS12 EQU( 0x1 << 28 );
-( MC ) Sector 12 तालकम् स्थितिः
AT91C_MC_LOCKS13 EQU( 0x1 << 29 );
-( MC ) Sector 13 तालकम् स्थितिः
AT91C_MC_LOCKS14 EQU( 0x1 << 30 );
-( MC ) Sector 14 तालकम् स्थितिः
AT91C_MC_LOCKS15 EQU( 0x1 << 31 );
-( MC ) Sector 15 तालकम् स्थितिः

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
-( SPI ) SPI चरमः Transfer
/* - -------- SPI_MR : (SPI Offset: 0x4) SPI Mode Register -------- */
AT91C_SPI_MSTR EQU( 0x1 << 0 );
-( SPI ) Master / Slave बहुलकम्
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
-( SPI ) बहुलकम् Fault Detection
AT91C_SPI_LLB EQU( 0x1 << 7 );
-( SPI ) Clock Selection
AT91C_SPI_PCS EQU( 0xF << 16 );
-( SPI ) Peripheral Chip Select
AT91C_SPI_DLYBCS EQU( 0xFF << 24 );
-( SPI ) Delay Between Chip Selects
/* - -------- SPI_RDR : (SPI Offset: 0x8) Receive Data Register -------- */
AT91C_SPI_RD EQU( 0xFFFF << 0 );
-( SPI ) Receive दत्त
AT91C_SPI_RPCS EQU( 0xF << 16 );
-( SPI ) Peripheral Chip Select स्थितिः
/* - -------- SPI_TDR : (SPI Offset: 0xc) Transmit Data Register -------- */
AT91C_SPI_TD EQU( 0xFFFF << 0 );
-( SPI ) Transmit दत्त
AT91C_SPI_TPCS EQU( 0xF << 16 );
-( SPI ) Peripheral Chip Select स्थितिः
/* - -------- SPI_SR : (SPI Offset: 0x10) Status Register -------- */
AT91C_SPI_RDRF EQU( 0x1 << 0 );
-( SPI ) Receive दत्त पञ्जिकाकोशः पूर्णम्
AT91C_SPI_TDRE EQU( 0x1 << 1 );
-( SPI ) Transmit दत्त पञ्जिकाकोशः रिक्तानि
AT91C_SPI_MODF EQU( 0x1 << 2 );
-( SPI ) बहुलकम् Fault Error
AT91C_SPI_OVRES EQU( 0x1 << 3 );
-( SPI ) Overrun Error स्थितिः
AT91C_SPI_ENDRX EQU( 0x1 << 4 );
-( SPI ) अन्तः_3 सम्बन्धि Receiver Transfer
AT91C_SPI_ENDTX EQU( 0x1 << 5 );
-( SPI ) अन्तः_3 सम्बन्धि Receiver Transfer
AT91C_SPI_RXBUFF EQU( 0x1 << 6 );
-( SPI ) RXBUFF व्यवधानम्_2
AT91C_SPI_TXBUFE EQU( 0x1 << 7 );
-( SPI ) TXBUFE व्यवधानम्_2
AT91C_SPI_NSSR EQU( 0x1 << 8 );
-( SPI ) NSSR व्यवधानम्_2
AT91C_SPI_TXEMPTY EQU( 0x1 << 9 );
-( SPI ) TXEMPTY व्यवधानम्_2
AT91C_SPI_SPIENS EQU( 0x1 << 16 );
-( SPI ) Enable स्थितिः
/* - -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- */
/* - -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- */
/* - -------- SPI_IMR : (SPI Offset: 0x1c) Interrupt Mask Register -------- */
/* - -------- SPI_CSR : (SPI Offset: 0x30) Chip Select Register -------- */
AT91C_SPI_CPOL EQU( 0x1 << 0 );
-( SPI ) Clock Polarity
AT91C_SPI_NCPHA EQU( 0x1 << 1 );
-( SPI ) Clock Phase
AT91C_SPI_CSAAT EQU( 0x1 << 3 );
-( SPI ) Chip Select सक्रिय After Transfer
AT91_C_SPI_द्वयङ्काः EQU( 0xF << 4 );
-( SPI ) द्वयङ्काः प्रत्येकम् Transfer
AT91_C_SPI_द्वयङ्काः_8 EQU( 0x0 << 4 );
-( SPI ) 8 द्वयङ्काः प्रत्येकम् transfer
AT91_C_SPI_द्वयङ्काः_9 EQU( 0x1 << 4 );
-( SPI ) 9 द्वयङ्काः प्रत्येकम् transfer
AT91_C_SPI_द्वयङ्काः_10 EQU( 0x2 << 4 );
-( SPI ) 10 द्वयङ्काः प्रत्येकम् transfer
AT91_C_SPI_द्वयङ्काः_11 EQU( 0x3 << 4 );
-( SPI ) 11 द्वयङ्काः प्रत्येकम् transfer
AT91_C_SPI_द्वयङ्काः_12 EQU( 0x4 << 4 );
-( SPI ) 12 द्वयङ्काः प्रत्येकम् transfer
AT91_C_SPI_द्वयङ्काः_13 EQU( 0x5 << 4 );
-( SPI ) 13 द्वयङ्काः प्रत्येकम् transfer
AT91_C_SPI_द्वयङ्काः_14 EQU( 0x6 << 4 );
-( SPI ) 14 द्वयङ्काः प्रत्येकम् transfer
AT91_C_SPI_द्वयङ्काः_15 EQU( 0x7 << 4 );
-( SPI ) 15 द्वयङ्काः प्रत्येकम् transfer
AT91_C_SPI_द्वयङ्काः_16 EQU( 0x8 << 4 );
-( SPI ) 16 द्वयङ्काः प्रत्येकम् transfer
AT91C_SPI_SCBR EQU( 0xFF << 8 );
-( SPI ) Serial Clock Baud दरः
AT91C_SPI_DLYBS EQU( 0xFF << 16 );
-( SPI ) Delay Before SPCK
AT91C_SPI_DLYBCT EQU( 0xFF << 24 );
-( SPI ) Delay Between Consecutive Transfers

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Usart */
/* - ***************************************************************************** */
/* - -------- US_CR : (USART Offset: 0x0) Debug Unit Control Register -------- */
AT91C_US_STTBRK EQU( 0x1 << 9 );
-( USART ) Start Break
AT91C_US_STPBRK EQU( 0x1 << 10 );
-( USART ) Stop Break
AT91C_US_STTTO EQU( 0x1 << 11 );
-( USART ) Start Time - बहिर्गमनम्
AT91C_US_SENDA EQU( 0x1 << 12 );
-( USART ) Send स्थानाङ्कः
AT91C_US_RSTIT EQU( 0x1 << 13 );
-( USART ) Reset Iterations
AT91C_US_RSTNACK EQU( 0x1 << 14 );
-( USART ) Reset Non Acknowledge
AT91C_US_RETTO EQU( 0x1 << 15 );
-( USART ) Rearm Time - बहिर्गमनम्
AT91C_US_DTREN EQU( 0x1 << 16 );
-( USART ) दत्त Terminal ready Enable
AT91C_US_DTRDIS EQU( 0x1 << 17 );
-( USART ) दत्त Terminal ready Disable
AT91C_US_RTSEN EQU( 0x1 << 18 );
-( USART ) Request गन्तव्यम् Send enable
AT91C_US_RTSDIS EQU( 0x1 << 19 );
-( USART ) Request गन्तव्यम् Send Disable
/* - -------- US_MR : (USART Offset: 0x4) Debug Unit Mode Register -------- */
AT91C_US_USMODE EQU( 0xF << 0 );
-( USART ) Usart बहुलकम्_2
AT91_C_US_USMODE_प्रसामान्यम् EQU( 0x0 );
-( USART ) प्रसामान्यम्
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
-( USART ) Clock Selection ( Baud दरः generator निवेशः Clock
                             AT91C_US_CLKS_CLOCK EQU( 0x0 << 4 );
                             -( USART ) Clock
                             AT91C_US_CLKS_FDIV1 EQU( 0x1 << 4 );
                             -( USART ) fdiv1
                             AT91C_US_CLKS_SLOW EQU( 0x2 << 4 );
                             -( USART ) slow_clock( ARM )
                             AT91C_US_CLKS_EXT EQU( 0x3 << 4 );
                             -( USART ) External( SCK )
                             AT91C_US_CHRL EQU( 0x3 << 6 );
                             -( USART ) Clock Selection ( Baud दरः generator निवेशः Clock
                                                          AT91_C_US_CHRL_5_द्वयङ्काः EQU( 0x0 << 6 );
                                                          -( USART ) Character दीर्घता_2 : 5 द्वयङ्काः_2
                                                          AT91_C_US_CHRL_6_द्वयङ्काः EQU( 0x1 << 6 );
                                                          -( USART ) Character दीर्घता_2 : 6 द्वयङ्काः_2
                                                          AT91_C_US_CHRL_7_द्वयङ्काः EQU( 0x2 << 6 );
                                                          -( USART ) Character दीर्घता_2 : 7 द्वयङ्काः_2
                                                          AT91_C_US_CHRL_8_द्वयङ्काः EQU( 0x3 << 6 );
                                                          -( USART ) Character दीर्घता_2 : 8 द्वयङ्काः_2
                                                          AT91C_US_SYNC EQU( 0x1 << 8 );
                                                          -( USART ) Synchronous बहुलकम् Select
                                                          AT91C_US_NBSTOP EQU( 0x3 << 12 );
                                                          -( USART ) सङ्ख्या_2 सम्बन्धि Stop द्वयङ्काः_2
                                                          AT91C_US_NBSTOP_1_BIT EQU( 0x0 << 12 );
                                                          -( USART ) 1 stop bit
                                                          AT91C_US_NBSTOP_15_BIT EQU( 0x1 << 12 );
                                                          -( USART ) Asynchronous( SYNC = 0 ) 2 stop द्वयङ्काः_2 Synchronous( SYNC = 1 ) 2 stop द्वयङ्काः_2
                                                          AT91C_US_NBSTOP_2_BIT EQU( 0x2 << 12 );
                                                          -( USART ) 2 stop द्वयङ्काः_2
                                                          AT91C_US_MSBF EQU( 0x1 << 16 );
                                                          -( USART ) Bit क्रमः_2
                                                          AT91C_US_MODE9 EQU( 0x1 << 17 );
                                                          -( USART ) 9 - bit Character दीर्घता_3
                                                          AT91C_US_CKLO EQU( 0x1 << 18 );
                                                          -( USART ) Clock Output Select
                                                          AT91C_US_OVER EQU( 0x1 << 19 );
                                                          -( USART ) Over Sampling बहुलकम्
                                                          AT91C_US_INACK EQU( 0x1 << 20 );
                                                          -( USART ) Inhibit Non Acknowledge
                                                          AT91C_US_DSNACK EQU( 0x1 << 21 );
                                                          -( USART ) Disable Successive NACK
                                                          AT91C_US_MAX_ITER EQU( 0x1 << 24 );
                                                          -( USART ) सङ्ख्या_2 सम्बन्धि Repetitions
                                                          AT91C_US_FILTER EQU( 0x1 << 28 );
                                                          -( USART ) Receive पङ्क्तिः_2 Filter
/* - -------- US_IER : (USART Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
                                                          AT91C_US_RXBRK EQU( 0x1 << 2 );
                                                          -( USART ) Break Received / अन्तः_3 सम्बन्धि Break
                                                          AT91C_US_TIMEOUT EQU( 0x1 << 8 );
                                                          -( USART ) Receiver Time - बहिर्गमनम्
                                                          AT91C_US_ITERATION EQU( 0x1 << 10 );
                                                          -( USART ) Max सङ्ख्या सम्बन्धि Repetitions Reached
                                                          AT91C_US_NACK EQU( 0x1 << 13 );
                                                          -( USART ) Non Acknowledge
                                                          AT91C_US_RIIC EQU( 0x1 << 16 );
                                                          -( USART ) Ring INdicator निवेशः Change Flag
                                                          AT91C_US_DSRIC EQU( 0x1 << 17 );
                                                          -( USART ) दत्त समुच्चयः_2 Ready निवेशः Change Flag
                                                          AT91C_US_DCDIC EQU( 0x1 << 18 );
                                                          -( USART ) दत्त Carrier Flag
                                                          AT91C_US_CTSIC EQU( 0x1 << 19 );
                                                          -( USART ) Clear गन्तव्यम्_2 Send निवेशः Change Flag
/* - -------- US_IDR : (USART Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* - -------- US_IMR : (USART Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* - -------- US_CSR : (USART Offset: 0x14) Debug Unit Channel Status Register -------- */
                                                          AT91C_US_RI EQU( 0x1 << 20 );
                                                          -( USART ) Image सम्बन्धि RI निवेशः
                                                          AT91C_US_DSR EQU( 0x1 << 21 );
                                                          -( USART ) Image सम्बन्धि DSR निवेशः
                                                          AT91C_US_DCD EQU( 0x1 << 22 );
                                                          -( USART ) Image सम्बन्धि DCD निवेशः
                                                          AT91C_US_CTS EQU( 0x1 << 23 );
                                                          -( USART ) Image सम्बन्धि CTS निवेशः

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
                                                          -( SSC ) TK Clock सङ्केत
                                                          AT91C_SSC_CKS_RK EQU( 0x2 );
                                                          -( SSC ) RK pin
                                                          AT91C_SSC_CKO EQU( 0x7 << 2 );
                                                          -( SSC ) Receive / Transmit Clock Output बहुलकम् Selection
                                                          AT91C_SSC_CKO_NONE EQU( 0x0 << 2 );
                                                          -( SSC ) Receive / Transmit Clock Output बहुलकम्:None RK pin: निवेशः - only
                                                          AT91C_SSC_CKO_CONTINUOUS EQU( 0x1 << 2 );
                                                          -( SSC ) Continuous Receive / Transmit Clock RK pin:Output
                                                          AT91_C_SSC_CKO_दत्त_TX EQU( 0x2 << 2 );
                                                          -( SSC ) Receive / Transmit Clock only during दत्त_2 transfers RK pin:Output
                                                          AT91C_SSC_CKI EQU( 0x1 << 5 );
                                                          -( SSC ) Receive / Transmit Clock Inversion
                                                          AT91C_SSC_START EQU( 0xF << 8 );
                                                          -( SSC ) Receive / Transmit Start Selection
                                                          AT91C_SSC_START_CONTINUOUS EQU( 0x0 << 8 );
                                                          -( SSC ) Continuous, as soon as the receiver is enabled, and immediately after the अन्तः_2 सम्बन्धि transfer सम्बन्धि the previous दत्त_2.
                                                             AT91C_SSC_START_TX EQU( 0x1 << 8 );
                                                          -( SSC ) Transmit / Receive start
                                                          AT91_C_SSC_START_नीचः_RF EQU( 0x2 << 8 );
                                                          -( SSC ) Detection सम्बन्धि a नीचः_2 level on RF निवेशः_2
                                                          AT91_C_SSC_START_उच्चः_RF EQU( 0x3 << 8 );
                                                          -( SSC ) Detection सम्बन्धि a उच्चः_2 level on RF निवेशः_2
                                                          AT91C_SSC_START_FALL_RF EQU( 0x4 << 8 );
                                                          -( SSC ) Detection सम्बन्धि a falling edge on RF निवेशः_2
                                                          AT91C_SSC_START_RISE_RF EQU( 0x5 << 8 );
                                                          -( SSC ) Detection सम्बन्धि a rising edge on RF निवेशः_2
                                                          AT91C_SSC_START_LEVEL_RF EQU( 0x6 << 8 );
                                                          -( SSC ) Detection सम्बन्धि any level change on RF निवेशः_2
                                                          AT91C_SSC_START_EDGE_RF EQU( 0x7 << 8 );
                                                          -( SSC ) Detection सम्बन्धि any edge on RF निवेशः_2
                                                          AT91C_SSC_START_0 EQU( 0x8 << 8 );
                                                          -( SSC ) Compare 0
                                                          AT91C_SSC_STTDLY EQU( 0xFF << 16 );
                                                          -( SSC ) Receive / Transmit Start Delay
                                                          AT91C_SSC_PERIOD EQU( 0xFF << 24 );
                                                          -( SSC ) Receive / Transmit Period Divider Selection
/* - -------- SSC_RFMR : (SSC Offset: 0x14) SSC Receive Frame Mode Register -------- */
                                                          AT91C_SSC_DATLEN EQU( 0x1F << 0 );
                                                          -( SSC ) दत्त दीर्घता_2
                                                          AT91C_SSC_LOOP EQU( 0x1 << 5 );
                                                          -( SSC ) Loop बहुलकम्
                                                          AT91C_SSC_MSBF EQU( 0x1 << 7 );
                                                          -( SSC ) Most Significant Bit First
                                                          AT91C_SSC_DATNB EQU( 0xF << 8 );
                                                          -( SSC ) दत्त सङ्ख्या_2 प्रत्येकम्_2 Frame
                                                          AT91C_SSC_FSLEN EQU( 0xF << 16 );
                                                          -( SSC ) Receive / Transmit Frame Sync दीर्घता_3
                                                          AT91C_SSC_FSOS EQU( 0x7 << 20 );
                                                          -( SSC ) Receive / Transmit Frame Sync Output Selection
                                                          AT91C_SSC_FSOS_NONE EQU( 0x0 << 20 );
                                                          -( SSC ) Selected Receive / Transmit Frame Sync Signal:None RK pin निवेशः - only
                                                          AT91C_SSC_FSOS_NEGATIVE EQU( 0x1 << 20 );
                                                          -( SSC ) Selected Receive / Transmit Frame Sync Signal:Negative Pulse
                                                          AT91_C_SSC_FSOS_धनात्मकम् EQU( 0x2 << 20 );
                                                          -( SSC ) Selected Receive / Transmit Frame Sync Signal:धनात्मकम् Pulse
                                                          AT91_C_SSC_FSOS_नीचः EQU( 0x3 << 20 );
                                                          -( SSC ) Selected Receive / Transmit Frame Sync Signal:Driver नीचः during दत्त_2 transfer
                                                          AT91_C_SSC_FSOS_उच्चः EQU( 0x4 << 20 );
                                                          -( SSC ) Selected Receive / Transmit Frame Sync Signal:Driver उच्चः during दत्त_2 transfer
                                                          AT91C_SSC_FSOS_TOGGLE EQU( 0x5 << 20 );
                                                          -( SSC ) Selected Receive / Transmit Frame Sync Signal:Toggling at each start सम्बन्धि दत्त_2 transfer
                                                          AT91C_SSC_FSEDGE EQU( 0x1 << 24 );
                                                          -( SSC ) Frame Sync Edge Detection
/* - -------- SSC_TCMR : (SSC Offset: 0x18) SSC Transmit Clock Mode Register -------- */
/* - -------- SSC_TFMR : (SSC Offset: 0x1c) SSC Transmit Frame Mode Register -------- */
                                                          AT91C_SSC_DATDEF EQU( 0x1 << 5 );
                                                          -( SSC ) दत्त Default मानम्_2
                                                          AT91C_SSC_FSDEN EQU( 0x1 << 23 );
                                                          -( SSC ) Frame Sync दत्त Enable
/* - -------- SSC_SR : (SSC Offset: 0x40) SSC Status Register -------- */
                                                          AT91C_SSC_TXRDY EQU( 0x1 << 0 );
                                                          -( SSC ) Transmit Ready
                                                          AT91C_SSC_TXEMPTY EQU( 0x1 << 1 );
                                                          -( SSC ) Transmit रिक्तानि
                                                          AT91C_SSC_ENDTX EQU( 0x1 << 2 );
                                                          -( SSC ) अन्तः_3 सम्बन्धि_2 सम्प्रेषणम्
                                                          AT91C_SSC_TXBUFE EQU( 0x1 << 3 );
                                                          -( SSC ) Transmit बफर रिक्तानि
                                                          AT91C_SSC_RXRDY EQU( 0x1 << 4 );
                                                          -( SSC ) Receive Ready
                                                          AT91C_SSC_OVRUN EQU( 0x1 << 5 );
                                                          -( SSC ) Receive Overrun
                                                          AT91C_SSC_ENDRX EQU( 0x1 << 6 );
                                                          -( SSC ) अन्तः_3 सम्बन्धि Reception
                                                          AT91C_SSC_RXBUFF EQU( 0x1 << 7 );
                                                          -( SSC ) Receive बफर पूर्णम्
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
                                                          AT91C_TWI_START EQU( 0x1 << 0 );
                                                          -( TWI ) Send a START Condition
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
                                                          -( TWI ) आन्तरिकम् Device स्थानाङ्कः आकार_2
                                                          AT91C_TWI_IADRSZ_NO EQU( 0x0 << 8 );
                                                          -( TWI ) No आन्तरिकम्_2 device स्थानाङ्कः_2
                                                          AT91C_TWI_IADRSZ_1_BYTE EQU( 0x1 << 8 );
                                                          -( TWI ) One - byte आन्तरिकम्_2 device स्थानाङ्कः_2
                                                          AT91C_TWI_IADRSZ_2_BYTE EQU( 0x2 << 8 );
                                                          -( TWI ) Two - byte आन्तरिकम्_2 device स्थानाङ्कः_2
                                                          AT91C_TWI_IADRSZ_3_BYTE EQU( 0x3 << 8 );
                                                          -( TWI ) Three - byte आन्तरिकम्_2 device स्थानाङ्कः_2
                                                          AT91C_TWI_MREAD EQU( 0x1 << 12 );
                                                          -( TWI ) Master Read Direction
                                                          AT91C_TWI_DADR EQU( 0x7F << 16 );
                                                          -( TWI ) Device स्थानाङ्कः
/* - -------- TWI_CWGR : (TWI Offset: 0x10) TWI Clock Waveform Generator Register -------- */
                                                          AT91C_TWI_CLDIV EQU( 0xFF << 0 );
                                                          -( TWI ) Clock नीचः Divider
                                                          AT91C_TWI_CHDIV EQU( 0xFF << 8 );
                                                          -( TWI ) Clock उच्चः Divider
                                                          AT91C_TWI_CKDIV EQU( 0x7 << 16 );
                                                          -( TWI ) Clock Divider
/* - -------- TWI_SR : (TWI Offset: 0x20) TWI Status Register -------- */
                                                          AT91C_TWI_TXCOMP EQU( 0x1 << 0 );
                                                          -( TWI ) सम्प्रेषणम् Completed
                                                          AT91C_TWI_RXRDY EQU( 0x1 << 1 );
                                                          -( TWI ) Receive holding पञ्जिका ReaDY
                                                          AT91C_TWI_TXRDY EQU( 0x1 << 2 );
                                                          -( TWI ) Transmit holding पञ्जिका ReaDY
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
                                                          -( PWMC_CH ) Channel Duty आवृत्तिः_2
/* - -------- PWMC_CPRDR : (PWMC_CH Offset: 0x8) PWMC Channel Period Register -------- */
                                                          AT91C_PWMC_CPRD EQU( 0x0 << 0 );
                                                          -( PWMC_CH ) Channel Period
/* - -------- PWMC_CCNTR : (PWMC_CH Offset: 0xc) PWMC Channel Counter Register -------- */
                                                          AT91C_PWMC_CCNT EQU( 0x0 << 0 );
                                                          -( PWMC_CH ) Channel गणक_2
/* - -------- PWMC_CUPDR : (PWMC_CH Offset: 0x10) PWMC Channel Update Register -------- */
                                                          AT91C_PWMC_CUPD EQU( 0x0 << 0 );
                                                          -( PWMC_CH ) Channel Update

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Pulse Width Modulation Controller Interface */
/* - ***************************************************************************** */
/* - -------- PWMC_MR : (PWMC Offset: 0x0) PWMC Mode Register -------- */
                                                          AT91C_PWMC_DIVA EQU( 0xFF << 0 );
                                                          -( PWMC ) CLKA divide गुणकः.
                                                             AT91C_PWMC_PREA EQU( 0xF << 8 );
                                                          -( PWMC ) Divider निवेशः Clock Prescaler A
                                                          AT91C_PWMC_PREA_MCK EQU( 0x0 << 8 );
                                                          -( PWMC )
                                                          AT91C_PWMC_DIVB EQU( 0xFF << 16 );
                                                          -( PWMC ) CLKB divide गुणकः.
                                                             AT91C_PWMC_PREB EQU( 0xF << 24 );
                                                          -( PWMC ) Divider निवेशः Clock Prescaler B
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
                                                          AT91_C_UDP_FRM_अङ्कः EQU( 0x7FF << 0 );
                                                          -( UDP ) Frame सङ्ख्या_2 as Defined अन्तर् the Packet क्षेत्रम्_2 Formats
                                                          AT91C_UDP_FRM_ERR EQU( 0x1 << 16 );
                                                          -( UDP ) Frame Error
                                                          AT91C_UDP_FRM_OK EQU( 0x1 << 17 );
                                                          -( UDP ) Frame OK
/* - -------- UDP_GLB_STATE : (UDP Offset: 0x4) USB Global State Register -------- */
                                                          AT91C_UDP_FADDEN EQU( 0x1 << 0 );
                                                          -( UDP ) Function स्थानाङ्कः Enable
                                                          AT91C_UDP_CONFG EQU( 0x1 << 1 );
                                                          -( UDP ) Configured
                                                          AT91C_UDP_ESR EQU( 0x1 << 2 );
                                                          -( UDP ) Enable Send Resume
                                                          AT91C_UDP_RSMINPR EQU( 0x1 << 3 );
                                                          -( UDP ) A Resume Has Been प्रेषितम् गन्तव्यम् the Host
                                                          AT91C_UDP_RMWUPE EQU( 0x1 << 4 );
                                                          -( UDP ) Remote Wake ऊर्ध्वम्_2 Enable
/* - -------- UDP_FADDR : (UDP Offset: 0x8) USB Function Address Register -------- */
                                                          AT91C_UDP_FADD EQU( 0xFF << 0 );
                                                          -( UDP ) Function स्थानाङ्कः मानम्_2
                                                          AT91C_UDP_FEN EQU( 0x1 << 8 );
                                                          -( UDP ) Function Enable
/* - -------- UDP_IER : (UDP Offset: 0x10) USB Interrupt Enable Register -------- */
                                                          AT91C_UDP_EPINT0 EQU( 0x1 << 0 );
                                                          -( UDP ) Endpoint 0 व्यवधानम्_2
                                                          AT91C_UDP_EPINT1 EQU( 0x1 << 1 );
                                                          -( UDP ) Endpoint 0 व्यवधानम्_2
                                                          AT91C_UDP_EPINT2 EQU( 0x1 << 2 );
                                                          -( UDP ) Endpoint 2 व्यवधानम्_2
                                                          AT91C_UDP_EPINT3 EQU( 0x1 << 3 );
                                                          -( UDP ) Endpoint 3 व्यवधानम्_2
                                                          AT91C_UDP_EPINT4 EQU( 0x1 << 4 );
                                                          -( UDP ) Endpoint 4 व्यवधानम्_2
                                                          AT91C_UDP_EPINT5 EQU( 0x1 << 5 );
                                                          -( UDP ) Endpoint 5 व्यवधानम्_2
                                                          AT91C_UDP_RXSUSP EQU( 0x1 << 8 );
                                                          -( UDP ) USB Suspend व्यवधानम्_2
                                                          AT91C_UDP_RXRSM EQU( 0x1 << 9 );
                                                          -( UDP ) USB Resume व्यवधानम्_2
                                                          AT91C_UDP_EXTRSM EQU( 0x1 << 10 );
                                                          -( UDP ) USB External Resume व्यवधानम्_2
                                                          AT91C_UDP_SOFINT EQU( 0x1 << 11 );
                                                          -( UDP ) USB Start सम्बन्धि_2 frame व्यवधानम्_2
                                                          AT91C_UDP_WAKEUP EQU( 0x1 << 13 );
                                                          -( UDP ) USB Resume व्यवधानम्_2
/* - -------- UDP_IDR : (UDP Offset: 0x14) USB Interrupt Disable Register -------- */
/* - -------- UDP_IMR : (UDP Offset: 0x18) USB Interrupt Mask Register -------- */
/* - -------- UDP_ISR : (UDP Offset: 0x1c) USB Interrupt Status Register -------- */
                                                          AT91C_UDP_ENDBUSRES EQU( 0x1 << 12 );
                                                          -( UDP ) USB अन्तः_3 सम्बन्धि_2 Bus Reset व्यवधानम्_2
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
                                                          -( UDP ) Generates an अन्तर्_2 packet with दत्त_2 previously written अन्तर् the DPR
                                                          AT91_C_UDP_RX_दत्त_BK0 EQU( 0x1 << 1 );
                                                          -( UDP ) Receive दत्त Bank 0
                                                          AT91C_UDP_RXSETUP EQU( 0x1 << 2 );
                                                          -( UDP ) Sends STALL गन्तव्यम् the Host( Control endpoints )
                                                          AT91C_UDP_ISOERROR EQU( 0x1 << 3 );
                                                          -( UDP ) Isochronous error( Isochronous endpoints )
                                                          AT91C_UDP_TXPKTRDY EQU( 0x1 << 4 );
                                                          -( UDP ) Transmit Packet Ready
                                                          AT91C_UDP_FORCESTALL EQU( 0x1 << 5 );
                                                          -( UDP ) Force Stall( प्रयुक्तम् by Control, Bulk and Isochronous endpoints ).
                                                             AT91_C_UDP_RX_दत्त_BK1 EQU( 0x1 << 6 );
                                                          -( UDP ) Receive दत्त Bank 1 ( only प्रयुक्तम् by endpoints with ping - pong गुणाः ).
                                                             AT91C_UDP_DIR EQU( 0x1 << 7 );
                                                          -( UDP ) Transfer Direction
                                                          AT91C_UDP_EPTYPE EQU( 0x7 << 8 );
                                                          -( UDP ) Endpoint type
                                                          AT91C_UDP_EPTYPE_CTRL EQU( 0x0 << 8 );
                                                          -( UDP ) Control
                                                          AT91_C_UDP_EPTYPE_ISO_बहिर्गमनम् EQU( 0x1 << 8 );
                                                          -( UDP ) Isochronous बहिर्गमनम्_2
                                                          AT91_C_UDP_EPTYPE_BULK_बहिर्गमनम् EQU( 0x2 << 8 );
                                                          -( UDP ) Bulk बहिर्गमनम्_2
                                                          AT91_C_UDP_EPTYPE_INT_बहिर्गमनम् EQU( 0x3 << 8 );
                                                          -( UDP ) व्यवधानम्_2 बहिर्गमनम्_2
                                                          AT91_C_UDP_EPTYPE_ISO_अन्तर् EQU( 0x5 << 8 );
                                                          -( UDP ) Isochronous अन्तर्_2
                                                          AT91_C_UDP_EPTYPE_BULK_अन्तर् EQU( 0x6 << 8 );
                                                          -( UDP ) Bulk अन्तर्_2
                                                          AT91_C_UDP_EPTYPE_INT_अन्तर् EQU( 0x7 << 8 );
                                                          -( UDP ) व्यवधानम्_2 अन्तर्_2
                                                          AT91C_UDP_DTGLE EQU( 0x1 << 11 );
                                                          -( UDP ) दत्त Toggle
                                                          AT91C_UDP_EPEDS EQU( 0x1 << 15 );
                                                          -( UDP ) Endpoint Enable Disable
                                                          AT91C_UDP_RXBYTECNT EQU( 0x7FF << 16 );
                                                          -( UDP ) सङ्ख्या_2 सम्बन्धि_2 अष्टकानि उपलब्धम्_2 अन्तर् the FIFO
/* - -------- UDP_TXVC : (UDP Offset: 0x74) Transceiver Control Register -------- */
                                                          AT91C_UDP_TXVDIS EQU( 0x1 << 8 );
                                                          -( UDP )
                                                          AT91C_UDP_PUON EQU( 0x1 << 9 );
                                                          -( UDP ) Pull - ऊर्ध्वम् ON

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Timer Counter Channel Interface */
/* - ***************************************************************************** */
/* - -------- TC_CCR : (TC Offset: 0x0) TC Channel Control Register -------- */
                                                          AT91C_TC_CLKEN EQU( 0x1 << 0 );
                                                          -( TC ) गणक_2 Clock Enable Command
                                                          AT91C_TC_CLKDIS EQU( 0x1 << 1 );
                                                          -( TC ) गणक_2 Clock Disable Command
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
                                                          AT91C_TC_BURST EQU( 0x3 << 4 );
                                                          -( TC ) Burst Signal Selection
                                                          AT91C_TC_BURST_NONE EQU( 0x0 << 4 );
                                                          -( TC ) The clock is not gated by an external सङ्केत
                                                          AT91C_TC_BURST_XC0 EQU( 0x1 << 4 );
                                                          -( TC ) XC0 is ANDed with the selected clock
                                                          AT91C_TC_BURST_XC1 EQU( 0x2 << 4 );
                                                          -( TC ) XC1 is ANDed with the selected clock
                                                          AT91C_TC_BURST_XC2 EQU( 0x3 << 4 );
                                                          -( TC ) XC2 is ANDed with the selected clock
                                                          AT91C_TC_CPCSTOP EQU( 0x1 << 6 );
                                                          -( TC ) गणक_2 Clock Stopped with RC Compare
                                                          AT91C_TC_LDBSTOP EQU( 0x1 << 6 );
                                                          -( TC ) गणक_2 Clock Stopped with RB Loading
                                                          AT91C_TC_CPCDIS EQU( 0x1 << 7 );
                                                          -( TC ) गणक_2 Clock Disable with RC Compare
                                                          AT91C_TC_LDBDIS EQU( 0x1 << 7 );
                                                          -( TC ) गणक_2 Clock Disabled with RB Loading
                                                          AT91C_TC_ETRGEDG EQU( 0x3 << 8 );
                                                          -( TC ) External Trigger Edge Selection
                                                          AT91C_TC_ETRGEDG_NONE EQU( 0x0 << 8 );
                                                          -( TC ) Edge:None
                                                          AT91C_TC_ETRGEDG_RISING EQU( 0x1 << 8 );
                                                          -( TC ) Edge:rising edge
                                                          AT91C_TC_ETRGEDG_FALLING EQU( 0x2 << 8 );
                                                          -( TC ) Edge:falling edge
                                                          AT91C_TC_ETRGEDG_BOTH EQU( 0x3 << 8 );
                                                          -( TC ) Edge:each edge
                                                          AT91C_TC_EEVTEDG EQU( 0x3 << 8 );
                                                          -( TC ) External Event Edge Selection
                                                          AT91C_TC_EEVTEDG_NONE EQU( 0x0 << 8 );
                                                          -( TC ) Edge:None
                                                          AT91C_TC_EEVTEDG_RISING EQU( 0x1 << 8 );
                                                          -( TC ) Edge:rising edge
                                                          AT91C_TC_EEVTEDG_FALLING EQU( 0x2 << 8 );
                                                          -( TC ) Edge:falling edge
                                                          AT91C_TC_EEVTEDG_BOTH EQU( 0x3 << 8 );
                                                          -( TC ) Edge:each edge
                                                          AT91C_TC_EEVT EQU( 0x3 << 10 );
                                                          -( TC ) External Event Selection
                                                          AT91C_TC_EEVT_TIOB EQU( 0x0 << 10 );
                                                          -( TC ) Signal selected as external event:TIOB TIOB direction: निवेशः_2
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
                                                          AT91_C_TC_WAVESEL_ऊर्ध्वम् EQU( 0x0 << 13 );
                                                          -( TC ) ऊर्ध्वम्_3 बहुलकम्_2 without atomatic trigger on RC Compare
                                                          AT91C_TC_WAVESEL_UPDOWN EQU( 0x1 << 13 );
                                                          -( TC ) UPDOWN बहुलकम्_2 without automatic trigger on RC Compare
                                                          AT91_C_TC_WAVESEL_ऊर्ध्वम्_AUTO EQU( 0x2 << 13 );
                                                          -( TC ) ऊर्ध्वम्_3 बहुलकम्_2 with automatic trigger on RC Compare
                                                          AT91C_TC_WAVESEL_UPDOWN_AUTO EQU( 0x3 << 13 );
                                                          -( TC ) UPDOWN बहुलकम्_2 with automatic trigger on RC Compare
                                                          AT91C_TC_CPCTRG EQU( 0x1 << 14 );
                                                          -( TC ) RC Compare Trigger Enable
                                                          AT91C_TC_WAVE EQU( 0x1 << 15 );
                                                          -( TC )
                                                          AT91C_TC_ACPA EQU( 0x3 << 16 );
                                                          -( TC ) RA Compare Effect on TIOA
                                                          AT91C_TC_ACPA_NONE EQU( 0x0 << 16 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_ACPA_समुच्चयः EQU( 0x1 << 16 );
                                                          -( TC ) Effect:समुच्चयः
                                                          AT91C_TC_ACPA_CLEAR EQU( 0x2 << 16 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_ACPA_TOGGLE EQU( 0x3 << 16 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_LDRA EQU( 0x3 << 16 );
                                                          -( TC ) RA Loading Selection
                                                          AT91C_TC_LDRA_NONE EQU( 0x0 << 16 );
                                                          -( TC ) Edge:None
                                                          AT91C_TC_LDRA_RISING EQU( 0x1 << 16 );
                                                          -( TC ) Edge:rising edge सम्बन्धि TIOA
                                                          AT91C_TC_LDRA_FALLING EQU( 0x2 << 16 );
                                                          -( TC ) Edge:falling edge सम्बन्धि TIOA
                                                          AT91C_TC_LDRA_BOTH EQU( 0x3 << 16 );
                                                          -( TC ) Edge:each edge सम्बन्धि TIOA
                                                          AT91C_TC_ACPC EQU( 0x3 << 18 );
                                                          -( TC ) RC Compare Effect on TIOA
                                                          AT91C_TC_ACPC_NONE EQU( 0x0 << 18 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_ACPC_समुच्चयः EQU( 0x1 << 18 );
                                                          -( TC ) Effect:समुच्चयः
                                                          AT91C_TC_ACPC_CLEAR EQU( 0x2 << 18 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_ACPC_TOGGLE EQU( 0x3 << 18 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_LDRB EQU( 0x3 << 18 );
                                                          -( TC ) RB Loading Selection
                                                          AT91C_TC_LDRB_NONE EQU( 0x0 << 18 );
                                                          -( TC ) Edge:None
                                                          AT91C_TC_LDRB_RISING EQU( 0x1 << 18 );
                                                          -( TC ) Edge:rising edge सम्बन्धि TIOA
                                                          AT91C_TC_LDRB_FALLING EQU( 0x2 << 18 );
                                                          -( TC ) Edge:falling edge सम्बन्धि TIOA
                                                          AT91C_TC_LDRB_BOTH EQU( 0x3 << 18 );
                                                          -( TC ) Edge:each edge सम्बन्धि TIOA
                                                          AT91C_TC_AEEVT EQU( 0x3 << 20 );
                                                          -( TC ) External Event Effect on TIOA
                                                          AT91C_TC_AEEVT_NONE EQU( 0x0 << 20 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_AEEVT_समुच्चयः EQU( 0x1 << 20 );
                                                          -( TC ) Effect:समुच्चयः
                                                          AT91C_TC_AEEVT_CLEAR EQU( 0x2 << 20 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_AEEVT_TOGGLE EQU( 0x3 << 20 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_ASWTRG EQU( 0x3 << 22 );
                                                          -( TC ) Software Trigger Effect on TIOA
                                                          AT91C_TC_ASWTRG_NONE EQU( 0x0 << 22 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_ASWTRG_समुच्चयः EQU( 0x1 << 22 );
                                                          -( TC ) Effect:समुच्चयः
                                                          AT91C_TC_ASWTRG_CLEAR EQU( 0x2 << 22 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_ASWTRG_TOGGLE EQU( 0x3 << 22 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_BCPB EQU( 0x3 << 24 );
                                                          -( TC ) RB Compare Effect on TIOB
                                                          AT91C_TC_BCPB_NONE EQU( 0x0 << 24 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_BCPB_समुच्चयः EQU( 0x1 << 24 );
                                                          -( TC ) Effect:समुच्चयः
                                                          AT91C_TC_BCPB_CLEAR EQU( 0x2 << 24 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_BCPB_TOGGLE EQU( 0x3 << 24 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_BCPC EQU( 0x3 << 26 );
                                                          -( TC ) RC Compare Effect on TIOB
                                                          AT91C_TC_BCPC_NONE EQU( 0x0 << 26 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_BCPC_समुच्चयः EQU( 0x1 << 26 );
                                                          -( TC ) Effect:समुच्चयः
                                                          AT91C_TC_BCPC_CLEAR EQU( 0x2 << 26 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_BCPC_TOGGLE EQU( 0x3 << 26 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_BEEVT EQU( 0x3 << 28 );
                                                          -( TC ) External Event Effect on TIOB
                                                          AT91C_TC_BEEVT_NONE EQU( 0x0 << 28 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_BEEVT_समुच्चयः EQU( 0x1 << 28 );
                                                          -( TC ) Effect:समुच्चयः
                                                          AT91C_TC_BEEVT_CLEAR EQU( 0x2 << 28 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_BEEVT_TOGGLE EQU( 0x3 << 28 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_BSWTRG EQU( 0x3 << 30 );
                                                          -( TC ) Software Trigger Effect on TIOB
                                                          AT91C_TC_BSWTRG_NONE EQU( 0x0 << 30 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_BSWTRG_समुच्चयः EQU( 0x1 << 30 );
                                                          -( TC ) Effect:समुच्चयः
                                                          AT91C_TC_BSWTRG_CLEAR EQU( 0x2 << 30 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_BSWTRG_TOGGLE EQU( 0x3 << 30 );
                                                          -( TC ) Effect:toggle
/* - -------- TC_SR : (TC Offset: 0x20) TC Channel Status Register -------- */
                                                          AT91C_TC_COVFS EQU( 0x1 << 0 );
                                                          -( TC ) गणक_2 अतिप्रवाहः_2
                                                          AT91C_TC_LOVRS EQU( 0x1 << 1 );
                                                          -( TC ) आरोपय Overrun
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
                                                          -( TCB ) TCLK0 connected गन्तव्यम् XC0
                                                          AT91C_TCB_TC0XC0S_NONE EQU( 0x1 );
                                                          -( TCB ) None सङ्केत connected गन्तव्यम् XC0
                                                          AT91C_TCB_TC0XC0S_TIOA1 EQU( 0x2 );
                                                          -( TCB ) TIOA1 connected गन्तव्यम् XC0
                                                          AT91C_TCB_TC0XC0S_TIOA2 EQU( 0x3 );
                                                          -( TCB ) TIOA2 connected गन्तव्यम् XC0
                                                          AT91C_TCB_TC1XC1S EQU( 0x3 << 2 );
                                                          -( TCB ) External Clock Signal 1 Selection
                                                          AT91C_TCB_TC1XC1S_TCLK1 EQU( 0x0 << 2 );
                                                          -( TCB ) TCLK1 connected गन्तव्यम् XC1
                                                          AT91C_TCB_TC1XC1S_NONE EQU( 0x1 << 2 );
                                                          -( TCB ) None सङ्केत connected गन्तव्यम् XC1
                                                          AT91C_TCB_TC1XC1S_TIOA0 EQU( 0x2 << 2 );
                                                          -( TCB ) TIOA0 connected गन्तव्यम् XC1
                                                          AT91C_TCB_TC1XC1S_TIOA2 EQU( 0x3 << 2 );
                                                          -( TCB ) TIOA2 connected गन्तव्यम् XC1
                                                          AT91C_TCB_TC2XC2S EQU( 0x3 << 4 );
                                                          -( TCB ) External Clock Signal 2 Selection
                                                          AT91C_TCB_TC2XC2S_TCLK2 EQU( 0x0 << 4 );
                                                          -( TCB ) TCLK2 connected गन्तव्यम् XC2
                                                          AT91C_TCB_TC2XC2S_NONE EQU( 0x1 << 4 );
                                                          -( TCB ) None सङ्केत connected गन्तव्यम् XC2
                                                          AT91C_TCB_TC2XC2S_TIOA0 EQU( 0x2 << 4 );
                                                          -( TCB ) TIOA0 connected गन्तव्यम् XC2
                                                          AT91C_TCB_TC2XC2S_TIOA1 EQU( 0x3 << 4 );
                                                          -( TCB ) TIOA2 connected गन्तव्यम् XC2

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Control Area Network MailBox Interface */
/* - ***************************************************************************** */
/* - -------- CAN_MMR : (CAN_MB Offset: 0x0) CAN Message Mode Register -------- */
                                                          AT91C_CAN_MTIMEMARK EQU( 0xFFFF << 0 );
                                                          -( CAN_MB ) Mailbox Timemark
                                                          AT91_C_CAN_प्राक् EQU( 0xF << 16 );
                                                          -( CAN_MB ) Mailbox प्राथमिकता_2
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
                                                          AT91_C_CAN_MOT_उपभोक्ता EQU( 0x4 << 24 );
                                                          -( CAN_MB )
                                                          AT91_C_CAN_MOT_उत्पादकः EQU( 0x5 << 24 );
                                                          -( CAN_MB )
/* - -------- CAN_MAM : (CAN_MB Offset: 0x4) CAN Message Acceptance Mask Register -------- */
                                                          AT91C_CAN_MIDvB EQU( 0x3FFFF << 0 );
                                                          -( CAN_MB ) Complementary द्वयङ्काः_2

                                                          प्रति identifier अन्तर् extended बहुलकम्_2
                                                          AT91C_CAN_MIDvA EQU( 0x7FF << 18 );
                                                          -( CAN_MB ) Identifier

                                                          प्रति standard frame बहुलकम्_2
                                                          AT91C_CAN_MIDE EQU( 0x1 << 29 );
                                                          -( CAN_MB ) Identifier संस्करणम्_2
/* - -------- CAN_MID : (CAN_MB Offset: 0x8) CAN Message ID Register -------- */
/* - -------- CAN_MFID : (CAN_MB Offset: 0xc) CAN Message Family ID Register -------- */
/* - -------- CAN_MSR : (CAN_MB Offset: 0x10) CAN Message Status Register -------- */
                                                          AT91C_CAN_MTIMESTAMP EQU( 0xFFFF << 0 );
                                                          -( CAN_MB ) Timer मानम्_2
                                                          AT91C_CAN_MDLC EQU( 0xF << 16 );
                                                          -( CAN_MB ) Mailbox दत्त दीर्घता_2 संहिता_2
                                                          AT91C_CAN_MRTR EQU( 0x1 << 20 );
                                                          -( CAN_MB ) Mailbox Remote सम्प्रेषणम् Request
                                                          AT91C_CAN_MABT EQU( 0x1 << 22 );
                                                          -( CAN_MB ) Mailbox सन्देशः Abort
                                                          AT91C_CAN_MRDY EQU( 0x1 << 23 );
                                                          -( CAN_MB ) Mailbox Ready
                                                          AT91C_CAN_MMI EQU( 0x1 << 24 );
                                                          -( CAN_MB ) Mailbox सन्देशः Ignored
/* - -------- CAN_MDL : (CAN_MB Offset: 0x14) CAN Message Data Low Register -------- */
/* - -------- CAN_MDH : (CAN_MB Offset: 0x18) CAN Message Data High Register -------- */
/* - -------- CAN_MCR : (CAN_MB Offset: 0x1c) CAN Message Control Register -------- */
                                                          AT91C_CAN_MACR EQU( 0x1 << 22 );
                                                          -( CAN_MB ) Abort Request

                                                          प्रति Mailbox
                                                          AT91C_CAN_MTCR EQU( 0x1 << 23 );
                                                          -( CAN_MB ) Mailbox Transfer Command

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Control Area Network Interface */
/* - ***************************************************************************** */
/* - -------- CAN_MR : (CAN Offset: 0x0) CAN Mode Register -------- */
                                                          AT91C_CAN_CANEN EQU( 0x1 << 0 );
                                                          -( CAN ) CAN Controller Enable
                                                          AT91C_CAN_LPM EQU( 0x1 << 1 );
                                                          -( CAN ) Disable / Enable नीचः Power बहुलकम्
                                                          AT91C_CAN_ABM EQU( 0x1 << 2 );
                                                          -( CAN ) Disable / Enable Autobaud / Listen बहुलकम्
                                                          AT91C_CAN_OVL EQU( 0x1 << 3 );
                                                          -( CAN ) Disable / Enable Overload Frame
                                                          AT91C_CAN_TEOF EQU( 0x1 << 4 );
                                                          -( CAN ) Time Stamp messages at each अन्तः_2 सम्बन्धि Frame
                                                          AT91C_CAN_TTM EQU( 0x1 << 5 );
                                                          -( CAN ) Disable / Enable Time Trigger बहुलकम्
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
                                                          -( CAN ) Error सक्रिय बहुलकम् Flag
                                                          AT91C_CAN_WARN EQU( 0x1 << 17 );
                                                          -( CAN ) Warning सीमा Flag
                                                          AT91C_CAN_ERRP EQU( 0x1 << 18 );
                                                          -( CAN ) Error Passive बहुलकम् Flag
                                                          AT91C_CAN_BOFF EQU( 0x1 << 19 );
                                                          -( CAN ) Bus Off बहुलकम् Flag
                                                          AT91C_CAN_SLEEP EQU( 0x1 << 20 );
                                                          -( CAN ) Sleep Flag
                                                          AT91C_CAN_WAKEUP EQU( 0x1 << 21 );
                                                          -( CAN ) Wakeup Flag
                                                          AT91C_CAN_TOVF EQU( 0x1 << 22 );
                                                          -( CAN ) Timer अतिप्रवाहः_2 Flag
                                                          AT91C_CAN_TSTP EQU( 0x1 << 23 );
                                                          -( CAN ) Timestamp Flag
                                                          AT91C_CAN_CERR EQU( 0x1 << 24 );
                                                          -( CAN ) CRC Error
                                                          AT91C_CAN_SERR EQU( 0x1 << 25 );
                                                          -( CAN ) Stuffing Error
                                                          AT91C_CAN_AERR EQU( 0x1 << 26 );
                                                          -( CAN ) Acknowledgment Error
                                                          AT91C_CAN_FERR EQU( 0x1 << 27 );
                                                          -( CAN ) Form Error
                                                          AT91C_CAN_BERR EQU( 0x1 << 28 );
                                                          -( CAN ) Bit Error
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
                                                          -( CAN ) Re - synchronization jump विस्तारः segment
                                                          AT91C_CAN_BRP EQU( 0x7F << 16 );
                                                          -( CAN ) Baudrate Prescaler
                                                          AT91C_CAN_SMP EQU( 0x1 << 24 );
                                                          -( CAN ) Sampling बहुलकम्_2
/* - -------- CAN_TIM : (CAN Offset: 0x18) CAN Timer Register -------- */
                                                          AT91C_CAN_TIMER EQU( 0xFFFF << 0 );
                                                          -( CAN ) Timer क्षेत्रम्
/* - -------- CAN_TIMESTP : (CAN Offset: 0x1c) CAN Timestamp Register -------- */
/* - -------- CAN_ECR : (CAN Offset: 0x20) CAN Error Counter Register -------- */
                                                          AT91C_CAN_REC EQU( 0xFF << 0 );
                                                          -( CAN ) Receive Error गणक_2
                                                          AT91C_CAN_TEC EQU( 0xFF << 16 );
                                                          -( CAN ) Transmit Error गणक_2
/* - -------- CAN_TCR : (CAN Offset: 0x24) CAN Transfer Command Register -------- */
                                                          AT91C_CAN_TIMRST EQU( 0x1 << 31 );
                                                          -( CAN ) Timer Reset क्षेत्रम्_2
/* - -------- CAN_ACR : (CAN Offset: 0x28) CAN Abort Command Register -------- */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Ethernet MAC 10/100 */
/* - ***************************************************************************** */
/* - -------- EMAC_NCR : (EMAC Offset: 0x0)  -------- */
                                                          AT91C_EMAC_LB EQU( 0x1 << 0 );
                                                          -( EMAC ) Loopback.Optional.When समुच्चयः, loopback सङ्केत is at उच्चः_2 level.
                                                             AT91C_EMAC_LLB EQU( 0x1 << 1 );
                                                          -( EMAC ) Loopback local.
                                                             AT91C_EMAC_RE EQU( 0x1 << 2 );
                                                          -( EMAC ) Receive enable.
                                                             AT91C_EMAC_TE EQU( 0x1 << 3 );
                                                          -( EMAC ) Transmit enable.
                                                             AT91C_EMAC_MPE EQU( 0x1 << 4 );
                                                          -( EMAC ) Management पत्तनम् enable.
                                                             AT91C_EMAC_CLRSTAT EQU( 0x1 << 5 );
                                                          -( EMAC ) Clear statistics registers.
                                                             AT91C_EMAC_INCSTAT EQU( 0x1 << 6 );
                                                          -( EMAC ) Increment statistics registers.
                                                             AT91C_EMAC_WESTAT EQU( 0x1 << 7 );
                                                          -( EMAC ) Write enable

                                                          प्रति statistics registers.
                                                             AT91C_EMAC_BP EQU( 0x1 << 8 );
                                                          -( EMAC ) पृष्ठभागः pressure.
                                                             AT91C_EMAC_TSTART EQU( 0x1 << 9 );
                                                          -( EMAC ) Start सम्प्रेषणम्.
                                                             AT91C_EMAC_THALT EQU( 0x1 << 10 );
                                                          -( EMAC ) सम्प्रेषणम् Halt.
                                                             AT91C_EMAC_TPFR EQU( 0x1 << 11 );
                                                          -( EMAC ) Transmit pause frame
                                                          AT91C_EMAC_TZQ EQU( 0x1 << 12 );
                                                          -( EMAC ) Transmit zero कालांशः pause frame
/* - -------- EMAC_NCFGR : (EMAC Offset: 0x4) Network Configuration Register -------- */
                                                          AT91C_EMAC_SPD EQU( 0x1 << 0 );
                                                          -( EMAC ) जवः.
                                                             AT91C_EMAC_FD EQU( 0x1 << 1 );
                                                          -( EMAC ) पूर्णम् duplex.
                                                             AT91C_EMAC_JFRAME EQU( 0x1 << 3 );
                                                          -( EMAC ) Jumbo चौकटाः.
                                                             AT91C_EMAC_CAF EQU( 0x1 << 4 );
                                                          -( EMAC ) Copy all चौकटाः_2.
                                                             AT91C_EMAC_NBC EQU( 0x1 << 5 );
                                                          -( EMAC ) No प्रसारणम्.
                                                             AT91C_EMAC_MTI EQU( 0x1 << 6 );
                                                          -( EMAC ) Multicast hash event enable
                                                          AT91C_EMAC_UNI EQU( 0x1 << 7 );
                                                          -( EMAC ) Unicast hash enable.
                                                             AT91C_EMAC_BIG EQU( 0x1 << 8 );
                                                          -( EMAC ) Receive 1522 अष्टकानि_2.
                                                             AT91C_EMAC_EAE EQU( 0x1 << 9 );
                                                          -( EMAC ) External स्थानाङ्कः_2 मेलनम् enable.
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
                                                          AT91_C_EMAC_RBOF_विस्थापनम्_0 EQU( 0x0 << 14 );
                                                          -( EMAC ) no offset from start सम्बन्धि receive बफर_2
                                                          AT91_C_EMAC_RBOF_विस्थापनम्_1 EQU( 0x1 << 14 );
                                                          -( EMAC ) one byte offset from start सम्बन्धि receive बफर_2
                                                          AT91_C_EMAC_RBOF_विस्थापनम्_2 EQU( 0x2 << 14 );
                                                          -( EMAC ) two अष्टकानि_2 offset from start सम्बन्धि receive बफर_2
                                                          AT91_C_EMAC_RBOF_विस्थापनम्_3 EQU( 0x3 << 14 );
                                                          -( EMAC ) three अष्टकानि_2 offset from start सम्बन्धि receive बफर_2
                                                          AT91C_EMAC_RLCE EQU( 0x1 << 16 );
                                                          -( EMAC ) Receive दीर्घता_2 क्षेत्रम् Checking Enable
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
                                                          AT91C_EMAC_COL EQU( 0x1 << 1 );
                                                          -( EMAC )
                                                          AT91C_EMAC_RLES EQU( 0x1 << 2 );
                                                          -( EMAC )
                                                          AT91C_EMAC_TGO EQU( 0x1 << 3 );
                                                          -( EMAC ) Transmit Go
                                                          AT91C_EMAC_BEX EQU( 0x1 << 4 );
                                                          -( EMAC ) Buffers exhausted mid frame
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
                                                          AT91_C_EMAC_दत्त EQU( 0xFFFF << 0 );
                                                          -( EMAC )
                                                          AT91_C_EMAC_संहिता EQU( 0x3 << 16 );
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
                                                          -( EMAC ) ARP request IP स्थानाङ्कः_2
                                                          AT91C_EMAC_MAG EQU( 0x1 << 16 );
                                                          -( EMAC ) Magic packet event enable
                                                          AT91C_EMAC_ARP EQU( 0x1 << 17 );
                                                          -( EMAC ) ARP request event enable
                                                          AT91C_EMAC_SA1 EQU( 0x1 << 18 );
                                                          -( EMAC ) Specific स्थानाङ्कः_2 पञ्जिका 1 event enable
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
                                                          AT91C_ADC_START EQU( 0x1 << 1 );
                                                          -( ADC ) Start Conversion
/* - -------- ADC_MR : (ADC Offset: 0x4) ADC Mode Register -------- */
                                                          AT91C_ADC_TRGEN EQU( 0x1 << 0 );
                                                          -( ADC ) Trigger Enable
                                                          AT91C_ADC_TRGEN_DIS EQU( 0x0 );
                                                          -( ADC ) Hardware triggers are disabled.Starting a conversion is only possible by software
                                                          AT91C_ADC_TRGEN_EN EQU( 0x1 );
                                                          -( ADC ) Hardware trigger selected by TRGSEL क्षेत्रम् is enabled.
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
                                                             AT91C_ADC_LOWRES_10_BIT EQU( 0x0 << 4 );
                                                          -( ADC ) 10 - bit resolution
                                                          AT91C_ADC_LOWRES_8_BIT EQU( 0x1 << 4 );
                                                          -( ADC ) 8 - bit resolution
                                                          AT91C_ADC_SLEEP EQU( 0x1 << 5 );
                                                          -( ADC ) Sleep बहुलकम्
                                                          AT91_C_ADC_SLEEP_प्रसामान्यम्_बहुलकम् EQU( 0x0 << 5 );
                                                          -( ADC ) प्रसामान्यम् बहुलकम्
                                                          AT91_C_ADC_SLEEP_बहुलकम् EQU( 0x1 << 5 );
                                                          -( ADC ) Sleep बहुलकम्
                                                          AT91C_ADC_PRESCAL EQU( 0x3F << 8 );
                                                          -( ADC ) Prescaler दरः_2 selection
                                                          AT91C_ADC_STARTUP EQU( 0x1F << 16 );
                                                          -( ADC ) Startup Time
                                                          AT91C_ADC_SHTIM EQU( 0xF << 24 );
                                                          -( ADC ) Sample & Hold Time
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
                                                          -( ADC ) अन्तः_3 सम्बन्धि Conversion
                                                          AT91C_ADC_EOC1 EQU( 0x1 << 1 );
                                                          -( ADC ) अन्तः_3 सम्बन्धि Conversion
                                                          AT91C_ADC_EOC2 EQU( 0x1 << 2 );
                                                          -( ADC ) अन्तः_3 सम्बन्धि Conversion
                                                          AT91C_ADC_EOC3 EQU( 0x1 << 3 );
                                                          -( ADC ) अन्तः_3 सम्बन्धि Conversion
                                                          AT91C_ADC_EOC4 EQU( 0x1 << 4 );
                                                          -( ADC ) अन्तः_3 सम्बन्धि Conversion
                                                          AT91C_ADC_EOC5 EQU( 0x1 << 5 );
                                                          -( ADC ) अन्तः_3 सम्बन्धि Conversion
                                                          AT91C_ADC_EOC6 EQU( 0x1 << 6 );
                                                          -( ADC ) अन्तः_3 सम्बन्धि Conversion
                                                          AT91C_ADC_EOC7 EQU( 0x1 << 7 );
                                                          -( ADC ) अन्तः_3 सम्बन्धि Conversion
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
                                                          -( ADC ) दत्त Ready
                                                          AT91C_ADC_GOVRE EQU( 0x1 << 17 );
                                                          -( ADC ) General Overrun
                                                          AT91C_ADC_ENDRX EQU( 0x1 << 18 );
                                                          -( ADC ) अन्तः_3 सम्बन्धि Receiver Transfer
                                                          AT91C_ADC_RXBUFF EQU( 0x1 << 19 );
                                                          -( ADC ) RXBUFF व्यवधानम्_2
/* - -------- ADC_LCDR : (ADC Offset: 0x20) ADC Last Converted Data Register -------- */
                                                          AT91C_ADC_LDATA EQU( 0x3FF << 0 );
                                                          -( ADC ) चरमः दत्त Converted
/* - -------- ADC_IER : (ADC Offset: 0x24) ADC Interrupt Enable Register -------- */
/* - -------- ADC_IDR : (ADC Offset: 0x28) ADC Interrupt Disable Register -------- */
/* - -------- ADC_IMR : (ADC Offset: 0x2c) ADC Interrupt Mask Register -------- */
/* - -------- ADC_CDR0 : (ADC Offset: 0x30) ADC Channel Data Register 0 -------- */
                                                          AT91_C_ADC_दत्त EQU( 0x3FF << 0 );
                                                          -( ADC ) Converted दत्त
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
                                                          AT91C_AES_START EQU( 0x1 << 0 );
                                                          -( AES ) Starts Processing
                                                          AT91C_AES_SWRST EQU( 0x1 << 8 );
                                                          -( AES ) Software Reset
                                                          AT91C_AES_LOADSEED EQU( 0x1 << 16 );
                                                          -( AES ) Random सङ्ख्या_2 Generator बीजम् Loading
/* - -------- AES_MR : (AES Offset: 0x4) Mode Register -------- */
                                                          AT91C_AES_CIPHER EQU( 0x1 << 0 );
                                                          -( AES ) Processing बहुलकम्
                                                          AT91C_AES_PROCDLY EQU( 0xF << 4 );
                                                          -( AES ) Processing Delay
                                                          AT91C_AES_SMOD EQU( 0x3 << 8 );
                                                          -( AES ) Start बहुलकम्
                                                          AT91C_AES_SMOD_MANUAL EQU( 0x0 << 8 );
                                                          -( AES ) Manual बहुलकम्:The START bit अन्तर् पञ्जिका AES_CR must be समुच्चयः गन्तव्यम् begin encryption or decryption.
                                                             AT91C_AES_SMOD_AUTO EQU( 0x1 << 8 );
                                                          -( AES ) Auto बहुलकम्:no action अन्तर् AES_CR is necessary( cf datasheet ).
                                                             AT91C_AES_SMOD_PDC EQU( 0x2 << 8 );
                                                          -( AES ) PDC बहुलकम्( cf datasheet ).
                                                             AT91C_AES_OPMOD EQU( 0x7 << 12 );
                                                          -( AES ) Operation बहुलकम्
                                                          AT91C_AES_OPMOD_ECB EQU( 0x0 << 12 );
                                                          -( AES ) ECB Electronic संहिता_Book बहुलकम्_2.
                                                             AT91C_AES_OPMOD_CBC EQU( 0x1 << 12 );
                                                          -( AES ) CBC Cipher खण्डम् Chaining बहुलकम्_2.
                                                             AT91C_AES_OPMOD_OFB EQU( 0x2 << 12 );
                                                          -( AES ) OFB Output Feedback बहुलकम्_2.
                                                             AT91C_AES_OPMOD_CFB EQU( 0x3 << 12 );
                                                          -( AES ) CFB Cipher Feedback बहुलकम्_2.
                                                             AT91C_AES_OPMOD_CTR EQU( 0x4 << 12 );
                                                          -( AES ) CTR गणक_2 बहुलकम्_2.
                                                             AT91C_AES_LOD EQU( 0x1 << 15 );
                                                          -( AES ) चरमः Output दत्त बहुलकम्
                                                          AT91C_AES_CFBS EQU( 0x7 << 16 );
                                                          -( AES ) Cipher Feedback दत्त आकार_2
                                                          AT91C_AES_CFBS_128_BIT EQU( 0x0 << 16 );
                                                          -( AES ) 128 - bit.
                                                             AT91C_AES_CFBS_64_BIT EQU( 0x1 << 16 );
                                                          -( AES ) 64 - bit.
                                                             AT91C_AES_CFBS_32_BIT EQU( 0x2 << 16 );
                                                          -( AES ) 32 - bit.
                                                             AT91C_AES_CFBS_16_BIT EQU( 0x3 << 16 );
                                                          -( AES ) 16 - bit.
                                                             AT91C_AES_CFBS_8_BIT EQU( 0x4 << 16 );
                                                          -( AES ) 8 - bit.
                                                             AT91C_AES_CKEY EQU( 0xF << 20 );
                                                          -( AES ) Countermeasure कुञ्चिका_2
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
                                                          -( AES ) PDC Read बफर अन्तः_3
                                                          AT91C_AES_ENDTX EQU( 0x1 << 2 );
                                                          -( AES ) PDC Write बफर अन्तः_3
                                                          AT91C_AES_RXBUFF EQU( 0x1 << 3 );
                                                          -( AES ) PDC Read बफर पूर्णम्
                                                          AT91C_AES_TXBUFE EQU( 0x1 << 4 );
                                                          -( AES ) PDC Write बफर रिक्तानि
                                                          AT91C_AES_URAD EQU( 0x1 << 8 );
                                                          -( AES ) Unspecified पञ्जिकाकोशः Access Detection
/* - -------- AES_IDR : (AES Offset: 0x14) Interrupt Disable Register -------- */
/* - -------- AES_IMR : (AES Offset: 0x18) Interrupt Mask Register -------- */
/* - -------- AES_ISR : (AES Offset: 0x1c) Interrupt Status Register -------- */
                                                          AT91C_AES_URAT EQU( 0x7 << 12 );
                                                          -( AES ) Unspecified पञ्जिकाकोशः Access Type स्थितिः
                                                          AT91_C_AES_URAT_अन्तर्_DAT_WRITE_DATPROC EQU( 0x0 << 12 );
                                                          -( AES ) निवेशः दत्त_2 पञ्जिका written during the दत्त_2 processing अन्तर् PDC बहुलकम्_2.
                                                             AT91_C_AES_URAT_बहिर्गमनम्_DAT_READ_DATPROC EQU( 0x1 << 12 );
                                                          -( AES ) Output दत्त_2 पञ्जिका पठ during the दत्त_2 processing.
                                                             AT91C_AES_URAT_MODEREG_WRITE_DATPROC EQU( 0x2 << 12 );
                                                          -( AES ) बहुलकम् पञ्जिका written during the दत्त_2 processing.
                                                             AT91_C_AES_URAT_बहिर्गमनम्_DAT_READ_SUBKEY EQU( 0x3 << 12 );
                                                          -( AES ) Output दत्त_2 पञ्जिका पठ during the sub - कुञ्चिकाः generation.
                                                             AT91C_AES_URAT_MODEREG_WRITE_SUBKEY EQU( 0x4 << 12 );
                                                          -( AES ) बहुलकम् पञ्जिका written during the sub - कुञ्चिकाः generation.
                                                             AT91C_AES_URAT_WO_REG_READ EQU( 0x5 << 12 );
                                                          -( AES ) Write - only पञ्जिका पठ access.

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Triple Data Encryption Standard */
/* - ***************************************************************************** */
/* - -------- TDES_CR : (TDES Offset: 0x0) Control Register -------- */
                                                             AT91C_TDES_START EQU( 0x1 << 0 );
                                                          -( TDES ) Starts Processing
                                                          AT91C_TDES_SWRST EQU( 0x1 << 8 );
                                                          -( TDES ) Software Reset
/* - -------- TDES_MR : (TDES Offset: 0x4) Mode Register -------- */
                                                          AT91C_TDES_CIPHER EQU( 0x1 << 0 );
                                                          -( TDES ) Processing बहुलकम्
                                                          AT91C_TDES_TDESMOD EQU( 0x1 << 1 );
                                                          -( TDES ) Single or Triple DES बहुलकम्
                                                          AT91C_TDES_KEYMOD EQU( 0x1 << 4 );
                                                          -( TDES ) कुञ्चिका_2 बहुलकम्
                                                          AT91C_TDES_SMOD EQU( 0x3 << 8 );
                                                          -( TDES ) Start बहुलकम्
                                                          AT91C_TDES_SMOD_MANUAL EQU( 0x0 << 8 );
                                                          -( TDES ) Manual बहुलकम्:The START bit अन्तर् पञ्जिका TDES_CR must be समुच्चयः गन्तव्यम् begin encryption or decryption.
                                                             AT91C_TDES_SMOD_AUTO EQU( 0x1 << 8 );
                                                          -( TDES ) Auto बहुलकम्:no action अन्तर् TDES_CR is necessary( cf datasheet ).
                                                             AT91C_TDES_SMOD_PDC EQU( 0x2 << 8 );
                                                          -( TDES ) PDC बहुलकम्( cf datasheet ).
                                                             AT91C_TDES_OPMOD EQU( 0x3 << 12 );
                                                          -( TDES ) Operation बहुलकम्
                                                          AT91C_TDES_OPMOD_ECB EQU( 0x0 << 12 );
                                                          -( TDES ) ECB Electronic संहिता_Book बहुलकम्_2.
                                                             AT91C_TDES_OPMOD_CBC EQU( 0x1 << 12 );
                                                          -( TDES ) CBC Cipher खण्डम् Chaining बहुलकम्_2.
                                                             AT91C_TDES_OPMOD_OFB EQU( 0x2 << 12 );
                                                          -( TDES ) OFB Output Feedback बहुलकम्_2.
                                                             AT91C_TDES_OPMOD_CFB EQU( 0x3 << 12 );
                                                          -( TDES ) CFB Cipher Feedback बहुलकम्_2.
                                                             AT91C_TDES_LOD EQU( 0x1 << 15 );
                                                          -( TDES ) चरमः Output दत्त बहुलकम्
                                                          AT91C_TDES_CFBS EQU( 0x3 << 16 );
                                                          -( TDES ) Cipher Feedback दत्त आकार_2
                                                          AT91C_TDES_CFBS_64_BIT EQU( 0x0 << 16 );
                                                          -( TDES ) 64 - bit.
                                                             AT91C_TDES_CFBS_32_BIT EQU( 0x1 << 16 );
                                                          -( TDES ) 32 - bit.
                                                             AT91C_TDES_CFBS_16_BIT EQU( 0x2 << 16 );
                                                          -( TDES ) 16 - bit.
                                                             AT91C_TDES_CFBS_8_BIT EQU( 0x3 << 16 );
                                                          -( TDES ) 8 - bit.
/* - -------- TDES_IER : (TDES Offset: 0x10) Interrupt Enable Register -------- */
                                                             AT91C_TDES_DATRDY EQU( 0x1 << 0 );
                                                          -( TDES ) DATRDY
                                                          AT91C_TDES_ENDRX EQU( 0x1 << 1 );
                                                          -( TDES ) PDC Read बफर अन्तः_3
                                                          AT91C_TDES_ENDTX EQU( 0x1 << 2 );
                                                          -( TDES ) PDC Write बफर अन्तः_3
                                                          AT91C_TDES_RXBUFF EQU( 0x1 << 3 );
                                                          -( TDES ) PDC Read बफर पूर्णम्
                                                          AT91C_TDES_TXBUFE EQU( 0x1 << 4 );
                                                          -( TDES ) PDC Write बफर रिक्तानि
                                                          AT91C_TDES_URAD EQU( 0x1 << 8 );
                                                          -( TDES ) Unspecified पञ्जिकाकोशः Access Detection
/* - -------- TDES_IDR : (TDES Offset: 0x14) Interrupt Disable Register -------- */
/* - -------- TDES_IMR : (TDES Offset: 0x18) Interrupt Mask Register -------- */
/* - -------- TDES_ISR : (TDES Offset: 0x1c) Interrupt Status Register -------- */
                                                          AT91C_TDES_URAT EQU( 0x3 << 12 );
                                                          -( TDES ) Unspecified पञ्जिकाकोशः Access Type स्थितिः
                                                          AT91_C_TDES_URAT_अन्तर्_DAT_WRITE_DATPROC EQU( 0x0 << 12 );
                                                          -( TDES ) निवेशः दत्त_2 पञ्जिका written during the दत्त_2 processing अन्तर् PDC बहुलकम्_2.
                                                             AT91_C_TDES_URAT_बहिर्गमनम्_DAT_READ_DATPROC EQU( 0x1 << 12 );
                                                          -( TDES ) Output दत्त_2 पञ्जिका पठ during the दत्त_2 processing.
                                                             AT91C_TDES_URAT_MODEREG_WRITE_DATPROC EQU( 0x2 << 12 );
                                                          -( TDES ) बहुलकम् पञ्जिका written during the दत्त_2 processing.
                                                             AT91C_TDES_URAT_WO_REG_READ EQU( 0x3 << 12 );
                                                          -( TDES ) Write - only पञ्जिका पठ access.

/* - ***************************************************************************** */
/* -               REGISTER ADDRESS DEFINITION FOR AT91SAM7X256 */
/* - ***************************************************************************** */
/* - ========== Register definition for SYS peripheral ========== */
/* - ========== Register definition for AIC peripheral ========== */
                                                             AT91C_AIC_IVR EQU( 0xFFFFF100 );
                                                          -( AIC ) IRQ सदिशम्_2 पञ्जिकाकोशः
                                                          AT91C_AIC_SMR EQU( 0xFFFFF000 );
                                                          -( AIC ) Source बहुलकम् पञ्जिकाकोशः
                                                          AT91C_AIC_FVR EQU( 0xFFFFF104 );
                                                          -( AIC ) FIQ सदिशम्_2 पञ्जिकाकोशः
                                                          AT91C_AIC_DCR EQU( 0xFFFFF138 );
                                                          -( AIC ) Debug Control पञ्जिकाकोशः( Protect )
                                                          AT91C_AIC_EOICR EQU( 0xFFFFF130 );
                                                          -( AIC ) अन्तः_3 सम्बन्धि व्यवधानम्_2 Command पञ्जिकाकोशः
                                                          AT91C_AIC_SVR EQU( 0xFFFFF080 );
                                                          -( AIC ) Source सदिशम्_2 पञ्जिकाकोशः
                                                          AT91C_AIC_FFSR EQU( 0xFFFFF148 );
                                                          -( AIC ) Fast Forcing स्थितिः पञ्जिकाकोशः
                                                          AT91C_AIC_ICCR EQU( 0xFFFFF128 );
                                                          -( AIC ) व्यवधानम्_2 Clear Command पञ्जिकाकोशः
                                                          AT91C_AIC_ISR EQU( 0xFFFFF108 );
                                                          -( AIC ) व्यवधानम्_2 स्थितिः पञ्जिकाकोशः
                                                          AT91C_AIC_IMR EQU( 0xFFFFF110 );
                                                          -( AIC ) व्यवधानम्_2 आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_AIC_IPR EQU( 0xFFFFF10C );
                                                          -( AIC ) व्यवधानम्_2 Pending पञ्जिकाकोशः
                                                          AT91C_AIC_FFER EQU( 0xFFFFF140 );
                                                          -( AIC ) Fast Forcing Enable पञ्जिकाकोशः
                                                          AT91C_AIC_IECR EQU( 0xFFFFF120 );
                                                          -( AIC ) व्यवधानम्_2 Enable Command पञ्जिकाकोशः
                                                          AT91C_AIC_ISCR EQU( 0xFFFFF12C );
                                                          -( AIC ) व्यवधानम्_2 समुच्चयः_2 Command पञ्जिकाकोशः
                                                          AT91C_AIC_FFDR EQU( 0xFFFFF144 );
                                                          -( AIC ) Fast Forcing Disable पञ्जिकाकोशः
                                                          AT91C_AIC_CISR EQU( 0xFFFFF114 );
                                                          -( AIC ) Core व्यवधानम्_2 स्थितिः पञ्जिकाकोशः
                                                          AT91C_AIC_IDCR EQU( 0xFFFFF124 );
                                                          -( AIC ) व्यवधानम्_2 Disable Command पञ्जिकाकोशः
                                                          AT91C_AIC_SPU EQU( 0xFFFFF134 );
                                                          -( AIC ) Spurious सदिशम्_2 पञ्जिकाकोशः
/* - ========== Register definition for PDC_DBGU peripheral ========== */
                                                          AT91C_DBGU_TCR EQU( 0xFFFFF30C );
                                                          -( PDC_DBGU ) Transmit गणक_2 पञ्जिकाकोशः
                                                          AT91C_DBGU_RNPR EQU( 0xFFFFF310 );
                                                          -( PDC_DBGU ) Receive अग्र Pointer पञ्जिकाकोशः
                                                          AT91C_DBGU_TNPR EQU( 0xFFFFF318 );
                                                          -( PDC_DBGU ) Transmit अग्र Pointer पञ्जिकाकोशः
                                                          AT91C_DBGU_TPR EQU( 0xFFFFF308 );
                                                          -( PDC_DBGU ) Transmit Pointer पञ्जिकाकोशः
                                                          AT91C_DBGU_RPR EQU( 0xFFFFF300 );
                                                          -( PDC_DBGU ) Receive Pointer पञ्जिकाकोशः
                                                          AT91C_DBGU_RCR EQU( 0xFFFFF304 );
                                                          -( PDC_DBGU ) Receive गणक_2 पञ्जिकाकोशः
                                                          AT91C_DBGU_RNCR EQU( 0xFFFFF314 );
                                                          -( PDC_DBGU ) Receive अग्र गणक_2 पञ्जिकाकोशः
                                                          AT91C_DBGU_PTCR EQU( 0xFFFFF320 );
                                                          -( PDC_DBGU ) PDC Transfer Control पञ्जिकाकोशः
                                                          AT91C_DBGU_PTSR EQU( 0xFFFFF324 );
                                                          -( PDC_DBGU ) PDC Transfer स्थितिः पञ्जिकाकोशः
                                                          AT91C_DBGU_TNCR EQU( 0xFFFFF31C );
                                                          -( PDC_DBGU ) Transmit अग्र गणक_2 पञ्जिकाकोशः
/* - ========== Register definition for DBGU peripheral ========== */
                                                          AT91C_DBGU_EXID EQU( 0xFFFFF244 );
                                                          -( DBGU ) Chip ID Extension पञ्जिकाकोशः
                                                          AT91C_DBGU_BRGR EQU( 0xFFFFF220 );
                                                          -( DBGU ) Baud दरः Generator पञ्जिकाकोशः
                                                          AT91C_DBGU_IDR EQU( 0xFFFFF20C );
                                                          -( DBGU ) व्यवधानम्_2 Disable पञ्जिकाकोशः
                                                          AT91C_DBGU_CSR EQU( 0xFFFFF214 );
                                                          -( DBGU ) Channel स्थितिः पञ्जिकाकोशः
                                                          AT91C_DBGU_CIDR EQU( 0xFFFFF240 );
                                                          -( DBGU ) Chip ID पञ्जिकाकोशः
                                                          AT91C_DBGU_MR EQU( 0xFFFFF204 );
                                                          -( DBGU ) बहुलकम् पञ्जिकाकोशः
                                                          AT91C_DBGU_IMR EQU( 0xFFFFF210 );
                                                          -( DBGU ) व्यवधानम्_2 आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_DBGU_CR EQU( 0xFFFFF200 );
                                                          -( DBGU ) Control पञ्जिकाकोशः
                                                          AT91C_DBGU_FNTR EQU( 0xFFFFF248 );
                                                          -( DBGU ) Force NTRST पञ्जिकाकोशः
                                                          AT91C_DBGU_THR EQU( 0xFFFFF21C );
                                                          -( DBGU ) Transmitter Holding पञ्जिकाकोशः
                                                          AT91C_DBGU_RHR EQU( 0xFFFFF218 );
                                                          -( DBGU ) Receiver Holding पञ्जिकाकोशः
                                                          AT91C_DBGU_IER EQU( 0xFFFFF208 );
                                                          -( DBGU ) व्यवधानम्_2 Enable पञ्जिकाकोशः
/* - ========== Register definition for PIOA peripheral ========== */
                                                          AT91C_PIOA_ODR EQU( 0xFFFFF414 );
                                                          -( PIOA ) Output Disable Registerr
                                                          AT91C_PIOA_SODR EQU( 0xFFFFF430 );
                                                          -( PIOA ) समुच्चयः_2 Output दत्त पञ्जिकाकोशः
                                                          AT91C_PIOA_ISR EQU( 0xFFFFF44C );
                                                          -( PIOA ) व्यवधानम्_2 स्थितिः पञ्जिकाकोशः
                                                          AT91C_PIOA_ABSR EQU( 0xFFFFF478 );
                                                          -( PIOA ) AB Select स्थितिः पञ्जिकाकोशः
                                                          AT91C_PIOA_IER EQU( 0xFFFFF440 );
                                                          -( PIOA ) व्यवधानम्_2 Enable पञ्जिकाकोशः
                                                          AT91C_PIOA_PPUDR EQU( 0xFFFFF460 );
                                                          -( PIOA ) Pull - ऊर्ध्वम् Disable पञ्जिकाकोशः
                                                          AT91C_PIOA_IMR EQU( 0xFFFFF448 );
                                                          -( PIOA ) व्यवधानम्_2 आवरणम्_2 पञ्जिकाकोशः
                                                          AT91_C_PIOA_प्रत्येकम् EQU( 0xFFFFF400 );
                                                          -( PIOA ) PIO Enable पञ्जिकाकोशः
                                                          AT91C_PIOA_IFDR EQU( 0xFFFFF424 );
                                                          -( PIOA ) निवेशः Filter Disable पञ्जिकाकोशः
                                                          AT91C_PIOA_OWDR EQU( 0xFFFFF4A4 );
                                                          -( PIOA ) Output Write Disable पञ्जिकाकोशः
                                                          AT91C_PIOA_MDSR EQU( 0xFFFFF458 );
                                                          -( PIOA ) Multi - driver स्थितिः पञ्जिकाकोशः
                                                          AT91C_PIOA_IDR EQU( 0xFFFFF444 );
                                                          -( PIOA ) व्यवधानम्_2 Disable पञ्जिकाकोशः
                                                          AT91C_PIOA_ODSR EQU( 0xFFFFF438 );
                                                          -( PIOA ) Output दत्त स्थितिः पञ्जिकाकोशः
                                                          AT91C_PIOA_PPUSR EQU( 0xFFFFF468 );
                                                          -( PIOA ) Pull - ऊर्ध्वम् स्थितिः पञ्जिकाकोशः
                                                          AT91C_PIOA_OWSR EQU( 0xFFFFF4A8 );
                                                          -( PIOA ) Output Write स्थितिः पञ्जिकाकोशः
                                                          AT91C_PIOA_BSR EQU( 0xFFFFF474 );
                                                          -( PIOA ) Select B पञ्जिकाकोशः
                                                          AT91C_PIOA_OWER EQU( 0xFFFFF4A0 );
                                                          -( PIOA ) Output Write Enable पञ्जिकाकोशः
                                                          AT91C_PIOA_IFER EQU( 0xFFFFF420 );
                                                          -( PIOA ) निवेशः Filter Enable पञ्जिकाकोशः
                                                          AT91C_PIOA_PDSR EQU( 0xFFFFF43C );
                                                          -( PIOA ) Pin दत्त स्थितिः पञ्जिकाकोशः
                                                          AT91C_PIOA_PPUER EQU( 0xFFFFF464 );
                                                          -( PIOA ) Pull - ऊर्ध्वम् Enable पञ्जिकाकोशः
                                                          AT91C_PIOA_OSR EQU( 0xFFFFF418 );
                                                          -( PIOA ) Output स्थितिः पञ्जिकाकोशः
                                                          AT91C_PIOA_ASR EQU( 0xFFFFF470 );
                                                          -( PIOA ) Select A पञ्जिकाकोशः
                                                          AT91C_PIOA_MDDR EQU( 0xFFFFF454 );
                                                          -( PIOA ) Multi - driver Disable पञ्जिकाकोशः
                                                          AT91C_PIOA_CODR EQU( 0xFFFFF434 );
                                                          -( PIOA ) Clear Output दत्त पञ्जिकाकोशः
                                                          AT91C_PIOA_MDER EQU( 0xFFFFF450 );
                                                          -( PIOA ) Multi - driver Enable पञ्जिकाकोशः
                                                          AT91C_PIOA_PDR EQU( 0xFFFFF404 );
                                                          -( PIOA ) PIO Disable पञ्जिकाकोशः
                                                          AT91C_PIOA_IFSR EQU( 0xFFFFF428 );
                                                          -( PIOA ) निवेशः Filter स्थितिः पञ्जिकाकोशः
                                                          AT91C_PIOA_OER EQU( 0xFFFFF410 );
                                                          -( PIOA ) Output Enable पञ्जिकाकोशः
                                                          AT91C_PIOA_PSR EQU( 0xFFFFF408 );
                                                          -( PIOA ) PIO स्थितिः पञ्जिकाकोशः
/* - ========== Register definition for PIOB peripheral ========== */
                                                          AT91C_PIOB_OWDR EQU( 0xFFFFF6A4 );
                                                          -( PIOB ) Output Write Disable पञ्जिकाकोशः
                                                          AT91C_PIOB_MDER EQU( 0xFFFFF650 );
                                                          -( PIOB ) Multi - driver Enable पञ्जिकाकोशः
                                                          AT91C_PIOB_PPUSR EQU( 0xFFFFF668 );
                                                          -( PIOB ) Pull - ऊर्ध्वम् स्थितिः पञ्जिकाकोशः
                                                          AT91C_PIOB_IMR EQU( 0xFFFFF648 );
                                                          -( PIOB ) व्यवधानम्_2 आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_PIOB_ASR EQU( 0xFFFFF670 );
                                                          -( PIOB ) Select A पञ्जिकाकोशः
                                                          AT91C_PIOB_PPUDR EQU( 0xFFFFF660 );
                                                          -( PIOB ) Pull - ऊर्ध्वम् Disable पञ्जिकाकोशः
                                                          AT91C_PIOB_PSR EQU( 0xFFFFF608 );
                                                          -( PIOB ) PIO स्थितिः पञ्जिकाकोशः
                                                          AT91C_PIOB_IER EQU( 0xFFFFF640 );
                                                          -( PIOB ) व्यवधानम्_2 Enable पञ्जिकाकोशः
                                                          AT91C_PIOB_CODR EQU( 0xFFFFF634 );
                                                          -( PIOB ) Clear Output दत्त पञ्जिकाकोशः
                                                          AT91C_PIOB_OWER EQU( 0xFFFFF6A0 );
                                                          -( PIOB ) Output Write Enable पञ्जिकाकोशः
                                                          AT91C_PIOB_ABSR EQU( 0xFFFFF678 );
                                                          -( PIOB ) AB Select स्थितिः पञ्जिकाकोशः
                                                          AT91C_PIOB_IFDR EQU( 0xFFFFF624 );
                                                          -( PIOB ) निवेशः Filter Disable पञ्जिकाकोशः
                                                          AT91C_PIOB_PDSR EQU( 0xFFFFF63C );
                                                          -( PIOB ) Pin दत्त स्थितिः पञ्जिकाकोशः
                                                          AT91C_PIOB_IDR EQU( 0xFFFFF644 );
                                                          -( PIOB ) व्यवधानम्_2 Disable पञ्जिकाकोशः
                                                          AT91C_PIOB_OWSR EQU( 0xFFFFF6A8 );
                                                          -( PIOB ) Output Write स्थितिः पञ्जिकाकोशः
                                                          AT91C_PIOB_PDR EQU( 0xFFFFF604 );
                                                          -( PIOB ) PIO Disable पञ्जिकाकोशः
                                                          AT91C_PIOB_ODR EQU( 0xFFFFF614 );
                                                          -( PIOB ) Output Disable Registerr
                                                          AT91C_PIOB_IFSR EQU( 0xFFFFF628 );
                                                          -( PIOB ) निवेशः Filter स्थितिः पञ्जिकाकोशः
                                                          AT91C_PIOB_PPUER EQU( 0xFFFFF664 );
                                                          -( PIOB ) Pull - ऊर्ध्वम् Enable पञ्जिकाकोशः
                                                          AT91C_PIOB_SODR EQU( 0xFFFFF630 );
                                                          -( PIOB ) समुच्चयः_2 Output दत्त पञ्जिकाकोशः
                                                          AT91C_PIOB_ISR EQU( 0xFFFFF64C );
                                                          -( PIOB ) व्यवधानम्_2 स्थितिः पञ्जिकाकोशः
                                                          AT91C_PIOB_ODSR EQU( 0xFFFFF638 );
                                                          -( PIOB ) Output दत्त स्थितिः पञ्जिकाकोशः
                                                          AT91C_PIOB_OSR EQU( 0xFFFFF618 );
                                                          -( PIOB ) Output स्थितिः पञ्जिकाकोशः
                                                          AT91C_PIOB_MDSR EQU( 0xFFFFF658 );
                                                          -( PIOB ) Multi - driver स्थितिः पञ्जिकाकोशः
                                                          AT91C_PIOB_IFER EQU( 0xFFFFF620 );
                                                          -( PIOB ) निवेशः Filter Enable पञ्जिकाकोशः
                                                          AT91C_PIOB_BSR EQU( 0xFFFFF674 );
                                                          -( PIOB ) Select B पञ्जिकाकोशः
                                                          AT91C_PIOB_MDDR EQU( 0xFFFFF654 );
                                                          -( PIOB ) Multi - driver Disable पञ्जिकाकोशः
                                                          AT91C_PIOB_OER EQU( 0xFFFFF610 );
                                                          -( PIOB ) Output Enable पञ्जिकाकोशः
                                                          AT91_C_PIOB_प्रत्येकम् EQU( 0xFFFFF600 );
                                                          -( PIOB ) PIO Enable पञ्जिकाकोशः
/* - ========== Register definition for CKGR peripheral ========== */
                                                          AT91C_CKGR_MOR EQU( 0xFFFFFC20 );
                                                          -( CKGR ) Main Oscillator पञ्जिकाकोशः
                                                          AT91C_CKGR_PLLR EQU( 0xFFFFFC2C );
                                                          -( CKGR ) PLL पञ्जिकाकोशः
                                                          AT91C_CKGR_MCFR EQU( 0xFFFFFC24 );
                                                          -( CKGR ) Main Clock Frequency पञ्जिकाकोशः
/* - ========== Register definition for PMC peripheral ========== */
                                                          AT91C_PMC_IDR EQU( 0xFFFFFC64 );
                                                          -( PMC ) व्यवधानम्_2 Disable पञ्जिकाकोशः
                                                          AT91C_PMC_MOR EQU( 0xFFFFFC20 );
                                                          -( PMC ) Main Oscillator पञ्जिकाकोशः
                                                          AT91C_PMC_PLLR EQU( 0xFFFFFC2C );
                                                          -( PMC ) PLL पञ्जिकाकोशः
                                                          AT91C_PMC_PCER EQU( 0xFFFFFC10 );
                                                          -( PMC ) Peripheral Clock Enable पञ्जिकाकोशः
                                                          AT91C_PMC_PCKR EQU( 0xFFFFFC40 );
                                                          -( PMC ) Programmable Clock पञ्जिकाकोशः
                                                          AT91C_PMC_MCKR EQU( 0xFFFFFC30 );
                                                          -( PMC ) Master Clock पञ्जिकाकोशः
                                                          AT91C_PMC_SCDR EQU( 0xFFFFFC04 );
                                                          -( PMC ) System Clock Disable पञ्जिकाकोशः
                                                          AT91C_PMC_PCDR EQU( 0xFFFFFC14 );
                                                          -( PMC ) Peripheral Clock Disable पञ्जिकाकोशः
                                                          AT91C_PMC_SCSR EQU( 0xFFFFFC08 );
                                                          -( PMC ) System Clock स्थितिः पञ्जिकाकोशः
                                                          AT91C_PMC_PCSR EQU( 0xFFFFFC18 );
                                                          -( PMC ) Peripheral Clock स्थितिः पञ्जिकाकोशः
                                                          AT91C_PMC_MCFR EQU( 0xFFFFFC24 );
                                                          -( PMC ) Main Clock Frequency पञ्जिकाकोशः
                                                          AT91C_PMC_SCER EQU( 0xFFFFFC00 );
                                                          -( PMC ) System Clock Enable पञ्जिकाकोशः
                                                          AT91C_PMC_IMR EQU( 0xFFFFFC6C );
                                                          -( PMC ) व्यवधानम्_2 आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_PMC_IER EQU( 0xFFFFFC60 );
                                                          -( PMC ) व्यवधानम्_2 Enable पञ्जिकाकोशः
                                                          AT91C_PMC_SR EQU( 0xFFFFFC68 );
                                                          -( PMC ) स्थितिः पञ्जिकाकोशः
/* - ========== Register definition for RSTC peripheral ========== */
                                                          AT91C_RSTC_RCR EQU( 0xFFFFFD00 );
                                                          -( RSTC ) Reset Control पञ्जिकाकोशः
                                                          AT91C_RSTC_RMR EQU( 0xFFFFFD08 );
                                                          -( RSTC ) Reset बहुलकम् पञ्जिकाकोशः
                                                          AT91C_RSTC_RSR EQU( 0xFFFFFD04 );
                                                          -( RSTC ) Reset स्थितिः पञ्जिकाकोशः
/* - ========== Register definition for RTTC peripheral ========== */
                                                          AT91C_RTTC_RTSR EQU( 0xFFFFFD2C );
                                                          -( RTTC ) Real - time स्थितिः पञ्जिकाकोशः
                                                          AT91C_RTTC_RTMR EQU( 0xFFFFFD20 );
                                                          -( RTTC ) Real - time बहुलकम् पञ्जिकाकोशः
                                                          AT91C_RTTC_RTVR EQU( 0xFFFFFD28 );
                                                          -( RTTC ) Real - time मानम्_2 पञ्जिकाकोशः
                                                          AT91C_RTTC_RTAR EQU( 0xFFFFFD24 );
                                                          -( RTTC ) Real - time Alarm पञ्जिकाकोशः
/* - ========== Register definition for PITC peripheral ========== */
                                                          AT91C_PITC_PIVR EQU( 0xFFFFFD38 );
                                                          -( PITC ) Period Interval मानम्_2 पञ्जिकाकोशः
                                                          AT91C_PITC_PISR EQU( 0xFFFFFD34 );
                                                          -( PITC ) Period Interval स्थितिः पञ्जिकाकोशः
                                                          AT91C_PITC_PIIR EQU( 0xFFFFFD3C );
                                                          -( PITC ) Period Interval Image पञ्जिकाकोशः
                                                          AT91C_PITC_PIMR EQU( 0xFFFFFD30 );
                                                          -( PITC ) Period Interval बहुलकम् पञ्जिकाकोशः
/* - ========== Register definition for WDTC peripheral ========== */
                                                          AT91C_WDTC_WDCR EQU( 0xFFFFFD40 );
                                                          -( WDTC ) Watchdog Control पञ्जिकाकोशः
                                                          AT91C_WDTC_WDSR EQU( 0xFFFFFD48 );
                                                          -( WDTC ) Watchdog स्थितिः पञ्जिकाकोशः
                                                          AT91C_WDTC_WDMR EQU( 0xFFFFFD44 );
                                                          -( WDTC ) Watchdog बहुलकम् पञ्जिकाकोशः
/* - ========== Register definition for VREG peripheral ========== */
                                                          AT91C_VREG_MR EQU( 0xFFFFFD60 );
                                                          -( VREG ) Voltage Regulator बहुलकम् पञ्जिकाकोशः
/* - ========== Register definition for MC peripheral ========== */
                                                          AT91C_MC_ASR EQU( 0xFFFFFF04 );
                                                          -( MC ) MC Abort स्थितिः पञ्जिकाकोशः
                                                          AT91C_MC_RCR EQU( 0xFFFFFF00 );
                                                          -( MC ) MC Remap Control पञ्जिकाकोशः
                                                          AT91C_MC_FCR EQU( 0xFFFFFF64 );
                                                          -( MC ) MC Flash Command पञ्जिकाकोशः
                                                          AT91C_MC_AASR EQU( 0xFFFFFF08 );
                                                          -( MC ) MC Abort स्थानाङ्कः स्थितिः पञ्जिकाकोशः
                                                          AT91C_MC_FSR EQU( 0xFFFFFF68 );
                                                          -( MC ) MC Flash स्थितिः पञ्जिकाकोशः
                                                          AT91C_MC_FMR EQU( 0xFFFFFF60 );
                                                          -( MC ) MC Flash बहुलकम् पञ्जिकाकोशः
/* - ========== Register definition for PDC_SPI1 peripheral ========== */
                                                          AT91C_SPI1_PTCR EQU( 0xFFFE4120 );
                                                          -( PDC_SPI1 ) PDC Transfer Control पञ्जिकाकोशः
                                                          AT91C_SPI1_RPR EQU( 0xFFFE4100 );
                                                          -( PDC_SPI1 ) Receive Pointer पञ्जिकाकोशः
                                                          AT91C_SPI1_TNCR EQU( 0xFFFE411C );
                                                          -( PDC_SPI1 ) Transmit अग्र गणक_2 पञ्जिकाकोशः
                                                          AT91C_SPI1_TPR EQU( 0xFFFE4108 );
                                                          -( PDC_SPI1 ) Transmit Pointer पञ्जिकाकोशः
                                                          AT91C_SPI1_TNPR EQU( 0xFFFE4118 );
                                                          -( PDC_SPI1 ) Transmit अग्र Pointer पञ्जिकाकोशः
                                                          AT91C_SPI1_TCR EQU( 0xFFFE410C );
                                                          -( PDC_SPI1 ) Transmit गणक_2 पञ्जिकाकोशः
                                                          AT91C_SPI1_RCR EQU( 0xFFFE4104 );
                                                          -( PDC_SPI1 ) Receive गणक_2 पञ्जिकाकोशः
                                                          AT91C_SPI1_RNPR EQU( 0xFFFE4110 );
                                                          -( PDC_SPI1 ) Receive अग्र Pointer पञ्जिकाकोशः
                                                          AT91C_SPI1_RNCR EQU( 0xFFFE4114 );
                                                          -( PDC_SPI1 ) Receive अग्र गणक_2 पञ्जिकाकोशः
                                                          AT91C_SPI1_PTSR EQU( 0xFFFE4124 );
                                                          -( PDC_SPI1 ) PDC Transfer स्थितिः पञ्जिकाकोशः
/* - ========== Register definition for SPI1 peripheral ========== */
                                                          AT91C_SPI1_IMR EQU( 0xFFFE401C );
                                                          -( SPI1 ) व्यवधानम्_2 आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_SPI1_IER EQU( 0xFFFE4014 );
                                                          -( SPI1 ) व्यवधानम्_2 Enable पञ्जिकाकोशः
                                                          AT91C_SPI1_MR EQU( 0xFFFE4004 );
                                                          -( SPI1 ) बहुलकम् पञ्जिकाकोशः
                                                          AT91C_SPI1_RDR EQU( 0xFFFE4008 );
                                                          -( SPI1 ) Receive दत्त पञ्जिकाकोशः
                                                          AT91C_SPI1_IDR EQU( 0xFFFE4018 );
                                                          -( SPI1 ) व्यवधानम्_2 Disable पञ्जिकाकोशः
                                                          AT91C_SPI1_SR EQU( 0xFFFE4010 );
                                                          -( SPI1 ) स्थितिः पञ्जिकाकोशः
                                                          AT91C_SPI1_TDR EQU( 0xFFFE400C );
                                                          -( SPI1 ) Transmit दत्त पञ्जिकाकोशः
                                                          AT91C_SPI1_CR EQU( 0xFFFE4000 );
                                                          -( SPI1 ) Control पञ्जिकाकोशः
                                                          AT91C_SPI1_CSR EQU( 0xFFFE4030 );
                                                          -( SPI1 ) Chip Select पञ्जिकाकोशः
/* - ========== Register definition for PDC_SPI0 peripheral ========== */
                                                          AT91C_SPI0_PTCR EQU( 0xFFFE0120 );
                                                          -( PDC_SPI0 ) PDC Transfer Control पञ्जिकाकोशः
                                                          AT91C_SPI0_TPR EQU( 0xFFFE0108 );
                                                          -( PDC_SPI0 ) Transmit Pointer पञ्जिकाकोशः
                                                          AT91C_SPI0_TCR EQU( 0xFFFE010C );
                                                          -( PDC_SPI0 ) Transmit गणक_2 पञ्जिकाकोशः
                                                          AT91C_SPI0_RCR EQU( 0xFFFE0104 );
                                                          -( PDC_SPI0 ) Receive गणक_2 पञ्जिकाकोशः
                                                          AT91C_SPI0_PTSR EQU( 0xFFFE0124 );
                                                          -( PDC_SPI0 ) PDC Transfer स्थितिः पञ्जिकाकोशः
                                                          AT91C_SPI0_RNPR EQU( 0xFFFE0110 );
                                                          -( PDC_SPI0 ) Receive अग्र Pointer पञ्जिकाकोशः
                                                          AT91C_SPI0_RPR EQU( 0xFFFE0100 );
                                                          -( PDC_SPI0 ) Receive Pointer पञ्जिकाकोशः
                                                          AT91C_SPI0_TNCR EQU( 0xFFFE011C );
                                                          -( PDC_SPI0 ) Transmit अग्र गणक_2 पञ्जिकाकोशः
                                                          AT91C_SPI0_RNCR EQU( 0xFFFE0114 );
                                                          -( PDC_SPI0 ) Receive अग्र गणक_2 पञ्जिकाकोशः
                                                          AT91C_SPI0_TNPR EQU( 0xFFFE0118 );
                                                          -( PDC_SPI0 ) Transmit अग्र Pointer पञ्जिकाकोशः
/* - ========== Register definition for SPI0 peripheral ========== */
                                                          AT91C_SPI0_IER EQU( 0xFFFE0014 );
                                                          -( SPI0 ) व्यवधानम्_2 Enable पञ्जिकाकोशः
                                                          AT91C_SPI0_SR EQU( 0xFFFE0010 );
                                                          -( SPI0 ) स्थितिः पञ्जिकाकोशः
                                                          AT91C_SPI0_IDR EQU( 0xFFFE0018 );
                                                          -( SPI0 ) व्यवधानम्_2 Disable पञ्जिकाकोशः
                                                          AT91C_SPI0_CR EQU( 0xFFFE0000 );
                                                          -( SPI0 ) Control पञ्जिकाकोशः
                                                          AT91C_SPI0_MR EQU( 0xFFFE0004 );
                                                          -( SPI0 ) बहुलकम् पञ्जिकाकोशः
                                                          AT91C_SPI0_IMR EQU( 0xFFFE001C );
                                                          -( SPI0 ) व्यवधानम्_2 आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_SPI0_TDR EQU( 0xFFFE000C );
                                                          -( SPI0 ) Transmit दत्त पञ्जिकाकोशः
                                                          AT91C_SPI0_RDR EQU( 0xFFFE0008 );
                                                          -( SPI0 ) Receive दत्त पञ्जिकाकोशः
                                                          AT91C_SPI0_CSR EQU( 0xFFFE0030 );
                                                          -( SPI0 ) Chip Select पञ्जिकाकोशः
/* - ========== Register definition for PDC_US1 peripheral ========== */
                                                          AT91C_US1_RNCR EQU( 0xFFFC4114 );
                                                          -( PDC_US1 ) Receive अग्र गणक_2 पञ्जिकाकोशः
                                                          AT91C_US1_PTCR EQU( 0xFFFC4120 );
                                                          -( PDC_US1 ) PDC Transfer Control पञ्जिकाकोशः
                                                          AT91C_US1_TCR EQU( 0xFFFC410C );
                                                          -( PDC_US1 ) Transmit गणक_2 पञ्जिकाकोशः
                                                          AT91C_US1_PTSR EQU( 0xFFFC4124 );
                                                          -( PDC_US1 ) PDC Transfer स्थितिः पञ्जिकाकोशः
                                                          AT91C_US1_TNPR EQU( 0xFFFC4118 );
                                                          -( PDC_US1 ) Transmit अग्र Pointer पञ्जिकाकोशः
                                                          AT91C_US1_RCR EQU( 0xFFFC4104 );
                                                          -( PDC_US1 ) Receive गणक_2 पञ्जिकाकोशः
                                                          AT91C_US1_RNPR EQU( 0xFFFC4110 );
                                                          -( PDC_US1 ) Receive अग्र Pointer पञ्जिकाकोशः
                                                          AT91C_US1_RPR EQU( 0xFFFC4100 );
                                                          -( PDC_US1 ) Receive Pointer पञ्जिकाकोशः
                                                          AT91C_US1_TNCR EQU( 0xFFFC411C );
                                                          -( PDC_US1 ) Transmit अग्र गणक_2 पञ्जिकाकोशः
                                                          AT91C_US1_TPR EQU( 0xFFFC4108 );
                                                          -( PDC_US1 ) Transmit Pointer पञ्जिकाकोशः
/* - ========== Register definition for US1 peripheral ========== */
                                                          AT91C_US1_IF EQU( 0xFFFC404C );
                                                          -( US1 ) IRDA_FILTER पञ्जिकाकोशः
                                                          AT91C_US1_NER EQU( 0xFFFC4044 );
                                                          -( US1 ) Nb Errors पञ्जिकाकोशः
                                                          AT91C_US1_RTOR EQU( 0xFFFC4024 );
                                                          -( US1 ) Receiver Time - बहिर्गमनम् पञ्जिकाकोशः
                                                          AT91C_US1_CSR EQU( 0xFFFC4014 );
                                                          -( US1 ) Channel स्थितिः पञ्जिकाकोशः
                                                          AT91C_US1_IDR EQU( 0xFFFC400C );
                                                          -( US1 ) व्यवधानम्_2 Disable पञ्जिकाकोशः
                                                          AT91C_US1_IER EQU( 0xFFFC4008 );
                                                          -( US1 ) व्यवधानम्_2 Enable पञ्जिकाकोशः
                                                          AT91C_US1_THR EQU( 0xFFFC401C );
                                                          -( US1 ) Transmitter Holding पञ्जिकाकोशः
                                                          AT91C_US1_TTGR EQU( 0xFFFC4028 );
                                                          -( US1 ) Transmitter Time - guard पञ्जिकाकोशः
                                                          AT91C_US1_RHR EQU( 0xFFFC4018 );
                                                          -( US1 ) Receiver Holding पञ्जिकाकोशः
                                                          AT91C_US1_BRGR EQU( 0xFFFC4020 );
                                                          -( US1 ) Baud दरः Generator पञ्जिकाकोशः
                                                          AT91C_US1_IMR EQU( 0xFFFC4010 );
                                                          -( US1 ) व्यवधानम्_2 आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_US1_FIDI EQU( 0xFFFC4040 );
                                                          -( US1 ) FI_DI_अनुपातः पञ्जिकाकोशः
                                                          AT91C_US1_CR EQU( 0xFFFC4000 );
                                                          -( US1 ) Control पञ्जिकाकोशः
                                                          AT91C_US1_MR EQU( 0xFFFC4004 );
                                                          -( US1 ) बहुलकम् पञ्जिकाकोशः
/* - ========== Register definition for PDC_US0 peripheral ========== */
                                                          AT91C_US0_TNPR EQU( 0xFFFC0118 );
                                                          -( PDC_US0 ) Transmit अग्र Pointer पञ्जिकाकोशः
                                                          AT91C_US0_RNPR EQU( 0xFFFC0110 );
                                                          -( PDC_US0 ) Receive अग्र Pointer पञ्जिकाकोशः
                                                          AT91C_US0_TCR EQU( 0xFFFC010C );
                                                          -( PDC_US0 ) Transmit गणक_2 पञ्जिकाकोशः
                                                          AT91C_US0_PTCR EQU( 0xFFFC0120 );
                                                          -( PDC_US0 ) PDC Transfer Control पञ्जिकाकोशः
                                                          AT91C_US0_PTSR EQU( 0xFFFC0124 );
                                                          -( PDC_US0 ) PDC Transfer स्थितिः पञ्जिकाकोशः
                                                          AT91C_US0_TNCR EQU( 0xFFFC011C );
                                                          -( PDC_US0 ) Transmit अग्र गणक_2 पञ्जिकाकोशः
                                                          AT91C_US0_TPR EQU( 0xFFFC0108 );
                                                          -( PDC_US0 ) Transmit Pointer पञ्जिकाकोशः
                                                          AT91C_US0_RCR EQU( 0xFFFC0104 );
                                                          -( PDC_US0 ) Receive गणक_2 पञ्जिकाकोशः
                                                          AT91C_US0_RPR EQU( 0xFFFC0100 );
                                                          -( PDC_US0 ) Receive Pointer पञ्जिकाकोशः
                                                          AT91C_US0_RNCR EQU( 0xFFFC0114 );
                                                          -( PDC_US0 ) Receive अग्र गणक_2 पञ्जिकाकोशः
/* - ========== Register definition for US0 peripheral ========== */
                                                          AT91C_US0_BRGR EQU( 0xFFFC0020 );
                                                          -( US0 ) Baud दरः Generator पञ्जिकाकोशः
                                                          AT91C_US0_NER EQU( 0xFFFC0044 );
                                                          -( US0 ) Nb Errors पञ्जिकाकोशः
                                                          AT91C_US0_CR EQU( 0xFFFC0000 );
                                                          -( US0 ) Control पञ्जिकाकोशः
                                                          AT91C_US0_IMR EQU( 0xFFFC0010 );
                                                          -( US0 ) व्यवधानम्_2 आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_US0_FIDI EQU( 0xFFFC0040 );
                                                          -( US0 ) FI_DI_अनुपातः पञ्जिकाकोशः
                                                          AT91C_US0_TTGR EQU( 0xFFFC0028 );
                                                          -( US0 ) Transmitter Time - guard पञ्जिकाकोशः
                                                          AT91C_US0_MR EQU( 0xFFFC0004 );
                                                          -( US0 ) बहुलकम् पञ्जिकाकोशः
                                                          AT91C_US0_RTOR EQU( 0xFFFC0024 );
                                                          -( US0 ) Receiver Time - बहिर्गमनम् पञ्जिकाकोशः
                                                          AT91C_US0_CSR EQU( 0xFFFC0014 );
                                                          -( US0 ) Channel स्थितिः पञ्जिकाकोशः
                                                          AT91C_US0_RHR EQU( 0xFFFC0018 );
                                                          -( US0 ) Receiver Holding पञ्जिकाकोशः
                                                          AT91C_US0_IDR EQU( 0xFFFC000C );
                                                          -( US0 ) व्यवधानम्_2 Disable पञ्जिकाकोशः
                                                          AT91C_US0_THR EQU( 0xFFFC001C );
                                                          -( US0 ) Transmitter Holding पञ्जिकाकोशः
                                                          AT91C_US0_IF EQU( 0xFFFC004C );
                                                          -( US0 ) IRDA_FILTER पञ्जिकाकोशः
                                                          AT91C_US0_IER EQU( 0xFFFC0008 );
                                                          -( US0 ) व्यवधानम्_2 Enable पञ्जिकाकोशः
/* - ========== Register definition for PDC_SSC peripheral ========== */
                                                          AT91C_SSC_TNCR EQU( 0xFFFD411C );
                                                          -( PDC_SSC ) Transmit अग्र गणक_2 पञ्जिकाकोशः
                                                          AT91C_SSC_RPR EQU( 0xFFFD4100 );
                                                          -( PDC_SSC ) Receive Pointer पञ्जिकाकोशः
                                                          AT91C_SSC_RNCR EQU( 0xFFFD4114 );
                                                          -( PDC_SSC ) Receive अग्र गणक_2 पञ्जिकाकोशः
                                                          AT91C_SSC_TPR EQU( 0xFFFD4108 );
                                                          -( PDC_SSC ) Transmit Pointer पञ्जिकाकोशः
                                                          AT91C_SSC_PTCR EQU( 0xFFFD4120 );
                                                          -( PDC_SSC ) PDC Transfer Control पञ्जिकाकोशः
                                                          AT91C_SSC_TCR EQU( 0xFFFD410C );
                                                          -( PDC_SSC ) Transmit गणक_2 पञ्जिकाकोशः
                                                          AT91C_SSC_RCR EQU( 0xFFFD4104 );
                                                          -( PDC_SSC ) Receive गणक_2 पञ्जिकाकोशः
                                                          AT91C_SSC_RNPR EQU( 0xFFFD4110 );
                                                          -( PDC_SSC ) Receive अग्र Pointer पञ्जिकाकोशः
                                                          AT91C_SSC_TNPR EQU( 0xFFFD4118 );
                                                          -( PDC_SSC ) Transmit अग्र Pointer पञ्जिकाकोशः
                                                          AT91C_SSC_PTSR EQU( 0xFFFD4124 );
                                                          -( PDC_SSC ) PDC Transfer स्थितिः पञ्जिकाकोशः
/* - ========== Register definition for SSC peripheral ========== */
                                                          AT91C_SSC_RHR EQU( 0xFFFD4020 );
                                                          -( SSC ) Receive Holding पञ्जिकाकोशः
                                                          AT91C_SSC_RSHR EQU( 0xFFFD4030 );
                                                          -( SSC ) Receive Sync Holding पञ्जिकाकोशः
                                                          AT91C_SSC_TFMR EQU( 0xFFFD401C );
                                                          -( SSC ) Transmit Frame बहुलकम् पञ्जिकाकोशः
                                                          AT91C_SSC_IDR EQU( 0xFFFD4048 );
                                                          -( SSC ) व्यवधानम्_2 Disable पञ्जिकाकोशः
                                                          AT91C_SSC_THR EQU( 0xFFFD4024 );
                                                          -( SSC ) Transmit Holding पञ्जिकाकोशः
                                                          AT91C_SSC_RCMR EQU( 0xFFFD4010 );
                                                          -( SSC ) Receive Clock बहुलकम्_पञ्जिकाकोशः
                                                          AT91C_SSC_IER EQU( 0xFFFD4044 );
                                                          -( SSC ) व्यवधानम्_2 Enable पञ्जिकाकोशः
                                                          AT91C_SSC_TSHR EQU( 0xFFFD4034 );
                                                          -( SSC ) Transmit Sync Holding पञ्जिकाकोशः
                                                          AT91C_SSC_SR EQU( 0xFFFD4040 );
                                                          -( SSC ) स्थितिः पञ्जिकाकोशः
                                                          AT91C_SSC_CMR EQU( 0xFFFD4004 );
                                                          -( SSC ) Clock बहुलकम् पञ्जिकाकोशः
                                                          AT91C_SSC_TCMR EQU( 0xFFFD4018 );
                                                          -( SSC ) Transmit Clock बहुलकम् पञ्जिकाकोशः
                                                          AT91C_SSC_CR EQU( 0xFFFD4000 );
                                                          -( SSC ) Control पञ्जिकाकोशः
                                                          AT91C_SSC_IMR EQU( 0xFFFD404C );
                                                          -( SSC ) व्यवधानम्_2 आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_SSC_RFMR EQU( 0xFFFD4014 );
                                                          -( SSC ) Receive Frame बहुलकम् पञ्जिकाकोशः
/* - ========== Register definition for TWI peripheral ========== */
                                                          AT91C_TWI_IER EQU( 0xFFFB8024 );
                                                          -( TWI ) व्यवधानम्_2 Enable पञ्जिकाकोशः
                                                          AT91C_TWI_CR EQU( 0xFFFB8000 );
                                                          -( TWI ) Control पञ्जिकाकोशः
                                                          AT91C_TWI_SR EQU( 0xFFFB8020 );
                                                          -( TWI ) स्थितिः पञ्जिकाकोशः
                                                          AT91C_TWI_IMR EQU( 0xFFFB802C );
                                                          -( TWI ) व्यवधानम्_2 आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_TWI_THR EQU( 0xFFFB8034 );
                                                          -( TWI ) Transmit Holding पञ्जिकाकोशः
                                                          AT91C_TWI_IDR EQU( 0xFFFB8028 );
                                                          -( TWI ) व्यवधानम्_2 Disable पञ्जिकाकोशः
                                                          AT91C_TWI_IADR EQU( 0xFFFB800C );
                                                          -( TWI ) आन्तरिकम् स्थानाङ्कः पञ्जिकाकोशः
                                                          AT91C_TWI_MMR EQU( 0xFFFB8004 );
                                                          -( TWI ) Master बहुलकम् पञ्जिकाकोशः
                                                          AT91C_TWI_CWGR EQU( 0xFFFB8010 );
                                                          -( TWI ) Clock Waveform Generator पञ्जिकाकोशः
                                                          AT91C_TWI_RHR EQU( 0xFFFB8030 );
                                                          -( TWI ) Receive Holding पञ्जिकाकोशः
/* - ========== Register definition for PWMC_CH3 peripheral ========== */
                                                          AT91C_PWMC_CH3_CUPDR EQU( 0xFFFCC270 );
                                                          -( PWMC_CH3 ) Channel Update पञ्जिकाकोशः
                                                          AT91C_PWMC_CH3_Reserved EQU( 0xFFFCC274 );
                                                          -( PWMC_CH3 ) Reserved
                                                          AT91C_PWMC_CH3_CPRDR EQU( 0xFFFCC268 );
                                                          -( PWMC_CH3 ) Channel Period पञ्जिकाकोशः
                                                          AT91C_PWMC_CH3_CDTYR EQU( 0xFFFCC264 );
                                                          -( PWMC_CH3 ) Channel Duty आवृत्तिः_2 पञ्जिकाकोशः
                                                          AT91C_PWMC_CH3_CCNTR EQU( 0xFFFCC26C );
                                                          -( PWMC_CH3 ) Channel गणक_2 पञ्जिकाकोशः
                                                          AT91C_PWMC_CH3_CMR EQU( 0xFFFCC260 );
                                                          -( PWMC_CH3 ) Channel बहुलकम् पञ्जिकाकोशः
/* - ========== Register definition for PWMC_CH2 peripheral ========== */
                                                          AT91C_PWMC_CH2_Reserved EQU( 0xFFFCC254 );
                                                          -( PWMC_CH2 ) Reserved
                                                          AT91C_PWMC_CH2_CMR EQU( 0xFFFCC240 );
                                                          -( PWMC_CH2 ) Channel बहुलकम् पञ्जिकाकोशः
                                                          AT91C_PWMC_CH2_CCNTR EQU( 0xFFFCC24C );
                                                          -( PWMC_CH2 ) Channel गणक_2 पञ्जिकाकोशः
                                                          AT91C_PWMC_CH2_CPRDR EQU( 0xFFFCC248 );
                                                          -( PWMC_CH2 ) Channel Period पञ्जिकाकोशः
                                                          AT91C_PWMC_CH2_CUPDR EQU( 0xFFFCC250 );
                                                          -( PWMC_CH2 ) Channel Update पञ्जिकाकोशः
                                                          AT91C_PWMC_CH2_CDTYR EQU( 0xFFFCC244 );
                                                          -( PWMC_CH2 ) Channel Duty आवृत्तिः_2 पञ्जिकाकोशः
/* - ========== Register definition for PWMC_CH1 peripheral ========== */
                                                          AT91C_PWMC_CH1_Reserved EQU( 0xFFFCC234 );
                                                          -( PWMC_CH1 ) Reserved
                                                          AT91C_PWMC_CH1_CUPDR EQU( 0xFFFCC230 );
                                                          -( PWMC_CH1 ) Channel Update पञ्जिकाकोशः
                                                          AT91C_PWMC_CH1_CPRDR EQU( 0xFFFCC228 );
                                                          -( PWMC_CH1 ) Channel Period पञ्जिकाकोशः
                                                          AT91C_PWMC_CH1_CCNTR EQU( 0xFFFCC22C );
                                                          -( PWMC_CH1 ) Channel गणक_2 पञ्जिकाकोशः
                                                          AT91C_PWMC_CH1_CDTYR EQU( 0xFFFCC224 );
                                                          -( PWMC_CH1 ) Channel Duty आवृत्तिः_2 पञ्जिकाकोशः
                                                          AT91C_PWMC_CH1_CMR EQU( 0xFFFCC220 );
                                                          -( PWMC_CH1 ) Channel बहुलकम् पञ्जिकाकोशः
/* - ========== Register definition for PWMC_CH0 peripheral ========== */
                                                          AT91C_PWMC_CH0_Reserved EQU( 0xFFFCC214 );
                                                          -( PWMC_CH0 ) Reserved
                                                          AT91C_PWMC_CH0_CPRDR EQU( 0xFFFCC208 );
                                                          -( PWMC_CH0 ) Channel Period पञ्जिकाकोशः
                                                          AT91C_PWMC_CH0_CDTYR EQU( 0xFFFCC204 );
                                                          -( PWMC_CH0 ) Channel Duty आवृत्तिः_2 पञ्जिकाकोशः
                                                          AT91C_PWMC_CH0_CMR EQU( 0xFFFCC200 );
                                                          -( PWMC_CH0 ) Channel बहुलकम् पञ्जिकाकोशः
                                                          AT91C_PWMC_CH0_CUPDR EQU( 0xFFFCC210 );
                                                          -( PWMC_CH0 ) Channel Update पञ्जिकाकोशः
                                                          AT91C_PWMC_CH0_CCNTR EQU( 0xFFFCC20C );
                                                          -( PWMC_CH0 ) Channel गणक_2 पञ्जिकाकोशः
/* - ========== Register definition for PWMC peripheral ========== */
                                                          AT91C_PWMC_IDR EQU( 0xFFFCC014 );
                                                          -( PWMC ) PWMC व्यवधानम्_2 Disable पञ्जिकाकोशः
                                                          AT91C_PWMC_DIS EQU( 0xFFFCC008 );
                                                          -( PWMC ) PWMC Disable पञ्जिकाकोशः
                                                          AT91C_PWMC_IER EQU( 0xFFFCC010 );
                                                          -( PWMC ) PWMC व्यवधानम्_2 Enable पञ्जिकाकोशः
                                                          AT91C_PWMC_VR EQU( 0xFFFCC0FC );
                                                          -( PWMC ) PWMC संस्करणम्_2 पञ्जिकाकोशः
                                                          AT91C_PWMC_ISR EQU( 0xFFFCC01C );
                                                          -( PWMC ) PWMC व्यवधानम्_2 स्थितिः पञ्जिकाकोशः
                                                          AT91C_PWMC_SR EQU( 0xFFFCC00C );
                                                          -( PWMC ) PWMC स्थितिः पञ्जिकाकोशः
                                                          AT91C_PWMC_IMR EQU( 0xFFFCC018 );
                                                          -( PWMC ) PWMC व्यवधानम्_2 आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_PWMC_MR EQU( 0xFFFCC000 );
                                                          -( PWMC ) PWMC बहुलकम् पञ्जिकाकोशः
                                                          AT91C_PWMC_ENA EQU( 0xFFFCC004 );
                                                          -( PWMC ) PWMC Enable पञ्जिकाकोशः
/* - ========== Register definition for UDP peripheral ========== */
                                                          AT91C_UDP_IMR EQU( 0xFFFB0018 );
                                                          -( UDP ) व्यवधानम्_2 आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_UDP_FADDR EQU( 0xFFFB0008 );
                                                          -( UDP ) Function स्थानाङ्कः पञ्जिकाकोशः
                                                          AT91_C_UDP_अङ्कः EQU( 0xFFFB0000 );
                                                          -( UDP ) Frame सङ्ख्या_2 पञ्जिकाकोशः
                                                          AT91C_UDP_FDR EQU( 0xFFFB0050 );
                                                          -( UDP ) Endpoint FIFO दत्त पञ्जिकाकोशः
                                                          AT91C_UDP_ISR EQU( 0xFFFB001C );
                                                          -( UDP ) व्यवधानम्_2 स्थितिः पञ्जिकाकोशः
                                                          AT91C_UDP_CSR EQU( 0xFFFB0030 );
                                                          -( UDP ) Endpoint Control and स्थितिः पञ्जिकाकोशः
                                                          AT91C_UDP_IDR EQU( 0xFFFB0014 );
                                                          -( UDP ) व्यवधानम्_2 Disable पञ्जिकाकोशः
                                                          AT91C_UDP_ICR EQU( 0xFFFB0020 );
                                                          -( UDP ) व्यवधानम्_2 Clear पञ्जिकाकोशः
                                                          AT91C_UDP_RSTEP EQU( 0xFFFB0028 );
                                                          -( UDP ) Reset Endpoint पञ्जिकाकोशः
                                                          AT91C_UDP_TXVC EQU( 0xFFFB0074 );
                                                          -( UDP ) Transceiver Control पञ्जिकाकोशः
                                                          AT91C_UDP_GLBSTATE EQU( 0xFFFB0004 );
                                                          -( UDP ) Global State पञ्जिकाकोशः
                                                          AT91C_UDP_IER EQU( 0xFFFB0010 );
                                                          -( UDP ) व्यवधानम्_2 Enable पञ्जिकाकोशः
/* - ========== Register definition for TC0 peripheral ========== */
                                                          AT91C_TC0_SR EQU( 0xFFFA0020 );
                                                          -( TC0 ) स्थितिः पञ्जिकाकोशः
                                                          AT91C_TC0_RC EQU( 0xFFFA001C );
                                                          -( TC0 ) पञ्जिकाकोशः C
                                                          AT91C_TC0_RB EQU( 0xFFFA0018 );
                                                          -( TC0 ) पञ्जिकाकोशः B
                                                          AT91C_TC0_CCR EQU( 0xFFFA0000 );
                                                          -( TC0 ) Channel Control पञ्जिकाकोशः
                                                          AT91C_TC0_CMR EQU( 0xFFFA0004 );
                                                          -( TC0 ) Channel बहुलकम् पञ्जिकाकोशः( Capture बहुलकम् / Waveform बहुलकम् )
                                                          AT91C_TC0_IER EQU( 0xFFFA0024 );
                                                          -( TC0 ) व्यवधानम्_2 Enable पञ्जिकाकोशः
                                                          AT91C_TC0_RA EQU( 0xFFFA0014 );
                                                          -( TC0 ) पञ्जिकाकोशः A
                                                          AT91C_TC0_IDR EQU( 0xFFFA0028 );
                                                          -( TC0 ) व्यवधानम्_2 Disable पञ्जिकाकोशः
                                                          AT91C_TC0_CV EQU( 0xFFFA0010 );
                                                          -( TC0 ) गणक_2 मानम्_2
                                                          AT91C_TC0_IMR EQU( 0xFFFA002C );
                                                          -( TC0 ) व्यवधानम्_2 आवरणम्_2 पञ्जिकाकोशः
/* - ========== Register definition for TC1 peripheral ========== */
                                                          AT91C_TC1_RB EQU( 0xFFFA0058 );
                                                          -( TC1 ) पञ्जिकाकोशः B
                                                          AT91C_TC1_CCR EQU( 0xFFFA0040 );
                                                          -( TC1 ) Channel Control पञ्जिकाकोशः
                                                          AT91C_TC1_IER EQU( 0xFFFA0064 );
                                                          -( TC1 ) व्यवधानम्_2 Enable पञ्जिकाकोशः
                                                          AT91C_TC1_IDR EQU( 0xFFFA0068 );
                                                          -( TC1 ) व्यवधानम्_2 Disable पञ्जिकाकोशः
                                                          AT91C_TC1_SR EQU( 0xFFFA0060 );
                                                          -( TC1 ) स्थितिः पञ्जिकाकोशः
                                                          AT91C_TC1_CMR EQU( 0xFFFA0044 );
                                                          -( TC1 ) Channel बहुलकम् पञ्जिकाकोशः( Capture बहुलकम् / Waveform बहुलकम् )
                                                          AT91C_TC1_RA EQU( 0xFFFA0054 );
                                                          -( TC1 ) पञ्जिकाकोशः A
                                                          AT91C_TC1_RC EQU( 0xFFFA005C );
                                                          -( TC1 ) पञ्जिकाकोशः C
                                                          AT91C_TC1_IMR EQU( 0xFFFA006C );
                                                          -( TC1 ) व्यवधानम्_2 आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_TC1_CV EQU( 0xFFFA0050 );
                                                          -( TC1 ) गणक_2 मानम्_2
/* - ========== Register definition for TC2 peripheral ========== */
                                                          AT91C_TC2_CMR EQU( 0xFFFA0084 );
                                                          -( TC2 ) Channel बहुलकम् पञ्जिकाकोशः( Capture बहुलकम् / Waveform बहुलकम् )
                                                          AT91C_TC2_CCR EQU( 0xFFFA0080 );
                                                          -( TC2 ) Channel Control पञ्जिकाकोशः
                                                          AT91C_TC2_CV EQU( 0xFFFA0090 );
                                                          -( TC2 ) गणक_2 मानम्_2
                                                          AT91C_TC2_RA EQU( 0xFFFA0094 );
                                                          -( TC2 ) पञ्जिकाकोशः A
                                                          AT91C_TC2_RB EQU( 0xFFFA0098 );
                                                          -( TC2 ) पञ्जिकाकोशः B
                                                          AT91C_TC2_IDR EQU( 0xFFFA00A8 );
                                                          -( TC2 ) व्यवधानम्_2 Disable पञ्जिकाकोशः
                                                          AT91C_TC2_IMR EQU( 0xFFFA00AC );
                                                          -( TC2 ) व्यवधानम्_2 आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_TC2_RC EQU( 0xFFFA009C );
                                                          -( TC2 ) पञ्जिकाकोशः C
                                                          AT91C_TC2_IER EQU( 0xFFFA00A4 );
                                                          -( TC2 ) व्यवधानम्_2 Enable पञ्जिकाकोशः
                                                          AT91C_TC2_SR EQU( 0xFFFA00A0 );
                                                          -( TC2 ) स्थितिः पञ्जिकाकोशः
/* - ========== Register definition for TCB peripheral ========== */
                                                          AT91C_TCB_BMR EQU( 0xFFFA00C4 );
                                                          -( TCB ) TC खण्डम् बहुलकम् पञ्जिकाकोशः
                                                          AT91C_TCB_BCR EQU( 0xFFFA00C0 );
                                                          -( TCB ) TC खण्डम् Control पञ्जिकाकोशः
/* - ========== Register definition for CAN_MB0 peripheral ========== */
                                                          AT91C_CAN_MB0_MDL EQU( 0xFFFD0214 );
                                                          -( CAN_MB0 ) MailBox दत्त नीचः पञ्जिकाकोशः
                                                          AT91C_CAN_MB0_MAM EQU( 0xFFFD0204 );
                                                          -( CAN_MB0 ) MailBox Acceptance आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_CAN_MB0_MCR EQU( 0xFFFD021C );
                                                          -( CAN_MB0 ) MailBox Control पञ्जिकाकोशः
                                                          AT91C_CAN_MB0_MID EQU( 0xFFFD0208 );
                                                          -( CAN_MB0 ) MailBox ID पञ्जिकाकोशः
                                                          AT91C_CAN_MB0_MSR EQU( 0xFFFD0210 );
                                                          -( CAN_MB0 ) MailBox स्थितिः पञ्जिकाकोशः
                                                          AT91C_CAN_MB0_MFID EQU( 0xFFFD020C );
                                                          -( CAN_MB0 ) MailBox Family ID पञ्जिकाकोशः
                                                          AT91C_CAN_MB0_MDH EQU( 0xFFFD0218 );
                                                          -( CAN_MB0 ) MailBox दत्त उच्चः पञ्जिकाकोशः
                                                          AT91C_CAN_MB0_MMR EQU( 0xFFFD0200 );
                                                          -( CAN_MB0 ) MailBox बहुलकम् पञ्जिकाकोशः
/* - ========== Register definition for CAN_MB1 peripheral ========== */
                                                          AT91C_CAN_MB1_MDL EQU( 0xFFFD0234 );
                                                          -( CAN_MB1 ) MailBox दत्त नीचः पञ्जिकाकोशः
                                                          AT91C_CAN_MB1_MID EQU( 0xFFFD0228 );
                                                          -( CAN_MB1 ) MailBox ID पञ्जिकाकोशः
                                                          AT91C_CAN_MB1_MMR EQU( 0xFFFD0220 );
                                                          -( CAN_MB1 ) MailBox बहुलकम् पञ्जिकाकोशः
                                                          AT91C_CAN_MB1_MSR EQU( 0xFFFD0230 );
                                                          -( CAN_MB1 ) MailBox स्थितिः पञ्जिकाकोशः
                                                          AT91C_CAN_MB1_MAM EQU( 0xFFFD0224 );
                                                          -( CAN_MB1 ) MailBox Acceptance आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_CAN_MB1_MDH EQU( 0xFFFD0238 );
                                                          -( CAN_MB1 ) MailBox दत्त उच्चः पञ्जिकाकोशः
                                                          AT91C_CAN_MB1_MCR EQU( 0xFFFD023C );
                                                          -( CAN_MB1 ) MailBox Control पञ्जिकाकोशः
                                                          AT91C_CAN_MB1_MFID EQU( 0xFFFD022C );
                                                          -( CAN_MB1 ) MailBox Family ID पञ्जिकाकोशः
/* - ========== Register definition for CAN_MB2 peripheral ========== */
                                                          AT91C_CAN_MB2_MCR EQU( 0xFFFD025C );
                                                          -( CAN_MB2 ) MailBox Control पञ्जिकाकोशः
                                                          AT91C_CAN_MB2_MDH EQU( 0xFFFD0258 );
                                                          -( CAN_MB2 ) MailBox दत्त उच्चः पञ्जिकाकोशः
                                                          AT91C_CAN_MB2_MID EQU( 0xFFFD0248 );
                                                          -( CAN_MB2 ) MailBox ID पञ्जिकाकोशः
                                                          AT91C_CAN_MB2_MDL EQU( 0xFFFD0254 );
                                                          -( CAN_MB2 ) MailBox दत्त नीचः पञ्जिकाकोशः
                                                          AT91C_CAN_MB2_MMR EQU( 0xFFFD0240 );
                                                          -( CAN_MB2 ) MailBox बहुलकम् पञ्जिकाकोशः
                                                          AT91C_CAN_MB2_MAM EQU( 0xFFFD0244 );
                                                          -( CAN_MB2 ) MailBox Acceptance आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_CAN_MB2_MFID EQU( 0xFFFD024C );
                                                          -( CAN_MB2 ) MailBox Family ID पञ्जिकाकोशः
                                                          AT91C_CAN_MB2_MSR EQU( 0xFFFD0250 );
                                                          -( CAN_MB2 ) MailBox स्थितिः पञ्जिकाकोशः
/* - ========== Register definition for CAN_MB3 peripheral ========== */
                                                          AT91C_CAN_MB3_MFID EQU( 0xFFFD026C );
                                                          -( CAN_MB3 ) MailBox Family ID पञ्जिकाकोशः
                                                          AT91C_CAN_MB3_MAM EQU( 0xFFFD0264 );
                                                          -( CAN_MB3 ) MailBox Acceptance आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_CAN_MB3_MID EQU( 0xFFFD0268 );
                                                          -( CAN_MB3 ) MailBox ID पञ्जिकाकोशः
                                                          AT91C_CAN_MB3_MCR EQU( 0xFFFD027C );
                                                          -( CAN_MB3 ) MailBox Control पञ्जिकाकोशः
                                                          AT91C_CAN_MB3_MMR EQU( 0xFFFD0260 );
                                                          -( CAN_MB3 ) MailBox बहुलकम् पञ्जिकाकोशः
                                                          AT91C_CAN_MB3_MSR EQU( 0xFFFD0270 );
                                                          -( CAN_MB3 ) MailBox स्थितिः पञ्जिकाकोशः
                                                          AT91C_CAN_MB3_MDL EQU( 0xFFFD0274 );
                                                          -( CAN_MB3 ) MailBox दत्त नीचः पञ्जिकाकोशः
                                                          AT91C_CAN_MB3_MDH EQU( 0xFFFD0278 );
                                                          -( CAN_MB3 ) MailBox दत्त उच्चः पञ्जिकाकोशः
/* - ========== Register definition for CAN_MB4 peripheral ========== */
                                                          AT91C_CAN_MB4_MID EQU( 0xFFFD0288 );
                                                          -( CAN_MB4 ) MailBox ID पञ्जिकाकोशः
                                                          AT91C_CAN_MB4_MMR EQU( 0xFFFD0280 );
                                                          -( CAN_MB4 ) MailBox बहुलकम् पञ्जिकाकोशः
                                                          AT91C_CAN_MB4_MDH EQU( 0xFFFD0298 );
                                                          -( CAN_MB4 ) MailBox दत्त उच्चः पञ्जिकाकोशः
                                                          AT91C_CAN_MB4_MFID EQU( 0xFFFD028C );
                                                          -( CAN_MB4 ) MailBox Family ID पञ्जिकाकोशः
                                                          AT91C_CAN_MB4_MSR EQU( 0xFFFD0290 );
                                                          -( CAN_MB4 ) MailBox स्थितिः पञ्जिकाकोशः
                                                          AT91C_CAN_MB4_MCR EQU( 0xFFFD029C );
                                                          -( CAN_MB4 ) MailBox Control पञ्जिकाकोशः
                                                          AT91C_CAN_MB4_MDL EQU( 0xFFFD0294 );
                                                          -( CAN_MB4 ) MailBox दत्त नीचः पञ्जिकाकोशः
                                                          AT91C_CAN_MB4_MAM EQU( 0xFFFD0284 );
                                                          -( CAN_MB4 ) MailBox Acceptance आवरणम्_2 पञ्जिकाकोशः
/* - ========== Register definition for CAN_MB5 peripheral ========== */
                                                          AT91C_CAN_MB5_MSR EQU( 0xFFFD02B0 );
                                                          -( CAN_MB5 ) MailBox स्थितिः पञ्जिकाकोशः
                                                          AT91C_CAN_MB5_MCR EQU( 0xFFFD02BC );
                                                          -( CAN_MB5 ) MailBox Control पञ्जिकाकोशः
                                                          AT91C_CAN_MB5_MFID EQU( 0xFFFD02AC );
                                                          -( CAN_MB5 ) MailBox Family ID पञ्जिकाकोशः
                                                          AT91C_CAN_MB5_MDH EQU( 0xFFFD02B8 );
                                                          -( CAN_MB5 ) MailBox दत्त उच्चः पञ्जिकाकोशः
                                                          AT91C_CAN_MB5_MID EQU( 0xFFFD02A8 );
                                                          -( CAN_MB5 ) MailBox ID पञ्जिकाकोशः
                                                          AT91C_CAN_MB5_MMR EQU( 0xFFFD02A0 );
                                                          -( CAN_MB5 ) MailBox बहुलकम् पञ्जिकाकोशः
                                                          AT91C_CAN_MB5_MDL EQU( 0xFFFD02B4 );
                                                          -( CAN_MB5 ) MailBox दत्त नीचः पञ्जिकाकोशः
                                                          AT91C_CAN_MB5_MAM EQU( 0xFFFD02A4 );
                                                          -( CAN_MB5 ) MailBox Acceptance आवरणम्_2 पञ्जिकाकोशः
/* - ========== Register definition for CAN_MB6 peripheral ========== */
                                                          AT91C_CAN_MB6_MFID EQU( 0xFFFD02CC );
                                                          -( CAN_MB6 ) MailBox Family ID पञ्जिकाकोशः
                                                          AT91C_CAN_MB6_MID EQU( 0xFFFD02C8 );
                                                          -( CAN_MB6 ) MailBox ID पञ्जिकाकोशः
                                                          AT91C_CAN_MB6_MAM EQU( 0xFFFD02C4 );
                                                          -( CAN_MB6 ) MailBox Acceptance आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_CAN_MB6_MSR EQU( 0xFFFD02D0 );
                                                          -( CAN_MB6 ) MailBox स्थितिः पञ्जिकाकोशः
                                                          AT91C_CAN_MB6_MDL EQU( 0xFFFD02D4 );
                                                          -( CAN_MB6 ) MailBox दत्त नीचः पञ्जिकाकोशः
                                                          AT91C_CAN_MB6_MCR EQU( 0xFFFD02DC );
                                                          -( CAN_MB6 ) MailBox Control पञ्जिकाकोशः
                                                          AT91C_CAN_MB6_MDH EQU( 0xFFFD02D8 );
                                                          -( CAN_MB6 ) MailBox दत्त उच्चः पञ्जिकाकोशः
                                                          AT91C_CAN_MB6_MMR EQU( 0xFFFD02C0 );
                                                          -( CAN_MB6 ) MailBox बहुलकम् पञ्जिकाकोशः
/* - ========== Register definition for CAN_MB7 peripheral ========== */
                                                          AT91C_CAN_MB7_MCR EQU( 0xFFFD02FC );
                                                          -( CAN_MB7 ) MailBox Control पञ्जिकाकोशः
                                                          AT91C_CAN_MB7_MDH EQU( 0xFFFD02F8 );
                                                          -( CAN_MB7 ) MailBox दत्त उच्चः पञ्जिकाकोशः
                                                          AT91C_CAN_MB7_MFID EQU( 0xFFFD02EC );
                                                          -( CAN_MB7 ) MailBox Family ID पञ्जिकाकोशः
                                                          AT91C_CAN_MB7_MDL EQU( 0xFFFD02F4 );
                                                          -( CAN_MB7 ) MailBox दत्त नीचः पञ्जिकाकोशः
                                                          AT91C_CAN_MB7_MID EQU( 0xFFFD02E8 );
                                                          -( CAN_MB7 ) MailBox ID पञ्जिकाकोशः
                                                          AT91C_CAN_MB7_MMR EQU( 0xFFFD02E0 );
                                                          -( CAN_MB7 ) MailBox बहुलकम् पञ्जिकाकोशः
                                                          AT91C_CAN_MB7_MAM EQU( 0xFFFD02E4 );
                                                          -( CAN_MB7 ) MailBox Acceptance आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_CAN_MB7_MSR EQU( 0xFFFD02F0 );
                                                          -( CAN_MB7 ) MailBox स्थितिः पञ्जिकाकोशः
/* - ========== Register definition for CAN peripheral ========== */
                                                          AT91C_CAN_TCR EQU( 0xFFFD0024 );
                                                          -( CAN ) Transfer Command पञ्जिकाकोशः
                                                          AT91C_CAN_IMR EQU( 0xFFFD000C );
                                                          -( CAN ) व्यवधानम्_2 आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_CAN_IER EQU( 0xFFFD0004 );
                                                          -( CAN ) व्यवधानम्_2 Enable पञ्जिकाकोशः
                                                          AT91C_CAN_ECR EQU( 0xFFFD0020 );
                                                          -( CAN ) Error गणक_2 पञ्जिकाकोशः
                                                          AT91C_CAN_TIMESTP EQU( 0xFFFD001C );
                                                          -( CAN ) Time Stamp पञ्जिकाकोशः
                                                          AT91C_CAN_MR EQU( 0xFFFD0000 );
                                                          -( CAN ) बहुलकम् पञ्जिकाकोशः
                                                          AT91C_CAN_IDR EQU( 0xFFFD0008 );
                                                          -( CAN ) व्यवधानम्_2 Disable पञ्जिकाकोशः
                                                          AT91C_CAN_ACR EQU( 0xFFFD0028 );
                                                          -( CAN ) Abort Command पञ्जिकाकोशः
                                                          AT91C_CAN_TIM EQU( 0xFFFD0018 );
                                                          -( CAN ) Timer पञ्जिकाकोशः
                                                          AT91C_CAN_SR EQU( 0xFFFD0010 );
                                                          -( CAN ) स्थितिः पञ्जिकाकोशः
                                                          AT91C_CAN_BR EQU( 0xFFFD0014 );
                                                          -( CAN ) Baudrate पञ्जिकाकोशः
                                                          AT91C_CAN_VR EQU( 0xFFFD00FC );
                                                          -( CAN ) संस्करणम्_2 पञ्जिकाकोशः
/* - ========== Register definition for EMAC peripheral ========== */
                                                          AT91C_EMAC_ISR EQU( 0xFFFDC024 );
                                                          -( EMAC ) व्यवधानम्_2 स्थितिः पञ्जिकाकोशः
                                                          AT91C_EMAC_SA4H EQU( 0xFFFDC0B4 );
                                                          -( EMAC ) Specific स्थानाङ्कः 4 शिखरम्, चरमः 2 अष्टकानि_2
                                                          AT91C_EMAC_SA1L EQU( 0xFFFDC098 );
                                                          -( EMAC ) Specific स्थानाङ्कः 1 Bottom, First 4 अष्टकानि_2
                                                          AT91C_EMAC_ELE EQU( 0xFFFDC078 );
                                                          -( EMAC ) Excessive दीर्घता_2 Errors पञ्जिकाकोशः
                                                          AT91C_EMAC_LCOL EQU( 0xFFFDC05C );
                                                          -( EMAC ) Late Collision पञ्जिकाकोशः
                                                          AT91C_EMAC_RLE EQU( 0xFFFDC088 );
                                                          -( EMAC ) Receive दीर्घता_2 क्षेत्रम्_2 Mismatch पञ्जिकाकोशः
                                                          AT91C_EMAC_WOL EQU( 0xFFFDC0C4 );
                                                          -( EMAC ) Wake On LAN पञ्जिकाकोशः
                                                          AT91C_EMAC_DTF EQU( 0xFFFDC058 );
                                                          -( EMAC ) Deferred सम्प्रेषणम् Frame पञ्जिकाकोशः
                                                          AT91C_EMAC_TUND EQU( 0xFFFDC064 );
                                                          -( EMAC ) Transmit Underrun Error पञ्जिकाकोशः
                                                          AT91C_EMAC_NCR EQU( 0xFFFDC000 );
                                                          -( EMAC ) जालम् Control पञ्जिकाकोशः
                                                          AT91C_EMAC_SA4L EQU( 0xFFFDC0B0 );
                                                          -( EMAC ) Specific स्थानाङ्कः 4 Bottom, First 4 अष्टकानि_2
                                                          AT91C_EMAC_RSR EQU( 0xFFFDC020 );
                                                          -( EMAC ) Receive स्थितिः पञ्जिकाकोशः
                                                          AT91C_EMAC_SA3L EQU( 0xFFFDC0A8 );
                                                          -( EMAC ) Specific स्थानाङ्कः 3 Bottom, First 4 अष्टकानि_2
                                                          AT91C_EMAC_TSR EQU( 0xFFFDC014 );
                                                          -( EMAC ) Transmit स्थितिः पञ्जिकाकोशः
                                                          AT91C_EMAC_IDR EQU( 0xFFFDC02C );
                                                          -( EMAC ) व्यवधानम्_2 Disable पञ्जिकाकोशः
                                                          AT91C_EMAC_RSE EQU( 0xFFFDC074 );
                                                          -( EMAC ) Receive चिह्नम् Errors पञ्जिकाकोशः
                                                          AT91C_EMAC_ECOL EQU( 0xFFFDC060 );
                                                          -( EMAC ) Excessive Collision पञ्जिकाकोशः
                                                          AT91C_EMAC_TID EQU( 0xFFFDC0B8 );
                                                          -( EMAC ) Type ID Checking पञ्जिकाकोशः
                                                          AT91C_EMAC_HRB EQU( 0xFFFDC090 );
                                                          -( EMAC ) Hash स्थानाङ्कः Bottom[ 31 : 0 ]
                                                          AT91C_EMAC_TBQP EQU( 0xFFFDC01C );
                                                          -( EMAC ) Transmit बफर Queue Pointer
                                                          AT91C_EMAC_USRIO EQU( 0xFFFDC0C0 );
                                                          -( EMAC ) USER निवेशः / Output पञ्जिकाकोशः
                                                          AT91C_EMAC_PTR EQU( 0xFFFDC038 );
                                                          -( EMAC ) Pause Time पञ्जिकाकोशः
                                                          AT91C_EMAC_SA2H EQU( 0xFFFDC0A4 );
                                                          -( EMAC ) Specific स्थानाङ्कः 2 शिखरम्, चरमः 2 अष्टकानि_2
                                                          AT91C_EMAC_ROV EQU( 0xFFFDC070 );
                                                          -( EMAC ) Receive Overrun Errors पञ्जिकाकोशः
                                                          AT91C_EMAC_ALE EQU( 0xFFFDC054 );
                                                          -( EMAC ) Alignment Error पञ्जिकाकोशः
                                                          AT91C_EMAC_RJA EQU( 0xFFFDC07C );
                                                          -( EMAC ) Receive Jabbers पञ्जिकाकोशः
                                                          AT91C_EMAC_RBQP EQU( 0xFFFDC018 );
                                                          -( EMAC ) Receive बफर Queue Pointer
                                                          AT91C_EMAC_TPF EQU( 0xFFFDC08C );
                                                          -( EMAC ) Transmitted Pause चौकटाः पञ्जिकाकोशः
                                                          AT91C_EMAC_NCFGR EQU( 0xFFFDC004 );
                                                          -( EMAC ) जालम् Configuration पञ्जिकाकोशः
                                                          AT91C_EMAC_HRT EQU( 0xFFFDC094 );
                                                          -( EMAC ) Hash स्थानाङ्कः शिखरम्[ 63 : 32 ]
                                                          AT91C_EMAC_USF EQU( 0xFFFDC080 );
                                                          -( EMAC ) Undersize चौकटाः पञ्जिकाकोशः
                                                          AT91C_EMAC_FCSE EQU( 0xFFFDC050 );
                                                          -( EMAC ) Frame Check Sequence Error पञ्जिकाकोशः
                                                          AT91C_EMAC_TPQ EQU( 0xFFFDC0BC );
                                                          -( EMAC ) Transmit Pause कालांशः_2 पञ्जिकाकोशः
                                                          AT91C_EMAC_MAN EQU( 0xFFFDC034 );
                                                          -( EMAC ) PHY Maintenance पञ्जिकाकोशः
                                                          AT91C_EMAC_FTO EQU( 0xFFFDC040 );
                                                          -( EMAC ) चौकटाः Transmitted OK पञ्जिकाकोशः
                                                          AT91C_EMAC_REV EQU( 0xFFFDC0FC );
                                                          -( EMAC ) Revision पञ्जिकाकोशः
                                                          AT91C_EMAC_IMR EQU( 0xFFFDC030 );
                                                          -( EMAC ) व्यवधानम्_2 आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_EMAC_SCF EQU( 0xFFFDC044 );
                                                          -( EMAC ) Single Collision Frame पञ्जिकाकोशः
                                                          AT91C_EMAC_PFR EQU( 0xFFFDC03C );
                                                          -( EMAC ) Pause चौकटाः received पञ्जिकाकोशः
                                                          AT91C_EMAC_MCF EQU( 0xFFFDC048 );
                                                          -( EMAC ) गुणजः Collision Frame पञ्जिकाकोशः
                                                          AT91C_EMAC_NSR EQU( 0xFFFDC008 );
                                                          -( EMAC ) जालम् स्थितिः पञ्जिकाकोशः
                                                          AT91C_EMAC_SA2L EQU( 0xFFFDC0A0 );
                                                          -( EMAC ) Specific स्थानाङ्कः 2 Bottom, First 4 अष्टकानि_2
                                                          AT91C_EMAC_FRO EQU( 0xFFFDC04C );
                                                          -( EMAC ) चौकटाः Received OK पञ्जिकाकोशः
                                                          AT91C_EMAC_IER EQU( 0xFFFDC028 );
                                                          -( EMAC ) व्यवधानम्_2 Enable पञ्जिकाकोशः
                                                          AT91C_EMAC_SA1H EQU( 0xFFFDC09C );
                                                          -( EMAC ) Specific स्थानाङ्कः 1 शिखरम्, चरमः 2 अष्टकानि_2
                                                          AT91C_EMAC_CSE EQU( 0xFFFDC068 );
                                                          -( EMAC ) Carrier Sense Error पञ्जिकाकोशः
                                                          AT91C_EMAC_SA3H EQU( 0xFFFDC0AC );
                                                          -( EMAC ) Specific स्थानाङ्कः 3 शिखरम्, चरमः 2 अष्टकानि_2
                                                          AT91C_EMAC_RRE EQU( 0xFFFDC06C );
                                                          -( EMAC ) Receive Resource Error पञ्जिकाकोशः
                                                          AT91C_EMAC_STE EQU( 0xFFFDC084 );
                                                          -( EMAC ) SQE Test Error पञ्जिकाकोशः
/* - ========== Register definition for PDC_ADC peripheral ========== */
                                                          AT91C_ADC_PTSR EQU( 0xFFFD8124 );
                                                          -( PDC_ADC ) PDC Transfer स्थितिः पञ्जिकाकोशः
                                                          AT91C_ADC_PTCR EQU( 0xFFFD8120 );
                                                          -( PDC_ADC ) PDC Transfer Control पञ्जिकाकोशः
                                                          AT91C_ADC_TNPR EQU( 0xFFFD8118 );
                                                          -( PDC_ADC ) Transmit अग्र Pointer पञ्जिकाकोशः
                                                          AT91C_ADC_TNCR EQU( 0xFFFD811C );
                                                          -( PDC_ADC ) Transmit अग्र गणक_2 पञ्जिकाकोशः
                                                          AT91C_ADC_RNPR EQU( 0xFFFD8110 );
                                                          -( PDC_ADC ) Receive अग्र Pointer पञ्जिकाकोशः
                                                          AT91C_ADC_RNCR EQU( 0xFFFD8114 );
                                                          -( PDC_ADC ) Receive अग्र गणक_2 पञ्जिकाकोशः
                                                          AT91C_ADC_RPR EQU( 0xFFFD8100 );
                                                          -( PDC_ADC ) Receive Pointer पञ्जिकाकोशः
                                                          AT91C_ADC_TCR EQU( 0xFFFD810C );
                                                          -( PDC_ADC ) Transmit गणक_2 पञ्जिकाकोशः
                                                          AT91C_ADC_TPR EQU( 0xFFFD8108 );
                                                          -( PDC_ADC ) Transmit Pointer पञ्जिकाकोशः
                                                          AT91C_ADC_RCR EQU( 0xFFFD8104 );
                                                          -( PDC_ADC ) Receive गणक_2 पञ्जिकाकोशः
/* - ========== Register definition for ADC peripheral ========== */
                                                          AT91C_ADC_CDR2 EQU( 0xFFFD8038 );
                                                          -( ADC ) ADC Channel दत्त पञ्जिकाकोशः 2
                                                          AT91C_ADC_CDR3 EQU( 0xFFFD803C );
                                                          -( ADC ) ADC Channel दत्त पञ्जिकाकोशः 3
                                                          AT91C_ADC_CDR0 EQU( 0xFFFD8030 );
                                                          -( ADC ) ADC Channel दत्त पञ्जिकाकोशः 0
                                                          AT91C_ADC_CDR5 EQU( 0xFFFD8044 );
                                                          -( ADC ) ADC Channel दत्त पञ्जिकाकोशः 5
                                                          AT91C_ADC_CHDR EQU( 0xFFFD8014 );
                                                          -( ADC ) ADC Channel Disable पञ्जिकाकोशः
                                                          AT91C_ADC_SR EQU( 0xFFFD801C );
                                                          -( ADC ) ADC स्थितिः पञ्जिकाकोशः
                                                          AT91C_ADC_CDR4 EQU( 0xFFFD8040 );
                                                          -( ADC ) ADC Channel दत्त पञ्जिकाकोशः 4
                                                          AT91C_ADC_CDR1 EQU( 0xFFFD8034 );
                                                          -( ADC ) ADC Channel दत्त पञ्जिकाकोशः 1
                                                          AT91C_ADC_LCDR EQU( 0xFFFD8020 );
                                                          -( ADC ) ADC चरमः Converted दत्त पञ्जिकाकोशः
                                                          AT91C_ADC_IDR EQU( 0xFFFD8028 );
                                                          -( ADC ) ADC व्यवधानम्_2 Disable पञ्जिकाकोशः
                                                          AT91C_ADC_CR EQU( 0xFFFD8000 );
                                                          -( ADC ) ADC Control पञ्जिकाकोशः
                                                          AT91C_ADC_CDR7 EQU( 0xFFFD804C );
                                                          -( ADC ) ADC Channel दत्त पञ्जिकाकोशः 7
                                                          AT91C_ADC_CDR6 EQU( 0xFFFD8048 );
                                                          -( ADC ) ADC Channel दत्त पञ्जिकाकोशः 6
                                                          AT91C_ADC_IER EQU( 0xFFFD8024 );
                                                          -( ADC ) ADC व्यवधानम्_2 Enable पञ्जिकाकोशः
                                                          AT91C_ADC_CHER EQU( 0xFFFD8010 );
                                                          -( ADC ) ADC Channel Enable पञ्जिकाकोशः
                                                          AT91C_ADC_CHSR EQU( 0xFFFD8018 );
                                                          -( ADC ) ADC Channel स्थितिः पञ्जिकाकोशः
                                                          AT91C_ADC_MR EQU( 0xFFFD8004 );
                                                          -( ADC ) ADC बहुलकम् पञ्जिकाकोशः
                                                          AT91C_ADC_IMR EQU( 0xFFFD802C );
                                                          -( ADC ) ADC व्यवधानम्_2 आवरणम्_2 पञ्जिकाकोशः
/* - ========== Register definition for PDC_AES peripheral ========== */
                                                          AT91C_AES_TPR EQU( 0xFFFA4108 );
                                                          -( PDC_AES ) Transmit Pointer पञ्जिकाकोशः
                                                          AT91C_AES_PTCR EQU( 0xFFFA4120 );
                                                          -( PDC_AES ) PDC Transfer Control पञ्जिकाकोशः
                                                          AT91C_AES_RNPR EQU( 0xFFFA4110 );
                                                          -( PDC_AES ) Receive अग्र Pointer पञ्जिकाकोशः
                                                          AT91C_AES_TNCR EQU( 0xFFFA411C );
                                                          -( PDC_AES ) Transmit अग्र गणक_2 पञ्जिकाकोशः
                                                          AT91C_AES_TCR EQU( 0xFFFA410C );
                                                          -( PDC_AES ) Transmit गणक_2 पञ्जिकाकोशः
                                                          AT91C_AES_RCR EQU( 0xFFFA4104 );
                                                          -( PDC_AES ) Receive गणक_2 पञ्जिकाकोशः
                                                          AT91C_AES_RNCR EQU( 0xFFFA4114 );
                                                          -( PDC_AES ) Receive अग्र गणक_2 पञ्जिकाकोशः
                                                          AT91C_AES_TNPR EQU( 0xFFFA4118 );
                                                          -( PDC_AES ) Transmit अग्र Pointer पञ्जिकाकोशः
                                                          AT91C_AES_RPR EQU( 0xFFFA4100 );
                                                          -( PDC_AES ) Receive Pointer पञ्जिकाकोशः
                                                          AT91C_AES_PTSR EQU( 0xFFFA4124 );
                                                          -( PDC_AES ) PDC Transfer स्थितिः पञ्जिकाकोशः
/* - ========== Register definition for AES peripheral ========== */
                                                          AT91C_AES_IVxR EQU( 0xFFFA4060 );
                                                          -( AES ) Initialization सदिशम्_2 x पञ्जिकाकोशः
                                                          AT91C_AES_MR EQU( 0xFFFA4004 );
                                                          -( AES ) बहुलकम् पञ्जिकाकोशः
                                                          AT91C_AES_VR EQU( 0xFFFA40FC );
                                                          -( AES ) AES संस्करणम्_2 पञ्जिकाकोशः
                                                          AT91C_AES_ODATAxR EQU( 0xFFFA4050 );
                                                          -( AES ) Output दत्त x पञ्जिकाकोशः
                                                          AT91C_AES_IDATAxR EQU( 0xFFFA4040 );
                                                          -( AES ) निवेशः दत्त x पञ्जिकाकोशः
                                                          AT91C_AES_CR EQU( 0xFFFA4000 );
                                                          -( AES ) Control पञ्जिकाकोशः
                                                          AT91C_AES_IDR EQU( 0xFFFA4014 );
                                                          -( AES ) व्यवधानम्_2 Disable पञ्जिकाकोशः
                                                          AT91C_AES_IMR EQU( 0xFFFA4018 );
                                                          -( AES ) व्यवधानम्_2 आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_AES_IER EQU( 0xFFFA4010 );
                                                          -( AES ) व्यवधानम्_2 Enable पञ्जिकाकोशः
                                                          AT91C_AES_KEYWxR EQU( 0xFFFA4020 );
                                                          -( AES ) कुञ्चिका_2 Word x पञ्जिकाकोशः
                                                          AT91C_AES_ISR EQU( 0xFFFA401C );
                                                          -( AES ) व्यवधानम्_2 स्थितिः पञ्जिकाकोशः
/* - ========== Register definition for PDC_TDES peripheral ========== */
                                                          AT91C_TDES_RNCR EQU( 0xFFFA8114 );
                                                          -( PDC_TDES ) Receive अग्र गणक_2 पञ्जिकाकोशः
                                                          AT91C_TDES_TCR EQU( 0xFFFA810C );
                                                          -( PDC_TDES ) Transmit गणक_2 पञ्जिकाकोशः
                                                          AT91C_TDES_RCR EQU( 0xFFFA8104 );
                                                          -( PDC_TDES ) Receive गणक_2 पञ्जिकाकोशः
                                                          AT91C_TDES_TNPR EQU( 0xFFFA8118 );
                                                          -( PDC_TDES ) Transmit अग्र Pointer पञ्जिकाकोशः
                                                          AT91C_TDES_RNPR EQU( 0xFFFA8110 );
                                                          -( PDC_TDES ) Receive अग्र Pointer पञ्जिकाकोशः
                                                          AT91C_TDES_RPR EQU( 0xFFFA8100 );
                                                          -( PDC_TDES ) Receive Pointer पञ्जिकाकोशः
                                                          AT91C_TDES_TNCR EQU( 0xFFFA811C );
                                                          -( PDC_TDES ) Transmit अग्र गणक_2 पञ्जिकाकोशः
                                                          AT91C_TDES_TPR EQU( 0xFFFA8108 );
                                                          -( PDC_TDES ) Transmit Pointer पञ्जिकाकोशः
                                                          AT91C_TDES_PTSR EQU( 0xFFFA8124 );
                                                          -( PDC_TDES ) PDC Transfer स्थितिः पञ्जिकाकोशः
                                                          AT91C_TDES_PTCR EQU( 0xFFFA8120 );
                                                          -( PDC_TDES ) PDC Transfer Control पञ्जिकाकोशः
/* - ========== Register definition for TDES peripheral ========== */
                                                          AT91C_TDES_KEY2WxR EQU( 0xFFFA8028 );
                                                          -( TDES ) कुञ्चिका_2 2 Word x पञ्जिकाकोशः
                                                          AT91C_TDES_KEY3WxR EQU( 0xFFFA8030 );
                                                          -( TDES ) कुञ्चिका_2 3 Word x पञ्जिकाकोशः
                                                          AT91C_TDES_IDR EQU( 0xFFFA8014 );
                                                          -( TDES ) व्यवधानम्_2 Disable पञ्जिकाकोशः
                                                          AT91C_TDES_VR EQU( 0xFFFA80FC );
                                                          -( TDES ) TDES संस्करणम्_2 पञ्जिकाकोशः
                                                          AT91C_TDES_IVxR EQU( 0xFFFA8060 );
                                                          -( TDES ) Initialization सदिशम्_2 x पञ्जिकाकोशः
                                                          AT91C_TDES_ODATAxR EQU( 0xFFFA8050 );
                                                          -( TDES ) Output दत्त x पञ्जिकाकोशः
                                                          AT91C_TDES_IMR EQU( 0xFFFA8018 );
                                                          -( TDES ) व्यवधानम्_2 आवरणम्_2 पञ्जिकाकोशः
                                                          AT91C_TDES_MR EQU( 0xFFFA8004 );
                                                          -( TDES ) बहुलकम् पञ्जिकाकोशः
                                                          AT91C_TDES_CR EQU( 0xFFFA8000 );
                                                          -( TDES ) Control पञ्जिकाकोशः
                                                          AT91C_TDES_IER EQU( 0xFFFA8010 );
                                                          -( TDES ) व्यवधानम्_2 Enable पञ्जिकाकोशः
                                                          AT91C_TDES_ISR EQU( 0xFFFA801C );
                                                          -( TDES ) व्यवधानम्_2 स्थितिः पञ्जिकाकोशः
                                                          AT91C_TDES_IDATAxR EQU( 0xFFFA8040 );
                                                          -( TDES ) निवेशः दत्त x पञ्जिकाकोशः
                                                          AT91C_TDES_KEY1WxR EQU( 0xFFFA8020 );
                                                          -( TDES ) कुञ्चिका_2 1 Word x पञ्जिकाकोशः

/* - ***************************************************************************** */
/* -               PIO DEFINITIONS FOR AT91SAM7X256 */
/* - ***************************************************************************** */
                                                          AT91C_PIO_PA0 EQU( 1 << 0 );
                                                          -Pin Controlled by PA0
                                                          AT91C_PA0_RXD0 EQU( AT91C_PIO_PA0 );
                                                          -USART 0 Receive दत्त
                                                          AT91C_PIO_PA1 EQU( 1 << 1 );
                                                          -Pin Controlled by PA1
                                                          AT91C_PA1_TXD0 EQU( AT91C_PIO_PA1 );
                                                          -USART 0 Transmit दत्त
                                                          AT91C_PIO_PA10 EQU( 1 << 10 );
                                                          -Pin Controlled by PA10
                                                          AT91C_PA10_TWD EQU( AT91C_PIO_PA10 );
                                                          -TWI Two - wire Serial दत्त
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
                                                          -External व्यवधानम्_2 1
                                                          AT91C_PIO_PA15 EQU( 1 << 15 );
                                                          -Pin Controlled by PA15
                                                          AT91C_PA15_NPCS03 EQU( AT91C_PIO_PA15 );
                                                          -SPI 0 Peripheral Chip Select 3
                                                          AT91C_PA15_TCLK2 EQU( AT91C_PIO_PA15 );
                                                          -Timer गणक_2 2 external clock निवेशः_2
                                                          AT91C_PIO_PA16 EQU( 1 << 16 );
                                                          -Pin Controlled by PA16
                                                          AT91C_PA16_MISO0 EQU( AT91C_PIO_PA16 );
                                                          -SPI 0 Master अन्तर्_3 Slave
                                                          AT91C_PIO_PA17 EQU( 1 << 17 );
                                                          -Pin Controlled by PA17
                                                          AT91C_PA17_MOSI0 EQU( AT91C_PIO_PA17 );
                                                          -SPI 0 Master बहिर्गमनम्_3 Slave
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
                                                          -SSC Transmit Frame Sync
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
                                                          -SSC Transmit दत्त_2
                                                          AT91C_PA23_MOSI1 EQU( AT91C_PIO_PA23 );
                                                          -SPI 1 Master बहिर्गमनम्_3 Slave
                                                          AT91C_PIO_PA24 EQU( 1 << 24 );
                                                          -Pin Controlled by PA24
                                                          AT91C_PA24_RD EQU( AT91C_PIO_PA24 );
                                                          -SSC Receive दत्त
                                                          AT91C_PA24_MISO1 EQU( AT91C_PIO_PA24 );
                                                          -SPI 1 Master अन्तर्_3 Slave
                                                          AT91C_PIO_PA25 EQU( 1 << 25 );
                                                          -Pin Controlled by PA25
                                                          AT91C_PA25_RK EQU( AT91C_PIO_PA25 );
                                                          -SSC Receive Clock
                                                          AT91C_PA25_NPCS11 EQU( AT91C_PIO_PA25 );
                                                          -SPI 1 Peripheral Chip Select 1
                                                          AT91C_PIO_PA26 EQU( 1 << 26 );
                                                          -Pin Controlled by PA26
                                                          AT91C_PA26_RF EQU( AT91C_PIO_PA26 );
                                                          -SSC Receive Frame Sync
                                                          AT91C_PA26_NPCS12 EQU( AT91C_PIO_PA26 );
                                                          -SPI 1 Peripheral Chip Select 2
                                                          AT91C_PIO_PA27 EQU( 1 << 27 );
                                                          -Pin Controlled by PA27
                                                          AT91C_PA27_DRXD EQU( AT91C_PIO_PA27 );
                                                          -DBGU Debug Receive दत्त
                                                          AT91C_PA27_PCK3 EQU( AT91C_PIO_PA27 );
                                                          -PMC Programmable Clock Output 3
                                                          AT91C_PIO_PA28 EQU( 1 << 28 );
                                                          -Pin Controlled by PA28
                                                          AT91C_PA28_DTXD EQU( AT91C_PIO_PA28 );
                                                          -DBGU Debug Transmit दत्त
                                                          AT91C_PIO_PA29 EQU( 1 << 29 );
                                                          -Pin Controlled by PA29
                                                          AT91C_PA29_FIQ EQU( AT91C_PIO_PA29 );
                                                          -AIC Fast व्यवधानम्_2 निवेशः
                                                          AT91C_PA29_NPCS13 EQU( AT91C_PIO_PA29 );
                                                          -SPI 1 Peripheral Chip Select 3
                                                          AT91C_PIO_PA3 EQU( 1 << 3 );
                                                          -Pin Controlled by PA3
                                                          AT91C_PA3_RTS0 EQU( AT91C_PIO_PA3 );
                                                          -USART 0 Ready गन्तव्यम्_2 Send
                                                          AT91C_PA3_NPCS12 EQU( AT91C_PIO_PA3 );
                                                          -SPI 1 Peripheral Chip Select 2
                                                          AT91C_PIO_PA30 EQU( 1 << 30 );
                                                          -Pin Controlled by PA30
                                                          AT91C_PA30_IRQ0 EQU( AT91C_PIO_PA30 );
                                                          -External व्यवधानम्_2 0
                                                          AT91C_PA30_PCK2 EQU( AT91C_PIO_PA30 );
                                                          -PMC Programmable Clock Output 2
                                                          AT91C_PIO_PA4 EQU( 1 << 4 );
                                                          -Pin Controlled by PA4
                                                          AT91C_PA4_CTS0 EQU( AT91C_PIO_PA4 );
                                                          -USART 0 Clear गन्तव्यम्_2 Send
                                                          AT91C_PA4_NPCS13 EQU( AT91C_PIO_PA4 );
                                                          -SPI 1 Peripheral Chip Select 3
                                                          AT91C_PIO_PA5 EQU( 1 << 5 );
                                                          -Pin Controlled by PA5
                                                          AT91C_PA5_RXD1 EQU( AT91C_PIO_PA5 );
                                                          -USART 1 Receive दत्त
                                                          AT91C_PIO_PA6 EQU( 1 << 6 );
                                                          -Pin Controlled by PA6
                                                          AT91C_PA6_TXD1 EQU( AT91C_PIO_PA6 );
                                                          -USART 1 Transmit दत्त
                                                          AT91C_PIO_PA7 EQU( 1 << 7 );
                                                          -Pin Controlled by PA7
                                                          AT91C_PA7_SCK1 EQU( AT91C_PIO_PA7 );
                                                          -USART 1 Serial Clock
                                                          AT91C_PA7_NPCS01 EQU( AT91C_PIO_PA7 );
                                                          -SPI 0 Peripheral Chip Select 1
                                                          AT91C_PIO_PA8 EQU( 1 << 8 );
                                                          -Pin Controlled by PA8
                                                          AT91C_PA8_RTS1 EQU( AT91C_PIO_PA8 );
                                                          -USART 1 Ready गन्तव्यम्_2 Send
                                                          AT91C_PA8_NPCS02 EQU( AT91C_PIO_PA8 );
                                                          -SPI 0 Peripheral Chip Select 2
                                                          AT91C_PIO_PA9 EQU( 1 << 9 );
                                                          -Pin Controlled by PA9
                                                          AT91C_PA9_CTS1 EQU( AT91C_PIO_PA9 );
                                                          -USART 1 Clear गन्तव्यम्_2 Send
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
                                                          -Ethernet MAC Transmit दत्त 2
                                                          AT91C_PB10_NPCS11 EQU( AT91C_PIO_PB10 );
                                                          -SPI 1 Peripheral Chip Select 1
                                                          AT91C_PIO_PB11 EQU( 1 << 11 );
                                                          -Pin Controlled by PB11
                                                          AT91C_PB11_ETX3 EQU( AT91C_PIO_PB11 );
                                                          -Ethernet MAC Transmit दत्त 3
                                                          AT91C_PB11_NPCS12 EQU( AT91C_PIO_PB11 );
                                                          -SPI 1 Peripheral Chip Select 2
                                                          AT91C_PIO_PB12 EQU( 1 << 12 );
                                                          -Pin Controlled by PB12
                                                          AT91C_PB12_ETXER EQU( AT91C_PIO_PB12 );
                                                          -Ethernet MAC Transmit Coding Error
                                                          AT91C_PB12_TCLK0 EQU( AT91C_PIO_PB12 );
                                                          -Timer गणक_2 0 external clock निवेशः_2
                                                          AT91C_PIO_PB13 EQU( 1 << 13 );
                                                          -Pin Controlled by PB13
                                                          AT91C_PB13_ERX2 EQU( AT91C_PIO_PB13 );
                                                          -Ethernet MAC Receive दत्त 2
                                                          AT91C_PB13_NPCS01 EQU( AT91C_PIO_PB13 );
                                                          -SPI 0 Peripheral Chip Select 1
                                                          AT91C_PIO_PB14 EQU( 1 << 14 );
                                                          -Pin Controlled by PB14
                                                          AT91C_PB14_ERX3 EQU( AT91C_PIO_PB14 );
                                                          -Ethernet MAC Receive दत्त 3
                                                          AT91C_PB14_NPCS02 EQU( AT91C_PIO_PB14 );
                                                          -SPI 0 Peripheral Chip Select 2
                                                          AT91C_PIO_PB15 EQU( 1 << 15 );
                                                          -Pin Controlled by PB15
                                                          AT91C_PB15_ERXDV EQU( AT91C_PIO_PB15 );
                                                          -Ethernet MAC Receive दत्त Valid
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
                                                          -Timer गणक_2 1 external clock निवेशः_2
                                                          AT91C_PIO_PB2 EQU( 1 << 2 );
                                                          -Pin Controlled by PB2
                                                          AT91C_PB2_ETX0 EQU( AT91C_PIO_PB2 );
                                                          -Ethernet MAC Transmit दत्त 0
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
                                                          -Timer गणक_2 0 Multipurpose Timer I / O Pin A
                                                          AT91C_PB23_DCD1 EQU( AT91C_PIO_PB23 );
                                                          -USART 1 दत्त Carrier Detect
                                                          AT91C_PIO_PB24 EQU( 1 << 24 );
                                                          -Pin Controlled by PB24
                                                          AT91C_PB24_TIOB0 EQU( AT91C_PIO_PB24 );
                                                          -Timer गणक_2 0 Multipurpose Timer I / O Pin B
                                                          AT91C_PB24_DSR1 EQU( AT91C_PIO_PB24 );
                                                          -USART 1 दत्त समुच्चयः_2 ready
                                                          AT91C_PIO_PB25 EQU( 1 << 25 );
                                                          -Pin Controlled by PB25
                                                          AT91C_PB25_TIOA1 EQU( AT91C_PIO_PB25 );
                                                          -Timer गणक_2 1 Multipurpose Timer I / O Pin A
                                                          AT91C_PB25_DTR1 EQU( AT91C_PIO_PB25 );
                                                          -USART 1 दत्त Terminal ready
                                                          AT91C_PIO_PB26 EQU( 1 << 26 );
                                                          -Pin Controlled by PB26
                                                          AT91C_PB26_TIOB1 EQU( AT91C_PIO_PB26 );
                                                          -Timer गणक_2 1 Multipurpose Timer I / O Pin B
                                                          AT91C_PB26_RI1 EQU( AT91C_PIO_PB26 );
                                                          -USART 1 Ring Indicator
                                                          AT91C_PIO_PB27 EQU( 1 << 27 );
                                                          -Pin Controlled by PB27
                                                          AT91C_PB27_TIOA2 EQU( AT91C_PIO_PB27 );
                                                          -Timer गणक_2 2 Multipurpose Timer I / O Pin A
                                                          AT91C_PB27_PWM0 EQU( AT91C_PIO_PB27 );
                                                          -PWM Channel 0
                                                          AT91C_PIO_PB28 EQU( 1 << 28 );
                                                          -Pin Controlled by PB28
                                                          AT91C_PB28_TIOB2 EQU( AT91C_PIO_PB28 );
                                                          -Timer गणक_2 2 Multipurpose Timer I / O Pin B
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
                                                          -Ethernet MAC Transmit दत्त 1
                                                          AT91C_PIO_PB30 EQU( 1 << 30 );
                                                          -Pin Controlled by PB30
                                                          AT91C_PB30_PCK2 EQU( AT91C_PIO_PB30 );
                                                          -PMC Programmable Clock Output 2
                                                          AT91C_PB30_PWM3 EQU( AT91C_PIO_PB30 );
                                                          -PWM Channel 3
                                                          AT91C_PIO_PB4 EQU( 1 << 4 );
                                                          -Pin Controlled by PB4
                                                          AT91C_PB4_ECRS_ECRSDV EQU( AT91C_PIO_PB4 );
                                                          -Ethernet MAC Carrier Sense / Carrier Sense and दत्त Valid
                                                          AT91C_PIO_PB5 EQU( 1 << 5 );
                                                          -Pin Controlled by PB5
                                                          AT91C_PB5_ERX0 EQU( AT91C_PIO_PB5 );
                                                          -Ethernet MAC Receive दत्त 0
                                                          AT91C_PIO_PB6 EQU( 1 << 6 );
                                                          -Pin Controlled by PB6
                                                          AT91C_PB6_ERX1 EQU( AT91C_PIO_PB6 );
                                                          -Ethernet MAC Receive दत्त 1
                                                          AT91C_PIO_PB7 EQU( 1 << 7 );
                                                          -Pin Controlled by PB7
                                                          AT91C_PB7_ERXER EQU( AT91C_PIO_PB7 );
                                                          -Ethernet MAC Receive Error
                                                          AT91C_PIO_PB8 EQU( 1 << 8 );
                                                          -Pin Controlled by PB8
                                                          AT91C_PB8_EMDC EQU( AT91C_PIO_PB8 );
                                                          -Ethernet MAC Management दत्त Clock
                                                          AT91C_PIO_PB9 EQU( 1 << 9 );
                                                          -Pin Controlled by PB9
                                                          AT91C_PB9_EMDIO EQU( AT91C_PIO_PB9 );
                                                          -Ethernet MAC Management दत्त निवेशः / Output

/* - ***************************************************************************** */
/* -               PERIPHERAL ID DEFINITIONS FOR AT91SAM7X256 */
/* - ***************************************************************************** */
                                                          AT91C_ID_FIQ EQU( 0 );
                                                          -Advanced व्यवधानम्_2 Controller( FIQ )
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
                                                          -USB Device पत्तनम्_2
                                                          AT91C_ID_TC0 EQU( 12 );
                                                          -Timer गणक_2 0
                                                          AT91C_ID_TC1 EQU( 13 );
                                                          -Timer गणक_2 1
                                                          AT91C_ID_TC2 EQU( 14 );
                                                          -Timer गणक_2 2
                                                          AT91C_ID_CAN EQU( 15 );
                                                          -Control Area जालम् Controller
                                                          AT91C_ID_EMAC EQU( 16 );
                                                          -Ethernet MAC
                                                          AT91C_ID_ADC EQU( 17 );
                                                          -Analog - गन्तव्यम् - Digital Converter
                                                          AT91C_ID_AES EQU( 18 );
                                                          -Advanced Encryption Standard 128 - bit
                                                          AT91C_ID_TDES EQU( 19 );
                                                          -Triple दत्त Encryption Standard
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
                                                          -Advanced व्यवधानम्_2 Controller( IRQ0 )
                                                          AT91C_ID_IRQ1 EQU( 31 );
                                                          -Advanced व्यवधानम्_2 Controller( IRQ1 )

/* - ***************************************************************************** */
/* -               BASE ADDRESS DEFINITIONS FOR AT91SAM7X256 */
/* - ***************************************************************************** */
                                                          AT91_C_आधारः_SYS EQU( 0xFFFFF000 );
                                                          -( SYS ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_AIC EQU( 0xFFFFF000 );
                                                          -( AIC ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_PDC_DBGU EQU( 0xFFFFF300 );
                                                          -( PDC_DBGU ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_DBGU EQU( 0xFFFFF200 );
                                                          -( DBGU ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_PIOA EQU( 0xFFFFF400 );
                                                          -( PIOA ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_PIOB EQU( 0xFFFFF600 );
                                                          -( PIOB ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_CKGR EQU( 0xFFFFFC20 );
                                                          -( CKGR ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_PMC EQU( 0xFFFFFC00 );
                                                          -( PMC ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_RSTC EQU( 0xFFFFFD00 );
                                                          -( RSTC ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_RTTC EQU( 0xFFFFFD20 );
                                                          -( RTTC ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_PITC EQU( 0xFFFFFD30 );
                                                          -( PITC ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_WDTC EQU( 0xFFFFFD40 );
                                                          -( WDTC ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_VREG EQU( 0xFFFFFD60 );
                                                          -( VREG ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_MC EQU( 0xFFFFFF00 );
                                                          -( MC ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_PDC_SPI1 EQU( 0xFFFE4100 );
                                                          -( PDC_SPI1 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_SPI1 EQU( 0xFFFE4000 );
                                                          -( SPI1 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_PDC_SPI0 EQU( 0xFFFE0100 );
                                                          -( PDC_SPI0 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_SPI0 EQU( 0xFFFE0000 );
                                                          -( SPI0 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_PDC_US1 EQU( 0xFFFC4100 );
                                                          -( PDC_US1 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_US1 EQU( 0xFFFC4000 );
                                                          -( US1 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_PDC_US0 EQU( 0xFFFC0100 );
                                                          -( PDC_US0 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_US0 EQU( 0xFFFC0000 );
                                                          -( US0 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_PDC_SSC EQU( 0xFFFD4100 );
                                                          -( PDC_SSC ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_SSC EQU( 0xFFFD4000 );
                                                          -( SSC ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_TWI EQU( 0xFFFB8000 );
                                                          -( TWI ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_PWMC_CH3 EQU( 0xFFFCC260 );
                                                          -( PWMC_CH3 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_PWMC_CH2 EQU( 0xFFFCC240 );
                                                          -( PWMC_CH2 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_PWMC_CH1 EQU( 0xFFFCC220 );
                                                          -( PWMC_CH1 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_PWMC_CH0 EQU( 0xFFFCC200 );
                                                          -( PWMC_CH0 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_PWMC EQU( 0xFFFCC000 );
                                                          -( PWMC ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_UDP EQU( 0xFFFB0000 );
                                                          -( UDP ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_TC0 EQU( 0xFFFA0000 );
                                                          -( TC0 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_TC1 EQU( 0xFFFA0040 );
                                                          -( TC1 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_TC2 EQU( 0xFFFA0080 );
                                                          -( TC2 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_TCB EQU( 0xFFFA0000 );
                                                          -( TCB ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_CAN_MB0 EQU( 0xFFFD0200 );
                                                          -( CAN_MB0 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_CAN_MB1 EQU( 0xFFFD0220 );
                                                          -( CAN_MB1 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_CAN_MB2 EQU( 0xFFFD0240 );
                                                          -( CAN_MB2 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_CAN_MB3 EQU( 0xFFFD0260 );
                                                          -( CAN_MB3 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_CAN_MB4 EQU( 0xFFFD0280 );
                                                          -( CAN_MB4 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_CAN_MB5 EQU( 0xFFFD02A0 );
                                                          -( CAN_MB5 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_CAN_MB6 EQU( 0xFFFD02C0 );
                                                          -( CAN_MB6 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_CAN_MB7 EQU( 0xFFFD02E0 );
                                                          -( CAN_MB7 ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_CAN EQU( 0xFFFD0000 );
                                                          -( CAN ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_EMAC EQU( 0xFFFDC000 );
                                                          -( EMAC ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_PDC_ADC EQU( 0xFFFD8100 );
                                                          -( PDC_ADC ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_ADC EQU( 0xFFFD8000 );
                                                          -( ADC ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_PDC_AES EQU( 0xFFFA4100 );
                                                          -( PDC_AES ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_AES EQU( 0xFFFA4000 );
                                                          -( AES ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_PDC_TDES EQU( 0xFFFA8100 );
                                                          -( PDC_TDES ) आधारः_2 स्थानाङ्कः
                                                          AT91_C_आधारः_TDES EQU( 0xFFFA8000 );
                                                          -( TDES ) आधारः_2 स्थानाङ्कः

/* - ***************************************************************************** */
/* -               MEMORY MAPPING DEFINITIONS FOR AT91SAM7X256 */
/* - ***************************************************************************** */
                                                          AT91C_ISRAM EQU( 0x00200000 );
                                                          -आन्तरिकम् SRAM आधारः स्थानाङ्कः_2
                                                          AT91_C_ISRAM_आकार EQU( 0x00010000 );
                                                          -आन्तरिकम् SRAM आकार अन्तर् byte( 64 Kbyte )
                                                          AT91C_IFLASH EQU( 0x00100000 );
                                                          -आन्तरिकम् ROM आधारः स्थानाङ्कः_2
                                                          AT91_C_IFLASH_आकार EQU( 0x00040000 );
                                                          -आन्तरिकम् ROM आकार अन्तर् byte( 256 Kbyte )



#यदि_अन्तः /* AT91SAM7X256_H */
