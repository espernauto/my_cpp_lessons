#include <iostream>
#include <vector>
#include <algorithm>

bool Cmp(std::vector<int>& team_1, std::vector<int>& team_2) {
  if (team_1[1] != team_2[1]) {
    return team_1[1] > team_2[1];
  }
  if (team_1[2] != team_2[2]) {
    return team_1[2] < team_2[2];
  }
  return team_1[0] < team_2[0];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> teams;
  for (int i = 0; i < n; i++) {
    std::vector<int> team;
    team.emplace_back(i + 1);
    int x, y;
    std::cin >> x >> y;
    team.emplace_back(x);
    team.emplace_back(y);
    teams.emplace_back(team);
  }
  std::sort(teams.begin(), teams.end(), Cmp);
  for (int i = 0; i < n; i++) {
    std::cout << teams[i][0] << '\n';
  }
}
