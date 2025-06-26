#include "bits/stdc++.h"
#pragma GCC target("popcnt")
using namespace std; 
const int MAXN = 5e4 + 2; 
bitset<MAXN>dyn; 
int main(void)
{
    int N, H; 
    while(cin >> H >> N)
    {
        vector<int>a(N);
        for(int i = 0; i < N; i++) cin >> a[i]; 
        dyn[0] = 1; 
        for(int i = 0; i < N; i++)
        {
            dyn = dyn | (dyn << a[i]); 
        }
        for(int i = H; i >= 0; i--) if(dyn[i])
        {
            cout << i << '\n'; 
            break; 
        }
    }
    return 0;
}