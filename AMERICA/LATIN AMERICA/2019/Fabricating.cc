#include "bits/stdc++.h"

using namespace std;
const int mod = 1e9 + 7;
const int MAX = 1e4 + 2; 

int N, B; 
int64_t dyn[MAX][MAX]; 
int64_t doit(int l, int b)
{
    if(l < 0 || b < 0)   return 0; 
    if(l == 0 && b > 0)  return 0; 
    if(b == 0 && l <= 1) return 1; 
    int64_t &c = dyn[l][b];
    if(c != -1) return c; 
    c = (doit(l, b - l) + mod + 2 * doit(l - 1, b) - doit(l - 2, b)) % mod; 
    return c; 
}
int main(void)
{
    while(cin >> N >> B)
    {
        memset(dyn, -1, sizeof(dyn));
        int64_t ret =  doit(N, B - N);
        cout << ret << '\n'; 
    }
    return 0; 
}