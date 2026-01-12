#include "bits/stdc++.h"

using namespace std;

const int oo = 1e9;

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0); 
 cout.tie(0);
 int n;
 cin >> n;
 vector<int>a; 
 for(int i = 0, x; i < n; i++) {
  cin >> x;
  if(x) a.push_back(x);
 }
 n = a.size();
 vector<int>prefix(n), suffix(n);
 prefix[0] = a[0];
 for(int i = 1; i < n; i++) {
  prefix[i] = gcd(prefix[i - 1], a[i]);
 }
 suffix.back() = a.back();
 for(int i = n - 2; i >= 0; i--) {
  suffix[i] = gcd(suffix[i + 1], a[i]);
 }
 int ret = 0;
 for(int i = 0; i < n; i++) {
  if(i == 0) ret = max(ret, suffix[i + 1]);
  else if(i == n - 1) ret = max(ret, prefix[i - 1]);  
  else ret = max(ret, gcd(suffix[i + 1], prefix[i - 1]));
 }
 cout << ret << '\n';
 return 0;
}
