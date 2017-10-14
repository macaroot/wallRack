#include <stdlib.h>
#include "data.h"

/* Data structure */
enum Error {
	none,
	bottom,
	edge
} errorData;

struct State {
	int startHeight;
	int startWidth;
	int startLength;
	int lapse;
	enum Error error;
} stateData;

struct Tape {
	char *raw;
	char *tok;
	int rawLength;
	int tokLength;
	int step;
} tapeData;

struct Rack {
	int *shelf;
	int ind;
	int height;
} *rackArray;

struct Wall {
	int cur;
	int pre;
	int width;
} wallData;

/* Getset definitions */
struct State * get_state_context(void)
{
	return(&stateData);
}

struct Tape * get_tape_context(void)
{
	return(&tapeData);
}

struct Rack ** get_racks_context(void)
{
	return(&rackArray);
}

struct Wall * get_wall_context(void)
{
	return(&wallData);
}

char get_raw(int number)
{
	struct Tape *tape;
	tape = get_tape_context();
	return(tape->raw[number]);
}

void set_raw(int number, char chara)
{
	struct Tape *tape;
	tape = get_tape_context();
	tape->raw[number] = chara;
}

int get_raw_length(void)
{
	struct Tape *tape;
	tape = get_tape_context();
	return(tape->rawLength);
}

void double_raw_length(void)
{
	struct Tape *tape;
	tape = get_tape_context();
	tape->rawLength *= 2;
}

char get_token(void)
{
	struct Tape *tape;
	tape = get_tape_context();
	return(tape->tok[tape->step]);
}

void set_token(int number, char chara)
{
	struct Tape *tape;
	tape = get_tape_context();
	tape->tok[number] = chara;
}

int get_token_length(void)
{
	struct Tape *tape;
	tape = get_tape_context();
	return(tape->tokLength);
}

void double_token_length(void)
{
	struct Tape *tape;
	tape = get_tape_context();
	tape->tokLength *= 2;
}

void slide_tape(int slide)
{
	struct Tape *tape;
	tape = get_tape_context();
	tape->step += slide;
}

int get_height(void)
{
	struct Wall *wall;
	struct Rack **racks;
	wall = get_wall_context();
	racks = get_racks_context();
	return((*racks)[wall->cur].height);
}

void set_height(int height)
{
	struct Wall *wall;
	struct Rack **racks;
	wall = get_wall_context();
	racks = get_racks_context();
	(*racks)[wall->cur].height = height;
}

int get_width(void)
{
	struct Wall *wall;
	wall = get_wall_context();
	return(wall->width);
}

void set_width(int width)
{
	struct Wall *wall;
	wall = get_wall_context();
	wall->width = width;
}

int get_index(void)
{
	struct Wall *wall;
	struct Rack **racks;
	wall = get_wall_context();
	racks = get_racks_context();
	return((*racks)[wall->cur].ind);
}

void set_index(int index)
{
	struct Wall *wall;
	struct Rack **racks;
	wall = get_wall_context();
	racks = get_racks_context();
	(*racks)[wall->cur].ind = index;
}

void slide_index(int slide)
{
	struct Wall *wall;
	struct Rack **racks;
	wall = get_wall_context();
	racks = get_racks_context();
	(*racks)[wall->cur].ind += slide;
}

int get_pre_index(void)
{
	struct Wall *wall;
	struct Rack **racks;
	wall = get_wall_context();
	racks = get_racks_context();
	return((*racks)[wall->pre].ind);
}

void set_pre_index(int index)
{
	struct Wall *wall;
	struct Rack **racks;
	wall = get_wall_context();
	racks = get_racks_context();
	(*racks)[wall->pre].ind = index;
}

void slide_pre_index(int slide)
{
	struct Wall *wall;
	struct Rack **racks;
	wall = get_wall_context();
	racks = get_racks_context();
	(*racks)[wall->pre].ind += slide;
}

int get_shelf(int aber)
{
	struct Wall *wall;
	struct Rack **racks;
	wall = get_wall_context();
	racks = get_racks_context();
	return((*racks)[wall->cur].shelf[(*racks)[wall->cur].ind+aber]);
}

void set_shelf(int aber, int value)
{
	struct Wall *wall;
	struct Rack **racks;
	wall = get_wall_context();
	racks = get_racks_context();
	(*racks)[wall->cur].shelf[(*racks)[wall->cur].ind+aber] = value;
}

