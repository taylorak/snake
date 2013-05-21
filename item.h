#ifndef ITEM_H_
#define ITEM_H_

#define CHAR_ITEM '*'
#include "snake.h"

typedef struct item {
  int x;
  int y;
} item;

// prototypes
item *init_item(snake *snake,int x_pos,int y_pox);
int change_pos(snake *snake,item *item,int max_x,int max_y);
int collision(snake *snake,item *item,int x_max,int y_max);
int destroy_item(item *item);

#endif /* ITEM_H_ */
