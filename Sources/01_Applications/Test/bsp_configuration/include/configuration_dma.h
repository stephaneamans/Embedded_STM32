#ifndef CONFIGURATION_DMA_H
#define CONFIGURATION_DMA_H

/*********************************
 * DMA definitions
 ********************************/
extern uint8_t usart_buffer;


/* DMA1 channel 1 configuration                      */
#define DMA1_CH1_MEM2MEM                dma_disable
#define DMA1_CH1_PRIORITY               low
#define DMA1_CH1_MEM_DATA_TYPE          bits_8
#define DMA1_CH1_MEMORY_ZONE_SIZE       USART_BUFFER_LENGTH
#define DMA1_CH1_MEMORY_ZONE_ADDRESS    0
#define DMA1_CH1_PERIPHERAL_ADDRESS     &usart1_configuration.reg->DR
#define DMA1_CH1_PERIPH_DATA_TYPE       bits_8
#define DMA1_CH1_MEMORY_INCREMENT       1
#define DMA1_CH1_PERIPHERAL_INCREMENT   0
#define DMA1_CH1_READ_FROM_MEMORY       0
#define DMA1_CH1_IRQ_TRANSFER_ERROR     dma_disable
#define DMA1_CH1_IRQ_HALF_TRANSFER      dma_disable
#define DMA1_CH1_IRQ_TRANSFER_COMPLETE  dma_disable
#define DMA1_CH1_IRQ_PRIORITY           0
#define DMA1_CH1_IRQ_CALLBACK           0

/* DMA1 channel 2 configuration                      */
#define DMA1_CH2_MEM2MEM                dma_disable
#define DMA1_CH2_PRIORITY               low
#define DMA1_CH2_MEM_DATA_TYPE          bits_8
#define DMA1_CH2_MEMORY_ZONE_SIZE       32
#define DMA1_CH2_MEMORY_ZONE_ADDRESS    0
#define DMA1_CH2_PERIPHERAL_ADDRESS     0
#define DMA1_CH2_PERIPH_DATA_TYPE       bits_8
#define DMA1_CH2_MEMORY_INCREMENT       0
#define DMA1_CH2_PERIPHERAL_INCREMENT   0
#define DMA1_CH2_READ_FROM_MEMORY       0
#define DMA1_CH2_IRQ_TRANSFER_ERROR     dma_disable
#define DMA1_CH2_IRQ_HALF_TRANSFER      dma_disable
#define DMA1_CH2_IRQ_TRANSFER_COMPLETE  dma_disable
#define DMA1_CH2_IRQ_PRIORITY           0
#define DMA1_CH2_IRQ_CALLBACK           0

/* DMA1 channel 3 configuration                      */
#define DMA1_CH3_MEM2MEM                dma_disable
#define DMA1_CH3_PRIORITY               low
#define DMA1_CH3_MEM_DATA_TYPE          bits_8
#define DMA1_CH3_MEMORY_ZONE_SIZE       32
#define DMA1_CH3_MEMORY_ZONE_ADDRESS    0
#define DMA1_CH3_PERIPHERAL_ADDRESS     0
#define DMA1_CH3_PERIPH_DATA_TYPE       bits_8
#define DMA1_CH3_MEMORY_INCREMENT       0
#define DMA1_CH3_PERIPHERAL_INCREMENT   0
#define DMA1_CH3_READ_FROM_MEMORY       0
#define DMA1_CH3_IRQ_TRANSFER_ERROR     dma_disable
#define DMA1_CH3_IRQ_HALF_TRANSFER      dma_disable
#define DMA1_CH3_IRQ_TRANSFER_COMPLETE  dma_disable
#define DMA1_CH3_IRQ_PRIORITY           0
#define DMA1_CH3_IRQ_CALLBACK           0

