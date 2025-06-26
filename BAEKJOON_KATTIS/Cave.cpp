#include "bits/stdc++.h"
#include "cave.h"
using namespace std;
#define MAXN (int) 2e5 + 10
bool vis[MAXN]; 
int arr[MAXN];
int d[MAXN]; 
void switching(int s, int e)
{
    for(int i = s; i <= e; i++)
    {
         if(!vis[i]) arr[i] = arr[i] xor 1; 
    }
    return;
}
int find(int pos, int n)
{
     int s = 0; int e = n - 1; 
     if(tryCombination(arr) != pos) switching(s, e); 
     while(s != e)
     {
         int mid = (s + e) / 2; 
         switching(s, mid);
         int t = tryCombination(arr); 
         switching(s, mid); 
         if(pos != t) e = mid; 
         else s = mid + 1; 
     }
     return s;
}
void exploreCave(int n)
{
     for(int i = 0; i < n; i++)
     {
         int pos = find(i, n);
         d[pos] = i; 
         vis[pos] = 1; 
         arr[pos] = arr[pos] xor 1;
     }
     answer(arr, d); 
}
signed main(void)
{
    return 0; 
}