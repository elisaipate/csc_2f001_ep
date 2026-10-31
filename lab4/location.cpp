#include "location.h"
#include <cmath>
#include <numbers>

using namespace std;

const int R = 6378;

location_t::location_t(string name, double latitude, double longitude) {
  this->name = name;
  this->latitude = latitude;
  this->longitude = longitude;
  this->neighbors = nullptr;
  this->nb_neighbors = 0;
}

void location_t::set_neighbors(location_t *list[]) {
  this->neighbors = list;

  int i = 0;
  while (list[i] != nullptr) {
    i++;
  }

  this->nb_neighbors = i;
}

location_t::~location_t() { delete[] neighbors; }

double location_t::distance_to(location_t *to) {
  double lat1 = this->latitude;
  double lat2 = to->latitude;
  double long1 = this->longitude;
  double long2 = to->longitude;

  return R *
         (numbers::pi / 2 - asin(sin(lat2) * sin(lat1) +
                                 cos(long2 - long1) * cos(lat2) * cos(lat1)));
}
