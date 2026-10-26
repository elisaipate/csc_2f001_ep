#include "monster.h"
#include <stdio.h>
#include <stdlib.h>

struct monster *create_monster(char *name, int hp) {
  struct monster *m = malloc(sizeof(struct monster));
  if (m == NULL) {
    return NULL;
  }

  snprintf(m->name, sizeof(m->name), "%s", name);
  m->hp = hp;
  return m;
}

void display_monster(struct monster *m) {
  printf("monster's name: %s, monster's hp: %d\n", m->name, m->hp);
}

void delete_monster(struct monster *m) { free(m); }
