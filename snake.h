#ifndef SNAKE_H
#define SNAKE_H


#define  SHAPE  '*'
#define  BLANK  ' '
#define  FOOD   '@'


// The struct for positionition
typedef struct {
	int x;  // x to col
	int y;  // y to row
} position;


// The struct of snake node
struct snake;
struct q_node;
typedef struct snake  *ptr_snake;
typedef struct q_node *queue;

struct snake {
	position pos;
	ptr_snake pre;
	ptr_snake next;
};

// The struct for queue's front and rear
struct q_node {
	ptr_snake front;
	ptr_snake rear;
};

// Operation for the snake node
void init_queue(queue Q);	// init a queue
void destroy_queue(queue Q);	// destroy a queue
position get_front(queue Q);
void front_enqueue(position X, queue Q);	// enqueue X at front
position rear_dequeue(queue Q);	// dequeue from rear
// End

// For error handling
void error(const char s[]);
void fatal_error(const char s[]);
// End

// init the terminal environment
void init();
// the moving of the snake
void snake_move();
// random produce food
void produce_food();
// set iterval timer
int set_ticker(int);
// reset terminal and free memory
void end();


// void death();
// reset the terminal environment and free memory
// void end();

// TODO where to set them? Is this a sytax(?) of cpp but not pure c?
// Some global vars
int delay, ndelay;	// delay for timer value and interval
int hour, min, sec;
int level;

position dir;	  // dir for where the snake go
position food;	 // food for the positionition of the food
position p1;		// tmp store
queue Q;	   // define queue

#endif
//	SNAKE_H
