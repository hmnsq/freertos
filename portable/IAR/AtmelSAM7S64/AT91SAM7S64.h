/* ---------------------------------------------------------------------------- */
/*          ATMEL Microcontroller Software Support  -  ROUSSET  - */
/* ---------------------------------------------------------------------------- */
/*  The software is delivered "AS IS" without warranty or condition of any */
/*  kind, either express, implied or statutory. This includes without */
/*  limitation any warranty or condition with respect to merchantability or */
/*  fitness for any particular purpose, or against the infringements of */
/*  intellectual property rights of others. */
/* ---------------------------------------------------------------------------- */
/* File Name           : AT91SAM7S64.h */
/* Object              : AT91SAM7S64 definitions */
/* Generated           : AT91 SW Application Group  07/16/2004 (07:43:08) */
/* */
/* CVS Reference       : /AT91SAM7S64.pl/1.12/Mon Jul 12 13:02:30 2004// */
/* CVS Reference       : /SYSC_SAM7Sxx.pl/1.5/Mon Jul 12 16:22:12 2004// */
/* CVS Reference       : /MC_SAM02.pl/1.3/Wed Mar 10 08:37:04 2004// */
/* CVS Reference       : /UDP_1765B.pl/1.3/Fri Aug  2 14:45:38 2002// */
/* CVS Reference       : /AIC_1796B.pl/1.1.1.1/Fri Jun 28 09:36:48 2002// */
/* CVS Reference       : /lib_pmc_SAM.h/1.6/Tue Apr 27 13:53:52 2004// */
/* CVS Reference       : /PIO_1725D.pl/1.1.1.1/Fri Jun 28 09:36:48 2002// */
/* CVS Reference       : /DBGU_1754A.pl/1.4/Fri Jan 31 12:18:24 2003// */
/* CVS Reference       : /US_1739C.pl/1.2/Mon Jul 12 17:26:24 2004// */
/* CVS Reference       : /SPI2.pl/1.2/Fri Oct 17 08:13:40 2003// */
/* CVS Reference       : /SSC_1762A.pl/1.2/Fri Nov  8 13:26:40 2002// */
/* CVS Reference       : /lib_tc_1753b.h/1.1/Fri Jan 31 12:20:02 2003// */
/* CVS Reference       : /TWI_1761B.pl/1.4/Fri Feb  7 10:30:08 2003// */
/* CVS Reference       : /PDC_1734B.pl/1.2/Thu Nov 21 16:38:24 2002// */
/* CVS Reference       : /ADC_SAM.pl/1.7/Fri Oct 17 08:12:38 2003// */
/* CVS Reference       : /lib_PWM_SAM.h/1.3/Thu Jan 22 10:10:50 2004// */
/* ---------------------------------------------------------------------------- */

#جيڪڏهن_وصف_نه_ٿيل AT91SAM7S64_H
#وصف_ڪريو AT91SAM7S64_H

تعريفنوع متطاير بنانشان صحيح AT91_REG; /* Hardware register definition */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR System Peripherals */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_SYSC
{
    AT91_REG SYSC_AIC_SMR[ 32 ]; /* Source Mode Register */
    AT91_REG SYSC_AIC_SVR[ 32 ]; /* Source Vector Register */
    AT91_REG SYSC_AIC_IVR;       /* IRQ Vector Register */
    AT91_REG SYSC_AIC_FVR;       /* FIQ Vector Register */
    AT91_REG SYSC_AIC_ISR;       /* Interrupt Status Register */
    AT91_REG SYSC_AIC_IPR;       /* Interrupt Pending Register */
    AT91_REG SYSC_AIC_IMR;       /* Interrupt Mask Register */
    AT91_REG SYSC_AIC_CISR;      /* Core Interrupt Status Register */
    AT91_REG Reserved0[ 2 ];     /* */
    AT91_REG SYSC_AIC_IECR;      /* Interrupt Enable Command Register */
    AT91_REG SYSC_AIC_IDCR;      /* Interrupt Disable Command Register */
    AT91_REG SYSC_AIC_ICCR;      /* Interrupt Clear Command Register */
    AT91_REG SYSC_AIC_ISCR;      /* Interrupt Set Command Register */
    AT91_REG SYSC_AIC_EOICR;     /* End of Interrupt Command Register */
    AT91_REG SYSC_AIC_SPU;       /* Spurious Vector Register */
    AT91_REG SYSC_AIC_DCR;       /* Debug Control Register (Protect) */
    AT91_REG Reserved1[ 1 ];     /* */
    AT91_REG SYSC_AIC_FFER;      /* Fast Forcing Enable Register */
    AT91_REG SYSC_AIC_FFDR;      /* Fast Forcing Disable Register */
    AT91_REG SYSC_AIC_FFSR;      /* Fast Forcing Status Register */
    AT91_REG Reserved2[ 45 ];    /* */
    AT91_REG SYSC_DBGU_CR;       /* Control Register */
    AT91_REG SYSC_DBGU_MR;       /* Mode Register */
    AT91_REG SYSC_DBGU_IER;      /* Interrupt Enable Register */
    AT91_REG SYSC_DBGU_IDR;      /* Interrupt Disable Register */
    AT91_REG SYSC_DBGU_IMR;      /* Interrupt Mask Register */
    AT91_REG SYSC_DBGU_CSR;      /* Channel Status Register */
    AT91_REG SYSC_DBGU_RHR;      /* Receiver Holding Register */
    AT91_REG SYSC_DBGU_THR;      /* Transmitter Holding Register */
    AT91_REG SYSC_DBGU_BRGR;     /* Baud Rate Generator Register */
    AT91_REG Reserved3[ 7 ];     /* */
    AT91_REG SYSC_DBGU_C1R;      /* Chip ID1 Register */
    AT91_REG SYSC_DBGU_C2R;      /* Chip ID2 Register */
    AT91_REG SYSC_DBGU_FNTR;     /* Force NTRST Register */
    AT91_REG Reserved4[ 45 ];    /* */
    AT91_REG SYSC_DBGU_RPR;      /* Receive Pointer Register */
    AT91_REG SYSC_DBGU_RCR;      /* Receive Counter Register */
    AT91_REG SYSC_DBGU_TPR;      /* Transmit Pointer Register */
    AT91_REG SYSC_DBGU_TCR;      /* Transmit Counter Register */
    AT91_REG SYSC_DBGU_RNPR;     /* Receive Next Pointer Register */
    AT91_REG SYSC_DBGU_RNCR;     /* Receive Next Counter Register */
    AT91_REG SYSC_DBGU_TNPR;     /* Transmit Next Pointer Register */
    AT91_REG SYSC_DBGU_TNCR;     /* Transmit Next Counter Register */
    AT91_REG SYSC_DBGU_PTCR;     /* PDC Transfer Control Register */
    AT91_REG SYSC_DBGU_PTSR;     /* PDC Transfer Status Register */
    AT91_REG Reserved5[ 54 ];    /* */
    AT91_REG SYSC_PIOA_في;      /* PIO Enable Register */
    AT91_REG SYSC_PIOA_PDR;      /* PIO Disable Register */
    AT91_REG SYSC_PIOA_PSR;      /* PIO Status Register */
    AT91_REG Reserved6[ 1 ];     /* */
    AT91_REG SYSC_PIOA_OER;      /* Output Enable Register */
    AT91_REG SYSC_PIOA_ODR;      /* Output Disable Registerr */
    AT91_REG SYSC_PIOA_OSR;      /* Output Status Register */
    AT91_REG Reserved7[ 1 ];     /* */
    AT91_REG SYSC_PIOA_IFER;     /* Input Filter Enable Register */
    AT91_REG SYSC_PIOA_IFDR;     /* Input Filter Disable Register */
    AT91_REG SYSC_PIOA_IFSR;     /* Input Filter Status Register */
    AT91_REG Reserved8[ 1 ];     /* */
    AT91_REG SYSC_PIOA_SODR;     /* Set Output Data Register */
    AT91_REG SYSC_PIOA_CODR;     /* Clear Output Data Register */
    AT91_REG SYSC_PIOA_ODSR;     /* Output Data Status Register */
    AT91_REG SYSC_PIOA_PDSR;     /* Pin Data Status Register */
    AT91_REG SYSC_PIOA_IER;      /* Interrupt Enable Register */
    AT91_REG SYSC_PIOA_IDR;      /* Interrupt Disable Register */
    AT91_REG SYSC_PIOA_IMR;      /* Interrupt Mask Register */
    AT91_REG SYSC_PIOA_ISR;      /* Interrupt Status Register */
    AT91_REG SYSC_PIOA_MDER;     /* Multi-driver Enable Register */
    AT91_REG SYSC_PIOA_MDDR;     /* Multi-driver Disable Register */
    AT91_REG SYSC_PIOA_MDSR;     /* Multi-driver Status Register */
    AT91_REG Reserved9[ 1 ];     /* */
    AT91_REG SYSC_PIOA_PPUDR;    /* Pull-up Disable Register */
    AT91_REG SYSC_PIOA_PPUER;    /* Pull-up Enable Register */
    AT91_REG SYSC_PIOA_PPUSR;    /* Pad Pull-up Status Register */
    AT91_REG Reserved10[ 1 ];    /* */
    AT91_REG SYSC_PIOA_ASR;      /* Select A Register */
    AT91_REG SYSC_PIOA_BSR;      /* Select B Register */
    AT91_REG SYSC_PIOA_ABSR;     /* AB Select Status Register */
    AT91_REG Reserved11[ 9 ];    /* */
    AT91_REG SYSC_PIOA_OWER;     /* Output Write Enable Register */
    AT91_REG SYSC_PIOA_OWDR;     /* Output Write Disable Register */
    AT91_REG SYSC_PIOA_OWSR;     /* Output Write Status Register */
    AT91_REG Reserved12[ 469 ];  /* */
    AT91_REG SYSC_PMC_SCER;      /* System Clock Enable Register */
    AT91_REG SYSC_PMC_SCDR;      /* System Clock Disable Register */
    AT91_REG SYSC_PMC_SCSR;      /* System Clock Status Register */
    AT91_REG Reserved13[ 1 ];    /* */
    AT91_REG SYSC_PMC_PCER;      /* Peripheral Clock Enable Register */
    AT91_REG SYSC_PMC_PCDR;      /* Peripheral Clock Disable Register */
    AT91_REG SYSC_PMC_PCSR;      /* Peripheral Clock Status Register */
    AT91_REG Reserved14[ 1 ];    /* */
    AT91_REG SYSC_PMC_MOR;       /* Main Oscillator Register */
    AT91_REG SYSC_PMC_MCFR;      /* Main Clock  Frequency Register */
    AT91_REG Reserved15[ 1 ];    /* */
    AT91_REG SYSC_PMC_PLLR;      /* PLL Register */
    AT91_REG SYSC_PMC_MCKR;      /* Master Clock Register */
    AT91_REG Reserved16[ 3 ];    /* */
    AT91_REG SYSC_PMC_PCKR[ 8 ]; /* Programmable Clock Register */
    AT91_REG SYSC_PMC_IER;       /* Interrupt Enable Register */
    AT91_REG SYSC_PMC_IDR;       /* Interrupt Disable Register */
    AT91_REG SYSC_PMC_SR;        /* Status Register */
    AT91_REG SYSC_PMC_IMR;       /* Interrupt Mask Register */
    AT91_REG Reserved17[ 36 ];   /* */
    AT91_REG SYSC_RSTC_RCR;      /* Reset Control Register */
    AT91_REG SYSC_RSTC_RSR;      /* Reset Status Register */
    AT91_REG SYSC_RSTC_RMR;      /* Reset Mode Register */
    AT91_REG Reserved18[ 5 ];    /* */
    AT91_REG SYSC_RTTC_RTMR;     /* Real-time Mode Register */
    AT91_REG SYSC_RTTC_RTAR;     /* Real-time Alarm Register */
    AT91_REG SYSC_RTTC_RTVR;     /* Real-time Value Register */
    AT91_REG SYSC_RTTC_RTSR;     /* Real-time Status Register */
    AT91_REG SYSC_PITC_PIMR;     /* Period Interval Mode Register */
    AT91_REG SYSC_PITC_PISR;     /* Period Interval Status Register */
    AT91_REG SYSC_PITC_PIVR;     /* Period Interval Value Register */
    AT91_REG SYSC_PITC_PIIR;     /* Period Interval Image Register */
    AT91_REG SYSC_WDTC_WDCR;     /* Watchdog Control Register */
    AT91_REG SYSC_WDTC_WDMR;     /* Watchdog Mode Register */
    AT91_REG SYSC_WDTC_WDSR;     /* Watchdog Status Register */
    AT91_REG Reserved19[ 5 ];    /* */
    AT91_REG SYSC_SYSC_VRPM;     /* Voltage Regulator Power Mode Register */
} AT91S_SYSC, * AT91PS_SYSC;

/* -------- VRPM : (SYSC Offset: 0xd60) Voltage Regulator Power Mode Register -------- */
#وصف_ڪريو AT91C_SYSC_PSTDBY    ( ( بنانشان صحيح ) 0x1 << 0 ) /* (SYSC) Voltage Regulator Power Mode */

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
#وصف_ڪريو AT91_C_AIC_اڳواٽ                              ( ( بنانشان صحيح ) 0x7 << 0 ) /* (AIC) Priority Level */
#وصف_ڪريو     AT91_C_AIC_اڳواٽ_سڀ_کان_هيٺ                   ( ( بنانشان صحيح ) 0x0 )      /* (AIC) Lowest priority level */
#وصف_ڪريو     AT91_C_AIC_اڳواٽ_HIGHEST                  ( ( بنانشان صحيح ) 0x7 )      /* (AIC) Highest priority level */
#وصف_ڪريو AT91C_AIC_SRCTYPE                            ( ( بنانشان صحيح ) 0x3 << 5 ) /* (AIC) Interrupt Source Type */
#وصف_ڪريو     AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE    ( ( بنانشان صحيح ) 0x0 << 5 ) /* (AIC) Internal Sources Code Label Level Sensitive */
#وصف_ڪريو     AT91_C_AIC_SRCTYPE_INT_ڪنارو_TRIGGERED     ( ( بنانشان صحيح ) 0x1 << 5 ) /* (AIC) Internal Sources Code Label Edge triggered */
#وصف_ڪريو     AT91_C_AIC_SRCTYPE_EXT_مٿاهون_LEVEL         ( ( بنانشان صحيح ) 0x2 << 5 ) /* (AIC) External Sources Code Label High-level Sensitive */
#وصف_ڪريو     AT91_C_AIC_SRCTYPE_EXT_مثبت_ڪنارو      ( ( بنانشان صحيح ) 0x3 << 5 ) /* (AIC) External Sources Code Label Positive Edge triggered */
/* -------- AIC_CISR : (AIC Offset: 0x114) AIC Core Interrupt Status Register -------- */
#وصف_ڪريو AT91C_AIC_NFIQ                               ( ( بنانشان صحيح ) 0x1 << 0 ) /* (AIC) NFIQ Status */
#وصف_ڪريو AT91C_AIC_NIRQ                               ( ( بنانشان صحيح ) 0x1 << 1 ) /* (AIC) NIRQ Status */
/* -------- AIC_DCR : (AIC Offset: 0x138) AIC Debug Control Register (Protect) -------- */
#وصف_ڪريو AT91C_AIC_DCR_PROT                           ( ( بنانشان صحيح ) 0x1 << 0 ) /* (AIC) Protection Mode */
#وصف_ڪريو AT91C_AIC_DCR_GMSK                           ( ( بنانشان صحيح ) 0x1 << 1 ) /* (AIC) General Mask */

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
    AT91_REG DBGU_C1R;        /* Chip ID1 Register */
    AT91_REG DBGU_C2R;        /* Chip ID2 Register */
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
/*              SOFTWARE API DEFINITION  FOR Peripheral Data Controller */
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
    AT91_REG PIO_PPUSR;      /* Pad Pull-up Status Register */
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
    AT91_REG PMC_PCKR[ 8 ];  /* Programmable Clock Register */
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

