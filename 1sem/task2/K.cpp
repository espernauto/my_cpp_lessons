#include <iostream>
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

struct MinStack {
 private:
  List l_;
  int64_t min_;

 public:
  int64_t PopFront() {
    if (l_.Size() == 0) {
      return 0;
    }
    int t = l_.GetFront();
    l_.PopFront();

    if (t < min_) {
      int64_t k = min_;
      min_ = 2 * min_ - t;
      return k;
    }
    return t;
  }

  void PushFront(int x) {
    if (l_.Size() == 0) {
      min_ = x;
      l_.PushFront(x);
      return;
    }
    if (x < min_) {
      l_.PushFront(2 * x - min_);
      min_ = x;
    } else {
      l_.PushFront(x);
    }
  }

  void Clear() {
    l_.Clear();
  }

  int64_t &GetFront() {
    if (l_.GetFront() < min_) {
      return min_;
    }
    return l_.GetFront();
  }

  size_t Size() {
    return l_.Size();
  }

  int64_t GetMin() {
    return min_;
  }
};

struct MinQueue {
 private:
  MinStack q1_, q2_;

 public:
  void Enqueue(int64_t val) {
    q1_.PushFront(val);
  }

  void Dequeue() {
    if (q1_.Size() > 0 || q2_.Size() > 0) {
      if (q2_.Size() == 0) {
        while (q1_.Size() > 0) {
          int64_t el = q1_.GetFront();
          q1_.PopFront();
          q2_.PushFront(el);
        }
      }
      q2_.PopFront();
    } else {
      return;
    }
  }

  int64_t &GetFront() {
    if (q2_.Size() == 0) {
      while (q1_.Size() > 0) {
        int64_t el = q1_.GetFront();
        q1_.PopFront();
        q2_.PushFront(el);
      }
    }
    return q2_.GetFront();
  }

  int64_t GetMin() {
    if (q1_.Size() > 0 && q2_.Size() > 0) {
      return std::min(q1_.GetMin(), q2_.GetMin());
    }
    if (q1_.Size() > 0) {
      return q1_.GetMin();
    }
    if (q2_.Size() > 0) {
      return q2_.GetMin();
    }
    return 0;
  }

  size_t Size() {
    return q1_.Size() + q2_.Size();
  }

  void Clear() {
    q1_.Clear();
    q2_.Clear();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  MinQueue q1;
  int64_t n, k;
  std::cin >> n >> k;
  int64_t val;
  for (int i = 0; i < k; i++) {
    std::cin >> val;
    q1.Enqueue(val);
  }
  std::cout << q1.GetMin() << '\n';
  for (int i = 0; i < n - k; i++) {
    q1.Dequeue();
    std::cin >> val;
    q1.Enqueue(val);
    std::cout << q1.GetMin() << '\n';
  }
  q1.Clear();
}
