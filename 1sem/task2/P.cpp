#include <iostream>
#include <algorithm>

struct Tree {
 private:
  struct Node {
    int64_t key;
    int64_t height;
    Node *left;
    Node *right;
    explicit Node(int k) {
      key = k;
      left = right = nullptr;
      height = 1;
    }
  };
  Node *root_ = nullptr;

  int Height(Node *p) {
    if (p) {
      return p->height;
    }
    return 0;
  }

  int BalanceFactor(Node *p) {
    return Height(p->right) - Height(p->left);
  }

  void FixHeight(Node *p) {
    int hl = Height(p->left);
    int hr = Height(p->right);
    if (hl > hr) {
      p->height = hl + 1;
    } else {
      p->height = hr + 1;
    }
  }

  Node *RotateRight(Node *p) {
    Node *q = p->left;
    p->left = q->right;
    q->right = p;
    FixHeight(p);
    FixHeight(q);
    return q;
  }

  Node *RotateLeft(Node *q) {
    Node *p = q->right;
    q->right = p->left;
    p->left = q;
    FixHeight(q);
    FixHeight(p);
    return p;
  }

  Node *Balance(Node *p) {
    FixHeight(p);
    if (BalanceFactor(p) == 2) {
      if (BalanceFactor(p->right) < 0) {
        p->right = RotateRight(p->right);
      }
      return RotateLeft(p);
    }
    if (BalanceFactor(p) == -2) {
      if (BalanceFactor(p->left) > 0) {
        p->left = RotateLeft(p->left);
      }
      return RotateRight(p);
    }
    return p;
  }

  Node *InsertInside(Node *p, int64_t k) {
    if (!p) {
      return new Node(k);
    }
    if (k < p->key) {
      p->left = InsertInside(p->left, k);
    } else if (k > p->key) {
      p->right = InsertInside(p->right, k);
    }
    return Balance(p);
  }

  void FreeInside(Node *&root) {
    if (root->left) {
      FreeInside(root->left);
    }
    if (root->right) {
      FreeInside(root->right);
    }
    delete root;
    root = nullptr;
  }

 public:
  void Insert(int64_t k) {
    root_ = InsertInside(root_, k);
  }

  int64_t Next(int64_t value) const {
    Node *current = root_;
    Node *successor = nullptr;
    while (current != nullptr) {
      if (current->key >= value) {
        successor = current;
        current = current->left;
      } else {
        current = current->right;
      }
    }
    if (!successor) {
      return -1;
    }
    return successor->key;
  }

  void Free() {
    FreeInside(root_);
  }
};

int main() {
  int n;
  std::cin >> n;
  Tree tree;
  char command;
  int64_t value;
  char old_command = '+';
  int64_t old_value = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> command;
    std::cin >> value;
    if (command == '+') {
      if (old_command == '+') {
        tree.Insert(value);
      } else {
        tree.Insert((value + old_value) % 1000000000);
      }
    } else {
      old_value = tree.Next(value);
      std::cout << old_value << '\n';
    }
    old_command = command;
  }
  tree.Free();
}
