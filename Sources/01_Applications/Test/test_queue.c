/*
 * test_queue.c
 *
 * Created on: Jun 3, 2020
 * Author: Stephane Amans
 */

/* Include files.        */
#include "test.h"


/* Defines */
#define TOTAL_TEST_NUMBER   5
#define BUFFER_LENGTH_64   64
#define BUFFER_LENGTH_256   256


/* Implement test queues. */
DEFINE_QUEUE(test_queue, uint8_t, BUFFER_LENGTH_256)
IMPLEMENT_QUEUE(test_queue, uint8_t, BUFFER_LENGTH_256)


/* Declare test structure. */
typedef struct
{
    uint32_t iterations_write;
    t_error_handling flag_write;
    uint32_t iterations_read;
    t_error_handling flag_read;
    uint32_t error_counter;
    test_issue result;
}tests;


/* Test results structure declaration and implementation. */
struct test_results
{
    tests *test[TOTAL_TEST_NUMBER];
};
struct test_results results;


/** Initialize tables.
 *
 * \param table_write: Pointer to the table containing the data to write in the queue.
 * \param table_read: Pointer to the location to store the data read.
 * \param length: Total buffer length.
 * \param test: Pointer to the test report structure.
 *
 * \return: void.
 *
 */
static void initialize_tables(uint8_t *table_write, uint8_t *table_read, uint32_t length,
                              struct test_results *test);


/** Write and read the queue with checking the data.
 *
 * The test acceptance is based on data integrity, flag values and number of iterations.
 *
 * \param queue: Pointer to the queue.
 * \param table_write: Pointer to the table containing the data to write in the queue.
 * \param table_read: Pointer to the location to store the data read.
 * \param number_write: Number of samples written in the queue.
 *                      If number > queue_length, the queue full flag is taken.
 * \param number_read: Number of samples read in the queue.
 *                     If number > queue_length, the queue empty flag is taken.
 * \param test: Pointer to the test report structure.
 *
 * \return: void.
 *
 */
static void test_check_fill_x_queue(t_test_queue *queue, uint8_t *table_write, uint8_t *table_read,
                                    uint32_t number_write, uint32_t number_read, tests *test);


/** Write and read the queue without checking any data.
 *
 * \param queue: Pointer to the queue.
 * \param table_write: Pointer to the table containing the data to write in the queue.
 * \param table_read: Pointer to the location to store the data read.
 * \param number_write: Number of samples written in the queue.
 *                      If number > queue_length, the queue full flag is taken.
 * \param number_read: Number of samples read in the queue.
 *                     If number > queue_length, the queue empty flag is taken.
 *
 * \return: void.
 *
 */
static void test_simple_read_write_queue(t_test_queue *queue, uint8_t *table_write, uint8_t *table_read,
                                         uint32_t number_write, uint32_t number_read);


/** Test acceptance.
 *
 * This function checks the acceptance critarias.
 *
 * \param cycle_number_write: Number of write cycles.
 * \param cycle_number_read: Number of read cycles.
 * \param queue_length: Buffer queue depth.
 * \param test: Pointer to the test report structure.
 *
 * \return: void.
 *
 */
static void test_acceptance(uint32_t cycle_number_write, uint32_t cycle_number_read, uint32_t queue_length,
                            tests *test);


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


