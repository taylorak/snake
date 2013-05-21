#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <curses.h> 
#include <unistd.h>
#include "snake.h"
#include "item.h"

int main(int argc, const char *argv[])
{
  int ch = 0;
  int x,y;

  initscr();            // start curses mode
  raw();                //line buffering disabled
  keypad(stdscr,TRUE);  // enable keypad
  noecho();             // don't echo() while we do getch
  curs_set(0);          // set cursor invisible
  nodelay(stdscr,TRUE);

  snake *snake = init_snake(1,1,RIGHT);
  item *item = init_item(snake,COLS-1,LINES-1);


  if(has_colors() == FALSE){
    endwin();
    printf("Your terminal does not support color\n");
    exit(1);
  }

  start_color();
  init_pair(1,COLOR_GREEN,COLOR_BLACK);
  init_pair(2,COLOR_BLUE,COLOR_BLACK);
  init_pair(3,COLOR_RED,COLOR_YELLOW);

  while(snake->stat == ALIVE && (ch = getch()) != 'q'){
    attron(COLOR_PAIR(2));
    for(y = 0; y < LINES;y++) {
      for(x = 0; x < COLS; x++) {
        mvaddch(y,x,' ');
        if(x == 0 || y == 0 || x == COLS-1 || y == LINES-1){
          mvaddch(y,x,'x');
        }
      }
    }
    attroff(COLOR_PAIR(2));

    int i;
    move_snake(snake);

    attron(COLOR_PAIR(1));
    segment *cur = snake->head;
    for(i = 0; i < snake->length; i++) {
      mvaddch(cur->y,cur->x,CHAR_SNAKE);
      if(cur->next != NULL){
        cur = cur->next;
      }
    }
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(3));
    mvaddch(item->y,item->x,CHAR_ITEM);
    attroff(COLOR_PAIR(3));

    refresh();
    collision(snake,item,COLS-1,LINES-1);
    
    switch(ch){
      case KEY_LEFT:
        if(snake->dir != RIGHT) {
          snake->dir = LEFT;
        }
        break;
      case KEY_RIGHT:
        if(snake->dir != LEFT) {
          snake->dir = RIGHT;
        }
        break;
      case KEY_UP:
        if(snake->dir != DOWN) {
          snake->dir = UP;
        }
        break;
      case KEY_DOWN:
        if(snake->dir != UP) {
          snake->dir = DOWN;
        }
        break;
      default:
        break;
    }
    usleep(100000 - (snake->length * (100000/(COLS*LINES))));
  }
  destroy_snake(snake);
  destroy_item(item);
  endwin(); // end curses mode
  return 0;
}
