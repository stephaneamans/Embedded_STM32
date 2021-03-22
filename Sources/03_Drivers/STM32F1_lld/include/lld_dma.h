/*
 * lld_dma.h
 *
 * Created on: Jun 8, 2020
 * Author: Stephane Amans
 */
#ifndef LLD_DMA_H_
#define LLD_DMA_H_


/* Include files:        */
#include <stdint.h>

#include "configuration_module_activation.h"
//#include "configuration_dma.h"
#include "lld_clock.h"
#include "lld_nvic.h"
#include "regbase_dma.h"

#define MAX_DMA_CHANNELS      7
#define DMA_CHANNEL_ENABLE    0x01


/* Option enable:        */
typedef enum
{
    dma_disable = 0x00,
    dma_enable = 0x01
}mode_enable;


/* DMA channel priority configuration: */
typedef enum
{
    low = 0x00,
    medium = 0x01,
    hight = 0x02,
    very_high = 0x03
}dma_prio;


/* Memory or peripheral data length. */
typedef enum
{
    bits_8 = 0x00,
    bits_16 = 0x01,
    bits_32 = 0x02
}dma_data_type;


/* DMA initialization structure definition :        */

typedef struct
{
    DMA_Channel_TypeDef *reg;
    mode_enable mem2mem;
    dma_prio dma_priority;
    dma_data_type mem_data_type;
    uint16_t memory_zone_size;
    uintptr_t memory_zone_address;
    uintptr_t peripheral_address;
    dma_data_type periph_data_type;
    mode_enable memory_increment;
    mode_enable peripheral_increment;
    mode_enable read_from_memory;
    struct
    {
        mode_enable transfer_error_interrupt;
        mode_enable half_transfer_interrupt;
        mode_enable transfer_complete_interrupt;
        irq_priority priority;
        void(*callback)(uint8_t*);
    }irq;
}t_dma_channel_cfg;

struct t_dma_driver
{
	DMA_Channel_TypeDef *reg;
	uint16_t memory_zone_size;
	uintptr_t memory_zone_address;
    uintptr_t peripheral_address;
};
extern struct t_dma_driver dma_driver[7];

/* Functions prototypes:                       */

/** Configure DMA:
 *
 * \param driver: DMA driver;
 * \param cfg: DMA configuration structure.
 *
 * \return: Error code or 0 if OK.
 *
 */
t_error_handling dma_init(struct t_dma_driver *driver, t_dma_channel_cfg *cfg);


/** Memory copy with DMA
 *
 * \param dma_channel: DMA channel configuration structure.
 * \param address_destination: Pointer to the destination address.
 * \param address_source: Pointer to the source address.
 * \param memory_zone_size: Memory zone length.
 *
 * \return: Error code or 0 if OK.
 *
 */
t_error_handling dma_memcpy(struct t_dma_driver *driver, void *address_destination,
                            void *address_source, uint16_t memory_zone_size);


/** Start DMA transfer:
 *
 * \param driver: DMA driver structure.
 *
 * \return: Error code or 0 if OK.
 *
 */
t_error_handling dma_start_transfer(struct t_dma_driver *driver);

/** Stop DMA transfer:
 *
 * \param dma_channel: DMA channel configuration structure.
 *
 * \return: Error code or 0 if OK.
 *
 */
t_error_handling dma_stop_transfer(struct t_dma_driver *driver);


/** Start DMA with new parameters if any changes:
 *
 * \param driver: DMA driver.
 * \param mem_address: Memory address location.
 * \param length: Transfer length.
 *
 */
t_error_handling dma_transfer(struct t_dma_driver *driver, void *mem_address,void *periph_address, uint16_t length);


/** Disable DMA clock.
 *
 * \param dma: address of the dma port to unclock.
 *
 * \return: Error code or OK.
 *
 */
t_error_handling dma_disable_clock(DMA_TypeDef *dma);


/* Pointer callback function table prototype	*/
void(*dma_callback[7])(uint8_t *irq_source);


#endif /* LLD_DMA_H_ */
