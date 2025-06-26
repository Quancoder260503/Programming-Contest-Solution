#include "bits/stdc++.h"

using namespace std; 

int is_prime(int x) { 
    for(int y = 2; y * y <= x; y++) if(x % y == 0) {
        return false;
    }
    return true; 
}

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    int N; 
    cin >> N; 
    while(!is_prime(N)){
        N--; 
    }
    cout << N << '\n'; 
    return 0; 
}