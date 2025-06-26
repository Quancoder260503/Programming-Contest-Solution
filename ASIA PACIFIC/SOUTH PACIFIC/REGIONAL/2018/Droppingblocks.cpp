#include "bits/stdc++.h"

using namespace std;

#define sz(a) int(a.size())

int main(void){ 
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    int n; 
    cin >> n; 
    vector<int>a(n); 
    for(int i = 0; i < n; i++) { 
        cin >> a[i]; 
    }
    a.push_back(0);
    int64_t ret = 0; 
    for(int i = 0; i < n; i++) { 
        if(a[i] < ret) { 
            puts("NO");
            return 0; 
        }
        ret += max(a[i + 1] - a[i], 0); 
    }
    puts("YES"); 
    return 0; 
}