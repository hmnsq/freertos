/*  ---------------------------------------------------------------------------- */
/*          ATMEL Microcontroller Software Support  -  ROUSSET  - */
/*  ---------------------------------------------------------------------------- */
/*  DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR */
/*  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE */
/*  DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT, */
/*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, */
/*  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF */
/*  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING */
/*  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/*  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
/*  ---------------------------------------------------------------------------- */
/* File Name           : AT91SAM7X128.h */
/* Object              : AT91SAM7X128 definitions */
/* Generated           : AT91 SW Application Group  05/20/2005 (16:22:23) */
/* */
/* CVS Reference       : /AT91SAM7X128.pl/1.14/Tue May 10 12:12:05 2005// */
/* CVS Reference       : /SYS_SAM7X.pl/1.3/Tue Feb  1 17:01:43 2005// */
/* CVS Reference       : /MC_SAM7X.pl/1.2/Fri May 20 14:13:04 2005// */
/* CVS Reference       : /PMC_SAM7X.pl/1.4/Tue Feb  8 13:58:10 2005// */
/* CVS Reference       : /RSTC_SAM7X.pl/1.1/Tue Feb  1 16:16:26 2005// */
/* CVS Reference       : /UDP_SAM7X.pl/1.1/Tue May 10 11:35:35 2005// */
/* CVS Reference       : /PWM_SAM7X.pl/1.1/Tue May 10 11:53:07 2005// */
/* CVS Reference       : /AIC_6075B.pl/1.3/Fri May 20 14:01:30 2005// */
/* CVS Reference       : /PIO_6057A.pl/1.2/Thu Feb  3 10:18:28 2005// */
/* CVS Reference       : /RTTC_6081A.pl/1.2/Tue Nov  9 14:43:58 2004// */
/* CVS Reference       : /PITC_6079A.pl/1.2/Tue Nov  9 14:43:56 2004// */
/* CVS Reference       : /WDTC_6080A.pl/1.3/Tue Nov  9 14:44:00 2004// */
/* CVS Reference       : /VREG_6085B.pl/1.1/Tue Feb  1 16:05:48 2005// */
/* CVS Reference       : /PDC_6074C.pl/1.2/Thu Feb  3 08:48:54 2005// */
/* CVS Reference       : /DBGU_6059D.pl/1.1/Mon Jan 31 13:15:32 2005// */
/* CVS Reference       : /SPI_6088D.pl/1.3/Fri May 20 14:08:59 2005// */
/* CVS Reference       : /US_6089C.pl/1.1/Mon Jul 12 18:23:26 2004// */
/* CVS Reference       : /SSC_6078A.pl/1.1/Tue Jul 13 07:45:40 2004// */
/* CVS Reference       : /TWI_6061A.pl/1.1/Tue Jul 13 07:38:06 2004// */
/* CVS Reference       : /TC_6082A.pl/1.7/Fri Mar 11 12:52:17 2005// */
/* CVS Reference       : /CAN_6019B.pl/1.1/Tue Mar  8 12:42:22 2005// */
/* CVS Reference       : /EMACB_6119A.pl/1.5/Thu Feb  3 15:52:04 2005// */
/* CVS Reference       : /ADC_6051C.pl/1.1/Fri Oct 17 09:12:38 2003// */
/* CVS Reference       : /AES_6149A.pl/1.10/Mon Feb  7 09:44:25 2005// */
/* CVS Reference       : /DES3_6150A.pl/1.1/Mon Jan 17 08:34:31 2005// */
/*  ---------------------------------------------------------------------------- */