/* -------- SYSC_RCR : (RSTC Offset: 0x0) Reset Control Register -------- */
#وصف_ڪريو AT91C_SYSC_PROCRST                ( ( بنانشان صحيح ) 0x1 << 0 )   /* (RSTC) Processor Reset */
#وصف_ڪريو AT91C_SYSC_ICERST                 ( ( بنانشان صحيح ) 0x1 << 1 )   /* (RSTC) ICE Interface Reset */
#وصف_ڪريو AT91C_SYSC_PERRST                 ( ( بنانشان صحيح ) 0x1 << 2 )   /* (RSTC) Peripheral Reset */
#وصف_ڪريو AT91C_SYSC_EXTRST                 ( ( بنانشان صحيح ) 0x1 << 3 )   /* (RSTC) External Reset */
#وصف_ڪريو AT91_C_SYSC_ڪنجي                    ( ( بنانشان صحيح ) 0xFF << 24 ) /* (RSTC) Password */
/* -------- SYSC_RSR : (RSTC Offset: 0x4) Reset Status Register -------- */
#وصف_ڪريو AT91C_SYSC_URSTS                  ( ( بنانشان صحيح ) 0x1 << 0 )   /* (RSTC) User Reset Status */
#وصف_ڪريو AT91C_SYSC_BODSTS                 ( ( بنانشان صحيح ) 0x1 << 1 )   /* (RSTC) Brown-out Detection Status */
#وصف_ڪريو AT91C_SYSC_RSTTYP                 ( ( بنانشان صحيح ) 0x7 << 8 )   /* (RSTC) Reset Type */
#وصف_ڪريو     AT91C_SYSC_RSTTYP_POWERUP     ( ( بنانشان صحيح ) 0x0 << 8 )   /* (RSTC) Power-up Reset. VDDCORE rising. */
#وصف_ڪريو     AT91C_SYSC_RSTTYP_WATCHDOG    ( ( بنانشان صحيح ) 0x2 << 8 )   /* (RSTC) Watchdog Reset. Watchdog overflow occurred. */
#وصف_ڪريو     AT91C_SYSC_RSTTYP_SOFTWARE    ( ( بنانشان صحيح ) 0x3 << 8 )   /* (RSTC) Software Reset. Processor reset required by the software. */
#وصف_ڪريو     AT91C_SYSC_RSTTYP_USER        ( ( بنانشان صحيح ) 0x4 << 8 )   /* (RSTC) User Reset. NRST pin detected low. */
#وصف_ڪريو     AT91C_SYSC_RSTTYP_BROWNOUT    ( ( بنانشان صحيح ) 0x5 << 8 )   /* (RSTC) Brown-out Reset. */
#وصف_ڪريو AT91C_SYSC_NRSTL                  ( ( بنانشان صحيح ) 0x1 << 16 )  /* (RSTC) NRST pin level */
#وصف_ڪريو AT91C_SYSC_SRCMP                  ( ( بنانشان صحيح ) 0x1 << 17 )  /* (RSTC) Software Reset Command in Progress. */
/* -------- SYSC_RMR : (RSTC Offset: 0x8) Reset Mode Register -------- */
#وصف_ڪريو AT91C_SYSC_URSTEN                 ( ( بنانشان صحيح ) 0x1 << 0 )   /* (RSTC) User Reset Enable */
#وصف_ڪريو AT91C_SYSC_URSTIEN                ( ( بنانشان صحيح ) 0x1 << 4 )   /* (RSTC) User Reset Interrupt Enable */
#وصف_ڪريو AT91C_SYSC_ERSTL                  ( ( بنانشان صحيح ) 0xF << 8 )   /* (RSTC) User Reset Enable */
#وصف_ڪريو AT91C_SYSC_BODIEN                 ( ( بنانشان صحيح ) 0x1 << 16 )  /* (RSTC) Brown-out Detection Interrupt Enable */

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

/* -------- SYSC_RTMR : (RTTC Offset: 0x0) Real-time Mode Register -------- */
#وصف_ڪريو AT91C_SYSC_RTPRES       ( ( بنانشان صحيح ) 0xFFFF << 0 ) /* (RTTC) Real-time Timer Prescaler Value */
#وصف_ڪريو AT91C_SYSC_ALMIEN       ( ( بنانشان صحيح ) 0x1 << 16 )   /* (RTTC) Alarm Interrupt Enable */
#وصف_ڪريو AT91C_SYSC_RTTINCIEN    ( ( بنانشان صحيح ) 0x1 << 17 )   /* (RTTC) Real Time Timer Increment Interrupt Enable */
#وصف_ڪريو AT91C_SYSC_RTTRST       ( ( بنانشان صحيح ) 0x1 << 18 )   /* (RTTC) Real Time Timer Restart */
/* -------- SYSC_RTAR : (RTTC Offset: 0x4) Real-time Alarm Register -------- */
#وصف_ڪريو AT91C_SYSC_ALMV         ( ( بنانشان صحيح ) 0x0 << 0 )    /* (RTTC) Alarm Value */
/* -------- SYSC_RTVR : (RTTC Offset: 0x8) Current Real-time Value Register -------- */
#وصف_ڪريو AT91C_SYSC_CRTV         ( ( بنانشان صحيح ) 0x0 << 0 )    /* (RTTC) Current Real-time Value */
/* -------- SYSC_RTSR : (RTTC Offset: 0xc) Real-time Status Register -------- */
#وصف_ڪريو AT91C_SYSC_ALMS         ( ( بنانشان صحيح ) 0x1 << 0 )    /* (RTTC) Real-time Alarm Status */
#وصف_ڪريو AT91C_SYSC_RTTINC       ( ( بنانشان صحيح ) 0x1 << 1 )    /* (RTTC) Real-time Timer Increment */

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

/* -------- SYSC_PIMR : (PITC Offset: 0x0) Periodic Interval Mode Register -------- */
#وصف_ڪريو AT91C_SYSC_PIV       ( ( بنانشان صحيح ) 0xFFFFF << 0 ) /* (PITC) Periodic Interval Value */
#وصف_ڪريو AT91C_SYSC_PITEN     ( ( بنانشان صحيح ) 0x1 << 24 )    /* (PITC) Periodic Interval Timer Enabled */
#وصف_ڪريو AT91C_SYSC_PITIEN    ( ( بنانشان صحيح ) 0x1 << 25 )    /* (PITC) Periodic Interval Timer Interrupt Enable */
/* -------- SYSC_PISR : (PITC Offset: 0x4) Periodic Interval Status Register -------- */
#وصف_ڪريو AT91C_SYSC_PITS      ( ( بنانشان صحيح ) 0x1 << 0 )     /* (PITC) Periodic Interval Timer Status */
/* -------- SYSC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register -------- */
#وصف_ڪريو AT91C_SYSC_CPIV      ( ( بنانشان صحيح ) 0xFFFFF << 0 ) /* (PITC) Current Periodic Interval Value */
#وصف_ڪريو AT91C_SYSC_PICNT     ( ( بنانشان صحيح ) 0xFFF << 20 )  /* (PITC) Periodic Interval Counter */
/* -------- SYSC_PIIR : (PITC Offset: 0xc) Periodic Interval Image Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Watchdog Timer Controller Interface */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_WDTC
{
    AT91_REG WDTC_WDCR; /* Watchdog Control Register */
    AT91_REG WDTC_WDMR; /* Watchdog Mode Register */
    AT91_REG WDTC_WDSR; /* Watchdog Status Register */
} AT91S_WDTC, * AT91PS_WDTC;

