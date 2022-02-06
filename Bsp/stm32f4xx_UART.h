#ifndef __UART
  #define __UART


/* Macros for specifying which UART to use. */
  #define SD_UART1                0
  #define SD_UART2                1
  #define SD_UART3                2

  #define MAX_BAUD_RATE           115200
  #define MIN_BAUD_RATE           300

/* UART Mode Definition Bits */
  #define UART_PARITY_NONE        0x00
  #define UART_PARITY_EVEN        0x01
  #define UART_PARITY_ODD         0x02

  #define UART_DATA_BITS_8        0x00
  #define UART_DATA_BITS_9        0x01

  #define UART_MODE_NORMAL        0x01
  #define UART_MODE_AUTO_ECHO     0x02
  #define UART_MODE_LOCAL_LOOP    0x03

  #define UART_STOP_BITS_1        0x00
  #define UART_STOP_BITS_2        0x01




/*===============================================================================================================
                                ќбъ€вление полей регистра  Status register (USART_SR)

This bit is set by hardware when the nCTS input toggles, if the CTSE bit is set. It is cleared by
software (by writing it to 0). An interrupt is generated if CTSIE=1 in the USART_CR3 register.
0: No change occurred on the nCTS status line
1: A change occurred on the nCTS status line*/
//  #define UART_SR_CTS     BIT(9)
/*LIN Break Detection Flag
LIN Break Detection Flag (Status flag)
0: LIN Break not detected
1: LIN break detected
Note: An interrupt is generated when LBD=1 if LBDIE=1 */
//  #define USART_SR_LBD    BIT(8)
/*Transmit Data Register Empty
This bit is set by hardware when the content of the TDR register has been transferred into the shift
register. An interrupt is generated if the TXEIE bit =1 in the USART_CR1 register. It is cleared by a
write to the USART_DR register.
0: Data is not transferred to the shift register
1: Data is transferred to the shift register)
Note: This bit is used during single buffer transmission */
//  #define USART_SR_TXE    BIT(7)
/*Transmission Complete.
This bit is set by hardware when transmission of a frame containing Data is complete. An interrupt
is generated if TCIE=1 in the USART_CR1 register. It is cleared by a software sequence (an read to
the USART_SR register followed by a write to the USART_DR register).
0: Transmission is not complete
1: Transmission is complete */
//  #define USART_SR_TC     BIT(6)
/*Read Data Register Not Empty.
This bit is set by hardware when the content of the RDR shift register has been transferred to the
USART_DR register. An interrupt is generated if RXNEIE=1 in the USART_CR1 register. It is
cleared by a read to the USART_DR register.
0: Data is not received
1: Received data is ready to be read */
//  #define USART_SR_RXNE   BIT(5)
/*IDLE line detected.
This bit is set by hardware when an Idle Line is detected. An interrupt is generated if the IDLEIE=1
in the USART_CR1 register. It is cleared by a software sequence (an read to the USART_SR
register followed by a read to the USART_DR register).
0: No Idle Line is detected
1: Idle Line is detected
Note: The IDLE bit will not be set again until the RXNE bit has been set itself (i.e. a new idle line occurs). */
//  #define USART_SR_IDLE   BIT(4)
/*OverRun Error.
This bit is set by hardware when the word currently being received in the shift register is ready to be
transferred into the RDR register while RXNE=1. An interrupt is generated if RXNEIE=1 in the
USART_CR1 register. It is cleared by a software sequence (an read to the USART_SR register
followed by a read to the USART_DR register).
0: No Overrun error
1: Overrun error is detected
Note: When this bit is set, the RDR register content will not be lost but the shift register will be
overwritten. An interrupt is generated on ORE flag in case of Multi Buffer communication if the EIE bit is set. */
//  #define USART_SR_ORE    BIT(3)
/*Noise Error Flag.
This bit is set by hardware when noise is detected on a received frame. It is cleared by a software
sequence (an read to the USART_SR register followed by a read to the USART_DR register).
0: No noise is detected
1: Noise is detected
Note: This bit does not generate interrupt as it appears at the same time as the RXNE bit which itself
generates an interrupting interrupt is generated on NE flag in case of Multi Buffer communication if the EIE bit is set. */
//  #define USART_SR_NE     BIT(2)
/*Framing Error.
This bit is set by hardware when a de-synchronization, excessive noise or a break character is
detected. It is cleared by a software sequence (an read to the USART_SR register followed by a
read to the USART_DR register).
0: No Framing error is detected
1: Framing error or break character is detected
Note:
This bit does not generate interrupt as it appears at the same time as the RXNE bit which itself
generates an interrupt. If the word currently being transferred causes both frame error and overrun
error, it will be transferred and only the ORE bit will be set.
An interrupt is generated on FE flag in case of Multi Buffer communication if the EIE bit is set. */
//  #define USART_SR_FE     BIT(1)
/*Parity Error.
This bit is set by hardware when a parity error occurs in receiver mode. It is cleared by a software
sequence (a read to the status register followed by a read to the USART_DR data register). An
interrupt is generated if PEIE=1 in the USART_CR1 register.
0: No parity error
1: Parity error */
//  #define USART_SR_PE     BIT(0)


