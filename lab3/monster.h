#ifndef MONSTER_H
#define MONSTER_H
struct monster {
  char *name;
  int hp;
};

struct monster *create_monster(char *name, int hp);
void display_monster(struct monster *m);
void delete_monster(struct monster *m);
#endif
