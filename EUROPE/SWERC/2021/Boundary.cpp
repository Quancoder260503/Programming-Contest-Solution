#include "bits/stdc++.h"
using namespace std; 
vector<int>ro; 
int n, m;
int gcd(int a, int b)
{
    if(a == 0) return b; 
    return gcd(b % a, a); 
}
void get_divisors(int k)
{
     for(int i = 1; i * i <= k; i++)
     {
        if(k % i == 0)
        {
             ro.push_back(i); 
             ro.push_back(k / i); 
        }
     }
     return; 
}
void solve()
{
   cin >> n >> m; 
   get_divisors(gcd(n - 1, m - 1)); 
   get_divisors(gcd(n - 2, m));
   get_divisors(gcd(n, m - 2));
   get_divisors(gcd(n, gcd(n - 2, m - 1))); 
   get_divisors(gcd(m, gcd(m - 2, n - 1)));
   sort(ro.begin(), ro.end());
   ro.erase(unique(ro.begin(), ro.end()),ro.end()); 
   cout << ro.size() << " "; 
   for(int i = 0; i < ro.size(); i++)
   {
     cout << ro[i] << " "; 
   }     
   ro.clear();
   cout << endl; 
   return;
}
int t; 
signed main(void)
{
    cin >> t;
    for(int i = 0; i < t; i++)
    {
        solve(); 
    }
    return 0; 
}