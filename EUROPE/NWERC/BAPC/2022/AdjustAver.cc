#include "bits/stdc++.h"

using namespace std;

const int64_t INF = 1e16; 

int main(void)
{
    int N, K;
    int64_t S; 
    while(cin >> N >> K >> S)
    {
        vector<int64_t> a(N);
        for (int i = 0; i < N; i++) cin >> a[i];
        function<int64_t(int)> f = [&](int k) -> int64_t 
        {
            S = S * (N - k); 
            int64_t ret = INF;
            int64_t sum = accumulate(a.begin(), a.end(), 0LL);
            if(k == 0)
            {
                ret = abs(sum - S); 
            }
            else if(k == 1)
            {
                for(int i = 0; i < N; i++)
                {
                    ret = min(ret, abs(S - (sum - a[i]))); 
                }
            }
            else if(k == 2)
            {
                for(int i = 0; i < N; i++) for(int j = i + 1; j < N; j++)
                {
                    ret = min(ret, abs(S - (sum - a[i] - a[j]))); 
                }
            }
            else if(k == 3)
            {
                set<int64_t> cc;
                for (int i = N - 1; i >= 0; i--)
                {
                    int64_t c = S + a[i];
                    auto it = cc.lower_bound(c);
                    if (it != cc.end())
                    {
                        ret = min(ret, *it - c);
                    }
                    if (it != cc.begin())
                    {
                        it--;
                        ret = min(ret, c - *it);
                    }
                    for (int j = i + 1; j < N; j++)
                    {
                        cc.insert(sum - a[i] - a[j]);
                    }
                }
            }
            else if(k == 4)
            {
                set<int64_t> cc;
                for (int i = N - 1; i >= 0; i--)
                {
                    for (int j = 0; j < i; j++)
                    {
                        int64_t c = S + a[i] + a[j];
                        auto it = cc.lower_bound(c);
                        if (it != cc.end())
                        {
                            ret = min(ret, *it - c);
                        }
                        if (it == cc.begin()) continue;
                        it--;
                        ret = min(ret, c - *it);
                    }
                    for (int j = i + 1; j < N; j++)
                    {
                        cc.insert(sum - a[i] - a[j]);
                    }
                }
            }
            S = S / (N - k); 
            return ret; 
        };
        double ret = INF; 
        for(int i = 0; i <= K; i++) ret = min(ret, 1.0 * f(i) / (N - i));
        cout << fixed << setprecision(10) << ret << '\n';  
    }
    return 0;
}