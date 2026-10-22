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
/* Generated           : AT91 SW Application Group  07/16/2004 (07:43:09) */
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

/* Hardware register definition */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR System Peripherals */
/* ***************************************************************************** */
/* *** Register offset in AT91S_SYSC structure *** */
#تعریف_کرو SYSC_AIC_SMR         ( 0 )        /* Source Mode Register */
#تعریف_کرو SYSC_AIC_SVR         ( 128 )      /* Source Vector Register */
#تعریف_کرو SYSC_AIC_IVR         ( 256 )      /* IRQ Vector Register */
#تعریف_کرو SYSC_AIC_FVR         ( 260 )      /* FIQ Vector Register */
#تعریف_کرو SYSC_AIC_ISR         ( 264 )      /* Interrupt Status Register */
#تعریف_کرو SYSC_AIC_IPR         ( 268 )      /* Interrupt Pending Register */
#تعریف_کرو SYSC_AIC_IMR         ( 272 )      /* Interrupt Mask Register */
#تعریف_کرو SYSC_AIC_CISR        ( 276 )      /* Core Interrupt Status Register */
#تعریف_کرو SYSC_AIC_IECR        ( 288 )      /* Interrupt Enable Command Register */
#تعریف_کرو SYSC_AIC_IDCR        ( 292 )      /* Interrupt Disable Command Register */
#تعریف_کرو SYSC_AIC_ICCR        ( 296 )      /* Interrupt Clear Command Register */
#تعریف_کرو SYSC_AIC_ISCR        ( 300 )      /* Interrupt Set Command Register */
#تعریف_کرو SYSC_AIC_EOICR       ( 304 )      /* End of Interrupt Command Register */
#تعریف_کرو SYSC_AIC_SPU         ( 308 )      /* Spurious Vector Register */
#تعریف_کرو SYSC_AIC_DCR         ( 312 )      /* Debug Control Register (Protect) */
#تعریف_کرو SYSC_AIC_FFER        ( 320 )      /* Fast Forcing Enable Register */
#تعریف_کرو SYSC_AIC_FFDR        ( 324 )      /* Fast Forcing Disable Register */
#تعریف_کرو SYSC_AIC_FFSR        ( 328 )      /* Fast Forcing Status Register */
#تعریف_کرو SYSC_DBGU_CR         ( 512 )      /* Control Register */
#تعریف_کرو SYSC_DBGU_MR         ( 516 )      /* Mode Register */
#تعریف_کرو SYSC_DBGU_IER        ( 520 )      /* Interrupt Enable Register */
#تعریف_کرو SYSC_DBGU_IDR        ( 524 )      /* Interrupt Disable Register */
#تعریف_کرو SYSC_DBGU_IMR        ( 528 )      /* Interrupt Mask Register */
#تعریف_کرو SYSC_DBGU_CSR        ( 532 )      /* Channel Status Register */
#تعریف_کرو SYSC_DBGU_RHR        ( 536 )      /* Receiver Holding Register */
#تعریف_کرو SYSC_DBGU_THR        ( 540 )      /* Transmitter Holding Register */
#تعریف_کرو SYSC_DBGU_BRGR       ( 544 )      /* Baud Rate Generator Register */
#تعریف_کرو SYSC_DBGU_C1R        ( 576 )      /* Chip ID1 Register */
#تعریف_کرو SYSC_DBGU_C2R        ( 580 )      /* Chip ID2 Register */
#تعریف_کرو SYSC_DBGU_FNTR       ( 584 )      /* Force NTRST Register */
#تعریف_کرو SYSC_DBGU_RPR        ( 768 )      /* Receive Pointer Register */
#تعریف_کرو SYSC_DBGU_RCR        ( 772 )      /* Receive Counter Register */
#تعریف_کرو SYSC_DBGU_TPR        ( 776 )      /* Transmit Pointer Register */
#تعریف_کرو SYSC_DBGU_TCR        ( 780 )      /* Transmit Counter Register */
#تعریف_کرو SYSC_DBGU_RNPR       ( 784 )      /* Receive Next Pointer Register */
#تعریف_کرو SYSC_DBGU_RNCR       ( 788 )      /* Receive Next Counter Register */
#تعریف_کرو SYSC_DBGU_TNPR       ( 792 )      /* Transmit Next Pointer Register */
#تعریف_کرو SYSC_DBGU_TNCR       ( 796 )      /* Transmit Next Counter Register */
#تعریف_کرو SYSC_DBGU_PTCR       ( 800 )      /* PDC Transfer Control Register */
#تعریف_کرو SYSC_DBGU_PTSR       ( 804 )      /* PDC Transfer Status Register */
#تعریف_کرو SYSC_PIOA_فی        ( 1024 )     /* PIO Enable Register */
#تعریف_کرو SYSC_PIOA_PDR        ( 1028 )     /* PIO Disable Register */
#تعریف_کرو SYSC_PIOA_PSR        ( 1032 )     /* PIO Status Register */
#تعریف_کرو SYSC_PIOA_OER        ( 1040 )     /* Output Enable Register */
#تعریف_کرو SYSC_PIOA_ODR        ( 1044 )     /* Output Disable Registerr */
#تعریف_کرو SYSC_PIOA_OSR        ( 1048 )     /* Output Status Register */
#تعریف_کرو SYSC_PIOA_IFER       ( 1056 )     /* Input Filter Enable Register */
#تعریف_کرو SYSC_PIOA_IFDR       ( 1060 )     /* Input Filter Disable Register */
#تعریف_کرو SYSC_PIOA_IFSR       ( 1064 )     /* Input Filter Status Register */
#تعریف_کرو SYSC_PIOA_SODR       ( 1072 )     /* Set Output Data Register */
#تعریف_کرو SYSC_PIOA_CODR       ( 1076 )     /* Clear Output Data Register */
#تعریف_کرو SYSC_PIOA_ODSR       ( 1080 )     /* Output Data Status Register */
#تعریف_کرو SYSC_PIOA_PDSR       ( 1084 )     /* Pin Data Status Register */
#تعریف_کرو SYSC_PIOA_IER        ( 1088 )     /* Interrupt Enable Register */
#تعریف_کرو SYSC_PIOA_IDR        ( 1092 )     /* Interrupt Disable Register */
#تعریف_کرو SYSC_PIOA_IMR        ( 1096 )     /* Interrupt Mask Register */
#تعریف_کرو SYSC_PIOA_ISR        ( 1100 )     /* Interrupt Status Register */
#تعریف_کرو SYSC_PIOA_MDER       ( 1104 )     /* Multi-driver Enable Register */
#تعریف_کرو SYSC_PIOA_MDDR       ( 1108 )     /* Multi-driver Disable Register */
#تعریف_کرو SYSC_PIOA_MDSR       ( 1112 )     /* Multi-driver Status Register */
#تعریف_کرو SYSC_PIOA_PPUDR      ( 1120 )     /* Pull-up Disable Register */
#تعریف_کرو SYSC_PIOA_PPUER      ( 1124 )     /* Pull-up Enable Register */
#تعریف_کرو SYSC_PIOA_PPUSR      ( 1128 )     /* Pad Pull-up Status Register */
#تعریف_کرو SYSC_PIOA_ASR        ( 1136 )     /* Select A Register */
#تعریف_کرو SYSC_PIOA_BSR        ( 1140 )     /* Select B Register */
#تعریف_کرو SYSC_PIOA_ABSR       ( 1144 )     /* AB Select Status Register */
#تعریف_کرو SYSC_PIOA_OWER       ( 1184 )     /* Output Write Enable Register */
#تعریف_کرو SYSC_PIOA_OWDR       ( 1188 )     /* Output Write Disable Register */
#تعریف_کرو SYSC_PIOA_OWSR       ( 1192 )     /* Output Write Status Register */
#تعریف_کرو SYSC_PMC_SCER        ( 3072 )     /* System Clock Enable Register */
#تعریف_کرو SYSC_PMC_SCDR        ( 3076 )     /* System Clock Disable Register */
#تعریف_کرو SYSC_PMC_SCSR        ( 3080 )     /* System Clock Status Register */
#تعریف_کرو SYSC_PMC_PCER        ( 3088 )     /* Peripheral Clock Enable Register */
#تعریف_کرو SYSC_PMC_PCDR        ( 3092 )     /* Peripheral Clock Disable Register */
#تعریف_کرو SYSC_PMC_PCSR        ( 3096 )     /* Peripheral Clock Status Register */
#تعریف_کرو SYSC_PMC_MOR         ( 3104 )     /* Main Oscillator Register */
#تعریف_کرو SYSC_PMC_MCFR        ( 3108 )     /* Main Clock  Frequency Register */
#تعریف_کرو SYSC_PMC_PLLR        ( 3116 )     /* PLL Register */
#تعریف_کرو SYSC_PMC_MCKR        ( 3120 )     /* Master Clock Register */
#تعریف_کرو SYSC_PMC_PCKR        ( 3136 )     /* Programmable Clock Register */
#تعریف_کرو SYSC_PMC_IER         ( 3168 )     /* Interrupt Enable Register */
#تعریف_کرو SYSC_PMC_IDR         ( 3172 )     /* Interrupt Disable Register */
#تعریف_کرو SYSC_PMC_SR          ( 3176 )     /* Status Register */
#تعریف_کرو SYSC_PMC_IMR         ( 3180 )     /* Interrupt Mask Register */
#تعریف_کرو SYSC_RSTC_RCR        ( 3328 )     /* Reset Control Register */
#تعریف_کرو SYSC_RSTC_RSR        ( 3332 )     /* Reset Status Register */
#تعریف_کرو SYSC_RSTC_RMR        ( 3336 )     /* Reset Mode Register */
#تعریف_کرو SYSC_RTTC_RTMR       ( 3360 )     /* Real-time Mode Register */
#تعریف_کرو SYSC_RTTC_RTAR       ( 3364 )     /* Real-time Alarm Register */
#تعریف_کرو SYSC_RTTC_RTVR       ( 3368 )     /* Real-time Value Register */
#تعریف_کرو SYSC_RTTC_RTSR       ( 3372 )     /* Real-time Status Register */
#تعریف_کرو SYSC_PITC_PIMR       ( 3376 )     /* Period Interval Mode Register */
#تعریف_کرو SYSC_PITC_PISR       ( 3380 )     /* Period Interval Status Register */
#تعریف_کرو SYSC_PITC_PIVR       ( 3384 )     /* Period Interval Value Register */
#تعریف_کرو SYSC_PITC_PIIR       ( 3388 )     /* Period Interval Image Register */
#تعریف_کرو SYSC_WDTC_WDCR       ( 3392 )     /* Watchdog Control Register */
#تعریف_کرو SYSC_WDTC_WDMR       ( 3396 )     /* Watchdog Mode Register */
#تعریف_کرو SYSC_WDTC_WDSR       ( 3400 )     /* Watchdog Status Register */
#تعریف_کرو SYSC_SYSC_VRPM       ( 3424 )     /* Voltage Regulator Power Mode Register */
/* -------- VRPM : (SYSC Offset: 0xd60) Voltage Regulator Power Mode Register -------- */
#تعریف_کرو AT91C_SYSC_PSTDBY    ( 0x1 << 0 ) /* (SYSC) Voltage Regulator Power Mode */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Advanced Interrupt Controller */
/* ***************************************************************************** */
/* *** Register offset in AT91S_AIC structure *** */
#تعریف_کرو AIC_SMR                                      ( 0 )        /* Source Mode Register */
#تعریف_کرو AIC_SVR                                      ( 128 )      /* Source Vector Register */
#تعریف_کرو AIC_IVR                                      ( 256 )      /* IRQ Vector Register */
#تعریف_کرو AIC_FVR                                      ( 260 )      /* FIQ Vector Register */
#تعریف_کرو AIC_ISR                                      ( 264 )      /* Interrupt Status Register */
#تعریف_کرو AIC_IPR                                      ( 268 )      /* Interrupt Pending Register */
#تعریف_کرو AIC_IMR                                      ( 272 )      /* Interrupt Mask Register */
#تعریف_کرو AIC_CISR                                     ( 276 )      /* Core Interrupt Status Register */
#تعریف_کرو AIC_IECR                                     ( 288 )      /* Interrupt Enable Command Register */
#تعریف_کرو AIC_IDCR                                     ( 292 )      /* Interrupt Disable Command Register */
#تعریف_کرو AIC_ICCR                                     ( 296 )      /* Interrupt Clear Command Register */
#تعریف_کرو AIC_ISCR                                     ( 300 )      /* Interrupt Set Command Register */
#تعریف_کرو AIC_EOICR                                    ( 304 )      /* End of Interrupt Command Register */
#تعریف_کرو AIC_SPU                                      ( 308 )      /* Spurious Vector Register */
#تعریف_کرو AIC_DCR                                      ( 312 )      /* Debug Control Register (Protect) */
#تعریف_کرو AIC_FFER                                     ( 320 )      /* Fast Forcing Enable Register */
#تعریف_کرو AIC_FFDR                                     ( 324 )      /* Fast Forcing Disable Register */
#تعریف_کرو AIC_FFSR                                     ( 328 )      /* Fast Forcing Status Register */
/* -------- AIC_SMR : (AIC Offset: 0x0) Control Register -------- */
#تعریف_کرو AT91_C_AIC_پیشگی                              ( 0x7 << 0 ) /* (AIC) Priority Level */
#تعریف_کرو     AT91_C_AIC_پیشگی_سب_سے_نیچا                   ( 0x0 )      /* (AIC) Lowest priority level */
#تعریف_کرو     AT91_C_AIC_پیشگی_HIGHEST                  ( 0x7 )      /* (AIC) Highest priority level */
#تعریف_کرو AT91C_AIC_SRCTYPE                            ( 0x3 << 5 ) /* (AIC) Interrupt Source Type */
#تعریف_کرو     AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE    ( 0x0 << 5 ) /* (AIC) Internal Sources Code Label Level Sensitive */
#تعریف_کرو     AT91_C_AIC_SRCTYPE_INT_کنارہ_TRIGGERED     ( 0x1 << 5 ) /* (AIC) Internal Sources Code Label Edge triggered */
#تعریف_کرو     AT91_C_AIC_SRCTYPE_EXT_بلند_LEVEL         ( 0x2 << 5 ) /* (AIC) External Sources Code Label High-level Sensitive */
#تعریف_کرو     AT91_C_AIC_SRCTYPE_EXT_مثبت_کنارہ      ( 0x3 << 5 ) /* (AIC) External Sources Code Label Positive Edge triggered */
/* -------- AIC_CISR : (AIC Offset: 0x114) AIC Core Interrupt Status Register -------- */
#تعریف_کرو AT91C_AIC_NFIQ                               ( 0x1 << 0 ) /* (AIC) NFIQ Status */
#تعریف_کرو AT91C_AIC_NIRQ                               ( 0x1 << 1 ) /* (AIC) NIRQ Status */
/* -------- AIC_DCR : (AIC Offset: 0x138) AIC Debug Control Register (Protect) -------- */
#تعریف_کرو AT91C_AIC_DCR_PROT                           ( 0x1 << 0 ) /* (AIC) Protection Mode */
#تعریف_کرو AT91C_AIC_DCR_GMSK                           ( 0x1 << 1 ) /* (AIC) General Mask */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Debug Unit */
/* ***************************************************************************** */
/* *** Register offset in AT91S_DBGU structure *** */
#تعریف_کرو DBGU_CR                        ( 0 )         /* Control Register */
#تعریف_کرو DBGU_MR                        ( 4 )         /* Mode Register */
#تعریف_کرو DBGU_IER                       ( 8 )         /* Interrupt Enable Register */
#تعریف_کرو DBGU_IDR                       ( 12 )        /* Interrupt Disable Register */
#تعریف_کرو DBGU_IMR                       ( 16 )        /* Interrupt Mask Register */
#تعریف_کرو DBGU_CSR                       ( 20 )        /* Channel Status Register */
#تعریف_کرو DBGU_RHR                       ( 24 )        /* Receiver Holding Register */
#تعریف_کرو DBGU_THR                       ( 28 )        /* Transmitter Holding Register */
#تعریف_کرو DBGU_BRGR                      ( 32 )        /* Baud Rate Generator Register */
#تعریف_کرو DBGU_C1R                       ( 64 )        /* Chip ID1 Register */
#تعریف_کرو DBGU_C2R                       ( 68 )        /* Chip ID2 Register */
#تعریف_کرو DBGU_FNTR                      ( 72 )        /* Force NTRST Register */
#تعریف_کرو DBGU_RPR                       ( 256 )       /* Receive Pointer Register */
#تعریف_کرو DBGU_RCR                       ( 260 )       /* Receive Counter Register */
#تعریف_کرو DBGU_TPR                       ( 264 )       /* Transmit Pointer Register */
#تعریف_کرو DBGU_TCR                       ( 268 )       /* Transmit Counter Register */
#تعریف_کرو DBGU_RNPR                      ( 272 )       /* Receive Next Pointer Register */
#تعریف_کرو DBGU_RNCR                      ( 276 )       /* Receive Next Counter Register */
#تعریف_کرو DBGU_TNPR                      ( 280 )       /* Transmit Next Pointer Register */
#تعریف_کرو DBGU_TNCR                      ( 284 )       /* Transmit Next Counter Register */
#تعریف_کرو DBGU_PTCR                      ( 288 )       /* PDC Transfer Control Register */
#تعریف_کرو DBGU_PTSR                      ( 292 )       /* PDC Transfer Status Register */
/* -------- DBGU_CR : (DBGU Offset: 0x0) Debug Unit Control Register -------- */
#تعریف_کرو AT91C_US_RSTRX                 ( 0x1 << 2 )  /* (DBGU) Reset Receiver */
#تعریف_کرو AT91C_US_RSTTX                 ( 0x1 << 3 )  /* (DBGU) Reset Transmitter */
#تعریف_کرو AT91C_US_RXEN                  ( 0x1 << 4 )  /* (DBGU) Receiver Enable */
#تعریف_کرو AT91C_US_RXDIS                 ( 0x1 << 5 )  /* (DBGU) Receiver Disable */
#تعریف_کرو AT91C_US_TXEN                  ( 0x1 << 6 )  /* (DBGU) Transmitter Enable */
#تعریف_کرو AT91C_US_TXDIS                 ( 0x1 << 7 )  /* (DBGU) Transmitter Disable */
/* -------- DBGU_MR : (DBGU Offset: 0x4) Debug Unit Mode Register -------- */
#تعریف_کرو AT91C_US_PAR                   ( 0x7 << 9 )  /* (DBGU) Parity type */
#تعریف_کرو     AT91C_US_PAR_EVEN          ( 0x0 << 9 )  /* (DBGU) Even Parity */
#تعریف_کرو     AT91C_US_PAR_ODD           ( 0x1 << 9 )  /* (DBGU) Odd Parity */
#تعریف_کرو     AT91C_US_PAR_SPACE         ( 0x2 << 9 )  /* (DBGU) Parity forced to 0 (Space) */
#تعریف_کرو     AT91C_US_PAR_MARK          ( 0x3 << 9 )  /* (DBGU) Parity forced to 1 (Mark) */
#تعریف_کرو     AT91C_US_PAR_NONE          ( 0x4 << 9 )  /* (DBGU) No Parity */
#تعریف_کرو     AT91C_US_PAR_MULTI_DROP    ( 0x6 << 9 )  /* (DBGU) Multi-drop mode */
#تعریف_کرو AT91C_US_CHMODE                ( 0x3 << 14 ) /* (DBGU) Channel Mode */
#تعریف_کرو     AT91_C_US_CHMODE_معمول     ( 0x0 << 14 ) /* (DBGU) Normal Mode: The USART channel operates as an RX/TX USART. */
#تعریف_کرو     AT91C_US_CHMODE_AUTO       ( 0x1 << 14 ) /* (DBGU) Automatic Echo: Receiver Data Input is connected to the TXD pin. */
#تعریف_کرو     AT91C_US_CHMODE_LOCAL      ( 0x2 << 14 ) /* (DBGU) Local Loopback: Transmitter Output Signal is connected to Receiver Input Signal. */
#تعریف_کرو     AT91C_US_CHMODE_REMOTE     ( 0x3 << 14 ) /* (DBGU) Remote Loopback: RXD pin is internally connected to TXD pin. */
/* -------- DBGU_IER : (DBGU Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
#تعریف_کرو AT91C_US_RXRDY                 ( 0x1 << 0 )  /* (DBGU) RXRDY Interrupt */
#تعریف_کرو AT91C_US_TXRDY                 ( 0x1 << 1 )  /* (DBGU) TXRDY Interrupt */
#تعریف_کرو AT91C_US_ENDRX                 ( 0x1 << 3 )  /* (DBGU) End of Receive Transfer Interrupt */
#تعریف_کرو AT91C_US_ENDTX                 ( 0x1 << 4 )  /* (DBGU) End of Transmit Interrupt */
#تعریف_کرو AT91C_US_OVRE                  ( 0x1 << 5 )  /* (DBGU) Overrun Interrupt */
#تعریف_کرو AT91_C_US_چوکھٹا                 ( 0x1 << 6 )  /* (DBGU) Framing Error Interrupt */
#تعریف_کرو AT91C_US_PARE                  ( 0x1 << 7 )  /* (DBGU) Parity Error Interrupt */
#تعریف_کرو AT91C_US_TXEMPTY               ( 0x1 << 9 )  /* (DBGU) TXEMPTY Interrupt */
#تعریف_کرو AT91C_US_TXBUFE                ( 0x1 << 11 ) /* (DBGU) TXBUFE Interrupt */
#تعریف_کرو AT91C_US_RXBUFF                ( 0x1 << 12 ) /* (DBGU) RXBUFF Interrupt */
#تعریف_کرو AT91C_US_COMM_TX               ( 0x1 << 30 ) /* (DBGU) COMM_TX Interrupt */
#تعریف_کرو AT91C_US_COMM_RX               ( 0x1 << 31 ) /* (DBGU) COMM_RX Interrupt */
/* -------- DBGU_IDR : (DBGU Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* -------- DBGU_IMR : (DBGU Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* -------- DBGU_CSR : (DBGU Offset: 0x14) Debug Unit Channel Status Register -------- */
/* -------- DBGU_FNTR : (DBGU Offset: 0x48) Debug Unit FORCE_NTRST Register -------- */
#تعریف_کرو AT91C_US_FORCE_NTRST    ( 0x1 << 0 )  /* (DBGU) Force NTRST in JTAG */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Peripheral Data Controller */
/* ***************************************************************************** */
/* *** Register offset in AT91S_PDC structure *** */
#تعریف_کرو PDC_RPR             ( 0 )        /* Receive Pointer Register */
#تعریف_کرو PDC_RCR             ( 4 )        /* Receive Counter Register */
#تعریف_کرو PDC_TPR             ( 8 )        /* Transmit Pointer Register */
#تعریف_کرو PDC_TCR             ( 12 )       /* Transmit Counter Register */
#تعریف_کرو PDC_RNPR            ( 16 )       /* Receive Next Pointer Register */
#تعریف_کرو PDC_RNCR            ( 20 )       /* Receive Next Counter Register */
#تعریف_کرو PDC_TNPR            ( 24 )       /* Transmit Next Pointer Register */
#تعریف_کرو PDC_TNCR            ( 28 )       /* Transmit Next Counter Register */
#تعریف_کرو PDC_PTCR            ( 32 )       /* PDC Transfer Control Register */
#تعریف_کرو PDC_PTSR            ( 36 )       /* PDC Transfer Status Register */
/* -------- PDC_PTCR : (PDC Offset: 0x20) PDC Transfer Control Register -------- */
#تعریف_کرو AT91C_PDC_RXTEN     ( 0x1 << 0 ) /* (PDC) Receiver Transfer Enable */
#تعریف_کرو AT91C_PDC_RXTDIS    ( 0x1 << 1 ) /* (PDC) Receiver Transfer Disable */
#تعریف_کرو AT91C_PDC_TXTEN     ( 0x1 << 8 ) /* (PDC) Transmitter Transfer Enable */
#تعریف_کرو AT91C_PDC_TXTDIS    ( 0x1 << 9 ) /* (PDC) Transmitter Transfer Disable */
/* -------- PDC_PTSR : (PDC Offset: 0x24) PDC Transfer Status Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Parallel Input Output Controller */
/* ***************************************************************************** */
/* *** Register offset in AT91S_PIO structure *** */
#تعریف_کرو PIO_فی      ( 0 )   /* PIO Enable Register */
#تعریف_کرو PIO_PDR      ( 4 )   /* PIO Disable Register */
#تعریف_کرو PIO_PSR      ( 8 )   /* PIO Status Register */
#تعریف_کرو PIO_OER      ( 16 )  /* Output Enable Register */
#تعریف_کرو PIO_ODR      ( 20 )  /* Output Disable Registerr */
#تعریف_کرو PIO_OSR      ( 24 )  /* Output Status Register */
#تعریف_کرو PIO_IFER     ( 32 )  /* Input Filter Enable Register */
#تعریف_کرو PIO_IFDR     ( 36 )  /* Input Filter Disable Register */
#تعریف_کرو PIO_IFSR     ( 40 )  /* Input Filter Status Register */
#تعریف_کرو PIO_SODR     ( 48 )  /* Set Output Data Register */
#تعریف_کرو PIO_CODR     ( 52 )  /* Clear Output Data Register */
#تعریف_کرو PIO_ODSR     ( 56 )  /* Output Data Status Register */
#تعریف_کرو PIO_PDSR     ( 60 )  /* Pin Data Status Register */
#تعریف_کرو PIO_IER      ( 64 )  /* Interrupt Enable Register */
#تعریف_کرو PIO_IDR      ( 68 )  /* Interrupt Disable Register */
#تعریف_کرو PIO_IMR      ( 72 )  /* Interrupt Mask Register */
#تعریف_کرو PIO_ISR      ( 76 )  /* Interrupt Status Register */
#تعریف_کرو PIO_MDER     ( 80 )  /* Multi-driver Enable Register */
#تعریف_کرو PIO_MDDR     ( 84 )  /* Multi-driver Disable Register */
#تعریف_کرو PIO_MDSR     ( 88 )  /* Multi-driver Status Register */
#تعریف_کرو PIO_PPUDR    ( 96 )  /* Pull-up Disable Register */
#تعریف_کرو PIO_PPUER    ( 100 ) /* Pull-up Enable Register */
#تعریف_کرو PIO_PPUSR    ( 104 ) /* Pad Pull-up Status Register */
#تعریف_کرو PIO_ASR      ( 112 ) /* Select A Register */
#تعریف_کرو PIO_BSR      ( 116 ) /* Select B Register */
#تعریف_کرو PIO_ABSR     ( 120 ) /* AB Select Status Register */
#تعریف_کرو PIO_OWER     ( 160 ) /* Output Write Enable Register */
#تعریف_کرو PIO_OWDR     ( 164 ) /* Output Write Disable Register */
#تعریف_کرو PIO_OWSR     ( 168 ) /* Output Write Status Register */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Clock Generator Controller */
/* ***************************************************************************** */
/* *** Register offset in AT91S_CKGR structure *** */
#تعریف_کرو CKGR_MOR                     ( 0 )           /* Main Oscillator Register */
#تعریف_کرو CKGR_MCFR                    ( 4 )           /* Main Clock  Frequency Register */
#تعریف_کرو CKGR_PLLR                    ( 12 )          /* PLL Register */
/* -------- CKGR_MOR : (CKGR Offset: 0x0) Main Oscillator Register -------- */
#تعریف_کرو AT91C_CKGR_MOSCEN            ( 0x1 << 0 )    /* (CKGR) Main Oscillator Enable */
#تعریف_کرو AT91C_CKGR_OSCBYPASS         ( 0x1 << 1 )    /* (CKGR) Main Oscillator Bypass */
#تعریف_کرو AT91C_CKGR_OSCOUNT           ( 0xFF << 8 )   /* (CKGR) Main Oscillator Start-up Time */
/* -------- CKGR_MCFR : (CKGR Offset: 0x4) Main Clock Frequency Register -------- */
#تعریف_کرو AT91C_CKGR_MAINF             ( 0xFFFF << 0 ) /* (CKGR) Main Clock Frequency */
#تعریف_کرو AT91C_CKGR_MAINRDY           ( 0x1 << 16 )   /* (CKGR) Main Clock Ready */
/* -------- CKGR_PLLR : (CKGR Offset: 0xc) PLL B Register -------- */
#تعریف_کرو AT91C_CKGR_DIV               ( 0xFF << 0 )   /* (CKGR) Divider Selected */
#تعریف_کرو     AT91C_CKGR_DIV_0         ( 0x0 )         /* (CKGR) Divider output is 0 */
#تعریف_کرو     AT91C_CKGR_DIV_BYPASS    ( 0x1 )         /* (CKGR) Divider is bypassed */
#تعریف_کرو AT91C_CKGR_PLLCOUNT          ( 0x3F << 8 )   /* (CKGR) PLL Counter */
#تعریف_کرو AT91_C_CKGR_برآمد               ( 0x3 << 14 )   /* (CKGR) PLL Output Frequency Range */
#تعریف_کرو     AT91_C_CKGR_برآمد_0         ( 0x0 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#تعریف_کرو     AT91_C_CKGR_برآمد_1         ( 0x1 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#تعریف_کرو     AT91_C_CKGR_برآمد_2         ( 0x2 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#تعریف_کرو     AT91_C_CKGR_برآمد_3         ( 0x3 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#تعریف_کرو AT91C_CKGR_MUL               ( 0x7FF << 16 ) /* (CKGR) PLL Multiplier */
#تعریف_کرو AT91C_CKGR_USBDIV            ( 0x3 << 28 )   /* (CKGR) Divider for USB Clocks */
#تعریف_کرو     AT91C_CKGR_USBDIV_0      ( 0x0 << 28 )   /* (CKGR) Divider output is PLL clock output */
#تعریف_کرو     AT91C_CKGR_USBDIV_1      ( 0x1 << 28 )   /* (CKGR) Divider output is PLL clock output divided by 2 */
#تعریف_کرو     AT91C_CKGR_USBDIV_2      ( 0x2 << 28 )   /* (CKGR) Divider output is PLL clock output divided by 4 */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Power Management Controller */
/* ***************************************************************************** */
/* *** Register offset in AT91S_PMC structure *** */
#تعریف_کرو PMC_SCER          ( 0 )         /* System Clock Enable Register */
#تعریف_کرو PMC_SCDR          ( 4 )         /* System Clock Disable Register */
#تعریف_کرو PMC_SCSR          ( 8 )         /* System Clock Status Register */
#تعریف_کرو PMC_PCER          ( 16 )        /* Peripheral Clock Enable Register */
#تعریف_کرو PMC_PCDR          ( 20 )        /* Peripheral Clock Disable Register */
#تعریف_کرو PMC_PCSR          ( 24 )        /* Peripheral Clock Status Register */
#تعریف_کرو PMC_MOR           ( 32 )        /* Main Oscillator Register */
#تعریف_کرو PMC_MCFR          ( 36 )        /* Main Clock  Frequency Register */
#تعریف_کرو PMC_PLLR          ( 44 )        /* PLL Register */
#تعریف_کرو PMC_MCKR          ( 48 )        /* Master Clock Register */
#تعریف_کرو PMC_PCKR          ( 64 )        /* Programmable Clock Register */
#تعریف_کرو PMC_IER           ( 96 )        /* Interrupt Enable Register */
#تعریف_کرو PMC_IDR           ( 100 )       /* Interrupt Disable Register */
#تعریف_کرو PMC_SR            ( 104 )       /* Status Register */
#تعریف_کرو PMC_IMR           ( 108 )       /* Interrupt Mask Register */
/* -------- PMC_SCER : (PMC Offset: 0x0) System Clock Enable Register -------- */
#تعریف_کرو AT91C_PMC_PCK     ( 0x1 << 0 )  /* (PMC) Processor Clock */
#تعریف_کرو AT91C_PMC_UDP     ( 0x1 << 7 )  /* (PMC) USB Device Port Clock */
#تعریف_کرو AT91C_PMC_PCK0    ( 0x1 << 8 )  /* (PMC) Programmable Clock Output */
#تعریف_کرو AT91C_PMC_PCK1    ( 0x1 << 9 )  /* (PMC) Programmable Clock Output */
#تعریف_کرو AT91C_PMC_PCK2    ( 0x1 << 10 ) /* (PMC) Programmable Clock Output */
#تعریف_کرو AT91C_PMC_PCK3    ( 0x1 << 11 ) /* (PMC) Programmable Clock Output */
/* -------- PMC_SCDR : (PMC Offset: 0x4) System Clock Disable Register -------- */
/* -------- PMC_SCSR : (PMC Offset: 0x8) System Clock Status Register -------- */
/* -------- CKGR_MOR : (PMC Offset: 0x20) Main Oscillator Register -------- */
/* -------- CKGR_MCFR : (PMC Offset: 0x24) Main Clock Frequency Register -------- */
/* -------- CKGR_PLLR : (PMC Offset: 0x2c) PLL B Register -------- */
/* -------- PMC_MCKR : (PMC Offset: 0x30) Master Clock Register -------- */
#تعریف_کرو AT91C_PMC_CSS                 ( 0x3 << 0 ) /* (PMC) Programmable Clock Selection */
#تعریف_کرو     AT91C_PMC_CSS_SLOW_CLK    ( 0x0 )      /* (PMC) Slow Clock is selected */
#تعریف_کرو     AT91C_PMC_CSS_MAIN_CLK    ( 0x1 )      /* (PMC) Main Clock is selected */
#تعریف_کرو     AT91C_PMC_CSS_PLL_CLK     ( 0x3 )      /* (PMC) Clock from PLL is selected */
#تعریف_کرو AT91C_PMC_PRES                ( 0x7 << 2 ) /* (PMC) Programmable Clock Prescaler */
#تعریف_کرو     AT91C_PMC_PRES_CLK        ( 0x0 << 2 ) /* (PMC) Selected clock */
#تعریف_کرو     AT91C_PMC_PRES_CLK_2      ( 0x1 << 2 ) /* (PMC) Selected clock divided by 2 */
#تعریف_کرو     AT91C_PMC_PRES_CLK_4      ( 0x2 << 2 ) /* (PMC) Selected clock divided by 4 */
#تعریف_کرو     AT91C_PMC_PRES_CLK_8      ( 0x3 << 2 ) /* (PMC) Selected clock divided by 8 */
#تعریف_کرو     AT91C_PMC_PRES_CLK_16     ( 0x4 << 2 ) /* (PMC) Selected clock divided by 16 */
#تعریف_کرو     AT91C_PMC_PRES_CLK_32     ( 0x5 << 2 ) /* (PMC) Selected clock divided by 32 */
#تعریف_کرو     AT91C_PMC_PRES_CLK_64     ( 0x6 << 2 ) /* (PMC) Selected clock divided by 64 */
/* -------- PMC_PCKR : (PMC Offset: 0x40) Programmable Clock Register -------- */
/* -------- PMC_IER : (PMC Offset: 0x60) PMC Interrupt Enable Register -------- */
#تعریف_کرو AT91C_PMC_MOSCS               ( 0x1 << 0 )  /* (PMC) MOSC Status/Enable/Disable/Mask */
#تعریف_کرو AT91_C_PMC_تالا                ( 0x1 << 2 )  /* (PMC) PLL Status/Enable/Disable/Mask */
#تعریف_کرو AT91C_PMC_MCKRDY              ( 0x1 << 3 )  /* (PMC) MCK_RDY Status/Enable/Disable/Mask */
#تعریف_کرو AT91C_PMC_PCK0RDY             ( 0x1 << 8 )  /* (PMC) PCK0_RDY Status/Enable/Disable/Mask */
#تعریف_کرو AT91C_PMC_PCK1RDY             ( 0x1 << 9 )  /* (PMC) PCK1_RDY Status/Enable/Disable/Mask */
#تعریف_کرو AT91C_PMC_PCK2RDY             ( 0x1 << 10 ) /* (PMC) PCK2_RDY Status/Enable/Disable/Mask */
#تعریف_کرو AT91C_PMC_PCK3RDY             ( 0x1 << 11 ) /* (PMC) PCK3_RDY Status/Enable/Disable/Mask */
/* -------- PMC_IDR : (PMC Offset: 0x64) PMC Interrupt Disable Register -------- */
/* -------- PMC_SR : (PMC Offset: 0x68) PMC Status Register -------- */
/* -------- PMC_IMR : (PMC Offset: 0x6c) PMC Interrupt Mask Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Reset Controller Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_RSTC structure *** */
#تعریف_کرو RSTC_RCR                          ( 0 )          /* Reset Control Register */
#تعریف_کرو RSTC_RSR                          ( 4 )          /* Reset Status Register */
#تعریف_کرو RSTC_RMR                          ( 8 )          /* Reset Mode Register */
/* -------- SYSC_RCR : (RSTC Offset: 0x0) Reset Control Register -------- */
#تعریف_کرو AT91C_SYSC_PROCRST                ( 0x1 << 0 )   /* (RSTC) Processor Reset */
#تعریف_کرو AT91C_SYSC_ICERST                 ( 0x1 << 1 )   /* (RSTC) ICE Interface Reset */
#تعریف_کرو AT91C_SYSC_PERRST                 ( 0x1 << 2 )   /* (RSTC) Peripheral Reset */
#تعریف_کرو AT91C_SYSC_EXTRST                 ( 0x1 << 3 )   /* (RSTC) External Reset */
#تعریف_کرو AT91_C_SYSC_کلید                    ( 0xFF << 24 ) /* (RSTC) Password */
/* -------- SYSC_RSR : (RSTC Offset: 0x4) Reset Status Register -------- */
#تعریف_کرو AT91C_SYSC_URSTS                  ( 0x1 << 0 )   /* (RSTC) User Reset Status */
#تعریف_کرو AT91C_SYSC_BODSTS                 ( 0x1 << 1 )   /* (RSTC) Brown-out Detection Status */
#تعریف_کرو AT91C_SYSC_RSTTYP                 ( 0x7 << 8 )   /* (RSTC) Reset Type */
#تعریف_کرو     AT91C_SYSC_RSTTYP_POWERUP     ( 0x0 << 8 )   /* (RSTC) Power-up Reset. VDDCORE rising. */
#تعریف_کرو     AT91C_SYSC_RSTTYP_WATCHDOG    ( 0x2 << 8 )   /* (RSTC) Watchdog Reset. Watchdog overflow occurred. */
#تعریف_کرو     AT91C_SYSC_RSTTYP_SOFTWARE    ( 0x3 << 8 )   /* (RSTC) Software Reset. Processor reset required by the software. */
#تعریف_کرو     AT91C_SYSC_RSTTYP_USER        ( 0x4 << 8 )   /* (RSTC) User Reset. NRST pin detected low. */
#تعریف_کرو     AT91C_SYSC_RSTTYP_BROWNOUT    ( 0x5 << 8 )   /* (RSTC) Brown-out Reset. */
#تعریف_کرو AT91C_SYSC_NRSTL                  ( 0x1 << 16 )  /* (RSTC) NRST pin level */
#تعریف_کرو AT91C_SYSC_SRCMP                  ( 0x1 << 17 )  /* (RSTC) Software Reset Command in Progress. */
/* -------- SYSC_RMR : (RSTC Offset: 0x8) Reset Mode Register -------- */
#تعریف_کرو AT91C_SYSC_URSTEN                 ( 0x1 << 0 )   /* (RSTC) User Reset Enable */
#تعریف_کرو AT91C_SYSC_URSTIEN                ( 0x1 << 4 )   /* (RSTC) User Reset Interrupt Enable */
#تعریف_کرو AT91C_SYSC_ERSTL                  ( 0xF << 8 )   /* (RSTC) User Reset Enable */
#تعریف_کرو AT91C_SYSC_BODIEN                 ( 0x1 << 16 )  /* (RSTC) Brown-out Detection Interrupt Enable */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Real Time Timer Controller Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_RTTC structure *** */
#تعریف_کرو RTTC_RTMR               ( 0 )           /* Real-time Mode Register */
#تعریف_کرو RTTC_RTAR               ( 4 )           /* Real-time Alarm Register */
#تعریف_کرو RTTC_RTVR               ( 8 )           /* Real-time Value Register */
#تعریف_کرو RTTC_RTSR               ( 12 )          /* Real-time Status Register */
/* -------- SYSC_RTMR : (RTTC Offset: 0x0) Real-time Mode Register -------- */
#تعریف_کرو AT91C_SYSC_RTPRES       ( 0xFFFF << 0 ) /* (RTTC) Real-time Timer Prescaler Value */
#تعریف_کرو AT91C_SYSC_ALMIEN       ( 0x1 << 16 )   /* (RTTC) Alarm Interrupt Enable */
#تعریف_کرو AT91C_SYSC_RTTINCIEN    ( 0x1 << 17 )   /* (RTTC) Real Time Timer Increment Interrupt Enable */
#تعریف_کرو AT91C_SYSC_RTTRST       ( 0x1 << 18 )   /* (RTTC) Real Time Timer Restart */
/* -------- SYSC_RTAR : (RTTC Offset: 0x4) Real-time Alarm Register -------- */
#تعریف_کرو AT91C_SYSC_ALMV         ( 0x0 << 0 )    /* (RTTC) Alarm Value */
/* -------- SYSC_RTVR : (RTTC Offset: 0x8) Current Real-time Value Register -------- */
#تعریف_کرو AT91C_SYSC_CRTV         ( 0x0 << 0 )    /* (RTTC) Current Real-time Value */
/* -------- SYSC_RTSR : (RTTC Offset: 0xc) Real-time Status Register -------- */
#تعریف_کرو AT91C_SYSC_ALMS         ( 0x1 << 0 )    /* (RTTC) Real-time Alarm Status */
#تعریف_کرو AT91C_SYSC_RTTINC       ( 0x1 << 1 )    /* (RTTC) Real-time Timer Increment */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Periodic Interval Timer Controller Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_PITC structure *** */
#تعریف_کرو PITC_PIMR            ( 0 )            /* Period Interval Mode Register */
#تعریف_کرو PITC_PISR            ( 4 )            /* Period Interval Status Register */
#تعریف_کرو PITC_PIVR            ( 8 )            /* Period Interval Value Register */
#تعریف_کرو PITC_PIIR            ( 12 )           /* Period Interval Image Register */
/* -------- SYSC_PIMR : (PITC Offset: 0x0) Periodic Interval Mode Register -------- */
#تعریف_کرو AT91C_SYSC_PIV       ( 0xFFFFF << 0 ) /* (PITC) Periodic Interval Value */
#تعریف_کرو AT91C_SYSC_PITEN     ( 0x1 << 24 )    /* (PITC) Periodic Interval Timer Enabled */
#تعریف_کرو AT91C_SYSC_PITIEN    ( 0x1 << 25 )    /* (PITC) Periodic Interval Timer Interrupt Enable */
/* -------- SYSC_PISR : (PITC Offset: 0x4) Periodic Interval Status Register -------- */
#تعریف_کرو AT91C_SYSC_PITS      ( 0x1 << 0 )     /* (PITC) Periodic Interval Timer Status */
/* -------- SYSC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register -------- */
#تعریف_کرو AT91C_SYSC_CPIV      ( 0xFFFFF << 0 ) /* (PITC) Current Periodic Interval Value */
#تعریف_کرو AT91C_SYSC_PICNT     ( 0xFFF << 20 )  /* (PITC) Periodic Interval Counter */
/* -------- SYSC_PIIR : (PITC Offset: 0xc) Periodic Interval Image Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Watchdog Timer Controller Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_WDTC structure *** */
#تعریف_کرو WDTC_WDCR               ( 0 )           /* Watchdog Control Register */
#تعریف_کرو WDTC_WDMR               ( 4 )           /* Watchdog Mode Register */
#تعریف_کرو WDTC_WDSR               ( 8 )           /* Watchdog Status Register */
/* -------- SYSC_WDCR : (WDTC Offset: 0x0) Periodic Interval Image Register -------- */
#تعریف_کرو AT91C_SYSC_WDRSTT       ( 0x1 << 0 )    /* (WDTC) Watchdog Restart */
/* -------- SYSC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register -------- */
#تعریف_کرو AT91C_SYSC_WDV          ( 0xFFF << 0 )  /* (WDTC) Watchdog Timer Restart */
#تعریف_کرو AT91C_SYSC_WDFIEN       ( 0x1 << 12 )   /* (WDTC) Watchdog Fault Interrupt Enable */
#تعریف_کرو AT91C_SYSC_WDRSTEN      ( 0x1 << 13 )   /* (WDTC) Watchdog Reset Enable */
#تعریف_کرو AT91C_SYSC_WDRPROC      ( 0x1 << 14 )   /* (WDTC) Watchdog Timer Restart */
#تعریف_کرو AT91C_SYSC_WDDIS        ( 0x1 << 15 )   /* (WDTC) Watchdog Disable */
#تعریف_کرو AT91C_SYSC_WDD          ( 0xFFF << 16 ) /* (WDTC) Watchdog Delta Value */
#تعریف_کرو AT91C_SYSC_WDDBGHLT     ( 0x1 << 28 )   /* (WDTC) Watchdog Debug Halt */
#تعریف_کرو AT91C_SYSC_WDIDLEHLT    ( 0x1 << 29 )   /* (WDTC) Watchdog Idle Halt */
/* -------- SYSC_WDSR : (WDTC Offset: 0x8) Watchdog Status Register -------- */
#تعریف_کرو AT91C_SYSC_WDUNF        ( 0x1 << 0 )    /* (WDTC) Watchdog Underflow */
#تعریف_کرو AT91C_SYSC_WDERR        ( 0x1 << 1 )    /* (WDTC) Watchdog Error */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Memory Controller Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_MC structure *** */
#تعریف_کرو MC_RCR                             ( 0 )          /* MC Remap Control Register */
#تعریف_کرو MC_ASR                             ( 4 )          /* MC Abort Status Register */
#تعریف_کرو MC_AASR                            ( 8 )          /* MC Abort Address Status Register */
#تعریف_کرو MC_FMR                             ( 96 )         /* MC Flash Mode Register */
#تعریف_کرو MC_FCR                             ( 100 )        /* MC Flash Command Register */
#تعریف_کرو MC_FSR                             ( 104 )        /* MC Flash Status Register */
/* -------- MC_RCR : (MC Offset: 0x0) MC Remap Control Register -------- */
#تعریف_کرو AT91C_MC_RCB                       ( 0x1 << 0 )   /* (MC) Remap Command Bit */
/* -------- MC_ASR : (MC Offset: 0x4) MC Abort Status Register -------- */
#تعریف_کرو AT91C_MC_UNDADD                    ( 0x1 << 0 )   /* (MC) Undefined Address Abort Status */
#تعریف_کرو AT91C_MC_MISADD                    ( 0x1 << 1 )   /* (MC) Misaligned Address Abort Status */
#تعریف_کرو AT91C_MC_ABTSZ                     ( 0x3 << 8 )   /* (MC) Abort Size Status */
#تعریف_کرو     AT91C_MC_ABTSZ_BYTE            ( 0x0 << 8 )   /* (MC) Byte */
#تعریف_کرو     AT91C_MC_ABTSZ_HWORD           ( 0x1 << 8 )   /* (MC) Half-word */
#تعریف_کرو     AT91_C_MC_ABTSZ_لفظ            ( 0x2 << 8 )   /* (MC) Word */
#تعریف_کرو AT91C_MC_ABTTYP                    ( 0x3 << 10 )  /* (MC) Abort Type Status */
#تعریف_کرو     AT91C_MC_ABTTYP_DATAR          ( 0x0 << 10 )  /* (MC) Data Read */
#تعریف_کرو     AT91C_MC_ABTTYP_DATAW          ( 0x1 << 10 )  /* (MC) Data Write */
#تعریف_کرو     AT91C_MC_ABTTYP_FETCH          ( 0x2 << 10 )  /* (MC) Code Fetch */
#تعریف_کرو AT91C_MC_MST0                      ( 0x1 << 16 )  /* (MC) Master 0 Abort Source */
#تعریف_کرو AT91C_MC_MST1                      ( 0x1 << 17 )  /* (MC) Master 1 Abort Source */
#تعریف_کرو AT91C_MC_SVMST0                    ( 0x1 << 24 )  /* (MC) Saved Master 0 Abort Source */
#تعریف_کرو AT91C_MC_SVMST1                    ( 0x1 << 25 )  /* (MC) Saved Master 1 Abort Source */
/* -------- MC_FMR : (MC Offset: 0x60) MC Flash Mode Register -------- */
#تعریف_کرو AT91C_MC_FRDY                      ( 0x1 << 0 )   /* (MC) Flash Ready */
#تعریف_کرو AT91C_MC_LOCKE                     ( 0x1 << 2 )   /* (MC) Lock Error */
#تعریف_کرو AT91C_MC_PROGE                     ( 0x1 << 3 )   /* (MC) Programming Error */
#تعریف_کرو AT91C_MC_NEBP                      ( 0x1 << 7 )   /* (MC) No Erase Before Programming */
#تعریف_کرو AT91C_MC_FWS                       ( 0x3 << 8 )   /* (MC) Flash Wait State */
#تعریف_کرو     AT91C_MC_FWS_0FWS              ( 0x0 << 8 )   /* (MC) 1 cycle for Read, 2 for Write operations */
#تعریف_کرو     AT91C_MC_FWS_1FWS              ( 0x1 << 8 )   /* (MC) 2 cycles for Read, 3 for Write operations */
#تعریف_کرو     AT91C_MC_FWS_2FWS              ( 0x2 << 8 )   /* (MC) 3 cycles for Read, 4 for Write operations */
#تعریف_کرو     AT91C_MC_FWS_3FWS              ( 0x3 << 8 )   /* (MC) 4 cycles for Read, 4 for Write operations */
#تعریف_کرو AT91C_MC_FMCN                      ( 0xFF << 16 ) /* (MC) Flash Microsecond Cycle Number */
/* -------- MC_FCR : (MC Offset: 0x64) MC Flash Command Register -------- */
#تعریف_کرو AT91C_MC_FCMD                      ( 0xF << 0 )   /* (MC) Flash Command */
#تعریف_کرو     AT91_C_MC_FCMD_آغاز_PROG       ( 0x1 )        /* (MC) Starts the programming of th epage specified by PAGEN. */
#تعریف_کرو     AT91_C_MC_FCMD_تالا             ( 0x2 )        /* (MC) Starts a lock sequence of the sector defined by the bits 4 to 7 of the field PAGEN. */
#تعریف_کرو     AT91_C_MC_FCMD_PROG_AND_تالا    ( 0x3 )        /* (MC) The lock sequence automatically happens after the programming sequence is completed. */
#تعریف_کرو     AT91C_MC_FCMD_UNLOCK           ( 0x4 )        /* (MC) Starts an unlock sequence of the sector defined by the bits 4 to 7 of the field PAGEN. */
#تعریف_کرو     AT91C_MC_FCMD_ERASE_ALL        ( 0x8 )        /* (MC) Starts the erase of the entire flash.If at least a page is locked, the command is cancelled. */
#تعریف_کرو     AT91_C_MC_FCMD_سیٹ_GP_NVM       ( 0xB )        /* (MC) Set General Purpose NVM bits. */
#تعریف_کرو     AT91C_MC_FCMD_CLR_GP_NVM       ( 0xD )        /* (MC) Clear General Purpose NVM bits. */
#تعریف_کرو     AT91_C_MC_FCMD_سیٹ_SECURITY     ( 0xF )        /* (MC) Set Security Bit. */
#تعریف_کرو AT91C_MC_PAGEN                     ( 0x3FF << 8 ) /* (MC) Page Number */
#تعریف_کرو AT91_C_MC_کلید                       ( 0xFF << 24 ) /* (MC) Writing Protect Key */
/* -------- MC_FSR : (MC Offset: 0x68) MC Flash Command Register -------- */
#تعریف_کرو AT91C_MC_SECURITY                  ( 0x1 << 4 )   /* (MC) Security Bit Status */
#تعریف_کرو AT91C_MC_GPNVM0                    ( 0x1 << 8 )   /* (MC) Sector 0 Lock Status */
#تعریف_کرو AT91C_MC_GPNVM1                    ( 0x1 << 9 )   /* (MC) Sector 1 Lock Status */
#تعریف_کرو AT91C_MC_GPNVM2                    ( 0x1 << 10 )  /* (MC) Sector 2 Lock Status */
#تعریف_کرو AT91C_MC_GPNVM3                    ( 0x1 << 11 )  /* (MC) Sector 3 Lock Status */
#تعریف_کرو AT91C_MC_GPNVM4                    ( 0x1 << 12 )  /* (MC) Sector 4 Lock Status */
#تعریف_کرو AT91C_MC_GPNVM5                    ( 0x1 << 13 )  /* (MC) Sector 5 Lock Status */
#تعریف_کرو AT91C_MC_GPNVM6                    ( 0x1 << 14 )  /* (MC) Sector 6 Lock Status */
#تعریف_کرو AT91C_MC_GPNVM7                    ( 0x1 << 15 )  /* (MC) Sector 7 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS0                    ( 0x1 << 16 )  /* (MC) Sector 0 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS1                    ( 0x1 << 17 )  /* (MC) Sector 1 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS2                    ( 0x1 << 18 )  /* (MC) Sector 2 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS3                    ( 0x1 << 19 )  /* (MC) Sector 3 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS4                    ( 0x1 << 20 )  /* (MC) Sector 4 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS5                    ( 0x1 << 21 )  /* (MC) Sector 5 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS6                    ( 0x1 << 22 )  /* (MC) Sector 6 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS7                    ( 0x1 << 23 )  /* (MC) Sector 7 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS8                    ( 0x1 << 24 )  /* (MC) Sector 8 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS9                    ( 0x1 << 25 )  /* (MC) Sector 9 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS10                   ( 0x1 << 26 )  /* (MC) Sector 10 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS11                   ( 0x1 << 27 )  /* (MC) Sector 11 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS12                   ( 0x1 << 28 )  /* (MC) Sector 12 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS13                   ( 0x1 << 29 )  /* (MC) Sector 13 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS14                   ( 0x1 << 30 )  /* (MC) Sector 14 Lock Status */
#تعریف_کرو AT91C_MC_LOCKS15                   ( 0x1 << 31 )  /* (MC) Sector 15 Lock Status */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Serial Parallel Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_SPI structure *** */
#تعریف_کرو SPI_CR                       ( 0 )           /* Control Register */
#تعریف_کرو SPI_MR                       ( 4 )           /* Mode Register */
#تعریف_کرو SPI_RDR                      ( 8 )           /* Receive Data Register */
#تعریف_کرو SPI_TDR                      ( 12 )          /* Transmit Data Register */
#تعریف_کرو SPI_SR                       ( 16 )          /* Status Register */
#تعریف_کرو SPI_IER                      ( 20 )          /* Interrupt Enable Register */
#تعریف_کرو SPI_IDR                      ( 24 )          /* Interrupt Disable Register */
#تعریف_کرو SPI_IMR                      ( 28 )          /* Interrupt Mask Register */
#تعریف_کرو SPI_CSR                      ( 48 )          /* Chip Select Register */
#تعریف_کرو SPI_RPR                      ( 256 )         /* Receive Pointer Register */
#تعریف_کرو SPI_RCR                      ( 260 )         /* Receive Counter Register */
#تعریف_کرو SPI_TPR                      ( 264 )         /* Transmit Pointer Register */
#تعریف_کرو SPI_TCR                      ( 268 )         /* Transmit Counter Register */
#تعریف_کرو SPI_RNPR                     ( 272 )         /* Receive Next Pointer Register */
#تعریف_کرو SPI_RNCR                     ( 276 )         /* Receive Next Counter Register */
#تعریف_کرو SPI_TNPR                     ( 280 )         /* Transmit Next Pointer Register */
#تعریف_کرو SPI_TNCR                     ( 284 )         /* Transmit Next Counter Register */
#تعریف_کرو SPI_PTCR                     ( 288 )         /* PDC Transfer Control Register */
#تعریف_کرو SPI_PTSR                     ( 292 )         /* PDC Transfer Status Register */
/* -------- SPI_CR : (SPI Offset: 0x0) SPI Control Register -------- */
#تعریف_کرو AT91C_SPI_SPIEN              ( 0x1 << 0 )    /* (SPI) SPI Enable */
#تعریف_کرو AT91C_SPI_SPIDIS             ( 0x1 << 1 )    /* (SPI) SPI Disable */
#تعریف_کرو AT91C_SPI_SWRST              ( 0x1 << 7 )    /* (SPI) SPI Software reset */
#تعریف_کرو AT91C_SPI_LASTXFER           ( 0x1 << 24 )   /* (SPI) SPI Last Transfer */
/* -------- SPI_MR : (SPI Offset: 0x4) SPI Mode Register -------- */
#تعریف_کرو AT91C_SPI_MSTR               ( 0x1 << 0 )    /* (SPI) Master/Slave Mode */
#تعریف_کرو AT91C_SPI_PS                 ( 0x1 << 1 )    /* (SPI) Peripheral Select */
#تعریف_کرو     AT91C_SPI_PS_FIXED       ( 0x0 << 1 )    /* (SPI) Fixed Peripheral Select */
#تعریف_کرو     AT91C_SPI_PS_VARIABLE    ( 0x1 << 1 )    /* (SPI) Variable Peripheral Select */
#تعریف_کرو AT91C_SPI_PCSDEC             ( 0x1 << 2 )    /* (SPI) Chip Select Decode */
#تعریف_کرو AT91C_SPI_FDIV               ( 0x1 << 3 )    /* (SPI) Clock Selection */
#تعریف_کرو AT91C_SPI_MODFDIS            ( 0x1 << 4 )    /* (SPI) Mode Fault Detection */
#تعریف_کرو AT91C_SPI_LLB                ( 0x1 << 7 )    /* (SPI) Clock Selection */
#تعریف_کرو AT91C_SPI_PCS                ( 0xF << 16 )   /* (SPI) Peripheral Chip Select */
#تعریف_کرو AT91C_SPI_DLYBCS             ( 0xFF << 24 )  /* (SPI) Delay Between Chip Selects */
/* -------- SPI_RDR : (SPI Offset: 0x8) Receive Data Register -------- */
#تعریف_کرو AT91C_SPI_RD                 ( 0xFFFF << 0 ) /* (SPI) Receive Data */
#تعریف_کرو AT91C_SPI_RPCS               ( 0xF << 16 )   /* (SPI) Peripheral Chip Select Status */
/* -------- SPI_TDR : (SPI Offset: 0xc) Transmit Data Register -------- */
#تعریف_کرو AT91C_SPI_TD                 ( 0xFFFF << 0 ) /* (SPI) Transmit Data */
#تعریف_کرو AT91C_SPI_TPCS               ( 0xF << 16 )   /* (SPI) Peripheral Chip Select Status */
/* -------- SPI_SR : (SPI Offset: 0x10) Status Register -------- */
#تعریف_کرو AT91C_SPI_RDRF               ( 0x1 << 0 )    /* (SPI) Receive Data Register Full */
#تعریف_کرو AT91C_SPI_TDRE               ( 0x1 << 1 )    /* (SPI) Transmit Data Register Empty */
#تعریف_کرو AT91C_SPI_MODF               ( 0x1 << 2 )    /* (SPI) Mode Fault Error */
#تعریف_کرو AT91C_SPI_OVRES              ( 0x1 << 3 )    /* (SPI) Overrun Error Status */
#تعریف_کرو AT91C_SPI_ENDRX              ( 0x1 << 4 )    /* (SPI) End of Receiver Transfer */
#تعریف_کرو AT91C_SPI_ENDTX              ( 0x1 << 5 )    /* (SPI) End of Receiver Transfer */
#تعریف_کرو AT91C_SPI_RXBUFF             ( 0x1 << 6 )    /* (SPI) RXBUFF Interrupt */
#تعریف_کرو AT91C_SPI_TXBUFE             ( 0x1 << 7 )    /* (SPI) TXBUFE Interrupt */
#تعریف_کرو AT91C_SPI_NSSR               ( 0x1 << 8 )    /* (SPI) NSSR Interrupt */
#تعریف_کرو AT91C_SPI_TXEMPTY            ( 0x1 << 9 )    /* (SPI) TXEMPTY Interrupt */
#تعریف_کرو AT91C_SPI_SPIENS             ( 0x1 << 16 )   /* (SPI) Enable Status */
/* -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- */
/* -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- */
/* -------- SPI_IMR : (SPI Offset: 0x1c) Interrupt Mask Register -------- */
/* -------- SPI_CSR : (SPI Offset: 0x30) Chip Select Register -------- */
#تعریف_کرو AT91C_SPI_CPOL           ( 0x1 << 0 )   /* (SPI) Clock Polarity */
#تعریف_کرو AT91C_SPI_NCPHA          ( 0x1 << 1 )   /* (SPI) Clock Phase */
#تعریف_کرو AT91C_SPI_CSAAT          ( 0x1 << 2 )   /* (SPI) Chip Select Active After Transfer */
#تعریف_کرو AT91_C_SPI_بٹ           ( 0xF << 4 )   /* (SPI) Bits Per Transfer */
#تعریف_کرو     AT91_C_SPI_بٹ_8     ( 0x0 << 4 )   /* (SPI) 8 Bits Per transfer */
#تعریف_کرو     AT91_C_SPI_بٹ_9     ( 0x1 << 4 )   /* (SPI) 9 Bits Per transfer */
#تعریف_کرو     AT91_C_SPI_بٹ_10    ( 0x2 << 4 )   /* (SPI) 10 Bits Per transfer */
#تعریف_کرو     AT91_C_SPI_بٹ_11    ( 0x3 << 4 )   /* (SPI) 11 Bits Per transfer */
#تعریف_کرو     AT91_C_SPI_بٹ_12    ( 0x4 << 4 )   /* (SPI) 12 Bits Per transfer */
#تعریف_کرو     AT91_C_SPI_بٹ_13    ( 0x5 << 4 )   /* (SPI) 13 Bits Per transfer */
#تعریف_کرو     AT91_C_SPI_بٹ_14    ( 0x6 << 4 )   /* (SPI) 14 Bits Per transfer */
#تعریف_کرو     AT91_C_SPI_بٹ_15    ( 0x7 << 4 )   /* (SPI) 15 Bits Per transfer */
#تعریف_کرو     AT91_C_SPI_بٹ_16    ( 0x8 << 4 )   /* (SPI) 16 Bits Per transfer */
#تعریف_کرو AT91C_SPI_SCBR           ( 0xFF << 8 )  /* (SPI) Serial Clock Baud Rate */
#تعریف_کرو AT91C_SPI_DLYBS          ( 0xFF << 16 ) /* (SPI) Serial Clock Baud Rate */
#تعریف_کرو AT91C_SPI_DLYBCT         ( 0xFF << 24 ) /* (SPI) Delay Between Consecutive Transfers */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Analog to Digital Convertor */
/* ***************************************************************************** */
/* *** Register offset in AT91S_ADC structure *** */
#تعریف_کرو ADC_CR                             ( 0 )          /* ADC Control Register */
#تعریف_کرو ADC_MR                             ( 4 )          /* ADC Mode Register */
#تعریف_کرو ADC_CHER                           ( 16 )         /* ADC Channel Enable Register */
#تعریف_کرو ADC_CHDR                           ( 20 )         /* ADC Channel Disable Register */
#تعریف_کرو ADC_CHSR                           ( 24 )         /* ADC Channel Status Register */
#تعریف_کرو ADC_SR                             ( 28 )         /* ADC Status Register */
#تعریف_کرو ADC_LCDR                           ( 32 )         /* ADC Last Converted Data Register */
#تعریف_کرو ADC_IER                            ( 36 )         /* ADC Interrupt Enable Register */
#تعریف_کرو ADC_IDR                            ( 40 )         /* ADC Interrupt Disable Register */
#تعریف_کرو ADC_IMR                            ( 44 )         /* ADC Interrupt Mask Register */
#تعریف_کرو ADC_CDR0                           ( 48 )         /* ADC Channel Data Register 0 */
#تعریف_کرو ADC_CDR1                           ( 52 )         /* ADC Channel Data Register 1 */
#تعریف_کرو ADC_CDR2                           ( 56 )         /* ADC Channel Data Register 2 */
#تعریف_کرو ADC_CDR3                           ( 60 )         /* ADC Channel Data Register 3 */
#تعریف_کرو ADC_CDR4                           ( 64 )         /* ADC Channel Data Register 4 */
#تعریف_کرو ADC_CDR5                           ( 68 )         /* ADC Channel Data Register 5 */
#تعریف_کرو ADC_CDR6                           ( 72 )         /* ADC Channel Data Register 6 */
#تعریف_کرو ADC_CDR7                           ( 76 )         /* ADC Channel Data Register 7 */
#تعریف_کرو ADC_RPR                            ( 256 )        /* Receive Pointer Register */
#تعریف_کرو ADC_RCR                            ( 260 )        /* Receive Counter Register */
#تعریف_کرو ADC_TPR                            ( 264 )        /* Transmit Pointer Register */
#تعریف_کرو ADC_TCR                            ( 268 )        /* Transmit Counter Register */
#تعریف_کرو ADC_RNPR                           ( 272 )        /* Receive Next Pointer Register */
#تعریف_کرو ADC_RNCR                           ( 276 )        /* Receive Next Counter Register */
#تعریف_کرو ADC_TNPR                           ( 280 )        /* Transmit Next Pointer Register */
#تعریف_کرو ADC_TNCR                           ( 284 )        /* Transmit Next Counter Register */
#تعریف_کرو ADC_PTCR                           ( 288 )        /* PDC Transfer Control Register */
#تعریف_کرو ADC_PTSR                           ( 292 )        /* PDC Transfer Status Register */
/* -------- ADC_CR : (ADC Offset: 0x0) ADC Control Register -------- */
#تعریف_کرو AT91C_ADC_SWRST                    ( 0x1 << 0 )   /* (ADC) Software Reset */
#تعریف_کرو AT91_C_ADC_آغاز                    ( 0x1 << 1 )   /* (ADC) Start Conversion */
/* -------- ADC_MR : (ADC Offset: 0x4) ADC Mode Register -------- */
#تعریف_کرو AT91C_ADC_TRGEN                    ( 0x1 << 0 )   /* (ADC) Trigger Enable */
#تعریف_کرو     AT91C_ADC_TRGEN_DIS            ( 0x0 )        /* (ADC) Hardware triggers are disabled. Starting a conversion is only possible by software */
#تعریف_کرو     AT91C_ADC_TRGEN_EN             ( 0x1 )        /* (ADC) Hardware trigger selected by TRGSEL field is enabled. */
#تعریف_کرو AT91C_ADC_TRGSEL                   ( 0x7 << 1 )   /* (ADC) Trigger Selection */
#تعریف_کرو     AT91C_ADC_TRGSEL_TIOA0         ( 0x0 << 1 )   /* (ADC) Selected TRGSEL = TIAO0 */
#تعریف_کرو     AT91C_ADC_TRGSEL_TIOA1         ( 0x1 << 1 )   /* (ADC) Selected TRGSEL = TIAO1 */
#تعریف_کرو     AT91C_ADC_TRGSEL_TIOA2         ( 0x2 << 1 )   /* (ADC) Selected TRGSEL = TIAO2 */
#تعریف_کرو     AT91C_ADC_TRGSEL_TIOA3         ( 0x3 << 1 )   /* (ADC) Selected TRGSEL = TIAO3 */
#تعریف_کرو     AT91C_ADC_TRGSEL_TIOA4         ( 0x4 << 1 )   /* (ADC) Selected TRGSEL = TIAO4 */
#تعریف_کرو     AT91C_ADC_TRGSEL_TIOA5         ( 0x5 << 1 )   /* (ADC) Selected TRGSEL = TIAO5 */
#تعریف_کرو     AT91C_ADC_TRGSEL_EXT           ( 0x6 << 1 )   /* (ADC) Selected TRGSEL = External Trigger */
#تعریف_کرو AT91C_ADC_LOWRES                   ( 0x1 << 4 )   /* (ADC) Resolution. */
#تعریف_کرو     AT91_C_ADC_LOWRES_10_ثنائی_ہندسہ        ( 0x0 << 4 )   /* (ADC) 10-bit resolution */
#تعریف_کرو     AT91_C_ADC_LOWRES_8_ثنائی_ہندسہ         ( 0x1 << 4 )   /* (ADC) 8-bit resolution */
#تعریف_کرو AT91C_ADC_SLEEP                    ( 0x1 << 5 )   /* (ADC) Sleep Mode */
#تعریف_کرو     AT91_C_ADC_SLEEP_معمول_منوال    ( 0x0 << 5 )   /* (ADC) Normal Mode */
#تعریف_کرو     AT91_C_ADC_SLEEP_منوال           ( 0x1 << 5 )   /* (ADC) Sleep Mode */
#تعریف_کرو AT91C_ADC_PRESCAL                  ( 0x3F << 8 )  /* (ADC) Prescaler rate selection */
#تعریف_کرو AT91C_ADC_STARTUP                  ( 0x1F << 16 ) /* (ADC) Startup Time */
#تعریف_کرو AT91C_ADC_SHTIM                    ( 0xF << 24 )  /* (ADC) Sample & Hold Time */
/* --------     ADC_CHER : (ADC Offset: 0x10) ADC Channel Enable Register -------- */
#تعریف_کرو AT91C_ADC_CH0                      ( 0x1 << 0 )   /* (ADC) Channel 0 */
#تعریف_کرو AT91C_ADC_CH1                      ( 0x1 << 1 )   /* (ADC) Channel 1 */
#تعریف_کرو AT91C_ADC_CH2                      ( 0x1 << 2 )   /* (ADC) Channel 2 */
#تعریف_کرو AT91C_ADC_CH3                      ( 0x1 << 3 )   /* (ADC) Channel 3 */
#تعریف_کرو AT91C_ADC_CH4                      ( 0x1 << 4 )   /* (ADC) Channel 4 */
#تعریف_کرو AT91C_ADC_CH5                      ( 0x1 << 5 )   /* (ADC) Channel 5 */
#تعریف_کرو AT91C_ADC_CH6                      ( 0x1 << 6 )   /* (ADC) Channel 6 */
#تعریف_کرو AT91C_ADC_CH7                      ( 0x1 << 7 )   /* (ADC) Channel 7 */
/* --------     ADC_CHDR : (ADC Offset: 0x14) ADC Channel Disable Register -------- */
/* --------     ADC_CHSR : (ADC Offset: 0x18) ADC Channel Status Register -------- */
/* -------- ADC_SR : (ADC Offset: 0x1c) ADC Status Register -------- */
#تعریف_کرو AT91C_ADC_EOC0      ( 0x1 << 0 )      /* (ADC) End of Conversion */
#تعریف_کرو AT91C_ADC_EOC1      ( 0x1 << 1 )      /* (ADC) End of Conversion */
#تعریف_کرو AT91C_ADC_EOC2      ( 0x1 << 2 )      /* (ADC) End of Conversion */
#تعریف_کرو AT91C_ADC_EOC3      ( 0x1 << 3 )      /* (ADC) End of Conversion */
#تعریف_کرو AT91C_ADC_EOC4      ( 0x1 << 4 )      /* (ADC) End of Conversion */
#تعریف_کرو AT91C_ADC_EOC5      ( 0x1 << 5 )      /* (ADC) End of Conversion */
#تعریف_کرو AT91C_ADC_EOC6      ( 0x1 << 6 )      /* (ADC) End of Conversion */
#تعریف_کرو AT91C_ADC_EOC7      ( 0x1 << 7 )      /* (ADC) End of Conversion */
#تعریف_کرو AT91C_ADC_OVRE0     ( 0x1 << 8 )      /* (ADC) Overrun Error */
#تعریف_کرو AT91C_ADC_OVRE1     ( 0x1 << 9 )      /* (ADC) Overrun Error */
#تعریف_کرو AT91C_ADC_OVRE2     ( 0x1 << 10 )     /* (ADC) Overrun Error */
#تعریف_کرو AT91C_ADC_OVRE3     ( 0x1 << 11 )     /* (ADC) Overrun Error */
#تعریف_کرو AT91C_ADC_OVRE4     ( 0x1 << 12 )     /* (ADC) Overrun Error */
#تعریف_کرو AT91C_ADC_OVRE5     ( 0x1 << 13 )     /* (ADC) Overrun Error */
#تعریف_کرو AT91C_ADC_OVRE6     ( 0x1 << 14 )     /* (ADC) Overrun Error */
#تعریف_کرو AT91C_ADC_OVRE7     ( 0x1 << 15 )     /* (ADC) Overrun Error */
#تعریف_کرو AT91C_ADC_DRDY      ( 0x1 << 16 )     /* (ADC) Data Ready */
#تعریف_کرو AT91C_ADC_GOVRE     ( 0x1 << 17 )     /* (ADC) General Overrun */
#تعریف_کرو AT91C_ADC_ENDRX     ( 0x1 << 18 )     /* (ADC) End of Receiver Transfer */
#تعریف_کرو AT91C_ADC_RXBUFF    ( 0x1 << 19 )     /* (ADC) RXBUFF Interrupt */
/* -------- ADC_LCDR : (ADC Offset: 0x20) ADC Last Converted Data Register -------- */
#تعریف_کرو AT91C_ADC_LDATA     ( 0x3FF << 0 )    /* (ADC) Last Data Converted */
/* -------- ADC_IER : (ADC Offset: 0x24) ADC Interrupt Enable Register -------- */
/* -------- ADC_IDR : (ADC Offset: 0x28) ADC Interrupt Disable Register -------- */
/* -------- ADC_IMR : (ADC Offset: 0x2c) ADC Interrupt Mask Register -------- */
/* -------- ADC_CDR0 : (ADC Offset: 0x30) ADC Channel Data Register 0 -------- */
#تعریف_کرو AT91_C_ADC_ڈیٹا    ( 0x3FF << 0 )        /* (ADC) Converted Data */
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
/* *** Register offset in AT91S_SSC structure *** */
#تعریف_کرو SSC_CR                            ( 0 )          /* Control Register */
#تعریف_کرو SSC_CMR                           ( 4 )          /* Clock Mode Register */
#تعریف_کرو SSC_RCMR                          ( 16 )         /* Receive Clock ModeRegister */
#تعریف_کرو SSC_RFMR                          ( 20 )         /* Receive Frame Mode Register */
#تعریف_کرو SSC_TCMR                          ( 24 )         /* Transmit Clock Mode Register */
#تعریف_کرو SSC_TFMR                          ( 28 )         /* Transmit Frame Mode Register */
#تعریف_کرو SSC_RHR                           ( 32 )         /* Receive Holding Register */
#تعریف_کرو SSC_THR                           ( 36 )         /* Transmit Holding Register */
#تعریف_کرو SSC_RSHR                          ( 48 )         /* Receive Sync Holding Register */
#تعریف_کرو SSC_TSHR                          ( 52 )         /* Transmit Sync Holding Register */
#تعریف_کرو SSC_RC0R                          ( 56 )         /* Receive Compare 0 Register */
#تعریف_کرو SSC_RC1R                          ( 60 )         /* Receive Compare 1 Register */
#تعریف_کرو SSC_SR                            ( 64 )         /* Status Register */
#تعریف_کرو SSC_IER                           ( 68 )         /* Interrupt Enable Register */
#تعریف_کرو SSC_IDR                           ( 72 )         /* Interrupt Disable Register */
#تعریف_کرو SSC_IMR                           ( 76 )         /* Interrupt Mask Register */
#تعریف_کرو SSC_RPR                           ( 256 )        /* Receive Pointer Register */
#تعریف_کرو SSC_RCR                           ( 260 )        /* Receive Counter Register */
#تعریف_کرو SSC_TPR                           ( 264 )        /* Transmit Pointer Register */
#تعریف_کرو SSC_TCR                           ( 268 )        /* Transmit Counter Register */
#تعریف_کرو SSC_RNPR                          ( 272 )        /* Receive Next Pointer Register */
#تعریف_کرو SSC_RNCR                          ( 276 )        /* Receive Next Counter Register */
#تعریف_کرو SSC_TNPR                          ( 280 )        /* Transmit Next Pointer Register */
#تعریف_کرو SSC_TNCR                          ( 284 )        /* Transmit Next Counter Register */
#تعریف_کرو SSC_PTCR                          ( 288 )        /* PDC Transfer Control Register */
#تعریف_کرو SSC_PTSR                          ( 292 )        /* PDC Transfer Status Register */
/* -------- SSC_CR : (SSC Offset: 0x0) SSC Control Register -------- */
#تعریف_کرو AT91C_SSC_RXEN                    ( 0x1 << 0 )   /* (SSC) Receive Enable */
#تعریف_کرو AT91C_SSC_RXDIS                   ( 0x1 << 1 )   /* (SSC) Receive Disable */
#تعریف_کرو AT91C_SSC_TXEN                    ( 0x1 << 8 )   /* (SSC) Transmit Enable */
#تعریف_کرو AT91C_SSC_TXDIS                   ( 0x1 << 9 )   /* (SSC) Transmit Disable */
#تعریف_کرو AT91C_SSC_SWRST                   ( 0x1 << 15 )  /* (SSC) Software Reset */
/* -------- SSC_RCMR : (SSC Offset: 0x10) SSC Receive Clock Mode Register -------- */
#تعریف_کرو AT91C_SSC_CKS                     ( 0x3 << 0 )   /* (SSC) Receive/Transmit Clock Selection */
#تعریف_کرو     AT91C_SSC_CKS_DIV             ( 0x0 )        /* (SSC) Divided Clock */
#تعریف_کرو     AT91C_SSC_CKS_TK              ( 0x1 )        /* (SSC) TK Clock signal */
#تعریف_کرو     AT91C_SSC_CKS_RK              ( 0x2 )        /* (SSC) RK pin */
#تعریف_کرو AT91C_SSC_CKO                     ( 0x7 << 2 )   /* (SSC) Receive/Transmit Clock Output Mode Selection */
#تعریف_کرو     AT91C_SSC_CKO_NONE            ( 0x0 << 2 )   /* (SSC) Receive/Transmit Clock Output Mode: None RK pin: Input-only */
#تعریف_کرو     AT91C_SSC_CKO_CONTINUOUS      ( 0x1 << 2 )   /* (SSC) Continuous Receive/Transmit Clock RK pin: Output */
#تعریف_کرو     AT91_C_SSC_CKO_ڈیٹا_TX         ( 0x2 << 2 )   /* (SSC) Receive/Transmit Clock only during data transfers RK pin: Output */
#تعریف_کرو AT91C_SSC_CKI                     ( 0x1 << 5 )   /* (SSC) Receive/Transmit Clock Inversion */
#تعریف_کرو AT91C_SSC_CKG                     ( 0x3 << 6 )   /* (SSC) Receive/Transmit Clock Gating Selection */
#تعریف_کرو     AT91C_SSC_CKG_NONE            ( 0x0 << 6 )   /* (SSC) Receive/Transmit Clock Gating: None, continuous clock */
#تعریف_کرو     AT91_C_SSC_CKG_کم             ( 0x1 << 6 )   /* (SSC) Receive/Transmit Clock enabled only if RF Low */
#تعریف_کرو     AT91_C_SSC_CKG_بلند            ( 0x2 << 6 )   /* (SSC) Receive/Transmit Clock enabled only if RF High */
#تعریف_کرو AT91_C_SSC_آغاز                   ( 0xF << 8 )   /* (SSC) Receive/Transmit Start Selection */
#تعریف_کرو     AT91_C_SSC_آغاز_CONTINUOUS    ( 0x0 << 8 )   /* (SSC) Continuous, as soon as the receiver is enabled, and immediately after the end of transfer of the previous data. */
#تعریف_کرو     AT91_C_SSC_آغاز_TX            ( 0x1 << 8 )   /* (SSC) Transmit/Receive start */
#تعریف_کرو     AT91_C_SSC_آغاز_کم_RF        ( 0x2 << 8 )   /* (SSC) Detection of a low level on RF input */
#تعریف_کرو     AT91_C_SSC_آغاز_بلند_RF       ( 0x3 << 8 )   /* (SSC) Detection of a high level on RF input */
#تعریف_کرو     AT91_C_SSC_آغاز_FALL_RF       ( 0x4 << 8 )   /* (SSC) Detection of a falling edge on RF input */
#تعریف_کرو     AT91_C_SSC_آغاز_RISE_RF       ( 0x5 << 8 )   /* (SSC) Detection of a rising edge on RF input */
#تعریف_کرو     AT91_C_SSC_آغاز_LEVEL_RF      ( 0x6 << 8 )   /* (SSC) Detection of any level change on RF input */
#تعریف_کرو     AT91_C_SSC_آغاز_کنارہ_RF       ( 0x7 << 8 )   /* (SSC) Detection of any edge on RF input */
#تعریف_کرو     AT91_C_SSC_آغاز_0             ( 0x8 << 8 )   /* (SSC) Compare 0 */
#تعریف_کرو AT91C_SSC_STOP                    ( 0x1 << 12 )  /* (SSC) Receive Stop Selection */
#تعریف_کرو AT91C_SSC_STTOUT                  ( 0x1 << 15 )  /* (SSC) Receive/Transmit Start Output Selection */
#تعریف_کرو AT91C_SSC_STTDLY                  ( 0xFF << 16 ) /* (SSC) Receive/Transmit Start Delay */
#تعریف_کرو AT91C_SSC_PERIOD                  ( 0xFF << 24 ) /* (SSC) Receive/Transmit Period Divider Selection */
/* -------- SSC_RFMR : (SSC Offset: 0x14) SSC Receive Frame Mode Register -------- */
#تعریف_کرو AT91C_SSC_DATLEN                  ( 0x1F << 0 )  /* (SSC) Data Length */
#تعریف_کرو AT91C_SSC_LOOP                    ( 0x1 << 5 )   /* (SSC) Loop Mode */
#تعریف_کرو AT91C_SSC_MSBF                    ( 0x1 << 7 )   /* (SSC) Most Significant Bit First */
#تعریف_کرو AT91C_SSC_DATNB                   ( 0xF << 8 )   /* (SSC) Data Number per Frame */
#تعریف_کرو AT91C_SSC_FSLEN                   ( 0xF << 16 )  /* (SSC) Receive/Transmit Frame Sync length */
#تعریف_کرو AT91C_SSC_FSOS                    ( 0x7 << 20 )  /* (SSC) Receive/Transmit Frame Sync Output Selection */
#تعریف_کرو     AT91C_SSC_FSOS_NONE           ( 0x0 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: None RK pin Input-only */
#تعریف_کرو     AT91C_SSC_FSOS_NEGATIVE       ( 0x1 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Negative Pulse */
#تعریف_کرو     AT91_C_SSC_FSOS_مثبت       ( 0x2 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Positive Pulse */
#تعریف_کرو     AT91_C_SSC_FSOS_کم            ( 0x3 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Driver Low during data transfer */
#تعریف_کرو     AT91_C_SSC_FSOS_بلند           ( 0x4 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Driver High during data transfer */
#تعریف_کرو     AT91C_SSC_FSOS_TOGGLE         ( 0x5 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Toggling at each start of data transfer */
#تعریف_کرو AT91C_SSC_FSEDGE                  ( 0x1 << 24 )  /* (SSC) Frame Sync Edge Detection */
/* -------- SSC_TCMR : (SSC Offset: 0x18) SSC Transmit Clock Mode Register -------- */
/* -------- SSC_TFMR : (SSC Offset: 0x1c) SSC Transmit Frame Mode Register -------- */
#تعریف_کرو AT91C_SSC_DATDEF                  ( 0x1 << 5 )  /* (SSC) Data Default Value */
#تعریف_کرو AT91C_SSC_FSDEN                   ( 0x1 << 23 ) /* (SSC) Frame Sync Data Enable */
/* -------- SSC_SR : (SSC Offset: 0x40) SSC Status Register -------- */
#تعریف_کرو AT91C_SSC_TXRDY                   ( 0x1 << 0 )  /* (SSC) Transmit Ready */
#تعریف_کرو AT91C_SSC_TXEMPTY                 ( 0x1 << 1 )  /* (SSC) Transmit Empty */
#تعریف_کرو AT91C_SSC_ENDTX                   ( 0x1 << 2 )  /* (SSC) End Of Transmission */
#تعریف_کرو AT91C_SSC_TXBUFE                  ( 0x1 << 3 )  /* (SSC) Transmit Buffer Empty */
#تعریف_کرو AT91C_SSC_RXRDY                   ( 0x1 << 4 )  /* (SSC) Receive Ready */
#تعریف_کرو AT91C_SSC_OVRUN                   ( 0x1 << 5 )  /* (SSC) Receive Overrun */
#تعریف_کرو AT91C_SSC_ENDRX                   ( 0x1 << 6 )  /* (SSC) End of Reception */
#تعریف_کرو AT91C_SSC_RXBUFF                  ( 0x1 << 7 )  /* (SSC) Receive Buffer Full */
#تعریف_کرو AT91C_SSC_CP0                     ( 0x1 << 8 )  /* (SSC) Compare 0 */
#تعریف_کرو AT91C_SSC_CP1                     ( 0x1 << 9 )  /* (SSC) Compare 1 */
#تعریف_کرو AT91C_SSC_TXSYN                   ( 0x1 << 10 ) /* (SSC) Transmit Sync */
#تعریف_کرو AT91C_SSC_RXSYN                   ( 0x1 << 11 ) /* (SSC) Receive Sync */
#تعریف_کرو AT91C_SSC_TXENA                   ( 0x1 << 16 ) /* (SSC) Transmit Enable */
#تعریف_کرو AT91C_SSC_RXENA                   ( 0x1 << 17 ) /* (SSC) Receive Enable */
/* -------- SSC_IER : (SSC Offset: 0x44) SSC Interrupt Enable Register -------- */
/* -------- SSC_IDR : (SSC Offset: 0x48) SSC Interrupt Disable Register -------- */
/* -------- SSC_IMR : (SSC Offset: 0x4c) SSC Interrupt Mask Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Usart */
/* ***************************************************************************** */
/* *** Register offset in AT91S_USART structure *** */
#تعریف_کرو US_CR                            ( 0 )         /* Control Register */
#تعریف_کرو US_MR                            ( 4 )         /* Mode Register */
#تعریف_کرو US_IER                           ( 8 )         /* Interrupt Enable Register */
#تعریف_کرو US_IDR                           ( 12 )        /* Interrupt Disable Register */
#تعریف_کرو US_IMR                           ( 16 )        /* Interrupt Mask Register */
#تعریف_کرو US_CSR                           ( 20 )        /* Channel Status Register */
#تعریف_کرو US_RHR                           ( 24 )        /* Receiver Holding Register */
#تعریف_کرو US_THR                           ( 28 )        /* Transmitter Holding Register */
#تعریف_کرو US_BRGR                          ( 32 )        /* Baud Rate Generator Register */
#تعریف_کرو US_RTOR                          ( 36 )        /* Receiver Time-out Register */
#تعریف_کرو US_TTGR                          ( 40 )        /* Transmitter Time-guard Register */
#تعریف_کرو US_FIDI                          ( 64 )        /* FI_DI_Ratio Register */
#تعریف_کرو US_NER                           ( 68 )        /* Nb Errors Register */
#تعریف_کرو US_XXR                           ( 72 )        /* XON_XOFF Register */
#تعریف_کرو US_IF                            ( 76 )        /* IRDA_FILTER Register */
#تعریف_کرو US_RPR                           ( 256 )       /* Receive Pointer Register */
#تعریف_کرو US_RCR                           ( 260 )       /* Receive Counter Register */
#تعریف_کرو US_TPR                           ( 264 )       /* Transmit Pointer Register */
#تعریف_کرو US_TCR                           ( 268 )       /* Transmit Counter Register */
#تعریف_کرو US_RNPR                          ( 272 )       /* Receive Next Pointer Register */
#تعریف_کرو US_RNCR                          ( 276 )       /* Receive Next Counter Register */
#تعریف_کرو US_TNPR                          ( 280 )       /* Transmit Next Pointer Register */
#تعریف_کرو US_TNCR                          ( 284 )       /* Transmit Next Counter Register */
#تعریف_کرو US_PTCR                          ( 288 )       /* PDC Transfer Control Register */
#تعریف_کرو US_PTSR                          ( 292 )       /* PDC Transfer Status Register */
/* -------- US_CR : (USART Offset: 0x0) Debug Unit Control Register -------- */
#تعریف_کرو AT91C_US_RSTSTA                  ( 0x1 << 8 )  /* (USART) Reset Status Bits */
#تعریف_کرو AT91C_US_STTBRK                  ( 0x1 << 9 )  /* (USART) Start Break */
#تعریف_کرو AT91C_US_STPBRK                  ( 0x1 << 10 ) /* (USART) Stop Break */
#تعریف_کرو AT91C_US_STTTO                   ( 0x1 << 11 ) /* (USART) Start Time-out */
#تعریف_کرو AT91C_US_SENDA                   ( 0x1 << 12 ) /* (USART) Send Address */
#تعریف_کرو AT91C_US_RSTIT                   ( 0x1 << 13 ) /* (USART) Reset Iterations */
#تعریف_کرو AT91C_US_RSTNACK                 ( 0x1 << 14 ) /* (USART) Reset Non Acknowledge */
#تعریف_کرو AT91C_US_RETTO                   ( 0x1 << 15 ) /* (USART) Rearm Time-out */
#تعریف_کرو AT91C_US_DTREN                   ( 0x1 << 16 ) /* (USART) Data Terminal ready Enable */
#تعریف_کرو AT91C_US_DTRDIS                  ( 0x1 << 17 ) /* (USART) Data Terminal ready Disable */
#تعریف_کرو AT91C_US_RTSEN                   ( 0x1 << 18 ) /* (USART) Request to Send enable */
#تعریف_کرو AT91C_US_RTSDIS                  ( 0x1 << 19 ) /* (USART) Request to Send Disable */
/* -------- US_MR : (USART Offset: 0x4) Debug Unit Mode Register -------- */
#تعریف_کرو AT91C_US_USMODE                  ( 0xF << 0 )  /* (USART) Usart mode */
#تعریف_کرو     AT91_C_US_USMODE_معمول       ( 0x0 )       /* (USART) Normal */
#تعریف_کرو     AT91C_US_USMODE_RS485        ( 0x1 )       /* (USART) RS485 */
#تعریف_کرو     AT91C_US_USMODE_HWHSH        ( 0x2 )       /* (USART) Hardware Handshaking */
#تعریف_کرو     AT91C_US_USMODE_MODEM        ( 0x3 )       /* (USART) Modem */
#تعریف_کرو     AT91C_US_USMODE_ISO7816_0    ( 0x4 )       /* (USART) ISO7816 protocol: T = 0 */
#تعریف_کرو     AT91C_US_USMODE_ISO7816_1    ( 0x6 )       /* (USART) ISO7816 protocol: T = 1 */
#تعریف_کرو     AT91C_US_USMODE_IRDA         ( 0x8 )       /* (USART) IrDA */
#تعریف_کرو     AT91C_US_USMODE_SWHSH        ( 0xC )       /* (USART) Software Handshaking */
#تعریف_کرو AT91C_US_CLKS                    ( 0x3 << 4 )  /* (USART) Clock Selection (Baud Rate generator Input Clock */
#تعریف_کرو     AT91C_US_CLKS_CLOCK          ( 0x0 << 4 )  /* (USART) Clock */
#تعریف_کرو     AT91C_US_CLKS_FDIV1          ( 0x1 << 4 )  /* (USART) fdiv1 */
#تعریف_کرو     AT91C_US_CLKS_SLOW           ( 0x2 << 4 )  /* (USART) slow_clock (ARM) */
#تعریف_کرو     AT91C_US_CLKS_EXT            ( 0x3 << 4 )  /* (USART) External (SCK) */
#تعریف_کرو AT91C_US_CHRL                    ( 0x3 << 6 )  /* (USART) Clock Selection (Baud Rate generator Input Clock */
#تعریف_کرو     AT91_C_US_CHRL_5_بٹ         ( 0x0 << 6 )  /* (USART) Character Length: 5 bits */
#تعریف_کرو     AT91_C_US_CHRL_6_بٹ         ( 0x1 << 6 )  /* (USART) Character Length: 6 bits */
#تعریف_کرو     AT91_C_US_CHRL_7_بٹ         ( 0x2 << 6 )  /* (USART) Character Length: 7 bits */
#تعریف_کرو     AT91_C_US_CHRL_8_بٹ         ( 0x3 << 6 )  /* (USART) Character Length: 8 bits */
#تعریف_کرو AT91C_US_SYNC                    ( 0x1 << 8 )  /* (USART) Synchronous Mode Select */
#تعریف_کرو AT91C_US_NBSTOP                  ( 0x3 << 12 ) /* (USART) Number of Stop bits */
#تعریف_کرو     AT91_C_US_NBSTOP_1_ثنائی_ہندسہ        ( 0x0 << 12 ) /* (USART) 1 stop bit */
#تعریف_کرو     AT91_C_US_NBSTOP_15_ثنائی_ہندسہ       ( 0x1 << 12 ) /* (USART) Asynchronous (SYNC=0) 2 stop bits Synchronous (SYNC=1) 2 stop bits */
#تعریف_کرو     AT91_C_US_NBSTOP_2_ثنائی_ہندسہ        ( 0x2 << 12 ) /* (USART) 2 stop bits */
#تعریف_کرو AT91C_US_MSBF                    ( 0x1 << 16 ) /* (USART) Bit Order */
#تعریف_کرو AT91C_US_MODE9                   ( 0x1 << 17 ) /* (USART) 9-bit Character length */
#تعریف_کرو AT91C_US_CKLO                    ( 0x1 << 18 ) /* (USART) Clock Output Select */
#تعریف_کرو AT91C_US_OVER                    ( 0x1 << 19 ) /* (USART) Over Sampling Mode */
#تعریف_کرو AT91C_US_INACK                   ( 0x1 << 20 ) /* (USART) Inhibit Non Acknowledge */
#تعریف_کرو AT91C_US_DSNACK                  ( 0x1 << 21 ) /* (USART) Disable Successive NACK */
#تعریف_کرو AT91C_US_MAX_ITER                ( 0x1 << 24 ) /* (USART) Number of Repetitions */
#تعریف_کرو AT91C_US_FILTER                  ( 0x1 << 28 ) /* (USART) Receive Line Filter */
/* -------- US_IER : (USART Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
#تعریف_کرو AT91C_US_RXBRK                   ( 0x1 << 2 )  /* (USART) Break Received/End of Break */
#تعریف_کرو AT91C_US_TIMEOUT                 ( 0x1 << 8 )  /* (USART) Receiver Time-out */
#تعریف_کرو AT91C_US_ITERATION               ( 0x1 << 10 ) /* (USART) Max number of Repetitions Reached */
#تعریف_کرو AT91C_US_NACK                    ( 0x1 << 13 ) /* (USART) Non Acknowledge */
#تعریف_کرو AT91C_US_RIIC                    ( 0x1 << 16 ) /* (USART) Ring INdicator Input Change Flag */
#تعریف_کرو AT91C_US_DSRIC                   ( 0x1 << 17 ) /* (USART) Data Set Ready Input Change Flag */
#تعریف_کرو AT91C_US_DCDIC                   ( 0x1 << 18 ) /* (USART) Data Carrier Flag */
#تعریف_کرو AT91C_US_CTSIC                   ( 0x1 << 19 ) /* (USART) Clear To Send Input Change Flag */
/* -------- US_IDR : (USART Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* -------- US_IMR : (USART Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* -------- US_CSR : (USART Offset: 0x14) Debug Unit Channel Status Register -------- */
#تعریف_کرو AT91C_US_RI     ( 0x1 << 20 )         /* (USART) Image of RI Input */
#تعریف_کرو AT91C_US_DSR    ( 0x1 << 21 )         /* (USART) Image of DSR Input */
#تعریف_کرو AT91C_US_DCD    ( 0x1 << 22 )         /* (USART) Image of DCD Input */
#تعریف_کرو AT91C_US_CTS    ( 0x1 << 23 )         /* (USART) Image of CTS Input */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Two-wire Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_TWI structure *** */
#تعریف_کرو TWI_CR                         ( 0 )          /* Control Register */
#تعریف_کرو TWI_MMR                        ( 4 )          /* Master Mode Register */
#تعریف_کرو TWI_SMR                        ( 8 )          /* Slave Mode Register */
#تعریف_کرو TWI_IADR                       ( 12 )         /* Internal Address Register */
#تعریف_کرو TWI_CWGR                       ( 16 )         /* Clock Waveform Generator Register */
#تعریف_کرو TWI_SR                         ( 32 )         /* Status Register */
#تعریف_کرو TWI_IER                        ( 36 )         /* Interrupt Enable Register */
#تعریف_کرو TWI_IDR                        ( 40 )         /* Interrupt Disable Register */
#تعریف_کرو TWI_IMR                        ( 44 )         /* Interrupt Mask Register */
#تعریف_کرو TWI_RHR                        ( 48 )         /* Receive Holding Register */
#تعریف_کرو TWI_THR                        ( 52 )         /* Transmit Holding Register */
/* -------- TWI_CR : (TWI Offset: 0x0) TWI Control Register -------- */
#تعریف_کرو AT91_C_TWI_آغاز                ( 0x1 << 0 )   /* (TWI) Send a START Condition */
#تعریف_کرو AT91C_TWI_STOP                 ( 0x1 << 1 )   /* (TWI) Send a STOP Condition */
#تعریف_کرو AT91C_TWI_MSEN                 ( 0x1 << 2 )   /* (TWI) TWI Master Transfer Enabled */
#تعریف_کرو AT91C_TWI_MSDIS                ( 0x1 << 3 )   /* (TWI) TWI Master Transfer Disabled */
#تعریف_کرو AT91C_TWI_SVEN                 ( 0x1 << 4 )   /* (TWI) TWI Slave Transfer Enabled */
#تعریف_کرو AT91C_TWI_SVDIS                ( 0x1 << 5 )   /* (TWI) TWI Slave Transfer Disabled */
#تعریف_کرو AT91C_TWI_SWRST                ( 0x1 << 7 )   /* (TWI) Software Reset */
/* -------- TWI_MMR : (TWI Offset: 0x4) TWI Master Mode Register -------- */
#تعریف_کرو AT91C_TWI_IADRSZ               ( 0x3 << 8 )   /* (TWI) Internal Device Address Size */
#تعریف_کرو     AT91C_TWI_IADRSZ_NO        ( 0x0 << 8 )   /* (TWI) No internal device address */
#تعریف_کرو     AT91C_TWI_IADRSZ_1_BYTE    ( 0x1 << 8 )   /* (TWI) One-byte internal device address */
#تعریف_کرو     AT91C_TWI_IADRSZ_2_BYTE    ( 0x2 << 8 )   /* (TWI) Two-byte internal device address */
#تعریف_کرو     AT91C_TWI_IADRSZ_3_BYTE    ( 0x3 << 8 )   /* (TWI) Three-byte internal device address */
#تعریف_کرو AT91C_TWI_MREAD                ( 0x1 << 12 )  /* (TWI) Master Read Direction */
#تعریف_کرو AT91C_TWI_DADR                 ( 0x7F << 16 ) /* (TWI) Device Address */
/* -------- TWI_SMR : (TWI Offset: 0x8) TWI Slave Mode Register -------- */
#تعریف_کرو AT91C_TWI_SADR                 ( 0x7F << 16 ) /* (TWI) Slave Device Address */
/* -------- TWI_CWGR : (TWI Offset: 0x10) TWI Clock Waveform Generator Register -------- */
#تعریف_کرو AT91C_TWI_CLDIV                ( 0xFF << 0 )  /* (TWI) Clock Low Divider */
#تعریف_کرو AT91C_TWI_CHDIV                ( 0xFF << 8 )  /* (TWI) Clock High Divider */
#تعریف_کرو AT91C_TWI_CKDIV                ( 0x7 << 16 )  /* (TWI) Clock Divider */
/* -------- TWI_SR : (TWI Offset: 0x20) TWI Status Register -------- */
#تعریف_کرو AT91C_TWI_TXCOMP               ( 0x1 << 0 )   /* (TWI) Transmission Completed */
#تعریف_کرو AT91C_TWI_RXRDY                ( 0x1 << 1 )   /* (TWI) Receive holding register ReaDY */
#تعریف_کرو AT91C_TWI_TXRDY                ( 0x1 << 2 )   /* (TWI) Transmit holding register ReaDY */
#تعریف_کرو AT91C_TWI_SVREAD               ( 0x1 << 3 )   /* (TWI) Slave Read */
#تعریف_کرو AT91C_TWI_SVACC                ( 0x1 << 4 )   /* (TWI) Slave Access */
#تعریف_کرو AT91C_TWI_GCACC                ( 0x1 << 5 )   /* (TWI) General Call Access */
#تعریف_کرو AT91C_TWI_OVRE                 ( 0x1 << 6 )   /* (TWI) Overrun Error */
#تعریف_کرو AT91C_TWI_UNRE                 ( 0x1 << 7 )   /* (TWI) Underrun Error */
#تعریف_کرو AT91C_TWI_NACK                 ( 0x1 << 8 )   /* (TWI) Not Acknowledged */
#تعریف_کرو AT91C_TWI_ARBLST               ( 0x1 << 9 )   /* (TWI) Arbitration Lost */
/* -------- TWI_IER : (TWI Offset: 0x24) TWI Interrupt Enable Register -------- */
/* -------- TWI_IDR : (TWI Offset: 0x28) TWI Interrupt Disable Register -------- */
/* -------- TWI_IMR : (TWI Offset: 0x2c) TWI Interrupt Mask Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Timer Counter Channel Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_TC structure *** */
#تعریف_کرو TC_CCR                                ( 0 )         /* Channel Control Register */
#تعریف_کرو TC_CMR                                ( 4 )         /* Channel Mode Register (Capture Mode / Waveform Mode) */
#تعریف_کرو TC_CV                                 ( 16 )        /* Counter Value */
#تعریف_کرو TC_RA                                 ( 20 )        /* Register A */
#تعریف_کرو TC_RB                                 ( 24 )        /* Register B */
#تعریف_کرو TC_RC                                 ( 28 )        /* Register C */
#تعریف_کرو TC_SR                                 ( 32 )        /* Status Register */
#تعریف_کرو TC_IER                                ( 36 )        /* Interrupt Enable Register */
#تعریف_کرو TC_IDR                                ( 40 )        /* Interrupt Disable Register */
#تعریف_کرو TC_IMR                                ( 44 )        /* Interrupt Mask Register */
/* -------- TC_CCR : (TC Offset: 0x0) TC Channel Control Register -------- */
#تعریف_کرو AT91C_TC_CLKEN                        ( 0x1 << 0 )  /* (TC) Counter Clock Enable Command */
#تعریف_کرو AT91C_TC_CLKDIS                       ( 0x1 << 1 )  /* (TC) Counter Clock Disable Command */
#تعریف_کرو AT91C_TC_SWTRG                        ( 0x1 << 2 )  /* (TC) Software Trigger Command */
/* -------- TC_CMR : (TC Offset: 0x4) TC Channel Mode Register: Capture Mode / Waveform Mode -------- */
#تعریف_کرو AT91C_TC_CLKS                         ( 0x7 << 0 )  /* (TC) Clock Selection */
#تعریف_کرو     AT91C_TC_CLKS_TIMER_DIV1_CLOCK    ( 0x0 )       /* (TC) Clock selected: TIMER_DIV1_CLOCK */
#تعریف_کرو     AT91C_TC_CLKS_TIMER_DIV2_CLOCK    ( 0x1 )       /* (TC) Clock selected: TIMER_DIV2_CLOCK */
#تعریف_کرو     AT91C_TC_CLKS_TIMER_DIV3_CLOCK    ( 0x2 )       /* (TC) Clock selected: TIMER_DIV3_CLOCK */
#تعریف_کرو     AT91C_TC_CLKS_TIMER_DIV4_CLOCK    ( 0x3 )       /* (TC) Clock selected: TIMER_DIV4_CLOCK */
#تعریف_کرو     AT91C_TC_CLKS_TIMER_DIV5_CLOCK    ( 0x4 )       /* (TC) Clock selected: TIMER_DIV5_CLOCK */
#تعریف_کرو     AT91C_TC_CLKS_XC0                 ( 0x5 )       /* (TC) Clock selected: XC0 */
#تعریف_کرو     AT91C_TC_CLKS_XC1                 ( 0x6 )       /* (TC) Clock selected: XC1 */
#تعریف_کرو     AT91C_TC_CLKS_XC2                 ( 0x7 )       /* (TC) Clock selected: XC2 */
#تعریف_کرو AT91C_TC_CLKI                         ( 0x1 << 3 )  /* (TC) Clock Invert */
#تعریف_کرو AT91_C_TC_مدت                        ( 0x3 << 4 )  /* (TC) Burst Signal Selection */
#تعریف_کرو     AT91_C_TC_مدت_NONE               ( 0x0 << 4 )  /* (TC) The clock is not gated by an external signal */
#تعریف_کرو     AT91_C_TC_مدت_XC0                ( 0x1 << 4 )  /* (TC) XC0 is ANDed with the selected clock */
#تعریف_کرو     AT91_C_TC_مدت_XC1                ( 0x2 << 4 )  /* (TC) XC1 is ANDed with the selected clock */
#تعریف_کرو     AT91_C_TC_مدت_XC2                ( 0x3 << 4 )  /* (TC) XC2 is ANDed with the selected clock */
#تعریف_کرو AT91C_TC_CPCSTOP                      ( 0x1 << 6 )  /* (TC) Counter Clock Stopped with RC Compare */
#تعریف_کرو AT91C_TC_LDBSTOP                      ( 0x1 << 6 )  /* (TC) Counter Clock Stopped with RB Loading */
#تعریف_کرو AT91C_TC_LDBDIS                       ( 0x1 << 7 )  /* (TC) Counter Clock Disabled with RB Loading */
#تعریف_کرو AT91C_TC_CPCDIS                       ( 0x1 << 7 )  /* (TC) Counter Clock Disable with RC Compare */
#تعریف_کرو AT91C_TC_ETRGEDG                      ( 0x3 << 8 )  /* (TC) External Trigger Edge Selection */
#تعریف_کرو     AT91C_TC_ETRGEDG_NONE             ( 0x0 << 8 )  /* (TC) Edge: None */
#تعریف_کرو     AT91C_TC_ETRGEDG_RISING           ( 0x1 << 8 )  /* (TC) Edge: rising edge */
#تعریف_کرو     AT91C_TC_ETRGEDG_FALLING          ( 0x2 << 8 )  /* (TC) Edge: falling edge */
#تعریف_کرو     AT91C_TC_ETRGEDG_BOTH             ( 0x3 << 8 )  /* (TC) Edge: each edge */
#تعریف_کرو AT91C_TC_EEVTEDG                      ( 0x3 << 8 )  /* (TC) External Event Edge Selection */
#تعریف_کرو     AT91C_TC_EEVTEDG_NONE             ( 0x0 << 8 )  /* (TC) Edge: None */
#تعریف_کرو     AT91C_TC_EEVTEDG_RISING           ( 0x1 << 8 )  /* (TC) Edge: rising edge */
#تعریف_کرو     AT91C_TC_EEVTEDG_FALLING          ( 0x2 << 8 )  /* (TC) Edge: falling edge */
#تعریف_کرو     AT91C_TC_EEVTEDG_BOTH             ( 0x3 << 8 )  /* (TC) Edge: each edge */
#تعریف_کرو AT91C_TC_ABETRG                       ( 0x1 << 10 ) /* (TC) TIOA or TIOB External Trigger Selection */
#تعریف_کرو AT91C_TC_EEVT                         ( 0x3 << 10 ) /* (TC) External Event  Selection */
#تعریف_کرو     AT91C_TC_EEVT_NONE                ( 0x0 << 10 ) /* (TC) Signal selected as external event: TIOB TIOB direction: input */
#تعریف_کرو     AT91C_TC_EEVT_RISING              ( 0x1 << 10 ) /* (TC) Signal selected as external event: XC0 TIOB direction: output */
#تعریف_کرو     AT91C_TC_EEVT_FALLING             ( 0x2 << 10 ) /* (TC) Signal selected as external event: XC1 TIOB direction: output */
#تعریف_کرو     AT91C_TC_EEVT_BOTH                ( 0x3 << 10 ) /* (TC) Signal selected as external event: XC2 TIOB direction: output */
#تعریف_کرو AT91C_TC_ENETRG                       ( 0x1 << 12 ) /* (TC) External Event Trigger enable */
#تعریف_کرو AT91C_TC_WAVESEL                      ( 0x3 << 13 ) /* (TC) Waveform  Selection */
#تعریف_کرو     AT91_C_TC_WAVESEL_اوپر               ( 0x0 << 13 ) /* (TC) UP mode without atomatic trigger on RC Compare */
#تعریف_کرو     AT91C_TC_WAVESEL_UPDOWN           ( 0x1 << 13 ) /* (TC) UPDOWN mode without automatic trigger on RC Compare */
#تعریف_کرو     AT91_C_TC_WAVESEL_اوپر_AUTO          ( 0x2 << 13 ) /* (TC) UP mode with automatic trigger on RC Compare */
#تعریف_کرو     AT91C_TC_WAVESEL_UPDOWN_AUTO      ( 0x3 << 13 ) /* (TC) UPDOWN mode with automatic trigger on RC Compare */
#تعریف_کرو AT91C_TC_CPCTRG                       ( 0x1 << 14 ) /* (TC) RC Compare Trigger Enable */
#تعریف_کرو AT91C_TC_WAVE                         ( 0x1 << 15 ) /* (TC) */
#تعریف_کرو AT91C_TC_LDRA                         ( 0x3 << 16 ) /* (TC) RA Loading Selection */
#تعریف_کرو     AT91C_TC_LDRA_NONE                ( 0x0 << 16 ) /* (TC) Edge: None */
#تعریف_کرو     AT91C_TC_LDRA_RISING              ( 0x1 << 16 ) /* (TC) Edge: rising edge of TIOA */
#تعریف_کرو     AT91C_TC_LDRA_FALLING             ( 0x2 << 16 ) /* (TC) Edge: falling edge of TIOA */
#تعریف_کرو     AT91C_TC_LDRA_BOTH                ( 0x3 << 16 ) /* (TC) Edge: each edge of TIOA */
#تعریف_کرو AT91C_TC_ACPA                         ( 0x3 << 16 ) /* (TC) RA Compare Effect on TIOA */
#تعریف_کرو     AT91C_TC_ACPA_NONE                ( 0x0 << 16 ) /* (TC) Effect: none */
#تعریف_کرو     AT91_C_TC_ACPA_سیٹ                 ( 0x1 << 16 ) /* (TC) Effect: set */
#تعریف_کرو     AT91C_TC_ACPA_CLEAR               ( 0x2 << 16 ) /* (TC) Effect: clear */
#تعریف_کرو     AT91C_TC_ACPA_TOGGLE              ( 0x3 << 16 ) /* (TC) Effect: toggle */
#تعریف_کرو AT91C_TC_LDRB                         ( 0x3 << 18 ) /* (TC) RB Loading Selection */
#تعریف_کرو     AT91C_TC_LDRB_NONE                ( 0x0 << 18 ) /* (TC) Edge: None */
#تعریف_کرو     AT91C_TC_LDRB_RISING              ( 0x1 << 18 ) /* (TC) Edge: rising edge of TIOA */
#تعریف_کرو     AT91C_TC_LDRB_FALLING             ( 0x2 << 18 ) /* (TC) Edge: falling edge of TIOA */
#تعریف_کرو     AT91C_TC_LDRB_BOTH                ( 0x3 << 18 ) /* (TC) Edge: each edge of TIOA */
#تعریف_کرو AT91C_TC_ACPC                         ( 0x3 << 18 ) /* (TC) RC Compare Effect on TIOA */
#تعریف_کرو     AT91C_TC_ACPC_NONE                ( 0x0 << 18 ) /* (TC) Effect: none */
#تعریف_کرو     AT91_C_TC_ACPC_سیٹ                 ( 0x1 << 18 ) /* (TC) Effect: set */
#تعریف_کرو     AT91C_TC_ACPC_CLEAR               ( 0x2 << 18 ) /* (TC) Effect: clear */
#تعریف_کرو     AT91C_TC_ACPC_TOGGLE              ( 0x3 << 18 ) /* (TC) Effect: toggle */
#تعریف_کرو AT91C_TC_AEEVT                        ( 0x3 << 20 ) /* (TC) External Event Effect on TIOA */
#تعریف_کرو     AT91C_TC_AEEVT_NONE               ( 0x0 << 20 ) /* (TC) Effect: none */
#تعریف_کرو     AT91_C_TC_AEEVT_سیٹ                ( 0x1 << 20 ) /* (TC) Effect: set */
#تعریف_کرو     AT91C_TC_AEEVT_CLEAR              ( 0x2 << 20 ) /* (TC) Effect: clear */
#تعریف_کرو     AT91C_TC_AEEVT_TOGGLE             ( 0x3 << 20 ) /* (TC) Effect: toggle */
#تعریف_کرو AT91C_TC_ASWTRG                       ( 0x3 << 22 ) /* (TC) Software Trigger Effect on TIOA */
#تعریف_کرو     AT91C_TC_ASWTRG_NONE              ( 0x0 << 22 ) /* (TC) Effect: none */
#تعریف_کرو     AT91_C_TC_ASWTRG_سیٹ               ( 0x1 << 22 ) /* (TC) Effect: set */
#تعریف_کرو     AT91C_TC_ASWTRG_CLEAR             ( 0x2 << 22 ) /* (TC) Effect: clear */
#تعریف_کرو     AT91C_TC_ASWTRG_TOGGLE            ( 0x3 << 22 ) /* (TC) Effect: toggle */
#تعریف_کرو AT91C_TC_BCPB                         ( 0x3 << 24 ) /* (TC) RB Compare Effect on TIOB */
#تعریف_کرو     AT91C_TC_BCPB_NONE                ( 0x0 << 24 ) /* (TC) Effect: none */
#تعریف_کرو     AT91_C_TC_BCPB_سیٹ                 ( 0x1 << 24 ) /* (TC) Effect: set */
#تعریف_کرو     AT91C_TC_BCPB_CLEAR               ( 0x2 << 24 ) /* (TC) Effect: clear */
#تعریف_کرو     AT91C_TC_BCPB_TOGGLE              ( 0x3 << 24 ) /* (TC) Effect: toggle */
#تعریف_کرو AT91C_TC_BCPC                         ( 0x3 << 26 ) /* (TC) RC Compare Effect on TIOB */
#تعریف_کرو     AT91C_TC_BCPC_NONE                ( 0x0 << 26 ) /* (TC) Effect: none */
#تعریف_کرو     AT91_C_TC_BCPC_سیٹ                 ( 0x1 << 26 ) /* (TC) Effect: set */
#تعریف_کرو     AT91C_TC_BCPC_CLEAR               ( 0x2 << 26 ) /* (TC) Effect: clear */
#تعریف_کرو     AT91C_TC_BCPC_TOGGLE              ( 0x3 << 26 ) /* (TC) Effect: toggle */
#تعریف_کرو AT91C_TC_BEEVT                        ( 0x3 << 28 ) /* (TC) External Event Effect on TIOB */
#تعریف_کرو     AT91C_TC_BEEVT_NONE               ( 0x0 << 28 ) /* (TC) Effect: none */
#تعریف_کرو     AT91_C_TC_BEEVT_سیٹ                ( 0x1 << 28 ) /* (TC) Effect: set */
#تعریف_کرو     AT91C_TC_BEEVT_CLEAR              ( 0x2 << 28 ) /* (TC) Effect: clear */
#تعریف_کرو     AT91C_TC_BEEVT_TOGGLE             ( 0x3 << 28 ) /* (TC) Effect: toggle */
#تعریف_کرو AT91C_TC_BSWTRG                       ( 0x3 << 30 ) /* (TC) Software Trigger Effect on TIOB */
#تعریف_کرو     AT91C_TC_BSWTRG_NONE              ( 0x0 << 30 ) /* (TC) Effect: none */
#تعریف_کرو     AT91_C_TC_BSWTRG_سیٹ               ( 0x1 << 30 ) /* (TC) Effect: set */
#تعریف_کرو     AT91C_TC_BSWTRG_CLEAR             ( 0x2 << 30 ) /* (TC) Effect: clear */
#تعریف_کرو     AT91C_TC_BSWTRG_TOGGLE            ( 0x3 << 30 ) /* (TC) Effect: toggle */
/* -------- TC_SR : (TC Offset: 0x20) TC Channel Status Register -------- */
#تعریف_کرو AT91C_TC_COVFS                        ( 0x1 << 0 )  /* (TC) Counter Overflow */
#تعریف_کرو AT91C_TC_LOVRS                        ( 0x1 << 1 )  /* (TC) Load Overrun */
#تعریف_کرو AT91C_TC_CPAS                         ( 0x1 << 2 )  /* (TC) RA Compare */
#تعریف_کرو AT91C_TC_CPBS                         ( 0x1 << 3 )  /* (TC) RB Compare */
#تعریف_کرو AT91C_TC_CPCS                         ( 0x1 << 4 )  /* (TC) RC Compare */
#تعریف_کرو AT91C_TC_LDRAS                        ( 0x1 << 5 )  /* (TC) RA Loading */
#تعریف_کرو AT91C_TC_LDRBS                        ( 0x1 << 6 )  /* (TC) RB Loading */
#تعریف_کرو AT91C_TC_ETRCS                        ( 0x1 << 7 )  /* (TC) External Trigger */
#تعریف_کرو AT91C_TC_ETRGS                        ( 0x1 << 16 ) /* (TC) Clock Enabling */
#تعریف_کرو AT91C_TC_MTIOA                        ( 0x1 << 17 ) /* (TC) TIOA Mirror */
#تعریف_کرو AT91C_TC_MTIOB                        ( 0x1 << 18 ) /* (TC) TIOA Mirror */
/* -------- TC_IER : (TC Offset: 0x24) TC Channel Interrupt Enable Register -------- */
/* -------- TC_IDR : (TC Offset: 0x28) TC Channel Interrupt Disable Register -------- */
/* -------- TC_IMR : (TC Offset: 0x2c) TC Channel Interrupt Mask Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Timer Counter Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_TCB structure *** */
#تعریف_کرو TCB_TC0                        ( 0 )        /* TC Channel 0 */
#تعریف_کرو TCB_TC1                        ( 64 )       /* TC Channel 1 */
#تعریف_کرو TCB_TC2                        ( 128 )      /* TC Channel 2 */
#تعریف_کرو TCB_BCR                        ( 192 )      /* TC Block Control Register */
#تعریف_کرو TCB_BMR                        ( 196 )      /* TC Block Mode Register */
/* -------- TCB_BCR : (TCB Offset: 0xc0) TC Block Control Register -------- */
#تعریف_کرو AT91C_TCB_SYNC                 ( 0x1 << 0 ) /* (TCB) Synchro Command */
/* -------- TCB_BMR : (TCB Offset: 0xc4) TC Block Mode Register -------- */
#تعریف_کرو AT91C_TCB_TC0XC0S              ( 0x1 << 0 ) /* (TCB) External Clock Signal 0 Selection */
#تعریف_کرو     AT91C_TCB_TC0XC0S_TCLK0    ( 0x0 )      /* (TCB) TCLK0 connected to XC0 */
#تعریف_کرو     AT91C_TCB_TC0XC0S_NONE     ( 0x1 )      /* (TCB) None signal connected to XC0 */
#تعریف_کرو     AT91C_TCB_TC0XC0S_TIOA1    ( 0x2 )      /* (TCB) TIOA1 connected to XC0 */
#تعریف_کرو     AT91C_TCB_TC0XC0S_TIOA2    ( 0x3 )      /* (TCB) TIOA2 connected to XC0 */
#تعریف_کرو AT91C_TCB_TC1XC1S              ( 0x1 << 2 ) /* (TCB) External Clock Signal 1 Selection */
#تعریف_کرو     AT91C_TCB_TC1XC1S_TCLK1    ( 0x0 << 2 ) /* (TCB) TCLK1 connected to XC1 */
#تعریف_کرو     AT91C_TCB_TC1XC1S_NONE     ( 0x1 << 2 ) /* (TCB) None signal connected to XC1 */
#تعریف_کرو     AT91C_TCB_TC1XC1S_TIOA0    ( 0x2 << 2 ) /* (TCB) TIOA0 connected to XC1 */
#تعریف_کرو     AT91C_TCB_TC1XC1S_TIOA2    ( 0x3 << 2 ) /* (TCB) TIOA2 connected to XC1 */
#تعریف_کرو AT91C_TCB_TC2XC2S              ( 0x1 << 4 ) /* (TCB) External Clock Signal 2 Selection */
#تعریف_کرو     AT91C_TCB_TC2XC2S_TCLK2    ( 0x0 << 4 ) /* (TCB) TCLK2 connected to XC2 */
#تعریف_کرو     AT91C_TCB_TC2XC2S_NONE     ( 0x1 << 4 ) /* (TCB) None signal connected to XC2 */
#تعریف_کرو     AT91C_TCB_TC2XC2S_TIOA0    ( 0x2 << 4 ) /* (TCB) TIOA0 connected to XC2 */
#تعریف_کرو     AT91C_TCB_TC2XC2S_TIOA2    ( 0x3 << 4 ) /* (TCB) TIOA2 connected to XC2 */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR PWMC Channel Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_PWMC_CH structure *** */
#تعریف_کرو PWMC_CMR                    ( 0 )         /* Channel Mode Register */
#تعریف_کرو PWMC_CDTYR                  ( 4 )         /* Channel Duty Cycle Register */
#تعریف_کرو PWMC_CPRDR                  ( 8 )         /* Channel Period Register */
#تعریف_کرو PWMC_CCNTR                  ( 12 )        /* Channel Counter Register */
#تعریف_کرو PWMC_CUPDR                  ( 16 )        /* Channel Update Register */
#تعریف_کرو PWMC_Reserved               ( 20 )        /* Reserved */
/* -------- PWMC_CMR : (PWMC_CH Offset: 0x0) PWMC Channel Mode Register -------- */
#تعریف_کرو AT91C_PWMC_CPRE             ( 0xF << 0 )  /* (PWMC_CH) Channel Pre-scaler : PWMC_CLKx */
#تعریف_کرو     AT91C_PWMC_CPRE_MCK     ( 0x0 )       /* (PWMC_CH) */
#تعریف_کرو     AT91C_PWMC_CPRE_MCKA    ( 0xB )       /* (PWMC_CH) */
#تعریف_کرو     AT91C_PWMC_CPRE_MCKB    ( 0xC )       /* (PWMC_CH) */
#تعریف_کرو AT91C_PWMC_CALG             ( 0x1 << 8 )  /* (PWMC_CH) Channel Alignment */
#تعریف_کرو AT91C_PWMC_CPOL             ( 0x1 << 9 )  /* (PWMC_CH) Channel Polarity */
#تعریف_کرو AT91C_PWMC_CPD              ( 0x1 << 10 ) /* (PWMC_CH) Channel Update Period */
/* -------- PWMC_CDTYR : (PWMC_CH Offset: 0x4) PWMC Channel Duty Cycle Register -------- */
#تعریف_کرو AT91C_PWMC_CDTY             ( 0x0 << 0 )  /* (PWMC_CH) Channel Duty Cycle */
/* -------- PWMC_CPRDR : (PWMC_CH Offset: 0x8) PWMC Channel Period Register -------- */
#تعریف_کرو AT91C_PWMC_CPRD             ( 0x0 << 0 )  /* (PWMC_CH) Channel Period */
/* -------- PWMC_CCNTR : (PWMC_CH Offset: 0xc) PWMC Channel Counter Register -------- */
#تعریف_کرو AT91C_PWMC_CCNT             ( 0x0 << 0 )  /* (PWMC_CH) Channel Counter */
/* -------- PWMC_CUPDR : (PWMC_CH Offset: 0x10) PWMC Channel Update Register -------- */
#تعریف_کرو AT91C_PWMC_CUPD             ( 0x0 << 0 )  /* (PWMC_CH) Channel Update */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Pulse Width Modulation Controller Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_PWMC structure *** */
#تعریف_کرو PWMC_MR                    ( 0 )          /* PWMC Mode Register */
#تعریف_کرو PWMC_ENA                   ( 4 )          /* PWMC Enable Register */
#تعریف_کرو PWMC_DIS                   ( 8 )          /* PWMC Disable Register */
#تعریف_کرو PWMC_SR                    ( 12 )         /* PWMC Status Register */
#تعریف_کرو PWMC_IER                   ( 16 )         /* PWMC Interrupt Enable Register */
#تعریف_کرو PWMC_IDR                   ( 20 )         /* PWMC Interrupt Disable Register */
#تعریف_کرو PWMC_IMR                   ( 24 )         /* PWMC Interrupt Mask Register */
#تعریف_کرو PWMC_ISR                   ( 28 )         /* PWMC Interrupt Status Register */
#تعریف_کرو PWMC_VR                    ( 252 )        /* PWMC Version Register */
#تعریف_کرو PWMC_CH                    ( 512 )        /* PWMC Channel 0 */
/* -------- PWMC_MR : (PWMC Offset: 0x0) PWMC Mode Register -------- */
#تعریف_کرو AT91C_PWMC_DIVA            ( 0xFF << 0 )  /* (PWMC) CLKA divide factor. */
#تعریف_کرو AT91C_PWMC_PREA            ( 0xF << 8 )   /* (PWMC) Divider Input Clock Prescaler A */
#تعریف_کرو     AT91C_PWMC_PREA_MCK    ( 0x0 << 8 )   /* (PWMC) */
#تعریف_کرو AT91C_PWMC_DIVB            ( 0xFF << 16 ) /* (PWMC) CLKB divide factor. */
#تعریف_کرو AT91C_PWMC_PREB            ( 0xF << 24 )  /* (PWMC) Divider Input Clock Prescaler B */
#تعریف_کرو     AT91C_PWMC_PREB_MCK    ( 0x0 << 24 )  /* (PWMC) */
/* -------- PWMC_ENA : (PWMC Offset: 0x4) PWMC Enable Register -------- */
#تعریف_کرو AT91C_PWMC_CHID0           ( 0x1 << 0 )   /* (PWMC) Channel ID 0 */
#تعریف_کرو AT91C_PWMC_CHID1           ( 0x1 << 1 )   /* (PWMC) Channel ID 1 */
#تعریف_کرو AT91C_PWMC_CHID2           ( 0x1 << 2 )   /* (PWMC) Channel ID 2 */
#تعریف_کرو AT91C_PWMC_CHID3           ( 0x1 << 3 )   /* (PWMC) Channel ID 3 */
#تعریف_کرو AT91C_PWMC_CHID4           ( 0x1 << 4 )   /* (PWMC) Channel ID 4 */
#تعریف_کرو AT91C_PWMC_CHID5           ( 0x1 << 5 )   /* (PWMC) Channel ID 5 */
#تعریف_کرو AT91C_PWMC_CHID6           ( 0x1 << 6 )   /* (PWMC) Channel ID 6 */
#تعریف_کرو AT91C_PWMC_CHID7           ( 0x1 << 7 )   /* (PWMC) Channel ID 7 */
/* -------- PWMC_DIS : (PWMC Offset: 0x8) PWMC Disable Register -------- */
/* -------- PWMC_SR : (PWMC Offset: 0xc) PWMC Status Register -------- */
/* -------- PWMC_IER : (PWMC Offset: 0x10) PWMC Interrupt Enable Register -------- */
/* -------- PWMC_IDR : (PWMC Offset: 0x14) PWMC Interrupt Disable Register -------- */
/* -------- PWMC_IMR : (PWMC Offset: 0x18) PWMC Interrupt Mask Register -------- */
/* -------- PWMC_ISR : (PWMC Offset: 0x1c) PWMC Interrupt Status Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR USB Device Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_UDP structure *** */
#تعریف_کرو UDP_عدد              ( 0 )          /* Frame Number Register */
#تعریف_کرو UDP_GLBSTATE         ( 4 )          /* Global State Register */
#تعریف_کرو UDP_FADDR            ( 8 )          /* Function Address Register */
#تعریف_کرو UDP_IER              ( 16 )         /* Interrupt Enable Register */
#تعریف_کرو UDP_IDR              ( 20 )         /* Interrupt Disable Register */
#تعریف_کرو UDP_IMR              ( 24 )         /* Interrupt Mask Register */
#تعریف_کرو UDP_ISR              ( 28 )         /* Interrupt Status Register */
#تعریف_کرو UDP_ICR              ( 32 )         /* Interrupt Clear Register */
#تعریف_کرو UDP_RSTEP            ( 40 )         /* Reset Endpoint Register */
#تعریف_کرو UDP_CSR              ( 48 )         /* Endpoint Control and Status Register */
#تعریف_کرو UDP_FDR              ( 80 )         /* Endpoint FIFO Data Register */
/* -------- UDP_FRM_NUM : (UDP Offset: 0x0) USB Frame Number Register -------- */
#تعریف_کرو AT91_C_UDP_FRM_عدد    ( 0x7FF << 0 ) /* (UDP) Frame Number as Defined in the Packet Field Formats */
#تعریف_کرو AT91C_UDP_FRM_ERR    ( 0x1 << 16 )  /* (UDP) Frame Error */
#تعریف_کرو AT91C_UDP_FRM_OK     ( 0x1 << 17 )  /* (UDP) Frame OK */
/* -------- UDP_GLB_STATE : (UDP Offset: 0x4) USB Global State Register -------- */
#تعریف_کرو AT91C_UDP_FADDEN     ( 0x1 << 0 )   /* (UDP) Function Address Enable */
#تعریف_کرو AT91C_UDP_CONFG      ( 0x1 << 1 )   /* (UDP) Configured */
#تعریف_کرو AT91C_UDP_RMWUPE     ( 0x1 << 2 )   /* (UDP) Remote Wake Up Enable */
#تعریف_کرو AT91C_UDP_RSMINPR    ( 0x1 << 3 )   /* (UDP) A Resume Has Been Sent to the Host */
/* -------- UDP_FADDR : (UDP Offset: 0x8) USB Function Address Register -------- */
#تعریف_کرو AT91C_UDP_FADD       ( 0xFF << 0 )  /* (UDP) Function Address Value */
#تعریف_کرو AT91C_UDP_FEN        ( 0x1 << 8 )   /* (UDP) Function Enable */
/* -------- UDP_IER : (UDP Offset: 0x10) USB Interrupt Enable Register -------- */
#تعریف_کرو AT91C_UDP_EPINT0     ( 0x1 << 0 )   /* (UDP) Endpoint 0 Interrupt */
#تعریف_کرو AT91C_UDP_EPINT1     ( 0x1 << 1 )   /* (UDP) Endpoint 0 Interrupt */
#تعریف_کرو AT91C_UDP_EPINT2     ( 0x1 << 2 )   /* (UDP) Endpoint 2 Interrupt */
#تعریف_کرو AT91C_UDP_EPINT3     ( 0x1 << 3 )   /* (UDP) Endpoint 3 Interrupt */
#تعریف_کرو AT91C_UDP_EPINT4     ( 0x1 << 4 )   /* (UDP) Endpoint 4 Interrupt */
#تعریف_کرو AT91C_UDP_EPINT5     ( 0x1 << 5 )   /* (UDP) Endpoint 5 Interrupt */
#تعریف_کرو AT91C_UDP_EPINT6     ( 0x1 << 6 )   /* (UDP) Endpoint 6 Interrupt */
#تعریف_کرو AT91C_UDP_EPINT7     ( 0x1 << 7 )   /* (UDP) Endpoint 7 Interrupt */
#تعریف_کرو AT91C_UDP_RXSUSP     ( 0x1 << 8 )   /* (UDP) USB Suspend Interrupt */
#تعریف_کرو AT91C_UDP_RXRSM      ( 0x1 << 9 )   /* (UDP) USB Resume Interrupt */
#تعریف_کرو AT91C_UDP_EXTRSM     ( 0x1 << 10 )  /* (UDP) USB External Resume Interrupt */
#تعریف_کرو AT91C_UDP_SOFINT     ( 0x1 << 11 )  /* (UDP) USB Start Of frame Interrupt */
#تعریف_کرو AT91C_UDP_WAKEUP     ( 0x1 << 13 )  /* (UDP) USB Resume Interrupt */
/* -------- UDP_IDR : (UDP Offset: 0x14) USB Interrupt Disable Register -------- */
/* -------- UDP_IMR : (UDP Offset: 0x18) USB Interrupt Mask Register -------- */
/* -------- UDP_ISR : (UDP Offset: 0x1c) USB Interrupt Status Register -------- */
#تعریف_کرو AT91C_UDP_ENDBUSRES              ( 0x1 << 12 ) /* (UDP) USB End Of Bus Reset Interrupt */
/* -------- UDP_ICR : (UDP Offset: 0x20) USB Interrupt Clear Register -------- */
/* -------- UDP_RST_EP : (UDP Offset: 0x28) USB Reset Endpoint Register -------- */
#تعریف_کرو AT91C_UDP_EP0                    ( 0x1 << 0 )    /* (UDP) Reset Endpoint 0 */
#تعریف_کرو AT91C_UDP_EP1                    ( 0x1 << 1 )    /* (UDP) Reset Endpoint 1 */
#تعریف_کرو AT91C_UDP_EP2                    ( 0x1 << 2 )    /* (UDP) Reset Endpoint 2 */
#تعریف_کرو AT91C_UDP_EP3                    ( 0x1 << 3 )    /* (UDP) Reset Endpoint 3 */
#تعریف_کرو AT91C_UDP_EP4                    ( 0x1 << 4 )    /* (UDP) Reset Endpoint 4 */
#تعریف_کرو AT91C_UDP_EP5                    ( 0x1 << 5 )    /* (UDP) Reset Endpoint 5 */
#تعریف_کرو AT91C_UDP_EP6                    ( 0x1 << 6 )    /* (UDP) Reset Endpoint 6 */
#تعریف_کرو AT91C_UDP_EP7                    ( 0x1 << 7 )    /* (UDP) Reset Endpoint 7 */
/* -------- UDP_CSR : (UDP Offset: 0x30) USB Endpoint Control and Status Register -------- */
#تعریف_کرو AT91C_UDP_TXCOMP                 ( 0x1 << 0 )    /* (UDP) Generates an IN packet with data previously written in the DPR */
#تعریف_کرو AT91_C_UDP_RX_ڈیٹا_BK0            ( 0x1 << 1 )    /* (UDP) Receive Data Bank 0 */
#تعریف_کرو AT91C_UDP_RXSETUP                ( 0x1 << 2 )    /* (UDP) Sends STALL to the Host (Control endpoints) */
#تعریف_کرو AT91C_UDP_ISOERROR               ( 0x1 << 3 )    /* (UDP) Isochronous error (Isochronous endpoints) */
#تعریف_کرو AT91C_UDP_TXPKTRDY               ( 0x1 << 4 )    /* (UDP) Transmit Packet Ready */
#تعریف_کرو AT91C_UDP_FORCESTALL             ( 0x1 << 5 )    /* (UDP) Force Stall (used by Control, Bulk and Isochronous endpoints). */
#تعریف_کرو AT91_C_UDP_RX_ڈیٹا_BK1            ( 0x1 << 6 )    /* (UDP) Receive Data Bank 1 (only used by endpoints with ping-pong attributes). */
#تعریف_کرو AT91C_UDP_DIR                    ( 0x1 << 7 )    /* (UDP) Transfer Direction */
#تعریف_کرو AT91C_UDP_EPTYPE                 ( 0x7 << 8 )    /* (UDP) Endpoint type */
#تعریف_کرو     AT91C_UDP_EPTYPE_CTRL        ( 0x0 << 8 )    /* (UDP) Control */
#تعریف_کرو     AT91_C_UDP_EPTYPE_ISO_برآمد     ( 0x1 << 8 )    /* (UDP) Isochronous OUT */
#تعریف_کرو     AT91_C_UDP_EPTYPE_BULK_برآمد    ( 0x2 << 8 )    /* (UDP) Bulk OUT */
#تعریف_کرو     AT91_C_UDP_EPTYPE_INT_برآمد     ( 0x3 << 8 )    /* (UDP) Interrupt OUT */
#تعریف_کرو     AT91_C_UDP_EPTYPE_ISO_اندر      ( 0x5 << 8 )    /* (UDP) Isochronous IN */
#تعریف_کرو     AT91_C_UDP_EPTYPE_BULK_اندر     ( 0x6 << 8 )    /* (UDP) Bulk IN */
#تعریف_کرو     AT91_C_UDP_EPTYPE_INT_اندر      ( 0x7 << 8 )    /* (UDP) Interrupt IN */
#تعریف_کرو AT91C_UDP_DTGLE                  ( 0x1 << 11 )   /* (UDP) Data Toggle */
#تعریف_کرو AT91C_UDP_EPEDS                  ( 0x1 << 15 )   /* (UDP) Endpoint Enable Disable */
#تعریف_کرو AT91C_UDP_RXBYTECNT              ( 0x7FF << 16 ) /* (UDP) Number Of Bytes Available in the FIFO */

