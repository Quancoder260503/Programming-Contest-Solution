#include "bits/stdc++.h"

using namespace std; 

#define f first
#define s second 
#define int64_t long long

pair<int64_t, int64_t> euclid(int64_t A, int64_t B)
{ 
    if (!B) return {1, 0};
    pair<int64_t, int64_t> p = euclid(B, A % B);
    return {p.s, p.f - A / B * p.s};
}
int64_t inv(int64_t A, int64_t B)
{ 
    pair<int64_t, int64_t> p = euclid(A, B);
    assert(p.f * A + p.s * B == 1);
    return p.f + (p.f < 0) * B;
} 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    int n, q;
    int64_t x = 1, y = 0;  
    cin >> n >> q;
    vector<int>a(n); 
    iota(a.begin(), a.end(), 0); 
    for(int _ = 0; _ < q; _++) { 
        char c; int j;  
        cin >> c >> j; 
        if(c == '+') { 
            y = (y + j) % n;
        }
        else if(c == '*') { 
            int64_t nx = x * j % n, ny = y * j % n; 
            if(gcd(x, n) != gcd(nx, n)) { 
                vector<vector<pair<int, int>>>b(n);
                for(int i = 0; i < n; i++) { 
                    int src = (x * i + y) % n, to = (nx * i + ny) % n; 
                    int dist = to - src; 
                    if(dist < 0) dist += n; 
                    if(a[i] != i) dist = n + 1; 
                    b[to].push_back({dist, i}); 
                } 
                for(int i = 0; i < n; i++) if(b[i].size()) { 
                    int mn = (*min_element(b[i].begin(), b[i].end())).second; 
                    for(auto [_, p] : b[i]) a[p] = mn; 
                }
            }
            x = nx, y = ny; 
        }
        else { 
            int64_t g = gcd(x, n); 
            if((j - y) % g == 0) {
                int at = ((j - y) / g) * inv(x / g, n / g) % n;
                at = a[(at + n) % n];  
                if(!at) at += n;  
                cout << at << '\n'; 
            } 
            else cout << -1 << '\n'; 
        }
    }
    return 0; 
}