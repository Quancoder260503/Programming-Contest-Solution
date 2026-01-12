#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <utility>
#include <map>

#define ll long long

using namespace std;

int main(void) {
 int n;
 cin >> n;
 vector<ll>a(n), prefix(n + 1);
 for(int i = 0; i < n; i++) {
  cin >> a[i];
  prefix[i + 1] = a[i] + prefix[i];
 }
 ll sum = prefix.back();
 map<ll, ll>cnt;
 cnt[0]++;
 ll ans = 0;
 for(int i = 1; i <= n; i++) {
  ans += cnt[prefix[i] * n - sum * i];
  cnt[prefix[i] * n - sum * i]++;
 }
 cout << ans << '\n';
 // sum / n = (p[i] - p[j]) / (i - j)
 // sum * (i - j) + n * p[j] = n * p[i]
  return 0;
}
