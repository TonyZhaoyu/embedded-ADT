#include <stdio.h>
#include <assert.h>
#include "ring_buf.h"

#define BUFFER_SIZE  (3)

void *bufferPtr[BUFFER_SIZE];
int  buffer[BUFFER_SIZE];
RingBuffer rb;

static void copy_buffer(void *dataTo, void *dataFrom)
{
  int *tempDataTo   = (int *)dataTo;
  int *tempDataFrom = (int *)dataFrom;
  *tempDataTo = *tempDataFrom;
}

int main(int argc, char *argv[])
{
  for(uint8_t i = 0; i < BUFFER_SIZE; i++) {
    bufferPtr[i] = (void *)&buffer[i];
  }
  rb_init(&rb, bufferPtr, BUFFER_SIZE, copy_buffer);

  int i = 1;
  void *getNum;
  assert(rb_set(&rb, &i) == 0);
  assert(rb_count(&rb) == 1);
  assert(rb_isempty(&rb) == 0);
  assert(rb_get(&rb, &getNum) == 0);
  assert(*(int *)getNum == 1);
  i = 2;
  assert(rb_set(&rb, &i) == 0);
  assert(rb_count(&rb) == 1);
  assert(rb_isempty(&rb) == 0);
  assert(rb_get(&rb, &getNum) == 0);
  assert(*(int *)getNum == 2);

  /* Insert 3,4 */
  i = 3;
  assert(rb_set(&rb, &i) == 0);
  i = 4;
  assert(rb_set(&rb, &i) == 0);

  assert(rb_count(&rb) == 2);
  assert(rb_isempty(&rb) == 0);
  assert(rb_isfull(&rb) == 1);

  // Since full, cannot insert.
  i = 5;
  assert(rb_set(&rb, &i) == 1);

  // Read out. FIFO.
  assert(rb_get(&rb, &getNum) == 0);
  assert(*(int *)getNum == 3);
  assert(rb_get(&rb, &getNum) == 0);
  assert(*(int *)getNum == 4);
  assert(rb_isempty(&rb) == 1);

  return 0;
}
