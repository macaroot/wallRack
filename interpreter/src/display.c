#include <stdio.h>
#include "display.h"
#include "data.h"

void draw_line (int width)
{
	int i;
	for(i = 0; i < width; ++i) {
		printf("========");
	}
	printf("\n");
}

void draw_bases (int width)
{
	int i;
	for(i = 0; i < width; ++i) {
		printf("%i\t", get_any_index(i));
	}
	printf("\n");
}

void display_wall_rack(void)
{
	int width;
	int height;
	int maxHeight;
	int used;
	int i;
	int j;
	maxHeight = 16;
	width = get_width();
	printf("\n");
	draw_line(width);
	for(j = (maxHeight-1); j > -1; --j) {
		used = 0;
		for(i = 0; i < width; ++i) {
			height = get_any_height(i);
			if(height >= j) {
				printf("%i\t", get_any_shelf(i, j));
				used = 1;
			} else {
				printf("\t");
				used = 1;
			}
		}
		if(used)
			printf("\n");
	}
	draw_line(width);
	draw_bases(width);
	printf("Rack: %i, token:%c\n", get_cur(), get_token());
	draw_line(width);
}