void set_foreign_shelf(int dest, int aber, int value)
{
	struct Rack **racks;
	racks = get_racks_context();
	(*racks)[dest].shelf[(*racks)[dest].ind+aber] = value;
}

void slide_foreign_index(int dest, int slide)
{
	struct Rack **racks;
	racks = get_racks_context();
	(*racks)[dest].ind += slide;
}

int get_cur(void)
{
	struct Wall *wall;
	wall = get_wall_context();
	return(wall->cur);
}

void set_cur(int value)
{
	struct Wall *wall;
	wall = get_wall_context();
	wall->cur = value;
}

int get_pre(void)
{
	struct Wall *wall;
	wall = get_wall_context();
	return(wall->pre);
}

void set_pre(int value)
{
	struct Wall *wall;
	wall = get_wall_context();
	wall->pre = value;
}

/* General */
void realloc_raw(void)
{
	struct Tape *tape;
	tape = get_tape_context();
	tape->raw = (char*)realloc(tape->raw, tape->rawLength);
}

void realloc_tokens(void)
{
	struct Tape *tape;
	tape = get_tape_context();
	tape->tok = (char*)realloc(tape->tok, tape->tokLength);
}

void realloc_rack(void)
{
	struct Wall *wall;
	struct Rack **racks;
	wall = get_wall_context();
	racks = get_racks_context();
	(*racks)[wall->cur].shelf = realloc((*racks)[wall->cur].shelf,
	(*racks)[wall->cur].height * sizeof(int));
}

void realloc_wall(void)
{
	struct Wall *wall;
	struct Rack **racks;
	wall = get_wall_context();
	racks = get_racks_context();
	*racks = realloc(*racks, wall->width * sizeof(struct Rack));
}

void free_raw(void)
{
	struct Tape *tape;
	tape = get_tape_context();
	free(tape->raw);
}

void free_tokens(void)
{
	struct Tape *tape;
	tape = get_tape_context();
	free(tape->tok);
}

void free_racks(void)
{
	struct Wall *wall;
	struct Rack **racks;
	int i;
	wall = get_wall_context();
	racks = get_racks_context();
	for(i = 0; i < wall->width; ++i) {
		free((*racks)[i].shelf);
	}
}

void free_wall(void)
{
	struct Rack **racks;
	racks = get_racks_context();
	free(*racks);
}

/* Inits */
void init_state(void)
{
	struct State *state;
	state = get_state_context();
	state->startHeight = 0x8;
	state->startWidth = 0x4;
	state->startLength = 0x40;
	state->lapse = 0;
	state->error = none;
}

void init_tape(void)
{
	struct State *state;
	struct Tape *tape;
	state = get_state_context();
	tape = get_tape_context();
	tape->raw = malloc(state->startLength * sizeof(char));
	tape->tok = malloc(state->startLength * sizeof(char));
	tape->rawLength = state->startLength;
	tape->tokLength = state->startLength;
	tape->step = 0;
}

void init_wall(void)
{
	struct State *state;
	struct Wall *wall;
	state = get_state_context();
	wall = get_wall_context();
	wall->cur = 0;
	wall->pre = 0;
	wall->width = state->startWidth;
}

void init_racks(void)
{
	struct State *state;
	struct Rack **racks;
	int i;
	state = get_state_context();
	racks = get_racks_context();
	*racks = malloc(state->startWidth * sizeof(struct Rack));
	for(i = 0; i < state->startWidth; ++i) {
		(*racks+i)->shelf = malloc(state->startHeight * sizeof(int));
		(*racks+i)->ind = -1;
		(*racks+i)->height = state->startHeight;
	}
}

void init_wall_rack(void)
{
	init_state();
	init_tape();
	init_wall();
	init_racks();
}


int get_any_shelf(int rack, int index)
{
	struct Rack **racks;
	racks = get_racks_context();
	return((*racks)[rack].shelf[index]);
}

int get_any_height(int number)
{
	struct Rack **racks;
	racks = get_racks_context();
	return((*racks)[number].height);
}

int get_any_index(int number)
{
	struct Rack **racks;
	racks = get_racks_context();
	return((*racks)[number].ind);
}
