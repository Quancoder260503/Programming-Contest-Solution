#include "bits/stdc++.h"

using namespace std; 

template <int64_t mod,int64_t factor>
struct Hash{
  int64_t value = 0;
  void add(int64_t x){
    value = (int64_t)((value * (__int128) factor + x) % (__int128) mod);
  }
  Hash operator+(Hash const &other) const {
    return {(value + other.value) % mod};
  }
  Hash operator-(Hash const &other) const {
    return {(mod + value - other.value) % mod};
  }
  Hash operator * (int64_t const by) const {
    return {(int64_t)((value* (__int128) by) % (__int128) mod)};
  }
  bool operator == (Hash const &other) const {
    return value == other.value;
  }
  bool operator < (Hash const &other)  const {
    return value < other.value;
  }
};

struct Hashes{
  Hash<6660000000001ll,251429ll> a;
  Hash<2345678911111111ll,11111117ll> b;
  Hash<9999999900000001ll,16431563ll> c;
  void add(int64_t const x){
    a.add(x);
    b.add(x);
    c.add(x);
  }
  bool operator==(Hashes const &other)const{
    return a==other.a and b==other.b and c==other.c;
  }
  Hashes operator+(Hashes const &other)const{
    return {a+other.a,b+other.b,c+other.c};
  }
  Hashes operator-(Hashes const &other)const{
    return {a-other.a,b-other.b,c-other.c};
  }
  bool operator<(Hashes const &other)const{
    return a==other.a? b==other.b? c<other.c: b<other.b: a<other.a;
  }
  Hashes operator*(int const by)const{
    return {a*by,b*by,c*by};
  }
  friend ostream &operator<<(ostream &os, Hashes p)
  {
    return os << "(" << p.a. value << ", " << p.b.value << ", " << p.c.value << ")";
  }
};

namespace std{
  template<>
  struct hash<Hashes>{
    size_t operator()(Hashes const &k)const{
      return k.a.value^k.b.value^k.c.value;
    }
  };
}

int main(void) {
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    int n, r, c; 
    cin >> r >> c >> n;
    vector<Hashes>arr(r); 
    for(int i = 0; i < r; i++) {
        vector<int>freq(n + 1); 
        for(int j = 0, x; j < c; j++) { 
            cin >> x; 
            freq[x]++;
        }
        for(int j = 1; j <= n; j++) {
            arr[i].add(freq[j]); 
        } 
    }
    vector<pair<Hashes, int>>mp; 
    int L = r / 2, R = r - L; 
    for(int mask = 0; mask < (1 << L); mask++) { 
        Hashes hsum; 
        for(int i = 0; i < L; i++) if(mask & (1 << i)) { 
            hsum = hsum + arr[i]; 
        } 
        mp.push_back({hsum, __builtin_popcount(mask)}); 
    }
    sort(mp.begin(), mp.end()); 
    vector<Hashes>cc;
    Hashes base; 
    for(int i = 1; i <= n; i++) { 
        base.add(1); 
    }
    for(int i = 1; i <= r; i++) { 
        if((i * c) % n == 0) { 
            cc.push_back(base * (i * c / n)); 
        }
    }
    int ret = 0; 
    for(int mask = 0; mask < (1 << R); mask++) { 
        Hashes hsum2; 
        for(int i = 0; i < R; i++) if(mask & (1 << i)) {
            hsum2 = hsum2 + arr[L + i]; 
        }
        for(auto &x : cc) {
            auto it = lower_bound(mp.begin(), mp.end(), make_pair(x - hsum2, -1));
            if(it != mp.end() && it->first == x - hsum2) {
                ret = max(ret, it->second + __builtin_popcount(mask));  
            } 
        }
    }
    cout << ret << '\n'; 
    return 0; 
}