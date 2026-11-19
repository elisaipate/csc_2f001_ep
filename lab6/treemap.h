#include <iostream>

using namespace std;

template <class K, class V> struct treemap_t {
  struct pair_t {
    K key;
    V value;
  };
  struct node_t : pair_t {
    node_t *parent, *left, *right;
    node_t(node_t *p) {
      parent = p;
      left = right = nullptr;
    };
  };
  node_t *root;
  treemap_t() { root = nullptr; };
  node_t *lookup(node_t **pcur, node_t *parent, const K *key, bool create) {
    node_t *cur = *pcur;

    if (cur == nullptr) {
      if (!create)
        return nullptr;

      *pcur = new node_t{parent};
      (*pcur)->key = *key;
      cur = *pcur;
    }

    if (cur->key == *key)
      return cur;
    else if (*key > cur->key)
      return lookup(&cur->right, cur, key, create);
    else
      return lookup(&cur->left, cur, key, create);
  }
  void set_at(const K key, const V value) {
    node_t *cur = lookup(&root, nullptr, &key, true);
    cur->value = value;
  }

  V at(const K key) {
    node_t *cur = lookup(&root, nullptr, &key, false);

    if (cur == nullptr) {
      cout << "key does not exist" << endl;
      exit(EXIT_FAILURE);
    }

    return cur->value;
  }
};
