#include <stdlib.h>
#include "memory.h"
#include "data.h"

/* Growing */
void realloc_rack(void)
{
	racks[wall.cur].height *= 0x2;
	racks[wall.cur].shelf = realloc(racks[wall.cur].shelf,
	racks[wall.cur].height * sizeof(int));
}

void realloc_wall(void)
{
	int oldWidth;
	int newWidth;
	int i;
	oldWidth = wall.width;
	wall.width *= 0x2;
	newWidth = wall.width;
	racks = realloc(racks, newWidth * sizeof(struct Rack));
	for(i = oldWidth; i < newWidth; ++i) {
		racks[i].shelf = malloc(state.startHeight * sizeof(int));
		racks[i].ind = -1;
		racks[i].height = state.startHeight;
	}
}

void realloc_raw(void)
{
	tape.rawLength *= 0x2;
	tape.raw = realloc(tape.raw, tape.rawLength * sizeof(char));
}

void realloc_tokens(void)
{
	tape.tokLength *= 0x2;
	tape.tok = realloc(tape.tok, tape.tokLength * sizeof(char));
}

/* Reductions */
void dealloc_rack(void)
{
	racks[wall.cur].height /= 0x2;
	racks[wall.cur].shelf = realloc(racks[wall.cur].shelf,
	racks[wall.cur].height * sizeof(int));
}

void dealloc_wall(void)
{
	int oldWidth;
	int newWidth;
	int i;
	oldWidth = wall.width;
	wall.width /= 0x2;
	newWidth = wall.width;
	for(i = oldWidth; i < newWidth; ++i) {
		free(racks[i].shelf);
	}
	racks = realloc(racks, newWidth * sizeof(struct Rack));
}

/* Wipes */
void wipe_raw(void)
{
	free(tape.raw);
}

void wipe_tokens(void)
{
	free(tape.tok);
}

void wipe_wall(void)
{
	free(racks);
}

void wipe_racks(void)
{
	int i;
	for(i = 0; i < wall.width; ++i) {
		free(racks[i].shelf);
	}
}

/* Inits */
void init_state(void)
{
	state.startHeight = 0x8;
	state.startWidth = 0x4;
	state.startLength = 0x40;
	state.lapse = 0;
	state.error = none;
}

void init_tape(void)
{
	tape.raw = malloc(state.startLength * sizeof(char));
	tape.tok = malloc(state.startLength * sizeof(char));
	tape.rawLength = state.startLength;
	tape.tokLength = state.startLength;
	tape.step = 0;
}

void init_wall(void)
{
	wall.cur = 0;
	wall.pre = 0;
	wall.width = state.startWidth;
	wall.usedWidth = 0;
}

void init_racks(void)
{
	int i;
	racks = malloc(state.startWidth * sizeof(struct Rack));
	for(i = 0; i < state.startWidth; ++i) {
		racks[i].shelf = malloc(state.startHeight * sizeof(int));
		racks[i].ind = -1;
		racks[i].height = state.startHeight;
	}
}

/* Interfaces */
void mem_grow_rack(void)
{
	realloc_rack();
}
void mem_grow_wall(void)
{
	realloc_wall();
}

void mem_grow_raw(void)
{
	realloc_raw();
}

void mem_grow_tokens(void)
{
	realloc_tokens();
}

void mem_reduce_rack(void)
{
	dealloc_rack();
}

void mem_reduce_wall(void)
{
	dealloc_wall();
}

void mem_wipe_raw(void)
{
	wipe_raw();
}

void mem_wipe_rest(void)
{
	wipe_tokens();
	wipe_racks();
	wipe_wall();
}

void mem_init_wall_rack(void)
{
	init_state();
	init_tape();
	init_wall();
	init_racks();
}
