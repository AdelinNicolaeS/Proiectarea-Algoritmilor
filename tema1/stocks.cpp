#include <fstream>
#include <vector>
using namespace std;

struct stock {
  int current_value;
  int min_value;
  int max_value;
};

int main() {
  ifstream fin("stocks.in");
  ofstream fout("stocks.out");

  int N, B, L, i, s, l;
  int prev_s, prev_l, profit;

  fin >> N >> B >> L;
  vector<vector<vector<int>>> dp(
      N + 1, vector<vector<int>>(B + 1, vector<int>(L + 1)));
  vector<struct stock> v(N + 1);
  for (i = 1; i <= N; i++) {
    fin >> v[i].current_value >> v[i].min_value >> v[i].max_value;
  }
  for (i = 1; i <= N; i++) {
    for (s = 1; s <= B; s++) {
      for (l = 1; l <= L; l++) {
        dp[i][s][l] = dp[i - 1][s][l];
        prev_s = s - v[i].current_value;
        prev_l = l - (v[i].current_value - v[i].min_value);
        profit = v[i].max_value - v[i].current_value;
        if (prev_s >= 0 && prev_l >= 0) {
          if (dp[i - 1][prev_s][prev_l] + profit > dp[i][s][l]) {
            dp[i][s][l] = dp[i - 1][prev_s][prev_l] + profit;
          }
        }
      }
    }
  }
  fout << dp[N][B][L] << "\n";
  fin.close();
  fout.close();
  return 0;
}
