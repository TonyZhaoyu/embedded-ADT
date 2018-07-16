#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash_table.h"

#define MULTIPLIER    (97)
#define OCCUPIED      (1)
#define EMPTY         (0)
#define EQAUL         (1)
#define NEQUAL        (0)

static uint8_t validate_key(const char *key);
static uint8_t isItemEmpty(Item *item);
static uint8_t isKeyEqual(Item *item, const char *key);
static uint32_t hashKey(const char *key);
static void init_item(Item *src, uint16_t itemSize);

void table_init(HashTb *tb)
{
  uint8_t i = 0;

  if(!tb) return;
  for(; i < tb->tbSize; i++) {
    init_item(&tb->itemArray[i], sizeof(Item));
  }
  tb->itemCnt = 0;
}

void table_print(HashTb *tb)
{
  uint8_t i = 0;

  for(; i < tb->tbSize; i++) {
    if(strlen(tb->itemArray[i].key) != 0) {
      printf("[key=%s, value=%d]\r\n",
              tb->itemArray[i].key,
              tb->itemArray[i].data);
    }
    else {
      printf("[key=null, value=0]\r\n");
    }
  }
}

uint8_t insert_item(HashTb *tb, const Item *item)
{
  uint8_t ret;
  uint8_t idx;

  ret = validate_key(item->key);
  if (ret == FAIL || tb->itemCnt == tb->tbSize) return FAIL;
  idx = (uint8_t)(hashKey(item->key) % tb->tbSize);
  // Insert the item in an empty spot.
  while(isItemEmpty(&tb->itemArray[idx]) == OCCUPIED) {
    ++idx;
    idx %= tb->tbSize;
  }
  // TOOD: refactory copy method.
  strncpy(tb->itemArray[idx].key, item->key, MAX_STR_LEN);
  tb->itemArray[idx].data = item->data;

  tb->itemCnt++;

  return PASS;
}

uint8_t delete_item(HashTb *tb, const char *key)
{
  uint8_t ret;
  uint8_t idx;
  uint8_t cnt = 0;

  ret = validate_key(key);
  if (ret == FAIL || tb->itemCnt == 0) return FAIL;
  idx = (uint8_t)(hashKey(key) % tb->tbSize);

  while(cnt <= tb->itemCnt) {
    if(isItemEmpty(&tb->itemArray[idx]) == OCCUPIED &&
       isKeyEqual(&tb->itemArray[idx], key) == EQAUL) {
      init_item(&tb->itemArray[idx], sizeof(Item));
      --tb->itemCnt;
      return PASS;
    }

    ++idx;
    ++cnt;
    idx %= tb->tbSize;
  }

  return FAIL;
}

Item* search_item(HashTb *tb, const char *key)
{
  uint8_t ret;
  uint8_t idx;
  uint8_t cnt = 0;

  ret = validate_key(key);
  if (ret == FAIL || tb->itemCnt == 0) return NULL;
  idx = (uint8_t)(hashKey(key) % tb->tbSize);

  while(cnt <= tb->itemCnt) {
    if(isItemEmpty(&tb->itemArray[idx]) == OCCUPIED &&
       isKeyEqual(&tb->itemArray[idx], key) == EQAUL) {
      return &tb->itemArray[idx];
    }

    ++idx;
    ++cnt;
    idx %= tb->tbSize;
  }

  return NULL;
}

static void init_item(Item *src, uint16_t itemSize)
{
  Item invalidItem = EMPTY_ITEM;

  memcpy((void *)src,
         (void *)&invalidItem,
         itemSize);
}

static uint8_t validate_key(const char *key)
{
  if(!key) return FAIL;
  return (strlen(key) <= MAX_STR_LEN - 1) ? PASS : FAIL;
}

static uint32_t hashKey(const char *key)
{
  const unsigned char *us;
  uint32_t h = 0;

  for(us = (const unsigned char *)key; *us; us++) {
    h = h * MULTIPLIER + *us;
  }
  return h;
}

static uint8_t isItemEmpty(Item *item)
{
  if(!item) return FAIL;
  return (strlen(item->key) == 0) ? EMPTY : OCCUPIED;
}

static uint8_t isKeyEqual(Item *item, const char *key)
{
  if(!item || !key) return FAIL;
  return (strncmp(item->key, key, sizeof(item->key)) == 0) ?
         EQAUL : NEQUAL;
}
