#include "bits/stdc++.h"

using namespace std;

#define ll long long 

struct Station { 
 int diag;
 int need;
 long long cost;
 int limit;
};

int main() {
 ios::sync_with_stdio(false);
 cin.tie(nullptr);
 int n, m;
 cin >> n >> m;
 vector<Station> a(m);
 for (int i = 0; i < m; i++) {
  int r, c, p, l;
  cin >> r >> c >> p >> l;
  a[i] = {r + c, min(r, c), p, l};
 } 
 sort(a.begin(), a.end(), [](auto &x, auto &y) {
   return x.diag < y.diag;
 });
 priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
 ll robots = 1;
 ll total_cost = 0;
 int ptr = 0;
 for (int d = 2; d <= 2 * n; d++) {
  ll required;
  if (d <= n + 1) required = d - 1;
  else required = 2 * n - d + 1;
  while (robots < required) {
   if (pq.empty()) {
    cout << "Impossible\n";
    return 0;
   }
   auto [cost, cnt] = pq.top();
   pq.pop();
   total_cost += cost;
   robots++;
   if (cnt > 1) pq.push({cost, cnt - 1});
  } 
  while (ptr < m && a[ptr].diag <= d && a[ptr].need <= robots) {
   pq.push({a[ptr].cost, a[ptr].limit});
   ptr++;
  } 
 }
 cout << "Possible\n" << total_cost << "\n";
 return 0;
}
