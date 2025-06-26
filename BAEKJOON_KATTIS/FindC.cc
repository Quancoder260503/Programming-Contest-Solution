#include "bits/stdc++.h"

using namespace std; 

#define x first
#define y second 
#define int64_t long long

using P = pair<int64_t, int64_t>; 

P euclid(int64_t A, int64_t B) { 
    if (!B) return {1, 0};
    P p = euclid(B, A % B);
    return {p.y, p.x - A / B * p.y};
}

void func(set<pair<int64_t, int64_t>>&ret, P a, P b, int64_t s, int k) {
    int64_t pa = a.y - b.y, pb = b.x - a.x, g = gcd(abs(pa), abs(pb));
    int64_t pc = s - (1LL * a.x * b.y - 1LL * a.y * b.x); 
    pa = pa / g;
    pb = pb / g; 
    pc = pc / g; 
    P p = euclid(abs(pa), abs(pb));
    if(abs(pb)) {
        p.x = p.x * (pc % abs(pb)) % abs(pb); 
        p.y = (pc - abs(pa) * p.x) / abs(pb); 
    } 
    else {
        p.y = p.y * (pc % abs(pa)) % abs(pa); 
        p.x = (pc - abs(pb) * p.y) / abs(pa); 
    }
    if(pa < 0) p.x = -p.x; 
    if(pb < 0) p.y = -p.y; 
    int64_t sx = (b.x - a.x) / g, sy = (b.y - a.y) / g; 
    for(int64_t x = p.x + sx, y = p.y + sy; ret.size() < k; x += sx, y += sy) { 
        ret.insert({x, y}); 
    } 
    for(int64_t x = p.x - sx, y = p.y - sy; ret.size() < k; x -= sx, y -= sy) { 
        ret.insert({x, y}); 
    } 
    return; 
}

int main(void) {
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    int tc, k; 
    cin >> tc;
    while(tc--) { 
        P a, b;  
        if(a.x > b.x) {swap(a, b); }
        cin >> a.x >> a.y >> b.x >> b.y >> k; 
        set<pair<int64_t, int64_t>>ret; 
        func(ret, a, b, gcd(abs(a.x - b.x), abs(a.y - b.y)), k); 
        func(ret, a, b, -gcd(abs(a.x - b.x), abs(a.y - b.y)), k); 
        for(auto v : ret) { 
            cout << v.x << " " << v.y << '\n'; 
        }
    }
    return 0; 
}