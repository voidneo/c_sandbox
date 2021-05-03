#include "gtvector.h"

Vec createVectorA(size_t sizeOfDatatype, size_t initialLength) {
    Vec v = {
        .dataTypeSize     = sizeOfDatatype,
        .bufferLength     = initialLength * sizeOfDatatype,
        .elementsInBuffer = initialLength,
        .buffer           = calloc(initialLength, sizeOfDatatype)
    };

    return v;
}

Vec createVector(size_t sizeOfDatatype) {
    Vec v = {
        .dataTypeSize     = sizeOfDatatype,
        .bufferLength     = 8 * sizeOfDatatype,
        .elementsInBuffer = 0,
        .buffer           = calloc(8, sizeOfDatatype)
    };

    return v;
}

/* Inner function */
int _simpleResize(Vec* vec) {
    /* Double the length, bufferLength already takes datatype size into account */
    size_t bytes = 2 * vec->bufferLength;
    void* newBufferAddress = realloc(vec->buffer, bytes);

    /* If succeeded, update buffer mem address and length */
    if(newBufferAddress) {
        vec->buffer = newBufferAddress;
        vec->bufferLength = bytes;
        return 1;
    }

    return 0;
}

/* Inner function */
int _manualResize(Vec* vec, size_t pos) {

    void* newBufferAddress = calloc(2 * vec->elementsInBuffer, vec->dataTypeSize);

    /* If mem couldn't be allocated */
    if(!newBufferAddress) {
        return 0;
    }

    int success = 0;

    if(pos == 0) {
        /* copy buffer to address of element 1 of newBufferAddress */
        void* firstElem = newBufferAddress + vec->dataTypeSize;
        size_t bytes    = vec->elementsInBuffer * vec->dataTypeSize;

        if(memcpy(firstElem, vec->buffer, bytes)) {
            success = 1;
        }
    } else {
        /* copy up to where the new element should be palced */
        size_t bytesUntilEmptySpot = pos * vec->dataTypeSize;

        if(memcpy(newBufferAddress, vec->buffer, bytesUntilEmptySpot)) {
            success = 1;
        }

        /* copy from pos * dataTypSize from buffer to newBufferAddress at (pos + 1) * dataTypeSize */
        void* elemAfterTheNewOne      = newBufferAddress + (pos + 1)  * vec->dataTypeSize;
        void* elemAfterLastElemCopied = vec->buffer      +  pos       * vec->dataTypeSize;
        size_t bytesToCopy            = (vec->elementsInBuffer - pos) * vec->dataTypeSize;

        if(!memcpy(elemAfterTheNewOne, elemAfterLastElemCopied, bytesToCopy)) {
            success = 0;
        }
    }

    if(success) {
        free(vec->buffer);
        vec->buffer = newBufferAddress;
    } else {
        free(newBufferAddress);
    }

    return success;
}

/* Inner function */
int _resizeVector(Vec* vec, unsigned char mustShift, size_t pos) {
    if(mustShift) {
        return _manualResize(vec, pos);
    }
    return _simpleResize(vec);
}

/** Copy the value from @vec at index @pos to @target. Returns 1 on success or 0 on failure **/
int getValue(Vec const * const vec, size_t pos, void* target) {
    /* If ptr is null or index out of bounds */
    if(!vec || pos >= vec->elementsInBuffer) {
        return 0;
    }

    /* Copy element at index @pos to @target */
    target = memcpy(target, vec->buffer + pos * vec->dataTypeSize, vec->dataTypeSize);
    return 1;
}

/* Adds an element after the last element if any, returns 0 on failure */
int addValue(Vec* vec, void* ptrToValue, size_t pos) {
    /* If any ptr is null */
    if(!vec || !ptrToValue) {
        return 0;
    }

    /* If the vector is full, resize */
    if(vec->dataTypeSize * (vec->elementsInBuffer + 1) > vec->bufferLength) {

        /* If the position for the new element isnt at the end, mustShift = 1 */
        int mustShift = pos != vec->elementsInBuffer ? 1 : 0;
        _resizeVector(vec, mustShift, pos);

    }

    /* Calculate address for element at index pos */
    void* newElemAddress = vec->buffer + pos * vec->dataTypeSize;

    /* Copy the value from the pointer to the vector */
    if(memcpy(newElemAddress, ptrToValue, vec->dataTypeSize)) {
        vec->elementsInBuffer += 1;
        return 1;
    }

    return 0;
}

int addFront(Vec* vec, void* ptrToValue) {
    return addValue(vec, ptrToValue, 0);
}

int addBack(Vec* vec, void* ptrToValue) {
    return addValue(vec, ptrToValue, vec->elementsInBuffer);
}

int setValue(Vec* vec, void* ptrToValue, size_t pos) {

    /* If any of the ptrs is null, or the position is invalid return false */
    if(
        !vec                            ||
        !ptrToValue                     ||
        pos > vec->elementsInBuffer + 1 ||
        pos > vec->bufferLength
    ) {
        return 0;
    }

    void* elemAddress = vec->buffer + pos * vec->dataTypeSize;
    elemAddress = memcpy(elemAddress, ptrToValue, vec->dataTypeSize);

    /* If failed to copy the value return false */
    if(!elemAddress) {
        return 0;
    }

    return 1;
}

/* Remove @noOfElements from the vector starting at element @index */
int removeValues(Vec* vec, size_t index, size_t noOfElements) {

    void* success = 0;

    // If we need to do not reach the end of vector with our deletion
    if(index + noOfElements - 1 < vec->elementsInBuffer) {
        // Number of the remaining elements after the ones to be deleted
        size_t trailingSubArrayLength = vec->elementsInBuffer - index - noOfElements;
        // Index of the first element after the last one to be deleted
        size_t subArrayFirstElement = index + noOfElements;
        // Address to first element to be deleted
        void* destination = &vec->buffer[index                * vec->dataTypeSize];
        // Address to first element after the set of elements to be deleted
        void* source      = &vec->buffer[subArrayFirstElement * vec->dataTypeSize];
        // Write remaining elements over the ones to be deleted
        success = memcpy(destination, source, trailingSubArrayLength * vec->dataTypeSize);
    }


    if(success) {
        // Update the number of elements
        vec->elementsInBuffer -= noOfElements;
        return 1;
    }
    return 0;
}

int removeValue(Vec* vec, size_t index) {
    return removeValues(vec, index, 1);
}

int removeFront(Vec* vec) {
    return removeValue(vec, 0);
}

int removeBack(Vec* vec) {
    return removeValue(vec, vec->elementsInBuffer - 1);
}























