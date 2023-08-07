#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

bool CmpBuyers(const std::pair<std::string, int64_t>& a, const std::pair<std::string, int64_t>& b) {
  return a.first < b.first;
}

class Buyer {
 private:
  std::map<std::string, int64_t> shopping_list_;
  std::vector<std::pair<std::string, int64_t>> pairs_;

 public:
  void Sort() {
    pairs_.resize(0);
    for (auto it = shopping_list_.begin(); it != shopping_list_.end(); ++it) {
      pairs_.emplace_back(*it);
    }
    std::sort(pairs_.begin(), pairs_.end(), CmpBuyers);
  }

  std::_Rb_tree_iterator<std::pair<const std::basic_string<char>, int64_t>> FindProduct(std::string& product) {
    return shopping_list_.find(product);
  }

  std::_Rb_tree_iterator<std::pair<const std::basic_string<char>, int64_t>> End() {
    return shopping_list_.end();
  }

  void Push(std::string& product, int64_t price) {
    shopping_list_[product] = price;
  }

  size_t ShoppingSize() {
    return shopping_list_.size();
  }

  std::pair<std::string, int64_t> Pair(int j) {
    return pairs_[j];
  }
};

void Push(std::map<std::string, Buyer>& buyers, std::string& buyer, std::string& product, int64_t& price) {
  auto it1 = buyers.find(buyer);
  if (it1 != buyers.end()) {
    auto it2 = buyers[buyer].FindProduct(product);
    if (it2 != it1->second.End()) {
      it2->second += price;
    } else {
      buyers[buyer].Push(product, price);
    }
  } else {
    buyers[buyer].Push(product, price);
  }
}

bool Cmp(std::pair<std::string, Buyer>& a, std::pair<std::string, Buyer>& b) {
  return a.first < b.first;
}

int main() {
  std::string text;
  std::map<std::string, Buyer> buyers;
  while (true) {
    std::string buyer, product;
    int64_t price;
    std::cin >> buyer >> product >> price;
    if (!std::cin) {
      break;
    }
    Push(buyers, buyer, product, price);
  }
  std::vector<std::pair<std::string, Buyer>> pairs;
  for (auto it = buyers.begin(); it != buyers.end(); ++it) {
    pairs.emplace_back(*it);
  }
  buyers.clear();
  for (size_t i = 0; i < pairs.size(); ++i) {
    pairs[i].second.Sort();
  }
  for (size_t i = 0; i < pairs.size(); ++i) {
    std::cout << pairs[i].first << ":" << '\n';
    for (size_t j = 0; j < pairs[i].second.ShoppingSize(); ++j) {
      std::cout << pairs[i].second.Pair(j).first << ' ';
      std::cout << pairs[i].second.Pair(j).second << '\n';
    }
  }
}
