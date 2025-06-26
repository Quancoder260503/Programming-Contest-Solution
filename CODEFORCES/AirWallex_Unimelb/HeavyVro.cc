#include "bits/stdc++.h"
 
using namespace std;
 
#define int64_t long long
#define sz(x) int(x.size())
 
class Heavy {
public:
 void solve() {
  int N, M;
  cin >> N >> M;
  vector<int> a(N);
  for (int i = 0, x; i < M; i++) {
   cin >> x;
   a[x - 1]++;
  }
  vector<int> ord(N);
  iota(ord.begin(), ord.end(), 0);
  sort(ord.begin(), ord.end(), [&](int i, int j) { return a[i] > a[j]; });
  
  int st = 0, ans = 0; 
  while(st + 1 < N) { 
   ans++; 
   st += a[ord[st]] + 1; 
  } 
  cout << ans + (st < sz(ord) && a[ord[st]] == 0) << '\n'; 
  return;
 }
};
 
int main(void) {
 Heavy problem;
 problem.solve();
 return 0;
}