/* Hardware register definition */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR System Peripherals */
/* ***************************************************************************** */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Advanced Interrupt Controller */
/* ***************************************************************************** */
/* *** Register offset in AT91S_AIC structure *** */
#وصف_ڪريو AIC_SMR                                    ( 0 )        /* Source Mode Register */
#وصف_ڪريو AIC_SVR                                    ( 128 )      /* Source Vector Register */
#وصف_ڪريو AIC_IVR                                    ( 256 )      /* IRQ Vector Register */
#وصف_ڪريو AIC_FVR                                    ( 260 )      /* FIQ Vector Register */
#وصف_ڪريو AIC_ISR                                    ( 264 )      /* Interrupt Status Register */
#وصف_ڪريو AIC_IPR                                    ( 268 )      /* Interrupt Pending Register */
#وصف_ڪريو AIC_IMR                                    ( 272 )      /* Interrupt Mask Register */
#وصف_ڪريو AIC_CISR                                   ( 276 )      /* Core Interrupt Status Register */
#وصف_ڪريو AIC_IECR                                   ( 288 )      /* Interrupt Enable Command Register */
#وصف_ڪريو AIC_IDCR                                   ( 292 )      /* Interrupt Disable Command Register */
#وصف_ڪريو AIC_ICCR                                   ( 296 )      /* Interrupt Clear Command Register */
#وصف_ڪريو AIC_ISCR                                   ( 300 )      /* Interrupt Set Command Register */
#وصف_ڪريو AIC_EOICR                                  ( 304 )      /* End of Interrupt Command Register */
#وصف_ڪريو AIC_SPU                                    ( 308 )      /* Spurious Vector Register */
#وصف_ڪريو AIC_DCR                                    ( 312 )      /* Debug Control Register (Protect) */
#وصف_ڪريو AIC_FFER                                   ( 320 )      /* Fast Forcing Enable Register */
#وصف_ڪريو AIC_FFDR                                   ( 324 )      /* Fast Forcing Disable Register */
#وصف_ڪريو AIC_FFSR                                   ( 328 )      /* Fast Forcing Status Register */
/* -------- AIC_SMR : (AIC Offset: 0x0) Control Register -------- */
#وصف_ڪريو AT91_C_AIC_اڳواٽ                            ( 0x7 << 0 ) /* (AIC) Priority Level */
#وصف_ڪريو     AT91_C_AIC_اڳواٽ_سڀ_کان_هيٺ                 ( 0x0 )      /* (AIC) Lowest priority level */
#وصف_ڪريو     AT91_C_AIC_اڳواٽ_HIGHEST                ( 0x7 )      /* (AIC) Highest priority level */
#وصف_ڪريو AT91C_AIC_SRCTYPE                          ( 0x3 << 5 ) /* (AIC) Interrupt Source Type */
#وصف_ڪريو     AT91_C_AIC_SRCTYPE_INT_مٿاهون_LEVEL       ( 0x0 << 5 ) /* (AIC) Internal Sources Code Label High-level Sensitive */
#وصف_ڪريو     AT91_C_AIC_SRCTYPE_EXT_هيٺيون_LEVEL        ( 0x0 << 5 ) /* (AIC) External Sources Code Label Low-level Sensitive */
#وصف_ڪريو     AT91_C_AIC_SRCTYPE_INT_مثبت_ڪنارو    ( 0x1 << 5 ) /* (AIC) Internal Sources Code Label Positive Edge triggered */
#وصف_ڪريو     AT91_C_AIC_SRCTYPE_EXT_NEGATIVE_ڪنارو    ( 0x1 << 5 ) /* (AIC) External Sources Code Label Negative Edge triggered */
#وصف_ڪريو     AT91_C_AIC_SRCTYPE_مٿاهون_LEVEL           ( 0x2 << 5 ) /* (AIC) Internal Or External Sources Code Label High-level Sensitive */
#وصف_ڪريو     AT91_C_AIC_SRCTYPE_مثبت_ڪنارو        ( 0x3 << 5 ) /* (AIC) Internal Or External Sources Code Label Positive Edge triggered */
/* -------- AIC_CISR : (AIC Offset: 0x114) AIC Core Interrupt Status Register -------- */
#وصف_ڪريو AT91C_AIC_NFIQ                             ( 0x1 << 0 ) /* (AIC) NFIQ Status */
#وصف_ڪريو AT91C_AIC_NIRQ                             ( 0x1 << 1 ) /* (AIC) NIRQ Status */
/* -------- AIC_DCR : (AIC Offset: 0x138) AIC Debug Control Register (Protect) -------- */
#وصف_ڪريو AT91C_AIC_DCR_PROT                         ( 0x1 << 0 ) /* (AIC) Protection Mode */
#وصف_ڪريو AT91C_AIC_DCR_GMSK                         ( 0x1 << 1 ) /* (AIC) General Mask */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Peripheral DMA Controller */
/* ***************************************************************************** */
/* *** Register offset in AT91S_PDC structure *** */
#وصف_ڪريو PDC_RPR             ( 0 )        /* Receive Pointer Register */
#وصف_ڪريو PDC_RCR             ( 4 )        /* Receive Counter Register */
#وصف_ڪريو PDC_TPR             ( 8 )        /* Transmit Pointer Register */
#وصف_ڪريو PDC_TCR             ( 12 )       /* Transmit Counter Register */
#وصف_ڪريو PDC_RNPR            ( 16 )       /* Receive Next Pointer Register */
#وصف_ڪريو PDC_RNCR            ( 20 )       /* Receive Next Counter Register */
#وصف_ڪريو PDC_TNPR            ( 24 )       /* Transmit Next Pointer Register */
#وصف_ڪريو PDC_TNCR            ( 28 )       /* Transmit Next Counter Register */
#وصف_ڪريو PDC_PTCR            ( 32 )       /* PDC Transfer Control Register */
#وصف_ڪريو PDC_PTSR            ( 36 )       /* PDC Transfer Status Register */
/* -------- PDC_PTCR : (PDC Offset: 0x20) PDC Transfer Control Register -------- */
#وصف_ڪريو AT91C_PDC_RXTEN     ( 0x1 << 0 ) /* (PDC) Receiver Transfer Enable */
#وصف_ڪريو AT91C_PDC_RXTDIS    ( 0x1 << 1 ) /* (PDC) Receiver Transfer Disable */
#وصف_ڪريو AT91C_PDC_TXTEN     ( 0x1 << 8 ) /* (PDC) Transmitter Transfer Enable */
#وصف_ڪريو AT91C_PDC_TXTDIS    ( 0x1 << 9 ) /* (PDC) Transmitter Transfer Disable */
/* -------- PDC_PTSR : (PDC Offset: 0x24) PDC Transfer Status Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Debug Unit */
/* ***************************************************************************** */
/* *** Register offset in AT91S_DBGU structure *** */
#وصف_ڪريو DBGU_CR                        ( 0 )         /* Control Register */
#وصف_ڪريو DBGU_MR                        ( 4 )         /* Mode Register */
#وصف_ڪريو DBGU_IER                       ( 8 )         /* Interrupt Enable Register */
#وصف_ڪريو DBGU_IDR                       ( 12 )        /* Interrupt Disable Register */
#وصف_ڪريو DBGU_IMR                       ( 16 )        /* Interrupt Mask Register */
#وصف_ڪريو DBGU_CSR                       ( 20 )        /* Channel Status Register */
#وصف_ڪريو DBGU_RHR                       ( 24 )        /* Receiver Holding Register */
#وصف_ڪريو DBGU_THR                       ( 28 )        /* Transmitter Holding Register */
#وصف_ڪريو DBGU_BRGR                      ( 32 )        /* Baud Rate Generator Register */
#وصف_ڪريو DBGU_CIDR                      ( 64 )        /* Chip ID Register */
#وصف_ڪريو DBGU_EXID                      ( 68 )        /* Chip ID Extension Register */
#وصف_ڪريو DBGU_FNTR                      ( 72 )        /* Force NTRST Register */
#وصف_ڪريو DBGU_RPR                       ( 256 )       /* Receive Pointer Register */
#وصف_ڪريو DBGU_RCR                       ( 260 )       /* Receive Counter Register */
#وصف_ڪريو DBGU_TPR                       ( 264 )       /* Transmit Pointer Register */
#وصف_ڪريو DBGU_TCR                       ( 268 )       /* Transmit Counter Register */
#وصف_ڪريو DBGU_RNPR                      ( 272 )       /* Receive Next Pointer Register */
#وصف_ڪريو DBGU_RNCR                      ( 276 )       /* Receive Next Counter Register */
#وصف_ڪريو DBGU_TNPR                      ( 280 )       /* Transmit Next Pointer Register */
#وصف_ڪريو DBGU_TNCR                      ( 284 )       /* Transmit Next Counter Register */
#وصف_ڪريو DBGU_PTCR                      ( 288 )       /* PDC Transfer Control Register */
#وصف_ڪريو DBGU_PTSR                      ( 292 )       /* PDC Transfer Status Register */
/* -------- DBGU_CR : (DBGU Offset: 0x0) Debug Unit Control Register -------- */
#وصف_ڪريو AT91C_US_RSTRX                 ( 0x1 << 2 )  /* (DBGU) Reset Receiver */
#وصف_ڪريو AT91C_US_RSTTX                 ( 0x1 << 3 )  /* (DBGU) Reset Transmitter */
#وصف_ڪريو AT91C_US_RXEN                  ( 0x1 << 4 )  /* (DBGU) Receiver Enable */
#وصف_ڪريو AT91C_US_RXDIS                 ( 0x1 << 5 )  /* (DBGU) Receiver Disable */
#وصف_ڪريو AT91C_US_TXEN                  ( 0x1 << 6 )  /* (DBGU) Transmitter Enable */
#وصف_ڪريو AT91C_US_TXDIS                 ( 0x1 << 7 )  /* (DBGU) Transmitter Disable */
#وصف_ڪريو AT91C_US_RSTSTA                ( 0x1 << 8 )  /* (DBGU) Reset Status Bits */
/* -------- DBGU_MR : (DBGU Offset: 0x4) Debug Unit Mode Register -------- */
#وصف_ڪريو AT91C_US_PAR                   ( 0x7 << 9 )  /* (DBGU) Parity type */
#وصف_ڪريو     AT91C_US_PAR_EVEN          ( 0x0 << 9 )  /* (DBGU) Even Parity */
#وصف_ڪريو     AT91C_US_PAR_ODD           ( 0x1 << 9 )  /* (DBGU) Odd Parity */
#وصف_ڪريو     AT91C_US_PAR_SPACE         ( 0x2 << 9 )  /* (DBGU) Parity forced to 0 (Space) */
#وصف_ڪريو     AT91C_US_PAR_MARK          ( 0x3 << 9 )  /* (DBGU) Parity forced to 1 (Mark) */
#وصف_ڪريو     AT91C_US_PAR_NONE          ( 0x4 << 9 )  /* (DBGU) No Parity */
#وصف_ڪريو     AT91C_US_PAR_MULTI_DROP    ( 0x6 << 9 )  /* (DBGU) Multi-drop mode */
#وصف_ڪريو AT91C_US_CHMODE                ( 0x3 << 14 ) /* (DBGU) Channel Mode */
#وصف_ڪريو     AT91_C_US_CHMODE_عام     ( 0x0 << 14 ) /* (DBGU) Normal Mode: The USART channel operates as an RX/TX USART. */
#وصف_ڪريو     AT91C_US_CHMODE_AUTO       ( 0x1 << 14 ) /* (DBGU) Automatic Echo: Receiver Data Input is connected to the TXD pin. */
#وصف_ڪريو     AT91C_US_CHMODE_LOCAL      ( 0x2 << 14 ) /* (DBGU) Local Loopback: Transmitter Output Signal is connected to Receiver Input Signal. */
#وصف_ڪريو     AT91C_US_CHMODE_REMOTE     ( 0x3 << 14 ) /* (DBGU) Remote Loopback: RXD pin is internally connected to TXD pin. */
/* -------- DBGU_IER : (DBGU Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
#وصف_ڪريو AT91C_US_RXRDY                 ( 0x1 << 0 )  /* (DBGU) RXRDY Interrupt */
#وصف_ڪريو AT91C_US_TXRDY                 ( 0x1 << 1 )  /* (DBGU) TXRDY Interrupt */
#وصف_ڪريو AT91C_US_ENDRX                 ( 0x1 << 3 )  /* (DBGU) End of Receive Transfer Interrupt */
#وصف_ڪريو AT91C_US_ENDTX                 ( 0x1 << 4 )  /* (DBGU) End of Transmit Interrupt */
#وصف_ڪريو AT91C_US_OVRE                  ( 0x1 << 5 )  /* (DBGU) Overrun Interrupt */
#وصف_ڪريو AT91_C_US_چوکٺو                 ( 0x1 << 6 )  /* (DBGU) Framing Error Interrupt */
#وصف_ڪريو AT91C_US_PARE                  ( 0x1 << 7 )  /* (DBGU) Parity Error Interrupt */
#وصف_ڪريو AT91C_US_TXEMPTY               ( 0x1 << 9 )  /* (DBGU) TXEMPTY Interrupt */
#وصف_ڪريو AT91C_US_TXBUFE                ( 0x1 << 11 ) /* (DBGU) TXBUFE Interrupt */
#وصف_ڪريو AT91C_US_RXBUFF                ( 0x1 << 12 ) /* (DBGU) RXBUFF Interrupt */
#وصف_ڪريو AT91C_US_COMM_TX               ( 0x1 << 30 ) /* (DBGU) COMM_TX Interrupt */
#وصف_ڪريو AT91C_US_COMM_RX               ( 0x1 << 31 ) /* (DBGU) COMM_RX Interrupt */
/* -------- DBGU_IDR : (DBGU Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* -------- DBGU_IMR : (DBGU Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* -------- DBGU_CSR : (DBGU Offset: 0x14) Debug Unit Channel Status Register -------- */
/* -------- DBGU_FNTR : (DBGU Offset: 0x48) Debug Unit FORCE_NTRST Register -------- */
#وصف_ڪريو AT91C_US_FORCE_NTRST    ( 0x1 << 0 )  /* (DBGU) Force NTRST in JTAG */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Parallel Input Output Controller */
/* ***************************************************************************** */
/* *** Register offset in AT91S_PIO structure *** */
#وصف_ڪريو PIO_في      ( 0 )   /* PIO Enable Register */
#وصف_ڪريو PIO_PDR      ( 4 )   /* PIO Disable Register */
#وصف_ڪريو PIO_PSR      ( 8 )   /* PIO Status Register */
#وصف_ڪريو PIO_OER      ( 16 )  /* Output Enable Register */
#وصف_ڪريو PIO_ODR      ( 20 )  /* Output Disable Registerr */
#وصف_ڪريو PIO_OSR      ( 24 )  /* Output Status Register */
#وصف_ڪريو PIO_IFER     ( 32 )  /* Input Filter Enable Register */
#وصف_ڪريو PIO_IFDR     ( 36 )  /* Input Filter Disable Register */
#وصف_ڪريو PIO_IFSR     ( 40 )  /* Input Filter Status Register */
#وصف_ڪريو PIO_SODR     ( 48 )  /* Set Output Data Register */
#وصف_ڪريو PIO_CODR     ( 52 )  /* Clear Output Data Register */
#وصف_ڪريو PIO_ODSR     ( 56 )  /* Output Data Status Register */
#وصف_ڪريو PIO_PDSR     ( 60 )  /* Pin Data Status Register */
#وصف_ڪريو PIO_IER      ( 64 )  /* Interrupt Enable Register */
#وصف_ڪريو PIO_IDR      ( 68 )  /* Interrupt Disable Register */
#وصف_ڪريو PIO_IMR      ( 72 )  /* Interrupt Mask Register */
#وصف_ڪريو PIO_ISR      ( 76 )  /* Interrupt Status Register */
#وصف_ڪريو PIO_MDER     ( 80 )  /* Multi-driver Enable Register */
#وصف_ڪريو PIO_MDDR     ( 84 )  /* Multi-driver Disable Register */
#وصف_ڪريو PIO_MDSR     ( 88 )  /* Multi-driver Status Register */
#وصف_ڪريو PIO_PPUDR    ( 96 )  /* Pull-up Disable Register */
#وصف_ڪريو PIO_PPUER    ( 100 ) /* Pull-up Enable Register */
#وصف_ڪريو PIO_PPUSR    ( 104 ) /* Pull-up Status Register */
#وصف_ڪريو PIO_ASR      ( 112 ) /* Select A Register */
#وصف_ڪريو PIO_BSR      ( 116 ) /* Select B Register */
#وصف_ڪريو PIO_ABSR     ( 120 ) /* AB Select Status Register */
#وصف_ڪريو PIO_OWER     ( 160 ) /* Output Write Enable Register */
#وصف_ڪريو PIO_OWDR     ( 164 ) /* Output Write Disable Register */
#وصف_ڪريو PIO_OWSR     ( 168 ) /* Output Write Status Register */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Clock Generator Controller */
/* ***************************************************************************** */
/* *** Register offset in AT91S_CKGR structure *** */
#وصف_ڪريو CKGR_MOR                     ( 0 )           /* Main Oscillator Register */
#وصف_ڪريو CKGR_MCFR                    ( 4 )           /* Main Clock  Frequency Register */
#وصف_ڪريو CKGR_PLLR                    ( 12 )          /* PLL Register */
/* -------- CKGR_MOR : (CKGR Offset: 0x0) Main Oscillator Register -------- */
#وصف_ڪريو AT91C_CKGR_MOSCEN            ( 0x1 << 0 )    /* (CKGR) Main Oscillator Enable */
#وصف_ڪريو AT91C_CKGR_OSCBYPASS         ( 0x1 << 1 )    /* (CKGR) Main Oscillator Bypass */
#وصف_ڪريو AT91C_CKGR_OSCOUNT           ( 0xFF << 8 )   /* (CKGR) Main Oscillator Start-up Time */
/* -------- CKGR_MCFR : (CKGR Offset: 0x4) Main Clock Frequency Register -------- */
#وصف_ڪريو AT91C_CKGR_MAINF             ( 0xFFFF << 0 ) /* (CKGR) Main Clock Frequency */
#وصف_ڪريو AT91C_CKGR_MAINRDY           ( 0x1 << 16 )   /* (CKGR) Main Clock Ready */
/* -------- CKGR_PLLR : (CKGR Offset: 0xc) PLL B Register -------- */
#وصف_ڪريو AT91C_CKGR_DIV               ( 0xFF << 0 )   /* (CKGR) Divider Selected */
#وصف_ڪريو     AT91C_CKGR_DIV_0         ( 0x0 )         /* (CKGR) Divider output is 0 */
#وصف_ڪريو     AT91C_CKGR_DIV_BYPASS    ( 0x1 )         /* (CKGR) Divider is bypassed */
#وصف_ڪريو AT91C_CKGR_PLLCOUNT          ( 0x3F << 8 )   /* (CKGR) PLL Counter */
#وصف_ڪريو AT91_C_CKGR_ٻاهريون               ( 0x3 << 14 )   /* (CKGR) PLL Output Frequency Range */
#وصف_ڪريو     AT91_C_CKGR_ٻاهريون_0         ( 0x0 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#وصف_ڪريو     AT91_C_CKGR_ٻاهريون_1         ( 0x1 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#وصف_ڪريو     AT91_C_CKGR_ٻاهريون_2         ( 0x2 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#وصف_ڪريو     AT91_C_CKGR_ٻاهريون_3         ( 0x3 << 14 )   /* (CKGR) Please refer to the PLL datasheet */
#وصف_ڪريو AT91C_CKGR_MUL               ( 0x7FF << 16 ) /* (CKGR) PLL Multiplier */
#وصف_ڪريو AT91C_CKGR_USBDIV            ( 0x3 << 28 )   /* (CKGR) Divider for USB Clocks */
#وصف_ڪريو     AT91C_CKGR_USBDIV_0      ( 0x0 << 28 )   /* (CKGR) Divider output is PLL clock output */
#وصف_ڪريو     AT91C_CKGR_USBDIV_1      ( 0x1 << 28 )   /* (CKGR) Divider output is PLL clock output divided by 2 */
#وصف_ڪريو     AT91C_CKGR_USBDIV_2      ( 0x2 << 28 )   /* (CKGR) Divider output is PLL clock output divided by 4 */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Power Management Controller */
/* ***************************************************************************** */
/* *** Register offset in AT91S_PMC structure *** */
#وصف_ڪريو PMC_SCER          ( 0 )         /* System Clock Enable Register */
#وصف_ڪريو PMC_SCDR          ( 4 )         /* System Clock Disable Register */
#وصف_ڪريو PMC_SCSR          ( 8 )         /* System Clock Status Register */
#وصف_ڪريو PMC_PCER          ( 16 )        /* Peripheral Clock Enable Register */
#وصف_ڪريو PMC_PCDR          ( 20 )        /* Peripheral Clock Disable Register */
#وصف_ڪريو PMC_PCSR          ( 24 )        /* Peripheral Clock Status Register */
#وصف_ڪريو PMC_MOR           ( 32 )        /* Main Oscillator Register */
#وصف_ڪريو PMC_MCFR          ( 36 )        /* Main Clock  Frequency Register */
#وصف_ڪريو PMC_PLLR          ( 44 )        /* PLL Register */
#وصف_ڪريو PMC_MCKR          ( 48 )        /* Master Clock Register */
#وصف_ڪريو PMC_PCKR          ( 64 )        /* Programmable Clock Register */
#وصف_ڪريو PMC_IER           ( 96 )        /* Interrupt Enable Register */
#وصف_ڪريو PMC_IDR           ( 100 )       /* Interrupt Disable Register */
#وصف_ڪريو PMC_SR            ( 104 )       /* Status Register */
#وصف_ڪريو PMC_IMR           ( 108 )       /* Interrupt Mask Register */
/* -------- PMC_SCER : (PMC Offset: 0x0) System Clock Enable Register -------- */
#وصف_ڪريو AT91C_PMC_PCK     ( 0x1 << 0 )  /* (PMC) Processor Clock */
#وصف_ڪريو AT91C_PMC_UDP     ( 0x1 << 7 )  /* (PMC) USB Device Port Clock */
#وصف_ڪريو AT91C_PMC_PCK0    ( 0x1 << 8 )  /* (PMC) Programmable Clock Output */
#وصف_ڪريو AT91C_PMC_PCK1    ( 0x1 << 9 )  /* (PMC) Programmable Clock Output */
#وصف_ڪريو AT91C_PMC_PCK2    ( 0x1 << 10 ) /* (PMC) Programmable Clock Output */
#وصف_ڪريو AT91C_PMC_PCK3    ( 0x1 << 11 ) /* (PMC) Programmable Clock Output */
/* -------- PMC_SCDR : (PMC Offset: 0x4) System Clock Disable Register -------- */
/* -------- PMC_SCSR : (PMC Offset: 0x8) System Clock Status Register -------- */
/* -------- CKGR_MOR : (PMC Offset: 0x20) Main Oscillator Register -------- */
/* -------- CKGR_MCFR : (PMC Offset: 0x24) Main Clock Frequency Register -------- */
/* -------- CKGR_PLLR : (PMC Offset: 0x2c) PLL B Register -------- */
/* -------- PMC_MCKR : (PMC Offset: 0x30) Master Clock Register -------- */
#وصف_ڪريو AT91C_PMC_CSS                 ( 0x3 << 0 ) /* (PMC) Programmable Clock Selection */
#وصف_ڪريو     AT91C_PMC_CSS_SLOW_CLK    ( 0x0 )      /* (PMC) Slow Clock is selected */
#وصف_ڪريو     AT91C_PMC_CSS_MAIN_CLK    ( 0x1 )      /* (PMC) Main Clock is selected */
#وصف_ڪريو     AT91C_PMC_CSS_PLL_CLK     ( 0x3 )      /* (PMC) Clock from PLL is selected */
#وصف_ڪريو AT91C_PMC_PRES                ( 0x7 << 2 ) /* (PMC) Programmable Clock Prescaler */
#وصف_ڪريو     AT91C_PMC_PRES_CLK        ( 0x0 << 2 ) /* (PMC) Selected clock */
#وصف_ڪريو     AT91C_PMC_PRES_CLK_2      ( 0x1 << 2 ) /* (PMC) Selected clock divided by 2 */
#وصف_ڪريو     AT91C_PMC_PRES_CLK_4      ( 0x2 << 2 ) /* (PMC) Selected clock divided by 4 */
#وصف_ڪريو     AT91C_PMC_PRES_CLK_8      ( 0x3 << 2 ) /* (PMC) Selected clock divided by 8 */
#وصف_ڪريو     AT91C_PMC_PRES_CLK_16     ( 0x4 << 2 ) /* (PMC) Selected clock divided by 16 */
#وصف_ڪريو     AT91C_PMC_PRES_CLK_32     ( 0x5 << 2 ) /* (PMC) Selected clock divided by 32 */
#وصف_ڪريو     AT91C_PMC_PRES_CLK_64     ( 0x6 << 2 ) /* (PMC) Selected clock divided by 64 */
/* -------- PMC_PCKR : (PMC Offset: 0x40) Programmable Clock Register -------- */
/* -------- PMC_IER : (PMC Offset: 0x60) PMC Interrupt Enable Register -------- */
#وصف_ڪريو AT91C_PMC_MOSCS               ( 0x1 << 0 )  /* (PMC) MOSC Status/Enable/Disable/Mask */
#وصف_ڪريو AT91_C_PMC_تالو                ( 0x1 << 2 )  /* (PMC) PLL Status/Enable/Disable/Mask */
#وصف_ڪريو AT91C_PMC_MCKRDY              ( 0x1 << 3 )  /* (PMC) MCK_RDY Status/Enable/Disable/Mask */
#وصف_ڪريو AT91C_PMC_PCK0RDY             ( 0x1 << 8 )  /* (PMC) PCK0_RDY Status/Enable/Disable/Mask */
#وصف_ڪريو AT91C_PMC_PCK1RDY             ( 0x1 << 9 )  /* (PMC) PCK1_RDY Status/Enable/Disable/Mask */
#وصف_ڪريو AT91C_PMC_PCK2RDY             ( 0x1 << 10 ) /* (PMC) PCK2_RDY Status/Enable/Disable/Mask */
#وصف_ڪريو AT91C_PMC_PCK3RDY             ( 0x1 << 11 ) /* (PMC) PCK3_RDY Status/Enable/Disable/Mask */
/* -------- PMC_IDR : (PMC Offset: 0x64) PMC Interrupt Disable Register -------- */
/* -------- PMC_SR : (PMC Offset: 0x68) PMC Status Register -------- */
/* -------- PMC_IMR : (PMC Offset: 0x6c) PMC Interrupt Mask Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Reset Controller Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_RSTC structure *** */
#وصف_ڪريو RSTC_RCR                          ( 0 )          /* Reset Control Register */
#وصف_ڪريو RSTC_RSR                          ( 4 )          /* Reset Status Register */
#وصف_ڪريو RSTC_RMR                          ( 8 )          /* Reset Mode Register */
/* -------- RSTC_RCR : (RSTC Offset: 0x0) Reset Control Register -------- */
#وصف_ڪريو AT91C_RSTC_PROCRST                ( 0x1 << 0 )   /* (RSTC) Processor Reset */
#وصف_ڪريو AT91C_RSTC_PERRST                 ( 0x1 << 2 )   /* (RSTC) Peripheral Reset */
#وصف_ڪريو AT91C_RSTC_EXTRST                 ( 0x1 << 3 )   /* (RSTC) External Reset */
#وصف_ڪريو AT91_C_RSTC_ڪنجي                    ( 0xFF << 24 ) /* (RSTC) Password */
/* -------- RSTC_RSR : (RSTC Offset: 0x4) Reset Status Register -------- */
#وصف_ڪريو AT91C_RSTC_URSTS                  ( 0x1 << 0 )   /* (RSTC) User Reset Status */
#وصف_ڪريو AT91C_RSTC_BODSTS                 ( 0x1 << 1 )   /* (RSTC) Brownout Detection Status */
#وصف_ڪريو AT91C_RSTC_RSTTYP                 ( 0x7 << 8 )   /* (RSTC) Reset Type */
#وصف_ڪريو     AT91C_RSTC_RSTTYP_POWERUP     ( 0x0 << 8 )   /* (RSTC) Power-up Reset. VDDCORE rising. */
#وصف_ڪريو     AT91C_RSTC_RSTTYP_WAKEUP      ( 0x1 << 8 )   /* (RSTC) WakeUp Reset. VDDCORE rising. */
#وصف_ڪريو     AT91C_RSTC_RSTTYP_WATCHDOG    ( 0x2 << 8 )   /* (RSTC) Watchdog Reset. Watchdog overflow occurred. */
#وصف_ڪريو     AT91C_RSTC_RSTTYP_SOFTWARE    ( 0x3 << 8 )   /* (RSTC) Software Reset. Processor reset required by the software. */
#وصف_ڪريو     AT91C_RSTC_RSTTYP_USER        ( 0x4 << 8 )   /* (RSTC) User Reset. NRST pin detected low. */
#وصف_ڪريو     AT91C_RSTC_RSTTYP_BROWNOUT    ( 0x5 << 8 )   /* (RSTC) Brownout Reset occurred. */
#وصف_ڪريو AT91C_RSTC_NRSTL                  ( 0x1 << 16 )  /* (RSTC) NRST pin level */
#وصف_ڪريو AT91C_RSTC_SRCMP                  ( 0x1 << 17 )  /* (RSTC) Software Reset Command in Progress. */
/* -------- RSTC_RMR : (RSTC Offset: 0x8) Reset Mode Register -------- */
#وصف_ڪريو AT91C_RSTC_URSTEN                 ( 0x1 << 0 )   /* (RSTC) User Reset Enable */
#وصف_ڪريو AT91C_RSTC_URSTIEN                ( 0x1 << 4 )   /* (RSTC) User Reset Interrupt Enable */
#وصف_ڪريو AT91C_RSTC_ERSTL                  ( 0xF << 8 )   /* (RSTC) User Reset Enable */
#وصف_ڪريو AT91C_RSTC_BODIEN                 ( 0x1 << 16 )  /* (RSTC) Brownout Detection Interrupt Enable */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Real Time Timer Controller Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_RTTC structure *** */
#وصف_ڪريو RTTC_RTMR               ( 0 )           /* Real-time Mode Register */
#وصف_ڪريو RTTC_RTAR               ( 4 )           /* Real-time Alarm Register */
#وصف_ڪريو RTTC_RTVR               ( 8 )           /* Real-time Value Register */
#وصف_ڪريو RTTC_RTSR               ( 12 )          /* Real-time Status Register */
/* -------- RTTC_RTMR : (RTTC Offset: 0x0) Real-time Mode Register -------- */
#وصف_ڪريو AT91C_RTTC_RTPRES       ( 0xFFFF << 0 ) /* (RTTC) Real-time Timer Prescaler Value */
#وصف_ڪريو AT91C_RTTC_ALMIEN       ( 0x1 << 16 )   /* (RTTC) Alarm Interrupt Enable */
#وصف_ڪريو AT91C_RTTC_RTTINCIEN    ( 0x1 << 17 )   /* (RTTC) Real Time Timer Increment Interrupt Enable */
#وصف_ڪريو AT91C_RTTC_RTTRST       ( 0x1 << 18 )   /* (RTTC) Real Time Timer Restart */
/* -------- RTTC_RTAR : (RTTC Offset: 0x4) Real-time Alarm Register -------- */
#وصف_ڪريو AT91C_RTTC_ALMV         ( 0x0 << 0 )    /* (RTTC) Alarm Value */
/* -------- RTTC_RTVR : (RTTC Offset: 0x8) Current Real-time Value Register -------- */
#وصف_ڪريو AT91C_RTTC_CRTV         ( 0x0 << 0 )    /* (RTTC) Current Real-time Value */
/* -------- RTTC_RTSR : (RTTC Offset: 0xc) Real-time Status Register -------- */
#وصف_ڪريو AT91C_RTTC_ALMS         ( 0x1 << 0 )    /* (RTTC) Real-time Alarm Status */
#وصف_ڪريو AT91C_RTTC_RTTINC       ( 0x1 << 1 )    /* (RTTC) Real-time Timer Increment */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Periodic Interval Timer Controller Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_PITC structure *** */
#وصف_ڪريو PITC_PIMR            ( 0 )            /* Period Interval Mode Register */
#وصف_ڪريو PITC_PISR            ( 4 )            /* Period Interval Status Register */
#وصف_ڪريو PITC_PIVR            ( 8 )            /* Period Interval Value Register */
#وصف_ڪريو PITC_PIIR            ( 12 )           /* Period Interval Image Register */
/* -------- PITC_PIMR : (PITC Offset: 0x0) Periodic Interval Mode Register -------- */
#وصف_ڪريو AT91C_PITC_PIV       ( 0xFFFFF << 0 ) /* (PITC) Periodic Interval Value */
#وصف_ڪريو AT91C_PITC_PITEN     ( 0x1 << 24 )    /* (PITC) Periodic Interval Timer Enabled */
#وصف_ڪريو AT91C_PITC_PITIEN    ( 0x1 << 25 )    /* (PITC) Periodic Interval Timer Interrupt Enable */
/* -------- PITC_PISR : (PITC Offset: 0x4) Periodic Interval Status Register -------- */
#وصف_ڪريو AT91C_PITC_PITS      ( 0x1 << 0 )     /* (PITC) Periodic Interval Timer Status */
/* -------- PITC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register -------- */
#وصف_ڪريو AT91C_PITC_CPIV      ( 0xFFFFF << 0 ) /* (PITC) Current Periodic Interval Value */
#وصف_ڪريو AT91C_PITC_PICNT     ( 0xFFF << 20 )  /* (PITC) Periodic Interval Counter */
/* -------- PITC_PIIR : (PITC Offset: 0xc) Periodic Interval Image Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Watchdog Timer Controller Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_WDTC structure *** */
#وصف_ڪريو WDTC_WDCR               ( 0 )           /* Watchdog Control Register */
#وصف_ڪريو WDTC_WDMR               ( 4 )           /* Watchdog Mode Register */
#وصف_ڪريو WDTC_WDSR               ( 8 )           /* Watchdog Status Register */
/* -------- WDTC_WDCR : (WDTC Offset: 0x0) Periodic Interval Image Register -------- */
#وصف_ڪريو AT91C_WDTC_WDRSTT       ( 0x1 << 0 )    /* (WDTC) Watchdog Restart */
#وصف_ڪريو AT91_C_WDTC_ڪنجي          ( 0xFF << 24 )  /* (WDTC) Watchdog KEY Password */
/* -------- WDTC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register -------- */
#وصف_ڪريو AT91C_WDTC_WDV          ( 0xFFF << 0 )  /* (WDTC) Watchdog Timer Restart */
#وصف_ڪريو AT91C_WDTC_WDFIEN       ( 0x1 << 12 )   /* (WDTC) Watchdog Fault Interrupt Enable */
#وصف_ڪريو AT91C_WDTC_WDRSTEN      ( 0x1 << 13 )   /* (WDTC) Watchdog Reset Enable */
#وصف_ڪريو AT91C_WDTC_WDRPROC      ( 0x1 << 14 )   /* (WDTC) Watchdog Timer Restart */
#وصف_ڪريو AT91C_WDTC_WDDIS        ( 0x1 << 15 )   /* (WDTC) Watchdog Disable */
#وصف_ڪريو AT91C_WDTC_WDD          ( 0xFFF << 16 ) /* (WDTC) Watchdog Delta Value */
#وصف_ڪريو AT91C_WDTC_WDDBGHLT     ( 0x1 << 28 )   /* (WDTC) Watchdog Debug Halt */
#وصف_ڪريو AT91C_WDTC_WDIDLEHLT    ( 0x1 << 29 )   /* (WDTC) Watchdog Idle Halt */
/* -------- WDTC_WDSR : (WDTC Offset: 0x8) Watchdog Status Register -------- */
#وصف_ڪريو AT91C_WDTC_WDUNF        ( 0x1 << 0 )    /* (WDTC) Watchdog Underflow */
#وصف_ڪريو AT91C_WDTC_WDERR        ( 0x1 << 1 )    /* (WDTC) Watchdog Error */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Voltage Regulator Mode Controller Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_VREG structure *** */
#وصف_ڪريو VREG_MR              ( 0 )        /* Voltage Regulator Mode Register */
/* -------- VREG_MR : (VREG Offset: 0x0) Voltage Regulator Mode Register -------- */
#وصف_ڪريو AT91C_VREG_PSTDBY    ( 0x1 << 0 ) /* (VREG) Voltage Regulator Power Standby Mode */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Memory Controller Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_MC structure *** */
#وصف_ڪريو MC_RCR                             ( 0 )          /* MC Remap Control Register */
#وصف_ڪريو MC_ASR                             ( 4 )          /* MC Abort Status Register */
#وصف_ڪريو MC_AASR                            ( 8 )          /* MC Abort Address Status Register */
#وصف_ڪريو MC_FMR                             ( 96 )         /* MC Flash Mode Register */
#وصف_ڪريو MC_FCR                             ( 100 )        /* MC Flash Command Register */
#وصف_ڪريو MC_FSR                             ( 104 )        /* MC Flash Status Register */
/* -------- MC_RCR : (MC Offset: 0x0) MC Remap Control Register -------- */
#وصف_ڪريو AT91C_MC_RCB                       ( 0x1 << 0 )   /* (MC) Remap Command Bit */
/* -------- MC_ASR : (MC Offset: 0x4) MC Abort Status Register -------- */
#وصف_ڪريو AT91C_MC_UNDADD                    ( 0x1 << 0 )   /* (MC) Undefined Address Abort Status */
#وصف_ڪريو AT91C_MC_MISADD                    ( 0x1 << 1 )   /* (MC) Misaligned Address Abort Status */
#وصف_ڪريو AT91C_MC_ABTSZ                     ( 0x3 << 8 )   /* (MC) Abort Size Status */
#وصف_ڪريو     AT91C_MC_ABTSZ_BYTE            ( 0x0 << 8 )   /* (MC) Byte */
#وصف_ڪريو     AT91C_MC_ABTSZ_HWORD           ( 0x1 << 8 )   /* (MC) Half-word */
#وصف_ڪريو     AT91_C_MC_ABTSZ_لفظ            ( 0x2 << 8 )   /* (MC) Word */
#وصف_ڪريو AT91C_MC_ABTTYP                    ( 0x3 << 10 )  /* (MC) Abort Type Status */
#وصف_ڪريو     AT91C_MC_ABTTYP_DATAR          ( 0x0 << 10 )  /* (MC) Data Read */
#وصف_ڪريو     AT91C_MC_ABTTYP_DATAW          ( 0x1 << 10 )  /* (MC) Data Write */
#وصف_ڪريو     AT91C_MC_ABTTYP_FETCH          ( 0x2 << 10 )  /* (MC) Code Fetch */
#وصف_ڪريو AT91C_MC_MST0                      ( 0x1 << 16 )  /* (MC) Master 0 Abort Source */
#وصف_ڪريو AT91C_MC_MST1                      ( 0x1 << 17 )  /* (MC) Master 1 Abort Source */
#وصف_ڪريو AT91C_MC_SVMST0                    ( 0x1 << 24 )  /* (MC) Saved Master 0 Abort Source */
#وصف_ڪريو AT91C_MC_SVMST1                    ( 0x1 << 25 )  /* (MC) Saved Master 1 Abort Source */
/* -------- MC_FMR : (MC Offset: 0x60) MC Flash Mode Register -------- */
#وصف_ڪريو AT91C_MC_FRDY                      ( 0x1 << 0 )   /* (MC) Flash Ready */
#وصف_ڪريو AT91C_MC_LOCKE                     ( 0x1 << 2 )   /* (MC) Lock Error */
#وصف_ڪريو AT91C_MC_PROGE                     ( 0x1 << 3 )   /* (MC) Programming Error */
#وصف_ڪريو AT91C_MC_NEBP                      ( 0x1 << 7 )   /* (MC) No Erase Before Programming */
#وصف_ڪريو AT91C_MC_FWS                       ( 0x3 << 8 )   /* (MC) Flash Wait State */
#وصف_ڪريو     AT91C_MC_FWS_0FWS              ( 0x0 << 8 )   /* (MC) 1 cycle for Read, 2 for Write operations */
#وصف_ڪريو     AT91C_MC_FWS_1FWS              ( 0x1 << 8 )   /* (MC) 2 cycles for Read, 3 for Write operations */
#وصف_ڪريو     AT91C_MC_FWS_2FWS              ( 0x2 << 8 )   /* (MC) 3 cycles for Read, 4 for Write operations */
#وصف_ڪريو     AT91C_MC_FWS_3FWS              ( 0x3 << 8 )   /* (MC) 4 cycles for Read, 4 for Write operations */
#وصف_ڪريو AT91C_MC_FMCN                      ( 0xFF << 16 ) /* (MC) Flash Microsecond Cycle Number */
/* -------- MC_FCR : (MC Offset: 0x64) MC Flash Command Register -------- */
#وصف_ڪريو AT91C_MC_FCMD                      ( 0xF << 0 )   /* (MC) Flash Command */
#وصف_ڪريو     AT91_C_MC_FCMD_شروعات_PROG       ( 0x1 )        /* (MC) Starts the programming of th epage specified by PAGEN. */
#وصف_ڪريو     AT91_C_MC_FCMD_تالو             ( 0x2 )        /* (MC) Starts a lock sequence of the sector defined by the bits 4 to 7 of the field PAGEN. */
#وصف_ڪريو     AT91_C_MC_FCMD_PROG_AND_تالو    ( 0x3 )        /* (MC) The lock sequence automatically happens after the programming sequence is completed. */
#وصف_ڪريو     AT91C_MC_FCMD_UNLOCK           ( 0x4 )        /* (MC) Starts an unlock sequence of the sector defined by the bits 4 to 7 of the field PAGEN. */
#وصف_ڪريو     AT91C_MC_FCMD_ERASE_ALL        ( 0x8 )        /* (MC) Starts the erase of the entire flash.If at least a page is locked, the command is cancelled. */
#وصف_ڪريو     AT91_C_MC_FCMD_سيٽ_GP_NVM       ( 0xB )        /* (MC) Set General Purpose NVM bits. */
#وصف_ڪريو     AT91C_MC_FCMD_CLR_GP_NVM       ( 0xD )        /* (MC) Clear General Purpose NVM bits. */
#وصف_ڪريو     AT91_C_MC_FCMD_سيٽ_SECURITY     ( 0xF )        /* (MC) Set Security Bit. */
#وصف_ڪريو AT91C_MC_PAGEN                     ( 0x3FF << 8 ) /* (MC) Page Number */
#وصف_ڪريو AT91_C_MC_ڪنجي                       ( 0xFF << 24 ) /* (MC) Writing Protect Key */
/* -------- MC_FSR : (MC Offset: 0x68) MC Flash Command Register -------- */
#وصف_ڪريو AT91C_MC_SECURITY                  ( 0x1 << 4 )   /* (MC) Security Bit Status */
#وصف_ڪريو AT91C_MC_GPNVM0                    ( 0x1 << 8 )   /* (MC) Sector 0 Lock Status */
#وصف_ڪريو AT91C_MC_GPNVM1                    ( 0x1 << 9 )   /* (MC) Sector 1 Lock Status */
#وصف_ڪريو AT91C_MC_GPNVM2                    ( 0x1 << 10 )  /* (MC) Sector 2 Lock Status */
#وصف_ڪريو AT91C_MC_GPNVM3                    ( 0x1 << 11 )  /* (MC) Sector 3 Lock Status */
#وصف_ڪريو AT91C_MC_GPNVM4                    ( 0x1 << 12 )  /* (MC) Sector 4 Lock Status */
#وصف_ڪريو AT91C_MC_GPNVM5                    ( 0x1 << 13 )  /* (MC) Sector 5 Lock Status */
#وصف_ڪريو AT91C_MC_GPNVM6                    ( 0x1 << 14 )  /* (MC) Sector 6 Lock Status */
#وصف_ڪريو AT91C_MC_GPNVM7                    ( 0x1 << 15 )  /* (MC) Sector 7 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS0                    ( 0x1 << 16 )  /* (MC) Sector 0 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS1                    ( 0x1 << 17 )  /* (MC) Sector 1 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS2                    ( 0x1 << 18 )  /* (MC) Sector 2 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS3                    ( 0x1 << 19 )  /* (MC) Sector 3 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS4                    ( 0x1 << 20 )  /* (MC) Sector 4 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS5                    ( 0x1 << 21 )  /* (MC) Sector 5 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS6                    ( 0x1 << 22 )  /* (MC) Sector 6 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS7                    ( 0x1 << 23 )  /* (MC) Sector 7 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS8                    ( 0x1 << 24 )  /* (MC) Sector 8 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS9                    ( 0x1 << 25 )  /* (MC) Sector 9 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS10                   ( 0x1 << 26 )  /* (MC) Sector 10 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS11                   ( 0x1 << 27 )  /* (MC) Sector 11 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS12                   ( 0x1 << 28 )  /* (MC) Sector 12 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS13                   ( 0x1 << 29 )  /* (MC) Sector 13 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS14                   ( 0x1 << 30 )  /* (MC) Sector 14 Lock Status */
#وصف_ڪريو AT91C_MC_LOCKS15                   ( 0x1 << 31 )  /* (MC) Sector 15 Lock Status */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Serial Parallel Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_SPI structure *** */
#وصف_ڪريو SPI_CR                       ( 0 )           /* Control Register */
#وصف_ڪريو SPI_MR                       ( 4 )           /* Mode Register */
#وصف_ڪريو SPI_RDR                      ( 8 )           /* Receive Data Register */
#وصف_ڪريو SPI_TDR                      ( 12 )          /* Transmit Data Register */
#وصف_ڪريو SPI_SR                       ( 16 )          /* Status Register */
#وصف_ڪريو SPI_IER                      ( 20 )          /* Interrupt Enable Register */
#وصف_ڪريو SPI_IDR                      ( 24 )          /* Interrupt Disable Register */
#وصف_ڪريو SPI_IMR                      ( 28 )          /* Interrupt Mask Register */
#وصف_ڪريو SPI_CSR                      ( 48 )          /* Chip Select Register */
#وصف_ڪريو SPI_RPR                      ( 256 )         /* Receive Pointer Register */
#وصف_ڪريو SPI_RCR                      ( 260 )         /* Receive Counter Register */
#وصف_ڪريو SPI_TPR                      ( 264 )         /* Transmit Pointer Register */
#وصف_ڪريو SPI_TCR                      ( 268 )         /* Transmit Counter Register */
#وصف_ڪريو SPI_RNPR                     ( 272 )         /* Receive Next Pointer Register */
#وصف_ڪريو SPI_RNCR                     ( 276 )         /* Receive Next Counter Register */
#وصف_ڪريو SPI_TNPR                     ( 280 )         /* Transmit Next Pointer Register */
#وصف_ڪريو SPI_TNCR                     ( 284 )         /* Transmit Next Counter Register */
#وصف_ڪريو SPI_PTCR                     ( 288 )         /* PDC Transfer Control Register */
#وصف_ڪريو SPI_PTSR                     ( 292 )         /* PDC Transfer Status Register */
/* -------- SPI_CR : (SPI Offset: 0x0) SPI Control Register -------- */
#وصف_ڪريو AT91C_SPI_SPIEN              ( 0x1 << 0 )    /* (SPI) SPI Enable */
#وصف_ڪريو AT91C_SPI_SPIDIS             ( 0x1 << 1 )    /* (SPI) SPI Disable */
#وصف_ڪريو AT91C_SPI_SWRST              ( 0x1 << 7 )    /* (SPI) SPI Software reset */
#وصف_ڪريو AT91C_SPI_LASTXFER           ( 0x1 << 24 )   /* (SPI) SPI Last Transfer */
/* -------- SPI_MR : (SPI Offset: 0x4) SPI Mode Register -------- */
#وصف_ڪريو AT91C_SPI_MSTR               ( 0x1 << 0 )    /* (SPI) Master/Slave Mode */
#وصف_ڪريو AT91C_SPI_PS                 ( 0x1 << 1 )    /* (SPI) Peripheral Select */
#وصف_ڪريو     AT91C_SPI_PS_FIXED       ( 0x0 << 1 )    /* (SPI) Fixed Peripheral Select */
#وصف_ڪريو     AT91C_SPI_PS_VARIABLE    ( 0x1 << 1 )    /* (SPI) Variable Peripheral Select */
#وصف_ڪريو AT91C_SPI_PCSDEC             ( 0x1 << 2 )    /* (SPI) Chip Select Decode */
#وصف_ڪريو AT91C_SPI_FDIV               ( 0x1 << 3 )    /* (SPI) Clock Selection */
#وصف_ڪريو AT91C_SPI_MODFDIS            ( 0x1 << 4 )    /* (SPI) Mode Fault Detection */
#وصف_ڪريو AT91C_SPI_LLB                ( 0x1 << 7 )    /* (SPI) Clock Selection */
#وصف_ڪريو AT91C_SPI_PCS                ( 0xF << 16 )   /* (SPI) Peripheral Chip Select */
#وصف_ڪريو AT91C_SPI_DLYBCS             ( 0xFF << 24 )  /* (SPI) Delay Between Chip Selects */
/* -------- SPI_RDR : (SPI Offset: 0x8) Receive Data Register -------- */
#وصف_ڪريو AT91C_SPI_RD                 ( 0xFFFF << 0 ) /* (SPI) Receive Data */
#وصف_ڪريو AT91C_SPI_RPCS               ( 0xF << 16 )   /* (SPI) Peripheral Chip Select Status */
/* -------- SPI_TDR : (SPI Offset: 0xc) Transmit Data Register -------- */
#وصف_ڪريو AT91C_SPI_TD                 ( 0xFFFF << 0 ) /* (SPI) Transmit Data */
#وصف_ڪريو AT91C_SPI_TPCS               ( 0xF << 16 )   /* (SPI) Peripheral Chip Select Status */
/* -------- SPI_SR : (SPI Offset: 0x10) Status Register -------- */
#وصف_ڪريو AT91C_SPI_RDRF               ( 0x1 << 0 )    /* (SPI) Receive Data Register Full */
#وصف_ڪريو AT91C_SPI_TDRE               ( 0x1 << 1 )    /* (SPI) Transmit Data Register Empty */
#وصف_ڪريو AT91C_SPI_MODF               ( 0x1 << 2 )    /* (SPI) Mode Fault Error */
#وصف_ڪريو AT91C_SPI_OVRES              ( 0x1 << 3 )    /* (SPI) Overrun Error Status */
#وصف_ڪريو AT91C_SPI_ENDRX              ( 0x1 << 4 )    /* (SPI) End of Receiver Transfer */
#وصف_ڪريو AT91C_SPI_ENDTX              ( 0x1 << 5 )    /* (SPI) End of Receiver Transfer */
#وصف_ڪريو AT91C_SPI_RXBUFF             ( 0x1 << 6 )    /* (SPI) RXBUFF Interrupt */
#وصف_ڪريو AT91C_SPI_TXBUFE             ( 0x1 << 7 )    /* (SPI) TXBUFE Interrupt */
#وصف_ڪريو AT91C_SPI_NSSR               ( 0x1 << 8 )    /* (SPI) NSSR Interrupt */
#وصف_ڪريو AT91C_SPI_TXEMPTY            ( 0x1 << 9 )    /* (SPI) TXEMPTY Interrupt */
#وصف_ڪريو AT91C_SPI_SPIENS             ( 0x1 << 16 )   /* (SPI) Enable Status */
/* -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- */
/* -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- */
/* -------- SPI_IMR : (SPI Offset: 0x1c) Interrupt Mask Register -------- */
/* -------- SPI_CSR : (SPI Offset: 0x30) Chip Select Register -------- */
#وصف_ڪريو AT91C_SPI_CPOL           ( 0x1 << 0 )   /* (SPI) Clock Polarity */
#وصف_ڪريو AT91C_SPI_NCPHA          ( 0x1 << 1 )   /* (SPI) Clock Phase */
#وصف_ڪريو AT91C_SPI_CSAAT          ( 0x1 << 3 )   /* (SPI) Chip Select Active After Transfer */
#وصف_ڪريو AT91_C_SPI_بٽ           ( 0xF << 4 )   /* (SPI) Bits Per Transfer */
#وصف_ڪريو     AT91_C_SPI_بٽ_8     ( 0x0 << 4 )   /* (SPI) 8 Bits Per transfer */
#وصف_ڪريو     AT91_C_SPI_بٽ_9     ( 0x1 << 4 )   /* (SPI) 9 Bits Per transfer */
#وصف_ڪريو     AT91_C_SPI_بٽ_10    ( 0x2 << 4 )   /* (SPI) 10 Bits Per transfer */
#وصف_ڪريو     AT91_C_SPI_بٽ_11    ( 0x3 << 4 )   /* (SPI) 11 Bits Per transfer */
#وصف_ڪريو     AT91_C_SPI_بٽ_12    ( 0x4 << 4 )   /* (SPI) 12 Bits Per transfer */
#وصف_ڪريو     AT91_C_SPI_بٽ_13    ( 0x5 << 4 )   /* (SPI) 13 Bits Per transfer */
#وصف_ڪريو     AT91_C_SPI_بٽ_14    ( 0x6 << 4 )   /* (SPI) 14 Bits Per transfer */
#وصف_ڪريو     AT91_C_SPI_بٽ_15    ( 0x7 << 4 )   /* (SPI) 15 Bits Per transfer */
#وصف_ڪريو     AT91_C_SPI_بٽ_16    ( 0x8 << 4 )   /* (SPI) 16 Bits Per transfer */
#وصف_ڪريو AT91C_SPI_SCBR           ( 0xFF << 8 )  /* (SPI) Serial Clock Baud Rate */
#وصف_ڪريو AT91C_SPI_DLYBS          ( 0xFF << 16 ) /* (SPI) Delay Before SPCK */
#وصف_ڪريو AT91C_SPI_DLYBCT         ( 0xFF << 24 ) /* (SPI) Delay Between Consecutive Transfers */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Usart */
/* ***************************************************************************** */
/* *** Register offset in AT91S_USART structure *** */
#وصف_ڪريو US_CR                            ( 0 )         /* Control Register */
#وصف_ڪريو US_MR                            ( 4 )         /* Mode Register */
#وصف_ڪريو US_IER                           ( 8 )         /* Interrupt Enable Register */
#وصف_ڪريو US_IDR                           ( 12 )        /* Interrupt Disable Register */
#وصف_ڪريو US_IMR                           ( 16 )        /* Interrupt Mask Register */
#وصف_ڪريو US_CSR                           ( 20 )        /* Channel Status Register */
#وصف_ڪريو US_RHR                           ( 24 )        /* Receiver Holding Register */
#وصف_ڪريو US_THR                           ( 28 )        /* Transmitter Holding Register */
#وصف_ڪريو US_BRGR                          ( 32 )        /* Baud Rate Generator Register */
#وصف_ڪريو US_RTOR                          ( 36 )        /* Receiver Time-out Register */
#وصف_ڪريو US_TTGR                          ( 40 )        /* Transmitter Time-guard Register */
#وصف_ڪريو US_FIDI                          ( 64 )        /* FI_DI_Ratio Register */
#وصف_ڪريو US_NER                           ( 68 )        /* Nb Errors Register */
#وصف_ڪريو US_IF                            ( 76 )        /* IRDA_FILTER Register */
#وصف_ڪريو US_RPR                           ( 256 )       /* Receive Pointer Register */
#وصف_ڪريو US_RCR                           ( 260 )       /* Receive Counter Register */
#وصف_ڪريو US_TPR                           ( 264 )       /* Transmit Pointer Register */
#وصف_ڪريو US_TCR                           ( 268 )       /* Transmit Counter Register */
#وصف_ڪريو US_RNPR                          ( 272 )       /* Receive Next Pointer Register */
#وصف_ڪريو US_RNCR                          ( 276 )       /* Receive Next Counter Register */
#وصف_ڪريو US_TNPR                          ( 280 )       /* Transmit Next Pointer Register */
#وصف_ڪريو US_TNCR                          ( 284 )       /* Transmit Next Counter Register */
#وصف_ڪريو US_PTCR                          ( 288 )       /* PDC Transfer Control Register */
#وصف_ڪريو US_PTSR                          ( 292 )       /* PDC Transfer Status Register */
/* -------- US_CR : (USART Offset: 0x0) Debug Unit Control Register -------- */
#وصف_ڪريو AT91C_US_STTBRK                  ( 0x1 << 9 )  /* (USART) Start Break */
#وصف_ڪريو AT91C_US_STPBRK                  ( 0x1 << 10 ) /* (USART) Stop Break */
#وصف_ڪريو AT91C_US_STTTO                   ( 0x1 << 11 ) /* (USART) Start Time-out */
#وصف_ڪريو AT91C_US_SENDA                   ( 0x1 << 12 ) /* (USART) Send Address */
#وصف_ڪريو AT91C_US_RSTIT                   ( 0x1 << 13 ) /* (USART) Reset Iterations */
#وصف_ڪريو AT91C_US_RSTNACK                 ( 0x1 << 14 ) /* (USART) Reset Non Acknowledge */
#وصف_ڪريو AT91C_US_RETTO                   ( 0x1 << 15 ) /* (USART) Rearm Time-out */
#وصف_ڪريو AT91C_US_DTREN                   ( 0x1 << 16 ) /* (USART) Data Terminal ready Enable */
#وصف_ڪريو AT91C_US_DTRDIS                  ( 0x1 << 17 ) /* (USART) Data Terminal ready Disable */
#وصف_ڪريو AT91C_US_RTSEN                   ( 0x1 << 18 ) /* (USART) Request to Send enable */
#وصف_ڪريو AT91C_US_RTSDIS                  ( 0x1 << 19 ) /* (USART) Request to Send Disable */
/* -------- US_MR : (USART Offset: 0x4) Debug Unit Mode Register -------- */
#وصف_ڪريو AT91C_US_USMODE                  ( 0xF << 0 )  /* (USART) Usart mode */
#وصف_ڪريو     AT91_C_US_USMODE_عام       ( 0x0 )       /* (USART) Normal */
#وصف_ڪريو     AT91C_US_USMODE_RS485        ( 0x1 )       /* (USART) RS485 */
#وصف_ڪريو     AT91C_US_USMODE_HWHSH        ( 0x2 )       /* (USART) Hardware Handshaking */
#وصف_ڪريو     AT91C_US_USMODE_MODEM        ( 0x3 )       /* (USART) Modem */
#وصف_ڪريو     AT91C_US_USMODE_ISO7816_0    ( 0x4 )       /* (USART) ISO7816 protocol: T = 0 */
#وصف_ڪريو     AT91C_US_USMODE_ISO7816_1    ( 0x6 )       /* (USART) ISO7816 protocol: T = 1 */
#وصف_ڪريو     AT91C_US_USMODE_IRDA         ( 0x8 )       /* (USART) IrDA */
#وصف_ڪريو     AT91C_US_USMODE_SWHSH        ( 0xC )       /* (USART) Software Handshaking */
#وصف_ڪريو AT91C_US_CLKS                    ( 0x3 << 4 )  /* (USART) Clock Selection (Baud Rate generator Input Clock */
#وصف_ڪريو     AT91C_US_CLKS_CLOCK          ( 0x0 << 4 )  /* (USART) Clock */
#وصف_ڪريو     AT91C_US_CLKS_FDIV1          ( 0x1 << 4 )  /* (USART) fdiv1 */
#وصف_ڪريو     AT91C_US_CLKS_SLOW           ( 0x2 << 4 )  /* (USART) slow_clock (ARM) */
#وصف_ڪريو     AT91C_US_CLKS_EXT            ( 0x3 << 4 )  /* (USART) External (SCK) */
#وصف_ڪريو AT91C_US_CHRL                    ( 0x3 << 6 )  /* (USART) Clock Selection (Baud Rate generator Input Clock */
#وصف_ڪريو     AT91_C_US_CHRL_5_بٽ         ( 0x0 << 6 )  /* (USART) Character Length: 5 bits */
#وصف_ڪريو     AT91_C_US_CHRL_6_بٽ         ( 0x1 << 6 )  /* (USART) Character Length: 6 bits */
#وصف_ڪريو     AT91_C_US_CHRL_7_بٽ         ( 0x2 << 6 )  /* (USART) Character Length: 7 bits */
#وصف_ڪريو     AT91_C_US_CHRL_8_بٽ         ( 0x3 << 6 )  /* (USART) Character Length: 8 bits */
#وصف_ڪريو AT91C_US_SYNC                    ( 0x1 << 8 )  /* (USART) Synchronous Mode Select */
#وصف_ڪريو AT91C_US_NBSTOP                  ( 0x3 << 12 ) /* (USART) Number of Stop bits */
#وصف_ڪريو     AT91_C_US_NBSTOP_1_ٻٽو_انگ        ( 0x0 << 12 ) /* (USART) 1 stop bit */
#وصف_ڪريو     AT91_C_US_NBSTOP_15_ٻٽو_انگ       ( 0x1 << 12 ) /* (USART) Asynchronous (SYNC=0) 2 stop bits Synchronous (SYNC=1) 2 stop bits */
#وصف_ڪريو     AT91_C_US_NBSTOP_2_ٻٽو_انگ        ( 0x2 << 12 ) /* (USART) 2 stop bits */
#وصف_ڪريو AT91C_US_MSBF                    ( 0x1 << 16 ) /* (USART) Bit Order */
#وصف_ڪريو AT91C_US_MODE9                   ( 0x1 << 17 ) /* (USART) 9-bit Character length */
#وصف_ڪريو AT91C_US_CKLO                    ( 0x1 << 18 ) /* (USART) Clock Output Select */
#وصف_ڪريو AT91C_US_OVER                    ( 0x1 << 19 ) /* (USART) Over Sampling Mode */
#وصف_ڪريو AT91C_US_INACK                   ( 0x1 << 20 ) /* (USART) Inhibit Non Acknowledge */
#وصف_ڪريو AT91C_US_DSNACK                  ( 0x1 << 21 ) /* (USART) Disable Successive NACK */
#وصف_ڪريو AT91C_US_MAX_ITER                ( 0x1 << 24 ) /* (USART) Number of Repetitions */
#وصف_ڪريو AT91C_US_FILTER                  ( 0x1 << 28 ) /* (USART) Receive Line Filter */
/* -------- US_IER : (USART Offset: 0x8) Debug Unit Interrupt Enable Register -------- */
#وصف_ڪريو AT91C_US_RXBRK                   ( 0x1 << 2 )  /* (USART) Break Received/End of Break */
#وصف_ڪريو AT91C_US_TIMEOUT                 ( 0x1 << 8 )  /* (USART) Receiver Time-out */
#وصف_ڪريو AT91C_US_ITERATION               ( 0x1 << 10 ) /* (USART) Max number of Repetitions Reached */
#وصف_ڪريو AT91C_US_NACK                    ( 0x1 << 13 ) /* (USART) Non Acknowledge */
#وصف_ڪريو AT91C_US_RIIC                    ( 0x1 << 16 ) /* (USART) Ring INdicator Input Change Flag */
#وصف_ڪريو AT91C_US_DSRIC                   ( 0x1 << 17 ) /* (USART) Data Set Ready Input Change Flag */
#وصف_ڪريو AT91C_US_DCDIC                   ( 0x1 << 18 ) /* (USART) Data Carrier Flag */
#وصف_ڪريو AT91C_US_CTSIC                   ( 0x1 << 19 ) /* (USART) Clear To Send Input Change Flag */
/* -------- US_IDR : (USART Offset: 0xc) Debug Unit Interrupt Disable Register -------- */
/* -------- US_IMR : (USART Offset: 0x10) Debug Unit Interrupt Mask Register -------- */
/* -------- US_CSR : (USART Offset: 0x14) Debug Unit Channel Status Register -------- */
#وصف_ڪريو AT91C_US_RI     ( 0x1 << 20 )         /* (USART) Image of RI Input */
#وصف_ڪريو AT91C_US_DSR    ( 0x1 << 21 )         /* (USART) Image of DSR Input */
#وصف_ڪريو AT91C_US_DCD    ( 0x1 << 22 )         /* (USART) Image of DCD Input */
#وصف_ڪريو AT91C_US_CTS    ( 0x1 << 23 )         /* (USART) Image of CTS Input */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Synchronous Serial Controller Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_SSC structure *** */
#وصف_ڪريو SSC_CR                            ( 0 )          /* Control Register */
#وصف_ڪريو SSC_CMR                           ( 4 )          /* Clock Mode Register */
#وصف_ڪريو SSC_RCMR                          ( 16 )         /* Receive Clock ModeRegister */
#وصف_ڪريو SSC_RFMR                          ( 20 )         /* Receive Frame Mode Register */
#وصف_ڪريو SSC_TCMR                          ( 24 )         /* Transmit Clock Mode Register */
#وصف_ڪريو SSC_TFMR                          ( 28 )         /* Transmit Frame Mode Register */
#وصف_ڪريو SSC_RHR                           ( 32 )         /* Receive Holding Register */
#وصف_ڪريو SSC_THR                           ( 36 )         /* Transmit Holding Register */
#وصف_ڪريو SSC_RSHR                          ( 48 )         /* Receive Sync Holding Register */
#وصف_ڪريو SSC_TSHR                          ( 52 )         /* Transmit Sync Holding Register */
#وصف_ڪريو SSC_SR                            ( 64 )         /* Status Register */
#وصف_ڪريو SSC_IER                           ( 68 )         /* Interrupt Enable Register */
#وصف_ڪريو SSC_IDR                           ( 72 )         /* Interrupt Disable Register */
#وصف_ڪريو SSC_IMR                           ( 76 )         /* Interrupt Mask Register */
#وصف_ڪريو SSC_RPR                           ( 256 )        /* Receive Pointer Register */
#وصف_ڪريو SSC_RCR                           ( 260 )        /* Receive Counter Register */
#وصف_ڪريو SSC_TPR                           ( 264 )        /* Transmit Pointer Register */
#وصف_ڪريو SSC_TCR                           ( 268 )        /* Transmit Counter Register */
#وصف_ڪريو SSC_RNPR                          ( 272 )        /* Receive Next Pointer Register */
#وصف_ڪريو SSC_RNCR                          ( 276 )        /* Receive Next Counter Register */
#وصف_ڪريو SSC_TNPR                          ( 280 )        /* Transmit Next Pointer Register */
#وصف_ڪريو SSC_TNCR                          ( 284 )        /* Transmit Next Counter Register */
#وصف_ڪريو SSC_PTCR                          ( 288 )        /* PDC Transfer Control Register */
#وصف_ڪريو SSC_PTSR                          ( 292 )        /* PDC Transfer Status Register */
/* -------- SSC_CR : (SSC Offset: 0x0) SSC Control Register -------- */
#وصف_ڪريو AT91C_SSC_RXEN                    ( 0x1 << 0 )   /* (SSC) Receive Enable */
#وصف_ڪريو AT91C_SSC_RXDIS                   ( 0x1 << 1 )   /* (SSC) Receive Disable */
#وصف_ڪريو AT91C_SSC_TXEN                    ( 0x1 << 8 )   /* (SSC) Transmit Enable */
#وصف_ڪريو AT91C_SSC_TXDIS                   ( 0x1 << 9 )   /* (SSC) Transmit Disable */
#وصف_ڪريو AT91C_SSC_SWRST                   ( 0x1 << 15 )  /* (SSC) Software Reset */
/* -------- SSC_RCMR : (SSC Offset: 0x10) SSC Receive Clock Mode Register -------- */
#وصف_ڪريو AT91C_SSC_CKS                     ( 0x3 << 0 )   /* (SSC) Receive/Transmit Clock Selection */
#وصف_ڪريو     AT91C_SSC_CKS_DIV             ( 0x0 )        /* (SSC) Divided Clock */
#وصف_ڪريو     AT91C_SSC_CKS_TK              ( 0x1 )        /* (SSC) TK Clock signal */
#وصف_ڪريو     AT91C_SSC_CKS_RK              ( 0x2 )        /* (SSC) RK pin */
#وصف_ڪريو AT91C_SSC_CKO                     ( 0x7 << 2 )   /* (SSC) Receive/Transmit Clock Output Mode Selection */
#وصف_ڪريو     AT91C_SSC_CKO_NONE            ( 0x0 << 2 )   /* (SSC) Receive/Transmit Clock Output Mode: None RK pin: Input-only */
#وصف_ڪريو     AT91C_SSC_CKO_CONTINUOUS      ( 0x1 << 2 )   /* (SSC) Continuous Receive/Transmit Clock RK pin: Output */
#وصف_ڪريو     AT91_C_SSC_CKO_معلومات_TX         ( 0x2 << 2 )   /* (SSC) Receive/Transmit Clock only during data transfers RK pin: Output */
#وصف_ڪريو AT91C_SSC_CKI                     ( 0x1 << 5 )   /* (SSC) Receive/Transmit Clock Inversion */
#وصف_ڪريو AT91_C_SSC_شروعات                   ( 0xF << 8 )   /* (SSC) Receive/Transmit Start Selection */
#وصف_ڪريو     AT91_C_SSC_شروعات_CONTINUOUS    ( 0x0 << 8 )   /* (SSC) Continuous, as soon as the receiver is enabled, and immediately after the end of transfer of the previous data. */
#وصف_ڪريو     AT91_C_SSC_شروعات_TX            ( 0x1 << 8 )   /* (SSC) Transmit/Receive start */
#وصف_ڪريو     AT91_C_SSC_شروعات_هيٺيون_RF        ( 0x2 << 8 )   /* (SSC) Detection of a low level on RF input */
#وصف_ڪريو     AT91_C_SSC_شروعات_مٿاهون_RF       ( 0x3 << 8 )   /* (SSC) Detection of a high level on RF input */
#وصف_ڪريو     AT91_C_SSC_شروعات_FALL_RF       ( 0x4 << 8 )   /* (SSC) Detection of a falling edge on RF input */
#وصف_ڪريو     AT91_C_SSC_شروعات_RISE_RF       ( 0x5 << 8 )   /* (SSC) Detection of a rising edge on RF input */
#وصف_ڪريو     AT91_C_SSC_شروعات_LEVEL_RF      ( 0x6 << 8 )   /* (SSC) Detection of any level change on RF input */
#وصف_ڪريو     AT91_C_SSC_شروعات_ڪنارو_RF       ( 0x7 << 8 )   /* (SSC) Detection of any edge on RF input */
#وصف_ڪريو     AT91_C_SSC_شروعات_0             ( 0x8 << 8 )   /* (SSC) Compare 0 */
#وصف_ڪريو AT91C_SSC_STTDLY                  ( 0xFF << 16 ) /* (SSC) Receive/Transmit Start Delay */
#وصف_ڪريو AT91C_SSC_PERIOD                  ( 0xFF << 24 ) /* (SSC) Receive/Transmit Period Divider Selection */
/* -------- SSC_RFMR : (SSC Offset: 0x14) SSC Receive Frame Mode Register -------- */
#وصف_ڪريو AT91C_SSC_DATLEN                  ( 0x1F << 0 )  /* (SSC) Data Length */
#وصف_ڪريو AT91C_SSC_LOOP                    ( 0x1 << 5 )   /* (SSC) Loop Mode */
#وصف_ڪريو AT91C_SSC_MSBF                    ( 0x1 << 7 )   /* (SSC) Most Significant Bit First */
#وصف_ڪريو AT91C_SSC_DATNB                   ( 0xF << 8 )   /* (SSC) Data Number per Frame */
#وصف_ڪريو AT91C_SSC_FSLEN                   ( 0xF << 16 )  /* (SSC) Receive/Transmit Frame Sync length */
#وصف_ڪريو AT91C_SSC_FSOS                    ( 0x7 << 20 )  /* (SSC) Receive/Transmit Frame Sync Output Selection */
#وصف_ڪريو     AT91C_SSC_FSOS_NONE           ( 0x0 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: None RK pin Input-only */
#وصف_ڪريو     AT91C_SSC_FSOS_NEGATIVE       ( 0x1 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Negative Pulse */
#وصف_ڪريو     AT91_C_SSC_FSOS_مثبت       ( 0x2 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Positive Pulse */
#وصف_ڪريو     AT91_C_SSC_FSOS_هيٺيون            ( 0x3 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Driver Low during data transfer */
#وصف_ڪريو     AT91_C_SSC_FSOS_مٿاهون           ( 0x4 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Driver High during data transfer */
#وصف_ڪريو     AT91C_SSC_FSOS_TOGGLE         ( 0x5 << 20 )  /* (SSC) Selected Receive/Transmit Frame Sync Signal: Toggling at each start of data transfer */
#وصف_ڪريو AT91C_SSC_FSEDGE                  ( 0x1 << 24 )  /* (SSC) Frame Sync Edge Detection */
/* -------- SSC_TCMR : (SSC Offset: 0x18) SSC Transmit Clock Mode Register -------- */
/* -------- SSC_TFMR : (SSC Offset: 0x1c) SSC Transmit Frame Mode Register -------- */
#وصف_ڪريو AT91C_SSC_DATDEF                  ( 0x1 << 5 )  /* (SSC) Data Default Value */
#وصف_ڪريو AT91C_SSC_FSDEN                   ( 0x1 << 23 ) /* (SSC) Frame Sync Data Enable */
/* -------- SSC_SR : (SSC Offset: 0x40) SSC Status Register -------- */
#وصف_ڪريو AT91C_SSC_TXRDY                   ( 0x1 << 0 )  /* (SSC) Transmit Ready */
#وصف_ڪريو AT91C_SSC_TXEMPTY                 ( 0x1 << 1 )  /* (SSC) Transmit Empty */
#وصف_ڪريو AT91C_SSC_ENDTX                   ( 0x1 << 2 )  /* (SSC) End Of Transmission */
#وصف_ڪريو AT91C_SSC_TXBUFE                  ( 0x1 << 3 )  /* (SSC) Transmit Buffer Empty */
#وصف_ڪريو AT91C_SSC_RXRDY                   ( 0x1 << 4 )  /* (SSC) Receive Ready */
#وصف_ڪريو AT91C_SSC_OVRUN                   ( 0x1 << 5 )  /* (SSC) Receive Overrun */
#وصف_ڪريو AT91C_SSC_ENDRX                   ( 0x1 << 6 )  /* (SSC) End of Reception */
#وصف_ڪريو AT91C_SSC_RXBUFF                  ( 0x1 << 7 )  /* (SSC) Receive Buffer Full */
#وصف_ڪريو AT91C_SSC_TXSYN                   ( 0x1 << 10 ) /* (SSC) Transmit Sync */
#وصف_ڪريو AT91C_SSC_RXSYN                   ( 0x1 << 11 ) /* (SSC) Receive Sync */
#وصف_ڪريو AT91C_SSC_TXENA                   ( 0x1 << 16 ) /* (SSC) Transmit Enable */
#وصف_ڪريو AT91C_SSC_RXENA                   ( 0x1 << 17 ) /* (SSC) Receive Enable */
/* -------- SSC_IER : (SSC Offset: 0x44) SSC Interrupt Enable Register -------- */
/* -------- SSC_IDR : (SSC Offset: 0x48) SSC Interrupt Disable Register -------- */
/* -------- SSC_IMR : (SSC Offset: 0x4c) SSC Interrupt Mask Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Two-wire Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_TWI structure *** */
#وصف_ڪريو TWI_CR                         ( 0 )          /* Control Register */
#وصف_ڪريو TWI_MMR                        ( 4 )          /* Master Mode Register */
#وصف_ڪريو TWI_IADR                       ( 12 )         /* Internal Address Register */
#وصف_ڪريو TWI_CWGR                       ( 16 )         /* Clock Waveform Generator Register */
#وصف_ڪريو TWI_SR                         ( 32 )         /* Status Register */
#وصف_ڪريو TWI_IER                        ( 36 )         /* Interrupt Enable Register */
#وصف_ڪريو TWI_IDR                        ( 40 )         /* Interrupt Disable Register */
#وصف_ڪريو TWI_IMR                        ( 44 )         /* Interrupt Mask Register */
#وصف_ڪريو TWI_RHR                        ( 48 )         /* Receive Holding Register */
#وصف_ڪريو TWI_THR                        ( 52 )         /* Transmit Holding Register */
/* -------- TWI_CR : (TWI Offset: 0x0) TWI Control Register -------- */
#وصف_ڪريو AT91_C_TWI_شروعات                ( 0x1 << 0 )   /* (TWI) Send a START Condition */
#وصف_ڪريو AT91C_TWI_STOP                 ( 0x1 << 1 )   /* (TWI) Send a STOP Condition */
#وصف_ڪريو AT91C_TWI_MSEN                 ( 0x1 << 2 )   /* (TWI) TWI Master Transfer Enabled */
#وصف_ڪريو AT91C_TWI_MSDIS                ( 0x1 << 3 )   /* (TWI) TWI Master Transfer Disabled */
#وصف_ڪريو AT91C_TWI_SWRST                ( 0x1 << 7 )   /* (TWI) Software Reset */
/* -------- TWI_MMR : (TWI Offset: 0x4) TWI Master Mode Register -------- */
#وصف_ڪريو AT91C_TWI_IADRSZ               ( 0x3 << 8 )   /* (TWI) Internal Device Address Size */
#وصف_ڪريو     AT91C_TWI_IADRSZ_NO        ( 0x0 << 8 )   /* (TWI) No internal device address */
#وصف_ڪريو     AT91C_TWI_IADRSZ_1_BYTE    ( 0x1 << 8 )   /* (TWI) One-byte internal device address */
#وصف_ڪريو     AT91C_TWI_IADRSZ_2_BYTE    ( 0x2 << 8 )   /* (TWI) Two-byte internal device address */
#وصف_ڪريو     AT91C_TWI_IADRSZ_3_BYTE    ( 0x3 << 8 )   /* (TWI) Three-byte internal device address */
#وصف_ڪريو AT91C_TWI_MREAD                ( 0x1 << 12 )  /* (TWI) Master Read Direction */
#وصف_ڪريو AT91C_TWI_DADR                 ( 0x7F << 16 ) /* (TWI) Device Address */
/* -------- TWI_CWGR : (TWI Offset: 0x10) TWI Clock Waveform Generator Register -------- */
#وصف_ڪريو AT91C_TWI_CLDIV                ( 0xFF << 0 )  /* (TWI) Clock Low Divider */
#وصف_ڪريو AT91C_TWI_CHDIV                ( 0xFF << 8 )  /* (TWI) Clock High Divider */
#وصف_ڪريو AT91C_TWI_CKDIV                ( 0x7 << 16 )  /* (TWI) Clock Divider */
/* -------- TWI_SR : (TWI Offset: 0x20) TWI Status Register -------- */
#وصف_ڪريو AT91C_TWI_TXCOMP               ( 0x1 << 0 )   /* (TWI) Transmission Completed */
#وصف_ڪريو AT91C_TWI_RXRDY                ( 0x1 << 1 )   /* (TWI) Receive holding register ReaDY */
#وصف_ڪريو AT91C_TWI_TXRDY                ( 0x1 << 2 )   /* (TWI) Transmit holding register ReaDY */
#وصف_ڪريو AT91C_TWI_OVRE                 ( 0x1 << 6 )   /* (TWI) Overrun Error */
#وصف_ڪريو AT91C_TWI_UNRE                 ( 0x1 << 7 )   /* (TWI) Underrun Error */
#وصف_ڪريو AT91C_TWI_NACK                 ( 0x1 << 8 )   /* (TWI) Not Acknowledged */
/* -------- TWI_IER : (TWI Offset: 0x24) TWI Interrupt Enable Register -------- */
/* -------- TWI_IDR : (TWI Offset: 0x28) TWI Interrupt Disable Register -------- */
/* -------- TWI_IMR : (TWI Offset: 0x2c) TWI Interrupt Mask Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR PWMC Channel Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_PWMC_CH structure *** */
#وصف_ڪريو PWMC_CMR                    ( 0 )         /* Channel Mode Register */
#وصف_ڪريو PWMC_CDTYR                  ( 4 )         /* Channel Duty Cycle Register */
#وصف_ڪريو PWMC_CPRDR                  ( 8 )         /* Channel Period Register */
#وصف_ڪريو PWMC_CCNTR                  ( 12 )        /* Channel Counter Register */
#وصف_ڪريو PWMC_CUPDR                  ( 16 )        /* Channel Update Register */
#وصف_ڪريو PWMC_Reserved               ( 20 )        /* Reserved */
/* -------- PWMC_CMR : (PWMC_CH Offset: 0x0) PWMC Channel Mode Register -------- */
#وصف_ڪريو AT91C_PWMC_CPRE             ( 0xF << 0 )  /* (PWMC_CH) Channel Pre-scaler : PWMC_CLKx */
#وصف_ڪريو     AT91C_PWMC_CPRE_MCK     ( 0x0 )       /* (PWMC_CH) */
#وصف_ڪريو     AT91C_PWMC_CPRE_MCKA    ( 0xB )       /* (PWMC_CH) */
#وصف_ڪريو     AT91C_PWMC_CPRE_MCKB    ( 0xC )       /* (PWMC_CH) */
#وصف_ڪريو AT91C_PWMC_CALG             ( 0x1 << 8 )  /* (PWMC_CH) Channel Alignment */
#وصف_ڪريو AT91C_PWMC_CPOL             ( 0x1 << 9 )  /* (PWMC_CH) Channel Polarity */
#وصف_ڪريو AT91C_PWMC_CPD              ( 0x1 << 10 ) /* (PWMC_CH) Channel Update Period */
/* -------- PWMC_CDTYR : (PWMC_CH Offset: 0x4) PWMC Channel Duty Cycle Register -------- */
#وصف_ڪريو AT91C_PWMC_CDTY             ( 0x0 << 0 )  /* (PWMC_CH) Channel Duty Cycle */
/* -------- PWMC_CPRDR : (PWMC_CH Offset: 0x8) PWMC Channel Period Register -------- */
#وصف_ڪريو AT91C_PWMC_CPRD             ( 0x0 << 0 )  /* (PWMC_CH) Channel Period */
/* -------- PWMC_CCNTR : (PWMC_CH Offset: 0xc) PWMC Channel Counter Register -------- */
#وصف_ڪريو AT91C_PWMC_CCNT             ( 0x0 << 0 )  /* (PWMC_CH) Channel Counter */
/* -------- PWMC_CUPDR : (PWMC_CH Offset: 0x10) PWMC Channel Update Register -------- */
#وصف_ڪريو AT91C_PWMC_CUPD             ( 0x0 << 0 )  /* (PWMC_CH) Channel Update */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Pulse Width Modulation Controller Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_PWMC structure *** */
#وصف_ڪريو PWMC_MR                    ( 0 )          /* PWMC Mode Register */
#وصف_ڪريو PWMC_ENA                   ( 4 )          /* PWMC Enable Register */
#وصف_ڪريو PWMC_DIS                   ( 8 )          /* PWMC Disable Register */
#وصف_ڪريو PWMC_SR                    ( 12 )         /* PWMC Status Register */
#وصف_ڪريو PWMC_IER                   ( 16 )         /* PWMC Interrupt Enable Register */
#وصف_ڪريو PWMC_IDR                   ( 20 )         /* PWMC Interrupt Disable Register */
#وصف_ڪريو PWMC_IMR                   ( 24 )         /* PWMC Interrupt Mask Register */
#وصف_ڪريو PWMC_ISR                   ( 28 )         /* PWMC Interrupt Status Register */
#وصف_ڪريو PWMC_VR                    ( 252 )        /* PWMC Version Register */
#وصف_ڪريو PWMC_CH                    ( 512 )        /* PWMC Channel */
/* -------- PWMC_MR : (PWMC Offset: 0x0) PWMC Mode Register -------- */
#وصف_ڪريو AT91C_PWMC_DIVA            ( 0xFF << 0 )  /* (PWMC) CLKA divide factor. */
#وصف_ڪريو AT91C_PWMC_PREA            ( 0xF << 8 )   /* (PWMC) Divider Input Clock Prescaler A */
#وصف_ڪريو     AT91C_PWMC_PREA_MCK    ( 0x0 << 8 )   /* (PWMC) */
#وصف_ڪريو AT91C_PWMC_DIVB            ( 0xFF << 16 ) /* (PWMC) CLKB divide factor. */
#وصف_ڪريو AT91C_PWMC_PREB            ( 0xF << 24 )  /* (PWMC) Divider Input Clock Prescaler B */
#وصف_ڪريو     AT91C_PWMC_PREB_MCK    ( 0x0 << 24 )  /* (PWMC) */
/* -------- PWMC_ENA : (PWMC Offset: 0x4) PWMC Enable Register -------- */
#وصف_ڪريو AT91C_PWMC_CHID0           ( 0x1 << 0 )   /* (PWMC) Channel ID 0 */
#وصف_ڪريو AT91C_PWMC_CHID1           ( 0x1 << 1 )   /* (PWMC) Channel ID 1 */
#وصف_ڪريو AT91C_PWMC_CHID2           ( 0x1 << 2 )   /* (PWMC) Channel ID 2 */
#وصف_ڪريو AT91C_PWMC_CHID3           ( 0x1 << 3 )   /* (PWMC) Channel ID 3 */
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
#وصف_ڪريو UDP_انگ              ( 0 )          /* Frame Number Register */
#وصف_ڪريو UDP_GLBSTATE         ( 4 )          /* Global State Register */
#وصف_ڪريو UDP_FADDR            ( 8 )          /* Function Address Register */
#وصف_ڪريو UDP_IER              ( 16 )         /* Interrupt Enable Register */
#وصف_ڪريو UDP_IDR              ( 20 )         /* Interrupt Disable Register */
#وصف_ڪريو UDP_IMR              ( 24 )         /* Interrupt Mask Register */
#وصف_ڪريو UDP_ISR              ( 28 )         /* Interrupt Status Register */
#وصف_ڪريو UDP_ICR              ( 32 )         /* Interrupt Clear Register */
#وصف_ڪريو UDP_RSTEP            ( 40 )         /* Reset Endpoint Register */
#وصف_ڪريو UDP_CSR              ( 48 )         /* Endpoint Control and Status Register */
#وصف_ڪريو UDP_FDR              ( 80 )         /* Endpoint FIFO Data Register */
#وصف_ڪريو UDP_TXVC             ( 116 )        /* Transceiver Control Register */
/* -------- UDP_FRM_NUM : (UDP Offset: 0x0) USB Frame Number Register -------- */
#وصف_ڪريو AT91_C_UDP_FRM_انگ    ( 0x7FF << 0 ) /* (UDP) Frame Number as Defined in the Packet Field Formats */
#وصف_ڪريو AT91C_UDP_FRM_ERR    ( 0x1 << 16 )  /* (UDP) Frame Error */
#وصف_ڪريو AT91C_UDP_FRM_OK     ( 0x1 << 17 )  /* (UDP) Frame OK */
/* -------- UDP_GLB_STATE : (UDP Offset: 0x4) USB Global State Register -------- */
#وصف_ڪريو AT91C_UDP_FADDEN     ( 0x1 << 0 )   /* (UDP) Function Address Enable */
#وصف_ڪريو AT91C_UDP_CONFG      ( 0x1 << 1 )   /* (UDP) Configured */
#وصف_ڪريو AT91C_UDP_ESR        ( 0x1 << 2 )   /* (UDP) Enable Send Resume */
#وصف_ڪريو AT91C_UDP_RSMINPR    ( 0x1 << 3 )   /* (UDP) A Resume Has Been Sent to the Host */
#وصف_ڪريو AT91C_UDP_RMWUPE     ( 0x1 << 4 )   /* (UDP) Remote Wake Up Enable */
/* -------- UDP_FADDR : (UDP Offset: 0x8) USB Function Address Register -------- */
#وصف_ڪريو AT91C_UDP_FADD       ( 0xFF << 0 )  /* (UDP) Function Address Value */
#وصف_ڪريو AT91C_UDP_FEN        ( 0x1 << 8 )   /* (UDP) Function Enable */
/* -------- UDP_IER : (UDP Offset: 0x10) USB Interrupt Enable Register -------- */
#وصف_ڪريو AT91C_UDP_EPINT0     ( 0x1 << 0 )   /* (UDP) Endpoint 0 Interrupt */
#وصف_ڪريو AT91C_UDP_EPINT1     ( 0x1 << 1 )   /* (UDP) Endpoint 0 Interrupt */
#وصف_ڪريو AT91C_UDP_EPINT2     ( 0x1 << 2 )   /* (UDP) Endpoint 2 Interrupt */
#وصف_ڪريو AT91C_UDP_EPINT3     ( 0x1 << 3 )   /* (UDP) Endpoint 3 Interrupt */
#وصف_ڪريو AT91C_UDP_EPINT4     ( 0x1 << 4 )   /* (UDP) Endpoint 4 Interrupt */
#وصف_ڪريو AT91C_UDP_EPINT5     ( 0x1 << 5 )   /* (UDP) Endpoint 5 Interrupt */
#وصف_ڪريو AT91C_UDP_RXSUSP     ( 0x1 << 8 )   /* (UDP) USB Suspend Interrupt */
#وصف_ڪريو AT91C_UDP_RXRSM      ( 0x1 << 9 )   /* (UDP) USB Resume Interrupt */
#وصف_ڪريو AT91C_UDP_EXTRSM     ( 0x1 << 10 )  /* (UDP) USB External Resume Interrupt */
#وصف_ڪريو AT91C_UDP_SOFINT     ( 0x1 << 11 )  /* (UDP) USB Start Of frame Interrupt */
#وصف_ڪريو AT91C_UDP_WAKEUP     ( 0x1 << 13 )  /* (UDP) USB Resume Interrupt */
/* -------- UDP_IDR : (UDP Offset: 0x14) USB Interrupt Disable Register -------- */
/* -------- UDP_IMR : (UDP Offset: 0x18) USB Interrupt Mask Register -------- */
/* -------- UDP_ISR : (UDP Offset: 0x1c) USB Interrupt Status Register -------- */
#وصف_ڪريو AT91C_UDP_ENDBUSRES              ( 0x1 << 12 ) /* (UDP) USB End Of Bus Reset Interrupt */
/* -------- UDP_ICR : (UDP Offset: 0x20) USB Interrupt Clear Register -------- */
/* -------- UDP_RST_EP : (UDP Offset: 0x28) USB Reset Endpoint Register -------- */
#وصف_ڪريو AT91C_UDP_EP0                    ( 0x1 << 0 )    /* (UDP) Reset Endpoint 0 */
#وصف_ڪريو AT91C_UDP_EP1                    ( 0x1 << 1 )    /* (UDP) Reset Endpoint 1 */
#وصف_ڪريو AT91C_UDP_EP2                    ( 0x1 << 2 )    /* (UDP) Reset Endpoint 2 */
#وصف_ڪريو AT91C_UDP_EP3                    ( 0x1 << 3 )    /* (UDP) Reset Endpoint 3 */
#وصف_ڪريو AT91C_UDP_EP4                    ( 0x1 << 4 )    /* (UDP) Reset Endpoint 4 */
#وصف_ڪريو AT91C_UDP_EP5                    ( 0x1 << 5 )    /* (UDP) Reset Endpoint 5 */
/* -------- UDP_CSR : (UDP Offset: 0x30) USB Endpoint Control and Status Register -------- */
#وصف_ڪريو AT91C_UDP_TXCOMP                 ( 0x1 << 0 )    /* (UDP) Generates an IN packet with data previously written in the DPR */
#وصف_ڪريو AT91_C_UDP_RX_معلومات_BK0            ( 0x1 << 1 )    /* (UDP) Receive Data Bank 0 */
#وصف_ڪريو AT91C_UDP_RXSETUP                ( 0x1 << 2 )    /* (UDP) Sends STALL to the Host (Control endpoints) */
#وصف_ڪريو AT91C_UDP_ISOERROR               ( 0x1 << 3 )    /* (UDP) Isochronous error (Isochronous endpoints) */
#وصف_ڪريو AT91C_UDP_TXPKTRDY               ( 0x1 << 4 )    /* (UDP) Transmit Packet Ready */
#وصف_ڪريو AT91C_UDP_FORCESTALL             ( 0x1 << 5 )    /* (UDP) Force Stall (used by Control, Bulk and Isochronous endpoints). */
#وصف_ڪريو AT91_C_UDP_RX_معلومات_BK1            ( 0x1 << 6 )    /* (UDP) Receive Data Bank 1 (only used by endpoints with ping-pong attributes). */
#وصف_ڪريو AT91C_UDP_DIR                    ( 0x1 << 7 )    /* (UDP) Transfer Direction */
#وصف_ڪريو AT91C_UDP_EPTYPE                 ( 0x7 << 8 )    /* (UDP) Endpoint type */
#وصف_ڪريو     AT91C_UDP_EPTYPE_CTRL        ( 0x0 << 8 )    /* (UDP) Control */
#وصف_ڪريو     AT91_C_UDP_EPTYPE_ISO_ٻاهريون     ( 0x1 << 8 )    /* (UDP) Isochronous OUT */
#وصف_ڪريو     AT91_C_UDP_EPTYPE_BULK_ٻاهريون    ( 0x2 << 8 )    /* (UDP) Bulk OUT */
#وصف_ڪريو     AT91_C_UDP_EPTYPE_INT_ٻاهريون     ( 0x3 << 8 )    /* (UDP) Interrupt OUT */
#وصف_ڪريو     AT91_C_UDP_EPTYPE_ISO_اندريون      ( 0x5 << 8 )    /* (UDP) Isochronous IN */
#وصف_ڪريو     AT91_C_UDP_EPTYPE_BULK_اندريون     ( 0x6 << 8 )    /* (UDP) Bulk IN */
#وصف_ڪريو     AT91_C_UDP_EPTYPE_INT_اندريون      ( 0x7 << 8 )    /* (UDP) Interrupt IN */
#وصف_ڪريو AT91C_UDP_DTGLE                  ( 0x1 << 11 )   /* (UDP) Data Toggle */
#وصف_ڪريو AT91C_UDP_EPEDS                  ( 0x1 << 15 )   /* (UDP) Endpoint Enable Disable */
#وصف_ڪريو AT91C_UDP_RXBYTECNT              ( 0x7FF << 16 ) /* (UDP) Number Of Bytes Available in the FIFO */
/* -------- UDP_TXVC : (UDP Offset: 0x74) Transceiver Control Register -------- */
#وصف_ڪريو AT91C_UDP_TXVDIS                 ( 0x1 << 8 )    /* (UDP) */
#وصف_ڪريو AT91C_UDP_PUON                   ( 0x1 << 9 )    /* (UDP) Pull-up ON */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Timer Counter Channel Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_TC structure *** */
#وصف_ڪريو TC_CCR                                ( 0 )         /* Channel Control Register */
#وصف_ڪريو TC_CMR                                ( 4 )         /* Channel Mode Register (Capture Mode / Waveform Mode) */
#وصف_ڪريو TC_CV                                 ( 16 )        /* Counter Value */
#وصف_ڪريو TC_RA                                 ( 20 )        /* Register A */
#وصف_ڪريو TC_RB                                 ( 24 )        /* Register B */
#وصف_ڪريو TC_RC                                 ( 28 )        /* Register C */
#وصف_ڪريو TC_SR                                 ( 32 )        /* Status Register */
#وصف_ڪريو TC_IER                                ( 36 )        /* Interrupt Enable Register */
#وصف_ڪريو TC_IDR                                ( 40 )        /* Interrupt Disable Register */
#وصف_ڪريو TC_IMR                                ( 44 )        /* Interrupt Mask Register */
/* -------- TC_CCR : (TC Offset: 0x0) TC Channel Control Register -------- */
#وصف_ڪريو AT91C_TC_CLKEN                        ( 0x1 << 0 )  /* (TC) Counter Clock Enable Command */
#وصف_ڪريو AT91C_TC_CLKDIS                       ( 0x1 << 1 )  /* (TC) Counter Clock Disable Command */
#وصف_ڪريو AT91C_TC_SWTRG                        ( 0x1 << 2 )  /* (TC) Software Trigger Command */
/* -------- TC_CMR : (TC Offset: 0x4) TC Channel Mode Register: Capture Mode / Waveform Mode -------- */
#وصف_ڪريو AT91C_TC_CLKS                         ( 0x7 << 0 )  /* (TC) Clock Selection */
#وصف_ڪريو     AT91C_TC_CLKS_TIMER_DIV1_CLOCK    ( 0x0 )       /* (TC) Clock selected: TIMER_DIV1_CLOCK */
#وصف_ڪريو     AT91C_TC_CLKS_TIMER_DIV2_CLOCK    ( 0x1 )       /* (TC) Clock selected: TIMER_DIV2_CLOCK */
#وصف_ڪريو     AT91C_TC_CLKS_TIMER_DIV3_CLOCK    ( 0x2 )       /* (TC) Clock selected: TIMER_DIV3_CLOCK */
#وصف_ڪريو     AT91C_TC_CLKS_TIMER_DIV4_CLOCK    ( 0x3 )       /* (TC) Clock selected: TIMER_DIV4_CLOCK */
#وصف_ڪريو     AT91C_TC_CLKS_TIMER_DIV5_CLOCK    ( 0x4 )       /* (TC) Clock selected: TIMER_DIV5_CLOCK */
#وصف_ڪريو     AT91C_TC_CLKS_XC0                 ( 0x5 )       /* (TC) Clock selected: XC0 */
#وصف_ڪريو     AT91C_TC_CLKS_XC1                 ( 0x6 )       /* (TC) Clock selected: XC1 */
#وصف_ڪريو     AT91C_TC_CLKS_XC2                 ( 0x7 )       /* (TC) Clock selected: XC2 */
#وصف_ڪريو AT91C_TC_CLKI                         ( 0x1 << 3 )  /* (TC) Clock Invert */
#وصف_ڪريو AT91_C_TC_مدو                        ( 0x3 << 4 )  /* (TC) Burst Signal Selection */
#وصف_ڪريو     AT91_C_TC_مدو_NONE               ( 0x0 << 4 )  /* (TC) The clock is not gated by an external signal */
#وصف_ڪريو     AT91_C_TC_مدو_XC0                ( 0x1 << 4 )  /* (TC) XC0 is ANDed with the selected clock */
#وصف_ڪريو     AT91_C_TC_مدو_XC1                ( 0x2 << 4 )  /* (TC) XC1 is ANDed with the selected clock */
#وصف_ڪريو     AT91_C_TC_مدو_XC2                ( 0x3 << 4 )  /* (TC) XC2 is ANDed with the selected clock */
#وصف_ڪريو AT91C_TC_CPCSTOP                      ( 0x1 << 6 )  /* (TC) Counter Clock Stopped with RC Compare */
#وصف_ڪريو AT91C_TC_LDBSTOP                      ( 0x1 << 6 )  /* (TC) Counter Clock Stopped with RB Loading */
#وصف_ڪريو AT91C_TC_CPCDIS                       ( 0x1 << 7 )  /* (TC) Counter Clock Disable with RC Compare */
#وصف_ڪريو AT91C_TC_LDBDIS                       ( 0x1 << 7 )  /* (TC) Counter Clock Disabled with RB Loading */
#وصف_ڪريو AT91C_TC_ETRGEDG                      ( 0x3 << 8 )  /* (TC) External Trigger Edge Selection */
#وصف_ڪريو     AT91C_TC_ETRGEDG_NONE             ( 0x0 << 8 )  /* (TC) Edge: None */
#وصف_ڪريو     AT91C_TC_ETRGEDG_RISING           ( 0x1 << 8 )  /* (TC) Edge: rising edge */
#وصف_ڪريو     AT91C_TC_ETRGEDG_FALLING          ( 0x2 << 8 )  /* (TC) Edge: falling edge */
#وصف_ڪريو     AT91C_TC_ETRGEDG_BOTH             ( 0x3 << 8 )  /* (TC) Edge: each edge */
#وصف_ڪريو AT91C_TC_EEVTEDG                      ( 0x3 << 8 )  /* (TC) External Event Edge Selection */
#وصف_ڪريو     AT91C_TC_EEVTEDG_NONE             ( 0x0 << 8 )  /* (TC) Edge: None */
#وصف_ڪريو     AT91C_TC_EEVTEDG_RISING           ( 0x1 << 8 )  /* (TC) Edge: rising edge */
#وصف_ڪريو     AT91C_TC_EEVTEDG_FALLING          ( 0x2 << 8 )  /* (TC) Edge: falling edge */
#وصف_ڪريو     AT91C_TC_EEVTEDG_BOTH             ( 0x3 << 8 )  /* (TC) Edge: each edge */
#وصف_ڪريو AT91C_TC_EEVT                         ( 0x3 << 10 ) /* (TC) External Event  Selection */
#وصف_ڪريو     AT91C_TC_EEVT_TIOB                ( 0x0 << 10 ) /* (TC) Signal selected as external event: TIOB TIOB direction: input */
#وصف_ڪريو     AT91C_TC_EEVT_XC0                 ( 0x1 << 10 ) /* (TC) Signal selected as external event: XC0 TIOB direction: output */
#وصف_ڪريو     AT91C_TC_EEVT_XC1                 ( 0x2 << 10 ) /* (TC) Signal selected as external event: XC1 TIOB direction: output */
#وصف_ڪريو     AT91C_TC_EEVT_XC2                 ( 0x3 << 10 ) /* (TC) Signal selected as external event: XC2 TIOB direction: output */
#وصف_ڪريو AT91C_TC_ABETRG                       ( 0x1 << 10 ) /* (TC) TIOA or TIOB External Trigger Selection */
#وصف_ڪريو AT91C_TC_ENETRG                       ( 0x1 << 12 ) /* (TC) External Event Trigger enable */
#وصف_ڪريو AT91C_TC_WAVESEL                      ( 0x3 << 13 ) /* (TC) Waveform  Selection */
#وصف_ڪريو     AT91_C_TC_WAVESEL_مٿي               ( 0x0 << 13 ) /* (TC) UP mode without atomatic trigger on RC Compare */
#وصف_ڪريو     AT91C_TC_WAVESEL_UPDOWN           ( 0x1 << 13 ) /* (TC) UPDOWN mode without automatic trigger on RC Compare */
#وصف_ڪريو     AT91_C_TC_WAVESEL_مٿي_AUTO          ( 0x2 << 13 ) /* (TC) UP mode with automatic trigger on RC Compare */
#وصف_ڪريو     AT91C_TC_WAVESEL_UPDOWN_AUTO      ( 0x3 << 13 ) /* (TC) UPDOWN mode with automatic trigger on RC Compare */
#وصف_ڪريو AT91C_TC_CPCTRG                       ( 0x1 << 14 ) /* (TC) RC Compare Trigger Enable */
#وصف_ڪريو AT91C_TC_WAVE                         ( 0x1 << 15 ) /* (TC) */
#وصف_ڪريو AT91C_TC_ACPA                         ( 0x3 << 16 ) /* (TC) RA Compare Effect on TIOA */
#وصف_ڪريو     AT91C_TC_ACPA_NONE                ( 0x0 << 16 ) /* (TC) Effect: none */
#وصف_ڪريو     AT91_C_TC_ACPA_سيٽ                 ( 0x1 << 16 ) /* (TC) Effect: set */
#وصف_ڪريو     AT91C_TC_ACPA_CLEAR               ( 0x2 << 16 ) /* (TC) Effect: clear */
#وصف_ڪريو     AT91C_TC_ACPA_TOGGLE              ( 0x3 << 16 ) /* (TC) Effect: toggle */
#وصف_ڪريو AT91C_TC_LDRA                         ( 0x3 << 16 ) /* (TC) RA Loading Selection */
#وصف_ڪريو     AT91C_TC_LDRA_NONE                ( 0x0 << 16 ) /* (TC) Edge: None */
#وصف_ڪريو     AT91C_TC_LDRA_RISING              ( 0x1 << 16 ) /* (TC) Edge: rising edge of TIOA */
#وصف_ڪريو     AT91C_TC_LDRA_FALLING             ( 0x2 << 16 ) /* (TC) Edge: falling edge of TIOA */
#وصف_ڪريو     AT91C_TC_LDRA_BOTH                ( 0x3 << 16 ) /* (TC) Edge: each edge of TIOA */
#وصف_ڪريو AT91C_TC_ACPC                         ( 0x3 << 18 ) /* (TC) RC Compare Effect on TIOA */
#وصف_ڪريو     AT91C_TC_ACPC_NONE                ( 0x0 << 18 ) /* (TC) Effect: none */
#وصف_ڪريو     AT91_C_TC_ACPC_سيٽ                 ( 0x1 << 18 ) /* (TC) Effect: set */
#وصف_ڪريو     AT91C_TC_ACPC_CLEAR               ( 0x2 << 18 ) /* (TC) Effect: clear */
#وصف_ڪريو     AT91C_TC_ACPC_TOGGLE              ( 0x3 << 18 ) /* (TC) Effect: toggle */
#وصف_ڪريو AT91C_TC_LDRB                         ( 0x3 << 18 ) /* (TC) RB Loading Selection */
#وصف_ڪريو     AT91C_TC_LDRB_NONE                ( 0x0 << 18 ) /* (TC) Edge: None */
#وصف_ڪريو     AT91C_TC_LDRB_RISING              ( 0x1 << 18 ) /* (TC) Edge: rising edge of TIOA */
#وصف_ڪريو     AT91C_TC_LDRB_FALLING             ( 0x2 << 18 ) /* (TC) Edge: falling edge of TIOA */
#وصف_ڪريو     AT91C_TC_LDRB_BOTH                ( 0x3 << 18 ) /* (TC) Edge: each edge of TIOA */
#وصف_ڪريو AT91C_TC_AEEVT                        ( 0x3 << 20 ) /* (TC) External Event Effect on TIOA */
#وصف_ڪريو     AT91C_TC_AEEVT_NONE               ( 0x0 << 20 ) /* (TC) Effect: none */
#وصف_ڪريو     AT91_C_TC_AEEVT_سيٽ                ( 0x1 << 20 ) /* (TC) Effect: set */
#وصف_ڪريو     AT91C_TC_AEEVT_CLEAR              ( 0x2 << 20 ) /* (TC) Effect: clear */
#وصف_ڪريو     AT91C_TC_AEEVT_TOGGLE             ( 0x3 << 20 ) /* (TC) Effect: toggle */
#وصف_ڪريو AT91C_TC_ASWTRG                       ( 0x3 << 22 ) /* (TC) Software Trigger Effect on TIOA */
#وصف_ڪريو     AT91C_TC_ASWTRG_NONE              ( 0x0 << 22 ) /* (TC) Effect: none */
#وصف_ڪريو     AT91_C_TC_ASWTRG_سيٽ               ( 0x1 << 22 ) /* (TC) Effect: set */
#وصف_ڪريو     AT91C_TC_ASWTRG_CLEAR             ( 0x2 << 22 ) /* (TC) Effect: clear */
#وصف_ڪريو     AT91C_TC_ASWTRG_TOGGLE            ( 0x3 << 22 ) /* (TC) Effect: toggle */
#وصف_ڪريو AT91C_TC_BCPB                         ( 0x3 << 24 ) /* (TC) RB Compare Effect on TIOB */
#وصف_ڪريو     AT91C_TC_BCPB_NONE                ( 0x0 << 24 ) /* (TC) Effect: none */
#وصف_ڪريو     AT91_C_TC_BCPB_سيٽ                 ( 0x1 << 24 ) /* (TC) Effect: set */
#وصف_ڪريو     AT91C_TC_BCPB_CLEAR               ( 0x2 << 24 ) /* (TC) Effect: clear */
#وصف_ڪريو     AT91C_TC_BCPB_TOGGLE              ( 0x3 << 24 ) /* (TC) Effect: toggle */
#وصف_ڪريو AT91C_TC_BCPC                         ( 0x3 << 26 ) /* (TC) RC Compare Effect on TIOB */
#وصف_ڪريو     AT91C_TC_BCPC_NONE                ( 0x0 << 26 ) /* (TC) Effect: none */
#وصف_ڪريو     AT91_C_TC_BCPC_سيٽ                 ( 0x1 << 26 ) /* (TC) Effect: set */
#وصف_ڪريو     AT91C_TC_BCPC_CLEAR               ( 0x2 << 26 ) /* (TC) Effect: clear */
#وصف_ڪريو     AT91C_TC_BCPC_TOGGLE              ( 0x3 << 26 ) /* (TC) Effect: toggle */
#وصف_ڪريو AT91C_TC_BEEVT                        ( 0x3 << 28 ) /* (TC) External Event Effect on TIOB */
#وصف_ڪريو     AT91C_TC_BEEVT_NONE               ( 0x0 << 28 ) /* (TC) Effect: none */
#وصف_ڪريو     AT91_C_TC_BEEVT_سيٽ                ( 0x1 << 28 ) /* (TC) Effect: set */
#وصف_ڪريو     AT91C_TC_BEEVT_CLEAR              ( 0x2 << 28 ) /* (TC) Effect: clear */
#وصف_ڪريو     AT91C_TC_BEEVT_TOGGLE             ( 0x3 << 28 ) /* (TC) Effect: toggle */
#وصف_ڪريو AT91C_TC_BSWTRG                       ( 0x3 << 30 ) /* (TC) Software Trigger Effect on TIOB */
#وصف_ڪريو     AT91C_TC_BSWTRG_NONE              ( 0x0 << 30 ) /* (TC) Effect: none */
#وصف_ڪريو     AT91_C_TC_BSWTRG_سيٽ               ( 0x1 << 30 ) /* (TC) Effect: set */
#وصف_ڪريو     AT91C_TC_BSWTRG_CLEAR             ( 0x2 << 30 ) /* (TC) Effect: clear */
#وصف_ڪريو     AT91C_TC_BSWTRG_TOGGLE            ( 0x3 << 30 ) /* (TC) Effect: toggle */
/* -------- TC_SR : (TC Offset: 0x20) TC Channel Status Register -------- */
#وصف_ڪريو AT91C_TC_COVFS                        ( 0x1 << 0 )  /* (TC) Counter Overflow */
#وصف_ڪريو AT91C_TC_LOVRS                        ( 0x1 << 1 )  /* (TC) Load Overrun */
#وصف_ڪريو AT91C_TC_CPAS                         ( 0x1 << 2 )  /* (TC) RA Compare */
#وصف_ڪريو AT91C_TC_CPBS                         ( 0x1 << 3 )  /* (TC) RB Compare */
#وصف_ڪريو AT91C_TC_CPCS                         ( 0x1 << 4 )  /* (TC) RC Compare */
#وصف_ڪريو AT91C_TC_LDRAS                        ( 0x1 << 5 )  /* (TC) RA Loading */
#وصف_ڪريو AT91C_TC_LDRBS                        ( 0x1 << 6 )  /* (TC) RB Loading */
#وصف_ڪريو AT91C_TC_ETRGS                        ( 0x1 << 7 )  /* (TC) External Trigger */
#وصف_ڪريو AT91C_TC_CLKSTA                       ( 0x1 << 16 ) /* (TC) Clock Enabling */
#وصف_ڪريو AT91C_TC_MTIOA                        ( 0x1 << 17 ) /* (TC) TIOA Mirror */
#وصف_ڪريو AT91C_TC_MTIOB                        ( 0x1 << 18 ) /* (TC) TIOA Mirror */
/* -------- TC_IER : (TC Offset: 0x24) TC Channel Interrupt Enable Register -------- */
/* -------- TC_IDR : (TC Offset: 0x28) TC Channel Interrupt Disable Register -------- */
/* -------- TC_IMR : (TC Offset: 0x2c) TC Channel Interrupt Mask Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Timer Counter Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_TCB structure *** */
#وصف_ڪريو TCB_TC0                        ( 0 )        /* TC Channel 0 */
#وصف_ڪريو TCB_TC1                        ( 64 )       /* TC Channel 1 */
#وصف_ڪريو TCB_TC2                        ( 128 )      /* TC Channel 2 */
#وصف_ڪريو TCB_BCR                        ( 192 )      /* TC Block Control Register */
#وصف_ڪريو TCB_BMR                        ( 196 )      /* TC Block Mode Register */
/* -------- TCB_BCR : (TCB Offset: 0xc0) TC Block Control Register -------- */
#وصف_ڪريو AT91C_TCB_SYNC                 ( 0x1 << 0 ) /* (TCB) Synchro Command */
/* -------- TCB_BMR : (TCB Offset: 0xc4) TC Block Mode Register -------- */
#وصف_ڪريو AT91C_TCB_TC0XC0S              ( 0x3 << 0 ) /* (TCB) External Clock Signal 0 Selection */
#وصف_ڪريو     AT91C_TCB_TC0XC0S_TCLK0    ( 0x0 )      /* (TCB) TCLK0 connected to XC0 */
#وصف_ڪريو     AT91C_TCB_TC0XC0S_NONE     ( 0x1 )      /* (TCB) None signal connected to XC0 */
#وصف_ڪريو     AT91C_TCB_TC0XC0S_TIOA1    ( 0x2 )      /* (TCB) TIOA1 connected to XC0 */
#وصف_ڪريو     AT91C_TCB_TC0XC0S_TIOA2    ( 0x3 )      /* (TCB) TIOA2 connected to XC0 */
#وصف_ڪريو AT91C_TCB_TC1XC1S              ( 0x3 << 2 ) /* (TCB) External Clock Signal 1 Selection */
#وصف_ڪريو     AT91C_TCB_TC1XC1S_TCLK1    ( 0x0 << 2 ) /* (TCB) TCLK1 connected to XC1 */
#وصف_ڪريو     AT91C_TCB_TC1XC1S_NONE     ( 0x1 << 2 ) /* (TCB) None signal connected to XC1 */
#وصف_ڪريو     AT91C_TCB_TC1XC1S_TIOA0    ( 0x2 << 2 ) /* (TCB) TIOA0 connected to XC1 */
#وصف_ڪريو     AT91C_TCB_TC1XC1S_TIOA2    ( 0x3 << 2 ) /* (TCB) TIOA2 connected to XC1 */
#وصف_ڪريو AT91C_TCB_TC2XC2S              ( 0x3 << 4 ) /* (TCB) External Clock Signal 2 Selection */
#وصف_ڪريو     AT91C_TCB_TC2XC2S_TCLK2    ( 0x0 << 4 ) /* (TCB) TCLK2 connected to XC2 */
#وصف_ڪريو     AT91C_TCB_TC2XC2S_NONE     ( 0x1 << 4 ) /* (TCB) None signal connected to XC2 */
#وصف_ڪريو     AT91C_TCB_TC2XC2S_TIOA0    ( 0x2 << 4 ) /* (TCB) TIOA0 connected to XC2 */
#وصف_ڪريو     AT91C_TCB_TC2XC2S_TIOA1    ( 0x3 << 4 ) /* (TCB) TIOA2 connected to XC2 */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Control Area Network MailBox Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_CAN_MB structure *** */
#وصف_ڪريو CAN_MB_MMR                       ( 0 )            /* MailBox Mode Register */
#وصف_ڪريو CAN_MB_MAM                       ( 4 )            /* MailBox Acceptance Mask Register */
#وصف_ڪريو CAN_MB_MID                       ( 8 )            /* MailBox ID Register */
#وصف_ڪريو CAN_MB_MFID                      ( 12 )           /* MailBox Family ID Register */
#وصف_ڪريو CAN_MB_MSR                       ( 16 )           /* MailBox Status Register */
#وصف_ڪريو CAN_MB_MDL                       ( 20 )           /* MailBox Data Low Register */
#وصف_ڪريو CAN_MB_MDH                       ( 24 )           /* MailBox Data High Register */
#وصف_ڪريو CAN_MB_MCR                       ( 28 )           /* MailBox Control Register */
/* -------- CAN_MMR : (CAN_MB Offset: 0x0) CAN Message Mode Register -------- */
#وصف_ڪريو AT91C_CAN_MTIMEMARK              ( 0xFFFF << 0 )  /* (CAN_MB) Mailbox Timemark */
#وصف_ڪريو AT91_C_CAN_اڳواٽ                  ( 0xF << 16 )    /* (CAN_MB) Mailbox Priority */
#وصف_ڪريو AT91C_CAN_MOT                    ( 0x7 << 24 )    /* (CAN_MB) Mailbox Object Type */
#وصف_ڪريو     AT91C_CAN_MOT_DIS            ( 0x0 << 24 )    /* (CAN_MB) */
#وصف_ڪريو     AT91C_CAN_MOT_RX             ( 0x1 << 24 )    /* (CAN_MB) */
#وصف_ڪريو     AT91C_CAN_MOT_RXOVERWRITE    ( 0x2 << 24 )    /* (CAN_MB) */
#وصف_ڪريو     AT91C_CAN_MOT_TX             ( 0x3 << 24 )    /* (CAN_MB) */
#وصف_ڪريو     AT91_C_CAN_MOT_استعمال_ڪندڙ       ( 0x4 << 24 )    /* (CAN_MB) */
#وصف_ڪريو     AT91_C_CAN_MOT_پيداوار_ڪندڙ       ( 0x5 << 24 )    /* (CAN_MB) */
/* -------- CAN_MAM : (CAN_MB Offset: 0x4) CAN Message Acceptance Mask Register -------- */
#وصف_ڪريو AT91C_CAN_MIDvB                  ( 0x3FFFF << 0 ) /* (CAN_MB) Complementary bits for identifier in extended mode */
#وصف_ڪريو AT91C_CAN_MIDvA                  ( 0x7FF << 18 )  /* (CAN_MB) Identifier for standard frame mode */
#وصف_ڪريو AT91C_CAN_MIDE                   ( 0x1 << 29 )    /* (CAN_MB) Identifier Version */
/* -------- CAN_MID : (CAN_MB Offset: 0x8) CAN Message ID Register -------- */
/* -------- CAN_MFID : (CAN_MB Offset: 0xc) CAN Message Family ID Register -------- */
/* -------- CAN_MSR : (CAN_MB Offset: 0x10) CAN Message Status Register -------- */
#وصف_ڪريو AT91C_CAN_MTIMESTAMP    ( 0xFFFF << 0 ) /* (CAN_MB) Timer Value */
#وصف_ڪريو AT91C_CAN_MDLC          ( 0xF << 16 )   /* (CAN_MB) Mailbox Data Length Code */
#وصف_ڪريو AT91C_CAN_MRTR          ( 0x1 << 20 )   /* (CAN_MB) Mailbox Remote Transmission Request */
#وصف_ڪريو AT91C_CAN_MABT          ( 0x1 << 22 )   /* (CAN_MB) Mailbox Message Abort */
#وصف_ڪريو AT91C_CAN_MRDY          ( 0x1 << 23 )   /* (CAN_MB) Mailbox Ready */
#وصف_ڪريو AT91C_CAN_MMI           ( 0x1 << 24 )   /* (CAN_MB) Mailbox Message Ignored */
/* -------- CAN_MDL : (CAN_MB Offset: 0x14) CAN Message Data Low Register -------- */
/* -------- CAN_MDH : (CAN_MB Offset: 0x18) CAN Message Data High Register -------- */
/* -------- CAN_MCR : (CAN_MB Offset: 0x1c) CAN Message Control Register -------- */
#وصف_ڪريو AT91C_CAN_MACR    ( 0x1 << 22 )       /* (CAN_MB) Abort Request for Mailbox */
#وصف_ڪريو AT91C_CAN_MTCR    ( 0x1 << 23 )       /* (CAN_MB) Mailbox Transfer Command */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Control Area Network Interface */
/* ***************************************************************************** */
/* *** Register offset in AT91S_CAN structure *** */
#وصف_ڪريو CAN_MR              ( 0 )         /* Mode Register */
#وصف_ڪريو CAN_IER             ( 4 )         /* Interrupt Enable Register */
#وصف_ڪريو CAN_IDR             ( 8 )         /* Interrupt Disable Register */
#وصف_ڪريو CAN_IMR             ( 12 )        /* Interrupt Mask Register */
#وصف_ڪريو CAN_SR              ( 16 )        /* Status Register */
#وصف_ڪريو CAN_BR              ( 20 )        /* Baudrate Register */
#وصف_ڪريو CAN_TIM             ( 24 )        /* Timer Register */
#وصف_ڪريو CAN_TIMESTP         ( 28 )        /* Time Stamp Register */
#وصف_ڪريو CAN_ECR             ( 32 )        /* Error Counter Register */
#وصف_ڪريو CAN_TCR             ( 36 )        /* Transfer Command Register */
#وصف_ڪريو CAN_ACR             ( 40 )        /* Abort Command Register */
#وصف_ڪريو CAN_VR              ( 252 )       /* Version Register */
#وصف_ڪريو CAN_MB0             ( 512 )       /* CAN Mailbox 0 */
#وصف_ڪريو CAN_MB1             ( 544 )       /* CAN Mailbox 1 */
#وصف_ڪريو CAN_MB2             ( 576 )       /* CAN Mailbox 2 */
#وصف_ڪريو CAN_MB3             ( 608 )       /* CAN Mailbox 3 */
#وصف_ڪريو CAN_MB4             ( 640 )       /* CAN Mailbox 4 */
#وصف_ڪريو CAN_MB5             ( 672 )       /* CAN Mailbox 5 */
#وصف_ڪريو CAN_MB6             ( 704 )       /* CAN Mailbox 6 */
#وصف_ڪريو CAN_MB7             ( 736 )       /* CAN Mailbox 7 */
#وصف_ڪريو CAN_MB8             ( 768 )       /* CAN Mailbox 8 */
#وصف_ڪريو CAN_MB9             ( 800 )       /* CAN Mailbox 9 */
#وصف_ڪريو CAN_MB10            ( 832 )       /* CAN Mailbox 10 */
#وصف_ڪريو CAN_MB11            ( 864 )       /* CAN Mailbox 11 */
#وصف_ڪريو CAN_MB12            ( 896 )       /* CAN Mailbox 12 */
#وصف_ڪريو CAN_MB13            ( 928 )       /* CAN Mailbox 13 */
#وصف_ڪريو CAN_MB14            ( 960 )       /* CAN Mailbox 14 */
#وصف_ڪريو CAN_MB15            ( 992 )       /* CAN Mailbox 15 */
/* -------- CAN_MR : (CAN Offset: 0x0) CAN Mode Register -------- */
#وصف_ڪريو AT91C_CAN_CANEN     ( 0x1 << 0 )  /* (CAN) CAN Controller Enable */
#وصف_ڪريو AT91C_CAN_LPM       ( 0x1 << 1 )  /* (CAN) Disable/Enable Low Power Mode */
#وصف_ڪريو AT91C_CAN_ABM       ( 0x1 << 2 )  /* (CAN) Disable/Enable Autobaud/Listen Mode */
#وصف_ڪريو AT91C_CAN_OVL       ( 0x1 << 3 )  /* (CAN) Disable/Enable Overload Frame */
#وصف_ڪريو AT91C_CAN_TEOF      ( 0x1 << 4 )  /* (CAN) Time Stamp messages at each end of Frame */
#وصف_ڪريو AT91C_CAN_TTM       ( 0x1 << 5 )  /* (CAN) Disable/Enable Time Trigger Mode */
#وصف_ڪريو AT91C_CAN_TIMFRZ    ( 0x1 << 6 )  /* (CAN) Enable Timer Freeze */
#وصف_ڪريو AT91C_CAN_DRPT      ( 0x1 << 7 )  /* (CAN) Disable Repeat */
/* -------- CAN_IER : (CAN Offset: 0x4) CAN Interrupt Enable Register -------- */
#وصف_ڪريو AT91C_CAN_MB0       ( 0x1 << 0 )  /* (CAN) Mailbox 0 Flag */
#وصف_ڪريو AT91C_CAN_MB1       ( 0x1 << 1 )  /* (CAN) Mailbox 1 Flag */
#وصف_ڪريو AT91C_CAN_MB2       ( 0x1 << 2 )  /* (CAN) Mailbox 2 Flag */
#وصف_ڪريو AT91C_CAN_MB3       ( 0x1 << 3 )  /* (CAN) Mailbox 3 Flag */
#وصف_ڪريو AT91C_CAN_MB4       ( 0x1 << 4 )  /* (CAN) Mailbox 4 Flag */
#وصف_ڪريو AT91C_CAN_MB5       ( 0x1 << 5 )  /* (CAN) Mailbox 5 Flag */
#وصف_ڪريو AT91C_CAN_MB6       ( 0x1 << 6 )  /* (CAN) Mailbox 6 Flag */
#وصف_ڪريو AT91C_CAN_MB7       ( 0x1 << 7 )  /* (CAN) Mailbox 7 Flag */
#وصف_ڪريو AT91C_CAN_MB8       ( 0x1 << 8 )  /* (CAN) Mailbox 8 Flag */
#وصف_ڪريو AT91C_CAN_MB9       ( 0x1 << 9 )  /* (CAN) Mailbox 9 Flag */
#وصف_ڪريو AT91C_CAN_MB10      ( 0x1 << 10 ) /* (CAN) Mailbox 10 Flag */
#وصف_ڪريو AT91C_CAN_MB11      ( 0x1 << 11 ) /* (CAN) Mailbox 11 Flag */
#وصف_ڪريو AT91C_CAN_MB12      ( 0x1 << 12 ) /* (CAN) Mailbox 12 Flag */
#وصف_ڪريو AT91C_CAN_MB13      ( 0x1 << 13 ) /* (CAN) Mailbox 13 Flag */
#وصف_ڪريو AT91C_CAN_MB14      ( 0x1 << 14 ) /* (CAN) Mailbox 14 Flag */
#وصف_ڪريو AT91C_CAN_MB15      ( 0x1 << 15 ) /* (CAN) Mailbox 15 Flag */
#وصف_ڪريو AT91C_CAN_ERRA      ( 0x1 << 16 ) /* (CAN) Error Active Mode Flag */
#وصف_ڪريو AT91C_CAN_WARN      ( 0x1 << 17 ) /* (CAN) Warning Limit Flag */
#وصف_ڪريو AT91C_CAN_ERRP      ( 0x1 << 18 ) /* (CAN) Error Passive Mode Flag */
#وصف_ڪريو AT91C_CAN_BOFF      ( 0x1 << 19 ) /* (CAN) Bus Off Mode Flag */
#وصف_ڪريو AT91C_CAN_SLEEP     ( 0x1 << 20 ) /* (CAN) Sleep Flag */
#وصف_ڪريو AT91C_CAN_WAKEUP    ( 0x1 << 21 ) /* (CAN) Wakeup Flag */
#وصف_ڪريو AT91C_CAN_TOVF      ( 0x1 << 22 ) /* (CAN) Timer Overflow Flag */
#وصف_ڪريو AT91C_CAN_TSTP      ( 0x1 << 23 ) /* (CAN) Timestamp Flag */
#وصف_ڪريو AT91C_CAN_CERR      ( 0x1 << 24 ) /* (CAN) CRC Error */
#وصف_ڪريو AT91C_CAN_SERR      ( 0x1 << 25 ) /* (CAN) Stuffing Error */
#وصف_ڪريو AT91C_CAN_AERR      ( 0x1 << 26 ) /* (CAN) Acknowledgment Error */
#وصف_ڪريو AT91C_CAN_FERR      ( 0x1 << 27 ) /* (CAN) Form Error */
#وصف_ڪريو AT91C_CAN_BERR      ( 0x1 << 28 ) /* (CAN) Bit Error */
/* -------- CAN_IDR : (CAN Offset: 0x8) CAN Interrupt Disable Register -------- */
/* -------- CAN_IMR : (CAN Offset: 0xc) CAN Interrupt Mask Register -------- */
/* -------- CAN_SR : (CAN Offset: 0x10) CAN Status Register -------- */
#وصف_ڪريو AT91C_CAN_RBSY      ( 0x1 << 29 )     /* (CAN) Receiver Busy */
#وصف_ڪريو AT91C_CAN_TBSY      ( 0x1 << 30 )     /* (CAN) Transmitter Busy */
#وصف_ڪريو AT91C_CAN_OVLY      ( 0x1 << 31 )     /* (CAN) Overload Busy */
/* -------- CAN_BR : (CAN Offset: 0x14) CAN Baudrate Register -------- */
#وصف_ڪريو AT91C_CAN_PHASE2    ( 0x7 << 0 )      /* (CAN) Phase 2 segment */
#وصف_ڪريو AT91C_CAN_PHASE1    ( 0x7 << 4 )      /* (CAN) Phase 1 segment */
#وصف_ڪريو AT91C_CAN_PROPAG    ( 0x7 << 8 )      /* (CAN) Programmation time segment */
#وصف_ڪريو AT91C_CAN_SYNC      ( 0x3 << 12 )     /* (CAN) Re-synchronization jump width segment */
#وصف_ڪريو AT91C_CAN_BRP       ( 0x7F << 16 )    /* (CAN) Baudrate Prescaler */
#وصف_ڪريو AT91C_CAN_SMP       ( 0x1 << 24 )     /* (CAN) Sampling mode */
/* -------- CAN_TIM : (CAN Offset: 0x18) CAN Timer Register -------- */
#وصف_ڪريو AT91C_CAN_TIMER     ( 0xFFFF << 0 )   /* (CAN) Timer field */
/* -------- CAN_TIMESTP : (CAN Offset: 0x1c) CAN Timestamp Register -------- */
/* -------- CAN_ECR : (CAN Offset: 0x20) CAN Error Counter Register -------- */
#وصف_ڪريو AT91C_CAN_REC       ( 0xFF << 0 )     /* (CAN) Receive Error Counter */
#وصف_ڪريو AT91C_CAN_TEC       ( 0xFF << 16 )    /* (CAN) Transmit Error Counter */
/* -------- CAN_TCR : (CAN Offset: 0x24) CAN Transfer Command Register -------- */
#وصف_ڪريو AT91C_CAN_TIMRST    ( 0x1 << 31 )     /* (CAN) Timer Reset Field */
/* -------- CAN_ACR : (CAN Offset: 0x28) CAN Abort Command Register -------- */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Ethernet MAC 10/100 */
/* ***************************************************************************** */
/* *** Register offset in AT91S_EMAC structure *** */
#وصف_ڪريو EMAC_NCR                        ( 0 )         /* Network Control Register */
#وصف_ڪريو EMAC_NCFGR                      ( 4 )         /* Network Configuration Register */
#وصف_ڪريو EMAC_NSR                        ( 8 )         /* Network Status Register */
#وصف_ڪريو EMAC_TSR                        ( 20 )        /* Transmit Status Register */
#وصف_ڪريو EMAC_RBQP                       ( 24 )        /* Receive Buffer Queue Pointer */
#وصف_ڪريو EMAC_TBQP                       ( 28 )        /* Transmit Buffer Queue Pointer */
#وصف_ڪريو EMAC_RSR                        ( 32 )        /* Receive Status Register */
#وصف_ڪريو EMAC_ISR                        ( 36 )        /* Interrupt Status Register */
#وصف_ڪريو EMAC_IER                        ( 40 )        /* Interrupt Enable Register */
#وصف_ڪريو EMAC_IDR                        ( 44 )        /* Interrupt Disable Register */
#وصف_ڪريو EMAC_IMR                        ( 48 )        /* Interrupt Mask Register */
#وصف_ڪريو EMAC_MAN                        ( 52 )        /* PHY Maintenance Register */
#وصف_ڪريو EMAC_PTR                        ( 56 )        /* Pause Time Register */
#وصف_ڪريو EMAC_PFR                        ( 60 )        /* Pause Frames received Register */
#وصف_ڪريو EMAC_FTO                        ( 64 )        /* Frames Transmitted OK Register */
#وصف_ڪريو EMAC_SCF                        ( 68 )        /* Single Collision Frame Register */
#وصف_ڪريو EMAC_MCF                        ( 72 )        /* Multiple Collision Frame Register */
#وصف_ڪريو EMAC_FRO                        ( 76 )        /* Frames Received OK Register */
#وصف_ڪريو EMAC_FCSE                       ( 80 )        /* Frame Check Sequence Error Register */
#وصف_ڪريو EMAC_ALE                        ( 84 )        /* Alignment Error Register */
#وصف_ڪريو EMAC_DTF                        ( 88 )        /* Deferred Transmission Frame Register */
#وصف_ڪريو EMAC_LCOL                       ( 92 )        /* Late Collision Register */
#وصف_ڪريو EMAC_ECOL                       ( 96 )        /* Excessive Collision Register */
#وصف_ڪريو EMAC_TUND                       ( 100 )       /* Transmit Underrun Error Register */
#وصف_ڪريو EMAC_CSE                        ( 104 )       /* Carrier Sense Error Register */
#وصف_ڪريو EMAC_RRE                        ( 108 )       /* Receive Resource Error Register */
#وصف_ڪريو EMAC_ROV                        ( 112 )       /* Receive Overrun Errors Register */
#وصف_ڪريو EMAC_RSE                        ( 116 )       /* Receive Symbol Errors Register */
#وصف_ڪريو EMAC_ELE                        ( 120 )       /* Excessive Length Errors Register */
#وصف_ڪريو EMAC_RJA                        ( 124 )       /* Receive Jabbers Register */
#وصف_ڪريو EMAC_USF                        ( 128 )       /* Undersize Frames Register */
#وصف_ڪريو EMAC_STE                        ( 132 )       /* SQE Test Error Register */
#وصف_ڪريو EMAC_RLE                        ( 136 )       /* Receive Length Field Mismatch Register */
#وصف_ڪريو EMAC_TPF                        ( 140 )       /* Transmitted Pause Frames Register */
#وصف_ڪريو EMAC_HRB                        ( 144 )       /* Hash Address Bottom[31:0] */
#وصف_ڪريو EMAC_HRT                        ( 148 )       /* Hash Address Top[63:32] */
#وصف_ڪريو EMAC_SA1L                       ( 152 )       /* Specific Address 1 Bottom, First 4 bytes */
#وصف_ڪريو EMAC_SA1H                       ( 156 )       /* Specific Address 1 Top, Last 2 bytes */
#وصف_ڪريو EMAC_SA2L                       ( 160 )       /* Specific Address 2 Bottom, First 4 bytes */
#وصف_ڪريو EMAC_SA2H                       ( 164 )       /* Specific Address 2 Top, Last 2 bytes */
#وصف_ڪريو EMAC_SA3L                       ( 168 )       /* Specific Address 3 Bottom, First 4 bytes */
#وصف_ڪريو EMAC_SA3H                       ( 172 )       /* Specific Address 3 Top, Last 2 bytes */
#وصف_ڪريو EMAC_SA4L                       ( 176 )       /* Specific Address 4 Bottom, First 4 bytes */
#وصف_ڪريو EMAC_SA4H                       ( 180 )       /* Specific Address 4 Top, Last 2 bytes */
#وصف_ڪريو EMAC_TID                        ( 184 )       /* Type ID Checking Register */
#وصف_ڪريو EMAC_TPQ                        ( 188 )       /* Transmit Pause Quantum Register */
#وصف_ڪريو EMAC_USRIO                      ( 192 )       /* USER Input/Output Register */
#وصف_ڪريو EMAC_WOL                        ( 196 )       /* Wake On LAN Register */
#وصف_ڪريو EMAC_REV                        ( 252 )       /* Revision Register */
/* -------- EMAC_NCR : (EMAC Offset: 0x0)  -------- */
#وصف_ڪريو AT91C_EMAC_LB                   ( 0x1 << 0 )  /* (EMAC) Loopback. Optional. When set, loopback signal is at high level. */
#وصف_ڪريو AT91C_EMAC_LLB                  ( 0x1 << 1 )  /* (EMAC) Loopback local. */
#وصف_ڪريو AT91C_EMAC_RE                   ( 0x1 << 2 )  /* (EMAC) Receive enable. */
#وصف_ڪريو AT91C_EMAC_TE                   ( 0x1 << 3 )  /* (EMAC) Transmit enable. */
#وصف_ڪريو AT91C_EMAC_MPE                  ( 0x1 << 4 )  /* (EMAC) Management port enable. */
#وصف_ڪريو AT91C_EMAC_CLRSTAT              ( 0x1 << 5 )  /* (EMAC) Clear statistics registers. */
#وصف_ڪريو AT91C_EMAC_INCSTAT              ( 0x1 << 6 )  /* (EMAC) Increment statistics registers. */
#وصف_ڪريو AT91C_EMAC_WESTAT               ( 0x1 << 7 )  /* (EMAC) Write enable for statistics registers. */
#وصف_ڪريو AT91C_EMAC_BP                   ( 0x1 << 8 )  /* (EMAC) Back pressure. */
#وصف_ڪريو AT91C_EMAC_TSTART               ( 0x1 << 9 )  /* (EMAC) Start Transmission. */
#وصف_ڪريو AT91C_EMAC_THALT                ( 0x1 << 10 ) /* (EMAC) Transmission Halt. */
#وصف_ڪريو AT91C_EMAC_TPFR                 ( 0x1 << 11 ) /* (EMAC) Transmit pause frame */
#وصف_ڪريو AT91C_EMAC_TZQ                  ( 0x1 << 12 ) /* (EMAC) Transmit zero quantum pause frame */
/* -------- EMAC_NCFGR : (EMAC Offset: 0x4) Network Configuration Register -------- */
#وصف_ڪريو AT91C_EMAC_SPD                  ( 0x1 << 0 )  /* (EMAC) Speed. */
#وصف_ڪريو AT91C_EMAC_FD                   ( 0x1 << 1 )  /* (EMAC) Full duplex. */
#وصف_ڪريو AT91C_EMAC_JFRAME               ( 0x1 << 3 )  /* (EMAC) Jumbo Frames. */
#وصف_ڪريو AT91C_EMAC_CAF                  ( 0x1 << 4 )  /* (EMAC) Copy all frames. */
#وصف_ڪريو AT91C_EMAC_NBC                  ( 0x1 << 5 )  /* (EMAC) No broadcast. */
#وصف_ڪريو AT91C_EMAC_MTI                  ( 0x1 << 6 )  /* (EMAC) Multicast hash event enable */
#وصف_ڪريو AT91C_EMAC_UNI                  ( 0x1 << 7 )  /* (EMAC) Unicast hash enable. */
#وصف_ڪريو AT91C_EMAC_BIG                  ( 0x1 << 8 )  /* (EMAC) Receive 1522 bytes. */
#وصف_ڪريو AT91C_EMAC_EAE                  ( 0x1 << 9 )  /* (EMAC) External address match enable. */
#وصف_ڪريو AT91C_EMAC_CLK                  ( 0x3 << 10 ) /* (EMAC) */
#وصف_ڪريو     AT91C_EMAC_CLK_HCLK_8       ( 0x0 << 10 ) /* (EMAC) HCLK divided by 8 */
#وصف_ڪريو     AT91C_EMAC_CLK_HCLK_16      ( 0x1 << 10 ) /* (EMAC) HCLK divided by 16 */
#وصف_ڪريو     AT91C_EMAC_CLK_HCLK_32      ( 0x2 << 10 ) /* (EMAC) HCLK divided by 32 */
#وصف_ڪريو     AT91C_EMAC_CLK_HCLK_64      ( 0x3 << 10 ) /* (EMAC) HCLK divided by 64 */
#وصف_ڪريو AT91C_EMAC_RTY                  ( 0x1 << 12 ) /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_PAE                  ( 0x1 << 13 ) /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_RBOF                 ( 0x3 << 14 ) /* (EMAC) */
#وصف_ڪريو     AT91_C_EMAC_RBOF_وٿي_0    ( 0x0 << 14 ) /* (EMAC) no offset from start of receive buffer */
#وصف_ڪريو     AT91_C_EMAC_RBOF_وٿي_1    ( 0x1 << 14 ) /* (EMAC) one byte offset from start of receive buffer */
#وصف_ڪريو     AT91_C_EMAC_RBOF_وٿي_2    ( 0x2 << 14 ) /* (EMAC) two bytes offset from start of receive buffer */
#وصف_ڪريو     AT91_C_EMAC_RBOF_وٿي_3    ( 0x3 << 14 ) /* (EMAC) three bytes offset from start of receive buffer */
#وصف_ڪريو AT91C_EMAC_RLCE                 ( 0x1 << 16 ) /* (EMAC) Receive Length field Checking Enable */
#وصف_ڪريو AT91C_EMAC_DRFCS                ( 0x1 << 17 ) /* (EMAC) Discard Receive FCS */
#وصف_ڪريو AT91C_EMAC_EFRHD                ( 0x1 << 18 ) /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_IRXFCS               ( 0x1 << 19 ) /* (EMAC) Ignore RX FCS */
/* -------- EMAC_NSR : (EMAC Offset: 0x8) Network Status Register -------- */
#وصف_ڪريو AT91C_EMAC_LINKR                ( 0x1 << 0 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_MDIO                 ( 0x1 << 1 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_IDLE                 ( 0x1 << 2 )  /* (EMAC) */
/* -------- EMAC_TSR : (EMAC Offset: 0x14) Transmit Status Register -------- */
#وصف_ڪريو AT91C_EMAC_UBR                  ( 0x1 << 0 )  /* (EMAC) */
#وصف_ڪريو AT91_C_EMAC_کانو                  ( 0x1 << 1 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_RLES                 ( 0x1 << 2 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_TGO                  ( 0x1 << 3 )  /* (EMAC) Transmit Go */
#وصف_ڪريو AT91C_EMAC_BEX                  ( 0x1 << 4 )  /* (EMAC) Buffers exhausted mid frame */
#وصف_ڪريو AT91C_EMAC_COMP                 ( 0x1 << 5 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_UND                  ( 0x1 << 6 )  /* (EMAC) */
/* -------- EMAC_RSR : (EMAC Offset: 0x20) Receive Status Register -------- */
#وصف_ڪريو AT91C_EMAC_BNA                  ( 0x1 << 0 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_REC                  ( 0x1 << 1 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_OVR                  ( 0x1 << 2 )  /* (EMAC) */
/* -------- EMAC_ISR : (EMAC Offset: 0x24) Interrupt Status Register -------- */
#وصف_ڪريو AT91C_EMAC_MFD                  ( 0x1 << 0 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_RCOMP                ( 0x1 << 1 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_RXUBR                ( 0x1 << 2 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_TXUBR                ( 0x1 << 3 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_TUNDR                ( 0x1 << 4 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_RLEX                 ( 0x1 << 5 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_TXERR                ( 0x1 << 6 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_TCOMP                ( 0x1 << 7 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_LINK                 ( 0x1 << 9 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_ROVR                 ( 0x1 << 10 ) /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_HRESP                ( 0x1 << 11 ) /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_PFRE                 ( 0x1 << 12 ) /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_PTZ                  ( 0x1 << 13 ) /* (EMAC) */
/* -------- EMAC_IER : (EMAC Offset: 0x28) Interrupt Enable Register -------- */
/* -------- EMAC_IDR : (EMAC Offset: 0x2c) Interrupt Disable Register -------- */
/* -------- EMAC_IMR : (EMAC Offset: 0x30) Interrupt Mask Register -------- */
/* -------- EMAC_MAN : (EMAC Offset: 0x34) PHY Maintenance Register -------- */
#وصف_ڪريو AT91_C_EMAC_معلومات       ( 0xFFFF << 0 )  /* (EMAC) */
#وصف_ڪريو AT91_C_EMAC_ڪوڊ       ( 0x3 << 16 )    /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_REGA       ( 0x1F << 18 )   /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_PHYA       ( 0x1F << 23 )   /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_RW         ( 0x3 << 28 )    /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_SOF        ( 0x3 << 30 )    /* (EMAC) */
/* -------- EMAC_USRIO : (EMAC Offset: 0xc0) USER Input Output Register -------- */
#وصف_ڪريو AT91C_EMAC_RMII       ( 0x1 << 0 )     /* (EMAC) Reduce MII */
/* -------- EMAC_WOL : (EMAC Offset: 0xc4) Wake On LAN Register -------- */
#وصف_ڪريو AT91C_EMAC_IP         ( 0xFFFF << 0 )  /* (EMAC) ARP request IP address */
#وصف_ڪريو AT91C_EMAC_MAG        ( 0x1 << 16 )    /* (EMAC) Magic packet event enable */
#وصف_ڪريو AT91C_EMAC_ARP        ( 0x1 << 17 )    /* (EMAC) ARP request event enable */
#وصف_ڪريو AT91C_EMAC_SA1        ( 0x1 << 18 )    /* (EMAC) Specific address register 1 event enable */
/* -------- EMAC_REV : (EMAC Offset: 0xfc) Revision Register -------- */
#وصف_ڪريو AT91C_EMAC_REVREF     ( 0xFFFF << 0 )  /* (EMAC) */
#وصف_ڪريو AT91C_EMAC_PARTREF    ( 0xFFFF << 16 ) /* (EMAC) */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Analog to Digital Convertor */
/* ***************************************************************************** */
/* *** Register offset in AT91S_ADC structure *** */
#وصف_ڪريو ADC_CR                             ( 0 )          /* ADC Control Register */
#وصف_ڪريو ADC_MR                             ( 4 )          /* ADC Mode Register */
#وصف_ڪريو ADC_CHER                           ( 16 )         /* ADC Channel Enable Register */
#وصف_ڪريو ADC_CHDR                           ( 20 )         /* ADC Channel Disable Register */
#وصف_ڪريو ADC_CHSR                           ( 24 )         /* ADC Channel Status Register */
#وصف_ڪريو ADC_SR                             ( 28 )         /* ADC Status Register */
#وصف_ڪريو ADC_LCDR                           ( 32 )         /* ADC Last Converted Data Register */
#وصف_ڪريو ADC_IER                            ( 36 )         /* ADC Interrupt Enable Register */
#وصف_ڪريو ADC_IDR                            ( 40 )         /* ADC Interrupt Disable Register */
#وصف_ڪريو ADC_IMR                            ( 44 )         /* ADC Interrupt Mask Register */
#وصف_ڪريو ADC_CDR0                           ( 48 )         /* ADC Channel Data Register 0 */
#وصف_ڪريو ADC_CDR1                           ( 52 )         /* ADC Channel Data Register 1 */
#وصف_ڪريو ADC_CDR2                           ( 56 )         /* ADC Channel Data Register 2 */
#وصف_ڪريو ADC_CDR3                           ( 60 )         /* ADC Channel Data Register 3 */
#وصف_ڪريو ADC_CDR4                           ( 64 )         /* ADC Channel Data Register 4 */
#وصف_ڪريو ADC_CDR5                           ( 68 )         /* ADC Channel Data Register 5 */
#وصف_ڪريو ADC_CDR6                           ( 72 )         /* ADC Channel Data Register 6 */
#وصف_ڪريو ADC_CDR7                           ( 76 )         /* ADC Channel Data Register 7 */
#وصف_ڪريو ADC_RPR                            ( 256 )        /* Receive Pointer Register */
#وصف_ڪريو ADC_RCR                            ( 260 )        /* Receive Counter Register */
#وصف_ڪريو ADC_TPR                            ( 264 )        /* Transmit Pointer Register */
#وصف_ڪريو ADC_TCR                            ( 268 )        /* Transmit Counter Register */
#وصف_ڪريو ADC_RNPR                           ( 272 )        /* Receive Next Pointer Register */
#وصف_ڪريو ADC_RNCR                           ( 276 )        /* Receive Next Counter Register */
#وصف_ڪريو ADC_TNPR                           ( 280 )        /* Transmit Next Pointer Register */
#وصف_ڪريو ADC_TNCR                           ( 284 )        /* Transmit Next Counter Register */
#وصف_ڪريو ADC_PTCR                           ( 288 )        /* PDC Transfer Control Register */
#وصف_ڪريو ADC_PTSR                           ( 292 )        /* PDC Transfer Status Register */
/* -------- ADC_CR : (ADC Offset: 0x0) ADC Control Register -------- */
#وصف_ڪريو AT91C_ADC_SWRST                    ( 0x1 << 0 )   /* (ADC) Software Reset */
#وصف_ڪريو AT91_C_ADC_شروعات                    ( 0x1 << 1 )   /* (ADC) Start Conversion */
/* -------- ADC_MR : (ADC Offset: 0x4) ADC Mode Register -------- */
#وصف_ڪريو AT91C_ADC_TRGEN                    ( 0x1 << 0 )   /* (ADC) Trigger Enable */
#وصف_ڪريو     AT91C_ADC_TRGEN_DIS            ( 0x0 )        /* (ADC) Hardware triggers are disabled. Starting a conversion is only possible by software */
#وصف_ڪريو     AT91C_ADC_TRGEN_EN             ( 0x1 )        /* (ADC) Hardware trigger selected by TRGSEL field is enabled. */
#وصف_ڪريو AT91C_ADC_TRGSEL                   ( 0x7 << 1 )   /* (ADC) Trigger Selection */
#وصف_ڪريو     AT91C_ADC_TRGSEL_TIOA0         ( 0x0 << 1 )   /* (ADC) Selected TRGSEL = TIAO0 */
#وصف_ڪريو     AT91C_ADC_TRGSEL_TIOA1         ( 0x1 << 1 )   /* (ADC) Selected TRGSEL = TIAO1 */
#وصف_ڪريو     AT91C_ADC_TRGSEL_TIOA2         ( 0x2 << 1 )   /* (ADC) Selected TRGSEL = TIAO2 */
#وصف_ڪريو     AT91C_ADC_TRGSEL_TIOA3         ( 0x3 << 1 )   /* (ADC) Selected TRGSEL = TIAO3 */
#وصف_ڪريو     AT91C_ADC_TRGSEL_TIOA4         ( 0x4 << 1 )   /* (ADC) Selected TRGSEL = TIAO4 */
#وصف_ڪريو     AT91C_ADC_TRGSEL_TIOA5         ( 0x5 << 1 )   /* (ADC) Selected TRGSEL = TIAO5 */
#وصف_ڪريو     AT91C_ADC_TRGSEL_EXT           ( 0x6 << 1 )   /* (ADC) Selected TRGSEL = External Trigger */
#وصف_ڪريو AT91C_ADC_LOWRES                   ( 0x1 << 4 )   /* (ADC) Resolution. */
#وصف_ڪريو     AT91_C_ADC_LOWRES_10_ٻٽو_انگ        ( 0x0 << 4 )   /* (ADC) 10-bit resolution */
#وصف_ڪريو     AT91_C_ADC_LOWRES_8_ٻٽو_انگ         ( 0x1 << 4 )   /* (ADC) 8-bit resolution */
#وصف_ڪريو AT91C_ADC_SLEEP                    ( 0x1 << 5 )   /* (ADC) Sleep Mode */
#وصف_ڪريو     AT91_C_ADC_SLEEP_عام_گهڻائي    ( 0x0 << 5 )   /* (ADC) Normal Mode */
#وصف_ڪريو     AT91_C_ADC_SLEEP_گهڻائي           ( 0x1 << 5 )   /* (ADC) Sleep Mode */
#وصف_ڪريو AT91C_ADC_PRESCAL                  ( 0x3F << 8 )  /* (ADC) Prescaler rate selection */
#وصف_ڪريو AT91C_ADC_STARTUP                  ( 0x1F << 16 ) /* (ADC) Startup Time */
#وصف_ڪريو AT91C_ADC_SHTIM                    ( 0xF << 24 )  /* (ADC) Sample & Hold Time */
/* --------     ADC_CHER : (ADC Offset: 0x10) ADC Channel Enable Register -------- */
#وصف_ڪريو AT91C_ADC_CH0                      ( 0x1 << 0 )   /* (ADC) Channel 0 */
#وصف_ڪريو AT91C_ADC_CH1                      ( 0x1 << 1 )   /* (ADC) Channel 1 */
#وصف_ڪريو AT91C_ADC_CH2                      ( 0x1 << 2 )   /* (ADC) Channel 2 */
#وصف_ڪريو AT91C_ADC_CH3                      ( 0x1 << 3 )   /* (ADC) Channel 3 */
#وصف_ڪريو AT91C_ADC_CH4                      ( 0x1 << 4 )   /* (ADC) Channel 4 */
#وصف_ڪريو AT91C_ADC_CH5                      ( 0x1 << 5 )   /* (ADC) Channel 5 */
#وصف_ڪريو AT91C_ADC_CH6                      ( 0x1 << 6 )   /* (ADC) Channel 6 */
#وصف_ڪريو AT91C_ADC_CH7                      ( 0x1 << 7 )   /* (ADC) Channel 7 */
/* --------     ADC_CHDR : (ADC Offset: 0x14) ADC Channel Disable Register -------- */
/* --------     ADC_CHSR : (ADC Offset: 0x18) ADC Channel Status Register -------- */
/* -------- ADC_SR : (ADC Offset: 0x1c) ADC Status Register -------- */
#وصف_ڪريو AT91C_ADC_EOC0      ( 0x1 << 0 )      /* (ADC) End of Conversion */
#وصف_ڪريو AT91C_ADC_EOC1      ( 0x1 << 1 )      /* (ADC) End of Conversion */
#وصف_ڪريو AT91C_ADC_EOC2      ( 0x1 << 2 )      /* (ADC) End of Conversion */
#وصف_ڪريو AT91C_ADC_EOC3      ( 0x1 << 3 )      /* (ADC) End of Conversion */
#وصف_ڪريو AT91C_ADC_EOC4      ( 0x1 << 4 )      /* (ADC) End of Conversion */
#وصف_ڪريو AT91C_ADC_EOC5      ( 0x1 << 5 )      /* (ADC) End of Conversion */
#وصف_ڪريو AT91C_ADC_EOC6      ( 0x1 << 6 )      /* (ADC) End of Conversion */
#وصف_ڪريو AT91C_ADC_EOC7      ( 0x1 << 7 )      /* (ADC) End of Conversion */
#وصف_ڪريو AT91C_ADC_OVRE0     ( 0x1 << 8 )      /* (ADC) Overrun Error */
#وصف_ڪريو AT91C_ADC_OVRE1     ( 0x1 << 9 )      /* (ADC) Overrun Error */
#وصف_ڪريو AT91C_ADC_OVRE2     ( 0x1 << 10 )     /* (ADC) Overrun Error */
#وصف_ڪريو AT91C_ADC_OVRE3     ( 0x1 << 11 )     /* (ADC) Overrun Error */
#وصف_ڪريو AT91C_ADC_OVRE4     ( 0x1 << 12 )     /* (ADC) Overrun Error */
#وصف_ڪريو AT91C_ADC_OVRE5     ( 0x1 << 13 )     /* (ADC) Overrun Error */
#وصف_ڪريو AT91C_ADC_OVRE6     ( 0x1 << 14 )     /* (ADC) Overrun Error */
#وصف_ڪريو AT91C_ADC_OVRE7     ( 0x1 << 15 )     /* (ADC) Overrun Error */
#وصف_ڪريو AT91C_ADC_DRDY      ( 0x1 << 16 )     /* (ADC) Data Ready */
#وصف_ڪريو AT91C_ADC_GOVRE     ( 0x1 << 17 )     /* (ADC) General Overrun */
#وصف_ڪريو AT91C_ADC_ENDRX     ( 0x1 << 18 )     /* (ADC) End of Receiver Transfer */
#وصف_ڪريو AT91C_ADC_RXBUFF    ( 0x1 << 19 )     /* (ADC) RXBUFF Interrupt */
/* -------- ADC_LCDR : (ADC Offset: 0x20) ADC Last Converted Data Register -------- */
#وصف_ڪريو AT91C_ADC_LDATA     ( 0x3FF << 0 )    /* (ADC) Last Data Converted */
/* -------- ADC_IER : (ADC Offset: 0x24) ADC Interrupt Enable Register -------- */
/* -------- ADC_IDR : (ADC Offset: 0x28) ADC Interrupt Disable Register -------- */
/* -------- ADC_IMR : (ADC Offset: 0x2c) ADC Interrupt Mask Register -------- */
/* -------- ADC_CDR0 : (ADC Offset: 0x30) ADC Channel Data Register 0 -------- */
#وصف_ڪريو AT91_C_ADC_معلومات    ( 0x3FF << 0 )        /* (ADC) Converted Data */
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
/* *** Register offset in AT91S_AES structure *** */
#وصف_ڪريو AES_CR                          ( 0 )          /* Control Register */
#وصف_ڪريو AES_MR                          ( 4 )          /* Mode Register */
#وصف_ڪريو AES_IER                         ( 16 )         /* Interrupt Enable Register */
#وصف_ڪريو AES_IDR                         ( 20 )         /* Interrupt Disable Register */
#وصف_ڪريو AES_IMR                         ( 24 )         /* Interrupt Mask Register */
#وصف_ڪريو AES_ISR                         ( 28 )         /* Interrupt Status Register */
#وصف_ڪريو AES_KEYWxR                      ( 32 )         /* Key Word x Register */
#وصف_ڪريو AES_IDATAxR                     ( 64 )         /* Input Data x Register */
#وصف_ڪريو AES_ODATAxR                     ( 80 )         /* Output Data x Register */
#وصف_ڪريو AES_IVxR                        ( 96 )         /* Initialization Vector x Register */
#وصف_ڪريو AES_VR                          ( 252 )        /* AES Version Register */
#وصف_ڪريو AES_RPR                         ( 256 )        /* Receive Pointer Register */
#وصف_ڪريو AES_RCR                         ( 260 )        /* Receive Counter Register */
#وصف_ڪريو AES_TPR                         ( 264 )        /* Transmit Pointer Register */
#وصف_ڪريو AES_TCR                         ( 268 )        /* Transmit Counter Register */
#وصف_ڪريو AES_RNPR                        ( 272 )        /* Receive Next Pointer Register */
#وصف_ڪريو AES_RNCR                        ( 276 )        /* Receive Next Counter Register */
#وصف_ڪريو AES_TNPR                        ( 280 )        /* Transmit Next Pointer Register */
#وصف_ڪريو AES_TNCR                        ( 284 )        /* Transmit Next Counter Register */
#وصف_ڪريو AES_PTCR                        ( 288 )        /* PDC Transfer Control Register */
#وصف_ڪريو AES_PTSR                        ( 292 )        /* PDC Transfer Status Register */
/* -------- AES_CR : (AES Offset: 0x0) Control Register -------- */
#وصف_ڪريو AT91_C_AES_شروعات                 ( 0x1 << 0 )   /* (AES) Starts Processing */
#وصف_ڪريو AT91C_AES_SWRST                 ( 0x1 << 8 )   /* (AES) Software Reset */
#وصف_ڪريو AT91C_AES_LOADSEED              ( 0x1 << 16 )  /* (AES) Random Number Generator Seed Loading */
/* -------- AES_MR : (AES Offset: 0x4) Mode Register -------- */
#وصف_ڪريو AT91C_AES_CIPHER                ( 0x1 << 0 )   /* (AES) Processing Mode */
#وصف_ڪريو AT91C_AES_PROCDLY               ( 0xF << 4 )   /* (AES) Processing Delay */
#وصف_ڪريو AT91C_AES_SMOD                  ( 0x3 << 8 )   /* (AES) Start Mode */
#وصف_ڪريو     AT91C_AES_SMOD_MANUAL       ( 0x0 << 8 )   /* (AES) Manual Mode: The START bit in register AES_CR must be set to begin encryption or decryption. */
#وصف_ڪريو     AT91C_AES_SMOD_AUTO         ( 0x1 << 8 )   /* (AES) Auto Mode: no action in AES_CR is necessary (cf datasheet). */
#وصف_ڪريو     AT91C_AES_SMOD_PDC          ( 0x2 << 8 )   /* (AES) PDC Mode (cf datasheet). */
#وصف_ڪريو AT91C_AES_OPMOD                 ( 0x7 << 12 )  /* (AES) Operation Mode */
#وصف_ڪريو     AT91C_AES_OPMOD_ECB         ( 0x0 << 12 )  /* (AES) ECB Electronic CodeBook mode. */
#وصف_ڪريو     AT91C_AES_OPMOD_CBC         ( 0x1 << 12 )  /* (AES) CBC Cipher Block Chaining mode. */
#وصف_ڪريو     AT91C_AES_OPMOD_OFB         ( 0x2 << 12 )  /* (AES) OFB Output Feedback mode. */
#وصف_ڪريو     AT91C_AES_OPMOD_CFB         ( 0x3 << 12 )  /* (AES) CFB Cipher Feedback mode. */
#وصف_ڪريو     AT91C_AES_OPMOD_CTR         ( 0x4 << 12 )  /* (AES) CTR Counter mode. */
#وصف_ڪريو AT91C_AES_LOD                   ( 0x1 << 15 )  /* (AES) Last Output Data Mode */
#وصف_ڪريو AT91C_AES_CFBS                  ( 0x7 << 16 )  /* (AES) Cipher Feedback Data Size */
#وصف_ڪريو     AT91_C_AES_CFBS_128_ٻٽو_انگ      ( 0x0 << 16 )  /* (AES) 128-bit. */
#وصف_ڪريو     AT91_C_AES_CFBS_64_ٻٽو_انگ       ( 0x1 << 16 )  /* (AES) 64-bit. */
#وصف_ڪريو     AT91_C_AES_CFBS_32_ٻٽو_انگ       ( 0x2 << 16 )  /* (AES) 32-bit. */
#وصف_ڪريو     AT91_C_AES_CFBS_16_ٻٽو_انگ       ( 0x3 << 16 )  /* (AES) 16-bit. */
#وصف_ڪريو     AT91_C_AES_CFBS_8_ٻٽو_انگ        ( 0x4 << 16 )  /* (AES) 8-bit. */
#وصف_ڪريو AT91C_AES_CKEY                  ( 0xF << 20 )  /* (AES) Countermeasure Key */
#وصف_ڪريو AT91C_AES_CTYPE                 ( 0x1F << 24 ) /* (AES) Countermeasure Type */
#وصف_ڪريو     AT91C_AES_CTYPE_TYPE1_EN    ( 0x1 << 24 )  /* (AES) Countermeasure type 1 is enabled. */
#وصف_ڪريو     AT91C_AES_CTYPE_TYPE2_EN    ( 0x2 << 24 )  /* (AES) Countermeasure type 2 is enabled. */
#وصف_ڪريو     AT91C_AES_CTYPE_TYPE3_EN    ( 0x4 << 24 )  /* (AES) Countermeasure type 3 is enabled. */
#وصف_ڪريو     AT91C_AES_CTYPE_TYPE4_EN    ( 0x8 << 24 )  /* (AES) Countermeasure type 4 is enabled. */
#وصف_ڪريو     AT91C_AES_CTYPE_TYPE5_EN    ( 0x10 << 24 ) /* (AES) Countermeasure type 5 is enabled. */
/* -------- AES_IER : (AES Offset: 0x10) Interrupt Enable Register -------- */
#وصف_ڪريو AT91C_AES_DATRDY                ( 0x1 << 0 )   /* (AES) DATRDY */
#وصف_ڪريو AT91C_AES_ENDRX                 ( 0x1 << 1 )   /* (AES) PDC Read Buffer End */
#وصف_ڪريو AT91C_AES_ENDTX                 ( 0x1 << 2 )   /* (AES) PDC Write Buffer End */
#وصف_ڪريو AT91C_AES_RXBUFF                ( 0x1 << 3 )   /* (AES) PDC Read Buffer Full */
#وصف_ڪريو AT91C_AES_TXBUFE                ( 0x1 << 4 )   /* (AES) PDC Write Buffer Empty */
#وصف_ڪريو AT91C_AES_URAD                  ( 0x1 << 8 )   /* (AES) Unspecified Register Access Detection */
/* -------- AES_IDR : (AES Offset: 0x14) Interrupt Disable Register -------- */
/* -------- AES_IMR : (AES Offset: 0x18) Interrupt Mask Register -------- */
/* -------- AES_ISR : (AES Offset: 0x1c) Interrupt Status Register -------- */
#وصف_ڪريو AT91C_AES_URAT                              ( 0x7 << 12 ) /* (AES) Unspecified Register Access Type Status */
#وصف_ڪريو     AT91_C_AES_URAT_اندريون_DAT_WRITE_DATPROC     ( 0x0 << 12 ) /* (AES) Input data register written during the data processing in PDC mode. */
#وصف_ڪريو     AT91_C_AES_URAT_ٻاهريون_DAT_READ_DATPROC     ( 0x1 << 12 ) /* (AES) Output data register read during the data processing. */
#وصف_ڪريو     AT91C_AES_URAT_MODEREG_WRITE_DATPROC    ( 0x2 << 12 ) /* (AES) Mode register written during the data processing. */
#وصف_ڪريو     AT91_C_AES_URAT_ٻاهريون_DAT_READ_SUBKEY      ( 0x3 << 12 ) /* (AES) Output data register read during the sub-keys generation. */
#وصف_ڪريو     AT91C_AES_URAT_MODEREG_WRITE_SUBKEY     ( 0x4 << 12 ) /* (AES) Mode register written during the sub-keys generation. */
#وصف_ڪريو     AT91C_AES_URAT_WO_REG_READ              ( 0x5 << 12 ) /* (AES) Write-only register read access. */

