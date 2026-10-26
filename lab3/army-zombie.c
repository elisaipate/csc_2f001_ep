#include "army.h"
#include <stdio.h>
#include <stdlib.h>

struct node {
  struct monster *monster;
  struct node *next;
};

struct army {
  struct node *head;
  struct node *tail;
  int stars;
};

struct army *create_army(void) {
  struct army *a = malloc(sizeof(struct army));

  if (a == NULL)
    return NULL;

  a->head = NULL;
  a->tail = NULL;
  a->stars = 0;

  return a;
}

void add_monster_to_army(struct army *a, struct monster *m) {
  if (a == NULL || m == NULL)
    return;

  struct node *n = malloc(sizeof(struct node));

  if (n == NULL)
    return;

  n->monster = m;
  n->next = NULL;

  if (a->head == NULL) {
    a->head = n;
    a->tail = n;
  } else {
    a->tail->next = n;
    a->tail = n;
  }
}

void display_army(struct army *a) {
  if (a == NULL)
    return;

  printf("This is a %d stars army\n", a->stars);

  struct node *n = a->head;

  while (n != NULL) {
    display_monster(n->monster);
    n = n->next;
  }
}

void delete_army(struct army *a) {
  if (a == NULL)
    return;

  struct node *n = a->head;

  while (n != NULL) {
    struct node *next = n->next;
    free(n);
    n = next;
  }

  free(a);
}
