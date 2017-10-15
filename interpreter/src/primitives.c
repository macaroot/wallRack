#include "primitives.h"
#include "data.h"

/* Primitives */
int get_lapse(void)
{
	return(state.lapse);
}

void set_lapse(int lapse)
{
	state.lapse = lapse;
}

char get_raw(int number)
{
	return(tape.raw[number]);
}

void set_raw(int number, char chara)
{
	tape.raw[number] = chara;
}

int get_raw_length(void)
{
	return(tape.rawLength);
}

char get_token(void)
{
	return(tape.tok[tape.step]);
}

void set_token(int number, char chara)
{
	tape.tok[number] = chara;
}

int get_token_length(void)
{
	return(tape.tokLength);
}

void slide_tape(int slide)
{
	tape.step += slide;
}

int get_step(void)
{
	return(tape.step);
}

int get_height(void)
{
	return(racks[wall.cur].height);
}

void set_height(int height)
{
	racks[wall.cur].height = height;
}

int get_width(void)
{
	return(wall.width);
}

void set_width(int width)
{
	wall.width = width;
}

int get_used_width(void)
{
	return(wall.usedWidth);
}

void set_used_width(int width)
{
	wall.usedWidth = width;
}

int get_index(void)
{
	return(racks[wall.cur].ind);
}

void set_index(int index)
{
	racks[wall.cur].ind = index;
}

void slide_index(int slide)
{
	racks[wall.cur].ind += slide;
}

int get_shelf(int aber)
{
	return(racks[wall.cur].shelf[racks[wall.cur].ind+aber]);
}

void set_shelf(int aber, int value)
{
	racks[wall.cur].shelf[racks[wall.cur].ind+aber] = value;
}

void set_foreign_shelf(int dest, int aber, int value)
{
	racks[dest].shelf[racks[dest].ind+aber] = value;
}
/*
 *int get_foreign_index(int number)
 *{
 *	return(racks[number].ind);
 *}
 */

void slide_foreign_index(int dest, int slide)
{
	racks[dest].ind += slide;
}

int get_cur(void)
{
	return(wall.cur);
}

void set_cur(int value)
{
	wall.cur = value;
}

int get_pre(void)
{
	return(wall.pre);
}

void set_pre(int value)
{
	wall.pre = value;
}

/* Display necessities */
int get_any_shelf(int rack, int index)
{
	return(racks[rack].shelf[index]);
}

int get_any_height(int number)
{
	return(racks[number].height);
}

int get_any_index(int number)
{
	return(racks[number].ind);
}