/* DMA1 channel 4 configuration                      */
#define DMA1_CH4_MEM2MEM                dma_disable
#define DMA1_CH4_PRIORITY               low
#define DMA1_CH4_MEM_DATA_TYPE          bits_8
#define DMA1_CH4_MEMORY_ZONE_SIZE       32
#define DMA1_CH4_MEMORY_ZONE_ADDRESS    0
#define DMA1_CH4_PERIPHERAL_ADDRESS     0
#define DMA1_CH4_PERIPH_DATA_TYPE       bits_8
#define DMA1_CH4_MEMORY_INCREMENT       1
#define DMA1_CH4_PERIPHERAL_INCREMENT   0
#define DMA1_CH4_READ_FROM_MEMORY       1
#define DMA1_CH4_IRQ_TRANSFER_ERROR     dma_disable
#define DMA1_CH4_IRQ_HALF_TRANSFER      dma_disable
#define DMA1_CH4_IRQ_TRANSFER_COMPLETE  dma_disable
#define DMA1_CH4_IRQ_PRIORITY           0
#define DMA1_CH4_IRQ_CALLBACK           0

/* DMA1 channel 5 configuration                      */
#define DMA1_CH5_MEM2MEM                dma_disable
#define DMA1_CH5_PRIORITY               low
#define DMA1_CH5_MEM_DATA_TYPE          bits_8
#define DMA1_CH5_MEMORY_ZONE_SIZE       32
#define DMA1_CH5_MEMORY_ZONE_ADDRESS    0
#define DMA1_CH5_PERIPHERAL_ADDRESS     0
#define DMA1_CH5_PERIPH_DATA_TYPE       bits_8
#define DMA1_CH5_MEMORY_INCREMENT       1
#define DMA1_CH5_PERIPHERAL_INCREMENT   0
#define DMA1_CH5_READ_FROM_MEMORY       0
#define DMA1_CH5_IRQ_TRANSFER_ERROR     dma_disable
#define DMA1_CH5_IRQ_HALF_TRANSFER      dma_disable
#define DMA1_CH5_IRQ_TRANSFER_COMPLETE  dma_disable
#define DMA1_CH5_IRQ_PRIORITY           0
#define DMA1_CH5_IRQ_CALLBACK           0

/* DMA1 channel 6 configuration                      */
#define DMA1_CH6_MEM2MEM                dma_disable
#define DMA1_CH6_PRIORITY               low
#define DMA1_CH6_MEM_DATA_TYPE          bits_8
#define DMA1_CH6_MEMORY_ZONE_SIZE       32
#define DMA1_CH6_MEMORY_ZONE_ADDRESS    0
#define DMA1_CH6_PERIPHERAL_ADDRESS     0
#define DMA1_CH6_PERIPH_DATA_TYPE       bits_8
#define DMA1_CH6_MEMORY_INCREMENT       0
#define DMA1_CH6_PERIPHERAL_INCREMENT   0
#define DMA1_CH6_READ_FROM_MEMORY       0
#define DMA1_CH6_IRQ_TRANSFER_ERROR     dma_disable
#define DMA1_CH6_IRQ_HALF_TRANSFER      dma_disable
#define DMA1_CH6_IRQ_TRANSFER_COMPLETE  dma_disable
#define DMA1_CH6_IRQ_PRIORITY           0
#define DMA1_CH6_IRQ_CALLBACK           0

/* DMA1 channel 7 configuration                      */
#define DMA1_CH7_MEM2MEM                dma_disable
#define DMA1_CH7_PRIORITY               low
#define DMA1_CH7_MEM_DATA_TYPE          bits_8
#define DMA1_CH7_MEMORY_ZONE_SIZE       32
#define DMA1_CH7_MEMORY_ZONE_ADDRESS    0
#define DMA1_CH7_PERIPHERAL_ADDRESS     0
#define DMA1_CH7_PERIPH_DATA_TYPE       bits_8
#define DMA1_CH7_MEMORY_INCREMENT       0
#define DMA1_CH7_PERIPHERAL_INCREMENT   0
#define DMA1_CH7_READ_FROM_MEMORY       0
#define DMA1_CH7_IRQ_TRANSFER_ERROR     dma_disable
#define DMA1_CH7_IRQ_HALF_TRANSFER      dma_disable
#define DMA1_CH7_IRQ_TRANSFER_COMPLETE  dma_disable
#define DMA1_CH7_IRQ_PRIORITY           0
#define DMA1_CH7_IRQ_CALLBACK           0

#endif /* CONFIGURATION_DMA_H_ */
