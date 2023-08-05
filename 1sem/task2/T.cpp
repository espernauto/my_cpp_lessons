#include <iostream>
#include <algorithm>
#include <cstring>

struct NodeTree {
  int val;
  NodeTree *left = nullptr, *right = nullptr, *prev = nullptr;
};

void Push(int a, NodeTree **t, NodeTree *prev) {
  if ((*t) == nullptr) {
    (*t) = new NodeTree;
    (*t)->val = a;
    (*t)->left = (*t)->right = nullptr;
    (*t)->prev = prev;
    return;
  }
  NodeTree *cur = *t;
  if (a > (*t)->val) {
    Push(a, &(*t)->right, cur);
  } else {
    Push(a, &(*t)->left, cur);
  }
}

void Free(NodeTree *&root) {
  if (root->left) {
    Free(root->left);
  }
  if (root->right) {
    Free(root->right);
  }
  delete root;
  root = nullptr;
}

void Walk(NodeTree *root) {
  NodeTree *current = root;
  NodeTree *previous = nullptr;
  int64_t prev = 0;
  while (current) {
    if (previous == current->prev) {
      previous = current;
      if (current->left) {
        current = current->left;
      } else {
        if (current->val != prev) {
          std::cout << current->val << '\n';
          prev = current->val;
        }
        if (current->right) {
          current = current->right;
        } else {
          current = current->prev;
        }
      }
    } else if (previous == current->left) {
      if (current->val != prev) {
        std::cout << current->val << '\n';
        prev = current->val;
      }
      previous = current;
      if (current->right) {
        current = current->right;
      } else {
        current = current->prev;
      }
    } else if (previous == current->right) {
      previous = current;
      current = current->prev;
    }
  }
}

int main() {
  NodeTree *tree = nullptr;
  int64_t el = -1;
  int64_t prev_el = 0;
  while (el != 0) {
    std::cin >> el;
    if (el != 0 && prev_el != el) {
      Push(el, &tree, nullptr);
    }
    prev_el = el;
  }
  Walk(tree);
  Free(tree);
}