/* -------- SYSC_WDCR : (WDTC Offset: 0x0) Periodic Interval Image Register -------- */
#وصف_ڪريو AT91C_SYSC_WDRSTT       ( ( بنانشان صحيح ) 0x1 << 0 )    /* (WDTC) Watchdog Restart */
/* -------- SYSC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register -------- */
#وصف_ڪريو AT91C_SYSC_WDV          ( ( بنانشان صحيح ) 0xFFF << 0 )  /* (WDTC) Watchdog Timer Restart */
#وصف_ڪريو AT91C_SYSC_WDFIEN       ( ( بنانشان صحيح ) 0x1 << 12 )   /* (WDTC) Watchdog Fault Interrupt Enable */
#وصف_ڪريو AT91C_SYSC_WDRSTEN      ( ( بنانشان صحيح ) 0x1 << 13 )   /* (WDTC) Watchdog Reset Enable */
#وصف_ڪريو AT91C_SYSC_WDRPROC      ( ( بنانشان صحيح ) 0x1 << 14 )   /* (WDTC) Watchdog Timer Restart */
#وصف_ڪريو AT91C_SYSC_WDDIS        ( ( بنانشان صحيح ) 0x1 << 15 )   /* (WDTC) Watchdog Disable */
#وصف_ڪريو AT91C_SYSC_WDD          ( ( بنانشان صحيح ) 0xFFF << 16 ) /* (WDTC) Watchdog Delta Value */
#وصف_ڪريو AT91C_SYSC_WDDBGHLT     ( ( بنانشان صحيح ) 0x1 << 28 )   /* (WDTC) Watchdog Debug Halt */
#وصف_ڪريو AT91C_SYSC_WDIDLEHLT    ( ( بنانشان صحيح ) 0x1 << 29 )   /* (WDTC) Watchdog Idle Halt */
/* -------- SYSC_WDSR : (WDTC Offset: 0x8) Watchdog Status Register -------- */
#وصف_ڪريو AT91C_SYSC_WDUNF        ( ( بنانشان صحيح ) 0x1 << 0 )    /* (WDTC) Watchdog Underflow */
#وصف_ڪريو AT91C_SYSC_WDERR        ( ( بنانشان صحيح ) 0x1 << 1 )    /* (WDTC) Watchdog Error */

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
#وصف_ڪريو AT91C_SPI_CSAAT          ( ( بنانشان صحيح ) 0x1 << 2 )   /* (SPI) Chip Select Active After Transfer */
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
#وصف_ڪريو AT91C_SPI_DLYBS          ( ( بنانشان صحيح ) 0xFF << 16 ) /* (SPI) Serial Clock Baud Rate */
#وصف_ڪريو AT91C_SPI_DLYBCT         ( ( بنانشان صحيح ) 0xFF << 24 ) /* (SPI) Delay Between Consecutive Transfers */

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
    AT91_REG SSC_RC0R;        /* Receive Compare 0 Register */
    AT91_REG SSC_RC1R;        /* Receive Compare 1 Register */
    AT91_REG SSC_SR;          /* Status Register */
    AT91_REG SSC_IER;         /* Interrupt Enable Register */
    AT91_REG SSC_IDR;         /* Interrupt Disable Register */
    AT91_REG SSC_IMR;         /* Interrupt Mask Register */
    AT91_REG Reserved2[ 44 ]; /* */
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
#وصف_ڪريو AT91C_SSC_CKG                     ( ( بنانشان صحيح ) 0x3 << 6 )   /* (SSC) Receive/Transmit Clock Gating Selection */
#وصف_ڪريو     AT91C_SSC_CKG_NONE            ( ( بنانشان صحيح ) 0x0 << 6 )   /* (SSC) Receive/Transmit Clock Gating: None, continuous clock */
#وصف_ڪريو     AT91_C_SSC_CKG_هيٺيون             ( ( بنانشان صحيح ) 0x1 << 6 )   /* (SSC) Receive/Transmit Clock enabled only if RF Low */
#وصف_ڪريو     AT91_C_SSC_CKG_مٿاهون            ( ( بنانشان صحيح ) 0x2 << 6 )   /* (SSC) Receive/Transmit Clock enabled only if RF High */
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
#وصف_ڪريو AT91C_SSC_STOP                    ( ( بنانشان صحيح ) 0x1 << 12 )  /* (SSC) Receive Stop Selection */
#وصف_ڪريو AT91C_SSC_STTOUT                  ( ( بنانشان صحيح ) 0x1 << 15 )  /* (SSC) Receive/Transmit Start Output Selection */
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
#وصف_ڪريو AT91C_SSC_CP0                     ( ( بنانشان صحيح ) 0x1 << 8 )  /* (SSC) Compare 0 */
#وصف_ڪريو AT91C_SSC_CP1                     ( ( بنانشان صحيح ) 0x1 << 9 )  /* (SSC) Compare 1 */
#وصف_ڪريو AT91C_SSC_TXSYN                   ( ( بنانشان صحيح ) 0x1 << 10 ) /* (SSC) Transmit Sync */
#وصف_ڪريو AT91C_SSC_RXSYN                   ( ( بنانشان صحيح ) 0x1 << 11 ) /* (SSC) Receive Sync */
#وصف_ڪريو AT91C_SSC_TXENA                   ( ( بنانشان صحيح ) 0x1 << 16 ) /* (SSC) Transmit Enable */
#وصف_ڪريو AT91C_SSC_RXENA                   ( ( بنانشان صحيح ) 0x1 << 17 ) /* (SSC) Receive Enable */
/* -------- SSC_IER : (SSC Offset: 0x44) SSC Interrupt Enable Register -------- */
/* -------- SSC_IDR : (SSC Offset: 0x48) SSC Interrupt Disable Register -------- */
/* -------- SSC_IMR : (SSC Offset: 0x4c) SSC Interrupt Mask Register -------- */

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
    AT91_REG US_XXR;          /* XON_XOFF Register */
    AT91_REG US_IF;           /* IRDA_FILTER Register */
    AT91_REG Reserved1[ 44 ]; /* */
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
#وصف_ڪريو AT91C_US_RSTSTA                  ( ( بنانشان صحيح ) 0x1 << 8 )  /* (USART) Reset Status Bits */
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
/*              SOFTWARE API DEFINITION  FOR Two-wire Interface */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_TWI
{
    AT91_REG TWI_CR;         /* Control Register */
    AT91_REG TWI_MMR;        /* Master Mode Register */
    AT91_REG TWI_SMR;        /* Slave Mode Register */
    AT91_REG TWI_IADR;       /* Internal Address Register */
    AT91_REG TWI_CWGR;       /* Clock Waveform Generator Register */
    AT91_REG Reserved0[ 3 ]; /* */
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
#وصف_ڪريو AT91C_TWI_SVEN                 ( ( بنانشان صحيح ) 0x1 << 4 )   /* (TWI) TWI Slave Transfer Enabled */
#وصف_ڪريو AT91C_TWI_SVDIS                ( ( بنانشان صحيح ) 0x1 << 5 )   /* (TWI) TWI Slave Transfer Disabled */
#وصف_ڪريو AT91C_TWI_SWRST                ( ( بنانشان صحيح ) 0x1 << 7 )   /* (TWI) Software Reset */
/* -------- TWI_MMR : (TWI Offset: 0x4) TWI Master Mode Register -------- */
#وصف_ڪريو AT91C_TWI_IADRSZ               ( ( بنانشان صحيح ) 0x3 << 8 )   /* (TWI) Internal Device Address Size */
#وصف_ڪريو     AT91C_TWI_IADRSZ_NO        ( ( بنانشان صحيح ) 0x0 << 8 )   /* (TWI) No internal device address */
#وصف_ڪريو     AT91C_TWI_IADRSZ_1_BYTE    ( ( بنانشان صحيح ) 0x1 << 8 )   /* (TWI) One-byte internal device address */
#وصف_ڪريو     AT91C_TWI_IADRSZ_2_BYTE    ( ( بنانشان صحيح ) 0x2 << 8 )   /* (TWI) Two-byte internal device address */
#وصف_ڪريو     AT91C_TWI_IADRSZ_3_BYTE    ( ( بنانشان صحيح ) 0x3 << 8 )   /* (TWI) Three-byte internal device address */
#وصف_ڪريو AT91C_TWI_MREAD                ( ( بنانشان صحيح ) 0x1 << 12 )  /* (TWI) Master Read Direction */
#وصف_ڪريو AT91C_TWI_DADR                 ( ( بنانشان صحيح ) 0x7F << 16 ) /* (TWI) Device Address */
/* -------- TWI_SMR : (TWI Offset: 0x8) TWI Slave Mode Register -------- */
#وصف_ڪريو AT91C_TWI_SADR                 ( ( بنانشان صحيح ) 0x7F << 16 ) /* (TWI) Slave Device Address */
/* -------- TWI_CWGR : (TWI Offset: 0x10) TWI Clock Waveform Generator Register -------- */
#وصف_ڪريو AT91C_TWI_CLDIV                ( ( بنانشان صحيح ) 0xFF << 0 )  /* (TWI) Clock Low Divider */
#وصف_ڪريو AT91C_TWI_CHDIV                ( ( بنانشان صحيح ) 0xFF << 8 )  /* (TWI) Clock High Divider */
#وصف_ڪريو AT91C_TWI_CKDIV                ( ( بنانشان صحيح ) 0x7 << 16 )  /* (TWI) Clock Divider */
/* -------- TWI_SR : (TWI Offset: 0x20) TWI Status Register -------- */
#وصف_ڪريو AT91C_TWI_TXCOMP               ( ( بنانشان صحيح ) 0x1 << 0 )   /* (TWI) Transmission Completed */
#وصف_ڪريو AT91C_TWI_RXRDY                ( ( بنانشان صحيح ) 0x1 << 1 )   /* (TWI) Receive holding register ReaDY */
#وصف_ڪريو AT91C_TWI_TXRDY                ( ( بنانشان صحيح ) 0x1 << 2 )   /* (TWI) Transmit holding register ReaDY */
#وصف_ڪريو AT91C_TWI_SVREAD               ( ( بنانشان صحيح ) 0x1 << 3 )   /* (TWI) Slave Read */
#وصف_ڪريو AT91C_TWI_SVACC                ( ( بنانشان صحيح ) 0x1 << 4 )   /* (TWI) Slave Access */
#وصف_ڪريو AT91C_TWI_GCACC                ( ( بنانشان صحيح ) 0x1 << 5 )   /* (TWI) General Call Access */
#وصف_ڪريو AT91C_TWI_OVRE                 ( ( بنانشان صحيح ) 0x1 << 6 )   /* (TWI) Overrun Error */
#وصف_ڪريو AT91C_TWI_UNRE                 ( ( بنانشان صحيح ) 0x1 << 7 )   /* (TWI) Underrun Error */
#وصف_ڪريو AT91C_TWI_NACK                 ( ( بنانشان صحيح ) 0x1 << 8 )   /* (TWI) Not Acknowledged */
#وصف_ڪريو AT91C_TWI_ARBLST               ( ( بنانشان صحيح ) 0x1 << 9 )   /* (TWI) Arbitration Lost */
/* -------- TWI_IER : (TWI Offset: 0x24) TWI Interrupt Enable Register -------- */
/* -------- TWI_IDR : (TWI Offset: 0x28) TWI Interrupt Disable Register -------- */
/* -------- TWI_IMR : (TWI Offset: 0x2c) TWI Interrupt Mask Register -------- */

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
#وصف_ڪريو AT91C_TC_LDBDIS                       ( ( بنانشان صحيح ) 0x1 << 7 )  /* (TC) Counter Clock Disabled with RB Loading */
#وصف_ڪريو AT91C_TC_CPCDIS                       ( ( بنانشان صحيح ) 0x1 << 7 )  /* (TC) Counter Clock Disable with RC Compare */
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
#وصف_ڪريو AT91C_TC_ABETRG                       ( ( بنانشان صحيح ) 0x1 << 10 ) /* (TC) TIOA or TIOB External Trigger Selection */
#وصف_ڪريو AT91C_TC_EEVT                         ( ( بنانشان صحيح ) 0x3 << 10 ) /* (TC) External Event  Selection */
#وصف_ڪريو     AT91C_TC_EEVT_NONE                ( ( بنانشان صحيح ) 0x0 << 10 ) /* (TC) Signal selected as external event: TIOB TIOB direction: input */
#وصف_ڪريو     AT91C_TC_EEVT_RISING              ( ( بنانشان صحيح ) 0x1 << 10 ) /* (TC) Signal selected as external event: XC0 TIOB direction: output */
#وصف_ڪريو     AT91C_TC_EEVT_FALLING             ( ( بنانشان صحيح ) 0x2 << 10 ) /* (TC) Signal selected as external event: XC1 TIOB direction: output */
#وصف_ڪريو     AT91C_TC_EEVT_BOTH                ( ( بنانشان صحيح ) 0x3 << 10 ) /* (TC) Signal selected as external event: XC2 TIOB direction: output */
#وصف_ڪريو AT91C_TC_ENETRG                       ( ( بنانشان صحيح ) 0x1 << 12 ) /* (TC) External Event Trigger enable */
#وصف_ڪريو AT91C_TC_WAVESEL                      ( ( بنانشان صحيح ) 0x3 << 13 ) /* (TC) Waveform  Selection */
#وصف_ڪريو     AT91_C_TC_WAVESEL_مٿي               ( ( بنانشان صحيح ) 0x0 << 13 ) /* (TC) UP mode without atomatic trigger on RC Compare */
#وصف_ڪريو     AT91C_TC_WAVESEL_UPDOWN           ( ( بنانشان صحيح ) 0x1 << 13 ) /* (TC) UPDOWN mode without automatic trigger on RC Compare */
#وصف_ڪريو     AT91_C_TC_WAVESEL_مٿي_AUTO          ( ( بنانشان صحيح ) 0x2 << 13 ) /* (TC) UP mode with automatic trigger on RC Compare */
#وصف_ڪريو     AT91C_TC_WAVESEL_UPDOWN_AUTO      ( ( بنانشان صحيح ) 0x3 << 13 ) /* (TC) UPDOWN mode with automatic trigger on RC Compare */
#وصف_ڪريو AT91C_TC_CPCTRG                       ( ( بنانشان صحيح ) 0x1 << 14 ) /* (TC) RC Compare Trigger Enable */
#وصف_ڪريو AT91C_TC_WAVE                         ( ( بنانشان صحيح ) 0x1 << 15 ) /* (TC) */
#وصف_ڪريو AT91C_TC_LDRA                         ( ( بنانشان صحيح ) 0x3 << 16 ) /* (TC) RA Loading Selection */
#وصف_ڪريو     AT91C_TC_LDRA_NONE                ( ( بنانشان صحيح ) 0x0 << 16 ) /* (TC) Edge: None */
#وصف_ڪريو     AT91C_TC_LDRA_RISING              ( ( بنانشان صحيح ) 0x1 << 16 ) /* (TC) Edge: rising edge of TIOA */
#وصف_ڪريو     AT91C_TC_LDRA_FALLING             ( ( بنانشان صحيح ) 0x2 << 16 ) /* (TC) Edge: falling edge of TIOA */
#وصف_ڪريو     AT91C_TC_LDRA_BOTH                ( ( بنانشان صحيح ) 0x3 << 16 ) /* (TC) Edge: each edge of TIOA */
#وصف_ڪريو AT91C_TC_ACPA                         ( ( بنانشان صحيح ) 0x3 << 16 ) /* (TC) RA Compare Effect on TIOA */
#وصف_ڪريو     AT91C_TC_ACPA_NONE                ( ( بنانشان صحيح ) 0x0 << 16 ) /* (TC) Effect: none */
#وصف_ڪريو     AT91_C_TC_ACPA_سيٽ                 ( ( بنانشان صحيح ) 0x1 << 16 ) /* (TC) Effect: set */
#وصف_ڪريو     AT91C_TC_ACPA_CLEAR               ( ( بنانشان صحيح ) 0x2 << 16 ) /* (TC) Effect: clear */
#وصف_ڪريو     AT91C_TC_ACPA_TOGGLE              ( ( بنانشان صحيح ) 0x3 << 16 ) /* (TC) Effect: toggle */
#وصف_ڪريو AT91C_TC_LDRB                         ( ( بنانشان صحيح ) 0x3 << 18 ) /* (TC) RB Loading Selection */
#وصف_ڪريو     AT91C_TC_LDRB_NONE                ( ( بنانشان صحيح ) 0x0 << 18 ) /* (TC) Edge: None */
#وصف_ڪريو     AT91C_TC_LDRB_RISING              ( ( بنانشان صحيح ) 0x1 << 18 ) /* (TC) Edge: rising edge of TIOA */
#وصف_ڪريو     AT91C_TC_LDRB_FALLING             ( ( بنانشان صحيح ) 0x2 << 18 ) /* (TC) Edge: falling edge of TIOA */
#وصف_ڪريو     AT91C_TC_LDRB_BOTH                ( ( بنانشان صحيح ) 0x3 << 18 ) /* (TC) Edge: each edge of TIOA */
#وصف_ڪريو AT91C_TC_ACPC                         ( ( بنانشان صحيح ) 0x3 << 18 ) /* (TC) RC Compare Effect on TIOA */
#وصف_ڪريو     AT91C_TC_ACPC_NONE                ( ( بنانشان صحيح ) 0x0 << 18 ) /* (TC) Effect: none */
#وصف_ڪريو     AT91_C_TC_ACPC_سيٽ                 ( ( بنانشان صحيح ) 0x1 << 18 ) /* (TC) Effect: set */
#وصف_ڪريو     AT91C_TC_ACPC_CLEAR               ( ( بنانشان صحيح ) 0x2 << 18 ) /* (TC) Effect: clear */
#وصف_ڪريو     AT91C_TC_ACPC_TOGGLE              ( ( بنانشان صحيح ) 0x3 << 18 ) /* (TC) Effect: toggle */
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
#وصف_ڪريو AT91C_TC_ETRCS                        ( ( بنانشان صحيح ) 0x1 << 7 )  /* (TC) External Trigger */
#وصف_ڪريو AT91C_TC_ETRGS                        ( ( بنانشان صحيح ) 0x1 << 16 ) /* (TC) Clock Enabling */
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
#وصف_ڪريو AT91C_TCB_TC0XC0S              ( ( بنانشان صحيح ) 0x1 << 0 ) /* (TCB) External Clock Signal 0 Selection */
#وصف_ڪريو     AT91C_TCB_TC0XC0S_TCLK0    ( ( بنانشان صحيح ) 0x0 )      /* (TCB) TCLK0 connected to XC0 */
#وصف_ڪريو     AT91C_TCB_TC0XC0S_NONE     ( ( بنانشان صحيح ) 0x1 )      /* (TCB) None signal connected to XC0 */
#وصف_ڪريو     AT91C_TCB_TC0XC0S_TIOA1    ( ( بنانشان صحيح ) 0x2 )      /* (TCB) TIOA1 connected to XC0 */
#وصف_ڪريو     AT91C_TCB_TC0XC0S_TIOA2    ( ( بنانشان صحيح ) 0x3 )      /* (TCB) TIOA2 connected to XC0 */
#وصف_ڪريو AT91C_TCB_TC1XC1S              ( ( بنانشان صحيح ) 0x1 << 2 ) /* (TCB) External Clock Signal 1 Selection */
#وصف_ڪريو     AT91C_TCB_TC1XC1S_TCLK1    ( ( بنانشان صحيح ) 0x0 << 2 ) /* (TCB) TCLK1 connected to XC1 */
#وصف_ڪريو     AT91C_TCB_TC1XC1S_NONE     ( ( بنانشان صحيح ) 0x1 << 2 ) /* (TCB) None signal connected to XC1 */
#وصف_ڪريو     AT91C_TCB_TC1XC1S_TIOA0    ( ( بنانشان صحيح ) 0x2 << 2 ) /* (TCB) TIOA0 connected to XC1 */
#وصف_ڪريو     AT91C_TCB_TC1XC1S_TIOA2    ( ( بنانشان صحيح ) 0x3 << 2 ) /* (TCB) TIOA2 connected to XC1 */
#وصف_ڪريو AT91C_TCB_TC2XC2S              ( ( بنانشان صحيح ) 0x1 << 4 ) /* (TCB) External Clock Signal 2 Selection */
#وصف_ڪريو     AT91C_TCB_TC2XC2S_TCLK2    ( ( بنانشان صحيح ) 0x0 << 4 ) /* (TCB) TCLK2 connected to XC2 */
#وصف_ڪريو     AT91C_TCB_TC2XC2S_NONE     ( ( بنانشان صحيح ) 0x1 << 4 ) /* (TCB) None signal connected to XC2 */
#وصف_ڪريو     AT91C_TCB_TC2XC2S_TIOA0    ( ( بنانشان صحيح ) 0x2 << 4 ) /* (TCB) TIOA0 connected to XC2 */
#وصف_ڪريو     AT91C_TCB_TC2XC2S_TIOA2    ( ( بنانشان صحيح ) 0x3 << 4 ) /* (TCB) TIOA2 connected to XC2 */

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
    AT91_REG PWMC_MR;            /* PWMC Mode Register */
    AT91_REG PWMC_ENA;           /* PWMC Enable Register */
    AT91_REG PWMC_DIS;           /* PWMC Disable Register */
    AT91_REG PWMC_SR;            /* PWMC Status Register */
    AT91_REG PWMC_IER;           /* PWMC Interrupt Enable Register */
    AT91_REG PWMC_IDR;           /* PWMC Interrupt Disable Register */
    AT91_REG PWMC_IMR;           /* PWMC Interrupt Mask Register */
    AT91_REG PWMC_ISR;           /* PWMC Interrupt Status Register */
    AT91_REG Reserved0[ 55 ];    /* */
    AT91_REG PWMC_VR;            /* PWMC Version Register */
    AT91_REG Reserved1[ 64 ];    /* */
    AT91S_PWMC_CH PWMC_CH[ 32 ]; /* PWMC Channel 0 */
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
#وصف_ڪريو AT91C_PWMC_CHID4           ( ( بنانشان صحيح ) 0x1 << 4 )   /* (PWMC) Channel ID 4 */
#وصف_ڪريو AT91C_PWMC_CHID5           ( ( بنانشان صحيح ) 0x1 << 5 )   /* (PWMC) Channel ID 5 */
#وصف_ڪريو AT91C_PWMC_CHID6           ( ( بنانشان صحيح ) 0x1 << 6 )   /* (PWMC) Channel ID 6 */
#وصف_ڪريو AT91C_PWMC_CHID7           ( ( بنانشان صحيح ) 0x1 << 7 )   /* (PWMC) Channel ID 7 */
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
    AT91_REG UDP_CSR[ 8 ];   /* Endpoint Control and Status Register */
    AT91_REG UDP_FDR[ 8 ];   /* Endpoint FIFO Data Register */
} AT91S_UDP, * AT91PS_UDP;

/* -------- UDP_FRM_NUM : (UDP Offset: 0x0) USB Frame Number Register -------- */
#وصف_ڪريو AT91_C_UDP_FRM_انگ    ( ( بنانشان صحيح ) 0x7FF << 0 ) /* (UDP) Frame Number as Defined in the Packet Field Formats */
#وصف_ڪريو AT91C_UDP_FRM_ERR    ( ( بنانشان صحيح ) 0x1 << 16 )  /* (UDP) Frame Error */
#وصف_ڪريو AT91C_UDP_FRM_OK     ( ( بنانشان صحيح ) 0x1 << 17 )  /* (UDP) Frame OK */
/* -------- UDP_GLB_STATE : (UDP Offset: 0x4) USB Global State Register -------- */
#وصف_ڪريو AT91C_UDP_FADDEN     ( ( بنانشان صحيح ) 0x1 << 0 )   /* (UDP) Function Address Enable */
#وصف_ڪريو AT91C_UDP_CONFG      ( ( بنانشان صحيح ) 0x1 << 1 )   /* (UDP) Configured */
#وصف_ڪريو AT91C_UDP_RMWUPE     ( ( بنانشان صحيح ) 0x1 << 2 )   /* (UDP) Remote Wake Up Enable */
#وصف_ڪريو AT91C_UDP_RSMINPR    ( ( بنانشان صحيح ) 0x1 << 3 )   /* (UDP) A Resume Has Been Sent to the Host */
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
#وصف_ڪريو AT91C_UDP_EPINT6     ( ( بنانشان صحيح ) 0x1 << 6 )   /* (UDP) Endpoint 6 Interrupt */
#وصف_ڪريو AT91C_UDP_EPINT7     ( ( بنانشان صحيح ) 0x1 << 7 )   /* (UDP) Endpoint 7 Interrupt */
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
#وصف_ڪريو AT91C_UDP_EP6                    ( ( بنانشان صحيح ) 0x1 << 6 )    /* (UDP) Reset Endpoint 6 */
#وصف_ڪريو AT91C_UDP_EP7                    ( ( بنانشان صحيح ) 0x1 << 7 )    /* (UDP) Reset Endpoint 7 */
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

