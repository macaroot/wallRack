#include <stdio.h>
#include "display.h"
#include "primitives.h"

/* Terminal display */
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

void draw_grid(int *fieldHeightPtr, int *widthPtr)
{
	int maxHeight;
	int fHeight;
	int topIndex;
	int i;
	int j;
	maxHeight = 16;
	topIndex = -1;
	for(i = 0; i < *widthPtr; ++i) {
		fHeight = get_any_height(i);
		if(fHeight > *fieldHeightPtr)
			*fieldHeightPtr = fHeight;
		if(topIndex < (get_any_index(i)+1))
			topIndex = (get_any_index(i)+1);
	}
	if(topIndex < maxHeight)
		maxHeight = topIndex;
	for(j = (maxHeight-1); j > -1; --j) {
		for(i = 0; i < *widthPtr; ++i) {
			if(get_any_index(i) >= j) {
				printf("%i\t", get_any_shelf(i, j));
			} else {
				printf("\t");
			}
		}
		printf("\n");
	}
}

void display_wall_rack(int lapse, int *snap)
{
	int width;
	int fieldHeight;
	char cmd;
	fieldHeight = 0;
	width = get_width();
	printf("\n");
	draw_line(width);
	draw_grid(&fieldHeight, &width);
	draw_single_line(width);
	draw_bases(width);
	printf("rack:%i token:%c field:%ix%i lapse:%i\n", get_cur(), get_token(),
	width, fieldHeight, get_lapse());
	draw_line(width);
	cmd = getchar();
	switch(cmd) {
	case '\n' :
		*snap += 0x1;
		break;
	case '1' :
		*snap += 0x1;
		getchar();
		break;
	case '2' :
		*snap += 0x2;
		getchar();
		break;
	case '3' :
		*snap += 0x3;
		getchar();
		break;
	case '4' :
		*snap += 0x4;
		getchar();
		break;
	case '5' :
		*snap += 0x5;
		getchar();
		break;
	case '6' :
		*snap += 0x6;
		getchar();
		break;
	case '7' :
		*snap += 0x7;
		getchar();
		break;
	case '8' :
		*snap += 0x8;
		getchar();
		break;
	case '9' :
		*snap += 0x9;
		getchar();
		break;
	case 'a' :
		*snap += 0xa;
		getchar();
		break;
	case 'b' :
		*snap += 0xb;
		getchar();
		break;
	case 'c' :
		*snap += 0xc;
		getchar();
		break;
	case 'd' :
		*snap += 0xd;
		getchar();
		break;
	case 'e' :
		*snap += 0xe;
		getchar();
		break;
	case 'f' :
		*snap += 0xf;
		getchar();
		break;
	default :
		*snap = 0;
		break;
	}
}
