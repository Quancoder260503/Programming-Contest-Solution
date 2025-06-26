#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 10; 

bitset<maxf>dyn; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); 
    int n, k; 
    cin >> n >> k; 
    vector<int>a(n), vis(n), ctr(n + 1);
    for(int i = 0; i < n; i++) { 
        cin >> a[i];
        --a[i];  
    } 
    vector<int>cyc; 
    for(int i = 0; i < n; i++) { 
        if(vis[i]) continue;
        int len = 0; 
        int j = i; 
        while(!vis[j]) { 
            len++; 
            vis[j] = true; 
            j = a[j]; 
        }
        ctr[len]++; 
    }
    dyn[0] = 1; 
    vector<int>b(ctr.begin(), ctr.end()); 
    for(int i = 0; i < b.size(); i++) { 
        for(int j = 1; j <= b[i]; j = j * 2) { 
            dyn |= (dyn << (j * i)); 
            b[i] -= j; 
        }
        if(b[i] > 0) dyn |= (dyn << (b[i] * i)); 
    }
    cout << (dyn[k] ? k : k + 1) << " "; 
    int ret = 0, cc = k; 
    for(int i = 0; i < ctr.size(); i++) { 
        ret += ctr[i] * (i / 2); 
    }
    if(ret >= k) ret = min(n, 2 * k); 
    else ret = min(n, k + ret); 
    cout << ret << '\n'; 
    return 0; 
}