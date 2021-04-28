#include <stdio.h>
#include <stdlib.h>
#include "gtvector.h"

int main() {
    Vec v = createVector(sizeof(char));

    size_t len = 16;
    char arr[len];

    for(size_t i = 0; i < len; i++) {
        arr[i] = i;
        addValue(&v, &arr[i], i);
    }

    char p = 0;

    p = 255;

    addFront(&v, &p);
    addValue(&v, &p, 9);
    addBack(&v, &p);

    setValue(&v, &p, 10);


    for(size_t i = 0; i < v.elementsInBuffer; i++) {
        getValue(&v, i, &p);
        printf("%lu: %i\n", i, (int) p);
    }



    printf("length in bytes: %lu\nlength in elements: %lu\nelements: %lu", v.bufferLength, (v.bufferLength/v.dataTypeSize), v.elementsInBuffer);

    return 0;
}
