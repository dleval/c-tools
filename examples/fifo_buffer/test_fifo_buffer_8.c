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

#include "../../lib/fifo_buffer/fifo_buffer_8.h"

fifoParam_TStruct fifo;
uint8_t fifoBuffer[167] = {0};

int main() 
{
    uint8_t i;
    uint8_t fifoData;

    printf("\r\nTest program for fifo_buffer\r\n\n");

    printf("Size of fifo : %d bytes\r\n", sizeof(fifoBuffer));
    //printf("Start Adress of fifoOne : 0x%X\r\n", &fifoOneBuffer[0]);
    printf("\n");

    InitFifo(&fifo, fifoBuffer, sizeof(fifoBuffer));

    fifoData = 0x56;
    printf("Write data 0x%X in fifo\r\n", fifoData);
    WriteFifo(&fifo, &fifoData);
    fifoData = 0x89;
    printf("Write data 0x%X in fifoOne\r\n", fifoData);
    WriteFifo(&fifo, &fifoData);
    printf("Number of data in fifoOne : %d\r\nRead :", nbrOfDataFifo(&fifo));
    while(ReadFifo(&fifo, &fifoData) == FIFO_OK) {
        i = 1;
        printf(" Data%d : 0x%X", i++, fifoData);
    }
    printf("\r\n\n");
    

    i = 0;
    while(WriteFifo(&fifo, &fifoData) != FIFO_FULL) { 
        i++;
    }
    printf("Write %d data in fifo before fifo Full\r\n", i);
    

    return 0;
}