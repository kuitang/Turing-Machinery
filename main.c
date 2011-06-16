#include <stdio.h>
#include <stdlib.h>
#include "vm.h"
#include "parser.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s file\n", argv[0]);
    return 2;
  }

  TM t;

  FILE *f = fopen(argv[1], "r");
  if (!f)                            { return 2; }
  int ret;
  if ((ret = tm_parse(&t, f)))      { return 100 + ret; }

  printf("Begin: %s\n", tape_str(&t));
  tm_run(&t);
  printf("End:   %s\n", tape_str(&t));
  return 0;
}

