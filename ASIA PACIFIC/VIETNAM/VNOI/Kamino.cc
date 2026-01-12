#include "bits/stdc++.h"

using namespace std; 

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

template <class T>
constexpr T infty = 0;
template <>
constexpr int infty<int> = 1'000'000'000;
template <>
constexpr ll infty<ll> = ll(infty<int>) * infty<int> * 2;
template <>
constexpr u32 infty<u32> = infty<int>;
template <>
constexpr u64 infty<u64> = infty<ll>;
template <>
constexpr i128 infty<i128> = i128(infty<ll>) * infty<ll>;
template <>
constexpr double infty<double> = infty<ll>;
template <>
constexpr long double infty<long double> = infty<ll>;

using pi = pair<ll, ll>;
using vi = vector<ll>;
template <class T>
using vc = vector<T>;
template <class T>
using vvc = vector<vc<T>>;
template <class T>
using vvvc = vector<vvc<T>>;
template <class T>
using vvvvc = vector<vvvc<T>>;
template <class T>
using vvvvvc = vector<vvvvc<T>>;
template <class T>
using pq = priority_queue<T>;
template <class T>
using pqg = priority_queue<T, vector<T>, greater<T>>;

#define vv(type, name, h, ...) \
  vector<vector<type>> name(h, vector<type>(__VA_ARGS__))
#define vvv(type, name, h, w, ...)   \
  vector<vector<vector<type>>> name( \
      h, vector<vector<type>>(w, vector<type>(__VA_ARGS__)))
#define vvvv(type, name, a, b, c, ...)       \
  vector<vector<vector<vector<type>>>> name( \
      a, vector<vector<vector<type>>>(       \
             b, vector<vector<type>>(c, vector<type>(__VA_ARGS__))))

// https://trap.jp/post/1224/
#define FOR1(a) for (ll _ = 0; _ < ll(a); ++_)
#define FOR2(i, a) for (ll i = 0; i < ll(a); ++i)
#define FOR3(i, a, b) for (ll i = a; i < ll(b); ++i)
#define FOR4(i, a, b, c) for (ll i = a; i < ll(b); i += (c))
#define FOR1_R(a) for (ll i = (a)-1; i >= ll(0); --i)
#define FOR2_R(i, a) for (ll i = (a)-1; i >= ll(0); --i)
#define FOR3_R(i, a, b) for (ll i = (b)-1; i >= ll(a); --i)
#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...) d
#define FOR(...) overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...) overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

#define FOR_subset(t, s) \
  for (ll t = (s); t >= 0; t = (t == 0 ? -1 : (t - 1) & (s)))
#define all(x) x.begin(), x.end()
#define len(x) ll(x.size())
#define elif else if

#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second

#define stoi stoll

