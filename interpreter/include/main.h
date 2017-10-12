#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef MAIN_H
#define MAIN_H

/* Data structure */
enum Error {
	none,
	top,
	bottom,
	edge
};
struct State {
	int startHeight;
	int startWidth;
	int startLength;
	int lapse;
	enum Error error;
};
struct Tape {
	char *raw;
	char *tok;
	int step;
};
struct Rack {
	int *shelf;
	int ind;
	int height;
};
struct Wall {
	int cur;
	int pre;
	int width;
};

#endif
