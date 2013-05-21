#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "item.h"
#include "snake.h"

item *init_item(snake *snake,int max_x,int max_y)
{
  item *new_item = malloc(sizeof(item));
  
  change_pos(snake,new_item,max_x,max_y);
  return new_item;
}

int change_pos(snake *snake,item *item,int max_x,int max_y)
{
  int x = -1;
  int y = -1;
  segment *cur = snake->head;

  srand(time(NULL));
  while(x < 0 && y < 0 && y != max_y && x != max_x) {
    x = rand() %(max_x-1) + 1;
    y = rand() % (max_y-1) + 1;

    while((cur = cur->next) != NULL) {
      if((cur->x == x && cur->y == y)){
        x = -1;
        y = -1;
      }
    }
  }

  item->x = x;
  item->y = y;
  return 0;
}

int collision(snake *snake,item *item,int x_max,int y_max)
{
  int i;
  segment *cur = snake->head;

  if (snake->head->x == item->x && snake->head->y == item->y) {
    change_pos(snake,item,x_max,y_max);
    add_segment(snake);
    return 0; 
  }

  for (i = 0 ; i < snake->length; i++) {
    if(cur->next != NULL){
      cur = cur->next;


      if(cur->x == snake->head->x && cur->y == snake->head->y) {
        die(snake);
        return -1;
      }
    }
  }

  if(snake->head->x == 0 || snake->head->y == 0 || snake->head->x == x_max || snake->head->y == y_max) {
    die(snake);
    return -1;
  }
  
  return 0;
}


int destroy_item(item *item)
{
  free(item);

  return 0;
}
