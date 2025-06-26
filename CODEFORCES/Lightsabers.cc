#include "bits/stdc++.h"
 
using namespace std;
 
#define int64_t long long
#define sz(x) int(x.size())
 
using cd = complex<double>;
const double PI = acos(-1);
const int MOD = 1009; 
 
void fft(vector<cd> &a, int sz, bool invert) {
  for (int i = 1, mask = 0; i < sz; i++) {
    int bit = sz >> 1;
    for (; mask & bit; bit = bit / 2) {
      mask = mask xor bit;
    }
    mask = mask xor bit;
    if (i < mask) {
      swap(a[i], a[mask]);
    }
  }
  for (int len = 2; len <= sz; len = len * 2) {
    double angle = 2 * PI / len * (invert ? -1 : 1);
    cd wang(cos(angle), sin(angle));
    for (int i = 0; i < sz; i += len) {
      cd w(1);
      for (int j = 0; j < len / 2; j++) {
        cd u = a[i + j];
        cd v = w * a[i + j + len / 2];
        a[i + j] = u + v;
        a[i + j + len / 2] = u - v;
        w = w * wang;
      }
    }
  }
  if (invert) {
    for (int i = 0; i < sz; i++) {
      a[i] /= sz;
    }
  }
  return;
}
vector<int64_t> FFT(const vector<int64_t>&a, const vector<int64_t>&b) {
  vector<cd> A(a.begin(), a.end()), B(b.begin(), b.end());
  int n = 1;
  while (n < A.size() + B.size()) {
    n = n * 2;
  }
  A.resize(n);
  B.resize(n);
  fft(A, (int)A.size(), false);
  fft(B, (int)B.size(), false);
  for (int i = 0; i < n; i++) {
    A[i] *= B[i];
  }
  fft(A, (int)A.size(), true);
  vector<int64_t>res(n);
  for (int i = 0; i < n; i++) {
    res[i] = 1LL * round(A[i].real());
    res[i] %= MOD; 
  }
  return res;
}
 
vector<vector<int64_t>>poly; 
 
vector<int64_t>rec(int Lbound, int Rbound) { 
  if(Lbound == Rbound) return poly[Lbound]; 
  int mid = (Lbound + Rbound) / 2; 
  vector<int64_t> L = rec(Lbound, mid), R = rec(mid + 1, Rbound);
  return FFT(L, R); 
}
 
int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0); 
 cout.tie(0);
 int N, M, K; 
 cin >> N >> M >> K; 
 vector<int>a(N), freq(M); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
  freq[a[i] - 1]++; 
 }
 //sort(freq.begin(), freq.end()); 
 for(int i = 0; i < M; i++) { 
  if(freq[i] == 0) continue; 
  vector<int64_t>curr; 
  for(int j = 0; j <= freq[i]; j++) { 
   curr.push_back(1); 
  }
  poly.push_back(curr); 
 }
 cout << rec(0, sz(poly) - 1)[K] << '\n'; 
 return 0;
}