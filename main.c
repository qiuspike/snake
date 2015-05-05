#include <curses.h>
#include "snake.h"

// Global curses vars
// KEY_UP
// KEY_DOWN
// KEY_LEFT
// KEY_RIGHT

// COLS
// LINES
// End global curses vars

extern int delay;// delay for timer value and interval
extern position dir;	  // dir for where the snake go
extern position food;	 // food for the positionition of the food
extern position p1;		// tmp store
extern queue Q;	   // define queue


int
main()
{
	int ch;

	init();
	// Decide direct and 'q' to quit
	while ((ch = getch()) != 'q') {
		// How miraculous is this!
		// equal to zero for the direction control
		if (ch == KEY_UP && dir.y == 0) {
			dir.y = -1;
			dir.x = 0;
		}
		if (ch == KEY_DOWN && dir.y == 0) {
			dir.y = +1;
			dir.x = 0;
		}
		if (ch == KEY_LEFT && dir.x == 0) {
			dir.y = 0;
			dir.x = -1;
		}
		if (ch == KEY_RIGHT && dir.x == 0) {
			dir.y = 0;
			dir.x = +1;
		}
	}
	end();

	return 0;
}


