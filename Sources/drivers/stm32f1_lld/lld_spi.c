/*
 * lld_spi.c
 *
 * Created on: Jun 25, 2021
 * Author: Stephane Amans
 *
 */

/* Include files        */
#include <stdio.h>
#include <string.h>

#include "fault.h"
#include "lld_spi.h"

#include "regbase_spi.h"

#include "bsp_configuration.h"
#include "configuration_soc.h"


/* Defines */
#define SPI_CR1_CPHA_BIT_MASK         0x1
#define SPI_CR1_CPOL_BIT_MASK         0x2
#define SPI_CR1_MSTR_BIT_MASK         0x4
#define SPI_CR1_BR_BIT_MASK          0x38
#define SPI_CR1_SPE_BIT_MASK         0x40
#define SPI_CR1_LSBFIRST_BIT_MASK    0x80
#define SPI_CR1_SSI_BIT_MASK        0x100
#define SPI_CR1_SSE_BIT_MASK        0x200
#define SPI_CR1_DFF_BIT_MASK        0x800

#define SPI_CR2_SSOE_BIT_MASK       0x4

#define SPI_SR_TXE_BIT_MASK         0x2
#define SPI_SR_RXNE_BIT_MASK        0x1


/* SPI private structure definition :        */
struct t_spi_private
{
    struct t_spi_regs *reg;
    struct t_spi_slave *spi_slaves;
    uint32_t clock_frequency;
    uint16_t freq_khz;
    uint8_t last_config;
};


enum t_cs_state
{
    LOW,
    HIGH,
};


/* Static SPI private and slaves record structure instances. */
static struct t_spi_private priv[SPI_IP_NUMBER];
static struct t_spi_slave *slaves_record[MAX_SPI0_PERIPHERALS + MAX_SPI1_PERIPHERALS];


/** Chip select pin control.
 *
 * \param slave: Pointer to the slave parameters.
 * \param state: Expected state of the cs pin..
 *
 * \return void;
 *
 */
static void cs(struct t_spi_slave *slave, enum t_cs_state state)
{
    if(state == LOW)
    {
        gpio_write(slave->cs, false);
    }

    else
    {
        gpio_write(slave->cs, true);
    }
};


/** Compute frequency divider code.
 *
 * \param bus_frequency: Internal bus frequency.
 * \param spi_frequency: Expected SPI frequency.
 * \param divider_code: Pointer to the divider code computed location.
 *
 * \return : Error code or ERROR_OK.
 *
 */
static t_error_handling compute_frequency_divider(uint32_t bus_frequency, uint16_t spi_frequency, uint8_t *divider_code)
{
    t_error_handling error = ERROR_OK;
    uint32_t local_spi_frequency = (uint32_t)spi_frequency * 1000;
    uint16_t divider = (uint16_t)(bus_frequency/local_spi_frequency);
    uint32_t modulo = bus_frequency%local_spi_frequency;

    if(divider < 3)
    {
        *divider_code = 0;
    }
    else if((divider >= 3) && (divider < 6))
    {
        *divider_code = (1 << 3) & SPI_CR1_BR_BIT_MASK;
    }
    else if((divider >= 6) && (divider < 12))
    {
        *divider_code = (2 << 3) & SPI_CR1_BR_BIT_MASK;
    }
    else if((divider >= 12) && (divider < 20))
    {
        *divider_code = (3 << 3) & SPI_CR1_BR_BIT_MASK;
    }
    else if((divider >= 20) && (divider < 48))
    {
        *divider_code = (4 << 3) & SPI_CR1_BR_BIT_MASK;
    }
    else if((divider >= 48) && (divider < 96))
    {
        *divider_code = (5 << 3) & SPI_CR1_BR_BIT_MASK;
    }
    else if((divider >= 96) && (divider < 192))
    {
        *divider_code = (6 << 3) & SPI_CR1_BR_BIT_MASK;
    }
    else
    {
        *divider_code = (7 << 3) & SPI_CR1_BR_BIT_MASK;
    }
    if(modulo != 0)
    {
        error = ERROR_WRONG_CLOCK_SET;
    }
    return error;
};


/** Set the peripheral clock phase.
 *
 * \param driver: Pointer to the SPI driver.
 * \param data_buffer: Clock phase value.
 *
 * \return : Error code or ERROR_OK.
 *
 */
