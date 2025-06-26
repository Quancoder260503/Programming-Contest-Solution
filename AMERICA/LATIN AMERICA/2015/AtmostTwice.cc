#include "bits/stdc++.h"

using namespace std;

int64_t dyn[19][60000][2]; 
int64_t pw3[15]; 
const int64_t oo = LLONG_MAX / 2; 
string S; 

int64_t memo(int pos, int mask, int smaller) { 
    if(pos == S.size()) return (smaller ? 0 : -oo); 
    int64_t &ret = dyn[pos][mask][smaller];
    if(ret != -1) return ret;
    ret = 0;
    vector<int>ctr(10); 
    int nmask = mask; 
    for(int digit = 0; digit < 10; digit++) { 
        ctr[digit] = nmask % 3; 
        nmask  = (nmask - nmask % 3) / 3; 
    } 
    for(int digit = 0; digit < 10; digit++) { 
        int state, c = S[pos] - '0'; 
        if(digit < c )      state = true; 
        else if(digit == c) state = smaller; 
        else                state = false; 
        if(ctr[digit] < 2) { 
            int64_t next = memo(pos + 1, mask + pw3[digit], state); 
            if(next == -oo) continue; 
            ret = max(ret, 10 * next + digit);  
        }
    }
    return ret;  
}

int main(void) { 
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0); 
    memset(dyn, -1, sizeof(dyn)); 
    cin >> S; 
    reverse(S.begin(), S.end()); 
    pw3[0] = 1; 
    for(int i = 1; i < 15; i++) { 
        pw3[i] = 3 * pw3[i - 1]; 
    }
    cout << memo(0, 0, true) << '\n'; 
    return 0; 
}



/*
  dyn[i][mask][leading_zero] is the maximum number that use digits appears in the mask of length i 
*/