#include "monster.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  char name[] = "Pikachu";
  struct monster *pikachu = create_monster(name, 1);
  display_monster(pikachu);
  delete_monster(pikachu);
  return 0;
}
