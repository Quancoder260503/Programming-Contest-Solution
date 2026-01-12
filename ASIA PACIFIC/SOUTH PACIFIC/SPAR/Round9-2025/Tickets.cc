#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <cstring> 

using namespace std;

#define ll long long

const ll oo = 1e12;
const int maxn = 3005;

ll dp[maxn][maxn][2], a[maxn];
int n, b;

ll memo(int pos, int num_a, int curr_theater) {
 if(pos == n) return 0;
 ll &ret = dp[pos][num_a][curr_theater];
 if(ret != -1) return ret;
 ret = oo;
 int num_b = pos - num_a;
 if(curr_theater) {
  if(num_a + 1 <= b) ret = min(ret, memo(pos + 1, num_a + 1, curr_theater));
  if(num_b + 1 <= b) ret = min(ret, a[pos] + memo(pos + 1, num_a, !curr_theater));
 } else {
  if(num_a + 1 <= b) ret = min(ret, a[pos] + memo(pos + 1, num_a + 1, !curr_theater));
  if(num_b + 1 <= b) ret = min(ret, memo(pos + 1, num_a, curr_theater));
 }
 return ret;
}

int main(void) {
 cin >> n >> b;
 for(int i = 0; i < n; i++) {
  cin >> a[i];
 }
 memset(dp, -1, sizeof dp);
 cout << min(memo(0, 0, 0), memo(0, 0, 1)) << '\n';
 return 0;
}