/* ***************************************************************************** */
/*              SOFTWARE API DEFINITION  FOR Triple Data Encryption Standard */
/* ***************************************************************************** */
/* *** Register offset in AT91S_TDES structure *** */
#وصف_ڪريو TDES_CR                       ( 0 )         /* Control Register */
#وصف_ڪريو TDES_MR                       ( 4 )         /* Mode Register */
#وصف_ڪريو TDES_IER                      ( 16 )        /* Interrupt Enable Register */
#وصف_ڪريو TDES_IDR                      ( 20 )        /* Interrupt Disable Register */
#وصف_ڪريو TDES_IMR                      ( 24 )        /* Interrupt Mask Register */
#وصف_ڪريو TDES_ISR                      ( 28 )        /* Interrupt Status Register */
#وصف_ڪريو TDES_KEY1WxR                  ( 32 )        /* Key 1 Word x Register */
#وصف_ڪريو TDES_KEY2WxR                  ( 40 )        /* Key 2 Word x Register */
#وصف_ڪريو TDES_KEY3WxR                  ( 48 )        /* Key 3 Word x Register */
#وصف_ڪريو TDES_IDATAxR                  ( 64 )        /* Input Data x Register */
#وصف_ڪريو TDES_ODATAxR                  ( 80 )        /* Output Data x Register */
#وصف_ڪريو TDES_IVxR                     ( 96 )        /* Initialization Vector x Register */
#وصف_ڪريو TDES_VR                       ( 252 )       /* TDES Version Register */
#وصف_ڪريو TDES_RPR                      ( 256 )       /* Receive Pointer Register */
#وصف_ڪريو TDES_RCR                      ( 260 )       /* Receive Counter Register */
#وصف_ڪريو TDES_TPR                      ( 264 )       /* Transmit Pointer Register */
#وصف_ڪريو TDES_TCR                      ( 268 )       /* Transmit Counter Register */
#وصف_ڪريو TDES_RNPR                     ( 272 )       /* Receive Next Pointer Register */
#وصف_ڪريو TDES_RNCR                     ( 276 )       /* Receive Next Counter Register */
#وصف_ڪريو TDES_TNPR                     ( 280 )       /* Transmit Next Pointer Register */
#وصف_ڪريو TDES_TNCR                     ( 284 )       /* Transmit Next Counter Register */
#وصف_ڪريو TDES_PTCR                     ( 288 )       /* PDC Transfer Control Register */
#وصف_ڪريو TDES_PTSR                     ( 292 )       /* PDC Transfer Status Register */
/* -------- TDES_CR : (TDES Offset: 0x0) Control Register -------- */
#وصف_ڪريو AT91_C_TDES_شروعات              ( 0x1 << 0 )  /* (TDES) Starts Processing */
#وصف_ڪريو AT91C_TDES_SWRST              ( 0x1 << 8 )  /* (TDES) Software Reset */
/* -------- TDES_MR : (TDES Offset: 0x4) Mode Register -------- */
#وصف_ڪريو AT91C_TDES_CIPHER             ( 0x1 << 0 )  /* (TDES) Processing Mode */
#وصف_ڪريو AT91C_TDES_TDESMOD            ( 0x1 << 1 )  /* (TDES) Single or Triple DES Mode */
#وصف_ڪريو AT91C_TDES_KEYMOD             ( 0x1 << 4 )  /* (TDES) Key Mode */
#وصف_ڪريو AT91C_TDES_SMOD               ( 0x3 << 8 )  /* (TDES) Start Mode */
#وصف_ڪريو     AT91C_TDES_SMOD_MANUAL    ( 0x0 << 8 )  /* (TDES) Manual Mode: The START bit in register TDES_CR must be set to begin encryption or decryption. */
#وصف_ڪريو     AT91C_TDES_SMOD_AUTO      ( 0x1 << 8 )  /* (TDES) Auto Mode: no action in TDES_CR is necessary (cf datasheet). */
#وصف_ڪريو     AT91C_TDES_SMOD_PDC       ( 0x2 << 8 )  /* (TDES) PDC Mode (cf datasheet). */
#وصف_ڪريو AT91C_TDES_OPMOD              ( 0x3 << 12 ) /* (TDES) Operation Mode */
#وصف_ڪريو     AT91C_TDES_OPMOD_ECB      ( 0x0 << 12 ) /* (TDES) ECB Electronic CodeBook mode. */
#وصف_ڪريو     AT91C_TDES_OPMOD_CBC      ( 0x1 << 12 ) /* (TDES) CBC Cipher Block Chaining mode. */
#وصف_ڪريو     AT91C_TDES_OPMOD_OFB      ( 0x2 << 12 ) /* (TDES) OFB Output Feedback mode. */
#وصف_ڪريو     AT91C_TDES_OPMOD_CFB      ( 0x3 << 12 ) /* (TDES) CFB Cipher Feedback mode. */
#وصف_ڪريو AT91C_TDES_LOD                ( 0x1 << 15 ) /* (TDES) Last Output Data Mode */
#وصف_ڪريو AT91C_TDES_CFBS               ( 0x3 << 16 ) /* (TDES) Cipher Feedback Data Size */
#وصف_ڪريو     AT91_C_TDES_CFBS_64_ٻٽو_انگ    ( 0x0 << 16 ) /* (TDES) 64-bit. */
#وصف_ڪريو     AT91_C_TDES_CFBS_32_ٻٽو_انگ    ( 0x1 << 16 ) /* (TDES) 32-bit. */
#وصف_ڪريو     AT91_C_TDES_CFBS_16_ٻٽو_انگ    ( 0x2 << 16 ) /* (TDES) 16-bit. */
#وصف_ڪريو     AT91_C_TDES_CFBS_8_ٻٽو_انگ     ( 0x3 << 16 ) /* (TDES) 8-bit. */
/* -------- TDES_IER : (TDES Offset: 0x10) Interrupt Enable Register -------- */
#وصف_ڪريو AT91C_TDES_DATRDY             ( 0x1 << 0 )  /* (TDES) DATRDY */
#وصف_ڪريو AT91C_TDES_ENDRX              ( 0x1 << 1 )  /* (TDES) PDC Read Buffer End */
#وصف_ڪريو AT91C_TDES_ENDTX              ( 0x1 << 2 )  /* (TDES) PDC Write Buffer End */
#وصف_ڪريو AT91C_TDES_RXBUFF             ( 0x1 << 3 )  /* (TDES) PDC Read Buffer Full */
#وصف_ڪريو AT91C_TDES_TXBUFE             ( 0x1 << 4 )  /* (TDES) PDC Write Buffer Empty */
#وصف_ڪريو AT91C_TDES_URAD               ( 0x1 << 8 )  /* (TDES) Unspecified Register Access Detection */
/* -------- TDES_IDR : (TDES Offset: 0x14) Interrupt Disable Register -------- */
/* -------- TDES_IMR : (TDES Offset: 0x18) Interrupt Mask Register -------- */
/* -------- TDES_ISR : (TDES Offset: 0x1c) Interrupt Status Register -------- */
#وصف_ڪريو AT91C_TDES_URAT                              ( 0x3 << 12 ) /* (TDES) Unspecified Register Access Type Status */
#وصف_ڪريو     AT91_C_TDES_URAT_اندريون_DAT_WRITE_DATPROC     ( 0x0 << 12 ) /* (TDES) Input data register written during the data processing in PDC mode. */
#وصف_ڪريو     AT91_C_TDES_URAT_ٻاهريون_DAT_READ_DATPROC     ( 0x1 << 12 ) /* (TDES) Output data register read during the data processing. */
#وصف_ڪريو     AT91C_TDES_URAT_MODEREG_WRITE_DATPROC    ( 0x2 << 12 ) /* (TDES) Mode register written during the data processing. */
#وصف_ڪريو     AT91C_TDES_URAT_WO_REG_READ              ( 0x3 << 12 ) /* (TDES) Write-only register read access. */