/* ***************************************************************************** */
/*               REGISTER ADDRESS DEFINITION FOR AT91SAM7S64 */
/* ***************************************************************************** */
/* ========== Register definition for SYSC peripheral ========== */
#تعریف_کرو AT91C_SYSC_SYSC_VRPM    ( 0xFFFFFD60 ) /* (SYSC) Voltage Regulator Power Mode Register */
/* ========== Register definition for AIC peripheral ========== */
#تعریف_کرو AT91C_AIC_ICCR          ( 0xFFFFF128 ) /* (AIC) Interrupt Clear Command Register */
#تعریف_کرو AT91C_AIC_IECR          ( 0xFFFFF120 ) /* (AIC) Interrupt Enable Command Register */
#تعریف_کرو AT91C_AIC_SMR           ( 0xFFFFF000 ) /* (AIC) Source Mode Register */
#تعریف_کرو AT91C_AIC_ISCR          ( 0xFFFFF12C ) /* (AIC) Interrupt Set Command Register */
#تعریف_کرو AT91C_AIC_EOICR         ( 0xFFFFF130 ) /* (AIC) End of Interrupt Command Register */
#تعریف_کرو AT91C_AIC_DCR           ( 0xFFFFF138 ) /* (AIC) Debug Control Register (Protect) */
#تعریف_کرو AT91C_AIC_FFER          ( 0xFFFFF140 ) /* (AIC) Fast Forcing Enable Register */
#تعریف_کرو AT91C_AIC_SVR           ( 0xFFFFF080 ) /* (AIC) Source Vector Register */
#تعریف_کرو AT91C_AIC_SPU           ( 0xFFFFF134 ) /* (AIC) Spurious Vector Register */
#تعریف_کرو AT91C_AIC_FFDR          ( 0xFFFFF144 ) /* (AIC) Fast Forcing Disable Register */
#تعریف_کرو AT91C_AIC_FVR           ( 0xFFFFF104 ) /* (AIC) FIQ Vector Register */
#تعریف_کرو AT91C_AIC_FFSR          ( 0xFFFFF148 ) /* (AIC) Fast Forcing Status Register */
#تعریف_کرو AT91C_AIC_IMR           ( 0xFFFFF110 ) /* (AIC) Interrupt Mask Register */
#تعریف_کرو AT91C_AIC_ISR           ( 0xFFFFF108 ) /* (AIC) Interrupt Status Register */
#تعریف_کرو AT91C_AIC_IVR           ( 0xFFFFF100 ) /* (AIC) IRQ Vector Register */
#تعریف_کرو AT91C_AIC_IDCR          ( 0xFFFFF124 ) /* (AIC) Interrupt Disable Command Register */
#تعریف_کرو AT91C_AIC_CISR          ( 0xFFFFF114 ) /* (AIC) Core Interrupt Status Register */
#تعریف_کرو AT91C_AIC_IPR           ( 0xFFFFF10C ) /* (AIC) Interrupt Pending Register */
/* ========== Register definition for DBGU peripheral ========== */
#تعریف_کرو AT91C_DBGU_C2R          ( 0xFFFFF244 ) /* (DBGU) Chip ID2 Register */
#تعریف_کرو AT91C_DBGU_THR          ( 0xFFFFF21C ) /* (DBGU) Transmitter Holding Register */
#تعریف_کرو AT91C_DBGU_CSR          ( 0xFFFFF214 ) /* (DBGU) Channel Status Register */
#تعریف_کرو AT91C_DBGU_IDR          ( 0xFFFFF20C ) /* (DBGU) Interrupt Disable Register */
#تعریف_کرو AT91C_DBGU_MR           ( 0xFFFFF204 ) /* (DBGU) Mode Register */
#تعریف_کرو AT91C_DBGU_FNTR         ( 0xFFFFF248 ) /* (DBGU) Force NTRST Register */
#تعریف_کرو AT91C_DBGU_C1R          ( 0xFFFFF240 ) /* (DBGU) Chip ID1 Register */
#تعریف_کرو AT91C_DBGU_BRGR         ( 0xFFFFF220 ) /* (DBGU) Baud Rate Generator Register */
#تعریف_کرو AT91C_DBGU_RHR          ( 0xFFFFF218 ) /* (DBGU) Receiver Holding Register */
#تعریف_کرو AT91C_DBGU_IMR          ( 0xFFFFF210 ) /* (DBGU) Interrupt Mask Register */
#تعریف_کرو AT91C_DBGU_IER          ( 0xFFFFF208 ) /* (DBGU) Interrupt Enable Register */
#تعریف_کرو AT91C_DBGU_CR           ( 0xFFFFF200 ) /* (DBGU) Control Register */
/* ========== Register definition for PDC_DBGU peripheral ========== */
#تعریف_کرو AT91C_DBGU_TNCR         ( 0xFFFFF31C ) /* (PDC_DBGU) Transmit Next Counter Register */
#تعریف_کرو AT91C_DBGU_RNCR         ( 0xFFFFF314 ) /* (PDC_DBGU) Receive Next Counter Register */
#تعریف_کرو AT91C_DBGU_PTCR         ( 0xFFFFF320 ) /* (PDC_DBGU) PDC Transfer Control Register */
#تعریف_کرو AT91C_DBGU_PTSR         ( 0xFFFFF324 ) /* (PDC_DBGU) PDC Transfer Status Register */
#تعریف_کرو AT91C_DBGU_RCR          ( 0xFFFFF304 ) /* (PDC_DBGU) Receive Counter Register */
#تعریف_کرو AT91C_DBGU_TCR          ( 0xFFFFF30C ) /* (PDC_DBGU) Transmit Counter Register */
#تعریف_کرو AT91C_DBGU_RPR          ( 0xFFFFF300 ) /* (PDC_DBGU) Receive Pointer Register */
#تعریف_کرو AT91C_DBGU_TPR          ( 0xFFFFF308 ) /* (PDC_DBGU) Transmit Pointer Register */
#تعریف_کرو AT91C_DBGU_RNPR         ( 0xFFFFF310 ) /* (PDC_DBGU) Receive Next Pointer Register */
#تعریف_کرو AT91C_DBGU_TNPR         ( 0xFFFFF318 ) /* (PDC_DBGU) Transmit Next Pointer Register */
/* ========== Register definition for PIOA peripheral ========== */
#تعریف_کرو AT91C_PIOA_IMR          ( 0xFFFFF448 ) /* (PIOA) Interrupt Mask Register */
#تعریف_کرو AT91C_PIOA_IER          ( 0xFFFFF440 ) /* (PIOA) Interrupt Enable Register */
#تعریف_کرو AT91C_PIOA_OWDR         ( 0xFFFFF4A4 ) /* (PIOA) Output Write Disable Register */
#تعریف_کرو AT91C_PIOA_ISR          ( 0xFFFFF44C ) /* (PIOA) Interrupt Status Register */
#تعریف_کرو AT91C_PIOA_PPUDR        ( 0xFFFFF460 ) /* (PIOA) Pull-up Disable Register */
#تعریف_کرو AT91C_PIOA_MDSR         ( 0xFFFFF458 ) /* (PIOA) Multi-driver Status Register */
#تعریف_کرو AT91C_PIOA_MDER         ( 0xFFFFF450 ) /* (PIOA) Multi-driver Enable Register */
#تعریف_کرو AT91_C_PIOA_فی          ( 0xFFFFF400 ) /* (PIOA) PIO Enable Register */
#تعریف_کرو AT91C_PIOA_PSR          ( 0xFFFFF408 ) /* (PIOA) PIO Status Register */
#تعریف_کرو AT91C_PIOA_OER          ( 0xFFFFF410 ) /* (PIOA) Output Enable Register */
#تعریف_کرو AT91C_PIOA_BSR          ( 0xFFFFF474 ) /* (PIOA) Select B Register */
#تعریف_کرو AT91C_PIOA_PPUER        ( 0xFFFFF464 ) /* (PIOA) Pull-up Enable Register */
#تعریف_کرو AT91C_PIOA_MDDR         ( 0xFFFFF454 ) /* (PIOA) Multi-driver Disable Register */
#تعریف_کرو AT91C_PIOA_PDR          ( 0xFFFFF404 ) /* (PIOA) PIO Disable Register */
#تعریف_کرو AT91C_PIOA_ODR          ( 0xFFFFF414 ) /* (PIOA) Output Disable Registerr */
#تعریف_کرو AT91C_PIOA_IFDR         ( 0xFFFFF424 ) /* (PIOA) Input Filter Disable Register */
#تعریف_کرو AT91C_PIOA_ABSR         ( 0xFFFFF478 ) /* (PIOA) AB Select Status Register */
#تعریف_کرو AT91C_PIOA_ASR          ( 0xFFFFF470 ) /* (PIOA) Select A Register */
#تعریف_کرو AT91C_PIOA_PPUSR        ( 0xFFFFF468 ) /* (PIOA) Pad Pull-up Status Register */
#تعریف_کرو AT91C_PIOA_ODSR         ( 0xFFFFF438 ) /* (PIOA) Output Data Status Register */
#تعریف_کرو AT91C_PIOA_SODR         ( 0xFFFFF430 ) /* (PIOA) Set Output Data Register */
#تعریف_کرو AT91C_PIOA_IFSR         ( 0xFFFFF428 ) /* (PIOA) Input Filter Status Register */
#تعریف_کرو AT91C_PIOA_IFER         ( 0xFFFFF420 ) /* (PIOA) Input Filter Enable Register */
#تعریف_کرو AT91C_PIOA_OSR          ( 0xFFFFF418 ) /* (PIOA) Output Status Register */
#تعریف_کرو AT91C_PIOA_IDR          ( 0xFFFFF444 ) /* (PIOA) Interrupt Disable Register */
#تعریف_کرو AT91C_PIOA_PDSR         ( 0xFFFFF43C ) /* (PIOA) Pin Data Status Register */
#تعریف_کرو AT91C_PIOA_CODR         ( 0xFFFFF434 ) /* (PIOA) Clear Output Data Register */
#تعریف_کرو AT91C_PIOA_OWSR         ( 0xFFFFF4A8 ) /* (PIOA) Output Write Status Register */
#تعریف_کرو AT91C_PIOA_OWER         ( 0xFFFFF4A0 ) /* (PIOA) Output Write Enable Register */
/* ========== Register definition for CKGR peripheral ========== */
#تعریف_کرو AT91C_CKGR_PLLR         ( 0xFFFFFC2C ) /* (CKGR) PLL Register */
#تعریف_کرو AT91C_CKGR_MCFR         ( 0xFFFFFC24 ) /* (CKGR) Main Clock  Frequency Register */
#تعریف_کرو AT91C_CKGR_MOR          ( 0xFFFFFC20 ) /* (CKGR) Main Oscillator Register */
/* ========== Register definition for PMC peripheral ========== */
#تعریف_کرو AT91C_PMC_SCSR          ( 0xFFFFFC08 ) /* (PMC) System Clock Status Register */
#تعریف_کرو AT91C_PMC_SCER          ( 0xFFFFFC00 ) /* (PMC) System Clock Enable Register */
#تعریف_کرو AT91C_PMC_IMR           ( 0xFFFFFC6C ) /* (PMC) Interrupt Mask Register */
#تعریف_کرو AT91C_PMC_IDR           ( 0xFFFFFC64 ) /* (PMC) Interrupt Disable Register */
#تعریف_کرو AT91C_PMC_PCDR          ( 0xFFFFFC14 ) /* (PMC) Peripheral Clock Disable Register */
#تعریف_کرو AT91C_PMC_SCDR          ( 0xFFFFFC04 ) /* (PMC) System Clock Disable Register */
#تعریف_کرو AT91C_PMC_SR            ( 0xFFFFFC68 ) /* (PMC) Status Register */
#تعریف_کرو AT91C_PMC_IER           ( 0xFFFFFC60 ) /* (PMC) Interrupt Enable Register */
#تعریف_کرو AT91C_PMC_MCKR          ( 0xFFFFFC30 ) /* (PMC) Master Clock Register */
#تعریف_کرو AT91C_PMC_MOR           ( 0xFFFFFC20 ) /* (PMC) Main Oscillator Register */
#تعریف_کرو AT91C_PMC_PCER          ( 0xFFFFFC10 ) /* (PMC) Peripheral Clock Enable Register */
#تعریف_کرو AT91C_PMC_PCSR          ( 0xFFFFFC18 ) /* (PMC) Peripheral Clock Status Register */
#تعریف_کرو AT91C_PMC_PLLR          ( 0xFFFFFC2C ) /* (PMC) PLL Register */
#تعریف_کرو AT91C_PMC_MCFR          ( 0xFFFFFC24 ) /* (PMC) Main Clock  Frequency Register */
#تعریف_کرو AT91C_PMC_PCKR          ( 0xFFFFFC40 ) /* (PMC) Programmable Clock Register */
/* ========== Register definition for RSTC peripheral ========== */
#تعریف_کرو AT91C_RSTC_RSR          ( 0xFFFFFD04 ) /* (RSTC) Reset Status Register */
#تعریف_کرو AT91C_RSTC_RMR          ( 0xFFFFFD08 ) /* (RSTC) Reset Mode Register */
#تعریف_کرو AT91C_RSTC_RCR          ( 0xFFFFFD00 ) /* (RSTC) Reset Control Register */
/* ========== Register definition for RTTC peripheral ========== */
#تعریف_کرو AT91C_RTTC_RTSR         ( 0xFFFFFD2C ) /* (RTTC) Real-time Status Register */
#تعریف_کرو AT91C_RTTC_RTAR         ( 0xFFFFFD24 ) /* (RTTC) Real-time Alarm Register */
#تعریف_کرو AT91C_RTTC_RTVR         ( 0xFFFFFD28 ) /* (RTTC) Real-time Value Register */
#تعریف_کرو AT91C_RTTC_RTMR         ( 0xFFFFFD20 ) /* (RTTC) Real-time Mode Register */
/* ========== Register definition for PITC peripheral ========== */
#تعریف_کرو AT91C_PITC_PIIR         ( 0xFFFFFD3C ) /* (PITC) Period Interval Image Register */
#تعریف_کرو AT91C_PITC_PISR         ( 0xFFFFFD34 ) /* (PITC) Period Interval Status Register */
#تعریف_کرو AT91C_PITC_PIVR         ( 0xFFFFFD38 ) /* (PITC) Period Interval Value Register */
#تعریف_کرو AT91C_PITC_PIMR         ( 0xFFFFFD30 ) /* (PITC) Period Interval Mode Register */
/* ========== Register definition for WDTC peripheral ========== */
#تعریف_کرو AT91C_WDTC_WDMR         ( 0xFFFFFD44 ) /* (WDTC) Watchdog Mode Register */
#تعریف_کرو AT91C_WDTC_WDSR         ( 0xFFFFFD48 ) /* (WDTC) Watchdog Status Register */
#تعریف_کرو AT91C_WDTC_WDCR         ( 0xFFFFFD40 ) /* (WDTC) Watchdog Control Register */
/* ========== Register definition for MC peripheral ========== */
#تعریف_کرو AT91C_MC_FCR            ( 0xFFFFFF64 ) /* (MC) MC Flash Command Register */
#تعریف_کرو AT91C_MC_ASR            ( 0xFFFFFF04 ) /* (MC) MC Abort Status Register */
#تعریف_کرو AT91C_MC_FSR            ( 0xFFFFFF68 ) /* (MC) MC Flash Status Register */
#تعریف_کرو AT91C_MC_FMR            ( 0xFFFFFF60 ) /* (MC) MC Flash Mode Register */
#تعریف_کرو AT91C_MC_AASR           ( 0xFFFFFF08 ) /* (MC) MC Abort Address Status Register */
#تعریف_کرو AT91C_MC_RCR            ( 0xFFFFFF00 ) /* (MC) MC Remap Control Register */
/* ========== Register definition for PDC_SPI peripheral ========== */
#تعریف_کرو AT91C_SPI_PTCR          ( 0xFFFE0120 ) /* (PDC_SPI) PDC Transfer Control Register */
#تعریف_کرو AT91C_SPI_TNPR          ( 0xFFFE0118 ) /* (PDC_SPI) Transmit Next Pointer Register */
#تعریف_کرو AT91C_SPI_RNPR          ( 0xFFFE0110 ) /* (PDC_SPI) Receive Next Pointer Register */
#تعریف_کرو AT91C_SPI_TPR           ( 0xFFFE0108 ) /* (PDC_SPI) Transmit Pointer Register */
#تعریف_کرو AT91C_SPI_RPR           ( 0xFFFE0100 ) /* (PDC_SPI) Receive Pointer Register */
#تعریف_کرو AT91C_SPI_PTSR          ( 0xFFFE0124 ) /* (PDC_SPI) PDC Transfer Status Register */
#تعریف_کرو AT91C_SPI_TNCR          ( 0xFFFE011C ) /* (PDC_SPI) Transmit Next Counter Register */
#تعریف_کرو AT91C_SPI_RNCR          ( 0xFFFE0114 ) /* (PDC_SPI) Receive Next Counter Register */
#تعریف_کرو AT91C_SPI_TCR           ( 0xFFFE010C ) /* (PDC_SPI) Transmit Counter Register */
#تعریف_کرو AT91C_SPI_RCR           ( 0xFFFE0104 ) /* (PDC_SPI) Receive Counter Register */
/* ========== Register definition for SPI peripheral ========== */
#تعریف_کرو AT91C_SPI_CSR           ( 0xFFFE0030 ) /* (SPI) Chip Select Register */
#تعریف_کرو AT91C_SPI_IDR           ( 0xFFFE0018 ) /* (SPI) Interrupt Disable Register */
#تعریف_کرو AT91C_SPI_SR            ( 0xFFFE0010 ) /* (SPI) Status Register */
#تعریف_کرو AT91C_SPI_RDR           ( 0xFFFE0008 ) /* (SPI) Receive Data Register */
#تعریف_کرو AT91C_SPI_CR            ( 0xFFFE0000 ) /* (SPI) Control Register */
#تعریف_کرو AT91C_SPI_IMR           ( 0xFFFE001C ) /* (SPI) Interrupt Mask Register */
#تعریف_کرو AT91C_SPI_IER           ( 0xFFFE0014 ) /* (SPI) Interrupt Enable Register */
#تعریف_کرو AT91C_SPI_TDR           ( 0xFFFE000C ) /* (SPI) Transmit Data Register */
#تعریف_کرو AT91C_SPI_MR            ( 0xFFFE0004 ) /* (SPI) Mode Register */
/* ========== Register definition for PDC_ADC peripheral ========== */
#تعریف_کرو AT91C_ADC_PTCR          ( 0xFFFD8120 ) /* (PDC_ADC) PDC Transfer Control Register */
#تعریف_کرو AT91C_ADC_TNPR          ( 0xFFFD8118 ) /* (PDC_ADC) Transmit Next Pointer Register */
#تعریف_کرو AT91C_ADC_RNPR          ( 0xFFFD8110 ) /* (PDC_ADC) Receive Next Pointer Register */
#تعریف_کرو AT91C_ADC_TPR           ( 0xFFFD8108 ) /* (PDC_ADC) Transmit Pointer Register */
#تعریف_کرو AT91C_ADC_RPR           ( 0xFFFD8100 ) /* (PDC_ADC) Receive Pointer Register */
#تعریف_کرو AT91C_ADC_PTSR          ( 0xFFFD8124 ) /* (PDC_ADC) PDC Transfer Status Register */
#تعریف_کرو AT91C_ADC_TNCR          ( 0xFFFD811C ) /* (PDC_ADC) Transmit Next Counter Register */
#تعریف_کرو AT91C_ADC_RNCR          ( 0xFFFD8114 ) /* (PDC_ADC) Receive Next Counter Register */
#تعریف_کرو AT91C_ADC_TCR           ( 0xFFFD810C ) /* (PDC_ADC) Transmit Counter Register */
#تعریف_کرو AT91C_ADC_RCR           ( 0xFFFD8104 ) /* (PDC_ADC) Receive Counter Register */
/* ========== Register definition for ADC peripheral ========== */
#تعریف_کرو AT91C_ADC_IMR           ( 0xFFFD802C ) /* (ADC) ADC Interrupt Mask Register */
#تعریف_کرو AT91C_ADC_CDR4          ( 0xFFFD8040 ) /* (ADC) ADC Channel Data Register 4 */
#تعریف_کرو AT91C_ADC_CDR2          ( 0xFFFD8038 ) /* (ADC) ADC Channel Data Register 2 */
#تعریف_کرو AT91C_ADC_CDR0          ( 0xFFFD8030 ) /* (ADC) ADC Channel Data Register 0 */
#تعریف_کرو AT91C_ADC_CDR7          ( 0xFFFD804C ) /* (ADC) ADC Channel Data Register 7 */
#تعریف_کرو AT91C_ADC_CDR1          ( 0xFFFD8034 ) /* (ADC) ADC Channel Data Register 1 */
#تعریف_کرو AT91C_ADC_CDR3          ( 0xFFFD803C ) /* (ADC) ADC Channel Data Register 3 */
#تعریف_کرو AT91C_ADC_CDR5          ( 0xFFFD8044 ) /* (ADC) ADC Channel Data Register 5 */
#تعریف_کرو AT91C_ADC_MR            ( 0xFFFD8004 ) /* (ADC) ADC Mode Register */
#تعریف_کرو AT91C_ADC_CDR6          ( 0xFFFD8048 ) /* (ADC) ADC Channel Data Register 6 */
#تعریف_کرو AT91C_ADC_CR            ( 0xFFFD8000 ) /* (ADC) ADC Control Register */
#تعریف_کرو AT91C_ADC_CHER          ( 0xFFFD8010 ) /* (ADC) ADC Channel Enable Register */
#تعریف_کرو AT91C_ADC_CHSR          ( 0xFFFD8018 ) /* (ADC) ADC Channel Status Register */
#تعریف_کرو AT91C_ADC_IER           ( 0xFFFD8024 ) /* (ADC) ADC Interrupt Enable Register */
#تعریف_کرو AT91C_ADC_SR            ( 0xFFFD801C ) /* (ADC) ADC Status Register */
#تعریف_کرو AT91C_ADC_CHDR          ( 0xFFFD8014 ) /* (ADC) ADC Channel Disable Register */
#تعریف_کرو AT91C_ADC_IDR           ( 0xFFFD8028 ) /* (ADC) ADC Interrupt Disable Register */
#تعریف_کرو AT91C_ADC_LCDR          ( 0xFFFD8020 ) /* (ADC) ADC Last Converted Data Register */
/* ========== Register definition for PDC_SSC peripheral ========== */
#تعریف_کرو AT91C_SSC_PTCR          ( 0xFFFD4120 ) /* (PDC_SSC) PDC Transfer Control Register */
#تعریف_کرو AT91C_SSC_TNPR          ( 0xFFFD4118 ) /* (PDC_SSC) Transmit Next Pointer Register */
#تعریف_کرو AT91C_SSC_RNPR          ( 0xFFFD4110 ) /* (PDC_SSC) Receive Next Pointer Register */
#تعریف_کرو AT91C_SSC_TPR           ( 0xFFFD4108 ) /* (PDC_SSC) Transmit Pointer Register */
#تعریف_کرو AT91C_SSC_RPR           ( 0xFFFD4100 ) /* (PDC_SSC) Receive Pointer Register */
#تعریف_کرو AT91C_SSC_PTSR          ( 0xFFFD4124 ) /* (PDC_SSC) PDC Transfer Status Register */
#تعریف_کرو AT91C_SSC_TNCR          ( 0xFFFD411C ) /* (PDC_SSC) Transmit Next Counter Register */
#تعریف_کرو AT91C_SSC_RNCR          ( 0xFFFD4114 ) /* (PDC_SSC) Receive Next Counter Register */
#تعریف_کرو AT91C_SSC_TCR           ( 0xFFFD410C ) /* (PDC_SSC) Transmit Counter Register */
#تعریف_کرو AT91C_SSC_RCR           ( 0xFFFD4104 ) /* (PDC_SSC) Receive Counter Register */
/* ========== Register definition for SSC peripheral ========== */
#تعریف_کرو AT91C_SSC_RFMR          ( 0xFFFD4014 ) /* (SSC) Receive Frame Mode Register */
#تعریف_کرو AT91C_SSC_CMR           ( 0xFFFD4004 ) /* (SSC) Clock Mode Register */
#تعریف_کرو AT91C_SSC_IDR           ( 0xFFFD4048 ) /* (SSC) Interrupt Disable Register */
#تعریف_کرو AT91C_SSC_SR            ( 0xFFFD4040 ) /* (SSC) Status Register */
#تعریف_کرو AT91C_SSC_RC0R          ( 0xFFFD4038 ) /* (SSC) Receive Compare 0 Register */
#تعریف_کرو AT91C_SSC_RSHR          ( 0xFFFD4030 ) /* (SSC) Receive Sync Holding Register */
#تعریف_کرو AT91C_SSC_RHR           ( 0xFFFD4020 ) /* (SSC) Receive Holding Register */
#تعریف_کرو AT91C_SSC_TCMR          ( 0xFFFD4018 ) /* (SSC) Transmit Clock Mode Register */
#تعریف_کرو AT91C_SSC_RCMR          ( 0xFFFD4010 ) /* (SSC) Receive Clock ModeRegister */
#تعریف_کرو AT91C_SSC_CR            ( 0xFFFD4000 ) /* (SSC) Control Register */
#تعریف_کرو AT91C_SSC_IMR           ( 0xFFFD404C ) /* (SSC) Interrupt Mask Register */
#تعریف_کرو AT91C_SSC_IER           ( 0xFFFD4044 ) /* (SSC) Interrupt Enable Register */
#تعریف_کرو AT91C_SSC_RC1R          ( 0xFFFD403C ) /* (SSC) Receive Compare 1 Register */
#تعریف_کرو AT91C_SSC_TSHR          ( 0xFFFD4034 ) /* (SSC) Transmit Sync Holding Register */
#تعریف_کرو AT91C_SSC_THR           ( 0xFFFD4024 ) /* (SSC) Transmit Holding Register */
#تعریف_کرو AT91C_SSC_TFMR          ( 0xFFFD401C ) /* (SSC) Transmit Frame Mode Register */
/* ========== Register definition for PDC_US1 peripheral ========== */
#تعریف_کرو AT91C_US1_PTSR          ( 0xFFFC4124 ) /* (PDC_US1) PDC Transfer Status Register */
#تعریف_کرو AT91C_US1_TNCR          ( 0xFFFC411C ) /* (PDC_US1) Transmit Next Counter Register */
#تعریف_کرو AT91C_US1_RNCR          ( 0xFFFC4114 ) /* (PDC_US1) Receive Next Counter Register */
#تعریف_کرو AT91C_US1_TCR           ( 0xFFFC410C ) /* (PDC_US1) Transmit Counter Register */
#تعریف_کرو AT91C_US1_RCR           ( 0xFFFC4104 ) /* (PDC_US1) Receive Counter Register */
#تعریف_کرو AT91C_US1_PTCR          ( 0xFFFC4120 ) /* (PDC_US1) PDC Transfer Control Register */
#تعریف_کرو AT91C_US1_TNPR          ( 0xFFFC4118 ) /* (PDC_US1) Transmit Next Pointer Register */
#تعریف_کرو AT91C_US1_RNPR          ( 0xFFFC4110 ) /* (PDC_US1) Receive Next Pointer Register */
#تعریف_کرو AT91C_US1_TPR           ( 0xFFFC4108 ) /* (PDC_US1) Transmit Pointer Register */
#تعریف_کرو AT91C_US1_RPR           ( 0xFFFC4100 ) /* (PDC_US1) Receive Pointer Register */
/* ========== Register definition for US1 peripheral ========== */
#تعریف_کرو AT91C_US1_XXR           ( 0xFFFC4048 ) /* (US1) XON_XOFF Register */
#تعریف_کرو AT91C_US1_RHR           ( 0xFFFC4018 ) /* (US1) Receiver Holding Register */
#تعریف_کرو AT91C_US1_IMR           ( 0xFFFC4010 ) /* (US1) Interrupt Mask Register */
#تعریف_کرو AT91C_US1_IER           ( 0xFFFC4008 ) /* (US1) Interrupt Enable Register */
#تعریف_کرو AT91C_US1_CR            ( 0xFFFC4000 ) /* (US1) Control Register */
#تعریف_کرو AT91C_US1_RTOR          ( 0xFFFC4024 ) /* (US1) Receiver Time-out Register */
#تعریف_کرو AT91C_US1_THR           ( 0xFFFC401C ) /* (US1) Transmitter Holding Register */
#تعریف_کرو AT91C_US1_CSR           ( 0xFFFC4014 ) /* (US1) Channel Status Register */
#تعریف_کرو AT91C_US1_IDR           ( 0xFFFC400C ) /* (US1) Interrupt Disable Register */
#تعریف_کرو AT91C_US1_FIDI          ( 0xFFFC4040 ) /* (US1) FI_DI_Ratio Register */
#تعریف_کرو AT91C_US1_BRGR          ( 0xFFFC4020 ) /* (US1) Baud Rate Generator Register */
#تعریف_کرو AT91C_US1_TTGR          ( 0xFFFC4028 ) /* (US1) Transmitter Time-guard Register */
#تعریف_کرو AT91C_US1_IF            ( 0xFFFC404C ) /* (US1) IRDA_FILTER Register */
#تعریف_کرو AT91C_US1_NER           ( 0xFFFC4044 ) /* (US1) Nb Errors Register */
#تعریف_کرو AT91C_US1_MR            ( 0xFFFC4004 ) /* (US1) Mode Register */
/* ========== Register definition for PDC_US0 peripheral ========== */
#تعریف_کرو AT91C_US0_PTCR          ( 0xFFFC0120 ) /* (PDC_US0) PDC Transfer Control Register */
#تعریف_کرو AT91C_US0_TNPR          ( 0xFFFC0118 ) /* (PDC_US0) Transmit Next Pointer Register */
#تعریف_کرو AT91C_US0_RNPR          ( 0xFFFC0110 ) /* (PDC_US0) Receive Next Pointer Register */
#تعریف_کرو AT91C_US0_TPR           ( 0xFFFC0108 ) /* (PDC_US0) Transmit Pointer Register */
#تعریف_کرو AT91C_US0_RPR           ( 0xFFFC0100 ) /* (PDC_US0) Receive Pointer Register */
#تعریف_کرو AT91C_US0_PTSR          ( 0xFFFC0124 ) /* (PDC_US0) PDC Transfer Status Register */
#تعریف_کرو AT91C_US0_TNCR          ( 0xFFFC011C ) /* (PDC_US0) Transmit Next Counter Register */
#تعریف_کرو AT91C_US0_RNCR          ( 0xFFFC0114 ) /* (PDC_US0) Receive Next Counter Register */
#تعریف_کرو AT91C_US0_TCR           ( 0xFFFC010C ) /* (PDC_US0) Transmit Counter Register */
#تعریف_کرو AT91C_US0_RCR           ( 0xFFFC0104 ) /* (PDC_US0) Receive Counter Register */
/* ========== Register definition for US0 peripheral ========== */
#تعریف_کرو AT91C_US0_TTGR          ( 0xFFFC0028 ) /* (US0) Transmitter Time-guard Register */
#تعریف_کرو AT91C_US0_BRGR          ( 0xFFFC0020 ) /* (US0) Baud Rate Generator Register */
#تعریف_کرو AT91C_US0_RHR           ( 0xFFFC0018 ) /* (US0) Receiver Holding Register */
#تعریف_کرو AT91C_US0_IMR           ( 0xFFFC0010 ) /* (US0) Interrupt Mask Register */
#تعریف_کرو AT91C_US0_NER           ( 0xFFFC0044 ) /* (US0) Nb Errors Register */
#تعریف_کرو AT91C_US0_RTOR          ( 0xFFFC0024 ) /* (US0) Receiver Time-out Register */
#تعریف_کرو AT91C_US0_XXR           ( 0xFFFC0048 ) /* (US0) XON_XOFF Register */
#تعریف_کرو AT91C_US0_FIDI          ( 0xFFFC0040 ) /* (US0) FI_DI_Ratio Register */
#تعریف_کرو AT91C_US0_CR            ( 0xFFFC0000 ) /* (US0) Control Register */
#تعریف_کرو AT91C_US0_IER           ( 0xFFFC0008 ) /* (US0) Interrupt Enable Register */
#تعریف_کرو AT91C_US0_IF            ( 0xFFFC004C ) /* (US0) IRDA_FILTER Register */
#تعریف_کرو AT91C_US0_MR            ( 0xFFFC0004 ) /* (US0) Mode Register */
#تعریف_کرو AT91C_US0_IDR           ( 0xFFFC000C ) /* (US0) Interrupt Disable Register */
#تعریف_کرو AT91C_US0_CSR           ( 0xFFFC0014 ) /* (US0) Channel Status Register */
#تعریف_کرو AT91C_US0_THR           ( 0xFFFC001C ) /* (US0) Transmitter Holding Register */
/* ========== Register definition for TWI peripheral ========== */
#تعریف_کرو AT91C_TWI_RHR           ( 0xFFFB8030 ) /* (TWI) Receive Holding Register */
#تعریف_کرو AT91C_TWI_IDR           ( 0xFFFB8028 ) /* (TWI) Interrupt Disable Register */
#تعریف_کرو AT91C_TWI_SR            ( 0xFFFB8020 ) /* (TWI) Status Register */
#تعریف_کرو AT91C_TWI_CWGR          ( 0xFFFB8010 ) /* (TWI) Clock Waveform Generator Register */
#تعریف_کرو AT91C_TWI_SMR           ( 0xFFFB8008 ) /* (TWI) Slave Mode Register */
#تعریف_کرو AT91C_TWI_CR            ( 0xFFFB8000 ) /* (TWI) Control Register */
#تعریف_کرو AT91C_TWI_THR           ( 0xFFFB8034 ) /* (TWI) Transmit Holding Register */
#تعریف_کرو AT91C_TWI_IMR           ( 0xFFFB802C ) /* (TWI) Interrupt Mask Register */
#تعریف_کرو AT91C_TWI_IER           ( 0xFFFB8024 ) /* (TWI) Interrupt Enable Register */
#تعریف_کرو AT91C_TWI_IADR          ( 0xFFFB800C ) /* (TWI) Internal Address Register */
#تعریف_کرو AT91C_TWI_MMR           ( 0xFFFB8004 ) /* (TWI) Master Mode Register */
/* ========== Register definition for TC2 peripheral ========== */
#تعریف_کرو AT91C_TC2_IMR           ( 0xFFFA00AC ) /* (TC2) Interrupt Mask Register */
#تعریف_کرو AT91C_TC2_IER           ( 0xFFFA00A4 ) /* (TC2) Interrupt Enable Register */
#تعریف_کرو AT91C_TC2_RC            ( 0xFFFA009C ) /* (TC2) Register C */
#تعریف_کرو AT91C_TC2_RA            ( 0xFFFA0094 ) /* (TC2) Register A */
#تعریف_کرو AT91C_TC2_CMR           ( 0xFFFA0084 ) /* (TC2) Channel Mode Register (Capture Mode / Waveform Mode) */
#تعریف_کرو AT91C_TC2_IDR           ( 0xFFFA00A8 ) /* (TC2) Interrupt Disable Register */
#تعریف_کرو AT91C_TC2_SR            ( 0xFFFA00A0 ) /* (TC2) Status Register */
#تعریف_کرو AT91C_TC2_RB            ( 0xFFFA0098 ) /* (TC2) Register B */
#تعریف_کرو AT91C_TC2_CV            ( 0xFFFA0090 ) /* (TC2) Counter Value */
#تعریف_کرو AT91C_TC2_CCR           ( 0xFFFA0080 ) /* (TC2) Channel Control Register */
/* ========== Register definition for TC1 peripheral ========== */
#تعریف_کرو AT91C_TC1_IMR           ( 0xFFFA006C ) /* (TC1) Interrupt Mask Register */
#تعریف_کرو AT91C_TC1_IER           ( 0xFFFA0064 ) /* (TC1) Interrupt Enable Register */
#تعریف_کرو AT91C_TC1_RC            ( 0xFFFA005C ) /* (TC1) Register C */
#تعریف_کرو AT91C_TC1_RA            ( 0xFFFA0054 ) /* (TC1) Register A */
#تعریف_کرو AT91C_TC1_CMR           ( 0xFFFA0044 ) /* (TC1) Channel Mode Register (Capture Mode / Waveform Mode) */
#تعریف_کرو AT91C_TC1_IDR           ( 0xFFFA0068 ) /* (TC1) Interrupt Disable Register */
#تعریف_کرو AT91C_TC1_SR            ( 0xFFFA0060 ) /* (TC1) Status Register */
#تعریف_کرو AT91C_TC1_RB            ( 0xFFFA0058 ) /* (TC1) Register B */
#تعریف_کرو AT91C_TC1_CV            ( 0xFFFA0050 ) /* (TC1) Counter Value */
#تعریف_کرو AT91C_TC1_CCR           ( 0xFFFA0040 ) /* (TC1) Channel Control Register */
/* ========== Register definition for TC0 peripheral ========== */
#تعریف_کرو AT91C_TC0_IMR           ( 0xFFFA002C ) /* (TC0) Interrupt Mask Register */
#تعریف_کرو AT91C_TC0_IER           ( 0xFFFA0024 ) /* (TC0) Interrupt Enable Register */
#تعریف_کرو AT91C_TC0_RC            ( 0xFFFA001C ) /* (TC0) Register C */
#تعریف_کرو AT91C_TC0_RA            ( 0xFFFA0014 ) /* (TC0) Register A */
#تعریف_کرو AT91C_TC0_CMR           ( 0xFFFA0004 ) /* (TC0) Channel Mode Register (Capture Mode / Waveform Mode) */
#تعریف_کرو AT91C_TC0_IDR           ( 0xFFFA0028 ) /* (TC0) Interrupt Disable Register */
#تعریف_کرو AT91C_TC0_SR            ( 0xFFFA0020 ) /* (TC0) Status Register */
#تعریف_کرو AT91C_TC0_RB            ( 0xFFFA0018 ) /* (TC0) Register B */
#تعریف_کرو AT91C_TC0_CV            ( 0xFFFA0010 ) /* (TC0) Counter Value */
#تعریف_کرو AT91C_TC0_CCR           ( 0xFFFA0000 ) /* (TC0) Channel Control Register */
/* ========== Register definition for TCB peripheral ========== */
#تعریف_کرو AT91C_TCB_BMR           ( 0xFFFA00C4 ) /* (TCB) TC Block Mode Register */
#تعریف_کرو AT91C_TCB_BCR           ( 0xFFFA00C0 ) /* (TCB) TC Block Control Register */
/* ========== Register definition for PWMC_CH3 peripheral ========== */
#تعریف_کرو AT91C_CH3_CUPDR         ( 0xFFFCC270 ) /* (PWMC_CH3) Channel Update Register */
#تعریف_کرو AT91C_CH3_CPRDR         ( 0xFFFCC268 ) /* (PWMC_CH3) Channel Period Register */
#تعریف_کرو AT91C_CH3_CMR           ( 0xFFFCC260 ) /* (PWMC_CH3) Channel Mode Register */
#تعریف_کرو AT91C_CH3_Reserved      ( 0xFFFCC274 ) /* (PWMC_CH3) Reserved */
#تعریف_کرو AT91C_CH3_CCNTR         ( 0xFFFCC26C ) /* (PWMC_CH3) Channel Counter Register */
#تعریف_کرو AT91C_CH3_CDTYR         ( 0xFFFCC264 ) /* (PWMC_CH3) Channel Duty Cycle Register */
/* ========== Register definition for PWMC_CH2 peripheral ========== */
#تعریف_کرو AT91C_CH2_CUPDR         ( 0xFFFCC250 ) /* (PWMC_CH2) Channel Update Register */
#تعریف_کرو AT91C_CH2_CPRDR         ( 0xFFFCC248 ) /* (PWMC_CH2) Channel Period Register */
#تعریف_کرو AT91C_CH2_CMR           ( 0xFFFCC240 ) /* (PWMC_CH2) Channel Mode Register */
#تعریف_کرو AT91C_CH2_Reserved      ( 0xFFFCC254 ) /* (PWMC_CH2) Reserved */
#تعریف_کرو AT91C_CH2_CCNTR         ( 0xFFFCC24C ) /* (PWMC_CH2) Channel Counter Register */
#تعریف_کرو AT91C_CH2_CDTYR         ( 0xFFFCC244 ) /* (PWMC_CH2) Channel Duty Cycle Register */
/* ========== Register definition for PWMC_CH1 peripheral ========== */
#تعریف_کرو AT91C_CH1_CUPDR         ( 0xFFFCC230 ) /* (PWMC_CH1) Channel Update Register */
#تعریف_کرو AT91C_CH1_CPRDR         ( 0xFFFCC228 ) /* (PWMC_CH1) Channel Period Register */
#تعریف_کرو AT91C_CH1_CMR           ( 0xFFFCC220 ) /* (PWMC_CH1) Channel Mode Register */
#تعریف_کرو AT91C_CH1_Reserved      ( 0xFFFCC234 ) /* (PWMC_CH1) Reserved */
#تعریف_کرو AT91C_CH1_CCNTR         ( 0xFFFCC22C ) /* (PWMC_CH1) Channel Counter Register */
#تعریف_کرو AT91C_CH1_CDTYR         ( 0xFFFCC224 ) /* (PWMC_CH1) Channel Duty Cycle Register */
/* ========== Register definition for PWMC_CH0 peripheral ========== */
#تعریف_کرو AT91C_CH0_CUPDR         ( 0xFFFCC210 ) /* (PWMC_CH0) Channel Update Register */
#تعریف_کرو AT91C_CH0_CPRDR         ( 0xFFFCC208 ) /* (PWMC_CH0) Channel Period Register */
#تعریف_کرو AT91C_CH0_CMR           ( 0xFFFCC200 ) /* (PWMC_CH0) Channel Mode Register */
#تعریف_کرو AT91C_CH0_Reserved      ( 0xFFFCC214 ) /* (PWMC_CH0) Reserved */
#تعریف_کرو AT91C_CH0_CCNTR         ( 0xFFFCC20C ) /* (PWMC_CH0) Channel Counter Register */
#تعریف_کرو AT91C_CH0_CDTYR         ( 0xFFFCC204 ) /* (PWMC_CH0) Channel Duty Cycle Register */
/* ========== Register definition for PWMC peripheral ========== */
#تعریف_کرو AT91C_PWMC_VR           ( 0xFFFCC0FC ) /* (PWMC) PWMC Version Register */
#تعریف_کرو AT91C_PWMC_ISR          ( 0xFFFCC01C ) /* (PWMC) PWMC Interrupt Status Register */
#تعریف_کرو AT91C_PWMC_IDR          ( 0xFFFCC014 ) /* (PWMC) PWMC Interrupt Disable Register */
#تعریف_کرو AT91C_PWMC_SR           ( 0xFFFCC00C ) /* (PWMC) PWMC Status Register */
#تعریف_کرو AT91C_PWMC_ENA          ( 0xFFFCC004 ) /* (PWMC) PWMC Enable Register */
#تعریف_کرو AT91C_PWMC_IMR          ( 0xFFFCC018 ) /* (PWMC) PWMC Interrupt Mask Register */
#تعریف_کرو AT91C_PWMC_MR           ( 0xFFFCC000 ) /* (PWMC) PWMC Mode Register */
#تعریف_کرو AT91C_PWMC_DIS          ( 0xFFFCC008 ) /* (PWMC) PWMC Disable Register */
#تعریف_کرو AT91C_PWMC_IER          ( 0xFFFCC010 ) /* (PWMC) PWMC Interrupt Enable Register */
/* ========== Register definition for UDP peripheral ========== */
#تعریف_کرو AT91C_UDP_ISR           ( 0xFFFB001C ) /* (UDP) Interrupt Status Register */
#تعریف_کرو AT91C_UDP_IDR           ( 0xFFFB0014 ) /* (UDP) Interrupt Disable Register */
#تعریف_کرو AT91C_UDP_GLBSTATE      ( 0xFFFB0004 ) /* (UDP) Global State Register */
#تعریف_کرو AT91C_UDP_FDR           ( 0xFFFB0050 ) /* (UDP) Endpoint FIFO Data Register */
#تعریف_کرو AT91C_UDP_CSR           ( 0xFFFB0030 ) /* (UDP) Endpoint Control and Status Register */
#تعریف_کرو AT91C_UDP_RSTEP         ( 0xFFFB0028 ) /* (UDP) Reset Endpoint Register */
#تعریف_کرو AT91C_UDP_ICR           ( 0xFFFB0020 ) /* (UDP) Interrupt Clear Register */
#تعریف_کرو AT91C_UDP_IMR           ( 0xFFFB0018 ) /* (UDP) Interrupt Mask Register */
#تعریف_کرو AT91C_UDP_IER           ( 0xFFFB0010 ) /* (UDP) Interrupt Enable Register */
#تعریف_کرو AT91C_UDP_FADDR         ( 0xFFFB0008 ) /* (UDP) Function Address Register */
#تعریف_کرو AT91_C_UDP_عدد           ( 0xFFFB0000 ) /* (UDP) Frame Number Register */

