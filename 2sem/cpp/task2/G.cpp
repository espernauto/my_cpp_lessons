#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

bool Cmp(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
  if (a.second != b.second) {
    return a.second > b.second;
  }
  return a.first < b.first;
}

int main() {
  std::string text;
  std::map<std::string, int> dictionary;
  while (true) {
    std::cin >> text;
    if (!std::cin) {
      break;
    }
    auto it1 = dictionary.find(text);
    if (it1 != dictionary.end()) {
      it1->second += 1;
    } else {
      dictionary[text] = 1;
    }
  }
  std::vector<std::pair<std::string, int>> pairs;
  for (auto it = dictionary.begin(); it != dictionary.end(); ++it) {
    pairs.emplace_back(*it);
  }
  std::sort(pairs.begin(), pairs.end(), Cmp);
  for (size_t i = 0; i < pairs.size(); i++) {
    std::cout << pairs[i].first << '\n';
  }
}
