#include "unity.h"
#include "fifo_buffer_8.h"

#define FIFO_SIZE   356

fifoParam_TStruct fifo;
uint8_t fifoBuffer[FIFO_SIZE] = {0};
uint8_t fifoData;
int8_t fifoBufferInt[FIFO_SIZE] = {0};
int8_t fifoDataInt;

/**
 * @brief Initialization function of each test 
 */
void setUp(void)
{
}

/**
 * @brief Function called after each test 
 */
void tearDown(void)
{
}

void test_InitFifo_uint8(void)
{
    InitFifo(&fifo, fifoBuffer, sizeof(fifoBuffer));

    TEST_ASSERT_EQUAL_UINT(&fifoBuffer, fifo.bufferAddr);
    TEST_ASSERT_EQUAL_UINT(FIFO_SIZE, fifo.size);
    TEST_ASSERT_EQUAL_UINT(0, fifo.readPtr);
    TEST_ASSERT_EQUAL_UINT(0, fifo.writePtr);
    TEST_ASSERT_EQUAL_UINT(1, fifo.isEmpty);
    TEST_ASSERT_EQUAL_UINT(0, fifo.isFull);
}

void test_Fifo_uint8(void)
{
    InitFifo(&fifo, fifoBuffer, sizeof(fifoBuffer));

    uint16_t nbrOfData = nbrOfDataFifo(&fifo);
    TEST_ASSERT_EQUAL_UINT(0, nbrOfData);

    fifoData = 45;
    uint8_t status = WriteFifo(&fifo, &fifoData);
    TEST_ASSERT_EQUAL_UINT(FIFO_OK, status);

    nbrOfData = nbrOfDataFifo(&fifo);
    TEST_ASSERT_EQUAL_UINT(1, nbrOfData);

    fifoData = 156;
    status = WriteFifo(&fifo, &fifoData);
    TEST_ASSERT_EQUAL_UINT(FIFO_OK, status);

    nbrOfData = nbrOfDataFifo(&fifo);
    TEST_ASSERT_EQUAL_UINT(2, nbrOfData);

    status = ReadFifo(&fifo, &fifoData);
    TEST_ASSERT_EQUAL_UINT(FIFO_OK, status);
    TEST_ASSERT_EQUAL_UINT(45, fifoData);

    nbrOfData = nbrOfDataFifo(&fifo);
    TEST_ASSERT_EQUAL_UINT(1, nbrOfData);

    status = ReadFifo(&fifo, &fifoData);
    TEST_ASSERT_EQUAL_UINT(FIFO_OK, status);
    TEST_ASSERT_EQUAL_UINT(156, fifoData);

    nbrOfData = nbrOfDataFifo(&fifo);
    TEST_ASSERT_EQUAL_UINT(0, nbrOfData);

    status = ReadFifo(&fifo, &fifoData);
    TEST_ASSERT_EQUAL_UINT(FIFO_EMPTY, status);
}

void test_Fifo_int8(void)
{
    InitFifo(&fifo, fifoBufferInt, sizeof(fifoBufferInt));

    uint16_t nbrOfData = nbrOfDataFifo(&fifo);
    TEST_ASSERT_EQUAL_UINT(0, nbrOfData);

    fifoDataInt = -45;
    uint8_t status = WriteFifo(&fifo, &fifoDataInt);
    TEST_ASSERT_EQUAL_UINT(FIFO_OK, status);

    nbrOfData = nbrOfDataFifo(&fifo);
    TEST_ASSERT_EQUAL_UINT(1, nbrOfData);

    fifoDataInt = 112;
    status = WriteFifo(&fifo, &fifoDataInt);
    TEST_ASSERT_EQUAL_UINT(FIFO_OK, status);

    nbrOfData = nbrOfDataFifo(&fifo);
    TEST_ASSERT_EQUAL_UINT(2, nbrOfData);

    status = ReadFifo(&fifo, &fifoDataInt);
    TEST_ASSERT_EQUAL_UINT(FIFO_OK, status);
    TEST_ASSERT_EQUAL_INT(-45, fifoDataInt);

    nbrOfData = nbrOfDataFifo(&fifo);
    TEST_ASSERT_EQUAL_UINT(1, nbrOfData);

    status = ReadFifo(&fifo, &fifoDataInt);
    TEST_ASSERT_EQUAL_UINT(FIFO_OK, status);
    TEST_ASSERT_EQUAL_INT(112, fifoDataInt);

    nbrOfData = nbrOfDataFifo(&fifo);
    TEST_ASSERT_EQUAL_UINT(0, nbrOfData);

    status = ReadFifo(&fifo, &fifoDataInt);
    TEST_ASSERT_EQUAL_UINT(FIFO_EMPTY, status);
}

void test_Fifo_Full(void)
{
    uint16_t i = 0;

    fifoData = 2;

    InitFifo(&fifo, fifoBuffer, sizeof(fifoBuffer));

    while(WriteFifo(&fifo, &fifoData) == FIFO_OK) i++;

    TEST_ASSERT_EQUAL_UINT(FIFO_SIZE, i);

    uint8_t status = WriteFifo(&fifo, &fifoData);
    TEST_ASSERT_EQUAL_UINT(FIFO_FULL, status);
}


void test_Fifo_turntable(void)
{
    uint16_t i = 0;
    uint8_t status;
    uint16_t nbrOfData;

    fifoData = 2;

    InitFifo(&fifo, fifoBuffer, sizeof(fifoBuffer));

    for(i = 0; i < (FIFO_SIZE - 10); i++)
        status = WriteFifo(&fifo, &fifoData);

    nbrOfData = nbrOfDataFifo(&fifo);
    TEST_ASSERT_EQUAL_UINT((FIFO_SIZE - 10), nbrOfData);
    TEST_ASSERT_EQUAL_UINT(FIFO_OK, status);

    for(i = 0; i < (FIFO_SIZE - 10); i++)
        status = ReadFifo(&fifo, &fifoData);

    nbrOfData = nbrOfDataFifo(&fifo);
    TEST_ASSERT_EQUAL_UINT(0, nbrOfData);
    TEST_ASSERT_EQUAL_UINT(2, fifoData);
    TEST_ASSERT_EQUAL_UINT(FIFO_OK, status);

    fifoData = 67;

    for(i = 0; i < (FIFO_SIZE / 2); i++)
        status = WriteFifo(&fifo, &fifoData);

    nbrOfData = nbrOfDataFifo(&fifo);
    TEST_ASSERT_EQUAL_UINT((FIFO_SIZE / 2), nbrOfData);
    TEST_ASSERT_EQUAL_UINT(FIFO_OK, status);

    status = ReadFifo(&fifo, &fifoData);
    nbrOfData = nbrOfDataFifo(&fifo);
    TEST_ASSERT_EQUAL_UINT((FIFO_SIZE / 2) - 1, nbrOfData);
    TEST_ASSERT_EQUAL_UINT(FIFO_OK, status);
    TEST_ASSERT_EQUAL_UINT(67, fifoData);

}