/* ***************************************************************************** */
/*               REGISTER ADDRESS DEFINITION FOR AT91SAM7X128 */
/* ***************************************************************************** */
/* ========== Register definition for SYS peripheral ========== */
/* ========== Register definition for AIC peripheral ========== */
#وصف_ڪريو AT91C_AIC_IVR              ( 0xFFFFF100 ) /* (AIC) IRQ Vector Register */
#وصف_ڪريو AT91C_AIC_SMR              ( 0xFFFFF000 ) /* (AIC) Source Mode Register */
#وصف_ڪريو AT91C_AIC_FVR              ( 0xFFFFF104 ) /* (AIC) FIQ Vector Register */
#وصف_ڪريو AT91C_AIC_DCR              ( 0xFFFFF138 ) /* (AIC) Debug Control Register (Protect) */
#وصف_ڪريو AT91C_AIC_EOICR            ( 0xFFFFF130 ) /* (AIC) End of Interrupt Command Register */
#وصف_ڪريو AT91C_AIC_SVR              ( 0xFFFFF080 ) /* (AIC) Source Vector Register */
#وصف_ڪريو AT91C_AIC_FFSR             ( 0xFFFFF148 ) /* (AIC) Fast Forcing Status Register */
#وصف_ڪريو AT91C_AIC_ICCR             ( 0xFFFFF128 ) /* (AIC) Interrupt Clear Command Register */
#وصف_ڪريو AT91C_AIC_ISR              ( 0xFFFFF108 ) /* (AIC) Interrupt Status Register */
#وصف_ڪريو AT91C_AIC_IMR              ( 0xFFFFF110 ) /* (AIC) Interrupt Mask Register */
#وصف_ڪريو AT91C_AIC_IPR              ( 0xFFFFF10C ) /* (AIC) Interrupt Pending Register */
#وصف_ڪريو AT91C_AIC_FFER             ( 0xFFFFF140 ) /* (AIC) Fast Forcing Enable Register */
#وصف_ڪريو AT91C_AIC_IECR             ( 0xFFFFF120 ) /* (AIC) Interrupt Enable Command Register */
#وصف_ڪريو AT91C_AIC_ISCR             ( 0xFFFFF12C ) /* (AIC) Interrupt Set Command Register */
#وصف_ڪريو AT91C_AIC_FFDR             ( 0xFFFFF144 ) /* (AIC) Fast Forcing Disable Register */
#وصف_ڪريو AT91C_AIC_CISR             ( 0xFFFFF114 ) /* (AIC) Core Interrupt Status Register */
#وصف_ڪريو AT91C_AIC_IDCR             ( 0xFFFFF124 ) /* (AIC) Interrupt Disable Command Register */
#وصف_ڪريو AT91C_AIC_SPU              ( 0xFFFFF134 ) /* (AIC) Spurious Vector Register */
/* ========== Register definition for PDC_DBGU peripheral ========== */
#وصف_ڪريو AT91C_DBGU_TCR             ( 0xFFFFF30C ) /* (PDC_DBGU) Transmit Counter Register */
#وصف_ڪريو AT91C_DBGU_RNPR            ( 0xFFFFF310 ) /* (PDC_DBGU) Receive Next Pointer Register */
#وصف_ڪريو AT91C_DBGU_TNPR            ( 0xFFFFF318 ) /* (PDC_DBGU) Transmit Next Pointer Register */
#وصف_ڪريو AT91C_DBGU_TPR             ( 0xFFFFF308 ) /* (PDC_DBGU) Transmit Pointer Register */
#وصف_ڪريو AT91C_DBGU_RPR             ( 0xFFFFF300 ) /* (PDC_DBGU) Receive Pointer Register */
#وصف_ڪريو AT91C_DBGU_RCR             ( 0xFFFFF304 ) /* (PDC_DBGU) Receive Counter Register */
#وصف_ڪريو AT91C_DBGU_RNCR            ( 0xFFFFF314 ) /* (PDC_DBGU) Receive Next Counter Register */
#وصف_ڪريو AT91C_DBGU_PTCR            ( 0xFFFFF320 ) /* (PDC_DBGU) PDC Transfer Control Register */
#وصف_ڪريو AT91C_DBGU_PTSR            ( 0xFFFFF324 ) /* (PDC_DBGU) PDC Transfer Status Register */
#وصف_ڪريو AT91C_DBGU_TNCR            ( 0xFFFFF31C ) /* (PDC_DBGU) Transmit Next Counter Register */
/* ========== Register definition for DBGU peripheral ========== */
#وصف_ڪريو AT91C_DBGU_EXID            ( 0xFFFFF244 ) /* (DBGU) Chip ID Extension Register */
#وصف_ڪريو AT91C_DBGU_BRGR            ( 0xFFFFF220 ) /* (DBGU) Baud Rate Generator Register */
#وصف_ڪريو AT91C_DBGU_IDR             ( 0xFFFFF20C ) /* (DBGU) Interrupt Disable Register */
#وصف_ڪريو AT91C_DBGU_CSR             ( 0xFFFFF214 ) /* (DBGU) Channel Status Register */
#وصف_ڪريو AT91C_DBGU_CIDR            ( 0xFFFFF240 ) /* (DBGU) Chip ID Register */
#وصف_ڪريو AT91C_DBGU_MR              ( 0xFFFFF204 ) /* (DBGU) Mode Register */
#وصف_ڪريو AT91C_DBGU_IMR             ( 0xFFFFF210 ) /* (DBGU) Interrupt Mask Register */
#وصف_ڪريو AT91C_DBGU_CR              ( 0xFFFFF200 ) /* (DBGU) Control Register */
#وصف_ڪريو AT91C_DBGU_FNTR            ( 0xFFFFF248 ) /* (DBGU) Force NTRST Register */
#وصف_ڪريو AT91C_DBGU_THR             ( 0xFFFFF21C ) /* (DBGU) Transmitter Holding Register */
#وصف_ڪريو AT91C_DBGU_RHR             ( 0xFFFFF218 ) /* (DBGU) Receiver Holding Register */
#وصف_ڪريو AT91C_DBGU_IER             ( 0xFFFFF208 ) /* (DBGU) Interrupt Enable Register */
/* ========== Register definition for PIOA peripheral ========== */
#وصف_ڪريو AT91C_PIOA_ODR             ( 0xFFFFF414 ) /* (PIOA) Output Disable Registerr */
#وصف_ڪريو AT91C_PIOA_SODR            ( 0xFFFFF430 ) /* (PIOA) Set Output Data Register */
#وصف_ڪريو AT91C_PIOA_ISR             ( 0xFFFFF44C ) /* (PIOA) Interrupt Status Register */
#وصف_ڪريو AT91C_PIOA_ABSR            ( 0xFFFFF478 ) /* (PIOA) AB Select Status Register */
#وصف_ڪريو AT91C_PIOA_IER             ( 0xFFFFF440 ) /* (PIOA) Interrupt Enable Register */
#وصف_ڪريو AT91C_PIOA_PPUDR           ( 0xFFFFF460 ) /* (PIOA) Pull-up Disable Register */
#وصف_ڪريو AT91C_PIOA_IMR             ( 0xFFFFF448 ) /* (PIOA) Interrupt Mask Register */
#وصف_ڪريو AT91_C_PIOA_في             ( 0xFFFFF400 ) /* (PIOA) PIO Enable Register */
#وصف_ڪريو AT91C_PIOA_IFDR            ( 0xFFFFF424 ) /* (PIOA) Input Filter Disable Register */
#وصف_ڪريو AT91C_PIOA_OWDR            ( 0xFFFFF4A4 ) /* (PIOA) Output Write Disable Register */
#وصف_ڪريو AT91C_PIOA_MDSR            ( 0xFFFFF458 ) /* (PIOA) Multi-driver Status Register */
#وصف_ڪريو AT91C_PIOA_IDR             ( 0xFFFFF444 ) /* (PIOA) Interrupt Disable Register */
#وصف_ڪريو AT91C_PIOA_ODSR            ( 0xFFFFF438 ) /* (PIOA) Output Data Status Register */
#وصف_ڪريو AT91C_PIOA_PPUSR           ( 0xFFFFF468 ) /* (PIOA) Pull-up Status Register */
#وصف_ڪريو AT91C_PIOA_OWSR            ( 0xFFFFF4A8 ) /* (PIOA) Output Write Status Register */
#وصف_ڪريو AT91C_PIOA_BSR             ( 0xFFFFF474 ) /* (PIOA) Select B Register */
#وصف_ڪريو AT91C_PIOA_OWER            ( 0xFFFFF4A0 ) /* (PIOA) Output Write Enable Register */
#وصف_ڪريو AT91C_PIOA_IFER            ( 0xFFFFF420 ) /* (PIOA) Input Filter Enable Register */
#وصف_ڪريو AT91C_PIOA_PDSR            ( 0xFFFFF43C ) /* (PIOA) Pin Data Status Register */
#وصف_ڪريو AT91C_PIOA_PPUER           ( 0xFFFFF464 ) /* (PIOA) Pull-up Enable Register */
#وصف_ڪريو AT91C_PIOA_OSR             ( 0xFFFFF418 ) /* (PIOA) Output Status Register */
#وصف_ڪريو AT91C_PIOA_ASR             ( 0xFFFFF470 ) /* (PIOA) Select A Register */
#وصف_ڪريو AT91C_PIOA_MDDR            ( 0xFFFFF454 ) /* (PIOA) Multi-driver Disable Register */
#وصف_ڪريو AT91C_PIOA_CODR            ( 0xFFFFF434 ) /* (PIOA) Clear Output Data Register */
#وصف_ڪريو AT91C_PIOA_MDER            ( 0xFFFFF450 ) /* (PIOA) Multi-driver Enable Register */
#وصف_ڪريو AT91C_PIOA_PDR             ( 0xFFFFF404 ) /* (PIOA) PIO Disable Register */
#وصف_ڪريو AT91C_PIOA_IFSR            ( 0xFFFFF428 ) /* (PIOA) Input Filter Status Register */
#وصف_ڪريو AT91C_PIOA_OER             ( 0xFFFFF410 ) /* (PIOA) Output Enable Register */
#وصف_ڪريو AT91C_PIOA_PSR             ( 0xFFFFF408 ) /* (PIOA) PIO Status Register */
/* ========== Register definition for PIOB peripheral ========== */
#وصف_ڪريو AT91C_PIOB_OWDR            ( 0xFFFFF6A4 ) /* (PIOB) Output Write Disable Register */
#وصف_ڪريو AT91C_PIOB_MDER            ( 0xFFFFF650 ) /* (PIOB) Multi-driver Enable Register */
#وصف_ڪريو AT91C_PIOB_PPUSR           ( 0xFFFFF668 ) /* (PIOB) Pull-up Status Register */
#وصف_ڪريو AT91C_PIOB_IMR             ( 0xFFFFF648 ) /* (PIOB) Interrupt Mask Register */
#وصف_ڪريو AT91C_PIOB_ASR             ( 0xFFFFF670 ) /* (PIOB) Select A Register */
#وصف_ڪريو AT91C_PIOB_PPUDR           ( 0xFFFFF660 ) /* (PIOB) Pull-up Disable Register */
#وصف_ڪريو AT91C_PIOB_PSR             ( 0xFFFFF608 ) /* (PIOB) PIO Status Register */
#وصف_ڪريو AT91C_PIOB_IER             ( 0xFFFFF640 ) /* (PIOB) Interrupt Enable Register */
#وصف_ڪريو AT91C_PIOB_CODR            ( 0xFFFFF634 ) /* (PIOB) Clear Output Data Register */
#وصف_ڪريو AT91C_PIOB_OWER            ( 0xFFFFF6A0 ) /* (PIOB) Output Write Enable Register */
#وصف_ڪريو AT91C_PIOB_ABSR            ( 0xFFFFF678 ) /* (PIOB) AB Select Status Register */
#وصف_ڪريو AT91C_PIOB_IFDR            ( 0xFFFFF624 ) /* (PIOB) Input Filter Disable Register */
#وصف_ڪريو AT91C_PIOB_PDSR            ( 0xFFFFF63C ) /* (PIOB) Pin Data Status Register */
#وصف_ڪريو AT91C_PIOB_IDR             ( 0xFFFFF644 ) /* (PIOB) Interrupt Disable Register */
#وصف_ڪريو AT91C_PIOB_OWSR            ( 0xFFFFF6A8 ) /* (PIOB) Output Write Status Register */
#وصف_ڪريو AT91C_PIOB_PDR             ( 0xFFFFF604 ) /* (PIOB) PIO Disable Register */
#وصف_ڪريو AT91C_PIOB_ODR             ( 0xFFFFF614 ) /* (PIOB) Output Disable Registerr */
#وصف_ڪريو AT91C_PIOB_IFSR            ( 0xFFFFF628 ) /* (PIOB) Input Filter Status Register */
#وصف_ڪريو AT91C_PIOB_PPUER           ( 0xFFFFF664 ) /* (PIOB) Pull-up Enable Register */
#وصف_ڪريو AT91C_PIOB_SODR            ( 0xFFFFF630 ) /* (PIOB) Set Output Data Register */
#وصف_ڪريو AT91C_PIOB_ISR             ( 0xFFFFF64C ) /* (PIOB) Interrupt Status Register */
#وصف_ڪريو AT91C_PIOB_ODSR            ( 0xFFFFF638 ) /* (PIOB) Output Data Status Register */
#وصف_ڪريو AT91C_PIOB_OSR             ( 0xFFFFF618 ) /* (PIOB) Output Status Register */
#وصف_ڪريو AT91C_PIOB_MDSR            ( 0xFFFFF658 ) /* (PIOB) Multi-driver Status Register */
#وصف_ڪريو AT91C_PIOB_IFER            ( 0xFFFFF620 ) /* (PIOB) Input Filter Enable Register */
#وصف_ڪريو AT91C_PIOB_BSR             ( 0xFFFFF674 ) /* (PIOB) Select B Register */
#وصف_ڪريو AT91C_PIOB_MDDR            ( 0xFFFFF654 ) /* (PIOB) Multi-driver Disable Register */
#وصف_ڪريو AT91C_PIOB_OER             ( 0xFFFFF610 ) /* (PIOB) Output Enable Register */
#وصف_ڪريو AT91_C_PIOB_في             ( 0xFFFFF600 ) /* (PIOB) PIO Enable Register */
/* ========== Register definition for CKGR peripheral ========== */
#وصف_ڪريو AT91C_CKGR_MOR             ( 0xFFFFFC20 ) /* (CKGR) Main Oscillator Register */
#وصف_ڪريو AT91C_CKGR_PLLR            ( 0xFFFFFC2C ) /* (CKGR) PLL Register */
#وصف_ڪريو AT91C_CKGR_MCFR            ( 0xFFFFFC24 ) /* (CKGR) Main Clock  Frequency Register */
/* ========== Register definition for PMC peripheral ========== */
#وصف_ڪريو AT91C_PMC_IDR              ( 0xFFFFFC64 ) /* (PMC) Interrupt Disable Register */
#وصف_ڪريو AT91C_PMC_MOR              ( 0xFFFFFC20 ) /* (PMC) Main Oscillator Register */
#وصف_ڪريو AT91C_PMC_PLLR             ( 0xFFFFFC2C ) /* (PMC) PLL Register */
#وصف_ڪريو AT91C_PMC_PCER             ( 0xFFFFFC10 ) /* (PMC) Peripheral Clock Enable Register */
#وصف_ڪريو AT91C_PMC_PCKR             ( 0xFFFFFC40 ) /* (PMC) Programmable Clock Register */
#وصف_ڪريو AT91C_PMC_MCKR             ( 0xFFFFFC30 ) /* (PMC) Master Clock Register */
#وصف_ڪريو AT91C_PMC_SCDR             ( 0xFFFFFC04 ) /* (PMC) System Clock Disable Register */
#وصف_ڪريو AT91C_PMC_PCDR             ( 0xFFFFFC14 ) /* (PMC) Peripheral Clock Disable Register */
#وصف_ڪريو AT91C_PMC_SCSR             ( 0xFFFFFC08 ) /* (PMC) System Clock Status Register */
#وصف_ڪريو AT91C_PMC_PCSR             ( 0xFFFFFC18 ) /* (PMC) Peripheral Clock Status Register */
#وصف_ڪريو AT91C_PMC_MCFR             ( 0xFFFFFC24 ) /* (PMC) Main Clock  Frequency Register */
#وصف_ڪريو AT91C_PMC_SCER             ( 0xFFFFFC00 ) /* (PMC) System Clock Enable Register */
#وصف_ڪريو AT91C_PMC_IMR              ( 0xFFFFFC6C ) /* (PMC) Interrupt Mask Register */
#وصف_ڪريو AT91C_PMC_IER              ( 0xFFFFFC60 ) /* (PMC) Interrupt Enable Register */
#وصف_ڪريو AT91C_PMC_SR               ( 0xFFFFFC68 ) /* (PMC) Status Register */
/* ========== Register definition for RSTC peripheral ========== */
#وصف_ڪريو AT91C_RSTC_RCR             ( 0xFFFFFD00 ) /* (RSTC) Reset Control Register */
#وصف_ڪريو AT91C_RSTC_RMR             ( 0xFFFFFD08 ) /* (RSTC) Reset Mode Register */
#وصف_ڪريو AT91C_RSTC_RSR             ( 0xFFFFFD04 ) /* (RSTC) Reset Status Register */
/* ========== Register definition for RTTC peripheral ========== */
#وصف_ڪريو AT91C_RTTC_RTSR            ( 0xFFFFFD2C ) /* (RTTC) Real-time Status Register */
#وصف_ڪريو AT91C_RTTC_RTMR            ( 0xFFFFFD20 ) /* (RTTC) Real-time Mode Register */
#وصف_ڪريو AT91C_RTTC_RTVR            ( 0xFFFFFD28 ) /* (RTTC) Real-time Value Register */
#وصف_ڪريو AT91C_RTTC_RTAR            ( 0xFFFFFD24 ) /* (RTTC) Real-time Alarm Register */
/* ========== Register definition for PITC peripheral ========== */
#وصف_ڪريو AT91C_PITC_PIVR            ( 0xFFFFFD38 ) /* (PITC) Period Interval Value Register */
#وصف_ڪريو AT91C_PITC_PISR            ( 0xFFFFFD34 ) /* (PITC) Period Interval Status Register */
#وصف_ڪريو AT91C_PITC_PIIR            ( 0xFFFFFD3C ) /* (PITC) Period Interval Image Register */
#وصف_ڪريو AT91C_PITC_PIMR            ( 0xFFFFFD30 ) /* (PITC) Period Interval Mode Register */
/* ========== Register definition for WDTC peripheral ========== */
#وصف_ڪريو AT91C_WDTC_WDCR            ( 0xFFFFFD40 ) /* (WDTC) Watchdog Control Register */
#وصف_ڪريو AT91C_WDTC_WDSR            ( 0xFFFFFD48 ) /* (WDTC) Watchdog Status Register */
#وصف_ڪريو AT91C_WDTC_WDMR            ( 0xFFFFFD44 ) /* (WDTC) Watchdog Mode Register */
/* ========== Register definition for VREG peripheral ========== */
#وصف_ڪريو AT91C_VREG_MR              ( 0xFFFFFD60 ) /* (VREG) Voltage Regulator Mode Register */
/* ========== Register definition for MC peripheral ========== */
#وصف_ڪريو AT91C_MC_ASR               ( 0xFFFFFF04 ) /* (MC) MC Abort Status Register */
#وصف_ڪريو AT91C_MC_RCR               ( 0xFFFFFF00 ) /* (MC) MC Remap Control Register */
#وصف_ڪريو AT91C_MC_FCR               ( 0xFFFFFF64 ) /* (MC) MC Flash Command Register */
#وصف_ڪريو AT91C_MC_AASR              ( 0xFFFFFF08 ) /* (MC) MC Abort Address Status Register */
#وصف_ڪريو AT91C_MC_FSR               ( 0xFFFFFF68 ) /* (MC) MC Flash Status Register */
#وصف_ڪريو AT91C_MC_FMR               ( 0xFFFFFF60 ) /* (MC) MC Flash Mode Register */
/* ========== Register definition for PDC_SPI1 peripheral ========== */
#وصف_ڪريو AT91C_SPI1_PTCR            ( 0xFFFE4120 ) /* (PDC_SPI1) PDC Transfer Control Register */
#وصف_ڪريو AT91C_SPI1_RPR             ( 0xFFFE4100 ) /* (PDC_SPI1) Receive Pointer Register */
#وصف_ڪريو AT91C_SPI1_TNCR            ( 0xFFFE411C ) /* (PDC_SPI1) Transmit Next Counter Register */
#وصف_ڪريو AT91C_SPI1_TPR             ( 0xFFFE4108 ) /* (PDC_SPI1) Transmit Pointer Register */
#وصف_ڪريو AT91C_SPI1_TNPR            ( 0xFFFE4118 ) /* (PDC_SPI1) Transmit Next Pointer Register */
#وصف_ڪريو AT91C_SPI1_TCR             ( 0xFFFE410C ) /* (PDC_SPI1) Transmit Counter Register */
#وصف_ڪريو AT91C_SPI1_RCR             ( 0xFFFE4104 ) /* (PDC_SPI1) Receive Counter Register */
#وصف_ڪريو AT91C_SPI1_RNPR            ( 0xFFFE4110 ) /* (PDC_SPI1) Receive Next Pointer Register */
#وصف_ڪريو AT91C_SPI1_RNCR            ( 0xFFFE4114 ) /* (PDC_SPI1) Receive Next Counter Register */
#وصف_ڪريو AT91C_SPI1_PTSR            ( 0xFFFE4124 ) /* (PDC_SPI1) PDC Transfer Status Register */
/* ========== Register definition for SPI1 peripheral ========== */
#وصف_ڪريو AT91C_SPI1_IMR             ( 0xFFFE401C ) /* (SPI1) Interrupt Mask Register */
#وصف_ڪريو AT91C_SPI1_IER             ( 0xFFFE4014 ) /* (SPI1) Interrupt Enable Register */
#وصف_ڪريو AT91C_SPI1_MR              ( 0xFFFE4004 ) /* (SPI1) Mode Register */
#وصف_ڪريو AT91C_SPI1_RDR             ( 0xFFFE4008 ) /* (SPI1) Receive Data Register */
#وصف_ڪريو AT91C_SPI1_IDR             ( 0xFFFE4018 ) /* (SPI1) Interrupt Disable Register */
#وصف_ڪريو AT91C_SPI1_SR              ( 0xFFFE4010 ) /* (SPI1) Status Register */
#وصف_ڪريو AT91C_SPI1_TDR             ( 0xFFFE400C ) /* (SPI1) Transmit Data Register */
#وصف_ڪريو AT91C_SPI1_CR              ( 0xFFFE4000 ) /* (SPI1) Control Register */
#وصف_ڪريو AT91C_SPI1_CSR             ( 0xFFFE4030 ) /* (SPI1) Chip Select Register */
/* ========== Register definition for PDC_SPI0 peripheral ========== */
#وصف_ڪريو AT91C_SPI0_PTCR            ( 0xFFFE0120 ) /* (PDC_SPI0) PDC Transfer Control Register */
#وصف_ڪريو AT91C_SPI0_TPR             ( 0xFFFE0108 ) /* (PDC_SPI0) Transmit Pointer Register */
#وصف_ڪريو AT91C_SPI0_TCR             ( 0xFFFE010C ) /* (PDC_SPI0) Transmit Counter Register */
#وصف_ڪريو AT91C_SPI0_RCR             ( 0xFFFE0104 ) /* (PDC_SPI0) Receive Counter Register */
#وصف_ڪريو AT91C_SPI0_PTSR            ( 0xFFFE0124 ) /* (PDC_SPI0) PDC Transfer Status Register */
#وصف_ڪريو AT91C_SPI0_RNPR            ( 0xFFFE0110 ) /* (PDC_SPI0) Receive Next Pointer Register */
#وصف_ڪريو AT91C_SPI0_RPR             ( 0xFFFE0100 ) /* (PDC_SPI0) Receive Pointer Register */
#وصف_ڪريو AT91C_SPI0_TNCR            ( 0xFFFE011C ) /* (PDC_SPI0) Transmit Next Counter Register */
#وصف_ڪريو AT91C_SPI0_RNCR            ( 0xFFFE0114 ) /* (PDC_SPI0) Receive Next Counter Register */
#وصف_ڪريو AT91C_SPI0_TNPR            ( 0xFFFE0118 ) /* (PDC_SPI0) Transmit Next Pointer Register */
/* ========== Register definition for SPI0 peripheral ========== */
#وصف_ڪريو AT91C_SPI0_IER             ( 0xFFFE0014 ) /* (SPI0) Interrupt Enable Register */
#وصف_ڪريو AT91C_SPI0_SR              ( 0xFFFE0010 ) /* (SPI0) Status Register */
#وصف_ڪريو AT91C_SPI0_IDR             ( 0xFFFE0018 ) /* (SPI0) Interrupt Disable Register */
#وصف_ڪريو AT91C_SPI0_CR              ( 0xFFFE0000 ) /* (SPI0) Control Register */
#وصف_ڪريو AT91C_SPI0_MR              ( 0xFFFE0004 ) /* (SPI0) Mode Register */
#وصف_ڪريو AT91C_SPI0_IMR             ( 0xFFFE001C ) /* (SPI0) Interrupt Mask Register */
#وصف_ڪريو AT91C_SPI0_TDR             ( 0xFFFE000C ) /* (SPI0) Transmit Data Register */
#وصف_ڪريو AT91C_SPI0_RDR             ( 0xFFFE0008 ) /* (SPI0) Receive Data Register */
#وصف_ڪريو AT91C_SPI0_CSR             ( 0xFFFE0030 ) /* (SPI0) Chip Select Register */
/* ========== Register definition for PDC_US1 peripheral ========== */
#وصف_ڪريو AT91C_US1_RNCR             ( 0xFFFC4114 ) /* (PDC_US1) Receive Next Counter Register */
#وصف_ڪريو AT91C_US1_PTCR             ( 0xFFFC4120 ) /* (PDC_US1) PDC Transfer Control Register */
#وصف_ڪريو AT91C_US1_TCR              ( 0xFFFC410C ) /* (PDC_US1) Transmit Counter Register */
#وصف_ڪريو AT91C_US1_PTSR             ( 0xFFFC4124 ) /* (PDC_US1) PDC Transfer Status Register */
#وصف_ڪريو AT91C_US1_TNPR             ( 0xFFFC4118 ) /* (PDC_US1) Transmit Next Pointer Register */
#وصف_ڪريو AT91C_US1_RCR              ( 0xFFFC4104 ) /* (PDC_US1) Receive Counter Register */
#وصف_ڪريو AT91C_US1_RNPR             ( 0xFFFC4110 ) /* (PDC_US1) Receive Next Pointer Register */
#وصف_ڪريو AT91C_US1_RPR              ( 0xFFFC4100 ) /* (PDC_US1) Receive Pointer Register */
#وصف_ڪريو AT91C_US1_TNCR             ( 0xFFFC411C ) /* (PDC_US1) Transmit Next Counter Register */
#وصف_ڪريو AT91C_US1_TPR              ( 0xFFFC4108 ) /* (PDC_US1) Transmit Pointer Register */
/* ========== Register definition for US1 peripheral ========== */
#وصف_ڪريو AT91C_US1_IF               ( 0xFFFC404C ) /* (US1) IRDA_FILTER Register */
#وصف_ڪريو AT91C_US1_NER              ( 0xFFFC4044 ) /* (US1) Nb Errors Register */
#وصف_ڪريو AT91C_US1_RTOR             ( 0xFFFC4024 ) /* (US1) Receiver Time-out Register */
#وصف_ڪريو AT91C_US1_CSR              ( 0xFFFC4014 ) /* (US1) Channel Status Register */
#وصف_ڪريو AT91C_US1_IDR              ( 0xFFFC400C ) /* (US1) Interrupt Disable Register */
#وصف_ڪريو AT91C_US1_IER              ( 0xFFFC4008 ) /* (US1) Interrupt Enable Register */
#وصف_ڪريو AT91C_US1_THR              ( 0xFFFC401C ) /* (US1) Transmitter Holding Register */
#وصف_ڪريو AT91C_US1_TTGR             ( 0xFFFC4028 ) /* (US1) Transmitter Time-guard Register */
#وصف_ڪريو AT91C_US1_RHR              ( 0xFFFC4018 ) /* (US1) Receiver Holding Register */
#وصف_ڪريو AT91C_US1_BRGR             ( 0xFFFC4020 ) /* (US1) Baud Rate Generator Register */
#وصف_ڪريو AT91C_US1_IMR              ( 0xFFFC4010 ) /* (US1) Interrupt Mask Register */
#وصف_ڪريو AT91C_US1_FIDI             ( 0xFFFC4040 ) /* (US1) FI_DI_Ratio Register */
#وصف_ڪريو AT91C_US1_CR               ( 0xFFFC4000 ) /* (US1) Control Register */
#وصف_ڪريو AT91C_US1_MR               ( 0xFFFC4004 ) /* (US1) Mode Register */
/* ========== Register definition for PDC_US0 peripheral ========== */
#وصف_ڪريو AT91C_US0_TNPR             ( 0xFFFC0118 ) /* (PDC_US0) Transmit Next Pointer Register */
#وصف_ڪريو AT91C_US0_RNPR             ( 0xFFFC0110 ) /* (PDC_US0) Receive Next Pointer Register */
#وصف_ڪريو AT91C_US0_TCR              ( 0xFFFC010C ) /* (PDC_US0) Transmit Counter Register */
#وصف_ڪريو AT91C_US0_PTCR             ( 0xFFFC0120 ) /* (PDC_US0) PDC Transfer Control Register */
#وصف_ڪريو AT91C_US0_PTSR             ( 0xFFFC0124 ) /* (PDC_US0) PDC Transfer Status Register */
#وصف_ڪريو AT91C_US0_TNCR             ( 0xFFFC011C ) /* (PDC_US0) Transmit Next Counter Register */
#وصف_ڪريو AT91C_US0_TPR              ( 0xFFFC0108 ) /* (PDC_US0) Transmit Pointer Register */
#وصف_ڪريو AT91C_US0_RCR              ( 0xFFFC0104 ) /* (PDC_US0) Receive Counter Register */
#وصف_ڪريو AT91C_US0_RPR              ( 0xFFFC0100 ) /* (PDC_US0) Receive Pointer Register */
#وصف_ڪريو AT91C_US0_RNCR             ( 0xFFFC0114 ) /* (PDC_US0) Receive Next Counter Register */
/* ========== Register definition for US0 peripheral ========== */
#وصف_ڪريو AT91C_US0_BRGR             ( 0xFFFC0020 ) /* (US0) Baud Rate Generator Register */
#وصف_ڪريو AT91C_US0_NER              ( 0xFFFC0044 ) /* (US0) Nb Errors Register */
#وصف_ڪريو AT91C_US0_CR               ( 0xFFFC0000 ) /* (US0) Control Register */
#وصف_ڪريو AT91C_US0_IMR              ( 0xFFFC0010 ) /* (US0) Interrupt Mask Register */
#وصف_ڪريو AT91C_US0_FIDI             ( 0xFFFC0040 ) /* (US0) FI_DI_Ratio Register */
#وصف_ڪريو AT91C_US0_TTGR             ( 0xFFFC0028 ) /* (US0) Transmitter Time-guard Register */
#وصف_ڪريو AT91C_US0_MR               ( 0xFFFC0004 ) /* (US0) Mode Register */
#وصف_ڪريو AT91C_US0_RTOR             ( 0xFFFC0024 ) /* (US0) Receiver Time-out Register */
#وصف_ڪريو AT91C_US0_CSR              ( 0xFFFC0014 ) /* (US0) Channel Status Register */
#وصف_ڪريو AT91C_US0_RHR              ( 0xFFFC0018 ) /* (US0) Receiver Holding Register */
#وصف_ڪريو AT91C_US0_IDR              ( 0xFFFC000C ) /* (US0) Interrupt Disable Register */
#وصف_ڪريو AT91C_US0_THR              ( 0xFFFC001C ) /* (US0) Transmitter Holding Register */
#وصف_ڪريو AT91C_US0_IF               ( 0xFFFC004C ) /* (US0) IRDA_FILTER Register */
#وصف_ڪريو AT91C_US0_IER              ( 0xFFFC0008 ) /* (US0) Interrupt Enable Register */
/* ========== Register definition for PDC_SSC peripheral ========== */
#وصف_ڪريو AT91C_SSC_TNCR             ( 0xFFFD411C ) /* (PDC_SSC) Transmit Next Counter Register */
#وصف_ڪريو AT91C_SSC_RPR              ( 0xFFFD4100 ) /* (PDC_SSC) Receive Pointer Register */
#وصف_ڪريو AT91C_SSC_RNCR             ( 0xFFFD4114 ) /* (PDC_SSC) Receive Next Counter Register */
#وصف_ڪريو AT91C_SSC_TPR              ( 0xFFFD4108 ) /* (PDC_SSC) Transmit Pointer Register */
#وصف_ڪريو AT91C_SSC_PTCR             ( 0xFFFD4120 ) /* (PDC_SSC) PDC Transfer Control Register */
#وصف_ڪريو AT91C_SSC_TCR              ( 0xFFFD410C ) /* (PDC_SSC) Transmit Counter Register */
#وصف_ڪريو AT91C_SSC_RCR              ( 0xFFFD4104 ) /* (PDC_SSC) Receive Counter Register */
#وصف_ڪريو AT91C_SSC_RNPR             ( 0xFFFD4110 ) /* (PDC_SSC) Receive Next Pointer Register */
#وصف_ڪريو AT91C_SSC_TNPR             ( 0xFFFD4118 ) /* (PDC_SSC) Transmit Next Pointer Register */
#وصف_ڪريو AT91C_SSC_PTSR             ( 0xFFFD4124 ) /* (PDC_SSC) PDC Transfer Status Register */
/* ========== Register definition for SSC peripheral ========== */
#وصف_ڪريو AT91C_SSC_RHR              ( 0xFFFD4020 ) /* (SSC) Receive Holding Register */
#وصف_ڪريو AT91C_SSC_RSHR             ( 0xFFFD4030 ) /* (SSC) Receive Sync Holding Register */
#وصف_ڪريو AT91C_SSC_TFMR             ( 0xFFFD401C ) /* (SSC) Transmit Frame Mode Register */
#وصف_ڪريو AT91C_SSC_IDR              ( 0xFFFD4048 ) /* (SSC) Interrupt Disable Register */
#وصف_ڪريو AT91C_SSC_THR              ( 0xFFFD4024 ) /* (SSC) Transmit Holding Register */
#وصف_ڪريو AT91C_SSC_RCMR             ( 0xFFFD4010 ) /* (SSC) Receive Clock ModeRegister */
#وصف_ڪريو AT91C_SSC_IER              ( 0xFFFD4044 ) /* (SSC) Interrupt Enable Register */
#وصف_ڪريو AT91C_SSC_TSHR             ( 0xFFFD4034 ) /* (SSC) Transmit Sync Holding Register */
#وصف_ڪريو AT91C_SSC_SR               ( 0xFFFD4040 ) /* (SSC) Status Register */
#وصف_ڪريو AT91C_SSC_CMR              ( 0xFFFD4004 ) /* (SSC) Clock Mode Register */
#وصف_ڪريو AT91C_SSC_TCMR             ( 0xFFFD4018 ) /* (SSC) Transmit Clock Mode Register */
#وصف_ڪريو AT91C_SSC_CR               ( 0xFFFD4000 ) /* (SSC) Control Register */
#وصف_ڪريو AT91C_SSC_IMR              ( 0xFFFD404C ) /* (SSC) Interrupt Mask Register */
#وصف_ڪريو AT91C_SSC_RFMR             ( 0xFFFD4014 ) /* (SSC) Receive Frame Mode Register */
/* ========== Register definition for TWI peripheral ========== */
#وصف_ڪريو AT91C_TWI_IER              ( 0xFFFB8024 ) /* (TWI) Interrupt Enable Register */
#وصف_ڪريو AT91C_TWI_CR               ( 0xFFFB8000 ) /* (TWI) Control Register */
#وصف_ڪريو AT91C_TWI_SR               ( 0xFFFB8020 ) /* (TWI) Status Register */
#وصف_ڪريو AT91C_TWI_IMR              ( 0xFFFB802C ) /* (TWI) Interrupt Mask Register */
#وصف_ڪريو AT91C_TWI_THR              ( 0xFFFB8034 ) /* (TWI) Transmit Holding Register */
#وصف_ڪريو AT91C_TWI_IDR              ( 0xFFFB8028 ) /* (TWI) Interrupt Disable Register */
#وصف_ڪريو AT91C_TWI_IADR             ( 0xFFFB800C ) /* (TWI) Internal Address Register */
#وصف_ڪريو AT91C_TWI_MMR              ( 0xFFFB8004 ) /* (TWI) Master Mode Register */
#وصف_ڪريو AT91C_TWI_CWGR             ( 0xFFFB8010 ) /* (TWI) Clock Waveform Generator Register */
#وصف_ڪريو AT91C_TWI_RHR              ( 0xFFFB8030 ) /* (TWI) Receive Holding Register */
/* ========== Register definition for PWMC_CH3 peripheral ========== */
#وصف_ڪريو AT91C_PWMC_CH3_CUPDR       ( 0xFFFCC270 ) /* (PWMC_CH3) Channel Update Register */
#وصف_ڪريو AT91C_PWMC_CH3_Reserved    ( 0xFFFCC274 ) /* (PWMC_CH3) Reserved */
#وصف_ڪريو AT91C_PWMC_CH3_CPRDR       ( 0xFFFCC268 ) /* (PWMC_CH3) Channel Period Register */
#وصف_ڪريو AT91C_PWMC_CH3_CDTYR       ( 0xFFFCC264 ) /* (PWMC_CH3) Channel Duty Cycle Register */
#وصف_ڪريو AT91C_PWMC_CH3_CCNTR       ( 0xFFFCC26C ) /* (PWMC_CH3) Channel Counter Register */
#وصف_ڪريو AT91C_PWMC_CH3_CMR         ( 0xFFFCC260 ) /* (PWMC_CH3) Channel Mode Register */
/* ========== Register definition for PWMC_CH2 peripheral ========== */
#وصف_ڪريو AT91C_PWMC_CH2_Reserved    ( 0xFFFCC254 ) /* (PWMC_CH2) Reserved */
#وصف_ڪريو AT91C_PWMC_CH2_CMR         ( 0xFFFCC240 ) /* (PWMC_CH2) Channel Mode Register */
#وصف_ڪريو AT91C_PWMC_CH2_CCNTR       ( 0xFFFCC24C ) /* (PWMC_CH2) Channel Counter Register */
#وصف_ڪريو AT91C_PWMC_CH2_CPRDR       ( 0xFFFCC248 ) /* (PWMC_CH2) Channel Period Register */
#وصف_ڪريو AT91C_PWMC_CH2_CUPDR       ( 0xFFFCC250 ) /* (PWMC_CH2) Channel Update Register */
#وصف_ڪريو AT91C_PWMC_CH2_CDTYR       ( 0xFFFCC244 ) /* (PWMC_CH2) Channel Duty Cycle Register */
/* ========== Register definition for PWMC_CH1 peripheral ========== */
#وصف_ڪريو AT91C_PWMC_CH1_Reserved    ( 0xFFFCC234 ) /* (PWMC_CH1) Reserved */
#وصف_ڪريو AT91C_PWMC_CH1_CUPDR       ( 0xFFFCC230 ) /* (PWMC_CH1) Channel Update Register */
#وصف_ڪريو AT91C_PWMC_CH1_CPRDR       ( 0xFFFCC228 ) /* (PWMC_CH1) Channel Period Register */
#وصف_ڪريو AT91C_PWMC_CH1_CCNTR       ( 0xFFFCC22C ) /* (PWMC_CH1) Channel Counter Register */
#وصف_ڪريو AT91C_PWMC_CH1_CDTYR       ( 0xFFFCC224 ) /* (PWMC_CH1) Channel Duty Cycle Register */
#وصف_ڪريو AT91C_PWMC_CH1_CMR         ( 0xFFFCC220 ) /* (PWMC_CH1) Channel Mode Register */
/* ========== Register definition for PWMC_CH0 peripheral ========== */
#وصف_ڪريو AT91C_PWMC_CH0_Reserved    ( 0xFFFCC214 ) /* (PWMC_CH0) Reserved */
#وصف_ڪريو AT91C_PWMC_CH0_CPRDR       ( 0xFFFCC208 ) /* (PWMC_CH0) Channel Period Register */
#وصف_ڪريو AT91C_PWMC_CH0_CDTYR       ( 0xFFFCC204 ) /* (PWMC_CH0) Channel Duty Cycle Register */
#وصف_ڪريو AT91C_PWMC_CH0_CMR         ( 0xFFFCC200 ) /* (PWMC_CH0) Channel Mode Register */
#وصف_ڪريو AT91C_PWMC_CH0_CUPDR       ( 0xFFFCC210 ) /* (PWMC_CH0) Channel Update Register */
#وصف_ڪريو AT91C_PWMC_CH0_CCNTR       ( 0xFFFCC20C ) /* (PWMC_CH0) Channel Counter Register */
/* ========== Register definition for PWMC peripheral ========== */
#وصف_ڪريو AT91C_PWMC_IDR             ( 0xFFFCC014 ) /* (PWMC) PWMC Interrupt Disable Register */
#وصف_ڪريو AT91C_PWMC_DIS             ( 0xFFFCC008 ) /* (PWMC) PWMC Disable Register */
#وصف_ڪريو AT91C_PWMC_IER             ( 0xFFFCC010 ) /* (PWMC) PWMC Interrupt Enable Register */
#وصف_ڪريو AT91C_PWMC_VR              ( 0xFFFCC0FC ) /* (PWMC) PWMC Version Register */
#وصف_ڪريو AT91C_PWMC_ISR             ( 0xFFFCC01C ) /* (PWMC) PWMC Interrupt Status Register */
#وصف_ڪريو AT91C_PWMC_SR              ( 0xFFFCC00C ) /* (PWMC) PWMC Status Register */
#وصف_ڪريو AT91C_PWMC_IMR             ( 0xFFFCC018 ) /* (PWMC) PWMC Interrupt Mask Register */
#وصف_ڪريو AT91C_PWMC_MR              ( 0xFFFCC000 ) /* (PWMC) PWMC Mode Register */
#وصف_ڪريو AT91C_PWMC_ENA             ( 0xFFFCC004 ) /* (PWMC) PWMC Enable Register */
/* ========== Register definition for UDP peripheral ========== */
#وصف_ڪريو AT91C_UDP_IMR              ( 0xFFFB0018 ) /* (UDP) Interrupt Mask Register */
#وصف_ڪريو AT91C_UDP_FADDR            ( 0xFFFB0008 ) /* (UDP) Function Address Register */
#وصف_ڪريو AT91_C_UDP_انگ              ( 0xFFFB0000 ) /* (UDP) Frame Number Register */
#وصف_ڪريو AT91C_UDP_FDR              ( 0xFFFB0050 ) /* (UDP) Endpoint FIFO Data Register */
#وصف_ڪريو AT91C_UDP_ISR              ( 0xFFFB001C ) /* (UDP) Interrupt Status Register */
#وصف_ڪريو AT91C_UDP_CSR              ( 0xFFFB0030 ) /* (UDP) Endpoint Control and Status Register */
#وصف_ڪريو AT91C_UDP_IDR              ( 0xFFFB0014 ) /* (UDP) Interrupt Disable Register */
#وصف_ڪريو AT91C_UDP_ICR              ( 0xFFFB0020 ) /* (UDP) Interrupt Clear Register */
#وصف_ڪريو AT91C_UDP_RSTEP            ( 0xFFFB0028 ) /* (UDP) Reset Endpoint Register */
#وصف_ڪريو AT91C_UDP_TXVC             ( 0xFFFB0074 ) /* (UDP) Transceiver Control Register */
#وصف_ڪريو AT91C_UDP_GLBSTATE         ( 0xFFFB0004 ) /* (UDP) Global State Register */
#وصف_ڪريو AT91C_UDP_IER              ( 0xFFFB0010 ) /* (UDP) Interrupt Enable Register */
/* ========== Register definition for TC0 peripheral ========== */
#وصف_ڪريو AT91C_TC0_SR               ( 0xFFFA0020 ) /* (TC0) Status Register */
#وصف_ڪريو AT91C_TC0_RC               ( 0xFFFA001C ) /* (TC0) Register C */
#وصف_ڪريو AT91C_TC0_RB               ( 0xFFFA0018 ) /* (TC0) Register B */
#وصف_ڪريو AT91C_TC0_CCR              ( 0xFFFA0000 ) /* (TC0) Channel Control Register */
#وصف_ڪريو AT91C_TC0_CMR              ( 0xFFFA0004 ) /* (TC0) Channel Mode Register (Capture Mode / Waveform Mode) */
#وصف_ڪريو AT91C_TC0_IER              ( 0xFFFA0024 ) /* (TC0) Interrupt Enable Register */
#وصف_ڪريو AT91C_TC0_RA               ( 0xFFFA0014 ) /* (TC0) Register A */
#وصف_ڪريو AT91C_TC0_IDR              ( 0xFFFA0028 ) /* (TC0) Interrupt Disable Register */
#وصف_ڪريو AT91C_TC0_CV               ( 0xFFFA0010 ) /* (TC0) Counter Value */
#وصف_ڪريو AT91C_TC0_IMR              ( 0xFFFA002C ) /* (TC0) Interrupt Mask Register */
/* ========== Register definition for TC1 peripheral ========== */
#وصف_ڪريو AT91C_TC1_RB               ( 0xFFFA0058 ) /* (TC1) Register B */
#وصف_ڪريو AT91C_TC1_CCR              ( 0xFFFA0040 ) /* (TC1) Channel Control Register */
#وصف_ڪريو AT91C_TC1_IER              ( 0xFFFA0064 ) /* (TC1) Interrupt Enable Register */
#وصف_ڪريو AT91C_TC1_IDR              ( 0xFFFA0068 ) /* (TC1) Interrupt Disable Register */
#وصف_ڪريو AT91C_TC1_SR               ( 0xFFFA0060 ) /* (TC1) Status Register */
#وصف_ڪريو AT91C_TC1_CMR              ( 0xFFFA0044 ) /* (TC1) Channel Mode Register (Capture Mode / Waveform Mode) */
#وصف_ڪريو AT91C_TC1_RA               ( 0xFFFA0054 ) /* (TC1) Register A */
#وصف_ڪريو AT91C_TC1_RC               ( 0xFFFA005C ) /* (TC1) Register C */
#وصف_ڪريو AT91C_TC1_IMR              ( 0xFFFA006C ) /* (TC1) Interrupt Mask Register */
#وصف_ڪريو AT91C_TC1_CV               ( 0xFFFA0050 ) /* (TC1) Counter Value */
/* ========== Register definition for TC2 peripheral ========== */
#وصف_ڪريو AT91C_TC2_CMR              ( 0xFFFA0084 ) /* (TC2) Channel Mode Register (Capture Mode / Waveform Mode) */
#وصف_ڪريو AT91C_TC2_CCR              ( 0xFFFA0080 ) /* (TC2) Channel Control Register */
#وصف_ڪريو AT91C_TC2_CV               ( 0xFFFA0090 ) /* (TC2) Counter Value */
#وصف_ڪريو AT91C_TC2_RA               ( 0xFFFA0094 ) /* (TC2) Register A */
#وصف_ڪريو AT91C_TC2_RB               ( 0xFFFA0098 ) /* (TC2) Register B */
#وصف_ڪريو AT91C_TC2_IDR              ( 0xFFFA00A8 ) /* (TC2) Interrupt Disable Register */
#وصف_ڪريو AT91C_TC2_IMR              ( 0xFFFA00AC ) /* (TC2) Interrupt Mask Register */
#وصف_ڪريو AT91C_TC2_RC               ( 0xFFFA009C ) /* (TC2) Register C */
#وصف_ڪريو AT91C_TC2_IER              ( 0xFFFA00A4 ) /* (TC2) Interrupt Enable Register */
#وصف_ڪريو AT91C_TC2_SR               ( 0xFFFA00A0 ) /* (TC2) Status Register */
/* ========== Register definition for TCB peripheral ========== */
#وصف_ڪريو AT91C_TCB_BMR              ( 0xFFFA00C4 ) /* (TCB) TC Block Mode Register */
#وصف_ڪريو AT91C_TCB_BCR              ( 0xFFFA00C0 ) /* (TCB) TC Block Control Register */
/* ========== Register definition for CAN_MB0 peripheral ========== */
#وصف_ڪريو AT91C_CAN_MB0_MDL          ( 0xFFFD0214 ) /* (CAN_MB0) MailBox Data Low Register */
#وصف_ڪريو AT91C_CAN_MB0_MAM          ( 0xFFFD0204 ) /* (CAN_MB0) MailBox Acceptance Mask Register */
#وصف_ڪريو AT91C_CAN_MB0_MCR          ( 0xFFFD021C ) /* (CAN_MB0) MailBox Control Register */
#وصف_ڪريو AT91C_CAN_MB0_MID          ( 0xFFFD0208 ) /* (CAN_MB0) MailBox ID Register */
#وصف_ڪريو AT91C_CAN_MB0_MSR          ( 0xFFFD0210 ) /* (CAN_MB0) MailBox Status Register */
#وصف_ڪريو AT91C_CAN_MB0_MFID         ( 0xFFFD020C ) /* (CAN_MB0) MailBox Family ID Register */
#وصف_ڪريو AT91C_CAN_MB0_MDH          ( 0xFFFD0218 ) /* (CAN_MB0) MailBox Data High Register */
#وصف_ڪريو AT91C_CAN_MB0_MMR          ( 0xFFFD0200 ) /* (CAN_MB0) MailBox Mode Register */
/* ========== Register definition for CAN_MB1 peripheral ========== */
#وصف_ڪريو AT91C_CAN_MB1_MDL          ( 0xFFFD0234 ) /* (CAN_MB1) MailBox Data Low Register */
#وصف_ڪريو AT91C_CAN_MB1_MID          ( 0xFFFD0228 ) /* (CAN_MB1) MailBox ID Register */
#وصف_ڪريو AT91C_CAN_MB1_MMR          ( 0xFFFD0220 ) /* (CAN_MB1) MailBox Mode Register */
#وصف_ڪريو AT91C_CAN_MB1_MSR          ( 0xFFFD0230 ) /* (CAN_MB1) MailBox Status Register */
#وصف_ڪريو AT91C_CAN_MB1_MAM          ( 0xFFFD0224 ) /* (CAN_MB1) MailBox Acceptance Mask Register */
#وصف_ڪريو AT91C_CAN_MB1_MDH          ( 0xFFFD0238 ) /* (CAN_MB1) MailBox Data High Register */
#وصف_ڪريو AT91C_CAN_MB1_MCR          ( 0xFFFD023C ) /* (CAN_MB1) MailBox Control Register */
#وصف_ڪريو AT91C_CAN_MB1_MFID         ( 0xFFFD022C ) /* (CAN_MB1) MailBox Family ID Register */
/* ========== Register definition for CAN_MB2 peripheral ========== */
#وصف_ڪريو AT91C_CAN_MB2_MCR          ( 0xFFFD025C ) /* (CAN_MB2) MailBox Control Register */
#وصف_ڪريو AT91C_CAN_MB2_MDH          ( 0xFFFD0258 ) /* (CAN_MB2) MailBox Data High Register */
#وصف_ڪريو AT91C_CAN_MB2_MID          ( 0xFFFD0248 ) /* (CAN_MB2) MailBox ID Register */
#وصف_ڪريو AT91C_CAN_MB2_MDL          ( 0xFFFD0254 ) /* (CAN_MB2) MailBox Data Low Register */
#وصف_ڪريو AT91C_CAN_MB2_MMR          ( 0xFFFD0240 ) /* (CAN_MB2) MailBox Mode Register */
#وصف_ڪريو AT91C_CAN_MB2_MAM          ( 0xFFFD0244 ) /* (CAN_MB2) MailBox Acceptance Mask Register */
#وصف_ڪريو AT91C_CAN_MB2_MFID         ( 0xFFFD024C ) /* (CAN_MB2) MailBox Family ID Register */
#وصف_ڪريو AT91C_CAN_MB2_MSR          ( 0xFFFD0250 ) /* (CAN_MB2) MailBox Status Register */
/* ========== Register definition for CAN_MB3 peripheral ========== */
#وصف_ڪريو AT91C_CAN_MB3_MFID         ( 0xFFFD026C ) /* (CAN_MB3) MailBox Family ID Register */
#وصف_ڪريو AT91C_CAN_MB3_MAM          ( 0xFFFD0264 ) /* (CAN_MB3) MailBox Acceptance Mask Register */
#وصف_ڪريو AT91C_CAN_MB3_MID          ( 0xFFFD0268 ) /* (CAN_MB3) MailBox ID Register */
#وصف_ڪريو AT91C_CAN_MB3_MCR          ( 0xFFFD027C ) /* (CAN_MB3) MailBox Control Register */
#وصف_ڪريو AT91C_CAN_MB3_MMR          ( 0xFFFD0260 ) /* (CAN_MB3) MailBox Mode Register */
#وصف_ڪريو AT91C_CAN_MB3_MSR          ( 0xFFFD0270 ) /* (CAN_MB3) MailBox Status Register */
#وصف_ڪريو AT91C_CAN_MB3_MDL          ( 0xFFFD0274 ) /* (CAN_MB3) MailBox Data Low Register */
#وصف_ڪريو AT91C_CAN_MB3_MDH          ( 0xFFFD0278 ) /* (CAN_MB3) MailBox Data High Register */
/* ========== Register definition for CAN_MB4 peripheral ========== */
#وصف_ڪريو AT91C_CAN_MB4_MID          ( 0xFFFD0288 ) /* (CAN_MB4) MailBox ID Register */
#وصف_ڪريو AT91C_CAN_MB4_MMR          ( 0xFFFD0280 ) /* (CAN_MB4) MailBox Mode Register */
#وصف_ڪريو AT91C_CAN_MB4_MDH          ( 0xFFFD0298 ) /* (CAN_MB4) MailBox Data High Register */
#وصف_ڪريو AT91C_CAN_MB4_MFID         ( 0xFFFD028C ) /* (CAN_MB4) MailBox Family ID Register */
#وصف_ڪريو AT91C_CAN_MB4_MSR          ( 0xFFFD0290 ) /* (CAN_MB4) MailBox Status Register */
#وصف_ڪريو AT91C_CAN_MB4_MCR          ( 0xFFFD029C ) /* (CAN_MB4) MailBox Control Register */
#وصف_ڪريو AT91C_CAN_MB4_MDL          ( 0xFFFD0294 ) /* (CAN_MB4) MailBox Data Low Register */
#وصف_ڪريو AT91C_CAN_MB4_MAM          ( 0xFFFD0284 ) /* (CAN_MB4) MailBox Acceptance Mask Register */
/* ========== Register definition for CAN_MB5 peripheral ========== */
#وصف_ڪريو AT91C_CAN_MB5_MSR          ( 0xFFFD02B0 ) /* (CAN_MB5) MailBox Status Register */
#وصف_ڪريو AT91C_CAN_MB5_MCR          ( 0xFFFD02BC ) /* (CAN_MB5) MailBox Control Register */
#وصف_ڪريو AT91C_CAN_MB5_MFID         ( 0xFFFD02AC ) /* (CAN_MB5) MailBox Family ID Register */
#وصف_ڪريو AT91C_CAN_MB5_MDH          ( 0xFFFD02B8 ) /* (CAN_MB5) MailBox Data High Register */
#وصف_ڪريو AT91C_CAN_MB5_MID          ( 0xFFFD02A8 ) /* (CAN_MB5) MailBox ID Register */
#وصف_ڪريو AT91C_CAN_MB5_MMR          ( 0xFFFD02A0 ) /* (CAN_MB5) MailBox Mode Register */
#وصف_ڪريو AT91C_CAN_MB5_MDL          ( 0xFFFD02B4 ) /* (CAN_MB5) MailBox Data Low Register */
#وصف_ڪريو AT91C_CAN_MB5_MAM          ( 0xFFFD02A4 ) /* (CAN_MB5) MailBox Acceptance Mask Register */
/* ========== Register definition for CAN_MB6 peripheral ========== */
#وصف_ڪريو AT91C_CAN_MB6_MFID         ( 0xFFFD02CC ) /* (CAN_MB6) MailBox Family ID Register */
#وصف_ڪريو AT91C_CAN_MB6_MID          ( 0xFFFD02C8 ) /* (CAN_MB6) MailBox ID Register */
#وصف_ڪريو AT91C_CAN_MB6_MAM          ( 0xFFFD02C4 ) /* (CAN_MB6) MailBox Acceptance Mask Register */
#وصف_ڪريو AT91C_CAN_MB6_MSR          ( 0xFFFD02D0 ) /* (CAN_MB6) MailBox Status Register */
#وصف_ڪريو AT91C_CAN_MB6_MDL          ( 0xFFFD02D4 ) /* (CAN_MB6) MailBox Data Low Register */
#وصف_ڪريو AT91C_CAN_MB6_MCR          ( 0xFFFD02DC ) /* (CAN_MB6) MailBox Control Register */
#وصف_ڪريو AT91C_CAN_MB6_MDH          ( 0xFFFD02D8 ) /* (CAN_MB6) MailBox Data High Register */
#وصف_ڪريو AT91C_CAN_MB6_MMR          ( 0xFFFD02C0 ) /* (CAN_MB6) MailBox Mode Register */
/* ========== Register definition for CAN_MB7 peripheral ========== */
#وصف_ڪريو AT91C_CAN_MB7_MCR          ( 0xFFFD02FC ) /* (CAN_MB7) MailBox Control Register */
#وصف_ڪريو AT91C_CAN_MB7_MDH          ( 0xFFFD02F8 ) /* (CAN_MB7) MailBox Data High Register */
#وصف_ڪريو AT91C_CAN_MB7_MFID         ( 0xFFFD02EC ) /* (CAN_MB7) MailBox Family ID Register */
#وصف_ڪريو AT91C_CAN_MB7_MDL          ( 0xFFFD02F4 ) /* (CAN_MB7) MailBox Data Low Register */
#وصف_ڪريو AT91C_CAN_MB7_MID          ( 0xFFFD02E8 ) /* (CAN_MB7) MailBox ID Register */
#وصف_ڪريو AT91C_CAN_MB7_MMR          ( 0xFFFD02E0 ) /* (CAN_MB7) MailBox Mode Register */
#وصف_ڪريو AT91C_CAN_MB7_MAM          ( 0xFFFD02E4 ) /* (CAN_MB7) MailBox Acceptance Mask Register */
#وصف_ڪريو AT91C_CAN_MB7_MSR          ( 0xFFFD02F0 ) /* (CAN_MB7) MailBox Status Register */
/* ========== Register definition for CAN peripheral ========== */
#وصف_ڪريو AT91C_CAN_TCR              ( 0xFFFD0024 ) /* (CAN) Transfer Command Register */
#وصف_ڪريو AT91C_CAN_IMR              ( 0xFFFD000C ) /* (CAN) Interrupt Mask Register */
#وصف_ڪريو AT91C_CAN_IER              ( 0xFFFD0004 ) /* (CAN) Interrupt Enable Register */
#وصف_ڪريو AT91C_CAN_ECR              ( 0xFFFD0020 ) /* (CAN) Error Counter Register */
#وصف_ڪريو AT91C_CAN_TIMESTP          ( 0xFFFD001C ) /* (CAN) Time Stamp Register */
#وصف_ڪريو AT91C_CAN_MR               ( 0xFFFD0000 ) /* (CAN) Mode Register */
#وصف_ڪريو AT91C_CAN_IDR              ( 0xFFFD0008 ) /* (CAN) Interrupt Disable Register */
#وصف_ڪريو AT91C_CAN_ACR              ( 0xFFFD0028 ) /* (CAN) Abort Command Register */
#وصف_ڪريو AT91C_CAN_TIM              ( 0xFFFD0018 ) /* (CAN) Timer Register */
#وصف_ڪريو AT91C_CAN_SR               ( 0xFFFD0010 ) /* (CAN) Status Register */
#وصف_ڪريو AT91C_CAN_BR               ( 0xFFFD0014 ) /* (CAN) Baudrate Register */
#وصف_ڪريو AT91C_CAN_VR               ( 0xFFFD00FC ) /* (CAN) Version Register */
/* ========== Register definition for EMAC peripheral ========== */
#وصف_ڪريو AT91C_EMAC_ISR             ( 0xFFFDC024 ) /* (EMAC) Interrupt Status Register */
#وصف_ڪريو AT91C_EMAC_SA4H            ( 0xFFFDC0B4 ) /* (EMAC) Specific Address 4 Top, Last 2 bytes */
#وصف_ڪريو AT91C_EMAC_SA1L            ( 0xFFFDC098 ) /* (EMAC) Specific Address 1 Bottom, First 4 bytes */
#وصف_ڪريو AT91C_EMAC_ELE             ( 0xFFFDC078 ) /* (EMAC) Excessive Length Errors Register */
#وصف_ڪريو AT91C_EMAC_LCOL            ( 0xFFFDC05C ) /* (EMAC) Late Collision Register */
#وصف_ڪريو AT91C_EMAC_RLE             ( 0xFFFDC088 ) /* (EMAC) Receive Length Field Mismatch Register */
#وصف_ڪريو AT91C_EMAC_WOL             ( 0xFFFDC0C4 ) /* (EMAC) Wake On LAN Register */
#وصف_ڪريو AT91C_EMAC_DTF             ( 0xFFFDC058 ) /* (EMAC) Deferred Transmission Frame Register */
#وصف_ڪريو AT91C_EMAC_TUND            ( 0xFFFDC064 ) /* (EMAC) Transmit Underrun Error Register */
#وصف_ڪريو AT91C_EMAC_NCR             ( 0xFFFDC000 ) /* (EMAC) Network Control Register */
#وصف_ڪريو AT91C_EMAC_SA4L            ( 0xFFFDC0B0 ) /* (EMAC) Specific Address 4 Bottom, First 4 bytes */
#وصف_ڪريو AT91C_EMAC_RSR             ( 0xFFFDC020 ) /* (EMAC) Receive Status Register */
#وصف_ڪريو AT91C_EMAC_SA3L            ( 0xFFFDC0A8 ) /* (EMAC) Specific Address 3 Bottom, First 4 bytes */
#وصف_ڪريو AT91C_EMAC_TSR             ( 0xFFFDC014 ) /* (EMAC) Transmit Status Register */
#وصف_ڪريو AT91C_EMAC_IDR             ( 0xFFFDC02C ) /* (EMAC) Interrupt Disable Register */
#وصف_ڪريو AT91C_EMAC_RSE             ( 0xFFFDC074 ) /* (EMAC) Receive Symbol Errors Register */
#وصف_ڪريو AT91C_EMAC_ECOL            ( 0xFFFDC060 ) /* (EMAC) Excessive Collision Register */
#وصف_ڪريو AT91C_EMAC_TID             ( 0xFFFDC0B8 ) /* (EMAC) Type ID Checking Register */
#وصف_ڪريو AT91C_EMAC_HRB             ( 0xFFFDC090 ) /* (EMAC) Hash Address Bottom[31:0] */
#وصف_ڪريو AT91C_EMAC_TBQP            ( 0xFFFDC01C ) /* (EMAC) Transmit Buffer Queue Pointer */
#وصف_ڪريو AT91C_EMAC_USRIO           ( 0xFFFDC0C0 ) /* (EMAC) USER Input/Output Register */
#وصف_ڪريو AT91C_EMAC_PTR             ( 0xFFFDC038 ) /* (EMAC) Pause Time Register */
#وصف_ڪريو AT91C_EMAC_SA2H            ( 0xFFFDC0A4 ) /* (EMAC) Specific Address 2 Top, Last 2 bytes */
#وصف_ڪريو AT91C_EMAC_ROV             ( 0xFFFDC070 ) /* (EMAC) Receive Overrun Errors Register */
#وصف_ڪريو AT91C_EMAC_ALE             ( 0xFFFDC054 ) /* (EMAC) Alignment Error Register */
#وصف_ڪريو AT91C_EMAC_RJA             ( 0xFFFDC07C ) /* (EMAC) Receive Jabbers Register */
#وصف_ڪريو AT91C_EMAC_RBQP            ( 0xFFFDC018 ) /* (EMAC) Receive Buffer Queue Pointer */
#وصف_ڪريو AT91C_EMAC_TPF             ( 0xFFFDC08C ) /* (EMAC) Transmitted Pause Frames Register */
#وصف_ڪريو AT91C_EMAC_NCFGR           ( 0xFFFDC004 ) /* (EMAC) Network Configuration Register */
#وصف_ڪريو AT91C_EMAC_HRT             ( 0xFFFDC094 ) /* (EMAC) Hash Address Top[63:32] */
#وصف_ڪريو AT91C_EMAC_USF             ( 0xFFFDC080 ) /* (EMAC) Undersize Frames Register */
#وصف_ڪريو AT91C_EMAC_FCSE            ( 0xFFFDC050 ) /* (EMAC) Frame Check Sequence Error Register */
#وصف_ڪريو AT91C_EMAC_TPQ             ( 0xFFFDC0BC ) /* (EMAC) Transmit Pause Quantum Register */
#وصف_ڪريو AT91C_EMAC_MAN             ( 0xFFFDC034 ) /* (EMAC) PHY Maintenance Register */
#وصف_ڪريو AT91C_EMAC_FTO             ( 0xFFFDC040 ) /* (EMAC) Frames Transmitted OK Register */
#وصف_ڪريو AT91C_EMAC_REV             ( 0xFFFDC0FC ) /* (EMAC) Revision Register */
#وصف_ڪريو AT91C_EMAC_IMR             ( 0xFFFDC030 ) /* (EMAC) Interrupt Mask Register */
#وصف_ڪريو AT91C_EMAC_SCF             ( 0xFFFDC044 ) /* (EMAC) Single Collision Frame Register */
#وصف_ڪريو AT91C_EMAC_PFR             ( 0xFFFDC03C ) /* (EMAC) Pause Frames received Register */
#وصف_ڪريو AT91C_EMAC_MCF             ( 0xFFFDC048 ) /* (EMAC) Multiple Collision Frame Register */
#وصف_ڪريو AT91C_EMAC_NSR             ( 0xFFFDC008 ) /* (EMAC) Network Status Register */
#وصف_ڪريو AT91C_EMAC_SA2L            ( 0xFFFDC0A0 ) /* (EMAC) Specific Address 2 Bottom, First 4 bytes */
#وصف_ڪريو AT91C_EMAC_FRO             ( 0xFFFDC04C ) /* (EMAC) Frames Received OK Register */
#وصف_ڪريو AT91C_EMAC_IER             ( 0xFFFDC028 ) /* (EMAC) Interrupt Enable Register */
#وصف_ڪريو AT91C_EMAC_SA1H            ( 0xFFFDC09C ) /* (EMAC) Specific Address 1 Top, Last 2 bytes */
#وصف_ڪريو AT91C_EMAC_CSE             ( 0xFFFDC068 ) /* (EMAC) Carrier Sense Error Register */
#وصف_ڪريو AT91C_EMAC_SA3H            ( 0xFFFDC0AC ) /* (EMAC) Specific Address 3 Top, Last 2 bytes */
#وصف_ڪريو AT91C_EMAC_RRE             ( 0xFFFDC06C ) /* (EMAC) Receive Resource Error Register */
#وصف_ڪريو AT91C_EMAC_STE             ( 0xFFFDC084 ) /* (EMAC) SQE Test Error Register */
/* ========== Register definition for PDC_ADC peripheral ========== */
#وصف_ڪريو AT91C_ADC_PTSR             ( 0xFFFD8124 ) /* (PDC_ADC) PDC Transfer Status Register */
#وصف_ڪريو AT91C_ADC_PTCR             ( 0xFFFD8120 ) /* (PDC_ADC) PDC Transfer Control Register */
#وصف_ڪريو AT91C_ADC_TNPR             ( 0xFFFD8118 ) /* (PDC_ADC) Transmit Next Pointer Register */
#وصف_ڪريو AT91C_ADC_TNCR             ( 0xFFFD811C ) /* (PDC_ADC) Transmit Next Counter Register */
#وصف_ڪريو AT91C_ADC_RNPR             ( 0xFFFD8110 ) /* (PDC_ADC) Receive Next Pointer Register */
#وصف_ڪريو AT91C_ADC_RNCR             ( 0xFFFD8114 ) /* (PDC_ADC) Receive Next Counter Register */
#وصف_ڪريو AT91C_ADC_RPR              ( 0xFFFD8100 ) /* (PDC_ADC) Receive Pointer Register */
#وصف_ڪريو AT91C_ADC_TCR              ( 0xFFFD810C ) /* (PDC_ADC) Transmit Counter Register */
#وصف_ڪريو AT91C_ADC_TPR              ( 0xFFFD8108 ) /* (PDC_ADC) Transmit Pointer Register */
#وصف_ڪريو AT91C_ADC_RCR              ( 0xFFFD8104 ) /* (PDC_ADC) Receive Counter Register */
/* ========== Register definition for ADC peripheral ========== */
#وصف_ڪريو AT91C_ADC_CDR2             ( 0xFFFD8038 ) /* (ADC) ADC Channel Data Register 2 */
#وصف_ڪريو AT91C_ADC_CDR3             ( 0xFFFD803C ) /* (ADC) ADC Channel Data Register 3 */
#وصف_ڪريو AT91C_ADC_CDR0             ( 0xFFFD8030 ) /* (ADC) ADC Channel Data Register 0 */
#وصف_ڪريو AT91C_ADC_CDR5             ( 0xFFFD8044 ) /* (ADC) ADC Channel Data Register 5 */
#وصف_ڪريو AT91C_ADC_CHDR             ( 0xFFFD8014 ) /* (ADC) ADC Channel Disable Register */
#وصف_ڪريو AT91C_ADC_SR               ( 0xFFFD801C ) /* (ADC) ADC Status Register */
#وصف_ڪريو AT91C_ADC_CDR4             ( 0xFFFD8040 ) /* (ADC) ADC Channel Data Register 4 */
#وصف_ڪريو AT91C_ADC_CDR1             ( 0xFFFD8034 ) /* (ADC) ADC Channel Data Register 1 */
#وصف_ڪريو AT91C_ADC_LCDR             ( 0xFFFD8020 ) /* (ADC) ADC Last Converted Data Register */
#وصف_ڪريو AT91C_ADC_IDR              ( 0xFFFD8028 ) /* (ADC) ADC Interrupt Disable Register */
#وصف_ڪريو AT91C_ADC_CR               ( 0xFFFD8000 ) /* (ADC) ADC Control Register */
#وصف_ڪريو AT91C_ADC_CDR7             ( 0xFFFD804C ) /* (ADC) ADC Channel Data Register 7 */
#وصف_ڪريو AT91C_ADC_CDR6             ( 0xFFFD8048 ) /* (ADC) ADC Channel Data Register 6 */
#وصف_ڪريو AT91C_ADC_IER              ( 0xFFFD8024 ) /* (ADC) ADC Interrupt Enable Register */
#وصف_ڪريو AT91C_ADC_CHER             ( 0xFFFD8010 ) /* (ADC) ADC Channel Enable Register */
#وصف_ڪريو AT91C_ADC_CHSR             ( 0xFFFD8018 ) /* (ADC) ADC Channel Status Register */
#وصف_ڪريو AT91C_ADC_MR               ( 0xFFFD8004 ) /* (ADC) ADC Mode Register */
#وصف_ڪريو AT91C_ADC_IMR              ( 0xFFFD802C ) /* (ADC) ADC Interrupt Mask Register */
/* ========== Register definition for PDC_AES peripheral ========== */
#وصف_ڪريو AT91C_AES_TPR              ( 0xFFFA4108 ) /* (PDC_AES) Transmit Pointer Register */
#وصف_ڪريو AT91C_AES_PTCR             ( 0xFFFA4120 ) /* (PDC_AES) PDC Transfer Control Register */
#وصف_ڪريو AT91C_AES_RNPR             ( 0xFFFA4110 ) /* (PDC_AES) Receive Next Pointer Register */
#وصف_ڪريو AT91C_AES_TNCR             ( 0xFFFA411C ) /* (PDC_AES) Transmit Next Counter Register */
#وصف_ڪريو AT91C_AES_TCR              ( 0xFFFA410C ) /* (PDC_AES) Transmit Counter Register */
#وصف_ڪريو AT91C_AES_RCR              ( 0xFFFA4104 ) /* (PDC_AES) Receive Counter Register */
#وصف_ڪريو AT91C_AES_RNCR             ( 0xFFFA4114 ) /* (PDC_AES) Receive Next Counter Register */
#وصف_ڪريو AT91C_AES_TNPR             ( 0xFFFA4118 ) /* (PDC_AES) Transmit Next Pointer Register */
#وصف_ڪريو AT91C_AES_RPR              ( 0xFFFA4100 ) /* (PDC_AES) Receive Pointer Register */
#وصف_ڪريو AT91C_AES_PTSR             ( 0xFFFA4124 ) /* (PDC_AES) PDC Transfer Status Register */
/* ========== Register definition for AES peripheral ========== */
#وصف_ڪريو AT91C_AES_IVxR             ( 0xFFFA4060 ) /* (AES) Initialization Vector x Register */
#وصف_ڪريو AT91C_AES_MR               ( 0xFFFA4004 ) /* (AES) Mode Register */
#وصف_ڪريو AT91C_AES_VR               ( 0xFFFA40FC ) /* (AES) AES Version Register */
#وصف_ڪريو AT91C_AES_ODATAxR          ( 0xFFFA4050 ) /* (AES) Output Data x Register */
#وصف_ڪريو AT91C_AES_IDATAxR          ( 0xFFFA4040 ) /* (AES) Input Data x Register */
#وصف_ڪريو AT91C_AES_CR               ( 0xFFFA4000 ) /* (AES) Control Register */
#وصف_ڪريو AT91C_AES_IDR              ( 0xFFFA4014 ) /* (AES) Interrupt Disable Register */
#وصف_ڪريو AT91C_AES_IMR              ( 0xFFFA4018 ) /* (AES) Interrupt Mask Register */
#وصف_ڪريو AT91C_AES_IER              ( 0xFFFA4010 ) /* (AES) Interrupt Enable Register */
#وصف_ڪريو AT91C_AES_KEYWxR           ( 0xFFFA4020 ) /* (AES) Key Word x Register */
#وصف_ڪريو AT91C_AES_ISR              ( 0xFFFA401C ) /* (AES) Interrupt Status Register */
/* ========== Register definition for PDC_TDES peripheral ========== */
#وصف_ڪريو AT91C_TDES_RNCR            ( 0xFFFA8114 ) /* (PDC_TDES) Receive Next Counter Register */
#وصف_ڪريو AT91C_TDES_TCR             ( 0xFFFA810C ) /* (PDC_TDES) Transmit Counter Register */
#وصف_ڪريو AT91C_TDES_RCR             ( 0xFFFA8104 ) /* (PDC_TDES) Receive Counter Register */
#وصف_ڪريو AT91C_TDES_TNPR            ( 0xFFFA8118 ) /* (PDC_TDES) Transmit Next Pointer Register */
#وصف_ڪريو AT91C_TDES_RNPR            ( 0xFFFA8110 ) /* (PDC_TDES) Receive Next Pointer Register */
#وصف_ڪريو AT91C_TDES_RPR             ( 0xFFFA8100 ) /* (PDC_TDES) Receive Pointer Register */
#وصف_ڪريو AT91C_TDES_TNCR            ( 0xFFFA811C ) /* (PDC_TDES) Transmit Next Counter Register */
#وصف_ڪريو AT91C_TDES_TPR             ( 0xFFFA8108 ) /* (PDC_TDES) Transmit Pointer Register */
#وصف_ڪريو AT91C_TDES_PTSR            ( 0xFFFA8124 ) /* (PDC_TDES) PDC Transfer Status Register */
#وصف_ڪريو AT91C_TDES_PTCR            ( 0xFFFA8120 ) /* (PDC_TDES) PDC Transfer Control Register */
/* ========== Register definition for TDES peripheral ========== */
#وصف_ڪريو AT91C_TDES_KEY2WxR         ( 0xFFFA8028 ) /* (TDES) Key 2 Word x Register */
#وصف_ڪريو AT91C_TDES_KEY3WxR         ( 0xFFFA8030 ) /* (TDES) Key 3 Word x Register */
#وصف_ڪريو AT91C_TDES_IDR             ( 0xFFFA8014 ) /* (TDES) Interrupt Disable Register */
#وصف_ڪريو AT91C_TDES_VR              ( 0xFFFA80FC ) /* (TDES) TDES Version Register */
#وصف_ڪريو AT91C_TDES_IVxR            ( 0xFFFA8060 ) /* (TDES) Initialization Vector x Register */
#وصف_ڪريو AT91C_TDES_ODATAxR         ( 0xFFFA8050 ) /* (TDES) Output Data x Register */
#وصف_ڪريو AT91C_TDES_IMR             ( 0xFFFA8018 ) /* (TDES) Interrupt Mask Register */
#وصف_ڪريو AT91C_TDES_MR              ( 0xFFFA8004 ) /* (TDES) Mode Register */
#وصف_ڪريو AT91C_TDES_CR              ( 0xFFFA8000 ) /* (TDES) Control Register */
#وصف_ڪريو AT91C_TDES_IER             ( 0xFFFA8010 ) /* (TDES) Interrupt Enable Register */
#وصف_ڪريو AT91C_TDES_ISR             ( 0xFFFA801C ) /* (TDES) Interrupt Status Register */
#وصف_ڪريو AT91C_TDES_IDATAxR         ( 0xFFFA8040 ) /* (TDES) Input Data x Register */
#وصف_ڪريو AT91C_TDES_KEY1WxR         ( 0xFFFA8020 ) /* (TDES) Key 1 Word x Register */

