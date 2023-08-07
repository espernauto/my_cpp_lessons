#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  std::cin >> n;
  std::string animals;
  std::vector<int> parsed_animals;
  for (int i = 0; i < n; i++) {
    std::cin >> animals;
    parsed_animals.emplace_back(stoi(animals));
  }
  int n_queries;
  std::cin >> n_queries;
  for (int i = 0; i < n_queries; i++) {
    int query;
    std::cin >> query;
    std::cout << std::upper_bound(parsed_animals.begin(), parsed_animals.end(), query) -
                     std::lower_bound(parsed_animals.begin(), parsed_animals.end(), query)
              << '\n';
  }
}