t_error_handling test_queue(void)
{
    /* Declarations. */
    uint8_t data_to_write[BUFFER_LENGTH_256];                /* Reference date table.       */
    uint8_t data_to_read[BUFFER_LENGTH_256];                 /* Read location table.        */
    t_test_queue queue;                                      /* Implement queue instance.   */
    tests test1, test2, test3, test4;

    results.test[0] = &test1;
    results.test[1] = &test2;
    results.test[2] = &test3;
    results.test[3] = &test4;
    results.test[4] = 0;

    initialize_tables(&data_to_write[0], &data_to_read[0], BUFFER_LENGTH_256, &results);
    test_queue_init(&queue);

    /* Run test 1: Fill then read a half queue. */
    test_check_fill_x_queue(&queue, &data_to_write[0], &data_to_read[0], 127, 127, results.test[0]);
    test_acceptance(127, 127, BUFFER_LENGTH_256, results.test[0]);

    /* Run test 2: Fill then read full queue. */
    test_check_fill_x_queue(&queue, &data_to_write[0], &data_to_read[0], 300, 300, results.test[1]);
    test_acceptance(300, 300, BUFFER_LENGTH_256, results.test[1]);

    /* Run test 3: Full fill the queue, then read a half queue. */
    test_check_fill_x_queue(&queue, &data_to_write[0], &data_to_read[0], 300, 100, results.test[2]);
    test_acceptance(300, 100, BUFFER_LENGTH_256, results.test[2]);

    /* Empty the queue. */
    test_simple_read_write_queue(&queue, &data_to_write[0], &data_to_read[0], 0, 200);

    /* Run test 4: Randomly full and read the queue. */
    test_simple_read_write_queue(&queue, &data_to_write[0], &data_to_read[0], 100, 50);
    test_simple_read_write_queue(&queue, &data_to_write[0], &data_to_read[0], 100, 0);
    test_simple_read_write_queue(&queue, &data_to_write[0], &data_to_read[0], 10, 100);
    test_simple_read_write_queue(&queue, &data_to_write[0], &data_to_read[0], 20, 80);
    test_check_fill_x_queue(&queue, &data_to_write[0], &data_to_read[0], 200, 200, results.test[3]);
    test_acceptance(200, 200, BUFFER_LENGTH_256, results.test[3]);

    return test_synthesis(&results);
}


static void initialize_tables(uint8_t *table_write, uint8_t *table_read, uint32_t length,
                              struct test_results *results)
{
    /* Initialize tables. */
    for(uint16_t index = 0; index < length; index++)
    {
        *table_write = index;
        *table_read = 0;
        table_write++;
        table_read++;
    }

    /* Initialize test results structure. */
    uint8_t index = 0;
    while(results->test[index] != 0)
    {
        results->test[index]->iterations_write = 0;
        results->test[index]->flag_write = OK;
        results->test[index]->iterations_read = 0;
        results->test[index]->flag_write = OK;
        results->test[index]->error_counter = 0;
        index++;
    }
}


static void test_check_fill_x_queue(t_test_queue *queue, uint8_t *table_write, uint8_t *table_read,
		                            uint32_t number_write, uint32_t number_read, tests *test)
{
    t_error_handling flag = OK;         /* Error flag to manage queue. */
    uint32_t iteration = 0;             /* Iteration counter.          */
    uint8_t *ptr_write = table_write;   /* Pointer to the table write. */
    uint8_t *ptr_read = table_read;     /* Pointer to the table read.  */

    /* Fill the queue until it is empty. */
    while((flag == OK) && (iteration < number_write))
    {
        flag = test_queue_write(queue, ptr_write);
        if(flag == OK)
        {
            ptr_write++;
            iteration++;
        }
    }

    test->iterations_write = iteration; /* Log iteration result.            */
    test->flag_write = flag;            /* Log flag result.                 */
    flag = OK;                          /* Re initialize the flag.          */
    iteration = 0;                      /* Re initialize iteration counter. */

    /* Read the queue until it is empty. */
    while((flag == OK) && (iteration < number_read))
    {
        flag = test_queue_read(queue, ptr_read);
        if(flag == OK)
        {
            ptr_read++;
            iteration++;
        }
    }

    /* Log test results. */
    test->iterations_read = iteration; /* Log iteration result.            */
    test->flag_read = flag;            /* Log flag result.                 */

    ptr_write = table_write;   /* Re initialize pointer to the table write. */
    ptr_read = table_read;     /* Re initialize pointer to the table read.  */

    /* Check data integrity. */
    for(uint16_t index = 0; index < iteration; index++)
    {
        if(*ptr_write != *ptr_read)
        {
             test->error_counter++;
        }
        ptr_write++;
        ptr_read++;
    }
}


static void test_simple_read_write_queue(t_test_queue *queue, uint8_t *table_write, uint8_t *table_read,
                                         uint32_t number_write, uint32_t number_read)
{
    t_error_handling flag = OK;         /* Error flag to manage queue. */
    uint32_t iteration = 0;             /* Iteration counter.          */
    uint8_t *ptr_write = table_write;   /* Pointer to the table write. */
    uint8_t *ptr_read = table_read;     /* Pointer to the table read.  */

    /* Fill the queue until it is empty. */
    while((flag == OK) && (iteration < number_write))
    {
        flag = test_queue_write(queue, ptr_write);
        if(flag == OK)
        {
            ptr_write++;
            iteration++;
        }
    }

    flag = OK;                                  /* Re initialize the flag.          */
    iteration = 0;                              /* Re initialize iteration counter. */

    /* Read the queue until it is empty. */
    while((flag == OK) && (iteration < number_read))
    {
        flag = test_queue_read(queue, ptr_read);
        if(flag == OK)
        {
            ptr_read++;
            iteration++;
        }
    }
}


