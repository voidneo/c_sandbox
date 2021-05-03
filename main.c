#include <stdio.h>
#include <stdlib.h>
#include "gtvector.h"

int main() {
    Vec v = createVector(sizeof(size_t));
    size_t p = 0;

    for(size_t i = 0; i < 16; i++) {
        addBack(&v, &i);
    }

    //removeFront(&v);
    //removeBack(&v);
    //removeValue(&v, 3);
    //removeValues(&v, 3, 2);

    for(size_t i = 0; i < v.elementsInBuffer; i++) {
        getValue(&v, i, &p);
        printf("%lu: %lu\n", i, p);
    }

    printf("length in bytes: %lu\nlength in elements: %lu\nelements: %lu", v.bufferLength, (v.bufferLength/v.dataTypeSize), v.elementsInBuffer);

    return 0;
}
