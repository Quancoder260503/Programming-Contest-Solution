#include "bits/stdc++.h"
using namespace std;
const int MAX = 102;
const int M = 10002; 
int64_t dyn[MAX][M]; 
int main(void)
{
    int N, H; 
    while(cin >> N >> H)
    {
        vector<int>P(N);
        vector<int>V(N); 
        for(int i = 0; i < N; i++) cin >> P[i] >> V[i]; 
        function<int64_t(int, int, int)>memo; 
        memo = [&](int pos, int vloss, int bound) -> int64_t
        {
            if(pos == N) return 0;
            if(dyn[pos][vloss] != -1) return dyn[pos][vloss]; 
            int Value = V[pos]; 
            int Power = P[pos]; 
            int64_t &ret  = dyn[pos][vloss]; 
            int64_t accP  = P[pos]; 
            int64_t accV  = Value - (Value / 2);
            ret = max(ret, memo(pos + 1, vloss, bound)); 
            while(Value && vloss + accV <= bound)
            { 
                ret = max(ret, accP + memo(pos + 1, vloss + accV, bound));
                Value = Value / 2; 
                Power = Power * 2;
                accP += Power;
                accV += Value - Value / 2;
            }
            return ret; 
        };
        auto f = [&](int L)
        {
            memset(dyn, -1, sizeof(dyn));
            memo(0, 0, L);
            return dyn[0][0] >= H; 
        };
        int L = 0; 
        int R = M; 
        while(L < R)
        {
            int mid = (L + R) / 2; 
            if(f(mid))
            {
                R = mid;
            }
            else 
            {
                L = mid + 1;  
            }
        }
        cout << (L == M ? -1 : L) << '\n'; 
    }
    return 0; 
}