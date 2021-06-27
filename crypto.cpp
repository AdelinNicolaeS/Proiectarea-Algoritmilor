#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

struct computer {
  int coins;
  int upgrade;
};

bool comparator(struct computer c1, struct computer c2) {
  return c1.coins < c2.coins;
}

int main() {
  ifstream fin("crypto.in");
  ofstream fout("crypto.out");

  int N, B, i, upgrade_sum = 0;
  int current_coins;
  struct computer comp;
  vector<struct computer> v;

  fin >> N >> B;
  for (i = 0; i < N; i++) {
    fin >> comp.coins >> comp.upgrade;
    v.push_back(comp);
  }
  sort(v.begin(), v.end(), comparator);
  for (i = 0; i < N; i++) {
    if (v[i].coins == current_coins) {
      upgrade_sum += v[i].upgrade;
    } else {
      if (1.0 * B / upgrade_sum >= 1.0 * (v[i].coins - current_coins)) {
        B -= upgrade_sum * (v[i].coins - current_coins);
        upgrade_sum += v[i].upgrade;
        current_coins = v[i].coins;
      } else {
        break;
      }
    }
  }
  current_coins += B / upgrade_sum;
  fout << current_coins << "\n";
  fin.close();
  fout.close();
  return 0;
}