/* ***************************************************************************** */
/*               PIO DEFINITIONS FOR AT91SAM7X128 */
/* ***************************************************************************** */
#وصف_ڪريو AT91C_PIO_PA0             ( 1 << 0 )         /* Pin Controlled by PA0 */
#وصف_ڪريو AT91C_PA0_RXD0            ( AT91C_PIO_PA0 )  /*  USART 0 Receive Data */
#وصف_ڪريو AT91C_PIO_PA1             ( 1 << 1 )         /* Pin Controlled by PA1 */
#وصف_ڪريو AT91C_PA1_TXD0            ( AT91C_PIO_PA1 )  /*  USART 0 Transmit Data */
#وصف_ڪريو AT91C_PIO_PA10            ( 1 << 10 )        /* Pin Controlled by PA10 */
#وصف_ڪريو AT91C_PA10_TWD            ( AT91C_PIO_PA10 ) /*  TWI Two-wire Serial Data */
#وصف_ڪريو AT91C_PIO_PA11            ( 1 << 11 )        /* Pin Controlled by PA11 */
#وصف_ڪريو AT91C_PA11_TWCK           ( AT91C_PIO_PA11 ) /*  TWI Two-wire Serial Clock */
#وصف_ڪريو AT91C_PIO_PA12            ( 1 << 12 )        /* Pin Controlled by PA12 */
#وصف_ڪريو AT91C_PA12_NPCS00         ( AT91C_PIO_PA12 ) /*  SPI 0 Peripheral Chip Select 0 */
#وصف_ڪريو AT91C_PIO_PA13            ( 1 << 13 )        /* Pin Controlled by PA13 */
#وصف_ڪريو AT91C_PA13_NPCS01         ( AT91C_PIO_PA13 ) /*  SPI 0 Peripheral Chip Select 1 */
#وصف_ڪريو AT91C_PA13_PCK1           ( AT91C_PIO_PA13 ) /*  PMC Programmable Clock Output 1 */
#وصف_ڪريو AT91C_PIO_PA14            ( 1 << 14 )        /* Pin Controlled by PA14 */
#وصف_ڪريو AT91C_PA14_NPCS02         ( AT91C_PIO_PA14 ) /*  SPI 0 Peripheral Chip Select 2 */
#وصف_ڪريو AT91C_PA14_IRQ1           ( AT91C_PIO_PA14 ) /*  External Interrupt 1 */
#وصف_ڪريو AT91C_PIO_PA15            ( 1 << 15 )        /* Pin Controlled by PA15 */
#وصف_ڪريو AT91C_PA15_NPCS03         ( AT91C_PIO_PA15 ) /*  SPI 0 Peripheral Chip Select 3 */
#وصف_ڪريو AT91C_PA15_TCLK2          ( AT91C_PIO_PA15 ) /*  Timer Counter 2 external clock input */
#وصف_ڪريو AT91C_PIO_PA16            ( 1 << 16 )        /* Pin Controlled by PA16 */
#وصف_ڪريو AT91C_PA16_MISO0          ( AT91C_PIO_PA16 ) /*  SPI 0 Master In Slave */
#وصف_ڪريو AT91C_PIO_PA17            ( 1 << 17 )        /* Pin Controlled by PA17 */
#وصف_ڪريو AT91C_PA17_MOSI0          ( AT91C_PIO_PA17 ) /*  SPI 0 Master Out Slave */
#وصف_ڪريو AT91C_PIO_PA18            ( 1 << 18 )        /* Pin Controlled by PA18 */
#وصف_ڪريو AT91C_PA18_SPCK0          ( AT91C_PIO_PA18 ) /*  SPI 0 Serial Clock */
#وصف_ڪريو AT91C_PIO_PA19            ( 1 << 19 )        /* Pin Controlled by PA19 */
#وصف_ڪريو AT91C_PA19_CANRX          ( AT91C_PIO_PA19 ) /*  CAN Receive */
#وصف_ڪريو AT91C_PIO_PA2             ( 1 << 2 )         /* Pin Controlled by PA2 */
#وصف_ڪريو AT91C_PA2_SCK0            ( AT91C_PIO_PA2 )  /*  USART 0 Serial Clock */
#وصف_ڪريو AT91C_PA2_NPCS11          ( AT91C_PIO_PA2 )  /*  SPI 1 Peripheral Chip Select 1 */
#وصف_ڪريو AT91C_PIO_PA20            ( 1 << 20 )        /* Pin Controlled by PA20 */
#وصف_ڪريو AT91C_PA20_CANTX          ( AT91C_PIO_PA20 ) /*  CAN Transmit */
#وصف_ڪريو AT91C_PIO_PA21            ( 1 << 21 )        /* Pin Controlled by PA21 */
#وصف_ڪريو AT91C_PA21_TF             ( AT91C_PIO_PA21 ) /*  SSC Transmit Frame Sync */
#وصف_ڪريو AT91C_PA21_NPCS10         ( AT91C_PIO_PA21 ) /*  SPI 1 Peripheral Chip Select 0 */
#وصف_ڪريو AT91C_PIO_PA22            ( 1 << 22 )        /* Pin Controlled by PA22 */
#وصف_ڪريو AT91C_PA22_TK             ( AT91C_PIO_PA22 ) /*  SSC Transmit Clock */
#وصف_ڪريو AT91C_PA22_SPCK1          ( AT91C_PIO_PA22 ) /*  SPI 1 Serial Clock */
#وصف_ڪريو AT91C_PIO_PA23            ( 1 << 23 )        /* Pin Controlled by PA23 */
#وصف_ڪريو AT91C_PA23_TD             ( AT91C_PIO_PA23 ) /*  SSC Transmit data */
#وصف_ڪريو AT91C_PA23_MOSI1          ( AT91C_PIO_PA23 ) /*  SPI 1 Master Out Slave */
#وصف_ڪريو AT91C_PIO_PA24            ( 1 << 24 )        /* Pin Controlled by PA24 */
#وصف_ڪريو AT91C_PA24_RD             ( AT91C_PIO_PA24 ) /*  SSC Receive Data */
#وصف_ڪريو AT91C_PA24_MISO1          ( AT91C_PIO_PA24 ) /*  SPI 1 Master In Slave */
#وصف_ڪريو AT91C_PIO_PA25            ( 1 << 25 )        /* Pin Controlled by PA25 */
#وصف_ڪريو AT91C_PA25_RK             ( AT91C_PIO_PA25 ) /*  SSC Receive Clock */
#وصف_ڪريو AT91C_PA25_NPCS11         ( AT91C_PIO_PA25 ) /*  SPI 1 Peripheral Chip Select 1 */
#وصف_ڪريو AT91C_PIO_PA26            ( 1 << 26 )        /* Pin Controlled by PA26 */
#وصف_ڪريو AT91C_PA26_RF             ( AT91C_PIO_PA26 ) /*  SSC Receive Frame Sync */
#وصف_ڪريو AT91C_PA26_NPCS12         ( AT91C_PIO_PA26 ) /*  SPI 1 Peripheral Chip Select 2 */
#وصف_ڪريو AT91C_PIO_PA27            ( 1 << 27 )        /* Pin Controlled by PA27 */
#وصف_ڪريو AT91C_PA27_DRXD           ( AT91C_PIO_PA27 ) /*  DBGU Debug Receive Data */
#وصف_ڪريو AT91C_PA27_PCK3           ( AT91C_PIO_PA27 ) /*  PMC Programmable Clock Output 3 */
#وصف_ڪريو AT91C_PIO_PA28            ( 1 << 28 )        /* Pin Controlled by PA28 */
#وصف_ڪريو AT91C_PA28_DTXD           ( AT91C_PIO_PA28 ) /*  DBGU Debug Transmit Data */
#وصف_ڪريو AT91C_PIO_PA29            ( 1 << 29 )        /* Pin Controlled by PA29 */
#وصف_ڪريو AT91C_PA29_FIQ            ( AT91C_PIO_PA29 ) /*  AIC Fast Interrupt Input */
#وصف_ڪريو AT91C_PA29_NPCS13         ( AT91C_PIO_PA29 ) /*  SPI 1 Peripheral Chip Select 3 */
#وصف_ڪريو AT91C_PIO_PA3             ( 1 << 3 )         /* Pin Controlled by PA3 */
#وصف_ڪريو AT91C_PA3_RTS0            ( AT91C_PIO_PA3 )  /*  USART 0 Ready To Send */
#وصف_ڪريو AT91C_PA3_NPCS12          ( AT91C_PIO_PA3 )  /*  SPI 1 Peripheral Chip Select 2 */
#وصف_ڪريو AT91C_PIO_PA30            ( 1 << 30 )        /* Pin Controlled by PA30 */
#وصف_ڪريو AT91C_PA30_IRQ0           ( AT91C_PIO_PA30 ) /*  External Interrupt 0 */
#وصف_ڪريو AT91C_PA30_PCK2           ( AT91C_PIO_PA30 ) /*  PMC Programmable Clock Output 2 */
#وصف_ڪريو AT91C_PIO_PA4             ( 1 << 4 )         /* Pin Controlled by PA4 */
#وصف_ڪريو AT91C_PA4_CTS0            ( AT91C_PIO_PA4 )  /*  USART 0 Clear To Send */
#وصف_ڪريو AT91C_PA4_NPCS13          ( AT91C_PIO_PA4 )  /*  SPI 1 Peripheral Chip Select 3 */
#وصف_ڪريو AT91C_PIO_PA5             ( 1 << 5 )         /* Pin Controlled by PA5 */
#وصف_ڪريو AT91C_PA5_RXD1            ( AT91C_PIO_PA5 )  /*  USART 1 Receive Data */
#وصف_ڪريو AT91C_PIO_PA6             ( 1 << 6 )         /* Pin Controlled by PA6 */
#وصف_ڪريو AT91C_PA6_TXD1            ( AT91C_PIO_PA6 )  /*  USART 1 Transmit Data */
#وصف_ڪريو AT91C_PIO_PA7             ( 1 << 7 )         /* Pin Controlled by PA7 */
#وصف_ڪريو AT91C_PA7_SCK1            ( AT91C_PIO_PA7 )  /*  USART 1 Serial Clock */
#وصف_ڪريو AT91C_PA7_NPCS01          ( AT91C_PIO_PA7 )  /*  SPI 0 Peripheral Chip Select 1 */
#وصف_ڪريو AT91C_PIO_PA8             ( 1 << 8 )         /* Pin Controlled by PA8 */
#وصف_ڪريو AT91C_PA8_RTS1            ( AT91C_PIO_PA8 )  /*  USART 1 Ready To Send */
#وصف_ڪريو AT91C_PA8_NPCS02          ( AT91C_PIO_PA8 )  /*  SPI 0 Peripheral Chip Select 2 */
#وصف_ڪريو AT91C_PIO_PA9             ( 1 << 9 )         /* Pin Controlled by PA9 */
#وصف_ڪريو AT91C_PA9_CTS1            ( AT91C_PIO_PA9 )  /*  USART 1 Clear To Send */
#وصف_ڪريو AT91C_PA9_NPCS03          ( AT91C_PIO_PA9 )  /*  SPI 0 Peripheral Chip Select 3 */
#وصف_ڪريو AT91C_PIO_PB0             ( 1 << 0 )         /* Pin Controlled by PB0 */
#وصف_ڪريو AT91C_PB0_ETXCK_EREFCK    ( AT91C_PIO_PB0 )  /*  Ethernet MAC Transmit Clock/Reference Clock */
#وصف_ڪريو AT91C_PB0_PCK0            ( AT91C_PIO_PB0 )  /*  PMC Programmable Clock Output 0 */
#وصف_ڪريو AT91C_PIO_PB1             ( 1 << 1 )         /* Pin Controlled by PB1 */
#وصف_ڪريو AT91C_PB1_ETXEN           ( AT91C_PIO_PB1 )  /*  Ethernet MAC Transmit Enable */
#وصف_ڪريو AT91C_PIO_PB10            ( 1 << 10 )        /* Pin Controlled by PB10 */
#وصف_ڪريو AT91C_PB10_ETX2           ( AT91C_PIO_PB10 ) /*  Ethernet MAC Transmit Data 2 */
#وصف_ڪريو AT91C_PB10_NPCS11         ( AT91C_PIO_PB10 ) /*  SPI 1 Peripheral Chip Select 1 */
#وصف_ڪريو AT91C_PIO_PB11            ( 1 << 11 )        /* Pin Controlled by PB11 */
#وصف_ڪريو AT91C_PB11_ETX3           ( AT91C_PIO_PB11 ) /*  Ethernet MAC Transmit Data 3 */
#وصف_ڪريو AT91C_PB11_NPCS12         ( AT91C_PIO_PB11 ) /*  SPI 1 Peripheral Chip Select 2 */
#وصف_ڪريو AT91C_PIO_PB12            ( 1 << 12 )        /* Pin Controlled by PB12 */
#وصف_ڪريو AT91C_PB12_ETXER          ( AT91C_PIO_PB12 ) /*  Ethernet MAC Transmit Coding Error */
#وصف_ڪريو AT91C_PB12_TCLK0          ( AT91C_PIO_PB12 ) /*  Timer Counter 0 external clock input */
#وصف_ڪريو AT91C_PIO_PB13            ( 1 << 13 )        /* Pin Controlled by PB13 */
#وصف_ڪريو AT91C_PB13_ERX2           ( AT91C_PIO_PB13 ) /*  Ethernet MAC Receive Data 2 */
#وصف_ڪريو AT91C_PB13_NPCS01         ( AT91C_PIO_PB13 ) /*  SPI 0 Peripheral Chip Select 1 */
#وصف_ڪريو AT91C_PIO_PB14            ( 1 << 14 )        /* Pin Controlled by PB14 */
#وصف_ڪريو AT91C_PB14_ERX3           ( AT91C_PIO_PB14 ) /*  Ethernet MAC Receive Data 3 */
#وصف_ڪريو AT91C_PB14_NPCS02         ( AT91C_PIO_PB14 ) /*  SPI 0 Peripheral Chip Select 2 */
#وصف_ڪريو AT91C_PIO_PB15            ( 1 << 15 )        /* Pin Controlled by PB15 */
#وصف_ڪريو AT91C_PB15_ERXDV          ( AT91C_PIO_PB15 ) /*  Ethernet MAC Receive Data Valid */
#وصف_ڪريو AT91C_PIO_PB16            ( 1 << 16 )        /* Pin Controlled by PB16 */
#وصف_ڪريو AT91C_PB16_ECOL           ( AT91C_PIO_PB16 ) /*  Ethernet MAC Collision Detected */
#وصف_ڪريو AT91C_PB16_NPCS13         ( AT91C_PIO_PB16 ) /*  SPI 1 Peripheral Chip Select 3 */
#وصف_ڪريو AT91C_PIO_PB17            ( 1 << 17 )        /* Pin Controlled by PB17 */
#وصف_ڪريو AT91C_PB17_ERXCK          ( AT91C_PIO_PB17 ) /*  Ethernet MAC Receive Clock */
#وصف_ڪريو AT91C_PB17_NPCS03         ( AT91C_PIO_PB17 ) /*  SPI 0 Peripheral Chip Select 3 */
#وصف_ڪريو AT91C_PIO_PB18            ( 1 << 18 )        /* Pin Controlled by PB18 */
#وصف_ڪريو AT91C_PB18_EF100          ( AT91C_PIO_PB18 ) /*  Ethernet MAC Force 100 Mbits/sec */
#وصف_ڪريو AT91C_PB18_ADTRG          ( AT91C_PIO_PB18 ) /*  ADC External Trigger */
#وصف_ڪريو AT91C_PIO_PB19            ( 1 << 19 )        /* Pin Controlled by PB19 */
#وصف_ڪريو AT91C_PB19_PWM0           ( AT91C_PIO_PB19 ) /*  PWM Channel 0 */
#وصف_ڪريو AT91C_PB19_TCLK1          ( AT91C_PIO_PB19 ) /*  Timer Counter 1 external clock input */
#وصف_ڪريو AT91C_PIO_PB2             ( 1 << 2 )         /* Pin Controlled by PB2 */
#وصف_ڪريو AT91C_PB2_ETX0            ( AT91C_PIO_PB2 )  /*  Ethernet MAC Transmit Data 0 */
#وصف_ڪريو AT91C_PIO_PB20            ( 1 << 20 )        /* Pin Controlled by PB20 */
#وصف_ڪريو AT91C_PB20_PWM1           ( AT91C_PIO_PB20 ) /*  PWM Channel 1 */
#وصف_ڪريو AT91C_PB20_PCK0           ( AT91C_PIO_PB20 ) /*  PMC Programmable Clock Output 0 */
#وصف_ڪريو AT91C_PIO_PB21            ( 1 << 21 )        /* Pin Controlled by PB21 */
#وصف_ڪريو AT91C_PB21_PWM2           ( AT91C_PIO_PB21 ) /*  PWM Channel 2 */
#وصف_ڪريو AT91C_PB21_PCK1           ( AT91C_PIO_PB21 ) /*  PMC Programmable Clock Output 1 */
#وصف_ڪريو AT91C_PIO_PB22            ( 1 << 22 )        /* Pin Controlled by PB22 */
#وصف_ڪريو AT91C_PB22_PWM3           ( AT91C_PIO_PB22 ) /*  PWM Channel 3 */
#وصف_ڪريو AT91C_PB22_PCK2           ( AT91C_PIO_PB22 ) /*  PMC Programmable Clock Output 2 */
#وصف_ڪريو AT91C_PIO_PB23            ( 1 << 23 )        /* Pin Controlled by PB23 */
#وصف_ڪريو AT91C_PB23_TIOA0          ( AT91C_PIO_PB23 ) /*  Timer Counter 0 Multipurpose Timer I/O Pin A */
#وصف_ڪريو AT91C_PB23_DCD1           ( AT91C_PIO_PB23 ) /*  USART 1 Data Carrier Detect */
#وصف_ڪريو AT91C_PIO_PB24            ( 1 << 24 )        /* Pin Controlled by PB24 */
#وصف_ڪريو AT91C_PB24_TIOB0          ( AT91C_PIO_PB24 ) /*  Timer Counter 0 Multipurpose Timer I/O Pin B */
#وصف_ڪريو AT91C_PB24_DSR1           ( AT91C_PIO_PB24 ) /*  USART 1 Data Set ready */
#وصف_ڪريو AT91C_PIO_PB25            ( 1 << 25 )        /* Pin Controlled by PB25 */
#وصف_ڪريو AT91C_PB25_TIOA1          ( AT91C_PIO_PB25 ) /*  Timer Counter 1 Multipurpose Timer I/O Pin A */
#وصف_ڪريو AT91C_PB25_DTR1           ( AT91C_PIO_PB25 ) /*  USART 1 Data Terminal ready */
#وصف_ڪريو AT91C_PIO_PB26            ( 1 << 26 )        /* Pin Controlled by PB26 */
#وصف_ڪريو AT91C_PB26_TIOB1          ( AT91C_PIO_PB26 ) /*  Timer Counter 1 Multipurpose Timer I/O Pin B */
#وصف_ڪريو AT91C_PB26_RI1            ( AT91C_PIO_PB26 ) /*  USART 1 Ring Indicator */
#وصف_ڪريو AT91C_PIO_PB27            ( 1 << 27 )        /* Pin Controlled by PB27 */
#وصف_ڪريو AT91C_PB27_TIOA2          ( AT91C_PIO_PB27 ) /*  Timer Counter 2 Multipurpose Timer I/O Pin A */
#وصف_ڪريو AT91C_PB27_PWM0           ( AT91C_PIO_PB27 ) /*  PWM Channel 0 */
#وصف_ڪريو AT91C_PIO_PB28            ( 1 << 28 )        /* Pin Controlled by PB28 */
#وصف_ڪريو AT91C_PB28_TIOB2          ( AT91C_PIO_PB28 ) /*  Timer Counter 2 Multipurpose Timer I/O Pin B */
#وصف_ڪريو AT91C_PB28_PWM1           ( AT91C_PIO_PB28 ) /*  PWM Channel 1 */
#وصف_ڪريو AT91C_PIO_PB29            ( 1 << 29 )        /* Pin Controlled by PB29 */
#وصف_ڪريو AT91C_PB29_PCK1           ( AT91C_PIO_PB29 ) /*  PMC Programmable Clock Output 1 */
#وصف_ڪريو AT91C_PB29_PWM2           ( AT91C_PIO_PB29 ) /*  PWM Channel 2 */
#وصف_ڪريو AT91C_PIO_PB3             ( 1 << 3 )         /* Pin Controlled by PB3 */
#وصف_ڪريو AT91C_PB3_ETX1            ( AT91C_PIO_PB3 )  /*  Ethernet MAC Transmit Data 1 */
#وصف_ڪريو AT91C_PIO_PB30            ( 1 << 30 )        /* Pin Controlled by PB30 */
#وصف_ڪريو AT91C_PB30_PCK2           ( AT91C_PIO_PB30 ) /*  PMC Programmable Clock Output 2 */
#وصف_ڪريو AT91C_PB30_PWM3           ( AT91C_PIO_PB30 ) /*  PWM Channel 3 */
#وصف_ڪريو AT91C_PIO_PB4             ( 1 << 4 )         /* Pin Controlled by PB4 */
#وصف_ڪريو AT91C_PB4_ECRS_ECRSDV     ( AT91C_PIO_PB4 )  /*  Ethernet MAC Carrier Sense/Carrier Sense and Data Valid */
#وصف_ڪريو AT91C_PIO_PB5             ( 1 << 5 )         /* Pin Controlled by PB5 */
#وصف_ڪريو AT91C_PB5_ERX0            ( AT91C_PIO_PB5 )  /*  Ethernet MAC Receive Data 0 */
#وصف_ڪريو AT91C_PIO_PB6             ( 1 << 6 )         /* Pin Controlled by PB6 */
#وصف_ڪريو AT91C_PB6_ERX1            ( AT91C_PIO_PB6 )  /*  Ethernet MAC Receive Data 1 */
#وصف_ڪريو AT91C_PIO_PB7             ( 1 << 7 )         /* Pin Controlled by PB7 */
#وصف_ڪريو AT91C_PB7_ERXER           ( AT91C_PIO_PB7 )  /*  Ethernet MAC Receive Error */
#وصف_ڪريو AT91C_PIO_PB8             ( 1 << 8 )         /* Pin Controlled by PB8 */
#وصف_ڪريو AT91C_PB8_EMDC            ( AT91C_PIO_PB8 )  /*  Ethernet MAC Management Data Clock */
#وصف_ڪريو AT91C_PIO_PB9             ( 1 << 9 )         /* Pin Controlled by PB9 */
#وصف_ڪريو AT91C_PB9_EMDIO           ( AT91C_PIO_PB9 )  /*  Ethernet MAC Management Data Input/Output */

