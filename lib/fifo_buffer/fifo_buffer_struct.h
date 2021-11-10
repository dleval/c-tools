/**
 * @file fifo_buffer_struct.h
 * @author David LEVAL (dleval@dle-dev.com)
 * @brief Tool for fifo memory with configurable size and type
 * @version 1.0
 * @date 2021-11-09
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

#ifndef FIFOBUFFERMULTI_H
#define	FIFOBUFFERMULTI_H

#include <stdint.h>

typedef void (*readData_t)(uint8_t, void*);
typedef void (*writeData_t)(uint8_t, void*);

typedef struct
{
    readData_t readData;
    writeData_t writeData;
    uint16_t size;
    uint16_t readPtr;
    uint16_t writePtr;
    uint8_t isEmpty;
    uint8_t isFull;
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
uint16_t nbrOfDataFifo(fifoParam_TStruct *fifo);
void InitFifo(fifoParam_TStruct *fifo, readData_t readData_ptr, writeData_t writeData_ptr, uint16_t size);

#endif	/* FIFOBUFFERMULTI_H */
