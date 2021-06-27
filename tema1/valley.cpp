#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ifstream fin("valley.in");
  ofstream fout("valley.out");

  int i, N;
  long ans;
  fin >> N;
  vector<long> dp(N + 1, 0);
  vector<long> v(N + 1, 0);
  for (i = 1; i <= N; i++) {
    fin >> v[i];
  }
  vector<long> current(v.begin(), v.end());
  // solve base case
  if (current[1] < current[2]) {
    dp[2] += current[2] - current[1];
    current[2] = current[1];
  }
  for (i = N - 1; i >= 2; i--) {
    if (current[i] > current[i + 1]) {
      dp[2] += current[i] - current[i + 1];
      current[i] = current[i + 1];
    }
  }
  ans = dp[2];
  // solve general case
  for (i = 3; i <= N - 1; i++) {
    dp[i] = dp[i - 1] - (v[i - 1] - current[i - 1]) - (v[i] - current[i]);

    current[i - 1] = v[i - 1];
    current[i] = v[i];

    if (current[i - 2] < current[i - 1]) {
      dp[i] += current[i - 1] - current[i - 2];
      current[i - 1] = current[i - 2];
    }
    if (current[i - 1] < current[i]) {
      dp[i] += current[i] - current[i - 1];
      current[i] = current[i - 1];
    }
    if (current[i] > current[i + 1]) {
      dp[i] += current[i] - current[i + 1];
      current[i] = current[i + 1];
    }
    ans = min(ans, dp[i]);
  }
  fout << ans << "\n";
  fin.close();
  fout.close();
  return 0;
}
