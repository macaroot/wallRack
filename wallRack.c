/*{{{*//* wallRack
 * Simple language that consists of an array of stacks, which are manipulated
 * tediously with 44 single character operators.
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
 * w[0] w[1] w[2] w[3] w[4] w[5] w[6] w[7] w[8] w[9] w[10] w[11] ...
 * r[0] r[0] r[0] r[0] r[0] r[0] r[0] r[0] r[0] r[0] r[0]  r[0]  ...
 * r[1] r[1] r[1] r[1] r[1] r[1] r[1] r[1] r[1] r[1] r[1]  r[1]  ...
 * r[2] r[2] r[2] r[2] r[2] r[2] r[2] r[2] r[2] r[2] r[2]  r[2]  ...
 * r[3] r[3] r[3] r[3] r[3] r[3] r[3] r[3] r[3] r[3] r[3]  r[3]  ...
 * r[4] r[4] r[4] r[4] r[4] r[4] r[4] r[4] r[4] r[4] r[4]  r[4]  ...
 * r[5] r[5] r[5] r[5] r[5] r[5] r[5] r[5] r[5] r[5] r[5]  r[5]  ...
 * r[6] r[6] r[6] r[6] r[6] r[6] r[6] r[6] r[6] r[6] r[6]  r[6]  ...
 * r[7] r[7] r[7] r[7] r[7] r[7] r[7] r[7] r[7] r[7] r[7]  r[7]  ...
 * r[8] r[8] r[8] r[8] r[8] r[8] r[8] r[8] r[8] r[8] r[8]  r[8]  ...
 * r[9] r[9] r[9] r[9] r[9] r[9] r[9] r[9] r[9] r[9] r[9]  r[9]  ...
 * .    .    .    .    .    .    .    .    .    .    .     .     ...
 * .    .    .    .    .    .    .    .    .    .    .     .     ...
 * .    .    .    .    .    .    .    .    .    .    .     .     ...
 *
 * Operators:
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
 * 	:: r[i-1] = r[i] O r[i-1]; --i
 *
 * !		Logical not, returns boolean.
 * 	:: r[i] = O r[i]
 *
 * & | ^	Logical operators for two shelves: and / or / xor. Returns
 * 		boolean. Decrements rack.
 * 	:: r[i-1] = r[i] O r[i-1]; --i
 *
 * = < >	Comparison of two shelves: equals / lesser / greater /
 * 		returns boolean. Decrements rack.
 * 	:: r[i-1] = r[i] O r[i-1]; --i
 *
 * :		Duplicate shelf's contents. Increments rack.
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
 * 		0 when end bracket is reached.
 *
 * { _ }	Ternary switch. If shelf is 0 the left side of _ operator is
 * 		executed, right side will be skipped, and vice versa if shelf
 * 		not 0. Decrements rack.
 * 	:: r[i] = 0; --i
 *
 * "		Print shelf as ASCII. Decrements rack.
 * 	:: OUTPUT = r[i]; r[i] = 0; --i
 *
 * '		Ask for ASCII input. Increments rack.
 * 	:: r[i] = INPUT; ++i
 *
 * '		Print decimal value. Decrements rack.
 * 	:: OUTPUT = r[i]; r[i] = 0; --i
 *
 * ?		Generates random number from 0 to option.
 * 	:: r[i] = rand( 0 - r[i] );
 *//*}}}*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int EJECT = 0;
const int WIDTH = 0x10;
const int HEIGHT = 0x80;
char RAWARR[0x80];
char TOKARR[0x80];
int CURR;
int PREV;
int STEP;
int TOKEN;
int LAPSE;
int SNAP;
typedef struct sWall WALL;
struct sWall
{
	int rack[0x80];
	int shelf;
};
WALL wall[0x10];

void output( void )
{/*{{{*/
	int i;
	int j;
	printf( "\n" );
	for( i = 0; i < 10; i++ )
	{
		if( i == 0 )
		{
			for( j = 0; j < WIDTH; j ++)
			{
				printf( "========", wall[j].shelf );
			};
			printf( "\ncurr: %i, prev: %i, token: %c, step: %i, lapse: %i\n", CURR, PREV, TOKEN, STEP, LAPSE );
			for( j = 0; j < WIDTH; j ++)
			{
				printf( "--------", wall[j].shelf );
			};
			printf( "\n" );
			for( j = 0; j < WIDTH; j ++)
			{
				if( j == CURR )
				{
					printf( "[%i]\t", wall[j].shelf );
				}
				else
				{
					printf( "%i\t", wall[j].shelf );
				}
			};
			printf( "\n" );
			for( j = 0; j < WIDTH; j ++)
			{
				printf( "--------", wall[j].shelf );
			};
			printf( "\n" );
		}
		for( j = 0; j < WIDTH; j++ )
		{
			if( ( j == CURR ) && ( i == wall[CURR].shelf ) )
			{
				printf( "%i <\t", wall[j].rack[i] );
			}
			else
			{
				printf( "%i\t", wall[j].rack[i] );
			}
		}
		printf( "\n" );
	}
	for( j = 0; j < WIDTH; j ++)
	{
		printf( "========", wall[j].shelf );
	};
	printf( "\n\n" );
}/*}}}*/

