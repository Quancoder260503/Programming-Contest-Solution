#include "bits/stdc++.h"

using namespace std;

const int maxf = 2e5 + 2; 

int a[maxf], N, K; 

int main(void)
{
    cin >> N >> K; 
    for(int i = 0; i < N; i++)
    {
        int x;
        cin >> x; 
        a[x]++;
        a[x + 1000]--; 
    }
    int ret = 0; 
    for(int i = 1; i < maxf; i++)
    {
        a[i] += a[i - 1];
        ret = max(ret, a[i]); 
    }
    cout << ceil(1.0 * ret / K) << '\n'; 
    return 0;
}