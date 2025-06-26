#include "bits/stdc++.h" 

using namespace std;

const int maxf = 1e6 + 10; 
const int64_t INF = 1e16; 

int64_t dyn[maxf];
int N, P, R; 

int64_t doit(int n)
{
    if(n <= 1) return 0; 
    if(dyn[n] != -1) return dyn[n];
    int64_t &ret = dyn[n]; 
    ret = INF; 
    for(int i = 1; i < n; i++)
    {
        ret = min(ret, doit(ceil(1.0 * n / (i + 1))) + (int64_t) i * P + R); 
    }
    return ret; 
}
int main(void)
{
    while(cin >> N >> R >> P)
    {
        memset(dyn, -1, sizeof(dyn)); 
        cout << doit(N) << '\n'; 
    }
    return 0;
}