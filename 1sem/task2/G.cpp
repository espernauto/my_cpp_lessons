#include <iostream>
#include <algorithm>

struct List {
 private:
  struct Node {
    int val;
    Node* next;
  };
  Node* begin_;
  Node* end_;
  size_t size_;

 public:
  List() {
    begin_ = nullptr;
    end_ = nullptr;
    size_ = 0;
  }
  void PushFront(int val) {
    auto* v = new Node();
    v->val = val;
    v->next = begin_;
    begin_ = v;
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

  void PushBack(int64_t val) {
    auto* v = new Node();
    v->val = val;
    v->next = nullptr;
    if (size_ > 0) {
      end_->next = v;
      end_ = end_->next;
    } else {
      begin_ = v;
      end_ = begin_;
    }
    ++size_;
  }

  int& GetFront() {
    return begin_->val;
  }

  size_t Size() const {
    return size_;
  }

  void Clear() {
    while (size_ != 0) {
      PopFront();
    }
  }
};

struct Queue {
 private:
  List l_;

 public:
  void PopFront() {
    l_.PopFront();
  }
  void PushBack(int64_t val) {
    l_.PushBack(val);
  }
  void Clear() {
    l_.Clear();
  }
  int& GetFront() {
    return l_.GetFront();
  }
  size_t Size() {
    return l_.Size();
  }
};

int main() {
  Queue a;
  Queue b;
  int64_t val;
  int first;
  int second;
  for (int i = 0; i < 5; i++) {
    std::cin >> val;
    a.PushBack(val);
  }
  for (int i = 0; i < 5; i++) {
    std::cin >> val;
    b.PushBack(val);
  }
  int64_t i = 0;
  for (; i < 1000000; i++) {
    first = a.GetFront();
    second = b.GetFront();
    a.PopFront();
    b.PopFront();
    if ((first > second && (first != 9 || second != 0)) || (first == 0 && second == 9)) {
      a.PushBack(first);
      a.PushBack(second);
    } else {
      b.PushBack(first);
      b.PushBack(second);
    }
    if (a.Size() == 10) {
      std::cout << "first" << '\n';
      std::cout << i + 1;
      break;
    }
    if (b.Size() == 10) {
      std::cout << "second" << '\n';
      std::cout << i + 1;
      break;
    }
  }
  if (i == 1000000) {
    std::cout << "botva";
  }
  a.Clear();
  b.Clear();
}
