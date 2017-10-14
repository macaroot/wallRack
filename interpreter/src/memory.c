#include "memory.h"
#include "data.h"

/* Growing */
void grow_rack(void)
{
	set_height((get_height() * 0x2));
	realloc_rack();
}

void grow_wall(void)
{
	set_width((get_width() * 0x2));
	realloc_wall();
}

/* Wipes */
void wipe_raw(void)
{
	free_raw();
}

void wipe_tokens(void)
{
	free_tokens();
}

void wipe_racks(void)
{
	free_racks();
	free_wall();
}

void wipe_rest(void)
{
	wipe_tokens();
	wipe_racks();
}

