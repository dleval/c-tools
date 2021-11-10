<a href ="http://dle-dev.com">
  <img src="https://dle-dev.com/wp-content/uploads/2020/05/dle_dev_logo_v1.1.png" alt="DLE-Dev logo" title="DLE-Dev" align="right" height="40" />
</a>

Fifo memory buffer
======================
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
![version](https://img.shields.io/badge/version-1.0-blue)

## fifo_buffer
Uses byte by byte access. This version is compiler sensitive and may not work depending on padding optimizations.<br>
It is better to use the fifo_buffer_struct version instead.

## fifo_buffer_8 / fifo_buffer_16 / fifo_buffer_32
Optimized version for a buffer with 8, 16 or 32 bits data.

### Declaration
```c
#include "fifo_buffer_8.h"
or
#include "fifo_buffer_16.h"
or
#include "fifo_buffer_32.h"

fifoParam_TStruct fifo;
uint8_t fifoBuffer[FIFO_SIZE];
```

### Initialization
```c
InitFifo(&fifo, fifoBuffer, FIFO_SIZE);
```

## fifo_buffer_sruct
Uses interface functions for writing and reading data. This is useful for complex types of variables like structures.<br>

### Declaration
```c
#include "fifo_buffer_struct.h"

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
```

### Initialization
```c
InitFifo(&fifo, readData, writeData, FIFO_SIZE);
```

## Common features

### Status of fifo

fifoStatus_TEnum :
- FIFO_OK
- FIFO_FULL
- FIFO_EMPTY

### Read
```c
fifoStatus_TEnum status = ReadFifo(&fifo, &fifoData);
```

### Write
```c
fifoStatus_TEnum status = WriteFifo(&fifo, &fifoData);
```

### Check number of data
```c
uint16_t nbrOfData = nbrOfDataFifo(&fifo);
```
