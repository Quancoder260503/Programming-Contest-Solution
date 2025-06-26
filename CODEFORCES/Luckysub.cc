#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int mod = 1e9 + 7;
const int MAXN = 1e6 + 10;
vector<lint> finv;
vector<lint> fac;
vector<lint> inv;
void binom_init()
{
   fac.resize(MAXN);
   finv.resize(MAXN);
   inv.resize(MAXN);
   fac[0] = fac[1] = 1;
   inv[1] = 1;
   finv[0] = finv[1] = 1;
   for (int i = 2; i < MAXN; i++)
   {
      fac[i] = fac[i - 1] * i % mod;
      inv[i] = mod - mod / i * inv[mod % i] % mod;
      finv[i] = finv[i - 1] * inv[i] % mod;
   }
}
lint C(lint n, lint r)
{
   if (n < r || n < 0 || r < 0)
      return 0;
   return (fac[n] * finv[r] % mod * finv[n - r] % mod) % mod;
}
signed main(void)
{
   int n, K;
   while (cin >> n >> K)
   {
      vector<int> arr(n);
      binom_init();
      auto chk = [&](int num)
      {
         vector<int> digit;
         while (num)
         {
            digit.push_back(num % 10);
            num = num / 10;
         }
         int good = 1;
         for (int i = 0; i < digit.size(); i++)
         {
            good = good & (digit[i] == 7 || digit[i] == 4);
         }
         return good;
      };
      vector<int> coord;
      int M = 0;
      for (int i = 0; i < n; i++)
      {
         cin >> arr[i];
         if (chk(arr[i]))
         {
            M++;
            coord.push_back(arr[i]);
         }
      }
      sort(coord.begin(), coord.end());
      coord.erase(unique(coord.begin(), coord.end()), coord.end());
      int N = coord.size();
      vector<int> cnt(N);
      for (int i = 0; i < n; i++)
      {
         if (chk(arr[i]))
         {
            int pos = lower_bound(coord.begin(), coord.end(), arr[i]) - coord.begin();
            cnt[pos]++;
         }
      }
      vector<vector<lint>> dyn(N + 1, vector<lint>(N + 1));
      dyn[0][0] = 1;
      for (int i = 0; i < N; i++)
      {
         for (int j = 0; j < N; j++)
         {
            dyn[i + 1][j]     = (dyn[i + 1][j]     + dyn[i][j] + mod) % mod;
            dyn[i + 1][j + 1] = (dyn[i + 1][j + 1] + 1LL * dyn[i][j] % mod * cnt[i] % mod + mod) % mod;
         }
      }
      lint ret = 0;
      for (int i = 0; i <= min(N, K); i++)
      {
         ret = (ret + 1LL * dyn[N][i] % mod * C(n - M, K - i) % mod + mod) % mod;
      }
      cout << ret << '\n';
   }
   return 0;
}