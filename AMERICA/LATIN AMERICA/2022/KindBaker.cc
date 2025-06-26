#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int k; 
    cin >> k; 
    if(k == 1) { 
        cout << 0 << '\n'; 
        return 0; 
    }
    const int N = 100; 
    int ret = 1, pw = 1, dim = 0; 
    while(pw < k) { pw = pw * 2; dim++; } 
    int r = dim / 2, c = (dim + 1) / 2; 
    vector<vector<pair<int, int>>>group(N * N + 1); 
    vector<vector<int>>a(N, vector<int>(N)); 
    vector<int>cc(N * N + 1, 0); 
    cc[0] = N * N; 
    auto done = [&](void) { 
        for(int x = 0; x < dim; x++) 
        for(int i = 0; i < N; i++) 
        for(int j = 0; j < N; j++) if(a[i][j] & (1 << x)) {
            group[x].push_back({i + 1, j + 1});  
        }
        cout << dim << '\n'; 
        for(int x = 0; x < dim; x++) { 
            cout << group[x].size() << " "; 
            for(auto [xa, ya] : group[x]) cout << xa << " " << ya << " "; 
            cout << '\n'; 
        }
        exit(0); 
    }; 
    for(int x = 0; x < dim; x++) 
    for(int i = 0; i < N; i++) 
    for(int j = 0; j < N; j++) if(i == 0 || j == 0) { 
        ret = ret - (cc[a[i][j]] == 1); 
        cc[a[i][j]]--; 
        a[i][j] |= (1 << x);
        ret = ret + (cc[a[i][j]] == 0); 
        cc[a[i][j]]++;  
        if(ret == k) { done(); }
    }
    for(int x = 0; x < r; x++) 
    for(int i = 1; i < N; i++) 
    for(int j = 1; j < N; j++) if(i & (1 << x)) { 
        ret = ret - (cc[a[i][j]] == 1); 
        cc[a[i][j]]--; 
        a[i][j] |= (1 << x);
        ret = ret + (cc[a[i][j]] == 0); 
        cc[a[i][j]]++;  
        if(ret == k) { done(); }
    }
    for(int y = 0; y < c; y++) 
    for(int i = 1; i < N; i++) 
    for(int j = 1; j < N; j++) if(j & (1 << y)) { 
        ret = ret - (cc[a[i][j]] == 1); 
        cc[a[i][j]]--; 
        a[i][j] |= (1 << (r + y));
        ret = ret + (cc[a[i][j]] == 0); 
        cc[a[i][j]]++;  
        if(ret == k) { done(); }
    }
    return 0; 
}