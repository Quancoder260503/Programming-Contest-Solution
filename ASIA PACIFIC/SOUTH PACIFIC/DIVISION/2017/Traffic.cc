#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int T;
    T = 1; 
    while(T--)
    {
        int N, D; 
        cin >> N >> D; 
        int ret = 1; 
        for(int i = 0; i < N; i++) 
        {
            int X, A, R, G;
            cin >> X >> A >> G >> R;
            if(X < A || (X - A) % (R + G) > G) {ret = 0; break; }
        }
        cout << (ret ? "YES" : "NO") << '\n'; 
    }
    return 0;
}