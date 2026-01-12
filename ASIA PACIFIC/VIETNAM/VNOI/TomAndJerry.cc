#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <map>

#define sz(x) int(x.size())


using namespace std;

const int maxn = 1e5 + 10;
 
/*
map<pair<int, int>, int>mp;

int Grundy(int s, int k) {
 if(s == 0) return 0;
 if(mp.count({s, k})) return mp[{s, k}];
 unordered_set<int>ms;
 for(int j = 1; j <= min(s, k); j++) {
  ms.insert(Grundy(s - j, k));
 }
 int ret = 0;
 while(ms.count(ret)) ret++;
 return mp[{s, k}] = ret;
}
*/

int main(void) {
 int n, C;
 for(cin >> C; C--; ) {
  cin >> n;
  int ret = 0;
  vector<int>a(n), b(n);
  for(auto &x : a) cin >> x;
  for(auto &x : b) cin >> x;
  for(int i = 0; i < n; i++) {
   ret = ret ^ (a[i] % (b[i] + 1));
  }
  cout << (ret ? "Jerry" : "Tom") << '\n';
 }
 return 0;
}
