A bytecode interpreter for a bidirectional, infinite-length-tape Turing machine.

My definition of the Turing machine is based on Martin Davis, _Computability and Unsolvability_, Dover, 1982 (originally McGraw Hill, 1958), page 5.

Define a Turing machine in an input file as follows:
-   Line 1: two integers, separated by space: initial length of tape, index of tape's start position (0-based)
-   Line 2: a string: initial contents of tape.
-   Line 3: two characters, separated by space: initial state of the machine, "blank" symbol (used to fill new squares on the tape)
-   Lines 3 to n: a four character quadruple _pabq_. When the machine is in state _p_ and the tape is over the square with character _a_, then the machine will write character _b_ and switch to state _q_.
    -   The special characters L and R move the tape reader left or right by one square and do not write anything.

Note that all states and tape symbols are limited to one character. However, they live in separate "namespaces:" you can have a state 2 and a tape symbol 2 with no relation to each other.

Example Turing Machine that does not halt (from page 5 of Davis):

    4 1
    2052
    1 0
    10R1
    12R1
    15R1
    1352
    25L3
    3053
    3253
    3353

If we save this as tm.txt, we can run

    ./tm tm.txt
    Begin: 2052
    2002
    2000
    20000
    200000
    2000000

And so forth.
