#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n, l; 
    cin >> n >> l;
    vector<int>loc(n); 
    for(int i = 0; i < n; i++) { 
        cin >> loc[i];
    }
    sort(loc.begin(), loc.end()); 
    int ret = 0; 
    l = l * 5; 
    for(int i = 0; i < n; i++) { 
        if(l >= loc[i]) { 
            l = l - loc[i];
            ret++; 
        }
        else break; 
    }
    cout << ret << '\n'; 
    return 0; 
}