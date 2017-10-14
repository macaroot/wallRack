#ifndef OPERATORS_H
#define OPERATORS_H

/* wallRack operators */
void op_insert_num(int number);
void op_add(void);
void op_mult(void);
void op_div(void);
void op_mod(void);
void op_sub(void);
void op_not(void);
void op_and(void);
void op_or(void);
void op_xor(void);
void op_lesser(void);
void op_greater(void);
void op_equals(void);
void op_duplicate(void);
void op_remove(void);
void op_reverse(void);
void psop_move(void);
void psop_carry(void);
void op_start_loop(void);
void op_end_loop(void);
void psop_skip_ternary(void);
void psop_right_ternary(void);
void op_switch_ternary(void);
void op_start_string(void);
void op_print_num(void);
void op_print_ascii(void);
void op_ask_ascii(void);
void op_random(void);

#endif
