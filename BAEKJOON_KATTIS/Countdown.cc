#include "bits/stdc++.h"

using namespace std; 

#define sz(x) (int) x.size()

int main(void)
{
    int t; 
    cin >> t; 
    for(int tc = 0; tc < t; tc++) {  
        int n, k; 
        cin >> n >> k;
        vector<int>a(n); 
        for(int i = 0; i < n; i++) cin >> a[i];
        int ret = 0;
        for(int i = 0; i < n; i++)
        {
            if(a[i] != k) continue;
            int j = i + 1; 
            while(j < sz(a) && a[j - 1] > a[j]) j++; 
            ret += (i + k == j);  
            i = j - 1; 
        }
        printf("Case #%d: %d\n", tc + 1, ret); 
    }
    return 0; 
}