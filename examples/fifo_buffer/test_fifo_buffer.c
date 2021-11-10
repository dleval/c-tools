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

#include "../../lib/fifo_buffer/fifo_buffer.h"

fifoParam_TStruct fifoOne;
fifoParam_TStruct fifoTwo;
uint8_t fifoOneBuffer[64] = {0};
uint32_t fifoTwoBuffer[32] = {0};

int main() 
{
    uint8_t i;
    uint8_t fifoOneData;
    uint32_t fifoTwoData;

    printf("\r\nTest program for fifo_buffer\r\n\n");

    printf("Size of fifoOne : %d bytes\r\n", sizeof(fifoOneBuffer));
    printf("Size of type fifoOne : %d bytes\r\n", sizeof(uint8_t));
    //printf("Start Adress of fifoOne : 0x%X\r\n", &fifoOneBuffer[0]);
    printf("Size of fifoTwo : %d bytes\r\n", sizeof(fifoTwoBuffer));
    printf("Size of type fifoTwo : %d bytes\r\n", sizeof(uint32_t));
    //printf("Start Adress of fifoTwo : 0x%X\r\n", &fifoTwoBuffer[0]);
    printf("\n");

    InitFifo(&fifoOne, fifoOneBuffer, sizeof(fifoOneBuffer), sizeof(uint8_t));
    InitFifo(&fifoTwo, fifoTwoBuffer, sizeof(fifoTwoBuffer), sizeof(uint32_t));

    fifoOneData = 0x56;
    printf("Write data 0x%X in fifoOne\r\n", fifoOneData);
    WriteFifo(&fifoOne, &fifoOneData);
    fifoOneData = 0x89;
    printf("Write data 0x%X in fifoOne\r\n", fifoOneData);
    WriteFifo(&fifoOne, &fifoOneData);
    printf("Number of data in fifoOne : %d\r\nRead :", nbrOfDataFifo(&fifoOne));
    while(ReadFifo(&fifoOne, &fifoOneData) == FIFO_OK) {
        i = 1;
        printf(" Data%d : 0x%X", i++, fifoOneData);
    }
    printf("\r\n\n");
    
    fifoTwoData = 0x56;
    printf("Write data 0x%X in fifoTwo\r\n", fifoTwoData);
    WriteFifo(&fifoTwo, &fifoTwoData);
    fifoTwoData = 0x89;
    printf("Write data 0x%X in fifoTwo\r\n", fifoTwoData);
    WriteFifo(&fifoTwo, &fifoTwoData);
    fifoTwoData = 0x12345678;
    printf("Write data 0x%X in fifoTwo\r\n", fifoTwoData);
    WriteFifo(&fifoTwo, &fifoTwoData);
    printf("Number of data in fifoTwo : %d\r\nRead :", nbrOfDataFifo(&fifoTwo));
    while(ReadFifo(&fifoTwo, &fifoTwoData) == FIFO_OK) {
        i = 1;
        printf(" Data%d : 0x%X", i++, fifoTwoData);
    }
    printf("\r\n\n");

    i = 0;
    while(WriteFifo(&fifoOne, &fifoOneData) != FIFO_FULL) { 
        i++;
    }
    printf("Write %d data in fifoOne before fifo Full\r\n", i);
    

    return 0;
}