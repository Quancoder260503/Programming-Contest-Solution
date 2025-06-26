#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int) x.size()

const int mod = 1e9 + 7; 
const int maxf = 750; 

int64_t dyn[maxf][maxf][3][3]; 
string s; 

int nxt[maxf]; 

int64_t f(int l, int r, int c1, int c2)
{
    if(l > r) return 1; 
    if(dyn[l][r][c1][c2] != -1) return dyn[l][r][c1][c2]; 
    int64_t &ret = dyn[l][r][c1][c2]; 
    int q = nxt[l]; 
    ret = 0;
    for(int c = 1; c < 3; c++) {
        if(q < r || c != c2) {
            ret += f(l + 1, q - 1, 0, c) * f(q + 1, r, c, c2) % mod; 
            ret %= mod; 
        } 
        if(c != c1)
        {
            ret += f(l + 1, q - 1, c, 0) * f(q + 1, r, 0, c2) % mod;
            ret %= mod; 
        }
    }
    return ret; 
}

int main(void)
{
    cin >> s; 
    memset(dyn, -1, sizeof(dyn)); 
    stack<int>stk;
    for(int i = 0; i < sz(s); i++)
    {
        if(s[i] == '(') stk.push(i);
        else 
        {
            nxt[stk.top()] = i; 
            stk.pop(); 
        }
    }
    cout << f(0, sz(s) - 1, 0, 0) << '\n'; 
    return 0; 
}