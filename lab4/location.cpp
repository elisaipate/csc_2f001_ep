#include "location.h"

using namespace std;

location_t::location_t(string name, double latitude, double longitude) {
  this->name = name;
  this->latitude = latitude;
  this->longitude = longitude;
  this->neighbors = nullptr;
  this->nb_neighbors = 0;
}

void location_t::set_neighbors(location_t *list[]) {
  this->neighbors = list[0];
  int i = 0;
  while (list[i] != nullptr)
    i++;
  this->nb_neighbors = i;
}
