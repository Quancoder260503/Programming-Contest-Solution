#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n; 
    cin >> n;
    vector<int>a(n); 
    for(int i = 0; i < n; i++) { 
        cin >> a[i]; 
    }
    int mx_so_far = 0, mn_so_far = INT32_MAX; 
    vector<int>vis(n), vis2(n); 
    for(int i = 0; i < n; i++) { 
        if(mx_so_far < a[i]) {
            vis[i] = true;  
        }
        mx_so_far = max(mx_so_far, a[i]); 
    }
    for(int i = n - 1; i >= 0; i--) { 
        if(mn_so_far > a[i]) { 
            vis2[i] = true; 
        }
        mn_so_far = min(mn_so_far, a[i]); 
    }
    int ret = 0; 
    for(int i = 0; i < n; i++) if(vis[i] && vis2[i]) { 
        ret++; 
    } 
    cout << ret << ' '; 
    int ctr = 0; 
    for(int i = 0; i < n; i++) if(vis[i] && vis2[i]) {
        cout << a[i] << " "; 
        ctr++;
        if(ctr == 100) break;  
    }
    return 0; 
}