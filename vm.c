#include "vm.h"
#include <stdlib.h>
#include <string.h>

int tm_init(TM *t, char init, char blank, const char * const tape, int pos) {
  int sz = strlen(tape) + 1; // Add back NUL
  t->tape = malloc(sz * sizeof(char));
  if (!tape) { return 0; }
  memcpy(t->tape, tape, sz);
  t->init = init;
  t->blank = blank;
  t->tape_sz = sz;
  t->tape_pos = pos;
  return 1;
}

static inline int realloc_tape(TM *t) {
  char *newtape = realloc(t->tape, 2 * t->tape_sz * sizeof(char));
  if (!newtape) { return 0; }
  t->tape_sz *= 2;
  t->tape = newtape;
  return 1;
}

static inline int tape_write_left(TM *t) {
  if (t->tape_pos <= 0) {
    // Make sure to test this! Pencil and paper!
    if (!realloc_tape(t)) { return 0; }
    int off = t->tape_sz / 2;
    memcpy(t->tape + off*sizeof(char), t->tape, off);
    t->tape_pos += off;
    // Bottom half of tape is garbage
    bzero(t->tape, off);
  } 
  t->tape_pos--;
  t->tape[t->tape_pos] = t->blank;
  return 1;
}

static inline int tape_write_right(TM *t) {
  if (t->tape_pos + 2 >= t->tape_sz) { // leave space for NULL
    if (!realloc_tape(t)) { return 0; }
    // Top half of tape is garbage
    int off = t->tape_sz / 2;
    bzero(t->tape + off*sizeof(char), off);
  }
  t->tape_pos++;
  t->tape[t->tape_pos] = t->blank;
  return 1;
}

int tape_write(TM *t, char w) {
  switch (w) {
    case 'L': return tape_write_left(t);
    case 'R': return tape_write_right(t);
    default:
              t->tape[t->tape_pos] = w;
              return 1;
  }
}

// Returns the pointer to the first non-NULL (nonblank) tape symbol.
// Can treat return as NULL-terminated string.
const char * tape_str(TM *t) {
  char *p = t->tape;
  while (!*p) {
    p++;
  }
  return p;
}

inline void tm_add_transition(TM *t, char start, char sym, char newsym, char endstate) {
  t->code[start][2*sym]     = newsym;
  t->code[start][2*sym + 1] = endstate;
}

void tm_run(TM *t) {
  char state = t->init, sym, newsym; 

  sym = t->tape[t->tape_pos];
  while (newsym = t->code[state][2*sym]) {
    tape_write(t, newsym);
#ifdef DEBUG
    puts(tape_str(t));
#endif
    state = t->code[state][2*sym + 1];
    sym = t->tape[t->tape_pos];
  }
}

