#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int) 2e5 + 10; 
int n; 
int a[MAXN], b[MAXN]; 
bool cmp(const int x, const int y)
{
    return b[x] < b[y]; 
}
signed main(void)
{
    cin >> n; 
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];
    vector<int>ord(n);
    iota(ord.begin(), ord.end(), 1);
    sort(ord.begin(), ord.end(), cmp); 
    int at;
    for(at = 0; at < ord.size(); at++)
    {
         if(b[ord[at]] != -1) break; 
    }
    int ans = 0; 
    int acc = 0; 
    for(int cur = at; cur < ord.size(); cur++)
    {
         acc += a[ord[cur]]; 
         ans = max(ans, (int) ceil( (acc * 1.0) / (1.0 * b[ord[cur]]))); 
    }
    cout << ans << endl;
    return 0;
}