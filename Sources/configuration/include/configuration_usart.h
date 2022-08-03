#ifndef CONFIGURATION_USART_H
#define CONFIGURATION_USART_H

/*********************************
 * USART definitions
 ********************************/

/* USART1 configuration                     */
#define USART1_BASE               (APB2PERIPH_BASE + 0x00003800U)
#define USART1_BAUDRATE           115200
#define USART1_LENGTH             usart_data_9_bits
#define USART1_PARITY             usart_parity_odd
#define USART1_STOP_BITS          usart_one_stop_bit
#define USART1_IRQ_ACTIVE         true  
#define USART1_IRQ_PRIORITY       prio4
#define USART1_DMA_ACTIVE         false


/* USART2 configuration                     */
#define USART2_BASE               (APB1PERIPH_BASE + 0x00004400U)
#define USART2_BAUDRATE           115200
#define USART2_LENGTH             usart_data_8_bits
#define USART2_PARITY             usart_parity_odd
#define USART2_STOP_BITS          usart_one_stop_bit
#define USART2_IRQ_ACTIVE         false
#define USART2_IRQ_PRIORITY       prio4
#define USART2_DMA_ACTIVE         false

#endif /* CONFIGURATION_USART_H_ */
