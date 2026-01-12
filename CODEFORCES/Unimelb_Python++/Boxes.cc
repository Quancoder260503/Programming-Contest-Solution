#include "bits/stdc++.h"

using namespace std; 

const int64_t oo = LLONG_MAX / 4; 

struct Hull {
  vector<int64_t>a, b; 
  vector<double>x; 
  int head, tail;
  Hull(int N): head(1), tail(0) {
   a.resize(N); 
   b.resize(N); 
   x.resize(N); 
   return;  
  }

  int64_t get(int64_t xQuery) {
   if (head > tail) return 0;
   while (head < tail && x[head + 1] <= xQuery) head++;
   x[head] = xQuery;
   return a[head] * xQuery + b[head];
  }
  void add(int64_t aNew, int64_t bNew) {
   double xNew = -1e18;
   while (head <= tail) {
    if (aNew == a[tail]) return;
    xNew = 1.0 * (b[tail] - bNew) / (aNew - a[tail]);
    if (head == tail || xNew >= x[tail]) break;
    tail--;
   }
   a[++tail] = aNew;
   b[tail] = bNew;
   x[tail] = xNew;
   return; 
 }
};

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, K;
 cin >> N >> K; 
 vector<int>a(N + 1); 
 for(int i = 1; i <= N; i++) { 
  cin >> a[i];
 }
 reverse(a.begin() + 1, a.end()); 
 vector<int64_t>prefix(N + 1), prefix_2(N + 1), dp(N + 1, oo); 
 for(int i = 1; i <= N; i++) { 
  prefix[i] = a[i] + prefix[i - 1]; 
  prefix_2[i] = prefix[i] + prefix_2[i - 1]; 
 }
 dp[0] = 0; 
 Hull convex_hull(1000002); 
 convex_hull.add(0, 0); 
 for(int j = 1; j <= N; j++) { 
  dp[j] = prefix_2[j] + convex_hull.get(j);
  convex_hull.add(-prefix[j], dp[j] - prefix_2[j] + prefix[j] * j + K);  
 }
 cout << dp[N] << '\n'; 
 return 0; 
}