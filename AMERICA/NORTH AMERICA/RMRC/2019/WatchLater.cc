#include "bits/stdc++.h"

using namespace std; 

const int maxf = (1 << 21); 
const int INF  = 1e9; 

int dyn[maxf], N, K, ptr;
string S;
char ord[maxf]; 
int a[maxf]; 

int doit(int mask)
{
    if(mask == (1 << K) - 1) return 0; 
    if(dyn[mask] != -1) return dyn[mask]; 
    int &c = dyn[mask]; 
    c = INF; 
    vector<int>ctr(K); 
    for(int i = 0, last = -1; i < N; i++) 
    {
        if(mask & (1 << a[i])) continue; 
        if(last != a[i]) 
        {
            ctr[a[i]]++; 
        }
        last = a[i]; 
    }
    for(int i = 0; i < K; i++)
    {
        if(mask & (1 << i)) continue;
        c = min(c, ctr[i] + doit(mask xor (1 << i)));
    }
    return c; 
}

int main(void)
{
    cin >> N >> K >> S;
    memset(dyn, -1, sizeof(dyn)); 
    memset(ord, -1, sizeof(ord));
    ptr = 0;  
    for(int i = 0; i < S.length(); i++)
    {
        if(ord[S[i] - 'a'] == -1) ord[S[i] - 'a'] = ptr++; 
        a[i] = ord[S[i] - 'a'];  
    }
    cout << doit(0) << '\n'; 
    return 0; 
}