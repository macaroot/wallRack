#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "operators.h"
#include "primitives.h"
#include "memory.h"

void op_insert_num(int number)
{
	slide_index(1);
	set_shelf(0, number);
}

void op_insert_cur(void)
{
	slide_index(1);
	set_shelf(0, get_cur());
}

void op_insert_pre(void)
{
	slide_index(1);
	set_shelf(0, get_pre());
}

void op_insert_index(void)
{
	slide_index(1);
	set_shelf(0, get_index());
}

void op_add(void)
{
	set_shelf(-1, (get_shelf(-1)+get_shelf(0)));
	set_shelf(0, 0);
	slide_index(-1);
}

void op_sub(void)
{
	set_shelf(-1, (get_shelf(-1)-get_shelf(0)));
	set_shelf(0, 0);
	slide_index(-1);
}

void op_mult(void)
{
	set_shelf(-1, (get_shelf(-1)*get_shelf(0)));
	set_shelf(0, 0);
	slide_index(-1);
}

void op_div(void)
{
	set_shelf(-1, (get_shelf(-1)/get_shelf(0)));
	set_shelf(0, 0);
	slide_index(-1);
}

void op_mod(void)
{
	set_shelf(-1, (get_shelf(-1)%get_shelf(0)));
	set_shelf(0, 0);
	slide_index(-1);
}

void op_not(void)
{
	set_shelf(0, !(get_shelf(0)));
}

void op_and(void)
{
	set_shelf(-1, (get_shelf(-1) && get_shelf(0)));
	set_shelf(0, 0);
	slide_index(-1);
}

void op_or(void)
{
	set_shelf(-1, (get_shelf(-1) || get_shelf(0)));
	set_shelf(0, 0);
	slide_index(-1);
}

void op_xor(void)
{
	set_shelf(-1, (get_shelf(-1) || get_shelf(0)) &&
	(get_shelf(-1) && get_shelf(0)));
	set_shelf(0, 0);
	slide_index(-1);
}

void op_lesser(void)
{
	set_shelf(-1, (get_shelf(-1) < get_shelf(0)));
	set_shelf(0, 0);
	slide_index(-1);
}

void op_greater(void)
{
	set_shelf(-1, (get_shelf(-1) > get_shelf(0)));
	set_shelf(0, 0);
	slide_index(-1);
}

void op_equals(void)
{
	set_shelf(-1, (get_shelf(-1) == get_shelf(0)));
	set_shelf(0, 0);
	slide_index(-1);
}

void op_duplicate(void)
{
	slide_index(1);
	set_shelf(0, get_shelf(-1));
}

void op_remove(void)
{
	set_shelf(0, 0);
	slide_index(1);
}
/*
 *void psop_adjust_used_width(void)
 *{
 *	if(get_shelf(-1) < 0){
 *		if((get_index() < 0) && (get_used_width() <= get_cur())) {
 *			int tmpWidth;
 *			tmpWidth = (get_cur()-1);
 *			while((get_foreign_index(tmpWidth) > -1) && (tmpWidth > 0))
 *				--tmpWidth;
 *			set_used_width(tmpWidth);
 *		}
 *	} else {
 *		
 *	}
 *}
 */

void psop_move(void)
{
	set_pre(get_cur());
	set_cur(get_shelf(-1));
	set_foreign_shelf(get_pre(), -1, 0);
	slide_foreign_index(get_pre(), -2);
}

void psop_carry(void)
{
	int i;
	int amount;
	int dest;
	amount = get_shelf(0);
	dest = get_shelf(-1);
	set_shelf(0, 0);
	set_shelf(-1, 0);
	slide_index(-2);
	for(i = 0; i < amount; ++i) {
		set_foreign_shelf(dest, (1+i), get_shelf((-(amount-1)+i)));
		slide_foreign_index(dest, 1);
	}
	for(i = 0; i < amount; ++i) {
		set_shelf(0, 0);
		slide_index(-1);
	}
	set_pre(get_cur());
	set_cur(dest);
}

void op_reverse(void)
{
	int i;
	int j;
	int temp;
	j = get_shelf(0);
	slide_index(-1);
	for(i = 0; i < (j/2); ++i) {
		temp = get_shelf(-i);
		set_shelf(-i, get_shelf((-(j-i)+1)));
		set_shelf((-(j-i)+1), temp);
	}
}

void op_start_loop(void)
{
	int loop;
	loop = 1;
	slide_tape(1);
	while((get_token() != ']') && (loop != 0)) {
		if(get_token() == '[') {
			++loop;
		} else if(get_token() == ']') {
			--loop;
			if(loop == 0)
				slide_tape(-1);
		}
		slide_tape(1);
	}
}

void op_end_loop(void)
{
	int out;
	int loop;
	out = 0;
	loop = 1;
	while(out == 0) {
		slide_tape(-1);
		if(get_step() < 0) {
			printf("\n\nError: no loop start");
			break;
		}
		if(get_token() == ']') {
			++loop;
		} else if(get_token() == '[') {
			--loop;
			if(loop == 0)
				out = 1;
		}
	}
}

void psop_skip_ternary(void)
{
	int out;
	int tern;
	out = 0;
	tern = 1;
	set_shelf(0, 0);
	slide_index(-1);
	while(out == 0) {
		slide_tape(1);
		if(get_token() == '{') {
			++tern;
		} else if(get_token() == '}') {
			--tern;
			if(tern == 0)
				out = 1;
		}
	}
}


void psop_right_ternary(void)
{
	int out;
	int tern;
	out = 0;
	tern = 0;
	set_shelf(0, 0);
	slide_index(-1);
	while(out == 0) {
		slide_tape(1);
		if(get_token() == '{') {
			++tern;
		} else if(get_token() == '}') {
			--tern;
		} else if(get_token() == '_') {
			if(tern == 0)
				out = 1;
		}
	}
}

void op_switch_ternary(void)
{
	int out;
	int tern;
	out = 0;
	tern = 1;
	while(out == 0) {
		slide_tape(1);
		if(get_token() == '{') {
			++tern;
		} else if(get_token() == '}') {
			--tern;
			if(tern == 0)
				out = 1;
		}
	}
}

void op_start_string(void)
{
	int out;
	out = 0;
	while(out == 0) {
		slide_tape(1);
		if(get_token() == ')') {
			out = 1;
		} else {
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			slide_index(1);
			set_shelf(0, get_token());
		}
	}
}

void op_print_num(void)
{
	printf( "%i", get_shelf(0));
	set_shelf(0, 0);
	slide_index(-1);
}

void op_print_ascii(void)
{
	printf( "%c", (char)get_shelf(0));
	set_shelf(0, 0);
	slide_index(-1);
}

void op_ask_ascii(void)
{
	char chara;
	slide_index(1);
	scanf("%c", &chara);
	set_shelf(0, (int)chara);
}

void op_random(void)
{
	int div;
	int temp;
	time_t secs;
	div = RAND_MAX/get_shelf(0);
	srand((unsigned)time(&secs));
	do {
		temp = rand()/div;
	} while(temp > get_shelf(0));
	set_shelf(0, temp);
}
