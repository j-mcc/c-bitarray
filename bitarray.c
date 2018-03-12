/*
 * $Author: jmcc $
 * $Date: 2017/12/02 05:48:41 $
 */


/* Created with help from 'The Bit Twiddler' http://bits.stephan-brumme.com/basics.html */

#include "bitarray.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

void clearAll(bitarray_t *bitArray){
  int i;
  for(i = 0; i < bitArray->bytes; i++) bitArray->bits[i] = MIN_VALUE;
}

void setAll(bitarray_t *bitArray){
  int i;
  for(i = 0; i < bitArray->bytes; i++) bitArray->bits[i] = MAX_VALUE;
}

int initBitVector(bitarray_t *bitArray, unsigned int size, unsigned char initialValue){
  if(size <= 0) return -1;
  bitArray->slots = size;
  bitArray->bytes = ceil((size * 1.)/(CHAR_BIT * 1.));
  if((bitArray->bits = malloc(bitArray->bytes)) == NULL) return -1;
  if(initialValue == MIN_VALUE) clearAll(bitArray);
  if(initialValue == MAX_VALUE) setAll(bitArray);
  return 0;
}

int isFull(bitarray_t *bitArray){
  int i;
  for(i = 0; i < bitArray->slots; i++)
    if(!getBit(bitArray, i)) return 0;
  return 1;
}

int isEmpty(bitarray_t *bitArray){
  int i;
  for( i = 0; i < bitArray->slots; i++)
    if(getBit(bitArray, i)) return 0;
  return 1;
}

void freeBitArray(bitarray_t *bitArray){
  if(bitArray){
    if(bitArray->bits){
      free(bitArray->bits);
    }
  }
}

int getBit(bitarray_t *bitArray, unsigned int index){
  if(index > (CHAR_BIT * bitArray->bytes - 1)) return -1;  //index out of range
  unsigned int byte = floor(index / CHAR_BIT);
  unsigned char x = bitArray->bits[byte];
  x >>= (index % CHAR_BIT);
  return (x & 1) != 0;
}

int setBit(bitarray_t *bitArray, unsigned int index){
  if(index > (CHAR_BIT * bitArray->bytes - 1)) return -1;  //index out of range
  unsigned char mask = 1 << (index % CHAR_BIT);
  unsigned int byte = floor(index / CHAR_BIT);
  bitArray->bits[byte] |= mask;
  return 0;  
}

int flipBit(bitarray_t *bitArray, unsigned int index){
  if(index > (CHAR_BIT * bitArray->bytes - 1)) return -1;  //index out of range
  unsigned char mask = 1U << (index % CHAR_BIT);
  unsigned int byte = floor(index / CHAR_BIT);
  bitArray->bits[byte] ^= mask;
  return 0;
}

int clearBit(bitarray_t *bitArray, unsigned int index){
  if(index > (CHAR_BIT * bitArray->bytes - 1)) return -1;  //index out of range
  unsigned char mask = 1U << (index % CHAR_BIT);
  unsigned int byte = floor(index / CHAR_BIT);
  bitArray->bits[byte] &= ~mask;
  return 0;
}

void printBitVector(bitarray_t *bitArray){
  int i;
  for(i = 0; i < (CHAR_BIT * bitArray->bytes); i++){
    if(i % CHAR_BIT == 0) fprintf(stderr, " ");
    fprintf(stderr, "%d", getBit(bitArray, i));
  }
  fprintf(stderr, "\n");
}

int indexOfNextSetBit(bitarray_t *bitArray){
  int i;
  for(i = 0; i < bitArray->slots; i++){
    if(getBit(bitArray, i)) return i;
  }
  return -1;
}

int getNumberSetBits(bitarray_t *bitArray){
  int numSet = 0;
  int byte, bit;
  for(byte = 0; byte < bitArray->bytes; byte++){
    for(bit = 0; bit < CHAR_BIT; bit++){
      if(getBit(bitArray, (CHAR_BIT * byte) + bit)) numSet++;
    }
  }
  return numSet;
}

