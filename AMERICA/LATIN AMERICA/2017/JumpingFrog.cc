#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int) x.size()

const int maxf = 1e5 + 10;
int ctr[maxf]; 

int main(void) { 
    string s; 
    cin >> s;
    int n = sz(s); 
    for(int i = 1; i < n; i++) ctr[gcd(i, n)]++; 
    int ret = 0; 
    for(int j = 1; j < n; j++) { 
        if(!ctr[j]) continue; 
        int chk = 0; 
        for(int i = 0; i < j; i++) { 
            if(s[i] == 'P') continue; 
            int nxt_i = (i + j) % n; 
            chk = 1; 
            while(nxt_i != i) { 
                if(s[nxt_i] == 'P') { 
                    chk = 0; 
                    break; 
                }
                nxt_i = (nxt_i + j) % n; 
            }
            if(chk) break; 
        }
        if(chk) ret += ctr[j]; 
    }
    cout << ret << '\n'; 
    return 0; 
}