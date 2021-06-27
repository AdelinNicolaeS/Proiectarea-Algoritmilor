#include <cstring>
#include <fstream>
#include <iostream>

#define MOD 1000000007
#define KMAX 4

using namespace std;

// Credits: https://ocw.cs.pub.ro/courses/pa/laboratoare/laborator-04
// C <- A * B if A, B have the same sizes
void multiply_matrices(int A[4][4], int B[4][4], int C[4][4]) {
  int aux[4][4];
  int i, j, k;
  long long sum;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      sum = 0;
      for (k = 0; k < 4; k++) {
        sum += 1LL * A[i][k] * B[k][j];
      }
      aux[i][j] = sum % MOD;
    }
  }
  memcpy(C, aux, sizeof(aux));
}

// R <- F * M;
void multiply_line_matrix(int F[4], int M[4][4], int R[4]) {
  int i, j, aux[4];
  long long sum;
  for (j = 0; j < 4; j++) {
    sum = 0;
    for (i = 0; i < 4; i++) {
      sum += 1LL * F[i] * M[i][j];
    }
    aux[j] = sum % MOD;
  }
  memcpy(R, aux, sizeof(aux));
}

// R <- C^n
void power_n(int C[4][4], long long n, int R[4][4]) {
  if (n < 0) {
    return;
  }

  // aux = I_n
  int aux[4][4] = {0}, i;
  for (i = 0; i < 4; i++) {
    aux[i][i] = 1;
  }

  if (n == 0) {
    memcpy(R, aux, sizeof(aux));
    return;
  }

  while (n > 1) {
    if (n % 2 == 0) {
      multiply_matrices(C, C, C);
      n = n / 2;
    } else {
      multiply_matrices(aux, C, aux);
      n--;
    }
  }
  multiply_matrices(C, aux, R);
}

int main() {
  ifstream fin("trigigel.in");
  ofstream fout("trigigel.out");

  long long n;
  fin >> n;
  if (n == 1 || n == 2) {
    fout << n * (n + 1) / 2;
  } else {
  	// n >= 3
    int M[4][4] = {{1, 0, 0, 1}, {0, 0, 0, 1}, {0, 1, 0, 0}, {0, 0, 1, 1}};
    int F[4] = {1, 1, 2, 3};
    int i;
    long long sum = 0;

    power_n(M, n - 3, M);              // M <- M^(n - 3)
    multiply_line_matrix(F, M, F);     // F <- F * M

    for (i = 1; i < 4; i++) {
      sum = (sum % MOD + F[i] % MOD) % MOD;
    }

    fout << sum;
  }

  fout << "\n";
  fin.close();
  fout.close();
  return 0;
}
