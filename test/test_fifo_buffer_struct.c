#include "unity.h"
#include "fifo_buffer_struct.h"

#define FIFO_SIZE   34

typedef struct {
    uint8_t data1;
    uint32_t data2;
    int16_t data3;
    float data4;
}structTest_t;

structTest_t fifoBuffer[FIFO_SIZE];
structTest_t fifoData;
fifoParam_TStruct fifo;

void readData(uint8_t pos, void *data)
{
    structTest_t *ptr;
    ptr = (structTest_t*)data;
    *ptr = fifoBuffer[pos];
}

void writeData(uint8_t pos, void *data)
{
    structTest_t *ptr;
    ptr = (structTest_t*)data;
    fifoBuffer[pos] = *ptr;
}


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

void test_InitFifo(void)
{
    InitFifo(&fifo, readData, writeData, FIFO_SIZE);

    TEST_ASSERT_EQUAL_UINT(&readData, fifo.readData);
    TEST_ASSERT_EQUAL_UINT(&writeData, fifo.writeData);
    TEST_ASSERT_EQUAL_UINT(FIFO_SIZE, fifo.size);
    TEST_ASSERT_EQUAL_UINT(0, fifo.readPtr);
    TEST_ASSERT_EQUAL_UINT(0, fifo.writePtr);
    TEST_ASSERT_EQUAL_UINT(1, fifo.isEmpty);
    TEST_ASSERT_EQUAL_UINT(0, fifo.isFull);
}

void test_Fifo_struct(void)
{
    InitFifo(&fifo, readData, writeData, FIFO_SIZE);

    uint16_t nbrOfData = nbrOfDataFifo(&fifo);
    TEST_ASSERT_EQUAL_UINT(0, nbrOfData);

    fifoData.data1 = 123;
    fifoData.data2 = 345678;
    fifoData.data3 = -34;
    fifoData.data4 = 3.56;
    uint8_t status = WriteFifo(&fifo, &fifoData);
    TEST_ASSERT_EQUAL_UINT(FIFO_OK, status);

    nbrOfData = nbrOfDataFifo(&fifo);
    TEST_ASSERT_EQUAL_UINT(1, nbrOfData);

    fifoData.data1 = 2;
    fifoData.data2 = 3;
    fifoData.data3 = 4;
    fifoData.data4 = 5;
    status = WriteFifo(&fifo, &fifoData);
    TEST_ASSERT_EQUAL_UINT(FIFO_OK, status);

    nbrOfData = nbrOfDataFifo(&fifo);
    TEST_ASSERT_EQUAL_UINT(2, nbrOfData);

    status = ReadFifo(&fifo, &fifoData);
    TEST_ASSERT_EQUAL_UINT(FIFO_OK, status);
    TEST_ASSERT_EQUAL_UINT(123, fifoData.data1);
    TEST_ASSERT_EQUAL_UINT(345678, fifoData.data2);
    TEST_ASSERT_EQUAL_INT(-34, fifoData.data3);
    TEST_ASSERT_EQUAL_FLOAT(3.56, fifoData.data4);

    nbrOfData = nbrOfDataFifo(&fifo);
    TEST_ASSERT_EQUAL_UINT(1, nbrOfData);

    status = ReadFifo(&fifo, &fifoData);
    TEST_ASSERT_EQUAL_UINT(FIFO_OK, status);
    TEST_ASSERT_EQUAL_UINT(2, fifoData.data1);
    TEST_ASSERT_EQUAL_UINT(3, fifoData.data2);
    TEST_ASSERT_EQUAL_INT(4, fifoData.data3);
    TEST_ASSERT_EQUAL_FLOAT(5, fifoData.data4);

    nbrOfData = nbrOfDataFifo(&fifo);
    TEST_ASSERT_EQUAL_UINT(0, nbrOfData);

    status = ReadFifo(&fifo, &fifoData);
    TEST_ASSERT_EQUAL_UINT(FIFO_EMPTY, status);
}

void test_Fifo_Full(void)
{
    uint8_t i = 0;

    fifoData.data1 = 2;
    fifoData.data2 = 3;
    fifoData.data3 = 4;
    fifoData.data4 = 5;

    InitFifo(&fifo, readData, writeData, FIFO_SIZE);

    while(WriteFifo(&fifo, &fifoData) == FIFO_OK) i++;

    TEST_ASSERT_EQUAL_UINT(FIFO_SIZE, i);

    uint8_t status = WriteFifo(&fifo, &fifoData);
    TEST_ASSERT_EQUAL_UINT(FIFO_FULL, status);
}

