#include "bits/stdc++.h"
using namespace std; 
const int INF = 100; 
int main(void)
{
    int N, K; 
    while(cin >> N >> K)
    {
        vector<string>S(N), T(N); 
        vector<vector<int>>ctr(N, vector<int>(26, INF)); 
        for(int i = 0; i < N; i++) 
        {
            cin >> S[i] >> T[i];
        }
        auto chk = [&](string a, string b)
        {
            string ret = "-----"; 
            vector<int>visa(5), visb(5); 
            for(int i = 0; i < 5; i++) if(a[i] == b[i])
            {
                ret[i] = 'G'; 
                visa[i] = visb[i] = 1; 
            }
            for(int i = 0; i < 5; i++) if(!visa[i])
            {
                for(int j = 0; j < 5; j++) if(!visb[j])
                {
                    if(a[i] == b[j])
                    {
                        ret[i] = 'Y';
                        visa[i] = visb[j] = 1; 
                        break;
                    }
                }
            }
            return ret; 
        }; 
        for(int _ = 0; _ < K; _++) 
        {
            string Q; 
            cin >> Q; 
            int res = 1; 
            for(int i = 0; i < N; i++)
            {
                res = res & (chk(S[i], Q) == T[i]);
            }
            if(res) cout << Q << '\n'; 
        }
    }
    return 0; 
}