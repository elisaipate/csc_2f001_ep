#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

void error(string str) __attribute__((noreturn));

void error(string str) {
  cout << "Error: " << str << endl;
  exit(1);
}

struct list_t;

struct node_t {
  virtual node_t *eval() { return this; }

  virtual node_t *apply(list_t *list) { error("Cannot apply this node"); }

  virtual string to_string() { return "???"; }

  virtual list_t *as_list() { error("This node is not a list"); }
};

struct integer_t : node_t {
  uintptr_t value;

  integer_t(uintptr_t v) { value = v; }

  string to_string() override { return std::to_string(value); }
};

struct list_t : node_t {
  node_t **elements;
  size_t nb_elements;
  size_t capacity;

  list_t() {
    capacity = 0;
    nb_elements = 0;
    elements = nullptr;
  }

  list_t *as_list() override { return this; }

  size_t size() { return nb_elements; }

  node_t *at(size_t i) {
    if (i >= nb_elements)
      error("i is out of bounds");

    return elements[i];
  }

  void set_at(size_t i, node_t *value) {
    if (i >= nb_elements)
      error("i is out of bounds");

    elements[i] = value;
  }

  void append(node_t *value) {
    if (nb_elements == capacity) {
      size_t new_capacity = 2 * capacity + 1;

      node_t **new_pointer = new node_t *[new_capacity];

      for (size_t i = 0; i < nb_elements; i++) {
        new_pointer[i] = elements[i];
      }

      delete[] elements;

      elements = new_pointer;
      capacity = new_capacity;
    }

    elements[nb_elements] = value;
    nb_elements++;
  }

  string to_string() override {
    string result = "(";

    for (size_t i = 0; i < nb_elements; i++) {
      if (i > 0)
        result += " ";

      result += elements[i]->to_string();
    }

    result += ")";
    return result;
  }
};

int main() {
  list_t *ast = new list_t;

  ast->append(new integer_t{1});
  ast->append(new integer_t{2});
  ast->append(new integer_t{3});

  cout << ast->to_string() << endl;

  return 0;
}
