#include "bits/stdc++.h"

using namespace std; 

const int maxf = 2e5 + 10; 
const int INF = 1e9; 

int dyn[maxf][10], ndyn[maxf][10][10], arr[maxf], n, ctr[10]; 

int f(int pos, int k) { 
    if(pos == n - 1) return 0; 
    if(dyn[pos][k] != -1) return dyn[pos][k]; 
    int &ret = dyn[pos][k];
    ret = INF;
    for(int i = 0; i < 10; i++) { 
        if(abs(k - i) <= 1) ret = min(ret, f(pos + 1, i) + (arr[pos + 1] != i)); 
    }
    return ret; 
}

int g(int pos, int k, int l) { 
    if(pos == n - 1) return (l != 2 ? INF : 0); 
    if(ndyn[pos][k][l] != -1) return ndyn[pos][k][l];
    int &ret = ndyn[pos][k][l]; 
    ret = INF; 
    if(l < 2) { 
        for(int i = 0; i < 10; i++) { 
            if(abs(k - i) <= 1) ret = min(ret, g(pos + 1, i, l + 1) + (arr[pos + 1] != i));
        }
    }
    else { 
        for(int i = 0; i < 10; i++) { 
            if(abs(k - i) <= 1) ret = min(ret, g(pos + 1, i, 2) + (arr[pos + 1] != i)); 
            ret = min(ret, g(pos + 1, i, 0) + (arr[pos + 1] != i));
        }
    }
    return ret; 
}

int main(void) { 
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    cout.tie(NULL); 
    cin >> n; 
    for(int i = 0; i < n; i++) { 
        cin >> arr[i]; 
        ctr[arr[i]]++; 
    }
    memset(ndyn, -1, sizeof(ndyn)); 
    memset(dyn, -1, sizeof(dyn)); 
    int reta = INF, retb = INF, retc = INF; 
    for(int i = 0; i < 10; i++) { 
        reta = min(reta, g(0, i, 0) + (arr[0] != i));
    }
    for(int i = 0; i < 10; i++) { 
        retb = min(retb, f(0, i) + (arr[0] != i)); 
    }
    for(int i = 0; i < 10; i++) {
        retc = min(retc, n - ctr[i]); 
    }
    cout << reta << " " << retb << " " << retc << '\n'; 
    return 0; 
}