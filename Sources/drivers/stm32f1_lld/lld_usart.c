/*
 * lld_usart.c
 *
 * Created on: Apr 12, 2019
 * Author: Stephane Amans
 *
 * Changes:
 *  - Add DMA support Rx and Tx
 */

/* Include files        */
#include "bsp.h"
#include "queues.h"
#include "usart.h"
#if defined(USART_1) || defined(USART_2)

/* Defines */
#define ENABLE              0x2000
#define TX_ENABLE           0x0008
#define RX_ENABLE           0x0004

#define ENABLE_IDLE_IRQ     0x0010
#define ENABLE_RXNE_IRQ     0x0020
#define ENABLE_TC_IRQ       0x0040
#define ENABLE_TXE_IRQ      0x0080
#define ENABLE_PE_IRQ       0x0100
#define ENABLE_DMA          0x00C0

#define PARITY_ERROR_FLAG   0x0001
#define FRAMING_ERROR_FLAG  0x0002
#define NOISE_ERROR_FLAG    0x0004
#define OVERRUN_ERROR_FLAG  0x0008
#define IDLE_ERROR_FLAG     0x0010
#define RX_NOT_EMPTY_FLAG   0x0020
#define TC_FLAG             0x0040
#define TXE_FLAG            0x0080

#define RX_BUFFER_LENGTH    256
#define TX_BUFFER_LENGTH    256

/* USART private structure definition :        */
struct t_usart_private
{
	bool write_end;
	bool read_end;
	uint8_t *data_buffer_tx;
	uint32_t length_tx;
	uint8_t *data_buffer_rx;
	uint32_t length_rx;
	t_error_handling error;
	struct t_dma_driver *tx_dma;
    struct t_dma_driver *rx_dma;
};

/* Static driver structure. */
static struct t_usart_driver usart_driver[USART_IP_NUMBER];
static struct t_usart_private priv[USART_IP_NUMBER];


/** Get transmission complete flag in interruption and DMA modes.
 *
  * \param usart: Pointer to the USART driver.
 *
 *
 * \return: bool .
 *
 */
static bool tx_complete_irq(struct t_usart_driver *driver)
{
    return driver->priv->write_end;
}

static bool tx_complete_dma(struct t_usart_driver *driver)
{
    bool status = true;
    if(driver->priv->write_end == false)
    {
        status = false;
        if(driver->priv->tx_dma->reg->CNDTR == 0)
        {
            status = true;
            driver->priv->write_end = true;
        }
    }
    return status;
}


/** Get reception complete flag in interruption and DMA modes.
 *
  * \param usart: Pointer to the USART driver.
 *
 *
 * \return: bool.
 *
 */
static bool rx_complete_irq(struct t_usart_driver *driver)
{
    return driver->priv->read_end;
}

static bool rx_complete_dma(struct t_usart_driver *driver)
{
  bool status = true;
  if(driver->priv->read_end == false)
  {
        status = false;
        if(driver->priv->rx_dma->reg->CNDTR == 0)
        {
            status = true;
            driver->priv->read_end = true;
        }
    }
    return status;
}


/** Function to receive bytes data with DMA.
 *
 * \param driver: Pointer to the USART driver.
 * \param data_buffer: Pointer to the data to send.
 * \param data_length: Length of the datas to send.
 *
 * \return: t_error_handling code or ERROR_OK.
 *
 */
static t_error_handling receive_dma(struct t_usart_driver *driver, uint8_t *data_buffer, uint32_t data_length)
{
    t_error_handling error = ERROR_OK;
    if(rx_complete_dma(driver))
    {
        error = dma_transfer(driver->priv->rx_dma, data_buffer, &driver->reg->DR, data_length);
        driver->priv->length_rx = data_length;
        driver->priv->read_end = false;
        driver->reg->CR1 |= RX_ENABLE;
        error = dma_start_transfer(driver->priv->rx_dma);
    }
    else
    {
        error = ERROR_USART_NOT_READY_TO_SEND;
        driver->priv->error = ERROR_USART_NOT_READY_TO_SEND;
    }
    return error;
}


