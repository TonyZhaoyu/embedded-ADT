#include <stdint.h>

typedef void * rbData;
typedef void (* copyDataFunc)(void *dataTo,
                              void *dataFrom);

typedef struct _RingBuffer
{
  rbData  *buf;
  uint8_t length;
  uint8_t head;
  uint8_t tail;
  uint8_t itemCnt;
  copyDataFunc cpyFunc;
} RingBuffer;

void rb_init(RingBuffer *rb,
             rbData *dataArray,
             uint8_t length,
             copyDataFunc func);
uint8_t rb_isempty(RingBuffer *rb);
uint8_t rb_isfull(RingBuffer *rb);
uint8_t rb_get(RingBuffer *rb, rbData *data);
uint8_t rb_set(RingBuffer *rb, rbData data);
uint8_t rb_peek(RingBuffer *rb, rbData *data);
uint8_t rb_count(RingBuffer *rb);