/* ***************************************************************************** */
/*               REGISTER ADDRESS DEFINITION FOR AT91SAM7S64 */
/* ***************************************************************************** */
/* ========== Register definition for SYSC peripheral ========== */
#وصف_ڪريو AT91C_SYSC_SYSC_VRPM    ( ( AT91_REG * ) 0xFFFFFD60 ) /* (SYSC) Voltage Regulator Power Mode Register */
/* ========== Register definition for AIC peripheral ========== */
#وصف_ڪريو AT91C_AIC_ICCR          ( ( AT91_REG * ) 0xFFFFF128 ) /* (AIC) Interrupt Clear Command Register */
#وصف_ڪريو AT91C_AIC_IECR          ( ( AT91_REG * ) 0xFFFFF120 ) /* (AIC) Interrupt Enable Command Register */
#وصف_ڪريو AT91C_AIC_SMR           ( ( AT91_REG * ) 0xFFFFF000 ) /* (AIC) Source Mode Register */
#وصف_ڪريو AT91C_AIC_ISCR          ( ( AT91_REG * ) 0xFFFFF12C ) /* (AIC) Interrupt Set Command Register */
#وصف_ڪريو AT91C_AIC_EOICR         ( ( AT91_REG * ) 0xFFFFF130 ) /* (AIC) End of Interrupt Command Register */
#وصف_ڪريو AT91C_AIC_DCR           ( ( AT91_REG * ) 0xFFFFF138 ) /* (AIC) Debug Control Register (Protect) */
#وصف_ڪريو AT91C_AIC_FFER          ( ( AT91_REG * ) 0xFFFFF140 ) /* (AIC) Fast Forcing Enable Register */
#وصف_ڪريو AT91C_AIC_SVR           ( ( AT91_REG * ) 0xFFFFF080 ) /* (AIC) Source Vector Register */
#وصف_ڪريو AT91C_AIC_SPU           ( ( AT91_REG * ) 0xFFFFF134 ) /* (AIC) Spurious Vector Register */
#وصف_ڪريو AT91C_AIC_FFDR          ( ( AT91_REG * ) 0xFFFFF144 ) /* (AIC) Fast Forcing Disable Register */
#وصف_ڪريو AT91C_AIC_FVR           ( ( AT91_REG * ) 0xFFFFF104 ) /* (AIC) FIQ Vector Register */
#وصف_ڪريو AT91C_AIC_FFSR          ( ( AT91_REG * ) 0xFFFFF148 ) /* (AIC) Fast Forcing Status Register */
#وصف_ڪريو AT91C_AIC_IMR           ( ( AT91_REG * ) 0xFFFFF110 ) /* (AIC) Interrupt Mask Register */
#وصف_ڪريو AT91C_AIC_ISR           ( ( AT91_REG * ) 0xFFFFF108 ) /* (AIC) Interrupt Status Register */
#وصف_ڪريو AT91C_AIC_IVR           ( ( AT91_REG * ) 0xFFFFF100 ) /* (AIC) IRQ Vector Register */
#وصف_ڪريو AT91C_AIC_IDCR          ( ( AT91_REG * ) 0xFFFFF124 ) /* (AIC) Interrupt Disable Command Register */
#وصف_ڪريو AT91C_AIC_CISR          ( ( AT91_REG * ) 0xFFFFF114 ) /* (AIC) Core Interrupt Status Register */
#وصف_ڪريو AT91C_AIC_IPR           ( ( AT91_REG * ) 0xFFFFF10C ) /* (AIC) Interrupt Pending Register */
/* ========== Register definition for DBGU peripheral ========== */
#وصف_ڪريو AT91C_DBGU_C2R          ( ( AT91_REG * ) 0xFFFFF244 ) /* (DBGU) Chip ID2 Register */
#وصف_ڪريو AT91C_DBGU_THR          ( ( AT91_REG * ) 0xFFFFF21C ) /* (DBGU) Transmitter Holding Register */
#وصف_ڪريو AT91C_DBGU_CSR          ( ( AT91_REG * ) 0xFFFFF214 ) /* (DBGU) Channel Status Register */
#وصف_ڪريو AT91C_DBGU_IDR          ( ( AT91_REG * ) 0xFFFFF20C ) /* (DBGU) Interrupt Disable Register */
#وصف_ڪريو AT91C_DBGU_MR           ( ( AT91_REG * ) 0xFFFFF204 ) /* (DBGU) Mode Register */
#وصف_ڪريو AT91C_DBGU_FNTR         ( ( AT91_REG * ) 0xFFFFF248 ) /* (DBGU) Force NTRST Register */
#وصف_ڪريو AT91C_DBGU_C1R          ( ( AT91_REG * ) 0xFFFFF240 ) /* (DBGU) Chip ID1 Register */
#وصف_ڪريو AT91C_DBGU_BRGR         ( ( AT91_REG * ) 0xFFFFF220 ) /* (DBGU) Baud Rate Generator Register */
#وصف_ڪريو AT91C_DBGU_RHR          ( ( AT91_REG * ) 0xFFFFF218 ) /* (DBGU) Receiver Holding Register */
#وصف_ڪريو AT91C_DBGU_IMR          ( ( AT91_REG * ) 0xFFFFF210 ) /* (DBGU) Interrupt Mask Register */
#وصف_ڪريو AT91C_DBGU_IER          ( ( AT91_REG * ) 0xFFFFF208 ) /* (DBGU) Interrupt Enable Register */
#وصف_ڪريو AT91C_DBGU_CR           ( ( AT91_REG * ) 0xFFFFF200 ) /* (DBGU) Control Register */
/* ========== Register definition for PDC_DBGU peripheral ========== */
#وصف_ڪريو AT91C_DBGU_TNCR         ( ( AT91_REG * ) 0xFFFFF31C ) /* (PDC_DBGU) Transmit Next Counter Register */
#وصف_ڪريو AT91C_DBGU_RNCR         ( ( AT91_REG * ) 0xFFFFF314 ) /* (PDC_DBGU) Receive Next Counter Register */
#وصف_ڪريو AT91C_DBGU_PTCR         ( ( AT91_REG * ) 0xFFFFF320 ) /* (PDC_DBGU) PDC Transfer Control Register */
#وصف_ڪريو AT91C_DBGU_PTSR         ( ( AT91_REG * ) 0xFFFFF324 ) /* (PDC_DBGU) PDC Transfer Status Register */
#وصف_ڪريو AT91C_DBGU_RCR          ( ( AT91_REG * ) 0xFFFFF304 ) /* (PDC_DBGU) Receive Counter Register */
#وصف_ڪريو AT91C_DBGU_TCR          ( ( AT91_REG * ) 0xFFFFF30C ) /* (PDC_DBGU) Transmit Counter Register */
#وصف_ڪريو AT91C_DBGU_RPR          ( ( AT91_REG * ) 0xFFFFF300 ) /* (PDC_DBGU) Receive Pointer Register */
#وصف_ڪريو AT91C_DBGU_TPR          ( ( AT91_REG * ) 0xFFFFF308 ) /* (PDC_DBGU) Transmit Pointer Register */
#وصف_ڪريو AT91C_DBGU_RNPR         ( ( AT91_REG * ) 0xFFFFF310 ) /* (PDC_DBGU) Receive Next Pointer Register */
#وصف_ڪريو AT91C_DBGU_TNPR         ( ( AT91_REG * ) 0xFFFFF318 ) /* (PDC_DBGU) Transmit Next Pointer Register */
/* ========== Register definition for PIOA peripheral ========== */
#وصف_ڪريو AT91C_PIOA_IMR          ( ( AT91_REG * ) 0xFFFFF448 ) /* (PIOA) Interrupt Mask Register */
#وصف_ڪريو AT91C_PIOA_IER          ( ( AT91_REG * ) 0xFFFFF440 ) /* (PIOA) Interrupt Enable Register */
#وصف_ڪريو AT91C_PIOA_OWDR         ( ( AT91_REG * ) 0xFFFFF4A4 ) /* (PIOA) Output Write Disable Register */
#وصف_ڪريو AT91C_PIOA_ISR          ( ( AT91_REG * ) 0xFFFFF44C ) /* (PIOA) Interrupt Status Register */
#وصف_ڪريو AT91C_PIOA_PPUDR        ( ( AT91_REG * ) 0xFFFFF460 ) /* (PIOA) Pull-up Disable Register */
#وصف_ڪريو AT91C_PIOA_MDSR         ( ( AT91_REG * ) 0xFFFFF458 ) /* (PIOA) Multi-driver Status Register */
#وصف_ڪريو AT91C_PIOA_MDER         ( ( AT91_REG * ) 0xFFFFF450 ) /* (PIOA) Multi-driver Enable Register */
#وصف_ڪريو AT91_C_PIOA_في          ( ( AT91_REG * ) 0xFFFFF400 ) /* (PIOA) PIO Enable Register */
#وصف_ڪريو AT91C_PIOA_PSR          ( ( AT91_REG * ) 0xFFFFF408 ) /* (PIOA) PIO Status Register */
#وصف_ڪريو AT91C_PIOA_OER          ( ( AT91_REG * ) 0xFFFFF410 ) /* (PIOA) Output Enable Register */
#وصف_ڪريو AT91C_PIOA_BSR          ( ( AT91_REG * ) 0xFFFFF474 ) /* (PIOA) Select B Register */
#وصف_ڪريو AT91C_PIOA_PPUER        ( ( AT91_REG * ) 0xFFFFF464 ) /* (PIOA) Pull-up Enable Register */
#وصف_ڪريو AT91C_PIOA_MDDR         ( ( AT91_REG * ) 0xFFFFF454 ) /* (PIOA) Multi-driver Disable Register */
#وصف_ڪريو AT91C_PIOA_PDR          ( ( AT91_REG * ) 0xFFFFF404 ) /* (PIOA) PIO Disable Register */
#وصف_ڪريو AT91C_PIOA_ODR          ( ( AT91_REG * ) 0xFFFFF414 ) /* (PIOA) Output Disable Registerr */
#وصف_ڪريو AT91C_PIOA_IFDR         ( ( AT91_REG * ) 0xFFFFF424 ) /* (PIOA) Input Filter Disable Register */
#وصف_ڪريو AT91C_PIOA_ABSR         ( ( AT91_REG * ) 0xFFFFF478 ) /* (PIOA) AB Select Status Register */
#وصف_ڪريو AT91C_PIOA_ASR          ( ( AT91_REG * ) 0xFFFFF470 ) /* (PIOA) Select A Register */
#وصف_ڪريو AT91C_PIOA_PPUSR        ( ( AT91_REG * ) 0xFFFFF468 ) /* (PIOA) Pad Pull-up Status Register */
#وصف_ڪريو AT91C_PIOA_ODSR         ( ( AT91_REG * ) 0xFFFFF438 ) /* (PIOA) Output Data Status Register */
#وصف_ڪريو AT91C_PIOA_SODR         ( ( AT91_REG * ) 0xFFFFF430 ) /* (PIOA) Set Output Data Register */
#وصف_ڪريو AT91C_PIOA_IFSR         ( ( AT91_REG * ) 0xFFFFF428 ) /* (PIOA) Input Filter Status Register */
#وصف_ڪريو AT91C_PIOA_IFER         ( ( AT91_REG * ) 0xFFFFF420 ) /* (PIOA) Input Filter Enable Register */
#وصف_ڪريو AT91C_PIOA_OSR          ( ( AT91_REG * ) 0xFFFFF418 ) /* (PIOA) Output Status Register */
#وصف_ڪريو AT91C_PIOA_IDR          ( ( AT91_REG * ) 0xFFFFF444 ) /* (PIOA) Interrupt Disable Register */
#وصف_ڪريو AT91C_PIOA_PDSR         ( ( AT91_REG * ) 0xFFFFF43C ) /* (PIOA) Pin Data Status Register */
#وصف_ڪريو AT91C_PIOA_CODR         ( ( AT91_REG * ) 0xFFFFF434 ) /* (PIOA) Clear Output Data Register */
#وصف_ڪريو AT91C_PIOA_OWSR         ( ( AT91_REG * ) 0xFFFFF4A8 ) /* (PIOA) Output Write Status Register */
#وصف_ڪريو AT91C_PIOA_OWER         ( ( AT91_REG * ) 0xFFFFF4A0 ) /* (PIOA) Output Write Enable Register */
/* ========== Register definition for CKGR peripheral ========== */
#وصف_ڪريو AT91C_CKGR_PLLR         ( ( AT91_REG * ) 0xFFFFFC2C ) /* (CKGR) PLL Register */
#وصف_ڪريو AT91C_CKGR_MCFR         ( ( AT91_REG * ) 0xFFFFFC24 ) /* (CKGR) Main Clock  Frequency Register */
#وصف_ڪريو AT91C_CKGR_MOR          ( ( AT91_REG * ) 0xFFFFFC20 ) /* (CKGR) Main Oscillator Register */
/* ========== Register definition for PMC peripheral ========== */
#وصف_ڪريو AT91C_PMC_SCSR          ( ( AT91_REG * ) 0xFFFFFC08 ) /* (PMC) System Clock Status Register */
#وصف_ڪريو AT91C_PMC_SCER          ( ( AT91_REG * ) 0xFFFFFC00 ) /* (PMC) System Clock Enable Register */
#وصف_ڪريو AT91C_PMC_IMR           ( ( AT91_REG * ) 0xFFFFFC6C ) /* (PMC) Interrupt Mask Register */
#وصف_ڪريو AT91C_PMC_IDR           ( ( AT91_REG * ) 0xFFFFFC64 ) /* (PMC) Interrupt Disable Register */
#وصف_ڪريو AT91C_PMC_PCDR          ( ( AT91_REG * ) 0xFFFFFC14 ) /* (PMC) Peripheral Clock Disable Register */
#وصف_ڪريو AT91C_PMC_SCDR          ( ( AT91_REG * ) 0xFFFFFC04 ) /* (PMC) System Clock Disable Register */
#وصف_ڪريو AT91C_PMC_SR            ( ( AT91_REG * ) 0xFFFFFC68 ) /* (PMC) Status Register */
#وصف_ڪريو AT91C_PMC_IER           ( ( AT91_REG * ) 0xFFFFFC60 ) /* (PMC) Interrupt Enable Register */
#وصف_ڪريو AT91C_PMC_MCKR          ( ( AT91_REG * ) 0xFFFFFC30 ) /* (PMC) Master Clock Register */
#وصف_ڪريو AT91C_PMC_MOR           ( ( AT91_REG * ) 0xFFFFFC20 ) /* (PMC) Main Oscillator Register */
#وصف_ڪريو AT91C_PMC_PCER          ( ( AT91_REG * ) 0xFFFFFC10 ) /* (PMC) Peripheral Clock Enable Register */
#وصف_ڪريو AT91C_PMC_PCSR          ( ( AT91_REG * ) 0xFFFFFC18 ) /* (PMC) Peripheral Clock Status Register */
#وصف_ڪريو AT91C_PMC_PLLR          ( ( AT91_REG * ) 0xFFFFFC2C ) /* (PMC) PLL Register */
#وصف_ڪريو AT91C_PMC_MCFR          ( ( AT91_REG * ) 0xFFFFFC24 ) /* (PMC) Main Clock  Frequency Register */
#وصف_ڪريو AT91C_PMC_PCKR          ( ( AT91_REG * ) 0xFFFFFC40 ) /* (PMC) Programmable Clock Register */
/* ========== Register definition for RSTC peripheral ========== */
#وصف_ڪريو AT91C_RSTC_RSR          ( ( AT91_REG * ) 0xFFFFFD04 ) /* (RSTC) Reset Status Register */
#وصف_ڪريو AT91C_RSTC_RMR          ( ( AT91_REG * ) 0xFFFFFD08 ) /* (RSTC) Reset Mode Register */
#وصف_ڪريو AT91C_RSTC_RCR          ( ( AT91_REG * ) 0xFFFFFD00 ) /* (RSTC) Reset Control Register */
/* ========== Register definition for RTTC peripheral ========== */
#وصف_ڪريو AT91C_RTTC_RTSR         ( ( AT91_REG * ) 0xFFFFFD2C ) /* (RTTC) Real-time Status Register */
#وصف_ڪريو AT91C_RTTC_RTAR         ( ( AT91_REG * ) 0xFFFFFD24 ) /* (RTTC) Real-time Alarm Register */
#وصف_ڪريو AT91C_RTTC_RTVR         ( ( AT91_REG * ) 0xFFFFFD28 ) /* (RTTC) Real-time Value Register */
#وصف_ڪريو AT91C_RTTC_RTMR         ( ( AT91_REG * ) 0xFFFFFD20 ) /* (RTTC) Real-time Mode Register */
/* ========== Register definition for PITC peripheral ========== */
#وصف_ڪريو AT91C_PITC_PIIR         ( ( AT91_REG * ) 0xFFFFFD3C ) /* (PITC) Period Interval Image Register */
#وصف_ڪريو AT91C_PITC_PISR         ( ( AT91_REG * ) 0xFFFFFD34 ) /* (PITC) Period Interval Status Register */
#وصف_ڪريو AT91C_PITC_PIVR         ( ( AT91_REG * ) 0xFFFFFD38 ) /* (PITC) Period Interval Value Register */
#وصف_ڪريو AT91C_PITC_PIMR         ( ( AT91_REG * ) 0xFFFFFD30 ) /* (PITC) Period Interval Mode Register */
/* ========== Register definition for WDTC peripheral ========== */
#وصف_ڪريو AT91C_WDTC_WDMR         ( ( AT91_REG * ) 0xFFFFFD44 ) /* (WDTC) Watchdog Mode Register */
#وصف_ڪريو AT91C_WDTC_WDSR         ( ( AT91_REG * ) 0xFFFFFD48 ) /* (WDTC) Watchdog Status Register */
#وصف_ڪريو AT91C_WDTC_WDCR         ( ( AT91_REG * ) 0xFFFFFD40 ) /* (WDTC) Watchdog Control Register */
/* ========== Register definition for MC peripheral ========== */
#وصف_ڪريو AT91C_MC_FCR            ( ( AT91_REG * ) 0xFFFFFF64 ) /* (MC) MC Flash Command Register */
#وصف_ڪريو AT91C_MC_ASR            ( ( AT91_REG * ) 0xFFFFFF04 ) /* (MC) MC Abort Status Register */
#وصف_ڪريو AT91C_MC_FSR            ( ( AT91_REG * ) 0xFFFFFF68 ) /* (MC) MC Flash Status Register */
#وصف_ڪريو AT91C_MC_FMR            ( ( AT91_REG * ) 0xFFFFFF60 ) /* (MC) MC Flash Mode Register */
#وصف_ڪريو AT91C_MC_AASR           ( ( AT91_REG * ) 0xFFFFFF08 ) /* (MC) MC Abort Address Status Register */
#وصف_ڪريو AT91C_MC_RCR            ( ( AT91_REG * ) 0xFFFFFF00 ) /* (MC) MC Remap Control Register */
/* ========== Register definition for PDC_SPI peripheral ========== */
#وصف_ڪريو AT91C_SPI_PTCR          ( ( AT91_REG * ) 0xFFFE0120 ) /* (PDC_SPI) PDC Transfer Control Register */
#وصف_ڪريو AT91C_SPI_TNPR          ( ( AT91_REG * ) 0xFFFE0118 ) /* (PDC_SPI) Transmit Next Pointer Register */
#وصف_ڪريو AT91C_SPI_RNPR          ( ( AT91_REG * ) 0xFFFE0110 ) /* (PDC_SPI) Receive Next Pointer Register */
#وصف_ڪريو AT91C_SPI_TPR           ( ( AT91_REG * ) 0xFFFE0108 ) /* (PDC_SPI) Transmit Pointer Register */
#وصف_ڪريو AT91C_SPI_RPR           ( ( AT91_REG * ) 0xFFFE0100 ) /* (PDC_SPI) Receive Pointer Register */
#وصف_ڪريو AT91C_SPI_PTSR          ( ( AT91_REG * ) 0xFFFE0124 ) /* (PDC_SPI) PDC Transfer Status Register */
#وصف_ڪريو AT91C_SPI_TNCR          ( ( AT91_REG * ) 0xFFFE011C ) /* (PDC_SPI) Transmit Next Counter Register */
#وصف_ڪريو AT91C_SPI_RNCR          ( ( AT91_REG * ) 0xFFFE0114 ) /* (PDC_SPI) Receive Next Counter Register */
#وصف_ڪريو AT91C_SPI_TCR           ( ( AT91_REG * ) 0xFFFE010C ) /* (PDC_SPI) Transmit Counter Register */
#وصف_ڪريو AT91C_SPI_RCR           ( ( AT91_REG * ) 0xFFFE0104 ) /* (PDC_SPI) Receive Counter Register */
/* ========== Register definition for SPI peripheral ========== */
#وصف_ڪريو AT91C_SPI_CSR           ( ( AT91_REG * ) 0xFFFE0030 ) /* (SPI) Chip Select Register */
#وصف_ڪريو AT91C_SPI_IDR           ( ( AT91_REG * ) 0xFFFE0018 ) /* (SPI) Interrupt Disable Register */
#وصف_ڪريو AT91C_SPI_SR            ( ( AT91_REG * ) 0xFFFE0010 ) /* (SPI) Status Register */
#وصف_ڪريو AT91C_SPI_RDR           ( ( AT91_REG * ) 0xFFFE0008 ) /* (SPI) Receive Data Register */
#وصف_ڪريو AT91C_SPI_CR            ( ( AT91_REG * ) 0xFFFE0000 ) /* (SPI) Control Register */
#وصف_ڪريو AT91C_SPI_IMR           ( ( AT91_REG * ) 0xFFFE001C ) /* (SPI) Interrupt Mask Register */
#وصف_ڪريو AT91C_SPI_IER           ( ( AT91_REG * ) 0xFFFE0014 ) /* (SPI) Interrupt Enable Register */
#وصف_ڪريو AT91C_SPI_TDR           ( ( AT91_REG * ) 0xFFFE000C ) /* (SPI) Transmit Data Register */
#وصف_ڪريو AT91C_SPI_MR            ( ( AT91_REG * ) 0xFFFE0004 ) /* (SPI) Mode Register */
/* ========== Register definition for PDC_ADC peripheral ========== */
#وصف_ڪريو AT91C_ADC_PTCR          ( ( AT91_REG * ) 0xFFFD8120 ) /* (PDC_ADC) PDC Transfer Control Register */
#وصف_ڪريو AT91C_ADC_TNPR          ( ( AT91_REG * ) 0xFFFD8118 ) /* (PDC_ADC) Transmit Next Pointer Register */
#وصف_ڪريو AT91C_ADC_RNPR          ( ( AT91_REG * ) 0xFFFD8110 ) /* (PDC_ADC) Receive Next Pointer Register */
#وصف_ڪريو AT91C_ADC_TPR           ( ( AT91_REG * ) 0xFFFD8108 ) /* (PDC_ADC) Transmit Pointer Register */
#وصف_ڪريو AT91C_ADC_RPR           ( ( AT91_REG * ) 0xFFFD8100 ) /* (PDC_ADC) Receive Pointer Register */
#وصف_ڪريو AT91C_ADC_PTSR          ( ( AT91_REG * ) 0xFFFD8124 ) /* (PDC_ADC) PDC Transfer Status Register */
#وصف_ڪريو AT91C_ADC_TNCR          ( ( AT91_REG * ) 0xFFFD811C ) /* (PDC_ADC) Transmit Next Counter Register */
#وصف_ڪريو AT91C_ADC_RNCR          ( ( AT91_REG * ) 0xFFFD8114 ) /* (PDC_ADC) Receive Next Counter Register */
#وصف_ڪريو AT91C_ADC_TCR           ( ( AT91_REG * ) 0xFFFD810C ) /* (PDC_ADC) Transmit Counter Register */
#وصف_ڪريو AT91C_ADC_RCR           ( ( AT91_REG * ) 0xFFFD8104 ) /* (PDC_ADC) Receive Counter Register */
/* ========== Register definition for ADC peripheral ========== */
#وصف_ڪريو AT91C_ADC_IMR           ( ( AT91_REG * ) 0xFFFD802C ) /* (ADC) ADC Interrupt Mask Register */
#وصف_ڪريو AT91C_ADC_CDR4          ( ( AT91_REG * ) 0xFFFD8040 ) /* (ADC) ADC Channel Data Register 4 */
#وصف_ڪريو AT91C_ADC_CDR2          ( ( AT91_REG * ) 0xFFFD8038 ) /* (ADC) ADC Channel Data Register 2 */
#وصف_ڪريو AT91C_ADC_CDR0          ( ( AT91_REG * ) 0xFFFD8030 ) /* (ADC) ADC Channel Data Register 0 */
#وصف_ڪريو AT91C_ADC_CDR7          ( ( AT91_REG * ) 0xFFFD804C ) /* (ADC) ADC Channel Data Register 7 */
#وصف_ڪريو AT91C_ADC_CDR1          ( ( AT91_REG * ) 0xFFFD8034 ) /* (ADC) ADC Channel Data Register 1 */
#وصف_ڪريو AT91C_ADC_CDR3          ( ( AT91_REG * ) 0xFFFD803C ) /* (ADC) ADC Channel Data Register 3 */
#وصف_ڪريو AT91C_ADC_CDR5          ( ( AT91_REG * ) 0xFFFD8044 ) /* (ADC) ADC Channel Data Register 5 */
#وصف_ڪريو AT91C_ADC_MR            ( ( AT91_REG * ) 0xFFFD8004 ) /* (ADC) ADC Mode Register */
#وصف_ڪريو AT91C_ADC_CDR6          ( ( AT91_REG * ) 0xFFFD8048 ) /* (ADC) ADC Channel Data Register 6 */
#وصف_ڪريو AT91C_ADC_CR            ( ( AT91_REG * ) 0xFFFD8000 ) /* (ADC) ADC Control Register */
#وصف_ڪريو AT91C_ADC_CHER          ( ( AT91_REG * ) 0xFFFD8010 ) /* (ADC) ADC Channel Enable Register */
#وصف_ڪريو AT91C_ADC_CHSR          ( ( AT91_REG * ) 0xFFFD8018 ) /* (ADC) ADC Channel Status Register */
#وصف_ڪريو AT91C_ADC_IER           ( ( AT91_REG * ) 0xFFFD8024 ) /* (ADC) ADC Interrupt Enable Register */
#وصف_ڪريو AT91C_ADC_SR            ( ( AT91_REG * ) 0xFFFD801C ) /* (ADC) ADC Status Register */
#وصف_ڪريو AT91C_ADC_CHDR          ( ( AT91_REG * ) 0xFFFD8014 ) /* (ADC) ADC Channel Disable Register */
#وصف_ڪريو AT91C_ADC_IDR           ( ( AT91_REG * ) 0xFFFD8028 ) /* (ADC) ADC Interrupt Disable Register */
#وصف_ڪريو AT91C_ADC_LCDR          ( ( AT91_REG * ) 0xFFFD8020 ) /* (ADC) ADC Last Converted Data Register */
/* ========== Register definition for PDC_SSC peripheral ========== */
#وصف_ڪريو AT91C_SSC_PTCR          ( ( AT91_REG * ) 0xFFFD4120 ) /* (PDC_SSC) PDC Transfer Control Register */
#وصف_ڪريو AT91C_SSC_TNPR          ( ( AT91_REG * ) 0xFFFD4118 ) /* (PDC_SSC) Transmit Next Pointer Register */
#وصف_ڪريو AT91C_SSC_RNPR          ( ( AT91_REG * ) 0xFFFD4110 ) /* (PDC_SSC) Receive Next Pointer Register */
#وصف_ڪريو AT91C_SSC_TPR           ( ( AT91_REG * ) 0xFFFD4108 ) /* (PDC_SSC) Transmit Pointer Register */
#وصف_ڪريو AT91C_SSC_RPR           ( ( AT91_REG * ) 0xFFFD4100 ) /* (PDC_SSC) Receive Pointer Register */
#وصف_ڪريو AT91C_SSC_PTSR          ( ( AT91_REG * ) 0xFFFD4124 ) /* (PDC_SSC) PDC Transfer Status Register */
#وصف_ڪريو AT91C_SSC_TNCR          ( ( AT91_REG * ) 0xFFFD411C ) /* (PDC_SSC) Transmit Next Counter Register */
#وصف_ڪريو AT91C_SSC_RNCR          ( ( AT91_REG * ) 0xFFFD4114 ) /* (PDC_SSC) Receive Next Counter Register */
#وصف_ڪريو AT91C_SSC_TCR           ( ( AT91_REG * ) 0xFFFD410C ) /* (PDC_SSC) Transmit Counter Register */
#وصف_ڪريو AT91C_SSC_RCR           ( ( AT91_REG * ) 0xFFFD4104 ) /* (PDC_SSC) Receive Counter Register */
/* ========== Register definition for SSC peripheral ========== */
#وصف_ڪريو AT91C_SSC_RFMR          ( ( AT91_REG * ) 0xFFFD4014 ) /* (SSC) Receive Frame Mode Register */
#وصف_ڪريو AT91C_SSC_CMR           ( ( AT91_REG * ) 0xFFFD4004 ) /* (SSC) Clock Mode Register */
#وصف_ڪريو AT91C_SSC_IDR           ( ( AT91_REG * ) 0xFFFD4048 ) /* (SSC) Interrupt Disable Register */
#وصف_ڪريو AT91C_SSC_SR            ( ( AT91_REG * ) 0xFFFD4040 ) /* (SSC) Status Register */
#وصف_ڪريو AT91C_SSC_RC0R          ( ( AT91_REG * ) 0xFFFD4038 ) /* (SSC) Receive Compare 0 Register */
#وصف_ڪريو AT91C_SSC_RSHR          ( ( AT91_REG * ) 0xFFFD4030 ) /* (SSC) Receive Sync Holding Register */
#وصف_ڪريو AT91C_SSC_RHR           ( ( AT91_REG * ) 0xFFFD4020 ) /* (SSC) Receive Holding Register */
#وصف_ڪريو AT91C_SSC_TCMR          ( ( AT91_REG * ) 0xFFFD4018 ) /* (SSC) Transmit Clock Mode Register */
#وصف_ڪريو AT91C_SSC_RCMR          ( ( AT91_REG * ) 0xFFFD4010 ) /* (SSC) Receive Clock ModeRegister */
#وصف_ڪريو AT91C_SSC_CR            ( ( AT91_REG * ) 0xFFFD4000 ) /* (SSC) Control Register */
#وصف_ڪريو AT91C_SSC_IMR           ( ( AT91_REG * ) 0xFFFD404C ) /* (SSC) Interrupt Mask Register */
#وصف_ڪريو AT91C_SSC_IER           ( ( AT91_REG * ) 0xFFFD4044 ) /* (SSC) Interrupt Enable Register */
#وصف_ڪريو AT91C_SSC_RC1R          ( ( AT91_REG * ) 0xFFFD403C ) /* (SSC) Receive Compare 1 Register */
#وصف_ڪريو AT91C_SSC_TSHR          ( ( AT91_REG * ) 0xFFFD4034 ) /* (SSC) Transmit Sync Holding Register */
#وصف_ڪريو AT91C_SSC_THR           ( ( AT91_REG * ) 0xFFFD4024 ) /* (SSC) Transmit Holding Register */
#وصف_ڪريو AT91C_SSC_TFMR          ( ( AT91_REG * ) 0xFFFD401C ) /* (SSC) Transmit Frame Mode Register */
/* ========== Register definition for PDC_US1 peripheral ========== */
#وصف_ڪريو AT91C_US1_PTSR          ( ( AT91_REG * ) 0xFFFC4124 ) /* (PDC_US1) PDC Transfer Status Register */
#وصف_ڪريو AT91C_US1_TNCR          ( ( AT91_REG * ) 0xFFFC411C ) /* (PDC_US1) Transmit Next Counter Register */
#وصف_ڪريو AT91C_US1_RNCR          ( ( AT91_REG * ) 0xFFFC4114 ) /* (PDC_US1) Receive Next Counter Register */
#وصف_ڪريو AT91C_US1_TCR           ( ( AT91_REG * ) 0xFFFC410C ) /* (PDC_US1) Transmit Counter Register */
#وصف_ڪريو AT91C_US1_RCR           ( ( AT91_REG * ) 0xFFFC4104 ) /* (PDC_US1) Receive Counter Register */
#وصف_ڪريو AT91C_US1_PTCR          ( ( AT91_REG * ) 0xFFFC4120 ) /* (PDC_US1) PDC Transfer Control Register */
#وصف_ڪريو AT91C_US1_TNPR          ( ( AT91_REG * ) 0xFFFC4118 ) /* (PDC_US1) Transmit Next Pointer Register */
#وصف_ڪريو AT91C_US1_RNPR          ( ( AT91_REG * ) 0xFFFC4110 ) /* (PDC_US1) Receive Next Pointer Register */
#وصف_ڪريو AT91C_US1_TPR           ( ( AT91_REG * ) 0xFFFC4108 ) /* (PDC_US1) Transmit Pointer Register */
#وصف_ڪريو AT91C_US1_RPR           ( ( AT91_REG * ) 0xFFFC4100 ) /* (PDC_US1) Receive Pointer Register */
/* ========== Register definition for US1 peripheral ========== */
#وصف_ڪريو AT91C_US1_XXR           ( ( AT91_REG * ) 0xFFFC4048 ) /* (US1) XON_XOFF Register */
#وصف_ڪريو AT91C_US1_RHR           ( ( AT91_REG * ) 0xFFFC4018 ) /* (US1) Receiver Holding Register */
#وصف_ڪريو AT91C_US1_IMR           ( ( AT91_REG * ) 0xFFFC4010 ) /* (US1) Interrupt Mask Register */
#وصف_ڪريو AT91C_US1_IER           ( ( AT91_REG * ) 0xFFFC4008 ) /* (US1) Interrupt Enable Register */
#وصف_ڪريو AT91C_US1_CR            ( ( AT91_REG * ) 0xFFFC4000 ) /* (US1) Control Register */
#وصف_ڪريو AT91C_US1_RTOR          ( ( AT91_REG * ) 0xFFFC4024 ) /* (US1) Receiver Time-out Register */
#وصف_ڪريو AT91C_US1_THR           ( ( AT91_REG * ) 0xFFFC401C ) /* (US1) Transmitter Holding Register */
#وصف_ڪريو AT91C_US1_CSR           ( ( AT91_REG * ) 0xFFFC4014 ) /* (US1) Channel Status Register */
#وصف_ڪريو AT91C_US1_IDR           ( ( AT91_REG * ) 0xFFFC400C ) /* (US1) Interrupt Disable Register */
#وصف_ڪريو AT91C_US1_FIDI          ( ( AT91_REG * ) 0xFFFC4040 ) /* (US1) FI_DI_Ratio Register */
#وصف_ڪريو AT91C_US1_BRGR          ( ( AT91_REG * ) 0xFFFC4020 ) /* (US1) Baud Rate Generator Register */
#وصف_ڪريو AT91C_US1_TTGR          ( ( AT91_REG * ) 0xFFFC4028 ) /* (US1) Transmitter Time-guard Register */
#وصف_ڪريو AT91C_US1_IF            ( ( AT91_REG * ) 0xFFFC404C ) /* (US1) IRDA_FILTER Register */
#وصف_ڪريو AT91C_US1_NER           ( ( AT91_REG * ) 0xFFFC4044 ) /* (US1) Nb Errors Register */
#وصف_ڪريو AT91C_US1_MR            ( ( AT91_REG * ) 0xFFFC4004 ) /* (US1) Mode Register */
/* ========== Register definition for PDC_US0 peripheral ========== */
#وصف_ڪريو AT91C_US0_PTCR          ( ( AT91_REG * ) 0xFFFC0120 ) /* (PDC_US0) PDC Transfer Control Register */
#وصف_ڪريو AT91C_US0_TNPR          ( ( AT91_REG * ) 0xFFFC0118 ) /* (PDC_US0) Transmit Next Pointer Register */
#وصف_ڪريو AT91C_US0_RNPR          ( ( AT91_REG * ) 0xFFFC0110 ) /* (PDC_US0) Receive Next Pointer Register */
#وصف_ڪريو AT91C_US0_TPR           ( ( AT91_REG * ) 0xFFFC0108 ) /* (PDC_US0) Transmit Pointer Register */
#وصف_ڪريو AT91C_US0_RPR           ( ( AT91_REG * ) 0xFFFC0100 ) /* (PDC_US0) Receive Pointer Register */
#وصف_ڪريو AT91C_US0_PTSR          ( ( AT91_REG * ) 0xFFFC0124 ) /* (PDC_US0) PDC Transfer Status Register */
#وصف_ڪريو AT91C_US0_TNCR          ( ( AT91_REG * ) 0xFFFC011C ) /* (PDC_US0) Transmit Next Counter Register */
#وصف_ڪريو AT91C_US0_RNCR          ( ( AT91_REG * ) 0xFFFC0114 ) /* (PDC_US0) Receive Next Counter Register */
#وصف_ڪريو AT91C_US0_TCR           ( ( AT91_REG * ) 0xFFFC010C ) /* (PDC_US0) Transmit Counter Register */
#وصف_ڪريو AT91C_US0_RCR           ( ( AT91_REG * ) 0xFFFC0104 ) /* (PDC_US0) Receive Counter Register */
/* ========== Register definition for US0 peripheral ========== */
#وصف_ڪريو AT91C_US0_TTGR          ( ( AT91_REG * ) 0xFFFC0028 ) /* (US0) Transmitter Time-guard Register */
#وصف_ڪريو AT91C_US0_BRGR          ( ( AT91_REG * ) 0xFFFC0020 ) /* (US0) Baud Rate Generator Register */
#وصف_ڪريو AT91C_US0_RHR           ( ( AT91_REG * ) 0xFFFC0018 ) /* (US0) Receiver Holding Register */
#وصف_ڪريو AT91C_US0_IMR           ( ( AT91_REG * ) 0xFFFC0010 ) /* (US0) Interrupt Mask Register */
#وصف_ڪريو AT91C_US0_NER           ( ( AT91_REG * ) 0xFFFC0044 ) /* (US0) Nb Errors Register */
#وصف_ڪريو AT91C_US0_RTOR          ( ( AT91_REG * ) 0xFFFC0024 ) /* (US0) Receiver Time-out Register */
#وصف_ڪريو AT91C_US0_XXR           ( ( AT91_REG * ) 0xFFFC0048 ) /* (US0) XON_XOFF Register */
#وصف_ڪريو AT91C_US0_FIDI          ( ( AT91_REG * ) 0xFFFC0040 ) /* (US0) FI_DI_Ratio Register */
#وصف_ڪريو AT91C_US0_CR            ( ( AT91_REG * ) 0xFFFC0000 ) /* (US0) Control Register */
#وصف_ڪريو AT91C_US0_IER           ( ( AT91_REG * ) 0xFFFC0008 ) /* (US0) Interrupt Enable Register */
#وصف_ڪريو AT91C_US0_IF            ( ( AT91_REG * ) 0xFFFC004C ) /* (US0) IRDA_FILTER Register */
#وصف_ڪريو AT91C_US0_MR            ( ( AT91_REG * ) 0xFFFC0004 ) /* (US0) Mode Register */
#وصف_ڪريو AT91C_US0_IDR           ( ( AT91_REG * ) 0xFFFC000C ) /* (US0) Interrupt Disable Register */
#وصف_ڪريو AT91C_US0_CSR           ( ( AT91_REG * ) 0xFFFC0014 ) /* (US0) Channel Status Register */
#وصف_ڪريو AT91C_US0_THR           ( ( AT91_REG * ) 0xFFFC001C ) /* (US0) Transmitter Holding Register */
/* ========== Register definition for TWI peripheral ========== */
#وصف_ڪريو AT91C_TWI_RHR           ( ( AT91_REG * ) 0xFFFB8030 ) /* (TWI) Receive Holding Register */
#وصف_ڪريو AT91C_TWI_IDR           ( ( AT91_REG * ) 0xFFFB8028 ) /* (TWI) Interrupt Disable Register */
#وصف_ڪريو AT91C_TWI_SR            ( ( AT91_REG * ) 0xFFFB8020 ) /* (TWI) Status Register */
#وصف_ڪريو AT91C_TWI_CWGR          ( ( AT91_REG * ) 0xFFFB8010 ) /* (TWI) Clock Waveform Generator Register */
#وصف_ڪريو AT91C_TWI_SMR           ( ( AT91_REG * ) 0xFFFB8008 ) /* (TWI) Slave Mode Register */
#وصف_ڪريو AT91C_TWI_CR            ( ( AT91_REG * ) 0xFFFB8000 ) /* (TWI) Control Register */
#وصف_ڪريو AT91C_TWI_THR           ( ( AT91_REG * ) 0xFFFB8034 ) /* (TWI) Transmit Holding Register */
#وصف_ڪريو AT91C_TWI_IMR           ( ( AT91_REG * ) 0xFFFB802C ) /* (TWI) Interrupt Mask Register */
#وصف_ڪريو AT91C_TWI_IER           ( ( AT91_REG * ) 0xFFFB8024 ) /* (TWI) Interrupt Enable Register */
#وصف_ڪريو AT91C_TWI_IADR          ( ( AT91_REG * ) 0xFFFB800C ) /* (TWI) Internal Address Register */
#وصف_ڪريو AT91C_TWI_MMR           ( ( AT91_REG * ) 0xFFFB8004 ) /* (TWI) Master Mode Register */
/* ========== Register definition for TC2 peripheral ========== */
#وصف_ڪريو AT91C_TC2_IMR           ( ( AT91_REG * ) 0xFFFA00AC ) /* (TC2) Interrupt Mask Register */
#وصف_ڪريو AT91C_TC2_IER           ( ( AT91_REG * ) 0xFFFA00A4 ) /* (TC2) Interrupt Enable Register */
#وصف_ڪريو AT91C_TC2_RC            ( ( AT91_REG * ) 0xFFFA009C ) /* (TC2) Register C */
#وصف_ڪريو AT91C_TC2_RA            ( ( AT91_REG * ) 0xFFFA0094 ) /* (TC2) Register A */
#وصف_ڪريو AT91C_TC2_CMR           ( ( AT91_REG * ) 0xFFFA0084 ) /* (TC2) Channel Mode Register (Capture Mode / Waveform Mode) */
#وصف_ڪريو AT91C_TC2_IDR           ( ( AT91_REG * ) 0xFFFA00A8 ) /* (TC2) Interrupt Disable Register */
#وصف_ڪريو AT91C_TC2_SR            ( ( AT91_REG * ) 0xFFFA00A0 ) /* (TC2) Status Register */
#وصف_ڪريو AT91C_TC2_RB            ( ( AT91_REG * ) 0xFFFA0098 ) /* (TC2) Register B */
#وصف_ڪريو AT91C_TC2_CV            ( ( AT91_REG * ) 0xFFFA0090 ) /* (TC2) Counter Value */
#وصف_ڪريو AT91C_TC2_CCR           ( ( AT91_REG * ) 0xFFFA0080 ) /* (TC2) Channel Control Register */
/* ========== Register definition for TC1 peripheral ========== */
#وصف_ڪريو AT91C_TC1_IMR           ( ( AT91_REG * ) 0xFFFA006C ) /* (TC1) Interrupt Mask Register */
#وصف_ڪريو AT91C_TC1_IER           ( ( AT91_REG * ) 0xFFFA0064 ) /* (TC1) Interrupt Enable Register */
#وصف_ڪريو AT91C_TC1_RC            ( ( AT91_REG * ) 0xFFFA005C ) /* (TC1) Register C */
#وصف_ڪريو AT91C_TC1_RA            ( ( AT91_REG * ) 0xFFFA0054 ) /* (TC1) Register A */
#وصف_ڪريو AT91C_TC1_CMR           ( ( AT91_REG * ) 0xFFFA0044 ) /* (TC1) Channel Mode Register (Capture Mode / Waveform Mode) */
#وصف_ڪريو AT91C_TC1_IDR           ( ( AT91_REG * ) 0xFFFA0068 ) /* (TC1) Interrupt Disable Register */
#وصف_ڪريو AT91C_TC1_SR            ( ( AT91_REG * ) 0xFFFA0060 ) /* (TC1) Status Register */
#وصف_ڪريو AT91C_TC1_RB            ( ( AT91_REG * ) 0xFFFA0058 ) /* (TC1) Register B */
#وصف_ڪريو AT91C_TC1_CV            ( ( AT91_REG * ) 0xFFFA0050 ) /* (TC1) Counter Value */
#وصف_ڪريو AT91C_TC1_CCR           ( ( AT91_REG * ) 0xFFFA0040 ) /* (TC1) Channel Control Register */
/* ========== Register definition for TC0 peripheral ========== */
#وصف_ڪريو AT91C_TC0_IMR           ( ( AT91_REG * ) 0xFFFA002C ) /* (TC0) Interrupt Mask Register */
#وصف_ڪريو AT91C_TC0_IER           ( ( AT91_REG * ) 0xFFFA0024 ) /* (TC0) Interrupt Enable Register */
#وصف_ڪريو AT91C_TC0_RC            ( ( AT91_REG * ) 0xFFFA001C ) /* (TC0) Register C */
#وصف_ڪريو AT91C_TC0_RA            ( ( AT91_REG * ) 0xFFFA0014 ) /* (TC0) Register A */
#وصف_ڪريو AT91C_TC0_CMR           ( ( AT91_REG * ) 0xFFFA0004 ) /* (TC0) Channel Mode Register (Capture Mode / Waveform Mode) */
#وصف_ڪريو AT91C_TC0_IDR           ( ( AT91_REG * ) 0xFFFA0028 ) /* (TC0) Interrupt Disable Register */
#وصف_ڪريو AT91C_TC0_SR            ( ( AT91_REG * ) 0xFFFA0020 ) /* (TC0) Status Register */
#وصف_ڪريو AT91C_TC0_RB            ( ( AT91_REG * ) 0xFFFA0018 ) /* (TC0) Register B */
#وصف_ڪريو AT91C_TC0_CV            ( ( AT91_REG * ) 0xFFFA0010 ) /* (TC0) Counter Value */
#وصف_ڪريو AT91C_TC0_CCR           ( ( AT91_REG * ) 0xFFFA0000 ) /* (TC0) Channel Control Register */
/* ========== Register definition for TCB peripheral ========== */
#وصف_ڪريو AT91C_TCB_BMR           ( ( AT91_REG * ) 0xFFFA00C4 ) /* (TCB) TC Block Mode Register */
#وصف_ڪريو AT91C_TCB_BCR           ( ( AT91_REG * ) 0xFFFA00C0 ) /* (TCB) TC Block Control Register */
/* ========== Register definition for PWMC_CH3 peripheral ========== */
#وصف_ڪريو AT91C_CH3_CUPDR         ( ( AT91_REG * ) 0xFFFCC270 ) /* (PWMC_CH3) Channel Update Register */
#وصف_ڪريو AT91C_CH3_CPRDR         ( ( AT91_REG * ) 0xFFFCC268 ) /* (PWMC_CH3) Channel Period Register */
#وصف_ڪريو AT91C_CH3_CMR           ( ( AT91_REG * ) 0xFFFCC260 ) /* (PWMC_CH3) Channel Mode Register */
#وصف_ڪريو AT91C_CH3_Reserved      ( ( AT91_REG * ) 0xFFFCC274 ) /* (PWMC_CH3) Reserved */
#وصف_ڪريو AT91C_CH3_CCNTR         ( ( AT91_REG * ) 0xFFFCC26C ) /* (PWMC_CH3) Channel Counter Register */
#وصف_ڪريو AT91C_CH3_CDTYR         ( ( AT91_REG * ) 0xFFFCC264 ) /* (PWMC_CH3) Channel Duty Cycle Register */
/* ========== Register definition for PWMC_CH2 peripheral ========== */
#وصف_ڪريو AT91C_CH2_CUPDR         ( ( AT91_REG * ) 0xFFFCC250 ) /* (PWMC_CH2) Channel Update Register */
#وصف_ڪريو AT91C_CH2_CPRDR         ( ( AT91_REG * ) 0xFFFCC248 ) /* (PWMC_CH2) Channel Period Register */
#وصف_ڪريو AT91C_CH2_CMR           ( ( AT91_REG * ) 0xFFFCC240 ) /* (PWMC_CH2) Channel Mode Register */
#وصف_ڪريو AT91C_CH2_Reserved      ( ( AT91_REG * ) 0xFFFCC254 ) /* (PWMC_CH2) Reserved */
#وصف_ڪريو AT91C_CH2_CCNTR         ( ( AT91_REG * ) 0xFFFCC24C ) /* (PWMC_CH2) Channel Counter Register */
#وصف_ڪريو AT91C_CH2_CDTYR         ( ( AT91_REG * ) 0xFFFCC244 ) /* (PWMC_CH2) Channel Duty Cycle Register */
/* ========== Register definition for PWMC_CH1 peripheral ========== */
#وصف_ڪريو AT91C_CH1_CUPDR         ( ( AT91_REG * ) 0xFFFCC230 ) /* (PWMC_CH1) Channel Update Register */
#وصف_ڪريو AT91C_CH1_CPRDR         ( ( AT91_REG * ) 0xFFFCC228 ) /* (PWMC_CH1) Channel Period Register */
#وصف_ڪريو AT91C_CH1_CMR           ( ( AT91_REG * ) 0xFFFCC220 ) /* (PWMC_CH1) Channel Mode Register */
#وصف_ڪريو AT91C_CH1_Reserved      ( ( AT91_REG * ) 0xFFFCC234 ) /* (PWMC_CH1) Reserved */
#وصف_ڪريو AT91C_CH1_CCNTR         ( ( AT91_REG * ) 0xFFFCC22C ) /* (PWMC_CH1) Channel Counter Register */
#وصف_ڪريو AT91C_CH1_CDTYR         ( ( AT91_REG * ) 0xFFFCC224 ) /* (PWMC_CH1) Channel Duty Cycle Register */
/* ========== Register definition for PWMC_CH0 peripheral ========== */
#وصف_ڪريو AT91C_CH0_CUPDR         ( ( AT91_REG * ) 0xFFFCC210 ) /* (PWMC_CH0) Channel Update Register */
#وصف_ڪريو AT91C_CH0_CPRDR         ( ( AT91_REG * ) 0xFFFCC208 ) /* (PWMC_CH0) Channel Period Register */
#وصف_ڪريو AT91C_CH0_CMR           ( ( AT91_REG * ) 0xFFFCC200 ) /* (PWMC_CH0) Channel Mode Register */
#وصف_ڪريو AT91C_CH0_Reserved      ( ( AT91_REG * ) 0xFFFCC214 ) /* (PWMC_CH0) Reserved */
#وصف_ڪريو AT91C_CH0_CCNTR         ( ( AT91_REG * ) 0xFFFCC20C ) /* (PWMC_CH0) Channel Counter Register */
#وصف_ڪريو AT91C_CH0_CDTYR         ( ( AT91_REG * ) 0xFFFCC204 ) /* (PWMC_CH0) Channel Duty Cycle Register */
/* ========== Register definition for PWMC peripheral ========== */
#وصف_ڪريو AT91C_PWMC_VR           ( ( AT91_REG * ) 0xFFFCC0FC ) /* (PWMC) PWMC Version Register */
#وصف_ڪريو AT91C_PWMC_ISR          ( ( AT91_REG * ) 0xFFFCC01C ) /* (PWMC) PWMC Interrupt Status Register */
#وصف_ڪريو AT91C_PWMC_IDR          ( ( AT91_REG * ) 0xFFFCC014 ) /* (PWMC) PWMC Interrupt Disable Register */
#وصف_ڪريو AT91C_PWMC_SR           ( ( AT91_REG * ) 0xFFFCC00C ) /* (PWMC) PWMC Status Register */
#وصف_ڪريو AT91C_PWMC_ENA          ( ( AT91_REG * ) 0xFFFCC004 ) /* (PWMC) PWMC Enable Register */
#وصف_ڪريو AT91C_PWMC_IMR          ( ( AT91_REG * ) 0xFFFCC018 ) /* (PWMC) PWMC Interrupt Mask Register */
#وصف_ڪريو AT91C_PWMC_MR           ( ( AT91_REG * ) 0xFFFCC000 ) /* (PWMC) PWMC Mode Register */
#وصف_ڪريو AT91C_PWMC_DIS          ( ( AT91_REG * ) 0xFFFCC008 ) /* (PWMC) PWMC Disable Register */
#وصف_ڪريو AT91C_PWMC_IER          ( ( AT91_REG * ) 0xFFFCC010 ) /* (PWMC) PWMC Interrupt Enable Register */
/* ========== Register definition for UDP peripheral ========== */
#وصف_ڪريو AT91C_UDP_ISR           ( ( AT91_REG * ) 0xFFFB001C ) /* (UDP) Interrupt Status Register */
#وصف_ڪريو AT91C_UDP_IDR           ( ( AT91_REG * ) 0xFFFB0014 ) /* (UDP) Interrupt Disable Register */
#وصف_ڪريو AT91C_UDP_GLBSTATE      ( ( AT91_REG * ) 0xFFFB0004 ) /* (UDP) Global State Register */
#وصف_ڪريو AT91C_UDP_FDR           ( ( AT91_REG * ) 0xFFFB0050 ) /* (UDP) Endpoint FIFO Data Register */
#وصف_ڪريو AT91C_UDP_CSR           ( ( AT91_REG * ) 0xFFFB0030 ) /* (UDP) Endpoint Control and Status Register */
#وصف_ڪريو AT91C_UDP_RSTEP         ( ( AT91_REG * ) 0xFFFB0028 ) /* (UDP) Reset Endpoint Register */
#وصف_ڪريو AT91C_UDP_ICR           ( ( AT91_REG * ) 0xFFFB0020 ) /* (UDP) Interrupt Clear Register */
#وصف_ڪريو AT91C_UDP_IMR           ( ( AT91_REG * ) 0xFFFB0018 ) /* (UDP) Interrupt Mask Register */
#وصف_ڪريو AT91C_UDP_IER           ( ( AT91_REG * ) 0xFFFB0010 ) /* (UDP) Interrupt Enable Register */
#وصف_ڪريو AT91C_UDP_FADDR         ( ( AT91_REG * ) 0xFFFB0008 ) /* (UDP) Function Address Register */
#وصف_ڪريو AT91_C_UDP_انگ           ( ( AT91_REG * ) 0xFFFB0000 ) /* (UDP) Frame Number Register */

