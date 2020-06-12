/*
 * test_dma.c
 *
 * Created on: Jun 9, 2020
 * Author: Stephane Amans
 */

/* Include files.        */
#include "test.h"


/* Defines */
#define TOTAL_TEST_NUMBER   5
#define BUFFER_LENGTH_256   256


/* Declare test structure. */
struct tests
{
    uint8_t gif_irq_general_interrupt_flag;
    uint8_t tcif_irq_transfer_complete_interrupt_flag;
    uint8_t htif_irq_half_transfer_interrupt_flag;
    uint8_t teif_irq_transfer_error_interrupt_flag;
    uint32_t error_counter;
    test_issue result;
};


/* Test results structure declaration and implementation. */
struct test_results
{
    struct tests *test[TOTAL_TEST_NUMBER];
};
struct test_results results;


/** Initialize 8 bits tables.
 *
 * \param table_write: Pointer to the table containing the source data.
 * \param table_read: Pointer to the location to store the data transfered.
 * \param length: Total buffer length.
 *
 * \return: void.
 *
 */
static void initialize_8_bits_tables(uint8_t *table_write, uint8_t *table_read, uint32_t length);


/** Initialize 32 bits tables.
 *
 * \param table_write: Pointer to the table containing the source data.
 * \param table_read: Pointer to the location to store the data transfered.
 * \param length: Total buffer length.
 *
 * \return: void.
 *
 */
static void initialize_32_bits_tables(uint32_t *table_write, uint32_t *table_read, uint32_t length);


/** Initialize test structure.
 *
 * \param results: Pointer to the test report structure.
 *
 * \return: void.
 *
 */
static void initialize_test_structure(struct test_results *results);


/** Initialize driver.
 *
 * \param dma_ch: Pointer to the dma channel driver.
 * \param irq: Parameter to validate or invalidate irq (1 to enable).
 * \param callback: Pointer to the callback function.
 *
 * \return: void.
 *
 */
static void initialize_driver(t_dma_channel_cfg *dma_ch, dma_data_type data_type, uint8_t irq,
                              void(*callback)(uint8_t*));


/** 8 bits memory to memory transfert.
 *
 * \param dma_ch: Pointer to the dma channel driver.
 * \param table_write: Pointer to the table containing the source data.
 * \param table_read: Pointer to the table containing the destination data.
 * \param test: Pointer to the test report structure.
 *
 * \return: void.
 *
 */
static void test_mem2mem_dma_8bits(t_dma_channel_cfg *dma_ch, uint8_t *table_write, uint8_t *table_read,
                                   struct tests *test);


/** 32 bits memory to memory transfert.
 *
 * \param dma_ch: Pointer to the dma channel driver.
 * \param table_write: Pointer to the table containing the source data.
 * \param table_read: Pointer to the table containing the destination data.
 * \param test: Pointer to the test report structure.
 *
 * \return: void.
 *
 */
static void test_mem2mem_dma_32bits(t_dma_channel_cfg *dma_ch, uint32_t *table_write, uint32_t *table_read,
                                    struct tests *test);


/** Check data integrity and fill test structure.
 *
 * The test acceptance is based on data integrity, flag values and number of iterations.
 *
 * \param dma_ch: Pointer to the dma channel driver.
 * \param test: Pointer to the test report structure.
 *
 * \return: void.
 *
 */
static void check_data_integrity(t_dma_channel_cfg *dma_ch, struct tests *test);


/** Call back function, if irq enabled.
 *
 * \param irq_source: Pointer to write the irq flags registers.
 *
 * \return: void.
 *
 */
static void dma_callback_1(uint8_t *irq_source);


/** Call back function, if irq enabled.
 *
 * \param irq_source: Pointer to write the irq flags registers.
 *
 * \return: void.
 *
 */
static void dma_callback_2(uint8_t *irq_source);


/** Test synthesis.
 *
 * This function checks the group and manage the result of all queues tests.
 *
 * \param results: Pointer to the  result structure.
 *
 * \return: Error code.
 *
 */
static t_error_handling test_synthesis(struct test_results *results);


