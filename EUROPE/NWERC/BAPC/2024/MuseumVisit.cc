#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int64_t oo = 1e17; 

struct Tree {
 typedef int64_t T;
 static constexpr T unit = oo;
 T f(T a, T b) { return min(a, b); }  // (any associative fn)
 vector<T> s;
 int n;
 Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
 void update(int pos, T val) { 
  s[pos += n] = val;  
  for (; pos /= 2;) s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
 }
 T query(int b, int e) {  // query [b, e)
  T ra = unit, rb = unit;
  for (b += n, e += n; b < e; b /= 2, e /= 2) {
   if (b % 2) ra = f(ra, s[b++]);
   if (e % 2) rb = f(s[--e], rb);
  }
  return f(ra, rb);
 }
};

int main(void) { 
 ios_base::sync_with_stdio(false);  
 cin.tie(0); 
 cout.tie(0); 
 int N, M;
 cin >> N >> M; 
 vector<int>a(N); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
 }
 a.push_back(0); 
 vector<array<int, 2>>interval(M); 
 for(int i = 0; i < M; i++) { 
  cin >> interval[i][0] >> interval[i][1];
  interval[i][0]--; 
 }
 sort(interval.begin(), interval.end()); 
 vector<pair<int, int>>monotone; 
 for(int i = 0; i < sz(interval); i++) { 
  while(sz(monotone) && monotone.back().second >= interval[i][1]) { 
   monotone.pop_back(); 
  }
  monotone.emplace_back(interval[i][0], interval[i][1]); 
 }
 vector<int>cnt(N + 1); 
 for(int i = 0; i < sz(monotone); i++) { 
  cnt[monotone[i].second]++; 
 }
 partial_sum(cnt.begin(), cnt.end(), cnt.begin()); 
 Tree tree(N + 2); 
 vector<int64_t>dp(N + 1);
 for(int i = 0; i <= N; i++) { 
  if(cnt[i] == 0) { 
    tree.update(i, a[i]); 
  } else { 
    int pos = monotone[cnt[i] - 1].first; 
    dp[i] = a[i] + tree.query(pos, i); 
    tree.update(i, dp[i]); 
  }
 } 
 cout << dp[N] << '\n'; 
 return 0; 
}