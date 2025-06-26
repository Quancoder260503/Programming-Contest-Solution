#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 1e6 + 10 
struct toy
{
    string shape; 
    double r; 
};
bool cmp(const toy &a, const toy &b)
{
    return a.r > b.r;
}
int n;
toy arr[MAXN];
vector<toy>cylin, cube;
signed main(void)
{
    cin >> n; 
    for(int i = 1; i <= n; i++)
    {
         cin >> arr[i].shape >> arr[i].r; 
         if(arr[i].shape == "cylinder") cylin.push_back(arr[i]); 
         else cube.push_back(arr[i]); 
    }
    sort(cube.begin(), cube.end(), cmp); 
    sort(cylin.begin(), cylin.end(), cmp);
    vector<toy>ans; 
    while(cube.size() && cylin.size())
    {
         double p = cube[0].r;
         double q = cylin[0].r;
         if(p <= q * sqrt(2.0))
         {
             ans.push_back(cylin[0]); 
             cylin.erase(cylin.begin()); 
         }
         else if(2.0 * q <= p)
         {
             ans.push_back(cube[0]);
             cube.erase(cube.begin()); 
         }
         else 
         {
             puts("impossible");
             return 0;
         }
    } 
    while(cylin.size())
    {
         ans.push_back(cylin[0]);
         cylin.erase(cylin.begin());
    }
    while (cube.size())
    {
         ans.push_back(cube[0]);
         cube.erase(cube.begin());
    }
    reverse(ans.begin(), ans.end()); 
    for(int i = 0; i < ans.size(); i++)
    {
         cout << ans[i].shape << " " << ans[i].r << '\n'; 
    }
    return 0;
}
/*
   Let p be the side length of cube and q be the radius of cylinder 
   get each of the toy into two sets 
   cylinder contains cubes when p / sqrt(2) <= q 
   cubes contain cylinder when 2 * q <= p
*/ 