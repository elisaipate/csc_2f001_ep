#include "army.h"
#include <stdio.h>
#include <stdlib.h>

struct army *create_army(void) {
  struct army *a = malloc(sizeof(struct army));

  if (a == NULL) {
    return NULL;
  }

  a->monsters = NULL;
  a->top = -1;
  a->capacity = 0;

  return a;
}

void add_monster_to_army(struct army *a, struct monster *m) {
  if (a == NULL || m == NULL) {
    return;
  }

  // Expand the array when it is full
  if (a->top + 1 == a->capacity) {
    int new_capacity;

    if (a->capacity == 0) {
      new_capacity = 1;
    } else {
      new_capacity = a->capacity * 2;
    }

    struct monster **new_monsters =
        realloc(a->monsters, new_capacity * sizeof(struct monster *));

    if (new_monsters == NULL) {
      return;
    }

    a->monsters = new_monsters;
    a->capacity = new_capacity;
  }

  a->top++;
  a->monsters[a->top] = m;
}

void display_army(struct army *a) {
  if (a == NULL) {
    return;
  }

  for (int i = 0; i <= a->top; i++) {
    display_monster(a->monsters[i]);
  }
}

void delete_army(struct army *a) {
  if (a == NULL) {
    return;
  }

  free(a->monsters);
  free(a);
}
