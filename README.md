# wallRack
Simple language that consists of an array of stacks, which are manipulated
tediously with 44 single character operators.

You can use a three digit number as an option, and it will show a snapshot
(with racks cut to 16 height) of the internal values.
Usage: ./wallRack prog \#\#\#

### Structure:

#### wall
An array which you traverse with absolute notation, currently 16 indexes.
#### rack
A stack for each index of wall. Racks start at '-1', so first operation on a rack must be one that adds a shelf.
#### shelf
Racks currently consist of 128 shelfs, which hold decimal values.

| w[0] | w[1] | w[2] | w[3] | w[4] | w[5] | w[6] | w[7] | w[8] | w[9] | w[10] | w[11] | ... |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| r[0] | r[0] | r[0] | r[0] | r[0] | r[0] | r[0] | r[0] | r[0] | r[0] | r[0] | r[0] | ... |
| r[1] | r[1] | r[1] | r[1] | r[1] | r[1] | r[1] | r[1] | r[1] | r[1] | r[1] | r[1] | ... |
| r[2] | r[2] | r[2] | r[2] | r[2] | r[2] | r[2] | r[2] | r[2] | r[2] | r[2] | r[2] | ... |
| r[3] | r[3] | r[3] | r[3] | r[3] | r[3] | r[3] | r[3] | r[3] | r[3] | r[3] | r[3] | ... |
| r[4] | r[4] | r[4] | r[4] | r[4] | r[4] | r[4] | r[4] | r[4] | r[4] | r[4] | r[4] | ... |
| r[5] | r[5] | r[5] | r[5] | r[5] | r[5] | r[5] | r[5] | r[5] | r[5] | r[5] | r[5] | ... |
| r[6] | r[6] | r[6] | r[6] | r[6] | r[6] | r[6] | r[6] | r[6] | r[6] | r[6] | r[6] | ... |
| r[7] | r[7] | r[7] | r[7] | r[7] | r[7] | r[7] | r[7] | r[7] | r[7] | r[7] | r[7] | ... |
| r[8] | r[8] | r[8] | r[8] | r[8] | r[8] | r[8] | r[8] | r[8] | r[8] | r[8] | r[8] | ... |
| r[9] | r[9] | r[9] | r[9] | r[9] | r[9] | r[9] | r[9] | r[9] | r[9] | r[9] | r[9] | ... |
| . | . | . | . | . | . | . | . | . | . | . | . | ... |
| . | . | . | . | . | . | . | . | . | . | . | . | ... |
| . | . | . | . | . | . | . | . | . | . | . | . | ... |

### Operators:

Values held by shelves are decimal, but hexadecimals can be used to input values, to ease the need for multidigit instructions. Increments rack.
```
0 1 2 3 4 5 6 7 8 9 a b c d e f

  :: r[i] = O; ++i
```

Get current index of wall / previous index of wall / current index of rack. Increments rack.
```
# ~ @

  :: r[i] = O; ++i
```

Basic mathematical operators, which combine the two shelves. Decrements rack.
```
+ - * / %

  :: r[i-1] = r[i] O r[i-1]; --i
```

Logical not, returns boolean.
```
!

  :: r[i] = O r[i]
```

Logical operators for two shelves: and / or / xor. Returns boolean. Decrements rack.
```
& | ^

  :: r[i-1] = r[i] O r[i-1]; --i
```


Comparison of two shelves: equals / lesser greater /
returns boolean. Decrements rack.
```
= < >	-

  :: r[i-1] = r[i] O r[i-1]; --i
```

Duplicate shelf's contents. Increments rack.
```
:
  :: r[i+1] = r[i]; ++i
```

Clear a shelf. Decrements rack.
```
.

  :: r[i] = 0; --i
```

Move on the wall and optionally carry values from multiple shelves. If first shelf is 0, nothing is carried. Decrements the two options used by the operator from the rack, and also decrements the amount of shelves you took. Increments the rack you go to by the amount of shelves you took.
```
$

  :: r[i] : How many items down the rack you will carry;
  :: r[i-1] : To which rack you go to;
```

Reverses the order of shelves, the amount is specified with an option. Decrements rack.
```
\

  :: r[i] : How many shelves do you reorder;
```

Loop which starts if shelf is not 0, and stops if shelf is
0 when end bracket is reached.
```
[ ]
```

Ternary switch. If shelf is 0 the left side of _ operator is executed, right side will be skipped, and vice versa if shelf not 0. Decrements rack.
```
{ } _

  :: r[i] = 0; --i
```

Print shelf as ASCII. Decrements rack.
```
"
  :: OUTPUT = r[i]; r[i] = 0; --i
```

Ask for ASCII input. Increments rack.
```
'
  :: r[i] = INPUT; ++i
```

Print decimal value. Decrements rack.
```
'

  :: OUTPUT = r[i]; r[i] = 0; --i
```

Generates random number from 0 to option.
```
?
  :: r[i] = rand( 0 - r[i] );
```
