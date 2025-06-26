#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n; 
    cin >> n; 
    int ret = 0; 
    vector<int>a(n + 3), b(n + 3);
    for(int i = 2; i <= n + 1; i++) { 
        cin >> a[i] >> b[i]; 
        if(a[i - 2] && a[i - 1] && a[i] <= i - 3 && i - 1 <= b[i - 2]) { 
            a[i] = 0; 
            ret++; 
        }
    }
    cout << ret << '\n'; 
    return 0; 
}