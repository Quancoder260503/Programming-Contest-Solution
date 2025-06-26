#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int T, prob;
    cin >> T; 
    prob = 0;
    while(T--)
    {
        prob++;
        int64_t ret = 0;
        int N; 
        cin >> N; 
        vector<int64_t>X(N), Y(N);
        for(int i = 0; i < N; i++) cin >> X[i]; 
        for(int i = 0; i < N; i++) cin >> Y[i]; 
        sort(X.begin(), X.end()); 
        sort(Y.rbegin(), Y.rend()); 
        for(int i = 0; i < N; i++)
        {
            ret += 1LL * X[i] * Y[i]; 
        } 
        printf("Case #%d: %lld\n", prob, ret); 
    }
    return 0;
}