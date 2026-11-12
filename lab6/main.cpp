#include "treemap.h"
#include <iostream>
using namespace std;

int main() {
  treemap_t<string, double>::pair_t pair{"Tyrion", 2.0};
  cout << pair.key << ": " << pair.value << "€" << endl;
  treemap_t<std::string, double> map;
  std::string name;

  name = "Tyrion";
  map.lookup(&map.root, nullptr, &name, true);
  name = "Jaime";
  map.lookup(&map.root, nullptr, &name, true);
  name = "Cersei";
  map.lookup(&map.root, nullptr, &name, true);
  return 0;
}