/** Function to receive bytes data with interrupts.
 *
 * \param driver: Pointer to the USART driver.
 * \param data_buffer: Pointer to the data to send.
 * \param data_length: Length of the datas to send.
 *
 * \return: t_error_handling code or ERROR_OK.
 *
 */
static t_error_handling receive_irq(struct t_usart_driver *driver, uint8_t *data_buffer, uint32_t data_length)
{
    t_error_handling error = ERROR_OK;
    if((driver->reg->CR1 & RX_ENABLE) != RX_ENABLE)
    {
        driver->priv->read_end = false;
        driver->priv->data_buffer_rx = data_buffer;
        driver->priv->length_rx = data_length;
        driver->reg->SR &= ~RX_NOT_EMPTY_FLAG;
        driver->reg->CR1 |= (ENABLE_IDLE_IRQ | ENABLE_RXNE_IRQ | ENABLE_PE_IRQ | RX_ENABLE);
    }
    else
    {
        error = ERROR_USART_NOT_READY_TO_SEND;
        driver->priv->error = ERROR_USART_NOT_READY_TO_SEND;
    }
    return error;
}


/** Simple polling function to read bytes data by polling.
 *
 * \param driver: Pointer to the USART driver.
 * \param data_buffer: Pointer to the data to send.
 * \param data_length: Length of the datas to send.
 *
 * \return : Error code or ERROR_OK.
 *
 */
static t_error_handling receive_poll(struct t_usart_driver *driver, uint8_t *data_buffer, uint32_t data_length)
{
    t_error_handling error = ERROR_OK;
    driver->priv->error = ERROR_OK;
    driver->priv->read_end = false;
    driver->reg->CR1 |= RX_ENABLE;
    for(uint32_t index = 0; index < data_length; index++)
    {
        while((driver->reg->SR & RX_NOT_EMPTY_FLAG) == 0){}
        *data_buffer = driver->reg->DR;
        if((driver->reg->SR & PARITY_ERROR_FLAG) == PARITY_ERROR_FLAG)
        {
            error = ERROR_USART_PARITY;
            break;
        }
        else if((driver->reg->SR & FRAMING_ERROR_FLAG) == FRAMING_ERROR_FLAG)
        {
            error = ERROR_USART_FRAMING;
            break;
        }
        else if((driver->reg->SR & NOISE_ERROR_FLAG) == NOISE_ERROR_FLAG)
        {
            error = ERROR_USART_NOISE;
            break;
        }
        else if((driver->reg->SR & OVERRUN_ERROR_FLAG) == OVERRUN_ERROR_FLAG)
        {
            error = ERROR_USART_OVERRUN;
            break;
        }
        else
        {
        }
        data_buffer++;
    }
    driver->reg->CR1 &= ~RX_ENABLE;
    driver->priv->read_end = true;
    driver->priv->error = error;
    return error;
}


/** Function to transmit a bytes data with DMA.
 *
 * \param usart: Pointer to the USART driver.
 * \param data_buffer: Pointer to the data location.
 * \param data_length: Length of the datas to send.
 *
* \return: t_error_handling code or ERROR_OK.
 *
 */
static t_error_handling transmit_dma(struct t_usart_driver *driver, uint8_t *data_buffer, uint32_t data_length)
{
    t_error_handling error = ERROR_OK;
    if(tx_complete_dma(driver))
    {
        error = dma_transfer(driver->priv->tx_dma, data_buffer, &driver->reg->DR, data_length);
        driver->priv->length_tx = data_length;
        driver->priv->write_end = false;
        driver->reg->CR1 |= TX_ENABLE;
        error = dma_start_transfer(driver->priv->tx_dma);
    }
    else
    {
        error = ERROR_USART_NOT_READY_TO_SEND;
        driver->priv->error = ERROR_USART_NOT_READY_TO_SEND;
    }
return error;
}


