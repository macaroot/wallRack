#ifndef PRIMITIVES_H
#define PRIMITIVES_H

/* Interface for primitive data manipulation */
int get_lapse(void);
void set_lapse(int lapse);
void slide_lapse(int slide);
int get_snap(void);
void set_snap(int snap);
void slide_snap(int slide);
void set_raw(int number, char chara);
char get_raw(int number);
int get_raw_length(void);
void double_raw_length(void);
char get_token(void);
void set_token(int number, char chara);
int get_token_length(void);
void double_token_length(void);
void slide_tape(int slide);
int get_step(void);
int get_width(void);
void set_width(int width);
int get_used_width(void);
void set_used_width(int width);
int get_height(void);
void set_height(int height);
int get_index(void);
void set_index(int index);
void slide_index(int slide);
int get_shelf(int aber);
void set_shelf(int aber, int value);
void set_foreign_shelf(int dest, int aber, int value);
/* int get_foreign_index(int number); */
void slide_foreign_index(int dest, int slide);
int get_cur(void);
void set_cur(int value);
int get_pre(void);
void set_pre(int value);

/* Necessities for display */
int get_any_shelf(int rack, int index);
int get_any_height(int number);
int get_any_index(int number);

#endif
