#include "bits/stdc++.h"

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

#define int64_t long long

using ll = long long;
using ull = unsigned long long; 
using ld = long double;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll get_rand(ll B) { return (ull)rng() % B; }
ll mult(ll x, ll y, ll md) {
  ull q = (ld)x * y / md;
  ll res = ((ull)x * y - q * md);
  if (res >= md) res -= md;
  if (res < 0) res += md;
  return res;
}

ll powMod(ll x, ll p, ll md) {
  if (p == 0) return 1;
  if (p & 1) return mult(x, powMod(x, p - 1, md), md);
  return powMod(mult(x, x, md), p / 2, md);
}

bool checkMillerRabin(ll x, ll md, ll s, int k) {
  x = powMod(x, s, md);
  if (x == 1) return true;
  while (k--) {
    if (x == md - 1) return true;
    x = mult(x, x, md);
    if (x == 1) return false;
  }
  return false;
}
bool isPrime(ll x) {
  if (x == 2 || x == 3 || x == 5 || x == 7) return true;
  if (x % 2 == 0 || x % 3 == 0 || x % 5 == 0 || x % 7 == 0) return false;
  if (x < 121) return x > 1;
  ll s = x - 1;
  int k = 0;
  while (s % 2 == 0) {
    s >>= 1;
    k++;
  }
  if (x < 1LL << 32) {
    for (ll z : {2, 7, 61}) {
      if (!checkMillerRabin(z, x, s, k)) return false;
    }
  } else {
    for (ll z : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
      if (!checkMillerRabin(z, x, s, k)) return false;
    }
  }
  return true;
}

ll gcd(ll x, ll y) { return y == 0 ? x : gcd(y, x % y); }

void pollard(ll x, vector<ll> &ans) {
  if (isPrime(x)) {
    ans.push_back(x);
    return;
  }
  ll c = 1;
  while (true) {
    c = 1 + get_rand(x - 1);
    auto f = [&](ll y) {
      ll res = mult(y, y, x) + c;
      if (res >= x) res -= x;
      return res;
    };
    ll y = 2;
    int B = 100;
    int len = 1;
    ll g = 1;
    while (g == 1) {
      ll z = y;
      for (int i = 0; i < len; i++) {
        z = f(z);
      }
      ll zs = -1;
      int lft = len;
      while (g == 1 && lft > 0) {
        zs = z;
        ll p = 1;
        for (int i = 0; i < B && i < lft; i++) {
          p = mult(p, abs(z - y), x);
          z = f(z);
        }
        g = gcd(p, x);
        lft -= B;
      }
      if (g == 1) {
        y = z;
        len <<= 1;
        continue;
      }
      if (g == x) {
        g = 1;
        z = zs;
        while (g == 1) {
          g = gcd(abs(z - y), x);
          z = f(z);
        }
      }
      if (g == x) break;
      assert(g != 1);
      pollard(g, ans);
      pollard(x / g, ans);
      return;
    }
  }
}
// return list of all prime factors of x (can have duplicates)
vector<ll> factorize(ll x) {
  vector<ll> ans;
  for (ll p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}) {
    while (x % p == 0) {
      x /= p;
      ans.push_back(p);
    }
  }
  if (x != 1) {
    pollard(x, ans);
  }
  sort(ans.begin(), ans.end());
  return ans;
}
// return pairs of (p, k) where x = product(p^k)
vector<pair<ll, int>> factorize_pk(ll x) {
  auto ps = factorize(x);
  ll last = -1, cnt = 0;
  vector<pair<ll, int>> res;
  for (auto p : ps) {
    if (p == last)
      ++cnt;
    else {
      if (last > 0) res.emplace_back(last, cnt);
      last = p;
      cnt = 1;
    }
  }
  if (cnt > 0) {
    res.emplace_back(last, cnt);
  }
  return res;
}

int main(void) {
  int64_t N;
  cin >> N;
  int64_t M = N;
  while (M % 4 == 0) { M = M / 4; }
  if (M % 8 == 7) {
    cout << "-1\n";
    return 0;
  }
  int sqrtN = (int) sqrt(N); 
  if(N % 3 == 0) { 
    int64_t cc = N / 3; 
    int x = (int) sqrt(cc); 
    if(1LL * x * x == cc) { 
     cout << x << " " << x << " " << x << '\n'; 
    }
    exit(0); 
  }
  for(int x = 0; x <= sqrtN; x++) { 
   int64_t ys = N - 1LL * x * x; // either y is sum of 2 squares or a squares itself 
   vector<pair<int64_t, int>>factor = factorize_pk(ys); 
   int isSquared = true, specialPrime = true; 
   int counter = 0; 
   for(auto [u, v] : factor) { 
    isSquared = isSquared & (v % 2 == 0); 
    specialPrime = specialPrime & (u % 4 == 1 || u == 2); 
   }
   if(isSquared) { 
    cout << x << " " << (int) sqrt(ys) << " " << 0 << '\n'; 
    return 0; 
   }
   if(specialPrime) {
    for(int y = x; 1LL * y * y <= ys; y++)  { 
     int64_t zs = ys - 1LL * y * y; 
     int z = (int) sqrt(zs); 
     if(1LL * z * z == zs) { 
      cout << x << " " << y << " " << z << '\n'; 
      exit(0); 
     }
    }
   }
  }
  return 0;
}