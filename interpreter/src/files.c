#include <stdio.h>
#include "files.h"
#include "primitives.h"
#include "memory.h"

/* File handling */
int fill_raw(FILE *file)
{
	int chara;
	int i;
	i = 0;
	while((chara = fgetc(file)) != EOF) {
		set_raw(i, chara);
		++i;
		if(i >= get_raw_length()) {
			mem_grow_raw();
		}
	}
	if(i == 0)
		goto fail;
	set_raw((i-1), '\0');
	return(1);
fail:
	return(0);
}

int fill_tokens(void)
{
	int i;
	int j;
	int leap;
	int dev;
	char mainraw;
	i = 0;
	j = 0;
	while(get_raw(i) != '\0') {
		mainraw = get_raw(i);
		leap = 1;
		dev = 1;
		if(mainraw == ';') {
			while((get_raw(i+dev) != '\n') &&
			(get_raw(i+dev) != '\0')) {
				++leap;
				++dev;
			}
			++leap;
			dev = 1;
		} else if(mainraw == '(') {
			set_token(j, '(');
			++j;
			if(j >= get_token_length())
				mem_grow_tokens();
			while(get_raw(i+dev) != ')') {
				if(get_raw(i+dev) == '\0') {
					printf( "\n\nError: String end was \
not found while tokenizing file.\n" );
					goto fail;
				}
				set_token(j, get_raw(i+dev));
				++j;
				if(j >= get_token_length())
					mem_grow_tokens();
				++leap;
				++dev;
			}
			set_token(j, ')');
			++j;
			if(j >= get_token_length())
				mem_grow_tokens();
			++leap;
			dev = 1;
		} else if(mainraw == '0' || mainraw == '1' ||
		mainraw == '2' || mainraw == '3' ||
		mainraw == '4' || mainraw == '5' ||
		mainraw == '6' || mainraw == '7' ||
		mainraw == '8' || mainraw == '9' ||
		mainraw == 'a' || mainraw == 'b' ||
		mainraw == 'c' || mainraw == 'd' ||
		mainraw == 'e' || mainraw == 'f' ||
		mainraw == '#' || mainraw == '~' ||
		mainraw == '@' || mainraw == '+' ||
		mainraw == '-' || mainraw == '*' ||
		mainraw == '/' || mainraw == '%' ||
		mainraw == '!' || mainraw == '&' ||
		mainraw == '|' || mainraw == '^' ||
		mainraw == '<' || mainraw == '>' ||
		mainraw == '>' || mainraw == ':' ||
		mainraw == '.' || mainraw == '$' ||
		mainraw == '\\' || mainraw == '[' ||
		mainraw == ']' || mainraw == '{' ||
		mainraw == '}' || mainraw == '_' ||
		mainraw == '\'' || mainraw == '\"' ||
		mainraw == '`' || mainraw == '\?') {
			if(j >= get_token_length())
				mem_grow_tokens();
			set_token(j, mainraw);
			++j;
		}
		i += leap;
	}
	if(j == 0) {
		printf("\nError: No recognizable characters.\n");
		goto fail;
	}
	if((j+1) >= get_token_length())
		mem_grow_tokens();
	set_token(j, '\0');
	return(1);
fail:
	return(0);
}

int parse_file(FILE *file)
{
	if(!file) {
		printf("\n\nError: Could not open file\n");
		goto fail;
	}
	mem_init_wall_rack();
	if(!fill_raw(file)) {
		printf("\n\nError: Empty file\n");
		fclose(file);
		goto fail;
	}
	fclose(file);
	if(!fill_tokens())
		goto fail;
	mem_wipe_raw();
	return(1);
fail:
	mem_wipe_raw();
	mem_wipe_rest();
	return(0);
}
