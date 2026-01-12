#include "bits/stdc++.h"

using namespace std; 

#define double long double 

const double oo = 1e40; 

struct CHT {
 deque<pair<double, double> > dq;
 double value(pair<double, double> l, double x) {
  return l.first * x + l.second;   
 }
 bool better(pair<double, double> L, pair<double, double> L1, pair<double, double> L2) {
  return (L2.second - L.second) * (L1.first - L2.first) <= (L.first - L2.first) * (L2.second - L1.second);
 }
 void init() {
  dq.clear();
  dq.push_back({0, 0});
 }
 void add(double m, double b) {
  while((int)dq.size() >= 2 && better({m, b}, dq[dq.size() - 1], dq[dq.size() - 2])) dq.pop_back();
  dq.push_back({m, b});
 }
 double query(double x) {
   while((int)dq.size() >= 2 && value(dq[0], x) < value(dq[1], x)) dq.pop_front();
   return value(dq.front(), x);
 }
}; 
  

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, K;
 cin >> N >> K; 
 vector<double>prefix(N + 1), prefix_inv(N + 1), prefix_div(N + 1), dp(N + 1, oo); 
 double x; 
 for(int i = 1; i <= N; i++) { 
  cin >> x; 
  prefix_inv[i] = prefix_inv[i - 1] + 1. / x; 
  prefix[i] = prefix[i - 1] + x; 
  prefix_div[i] = prefix_div[i - 1] + prefix[i] / x; 
 }
 CHT convex_hull; 
 dp[0] = 0; 
 for(int c = 0; c < K; c++) {
  convex_hull.init();   
  vector<double>ndp(N + 1, oo); 
  for(int i = 1; i <= N; i++) { 
   ndp[i] = min(dp[i], prefix_div[i] - convex_hull.query(prefix_inv[i])); 
   convex_hull.add(prefix[i], -dp[i] - prefix[i] * prefix_inv[i] + prefix_div[i]); 
  }
  dp.swap(ndp); 
 }
 cout << fixed << setprecision(10) << dp[N] << '\n'; 
 return 0; 
}