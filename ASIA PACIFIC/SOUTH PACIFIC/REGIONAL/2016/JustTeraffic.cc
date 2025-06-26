#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e5 + 2; 
const int imp = -2; 
const int amb = -3; 

int64_t dyn[maxf]; 
int N, arr[maxf]; 

int64_t doit(int at)
{
    if(at == N) return 0; 
    if(at == N - 1) return imp;
    int64_t &c = dyn[at];
    if(c != -1) return c;
    if(at >= 1    && arr[at] - arr[at - 1] <= 1000) return c = imp; 
    if(at < N - 1 && arr[at + 1] - arr[at] >= 2000) return c = imp; 
    int64_t c2 = doit(at + 2);
    if(c2 >= 0) c2++; 
    if(at + 2 >= N || arr[at + 2] - arr[at + 1] >= 2000) return c = c2; 
    int64_t c3 = doit(at + 3);
    if(c3 == imp) c3 = c2; 
    if(c2 == imp) c2 = c3; 
    return c = (c2 == c3 ? c2 : amb); 
}

int main(void)
{
    cin >> N; 
    memset(dyn, -1, sizeof(dyn)); 
    for(int i = 0; i < N; i++) cin >> arr[i]; 
    int64_t ret = doit(0); 
    if(ret == imp) cout << "Impossible" << '\n'; 
    else if(ret == amb) cout << "Ambiguous" << '\n'; 
    else 
    {
        cout << "Car with trailers: " << ret << '\n'; 
        cout << "Car without trailers: " << (N - 2 * ret) / 3 << '\n'; 
    }
    return 0;
}