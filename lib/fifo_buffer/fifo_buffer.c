/**
 * @file fifo_buffer.c
 * @author David LEVAL (dleval@dle-dev.com)
 * @version 1.0
 * @date 2021-11-08
 * 
 * @copyright Copyright (c) 2021
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include "fifo_buffer.h"

/**
 * @brief Writing in a FIFO memory
 * 
 * @param fifo  fifo parameters data address
 * @param data  data to write in the FIFO memory
 * @return fifoStatus_TEnum  
 */
fifoStatus_TEnum WriteFifo(fifoParam_TStruct *fifo, void *data)
{
    uint8_t i;
    uint8_t *dataPtr, *bufferPtr;
    dataPtr = (uint8_t*)data;
    bufferPtr = fifo->bufferAddr;
    //Test if the FIFO is full
    if(fifo->isFull == 0) {
        //Adding data to the queue
        bufferPtr = bufferPtr + (fifo->typeSize * fifo->writePtr);
        for(i=0; i<fifo->size; i++)
            *(bufferPtr)++ = *dataPtr++;
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
    uint8_t i;
    uint8_t *dataPtr, *bufferPtr;
    dataPtr = (uint8_t*)data;
    bufferPtr = fifo->bufferAddr;
    //Read if the fifo is not empty.
    if(fifo->isEmpty == 0) {
        //Reading the data in the queue
        bufferPtr = bufferPtr + (fifo->typeSize * fifo->readPtr);
        for(i=0; i<fifo->size; i++)
            *dataPtr++ = *(bufferPtr)++;
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
uint8_t nbrOfDataFifo(fifoParam_TStruct *fifo)
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
 * @param fifo      fifo parameters data address
 * @param buffer    fifo buffer data address
 * @param size      size of fifo buffer (byte)
 * @param typeSize  size of type data fifo buffer (byte)
 */
void InitFifo(fifoParam_TStruct *fifo, void *buffer, uint16_t size, uint8_t typeSize)
{
    fifo->bufferAddr = buffer;
    fifo->size = size / typeSize;
    fifo->typeSize = typeSize;
    fifo->readPtr = 0;
    fifo->writePtr = 0;
    fifo->isEmpty = 1;
    fifo->isFull = 0;
}
