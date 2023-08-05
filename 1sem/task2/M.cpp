#include <iostream>
#include <algorithm>

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

  int64_t SearchInternal(Node *root, int64_t max, int64_t second_max) const {
    if (root->right == nullptr && root->left == nullptr) {
      return second_max;
    }
    if (root->right == nullptr) {
      if (root->info > second_max && root->info < max) {
        second_max = root->info;
      }
      if (root->left->info > second_max) {
        second_max = root->left->info;
      }
      return SearchInternal(root->left, max, second_max);
    }
    if (root->left != nullptr) {
      if (root->left->info > second_max) {
        second_max = root->left->info;
      }
    }
    if (max < root->right->info) {
      max = root->right->info;
    }
    if (second_max < root->info && root->info != max) {
      second_max = root->info;
    }
    if (second_max < root->right->info && root->right->info != max) {
      second_max = root->right->info;
    }
    return SearchInternal(root->right, max, second_max);
  }

 public:
  void Push(int64_t a) {
    PushInside(root_, a);
  }

  void Free() {
    FreeInside(root_);
  }

  void Search() const {
    int64_t max;
    int64_t second_max;
    if (root_->right == nullptr) {
      max = root_->info;
      second_max = root_->left->info;
      std::cout << SearchInternal(root_, max, second_max) << '\n';
    } else if (root_->left != nullptr) {
      max = root_->info;
      second_max = root_->left->info;
      std::cout << SearchInternal(root_, max, second_max) << '\n';
    } else {
      max = root_->right->info;
      second_max = root_->info;
      std::cout << SearchInternal(root_, max, second_max) << '\n';
    }
  }
};

int main() {
  Tree tree;
  int64_t el = -1;
  while (el != 0) {
    std::cin >> el;
    if (el != 0) {
      tree.Push(el);
    }
  }
  tree.Search();
  tree.Free();
}
