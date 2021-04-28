#ifndef GTVECTOR_H_INCLUDED
#define GTVECTOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t const dataTypeSize;
    size_t bufferLength;
    size_t elementsInBuffer;
    unsigned char* buffer;
} Vec;

Vec createVectorA(size_t sizeOfDatatype, size_t initialLength);
Vec createVector(size_t sizeOfDatatype);
int _simpleResize(Vec* vec);
int _manualResize(Vec* vec, size_t pos);
int _resizeVector(Vec* vec, unsigned char mustShift, size_t pos);
int addValue(Vec* vec, void* ptrToValue, size_t pos);
int addFront(Vec* vec, void* ptrToValue);
int addBack(Vec* vec, void* ptrToValue);
int setValue(Vec* vec, void* ptrToValue, size_t pos);
int removeValues(Vec* vec, size_t index, size_t noOfElements);
int removeValue(Vec* vec, size_t index);
int removeFront(Vec* vec);
int removeBack(Vec* vec);
// TODO: resize, sort, reverseOrder, shrink to fit

#endif // GTVECTOR_H_INCLUDED