/* ***************************************************************************** */
/*               PERIPHERAL ID DEFINITIONS FOR AT91SAM7X128 */
/* ***************************************************************************** */
#وصف_ڪريو AT91C_ID_FIQ            ( 0 )  /* Advanced Interrupt Controller (FIQ) */
#وصف_ڪريو AT91C_ID_SYS            ( 1 )  /* System Peripheral */
#وصف_ڪريو AT91C_ID_PIOA           ( 2 )  /* Parallel IO Controller A */
#وصف_ڪريو AT91C_ID_PIOB           ( 3 )  /* Parallel IO Controller B */
#وصف_ڪريو AT91C_ID_SPI0           ( 4 )  /* Serial Peripheral Interface 0 */
#وصف_ڪريو AT91C_ID_SPI1           ( 5 )  /* Serial Peripheral Interface 1 */
#وصف_ڪريو AT91C_ID_US0            ( 6 )  /* USART 0 */
#وصف_ڪريو AT91C_ID_US1            ( 7 )  /* USART 1 */
#وصف_ڪريو AT91C_ID_SSC            ( 8 )  /* Serial Synchronous Controller */
#وصف_ڪريو AT91C_ID_TWI            ( 9 )  /* Two-Wire Interface */
#وصف_ڪريو AT91C_ID_PWMC           ( 10 ) /* PWM Controller */
#وصف_ڪريو AT91C_ID_UDP            ( 11 ) /* USB Device Port */
#وصف_ڪريو AT91C_ID_TC0            ( 12 ) /* Timer Counter 0 */
#وصف_ڪريو AT91C_ID_TC1            ( 13 ) /* Timer Counter 1 */
#وصف_ڪريو AT91C_ID_TC2            ( 14 ) /* Timer Counter 2 */
#وصف_ڪريو AT91C_ID_CAN            ( 15 ) /* Control Area Network Controller */
#وصف_ڪريو AT91C_ID_EMAC           ( 16 ) /* Ethernet MAC */
#وصف_ڪريو AT91C_ID_ADC            ( 17 ) /* Analog-to-Digital Converter */
#وصف_ڪريو AT91C_ID_AES            ( 18 ) /* Advanced Encryption Standard 128-bit */
#وصف_ڪريو AT91C_ID_TDES           ( 19 ) /* Triple Data Encryption Standard */
#وصف_ڪريو AT91C_ID_20_Reserved    ( 20 ) /* Reserved */
#وصف_ڪريو AT91C_ID_21_Reserved    ( 21 ) /* Reserved */
#وصف_ڪريو AT91C_ID_22_Reserved    ( 22 ) /* Reserved */
#وصف_ڪريو AT91C_ID_23_Reserved    ( 23 ) /* Reserved */
#وصف_ڪريو AT91C_ID_24_Reserved    ( 24 ) /* Reserved */
#وصف_ڪريو AT91C_ID_25_Reserved    ( 25 ) /* Reserved */
#وصف_ڪريو AT91C_ID_26_Reserved    ( 26 ) /* Reserved */
#وصف_ڪريو AT91C_ID_27_Reserved    ( 27 ) /* Reserved */
#وصف_ڪريو AT91C_ID_28_Reserved    ( 28 ) /* Reserved */
#وصف_ڪريو AT91C_ID_29_Reserved    ( 29 ) /* Reserved */
#وصف_ڪريو AT91C_ID_IRQ0           ( 30 ) /* Advanced Interrupt Controller (IRQ0) */
#وصف_ڪريو AT91C_ID_IRQ1           ( 31 ) /* Advanced Interrupt Controller (IRQ1) */

