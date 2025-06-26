#include "bits/stdc++.h"
using namespace std; 
const int INF = 1e9; 
int main(void)
{ 
    int N, D; 
    while(cin >> N >> D)
    {
        vector<int>m(N), c(N); 
        vector<int>day(D); 
        for(int i = 0; i < N; i++) cin >> m[i] >> c[i]; 
        for(int i = 0; i < D; i++) cin >> day[i]; 
        int ptr = 0; 
        int ret = 0; 
        for(int k = 0; k < D; k++)
        {
            vector<int>dyn(day[k] - ptr + 1, -INF);
            dyn[0] = -m[ptr]; 
            dyn[1] =  min(0, c[ptr] - m[ptr]); 
            for(int i = ptr + 1; i < day[k]; i++) 
            {
                vector<int> ndyn(day[k] - ptr + 1, -INF);
                for(int j = 0; j < dyn.size(); j++)
                {
                    ndyn[j] = max(ndyn[j], dyn[j] - m[i]);
                    if(j) ndyn[j] = max(ndyn[j], dyn[j - 1] + c[i] - m[i]);  
                }
                for(int j = 0; j < ndyn.size(); j++) ndyn[j] = min(ndyn[j], 0); 
                dyn.swap(ndyn); 
            }
            int chk = 0; 
            for(int i = 0; i <= day[k] - ptr; i++) if(dyn[i] >= 0)
            { 
                ret += i;
                chk = 1;  
                break; 
            }
            if(!chk)
            {
                puts("-1"); 
                goto done; 
            }
            ptr = day[k]; 
        }
        cout << ret << '\n';
    done: 
        continue;  
    }
    return 0;
}