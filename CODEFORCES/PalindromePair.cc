#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

using ll = long long;

const int maxn = 2e5 + 2;
const ll MOD_A = 1e9 + 9;
const ll MOD_B = 1e9 + 7;
const ll BASE_A = 443;
const ll BASE_B = 479;

ll apow[maxn], bpow[maxn];

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 apow[0] = bpow[0] = 1;
 for(int i = 1; i < maxn; i++) {
  apow[i] = (apow[i - 1] * BASE_A) % MOD_A;
  bpow[i] = (bpow[i - 1] * BASE_B) % MOD_B;
 }
 int n;
 cin >> n;
 map<pair<ll, ll>, ll>mp;
 ll ans = 0;
 for(int i = 0; i < n; i++) {
  string s;
  cin >> s;
  vector<int>cnt(26);
  for(int j = 0; j < s.size(); j++) cnt[s[j] - 'a']++;
  pair<ll, ll>ret = {0, 0};
  for(int j = 0; j < 26; j++) {
   cnt[j] %= 2;
   (ret.first  += apow[j + 1] * (cnt[j] + 1) % MOD_A) %= MOD_A;
   (ret.second += bpow[j + 1] * (cnt[j] + 1) % MOD_B) %= MOD_B;
  }
  ans += mp[ret];
  for(int j = 0; j < 26; j++) {
   if(cnt[j] == 1) {
    (ret.first  += MOD_A - apow[j + 1] * (cnt[j] + 1) % MOD_A) %= MOD_A;
    (ret.second += MOD_B - bpow[j + 1] * (cnt[j] + 1) % MOD_B) %= MOD_B;
    cnt[j]--;
    (ret.first  += apow[j + 1] * (cnt[j] + 1) % MOD_A) %= MOD_A;
    (ret.second += bpow[j + 1] * (cnt[j] + 1) % MOD_B) %= MOD_B;
    ans += mp[ret];
    (ret.first  += MOD_A - apow[j + 1] * (cnt[j] + 1) % MOD_A) %= MOD_A;
    (ret.second += MOD_B - bpow[j + 1] * (cnt[j] + 1) % MOD_B) %= MOD_B;
     cnt[j]++;
    (ret.first  += apow[j + 1] * (cnt[j] + 1) % MOD_A) %= MOD_A;
    (ret.second += bpow[j + 1] * (cnt[j] + 1) % MOD_B) %= MOD_B;
   } else {
    (ret.first  += MOD_A - apow[j + 1] * (cnt[j] + 1) % MOD_A) %= MOD_A;
    (ret.second += MOD_B - bpow[j + 1] * (cnt[j] + 1) % MOD_B) %= MOD_B;
    cnt[j]++;
    (ret.first  += apow[j + 1] * (cnt[j] + 1) % MOD_A) %= MOD_A;
    (ret.second += bpow[j + 1] * (cnt[j] + 1) % MOD_B) %= MOD_B;
    cnt[j]++;
    ans += mp[ret];
    (ret.first  += MOD_A - apow[j + 1] * (cnt[j] + 1) % MOD_A) %= MOD_A;
    (ret.second += MOD_B - bpow[j + 1] * (cnt[j] + 1) % MOD_B) %= MOD_B;
    cnt[j]--;
    (ret.first  += apow[j + 1] * (cnt[j] + 1) % MOD_A) %= MOD_A;
    (ret.second += bpow[j + 1] * (cnt[j] + 1) % MOD_B) %= MOD_B;
   }
  }
  mp[ret]++;
 }
 cout << ans << '\n';
 return 0;
}
