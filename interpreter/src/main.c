/* wallRack interpreter in C
 * wallRack is a simple language that consists of an array of 'stacks', which
 * are manipulated tediously with 47 single character operators.
 *
 * You can use a three digit number as an option, and it will show a snapshot
 * (with racks cut to 16 height) of the internal values.
 * Usage: ./wallRack prog ###
 *
 * Structure:
 * wall		- An array which you traverse with absolute notation, currently
 * 		16 indexes.
 * rack		- A stack for each index of wall. Racks start at '-1', so first
 * 		operation on a rack must be one that adds a shelf.
 * shelf	- Racks currently consist of 128 shelfs, which hold decimal
 * 		values.
 *
 * .    .    .    .    .    .    .    .    .    .    .     .     ...
 * .    .    .    .    .    .    .    .    .    .    .     .     ...
 * .    .    .    .    .    .    .    .    .    .    .     .     ...
 * r[9] r[9] r[9] r[9] r[9] r[9] r[9] r[9] r[9] r[9] r[9]  r[9]  ...
 * r[8] r[8] r[8] r[8] r[8] r[8] r[8] r[8] r[8] r[8] r[8]  r[8]  ...
 * r[7] r[7] r[7] r[7] r[7] r[7] r[7] r[7] r[7] r[7] r[7]  r[7]  ...
 * r[6] r[6] r[6] r[6] r[6] r[6] r[6] r[6] r[6] r[6] r[6]  r[6]  ...
 * r[5] r[5] r[5] r[5] r[5] r[5] r[5] r[5] r[5] r[5] r[5]  r[5]  ...
 * r[4] r[4] r[4] r[4] r[4] r[4] r[4] r[4] r[4] r[4] r[4]  r[4]  ...
 * r[3] r[3] r[3] r[3] r[3] r[3] r[3] r[3] r[3] r[3] r[3]  r[3]  ...
 * r[2] r[2] r[2] r[2] r[2] r[2] r[2] r[2] r[2] r[2] r[2]  r[2]  ...
 * r[1] r[1] r[1] r[1] r[1] r[1] r[1] r[1] r[1] r[1] r[1]  r[1]  ...
 * r[0] r[0] r[0] r[0] r[0] r[0] r[0] r[0] r[0] r[0] r[0]  r[0]  ...
 * w[0] w[1] w[2] w[3] w[4] w[5] w[6] w[7] w[8] w[9] w[10] w[11] ...
 *
 *
 * Operators:
 * ;		Linecomment.
 *
 * 0 1 2 3 4 5	Values held by shelves are decimal, but hexadecimals can
 * 6 7 8 9 a b	be used to input values, to ease the need for multidigit
 * c d e f	instructions. Increments rack.
 * 	:: r[i] = O; ++i
 *
 * # ~ @	Get current index of wall / previous index of wall / current
 * 		index of rack. Increments rack.
 * 	:: r[i] = O; ++i
 *
 * + - * / %	Basic mathematical operators, which combine the two shelves.
 * 		Decrements rack.
 * 	:: r[i-1] = r[i] O r[i-1]; r[i] = 0; --i
 *
 * !		Logical not, returns boolean.
 * 	:: r[i] = O r[i]
 *
 * & | ^	Logical operators for two shelves: and / or / xor. Returns
 * 		boolean. Decrements rack.
 * 	:: r[i-1] = r[i] O r[i-1]; r[i] = 0; --i
 *
 * = < >	Comparison of two shelves: equals / lesser / greater /
 * 		returns boolean. Decrements rack.
 * 	:: r[i-1] = r[i] O r[i-1]; r[i] = 0; --i
 *
 * :		Duplicate a shelf. Increments rack.
 * 	:: r[i+1] = r[i]; ++i
 *
 * .		Clear a shelf. Decrements rack.
 * 	:: r[i] = 0; --i
 *
 * $		Move on the wall and optionally carry values from multiple
 * 		shelves. If first shelf is 0, nothing is carried. Decrements
 * 		the two options used by the operator from the rack, and also
 * 		decrements the amount of shelves you took. Increments the rack
 * 		you go to by the amount of shelves you took.
 * 	:: r[i] : How many items down the rack you will carry;
 * 	:: r[i-1] : To which rack you go to;
 *
 * \		Reverses the order of shelves, the amount is specified with
 * 		an option. Decrements rack.
 * 	:: r[i] : How many shelves do you reorder;
 *
 * [ ]		Loop which starts if shelf is not 0, and stops if shelf is
 * 		0 when end bracket is reached. If below rack, start and end are
 * 		entirely ignored. Decrements rack when exciting loop.
 * 	:: at [ if r[i] == 0 or r[-1], go to corresponding ]
 * 	:: at ] if r[i] == 0, --i
 * 	:: at ] if r[i] != 0, go back to corresponding [
 * 	:: at ] if r[-1], do nothing
 *
 * { _ }	Ternary switch. If shelf is 0 the left side of _ operator is
 * 		executed, right side will be skipped, and vice versa if shelf
 * 		not 0. Entering decrements rack. If below rack, both sides are
 * 		ignored. This behavior makes it a pseudo quarternary switch.
 * 	:: at { if r[i] == 0; --i
 * 	:: at { if r[i] != 0, r[i] = 0, go to corresponding _; --i
 * 	:: at { if r[-i], go to corresponding }
 * 	:: at _ go to corresponding };
 *
 * ( )		Stringform. Puts ASCII into shelves sequentially.
 *
 * "		Print shelf as ASCII. Decrements rack.
 * 	:: OUTPUT = r[i]; r[i] = 0; --i
 *
 * '		Ask for ASCII input. Increments rack.
 * 	:: r[i] = INPUT; ++i
 *
 * `		Print decimal value. Decrements rack.
 * 	:: OUTPUT = r[i]; r[i] = 0; --i
 *
 * ?		Generates random number from 0 to option.
 * 	:: r[i] = rand( 0 - r[i] );
 */
