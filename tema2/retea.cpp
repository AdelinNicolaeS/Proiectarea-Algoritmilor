#include <algorithm>
#include <climits>
#include <fstream>
#include <vector>
using namespace std;

#define NMAX 10000

long long solution[NMAX + 1];
vector<int> adj[NMAX + 1];
int backwards[NMAX + 1];
int depth[NMAX + 1];
int size[NMAX + 1];
int n, m;

void DFS(int node, int parent) {
  // actualizam adancimea si dimensiunea
  depth[node] = depth[parent] + 1;
  size[node] = 1;

  // pentru fiecare muchie de intoarcere
  // vedem cat de sus se poate merge
  for (auto child : adj[node]) {
    if (child != parent) {
      if (depth[child] > 0) {  // muchie de intoarcere
        // actualizam backwards
        backwards[node] = min(backwards[node], depth[child]);
      } else {
        // facem dfs pe copil
        DFS(child, node);
        size[node] += size[child];
      }
    }
  }

  // aflu muchia de intoarcere din subarbore
  for (auto child : adj[node]) {
    if (depth[child] == depth[node] + 1) {
      backwards[node] = min(backwards[node], backwards[child]);
    }
  }

  // numaram conexiunile pierdute
  int curr = 1;
  for (auto child : adj[node]) {
    if (depth[child] == depth[node] + 1 && backwards[child] >= depth[node]) {
      solution[node] =
          solution[node] + 2LL * size[child] * (n - size[child] - curr);
      curr = curr + size[child];
    }
  }
}

int main() {
  ifstream fin("retea.in");
  ofstream fout("retea.out");
  int i;

  fin >> n >> m;
  for (i = 1; i <= m; i++) {
    int x, y;
    fin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // backwards(i) = cea mai de sus muchie de intoarcere
  // a subarborelui cu radacina in i
  for (i = 1; i <= n; i++) {
    backwards[i] = INT_MAX;
  }

  DFS(1, 0);

  for (i = 1; i <= n;
       i++) {  // daca scot nodul se scot toate conexiunile
    solution[i] = solution[i] + 2 * (n - 1);
  }

  for (i = 1; i <= n; i++) {
    fout << solution[i] << "\n";
  }

  fin.close();
  fout.close();

  return 0;
}
