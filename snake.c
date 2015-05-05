#include <curses.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include "snake.h"



void
init()
{
	// Terminal environment init
	WINDOW *wnd;

	wnd = initscr();
	keypad(wnd, TRUE);
	cbreak();
	noecho();
	clear();

	// dir init
	dir.x = 0;
	dir.y = 0;
	// food init
	food.x = 0;
	food.y = 0;
	// interval timer value
	delay = 200;

	p1.x = 5;
	p1.y = 5;
	Q = (queue)malloc(sizeof(struct q_node));
	init_queue(Q);
	front_enqueue(p1, Q);

	move(p1.y, p1.x);
	addch(SHAPE);
	move(LINES-1, COLS-1);
	refresh();
	produce_food();	// TODO food before snake
	refresh();

	// Signal and ticker TODO
	signal(SIGALRM, snake_move);	//Use timer to control moving.
	set_ticker(delay);
}


// This func is for signal
void
snake_move()	//TODO
{
	// if (position.x > COLS)

	// for the node next front
	// need one more method to just get front node pos
	p1 = get_front(Q); // haven't been implemented
	p1.x += dir.x;
	p1.y += dir.y;
	// cross the border at right and left
	if (p1.x > COLS-1)
		p1.x = 0;
	else if (p1.x < 0)
		p1.x = COLS-1;
	// cross the border at down and up
	if (p1.y > LINES-1)
		p1.y = 0;
	else if (p1.y < 0)
		p1.y = LINES-1;

	front_enqueue(p1, Q);
	move(p1.y, p1.x);
	addch(SHAPE);

	if ((p1.x == food.x) && (p1.y == food.y))	// 1 for eat, 0 for not eat
		produce_food();
	else {
		p1 = rear_dequeue(Q);
		move(p1.y, p1.x);
		addch(BLANK);
		move(LINES-1, COLS-1);
	}

	refresh();
	signal(SIGALRM, snake_move); // set the signal again
}

//TODO
void
produce_food()
{
	// TODO Is there any better to produce random?
	// This is just a fake random that every time run the program
	// the random is the same as before.
	food.x = rand() % COLS;	//COLS AND LINES IN THE TERMINAL
	food.y = rand() % (LINES - 1); //use one line to show some info.
	move(food.y, food.x);
	addch(FOOD);
	move(LINES-1, COLS-1);
}

int
set_ticker(int n_msecs)	// Set the interval timer
{							// TODO it is just ok, but for a snake with level,
	struct itimerval new_timeset; // there have many things to do.
	long n_sec, n_usecs;

	n_sec = n_msecs / 1000;
	n_usecs = (n_msecs % 1000) * 1000L;

	new_timeset.it_interval.tv_sec = n_sec;
	new_timeset.it_interval.tv_usec = n_usecs;

	new_timeset.it_value.tv_sec = n_sec;
	new_timeset.it_value.tv_usec = n_usecs;

	return setitimer(ITIMER_REAL, &new_timeset, NULL);
}

void
end()
{
	endwin();	// Reset the terminal.
	destroy_queue(Q);
	free(Q);
}
