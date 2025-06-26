#include "bits/stdc++.h"

using namespace std;

const int maxf = 8e3 + 2;

int64_t dyn[803][maxf], prefix[maxf];
int n, m; 

int64_t cost(int i, int j) { 
    return 1LL * (prefix[j] - prefix[i - 1]) * (j - i + 1); 
}

void DP(int l, int r, int optl, int optr, int now) { 
    if(l > r) return; 
    int mid = (l + r) / 2; 
    pair<int64_t, int>best = {INT64_MAX, -1}; 
    for(int i = optl; i <= min(mid, optr); i++) { 
        best = min(best, {dyn[now - 1][i - 1] + cost(i, mid), i});
    }
    dyn[now][mid] = best.first;
    int opt = best.second; 
    DP(l, mid - 1, optl, opt, now);
    DP(mid + 1, r, opt, optr, now);
    return;  
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    cin >> n >> m; 
    for(int i = 1, x; i <= n; i++) { 
        cin >> x;  
        prefix[i] = prefix[i - 1] + x; 
    } 
    for(int i = 1; i <= n; i++) { 
        dyn[0][i] = cost(1, i); 
    }
    for(int i = 1; i < m; i++) DP(1, n, 1, n, i);  
    cout << dyn[m - 1][n] << '\n'; 
    return 0;
}