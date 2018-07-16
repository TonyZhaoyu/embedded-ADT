#include <stdio.h>
#include <assert.h>
#include "hash_table.h"

#define MAX_TB_SIZE   (5)

int main(int argc, char **argv)
{
  // Test hash table.
  Item itemArray[MAX_TB_SIZE];
  HashTb uuidTb;
  uuidTb.tbSize = MAX_TB_SIZE;
  uuidTb.itemArray = itemArray;

  // Test items.
  Item tstItem_1 = {
    .key = "53696C6162734465762DAF8D64570B00",
    .data = 0x1
  };

  Item tstItem_2 = {
    .key = "53696C6162734465762D5E50BE570B00",
    .data = 0x2
  };

  Item tstItem_3 = {
    .key = "53696C6162734465762D1D5731570B00",
    .data = 0x3
  };

  Item tstItem_4 = {
    .key = "53696C6162734465762DFA8C64570B00",
    .data = 0x4
  };

  Item tstItem_5 = {
    .key = "53696C6162734465762DA68764570B00",
    .data = 0x5
  };

  Item tstItem_6 = {
    .key = "53696C6162734465762D9B8D64570B00",
    .data = 0x6
  };

  Item *retItem;

  // Init table tests.
  table_init(&uuidTb);
  printf("---- Init uuidTb ----:\r\n");
  table_print(&uuidTb);
  // Insertion test.
  assert(insert_item(&uuidTb, &tstItem_1) == PASS);
  assert(insert_item(&uuidTb, &tstItem_2) == PASS);
  assert(insert_item(&uuidTb, &tstItem_3) == PASS);
  assert(insert_item(&uuidTb, &tstItem_4) == PASS);
  assert(insert_item(&uuidTb, &tstItem_5) == PASS);
  assert(insert_item(&uuidTb, &tstItem_6) == FAIL);
  printf("---- Insert uuidTb ----:\r\n");
  table_print(&uuidTb);
  // Search item tests.
  retItem = search_item(&uuidTb, tstItem_1.key);
  assert(retItem != NULL && retItem->data == 0x1);
  retItem = search_item(&uuidTb, tstItem_2.key);
  assert(retItem != NULL && retItem->data == 0x2);
  retItem = search_item(&uuidTb, tstItem_3.key);
  assert(retItem != NULL && retItem->data == 0x3);
  retItem = search_item(&uuidTb, tstItem_4.key);
  assert(retItem != NULL && retItem->data == 0x4);
  retItem = search_item(&uuidTb, tstItem_5.key);
  assert(retItem != NULL && retItem->data == 0x5);
  retItem = search_item(&uuidTb, tstItem_6.key);
  assert(retItem == NULL);
  // Deletion tests.
  assert(delete_item(&uuidTb, tstItem_1.key) == PASS);
  assert(delete_item(&uuidTb, tstItem_3.key) == PASS);
  assert(delete_item(&uuidTb, tstItem_4.key) == PASS);
  printf("---- Delete item in uuidTb ----:\r\n");
  table_print(&uuidTb);
  retItem = search_item(&uuidTb, tstItem_1.key);
  assert(retItem == NULL);
  retItem = search_item(&uuidTb, tstItem_2.key);
  assert(retItem != NULL && retItem->data == 0x2);
  retItem = search_item(&uuidTb, tstItem_3.key);
  assert(retItem == NULL);
  retItem = search_item(&uuidTb, tstItem_4.key);
  assert(retItem == NULL);
  retItem = search_item(&uuidTb, tstItem_5.key);
  assert(retItem != NULL && retItem->data == 0x5);
  // Regresstion tst_0.
  assert(insert_item(&uuidTb, &tstItem_4) == PASS);
  assert(insert_item(&uuidTb, &tstItem_3) == PASS);
  assert(insert_item(&uuidTb, &tstItem_6) == PASS);
  printf("---- Regression tst_0 of uuidTb ----:\r\n");
  table_print(&uuidTb);
  retItem = search_item(&uuidTb, tstItem_1.key);
  assert(retItem == NULL);
  retItem = search_item(&uuidTb, tstItem_2.key);
  assert(retItem != NULL && retItem->data == 0x2);
  retItem = search_item(&uuidTb, tstItem_3.key);
  assert(retItem != NULL && retItem->data == 0x3);
  retItem = search_item(&uuidTb, tstItem_4.key);
  assert(retItem != NULL && retItem->data == 0x4);
  retItem = search_item(&uuidTb, tstItem_5.key);
  assert(retItem != NULL && retItem->data == 0x5);
  retItem = search_item(&uuidTb, tstItem_6.key);
  assert(retItem != NULL && retItem->data == 0x6);
  // Regression tst_1.
  assert(delete_item(&uuidTb, tstItem_1.key) == FAIL);
  assert(delete_item(&uuidTb, tstItem_3.key) == PASS);
  assert(delete_item(&uuidTb, tstItem_5.key) == PASS);
  printf("---- Regression tst_1 of uuidTb ----:\r\n");
  table_print(&uuidTb);

  return 0;
}
