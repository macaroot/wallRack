#include "main.h"
#include "operators.h"

void op_insert_zero(struct Wall *wall, struct Rack **racks)
{
	++racks[wall->cur]->ind;
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0x0;
}

void op_insert_one(struct Wall *wall, struct Rack **racks)
{
	++racks[wall->cur]->ind;
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0x1;
}

void op_insert_two(struct Wall *wall, struct Rack **racks)
{
	++racks[wall->cur]->ind;
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0x2;
}

void op_insert_three(struct Wall *wall, struct Rack **racks)
{
	++racks[wall->cur]->ind;
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0x3;
}

void op_insert_four(struct Wall *wall, struct Rack **racks)
{
	++racks[wall->cur]->ind;
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0x4;
}

void op_insert_five(struct Wall *wall, struct Rack **racks)
{
	++racks[wall->cur]->ind;
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0x5;
}

void op_insert_six(struct Wall *wall, struct Rack **racks)
{
	++racks[wall->cur]->ind;
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0x6;
}

void op_insert_seven(struct Wall *wall, struct Rack **racks)
{
	++racks[wall->cur]->ind;
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0x7;
}

void op_insert_eight(struct Wall *wall, struct Rack **racks)
{
	++racks[wall->cur]->ind;
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0x8;
}

void op_insert_nine(struct Wall *wall, struct Rack **racks)
{
	++racks[wall->cur]->ind;
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0x9;
}

void op_insert_a(struct Wall *wall, struct Rack **racks)
{
	++racks[wall->cur]->ind;
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0xa;
}

void op_insert_b(struct Wall *wall, struct Rack **racks)
{
	++racks[wall->cur]->ind;
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0xb;
}

void op_insert_c(struct Wall *wall, struct Rack **racks)
{
	++racks[wall->cur]->ind;
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0xc;
}

void op_insert_d(struct Wall *wall, struct Rack **racks)
{
	++racks[wall->cur]->ind;
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0xd;
}

void op_insert_e(struct Wall *wall, struct Rack **racks)
{
	++racks[wall->cur]->ind;
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0xe;
}

void op_insert_f(struct Wall *wall, struct Rack **racks)
{
	++racks[wall->cur]->ind;
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0xf;
}

void op_insert_cur(struct Wall *wall, struct Rack **racks)
{
	++racks[wall->cur]->ind;
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = wall->cur;
}

void op_insert_pre(struct Wall *wall, struct Rack **racks)
{
	++racks[wall->cur]->ind;
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = wall->pre;
}

void op_insert_ind(struct Wall *wall, struct Rack **racks)
{
	++racks[wall->cur]->ind;
	racks[wall->cur]->shelf[racks[wall->cur]->ind] =
	racks[wall->cur]->ind;
}

void op_add(struct Wall *wall, struct Rack **racks)
{
	racks[wall->cur]->shelf[racks[wall->cur]->ind-1] +=
	racks[wall->cur]->shelf[racks[wall->cur]->ind];
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0;
	--racks[wall->cur]->ind;
}

void op_sub(struct Wall *wall, struct Rack **racks)
{
	racks[wall->cur]->shelf[racks[wall->cur]->ind-1] -=
	racks[wall->cur]->shelf[racks[wall->cur]->ind];
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0;
	--racks[wall->cur]->ind;
}

void op_mult(struct Wall *wall, struct Rack **racks)
{
	racks[wall->cur]->shelf[racks[wall->cur]->ind-1] *=
	racks[wall->cur]->shelf[racks[wall->cur]->ind];
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0;
	--racks[wall->cur]->ind;
}

void op_div(struct Wall *wall, struct Rack **racks)
{
	racks[wall->cur]->shelf[racks[wall->cur]->ind-1] /=
	racks[wall->cur]->shelf[racks[wall->cur]->ind];
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0;
	--racks[wall->cur]->ind;
}

void op_mod(struct Wall *wall, struct Rack **racks)
{
	racks[wall->cur]->shelf[racks[wall->cur]->ind-1] %=
	racks[wall->cur]->shelf[racks[wall->cur]->ind];
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0;
	--racks[wall->cur]->ind;
}

void op_not(struct Wall *wall, struct Rack **racks)
{
	racks[wall->cur]->shelf[racks[wall->cur]->ind] =
	!(racks[wall->cur]->shelf[racks[wall->cur]->ind]);
}

