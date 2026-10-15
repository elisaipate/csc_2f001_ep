#include "monster.h"
#include <stdio.h>
#include <stdlib.h>
struct monster *create_monster(char *name, int hp) {
  struct monster *m = malloc(sizeof(struct monster));
  m->name = name;
  m->hp = hp;
  return m;
};

void display_monster(struct monster *m) {
  printf("monster's name: %s, monnster's hp: %d\n", m->name, m->hp);
};

void delete_monster(struct monster *m) { free(m); };
