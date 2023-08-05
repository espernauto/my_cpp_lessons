#include <iostream>
#include <algorithm>

struct Node {
  int info;
  Node *left, *right;
};

void Push(int a, Node **t) {
  if ((*t) == nullptr) {
    (*t) = new Node;
    (*t)->info = a;
    (*t)->left = (*t)->right = nullptr;
    return;
  }
  if (a > (*t)->info) {
    Push(a, &(*t)->right);
  } else {
    Push(a, &(*t)->left);
  }
}

int64_t Height(Node *root) {
  if (root == nullptr) {
    return 1;
  }
  if (root->left == nullptr && root->right == nullptr) {
    return 1;
  }
  return 1 + std::max(Height(root->left), Height(root->right));
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
  while (el != 0) {
    std::cin >> el;
    if (el != 0) {
      Push(el, &tree);
    }
  }
  std::cout << Height(tree);
  Free(tree);
}
