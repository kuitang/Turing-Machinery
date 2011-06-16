#ifndef _TM_H
#define _TM_H
#define TAPE_INITSZ 2

typedef struct {
  char code[256][512];
  char *tape;
  char init;
  char blank;
  int tape_pos;
  int tape_sz;
} TM;

// Returns 1 on success, 0 on failure
// tape is null-terminated string.
int tm_init(TM *t, char init, char blank, const char * const tape, int pos);
int tape_write(TM *t, char w);
// Returns the pointer to the first non-NULL (nonblank) tape symbol.
// Can treat return as NULL-terminated string.
const char * tape_str(TM *t);
// Careful! Double evaluation of T!
#define TAPE_READ(T) ( (T).tape[(T).tape_pos] )

inline void tm_add_transition(TM *t, char start, char sym, char newsym, char endstate);
void tm_run(TM *t);
#endif
