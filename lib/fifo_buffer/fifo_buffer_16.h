/**
 * @file fifo_buffer_16.h
 * @author David LEVAL (dleval@dle-dev.com)
 * @brief Tool for fifo memory with configurable size (optimized for 16-bit data)
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
 */

#ifndef FIFOBUFFER_16_H
#define	FIFOBUFFER_16_H

#include <stdint.h>

typedef struct
{
    uint16_t *bufferAddr;  //!< Buffer de la mémoire FIFO
    uint16_t size;
    uint16_t readPtr;        //!< Pointeur de lecture
    uint16_t writePtr;       //!< Pointeur d'écriture
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
fifoStatus_TEnum WriteFifo(fifoParam_TStruct *FIFO, uint16_t *data);
fifoStatus_TEnum ReadFifo(fifoParam_TStruct *FIFO, uint16_t *data);
uint16_t nbrOfDataFifo(fifoParam_TStruct *FIFO);
void InitFifo(fifoParam_TStruct *fifo, uint16_t *buffer, uint16_t size);

#endif	/* FIFOBUFFER_16_H */

