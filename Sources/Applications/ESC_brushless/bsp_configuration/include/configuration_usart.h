#ifndef CONFIGURATION_USART_H
#define CONFIGURATION_USART_H


/*********************************
 * USART definitions
 ********************************/


/* USART1 configuration                     */
#define USART1_BAUDRATE                      115200
#define USART1_LENGTH                        bits_data_8
#define USART1_WAKEUP                        idle_line
#define USART1_PARITY                        parity_even
#define USART1_STOP_BITS                     one
#define USART1_CLOCK_MODES                   low_and_first_edge
#define USART1_RTS                           0
#define USART1_DMA                           0
#define USART1_IRQ_TYPE                      no_usart_irq
#define USART1_IRQ_CALLBACK_PARITY           0
#define USART1_IRQ_CALLBACK_TX_ERR           0
#define USART1_IRQ_CALLBACK_TX_COMPLETE_ERR  0
#define USART1_IRQ_CALLBACK_RX_ERR           0
#define USART1_IRQ_CALLBACK_IDLE             0
#define USART1_IRQ_CALLBACK_CTS              0
#define USART1_IRQ_CALLBACK_ERROR_IRQ        0


/* USART2 configuration                     */
#define USART2_BAUDRATE                      115200
#define USART2_LENGTH                        bits_data_8
#define USART2_WAKEUP                        idle_line
#define USART2_PARITY                        parity_even
#define USART2_STOP_BITS                     one
#define USART2_CLOCK_MODES                   low_and_first_edge
#define USART2_RTS                           0
#define USART2_DMA                           0
#define USART2_IRQ_TYPE                      no_usart_irq
#define USART2_IRQ_CALLBACK_PARITY           0
#define USART2_IRQ_CALLBACK_TX_ERR           0
#define USART2_IRQ_CALLBACK_TX_COMPLETE_ERR  0
#define USART2_IRQ_CALLBACK_RX_ERR           0
#define USART2_IRQ_CALLBACK_IDLE             0
#define USART2_IRQ_CALLBACK_CTS              0
#define USART2_IRQ_CALLBACK_ERROR_IRQ        0

#endif /* CONFIGURATION_USART_H_ */