/*===============================================================================================================
                                ќбъ€вление полей регистра  Control register 1 (USART_CR1)

USART Enable.
When this bit is cleared the USART prescalers and outputs are stopped and the end of the current
byte transfer in order to reduce power consumption. This bit is set and cleared by software.
0: USART prescaler and outputs disabled
1: USART enabled*/
//  #define USART_CR1_UE       BIT(13)
/*word length.
This bit determines the word length. It is set or cleared by software.
0: 1 Start bit, 8 Data bits, n Stop bit
1: 1 Start bit, 9 Data bits, 1 Stop bit
Note: The M bit must not be modified during a data transfer (both transmission and reception) */
//  #define USART_CR1_M        BIT(12)
/*Wakeup method.
This bit determines the USART wakeup method, it is set or cleared by software.
0: Idle Line
1: Address Mark */
//  #define USART_CR1_WAKE     BIT(11)
/*Parity Control Enable.
This bit selects the hardware parity control (generation and detection). When the parity control is
enabled, the computed parity is inserted at the MSB position (9th bit if M=1; 8th bit if M=0) and
parity is checked on the received data. This bit is set and cleared by software. Once it is set, PCE is
active after the current byte (in reception and in transmission).
0: Parity control disabled
1: Parity control enabled */
//  #define USART_CR1_PCE      BIT(10)
/*Parity Selection.
This bit selects the odd or even parity when the parity generation/detection is enabled (PCE bit set).
It is set and cleared by software. The parity will be selected after the current byte.
0: Even parity
1: Odd parity */
//  #define USART_CR1_PS       BIT(9)
/*PE Interrupt Enable.
This bit is set and cleared by software.
0: Interrupt is inhibited
1: An USART interrupt is generated whenever PE=1 in the USART_SR register */
//  #define USART_CR1_PEIE     BIT(8)
/*TXE Interrupt Enable.
This bit is set and cleared by software.
0: Interrupt is inhibited
1: An USART interrupt is generated whenever TXE=1 in the USART_SR register */
//  #define USART_CR1_TXEIE    BIT(7)
/*Transmission Complete Interrupt Enable.
This bit is set and cleared by software.
0: Interrupt is inhibited
1: An USART interrupt is generated whenever TC=1 in the USART_SR register */
//  #define USART_CR1_TCIE     BIT(6)
/*RXNE Interrupt Enable.
This bit is set and cleared by software.
0: Interrupt is inhibited
1: An USART interrupt is generated whenever ORE=1 or RXNE=1 in the USART_SR register */
//  #define USART_CR1_RXNEIE   BIT(5)
/*IDLE Interrupt Enable.
This bit is set and cleared by software.
0: Interrupt is inhibited
1: An USART interrupt is generated whenever IDLE=1 in the USART_SR register */
//  #define USART_CR1_IDLEIE   BIT(4)
/*Transmitter Enable.
This bit enables the transmitter. It is set and cleared by software.
0: Transmitter is disabled
1: Transmitter is enabled
Notes:
1: During transmission, a У0Ф pulse on the TE bit (У0Ф followed by У1Ф) sends a preamble (idle line) after
the current word, except in smartcard mode.
2: When TE is set there is a 1 bit-time delay before the transmission starts. */
//  #define USART_CR1_TE       BIT(3)
/*Receiver Enable.
This bit enables the receiver. It is set and cleared by software.
0: Receiver is disabled
1: Receiver is enabled and begins searching for a start bit */                        
//  #define USART_CR1_RE       BIT(2)
/*Receiver wakeup.
This bit determines if the USART is in mute mode or not. It is set and cleared by software and can
be cleared by hardware when a wakeup sequence is recognized.
0: Receiver in active mode
1: Receiver in mute mode
Notes:
1: Before selecting Mute mode (by setting the RWU bit) the USART must first receive a data byte,
otherwise it cannot function in Mute mode with wakeup by Idle line detection.
2: In Address Mark Detection wakeup configuration (WAKE bit=1) the RWU bit cannot be modified by
software while the RXNE bit is set. */
//  #define USART_CR1_RWU      BIT(1)
/*Send Break.
This bit set is used to send break characters. It can be set and cleared by software. It should be set
by software, and will be reset by hardware during the stop bit of break.
0: No break character is transmitted
1: Break character will be transmitted */                       
//  #define USART_CR1_SBK      BIT(0)