int popcnt(int x) { return __builtin_popcount(x); }
int popcnt(u32 x) { return __builtin_popcount(x); }
int popcnt(ll x) { return __builtin_popcountll(x); }
int popcnt(u64 x) { return __builtin_popcountll(x); }
int popcnt_mod_2(int x) { return __builtin_parity(x); }
int popcnt_mod_2(u32 x) { return __builtin_parity(x); }
int popcnt_mod_2(ll x) { return __builtin_parityll(x); }
int popcnt_mod_2(u64 x) { return __builtin_parityll(x); }
// (0, 1, 2, 3, 4) -> (-1, 0, 1, 1, 2)
int topbit(int x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(u32 x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(ll x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
int topbit(u64 x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
// (0, 1, 2, 3, 4) -> (-1, 0, 1, 0, 2)
int lowbit(int x) { return (x == 0 ? -1 : __builtin_ctz(x)); }
int lowbit(u32 x) { return (x == 0 ? -1 : __builtin_ctz(x)); }
int lowbit(ll x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }
int lowbit(u64 x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }

template <typename T>
T floor(T a, T b) {
  return a / b - (a % b && (a ^ b) < 0);
}
template <typename T>
T ceil(T x, T y) {
  return floor(x + y - 1, y);
}
template <typename T>
T bmod(T x, T y) {
  return x - y * floor(x, y);
}
template <typename T>
pair<T, T> divmod(T x, T y) {
  T q = floor(x, y);
  return {q, x - q * y};
}

template <typename T, typename U>
T SUM(const vector<U> &A) {
  T sm = 0;
  for (auto &&a: A) sm += a;
  return sm;
}

#define MIN(v) *min_element(all(v))
#define MAX(v) *max_element(all(v))
#define LB(c, x) distance((c).begin(), lower_bound(all(c), (x)))
#define UB(c, x) distance((c).begin(), upper_bound(all(c), (x)))
#define UNIQUE(x) \
  sort(all(x)), x.erase(unique(all(x)), x.end()), x.shrink_to_fit()

template <typename T>
T POP(deque<T> &que) {
  T a = que.front();
  que.pop_front();
  return a;
}
template <typename T>
T POP(pq<T> &que) {
  T a = que.top();
  que.pop();
  return a;
}
template <typename T>
T POP(pqg<T> &que) {
  T a = que.top();
  que.pop();
  return a;
}
template <typename T>
T POP(vc<T> &que) {
  T a = que.back();
  que.pop_back();
  return a;
}

template <typename F>
ll binary_search(F check, ll ok, ll ng, bool check_ok = true) {
  if (check_ok) assert(check(ok));
  while (abs(ok - ng) > 1) {
    auto x = (ng + ok) / 2;
    (check(x) ? ok : ng) = x;
  }
  return ok;
}
template <typename F>
double binary_search_real(F check, double ok, double ng, int iter = 100) {
  FOR(iter) {
    double x = (ok + ng) / 2;
    (check(x) ? ok : ng) = x;
  }
  return (ok + ng) / 2;
}

template <class T, class S>
inline bool chmax(T &a, const S &b) {
  return (a < b ? a = b, 1 : 0);
}
template <class T, class S>
inline bool chmin(T &a, const S &b) {
  return (a > b ? a = b, 1 : 0);
}

// ? は -1
vc<int> s_to_vi(const string &S, char first_char) {
  vc<int> A(S.size());
  FOR(i, S.size()) { A[i] = (S[i] != '?' ? S[i] - first_char : -1); }
  return A;
}

template <typename T, typename U>
vector<T> cumsum(vector<U> &A, int off = 1) {
  int N = A.size();
  vector<T> B(N + 1);
  FOR(i, N) { B[i + 1] = B[i] + A[i]; }
  if (off == 0) B.erase(B.begin());
  return B;
}

// stable sort
template <typename T>
vector<int> argsort(const vector<T> &A) {
  vector<int> ids(len(A));
  iota(all(ids), 0);
  sort(all(ids),
       [&](int i, int j) { return (A[i] == A[j] ? i < j : A[i] < A[j]); });
  return ids;
}

// A[I[0]], A[I[1]], ...
template <typename T>
vc<T> rearrange(const vc<T> &A, const vc<int> &I) {
  vc<T> B(len(I));
  FOR(i, len(I)) B[i] = A[I[i]];
  return B;
}


#line 1 "library/other/io.hpp"
#define FASTIO
#include <unistd.h>

// https://judge.yosupo.jp/submission/21623
namespace fastio {
static constexpr uint32_t SZ = 1 << 17;
char ibuf[SZ];
char obuf[SZ];
char out[100];
// pointer of ibuf, obuf
uint32_t pil = 0, pir = 0, por = 0;

struct Pre {
  char num[10000][4];
  constexpr Pre() : num() {
    for (int i = 0; i < 10000; i++) {
      int n = i;
      for (int j = 3; j >= 0; j--) {
        num[i][j] = n % 10 | '0';
        n /= 10;
      }
    }
  }
} constexpr pre;

inline void load() {
  memcpy(ibuf, ibuf + pil, pir - pil);
  pir = pir - pil + fread(ibuf + pir - pil, 1, SZ - pir + pil, stdin);
  pil = 0;
  if (pir < SZ) ibuf[pir++] = '\n';
}

inline void flush() {
  fwrite(obuf, 1, por, stdout);
  por = 0;
}

void rd(char &c) {
  do {
    if (pil + 1 > pir) load();
    c = ibuf[pil++];
  } while (isspace(c));
}

void rd(string &x) {
  x.clear();
  char c;
  do {
    if (pil + 1 > pir) load();
    c = ibuf[pil++];
  } while (isspace(c));
  do {
    x += c;
    if (pil == pir) load();
    c = ibuf[pil++];
  } while (!isspace(c));
}

template <typename T>
void rd_real(T &x) {
  string s;
  rd(s);
  x = stod(s);
}

template <typename T>
void rd_integer(T &x) {
  if (pil + 100 > pir) load();
  char c;
  do
    c = ibuf[pil++];
  while (c < '-');
  bool minus = 0;
  if constexpr (is_signed<T>::value || is_same_v<T, i128>) {
    if (c == '-') { minus = 1, c = ibuf[pil++]; }
  }
  x = 0;
  while ('0' <= c) { x = x * 10 + (c & 15), c = ibuf[pil++]; }
  if constexpr (is_signed<T>::value || is_same_v<T, i128>) {
    if (minus) x = -x;
  }
}

void rd(int &x) { rd_integer(x); }
void rd(ll &x) { rd_integer(x); }
void rd(i128 &x) { rd_integer(x); }
void rd(u32 &x) { rd_integer(x); }
void rd(u64 &x) { rd_integer(x); }
void rd(u128 &x) { rd_integer(x); }
void rd(double &x) { rd_real(x); }
void rd(long double &x) { rd_real(x); }
void rd(f128 &x) { rd_real(x); }

template <class T, class U>
void rd(pair<T, U> &p) {
  return rd(p.first), rd(p.second);
}
template <size_t N = 0, typename T>
void rd_tuple(T &t) {
  if constexpr (N < std::tuple_size<T>::value) {
    auto &x = std::get<N>(t);
    rd(x);
    rd_tuple<N + 1>(t);
  }
}
template <class... T>
void rd(tuple<T...> &tpl) {
  rd_tuple(tpl);
}

template <size_t N = 0, typename T>
void rd(array<T, N> &x) {
  for (auto &d: x) rd(d);
}
template <class T>
void rd(vc<T> &x) {
  for (auto &d: x) rd(d);
}

void read() {}
template <class H, class... T>
void read(H &h, T &... t) {
  rd(h), read(t...);
}

void wt(const char c) {
  if (por == SZ) flush();
  obuf[por++] = c;
}
void wt(const string s) {
  for (char c: s) wt(c);
}
void wt(const char *s) {
  size_t len = strlen(s);
  for (size_t i = 0; i < len; i++) wt(s[i]);
}

template <typename T>
void wt_integer(T x) {
  if (por > SZ - 100) flush();
  if (x < 0) { obuf[por++] = '-', x = -x; }
  int outi;
  for (outi = 96; x >= 10000; outi -= 4) {
    memcpy(out + outi, pre.num[x % 10000], 4);
    x /= 10000;
  }
  if (x >= 1000) {
    memcpy(obuf + por, pre.num[x], 4);
    por += 4;
  } else if (x >= 100) {
    memcpy(obuf + por, pre.num[x] + 1, 3);
    por += 3;
  } else if (x >= 10) {
    int q = (x * 103) >> 10;
    obuf[por] = q | '0';
    obuf[por + 1] = (x - q * 10) | '0';
    por += 2;
  } else
    obuf[por++] = x | '0';
  memcpy(obuf + por, out + outi + 4, 96 - outi);
  por += 96 - outi;
}

template <typename T>
void wt_real(T x) {
  ostringstream oss;
  oss << fixed << setprecision(15) << double(x);
  string s = oss.str();
  wt(s);
}

void wt(int x) { wt_integer(x); }
void wt(ll x) { wt_integer(x); }
void wt(i128 x) { wt_integer(x); }
void wt(u32 x) { wt_integer(x); }
void wt(u64 x) { wt_integer(x); }
void wt(u128 x) { wt_integer(x); }
void wt(double x) { wt_real(x); }
void wt(long double x) { wt_real(x); }
void wt(f128 x) { wt_real(x); }

template <class T, class U>
void wt(const pair<T, U> val) {
  wt(val.first);
  wt(' ');
  wt(val.second);
}
template <size_t N = 0, typename T>
void wt_tuple(const T t) {
  if constexpr (N < std::tuple_size<T>::value) {
    if constexpr (N > 0) { wt(' '); }
    const auto x = std::get<N>(t);
    wt(x);
    wt_tuple<N + 1>(t);
  }
}
template <class... T>
void wt(tuple<T...> tpl) {
  wt_tuple(tpl);
}
template <class T, size_t S>
void wt(const array<T, S> val) {
  auto n = val.size();
  for (size_t i = 0; i < n; i++) {
    if (i) wt(' ');
    wt(val[i]);
  }
}
template <class T>
void wt(const vector<T> val) {
  auto n = val.size();
  for (size_t i = 0; i < n; i++) {
    if (i) wt(' ');
    wt(val[i]);
  }
}

void print() { wt('\n'); }
template <class Head, class... Tail>
void print(Head &&head, Tail &&... tail) {
  wt(head);
  if (sizeof...(Tail)) wt(' ');
  print(forward<Tail>(tail)...);
}

// gcc expansion. called automaticall after main.
void __attribute__((destructor)) _d() { flush(); }
} // namespace fastio
using fastio::read;
using fastio::print;
using fastio::flush;

#define INT(...)   \
  int __VA_ARGS__; \
  read(__VA_ARGS__)
#define LL(...)   \
  ll __VA_ARGS__; \
  read(__VA_ARGS__)
#define U32(...)   \
  u32 __VA_ARGS__; \
  read(__VA_ARGS__)
#define U64(...)   \
  u64 __VA_ARGS__; \
  read(__VA_ARGS__)
#define STR(...)      \
  string __VA_ARGS__; \
  read(__VA_ARGS__)
#define CHAR(...)   \
  char __VA_ARGS__; \
  read(__VA_ARGS__)
#define DBL(...)      \
  double __VA_ARGS__; \
  read(__VA_ARGS__)

#define VEC(type, name, size) \
  vector<type> name(size);    \
  read(name)
#define VV(type, name, h, w)                     \
  vector<vector<type>> name(h, vector<type>(w)); \
  read(name)

void YES(bool t = 1) { print(t ? "YES" : "NO"); }
void NO(bool t = 1) { YES(!t); }
void Yes(bool t = 1) { print(t ? "Yes" : "No"); }
void No(bool t = 1) { Yes(!t); }
void yes(bool t = 1) { print(t ? "yes" : "no"); }
void no(bool t = 1) { yes(!t); }


struct has_mod_impl {
  template <class T>
  static auto check(T &&x) -> decltype(x.get_mod(), std::true_type{});
  template <class T>
  static auto check(...) -> std::false_type;
};

template <class T>
class has_mod : public decltype(has_mod_impl::check<T>(std::declval<T>())) {};

template <typename mint>
mint inv(int n) {
  static const int mod = mint::get_mod();
  static vector<mint> dat = {0, 1};
  assert(0 <= n);
  if (n >= mod) n %= mod;
  while (len(dat) <= n) {
    int k = len(dat);
    int q = (mod + k - 1) / k;
    dat.eb(dat[k * q - mod] * mint::raw(q));
  }
  return dat[n];
}

template <typename mint>
mint fact(int n) {
  static const int mod = mint::get_mod();
  assert(0 <= n && n < mod);
  static vector<mint> dat = {1, 1};
  while (len(dat) <= n) dat.eb(dat[len(dat) - 1] * mint::raw(len(dat)));
  return dat[n];
}

template <typename mint>
mint fact_inv(int n) {
  static vector<mint> dat = {1, 1};
  if (n < 0) return mint(0);
  while (len(dat) <= n) dat.eb(dat[len(dat) - 1] * inv<mint>(len(dat)));
  return dat[n];
}

template <class mint, class... Ts>
mint fact_invs(Ts... xs) {
  return (mint(1) * ... * fact_inv<mint>(xs));
}

template <typename mint, class Head, class... Tail>
mint multinomial(Head &&head, Tail &&... tail) {
  return fact<mint>(head) * fact_invs<mint>(std::forward<Tail>(tail)...);
}

template <typename mint>
mint C_dense(int n, int k) {
  static vvc<mint> C;
  static int H = 0, W = 0;
  auto calc = [&](int i, int j) -> mint {
    if (i == 0) return (j == 0 ? mint(1) : mint(0));
    return C[i - 1][j] + (j ? C[i - 1][j - 1] : 0);
  };
  if (W <= k) {
    FOR(i, H) {
      C[i].resize(k + 1);
      FOR(j, W, k + 1) { C[i][j] = calc(i, j); }
    }
    W = k + 1;
  }
  if (H <= n) {
    C.resize(n + 1);
    FOR(i, H, n + 1) {
      C[i].resize(W);
      FOR(j, W) { C[i][j] = calc(i, j); }
    }
    H = n + 1;
  }
  return C[n][k];
}

template <typename mint, bool large = false, bool dense = false>
mint C(ll n, ll k) {
  assert(n >= 0);
  if (k < 0 || n < k) return 0;
  if constexpr (dense) return C_dense<mint>(n, k);
  if constexpr (!large) return multinomial<mint>(n, k, n - k);
  k = min(k, n - k);
  mint x(1);
  FOR(i, k) x *= mint(n - i);
  return x * fact_inv<mint>(k);
}

template <typename mint, bool large = false>
mint C_inv(ll n, ll k) {
  assert(n >= 0);
  assert(0 <= k && k <= n);
  if (!large) return fact_inv<mint>(n) * fact<mint>(k) * fact<mint>(n - k);
  return mint(1) / C<mint, 1>(n, k);
}

// [x^d](1-x)^{-n}
template <typename mint, bool large = false, bool dense = false>
mint C_negative(ll n, ll d) {
  assert(n >= 0);
  if (d < 0) return mint(0);
  if (n == 0) { return (d == 0 ? mint(1) : mint(0)); }
  return C<mint, large, dense>(n + d - 1, d);
}

template <int mod>
struct modint {
  static constexpr u32 umod = u32(mod);
  static_assert(umod < u32(1) << 31);
  u32 val;

  static modint raw(u32 v) {
    modint x;
    x.val = v;
    return x;
  }
  constexpr modint() : val(0) {}
  constexpr modint(u32 x) : val(x % umod) {}
  constexpr modint(u64 x) : val(x % umod) {}
  constexpr modint(u128 x) : val(x % umod) {}
  constexpr modint(int x) : val((x %= mod) < 0 ? x + mod : x){};
  constexpr modint(ll x) : val((x %= mod) < 0 ? x + mod : x){};
  constexpr modint(i128 x) : val((x %= mod) < 0 ? x + mod : x){};
  bool operator<(const modint &other) const { return val < other.val; }
  modint &operator+=(const modint &p) {
    if ((val += p.val) >= umod) val -= umod;
    return *this;
  }
  modint &operator-=(const modint &p) {
    if ((val += umod - p.val) >= umod) val -= umod;
    return *this;
  }
  modint &operator*=(const modint &p) {
    val = u64(val) * p.val % umod;
    return *this;
  }
  modint &operator/=(const modint &p) {
    *this *= p.inverse();
    return *this;
  }
  modint operator-() const { return modint::raw(val ? mod - val : u32(0)); }
  modint operator+(const modint &p) const { return modint(*this) += p; }
  modint operator-(const modint &p) const { return modint(*this) -= p; }
  modint operator*(const modint &p) const { return modint(*this) *= p; }
  modint operator/(const modint &p) const { return modint(*this) /= p; }
  bool operator==(const modint &p) const { return val == p.val; }
  bool operator!=(const modint &p) const { return val != p.val; }
  modint inverse() const {
    int a = val, b = mod, u = 1, v = 0, t;
    while (b > 0) {
      t = a / b;
      swap(a -= t * b, b), swap(u -= t * v, v);
    }
    return modint(u);
  }
  modint pow(ll n) const {
    assert(n >= 0);
    modint ret(1), mul(val);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }
  static constexpr int get_mod() { return mod; }
  // (n, r), r は 1 の 2^n 乗根
  static constexpr pair<int, int> ntt_info() {
    if (mod == 167772161) return {25, 17};
    if (mod == 469762049) return {26, 30};
    if (mod == 754974721) return {24, 362};
    if (mod == 880803841) return {23, 211};
    if (mod == 943718401) return {22, 663003469};
    if (mod == 998244353) return {23, 31};
    if (mod == 1045430273) return {20, 363};
    if (mod == 1051721729) return {20, 330};
    if (mod == 1053818881) return {20, 2789};
    return {-1, -1};
  }
  static constexpr bool can_ntt() { return ntt_info().fi != -1; }
};

#ifdef FASTIO
template <int mod>
void rd(modint<mod> &x) {
  fastio::rd(x.val);
  assert(0 <= x.val && x.val < mod);
}
template <int mod>
void wt(modint<mod> x) {
  fastio::wt(x.val);
}
#endif

using modint107 = modint<1000000007>;
using modint998 = modint<998244353>;

// 1<<20
int factorial998table[1024] = {1,467742124,703158536,849331177,183632821,786787592,708945888,623860151,442444797,339076928,916211838,827641482,982515753,303461550,466748179,669060208,789885751,915736046,189957301,934038903,728735046,774755699,649374308,602288735,492352484,958678776,943233257,148504501,352124178,569334038,927469492,343841688,432351202,700916755,170721982,8283809,875807278,931632987,330722936,603566523,391470976,157944106,826756015,278928878,178606531,522053153,175494307,16217485,310769109,430912024,970167731,302127847,960178710,607169580,211863227,918097328,664502958,598427325,415194799,38321157,375608821,557298612,497769749,114695383,77784134,629192790,339438380,348348875,713806860,526342541,671850855,414726935,844082152,412454739,351143550,868784407,834684152,186057224,996072584,619190001,24770542,765280770,513490122,468949120,867194196,866447292,937135640,560788103,308335177,703539315,252044620,119916775,298069903,43651994,148641017,730387621,856452172,74265901,626807500,980602375,42825068,348086475,162321900,207340584,151258454,461547160,320321845,361026143,882876292,842563318,257705870,158156446,292795459,984763947,917068833,811332379,782439665,944504775,298167161,141501910,155584237,149720256,71954352,666430555,580966229,884747116,616367471,918981127,310328833,724405658,383796145,256700166,487819118,642491144,181867555,524937737,222137750,445244561,79921588,253457448,405659726,260707689,740044210,654653354,229885020,230551611,616689587,939003921,565960348,904184966,133298693,859220865,186139683,765071679,247651638,451157944,929341123,503724944,768266737,142218056,910573117,274579400,151387843,212671109,815271666,406331931,154251304,642676789,570372925,976277122,442985463,928799971,817581666,797627351,100113334,877639265,541537097,434482347,300960222,270085755,481153328,236088097,686884498,323505794,897572220,900787550,277507290,157634146,892066519,616420589,46056764,697140618,592483685,896871487,896388868,106444279,115102765,191484323,62322499,434613622,426026852,378184205,194359325,415197585,965735328,598860936,653751428,942602959,475099103,642401460,77868208,464952529,549976420,705774928,635299526,704085554,809044086,670938184,799176916,58985566,402328281,182103192,921913660,674272214,428301920,520916749,127424638,296779896,166780239,19634060,95873539,708947606,532272305,980167862,7015847,370183454,45567119,866949818,374428494,25583689,351370758,835388325,232690098,42002598,17055285,985022727,214528454,122907290,793349516,609331634,87133548,248246624,448572380,502875867,183097664,536117329,170926160,381772251,37038194,374439881,94285547,880631489,452052533,739811514,675382782,587926712,179133902,694266603,338843576,281485671,813341519,616512705,222785194,382494725,471654428,961907947,442140830,702296161,548575377,388901073,19119024,545916498,947169254,801677200,377657430,634980290,246239186,13175103,239754689,656729178,364003283,646568868,584909084,690387116,452007054,131381944,908149670,807287523,802277179,745423153,893994782,197548253,376096720,105840336,687751559,170787791,928507410,620382696,446955151,139665212,882526402,494793004,107171423,753993075,467588754,207595897,269813018,941027990,856873596,717085190,245280646,792026805,548741735,523767341,637697735,261200153,89666563,344573088,15832984,558492246,825051585,923222974,826620400,558080789,657328927,991078225,706029275,738905108,401212366,980043233,895405022,597894231,636951913,947342478,786075225,395095090,188433847,121279219,860403973,396099425,240442489,521535558,280382318,58023116,735594008,8696133,477645338,223630480,816606673,680021043,362424474,181667447,504295826,332167472,766361494,992840497,417671938,376941230,11880047,275790726,106186450,150546053,966438917,431896075,158021876,734833661,328332504,632143386,962477966,638741189,728804571,753715698,20536106,45105841,271673172,982138522,604809222,199722980,211807634,478008419,194715230,246865373,316443541,869035744,202922168,245262975,136244583,650969410,566222746,55188168,495968583,571946805,188658038,353720239,830419870,669127165,86710835,810103736,630008035,764354348,209246227,277861984,725469211,151404581,894191013,775554083,634671016,170299187,471849450,575347258,505276194,636730506,40086858,386228700,789875034,998219457,359035788,843760715,864829665,794240359,241486050,48334220,583177582,714653706,617669563,132782021,779225352,333301287,520569296,508276228,689073648,573645847,200419842,911561316,310562870,204959007,879280837,762843188,103128368,133300147,648946778,287218789,662474952,587555465,105622721,648151526,517033362,729251452,850555187,708613432,874408867,345608416,690718720,10813958,42384375,882264058,825490058,252850511,652942840,202604098,277615259,862885671,582470925,190843016,534488148,187675153,911660635,377262012,642854978,359397276,712333871,580131409,841639861,925383257,213683380,25291651,974815450,32032244,119030165,443676106,555727293,170519648,171131074,839941962,789829593,140975543,845347712,303299112,530420097,857005350,249174130,224087061,311280308,404814306,567648772,766512373,470895965,294358155,625218604,89534510,513216330,78173719,22818060,254922573,292417477,415060121,208989124,960117615,570018845,237661008,442774488,871349246,161574942,548661451,313471555,448096394,587422360,987939533,254478574,113844945,268886375,927289435,664834607,983476167,390569280,363763327,935767957,159015901,508613041,134148582,127417680,484767855,825835285,43847241,972918293,151969014,768480291,729490470,76727400,384998943,648970509,764966281,391326774,585299643,661473977,530021579,368308424,81083443,981417794,185781362,169555925,934957641,56005264,296483160,853982963,489694611,73207251,20297311,431253211,168162850,36271383,689526671,397669110,705876730,785504919,764896820,936514026,350141918,784778738,682324919,140913543,862125900,723248565,369074340,146936534,226913694,277886748,856792647,13654547,141461269,255233971,979535193,747662027,452683681,338311679,399620140,306913085,817524367,333578440,943193170,387930488,964713035,554372227,524201507,267870305,698863503,695139108,399857384,830659092,479624682,594238820,768224890,956955770,940576967,920740072,282055556,621677930,847367415,619094041,432519599,192780811,912052381,263304046,114280963,307107320,956809356,118706101,836710721,356893069,427113038,55360495,892694364,443807400,568616581,130165565,732273554,778059496,95936679,629634134,383940143,474733431,271200931,253893765,65679204,670721645,268831988,225698685,424701963,654858732,405695790,894299102,797306377,464723449,647679843,730366154,956550665,898568348,313188681,661403769,346715295,358990430,868898456,719464962,978551995,772931269,255694712,379904456,393101377,130818973,810783770,78951115,608848341,941552927,523163696,581658405,188869913,161971620,114600913,300038465,126906968,572973411,118017645,806069307,430432761,310699012,989119052,282768145,557792692,611036992,427168405,84497995,529589599,967936672,416953197,549641787,787274930,514952744,646568513,39329263,765390776,831388678,299074396,102522509,886062498,598990751,553048069,305737423,388746841,13007805,3445560,568306294,109543305,847740132,746222360,454654676,748993028,222910140,861308982,390243513,692742883,789475199,153430402,299806798,913070840,881332402,245792511,618823409,1817990,897836424,726794141,700802042,472214481,97004031,479899815,573979309,752576644,374801082,599964908,894966385,178103304,12240556,393873628,855241924,305678131,971858774,281586141,87362107,41844894,175133514,276243521,997376957,260427125,439339251,64661516,362212695,186181824,423316311,267640938,299252572,810040987,857956827,758991665,207700847,399398818,747579039,814755712,298373935,307448236,42074518,982127624,538863790,528558929,96501138,813255509,611769398,710541518,408153968,675346745,970094012,791931126,811516976,618049736,264048084,209805699,909045292,645349311,416989597,590393407,320547207,342653696,860169617,856611053,475149267,124801433,547187333,466598598,266454901,554467907,868909135,199244107,548833449,20952517,234169026,117025205,804238552,205574540,590283297,822322644,866010856,477388420,935768507,424373916,951967787,344871828,133969287,937034425,309380768,666909962,726492795,996576193,883938945,869749688,313581344,65216237,88860786,208895640,888760811,854567609,328142793,121852766,928690075,135269006,333105486,502240551,573712984,397698082,935117672,718828733,440474396,335628894,184935718,788258676,646732201,68099895,167036421,362572358,787671392,666366534,193503119,74429287,132805884,796935846,124574194,926012440,147265585,722608579,526866610,452261307,990444071,4595579,147427028,774597449,678783012,568563934,383628463,68242206,163493293,352851801,123192034,529859554,14733470,565063217,178575398,580871309,135817500,313966456,647215844,118781836,106243172,796669460,48496927,772979683,715961917,546863206,601711799,644312478,629259662,738295002,692301787,149995411,864799423,284186171,246177326,268779154,86400350,518698490,321709079,946212693,800553099,865864136,244789848,386206318,851633075,713794602,131117952,280474884,243820970,820033654,399700655,825581574,443639603,774376660,362476217,552383080,436759518,538430048,965968656,150434699,563163603,352073025,840124972,152029247,902082055,770264937,747653807,934664232,541451013,807031739,854866728,503502641,283479207,297947602,488469464,205196166,381583984,108455782,570592132,363674728,134077711,356931610,887112858,273780969,443297964,650953636,402662299,894089640,71844431,33030748,208583995,597099208,671156881,875032178,998244352,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int factorial998(ll n) {
  constexpr int mod = 998244353;
  if (n >= mod) return 0;
  auto [q, r] = divmod<int>(n, 1 << 20);
  ll x = factorial998table[q];
  int s = q << 20;
  FOR(i, r) x = x * (s + i + 1) % mod;
  return x;
}

using mint = modint998;

const int MOD = 998244353;
const int maxn = 1e6 + 5000; 

int64_t mod_pow(int64_t a, int64_t b, int64_t p) { 
 int64_t res = 1;
 while (b > 0) {
  if (b & 1) res = (res * a) % p;
  a = (a * a) % p;
  b >>= 1;
 }
 return res;
}

int64_t mod_inv(int64_t a, int64_t p) { return mod_pow(a % p, p - 2, p); }

int bit[maxn]; 

void update(int x, int val) { 
 for(x++; x < maxn; x += x & (-x)) { 
  bit[x] += val; 
 }
 return; 
}

int query(int x) { 
 int ret = 0; 
 for(x++; x > 0; x -= x & (-x)) { 
  ret += bit[x]; 
 }
 return ret; 
}

int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(nullptr);
  cout.tie(nullptr); 
  int n;
  cin >> n;
  vector<int> h(n), dp(n);
  for (int i = 0; i < n; i++) {
    cin >> h[i];
  }
  vector<int>coord(h.begin(), h.end()); 
  sort(coord.begin(), coord.end()); 
  for(int i = 0; i < n; i++) { 
   h[i] = lower_bound(coord.begin(), coord.end(), h[i]) - coord.begin() + 1; 
  }
  int64_t total = 0; 
  for(int i = 0; i < n; i++) { 
   dp[i] = query(maxn) - query(h[i]); 
   update(h[i], 1); 
   total += dp[i]; 
  }
  int64_t ret = factorial998(total), fact = 1; 
  vector<int64_t>ifact(n + 1);
  ifact[0] = 1;  
  for(int i = 1; i <= n; i++) { 
   fact = fact * i % MOD; 
   ifact[i] = mod_inv(fact, MOD); 
  }
  for(int i = 0; i < n; i++) { 
   ret = ret % MOD * ifact[dp[i]] % MOD; 
  } 
  cout << ret << '\n'; 
  return 0;
}
