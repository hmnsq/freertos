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

#جے_بنا_تعریف AT91SAM7S64_H
#تعریف_کرو AT91SAM7S64_H

تعريفنوع متطاير بنانشانی صحيح AT91_REG; /* Hardware register definition */

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
    AT91_REG SYSC_PIOA_فی;      /* PIO Enable Register */
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
#تعریف_کرو AT91C_SYSC_PSTDBY    ( ( بنانشانی صحيح ) 0x1 << 0 ) /* (SYSC) Voltage Regulator Power Mode */

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
#تعریف_کرو AT91_C_AIC_پہلوں                              ( ( بنانشانی صحيح ) 0x7 << 0 ) /* (AIC) Priority Level */
#تعریف_کرو     AT91_C_AIC_پہلوں_سبھ_توں_نیواں                   ( ( بنانشانی صحيح ) 0x0 )      /* (AIC) Lowest priority level */
#تعریف_کرو     AT91_C_AIC_پہلوں_HIGHEST                  ( ( بنانشانی صحيح ) 0x7 )      /* (AIC) Highest priority level */
#تعریف_کرو AT91C_AIC_SRCTYPE                            ( ( بنانشانی صحيح ) 0x3 << 5 ) /* (AIC) Interrupt Source Type */
#تعریف_کرو     AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE    ( ( بنانشانی صحيح ) 0x0 << 5 ) /* (AIC) Internal Sources Code Label Level Sensitive */
#تعریف_کرو     AT91_C_AIC_SRCTYPE_INT_کنارا_TRIGGERED     ( ( بنانشانی صحيح ) 0x1 << 5 ) /* (AIC) Internal Sources Code Label Edge triggered */
#تعریف_کرو     AT91_C_AIC_SRCTYPE_EXT_بلند_LEVEL         ( ( بنانشانی صحيح ) 0x2 << 5 ) /* (AIC) External Sources Code Label High-level Sensitive */
#تعریف_کرو     AT91_C_AIC_SRCTYPE_EXT_مثبت_کنارا      ( ( بنانشانی صحيح ) 0x3 << 5 ) /* (AIC) External Sources Code Label Positive Edge triggered */
/* -------- AIC_CISR : (AIC Offset: 0x114) AIC Core Interrupt Status Register -------- */
#تعریف_کرو AT91C_AIC_NFIQ                               ( ( بنانشانی صحيح ) 0x1 << 0 ) /* (AIC) NFIQ Status */
#تعریف_کرو AT91C_AIC_NIRQ                               ( ( بنانشانی صحيح ) 0x1 << 1 ) /* (AIC) NIRQ Status */
/* -------- AIC_DCR : (AIC Offset: 0x138) AIC Debug Control Register (Protect) -------- */
#تعریف_کرو AT91C_AIC_DCR_PROT                           ( ( بنانشانی صحيح ) 0x1 << 0 ) /* (AIC) Protection Mode */
#تعریف_کرو AT91C_AIC_DCR_GMSK                           ( ( بنانشانی صحيح ) 0x1 << 1 ) /* (AIC) General Mask */

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
#تعریف_کرو AT91C_US_RSTRX                 ( ( بنانشانی صحيح ) 0x1 << 2 )  /* (DBGU) Reset Receiver */
#تعریف_کرو AT91C_US_RSTTX                 ( ( بنانشانی صحيح ) 0x1 << 3 )  /* (DBGU) Reset Transmitter */
#تعریف_کرو AT91C_US_RXEN                  ( ( بنانشانی صحيح ) 0x1 << 4 )  /* (DBGU) Receiver Enable */
#تعریف_کرو AT91C_US_RXDIS                 ( ( بنانشانی صحيح ) 0x1 << 5 )  /* (DBGU) Receiver Disable */
#تعریف_کرو AT91C_US_TXEN                  ( ( بنانشانی صحيح ) 0x1 << 6 )  /* (DBGU) Transmitter Enable */
#تعریف_کرو AT91C_US_TXDIS                 ( ( بنانشانی صحيح ) 0x1 << 7 )  /* (DBGU) Transmitter Disable */
/* -------- DBGU_MR : (DBGU Offset: 0x4) Debug Unit Mode Register -------- */
#تعریف_کرو AT91C_US_PAR                   ( ( بنانشانی صحيح ) 0x7 << 9 )  /* (DBGU) Parity type */
#تعریف_کرو     AT91C_US_PAR_EVEN          ( ( بنانشانی صحيح ) 0x0 << 9 )  /* (DBGU) Even Parity */
#تعریف_کرو     AT91C_US_PAR_ODD           ( ( بنانشانی صحيح ) 0x1 << 9 )  /* (DBGU) Odd Parity */
#تعریف_کرو     AT91C_US_PAR_SPACE         ( ( بنانشانی صحيح ) 0x2 << 9 )  /* (DBGU) Parity forced to 0 (Space) */
#تعریف_کرو     AT91C_US_PAR_MARK          ( ( بنانشانی صحيح ) 0x3 << 9 )  /* (DBGU) Parity forced to 1 (Mark) */
#تعریف_کرو     AT91C_US_PAR_NONE          ( ( بنانشانی صحيح ) 0x4 << 9 )  /* (DBGU) No Parity */
#تعریف_کرو     AT91C_US_PAR_MULTI_DROP    ( ( بنانشانی صحيح ) 0x6 << 9 )  /* (DBGU) Multi-drop mode */
#تعریف_کرو AT91C_US_CHMODE                ( ( بنانشانی صحيح ) 0x3 << 14 ) /* (DBGU) Channel Mode */
#تعریف_کرو     AT91_C_US_CHMODE_عام     ( ( بنانشانی صحيح ) 0x0 << 14 ) /* (DBGU) Normal Mode: The USART channel operates as an RX/TX USART. */
#تعریف_کرو     AT91C_US_CHMODE_AUTO       ( ( بنانشانی صحيح ) 0x1 << 14 ) /* (DBGU) Automatic Echo: Receiver Data Input is connected to the TXD pin. */
#تعریف_کرو     AT91C_US_CHMODE_LOCAL      ( ( بنانشانی صحيح ) 0x2 << 14 ) /* (DBGU) Local Loopback: Transmitter Output Signal is connected to Receiver Input Signal. */
#تعریف_کرو     AT91C_US_CHMODE_REMOTE     ( ( بنانشانی صحيح ) 0x3 << 14 ) /* (DBGU) Remote Loopback: RXD pin is internally connected to TXD pin. */
/* -------- DBGU_IER : (DBGU Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
#تعریف_کرو AT91C_US_RXRDY                 ( ( بنانشانی صحيح ) 0x1 << 0 )  /* (DBGU) RXRDY Interrupt */
#تعریف_کرو AT91C_US_TXRDY                 ( ( بنانشانی صحيح ) 0x1 << 1 )  /* (DBGU) TXRDY Interrupt */
#تعریف_کرو AT91C_US_ENDRX                 ( ( بنانشانی صحيح ) 0x1 << 3 )  /* (DBGU) End of Receive Transfer Interrupt */
#تعریف_کرو AT91C_US_ENDTX                 ( ( بنانشانی صحيح ) 0x1 << 4 )  /* (DBGU) End of Transmit Interrupt */
#تعریف_کرو AT91C_US_OVRE                  ( ( بنانشانی صحيح ) 0x1 << 5 )  /* (DBGU) Overrun Interrupt */
#تعریف_کرو AT91_C_US_چوکھٹا                 ( ( بنانشانی صحيح ) 0x1 << 6 )  /* (DBGU) Framing Error Interrupt */
#تعریف_کرو AT91C_US_PARE                  ( ( بنانشانی صحيح ) 0x1 << 7 )  /* (DBGU) Parity Error Interrupt */
#تعریف_کرو AT91C_US_TXEMPTY               ( ( بنانشانی صحيح ) 0x1 << 9 )  /* (DBGU) TXEMPTY Interrupt */
#تعریف_کرو AT91C_US_TXBUFE                ( ( بنانشانی صحيح ) 0x1 << 11 ) /* (DBGU) TXBUFE Interrupt */
#تعریف_کرو AT91C_US_RXBUFF                ( ( بنانشانی صحيح ) 0x1 << 12 ) /* (DBGU) RXBUFF Interrupt */
#تعریف_کرو AT91C_US_COMM_TX               ( ( بنانشانی صحيح ) 0x1 << 30 ) /* (DBGU) COMM_TX Interrupt */
#تعریف_کرو AT91C_US_COMM_RX               ( ( بنانشانی صحيح ) 0x1 << 31 ) /* (DBGU) COMM_RX Interrupt */
/* -------- DBGU_IDR : (DBGU Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* -------- DBGU_IMR : (DBGU Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* -------- DBGU_CSR : (DBGU Offset: 0x14) Debug Unit Channel Status Register -------- */
/* -------- DBGU_FNTR : (DBGU Offset: 0x48) Debug Unit FORCE_NTRST Register -------- */
#تعریف_کرو AT91C_US_FORCE_NTRST    ( ( بنانشانی صحيح ) 0x1 << 0 ) /* (DBGU) Force NTRST in JTAG */

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
#تعریف_کرو AT91C_PDC_RXTEN     ( ( بنانشانی صحيح ) 0x1 << 0 ) /* (PDC) Receiver Transfer Enable */
#تعریف_کرو AT91C_PDC_RXTDIS    ( ( بنانشانی صحيح ) 0x1 << 1 ) /* (PDC) Receiver Transfer Disable */
#تعریف_کرو AT91C_PDC_TXTEN     ( ( بنانشانی صحيح ) 0x1 << 8 ) /* (PDC) Transmitter Transfer Enable */
#تعریف_کرو AT91C_PDC_TXTDIS    ( ( بنانشانی صحيح ) 0x1 << 9 ) /* (PDC) Transmitter Transfer Disable */
/* -------- PDC_PTSR : (PDC Offset: 0x24) PDC Transfer Status Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Parallel Input Output Controller */
/* ***************************************************************************** */
تعريفنوع بنية _AT91S_PIO
{
    AT91_REG PIO_فی;        /* PIO Enable Register */
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
#تعریف_کرو AT91C_CKGR_MOSCEN            ( ( بنانشانی صحيح ) 0x1 << 0 )    /* (CKGR) Main Oscillator Enable */
#تعریف_کرو AT91C_CKGR_OSCBYPASS         ( ( بنانشانی صحيح ) 0x1 << 1 )    /* (CKGR) Main Oscillator Bypass */
#تعریف_کرو AT91C_CKGR_OSCOUNT           ( ( بنانشانی صحيح ) 0xFF << 8 )   /* (CKGR) Main Oscillator Start-up Time */
/* -------- CKGR_MCFR : (CKGR Offset: 0x4) Main Clock Frequency Register -------- */
#تعریف_کرو AT91C_CKGR_MAINF             ( ( بنانشانی صحيح ) 0xFFFF << 0 ) /* (CKGR) Main Clock Frequency */
#تعریف_کرو AT91C_CKGR_MAINRDY           ( ( بنانشانی صحيح ) 0x1 << 16 )   /* (CKGR) Main Clock Ready */
/* -------- CKGR_PLLR : (CKGR Offset: 0xc) PLL B Register -------- */
#تعریف_کرو AT91C_CKGR_DIV               ( ( بنانشانی صحيح ) 0xFF << 0 )   /* (CKGR) Divider Selected */
#تعریف_کرو     AT91C_CKGR_DIV_0         ( ( بنانشانی صحيح ) 0x0 )         /* (CKGR) Divider output is 0 */
#تعریف_کرو     AT91C_CKGR_DIV_BYPASS    ( ( بنانشانی صحيح ) 0x1 )         /* (CKGR) Divider is bypassed */
#تعریف_کرو AT91C_CKGR_PLLCOUNT          ( ( بنانشانی صحيح ) 0x3F << 8 )   /* (CKGR) PLL Counter */
#تعریف_کرو AT91_C_CKGR_باہرلا               ( ( بنانشانی صحيح ) 0x3 << 14 )   /* (CKGR) PLL Output Frequency Range */
#تعریف_کرو     AT91_C_CKGR_باہرلا_0         ( ( بنانشانی صحيح ) 0x0 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#تعریف_کرو     AT91_C_CKGR_باہرلا_1         ( ( بنانشانی صحيح ) 0x1 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#تعریف_کرو     AT91_C_CKGR_باہرلا_2         ( ( بنانشانی صحيح ) 0x2 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#تعریف_کرو     AT91_C_CKGR_باہرلا_3         ( ( بنانشانی صحيح ) 0x3 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#تعریف_کرو AT91C_CKGR_MUL               ( ( بنانشانی صحيح ) 0x7FF << 16 ) /* (CKGR) PLL Multiplier */
#تعریف_کرو AT91C_CKGR_USBDIV            ( ( بنانشانی صحيح ) 0x3 << 28 )   /* (CKGR) Divider for USB Clocks */
#تعریف_کرو     AT91C_CKGR_USBDIV_0      ( ( بنانشانی صحيح ) 0x0 << 28 )   /* (CKGR) Divider output is PLL clock output */
#تعریف_کرو     AT91C_CKGR_USBDIV_1      ( ( بنانشانی صحيح ) 0x1 << 28 )   /* (CKGR) Divider output is PLL clock output divided by 2 */
#تعریف_کرو     AT91C_CKGR_USBDIV_2      ( ( بنانشانی صحيح ) 0x2 << 28 )   /* (CKGR) Divider output is PLL clock output divided by 4 */

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
#تعریف_کرو AT91C_PMC_PCK     ( ( بنانشانی صحيح ) 0x1 << 0 )  /* (PMC) Processor Clock */
#تعریف_کرو AT91C_PMC_UDP     ( ( بنانشانی صحيح ) 0x1 << 7 )  /* (PMC) USB Device Port Clock */
#تعریف_کرو AT91C_PMC_PCK0    ( ( بنانشانی صحيح ) 0x1 << 8 )  /* (PMC) Programmable Clock Output */
#تعریف_کرو AT91C_PMC_PCK1    ( ( بنانشانی صحيح ) 0x1 << 9 )  /* (PMC) Programmable Clock Output */
#تعریف_کرو AT91C_PMC_PCK2    ( ( بنانشانی صحيح ) 0x1 << 10 ) /* (PMC) Programmable Clock Output */
#تعریف_کرو AT91C_PMC_PCK3    ( ( بنانشانی صحيح ) 0x1 << 11 ) /* (PMC) Programmable Clock Output */
/* -------- PMC_SCDR : (PMC Offset: 0x4) System Clock Disable Register -------- */
/* -------- PMC_SCSR : (PMC Offset: 0x8) System Clock Status Register -------- */
/* -------- CKGR_MOR : (PMC Offset: 0x20) Main Oscillator Register -------- */
/* -------- CKGR_MCFR : (PMC Offset: 0x24) Main Clock Frequency Register -------- */
/* -------- CKGR_PLLR : (PMC Offset: 0x2c) PLL B Register -------- */
/* -------- PMC_MCKR : (PMC Offset: 0x30) Master Clock Register -------- */
#تعریف_کرو AT91C_PMC_CSS                 ( ( بنانشانی صحيح ) 0x3 << 0 ) /* (PMC) Programmable Clock Selection */
#تعریف_کرو     AT91C_PMC_CSS_SLOW_CLK    ( ( بنانشانی صحيح ) 0x0 )      /* (PMC) Slow Clock is selected */
#تعریف_کرو     AT91C_PMC_CSS_MAIN_CLK    ( ( بنانشانی صحيح ) 0x1 )      /* (PMC) Main Clock is selected */
#تعریف_کرو     AT91C_PMC_CSS_PLL_CLK     ( ( بنانشانی صحيح ) 0x3 )      /* (PMC) Clock from PLL is selected */
#تعریف_کرو AT91C_PMC_PRES                ( ( بنانشانی صحيح ) 0x7 << 2 ) /* (PMC) Programmable Clock Prescaler */
#تعریف_کرو     AT91C_PMC_PRES_CLK        ( ( بنانشانی صحيح ) 0x0 << 2 ) /* (PMC) Selected clock */
#تعریف_کرو     AT91C_PMC_PRES_CLK_2      ( ( بنانشانی صحيح ) 0x1 << 2 ) /* (PMC) Selected clock divided by 2 */
#تعریف_کرو     AT91C_PMC_PRES_CLK_4      ( ( بنانشانی صحيح ) 0x2 << 2 ) /* (PMC) Selected clock divided by 4 */
#تعریف_کرو     AT91C_PMC_PRES_CLK_8      ( ( بنانشانی صحيح ) 0x3 << 2 ) /* (PMC) Selected clock divided by 8 */
#تعریف_کرو     AT91C_PMC_PRES_CLK_16     ( ( بنانشانی صحيح ) 0x4 << 2 ) /* (PMC) Selected clock divided by 16 */
#تعریف_کرو     AT91C_PMC_PRES_CLK_32     ( ( بنانشانی صحيح ) 0x5 << 2 ) /* (PMC) Selected clock divided by 32 */
#تعریف_کرو     AT91C_PMC_PRES_CLK_64     ( ( بنانشانی صحيح ) 0x6 << 2 ) /* (PMC) Selected clock divided by 64 */
/* -------- PMC_PCKR : (PMC Offset: 0x40) Programmable Clock Register -------- */
/* -------- PMC_IER : (PMC Offset: 0x60) PMC Interrupt Enable Register -------- */
#تعریف_کرو AT91C_PMC_MOSCS               ( ( بنانشانی صحيح ) 0x1 << 0 )  /* (PMC) MOSC Status/Enable/Disable/Mask */
#تعریف_کرو AT91_C_PMC_جندرا                ( ( بنانشانی صحيح ) 0x1 << 2 )  /* (PMC) PLL Status/Enable/Disable/Mask */
#تعریف_کرو AT91C_PMC_MCKRDY              ( ( بنانشانی صحيح ) 0x1 << 3 )  /* (PMC) MCK_RDY Status/Enable/Disable/Mask */
#تعریف_کرو AT91C_PMC_PCK0RDY             ( ( بنانشانی صحيح ) 0x1 << 8 )  /* (PMC) PCK0_RDY Status/Enable/Disable/Mask */
#تعریف_کرو AT91C_PMC_PCK1RDY             ( ( بنانشانی صحيح ) 0x1 << 9 )  /* (PMC) PCK1_RDY Status/Enable/Disable/Mask */
#تعریف_کرو AT91C_PMC_PCK2RDY             ( ( بنانشانی صحيح ) 0x1 << 10 ) /* (PMC) PCK2_RDY Status/Enable/Disable/Mask */
#تعریف_کرو AT91C_PMC_PCK3RDY             ( ( بنانشانی صحيح ) 0x1 << 11 ) /* (PMC) PCK3_RDY Status/Enable/Disable/Mask */
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
#تعریف_کرو AT91C_SYSC_PROCRST                ( ( بنانشانی صحيح ) 0x1 << 0 )   /* (RSTC) Processor Reset */
#تعریف_کرو AT91C_SYSC_ICERST                 ( ( بنانشانی صحيح ) 0x1 << 1 )   /* (RSTC) ICE Interface Reset */
#تعریف_کرو AT91C_SYSC_PERRST                 ( ( بنانشانی صحيح ) 0x1 << 2 )   /* (RSTC) Peripheral Reset */
#تعریف_کرو AT91C_SYSC_EXTRST                 ( ( بنانشانی صحيح ) 0x1 << 3 )   /* (RSTC) External Reset */
#تعریف_کرو AT91_C_SYSC_کلید                    ( ( بنانشانی صحيح ) 0xFF << 24 ) /* (RSTC) Password */
/* -------- SYSC_RSR : (RSTC Offset: 0x4) Reset Status Register -------- */
#تعریف_کرو AT91C_SYSC_URSTS                  ( ( بنانشانی صحيح ) 0x1 << 0 )   /* (RSTC) User Reset Status */
#تعریف_کرو AT91C_SYSC_BODSTS                 ( ( بنانشانی صحيح ) 0x1 << 1 )   /* (RSTC) Brown-out Detection Status */
#تعریف_کرو AT91C_SYSC_RSTTYP                 ( ( بنانشانی صحيح ) 0x7 << 8 )   /* (RSTC) Reset Type */
#تعریف_کرو     AT91C_SYSC_RSTTYP_POWERUP     ( ( بنانشانی صحيح ) 0x0 << 8 )   /* (RSTC) Power-up Reset. VDDCORE rising. */
#تعریف_کرو     AT91C_SYSC_RSTTYP_WATCHDOG    ( ( بنانشانی صحيح ) 0x2 << 8 )   /* (RSTC) Watchdog Reset. Watchdog overflow occurred. */
#تعریف_کرو     AT91C_SYSC_RSTTYP_SOFTWARE    ( ( بنانشانی صحيح ) 0x3 << 8 )   /* (RSTC) Software Reset. Processor reset required by the software. */
#تعریف_کرو     AT91C_SYSC_RSTTYP_USER        ( ( بنانشانی صحيح ) 0x4 << 8 )   /* (RSTC) User Reset. NRST pin detected low. */
#تعریف_کرو     AT91C_SYSC_RSTTYP_BROWNOUT    ( ( بنانشانی صحيح ) 0x5 << 8 )   /* (RSTC) Brown-out Reset. */
#تعریف_کرو AT91C_SYSC_NRSTL                  ( ( بنانشانی صحيح ) 0x1 << 16 )  /* (RSTC) NRST pin level */
#تعریف_کرو AT91C_SYSC_SRCMP                  ( ( بنانشانی صحيح ) 0x1 << 17 )  /* (RSTC) Software Reset Command in Progress. */
/* -------- SYSC_RMR : (RSTC Offset: 0x8) Reset Mode Register -------- */
#تعریف_کرو AT91C_SYSC_URSTEN                 ( ( بنانشانی صحيح ) 0x1 << 0 )   /* (RSTC) User Reset Enable */
#تعریف_کرو AT91C_SYSC_URSTIEN                ( ( بنانشانی صحيح ) 0x1 << 4 )   /* (RSTC) User Reset Interrupt Enable */
#تعریف_کرو AT91C_SYSC_ERSTL                  ( ( بنانشانی صحيح ) 0xF << 8 )   /* (RSTC) User Reset Enable */
#تعریف_کرو AT91C_SYSC_BODIEN                 ( ( بنانشانی صحيح ) 0x1 << 16 )  /* (RSTC) Brown-out Detection Interrupt Enable */

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
#تعریف_کرو AT91C_SYSC_RTPRES       ( ( بنانشانی صحيح ) 0xFFFF << 0 ) /* (RTTC) Real-time Timer Prescaler Value */
#تعریف_کرو AT91C_SYSC_ALMIEN       ( ( بنانشانی صحيح ) 0x1 << 16 )   /* (RTTC) Alarm Interrupt Enable */
#تعریف_کرو AT91C_SYSC_RTTINCIEN    ( ( بنانشانی صحيح ) 0x1 << 17 )   /* (RTTC) Real Time Timer Increment Interrupt Enable */
#تعریف_کرو AT91C_SYSC_RTTRST       ( ( بنانشانی صحيح ) 0x1 << 18 )   /* (RTTC) Real Time Timer Restart */
/* -------- SYSC_RTAR : (RTTC Offset: 0x4) Real-time Alarm Register -------- */
#تعریف_کرو AT91C_SYSC_ALMV         ( ( بنانشانی صحيح ) 0x0 << 0 )    /* (RTTC) Alarm Value */
/* -------- SYSC_RTVR : (RTTC Offset: 0x8) Current Real-time Value Register -------- */
#تعریف_کرو AT91C_SYSC_CRTV         ( ( بنانشانی صحيح ) 0x0 << 0 )    /* (RTTC) Current Real-time Value */
/* -------- SYSC_RTSR : (RTTC Offset: 0xc) Real-time Status Register -------- */
#تعریف_کرو AT91C_SYSC_ALMS         ( ( بنانشانی صحيح ) 0x1 << 0 )    /* (RTTC) Real-time Alarm Status */
#تعریف_کرو AT91C_SYSC_RTTINC       ( ( بنانشانی صحيح ) 0x1 << 1 )    /* (RTTC) Real-time Timer Increment */

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
#تعریف_کرو AT91C_SYSC_PIV       ( ( بنانشانی صحيح ) 0xFFFFF << 0 ) /* (PITC) Periodic Interval Value */
#تعریف_کرو AT91C_SYSC_PITEN     ( ( بنانشانی صحيح ) 0x1 << 24 )    /* (PITC) Periodic Interval Timer Enabled */
#تعریف_کرو AT91C_SYSC_PITIEN    ( ( بنانشانی صحيح ) 0x1 << 25 )    /* (PITC) Periodic Interval Timer Interrupt Enable */
/* -------- SYSC_PISR : (PITC Offset: 0x4) Periodic Interval Status Register -------- */
#تعریف_کرو AT91C_SYSC_PITS      ( ( بنانشانی صحيح ) 0x1 << 0 )     /* (PITC) Periodic Interval Timer Status */
/* -------- SYSC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register -------- */
#تعریف_کرو AT91C_SYSC_CPIV      ( ( بنانشانی صحيح ) 0xFFFFF << 0 ) /* (PITC) Current Periodic Interval Value */
#تعریف_کرو AT91C_SYSC_PICNT     ( ( بنانشانی صحيح ) 0xFFF << 20 )  /* (PITC) Periodic Interval Counter */
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
#تعریف_کرو AT91C_SYSC_WDRSTT       ( ( بنانشانی صحيح ) 0x1 << 0 )    /* (WDTC) Watchdog Restart */
/* -------- SYSC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register -------- */
#تعریف_کرو AT91C_SYSC_WDV          ( ( بنانشانی صحيح ) 0xFFF << 0 )  /* (WDTC) Watchdog Timer Restart */
#تعریف_کرو AT91C_SYSC_WDFIEN       ( ( بنانشانی صحيح ) 0x1 << 12 )   /* (WDTC) Watchdog Fault Interrupt Enable */
#تعریف_کرو AT91C_SYSC_WDRSTEN      ( ( بنانشانی صحيح ) 0x1 << 13 )   /* (WDTC) Watchdog Reset Enable */
#تعریف_کرو AT91C_SYSC_WDRPROC      ( ( بنانشانی صحيح ) 0x1 << 14 )   /* (WDTC) Watchdog Timer Restart */
#تعریف_کرو AT91C_SYSC_WDDIS        ( ( بنانشانی صحيح ) 0x1 << 15 )   /* (WDTC) Watchdog Disable */
#تعریف_کرو AT91C_SYSC_WDD          ( ( بنانشانی صحيح ) 0xFFF << 16 ) /* (WDTC) Watchdog Delta Value */
#تعریف_کرو AT91C_SYSC_WDDBGHLT     ( ( بنانشانی صحيح ) 0x1 << 28 )   /* (WDTC) Watchdog Debug Halt */
#تعریف_کرو AT91C_SYSC_WDIDLEHLT    ( ( بنانشانی صحيح ) 0x1 << 29 )   /* (WDTC) Watchdog Idle Halt */
/* -------- SYSC_WDSR : (WDTC Offset: 0x8) Watchdog Status Register -------- */
#تعریف_کرو AT91C_SYSC_WDUNF        ( ( بنانشانی صحيح ) 0x1 << 0 )    /* (WDTC) Watchdog Underflow */
#تعریف_کرو AT91C_SYSC_WDERR        ( ( بنانشانی صحيح ) 0x1 << 1 )    /* (WDTC) Watchdog Error */

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
#تعریف_کرو AT91C_MC_RCB                       ( ( بنانشانی صحيح ) 0x1 << 0 )   /* (MC) Remap Command Bit */
/* -------- MC_ASR : (MC Offset: 0x4) MC Abort Status Register -------- */
#تعریف_کرو AT91C_MC_UNDADD                    ( ( بنانشانی صحيح ) 0x1 << 0 )   /* (MC) Undefined Address Abort Status */
#تعریف_کرو AT91C_MC_MISADD                    ( ( بنانشانی صحيح ) 0x1 << 1 )   /* (MC) Misaligned Address Abort Status */
#تعریف_کرو AT91C_MC_ABTSZ                     ( ( بنانشانی صحيح ) 0x3 << 8 )   /* (MC) Abort Size Status */
#تعریف_کرو     AT91C_MC_ABTSZ_BYTE            ( ( بنانشانی صحيح ) 0x0 << 8 )   /* (MC) Byte */
#تعریف_کرو     AT91C_MC_ABTSZ_HWORD           ( ( بنانشانی صحيح ) 0x1 << 8 )   /* (MC) Half-word */
#تعریف_کرو     AT91_C_MC_ABTSZ_لفظ            ( ( بنانشانی صحيح ) 0x2 << 8 )   /* (MC) Word */
#تعریف_کرو AT91C_MC_ABTTYP                    ( ( بنانشانی صحيح ) 0x3 << 10 )  /* (MC) Abort Type Status */
#تعریف_کرو     AT91C_MC_ABTTYP_DATAR          ( ( بنانشانی صحيح ) 0x0 << 10 )  /* (MC) Data Read */
#تعریف_کرو     AT91C_MC_ABTTYP_DATAW          ( ( بنانشانی صحيح ) 0x1 << 10 )  /* (MC) Data Write */
#تعریف_کرو     AT91C_MC_ABTTYP_FETCH          ( ( بنانشانی صحيح ) 0x2 << 10 )  /* (MC) Code Fetch */
#تعریف_کرو AT91C_MC_MST0                      ( ( بنانشانی صحيح ) 0x1 << 16 )  /* (MC) Master 0 Abort Source */
#تعریف_کرو AT91C_MC_MST1                      ( ( بنانشانی صحيح ) 0x1 << 17 )  /* (MC) Master 1 Abort Source */
#تعریف_کرو AT91C_MC_SVMST0                    ( ( بنانشانی صحيح ) 0x1 << 24 )  /* (MC) Saved Master 0 Abort Source */
#تعریف_کرو AT91C_MC_SVMST1                    ( ( بنانشانی صحيح ) 0x1 << 25 )  /* (MC) Saved Master 1 Abort Source */
/* -------- MC_FMR : (MC Offset: 0x60) MC Flash Mode Register -------- */
#تعریف_کرو AT91C_MC_FRDY                      ( ( بنانشانی صحيح ) 0x1 << 0 )   /* (MC) Flash Ready */
#تعریف_کرو AT91C_MC_LOCKE                     ( ( بنانشانی صحيح ) 0x1 << 2 )   /* (MC) Lock Error */
#تعریف_کرو AT91C_MC_PROGE                     ( ( بنانشانی صحيح ) 0x1 << 3 )   /* (MC) Programming Error */
#تعریف_کرو AT91C_MC_NEBP                      ( ( بنانشانی صحيح ) 0x1 << 7 )   /* (MC) No Erase Before Programming */
#تعریف_کرو AT91C_MC_FWS                       ( ( بنانشانی صحيح ) 0x3 << 8 )   /* (MC) Flash Wait State */
#تعریف_کرو     AT91C_MC_FWS_0FWS              ( ( بنانشانی صحيح ) 0x0 << 8 )   /* (MC) 1 cycle for Read, 2 for Write operations */
#تعریف_کرو     AT91C_MC_FWS_1FWS              ( ( بنانشانی صحيح ) 0x1 << 8 )   /* (MC) 2 cycles for Read, 3 for Write operations */
#تعریف_کرو     AT91C_MC_FWS_2FWS              ( ( بنانشانی صحيح ) 0x2 << 8 )   /* (MC) 3 cycles for Read, 4 for Write operations */
#تعریف_کرو     AT91C_MC_FWS_3FWS              ( ( بنانشانی صحيح ) 0x3 << 8 )   /* (MC) 4 cycles for Read, 4 for Write operations */
#تعریف_کرو AT91C_MC_FMCN                      ( ( بنانشانی صحيح ) 0xFF << 16 ) /* (MC) Flash Microsecond Cycle Number */
/* -------- MC_FCR : (MC Offset: 0x64) MC Flash Command Register -------- */
#تعریف_کرو AT91C_MC_FCMD                      ( ( بنانشانی صحيح ) 0xF << 0 )   /* (MC) Flash Command */
#تعریف_کرو     AT91_C_MC_FCMD_شروع_PROG       ( ( بنانشانی صحيح ) 0x1 )        /* (MC) Starts the programming of th epage specified by PAGEN. */
#تعریف_کرو     AT91_C_MC_FCMD_جندرا             ( ( بنانشانی صحيح ) 0x2 )        /* (MC) Starts a lock sequence of the sector defined by the bits 4 to 7 of the field PAGEN. */
#تعریف_کرو     AT91_C_MC_FCMD_PROG_AND_جندرا    ( ( بنانشانی صحيح ) 0x3 )        /* (MC) The lock sequence automatically happens after the programming sequence is completed. */
#تعریف_کرو     AT91C_MC_FCMD_UNLOCK           ( ( بنانشانی صحيح ) 0x4 )        /* (MC) Starts an unlock sequence of the sector defined by the bits 4 to 7 of the field PAGEN. */
#تعریف_کرو     AT91C_MC_FCMD_ERASE_ALL        ( ( بنانشانی صحيح ) 0x8 )        /* (MC) Starts the erase of the entire flash.If at least a page is locked, the command is cancelled. */
#تعریف_کرو     AT91_C_MC_FCMD_سیٹ_GP_NVM       ( ( بنانشانی صحيح ) 0xB )        /* (MC) Set General Purpose NVM bits. */
#تعریف_کرو     AT91C_MC_FCMD_CLR_GP_NVM       ( ( بنانشانی صحيح ) 0xD )        /* (MC) Clear General Purpose NVM bits. */
#تعریف_کرو     AT91_C_MC_FCMD_سیٹ_SECURITY     ( ( بنانشانی صحيح ) 0xF )        /* (MC) Set Security Bit. */
#تعریف_کرو AT91C_MC_PAGEN                     ( ( بنانشانی صحيح ) 0x3FF << 8 ) /* (MC) Page Number */
#تعریف_کرو AT91_C_MC_کلید                       ( ( بنانشانی صحيح ) 0xFF << 24 ) /* (MC) Writing Protect Key */
/* -------- MC_FSR : (MC Offset: 0x68) MC Flash Command Register -------- */
#تعریف_کرو AT91C_MC_SECURITY                  ( ( بنانشانی صحيح ) 0x1 << 4 )   /* (MC) Security Bit Status */
#تعریف_کرو AT91C_MC_GPNVM0                    ( ( بنانشانی صحيح ) 0x1 << 8 )   /* (MC) Sector 0 Lock Status */
#تعریف_کرو AT91C_MC_GPNVM1                    ( ( بنانشانی صحيح ) 0x1 << 9 )   /* (MC) Sector 1 Lock Status */
#تعریف_کرو AT91C_MC_GPNVM2                    ( ( بنانشانی صحيح ) 0x1 << 10 )  /* (MC) Sector 2 Lock Status */
#تعریف_کرو AT91C_MC_GPNVM3                    ( ( بنانشانی صحيح ) 0x1 << 11 )  /* (MC) Sector 3 Lock Status */
#تعریف_کرو AT91C_MC_GPNVM4                    ( ( بنانشانی صحيح ) 0x1 << 12 )  /* (MC) Sector 4 Lock Status */
#تعریف_کرو AT91C_MC_GPNVM5                    ( ( بنانشانی صحيح ) 0x1 << 13 )  /* (MC) Sector 5 Lock Status */
#تعریف_کرو AT91C_MC_GPNVM6                    ( ( بنانشانی صحيح ) 0x1 << 14 )  /* (MC) Sector 6 Lock Status */
#تعریف_کرو AT91C_MC_GPNVM7                    ( ( بنانشانی صحيح ) 0x1 << 15 )  /* (MC) Sector 7 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS0                    ( ( بنانشانی صحيح ) 0x1 << 16 )  /* (MC) Sector 0 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS1                    ( ( بنانشانی صحيح ) 0x1 << 17 )  /* (MC) Sector 1 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS2                    ( ( بنانشانی صحيح ) 0x1 << 18 )  /* (MC) Sector 2 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS3                    ( ( بنانشانی صحيح ) 0x1 << 19 )  /* (MC) Sector 3 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS4                    ( ( بنانشانی صحيح ) 0x1 << 20 )  /* (MC) Sector 4 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS5                    ( ( بنانشانی صحيح ) 0x1 << 21 )  /* (MC) Sector 5 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS6                    ( ( بنانشانی صحيح ) 0x1 << 22 )  /* (MC) Sector 6 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS7                    ( ( بنانشانی صحيح ) 0x1 << 23 )  /* (MC) Sector 7 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS8                    ( ( بنانشانی صحيح ) 0x1 << 24 )  /* (MC) Sector 8 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS9                    ( ( بنانشانی صحيح ) 0x1 << 25 )  /* (MC) Sector 9 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS10                   ( ( بنانشانی صحيح ) 0x1 << 26 )  /* (MC) Sector 10 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS11                   ( ( بنانشانی صحيح ) 0x1 << 27 )  /* (MC) Sector 11 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS12                   ( ( بنانشانی صحيح ) 0x1 << 28 )  /* (MC) Sector 12 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS13                   ( ( بنانشانی صحيح ) 0x1 << 29 )  /* (MC) Sector 13 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS14                   ( ( بنانشانی صحيح ) 0x1 << 30 )  /* (MC) Sector 14 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS15                   ( ( بنانشانی صحيح ) 0x1 << 31 )  /* (MC) Sector 15 Lock Status */

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
#تعریف_کرو AT91C_SPI_SPIEN              ( ( بنانشانی صحيح ) 0x1 << 0 )    /* (SPI) SPI Enable */
#تعریف_کرو AT91C_SPI_SPIDIS             ( ( بنانشانی صحيح ) 0x1 << 1 )    /* (SPI) SPI Disable */
#تعریف_کرو AT91C_SPI_SWRST              ( ( بنانشانی صحيح ) 0x1 << 7 )    /* (SPI) SPI Software reset */
#تعریف_کرو AT91C_SPI_LASTXFER           ( ( بنانشانی صحيح ) 0x1 << 24 )   /* (SPI) SPI Last Transfer */
/* -------- SPI_MR : (SPI Offset: 0x4) SPI Mode Register -------- */
#تعریف_کرو AT91C_SPI_MSTR               ( ( بنانشانی صحيح ) 0x1 << 0 )    /* (SPI) Master/Slave Mode */
#تعریف_کرو AT91C_SPI_PS                 ( ( بنانشانی صحيح ) 0x1 << 1 )    /* (SPI) Peripheral Select */
#تعریف_کرو     AT91C_SPI_PS_FIXED       ( ( بنانشانی صحيح ) 0x0 << 1 )    /* (SPI) Fixed Peripheral Select */
#تعریف_کرو     AT91C_SPI_PS_VARIABLE    ( ( بنانشانی صحيح ) 0x1 << 1 )    /* (SPI) Variable Peripheral Select */
#تعریف_کرو AT91C_SPI_PCSDEC             ( ( بنانشانی صحيح ) 0x1 << 2 )    /* (SPI) Chip Select Decode */
#تعریف_کرو AT91C_SPI_FDIV               ( ( بنانشانی صحيح ) 0x1 << 3 )    /* (SPI) Clock Selection */
#تعریف_کرو AT91C_SPI_MODFDIS            ( ( بنانشانی صحيح ) 0x1 << 4 )    /* (SPI) Mode Fault Detection */
#تعریف_کرو AT91C_SPI_LLB                ( ( بنانشانی صحيح ) 0x1 << 7 )    /* (SPI) Clock Selection */
#تعریف_کرو AT91C_SPI_PCS                ( ( بنانشانی صحيح ) 0xF << 16 )   /* (SPI) Peripheral Chip Select */
#تعریف_کرو AT91C_SPI_DLYBCS             ( ( بنانشانی صحيح ) 0xFF << 24 )  /* (SPI) Delay Between Chip Selects */
/* -------- SPI_RDR : (SPI Offset: 0x8) Receive Data Register -------- */
#تعریف_کرو AT91C_SPI_RD                 ( ( بنانشانی صحيح ) 0xFFFF << 0 ) /* (SPI) Receive Data */
#تعریف_کرو AT91C_SPI_RPCS               ( ( بنانشانی صحيح ) 0xF << 16 )   /* (SPI) Peripheral Chip Select Status */
/* -------- SPI_TDR : (SPI Offset: 0xc) Transmit Data Register -------- */
#تعریف_کرو AT91C_SPI_TD                 ( ( بنانشانی صحيح ) 0xFFFF << 0 ) /* (SPI) Transmit Data */
#تعریف_کرو AT91C_SPI_TPCS               ( ( بنانشانی صحيح ) 0xF << 16 )   /* (SPI) Peripheral Chip Select Status */
/* -------- SPI_SR : (SPI Offset: 0x10) Status Register -------- */
#تعریف_کرو AT91C_SPI_RDRF               ( ( بنانشانی صحيح ) 0x1 << 0 )    /* (SPI) Receive Data Register Full */
#تعریف_کرو AT91C_SPI_TDRE               ( ( بنانشانی صحيح ) 0x1 << 1 )    /* (SPI) Transmit Data Register Empty */
#تعریف_کرو AT91C_SPI_MODF               ( ( بنانشانی صحيح ) 0x1 << 2 )    /* (SPI) Mode Fault Error */
#تعریف_کرو AT91C_SPI_OVRES              ( ( بنانشانی صحيح ) 0x1 << 3 )    /* (SPI) Overrun Error Status */
#تعریف_کرو AT91C_SPI_ENDRX              ( ( بنانشانی صحيح ) 0x1 << 4 )    /* (SPI) End of Receiver Transfer */
#تعریف_کرو AT91C_SPI_ENDTX              ( ( بنانشانی صحيح ) 0x1 << 5 )    /* (SPI) End of Receiver Transfer */
#تعریف_کرو AT91C_SPI_RXBUFF             ( ( بنانشانی صحيح ) 0x1 << 6 )    /* (SPI) RXBUFF Interrupt */
#تعریف_کرو AT91C_SPI_TXBUFE             ( ( بنانشانی صحيح ) 0x1 << 7 )    /* (SPI) TXBUFE Interrupt */
#تعریف_کرو AT91C_SPI_NSSR               ( ( بنانشانی صحيح ) 0x1 << 8 )    /* (SPI) NSSR Interrupt */
#تعریف_کرو AT91C_SPI_TXEMPTY            ( ( بنانشانی صحيح ) 0x1 << 9 )    /* (SPI) TXEMPTY Interrupt */
#تعریف_کرو AT91C_SPI_SPIENS             ( ( بنانشانی صحيح ) 0x1 << 16 )   /* (SPI) Enable Status */
/* -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- */
/* -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- */
/* -------- SPI_IMR : (SPI Offset: 0x1c) Interrupt Mask Register -------- */
/* -------- SPI_CSR : (SPI Offset: 0x30) Chip Select Register -------- */
#تعریف_کرو AT91C_SPI_CPOL           ( ( بنانشانی صحيح ) 0x1 << 0 )   /* (SPI) Clock Polarity */
#تعریف_کرو AT91C_SPI_NCPHA          ( ( بنانشانی صحيح ) 0x1 << 1 )   /* (SPI) Clock Phase */
#تعریف_کرو AT91C_SPI_CSAAT          ( ( بنانشانی صحيح ) 0x1 << 2 )   /* (SPI) Chip Select Active After Transfer */
#تعریف_کرو AT91_C_SPI_بٹ           ( ( بنانشانی صحيح ) 0xF << 4 )   /* (SPI) Bits Per Transfer */
#تعریف_کرو     AT91_C_SPI_بٹ_8     ( ( بنانشانی صحيح ) 0x0 << 4 )   /* (SPI) 8 Bits Per transfer */
#تعریف_کرو     AT91_C_SPI_بٹ_9     ( ( بنانشانی صحيح ) 0x1 << 4 )   /* (SPI) 9 Bits Per transfer */
#تعریف_کرو     AT91_C_SPI_بٹ_10    ( ( بنانشانی صحيح ) 0x2 << 4 )   /* (SPI) 10 Bits Per transfer */
#تعریف_کرو     AT91_C_SPI_بٹ_11    ( ( بنانشانی صحيح ) 0x3 << 4 )   /* (SPI) 11 Bits Per transfer */
#تعریف_کرو     AT91_C_SPI_بٹ_12    ( ( بنانشانی صحيح ) 0x4 << 4 )   /* (SPI) 12 Bits Per transfer */
#تعریف_کرو     AT91_C_SPI_بٹ_13    ( ( بنانشانی صحيح ) 0x5 << 4 )   /* (SPI) 13 Bits Per transfer */
#تعریف_کرو     AT91_C_SPI_بٹ_14    ( ( بنانشانی صحيح ) 0x6 << 4 )   /* (SPI) 14 Bits Per transfer */
#تعریف_کرو     AT91_C_SPI_بٹ_15    ( ( بنانشانی صحيح ) 0x7 << 4 )   /* (SPI) 15 Bits Per transfer */
#تعریف_کرو     AT91_C_SPI_بٹ_16    ( ( بنانشانی صحيح ) 0x8 << 4 )   /* (SPI) 16 Bits Per transfer */
#تعریف_کرو AT91C_SPI_SCBR           ( ( بنانشانی صحيح ) 0xFF << 8 )  /* (SPI) Serial Clock Baud Rate */
#تعریف_کرو AT91C_SPI_DLYBS          ( ( بنانشانی صحيح ) 0xFF << 16 ) /* (SPI) Serial Clock Baud Rate */
#تعریف_کرو AT91C_SPI_DLYBCT         ( ( بنانشانی صحيح ) 0xFF << 24 ) /* (SPI) Delay Between Consecutive Transfers */

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
#تعریف_کرو AT91C_ADC_SWRST                    ( ( بنانشانی صحيح ) 0x1 << 0 )   /* (ADC) Software Reset */
#تعریف_کرو AT91_C_ADC_شروع                    ( ( بنانشانی صحيح ) 0x1 << 1 )   /* (ADC) Start Conversion */
/* -------- ADC_MR : (ADC Offset: 0x4) ADC Mode Register -------- */
#تعریف_کرو AT91C_ADC_TRGEN                    ( ( بنانشانی صحيح ) 0x1 << 0 )   /* (ADC) Trigger Enable */
#تعریف_کرو     AT91C_ADC_TRGEN_DIS            ( ( بنانشانی صحيح ) 0x0 )        /* (ADC) Hardware triggers are disabled. Starting a conversion is only possible by software */
#تعریف_کرو     AT91C_ADC_TRGEN_EN             ( ( بنانشانی صحيح ) 0x1 )        /* (ADC) Hardware trigger selected by TRGSEL field is enabled. */
#تعریف_کرو AT91C_ADC_TRGSEL                   ( ( بنانشانی صحيح ) 0x7 << 1 )   /* (ADC) Trigger Selection */
#تعریف_کرو     AT91C_ADC_TRGSEL_TIOA0         ( ( بنانشانی صحيح ) 0x0 << 1 )   /* (ADC) Selected TRGSEL = TIAO0 */
#تعریف_کرو     AT91C_ADC_TRGSEL_TIOA1         ( ( بنانشانی صحيح ) 0x1 << 1 )   /* (ADC) Selected TRGSEL = TIAO1 */
#تعریف_کرو     AT91C_ADC_TRGSEL_TIOA2         ( ( بنانشانی صحيح ) 0x2 << 1 )   /* (ADC) Selected TRGSEL = TIAO2 */
#تعریف_کرو     AT91C_ADC_TRGSEL_TIOA3         ( ( بنانشانی صحيح ) 0x3 << 1 )   /* (ADC) Selected TRGSEL = TIAO3 */
#تعریف_کرو     AT91C_ADC_TRGSEL_TIOA4         ( ( بنانشانی صحيح ) 0x4 << 1 )   /* (ADC) Selected TRGSEL = TIAO4 */
#تعریف_کرو     AT91C_ADC_TRGSEL_TIOA5         ( ( بنانشانی صحيح ) 0x5 << 1 )   /* (ADC) Selected TRGSEL = TIAO5 */
#تعریف_کرو     AT91C_ADC_TRGSEL_EXT           ( ( بنانشانی صحيح ) 0x6 << 1 )   /* (ADC) Selected TRGSEL = External Trigger */
#تعریف_کرو AT91C_ADC_LOWRES                   ( ( بنانشانی صحيح ) 0x1 << 4 )   /* (ADC) Resolution. */
#تعریف_کرو     AT91_C_ADC_LOWRES_10_ثنائی_ہندسہ        ( ( بنانشانی صحيح ) 0x0 << 4 )   /* (ADC) 10-bit resolution */
#تعریف_کرو     AT91_C_ADC_LOWRES_8_ثنائی_ہندسہ         ( ( بنانشانی صحيح ) 0x1 << 4 )   /* (ADC) 8-bit resolution */
#تعریف_کرو AT91C_ADC_SLEEP                    ( ( بنانشانی صحيح ) 0x1 << 5 )   /* (ADC) Sleep Mode */
#تعریف_کرو     AT91_C_ADC_SLEEP_عام_منوال    ( ( بنانشانی صحيح ) 0x0 << 5 )   /* (ADC) Normal Mode */
#تعریف_کرو     AT91_C_ADC_SLEEP_منوال           ( ( بنانشانی صحيح ) 0x1 << 5 )   /* (ADC) Sleep Mode */
#تعریف_کرو AT91C_ADC_PRESCAL                  ( ( بنانشانی صحيح ) 0x3F << 8 )  /* (ADC) Prescaler rate selection */
#تعریف_کرو AT91C_ADC_STARTUP                  ( ( بنانشانی صحيح ) 0x1F << 16 ) /* (ADC) Startup Time */
#تعریف_کرو AT91C_ADC_SHTIM                    ( ( بنانشانی صحيح ) 0xF << 24 )  /* (ADC) Sample & Hold Time */
/* --------     ADC_CHER : (ADC Offset: 0x10) ADC Channel Enable Register -------- */
#تعریف_کرو AT91C_ADC_CH0                      ( ( بنانشانی صحيح ) 0x1 << 0 )   /* (ADC) Channel 0 */
#تعریف_کرو AT91C_ADC_CH1                      ( ( بنانشانی صحيح ) 0x1 << 1 )   /* (ADC) Channel 1 */
#تعریف_کرو AT91C_ADC_CH2                      ( ( بنانشانی صحيح ) 0x1 << 2 )   /* (ADC) Channel 2 */
#تعریف_کرو AT91C_ADC_CH3                      ( ( بنانشانی صحيح ) 0x1 << 3 )   /* (ADC) Channel 3 */
#تعریف_کرو AT91C_ADC_CH4                      ( ( بنانشانی صحيح ) 0x1 << 4 )   /* (ADC) Channel 4 */
#تعریف_کرو AT91C_ADC_CH5                      ( ( بنانشانی صحيح ) 0x1 << 5 )   /* (ADC) Channel 5 */
#تعریف_کرو AT91C_ADC_CH6                      ( ( بنانشانی صحيح ) 0x1 << 6 )   /* (ADC) Channel 6 */
#تعریف_کرو AT91C_ADC_CH7                      ( ( بنانشانی صحيح ) 0x1 << 7 )   /* (ADC) Channel 7 */
/* --------     ADC_CHDR : (ADC Offset: 0x14) ADC Channel Disable Register -------- */
/* --------     ADC_CHSR : (ADC Offset: 0x18) ADC Channel Status Register -------- */
/* -------- ADC_SR : (ADC Offset: 0x1c) ADC Status Register -------- */
#تعریف_کرو AT91C_ADC_EOC0      ( ( بنانشانی صحيح ) 0x1 << 0 )   /* (ADC) End of Conversion */
#تعریف_کرو AT91C_ADC_EOC1      ( ( بنانشانی صحيح ) 0x1 << 1 )   /* (ADC) End of Conversion */
#تعریف_کرو AT91C_ADC_EOC2      ( ( بنانشانی صحيح ) 0x1 << 2 )   /* (ADC) End of Conversion */
#تعریف_کرو AT91C_ADC_EOC3      ( ( بنانشانی صحيح ) 0x1 << 3 )   /* (ADC) End of Conversion */
#تعریف_کرو AT91C_ADC_EOC4      ( ( بنانشانی صحيح ) 0x1 << 4 )   /* (ADC) End of Conversion */
#تعریف_کرو AT91C_ADC_EOC5      ( ( بنانشانی صحيح ) 0x1 << 5 )   /* (ADC) End of Conversion */
#تعریف_کرو AT91C_ADC_EOC6      ( ( بنانشانی صحيح ) 0x1 << 6 )   /* (ADC) End of Conversion */
#تعریف_کرو AT91C_ADC_EOC7      ( ( بنانشانی صحيح ) 0x1 << 7 )   /* (ADC) End of Conversion */
#تعریف_کرو AT91C_ADC_OVRE0     ( ( بنانشانی صحيح ) 0x1 << 8 )   /* (ADC) Overrun Error */
#تعریف_کرو AT91C_ADC_OVRE1     ( ( بنانشانی صحيح ) 0x1 << 9 )   /* (ADC) Overrun Error */
#تعریف_کرو AT91C_ADC_OVRE2     ( ( بنانشانی صحيح ) 0x1 << 10 )  /* (ADC) Overrun Error */
#تعریف_کرو AT91C_ADC_OVRE3     ( ( بنانشانی صحيح ) 0x1 << 11 )  /* (ADC) Overrun Error */
#تعریف_کرو AT91C_ADC_OVRE4     ( ( بنانشانی صحيح ) 0x1 << 12 )  /* (ADC) Overrun Error */
#تعریف_کرو AT91C_ADC_OVRE5     ( ( بنانشانی صحيح ) 0x1 << 13 )  /* (ADC) Overrun Error */
#تعریف_کرو AT91C_ADC_OVRE6     ( ( بنانشانی صحيح ) 0x1 << 14 )  /* (ADC) Overrun Error */
#تعریف_کرو AT91C_ADC_OVRE7     ( ( بنانشانی صحيح ) 0x1 << 15 )  /* (ADC) Overrun Error */
#تعریف_کرو AT91C_ADC_DRDY      ( ( بنانشانی صحيح ) 0x1 << 16 )  /* (ADC) Data Ready */
#تعریف_کرو AT91C_ADC_GOVRE     ( ( بنانشانی صحيح ) 0x1 << 17 )  /* (ADC) General Overrun */
#تعریف_کرو AT91C_ADC_ENDRX     ( ( بنانشانی صحيح ) 0x1 << 18 )  /* (ADC) End of Receiver Transfer */
#تعریف_کرو AT91C_ADC_RXBUFF    ( ( بنانشانی صحيح ) 0x1 << 19 )  /* (ADC) RXBUFF Interrupt */
/* -------- ADC_LCDR : (ADC Offset: 0x20) ADC Last Converted Data Register -------- */
#تعریف_کرو AT91C_ADC_LDATA     ( ( بنانشانی صحيح ) 0x3FF << 0 ) /* (ADC) Last Data Converted */
/* -------- ADC_IER : (ADC Offset: 0x24) ADC Interrupt Enable Register -------- */
/* -------- ADC_IDR : (ADC Offset: 0x28) ADC Interrupt Disable Register -------- */
/* -------- ADC_IMR : (ADC Offset: 0x2c) ADC Interrupt Mask Register -------- */
/* -------- ADC_CDR0 : (ADC Offset: 0x30) ADC Channel Data Register 0 -------- */
#تعریف_کرو AT91_C_ADC_انکڑے    ( ( بنانشانی صحيح ) 0x3FF << 0 )  /* (ADC) Converted Data */
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
#تعریف_کرو AT91C_SSC_RXEN                    ( ( بنانشانی صحيح ) 0x1 << 0 )   /* (SSC) Receive Enable */
#تعریف_کرو AT91C_SSC_RXDIS                   ( ( بنانشانی صحيح ) 0x1 << 1 )   /* (SSC) Receive Disable */
#تعریف_کرو AT91C_SSC_TXEN                    ( ( بنانشانی صحيح ) 0x1 << 8 )   /* (SSC) Transmit Enable */
#تعریف_کرو AT91C_SSC_TXDIS                   ( ( بنانشانی صحيح ) 0x1 << 9 )   /* (SSC) Transmit Disable */
#تعریف_کرو AT91C_SSC_SWRST                   ( ( بنانشانی صحيح ) 0x1 << 15 )  /* (SSC) Software Reset */
/* -------- SSC_RCMR : (SSC Offset: 0x10) SSC Receive Clock Mode Register -------- */
#تعریف_کرو AT91C_SSC_CKS                     ( ( بنانشانی صحيح ) 0x3 << 0 )   /* (SSC) Receive/Transmit Clock Selection */
#تعریف_کرو     AT91C_SSC_CKS_DIV             ( ( بنانشانی صحيح ) 0x0 )        /* (SSC) Divided Clock */
#تعریف_کرو     AT91C_SSC_CKS_TK              ( ( بنانشانی صحيح ) 0x1 )        /* (SSC) TK Clock signal */
#تعریف_کرو     AT91C_SSC_CKS_RK              ( ( بنانشانی صحيح ) 0x2 )        /* (SSC) RK pin */
#تعریف_کرو AT91C_SSC_CKO                     ( ( بنانشانی صحيح ) 0x7 << 2 )   /* (SSC) Receive/Transmit Clock Output Mode Selection */
#تعریف_کرو     AT91C_SSC_CKO_NONE            ( ( بنانشانی صحيح ) 0x0 << 2 )   /* (SSC) Receive/Transmit Clock Output Mode: None RK pin: Input-only */
#تعریف_کرو     AT91C_SSC_CKO_CONTINUOUS      ( ( بنانشانی صحيح ) 0x1 << 2 )   /* (SSC) Continuous Receive/Transmit Clock RK pin: Output */
#تعریف_کرو     AT91_C_SSC_CKO_انکڑے_TX         ( ( بنانشانی صحيح ) 0x2 << 2 )   /* (SSC) Receive/Transmit Clock only during data transfers RK pin: Output */
#تعریف_کرو AT91C_SSC_CKI                     ( ( بنانشانی صحيح ) 0x1 << 5 )   /* (SSC) Receive/Transmit Clock Inversion */
#تعریف_کرو AT91C_SSC_CKG                     ( ( بنانشانی صحيح ) 0x3 << 6 )   /* (SSC) Receive/Transmit Clock Gating Selection */
#تعریف_کرو     AT91C_SSC_CKG_NONE            ( ( بنانشانی صحيح ) 0x0 << 6 )   /* (SSC) Receive/Transmit Clock Gating: None, continuous clock */
#تعریف_کرو     AT91_C_SSC_CKG_کم             ( ( بنانشانی صحيح ) 0x1 << 6 )   /* (SSC) Receive/Transmit Clock enabled only if RF Low */
#تعریف_کرو     AT91_C_SSC_CKG_بلند            ( ( بنانشانی صحيح ) 0x2 << 6 )   /* (SSC) Receive/Transmit Clock enabled only if RF High */
#تعریف_کرو AT91_C_SSC_شروع                   ( ( بنانشانی صحيح ) 0xF << 8 )   /* (SSC) Receive/Transmit Start Selection */
#تعریف_کرو     AT91_C_SSC_شروع_CONTINUOUS    ( ( بنانشانی صحيح ) 0x0 << 8 )   /* (SSC) Continuous, as soon as the receiver is enabled, and immediately after the end of transfer of the previous data. */
#تعریف_کرو     AT91_C_SSC_شروع_TX            ( ( بنانشانی صحيح ) 0x1 << 8 )   /* (SSC) Transmit/Receive start */
#تعریف_کرو     AT91_C_SSC_شروع_کم_RF        ( ( بنانشانی صحيح ) 0x2 << 8 )   /* (SSC) Detection of a low level on RF input */
#تعریف_کرو     AT91_C_SSC_شروع_بلند_RF       ( ( بنانشانی صحيح ) 0x3 << 8 )   /* (SSC) Detection of a high level on RF input */
#تعریف_کرو     AT91_C_SSC_شروع_FALL_RF       ( ( بنانشانی صحيح ) 0x4 << 8 )   /* (SSC) Detection of a falling edge on RF input */
#تعریف_کرو     AT91_C_SSC_شروع_RISE_RF       ( ( بنانشانی صحيح ) 0x5 << 8 )   /* (SSC) Detection of a rising edge on RF input */
#تعریف_کرو     AT91_C_SSC_شروع_LEVEL_RF      ( ( بنانشانی صحيح ) 0x6 << 8 )   /* (SSC) Detection of any level change on RF input */
#تعریف_کرو     AT91_C_SSC_شروع_کنارا_RF       ( ( بنانشانی صحيح ) 0x7 << 8 )   /* (SSC) Detection of any edge on RF input */
#تعریف_کرو     AT91_C_SSC_شروع_0             ( ( بنانشانی صحيح ) 0x8 << 8 )   /* (SSC) Compare 0 */
#تعریف_کرو AT91C_SSC_STOP                    ( ( بنانشانی صحيح ) 0x1 << 12 )  /* (SSC) Receive Stop Selection */
#تعریف_کرو AT91C_SSC_STTOUT                  ( ( بنانشانی صحيح ) 0x1 << 15 )  /* (SSC) Receive/Transmit Start Output Selection */
#تعریف_کرو AT91C_SSC_STTDLY                  ( ( بنانشانی صحيح ) 0xFF << 16 ) /* (SSC) Receive/Transmit Start Delay */
#تعریف_کرو AT91C_SSC_PERIOD                  ( ( بنانشانی صحيح ) 0xFF << 24 ) /* (SSC) Receive/Transmit Period Divider Selection */
/* -------- SSC_RFMR : (SSC Offset: 0x14) SSC Receive Frame Mode Register -------- */
#تعریف_کرو AT91C_SSC_DATLEN                  ( ( بنانشانی صحيح ) 0x1F << 0 )  /* (SSC) Data Length */
#تعریف_کرو AT91C_SSC_LOOP                    ( ( بنانشانی صحيح ) 0x1 << 5 )   /* (SSC) Loop Mode */
#تعریف_کرو AT91C_SSC_MSBF                    ( ( بنانشانی صحيح ) 0x1 << 7 )   /* (SSC) Most Significant Bit First */
#تعریف_کرو AT91C_SSC_DATNB                   ( ( بنانشانی صحيح ) 0xF << 8 )   /* (SSC) Data Number per Frame */
#تعریف_کرو AT91C_SSC_FSLEN                   ( ( بنانشانی صحيح ) 0xF << 16 )  /* (SSC) Receive/Transmit Frame Sync length */
#تعریف_کرو AT91C_SSC_FSOS                    ( ( بنانشانی صحيح ) 0x7 << 20 )  /* (SSC) Receive/Transmit Frame Sync Output Selection */
#تعریف_کرو     AT91C_SSC_FSOS_NONE           ( ( بنانشانی صحيح ) 0x0 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: None RK pin Input-only */
#تعریف_کرو     AT91C_SSC_FSOS_NEGATIVE       ( ( بنانشانی صحيح ) 0x1 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Negative Pulse */
#تعریف_کرو     AT91_C_SSC_FSOS_مثبت       ( ( بنانشانی صحيح ) 0x2 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Positive Pulse */
#تعریف_کرو     AT91_C_SSC_FSOS_کم            ( ( بنانشانی صحيح ) 0x3 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Driver Low during data transfer */
#تعریف_کرو     AT91_C_SSC_FSOS_بلند           ( ( بنانشانی صحيح ) 0x4 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Driver High during data transfer */
#تعریف_کرو     AT91C_SSC_FSOS_TOGGLE         ( ( بنانشانی صحيح ) 0x5 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Toggling at each start of data transfer */
#تعریف_کرو AT91C_SSC_FSEDGE                  ( ( بنانشانی صحيح ) 0x1 << 24 )  /* (SSC) Frame Sync Edge Detection */
/* -------- SSC_TCMR : (SSC Offset: 0x18) SSC Transmit Clock Mode Register -------- */
/* -------- SSC_TFMR : (SSC Offset: 0x1c) SSC Transmit Frame Mode Register -------- */
#تعریف_کرو AT91C_SSC_DATDEF                  ( ( بنانشانی صحيح ) 0x1 << 5 )  /* (SSC) Data Default Value */
#تعریف_کرو AT91C_SSC_FSDEN                   ( ( بنانشانی صحيح ) 0x1 << 23 ) /* (SSC) Frame Sync Data Enable */
/* -------- SSC_SR : (SSC Offset: 0x40) SSC Status Register -------- */
#تعریف_کرو AT91C_SSC_TXRDY                   ( ( بنانشانی صحيح ) 0x1 << 0 )  /* (SSC) Transmit Ready */
#تعریف_کرو AT91C_SSC_TXEMPTY                 ( ( بنانشانی صحيح ) 0x1 << 1 )  /* (SSC) Transmit Empty */
#تعریف_کرو AT91C_SSC_ENDTX                   ( ( بنانشانی صحيح ) 0x1 << 2 )  /* (SSC) End Of Transmission */
#تعریف_کرو AT91C_SSC_TXBUFE                  ( ( بنانشانی صحيح ) 0x1 << 3 )  /* (SSC) Transmit Buffer Empty */
#تعریف_کرو AT91C_SSC_RXRDY                   ( ( بنانشانی صحيح ) 0x1 << 4 )  /* (SSC) Receive Ready */
#تعریف_کرو AT91C_SSC_OVRUN                   ( ( بنانشانی صحيح ) 0x1 << 5 )  /* (SSC) Receive Overrun */
#تعریف_کرو AT91C_SSC_ENDRX                   ( ( بنانشانی صحيح ) 0x1 << 6 )  /* (SSC) End of Reception */
#تعریف_کرو AT91C_SSC_RXBUFF                  ( ( بنانشانی صحيح ) 0x1 << 7 )  /* (SSC) Receive Buffer Full */
#تعریف_کرو AT91C_SSC_CP0                     ( ( بنانشانی صحيح ) 0x1 << 8 )  /* (SSC) Compare 0 */
#تعریف_کرو AT91C_SSC_CP1                     ( ( بنانشانی صحيح ) 0x1 << 9 )  /* (SSC) Compare 1 */
#تعریف_کرو AT91C_SSC_TXSYN                   ( ( بنانشانی صحيح ) 0x1 << 10 ) /* (SSC) Transmit Sync */
#تعریف_کرو AT91C_SSC_RXSYN                   ( ( بنانشانی صحيح ) 0x1 << 11 ) /* (SSC) Receive Sync */
#تعریف_کرو AT91C_SSC_TXENA                   ( ( بنانشانی صحيح ) 0x1 << 16 ) /* (SSC) Transmit Enable */
#تعریف_کرو AT91C_SSC_RXENA                   ( ( بنانشانی صحيح ) 0x1 << 17 ) /* (SSC) Receive Enable */
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
#تعریف_کرو AT91C_US_RSTSTA                  ( ( بنانشانی صحيح ) 0x1 << 8 )  /* (USART) Reset Status Bits */
#تعریف_کرو AT91C_US_STTBRK                  ( ( بنانشانی صحيح ) 0x1 << 9 )  /* (USART) Start Break */
#تعریف_کرو AT91C_US_STPBRK                  ( ( بنانشانی صحيح ) 0x1 << 10 ) /* (USART) Stop Break */
#تعریف_کرو AT91C_US_STTTO                   ( ( بنانشانی صحيح ) 0x1 << 11 ) /* (USART) Start Time-out */
#تعریف_کرو AT91C_US_SENDA                   ( ( بنانشانی صحيح ) 0x1 << 12 ) /* (USART) Send Address */
#تعریف_کرو AT91C_US_RSTIT                   ( ( بنانشانی صحيح ) 0x1 << 13 ) /* (USART) Reset Iterations */
#تعریف_کرو AT91C_US_RSTNACK                 ( ( بنانشانی صحيح ) 0x1 << 14 ) /* (USART) Reset Non Acknowledge */
#تعریف_کرو AT91C_US_RETTO                   ( ( بنانشانی صحيح ) 0x1 << 15 ) /* (USART) Rearm Time-out */
#تعریف_کرو AT91C_US_DTREN                   ( ( بنانشانی صحيح ) 0x1 << 16 ) /* (USART) Data Terminal ready Enable */
#تعریف_کرو AT91C_US_DTRDIS                  ( ( بنانشانی صحيح ) 0x1 << 17 ) /* (USART) Data Terminal ready Disable */
#تعریف_کرو AT91C_US_RTSEN                   ( ( بنانشانی صحيح ) 0x1 << 18 ) /* (USART) Request to Send enable */
#تعریف_کرو AT91C_US_RTSDIS                  ( ( بنانشانی صحيح ) 0x1 << 19 ) /* (USART) Request to Send Disable */
/* -------- US_MR : (USART Offset: 0x4) Debug Unit Mode Register -------- */
#تعریف_کرو AT91C_US_USMODE                  ( ( بنانشانی صحيح ) 0xF << 0 )  /* (USART) Usart mode */
#تعریف_کرو     AT91_C_US_USMODE_عام       ( ( بنانشانی صحيح ) 0x0 )       /* (USART) Normal */
#تعریف_کرو     AT91C_US_USMODE_RS485        ( ( بنانشانی صحيح ) 0x1 )       /* (USART) RS485 */
#تعریف_کرو     AT91C_US_USMODE_HWHSH        ( ( بنانشانی صحيح ) 0x2 )       /* (USART) Hardware Handshaking */
#تعریف_کرو     AT91C_US_USMODE_MODEM        ( ( بنانشانی صحيح ) 0x3 )       /* (USART) Modem */
#تعریف_کرو     AT91C_US_USMODE_ISO7816_0    ( ( بنانشانی صحيح ) 0x4 )       /* (USART) ISO7816 protocol: T = 0 */
#تعریف_کرو     AT91C_US_USMODE_ISO7816_1    ( ( بنانشانی صحيح ) 0x6 )       /* (USART) ISO7816 protocol: T = 1 */
#تعریف_کرو     AT91C_US_USMODE_IRDA         ( ( بنانشانی صحيح ) 0x8 )       /* (USART) IrDA */
#تعریف_کرو     AT91C_US_USMODE_SWHSH        ( ( بنانشانی صحيح ) 0xC )       /* (USART) Software Handshaking */
#تعریف_کرو AT91C_US_CLKS                    ( ( بنانشانی صحيح ) 0x3 << 4 )  /* (USART) Clock Selection (Baud Rate generator Input Clock */
#تعریف_کرو     AT91C_US_CLKS_CLOCK          ( ( بنانشانی صحيح ) 0x0 << 4 )  /* (USART) Clock */
#تعریف_کرو     AT91C_US_CLKS_FDIV1          ( ( بنانشانی صحيح ) 0x1 << 4 )  /* (USART) fdiv1 */
#تعریف_کرو     AT91C_US_CLKS_SLOW           ( ( بنانشانی صحيح ) 0x2 << 4 )  /* (USART) slow_clock (ARM) */
#تعریف_کرو     AT91C_US_CLKS_EXT            ( ( بنانشانی صحيح ) 0x3 << 4 )  /* (USART) External (SCK) */
#تعریف_کرو AT91C_US_CHRL                    ( ( بنانشانی صحيح ) 0x3 << 6 )  /* (USART) Clock Selection (Baud Rate generator Input Clock */
#تعریف_کرو     AT91_C_US_CHRL_5_بٹ         ( ( بنانشانی صحيح ) 0x0 << 6 )  /* (USART) Character Length: 5 bits */
#تعریف_کرو     AT91_C_US_CHRL_6_بٹ         ( ( بنانشانی صحيح ) 0x1 << 6 )  /* (USART) Character Length: 6 bits */
#تعریف_کرو     AT91_C_US_CHRL_7_بٹ         ( ( بنانشانی صحيح ) 0x2 << 6 )  /* (USART) Character Length: 7 bits */
#تعریف_کرو     AT91_C_US_CHRL_8_بٹ         ( ( بنانشانی صحيح ) 0x3 << 6 )  /* (USART) Character Length: 8 bits */
#تعریف_کرو AT91C_US_SYNC                    ( ( بنانشانی صحيح ) 0x1 << 8 )  /* (USART) Synchronous Mode Select */
#تعریف_کرو AT91C_US_NBSTOP                  ( ( بنانشانی صحيح ) 0x3 << 12 ) /* (USART) Number of Stop bits */
#تعریف_کرو     AT91_C_US_NBSTOP_1_ثنائی_ہندسہ        ( ( بنانشانی صحيح ) 0x0 << 12 ) /* (USART) 1 stop bit */
#تعریف_کرو     AT91_C_US_NBSTOP_15_ثنائی_ہندسہ       ( ( بنانشانی صحيح ) 0x1 << 12 ) /* (USART) Asynchronous (SYNC=0) 2 stop bits Synchronous (SYNC=1) 2 stop bits */
#تعریف_کرو     AT91_C_US_NBSTOP_2_ثنائی_ہندسہ        ( ( بنانشانی صحيح ) 0x2 << 12 ) /* (USART) 2 stop bits */
#تعریف_کرو AT91C_US_MSBF                    ( ( بنانشانی صحيح ) 0x1 << 16 ) /* (USART) Bit Order */
#تعریف_کرو AT91C_US_MODE9                   ( ( بنانشانی صحيح ) 0x1 << 17 ) /* (USART) 9-bit Character length */
#تعریف_کرو AT91C_US_CKLO                    ( ( بنانشانی صحيح ) 0x1 << 18 ) /* (USART) Clock Output Select */
#تعریف_کرو AT91C_US_OVER                    ( ( بنانشانی صحيح ) 0x1 << 19 ) /* (USART) Over Sampling Mode */
#تعریف_کرو AT91C_US_INACK                   ( ( بنانشانی صحيح ) 0x1 << 20 ) /* (USART) Inhibit Non Acknowledge */
#تعریف_کرو AT91C_US_DSNACK                  ( ( بنانشانی صحيح ) 0x1 << 21 ) /* (USART) Disable Successive NACK */
#تعریف_کرو AT91C_US_MAX_ITER                ( ( بنانشانی صحيح ) 0x1 << 24 ) /* (USART) Number of Repetitions */
#تعریف_کرو AT91C_US_FILTER                  ( ( بنانشانی صحيح ) 0x1 << 28 ) /* (USART) Receive Line Filter */
/* -------- US_IER : (USART Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
#تعریف_کرو AT91C_US_RXBRK                   ( ( بنانشانی صحيح ) 0x1 << 2 )  /* (USART) Break Received/End of Break */
#تعریف_کرو AT91C_US_TIMEOUT                 ( ( بنانشانی صحيح ) 0x1 << 8 )  /* (USART) Receiver Time-out */
#تعریف_کرو AT91C_US_ITERATION               ( ( بنانشانی صحيح ) 0x1 << 10 ) /* (USART) Max number of Repetitions Reached */
#تعریف_کرو AT91C_US_NACK                    ( ( بنانشانی صحيح ) 0x1 << 13 ) /* (USART) Non Acknowledge */
#تعریف_کرو AT91C_US_RIIC                    ( ( بنانشانی صحيح ) 0x1 << 16 ) /* (USART) Ring INdicator Input Change Flag */
#تعریف_کرو AT91C_US_DSRIC                   ( ( بنانشانی صحيح ) 0x1 << 17 ) /* (USART) Data Set Ready Input Change Flag */
#تعریف_کرو AT91C_US_DCDIC                   ( ( بنانشانی صحيح ) 0x1 << 18 ) /* (USART) Data Carrier Flag */
#تعریف_کرو AT91C_US_CTSIC                   ( ( بنانشانی صحيح ) 0x1 << 19 ) /* (USART) Clear To Send Input Change Flag */
/* -------- US_IDR : (USART Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* -------- US_IMR : (USART Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* -------- US_CSR : (USART Offset: 0x14) Debug Unit Channel Status Register -------- */
#تعریف_کرو AT91C_US_RI     ( ( بنانشانی صحيح ) 0x1 << 20 )   /* (USART) Image of RI Input */
#تعریف_کرو AT91C_US_DSR    ( ( بنانشانی صحيح ) 0x1 << 21 )   /* (USART) Image of DSR Input */
#تعریف_کرو AT91C_US_DCD    ( ( بنانشانی صحيح ) 0x1 << 22 )   /* (USART) Image of DCD Input */
#تعریف_کرو AT91C_US_CTS    ( ( بنانشانی صحيح ) 0x1 << 23 )   /* (USART) Image of CTS Input */

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
#تعریف_کرو AT91_C_TWI_شروع                ( ( بنانشانی صحيح ) 0x1 << 0 )   /* (TWI) Send a START Condition */
#تعریف_کرو AT91C_TWI_STOP                 ( ( بنانشانی صحيح ) 0x1 << 1 )   /* (TWI) Send a STOP Condition */
#تعریف_کرو AT91C_TWI_MSEN                 ( ( بنانشانی صحيح ) 0x1 << 2 )   /* (TWI) TWI Master Transfer Enabled */
#تعریف_کرو AT91C_TWI_MSDIS                ( ( بنانشانی صحيح ) 0x1 << 3 )   /* (TWI) TWI Master Transfer Disabled */
#تعریف_کرو AT91C_TWI_SVEN                 ( ( بنانشانی صحيح ) 0x1 << 4 )   /* (TWI) TWI Slave Transfer Enabled */
#تعریف_کرو AT91C_TWI_SVDIS                ( ( بنانشانی صحيح ) 0x1 << 5 )   /* (TWI) TWI Slave Transfer Disabled */
#تعریف_کرو AT91C_TWI_SWRST                ( ( بنانشانی صحيح ) 0x1 << 7 )   /* (TWI) Software Reset */
/* -------- TWI_MMR : (TWI Offset: 0x4) TWI Master Mode Register -------- */
#تعریف_کرو AT91C_TWI_IADRSZ               ( ( بنانشانی صحيح ) 0x3 << 8 )   /* (TWI) Internal Device Address Size */
#تعریف_کرو     AT91C_TWI_IADRSZ_NO        ( ( بنانشانی صحيح ) 0x0 << 8 )   /* (TWI) No internal device address */
#تعریف_کرو     AT91C_TWI_IADRSZ_1_BYTE    ( ( بنانشانی صحيح ) 0x1 << 8 )   /* (TWI) One-byte internal device address */
#تعریف_کرو     AT91C_TWI_IADRSZ_2_BYTE    ( ( بنانشانی صحيح ) 0x2 << 8 )   /* (TWI) Two-byte internal device address */
#تعریف_کرو     AT91C_TWI_IADRSZ_3_BYTE    ( ( بنانشانی صحيح ) 0x3 << 8 )   /* (TWI) Three-byte internal device address */
#تعریف_کرو AT91C_TWI_MREAD                ( ( بنانشانی صحيح ) 0x1 << 12 )  /* (TWI) Master Read Direction */
#تعریف_کرو AT91C_TWI_DADR                 ( ( بنانشانی صحيح ) 0x7F << 16 ) /* (TWI) Device Address */
/* -------- TWI_SMR : (TWI Offset: 0x8) TWI Slave Mode Register -------- */
#تعریف_کرو AT91C_TWI_SADR                 ( ( بنانشانی صحيح ) 0x7F << 16 ) /* (TWI) Slave Device Address */
/* -------- TWI_CWGR : (TWI Offset: 0x10) TWI Clock Waveform Generator Register -------- */
#تعریف_کرو AT91C_TWI_CLDIV                ( ( بنانشانی صحيح ) 0xFF << 0 )  /* (TWI) Clock Low Divider */
#تعریف_کرو AT91C_TWI_CHDIV                ( ( بنانشانی صحيح ) 0xFF << 8 )  /* (TWI) Clock High Divider */
#تعریف_کرو AT91C_TWI_CKDIV                ( ( بنانشانی صحيح ) 0x7 << 16 )  /* (TWI) Clock Divider */
/* -------- TWI_SR : (TWI Offset: 0x20) TWI Status Register -------- */
#تعریف_کرو AT91C_TWI_TXCOMP               ( ( بنانشانی صحيح ) 0x1 << 0 )   /* (TWI) Transmission Completed */
#تعریف_کرو AT91C_TWI_RXRDY                ( ( بنانشانی صحيح ) 0x1 << 1 )   /* (TWI) Receive holding register ReaDY */
#تعریف_کرو AT91C_TWI_TXRDY                ( ( بنانشانی صحيح ) 0x1 << 2 )   /* (TWI) Transmit holding register ReaDY */
#تعریف_کرو AT91C_TWI_SVREAD               ( ( بنانشانی صحيح ) 0x1 << 3 )   /* (TWI) Slave Read */
#تعریف_کرو AT91C_TWI_SVACC                ( ( بنانشانی صحيح ) 0x1 << 4 )   /* (TWI) Slave Access */
#تعریف_کرو AT91C_TWI_GCACC                ( ( بنانشانی صحيح ) 0x1 << 5 )   /* (TWI) General Call Access */
#تعریف_کرو AT91C_TWI_OVRE                 ( ( بنانشانی صحيح ) 0x1 << 6 )   /* (TWI) Overrun Error */
#تعریف_کرو AT91C_TWI_UNRE                 ( ( بنانشانی صحيح ) 0x1 << 7 )   /* (TWI) Underrun Error */
#تعریف_کرو AT91C_TWI_NACK                 ( ( بنانشانی صحيح ) 0x1 << 8 )   /* (TWI) Not Acknowledged */
#تعریف_کرو AT91C_TWI_ARBLST               ( ( بنانشانی صحيح ) 0x1 << 9 )   /* (TWI) Arbitration Lost */
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
#تعریف_کرو AT91C_TC_CLKEN                        ( ( بنانشانی صحيح ) 0x1 << 0 )  /* (TC) Counter Clock Enable Command */
#تعریف_کرو AT91C_TC_CLKDIS                       ( ( بنانشانی صحيح ) 0x1 << 1 )  /* (TC) Counter Clock Disable Command */
#تعریف_کرو AT91C_TC_SWTRG                        ( ( بنانشانی صحيح ) 0x1 << 2 )  /* (TC) Software Trigger Command */
/* -------- TC_CMR : (TC Offset: 0x4) TC Channel Mode Register: Capture Mode / Waveform Mode -------- */
#تعریف_کرو AT91C_TC_CLKS                         ( ( بنانشانی صحيح ) 0x7 << 0 )  /* (TC) Clock Selection */
#تعریف_کرو     AT91C_TC_CLKS_TIMER_DIV1_CLOCK    ( ( بنانشانی صحيح ) 0x0 )       /* (TC) Clock selected: TIMER_DIV1_CLOCK */
#تعریف_کرو     AT91C_TC_CLKS_TIMER_DIV2_CLOCK    ( ( بنانشانی صحيح ) 0x1 )       /* (TC) Clock selected: TIMER_DIV2_CLOCK */
#تعریف_کرو     AT91C_TC_CLKS_TIMER_DIV3_CLOCK    ( ( بنانشانی صحيح ) 0x2 )       /* (TC) Clock selected: TIMER_DIV3_CLOCK */
#تعریف_کرو     AT91C_TC_CLKS_TIMER_DIV4_CLOCK    ( ( بنانشانی صحيح ) 0x3 )       /* (TC) Clock selected: TIMER_DIV4_CLOCK */
#تعریف_کرو     AT91C_TC_CLKS_TIMER_DIV5_CLOCK    ( ( بنانشانی صحيح ) 0x4 )       /* (TC) Clock selected: TIMER_DIV5_CLOCK */
#تعریف_کرو     AT91C_TC_CLKS_XC0                 ( ( بنانشانی صحيح ) 0x5 )       /* (TC) Clock selected: XC0 */
#تعریف_کرو     AT91C_TC_CLKS_XC1                 ( ( بنانشانی صحيح ) 0x6 )       /* (TC) Clock selected: XC1 */
#تعریف_کرو     AT91C_TC_CLKS_XC2                 ( ( بنانشانی صحيح ) 0x7 )       /* (TC) Clock selected: XC2 */
#تعریف_کرو AT91C_TC_CLKI                         ( ( بنانشانی صحيح ) 0x1 << 3 )  /* (TC) Clock Invert */
#تعریف_کرو AT91_C_TC_مدت                        ( ( بنانشانی صحيح ) 0x3 << 4 )  /* (TC) Burst Signal Selection */
#تعریف_کرو     AT91_C_TC_مدت_NONE               ( ( بنانشانی صحيح ) 0x0 << 4 )  /* (TC) The clock is not gated by an external signal */
#تعریف_کرو     AT91_C_TC_مدت_XC0                ( ( بنانشانی صحيح ) 0x1 << 4 )  /* (TC) XC0 is ANDed with the selected clock */
#تعریف_کرو     AT91_C_TC_مدت_XC1                ( ( بنانشانی صحيح ) 0x2 << 4 )  /* (TC) XC1 is ANDed with the selected clock */
#تعریف_کرو     AT91_C_TC_مدت_XC2                ( ( بنانشانی صحيح ) 0x3 << 4 )  /* (TC) XC2 is ANDed with the selected clock */
#تعریف_کرو AT91C_TC_CPCSTOP                      ( ( بنانشانی صحيح ) 0x1 << 6 )  /* (TC) Counter Clock Stopped with RC Compare */
#تعریف_کرو AT91C_TC_LDBSTOP                      ( ( بنانشانی صحيح ) 0x1 << 6 )  /* (TC) Counter Clock Stopped with RB Loading */
#تعریف_کرو AT91C_TC_LDBDIS                       ( ( بنانشانی صحيح ) 0x1 << 7 )  /* (TC) Counter Clock Disabled with RB Loading */
#تعریف_کرو AT91C_TC_CPCDIS                       ( ( بنانشانی صحيح ) 0x1 << 7 )  /* (TC) Counter Clock Disable with RC Compare */
#تعریف_کرو AT91C_TC_ETRGEDG                      ( ( بنانشانی صحيح ) 0x3 << 8 )  /* (TC) External Trigger Edge Selection */
#تعریف_کرو     AT91C_TC_ETRGEDG_NONE             ( ( بنانشانی صحيح ) 0x0 << 8 )  /* (TC) Edge: None */
#تعریف_کرو     AT91C_TC_ETRGEDG_RISING           ( ( بنانشانی صحيح ) 0x1 << 8 )  /* (TC) Edge: rising edge */
#تعریف_کرو     AT91C_TC_ETRGEDG_FALLING          ( ( بنانشانی صحيح ) 0x2 << 8 )  /* (TC) Edge: falling edge */
#تعریف_کرو     AT91C_TC_ETRGEDG_BOTH             ( ( بنانشانی صحيح ) 0x3 << 8 )  /* (TC) Edge: each edge */
#تعریف_کرو AT91C_TC_EEVTEDG                      ( ( بنانشانی صحيح ) 0x3 << 8 )  /* (TC) External Event Edge Selection */
#تعریف_کرو     AT91C_TC_EEVTEDG_NONE             ( ( بنانشانی صحيح ) 0x0 << 8 )  /* (TC) Edge: None */
#تعریف_کرو     AT91C_TC_EEVTEDG_RISING           ( ( بنانشانی صحيح ) 0x1 << 8 )  /* (TC) Edge: rising edge */
#تعریف_کرو     AT91C_TC_EEVTEDG_FALLING          ( ( بنانشانی صحيح ) 0x2 << 8 )  /* (TC) Edge: falling edge */
#تعریف_کرو     AT91C_TC_EEVTEDG_BOTH             ( ( بنانشانی صحيح ) 0x3 << 8 )  /* (TC) Edge: each edge */
#تعریف_کرو AT91C_TC_ABETRG                       ( ( بنانشانی صحيح ) 0x1 << 10 ) /* (TC) TIOA or TIOB External Trigger Selection */
#تعریف_کرو AT91C_TC_EEVT                         ( ( بنانشانی صحيح ) 0x3 << 10 ) /* (TC) External Event  Selection */
#تعریف_کرو     AT91C_TC_EEVT_NONE                ( ( بنانشانی صحيح ) 0x0 << 10 ) /* (TC) Signal selected as external event: TIOB TIOB direction: input */
#تعریف_کرو     AT91C_TC_EEVT_RISING              ( ( بنانشانی صحيح ) 0x1 << 10 ) /* (TC) Signal selected as external event: XC0 TIOB direction: output */
#تعریف_کرو     AT91C_TC_EEVT_FALLING             ( ( بنانشانی صحيح ) 0x2 << 10 ) /* (TC) Signal selected as external event: XC1 TIOB direction: output */
#تعریف_کرو     AT91C_TC_EEVT_BOTH                ( ( بنانشانی صحيح ) 0x3 << 10 ) /* (TC) Signal selected as external event: XC2 TIOB direction: output */
#تعریف_کرو AT91C_TC_ENETRG                       ( ( بنانشانی صحيح ) 0x1 << 12 ) /* (TC) External Event Trigger enable */
#تعریف_کرو AT91C_TC_WAVESEL                      ( ( بنانشانی صحيح ) 0x3 << 13 ) /* (TC) Waveform  Selection */
#تعریف_کرو     AT91_C_TC_WAVESEL_اتے               ( ( بنانشانی صحيح ) 0x0 << 13 ) /* (TC) UP mode without atomatic trigger on RC Compare */
#تعریف_کرو     AT91C_TC_WAVESEL_UPDOWN           ( ( بنانشانی صحيح ) 0x1 << 13 ) /* (TC) UPDOWN mode without automatic trigger on RC Compare */
#تعریف_کرو     AT91_C_TC_WAVESEL_اتے_AUTO          ( ( بنانشانی صحيح ) 0x2 << 13 ) /* (TC) UP mode with automatic trigger on RC Compare */
#تعریف_کرو     AT91C_TC_WAVESEL_UPDOWN_AUTO      ( ( بنانشانی صحيح ) 0x3 << 13 ) /* (TC) UPDOWN mode with automatic trigger on RC Compare */
#تعریف_کرو AT91C_TC_CPCTRG                       ( ( بنانشانی صحيح ) 0x1 << 14 ) /* (TC) RC Compare Trigger Enable */
#تعریف_کرو AT91C_TC_WAVE                         ( ( بنانشانی صحيح ) 0x1 << 15 ) /* (TC) */
#تعریف_کرو AT91C_TC_LDRA                         ( ( بنانشانی صحيح ) 0x3 << 16 ) /* (TC) RA Loading Selection */
#تعریف_کرو     AT91C_TC_LDRA_NONE                ( ( بنانشانی صحيح ) 0x0 << 16 ) /* (TC) Edge: None */
#تعریف_کرو     AT91C_TC_LDRA_RISING              ( ( بنانشانی صحيح ) 0x1 << 16 ) /* (TC) Edge: rising edge of TIOA */
#تعریف_کرو     AT91C_TC_LDRA_FALLING             ( ( بنانشانی صحيح ) 0x2 << 16 ) /* (TC) Edge: falling edge of TIOA */
#تعریف_کرو     AT91C_TC_LDRA_BOTH                ( ( بنانشانی صحيح ) 0x3 << 16 ) /* (TC) Edge: each edge of TIOA */
#تعریف_کرو AT91C_TC_ACPA                         ( ( بنانشانی صحيح ) 0x3 << 16 ) /* (TC) RA Compare Effect on TIOA */
#تعریف_کرو     AT91C_TC_ACPA_NONE                ( ( بنانشانی صحيح ) 0x0 << 16 ) /* (TC) Effect: none */
#تعریف_کرو     AT91_C_TC_ACPA_سیٹ                 ( ( بنانشانی صحيح ) 0x1 << 16 ) /* (TC) Effect: set */
#تعریف_کرو     AT91C_TC_ACPA_CLEAR               ( ( بنانشانی صحيح ) 0x2 << 16 ) /* (TC) Effect: clear */
#تعریف_کرو     AT91C_TC_ACPA_TOGGLE              ( ( بنانشانی صحيح ) 0x3 << 16 ) /* (TC) Effect: toggle */
#تعریف_کرو AT91C_TC_LDRB                         ( ( بنانشانی صحيح ) 0x3 << 18 ) /* (TC) RB Loading Selection */
#تعریف_کرو     AT91C_TC_LDRB_NONE                ( ( بنانشانی صحيح ) 0x0 << 18 ) /* (TC) Edge: None */
#تعریف_کرو     AT91C_TC_LDRB_RISING              ( ( بنانشانی صحيح ) 0x1 << 18 ) /* (TC) Edge: rising edge of TIOA */
#تعریف_کرو     AT91C_TC_LDRB_FALLING             ( ( بنانشانی صحيح ) 0x2 << 18 ) /* (TC) Edge: falling edge of TIOA */
#تعریف_کرو     AT91C_TC_LDRB_BOTH                ( ( بنانشانی صحيح ) 0x3 << 18 ) /* (TC) Edge: each edge of TIOA */
#تعریف_کرو AT91C_TC_ACPC                         ( ( بنانشانی صحيح ) 0x3 << 18 ) /* (TC) RC Compare Effect on TIOA */
#تعریف_کرو     AT91C_TC_ACPC_NONE                ( ( بنانشانی صحيح ) 0x0 << 18 ) /* (TC) Effect: none */
#تعریف_کرو     AT91_C_TC_ACPC_سیٹ                 ( ( بنانشانی صحيح ) 0x1 << 18 ) /* (TC) Effect: set */
#تعریف_کرو     AT91C_TC_ACPC_CLEAR               ( ( بنانشانی صحيح ) 0x2 << 18 ) /* (TC) Effect: clear */
#تعریف_کرو     AT91C_TC_ACPC_TOGGLE              ( ( بنانشانی صحيح ) 0x3 << 18 ) /* (TC) Effect: toggle */
#تعریف_کرو AT91C_TC_AEEVT                        ( ( بنانشانی صحيح ) 0x3 << 20 ) /* (TC) External Event Effect on TIOA */
#تعریف_کرو     AT91C_TC_AEEVT_NONE               ( ( بنانشانی صحيح ) 0x0 << 20 ) /* (TC) Effect: none */
#تعریف_کرو     AT91_C_TC_AEEVT_سیٹ                ( ( بنانشانی صحيح ) 0x1 << 20 ) /* (TC) Effect: set */
#تعریف_کرو     AT91C_TC_AEEVT_CLEAR              ( ( بنانشانی صحيح ) 0x2 << 20 ) /* (TC) Effect: clear */
#تعریف_کرو     AT91C_TC_AEEVT_TOGGLE             ( ( بنانشانی صحيح ) 0x3 << 20 ) /* (TC) Effect: toggle */
#تعریف_کرو AT91C_TC_ASWTRG                       ( ( بنانشانی صحيح ) 0x3 << 22 ) /* (TC) Software Trigger Effect on TIOA */
#تعریف_کرو     AT91C_TC_ASWTRG_NONE              ( ( بنانشانی صحيح ) 0x0 << 22 ) /* (TC) Effect: none */
#تعریف_کرو     AT91_C_TC_ASWTRG_سیٹ               ( ( بنانشانی صحيح ) 0x1 << 22 ) /* (TC) Effect: set */
#تعریف_کرو     AT91C_TC_ASWTRG_CLEAR             ( ( بنانشانی صحيح ) 0x2 << 22 ) /* (TC) Effect: clear */
#تعریف_کرو     AT91C_TC_ASWTRG_TOGGLE            ( ( بنانشانی صحيح ) 0x3 << 22 ) /* (TC) Effect: toggle */
#تعریف_کرو AT91C_TC_BCPB                         ( ( بنانشانی صحيح ) 0x3 << 24 ) /* (TC) RB Compare Effect on TIOB */
#تعریف_کرو     AT91C_TC_BCPB_NONE                ( ( بنانشانی صحيح ) 0x0 << 24 ) /* (TC) Effect: none */
#تعریف_کرو     AT91_C_TC_BCPB_سیٹ                 ( ( بنانشانی صحيح ) 0x1 << 24 ) /* (TC) Effect: set */
#تعریف_کرو     AT91C_TC_BCPB_CLEAR               ( ( بنانشانی صحيح ) 0x2 << 24 ) /* (TC) Effect: clear */
#تعریف_کرو     AT91C_TC_BCPB_TOGGLE              ( ( بنانشانی صحيح ) 0x3 << 24 ) /* (TC) Effect: toggle */
#تعریف_کرو AT91C_TC_BCPC                         ( ( بنانشانی صحيح ) 0x3 << 26 ) /* (TC) RC Compare Effect on TIOB */
#تعریف_کرو     AT91C_TC_BCPC_NONE                ( ( بنانشانی صحيح ) 0x0 << 26 ) /* (TC) Effect: none */
#تعریف_کرو     AT91_C_TC_BCPC_سیٹ                 ( ( بنانشانی صحيح ) 0x1 << 26 ) /* (TC) Effect: set */
#تعریف_کرو     AT91C_TC_BCPC_CLEAR               ( ( بنانشانی صحيح ) 0x2 << 26 ) /* (TC) Effect: clear */
#تعریف_کرو     AT91C_TC_BCPC_TOGGLE              ( ( بنانشانی صحيح ) 0x3 << 26 ) /* (TC) Effect: toggle */
#تعریف_کرو AT91C_TC_BEEVT                        ( ( بنانشانی صحيح ) 0x3 << 28 ) /* (TC) External Event Effect on TIOB */
#تعریف_کرو     AT91C_TC_BEEVT_NONE               ( ( بنانشانی صحيح ) 0x0 << 28 ) /* (TC) Effect: none */
#تعریف_کرو     AT91_C_TC_BEEVT_سیٹ                ( ( بنانشانی صحيح ) 0x1 << 28 ) /* (TC) Effect: set */
#تعریف_کرو     AT91C_TC_BEEVT_CLEAR              ( ( بنانشانی صحيح ) 0x2 << 28 ) /* (TC) Effect: clear */
#تعریف_کرو     AT91C_TC_BEEVT_TOGGLE             ( ( بنانشانی صحيح ) 0x3 << 28 ) /* (TC) Effect: toggle */
#تعریف_کرو AT91C_TC_BSWTRG                       ( ( بنانشانی صحيح ) 0x3 << 30 ) /* (TC) Software Trigger Effect on TIOB */
#تعریف_کرو     AT91C_TC_BSWTRG_NONE              ( ( بنانشانی صحيح ) 0x0 << 30 ) /* (TC) Effect: none */
#تعریف_کرو     AT91_C_TC_BSWTRG_سیٹ               ( ( بنانشانی صحيح ) 0x1 << 30 ) /* (TC) Effect: set */
#تعریف_کرو     AT91C_TC_BSWTRG_CLEAR             ( ( بنانشانی صحيح ) 0x2 << 30 ) /* (TC) Effect: clear */
#تعریف_کرو     AT91C_TC_BSWTRG_TOGGLE            ( ( بنانشانی صحيح ) 0x3 << 30 ) /* (TC) Effect: toggle */
/* -------- TC_SR : (TC Offset: 0x20) TC Channel Status Register -------- */
#تعریف_کرو AT91C_TC_COVFS                        ( ( بنانشانی صحيح ) 0x1 << 0 )  /* (TC) Counter Overflow */
#تعریف_کرو AT91C_TC_LOVRS                        ( ( بنانشانی صحيح ) 0x1 << 1 )  /* (TC) Load Overrun */
#تعریف_کرو AT91C_TC_CPAS                         ( ( بنانشانی صحيح ) 0x1 << 2 )  /* (TC) RA Compare */
#تعریف_کرو AT91C_TC_CPBS                         ( ( بنانشانی صحيح ) 0x1 << 3 )  /* (TC) RB Compare */
#تعریف_کرو AT91C_TC_CPCS                         ( ( بنانشانی صحيح ) 0x1 << 4 )  /* (TC) RC Compare */
#تعریف_کرو AT91C_TC_LDRAS                        ( ( بنانشانی صحيح ) 0x1 << 5 )  /* (TC) RA Loading */
#تعریف_کرو AT91C_TC_LDRBS                        ( ( بنانشانی صحيح ) 0x1 << 6 )  /* (TC) RB Loading */
#تعریف_کرو AT91C_TC_ETRCS                        ( ( بنانشانی صحيح ) 0x1 << 7 )  /* (TC) External Trigger */
#تعریف_کرو AT91C_TC_ETRGS                        ( ( بنانشانی صحيح ) 0x1 << 16 ) /* (TC) Clock Enabling */
#تعریف_کرو AT91C_TC_MTIOA                        ( ( بنانشانی صحيح ) 0x1 << 17 ) /* (TC) TIOA Mirror */
#تعریف_کرو AT91C_TC_MTIOB                        ( ( بنانشانی صحيح ) 0x1 << 18 ) /* (TC) TIOA Mirror */
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
#تعریف_کرو AT91C_TCB_SYNC                 ( ( بنانشانی صحيح ) 0x1 << 0 ) /* (TCB) Synchro Command */
/* -------- TCB_BMR : (TCB Offset: 0xc4) TC Block Mode Register -------- */
#تعریف_کرو AT91C_TCB_TC0XC0S              ( ( بنانشانی صحيح ) 0x1 << 0 ) /* (TCB) External Clock Signal 0 Selection */
#تعریف_کرو     AT91C_TCB_TC0XC0S_TCLK0    ( ( بنانشانی صحيح ) 0x0 )      /* (TCB) TCLK0 connected to XC0 */
#تعریف_کرو     AT91C_TCB_TC0XC0S_NONE     ( ( بنانشانی صحيح ) 0x1 )      /* (TCB) None signal connected to XC0 */
#تعریف_کرو     AT91C_TCB_TC0XC0S_TIOA1    ( ( بنانشانی صحيح ) 0x2 )      /* (TCB) TIOA1 connected to XC0 */
#تعریف_کرو     AT91C_TCB_TC0XC0S_TIOA2    ( ( بنانشانی صحيح ) 0x3 )      /* (TCB) TIOA2 connected to XC0 */
#تعریف_کرو AT91C_TCB_TC1XC1S              ( ( بنانشانی صحيح ) 0x1 << 2 ) /* (TCB) External Clock Signal 1 Selection */
#تعریف_کرو     AT91C_TCB_TC1XC1S_TCLK1    ( ( بنانشانی صحيح ) 0x0 << 2 ) /* (TCB) TCLK1 connected to XC1 */
#تعریف_کرو     AT91C_TCB_TC1XC1S_NONE     ( ( بنانشانی صحيح ) 0x1 << 2 ) /* (TCB) None signal connected to XC1 */
#تعریف_کرو     AT91C_TCB_TC1XC1S_TIOA0    ( ( بنانشانی صحيح ) 0x2 << 2 ) /* (TCB) TIOA0 connected to XC1 */
#تعریف_کرو     AT91C_TCB_TC1XC1S_TIOA2    ( ( بنانشانی صحيح ) 0x3 << 2 ) /* (TCB) TIOA2 connected to XC1 */
#تعریف_کرو AT91C_TCB_TC2XC2S              ( ( بنانشانی صحيح ) 0x1 << 4 ) /* (TCB) External Clock Signal 2 Selection */
#تعریف_کرو     AT91C_TCB_TC2XC2S_TCLK2    ( ( بنانشانی صحيح ) 0x0 << 4 ) /* (TCB) TCLK2 connected to XC2 */
#تعریف_کرو     AT91C_TCB_TC2XC2S_NONE     ( ( بنانشانی صحيح ) 0x1 << 4 ) /* (TCB) None signal connected to XC2 */
#تعریف_کرو     AT91C_TCB_TC2XC2S_TIOA0    ( ( بنانشانی صحيح ) 0x2 << 4 ) /* (TCB) TIOA0 connected to XC2 */
#تعریف_کرو     AT91C_TCB_TC2XC2S_TIOA2    ( ( بنانشانی صحيح ) 0x3 << 4 ) /* (TCB) TIOA2 connected to XC2 */

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
#تعریف_کرو AT91C_PWMC_CPRE             ( ( بنانشانی صحيح ) 0xF << 0 )  /* (PWMC_CH) Channel Pre-scaler : PWMC_CLKx */
#تعریف_کرو     AT91C_PWMC_CPRE_MCK     ( ( بنانشانی صحيح ) 0x0 )       /* (PWMC_CH) */
#تعریف_کرو     AT91C_PWMC_CPRE_MCKA    ( ( بنانشانی صحيح ) 0xB )       /* (PWMC_CH) */
#تعریف_کرو     AT91C_PWMC_CPRE_MCKB    ( ( بنانشانی صحيح ) 0xC )       /* (PWMC_CH) */
#تعریف_کرو AT91C_PWMC_CALG             ( ( بنانشانی صحيح ) 0x1 << 8 )  /* (PWMC_CH) Channel Alignment */
#تعریف_کرو AT91C_PWMC_CPOL             ( ( بنانشانی صحيح ) 0x1 << 9 )  /* (PWMC_CH) Channel Polarity */
#تعریف_کرو AT91C_PWMC_CPD              ( ( بنانشانی صحيح ) 0x1 << 10 ) /* (PWMC_CH) Channel Update Period */
/* -------- PWMC_CDTYR : (PWMC_CH Offset: 0x4) PWMC Channel Duty Cycle Register -------- */
#تعریف_کرو AT91C_PWMC_CDTY             ( ( بنانشانی صحيح ) 0x0 << 0 )  /* (PWMC_CH) Channel Duty Cycle */
/* -------- PWMC_CPRDR : (PWMC_CH Offset: 0x8) PWMC Channel Period Register -------- */
#تعریف_کرو AT91C_PWMC_CPRD             ( ( بنانشانی صحيح ) 0x0 << 0 )  /* (PWMC_CH) Channel Period */
/* -------- PWMC_CCNTR : (PWMC_CH Offset: 0xc) PWMC Channel Counter Register -------- */
#تعریف_کرو AT91C_PWMC_CCNT             ( ( بنانشانی صحيح ) 0x0 << 0 )  /* (PWMC_CH) Channel Counter */
/* -------- PWMC_CUPDR : (PWMC_CH Offset: 0x10) PWMC Channel Update Register -------- */
#تعریف_کرو AT91C_PWMC_CUPD             ( ( بنانشانی صحيح ) 0x0 << 0 )  /* (PWMC_CH) Channel Update */

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
#تعریف_کرو AT91C_PWMC_DIVA            ( ( بنانشانی صحيح ) 0xFF << 0 )  /* (PWMC) CLKA divide factor. */
#تعریف_کرو AT91C_PWMC_PREA            ( ( بنانشانی صحيح ) 0xF << 8 )   /* (PWMC) Divider Input Clock Prescaler A */
#تعریف_کرو     AT91C_PWMC_PREA_MCK    ( ( بنانشانی صحيح ) 0x0 << 8 )   /* (PWMC) */
#تعریف_کرو AT91C_PWMC_DIVB            ( ( بنانشانی صحيح ) 0xFF << 16 ) /* (PWMC) CLKB divide factor. */
#تعریف_کرو AT91C_PWMC_PREB            ( ( بنانشانی صحيح ) 0xF << 24 )  /* (PWMC) Divider Input Clock Prescaler B */
#تعریف_کرو     AT91C_PWMC_PREB_MCK    ( ( بنانشانی صحيح ) 0x0 << 24 )  /* (PWMC) */
/* -------- PWMC_ENA : (PWMC Offset: 0x4) PWMC Enable Register -------- */
#تعریف_کرو AT91C_PWMC_CHID0           ( ( بنانشانی صحيح ) 0x1 << 0 )   /* (PWMC) Channel ID 0 */
#تعریف_کرو AT91C_PWMC_CHID1           ( ( بنانشانی صحيح ) 0x1 << 1 )   /* (PWMC) Channel ID 1 */
#تعریف_کرو AT91C_PWMC_CHID2           ( ( بنانشانی صحيح ) 0x1 << 2 )   /* (PWMC) Channel ID 2 */
#تعریف_کرو AT91C_PWMC_CHID3           ( ( بنانشانی صحيح ) 0x1 << 3 )   /* (PWMC) Channel ID 3 */
#تعریف_کرو AT91C_PWMC_CHID4           ( ( بنانشانی صحيح ) 0x1 << 4 )   /* (PWMC) Channel ID 4 */
#تعریف_کرو AT91C_PWMC_CHID5           ( ( بنانشانی صحيح ) 0x1 << 5 )   /* (PWMC) Channel ID 5 */
#تعریف_کرو AT91C_PWMC_CHID6           ( ( بنانشانی صحيح ) 0x1 << 6 )   /* (PWMC) Channel ID 6 */
#تعریف_کرو AT91C_PWMC_CHID7           ( ( بنانشانی صحيح ) 0x1 << 7 )   /* (PWMC) Channel ID 7 */
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
    AT91_REG UDP_عدد;        /* Frame Number Register */
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
#تعریف_کرو AT91_C_UDP_FRM_عدد    ( ( بنانشانی صحيح ) 0x7FF << 0 ) /* (UDP) Frame Number as Defined in the Packet Field Formats */
#تعریف_کرو AT91C_UDP_FRM_ERR    ( ( بنانشانی صحيح ) 0x1 << 16 )  /* (UDP) Frame Error */
#تعریف_کرو AT91C_UDP_FRM_OK     ( ( بنانشانی صحيح ) 0x1 << 17 )  /* (UDP) Frame OK */
/* -------- UDP_GLB_STATE : (UDP Offset: 0x4) USB Global State Register -------- */
#تعریف_کرو AT91C_UDP_FADDEN     ( ( بنانشانی صحيح ) 0x1 << 0 )   /* (UDP) Function Address Enable */
#تعریف_کرو AT91C_UDP_CONFG      ( ( بنانشانی صحيح ) 0x1 << 1 )   /* (UDP) Configured */
#تعریف_کرو AT91C_UDP_RMWUPE     ( ( بنانشانی صحيح ) 0x1 << 2 )   /* (UDP) Remote Wake Up Enable */
#تعریف_کرو AT91C_UDP_RSMINPR    ( ( بنانشانی صحيح ) 0x1 << 3 )   /* (UDP) A Resume Has Been Sent to the Host */
/* -------- UDP_FADDR : (UDP Offset: 0x8) USB Function Address Register -------- */
#تعریف_کرو AT91C_UDP_FADD       ( ( بنانشانی صحيح ) 0xFF << 0 )  /* (UDP) Function Address Value */
#تعریف_کرو AT91C_UDP_FEN        ( ( بنانشانی صحيح ) 0x1 << 8 )   /* (UDP) Function Enable */
/* -------- UDP_IER : (UDP Offset: 0x10) USB Interrupt Enable Register -------- */
#تعریف_کرو AT91C_UDP_EPINT0     ( ( بنانشانی صحيح ) 0x1 << 0 )   /* (UDP) Endpoint 0 Interrupt */
#تعریف_کرو AT91C_UDP_EPINT1     ( ( بنانشانی صحيح ) 0x1 << 1 )   /* (UDP) Endpoint 0 Interrupt */
#تعریف_کرو AT91C_UDP_EPINT2     ( ( بنانشانی صحيح ) 0x1 << 2 )   /* (UDP) Endpoint 2 Interrupt */
#تعریف_کرو AT91C_UDP_EPINT3     ( ( بنانشانی صحيح ) 0x1 << 3 )   /* (UDP) Endpoint 3 Interrupt */
#تعریف_کرو AT91C_UDP_EPINT4     ( ( بنانشانی صحيح ) 0x1 << 4 )   /* (UDP) Endpoint 4 Interrupt */
#تعریف_کرو AT91C_UDP_EPINT5     ( ( بنانشانی صحيح ) 0x1 << 5 )   /* (UDP) Endpoint 5 Interrupt */
#تعریف_کرو AT91C_UDP_EPINT6     ( ( بنانشانی صحيح ) 0x1 << 6 )   /* (UDP) Endpoint 6 Interrupt */
#تعریف_کرو AT91C_UDP_EPINT7     ( ( بنانشانی صحيح ) 0x1 << 7 )   /* (UDP) Endpoint 7 Interrupt */
#تعریف_کرو AT91C_UDP_RXSUSP     ( ( بنانشانی صحيح ) 0x1 << 8 )   /* (UDP) USB Suspend Interrupt */
#تعریف_کرو AT91C_UDP_RXRSM      ( ( بنانشانی صحيح ) 0x1 << 9 )   /* (UDP) USB Resume Interrupt */
#تعریف_کرو AT91C_UDP_EXTRSM     ( ( بنانشانی صحيح ) 0x1 << 10 )  /* (UDP) USB External Resume Interrupt */
#تعریف_کرو AT91C_UDP_SOFINT     ( ( بنانشانی صحيح ) 0x1 << 11 )  /* (UDP) USB Start Of frame Interrupt */
#تعریف_کرو AT91C_UDP_WAKEUP     ( ( بنانشانی صحيح ) 0x1 << 13 )  /* (UDP) USB Resume Interrupt */
/* -------- UDP_IDR : (UDP Offset: 0x14) USB Interrupt Disable Register -------- */
/* -------- UDP_IMR : (UDP Offset: 0x18) USB Interrupt Mask Register -------- */
/* -------- UDP_ISR : (UDP Offset: 0x1c) USB Interrupt Status Register -------- */
#تعریف_کرو AT91C_UDP_ENDBUSRES              ( ( بنانشانی صحيح ) 0x1 << 12 ) /* (UDP) USB End Of Bus Reset Interrupt */
/* -------- UDP_ICR : (UDP Offset: 0x20) USB Interrupt Clear Register -------- */
/* -------- UDP_RST_EP : (UDP Offset: 0x28) USB Reset Endpoint Register -------- */
#تعریف_کرو AT91C_UDP_EP0                    ( ( بنانشانی صحيح ) 0x1 << 0 )    /* (UDP) Reset Endpoint 0 */
#تعریف_کرو AT91C_UDP_EP1                    ( ( بنانشانی صحيح ) 0x1 << 1 )    /* (UDP) Reset Endpoint 1 */
#تعریف_کرو AT91C_UDP_EP2                    ( ( بنانشانی صحيح ) 0x1 << 2 )    /* (UDP) Reset Endpoint 2 */
#تعریف_کرو AT91C_UDP_EP3                    ( ( بنانشانی صحيح ) 0x1 << 3 )    /* (UDP) Reset Endpoint 3 */
#تعریف_کرو AT91C_UDP_EP4                    ( ( بنانشانی صحيح ) 0x1 << 4 )    /* (UDP) Reset Endpoint 4 */
#تعریف_کرو AT91C_UDP_EP5                    ( ( بنانشانی صحيح ) 0x1 << 5 )    /* (UDP) Reset Endpoint 5 */
#تعریف_کرو AT91C_UDP_EP6                    ( ( بنانشانی صحيح ) 0x1 << 6 )    /* (UDP) Reset Endpoint 6 */
#تعریف_کرو AT91C_UDP_EP7                    ( ( بنانشانی صحيح ) 0x1 << 7 )    /* (UDP) Reset Endpoint 7 */
/* -------- UDP_CSR : (UDP Offset: 0x30) USB Endpoint Control and Status Register -------- */
#تعریف_کرو AT91C_UDP_TXCOMP                 ( ( بنانشانی صحيح ) 0x1 << 0 )    /* (UDP) Generates an IN packet with data previously written in the DPR */
#تعریف_کرو AT91_C_UDP_RX_انکڑے_BK0            ( ( بنانشانی صحيح ) 0x1 << 1 )    /* (UDP) Receive Data Bank 0 */
#تعریف_کرو AT91C_UDP_RXSETUP                ( ( بنانشانی صحيح ) 0x1 << 2 )    /* (UDP) Sends STALL to the Host (Control endpoints) */
#تعریف_کرو AT91C_UDP_ISOERROR               ( ( بنانشانی صحيح ) 0x1 << 3 )    /* (UDP) Isochronous error (Isochronous endpoints) */
#تعریف_کرو AT91C_UDP_TXPKTRDY               ( ( بنانشانی صحيح ) 0x1 << 4 )    /* (UDP) Transmit Packet Ready */
#تعریف_کرو AT91C_UDP_FORCESTALL             ( ( بنانشانی صحيح ) 0x1 << 5 )    /* (UDP) Force Stall (used by Control, Bulk and Isochronous endpoints). */
#تعریف_کرو AT91_C_UDP_RX_انکڑے_BK1            ( ( بنانشانی صحيح ) 0x1 << 6 )    /* (UDP) Receive Data Bank 1 (only used by endpoints with ping-pong attributes). */
#تعریف_کرو AT91C_UDP_DIR                    ( ( بنانشانی صحيح ) 0x1 << 7 )    /* (UDP) Transfer Direction */
#تعریف_کرو AT91C_UDP_EPTYPE                 ( ( بنانشانی صحيح ) 0x7 << 8 )    /* (UDP) Endpoint type */
#تعریف_کرو     AT91C_UDP_EPTYPE_CTRL        ( ( بنانشانی صحيح ) 0x0 << 8 )    /* (UDP) Control */
#تعریف_کرو     AT91_C_UDP_EPTYPE_ISO_باہرلا     ( ( بنانشانی صحيح ) 0x1 << 8 )    /* (UDP) Isochronous OUT */
#تعریف_کرو     AT91_C_UDP_EPTYPE_BULK_باہرلا    ( ( بنانشانی صحيح ) 0x2 << 8 )    /* (UDP) Bulk OUT */
#تعریف_کرو     AT91_C_UDP_EPTYPE_INT_باہرلا     ( ( بنانشانی صحيح ) 0x3 << 8 )    /* (UDP) Interrupt OUT */
#تعریف_کرو     AT91_C_UDP_EPTYPE_ISO_وچ      ( ( بنانشانی صحيح ) 0x5 << 8 )    /* (UDP) Isochronous IN */
#تعریف_کرو     AT91_C_UDP_EPTYPE_BULK_وچ     ( ( بنانشانی صحيح ) 0x6 << 8 )    /* (UDP) Bulk IN */
#تعریف_کرو     AT91_C_UDP_EPTYPE_INT_وچ      ( ( بنانشانی صحيح ) 0x7 << 8 )    /* (UDP) Interrupt IN */
#تعریف_کرو AT91C_UDP_DTGLE                  ( ( بنانشانی صحيح ) 0x1 << 11 )   /* (UDP) Data Toggle */
#تعریف_کرو AT91C_UDP_EPEDS                  ( ( بنانشانی صحيح ) 0x1 << 15 )   /* (UDP) Endpoint Enable Disable */
#تعریف_کرو AT91C_UDP_RXBYTECNT              ( ( بنانشانی صحيح ) 0x7FF << 16 ) /* (UDP) Number Of Bytes Available in the FIFO */

/* ***************************************************************************** */
/*               REGISTER ADDRESS DEFINITION FOR AT91SAM7S64 */
/* ***************************************************************************** */
/* ========== Register definition for SYSC peripheral ========== */
#تعریف_کرو AT91C_SYSC_SYSC_VRPM    ( ( AT91_REG * ) 0xFFFFFD60 ) /* (SYSC) Voltage Regulator Power Mode Register */
/* ========== Register definition for AIC peripheral ========== */
#تعریف_کرو AT91C_AIC_ICCR          ( ( AT91_REG * ) 0xFFFFF128 ) /* (AIC) Interrupt Clear Command Register */
#تعریف_کرو AT91C_AIC_IECR          ( ( AT91_REG * ) 0xFFFFF120 ) /* (AIC) Interrupt Enable Command Register */
#تعریف_کرو AT91C_AIC_SMR           ( ( AT91_REG * ) 0xFFFFF000 ) /* (AIC) Source Mode Register */
#تعریف_کرو AT91C_AIC_ISCR          ( ( AT91_REG * ) 0xFFFFF12C ) /* (AIC) Interrupt Set Command Register */
#تعریف_کرو AT91C_AIC_EOICR         ( ( AT91_REG * ) 0xFFFFF130 ) /* (AIC) End of Interrupt Command Register */
#تعریف_کرو AT91C_AIC_DCR           ( ( AT91_REG * ) 0xFFFFF138 ) /* (AIC) Debug Control Register (Protect) */
#تعریف_کرو AT91C_AIC_FFER          ( ( AT91_REG * ) 0xFFFFF140 ) /* (AIC) Fast Forcing Enable Register */
#تعریف_کرو AT91C_AIC_SVR           ( ( AT91_REG * ) 0xFFFFF080 ) /* (AIC) Source Vector Register */
#تعریف_کرو AT91C_AIC_SPU           ( ( AT91_REG * ) 0xFFFFF134 ) /* (AIC) Spurious Vector Register */
#تعریف_کرو AT91C_AIC_FFDR          ( ( AT91_REG * ) 0xFFFFF144 ) /* (AIC) Fast Forcing Disable Register */
#تعریف_کرو AT91C_AIC_FVR           ( ( AT91_REG * ) 0xFFFFF104 ) /* (AIC) FIQ Vector Register */
#تعریف_کرو AT91C_AIC_FFSR          ( ( AT91_REG * ) 0xFFFFF148 ) /* (AIC) Fast Forcing Status Register */
#تعریف_کرو AT91C_AIC_IMR           ( ( AT91_REG * ) 0xFFFFF110 ) /* (AIC) Interrupt Mask Register */
#تعریف_کرو AT91C_AIC_ISR           ( ( AT91_REG * ) 0xFFFFF108 ) /* (AIC) Interrupt Status Register */
#تعریف_کرو AT91C_AIC_IVR           ( ( AT91_REG * ) 0xFFFFF100 ) /* (AIC) IRQ Vector Register */
#تعریف_کرو AT91C_AIC_IDCR          ( ( AT91_REG * ) 0xFFFFF124 ) /* (AIC) Interrupt Disable Command Register */
#تعریف_کرو AT91C_AIC_CISR          ( ( AT91_REG * ) 0xFFFFF114 ) /* (AIC) Core Interrupt Status Register */
#تعریف_کرو AT91C_AIC_IPR           ( ( AT91_REG * ) 0xFFFFF10C ) /* (AIC) Interrupt Pending Register */
/* ========== Register definition for DBGU peripheral ========== */
#تعریف_کرو AT91C_DBGU_C2R          ( ( AT91_REG * ) 0xFFFFF244 ) /* (DBGU) Chip ID2 Register */
#تعریف_کرو AT91C_DBGU_THR          ( ( AT91_REG * ) 0xFFFFF21C ) /* (DBGU) Transmitter Holding Register */
#تعریف_کرو AT91C_DBGU_CSR          ( ( AT91_REG * ) 0xFFFFF214 ) /* (DBGU) Channel Status Register */
#تعریف_کرو AT91C_DBGU_IDR          ( ( AT91_REG * ) 0xFFFFF20C ) /* (DBGU) Interrupt Disable Register */
#تعریف_کرو AT91C_DBGU_MR           ( ( AT91_REG * ) 0xFFFFF204 ) /* (DBGU) Mode Register */
#تعریف_کرو AT91C_DBGU_FNTR         ( ( AT91_REG * ) 0xFFFFF248 ) /* (DBGU) Force NTRST Register */
#تعریف_کرو AT91C_DBGU_C1R          ( ( AT91_REG * ) 0xFFFFF240 ) /* (DBGU) Chip ID1 Register */
#تعریف_کرو AT91C_DBGU_BRGR         ( ( AT91_REG * ) 0xFFFFF220 ) /* (DBGU) Baud Rate Generator Register */
#تعریف_کرو AT91C_DBGU_RHR          ( ( AT91_REG * ) 0xFFFFF218 ) /* (DBGU) Receiver Holding Register */
#تعریف_کرو AT91C_DBGU_IMR          ( ( AT91_REG * ) 0xFFFFF210 ) /* (DBGU) Interrupt Mask Register */
#تعریف_کرو AT91C_DBGU_IER          ( ( AT91_REG * ) 0xFFFFF208 ) /* (DBGU) Interrupt Enable Register */
#تعریف_کرو AT91C_DBGU_CR           ( ( AT91_REG * ) 0xFFFFF200 ) /* (DBGU) Control Register */
/* ========== Register definition for PDC_DBGU peripheral ========== */
#تعریف_کرو AT91C_DBGU_TNCR         ( ( AT91_REG * ) 0xFFFFF31C ) /* (PDC_DBGU) Transmit Next Counter Register */
#تعریف_کرو AT91C_DBGU_RNCR         ( ( AT91_REG * ) 0xFFFFF314 ) /* (PDC_DBGU) Receive Next Counter Register */
#تعریف_کرو AT91C_DBGU_PTCR         ( ( AT91_REG * ) 0xFFFFF320 ) /* (PDC_DBGU) PDC Transfer Control Register */
#تعریف_کرو AT91C_DBGU_PTSR         ( ( AT91_REG * ) 0xFFFFF324 ) /* (PDC_DBGU) PDC Transfer Status Register */
#تعریف_کرو AT91C_DBGU_RCR          ( ( AT91_REG * ) 0xFFFFF304 ) /* (PDC_DBGU) Receive Counter Register */
#تعریف_کرو AT91C_DBGU_TCR          ( ( AT91_REG * ) 0xFFFFF30C ) /* (PDC_DBGU) Transmit Counter Register */
#تعریف_کرو AT91C_DBGU_RPR          ( ( AT91_REG * ) 0xFFFFF300 ) /* (PDC_DBGU) Receive Pointer Register */
#تعریف_کرو AT91C_DBGU_TPR          ( ( AT91_REG * ) 0xFFFFF308 ) /* (PDC_DBGU) Transmit Pointer Register */
#تعریف_کرو AT91C_DBGU_RNPR         ( ( AT91_REG * ) 0xFFFFF310 ) /* (PDC_DBGU) Receive Next Pointer Register */
#تعریف_کرو AT91C_DBGU_TNPR         ( ( AT91_REG * ) 0xFFFFF318 ) /* (PDC_DBGU) Transmit Next Pointer Register */
/* ========== Register definition for PIOA peripheral ========== */
#تعریف_کرو AT91C_PIOA_IMR          ( ( AT91_REG * ) 0xFFFFF448 ) /* (PIOA) Interrupt Mask Register */
#تعریف_کرو AT91C_PIOA_IER          ( ( AT91_REG * ) 0xFFFFF440 ) /* (PIOA) Interrupt Enable Register */
#تعریف_کرو AT91C_PIOA_OWDR         ( ( AT91_REG * ) 0xFFFFF4A4 ) /* (PIOA) Output Write Disable Register */
#تعریف_کرو AT91C_PIOA_ISR          ( ( AT91_REG * ) 0xFFFFF44C ) /* (PIOA) Interrupt Status Register */
#تعریف_کرو AT91C_PIOA_PPUDR        ( ( AT91_REG * ) 0xFFFFF460 ) /* (PIOA) Pull-up Disable Register */
#تعریف_کرو AT91C_PIOA_MDSR         ( ( AT91_REG * ) 0xFFFFF458 ) /* (PIOA) Multi-driver Status Register */
#تعریف_کرو AT91C_PIOA_MDER         ( ( AT91_REG * ) 0xFFFFF450 ) /* (PIOA) Multi-driver Enable Register */
#تعریف_کرو AT91_C_PIOA_فی          ( ( AT91_REG * ) 0xFFFFF400 ) /* (PIOA) PIO Enable Register */
#تعریف_کرو AT91C_PIOA_PSR          ( ( AT91_REG * ) 0xFFFFF408 ) /* (PIOA) PIO Status Register */
#تعریف_کرو AT91C_PIOA_OER          ( ( AT91_REG * ) 0xFFFFF410 ) /* (PIOA) Output Enable Register */
#تعریف_کرو AT91C_PIOA_BSR          ( ( AT91_REG * ) 0xFFFFF474 ) /* (PIOA) Select B Register */
#تعریف_کرو AT91C_PIOA_PPUER        ( ( AT91_REG * ) 0xFFFFF464 ) /* (PIOA) Pull-up Enable Register */
#تعریف_کرو AT91C_PIOA_MDDR         ( ( AT91_REG * ) 0xFFFFF454 ) /* (PIOA) Multi-driver Disable Register */
#تعریف_کرو AT91C_PIOA_PDR          ( ( AT91_REG * ) 0xFFFFF404 ) /* (PIOA) PIO Disable Register */
#تعریف_کرو AT91C_PIOA_ODR          ( ( AT91_REG * ) 0xFFFFF414 ) /* (PIOA) Output Disable Registerr */
#تعریف_کرو AT91C_PIOA_IFDR         ( ( AT91_REG * ) 0xFFFFF424 ) /* (PIOA) Input Filter Disable Register */
#تعریف_کرو AT91C_PIOA_ABSR         ( ( AT91_REG * ) 0xFFFFF478 ) /* (PIOA) AB Select Status Register */
#تعریف_کرو AT91C_PIOA_ASR          ( ( AT91_REG * ) 0xFFFFF470 ) /* (PIOA) Select A Register */
#تعریف_کرو AT91C_PIOA_PPUSR        ( ( AT91_REG * ) 0xFFFFF468 ) /* (PIOA) Pad Pull-up Status Register */
#تعریف_کرو AT91C_PIOA_ODSR         ( ( AT91_REG * ) 0xFFFFF438 ) /* (PIOA) Output Data Status Register */
#تعریف_کرو AT91C_PIOA_SODR         ( ( AT91_REG * ) 0xFFFFF430 ) /* (PIOA) Set Output Data Register */
#تعریف_کرو AT91C_PIOA_IFSR         ( ( AT91_REG * ) 0xFFFFF428 ) /* (PIOA) Input Filter Status Register */
#تعریف_کرو AT91C_PIOA_IFER         ( ( AT91_REG * ) 0xFFFFF420 ) /* (PIOA) Input Filter Enable Register */
#تعریف_کرو AT91C_PIOA_OSR          ( ( AT91_REG * ) 0xFFFFF418 ) /* (PIOA) Output Status Register */
#تعریف_کرو AT91C_PIOA_IDR          ( ( AT91_REG * ) 0xFFFFF444 ) /* (PIOA) Interrupt Disable Register */
#تعریف_کرو AT91C_PIOA_PDSR         ( ( AT91_REG * ) 0xFFFFF43C ) /* (PIOA) Pin Data Status Register */
#تعریف_کرو AT91C_PIOA_CODR         ( ( AT91_REG * ) 0xFFFFF434 ) /* (PIOA) Clear Output Data Register */
#تعریف_کرو AT91C_PIOA_OWSR         ( ( AT91_REG * ) 0xFFFFF4A8 ) /* (PIOA) Output Write Status Register */
#تعریف_کرو AT91C_PIOA_OWER         ( ( AT91_REG * ) 0xFFFFF4A0 ) /* (PIOA) Output Write Enable Register */
/* ========== Register definition for CKGR peripheral ========== */
#تعریف_کرو AT91C_CKGR_PLLR         ( ( AT91_REG * ) 0xFFFFFC2C ) /* (CKGR) PLL Register */
#تعریف_کرو AT91C_CKGR_MCFR         ( ( AT91_REG * ) 0xFFFFFC24 ) /* (CKGR) Main Clock  Frequency Register */
#تعریف_کرو AT91C_CKGR_MOR          ( ( AT91_REG * ) 0xFFFFFC20 ) /* (CKGR) Main Oscillator Register */
/* ========== Register definition for PMC peripheral ========== */
#تعریف_کرو AT91C_PMC_SCSR          ( ( AT91_REG * ) 0xFFFFFC08 ) /* (PMC) System Clock Status Register */
#تعریف_کرو AT91C_PMC_SCER          ( ( AT91_REG * ) 0xFFFFFC00 ) /* (PMC) System Clock Enable Register */
#تعریف_کرو AT91C_PMC_IMR           ( ( AT91_REG * ) 0xFFFFFC6C ) /* (PMC) Interrupt Mask Register */
#تعریف_کرو AT91C_PMC_IDR           ( ( AT91_REG * ) 0xFFFFFC64 ) /* (PMC) Interrupt Disable Register */
#تعریف_کرو AT91C_PMC_PCDR          ( ( AT91_REG * ) 0xFFFFFC14 ) /* (PMC) Peripheral Clock Disable Register */
#تعریف_کرو AT91C_PMC_SCDR          ( ( AT91_REG * ) 0xFFFFFC04 ) /* (PMC) System Clock Disable Register */
#تعریف_کرو AT91C_PMC_SR            ( ( AT91_REG * ) 0xFFFFFC68 ) /* (PMC) Status Register */
#تعریف_کرو AT91C_PMC_IER           ( ( AT91_REG * ) 0xFFFFFC60 ) /* (PMC) Interrupt Enable Register */
#تعریف_کرو AT91C_PMC_MCKR          ( ( AT91_REG * ) 0xFFFFFC30 ) /* (PMC) Master Clock Register */
#تعریف_کرو AT91C_PMC_MOR           ( ( AT91_REG * ) 0xFFFFFC20 ) /* (PMC) Main Oscillator Register */
#تعریف_کرو AT91C_PMC_PCER          ( ( AT91_REG * ) 0xFFFFFC10 ) /* (PMC) Peripheral Clock Enable Register */
#تعریف_کرو AT91C_PMC_PCSR          ( ( AT91_REG * ) 0xFFFFFC18 ) /* (PMC) Peripheral Clock Status Register */
#تعریف_کرو AT91C_PMC_PLLR          ( ( AT91_REG * ) 0xFFFFFC2C ) /* (PMC) PLL Register */
#تعریف_کرو AT91C_PMC_MCFR          ( ( AT91_REG * ) 0xFFFFFC24 ) /* (PMC) Main Clock  Frequency Register */
#تعریف_کرو AT91C_PMC_PCKR          ( ( AT91_REG * ) 0xFFFFFC40 ) /* (PMC) Programmable Clock Register */
/* ========== Register definition for RSTC peripheral ========== */
#تعریف_کرو AT91C_RSTC_RSR          ( ( AT91_REG * ) 0xFFFFFD04 ) /* (RSTC) Reset Status Register */
#تعریف_کرو AT91C_RSTC_RMR          ( ( AT91_REG * ) 0xFFFFFD08 ) /* (RSTC) Reset Mode Register */
#تعریف_کرو AT91C_RSTC_RCR          ( ( AT91_REG * ) 0xFFFFFD00 ) /* (RSTC) Reset Control Register */
/* ========== Register definition for RTTC peripheral ========== */
#تعریف_کرو AT91C_RTTC_RTSR         ( ( AT91_REG * ) 0xFFFFFD2C ) /* (RTTC) Real-time Status Register */
#تعریف_کرو AT91C_RTTC_RTAR         ( ( AT91_REG * ) 0xFFFFFD24 ) /* (RTTC) Real-time Alarm Register */
#تعریف_کرو AT91C_RTTC_RTVR         ( ( AT91_REG * ) 0xFFFFFD28 ) /* (RTTC) Real-time Value Register */
#تعریف_کرو AT91C_RTTC_RTMR         ( ( AT91_REG * ) 0xFFFFFD20 ) /* (RTTC) Real-time Mode Register */
/* ========== Register definition for PITC peripheral ========== */
#تعریف_کرو AT91C_PITC_PIIR         ( ( AT91_REG * ) 0xFFFFFD3C ) /* (PITC) Period Interval Image Register */
#تعریف_کرو AT91C_PITC_PISR         ( ( AT91_REG * ) 0xFFFFFD34 ) /* (PITC) Period Interval Status Register */
#تعریف_کرو AT91C_PITC_PIVR         ( ( AT91_REG * ) 0xFFFFFD38 ) /* (PITC) Period Interval Value Register */
#تعریف_کرو AT91C_PITC_PIMR         ( ( AT91_REG * ) 0xFFFFFD30 ) /* (PITC) Period Interval Mode Register */
/* ========== Register definition for WDTC peripheral ========== */
#تعریف_کرو AT91C_WDTC_WDMR         ( ( AT91_REG * ) 0xFFFFFD44 ) /* (WDTC) Watchdog Mode Register */
#تعریف_کرو AT91C_WDTC_WDSR         ( ( AT91_REG * ) 0xFFFFFD48 ) /* (WDTC) Watchdog Status Register */
#تعریف_کرو AT91C_WDTC_WDCR         ( ( AT91_REG * ) 0xFFFFFD40 ) /* (WDTC) Watchdog Control Register */
/* ========== Register definition for MC peripheral ========== */
#تعریف_کرو AT91C_MC_FCR            ( ( AT91_REG * ) 0xFFFFFF64 ) /* (MC) MC Flash Command Register */
#تعریف_کرو AT91C_MC_ASR            ( ( AT91_REG * ) 0xFFFFFF04 ) /* (MC) MC Abort Status Register */
#تعریف_کرو AT91C_MC_FSR            ( ( AT91_REG * ) 0xFFFFFF68 ) /* (MC) MC Flash Status Register */
#تعریف_کرو AT91C_MC_FMR            ( ( AT91_REG * ) 0xFFFFFF60 ) /* (MC) MC Flash Mode Register */
#تعریف_کرو AT91C_MC_AASR           ( ( AT91_REG * ) 0xFFFFFF08 ) /* (MC) MC Abort Address Status Register */
#تعریف_کرو AT91C_MC_RCR            ( ( AT91_REG * ) 0xFFFFFF00 ) /* (MC) MC Remap Control Register */
/* ========== Register definition for PDC_SPI peripheral ========== */
#تعریف_کرو AT91C_SPI_PTCR          ( ( AT91_REG * ) 0xFFFE0120 ) /* (PDC_SPI) PDC Transfer Control Register */
#تعریف_کرو AT91C_SPI_TNPR          ( ( AT91_REG * ) 0xFFFE0118 ) /* (PDC_SPI) Transmit Next Pointer Register */
#تعریف_کرو AT91C_SPI_RNPR          ( ( AT91_REG * ) 0xFFFE0110 ) /* (PDC_SPI) Receive Next Pointer Register */
#تعریف_کرو AT91C_SPI_TPR           ( ( AT91_REG * ) 0xFFFE0108 ) /* (PDC_SPI) Transmit Pointer Register */
#تعریف_کرو AT91C_SPI_RPR           ( ( AT91_REG * ) 0xFFFE0100 ) /* (PDC_SPI) Receive Pointer Register */
#تعریف_کرو AT91C_SPI_PTSR          ( ( AT91_REG * ) 0xFFFE0124 ) /* (PDC_SPI) PDC Transfer Status Register */
#تعریف_کرو AT91C_SPI_TNCR          ( ( AT91_REG * ) 0xFFFE011C ) /* (PDC_SPI) Transmit Next Counter Register */
#تعریف_کرو AT91C_SPI_RNCR          ( ( AT91_REG * ) 0xFFFE0114 ) /* (PDC_SPI) Receive Next Counter Register */
#تعریف_کرو AT91C_SPI_TCR           ( ( AT91_REG * ) 0xFFFE010C ) /* (PDC_SPI) Transmit Counter Register */
#تعریف_کرو AT91C_SPI_RCR           ( ( AT91_REG * ) 0xFFFE0104 ) /* (PDC_SPI) Receive Counter Register */
/* ========== Register definition for SPI peripheral ========== */
#تعریف_کرو AT91C_SPI_CSR           ( ( AT91_REG * ) 0xFFFE0030 ) /* (SPI) Chip Select Register */
#تعریف_کرو AT91C_SPI_IDR           ( ( AT91_REG * ) 0xFFFE0018 ) /* (SPI) Interrupt Disable Register */
#تعریف_کرو AT91C_SPI_SR            ( ( AT91_REG * ) 0xFFFE0010 ) /* (SPI) Status Register */
#تعریف_کرو AT91C_SPI_RDR           ( ( AT91_REG * ) 0xFFFE0008 ) /* (SPI) Receive Data Register */
#تعریف_کرو AT91C_SPI_CR            ( ( AT91_REG * ) 0xFFFE0000 ) /* (SPI) Control Register */
#تعریف_کرو AT91C_SPI_IMR           ( ( AT91_REG * ) 0xFFFE001C ) /* (SPI) Interrupt Mask Register */
#تعریف_کرو AT91C_SPI_IER           ( ( AT91_REG * ) 0xFFFE0014 ) /* (SPI) Interrupt Enable Register */
#تعریف_کرو AT91C_SPI_TDR           ( ( AT91_REG * ) 0xFFFE000C ) /* (SPI) Transmit Data Register */
#تعریف_کرو AT91C_SPI_MR            ( ( AT91_REG * ) 0xFFFE0004 ) /* (SPI) Mode Register */
/* ========== Register definition for PDC_ADC peripheral ========== */
#تعریف_کرو AT91C_ADC_PTCR          ( ( AT91_REG * ) 0xFFFD8120 ) /* (PDC_ADC) PDC Transfer Control Register */
#تعریف_کرو AT91C_ADC_TNPR          ( ( AT91_REG * ) 0xFFFD8118 ) /* (PDC_ADC) Transmit Next Pointer Register */
#تعریف_کرو AT91C_ADC_RNPR          ( ( AT91_REG * ) 0xFFFD8110 ) /* (PDC_ADC) Receive Next Pointer Register */
#تعریف_کرو AT91C_ADC_TPR           ( ( AT91_REG * ) 0xFFFD8108 ) /* (PDC_ADC) Transmit Pointer Register */
#تعریف_کرو AT91C_ADC_RPR           ( ( AT91_REG * ) 0xFFFD8100 ) /* (PDC_ADC) Receive Pointer Register */
#تعریف_کرو AT91C_ADC_PTSR          ( ( AT91_REG * ) 0xFFFD8124 ) /* (PDC_ADC) PDC Transfer Status Register */
#تعریف_کرو AT91C_ADC_TNCR          ( ( AT91_REG * ) 0xFFFD811C ) /* (PDC_ADC) Transmit Next Counter Register */
#تعریف_کرو AT91C_ADC_RNCR          ( ( AT91_REG * ) 0xFFFD8114 ) /* (PDC_ADC) Receive Next Counter Register */
#تعریف_کرو AT91C_ADC_TCR           ( ( AT91_REG * ) 0xFFFD810C ) /* (PDC_ADC) Transmit Counter Register */
#تعریف_کرو AT91C_ADC_RCR           ( ( AT91_REG * ) 0xFFFD8104 ) /* (PDC_ADC) Receive Counter Register */
/* ========== Register definition for ADC peripheral ========== */
#تعریف_کرو AT91C_ADC_IMR           ( ( AT91_REG * ) 0xFFFD802C ) /* (ADC) ADC Interrupt Mask Register */
#تعریف_کرو AT91C_ADC_CDR4          ( ( AT91_REG * ) 0xFFFD8040 ) /* (ADC) ADC Channel Data Register 4 */
#تعریف_کرو AT91C_ADC_CDR2          ( ( AT91_REG * ) 0xFFFD8038 ) /* (ADC) ADC Channel Data Register 2 */
#تعریف_کرو AT91C_ADC_CDR0          ( ( AT91_REG * ) 0xFFFD8030 ) /* (ADC) ADC Channel Data Register 0 */
#تعریف_کرو AT91C_ADC_CDR7          ( ( AT91_REG * ) 0xFFFD804C ) /* (ADC) ADC Channel Data Register 7 */
#تعریف_کرو AT91C_ADC_CDR1          ( ( AT91_REG * ) 0xFFFD8034 ) /* (ADC) ADC Channel Data Register 1 */
#تعریف_کرو AT91C_ADC_CDR3          ( ( AT91_REG * ) 0xFFFD803C ) /* (ADC) ADC Channel Data Register 3 */
#تعریف_کرو AT91C_ADC_CDR5          ( ( AT91_REG * ) 0xFFFD8044 ) /* (ADC) ADC Channel Data Register 5 */
#تعریف_کرو AT91C_ADC_MR            ( ( AT91_REG * ) 0xFFFD8004 ) /* (ADC) ADC Mode Register */
#تعریف_کرو AT91C_ADC_CDR6          ( ( AT91_REG * ) 0xFFFD8048 ) /* (ADC) ADC Channel Data Register 6 */
#تعریف_کرو AT91C_ADC_CR            ( ( AT91_REG * ) 0xFFFD8000 ) /* (ADC) ADC Control Register */
#تعریف_کرو AT91C_ADC_CHER          ( ( AT91_REG * ) 0xFFFD8010 ) /* (ADC) ADC Channel Enable Register */
#تعریف_کرو AT91C_ADC_CHSR          ( ( AT91_REG * ) 0xFFFD8018 ) /* (ADC) ADC Channel Status Register */
#تعریف_کرو AT91C_ADC_IER           ( ( AT91_REG * ) 0xFFFD8024 ) /* (ADC) ADC Interrupt Enable Register */
#تعریف_کرو AT91C_ADC_SR            ( ( AT91_REG * ) 0xFFFD801C ) /* (ADC) ADC Status Register */
#تعریف_کرو AT91C_ADC_CHDR          ( ( AT91_REG * ) 0xFFFD8014 ) /* (ADC) ADC Channel Disable Register */
#تعریف_کرو AT91C_ADC_IDR           ( ( AT91_REG * ) 0xFFFD8028 ) /* (ADC) ADC Interrupt Disable Register */
#تعریف_کرو AT91C_ADC_LCDR          ( ( AT91_REG * ) 0xFFFD8020 ) /* (ADC) ADC Last Converted Data Register */
/* ========== Register definition for PDC_SSC peripheral ========== */
#تعریف_کرو AT91C_SSC_PTCR          ( ( AT91_REG * ) 0xFFFD4120 ) /* (PDC_SSC) PDC Transfer Control Register */
#تعریف_کرو AT91C_SSC_TNPR          ( ( AT91_REG * ) 0xFFFD4118 ) /* (PDC_SSC) Transmit Next Pointer Register */
#تعریف_کرو AT91C_SSC_RNPR          ( ( AT91_REG * ) 0xFFFD4110 ) /* (PDC_SSC) Receive Next Pointer Register */
#تعریف_کرو AT91C_SSC_TPR           ( ( AT91_REG * ) 0xFFFD4108 ) /* (PDC_SSC) Transmit Pointer Register */
#تعریف_کرو AT91C_SSC_RPR           ( ( AT91_REG * ) 0xFFFD4100 ) /* (PDC_SSC) Receive Pointer Register */
#تعریف_کرو AT91C_SSC_PTSR          ( ( AT91_REG * ) 0xFFFD4124 ) /* (PDC_SSC) PDC Transfer Status Register */
#تعریف_کرو AT91C_SSC_TNCR          ( ( AT91_REG * ) 0xFFFD411C ) /* (PDC_SSC) Transmit Next Counter Register */
#تعریف_کرو AT91C_SSC_RNCR          ( ( AT91_REG * ) 0xFFFD4114 ) /* (PDC_SSC) Receive Next Counter Register */
#تعریف_کرو AT91C_SSC_TCR           ( ( AT91_REG * ) 0xFFFD410C ) /* (PDC_SSC) Transmit Counter Register */
#تعریف_کرو AT91C_SSC_RCR           ( ( AT91_REG * ) 0xFFFD4104 ) /* (PDC_SSC) Receive Counter Register */
/* ========== Register definition for SSC peripheral ========== */
#تعریف_کرو AT91C_SSC_RFMR          ( ( AT91_REG * ) 0xFFFD4014 ) /* (SSC) Receive Frame Mode Register */
#تعریف_کرو AT91C_SSC_CMR           ( ( AT91_REG * ) 0xFFFD4004 ) /* (SSC) Clock Mode Register */
#تعریف_کرو AT91C_SSC_IDR           ( ( AT91_REG * ) 0xFFFD4048 ) /* (SSC) Interrupt Disable Register */
#تعریف_کرو AT91C_SSC_SR            ( ( AT91_REG * ) 0xFFFD4040 ) /* (SSC) Status Register */
#تعریف_کرو AT91C_SSC_RC0R          ( ( AT91_REG * ) 0xFFFD4038 ) /* (SSC) Receive Compare 0 Register */
#تعریف_کرو AT91C_SSC_RSHR          ( ( AT91_REG * ) 0xFFFD4030 ) /* (SSC) Receive Sync Holding Register */
#تعریف_کرو AT91C_SSC_RHR           ( ( AT91_REG * ) 0xFFFD4020 ) /* (SSC) Receive Holding Register */
#تعریف_کرو AT91C_SSC_TCMR          ( ( AT91_REG * ) 0xFFFD4018 ) /* (SSC) Transmit Clock Mode Register */
#تعریف_کرو AT91C_SSC_RCMR          ( ( AT91_REG * ) 0xFFFD4010 ) /* (SSC) Receive Clock ModeRegister */
#تعریف_کرو AT91C_SSC_CR            ( ( AT91_REG * ) 0xFFFD4000 ) /* (SSC) Control Register */
#تعریف_کرو AT91C_SSC_IMR           ( ( AT91_REG * ) 0xFFFD404C ) /* (SSC) Interrupt Mask Register */
#تعریف_کرو AT91C_SSC_IER           ( ( AT91_REG * ) 0xFFFD4044 ) /* (SSC) Interrupt Enable Register */
#تعریف_کرو AT91C_SSC_RC1R          ( ( AT91_REG * ) 0xFFFD403C ) /* (SSC) Receive Compare 1 Register */
#تعریف_کرو AT91C_SSC_TSHR          ( ( AT91_REG * ) 0xFFFD4034 ) /* (SSC) Transmit Sync Holding Register */
#تعریف_کرو AT91C_SSC_THR           ( ( AT91_REG * ) 0xFFFD4024 ) /* (SSC) Transmit Holding Register */
#تعریف_کرو AT91C_SSC_TFMR          ( ( AT91_REG * ) 0xFFFD401C ) /* (SSC) Transmit Frame Mode Register */
/* ========== Register definition for PDC_US1 peripheral ========== */
#تعریف_کرو AT91C_US1_PTSR          ( ( AT91_REG * ) 0xFFFC4124 ) /* (PDC_US1) PDC Transfer Status Register */
#تعریف_کرو AT91C_US1_TNCR          ( ( AT91_REG * ) 0xFFFC411C ) /* (PDC_US1) Transmit Next Counter Register */
#تعریف_کرو AT91C_US1_RNCR          ( ( AT91_REG * ) 0xFFFC4114 ) /* (PDC_US1) Receive Next Counter Register */
#تعریف_کرو AT91C_US1_TCR           ( ( AT91_REG * ) 0xFFFC410C ) /* (PDC_US1) Transmit Counter Register */
#تعریف_کرو AT91C_US1_RCR           ( ( AT91_REG * ) 0xFFFC4104 ) /* (PDC_US1) Receive Counter Register */
#تعریف_کرو AT91C_US1_PTCR          ( ( AT91_REG * ) 0xFFFC4120 ) /* (PDC_US1) PDC Transfer Control Register */
#تعریف_کرو AT91C_US1_TNPR          ( ( AT91_REG * ) 0xFFFC4118 ) /* (PDC_US1) Transmit Next Pointer Register */
#تعریف_کرو AT91C_US1_RNPR          ( ( AT91_REG * ) 0xFFFC4110 ) /* (PDC_US1) Receive Next Pointer Register */
#تعریف_کرو AT91C_US1_TPR           ( ( AT91_REG * ) 0xFFFC4108 ) /* (PDC_US1) Transmit Pointer Register */
#تعریف_کرو AT91C_US1_RPR           ( ( AT91_REG * ) 0xFFFC4100 ) /* (PDC_US1) Receive Pointer Register */
/* ========== Register definition for US1 peripheral ========== */
#تعریف_کرو AT91C_US1_XXR           ( ( AT91_REG * ) 0xFFFC4048 ) /* (US1) XON_XOFF Register */
#تعریف_کرو AT91C_US1_RHR           ( ( AT91_REG * ) 0xFFFC4018 ) /* (US1) Receiver Holding Register */
#تعریف_کرو AT91C_US1_IMR           ( ( AT91_REG * ) 0xFFFC4010 ) /* (US1) Interrupt Mask Register */
#تعریف_کرو AT91C_US1_IER           ( ( AT91_REG * ) 0xFFFC4008 ) /* (US1) Interrupt Enable Register */
#تعریف_کرو AT91C_US1_CR            ( ( AT91_REG * ) 0xFFFC4000 ) /* (US1) Control Register */
#تعریف_کرو AT91C_US1_RTOR          ( ( AT91_REG * ) 0xFFFC4024 ) /* (US1) Receiver Time-out Register */
#تعریف_کرو AT91C_US1_THR           ( ( AT91_REG * ) 0xFFFC401C ) /* (US1) Transmitter Holding Register */
#تعریف_کرو AT91C_US1_CSR           ( ( AT91_REG * ) 0xFFFC4014 ) /* (US1) Channel Status Register */
#تعریف_کرو AT91C_US1_IDR           ( ( AT91_REG * ) 0xFFFC400C ) /* (US1) Interrupt Disable Register */
#تعریف_کرو AT91C_US1_FIDI          ( ( AT91_REG * ) 0xFFFC4040 ) /* (US1) FI_DI_Ratio Register */
#تعریف_کرو AT91C_US1_BRGR          ( ( AT91_REG * ) 0xFFFC4020 ) /* (US1) Baud Rate Generator Register */
#تعریف_کرو AT91C_US1_TTGR          ( ( AT91_REG * ) 0xFFFC4028 ) /* (US1) Transmitter Time-guard Register */
#تعریف_کرو AT91C_US1_IF            ( ( AT91_REG * ) 0xFFFC404C ) /* (US1) IRDA_FILTER Register */
#تعریف_کرو AT91C_US1_NER           ( ( AT91_REG * ) 0xFFFC4044 ) /* (US1) Nb Errors Register */
#تعریف_کرو AT91C_US1_MR            ( ( AT91_REG * ) 0xFFFC4004 ) /* (US1) Mode Register */
/* ========== Register definition for PDC_US0 peripheral ========== */
#تعریف_کرو AT91C_US0_PTCR          ( ( AT91_REG * ) 0xFFFC0120 ) /* (PDC_US0) PDC Transfer Control Register */
#تعریف_کرو AT91C_US0_TNPR          ( ( AT91_REG * ) 0xFFFC0118 ) /* (PDC_US0) Transmit Next Pointer Register */
#تعریف_کرو AT91C_US0_RNPR          ( ( AT91_REG * ) 0xFFFC0110 ) /* (PDC_US0) Receive Next Pointer Register */
#تعریف_کرو AT91C_US0_TPR           ( ( AT91_REG * ) 0xFFFC0108 ) /* (PDC_US0) Transmit Pointer Register */
#تعریف_کرو AT91C_US0_RPR           ( ( AT91_REG * ) 0xFFFC0100 ) /* (PDC_US0) Receive Pointer Register */
#تعریف_کرو AT91C_US0_PTSR          ( ( AT91_REG * ) 0xFFFC0124 ) /* (PDC_US0) PDC Transfer Status Register */
#تعریف_کرو AT91C_US0_TNCR          ( ( AT91_REG * ) 0xFFFC011C ) /* (PDC_US0) Transmit Next Counter Register */
#تعریف_کرو AT91C_US0_RNCR          ( ( AT91_REG * ) 0xFFFC0114 ) /* (PDC_US0) Receive Next Counter Register */
#تعریف_کرو AT91C_US0_TCR           ( ( AT91_REG * ) 0xFFFC010C ) /* (PDC_US0) Transmit Counter Register */
#تعریف_کرو AT91C_US0_RCR           ( ( AT91_REG * ) 0xFFFC0104 ) /* (PDC_US0) Receive Counter Register */
/* ========== Register definition for US0 peripheral ========== */
#تعریف_کرو AT91C_US0_TTGR          ( ( AT91_REG * ) 0xFFFC0028 ) /* (US0) Transmitter Time-guard Register */
#تعریف_کرو AT91C_US0_BRGR          ( ( AT91_REG * ) 0xFFFC0020 ) /* (US0) Baud Rate Generator Register */
#تعریف_کرو AT91C_US0_RHR           ( ( AT91_REG * ) 0xFFFC0018 ) /* (US0) Receiver Holding Register */
#تعریف_کرو AT91C_US0_IMR           ( ( AT91_REG * ) 0xFFFC0010 ) /* (US0) Interrupt Mask Register */
#تعریف_کرو AT91C_US0_NER           ( ( AT91_REG * ) 0xFFFC0044 ) /* (US0) Nb Errors Register */
#تعریف_کرو AT91C_US0_RTOR          ( ( AT91_REG * ) 0xFFFC0024 ) /* (US0) Receiver Time-out Register */
#تعریف_کرو AT91C_US0_XXR           ( ( AT91_REG * ) 0xFFFC0048 ) /* (US0) XON_XOFF Register */
#تعریف_کرو AT91C_US0_FIDI          ( ( AT91_REG * ) 0xFFFC0040 ) /* (US0) FI_DI_Ratio Register */
#تعریف_کرو AT91C_US0_CR            ( ( AT91_REG * ) 0xFFFC0000 ) /* (US0) Control Register */
#تعریف_کرو AT91C_US0_IER           ( ( AT91_REG * ) 0xFFFC0008 ) /* (US0) Interrupt Enable Register */
#تعریف_کرو AT91C_US0_IF            ( ( AT91_REG * ) 0xFFFC004C ) /* (US0) IRDA_FILTER Register */
#تعریف_کرو AT91C_US0_MR            ( ( AT91_REG * ) 0xFFFC0004 ) /* (US0) Mode Register */
#تعریف_کرو AT91C_US0_IDR           ( ( AT91_REG * ) 0xFFFC000C ) /* (US0) Interrupt Disable Register */
#تعریف_کرو AT91C_US0_CSR           ( ( AT91_REG * ) 0xFFFC0014 ) /* (US0) Channel Status Register */
#تعریف_کرو AT91C_US0_THR           ( ( AT91_REG * ) 0xFFFC001C ) /* (US0) Transmitter Holding Register */
/* ========== Register definition for TWI peripheral ========== */
#تعریف_کرو AT91C_TWI_RHR           ( ( AT91_REG * ) 0xFFFB8030 ) /* (TWI) Receive Holding Register */
#تعریف_کرو AT91C_TWI_IDR           ( ( AT91_REG * ) 0xFFFB8028 ) /* (TWI) Interrupt Disable Register */
#تعریف_کرو AT91C_TWI_SR            ( ( AT91_REG * ) 0xFFFB8020 ) /* (TWI) Status Register */
#تعریف_کرو AT91C_TWI_CWGR          ( ( AT91_REG * ) 0xFFFB8010 ) /* (TWI) Clock Waveform Generator Register */
#تعریف_کرو AT91C_TWI_SMR           ( ( AT91_REG * ) 0xFFFB8008 ) /* (TWI) Slave Mode Register */
#تعریف_کرو AT91C_TWI_CR            ( ( AT91_REG * ) 0xFFFB8000 ) /* (TWI) Control Register */
#تعریف_کرو AT91C_TWI_THR           ( ( AT91_REG * ) 0xFFFB8034 ) /* (TWI) Transmit Holding Register */
#تعریف_کرو AT91C_TWI_IMR           ( ( AT91_REG * ) 0xFFFB802C ) /* (TWI) Interrupt Mask Register */
#تعریف_کرو AT91C_TWI_IER           ( ( AT91_REG * ) 0xFFFB8024 ) /* (TWI) Interrupt Enable Register */
#تعریف_کرو AT91C_TWI_IADR          ( ( AT91_REG * ) 0xFFFB800C ) /* (TWI) Internal Address Register */
#تعریف_کرو AT91C_TWI_MMR           ( ( AT91_REG * ) 0xFFFB8004 ) /* (TWI) Master Mode Register */
/* ========== Register definition for TC2 peripheral ========== */
#تعریف_کرو AT91C_TC2_IMR           ( ( AT91_REG * ) 0xFFFA00AC ) /* (TC2) Interrupt Mask Register */
#تعریف_کرو AT91C_TC2_IER           ( ( AT91_REG * ) 0xFFFA00A4 ) /* (TC2) Interrupt Enable Register */
#تعریف_کرو AT91C_TC2_RC            ( ( AT91_REG * ) 0xFFFA009C ) /* (TC2) Register C */
#تعریف_کرو AT91C_TC2_RA            ( ( AT91_REG * ) 0xFFFA0094 ) /* (TC2) Register A */
#تعریف_کرو AT91C_TC2_CMR           ( ( AT91_REG * ) 0xFFFA0084 ) /* (TC2) Channel Mode Register (Capture Mode / Waveform Mode) */
#تعریف_کرو AT91C_TC2_IDR           ( ( AT91_REG * ) 0xFFFA00A8 ) /* (TC2) Interrupt Disable Register */
#تعریف_کرو AT91C_TC2_SR            ( ( AT91_REG * ) 0xFFFA00A0 ) /* (TC2) Status Register */
#تعریف_کرو AT91C_TC2_RB            ( ( AT91_REG * ) 0xFFFA0098 ) /* (TC2) Register B */
#تعریف_کرو AT91C_TC2_CV            ( ( AT91_REG * ) 0xFFFA0090 ) /* (TC2) Counter Value */
#تعریف_کرو AT91C_TC2_CCR           ( ( AT91_REG * ) 0xFFFA0080 ) /* (TC2) Channel Control Register */
/* ========== Register definition for TC1 peripheral ========== */
#تعریف_کرو AT91C_TC1_IMR           ( ( AT91_REG * ) 0xFFFA006C ) /* (TC1) Interrupt Mask Register */
#تعریف_کرو AT91C_TC1_IER           ( ( AT91_REG * ) 0xFFFA0064 ) /* (TC1) Interrupt Enable Register */
#تعریف_کرو AT91C_TC1_RC            ( ( AT91_REG * ) 0xFFFA005C ) /* (TC1) Register C */
#تعریف_کرو AT91C_TC1_RA            ( ( AT91_REG * ) 0xFFFA0054 ) /* (TC1) Register A */
#تعریف_کرو AT91C_TC1_CMR           ( ( AT91_REG * ) 0xFFFA0044 ) /* (TC1) Channel Mode Register (Capture Mode / Waveform Mode) */
#تعریف_کرو AT91C_TC1_IDR           ( ( AT91_REG * ) 0xFFFA0068 ) /* (TC1) Interrupt Disable Register */
#تعریف_کرو AT91C_TC1_SR            ( ( AT91_REG * ) 0xFFFA0060 ) /* (TC1) Status Register */
#تعریف_کرو AT91C_TC1_RB            ( ( AT91_REG * ) 0xFFFA0058 ) /* (TC1) Register B */
#تعریف_کرو AT91C_TC1_CV            ( ( AT91_REG * ) 0xFFFA0050 ) /* (TC1) Counter Value */
#تعریف_کرو AT91C_TC1_CCR           ( ( AT91_REG * ) 0xFFFA0040 ) /* (TC1) Channel Control Register */
/* ========== Register definition for TC0 peripheral ========== */
#تعریف_کرو AT91C_TC0_IMR           ( ( AT91_REG * ) 0xFFFA002C ) /* (TC0) Interrupt Mask Register */
#تعریف_کرو AT91C_TC0_IER           ( ( AT91_REG * ) 0xFFFA0024 ) /* (TC0) Interrupt Enable Register */
#تعریف_کرو AT91C_TC0_RC            ( ( AT91_REG * ) 0xFFFA001C ) /* (TC0) Register C */
#تعریف_کرو AT91C_TC0_RA            ( ( AT91_REG * ) 0xFFFA0014 ) /* (TC0) Register A */
#تعریف_کرو AT91C_TC0_CMR           ( ( AT91_REG * ) 0xFFFA0004 ) /* (TC0) Channel Mode Register (Capture Mode / Waveform Mode) */
#تعریف_کرو AT91C_TC0_IDR           ( ( AT91_REG * ) 0xFFFA0028 ) /* (TC0) Interrupt Disable Register */
#تعریف_کرو AT91C_TC0_SR            ( ( AT91_REG * ) 0xFFFA0020 ) /* (TC0) Status Register */
#تعریف_کرو AT91C_TC0_RB            ( ( AT91_REG * ) 0xFFFA0018 ) /* (TC0) Register B */
#تعریف_کرو AT91C_TC0_CV            ( ( AT91_REG * ) 0xFFFA0010 ) /* (TC0) Counter Value */
#تعریف_کرو AT91C_TC0_CCR           ( ( AT91_REG * ) 0xFFFA0000 ) /* (TC0) Channel Control Register */
/* ========== Register definition for TCB peripheral ========== */
#تعریف_کرو AT91C_TCB_BMR           ( ( AT91_REG * ) 0xFFFA00C4 ) /* (TCB) TC Block Mode Register */
#تعریف_کرو AT91C_TCB_BCR           ( ( AT91_REG * ) 0xFFFA00C0 ) /* (TCB) TC Block Control Register */
/* ========== Register definition for PWMC_CH3 peripheral ========== */
#تعریف_کرو AT91C_CH3_CUPDR         ( ( AT91_REG * ) 0xFFFCC270 ) /* (PWMC_CH3) Channel Update Register */
#تعریف_کرو AT91C_CH3_CPRDR         ( ( AT91_REG * ) 0xFFFCC268 ) /* (PWMC_CH3) Channel Period Register */
#تعریف_کرو AT91C_CH3_CMR           ( ( AT91_REG * ) 0xFFFCC260 ) /* (PWMC_CH3) Channel Mode Register */
#تعریف_کرو AT91C_CH3_Reserved      ( ( AT91_REG * ) 0xFFFCC274 ) /* (PWMC_CH3) Reserved */
#تعریف_کرو AT91C_CH3_CCNTR         ( ( AT91_REG * ) 0xFFFCC26C ) /* (PWMC_CH3) Channel Counter Register */
#تعریف_کرو AT91C_CH3_CDTYR         ( ( AT91_REG * ) 0xFFFCC264 ) /* (PWMC_CH3) Channel Duty Cycle Register */
/* ========== Register definition for PWMC_CH2 peripheral ========== */
#تعریف_کرو AT91C_CH2_CUPDR         ( ( AT91_REG * ) 0xFFFCC250 ) /* (PWMC_CH2) Channel Update Register */
#تعریف_کرو AT91C_CH2_CPRDR         ( ( AT91_REG * ) 0xFFFCC248 ) /* (PWMC_CH2) Channel Period Register */
#تعریف_کرو AT91C_CH2_CMR           ( ( AT91_REG * ) 0xFFFCC240 ) /* (PWMC_CH2) Channel Mode Register */
#تعریف_کرو AT91C_CH2_Reserved      ( ( AT91_REG * ) 0xFFFCC254 ) /* (PWMC_CH2) Reserved */
#تعریف_کرو AT91C_CH2_CCNTR         ( ( AT91_REG * ) 0xFFFCC24C ) /* (PWMC_CH2) Channel Counter Register */
#تعریف_کرو AT91C_CH2_CDTYR         ( ( AT91_REG * ) 0xFFFCC244 ) /* (PWMC_CH2) Channel Duty Cycle Register */
/* ========== Register definition for PWMC_CH1 peripheral ========== */
#تعریف_کرو AT91C_CH1_CUPDR         ( ( AT91_REG * ) 0xFFFCC230 ) /* (PWMC_CH1) Channel Update Register */
#تعریف_کرو AT91C_CH1_CPRDR         ( ( AT91_REG * ) 0xFFFCC228 ) /* (PWMC_CH1) Channel Period Register */
#تعریف_کرو AT91C_CH1_CMR           ( ( AT91_REG * ) 0xFFFCC220 ) /* (PWMC_CH1) Channel Mode Register */
#تعریف_کرو AT91C_CH1_Reserved      ( ( AT91_REG * ) 0xFFFCC234 ) /* (PWMC_CH1) Reserved */
#تعریف_کرو AT91C_CH1_CCNTR         ( ( AT91_REG * ) 0xFFFCC22C ) /* (PWMC_CH1) Channel Counter Register */
#تعریف_کرو AT91C_CH1_CDTYR         ( ( AT91_REG * ) 0xFFFCC224 ) /* (PWMC_CH1) Channel Duty Cycle Register */
/* ========== Register definition for PWMC_CH0 peripheral ========== */
#تعریف_کرو AT91C_CH0_CUPDR         ( ( AT91_REG * ) 0xFFFCC210 ) /* (PWMC_CH0) Channel Update Register */
#تعریف_کرو AT91C_CH0_CPRDR         ( ( AT91_REG * ) 0xFFFCC208 ) /* (PWMC_CH0) Channel Period Register */
#تعریف_کرو AT91C_CH0_CMR           ( ( AT91_REG * ) 0xFFFCC200 ) /* (PWMC_CH0) Channel Mode Register */
#تعریف_کرو AT91C_CH0_Reserved      ( ( AT91_REG * ) 0xFFFCC214 ) /* (PWMC_CH0) Reserved */
#تعریف_کرو AT91C_CH0_CCNTR         ( ( AT91_REG * ) 0xFFFCC20C ) /* (PWMC_CH0) Channel Counter Register */
#تعریف_کرو AT91C_CH0_CDTYR         ( ( AT91_REG * ) 0xFFFCC204 ) /* (PWMC_CH0) Channel Duty Cycle Register */
/* ========== Register definition for PWMC peripheral ========== */
#تعریف_کرو AT91C_PWMC_VR           ( ( AT91_REG * ) 0xFFFCC0FC ) /* (PWMC) PWMC Version Register */
#تعریف_کرو AT91C_PWMC_ISR          ( ( AT91_REG * ) 0xFFFCC01C ) /* (PWMC) PWMC Interrupt Status Register */
#تعریف_کرو AT91C_PWMC_IDR          ( ( AT91_REG * ) 0xFFFCC014 ) /* (PWMC) PWMC Interrupt Disable Register */
#تعریف_کرو AT91C_PWMC_SR           ( ( AT91_REG * ) 0xFFFCC00C ) /* (PWMC) PWMC Status Register */
#تعریف_کرو AT91C_PWMC_ENA          ( ( AT91_REG * ) 0xFFFCC004 ) /* (PWMC) PWMC Enable Register */
#تعریف_کرو AT91C_PWMC_IMR          ( ( AT91_REG * ) 0xFFFCC018 ) /* (PWMC) PWMC Interrupt Mask Register */
#تعریف_کرو AT91C_PWMC_MR           ( ( AT91_REG * ) 0xFFFCC000 ) /* (PWMC) PWMC Mode Register */
#تعریف_کرو AT91C_PWMC_DIS          ( ( AT91_REG * ) 0xFFFCC008 ) /* (PWMC) PWMC Disable Register */
#تعریف_کرو AT91C_PWMC_IER          ( ( AT91_REG * ) 0xFFFCC010 ) /* (PWMC) PWMC Interrupt Enable Register */
/* ========== Register definition for UDP peripheral ========== */
#تعریف_کرو AT91C_UDP_ISR           ( ( AT91_REG * ) 0xFFFB001C ) /* (UDP) Interrupt Status Register */
#تعریف_کرو AT91C_UDP_IDR           ( ( AT91_REG * ) 0xFFFB0014 ) /* (UDP) Interrupt Disable Register */
#تعریف_کرو AT91C_UDP_GLBSTATE      ( ( AT91_REG * ) 0xFFFB0004 ) /* (UDP) Global State Register */
#تعریف_کرو AT91C_UDP_FDR           ( ( AT91_REG * ) 0xFFFB0050 ) /* (UDP) Endpoint FIFO Data Register */
#تعریف_کرو AT91C_UDP_CSR           ( ( AT91_REG * ) 0xFFFB0030 ) /* (UDP) Endpoint Control and Status Register */
#تعریف_کرو AT91C_UDP_RSTEP         ( ( AT91_REG * ) 0xFFFB0028 ) /* (UDP) Reset Endpoint Register */
#تعریف_کرو AT91C_UDP_ICR           ( ( AT91_REG * ) 0xFFFB0020 ) /* (UDP) Interrupt Clear Register */
#تعریف_کرو AT91C_UDP_IMR           ( ( AT91_REG * ) 0xFFFB0018 ) /* (UDP) Interrupt Mask Register */
#تعریف_کرو AT91C_UDP_IER           ( ( AT91_REG * ) 0xFFFB0010 ) /* (UDP) Interrupt Enable Register */
#تعریف_کرو AT91C_UDP_FADDR         ( ( AT91_REG * ) 0xFFFB0008 ) /* (UDP) Function Address Register */
#تعریف_کرو AT91_C_UDP_عدد           ( ( AT91_REG * ) 0xFFFB0000 ) /* (UDP) Frame Number Register */

/* ***************************************************************************** */
/*               PIO DEFINITIONS FOR AT91SAM7S64 */
/* ***************************************************************************** */
#تعریف_کرو AT91C_PIO_PA0       ( ( بنانشانی صحيح ) 1 << 0 )         /* Pin Controlled by PA0 */
#تعریف_کرو AT91C_PA0_PWM0      ( ( بنانشانی صحيح ) AT91C_PIO_PA0 )  /*  PWM Channel 0 */
#تعریف_کرو AT91C_PA0_TIOA0     ( ( بنانشانی صحيح ) AT91C_PIO_PA0 )  /*  Timer Counter 0 Multipurpose Timer I/O Pin A */
#تعریف_کرو AT91C_PIO_PA1       ( ( بنانشانی صحيح ) 1 << 1 )         /* Pin Controlled by PA1 */
#تعریف_کرو AT91C_PA1_PWM1      ( ( بنانشانی صحيح ) AT91C_PIO_PA1 )  /*  PWM Channel 1 */
#تعریف_کرو AT91C_PA1_TIOB0     ( ( بنانشانی صحيح ) AT91C_PIO_PA1 )  /*  Timer Counter 0 Multipurpose Timer I/O Pin B */
#تعریف_کرو AT91C_PIO_PA10      ( ( بنانشانی صحيح ) 1 << 10 )        /* Pin Controlled by PA10 */
#تعریف_کرو AT91C_PA10_DTXD     ( ( بنانشانی صحيح ) AT91C_PIO_PA10 ) /*  DBGU Debug Transmit Data */
#تعریف_کرو AT91C_PA10_NPCS2    ( ( بنانشانی صحيح ) AT91C_PIO_PA10 ) /*  SPI Peripheral Chip Select 2 */
#تعریف_کرو AT91C_PIO_PA11      ( ( بنانشانی صحيح ) 1 << 11 )        /* Pin Controlled by PA11 */
#تعریف_کرو AT91C_PA11_NPCS0    ( ( بنانشانی صحيح ) AT91C_PIO_PA11 ) /*  SPI Peripheral Chip Select 0 */
#تعریف_کرو AT91C_PA11_PWM0     ( ( بنانشانی صحيح ) AT91C_PIO_PA11 ) /*  PWM Channel 0 */
#تعریف_کرو AT91C_PIO_PA12      ( ( بنانشانی صحيح ) 1 << 12 )        /* Pin Controlled by PA12 */
#تعریف_کرو AT91C_PA12_MISO     ( ( بنانشانی صحيح ) AT91C_PIO_PA12 ) /*  SPI Master In Slave */
#تعریف_کرو AT91C_PA12_PWM1     ( ( بنانشانی صحيح ) AT91C_PIO_PA12 ) /*  PWM Channel 1 */
#تعریف_کرو AT91C_PIO_PA13      ( ( بنانشانی صحيح ) 1 << 13 )        /* Pin Controlled by PA13 */
#تعریف_کرو AT91C_PA13_MOSI     ( ( بنانشانی صحيح ) AT91C_PIO_PA13 ) /*  SPI Master Out Slave */
#تعریف_کرو AT91C_PA13_PWM2     ( ( بنانشانی صحيح ) AT91C_PIO_PA13 ) /*  PWM Channel 2 */
#تعریف_کرو AT91C_PIO_PA14      ( ( بنانشانی صحيح ) 1 << 14 )        /* Pin Controlled by PA14 */
#تعریف_کرو AT91C_PA14_SPCK     ( ( بنانشانی صحيح ) AT91C_PIO_PA14 ) /*  SPI Serial Clock */
#تعریف_کرو AT91C_PA14_PWM3     ( ( بنانشانی صحيح ) AT91C_PIO_PA14 ) /*  PWM Channel 3 */
#تعریف_کرو AT91C_PIO_PA15      ( ( بنانشانی صحيح ) 1 << 15 )        /* Pin Controlled by PA15 */
#تعریف_کرو AT91C_PA15_TF       ( ( بنانشانی صحيح ) AT91C_PIO_PA15 ) /*  SSC Transmit Frame Sync */
#تعریف_کرو AT91C_PA15_TIOA1    ( ( بنانشانی صحيح ) AT91C_PIO_PA15 ) /*  Timer Counter 1 Multipurpose Timer I/O Pin A */
#تعریف_کرو AT91C_PIO_PA16      ( ( بنانشانی صحيح ) 1 << 16 )        /* Pin Controlled by PA16 */
#تعریف_کرو AT91C_PA16_TK       ( ( بنانشانی صحيح ) AT91C_PIO_PA16 ) /*  SSC Transmit Clock */
#تعریف_کرو AT91C_PA16_TIOB1    ( ( بنانشانی صحيح ) AT91C_PIO_PA16 ) /*  Timer Counter 1 Multipurpose Timer I/O Pin B */
#تعریف_کرو AT91C_PIO_PA17      ( ( بنانشانی صحيح ) 1 << 17 )        /* Pin Controlled by PA17 */
#تعریف_کرو AT91C_PA17_TD       ( ( بنانشانی صحيح ) AT91C_PIO_PA17 ) /*  SSC Transmit data */
#تعریف_کرو AT91C_PA17_PCK1     ( ( بنانشانی صحيح ) AT91C_PIO_PA17 ) /*  PMC Programmable Clock Output 1 */
#تعریف_کرو AT91C_PIO_PA18      ( ( بنانشانی صحيح ) 1 << 18 )        /* Pin Controlled by PA18 */
#تعریف_کرو AT91C_PA18_RD       ( ( بنانشانی صحيح ) AT91C_PIO_PA18 ) /*  SSC Receive Data */
#تعریف_کرو AT91C_PA18_PCK2     ( ( بنانشانی صحيح ) AT91C_PIO_PA18 ) /*  PMC Programmable Clock Output 2 */
#تعریف_کرو AT91C_PIO_PA19      ( ( بنانشانی صحيح ) 1 << 19 )        /* Pin Controlled by PA19 */
#تعریف_کرو AT91C_PA19_RK       ( ( بنانشانی صحيح ) AT91C_PIO_PA19 ) /*  SSC Receive Clock */
#تعریف_کرو AT91C_PA19_FIQ      ( ( بنانشانی صحيح ) AT91C_PIO_PA19 ) /*  AIC Fast Interrupt Input */
#تعریف_کرو AT91C_PIO_PA2       ( ( بنانشانی صحيح ) 1 << 2 )         /* Pin Controlled by PA2 */
#تعریف_کرو AT91C_PA2_PWM2      ( ( بنانشانی صحيح ) AT91C_PIO_PA2 )  /*  PWM Channel 2 */
#تعریف_کرو AT91C_PA2_SCK0      ( ( بنانشانی صحيح ) AT91C_PIO_PA2 )  /*  USART 0 Serial Clock */
#تعریف_کرو AT91C_PIO_PA20      ( ( بنانشانی صحيح ) 1 << 20 )        /* Pin Controlled by PA20 */
#تعریف_کرو AT91C_PA20_RF       ( ( بنانشانی صحيح ) AT91C_PIO_PA20 ) /*  SSC Receive Frame Sync */
#تعریف_کرو AT91C_PA20_IRQ0     ( ( بنانشانی صحيح ) AT91C_PIO_PA20 ) /*  External Interrupt 0 */
#تعریف_کرو AT91C_PIO_PA21      ( ( بنانشانی صحيح ) 1 << 21 )        /* Pin Controlled by PA21 */
#تعریف_کرو AT91C_PA21_RXD1     ( ( بنانشانی صحيح ) AT91C_PIO_PA21 ) /*  USART 1 Receive Data */
#تعریف_کرو AT91C_PA21_PCK1     ( ( بنانشانی صحيح ) AT91C_PIO_PA21 ) /*  PMC Programmable Clock Output 1 */
#تعریف_کرو AT91C_PIO_PA22      ( ( بنانشانی صحيح ) 1 << 22 )        /* Pin Controlled by PA22 */
#تعریف_کرو AT91C_PA22_TXD1     ( ( بنانشانی صحيح ) AT91C_PIO_PA22 ) /*  USART 1 Transmit Data */
#تعریف_کرو AT91C_PA22_NPCS3    ( ( بنانشانی صحيح ) AT91C_PIO_PA22 ) /*  SPI Peripheral Chip Select 3 */
#تعریف_کرو AT91C_PIO_PA23      ( ( بنانشانی صحيح ) 1 << 23 )        /* Pin Controlled by PA23 */
#تعریف_کرو AT91C_PA23_SCK1     ( ( بنانشانی صحيح ) AT91C_PIO_PA23 ) /*  USART 1 Serial Clock */
#تعریف_کرو AT91C_PA23_PWM0     ( ( بنانشانی صحيح ) AT91C_PIO_PA23 ) /*  PWM Channel 0 */
#تعریف_کرو AT91C_PIO_PA24      ( ( بنانشانی صحيح ) 1 << 24 )        /* Pin Controlled by PA24 */
#تعریف_کرو AT91C_PA24_RTS1     ( ( بنانشانی صحيح ) AT91C_PIO_PA24 ) /*  USART 1 Ready To Send */
#تعریف_کرو AT91C_PA24_PWM1     ( ( بنانشانی صحيح ) AT91C_PIO_PA24 ) /*  PWM Channel 1 */
#تعریف_کرو AT91C_PIO_PA25      ( ( بنانشانی صحيح ) 1 << 25 )        /* Pin Controlled by PA25 */
#تعریف_کرو AT91C_PA25_CTS1     ( ( بنانشانی صحيح ) AT91C_PIO_PA25 ) /*  USART 1 Clear To Send */
#تعریف_کرو AT91C_PA25_PWM2     ( ( بنانشانی صحيح ) AT91C_PIO_PA25 ) /*  PWM Channel 2 */
#تعریف_کرو AT91C_PIO_PA26      ( ( بنانشانی صحيح ) 1 << 26 )        /* Pin Controlled by PA26 */
#تعریف_کرو AT91C_PA26_DCD1     ( ( بنانشانی صحيح ) AT91C_PIO_PA26 ) /*  USART 1 Data Carrier Detect */
#تعریف_کرو AT91C_PA26_TIOA2    ( ( بنانشانی صحيح ) AT91C_PIO_PA26 ) /*  Timer Counter 2 Multipurpose Timer I/O Pin A */
#تعریف_کرو AT91C_PIO_PA27      ( ( بنانشانی صحيح ) 1 << 27 )        /* Pin Controlled by PA27 */
#تعریف_کرو AT91C_PA27_DTR1     ( ( بنانشانی صحيح ) AT91C_PIO_PA27 ) /*  USART 1 Data Terminal ready */
#تعریف_کرو AT91C_PA27_TIOB2    ( ( بنانشانی صحيح ) AT91C_PIO_PA27 ) /*  Timer Counter 2 Multipurpose Timer I/O Pin B */
#تعریف_کرو AT91C_PIO_PA28      ( ( بنانشانی صحيح ) 1 << 28 )        /* Pin Controlled by PA28 */
#تعریف_کرو AT91C_PA28_DSR1     ( ( بنانشانی صحيح ) AT91C_PIO_PA28 ) /*  USART 1 Data Set ready */
#تعریف_کرو AT91C_PA28_TCLK1    ( ( بنانشانی صحيح ) AT91C_PIO_PA28 ) /*  Timer Counter 1 external clock input */
#تعریف_کرو AT91C_PIO_PA29      ( ( بنانشانی صحيح ) 1 << 29 )        /* Pin Controlled by PA29 */
#تعریف_کرو AT91C_PA29_RI1      ( ( بنانشانی صحيح ) AT91C_PIO_PA29 ) /*  USART 1 Ring Indicator */
#تعریف_کرو AT91C_PA29_TCLK2    ( ( بنانشانی صحيح ) AT91C_PIO_PA29 ) /*  Timer Counter 2 external clock input */
#تعریف_کرو AT91C_PIO_PA3       ( ( بنانشانی صحيح ) 1 << 3 )         /* Pin Controlled by PA3 */
#تعریف_کرو AT91C_PA3_TWD       ( ( بنانشانی صحيح ) AT91C_PIO_PA3 )  /*  TWI Two-wire Serial Data */
#تعریف_کرو AT91C_PA3_NPCS3     ( ( بنانشانی صحيح ) AT91C_PIO_PA3 )  /*  SPI Peripheral Chip Select 3 */
#تعریف_کرو AT91C_PIO_PA30      ( ( بنانشانی صحيح ) 1 << 30 )        /* Pin Controlled by PA30 */
#تعریف_کرو AT91C_PA30_IRQ1     ( ( بنانشانی صحيح ) AT91C_PIO_PA30 ) /*  External Interrupt 1 */
#تعریف_کرو AT91C_PA30_NPCS2    ( ( بنانشانی صحيح ) AT91C_PIO_PA30 ) /*  SPI Peripheral Chip Select 2 */
#تعریف_کرو AT91C_PIO_PA31      ( ( بنانشانی صحيح ) 1 << 31 )        /* Pin Controlled by PA31 */
#تعریف_کرو AT91C_PA31_NPCS1    ( ( بنانشانی صحيح ) AT91C_PIO_PA31 ) /*  SPI Peripheral Chip Select 1 */
#تعریف_کرو AT91C_PA31_PCK2     ( ( بنانشانی صحيح ) AT91C_PIO_PA31 ) /*  PMC Programmable Clock Output 2 */
#تعریف_کرو AT91C_PIO_PA4       ( ( بنانشانی صحيح ) 1 << 4 )         /* Pin Controlled by PA4 */
#تعریف_کرو AT91C_PA4_TWCK      ( ( بنانشانی صحيح ) AT91C_PIO_PA4 )  /*  TWI Two-wire Serial Clock */
#تعریف_کرو AT91C_PA4_TCLK0     ( ( بنانشانی صحيح ) AT91C_PIO_PA4 )  /*  Timer Counter 0 external clock input */
#تعریف_کرو AT91C_PIO_PA5       ( ( بنانشانی صحيح ) 1 << 5 )         /* Pin Controlled by PA5 */
#تعریف_کرو AT91C_PA5_RXD0      ( ( بنانشانی صحيح ) AT91C_PIO_PA5 )  /*  USART 0 Receive Data */
#تعریف_کرو AT91C_PA5_NPCS3     ( ( بنانشانی صحيح ) AT91C_PIO_PA5 )  /*  SPI Peripheral Chip Select 3 */
#تعریف_کرو AT91C_PIO_PA6       ( ( بنانشانی صحيح ) 1 << 6 )         /* Pin Controlled by PA6 */
#تعریف_کرو AT91C_PA6_TXD0      ( ( بنانشانی صحيح ) AT91C_PIO_PA6 )  /*  USART 0 Transmit Data */
#تعریف_کرو AT91C_PA6_PCK0      ( ( بنانشانی صحيح ) AT91C_PIO_PA6 )  /*  PMC Programmable Clock Output 0 */
#تعریف_کرو AT91C_PIO_PA7       ( ( بنانشانی صحيح ) 1 << 7 )         /* Pin Controlled by PA7 */
#تعریف_کرو AT91C_PA7_RTS0      ( ( بنانشانی صحيح ) AT91C_PIO_PA7 )  /*  USART 0 Ready To Send */
#تعریف_کرو AT91C_PA7_PWM3      ( ( بنانشانی صحيح ) AT91C_PIO_PA7 )  /*  PWM Channel 3 */
#تعریف_کرو AT91C_PIO_PA8       ( ( بنانشانی صحيح ) 1 << 8 )         /* Pin Controlled by PA8 */
#تعریف_کرو AT91C_PA8_CTS0      ( ( بنانشانی صحيح ) AT91C_PIO_PA8 )  /*  USART 0 Clear To Send */
#تعریف_کرو AT91C_PA8_ADTRG     ( ( بنانشانی صحيح ) AT91C_PIO_PA8 )  /*  ADC External Trigger */
#تعریف_کرو AT91C_PIO_PA9       ( ( بنانشانی صحيح ) 1 << 9 )         /* Pin Controlled by PA9 */
#تعریف_کرو AT91C_PA9_DRXD      ( ( بنانشانی صحيح ) AT91C_PIO_PA9 )  /*  DBGU Debug Receive Data */
#تعریف_کرو AT91C_PA9_NPCS1     ( ( بنانشانی صحيح ) AT91C_PIO_PA9 )  /*  SPI Peripheral Chip Select 1 */

/* ***************************************************************************** */
/*               PERIPHERAL ID DEFINITIONS FOR AT91SAM7S64 */
/* ***************************************************************************** */
#تعریف_کرو AT91C_ID_FIQ            ( ( بنانشانی صحيح ) 0 )  /* Advanced Interrupt Controller (FIQ) */
#تعریف_کرو AT91C_ID_SYS            ( ( بنانشانی صحيح ) 1 )  /* System Peripheral */
#تعریف_کرو AT91C_ID_PIOA           ( ( بنانشانی صحيح ) 2 )  /* Parallel IO Controller */
#تعریف_کرو AT91C_ID_3_Reserved     ( ( بنانشانی صحيح ) 3 )  /* Reserved */
#تعریف_کرو AT91C_ID_ADC            ( ( بنانشانی صحيح ) 4 )  /* Analog-to-Digital Converter */
#تعریف_کرو AT91C_ID_SPI            ( ( بنانشانی صحيح ) 5 )  /* Serial Peripheral Interface */
#تعریف_کرو AT91C_ID_US0            ( ( بنانشانی صحيح ) 6 )  /* USART 0 */
#تعریف_کرو AT91C_ID_US1            ( ( بنانشانی صحيح ) 7 )  /* USART 1 */
#تعریف_کرو AT91C_ID_SSC            ( ( بنانشانی صحيح ) 8 )  /* Serial Synchronous Controller */
#تعریف_کرو AT91C_ID_TWI            ( ( بنانشانی صحيح ) 9 )  /* Two-Wire Interface */
#تعریف_کرو AT91C_ID_PWMC           ( ( بنانشانی صحيح ) 10 ) /* PWM Controller */
#تعریف_کرو AT91C_ID_UDP            ( ( بنانشانی صحيح ) 11 ) /* USB Device Port */
#تعریف_کرو AT91C_ID_TC0            ( ( بنانشانی صحيح ) 12 ) /* Timer Counter 0 */
#تعریف_کرو AT91C_ID_TC1            ( ( بنانشانی صحيح ) 13 ) /* Timer Counter 1 */
#تعریف_کرو AT91C_ID_TC2            ( ( بنانشانی صحيح ) 14 ) /* Timer Counter 2 */
#تعریف_کرو AT91C_ID_15_Reserved    ( ( بنانشانی صحيح ) 15 ) /* Reserved */
#تعریف_کرو AT91C_ID_16_Reserved    ( ( بنانشانی صحيح ) 16 ) /* Reserved */
#تعریف_کرو AT91C_ID_17_Reserved    ( ( بنانشانی صحيح ) 17 ) /* Reserved */
#تعریف_کرو AT91C_ID_18_Reserved    ( ( بنانشانی صحيح ) 18 ) /* Reserved */
#تعریف_کرو AT91C_ID_19_Reserved    ( ( بنانشانی صحيح ) 19 ) /* Reserved */
#تعریف_کرو AT91C_ID_20_Reserved    ( ( بنانشانی صحيح ) 20 ) /* Reserved */
#تعریف_کرو AT91C_ID_21_Reserved    ( ( بنانشانی صحيح ) 21 ) /* Reserved */
#تعریف_کرو AT91C_ID_22_Reserved    ( ( بنانشانی صحيح ) 22 ) /* Reserved */
#تعریف_کرو AT91C_ID_23_Reserved    ( ( بنانشانی صحيح ) 23 ) /* Reserved */
#تعریف_کرو AT91C_ID_24_Reserved    ( ( بنانشانی صحيح ) 24 ) /* Reserved */
#تعریف_کرو AT91C_ID_25_Reserved    ( ( بنانشانی صحيح ) 25 ) /* Reserved */
#تعریف_کرو AT91C_ID_26_Reserved    ( ( بنانشانی صحيح ) 26 ) /* Reserved */
#تعریف_کرو AT91C_ID_27_Reserved    ( ( بنانشانی صحيح ) 27 ) /* Reserved */
#تعریف_کرو AT91C_ID_28_Reserved    ( ( بنانشانی صحيح ) 28 ) /* Reserved */
#تعریف_کرو AT91C_ID_29_Reserved    ( ( بنانشانی صحيح ) 29 ) /* Reserved */
#تعریف_کرو AT91C_ID_IRQ0           ( ( بنانشانی صحيح ) 30 ) /* Advanced Interrupt Controller (IRQ0) */
#تعریف_کرو AT91C_ID_IRQ1           ( ( بنانشانی صحيح ) 31 ) /* Advanced Interrupt Controller (IRQ1) */

/* ***************************************************************************** */
/*               BASE ADDRESS DEFINITIONS FOR AT91SAM7S64 */
/* ***************************************************************************** */
#تعریف_کرو AT91_C_ادھار_SYSC        ( ( AT91PS_SYSC ) 0xFFFFF000 )    /* (SYSC) Base Address */
#تعریف_کرو AT91_C_ادھار_AIC         ( ( AT91PS_AIC ) 0xFFFFF000 )     /* (AIC) Base Address */
#تعریف_کرو AT91_C_ادھار_DBGU        ( ( AT91PS_DBGU ) 0xFFFFF200 )    /* (DBGU) Base Address */
#تعریف_کرو AT91_C_ادھار_PDC_DBGU    ( ( AT91PS_PDC ) 0xFFFFF300 )     /* (PDC_DBGU) Base Address */
#تعریف_کرو AT91_C_ادھار_PIOA        ( ( AT91PS_PIO ) 0xFFFFF400 )     /* (PIOA) Base Address */
#تعریف_کرو AT91_C_ادھار_CKGR        ( ( AT91PS_CKGR ) 0xFFFFFC20 )    /* (CKGR) Base Address */
#تعریف_کرو AT91_C_ادھار_PMC         ( ( AT91PS_PMC ) 0xFFFFFC00 )     /* (PMC) Base Address */
#تعریف_کرو AT91_C_ادھار_RSTC        ( ( AT91PS_RSTC ) 0xFFFFFD00 )    /* (RSTC) Base Address */
#تعریف_کرو AT91_C_ادھار_RTTC        ( ( AT91PS_RTTC ) 0xFFFFFD20 )    /* (RTTC) Base Address */
#تعریف_کرو AT91_C_ادھار_PITC        ( ( AT91PS_PITC ) 0xFFFFFD30 )    /* (PITC) Base Address */
#تعریف_کرو AT91_C_ادھار_WDTC        ( ( AT91PS_WDTC ) 0xFFFFFD40 )    /* (WDTC) Base Address */
#تعریف_کرو AT91_C_ادھار_MC          ( ( AT91PS_MC ) 0xFFFFFF00 )      /* (MC) Base Address */
#تعریف_کرو AT91_C_ادھار_PDC_SPI     ( ( AT91PS_PDC ) 0xFFFE0100 )     /* (PDC_SPI) Base Address */
#تعریف_کرو AT91_C_ادھار_SPI         ( ( AT91PS_SPI ) 0xFFFE0000 )     /* (SPI) Base Address */
#تعریف_کرو AT91_C_ادھار_PDC_ADC     ( ( AT91PS_PDC ) 0xFFFD8100 )     /* (PDC_ADC) Base Address */
#تعریف_کرو AT91_C_ادھار_ADC         ( ( AT91PS_ADC ) 0xFFFD8000 )     /* (ADC) Base Address */
#تعریف_کرو AT91_C_ادھار_PDC_SSC     ( ( AT91PS_PDC ) 0xFFFD4100 )     /* (PDC_SSC) Base Address */
#تعریف_کرو AT91_C_ادھار_SSC         ( ( AT91PS_SSC ) 0xFFFD4000 )     /* (SSC) Base Address */
#تعریف_کرو AT91_C_ادھار_PDC_US1     ( ( AT91PS_PDC ) 0xFFFC4100 )     /* (PDC_US1) Base Address */
#تعریف_کرو AT91_C_ادھار_US1         ( ( AT91PS_USART ) 0xFFFC4000 )   /* (US1) Base Address */
#تعریف_کرو AT91_C_ادھار_PDC_US0     ( ( AT91PS_PDC ) 0xFFFC0100 )     /* (PDC_US0) Base Address */
#تعریف_کرو AT91_C_ادھار_US0         ( ( AT91PS_USART ) 0xFFFC0000 )   /* (US0) Base Address */
#تعریف_کرو AT91_C_ادھار_TWI         ( ( AT91PS_TWI ) 0xFFFB8000 )     /* (TWI) Base Address */
#تعریف_کرو AT91_C_ادھار_TC2         ( ( AT91PS_TC ) 0xFFFA0080 )      /* (TC2) Base Address */
#تعریف_کرو AT91_C_ادھار_TC1         ( ( AT91PS_TC ) 0xFFFA0040 )      /* (TC1) Base Address */
#تعریف_کرو AT91_C_ادھار_TC0         ( ( AT91PS_TC ) 0xFFFA0000 )      /* (TC0) Base Address */
#تعریف_کرو AT91_C_ادھار_TCB         ( ( AT91PS_TCB ) 0xFFFA0000 )     /* (TCB) Base Address */
#تعریف_کرو AT91_C_ادھار_PWMC_CH3    ( ( AT91PS_PWMC_CH ) 0xFFFCC260 ) /* (PWMC_CH3) Base Address */
#تعریف_کرو AT91_C_ادھار_PWMC_CH2    ( ( AT91PS_PWMC_CH ) 0xFFFCC240 ) /* (PWMC_CH2) Base Address */
#تعریف_کرو AT91_C_ادھار_PWMC_CH1    ( ( AT91PS_PWMC_CH ) 0xFFFCC220 ) /* (PWMC_CH1) Base Address */
#تعریف_کرو AT91_C_ادھار_PWMC_CH0    ( ( AT91PS_PWMC_CH ) 0xFFFCC200 ) /* (PWMC_CH0) Base Address */
#تعریف_کرو AT91_C_ادھار_PWMC        ( ( AT91PS_PWMC ) 0xFFFCC000 )    /* (PWMC) Base Address */
#تعریف_کرو AT91_C_ادھار_UDP         ( ( AT91PS_UDP ) 0xFFFB0000 )     /* (UDP) Base Address */

/* ***************************************************************************** */
/*               MEMORY MAPPING DEFINITIONS FOR AT91SAM7S64 */
/* ***************************************************************************** */
#تعریف_کرو AT91C_ISRAM          ( ( حرف * ) 0x00200000 )       /* Internal SRAM base address */
#تعریف_کرو AT91_C_ISRAM_ناپ     ( ( بنانشانی صحيح ) 0x00004000 ) /* Internal SRAM size in byte (16 Kbyte) */
#تعریف_کرو AT91C_IFLASH         ( ( حرف * ) 0x00100000 )       /* Internal ROM base address */
#تعریف_کرو AT91_C_IFLASH_ناپ    ( ( بنانشانی صحيح ) 0x00010000 ) /* Internal ROM size in byte (64 Kbyte) */

#جے_انت /* ifndef AT91SAM7S64_H */