/** Function to transmit bytes data with interrupts.
 *
 * \param usart: Pointer to the USART driver.
 * \param data_buffer: Pointer to the data location.
 * \param data_length: Length of the datas to send.
 *
 * \return: t_error_handling code or ERROR_OK.
 *
 */
static t_error_handling transmit_irq(struct t_usart_driver *driver, uint8_t *data_buffer, uint32_t data_length)
{
    t_error_handling error = ERROR_OK;
    if((driver->reg->CR1 & TX_ENABLE) != TX_ENABLE)
    {
        driver->priv->write_end = false;
        driver->priv->data_buffer_tx = data_buffer;
        driver->priv->length_tx = data_length;
        driver->reg->CR1 |= TX_ENABLE;
        driver->reg->SR = 0x00;
        driver->reg->DR = *data_buffer;
        priv->data_buffer_tx++;
        priv->length_tx--;
        driver->reg->CR1 |= (ENABLE_IDLE_IRQ | ENABLE_TC_IRQ | ENABLE_TXE_IRQ | ENABLE_PE_IRQ);
    }
    else
    {
        error = ERROR_USART_NOT_READY_TO_SEND;
        driver->priv->error = ERROR_USART_NOT_READY_TO_SEND;
    }
return error;
}

/** Simple blocking function to transmit bytes data.
 *
 * \param usart: Pointer to the USART driver.
 * \param data_buffer: Pointer to the data location.
 * \param data_length: Length of the datas to send.
 *
 * \return: t_error_handling code or ERROR_OK.
 *
 */
static t_error_handling transmit_poll(struct t_usart_driver *driver, uint8_t *data_buffer, uint32_t data_length)
{
    t_error_handling error = ERROR_OK;
    driver->priv->write_end = false;
    driver->reg->CR1 |= TX_ENABLE;
    for(uint32_t index = 0; index < data_length; index++)
    {
        driver->reg->DR = *data_buffer;
        while((driver->reg->SR & TXE_FLAG) != TXE_FLAG){}
        data_buffer++;
    }
    while((driver->reg->SR & TC_FLAG) != TC_FLAG){}
    driver->reg->CR1 &= ~TX_ENABLE;
    driver->priv->error = error;
    return error;
}

/** Compute divider from the bus frequency.
 *
 * \param bus_frequency: USART bus frequency value.
 *
 *
 * \return: t_error_handling code or ERROR_OK.
 *
 */
static uint16_t compute_baudrate_divider(uint32_t bus_frequency, uint32_t baudrate)
{
    uint32_t local_divider = baudrate * 16;
    uint16_t mantissa = bus_frequency / local_divider;
    uint8_t fraction = (uint8_t)(((bus_frequency % local_divider) * 16) / local_divider);

    if(fraction > 16)
    {
        mantissa++;
        fraction -= 16;
    }
    return ((mantissa << 4) | (fraction & 0x0F));
}