static t_error_handling set_clock_phase(const struct t_spi_driver *driver, enum t_clock_phase clock_phase)
{
    t_error_handling error = ERROR_OK;
    if(clock_phase == spi_clk_first)
    {
        driver->priv->reg->CR1 &= ~SPI_CR1_CPHA_BIT_MASK;
    }
    else if(clock_phase == spi_clk_second)
    {
        driver->priv->reg->CR1 |= SPI_CR1_CPHA_BIT_MASK;
    }
    else
    {
        error = ERROR_WRONG_VALUE;
    }
    return error;
}


/** Set the peripheral clock polarity.
 *
 * \param driver: Pointer to the SPI driver.
 * \param data_buffer: Clock polarity value.
 *
 * \return : Error code or ERROR_OK.
 *
 */
static t_error_handling set_clock_polarity(const struct t_spi_driver *driver, enum t_clock_polarity clock_polarity)
{
    t_error_handling error = ERROR_OK;
    if(clock_polarity == spi_clk_rising)
    {
        driver->priv->reg->CR1 &= ~SPI_CR1_CPOL_BIT_MASK;
    }
    else if(clock_polarity == spi_clk_falling)
    {
        driver->priv->reg->CR1 |= SPI_CR1_CPOL_BIT_MASK;
    }
    else
    {
        error = ERROR_WRONG_VALUE;
    }
    return error;
}


/** Set the peripheral frame direction.
 *
 * \param driver: Pointer to the SPI driver.
 * \param frame_direction: Frame direction.
 *
 * \return : Error code or ERROR_OK.
 *
 */
static t_error_handling set_frame_direction(const struct t_spi_driver *driver, enum t_frame_direction frame_direction)
{
    t_error_handling error = ERROR_OK;
    if(frame_direction == spi_frame_msb_first)
    {
        driver->priv->reg->CR1 &= ~SPI_CR1_LSBFIRST_BIT_MASK;
    }
    else if(frame_direction == spi_frame_lsb_first)
    {
        driver->priv->reg->CR1 |= SPI_CR1_LSBFIRST_BIT_MASK;
    }
    else
    {
        error = ERROR_WRONG_VALUE;
    }
    return error;
};


/** Set the peripheral frame length.
 *
 * \param driver: Pointer to the SPI driver.
 * \param frame_length: Frame length value.
 *
 * \return : Error code or ERROR_OK.
 *
 */
static t_error_handling set_frame_length(const struct t_spi_driver *driver, enum t_frame_length frame_length)
{
    t_error_handling error = ERROR_OK;
    if(frame_length == spi_frame_8_bits)
    {
        driver->priv->reg->CR1 &= ~SPI_CR1_DFF_BIT_MASK;
    }
    else if(frame_length == spi_frame_16_bits)
    {
        driver->priv->reg->CR1 |= SPI_CR1_DFF_BIT_MASK;
    }
    else
    {
        error = ERROR_WRONG_VALUE;
    }
    return error;
}


/** Set the frequency in KHz.
 *
 * \param driver: Pointer to the SPI driver.
 * \param freq_khz: Frequency expected in KHz.
 *
 * \return : Error code or ERROR_OK.
 *
 */
static t_error_handling set_frequency(const struct t_spi_driver *driver, uint16_t freq_khz)
{
    t_error_handling error = ERROR_OK;
    uint16_t local_mask = 0;
    error = compute_frequency_divider(driver->priv->clock_frequency,
                                      freq_khz,
                                      (uint8_t*)&local_mask);
    driver->priv->reg->CR1 &= ~SPI_CR1_BR_BIT_MASK;
    driver->priv->reg->CR1 |= local_mask;
    driver->priv->freq_khz = freq_khz;
    return error;
}


/** Update the peripheral configuration.
 *
 * \param driver: Pointer to the SPI driver.
 * \param slave: Pointer to the slave configuration.
 *
 * \return : Error code or ERROR_OK.
 *
 */
static t_error_handling update_spi_configuration(const struct t_spi_driver *driver, struct t_spi_slave *slave)
{
    t_error_handling error = ERROR_OK;

    if(slave->freq_khz != driver->priv->freq_khz)
    {
        error = set_frequency(driver, slave->freq_khz);
        if(error != ERROR_OK)
        {
            goto end;
        }
    }

    error = set_frame_length(driver, slave->frame_length);
    if(error != ERROR_OK)
    {
        goto end;
    }

    error = set_frame_direction(driver, slave->frame_direction);
    if(error != ERROR_OK)
    {
        goto end;
    }
    
    error = set_clock_phase(driver, slave->clock_phase);
    if(error != ERROR_OK)
    {
        goto end;
    }
    
    error = set_clock_polarity(driver, slave->clock_polarity);
    if(error != ERROR_OK)
    {
        goto end;
    }
end:
    return error;
};