/*===============================================================================================================
                                ќбъ€вление полей регистра  Control register 2 (USART_CR2)

 These 3 bits (CPOL, CPHA, LBCL) should not be written while the transmitter is enabled.


LIN mode enable
This bit is set and cleared by software.
0: LIN mode disabled
1: LIN mode enabled
The LIN mode enables the capability to send LIN Synch Breaks (13 low bits) using the SBK bit in
the USART_CR1 register, and to detect LIN Sync breaks.*/
//  #define USART_CR2_LINEN   BIT(14)
/*STOP bits.
These bits are used for programming the stop bits.
00: 1 Stop bit
01: 0.5 Stop bit
10: 2 Stop bits
11: 1.5 Stop bit */
  #define USART_CR2_STOP_x(x) LSHIFT(x,12)
/*Clock Enable.
This bit allows the user to enable the SCLK pin.
0: SCLK pin disabled
1: SCLK pin enabled */
//  #define USART_CR2_CLKEN   BIT(11)
/*Clock Polarity.
This bit allows the user to select the polarity of the clock output on the SCLK pin in synchronous
mode. It works in conjunction with the CPHA bit to produce the desired clock/data relationship
0: Steady low value on SCLK pin outside transmission window.
1: Steady high value on SCLK pin outside transmission window. */
//  #define USART_CR2_CPOL    BIT(10)
/*Clock Phase
This bit allows the user to select the phase of the clock output on the SCLK pin in synchronous
mode. It works in conjunction with the CPOL bit to produce the desired clock/data relationship (see
figures 173 to 176)
0: The first clock transition is the first data capture edge.
1: The second clock transition is the first data capture edge */
//  #define USART_CR2_CPHA    BIT(9)
/*Last Bit Clock pulse.
This bit allows the user to select whether the clock pulse associated with the last data bit
transmitted (MSB) has to be output on the SCLK pin in synchronous mode.
0: The clock pulse of the last data bit is not output to the SCLK pin.
1: The clock pulse of the last data bit is output to the SCLK pin.
Note: The last bit is the 8th or 9th data bit transmitted depending on the 8 or 9 bit format selected by
the M bit in the USART_CR1 register. */
//  #define USART_CR2_LBCL    BIT(8)
/*LIN Break Detection Interrupt Enable.
Break interrupt mask (break detection using break delimiter).
0: Interrupt is inhibited
1: An interrupt is generated whenever LBD=1 in the USART_SR register */
//  #define USART_CR2_LBDIE   BIT(6)
/*LIN Break Detection Length.
This bit is for selection between 11 bit or 10 bit break detection.
0: 10 bit break detection
1: 11 bit break detection */
//  #define USART_CR2_LBDL    BIT(5)
/*Address of the USART node.
This bit-field gives the address of the USART node.
This is used in multiprocessor communication during mute mode, for wake up with address mark
detection. */
//  #define USART_CR2_ADD(x)  LSHIFT(x,0)

