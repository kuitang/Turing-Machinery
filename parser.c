#include <stdio.h>
#include <stdlib.h>
#include "vm.h"
#include "parser.h"

int tm_parse(TM *t, FILE *f) {
  int n;
  int tapelen, tape_pos;
  char init, blank, start, sym, newsym, endstate;
  n = fscanf(f, "%d %d\n", &tapelen, &tape_pos);
  if (n != 2)                            { return 1; }

#ifdef DEBUG
  fprintf(stderr, "tapelen = %d; tape_pos = %d\n", tapelen, tape_pos);
#endif
  char *tape = malloc((tapelen + 1) * sizeof(char));
  if (!tape)                             { return 2; }
  if (!fgets(tape, tapelen + 1, f))      { return 3; }
  fgetc(f); // Swallows the newline

  n = fscanf(f, "%c %c\n", &init, &blank);
  if (n != 2)                            { return 4; }
  //fgetc(f); // swallow the newline
#ifdef DEBUG
  fprintf(stderr, "tape = %s\n", tape);
  fprintf(stderr, "init = %c\n", init);
#endif
  if (!tm_init(t, init, blank, tape, tape_pos)) { return 5; }

  while (fscanf(f, "%c%c%c%c\n", &start, &sym, &newsym, &endstate) != EOF) {
    tm_add_transition(t, start, sym, newsym, endstate);
#ifdef DEBUG
    fprintf(stderr, "Added %c%c%c%c\n", start, sym, newsym, endstate);
#endif
  }

  return 0;
}
