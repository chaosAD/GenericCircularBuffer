#ifndef CircularBuffer_H
#define CircularBuffer_H

#define circularBufferAddInt(cb, data)													\
												circularBufferAdd(cb, data, copyInt)
#define circularBufferRemoveInt(cb, data)												\
												circularBufferRemove(cb, data, copyInt)

typedef struct {
	void *head;
	void *tail;
	int length;						// total number of items allowable in the buffer
	int size;							// current number of item in the buffer
	int sizeOfType;
	void *buffer;	
} CircularBuffer;

CircularBuffer *circularBufferNew(int length, int sizeOfType);
void circularBufferAdd(CircularBuffer *cb, void *data, void (*copy)(void *, void *));
void circularBufferRemove(CircularBuffer *cb, void *data, void (*copy)(void *, void *));
void circularBufferIsEmpty(CircularBuffer *cb);
void circularBufferIsFull(CircularBuffer *cb);
void circularBufferDel(CircularBuffer *cb);

#endif // CircularBuffer_H
