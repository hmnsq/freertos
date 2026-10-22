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

#اگر_تعریف_نشده AT91SAM7X256_H
#تعریف_کن AT91SAM7X256_H

تعريفنوع متطاير بیعلامت صحيح AT91_REG; /* Hardware register definition */

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
    AT91_REG PIOA_در_هر;          /* PIO Enable Register */
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
    AT91_REG PIOB_در_هر;          /* PIO Enable Register */
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
#تعریف_کن AT91_C_AIC_پیشین                            ( ( بیعلامت صحيح ) 0x7 << 0 ) /* (AIC) Priority Level */
#تعریف_کن     AT91_C_AIC_پیشین_پایینترین                 ( ( بیعلامت صحيح ) 0x0 )      /* (AIC) Lowest priority level */
#تعریف_کن     AT91_C_AIC_پیشین_HIGHEST                ( ( بیعلامت صحيح ) 0x7 )      /* (AIC) Highest priority level */
#تعریف_کن AT91C_AIC_SRCTYPE                          ( ( بیعلامت صحيح ) 0x3 << 5 ) /* (AIC) Interrupt Source Type */
#تعریف_کن     AT91_C_AIC_SRCTYPE_INT_بالا_LEVEL       ( ( بیعلامت صحيح ) 0x0 << 5 ) /* (AIC) Internal Sources Code Label High-level Sensitive */
#تعریف_کن     AT91_C_AIC_SRCTYPE_EXT_کم_LEVEL        ( ( بیعلامت صحيح ) 0x0 << 5 ) /* (AIC) External Sources Code Label Low-level Sensitive */
#تعریف_کن     AT91_C_AIC_SRCTYPE_INT_مثبت_یال    ( ( بیعلامت صحيح ) 0x1 << 5 ) /* (AIC) Internal Sources Code Label Positive Edge triggered */
#تعریف_کن     AT91_C_AIC_SRCTYPE_EXT_NEGATIVE_یال    ( ( بیعلامت صحيح ) 0x1 << 5 ) /* (AIC) External Sources Code Label Negative Edge triggered */
#تعریف_کن     AT91_C_AIC_SRCTYPE_بالا_LEVEL           ( ( بیعلامت صحيح ) 0x2 << 5 ) /* (AIC) Internal Or External Sources Code Label High-level Sensitive */
#تعریف_کن     AT91_C_AIC_SRCTYPE_مثبت_یال        ( ( بیعلامت صحيح ) 0x3 << 5 ) /* (AIC) Internal Or External Sources Code Label Positive Edge triggered */
/* -------- AIC_CISR : (AIC Offset: 0x114) AIC Core Interrupt Status Register -------- */
#تعریف_کن AT91C_AIC_NFIQ                             ( ( بیعلامت صحيح ) 0x1 << 0 ) /* (AIC) NFIQ Status */
#تعریف_کن AT91C_AIC_NIRQ                             ( ( بیعلامت صحيح ) 0x1 << 1 ) /* (AIC) NIRQ Status */
/* -------- AIC_DCR : (AIC Offset: 0x138) AIC Debug Control Register (Protect) -------- */
#تعریف_کن AT91C_AIC_DCR_PROT                         ( ( بیعلامت صحيح ) 0x1 << 0 ) /* (AIC) Protection Mode */
#تعریف_کن AT91C_AIC_DCR_GMSK                         ( ( بیعلامت صحيح ) 0x1 << 1 ) /* (AIC) General Mask */

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
#تعریف_کن AT91C_PDC_RXTEN     ( ( بیعلامت صحيح ) 0x1 << 0 ) /* (PDC) Receiver Transfer Enable */
#تعریف_کن AT91C_PDC_RXTDIS    ( ( بیعلامت صحيح ) 0x1 << 1 ) /* (PDC) Receiver Transfer Disable */
#تعریف_کن AT91C_PDC_TXTEN     ( ( بیعلامت صحيح ) 0x1 << 8 ) /* (PDC) Transmitter Transfer Enable */
#تعریف_کن AT91C_PDC_TXTDIS    ( ( بیعلامت صحيح ) 0x1 << 9 ) /* (PDC) Transmitter Transfer Disable */
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
#تعریف_کن AT91C_US_RSTRX                 ( ( بیعلامت صحيح ) 0x1 << 2 )  /* (DBGU) Reset Receiver */
#تعریف_کن AT91C_US_RSTTX                 ( ( بیعلامت صحيح ) 0x1 << 3 )  /* (DBGU) Reset Transmitter */
#تعریف_کن AT91C_US_RXEN                  ( ( بیعلامت صحيح ) 0x1 << 4 )  /* (DBGU) Receiver Enable */
#تعریف_کن AT91C_US_RXDIS                 ( ( بیعلامت صحيح ) 0x1 << 5 )  /* (DBGU) Receiver Disable */
#تعریف_کن AT91C_US_TXEN                  ( ( بیعلامت صحيح ) 0x1 << 6 )  /* (DBGU) Transmitter Enable */
#تعریف_کن AT91C_US_TXDIS                 ( ( بیعلامت صحيح ) 0x1 << 7 )  /* (DBGU) Transmitter Disable */
#تعریف_کن AT91C_US_RSTSTA                ( ( بیعلامت صحيح ) 0x1 << 8 )  /* (DBGU) Reset Status Bits */
/* -------- DBGU_MR : (DBGU Offset: 0x4) Debug Unit Mode Register -------- */
#تعریف_کن AT91C_US_PAR                   ( ( بیعلامت صحيح ) 0x7 << 9 )  /* (DBGU) Parity type */
#تعریف_کن     AT91C_US_PAR_EVEN          ( ( بیعلامت صحيح ) 0x0 << 9 )  /* (DBGU) Even Parity */
#تعریف_کن     AT91C_US_PAR_ODD           ( ( بیعلامت صحيح ) 0x1 << 9 )  /* (DBGU) Odd Parity */
#تعریف_کن     AT91C_US_PAR_SPACE         ( ( بیعلامت صحيح ) 0x2 << 9 )  /* (DBGU) Parity forced to 0 (Space) */
#تعریف_کن     AT91C_US_PAR_MARK          ( ( بیعلامت صحيح ) 0x3 << 9 )  /* (DBGU) Parity forced to 1 (Mark) */
#تعریف_کن     AT91C_US_PAR_NONE          ( ( بیعلامت صحيح ) 0x4 << 9 )  /* (DBGU) No Parity */
#تعریف_کن     AT91C_US_PAR_MULTI_DROP    ( ( بیعلامت صحيح ) 0x6 << 9 )  /* (DBGU) Multi-drop mode */
#تعریف_کن AT91C_US_CHMODE                ( ( بیعلامت صحيح ) 0x3 << 14 ) /* (DBGU) Channel Mode */
#تعریف_کن     AT91_C_US_CHMODE_نرمال     ( ( بیعلامت صحيح ) 0x0 << 14 ) /* (DBGU) Normal Mode: The USART channel operates as an RX/TX USART. */
#تعریف_کن     AT91C_US_CHMODE_AUTO       ( ( بیعلامت صحيح ) 0x1 << 14 ) /* (DBGU) Automatic Echo: Receiver Data Input is connected to the TXD pin. */
#تعریف_کن     AT91C_US_CHMODE_LOCAL      ( ( بیعلامت صحيح ) 0x2 << 14 ) /* (DBGU) Local Loopback: Transmitter Output Signal is connected to Receiver Input Signal. */
#تعریف_کن     AT91C_US_CHMODE_REMOTE     ( ( بیعلامت صحيح ) 0x3 << 14 ) /* (DBGU) Remote Loopback: RXD pin is internally connected to TXD pin. */
/* -------- DBGU_IER : (DBGU Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
#تعریف_کن AT91C_US_RXRDY                 ( ( بیعلامت صحيح ) 0x1 << 0 )  /* (DBGU) RXRDY Interrupt */
#تعریف_کن AT91C_US_TXRDY                 ( ( بیعلامت صحيح ) 0x1 << 1 )  /* (DBGU) TXRDY Interrupt */
#تعریف_کن AT91C_US_ENDRX                 ( ( بیعلامت صحيح ) 0x1 << 3 )  /* (DBGU) End of Receive Transfer Interrupt */
#تعریف_کن AT91C_US_ENDTX                 ( ( بیعلامت صحيح ) 0x1 << 4 )  /* (DBGU) End of Transmit Interrupt */
#تعریف_کن AT91C_US_OVRE                  ( ( بیعلامت صحيح ) 0x1 << 5 )  /* (DBGU) Overrun Interrupt */
#تعریف_کن AT91_C_US_قاب                 ( ( بیعلامت صحيح ) 0x1 << 6 )  /* (DBGU) Framing Error Interrupt */
#تعریف_کن AT91C_US_PARE                  ( ( بیعلامت صحيح ) 0x1 << 7 )  /* (DBGU) Parity Error Interrupt */
#تعریف_کن AT91C_US_TXEMPTY               ( ( بیعلامت صحيح ) 0x1 << 9 )  /* (DBGU) TXEMPTY Interrupt */
#تعریف_کن AT91C_US_TXBUFE                ( ( بیعلامت صحيح ) 0x1 << 11 ) /* (DBGU) TXBUFE Interrupt */
#تعریف_کن AT91C_US_RXBUFF                ( ( بیعلامت صحيح ) 0x1 << 12 ) /* (DBGU) RXBUFF Interrupt */
#تعریف_کن AT91C_US_COMM_TX               ( ( بیعلامت صحيح ) 0x1 << 30 ) /* (DBGU) COMM_TX Interrupt */
#تعریف_کن AT91C_US_COMM_RX               ( ( بیعلامت صحيح ) 0x1 << 31 ) /* (DBGU) COMM_RX Interrupt */
/* -------- DBGU_IDR : (DBGU Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* -------- DBGU_IMR : (DBGU Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* -------- DBGU_CSR : (DBGU Offset: 0x14) Debug Unit Channel Status Register -------- */
/* -------- DBGU_FNTR : (DBGU Offset: 0x48) Debug Unit FORCE_NTRST Register -------- */
#تعریف_کن AT91C_US_FORCE_NTRST    ( ( بیعلامت صحيح ) 0x1 << 0 ) /* (DBGU) Force NTRST in JTAG */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Parallel Input Output Controller */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_PIO
{
    AT91_REG PIO_در_هر;        /* PIO Enable Register */
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
#تعریف_کن AT91C_CKGR_MOSCEN            ( ( بیعلامت صحيح ) 0x1 << 0 )    /* (CKGR) Main Oscillator Enable */
#تعریف_کن AT91C_CKGR_OSCBYPASS         ( ( بیعلامت صحيح ) 0x1 << 1 )    /* (CKGR) Main Oscillator Bypass */
#تعریف_کن AT91C_CKGR_OSCOUNT           ( ( بیعلامت صحيح ) 0xFF << 8 )   /* (CKGR) Main Oscillator Start-up Time */
/* -------- CKGR_MCFR : (CKGR Offset: 0x4) Main Clock Frequency Register -------- */
#تعریف_کن AT91C_CKGR_MAINF             ( ( بیعلامت صحيح ) 0xFFFF << 0 ) /* (CKGR) Main Clock Frequency */
#تعریف_کن AT91C_CKGR_MAINRDY           ( ( بیعلامت صحيح ) 0x1 << 16 )   /* (CKGR) Main Clock Ready */
/* -------- CKGR_PLLR : (CKGR Offset: 0xc) PLL B Register -------- */
#تعریف_کن AT91C_CKGR_DIV               ( ( بیعلامت صحيح ) 0xFF << 0 )   /* (CKGR) Divider Selected */
#تعریف_کن     AT91C_CKGR_DIV_0         ( ( بیعلامت صحيح ) 0x0 )         /* (CKGR) Divider output is 0 */
#تعریف_کن     AT91C_CKGR_DIV_BYPASS    ( ( بیعلامت صحيح ) 0x1 )         /* (CKGR) Divider is bypassed */
#تعریف_کن AT91C_CKGR_PLLCOUNT          ( ( بیعلامت صحيح ) 0x3F << 8 )   /* (CKGR) PLL Counter */
#تعریف_کن AT91_C_CKGR_بیرون               ( ( بیعلامت صحيح ) 0x3 << 14 )   /* (CKGR) PLL Output Frequency Range */
#تعریف_کن     AT91_C_CKGR_بیرون_0         ( ( بیعلامت صحيح ) 0x0 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#تعریف_کن     AT91_C_CKGR_بیرون_1         ( ( بیعلامت صحيح ) 0x1 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#تعریف_کن     AT91_C_CKGR_بیرون_2         ( ( بیعلامت صحيح ) 0x2 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#تعریف_کن     AT91_C_CKGR_بیرون_3         ( ( بیعلامت صحيح ) 0x3 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#تعریف_کن AT91C_CKGR_MUL               ( ( بیعلامت صحيح ) 0x7FF << 16 ) /* (CKGR) PLL Multiplier */
#تعریف_کن AT91C_CKGR_USBDIV            ( ( بیعلامت صحيح ) 0x3 << 28 )   /* (CKGR) Divider for USB Clocks */
#تعریف_کن     AT91C_CKGR_USBDIV_0      ( ( بیعلامت صحيح ) 0x0 << 28 )   /* (CKGR) Divider output is PLL clock output */
#تعریف_کن     AT91C_CKGR_USBDIV_1      ( ( بیعلامت صحيح ) 0x1 << 28 )   /* (CKGR) Divider output is PLL clock output divided by 2 */
#تعریف_کن     AT91C_CKGR_USBDIV_2      ( ( بیعلامت صحيح ) 0x2 << 28 )   /* (CKGR) Divider output is PLL clock output divided by 4 */

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
#تعریف_کن AT91C_PMC_PCK     ( ( بیعلامت صحيح ) 0x1 << 0 )  /* (PMC) Processor Clock */
#تعریف_کن AT91C_PMC_UDP     ( ( بیعلامت صحيح ) 0x1 << 7 )  /* (PMC) USB Device Port Clock */
#تعریف_کن AT91C_PMC_PCK0    ( ( بیعلامت صحيح ) 0x1 << 8 )  /* (PMC) Programmable Clock Output */
#تعریف_کن AT91C_PMC_PCK1    ( ( بیعلامت صحيح ) 0x1 << 9 )  /* (PMC) Programmable Clock Output */
#تعریف_کن AT91C_PMC_PCK2    ( ( بیعلامت صحيح ) 0x1 << 10 ) /* (PMC) Programmable Clock Output */
#تعریف_کن AT91C_PMC_PCK3    ( ( بیعلامت صحيح ) 0x1 << 11 ) /* (PMC) Programmable Clock Output */
/* -------- PMC_SCDR : (PMC Offset: 0x4) System Clock Disable Register -------- */
/* -------- PMC_SCSR : (PMC Offset: 0x8) System Clock Status Register -------- */
/* -------- CKGR_MOR : (PMC Offset: 0x20) Main Oscillator Register -------- */
/* -------- CKGR_MCFR : (PMC Offset: 0x24) Main Clock Frequency Register -------- */
/* -------- CKGR_PLLR : (PMC Offset: 0x2c) PLL B Register -------- */
/* -------- PMC_MCKR : (PMC Offset: 0x30) Master Clock Register -------- */
#تعریف_کن AT91C_PMC_CSS                 ( ( بیعلامت صحيح ) 0x3 << 0 ) /* (PMC) Programmable Clock Selection */
#تعریف_کن     AT91C_PMC_CSS_SLOW_CLK    ( ( بیعلامت صحيح ) 0x0 )      /* (PMC) Slow Clock is selected */
#تعریف_کن     AT91C_PMC_CSS_MAIN_CLK    ( ( بیعلامت صحيح ) 0x1 )      /* (PMC) Main Clock is selected */
#تعریف_کن     AT91C_PMC_CSS_PLL_CLK     ( ( بیعلامت صحيح ) 0x3 )      /* (PMC) Clock from PLL is selected */
#تعریف_کن AT91C_PMC_PRES                ( ( بیعلامت صحيح ) 0x7 << 2 ) /* (PMC) Programmable Clock Prescaler */
#تعریف_کن     AT91C_PMC_PRES_CLK        ( ( بیعلامت صحيح ) 0x0 << 2 ) /* (PMC) Selected clock */
#تعریف_کن     AT91C_PMC_PRES_CLK_2      ( ( بیعلامت صحيح ) 0x1 << 2 ) /* (PMC) Selected clock divided by 2 */
#تعریف_کن     AT91C_PMC_PRES_CLK_4      ( ( بیعلامت صحيح ) 0x2 << 2 ) /* (PMC) Selected clock divided by 4 */
#تعریف_کن     AT91C_PMC_PRES_CLK_8      ( ( بیعلامت صحيح ) 0x3 << 2 ) /* (PMC) Selected clock divided by 8 */
#تعریف_کن     AT91C_PMC_PRES_CLK_16     ( ( بیعلامت صحيح ) 0x4 << 2 ) /* (PMC) Selected clock divided by 16 */
#تعریف_کن     AT91C_PMC_PRES_CLK_32     ( ( بیعلامت صحيح ) 0x5 << 2 ) /* (PMC) Selected clock divided by 32 */
#تعریف_کن     AT91C_PMC_PRES_CLK_64     ( ( بیعلامت صحيح ) 0x6 << 2 ) /* (PMC) Selected clock divided by 64 */
/* -------- PMC_PCKR : (PMC Offset: 0x40) Programmable Clock Register -------- */
/* -------- PMC_IER : (PMC Offset: 0x60) PMC Interrupt Enable Register -------- */
#تعریف_کن AT91C_PMC_MOSCS               ( ( بیعلامت صحيح ) 0x1 << 0 )  /* (PMC) MOSC Status/Enable/Disable/Mask */
#تعریف_کن AT91_C_PMC_قفل                ( ( بیعلامت صحيح ) 0x1 << 2 )  /* (PMC) PLL Status/Enable/Disable/Mask */
#تعریف_کن AT91C_PMC_MCKRDY              ( ( بیعلامت صحيح ) 0x1 << 3 )  /* (PMC) MCK_RDY Status/Enable/Disable/Mask */
#تعریف_کن AT91C_PMC_PCK0RDY             ( ( بیعلامت صحيح ) 0x1 << 8 )  /* (PMC) PCK0_RDY Status/Enable/Disable/Mask */
#تعریف_کن AT91C_PMC_PCK1RDY             ( ( بیعلامت صحيح ) 0x1 << 9 )  /* (PMC) PCK1_RDY Status/Enable/Disable/Mask */
#تعریف_کن AT91C_PMC_PCK2RDY             ( ( بیعلامت صحيح ) 0x1 << 10 ) /* (PMC) PCK2_RDY Status/Enable/Disable/Mask */
#تعریف_کن AT91C_PMC_PCK3RDY             ( ( بیعلامت صحيح ) 0x1 << 11 ) /* (PMC) PCK3_RDY Status/Enable/Disable/Mask */
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
#تعریف_کن AT91C_RSTC_PROCRST                ( ( بیعلامت صحيح ) 0x1 << 0 )   /* (RSTC) Processor Reset */
#تعریف_کن AT91C_RSTC_PERRST                 ( ( بیعلامت صحيح ) 0x1 << 2 )   /* (RSTC) Peripheral Reset */
#تعریف_کن AT91C_RSTC_EXTRST                 ( ( بیعلامت صحيح ) 0x1 << 3 )   /* (RSTC) External Reset */
#تعریف_کن AT91_C_RSTC_کلید                    ( ( بیعلامت صحيح ) 0xFF << 24 ) /* (RSTC) Password */
/* -------- RSTC_RSR : (RSTC Offset: 0x4) Reset Status Register -------- */
#تعریف_کن AT91C_RSTC_URSTS                  ( ( بیعلامت صحيح ) 0x1 << 0 )   /* (RSTC) User Reset Status */
#تعریف_کن AT91C_RSTC_BODSTS                 ( ( بیعلامت صحيح ) 0x1 << 1 )   /* (RSTC) Brownout Detection Status */
#تعریف_کن AT91C_RSTC_RSTTYP                 ( ( بیعلامت صحيح ) 0x7 << 8 )   /* (RSTC) Reset Type */
#تعریف_کن     AT91C_RSTC_RSTTYP_POWERUP     ( ( بیعلامت صحيح ) 0x0 << 8 )   /* (RSTC) Power-up Reset. VDDCORE rising. */
#تعریف_کن     AT91C_RSTC_RSTTYP_WAKEUP      ( ( بیعلامت صحيح ) 0x1 << 8 )   /* (RSTC) WakeUp Reset. VDDCORE rising. */
#تعریف_کن     AT91C_RSTC_RSTTYP_WATCHDOG    ( ( بیعلامت صحيح ) 0x2 << 8 )   /* (RSTC) Watchdog Reset. Watchdog overflow occurred. */
#تعریف_کن     AT91C_RSTC_RSTTYP_SOFTWARE    ( ( بیعلامت صحيح ) 0x3 << 8 )   /* (RSTC) Software Reset. Processor reset required by the software. */
#تعریف_کن     AT91C_RSTC_RSTTYP_USER        ( ( بیعلامت صحيح ) 0x4 << 8 )   /* (RSTC) User Reset. NRST pin detected low. */
#تعریف_کن     AT91C_RSTC_RSTTYP_BROWNOUT    ( ( بیعلامت صحيح ) 0x5 << 8 )   /* (RSTC) Brownout Reset occurred. */
#تعریف_کن AT91C_RSTC_NRSTL                  ( ( بیعلامت صحيح ) 0x1 << 16 )  /* (RSTC) NRST pin level */
#تعریف_کن AT91C_RSTC_SRCMP                  ( ( بیعلامت صحيح ) 0x1 << 17 )  /* (RSTC) Software Reset Command in Progress. */
/* -------- RSTC_RMR : (RSTC Offset: 0x8) Reset Mode Register -------- */
#تعریف_کن AT91C_RSTC_URSTEN                 ( ( بیعلامت صحيح ) 0x1 << 0 )   /* (RSTC) User Reset Enable */
#تعریف_کن AT91C_RSTC_URSTIEN                ( ( بیعلامت صحيح ) 0x1 << 4 )   /* (RSTC) User Reset Interrupt Enable */
#تعریف_کن AT91C_RSTC_ERSTL                  ( ( بیعلامت صحيح ) 0xF << 8 )   /* (RSTC) User Reset Enable */
#تعریف_کن AT91C_RSTC_BODIEN                 ( ( بیعلامت صحيح ) 0x1 << 16 )  /* (RSTC) Brownout Detection Interrupt Enable */

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
#تعریف_کن AT91C_RTTC_RTPRES       ( ( بیعلامت صحيح ) 0xFFFF << 0 ) /* (RTTC) Real-time Timer Prescaler Value */
#تعریف_کن AT91C_RTTC_ALMIEN       ( ( بیعلامت صحيح ) 0x1 << 16 )   /* (RTTC) Alarm Interrupt Enable */
#تعریف_کن AT91C_RTTC_RTTINCIEN    ( ( بیعلامت صحيح ) 0x1 << 17 )   /* (RTTC) Real Time Timer Increment Interrupt Enable */
#تعریف_کن AT91C_RTTC_RTTRST       ( ( بیعلامت صحيح ) 0x1 << 18 )   /* (RTTC) Real Time Timer Restart */
/* -------- RTTC_RTAR : (RTTC Offset: 0x4) Real-time Alarm Register -------- */
#تعریف_کن AT91C_RTTC_ALMV         ( ( بیعلامت صحيح ) 0x0 << 0 )    /* (RTTC) Alarm Value */
/* -------- RTTC_RTVR : (RTTC Offset: 0x8) Current Real-time Value Register -------- */
#تعریف_کن AT91C_RTTC_CRTV         ( ( بیعلامت صحيح ) 0x0 << 0 )    /* (RTTC) Current Real-time Value */
/* -------- RTTC_RTSR : (RTTC Offset: 0xc) Real-time Status Register -------- */
#تعریف_کن AT91C_RTTC_ALMS         ( ( بیعلامت صحيح ) 0x1 << 0 )    /* (RTTC) Real-time Alarm Status */
#تعریف_کن AT91C_RTTC_RTTINC       ( ( بیعلامت صحيح ) 0x1 << 1 )    /* (RTTC) Real-time Timer Increment */

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
#تعریف_کن AT91C_PITC_PIV       ( ( بیعلامت صحيح ) 0xFFFFF << 0 ) /* (PITC) Periodic Interval Value */
#تعریف_کن AT91C_PITC_PITEN     ( ( بیعلامت صحيح ) 0x1 << 24 )    /* (PITC) Periodic Interval Timer Enabled */
#تعریف_کن AT91C_PITC_PITIEN    ( ( بیعلامت صحيح ) 0x1 << 25 )    /* (PITC) Periodic Interval Timer Interrupt Enable */
/* -------- PITC_PISR : (PITC Offset: 0x4) Periodic Interval Status Register -------- */
#تعریف_کن AT91C_PITC_PITS      ( ( بیعلامت صحيح ) 0x1 << 0 )     /* (PITC) Periodic Interval Timer Status */
/* -------- PITC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register -------- */
#تعریف_کن AT91C_PITC_CPIV      ( ( بیعلامت صحيح ) 0xFFFFF << 0 ) /* (PITC) Current Periodic Interval Value */
#تعریف_کن AT91C_PITC_PICNT     ( ( بیعلامت صحيح ) 0xFFF << 20 )  /* (PITC) Periodic Interval Counter */
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
#تعریف_کن AT91C_WDTC_WDRSTT       ( ( بیعلامت صحيح ) 0x1 << 0 )    /* (WDTC) Watchdog Restart */
#تعریف_کن AT91_C_WDTC_کلید          ( ( بیعلامت صحيح ) 0xFF << 24 )  /* (WDTC) Watchdog KEY Password */
/* -------- WDTC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register -------- */
#تعریف_کن AT91C_WDTC_WDV          ( ( بیعلامت صحيح ) 0xFFF << 0 )  /* (WDTC) Watchdog Timer Restart */
#تعریف_کن AT91C_WDTC_WDFIEN       ( ( بیعلامت صحيح ) 0x1 << 12 )   /* (WDTC) Watchdog Fault Interrupt Enable */
#تعریف_کن AT91C_WDTC_WDRSTEN      ( ( بیعلامت صحيح ) 0x1 << 13 )   /* (WDTC) Watchdog Reset Enable */
#تعریف_کن AT91C_WDTC_WDRPROC      ( ( بیعلامت صحيح ) 0x1 << 14 )   /* (WDTC) Watchdog Timer Restart */
#تعریف_کن AT91C_WDTC_WDDIS        ( ( بیعلامت صحيح ) 0x1 << 15 )   /* (WDTC) Watchdog Disable */
#تعریف_کن AT91C_WDTC_WDD          ( ( بیعلامت صحيح ) 0xFFF << 16 ) /* (WDTC) Watchdog Delta Value */
#تعریف_کن AT91C_WDTC_WDDBGHLT     ( ( بیعلامت صحيح ) 0x1 << 28 )   /* (WDTC) Watchdog Debug Halt */
#تعریف_کن AT91C_WDTC_WDIDLEHLT    ( ( بیعلامت صحيح ) 0x1 << 29 )   /* (WDTC) Watchdog Idle Halt */
/* -------- WDTC_WDSR : (WDTC Offset: 0x8) Watchdog Status Register -------- */
#تعریف_کن AT91C_WDTC_WDUNF        ( ( بیعلامت صحيح ) 0x1 << 0 )    /* (WDTC) Watchdog Underflow */
#تعریف_کن AT91C_WDTC_WDERR        ( ( بیعلامت صحيح ) 0x1 << 1 )    /* (WDTC) Watchdog Error */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Voltage Regulator Mode Controller Interface */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_VREG
{
    AT91_REG VREG_MR; /* Voltage Regulator Mode Register */
} AT91S_VREG, * AT91PS_VREG;

/* -------- VREG_MR : (VREG Offset: 0x0) Voltage Regulator Mode Register -------- */
#تعریف_کن AT91C_VREG_PSTDBY    ( ( بیعلامت صحيح ) 0x1 << 0 ) /* (VREG) Voltage Regulator Power Standby Mode */

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
#تعریف_کن AT91C_MC_RCB                       ( ( بیعلامت صحيح ) 0x1 << 0 )   /* (MC) Remap Command Bit */
/* -------- MC_ASR : (MC Offset: 0x4) MC Abort Status Register -------- */
#تعریف_کن AT91C_MC_UNDADD                    ( ( بیعلامت صحيح ) 0x1 << 0 )   /* (MC) Undefined Address Abort Status */
#تعریف_کن AT91C_MC_MISADD                    ( ( بیعلامت صحيح ) 0x1 << 1 )   /* (MC) Misaligned Address Abort Status */
#تعریف_کن AT91C_MC_ABTSZ                     ( ( بیعلامت صحيح ) 0x3 << 8 )   /* (MC) Abort Size Status */
#تعریف_کن     AT91C_MC_ABTSZ_BYTE            ( ( بیعلامت صحيح ) 0x0 << 8 )   /* (MC) Byte */
#تعریف_کن     AT91C_MC_ABTSZ_HWORD           ( ( بیعلامت صحيح ) 0x1 << 8 )   /* (MC) Half-word */
#تعریف_کن     AT91_C_MC_ABTSZ_کلمه            ( ( بیعلامت صحيح ) 0x2 << 8 )   /* (MC) Word */
#تعریف_کن AT91C_MC_ABTTYP                    ( ( بیعلامت صحيح ) 0x3 << 10 )  /* (MC) Abort Type Status */
#تعریف_کن     AT91C_MC_ABTTYP_DATAR          ( ( بیعلامت صحيح ) 0x0 << 10 )  /* (MC) Data Read */
#تعریف_کن     AT91C_MC_ABTTYP_DATAW          ( ( بیعلامت صحيح ) 0x1 << 10 )  /* (MC) Data Write */
#تعریف_کن     AT91C_MC_ABTTYP_FETCH          ( ( بیعلامت صحيح ) 0x2 << 10 )  /* (MC) Code Fetch */
#تعریف_کن AT91C_MC_MST0                      ( ( بیعلامت صحيح ) 0x1 << 16 )  /* (MC) Master 0 Abort Source */
#تعریف_کن AT91C_MC_MST1                      ( ( بیعلامت صحيح ) 0x1 << 17 )  /* (MC) Master 1 Abort Source */
#تعریف_کن AT91C_MC_SVMST0                    ( ( بیعلامت صحيح ) 0x1 << 24 )  /* (MC) Saved Master 0 Abort Source */
#تعریف_کن AT91C_MC_SVMST1                    ( ( بیعلامت صحيح ) 0x1 << 25 )  /* (MC) Saved Master 1 Abort Source */
/* -------- MC_FMR : (MC Offset: 0x60) MC Flash Mode Register -------- */
#تعریف_کن AT91C_MC_FRDY                      ( ( بیعلامت صحيح ) 0x1 << 0 )   /* (MC) Flash Ready */
#تعریف_کن AT91C_MC_LOCKE                     ( ( بیعلامت صحيح ) 0x1 << 2 )   /* (MC) Lock Error */
#تعریف_کن AT91C_MC_PROGE                     ( ( بیعلامت صحيح ) 0x1 << 3 )   /* (MC) Programming Error */
#تعریف_کن AT91C_MC_NEBP                      ( ( بیعلامت صحيح ) 0x1 << 7 )   /* (MC) No Erase Before Programming */
#تعریف_کن AT91C_MC_FWS                       ( ( بیعلامت صحيح ) 0x3 << 8 )   /* (MC) Flash Wait State */
#تعریف_کن     AT91C_MC_FWS_0FWS              ( ( بیعلامت صحيح ) 0x0 << 8 )   /* (MC) 1 cycle for Read, 2 for Write operations */
#تعریف_کن     AT91C_MC_FWS_1FWS              ( ( بیعلامت صحيح ) 0x1 << 8 )   /* (MC) 2 cycles for Read, 3 for Write operations */
#تعریف_کن     AT91C_MC_FWS_2FWS              ( ( بیعلامت صحيح ) 0x2 << 8 )   /* (MC) 3 cycles for Read, 4 for Write operations */
#تعریف_کن     AT91C_MC_FWS_3FWS              ( ( بیعلامت صحيح ) 0x3 << 8 )   /* (MC) 4 cycles for Read, 4 for Write operations */
#تعریف_کن AT91C_MC_FMCN                      ( ( بیعلامت صحيح ) 0xFF << 16 ) /* (MC) Flash Microsecond Cycle Number */
/* -------- MC_FCR : (MC Offset: 0x64) MC Flash Command Register -------- */
#تعریف_کن AT91C_MC_FCMD                      ( ( بیعلامت صحيح ) 0xF << 0 )   /* (MC) Flash Command */
#تعریف_کن     AT91_C_MC_FCMD_شروع_PROG       ( ( بیعلامت صحيح ) 0x1 )        /* (MC) Starts the programming of th epage specified by PAGEN. */
#تعریف_کن     AT91_C_MC_FCMD_قفل             ( ( بیعلامت صحيح ) 0x2 )        /* (MC) Starts a lock sequence of the sector defined by the bits 4 to 7 of the field PAGEN. */
#تعریف_کن     AT91_C_MC_FCMD_PROG_AND_قفل    ( ( بیعلامت صحيح ) 0x3 )        /* (MC) The lock sequence automatically happens after the programming sequence is completed. */
#تعریف_کن     AT91C_MC_FCMD_UNLOCK           ( ( بیعلامت صحيح ) 0x4 )        /* (MC) Starts an unlock sequence of the sector defined by the bits 4 to 7 of the field PAGEN. */
#تعریف_کن     AT91C_MC_FCMD_ERASE_ALL        ( ( بیعلامت صحيح ) 0x8 )        /* (MC) Starts the erase of the entire flash.If at least a page is locked, the command is cancelled. */
#تعریف_کن     AT91_C_MC_FCMD_مجموعه_GP_NVM       ( ( بیعلامت صحيح ) 0xB )        /* (MC) Set General Purpose NVM bits. */
#تعریف_کن     AT91C_MC_FCMD_CLR_GP_NVM       ( ( بیعلامت صحيح ) 0xD )        /* (MC) Clear General Purpose NVM bits. */
#تعریف_کن     AT91_C_MC_FCMD_مجموعه_SECURITY     ( ( بیعلامت صحيح ) 0xF )        /* (MC) Set Security Bit. */
#تعریف_کن AT91C_MC_PAGEN                     ( ( بیعلامت صحيح ) 0x3FF << 8 ) /* (MC) Page Number */
#تعریف_کن AT91_C_MC_کلید                       ( ( بیعلامت صحيح ) 0xFF << 24 ) /* (MC) Writing Protect Key */
/* -------- MC_FSR : (MC Offset: 0x68) MC Flash Command Register -------- */
#تعریف_کن AT91C_MC_SECURITY                  ( ( بیعلامت صحيح ) 0x1 << 4 )   /* (MC) Security Bit Status */
#تعریف_کن AT91C_MC_GPNVM0                    ( ( بیعلامت صحيح ) 0x1 << 8 )   /* (MC) Sector 0 Lock Status */
#تعریف_کن AT91C_MC_GPNVM1                    ( ( بیعلامت صحيح ) 0x1 << 9 )   /* (MC) Sector 1 Lock Status */
#تعریف_کن AT91C_MC_GPNVM2                    ( ( بیعلامت صحيح ) 0x1 << 10 )  /* (MC) Sector 2 Lock Status */
#تعریف_کن AT91C_MC_GPNVM3                    ( ( بیعلامت صحيح ) 0x1 << 11 )  /* (MC) Sector 3 Lock Status */
#تعریف_کن AT91C_MC_GPNVM4                    ( ( بیعلامت صحيح ) 0x1 << 12 )  /* (MC) Sector 4 Lock Status */
#تعریف_کن AT91C_MC_GPNVM5                    ( ( بیعلامت صحيح ) 0x1 << 13 )  /* (MC) Sector 5 Lock Status */
#تعریف_کن AT91C_MC_GPNVM6                    ( ( بیعلامت صحيح ) 0x1 << 14 )  /* (MC) Sector 6 Lock Status */
#تعریف_کن AT91C_MC_GPNVM7                    ( ( بیعلامت صحيح ) 0x1 << 15 )  /* (MC) Sector 7 Lock Status */
#تعریف_کن AT91C_MC_LOCKS0                    ( ( بیعلامت صحيح ) 0x1 << 16 )  /* (MC) Sector 0 Lock Status */
#تعریف_کن AT91C_MC_LOCKS1                    ( ( بیعلامت صحيح ) 0x1 << 17 )  /* (MC) Sector 1 Lock Status */
#تعریف_کن AT91C_MC_LOCKS2                    ( ( بیعلامت صحيح ) 0x1 << 18 )  /* (MC) Sector 2 Lock Status */
#تعریف_کن AT91C_MC_LOCKS3                    ( ( بیعلامت صحيح ) 0x1 << 19 )  /* (MC) Sector 3 Lock Status */
#تعریف_کن AT91C_MC_LOCKS4                    ( ( بیعلامت صحيح ) 0x1 << 20 )  /* (MC) Sector 4 Lock Status */
#تعریف_کن AT91C_MC_LOCKS5                    ( ( بیعلامت صحيح ) 0x1 << 21 )  /* (MC) Sector 5 Lock Status */
#تعریف_کن AT91C_MC_LOCKS6                    ( ( بیعلامت صحيح ) 0x1 << 22 )  /* (MC) Sector 6 Lock Status */
#تعریف_کن AT91C_MC_LOCKS7                    ( ( بیعلامت صحيح ) 0x1 << 23 )  /* (MC) Sector 7 Lock Status */
#تعریف_کن AT91C_MC_LOCKS8                    ( ( بیعلامت صحيح ) 0x1 << 24 )  /* (MC) Sector 8 Lock Status */
#تعریف_کن AT91C_MC_LOCKS9                    ( ( بیعلامت صحيح ) 0x1 << 25 )  /* (MC) Sector 9 Lock Status */
#تعریف_کن AT91C_MC_LOCKS10                   ( ( بیعلامت صحيح ) 0x1 << 26 )  /* (MC) Sector 10 Lock Status */
#تعریف_کن AT91C_MC_LOCKS11                   ( ( بیعلامت صحيح ) 0x1 << 27 )  /* (MC) Sector 11 Lock Status */
#تعریف_کن AT91C_MC_LOCKS12                   ( ( بیعلامت صحيح ) 0x1 << 28 )  /* (MC) Sector 12 Lock Status */
#تعریف_کن AT91C_MC_LOCKS13                   ( ( بیعلامت صحيح ) 0x1 << 29 )  /* (MC) Sector 13 Lock Status */
#تعریف_کن AT91C_MC_LOCKS14                   ( ( بیعلامت صحيح ) 0x1 << 30 )  /* (MC) Sector 14 Lock Status */
#تعریف_کن AT91C_MC_LOCKS15                   ( ( بیعلامت صحيح ) 0x1 << 31 )  /* (MC) Sector 15 Lock Status */

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
#تعریف_کن AT91C_SPI_SPIEN              ( ( بیعلامت صحيح ) 0x1 << 0 )    /* (SPI) SPI Enable */
#تعریف_کن AT91C_SPI_SPIDIS             ( ( بیعلامت صحيح ) 0x1 << 1 )    /* (SPI) SPI Disable */
#تعریف_کن AT91C_SPI_SWRST              ( ( بیعلامت صحيح ) 0x1 << 7 )    /* (SPI) SPI Software reset */
#تعریف_کن AT91C_SPI_LASTXFER           ( ( بیعلامت صحيح ) 0x1 << 24 )   /* (SPI) SPI Last Transfer */
/* -------- SPI_MR : (SPI Offset: 0x4) SPI Mode Register -------- */
#تعریف_کن AT91C_SPI_MSTR               ( ( بیعلامت صحيح ) 0x1 << 0 )    /* (SPI) Master/Slave Mode */
#تعریف_کن AT91C_SPI_PS                 ( ( بیعلامت صحيح ) 0x1 << 1 )    /* (SPI) Peripheral Select */
#تعریف_کن     AT91C_SPI_PS_FIXED       ( ( بیعلامت صحيح ) 0x0 << 1 )    /* (SPI) Fixed Peripheral Select */
#تعریف_کن     AT91C_SPI_PS_VARIABLE    ( ( بیعلامت صحيح ) 0x1 << 1 )    /* (SPI) Variable Peripheral Select */
#تعریف_کن AT91C_SPI_PCSDEC             ( ( بیعلامت صحيح ) 0x1 << 2 )    /* (SPI) Chip Select Decode */
#تعریف_کن AT91C_SPI_FDIV               ( ( بیعلامت صحيح ) 0x1 << 3 )    /* (SPI) Clock Selection */
#تعریف_کن AT91C_SPI_MODFDIS            ( ( بیعلامت صحيح ) 0x1 << 4 )    /* (SPI) Mode Fault Detection */
#تعریف_کن AT91C_SPI_LLB                ( ( بیعلامت صحيح ) 0x1 << 7 )    /* (SPI) Clock Selection */
#تعریف_کن AT91C_SPI_PCS                ( ( بیعلامت صحيح ) 0xF << 16 )   /* (SPI) Peripheral Chip Select */
#تعریف_کن AT91C_SPI_DLYBCS             ( ( بیعلامت صحيح ) 0xFF << 24 )  /* (SPI) Delay Between Chip Selects */
/* -------- SPI_RDR : (SPI Offset: 0x8) Receive Data Register -------- */
#تعریف_کن AT91C_SPI_RD                 ( ( بیعلامت صحيح ) 0xFFFF << 0 ) /* (SPI) Receive Data */
#تعریف_کن AT91C_SPI_RPCS               ( ( بیعلامت صحيح ) 0xF << 16 )   /* (SPI) Peripheral Chip Select Status */
/* -------- SPI_TDR : (SPI Offset: 0xc) Transmit Data Register -------- */
#تعریف_کن AT91C_SPI_TD                 ( ( بیعلامت صحيح ) 0xFFFF << 0 ) /* (SPI) Transmit Data */
#تعریف_کن AT91C_SPI_TPCS               ( ( بیعلامت صحيح ) 0xF << 16 )   /* (SPI) Peripheral Chip Select Status */
/* -------- SPI_SR : (SPI Offset: 0x10) Status Register -------- */
#تعریف_کن AT91C_SPI_RDRF               ( ( بیعلامت صحيح ) 0x1 << 0 )    /* (SPI) Receive Data Register Full */
#تعریف_کن AT91C_SPI_TDRE               ( ( بیعلامت صحيح ) 0x1 << 1 )    /* (SPI) Transmit Data Register Empty */
#تعریف_کن AT91C_SPI_MODF               ( ( بیعلامت صحيح ) 0x1 << 2 )    /* (SPI) Mode Fault Error */
#تعریف_کن AT91C_SPI_OVRES              ( ( بیعلامت صحيح ) 0x1 << 3 )    /* (SPI) Overrun Error Status */
#تعریف_کن AT91C_SPI_ENDRX              ( ( بیعلامت صحيح ) 0x1 << 4 )    /* (SPI) End of Receiver Transfer */
#تعریف_کن AT91C_SPI_ENDTX              ( ( بیعلامت صحيح ) 0x1 << 5 )    /* (SPI) End of Receiver Transfer */
#تعریف_کن AT91C_SPI_RXBUFF             ( ( بیعلامت صحيح ) 0x1 << 6 )    /* (SPI) RXBUFF Interrupt */
#تعریف_کن AT91C_SPI_TXBUFE             ( ( بیعلامت صحيح ) 0x1 << 7 )    /* (SPI) TXBUFE Interrupt */
#تعریف_کن AT91C_SPI_NSSR               ( ( بیعلامت صحيح ) 0x1 << 8 )    /* (SPI) NSSR Interrupt */
#تعریف_کن AT91C_SPI_TXEMPTY            ( ( بیعلامت صحيح ) 0x1 << 9 )    /* (SPI) TXEMPTY Interrupt */
#تعریف_کن AT91C_SPI_SPIENS             ( ( بیعلامت صحيح ) 0x1 << 16 )   /* (SPI) Enable Status */
/* -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- */
/* -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- */
/* -------- SPI_IMR : (SPI Offset: 0x1c) Interrupt Mask Register -------- */
/* -------- SPI_CSR : (SPI Offset: 0x30) Chip Select Register -------- */
#تعریف_کن AT91C_SPI_CPOL           ( ( بیعلامت صحيح ) 0x1 << 0 )   /* (SPI) Clock Polarity */
#تعریف_کن AT91C_SPI_NCPHA          ( ( بیعلامت صحيح ) 0x1 << 1 )   /* (SPI) Clock Phase */
#تعریف_کن AT91C_SPI_CSAAT          ( ( بیعلامت صحيح ) 0x1 << 3 )   /* (SPI) Chip Select Active After Transfer */
#تعریف_کن AT91_C_SPI_بیتها           ( ( بیعلامت صحيح ) 0xF << 4 )   /* (SPI) Bits Per Transfer */
#تعریف_کن     AT91_C_SPI_بیتها_8     ( ( بیعلامت صحيح ) 0x0 << 4 )   /* (SPI) 8 Bits Per transfer */
#تعریف_کن     AT91_C_SPI_بیتها_9     ( ( بیعلامت صحيح ) 0x1 << 4 )   /* (SPI) 9 Bits Per transfer */
#تعریف_کن     AT91_C_SPI_بیتها_10    ( ( بیعلامت صحيح ) 0x2 << 4 )   /* (SPI) 10 Bits Per transfer */
#تعریف_کن     AT91_C_SPI_بیتها_11    ( ( بیعلامت صحيح ) 0x3 << 4 )   /* (SPI) 11 Bits Per transfer */
#تعریف_کن     AT91_C_SPI_بیتها_12    ( ( بیعلامت صحيح ) 0x4 << 4 )   /* (SPI) 12 Bits Per transfer */
#تعریف_کن     AT91_C_SPI_بیتها_13    ( ( بیعلامت صحيح ) 0x5 << 4 )   /* (SPI) 13 Bits Per transfer */
#تعریف_کن     AT91_C_SPI_بیتها_14    ( ( بیعلامت صحيح ) 0x6 << 4 )   /* (SPI) 14 Bits Per transfer */
#تعریف_کن     AT91_C_SPI_بیتها_15    ( ( بیعلامت صحيح ) 0x7 << 4 )   /* (SPI) 15 Bits Per transfer */
#تعریف_کن     AT91_C_SPI_بیتها_16    ( ( بیعلامت صحيح ) 0x8 << 4 )   /* (SPI) 16 Bits Per transfer */
#تعریف_کن AT91C_SPI_SCBR           ( ( بیعلامت صحيح ) 0xFF << 8 )  /* (SPI) Serial Clock Baud Rate */
#تعریف_کن AT91C_SPI_DLYBS          ( ( بیعلامت صحيح ) 0xFF << 16 ) /* (SPI) Delay Before SPCK */
#تعریف_کن AT91C_SPI_DLYBCT         ( ( بیعلامت صحيح ) 0xFF << 24 ) /* (SPI) Delay Between Consecutive Transfers */

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
#تعریف_کن AT91C_US_STTBRK                  ( ( بیعلامت صحيح ) 0x1 << 9 )  /* (USART) Start Break */
#تعریف_کن AT91C_US_STPBRK                  ( ( بیعلامت صحيح ) 0x1 << 10 ) /* (USART) Stop Break */
#تعریف_کن AT91C_US_STTTO                   ( ( بیعلامت صحيح ) 0x1 << 11 ) /* (USART) Start Time-out */
#تعریف_کن AT91C_US_SENDA                   ( ( بیعلامت صحيح ) 0x1 << 12 ) /* (USART) Send Address */
#تعریف_کن AT91C_US_RSTIT                   ( ( بیعلامت صحيح ) 0x1 << 13 ) /* (USART) Reset Iterations */
#تعریف_کن AT91C_US_RSTNACK                 ( ( بیعلامت صحيح ) 0x1 << 14 ) /* (USART) Reset Non Acknowledge */
#تعریف_کن AT91C_US_RETTO                   ( ( بیعلامت صحيح ) 0x1 << 15 ) /* (USART) Rearm Time-out */
#تعریف_کن AT91C_US_DTREN                   ( ( بیعلامت صحيح ) 0x1 << 16 ) /* (USART) Data Terminal ready Enable */
#تعریف_کن AT91C_US_DTRDIS                  ( ( بیعلامت صحيح ) 0x1 << 17 ) /* (USART) Data Terminal ready Disable */
#تعریف_کن AT91C_US_RTSEN                   ( ( بیعلامت صحيح ) 0x1 << 18 ) /* (USART) Request to Send enable */
#تعریف_کن AT91C_US_RTSDIS                  ( ( بیعلامت صحيح ) 0x1 << 19 ) /* (USART) Request to Send Disable */
/* -------- US_MR : (USART Offset: 0x4) Debug Unit Mode Register -------- */
#تعریف_کن AT91C_US_USMODE                  ( ( بیعلامت صحيح ) 0xF << 0 )  /* (USART) Usart mode */
#تعریف_کن     AT91_C_US_USMODE_نرمال       ( ( بیعلامت صحيح ) 0x0 )       /* (USART) Normal */
#تعریف_کن     AT91C_US_USMODE_RS485        ( ( بیعلامت صحيح ) 0x1 )       /* (USART) RS485 */
#تعریف_کن     AT91C_US_USMODE_HWHSH        ( ( بیعلامت صحيح ) 0x2 )       /* (USART) Hardware Handshaking */
#تعریف_کن     AT91C_US_USMODE_MODEM        ( ( بیعلامت صحيح ) 0x3 )       /* (USART) Modem */
#تعریف_کن     AT91C_US_USMODE_ISO7816_0    ( ( بیعلامت صحيح ) 0x4 )       /* (USART) ISO7816 protocol: T = 0 */
#تعریف_کن     AT91C_US_USMODE_ISO7816_1    ( ( بیعلامت صحيح ) 0x6 )       /* (USART) ISO7816 protocol: T = 1 */
#تعریف_کن     AT91C_US_USMODE_IRDA         ( ( بیعلامت صحيح ) 0x8 )       /* (USART) IrDA */
#تعریف_کن     AT91C_US_USMODE_SWHSH        ( ( بیعلامت صحيح ) 0xC )       /* (USART) Software Handshaking */
#تعریف_کن AT91C_US_CLKS                    ( ( بیعلامت صحيح ) 0x3 << 4 )  /* (USART) Clock Selection (Baud Rate generator Input Clock */
#تعریف_کن     AT91C_US_CLKS_CLOCK          ( ( بیعلامت صحيح ) 0x0 << 4 )  /* (USART) Clock */
#تعریف_کن     AT91C_US_CLKS_FDIV1          ( ( بیعلامت صحيح ) 0x1 << 4 )  /* (USART) fdiv1 */
#تعریف_کن     AT91C_US_CLKS_SLOW           ( ( بیعلامت صحيح ) 0x2 << 4 )  /* (USART) slow_clock (ARM) */
#تعریف_کن     AT91C_US_CLKS_EXT            ( ( بیعلامت صحيح ) 0x3 << 4 )  /* (USART) External (SCK) */
#تعریف_کن AT91C_US_CHRL                    ( ( بیعلامت صحيح ) 0x3 << 6 )  /* (USART) Clock Selection (Baud Rate generator Input Clock */
#تعریف_کن     AT91_C_US_CHRL_5_بیتها         ( ( بیعلامت صحيح ) 0x0 << 6 )  /* (USART) Character Length: 5 bits */
#تعریف_کن     AT91_C_US_CHRL_6_بیتها         ( ( بیعلامت صحيح ) 0x1 << 6 )  /* (USART) Character Length: 6 bits */
#تعریف_کن     AT91_C_US_CHRL_7_بیتها         ( ( بیعلامت صحيح ) 0x2 << 6 )  /* (USART) Character Length: 7 bits */
#تعریف_کن     AT91_C_US_CHRL_8_بیتها         ( ( بیعلامت صحيح ) 0x3 << 6 )  /* (USART) Character Length: 8 bits */
#تعریف_کن AT91C_US_SYNC                    ( ( بیعلامت صحيح ) 0x1 << 8 )  /* (USART) Synchronous Mode Select */
#تعریف_کن AT91C_US_NBSTOP                  ( ( بیعلامت صحيح ) 0x3 << 12 ) /* (USART) Number of Stop bits */
#تعریف_کن     AT91_C_US_NBSTOP_1_بیت        ( ( بیعلامت صحيح ) 0x0 << 12 ) /* (USART) 1 stop bit */
#تعریف_کن     AT91_C_US_NBSTOP_15_بیت       ( ( بیعلامت صحيح ) 0x1 << 12 ) /* (USART) Asynchronous (SYNC=0) 2 stop bits Synchronous (SYNC=1) 2 stop bits */
#تعریف_کن     AT91_C_US_NBSTOP_2_بیت        ( ( بیعلامت صحيح ) 0x2 << 12 ) /* (USART) 2 stop bits */
#تعریف_کن AT91C_US_MSBF                    ( ( بیعلامت صحيح ) 0x1 << 16 ) /* (USART) Bit Order */
#تعریف_کن AT91C_US_MODE9                   ( ( بیعلامت صحيح ) 0x1 << 17 ) /* (USART) 9-bit Character length */
#تعریف_کن AT91C_US_CKLO                    ( ( بیعلامت صحيح ) 0x1 << 18 ) /* (USART) Clock Output Select */
#تعریف_کن AT91C_US_OVER                    ( ( بیعلامت صحيح ) 0x1 << 19 ) /* (USART) Over Sampling Mode */
#تعریف_کن AT91C_US_INACK                   ( ( بیعلامت صحيح ) 0x1 << 20 ) /* (USART) Inhibit Non Acknowledge */
#تعریف_کن AT91C_US_DSNACK                  ( ( بیعلامت صحيح ) 0x1 << 21 ) /* (USART) Disable Successive NACK */
#تعریف_کن AT91C_US_MAX_ITER                ( ( بیعلامت صحيح ) 0x1 << 24 ) /* (USART) Number of Repetitions */
#تعریف_کن AT91C_US_FILTER                  ( ( بیعلامت صحيح ) 0x1 << 28 ) /* (USART) Receive Line Filter */
/* -------- US_IER : (USART Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
#تعریف_کن AT91C_US_RXBRK                   ( ( بیعلامت صحيح ) 0x1 << 2 )  /* (USART) Break Received/End of Break */
#تعریف_کن AT91C_US_TIMEOUT                 ( ( بیعلامت صحيح ) 0x1 << 8 )  /* (USART) Receiver Time-out */
#تعریف_کن AT91C_US_ITERATION               ( ( بیعلامت صحيح ) 0x1 << 10 ) /* (USART) Max number of Repetitions Reached */
#تعریف_کن AT91C_US_NACK                    ( ( بیعلامت صحيح ) 0x1 << 13 ) /* (USART) Non Acknowledge */
#تعریف_کن AT91C_US_RIIC                    ( ( بیعلامت صحيح ) 0x1 << 16 ) /* (USART) Ring INdicator Input Change Flag */
#تعریف_کن AT91C_US_DSRIC                   ( ( بیعلامت صحيح ) 0x1 << 17 ) /* (USART) Data Set Ready Input Change Flag */
#تعریف_کن AT91C_US_DCDIC                   ( ( بیعلامت صحيح ) 0x1 << 18 ) /* (USART) Data Carrier Flag */
#تعریف_کن AT91C_US_CTSIC                   ( ( بیعلامت صحيح ) 0x1 << 19 ) /* (USART) Clear To Send Input Change Flag */
/* -------- US_IDR : (USART Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* -------- US_IMR : (USART Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* -------- US_CSR : (USART Offset: 0x14) Debug Unit Channel Status Register -------- */
#تعریف_کن AT91C_US_RI     ( ( بیعلامت صحيح ) 0x1 << 20 )   /* (USART) Image of RI Input */
#تعریف_کن AT91C_US_DSR    ( ( بیعلامت صحيح ) 0x1 << 21 )   /* (USART) Image of DSR Input */
#تعریف_کن AT91C_US_DCD    ( ( بیعلامت صحيح ) 0x1 << 22 )   /* (USART) Image of DCD Input */
#تعریف_کن AT91C_US_CTS    ( ( بیعلامت صحيح ) 0x1 << 23 )   /* (USART) Image of CTS Input */

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
#تعریف_کن AT91C_SSC_RXEN                    ( ( بیعلامت صحيح ) 0x1 << 0 )   /* (SSC) Receive Enable */
#تعریف_کن AT91C_SSC_RXDIS                   ( ( بیعلامت صحيح ) 0x1 << 1 )   /* (SSC) Receive Disable */
#تعریف_کن AT91C_SSC_TXEN                    ( ( بیعلامت صحيح ) 0x1 << 8 )   /* (SSC) Transmit Enable */
#تعریف_کن AT91C_SSC_TXDIS                   ( ( بیعلامت صحيح ) 0x1 << 9 )   /* (SSC) Transmit Disable */
#تعریف_کن AT91C_SSC_SWRST                   ( ( بیعلامت صحيح ) 0x1 << 15 )  /* (SSC) Software Reset */
/* -------- SSC_RCMR : (SSC Offset: 0x10) SSC Receive Clock Mode Register -------- */
#تعریف_کن AT91C_SSC_CKS                     ( ( بیعلامت صحيح ) 0x3 << 0 )   /* (SSC) Receive/Transmit Clock Selection */
#تعریف_کن     AT91C_SSC_CKS_DIV             ( ( بیعلامت صحيح ) 0x0 )        /* (SSC) Divided Clock */
#تعریف_کن     AT91C_SSC_CKS_TK              ( ( بیعلامت صحيح ) 0x1 )        /* (SSC) TK Clock signal */
#تعریف_کن     AT91C_SSC_CKS_RK              ( ( بیعلامت صحيح ) 0x2 )        /* (SSC) RK pin */
#تعریف_کن AT91C_SSC_CKO                     ( ( بیعلامت صحيح ) 0x7 << 2 )   /* (SSC) Receive/Transmit Clock Output Mode Selection */
#تعریف_کن     AT91C_SSC_CKO_NONE            ( ( بیعلامت صحيح ) 0x0 << 2 )   /* (SSC) Receive/Transmit Clock Output Mode: None RK pin: Input-only */
#تعریف_کن     AT91C_SSC_CKO_CONTINUOUS      ( ( بیعلامت صحيح ) 0x1 << 2 )   /* (SSC) Continuous Receive/Transmit Clock RK pin: Output */
#تعریف_کن     AT91_C_SSC_CKO_داده_TX         ( ( بیعلامت صحيح ) 0x2 << 2 )   /* (SSC) Receive/Transmit Clock only during data transfers RK pin: Output */
#تعریف_کن AT91C_SSC_CKI                     ( ( بیعلامت صحيح ) 0x1 << 5 )   /* (SSC) Receive/Transmit Clock Inversion */
#تعریف_کن AT91_C_SSC_شروع                   ( ( بیعلامت صحيح ) 0xF << 8 )   /* (SSC) Receive/Transmit Start Selection */
#تعریف_کن     AT91_C_SSC_شروع_CONTINUOUS    ( ( بیعلامت صحيح ) 0x0 << 8 )   /* (SSC) Continuous, as soon as the receiver is enabled, and immediately after the end of transfer of the previous data. */
#تعریف_کن     AT91_C_SSC_شروع_TX            ( ( بیعلامت صحيح ) 0x1 << 8 )   /* (SSC) Transmit/Receive start */
#تعریف_کن     AT91_C_SSC_شروع_کم_RF        ( ( بیعلامت صحيح ) 0x2 << 8 )   /* (SSC) Detection of a low level on RF input */
#تعریف_کن     AT91_C_SSC_شروع_بالا_RF       ( ( بیعلامت صحيح ) 0x3 << 8 )   /* (SSC) Detection of a high level on RF input */
#تعریف_کن     AT91_C_SSC_شروع_FALL_RF       ( ( بیعلامت صحيح ) 0x4 << 8 )   /* (SSC) Detection of a falling edge on RF input */
#تعریف_کن     AT91_C_SSC_شروع_RISE_RF       ( ( بیعلامت صحيح ) 0x5 << 8 )   /* (SSC) Detection of a rising edge on RF input */
#تعریف_کن     AT91_C_SSC_شروع_LEVEL_RF      ( ( بیعلامت صحيح ) 0x6 << 8 )   /* (SSC) Detection of any level change on RF input */
#تعریف_کن     AT91_C_SSC_شروع_یال_RF       ( ( بیعلامت صحيح ) 0x7 << 8 )   /* (SSC) Detection of any edge on RF input */
#تعریف_کن     AT91_C_SSC_شروع_0             ( ( بیعلامت صحيح ) 0x8 << 8 )   /* (SSC) Compare 0 */
#تعریف_کن AT91C_SSC_STTDLY                  ( ( بیعلامت صحيح ) 0xFF << 16 ) /* (SSC) Receive/Transmit Start Delay */
#تعریف_کن AT91C_SSC_PERIOD                  ( ( بیعلامت صحيح ) 0xFF << 24 ) /* (SSC) Receive/Transmit Period Divider Selection */
/* -------- SSC_RFMR : (SSC Offset: 0x14) SSC Receive Frame Mode Register -------- */
#تعریف_کن AT91C_SSC_DATLEN                  ( ( بیعلامت صحيح ) 0x1F << 0 )  /* (SSC) Data Length */
#تعریف_کن AT91C_SSC_LOOP                    ( ( بیعلامت صحيح ) 0x1 << 5 )   /* (SSC) Loop Mode */
#تعریف_کن AT91C_SSC_MSBF                    ( ( بیعلامت صحيح ) 0x1 << 7 )   /* (SSC) Most Significant Bit First */
#تعریف_کن AT91C_SSC_DATNB                   ( ( بیعلامت صحيح ) 0xF << 8 )   /* (SSC) Data Number per Frame */
#تعریف_کن AT91C_SSC_FSLEN                   ( ( بیعلامت صحيح ) 0xF << 16 )  /* (SSC) Receive/Transmit Frame Sync length */
#تعریف_کن AT91C_SSC_FSOS                    ( ( بیعلامت صحيح ) 0x7 << 20 )  /* (SSC) Receive/Transmit Frame Sync Output Selection */
#تعریف_کن     AT91C_SSC_FSOS_NONE           ( ( بیعلامت صحيح ) 0x0 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: None RK pin Input-only */
#تعریف_کن     AT91C_SSC_FSOS_NEGATIVE       ( ( بیعلامت صحيح ) 0x1 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Negative Pulse */
#تعریف_کن     AT91_C_SSC_FSOS_مثبت       ( ( بیعلامت صحيح ) 0x2 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Positive Pulse */
#تعریف_کن     AT91_C_SSC_FSOS_کم            ( ( بیعلامت صحيح ) 0x3 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Driver Low during data transfer */
#تعریف_کن     AT91_C_SSC_FSOS_بالا           ( ( بیعلامت صحيح ) 0x4 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Driver High during data transfer */
#تعریف_کن     AT91C_SSC_FSOS_TOGGLE         ( ( بیعلامت صحيح ) 0x5 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Toggling at each start of data transfer */
#تعریف_کن AT91C_SSC_FSEDGE                  ( ( بیعلامت صحيح ) 0x1 << 24 )  /* (SSC) Frame Sync Edge Detection */
/* -------- SSC_TCMR : (SSC Offset: 0x18) SSC Transmit Clock Mode Register -------- */
/* -------- SSC_TFMR : (SSC Offset: 0x1c) SSC Transmit Frame Mode Register -------- */
#تعریف_کن AT91C_SSC_DATDEF                  ( ( بیعلامت صحيح ) 0x1 << 5 )  /* (SSC) Data Default Value */
#تعریف_کن AT91C_SSC_FSDEN                   ( ( بیعلامت صحيح ) 0x1 << 23 ) /* (SSC) Frame Sync Data Enable */
/* -------- SSC_SR : (SSC Offset: 0x40) SSC Status Register -------- */
#تعریف_کن AT91C_SSC_TXRDY                   ( ( بیعلامت صحيح ) 0x1 << 0 )  /* (SSC) Transmit Ready */
#تعریف_کن AT91C_SSC_TXEMPTY                 ( ( بیعلامت صحيح ) 0x1 << 1 )  /* (SSC) Transmit Empty */
#تعریف_کن AT91C_SSC_ENDTX                   ( ( بیعلامت صحيح ) 0x1 << 2 )  /* (SSC) End Of Transmission */
#تعریف_کن AT91C_SSC_TXBUFE                  ( ( بیعلامت صحيح ) 0x1 << 3 )  /* (SSC) Transmit Buffer Empty */
#تعریف_کن AT91C_SSC_RXRDY                   ( ( بیعلامت صحيح ) 0x1 << 4 )  /* (SSC) Receive Ready */
#تعریف_کن AT91C_SSC_OVRUN                   ( ( بیعلامت صحيح ) 0x1 << 5 )  /* (SSC) Receive Overrun */
#تعریف_کن AT91C_SSC_ENDRX                   ( ( بیعلامت صحيح ) 0x1 << 6 )  /* (SSC) End of Reception */
#تعریف_کن AT91C_SSC_RXBUFF                  ( ( بیعلامت صحيح ) 0x1 << 7 )  /* (SSC) Receive Buffer Full */
#تعریف_کن AT91C_SSC_TXSYN                   ( ( بیعلامت صحيح ) 0x1 << 10 ) /* (SSC) Transmit Sync */
#تعریف_کن AT91C_SSC_RXSYN                   ( ( بیعلامت صحيح ) 0x1 << 11 ) /* (SSC) Receive Sync */
#تعریف_کن AT91C_SSC_TXENA                   ( ( بیعلامت صحيح ) 0x1 << 16 ) /* (SSC) Transmit Enable */
#تعریف_کن AT91C_SSC_RXENA                   ( ( بیعلامت صحيح ) 0x1 << 17 ) /* (SSC) Receive Enable */
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
#تعریف_کن AT91_C_TWI_شروع                ( ( بیعلامت صحيح ) 0x1 << 0 )   /* (TWI) Send a START Condition */
#تعریف_کن AT91C_TWI_STOP                 ( ( بیعلامت صحيح ) 0x1 << 1 )   /* (TWI) Send a STOP Condition */
#تعریف_کن AT91C_TWI_MSEN                 ( ( بیعلامت صحيح ) 0x1 << 2 )   /* (TWI) TWI Master Transfer Enabled */
#تعریف_کن AT91C_TWI_MSDIS                ( ( بیعلامت صحيح ) 0x1 << 3 )   /* (TWI) TWI Master Transfer Disabled */
#تعریف_کن AT91C_TWI_SWRST                ( ( بیعلامت صحيح ) 0x1 << 7 )   /* (TWI) Software Reset */
/* -------- TWI_MMR : (TWI Offset: 0x4) TWI Master Mode Register -------- */
#تعریف_کن AT91C_TWI_IADRSZ               ( ( بیعلامت صحيح ) 0x3 << 8 )   /* (TWI) Internal Device Address Size */
#تعریف_کن     AT91C_TWI_IADRSZ_NO        ( ( بیعلامت صحيح ) 0x0 << 8 )   /* (TWI) No internal device address */
#تعریف_کن     AT91C_TWI_IADRSZ_1_BYTE    ( ( بیعلامت صحيح ) 0x1 << 8 )   /* (TWI) One-byte internal device address */
#تعریف_کن     AT91C_TWI_IADRSZ_2_BYTE    ( ( بیعلامت صحيح ) 0x2 << 8 )   /* (TWI) Two-byte internal device address */
#تعریف_کن     AT91C_TWI_IADRSZ_3_BYTE    ( ( بیعلامت صحيح ) 0x3 << 8 )   /* (TWI) Three-byte internal device address */
#تعریف_کن AT91C_TWI_MREAD                ( ( بیعلامت صحيح ) 0x1 << 12 )  /* (TWI) Master Read Direction */
#تعریف_کن AT91C_TWI_DADR                 ( ( بیعلامت صحيح ) 0x7F << 16 ) /* (TWI) Device Address */
/* -------- TWI_CWGR : (TWI Offset: 0x10) TWI Clock Waveform Generator Register -------- */
#تعریف_کن AT91C_TWI_CLDIV                ( ( بیعلامت صحيح ) 0xFF << 0 )  /* (TWI) Clock Low Divider */
#تعریف_کن AT91C_TWI_CHDIV                ( ( بیعلامت صحيح ) 0xFF << 8 )  /* (TWI) Clock High Divider */
#تعریف_کن AT91C_TWI_CKDIV                ( ( بیعلامت صحيح ) 0x7 << 16 )  /* (TWI) Clock Divider */
/* -------- TWI_SR : (TWI Offset: 0x20) TWI Status Register -------- */
#تعریف_کن AT91C_TWI_TXCOMP               ( ( بیعلامت صحيح ) 0x1 << 0 )   /* (TWI) Transmission Completed */
#تعریف_کن AT91C_TWI_RXRDY                ( ( بیعلامت صحيح ) 0x1 << 1 )   /* (TWI) Receive holding register ReaDY */
#تعریف_کن AT91C_TWI_TXRDY                ( ( بیعلامت صحيح ) 0x1 << 2 )   /* (TWI) Transmit holding register ReaDY */
#تعریف_کن AT91C_TWI_OVRE                 ( ( بیعلامت صحيح ) 0x1 << 6 )   /* (TWI) Overrun Error */
#تعریف_کن AT91C_TWI_UNRE                 ( ( بیعلامت صحيح ) 0x1 << 7 )   /* (TWI) Underrun Error */
#تعریف_کن AT91C_TWI_NACK                 ( ( بیعلامت صحيح ) 0x1 << 8 )   /* (TWI) Not Acknowledged */
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
#تعریف_کن AT91C_PWMC_CPRE             ( ( بیعلامت صحيح ) 0xF << 0 )  /* (PWMC_CH) Channel Pre-scaler : PWMC_CLKx */
#تعریف_کن     AT91C_PWMC_CPRE_MCK     ( ( بیعلامت صحيح ) 0x0 )       /* (PWMC_CH) */
#تعریف_کن     AT91C_PWMC_CPRE_MCKA    ( ( بیعلامت صحيح ) 0xB )       /* (PWMC_CH) */
#تعریف_کن     AT91C_PWMC_CPRE_MCKB    ( ( بیعلامت صحيح ) 0xC )       /* (PWMC_CH) */
#تعریف_کن AT91C_PWMC_CALG             ( ( بیعلامت صحيح ) 0x1 << 8 )  /* (PWMC_CH) Channel Alignment */
#تعریف_کن AT91C_PWMC_CPOL             ( ( بیعلامت صحيح ) 0x1 << 9 )  /* (PWMC_CH) Channel Polarity */
#تعریف_کن AT91C_PWMC_CPD              ( ( بیعلامت صحيح ) 0x1 << 10 ) /* (PWMC_CH) Channel Update Period */
/* -------- PWMC_CDTYR : (PWMC_CH Offset: 0x4) PWMC Channel Duty Cycle Register -------- */
#تعریف_کن AT91C_PWMC_CDTY             ( ( بیعلامت صحيح ) 0x0 << 0 )  /* (PWMC_CH) Channel Duty Cycle */
/* -------- PWMC_CPRDR : (PWMC_CH Offset: 0x8) PWMC Channel Period Register -------- */
#تعریف_کن AT91C_PWMC_CPRD             ( ( بیعلامت صحيح ) 0x0 << 0 )  /* (PWMC_CH) Channel Period */
/* -------- PWMC_CCNTR : (PWMC_CH Offset: 0xc) PWMC Channel Counter Register -------- */
#تعریف_کن AT91C_PWMC_CCNT             ( ( بیعلامت صحيح ) 0x0 << 0 )  /* (PWMC_CH) Channel Counter */
/* -------- PWMC_CUPDR : (PWMC_CH Offset: 0x10) PWMC Channel Update Register -------- */
#تعریف_کن AT91C_PWMC_CUPD             ( ( بیعلامت صحيح ) 0x0 << 0 )  /* (PWMC_CH) Channel Update */

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
#تعریف_کن AT91C_PWMC_DIVA            ( ( بیعلامت صحيح ) 0xFF << 0 )  /* (PWMC) CLKA divide factor. */
#تعریف_کن AT91C_PWMC_PREA            ( ( بیعلامت صحيح ) 0xF << 8 )   /* (PWMC) Divider Input Clock Prescaler A */
#تعریف_کن     AT91C_PWMC_PREA_MCK    ( ( بیعلامت صحيح ) 0x0 << 8 )   /* (PWMC) */
#تعریف_کن AT91C_PWMC_DIVB            ( ( بیعلامت صحيح ) 0xFF << 16 ) /* (PWMC) CLKB divide factor. */
#تعریف_کن AT91C_PWMC_PREB            ( ( بیعلامت صحيح ) 0xF << 24 )  /* (PWMC) Divider Input Clock Prescaler B */
#تعریف_کن     AT91C_PWMC_PREB_MCK    ( ( بیعلامت صحيح ) 0x0 << 24 )  /* (PWMC) */
/* -------- PWMC_ENA : (PWMC Offset: 0x4) PWMC Enable Register -------- */
#تعریف_کن AT91C_PWMC_CHID0           ( ( بیعلامت صحيح ) 0x1 << 0 )   /* (PWMC) Channel ID 0 */
#تعریف_کن AT91C_PWMC_CHID1           ( ( بیعلامت صحيح ) 0x1 << 1 )   /* (PWMC) Channel ID 1 */
#تعریف_کن AT91C_PWMC_CHID2           ( ( بیعلامت صحيح ) 0x1 << 2 )   /* (PWMC) Channel ID 2 */
#تعریف_کن AT91C_PWMC_CHID3           ( ( بیعلامت صحيح ) 0x1 << 3 )   /* (PWMC) Channel ID 3 */
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
    AT91_REG UDP_رقم;        /* Frame Number Register */
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
#تعریف_کن AT91_C_UDP_FRM_رقم    ( ( بیعلامت صحيح ) 0x7FF << 0 ) /* (UDP) Frame Number as Defined in the Packet Field Formats */
#تعریف_کن AT91C_UDP_FRM_ERR    ( ( بیعلامت صحيح ) 0x1 << 16 )  /* (UDP) Frame Error */
#تعریف_کن AT91C_UDP_FRM_OK     ( ( بیعلامت صحيح ) 0x1 << 17 )  /* (UDP) Frame OK */
/* -------- UDP_GLB_STATE : (UDP Offset: 0x4) USB Global State Register -------- */
#تعریف_کن AT91C_UDP_FADDEN     ( ( بیعلامت صحيح ) 0x1 << 0 )   /* (UDP) Function Address Enable */
#تعریف_کن AT91C_UDP_CONFG      ( ( بیعلامت صحيح ) 0x1 << 1 )   /* (UDP) Configured */
#تعریف_کن AT91C_UDP_ESR        ( ( بیعلامت صحيح ) 0x1 << 2 )   /* (UDP) Enable Send Resume */
#تعریف_کن AT91C_UDP_RSMINPR    ( ( بیعلامت صحيح ) 0x1 << 3 )   /* (UDP) A Resume Has Been Sent to the Host */
#تعریف_کن AT91C_UDP_RMWUPE     ( ( بیعلامت صحيح ) 0x1 << 4 )   /* (UDP) Remote Wake Up Enable */
/* -------- UDP_FADDR : (UDP Offset: 0x8) USB Function Address Register -------- */
#تعریف_کن AT91C_UDP_FADD       ( ( بیعلامت صحيح ) 0xFF << 0 )  /* (UDP) Function Address Value */
#تعریف_کن AT91C_UDP_FEN        ( ( بیعلامت صحيح ) 0x1 << 8 )   /* (UDP) Function Enable */
/* -------- UDP_IER : (UDP Offset: 0x10) USB Interrupt Enable Register -------- */
#تعریف_کن AT91C_UDP_EPINT0     ( ( بیعلامت صحيح ) 0x1 << 0 )   /* (UDP) Endpoint 0 Interrupt */
#تعریف_کن AT91C_UDP_EPINT1     ( ( بیعلامت صحيح ) 0x1 << 1 )   /* (UDP) Endpoint 0 Interrupt */
#تعریف_کن AT91C_UDP_EPINT2     ( ( بیعلامت صحيح ) 0x1 << 2 )   /* (UDP) Endpoint 2 Interrupt */
#تعریف_کن AT91C_UDP_EPINT3     ( ( بیعلامت صحيح ) 0x1 << 3 )   /* (UDP) Endpoint 3 Interrupt */
#تعریف_کن AT91C_UDP_EPINT4     ( ( بیعلامت صحيح ) 0x1 << 4 )   /* (UDP) Endpoint 4 Interrupt */
#تعریف_کن AT91C_UDP_EPINT5     ( ( بیعلامت صحيح ) 0x1 << 5 )   /* (UDP) Endpoint 5 Interrupt */
#تعریف_کن AT91C_UDP_RXSUSP     ( ( بیعلامت صحيح ) 0x1 << 8 )   /* (UDP) USB Suspend Interrupt */
#تعریف_کن AT91C_UDP_RXRSM      ( ( بیعلامت صحيح ) 0x1 << 9 )   /* (UDP) USB Resume Interrupt */
#تعریف_کن AT91C_UDP_EXTRSM     ( ( بیعلامت صحيح ) 0x1 << 10 )  /* (UDP) USB External Resume Interrupt */
#تعریف_کن AT91C_UDP_SOFINT     ( ( بیعلامت صحيح ) 0x1 << 11 )  /* (UDP) USB Start Of frame Interrupt */
#تعریف_کن AT91C_UDP_WAKEUP     ( ( بیعلامت صحيح ) 0x1 << 13 )  /* (UDP) USB Resume Interrupt */
/* -------- UDP_IDR : (UDP Offset: 0x14) USB Interrupt Disable Register -------- */
/* -------- UDP_IMR : (UDP Offset: 0x18) USB Interrupt Mask Register -------- */
/* -------- UDP_ISR : (UDP Offset: 0x1c) USB Interrupt Status Register -------- */
#تعریف_کن AT91C_UDP_ENDBUSRES              ( ( بیعلامت صحيح ) 0x1 << 12 ) /* (UDP) USB End Of Bus Reset Interrupt */
/* -------- UDP_ICR : (UDP Offset: 0x20) USB Interrupt Clear Register -------- */
/* -------- UDP_RST_EP : (UDP Offset: 0x28) USB Reset Endpoint Register -------- */
#تعریف_کن AT91C_UDP_EP0                    ( ( بیعلامت صحيح ) 0x1 << 0 )    /* (UDP) Reset Endpoint 0 */
#تعریف_کن AT91C_UDP_EP1                    ( ( بیعلامت صحيح ) 0x1 << 1 )    /* (UDP) Reset Endpoint 1 */
#تعریف_کن AT91C_UDP_EP2                    ( ( بیعلامت صحيح ) 0x1 << 2 )    /* (UDP) Reset Endpoint 2 */
#تعریف_کن AT91C_UDP_EP3                    ( ( بیعلامت صحيح ) 0x1 << 3 )    /* (UDP) Reset Endpoint 3 */
#تعریف_کن AT91C_UDP_EP4                    ( ( بیعلامت صحيح ) 0x1 << 4 )    /* (UDP) Reset Endpoint 4 */
#تعریف_کن AT91C_UDP_EP5                    ( ( بیعلامت صحيح ) 0x1 << 5 )    /* (UDP) Reset Endpoint 5 */
/* -------- UDP_CSR : (UDP Offset: 0x30) USB Endpoint Control and Status Register -------- */
#تعریف_کن AT91C_UDP_TXCOMP                 ( ( بیعلامت صحيح ) 0x1 << 0 )    /* (UDP) Generates an IN packet with data previously written in the DPR */
#تعریف_کن AT91_C_UDP_RX_داده_BK0            ( ( بیعلامت صحيح ) 0x1 << 1 )    /* (UDP) Receive Data Bank 0 */
#تعریف_کن AT91C_UDP_RXSETUP                ( ( بیعلامت صحيح ) 0x1 << 2 )    /* (UDP) Sends STALL to the Host (Control endpoints) */
#تعریف_کن AT91C_UDP_ISOERROR               ( ( بیعلامت صحيح ) 0x1 << 3 )    /* (UDP) Isochronous error (Isochronous endpoints) */
#تعریف_کن AT91C_UDP_TXPKTRDY               ( ( بیعلامت صحيح ) 0x1 << 4 )    /* (UDP) Transmit Packet Ready */
#تعریف_کن AT91C_UDP_FORCESTALL             ( ( بیعلامت صحيح ) 0x1 << 5 )    /* (UDP) Force Stall (used by Control, Bulk and Isochronous endpoints). */
#تعریف_کن AT91_C_UDP_RX_داده_BK1            ( ( بیعلامت صحيح ) 0x1 << 6 )    /* (UDP) Receive Data Bank 1 (only used by endpoints with ping-pong attributes). */
#تعریف_کن AT91C_UDP_DIR                    ( ( بیعلامت صحيح ) 0x1 << 7 )    /* (UDP) Transfer Direction */
#تعریف_کن AT91C_UDP_EPTYPE                 ( ( بیعلامت صحيح ) 0x7 << 8 )    /* (UDP) Endpoint type */
#تعریف_کن     AT91C_UDP_EPTYPE_CTRL        ( ( بیعلامت صحيح ) 0x0 << 8 )    /* (UDP) Control */
#تعریف_کن     AT91_C_UDP_EPTYPE_ISO_بیرون     ( ( بیعلامت صحيح ) 0x1 << 8 )    /* (UDP) Isochronous OUT */
#تعریف_کن     AT91_C_UDP_EPTYPE_BULK_بیرون    ( ( بیعلامت صحيح ) 0x2 << 8 )    /* (UDP) Bulk OUT */
#تعریف_کن     AT91_C_UDP_EPTYPE_INT_بیرون     ( ( بیعلامت صحيح ) 0x3 << 8 )    /* (UDP) Interrupt OUT */
#تعریف_کن     AT91_C_UDP_EPTYPE_ISO_درون      ( ( بیعلامت صحيح ) 0x5 << 8 )    /* (UDP) Isochronous IN */
#تعریف_کن     AT91_C_UDP_EPTYPE_BULK_درون     ( ( بیعلامت صحيح ) 0x6 << 8 )    /* (UDP) Bulk IN */
#تعریف_کن     AT91_C_UDP_EPTYPE_INT_درون      ( ( بیعلامت صحيح ) 0x7 << 8 )    /* (UDP) Interrupt IN */
#تعریف_کن AT91C_UDP_DTGLE                  ( ( بیعلامت صحيح ) 0x1 << 11 )   /* (UDP) Data Toggle */
#تعریف_کن AT91C_UDP_EPEDS                  ( ( بیعلامت صحيح ) 0x1 << 15 )   /* (UDP) Endpoint Enable Disable */
#تعریف_کن AT91C_UDP_RXBYTECNT              ( ( بیعلامت صحيح ) 0x7FF << 16 ) /* (UDP) Number Of Bytes Available in the FIFO */
/* -------- UDP_TXVC : (UDP Offset: 0x74) Transceiver Control Register -------- */
#تعریف_کن AT91C_UDP_TXVDIS                 ( ( بیعلامت صحيح ) 0x1 << 8 )    /* (UDP) */
#تعریف_کن AT91C_UDP_PUON                   ( ( بیعلامت صحيح ) 0x1 << 9 )    /* (UDP) Pull-up ON */

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
#تعریف_کن AT91C_TC_CLKEN                        ( ( بیعلامت صحيح ) 0x1 << 0 )  /* (TC) Counter Clock Enable Command */
#تعریف_کن AT91C_TC_CLKDIS                       ( ( بیعلامت صحيح ) 0x1 << 1 )  /* (TC) Counter Clock Disable Command */
#تعریف_کن AT91C_TC_SWTRG                        ( ( بیعلامت صحيح ) 0x1 << 2 )  /* (TC) Software Trigger Command */
/* -------- TC_CMR : (TC Offset: 0x4) TC Channel Mode Register: Capture Mode / Waveform Mode -------- */
#تعریف_کن AT91C_TC_CLKS                         ( ( بیعلامت صحيح ) 0x7 << 0 )  /* (TC) Clock Selection */
#تعریف_کن     AT91C_TC_CLKS_TIMER_DIV1_CLOCK    ( ( بیعلامت صحيح ) 0x0 )       /* (TC) Clock selected: TIMER_DIV1_CLOCK */
#تعریف_کن     AT91C_TC_CLKS_TIMER_DIV2_CLOCK    ( ( بیعلامت صحيح ) 0x1 )       /* (TC) Clock selected: TIMER_DIV2_CLOCK */
#تعریف_کن     AT91C_TC_CLKS_TIMER_DIV3_CLOCK    ( ( بیعلامت صحيح ) 0x2 )       /* (TC) Clock selected: TIMER_DIV3_CLOCK */
#تعریف_کن     AT91C_TC_CLKS_TIMER_DIV4_CLOCK    ( ( بیعلامت صحيح ) 0x3 )       /* (TC) Clock selected: TIMER_DIV4_CLOCK */
#تعریف_کن     AT91C_TC_CLKS_TIMER_DIV5_CLOCK    ( ( بیعلامت صحيح ) 0x4 )       /* (TC) Clock selected: TIMER_DIV5_CLOCK */
#تعریف_کن     AT91C_TC_CLKS_XC0                 ( ( بیعلامت صحيح ) 0x5 )       /* (TC) Clock selected: XC0 */
#تعریف_کن     AT91C_TC_CLKS_XC1                 ( ( بیعلامت صحيح ) 0x6 )       /* (TC) Clock selected: XC1 */
#تعریف_کن     AT91C_TC_CLKS_XC2                 ( ( بیعلامت صحيح ) 0x7 )       /* (TC) Clock selected: XC2 */
#تعریف_کن AT91C_TC_CLKI                         ( ( بیعلامت صحيح ) 0x1 << 3 )  /* (TC) Clock Invert */
#تعریف_کن AT91_C_TC_مدت                        ( ( بیعلامت صحيح ) 0x3 << 4 )  /* (TC) Burst Signal Selection */
#تعریف_کن     AT91_C_TC_مدت_NONE               ( ( بیعلامت صحيح ) 0x0 << 4 )  /* (TC) The clock is not gated by an external signal */
#تعریف_کن     AT91_C_TC_مدت_XC0                ( ( بیعلامت صحيح ) 0x1 << 4 )  /* (TC) XC0 is ANDed with the selected clock */
#تعریف_کن     AT91_C_TC_مدت_XC1                ( ( بیعلامت صحيح ) 0x2 << 4 )  /* (TC) XC1 is ANDed with the selected clock */
#تعریف_کن     AT91_C_TC_مدت_XC2                ( ( بیعلامت صحيح ) 0x3 << 4 )  /* (TC) XC2 is ANDed with the selected clock */
#تعریف_کن AT91C_TC_CPCSTOP                      ( ( بیعلامت صحيح ) 0x1 << 6 )  /* (TC) Counter Clock Stopped with RC Compare */
#تعریف_کن AT91C_TC_LDBSTOP                      ( ( بیعلامت صحيح ) 0x1 << 6 )  /* (TC) Counter Clock Stopped with RB Loading */
#تعریف_کن AT91C_TC_CPCDIS                       ( ( بیعلامت صحيح ) 0x1 << 7 )  /* (TC) Counter Clock Disable with RC Compare */
#تعریف_کن AT91C_TC_LDBDIS                       ( ( بیعلامت صحيح ) 0x1 << 7 )  /* (TC) Counter Clock Disabled with RB Loading */
#تعریف_کن AT91C_TC_ETRGEDG                      ( ( بیعلامت صحيح ) 0x3 << 8 )  /* (TC) External Trigger Edge Selection */
#تعریف_کن     AT91C_TC_ETRGEDG_NONE             ( ( بیعلامت صحيح ) 0x0 << 8 )  /* (TC) Edge: None */
#تعریف_کن     AT91C_TC_ETRGEDG_RISING           ( ( بیعلامت صحيح ) 0x1 << 8 )  /* (TC) Edge: rising edge */
#تعریف_کن     AT91C_TC_ETRGEDG_FALLING          ( ( بیعلامت صحيح ) 0x2 << 8 )  /* (TC) Edge: falling edge */
#تعریف_کن     AT91C_TC_ETRGEDG_BOTH             ( ( بیعلامت صحيح ) 0x3 << 8 )  /* (TC) Edge: each edge */
#تعریف_کن AT91C_TC_EEVTEDG                      ( ( بیعلامت صحيح ) 0x3 << 8 )  /* (TC) External Event Edge Selection */
#تعریف_کن     AT91C_TC_EEVTEDG_NONE             ( ( بیعلامت صحيح ) 0x0 << 8 )  /* (TC) Edge: None */
#تعریف_کن     AT91C_TC_EEVTEDG_RISING           ( ( بیعلامت صحيح ) 0x1 << 8 )  /* (TC) Edge: rising edge */
#تعریف_کن     AT91C_TC_EEVTEDG_FALLING          ( ( بیعلامت صحيح ) 0x2 << 8 )  /* (TC) Edge: falling edge */
#تعریف_کن     AT91C_TC_EEVTEDG_BOTH             ( ( بیعلامت صحيح ) 0x3 << 8 )  /* (TC) Edge: each edge */
#تعریف_کن AT91C_TC_EEVT                         ( ( بیعلامت صحيح ) 0x3 << 10 ) /* (TC) External Event  Selection */
#تعریف_کن     AT91C_TC_EEVT_TIOB                ( ( بیعلامت صحيح ) 0x0 << 10 ) /* (TC) Signal selected as external event: TIOB TIOB direction: input */
#تعریف_کن     AT91C_TC_EEVT_XC0                 ( ( بیعلامت صحيح ) 0x1 << 10 ) /* (TC) Signal selected as external event: XC0 TIOB direction: output */
#تعریف_کن     AT91C_TC_EEVT_XC1                 ( ( بیعلامت صحيح ) 0x2 << 10 ) /* (TC) Signal selected as external event: XC1 TIOB direction: output */
#تعریف_کن     AT91C_TC_EEVT_XC2                 ( ( بیعلامت صحيح ) 0x3 << 10 ) /* (TC) Signal selected as external event: XC2 TIOB direction: output */
#تعریف_کن AT91C_TC_ABETRG                       ( ( بیعلامت صحيح ) 0x1 << 10 ) /* (TC) TIOA or TIOB External Trigger Selection */
#تعریف_کن AT91C_TC_ENETRG                       ( ( بیعلامت صحيح ) 0x1 << 12 ) /* (TC) External Event Trigger enable */
#تعریف_کن AT91C_TC_WAVESEL                      ( ( بیعلامت صحيح ) 0x3 << 13 ) /* (TC) Waveform  Selection */
#تعریف_کن     AT91_C_TC_WAVESEL_به_بالا               ( ( بیعلامت صحيح ) 0x0 << 13 ) /* (TC) UP mode without atomatic trigger on RC Compare */
#تعریف_کن     AT91C_TC_WAVESEL_UPDOWN           ( ( بیعلامت صحيح ) 0x1 << 13 ) /* (TC) UPDOWN mode without automatic trigger on RC Compare */
#تعریف_کن     AT91_C_TC_WAVESEL_به_بالا_AUTO          ( ( بیعلامت صحيح ) 0x2 << 13 ) /* (TC) UP mode with automatic trigger on RC Compare */
#تعریف_کن     AT91C_TC_WAVESEL_UPDOWN_AUTO      ( ( بیعلامت صحيح ) 0x3 << 13 ) /* (TC) UPDOWN mode with automatic trigger on RC Compare */
#تعریف_کن AT91C_TC_CPCTRG                       ( ( بیعلامت صحيح ) 0x1 << 14 ) /* (TC) RC Compare Trigger Enable */
#تعریف_کن AT91C_TC_WAVE                         ( ( بیعلامت صحيح ) 0x1 << 15 ) /* (TC) */
#تعریف_کن AT91C_TC_ACPA                         ( ( بیعلامت صحيح ) 0x3 << 16 ) /* (TC) RA Compare Effect on TIOA */
#تعریف_کن     AT91C_TC_ACPA_NONE                ( ( بیعلامت صحيح ) 0x0 << 16 ) /* (TC) Effect: none */
#تعریف_کن     AT91_C_TC_ACPA_مجموعه                 ( ( بیعلامت صحيح ) 0x1 << 16 ) /* (TC) Effect: set */
#تعریف_کن     AT91C_TC_ACPA_CLEAR               ( ( بیعلامت صحيح ) 0x2 << 16 ) /* (TC) Effect: clear */
#تعریف_کن     AT91C_TC_ACPA_TOGGLE              ( ( بیعلامت صحيح ) 0x3 << 16 ) /* (TC) Effect: toggle */
#تعریف_کن AT91C_TC_LDRA                         ( ( بیعلامت صحيح ) 0x3 << 16 ) /* (TC) RA Loading Selection */
#تعریف_کن     AT91C_TC_LDRA_NONE                ( ( بیعلامت صحيح ) 0x0 << 16 ) /* (TC) Edge: None */
#تعریف_کن     AT91C_TC_LDRA_RISING              ( ( بیعلامت صحيح ) 0x1 << 16 ) /* (TC) Edge: rising edge of TIOA */
#تعریف_کن     AT91C_TC_LDRA_FALLING             ( ( بیعلامت صحيح ) 0x2 << 16 ) /* (TC) Edge: falling edge of TIOA */
#تعریف_کن     AT91C_TC_LDRA_BOTH                ( ( بیعلامت صحيح ) 0x3 << 16 ) /* (TC) Edge: each edge of TIOA */
#تعریف_کن AT91C_TC_ACPC                         ( ( بیعلامت صحيح ) 0x3 << 18 ) /* (TC) RC Compare Effect on TIOA */
#تعریف_کن     AT91C_TC_ACPC_NONE                ( ( بیعلامت صحيح ) 0x0 << 18 ) /* (TC) Effect: none */
#تعریف_کن     AT91_C_TC_ACPC_مجموعه                 ( ( بیعلامت صحيح ) 0x1 << 18 ) /* (TC) Effect: set */
#تعریف_کن     AT91C_TC_ACPC_CLEAR               ( ( بیعلامت صحيح ) 0x2 << 18 ) /* (TC) Effect: clear */
#تعریف_کن     AT91C_TC_ACPC_TOGGLE              ( ( بیعلامت صحيح ) 0x3 << 18 ) /* (TC) Effect: toggle */
#تعریف_کن AT91C_TC_LDRB                         ( ( بیعلامت صحيح ) 0x3 << 18 ) /* (TC) RB Loading Selection */
#تعریف_کن     AT91C_TC_LDRB_NONE                ( ( بیعلامت صحيح ) 0x0 << 18 ) /* (TC) Edge: None */
#تعریف_کن     AT91C_TC_LDRB_RISING              ( ( بیعلامت صحيح ) 0x1 << 18 ) /* (TC) Edge: rising edge of TIOA */
#تعریف_کن     AT91C_TC_LDRB_FALLING             ( ( بیعلامت صحيح ) 0x2 << 18 ) /* (TC) Edge: falling edge of TIOA */
#تعریف_کن     AT91C_TC_LDRB_BOTH                ( ( بیعلامت صحيح ) 0x3 << 18 ) /* (TC) Edge: each edge of TIOA */
#تعریف_کن AT91C_TC_AEEVT                        ( ( بیعلامت صحيح ) 0x3 << 20 ) /* (TC) External Event Effect on TIOA */
#تعریف_کن     AT91C_TC_AEEVT_NONE               ( ( بیعلامت صحيح ) 0x0 << 20 ) /* (TC) Effect: none */
#تعریف_کن     AT91_C_TC_AEEVT_مجموعه                ( ( بیعلامت صحيح ) 0x1 << 20 ) /* (TC) Effect: set */
#تعریف_کن     AT91C_TC_AEEVT_CLEAR              ( ( بیعلامت صحيح ) 0x2 << 20 ) /* (TC) Effect: clear */
#تعریف_کن     AT91C_TC_AEEVT_TOGGLE             ( ( بیعلامت صحيح ) 0x3 << 20 ) /* (TC) Effect: toggle */
#تعریف_کن AT91C_TC_ASWTRG                       ( ( بیعلامت صحيح ) 0x3 << 22 ) /* (TC) Software Trigger Effect on TIOA */
#تعریف_کن     AT91C_TC_ASWTRG_NONE              ( ( بیعلامت صحيح ) 0x0 << 22 ) /* (TC) Effect: none */
#تعریف_کن     AT91_C_TC_ASWTRG_مجموعه               ( ( بیعلامت صحيح ) 0x1 << 22 ) /* (TC) Effect: set */
#تعریف_کن     AT91C_TC_ASWTRG_CLEAR             ( ( بیعلامت صحيح ) 0x2 << 22 ) /* (TC) Effect: clear */
#تعریف_کن     AT91C_TC_ASWTRG_TOGGLE            ( ( بیعلامت صحيح ) 0x3 << 22 ) /* (TC) Effect: toggle */
#تعریف_کن AT91C_TC_BCPB                         ( ( بیعلامت صحيح ) 0x3 << 24 ) /* (TC) RB Compare Effect on TIOB */
#تعریف_کن     AT91C_TC_BCPB_NONE                ( ( بیعلامت صحيح ) 0x0 << 24 ) /* (TC) Effect: none */
#تعریف_کن     AT91_C_TC_BCPB_مجموعه                 ( ( بیعلامت صحيح ) 0x1 << 24 ) /* (TC) Effect: set */
#تعریف_کن     AT91C_TC_BCPB_CLEAR               ( ( بیعلامت صحيح ) 0x2 << 24 ) /* (TC) Effect: clear */
#تعریف_کن     AT91C_TC_BCPB_TOGGLE              ( ( بیعلامت صحيح ) 0x3 << 24 ) /* (TC) Effect: toggle */
#تعریف_کن AT91C_TC_BCPC                         ( ( بیعلامت صحيح ) 0x3 << 26 ) /* (TC) RC Compare Effect on TIOB */
#تعریف_کن     AT91C_TC_BCPC_NONE                ( ( بیعلامت صحيح ) 0x0 << 26 ) /* (TC) Effect: none */
#تعریف_کن     AT91_C_TC_BCPC_مجموعه                 ( ( بیعلامت صحيح ) 0x1 << 26 ) /* (TC) Effect: set */
#تعریف_کن     AT91C_TC_BCPC_CLEAR               ( ( بیعلامت صحيح ) 0x2 << 26 ) /* (TC) Effect: clear */
#تعریف_کن     AT91C_TC_BCPC_TOGGLE              ( ( بیعلامت صحيح ) 0x3 << 26 ) /* (TC) Effect: toggle */
#تعریف_کن AT91C_TC_BEEVT                        ( ( بیعلامت صحيح ) 0x3 << 28 ) /* (TC) External Event Effect on TIOB */
#تعریف_کن     AT91C_TC_BEEVT_NONE               ( ( بیعلامت صحيح ) 0x0 << 28 ) /* (TC) Effect: none */
#تعریف_کن     AT91_C_TC_BEEVT_مجموعه                ( ( بیعلامت صحيح ) 0x1 << 28 ) /* (TC) Effect: set */
#تعریف_کن     AT91C_TC_BEEVT_CLEAR              ( ( بیعلامت صحيح ) 0x2 << 28 ) /* (TC) Effect: clear */
#تعریف_کن     AT91C_TC_BEEVT_TOGGLE             ( ( بیعلامت صحيح ) 0x3 << 28 ) /* (TC) Effect: toggle */
#تعریف_کن AT91C_TC_BSWTRG                       ( ( بیعلامت صحيح ) 0x3 << 30 ) /* (TC) Software Trigger Effect on TIOB */
#تعریف_کن     AT91C_TC_BSWTRG_NONE              ( ( بیعلامت صحيح ) 0x0 << 30 ) /* (TC) Effect: none */
#تعریف_کن     AT91_C_TC_BSWTRG_مجموعه               ( ( بیعلامت صحيح ) 0x1 << 30 ) /* (TC) Effect: set */
#تعریف_کن     AT91C_TC_BSWTRG_CLEAR             ( ( بیعلامت صحيح ) 0x2 << 30 ) /* (TC) Effect: clear */
#تعریف_کن     AT91C_TC_BSWTRG_TOGGLE            ( ( بیعلامت صحيح ) 0x3 << 30 ) /* (TC) Effect: toggle */
/* -------- TC_SR : (TC Offset: 0x20) TC Channel Status Register -------- */
#تعریف_کن AT91C_TC_COVFS                        ( ( بیعلامت صحيح ) 0x1 << 0 )  /* (TC) Counter Overflow */
#تعریف_کن AT91C_TC_LOVRS                        ( ( بیعلامت صحيح ) 0x1 << 1 )  /* (TC) Load Overrun */
#تعریف_کن AT91C_TC_CPAS                         ( ( بیعلامت صحيح ) 0x1 << 2 )  /* (TC) RA Compare */
#تعریف_کن AT91C_TC_CPBS                         ( ( بیعلامت صحيح ) 0x1 << 3 )  /* (TC) RB Compare */
#تعریف_کن AT91C_TC_CPCS                         ( ( بیعلامت صحيح ) 0x1 << 4 )  /* (TC) RC Compare */
#تعریف_کن AT91C_TC_LDRAS                        ( ( بیعلامت صحيح ) 0x1 << 5 )  /* (TC) RA Loading */
#تعریف_کن AT91C_TC_LDRBS                        ( ( بیعلامت صحيح ) 0x1 << 6 )  /* (TC) RB Loading */
#تعریف_کن AT91C_TC_ETRGS                        ( ( بیعلامت صحيح ) 0x1 << 7 )  /* (TC) External Trigger */
#تعریف_کن AT91C_TC_CLKSTA                       ( ( بیعلامت صحيح ) 0x1 << 16 ) /* (TC) Clock Enabling */
#تعریف_کن AT91C_TC_MTIOA                        ( ( بیعلامت صحيح ) 0x1 << 17 ) /* (TC) TIOA Mirror */
#تعریف_کن AT91C_TC_MTIOB                        ( ( بیعلامت صحيح ) 0x1 << 18 ) /* (TC) TIOA Mirror */
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
#تعریف_کن AT91C_TCB_SYNC                 ( ( بیعلامت صحيح ) 0x1 << 0 ) /* (TCB) Synchro Command */
/* -------- TCB_BMR : (TCB Offset: 0xc4) TC Block Mode Register -------- */
#تعریف_کن AT91C_TCB_TC0XC0S              ( ( بیعلامت صحيح ) 0x3 << 0 ) /* (TCB) External Clock Signal 0 Selection */
#تعریف_کن     AT91C_TCB_TC0XC0S_TCLK0    ( ( بیعلامت صحيح ) 0x0 )      /* (TCB) TCLK0 connected to XC0 */
#تعریف_کن     AT91C_TCB_TC0XC0S_NONE     ( ( بیعلامت صحيح ) 0x1 )      /* (TCB) None signal connected to XC0 */
#تعریف_کن     AT91C_TCB_TC0XC0S_TIOA1    ( ( بیعلامت صحيح ) 0x2 )      /* (TCB) TIOA1 connected to XC0 */
#تعریف_کن     AT91C_TCB_TC0XC0S_TIOA2    ( ( بیعلامت صحيح ) 0x3 )      /* (TCB) TIOA2 connected to XC0 */
#تعریف_کن AT91C_TCB_TC1XC1S              ( ( بیعلامت صحيح ) 0x3 << 2 ) /* (TCB) External Clock Signal 1 Selection */
#تعریف_کن     AT91C_TCB_TC1XC1S_TCLK1    ( ( بیعلامت صحيح ) 0x0 << 2 ) /* (TCB) TCLK1 connected to XC1 */
#تعریف_کن     AT91C_TCB_TC1XC1S_NONE     ( ( بیعلامت صحيح ) 0x1 << 2 ) /* (TCB) None signal connected to XC1 */
#تعریف_کن     AT91C_TCB_TC1XC1S_TIOA0    ( ( بیعلامت صحيح ) 0x2 << 2 ) /* (TCB) TIOA0 connected to XC1 */
#تعریف_کن     AT91C_TCB_TC1XC1S_TIOA2    ( ( بیعلامت صحيح ) 0x3 << 2 ) /* (TCB) TIOA2 connected to XC1 */
#تعریف_کن AT91C_TCB_TC2XC2S              ( ( بیعلامت صحيح ) 0x3 << 4 ) /* (TCB) External Clock Signal 2 Selection */
#تعریف_کن     AT91C_TCB_TC2XC2S_TCLK2    ( ( بیعلامت صحيح ) 0x0 << 4 ) /* (TCB) TCLK2 connected to XC2 */
#تعریف_کن     AT91C_TCB_TC2XC2S_NONE     ( ( بیعلامت صحيح ) 0x1 << 4 ) /* (TCB) None signal connected to XC2 */
#تعریف_کن     AT91C_TCB_TC2XC2S_TIOA0    ( ( بیعلامت صحيح ) 0x2 << 4 ) /* (TCB) TIOA0 connected to XC2 */
#تعریف_کن     AT91C_TCB_TC2XC2S_TIOA1    ( ( بیعلامت صحيح ) 0x3 << 4 ) /* (TCB) TIOA2 connected to XC2 */

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
#تعریف_کن AT91C_CAN_MTIMEMARK              ( ( بیعلامت صحيح ) 0xFFFF << 0 )  /* (CAN_MB) Mailbox Timemark */
#تعریف_کن AT91_C_CAN_پیشین                  ( ( بیعلامت صحيح ) 0xF << 16 )    /* (CAN_MB) Mailbox Priority */
#تعریف_کن AT91C_CAN_MOT                    ( ( بیعلامت صحيح ) 0x7 << 24 )    /* (CAN_MB) Mailbox Object Type */
#تعریف_کن     AT91C_CAN_MOT_DIS            ( ( بیعلامت صحيح ) 0x0 << 24 )    /* (CAN_MB) */
#تعریف_کن     AT91C_CAN_MOT_RX             ( ( بیعلامت صحيح ) 0x1 << 24 )    /* (CAN_MB) */
#تعریف_کن     AT91C_CAN_MOT_RXOVERWRITE    ( ( بیعلامت صحيح ) 0x2 << 24 )    /* (CAN_MB) */
#تعریف_کن     AT91C_CAN_MOT_TX             ( ( بیعلامت صحيح ) 0x3 << 24 )    /* (CAN_MB) */
#تعریف_کن     AT91_C_CAN_MOT_مصرفکننده       ( ( بیعلامت صحيح ) 0x4 << 24 )    /* (CAN_MB) */
#تعریف_کن     AT91_C_CAN_MOT_تولیدکننده       ( ( بیعلامت صحيح ) 0x5 << 24 )    /* (CAN_MB) */
/* -------- CAN_MAM : (CAN_MB Offset: 0x4) CAN Message Acceptance Mask Register -------- */
#تعریف_کن AT91C_CAN_MIDvB                  ( ( بیعلامت صحيح ) 0x3FFFF << 0 ) /* (CAN_MB) Complementary bits for identifier in extended mode */
#تعریف_کن AT91C_CAN_MIDvA                  ( ( بیعلامت صحيح ) 0x7FF << 18 )  /* (CAN_MB) Identifier for standard frame mode */
#تعریف_کن AT91C_CAN_MIDE                   ( ( بیعلامت صحيح ) 0x1 << 29 )    /* (CAN_MB) Identifier Version */
/* -------- CAN_MID : (CAN_MB Offset: 0x8) CAN Message ID Register -------- */
/* -------- CAN_MFID : (CAN_MB Offset: 0xc) CAN Message Family ID Register -------- */
/* -------- CAN_MSR : (CAN_MB Offset: 0x10) CAN Message Status Register -------- */
#تعریف_کن AT91C_CAN_MTIMESTAMP    ( ( بیعلامت صحيح ) 0xFFFF << 0 ) /* (CAN_MB) Timer Value */
#تعریف_کن AT91C_CAN_MDLC          ( ( بیعلامت صحيح ) 0xF << 16 )   /* (CAN_MB) Mailbox Data Length Code */
#تعریف_کن AT91C_CAN_MRTR          ( ( بیعلامت صحيح ) 0x1 << 20 )   /* (CAN_MB) Mailbox Remote Transmission Request */
#تعریف_کن AT91C_CAN_MABT          ( ( بیعلامت صحيح ) 0x1 << 22 )   /* (CAN_MB) Mailbox Message Abort */
#تعریف_کن AT91C_CAN_MRDY          ( ( بیعلامت صحيح ) 0x1 << 23 )   /* (CAN_MB) Mailbox Ready */
#تعریف_کن AT91C_CAN_MMI           ( ( بیعلامت صحيح ) 0x1 << 24 )   /* (CAN_MB) Mailbox Message Ignored */
/* -------- CAN_MDL : (CAN_MB Offset: 0x14) CAN Message Data Low Register -------- */
/* -------- CAN_MDH : (CAN_MB Offset: 0x18) CAN Message Data High Register -------- */
/* -------- CAN_MCR : (CAN_MB Offset: 0x1c) CAN Message Control Register -------- */
#تعریف_کن AT91C_CAN_MACR    ( ( بیعلامت صحيح ) 0x1 << 22 ) /* (CAN_MB) Abort Request for Mailbox */
#تعریف_کن AT91C_CAN_MTCR    ( ( بیعلامت صحيح ) 0x1 << 23 ) /* (CAN_MB) Mailbox Transfer Command */

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
#تعریف_کن AT91C_CAN_CANEN     ( ( بیعلامت صحيح ) 0x1 << 0 )  /* (CAN) CAN Controller Enable */
#تعریف_کن AT91C_CAN_LPM       ( ( بیعلامت صحيح ) 0x1 << 1 )  /* (CAN) Disable/Enable Low Power Mode */
#تعریف_کن AT91C_CAN_ABM       ( ( بیعلامت صحيح ) 0x1 << 2 )  /* (CAN) Disable/Enable Autobaud/Listen Mode */
#تعریف_کن AT91C_CAN_OVL       ( ( بیعلامت صحيح ) 0x1 << 3 )  /* (CAN) Disable/Enable Overload Frame */
#تعریف_کن AT91C_CAN_TEOF      ( ( بیعلامت صحيح ) 0x1 << 4 )  /* (CAN) Time Stamp messages at each end of Frame */
#تعریف_کن AT91C_CAN_TTM       ( ( بیعلامت صحيح ) 0x1 << 5 )  /* (CAN) Disable/Enable Time Trigger Mode */
#تعریف_کن AT91C_CAN_TIMFRZ    ( ( بیعلامت صحيح ) 0x1 << 6 )  /* (CAN) Enable Timer Freeze */
#تعریف_کن AT91C_CAN_DRPT      ( ( بیعلامت صحيح ) 0x1 << 7 )  /* (CAN) Disable Repeat */
/* -------- CAN_IER : (CAN Offset: 0x4) CAN Interrupt Enable Register -------- */
#تعریف_کن AT91C_CAN_MB0       ( ( بیعلامت صحيح ) 0x1 << 0 )  /* (CAN) Mailbox 0 Flag */
#تعریف_کن AT91C_CAN_MB1       ( ( بیعلامت صحيح ) 0x1 << 1 )  /* (CAN) Mailbox 1 Flag */
#تعریف_کن AT91C_CAN_MB2       ( ( بیعلامت صحيح ) 0x1 << 2 )  /* (CAN) Mailbox 2 Flag */
#تعریف_کن AT91C_CAN_MB3       ( ( بیعلامت صحيح ) 0x1 << 3 )  /* (CAN) Mailbox 3 Flag */
#تعریف_کن AT91C_CAN_MB4       ( ( بیعلامت صحيح ) 0x1 << 4 )  /* (CAN) Mailbox 4 Flag */
#تعریف_کن AT91C_CAN_MB5       ( ( بیعلامت صحيح ) 0x1 << 5 )  /* (CAN) Mailbox 5 Flag */
#تعریف_کن AT91C_CAN_MB6       ( ( بیعلامت صحيح ) 0x1 << 6 )  /* (CAN) Mailbox 6 Flag */
#تعریف_کن AT91C_CAN_MB7       ( ( بیعلامت صحيح ) 0x1 << 7 )  /* (CAN) Mailbox 7 Flag */
#تعریف_کن AT91C_CAN_MB8       ( ( بیعلامت صحيح ) 0x1 << 8 )  /* (CAN) Mailbox 8 Flag */
#تعریف_کن AT91C_CAN_MB9       ( ( بیعلامت صحيح ) 0x1 << 9 )  /* (CAN) Mailbox 9 Flag */
#تعریف_کن AT91C_CAN_MB10      ( ( بیعلامت صحيح ) 0x1 << 10 ) /* (CAN) Mailbox 10 Flag */
#تعریف_کن AT91C_CAN_MB11      ( ( بیعلامت صحيح ) 0x1 << 11 ) /* (CAN) Mailbox 11 Flag */
#تعریف_کن AT91C_CAN_MB12      ( ( بیعلامت صحيح ) 0x1 << 12 ) /* (CAN) Mailbox 12 Flag */
#تعریف_کن AT91C_CAN_MB13      ( ( بیعلامت صحيح ) 0x1 << 13 ) /* (CAN) Mailbox 13 Flag */
#تعریف_کن AT91C_CAN_MB14      ( ( بیعلامت صحيح ) 0x1 << 14 ) /* (CAN) Mailbox 14 Flag */
#تعریف_کن AT91C_CAN_MB15      ( ( بیعلامت صحيح ) 0x1 << 15 ) /* (CAN) Mailbox 15 Flag */
#تعریف_کن AT91C_CAN_ERRA      ( ( بیعلامت صحيح ) 0x1 << 16 ) /* (CAN) Error Active Mode Flag */
#تعریف_کن AT91C_CAN_WARN      ( ( بیعلامت صحيح ) 0x1 << 17 ) /* (CAN) Warning Limit Flag */
#تعریف_کن AT91C_CAN_ERRP      ( ( بیعلامت صحيح ) 0x1 << 18 ) /* (CAN) Error Passive Mode Flag */
#تعریف_کن AT91C_CAN_BOFF      ( ( بیعلامت صحيح ) 0x1 << 19 ) /* (CAN) Bus Off Mode Flag */
#تعریف_کن AT91C_CAN_SLEEP     ( ( بیعلامت صحيح ) 0x1 << 20 ) /* (CAN) Sleep Flag */
#تعریف_کن AT91C_CAN_WAKEUP    ( ( بیعلامت صحيح ) 0x1 << 21 ) /* (CAN) Wakeup Flag */
#تعریف_کن AT91C_CAN_TOVF      ( ( بیعلامت صحيح ) 0x1 << 22 ) /* (CAN) Timer Overflow Flag */
#تعریف_کن AT91C_CAN_TSTP      ( ( بیعلامت صحيح ) 0x1 << 23 ) /* (CAN) Timestamp Flag */
#تعریف_کن AT91C_CAN_CERR      ( ( بیعلامت صحيح ) 0x1 << 24 ) /* (CAN) CRC Error */
#تعریف_کن AT91C_CAN_SERR      ( ( بیعلامت صحيح ) 0x1 << 25 ) /* (CAN) Stuffing Error */
#تعریف_کن AT91C_CAN_AERR      ( ( بیعلامت صحيح ) 0x1 << 26 ) /* (CAN) Acknowledgment Error */
#تعریف_کن AT91C_CAN_FERR      ( ( بیعلامت صحيح ) 0x1 << 27 ) /* (CAN) Form Error */
#تعریف_کن AT91C_CAN_BERR      ( ( بیعلامت صحيح ) 0x1 << 28 ) /* (CAN) Bit Error */
/* -------- CAN_IDR : (CAN Offset: 0x8) CAN Interrupt Disable Register -------- */
/* -------- CAN_IMR : (CAN Offset: 0xc) CAN Interrupt Mask Register -------- */
/* -------- CAN_SR : (CAN Offset: 0x10) CAN Status Register -------- */
#تعریف_کن AT91C_CAN_RBSY      ( ( بیعلامت صحيح ) 0x1 << 29 )   /* (CAN) Receiver Busy */
#تعریف_کن AT91C_CAN_TBSY      ( ( بیعلامت صحيح ) 0x1 << 30 )   /* (CAN) Transmitter Busy */
#تعریف_کن AT91C_CAN_OVLY      ( ( بیعلامت صحيح ) 0x1 << 31 )   /* (CAN) Overload Busy */
/* -------- CAN_BR : (CAN Offset: 0x14) CAN Baudrate Register -------- */
#تعریف_کن AT91C_CAN_PHASE2    ( ( بیعلامت صحيح ) 0x7 << 0 )    /* (CAN) Phase 2 segment */
#تعریف_کن AT91C_CAN_PHASE1    ( ( بیعلامت صحيح ) 0x7 << 4 )    /* (CAN) Phase 1 segment */
#تعریف_کن AT91C_CAN_PROPAG    ( ( بیعلامت صحيح ) 0x7 << 8 )    /* (CAN) Programmation time segment */
#تعریف_کن AT91C_CAN_SYNC      ( ( بیعلامت صحيح ) 0x3 << 12 )   /* (CAN) Re-synchronization jump width segment */
#تعریف_کن AT91C_CAN_BRP       ( ( بیعلامت صحيح ) 0x7F << 16 )  /* (CAN) Baudrate Prescaler */
#تعریف_کن AT91C_CAN_SMP       ( ( بیعلامت صحيح ) 0x1 << 24 )   /* (CAN) Sampling mode */
/* -------- CAN_TIM : (CAN Offset: 0x18) CAN Timer Register -------- */
#تعریف_کن AT91C_CAN_TIMER     ( ( بیعلامت صحيح ) 0xFFFF << 0 ) /* (CAN) Timer field */
/* -------- CAN_TIMESTP : (CAN Offset: 0x1c) CAN Timestamp Register -------- */
/* -------- CAN_ECR : (CAN Offset: 0x20) CAN Error Counter Register -------- */
#تعریف_کن AT91C_CAN_REC       ( ( بیعلامت صحيح ) 0xFF << 0 )  /* (CAN) Receive Error Counter */
#تعریف_کن AT91C_CAN_TEC       ( ( بیعلامت صحيح ) 0xFF << 16 ) /* (CAN) Transmit Error Counter */
/* -------- CAN_TCR : (CAN Offset: 0x24) CAN Transfer Command Register -------- */
#تعریف_کن AT91C_CAN_TIMRST    ( ( بیعلامت صحيح ) 0x1 << 31 )  /* (CAN) Timer Reset Field */
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
#تعریف_کن AT91C_EMAC_LB                   ( ( بیعلامت صحيح ) 0x1 << 0 )  /* (EMAC) Loopback. Optional. When set, loopback signal is at high level. */
#تعریف_کن AT91C_EMAC_LLB                  ( ( بیعلامت صحيح ) 0x1 << 1 )  /* (EMAC) Loopback local. */
#تعریف_کن AT91C_EMAC_RE                   ( ( بیعلامت صحيح ) 0x1 << 2 )  /* (EMAC) Receive enable. */
#تعریف_کن AT91C_EMAC_TE                   ( ( بیعلامت صحيح ) 0x1 << 3 )  /* (EMAC) Transmit enable. */
#تعریف_کن AT91C_EMAC_MPE                  ( ( بیعلامت صحيح ) 0x1 << 4 )  /* (EMAC) Management port enable. */
#تعریف_کن AT91C_EMAC_CLRSTAT              ( ( بیعلامت صحيح ) 0x1 << 5 )  /* (EMAC) Clear statistics registers. */
#تعریف_کن AT91C_EMAC_INCSTAT              ( ( بیعلامت صحيح ) 0x1 << 6 )  /* (EMAC) Increment statistics registers. */
#تعریف_کن AT91C_EMAC_WESTAT               ( ( بیعلامت صحيح ) 0x1 << 7 )  /* (EMAC) Write enable for statistics registers. */
#تعریف_کن AT91C_EMAC_BP                   ( ( بیعلامت صحيح ) 0x1 << 8 )  /* (EMAC) Back pressure. */
#تعریف_کن AT91C_EMAC_TSTART               ( ( بیعلامت صحيح ) 0x1 << 9 )  /* (EMAC) Start Transmission. */
#تعریف_کن AT91C_EMAC_THALT                ( ( بیعلامت صحيح ) 0x1 << 10 ) /* (EMAC) Transmission Halt. */
#تعریف_کن AT91C_EMAC_TPFR                 ( ( بیعلامت صحيح ) 0x1 << 11 ) /* (EMAC) Transmit pause frame */
#تعریف_کن AT91C_EMAC_TZQ                  ( ( بیعلامت صحيح ) 0x1 << 12 ) /* (EMAC) Transmit zero quantum pause frame */
/* -------- EMAC_NCFGR : (EMAC Offset: 0x4) Network Configuration Register -------- */
#تعریف_کن AT91C_EMAC_SPD                  ( ( بیعلامت صحيح ) 0x1 << 0 )  /* (EMAC) Speed. */
#تعریف_کن AT91C_EMAC_FD                   ( ( بیعلامت صحيح ) 0x1 << 1 )  /* (EMAC) Full duplex. */
#تعریف_کن AT91C_EMAC_JFRAME               ( ( بیعلامت صحيح ) 0x1 << 3 )  /* (EMAC) Jumbo Frames. */
#تعریف_کن AT91C_EMAC_CAF                  ( ( بیعلامت صحيح ) 0x1 << 4 )  /* (EMAC) Copy all frames. */
#تعریف_کن AT91C_EMAC_NBC                  ( ( بیعلامت صحيح ) 0x1 << 5 )  /* (EMAC) No broadcast. */
#تعریف_کن AT91C_EMAC_MTI                  ( ( بیعلامت صحيح ) 0x1 << 6 )  /* (EMAC) Multicast hash event enable */
#تعریف_کن AT91C_EMAC_UNI                  ( ( بیعلامت صحيح ) 0x1 << 7 )  /* (EMAC) Unicast hash enable. */
#تعریف_کن AT91C_EMAC_BIG                  ( ( بیعلامت صحيح ) 0x1 << 8 )  /* (EMAC) Receive 1522 bytes. */
#تعریف_کن AT91C_EMAC_EAE                  ( ( بیعلامت صحيح ) 0x1 << 9 )  /* (EMAC) External address match enable. */
#تعریف_کن AT91C_EMAC_CLK                  ( ( بیعلامت صحيح ) 0x3 << 10 ) /* (EMAC) */
#تعریف_کن     AT91C_EMAC_CLK_HCLK_8       ( ( بیعلامت صحيح ) 0x0 << 10 ) /* (EMAC) HCLK divided by 8 */
#تعریف_کن     AT91C_EMAC_CLK_HCLK_16      ( ( بیعلامت صحيح ) 0x1 << 10 ) /* (EMAC) HCLK divided by 16 */
#تعریف_کن     AT91C_EMAC_CLK_HCLK_32      ( ( بیعلامت صحيح ) 0x2 << 10 ) /* (EMAC) HCLK divided by 32 */
#تعریف_کن     AT91C_EMAC_CLK_HCLK_64      ( ( بیعلامت صحيح ) 0x3 << 10 ) /* (EMAC) HCLK divided by 64 */
#تعریف_کن AT91C_EMAC_RTY                  ( ( بیعلامت صحيح ) 0x1 << 12 ) /* (EMAC) */
#تعریف_کن AT91C_EMAC_PAE                  ( ( بیعلامت صحيح ) 0x1 << 13 ) /* (EMAC) */
#تعریف_کن AT91C_EMAC_RBOF                 ( ( بیعلامت صحيح ) 0x3 << 14 ) /* (EMAC) */
#تعریف_کن     AT91_C_EMAC_RBOF_جابه_جایی_0    ( ( بیعلامت صحيح ) 0x0 << 14 ) /* (EMAC) no offset from start of receive buffer */
#تعریف_کن     AT91_C_EMAC_RBOF_جابه_جایی_1    ( ( بیعلامت صحيح ) 0x1 << 14 ) /* (EMAC) one byte offset from start of receive buffer */
#تعریف_کن     AT91_C_EMAC_RBOF_جابه_جایی_2    ( ( بیعلامت صحيح ) 0x2 << 14 ) /* (EMAC) two bytes offset from start of receive buffer */
#تعریف_کن     AT91_C_EMAC_RBOF_جابه_جایی_3    ( ( بیعلامت صحيح ) 0x3 << 14 ) /* (EMAC) three bytes offset from start of receive buffer */
#تعریف_کن AT91C_EMAC_RLCE                 ( ( بیعلامت صحيح ) 0x1 << 16 ) /* (EMAC) Receive Length field Checking Enable */
#تعریف_کن AT91C_EMAC_DRFCS                ( ( بیعلامت صحيح ) 0x1 << 17 ) /* (EMAC) Discard Receive FCS */
#تعریف_کن AT91C_EMAC_EFRHD                ( ( بیعلامت صحيح ) 0x1 << 18 ) /* (EMAC) */
#تعریف_کن AT91C_EMAC_IRXFCS               ( ( بیعلامت صحيح ) 0x1 << 19 ) /* (EMAC) Ignore RX FCS */
/* -------- EMAC_NSR : (EMAC Offset: 0x8) Network Status Register -------- */
#تعریف_کن AT91C_EMAC_LINKR                ( ( بیعلامت صحيح ) 0x1 << 0 )  /* (EMAC) */
#تعریف_کن AT91C_EMAC_MDIO                 ( ( بیعلامت صحيح ) 0x1 << 1 )  /* (EMAC) */
#تعریف_کن AT91C_EMAC_IDLE                 ( ( بیعلامت صحيح ) 0x1 << 2 )  /* (EMAC) */
/* -------- EMAC_TSR : (EMAC Offset: 0x14) Transmit Status Register -------- */
#تعریف_کن AT91C_EMAC_UBR                  ( ( بیعلامت صحيح ) 0x1 << 0 )  /* (EMAC) */
#تعریف_کن AT91_C_EMAC_ستون                  ( ( بیعلامت صحيح ) 0x1 << 1 )  /* (EMAC) */
#تعریف_کن AT91C_EMAC_RLES                 ( ( بیعلامت صحيح ) 0x1 << 2 )  /* (EMAC) */
#تعریف_کن AT91C_EMAC_TGO                  ( ( بیعلامت صحيح ) 0x1 << 3 )  /* (EMAC) Transmit Go */
#تعریف_کن AT91C_EMAC_BEX                  ( ( بیعلامت صحيح ) 0x1 << 4 )  /* (EMAC) Buffers exhausted mid frame */
#تعریف_کن AT91C_EMAC_COMP                 ( ( بیعلامت صحيح ) 0x1 << 5 )  /* (EMAC) */
#تعریف_کن AT91C_EMAC_UND                  ( ( بیعلامت صحيح ) 0x1 << 6 )  /* (EMAC) */
/* -------- EMAC_RSR : (EMAC Offset: 0x20) Receive Status Register -------- */
#تعریف_کن AT91C_EMAC_BNA                  ( ( بیعلامت صحيح ) 0x1 << 0 )  /* (EMAC) */
#تعریف_کن AT91C_EMAC_REC                  ( ( بیعلامت صحيح ) 0x1 << 1 )  /* (EMAC) */
#تعریف_کن AT91C_EMAC_OVR                  ( ( بیعلامت صحيح ) 0x1 << 2 )  /* (EMAC) */
/* -------- EMAC_ISR : (EMAC Offset: 0x24) Interrupt Status Register -------- */
#تعریف_کن AT91C_EMAC_MFD                  ( ( بیعلامت صحيح ) 0x1 << 0 )  /* (EMAC) */
#تعریف_کن AT91C_EMAC_RCOMP                ( ( بیعلامت صحيح ) 0x1 << 1 )  /* (EMAC) */
#تعریف_کن AT91C_EMAC_RXUBR                ( ( بیعلامت صحيح ) 0x1 << 2 )  /* (EMAC) */
#تعریف_کن AT91C_EMAC_TXUBR                ( ( بیعلامت صحيح ) 0x1 << 3 )  /* (EMAC) */
#تعریف_کن AT91C_EMAC_TUNDR                ( ( بیعلامت صحيح ) 0x1 << 4 )  /* (EMAC) */
#تعریف_کن AT91C_EMAC_RLEX                 ( ( بیعلامت صحيح ) 0x1 << 5 )  /* (EMAC) */
#تعریف_کن AT91C_EMAC_TXERR                ( ( بیعلامت صحيح ) 0x1 << 6 )  /* (EMAC) */
#تعریف_کن AT91C_EMAC_TCOMP                ( ( بیعلامت صحيح ) 0x1 << 7 )  /* (EMAC) */
#تعریف_کن AT91C_EMAC_LINK                 ( ( بیعلامت صحيح ) 0x1 << 9 )  /* (EMAC) */
#تعریف_کن AT91C_EMAC_ROVR                 ( ( بیعلامت صحيح ) 0x1 << 10 ) /* (EMAC) */
#تعریف_کن AT91C_EMAC_HRESP                ( ( بیعلامت صحيح ) 0x1 << 11 ) /* (EMAC) */
#تعریف_کن AT91C_EMAC_PFRE                 ( ( بیعلامت صحيح ) 0x1 << 12 ) /* (EMAC) */
#تعریف_کن AT91C_EMAC_PTZ                  ( ( بیعلامت صحيح ) 0x1 << 13 ) /* (EMAC) */
/* -------- EMAC_IER : (EMAC Offset: 0x28) Interrupt Enable Register -------- */
/* -------- EMAC_IDR : (EMAC Offset: 0x2c) Interrupt Disable Register -------- */
/* -------- EMAC_IMR : (EMAC Offset: 0x30) Interrupt Mask Register -------- */
/* -------- EMAC_MAN : (EMAC Offset: 0x34) PHY Maintenance Register -------- */
#تعریف_کن AT91_C_EMAC_داده       ( ( بیعلامت صحيح ) 0xFFFF << 0 )  /* (EMAC) */
#تعریف_کن AT91_C_EMAC_کد       ( ( بیعلامت صحيح ) 0x3 << 16 )    /* (EMAC) */
#تعریف_کن AT91C_EMAC_REGA       ( ( بیعلامت صحيح ) 0x1F << 18 )   /* (EMAC) */
#تعریف_کن AT91C_EMAC_PHYA       ( ( بیعلامت صحيح ) 0x1F << 23 )   /* (EMAC) */
#تعریف_کن AT91C_EMAC_RW         ( ( بیعلامت صحيح ) 0x3 << 28 )    /* (EMAC) */
#تعریف_کن AT91C_EMAC_SOF        ( ( بیعلامت صحيح ) 0x3 << 30 )    /* (EMAC) */
/* -------- EMAC_USRIO : (EMAC Offset: 0xc0) USER Input Output Register -------- */
#تعریف_کن AT91C_EMAC_RMII       ( ( بیعلامت صحيح ) 0x1 << 0 )     /* (EMAC) Reduce MII */
/* -------- EMAC_WOL : (EMAC Offset: 0xc4) Wake On LAN Register -------- */
#تعریف_کن AT91C_EMAC_IP         ( ( بیعلامت صحيح ) 0xFFFF << 0 )  /* (EMAC) ARP request IP address */
#تعریف_کن AT91C_EMAC_MAG        ( ( بیعلامت صحيح ) 0x1 << 16 )    /* (EMAC) Magic packet event enable */
#تعریف_کن AT91C_EMAC_ARP        ( ( بیعلامت صحيح ) 0x1 << 17 )    /* (EMAC) ARP request event enable */
#تعریف_کن AT91C_EMAC_SA1        ( ( بیعلامت صحيح ) 0x1 << 18 )    /* (EMAC) Specific address register 1 event enable */
/* -------- EMAC_REV : (EMAC Offset: 0xfc) Revision Register -------- */
#تعریف_کن AT91C_EMAC_REVREF     ( ( بیعلامت صحيح ) 0xFFFF << 0 )  /* (EMAC) */
#تعریف_کن AT91C_EMAC_PARTREF    ( ( بیعلامت صحيح ) 0xFFFF << 16 ) /* (EMAC) */

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
#تعریف_کن AT91C_ADC_SWRST                    ( ( بیعلامت صحيح ) 0x1 << 0 )   /* (ADC) Software Reset */
#تعریف_کن AT91_C_ADC_شروع                    ( ( بیعلامت صحيح ) 0x1 << 1 )   /* (ADC) Start Conversion */
/* -------- ADC_MR : (ADC Offset: 0x4) ADC Mode Register -------- */
#تعریف_کن AT91C_ADC_TRGEN                    ( ( بیعلامت صحيح ) 0x1 << 0 )   /* (ADC) Trigger Enable */
#تعریف_کن     AT91C_ADC_TRGEN_DIS            ( ( بیعلامت صحيح ) 0x0 )        /* (ADC) Hardware triggers are disabled. Starting a conversion is only possible by software */
#تعریف_کن     AT91C_ADC_TRGEN_EN             ( ( بیعلامت صحيح ) 0x1 )        /* (ADC) Hardware trigger selected by TRGSEL field is enabled. */
#تعریف_کن AT91C_ADC_TRGSEL                   ( ( بیعلامت صحيح ) 0x7 << 1 )   /* (ADC) Trigger Selection */
#تعریف_کن     AT91C_ADC_TRGSEL_TIOA0         ( ( بیعلامت صحيح ) 0x0 << 1 )   /* (ADC) Selected TRGSEL = TIAO0 */
#تعریف_کن     AT91C_ADC_TRGSEL_TIOA1         ( ( بیعلامت صحيح ) 0x1 << 1 )   /* (ADC) Selected TRGSEL = TIAO1 */
#تعریف_کن     AT91C_ADC_TRGSEL_TIOA2         ( ( بیعلامت صحيح ) 0x2 << 1 )   /* (ADC) Selected TRGSEL = TIAO2 */
#تعریف_کن     AT91C_ADC_TRGSEL_TIOA3         ( ( بیعلامت صحيح ) 0x3 << 1 )   /* (ADC) Selected TRGSEL = TIAO3 */
#تعریف_کن     AT91C_ADC_TRGSEL_TIOA4         ( ( بیعلامت صحيح ) 0x4 << 1 )   /* (ADC) Selected TRGSEL = TIAO4 */
#تعریف_کن     AT91C_ADC_TRGSEL_TIOA5         ( ( بیعلامت صحيح ) 0x5 << 1 )   /* (ADC) Selected TRGSEL = TIAO5 */
#تعریف_کن     AT91C_ADC_TRGSEL_EXT           ( ( بیعلامت صحيح ) 0x6 << 1 )   /* (ADC) Selected TRGSEL = External Trigger */
#تعریف_کن AT91C_ADC_LOWRES                   ( ( بیعلامت صحيح ) 0x1 << 4 )   /* (ADC) Resolution. */
#تعریف_کن     AT91_C_ADC_LOWRES_10_بیت        ( ( بیعلامت صحيح ) 0x0 << 4 )   /* (ADC) 10-bit resolution */
#تعریف_کن     AT91_C_ADC_LOWRES_8_بیت         ( ( بیعلامت صحيح ) 0x1 << 4 )   /* (ADC) 8-bit resolution */
#تعریف_کن AT91C_ADC_SLEEP                    ( ( بیعلامت صحيح ) 0x1 << 5 )   /* (ADC) Sleep Mode */
#تعریف_کن     AT91_C_ADC_SLEEP_نرمال_نما    ( ( بیعلامت صحيح ) 0x0 << 5 )   /* (ADC) Normal Mode */
#تعریف_کن     AT91_C_ADC_SLEEP_نما           ( ( بیعلامت صحيح ) 0x1 << 5 )   /* (ADC) Sleep Mode */
#تعریف_کن AT91C_ADC_PRESCAL                  ( ( بیعلامت صحيح ) 0x3F << 8 )  /* (ADC) Prescaler rate selection */
#تعریف_کن AT91C_ADC_STARTUP                  ( ( بیعلامت صحيح ) 0x1F << 16 ) /* (ADC) Startup Time */
#تعریف_کن AT91C_ADC_SHTIM                    ( ( بیعلامت صحيح ) 0xF << 24 )  /* (ADC) Sample & Hold Time */
/* --------     ADC_CHER : (ADC Offset: 0x10) ADC Channel Enable Register -------- */
#تعریف_کن AT91C_ADC_CH0                      ( ( بیعلامت صحيح ) 0x1 << 0 )   /* (ADC) Channel 0 */
#تعریف_کن AT91C_ADC_CH1                      ( ( بیعلامت صحيح ) 0x1 << 1 )   /* (ADC) Channel 1 */
#تعریف_کن AT91C_ADC_CH2                      ( ( بیعلامت صحيح ) 0x1 << 2 )   /* (ADC) Channel 2 */
#تعریف_کن AT91C_ADC_CH3                      ( ( بیعلامت صحيح ) 0x1 << 3 )   /* (ADC) Channel 3 */
#تعریف_کن AT91C_ADC_CH4                      ( ( بیعلامت صحيح ) 0x1 << 4 )   /* (ADC) Channel 4 */
#تعریف_کن AT91C_ADC_CH5                      ( ( بیعلامت صحيح ) 0x1 << 5 )   /* (ADC) Channel 5 */
#تعریف_کن AT91C_ADC_CH6                      ( ( بیعلامت صحيح ) 0x1 << 6 )   /* (ADC) Channel 6 */
#تعریف_کن AT91C_ADC_CH7                      ( ( بیعلامت صحيح ) 0x1 << 7 )   /* (ADC) Channel 7 */
/* --------     ADC_CHDR : (ADC Offset: 0x14) ADC Channel Disable Register -------- */
/* --------     ADC_CHSR : (ADC Offset: 0x18) ADC Channel Status Register -------- */
/* -------- ADC_SR : (ADC Offset: 0x1c) ADC Status Register -------- */
#تعریف_کن AT91C_ADC_EOC0      ( ( بیعلامت صحيح ) 0x1 << 0 )   /* (ADC) End of Conversion */
#تعریف_کن AT91C_ADC_EOC1      ( ( بیعلامت صحيح ) 0x1 << 1 )   /* (ADC) End of Conversion */
#تعریف_کن AT91C_ADC_EOC2      ( ( بیعلامت صحيح ) 0x1 << 2 )   /* (ADC) End of Conversion */
#تعریف_کن AT91C_ADC_EOC3      ( ( بیعلامت صحيح ) 0x1 << 3 )   /* (ADC) End of Conversion */
#تعریف_کن AT91C_ADC_EOC4      ( ( بیعلامت صحيح ) 0x1 << 4 )   /* (ADC) End of Conversion */
#تعریف_کن AT91C_ADC_EOC5      ( ( بیعلامت صحيح ) 0x1 << 5 )   /* (ADC) End of Conversion */
#تعریف_کن AT91C_ADC_EOC6      ( ( بیعلامت صحيح ) 0x1 << 6 )   /* (ADC) End of Conversion */
#تعریف_کن AT91C_ADC_EOC7      ( ( بیعلامت صحيح ) 0x1 << 7 )   /* (ADC) End of Conversion */
#تعریف_کن AT91C_ADC_OVRE0     ( ( بیعلامت صحيح ) 0x1 << 8 )   /* (ADC) Overrun Error */
#تعریف_کن AT91C_ADC_OVRE1     ( ( بیعلامت صحيح ) 0x1 << 9 )   /* (ADC) Overrun Error */
#تعریف_کن AT91C_ADC_OVRE2     ( ( بیعلامت صحيح ) 0x1 << 10 )  /* (ADC) Overrun Error */
#تعریف_کن AT91C_ADC_OVRE3     ( ( بیعلامت صحيح ) 0x1 << 11 )  /* (ADC) Overrun Error */
#تعریف_کن AT91C_ADC_OVRE4     ( ( بیعلامت صحيح ) 0x1 << 12 )  /* (ADC) Overrun Error */
#تعریف_کن AT91C_ADC_OVRE5     ( ( بیعلامت صحيح ) 0x1 << 13 )  /* (ADC) Overrun Error */
#تعریف_کن AT91C_ADC_OVRE6     ( ( بیعلامت صحيح ) 0x1 << 14 )  /* (ADC) Overrun Error */
#تعریف_کن AT91C_ADC_OVRE7     ( ( بیعلامت صحيح ) 0x1 << 15 )  /* (ADC) Overrun Error */
#تعریف_کن AT91C_ADC_DRDY      ( ( بیعلامت صحيح ) 0x1 << 16 )  /* (ADC) Data Ready */
#تعریف_کن AT91C_ADC_GOVRE     ( ( بیعلامت صحيح ) 0x1 << 17 )  /* (ADC) General Overrun */
#تعریف_کن AT91C_ADC_ENDRX     ( ( بیعلامت صحيح ) 0x1 << 18 )  /* (ADC) End of Receiver Transfer */
#تعریف_کن AT91C_ADC_RXBUFF    ( ( بیعلامت صحيح ) 0x1 << 19 )  /* (ADC) RXBUFF Interrupt */
/* -------- ADC_LCDR : (ADC Offset: 0x20) ADC Last Converted Data Register -------- */
#تعریف_کن AT91C_ADC_LDATA     ( ( بیعلامت صحيح ) 0x3FF << 0 ) /* (ADC) Last Data Converted */
/* -------- ADC_IER : (ADC Offset: 0x24) ADC Interrupt Enable Register -------- */
/* -------- ADC_IDR : (ADC Offset: 0x28) ADC Interrupt Disable Register -------- */
/* -------- ADC_IMR : (ADC Offset: 0x2c) ADC Interrupt Mask Register -------- */
/* -------- ADC_CDR0 : (ADC Offset: 0x30) ADC Channel Data Register 0 -------- */
#تعریف_کن AT91_C_ADC_داده    ( ( بیعلامت صحيح ) 0x3FF << 0 )  /* (ADC) Converted Data */
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
#تعریف_کن AT91_C_AES_شروع                 ( ( بیعلامت صحيح ) 0x1 << 0 )   /* (AES) Starts Processing */
#تعریف_کن AT91C_AES_SWRST                 ( ( بیعلامت صحيح ) 0x1 << 8 )   /* (AES) Software Reset */
#تعریف_کن AT91C_AES_LOADSEED              ( ( بیعلامت صحيح ) 0x1 << 16 )  /* (AES) Random Number Generator Seed Loading */
/* -------- AES_MR : (AES Offset: 0x4) Mode Register -------- */
#تعریف_کن AT91C_AES_CIPHER                ( ( بیعلامت صحيح ) 0x1 << 0 )   /* (AES) Processing Mode */
#تعریف_کن AT91C_AES_PROCDLY               ( ( بیعلامت صحيح ) 0xF << 4 )   /* (AES) Processing Delay */
#تعریف_کن AT91C_AES_SMOD                  ( ( بیعلامت صحيح ) 0x3 << 8 )   /* (AES) Start Mode */
#تعریف_کن     AT91C_AES_SMOD_MANUAL       ( ( بیعلامت صحيح ) 0x0 << 8 )   /* (AES) Manual Mode: The START bit in register AES_CR must be set to begin encryption or decryption. */
#تعریف_کن     AT91C_AES_SMOD_AUTO         ( ( بیعلامت صحيح ) 0x1 << 8 )   /* (AES) Auto Mode: no action in AES_CR is necessary (cf datasheet). */
#تعریف_کن     AT91C_AES_SMOD_PDC          ( ( بیعلامت صحيح ) 0x2 << 8 )   /* (AES) PDC Mode (cf datasheet). */
#تعریف_کن AT91C_AES_OPMOD                 ( ( بیعلامت صحيح ) 0x7 << 12 )  /* (AES) Operation Mode */
#تعریف_کن     AT91C_AES_OPMOD_ECB         ( ( بیعلامت صحيح ) 0x0 << 12 )  /* (AES) ECB Electronic CodeBook mode. */
#تعریف_کن     AT91C_AES_OPMOD_CBC         ( ( بیعلامت صحيح ) 0x1 << 12 )  /* (AES) CBC Cipher Block Chaining mode. */
#تعریف_کن     AT91C_AES_OPMOD_OFB         ( ( بیعلامت صحيح ) 0x2 << 12 )  /* (AES) OFB Output Feedback mode. */
#تعریف_کن     AT91C_AES_OPMOD_CFB         ( ( بیعلامت صحيح ) 0x3 << 12 )  /* (AES) CFB Cipher Feedback mode. */
#تعریف_کن     AT91C_AES_OPMOD_CTR         ( ( بیعلامت صحيح ) 0x4 << 12 )  /* (AES) CTR Counter mode. */
#تعریف_کن AT91C_AES_LOD                   ( ( بیعلامت صحيح ) 0x1 << 15 )  /* (AES) Last Output Data Mode */
#تعریف_کن AT91C_AES_CFBS                  ( ( بیعلامت صحيح ) 0x7 << 16 )  /* (AES) Cipher Feedback Data Size */
#تعریف_کن     AT91_C_AES_CFBS_128_بیت      ( ( بیعلامت صحيح ) 0x0 << 16 )  /* (AES) 128-bit. */
#تعریف_کن     AT91_C_AES_CFBS_64_بیت       ( ( بیعلامت صحيح ) 0x1 << 16 )  /* (AES) 64-bit. */
#تعریف_کن     AT91_C_AES_CFBS_32_بیت       ( ( بیعلامت صحيح ) 0x2 << 16 )  /* (AES) 32-bit. */
#تعریف_کن     AT91_C_AES_CFBS_16_بیت       ( ( بیعلامت صحيح ) 0x3 << 16 )  /* (AES) 16-bit. */
#تعریف_کن     AT91_C_AES_CFBS_8_بیت        ( ( بیعلامت صحيح ) 0x4 << 16 )  /* (AES) 8-bit. */
#تعریف_کن AT91C_AES_CKEY                  ( ( بیعلامت صحيح ) 0xF << 20 )  /* (AES) Countermeasure Key */
#تعریف_کن AT91C_AES_CTYPE                 ( ( بیعلامت صحيح ) 0x1F << 24 ) /* (AES) Countermeasure Type */
#تعریف_کن     AT91C_AES_CTYPE_TYPE1_EN    ( ( بیعلامت صحيح ) 0x1 << 24 )  /* (AES) Countermeasure type 1 is enabled. */
#تعریف_کن     AT91C_AES_CTYPE_TYPE2_EN    ( ( بیعلامت صحيح ) 0x2 << 24 )  /* (AES) Countermeasure type 2 is enabled. */
#تعریف_کن     AT91C_AES_CTYPE_TYPE3_EN    ( ( بیعلامت صحيح ) 0x4 << 24 )  /* (AES) Countermeasure type 3 is enabled. */
#تعریف_کن     AT91C_AES_CTYPE_TYPE4_EN    ( ( بیعلامت صحيح ) 0x8 << 24 )  /* (AES) Countermeasure type 4 is enabled. */
#تعریف_کن     AT91C_AES_CTYPE_TYPE5_EN    ( ( بیعلامت صحيح ) 0x10 << 24 ) /* (AES) Countermeasure type 5 is enabled. */
/* -------- AES_IER : (AES Offset: 0x10) Interrupt Enable Register -------- */
#تعریف_کن AT91C_AES_DATRDY                ( ( بیعلامت صحيح ) 0x1 << 0 )   /* (AES) DATRDY */
#تعریف_کن AT91C_AES_ENDRX                 ( ( بیعلامت صحيح ) 0x1 << 1 )   /* (AES) PDC Read Buffer End */
#تعریف_کن AT91C_AES_ENDTX                 ( ( بیعلامت صحيح ) 0x1 << 2 )   /* (AES) PDC Write Buffer End */
#تعریف_کن AT91C_AES_RXBUFF                ( ( بیعلامت صحيح ) 0x1 << 3 )   /* (AES) PDC Read Buffer Full */
#تعریف_کن AT91C_AES_TXBUFE                ( ( بیعلامت صحيح ) 0x1 << 4 )   /* (AES) PDC Write Buffer Empty */
#تعریف_کن AT91C_AES_URAD                  ( ( بیعلامت صحيح ) 0x1 << 8 )   /* (AES) Unspecified Register Access Detection */
/* -------- AES_IDR : (AES Offset: 0x14) Interrupt Disable Register -------- */
/* -------- AES_IMR : (AES Offset: 0x18) Interrupt Mask Register -------- */
/* -------- AES_ISR : (AES Offset: 0x1c) Interrupt Status Register -------- */
#تعریف_کن AT91C_AES_URAT                              ( ( بیعلامت صحيح ) 0x7 << 12 ) /* (AES) Unspecified Register Access Type Status */
#تعریف_کن     AT91_C_AES_URAT_درون_DAT_WRITE_DATPROC     ( ( بیعلامت صحيح ) 0x0 << 12 ) /* (AES) Input data register written during the data processing in PDC mode. */
#تعریف_کن     AT91_C_AES_URAT_بیرون_DAT_READ_DATPROC     ( ( بیعلامت صحيح ) 0x1 << 12 ) /* (AES) Output data register read during the data processing. */
#تعریف_کن     AT91C_AES_URAT_MODEREG_WRITE_DATPROC    ( ( بیعلامت صحيح ) 0x2 << 12 ) /* (AES) Mode register written during the data processing. */
#تعریف_کن     AT91_C_AES_URAT_بیرون_DAT_READ_SUBKEY      ( ( بیعلامت صحيح ) 0x3 << 12 ) /* (AES) Output data register read during the sub-keys generation. */
#تعریف_کن     AT91C_AES_URAT_MODEREG_WRITE_SUBKEY     ( ( بیعلامت صحيح ) 0x4 << 12 ) /* (AES) Mode register written during the sub-keys generation. */
#تعریف_کن     AT91C_AES_URAT_WO_REG_READ              ( ( بیعلامت صحيح ) 0x5 << 12 ) /* (AES) Write-only register read access. */

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
#تعریف_کن AT91_C_TDES_شروع              ( ( بیعلامت صحيح ) 0x1 << 0 )  /* (TDES) Starts Processing */
#تعریف_کن AT91C_TDES_SWRST              ( ( بیعلامت صحيح ) 0x1 << 8 )  /* (TDES) Software Reset */
/* -------- TDES_MR : (TDES Offset: 0x4) Mode Register -------- */
#تعریف_کن AT91C_TDES_CIPHER             ( ( بیعلامت صحيح ) 0x1 << 0 )  /* (TDES) Processing Mode */
#تعریف_کن AT91C_TDES_TDESMOD            ( ( بیعلامت صحيح ) 0x1 << 1 )  /* (TDES) Single or Triple DES Mode */
#تعریف_کن AT91C_TDES_KEYMOD             ( ( بیعلامت صحيح ) 0x1 << 4 )  /* (TDES) Key Mode */
#تعریف_کن AT91C_TDES_SMOD               ( ( بیعلامت صحيح ) 0x3 << 8 )  /* (TDES) Start Mode */
#تعریف_کن     AT91C_TDES_SMOD_MANUAL    ( ( بیعلامت صحيح ) 0x0 << 8 )  /* (TDES) Manual Mode: The START bit in register TDES_CR must be set to begin encryption or decryption. */
#تعریف_کن     AT91C_TDES_SMOD_AUTO      ( ( بیعلامت صحيح ) 0x1 << 8 )  /* (TDES) Auto Mode: no action in TDES_CR is necessary (cf datasheet). */
#تعریف_کن     AT91C_TDES_SMOD_PDC       ( ( بیعلامت صحيح ) 0x2 << 8 )  /* (TDES) PDC Mode (cf datasheet). */
#تعریف_کن AT91C_TDES_OPMOD              ( ( بیعلامت صحيح ) 0x3 << 12 ) /* (TDES) Operation Mode */
#تعریف_کن     AT91C_TDES_OPMOD_ECB      ( ( بیعلامت صحيح ) 0x0 << 12 ) /* (TDES) ECB Electronic CodeBook mode. */
#تعریف_کن     AT91C_TDES_OPMOD_CBC      ( ( بیعلامت صحيح ) 0x1 << 12 ) /* (TDES) CBC Cipher Block Chaining mode. */
#تعریف_کن     AT91C_TDES_OPMOD_OFB      ( ( بیعلامت صحيح ) 0x2 << 12 ) /* (TDES) OFB Output Feedback mode. */
#تعریف_کن     AT91C_TDES_OPMOD_CFB      ( ( بیعلامت صحيح ) 0x3 << 12 ) /* (TDES) CFB Cipher Feedback mode. */
#تعریف_کن AT91C_TDES_LOD                ( ( بیعلامت صحيح ) 0x1 << 15 ) /* (TDES) Last Output Data Mode */
#تعریف_کن AT91C_TDES_CFBS               ( ( بیعلامت صحيح ) 0x3 << 16 ) /* (TDES) Cipher Feedback Data Size */
#تعریف_کن     AT91_C_TDES_CFBS_64_بیت    ( ( بیعلامت صحيح ) 0x0 << 16 ) /* (TDES) 64-bit. */
#تعریف_کن     AT91_C_TDES_CFBS_32_بیت    ( ( بیعلامت صحيح ) 0x1 << 16 ) /* (TDES) 32-bit. */
#تعریف_کن     AT91_C_TDES_CFBS_16_بیت    ( ( بیعلامت صحيح ) 0x2 << 16 ) /* (TDES) 16-bit. */
#تعریف_کن     AT91_C_TDES_CFBS_8_بیت     ( ( بیعلامت صحيح ) 0x3 << 16 ) /* (TDES) 8-bit. */
/* -------- TDES_IER : (TDES Offset: 0x10) Interrupt Enable Register -------- */
#تعریف_کن AT91C_TDES_DATRDY             ( ( بیعلامت صحيح ) 0x1 << 0 )  /* (TDES) DATRDY */
#تعریف_کن AT91C_TDES_ENDRX              ( ( بیعلامت صحيح ) 0x1 << 1 )  /* (TDES) PDC Read Buffer End */
#تعریف_کن AT91C_TDES_ENDTX              ( ( بیعلامت صحيح ) 0x1 << 2 )  /* (TDES) PDC Write Buffer End */
#تعریف_کن AT91C_TDES_RXBUFF             ( ( بیعلامت صحيح ) 0x1 << 3 )  /* (TDES) PDC Read Buffer Full */
#تعریف_کن AT91C_TDES_TXBUFE             ( ( بیعلامت صحيح ) 0x1 << 4 )  /* (TDES) PDC Write Buffer Empty */
#تعریف_کن AT91C_TDES_URAD               ( ( بیعلامت صحيح ) 0x1 << 8 )  /* (TDES) Unspecified Register Access Detection */
/* -------- TDES_IDR : (TDES Offset: 0x14) Interrupt Disable Register -------- */
/* -------- TDES_IMR : (TDES Offset: 0x18) Interrupt Mask Register -------- */
/* -------- TDES_ISR : (TDES Offset: 0x1c) Interrupt Status Register -------- */
#تعریف_کن AT91C_TDES_URAT                              ( ( بیعلامت صحيح ) 0x3 << 12 ) /* (TDES) Unspecified Register Access Type Status */
#تعریف_کن     AT91_C_TDES_URAT_درون_DAT_WRITE_DATPROC     ( ( بیعلامت صحيح ) 0x0 << 12 ) /* (TDES) Input data register written during the data processing in PDC mode. */
#تعریف_کن     AT91_C_TDES_URAT_بیرون_DAT_READ_DATPROC     ( ( بیعلامت صحيح ) 0x1 << 12 ) /* (TDES) Output data register read during the data processing. */
#تعریف_کن     AT91C_TDES_URAT_MODEREG_WRITE_DATPROC    ( ( بیعلامت صحيح ) 0x2 << 12 ) /* (TDES) Mode register written during the data processing. */
#تعریف_کن     AT91C_TDES_URAT_WO_REG_READ              ( ( بیعلامت صحيح ) 0x3 << 12 ) /* (TDES) Write-only register read access. */

/* ***************************************************************************** */
/*               REGISTER ADDRESS DEFINITION FOR AT91SAM7X256 */
/* ***************************************************************************** */
/* ========== Register definition for SYS peripheral ========== */
/* ========== Register definition for AIC peripheral ========== */
#تعریف_کن AT91C_AIC_IVR              ( ( AT91_REG * ) 0xFFFFF100 ) /* (AIC) IRQ Vector Register */
#تعریف_کن AT91C_AIC_SMR              ( ( AT91_REG * ) 0xFFFFF000 ) /* (AIC) Source Mode Register */
#تعریف_کن AT91C_AIC_FVR              ( ( AT91_REG * ) 0xFFFFF104 ) /* (AIC) FIQ Vector Register */
#تعریف_کن AT91C_AIC_DCR              ( ( AT91_REG * ) 0xFFFFF138 ) /* (AIC) Debug Control Register (Protect) */
#تعریف_کن AT91C_AIC_EOICR            ( ( AT91_REG * ) 0xFFFFF130 ) /* (AIC) End of Interrupt Command Register */
#تعریف_کن AT91C_AIC_SVR              ( ( AT91_REG * ) 0xFFFFF080 ) /* (AIC) Source Vector Register */
#تعریف_کن AT91C_AIC_FFSR             ( ( AT91_REG * ) 0xFFFFF148 ) /* (AIC) Fast Forcing Status Register */
#تعریف_کن AT91C_AIC_ICCR             ( ( AT91_REG * ) 0xFFFFF128 ) /* (AIC) Interrupt Clear Command Register */
#تعریف_کن AT91C_AIC_ISR              ( ( AT91_REG * ) 0xFFFFF108 ) /* (AIC) Interrupt Status Register */
#تعریف_کن AT91C_AIC_IMR              ( ( AT91_REG * ) 0xFFFFF110 ) /* (AIC) Interrupt Mask Register */
#تعریف_کن AT91C_AIC_IPR              ( ( AT91_REG * ) 0xFFFFF10C ) /* (AIC) Interrupt Pending Register */
#تعریف_کن AT91C_AIC_FFER             ( ( AT91_REG * ) 0xFFFFF140 ) /* (AIC) Fast Forcing Enable Register */
#تعریف_کن AT91C_AIC_IECR             ( ( AT91_REG * ) 0xFFFFF120 ) /* (AIC) Interrupt Enable Command Register */
#تعریف_کن AT91C_AIC_ISCR             ( ( AT91_REG * ) 0xFFFFF12C ) /* (AIC) Interrupt Set Command Register */
#تعریف_کن AT91C_AIC_FFDR             ( ( AT91_REG * ) 0xFFFFF144 ) /* (AIC) Fast Forcing Disable Register */
#تعریف_کن AT91C_AIC_CISR             ( ( AT91_REG * ) 0xFFFFF114 ) /* (AIC) Core Interrupt Status Register */
#تعریف_کن AT91C_AIC_IDCR             ( ( AT91_REG * ) 0xFFFFF124 ) /* (AIC) Interrupt Disable Command Register */
#تعریف_کن AT91C_AIC_SPU              ( ( AT91_REG * ) 0xFFFFF134 ) /* (AIC) Spurious Vector Register */
/* ========== Register definition for PDC_DBGU peripheral ========== */
#تعریف_کن AT91C_DBGU_TCR             ( ( AT91_REG * ) 0xFFFFF30C ) /* (PDC_DBGU) Transmit Counter Register */
#تعریف_کن AT91C_DBGU_RNPR            ( ( AT91_REG * ) 0xFFFFF310 ) /* (PDC_DBGU) Receive Next Pointer Register */
#تعریف_کن AT91C_DBGU_TNPR            ( ( AT91_REG * ) 0xFFFFF318 ) /* (PDC_DBGU) Transmit Next Pointer Register */
#تعریف_کن AT91C_DBGU_TPR             ( ( AT91_REG * ) 0xFFFFF308 ) /* (PDC_DBGU) Transmit Pointer Register */
#تعریف_کن AT91C_DBGU_RPR             ( ( AT91_REG * ) 0xFFFFF300 ) /* (PDC_DBGU) Receive Pointer Register */
#تعریف_کن AT91C_DBGU_RCR             ( ( AT91_REG * ) 0xFFFFF304 ) /* (PDC_DBGU) Receive Counter Register */
#تعریف_کن AT91C_DBGU_RNCR            ( ( AT91_REG * ) 0xFFFFF314 ) /* (PDC_DBGU) Receive Next Counter Register */
#تعریف_کن AT91C_DBGU_PTCR            ( ( AT91_REG * ) 0xFFFFF320 ) /* (PDC_DBGU) PDC Transfer Control Register */
#تعریف_کن AT91C_DBGU_PTSR            ( ( AT91_REG * ) 0xFFFFF324 ) /* (PDC_DBGU) PDC Transfer Status Register */
#تعریف_کن AT91C_DBGU_TNCR            ( ( AT91_REG * ) 0xFFFFF31C ) /* (PDC_DBGU) Transmit Next Counter Register */
/* ========== Register definition for DBGU peripheral ========== */
#تعریف_کن AT91C_DBGU_EXID            ( ( AT91_REG * ) 0xFFFFF244 ) /* (DBGU) Chip ID Extension Register */
#تعریف_کن AT91C_DBGU_BRGR            ( ( AT91_REG * ) 0xFFFFF220 ) /* (DBGU) Baud Rate Generator Register */
#تعریف_کن AT91C_DBGU_IDR             ( ( AT91_REG * ) 0xFFFFF20C ) /* (DBGU) Interrupt Disable Register */
#تعریف_کن AT91C_DBGU_CSR             ( ( AT91_REG * ) 0xFFFFF214 ) /* (DBGU) Channel Status Register */
#تعریف_کن AT91C_DBGU_CIDR            ( ( AT91_REG * ) 0xFFFFF240 ) /* (DBGU) Chip ID Register */
#تعریف_کن AT91C_DBGU_MR              ( ( AT91_REG * ) 0xFFFFF204 ) /* (DBGU) Mode Register */
#تعریف_کن AT91C_DBGU_IMR             ( ( AT91_REG * ) 0xFFFFF210 ) /* (DBGU) Interrupt Mask Register */
#تعریف_کن AT91C_DBGU_CR              ( ( AT91_REG * ) 0xFFFFF200 ) /* (DBGU) Control Register */
#تعریف_کن AT91C_DBGU_FNTR            ( ( AT91_REG * ) 0xFFFFF248 ) /* (DBGU) Force NTRST Register */
#تعریف_کن AT91C_DBGU_THR             ( ( AT91_REG * ) 0xFFFFF21C ) /* (DBGU) Transmitter Holding Register */
#تعریف_کن AT91C_DBGU_RHR             ( ( AT91_REG * ) 0xFFFFF218 ) /* (DBGU) Receiver Holding Register */
#تعریف_کن AT91C_DBGU_IER             ( ( AT91_REG * ) 0xFFFFF208 ) /* (DBGU) Interrupt Enable Register */
/* ========== Register definition for PIOA peripheral ========== */
#تعریف_کن AT91C_PIOA_ODR             ( ( AT91_REG * ) 0xFFFFF414 ) /* (PIOA) Output Disable Registerr */
#تعریف_کن AT91C_PIOA_SODR            ( ( AT91_REG * ) 0xFFFFF430 ) /* (PIOA) Set Output Data Register */
#تعریف_کن AT91C_PIOA_ISR             ( ( AT91_REG * ) 0xFFFFF44C ) /* (PIOA) Interrupt Status Register */
#تعریف_کن AT91C_PIOA_ABSR            ( ( AT91_REG * ) 0xFFFFF478 ) /* (PIOA) AB Select Status Register */
#تعریف_کن AT91C_PIOA_IER             ( ( AT91_REG * ) 0xFFFFF440 ) /* (PIOA) Interrupt Enable Register */
#تعریف_کن AT91C_PIOA_PPUDR           ( ( AT91_REG * ) 0xFFFFF460 ) /* (PIOA) Pull-up Disable Register */
#تعریف_کن AT91C_PIOA_IMR             ( ( AT91_REG * ) 0xFFFFF448 ) /* (PIOA) Interrupt Mask Register */
#تعریف_کن AT91_C_PIOA_در_هر             ( ( AT91_REG * ) 0xFFFFF400 ) /* (PIOA) PIO Enable Register */
#تعریف_کن AT91C_PIOA_IFDR            ( ( AT91_REG * ) 0xFFFFF424 ) /* (PIOA) Input Filter Disable Register */
#تعریف_کن AT91C_PIOA_OWDR            ( ( AT91_REG * ) 0xFFFFF4A4 ) /* (PIOA) Output Write Disable Register */
#تعریف_کن AT91C_PIOA_MDSR            ( ( AT91_REG * ) 0xFFFFF458 ) /* (PIOA) Multi-driver Status Register */
#تعریف_کن AT91C_PIOA_IDR             ( ( AT91_REG * ) 0xFFFFF444 ) /* (PIOA) Interrupt Disable Register */
#تعریف_کن AT91C_PIOA_ODSR            ( ( AT91_REG * ) 0xFFFFF438 ) /* (PIOA) Output Data Status Register */
#تعریف_کن AT91C_PIOA_PPUSR           ( ( AT91_REG * ) 0xFFFFF468 ) /* (PIOA) Pull-up Status Register */
#تعریف_کن AT91C_PIOA_OWSR            ( ( AT91_REG * ) 0xFFFFF4A8 ) /* (PIOA) Output Write Status Register */
#تعریف_کن AT91C_PIOA_BSR             ( ( AT91_REG * ) 0xFFFFF474 ) /* (PIOA) Select B Register */
#تعریف_کن AT91C_PIOA_OWER            ( ( AT91_REG * ) 0xFFFFF4A0 ) /* (PIOA) Output Write Enable Register */
#تعریف_کن AT91C_PIOA_IFER            ( ( AT91_REG * ) 0xFFFFF420 ) /* (PIOA) Input Filter Enable Register */
#تعریف_کن AT91C_PIOA_PDSR            ( ( AT91_REG * ) 0xFFFFF43C ) /* (PIOA) Pin Data Status Register */
#تعریف_کن AT91C_PIOA_PPUER           ( ( AT91_REG * ) 0xFFFFF464 ) /* (PIOA) Pull-up Enable Register */
#تعریف_کن AT91C_PIOA_OSR             ( ( AT91_REG * ) 0xFFFFF418 ) /* (PIOA) Output Status Register */
#تعریف_کن AT91C_PIOA_ASR             ( ( AT91_REG * ) 0xFFFFF470 ) /* (PIOA) Select A Register */
#تعریف_کن AT91C_PIOA_MDDR            ( ( AT91_REG * ) 0xFFFFF454 ) /* (PIOA) Multi-driver Disable Register */
#تعریف_کن AT91C_PIOA_CODR            ( ( AT91_REG * ) 0xFFFFF434 ) /* (PIOA) Clear Output Data Register */
#تعریف_کن AT91C_PIOA_MDER            ( ( AT91_REG * ) 0xFFFFF450 ) /* (PIOA) Multi-driver Enable Register */
#تعریف_کن AT91C_PIOA_PDR             ( ( AT91_REG * ) 0xFFFFF404 ) /* (PIOA) PIO Disable Register */
#تعریف_کن AT91C_PIOA_IFSR            ( ( AT91_REG * ) 0xFFFFF428 ) /* (PIOA) Input Filter Status Register */
#تعریف_کن AT91C_PIOA_OER             ( ( AT91_REG * ) 0xFFFFF410 ) /* (PIOA) Output Enable Register */
#تعریف_کن AT91C_PIOA_PSR             ( ( AT91_REG * ) 0xFFFFF408 ) /* (PIOA) PIO Status Register */
/* ========== Register definition for PIOB peripheral ========== */
#تعریف_کن AT91C_PIOB_OWDR            ( ( AT91_REG * ) 0xFFFFF6A4 ) /* (PIOB) Output Write Disable Register */
#تعریف_کن AT91C_PIOB_MDER            ( ( AT91_REG * ) 0xFFFFF650 ) /* (PIOB) Multi-driver Enable Register */
#تعریف_کن AT91C_PIOB_PPUSR           ( ( AT91_REG * ) 0xFFFFF668 ) /* (PIOB) Pull-up Status Register */
#تعریف_کن AT91C_PIOB_IMR             ( ( AT91_REG * ) 0xFFFFF648 ) /* (PIOB) Interrupt Mask Register */
#تعریف_کن AT91C_PIOB_ASR             ( ( AT91_REG * ) 0xFFFFF670 ) /* (PIOB) Select A Register */
#تعریف_کن AT91C_PIOB_PPUDR           ( ( AT91_REG * ) 0xFFFFF660 ) /* (PIOB) Pull-up Disable Register */
#تعریف_کن AT91C_PIOB_PSR             ( ( AT91_REG * ) 0xFFFFF608 ) /* (PIOB) PIO Status Register */
#تعریف_کن AT91C_PIOB_IER             ( ( AT91_REG * ) 0xFFFFF640 ) /* (PIOB) Interrupt Enable Register */
#تعریف_کن AT91C_PIOB_CODR            ( ( AT91_REG * ) 0xFFFFF634 ) /* (PIOB) Clear Output Data Register */
#تعریف_کن AT91C_PIOB_OWER            ( ( AT91_REG * ) 0xFFFFF6A0 ) /* (PIOB) Output Write Enable Register */
#تعریف_کن AT91C_PIOB_ABSR            ( ( AT91_REG * ) 0xFFFFF678 ) /* (PIOB) AB Select Status Register */
#تعریف_کن AT91C_PIOB_IFDR            ( ( AT91_REG * ) 0xFFFFF624 ) /* (PIOB) Input Filter Disable Register */
#تعریف_کن AT91C_PIOB_PDSR            ( ( AT91_REG * ) 0xFFFFF63C ) /* (PIOB) Pin Data Status Register */
#تعریف_کن AT91C_PIOB_IDR             ( ( AT91_REG * ) 0xFFFFF644 ) /* (PIOB) Interrupt Disable Register */
#تعریف_کن AT91C_PIOB_OWSR            ( ( AT91_REG * ) 0xFFFFF6A8 ) /* (PIOB) Output Write Status Register */
#تعریف_کن AT91C_PIOB_PDR             ( ( AT91_REG * ) 0xFFFFF604 ) /* (PIOB) PIO Disable Register */
#تعریف_کن AT91C_PIOB_ODR             ( ( AT91_REG * ) 0xFFFFF614 ) /* (PIOB) Output Disable Registerr */
#تعریف_کن AT91C_PIOB_IFSR            ( ( AT91_REG * ) 0xFFFFF628 ) /* (PIOB) Input Filter Status Register */
#تعریف_کن AT91C_PIOB_PPUER           ( ( AT91_REG * ) 0xFFFFF664 ) /* (PIOB) Pull-up Enable Register */
#تعریف_کن AT91C_PIOB_SODR            ( ( AT91_REG * ) 0xFFFFF630 ) /* (PIOB) Set Output Data Register */
#تعریف_کن AT91C_PIOB_ISR             ( ( AT91_REG * ) 0xFFFFF64C ) /* (PIOB) Interrupt Status Register */
#تعریف_کن AT91C_PIOB_ODSR            ( ( AT91_REG * ) 0xFFFFF638 ) /* (PIOB) Output Data Status Register */
#تعریف_کن AT91C_PIOB_OSR             ( ( AT91_REG * ) 0xFFFFF618 ) /* (PIOB) Output Status Register */
#تعریف_کن AT91C_PIOB_MDSR            ( ( AT91_REG * ) 0xFFFFF658 ) /* (PIOB) Multi-driver Status Register */
#تعریف_کن AT91C_PIOB_IFER            ( ( AT91_REG * ) 0xFFFFF620 ) /* (PIOB) Input Filter Enable Register */
#تعریف_کن AT91C_PIOB_BSR             ( ( AT91_REG * ) 0xFFFFF674 ) /* (PIOB) Select B Register */
#تعریف_کن AT91C_PIOB_MDDR            ( ( AT91_REG * ) 0xFFFFF654 ) /* (PIOB) Multi-driver Disable Register */
#تعریف_کن AT91C_PIOB_OER             ( ( AT91_REG * ) 0xFFFFF610 ) /* (PIOB) Output Enable Register */
#تعریف_کن AT91_C_PIOB_در_هر             ( ( AT91_REG * ) 0xFFFFF600 ) /* (PIOB) PIO Enable Register */
/* ========== Register definition for CKGR peripheral ========== */
#تعریف_کن AT91C_CKGR_MOR             ( ( AT91_REG * ) 0xFFFFFC20 ) /* (CKGR) Main Oscillator Register */
#تعریف_کن AT91C_CKGR_PLLR            ( ( AT91_REG * ) 0xFFFFFC2C ) /* (CKGR) PLL Register */
#تعریف_کن AT91C_CKGR_MCFR            ( ( AT91_REG * ) 0xFFFFFC24 ) /* (CKGR) Main Clock  Frequency Register */
/* ========== Register definition for PMC peripheral ========== */
#تعریف_کن AT91C_PMC_IDR              ( ( AT91_REG * ) 0xFFFFFC64 ) /* (PMC) Interrupt Disable Register */
#تعریف_کن AT91C_PMC_MOR              ( ( AT91_REG * ) 0xFFFFFC20 ) /* (PMC) Main Oscillator Register */
#تعریف_کن AT91C_PMC_PLLR             ( ( AT91_REG * ) 0xFFFFFC2C ) /* (PMC) PLL Register */
#تعریف_کن AT91C_PMC_PCER             ( ( AT91_REG * ) 0xFFFFFC10 ) /* (PMC) Peripheral Clock Enable Register */
#تعریف_کن AT91C_PMC_PCKR             ( ( AT91_REG * ) 0xFFFFFC40 ) /* (PMC) Programmable Clock Register */
#تعریف_کن AT91C_PMC_MCKR             ( ( AT91_REG * ) 0xFFFFFC30 ) /* (PMC) Master Clock Register */
#تعریف_کن AT91C_PMC_SCDR             ( ( AT91_REG * ) 0xFFFFFC04 ) /* (PMC) System Clock Disable Register */
#تعریف_کن AT91C_PMC_PCDR             ( ( AT91_REG * ) 0xFFFFFC14 ) /* (PMC) Peripheral Clock Disable Register */
#تعریف_کن AT91C_PMC_SCSR             ( ( AT91_REG * ) 0xFFFFFC08 ) /* (PMC) System Clock Status Register */
#تعریف_کن AT91C_PMC_PCSR             ( ( AT91_REG * ) 0xFFFFFC18 ) /* (PMC) Peripheral Clock Status Register */
#تعریف_کن AT91C_PMC_MCFR             ( ( AT91_REG * ) 0xFFFFFC24 ) /* (PMC) Main Clock  Frequency Register */
#تعریف_کن AT91C_PMC_SCER             ( ( AT91_REG * ) 0xFFFFFC00 ) /* (PMC) System Clock Enable Register */
#تعریف_کن AT91C_PMC_IMR              ( ( AT91_REG * ) 0xFFFFFC6C ) /* (PMC) Interrupt Mask Register */
#تعریف_کن AT91C_PMC_IER              ( ( AT91_REG * ) 0xFFFFFC60 ) /* (PMC) Interrupt Enable Register */
#تعریف_کن AT91C_PMC_SR               ( ( AT91_REG * ) 0xFFFFFC68 ) /* (PMC) Status Register */
/* ========== Register definition for RSTC peripheral ========== */
#تعریف_کن AT91C_RSTC_RCR             ( ( AT91_REG * ) 0xFFFFFD00 ) /* (RSTC) Reset Control Register */
#تعریف_کن AT91C_RSTC_RMR             ( ( AT91_REG * ) 0xFFFFFD08 ) /* (RSTC) Reset Mode Register */
#تعریف_کن AT91C_RSTC_RSR             ( ( AT91_REG * ) 0xFFFFFD04 ) /* (RSTC) Reset Status Register */
/* ========== Register definition for RTTC peripheral ========== */
#تعریف_کن AT91C_RTTC_RTSR            ( ( AT91_REG * ) 0xFFFFFD2C ) /* (RTTC) Real-time Status Register */
#تعریف_کن AT91C_RTTC_RTMR            ( ( AT91_REG * ) 0xFFFFFD20 ) /* (RTTC) Real-time Mode Register */
#تعریف_کن AT91C_RTTC_RTVR            ( ( AT91_REG * ) 0xFFFFFD28 ) /* (RTTC) Real-time Value Register */
#تعریف_کن AT91C_RTTC_RTAR            ( ( AT91_REG * ) 0xFFFFFD24 ) /* (RTTC) Real-time Alarm Register */
/* ========== Register definition for PITC peripheral ========== */
#تعریف_کن AT91C_PITC_PIVR            ( ( AT91_REG * ) 0xFFFFFD38 ) /* (PITC) Period Interval Value Register */
#تعریف_کن AT91C_PITC_PISR            ( ( AT91_REG * ) 0xFFFFFD34 ) /* (PITC) Period Interval Status Register */
#تعریف_کن AT91C_PITC_PIIR            ( ( AT91_REG * ) 0xFFFFFD3C ) /* (PITC) Period Interval Image Register */
#تعریف_کن AT91C_PITC_PIMR            ( ( AT91_REG * ) 0xFFFFFD30 ) /* (PITC) Period Interval Mode Register */
/* ========== Register definition for WDTC peripheral ========== */
#تعریف_کن AT91C_WDTC_WDCR            ( ( AT91_REG * ) 0xFFFFFD40 ) /* (WDTC) Watchdog Control Register */
#تعریف_کن AT91C_WDTC_WDSR            ( ( AT91_REG * ) 0xFFFFFD48 ) /* (WDTC) Watchdog Status Register */
#تعریف_کن AT91C_WDTC_WDMR            ( ( AT91_REG * ) 0xFFFFFD44 ) /* (WDTC) Watchdog Mode Register */
/* ========== Register definition for VREG peripheral ========== */
#تعریف_کن AT91C_VREG_MR              ( ( AT91_REG * ) 0xFFFFFD60 ) /* (VREG) Voltage Regulator Mode Register */
/* ========== Register definition for MC peripheral ========== */
#تعریف_کن AT91C_MC_ASR               ( ( AT91_REG * ) 0xFFFFFF04 ) /* (MC) MC Abort Status Register */
#تعریف_کن AT91C_MC_RCR               ( ( AT91_REG * ) 0xFFFFFF00 ) /* (MC) MC Remap Control Register */
#تعریف_کن AT91C_MC_FCR               ( ( AT91_REG * ) 0xFFFFFF64 ) /* (MC) MC Flash Command Register */
#تعریف_کن AT91C_MC_AASR              ( ( AT91_REG * ) 0xFFFFFF08 ) /* (MC) MC Abort Address Status Register */
#تعریف_کن AT91C_MC_FSR               ( ( AT91_REG * ) 0xFFFFFF68 ) /* (MC) MC Flash Status Register */
#تعریف_کن AT91C_MC_FMR               ( ( AT91_REG * ) 0xFFFFFF60 ) /* (MC) MC Flash Mode Register */
/* ========== Register definition for PDC_SPI1 peripheral ========== */
#تعریف_کن AT91C_SPI1_PTCR            ( ( AT91_REG * ) 0xFFFE4120 ) /* (PDC_SPI1) PDC Transfer Control Register */
#تعریف_کن AT91C_SPI1_RPR             ( ( AT91_REG * ) 0xFFFE4100 ) /* (PDC_SPI1) Receive Pointer Register */
#تعریف_کن AT91C_SPI1_TNCR            ( ( AT91_REG * ) 0xFFFE411C ) /* (PDC_SPI1) Transmit Next Counter Register */
#تعریف_کن AT91C_SPI1_TPR             ( ( AT91_REG * ) 0xFFFE4108 ) /* (PDC_SPI1) Transmit Pointer Register */
#تعریف_کن AT91C_SPI1_TNPR            ( ( AT91_REG * ) 0xFFFE4118 ) /* (PDC_SPI1) Transmit Next Pointer Register */
#تعریف_کن AT91C_SPI1_TCR             ( ( AT91_REG * ) 0xFFFE410C ) /* (PDC_SPI1) Transmit Counter Register */
#تعریف_کن AT91C_SPI1_RCR             ( ( AT91_REG * ) 0xFFFE4104 ) /* (PDC_SPI1) Receive Counter Register */
#تعریف_کن AT91C_SPI1_RNPR            ( ( AT91_REG * ) 0xFFFE4110 ) /* (PDC_SPI1) Receive Next Pointer Register */
#تعریف_کن AT91C_SPI1_RNCR            ( ( AT91_REG * ) 0xFFFE4114 ) /* (PDC_SPI1) Receive Next Counter Register */
#تعریف_کن AT91C_SPI1_PTSR            ( ( AT91_REG * ) 0xFFFE4124 ) /* (PDC_SPI1) PDC Transfer Status Register */
/* ========== Register definition for SPI1 peripheral ========== */
#تعریف_کن AT91C_SPI1_IMR             ( ( AT91_REG * ) 0xFFFE401C ) /* (SPI1) Interrupt Mask Register */
#تعریف_کن AT91C_SPI1_IER             ( ( AT91_REG * ) 0xFFFE4014 ) /* (SPI1) Interrupt Enable Register */
#تعریف_کن AT91C_SPI1_MR              ( ( AT91_REG * ) 0xFFFE4004 ) /* (SPI1) Mode Register */
#تعریف_کن AT91C_SPI1_RDR             ( ( AT91_REG * ) 0xFFFE4008 ) /* (SPI1) Receive Data Register */
#تعریف_کن AT91C_SPI1_IDR             ( ( AT91_REG * ) 0xFFFE4018 ) /* (SPI1) Interrupt Disable Register */
#تعریف_کن AT91C_SPI1_SR              ( ( AT91_REG * ) 0xFFFE4010 ) /* (SPI1) Status Register */
#تعریف_کن AT91C_SPI1_TDR             ( ( AT91_REG * ) 0xFFFE400C ) /* (SPI1) Transmit Data Register */
#تعریف_کن AT91C_SPI1_CR              ( ( AT91_REG * ) 0xFFFE4000 ) /* (SPI1) Control Register */
#تعریف_کن AT91C_SPI1_CSR             ( ( AT91_REG * ) 0xFFFE4030 ) /* (SPI1) Chip Select Register */
/* ========== Register definition for PDC_SPI0 peripheral ========== */
#تعریف_کن AT91C_SPI0_PTCR            ( ( AT91_REG * ) 0xFFFE0120 ) /* (PDC_SPI0) PDC Transfer Control Register */
#تعریف_کن AT91C_SPI0_TPR             ( ( AT91_REG * ) 0xFFFE0108 ) /* (PDC_SPI0) Transmit Pointer Register */
#تعریف_کن AT91C_SPI0_TCR             ( ( AT91_REG * ) 0xFFFE010C ) /* (PDC_SPI0) Transmit Counter Register */
#تعریف_کن AT91C_SPI0_RCR             ( ( AT91_REG * ) 0xFFFE0104 ) /* (PDC_SPI0) Receive Counter Register */
#تعریف_کن AT91C_SPI0_PTSR            ( ( AT91_REG * ) 0xFFFE0124 ) /* (PDC_SPI0) PDC Transfer Status Register */
#تعریف_کن AT91C_SPI0_RNPR            ( ( AT91_REG * ) 0xFFFE0110 ) /* (PDC_SPI0) Receive Next Pointer Register */
#تعریف_کن AT91C_SPI0_RPR             ( ( AT91_REG * ) 0xFFFE0100 ) /* (PDC_SPI0) Receive Pointer Register */
#تعریف_کن AT91C_SPI0_TNCR            ( ( AT91_REG * ) 0xFFFE011C ) /* (PDC_SPI0) Transmit Next Counter Register */
#تعریف_کن AT91C_SPI0_RNCR            ( ( AT91_REG * ) 0xFFFE0114 ) /* (PDC_SPI0) Receive Next Counter Register */
#تعریف_کن AT91C_SPI0_TNPR            ( ( AT91_REG * ) 0xFFFE0118 ) /* (PDC_SPI0) Transmit Next Pointer Register */
/* ========== Register definition for SPI0 peripheral ========== */
#تعریف_کن AT91C_SPI0_IER             ( ( AT91_REG * ) 0xFFFE0014 ) /* (SPI0) Interrupt Enable Register */
#تعریف_کن AT91C_SPI0_SR              ( ( AT91_REG * ) 0xFFFE0010 ) /* (SPI0) Status Register */
#تعریف_کن AT91C_SPI0_IDR             ( ( AT91_REG * ) 0xFFFE0018 ) /* (SPI0) Interrupt Disable Register */
#تعریف_کن AT91C_SPI0_CR              ( ( AT91_REG * ) 0xFFFE0000 ) /* (SPI0) Control Register */
#تعریف_کن AT91C_SPI0_MR              ( ( AT91_REG * ) 0xFFFE0004 ) /* (SPI0) Mode Register */
#تعریف_کن AT91C_SPI0_IMR             ( ( AT91_REG * ) 0xFFFE001C ) /* (SPI0) Interrupt Mask Register */
#تعریف_کن AT91C_SPI0_TDR             ( ( AT91_REG * ) 0xFFFE000C ) /* (SPI0) Transmit Data Register */
#تعریف_کن AT91C_SPI0_RDR             ( ( AT91_REG * ) 0xFFFE0008 ) /* (SPI0) Receive Data Register */
#تعریف_کن AT91C_SPI0_CSR             ( ( AT91_REG * ) 0xFFFE0030 ) /* (SPI0) Chip Select Register */
/* ========== Register definition for PDC_US1 peripheral ========== */
#تعریف_کن AT91C_US1_RNCR             ( ( AT91_REG * ) 0xFFFC4114 ) /* (PDC_US1) Receive Next Counter Register */
#تعریف_کن AT91C_US1_PTCR             ( ( AT91_REG * ) 0xFFFC4120 ) /* (PDC_US1) PDC Transfer Control Register */
#تعریف_کن AT91C_US1_TCR              ( ( AT91_REG * ) 0xFFFC410C ) /* (PDC_US1) Transmit Counter Register */
#تعریف_کن AT91C_US1_PTSR             ( ( AT91_REG * ) 0xFFFC4124 ) /* (PDC_US1) PDC Transfer Status Register */
#تعریف_کن AT91C_US1_TNPR             ( ( AT91_REG * ) 0xFFFC4118 ) /* (PDC_US1) Transmit Next Pointer Register */
#تعریف_کن AT91C_US1_RCR              ( ( AT91_REG * ) 0xFFFC4104 ) /* (PDC_US1) Receive Counter Register */
#تعریف_کن AT91C_US1_RNPR             ( ( AT91_REG * ) 0xFFFC4110 ) /* (PDC_US1) Receive Next Pointer Register */
#تعریف_کن AT91C_US1_RPR              ( ( AT91_REG * ) 0xFFFC4100 ) /* (PDC_US1) Receive Pointer Register */
#تعریف_کن AT91C_US1_TNCR             ( ( AT91_REG * ) 0xFFFC411C ) /* (PDC_US1) Transmit Next Counter Register */
#تعریف_کن AT91C_US1_TPR              ( ( AT91_REG * ) 0xFFFC4108 ) /* (PDC_US1) Transmit Pointer Register */
/* ========== Register definition for US1 peripheral ========== */
#تعریف_کن AT91C_US1_IF               ( ( AT91_REG * ) 0xFFFC404C ) /* (US1) IRDA_FILTER Register */
#تعریف_کن AT91C_US1_NER              ( ( AT91_REG * ) 0xFFFC4044 ) /* (US1) Nb Errors Register */
#تعریف_کن AT91C_US1_RTOR             ( ( AT91_REG * ) 0xFFFC4024 ) /* (US1) Receiver Time-out Register */
#تعریف_کن AT91C_US1_CSR              ( ( AT91_REG * ) 0xFFFC4014 ) /* (US1) Channel Status Register */
#تعریف_کن AT91C_US1_IDR              ( ( AT91_REG * ) 0xFFFC400C ) /* (US1) Interrupt Disable Register */
#تعریف_کن AT91C_US1_IER              ( ( AT91_REG * ) 0xFFFC4008 ) /* (US1) Interrupt Enable Register */
#تعریف_کن AT91C_US1_THR              ( ( AT91_REG * ) 0xFFFC401C ) /* (US1) Transmitter Holding Register */
#تعریف_کن AT91C_US1_TTGR             ( ( AT91_REG * ) 0xFFFC4028 ) /* (US1) Transmitter Time-guard Register */
#تعریف_کن AT91C_US1_RHR              ( ( AT91_REG * ) 0xFFFC4018 ) /* (US1) Receiver Holding Register */
#تعریف_کن AT91C_US1_BRGR             ( ( AT91_REG * ) 0xFFFC4020 ) /* (US1) Baud Rate Generator Register */
#تعریف_کن AT91C_US1_IMR              ( ( AT91_REG * ) 0xFFFC4010 ) /* (US1) Interrupt Mask Register */
#تعریف_کن AT91C_US1_FIDI             ( ( AT91_REG * ) 0xFFFC4040 ) /* (US1) FI_DI_Ratio Register */
#تعریف_کن AT91C_US1_CR               ( ( AT91_REG * ) 0xFFFC4000 ) /* (US1) Control Register */
#تعریف_کن AT91C_US1_MR               ( ( AT91_REG * ) 0xFFFC4004 ) /* (US1) Mode Register */
/* ========== Register definition for PDC_US0 peripheral ========== */
#تعریف_کن AT91C_US0_TNPR             ( ( AT91_REG * ) 0xFFFC0118 ) /* (PDC_US0) Transmit Next Pointer Register */
#تعریف_کن AT91C_US0_RNPR             ( ( AT91_REG * ) 0xFFFC0110 ) /* (PDC_US0) Receive Next Pointer Register */
#تعریف_کن AT91C_US0_TCR              ( ( AT91_REG * ) 0xFFFC010C ) /* (PDC_US0) Transmit Counter Register */
#تعریف_کن AT91C_US0_PTCR             ( ( AT91_REG * ) 0xFFFC0120 ) /* (PDC_US0) PDC Transfer Control Register */
#تعریف_کن AT91C_US0_PTSR             ( ( AT91_REG * ) 0xFFFC0124 ) /* (PDC_US0) PDC Transfer Status Register */
#تعریف_کن AT91C_US0_TNCR             ( ( AT91_REG * ) 0xFFFC011C ) /* (PDC_US0) Transmit Next Counter Register */
#تعریف_کن AT91C_US0_TPR              ( ( AT91_REG * ) 0xFFFC0108 ) /* (PDC_US0) Transmit Pointer Register */
#تعریف_کن AT91C_US0_RCR              ( ( AT91_REG * ) 0xFFFC0104 ) /* (PDC_US0) Receive Counter Register */
#تعریف_کن AT91C_US0_RPR              ( ( AT91_REG * ) 0xFFFC0100 ) /* (PDC_US0) Receive Pointer Register */
#تعریف_کن AT91C_US0_RNCR             ( ( AT91_REG * ) 0xFFFC0114 ) /* (PDC_US0) Receive Next Counter Register */
/* ========== Register definition for US0 peripheral ========== */
#تعریف_کن AT91C_US0_BRGR             ( ( AT91_REG * ) 0xFFFC0020 ) /* (US0) Baud Rate Generator Register */
#تعریف_کن AT91C_US0_NER              ( ( AT91_REG * ) 0xFFFC0044 ) /* (US0) Nb Errors Register */
#تعریف_کن AT91C_US0_CR               ( ( AT91_REG * ) 0xFFFC0000 ) /* (US0) Control Register */
#تعریف_کن AT91C_US0_IMR              ( ( AT91_REG * ) 0xFFFC0010 ) /* (US0) Interrupt Mask Register */
#تعریف_کن AT91C_US0_FIDI             ( ( AT91_REG * ) 0xFFFC0040 ) /* (US0) FI_DI_Ratio Register */
#تعریف_کن AT91C_US0_TTGR             ( ( AT91_REG * ) 0xFFFC0028 ) /* (US0) Transmitter Time-guard Register */
#تعریف_کن AT91C_US0_MR               ( ( AT91_REG * ) 0xFFFC0004 ) /* (US0) Mode Register */
#تعریف_کن AT91C_US0_RTOR             ( ( AT91_REG * ) 0xFFFC0024 ) /* (US0) Receiver Time-out Register */
#تعریف_کن AT91C_US0_CSR              ( ( AT91_REG * ) 0xFFFC0014 ) /* (US0) Channel Status Register */
#تعریف_کن AT91C_US0_RHR              ( ( AT91_REG * ) 0xFFFC0018 ) /* (US0) Receiver Holding Register */
#تعریف_کن AT91C_US0_IDR              ( ( AT91_REG * ) 0xFFFC000C ) /* (US0) Interrupt Disable Register */
#تعریف_کن AT91C_US0_THR              ( ( AT91_REG * ) 0xFFFC001C ) /* (US0) Transmitter Holding Register */
#تعریف_کن AT91C_US0_IF               ( ( AT91_REG * ) 0xFFFC004C ) /* (US0) IRDA_FILTER Register */
#تعریف_کن AT91C_US0_IER              ( ( AT91_REG * ) 0xFFFC0008 ) /* (US0) Interrupt Enable Register */
/* ========== Register definition for PDC_SSC peripheral ========== */
#تعریف_کن AT91C_SSC_TNCR             ( ( AT91_REG * ) 0xFFFD411C ) /* (PDC_SSC) Transmit Next Counter Register */
#تعریف_کن AT91C_SSC_RPR              ( ( AT91_REG * ) 0xFFFD4100 ) /* (PDC_SSC) Receive Pointer Register */
#تعریف_کن AT91C_SSC_RNCR             ( ( AT91_REG * ) 0xFFFD4114 ) /* (PDC_SSC) Receive Next Counter Register */
#تعریف_کن AT91C_SSC_TPR              ( ( AT91_REG * ) 0xFFFD4108 ) /* (PDC_SSC) Transmit Pointer Register */
#تعریف_کن AT91C_SSC_PTCR             ( ( AT91_REG * ) 0xFFFD4120 ) /* (PDC_SSC) PDC Transfer Control Register */
#تعریف_کن AT91C_SSC_TCR              ( ( AT91_REG * ) 0xFFFD410C ) /* (PDC_SSC) Transmit Counter Register */
#تعریف_کن AT91C_SSC_RCR              ( ( AT91_REG * ) 0xFFFD4104 ) /* (PDC_SSC) Receive Counter Register */
#تعریف_کن AT91C_SSC_RNPR             ( ( AT91_REG * ) 0xFFFD4110 ) /* (PDC_SSC) Receive Next Pointer Register */
#تعریف_کن AT91C_SSC_TNPR             ( ( AT91_REG * ) 0xFFFD4118 ) /* (PDC_SSC) Transmit Next Pointer Register */
#تعریف_کن AT91C_SSC_PTSR             ( ( AT91_REG * ) 0xFFFD4124 ) /* (PDC_SSC) PDC Transfer Status Register */
/* ========== Register definition for SSC peripheral ========== */
#تعریف_کن AT91C_SSC_RHR              ( ( AT91_REG * ) 0xFFFD4020 ) /* (SSC) Receive Holding Register */
#تعریف_کن AT91C_SSC_RSHR             ( ( AT91_REG * ) 0xFFFD4030 ) /* (SSC) Receive Sync Holding Register */
#تعریف_کن AT91C_SSC_TFMR             ( ( AT91_REG * ) 0xFFFD401C ) /* (SSC) Transmit Frame Mode Register */
#تعریف_کن AT91C_SSC_IDR              ( ( AT91_REG * ) 0xFFFD4048 ) /* (SSC) Interrupt Disable Register */
#تعریف_کن AT91C_SSC_THR              ( ( AT91_REG * ) 0xFFFD4024 ) /* (SSC) Transmit Holding Register */
#تعریف_کن AT91C_SSC_RCMR             ( ( AT91_REG * ) 0xFFFD4010 ) /* (SSC) Receive Clock ModeRegister */
#تعریف_کن AT91C_SSC_IER              ( ( AT91_REG * ) 0xFFFD4044 ) /* (SSC) Interrupt Enable Register */
#تعریف_کن AT91C_SSC_TSHR             ( ( AT91_REG * ) 0xFFFD4034 ) /* (SSC) Transmit Sync Holding Register */
#تعریف_کن AT91C_SSC_SR               ( ( AT91_REG * ) 0xFFFD4040 ) /* (SSC) Status Register */
#تعریف_کن AT91C_SSC_CMR              ( ( AT91_REG * ) 0xFFFD4004 ) /* (SSC) Clock Mode Register */
#تعریف_کن AT91C_SSC_TCMR             ( ( AT91_REG * ) 0xFFFD4018 ) /* (SSC) Transmit Clock Mode Register */
#تعریف_کن AT91C_SSC_CR               ( ( AT91_REG * ) 0xFFFD4000 ) /* (SSC) Control Register */
#تعریف_کن AT91C_SSC_IMR              ( ( AT91_REG * ) 0xFFFD404C ) /* (SSC) Interrupt Mask Register */
#تعریف_کن AT91C_SSC_RFMR             ( ( AT91_REG * ) 0xFFFD4014 ) /* (SSC) Receive Frame Mode Register */
/* ========== Register definition for TWI peripheral ========== */
#تعریف_کن AT91C_TWI_IER              ( ( AT91_REG * ) 0xFFFB8024 ) /* (TWI) Interrupt Enable Register */
#تعریف_کن AT91C_TWI_CR               ( ( AT91_REG * ) 0xFFFB8000 ) /* (TWI) Control Register */
#تعریف_کن AT91C_TWI_SR               ( ( AT91_REG * ) 0xFFFB8020 ) /* (TWI) Status Register */
#تعریف_کن AT91C_TWI_IMR              ( ( AT91_REG * ) 0xFFFB802C ) /* (TWI) Interrupt Mask Register */
#تعریف_کن AT91C_TWI_THR              ( ( AT91_REG * ) 0xFFFB8034 ) /* (TWI) Transmit Holding Register */
#تعریف_کن AT91C_TWI_IDR              ( ( AT91_REG * ) 0xFFFB8028 ) /* (TWI) Interrupt Disable Register */
#تعریف_کن AT91C_TWI_IADR             ( ( AT91_REG * ) 0xFFFB800C ) /* (TWI) Internal Address Register */
#تعریف_کن AT91C_TWI_MMR              ( ( AT91_REG * ) 0xFFFB8004 ) /* (TWI) Master Mode Register */
#تعریف_کن AT91C_TWI_CWGR             ( ( AT91_REG * ) 0xFFFB8010 ) /* (TWI) Clock Waveform Generator Register */
#تعریف_کن AT91C_TWI_RHR              ( ( AT91_REG * ) 0xFFFB8030 ) /* (TWI) Receive Holding Register */
/* ========== Register definition for PWMC_CH3 peripheral ========== */
#تعریف_کن AT91C_PWMC_CH3_CUPDR       ( ( AT91_REG * ) 0xFFFCC270 ) /* (PWMC_CH3) Channel Update Register */
#تعریف_کن AT91C_PWMC_CH3_Reserved    ( ( AT91_REG * ) 0xFFFCC274 ) /* (PWMC_CH3) Reserved */
#تعریف_کن AT91C_PWMC_CH3_CPRDR       ( ( AT91_REG * ) 0xFFFCC268 ) /* (PWMC_CH3) Channel Period Register */
#تعریف_کن AT91C_PWMC_CH3_CDTYR       ( ( AT91_REG * ) 0xFFFCC264 ) /* (PWMC_CH3) Channel Duty Cycle Register */
#تعریف_کن AT91C_PWMC_CH3_CCNTR       ( ( AT91_REG * ) 0xFFFCC26C ) /* (PWMC_CH3) Channel Counter Register */
#تعریف_کن AT91C_PWMC_CH3_CMR         ( ( AT91_REG * ) 0xFFFCC260 ) /* (PWMC_CH3) Channel Mode Register */
/* ========== Register definition for PWMC_CH2 peripheral ========== */
#تعریف_کن AT91C_PWMC_CH2_Reserved    ( ( AT91_REG * ) 0xFFFCC254 ) /* (PWMC_CH2) Reserved */
#تعریف_کن AT91C_PWMC_CH2_CMR         ( ( AT91_REG * ) 0xFFFCC240 ) /* (PWMC_CH2) Channel Mode Register */
#تعریف_کن AT91C_PWMC_CH2_CCNTR       ( ( AT91_REG * ) 0xFFFCC24C ) /* (PWMC_CH2) Channel Counter Register */
#تعریف_کن AT91C_PWMC_CH2_CPRDR       ( ( AT91_REG * ) 0xFFFCC248 ) /* (PWMC_CH2) Channel Period Register */
#تعریف_کن AT91C_PWMC_CH2_CUPDR       ( ( AT91_REG * ) 0xFFFCC250 ) /* (PWMC_CH2) Channel Update Register */
#تعریف_کن AT91C_PWMC_CH2_CDTYR       ( ( AT91_REG * ) 0xFFFCC244 ) /* (PWMC_CH2) Channel Duty Cycle Register */
/* ========== Register definition for PWMC_CH1 peripheral ========== */
#تعریف_کن AT91C_PWMC_CH1_Reserved    ( ( AT91_REG * ) 0xFFFCC234 ) /* (PWMC_CH1) Reserved */
#تعریف_کن AT91C_PWMC_CH1_CUPDR       ( ( AT91_REG * ) 0xFFFCC230 ) /* (PWMC_CH1) Channel Update Register */
#تعریف_کن AT91C_PWMC_CH1_CPRDR       ( ( AT91_REG * ) 0xFFFCC228 ) /* (PWMC_CH1) Channel Period Register */
#تعریف_کن AT91C_PWMC_CH1_CCNTR       ( ( AT91_REG * ) 0xFFFCC22C ) /* (PWMC_CH1) Channel Counter Register */
#تعریف_کن AT91C_PWMC_CH1_CDTYR       ( ( AT91_REG * ) 0xFFFCC224 ) /* (PWMC_CH1) Channel Duty Cycle Register */
#تعریف_کن AT91C_PWMC_CH1_CMR         ( ( AT91_REG * ) 0xFFFCC220 ) /* (PWMC_CH1) Channel Mode Register */
/* ========== Register definition for PWMC_CH0 peripheral ========== */
#تعریف_کن AT91C_PWMC_CH0_Reserved    ( ( AT91_REG * ) 0xFFFCC214 ) /* (PWMC_CH0) Reserved */
#تعریف_کن AT91C_PWMC_CH0_CPRDR       ( ( AT91_REG * ) 0xFFFCC208 ) /* (PWMC_CH0) Channel Period Register */
#تعریف_کن AT91C_PWMC_CH0_CDTYR       ( ( AT91_REG * ) 0xFFFCC204 ) /* (PWMC_CH0) Channel Duty Cycle Register */
#تعریف_کن AT91C_PWMC_CH0_CMR         ( ( AT91_REG * ) 0xFFFCC200 ) /* (PWMC_CH0) Channel Mode Register */
#تعریف_کن AT91C_PWMC_CH0_CUPDR       ( ( AT91_REG * ) 0xFFFCC210 ) /* (PWMC_CH0) Channel Update Register */
#تعریف_کن AT91C_PWMC_CH0_CCNTR       ( ( AT91_REG * ) 0xFFFCC20C ) /* (PWMC_CH0) Channel Counter Register */
/* ========== Register definition for PWMC peripheral ========== */
#تعریف_کن AT91C_PWMC_IDR             ( ( AT91_REG * ) 0xFFFCC014 ) /* (PWMC) PWMC Interrupt Disable Register */
#تعریف_کن AT91C_PWMC_DIS             ( ( AT91_REG * ) 0xFFFCC008 ) /* (PWMC) PWMC Disable Register */
#تعریف_کن AT91C_PWMC_IER             ( ( AT91_REG * ) 0xFFFCC010 ) /* (PWMC) PWMC Interrupt Enable Register */
#تعریف_کن AT91C_PWMC_VR              ( ( AT91_REG * ) 0xFFFCC0FC ) /* (PWMC) PWMC Version Register */
#تعریف_کن AT91C_PWMC_ISR             ( ( AT91_REG * ) 0xFFFCC01C ) /* (PWMC) PWMC Interrupt Status Register */
#تعریف_کن AT91C_PWMC_SR              ( ( AT91_REG * ) 0xFFFCC00C ) /* (PWMC) PWMC Status Register */
#تعریف_کن AT91C_PWMC_IMR             ( ( AT91_REG * ) 0xFFFCC018 ) /* (PWMC) PWMC Interrupt Mask Register */
#تعریف_کن AT91C_PWMC_MR              ( ( AT91_REG * ) 0xFFFCC000 ) /* (PWMC) PWMC Mode Register */
#تعریف_کن AT91C_PWMC_ENA             ( ( AT91_REG * ) 0xFFFCC004 ) /* (PWMC) PWMC Enable Register */
/* ========== Register definition for UDP peripheral ========== */
#تعریف_کن AT91C_UDP_IMR              ( ( AT91_REG * ) 0xFFFB0018 ) /* (UDP) Interrupt Mask Register */
#تعریف_کن AT91C_UDP_FADDR            ( ( AT91_REG * ) 0xFFFB0008 ) /* (UDP) Function Address Register */
#تعریف_کن AT91_C_UDP_رقم              ( ( AT91_REG * ) 0xFFFB0000 ) /* (UDP) Frame Number Register */
#تعریف_کن AT91C_UDP_FDR              ( ( AT91_REG * ) 0xFFFB0050 ) /* (UDP) Endpoint FIFO Data Register */
#تعریف_کن AT91C_UDP_ISR              ( ( AT91_REG * ) 0xFFFB001C ) /* (UDP) Interrupt Status Register */
#تعریف_کن AT91C_UDP_CSR              ( ( AT91_REG * ) 0xFFFB0030 ) /* (UDP) Endpoint Control and Status Register */
#تعریف_کن AT91C_UDP_IDR              ( ( AT91_REG * ) 0xFFFB0014 ) /* (UDP) Interrupt Disable Register */
#تعریف_کن AT91C_UDP_ICR              ( ( AT91_REG * ) 0xFFFB0020 ) /* (UDP) Interrupt Clear Register */
#تعریف_کن AT91C_UDP_RSTEP            ( ( AT91_REG * ) 0xFFFB0028 ) /* (UDP) Reset Endpoint Register */
#تعریف_کن AT91C_UDP_TXVC             ( ( AT91_REG * ) 0xFFFB0074 ) /* (UDP) Transceiver Control Register */
#تعریف_کن AT91C_UDP_GLBSTATE         ( ( AT91_REG * ) 0xFFFB0004 ) /* (UDP) Global State Register */
#تعریف_کن AT91C_UDP_IER              ( ( AT91_REG * ) 0xFFFB0010 ) /* (UDP) Interrupt Enable Register */
/* ========== Register definition for TC0 peripheral ========== */
#تعریف_کن AT91C_TC0_SR               ( ( AT91_REG * ) 0xFFFA0020 ) /* (TC0) Status Register */
#تعریف_کن AT91C_TC0_RC               ( ( AT91_REG * ) 0xFFFA001C ) /* (TC0) Register C */
#تعریف_کن AT91C_TC0_RB               ( ( AT91_REG * ) 0xFFFA0018 ) /* (TC0) Register B */
#تعریف_کن AT91C_TC0_CCR              ( ( AT91_REG * ) 0xFFFA0000 ) /* (TC0) Channel Control Register */
#تعریف_کن AT91C_TC0_CMR              ( ( AT91_REG * ) 0xFFFA0004 ) /* (TC0) Channel Mode Register (Capture Mode / Waveform Mode) */
#تعریف_کن AT91C_TC0_IER              ( ( AT91_REG * ) 0xFFFA0024 ) /* (TC0) Interrupt Enable Register */
#تعریف_کن AT91C_TC0_RA               ( ( AT91_REG * ) 0xFFFA0014 ) /* (TC0) Register A */
#تعریف_کن AT91C_TC0_IDR              ( ( AT91_REG * ) 0xFFFA0028 ) /* (TC0) Interrupt Disable Register */
#تعریف_کن AT91C_TC0_CV               ( ( AT91_REG * ) 0xFFFA0010 ) /* (TC0) Counter Value */
#تعریف_کن AT91C_TC0_IMR              ( ( AT91_REG * ) 0xFFFA002C ) /* (TC0) Interrupt Mask Register */
/* ========== Register definition for TC1 peripheral ========== */
#تعریف_کن AT91C_TC1_RB               ( ( AT91_REG * ) 0xFFFA0058 ) /* (TC1) Register B */
#تعریف_کن AT91C_TC1_CCR              ( ( AT91_REG * ) 0xFFFA0040 ) /* (TC1) Channel Control Register */
#تعریف_کن AT91C_TC1_IER              ( ( AT91_REG * ) 0xFFFA0064 ) /* (TC1) Interrupt Enable Register */
#تعریف_کن AT91C_TC1_IDR              ( ( AT91_REG * ) 0xFFFA0068 ) /* (TC1) Interrupt Disable Register */
#تعریف_کن AT91C_TC1_SR               ( ( AT91_REG * ) 0xFFFA0060 ) /* (TC1) Status Register */
#تعریف_کن AT91C_TC1_CMR              ( ( AT91_REG * ) 0xFFFA0044 ) /* (TC1) Channel Mode Register (Capture Mode / Waveform Mode) */
#تعریف_کن AT91C_TC1_RA               ( ( AT91_REG * ) 0xFFFA0054 ) /* (TC1) Register A */
#تعریف_کن AT91C_TC1_RC               ( ( AT91_REG * ) 0xFFFA005C ) /* (TC1) Register C */
#تعریف_کن AT91C_TC1_IMR              ( ( AT91_REG * ) 0xFFFA006C ) /* (TC1) Interrupt Mask Register */
#تعریف_کن AT91C_TC1_CV               ( ( AT91_REG * ) 0xFFFA0050 ) /* (TC1) Counter Value */
/* ========== Register definition for TC2 peripheral ========== */
#تعریف_کن AT91C_TC2_CMR              ( ( AT91_REG * ) 0xFFFA0084 ) /* (TC2) Channel Mode Register (Capture Mode / Waveform Mode) */
#تعریف_کن AT91C_TC2_CCR              ( ( AT91_REG * ) 0xFFFA0080 ) /* (TC2) Channel Control Register */
#تعریف_کن AT91C_TC2_CV               ( ( AT91_REG * ) 0xFFFA0090 ) /* (TC2) Counter Value */
#تعریف_کن AT91C_TC2_RA               ( ( AT91_REG * ) 0xFFFA0094 ) /* (TC2) Register A */
#تعریف_کن AT91C_TC2_RB               ( ( AT91_REG * ) 0xFFFA0098 ) /* (TC2) Register B */
#تعریف_کن AT91C_TC2_IDR              ( ( AT91_REG * ) 0xFFFA00A8 ) /* (TC2) Interrupt Disable Register */
#تعریف_کن AT91C_TC2_IMR              ( ( AT91_REG * ) 0xFFFA00AC ) /* (TC2) Interrupt Mask Register */
#تعریف_کن AT91C_TC2_RC               ( ( AT91_REG * ) 0xFFFA009C ) /* (TC2) Register C */
#تعریف_کن AT91C_TC2_IER              ( ( AT91_REG * ) 0xFFFA00A4 ) /* (TC2) Interrupt Enable Register */
#تعریف_کن AT91C_TC2_SR               ( ( AT91_REG * ) 0xFFFA00A0 ) /* (TC2) Status Register */
/* ========== Register definition for TCB peripheral ========== */
#تعریف_کن AT91C_TCB_BMR              ( ( AT91_REG * ) 0xFFFA00C4 ) /* (TCB) TC Block Mode Register */
#تعریف_کن AT91C_TCB_BCR              ( ( AT91_REG * ) 0xFFFA00C0 ) /* (TCB) TC Block Control Register */
/* ========== Register definition for CAN_MB0 peripheral ========== */
#تعریف_کن AT91C_CAN_MB0_MDL          ( ( AT91_REG * ) 0xFFFD0214 ) /* (CAN_MB0) MailBox Data Low Register */
#تعریف_کن AT91C_CAN_MB0_MAM          ( ( AT91_REG * ) 0xFFFD0204 ) /* (CAN_MB0) MailBox Acceptance Mask Register */
#تعریف_کن AT91C_CAN_MB0_MCR          ( ( AT91_REG * ) 0xFFFD021C ) /* (CAN_MB0) MailBox Control Register */
#تعریف_کن AT91C_CAN_MB0_MID          ( ( AT91_REG * ) 0xFFFD0208 ) /* (CAN_MB0) MailBox ID Register */
#تعریف_کن AT91C_CAN_MB0_MSR          ( ( AT91_REG * ) 0xFFFD0210 ) /* (CAN_MB0) MailBox Status Register */
#تعریف_کن AT91C_CAN_MB0_MFID         ( ( AT91_REG * ) 0xFFFD020C ) /* (CAN_MB0) MailBox Family ID Register */
#تعریف_کن AT91C_CAN_MB0_MDH          ( ( AT91_REG * ) 0xFFFD0218 ) /* (CAN_MB0) MailBox Data High Register */
#تعریف_کن AT91C_CAN_MB0_MMR          ( ( AT91_REG * ) 0xFFFD0200 ) /* (CAN_MB0) MailBox Mode Register */
/* ========== Register definition for CAN_MB1 peripheral ========== */
#تعریف_کن AT91C_CAN_MB1_MDL          ( ( AT91_REG * ) 0xFFFD0234 ) /* (CAN_MB1) MailBox Data Low Register */
#تعریف_کن AT91C_CAN_MB1_MID          ( ( AT91_REG * ) 0xFFFD0228 ) /* (CAN_MB1) MailBox ID Register */
#تعریف_کن AT91C_CAN_MB1_MMR          ( ( AT91_REG * ) 0xFFFD0220 ) /* (CAN_MB1) MailBox Mode Register */
#تعریف_کن AT91C_CAN_MB1_MSR          ( ( AT91_REG * ) 0xFFFD0230 ) /* (CAN_MB1) MailBox Status Register */
#تعریف_کن AT91C_CAN_MB1_MAM          ( ( AT91_REG * ) 0xFFFD0224 ) /* (CAN_MB1) MailBox Acceptance Mask Register */
#تعریف_کن AT91C_CAN_MB1_MDH          ( ( AT91_REG * ) 0xFFFD0238 ) /* (CAN_MB1) MailBox Data High Register */
#تعریف_کن AT91C_CAN_MB1_MCR          ( ( AT91_REG * ) 0xFFFD023C ) /* (CAN_MB1) MailBox Control Register */
#تعریف_کن AT91C_CAN_MB1_MFID         ( ( AT91_REG * ) 0xFFFD022C ) /* (CAN_MB1) MailBox Family ID Register */
/* ========== Register definition for CAN_MB2 peripheral ========== */
#تعریف_کن AT91C_CAN_MB2_MCR          ( ( AT91_REG * ) 0xFFFD025C ) /* (CAN_MB2) MailBox Control Register */
#تعریف_کن AT91C_CAN_MB2_MDH          ( ( AT91_REG * ) 0xFFFD0258 ) /* (CAN_MB2) MailBox Data High Register */
#تعریف_کن AT91C_CAN_MB2_MID          ( ( AT91_REG * ) 0xFFFD0248 ) /* (CAN_MB2) MailBox ID Register */
#تعریف_کن AT91C_CAN_MB2_MDL          ( ( AT91_REG * ) 0xFFFD0254 ) /* (CAN_MB2) MailBox Data Low Register */
#تعریف_کن AT91C_CAN_MB2_MMR          ( ( AT91_REG * ) 0xFFFD0240 ) /* (CAN_MB2) MailBox Mode Register */
#تعریف_کن AT91C_CAN_MB2_MAM          ( ( AT91_REG * ) 0xFFFD0244 ) /* (CAN_MB2) MailBox Acceptance Mask Register */
#تعریف_کن AT91C_CAN_MB2_MFID         ( ( AT91_REG * ) 0xFFFD024C ) /* (CAN_MB2) MailBox Family ID Register */
#تعریف_کن AT91C_CAN_MB2_MSR          ( ( AT91_REG * ) 0xFFFD0250 ) /* (CAN_MB2) MailBox Status Register */
/* ========== Register definition for CAN_MB3 peripheral ========== */
#تعریف_کن AT91C_CAN_MB3_MFID         ( ( AT91_REG * ) 0xFFFD026C ) /* (CAN_MB3) MailBox Family ID Register */
#تعریف_کن AT91C_CAN_MB3_MAM          ( ( AT91_REG * ) 0xFFFD0264 ) /* (CAN_MB3) MailBox Acceptance Mask Register */
#تعریف_کن AT91C_CAN_MB3_MID          ( ( AT91_REG * ) 0xFFFD0268 ) /* (CAN_MB3) MailBox ID Register */
#تعریف_کن AT91C_CAN_MB3_MCR          ( ( AT91_REG * ) 0xFFFD027C ) /* (CAN_MB3) MailBox Control Register */
#تعریف_کن AT91C_CAN_MB3_MMR          ( ( AT91_REG * ) 0xFFFD0260 ) /* (CAN_MB3) MailBox Mode Register */
#تعریف_کن AT91C_CAN_MB3_MSR          ( ( AT91_REG * ) 0xFFFD0270 ) /* (CAN_MB3) MailBox Status Register */
#تعریف_کن AT91C_CAN_MB3_MDL          ( ( AT91_REG * ) 0xFFFD0274 ) /* (CAN_MB3) MailBox Data Low Register */
#تعریف_کن AT91C_CAN_MB3_MDH          ( ( AT91_REG * ) 0xFFFD0278 ) /* (CAN_MB3) MailBox Data High Register */
/* ========== Register definition for CAN_MB4 peripheral ========== */
#تعریف_کن AT91C_CAN_MB4_MID          ( ( AT91_REG * ) 0xFFFD0288 ) /* (CAN_MB4) MailBox ID Register */
#تعریف_کن AT91C_CAN_MB4_MMR          ( ( AT91_REG * ) 0xFFFD0280 ) /* (CAN_MB4) MailBox Mode Register */
#تعریف_کن AT91C_CAN_MB4_MDH          ( ( AT91_REG * ) 0xFFFD0298 ) /* (CAN_MB4) MailBox Data High Register */
#تعریف_کن AT91C_CAN_MB4_MFID         ( ( AT91_REG * ) 0xFFFD028C ) /* (CAN_MB4) MailBox Family ID Register */
#تعریف_کن AT91C_CAN_MB4_MSR          ( ( AT91_REG * ) 0xFFFD0290 ) /* (CAN_MB4) MailBox Status Register */
#تعریف_کن AT91C_CAN_MB4_MCR          ( ( AT91_REG * ) 0xFFFD029C ) /* (CAN_MB4) MailBox Control Register */
#تعریف_کن AT91C_CAN_MB4_MDL          ( ( AT91_REG * ) 0xFFFD0294 ) /* (CAN_MB4) MailBox Data Low Register */
#تعریف_کن AT91C_CAN_MB4_MAM          ( ( AT91_REG * ) 0xFFFD0284 ) /* (CAN_MB4) MailBox Acceptance Mask Register */
/* ========== Register definition for CAN_MB5 peripheral ========== */
#تعریف_کن AT91C_CAN_MB5_MSR          ( ( AT91_REG * ) 0xFFFD02B0 ) /* (CAN_MB5) MailBox Status Register */
#تعریف_کن AT91C_CAN_MB5_MCR          ( ( AT91_REG * ) 0xFFFD02BC ) /* (CAN_MB5) MailBox Control Register */
#تعریف_کن AT91C_CAN_MB5_MFID         ( ( AT91_REG * ) 0xFFFD02AC ) /* (CAN_MB5) MailBox Family ID Register */
#تعریف_کن AT91C_CAN_MB5_MDH          ( ( AT91_REG * ) 0xFFFD02B8 ) /* (CAN_MB5) MailBox Data High Register */
#تعریف_کن AT91C_CAN_MB5_MID          ( ( AT91_REG * ) 0xFFFD02A8 ) /* (CAN_MB5) MailBox ID Register */
#تعریف_کن AT91C_CAN_MB5_MMR          ( ( AT91_REG * ) 0xFFFD02A0 ) /* (CAN_MB5) MailBox Mode Register */
#تعریف_کن AT91C_CAN_MB5_MDL          ( ( AT91_REG * ) 0xFFFD02B4 ) /* (CAN_MB5) MailBox Data Low Register */
#تعریف_کن AT91C_CAN_MB5_MAM          ( ( AT91_REG * ) 0xFFFD02A4 ) /* (CAN_MB5) MailBox Acceptance Mask Register */
/* ========== Register definition for CAN_MB6 peripheral ========== */
#تعریف_کن AT91C_CAN_MB6_MFID         ( ( AT91_REG * ) 0xFFFD02CC ) /* (CAN_MB6) MailBox Family ID Register */
#تعریف_کن AT91C_CAN_MB6_MID          ( ( AT91_REG * ) 0xFFFD02C8 ) /* (CAN_MB6) MailBox ID Register */
#تعریف_کن AT91C_CAN_MB6_MAM          ( ( AT91_REG * ) 0xFFFD02C4 ) /* (CAN_MB6) MailBox Acceptance Mask Register */
#تعریف_کن AT91C_CAN_MB6_MSR          ( ( AT91_REG * ) 0xFFFD02D0 ) /* (CAN_MB6) MailBox Status Register */
#تعریف_کن AT91C_CAN_MB6_MDL          ( ( AT91_REG * ) 0xFFFD02D4 ) /* (CAN_MB6) MailBox Data Low Register */
#تعریف_کن AT91C_CAN_MB6_MCR          ( ( AT91_REG * ) 0xFFFD02DC ) /* (CAN_MB6) MailBox Control Register */
#تعریف_کن AT91C_CAN_MB6_MDH          ( ( AT91_REG * ) 0xFFFD02D8 ) /* (CAN_MB6) MailBox Data High Register */
#تعریف_کن AT91C_CAN_MB6_MMR          ( ( AT91_REG * ) 0xFFFD02C0 ) /* (CAN_MB6) MailBox Mode Register */
/* ========== Register definition for CAN_MB7 peripheral ========== */
#تعریف_کن AT91C_CAN_MB7_MCR          ( ( AT91_REG * ) 0xFFFD02FC ) /* (CAN_MB7) MailBox Control Register */
#تعریف_کن AT91C_CAN_MB7_MDH          ( ( AT91_REG * ) 0xFFFD02F8 ) /* (CAN_MB7) MailBox Data High Register */
#تعریف_کن AT91C_CAN_MB7_MFID         ( ( AT91_REG * ) 0xFFFD02EC ) /* (CAN_MB7) MailBox Family ID Register */
#تعریف_کن AT91C_CAN_MB7_MDL          ( ( AT91_REG * ) 0xFFFD02F4 ) /* (CAN_MB7) MailBox Data Low Register */
#تعریف_کن AT91C_CAN_MB7_MID          ( ( AT91_REG * ) 0xFFFD02E8 ) /* (CAN_MB7) MailBox ID Register */
#تعریف_کن AT91C_CAN_MB7_MMR          ( ( AT91_REG * ) 0xFFFD02E0 ) /* (CAN_MB7) MailBox Mode Register */
#تعریف_کن AT91C_CAN_MB7_MAM          ( ( AT91_REG * ) 0xFFFD02E4 ) /* (CAN_MB7) MailBox Acceptance Mask Register */
#تعریف_کن AT91C_CAN_MB7_MSR          ( ( AT91_REG * ) 0xFFFD02F0 ) /* (CAN_MB7) MailBox Status Register */
/* ========== Register definition for CAN peripheral ========== */
#تعریف_کن AT91C_CAN_TCR              ( ( AT91_REG * ) 0xFFFD0024 ) /* (CAN) Transfer Command Register */
#تعریف_کن AT91C_CAN_IMR              ( ( AT91_REG * ) 0xFFFD000C ) /* (CAN) Interrupt Mask Register */
#تعریف_کن AT91C_CAN_IER              ( ( AT91_REG * ) 0xFFFD0004 ) /* (CAN) Interrupt Enable Register */
#تعریف_کن AT91C_CAN_ECR              ( ( AT91_REG * ) 0xFFFD0020 ) /* (CAN) Error Counter Register */
#تعریف_کن AT91C_CAN_TIMESTP          ( ( AT91_REG * ) 0xFFFD001C ) /* (CAN) Time Stamp Register */
#تعریف_کن AT91C_CAN_MR               ( ( AT91_REG * ) 0xFFFD0000 ) /* (CAN) Mode Register */
#تعریف_کن AT91C_CAN_IDR              ( ( AT91_REG * ) 0xFFFD0008 ) /* (CAN) Interrupt Disable Register */
#تعریف_کن AT91C_CAN_ACR              ( ( AT91_REG * ) 0xFFFD0028 ) /* (CAN) Abort Command Register */
#تعریف_کن AT91C_CAN_TIM              ( ( AT91_REG * ) 0xFFFD0018 ) /* (CAN) Timer Register */
#تعریف_کن AT91C_CAN_SR               ( ( AT91_REG * ) 0xFFFD0010 ) /* (CAN) Status Register */
#تعریف_کن AT91C_CAN_BR               ( ( AT91_REG * ) 0xFFFD0014 ) /* (CAN) Baudrate Register */
#تعریف_کن AT91C_CAN_VR               ( ( AT91_REG * ) 0xFFFD00FC ) /* (CAN) Version Register */
/* ========== Register definition for EMAC peripheral ========== */
#تعریف_کن AT91C_EMAC_ISR             ( ( AT91_REG * ) 0xFFFDC024 ) /* (EMAC) Interrupt Status Register */
#تعریف_کن AT91C_EMAC_SA4H            ( ( AT91_REG * ) 0xFFFDC0B4 ) /* (EMAC) Specific Address 4 Top, Last 2 bytes */
#تعریف_کن AT91C_EMAC_SA1L            ( ( AT91_REG * ) 0xFFFDC098 ) /* (EMAC) Specific Address 1 Bottom, First 4 bytes */
#تعریف_کن AT91C_EMAC_ELE             ( ( AT91_REG * ) 0xFFFDC078 ) /* (EMAC) Excessive Length Errors Register */
#تعریف_کن AT91C_EMAC_LCOL            ( ( AT91_REG * ) 0xFFFDC05C ) /* (EMAC) Late Collision Register */
#تعریف_کن AT91C_EMAC_RLE             ( ( AT91_REG * ) 0xFFFDC088 ) /* (EMAC) Receive Length Field Mismatch Register */
#تعریف_کن AT91C_EMAC_WOL             ( ( AT91_REG * ) 0xFFFDC0C4 ) /* (EMAC) Wake On LAN Register */
#تعریف_کن AT91C_EMAC_DTF             ( ( AT91_REG * ) 0xFFFDC058 ) /* (EMAC) Deferred Transmission Frame Register */
#تعریف_کن AT91C_EMAC_TUND            ( ( AT91_REG * ) 0xFFFDC064 ) /* (EMAC) Transmit Underrun Error Register */
#تعریف_کن AT91C_EMAC_NCR             ( ( AT91_REG * ) 0xFFFDC000 ) /* (EMAC) Network Control Register */
#تعریف_کن AT91C_EMAC_SA4L            ( ( AT91_REG * ) 0xFFFDC0B0 ) /* (EMAC) Specific Address 4 Bottom, First 4 bytes */
#تعریف_کن AT91C_EMAC_RSR             ( ( AT91_REG * ) 0xFFFDC020 ) /* (EMAC) Receive Status Register */
#تعریف_کن AT91C_EMAC_SA3L            ( ( AT91_REG * ) 0xFFFDC0A8 ) /* (EMAC) Specific Address 3 Bottom, First 4 bytes */
#تعریف_کن AT91C_EMAC_TSR             ( ( AT91_REG * ) 0xFFFDC014 ) /* (EMAC) Transmit Status Register */
#تعریف_کن AT91C_EMAC_IDR             ( ( AT91_REG * ) 0xFFFDC02C ) /* (EMAC) Interrupt Disable Register */
#تعریف_کن AT91C_EMAC_RSE             ( ( AT91_REG * ) 0xFFFDC074 ) /* (EMAC) Receive Symbol Errors Register */
#تعریف_کن AT91C_EMAC_ECOL            ( ( AT91_REG * ) 0xFFFDC060 ) /* (EMAC) Excessive Collision Register */
#تعریف_کن AT91C_EMAC_TID             ( ( AT91_REG * ) 0xFFFDC0B8 ) /* (EMAC) Type ID Checking Register */
#تعریف_کن AT91C_EMAC_HRB             ( ( AT91_REG * ) 0xFFFDC090 ) /* (EMAC) Hash Address Bottom[31:0] */
#تعریف_کن AT91C_EMAC_TBQP            ( ( AT91_REG * ) 0xFFFDC01C ) /* (EMAC) Transmit Buffer Queue Pointer */
#تعریف_کن AT91C_EMAC_USRIO           ( ( AT91_REG * ) 0xFFFDC0C0 ) /* (EMAC) USER Input/Output Register */
#تعریف_کن AT91C_EMAC_PTR             ( ( AT91_REG * ) 0xFFFDC038 ) /* (EMAC) Pause Time Register */
#تعریف_کن AT91C_EMAC_SA2H            ( ( AT91_REG * ) 0xFFFDC0A4 ) /* (EMAC) Specific Address 2 Top, Last 2 bytes */
#تعریف_کن AT91C_EMAC_ROV             ( ( AT91_REG * ) 0xFFFDC070 ) /* (EMAC) Receive Overrun Errors Register */
#تعریف_کن AT91C_EMAC_ALE             ( ( AT91_REG * ) 0xFFFDC054 ) /* (EMAC) Alignment Error Register */
#تعریف_کن AT91C_EMAC_RJA             ( ( AT91_REG * ) 0xFFFDC07C ) /* (EMAC) Receive Jabbers Register */
#تعریف_کن AT91C_EMAC_RBQP            ( ( AT91_REG * ) 0xFFFDC018 ) /* (EMAC) Receive Buffer Queue Pointer */
#تعریف_کن AT91C_EMAC_TPF             ( ( AT91_REG * ) 0xFFFDC08C ) /* (EMAC) Transmitted Pause Frames Register */
#تعریف_کن AT91C_EMAC_NCFGR           ( ( AT91_REG * ) 0xFFFDC004 ) /* (EMAC) Network Configuration Register */
#تعریف_کن AT91C_EMAC_HRT             ( ( AT91_REG * ) 0xFFFDC094 ) /* (EMAC) Hash Address Top[63:32] */
#تعریف_کن AT91C_EMAC_USF             ( ( AT91_REG * ) 0xFFFDC080 ) /* (EMAC) Undersize Frames Register */
#تعریف_کن AT91C_EMAC_FCSE            ( ( AT91_REG * ) 0xFFFDC050 ) /* (EMAC) Frame Check Sequence Error Register */
#تعریف_کن AT91C_EMAC_TPQ             ( ( AT91_REG * ) 0xFFFDC0BC ) /* (EMAC) Transmit Pause Quantum Register */
#تعریف_کن AT91C_EMAC_MAN             ( ( AT91_REG * ) 0xFFFDC034 ) /* (EMAC) PHY Maintenance Register */
#تعریف_کن AT91C_EMAC_FTO             ( ( AT91_REG * ) 0xFFFDC040 ) /* (EMAC) Frames Transmitted OK Register */
#تعریف_کن AT91C_EMAC_REV             ( ( AT91_REG * ) 0xFFFDC0FC ) /* (EMAC) Revision Register */
#تعریف_کن AT91C_EMAC_IMR             ( ( AT91_REG * ) 0xFFFDC030 ) /* (EMAC) Interrupt Mask Register */
#تعریف_کن AT91C_EMAC_SCF             ( ( AT91_REG * ) 0xFFFDC044 ) /* (EMAC) Single Collision Frame Register */
#تعریف_کن AT91C_EMAC_PFR             ( ( AT91_REG * ) 0xFFFDC03C ) /* (EMAC) Pause Frames received Register */
#تعریف_کن AT91C_EMAC_MCF             ( ( AT91_REG * ) 0xFFFDC048 ) /* (EMAC) Multiple Collision Frame Register */
#تعریف_کن AT91C_EMAC_NSR             ( ( AT91_REG * ) 0xFFFDC008 ) /* (EMAC) Network Status Register */
#تعریف_کن AT91C_EMAC_SA2L            ( ( AT91_REG * ) 0xFFFDC0A0 ) /* (EMAC) Specific Address 2 Bottom, First 4 bytes */
#تعریف_کن AT91C_EMAC_FRO             ( ( AT91_REG * ) 0xFFFDC04C ) /* (EMAC) Frames Received OK Register */
#تعریف_کن AT91C_EMAC_IER             ( ( AT91_REG * ) 0xFFFDC028 ) /* (EMAC) Interrupt Enable Register */
#تعریف_کن AT91C_EMAC_SA1H            ( ( AT91_REG * ) 0xFFFDC09C ) /* (EMAC) Specific Address 1 Top, Last 2 bytes */
#تعریف_کن AT91C_EMAC_CSE             ( ( AT91_REG * ) 0xFFFDC068 ) /* (EMAC) Carrier Sense Error Register */
#تعریف_کن AT91C_EMAC_SA3H            ( ( AT91_REG * ) 0xFFFDC0AC ) /* (EMAC) Specific Address 3 Top, Last 2 bytes */
#تعریف_کن AT91C_EMAC_RRE             ( ( AT91_REG * ) 0xFFFDC06C ) /* (EMAC) Receive Resource Error Register */
#تعریف_کن AT91C_EMAC_STE             ( ( AT91_REG * ) 0xFFFDC084 ) /* (EMAC) SQE Test Error Register */
/* ========== Register definition for PDC_ADC peripheral ========== */
#تعریف_کن AT91C_ADC_PTSR             ( ( AT91_REG * ) 0xFFFD8124 ) /* (PDC_ADC) PDC Transfer Status Register */
#تعریف_کن AT91C_ADC_PTCR             ( ( AT91_REG * ) 0xFFFD8120 ) /* (PDC_ADC) PDC Transfer Control Register */
#تعریف_کن AT91C_ADC_TNPR             ( ( AT91_REG * ) 0xFFFD8118 ) /* (PDC_ADC) Transmit Next Pointer Register */
#تعریف_کن AT91C_ADC_TNCR             ( ( AT91_REG * ) 0xFFFD811C ) /* (PDC_ADC) Transmit Next Counter Register */
#تعریف_کن AT91C_ADC_RNPR             ( ( AT91_REG * ) 0xFFFD8110 ) /* (PDC_ADC) Receive Next Pointer Register */
#تعریف_کن AT91C_ADC_RNCR             ( ( AT91_REG * ) 0xFFFD8114 ) /* (PDC_ADC) Receive Next Counter Register */
#تعریف_کن AT91C_ADC_RPR              ( ( AT91_REG * ) 0xFFFD8100 ) /* (PDC_ADC) Receive Pointer Register */
#تعریف_کن AT91C_ADC_TCR              ( ( AT91_REG * ) 0xFFFD810C ) /* (PDC_ADC) Transmit Counter Register */
#تعریف_کن AT91C_ADC_TPR              ( ( AT91_REG * ) 0xFFFD8108 ) /* (PDC_ADC) Transmit Pointer Register */
#تعریف_کن AT91C_ADC_RCR              ( ( AT91_REG * ) 0xFFFD8104 ) /* (PDC_ADC) Receive Counter Register */
/* ========== Register definition for ADC peripheral ========== */
#تعریف_کن AT91C_ADC_CDR2             ( ( AT91_REG * ) 0xFFFD8038 ) /* (ADC) ADC Channel Data Register 2 */
#تعریف_کن AT91C_ADC_CDR3             ( ( AT91_REG * ) 0xFFFD803C ) /* (ADC) ADC Channel Data Register 3 */
#تعریف_کن AT91C_ADC_CDR0             ( ( AT91_REG * ) 0xFFFD8030 ) /* (ADC) ADC Channel Data Register 0 */
#تعریف_کن AT91C_ADC_CDR5             ( ( AT91_REG * ) 0xFFFD8044 ) /* (ADC) ADC Channel Data Register 5 */
#تعریف_کن AT91C_ADC_CHDR             ( ( AT91_REG * ) 0xFFFD8014 ) /* (ADC) ADC Channel Disable Register */
#تعریف_کن AT91C_ADC_SR               ( ( AT91_REG * ) 0xFFFD801C ) /* (ADC) ADC Status Register */
#تعریف_کن AT91C_ADC_CDR4             ( ( AT91_REG * ) 0xFFFD8040 ) /* (ADC) ADC Channel Data Register 4 */
#تعریف_کن AT91C_ADC_CDR1             ( ( AT91_REG * ) 0xFFFD8034 ) /* (ADC) ADC Channel Data Register 1 */
#تعریف_کن AT91C_ADC_LCDR             ( ( AT91_REG * ) 0xFFFD8020 ) /* (ADC) ADC Last Converted Data Register */
#تعریف_کن AT91C_ADC_IDR              ( ( AT91_REG * ) 0xFFFD8028 ) /* (ADC) ADC Interrupt Disable Register */
#تعریف_کن AT91C_ADC_CR               ( ( AT91_REG * ) 0xFFFD8000 ) /* (ADC) ADC Control Register */
#تعریف_کن AT91C_ADC_CDR7             ( ( AT91_REG * ) 0xFFFD804C ) /* (ADC) ADC Channel Data Register 7 */
#تعریف_کن AT91C_ADC_CDR6             ( ( AT91_REG * ) 0xFFFD8048 ) /* (ADC) ADC Channel Data Register 6 */
#تعریف_کن AT91C_ADC_IER              ( ( AT91_REG * ) 0xFFFD8024 ) /* (ADC) ADC Interrupt Enable Register */
#تعریف_کن AT91C_ADC_CHER             ( ( AT91_REG * ) 0xFFFD8010 ) /* (ADC) ADC Channel Enable Register */
#تعریف_کن AT91C_ADC_CHSR             ( ( AT91_REG * ) 0xFFFD8018 ) /* (ADC) ADC Channel Status Register */
#تعریف_کن AT91C_ADC_MR               ( ( AT91_REG * ) 0xFFFD8004 ) /* (ADC) ADC Mode Register */
#تعریف_کن AT91C_ADC_IMR              ( ( AT91_REG * ) 0xFFFD802C ) /* (ADC) ADC Interrupt Mask Register */
/* ========== Register definition for PDC_AES peripheral ========== */
#تعریف_کن AT91C_AES_TPR              ( ( AT91_REG * ) 0xFFFA4108 ) /* (PDC_AES) Transmit Pointer Register */
#تعریف_کن AT91C_AES_PTCR             ( ( AT91_REG * ) 0xFFFA4120 ) /* (PDC_AES) PDC Transfer Control Register */
#تعریف_کن AT91C_AES_RNPR             ( ( AT91_REG * ) 0xFFFA4110 ) /* (PDC_AES) Receive Next Pointer Register */
#تعریف_کن AT91C_AES_TNCR             ( ( AT91_REG * ) 0xFFFA411C ) /* (PDC_AES) Transmit Next Counter Register */
#تعریف_کن AT91C_AES_TCR              ( ( AT91_REG * ) 0xFFFA410C ) /* (PDC_AES) Transmit Counter Register */
#تعریف_کن AT91C_AES_RCR              ( ( AT91_REG * ) 0xFFFA4104 ) /* (PDC_AES) Receive Counter Register */
#تعریف_کن AT91C_AES_RNCR             ( ( AT91_REG * ) 0xFFFA4114 ) /* (PDC_AES) Receive Next Counter Register */
#تعریف_کن AT91C_AES_TNPR             ( ( AT91_REG * ) 0xFFFA4118 ) /* (PDC_AES) Transmit Next Pointer Register */
#تعریف_کن AT91C_AES_RPR              ( ( AT91_REG * ) 0xFFFA4100 ) /* (PDC_AES) Receive Pointer Register */
#تعریف_کن AT91C_AES_PTSR             ( ( AT91_REG * ) 0xFFFA4124 ) /* (PDC_AES) PDC Transfer Status Register */
/* ========== Register definition for AES peripheral ========== */
#تعریف_کن AT91C_AES_IVxR             ( ( AT91_REG * ) 0xFFFA4060 ) /* (AES) Initialization Vector x Register */
#تعریف_کن AT91C_AES_MR               ( ( AT91_REG * ) 0xFFFA4004 ) /* (AES) Mode Register */
#تعریف_کن AT91C_AES_VR               ( ( AT91_REG * ) 0xFFFA40FC ) /* (AES) AES Version Register */
#تعریف_کن AT91C_AES_ODATAxR          ( ( AT91_REG * ) 0xFFFA4050 ) /* (AES) Output Data x Register */
#تعریف_کن AT91C_AES_IDATAxR          ( ( AT91_REG * ) 0xFFFA4040 ) /* (AES) Input Data x Register */
#تعریف_کن AT91C_AES_CR               ( ( AT91_REG * ) 0xFFFA4000 ) /* (AES) Control Register */
#تعریف_کن AT91C_AES_IDR              ( ( AT91_REG * ) 0xFFFA4014 ) /* (AES) Interrupt Disable Register */
#تعریف_کن AT91C_AES_IMR              ( ( AT91_REG * ) 0xFFFA4018 ) /* (AES) Interrupt Mask Register */
#تعریف_کن AT91C_AES_IER              ( ( AT91_REG * ) 0xFFFA4010 ) /* (AES) Interrupt Enable Register */
#تعریف_کن AT91C_AES_KEYWxR           ( ( AT91_REG * ) 0xFFFA4020 ) /* (AES) Key Word x Register */
#تعریف_کن AT91C_AES_ISR              ( ( AT91_REG * ) 0xFFFA401C ) /* (AES) Interrupt Status Register */
/* ========== Register definition for PDC_TDES peripheral ========== */
#تعریف_کن AT91C_TDES_RNCR            ( ( AT91_REG * ) 0xFFFA8114 ) /* (PDC_TDES) Receive Next Counter Register */
#تعریف_کن AT91C_TDES_TCR             ( ( AT91_REG * ) 0xFFFA810C ) /* (PDC_TDES) Transmit Counter Register */
#تعریف_کن AT91C_TDES_RCR             ( ( AT91_REG * ) 0xFFFA8104 ) /* (PDC_TDES) Receive Counter Register */
#تعریف_کن AT91C_TDES_TNPR            ( ( AT91_REG * ) 0xFFFA8118 ) /* (PDC_TDES) Transmit Next Pointer Register */
#تعریف_کن AT91C_TDES_RNPR            ( ( AT91_REG * ) 0xFFFA8110 ) /* (PDC_TDES) Receive Next Pointer Register */
#تعریف_کن AT91C_TDES_RPR             ( ( AT91_REG * ) 0xFFFA8100 ) /* (PDC_TDES) Receive Pointer Register */
#تعریف_کن AT91C_TDES_TNCR            ( ( AT91_REG * ) 0xFFFA811C ) /* (PDC_TDES) Transmit Next Counter Register */
#تعریف_کن AT91C_TDES_TPR             ( ( AT91_REG * ) 0xFFFA8108 ) /* (PDC_TDES) Transmit Pointer Register */
#تعریف_کن AT91C_TDES_PTSR            ( ( AT91_REG * ) 0xFFFA8124 ) /* (PDC_TDES) PDC Transfer Status Register */
#تعریف_کن AT91C_TDES_PTCR            ( ( AT91_REG * ) 0xFFFA8120 ) /* (PDC_TDES) PDC Transfer Control Register */
/* ========== Register definition for TDES peripheral ========== */
#تعریف_کن AT91C_TDES_KEY2WxR         ( ( AT91_REG * ) 0xFFFA8028 ) /* (TDES) Key 2 Word x Register */
#تعریف_کن AT91C_TDES_KEY3WxR         ( ( AT91_REG * ) 0xFFFA8030 ) /* (TDES) Key 3 Word x Register */
#تعریف_کن AT91C_TDES_IDR             ( ( AT91_REG * ) 0xFFFA8014 ) /* (TDES) Interrupt Disable Register */
#تعریف_کن AT91C_TDES_VR              ( ( AT91_REG * ) 0xFFFA80FC ) /* (TDES) TDES Version Register */
#تعریف_کن AT91C_TDES_IVxR            ( ( AT91_REG * ) 0xFFFA8060 ) /* (TDES) Initialization Vector x Register */
#تعریف_کن AT91C_TDES_ODATAxR         ( ( AT91_REG * ) 0xFFFA8050 ) /* (TDES) Output Data x Register */
#تعریف_کن AT91C_TDES_IMR             ( ( AT91_REG * ) 0xFFFA8018 ) /* (TDES) Interrupt Mask Register */
#تعریف_کن AT91C_TDES_MR              ( ( AT91_REG * ) 0xFFFA8004 ) /* (TDES) Mode Register */
#تعریف_کن AT91C_TDES_CR              ( ( AT91_REG * ) 0xFFFA8000 ) /* (TDES) Control Register */
#تعریف_کن AT91C_TDES_IER             ( ( AT91_REG * ) 0xFFFA8010 ) /* (TDES) Interrupt Enable Register */
#تعریف_کن AT91C_TDES_ISR             ( ( AT91_REG * ) 0xFFFA801C ) /* (TDES) Interrupt Status Register */
#تعریف_کن AT91C_TDES_IDATAxR         ( ( AT91_REG * ) 0xFFFA8040 ) /* (TDES) Input Data x Register */
#تعریف_کن AT91C_TDES_KEY1WxR         ( ( AT91_REG * ) 0xFFFA8020 ) /* (TDES) Key 1 Word x Register */

/* ***************************************************************************** */
/*               PIO DEFINITIONS FOR AT91SAM7X256 */
/* ***************************************************************************** */
#تعریف_کن AT91C_PIO_PA0             ( ( بیعلامت صحيح ) 1 << 0 )         /* Pin Controlled by PA0 */
#تعریف_کن AT91C_PA0_RXD0            ( ( بیعلامت صحيح ) AT91C_PIO_PA0 )  /*  USART 0 Receive Data */
#تعریف_کن AT91C_PIO_PA1             ( ( بیعلامت صحيح ) 1 << 1 )         /* Pin Controlled by PA1 */
#تعریف_کن AT91C_PA1_TXD0            ( ( بیعلامت صحيح ) AT91C_PIO_PA1 )  /*  USART 0 Transmit Data */
#تعریف_کن AT91C_PIO_PA10            ( ( بیعلامت صحيح ) 1 << 10 )        /* Pin Controlled by PA10 */
#تعریف_کن AT91C_PA10_TWD            ( ( بیعلامت صحيح ) AT91C_PIO_PA10 ) /*  TWI Two-wire Serial Data */
#تعریف_کن AT91C_PIO_PA11            ( ( بیعلامت صحيح ) 1 << 11 )        /* Pin Controlled by PA11 */
#تعریف_کن AT91C_PA11_TWCK           ( ( بیعلامت صحيح ) AT91C_PIO_PA11 ) /*  TWI Two-wire Serial Clock */
#تعریف_کن AT91C_PIO_PA12            ( ( بیعلامت صحيح ) 1 << 12 )        /* Pin Controlled by PA12 */
#تعریف_کن AT91C_PA12_NPCS00         ( ( بیعلامت صحيح ) AT91C_PIO_PA12 ) /*  SPI 0 Peripheral Chip Select 0 */
#تعریف_کن AT91C_PIO_PA13            ( ( بیعلامت صحيح ) 1 << 13 )        /* Pin Controlled by PA13 */
#تعریف_کن AT91C_PA13_NPCS01         ( ( بیعلامت صحيح ) AT91C_PIO_PA13 ) /*  SPI 0 Peripheral Chip Select 1 */
#تعریف_کن AT91C_PA13_PCK1           ( ( بیعلامت صحيح ) AT91C_PIO_PA13 ) /*  PMC Programmable Clock Output 1 */
#تعریف_کن AT91C_PIO_PA14            ( ( بیعلامت صحيح ) 1 << 14 )        /* Pin Controlled by PA14 */
#تعریف_کن AT91C_PA14_NPCS02         ( ( بیعلامت صحيح ) AT91C_PIO_PA14 ) /*  SPI 0 Peripheral Chip Select 2 */
#تعریف_کن AT91C_PA14_IRQ1           ( ( بیعلامت صحيح ) AT91C_PIO_PA14 ) /*  External Interrupt 1 */
#تعریف_کن AT91C_PIO_PA15            ( ( بیعلامت صحيح ) 1 << 15 )        /* Pin Controlled by PA15 */
#تعریف_کن AT91C_PA15_NPCS03         ( ( بیعلامت صحيح ) AT91C_PIO_PA15 ) /*  SPI 0 Peripheral Chip Select 3 */
#تعریف_کن AT91C_PA15_TCLK2          ( ( بیعلامت صحيح ) AT91C_PIO_PA15 ) /*  Timer Counter 2 external clock input */
#تعریف_کن AT91C_PIO_PA16            ( ( بیعلامت صحيح ) 1 << 16 )        /* Pin Controlled by PA16 */
#تعریف_کن AT91C_PA16_MISO0          ( ( بیعلامت صحيح ) AT91C_PIO_PA16 ) /*  SPI 0 Master In Slave */
#تعریف_کن AT91C_PIO_PA17            ( ( بیعلامت صحيح ) 1 << 17 )        /* Pin Controlled by PA17 */
#تعریف_کن AT91C_PA17_MOSI0          ( ( بیعلامت صحيح ) AT91C_PIO_PA17 ) /*  SPI 0 Master Out Slave */
#تعریف_کن AT91C_PIO_PA18            ( ( بیعلامت صحيح ) 1 << 18 )        /* Pin Controlled by PA18 */
#تعریف_کن AT91C_PA18_SPCK0          ( ( بیعلامت صحيح ) AT91C_PIO_PA18 ) /*  SPI 0 Serial Clock */
#تعریف_کن AT91C_PIO_PA19            ( ( بیعلامت صحيح ) 1 << 19 )        /* Pin Controlled by PA19 */
#تعریف_کن AT91C_PA19_CANRX          ( ( بیعلامت صحيح ) AT91C_PIO_PA19 ) /*  CAN Receive */
#تعریف_کن AT91C_PIO_PA2             ( ( بیعلامت صحيح ) 1 << 2 )         /* Pin Controlled by PA2 */
#تعریف_کن AT91C_PA2_SCK0            ( ( بیعلامت صحيح ) AT91C_PIO_PA2 )  /*  USART 0 Serial Clock */
#تعریف_کن AT91C_PA2_NPCS11          ( ( بیعلامت صحيح ) AT91C_PIO_PA2 )  /*  SPI 1 Peripheral Chip Select 1 */
#تعریف_کن AT91C_PIO_PA20            ( ( بیعلامت صحيح ) 1 << 20 )        /* Pin Controlled by PA20 */
#تعریف_کن AT91C_PA20_CANTX          ( ( بیعلامت صحيح ) AT91C_PIO_PA20 ) /*  CAN Transmit */
#تعریف_کن AT91C_PIO_PA21            ( ( بیعلامت صحيح ) 1 << 21 )        /* Pin Controlled by PA21 */
#تعریف_کن AT91C_PA21_TF             ( ( بیعلامت صحيح ) AT91C_PIO_PA21 ) /*  SSC Transmit Frame Sync */
#تعریف_کن AT91C_PA21_NPCS10         ( ( بیعلامت صحيح ) AT91C_PIO_PA21 ) /*  SPI 1 Peripheral Chip Select 0 */
#تعریف_کن AT91C_PIO_PA22            ( ( بیعلامت صحيح ) 1 << 22 )        /* Pin Controlled by PA22 */
#تعریف_کن AT91C_PA22_TK             ( ( بیعلامت صحيح ) AT91C_PIO_PA22 ) /*  SSC Transmit Clock */
#تعریف_کن AT91C_PA22_SPCK1          ( ( بیعلامت صحيح ) AT91C_PIO_PA22 ) /*  SPI 1 Serial Clock */
#تعریف_کن AT91C_PIO_PA23            ( ( بیعلامت صحيح ) 1 << 23 )        /* Pin Controlled by PA23 */
#تعریف_کن AT91C_PA23_TD             ( ( بیعلامت صحيح ) AT91C_PIO_PA23 ) /*  SSC Transmit data */
#تعریف_کن AT91C_PA23_MOSI1          ( ( بیعلامت صحيح ) AT91C_PIO_PA23 ) /*  SPI 1 Master Out Slave */
#تعریف_کن AT91C_PIO_PA24            ( ( بیعلامت صحيح ) 1 << 24 )        /* Pin Controlled by PA24 */
#تعریف_کن AT91C_PA24_RD             ( ( بیعلامت صحيح ) AT91C_PIO_PA24 ) /*  SSC Receive Data */
#تعریف_کن AT91C_PA24_MISO1          ( ( بیعلامت صحيح ) AT91C_PIO_PA24 ) /*  SPI 1 Master In Slave */
#تعریف_کن AT91C_PIO_PA25            ( ( بیعلامت صحيح ) 1 << 25 )        /* Pin Controlled by PA25 */
#تعریف_کن AT91C_PA25_RK             ( ( بیعلامت صحيح ) AT91C_PIO_PA25 ) /*  SSC Receive Clock */
#تعریف_کن AT91C_PA25_NPCS11         ( ( بیعلامت صحيح ) AT91C_PIO_PA25 ) /*  SPI 1 Peripheral Chip Select 1 */
#تعریف_کن AT91C_PIO_PA26            ( ( بیعلامت صحيح ) 1 << 26 )        /* Pin Controlled by PA26 */
#تعریف_کن AT91C_PA26_RF             ( ( بیعلامت صحيح ) AT91C_PIO_PA26 ) /*  SSC Receive Frame Sync */
#تعریف_کن AT91C_PA26_NPCS12         ( ( بیعلامت صحيح ) AT91C_PIO_PA26 ) /*  SPI 1 Peripheral Chip Select 2 */
#تعریف_کن AT91C_PIO_PA27            ( ( بیعلامت صحيح ) 1 << 27 )        /* Pin Controlled by PA27 */
#تعریف_کن AT91C_PA27_DRXD           ( ( بیعلامت صحيح ) AT91C_PIO_PA27 ) /*  DBGU Debug Receive Data */
#تعریف_کن AT91C_PA27_PCK3           ( ( بیعلامت صحيح ) AT91C_PIO_PA27 ) /*  PMC Programmable Clock Output 3 */
#تعریف_کن AT91C_PIO_PA28            ( ( بیعلامت صحيح ) 1 << 28 )        /* Pin Controlled by PA28 */
#تعریف_کن AT91C_PA28_DTXD           ( ( بیعلامت صحيح ) AT91C_PIO_PA28 ) /*  DBGU Debug Transmit Data */
#تعریف_کن AT91C_PIO_PA29            ( ( بیعلامت صحيح ) 1 << 29 )        /* Pin Controlled by PA29 */
#تعریف_کن AT91C_PA29_FIQ            ( ( بیعلامت صحيح ) AT91C_PIO_PA29 ) /*  AIC Fast Interrupt Input */
#تعریف_کن AT91C_PA29_NPCS13         ( ( بیعلامت صحيح ) AT91C_PIO_PA29 ) /*  SPI 1 Peripheral Chip Select 3 */
#تعریف_کن AT91C_PIO_PA3             ( ( بیعلامت صحيح ) 1 << 3 )         /* Pin Controlled by PA3 */
#تعریف_کن AT91C_PA3_RTS0            ( ( بیعلامت صحيح ) AT91C_PIO_PA3 )  /*  USART 0 Ready To Send */
#تعریف_کن AT91C_PA3_NPCS12          ( ( بیعلامت صحيح ) AT91C_PIO_PA3 )  /*  SPI 1 Peripheral Chip Select 2 */
#تعریف_کن AT91C_PIO_PA30            ( ( بیعلامت صحيح ) 1 << 30 )        /* Pin Controlled by PA30 */
#تعریف_کن AT91C_PA30_IRQ0           ( ( بیعلامت صحيح ) AT91C_PIO_PA30 ) /*  External Interrupt 0 */
#تعریف_کن AT91C_PA30_PCK2           ( ( بیعلامت صحيح ) AT91C_PIO_PA30 ) /*  PMC Programmable Clock Output 2 */
#تعریف_کن AT91C_PIO_PA4             ( ( بیعلامت صحيح ) 1 << 4 )         /* Pin Controlled by PA4 */
#تعریف_کن AT91C_PA4_CTS0            ( ( بیعلامت صحيح ) AT91C_PIO_PA4 )  /*  USART 0 Clear To Send */
#تعریف_کن AT91C_PA4_NPCS13          ( ( بیعلامت صحيح ) AT91C_PIO_PA4 )  /*  SPI 1 Peripheral Chip Select 3 */
#تعریف_کن AT91C_PIO_PA5             ( ( بیعلامت صحيح ) 1 << 5 )         /* Pin Controlled by PA5 */
#تعریف_کن AT91C_PA5_RXD1            ( ( بیعلامت صحيح ) AT91C_PIO_PA5 )  /*  USART 1 Receive Data */
#تعریف_کن AT91C_PIO_PA6             ( ( بیعلامت صحيح ) 1 << 6 )         /* Pin Controlled by PA6 */
#تعریف_کن AT91C_PA6_TXD1            ( ( بیعلامت صحيح ) AT91C_PIO_PA6 )  /*  USART 1 Transmit Data */
#تعریف_کن AT91C_PIO_PA7             ( ( بیعلامت صحيح ) 1 << 7 )         /* Pin Controlled by PA7 */
#تعریف_کن AT91C_PA7_SCK1            ( ( بیعلامت صحيح ) AT91C_PIO_PA7 )  /*  USART 1 Serial Clock */
#تعریف_کن AT91C_PA7_NPCS01          ( ( بیعلامت صحيح ) AT91C_PIO_PA7 )  /*  SPI 0 Peripheral Chip Select 1 */
#تعریف_کن AT91C_PIO_PA8             ( ( بیعلامت صحيح ) 1 << 8 )         /* Pin Controlled by PA8 */
#تعریف_کن AT91C_PA8_RTS1            ( ( بیعلامت صحيح ) AT91C_PIO_PA8 )  /*  USART 1 Ready To Send */
#تعریف_کن AT91C_PA8_NPCS02          ( ( بیعلامت صحيح ) AT91C_PIO_PA8 )  /*  SPI 0 Peripheral Chip Select 2 */
#تعریف_کن AT91C_PIO_PA9             ( ( بیعلامت صحيح ) 1 << 9 )         /* Pin Controlled by PA9 */
#تعریف_کن AT91C_PA9_CTS1            ( ( بیعلامت صحيح ) AT91C_PIO_PA9 )  /*  USART 1 Clear To Send */
#تعریف_کن AT91C_PA9_NPCS03          ( ( بیعلامت صحيح ) AT91C_PIO_PA9 )  /*  SPI 0 Peripheral Chip Select 3 */
#تعریف_کن AT91C_PIO_PB0             ( ( بیعلامت صحيح ) 1 << 0 )         /* Pin Controlled by PB0 */
#تعریف_کن AT91C_PB0_ETXCK_EREFCK    ( ( بیعلامت صحيح ) AT91C_PIO_PB0 )  /*  Ethernet MAC Transmit Clock/Reference Clock */
#تعریف_کن AT91C_PB0_PCK0            ( ( بیعلامت صحيح ) AT91C_PIO_PB0 )  /*  PMC Programmable Clock Output 0 */
#تعریف_کن AT91C_PIO_PB1             ( ( بیعلامت صحيح ) 1 << 1 )         /* Pin Controlled by PB1 */
#تعریف_کن AT91C_PB1_ETXEN           ( ( بیعلامت صحيح ) AT91C_PIO_PB1 )  /*  Ethernet MAC Transmit Enable */
#تعریف_کن AT91C_PIO_PB10            ( ( بیعلامت صحيح ) 1 << 10 )        /* Pin Controlled by PB10 */
#تعریف_کن AT91C_PB10_ETX2           ( ( بیعلامت صحيح ) AT91C_PIO_PB10 ) /*  Ethernet MAC Transmit Data 2 */
#تعریف_کن AT91C_PB10_NPCS11         ( ( بیعلامت صحيح ) AT91C_PIO_PB10 ) /*  SPI 1 Peripheral Chip Select 1 */
#تعریف_کن AT91C_PIO_PB11            ( ( بیعلامت صحيح ) 1 << 11 )        /* Pin Controlled by PB11 */
#تعریف_کن AT91C_PB11_ETX3           ( ( بیعلامت صحيح ) AT91C_PIO_PB11 ) /*  Ethernet MAC Transmit Data 3 */
#تعریف_کن AT91C_PB11_NPCS12         ( ( بیعلامت صحيح ) AT91C_PIO_PB11 ) /*  SPI 1 Peripheral Chip Select 2 */
#تعریف_کن AT91C_PIO_PB12            ( ( بیعلامت صحيح ) 1 << 12 )        /* Pin Controlled by PB12 */
#تعریف_کن AT91C_PB12_ETXER          ( ( بیعلامت صحيح ) AT91C_PIO_PB12 ) /*  Ethernet MAC Transmit Coding Error */
#تعریف_کن AT91C_PB12_TCLK0          ( ( بیعلامت صحيح ) AT91C_PIO_PB12 ) /*  Timer Counter 0 external clock input */
#تعریف_کن AT91C_PIO_PB13            ( ( بیعلامت صحيح ) 1 << 13 )        /* Pin Controlled by PB13 */
#تعریف_کن AT91C_PB13_ERX2           ( ( بیعلامت صحيح ) AT91C_PIO_PB13 ) /*  Ethernet MAC Receive Data 2 */
#تعریف_کن AT91C_PB13_NPCS01         ( ( بیعلامت صحيح ) AT91C_PIO_PB13 ) /*  SPI 0 Peripheral Chip Select 1 */
#تعریف_کن AT91C_PIO_PB14            ( ( بیعلامت صحيح ) 1 << 14 )        /* Pin Controlled by PB14 */
#تعریف_کن AT91C_PB14_ERX3           ( ( بیعلامت صحيح ) AT91C_PIO_PB14 ) /*  Ethernet MAC Receive Data 3 */
#تعریف_کن AT91C_PB14_NPCS02         ( ( بیعلامت صحيح ) AT91C_PIO_PB14 ) /*  SPI 0 Peripheral Chip Select 2 */
#تعریف_کن AT91C_PIO_PB15            ( ( بیعلامت صحيح ) 1 << 15 )        /* Pin Controlled by PB15 */
#تعریف_کن AT91C_PB15_ERXDV          ( ( بیعلامت صحيح ) AT91C_PIO_PB15 ) /*  Ethernet MAC Receive Data Valid */
#تعریف_کن AT91C_PIO_PB16            ( ( بیعلامت صحيح ) 1 << 16 )        /* Pin Controlled by PB16 */
#تعریف_کن AT91C_PB16_ECOL           ( ( بیعلامت صحيح ) AT91C_PIO_PB16 ) /*  Ethernet MAC Collision Detected */
#تعریف_کن AT91C_PB16_NPCS13         ( ( بیعلامت صحيح ) AT91C_PIO_PB16 ) /*  SPI 1 Peripheral Chip Select 3 */
#تعریف_کن AT91C_PIO_PB17            ( ( بیعلامت صحيح ) 1 << 17 )        /* Pin Controlled by PB17 */
#تعریف_کن AT91C_PB17_ERXCK          ( ( بیعلامت صحيح ) AT91C_PIO_PB17 ) /*  Ethernet MAC Receive Clock */
#تعریف_کن AT91C_PB17_NPCS03         ( ( بیعلامت صحيح ) AT91C_PIO_PB17 ) /*  SPI 0 Peripheral Chip Select 3 */
#تعریف_کن AT91C_PIO_PB18            ( ( بیعلامت صحيح ) 1 << 18 )        /* Pin Controlled by PB18 */
#تعریف_کن AT91C_PB18_EF100          ( ( بیعلامت صحيح ) AT91C_PIO_PB18 ) /*  Ethernet MAC Force 100 Mbits/sec */
#تعریف_کن AT91C_PB18_ADTRG          ( ( بیعلامت صحيح ) AT91C_PIO_PB18 ) /*  ADC External Trigger */
#تعریف_کن AT91C_PIO_PB19            ( ( بیعلامت صحيح ) 1 << 19 )        /* Pin Controlled by PB19 */
#تعریف_کن AT91C_PB19_PWM0           ( ( بیعلامت صحيح ) AT91C_PIO_PB19 ) /*  PWM Channel 0 */
#تعریف_کن AT91C_PB19_TCLK1          ( ( بیعلامت صحيح ) AT91C_PIO_PB19 ) /*  Timer Counter 1 external clock input */
#تعریف_کن AT91C_PIO_PB2             ( ( بیعلامت صحيح ) 1 << 2 )         /* Pin Controlled by PB2 */
#تعریف_کن AT91C_PB2_ETX0            ( ( بیعلامت صحيح ) AT91C_PIO_PB2 )  /*  Ethernet MAC Transmit Data 0 */
#تعریف_کن AT91C_PIO_PB20            ( ( بیعلامت صحيح ) 1 << 20 )        /* Pin Controlled by PB20 */
#تعریف_کن AT91C_PB20_PWM1           ( ( بیعلامت صحيح ) AT91C_PIO_PB20 ) /*  PWM Channel 1 */
#تعریف_کن AT91C_PB20_PCK0           ( ( بیعلامت صحيح ) AT91C_PIO_PB20 ) /*  PMC Programmable Clock Output 0 */
#تعریف_کن AT91C_PIO_PB21            ( ( بیعلامت صحيح ) 1 << 21 )        /* Pin Controlled by PB21 */
#تعریف_کن AT91C_PB21_PWM2           ( ( بیعلامت صحيح ) AT91C_PIO_PB21 ) /*  PWM Channel 2 */
#تعریف_کن AT91C_PB21_PCK1           ( ( بیعلامت صحيح ) AT91C_PIO_PB21 ) /*  PMC Programmable Clock Output 1 */
#تعریف_کن AT91C_PIO_PB22            ( ( بیعلامت صحيح ) 1 << 22 )        /* Pin Controlled by PB22 */
#تعریف_کن AT91C_PB22_PWM3           ( ( بیعلامت صحيح ) AT91C_PIO_PB22 ) /*  PWM Channel 3 */
#تعریف_کن AT91C_PB22_PCK2           ( ( بیعلامت صحيح ) AT91C_PIO_PB22 ) /*  PMC Programmable Clock Output 2 */
#تعریف_کن AT91C_PIO_PB23            ( ( بیعلامت صحيح ) 1 << 23 )        /* Pin Controlled by PB23 */
#تعریف_کن AT91C_PB23_TIOA0          ( ( بیعلامت صحيح ) AT91C_PIO_PB23 ) /*  Timer Counter 0 Multipurpose Timer I/O Pin A */
#تعریف_کن AT91C_PB23_DCD1           ( ( بیعلامت صحيح ) AT91C_PIO_PB23 ) /*  USART 1 Data Carrier Detect */
#تعریف_کن AT91C_PIO_PB24            ( ( بیعلامت صحيح ) 1 << 24 )        /* Pin Controlled by PB24 */
#تعریف_کن AT91C_PB24_TIOB0          ( ( بیعلامت صحيح ) AT91C_PIO_PB24 ) /*  Timer Counter 0 Multipurpose Timer I/O Pin B */
#تعریف_کن AT91C_PB24_DSR1           ( ( بیعلامت صحيح ) AT91C_PIO_PB24 ) /*  USART 1 Data Set ready */
#تعریف_کن AT91C_PIO_PB25            ( ( بیعلامت صحيح ) 1 << 25 )        /* Pin Controlled by PB25 */
#تعریف_کن AT91C_PB25_TIOA1          ( ( بیعلامت صحيح ) AT91C_PIO_PB25 ) /*  Timer Counter 1 Multipurpose Timer I/O Pin A */
#تعریف_کن AT91C_PB25_DTR1           ( ( بیعلامت صحيح ) AT91C_PIO_PB25 ) /*  USART 1 Data Terminal ready */
#تعریف_کن AT91C_PIO_PB26            ( ( بیعلامت صحيح ) 1 << 26 )        /* Pin Controlled by PB26 */
#تعریف_کن AT91C_PB26_TIOB1          ( ( بیعلامت صحيح ) AT91C_PIO_PB26 ) /*  Timer Counter 1 Multipurpose Timer I/O Pin B */
#تعریف_کن AT91C_PB26_RI1            ( ( بیعلامت صحيح ) AT91C_PIO_PB26 ) /*  USART 1 Ring Indicator */
#تعریف_کن AT91C_PIO_PB27            ( ( بیعلامت صحيح ) 1 << 27 )        /* Pin Controlled by PB27 */
#تعریف_کن AT91C_PB27_TIOA2          ( ( بیعلامت صحيح ) AT91C_PIO_PB27 ) /*  Timer Counter 2 Multipurpose Timer I/O Pin A */
#تعریف_کن AT91C_PB27_PWM0           ( ( بیعلامت صحيح ) AT91C_PIO_PB27 ) /*  PWM Channel 0 */
#تعریف_کن AT91C_PIO_PB28            ( ( بیعلامت صحيح ) 1 << 28 )        /* Pin Controlled by PB28 */
#تعریف_کن AT91C_PB28_TIOB2          ( ( بیعلامت صحيح ) AT91C_PIO_PB28 ) /*  Timer Counter 2 Multipurpose Timer I/O Pin B */
#تعریف_کن AT91C_PB28_PWM1           ( ( بیعلامت صحيح ) AT91C_PIO_PB28 ) /*  PWM Channel 1 */
#تعریف_کن AT91C_PIO_PB29            ( ( بیعلامت صحيح ) 1 << 29 )        /* Pin Controlled by PB29 */
#تعریف_کن AT91C_PB29_PCK1           ( ( بیعلامت صحيح ) AT91C_PIO_PB29 ) /*  PMC Programmable Clock Output 1 */
#تعریف_کن AT91C_PB29_PWM2           ( ( بیعلامت صحيح ) AT91C_PIO_PB29 ) /*  PWM Channel 2 */
#تعریف_کن AT91C_PIO_PB3             ( ( بیعلامت صحيح ) 1 << 3 )         /* Pin Controlled by PB3 */
#تعریف_کن AT91C_PB3_ETX1            ( ( بیعلامت صحيح ) AT91C_PIO_PB3 )  /*  Ethernet MAC Transmit Data 1 */
#تعریف_کن AT91C_PIO_PB30            ( ( بیعلامت صحيح ) 1 << 30 )        /* Pin Controlled by PB30 */
#تعریف_کن AT91C_PB30_PCK2           ( ( بیعلامت صحيح ) AT91C_PIO_PB30 ) /*  PMC Programmable Clock Output 2 */
#تعریف_کن AT91C_PB30_PWM3           ( ( بیعلامت صحيح ) AT91C_PIO_PB30 ) /*  PWM Channel 3 */
#تعریف_کن AT91C_PIO_PB4             ( ( بیعلامت صحيح ) 1 << 4 )         /* Pin Controlled by PB4 */
#تعریف_کن AT91C_PB4_ECRS_ECRSDV     ( ( بیعلامت صحيح ) AT91C_PIO_PB4 )  /*  Ethernet MAC Carrier Sense/Carrier Sense and Data Valid */
#تعریف_کن AT91C_PIO_PB5             ( ( بیعلامت صحيح ) 1 << 5 )         /* Pin Controlled by PB5 */
#تعریف_کن AT91C_PB5_ERX0            ( ( بیعلامت صحيح ) AT91C_PIO_PB5 )  /*  Ethernet MAC Receive Data 0 */
#تعریف_کن AT91C_PIO_PB6             ( ( بیعلامت صحيح ) 1 << 6 )         /* Pin Controlled by PB6 */
#تعریف_کن AT91C_PB6_ERX1            ( ( بیعلامت صحيح ) AT91C_PIO_PB6 )  /*  Ethernet MAC Receive Data 1 */
#تعریف_کن AT91C_PIO_PB7             ( ( بیعلامت صحيح ) 1 << 7 )         /* Pin Controlled by PB7 */
#تعریف_کن AT91C_PB7_ERXER           ( ( بیعلامت صحيح ) AT91C_PIO_PB7 )  /*  Ethernet MAC Receive Error */
#تعریف_کن AT91C_PIO_PB8             ( ( بیعلامت صحيح ) 1 << 8 )         /* Pin Controlled by PB8 */
#تعریف_کن AT91C_PB8_EMDC            ( ( بیعلامت صحيح ) AT91C_PIO_PB8 )  /*  Ethernet MAC Management Data Clock */
#تعریف_کن AT91C_PIO_PB9             ( ( بیعلامت صحيح ) 1 << 9 )         /* Pin Controlled by PB9 */
#تعریف_کن AT91C_PB9_EMDIO           ( ( بیعلامت صحيح ) AT91C_PIO_PB9 )  /*  Ethernet MAC Management Data Input/Output */

/* ***************************************************************************** */
/*               PERIPHERAL ID DEFINITIONS FOR AT91SAM7X256 */
/* ***************************************************************************** */
#تعریف_کن AT91C_ID_FIQ            ( ( بیعلامت صحيح ) 0 )  /* Advanced Interrupt Controller (FIQ) */
#تعریف_کن AT91C_ID_SYS            ( ( بیعلامت صحيح ) 1 )  /* System Peripheral */
#تعریف_کن AT91C_ID_PIOA           ( ( بیعلامت صحيح ) 2 )  /* Parallel IO Controller A */
#تعریف_کن AT91C_ID_PIOB           ( ( بیعلامت صحيح ) 3 )  /* Parallel IO Controller B */
#تعریف_کن AT91C_ID_SPI0           ( ( بیعلامت صحيح ) 4 )  /* Serial Peripheral Interface 0 */
#تعریف_کن AT91C_ID_SPI1           ( ( بیعلامت صحيح ) 5 )  /* Serial Peripheral Interface 1 */
#تعریف_کن AT91C_ID_US0            ( ( بیعلامت صحيح ) 6 )  /* USART 0 */
#تعریف_کن AT91C_ID_US1            ( ( بیعلامت صحيح ) 7 )  /* USART 1 */
#تعریف_کن AT91C_ID_SSC            ( ( بیعلامت صحيح ) 8 )  /* Serial Synchronous Controller */
#تعریف_کن AT91C_ID_TWI            ( ( بیعلامت صحيح ) 9 )  /* Two-Wire Interface */
#تعریف_کن AT91C_ID_PWMC           ( ( بیعلامت صحيح ) 10 ) /* PWM Controller */
#تعریف_کن AT91C_ID_UDP            ( ( بیعلامت صحيح ) 11 ) /* USB Device Port */
#تعریف_کن AT91C_ID_TC0            ( ( بیعلامت صحيح ) 12 ) /* Timer Counter 0 */
#تعریف_کن AT91C_ID_TC1            ( ( بیعلامت صحيح ) 13 ) /* Timer Counter 1 */
#تعریف_کن AT91C_ID_TC2            ( ( بیعلامت صحيح ) 14 ) /* Timer Counter 2 */
#تعریف_کن AT91C_ID_CAN            ( ( بیعلامت صحيح ) 15 ) /* Control Area Network Controller */
#تعریف_کن AT91C_ID_EMAC           ( ( بیعلامت صحيح ) 16 ) /* Ethernet MAC */
#تعریف_کن AT91C_ID_ADC            ( ( بیعلامت صحيح ) 17 ) /* Analog-to-Digital Converter */
#تعریف_کن AT91C_ID_AES            ( ( بیعلامت صحيح ) 18 ) /* Advanced Encryption Standard 128-bit */
#تعریف_کن AT91C_ID_TDES           ( ( بیعلامت صحيح ) 19 ) /* Triple Data Encryption Standard */
#تعریف_کن AT91C_ID_20_Reserved    ( ( بیعلامت صحيح ) 20 ) /* Reserved */
#تعریف_کن AT91C_ID_21_Reserved    ( ( بیعلامت صحيح ) 21 ) /* Reserved */
#تعریف_کن AT91C_ID_22_Reserved    ( ( بیعلامت صحيح ) 22 ) /* Reserved */
#تعریف_کن AT91C_ID_23_Reserved    ( ( بیعلامت صحيح ) 23 ) /* Reserved */
#تعریف_کن AT91C_ID_24_Reserved    ( ( بیعلامت صحيح ) 24 ) /* Reserved */
#تعریف_کن AT91C_ID_25_Reserved    ( ( بیعلامت صحيح ) 25 ) /* Reserved */
#تعریف_کن AT91C_ID_26_Reserved    ( ( بیعلامت صحيح ) 26 ) /* Reserved */
#تعریف_کن AT91C_ID_27_Reserved    ( ( بیعلامت صحيح ) 27 ) /* Reserved */
#تعریف_کن AT91C_ID_28_Reserved    ( ( بیعلامت صحيح ) 28 ) /* Reserved */
#تعریف_کن AT91C_ID_29_Reserved    ( ( بیعلامت صحيح ) 29 ) /* Reserved */
#تعریف_کن AT91C_ID_IRQ0           ( ( بیعلامت صحيح ) 30 ) /* Advanced Interrupt Controller (IRQ0) */
#تعریف_کن AT91C_ID_IRQ1           ( ( بیعلامت صحيح ) 31 ) /* Advanced Interrupt Controller (IRQ1) */

/* ***************************************************************************** */
/*               BASE ADDRESS DEFINITIONS FOR AT91SAM7X256 */
/* ***************************************************************************** */
#تعریف_کن AT91_C_پایه_SYS         ( ( AT91PS_SYS ) 0xFFFFF000 )     /* (SYS) Base Address */
#تعریف_کن AT91_C_پایه_AIC         ( ( AT91PS_AIC ) 0xFFFFF000 )     /* (AIC) Base Address */
#تعریف_کن AT91_C_پایه_PDC_DBGU    ( ( AT91PS_PDC ) 0xFFFFF300 )     /* (PDC_DBGU) Base Address */
#تعریف_کن AT91_C_پایه_DBGU        ( ( AT91PS_DBGU ) 0xFFFFF200 )    /* (DBGU) Base Address */
#تعریف_کن AT91_C_پایه_PIOA        ( ( AT91PS_PIO ) 0xFFFFF400 )     /* (PIOA) Base Address */
#تعریف_کن AT91_C_پایه_PIOB        ( ( AT91PS_PIO ) 0xFFFFF600 )     /* (PIOB) Base Address */
#تعریف_کن AT91_C_پایه_CKGR        ( ( AT91PS_CKGR ) 0xFFFFFC20 )    /* (CKGR) Base Address */
#تعریف_کن AT91_C_پایه_PMC         ( ( AT91PS_PMC ) 0xFFFFFC00 )     /* (PMC) Base Address */
#تعریف_کن AT91_C_پایه_RSTC        ( ( AT91PS_RSTC ) 0xFFFFFD00 )    /* (RSTC) Base Address */
#تعریف_کن AT91_C_پایه_RTTC        ( ( AT91PS_RTTC ) 0xFFFFFD20 )    /* (RTTC) Base Address */
#تعریف_کن AT91_C_پایه_PITC        ( ( AT91PS_PITC ) 0xFFFFFD30 )    /* (PITC) Base Address */
#تعریف_کن AT91_C_پایه_WDTC        ( ( AT91PS_WDTC ) 0xFFFFFD40 )    /* (WDTC) Base Address */
#تعریف_کن AT91_C_پایه_VREG        ( ( AT91PS_VREG ) 0xFFFFFD60 )    /* (VREG) Base Address */
#تعریف_کن AT91_C_پایه_MC          ( ( AT91PS_MC ) 0xFFFFFF00 )      /* (MC) Base Address */
#تعریف_کن AT91_C_پایه_PDC_SPI1    ( ( AT91PS_PDC ) 0xFFFE4100 )     /* (PDC_SPI1) Base Address */
#تعریف_کن AT91_C_پایه_SPI1        ( ( AT91PS_SPI ) 0xFFFE4000 )     /* (SPI1) Base Address */
#تعریف_کن AT91_C_پایه_PDC_SPI0    ( ( AT91PS_PDC ) 0xFFFE0100 )     /* (PDC_SPI0) Base Address */
#تعریف_کن AT91_C_پایه_SPI0        ( ( AT91PS_SPI ) 0xFFFE0000 )     /* (SPI0) Base Address */
#تعریف_کن AT91_C_پایه_PDC_US1     ( ( AT91PS_PDC ) 0xFFFC4100 )     /* (PDC_US1) Base Address */
#تعریف_کن AT91_C_پایه_US1         ( ( AT91PS_USART ) 0xFFFC4000 )   /* (US1) Base Address */
#تعریف_کن AT91_C_پایه_PDC_US0     ( ( AT91PS_PDC ) 0xFFFC0100 )     /* (PDC_US0) Base Address */
#تعریف_کن AT91_C_پایه_US0         ( ( AT91PS_USART ) 0xFFFC0000 )   /* (US0) Base Address */
#تعریف_کن AT91_C_پایه_PDC_SSC     ( ( AT91PS_PDC ) 0xFFFD4100 )     /* (PDC_SSC) Base Address */
#تعریف_کن AT91_C_پایه_SSC         ( ( AT91PS_SSC ) 0xFFFD4000 )     /* (SSC) Base Address */
#تعریف_کن AT91_C_پایه_TWI         ( ( AT91PS_TWI ) 0xFFFB8000 )     /* (TWI) Base Address */
#تعریف_کن AT91_C_پایه_PWMC_CH3    ( ( AT91PS_PWMC_CH ) 0xFFFCC260 ) /* (PWMC_CH3) Base Address */
#تعریف_کن AT91_C_پایه_PWMC_CH2    ( ( AT91PS_PWMC_CH ) 0xFFFCC240 ) /* (PWMC_CH2) Base Address */
#تعریف_کن AT91_C_پایه_PWMC_CH1    ( ( AT91PS_PWMC_CH ) 0xFFFCC220 ) /* (PWMC_CH1) Base Address */
#تعریف_کن AT91_C_پایه_PWMC_CH0    ( ( AT91PS_PWMC_CH ) 0xFFFCC200 ) /* (PWMC_CH0) Base Address */
#تعریف_کن AT91_C_پایه_PWMC        ( ( AT91PS_PWMC ) 0xFFFCC000 )    /* (PWMC) Base Address */
#تعریف_کن AT91_C_پایه_UDP         ( ( AT91PS_UDP ) 0xFFFB0000 )     /* (UDP) Base Address */
#تعریف_کن AT91_C_پایه_TC0         ( ( AT91PS_TC ) 0xFFFA0000 )      /* (TC0) Base Address */
#تعریف_کن AT91_C_پایه_TC1         ( ( AT91PS_TC ) 0xFFFA0040 )      /* (TC1) Base Address */
#تعریف_کن AT91_C_پایه_TC2         ( ( AT91PS_TC ) 0xFFFA0080 )      /* (TC2) Base Address */
#تعریف_کن AT91_C_پایه_TCB         ( ( AT91PS_TCB ) 0xFFFA0000 )     /* (TCB) Base Address */
#تعریف_کن AT91_C_پایه_CAN_MB0     ( ( AT91PS_CAN_MB ) 0xFFFD0200 )  /* (CAN_MB0) Base Address */
#تعریف_کن AT91_C_پایه_CAN_MB1     ( ( AT91PS_CAN_MB ) 0xFFFD0220 )  /* (CAN_MB1) Base Address */
#تعریف_کن AT91_C_پایه_CAN_MB2     ( ( AT91PS_CAN_MB ) 0xFFFD0240 )  /* (CAN_MB2) Base Address */
#تعریف_کن AT91_C_پایه_CAN_MB3     ( ( AT91PS_CAN_MB ) 0xFFFD0260 )  /* (CAN_MB3) Base Address */
#تعریف_کن AT91_C_پایه_CAN_MB4     ( ( AT91PS_CAN_MB ) 0xFFFD0280 )  /* (CAN_MB4) Base Address */
#تعریف_کن AT91_C_پایه_CAN_MB5     ( ( AT91PS_CAN_MB ) 0xFFFD02A0 )  /* (CAN_MB5) Base Address */
#تعریف_کن AT91_C_پایه_CAN_MB6     ( ( AT91PS_CAN_MB ) 0xFFFD02C0 )  /* (CAN_MB6) Base Address */
#تعریف_کن AT91_C_پایه_CAN_MB7     ( ( AT91PS_CAN_MB ) 0xFFFD02E0 )  /* (CAN_MB7) Base Address */
#تعریف_کن AT91_C_پایه_CAN         ( ( AT91PS_CAN ) 0xFFFD0000 )     /* (CAN) Base Address */
#تعریف_کن AT91_C_پایه_EMAC        ( ( AT91PS_EMAC ) 0xFFFDC000 )    /* (EMAC) Base Address */
#تعریف_کن AT91_C_پایه_PDC_ADC     ( ( AT91PS_PDC ) 0xFFFD8100 )     /* (PDC_ADC) Base Address */
#تعریف_کن AT91_C_پایه_ADC         ( ( AT91PS_ADC ) 0xFFFD8000 )     /* (ADC) Base Address */
#تعریف_کن AT91_C_پایه_PDC_AES     ( ( AT91PS_PDC ) 0xFFFA4100 )     /* (PDC_AES) Base Address */
#تعریف_کن AT91_C_پایه_AES         ( ( AT91PS_AES ) 0xFFFA4000 )     /* (AES) Base Address */
#تعریف_کن AT91_C_پایه_PDC_TDES    ( ( AT91PS_PDC ) 0xFFFA8100 )     /* (PDC_TDES) Base Address */
#تعریف_کن AT91_C_پایه_TDES        ( ( AT91PS_TDES ) 0xFFFA8000 )    /* (TDES) Base Address */

/* ***************************************************************************** */
/*               MEMORY MAPPING DEFINITIONS FOR AT91SAM7X256 */
/* ***************************************************************************** */
#تعریف_کن AT91C_ISRAM          ( ( حرف * ) 0x00200000 )       /* Internal SRAM base address */
#تعریف_کن AT91_C_ISRAM_اندازه     ( ( بیعلامت صحيح ) 0x00010000 ) /* Internal SRAM size in byte (64 Kbyte) */
#تعریف_کن AT91C_IFLASH         ( ( حرف * ) 0x00100000 )       /* Internal ROM base address */
#تعریف_کن AT91_C_IFLASH_اندازه    ( ( بیعلامت صحيح ) 0x00040000 ) /* Internal ROM size in byte (256 Kbyte) */



/* - Hardware register definition */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR System Peripherals */
/* - ***************************************************************************** */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Advanced Interrupt Controller */
/* - ***************************************************************************** */
/* - -------- AIC_SMR : (AIC Offset: 0x0) Control Register -------- */
#إذا 0 /*_RB_*/
    AT91_C_AIC_پیشین EQU( 0x7 << 0 );
    -( AIC ) اولویت_2 Level
    AT91_C_AIC_پیشین_پایینترین EQU( 0x0 );
    -( AIC ) پایینترین اولویت level
    AT91_C_AIC_پیشین_HIGHEST EQU( 0x7 );
    -( AIC ) Highest اولویت level
    AT91C_AIC_SRCTYPE EQU( 0x3 << 5 );
    -( AIC ) وقفه_2 منبع_2 Type
    AT91_C_AIC_SRCTYPE_INT_بالا_LEVEL EQU( 0x0 << 5 );
    -( AIC ) داخلی Sources کد_2 Label بالا - level Sensitive
    AT91_C_AIC_SRCTYPE_EXT_کم_LEVEL EQU( 0x0 << 5 );
    -( AIC ) External Sources کد_2 Label کم - level Sensitive
    AT91_C_AIC_SRCTYPE_INT_مثبت_یال EQU( 0x1 << 5 );
    -( AIC ) داخلی Sources کد_2 Label مثبت یال triggered
    AT91_C_AIC_SRCTYPE_EXT_NEGATIVE_یال EQU( 0x1 << 5 );
    -( AIC ) External Sources کد_2 Label Negative یال triggered
    AT91_C_AIC_SRCTYPE_بالا_LEVEL EQU( 0x2 << 5 );
    -( AIC ) داخلی Or External Sources کد_2 Label بالا - level Sensitive
    AT91_C_AIC_SRCTYPE_مثبت_یال EQU( 0x3 << 5 );
    -( AIC ) داخلی Or External Sources کد_2 Label مثبت یال triggered
/* - -------- AIC_CISR : (AIC Offset: 0x114) AIC Core Interrupt Status Register -------- */
    AT91C_AIC_NFIQ EQU( 0x1 << 0 );
    -( AIC ) NFIQ وضعیت
    AT91C_AIC_NIRQ EQU( 0x1 << 1 );
    -( AIC ) NIRQ وضعیت
/* - -------- AIC_DCR : (AIC Offset: 0x138) AIC Debug Control Register (Protect) -------- */
    AT91C_AIC_DCR_PROT EQU( 0x1 << 0 );
    -( AIC ) Protection نما
    AT91C_AIC_DCR_GMSK EQU( 0x1 << 1 );
    -( AIC ) General ماسک_2
#پایان_اگر /* if 0 */
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
-( DBGU ) Reset وضعیت بیتها
/* - -------- DBGU_MR : (DBGU Offset: 0x4) Debug Unit Mode Register -------- */
AT91C_US_PAR EQU( 0x7 << 9 );
-( DBGU ) Parity type
AT91C_US_PAR_EVEN EQU( 0x0 << 9 );
-( DBGU ) Even Parity
AT91C_US_PAR_ODD EQU( 0x1 << 9 );
-( DBGU ) Odd Parity
AT91C_US_PAR_SPACE EQU( 0x2 << 9 );
-( DBGU ) Parity forced مقصد 0 ( Space )
AT91C_US_PAR_MARK EQU( 0x3 << 9 );
-( DBGU ) Parity forced مقصد 1 ( Mark )
AT91C_US_PAR_NONE EQU( 0x4 << 9 );
-( DBGU ) No Parity
AT91C_US_PAR_MULTI_DROP EQU( 0x6 << 9 );
-( DBGU ) Multi - drop نما_2
AT91C_US_CHMODE EQU( 0x3 << 14 );
-( DBGU ) Channel نما
AT91_C_US_CHMODE_نرمال EQU( 0x0 << 14 );
-( DBGU ) نرمال نما: The USART channel operates as an RX / TX USART.
   AT91C_US_CHMODE_AUTO EQU( 0x1 << 14 );
-( DBGU ) Automatic Echo: Receiver داده درون_داد is connected مقصد the TXD pin.
   AT91C_US_CHMODE_LOCAL EQU( 0x2 << 14 );
-( DBGU ) Local Loopback: Transmitter Output Signal is connected مقصد Receiver درون_داد Signal.
   AT91C_US_CHMODE_REMOTE EQU( 0x3 << 14 );
-( DBGU ) Remote Loopback: RXD pin is internally connected مقصد TXD pin.
/* - -------- DBGU_IER : (DBGU Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
   AT91C_US_RXRDY EQU( 0x1 << 0 );
-( DBGU ) RXRDY وقفه_2
AT91C_US_TXRDY EQU( 0x1 << 1 );
-( DBGU ) TXRDY وقفه_2
AT91C_US_ENDRX EQU( 0x1 << 3 );
-( DBGU ) انتها_2 از Receive Transfer وقفه_2
AT91C_US_ENDTX EQU( 0x1 << 4 );
-( DBGU ) انتها_2 از Transmit وقفه_2
AT91C_US_OVRE EQU( 0x1 << 5 );
-( DBGU ) Overrun وقفه_2
AT91_C_US_قاب EQU( 0x1 << 6 );
-( DBGU ) Framing Error وقفه_2
AT91C_US_PARE EQU( 0x1 << 7 );
-( DBGU ) Parity Error وقفه_2
AT91C_US_TXEMPTY EQU( 0x1 << 9 );
-( DBGU ) TXEMPTY وقفه_2
AT91C_US_TXBUFE EQU( 0x1 << 11 );
-( DBGU ) TXBUFE وقفه_2
AT91C_US_RXBUFF EQU( 0x1 << 12 );
-( DBGU ) RXBUFF وقفه_2
AT91C_US_COMM_TX EQU( 0x1 << 30 );
-( DBGU ) COMM_TX وقفه_2
AT91C_US_COMM_RX EQU( 0x1 << 31 );
-( DBGU ) COMM_RX وقفه_2
/* - -------- DBGU_IDR : (DBGU Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* - -------- DBGU_IMR : (DBGU Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* - -------- DBGU_CSR : (DBGU Offset: 0x14) Debug Unit Channel Status Register -------- */
/* - -------- DBGU_FNTR : (DBGU Offset: 0x48) Debug Unit FORCE_NTRST Register -------- */
AT91C_US_FORCE_NTRST EQU( 0x1 << 0 );
-( DBGU ) Force NTRST درون JTAG

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
-( CKGR ) Main Oscillator شروع_2 - به_بالا زمان
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
AT91_C_CKGR_بیرون EQU( 0x3 << 14 );
-( CKGR ) PLL Output Frequency Range
AT91_C_CKGR_بیرون_0 EQU( 0x0 << 14 );
-( CKGR ) Please refer مقصد the PLL datasheet
AT91_C_CKGR_بیرون_1 EQU( 0x1 << 14 );
-( CKGR ) Please refer مقصد the PLL datasheet
AT91_C_CKGR_بیرون_2 EQU( 0x2 << 14 );
-( CKGR ) Please refer مقصد the PLL datasheet
AT91_C_CKGR_بیرون_3 EQU( 0x3 << 14 );
-( CKGR ) Please refer مقصد the PLL datasheet
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
-( PMC ) USB Device پورت_2 Clock
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
-( PMC ) MOSC وضعیت / Enable / Disable / ماسک_2
AT91_C_PMC_قفل EQU( 0x1 << 2 );
-( PMC ) PLL وضعیت / Enable / Disable / ماسک_2
AT91C_PMC_MCKRDY EQU( 0x1 << 3 );
-( PMC ) MCK_RDY وضعیت / Enable / Disable / ماسک_2
AT91C_PMC_PCK0RDY EQU( 0x1 << 8 );
-( PMC ) PCK0_RDY وضعیت / Enable / Disable / ماسک_2
AT91C_PMC_PCK1RDY EQU( 0x1 << 9 );
-( PMC ) PCK1_RDY وضعیت / Enable / Disable / ماسک_2
AT91C_PMC_PCK2RDY EQU( 0x1 << 10 );
-( PMC ) PCK2_RDY وضعیت / Enable / Disable / ماسک_2
AT91C_PMC_PCK3RDY EQU( 0x1 << 11 );
-( PMC ) PCK3_RDY وضعیت / Enable / Disable / ماسک_2
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
AT91_C_RSTC_کلید EQU( 0xFF << 24 );
-( RSTC ) Password
/* - -------- RSTC_RSR : (RSTC Offset: 0x4) Reset Status Register -------- */
AT91C_RSTC_URSTS EQU( 0x1 << 0 );
-( RSTC ) User Reset وضعیت
AT91C_RSTC_BODSTS EQU( 0x1 << 1 );
-( RSTC ) Brownout Detection وضعیت
AT91C_RSTC_RSTTYP EQU( 0x7 << 8 );
-( RSTC ) Reset Type
AT91C_RSTC_RSTTYP_POWERUP EQU( 0x0 << 8 );
-( RSTC ) Power - به_بالا Reset.VDDCORE rising.
   AT91C_RSTC_RSTTYP_WAKEUP EQU( 0x1 << 8 );
-( RSTC ) Wake_به_بالا Reset.VDDCORE rising.
   AT91C_RSTC_RSTTYP_WATCHDOG EQU( 0x2 << 8 );
-( RSTC ) Watchdog Reset.Watchdog سرریز occurred.
   AT91C_RSTC_RSTTYP_SOFTWARE EQU( 0x3 << 8 );
-( RSTC ) Software Reset.Processor reset required by the software.
   AT91C_RSTC_RSTTYP_USER EQU( 0x4 << 8 );
-( RSTC ) User Reset.NRST pin detected کم_2.
   AT91C_RSTC_RSTTYP_BROWNOUT EQU( 0x5 << 8 );
-( RSTC ) Brownout Reset occurred.
   AT91C_RSTC_NRSTL EQU( 0x1 << 16 );
-( RSTC ) NRST pin level
AT91C_RSTC_SRCMP EQU( 0x1 << 17 );
-( RSTC ) Software Reset Command درون پیشرفت.
/* - -------- RSTC_RMR : (RSTC Offset: 0x8) Reset Mode Register -------- */
   AT91C_RSTC_URSTEN EQU( 0x1 << 0 );
-( RSTC ) User Reset Enable
AT91C_RSTC_URSTIEN EQU( 0x1 << 4 );
-( RSTC ) User Reset وقفه_2 Enable
AT91C_RSTC_ERSTL EQU( 0xF << 8 );
-( RSTC ) User Reset Enable
AT91C_RSTC_BODIEN EQU( 0x1 << 16 );
-( RSTC ) Brownout Detection وقفه_2 Enable

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Real Time Timer Controller Interface */
/* - ***************************************************************************** */
/* - -------- RTTC_RTMR : (RTTC Offset: 0x0) Real-time Mode Register -------- */
AT91C_RTTC_RTPRES EQU( 0xFFFF << 0 );
-( RTTC ) Real - time Timer Prescaler مقدار_2
AT91C_RTTC_ALMIEN EQU( 0x1 << 16 );
-( RTTC ) Alarm وقفه_2 Enable
AT91C_RTTC_RTTINCIEN EQU( 0x1 << 17 );
-( RTTC ) Real زمان Timer Increment وقفه_2 Enable
AT91C_RTTC_RTTRST EQU( 0x1 << 18 );
-( RTTC ) Real زمان Timer Restart
/* - -------- RTTC_RTAR : (RTTC Offset: 0x4) Real-time Alarm Register -------- */
AT91C_RTTC_ALMV EQU( 0x0 << 0 );
-( RTTC ) Alarm مقدار_2
/* - -------- RTTC_RTVR : (RTTC Offset: 0x8) Current Real-time Value Register -------- */
AT91C_RTTC_CRTV EQU( 0x0 << 0 );
-( RTTC ) Current Real - time مقدار_2
/* - -------- RTTC_RTSR : (RTTC Offset: 0xc) Real-time Status Register -------- */
AT91C_RTTC_ALMS EQU( 0x1 << 0 );
-( RTTC ) Real - time Alarm وضعیت
AT91C_RTTC_RTTINC EQU( 0x1 << 1 );
-( RTTC ) Real - time Timer Increment

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Periodic Interval Timer Controller Interface */
/* - ***************************************************************************** */
/* - -------- PITC_PIMR : (PITC Offset: 0x0) Periodic Interval Mode Register -------- */
AT91C_PITC_PIV EQU( 0xFFFFF << 0 );
-( PITC ) Periodic Interval مقدار_2
AT91C_PITC_PITEN EQU( 0x1 << 24 );
-( PITC ) Periodic Interval Timer Enabled
AT91C_PITC_PITIEN EQU( 0x1 << 25 );
-( PITC ) Periodic Interval Timer وقفه_2 Enable
/* - -------- PITC_PISR : (PITC Offset: 0x4) Periodic Interval Status Register -------- */
AT91C_PITC_PITS EQU( 0x1 << 0 );
-( PITC ) Periodic Interval Timer وضعیت
/* - -------- PITC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register -------- */
AT91C_PITC_CPIV EQU( 0xFFFFF << 0 );
-( PITC ) Current Periodic Interval مقدار_2
AT91C_PITC_PICNT EQU( 0xFFF << 20 );
-( PITC ) Periodic Interval Counter
/* - -------- PITC_PIIR : (PITC Offset: 0xc) Periodic Interval Image Register -------- */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Watchdog Timer Controller Interface */
/* - ***************************************************************************** */
/* - -------- WDTC_WDCR : (WDTC Offset: 0x0) Periodic Interval Image Register -------- */
AT91C_WDTC_WDRSTT EQU( 0x1 << 0 );
-( WDTC ) Watchdog Restart
AT91_C_WDTC_کلید EQU( 0xFF << 24 );
-( WDTC ) Watchdog کلید Password
/* - -------- WDTC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register -------- */
AT91C_WDTC_WDV EQU( 0xFFF << 0 );
-( WDTC ) Watchdog Timer Restart
AT91C_WDTC_WDFIEN EQU( 0x1 << 12 );
-( WDTC ) Watchdog Fault وقفه_2 Enable
AT91C_WDTC_WDRSTEN EQU( 0x1 << 13 );
-( WDTC ) Watchdog Reset Enable
AT91C_WDTC_WDRPROC EQU( 0x1 << 14 );
-( WDTC ) Watchdog Timer Restart
AT91C_WDTC_WDDIS EQU( 0x1 << 15 );
-( WDTC ) Watchdog Disable
AT91C_WDTC_WDD EQU( 0xFFF << 16 );
-( WDTC ) Watchdog Delta مقدار_2
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
-( VREG ) Voltage Regulator Power Standby نما

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Memory Controller Interface */
/* - ***************************************************************************** */
/* - -------- MC_RCR : (MC Offset: 0x0) MC Remap Control Register -------- */
AT91C_MC_RCB EQU( 0x1 << 0 );
-( MC ) Remap Command بیت
/* - -------- MC_ASR : (MC Offset: 0x4) MC Abort Status Register -------- */
AT91C_MC_UNDADD EQU( 0x1 << 0 );
-( MC ) Undefined آدرس Abort وضعیت
AT91C_MC_MISADD EQU( 0x1 << 1 );
-( MC ) Misaligned آدرس Abort وضعیت
AT91C_MC_ABTSZ EQU( 0x3 << 8 );
-( MC ) Abort اندازه_2 وضعیت
AT91C_MC_ABTSZ_BYTE EQU( 0x0 << 8 );
-( MC ) Byte
AT91C_MC_ABTSZ_HWORD EQU( 0x1 << 8 );
-( MC ) Half - کلمه
AT91_C_MC_ABTSZ_کلمه EQU( 0x2 << 8 );
-( MC ) کلمه_2
AT91C_MC_ABTTYP EQU( 0x3 << 10 );
-( MC ) Abort Type وضعیت
AT91C_MC_ABTTYP_DATAR EQU( 0x0 << 10 );
-( MC ) داده Read
AT91C_MC_ABTTYP_DATAW EQU( 0x1 << 10 );
-( MC ) داده Write
AT91C_MC_ABTTYP_FETCH EQU( 0x2 << 10 );
-( MC ) کد_2 Fetch
AT91C_MC_MST0 EQU( 0x1 << 16 );
-( MC ) Master 0 Abort منبع_2
AT91C_MC_MST1 EQU( 0x1 << 17 );
-( MC ) Master 1 Abort منبع_2
AT91C_MC_SVMST0 EQU( 0x1 << 24 );
-( MC ) Saved Master 0 Abort منبع_2
AT91C_MC_SVMST1 EQU( 0x1 << 25 );
-( MC ) Saved Master 1 Abort منبع_2
/* - -------- MC_FMR : (MC Offset: 0x60) MC Flash Mode Register -------- */
AT91C_MC_FRDY EQU( 0x1 << 0 );
-( MC ) Flash Ready
AT91C_MC_LOCKE EQU( 0x1 << 2 );
-( MC ) قفل_2 Error
AT91C_MC_PROGE EQU( 0x1 << 3 );
-( MC ) Programming Error
AT91C_MC_NEBP EQU( 0x1 << 7 );
-( MC ) No Erase Before Programming
AT91C_MC_FWS EQU( 0x3 << 8 );
-( MC ) Flash Wait State
AT91C_MC_FWS_0FWS EQU( 0x0 << 8 );
-( MC ) 1 چرخه

لكل Read, 2

لكل Write operations
AT91C_MC_FWS_1FWS EQU( 0x1 << 8 );
-( MC ) 2 چرخهها

لكل Read, 3

لكل Write operations
AT91C_MC_FWS_2FWS EQU( 0x2 << 8 );
-( MC ) 3 چرخهها

لكل Read, 4

لكل Write operations
AT91C_MC_FWS_3FWS EQU( 0x3 << 8 );
-( MC ) 4 چرخهها

لكل Read, 4

لكل Write operations
AT91C_MC_FMCN EQU( 0xFF << 16 );
-( MC ) Flash Microsecond چرخه_2 عدد_2
/* - -------- MC_FCR : (MC Offset: 0x64) MC Flash Command Register -------- */
AT91C_MC_FCMD EQU( 0xF << 0 );
-( MC ) Flash Command
AT91_C_MC_FCMD_شروع_PROG EQU( 0x1 );
-( MC ) Starts the programming از th epage specified by PAGEN.
   AT91_C_MC_FCMD_قفل EQU( 0x2 );
-( MC ) Starts a قفل_3 sequence از the sector defined by the بیتها_2 4 مقصد 7 از the فیلد PAGEN.
   AT91_C_MC_FCMD_PROG_AND_قفل EQU( 0x3 );
-( MC ) The قفل_3 sequence automatically happens after the programming sequence is completed.
   AT91C_MC_FCMD_UNLOCK EQU( 0x4 );
-( MC ) Starts an unlock sequence از the sector defined by the بیتها_2 4 مقصد 7 از the فیلد PAGEN.
   AT91C_MC_FCMD_ERASE_ALL EQU( 0x8 );
-( MC ) Starts the erase از the entire flash.If at کمترین a صفحه is locked, the command is cancelled.
   AT91_C_MC_FCMD_مجموعه_GP_NVM EQU( 0xB );
-( MC ) مجموعه_2 General Purpose NVM بیتها_2.
   AT91C_MC_FCMD_CLR_GP_NVM EQU( 0xD );
-( MC ) Clear General Purpose NVM بیتها_2.
   AT91_C_MC_FCMD_مجموعه_SECURITY EQU( 0xF );
-( MC ) مجموعه_2 Security بیت.
   AT91C_MC_PAGEN EQU( 0x3FF << 8 );
-( MC ) صفحه_2 عدد_2
AT91_C_MC_کلید EQU( 0xFF << 24 );
-( MC ) Writing Protect کلید_2
/* - -------- MC_FSR : (MC Offset: 0x68) MC Flash Command Register -------- */
AT91C_MC_SECURITY EQU( 0x1 << 4 );
-( MC ) Security بیت وضعیت
AT91C_MC_GPNVM0 EQU( 0x1 << 8 );
-( MC ) Sector 0 قفل_2 وضعیت
AT91C_MC_GPNVM1 EQU( 0x1 << 9 );
-( MC ) Sector 1 قفل_2 وضعیت
AT91C_MC_GPNVM2 EQU( 0x1 << 10 );
-( MC ) Sector 2 قفل_2 وضعیت
AT91C_MC_GPNVM3 EQU( 0x1 << 11 );
-( MC ) Sector 3 قفل_2 وضعیت
AT91C_MC_GPNVM4 EQU( 0x1 << 12 );
-( MC ) Sector 4 قفل_2 وضعیت
AT91C_MC_GPNVM5 EQU( 0x1 << 13 );
-( MC ) Sector 5 قفل_2 وضعیت
AT91C_MC_GPNVM6 EQU( 0x1 << 14 );
-( MC ) Sector 6 قفل_2 وضعیت
AT91C_MC_GPNVM7 EQU( 0x1 << 15 );
-( MC ) Sector 7 قفل_2 وضعیت
AT91C_MC_LOCKS0 EQU( 0x1 << 16 );
-( MC ) Sector 0 قفل_2 وضعیت
AT91C_MC_LOCKS1 EQU( 0x1 << 17 );
-( MC ) Sector 1 قفل_2 وضعیت
AT91C_MC_LOCKS2 EQU( 0x1 << 18 );
-( MC ) Sector 2 قفل_2 وضعیت
AT91C_MC_LOCKS3 EQU( 0x1 << 19 );
-( MC ) Sector 3 قفل_2 وضعیت
AT91C_MC_LOCKS4 EQU( 0x1 << 20 );
-( MC ) Sector 4 قفل_2 وضعیت
AT91C_MC_LOCKS5 EQU( 0x1 << 21 );
-( MC ) Sector 5 قفل_2 وضعیت
AT91C_MC_LOCKS6 EQU( 0x1 << 22 );
-( MC ) Sector 6 قفل_2 وضعیت
AT91C_MC_LOCKS7 EQU( 0x1 << 23 );
-( MC ) Sector 7 قفل_2 وضعیت
AT91C_MC_LOCKS8 EQU( 0x1 << 24 );
-( MC ) Sector 8 قفل_2 وضعیت
AT91C_MC_LOCKS9 EQU( 0x1 << 25 );
-( MC ) Sector 9 قفل_2 وضعیت
AT91C_MC_LOCKS10 EQU( 0x1 << 26 );
-( MC ) Sector 10 قفل_2 وضعیت
AT91C_MC_LOCKS11 EQU( 0x1 << 27 );
-( MC ) Sector 11 قفل_2 وضعیت
AT91C_MC_LOCKS12 EQU( 0x1 << 28 );
-( MC ) Sector 12 قفل_2 وضعیت
AT91C_MC_LOCKS13 EQU( 0x1 << 29 );
-( MC ) Sector 13 قفل_2 وضعیت
AT91C_MC_LOCKS14 EQU( 0x1 << 30 );
-( MC ) Sector 14 قفل_2 وضعیت
AT91C_MC_LOCKS15 EQU( 0x1 << 31 );
-( MC ) Sector 15 قفل_2 وضعیت

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
-( SPI ) SPI آخرین Transfer
/* - -------- SPI_MR : (SPI Offset: 0x4) SPI Mode Register -------- */
AT91C_SPI_MSTR EQU( 0x1 << 0 );
-( SPI ) Master / Slave نما
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
-( SPI ) نما Fault Detection
AT91C_SPI_LLB EQU( 0x1 << 7 );
-( SPI ) Clock Selection
AT91C_SPI_PCS EQU( 0xF << 16 );
-( SPI ) Peripheral Chip Select
AT91C_SPI_DLYBCS EQU( 0xFF << 24 );
-( SPI ) Delay Between Chip Selects
/* - -------- SPI_RDR : (SPI Offset: 0x8) Receive Data Register -------- */
AT91C_SPI_RD EQU( 0xFFFF << 0 );
-( SPI ) Receive داده
AT91C_SPI_RPCS EQU( 0xF << 16 );
-( SPI ) Peripheral Chip Select وضعیت
/* - -------- SPI_TDR : (SPI Offset: 0xc) Transmit Data Register -------- */
AT91C_SPI_TD EQU( 0xFFFF << 0 );
-( SPI ) Transmit داده
AT91C_SPI_TPCS EQU( 0xF << 16 );
-( SPI ) Peripheral Chip Select وضعیت
/* - -------- SPI_SR : (SPI Offset: 0x10) Status Register -------- */
AT91C_SPI_RDRF EQU( 0x1 << 0 );
-( SPI ) Receive داده ثبات پر
AT91C_SPI_TDRE EQU( 0x1 << 1 );
-( SPI ) Transmit داده ثبات خالی
AT91C_SPI_MODF EQU( 0x1 << 2 );
-( SPI ) نما Fault Error
AT91C_SPI_OVRES EQU( 0x1 << 3 );
-( SPI ) Overrun Error وضعیت
AT91C_SPI_ENDRX EQU( 0x1 << 4 );
-( SPI ) انتها_2 از Receiver Transfer
AT91C_SPI_ENDTX EQU( 0x1 << 5 );
-( SPI ) انتها_2 از Receiver Transfer
AT91C_SPI_RXBUFF EQU( 0x1 << 6 );
-( SPI ) RXBUFF وقفه_2
AT91C_SPI_TXBUFE EQU( 0x1 << 7 );
-( SPI ) TXBUFE وقفه_2
AT91C_SPI_NSSR EQU( 0x1 << 8 );
-( SPI ) NSSR وقفه_2
AT91C_SPI_TXEMPTY EQU( 0x1 << 9 );
-( SPI ) TXEMPTY وقفه_2
AT91C_SPI_SPIENS EQU( 0x1 << 16 );
-( SPI ) Enable وضعیت
/* - -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- */
/* - -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- */
/* - -------- SPI_IMR : (SPI Offset: 0x1c) Interrupt Mask Register -------- */
/* - -------- SPI_CSR : (SPI Offset: 0x30) Chip Select Register -------- */
AT91C_SPI_CPOL EQU( 0x1 << 0 );
-( SPI ) Clock Polarity
AT91C_SPI_NCPHA EQU( 0x1 << 1 );
-( SPI ) Clock Phase
AT91C_SPI_CSAAT EQU( 0x1 << 3 );
-( SPI ) Chip Select فعال After Transfer
AT91_C_SPI_بیتها EQU( 0xF << 4 );
-( SPI ) بیتها در_هر Transfer
AT91_C_SPI_بیتها_8 EQU( 0x0 << 4 );
-( SPI ) 8 بیتها در_هر transfer
AT91_C_SPI_بیتها_9 EQU( 0x1 << 4 );
-( SPI ) 9 بیتها در_هر transfer
AT91_C_SPI_بیتها_10 EQU( 0x2 << 4 );
-( SPI ) 10 بیتها در_هر transfer
AT91_C_SPI_بیتها_11 EQU( 0x3 << 4 );
-( SPI ) 11 بیتها در_هر transfer
AT91_C_SPI_بیتها_12 EQU( 0x4 << 4 );
-( SPI ) 12 بیتها در_هر transfer
AT91_C_SPI_بیتها_13 EQU( 0x5 << 4 );
-( SPI ) 13 بیتها در_هر transfer
AT91_C_SPI_بیتها_14 EQU( 0x6 << 4 );
-( SPI ) 14 بیتها در_هر transfer
AT91_C_SPI_بیتها_15 EQU( 0x7 << 4 );
-( SPI ) 15 بیتها در_هر transfer
AT91_C_SPI_بیتها_16 EQU( 0x8 << 4 );
-( SPI ) 16 بیتها در_هر transfer
AT91C_SPI_SCBR EQU( 0xFF << 8 );
-( SPI ) Serial Clock Baud نرخ
AT91C_SPI_DLYBS EQU( 0xFF << 16 );
-( SPI ) Delay Before SPCK
AT91C_SPI_DLYBCT EQU( 0xFF << 24 );
-( SPI ) Delay Between Consecutive Transfers

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Usart */
/* - ***************************************************************************** */
/* - -------- US_CR : (USART Offset: 0x0) Debug Unit Control Register -------- */
AT91C_US_STTBRK EQU( 0x1 << 9 );
-( USART ) شروع_2 Break
AT91C_US_STPBRK EQU( 0x1 << 10 );
-( USART ) Stop Break
AT91C_US_STTTO EQU( 0x1 << 11 );
-( USART ) شروع_2 زمان - بیرون
AT91C_US_SENDA EQU( 0x1 << 12 );
-( USART ) Send آدرس
AT91C_US_RSTIT EQU( 0x1 << 13 );
-( USART ) Reset Iterations
AT91C_US_RSTNACK EQU( 0x1 << 14 );
-( USART ) Reset Non Acknowledge
AT91C_US_RETTO EQU( 0x1 << 15 );
-( USART ) Rearm زمان - بیرون
AT91C_US_DTREN EQU( 0x1 << 16 );
-( USART ) داده Terminal ready Enable
AT91C_US_DTRDIS EQU( 0x1 << 17 );
-( USART ) داده Terminal ready Disable
AT91C_US_RTSEN EQU( 0x1 << 18 );
-( USART ) Request مقصد Send enable
AT91C_US_RTSDIS EQU( 0x1 << 19 );
-( USART ) Request مقصد Send Disable
/* - -------- US_MR : (USART Offset: 0x4) Debug Unit Mode Register -------- */
AT91C_US_USMODE EQU( 0xF << 0 );
-( USART ) Usart نما_2
AT91_C_US_USMODE_نرمال EQU( 0x0 );
-( USART ) نرمال
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
-( USART ) Clock Selection ( Baud نرخ generator درون_داد Clock
                             AT91C_US_CLKS_CLOCK EQU( 0x0 << 4 );
                             -( USART ) Clock
                             AT91C_US_CLKS_FDIV1 EQU( 0x1 << 4 );
                             -( USART ) fdiv1
                             AT91C_US_CLKS_SLOW EQU( 0x2 << 4 );
                             -( USART ) slow_clock( ARM )
                             AT91C_US_CLKS_EXT EQU( 0x3 << 4 );
                             -( USART ) External( SCK )
                             AT91C_US_CHRL EQU( 0x3 << 6 );
                             -( USART ) Clock Selection ( Baud نرخ generator درون_داد Clock
                                                          AT91_C_US_CHRL_5_بیتها EQU( 0x0 << 6 );
                                                          -( USART ) Character درازی : 5 بیتها_2
                                                          AT91_C_US_CHRL_6_بیتها EQU( 0x1 << 6 );
                                                          -( USART ) Character درازی : 6 بیتها_2
                                                          AT91_C_US_CHRL_7_بیتها EQU( 0x2 << 6 );
                                                          -( USART ) Character درازی : 7 بیتها_2
                                                          AT91_C_US_CHRL_8_بیتها EQU( 0x3 << 6 );
                                                          -( USART ) Character درازی : 8 بیتها_2
                                                          AT91C_US_SYNC EQU( 0x1 << 8 );
                                                          -( USART ) Synchronous نما Select
                                                          AT91C_US_NBSTOP EQU( 0x3 << 12 );
                                                          -( USART ) عدد_2 از Stop بیتها_2
                                                          AT91_C_US_NBSTOP_1_بیت EQU( 0x0 << 12 );
                                                          -( USART ) 1 stop بیت_2
                                                          AT91_C_US_NBSTOP_15_بیت EQU( 0x1 << 12 );
                                                          -( USART ) Asynchronous( SYNC = 0 ) 2 stop بیتها_2 Synchronous( SYNC = 1 ) 2 stop بیتها_2
                                                          AT91_C_US_NBSTOP_2_بیت EQU( 0x2 << 12 );
                                                          -( USART ) 2 stop بیتها_2
                                                          AT91C_US_MSBF EQU( 0x1 << 16 );
                                                          -( USART ) بیت ترتیب_2
                                                          AT91C_US_MODE9 EQU( 0x1 << 17 );
                                                          -( USART ) 9 - بیت_2 Character درازی_2
                                                          AT91C_US_CKLO EQU( 0x1 << 18 );
                                                          -( USART ) Clock Output Select
                                                          AT91C_US_OVER EQU( 0x1 << 19 );
                                                          -( USART ) Over Sampling نما
                                                          AT91C_US_INACK EQU( 0x1 << 20 );
                                                          -( USART ) Inhibit Non Acknowledge
                                                          AT91C_US_DSNACK EQU( 0x1 << 21 );
                                                          -( USART ) Disable Successive NACK
                                                          AT91C_US_MAX_ITER EQU( 0x1 << 24 );
                                                          -( USART ) عدد_2 از Repetitions
                                                          AT91C_US_FILTER EQU( 0x1 << 28 );
                                                          -( USART ) Receive سطر_2 Filter
/* - -------- US_IER : (USART Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
                                                          AT91C_US_RXBRK EQU( 0x1 << 2 );
                                                          -( USART ) Break Received / انتها_2 از Break
                                                          AT91C_US_TIMEOUT EQU( 0x1 << 8 );
                                                          -( USART ) Receiver زمان - بیرون
                                                          AT91C_US_ITERATION EQU( 0x1 << 10 );
                                                          -( USART ) Max عدد از Repetitions Reached
                                                          AT91C_US_NACK EQU( 0x1 << 13 );
                                                          -( USART ) Non Acknowledge
                                                          AT91C_US_RIIC EQU( 0x1 << 16 );
                                                          -( USART ) Ring INdicator درون_داد Change Flag
                                                          AT91C_US_DSRIC EQU( 0x1 << 17 );
                                                          -( USART ) داده مجموعه_2 Ready درون_داد Change Flag
                                                          AT91C_US_DCDIC EQU( 0x1 << 18 );
                                                          -( USART ) داده Carrier Flag
                                                          AT91C_US_CTSIC EQU( 0x1 << 19 );
                                                          -( USART ) Clear مقصد_2 Send درون_داد Change Flag
/* - -------- US_IDR : (USART Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* - -------- US_IMR : (USART Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* - -------- US_CSR : (USART Offset: 0x14) Debug Unit Channel Status Register -------- */
                                                          AT91C_US_RI EQU( 0x1 << 20 );
                                                          -( USART ) Image از RI درون_داد
                                                          AT91C_US_DSR EQU( 0x1 << 21 );
                                                          -( USART ) Image از DSR درون_داد
                                                          AT91C_US_DCD EQU( 0x1 << 22 );
                                                          -( USART ) Image از DCD درون_داد
                                                          AT91C_US_CTS EQU( 0x1 << 23 );
                                                          -( USART ) Image از CTS درون_داد

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
                                                          -( SSC ) Receive / Transmit Clock Output نما Selection
                                                          AT91C_SSC_CKO_NONE EQU( 0x0 << 2 );
                                                          -( SSC ) Receive / Transmit Clock Output نما:None RK pin: درون_داد - only
                                                          AT91C_SSC_CKO_CONTINUOUS EQU( 0x1 << 2 );
                                                          -( SSC ) Continuous Receive / Transmit Clock RK pin:Output
                                                          AT91_C_SSC_CKO_داده_TX EQU( 0x2 << 2 );
                                                          -( SSC ) Receive / Transmit Clock only during داده_2 transfers RK pin:Output
                                                          AT91C_SSC_CKI EQU( 0x1 << 5 );
                                                          -( SSC ) Receive / Transmit Clock Inversion
                                                          AT91_C_SSC_شروع EQU( 0xF << 8 );
                                                          -( SSC ) Receive / Transmit شروع_2 Selection
                                                          AT91_C_SSC_شروع_CONTINUOUS EQU( 0x0 << 8 );
                                                          -( SSC ) Continuous, as soon as the receiver is enabled, and immediately after the انتها از transfer از the قبلی داده_2.
                                                             AT91_C_SSC_شروع_TX EQU( 0x1 << 8 );
                                                          -( SSC ) Transmit / Receive شروع
                                                          AT91_C_SSC_شروع_کم_RF EQU( 0x2 << 8 );
                                                          -( SSC ) Detection از a کم_2 level on RF درون_داد_2
                                                          AT91_C_SSC_شروع_بالا_RF EQU( 0x3 << 8 );
                                                          -( SSC ) Detection از a بالا_2 level on RF درون_داد_2
                                                          AT91_C_SSC_شروع_FALL_RF EQU( 0x4 << 8 );
                                                          -( SSC ) Detection از a falling یال_2 on RF درون_داد_2
                                                          AT91_C_SSC_شروع_RISE_RF EQU( 0x5 << 8 );
                                                          -( SSC ) Detection از a rising یال_2 on RF درون_داد_2
                                                          AT91_C_SSC_شروع_LEVEL_RF EQU( 0x6 << 8 );
                                                          -( SSC ) Detection از any level change on RF درون_داد_2
                                                          AT91_C_SSC_شروع_یال_RF EQU( 0x7 << 8 );
                                                          -( SSC ) Detection از any یال_2 on RF درون_داد_2
                                                          AT91_C_SSC_شروع_0 EQU( 0x8 << 8 );
                                                          -( SSC ) Compare 0
                                                          AT91C_SSC_STTDLY EQU( 0xFF << 16 );
                                                          -( SSC ) Receive / Transmit شروع_2 Delay
                                                          AT91C_SSC_PERIOD EQU( 0xFF << 24 );
                                                          -( SSC ) Receive / Transmit Period Divider Selection
/* - -------- SSC_RFMR : (SSC Offset: 0x14) SSC Receive Frame Mode Register -------- */
                                                          AT91C_SSC_DATLEN EQU( 0x1F << 0 );
                                                          -( SSC ) داده درازی
                                                          AT91C_SSC_LOOP EQU( 0x1 << 5 );
                                                          -( SSC ) Loop نما
                                                          AT91C_SSC_MSBF EQU( 0x1 << 7 );
                                                          -( SSC ) Most Significant بیت اولی
                                                          AT91C_SSC_DATNB EQU( 0xF << 8 );
                                                          -( SSC ) داده عدد_2 در_هر_2 قاب
                                                          AT91C_SSC_FSLEN EQU( 0xF << 16 );
                                                          -( SSC ) Receive / Transmit قاب Sync درازی_2
                                                          AT91C_SSC_FSOS EQU( 0x7 << 20 );
                                                          -( SSC ) Receive / Transmit قاب Sync Output Selection
                                                          AT91C_SSC_FSOS_NONE EQU( 0x0 << 20 );
                                                          -( SSC ) Selected Receive / Transmit قاب Sync Signal:None RK pin درون_داد - only
                                                          AT91C_SSC_FSOS_NEGATIVE EQU( 0x1 << 20 );
                                                          -( SSC ) Selected Receive / Transmit قاب Sync Signal:Negative Pulse
                                                          AT91_C_SSC_FSOS_مثبت EQU( 0x2 << 20 );
                                                          -( SSC ) Selected Receive / Transmit قاب Sync Signal:مثبت Pulse
                                                          AT91_C_SSC_FSOS_کم EQU( 0x3 << 20 );
                                                          -( SSC ) Selected Receive / Transmit قاب Sync Signal:Driver کم during داده_2 transfer
                                                          AT91_C_SSC_FSOS_بالا EQU( 0x4 << 20 );
                                                          -( SSC ) Selected Receive / Transmit قاب Sync Signal:Driver بالا during داده_2 transfer
                                                          AT91C_SSC_FSOS_TOGGLE EQU( 0x5 << 20 );
                                                          -( SSC ) Selected Receive / Transmit قاب Sync Signal:Toggling at each شروع از داده_2 transfer
                                                          AT91C_SSC_FSEDGE EQU( 0x1 << 24 );
                                                          -( SSC ) قاب Sync یال Detection
/* - -------- SSC_TCMR : (SSC Offset: 0x18) SSC Transmit Clock Mode Register -------- */
/* - -------- SSC_TFMR : (SSC Offset: 0x1c) SSC Transmit Frame Mode Register -------- */
                                                          AT91C_SSC_DATDEF EQU( 0x1 << 5 );
                                                          -( SSC ) داده Default مقدار_2
                                                          AT91C_SSC_FSDEN EQU( 0x1 << 23 );
                                                          -( SSC ) قاب Sync داده Enable
/* - -------- SSC_SR : (SSC Offset: 0x40) SSC Status Register -------- */
                                                          AT91C_SSC_TXRDY EQU( 0x1 << 0 );
                                                          -( SSC ) Transmit Ready
                                                          AT91C_SSC_TXEMPTY EQU( 0x1 << 1 );
                                                          -( SSC ) Transmit خالی
                                                          AT91C_SSC_ENDTX EQU( 0x1 << 2 );
                                                          -( SSC ) انتها_2 از_2 ارسال
                                                          AT91C_SSC_TXBUFE EQU( 0x1 << 3 );
                                                          -( SSC ) Transmit میانگیر خالی
                                                          AT91C_SSC_RXRDY EQU( 0x1 << 4 );
                                                          -( SSC ) Receive Ready
                                                          AT91C_SSC_OVRUN EQU( 0x1 << 5 );
                                                          -( SSC ) Receive Overrun
                                                          AT91C_SSC_ENDRX EQU( 0x1 << 6 );
                                                          -( SSC ) انتها_2 از Reception
                                                          AT91C_SSC_RXBUFF EQU( 0x1 << 7 );
                                                          -( SSC ) Receive میانگیر پر
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
                                                          AT91_C_TWI_شروع EQU( 0x1 << 0 );
                                                          -( TWI ) Send a شروع_3 Condition
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
                                                          -( TWI ) داخلی Device آدرس اندازه_2
                                                          AT91C_TWI_IADRSZ_NO EQU( 0x0 << 8 );
                                                          -( TWI ) No داخلی_2 device آدرس_2
                                                          AT91C_TWI_IADRSZ_1_BYTE EQU( 0x1 << 8 );
                                                          -( TWI ) One - byte داخلی_2 device آدرس_2
                                                          AT91C_TWI_IADRSZ_2_BYTE EQU( 0x2 << 8 );
                                                          -( TWI ) Two - byte داخلی_2 device آدرس_2
                                                          AT91C_TWI_IADRSZ_3_BYTE EQU( 0x3 << 8 );
                                                          -( TWI ) Three - byte داخلی_2 device آدرس_2
                                                          AT91C_TWI_MREAD EQU( 0x1 << 12 );
                                                          -( TWI ) Master Read Direction
                                                          AT91C_TWI_DADR EQU( 0x7F << 16 );
                                                          -( TWI ) Device آدرس
/* - -------- TWI_CWGR : (TWI Offset: 0x10) TWI Clock Waveform Generator Register -------- */
                                                          AT91C_TWI_CLDIV EQU( 0xFF << 0 );
                                                          -( TWI ) Clock کم Divider
                                                          AT91C_TWI_CHDIV EQU( 0xFF << 8 );
                                                          -( TWI ) Clock بالا Divider
                                                          AT91C_TWI_CKDIV EQU( 0x7 << 16 );
                                                          -( TWI ) Clock Divider
/* - -------- TWI_SR : (TWI Offset: 0x20) TWI Status Register -------- */
                                                          AT91C_TWI_TXCOMP EQU( 0x1 << 0 );
                                                          -( TWI ) ارسال Completed
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
                                                          -( PWMC_CH ) Channel Duty چرخه_2
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
                                                          -( PWMC ) CLKA divide ضریب.
                                                             AT91C_PWMC_PREA EQU( 0xF << 8 );
                                                          -( PWMC ) Divider درون_داد Clock Prescaler A
                                                          AT91C_PWMC_PREA_MCK EQU( 0x0 << 8 );
                                                          -( PWMC )
                                                          AT91C_PWMC_DIVB EQU( 0xFF << 16 );
                                                          -( PWMC ) CLKB divide ضریب.
                                                             AT91C_PWMC_PREB EQU( 0xF << 24 );
                                                          -( PWMC ) Divider درون_داد Clock Prescaler B
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
                                                          AT91_C_UDP_FRM_رقم EQU( 0x7FF << 0 );
                                                          -( UDP ) قاب عدد_2 as Defined درون the Packet فیلد_2 Formats
                                                          AT91C_UDP_FRM_ERR EQU( 0x1 << 16 );
                                                          -( UDP ) قاب Error
                                                          AT91C_UDP_FRM_OK EQU( 0x1 << 17 );
                                                          -( UDP ) قاب OK
/* - -------- UDP_GLB_STATE : (UDP Offset: 0x4) USB Global State Register -------- */
                                                          AT91C_UDP_FADDEN EQU( 0x1 << 0 );
                                                          -( UDP ) Function آدرس Enable
                                                          AT91C_UDP_CONFG EQU( 0x1 << 1 );
                                                          -( UDP ) Configured
                                                          AT91C_UDP_ESR EQU( 0x1 << 2 );
                                                          -( UDP ) Enable Send Resume
                                                          AT91C_UDP_RSMINPR EQU( 0x1 << 3 );
                                                          -( UDP ) A Resume Has Been فرستاده مقصد the Host
                                                          AT91C_UDP_RMWUPE EQU( 0x1 << 4 );
                                                          -( UDP ) Remote Wake به_بالا_2 Enable
/* - -------- UDP_FADDR : (UDP Offset: 0x8) USB Function Address Register -------- */
                                                          AT91C_UDP_FADD EQU( 0xFF << 0 );
                                                          -( UDP ) Function آدرس مقدار_2
                                                          AT91C_UDP_FEN EQU( 0x1 << 8 );
                                                          -( UDP ) Function Enable
/* - -------- UDP_IER : (UDP Offset: 0x10) USB Interrupt Enable Register -------- */
                                                          AT91C_UDP_EPINT0 EQU( 0x1 << 0 );
                                                          -( UDP ) Endpoint 0 وقفه_2
                                                          AT91C_UDP_EPINT1 EQU( 0x1 << 1 );
                                                          -( UDP ) Endpoint 0 وقفه_2
                                                          AT91C_UDP_EPINT2 EQU( 0x1 << 2 );
                                                          -( UDP ) Endpoint 2 وقفه_2
                                                          AT91C_UDP_EPINT3 EQU( 0x1 << 3 );
                                                          -( UDP ) Endpoint 3 وقفه_2
                                                          AT91C_UDP_EPINT4 EQU( 0x1 << 4 );
                                                          -( UDP ) Endpoint 4 وقفه_2
                                                          AT91C_UDP_EPINT5 EQU( 0x1 << 5 );
                                                          -( UDP ) Endpoint 5 وقفه_2
                                                          AT91C_UDP_RXSUSP EQU( 0x1 << 8 );
                                                          -( UDP ) USB Suspend وقفه_2
                                                          AT91C_UDP_RXRSM EQU( 0x1 << 9 );
                                                          -( UDP ) USB Resume وقفه_2
                                                          AT91C_UDP_EXTRSM EQU( 0x1 << 10 );
                                                          -( UDP ) USB External Resume وقفه_2
                                                          AT91C_UDP_SOFINT EQU( 0x1 << 11 );
                                                          -( UDP ) USB شروع_2 از_2 قاب_2 وقفه_2
                                                          AT91C_UDP_WAKEUP EQU( 0x1 << 13 );
                                                          -( UDP ) USB Resume وقفه_2
/* - -------- UDP_IDR : (UDP Offset: 0x14) USB Interrupt Disable Register -------- */
/* - -------- UDP_IMR : (UDP Offset: 0x18) USB Interrupt Mask Register -------- */
/* - -------- UDP_ISR : (UDP Offset: 0x1c) USB Interrupt Status Register -------- */
                                                          AT91C_UDP_ENDBUSRES EQU( 0x1 << 12 );
                                                          -( UDP ) USB انتها_2 از_2 Bus Reset وقفه_2
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
                                                          -( UDP ) Generates an درون_2 packet with داده_2 previously written درون the DPR
                                                          AT91_C_UDP_RX_داده_BK0 EQU( 0x1 << 1 );
                                                          -( UDP ) Receive داده Bank 0
                                                          AT91C_UDP_RXSETUP EQU( 0x1 << 2 );
                                                          -( UDP ) Sends STALL مقصد the Host( Control endpoints )
                                                          AT91C_UDP_ISOERROR EQU( 0x1 << 3 );
                                                          -( UDP ) Isochronous error( Isochronous endpoints )
                                                          AT91C_UDP_TXPKTRDY EQU( 0x1 << 4 );
                                                          -( UDP ) Transmit Packet Ready
                                                          AT91C_UDP_FORCESTALL EQU( 0x1 << 5 );
                                                          -( UDP ) Force Stall( استفاده_شده by Control, Bulk and Isochronous endpoints ).
                                                             AT91_C_UDP_RX_داده_BK1 EQU( 0x1 << 6 );
                                                          -( UDP ) Receive داده Bank 1 ( only استفاده_شده by endpoints with ping - pong صفات ).
                                                             AT91C_UDP_DIR EQU( 0x1 << 7 );
                                                          -( UDP ) Transfer Direction
                                                          AT91C_UDP_EPTYPE EQU( 0x7 << 8 );
                                                          -( UDP ) Endpoint type
                                                          AT91C_UDP_EPTYPE_CTRL EQU( 0x0 << 8 );
                                                          -( UDP ) Control
                                                          AT91_C_UDP_EPTYPE_ISO_بیرون EQU( 0x1 << 8 );
                                                          -( UDP ) Isochronous بیرون_2
                                                          AT91_C_UDP_EPTYPE_BULK_بیرون EQU( 0x2 << 8 );
                                                          -( UDP ) Bulk بیرون_2
                                                          AT91_C_UDP_EPTYPE_INT_بیرون EQU( 0x3 << 8 );
                                                          -( UDP ) وقفه_2 بیرون_2
                                                          AT91_C_UDP_EPTYPE_ISO_درون EQU( 0x5 << 8 );
                                                          -( UDP ) Isochronous درون_2
                                                          AT91_C_UDP_EPTYPE_BULK_درون EQU( 0x6 << 8 );
                                                          -( UDP ) Bulk درون_2
                                                          AT91_C_UDP_EPTYPE_INT_درون EQU( 0x7 << 8 );
                                                          -( UDP ) وقفه_2 درون_2
                                                          AT91C_UDP_DTGLE EQU( 0x1 << 11 );
                                                          -( UDP ) داده Toggle
                                                          AT91C_UDP_EPEDS EQU( 0x1 << 15 );
                                                          -( UDP ) Endpoint Enable Disable
                                                          AT91C_UDP_RXBYTECNT EQU( 0x7FF << 16 );
                                                          -( UDP ) عدد_2 از_2 بایتها موجود_2 درون the FIFO
/* - -------- UDP_TXVC : (UDP Offset: 0x74) Transceiver Control Register -------- */
                                                          AT91C_UDP_TXVDIS EQU( 0x1 << 8 );
                                                          -( UDP )
                                                          AT91C_UDP_PUON EQU( 0x1 << 9 );
                                                          -( UDP ) Pull - به_بالا ON

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
                                                          AT91_C_TC_مدت EQU( 0x3 << 4 );
                                                          -( TC ) مدت Signal Selection
                                                          AT91_C_TC_مدت_NONE EQU( 0x0 << 4 );
                                                          -( TC ) The clock is not gated by an external إشارة
                                                          AT91_C_TC_مدت_XC0 EQU( 0x1 << 4 );
                                                          -( TC ) XC0 is ANDed with the selected clock
                                                          AT91_C_TC_مدت_XC1 EQU( 0x2 << 4 );
                                                          -( TC ) XC1 is ANDed with the selected clock
                                                          AT91_C_TC_مدت_XC2 EQU( 0x3 << 4 );
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
                                                          -( TC ) External Trigger یال Selection
                                                          AT91C_TC_ETRGEDG_NONE EQU( 0x0 << 8 );
                                                          -( TC ) یال:None
                                                          AT91C_TC_ETRGEDG_RISING EQU( 0x1 << 8 );
                                                          -( TC ) یال:rising یال_2
                                                          AT91C_TC_ETRGEDG_FALLING EQU( 0x2 << 8 );
                                                          -( TC ) یال:falling یال_2
                                                          AT91C_TC_ETRGEDG_BOTH EQU( 0x3 << 8 );
                                                          -( TC ) یال:each یال_2
                                                          AT91C_TC_EEVTEDG EQU( 0x3 << 8 );
                                                          -( TC ) External Event یال Selection
                                                          AT91C_TC_EEVTEDG_NONE EQU( 0x0 << 8 );
                                                          -( TC ) یال:None
                                                          AT91C_TC_EEVTEDG_RISING EQU( 0x1 << 8 );
                                                          -( TC ) یال:rising یال_2
                                                          AT91C_TC_EEVTEDG_FALLING EQU( 0x2 << 8 );
                                                          -( TC ) یال:falling یال_2
                                                          AT91C_TC_EEVTEDG_BOTH EQU( 0x3 << 8 );
                                                          -( TC ) یال:each یال_2
                                                          AT91C_TC_EEVT EQU( 0x3 << 10 );
                                                          -( TC ) External Event Selection
                                                          AT91C_TC_EEVT_TIOB EQU( 0x0 << 10 );
                                                          -( TC ) Signal selected as external event:TIOB TIOB direction: درون_داد_2
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
                                                          AT91_C_TC_WAVESEL_به_بالا EQU( 0x0 << 13 );
                                                          -( TC ) به_بالا_3 نما_2 without atomatic trigger on RC Compare
                                                          AT91C_TC_WAVESEL_UPDOWN EQU( 0x1 << 13 );
                                                          -( TC ) UPDOWN نما_2 without automatic trigger on RC Compare
                                                          AT91_C_TC_WAVESEL_به_بالا_AUTO EQU( 0x2 << 13 );
                                                          -( TC ) به_بالا_3 نما_2 with automatic trigger on RC Compare
                                                          AT91C_TC_WAVESEL_UPDOWN_AUTO EQU( 0x3 << 13 );
                                                          -( TC ) UPDOWN نما_2 with automatic trigger on RC Compare
                                                          AT91C_TC_CPCTRG EQU( 0x1 << 14 );
                                                          -( TC ) RC Compare Trigger Enable
                                                          AT91C_TC_WAVE EQU( 0x1 << 15 );
                                                          -( TC )
                                                          AT91C_TC_ACPA EQU( 0x3 << 16 );
                                                          -( TC ) RA Compare Effect on TIOA
                                                          AT91C_TC_ACPA_NONE EQU( 0x0 << 16 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_ACPA_مجموعه EQU( 0x1 << 16 );
                                                          -( TC ) Effect:مجموعه
                                                          AT91C_TC_ACPA_CLEAR EQU( 0x2 << 16 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_ACPA_TOGGLE EQU( 0x3 << 16 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_LDRA EQU( 0x3 << 16 );
                                                          -( TC ) RA Loading Selection
                                                          AT91C_TC_LDRA_NONE EQU( 0x0 << 16 );
                                                          -( TC ) یال:None
                                                          AT91C_TC_LDRA_RISING EQU( 0x1 << 16 );
                                                          -( TC ) یال:rising یال_2 از TIOA
                                                          AT91C_TC_LDRA_FALLING EQU( 0x2 << 16 );
                                                          -( TC ) یال:falling یال_2 از TIOA
                                                          AT91C_TC_LDRA_BOTH EQU( 0x3 << 16 );
                                                          -( TC ) یال:each یال_2 از TIOA
                                                          AT91C_TC_ACPC EQU( 0x3 << 18 );
                                                          -( TC ) RC Compare Effect on TIOA
                                                          AT91C_TC_ACPC_NONE EQU( 0x0 << 18 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_ACPC_مجموعه EQU( 0x1 << 18 );
                                                          -( TC ) Effect:مجموعه
                                                          AT91C_TC_ACPC_CLEAR EQU( 0x2 << 18 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_ACPC_TOGGLE EQU( 0x3 << 18 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_LDRB EQU( 0x3 << 18 );
                                                          -( TC ) RB Loading Selection
                                                          AT91C_TC_LDRB_NONE EQU( 0x0 << 18 );
                                                          -( TC ) یال:None
                                                          AT91C_TC_LDRB_RISING EQU( 0x1 << 18 );
                                                          -( TC ) یال:rising یال_2 از TIOA
                                                          AT91C_TC_LDRB_FALLING EQU( 0x2 << 18 );
                                                          -( TC ) یال:falling یال_2 از TIOA
                                                          AT91C_TC_LDRB_BOTH EQU( 0x3 << 18 );
                                                          -( TC ) یال:each یال_2 از TIOA
                                                          AT91C_TC_AEEVT EQU( 0x3 << 20 );
                                                          -( TC ) External Event Effect on TIOA
                                                          AT91C_TC_AEEVT_NONE EQU( 0x0 << 20 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_AEEVT_مجموعه EQU( 0x1 << 20 );
                                                          -( TC ) Effect:مجموعه
                                                          AT91C_TC_AEEVT_CLEAR EQU( 0x2 << 20 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_AEEVT_TOGGLE EQU( 0x3 << 20 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_ASWTRG EQU( 0x3 << 22 );
                                                          -( TC ) Software Trigger Effect on TIOA
                                                          AT91C_TC_ASWTRG_NONE EQU( 0x0 << 22 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_ASWTRG_مجموعه EQU( 0x1 << 22 );
                                                          -( TC ) Effect:مجموعه
                                                          AT91C_TC_ASWTRG_CLEAR EQU( 0x2 << 22 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_ASWTRG_TOGGLE EQU( 0x3 << 22 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_BCPB EQU( 0x3 << 24 );
                                                          -( TC ) RB Compare Effect on TIOB
                                                          AT91C_TC_BCPB_NONE EQU( 0x0 << 24 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_BCPB_مجموعه EQU( 0x1 << 24 );
                                                          -( TC ) Effect:مجموعه
                                                          AT91C_TC_BCPB_CLEAR EQU( 0x2 << 24 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_BCPB_TOGGLE EQU( 0x3 << 24 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_BCPC EQU( 0x3 << 26 );
                                                          -( TC ) RC Compare Effect on TIOB
                                                          AT91C_TC_BCPC_NONE EQU( 0x0 << 26 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_BCPC_مجموعه EQU( 0x1 << 26 );
                                                          -( TC ) Effect:مجموعه
                                                          AT91C_TC_BCPC_CLEAR EQU( 0x2 << 26 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_BCPC_TOGGLE EQU( 0x3 << 26 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_BEEVT EQU( 0x3 << 28 );
                                                          -( TC ) External Event Effect on TIOB
                                                          AT91C_TC_BEEVT_NONE EQU( 0x0 << 28 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_BEEVT_مجموعه EQU( 0x1 << 28 );
                                                          -( TC ) Effect:مجموعه
                                                          AT91C_TC_BEEVT_CLEAR EQU( 0x2 << 28 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_BEEVT_TOGGLE EQU( 0x3 << 28 );
                                                          -( TC ) Effect:toggle
                                                          AT91C_TC_BSWTRG EQU( 0x3 << 30 );
                                                          -( TC ) Software Trigger Effect on TIOB
                                                          AT91C_TC_BSWTRG_NONE EQU( 0x0 << 30 );
                                                          -( TC ) Effect:none
                                                          AT91_C_TC_BSWTRG_مجموعه EQU( 0x1 << 30 );
                                                          -( TC ) Effect:مجموعه
                                                          AT91C_TC_BSWTRG_CLEAR EQU( 0x2 << 30 );
                                                          -( TC ) Effect:clear
                                                          AT91C_TC_BSWTRG_TOGGLE EQU( 0x3 << 30 );
                                                          -( TC ) Effect:toggle
/* - -------- TC_SR : (TC Offset: 0x20) TC Channel Status Register -------- */
                                                          AT91C_TC_COVFS EQU( 0x1 << 0 );
                                                          -( TC ) Counter سرریز_2
                                                          AT91C_TC_LOVRS EQU( 0x1 << 1 );
                                                          -( TC ) بارگیری Overrun
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
                                                          -( TCB ) TCLK0 connected مقصد XC0
                                                          AT91C_TCB_TC0XC0S_NONE EQU( 0x1 );
                                                          -( TCB ) None إشارة connected مقصد XC0
                                                          AT91C_TCB_TC0XC0S_TIOA1 EQU( 0x2 );
                                                          -( TCB ) TIOA1 connected مقصد XC0
                                                          AT91C_TCB_TC0XC0S_TIOA2 EQU( 0x3 );
                                                          -( TCB ) TIOA2 connected مقصد XC0
                                                          AT91C_TCB_TC1XC1S EQU( 0x3 << 2 );
                                                          -( TCB ) External Clock Signal 1 Selection
                                                          AT91C_TCB_TC1XC1S_TCLK1 EQU( 0x0 << 2 );
                                                          -( TCB ) TCLK1 connected مقصد XC1
                                                          AT91C_TCB_TC1XC1S_NONE EQU( 0x1 << 2 );
                                                          -( TCB ) None إشارة connected مقصد XC1
                                                          AT91C_TCB_TC1XC1S_TIOA0 EQU( 0x2 << 2 );
                                                          -( TCB ) TIOA0 connected مقصد XC1
                                                          AT91C_TCB_TC1XC1S_TIOA2 EQU( 0x3 << 2 );
                                                          -( TCB ) TIOA2 connected مقصد XC1
                                                          AT91C_TCB_TC2XC2S EQU( 0x3 << 4 );
                                                          -( TCB ) External Clock Signal 2 Selection
                                                          AT91C_TCB_TC2XC2S_TCLK2 EQU( 0x0 << 4 );
                                                          -( TCB ) TCLK2 connected مقصد XC2
                                                          AT91C_TCB_TC2XC2S_NONE EQU( 0x1 << 4 );
                                                          -( TCB ) None إشارة connected مقصد XC2
                                                          AT91C_TCB_TC2XC2S_TIOA0 EQU( 0x2 << 4 );
                                                          -( TCB ) TIOA0 connected مقصد XC2
                                                          AT91C_TCB_TC2XC2S_TIOA1 EQU( 0x3 << 4 );
                                                          -( TCB ) TIOA2 connected مقصد XC2

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Control Area Network MailBox Interface */
/* - ***************************************************************************** */
/* - -------- CAN_MMR : (CAN_MB Offset: 0x0) CAN Message Mode Register -------- */
                                                          AT91C_CAN_MTIMEMARK EQU( 0xFFFF << 0 );
                                                          -( CAN_MB ) Mailbox Timemark
                                                          AT91_C_CAN_پیشین EQU( 0xF << 16 );
                                                          -( CAN_MB ) Mailbox اولویت_2
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
                                                          AT91_C_CAN_MOT_مصرفکننده EQU( 0x4 << 24 );
                                                          -( CAN_MB )
                                                          AT91_C_CAN_MOT_تولیدکننده EQU( 0x5 << 24 );
                                                          -( CAN_MB )
/* - -------- CAN_MAM : (CAN_MB Offset: 0x4) CAN Message Acceptance Mask Register -------- */
                                                          AT91C_CAN_MIDvB EQU( 0x3FFFF << 0 );
                                                          -( CAN_MB ) Complementary بیتها_2

                                                          لكل identifier درون extended نما_2
                                                          AT91C_CAN_MIDvA EQU( 0x7FF << 18 );
                                                          -( CAN_MB ) Identifier

                                                          لكل standard قاب_2 نما_2
                                                          AT91C_CAN_MIDE EQU( 0x1 << 29 );
                                                          -( CAN_MB ) Identifier نسخه_2
/* - -------- CAN_MID : (CAN_MB Offset: 0x8) CAN Message ID Register -------- */
/* - -------- CAN_MFID : (CAN_MB Offset: 0xc) CAN Message Family ID Register -------- */
/* - -------- CAN_MSR : (CAN_MB Offset: 0x10) CAN Message Status Register -------- */
                                                          AT91C_CAN_MTIMESTAMP EQU( 0xFFFF << 0 );
                                                          -( CAN_MB ) Timer مقدار_2
                                                          AT91C_CAN_MDLC EQU( 0xF << 16 );
                                                          -( CAN_MB ) Mailbox داده درازی کد_2
                                                          AT91C_CAN_MRTR EQU( 0x1 << 20 );
                                                          -( CAN_MB ) Mailbox Remote ارسال Request
                                                          AT91C_CAN_MABT EQU( 0x1 << 22 );
                                                          -( CAN_MB ) Mailbox پیام Abort
                                                          AT91C_CAN_MRDY EQU( 0x1 << 23 );
                                                          -( CAN_MB ) Mailbox Ready
                                                          AT91C_CAN_MMI EQU( 0x1 << 24 );
                                                          -( CAN_MB ) Mailbox پیام Ignored
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
                                                          -( CAN ) Disable / Enable کم Power نما
                                                          AT91C_CAN_ABM EQU( 0x1 << 2 );
                                                          -( CAN ) Disable / Enable Autobaud / Listen نما
                                                          AT91C_CAN_OVL EQU( 0x1 << 3 );
                                                          -( CAN ) Disable / Enable Overload قاب
                                                          AT91C_CAN_TEOF EQU( 0x1 << 4 );
                                                          -( CAN ) زمان Stamp messages at each انتها از قاب
                                                          AT91C_CAN_TTM EQU( 0x1 << 5 );
                                                          -( CAN ) Disable / Enable زمان Trigger نما
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
                                                          -( CAN ) Error فعال نما Flag
                                                          AT91C_CAN_WARN EQU( 0x1 << 17 );
                                                          -( CAN ) Warning حد Flag
                                                          AT91C_CAN_ERRP EQU( 0x1 << 18 );
                                                          -( CAN ) Error Passive نما Flag
                                                          AT91C_CAN_BOFF EQU( 0x1 << 19 );
                                                          -( CAN ) Bus Off نما Flag
                                                          AT91C_CAN_SLEEP EQU( 0x1 << 20 );
                                                          -( CAN ) Sleep Flag
                                                          AT91C_CAN_WAKEUP EQU( 0x1 << 21 );
                                                          -( CAN ) Wakeup Flag
                                                          AT91C_CAN_TOVF EQU( 0x1 << 22 );
                                                          -( CAN ) Timer سرریز_2 Flag
                                                          AT91C_CAN_TSTP EQU( 0x1 << 23 );
                                                          -( CAN ) Timestamp Flag
                                                          AT91C_CAN_CERR EQU( 0x1 << 24 );
                                                          -( CAN ) بررسی_چرخهای Error
                                                          AT91C_CAN_SERR EQU( 0x1 << 25 );
                                                          -( CAN ) Stuffing Error
                                                          AT91C_CAN_AERR EQU( 0x1 << 26 );
                                                          -( CAN ) Acknowledgment Error
                                                          AT91C_CAN_FERR EQU( 0x1 << 27 );
                                                          -( CAN ) Form Error
                                                          AT91C_CAN_BERR EQU( 0x1 << 28 );
                                                          -( CAN ) بیت Error
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
                                                          -( CAN ) Re - synchronization jump عرض segment
                                                          AT91C_CAN_BRP EQU( 0x7F << 16 );
                                                          -( CAN ) Baudrate Prescaler
                                                          AT91C_CAN_SMP EQU( 0x1 << 24 );
                                                          -( CAN ) Sampling نما_2
/* - -------- CAN_TIM : (CAN Offset: 0x18) CAN Timer Register -------- */
                                                          AT91C_CAN_TIMER EQU( 0xFFFF << 0 );
                                                          -( CAN ) Timer فیلد
/* - -------- CAN_TIMESTP : (CAN Offset: 0x1c) CAN Timestamp Register -------- */
/* - -------- CAN_ECR : (CAN Offset: 0x20) CAN Error Counter Register -------- */
                                                          AT91C_CAN_REC EQU( 0xFF << 0 );
                                                          -( CAN ) Receive Error Counter
                                                          AT91C_CAN_TEC EQU( 0xFF << 16 );
                                                          -( CAN ) Transmit Error Counter
/* - -------- CAN_TCR : (CAN Offset: 0x24) CAN Transfer Command Register -------- */
                                                          AT91C_CAN_TIMRST EQU( 0x1 << 31 );
                                                          -( CAN ) Timer Reset فیلد_2
/* - -------- CAN_ACR : (CAN Offset: 0x28) CAN Abort Command Register -------- */

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Ethernet MAC 10/100 */
/* - ***************************************************************************** */
/* - -------- EMAC_NCR : (EMAC Offset: 0x0)  -------- */
                                                          AT91C_EMAC_LB EQU( 0x1 << 0 );
                                                          -( EMAC ) Loopback.Optional.When مجموعه, loopback إشارة is at بالا_2 level.
                                                             AT91C_EMAC_LLB EQU( 0x1 << 1 );
                                                          -( EMAC ) Loopback local.
                                                             AT91C_EMAC_RE EQU( 0x1 << 2 );
                                                          -( EMAC ) Receive enable.
                                                             AT91C_EMAC_TE EQU( 0x1 << 3 );
                                                          -( EMAC ) Transmit enable.
                                                             AT91C_EMAC_MPE EQU( 0x1 << 4 );
                                                          -( EMAC ) Management پورت enable.
                                                             AT91C_EMAC_CLRSTAT EQU( 0x1 << 5 );
                                                          -( EMAC ) Clear statistics registers.
                                                             AT91C_EMAC_INCSTAT EQU( 0x1 << 6 );
                                                          -( EMAC ) Increment statistics registers.
                                                             AT91C_EMAC_WESTAT EQU( 0x1 << 7 );
                                                          -( EMAC ) Write enable

                                                          لكل statistics registers.
                                                             AT91C_EMAC_BP EQU( 0x1 << 8 );
                                                          -( EMAC ) پشت pressure.
                                                             AT91C_EMAC_TSTART EQU( 0x1 << 9 );
                                                          -( EMAC ) شروع_2 ارسال.
                                                             AT91C_EMAC_THALT EQU( 0x1 << 10 );
                                                          -( EMAC ) ارسال Halt.
                                                             AT91C_EMAC_TPFR EQU( 0x1 << 11 );
                                                          -( EMAC ) Transmit pause قاب_2
                                                          AT91C_EMAC_TZQ EQU( 0x1 << 12 );
                                                          -( EMAC ) Transmit zero برش_زمانی pause قاب_2
/* - -------- EMAC_NCFGR : (EMAC Offset: 0x4) Network Configuration Register -------- */
                                                          AT91C_EMAC_SPD EQU( 0x1 << 0 );
                                                          -( EMAC ) سرعت.
                                                             AT91C_EMAC_FD EQU( 0x1 << 1 );
                                                          -( EMAC ) پر duplex.
                                                             AT91C_EMAC_JFRAME EQU( 0x1 << 3 );
                                                          -( EMAC ) Jumbo قابها.
                                                             AT91C_EMAC_CAF EQU( 0x1 << 4 );
                                                          -( EMAC ) Copy all قابها_2.
                                                             AT91C_EMAC_NBC EQU( 0x1 << 5 );
                                                          -( EMAC ) No پخش.
                                                             AT91C_EMAC_MTI EQU( 0x1 << 6 );
                                                          -( EMAC ) Multicast hash event enable
                                                          AT91C_EMAC_UNI EQU( 0x1 << 7 );
                                                          -( EMAC ) Unicast hash enable.
                                                             AT91C_EMAC_BIG EQU( 0x1 << 8 );
                                                          -( EMAC ) Receive 1522 بایتها_2.
                                                             AT91C_EMAC_EAE EQU( 0x1 << 9 );
                                                          -( EMAC ) External آدرس_2 تطابق enable.
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
                                                          AT91_C_EMAC_RBOF_جابه_جایی_0 EQU( 0x0 << 14 );
                                                          -( EMAC ) no offset from شروع از receive میانگیر_2
                                                          AT91_C_EMAC_RBOF_جابه_جایی_1 EQU( 0x1 << 14 );
                                                          -( EMAC ) one byte offset from شروع از receive میانگیر_2
                                                          AT91_C_EMAC_RBOF_جابه_جایی_2 EQU( 0x2 << 14 );
                                                          -( EMAC ) two بایتها_2 offset from شروع از receive میانگیر_2
                                                          AT91_C_EMAC_RBOF_جابه_جایی_3 EQU( 0x3 << 14 );
                                                          -( EMAC ) three بایتها_2 offset from شروع از receive میانگیر_2
                                                          AT91C_EMAC_RLCE EQU( 0x1 << 16 );
                                                          -( EMAC ) Receive درازی فیلد Checking Enable
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
                                                          AT91_C_EMAC_ستون EQU( 0x1 << 1 );
                                                          -( EMAC )
                                                          AT91C_EMAC_RLES EQU( 0x1 << 2 );
                                                          -( EMAC )
                                                          AT91C_EMAC_TGO EQU( 0x1 << 3 );
                                                          -( EMAC ) Transmit Go
                                                          AT91C_EMAC_BEX EQU( 0x1 << 4 );
                                                          -( EMAC ) Buffers exhausted mid قاب_2
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
                                                          AT91_C_EMAC_داده EQU( 0xFFFF << 0 );
                                                          -( EMAC )
                                                          AT91_C_EMAC_کد EQU( 0x3 << 16 );
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
                                                          -( EMAC ) ARP request IP آدرس_2
                                                          AT91C_EMAC_MAG EQU( 0x1 << 16 );
                                                          -( EMAC ) Magic packet event enable
                                                          AT91C_EMAC_ARP EQU( 0x1 << 17 );
                                                          -( EMAC ) ARP request event enable
                                                          AT91C_EMAC_SA1 EQU( 0x1 << 18 );
                                                          -( EMAC ) Specific آدرس_2 سجل 1 event enable
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
                                                          AT91_C_ADC_شروع EQU( 0x1 << 1 );
                                                          -( ADC ) شروع_2 Conversion
/* - -------- ADC_MR : (ADC Offset: 0x4) ADC Mode Register -------- */
                                                          AT91C_ADC_TRGEN EQU( 0x1 << 0 );
                                                          -( ADC ) Trigger Enable
                                                          AT91C_ADC_TRGEN_DIS EQU( 0x0 );
                                                          -( ADC ) Hardware triggers are disabled.Starting a conversion is only possible by software
                                                          AT91C_ADC_TRGEN_EN EQU( 0x1 );
                                                          -( ADC ) Hardware trigger selected by TRGSEL فیلد is enabled.
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
                                                             AT91_C_ADC_LOWRES_10_بیت EQU( 0x0 << 4 );
                                                          -( ADC ) 10 - بیت_2 resolution
                                                          AT91_C_ADC_LOWRES_8_بیت EQU( 0x1 << 4 );
                                                          -( ADC ) 8 - بیت_2 resolution
                                                          AT91C_ADC_SLEEP EQU( 0x1 << 5 );
                                                          -( ADC ) Sleep نما
                                                          AT91_C_ADC_SLEEP_نرمال_نما EQU( 0x0 << 5 );
                                                          -( ADC ) نرمال نما
                                                          AT91_C_ADC_SLEEP_نما EQU( 0x1 << 5 );
                                                          -( ADC ) Sleep نما
                                                          AT91C_ADC_PRESCAL EQU( 0x3F << 8 );
                                                          -( ADC ) Prescaler نرخ_2 selection
                                                          AT91C_ADC_STARTUP EQU( 0x1F << 16 );
                                                          -( ADC ) Startup زمان
                                                          AT91C_ADC_SHTIM EQU( 0xF << 24 );
                                                          -( ADC ) Sample & Hold زمان
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
                                                          -( ADC ) انتها_2 از Conversion
                                                          AT91C_ADC_EOC1 EQU( 0x1 << 1 );
                                                          -( ADC ) انتها_2 از Conversion
                                                          AT91C_ADC_EOC2 EQU( 0x1 << 2 );
                                                          -( ADC ) انتها_2 از Conversion
                                                          AT91C_ADC_EOC3 EQU( 0x1 << 3 );
                                                          -( ADC ) انتها_2 از Conversion
                                                          AT91C_ADC_EOC4 EQU( 0x1 << 4 );
                                                          -( ADC ) انتها_2 از Conversion
                                                          AT91C_ADC_EOC5 EQU( 0x1 << 5 );
                                                          -( ADC ) انتها_2 از Conversion
                                                          AT91C_ADC_EOC6 EQU( 0x1 << 6 );
                                                          -( ADC ) انتها_2 از Conversion
                                                          AT91C_ADC_EOC7 EQU( 0x1 << 7 );
                                                          -( ADC ) انتها_2 از Conversion
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
                                                          -( ADC ) داده Ready
                                                          AT91C_ADC_GOVRE EQU( 0x1 << 17 );
                                                          -( ADC ) General Overrun
                                                          AT91C_ADC_ENDRX EQU( 0x1 << 18 );
                                                          -( ADC ) انتها_2 از Receiver Transfer
                                                          AT91C_ADC_RXBUFF EQU( 0x1 << 19 );
                                                          -( ADC ) RXBUFF وقفه_2
/* - -------- ADC_LCDR : (ADC Offset: 0x20) ADC Last Converted Data Register -------- */
                                                          AT91C_ADC_LDATA EQU( 0x3FF << 0 );
                                                          -( ADC ) آخرین داده Converted
/* - -------- ADC_IER : (ADC Offset: 0x24) ADC Interrupt Enable Register -------- */
/* - -------- ADC_IDR : (ADC Offset: 0x28) ADC Interrupt Disable Register -------- */
/* - -------- ADC_IMR : (ADC Offset: 0x2c) ADC Interrupt Mask Register -------- */
/* - -------- ADC_CDR0 : (ADC Offset: 0x30) ADC Channel Data Register 0 -------- */
                                                          AT91_C_ADC_داده EQU( 0x3FF << 0 );
                                                          -( ADC ) Converted داده
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
                                                          AT91_C_AES_شروع EQU( 0x1 << 0 );
                                                          -( AES ) Starts Processing
                                                          AT91C_AES_SWRST EQU( 0x1 << 8 );
                                                          -( AES ) Software Reset
                                                          AT91C_AES_LOADSEED EQU( 0x1 << 16 );
                                                          -( AES ) Random عدد_2 Generator دانه Loading
/* - -------- AES_MR : (AES Offset: 0x4) Mode Register -------- */
                                                          AT91C_AES_CIPHER EQU( 0x1 << 0 );
                                                          -( AES ) Processing نما
                                                          AT91C_AES_PROCDLY EQU( 0xF << 4 );
                                                          -( AES ) Processing Delay
                                                          AT91C_AES_SMOD EQU( 0x3 << 8 );
                                                          -( AES ) شروع_2 نما
                                                          AT91C_AES_SMOD_MANUAL EQU( 0x0 << 8 );
                                                          -( AES ) Manual نما:The شروع_3 بیت_2 درون سجل AES_CR must be مجموعه مقصد begin encryption or decryption.
                                                             AT91C_AES_SMOD_AUTO EQU( 0x1 << 8 );
                                                          -( AES ) Auto نما:no action درون AES_CR is necessary( cf datasheet ).
                                                             AT91C_AES_SMOD_PDC EQU( 0x2 << 8 );
                                                          -( AES ) PDC نما( cf datasheet ).
                                                             AT91C_AES_OPMOD EQU( 0x7 << 12 );
                                                          -( AES ) Operation نما
                                                          AT91C_AES_OPMOD_ECB EQU( 0x0 << 12 );
                                                          -( AES ) ECB Electronic کد_Book نما_2.
                                                             AT91C_AES_OPMOD_CBC EQU( 0x1 << 12 );
                                                          -( AES ) CBC Cipher بلوک Chaining نما_2.
                                                             AT91C_AES_OPMOD_OFB EQU( 0x2 << 12 );
                                                          -( AES ) OFB Output Feedback نما_2.
                                                             AT91C_AES_OPMOD_CFB EQU( 0x3 << 12 );
                                                          -( AES ) CFB Cipher Feedback نما_2.
                                                             AT91C_AES_OPMOD_CTR EQU( 0x4 << 12 );
                                                          -( AES ) CTR Counter نما_2.
                                                             AT91C_AES_LOD EQU( 0x1 << 15 );
                                                          -( AES ) آخرین Output داده نما
                                                          AT91C_AES_CFBS EQU( 0x7 << 16 );
                                                          -( AES ) Cipher Feedback داده اندازه_2
                                                          AT91_C_AES_CFBS_128_بیت EQU( 0x0 << 16 );
                                                          -( AES ) 128 - بیت_2.
                                                             AT91_C_AES_CFBS_64_بیت EQU( 0x1 << 16 );
                                                          -( AES ) 64 - بیت_2.
                                                             AT91_C_AES_CFBS_32_بیت EQU( 0x2 << 16 );
                                                          -( AES ) 32 - بیت_2.
                                                             AT91_C_AES_CFBS_16_بیت EQU( 0x3 << 16 );
                                                          -( AES ) 16 - بیت_2.
                                                             AT91_C_AES_CFBS_8_بیت EQU( 0x4 << 16 );
                                                          -( AES ) 8 - بیت_2.
                                                             AT91C_AES_CKEY EQU( 0xF << 20 );
                                                          -( AES ) Countermeasure کلید_2
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
                                                          -( AES ) PDC Read میانگیر انتها_2
                                                          AT91C_AES_ENDTX EQU( 0x1 << 2 );
                                                          -( AES ) PDC Write میانگیر انتها_2
                                                          AT91C_AES_RXBUFF EQU( 0x1 << 3 );
                                                          -( AES ) PDC Read میانگیر پر
                                                          AT91C_AES_TXBUFE EQU( 0x1 << 4 );
                                                          -( AES ) PDC Write میانگیر خالی
                                                          AT91C_AES_URAD EQU( 0x1 << 8 );
                                                          -( AES ) Unspecified ثبات Access Detection
/* - -------- AES_IDR : (AES Offset: 0x14) Interrupt Disable Register -------- */
/* - -------- AES_IMR : (AES Offset: 0x18) Interrupt Mask Register -------- */
/* - -------- AES_ISR : (AES Offset: 0x1c) Interrupt Status Register -------- */
                                                          AT91C_AES_URAT EQU( 0x7 << 12 );
                                                          -( AES ) Unspecified ثبات Access Type وضعیت
                                                          AT91_C_AES_URAT_درون_DAT_WRITE_DATPROC EQU( 0x0 << 12 );
                                                          -( AES ) درون_داد داده_2 سجل written during the داده_2 processing درون PDC نما_2.
                                                             AT91_C_AES_URAT_بیرون_DAT_READ_DATPROC EQU( 0x1 << 12 );
                                                          -( AES ) Output داده_2 سجل اقرأ during the داده_2 processing.
                                                             AT91C_AES_URAT_MODEREG_WRITE_DATPROC EQU( 0x2 << 12 );
                                                          -( AES ) نما سجل written during the داده_2 processing.
                                                             AT91_C_AES_URAT_بیرون_DAT_READ_SUBKEY EQU( 0x3 << 12 );
                                                          -( AES ) Output داده_2 سجل اقرأ during the sub - کلیدها generation.
                                                             AT91C_AES_URAT_MODEREG_WRITE_SUBKEY EQU( 0x4 << 12 );
                                                          -( AES ) نما سجل written during the sub - کلیدها generation.
                                                             AT91C_AES_URAT_WO_REG_READ EQU( 0x5 << 12 );
                                                          -( AES ) Write - only سجل اقرأ access.

/* - ***************************************************************************** */
/* -              SOFTWARE API DEFINITION  FOR Triple Data Encryption Standard */
/* - ***************************************************************************** */
/* - -------- TDES_CR : (TDES Offset: 0x0) Control Register -------- */
                                                             AT91_C_TDES_شروع EQU( 0x1 << 0 );
                                                          -( TDES ) Starts Processing
                                                          AT91C_TDES_SWRST EQU( 0x1 << 8 );
                                                          -( TDES ) Software Reset
/* - -------- TDES_MR : (TDES Offset: 0x4) Mode Register -------- */
                                                          AT91C_TDES_CIPHER EQU( 0x1 << 0 );
                                                          -( TDES ) Processing نما
                                                          AT91C_TDES_TDESMOD EQU( 0x1 << 1 );
                                                          -( TDES ) Single or Triple DES نما
                                                          AT91C_TDES_KEYMOD EQU( 0x1 << 4 );
                                                          -( TDES ) کلید_2 نما
                                                          AT91C_TDES_SMOD EQU( 0x3 << 8 );
                                                          -( TDES ) شروع_2 نما
                                                          AT91C_TDES_SMOD_MANUAL EQU( 0x0 << 8 );
                                                          -( TDES ) Manual نما:The شروع_3 بیت_2 درون سجل TDES_CR must be مجموعه مقصد begin encryption or decryption.
                                                             AT91C_TDES_SMOD_AUTO EQU( 0x1 << 8 );
                                                          -( TDES ) Auto نما:no action درون TDES_CR is necessary( cf datasheet ).
                                                             AT91C_TDES_SMOD_PDC EQU( 0x2 << 8 );
                                                          -( TDES ) PDC نما( cf datasheet ).
                                                             AT91C_TDES_OPMOD EQU( 0x3 << 12 );
                                                          -( TDES ) Operation نما
                                                          AT91C_TDES_OPMOD_ECB EQU( 0x0 << 12 );
                                                          -( TDES ) ECB Electronic کد_Book نما_2.
                                                             AT91C_TDES_OPMOD_CBC EQU( 0x1 << 12 );
                                                          -( TDES ) CBC Cipher بلوک Chaining نما_2.
                                                             AT91C_TDES_OPMOD_OFB EQU( 0x2 << 12 );
                                                          -( TDES ) OFB Output Feedback نما_2.
                                                             AT91C_TDES_OPMOD_CFB EQU( 0x3 << 12 );
                                                          -( TDES ) CFB Cipher Feedback نما_2.
                                                             AT91C_TDES_LOD EQU( 0x1 << 15 );
                                                          -( TDES ) آخرین Output داده نما
                                                          AT91C_TDES_CFBS EQU( 0x3 << 16 );
                                                          -( TDES ) Cipher Feedback داده اندازه_2
                                                          AT91_C_TDES_CFBS_64_بیت EQU( 0x0 << 16 );
                                                          -( TDES ) 64 - بیت_2.
                                                             AT91_C_TDES_CFBS_32_بیت EQU( 0x1 << 16 );
                                                          -( TDES ) 32 - بیت_2.
                                                             AT91_C_TDES_CFBS_16_بیت EQU( 0x2 << 16 );
                                                          -( TDES ) 16 - بیت_2.
                                                             AT91_C_TDES_CFBS_8_بیت EQU( 0x3 << 16 );
                                                          -( TDES ) 8 - بیت_2.
/* - -------- TDES_IER : (TDES Offset: 0x10) Interrupt Enable Register -------- */
                                                             AT91C_TDES_DATRDY EQU( 0x1 << 0 );
                                                          -( TDES ) DATRDY
                                                          AT91C_TDES_ENDRX EQU( 0x1 << 1 );
                                                          -( TDES ) PDC Read میانگیر انتها_2
                                                          AT91C_TDES_ENDTX EQU( 0x1 << 2 );
                                                          -( TDES ) PDC Write میانگیر انتها_2
                                                          AT91C_TDES_RXBUFF EQU( 0x1 << 3 );
                                                          -( TDES ) PDC Read میانگیر پر
                                                          AT91C_TDES_TXBUFE EQU( 0x1 << 4 );
                                                          -( TDES ) PDC Write میانگیر خالی
                                                          AT91C_TDES_URAD EQU( 0x1 << 8 );
                                                          -( TDES ) Unspecified ثبات Access Detection
/* - -------- TDES_IDR : (TDES Offset: 0x14) Interrupt Disable Register -------- */
/* - -------- TDES_IMR : (TDES Offset: 0x18) Interrupt Mask Register -------- */
/* - -------- TDES_ISR : (TDES Offset: 0x1c) Interrupt Status Register -------- */
                                                          AT91C_TDES_URAT EQU( 0x3 << 12 );
                                                          -( TDES ) Unspecified ثبات Access Type وضعیت
                                                          AT91_C_TDES_URAT_درون_DAT_WRITE_DATPROC EQU( 0x0 << 12 );
                                                          -( TDES ) درون_داد داده_2 سجل written during the داده_2 processing درون PDC نما_2.
                                                             AT91_C_TDES_URAT_بیرون_DAT_READ_DATPROC EQU( 0x1 << 12 );
                                                          -( TDES ) Output داده_2 سجل اقرأ during the داده_2 processing.
                                                             AT91C_TDES_URAT_MODEREG_WRITE_DATPROC EQU( 0x2 << 12 );
                                                          -( TDES ) نما سجل written during the داده_2 processing.
                                                             AT91C_TDES_URAT_WO_REG_READ EQU( 0x3 << 12 );
                                                          -( TDES ) Write - only سجل اقرأ access.

/* - ***************************************************************************** */
/* -               REGISTER ADDRESS DEFINITION FOR AT91SAM7X256 */
/* - ***************************************************************************** */
/* - ========== Register definition for SYS peripheral ========== */
/* - ========== Register definition for AIC peripheral ========== */
                                                             AT91C_AIC_IVR EQU( 0xFFFFF100 );
                                                          -( AIC ) IRQ وکتور_2 ثبات
                                                          AT91C_AIC_SMR EQU( 0xFFFFF000 );
                                                          -( AIC ) منبع_2 نما ثبات
                                                          AT91C_AIC_FVR EQU( 0xFFFFF104 );
                                                          -( AIC ) FIQ وکتور_2 ثبات
                                                          AT91C_AIC_DCR EQU( 0xFFFFF138 );
                                                          -( AIC ) Debug Control ثبات( Protect )
                                                          AT91C_AIC_EOICR EQU( 0xFFFFF130 );
                                                          -( AIC ) انتها_2 از وقفه_2 Command ثبات
                                                          AT91C_AIC_SVR EQU( 0xFFFFF080 );
                                                          -( AIC ) منبع_2 وکتور_2 ثبات
                                                          AT91C_AIC_FFSR EQU( 0xFFFFF148 );
                                                          -( AIC ) Fast Forcing وضعیت ثبات
                                                          AT91C_AIC_ICCR EQU( 0xFFFFF128 );
                                                          -( AIC ) وقفه_2 Clear Command ثبات
                                                          AT91C_AIC_ISR EQU( 0xFFFFF108 );
                                                          -( AIC ) وقفه_2 وضعیت ثبات
                                                          AT91C_AIC_IMR EQU( 0xFFFFF110 );
                                                          -( AIC ) وقفه_2 ماسک_2 ثبات
                                                          AT91C_AIC_IPR EQU( 0xFFFFF10C );
                                                          -( AIC ) وقفه_2 Pending ثبات
                                                          AT91C_AIC_FFER EQU( 0xFFFFF140 );
                                                          -( AIC ) Fast Forcing Enable ثبات
                                                          AT91C_AIC_IECR EQU( 0xFFFFF120 );
                                                          -( AIC ) وقفه_2 Enable Command ثبات
                                                          AT91C_AIC_ISCR EQU( 0xFFFFF12C );
                                                          -( AIC ) وقفه_2 مجموعه_2 Command ثبات
                                                          AT91C_AIC_FFDR EQU( 0xFFFFF144 );
                                                          -( AIC ) Fast Forcing Disable ثبات
                                                          AT91C_AIC_CISR EQU( 0xFFFFF114 );
                                                          -( AIC ) Core وقفه_2 وضعیت ثبات
                                                          AT91C_AIC_IDCR EQU( 0xFFFFF124 );
                                                          -( AIC ) وقفه_2 Disable Command ثبات
                                                          AT91C_AIC_SPU EQU( 0xFFFFF134 );
                                                          -( AIC ) Spurious وکتور_2 ثبات
/* - ========== Register definition for PDC_DBGU peripheral ========== */
                                                          AT91C_DBGU_TCR EQU( 0xFFFFF30C );
                                                          -( PDC_DBGU ) Transmit Counter ثبات
                                                          AT91C_DBGU_RNPR EQU( 0xFFFFF310 );
                                                          -( PDC_DBGU ) Receive بعدی اشاره_گر ثبات
                                                          AT91C_DBGU_TNPR EQU( 0xFFFFF318 );
                                                          -( PDC_DBGU ) Transmit بعدی اشاره_گر ثبات
                                                          AT91C_DBGU_TPR EQU( 0xFFFFF308 );
                                                          -( PDC_DBGU ) Transmit اشاره_گر ثبات
                                                          AT91C_DBGU_RPR EQU( 0xFFFFF300 );
                                                          -( PDC_DBGU ) Receive اشاره_گر ثبات
                                                          AT91C_DBGU_RCR EQU( 0xFFFFF304 );
                                                          -( PDC_DBGU ) Receive Counter ثبات
                                                          AT91C_DBGU_RNCR EQU( 0xFFFFF314 );
                                                          -( PDC_DBGU ) Receive بعدی Counter ثبات
                                                          AT91C_DBGU_PTCR EQU( 0xFFFFF320 );
                                                          -( PDC_DBGU ) PDC Transfer Control ثبات
                                                          AT91C_DBGU_PTSR EQU( 0xFFFFF324 );
                                                          -( PDC_DBGU ) PDC Transfer وضعیت ثبات
                                                          AT91C_DBGU_TNCR EQU( 0xFFFFF31C );
                                                          -( PDC_DBGU ) Transmit بعدی Counter ثبات
/* - ========== Register definition for DBGU peripheral ========== */
                                                          AT91C_DBGU_EXID EQU( 0xFFFFF244 );
                                                          -( DBGU ) Chip ID Extension ثبات
                                                          AT91C_DBGU_BRGR EQU( 0xFFFFF220 );
                                                          -( DBGU ) Baud نرخ Generator ثبات
                                                          AT91C_DBGU_IDR EQU( 0xFFFFF20C );
                                                          -( DBGU ) وقفه_2 Disable ثبات
                                                          AT91C_DBGU_CSR EQU( 0xFFFFF214 );
                                                          -( DBGU ) Channel وضعیت ثبات
                                                          AT91C_DBGU_CIDR EQU( 0xFFFFF240 );
                                                          -( DBGU ) Chip ID ثبات
                                                          AT91C_DBGU_MR EQU( 0xFFFFF204 );
                                                          -( DBGU ) نما ثبات
                                                          AT91C_DBGU_IMR EQU( 0xFFFFF210 );
                                                          -( DBGU ) وقفه_2 ماسک_2 ثبات
                                                          AT91C_DBGU_CR EQU( 0xFFFFF200 );
                                                          -( DBGU ) Control ثبات
                                                          AT91C_DBGU_FNTR EQU( 0xFFFFF248 );
                                                          -( DBGU ) Force NTRST ثبات
                                                          AT91C_DBGU_THR EQU( 0xFFFFF21C );
                                                          -( DBGU ) Transmitter Holding ثبات
                                                          AT91C_DBGU_RHR EQU( 0xFFFFF218 );
                                                          -( DBGU ) Receiver Holding ثبات
                                                          AT91C_DBGU_IER EQU( 0xFFFFF208 );
                                                          -( DBGU ) وقفه_2 Enable ثبات
/* - ========== Register definition for PIOA peripheral ========== */
                                                          AT91C_PIOA_ODR EQU( 0xFFFFF414 );
                                                          -( PIOA ) Output Disable Registerr
                                                          AT91C_PIOA_SODR EQU( 0xFFFFF430 );
                                                          -( PIOA ) مجموعه_2 Output داده ثبات
                                                          AT91C_PIOA_ISR EQU( 0xFFFFF44C );
                                                          -( PIOA ) وقفه_2 وضعیت ثبات
                                                          AT91C_PIOA_ABSR EQU( 0xFFFFF478 );
                                                          -( PIOA ) AB Select وضعیت ثبات
                                                          AT91C_PIOA_IER EQU( 0xFFFFF440 );
                                                          -( PIOA ) وقفه_2 Enable ثبات
                                                          AT91C_PIOA_PPUDR EQU( 0xFFFFF460 );
                                                          -( PIOA ) Pull - به_بالا Disable ثبات
                                                          AT91C_PIOA_IMR EQU( 0xFFFFF448 );
                                                          -( PIOA ) وقفه_2 ماسک_2 ثبات
                                                          AT91_C_PIOA_در_هر EQU( 0xFFFFF400 );
                                                          -( PIOA ) PIO Enable ثبات
                                                          AT91C_PIOA_IFDR EQU( 0xFFFFF424 );
                                                          -( PIOA ) درون_داد Filter Disable ثبات
                                                          AT91C_PIOA_OWDR EQU( 0xFFFFF4A4 );
                                                          -( PIOA ) Output Write Disable ثبات
                                                          AT91C_PIOA_MDSR EQU( 0xFFFFF458 );
                                                          -( PIOA ) Multi - driver وضعیت ثبات
                                                          AT91C_PIOA_IDR EQU( 0xFFFFF444 );
                                                          -( PIOA ) وقفه_2 Disable ثبات
                                                          AT91C_PIOA_ODSR EQU( 0xFFFFF438 );
                                                          -( PIOA ) Output داده وضعیت ثبات
                                                          AT91C_PIOA_PPUSR EQU( 0xFFFFF468 );
                                                          -( PIOA ) Pull - به_بالا وضعیت ثبات
                                                          AT91C_PIOA_OWSR EQU( 0xFFFFF4A8 );
                                                          -( PIOA ) Output Write وضعیت ثبات
                                                          AT91C_PIOA_BSR EQU( 0xFFFFF474 );
                                                          -( PIOA ) Select B ثبات
                                                          AT91C_PIOA_OWER EQU( 0xFFFFF4A0 );
                                                          -( PIOA ) Output Write Enable ثبات
                                                          AT91C_PIOA_IFER EQU( 0xFFFFF420 );
                                                          -( PIOA ) درون_داد Filter Enable ثبات
                                                          AT91C_PIOA_PDSR EQU( 0xFFFFF43C );
                                                          -( PIOA ) Pin داده وضعیت ثبات
                                                          AT91C_PIOA_PPUER EQU( 0xFFFFF464 );
                                                          -( PIOA ) Pull - به_بالا Enable ثبات
                                                          AT91C_PIOA_OSR EQU( 0xFFFFF418 );
                                                          -( PIOA ) Output وضعیت ثبات
                                                          AT91C_PIOA_ASR EQU( 0xFFFFF470 );
                                                          -( PIOA ) Select A ثبات
                                                          AT91C_PIOA_MDDR EQU( 0xFFFFF454 );
                                                          -( PIOA ) Multi - driver Disable ثبات
                                                          AT91C_PIOA_CODR EQU( 0xFFFFF434 );
                                                          -( PIOA ) Clear Output داده ثبات
                                                          AT91C_PIOA_MDER EQU( 0xFFFFF450 );
                                                          -( PIOA ) Multi - driver Enable ثبات
                                                          AT91C_PIOA_PDR EQU( 0xFFFFF404 );
                                                          -( PIOA ) PIO Disable ثبات
                                                          AT91C_PIOA_IFSR EQU( 0xFFFFF428 );
                                                          -( PIOA ) درون_داد Filter وضعیت ثبات
                                                          AT91C_PIOA_OER EQU( 0xFFFFF410 );
                                                          -( PIOA ) Output Enable ثبات
                                                          AT91C_PIOA_PSR EQU( 0xFFFFF408 );
                                                          -( PIOA ) PIO وضعیت ثبات
/* - ========== Register definition for PIOB peripheral ========== */
                                                          AT91C_PIOB_OWDR EQU( 0xFFFFF6A4 );
                                                          -( PIOB ) Output Write Disable ثبات
                                                          AT91C_PIOB_MDER EQU( 0xFFFFF650 );
                                                          -( PIOB ) Multi - driver Enable ثبات
                                                          AT91C_PIOB_PPUSR EQU( 0xFFFFF668 );
                                                          -( PIOB ) Pull - به_بالا وضعیت ثبات
                                                          AT91C_PIOB_IMR EQU( 0xFFFFF648 );
                                                          -( PIOB ) وقفه_2 ماسک_2 ثبات
                                                          AT91C_PIOB_ASR EQU( 0xFFFFF670 );
                                                          -( PIOB ) Select A ثبات
                                                          AT91C_PIOB_PPUDR EQU( 0xFFFFF660 );
                                                          -( PIOB ) Pull - به_بالا Disable ثبات
                                                          AT91C_PIOB_PSR EQU( 0xFFFFF608 );
                                                          -( PIOB ) PIO وضعیت ثبات
                                                          AT91C_PIOB_IER EQU( 0xFFFFF640 );
                                                          -( PIOB ) وقفه_2 Enable ثبات
                                                          AT91C_PIOB_CODR EQU( 0xFFFFF634 );
                                                          -( PIOB ) Clear Output داده ثبات
                                                          AT91C_PIOB_OWER EQU( 0xFFFFF6A0 );
                                                          -( PIOB ) Output Write Enable ثبات
                                                          AT91C_PIOB_ABSR EQU( 0xFFFFF678 );
                                                          -( PIOB ) AB Select وضعیت ثبات
                                                          AT91C_PIOB_IFDR EQU( 0xFFFFF624 );
                                                          -( PIOB ) درون_داد Filter Disable ثبات
                                                          AT91C_PIOB_PDSR EQU( 0xFFFFF63C );
                                                          -( PIOB ) Pin داده وضعیت ثبات
                                                          AT91C_PIOB_IDR EQU( 0xFFFFF644 );
                                                          -( PIOB ) وقفه_2 Disable ثبات
                                                          AT91C_PIOB_OWSR EQU( 0xFFFFF6A8 );
                                                          -( PIOB ) Output Write وضعیت ثبات
                                                          AT91C_PIOB_PDR EQU( 0xFFFFF604 );
                                                          -( PIOB ) PIO Disable ثبات
                                                          AT91C_PIOB_ODR EQU( 0xFFFFF614 );
                                                          -( PIOB ) Output Disable Registerr
                                                          AT91C_PIOB_IFSR EQU( 0xFFFFF628 );
                                                          -( PIOB ) درون_داد Filter وضعیت ثبات
                                                          AT91C_PIOB_PPUER EQU( 0xFFFFF664 );
                                                          -( PIOB ) Pull - به_بالا Enable ثبات
                                                          AT91C_PIOB_SODR EQU( 0xFFFFF630 );
                                                          -( PIOB ) مجموعه_2 Output داده ثبات
                                                          AT91C_PIOB_ISR EQU( 0xFFFFF64C );
                                                          -( PIOB ) وقفه_2 وضعیت ثبات
                                                          AT91C_PIOB_ODSR EQU( 0xFFFFF638 );
                                                          -( PIOB ) Output داده وضعیت ثبات
                                                          AT91C_PIOB_OSR EQU( 0xFFFFF618 );
                                                          -( PIOB ) Output وضعیت ثبات
                                                          AT91C_PIOB_MDSR EQU( 0xFFFFF658 );
                                                          -( PIOB ) Multi - driver وضعیت ثبات
                                                          AT91C_PIOB_IFER EQU( 0xFFFFF620 );
                                                          -( PIOB ) درون_داد Filter Enable ثبات
                                                          AT91C_PIOB_BSR EQU( 0xFFFFF674 );
                                                          -( PIOB ) Select B ثبات
                                                          AT91C_PIOB_MDDR EQU( 0xFFFFF654 );
                                                          -( PIOB ) Multi - driver Disable ثبات
                                                          AT91C_PIOB_OER EQU( 0xFFFFF610 );
                                                          -( PIOB ) Output Enable ثبات
                                                          AT91_C_PIOB_در_هر EQU( 0xFFFFF600 );
                                                          -( PIOB ) PIO Enable ثبات
/* - ========== Register definition for CKGR peripheral ========== */
                                                          AT91C_CKGR_MOR EQU( 0xFFFFFC20 );
                                                          -( CKGR ) Main Oscillator ثبات
                                                          AT91C_CKGR_PLLR EQU( 0xFFFFFC2C );
                                                          -( CKGR ) PLL ثبات
                                                          AT91C_CKGR_MCFR EQU( 0xFFFFFC24 );
                                                          -( CKGR ) Main Clock Frequency ثبات
/* - ========== Register definition for PMC peripheral ========== */
                                                          AT91C_PMC_IDR EQU( 0xFFFFFC64 );
                                                          -( PMC ) وقفه_2 Disable ثبات
                                                          AT91C_PMC_MOR EQU( 0xFFFFFC20 );
                                                          -( PMC ) Main Oscillator ثبات
                                                          AT91C_PMC_PLLR EQU( 0xFFFFFC2C );
                                                          -( PMC ) PLL ثبات
                                                          AT91C_PMC_PCER EQU( 0xFFFFFC10 );
                                                          -( PMC ) Peripheral Clock Enable ثبات
                                                          AT91C_PMC_PCKR EQU( 0xFFFFFC40 );
                                                          -( PMC ) Programmable Clock ثبات
                                                          AT91C_PMC_MCKR EQU( 0xFFFFFC30 );
                                                          -( PMC ) Master Clock ثبات
                                                          AT91C_PMC_SCDR EQU( 0xFFFFFC04 );
                                                          -( PMC ) System Clock Disable ثبات
                                                          AT91C_PMC_PCDR EQU( 0xFFFFFC14 );
                                                          -( PMC ) Peripheral Clock Disable ثبات
                                                          AT91C_PMC_SCSR EQU( 0xFFFFFC08 );
                                                          -( PMC ) System Clock وضعیت ثبات
                                                          AT91C_PMC_PCSR EQU( 0xFFFFFC18 );
                                                          -( PMC ) Peripheral Clock وضعیت ثبات
                                                          AT91C_PMC_MCFR EQU( 0xFFFFFC24 );
                                                          -( PMC ) Main Clock Frequency ثبات
                                                          AT91C_PMC_SCER EQU( 0xFFFFFC00 );
                                                          -( PMC ) System Clock Enable ثبات
                                                          AT91C_PMC_IMR EQU( 0xFFFFFC6C );
                                                          -( PMC ) وقفه_2 ماسک_2 ثبات
                                                          AT91C_PMC_IER EQU( 0xFFFFFC60 );
                                                          -( PMC ) وقفه_2 Enable ثبات
                                                          AT91C_PMC_SR EQU( 0xFFFFFC68 );
                                                          -( PMC ) وضعیت ثبات
/* - ========== Register definition for RSTC peripheral ========== */
                                                          AT91C_RSTC_RCR EQU( 0xFFFFFD00 );
                                                          -( RSTC ) Reset Control ثبات
                                                          AT91C_RSTC_RMR EQU( 0xFFFFFD08 );
                                                          -( RSTC ) Reset نما ثبات
                                                          AT91C_RSTC_RSR EQU( 0xFFFFFD04 );
                                                          -( RSTC ) Reset وضعیت ثبات
/* - ========== Register definition for RTTC peripheral ========== */
                                                          AT91C_RTTC_RTSR EQU( 0xFFFFFD2C );
                                                          -( RTTC ) Real - time وضعیت ثبات
                                                          AT91C_RTTC_RTMR EQU( 0xFFFFFD20 );
                                                          -( RTTC ) Real - time نما ثبات
                                                          AT91C_RTTC_RTVR EQU( 0xFFFFFD28 );
                                                          -( RTTC ) Real - time مقدار_2 ثبات
                                                          AT91C_RTTC_RTAR EQU( 0xFFFFFD24 );
                                                          -( RTTC ) Real - time Alarm ثبات
/* - ========== Register definition for PITC peripheral ========== */
                                                          AT91C_PITC_PIVR EQU( 0xFFFFFD38 );
                                                          -( PITC ) Period Interval مقدار_2 ثبات
                                                          AT91C_PITC_PISR EQU( 0xFFFFFD34 );
                                                          -( PITC ) Period Interval وضعیت ثبات
                                                          AT91C_PITC_PIIR EQU( 0xFFFFFD3C );
                                                          -( PITC ) Period Interval Image ثبات
                                                          AT91C_PITC_PIMR EQU( 0xFFFFFD30 );
                                                          -( PITC ) Period Interval نما ثبات
/* - ========== Register definition for WDTC peripheral ========== */
                                                          AT91C_WDTC_WDCR EQU( 0xFFFFFD40 );
                                                          -( WDTC ) Watchdog Control ثبات
                                                          AT91C_WDTC_WDSR EQU( 0xFFFFFD48 );
                                                          -( WDTC ) Watchdog وضعیت ثبات
                                                          AT91C_WDTC_WDMR EQU( 0xFFFFFD44 );
                                                          -( WDTC ) Watchdog نما ثبات
/* - ========== Register definition for VREG peripheral ========== */
                                                          AT91C_VREG_MR EQU( 0xFFFFFD60 );
                                                          -( VREG ) Voltage Regulator نما ثبات
/* - ========== Register definition for MC peripheral ========== */
                                                          AT91C_MC_ASR EQU( 0xFFFFFF04 );
                                                          -( MC ) MC Abort وضعیت ثبات
                                                          AT91C_MC_RCR EQU( 0xFFFFFF00 );
                                                          -( MC ) MC Remap Control ثبات
                                                          AT91C_MC_FCR EQU( 0xFFFFFF64 );
                                                          -( MC ) MC Flash Command ثبات
                                                          AT91C_MC_AASR EQU( 0xFFFFFF08 );
                                                          -( MC ) MC Abort آدرس وضعیت ثبات
                                                          AT91C_MC_FSR EQU( 0xFFFFFF68 );
                                                          -( MC ) MC Flash وضعیت ثبات
                                                          AT91C_MC_FMR EQU( 0xFFFFFF60 );
                                                          -( MC ) MC Flash نما ثبات
/* - ========== Register definition for PDC_SPI1 peripheral ========== */
                                                          AT91C_SPI1_PTCR EQU( 0xFFFE4120 );
                                                          -( PDC_SPI1 ) PDC Transfer Control ثبات
                                                          AT91C_SPI1_RPR EQU( 0xFFFE4100 );
                                                          -( PDC_SPI1 ) Receive اشاره_گر ثبات
                                                          AT91C_SPI1_TNCR EQU( 0xFFFE411C );
                                                          -( PDC_SPI1 ) Transmit بعدی Counter ثبات
                                                          AT91C_SPI1_TPR EQU( 0xFFFE4108 );
                                                          -( PDC_SPI1 ) Transmit اشاره_گر ثبات
                                                          AT91C_SPI1_TNPR EQU( 0xFFFE4118 );
                                                          -( PDC_SPI1 ) Transmit بعدی اشاره_گر ثبات
                                                          AT91C_SPI1_TCR EQU( 0xFFFE410C );
                                                          -( PDC_SPI1 ) Transmit Counter ثبات
                                                          AT91C_SPI1_RCR EQU( 0xFFFE4104 );
                                                          -( PDC_SPI1 ) Receive Counter ثبات
                                                          AT91C_SPI1_RNPR EQU( 0xFFFE4110 );
                                                          -( PDC_SPI1 ) Receive بعدی اشاره_گر ثبات
                                                          AT91C_SPI1_RNCR EQU( 0xFFFE4114 );
                                                          -( PDC_SPI1 ) Receive بعدی Counter ثبات
                                                          AT91C_SPI1_PTSR EQU( 0xFFFE4124 );
                                                          -( PDC_SPI1 ) PDC Transfer وضعیت ثبات
/* - ========== Register definition for SPI1 peripheral ========== */
                                                          AT91C_SPI1_IMR EQU( 0xFFFE401C );
                                                          -( SPI1 ) وقفه_2 ماسک_2 ثبات
                                                          AT91C_SPI1_IER EQU( 0xFFFE4014 );
                                                          -( SPI1 ) وقفه_2 Enable ثبات
                                                          AT91C_SPI1_MR EQU( 0xFFFE4004 );
                                                          -( SPI1 ) نما ثبات
                                                          AT91C_SPI1_RDR EQU( 0xFFFE4008 );
                                                          -( SPI1 ) Receive داده ثبات
                                                          AT91C_SPI1_IDR EQU( 0xFFFE4018 );
                                                          -( SPI1 ) وقفه_2 Disable ثبات
                                                          AT91C_SPI1_SR EQU( 0xFFFE4010 );
                                                          -( SPI1 ) وضعیت ثبات
                                                          AT91C_SPI1_TDR EQU( 0xFFFE400C );
                                                          -( SPI1 ) Transmit داده ثبات
                                                          AT91C_SPI1_CR EQU( 0xFFFE4000 );
                                                          -( SPI1 ) Control ثبات
                                                          AT91C_SPI1_CSR EQU( 0xFFFE4030 );
                                                          -( SPI1 ) Chip Select ثبات
/* - ========== Register definition for PDC_SPI0 peripheral ========== */
                                                          AT91C_SPI0_PTCR EQU( 0xFFFE0120 );
                                                          -( PDC_SPI0 ) PDC Transfer Control ثبات
                                                          AT91C_SPI0_TPR EQU( 0xFFFE0108 );
                                                          -( PDC_SPI0 ) Transmit اشاره_گر ثبات
                                                          AT91C_SPI0_TCR EQU( 0xFFFE010C );
                                                          -( PDC_SPI0 ) Transmit Counter ثبات
                                                          AT91C_SPI0_RCR EQU( 0xFFFE0104 );
                                                          -( PDC_SPI0 ) Receive Counter ثبات
                                                          AT91C_SPI0_PTSR EQU( 0xFFFE0124 );
                                                          -( PDC_SPI0 ) PDC Transfer وضعیت ثبات
                                                          AT91C_SPI0_RNPR EQU( 0xFFFE0110 );
                                                          -( PDC_SPI0 ) Receive بعدی اشاره_گر ثبات
                                                          AT91C_SPI0_RPR EQU( 0xFFFE0100 );
                                                          -( PDC_SPI0 ) Receive اشاره_گر ثبات
                                                          AT91C_SPI0_TNCR EQU( 0xFFFE011C );
                                                          -( PDC_SPI0 ) Transmit بعدی Counter ثبات
                                                          AT91C_SPI0_RNCR EQU( 0xFFFE0114 );
                                                          -( PDC_SPI0 ) Receive بعدی Counter ثبات
                                                          AT91C_SPI0_TNPR EQU( 0xFFFE0118 );
                                                          -( PDC_SPI0 ) Transmit بعدی اشاره_گر ثبات
/* - ========== Register definition for SPI0 peripheral ========== */
                                                          AT91C_SPI0_IER EQU( 0xFFFE0014 );
                                                          -( SPI0 ) وقفه_2 Enable ثبات
                                                          AT91C_SPI0_SR EQU( 0xFFFE0010 );
                                                          -( SPI0 ) وضعیت ثبات
                                                          AT91C_SPI0_IDR EQU( 0xFFFE0018 );
                                                          -( SPI0 ) وقفه_2 Disable ثبات
                                                          AT91C_SPI0_CR EQU( 0xFFFE0000 );
                                                          -( SPI0 ) Control ثبات
                                                          AT91C_SPI0_MR EQU( 0xFFFE0004 );
                                                          -( SPI0 ) نما ثبات
                                                          AT91C_SPI0_IMR EQU( 0xFFFE001C );
                                                          -( SPI0 ) وقفه_2 ماسک_2 ثبات
                                                          AT91C_SPI0_TDR EQU( 0xFFFE000C );
                                                          -( SPI0 ) Transmit داده ثبات
                                                          AT91C_SPI0_RDR EQU( 0xFFFE0008 );
                                                          -( SPI0 ) Receive داده ثبات
                                                          AT91C_SPI0_CSR EQU( 0xFFFE0030 );
                                                          -( SPI0 ) Chip Select ثبات
/* - ========== Register definition for PDC_US1 peripheral ========== */
                                                          AT91C_US1_RNCR EQU( 0xFFFC4114 );
                                                          -( PDC_US1 ) Receive بعدی Counter ثبات
                                                          AT91C_US1_PTCR EQU( 0xFFFC4120 );
                                                          -( PDC_US1 ) PDC Transfer Control ثبات
                                                          AT91C_US1_TCR EQU( 0xFFFC410C );
                                                          -( PDC_US1 ) Transmit Counter ثبات
                                                          AT91C_US1_PTSR EQU( 0xFFFC4124 );
                                                          -( PDC_US1 ) PDC Transfer وضعیت ثبات
                                                          AT91C_US1_TNPR EQU( 0xFFFC4118 );
                                                          -( PDC_US1 ) Transmit بعدی اشاره_گر ثبات
                                                          AT91C_US1_RCR EQU( 0xFFFC4104 );
                                                          -( PDC_US1 ) Receive Counter ثبات
                                                          AT91C_US1_RNPR EQU( 0xFFFC4110 );
                                                          -( PDC_US1 ) Receive بعدی اشاره_گر ثبات
                                                          AT91C_US1_RPR EQU( 0xFFFC4100 );
                                                          -( PDC_US1 ) Receive اشاره_گر ثبات
                                                          AT91C_US1_TNCR EQU( 0xFFFC411C );
                                                          -( PDC_US1 ) Transmit بعدی Counter ثبات
                                                          AT91C_US1_TPR EQU( 0xFFFC4108 );
                                                          -( PDC_US1 ) Transmit اشاره_گر ثبات
/* - ========== Register definition for US1 peripheral ========== */
                                                          AT91C_US1_IF EQU( 0xFFFC404C );
                                                          -( US1 ) IRDA_FILTER ثبات
                                                          AT91C_US1_NER EQU( 0xFFFC4044 );
                                                          -( US1 ) Nb Errors ثبات
                                                          AT91C_US1_RTOR EQU( 0xFFFC4024 );
                                                          -( US1 ) Receiver زمان - بیرون ثبات
                                                          AT91C_US1_CSR EQU( 0xFFFC4014 );
                                                          -( US1 ) Channel وضعیت ثبات
                                                          AT91C_US1_IDR EQU( 0xFFFC400C );
                                                          -( US1 ) وقفه_2 Disable ثبات
                                                          AT91C_US1_IER EQU( 0xFFFC4008 );
                                                          -( US1 ) وقفه_2 Enable ثبات
                                                          AT91C_US1_THR EQU( 0xFFFC401C );
                                                          -( US1 ) Transmitter Holding ثبات
                                                          AT91C_US1_TTGR EQU( 0xFFFC4028 );
                                                          -( US1 ) Transmitter زمان - guard ثبات
                                                          AT91C_US1_RHR EQU( 0xFFFC4018 );
                                                          -( US1 ) Receiver Holding ثبات
                                                          AT91C_US1_BRGR EQU( 0xFFFC4020 );
                                                          -( US1 ) Baud نرخ Generator ثبات
                                                          AT91C_US1_IMR EQU( 0xFFFC4010 );
                                                          -( US1 ) وقفه_2 ماسک_2 ثبات
                                                          AT91C_US1_FIDI EQU( 0xFFFC4040 );
                                                          -( US1 ) FI_DI_نسبت ثبات
                                                          AT91C_US1_CR EQU( 0xFFFC4000 );
                                                          -( US1 ) Control ثبات
                                                          AT91C_US1_MR EQU( 0xFFFC4004 );
                                                          -( US1 ) نما ثبات
/* - ========== Register definition for PDC_US0 peripheral ========== */
                                                          AT91C_US0_TNPR EQU( 0xFFFC0118 );
                                                          -( PDC_US0 ) Transmit بعدی اشاره_گر ثبات
                                                          AT91C_US0_RNPR EQU( 0xFFFC0110 );
                                                          -( PDC_US0 ) Receive بعدی اشاره_گر ثبات
                                                          AT91C_US0_TCR EQU( 0xFFFC010C );
                                                          -( PDC_US0 ) Transmit Counter ثبات
                                                          AT91C_US0_PTCR EQU( 0xFFFC0120 );
                                                          -( PDC_US0 ) PDC Transfer Control ثبات
                                                          AT91C_US0_PTSR EQU( 0xFFFC0124 );
                                                          -( PDC_US0 ) PDC Transfer وضعیت ثبات
                                                          AT91C_US0_TNCR EQU( 0xFFFC011C );
                                                          -( PDC_US0 ) Transmit بعدی Counter ثبات
                                                          AT91C_US0_TPR EQU( 0xFFFC0108 );
                                                          -( PDC_US0 ) Transmit اشاره_گر ثبات
                                                          AT91C_US0_RCR EQU( 0xFFFC0104 );
                                                          -( PDC_US0 ) Receive Counter ثبات
                                                          AT91C_US0_RPR EQU( 0xFFFC0100 );
                                                          -( PDC_US0 ) Receive اشاره_گر ثبات
                                                          AT91C_US0_RNCR EQU( 0xFFFC0114 );
                                                          -( PDC_US0 ) Receive بعدی Counter ثبات
/* - ========== Register definition for US0 peripheral ========== */
                                                          AT91C_US0_BRGR EQU( 0xFFFC0020 );
                                                          -( US0 ) Baud نرخ Generator ثبات
                                                          AT91C_US0_NER EQU( 0xFFFC0044 );
                                                          -( US0 ) Nb Errors ثبات
                                                          AT91C_US0_CR EQU( 0xFFFC0000 );
                                                          -( US0 ) Control ثبات
                                                          AT91C_US0_IMR EQU( 0xFFFC0010 );
                                                          -( US0 ) وقفه_2 ماسک_2 ثبات
                                                          AT91C_US0_FIDI EQU( 0xFFFC0040 );
                                                          -( US0 ) FI_DI_نسبت ثبات
                                                          AT91C_US0_TTGR EQU( 0xFFFC0028 );
                                                          -( US0 ) Transmitter زمان - guard ثبات
                                                          AT91C_US0_MR EQU( 0xFFFC0004 );
                                                          -( US0 ) نما ثبات
                                                          AT91C_US0_RTOR EQU( 0xFFFC0024 );
                                                          -( US0 ) Receiver زمان - بیرون ثبات
                                                          AT91C_US0_CSR EQU( 0xFFFC0014 );
                                                          -( US0 ) Channel وضعیت ثبات
                                                          AT91C_US0_RHR EQU( 0xFFFC0018 );
                                                          -( US0 ) Receiver Holding ثبات
                                                          AT91C_US0_IDR EQU( 0xFFFC000C );
                                                          -( US0 ) وقفه_2 Disable ثبات
                                                          AT91C_US0_THR EQU( 0xFFFC001C );
                                                          -( US0 ) Transmitter Holding ثبات
                                                          AT91C_US0_IF EQU( 0xFFFC004C );
                                                          -( US0 ) IRDA_FILTER ثبات
                                                          AT91C_US0_IER EQU( 0xFFFC0008 );
                                                          -( US0 ) وقفه_2 Enable ثبات
/* - ========== Register definition for PDC_SSC peripheral ========== */
                                                          AT91C_SSC_TNCR EQU( 0xFFFD411C );
                                                          -( PDC_SSC ) Transmit بعدی Counter ثبات
                                                          AT91C_SSC_RPR EQU( 0xFFFD4100 );
                                                          -( PDC_SSC ) Receive اشاره_گر ثبات
                                                          AT91C_SSC_RNCR EQU( 0xFFFD4114 );
                                                          -( PDC_SSC ) Receive بعدی Counter ثبات
                                                          AT91C_SSC_TPR EQU( 0xFFFD4108 );
                                                          -( PDC_SSC ) Transmit اشاره_گر ثبات
                                                          AT91C_SSC_PTCR EQU( 0xFFFD4120 );
                                                          -( PDC_SSC ) PDC Transfer Control ثبات
                                                          AT91C_SSC_TCR EQU( 0xFFFD410C );
                                                          -( PDC_SSC ) Transmit Counter ثبات
                                                          AT91C_SSC_RCR EQU( 0xFFFD4104 );
                                                          -( PDC_SSC ) Receive Counter ثبات
                                                          AT91C_SSC_RNPR EQU( 0xFFFD4110 );
                                                          -( PDC_SSC ) Receive بعدی اشاره_گر ثبات
                                                          AT91C_SSC_TNPR EQU( 0xFFFD4118 );
                                                          -( PDC_SSC ) Transmit بعدی اشاره_گر ثبات
                                                          AT91C_SSC_PTSR EQU( 0xFFFD4124 );
                                                          -( PDC_SSC ) PDC Transfer وضعیت ثبات
/* - ========== Register definition for SSC peripheral ========== */
                                                          AT91C_SSC_RHR EQU( 0xFFFD4020 );
                                                          -( SSC ) Receive Holding ثبات
                                                          AT91C_SSC_RSHR EQU( 0xFFFD4030 );
                                                          -( SSC ) Receive Sync Holding ثبات
                                                          AT91C_SSC_TFMR EQU( 0xFFFD401C );
                                                          -( SSC ) Transmit قاب نما ثبات
                                                          AT91C_SSC_IDR EQU( 0xFFFD4048 );
                                                          -( SSC ) وقفه_2 Disable ثبات
                                                          AT91C_SSC_THR EQU( 0xFFFD4024 );
                                                          -( SSC ) Transmit Holding ثبات
                                                          AT91C_SSC_RCMR EQU( 0xFFFD4010 );
                                                          -( SSC ) Receive Clock نما_ثبات
                                                          AT91C_SSC_IER EQU( 0xFFFD4044 );
                                                          -( SSC ) وقفه_2 Enable ثبات
                                                          AT91C_SSC_TSHR EQU( 0xFFFD4034 );
                                                          -( SSC ) Transmit Sync Holding ثبات
                                                          AT91C_SSC_SR EQU( 0xFFFD4040 );
                                                          -( SSC ) وضعیت ثبات
                                                          AT91C_SSC_CMR EQU( 0xFFFD4004 );
                                                          -( SSC ) Clock نما ثبات
                                                          AT91C_SSC_TCMR EQU( 0xFFFD4018 );
                                                          -( SSC ) Transmit Clock نما ثبات
                                                          AT91C_SSC_CR EQU( 0xFFFD4000 );
                                                          -( SSC ) Control ثبات
                                                          AT91C_SSC_IMR EQU( 0xFFFD404C );
                                                          -( SSC ) وقفه_2 ماسک_2 ثبات
                                                          AT91C_SSC_RFMR EQU( 0xFFFD4014 );
                                                          -( SSC ) Receive قاب نما ثبات
/* - ========== Register definition for TWI peripheral ========== */
                                                          AT91C_TWI_IER EQU( 0xFFFB8024 );
                                                          -( TWI ) وقفه_2 Enable ثبات
                                                          AT91C_TWI_CR EQU( 0xFFFB8000 );
                                                          -( TWI ) Control ثبات
                                                          AT91C_TWI_SR EQU( 0xFFFB8020 );
                                                          -( TWI ) وضعیت ثبات
                                                          AT91C_TWI_IMR EQU( 0xFFFB802C );
                                                          -( TWI ) وقفه_2 ماسک_2 ثبات
                                                          AT91C_TWI_THR EQU( 0xFFFB8034 );
                                                          -( TWI ) Transmit Holding ثبات
                                                          AT91C_TWI_IDR EQU( 0xFFFB8028 );
                                                          -( TWI ) وقفه_2 Disable ثبات
                                                          AT91C_TWI_IADR EQU( 0xFFFB800C );
                                                          -( TWI ) داخلی آدرس ثبات
                                                          AT91C_TWI_MMR EQU( 0xFFFB8004 );
                                                          -( TWI ) Master نما ثبات
                                                          AT91C_TWI_CWGR EQU( 0xFFFB8010 );
                                                          -( TWI ) Clock Waveform Generator ثبات
                                                          AT91C_TWI_RHR EQU( 0xFFFB8030 );
                                                          -( TWI ) Receive Holding ثبات
/* - ========== Register definition for PWMC_CH3 peripheral ========== */
                                                          AT91C_PWMC_CH3_CUPDR EQU( 0xFFFCC270 );
                                                          -( PWMC_CH3 ) Channel Update ثبات
                                                          AT91C_PWMC_CH3_Reserved EQU( 0xFFFCC274 );
                                                          -( PWMC_CH3 ) Reserved
                                                          AT91C_PWMC_CH3_CPRDR EQU( 0xFFFCC268 );
                                                          -( PWMC_CH3 ) Channel Period ثبات
                                                          AT91C_PWMC_CH3_CDTYR EQU( 0xFFFCC264 );
                                                          -( PWMC_CH3 ) Channel Duty چرخه_2 ثبات
                                                          AT91C_PWMC_CH3_CCNTR EQU( 0xFFFCC26C );
                                                          -( PWMC_CH3 ) Channel Counter ثبات
                                                          AT91C_PWMC_CH3_CMR EQU( 0xFFFCC260 );
                                                          -( PWMC_CH3 ) Channel نما ثبات
/* - ========== Register definition for PWMC_CH2 peripheral ========== */
                                                          AT91C_PWMC_CH2_Reserved EQU( 0xFFFCC254 );
                                                          -( PWMC_CH2 ) Reserved
                                                          AT91C_PWMC_CH2_CMR EQU( 0xFFFCC240 );
                                                          -( PWMC_CH2 ) Channel نما ثبات
                                                          AT91C_PWMC_CH2_CCNTR EQU( 0xFFFCC24C );
                                                          -( PWMC_CH2 ) Channel Counter ثبات
                                                          AT91C_PWMC_CH2_CPRDR EQU( 0xFFFCC248 );
                                                          -( PWMC_CH2 ) Channel Period ثبات
                                                          AT91C_PWMC_CH2_CUPDR EQU( 0xFFFCC250 );
                                                          -( PWMC_CH2 ) Channel Update ثبات
                                                          AT91C_PWMC_CH2_CDTYR EQU( 0xFFFCC244 );
                                                          -( PWMC_CH2 ) Channel Duty چرخه_2 ثبات
/* - ========== Register definition for PWMC_CH1 peripheral ========== */
                                                          AT91C_PWMC_CH1_Reserved EQU( 0xFFFCC234 );
                                                          -( PWMC_CH1 ) Reserved
                                                          AT91C_PWMC_CH1_CUPDR EQU( 0xFFFCC230 );
                                                          -( PWMC_CH1 ) Channel Update ثبات
                                                          AT91C_PWMC_CH1_CPRDR EQU( 0xFFFCC228 );
                                                          -( PWMC_CH1 ) Channel Period ثبات
                                                          AT91C_PWMC_CH1_CCNTR EQU( 0xFFFCC22C );
                                                          -( PWMC_CH1 ) Channel Counter ثبات
                                                          AT91C_PWMC_CH1_CDTYR EQU( 0xFFFCC224 );
                                                          -( PWMC_CH1 ) Channel Duty چرخه_2 ثبات
                                                          AT91C_PWMC_CH1_CMR EQU( 0xFFFCC220 );
                                                          -( PWMC_CH1 ) Channel نما ثبات
/* - ========== Register definition for PWMC_CH0 peripheral ========== */
                                                          AT91C_PWMC_CH0_Reserved EQU( 0xFFFCC214 );
                                                          -( PWMC_CH0 ) Reserved
                                                          AT91C_PWMC_CH0_CPRDR EQU( 0xFFFCC208 );
                                                          -( PWMC_CH0 ) Channel Period ثبات
                                                          AT91C_PWMC_CH0_CDTYR EQU( 0xFFFCC204 );
                                                          -( PWMC_CH0 ) Channel Duty چرخه_2 ثبات
                                                          AT91C_PWMC_CH0_CMR EQU( 0xFFFCC200 );
                                                          -( PWMC_CH0 ) Channel نما ثبات
                                                          AT91C_PWMC_CH0_CUPDR EQU( 0xFFFCC210 );
                                                          -( PWMC_CH0 ) Channel Update ثبات
                                                          AT91C_PWMC_CH0_CCNTR EQU( 0xFFFCC20C );
                                                          -( PWMC_CH0 ) Channel Counter ثبات
/* - ========== Register definition for PWMC peripheral ========== */
                                                          AT91C_PWMC_IDR EQU( 0xFFFCC014 );
                                                          -( PWMC ) PWMC وقفه_2 Disable ثبات
                                                          AT91C_PWMC_DIS EQU( 0xFFFCC008 );
                                                          -( PWMC ) PWMC Disable ثبات
                                                          AT91C_PWMC_IER EQU( 0xFFFCC010 );
                                                          -( PWMC ) PWMC وقفه_2 Enable ثبات
                                                          AT91C_PWMC_VR EQU( 0xFFFCC0FC );
                                                          -( PWMC ) PWMC نسخه_2 ثبات
                                                          AT91C_PWMC_ISR EQU( 0xFFFCC01C );
                                                          -( PWMC ) PWMC وقفه_2 وضعیت ثبات
                                                          AT91C_PWMC_SR EQU( 0xFFFCC00C );
                                                          -( PWMC ) PWMC وضعیت ثبات
                                                          AT91C_PWMC_IMR EQU( 0xFFFCC018 );
                                                          -( PWMC ) PWMC وقفه_2 ماسک_2 ثبات
                                                          AT91C_PWMC_MR EQU( 0xFFFCC000 );
                                                          -( PWMC ) PWMC نما ثبات
                                                          AT91C_PWMC_ENA EQU( 0xFFFCC004 );
                                                          -( PWMC ) PWMC Enable ثبات
/* - ========== Register definition for UDP peripheral ========== */
                                                          AT91C_UDP_IMR EQU( 0xFFFB0018 );
                                                          -( UDP ) وقفه_2 ماسک_2 ثبات
                                                          AT91C_UDP_FADDR EQU( 0xFFFB0008 );
                                                          -( UDP ) Function آدرس ثبات
                                                          AT91_C_UDP_رقم EQU( 0xFFFB0000 );
                                                          -( UDP ) قاب عدد_2 ثبات
                                                          AT91C_UDP_FDR EQU( 0xFFFB0050 );
                                                          -( UDP ) Endpoint FIFO داده ثبات
                                                          AT91C_UDP_ISR EQU( 0xFFFB001C );
                                                          -( UDP ) وقفه_2 وضعیت ثبات
                                                          AT91C_UDP_CSR EQU( 0xFFFB0030 );
                                                          -( UDP ) Endpoint Control and وضعیت ثبات
                                                          AT91C_UDP_IDR EQU( 0xFFFB0014 );
                                                          -( UDP ) وقفه_2 Disable ثبات
                                                          AT91C_UDP_ICR EQU( 0xFFFB0020 );
                                                          -( UDP ) وقفه_2 Clear ثبات
                                                          AT91C_UDP_RSTEP EQU( 0xFFFB0028 );
                                                          -( UDP ) Reset Endpoint ثبات
                                                          AT91C_UDP_TXVC EQU( 0xFFFB0074 );
                                                          -( UDP ) Transceiver Control ثبات
                                                          AT91C_UDP_GLBSTATE EQU( 0xFFFB0004 );
                                                          -( UDP ) Global State ثبات
                                                          AT91C_UDP_IER EQU( 0xFFFB0010 );
                                                          -( UDP ) وقفه_2 Enable ثبات
/* - ========== Register definition for TC0 peripheral ========== */
                                                          AT91C_TC0_SR EQU( 0xFFFA0020 );
                                                          -( TC0 ) وضعیت ثبات
                                                          AT91C_TC0_RC EQU( 0xFFFA001C );
                                                          -( TC0 ) ثبات C
                                                          AT91C_TC0_RB EQU( 0xFFFA0018 );
                                                          -( TC0 ) ثبات B
                                                          AT91C_TC0_CCR EQU( 0xFFFA0000 );
                                                          -( TC0 ) Channel Control ثبات
                                                          AT91C_TC0_CMR EQU( 0xFFFA0004 );
                                                          -( TC0 ) Channel نما ثبات( Capture نما / Waveform نما )
                                                          AT91C_TC0_IER EQU( 0xFFFA0024 );
                                                          -( TC0 ) وقفه_2 Enable ثبات
                                                          AT91C_TC0_RA EQU( 0xFFFA0014 );
                                                          -( TC0 ) ثبات A
                                                          AT91C_TC0_IDR EQU( 0xFFFA0028 );
                                                          -( TC0 ) وقفه_2 Disable ثبات
                                                          AT91C_TC0_CV EQU( 0xFFFA0010 );
                                                          -( TC0 ) Counter مقدار_2
                                                          AT91C_TC0_IMR EQU( 0xFFFA002C );
                                                          -( TC0 ) وقفه_2 ماسک_2 ثبات
/* - ========== Register definition for TC1 peripheral ========== */
                                                          AT91C_TC1_RB EQU( 0xFFFA0058 );
                                                          -( TC1 ) ثبات B
                                                          AT91C_TC1_CCR EQU( 0xFFFA0040 );
                                                          -( TC1 ) Channel Control ثبات
                                                          AT91C_TC1_IER EQU( 0xFFFA0064 );
                                                          -( TC1 ) وقفه_2 Enable ثبات
                                                          AT91C_TC1_IDR EQU( 0xFFFA0068 );
                                                          -( TC1 ) وقفه_2 Disable ثبات
                                                          AT91C_TC1_SR EQU( 0xFFFA0060 );
                                                          -( TC1 ) وضعیت ثبات
                                                          AT91C_TC1_CMR EQU( 0xFFFA0044 );
                                                          -( TC1 ) Channel نما ثبات( Capture نما / Waveform نما )
                                                          AT91C_TC1_RA EQU( 0xFFFA0054 );
                                                          -( TC1 ) ثبات A
                                                          AT91C_TC1_RC EQU( 0xFFFA005C );
                                                          -( TC1 ) ثبات C
                                                          AT91C_TC1_IMR EQU( 0xFFFA006C );
                                                          -( TC1 ) وقفه_2 ماسک_2 ثبات
                                                          AT91C_TC1_CV EQU( 0xFFFA0050 );
                                                          -( TC1 ) Counter مقدار_2
/* - ========== Register definition for TC2 peripheral ========== */
                                                          AT91C_TC2_CMR EQU( 0xFFFA0084 );
                                                          -( TC2 ) Channel نما ثبات( Capture نما / Waveform نما )
                                                          AT91C_TC2_CCR EQU( 0xFFFA0080 );
                                                          -( TC2 ) Channel Control ثبات
                                                          AT91C_TC2_CV EQU( 0xFFFA0090 );
                                                          -( TC2 ) Counter مقدار_2
                                                          AT91C_TC2_RA EQU( 0xFFFA0094 );
                                                          -( TC2 ) ثبات A
                                                          AT91C_TC2_RB EQU( 0xFFFA0098 );
                                                          -( TC2 ) ثبات B
                                                          AT91C_TC2_IDR EQU( 0xFFFA00A8 );
                                                          -( TC2 ) وقفه_2 Disable ثبات
                                                          AT91C_TC2_IMR EQU( 0xFFFA00AC );
                                                          -( TC2 ) وقفه_2 ماسک_2 ثبات
                                                          AT91C_TC2_RC EQU( 0xFFFA009C );
                                                          -( TC2 ) ثبات C
                                                          AT91C_TC2_IER EQU( 0xFFFA00A4 );
                                                          -( TC2 ) وقفه_2 Enable ثبات
                                                          AT91C_TC2_SR EQU( 0xFFFA00A0 );
                                                          -( TC2 ) وضعیت ثبات
/* - ========== Register definition for TCB peripheral ========== */
                                                          AT91C_TCB_BMR EQU( 0xFFFA00C4 );
                                                          -( TCB ) TC بلوک نما ثبات
                                                          AT91C_TCB_BCR EQU( 0xFFFA00C0 );
                                                          -( TCB ) TC بلوک Control ثبات
/* - ========== Register definition for CAN_MB0 peripheral ========== */
                                                          AT91C_CAN_MB0_MDL EQU( 0xFFFD0214 );
                                                          -( CAN_MB0 ) MailBox داده کم ثبات
                                                          AT91C_CAN_MB0_MAM EQU( 0xFFFD0204 );
                                                          -( CAN_MB0 ) MailBox Acceptance ماسک_2 ثبات
                                                          AT91C_CAN_MB0_MCR EQU( 0xFFFD021C );
                                                          -( CAN_MB0 ) MailBox Control ثبات
                                                          AT91C_CAN_MB0_MID EQU( 0xFFFD0208 );
                                                          -( CAN_MB0 ) MailBox ID ثبات
                                                          AT91C_CAN_MB0_MSR EQU( 0xFFFD0210 );
                                                          -( CAN_MB0 ) MailBox وضعیت ثبات
                                                          AT91C_CAN_MB0_MFID EQU( 0xFFFD020C );
                                                          -( CAN_MB0 ) MailBox Family ID ثبات
                                                          AT91C_CAN_MB0_MDH EQU( 0xFFFD0218 );
                                                          -( CAN_MB0 ) MailBox داده بالا ثبات
                                                          AT91C_CAN_MB0_MMR EQU( 0xFFFD0200 );
                                                          -( CAN_MB0 ) MailBox نما ثبات
/* - ========== Register definition for CAN_MB1 peripheral ========== */
                                                          AT91C_CAN_MB1_MDL EQU( 0xFFFD0234 );
                                                          -( CAN_MB1 ) MailBox داده کم ثبات
                                                          AT91C_CAN_MB1_MID EQU( 0xFFFD0228 );
                                                          -( CAN_MB1 ) MailBox ID ثبات
                                                          AT91C_CAN_MB1_MMR EQU( 0xFFFD0220 );
                                                          -( CAN_MB1 ) MailBox نما ثبات
                                                          AT91C_CAN_MB1_MSR EQU( 0xFFFD0230 );
                                                          -( CAN_MB1 ) MailBox وضعیت ثبات
                                                          AT91C_CAN_MB1_MAM EQU( 0xFFFD0224 );
                                                          -( CAN_MB1 ) MailBox Acceptance ماسک_2 ثبات
                                                          AT91C_CAN_MB1_MDH EQU( 0xFFFD0238 );
                                                          -( CAN_MB1 ) MailBox داده بالا ثبات
                                                          AT91C_CAN_MB1_MCR EQU( 0xFFFD023C );
                                                          -( CAN_MB1 ) MailBox Control ثبات
                                                          AT91C_CAN_MB1_MFID EQU( 0xFFFD022C );
                                                          -( CAN_MB1 ) MailBox Family ID ثبات
/* - ========== Register definition for CAN_MB2 peripheral ========== */
                                                          AT91C_CAN_MB2_MCR EQU( 0xFFFD025C );
                                                          -( CAN_MB2 ) MailBox Control ثبات
                                                          AT91C_CAN_MB2_MDH EQU( 0xFFFD0258 );
                                                          -( CAN_MB2 ) MailBox داده بالا ثبات
                                                          AT91C_CAN_MB2_MID EQU( 0xFFFD0248 );
                                                          -( CAN_MB2 ) MailBox ID ثبات
                                                          AT91C_CAN_MB2_MDL EQU( 0xFFFD0254 );
                                                          -( CAN_MB2 ) MailBox داده کم ثبات
                                                          AT91C_CAN_MB2_MMR EQU( 0xFFFD0240 );
                                                          -( CAN_MB2 ) MailBox نما ثبات
                                                          AT91C_CAN_MB2_MAM EQU( 0xFFFD0244 );
                                                          -( CAN_MB2 ) MailBox Acceptance ماسک_2 ثبات
                                                          AT91C_CAN_MB2_MFID EQU( 0xFFFD024C );
                                                          -( CAN_MB2 ) MailBox Family ID ثبات
                                                          AT91C_CAN_MB2_MSR EQU( 0xFFFD0250 );
                                                          -( CAN_MB2 ) MailBox وضعیت ثبات
/* - ========== Register definition for CAN_MB3 peripheral ========== */
                                                          AT91C_CAN_MB3_MFID EQU( 0xFFFD026C );
                                                          -( CAN_MB3 ) MailBox Family ID ثبات
                                                          AT91C_CAN_MB3_MAM EQU( 0xFFFD0264 );
                                                          -( CAN_MB3 ) MailBox Acceptance ماسک_2 ثبات
                                                          AT91C_CAN_MB3_MID EQU( 0xFFFD0268 );
                                                          -( CAN_MB3 ) MailBox ID ثبات
                                                          AT91C_CAN_MB3_MCR EQU( 0xFFFD027C );
                                                          -( CAN_MB3 ) MailBox Control ثبات
                                                          AT91C_CAN_MB3_MMR EQU( 0xFFFD0260 );
                                                          -( CAN_MB3 ) MailBox نما ثبات
                                                          AT91C_CAN_MB3_MSR EQU( 0xFFFD0270 );
                                                          -( CAN_MB3 ) MailBox وضعیت ثبات
                                                          AT91C_CAN_MB3_MDL EQU( 0xFFFD0274 );
                                                          -( CAN_MB3 ) MailBox داده کم ثبات
                                                          AT91C_CAN_MB3_MDH EQU( 0xFFFD0278 );
                                                          -( CAN_MB3 ) MailBox داده بالا ثبات
/* - ========== Register definition for CAN_MB4 peripheral ========== */
                                                          AT91C_CAN_MB4_MID EQU( 0xFFFD0288 );
                                                          -( CAN_MB4 ) MailBox ID ثبات
                                                          AT91C_CAN_MB4_MMR EQU( 0xFFFD0280 );
                                                          -( CAN_MB4 ) MailBox نما ثبات
                                                          AT91C_CAN_MB4_MDH EQU( 0xFFFD0298 );
                                                          -( CAN_MB4 ) MailBox داده بالا ثبات
                                                          AT91C_CAN_MB4_MFID EQU( 0xFFFD028C );
                                                          -( CAN_MB4 ) MailBox Family ID ثبات
                                                          AT91C_CAN_MB4_MSR EQU( 0xFFFD0290 );
                                                          -( CAN_MB4 ) MailBox وضعیت ثبات
                                                          AT91C_CAN_MB4_MCR EQU( 0xFFFD029C );
                                                          -( CAN_MB4 ) MailBox Control ثبات
                                                          AT91C_CAN_MB4_MDL EQU( 0xFFFD0294 );
                                                          -( CAN_MB4 ) MailBox داده کم ثبات
                                                          AT91C_CAN_MB4_MAM EQU( 0xFFFD0284 );
                                                          -( CAN_MB4 ) MailBox Acceptance ماسک_2 ثبات
/* - ========== Register definition for CAN_MB5 peripheral ========== */
                                                          AT91C_CAN_MB5_MSR EQU( 0xFFFD02B0 );
                                                          -( CAN_MB5 ) MailBox وضعیت ثبات
                                                          AT91C_CAN_MB5_MCR EQU( 0xFFFD02BC );
                                                          -( CAN_MB5 ) MailBox Control ثبات
                                                          AT91C_CAN_MB5_MFID EQU( 0xFFFD02AC );
                                                          -( CAN_MB5 ) MailBox Family ID ثبات
                                                          AT91C_CAN_MB5_MDH EQU( 0xFFFD02B8 );
                                                          -( CAN_MB5 ) MailBox داده بالا ثبات
                                                          AT91C_CAN_MB5_MID EQU( 0xFFFD02A8 );
                                                          -( CAN_MB5 ) MailBox ID ثبات
                                                          AT91C_CAN_MB5_MMR EQU( 0xFFFD02A0 );
                                                          -( CAN_MB5 ) MailBox نما ثبات
                                                          AT91C_CAN_MB5_MDL EQU( 0xFFFD02B4 );
                                                          -( CAN_MB5 ) MailBox داده کم ثبات
                                                          AT91C_CAN_MB5_MAM EQU( 0xFFFD02A4 );
                                                          -( CAN_MB5 ) MailBox Acceptance ماسک_2 ثبات
/* - ========== Register definition for CAN_MB6 peripheral ========== */
                                                          AT91C_CAN_MB6_MFID EQU( 0xFFFD02CC );
                                                          -( CAN_MB6 ) MailBox Family ID ثبات
                                                          AT91C_CAN_MB6_MID EQU( 0xFFFD02C8 );
                                                          -( CAN_MB6 ) MailBox ID ثبات
                                                          AT91C_CAN_MB6_MAM EQU( 0xFFFD02C4 );
                                                          -( CAN_MB6 ) MailBox Acceptance ماسک_2 ثبات
                                                          AT91C_CAN_MB6_MSR EQU( 0xFFFD02D0 );
                                                          -( CAN_MB6 ) MailBox وضعیت ثبات
                                                          AT91C_CAN_MB6_MDL EQU( 0xFFFD02D4 );
                                                          -( CAN_MB6 ) MailBox داده کم ثبات
                                                          AT91C_CAN_MB6_MCR EQU( 0xFFFD02DC );
                                                          -( CAN_MB6 ) MailBox Control ثبات
                                                          AT91C_CAN_MB6_MDH EQU( 0xFFFD02D8 );
                                                          -( CAN_MB6 ) MailBox داده بالا ثبات
                                                          AT91C_CAN_MB6_MMR EQU( 0xFFFD02C0 );
                                                          -( CAN_MB6 ) MailBox نما ثبات
/* - ========== Register definition for CAN_MB7 peripheral ========== */
                                                          AT91C_CAN_MB7_MCR EQU( 0xFFFD02FC );
                                                          -( CAN_MB7 ) MailBox Control ثبات
                                                          AT91C_CAN_MB7_MDH EQU( 0xFFFD02F8 );
                                                          -( CAN_MB7 ) MailBox داده بالا ثبات
                                                          AT91C_CAN_MB7_MFID EQU( 0xFFFD02EC );
                                                          -( CAN_MB7 ) MailBox Family ID ثبات
                                                          AT91C_CAN_MB7_MDL EQU( 0xFFFD02F4 );
                                                          -( CAN_MB7 ) MailBox داده کم ثبات
                                                          AT91C_CAN_MB7_MID EQU( 0xFFFD02E8 );
                                                          -( CAN_MB7 ) MailBox ID ثبات
                                                          AT91C_CAN_MB7_MMR EQU( 0xFFFD02E0 );
                                                          -( CAN_MB7 ) MailBox نما ثبات
                                                          AT91C_CAN_MB7_MAM EQU( 0xFFFD02E4 );
                                                          -( CAN_MB7 ) MailBox Acceptance ماسک_2 ثبات
                                                          AT91C_CAN_MB7_MSR EQU( 0xFFFD02F0 );
                                                          -( CAN_MB7 ) MailBox وضعیت ثبات
/* - ========== Register definition for CAN peripheral ========== */
                                                          AT91C_CAN_TCR EQU( 0xFFFD0024 );
                                                          -( CAN ) Transfer Command ثبات
                                                          AT91C_CAN_IMR EQU( 0xFFFD000C );
                                                          -( CAN ) وقفه_2 ماسک_2 ثبات
                                                          AT91C_CAN_IER EQU( 0xFFFD0004 );
                                                          -( CAN ) وقفه_2 Enable ثبات
                                                          AT91C_CAN_ECR EQU( 0xFFFD0020 );
                                                          -( CAN ) Error Counter ثبات
                                                          AT91C_CAN_TIMESTP EQU( 0xFFFD001C );
                                                          -( CAN ) زمان Stamp ثبات
                                                          AT91C_CAN_MR EQU( 0xFFFD0000 );
                                                          -( CAN ) نما ثبات
                                                          AT91C_CAN_IDR EQU( 0xFFFD0008 );
                                                          -( CAN ) وقفه_2 Disable ثبات
                                                          AT91C_CAN_ACR EQU( 0xFFFD0028 );
                                                          -( CAN ) Abort Command ثبات
                                                          AT91C_CAN_TIM EQU( 0xFFFD0018 );
                                                          -( CAN ) Timer ثبات
                                                          AT91C_CAN_SR EQU( 0xFFFD0010 );
                                                          -( CAN ) وضعیت ثبات
                                                          AT91C_CAN_BR EQU( 0xFFFD0014 );
                                                          -( CAN ) Baudrate ثبات
                                                          AT91C_CAN_VR EQU( 0xFFFD00FC );
                                                          -( CAN ) نسخه_2 ثبات
/* - ========== Register definition for EMAC peripheral ========== */
                                                          AT91C_EMAC_ISR EQU( 0xFFFDC024 );
                                                          -( EMAC ) وقفه_2 وضعیت ثبات
                                                          AT91C_EMAC_SA4H EQU( 0xFFFDC0B4 );
                                                          -( EMAC ) Specific آدرس 4 بالاترین, آخرین 2 بایتها_2
                                                          AT91C_EMAC_SA1L EQU( 0xFFFDC098 );
                                                          -( EMAC ) Specific آدرس 1 Bottom, اولی 4 بایتها_2
                                                          AT91C_EMAC_ELE EQU( 0xFFFDC078 );
                                                          -( EMAC ) Excessive درازی Errors ثبات
                                                          AT91C_EMAC_LCOL EQU( 0xFFFDC05C );
                                                          -( EMAC ) Late Collision ثبات
                                                          AT91C_EMAC_RLE EQU( 0xFFFDC088 );
                                                          -( EMAC ) Receive درازی فیلد_2 Mismatch ثبات
                                                          AT91C_EMAC_WOL EQU( 0xFFFDC0C4 );
                                                          -( EMAC ) Wake On LAN ثبات
                                                          AT91C_EMAC_DTF EQU( 0xFFFDC058 );
                                                          -( EMAC ) Deferred ارسال قاب ثبات
                                                          AT91C_EMAC_TUND EQU( 0xFFFDC064 );
                                                          -( EMAC ) Transmit Underrun Error ثبات
                                                          AT91C_EMAC_NCR EQU( 0xFFFDC000 );
                                                          -( EMAC ) شبکه Control ثبات
                                                          AT91C_EMAC_SA4L EQU( 0xFFFDC0B0 );
                                                          -( EMAC ) Specific آدرس 4 Bottom, اولی 4 بایتها_2
                                                          AT91C_EMAC_RSR EQU( 0xFFFDC020 );
                                                          -( EMAC ) Receive وضعیت ثبات
                                                          AT91C_EMAC_SA3L EQU( 0xFFFDC0A8 );
                                                          -( EMAC ) Specific آدرس 3 Bottom, اولی 4 بایتها_2
                                                          AT91C_EMAC_TSR EQU( 0xFFFDC014 );
                                                          -( EMAC ) Transmit وضعیت ثبات
                                                          AT91C_EMAC_IDR EQU( 0xFFFDC02C );
                                                          -( EMAC ) وقفه_2 Disable ثبات
                                                          AT91C_EMAC_RSE EQU( 0xFFFDC074 );
                                                          -( EMAC ) Receive نماد Errors ثبات
                                                          AT91C_EMAC_ECOL EQU( 0xFFFDC060 );
                                                          -( EMAC ) Excessive Collision ثبات
                                                          AT91C_EMAC_TID EQU( 0xFFFDC0B8 );
                                                          -( EMAC ) Type ID Checking ثبات
                                                          AT91C_EMAC_HRB EQU( 0xFFFDC090 );
                                                          -( EMAC ) Hash آدرس Bottom[ 31 : 0 ]
                                                          AT91C_EMAC_TBQP EQU( 0xFFFDC01C );
                                                          -( EMAC ) Transmit میانگیر صف اشاره_گر
                                                          AT91C_EMAC_USRIO EQU( 0xFFFDC0C0 );
                                                          -( EMAC ) USER درون_داد / Output ثبات
                                                          AT91C_EMAC_PTR EQU( 0xFFFDC038 );
                                                          -( EMAC ) Pause زمان ثبات
                                                          AT91C_EMAC_SA2H EQU( 0xFFFDC0A4 );
                                                          -( EMAC ) Specific آدرس 2 بالاترین, آخرین 2 بایتها_2
                                                          AT91C_EMAC_ROV EQU( 0xFFFDC070 );
                                                          -( EMAC ) Receive Overrun Errors ثبات
                                                          AT91C_EMAC_ALE EQU( 0xFFFDC054 );
                                                          -( EMAC ) Alignment Error ثبات
                                                          AT91C_EMAC_RJA EQU( 0xFFFDC07C );
                                                          -( EMAC ) Receive Jabbers ثبات
                                                          AT91C_EMAC_RBQP EQU( 0xFFFDC018 );
                                                          -( EMAC ) Receive میانگیر صف اشاره_گر
                                                          AT91C_EMAC_TPF EQU( 0xFFFDC08C );
                                                          -( EMAC ) Transmitted Pause قابها ثبات
                                                          AT91C_EMAC_NCFGR EQU( 0xFFFDC004 );
                                                          -( EMAC ) شبکه Configuration ثبات
                                                          AT91C_EMAC_HRT EQU( 0xFFFDC094 );
                                                          -( EMAC ) Hash آدرس بالاترین[ 63 : 32 ]
                                                          AT91C_EMAC_USF EQU( 0xFFFDC080 );
                                                          -( EMAC ) Undersize قابها ثبات
                                                          AT91C_EMAC_FCSE EQU( 0xFFFDC050 );
                                                          -( EMAC ) قاب Check Sequence Error ثبات
                                                          AT91C_EMAC_TPQ EQU( 0xFFFDC0BC );
                                                          -( EMAC ) Transmit Pause برش_زمانی_2 ثبات
                                                          AT91C_EMAC_MAN EQU( 0xFFFDC034 );
                                                          -( EMAC ) PHY Maintenance ثبات
                                                          AT91C_EMAC_FTO EQU( 0xFFFDC040 );
                                                          -( EMAC ) قابها Transmitted OK ثبات
                                                          AT91C_EMAC_REV EQU( 0xFFFDC0FC );
                                                          -( EMAC ) Revision ثبات
                                                          AT91C_EMAC_IMR EQU( 0xFFFDC030 );
                                                          -( EMAC ) وقفه_2 ماسک_2 ثبات
                                                          AT91C_EMAC_SCF EQU( 0xFFFDC044 );
                                                          -( EMAC ) Single Collision قاب ثبات
                                                          AT91C_EMAC_PFR EQU( 0xFFFDC03C );
                                                          -( EMAC ) Pause قابها received ثبات
                                                          AT91C_EMAC_MCF EQU( 0xFFFDC048 );
                                                          -( EMAC ) مضرب Collision قاب ثبات
                                                          AT91C_EMAC_NSR EQU( 0xFFFDC008 );
                                                          -( EMAC ) شبکه وضعیت ثبات
                                                          AT91C_EMAC_SA2L EQU( 0xFFFDC0A0 );
                                                          -( EMAC ) Specific آدرس 2 Bottom, اولی 4 بایتها_2
                                                          AT91C_EMAC_FRO EQU( 0xFFFDC04C );
                                                          -( EMAC ) قابها Received OK ثبات
                                                          AT91C_EMAC_IER EQU( 0xFFFDC028 );
                                                          -( EMAC ) وقفه_2 Enable ثبات
                                                          AT91C_EMAC_SA1H EQU( 0xFFFDC09C );
                                                          -( EMAC ) Specific آدرس 1 بالاترین, آخرین 2 بایتها_2
                                                          AT91C_EMAC_CSE EQU( 0xFFFDC068 );
                                                          -( EMAC ) Carrier Sense Error ثبات
                                                          AT91C_EMAC_SA3H EQU( 0xFFFDC0AC );
                                                          -( EMAC ) Specific آدرس 3 بالاترین, آخرین 2 بایتها_2
                                                          AT91C_EMAC_RRE EQU( 0xFFFDC06C );
                                                          -( EMAC ) Receive Resource Error ثبات
                                                          AT91C_EMAC_STE EQU( 0xFFFDC084 );
                                                          -( EMAC ) SQE Test Error ثبات
/* - ========== Register definition for PDC_ADC peripheral ========== */
                                                          AT91C_ADC_PTSR EQU( 0xFFFD8124 );
                                                          -( PDC_ADC ) PDC Transfer وضعیت ثبات
                                                          AT91C_ADC_PTCR EQU( 0xFFFD8120 );
                                                          -( PDC_ADC ) PDC Transfer Control ثبات
                                                          AT91C_ADC_TNPR EQU( 0xFFFD8118 );
                                                          -( PDC_ADC ) Transmit بعدی اشاره_گر ثبات
                                                          AT91C_ADC_TNCR EQU( 0xFFFD811C );
                                                          -( PDC_ADC ) Transmit بعدی Counter ثبات
                                                          AT91C_ADC_RNPR EQU( 0xFFFD8110 );
                                                          -( PDC_ADC ) Receive بعدی اشاره_گر ثبات
                                                          AT91C_ADC_RNCR EQU( 0xFFFD8114 );
                                                          -( PDC_ADC ) Receive بعدی Counter ثبات
                                                          AT91C_ADC_RPR EQU( 0xFFFD8100 );
                                                          -( PDC_ADC ) Receive اشاره_گر ثبات
                                                          AT91C_ADC_TCR EQU( 0xFFFD810C );
                                                          -( PDC_ADC ) Transmit Counter ثبات
                                                          AT91C_ADC_TPR EQU( 0xFFFD8108 );
                                                          -( PDC_ADC ) Transmit اشاره_گر ثبات
                                                          AT91C_ADC_RCR EQU( 0xFFFD8104 );
                                                          -( PDC_ADC ) Receive Counter ثبات
/* - ========== Register definition for ADC peripheral ========== */
                                                          AT91C_ADC_CDR2 EQU( 0xFFFD8038 );
                                                          -( ADC ) ADC Channel داده ثبات 2
                                                          AT91C_ADC_CDR3 EQU( 0xFFFD803C );
                                                          -( ADC ) ADC Channel داده ثبات 3
                                                          AT91C_ADC_CDR0 EQU( 0xFFFD8030 );
                                                          -( ADC ) ADC Channel داده ثبات 0
                                                          AT91C_ADC_CDR5 EQU( 0xFFFD8044 );
                                                          -( ADC ) ADC Channel داده ثبات 5
                                                          AT91C_ADC_CHDR EQU( 0xFFFD8014 );
                                                          -( ADC ) ADC Channel Disable ثبات
                                                          AT91C_ADC_SR EQU( 0xFFFD801C );
                                                          -( ADC ) ADC وضعیت ثبات
                                                          AT91C_ADC_CDR4 EQU( 0xFFFD8040 );
                                                          -( ADC ) ADC Channel داده ثبات 4
                                                          AT91C_ADC_CDR1 EQU( 0xFFFD8034 );
                                                          -( ADC ) ADC Channel داده ثبات 1
                                                          AT91C_ADC_LCDR EQU( 0xFFFD8020 );
                                                          -( ADC ) ADC آخرین Converted داده ثبات
                                                          AT91C_ADC_IDR EQU( 0xFFFD8028 );
                                                          -( ADC ) ADC وقفه_2 Disable ثبات
                                                          AT91C_ADC_CR EQU( 0xFFFD8000 );
                                                          -( ADC ) ADC Control ثبات
                                                          AT91C_ADC_CDR7 EQU( 0xFFFD804C );
                                                          -( ADC ) ADC Channel داده ثبات 7
                                                          AT91C_ADC_CDR6 EQU( 0xFFFD8048 );
                                                          -( ADC ) ADC Channel داده ثبات 6
                                                          AT91C_ADC_IER EQU( 0xFFFD8024 );
                                                          -( ADC ) ADC وقفه_2 Enable ثبات
                                                          AT91C_ADC_CHER EQU( 0xFFFD8010 );
                                                          -( ADC ) ADC Channel Enable ثبات
                                                          AT91C_ADC_CHSR EQU( 0xFFFD8018 );
                                                          -( ADC ) ADC Channel وضعیت ثبات
                                                          AT91C_ADC_MR EQU( 0xFFFD8004 );
                                                          -( ADC ) ADC نما ثبات
                                                          AT91C_ADC_IMR EQU( 0xFFFD802C );
                                                          -( ADC ) ADC وقفه_2 ماسک_2 ثبات
/* - ========== Register definition for PDC_AES peripheral ========== */
                                                          AT91C_AES_TPR EQU( 0xFFFA4108 );
                                                          -( PDC_AES ) Transmit اشاره_گر ثبات
                                                          AT91C_AES_PTCR EQU( 0xFFFA4120 );
                                                          -( PDC_AES ) PDC Transfer Control ثبات
                                                          AT91C_AES_RNPR EQU( 0xFFFA4110 );
                                                          -( PDC_AES ) Receive بعدی اشاره_گر ثبات
                                                          AT91C_AES_TNCR EQU( 0xFFFA411C );
                                                          -( PDC_AES ) Transmit بعدی Counter ثبات
                                                          AT91C_AES_TCR EQU( 0xFFFA410C );
                                                          -( PDC_AES ) Transmit Counter ثبات
                                                          AT91C_AES_RCR EQU( 0xFFFA4104 );
                                                          -( PDC_AES ) Receive Counter ثبات
                                                          AT91C_AES_RNCR EQU( 0xFFFA4114 );
                                                          -( PDC_AES ) Receive بعدی Counter ثبات
                                                          AT91C_AES_TNPR EQU( 0xFFFA4118 );
                                                          -( PDC_AES ) Transmit بعدی اشاره_گر ثبات
                                                          AT91C_AES_RPR EQU( 0xFFFA4100 );
                                                          -( PDC_AES ) Receive اشاره_گر ثبات
                                                          AT91C_AES_PTSR EQU( 0xFFFA4124 );
                                                          -( PDC_AES ) PDC Transfer وضعیت ثبات
/* - ========== Register definition for AES peripheral ========== */
                                                          AT91C_AES_IVxR EQU( 0xFFFA4060 );
                                                          -( AES ) Initialization وکتور_2 x ثبات
                                                          AT91C_AES_MR EQU( 0xFFFA4004 );
                                                          -( AES ) نما ثبات
                                                          AT91C_AES_VR EQU( 0xFFFA40FC );
                                                          -( AES ) AES نسخه_2 ثبات
                                                          AT91C_AES_ODATAxR EQU( 0xFFFA4050 );
                                                          -( AES ) Output داده x ثبات
                                                          AT91C_AES_IDATAxR EQU( 0xFFFA4040 );
                                                          -( AES ) درون_داد داده x ثبات
                                                          AT91C_AES_CR EQU( 0xFFFA4000 );
                                                          -( AES ) Control ثبات
                                                          AT91C_AES_IDR EQU( 0xFFFA4014 );
                                                          -( AES ) وقفه_2 Disable ثبات
                                                          AT91C_AES_IMR EQU( 0xFFFA4018 );
                                                          -( AES ) وقفه_2 ماسک_2 ثبات
                                                          AT91C_AES_IER EQU( 0xFFFA4010 );
                                                          -( AES ) وقفه_2 Enable ثبات
                                                          AT91C_AES_KEYWxR EQU( 0xFFFA4020 );
                                                          -( AES ) کلید_2 کلمه_2 x ثبات
                                                          AT91C_AES_ISR EQU( 0xFFFA401C );
                                                          -( AES ) وقفه_2 وضعیت ثبات
/* - ========== Register definition for PDC_TDES peripheral ========== */
                                                          AT91C_TDES_RNCR EQU( 0xFFFA8114 );
                                                          -( PDC_TDES ) Receive بعدی Counter ثبات
                                                          AT91C_TDES_TCR EQU( 0xFFFA810C );
                                                          -( PDC_TDES ) Transmit Counter ثبات
                                                          AT91C_TDES_RCR EQU( 0xFFFA8104 );
                                                          -( PDC_TDES ) Receive Counter ثبات
                                                          AT91C_TDES_TNPR EQU( 0xFFFA8118 );
                                                          -( PDC_TDES ) Transmit بعدی اشاره_گر ثبات
                                                          AT91C_TDES_RNPR EQU( 0xFFFA8110 );
                                                          -( PDC_TDES ) Receive بعدی اشاره_گر ثبات
                                                          AT91C_TDES_RPR EQU( 0xFFFA8100 );
                                                          -( PDC_TDES ) Receive اشاره_گر ثبات
                                                          AT91C_TDES_TNCR EQU( 0xFFFA811C );
                                                          -( PDC_TDES ) Transmit بعدی Counter ثبات
                                                          AT91C_TDES_TPR EQU( 0xFFFA8108 );
                                                          -( PDC_TDES ) Transmit اشاره_گر ثبات
                                                          AT91C_TDES_PTSR EQU( 0xFFFA8124 );
                                                          -( PDC_TDES ) PDC Transfer وضعیت ثبات
                                                          AT91C_TDES_PTCR EQU( 0xFFFA8120 );
                                                          -( PDC_TDES ) PDC Transfer Control ثبات
/* - ========== Register definition for TDES peripheral ========== */
                                                          AT91C_TDES_KEY2WxR EQU( 0xFFFA8028 );
                                                          -( TDES ) کلید_2 2 کلمه_2 x ثبات
                                                          AT91C_TDES_KEY3WxR EQU( 0xFFFA8030 );
                                                          -( TDES ) کلید_2 3 کلمه_2 x ثبات
                                                          AT91C_TDES_IDR EQU( 0xFFFA8014 );
                                                          -( TDES ) وقفه_2 Disable ثبات
                                                          AT91C_TDES_VR EQU( 0xFFFA80FC );
                                                          -( TDES ) TDES نسخه_2 ثبات
                                                          AT91C_TDES_IVxR EQU( 0xFFFA8060 );
                                                          -( TDES ) Initialization وکتور_2 x ثبات
                                                          AT91C_TDES_ODATAxR EQU( 0xFFFA8050 );
                                                          -( TDES ) Output داده x ثبات
                                                          AT91C_TDES_IMR EQU( 0xFFFA8018 );
                                                          -( TDES ) وقفه_2 ماسک_2 ثبات
                                                          AT91C_TDES_MR EQU( 0xFFFA8004 );
                                                          -( TDES ) نما ثبات
                                                          AT91C_TDES_CR EQU( 0xFFFA8000 );
                                                          -( TDES ) Control ثبات
                                                          AT91C_TDES_IER EQU( 0xFFFA8010 );
                                                          -( TDES ) وقفه_2 Enable ثبات
                                                          AT91C_TDES_ISR EQU( 0xFFFA801C );
                                                          -( TDES ) وقفه_2 وضعیت ثبات
                                                          AT91C_TDES_IDATAxR EQU( 0xFFFA8040 );
                                                          -( TDES ) درون_داد داده x ثبات
                                                          AT91C_TDES_KEY1WxR EQU( 0xFFFA8020 );
                                                          -( TDES ) کلید_2 1 کلمه_2 x ثبات

/* - ***************************************************************************** */
/* -               PIO DEFINITIONS FOR AT91SAM7X256 */
/* - ***************************************************************************** */
                                                          AT91C_PIO_PA0 EQU( 1 << 0 );
                                                          -Pin Controlled by PA0
                                                          AT91C_PA0_RXD0 EQU( AT91C_PIO_PA0 );
                                                          -USART 0 Receive داده
                                                          AT91C_PIO_PA1 EQU( 1 << 1 );
                                                          -Pin Controlled by PA1
                                                          AT91C_PA1_TXD0 EQU( AT91C_PIO_PA1 );
                                                          -USART 0 Transmit داده
                                                          AT91C_PIO_PA10 EQU( 1 << 10 );
                                                          -Pin Controlled by PA10
                                                          AT91C_PA10_TWD EQU( AT91C_PIO_PA10 );
                                                          -TWI Two - wire Serial داده
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
                                                          -External وقفه_2 1
                                                          AT91C_PIO_PA15 EQU( 1 << 15 );
                                                          -Pin Controlled by PA15
                                                          AT91C_PA15_NPCS03 EQU( AT91C_PIO_PA15 );
                                                          -SPI 0 Peripheral Chip Select 3
                                                          AT91C_PA15_TCLK2 EQU( AT91C_PIO_PA15 );
                                                          -Timer Counter 2 external clock درون_داد_2
                                                          AT91C_PIO_PA16 EQU( 1 << 16 );
                                                          -Pin Controlled by PA16
                                                          AT91C_PA16_MISO0 EQU( AT91C_PIO_PA16 );
                                                          -SPI 0 Master درون_3 Slave
                                                          AT91C_PIO_PA17 EQU( 1 << 17 );
                                                          -Pin Controlled by PA17
                                                          AT91C_PA17_MOSI0 EQU( AT91C_PIO_PA17 );
                                                          -SPI 0 Master بیرون_3 Slave
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
                                                          -SSC Transmit قاب Sync
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
                                                          -SSC Transmit داده_2
                                                          AT91C_PA23_MOSI1 EQU( AT91C_PIO_PA23 );
                                                          -SPI 1 Master بیرون_3 Slave
                                                          AT91C_PIO_PA24 EQU( 1 << 24 );
                                                          -Pin Controlled by PA24
                                                          AT91C_PA24_RD EQU( AT91C_PIO_PA24 );
                                                          -SSC Receive داده
                                                          AT91C_PA24_MISO1 EQU( AT91C_PIO_PA24 );
                                                          -SPI 1 Master درون_3 Slave
                                                          AT91C_PIO_PA25 EQU( 1 << 25 );
                                                          -Pin Controlled by PA25
                                                          AT91C_PA25_RK EQU( AT91C_PIO_PA25 );
                                                          -SSC Receive Clock
                                                          AT91C_PA25_NPCS11 EQU( AT91C_PIO_PA25 );
                                                          -SPI 1 Peripheral Chip Select 1
                                                          AT91C_PIO_PA26 EQU( 1 << 26 );
                                                          -Pin Controlled by PA26
                                                          AT91C_PA26_RF EQU( AT91C_PIO_PA26 );
                                                          -SSC Receive قاب Sync
                                                          AT91C_PA26_NPCS12 EQU( AT91C_PIO_PA26 );
                                                          -SPI 1 Peripheral Chip Select 2
                                                          AT91C_PIO_PA27 EQU( 1 << 27 );
                                                          -Pin Controlled by PA27
                                                          AT91C_PA27_DRXD EQU( AT91C_PIO_PA27 );
                                                          -DBGU Debug Receive داده
                                                          AT91C_PA27_PCK3 EQU( AT91C_PIO_PA27 );
                                                          -PMC Programmable Clock Output 3
                                                          AT91C_PIO_PA28 EQU( 1 << 28 );
                                                          -Pin Controlled by PA28
                                                          AT91C_PA28_DTXD EQU( AT91C_PIO_PA28 );
                                                          -DBGU Debug Transmit داده
                                                          AT91C_PIO_PA29 EQU( 1 << 29 );
                                                          -Pin Controlled by PA29
                                                          AT91C_PA29_FIQ EQU( AT91C_PIO_PA29 );
                                                          -AIC Fast وقفه_2 درون_داد
                                                          AT91C_PA29_NPCS13 EQU( AT91C_PIO_PA29 );
                                                          -SPI 1 Peripheral Chip Select 3
                                                          AT91C_PIO_PA3 EQU( 1 << 3 );
                                                          -Pin Controlled by PA3
                                                          AT91C_PA3_RTS0 EQU( AT91C_PIO_PA3 );
                                                          -USART 0 Ready مقصد_2 Send
                                                          AT91C_PA3_NPCS12 EQU( AT91C_PIO_PA3 );
                                                          -SPI 1 Peripheral Chip Select 2
                                                          AT91C_PIO_PA30 EQU( 1 << 30 );
                                                          -Pin Controlled by PA30
                                                          AT91C_PA30_IRQ0 EQU( AT91C_PIO_PA30 );
                                                          -External وقفه_2 0
                                                          AT91C_PA30_PCK2 EQU( AT91C_PIO_PA30 );
                                                          -PMC Programmable Clock Output 2
                                                          AT91C_PIO_PA4 EQU( 1 << 4 );
                                                          -Pin Controlled by PA4
                                                          AT91C_PA4_CTS0 EQU( AT91C_PIO_PA4 );
                                                          -USART 0 Clear مقصد_2 Send
                                                          AT91C_PA4_NPCS13 EQU( AT91C_PIO_PA4 );
                                                          -SPI 1 Peripheral Chip Select 3
                                                          AT91C_PIO_PA5 EQU( 1 << 5 );
                                                          -Pin Controlled by PA5
                                                          AT91C_PA5_RXD1 EQU( AT91C_PIO_PA5 );
                                                          -USART 1 Receive داده
                                                          AT91C_PIO_PA6 EQU( 1 << 6 );
                                                          -Pin Controlled by PA6
                                                          AT91C_PA6_TXD1 EQU( AT91C_PIO_PA6 );
                                                          -USART 1 Transmit داده
                                                          AT91C_PIO_PA7 EQU( 1 << 7 );
                                                          -Pin Controlled by PA7
                                                          AT91C_PA7_SCK1 EQU( AT91C_PIO_PA7 );
                                                          -USART 1 Serial Clock
                                                          AT91C_PA7_NPCS01 EQU( AT91C_PIO_PA7 );
                                                          -SPI 0 Peripheral Chip Select 1
                                                          AT91C_PIO_PA8 EQU( 1 << 8 );
                                                          -Pin Controlled by PA8
                                                          AT91C_PA8_RTS1 EQU( AT91C_PIO_PA8 );
                                                          -USART 1 Ready مقصد_2 Send
                                                          AT91C_PA8_NPCS02 EQU( AT91C_PIO_PA8 );
                                                          -SPI 0 Peripheral Chip Select 2
                                                          AT91C_PIO_PA9 EQU( 1 << 9 );
                                                          -Pin Controlled by PA9
                                                          AT91C_PA9_CTS1 EQU( AT91C_PIO_PA9 );
                                                          -USART 1 Clear مقصد_2 Send
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
                                                          -Ethernet MAC Transmit داده 2
                                                          AT91C_PB10_NPCS11 EQU( AT91C_PIO_PB10 );
                                                          -SPI 1 Peripheral Chip Select 1
                                                          AT91C_PIO_PB11 EQU( 1 << 11 );
                                                          -Pin Controlled by PB11
                                                          AT91C_PB11_ETX3 EQU( AT91C_PIO_PB11 );
                                                          -Ethernet MAC Transmit داده 3
                                                          AT91C_PB11_NPCS12 EQU( AT91C_PIO_PB11 );
                                                          -SPI 1 Peripheral Chip Select 2
                                                          AT91C_PIO_PB12 EQU( 1 << 12 );
                                                          -Pin Controlled by PB12
                                                          AT91C_PB12_ETXER EQU( AT91C_PIO_PB12 );
                                                          -Ethernet MAC Transmit Coding Error
                                                          AT91C_PB12_TCLK0 EQU( AT91C_PIO_PB12 );
                                                          -Timer Counter 0 external clock درون_داد_2
                                                          AT91C_PIO_PB13 EQU( 1 << 13 );
                                                          -Pin Controlled by PB13
                                                          AT91C_PB13_ERX2 EQU( AT91C_PIO_PB13 );
                                                          -Ethernet MAC Receive داده 2
                                                          AT91C_PB13_NPCS01 EQU( AT91C_PIO_PB13 );
                                                          -SPI 0 Peripheral Chip Select 1
                                                          AT91C_PIO_PB14 EQU( 1 << 14 );
                                                          -Pin Controlled by PB14
                                                          AT91C_PB14_ERX3 EQU( AT91C_PIO_PB14 );
                                                          -Ethernet MAC Receive داده 3
                                                          AT91C_PB14_NPCS02 EQU( AT91C_PIO_PB14 );
                                                          -SPI 0 Peripheral Chip Select 2
                                                          AT91C_PIO_PB15 EQU( 1 << 15 );
                                                          -Pin Controlled by PB15
                                                          AT91C_PB15_ERXDV EQU( AT91C_PIO_PB15 );
                                                          -Ethernet MAC Receive داده Valid
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
                                                          -Timer Counter 1 external clock درون_داد_2
                                                          AT91C_PIO_PB2 EQU( 1 << 2 );
                                                          -Pin Controlled by PB2
                                                          AT91C_PB2_ETX0 EQU( AT91C_PIO_PB2 );
                                                          -Ethernet MAC Transmit داده 0
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
                                                          -USART 1 داده Carrier Detect
                                                          AT91C_PIO_PB24 EQU( 1 << 24 );
                                                          -Pin Controlled by PB24
                                                          AT91C_PB24_TIOB0 EQU( AT91C_PIO_PB24 );
                                                          -Timer Counter 0 Multipurpose Timer I / O Pin B
                                                          AT91C_PB24_DSR1 EQU( AT91C_PIO_PB24 );
                                                          -USART 1 داده مجموعه_2 ready
                                                          AT91C_PIO_PB25 EQU( 1 << 25 );
                                                          -Pin Controlled by PB25
                                                          AT91C_PB25_TIOA1 EQU( AT91C_PIO_PB25 );
                                                          -Timer Counter 1 Multipurpose Timer I / O Pin A
                                                          AT91C_PB25_DTR1 EQU( AT91C_PIO_PB25 );
                                                          -USART 1 داده Terminal ready
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
                                                          -Ethernet MAC Transmit داده 1
                                                          AT91C_PIO_PB30 EQU( 1 << 30 );
                                                          -Pin Controlled by PB30
                                                          AT91C_PB30_PCK2 EQU( AT91C_PIO_PB30 );
                                                          -PMC Programmable Clock Output 2
                                                          AT91C_PB30_PWM3 EQU( AT91C_PIO_PB30 );
                                                          -PWM Channel 3
                                                          AT91C_PIO_PB4 EQU( 1 << 4 );
                                                          -Pin Controlled by PB4
                                                          AT91C_PB4_ECRS_ECRSDV EQU( AT91C_PIO_PB4 );
                                                          -Ethernet MAC Carrier Sense / Carrier Sense and داده Valid
                                                          AT91C_PIO_PB5 EQU( 1 << 5 );
                                                          -Pin Controlled by PB5
                                                          AT91C_PB5_ERX0 EQU( AT91C_PIO_PB5 );
                                                          -Ethernet MAC Receive داده 0
                                                          AT91C_PIO_PB6 EQU( 1 << 6 );
                                                          -Pin Controlled by PB6
                                                          AT91C_PB6_ERX1 EQU( AT91C_PIO_PB6 );
                                                          -Ethernet MAC Receive داده 1
                                                          AT91C_PIO_PB7 EQU( 1 << 7 );
                                                          -Pin Controlled by PB7
                                                          AT91C_PB7_ERXER EQU( AT91C_PIO_PB7 );
                                                          -Ethernet MAC Receive Error
                                                          AT91C_PIO_PB8 EQU( 1 << 8 );
                                                          -Pin Controlled by PB8
                                                          AT91C_PB8_EMDC EQU( AT91C_PIO_PB8 );
                                                          -Ethernet MAC Management داده Clock
                                                          AT91C_PIO_PB9 EQU( 1 << 9 );
                                                          -Pin Controlled by PB9
                                                          AT91C_PB9_EMDIO EQU( AT91C_PIO_PB9 );
                                                          -Ethernet MAC Management داده درون_داد / Output

/* - ***************************************************************************** */
/* -               PERIPHERAL ID DEFINITIONS FOR AT91SAM7X256 */
/* - ***************************************************************************** */
                                                          AT91C_ID_FIQ EQU( 0 );
                                                          -Advanced وقفه_2 Controller( FIQ )
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
                                                          -USB Device پورت_2
                                                          AT91C_ID_TC0 EQU( 12 );
                                                          -Timer Counter 0
                                                          AT91C_ID_TC1 EQU( 13 );
                                                          -Timer Counter 1
                                                          AT91C_ID_TC2 EQU( 14 );
                                                          -Timer Counter 2
                                                          AT91C_ID_CAN EQU( 15 );
                                                          -Control Area شبکه Controller
                                                          AT91C_ID_EMAC EQU( 16 );
                                                          -Ethernet MAC
                                                          AT91C_ID_ADC EQU( 17 );
                                                          -Analog - مقصد - Digital Converter
                                                          AT91C_ID_AES EQU( 18 );
                                                          -Advanced Encryption Standard 128 - بیت_2
                                                          AT91C_ID_TDES EQU( 19 );
                                                          -Triple داده Encryption Standard
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
                                                          -Advanced وقفه_2 Controller( IRQ0 )
                                                          AT91C_ID_IRQ1 EQU( 31 );
                                                          -Advanced وقفه_2 Controller( IRQ1 )

/* - ***************************************************************************** */
/* -               BASE ADDRESS DEFINITIONS FOR AT91SAM7X256 */
/* - ***************************************************************************** */
                                                          AT91_C_پایه_SYS EQU( 0xFFFFF000 );
                                                          -( SYS ) پایه_2 آدرس
                                                          AT91_C_پایه_AIC EQU( 0xFFFFF000 );
                                                          -( AIC ) پایه_2 آدرس
                                                          AT91_C_پایه_PDC_DBGU EQU( 0xFFFFF300 );
                                                          -( PDC_DBGU ) پایه_2 آدرس
                                                          AT91_C_پایه_DBGU EQU( 0xFFFFF200 );
                                                          -( DBGU ) پایه_2 آدرس
                                                          AT91_C_پایه_PIOA EQU( 0xFFFFF400 );
                                                          -( PIOA ) پایه_2 آدرس
                                                          AT91_C_پایه_PIOB EQU( 0xFFFFF600 );
                                                          -( PIOB ) پایه_2 آدرس
                                                          AT91_C_پایه_CKGR EQU( 0xFFFFFC20 );
                                                          -( CKGR ) پایه_2 آدرس
                                                          AT91_C_پایه_PMC EQU( 0xFFFFFC00 );
                                                          -( PMC ) پایه_2 آدرس
                                                          AT91_C_پایه_RSTC EQU( 0xFFFFFD00 );
                                                          -( RSTC ) پایه_2 آدرس
                                                          AT91_C_پایه_RTTC EQU( 0xFFFFFD20 );
                                                          -( RTTC ) پایه_2 آدرس
                                                          AT91_C_پایه_PITC EQU( 0xFFFFFD30 );
                                                          -( PITC ) پایه_2 آدرس
                                                          AT91_C_پایه_WDTC EQU( 0xFFFFFD40 );
                                                          -( WDTC ) پایه_2 آدرس
                                                          AT91_C_پایه_VREG EQU( 0xFFFFFD60 );
                                                          -( VREG ) پایه_2 آدرس
                                                          AT91_C_پایه_MC EQU( 0xFFFFFF00 );
                                                          -( MC ) پایه_2 آدرس
                                                          AT91_C_پایه_PDC_SPI1 EQU( 0xFFFE4100 );
                                                          -( PDC_SPI1 ) پایه_2 آدرس
                                                          AT91_C_پایه_SPI1 EQU( 0xFFFE4000 );
                                                          -( SPI1 ) پایه_2 آدرس
                                                          AT91_C_پایه_PDC_SPI0 EQU( 0xFFFE0100 );
                                                          -( PDC_SPI0 ) پایه_2 آدرس
                                                          AT91_C_پایه_SPI0 EQU( 0xFFFE0000 );
                                                          -( SPI0 ) پایه_2 آدرس
                                                          AT91_C_پایه_PDC_US1 EQU( 0xFFFC4100 );
                                                          -( PDC_US1 ) پایه_2 آدرس
                                                          AT91_C_پایه_US1 EQU( 0xFFFC4000 );
                                                          -( US1 ) پایه_2 آدرس
                                                          AT91_C_پایه_PDC_US0 EQU( 0xFFFC0100 );
                                                          -( PDC_US0 ) پایه_2 آدرس
                                                          AT91_C_پایه_US0 EQU( 0xFFFC0000 );
                                                          -( US0 ) پایه_2 آدرس
                                                          AT91_C_پایه_PDC_SSC EQU( 0xFFFD4100 );
                                                          -( PDC_SSC ) پایه_2 آدرس
                                                          AT91_C_پایه_SSC EQU( 0xFFFD4000 );
                                                          -( SSC ) پایه_2 آدرس
                                                          AT91_C_پایه_TWI EQU( 0xFFFB8000 );
                                                          -( TWI ) پایه_2 آدرس
                                                          AT91_C_پایه_PWMC_CH3 EQU( 0xFFFCC260 );
                                                          -( PWMC_CH3 ) پایه_2 آدرس
                                                          AT91_C_پایه_PWMC_CH2 EQU( 0xFFFCC240 );
                                                          -( PWMC_CH2 ) پایه_2 آدرس
                                                          AT91_C_پایه_PWMC_CH1 EQU( 0xFFFCC220 );
                                                          -( PWMC_CH1 ) پایه_2 آدرس
                                                          AT91_C_پایه_PWMC_CH0 EQU( 0xFFFCC200 );
                                                          -( PWMC_CH0 ) پایه_2 آدرس
                                                          AT91_C_پایه_PWMC EQU( 0xFFFCC000 );
                                                          -( PWMC ) پایه_2 آدرس
                                                          AT91_C_پایه_UDP EQU( 0xFFFB0000 );
                                                          -( UDP ) پایه_2 آدرس
                                                          AT91_C_پایه_TC0 EQU( 0xFFFA0000 );
                                                          -( TC0 ) پایه_2 آدرس
                                                          AT91_C_پایه_TC1 EQU( 0xFFFA0040 );
                                                          -( TC1 ) پایه_2 آدرس
                                                          AT91_C_پایه_TC2 EQU( 0xFFFA0080 );
                                                          -( TC2 ) پایه_2 آدرس
                                                          AT91_C_پایه_TCB EQU( 0xFFFA0000 );
                                                          -( TCB ) پایه_2 آدرس
                                                          AT91_C_پایه_CAN_MB0 EQU( 0xFFFD0200 );
                                                          -( CAN_MB0 ) پایه_2 آدرس
                                                          AT91_C_پایه_CAN_MB1 EQU( 0xFFFD0220 );
                                                          -( CAN_MB1 ) پایه_2 آدرس
                                                          AT91_C_پایه_CAN_MB2 EQU( 0xFFFD0240 );
                                                          -( CAN_MB2 ) پایه_2 آدرس
                                                          AT91_C_پایه_CAN_MB3 EQU( 0xFFFD0260 );
                                                          -( CAN_MB3 ) پایه_2 آدرس
                                                          AT91_C_پایه_CAN_MB4 EQU( 0xFFFD0280 );
                                                          -( CAN_MB4 ) پایه_2 آدرس
                                                          AT91_C_پایه_CAN_MB5 EQU( 0xFFFD02A0 );
                                                          -( CAN_MB5 ) پایه_2 آدرس
                                                          AT91_C_پایه_CAN_MB6 EQU( 0xFFFD02C0 );
                                                          -( CAN_MB6 ) پایه_2 آدرس
                                                          AT91_C_پایه_CAN_MB7 EQU( 0xFFFD02E0 );
                                                          -( CAN_MB7 ) پایه_2 آدرس
                                                          AT91_C_پایه_CAN EQU( 0xFFFD0000 );
                                                          -( CAN ) پایه_2 آدرس
                                                          AT91_C_پایه_EMAC EQU( 0xFFFDC000 );
                                                          -( EMAC ) پایه_2 آدرس
                                                          AT91_C_پایه_PDC_ADC EQU( 0xFFFD8100 );
                                                          -( PDC_ADC ) پایه_2 آدرس
                                                          AT91_C_پایه_ADC EQU( 0xFFFD8000 );
                                                          -( ADC ) پایه_2 آدرس
                                                          AT91_C_پایه_PDC_AES EQU( 0xFFFA4100 );
                                                          -( PDC_AES ) پایه_2 آدرس
                                                          AT91_C_پایه_AES EQU( 0xFFFA4000 );
                                                          -( AES ) پایه_2 آدرس
                                                          AT91_C_پایه_PDC_TDES EQU( 0xFFFA8100 );
                                                          -( PDC_TDES ) پایه_2 آدرس
                                                          AT91_C_پایه_TDES EQU( 0xFFFA8000 );
                                                          -( TDES ) پایه_2 آدرس

/* - ***************************************************************************** */
/* -               MEMORY MAPPING DEFINITIONS FOR AT91SAM7X256 */
/* - ***************************************************************************** */
                                                          AT91C_ISRAM EQU( 0x00200000 );
                                                          -داخلی SRAM پایه آدرس_2
                                                          AT91_C_ISRAM_اندازه EQU( 0x00010000 );
                                                          -داخلی SRAM اندازه درون byte( 64 Kbyte )
                                                          AT91C_IFLASH EQU( 0x00100000 );
                                                          -داخلی ROM پایه آدرس_2
                                                          AT91_C_IFLASH_اندازه EQU( 0x00040000 );
                                                          -داخلی ROM اندازه درون byte( 256 Kbyte )



#پایان_اگر /* AT91SAM7X256_H */
