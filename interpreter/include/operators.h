#include "main.h"

#ifndef OPERATORS_H
#define OPERATORS_H

/* wallRack operators */
void op_insert_zero(struct Wall *wall, struct Rack **racks);
void op_insert_one(struct Wall *wall, struct Rack **racks);
void op_insert_two(struct Wall *wall, struct Rack **racks);
void op_insert_three(struct Wall *wall, struct Rack **racks);
void op_insert_four(struct Wall *wall, struct Rack **racks);
void op_insert_five(struct Wall *wall, struct Rack **racks);
void op_insert_six(struct Wall *wall, struct Rack **racks);
void op_insert_seven(struct Wall *wall, struct Rack **racks);
void op_insert_eight(struct Wall *wall, struct Rack **racks);
void op_insert_nine(struct Wall *wall, struct Rack **racks);
void op_insert_a(struct Wall *wall, struct Rack **racks);
void op_insert_b(struct Wall *wall, struct Rack **racks);
void op_insert_c(struct Wall *wall, struct Rack **racks);
void op_insert_d(struct Wall *wall, struct Rack **racks);
void op_insert_e(struct Wall *wall, struct Rack **racks);
void op_insert_f(struct Wall *wall, struct Rack **racks);
void op_insert_cur(struct Wall *wall, struct Rack **racks);
void op_insert_pre(struct Wall *wall, struct Rack **racks);
void op_insert_ind(struct Wall *wall, struct Rack **racks);
void op_add(struct Wall *wall, struct Rack **racks);
void op_sub(struct Wall *wall, struct Rack **racks);
void op_mult(struct Wall *wall, struct Rack **racks);
void op_div(struct Wall *wall, struct Rack **racks);
void op_mod(struct Wall *wall, struct Rack **racks);
void op_not(struct Wall *wall, struct Rack **racks);
void op_and(struct Wall *wall, struct Rack **racks);
void op_or(struct Wall *wall, struct Rack **racks);
void op_xor(struct Wall *wall, struct Rack **racks);
void op_lesser(struct Wall *wall, struct Rack **racks);
void op_greater(struct Wall *wall, struct Rack **racks);
void op_equals(struct Wall *wall, struct Rack **racks);
void op_duplicate(struct Wall *wall, struct Rack **racks);
void op_remove(struct Wall *wall, struct Rack **racks);
void op_move(struct Wall *wall, struct Rack **racks);
void op_reverse(struct Wall *wall, struct Rack **racks);
void op_start_loop(struct Tape *tape, struct Wall *wall, struct Rack **racks);
void op_end_loop(struct Tape *tape, struct Wall *wall, struct Rack **racks);
void op_start_ternary(struct Tape *tape, struct Wall *wall, struct Rack **racks);
void op_switch_ternary(struct Tape *tape, struct Wall *wall, struct Rack **racks);
void op_start_string(struct Tape *tape, struct Wall *wall, struct Rack **racks);
void op_print_num(struct Wall *wall, struct Rack **racks);
void op_print_ascii(struct Wall *wall, struct Rack **racks);
void op_ask_ascii(struct Wall *wall, struct Rack **racks);
void op_random(struct Wall *wall, struct Rack **racks);

#endif