t_error_handling usart_init(struct t_usart_driver *driver, const struct t_usart_config *config)
{
    t_error_handling error  = ERROR_OK;
    uint32_t clock_frequency = 0;

    memset(driver, 0, sizeof(struct t_usart_driver));

    driver->reg = config->reg;
    if(driver->reg == USART1)
    {
   	    enable_clock(USART_01);
    }
    else if(driver->reg == USART2)
    {
    	enable_clock(USART_02);
    }
    struct t_clock_driver *clock_driver = get_clock_driver();

    if(driver->reg == USART1)
    {
        driver->uart_number = 1;
        clock_frequency = clock_driver->APB2_clk_freq; //get_apb2_clock(clock_driver);
        driver->priv = &priv[0];
        memset(driver->priv, 0, sizeof(struct t_usart_private));
    }
    else if(driver->reg == USART2)
    {
        driver->uart_number = 2;
        clock_frequency = clock_driver->APB1_clk_freq; //get_apb1_clock(clock_driver);
        driver->priv = &priv[1];
        memset(driver->priv, 0, sizeof(struct t_usart_private));
    }
    else
    {
        error = ERROR_DRIVER_NOT_INITIALIZED;
    }

    driver->priv->write_end = true;
    driver->priv->read_end = true;

    driver->reg->CR1 = 0;                  /* Reset the register         */
    driver->reg->CR1 |= ENABLE;            /* Enables the module.        */
    driver->reg->BRR = compute_baudrate_divider(clock_frequency, config->baudrate);

    driver->reg->CR1 |= config->length;    /* Fix frame length.          */
    driver->reg->CR1 |= config->parity;    /* Select parity. ;           */
    driver->reg->CR2 |= config->stop;      /* Configure stop bit length. */

    if(config->mode == usart_poll)
    {
        driver->methods.transmit = transmit_poll;
        driver->methods.receive = receive_poll;
    }
    else if(config->mode == usart_irq)
    {
        if(driver->uart_number == 1)
        {
            enable_nvic_irq(IRQ_USART_1);
            set_nvic_priority(IRQ_USART_1, config->irq_dma.priority);
        }
        else if(driver->uart_number == 2)
        {
            enable_nvic_irq(IRQ_USART_2);
            set_nvic_priority(IRQ_USART_2, config->irq_dma.priority);
        }
        driver->methods.transmit = transmit_irq;
        driver->methods.receive = receive_irq;
        driver->methods.tx_complete = tx_complete_irq;
        driver->methods.rx_complete = rx_complete_irq;
    }
    else if(config->mode == usart_dma)
    {
        driver->reg->CR3 = ENABLE_DMA;                          /* Enable DMA.               */
        driver->priv->tx_dma = config->irq_dma.tx_dma_channel;  /* Pointer to TX DMA driver. */
        driver->priv->rx_dma = config->irq_dma.rx_dma_channel;  /* Pointer to RX DMA driver. */
        driver->methods.transmit = transmit_dma;
        driver->methods.receive = receive_dma;
        driver->methods.tx_complete = tx_complete_dma;
        driver->methods.rx_complete = rx_complete_dma;
    }
    return error;
}

struct t_usart_driver *usart_get_driver(uint8_t usart_number)
{
    struct t_usart_driver *driver = 0;
    if((usart_number > 0)  && (usart_number <= USART_IP_NUMBER))
    {
        driver = &usart_driver[usart_number - 1];
    }
    return driver;
}

t_error_handling usart_get_error_status(struct t_usart_driver *driver)
{
    return driver->priv->error;
}