/* ***************************************************************************** */
/*               PIO DEFINITIONS FOR AT91SAM7S64 */
/* ***************************************************************************** */
#تعریف_کرو AT91C_PIO_PA0       ( 1 << 0 )         /* Pin Controlled by PA0 */
#تعریف_کرو AT91C_PA0_PWM0      ( AT91C_PIO_PA0 )  /*  PWM Channel 0 */
#تعریف_کرو AT91C_PA0_TIOA0     ( AT91C_PIO_PA0 )  /*  Timer Counter 0 Multipurpose Timer I/O Pin A */
#تعریف_کرو AT91C_PIO_PA1       ( 1 << 1 )         /* Pin Controlled by PA1 */
#تعریف_کرو AT91C_PA1_PWM1      ( AT91C_PIO_PA1 )  /*  PWM Channel 1 */
#تعریف_کرو AT91C_PA1_TIOB0     ( AT91C_PIO_PA1 )  /*  Timer Counter 0 Multipurpose Timer I/O Pin B */
#تعریف_کرو AT91C_PIO_PA10      ( 1 << 10 )        /* Pin Controlled by PA10 */
#تعریف_کرو AT91C_PA10_DTXD     ( AT91C_PIO_PA10 ) /*  DBGU Debug Transmit Data */
#تعریف_کرو AT91C_PA10_NPCS2    ( AT91C_PIO_PA10 ) /*  SPI Peripheral Chip Select 2 */
#تعریف_کرو AT91C_PIO_PA11      ( 1 << 11 )        /* Pin Controlled by PA11 */
#تعریف_کرو AT91C_PA11_NPCS0    ( AT91C_PIO_PA11 ) /*  SPI Peripheral Chip Select 0 */
#تعریف_کرو AT91C_PA11_PWM0     ( AT91C_PIO_PA11 ) /*  PWM Channel 0 */
#تعریف_کرو AT91C_PIO_PA12      ( 1 << 12 )        /* Pin Controlled by PA12 */
#تعریف_کرو AT91C_PA12_MISO     ( AT91C_PIO_PA12 ) /*  SPI Master In Slave */
#تعریف_کرو AT91C_PA12_PWM1     ( AT91C_PIO_PA12 ) /*  PWM Channel 1 */
#تعریف_کرو AT91C_PIO_PA13      ( 1 << 13 )        /* Pin Controlled by PA13 */
#تعریف_کرو AT91C_PA13_MOSI     ( AT91C_PIO_PA13 ) /*  SPI Master Out Slave */
#تعریف_کرو AT91C_PA13_PWM2     ( AT91C_PIO_PA13 ) /*  PWM Channel 2 */
#تعریف_کرو AT91C_PIO_PA14      ( 1 << 14 )        /* Pin Controlled by PA14 */
#تعریف_کرو AT91C_PA14_SPCK     ( AT91C_PIO_PA14 ) /*  SPI Serial Clock */
#تعریف_کرو AT91C_PA14_PWM3     ( AT91C_PIO_PA14 ) /*  PWM Channel 3 */
#تعریف_کرو AT91C_PIO_PA15      ( 1 << 15 )        /* Pin Controlled by PA15 */
#تعریف_کرو AT91C_PA15_TF       ( AT91C_PIO_PA15 ) /*  SSC Transmit Frame Sync */
#تعریف_کرو AT91C_PA15_TIOA1    ( AT91C_PIO_PA15 ) /*  Timer Counter 1 Multipurpose Timer I/O Pin A */
#تعریف_کرو AT91C_PIO_PA16      ( 1 << 16 )        /* Pin Controlled by PA16 */
#تعریف_کرو AT91C_PA16_TK       ( AT91C_PIO_PA16 ) /*  SSC Transmit Clock */
#تعریف_کرو AT91C_PA16_TIOB1    ( AT91C_PIO_PA16 ) /*  Timer Counter 1 Multipurpose Timer I/O Pin B */
#تعریف_کرو AT91C_PIO_PA17      ( 1 << 17 )        /* Pin Controlled by PA17 */
#تعریف_کرو AT91C_PA17_TD       ( AT91C_PIO_PA17 ) /*  SSC Transmit data */
#تعریف_کرو AT91C_PA17_PCK1     ( AT91C_PIO_PA17 ) /*  PMC Programmable Clock Output 1 */
#تعریف_کرو AT91C_PIO_PA18      ( 1 << 18 )        /* Pin Controlled by PA18 */
#تعریف_کرو AT91C_PA18_RD       ( AT91C_PIO_PA18 ) /*  SSC Receive Data */
#تعریف_کرو AT91C_PA18_PCK2     ( AT91C_PIO_PA18 ) /*  PMC Programmable Clock Output 2 */
#تعریف_کرو AT91C_PIO_PA19      ( 1 << 19 )        /* Pin Controlled by PA19 */
#تعریف_کرو AT91C_PA19_RK       ( AT91C_PIO_PA19 ) /*  SSC Receive Clock */
#تعریف_کرو AT91C_PA19_FIQ      ( AT91C_PIO_PA19 ) /*  AIC Fast Interrupt Input */
#تعریف_کرو AT91C_PIO_PA2       ( 1 << 2 )         /* Pin Controlled by PA2 */
#تعریف_کرو AT91C_PA2_PWM2      ( AT91C_PIO_PA2 )  /*  PWM Channel 2 */
#تعریف_کرو AT91C_PA2_SCK0      ( AT91C_PIO_PA2 )  /*  USART 0 Serial Clock */
#تعریف_کرو AT91C_PIO_PA20      ( 1 << 20 )        /* Pin Controlled by PA20 */
#تعریف_کرو AT91C_PA20_RF       ( AT91C_PIO_PA20 ) /*  SSC Receive Frame Sync */
#تعریف_کرو AT91C_PA20_IRQ0     ( AT91C_PIO_PA20 ) /*  External Interrupt 0 */
#تعریف_کرو AT91C_PIO_PA21      ( 1 << 21 )        /* Pin Controlled by PA21 */
#تعریف_کرو AT91C_PA21_RXD1     ( AT91C_PIO_PA21 ) /*  USART 1 Receive Data */
#تعریف_کرو AT91C_PA21_PCK1     ( AT91C_PIO_PA21 ) /*  PMC Programmable Clock Output 1 */
#تعریف_کرو AT91C_PIO_PA22      ( 1 << 22 )        /* Pin Controlled by PA22 */
#تعریف_کرو AT91C_PA22_TXD1     ( AT91C_PIO_PA22 ) /*  USART 1 Transmit Data */
#تعریف_کرو AT91C_PA22_NPCS3    ( AT91C_PIO_PA22 ) /*  SPI Peripheral Chip Select 3 */
#تعریف_کرو AT91C_PIO_PA23      ( 1 << 23 )        /* Pin Controlled by PA23 */
#تعریف_کرو AT91C_PA23_SCK1     ( AT91C_PIO_PA23 ) /*  USART 1 Serial Clock */
#تعریف_کرو AT91C_PA23_PWM0     ( AT91C_PIO_PA23 ) /*  PWM Channel 0 */
#تعریف_کرو AT91C_PIO_PA24      ( 1 << 24 )        /* Pin Controlled by PA24 */
#تعریف_کرو AT91C_PA24_RTS1     ( AT91C_PIO_PA24 ) /*  USART 1 Ready To Send */
#تعریف_کرو AT91C_PA24_PWM1     ( AT91C_PIO_PA24 ) /*  PWM Channel 1 */
#تعریف_کرو AT91C_PIO_PA25      ( 1 << 25 )        /* Pin Controlled by PA25 */
#تعریف_کرو AT91C_PA25_CTS1     ( AT91C_PIO_PA25 ) /*  USART 1 Clear To Send */
#تعریف_کرو AT91C_PA25_PWM2     ( AT91C_PIO_PA25 ) /*  PWM Channel 2 */
#تعریف_کرو AT91C_PIO_PA26      ( 1 << 26 )        /* Pin Controlled by PA26 */
#تعریف_کرو AT91C_PA26_DCD1     ( AT91C_PIO_PA26 ) /*  USART 1 Data Carrier Detect */
#تعریف_کرو AT91C_PA26_TIOA2    ( AT91C_PIO_PA26 ) /*  Timer Counter 2 Multipurpose Timer I/O Pin A */
#تعریف_کرو AT91C_PIO_PA27      ( 1 << 27 )        /* Pin Controlled by PA27 */
#تعریف_کرو AT91C_PA27_DTR1     ( AT91C_PIO_PA27 ) /*  USART 1 Data Terminal ready */
#تعریف_کرو AT91C_PA27_TIOB2    ( AT91C_PIO_PA27 ) /*  Timer Counter 2 Multipurpose Timer I/O Pin B */
#تعریف_کرو AT91C_PIO_PA28      ( 1 << 28 )        /* Pin Controlled by PA28 */
#تعریف_کرو AT91C_PA28_DSR1     ( AT91C_PIO_PA28 ) /*  USART 1 Data Set ready */
#تعریف_کرو AT91C_PA28_TCLK1    ( AT91C_PIO_PA28 ) /*  Timer Counter 1 external clock input */
#تعریف_کرو AT91C_PIO_PA29      ( 1 << 29 )        /* Pin Controlled by PA29 */
#تعریف_کرو AT91C_PA29_RI1      ( AT91C_PIO_PA29 ) /*  USART 1 Ring Indicator */
#تعریف_کرو AT91C_PA29_TCLK2    ( AT91C_PIO_PA29 ) /*  Timer Counter 2 external clock input */
#تعریف_کرو AT91C_PIO_PA3       ( 1 << 3 )         /* Pin Controlled by PA3 */
#تعریف_کرو AT91C_PA3_TWD       ( AT91C_PIO_PA3 )  /*  TWI Two-wire Serial Data */
#تعریف_کرو AT91C_PA3_NPCS3     ( AT91C_PIO_PA3 )  /*  SPI Peripheral Chip Select 3 */
#تعریف_کرو AT91C_PIO_PA30      ( 1 << 30 )        /* Pin Controlled by PA30 */
#تعریف_کرو AT91C_PA30_IRQ1     ( AT91C_PIO_PA30 ) /*  External Interrupt 1 */
#تعریف_کرو AT91C_PA30_NPCS2    ( AT91C_PIO_PA30 ) /*  SPI Peripheral Chip Select 2 */
#تعریف_کرو AT91C_PIO_PA31      ( 1 << 31 )        /* Pin Controlled by PA31 */
#تعریف_کرو AT91C_PA31_NPCS1    ( AT91C_PIO_PA31 ) /*  SPI Peripheral Chip Select 1 */
#تعریف_کرو AT91C_PA31_PCK2     ( AT91C_PIO_PA31 ) /*  PMC Programmable Clock Output 2 */
#تعریف_کرو AT91C_PIO_PA4       ( 1 << 4 )         /* Pin Controlled by PA4 */
#تعریف_کرو AT91C_PA4_TWCK      ( AT91C_PIO_PA4 )  /*  TWI Two-wire Serial Clock */
#تعریف_کرو AT91C_PA4_TCLK0     ( AT91C_PIO_PA4 )  /*  Timer Counter 0 external clock input */
#تعریف_کرو AT91C_PIO_PA5       ( 1 << 5 )         /* Pin Controlled by PA5 */
#تعریف_کرو AT91C_PA5_RXD0      ( AT91C_PIO_PA5 )  /*  USART 0 Receive Data */
#تعریف_کرو AT91C_PA5_NPCS3     ( AT91C_PIO_PA5 )  /*  SPI Peripheral Chip Select 3 */
#تعریف_کرو AT91C_PIO_PA6       ( 1 << 6 )         /* Pin Controlled by PA6 */
#تعریف_کرو AT91C_PA6_TXD0      ( AT91C_PIO_PA6 )  /*  USART 0 Transmit Data */
#تعریف_کرو AT91C_PA6_PCK0      ( AT91C_PIO_PA6 )  /*  PMC Programmable Clock Output 0 */
#تعریف_کرو AT91C_PIO_PA7       ( 1 << 7 )         /* Pin Controlled by PA7 */
#تعریف_کرو AT91C_PA7_RTS0      ( AT91C_PIO_PA7 )  /*  USART 0 Ready To Send */
#تعریف_کرو AT91C_PA7_PWM3      ( AT91C_PIO_PA7 )  /*  PWM Channel 3 */
#تعریف_کرو AT91C_PIO_PA8       ( 1 << 8 )         /* Pin Controlled by PA8 */
#تعریف_کرو AT91C_PA8_CTS0      ( AT91C_PIO_PA8 )  /*  USART 0 Clear To Send */
#تعریف_کرو AT91C_PA8_ADTRG     ( AT91C_PIO_PA8 )  /*  ADC External Trigger */
#تعریف_کرو AT91C_PIO_PA9       ( 1 << 9 )         /* Pin Controlled by PA9 */
#تعریف_کرو AT91C_PA9_DRXD      ( AT91C_PIO_PA9 )  /*  DBGU Debug Receive Data */
#تعریف_کرو AT91C_PA9_NPCS1     ( AT91C_PIO_PA9 )  /*  SPI Peripheral Chip Select 1 */