static void test_acceptance(uint32_t cycle_number_write, uint32_t cycle_number_read, uint32_t queue_length,
                            tests *test)
{
    t_error_handling flag_write_ref;    /* Write test reference for test acceptance. */
    t_error_handling flag_read_ref;     /* Read test reference for test acceptance.  */
    uint32_t cyc_numb_write_ref;        /* Reference write cycles number.            */
    uint32_t cyc_numb_read_ref;         /* Reference read cycles number.             */

    if(cycle_number_write < queue_length)
    {
        flag_write_ref = OK;
        cyc_numb_write_ref = cycle_number_write;
    }
    else
    {
        flag_write_ref = ERROR_QUEUE_FULL;
        cyc_numb_write_ref = queue_length - 1;
    }

    if(cycle_number_read < queue_length)
    {
      	flag_read_ref = OK;
       	cyc_numb_read_ref = cycle_number_read;
    }
    else
    {
        flag_read_ref = ERROR_QUEUE_EMPTY;
        cyc_numb_read_ref = queue_length - 1;
    }

    if((test->iterations_write == cyc_numb_write_ref) && (test->flag_write == flag_write_ref) &&
       (test->iterations_read == cyc_numb_read_ref) &&(test->flag_read == flag_read_ref) &&
	   (test->error_counter == 0))
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
    char usart_buffer[BUFFER_LENGTH_64];       /* USART 8 bits buffer.   */
    struct t_usart_driver *usart1 = usart_get_driver(1);

    uint32_t string_length = sprintf(&usart_buffer[0], "QUEUE - Test 1, fill then read a half queue: ");
    usart_send(usart1, (uint8_t*)&usart_buffer[0], string_length);
    if(results->test[0]->result == OK)
    {
        string_length = sprintf(&usart_buffer[0], "PASS");
    }
    else
    {
        string_length = sprintf(&usart_buffer[0], "FAIL");
    }
    usart_send(usart1, (uint8_t*)&usart_buffer[0], string_length);
    usart_buffer[0] = 0x0A;
    usart_send(usart1, (uint8_t*)&usart_buffer[0], 1);

    string_length = sprintf(&usart_buffer[0], "QUEUE - Test 2, fill then read a full queue: ");
    usart_send(usart1, (uint8_t*)&usart_buffer[0], string_length);
    if(results->test[1]->result == OK)
    {
        string_length = sprintf(&usart_buffer[0], "PASS");
    }
    else
    {
        string_length = sprintf(&usart_buffer[0], "FAIL");
    }
    usart_send(usart1, (uint8_t*)&usart_buffer[0], string_length);
    usart_buffer[0] = 0x0A;
    usart_send(usart1, (uint8_t*)&usart_buffer[0], 1);

    string_length = sprintf(&usart_buffer[0], "QUEUE - Test 3, full fill the queue then read a full queue: ");
    usart_send(usart1, (uint8_t*)&usart_buffer[0], string_length);
    if(results->test[2]->result == OK)
    {
        string_length = sprintf(&usart_buffer[0], "PASS");
    }
    else
    {
        string_length = sprintf(&usart_buffer[0], "FAIL");
    }
    usart_send(usart1, (uint8_t*)&usart_buffer[0], string_length);
    usart_buffer[0] = 0x0A;
    usart_send(usart1, (uint8_t*)&usart_buffer[0], 1);

    string_length = sprintf(&usart_buffer[0], "QUEUE - Test 4, randomly full and read the queue: ");
    usart_send(usart1, (uint8_t*)&usart_buffer[0], string_length);
    if(results->test[3]->result == OK)
    {
        string_length = sprintf(&usart_buffer[0], "PASS");
    }
    else
    {
        string_length = sprintf(&usart_buffer[0], "FAIL");
    }
    usart_send(usart1, (uint8_t*)&usart_buffer[0], string_length);
    usart_buffer[0] = 0x0A;
    usart_send(usart1, (uint8_t*)&usart_buffer[0], 1);
    usart_buffer[0] = 0x0A;
    usart_send(usart1, (uint8_t*)&usart_buffer[0], 1);

    while(results->test[index] != 0)
    {
        result += results->test[index]->result;
        index++;
    }
    return result;
}

