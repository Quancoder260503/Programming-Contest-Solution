#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); 
    long long sum = 0; 
    vector<long long>skill(4);  
    for(int i = 0; i < 4; i++) { 
        cin >> skill[i]; 
        sum += skill[i]; 
    }
    long long ret = LLONG_MAX; 
    for(int mask = 0; mask < (1 << 4); mask++) {    
        int bit = 0; 
        long long sumA = 0; 
        for(int i = 0; i < 4; i++) if((mask & (1 << i)) != 0) { 
            sumA += skill[i]; 
            bit++; 
        }
        if(bit != 2) continue; 
        long long sumB = sum - sumA; 
        ret = min(ret, abs(sumA - sumB)); 
    }
    cout << ret << '\n';  
    return 0; 
}