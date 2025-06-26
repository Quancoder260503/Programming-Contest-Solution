#include "bits/stdc++.h"

using namespace std; 

#define sz(x) (int) x.size()

int main(int argc, char **argv){
    int64_t n, p, k; 
    cin >> n >> p >> k; 
    vector<int64_t>ret; 
    for(int64_t i = 1; i * i <= n; i++){
        if(n % i == 0) { 
            int64_t j = n / i; 
            if(i <= k && j <= p) ret.push_back(j);  
            if(i == j) continue; 
            if(j <= k && i <= p) ret.push_back(i); 
        }
    }
    cout << sz(ret) << '\n'; 
    sort(ret.begin(), ret.end()); 
    for(auto c : ret) cout << c << '\n'; 
    return 0; 
}