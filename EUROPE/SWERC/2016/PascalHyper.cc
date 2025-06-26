#include "bits/stdc++.h"

using namespace std; 

const int maxf = 35; 

__int128_t fact[maxf]; 
vector<int64_t>ret; 

void doit(int h, int d, int lh, __int128_t c) { 
    if(d == 0) { 
        if(h == 0) ret.push_back(c); 
        return; 
    }
    for(int i = 0; i <= min(h, lh); i++) { 
        doit(h - i, d - 1, i, c / fact[i]); 
    }
    return; 
}

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    int d, h; 
    cin >> d >> h;
    fact[0] = 1; 
    for(int i = 1; i < maxf; i++){
        fact[i] = fact[i - 1] * i; 
    } 
    --h; 
    doit(h, d, h, fact[h]); 
    sort(ret.begin(), ret.end());
    ret.erase(unique(ret.begin(), ret.end()), ret.end());
    for(auto r : ret) cout << r << '\n'; 
    return 0; 
}