/* ***************************************************************************** */
/*               PIO DEFINITIONS FOR AT91SAM7S64 */
/* ***************************************************************************** */
#وصف_ڪريو AT91C_PIO_PA0       ( ( بنانشان صحيح ) 1 << 0 )         /* Pin Controlled by PA0 */
#وصف_ڪريو AT91C_PA0_PWM0      ( ( بنانشان صحيح ) AT91C_PIO_PA0 )  /*  PWM Channel 0 */
#وصف_ڪريو AT91C_PA0_TIOA0     ( ( بنانشان صحيح ) AT91C_PIO_PA0 )  /*  Timer Counter 0 Multipurpose Timer I/O Pin A */
#وصف_ڪريو AT91C_PIO_PA1       ( ( بنانشان صحيح ) 1 << 1 )         /* Pin Controlled by PA1 */
#وصف_ڪريو AT91C_PA1_PWM1      ( ( بنانشان صحيح ) AT91C_PIO_PA1 )  /*  PWM Channel 1 */
#وصف_ڪريو AT91C_PA1_TIOB0     ( ( بنانشان صحيح ) AT91C_PIO_PA1 )  /*  Timer Counter 0 Multipurpose Timer I/O Pin B */
#وصف_ڪريو AT91C_PIO_PA10      ( ( بنانشان صحيح ) 1 << 10 )        /* Pin Controlled by PA10 */
#وصف_ڪريو AT91C_PA10_DTXD     ( ( بنانشان صحيح ) AT91C_PIO_PA10 ) /*  DBGU Debug Transmit Data */
#وصف_ڪريو AT91C_PA10_NPCS2    ( ( بنانشان صحيح ) AT91C_PIO_PA10 ) /*  SPI Peripheral Chip Select 2 */
#وصف_ڪريو AT91C_PIO_PA11      ( ( بنانشان صحيح ) 1 << 11 )        /* Pin Controlled by PA11 */
#وصف_ڪريو AT91C_PA11_NPCS0    ( ( بنانشان صحيح ) AT91C_PIO_PA11 ) /*  SPI Peripheral Chip Select 0 */
#وصف_ڪريو AT91C_PA11_PWM0     ( ( بنانشان صحيح ) AT91C_PIO_PA11 ) /*  PWM Channel 0 */
#وصف_ڪريو AT91C_PIO_PA12      ( ( بنانشان صحيح ) 1 << 12 )        /* Pin Controlled by PA12 */
#وصف_ڪريو AT91C_PA12_MISO     ( ( بنانشان صحيح ) AT91C_PIO_PA12 ) /*  SPI Master In Slave */
#وصف_ڪريو AT91C_PA12_PWM1     ( ( بنانشان صحيح ) AT91C_PIO_PA12 ) /*  PWM Channel 1 */
#وصف_ڪريو AT91C_PIO_PA13      ( ( بنانشان صحيح ) 1 << 13 )        /* Pin Controlled by PA13 */
#وصف_ڪريو AT91C_PA13_MOSI     ( ( بنانشان صحيح ) AT91C_PIO_PA13 ) /*  SPI Master Out Slave */
#وصف_ڪريو AT91C_PA13_PWM2     ( ( بنانشان صحيح ) AT91C_PIO_PA13 ) /*  PWM Channel 2 */
#وصف_ڪريو AT91C_PIO_PA14      ( ( بنانشان صحيح ) 1 << 14 )        /* Pin Controlled by PA14 */
#وصف_ڪريو AT91C_PA14_SPCK     ( ( بنانشان صحيح ) AT91C_PIO_PA14 ) /*  SPI Serial Clock */
#وصف_ڪريو AT91C_PA14_PWM3     ( ( بنانشان صحيح ) AT91C_PIO_PA14 ) /*  PWM Channel 3 */
#وصف_ڪريو AT91C_PIO_PA15      ( ( بنانشان صحيح ) 1 << 15 )        /* Pin Controlled by PA15 */
#وصف_ڪريو AT91C_PA15_TF       ( ( بنانشان صحيح ) AT91C_PIO_PA15 ) /*  SSC Transmit Frame Sync */
#وصف_ڪريو AT91C_PA15_TIOA1    ( ( بنانشان صحيح ) AT91C_PIO_PA15 ) /*  Timer Counter 1 Multipurpose Timer I/O Pin A */
#وصف_ڪريو AT91C_PIO_PA16      ( ( بنانشان صحيح ) 1 << 16 )        /* Pin Controlled by PA16 */
#وصف_ڪريو AT91C_PA16_TK       ( ( بنانشان صحيح ) AT91C_PIO_PA16 ) /*  SSC Transmit Clock */
#وصف_ڪريو AT91C_PA16_TIOB1    ( ( بنانشان صحيح ) AT91C_PIO_PA16 ) /*  Timer Counter 1 Multipurpose Timer I/O Pin B */
#وصف_ڪريو AT91C_PIO_PA17      ( ( بنانشان صحيح ) 1 << 17 )        /* Pin Controlled by PA17 */
#وصف_ڪريو AT91C_PA17_TD       ( ( بنانشان صحيح ) AT91C_PIO_PA17 ) /*  SSC Transmit data */
#وصف_ڪريو AT91C_PA17_PCK1     ( ( بنانشان صحيح ) AT91C_PIO_PA17 ) /*  PMC Programmable Clock Output 1 */
#وصف_ڪريو AT91C_PIO_PA18      ( ( بنانشان صحيح ) 1 << 18 )        /* Pin Controlled by PA18 */
#وصف_ڪريو AT91C_PA18_RD       ( ( بنانشان صحيح ) AT91C_PIO_PA18 ) /*  SSC Receive Data */
#وصف_ڪريو AT91C_PA18_PCK2     ( ( بنانشان صحيح ) AT91C_PIO_PA18 ) /*  PMC Programmable Clock Output 2 */
#وصف_ڪريو AT91C_PIO_PA19      ( ( بنانشان صحيح ) 1 << 19 )        /* Pin Controlled by PA19 */
#وصف_ڪريو AT91C_PA19_RK       ( ( بنانشان صحيح ) AT91C_PIO_PA19 ) /*  SSC Receive Clock */
#وصف_ڪريو AT91C_PA19_FIQ      ( ( بنانشان صحيح ) AT91C_PIO_PA19 ) /*  AIC Fast Interrupt Input */
#وصف_ڪريو AT91C_PIO_PA2       ( ( بنانشان صحيح ) 1 << 2 )         /* Pin Controlled by PA2 */
#وصف_ڪريو AT91C_PA2_PWM2      ( ( بنانشان صحيح ) AT91C_PIO_PA2 )  /*  PWM Channel 2 */
#وصف_ڪريو AT91C_PA2_SCK0      ( ( بنانشان صحيح ) AT91C_PIO_PA2 )  /*  USART 0 Serial Clock */
#وصف_ڪريو AT91C_PIO_PA20      ( ( بنانشان صحيح ) 1 << 20 )        /* Pin Controlled by PA20 */
#وصف_ڪريو AT91C_PA20_RF       ( ( بنانشان صحيح ) AT91C_PIO_PA20 ) /*  SSC Receive Frame Sync */
#وصف_ڪريو AT91C_PA20_IRQ0     ( ( بنانشان صحيح ) AT91C_PIO_PA20 ) /*  External Interrupt 0 */
#وصف_ڪريو AT91C_PIO_PA21      ( ( بنانشان صحيح ) 1 << 21 )        /* Pin Controlled by PA21 */
#وصف_ڪريو AT91C_PA21_RXD1     ( ( بنانشان صحيح ) AT91C_PIO_PA21 ) /*  USART 1 Receive Data */
#وصف_ڪريو AT91C_PA21_PCK1     ( ( بنانشان صحيح ) AT91C_PIO_PA21 ) /*  PMC Programmable Clock Output 1 */
#وصف_ڪريو AT91C_PIO_PA22      ( ( بنانشان صحيح ) 1 << 22 )        /* Pin Controlled by PA22 */
#وصف_ڪريو AT91C_PA22_TXD1     ( ( بنانشان صحيح ) AT91C_PIO_PA22 ) /*  USART 1 Transmit Data */
#وصف_ڪريو AT91C_PA22_NPCS3    ( ( بنانشان صحيح ) AT91C_PIO_PA22 ) /*  SPI Peripheral Chip Select 3 */
#وصف_ڪريو AT91C_PIO_PA23      ( ( بنانشان صحيح ) 1 << 23 )        /* Pin Controlled by PA23 */
#وصف_ڪريو AT91C_PA23_SCK1     ( ( بنانشان صحيح ) AT91C_PIO_PA23 ) /*  USART 1 Serial Clock */
#وصف_ڪريو AT91C_PA23_PWM0     ( ( بنانشان صحيح ) AT91C_PIO_PA23 ) /*  PWM Channel 0 */
#وصف_ڪريو AT91C_PIO_PA24      ( ( بنانشان صحيح ) 1 << 24 )        /* Pin Controlled by PA24 */
#وصف_ڪريو AT91C_PA24_RTS1     ( ( بنانشان صحيح ) AT91C_PIO_PA24 ) /*  USART 1 Ready To Send */
#وصف_ڪريو AT91C_PA24_PWM1     ( ( بنانشان صحيح ) AT91C_PIO_PA24 ) /*  PWM Channel 1 */
#وصف_ڪريو AT91C_PIO_PA25      ( ( بنانشان صحيح ) 1 << 25 )        /* Pin Controlled by PA25 */
#وصف_ڪريو AT91C_PA25_CTS1     ( ( بنانشان صحيح ) AT91C_PIO_PA25 ) /*  USART 1 Clear To Send */
#وصف_ڪريو AT91C_PA25_PWM2     ( ( بنانشان صحيح ) AT91C_PIO_PA25 ) /*  PWM Channel 2 */
#وصف_ڪريو AT91C_PIO_PA26      ( ( بنانشان صحيح ) 1 << 26 )        /* Pin Controlled by PA26 */
#وصف_ڪريو AT91C_PA26_DCD1     ( ( بنانشان صحيح ) AT91C_PIO_PA26 ) /*  USART 1 Data Carrier Detect */
#وصف_ڪريو AT91C_PA26_TIOA2    ( ( بنانشان صحيح ) AT91C_PIO_PA26 ) /*  Timer Counter 2 Multipurpose Timer I/O Pin A */
#وصف_ڪريو AT91C_PIO_PA27      ( ( بنانشان صحيح ) 1 << 27 )        /* Pin Controlled by PA27 */
#وصف_ڪريو AT91C_PA27_DTR1     ( ( بنانشان صحيح ) AT91C_PIO_PA27 ) /*  USART 1 Data Terminal ready */
#وصف_ڪريو AT91C_PA27_TIOB2    ( ( بنانشان صحيح ) AT91C_PIO_PA27 ) /*  Timer Counter 2 Multipurpose Timer I/O Pin B */
#وصف_ڪريو AT91C_PIO_PA28      ( ( بنانشان صحيح ) 1 << 28 )        /* Pin Controlled by PA28 */
#وصف_ڪريو AT91C_PA28_DSR1     ( ( بنانشان صحيح ) AT91C_PIO_PA28 ) /*  USART 1 Data Set ready */
#وصف_ڪريو AT91C_PA28_TCLK1    ( ( بنانشان صحيح ) AT91C_PIO_PA28 ) /*  Timer Counter 1 external clock input */
#وصف_ڪريو AT91C_PIO_PA29      ( ( بنانشان صحيح ) 1 << 29 )        /* Pin Controlled by PA29 */
#وصف_ڪريو AT91C_PA29_RI1      ( ( بنانشان صحيح ) AT91C_PIO_PA29 ) /*  USART 1 Ring Indicator */
#وصف_ڪريو AT91C_PA29_TCLK2    ( ( بنانشان صحيح ) AT91C_PIO_PA29 ) /*  Timer Counter 2 external clock input */
#وصف_ڪريو AT91C_PIO_PA3       ( ( بنانشان صحيح ) 1 << 3 )         /* Pin Controlled by PA3 */
#وصف_ڪريو AT91C_PA3_TWD       ( ( بنانشان صحيح ) AT91C_PIO_PA3 )  /*  TWI Two-wire Serial Data */
#وصف_ڪريو AT91C_PA3_NPCS3     ( ( بنانشان صحيح ) AT91C_PIO_PA3 )  /*  SPI Peripheral Chip Select 3 */
#وصف_ڪريو AT91C_PIO_PA30      ( ( بنانشان صحيح ) 1 << 30 )        /* Pin Controlled by PA30 */
#وصف_ڪريو AT91C_PA30_IRQ1     ( ( بنانشان صحيح ) AT91C_PIO_PA30 ) /*  External Interrupt 1 */
#وصف_ڪريو AT91C_PA30_NPCS2    ( ( بنانشان صحيح ) AT91C_PIO_PA30 ) /*  SPI Peripheral Chip Select 2 */
#وصف_ڪريو AT91C_PIO_PA31      ( ( بنانشان صحيح ) 1 << 31 )        /* Pin Controlled by PA31 */
#وصف_ڪريو AT91C_PA31_NPCS1    ( ( بنانشان صحيح ) AT91C_PIO_PA31 ) /*  SPI Peripheral Chip Select 1 */
#وصف_ڪريو AT91C_PA31_PCK2     ( ( بنانشان صحيح ) AT91C_PIO_PA31 ) /*  PMC Programmable Clock Output 2 */
#وصف_ڪريو AT91C_PIO_PA4       ( ( بنانشان صحيح ) 1 << 4 )         /* Pin Controlled by PA4 */
#وصف_ڪريو AT91C_PA4_TWCK      ( ( بنانشان صحيح ) AT91C_PIO_PA4 )  /*  TWI Two-wire Serial Clock */
#وصف_ڪريو AT91C_PA4_TCLK0     ( ( بنانشان صحيح ) AT91C_PIO_PA4 )  /*  Timer Counter 0 external clock input */
#وصف_ڪريو AT91C_PIO_PA5       ( ( بنانشان صحيح ) 1 << 5 )         /* Pin Controlled by PA5 */
#وصف_ڪريو AT91C_PA5_RXD0      ( ( بنانشان صحيح ) AT91C_PIO_PA5 )  /*  USART 0 Receive Data */
#وصف_ڪريو AT91C_PA5_NPCS3     ( ( بنانشان صحيح ) AT91C_PIO_PA5 )  /*  SPI Peripheral Chip Select 3 */
#وصف_ڪريو AT91C_PIO_PA6       ( ( بنانشان صحيح ) 1 << 6 )         /* Pin Controlled by PA6 */
#وصف_ڪريو AT91C_PA6_TXD0      ( ( بنانشان صحيح ) AT91C_PIO_PA6 )  /*  USART 0 Transmit Data */
#وصف_ڪريو AT91C_PA6_PCK0      ( ( بنانشان صحيح ) AT91C_PIO_PA6 )  /*  PMC Programmable Clock Output 0 */
#وصف_ڪريو AT91C_PIO_PA7       ( ( بنانشان صحيح ) 1 << 7 )         /* Pin Controlled by PA7 */
#وصف_ڪريو AT91C_PA7_RTS0      ( ( بنانشان صحيح ) AT91C_PIO_PA7 )  /*  USART 0 Ready To Send */
#وصف_ڪريو AT91C_PA7_PWM3      ( ( بنانشان صحيح ) AT91C_PIO_PA7 )  /*  PWM Channel 3 */
#وصف_ڪريو AT91C_PIO_PA8       ( ( بنانشان صحيح ) 1 << 8 )         /* Pin Controlled by PA8 */
#وصف_ڪريو AT91C_PA8_CTS0      ( ( بنانشان صحيح ) AT91C_PIO_PA8 )  /*  USART 0 Clear To Send */
#وصف_ڪريو AT91C_PA8_ADTRG     ( ( بنانشان صحيح ) AT91C_PIO_PA8 )  /*  ADC External Trigger */
#وصف_ڪريو AT91C_PIO_PA9       ( ( بنانشان صحيح ) 1 << 9 )         /* Pin Controlled by PA9 */
#وصف_ڪريو AT91C_PA9_DRXD      ( ( بنانشان صحيح ) AT91C_PIO_PA9 )  /*  DBGU Debug Receive Data */
#وصف_ڪريو AT91C_PA9_NPCS1     ( ( بنانشان صحيح ) AT91C_PIO_PA9 )  /*  SPI Peripheral Chip Select 1 */

