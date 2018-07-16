#include <stdint.h>

#define MAX_STR_LEN   (33)
#ifndef PASS
  #define PASS        (0)
#endif
#ifndef FAIL
  #define FAIL        (1)
#endif
#ifndef NULL
  #define NULL        (0)
#endif
#define EMPTY_ITEM   \
{                    \
 .key  = {'\0'},     \
 .data = 0           \
}

typedef struct _item {
  char     key[MAX_STR_LEN];
  uint16_t data;
} Item;

typedef struct _hashTb {
  uint16_t itemCnt;
  uint16_t tbSize;
  Item     *itemArray;
} HashTb;

void table_init(HashTb* tb);
void table_print(HashTb *tb);
uint8_t insert_item(HashTb *tb, const Item *item);
uint8_t delete_item(HashTb *tb, const char *key);
Item* search_item(HashTb *tb, const char *key);
