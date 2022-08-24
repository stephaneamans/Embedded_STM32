#include "platform_configuration.h"

struct t_nrf24l01_driver nrf24l01 =
{
    .spi                            = &spi1,
    .ce                             = &pa3,
    .irq                            = &pa2,
    .spi_parameters.cs              = &pa4,
    .spi_parameters.freq_khz        = 8000,
    .spi_parameters.data_length     = spi_data_8_bits,
    .spi_parameters.frame_direction = spi_frame_msb_first,
    .spi_parameters.clock_phase     = spi_clk_first,
    .spi_parameters.clock_polarity  = spi_clk_rising,
    .ic_setup.mask_rx_dr_irq        = true,
    .ic_setup.mask_tx_ds_irq        = true,
    .ic_setup.mask_max_rt_irq       = true,
    .ic_setup.crc                   = nrf24l01_none,
    .ic_setup.startup_receiver      = false,
    .ic_setup.address_width         = nrf24l01_3bytes,
    .rf_setup.air_data_rate         = nrf24l01_air_datarate_1mbps,
    .rf_setup.tx_output_power       = nrf24l01_m18dBm,
    .rf_setup.high_current          = false,
};
