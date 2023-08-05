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

struct Stack {
 private:
  List l_;

 public:
  void PopFront() {
    l_.PopFront();
  }
  void PushFront(int64_t val) {
    l_.PushFront(val);
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
  char str[1000000];
  char a = getchar();
  int n = 0;
  while (a != '\n') {
    if (str[n] != ' ') {
      str[n] = a;
      n++;
    }
    a = getchar();
  }
  Stack stack;
  for (int i = 0; i < n; i++) {
    if (isdigit(str[i])) {
      stack.PushFront(atoi(&(str[i])));
    } else if (str[i] == '+') {
      int a, b;
      a = stack.GetFront();
      stack.PopFront();
      b = stack.GetFront();
      stack.PopFront();
      stack.PushFront(b + a);
    } else if (str[i] == '-') {
      int a, b;
      a = stack.GetFront();
      stack.PopFront();
      b = stack.GetFront();
      stack.PopFront();
      stack.PushFront(b - a);
    } else if (str[i] == '*') {
      int a, b;
      a = stack.GetFront();
      stack.PopFront();
      b = stack.GetFront();
      stack.PopFront();
      stack.PushFront(b * a);
    }
  }
  std::cout << stack.GetFront();
  stack.Clear();
}
