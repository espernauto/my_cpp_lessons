#include <iostream>
#include <unordered_map>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  std::cin >> n;
  std::unordered_map<std::string, int> clients_dict;
  int command;
  std::string key;
  int value;
  for (int i = 0; i < n; i++) {
    std::cin >> command;
    if (command == 1) {
      std::cin >> key >> value;
      clients_dict[key] += value;
    } else {
      std::cin >> key;
      auto it1 = clients_dict.find(key);
      if (it1 != clients_dict.end()) {
        std::cout << it1->second << '\n';
      } else {
        std::cout << "ERROR\n";
      }
    }
  }
}
