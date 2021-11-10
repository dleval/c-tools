/**
 * @file fifo_buffer_struct.c
 * @author David LEVAL (dleval@dle-dev.com)
 * @version 1.0
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "fifo_buffer_struct.h"

/**
 * @brief Writing in a FIFO memory
 * 
 * @param fifo  fifo parameters data address
 * @param data  data to write in the FIFO memory
 * @return fifoStatus_TEnum  
 */
fifoStatus_TEnum WriteFifo(fifoParam_TStruct *fifo, void *data)
{
    //Test if the FIFO is full
    if(fifo->isFull == 0) {
        //Adding data to the queue
        fifo->writeData(fifo->writePtr, data);
        //Incrementing the write pointer
        fifo->writePtr = (fifo->writePtr + 1) % fifo->size;
        //Test if the queue is full
        if(fifo->writePtr == fifo->readPtr) fifo->isFull = 1;
        //Clear fifo empty flag
        fifo->isEmpty = 0;

        return FIFO_OK;
    }
    return FIFO_FULL;
}

/**
 * @brief Reading in a FIFO memory
 * 
 * @param fifo  fifo parameters data address
 * @param data  data to read in the FIFO memory
 * @return fifoStatus_TEnum 
 */
fifoStatus_TEnum ReadFifo(fifoParam_TStruct *fifo, void *data)
{
    //Read if the fifo is not empty.
    if(fifo->isEmpty == 0) {
        //Reading the data in the queue
        fifo->readData(fifo->readPtr, data);
        //*data = fifo->buffer[fifo->readPtr];
        //Incrementing the read pointer
        fifo->readPtr = (fifo->readPtr + 1) % fifo->size;
        //Test if the queue is empty
        if(fifo->readPtr == fifo->writePtr) fifo->isEmpty = 1;
        //Clear fifo full flag
        fifo->isFull = 0;

        return FIFO_OK;
    }
    return FIFO_EMPTY;
}

/**
 * @brief Returns the given number available in the fifo
 * 
 * @param fifo  fifo parameters data address
 * @return number of data available in the fifo
 */
uint16_t nbrOfDataFifo(fifoParam_TStruct *fifo)
{
    if(fifo->writePtr >= fifo->readPtr) {
        return (fifo->writePtr - fifo->readPtr);
    } else {
        return ((fifo->size - fifo->readPtr) + fifo->writePtr);
    }
}

/**
 * @brief Initialization of the FIFO memory
 * 
 * @param fifo              fifo parameters data address
 * @param readData_ptr      read function interface
 * @param writeData_ptr     write function interface
 * @param size              size of fifo buffer
 */
void InitFifo(fifoParam_TStruct *fifo, readData_t readData_ptr, writeData_t writeData_ptr, uint16_t size)
{
    fifo->readData = readData_ptr;
    fifo->writeData = writeData_ptr;
    fifo->size = size;
    fifo->readPtr = 0;
    fifo->writePtr = 0;
    fifo->isEmpty = 1;
    fifo->isFull = 0;
}