#include "main.h"
#include "operators.h"

/* Inits */
void init_state(struct State *state)
{
	state->startHeight = 0x8;
	state->startWidth = 0x4;
	state->startLength = 0x40;
	state->lapse = 0;
	state->error = none;
}

void init_tape(struct State *state, struct Tape *tape)
{
	tape->raw = malloc(state->startLength * sizeof(char));
	tape->tok = malloc(state->startLength * sizeof(char));
	tape->step = 0;
}

void init_wall(struct State *state, struct Wall *wall)
{
	wall->cur = 0;
	wall->pre = 0;
	wall->width = state->startWidth;
}

void init_racks(struct State *state, struct Wall *wall, struct Rack **racks)
{
	int i;
	*racks = malloc(state->startWidth * sizeof(struct Rack));
	for(i = 0; i < 0x4; ++i) {
		(*racks)[i].shelf = malloc(state->startHeight * sizeof(int));
		(*racks)[i].ind = 0;
		(*racks)[i].height = state->startHeight;
	}
}

void init_wall_rack(struct State *state, struct Tape *tape, struct Wall *wall,
struct Rack **racks)
{
	init_state(state);
	init_tape(state, tape);
	init_wall(state, wall);
	init_racks(state, wall, racks);
}

/* Wipes */
void wipe_raw(struct Tape *tape)
{
	free(tape->raw);
}

void wipe_tokens(struct Tape *tape)
{
	free(tape->tok);
}

void wipe_racks(struct Wall *wall, struct Rack **racks)
{
	int i;
	for(i = 0; i < wall->width; ++i) {
		free((*racks)[i].shelf);
	}
	free(*racks);
}

void wipe_rest(struct Tape *tape, struct Wall *wall, struct Rack **racks)
{
	wipe_tokens(tape);
	wipe_racks(wall, racks);
}

/* File handling */
void fill_raw(FILE *file, struct Tape *tape)
{
	int chara;
	int i;
	i = 0;
	while((chara = fgetc(file)) != EOF) {
		tape->raw[i] = chara;
		++i;
		if(i >= sizeof(tape->raw))
			tape->raw = (char*)realloc(tape->raw,
			0x2 * sizeof(tape->raw));
	}
	tape->raw[i] = '\0';
	fclose(file);
}

