#include "unity.h"
#include "CircularBuffer.h"
#include "Integer.h"

void setUp(void) {}

void tearDown(void) {}

void test_circularBufferNew_should_create_new_CircularBuffer_object_of_integer_type() {
	CircularBuffer *cb = circularBufferNew(7, sizeof(int));
	TEST_ASSERT_NOT_NULL(cb);
	TEST_ASSERT_NOT_NULL(cb->buffer);
	TEST_ASSERT_EQUAL_PTR(cb->buffer, cb->head);
	TEST_ASSERT_EQUAL_PTR(cb->buffer, cb->tail);
	TEST_ASSERT_EQUAL(0, cb->size);
	TEST_ASSERT_EQUAL(7, cb->length);
	TEST_ASSERT_EQUAL(sizeof(int), cb->sizeOfType);
	circularBufferDel(cb);
}

void test_circularBufferNew_should_create_new_CircularBuffer_object_of_double_type() {
	CircularBuffer *cb = circularBufferNew(13, sizeof(double));
	TEST_ASSERT_NOT_NULL(cb);
	TEST_ASSERT_NOT_NULL(cb->buffer);
	TEST_ASSERT_EQUAL_PTR(cb->buffer, cb->head);
	TEST_ASSERT_EQUAL_PTR(cb->buffer, cb->tail);
	TEST_ASSERT_EQUAL(0, cb->size);
	TEST_ASSERT_EQUAL(13, cb->length);
	TEST_ASSERT_EQUAL(sizeof(double), cb->sizeOfType);
	circularBufferDel(cb);
}

void test_circularBufferAddInt_1_integer_should_add_0xbeef() {
	CircularBuffer *cb = circularBufferNew(4, sizeof(int));	
	int integer = 0xbeef;
	
	circularBufferAddInt(cb, &integer);
	TEST_ASSERT_EQUAL(1, cb->size);
	TEST_ASSERT_EQUAL(4, cb->length);
	TEST_ASSERT_EQUAL((int *)cb->head, &((int *)cb->buffer)[1]);
	TEST_ASSERT_EQUAL((int *)cb->tail, &((int *)cb->buffer)[0]);
	TEST_ASSERT_EQUAL(0xbeef, ((int *)cb->buffer)[0]);
	circularBufferDel(cb);
}

void test_circularBufferAddInt_2_integers_should_add_the_2_integers() {
	CircularBuffer *cb = circularBufferNew(4, sizeof(int));	
	int arrayInts[] = {0xdead, 0xbeef};
	
	circularBufferAddInt(cb, &arrayInts[0]);
	circularBufferAddInt(cb, &arrayInts[1]);
	TEST_ASSERT_EQUAL(2, cb->size);
	TEST_ASSERT_EQUAL(4, cb->length);
	TEST_ASSERT_EQUAL((int *)cb->head, &((int *)cb->buffer)[2]);
	TEST_ASSERT_EQUAL((int *)cb->tail, &((int *)cb->buffer)[0]);
	TEST_ASSERT_EQUAL(0xdead, ((int *)cb->buffer)[0]);
	TEST_ASSERT_EQUAL(0xbeef, ((int *)cb->buffer)[1]);
	circularBufferDel(cb);
}

void test_circularBufferRemoveInt_an_integer_should_remain_1_integer_in_buffer() {
	CircularBuffer *cb = circularBufferNew(4, sizeof(int));	
	int arrayInts[] = {0xdead, 0xbeef};
	int data;
	
	circularBufferAddInt(cb, &arrayInts[0]);
	circularBufferAddInt(cb, &arrayInts[1]);
	circularBufferRemoveInt(cb, &data);
	TEST_ASSERT_EQUAL(2, cb->size);
	TEST_ASSERT_EQUAL(0xdead, data);	
	TEST_ASSERT_EQUAL((int *)cb->head, &((int *)cb->buffer)[2]);
	TEST_ASSERT_EQUAL((int *)cb->tail, &((int *)cb->buffer)[1]);
	TEST_ASSERT_EQUAL(0xbeef, ((int *)cb->buffer)[1]);
	circularBufferDel(cb);
}

void test_circularBufferAddInt_until_overflow_should_wrap_over_to_beginning_of_buffer() {
	CircularBuffer *cb = circularBufferNew(4, sizeof(int));	
	int arrayInts[] = {0xdead, 0xbeef, 0xbad, 0xc0ffee, 0xfee1bad};
	int data;
	
	circularBufferAddInt(cb, &arrayInts[0]);
	circularBufferAddInt(cb, &arrayInts[1]);
	circularBufferAddInt(cb, &arrayInts[2]);
	circularBufferAddInt(cb, &arrayInts[3]);
	circularBufferRemoveInt(cb, &data);
	circularBufferAddInt(cb, &arrayInts[4]);			// should wrap over
	TEST_ASSERT_EQUAL(4, cb->size);
	TEST_ASSERT_EQUAL(0xdead, data);	
	TEST_ASSERT_EQUAL((int *)cb->head, &((int *)cb->buffer)[1]);
	TEST_ASSERT_EQUAL((int *)cb->tail, &((int *)cb->buffer)[1]);
	TEST_ASSERT_EQUAL(0xbeef, ((int *)cb->buffer)[1]);
	TEST_ASSERT_EQUAL(0xbad, ((int *)cb->buffer)[2]);
	TEST_ASSERT_EQUAL(0xc0ffee, ((int *)cb->buffer)[3]);
	TEST_ASSERT_EQUAL(0xfee1bad, ((int *)cb->buffer)[0]);
	circularBufferDel(cb);
}

void test_circularBufferRemoveInt_until_overflow_should_wrap_over_to_beginning_of_buffer() {
	CircularBuffer *cb = circularBufferNew(4, sizeof(int));	
	int arrayInts[] = {0xdead, 0xbeef, 0xbad, 0xc0ffee, 0xfee1bad};
	int data;
	
	circularBufferAddInt(cb, &arrayInts[0]);
	circularBufferAddInt(cb, &arrayInts[1]);
	circularBufferAddInt(cb, &arrayInts[2]);
	circularBufferAddInt(cb, &arrayInts[3]);
	circularBufferRemoveInt(cb, &data);
	TEST_ASSERT_EQUAL(0xdead, data);
	circularBufferAddInt(cb, &arrayInts[4]);			// should wrap over
	circularBufferRemoveInt(cb, &data);
	TEST_ASSERT_EQUAL(0xbeef, data);
	circularBufferRemoveInt(cb, &data);
	TEST_ASSERT_EQUAL(0xbad, data);
	circularBufferRemoveInt(cb, &data);
	TEST_ASSERT_EQUAL(0xc0ffee, data);
	circularBufferRemoveInt(cb, &data);
	TEST_ASSERT_EQUAL(0xfee1bad, data);
	TEST_ASSERT_EQUAL(0, cb->size);		
	TEST_ASSERT_EQUAL((int *)cb->head, &((int *)cb->buffer)[1]);
	TEST_ASSERT_EQUAL((int *)cb->tail, &((int *)cb->buffer)[1]);
	circularBufferDel(cb);
}