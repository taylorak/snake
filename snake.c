#include <stdio.h>
#include <stdlib.h>
#include "snake.h"
#include "item.h"

snake *init_snake(int x_pos, int y_pos,direction dir)
{
  // init new snake and first segment
  snake *new_snake       = NULL;
  segment *first_segment = NULL;
  if((new_snake = malloc(sizeof(snake))) == NULL) {
    return NULL;
  }
  if((first_segment = malloc(sizeof(segment))) == NULL) {
    return NULL;
  }

  first_segment->x = x_pos;
  first_segment->y = y_pos;
  first_segment->prev = NULL;
  first_segment->next = NULL;
 
  // init snake variables
  new_snake->stat = ALIVE;
  new_snake->dir  = dir;
  new_snake->head = first_segment;
  new_snake->tail = first_segment;
  new_snake->length   = 1;

  return new_snake;
}

int move_snake(snake *snake)
{
  // current tail
  segment *cur_tail = snake->tail;
  
  // check that snake has more than one part
  if(snake->head != snake->tail){
   
    // remove tail
    snake->tail           = cur_tail->prev;
    cur_tail->prev->next  = NULL;

    // move tail to head
    cur_tail->x = snake->head->x;
    cur_tail->y = snake->head->y;
    
    cur_tail->prev    = NULL;
    cur_tail->next    = snake->head;
    snake->head->prev = cur_tail;
    snake->head       = cur_tail;

  }
  
  // move the head
  switch (snake->dir){
    case UP:
      snake->head->y--;
      break;
    case DOWN:
      snake->head->y++;
      break;
    case RIGHT:
      snake->head->x++;
      break;
    case LEFT:
      snake->head->x--;
      break;
    default:
      break;
  }

  return 0;
}

int add_segment(snake *snake)
{
  // create new segment
  segment *new_segment = malloc(sizeof(segment));
  
  // place new segment on tail
  new_segment->x    = snake->tail->x;
  new_segment->y    = snake->tail->y;
  new_segment->prev = snake->tail;
  new_segment->next = NULL;

  // make new segment the tail
  snake->tail->next = new_segment;
  snake->tail       = new_segment;
  snake->length++;
  
  return 0;
}

int destroy_snake(snake *snake)
{
  int i;
  segment *cur = snake->head;
  
  // free segments
  for (i = 0 ; i < snake->length; i++) {
    free(cur);
    if(cur->next != NULL){
      cur = cur->next;
    }
  }
  
  // free snake
  free(snake);

  return 0; 
}

int die(snake *snake)
{
  // kill snake
  snake->stat = DEAD;
  return 0;
}
