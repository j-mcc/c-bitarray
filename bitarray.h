/*
 * $Author: jmcc$
 * $Date: 2017/12/01 20:07:03 $
 *
 */

#ifndef BITARRAY_H
#define BITARRAY_H

#define MAX_VALUE 255
#define MIN_VALUE 0

typedef struct{
  unsigned char *bits;
  unsigned int slots;
  unsigned int bytes;
}bitarray_t;

void clearAll(bitarray_t *bitArray);

void setAll(bitarray_t *bitArray);

int initBitVector(bitarray_t *bitArray, unsigned int size, unsigned char initialValue);

int getBit(bitarray_t *bitArray, unsigned int index);

int setBit(bitarray_t *bitArray, unsigned int index);

int flipBit(bitarray_t *bitArray, unsigned int index);

int clearBit(bitarray_t *bitArray, unsigned int index);

void printBitVector(bitarray_t *bitArray);

void freeBitArray(bitarray_t *bitArray);

int isFull(bitarray_t *bitArray);

int isEmpty(bitarray_t *bitArray);

int indexOfNextSetBit(bitarray_t *bitArray);

int getNumberSetBits(bitarray_t *bitArray);

#endif
