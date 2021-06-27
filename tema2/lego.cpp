#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int k, n, t;

// preluat din laboratorul de backtracking
void back(int step, int stop, vector<int> &domain, vector<int> &solution,
          vector<vector<int>> &all_solutions) {
  if (step == stop) {
    vector<int> aux;
    for (int j = 0; j < stop; j++) {
      aux.push_back(domain[solution[j]]);
    }
    all_solutions.push_back(aux);

    return;
  }
  if (step == 0) {
    solution[step] = 0;
    back(step + 1, stop, domain, solution, all_solutions);
  } else {
    unsigned i = step > 0 ? solution[step - 1] + 1 : 0;
    for (; i < domain.size(); ++i) {
      solution[step] = i;
      back(step + 1, stop, domain, solution, all_solutions);
    }
  }
}

int main() {
  ifstream fin("lego.in");
  ofstream fout("lego.out");
  fin >> k >> n >> t;

  vector<int> domain(k), solution(n);
  solution[0] = 1;

  for (int i = 0; i < k; ++i) {
    domain[i] = i + 1;
  }

  vector<vector<int>> solutions;
  back(0, n, domain, solution, solutions);

  int ans = -1;
  vector<int> ans_sol;
  for (vector<int> sol : solutions) {
    bool in_sequence = false;
    int max_size = sol.back() * t;
    vector<int> dp(max_size + 1, INT_MAX);
    int start;
    int max_seq_len = -1;
    int i;

    // cazurile de baza
    for (auto el : sol) {
      dp[el] = 1;
    }

    for (i = 1; i <= max_size; i++) {
      if (dp[i] == 1 && dp[i] <= t) {
        // avem secventa noua, avem un nou start
        if (!in_sequence) {
          in_sequence = true;
          start = i;
        }
        continue;
      }

      // calculam folosind starile anterioare
      dp[i] = dp[1] + dp[i - 1];
      for (int j = 2; j <= i / 2; j++) {
        dp[i] = min(dp[i], dp[j] + dp[i - j]);
      }

      // se termina secventa
      if (dp[i] > t) {
        if (in_sequence) {
          int len = i - start;
          max_seq_len = max(max_seq_len, len);
          in_sequence = false;
        }
      } else {
        // altfel incepem una noua
        if (!in_sequence) {
          in_sequence = true;
          start = i;
        }
      }
    }

    // am avut o secventa care s-a terminat la final
    if (in_sequence) {
      int len = i - start;
      max_seq_len = max(max_seq_len, len);
    }

    if (ans < max_seq_len) {
      ans = max_seq_len;
      ans_sol = sol;
    }
  }

  fout << ans << "\n";
  for (int el : ans_sol) {
    fout << el << " ";
  }
  fout << "\n";

  fin.close();
  fout.close();

  return 0;
}