t_error_handling test_dma(void)
{
    /* Declarations. */
    uint8_t write_8bits[BUFFER_LENGTH_256];    /* Transfer source 8 bits date table.           */
    uint8_t read_8bits[BUFFER_LENGTH_256];     /* Transfer destination location 8 bits table.  */
    uint32_t write_32bits[BUFFER_LENGTH_256];  /* Transfer source 32 bits date table.          */
    uint32_t read_32bits[BUFFER_LENGTH_256];   /* Transfer destination location 32 bits table. */

    /* Implement driver structure. */
    t_dma_channel_cfg dma_ch1, dma_ch2, dma_ch3;
    dma_ch1.reg = DMA1_Ch1;
    dma_ch2.reg = DMA1_Ch2;
    dma_ch3.reg = DMA1_Ch3;

    /* Initializations. */
    struct tests test1, test2, test3;
    results.test[0] = &test1;
    results.test[1] = &test2;
    results.test[2] = &test3;
    results.test[3] = 0;
    results.test[4] = 0;
    initialize_test_structure(&results);
    initialize_driver(&dma_ch1, bits_8, 0, 0);
    initialize_driver(&dma_ch2, bits_8, 1, dma_callback_1);
    initialize_driver(&dma_ch3, bits_32, 1, dma_callback_2);
    dma_init(&dma_ch1);
    dma_init(&dma_ch2);
    dma_init(&dma_ch3);

    /* Run test 1: Transfer 8 bits half buffer without interruptions. */
    initialize_8_bits_tables(&write_8bits[0], &read_8bits[0], BUFFER_LENGTH_256);
    test_mem2mem_dma_8bits(&dma_ch1, &write_8bits[0], &read_8bits[0], results.test[0]);
    check_data_integrity(&dma_ch1, results.test[0]);

    /* Run test 2: Transfer 8 bits half buffer with interruptions. */
    initialize_8_bits_tables(&write_8bits[0], &read_8bits[0], BUFFER_LENGTH_256);
    test_mem2mem_dma_8bits(&dma_ch2, &write_8bits[0], &read_8bits[0], results.test[1]);
    check_data_integrity(&dma_ch2, results.test[1]);

    /* Run test 3: Transfer 32 bits half buffer with interruptions. */
    initialize_32_bits_tables(&write_32bits[0], &read_32bits[0], BUFFER_LENGTH_256);
    test_mem2mem_dma_32bits(&dma_ch3, &write_32bits[0], &read_32bits[0], results.test[2]);
    check_data_integrity(&dma_ch3, results.test[2]);

    return test_synthesis(&results);
}


static void initialize_8_bits_tables(uint8_t *table_write, uint8_t *table_read, uint32_t length)
{
    for(uint16_t index = 0; index < length; index++)
    {
        *table_write = index;
        *table_read = 0;
        table_write++;
        table_read++;
    }
}


static void initialize_32_bits_tables(uint32_t *table_write, uint32_t *table_read, uint32_t length)
{
    for(uint16_t index = 0; index < length; index++)
    {
        *table_write = 16777216 * index;
        *table_read = 0;
        table_write++;
        table_read++;
    }
}


static void initialize_test_structure(struct test_results *results)
{
    uint8_t index = 0;
    while(results->test[index] != 0)
    {
        results->test[index]->gif_irq_general_interrupt_flag = 0;
        results->test[index]->tcif_irq_transfer_complete_interrupt_flag = 0;
        results->test[index]->htif_irq_half_transfer_interrupt_flag = 0;
        results->test[index]->teif_irq_transfer_error_interrupt_flag = 0;
        results->test[index]->error_counter = 0;
        index++;
    }
}


static void initialize_driver(t_dma_channel_cfg *dma_ch, dma_data_type data_type, uint8_t irq,
                              void(*callback)(uint8_t*))
{
    uint8_t enable = dma_disable;
    if(irq == 1)
    {
        enable = dma_enable;
    }
    dma_ch->mem2mem = dma_enable;
    dma_ch->dma_priority = low;
    dma_ch->mem_data_type = data_type;
    dma_ch->memory_zone_size = (BUFFER_LENGTH_256 / 2);
    dma_ch->periph_data_type = data_type;
    dma_ch->memory_increment = dma_enable;
    dma_ch->peripheral_increment = dma_enable;
    dma_ch->read_from_memory = dma_enable;
    dma_ch->irq.transfer_error_interrupt = enable;
    dma_ch->irq.half_transfer_interrupt = enable;
    dma_ch->irq.transfert_complete_interrupt = enable;
    dma_ch->irq.priority = 0;
    dma_ch->irq.callback = callback;
}


