#include <malloc.h>
#include "CircularBuffer.h"

CircularBuffer *circularBufferNew(int length, int sizeOfType) {
	CircularBuffer *cb = malloc(sizeof(CircularBuffer));
	cb->length = length;
	cb->size = 0;
	cb->sizeOfType = sizeOfType;
	cb->head = cb->tail = cb->buffer = malloc(sizeOfType * length);	
	return cb;
}

void circularBufferAdd(CircularBuffer *cb, void *data, void (*copy)(void *, void *)) {	
}

void circularBufferRemove(CircularBuffer *cb, void *data, void (*copy)(void *, void *)) {	
}

void circularBufferDel(CircularBuffer *cb) {
	if(cb) {
		if(cb->buffer)
			free(cb->buffer);
		free(cb);
	}
}