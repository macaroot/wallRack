#ifndef DATA_H
#define DATA_H

/* Data structure */
enum Error {
	none,
	bottom,
	edge
} errorContext;

struct State {
	int startHeight;
	int startWidth;
	int startLength;
	int lapse;
	enum Error error;
} state;

struct Tape {
	char *raw;
	char *tok;
	int rawLength;
	int tokLength;
	int step;
} tape;

struct Rack {
	int *shelf;
	int ind;
	int height;
} *racks;

struct Wall {
	int cur;
	int pre;
	int width;
	int usedWidth;
} wall;


#endif