void USART1_IRQHandler(void)        			/* USART1 global interrupt                          */
{
    /**	USART1 IRQ handler.
    *
    * \param void : No parameter.
    *
    * \return : No return value.
    */
    uint8_t sr_register = usart_driver[0].reg->SR;
    if((sr_register & PARITY_ERROR_FLAG) == PARITY_ERROR_FLAG)
    {
        usart_driver[0].priv->error = ERROR_USART_PARITY;
    }
    else if((sr_register & FRAMING_ERROR_FLAG) == FRAMING_ERROR_FLAG)
    {
        usart_driver[0].priv->error  = ERROR_USART_FRAMING;
    }
    else if((sr_register & NOISE_ERROR_FLAG) == NOISE_ERROR_FLAG)
    {
        usart_driver[0].priv->error  = ERROR_USART_NOISE;
    }
    else if((sr_register & OVERRUN_ERROR_FLAG) == OVERRUN_ERROR_FLAG)
    {
        usart_driver[0].priv->error  = ERROR_USART_OVERRUN;
    }
    else if((sr_register & RX_NOT_EMPTY_FLAG) == RX_NOT_EMPTY_FLAG)
    {
        *usart_driver[0].priv->data_buffer_rx = usart_driver[0].reg->DR;
        priv->length_rx--;
        if(priv->length_rx == 0)
        {
            usart_driver[0].reg->CR1 &= ~(ENABLE_IDLE_IRQ | RX_NOT_EMPTY_FLAG | ENABLE_PE_IRQ | RX_ENABLE);
            usart_driver[0].priv->read_end = true;
        }
        else
        {
            usart_driver[0].priv->data_buffer_rx++;
        }
    }
    else if(((sr_register & TXE_FLAG) == TXE_FLAG) &&
             (usart_driver[0].priv->length_tx > 0))
    {
        usart_driver[0].reg->DR = *usart_driver[0].priv->data_buffer_tx;
        usart_driver[0].priv->data_buffer_tx++;
        usart_driver[0].priv->length_tx--;
    }
    else if((sr_register & TC_FLAG) == TC_FLAG)
    {
        usart_driver[0].reg->CR1 &= ~TX_ENABLE;
        usart_driver[0].reg->CR1 &= ~(ENABLE_IDLE_IRQ | ENABLE_TC_IRQ | ENABLE_TXE_IRQ | ENABLE_PE_IRQ);
        usart_driver[0].priv->write_end = true;
    }
    else
    {
    }
    clear_pending_nvic_irq(IRQ_USART_1); /* Clear any USART 1 NVIC pending interrupt.   */
}

void USART2_IRQHandler(void)
{
    /**	USART2 IRQ handler.
    *
    * \param void : No parameter.
    *
    * \return : No return value.
    */

    uint8_t sr_register = usart_driver[1].reg->SR;
    if((sr_register & PARITY_ERROR_FLAG) == PARITY_ERROR_FLAG)
    {
        usart_driver[1].priv->error = ERROR_USART_PARITY;
    }
    else if((sr_register & FRAMING_ERROR_FLAG) == FRAMING_ERROR_FLAG)
    {
        usart_driver[1].priv->error  = ERROR_USART_FRAMING;
    }
    else if((sr_register & NOISE_ERROR_FLAG) == NOISE_ERROR_FLAG)
    {
        usart_driver[1].priv->error  = ERROR_USART_NOISE;
    }
    else if((sr_register & OVERRUN_ERROR_FLAG) == OVERRUN_ERROR_FLAG)
    {
        usart_driver[1].priv->error  = ERROR_USART_OVERRUN;
    }
    else if((sr_register & RX_NOT_EMPTY_FLAG) == RX_NOT_EMPTY_FLAG)
    {
        *usart_driver[1].priv->data_buffer_rx = usart_driver[1].reg->DR;
        priv->length_rx--;
        if(priv->length_rx == 0)
        {
            usart_driver[1].reg->CR1 &= ~(ENABLE_IDLE_IRQ | RX_NOT_EMPTY_FLAG | ENABLE_PE_IRQ | RX_ENABLE);
            usart_driver[1].priv->read_end = true;
        }
        else
        {
            usart_driver[1].priv->data_buffer_rx++;
        }
    }
    else if(((sr_register & TXE_FLAG) == TXE_FLAG) &&
             (usart_driver[1].priv->length_tx > 0))
    {
        usart_driver[1].reg->DR = *usart_driver[1].priv->data_buffer_tx;
        usart_driver[1].priv->data_buffer_tx++;
        usart_driver[1].priv->length_tx--;
    }
    else if((sr_register & TC_FLAG) == TC_FLAG)
    {
        usart_driver[1].reg->CR1 &= ~TX_ENABLE;
        usart_driver[1].reg->CR1 &= ~(ENABLE_IDLE_IRQ | ENABLE_TC_IRQ | ENABLE_TXE_IRQ | ENABLE_PE_IRQ);
        usart_driver[1].priv->write_end = true;
    }
    else
    {
    }
    clear_pending_nvic_irq(IRQ_USART_2); /* Clear any USART 1 NVIC pending interrupt.   */
}

#endif /* USART */
