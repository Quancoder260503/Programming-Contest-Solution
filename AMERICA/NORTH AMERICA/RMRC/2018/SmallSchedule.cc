#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    int Q, M, S, L; 
    cin >> Q >> M >> S >> L;
    vector<int>a(M); 
    for(int i = 0; i < L; i++) { 
        a[i % M] += Q; 
    }
    for(int i = 1; i < M; i++) { 
        if(a[i] != a[i - 1]) {
            a[i] = a[i - 1];  
            S = S - Q; 
        }
    }
    for(int i = 0; S > 0; i = (i + 1) % M, S--) { 
        a[i]++; 
    }
    cout << *max_element(a.begin(), a.end()) << '\n'; 
    return 0; 
}