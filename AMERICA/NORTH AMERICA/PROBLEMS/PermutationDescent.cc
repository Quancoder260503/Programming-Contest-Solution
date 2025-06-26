#include "bits/stdc++.h"

using namespace std;

const int mod = 1001113; 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int ProbNum, N, K, tc;
    cin >> tc;  
    for(int iter = 0; iter < tc; iter++) { 
        cin >> ProbNum >> N >> K; 
        vector<vector<int64_t>>dyn(N + 1, vector<int64_t>(K + 1, -1)); 
        function<int64_t(int, int)> memo = [&](int pos, int descent) -> int64_t { 
            if(pos < 0 || descent < 0) return 0; 
            if(pos == 0 && descent == 0) return 1; 
            int64_t &ret = dyn[pos][descent]; 
            if(ret != -1) return ret; 
            ret = (memo(pos - 1, descent - 1) % mod * (pos - descent) % mod + 
                   memo(pos - 1, descent) % mod * (descent + 1) % mod) % mod; 
            return ret; 
        };
        cout << ProbNum << " " << memo(N, K) << '\n'; 
    }
    return 0; 
}
/*
   dyn[i][j] = {the number of permutations of the first i-th integers and there are j descents}
   there are i gaps between i - 1 number and j - 1 of them are descents.
   if a[i] < a[j]  then insert the larger a[k] gives : a[i] < a[k] > a[j]  : (i - (j - 1) - 1) * dyn[i - 1][descent - 1] ways
   if a[i] > a[j]  then insert the larger a[k] gives : a[i] < a[k] > a[j]  : j * dyn[i - 1][j] % mod; 
*/