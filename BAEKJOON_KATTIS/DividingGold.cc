#include "bits/stdc++.h"

using namespace std; 

const int maxf = 5e5 + 2; 
const int mod = 1e6; 
const int mod2 = 1e9 + 7;
int64_t dyn[maxf], dyn2[maxf], a[maxf]; 

int main(void)
{
    int N; 
    cin >> N; 
    int sum = 0; 
    for(int i = 1; i <= N; i++) 
    {
        cin >> a[i]; 
        sum += a[i]; 
    }
    dyn[0] = dyn2[0] = 1; 
    sort(a + 1, a + N + 1); 
    for(int i = 1; i <= N; i++) 
    {
        for(int j = maxf - 1; j >= a[i]; j--) 
        {
            dyn[j] = (dyn[j] + dyn[j - a[i]]) % mod; 
            dyn2[j] = (dyn2[j] + dyn2[j - a[i]]) % mod2; 
        } 
    }
    pair<int, int64_t>ret = {maxf, 0}; 
    for(int i = 0; i < maxf; i++)
    {
        if(dyn2[i] && abs(sum - 2 * i) < ret.first)
        {
            ret = make_pair(abs(sum - 2 * i), dyn[i]); 
        }
    }
    cout << ret.first << '\n' << ret.second << '\n'; 
    return 0; 
}