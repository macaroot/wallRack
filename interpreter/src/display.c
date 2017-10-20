#include <stdio.h>
#include "display.h"
#include "primitives.h"

/* Terminal display */
void draw_last_line(int width)
{
	int i;
	for(i = 0; i < width;  ++i) {
		printf("========");
	}
	printf(" Next snap: ");
}

void draw_line(int width)
{
	int i;
	for(i = 0; i < width; ++i) {
		printf("========");
	}
	printf("\n");
}

void draw_single_line(int width)
{
	int i;
	for(i = 0; i < width; ++i) {
		printf("--------");
	}
	printf("\n");
}

void draw_bases(int width)
{
	int i;
	int index;
	for(i = 0; i < width; ++i) {
		index = get_any_index(i);
		if(index < 0)
			printf("-\t");
		else
			printf("%i\t", index);
	}
	printf("\n");
}

void define_field_size(int *fieldHeight, int *width)
{
	int maxHeight;
	int rackHeight;
	int topIndex;
	int i;
	maxHeight = 16;
	topIndex = -1;
	for(i = 0; i < *width; ++i) {
		rackHeight = get_any_height(i);
		if(rackHeight > *fieldHeight)
			*fieldHeight = rackHeight;
		if(topIndex < (get_any_index(i)+1))
			topIndex = (get_any_index(i)+1);
	}
	if(topIndex < maxHeight)
		*fieldHeight = topIndex;
	else
		*fieldHeight = maxHeight;
}

void draw_grid(int fieldHeight, int width)
{
	int i;
	int j;
	for(j = (fieldHeight-1); j > -1; --j) {
		for(i = 0; i < width; ++i) {
			if(get_any_index(i) >= j) {
				printf("%i\t", get_any_shelf(i, j));
			} else {
				printf("\t");
			}
		}
		printf("\n");
	}
}

void display_wall_rack(void)
{
	int width;
	int fieldHeight;
	char cmd;
	fieldHeight = 0;
	width = get_width();
	printf("\n");
	draw_line(width);
	define_field_size(&fieldHeight, &width);
	draw_grid(fieldHeight, width);
	draw_single_line(width);
	draw_bases(width);
	printf("rack:%i token:%c field:%ix%i lapse:%i\n", get_cur(), \
get_token(),
	width, fieldHeight, get_lapse());
	draw_last_line(width);
	cmd = getchar();
	switch(cmd) {
	case '\n' :
		slide_snap(0x1);
		break;
	case '1' :
		slide_snap(0x1);
		getchar();
		break;
	case '2' :
		slide_snap(0x2);
		getchar();
		break;
	case '3' :
		slide_snap(0x3);
		getchar();
		break;
	case '4' :
		slide_snap(0x4);
		getchar();
		break;
	case '5' :
		slide_snap(0x5);
		getchar();
		break;
	case '6' :
		slide_snap(0x6);
		getchar();
		break;
	case '7' :
		slide_snap(0x7);
		getchar();
		break;
	case '8' :
		slide_snap(0x8);
		getchar();
		break;
	case '9' :
		slide_snap(0x9);
		getchar();
		break;
	case 'a' :
		slide_snap(0xa);
		getchar();
		break;
	case 'b' :
		slide_snap(0xb);
		getchar();
		break;
	case 'c' :
		slide_snap(0xc);
		getchar();
		break;
	case 'd' :
		slide_snap(0xd);
		getchar();
		break;
	case 'e' :
		slide_snap(0xe);
		getchar();
		break;
	case 'f' :
		slide_snap(0xf);
		getchar();
		break;
	default :
		set_snap(0);
		break;
	}
}
