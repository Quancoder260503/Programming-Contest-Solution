#include "bits/stdc++.h"

using namespace std; 
#define int64_t unsigned long long

const int maxf = 1e6 + 2; 

int vis[maxf]; 
int prime[maxf]; 
int ptr; 

void sieve()
{
    ptr = 0;
    for(int i = 2; i < maxf; i++) if(!vis[i])
    {
        prime[ptr++] = i; 
        for(int j = 2 * i; j < maxf; j += i) vis[j] = 1; 
    }
    return; 
}

int main(void)
{
    int64_t N; 
    sieve(); 
    while(cin >> N)
    {
        int64_t num = 1, den = 1; 
        for(int i = 0; 1LL * den * prime[i] <= N; i++)
        {
            num = 1LL * num * (prime[i] - 1); 
            den = 1LL * den * prime[i];
        }
        num = den - num; 
        cout << num / gcd(num, den) << "/" << den / gcd(num, den) << '\n'; 
    }
    return 0; 
}