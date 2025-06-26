#include "bits/stdc++.h"

using namespace std;

int main(void) {
    int tc, N, M;
    tc = 1; 
    while(tc--) {
        cin >> N >> M;
        int sum, i, x; 
        for(sum = 0, i = 0; i < N; i++) { 
            cin >> x;
            if(sum + x > M) break;  
            sum += x;
        } 
        cout << i << '\n'; 
    }
    return 0;
}