void op_and(struct Wall *wall, struct Rack **racks)
{
	racks[wall->cur]->shelf[racks[wall->cur]->ind-1] =
	(racks[wall->cur]->shelf[racks[wall->cur]->ind-1] &&
	racks[wall->cur]->shelf[racks[wall->cur]->ind]);
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0;
	--racks[wall->cur]->ind;
}

void op_or(struct Wall *wall, struct Rack **racks)
{
	racks[wall->cur]->shelf[racks[wall->cur]->ind-1] =
	(racks[wall->cur]->shelf[racks[wall->cur]->ind-1] ||
	racks[wall->cur]->shelf[racks[wall->cur]->ind]);
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0;
	--racks[wall->cur]->ind;
}

void op_xor(struct Wall *wall, struct Rack **racks)
{
	racks[wall->cur]->shelf[racks[wall->cur]->ind-1] =
	((racks[wall->cur]->shelf[racks[wall->cur]->ind-1] ||
	racks[wall->cur]->shelf[racks[wall->cur]->ind]) &&
	(racks[wall->cur]->shelf[racks[wall->cur]->ind-1] &&
	racks[wall->cur]->shelf[racks[wall->cur]->ind]));
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0;
	--racks[wall->cur]->ind;
}

void op_lesser(struct Wall *wall, struct Rack **racks)
{
	racks[wall->cur]->shelf[racks[wall->cur]->ind-1] =
	(racks[wall->cur]->shelf[racks[wall->cur]->ind-1] <
	racks[wall->cur]->shelf[racks[wall->cur]->ind]);
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0;
	--racks[wall->cur]->ind;
}

void op_greater(struct Wall *wall, struct Rack **racks)
{
	racks[wall->cur]->shelf[racks[wall->cur]->ind-1] =
	(racks[wall->cur]->shelf[racks[wall->cur]->ind-1] >
	racks[wall->cur]->shelf[racks[wall->cur]->ind]);
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0;
	--racks[wall->cur]->ind;
}

void op_equals(struct Wall *wall, struct Rack **racks)
{
	racks[wall->cur]->shelf[racks[wall->cur]->ind-1] =
	(racks[wall->cur]->shelf[racks[wall->cur]->ind-1] ==
	racks[wall->cur]->shelf[racks[wall->cur]->ind]);
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0;
	--racks[wall->cur]->ind;
}

void op_duplicate(struct Wall *wall, struct Rack **racks)
{
	racks[wall->cur]->shelf[racks[wall->cur]->ind+1] =
	racks[wall->cur]->shelf[racks[wall->cur]->ind];
	++racks[wall->cur]->ind;
}

void op_remove(struct Wall *wall, struct Rack **racks)
{
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0;
	--racks[wall->cur]->ind;
}

void op_move(struct Wall *wall, struct Rack **racks)
{
	if(racks[wall->cur]->shelf[racks[wall->cur]->ind] == 0) {
		wall->pre = wall->cur;
		wall->cur = racks[wall->cur]->shelf[racks[wall->cur]->ind-1];
		racks[wall->pre]->shelf[racks[wall->pre]->ind-1] = 0;
		racks[wall->pre]->ind -= 2;
	}
	else {
		int i;
		int amount;
		int dest;
		amount = racks[wall->cur]->shelf[racks[wall->cur]->ind];
		dest = racks[wall->cur]->shelf[racks[wall->cur]->ind-1];
		racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0;
		racks[wall->cur]->shelf[racks[wall->cur]->ind-1] = 0;
		racks[wall->cur]->ind -= 2;
		for(i = 0; i < amount; ++i) {
			racks[dest]->shelf[racks[dest]->ind+(1+i)] =
			racks[wall->cur]->shelf[racks[wall->cur]->ind-(amount-1)+i];
			++racks[wall->cur]->ind;
		}
		for( i = 0; i < amount; ++i ) {
			racks[wall->cur]->shelf[racks[wall->cur]->ind-1] = 0;
			--racks[wall->cur]->ind;
		}
		wall->pre = wall->cur;
		wall->cur = dest;
	}
}

void op_reverse(struct Wall *wall, struct Rack **racks)
{
	int i;
	int j;
	int temp;
	j = racks[wall->cur]->shelf[racks[wall->cur]->ind];
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0;
	--racks[wall->cur]->ind;
	for(i = 0; i < (j/2); ++i) {
		temp = racks[wall->cur]->shelf[racks[wall->cur]->ind-i];
		racks[wall->cur]->shelf[racks[wall->cur]->ind+i] =
		racks[wall->cur]->shelf[racks[wall->cur]->ind-(j-i)+1];
		racks[wall->cur]->shelf[racks[wall->cur]->ind-(j-i)+1] = temp;
	}
}