void run( void )
{/*{{{*/
	STEP = 0;
	if( LAPSE == SNAP )
	{
		output();
	}
	while( ( TOKARR[STEP] != '\0' ) && ( EJECT == 0 ) )
	{
		TOKEN = TOKARR[STEP];
		switch( TOKEN )
		{
			case '0' :
				if( wall[CURR].shelf > ( HEIGHT - 2 ) )/*{{{*/
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : 0 . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 0x0;
				}
				break;/*}}}*/
			case '1' :
				if( wall[CURR].shelf > ( HEIGHT - 2 ) )/*{{{*/
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : 1 . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 0x1;
				}
				break;/*}}}*/
			case '2' :
				if( wall[CURR].shelf > ( HEIGHT - 2 ) )/*{{{*/
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : 2 . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 0x2;
				}
				break;/*}}}*/
			case '3' :
				if( wall[CURR].shelf > ( HEIGHT - 2 ) )/*{{{*/
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : 3 . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 0x3;
				}
				break;/*}}}*/
			case '4' :
				if( wall[CURR].shelf > ( HEIGHT - 2 ) )/*{{{*/
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : 4 . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 0x4;
				}
				break;/*}}}*/
			case '5' :
				if( wall[CURR].shelf > ( HEIGHT - 2 ) )/*{{{*/
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : 5 . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 0x5;
				}
				break;/*}}}*/
			case '6' :
				if( wall[CURR].shelf > ( HEIGHT - 2 ) )/*{{{*/
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : 6 . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 0x6;
				}
				break;/*}}}*/
			case '7' :
				if( wall[CURR].shelf > ( HEIGHT - 2 ) )/*{{{*/
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : 7 . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 0x7;
				}
				break;/*}}}*/
			case '8' :
				if( wall[CURR].shelf > ( HEIGHT - 2 ) )/*{{{*/
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : 8 . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 0x8;
				}
				break;/*}}}*/
			case '9' :
				if( wall[CURR].shelf > ( HEIGHT - 2 ) )/*{{{*/
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : 9 . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 0x9;
				}
				break;/*}}}*/
			case 'a' :
				if( wall[CURR].shelf > ( HEIGHT - 2 ) )/*{{{*/
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : a . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 0xa;
				}
				break;/*}}}*/
			case 'b' :
				if( wall[CURR].shelf > ( HEIGHT - 2 ) )/*{{{*/
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : b . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 0xb;
				}
				break;/*}}}*/
			case 'c' :
				if( wall[CURR].shelf > ( HEIGHT - 2 ) )/*{{{*/
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : c . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 0xc;
				}
				break;/*}}}*/
			case 'd' :
				if( wall[CURR].shelf > ( HEIGHT - 2 ) )/*{{{*/
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : d . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 0xd;
				}
				break;/*}}}*/
			case 'e' :
				if( wall[CURR].shelf > ( HEIGHT - 2 ) )/*{{{*/
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : e . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 0xe;
				}
				break;/*}}}*/
			case 'f' :
				if( wall[CURR].shelf > ( HEIGHT - 2 ) )/*{{{*/
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : f . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 0xf;
				}
				break;/*}}}*/
			case '#' :
				if( wall[CURR].shelf > ( HEIGHT - 2 ) )/*{{{*/
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : # . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = CURR;
				}
				break;/*}}}*/
			case '~' :
				if( wall[CURR].shelf > ( HEIGHT - 2 ) )/*{{{*/
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : ~ . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = PREV;
				}
				break;/*}}}*/
			case '@' :
				if( wall[CURR].shelf > ( HEIGHT - 2 ) )/*{{{*/
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : @ . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = wall[CURR].shelf;
				}
				break;/*}}}*/
			case '+' :
				if( wall[CURR].shelf < 1 )/*{{{*/
				{
					printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : + . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					wall[CURR].rack[wall[CURR].shelf - 1] +=
                                        wall[CURR].rack[wall[CURR].shelf];
        				wall[CURR].rack[wall[CURR].shelf] = 0;
        				--wall[CURR].shelf;
        			}
				break;/*}}}*/
			case '-' :
				if( wall[CURR].shelf < 1 )/*{{{*/
				{
					printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : - . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					wall[CURR].rack[wall[CURR].shelf - 1] -=
                                        wall[CURR].rack[wall[CURR].shelf];
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				}
				break;/*}}}*/
			case '*' :
				if( wall[CURR].shelf < 1 )/*{{{*/
				{
					printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : * . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					wall[CURR].rack[wall[CURR].shelf - 1] *=
                                        wall[CURR].rack[wall[CURR].shelf];
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				}
				break;/*}}}*/
			case '/' :
				if( wall[CURR].shelf < 1 )/*{{{*/
				{
					printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : / . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					wall[CURR].rack[wall[CURR].shelf - 1] /=
                                        wall[CURR].rack[wall[CURR].shelf];
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				}
				break;/*}}}*/
			case '%' :
				if( wall[CURR].shelf < 1 )/*{{{*/
				{
					printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : \% . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					wall[CURR].rack[wall[CURR].shelf - 1] %=
                                        wall[CURR].rack[wall[CURR].shelf];
		 			wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				}
				break;/*}}}*/
			case '!' :
				if( wall[CURR].shelf < 0 )/*{{{*/
				{
					printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : ! . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else if( wall[CURR].rack[wall[CURR].shelf] != 0)
				{
					wall[CURR].rack[wall[CURR].shelf] = 0;
				}
				else
				{
					wall[CURR].rack[wall[CURR].shelf] = 1;
				}
				break;/*}}}*/
			case '&' :
				if( wall[CURR].shelf < 1 )/*{{{*/
				{
					printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : & . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else if( wall[CURR].rack[wall[CURR].shelf] &&
				wall[CURR].rack[wall[CURR].shelf - 1 ] )
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 1;
				}
				else
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 0;
				}
				wall[CURR].rack[wall[CURR].shelf] = 0;
				--wall[CURR].shelf;
				break;/*}}}*/
			case '|' :
				if( wall[CURR].shelf < 1 )/*{{{*/
				{
					printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : | . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else if( wall[CURR].rack[wall[CURR].shelf] ||
				wall[CURR].rack[wall[CURR].shelf - 1 ] )
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 1;
				}
				else
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 0;
				}
				wall[CURR].rack[wall[CURR].shelf] = 0;
				--wall[CURR].shelf;
				break;/*}}}*/
			case '^' :
				if( wall[CURR].shelf < 1 )/*{{{*/
				{
					printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : ^ . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else if( ( wall[CURR].rack[wall[CURR].shelf] ||
				wall[CURR].rack[wall[CURR].shelf - 1 ] ) &&
				!( wall[CURR].rack[wall[CURR].shelf] &&
				wall[CURR].rack[wall[CURR].shelf - 1 ] ) )
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 1;
				}
				else
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 0;
				}
				wall[CURR].rack[wall[CURR].shelf] = 0;
				--wall[CURR].shelf;
				break;/*}}}*/
			case '<' :
				if( wall[CURR].shelf < 1 )/*{{{*/
				{
					printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : < . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else if( wall[CURR].rack[wall[CURR].shelf] <
				wall[CURR].rack[wall[CURR].shelf - 1 ] )
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 1;
				}
				else
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 0;
				}
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				break;/*}}}*/
			case '>' :
				if( wall[CURR].shelf > 1 )/*{{{*/
				{
					printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : > . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else if( wall[CURR].rack[wall[CURR].shelf] >
				wall[CURR].rack[wall[CURR].shelf - 1 ] )
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 1;
				}
				else
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 0;
				}
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				break;/*}}}*/
			case '=' :
				if( wall[CURR].shelf > 1 )/*{{{*/
				{
					printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : > . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else if( wall[CURR].rack[wall[CURR].shelf] ==
				wall[CURR].rack[wall[CURR].shelf - 1 ] )
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 1;
				}
				else
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 0;
				}
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				break;/*}}}*/
			case ':' :
				if( wall[CURR].shelf < 0 )/*{{{*/
				{
					printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : : . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				if( wall[CURR].shelf > ( HEIGHT - 2 ) )
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : : . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					wall[CURR].rack[wall[CURR].shelf + 1] =
                                        wall[CURR].rack[wall[CURR].shelf];
					++wall[CURR].shelf;
				}
				break;/*}}}*/
			case '.' :
				if( wall[CURR].shelf < 0 )/*{{{*/
				{
					printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : . . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				}
				break;/*}}}*/
			case '$' :
				if( wall[CURR].rack[wall[CURR].shelf] < 0 )/*{{{*/
				{
					printf( "\nError: Negative number used for collecting moved values at rack %i, \
during token #%i : $ . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else if( wall[CURR].rack[wall[CURR].shelf] == 0 )
				{
					if( wall[CURR].shelf < 1 )
					{
						printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : $ . Lapse: %i\n", CURR, STEP, LAPSE );
						EJECT = 1;
					}
					else if( ( wall[CURR].rack[wall[CURR].shelf - 1] < 0 ) ||
                                                 ( wall[CURR].rack[wall[CURR].shelf - 1] > WIDTH ) )
					{
						printf( "\nError: Values were attempted to be moved to non-existent rack %i at rack %i, \
during token #%i : $ . Lapse: %i\n", wall[CURR].rack[wall[CURR].shelf - 1], CURR, STEP, LAPSE );
						EJECT = 1;
					}
					else
					{
						PREV = CURR;
						CURR = wall[CURR].rack[wall[CURR].shelf - 1];
						wall[PREV].rack[wall[PREV].shelf - 1] = 0;
						wall[PREV].shelf -= 2;
					}
				}
				else
				{
					if( wall[CURR].shelf < ( wall[CURR].rack[wall[CURR].shelf] + 1 ) )
					{
						printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : $ . Lapse: %i\n", CURR, STEP, LAPSE );
						EJECT = 1;
					}
					else if( ( wall[CURR].rack[wall[CURR].shelf - 1] < 0 ) ||
                                                 ( wall[CURR].rack[wall[CURR].shelf - 1] > WIDTH ) )
					{
						printf( "\nError: Values were attempted to be moved to non-existent rack %i at rack %i, \
during token #%i : $ . Lapse: %i\n", wall[CURR].rack[wall[CURR].shelf - 1], CURR, STEP, LAPSE );
						EJECT = 1;
					}
					else if( ( wall[wall[CURR].rack[wall[CURR].shelf -1]].shelf +
                                                   wall[CURR].rack[wall[CURR].shelf] ) > ( HEIGHT - 2 ) )
					{
						printf( "\nError: Rack top exceeded in destination rack %i at rack %i, \
during token #%i : $ . Lapse: %i\n", wall[CURR].rack[wall[CURR].shelf - 1], CURR, STEP, LAPSE );
						EJECT = 1;
					}
					else
					{
						int i;
						int j;
						int d;
						j = wall[CURR].rack[wall[CURR].shelf];
						d = wall[CURR].rack[wall[CURR].shelf - 1];
						wall[CURR].rack[wall[CURR].shelf] = 0;
						wall[CURR].rack[wall[CURR].shelf - 1] = 0;
						wall[CURR].shelf -= 2;
						for( i = 0; i < j; i++ )
						{
							wall[d].rack[wall[d].shelf + 1 + i] =
                                                        wall[CURR].rack[wall[CURR].shelf - ( j - 1 ) + i];
							++wall[d].shelf;
						}
						for( i = 0; i < j; i++ )
						{
							wall[CURR].rack[wall[CURR].shelf - i] = 0;
							--wall[CURR].shelf;
						}
						PREV = CURR;
						CURR = d;
					}
				}
				break;/*}}}*/
			case '\\' :
				if( wall[CURR].shelf < ( wall[CURR].rack[wall[CURR].shelf] - 1 ) )/*{{{*/
				{
					printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : \\. Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					int i;
					int j;
					int s;
					j = wall[CURR].rack[wall[CURR].shelf];
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
					for( i = 0; i < ( j / 2 ); i++)
					{
						s = wall[CURR].rack[wall[CURR].shelf - i];
						wall[CURR].rack[wall[CURR].shelf - i] = wall[CURR].rack[wall[CURR].shelf - ( j - i ) + 1];
						wall[CURR].rack[wall[CURR].shelf - ( j - i ) + 1] = s;
					}
				}
				break;/*}}}*/
			case '[' :
				if( wall[CURR].shelf < 0 )/*{{{*/
				{
					printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : [ . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else if( wall[CURR].rack[wall[CURR].shelf] == 0 )
				{
					int b;
					int bt;
					int loop;
					loop = 0;
					b = STEP;
					bt = TOKARR[STEP];
					++STEP;
					while( ( TOKARR[STEP] != ']' ) && ( loop != 0 ) )
					{
						if( STEP > 0x80 )
						{
							printf( "\nError: Loop end was not found at rack %i, \
during token #%i : [ . Lapse: %i\n", CURR, b, LAPSE );
							EJECT = 1;
						}
						else
						{
							if( TOKARR[STEP] == '[' )
							{
								++loop;
							}
							else if( TOKARR[STEP] == ']' )
							{
								--loop;
								if( loop == 0 )
								{
									--STEP;
								}
							}
							++STEP;
						}
					}
				}
				break;/*}}}*/
			case ']' :
				if( wall[CURR].shelf < 0 )/*{{{*/
				{
					printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : ] . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else if( wall[CURR].rack[wall[CURR].shelf] != 0 )
				{
					int b;
					int bt;
					int out;
					int loop;
					out = 0;
					loop = 1;
					b = STEP;
					bt = TOKARR[STEP];
					while( out == 0 && EJECT == 0 )
					{
						--STEP;
						if( STEP < 0 )
						{
							printf( "\nError: Error: Loop start was not found at rack %i, \
during token #%i : ] . Lapse: %i\n", CURR, b, LAPSE );
							EJECT = 1;
						}
						else
						{
							if( TOKARR[STEP] == ']' )
							{
								++loop;
							}
							else if( TOKARR[STEP] == '[' )
							{
								--loop;
								if( loop == 0 )
								{
									out = 1;
								}
							}
						}
					}
				}
				break;/*}}}*/
			case '{' :
				if( wall[CURR].shelf < 0 )/*{{{*/
				{
					printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : { . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else if( wall[CURR].rack[wall[CURR].shelf] == 0 )
				{
					--wall[CURR].shelf;
				}
				else
				{
					int b;
					int bt;
					int out;
					int tern;
					b = STEP;
					bt = TOKARR[STEP];
					out = 0;
					tern = 0;
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
					while( out == 0 )
					{
						++STEP;
						if( TOKARR[STEP] == '{' )
						{
							++tern;
						}
						else if( TOKARR[STEP] == '}' )
						{
							--tern;
						}
						else if( TOKARR[STEP] == '_' )
						{
							if( tern == 0 )
							{
								out = 1;
							}
						}
						if( tern < 0 )
						{
							printf( "\nError: Extra ternary end found at rack %i, \
during token #%i : { . Lapse: %i\n", CURR, b, LAPSE );
							EJECT = 1;
						}
					}
				}
				break;/*}}}*/
			case '}' :
				break;
			case '_' :
				if( 1 )/*{{{*/
				{
					int b;
					int bt;
					int out;
					int tern;
					b = STEP;
					bt = TOKARR[STEP];
					tern = 1;
					while( out == 0 )
					{
						++STEP;
						if( TOKARR[STEP] == '{' )
						{
							++tern;
						}
						else if( TOKARR[STEP] == '}' )
						{
							--tern;
							if( tern == 0 )
							{
								out = 1;
							}
						}
						if( tern < 0 )
						{
							printf( "\nError: Extra ternary end found at rack %i, \
during token #%i : } . Lapse: %i\n", CURR, b, LAPSE );
							EJECT = 1;
						}
					}
				}
				break;/*}}}*/
			case '\'' :
				if( wall[CURR].shelf > ( HEIGHT - 2 ) )/*{{{*/
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : \' . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					char c;
					++wall[CURR].shelf;
					scanf( "%c", &c );
					wall[CURR].rack[wall[CURR].shelf] = (int) c;
				}
				break;/*}}}*/
			case '\"' :
				if( wall[CURR].shelf < 0 )/*{{{*/
				{
					printf( "\nError: \nError: Rack bottom exceeded at rack %i, \
during token #%i : \" . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					int d;
					int h;
					d = wall[CURR].rack[wall[CURR].shelf];
					printf( "%c", (char) wall[CURR].rack[wall[CURR].shelf] );
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				}
				break;/*}}}*/
			case '`' :
				if( wall[CURR].shelf < 0 )/*{{{*/
				{
					printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : ` . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					printf( "%i", (int) wall[CURR].rack[wall[CURR].shelf] );
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				}
				break;/*}}}*/
			case '\?' :
				if( wall[CURR].shelf < 0 )/*{{{*/
				{
					printf( "\nError: Rack bottom exceeded at rack %i, \
during token #%i : ` . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else if( wall[CURR].shelf > ( HEIGHT - 2 ) )
				{
					printf( "\nError: Rack top exceeded at rack %i, \
during token #%i : ? . Lapse: %i\n", CURR, STEP, LAPSE );
					EJECT = 1;
				}
				else
				{
					int j;
					int d;
					time_t t;
					srand( ( unsigned ) time( &t ) );
					do {
						d = rand() / j;
					} while( d > wall[CURR].rack[wall[CURR].shelf] );
					wall[CURR].rack[wall[CURR].shelf] = d;
				}
				break;/*}}}*/
		}
		++STEP;
		++LAPSE;
		if( LAPSE == SNAP )
		{
			output();
		}
	}
}/*}}}*/

void init( void )
{/*{{{*/
	CURR = 0;
	PREV = 0;
	LAPSE = 0;
	SNAP = -1;
	int i;
	for( i = 0; i < WIDTH; i++ )
	{
		int j;
		for( j = 0; j < HEIGHT; j++ )
		{
			wall[i].rack[j] = 0;
		}
		wall[i].shelf = -1;
	}
}/*}}}*/

void tokenize( void )
{/*{{{*/
	int i = 0;
	int j = 0;
	int leap;
	int dev = 1;
	while( RAWARR[i] != 0 )
	{
		leap = 1;
		if( RAWARR[i] == ';' )
		{
			while( RAWARR[i + dev] != '\n' )
			{
				++leap;
				++dev;
			}
			++leap;
		}
		else if( RAWARR[i] == '0' || RAWARR[i] == '1' ||
		         RAWARR[i] == '2' || RAWARR[i] == '3' ||
		         RAWARR[i] == '4' || RAWARR[i] == '5' ||
		         RAWARR[i] == '6' || RAWARR[i] == '7' ||
		         RAWARR[i] == '8' || RAWARR[i] == '9' ||
		         RAWARR[i] == 'a' || RAWARR[i] == 'b' ||
		         RAWARR[i] == 'c' || RAWARR[i] == 'd' ||
		         RAWARR[i] == 'e' || RAWARR[i] == 'f' ||
		         RAWARR[i] == '#' || RAWARR[i] == '~' ||
		         RAWARR[i] == '@' || RAWARR[i] == '+' ||
		         RAWARR[i] == '-' || RAWARR[i] == '*' ||
		         RAWARR[i] == '/' || RAWARR[i] == '%' ||
		         RAWARR[i] == '!' || RAWARR[i] == '&' ||
		         RAWARR[i] == '|' || RAWARR[i] == '^' ||
		         RAWARR[i] == '<' || RAWARR[i] == '>' ||
		         RAWARR[i] == '>' || RAWARR[i] == ':' ||
		         RAWARR[i] == '.' || RAWARR[i] == '$' ||
		         RAWARR[i] == '\\' || RAWARR[i] == '[' ||
		         RAWARR[i] == ']' || RAWARR[i] == '{' ||
		         RAWARR[i] == '}' || RAWARR[i] == '_' ||
		         RAWARR[i] == '\'' || RAWARR[i] == '\"' ||
		         RAWARR[i] == '`' || RAWARR[i] == '\?' )
		         {
			TOKARR[j] = RAWARR[i];
			++j;
		}
		i += leap;
	}
	TOKARR[j + 1] = '\0';
	if( j == 0 )
	{
		printf( "\nError: No recognizable characters.\n" );
		EJECT = 1;
	}
}/*}}}*/

void parse( FILE* file )
{/*{{{*/
	int c;
	int i = 0;
	while( ( c = fgetc( file ) ) != EOF && EJECT == 0 )
	{
		RAWARR[i] = c;
		++i;
		if( i > 0x80 && i != EOF )
		{
			printf( "\nError: The file was too long, maximum character length is 0x80\n" );
			EJECT = 1;
		}
	}
	fclose( file );
}/*}}}*/

int main( int argc, void* argv[] )
{/*{{{*/
	if( ( argc != 2 ) && ( argc !=3 ) )
	{
		printf( "\nError: Provide program file, and (optionally) three digit number to get snapshot.\nExample: %s prog 054\n", argv[0] );
		EJECT = 1;
	}
	else
	{
		if( argc == 3 )
		{
			char* snapString = argv[2];
			int k;
			int a;
			k = 0;
			a = 100;
			while( snapString[k] != '\0' )
			{
				SNAP += ( (int) snapString[k] - 48 ) * a;
				++k;
				a /= 10;
			}
		}
		FILE* file;
		file = fopen( argv[1], "r" );
		if( file == 0 )
		{
			printf( "\nError: Could not open file\n" );
			EJECT = 1;
		}
		else
		{
			parse( file );
			if( EJECT == 0 )
			{
				tokenize();
			}
			if( EJECT == 0 )
			{
				init();
				run();
			}
		}
	}
	if( EJECT == 1 )
	{
		return( 1 );
	}
	else
	{
		printf( "\n\nSuccessful exit.\nLapse: %i\n", LAPSE);
		return( 0 );
	}
}/*}}}*/
