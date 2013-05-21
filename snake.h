#ifndef SNAKE_H_
#define SNAKE_H_

#define CHAR_SNAKE 'o'

typedef enum direction {
  NONE,
  UP,
  DOWN,
  LEFT,
  RIGHT,
} direction;

typedef enum status {
  ALIVE,
  DEAD,
} status;

typedef struct segment {
  int x;
  int y;
  struct segment *prev;
  struct segment *next;
} segment;

typedef struct snake {
  int length;
  status stat;
  direction dir;
  segment *head;
  segment *tail;
} snake;

// prototypes
snake *init_snake(int x_pos, int y_pos, direction dir);
int move_snake(snake *snake);
int add_segment(snake *snake);
int destroy_snake(snake *snake);
int die(snake *snake);

#endif /* SNAKE_H_ */
