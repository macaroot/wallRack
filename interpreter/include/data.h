#ifndef DATA_H
#define DATA_H

/* Getset declarations */
struct State * get_state_context(void);
struct Tape * get_tape_context(void);
struct Rack ** get_racks_context(void);
struct Wall * get_wall_context(void);
void set_raw(int number, char chara);
char get_raw(int number);
int get_raw_length(void);
void double_raw_length(void);
char get_token(void);
void set_token(int number, char chara);
int get_token_length(void);
void double_token_length(void);
void slide_tape(int slide);
int get_width(void);
void set_width(int width);
int get_height(void);
void set_height(int height);
int get_index(void);
void set_index(int index);
void slide_index(int slide);
int get_pre_index(void);
void set_pre_index(int index);
void slide_pre_index(int slide);
int get_shelf(int aber);
void set_shelf(int aber, int value);
void set_foreign_shelf(int dest, int aber, int value);
void slide_foreign_index(int dest, int slide);
int get_cur(void);
void set_cur(int value);
int get_pre(void);
void set_pre(int value);

void realloc_raw(void);
void realloc_tokens(void);
void realloc_rack(void);
void realloc_wall(void);

void free_raw(void);
void free_tokens(void);
void free_wall(void);
void free_racks(void);

void init_wall_rack(void);

int get_any_shelf(int rack, int index);
int get_any_height(int number);
int get_any_index(int number);

#endif
