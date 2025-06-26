#include "bits/stdc++.h"
using namespace std;
const int MAXN = 200;
map<string, int> mp;
map<string, int>school;
map<string, int>team;
int n;
struct info
{
    string name, uni, division;
};
info arr[MAXN];
bool cmp(pair<string,int>&a, pair<string,int>&b)
{
    return a.second < b.second;
}
signed main(void)
{
    vector<pair<string, int>> ans;
    vector<pair<string, int>> board;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i].name >> arr[i].division >> arr[i].uni;
    }
    for (int i = 0; i < n; i++)
    {
        if (mp[arr[i].division] == 2 || school[arr[i].uni] == 1) continue;
        school[arr[i].uni]++; 
        mp[arr[i].division]++;
        team[arr[i].name]++;
        ans.push_back({arr[i].name, i});
    }
    for(int i = 0; i < n; i++)
    {
        if(school[arr[i].uni] == 2 || team[arr[i].name] == 1) continue; 
        school[arr[i].uni]++; 
        ans.push_back({arr[i].name, i}); 
        if(ans.size() == 12) break;
    }
    sort(ans.begin(), ans.end(), cmp);
    for(int i = 0; i < 12; i++)
    {
       cout << ans[i].first << endl;
    }
    return 0;
}