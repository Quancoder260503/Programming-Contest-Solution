#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)2e5 + 10;
int n;
string s[MAXN];
string ver[MAXN]; 
signed main(void)
{
    cin >> n;
    int no = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i] >> ver[i]; 
        no += (ver[i] == "no"); 
    }
    for(int i = 1; i <= n; i++)
    {
         cout << s[i] << " " << (ver[i] == "no" ? 0 : no) << endl;
    }
    return 0;
}
