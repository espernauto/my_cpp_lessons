#include <iostream>
#include <unordered_map>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  std::cin >> n;
  std::unordered_map<std::string, std::string> dictionary_1;
  std::unordered_map<std::string, std::string> dictionary_2;
  std::string key, value;
  for (int i = 0; i < n; i++) {
    std::cin >> key >> value;
    dictionary_1.insert(std::make_pair(key, value));
    dictionary_2.insert(std::make_pair(value, key));
  }
  int q;
  std::cin >> q;
  std::string query;
  for (int i = 0; i < q; i++) {
    std::cin >> query;
    auto it1 = dictionary_1.find(query);
    auto it2 = dictionary_2.find(query);
    if (it1 != dictionary_1.end()) {
      std::cout << it1->second << '\n';
    }
    if (it2 != dictionary_2.end()) {
      std::cout << it2->second << '\n';
    }
  }
}
