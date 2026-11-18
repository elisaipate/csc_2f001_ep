#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

void error(string str) __attribute__((noreturn));

void error(string str) {
  cout << "Error: " << str << std::endl;
  exit(1);
}

struct list_t;

struct node_t {
  virtual node_t *eval() { return this; }

  virtual node_t *apply(list_t *) { error("Cannot apply this node"); }

  virtual string to_string() { return "???"; }

  virtual list_t *as_list() { error("This node is not a list"); }

  virtual uintptr_t int_value() { error("This node is not an integer"); }
};

struct integer_t : node_t {
  uintptr_t value;

  integer_t(uintptr_t v) { value = v; }

  string to_string() { return std::to_string(value); }

  uintptr_t int_value() { return value; }
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

  list_t *as_list() { return this; }

  size_t size() { return nb_elements; }

  node_t *at(size_t i) {
    if (i >= nb_elements)
      error("i is out of bounds");
    return *(elements + i);
  }

  void set_at(size_t i, node_t *value) {
    if (i >= nb_elements)
      error("i is out of bounds");
    *(elements + i) = value;
  }

  void append(node_t *value) {
    if (nb_elements == capacity) {
      size_t new_capacity = 2 * capacity + 1;
      node_t **new_pointer = new node_t *[new_capacity];

      for (size_t i = 0; i < nb_elements; i++)
        *(new_pointer + i) = *(elements + i);

      delete[] elements;
      elements = new_pointer;
      capacity = new_capacity;
    }

    *(elements + nb_elements) = value;
    nb_elements++;
  }

  string to_string() {
    string result = "(";

    for (size_t i = 0; i < nb_elements; i++) {
      if (i > 0)
        result += " ";
      result += at(i)->to_string();
    }

    result += ")";
    return result;
  }

  node_t *eval() {
    if (nb_elements == 0)
      error("Cannot evaluate an empty list");

    node_t *operation = at(0)->eval();
    return operation->apply(this);
  }
};

struct keyword_t : node_t {
  string id;

  keyword_t(string s) { id = s; }

  string to_string() { return "<" + id + ">"; }
};

struct add_t : keyword_t {
  add_t() : keyword_t("+") {}

  node_t *apply(list_t *list) {
    uintptr_t sum = 0;

    for (size_t i = 1; i < list->size(); i++)
      sum += list->at(i)->eval()->int_value();

    return new integer_t{sum};
  }
};

int main() {
  node_t *add = new add_t;
  list_t *ast = new list_t;

  ast->append(add);
  ast->append(new list_t);
  ast->at(1)->as_list()->append(add);
  ast->at(1)->as_list()->append(new integer_t{1});
  ast->at(1)->as_list()->append(new integer_t{2});
  ast->append(new integer_t{3});

  cout << ast->to_string() << " => " << ast->eval()->to_string() << endl;

  return 0;
}