/*===============================================================================================================
                                ќбъ€вление полей регистра  Control register 3 (USART_CR3)

CTS Interrupt Enable.
0: Interrupt is inhibited
1: An interrupt is generated whenever CTS=1 in the USART_SR register*/
//  #define USART_CR3_CTSIE     BIT(10)
/*CTS Enable.
0: CTS hardware flow control disabled
1: CTS mode enabled, data is only transmitted when the nCTS input is asserted (tied to 0). If the
nCTS input is deasserted while a data is being transmitted, then the transmission is completed
before stopping. If a data is written into the data register while nCTS is asserted, the transmission is
postponed until nCTS is asserted. */
//  #define USART_CR3_CTSE   BIT(9)
/*RTS Enable.
0: RTS hardware flow control disabled
1: RTS interrupt enabled, data is only requested when there is space in the receive buffer. The
transmission of data is expected to cease after the current character has been transmitted. The
nRTS output is asserted (tied to 0) when a data can be received. */
//  #define USART_CR3_RTSE   BIT(8)
/*DMA Enable Transmitter.
This bit is set/reset by software
1: DMA mode is enabled for transmission.
0: DMA mode is disabled for transmission. */
//  #define USART_CR3_DMAT   BIT(7)
/*DMA Enable Receiver.
This bit is set/reset by software
1: DMA mode is enabled for reception.
0: DMA mode is disabled for reception. */
//  #define USART_CR3_DMAR   BIT(6)
/*Smartcard mode enable.
This bit is used for enabling Smartcard mode.
0: Smartcard Mode disabled
1: Smartcard Mode enabled */
//  #define USART_CR3_SCEN   BIT(5)
/*Smartcard NACK enable.
0: NACK transmission in case of parity error is disabled
1: NACK transmission during parity error is enabled. */
//  #define USART_CR3_NACK   BIT(4)
/*Half-Duplex Selection.
Selection of Single-wire Half-duplex mode
0: Half duplex mode is not selected
1: Half duplex mode is selected */
//  #define USART_CR3_HDSEL   BIT(3)
/*IrDA Low-Power.
This bit is used for selecting between normal and low-power IrDA modes
0: Normal mode
1: Low-power mode */
//  #define USART_CR3_IRLP   BIT(2)
/*IrDA mode Enable.
This bit is set and cleared by software.
0: IrDA disabled
1: IrDA enabled */
//  #define USART_CR3_IREN   BIT(1)
/*Error Interrupt Enable.
Error Interrupt Enable Bit is required to enable interrupt generation in case of a framing error,
overrun error or noise error (FE=1 or ORE=1 or NE=1 in the USART_SR register) in case of Multi
Buffer Communication (DMAR=1 in the USART_CR3 register).
0: Interrupt is inhibited
1: An interrupt is generated whenever DMAR=1 in the USART_CR3 register and FE=1 or ORE=1
or NE=1 in the USART_SR register. */
//  #define USART_CR3_EIE   BIT(0)




void   UART_reset(INT8U n);
void   UART_disable(USART_TypeDef *puart);
void   UART_enable(USART_TypeDef *puart);
void   UART_set_baude_rate(INT8U n, INT32U baudrate);
void   UART_set_stop_bits(USART_TypeDef *puart,INT8U sb);
void   UART_set_data_bits(USART_TypeDef *puart,INT8U db);
void   UART_set_parity_bits(USART_TypeDef *puart,INT8U pb);
void   UART_enable_TX_int(USART_TypeDef *puart);
void   UART_enable_RX_int(USART_TypeDef *puart);
void   UART_disable_TX_int(USART_TypeDef *puart);
void   UART_wait_TX_occasion(USART_TypeDef *puart);
void   Init_UART(INT8U n,INT32U baudrate,INT8U sb,INT8U pb,INT8U db);
void   Init_UART_interrupt(INT8U n);
void   DeInit_UART_interrupt(INT8U n);
void   UART_TX_byte(USART_TypeDef *puart,INT8U b);
INT8U  UART_RX_byte(USART_TypeDef *puart);
INT32U UART_peek_byte(USART_TypeDef *puart,INT8U *b);
INT32S UART_wait_byte (USART_TypeDef *puart,INT8U *c, INT32U timeout);

void   UART_TX_str(USART_TypeDef *puart,INT8U* str);

void   Comc_init_channel(char ch);
void   Comc_set_recv_task(char ch);
int    Comc_check_data(char ch);
int    Comc_peek_byte(char ch, unsigned char *b);
int    Comc_send_buffer(char ch,unsigned char *buf, int len);
int    Comc_send_str(char ch, char *str);
INT32S UART1_printf(char* fmtstr,...);

#endif
