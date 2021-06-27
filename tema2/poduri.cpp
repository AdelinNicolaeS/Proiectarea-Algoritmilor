#include <fstream>
#include <queue>
#include <tuple>

using namespace std;

bool available(int n, int m, int x, int y, vector<vector<char>> a,
               vector<vector<bool>> visited) {
  return (x >= 0 && x < n && y >= 0 && y < m && !visited[x][y] &&
          a[x][y] != '.');
}

bool margine_iese(int n, int m, int x, int y, vector<vector<char>> a) {
  if (x == 0 && (a[x][y] == 'V' || a[x][y] == 'D')) {
    return true;
  }
  if (x == n - 1 && (a[x][y] == 'V' || a[x][y] == 'D')) {
    return true;
  }
  if (y == 0 && (a[x][y] == 'O' || a[x][y] == 'D')) {
    return true;
  }
  if (y == m - 1 && (a[x][y] == 'O' || a[x][y] == 'D')) {
    return true;
  }
  return false;
}

int main() {
  int n, m, x, y, i, j;
  int rows[4] = {0, 0, 1, -1};
  int colu[4] = {1, -1, 0, 0};
  ifstream fin("poduri.in");
  ofstream fout("poduri.out");

  fin >> n >> m;
  fin >> x >> y;
  x--;
  y--;
  vector<vector<char>> a(n, vector<char>(m));
  vector<vector<bool>> visited(n, vector<bool>(m));

  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      fin >> a[i][j];
      visited[i][j] = false;
    }
  }

  queue<tuple<int, int, int>> my_queue;
  my_queue.push({x, y, 0});
  visited[x][y] = true;
  if (a[x][y] == '.') {
    fout << "-1\n";
    return 0;
  }

  while (!my_queue.empty()) {
    tuple<int, int, int> aux = my_queue.front();
    my_queue.pop();

    x = get<0>(aux);
    y = get<1>(aux);
    int dist = get<2>(aux);

    if (((x == 0 || x == n - 1) && (a[x][y] == 'V' || a[x][y] == 'D')) ||
        ((y == 0 || y == m - 1) && (a[x][y] == 'O' || a[x][y] == 'D'))) {
      fout << dist + 1 << "\n";
      fin.close();
      fout.close();
      return 0;
    }

    if (a[x][y] == 'V') {
      for (int k = 2; k < 4; k++) {
        if (x + rows[k] >= 0 && x + rows[k] < n && y + colu[k] >= 0 &&
            y + colu[k] < m && !visited[x + rows[k]][y + colu[k]] &&
            a[x + rows[k]][y + colu[k]] != '.') {
          visited[x + rows[k]][y + colu[k]] = true;
          my_queue.push({x + rows[k], y + colu[k], dist + 1});
        }
      }
    } else if (a[x][y] == 'O') {
      for (int k = 0; k < 2; k++) {
        if (x + rows[k] >= 0 && x + rows[k] < n && y + colu[k] >= 0 &&
            y + colu[k] < m && !visited[x + rows[k]][y + colu[k]] &&
            a[x + rows[k]][y + colu[k]] != '.') {
          visited[x + rows[k]][y + colu[k]] = true;
          my_queue.push({x + rows[k], y + colu[k], dist + 1});
        }
      }
    } else if (a[x][y] == 'D') {
      for (int k = 0; k < 4; k++) {
        if (x + rows[k] >= 0 && x + rows[k] < n && y + colu[k] >= 0 &&
            y + colu[k] < m && !visited[x + rows[k]][y + colu[k]] &&
            a[x + rows[k]][y + colu[k]] != '.') {
          visited[x + rows[k]][y + colu[k]] = true;
          my_queue.push({x + rows[k], y + colu[k], dist + 1});
        }
      }
    }
  }
  fout << "-1\n";
  fin.close();
  fout.close();
  return 0;
}
