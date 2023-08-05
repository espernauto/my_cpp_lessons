#include <iostream>
#include <algorithm>

struct Pair {
  int i;
  int j;

  Pair(int a, int b) {
    i = a;
    j = b;
  }

  Pair() {
    i = 0;
    j = 0;
  }

  bool operator==(Pair b) {
    return (i == b.i && j == b.j);
  }

  bool operator!=(Pair b) {
    return (i != b.i || j != b.j);
  }
};

Pair MaxStep(Pair place, int** floor, int h, int w) {
  Pair best = place;
  for (int i = place.i; i < place.i + h; i++) {
    for (int j = place.j; j < place.j + w; j++) {
      if (floor[i][j] > floor[best.i][best.j]) {
        best = Pair(i, j);
      }
    }
  }
  return best;
}

int main() {
  int x, y;
  std::cin >> x >> y;
  int h, w;
  std::cin >> h >> w;
  auto** floor = new int*[x];
  for (int i = 0; i < x; i++) {
    floor[i] = new int[y];
  }
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      std::cin >> floor[i][j];
    }
  }
  Pair place(0, 0);
  while (place != MaxStep(place, floor, std::min(h, x - place.i), std::min(w, y - place.j))) {
    place = MaxStep(place, floor, std::min(h, x - place.i), std::min(w, y - place.j));
  }
  std::cout << place.i << " " << place.j;
  for (int i = 0; i < x; i++) {
    delete[] floor[i];
  }
  delete[] floor;
}
