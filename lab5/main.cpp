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
struct frame_t;

struct node_t {
  virtual node_t *eval(frame_t *frame) { return this; }

  virtual node_t *apply(list_t *, frame_t *) {
    error("Cannot apply this node");
  }

  virtual string to_string() { return "???"; }

  virtual list_t *as_list() { error("This node is not a list"); }

  virtual uintptr_t int_value() { error("This node is not an integer"); }

  virtual bool is(string id) { return false; }
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

  node_t *eval(frame_t *frame) {
    if (nb_elements == 0)
      error("Cannot evaluate an empty list");
    node_t *operation = at(0)->eval(frame);
    return operation->apply(this, frame);
  }
};

struct keyword_t : node_t {
  string id;
  keyword_t(string s) { id = s; }
  string to_string() { return "<" + id + ">"; }
};

struct add_t : keyword_t {
  add_t() : keyword_t("+") {}
  node_t *apply(list_t *list, frame_t *frame) {
    uintptr_t sum = 0;
    for (size_t i = 1; i < list->size(); i++)
      sum += list->at(i)->eval(frame)->int_value();
    return new integer_t{sum};
  }
};

struct symbol_t : node_t {
  string id;
  symbol_t(string s) { id = s; }
  bool is(string s) { return id == s; }
  string to_string() { return id; }
  node_t *eval(frame_t *frame);
};

struct frame_t : list_t {
  void set(node_t *sym, node_t *value) {
    for (size_t i = 0; i < size(); i++) {
      list_t *pair = at(i)->as_list();
      if (sym->is(pair->at(0)->to_string())) {
        pair->set_at(1, value);
        return;
      }
    }

    list_t *pair = new list_t;
    pair->append(sym);
    pair->append(value);
    append(pair);
  }

  node_t *get(node_t *sym) {
    for (size_t i = 0; i < size(); i++) {
      list_t *pair = at(i)->as_list();
      if (sym->is(pair->at(0)->to_string()))
        return pair->at(1);
    }
    error("symbol not found: " + sym->to_string());
  }
};

struct set_t : keyword_t {
  set_t() : keyword_t("set!") {}

  node_t *apply(list_t *list, frame_t *frame) {
    if (list->size() != 3)
      error("error at list size of set!");

    node_t *sym = list->at(1);
    node_t *value = list->at(2)->eval(frame);

    frame->set(sym, value);

    return value;
  }
};
node_t *symbol_t::eval(frame_t *frame) { return frame->get(this); }

int main() {

  node_t *add = new add_t;
  node_t *set = new set_t;
  symbol_t *x = new symbol_t{"x"};
  frame_t *frame = new frame_t;

  list_t *ast = new list_t;
  ast->append(set);
  ast->append(x);
  ast->append(new integer_t{42});

  cout << ast->to_string() << " => " << ast->eval(frame)->to_string() << endl;
  cout << "x = " << frame->get(x)->to_string() << endl;

  return 0;
}
