#include "ring_buf.h"

/*
 * @brief: initialize a ring buffer.
 * @param[in]: rb - pointer to a ring buffer.
 * @param[in]: dataArray - pointer to an array containing
 *             void pointers. The last item must be empty.
 * @param[in]: length - the length of dataArray.
 * @param[in]: func - function pointer to deep copy items.
 */
void rb_init(RingBuffer *rb, rbData *dataArray,
             uint8_t length, copyDataFunc func)
{
  rb->buf     = dataArray;
  rb->length  = length;
  rb->head    = 0;
  rb->tail    = 0;
  rb->itemCnt = 0;
  rb->cpyFunc = func;
}

/*
 * @brief: return 1 for emnpty, 0 for not empty.
 */
uint8_t rb_isempty(RingBuffer *rb)
{
  return (rb->head == rb->tail ? 1 : 0);
}

/*
 * @brief: return 1 for full, 0 for not not full.
 */
uint8_t rb_isfull(RingBuffer *rb)
{
  return (((rb->tail + 1) % rb->length) == rb->head ? 1 : 0);
}

/*
 * @brief: get an element from the buffer, and reset the head.
 * @param[in]: rb - pointer to the ring buffer.
 * @param[out]: data - pointer to the pointer of consumed data.
 * @return: 0 for success, 1 for fail.
 */
uint8_t rb_get(RingBuffer *rb, rbData *data)
{
  if (rb->head == rb->tail) {
    return 1;
  } else {
    *data = rb->buf[rb->head];
    rb->head = (rb->head + 1) % rb->length;
    rb->itemCnt--;
    return 0;
  }
}

/*
 * @brief: set an element into the buffer, and reset the tail.
 * @param[in]: rb - pointer to the ring buffer.
 * @param[in]: data - pointer to the data to be set.
 * @return: 0 for success, 1 for fail.
 */
uint8_t rb_set(RingBuffer *rb, rbData data)
{
  uint8_t nextTail;
  nextTail = (rb->tail + 1) % rb->length;
  if (nextTail == rb->head){
    return 1;
  } else {
    if(rb->cpyFunc != 0) {
      rb->cpyFunc((void *)rb->buf[rb->tail],
                  (void *)data);
    } else {
      return 1;
    }
    rb->tail = nextTail;
    rb->itemCnt++;
    return 0;
  }
}

/*
 * @brief: peek an element from the buffer, and head is retained.
 * @param[in]: rb - pointer to the ring buffer.
 * @param[out]: data - pointer to the pointer of consumed data.
 * @return: 0 for success, 1 for fail.
 */
uint8_t rb_peek(RingBuffer *rb, rbData *data)
{
  if (rb->head == rb->tail) {
    return 1;
  } else {
    *data = rb->buf[rb->head];
    return 0;
  }
}

/*
 * @brief: get the item count.
 * @param[in]: rb - pointer to the ring buffer.
 * @return: item count.
 */
uint8_t rb_count(RingBuffer *rb)
{
    return rb->itemCnt;
}
