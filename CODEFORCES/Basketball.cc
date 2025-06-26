#include "bits/stdc++.h"

using namespace std; 

#define sz(x) (int) x.size()

int main(void){
    int n, m, h; 
    cin >> n >> m >> h; 
    --h; 
    int sum = 0, ss; 
    for(int i = 0; i < m; i++) {
        double s; 
        cin >> s; 
        if(i == h) ss = s;  
        sum += s; 
    }
    if(sum < n) {
        puts("-1"); 
        return 0; 
    }
    double ret = 1.0; 
    sum--, n--, ss--; 
    for(int i = 1; i <= n; i++) { 
        ret = ret * (sum - ss - n + i) / (sum - n + i); 
    }
    ret = 1.0 - ret; 
    cout << fixed << setprecision(10) << ret << '\n'; 
    return 0; 
}