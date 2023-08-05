#include <iostream>
#include <algorithm>
#include <cstring>

struct List {
 private:
  struct Node {
    char val;
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
  void PushFront(char val) {
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

  void PushBack(char val) {
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

  char& GetFront() {
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
  void PushFront(char val) {
    l_.PushFront(val);
  }
  void Clear() {
    l_.Clear();
  }
  char& GetFront() {
    return l_.GetFront();
  }
  size_t Size() {
    return l_.Size();
  }
};

int main() {
  Stack stack;
  char val = getchar();
  while (val != '\n') {
    if (val == '(' or val == '{' or val == '[') {
      stack.PushFront(val);
    }
    if (val == ')') {
      if (stack.Size() > 0) {
        if (stack.GetFront() == '(') {
          stack.PopFront();
        } else {
          stack.PushFront(val);
          break;
        }
      } else {
        stack.PushFront(val);
        break;
      }
    }
    if (val == ']') {
      if (stack.Size() > 0) {
        if (stack.GetFront() == '[') {
          stack.PopFront();
        } else {
          stack.PushFront(val);
          break;
        }
      } else {
        stack.PushFront(val);
        break;
      }
    }
    if (val == '}') {
      if (stack.Size() > 0) {
        if (stack.GetFront() == '{') {
          stack.PopFront();
        } else {
          stack.PushFront(val);
          break;
        }
      } else {
        stack.PushFront(val);
        break;
      }
    }
    val = getchar();
  }
  if (stack.Size() == 0) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  stack.Clear();
}
