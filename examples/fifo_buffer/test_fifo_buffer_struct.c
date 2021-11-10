#include <stdio.h>
#include <sys/time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) sleep(x)
#endif

#ifdef _WIN32
	#pragma message "OS : Windows"
#elif __linux__
	#pragma message "OS : Linux"
#elif __unix__
	#pragma message "OS : Other unix"
#else
	#pragma message "OS : Unidentified"
#endif

#include "../../lib/fifo_buffer/fifo_buffer_struct.h"

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

int main()
{
    printf("\r\nTest program for fifo_buffer_multi\r\n\n");
    
    InitFifo(&fifo, readData, writeData, FIFO_SIZE);

    printf("Write 2 set of data in fifo ...\r\n");
    
    fifoData.data1 = 123;
    fifoData.data2 = 345678;
    fifoData.data3 = -34;
    fifoData.data4 = 3.56;
    WriteFifo(&fifo, &fifoData);

    fifoData.data1 = 2;
    fifoData.data2 = 3;
    fifoData.data3 = 4;
    fifoData.data4 = 5;
    WriteFifo(&fifo, &fifoData);

    printf("Number of data in fifo : %d\r\n", nbrOfDataFifo(&fifo));

    fifoData.data1 = 0;
    fifoData.data2 = 0;
    fifoData.data3 = 0;
    fifoData.data4 = 0;
    printf("Read :\r\n");
    while(ReadFifo(&fifo, &fifoData) == FIFO_OK) {
        printf(" data1 : %d, data2 : %d, data3 : %d, data4 : %f\r\n", fifoData.data1, fifoData.data2, fifoData.data3, fifoData.data4);
    }
    printf("\r\n\n");

    return 0;
}