void spi_record_slave(struct t_spi_slave *slave)
{
    uint32_t idx_pos = 0;
    uint32_t idx_scan = 0;

    while((slaves_record[idx_pos] != 0) &&
          (idx_pos < (MAX_SPI0_PERIPHERALS + MAX_SPI1_PERIPHERALS)))
    {
        idx_pos++;
    };

    if(idx_pos == 0)
    {
        slaves_record[idx_pos] = slave;
        slaves_record[idx_pos]->id = idx_pos;
    }
    else
    {
        while(idx_scan <= idx_pos)
        {
            if((slaves_record[idx_scan]->freq_khz != slave->freq_khz) ||
               (slaves_record[idx_scan]->frame_length != slave->frame_length) ||
               (slaves_record[idx_scan]->frame_direction != slave->frame_direction) ||
               (slaves_record[idx_scan]->clock_phase != slave->clock_phase) ||
               (slaves_record[idx_scan]->clock_polarity != slave->clock_polarity))
            {
                slaves_record[idx_pos] = slave;
                slaves_record[idx_pos]->id = idx_pos;
                break;
            }
               else
            {
                idx_scan++;
            }
        }
    }
}


t_error_handling spi_transfer(struct t_spi_driver *driver, struct t_spi_slave *slave, struct t_spi_data *data)
{
    t_error_handling error = ERROR_OK;
    uint16_t *write_pointer = &data->write_buffer[0];
    uint16_t *read_pointer = &data->read_buffer[0];
    uint32_t length = data->length;

    if(slave->id != driver->priv->last_config)
    {
        uint8_t index = 0;
        while((slave->id != slaves_record[index]->id) && (index < (MAX_SPI0_PERIPHERALS + MAX_SPI1_PERIPHERALS)))
        {
            index++;
        };

        if(index >= (MAX_SPI0_PERIPHERALS + MAX_SPI1_PERIPHERALS))
        {
            error = 0; /* TBD */
        }

        else
        {
            update_spi_configuration(driver, slave);
            driver->priv->last_config = slave->id;
        }
    };

    cs(slave, LOW);

    while(length > 0)
    {
        driver->priv->reg->DR = *write_pointer;
        while((driver->priv->reg->SR & SPI_SR_TXE_BIT_MASK) != SPI_SR_TXE_BIT_MASK){}
        while((driver->priv->reg->SR & SPI_SR_RXNE_BIT_MASK) != SPI_SR_RXNE_BIT_MASK){}
        *read_pointer = driver->priv->reg->DR;
        write_pointer++;
        read_pointer++;
        length--;
    };

    cs(slave, HIGH);

    return error;
}


void spi_init(struct t_spi_driver *driver, const struct t_spi_config *config)
{
    /* Get the SoC frequency parameters */
    struct t_clock_driver *clock_driver = get_clock_driver();

    /* Link the driver to the configuration structure */
    driver->config = config;

    /* Clear the record table. */
    memset(slaves_record, 0,
           sizeof(struct t_spi_slave[MAX_SPI0_PERIPHERALS + MAX_SPI1_PERIPHERALS]));
    
    /* Associate private instance to the driver */
    driver->priv = &priv[driver->config->instance];

    /* Clear the private structure instance */
    memset(driver->priv, 0, sizeof(struct t_spi_private));

    /* For any SPI instance */
    if(driver->config->instance == 0)
    {
   	    driver->priv->clock_frequency = clock_driver->APB2_clk_freq;
    }
    else if(driver->config->instance == 1)
    {
    	driver->priv->clock_frequency = clock_driver->APB1_clk_freq;
    }

    enable_clock(driver->config->peripheral);

    /* Locate registers to the base address */
    driver->priv->reg = (struct t_spi_regs*)driver->config->base_address;

    /* SPI in master mode */
    driver->priv->reg->CR1 |= SPI_CR1_MSTR_BIT_MASK;

    /* NSS pin is not used */
    driver->priv->reg->CR1 |= (SPI_CR1_SSI_BIT_MASK | SPI_CR1_SSE_BIT_MASK);

    /* Enable SPI Module */
    driver->priv->reg->CR1 |= SPI_CR1_SPE_BIT_MASK;

    /* Initialize last_config to force a configuration initializastion at the first start */
    driver->priv->last_config = UINT8_MAX;
}


void SPI0_IRQHandler(void)
{
    /** SPI0 IRQ handler.
    *
    * \param void : No parameter.
    *
    * \return : No return value.
    */   
}

void SPI1_IRQHandler(void)
{
    /**	SPI1 IRQ handler.
    *
    * \param void : No parameter.
    *
    * \return : No return value.
    */
}

//#endif /* SPI */
