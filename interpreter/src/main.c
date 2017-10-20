/* wallRack interpreter in C
 * wallRack is a simple language that consists of an array of 'stacks', which
 * are manipulated tediously with 47 single character operators.
 *
 * You can use a three digit number as an option, and it will show a snapshot
 * (with racks cut to 16 height) of the internal values.
 * Usage: ./wallRack prog ###
 *
 * Structure:
 * wall		- An array which you traverse with absolute notation, currently
 * 		16 indexes.
 * rack		- A stack for each index of wall. Racks start at '-1', so first
 * 		operation on a rack must be one that adds a shelf.
 * shelf	- Racks currently consist of 128 shelfs, which hold decimal
 * 		values.
 *
 * .    .    .    .    .    .    .    .    .    .    .     .     ...
 * .    .    .    .    .    .    .    .    .    .    .     .     ...
 * .    .    .    .    .    .    .    .    .    .    .     .     ...
 * r[9] r[9] r[9] r[9] r[9] r[9] r[9] r[9] r[9] r[9] r[9]  r[9]  ...
 * r[8] r[8] r[8] r[8] r[8] r[8] r[8] r[8] r[8] r[8] r[8]  r[8]  ...
 * r[7] r[7] r[7] r[7] r[7] r[7] r[7] r[7] r[7] r[7] r[7]  r[7]  ...
 * r[6] r[6] r[6] r[6] r[6] r[6] r[6] r[6] r[6] r[6] r[6]  r[6]  ...
 * r[5] r[5] r[5] r[5] r[5] r[5] r[5] r[5] r[5] r[5] r[5]  r[5]  ...
 * r[4] r[4] r[4] r[4] r[4] r[4] r[4] r[4] r[4] r[4] r[4]  r[4]  ...
 * r[3] r[3] r[3] r[3] r[3] r[3] r[3] r[3] r[3] r[3] r[3]  r[3]  ...
 * r[2] r[2] r[2] r[2] r[2] r[2] r[2] r[2] r[2] r[2] r[2]  r[2]  ...
 * r[1] r[1] r[1] r[1] r[1] r[1] r[1] r[1] r[1] r[1] r[1]  r[1]  ...
 * r[0] r[0] r[0] r[0] r[0] r[0] r[0] r[0] r[0] r[0] r[0]  r[0]  ...
 * w[0] w[1] w[2] w[3] w[4] w[5] w[6] w[7] w[8] w[9] w[10] w[11] ...
 *
 *
 * Operators:
 * ;		Linecomment.
 *
 * 0 1 2 3 4 5	Values held by shelves are decimal, but hexadecimals can
 * 6 7 8 9 a b	be used to input values, to ease the need for multidigit
 * c d e f	instructions. Increments rack.
 * 	:: r[i] = O; ++i
 *
 * # ~ @	Get current index of wall / previous index of wall / current
 * 		index of rack. Increments rack.
 * 	:: r[i] = O; ++i
 *
 * + - * / %	Basic mathematical operators, which combine the two shelves.
 * 		Decrements rack.
 * 	:: r[i-1] = r[i] O r[i-1]; r[i] = 0; --i
 *
 * !		Logical not, returns boolean.
 * 	:: r[i] = O r[i]
 *
 * & | ^	Logical operators for two shelves: and / or / xor. Returns
 * 		boolean. Decrements rack.
 * 	:: r[i-1] = r[i] O r[i-1]; r[i] = 0; --i
 *
 * = < >	Comparison of two shelves: equals / lesser / greater /
 * 		returns boolean. Decrements rack.
 * 	:: r[i-1] = r[i] O r[i-1]; r[i] = 0; --i
 *
 * :		Duplicate a shelf. Increments rack.
 * 	:: r[i+1] = r[i]; ++i
 *
 * .		Clear a shelf. Decrements rack.
 * 	:: r[i] = 0; --i
 *
 * $		Move on the wall and optionally carry values from multiple
 * 		shelves. If first shelf is 0, nothing is carried. Decrements
 * 		the two options used by the operator from the rack, and also
 * 		decrements the amount of shelves you took. Increments the rack
 * 		you go to by the amount of shelves you took.
 * 	:: r[i] : How many items down the rack you will carry;
 * 	:: r[i-1] : To which rack you go to;
 *
 * \		Reverses the order of shelves, the amount is specified with
 * 		an option. Decrements rack.
 * 	:: r[i] : How many shelves do you reorder;
 *
 * [ ]		Loop which starts if shelf is not 0, and stops if shelf is
 * 		0 when end bracket is reached. If below rack, start and end are
 * 		entirely ignored. Decrements rack when exciting loop.
 * 	:: at [ if r[i] == 0 or r[-1], go to corresponding ]
 * 	:: at ] if r[i] == 0, --i
 * 	:: at ] if r[i] != 0, go back to corresponding [
 * 	:: at ] if r[-1], do nothing
 *
 * { _ }	Ternary switch. If shelf is 0 the left side of _ operator is
 * 		executed, right side will be skipped, and vice versa if shelf
 * 		not 0. Entering decrements rack. If below rack, both sides are
 * 		ignored. This behavior makes it a pseudo quarternary switch.
 * 	:: at { if r[i] == 0; --i
 * 	:: at { if r[i] != 0, r[i] = 0, go to corresponding _; --i
 * 	:: at { if r[-i], go to corresponding }
 * 	:: at _ go to corresponding };
 *
 * ( )		Stringform. Puts ASCII into shelves sequentially.
 *
 * "		Print shelf as ASCII. Decrements rack.
 * 	:: OUTPUT = r[i]; r[i] = 0; --i
 *
 * '		Ask for ASCII input. Increments rack.
 * 	:: r[i] = INPUT; ++i
 *
 * `		Print decimal value. Decrements rack.
 * 	:: OUTPUT = r[i]; r[i] = 0; --i
 *
 * ?		Generates random number from 0 to option.
 * 	:: r[i] = rand( 0 - r[i] );
 */
#include <stdio.h>
#include "files.h"
#include "interpreter.h"

int confirm_snap(char *argv, int *snap)
{
	char digit;
	int mult;
	int i;
	*snap = 0;
	mult = 1;
	i = 0;
	digit = argv[i];
	while(digit != '\0') {
		if(digit < 48 || digit > 57) {
			printf("\n\nError: use only digits in the second \
option to determine snap\n");
			goto fail;
		}
		++i;
		digit = argv[i];
	}
	--i;
	while(i != -1) {
		digit = (argv[i]-48);
		*snap += (digit*mult);
		mult *= 10;
		--i;
	}
	return(1);
fail:
	return(0);
}

/* main */
int main(int argc, char* argv[])
{
	int snap;
	if(argc > 3 || argc < 2) {
		printf("\n\nError: Provide a program file, and optionally \
give a number to get a screenshot of the wallRack at a certain cycle.\
\nExample usage: %s program 54\n", argv[0]);
		goto fail;
	}
	if(argc == 3)
		if(!confirm_snap(argv[2], &snap))
			goto fail;
	if(!parse_file(fopen(argv[1], "r"))) {
		printf("\n\nError: Could not open file\n");
		goto fail;
	}
	if(!interpret(snap))
		goto fail;
	printf("\n\nSuccessful exit.\n");
	return(0);
fail:
	return(1);
}
