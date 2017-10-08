#include <stdio.h>

int EJECT = 0;
const int WIDTH = 16;
const int HEIGHT = 128;
char RAWARR[128];
char TOKARR[128];
int CURR;
int PREV;
int OPEN;
int LAPSE;
int SNAP;
typedef struct sWall WALL;
struct sWall
{
	int rack[128];
	int loop;
	int shelf;
	int prev;
};
WALL wall[16];

void output( char token )
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
			printf( "\ncurr: %i, prev: %i, token: %c, open: %i, lapse: %i\n", CURR, PREV, token, OPEN, LAPSE );
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
	printf( "\n" );
}/*}}}*/

void run( void )
{/*{{{*/
	int step = 0;
	if( LAPSE == SNAP )
	{
		output( TOKARR[step] );
	}
	char token;
	while( ( TOKARR[step] != '\0' ) && ( EJECT == 0 ) )
	{
		token = TOKARR[step];
		switch( token )
		{
			case '0' :
				if( wall[CURR].shelf == HEIGHT )/*{{{*/
				{
					printf( "Rack top exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 0;
				}
				break;/*}}}*/
			case '1' :
				if( wall[CURR].shelf == HEIGHT )/*{{{*/
				{
					printf( "Rack top exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 1;
				}
				break;/*}}}*/
			case '2' :
				if( wall[CURR].shelf == HEIGHT )/*{{{*/
				{
					printf( "Rack top exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 2;
				}
				break;/*}}}*/
			case '3' :
				if( wall[CURR].shelf == HEIGHT )/*{{{*/
				{
					printf( "Rack top exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 3;
				}
				break;/*}}}*/
			case '4' :
				if( wall[CURR].shelf == HEIGHT )/*{{{*/
				{
					printf( "Rack top exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 4;
				}
				break;/*}}}*/
			case '5' :
				if( wall[CURR].shelf == HEIGHT )/*{{{*/
				{
					printf( "Rack top exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 5;
				}
				break;/*}}}*/
			case '6' :
				if( wall[CURR].shelf == HEIGHT )/*{{{*/
				{
					printf( "Rack top exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 6;
				}
				break;/*}}}*/
			case '7' :
				if( wall[CURR].shelf == HEIGHT )/*{{{*/
				{
					printf( "Rack top exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 7;
				}
				break;/*}}}*/
			case '8' :
				if( wall[CURR].shelf == HEIGHT )/*{{{*/
				{
					printf( "Rack top exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 8;
				}
				break;/*}}}*/
			case '9' :
				if( wall[CURR].shelf == HEIGHT )/*{{{*/
				{
					printf( "Rack top exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 9;
				}
				break;/*}}}*/
			case 'a' :
				if( wall[CURR].shelf == HEIGHT )/*{{{*/
				{
					printf( "Rack top exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 10;
				}
				break;/*}}}*/
			case 'b' :
				if( wall[CURR].shelf == HEIGHT )/*{{{*/
				{
					printf( "Rack top exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 11;
				}
				break;/*}}}*/
			case 'c' :
				if( wall[CURR].shelf == HEIGHT )/*{{{*/
				{
					printf( "Rack top exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 12;
				}
				break;/*}}}*/
			case 'd' :
				if( wall[CURR].shelf == HEIGHT )/*{{{*/
				{
					printf( "Rack top exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 13;
				}
				break;/*}}}*/
			case 'e' :
				if( wall[CURR].shelf == HEIGHT )/*{{{*/
				{
					printf( "Rack top exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 14;
				}
				break;/*}}}*/
			case 'f' :
				if( wall[CURR].shelf == HEIGHT )/*{{{*/
				{
					printf( "Rack top exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else
				{
					++wall[CURR].shelf;
					wall[CURR].rack[wall[CURR].shelf] = 15;
				}
				break;/*}}}*/
			case '+' :
				if( wall[CURR].shelf == 0 )/*{{{*/
				{
					printf( "Rack bottom exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
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
				if( wall[CURR].shelf == 0 )/*{{{*/
				{
					printf( "Rack bottom exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
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
				if( wall[CURR].shelf == 0 )/*{{{*/
				{
					printf( "Rack bottom exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
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
				if( wall[CURR].shelf == 0 )/*{{{*/
				{
					printf( "Rack bottom exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
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
				if( wall[CURR].shelf == 0 )/*{{{*/
				{
					printf( "Rack bottom exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
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
				if( wall[CURR].shelf == 0 )/*{{{*/
				{
					printf( "Rack bottom exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
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
				if( wall[CURR].shelf == 1 )/*{{{*/
				{
					printf( "Rack bottom exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else if( wall[CURR].rack[wall[CURR].shelf] &&
				wall[CURR].rack[wall[CURR].shelf - 1 ] )
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 1;
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				}
				else
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 0;
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				}
				break;/*}}}*/
			case '|' :
				if( wall[CURR].shelf == 1 )/*{{{*/
				{
					printf( "Rack bottom exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else if( wall[CURR].rack[wall[CURR].shelf] ||
				wall[CURR].rack[wall[CURR].shelf - 1 ] )
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 1;
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				}
				else
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 0;
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				}
				break;/*}}}*/
			case '^' :
				if( wall[CURR].shelf == 1 )/*{{{*/
				{
					printf( "Rack bottom exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else if( ( wall[CURR].rack[wall[CURR].shelf] &&
				wall[CURR].rack[wall[CURR].shelf - 1 ] ) ||
				!( wall[CURR].rack[wall[CURR].shelf] ||
				wall[CURR].rack[wall[CURR].shelf - 1 ] ) )
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 1;
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				}
				else
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 0;
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				}
				break;/*}}}*/
			case '<' :
				if( wall[CURR].shelf == 1 )/*{{{*/
				{
					printf( "Rack bottom exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else if( wall[CURR].rack[wall[CURR].shelf] <
				wall[CURR].rack[wall[CURR].shelf - 1 ] )
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 1;
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				}
				else
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 0;
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				}
				break;/*}}}*/
			case '>' :
				if( wall[CURR].shelf == 1 )/*{{{*/
				{
					printf( "Rack bottom exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else if( wall[CURR].rack[wall[CURR].shelf] >
				wall[CURR].rack[wall[CURR].shelf - 1 ] )
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 1;
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				}
				else
				{
					wall[CURR].rack[wall[CURR].shelf - 1] = 0;
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				}
				break;/*}}}*/
			case ':' :
				if( wall[CURR].shelf == -1 )/*{{{*/
				{
					printf( "Rack bottom exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				if( wall[CURR].shelf == HEIGHT )
				{
					printf( "Rack top exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
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
				if( wall[CURR].shelf == -1 )/*{{{*/
				{
					printf( "Rack bottom exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
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
					printf( "Negative number used for collecting moved values at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else if( wall[CURR].rack[wall[CURR].shelf] == 0 )
				{
					if( wall[CURR].shelf < 1 )
					{
						printf( "Rack bottom exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
						EJECT = 1;
					}
					else if( ( wall[CURR].rack[wall[CURR].shelf - 1] < 0 ) ||
                                                 ( wall[CURR].rack[wall[CURR].shelf - 1] > WIDTH ) )
					{
						printf( "Values were attempted to be moved to non-existent rack %i at rack %i, \
during token #%i : %c. Lapse: %i\n", wall[CURR].rack[wall[CURR].shelf - 1], CURR, step, token, LAPSE );
						EJECT = 1;
					}
					else
					{
						wall[CURR].rack[wall[CURR].shelf] = 0;
						wall[CURR].rack[wall[CURR].shelf - 1] = 0;
						PREV = CURR;
						CURR = wall[CURR].rack[wall[CURR].shelf - 1];
						wall[PREV].shelf -= 2;
					}
				}
				else
				{
					if( wall[CURR].shelf < wall[CURR].rack[wall[CURR].shelf] )
					{
						printf( "Rack bottom exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
						EJECT = 1;
					}
					else if( ( wall[CURR].rack[wall[CURR].shelf - 1] < 0 ) ||
                                                 ( wall[CURR].rack[wall[CURR].shelf - 1] > WIDTH ) )
					{
						printf( "Values were attempted to be moved to non-existent rack %i at rack %i, \
during token #%i : %c. Lapse: %i\n", wall[CURR].rack[wall[CURR].shelf - 1], CURR, step, token, LAPSE );
						EJECT = 1;
					}
					else if( ( wall[wall[CURR].rack[wall[CURR].shelf -1]].shelf +
                                                   wall[CURR].rack[wall[CURR].shelf] ) > HEIGHT )
					{
						printf( "Rack top exceeded in destination rack %i at rack %i, \
during token #%i : %c. Lapse: %i\n", wall[CURR].rack[wall[CURR].shelf - 1], CURR, step, token, LAPSE );
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
			case '#' :
				if( wall[CURR].shelf < wall[CURR].rack[wall[CURR].shelf] )/*{{{*/
				{
					printf( "Rack bottom exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
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
				if( wall[CURR].rack[wall[CURR].shelf] == 0 )/*{{{*/
				{
					++OPEN;
					int b;
					int bt;
					b = step;
					bt = TOKARR[step];
					++step;
					while( TOKARR[step] != ']' && OPEN > 0 )
					{
						if( step > 128 )
						{
							printf( "Loop end was not found at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, b, bt, LAPSE );
							EJECT = 1;
						}
						else
						{
							if( TOKARR[step] == '[' )
							{
								++OPEN;
							}
							else if( TOKARR[step] == ']' && OPEN == 1 )
							{
								--OPEN;
							}
							++step;
						}
					}
				}
				break;/*}}}*/
			case ']' :
				if( wall[CURR].rack[wall[CURR].shelf] != 0 )/*{{{*/
				{
					int b;
					int bt;
					++OPEN;
					b = step;
					bt = TOKARR[step];
					--step;
					while( TOKARR[step] != '[' && OPEN > 0 )
					{
						if( step < 0 )
						{
							printf( "Loop start was not found at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, b, bt, LAPSE );
							EJECT = 1;
						}
						else
						{
							if( TOKARR[step] == ']' )
							{
								++OPEN;
							}
							else if( TOKARR[step] == '[' && OPEN == 1 )
							{
								--OPEN;
							}
							--step;
						}
					}
				}
				break;/*}}}*/
			case '\"' :
				if( wall[CURR].shelf == -1 )/*{{{*/
				{
					printf( "Rack bottom exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else
				{
					printf( "%c", (char) wall[CURR].rack[wall[CURR].shelf] );
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				}
				break;/*}}}*/
			case '\'' :
				if( wall[CURR].shelf == HEIGHT )/*{{{*/
				{
					printf( "Rack top exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
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
			case '`' :
				if( wall[CURR].shelf == -1 )/*{{{*/
				{
					printf( "Rack bottom exceeded at rack %i, \
during token #%i : %c. Lapse: %i\n", CURR, step, token, LAPSE );
					EJECT = 1;
				}
				else
				{
					printf( "%i", (int) wall[CURR].rack[wall[CURR].shelf] );
					wall[CURR].rack[wall[CURR].shelf] = 0;
					--wall[CURR].shelf;
				}
				break;/*}}}*/
		}
		++step;
		++LAPSE;
		if( LAPSE == SNAP )
		{
			output( TOKARR[step] );
		}
	}
	if( LAPSE == SNAP )
	{
		output( TOKARR[step] );
	}
}/*}}}*/

void init( void )
{/*{{{*/
	CURR = 0;
	PREV = 0;
	OPEN = 0;
	LAPSE = 0;
	int i;
	for( i = 0; i < WIDTH; i++ )
	{
		int j;
		for( j = 0; j < HEIGHT; j++ )
		{
			wall[i].rack[j] = 0;
		}
		wall[i].loop = 0;
		wall[i].shelf = -1;
		wall[i].prev = 0;
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
		if( RAWARR[i] == '\?' )
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
		         RAWARR[i] == '+' || RAWARR[i] == '-' ||
		         RAWARR[i] == '*' || RAWARR[i] == '/' ||
		         RAWARR[i] == '%' || RAWARR[i] == '!' ||
		         RAWARR[i] == '&' || RAWARR[i] == '|' ||
		         RAWARR[i] == '^' || RAWARR[i] == '<' ||
		         RAWARR[i] == '>' || RAWARR[i] == ':' ||
		         RAWARR[i] == '.' || RAWARR[i] == '$' ||
		         RAWARR[i] == '#' || RAWARR[i] == '[' ||
		         RAWARR[i] == ']' || RAWARR[i] == '\'' ||
		         RAWARR[i] == '\"' || RAWARR[i] == '`' )
		{
			TOKARR[j] = RAWARR[i];
			++j;
		}
		i += leap;
	}
	TOKARR[j + 1] = '\0';
	if( j == 0 )
	{
		printf( "No recognizable characters.\n" );
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
		if( i > 128 && i != EOF )
		{
			printf( "The file was too long, maximum token amount is 128\n" );
			EJECT = 1;
		}
	}
	fclose( file );
}/*}}}*/

int main( int argc, void* argv[] )
{/*{{{*/
	if( ( argc != 2 ) && ( argc !=3 ) )
	{
		printf( "Provide program file, and (optionally) three digit number to get snapshot.\nExample: %s prog 054\n", argv[0] );
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
			printf( "Could not open file\n" );
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
	printf( "\nLapse: %i\n", LAPSE);
	if( EJECT == 1 )
	{
		return( 1 );
	}
	else
	{
		return( 0 );
	}
}/*}}}*/
