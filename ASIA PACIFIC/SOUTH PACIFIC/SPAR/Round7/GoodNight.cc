#include "bits/stdc++.h"

using namespace std;

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#define sz(x) int(x.size())
#define int64_t long long

using type = int64_t; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int64_t n, m, T; 
 cin >> n >> m >> T; 
 cout << (1LL * lcm(n, m) <= T ? "yes" : "no") << '\n'; 
 return 0; 
}