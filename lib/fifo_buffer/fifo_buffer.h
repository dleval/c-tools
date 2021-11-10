/**
 * @file fifo_buffer.h
 * @author David LEVAL (dleval@dle-dev.com)
 * @brief Tool for fifo memory with configurable size and type
 * @version 1.0
 * @date 2021-11-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef FIFOBUFFER_H
#define	FIFOBUFFER_H

#include <stdint.h>

/******************************************************************************/
/* Usage                                                                      */
/******************************************************************************/
/*
    //variables
    fifoParam_TStruct fifo;
    uint32_t fifoBuffer[32];
    uint32_t fifoData;

    //init
    InitFifo(&fifo, fifoBuffer, sizeof(fifoBuffer), sizeof(uint32_t));

    //write
    WriteFifo(&fifo, &fifoData);

    //read
    ReadFifo(&fifo, &fifoData);

    //check number of data
    uint8_t nbrOfData = nbrOfDataFifo(&fifo);
*/

/**
 * @brief Memory object containing a FIFO memory structure
 */
typedef struct
{
    uint8_t *bufferAddr;  //!< Buffer de la mémoire FIFO
    uint8_t size;
    uint8_t typeSize;
    uint8_t readPtr;        //!< Pointeur de lecture
    uint8_t writePtr;       //!< Pointeur d'écriture
    uint8_t isEmpty;              //!< Indicateur de mémoire vide
    uint8_t isFull;               //!< Indicateur de mémoire pleine
} fifoParam_TStruct;

typedef enum
{
    FIFO_OK = 0,
    FIFO_FULL,
    FIFO_EMPTY
} fifoStatus_TEnum;

/******************************************************************************/
/* Public Prototypes                                                          */
/******************************************************************************/
fifoStatus_TEnum WriteFifo(fifoParam_TStruct *fifo, void *data);
fifoStatus_TEnum ReadFifo(fifoParam_TStruct *fifo, void *data);
uint8_t nbrOfDataFifo(fifoParam_TStruct *fifo);
void InitFifo(fifoParam_TStruct *fifo, void *buffer, uint16_t size, uint8_t typeSize);

#endif	/* FIFOBUFFER_H */
