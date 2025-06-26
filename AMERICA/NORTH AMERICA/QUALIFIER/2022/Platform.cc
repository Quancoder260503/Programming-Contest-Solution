#include "bits/stdc++.h"
using namespace std;
int main(void)
{
    int N, L, R;
    while(cin >> N >> L >> R)
    {
        vector<int>a(N);
        for(int i = 0; i < N; i++) cin >> a[i];
        sort(a.begin(), a.end());
        int ret = 0; 
        int rem = 1e9; 
        for(int i = 0; i < N; i++) 
        {
            int add = 0; 
            if(i < N - 1)
            {
                add = min({rem, R, 2 * (a[i + 1] - a[i]) - L}); 
                rem = 2 * (a[i + 1] - a[i]) - add; 
            }
            else 
            {
                add = min(R, rem);
            }
            if(add < L) 
            {
                cout << "-1" << '\n';
                goto done; 
            }
            ret += add; 
        }
        cout << ret << '\n';
    done:;  
    }
    return 0; 
}