#include <climits>
#include <fstream>
#include <vector>

#define MAX_DEC 2
using namespace std;

struct mountain {
  int heigth;
  int cost;
};

int main() {
  ifstream fin("ridge.in");
  ofstream fout("ridge.out");

  long i, dec, N, mn;
  fin >> N;
  vector<struct mountain> v(N + 1);
  vector<vector<long>> dp(N + 1, vector<long>(MAX_DEC + 1));
  for (i = 1; i <= N; i++) {
    fin >> v[i].heigth >> v[i].cost;
  }
  for (dec = 0; dec <= MAX_DEC; dec++) {
    if (dec <= v[1].heigth) {
      dp[1][dec] = v[1].cost * dec;
    } else {
      dp[1][dec] = LONG_MAX;
    }
  }
  for (i = 2; i <= N; i++) {
    for (dec = 0; dec <= MAX_DEC; dec++) {
      dp[i][dec] = v[i].cost * dec;
      if (dec <= v[i].heigth) {  // inaltimea nenegativa
        // mn = minimul costurilor anterioare
        mn = LONG_MAX;
        for (long k = 0; k <= MAX_DEC; k++) {
          // scop indeplinit
          if (v[i].heigth - dec != v[i - 1].heigth - k) {
            if (mn > dp[i - 1][k]) {
              mn = dp[i - 1][k];
            }
          }
        }
        dp[i][dec] += mn;
      } else {
        dp[i][dec] = LONG_MAX;
      }
    }
  }
  mn = LONG_MAX;
  for (dec = 0; dec <= MAX_DEC; dec++) {
    if (mn > dp[N][dec]) {
      mn = dp[N][dec];
    }
  }
  fout << mn << "\n";
  fin.close();
  fout.close();
  return 0;
}
