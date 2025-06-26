#include "bits/stdc++.h"

using namespace std;
#define double long double
const int M = (1 << 19); 

double dyn[M], ret[M]; 

int main(void)
{
    int n, m; 
    cin >> n >> m; 
    dyn[(1 << n) - 1] = 1.0; 
    for(int i = 0; i < m; i++)
    {
        int u, v;
        double prob; 
        cin >> u >> v >> prob;
        --u, --v;
        for(int mask = 0; mask < (1 << n); mask++) if(((mask >> u) & 1) && ((mask >> v) & 1))
        {
            dyn[mask xor (1 << v)] += prob * dyn[mask]; 
            dyn[mask] = dyn[mask] * (1.0 - prob); 
        }
    }
    for(int mask = 0; mask < (1 << n); mask++) for(int i = 0; i < n; i++) if(mask & (1 << i))
    {
        //cout << dyn[mask] << '\n'; 
        ret[i] += dyn[mask]; 
    } 
    cout << fixed << setprecision(10); 
    for(int i = 0; i < n; i++) cout << ret[i] << '\n'; 
    return 0;
}