#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr); 
    int n;
    cin >> n; 
    vector<int>a(n + 1);
    for(int i = 1; i <= n; i++) { 
        cin >> a[i]; 
    }
    int res = 2; 
    for (int i = 1; i <= n; i += 2) {
        int start = i;
        while (i + 2 <= n) {
            if (abs(a[i] - a[i + 2]) == 2 || a[i] == a[i + 2]) i += 2; 
            else break;
        }
        int c = i - start + 1; 
        if (i < n) c++;
        if (start > 1) c++;
        res = max(res, c); 
    }
    cout << res << '\n';
    return 0;
}