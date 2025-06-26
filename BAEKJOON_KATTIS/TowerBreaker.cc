#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    int tc; 
    cin >> tc; 
    for(int j = 1; j <= tc; j++) { 
        int n; 
        cin >> n;
        int ret = 0; 
        for(int i = 0, x; i < n; i++) { 
            cin >> x; 
            int ctr = 0; 
            for(int j = 2; j * j <= x; j++) { 
                while(x % j == 0) { 
                    x = x / j; 
                    ctr++;
                }
            }
            if(x > 1) ctr++; 
            ret = ret ^ ctr;    
        }
        cout << (ret ? 1 : 2) << '\n'; 
    }
    return 0; 
}
