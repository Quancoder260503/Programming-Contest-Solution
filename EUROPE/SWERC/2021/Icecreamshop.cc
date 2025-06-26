#include "bits/stdc++.h"
using namespace std; 
int main(void)
{
    int N, M;
    while(cin >> N >> M)
    {
        vector<int>P(N); 
        vector<int64_t>X(M + 2); 
        for(int i = 0; i < N;  i++)  cin >> P[i]; 
        for(int i = 1; i <= M; i++)  cin >> X[i]; 
        vector<int64_t>coord {INT32_MIN, INT32_MAX}; 
        for(int i = 0; i < N; i++) coord.push_back(200 * i); 
        sort(coord.begin(), coord.end());
        vector<int64_t>prefix(N + 1);
        for(int i = 0; i < N; i++) prefix[i + 1] = prefix[i] + P[i];  
        X[0]     = INT32_MIN;
        X[M + 1] = INT32_MAX;
        int ptr = 0; 
        int64_t ret = 0; 
        sort(X.begin(), X.end()); 
        for(int i = 0; i < N; i++)
        {
            while(X[ptr + 1] < 100LL * i) ptr++; 
            int64_t L = 200 * i - 1; 
            int64_t R = min(2 * X[ptr + 1], L + (X[ptr + 1] - X[ptr]));
            L = 1LL * max(1, (int)(lower_bound(coord.begin(), coord.end(), L) - coord.begin())); 
            R = 1LL * min(N, (int)(upper_bound(coord.begin(), coord.end(), R) - coord.begin()) - 1); 
            if(L < R)
            {
                ret = max(ret, prefix[R] - prefix[L - 1]); 
            }
        }
        cout << ret << '\n'; 
    }
    return 0;
}