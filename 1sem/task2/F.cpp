#include <iostream>
#include <algorithm>
#include <cstring>

struct List {
 private:
  struct Node {
    int64_t val;
    Node *next = nullptr;
    Node *prev = nullptr;
  };
  Node *begin_ = nullptr;
  Node *end_ = nullptr;
  size_t size_ = 0;

 public:
  List() {
    begin_ = nullptr;
    end_ = nullptr;
    size_ = 0;
  }

  void PopBack() {
    if (size_ == 0) {
      return;
    }
    auto *old = end_;
    end_ = end_->prev;
    delete old;
    --size_;
  }

  void PushFront(int64_t val) {
    auto *v = new Node();
    v->val = val;
    v->next = begin_;
    begin_ = v;
    if (size_ == 0) {
      end_ = begin_;
    } else {
      begin_->next->prev = begin_;
    }
    ++size_;
  }

  void PushBack(int64_t val) {
    auto *v = new Node();
    v->val = val;
    v->next = nullptr;
    v->prev = end_;
    if (size_ > 0) {
      end_->next = v;
      end_ = end_->next;
    } else {
      begin_ = v;
      end_ = begin_;
    }
    ++size_;
  }

  void PopFront() {
    if (size_ == 0) {
      return;
    }
    auto old = begin_;
    begin_ = begin_->next;
    delete old;
    --size_;
  }

  int64_t &GetFront() const {
    return begin_->val;
  }

  int64_t &GetBack() const {
    return end_->val;
  }

  size_t Size() const {
    return size_;
  }

  void Clear() {
    while (size_ > 0) {
      PopFront();
    }
  }
};

struct Deck {
  List l_;
  void PopBack() {
    l_.PopBack();
  }

  void PushFront(int64_t val) {
    l_.PushFront(val);
  }

  void PushBack(int64_t val) {
    l_.PushBack(val);
  }

  void PopFront() {
    l_.PopFront();
  }

  int64_t &GetFront() const {
    return l_.GetFront();
  }

  int64_t &GetBack() const {
    return l_.GetBack();
  }

  size_t Size() const {
    return l_.Size();
  }

  void Clear() {
    l_.Clear();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t m;
  std::cin >> m;
  char command[40];
  int64_t val;
  Deck que;
  for (int i = 0; i < m; i++) {
    std::cin >> command;
    if (!strcmp(command, "push_back")) {
      std::cin >> val;
      que.PushBack(val);
      std::cout << "ok" << '\n';
    }
    if (!strcmp(command, "push_front")) {
      std::cin >> val;
      que.PushFront(val);
      std::cout << "ok" << '\n';
    }
    if (!strcmp(command, "pop_front")) {
      if (que.Size() > 0) {
        std::cout << que.GetFront() << '\n';
        que.PopFront();
      } else {
        std::cout << "error" << '\n';
      }
    }
    if (!strcmp(command, "pop_back")) {
      if (que.Size() > 0) {
        std::cout << que.GetBack() << '\n';
        que.PopBack();
      } else {
        std::cout << "error" << '\n';
      }
    }
    if (!strcmp(command, "front")) {
      if (que.Size() == 0) {
        std::cout << "error" << '\n';
      } else {
        std::cout << que.GetFront() << '\n';
      }
    }
    if (!strcmp(command, "back")) {
      if (que.Size() == 0) {
        std::cout << "error" << '\n';
      } else {
        std::cout << que.GetBack() << '\n';
      }
    }
    if (!strcmp(command, "size")) {
      std::cout << que.Size() << '\n';
    }
    if (!strcmp(command, "clear")) {
      que.Clear();
      std::cout << "ok" << '\n';
    }
    if (!strcmp(command, "exit")) {
      std::cout << "bye";
      break;
    }
  }
  que.Clear();
}
