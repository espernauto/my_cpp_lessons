#include <iostream>
#include <algorithm>

struct Node {
  int64_t info;
  Node *left, *right;
};

void Push(int64_t a, Node **t) {
  if ((*t) == nullptr) {
    (*t) = new Node;
    (*t)->info = a;
    (*t)->left = (*t)->right = nullptr;
    return;
  }
  if (a > (*t)->info) {
    Push(a, &(*t)->right);
  } else if (a < (*t)->info) {
    Push(a, &(*t)->left);
  }
}

void Leaf(Node *root) {
  if (root) {
    Leaf(root->left);
    if (root->right == nullptr && root->left == nullptr) {
      std::cout << root->info << " ";
      return;
    }
    Leaf(root->right);
  }
}

void Free(Node *&root) {
  if (root->left) {
    Free(root->left);
  }
  if (root->right) {
    Free(root->right);
  }
  delete root;
  root = nullptr;
}

int main() {
  Node *tree = nullptr;
  int64_t el = -1;
  int64_t prev_el = 0;
  while (el != 0) {
    std::cin >> el;
    if (el != 0 && prev_el != el) {
      Push(el, &tree);
    }
    prev_el = el;
  }
  Leaf(tree);
  Free(tree);
}
