#include "bits/stdc++.h"
using namespace std; 
#define MASK 30
int solve(int mask, vector<int>&arr)
{
     if(mask == -1) return 0; 
     vector<int>on, off; 
     for(int i = 0; i < arr.size(); i++)
     {
         if((1 << mask) & arr[i])
         {
             on.push_back(arr[i]); 
         }
         else 
         {
             off.push_back(arr[i]); 
         }
     }
     if(on.size() == 0) return solve(mask - 1, off);
     if(off.size() == 0) return solve(mask - 1, on);
     return min(solve(mask - 1, off), solve(mask - 1, on)) + (1 << mask);   
}
vector<int>arr;
int n;  
signed main(void)
{
    cin >> n;
    for(int i = 0; i < n; i++)
    {
         int x; cin >> x; 
         arr.push_back(x); 
    }
    cout << solve(MASK, arr) << endl;
    return 0;
}
/*
  FOR each ith bit -> divide the group into two parts 
  (AND operations on or off with the current bit) 

*/ 