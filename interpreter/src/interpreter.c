#include <stdio.h>
#include "interpreter.h"
#include "primitives.h"
#include "memory.h"
#include "operators.h"
#include "display.h"

/* Interpreting tokens */
int interpret(int snap)
{
	set_snap(snap);
	while(get_token() != '\0') {
		if(get_index() < -1) {
			printf("\n\nindex error");
			goto fail;
		}
		switch(get_token()) {
		case '0' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_insert_num(0x0);
			break;
		case '1' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_insert_num(0x1);
			break;
		case '2' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_insert_num(0x2);
			break;
		case '3' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_insert_num(0x3);
			break;
		case '4' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_insert_num(0x4);
			break;
		case '5' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_insert_num(0x5);
			break;
		case '6' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_insert_num(0x6);
			break;
		case '7' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_insert_num(0x7);
			break;
		case '8' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_insert_num(0x8);
			break;
		case '9' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_insert_num(0x9);
			break;
		case 'a' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_insert_num(0xa);
			break;
		case 'b' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_insert_num(0xb);
			break;
		case 'c' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_insert_num(0xc);
			break;
		case 'd' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_insert_num(0xd);
			break;
		case 'e' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_insert_num(0xe);
			break;
		case 'f' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_insert_num(0xf);
			break;
		case '#' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_insert_cur();
			break;
		case '~' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_insert_pre();
			break;
		case '@' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_insert_index();
			break;
		case '+' :
			if(get_index() < 1) {
				printf("\n\n+error\n");
				goto fail;
			}
			op_add();
			break;
		case '-' :
			if(get_index() < 1) {
				printf("\n\n-error\n");
				goto fail;
			}
			op_sub();
			break;
		case '*' :
			if(get_index() < 1) {
				printf("\n\n*error\n");
				goto fail;
			}
			op_mult();
			break;
		case '/' :
			if(get_index() < 1) {
				printf("\n\n/error\n");
				goto fail;
			}
			op_div();
			break;
		case '%' :
			if(get_index() < 1) {
				printf("\n\n%%error\n");
				goto fail;
			}
			op_mod();
			break;
		case '!' :
			if(get_index() < 0) {
				printf("\n\n!error");
				goto fail;
			}
			op_not();
			break;
		case '&' :
			if(get_index() < 1) {
				printf("\n\n&error");
				goto fail;
			}
			op_and();
			break;
		case '|' :
			if(get_index() < 1) {
				printf("\n\n|error");
				goto fail;
			}
			op_or();
			break;
		case '^' :
			if(get_index() < 1) {
				printf("\n\n^error");
				goto fail;
			}
			op_xor();
			break;
		case '<' :
			if(get_index() < 1) {
				printf("\n\n<error\n");
				goto fail;
			}
			op_lesser();
			break;
		case '>' :
			if(get_index() < 1) {
				printf("\n\n>error\n");
				goto fail;
			}
			op_greater();
			break;
		case '=' :
			if(get_index() < 1) {
				printf("\n\n=error\n");
				goto fail;
			}
			op_equals();
			break;
		case ':' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_duplicate();
			break;
		case '.' :
			if(get_index() < 0) {
				printf("\n\n=error\n");
				goto fail;
			}
			op_remove();
			break;
		case '$' :
			if(get_index() < 1) {
				printf("\n\n$error bottom\n");
				goto fail;
			}
			else if(get_shelf(0) < 0) {
				printf("\n\n$error -carry\n");
				goto fail;
			}
			else if(get_shelf(0) >= get_index()) {
				printf("\n\n$error too many carry\n");
				goto fail;
			}
/*	decwall		if(get_shelf(-1) != get_cur())
 *				psop_adjust_used_width;
 */	/* grow forrak if((car+forind) > (forheight-2)) */
			while(get_shelf(-1) > (get_width()-1))
				mem_grow_wall();
			if(get_shelf(0) == 0)
				psop_move();
			else
				psop_carry();
/*			while((get_shelf(-1)/4) < ((get_used_width()/4)*8))
 *				mem_reduce_wall();
 */			break;
		case '\\' :
			if(get_index() < 1) {
				printf("\n\n\\error bottom\n");
				goto fail;
			}
			if(get_index() == 1) {
				set_shelf(0,0);
				slide_index(-1);
			} else {
				op_reverse();
			}
			break;
		case '[' :
			if((get_index() < 0) || (get_shelf(0) == 0))
				op_start_loop();
			break;
		case ']' :
			if(get_index() < 0)
				break;
			else if(get_shelf(0) == 0)
				slide_index(-1);
			else
				op_end_loop();
			break;
		case '{' :
			if(get_index() < 0)
				psop_skip_ternary();
			else if(get_shelf(0) == 0)
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
			op_start_string();
			break;
		case ')' :
			printf("\n\n)error\n");
			goto fail;
			break;
		case '\'' :
			if(get_index() < 0) {
				printf("\n\n'error\n");
				goto fail;
			}
			op_print_num();
			break;
		case '\"' :
			if(get_index() < 0) {
				printf("\n\n\"error\n");
				goto fail;
			}
			op_print_ascii();
			break;
		case '`' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_ask_ascii();
			break;
		case '\?' :
			if(get_index() > (get_height()-2))
				mem_grow_rack();
			op_random();
			break;
		}
		if(get_snap() == get_lapse())
			display_wall_rack();
		slide_lapse(1);
		slide_tape(1);
	}
	mem_wipe_rest();
	return(1);
fail:
	mem_wipe_rest();
	return(0);
}
