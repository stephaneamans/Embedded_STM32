#ifndef CONFIGURATION_USART_H
#define CONFIGURATION_USART_H

/*********************************
 * USART definitions
 ********************************/

/* USART1 configuration                     */
#define USART1_REGS                          USART1
#define USART1_BAUDRATE                      115200
#define USART1_LENGTH                        bits_data_9
#define USART1_PARITY                        parity_odd
#define USART1_STOP_BITS                     one
#define USART1_MODE                          usart_dma
#define USART1_IRQ_DMA_PRIORITY              prio4
#define USART1_DMA_DRIVER_TX                 0
#define USART1_DMA_DRIVER_RX                 0

/* USART2 configuration                     */
#define USART2_REGS                          USART2
#define USART2_BAUDRATE                      115200
#define USART2_LENGTH                        bits_data_8
#define USART2_PARITY                        parity_odd
#define USART2_STOP_BITS                     one
#define USART2_MODE                          usart_poll
#define USART2_IRQ_DMA_PRIORITY              prio4
#define USART2_DMA_DRIVER_TX                 0
#define USART2_DMA_DRIVER_RX                 0

#endif /* CONFIGURATION_USART_H_ */
