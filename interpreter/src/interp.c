#include <stdio.h>
#include "interp.h"
#include "data.h"
#include "memory.h"
#include "checks.h"
#include "operators.h"
#include "display.h"

/* Interpreting tokens */
int interpret(void)
{
	while(get_token() != '\0') {
		switch(get_token()) {
		case '1' :
			if(height_check(get_index(), get_height()))
				grow_rack();
			op_insert_num(0x1);
			break;
		case '2' :
			if(height_check(get_index(), get_height()))
				grow_rack();
			op_insert_num(0x2);
			break;
		case '3' :
			if(height_check(get_index(), get_height()))
				grow_rack();
			op_insert_num(0x3);
			break;
		case '4' :
			if(height_check(get_index(), get_height()))
				grow_rack();
			op_insert_num(0x4);
			break;
		case '5' :
			if(height_check(get_index(), get_height()))
				grow_rack();
			op_insert_num(0x5);
			break;
		case '6' :
			if(height_check(get_index(), get_height()))
				grow_rack();
			op_insert_num(0x6);
			break;
		case '7' :
			if(height_check(get_index(), get_height()))
				grow_rack();
			op_insert_num(0x7);
			break;
		case '8' :
			if(height_check(get_index(), get_height()))
				grow_rack();
			op_insert_num(0x8);
			break;
		case '9' :
			if(height_check(get_index(), get_height()))
				grow_rack();
			op_insert_num(0x9);
			break;
		case 'a' :
			if(height_check(get_index(), get_height()))
				grow_rack();
			op_insert_num(0xa);
			break;
		case 'b' :
			if(height_check(get_index(), get_height()))
				grow_rack();
			op_insert_num(0xb);
			break;
		case 'c' :
			if(height_check(get_index(), get_height()))
				grow_rack();
			op_insert_num(0xc);
			break;
		case 'd' :
			if(height_check(get_index(), get_height()))
				grow_rack();
			op_insert_num(0xd);
			break;
		case 'e' :
			if(height_check(get_index(), get_height()))
				grow_rack();
			op_insert_num(0xe);
			break;
		case 'f' :
			if(height_check(get_index(), get_height()))
				grow_rack();
			op_insert_num(0xf);
			break;
		case '+' :
			if(under_lim_check(get_index(), 1)) {
				printf("\n\n+error\n");
				goto fail;
			}
			op_add();
			break;
		case '-' :
			if(under_lim_check(get_index(), 1)) {
				printf("\n\n-error\n");
				goto fail;
			}
			op_sub();
			break;
		case '*' :
			if(under_lim_check(get_index(), 1)) {
				printf("\n\n*error\n");
				goto fail;
			}
			op_mult();
			break;
		case '/' :
			if(under_lim_check(get_index(), 1)) {
				printf("\n\n/error\n");
				goto fail;
			}
			op_div();
			break;
		case '%' :
			if(under_lim_check(get_index(), 1)) {
				printf("\n\n%%error\n");
				goto fail;
			}
			op_mod();
			break;
		case '!' :
			if(under_lim_check(get_index(), 0)) {
				printf("\n\n!error");
				goto fail;
			}
			op_not();
			break;
		case '&' :
			if(under_lim_check(get_index(), 1)) {
				printf("\n\n&error");
				goto fail;
			}
			op_and();
			break;
		case '|' :
			if(under_lim_check(get_index(), 1)) {
				printf("\n\n|error");
				goto fail;
			}
			op_or();
			break;
		case '^' :
			if(under_lim_check(get_index(), 1)) {
				printf("\n\n^error");
				goto fail;
			}
			op_xor();
			break;
		case '<' :
			if(under_lim_check(get_index(), 1)) {
				printf("\n\n<error");
				goto fail;
			}
			op_lesser();
			break;
		case '>' :
			if(under_lim_check(get_index(), 1)) {
				printf("\n\n>error");
				goto fail;
			}
			op_greater();
			break;
		case '=' :
			if(under_lim_check(get_index(), 1)) {
				printf("\n\n=error");
				goto fail;
			}
			op_equals();
			break;
		case ':' :
			if(height_check(get_index(), get_height()))
				grow_rack();
			op_duplicate();
			break;
		case '.' :
			if(under_lim_check(get_index(), 0)) {
				printf("\n\n=error");
				goto fail;
			}
			op_remove();
			break;
		case '$' :
			if(under_lim_check(get_shelf(0), 0)) {
				printf("\n\n$error\n");
				goto fail;
			}
			while(width_check(get_shelf(-1), get_width()))
				grow_wall();
			if(value_zero_check(get_shelf(0)))
				psop_move();
			else
				psop_carry();
			break;
		case '\\' :
			op_reverse();
			break;
		case '[' :
			if(under_lim_check(get_shelf(0), 0) ||
			value_zero_check(get_shelf(0)))
				op_start_loop();
			break;
		case ']' :
			if(under_lim_check(get_shelf(0), 0))
				break;
			else if(value_zero_check(get_shelf(0)))
				slide_index(-1);
			else
				op_end_loop();
			break;
		case '{' :
			if(under_lim_check(get_shelf(0), 0))
				psop_skip_ternary();
			else if(!(value_zero_check(get_shelf(0))))
				slide_index(-1);
			else
				psop_right_ternary();
			break;
		case '}' :
			break;
		case '_' :
			op_switch_ternary();
			break;
		case '(' :
			if(height_check(get_index(), get_height()))
				grow_rack();
			op_start_string();
			break;
		case ')' :
			printf("\n\n)error");
			goto fail;
			break;
		case '\'' :
			if(under_lim_check(get_index(), 0)) {
				printf("\n\n'error\n");
				goto fail;
			}
			op_print_num();
			break;
		case '\"' :
			if(under_lim_check(get_index(), 0)) {
				printf("\n\n\"error\n");
				goto fail;
			}
			op_print_ascii();
			break;
		case '`' :
			if(height_check(get_index(), get_height()))
				grow_rack();
			op_ask_ascii();
			break;
		case '\?' :
			if(height_check(get_index(), get_height()))
				grow_rack();
			op_random();
			break;
		}
		display_wall_rack();
		slide_tape(1);
	}
	wipe_rest();
	return(1);
fail:
	wipe_rest();
	return(0);
}
