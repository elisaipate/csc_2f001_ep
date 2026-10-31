#include "shortest_path.h"
#include <iostream>
#include <vector>

using namespace std;

shortest_path_t::shortest_path_t(location_t *from, location_t *to) {
  this->head = nullptr;
  this->base = nullptr;
  this->from = from;
  this->to = to;
}

void shortest_path_t::compute() {
  head = new node_t;

  head->next = nullptr;
  head->location = from;
  head->from = nullptr;
  head->from_origin = 0;
  head->total = from->distance_to(to);
  head->visited = false;

  while (true) {
    base = nullptr;

    for (node_t *n = head; n != nullptr; n = n->next) {
      if (!n->visited && (base == nullptr || n->total < base->total)) {
        base = n;
      }
    }

    if (base == nullptr) {
      return;
    }

    if (base->location == to) {
      return;
    }

    base->visited = true;

    for (size_t i = 0; i < base->location->nb_neighbors; i++) {
      location_t *cur = base->location->neighbors[i];

      double from_origin = base->from_origin + base->location->distance_to(cur);

      double total = from_origin + cur->distance_to(to);

      node_t *n = head;

      while (n != nullptr && n->location != cur) {
        n = n->next;
      }

      if (n == nullptr) {
        n = new node_t;

        n->location = cur;
        n->from = base;
        n->from_origin = from_origin;
        n->total = total;
        n->visited = false;

        n->next = head;
        head = n;
      } else if (from_origin < n->from_origin) {
        n->from = base;
        n->from_origin = from_origin;
        n->total = total;
        n->visited = false;
      }
    }
  }
}

void shortest_path_t::display() {
  if (base == nullptr || base->location != to) {
    cout << "unable to find a path from " << from->name << " to " << to->name
         << endl;
    return;
  }

  cout << "path from " << from->name << " to " << to->name << endl;

  vector<node_t *> path;

  for (node_t *n = base; n != nullptr; n = n->from) {
    path.push_back(n);
  }

  for (size_t i = path.size(); i > 0; i--) {
    node_t *n = path[i - 1];

    cout << "  * " << n->location->name << " at " << n->from_origin
         << " km from " << from->name << endl;
  }
}

shortest_path_t::~shortest_path_t() {
  node_t *n = head;

  while (n != nullptr) {
    node_t *next = n->next;
    delete n;
    n = next;
  }
}