/* ***************************************************************************** */
/*               PERIPHERAL ID DEFINITIONS FOR AT91SAM7S64 */
/* ***************************************************************************** */
#تعریف_کرو AT91C_ID_FIQ            ( 0 )  /* Advanced Interrupt Controller (FIQ) */
#تعریف_کرو AT91C_ID_SYS            ( 1 )  /* System Peripheral */
#تعریف_کرو AT91C_ID_PIOA           ( 2 )  /* Parallel IO Controller */
#تعریف_کرو AT91C_ID_3_Reserved     ( 3 )  /* Reserved */
#تعریف_کرو AT91C_ID_ADC            ( 4 )  /* Analog-to-Digital Converter */
#تعریف_کرو AT91C_ID_SPI            ( 5 )  /* Serial Peripheral Interface */
#تعریف_کرو AT91C_ID_US0            ( 6 )  /* USART 0 */
#تعریف_کرو AT91C_ID_US1            ( 7 )  /* USART 1 */
#تعریف_کرو AT91C_ID_SSC            ( 8 )  /* Serial Synchronous Controller */
#تعریف_کرو AT91C_ID_TWI            ( 9 )  /* Two-Wire Interface */
#تعریف_کرو AT91C_ID_PWMC           ( 10 ) /* PWM Controller */
#تعریف_کرو AT91C_ID_UDP            ( 11 ) /* USB Device Port */
#تعریف_کرو AT91C_ID_TC0            ( 12 ) /* Timer Counter 0 */
#تعریف_کرو AT91C_ID_TC1            ( 13 ) /* Timer Counter 1 */
#تعریف_کرو AT91C_ID_TC2            ( 14 ) /* Timer Counter 2 */
#تعریف_کرو AT91C_ID_15_Reserved    ( 15 ) /* Reserved */
#تعریف_کرو AT91C_ID_16_Reserved    ( 16 ) /* Reserved */
#تعریف_کرو AT91C_ID_17_Reserved    ( 17 ) /* Reserved */
#تعریف_کرو AT91C_ID_18_Reserved    ( 18 ) /* Reserved */
#تعریف_کرو AT91C_ID_19_Reserved    ( 19 ) /* Reserved */
#تعریف_کرو AT91C_ID_20_Reserved    ( 20 ) /* Reserved */
#تعریف_کرو AT91C_ID_21_Reserved    ( 21 ) /* Reserved */
#تعریف_کرو AT91C_ID_22_Reserved    ( 22 ) /* Reserved */
#تعریف_کرو AT91C_ID_23_Reserved    ( 23 ) /* Reserved */
#تعریف_کرو AT91C_ID_24_Reserved    ( 24 ) /* Reserved */
#تعریف_کرو AT91C_ID_25_Reserved    ( 25 ) /* Reserved */
#تعریف_کرو AT91C_ID_26_Reserved    ( 26 ) /* Reserved */
#تعریف_کرو AT91C_ID_27_Reserved    ( 27 ) /* Reserved */
#تعریف_کرو AT91C_ID_28_Reserved    ( 28 ) /* Reserved */
#تعریف_کرو AT91C_ID_29_Reserved    ( 29 ) /* Reserved */
#تعریف_کرو AT91C_ID_IRQ0           ( 30 ) /* Advanced Interrupt Controller (IRQ0) */
#تعریف_کرو AT91C_ID_IRQ1           ( 31 ) /* Advanced Interrupt Controller (IRQ1) */