void fill_tokens(struct Tape *tape)
{
	int i;
	int j;
	int leap;
	int dev;
	i = 0;
	j = 0;
	while(tape->raw[i] != '\0') {
		leap = 1;
		dev = 1;
		if(tape->raw[i] == ';') {
			while((tape->raw[i+dev] != '\n') &&
			(tape->raw[i+dev] != '\0')) {
				++leap;
				++dev;
			}
			++leap;
			dev = 1;
		}
		else if(tape->raw[i] == '(') {
			tape->tok[j] = '(';
			++j;
			if(j >= sizeof(tape->tok))
				tape->tok = (char*)realloc(tape->tok,
				0x2 * sizeof(tape->tok));
			while(tape->raw[i+dev] != ')') {
				if(tape->raw[i+dev]== '\0') {
					printf( "\nError: String end was not found while tokenizing file.\n" );
				}
				else {
					tape->tok[j] = tape->raw[i + dev];
					++j;
					if(j >= sizeof(tape->tok))
						tape->tok = (char*)realloc(
						tape->tok, 0x2 * sizeof(tape->tok));
					++leap;
					++dev;
				}
			}
			tape->tok[j] = ')';
			++j;
			if(j >= sizeof(tape->tok))
				tape->tok = (char*) realloc(tape->tok, 0x2 * sizeof(tape->tok));
			++leap;
			dev = 1;
		}
		else if(tape->raw[i] == '0' || tape->raw[i] == '1' ||
		tape->raw[i] == '2' || tape->raw[i] == '3' ||
		tape->raw[i] == '4' || tape->raw[i] == '5' ||
		tape->raw[i] == '6' || tape->raw[i] == '7' ||
		tape->raw[i] == '8' || tape->raw[i] == '9' ||
		tape->raw[i] == 'a' || tape->raw[i] == 'b' ||
		tape->raw[i] == 'c' || tape->raw[i] == 'd' ||
		tape->raw[i] == 'e' || tape->raw[i] == 'f' ||
		tape->raw[i] == '#' || tape->raw[i] == '~' ||
		tape->raw[i] == '@' || tape->raw[i] == '+' ||
		tape->raw[i] == '-' || tape->raw[i] == '*' ||
		tape->raw[i] == '/' || tape->raw[i] == '%' ||
		tape->raw[i] == '!' || tape->raw[i] == '&' ||
		tape->raw[i] == '|' || tape->raw[i] == '^' ||
		tape->raw[i] == '<' || tape->raw[i] == '>' ||
		tape->raw[i] == '>' || tape->raw[i] == ':' ||
		tape->raw[i] == '.' || tape->raw[i] == '$' ||
		tape->raw[i] == '\\' || tape->raw[i] == '[' ||
		tape->raw[i] == ']' || tape->raw[i] == '{' ||
		tape->raw[i] == '}' || tape->raw[i] == '_' ||
		tape->raw[i] == '\'' || tape->raw[i] == '\"' ||
		tape->raw[i] == '`' || tape->raw[i] == '\?') {
		tape->tok[j] = tape->raw[i];
			++j;
		}
		i += leap;
	}
	if(j == 0) {
		printf("\nError: No recognizable characters.\n");
	}
	else {
		if((j+1) >= sizeof(tape->tok))
			tape->tok = (char*) realloc(tape->raw, 0x2 * sizeof(tape->tok));
		tape->tok[j+1] = '\0';
	}
}

void parse_file(FILE *file, struct Tape *tape)
{
	fill_raw(file, tape);
	fill_tokens(tape);
}

/* Checks */
int top_check( struct Wall *wall, struct Rack **racks)
{
	return((racks[wall->cur]->height-2) - racks[wall->cur]->ind);
}

int bottom_check( struct Wall *wall, struct Rack **racks)
{
	return(racks[wall->cur]->ind - 1);
}

int edge_check( struct Wall *wall, struct Rack **racks)
{
	return(!(((wall->width-1) <
	racks[wall->cur]->shelf[racks[wall->cur]->ind]) ||
	(racks[wall->cur]->shelf[racks[wall->cur]->ind] < 0)));
}