void op_start_loop(struct Tape *tape, struct Wall *wall, struct Rack **racks)
{
	if((racks[wall->cur]->shelf[racks[wall->cur]->ind] == 0) ||
	(racks[wall->cur]->ind < 0)) {
		int loop;
		loop = 0;
		++tape->step;
		while((tape->tok[tape->step] != ']') && (loop != 0)) {
			if(tape->tok[tape->step] == '[') {
				++loop;
			}
			else if(tape->tok[tape->step] == ']') {
				--loop;
				if( loop == 0 )
					--tape->step;
			}
			++tape->step;
		}
	}
}

void op_end_loop(struct Tape *tape, struct Wall *wall, struct Rack **racks)
{
	if(racks[wall->cur]->ind < 0) {
	}
	else if(racks[wall->cur]->shelf[racks[wall->cur]->ind] == 0 ) {
		--racks[wall->cur]->ind;
	}
	else {
		int out;
		int loop;
		out = 0;
		loop = 1;
		while(out == 0) {
			--tape->step;
			if(racks[wall->cur]->ind < 0 ) {
				out = 1;
			}
			else {
				if(tape->tok[tape->step] == ']') {
					++loop;
				}
				else if(tape->tok[tape->step] == '[') {
					--loop;
					if(loop == 0)
						out = 1;
				}
			}
		}
	}
}

void op_start_ternary(struct Tape *tape, struct Wall *wall, struct Rack **racks)
{
	if(racks[wall->cur]->shelf[racks[wall->cur]->ind] == 0) {
		--racks[wall->cur]->ind;
	}
	else if(racks[wall->cur]->shelf[racks[wall->cur]->ind] < 0) {
		int out;
		int tern;
		out = 0;
		tern = 1;
		racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0;
		--racks[wall->cur]->ind;
		while(out == 0) {
			++tape->step;
			if(tape->tok[tape->step] == '{') {
				++tern;
			}
			else if(tape->tok[tape->step] == '}') {
				--tern;
				if(tern == 0)
					out = 1;
			}
		}
	}
	else {
		int out;
		int tern;
		out = 0;
		tern = 0;
		racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0;
		--racks[wall->cur]->ind;
		while(out == 0) {
			++tape->step;
			if(tape->tok[tape->step] == '{') {
				++tern;
			}
			else if(tape->tok[tape->step] == '}') {
				--tern;
			}
			else if(tape->tok[tape->step] == '_') {
				if(tern == 0)
					out = 1;
			}
		}
	}
}

void op_switch_ternary(struct Tape *tape, struct Wall *wall, struct Rack **racks)
{
	int out;
	int tern;
	tern = 1;
	while(out == 0) {
		++tape->step;
		if(tape->tok[tape->step] == '{') {
			++tern;
		}
		else if(tape->tok[tape->step] == '}') {
			--tern;
			if( tern == 0 )
				out = 1;
		}
	}
}

void op_start_string(struct Tape *tape, struct Wall *wall, struct Rack **racks)
{
	int out;
	out = 0;
	while(out == 0) {
		++tape->step;
		if( tape->tok[tape->step] == ')' ) {
			out = 1;
		}
		else {
			++racks[wall->cur]->ind;
			racks[wall->cur]->shelf[racks[wall->cur]->ind] = tape->tok[tape->step];
		}
	}
}

void op_print_num(struct Wall *wall, struct Rack **racks)
{
	char chara;
	++racks[wall->cur]->ind;
	scanf("%c", &chara);
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = (int)chara;
}

void op_print_ascii(struct Wall *wall, struct Rack **racks)
{
	printf( "%c", (char)racks[wall->cur]->shelf[racks[wall->cur]->ind]);
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0;
	--racks[wall->cur]->ind;
}

void op_ask_ascii(struct Wall *wall, struct Rack **racks)
{
	printf( "%i", (char)racks[wall->cur]->shelf[racks[wall->cur]->ind]);
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = 0;
	--racks[wall->cur]->ind;
}

void op_random(struct Wall *wall, struct Rack **racks)
{
	int div;
	int temp;
	time_t secs;
	div = RAND_MAX/(racks[wall->cur]->shelf[racks[wall->cur]->ind]+1);
	srand((unsigned)time(&secs));
	do {
		temp = rand() / div;
	} while(temp > racks[wall->cur]->shelf[racks[wall->cur]->ind]);
	racks[wall->cur]->shelf[racks[wall->cur]->ind] = temp;
}
