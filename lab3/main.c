#include "monster.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  char name[] = "Pikachu";
  struct monster *monsters[10];
  for (int i = 0; i < 10; i++)
    monsters[i] = create_monster(name, 1);
  for (int i = 0; i < 10; i++)
    display_monster(monsters[i]);
  for (int i = 0; i < 10; i++)
    delete_monster(monsters[i]);
  return 0;
}