/* Error messages */
void interp_error(struct State *state, struct Tape *tape, struct Wall *wall,
struct Rack **racks)
{
	switch(state->error) {
	case(none) :
		break;
	case(top) :
		printf("\n\nError: Rack top exceeded at rack %i, \
during token #%i: '%c'. Lapse %i\n", wall->cur, tape->step,
tape->tok[tape->step], state->lapse);
		break;
	case(bottom) :
		printf("\n\nError: Rack bottom exceeded at rack %i, \
during token #%i: '%c'. Lapse %i\n", wall->cur, tape->step,
tape->tok[tape->step], state->lapse);
		break;
	case(edge) :
		printf("\n\nError: Nonexistent rack was reached at rack %i, \
during token #%i: '%c'. Lapse %i\n", wall->cur, tape->step,
tape->tok[tape->step], state->lapse);
		break;
	}
}

/* Interpreting tokens */
void run(struct State *state, struct Tape *tape, struct Wall *wall,
struct Rack **racks)
{
	while((tape->tok[tape->step] != '\0')) {
		switch(tape->tok[tape->step]) {
		case '0' :
			if(!top_check(wall, racks)) {
				state->error = top;
				goto fail;
			}
			op_insert_zero(wall, racks);
			break;
		case '1' :
			if(!top_check(wall, racks)) {
				state->error = top;
				goto fail;
			}
			op_insert_one(wall, racks);
			break;
		case '2' :
			if(!top_check(wall, racks)) {
				state->error = top;
				goto fail;
			}
			op_insert_two(wall, racks);
			break;
		case '3' :
			if(!top_check(wall, racks)) {
				state->error = top;
				goto fail;
			}
			op_insert_three(wall, racks);
			break;
		case '4' :
			if(!top_check(wall, racks)) {
				state->error = top;
				goto fail;
			}
			op_insert_four(wall, racks);
			break;
		case '5' :
			if(!top_check(wall, racks)) {
				state->error = top;
				goto fail;
			}
			op_insert_five(wall, racks);
			break;
		case '6' :
			if(!top_check(wall, racks)) {
				state->error = top;
				goto fail;
			}
			op_insert_six(wall, racks);
			break;
		case '7' :
			if(!top_check(wall, racks)) {
				state->error = top;
				goto fail;
			}
			op_insert_seven(wall, racks);
			break;
		case '8' :
			if(!top_check(wall, racks)) {
				state->error = top;
				goto fail;
			}
			op_insert_eight(wall, racks);
			break;
		case '9' :
			if(!top_check(wall, racks)) {
				state->error = top;
				goto fail;
			}
			op_insert_nine(wall, racks);
			break;
		case 'a' :
			if(!top_check(wall, racks)) {
				state->error = top;
				goto fail;
			}
			op_insert_a(wall, racks);
			break;
		case 'b' :
			if(!top_check(wall, racks)) {
				state->error = top;
				goto fail;
			}
			op_insert_b(wall, racks);
			break;
		case 'c' :
			if(!top_check(wall, racks)) {
				state->error = top;
				goto fail;
			}
			op_insert_c(wall, racks);
			break;
		case 'd' :
			if(!top_check(wall, racks)) {
				state->error = top;
				goto fail;
			}
			op_insert_d(wall, racks);
			break;
		case 'e' :
			if(!top_check(wall, racks)) {
				state->error = top;
				goto fail;
			}
			op_insert_e(wall, racks);
			break;
		case 'f' :
			if(!top_check(wall, racks)) {
				state->error = top;
				goto fail;
			}
			op_insert_f(wall, racks);
			break;
		case '#' :
			if(!top_check(wall, racks)) {
				state->error = top;
				goto fail;
			}
			op_insert_cur(wall, racks);
			break;
		case '~' :
			if(!top_check(wall, racks)) {
				state->error = top;
				goto fail;
			}
			op_insert_pre(wall, racks);
			break;
		case '@' :
			if(!top_check(wall, racks)) {
				state->error = top;
				goto fail;
			}
			op_insert_ind(wall, racks);
			break;
		case '+' :
			if(!bottom_check(wall, racks)) {
				state->error = bottom;
				goto fail;
			}
			op_add(wall, racks);
			break;
		case '-' :
			if(!bottom_check(wall, racks)) {
				state->error = bottom;
				goto fail;
			}
			op_sub(wall, racks);
			break;
		case '*' :
			if(!bottom_check(wall, racks)) {
				state->error = bottom;
				goto fail;
			}
			op_mult(wall, racks);
			break;
		case '/' :
			if(!bottom_check(wall, racks)) {
				state->error = bottom;
				goto fail;
			}
			op_div(wall, racks);
			break;
		case '%' :
			if(!bottom_check(wall, racks)) {
				state->error = bottom;
				goto fail;
			}
			op_mod(wall, racks);
			break;
		case '!' :
			if(!(bottom_check(wall, racks)+1)) {
				state->error = bottom;
				goto fail;
			}
			op_not(wall, racks);
			break;
		case '&' :
			if(!bottom_check(wall, racks)) {
				state->error = bottom;
				goto fail;
			}
			op_and(wall, racks);
			break;
		case '|' :
			if(!bottom_check(wall, racks)) {
				state->error = bottom;
				goto fail;
			}
			op_or(wall, racks);
			break;
		case '^' :
			if(!bottom_check(wall, racks)) {
				state->error = bottom;
				goto fail;
			}
			op_xor(wall, racks);
			break;
		case '<' :
			if(!bottom_check(wall, racks)) {
				state->error = bottom;
				goto fail;
			}
			op_lesser(wall, racks);
			break;
		case '>' :
			if(!bottom_check(wall, racks)) {
				state->error = bottom;
				goto fail;
			}
			op_greater(wall, racks);
			break;
		case '=' :
			if(!bottom_check(wall, racks)) {
				state->error = bottom;
				goto fail;
			}
			op_equals(wall, racks);
			break;
		case ':' :
			if(!bottom_check(wall, racks)) {
				state->error = bottom;
				goto fail;
			}
			if(!top_check(wall, racks)) {
				state->error = top;
				goto fail;
			}
			op_duplicate(wall, racks);
			break;
		case '.' :
			if(!bottom_check(wall, racks)) {
				state->error = bottom;
				goto fail;
			}
			op_remove(wall, racks);
			break;
		case '$' :
			if(!edge_check(wall, racks)) {
				state->error = edge;
				goto fail;
			}
			op_move(wall, racks);
			break;
		case '\\' :
			op_reverse(wall, racks);
			break;
		case '[' :
			op_start_loop(tape, wall, racks);
			break;
		case ']' :
			op_end_loop(tape, wall, racks);
			break;
		case '{' :
			op_start_ternary(tape, wall, racks);
			break;
		case '}' :
			break;
		case '_' :
			op_switch_ternary(tape, wall, racks);
			break;
		case '(' :
			op_start_string(tape, wall, racks);
			break;
		case ')' :
			if(1) {
				/*error*/
			}
			break;
		case '\'' :
			op_print_num(wall, racks);
			break;
		case '\"' :
			op_print_ascii(wall, racks);
			break;
		case '`' :
			op_ask_ascii(wall, racks);
			break;
		case '\?' :
			op_random(wall, racks);
			break;
		}
		++tape->step;
	}
	fail: if(state->error != none)
		interp_error(state, tape, wall, racks);
}

/* main */
int main(int argc, char* argv[])
{
	FILE* file;
	struct State state;
	struct Tape tape;
	struct Rack *racks;
	struct Wall wall;
	if(argc > 2) {
		printf("\n\nError: Provide program file.\nUsage: %s program 054\n", argv[0]);
		goto fail;
	}
	init_wall_rack(&state, &tape, &wall, &racks);
	file = fopen(argv[1], "r");
	if(!file) {
		printf("\n\nError: Could not open file\n");
		goto fail;
	}
	parse_file(file, &tape);
	wipe_raw(&tape);
	run(&state, &tape, &wall, &racks);
	wipe_rest(&tape, &wall, &racks);
	printf("\n\nSuccessful exit.\n");
	return(0);
	fail:
	return(1);
}
