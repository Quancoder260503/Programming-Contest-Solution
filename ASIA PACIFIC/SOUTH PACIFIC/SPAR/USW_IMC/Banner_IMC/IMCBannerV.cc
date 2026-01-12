#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <complex>

using namespace std;

#define ll long long
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
void mul(vector<cd> &A, vector<cd> &B) {
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
  return;
}

const int maxn = 3e5 + 10;

int n;
string S;

ll calc(int lo, int hi)  {
 if(lo + 1 == hi) return 0;
 vector<cd>a, b;
 int mid = (lo + hi) / 2;
 for(int i = lo; i < mid; i++) {
  a.push_back(S[i] == 'I');
  b.push_back(0); 
 }
 for(int i = mid; i < hi; i++) {
  b.push_back(S[i] == 'C');
  a.push_back(0); 
 }
 ll ret = 0;
 mul(a, b);
 for(int i = lo; i < hi; i++) {
  if(S[i] == 'M') ret += 1LL * round(a[2 * (i - lo)].real());
 }
 ret += calc(lo, mid);
 ret += calc(mid, hi);
 return ret;
}


int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> n >> S;
  ll ret = calc(0, n);
  cout << ret << '\n';
  return 0;
}