/* ***************************************************************************** */
/*               PERIPHERAL ID DEFINITIONS FOR AT91SAM7S64 */
/* ***************************************************************************** */
#وصف_ڪريو AT91C_ID_FIQ            ( ( بنانشان صحيح ) 0 )  /* Advanced Interrupt Controller (FIQ) */
#وصف_ڪريو AT91C_ID_SYS            ( ( بنانشان صحيح ) 1 )  /* System Peripheral */
#وصف_ڪريو AT91C_ID_PIOA           ( ( بنانشان صحيح ) 2 )  /* Parallel IO Controller */
#وصف_ڪريو AT91C_ID_3_Reserved     ( ( بنانشان صحيح ) 3 )  /* Reserved */
#وصف_ڪريو AT91C_ID_ADC            ( ( بنانشان صحيح ) 4 )  /* Analog-to-Digital Converter */
#وصف_ڪريو AT91C_ID_SPI            ( ( بنانشان صحيح ) 5 )  /* Serial Peripheral Interface */
#وصف_ڪريو AT91C_ID_US0            ( ( بنانشان صحيح ) 6 )  /* USART 0 */
#وصف_ڪريو AT91C_ID_US1            ( ( بنانشان صحيح ) 7 )  /* USART 1 */
#وصف_ڪريو AT91C_ID_SSC            ( ( بنانشان صحيح ) 8 )  /* Serial Synchronous Controller */
#وصف_ڪريو AT91C_ID_TWI            ( ( بنانشان صحيح ) 9 )  /* Two-Wire Interface */
#وصف_ڪريو AT91C_ID_PWMC           ( ( بنانشان صحيح ) 10 ) /* PWM Controller */
#وصف_ڪريو AT91C_ID_UDP            ( ( بنانشان صحيح ) 11 ) /* USB Device Port */
#وصف_ڪريو AT91C_ID_TC0            ( ( بنانشان صحيح ) 12 ) /* Timer Counter 0 */
#وصف_ڪريو AT91C_ID_TC1            ( ( بنانشان صحيح ) 13 ) /* Timer Counter 1 */
#وصف_ڪريو AT91C_ID_TC2            ( ( بنانشان صحيح ) 14 ) /* Timer Counter 2 */
#وصف_ڪريو AT91C_ID_15_Reserved    ( ( بنانشان صحيح ) 15 ) /* Reserved */
#وصف_ڪريو AT91C_ID_16_Reserved    ( ( بنانشان صحيح ) 16 ) /* Reserved */
#وصف_ڪريو AT91C_ID_17_Reserved    ( ( بنانشان صحيح ) 17 ) /* Reserved */
#وصف_ڪريو AT91C_ID_18_Reserved    ( ( بنانشان صحيح ) 18 ) /* Reserved */
#وصف_ڪريو AT91C_ID_19_Reserved    ( ( بنانشان صحيح ) 19 ) /* Reserved */
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
/*               BASE ADDRESS DEFINITIONS FOR AT91SAM7S64 */
/* ***************************************************************************** */
#وصف_ڪريو AT91_C_بنياد_SYSC        ( ( AT91PS_SYSC ) 0xFFFFF000 )    /* (SYSC) Base Address */
#وصف_ڪريو AT91_C_بنياد_AIC         ( ( AT91PS_AIC ) 0xFFFFF000 )     /* (AIC) Base Address */
#وصف_ڪريو AT91_C_بنياد_DBGU        ( ( AT91PS_DBGU ) 0xFFFFF200 )    /* (DBGU) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_DBGU    ( ( AT91PS_PDC ) 0xFFFFF300 )     /* (PDC_DBGU) Base Address */
#وصف_ڪريو AT91_C_بنياد_PIOA        ( ( AT91PS_PIO ) 0xFFFFF400 )     /* (PIOA) Base Address */
#وصف_ڪريو AT91_C_بنياد_CKGR        ( ( AT91PS_CKGR ) 0xFFFFFC20 )    /* (CKGR) Base Address */
#وصف_ڪريو AT91_C_بنياد_PMC         ( ( AT91PS_PMC ) 0xFFFFFC00 )     /* (PMC) Base Address */
#وصف_ڪريو AT91_C_بنياد_RSTC        ( ( AT91PS_RSTC ) 0xFFFFFD00 )    /* (RSTC) Base Address */
#وصف_ڪريو AT91_C_بنياد_RTTC        ( ( AT91PS_RTTC ) 0xFFFFFD20 )    /* (RTTC) Base Address */
#وصف_ڪريو AT91_C_بنياد_PITC        ( ( AT91PS_PITC ) 0xFFFFFD30 )    /* (PITC) Base Address */
#وصف_ڪريو AT91_C_بنياد_WDTC        ( ( AT91PS_WDTC ) 0xFFFFFD40 )    /* (WDTC) Base Address */
#وصف_ڪريو AT91_C_بنياد_MC          ( ( AT91PS_MC ) 0xFFFFFF00 )      /* (MC) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_SPI     ( ( AT91PS_PDC ) 0xFFFE0100 )     /* (PDC_SPI) Base Address */
#وصف_ڪريو AT91_C_بنياد_SPI         ( ( AT91PS_SPI ) 0xFFFE0000 )     /* (SPI) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_ADC     ( ( AT91PS_PDC ) 0xFFFD8100 )     /* (PDC_ADC) Base Address */
#وصف_ڪريو AT91_C_بنياد_ADC         ( ( AT91PS_ADC ) 0xFFFD8000 )     /* (ADC) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_SSC     ( ( AT91PS_PDC ) 0xFFFD4100 )     /* (PDC_SSC) Base Address */
#وصف_ڪريو AT91_C_بنياد_SSC         ( ( AT91PS_SSC ) 0xFFFD4000 )     /* (SSC) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_US1     ( ( AT91PS_PDC ) 0xFFFC4100 )     /* (PDC_US1) Base Address */
#وصف_ڪريو AT91_C_بنياد_US1         ( ( AT91PS_USART ) 0xFFFC4000 )   /* (US1) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_US0     ( ( AT91PS_PDC ) 0xFFFC0100 )     /* (PDC_US0) Base Address */
#وصف_ڪريو AT91_C_بنياد_US0         ( ( AT91PS_USART ) 0xFFFC0000 )   /* (US0) Base Address */
#وصف_ڪريو AT91_C_بنياد_TWI         ( ( AT91PS_TWI ) 0xFFFB8000 )     /* (TWI) Base Address */
#وصف_ڪريو AT91_C_بنياد_TC2         ( ( AT91PS_TC ) 0xFFFA0080 )      /* (TC2) Base Address */
#وصف_ڪريو AT91_C_بنياد_TC1         ( ( AT91PS_TC ) 0xFFFA0040 )      /* (TC1) Base Address */
#وصف_ڪريو AT91_C_بنياد_TC0         ( ( AT91PS_TC ) 0xFFFA0000 )      /* (TC0) Base Address */
#وصف_ڪريو AT91_C_بنياد_TCB         ( ( AT91PS_TCB ) 0xFFFA0000 )     /* (TCB) Base Address */
#وصف_ڪريو AT91_C_بنياد_PWMC_CH3    ( ( AT91PS_PWMC_CH ) 0xFFFCC260 ) /* (PWMC_CH3) Base Address */
#وصف_ڪريو AT91_C_بنياد_PWMC_CH2    ( ( AT91PS_PWMC_CH ) 0xFFFCC240 ) /* (PWMC_CH2) Base Address */
#وصف_ڪريو AT91_C_بنياد_PWMC_CH1    ( ( AT91PS_PWMC_CH ) 0xFFFCC220 ) /* (PWMC_CH1) Base Address */
#وصف_ڪريو AT91_C_بنياد_PWMC_CH0    ( ( AT91PS_PWMC_CH ) 0xFFFCC200 ) /* (PWMC_CH0) Base Address */
#وصف_ڪريو AT91_C_بنياد_PWMC        ( ( AT91PS_PWMC ) 0xFFFCC000 )    /* (PWMC) Base Address */
#وصف_ڪريو AT91_C_بنياد_UDP         ( ( AT91PS_UDP ) 0xFFFB0000 )     /* (UDP) Base Address */

/* ***************************************************************************** */
/*               MEMORY MAPPING DEFINITIONS FOR AT91SAM7S64 */
/* ***************************************************************************** */
#وصف_ڪريو AT91C_ISRAM          ( ( حرف * ) 0x00200000 )       /* Internal SRAM base address */
#وصف_ڪريو AT91_C_ISRAM_سائيز     ( ( بنانشان صحيح ) 0x00004000 ) /* Internal SRAM size in byte (16 Kbyte) */
#وصف_ڪريو AT91C_IFLASH         ( ( حرف * ) 0x00100000 )       /* Internal ROM base address */
#وصف_ڪريو AT91_C_IFLASH_سائيز    ( ( بنانشان صحيح ) 0x00010000 ) /* Internal ROM size in byte (64 Kbyte) */

#جيڪڏهن_پورو /* ifndef AT91SAM7S64_H */
