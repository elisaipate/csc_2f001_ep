#include "army.h"
#include "monster.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  char name[NAME_SIZE];
  struct monster *monsters[10];
  struct army *a = create_army();

  if (a == NULL)
    return 1;

  for (int i = 0; i < 10; i++) {
    snprintf(name, sizeof(name), "Pikachu-%d", i);
    monsters[i] = create_monster(name, 1);
    if (monsters[i] == NULL) {
      for (int j = 0; j < i; j++)
        delete_monster(monsters[j]);
      delete_army(a);
      return 1;
    }
    add_monster_to_army(a, monsters[i]);
  }

  display_army(a);

  delete_army(a);

  for (int i = 0; i < 10; i++)
    delete_monster(monsters[i]);

  return 0;
}
