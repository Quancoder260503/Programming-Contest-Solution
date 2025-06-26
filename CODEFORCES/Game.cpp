#include "bits/stdc++.h"
using namespace std;
#pragma GCC target("popcnt")
#define MASK 19
#define M (int)1e3 + 1
#define MAXN (int)(1 << MASK)
#define lint long long
bitset<M>arr;
bitset<M>odd;
bitset<M>even;
int n;
char s[M]; 
signed main(void)
{
    scanf("%d", &n);
    scanf(" %s", &s);
    for(int i = 0; i < n; i++)
    {
        arr[i] = s[i] - '0'; 
    }
    int cur = 0; 
    for(int i = 0; i < n; i++)
    {
        even[i] = cur; 
        odd[i] = cur xor 1; 
        cur = cur xor 1; 
    }
    int ans = min((arr xor even).count(), (odd xor arr).count());
    printf("%d\n", ans); 
    return 0;
}