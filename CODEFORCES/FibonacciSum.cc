#include "bits/stdc++.h"

using namespace std;

const int maxf = 92; 

int64_t fib[maxf]; 
map<int64_t, int>ret; 
int digit[maxf]; 
int dyn[maxf][2]; 

int64_t f(int64_t x) { 
    if(ret.count(x)) return ret[x]; 
    for(int i = maxf - 1; i >= 0; i--) { 
        digit[i] = (x >= fib[i]); 
        if(x >= fib[i]) x = x - fib[i]; 
    }
    dyn[0][1] = 1; 
    int last = 0; 
    for(int i = 1, length = 0; i < maxf; i++) { 
        length++; 
        if(digit[i]) { 
            dyn[i][1] = 1LL * (dyn[last][0] + dyn[last][1]);  
            dyn[i][0] = 1LL * dyn[last][1] * ((length - 1) / 2) + 1LL * dyn[last][0] * (length / 2); 
            length = 0; 
            last = i; 
        }
    }
    return ret[x] = dyn[last][1] + dyn[last][0];
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    fib[0] = fib[1] = 1;
    for (int i = 2; i < maxf; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    int tc;
    cin >> tc;
    for (int i = 0; i < tc; i++) {
        int64_t x;
        cin >> x;
        cout << f(x) << '\n';
    }
    return 0;
}