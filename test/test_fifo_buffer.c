
#include "unity.h"
#include "fifo_buffer.h"

typedef struct {
    uint8_t data8;
    uint32_t data32;
    int16_t data16;
} testStruct_t;


fifoParam_TStruct fifoUINT8;
fifoParam_TStruct fifoUINT32;
fifoParam_TStruct fifoSTRUCT;
uint8_t fifoUINT8Buffer[64] = {0};
uint32_t fifoUINT32Buffer[32] = {0};
testStruct_t fifoStructBuffer[200];

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
    InitFifo(&fifoUINT8, fifoUINT8Buffer, sizeof(fifoUINT8Buffer), sizeof(uint8_t));

    TEST_ASSERT_EQUAL_UINT(&fifoUINT8Buffer, fifoUINT8.bufferAddr);
    TEST_ASSERT_EQUAL_UINT(64, fifoUINT8.size);
    TEST_ASSERT_EQUAL_UINT(1, fifoUINT8.typeSize);
    TEST_ASSERT_EQUAL_UINT(0, fifoUINT8.readPtr);
    TEST_ASSERT_EQUAL_UINT(0, fifoUINT8.writePtr);
    TEST_ASSERT_EQUAL_UINT(1, fifoUINT8.isEmpty);
    TEST_ASSERT_EQUAL_UINT(0, fifoUINT8.isFull);
}

void test_InitFifo_uint32(void)
{
    InitFifo(&fifoUINT32, fifoUINT32Buffer, sizeof(fifoUINT32Buffer), sizeof(uint32_t));

    TEST_ASSERT_EQUAL_UINT(&fifoUINT32Buffer, fifoUINT32.bufferAddr);
    TEST_ASSERT_EQUAL_UINT(32, fifoUINT32.size);
    TEST_ASSERT_EQUAL_UINT(4, fifoUINT32.typeSize);
    TEST_ASSERT_EQUAL_UINT(0, fifoUINT32.readPtr);
    TEST_ASSERT_EQUAL_UINT(0, fifoUINT32.writePtr);
    TEST_ASSERT_EQUAL_UINT(1, fifoUINT32.isEmpty);
    TEST_ASSERT_EQUAL_UINT(0, fifoUINT32.isFull);
}

void test_InitFifo_struct(void)
{
    InitFifo(&fifoSTRUCT, fifoStructBuffer, sizeof(fifoStructBuffer), sizeof(testStruct_t));

    TEST_ASSERT_EQUAL_UINT(&fifoStructBuffer, fifoSTRUCT.bufferAddr);
    TEST_ASSERT_EQUAL_UINT(200, fifoSTRUCT.size);
    TEST_ASSERT_EQUAL_UINT(sizeof(testStruct_t), fifoSTRUCT.typeSize);
    TEST_ASSERT_EQUAL_UINT(0, fifoSTRUCT.readPtr);
    TEST_ASSERT_EQUAL_UINT(0, fifoSTRUCT.writePtr);
    TEST_ASSERT_EQUAL_UINT(1, fifoSTRUCT.isEmpty);
    TEST_ASSERT_EQUAL_UINT(0, fifoSTRUCT.isFull);
}

void test_Fifo_uint8(void)
{
    InitFifo(&fifoUINT8, fifoUINT8Buffer, sizeof(fifoUINT8Buffer), sizeof(uint8_t));

    static uint8_t fifoData;

    for(fifoData = 0; fifoData < 20; fifoData++) {
        WriteFifo(&fifoUINT8, &fifoData);
    }
    for(fifoData = 0; fifoData < 20; fifoData++) {
        TEST_ASSERT_EQUAL_UINT(fifoData, fifoUINT8Buffer[fifoData]);
    }
    uint8_t nbrOfData = nbrOfDataFifo(&fifoUINT8);
    TEST_ASSERT_EQUAL_UINT(20, nbrOfData);

    ReadFifo(&fifoUINT8, &fifoData);
    TEST_ASSERT_EQUAL_UINT(0, fifoData);
    ReadFifo(&fifoUINT8, &fifoData);
    TEST_ASSERT_EQUAL_UINT(1, fifoData);
    ReadFifo(&fifoUINT8, &fifoData);
    TEST_ASSERT_EQUAL_UINT(2, fifoData);
    
    nbrOfData = nbrOfDataFifo(&fifoUINT8);
    TEST_ASSERT_EQUAL_UINT(17, nbrOfData);
}


//!!!!!!!!!!! Doesn't work : padding problem
// void test_Fifo_uint32(void)
// {
//     InitFifo(&fifoUINT32, fifoUINT32Buffer, sizeof(fifoUINT32Buffer), sizeof(uint8_t));

//     static uint32_t fifoData = 0;
//     static uint8_t* ptrfifoData = (uint8_t*)&fifoData;

//     // for(fifoData = 0; fifoData < 20; fifoData++) {
//     //     WriteFifo(&fifoUINT32, &fifoData);
//     // }
//     WriteFifo(&fifoUINT32, ptrfifoData);
//     *ptrfifoData = 1;
//     WriteFifo(&fifoUINT32, ptrfifoData);
//     *ptrfifoData = 2;
//     WriteFifo(&fifoUINT32, ptrfifoData);
//     *ptrfifoData = 3;
//     WriteFifo(&fifoUINT32, ptrfifoData);
//     *ptrfifoData = 4;
//     WriteFifo(&fifoUINT32, ptrfifoData);
//     // for(fifoData = 0; fifoData < 20; fifoData++) {
//     //     TEST_ASSERT_EQUAL_UINT(fifoData, fifoUINT32Buffer[fifoData]);
//     // }
//     uint8_t nbrOfData = nbrOfDataFifo(&fifoUINT32);
//     TEST_ASSERT_EQUAL_UINT(5, nbrOfData);

//     ReadFifo(&fifoUINT32, ptrfifoData);
//     TEST_ASSERT_EQUAL_UINT(0, *ptrfifoData);
//     ReadFifo(&fifoUINT32, ptrfifoData);
//     TEST_ASSERT_EQUAL_UINT(1, *ptrfifoData);
//     ReadFifo(&fifoUINT32, ptrfifoData);
//     TEST_ASSERT_EQUAL_UINT(2, *ptrfifoData);
    
//     nbrOfData = nbrOfDataFifo(&fifoUINT32);
//     TEST_ASSERT_EQUAL_UINT(2, nbrOfData);
// }