/* ***************************************************************************** */
/*               BASE ADDRESS DEFINITIONS FOR AT91SAM7S64 */
/* ***************************************************************************** */
#تعریف_کرو AT91_C_بنیاد_SYSC        ( 0xFFFFF000 )  /* (SYSC) Base Address */
#تعریف_کرو AT91_C_بنیاد_AIC         ( 0xFFFFF000 )  /* (AIC) Base Address */
#تعریف_کرو AT91_C_بنیاد_DBGU        ( 0xFFFFF200 )  /* (DBGU) Base Address */
#تعریف_کرو AT91_C_بنیاد_PDC_DBGU    ( 0xFFFFF300 )  /* (PDC_DBGU) Base Address */
#تعریف_کرو AT91_C_بنیاد_PIOA        ( 0xFFFFF400 )  /* (PIOA) Base Address */
#تعریف_کرو AT91_C_بنیاد_CKGR        ( 0xFFFFFC20 )  /* (CKGR) Base Address */
#تعریف_کرو AT91_C_بنیاد_PMC         ( 0xFFFFFC00 )  /* (PMC) Base Address */
#تعریف_کرو AT91_C_بنیاد_RSTC        ( 0xFFFFFD00 )  /* (RSTC) Base Address */
#تعریف_کرو AT91_C_بنیاد_RTTC        ( 0xFFFFFD20 )  /* (RTTC) Base Address */
#تعریف_کرو AT91_C_بنیاد_PITC        ( 0xFFFFFD30 )  /* (PITC) Base Address */
#تعریف_کرو AT91_C_بنیاد_WDTC        ( 0xFFFFFD40 )  /* (WDTC) Base Address */
#تعریف_کرو AT91_C_بنیاد_MC          ( 0xFFFFFF00 )  /* (MC) Base Address */
#تعریف_کرو AT91_C_بنیاد_PDC_SPI     ( 0xFFFE0100 )  /* (PDC_SPI) Base Address */
#تعریف_کرو AT91_C_بنیاد_SPI         ( 0xFFFE0000 )  /* (SPI) Base Address */
#تعریف_کرو AT91_C_بنیاد_PDC_ADC     ( 0xFFFD8100 )  /* (PDC_ADC) Base Address */
#تعریف_کرو AT91_C_بنیاد_ADC         ( 0xFFFD8000 )  /* (ADC) Base Address */
#تعریف_کرو AT91_C_بنیاد_PDC_SSC     ( 0xFFFD4100 )  /* (PDC_SSC) Base Address */
#تعریف_کرو AT91_C_بنیاد_SSC         ( 0xFFFD4000 )  /* (SSC) Base Address */
#تعریف_کرو AT91_C_بنیاد_PDC_US1     ( 0xFFFC4100 )  /* (PDC_US1) Base Address */
#تعریف_کرو AT91_C_بنیاد_US1         ( 0xFFFC4000 )  /* (US1) Base Address */
#تعریف_کرو AT91_C_بنیاد_PDC_US0     ( 0xFFFC0100 )  /* (PDC_US0) Base Address */
#تعریف_کرو AT91_C_بنیاد_US0         ( 0xFFFC0000 )  /* (US0) Base Address */
#تعریف_کرو AT91_C_بنیاد_TWI         ( 0xFFFB8000 )  /* (TWI) Base Address */
#تعریف_کرو AT91_C_بنیاد_TC2         ( 0xFFFA0080 )  /* (TC2) Base Address */
#تعریف_کرو AT91_C_بنیاد_TC1         ( 0xFFFA0040 )  /* (TC1) Base Address */
#تعریف_کرو AT91_C_بنیاد_TC0         ( 0xFFFA0000 )  /* (TC0) Base Address */
#تعریف_کرو AT91_C_بنیاد_TCB         ( 0xFFFA0000 )  /* (TCB) Base Address */
#تعریف_کرو AT91_C_بنیاد_PWMC_CH3    ( 0xFFFCC260 )  /* (PWMC_CH3) Base Address */
#تعریف_کرو AT91_C_بنیاد_PWMC_CH2    ( 0xFFFCC240 )  /* (PWMC_CH2) Base Address */
#تعریف_کرو AT91_C_بنیاد_PWMC_CH1    ( 0xFFFCC220 )  /* (PWMC_CH1) Base Address */
#تعریف_کرو AT91_C_بنیاد_PWMC_CH0    ( 0xFFFCC200 )  /* (PWMC_CH0) Base Address */
#تعریف_کرو AT91_C_بنیاد_PWMC        ( 0xFFFCC000 )  /* (PWMC) Base Address */
#تعریف_کرو AT91_C_بنیاد_UDP         ( 0xFFFB0000 )  /* (UDP) Base Address */

/* ***************************************************************************** */
/*               MEMORY MAPPING DEFINITIONS FOR AT91SAM7S64 */
/* ***************************************************************************** */
#تعریف_کرو AT91C_ISRAM          ( 0x00200000 )    /* Internal SRAM base address */
#تعریف_کرو AT91_C_ISRAM_سائز     ( 0x00004000 )    /* Internal SRAM size in byte (16 Kbyte) */
#تعریف_کرو AT91C_IFLASH         ( 0x00100000 )    /* Internal ROM base address */
#تعریف_کرو AT91_C_IFLASH_سائز    ( 0x00010000 )    /* Internal ROM size in byte (64 Kbyte) */