/* ***************************************************************************** */
/*               BASE ADDRESS DEFINITIONS FOR AT91SAM7X128 */
/* ***************************************************************************** */
#وصف_ڪريو AT91_C_بنياد_SYS         ( 0xFFFFF000 )  /* (SYS) Base Address */
#وصف_ڪريو AT91_C_بنياد_AIC         ( 0xFFFFF000 )  /* (AIC) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_DBGU    ( 0xFFFFF300 )  /* (PDC_DBGU) Base Address */
#وصف_ڪريو AT91_C_بنياد_DBGU        ( 0xFFFFF200 )  /* (DBGU) Base Address */
#وصف_ڪريو AT91_C_بنياد_PIOA        ( 0xFFFFF400 )  /* (PIOA) Base Address */
#وصف_ڪريو AT91_C_بنياد_PIOB        ( 0xFFFFF600 )  /* (PIOB) Base Address */
#وصف_ڪريو AT91_C_بنياد_CKGR        ( 0xFFFFFC20 )  /* (CKGR) Base Address */
#وصف_ڪريو AT91_C_بنياد_PMC         ( 0xFFFFFC00 )  /* (PMC) Base Address */
#وصف_ڪريو AT91_C_بنياد_RSTC        ( 0xFFFFFD00 )  /* (RSTC) Base Address */
#وصف_ڪريو AT91_C_بنياد_RTTC        ( 0xFFFFFD20 )  /* (RTTC) Base Address */
#وصف_ڪريو AT91_C_بنياد_PITC        ( 0xFFFFFD30 )  /* (PITC) Base Address */
#وصف_ڪريو AT91_C_بنياد_WDTC        ( 0xFFFFFD40 )  /* (WDTC) Base Address */
#وصف_ڪريو AT91_C_بنياد_VREG        ( 0xFFFFFD60 )  /* (VREG) Base Address */
#وصف_ڪريو AT91_C_بنياد_MC          ( 0xFFFFFF00 )  /* (MC) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_SPI1    ( 0xFFFE4100 )  /* (PDC_SPI1) Base Address */
#وصف_ڪريو AT91_C_بنياد_SPI1        ( 0xFFFE4000 )  /* (SPI1) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_SPI0    ( 0xFFFE0100 )  /* (PDC_SPI0) Base Address */
#وصف_ڪريو AT91_C_بنياد_SPI0        ( 0xFFFE0000 )  /* (SPI0) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_US1     ( 0xFFFC4100 )  /* (PDC_US1) Base Address */
#وصف_ڪريو AT91_C_بنياد_US1         ( 0xFFFC4000 )  /* (US1) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_US0     ( 0xFFFC0100 )  /* (PDC_US0) Base Address */
#وصف_ڪريو AT91_C_بنياد_US0         ( 0xFFFC0000 )  /* (US0) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_SSC     ( 0xFFFD4100 )  /* (PDC_SSC) Base Address */
#وصف_ڪريو AT91_C_بنياد_SSC         ( 0xFFFD4000 )  /* (SSC) Base Address */
#وصف_ڪريو AT91_C_بنياد_TWI         ( 0xFFFB8000 )  /* (TWI) Base Address */
#وصف_ڪريو AT91_C_بنياد_PWMC_CH3    ( 0xFFFCC260 )  /* (PWMC_CH3) Base Address */
#وصف_ڪريو AT91_C_بنياد_PWMC_CH2    ( 0xFFFCC240 )  /* (PWMC_CH2) Base Address */
#وصف_ڪريو AT91_C_بنياد_PWMC_CH1    ( 0xFFFCC220 )  /* (PWMC_CH1) Base Address */
#وصف_ڪريو AT91_C_بنياد_PWMC_CH0    ( 0xFFFCC200 )  /* (PWMC_CH0) Base Address */
#وصف_ڪريو AT91_C_بنياد_PWMC        ( 0xFFFCC000 )  /* (PWMC) Base Address */
#وصف_ڪريو AT91_C_بنياد_UDP         ( 0xFFFB0000 )  /* (UDP) Base Address */
#وصف_ڪريو AT91_C_بنياد_TC0         ( 0xFFFA0000 )  /* (TC0) Base Address */
#وصف_ڪريو AT91_C_بنياد_TC1         ( 0xFFFA0040 )  /* (TC1) Base Address */
#وصف_ڪريو AT91_C_بنياد_TC2         ( 0xFFFA0080 )  /* (TC2) Base Address */
#وصف_ڪريو AT91_C_بنياد_TCB         ( 0xFFFA0000 )  /* (TCB) Base Address */
#وصف_ڪريو AT91_C_بنياد_CAN_MB0     ( 0xFFFD0200 )  /* (CAN_MB0) Base Address */
#وصف_ڪريو AT91_C_بنياد_CAN_MB1     ( 0xFFFD0220 )  /* (CAN_MB1) Base Address */
#وصف_ڪريو AT91_C_بنياد_CAN_MB2     ( 0xFFFD0240 )  /* (CAN_MB2) Base Address */
#وصف_ڪريو AT91_C_بنياد_CAN_MB3     ( 0xFFFD0260 )  /* (CAN_MB3) Base Address */
#وصف_ڪريو AT91_C_بنياد_CAN_MB4     ( 0xFFFD0280 )  /* (CAN_MB4) Base Address */
#وصف_ڪريو AT91_C_بنياد_CAN_MB5     ( 0xFFFD02A0 )  /* (CAN_MB5) Base Address */
#وصف_ڪريو AT91_C_بنياد_CAN_MB6     ( 0xFFFD02C0 )  /* (CAN_MB6) Base Address */
#وصف_ڪريو AT91_C_بنياد_CAN_MB7     ( 0xFFFD02E0 )  /* (CAN_MB7) Base Address */
#وصف_ڪريو AT91_C_بنياد_CAN         ( 0xFFFD0000 )  /* (CAN) Base Address */
#وصف_ڪريو AT91_C_بنياد_EMAC        ( 0xFFFDC000 )  /* (EMAC) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_ADC     ( 0xFFFD8100 )  /* (PDC_ADC) Base Address */
#وصف_ڪريو AT91_C_بنياد_ADC         ( 0xFFFD8000 )  /* (ADC) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_AES     ( 0xFFFA4100 )  /* (PDC_AES) Base Address */
#وصف_ڪريو AT91_C_بنياد_AES         ( 0xFFFA4000 )  /* (AES) Base Address */
#وصف_ڪريو AT91_C_بنياد_PDC_TDES    ( 0xFFFA8100 )  /* (PDC_TDES) Base Address */
#وصف_ڪريو AT91_C_بنياد_TDES        ( 0xFFFA8000 )  /* (TDES) Base Address */

/* ***************************************************************************** */
/*               MEMORY MAPPING DEFINITIONS FOR AT91SAM7X128 */
/* ***************************************************************************** */
#وصف_ڪريو AT91C_ISRAM          ( 0x00200000 )    /* Internal SRAM base address */
#وصف_ڪريو AT91_C_ISRAM_سائيز     ( 0x00008000 )    /* Internal SRAM size in byte (32 Kbyte) */
#وصف_ڪريو AT91C_IFLASH         ( 0x00100000 )    /* Internal ROM base address */
#وصف_ڪريو AT91_C_IFLASH_سائيز    ( 0x00020000 )    /* Internal ROM size in byte (128 Kbyte) */
