#include "checks.h"

/* Checks */
int height_check(int index, int height)
{
	return(index > (height-2));
}

int width_check(int value, int width)
{
	return(value > (width-1));
}

int under_lim_check(int value, int limit)
{
	return(value < limit);
}

int value_zero_check(int value)
{
	return(value == 0);
}
