// Returns 0 on success, nonzero for failure.
// file format:
// tapelen tape_start_pos
// tttttaaaaaaaaaaappppppppeeeeeeeeeee
// init_state
// abcd
// abcd
// ...
#ifndef _PARSER_H
#define _PARSER_H
#include <stdio.h>
#include "vm.h"
int tm_parse(TM *t, FILE *f);
#endif

