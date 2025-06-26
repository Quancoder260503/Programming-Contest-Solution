#include "bits/stdc++.h"

using namespace std;

#define int64_t long long
#define sz(x) int(x.size())

using cd = complex<double>;
const double PI = acos(-1);

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
vector<int64_t> FFT(vector<int> &a, vector<int> &b) {
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
  vector<int64_t> res(n);
  for (int i = 0; i < n; i++) {
    res[i] = 1LL * round(A[i].real());
  }
  return res;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N, M;
  cin >> N >> M;
  vector<char>cA(N), cB(M);  
  vector<int>freqA(N), freqB(M);
  set<pair<char, int>>direction; 
  for (int i = 0; i < N; i++) {
    cin >> cA[i]; 
    if(cA[i] == '?') { 
      freqA[i] = 1; 
    }
    else { 
      cin >> freqA[i]; 
    }
    if(cA[i] != '?') direction.insert({cA[i], freqA[i]}); 
  }
  for (int i = 0; i < M; i++) {
    cin >> cB[i]; 
    if(cB[i] == '?') { 
      freqB[i] = 1; 
    }
    else { 
      cin >> freqB[i]; 
    }
    if(cB[i] != '?') direction.insert({cB[i], freqB[i]}); 
  }
  vector<int> numMatch(N);
  for (auto dir : direction) {
    vector<int> pa(N), pb(M);
    for (int i = 0; i < N; i++) {
      if (cA[i] == dir.first && freqA[i] == dir.second) {
        pa[i]++;
      }
    }
    for (int i = 0; i < M; i++) {
      if ((cB[i] == dir.first && freqB[i] == dir.second) || cB[i] == '?') {
        pb[M - 1 - i]++;
      }
    }
    vector<int64_t> pc = FFT(pa, pb);
    for (int i = 0; i < min(sz(pc), N); i++) {
      numMatch[i] += pc[i];
    }
  }
  vector<int> pa(N), pb(M);
  for (int i = 0; i < N; i++) {
    if (cA[i] == '?') {
      pa[i]++;
    }
  }
  for (int i = 0; i < M; i++) {
    pb[M - 1 - i] = 1;
  }
  vector<int64_t> pc = FFT(pa, pb);
  for (int i = 0; i < min(sz(pc), N); i++) {
    numMatch[i] += pc[i];
  }
  int ret = 0;
  for (int i = 0; i < N; i++) {
    if (numMatch[i] == M) {
      ret++;
    }
  }
  cout << ret << '\n';
  return 0;
}