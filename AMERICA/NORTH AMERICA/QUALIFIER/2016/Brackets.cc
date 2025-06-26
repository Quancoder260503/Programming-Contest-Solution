#include "bits/stdc++.h"

using namespace std; 

const int N = 5002; 

int dyn[N][N][2]; 
string s; 

int memo(int pos, int open, int finish) { 
    if(open  < 0) return 0; 
    if(pos == s.size()) return (open == 0); 
    int &ret = dyn[pos][open][finish]; 
    if(ret != -1) return ret; 
    ret = false; 
    if(!finish) {
        ret |= memo(pos + 1, open + (s[pos] == '(' ? -1 : 1), false); 
        ret |= memo(pos + 1, open + (s[pos] == '(' ? -1 : 1), true); 
    }
    else { 
        ret |= memo(pos + 1, open + (s[pos] == '(' ? 1 : -1), finish); 
    }
    return ret; 
}

int main(void) { 
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    cin >> s; 
    memset(dyn, -1, sizeof(dyn)); 
    int closed = 0, open = 0, ret = false; 
    for(int i = 0; i < s.size(); i++) { 
        ret |= memo(i, open - closed, false) | memo(i, open - closed, true); 
        if(s[i] == '(') open++; 
        if(s[i] == ')') closed++;
        if(closed > open) break; 
    }
    cout << (ret ? "" : "im") << "possible\n"; 
    return 0; 
}