/*
 * lld_dma.c
 *
 * Created on: Jun 8, 2020
 * Author: Stephane Amans
 *
 *    Change log:
 *
 *    29/07/2022: Refactor driver
 *
 */

/* Include files.        */
#include "lld_clock.h"
#include "lld_dma.h"
#include "lld_nvic.h"
#include "regbase_dma.h"

/* Bits masks */
#define DMA_CCR_EN_BIT_MASK        0x1U
#define DMA_CCR_TCIE_BIT_MASK      0x2U
#define DMA_CCR_HTIE_BIT_MASK      0x4U
#define DMA_CCR_TEIE_BIT_MASK      0x8U
#define DMA_CCR_DIR_BIT_MASK       0x10U
#define DMA_CCR_PINC_BIT_MASK      0x40U
#define DMA_CCR_MINC_BIT_MASK      0x80U
#define DMA_CCR_PSIZE_16BITS_MASK  0x100U
#define DMA_CCR_PSIZE_32BITS_MASK  0x200U
#define DMA_CCR_PSIZE_BIT_MASK     0x300U
#define DMA_CCR_MSIZE_16BITS_MASK  0x400U
#define DMA_CCR_MSIZE_32BITS_MASK  0x800U
#define DMA_CCR_MSIZE_BIT_MASK     0xC00U
#define DMA_CCR_PL_MEDIUM_BIT_MASK 0x1000U
#define DMA_CCR_PL_HIGH_BIT_MASK   0x2000U
#define DMA_CCR_PL_V_HIGH_BIT_MASK 0x3000U
#define DMA_CCR_PL_BIT_MASK        0x3000U
#define DMA_CCR_MEM2MEM_BIT_MASK   0x4000U

#define DMA_ISR_IFCR_CH1_MASK      0xFU
#define DMA_ISR_IFCR_CH2_MASK      0xF0U
#define DMA_ISR_IFCR_CH3_MASK      0xF00U
#define DMA_ISR_IFCR_CH4_MASK      0xF000U
#define DMA_ISR_IFCR_CH5_MASK      0xF0000U
#define DMA_ISR_IFCR_CH6_MASK      0xF00000U
#define DMA_ISR_IFCR_CH7_MASK      0xF000000U
#define DMA_ISR_CH1_TCIF_BITMASK   0x2U
#define DMA_ISR_CH1_HTIF_BITMASK   0x4U
#define DMA_ISR_CH1_TEIF_BITMASK   0x8U
#define DMA_ISR_CH2_TCIF_BITMASK   0x20U
#define DMA_ISR_CH2_HTIF_BITMASK   0x40U
#define DMA_ISR_CH2_TEIF_BITMASK   0x80U
#define DMA_ISR_CH3_TCIF_BITMASK   0x200U
#define DMA_ISR_CH3_HTIF_BITMASK   0x400U
#define DMA_ISR_CH3_TEIF_BITMASK   0x800U
#define DMA_ISR_CH4_TCIF_BITMASK   0x2000U
#define DMA_ISR_CH4_HTIF_BITMASK   0x4000U
#define DMA_ISR_CH4_TEIF_BITMASK   0x8000U
#define DMA_ISR_CH5_TCIF_BITMASK   0x20000U
#define DMA_ISR_CH5_HTIF_BITMASK   0x40000U
#define DMA_ISR_CH5_TEIF_BITMASK   0x80000U
#define DMA_ISR_CH6_TCIF_BITMASK   0x200000U
#define DMA_ISR_CH6_HTIF_BITMASK   0x400000U
#define DMA_ISR_CH6_TEIF_BITMASK   0x800000U
#define DMA_ISR_CH7_TCIF_BITMASK   0x2000000U
#define DMA_ISR_CH7_HTIF_BITMASK   0x4000000U
#define DMA_ISR_CH7_TEIF_BITMASK   0x8000000U

/* DMA status bitfield structure definition :  */
struct t_dma_isr_bit
{
    uint8_t gif : 1;
    uint8_t tcif : 1;
    uint8_t htif : 1;
    uint8_t teif : 1;
};

/* DMA private structures definition :        */
struct t_dma_private
{
    struct t_dma_regs *reg;
};

struct t_dma_channel_private
{
    struct t_dma_channel_regs *channel_reg;
    uint8_t channel_number;
    struct t_dma_driver *dma;
};

/* Pointer callback function table prototype    */
void (*dma_callback[5])(struct t_dma_status *dma_status);


bool dma_get_half_transfer_complete(struct t_dma_channel_driver *driver)
{
    bool bit_value;

    /* Store and left shift to the 4 LSB the concerned bits of the ISR register */
    uint32_t dma_isr = dma_isr >> (driver->channel_number * 4);

    /* Fill the ISR bitfield structure */
    struct t_dma_isr_bit *isr_bit = (struct t_dma_isr_bit*)&dma_isr;
    bit_value = isr_bit->htif;

    return bit_value;
}

bool dma_get_transfer_complete(struct t_dma_channel_driver *driver)
{
    bool bit_value;

    /* Store and left shift to the 4 LSB the concerned bits of the ISR register */
    uint32_t dma_isr = dma_isr >> (driver->channel_number * 4);

    /* Fill the ISR bitfield structure */
    struct t_dma_isr_bit *isr_bit = (struct t_dma_isr_bit*)&dma_isr;
    bit_value = isr_bit->tcif;

    return bit_value;
}

bool dma_get_transfer_error(struct t_dma_channel_driver *driver)
{
    bool bit_value;

    /* Store and left shift to the 4 LSB the concerned bits of the ISR register */
    uint32_t dma_isr = dma_isr >> (driver->channel_number * 4);

    /* Fill the ISR bitfield structure */
    struct t_dma_isr_bit *isr_bit = (struct t_dma_isr_bit*)&dma_isr;
    bit_value = isr_bit->teif;

    return bit_value;
}

void dma_set_transfer(struct t_dma_channel_driver *driver, struct t_dma_client *client)
{
    dma_stop_transfer(driver);

    /* Set the new configuration parameters. */
    if(client->memory_increment == true)
    {
    }

    if(client->mem_data_type == dma_16_bits)
    {
    }
    else if(client->mem_data_type == dma_32_bits)
    {
    }
}

void dma_start_transfer(struct t_dma_channel_driver *driver)
{
}

void dma_stop_transfer(struct t_dma_channel_driver *driver)
{
}

void dma_transfer_status(struct t_dma_channel_driver *driver, struct t_dma_status *dma_status)
{
    /* Store and left shift to the 4 LSB the concerned bits of the ISR register */
    uint32_t dma_isr = dma_isr >> (driver->channel_number * 4);

    /* Fill the ISR bitfield structure */
    struct t_dma_isr_bit *isr_bit = (struct t_dma_isr_bit*)&dma_isr;

    /* Fill the DMA status structure fields */
    dma_status->transfer_complete = isr_bit->tcif;
    dma_status->half_transfer_complete = isr_bit->htif;
    dma_status->transfer_error = isr_bit->teif;
}

void dma_initialization(struct t_dma_driver *config, struct t_dma_channel_driver *channel_config)
{

    /* Initializes the private structure instances */
    enable_clock(config->peripheral);

    if((channel_config->irq.transfer_complete == true) ||
       (channel_config->irq.half_transfer_complete == true) ||
       (channel_config->irq.transfer_error == true))
    {
        enable_nvic_irq(channel_config->channel_number);
        set_nvic_priority(channel_config->channel_number, channel_config->irq.priority);
        dma_callback[channel_config->channel_number] = channel_config->irq.callback;
    }
}