static void test_mem2mem_dma_8bits(t_dma_channel_cfg *dma_ch, uint8_t *table_write, uint8_t *table_read,
                                   struct tests *test)
{
    uint8_t *ptr_write = table_write;   /* Pointer to the table write. */
    uint8_t *ptr_read = table_read;     /* Pointer to the table read.  */

    dma_memcpy(dma_ch, table_read, table_write, dma_ch->mem_data_type, dma_ch->memory_zone_size);
    dma_start_transfer(dma_ch);

    /* Check data integrity. */
    for(uint16_t index = 0; index < dma_ch->memory_zone_size; index++)
    {
        if(*ptr_write != *ptr_read)
        {
            test->error_counter++;
        }
        ptr_write++;
        ptr_read++;
    }

    for(uint16_t index = dma_ch->memory_zone_size; index < BUFFER_LENGTH_256; index++)
    {
        if(*ptr_read != 0)
        {
            test->error_counter++;
        }
        ptr_write++;
        ptr_read++;
    }
}


static void test_mem2mem_dma_32bits(t_dma_channel_cfg *dma_ch, uint32_t *table_write, uint32_t *table_read,
                                    struct tests *test)
{
    uint32_t *ptr_write = table_write;   /* Pointer to the table write. */
    uint32_t *ptr_read = table_read;     /* Pointer to the table read.  */

    dma_memcpy(dma_ch, table_read, table_write, dma_ch->mem_data_type, dma_ch->memory_zone_size);
    dma_start_transfer(dma_ch);

    /* Check data integrity. */
    for(uint16_t index = 0; index < dma_ch->memory_zone_size; index++)
    {
        if(*ptr_write != *ptr_read)
        {
            test->error_counter++;
        }
        ptr_write++;
        ptr_read++;
    }

    for(uint16_t index = dma_ch->memory_zone_size; index < BUFFER_LENGTH_256; index++)
    {
        if(*ptr_read != 0)
        {
            test->error_counter++;
        }
        ptr_write++;
        ptr_read++;
    }
}


static void check_data_integrity(t_dma_channel_cfg *dma_ch, struct tests *test)
{
    uint8_t irq = 0;
	if((dma_ch->irq.half_transfer_interrupt == 1) && (dma_ch->irq.transfer_error_interrupt) &&
        (dma_ch->irq.transfert_complete_interrupt == 1))
    {
        irq = 1;
    }

    if((irq == 1) && (test->error_counter == 0) &&
        (test->gif_irq_general_interrupt_flag == 1) &&
        (test->tcif_irq_transfer_complete_interrupt_flag == 1) &&
        (test->htif_irq_half_transfer_interrupt_flag == 1) &&
        (test->teif_irq_transfer_error_interrupt_flag == 0))
    {
        test->result = PASS;
    }
    else if((irq == 0) && (test->error_counter == 0) &&
        (test->gif_irq_general_interrupt_flag == 0) &&
        (test->tcif_irq_transfer_complete_interrupt_flag == 0) &&
        (test->htif_irq_half_transfer_interrupt_flag == 0) &&
        (test->teif_irq_transfer_error_interrupt_flag == 0))
    {
        test->result = PASS;
    }
    else
    {
        test->result = FAIL;
    }
}


static t_error_handling test_synthesis(struct test_results *results)
{
    uint8_t index = 0;
    t_error_handling result = OK;
    while(results->test[index] != 0)
    {
        result += results->test[index]->result;
        index++;
    }
    return result;
}

static void dma_callback_1(uint8_t *irq_source)
{
    results.test[1]->gif_irq_general_interrupt_flag |= (*irq_source & 0x01);
    results.test[1]->tcif_irq_transfer_complete_interrupt_flag |= ((*irq_source >> 1) & 0x01);
    results.test[1]->htif_irq_half_transfer_interrupt_flag |= ((*irq_source >> 2) & 0x01);
    results.test[1]->teif_irq_transfer_error_interrupt_flag |= ((*irq_source >> 3) & 0x01);
}


static void dma_callback_2(uint8_t *irq_source)
{
    results.test[2]->gif_irq_general_interrupt_flag |= (*irq_source & 0x01);
    results.test[2]->tcif_irq_transfer_complete_interrupt_flag |= ((*irq_source >> 1) & 0x01);
    results.test[2]->htif_irq_half_transfer_interrupt_flag |= ((*irq_source >> 2) & 0x01);
    results.test[2]->teif_irq_transfer_error_interrupt_flag |= ((*irq_source >> 3) & 0x01);
}

