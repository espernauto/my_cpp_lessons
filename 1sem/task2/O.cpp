#include <iostream>

struct Tree {
 private:
  struct Node {
    int64_t info;
    Node *left;
    Node *right;
    explicit Node(int64_t a) {
      info = a;
      left = nullptr;
      right = nullptr;
    }
  };
  Node *root_ = nullptr;
  void PushInside(Node *root_tree, int64_t a) {
    if (root_tree == nullptr) {
      root_ = new Node(a);
    } else if (a > root_tree->info && root_tree->right) {
      PushInside(root_tree->right, a);
    } else if (a > root_tree->info && !root_tree->right) {
      root_tree->right = new Node(a);
    } else if (a < root_tree->info && root_tree->left) {
      PushInside(root_tree->left, a);
    } else if (a < root_tree->info && !root_tree->left) {
      root_tree->left = new Node(a);
    }
  }

  void FreeInside(Node *root_tree) {
    if (root_tree->left) {
      FreeInside(root_tree->left);
    }
    if (root_tree->right) {
      FreeInside(root_tree->right);
    }
    delete root_tree;
  }

  void LeafInternal(Node *root) const {
    if (root->right == nullptr && root->left == nullptr) {
      return;
    }
    if (root->right == nullptr) {
      LeafInternal(root->left);
    } else if (root->left == nullptr) {
      LeafInternal(root->right);
    } else {
      LeafInternal(root->left);
      std::cout << root->info << '\n';
      LeafInternal(root->right);
    }
  }

 public:
  void Push(int64_t a) {
    PushInside(root_, a);
  }

  void Free() {
    FreeInside(root_);
  }

  void Leaf() const {
    LeafInternal(root_);
  }
};

int main() {
  Tree tree;
  int64_t el = -1;
  int64_t prev_el = 0;
  while (el != 0) {
    std::cin >> el;
    if (el != 0 && prev_el != el) {
      tree.Push(el);
    }
    prev_el = el;
  }
  tree.Leaf();
  tree.Free();
}
