#include "bits/stdc++.h"

using namespace std; 

const int maxf = 2e6 + 10; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n; 
    cin >> n;
    cout << n << ": \n";  
    for(int i = 2; i < n; i++) { 
        for(int j = i - 1; j <= i; j++) {
            if(n % (i + j) == 0 || n % (i + j) == i) { 
                cout << i << "," << j << '\n'; 
            }
        }
    }
    return 0; 
}