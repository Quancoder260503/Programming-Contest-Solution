#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int n;
    while(cin >> n) { 
        if(n == 0) break;
        vector<int>a(n); 
        for(int i = 0; i < n; i++){ 
            cin >> a[i]; 
        }
        int sum = accumulate(a.begin(), a.end(), 0);
        vector<vector<vector<int64_t>>>dyn(n, vector<vector<int64_t>>(sum + 1, vector<int64_t>(3, -1))); 
        function<int64_t(int, int, int)> memo = [&](int pos, int total, int greater) -> int64_t {
            if(pos == n) return total > 0 || (total == 0 && greater < 2);  
            int64_t &ret = dyn[pos][total][greater]; 
            if(ret != -1) return ret; 
            ret = 0; 
            for(int k = 0; k <= total; k++) { 
                if(greater == 0) { 
                    if(a[pos] == k) ret += memo(pos + 1, total - k, 0);
                    if(a[pos] <  k) ret += memo(pos + 1, total - k, 2); 
                    if(a[pos] >  k) ret += memo(pos + 1, total - k, 1);  
                } 
                else { 
                    ret += memo(pos + 1, total - k, greater); 
                }
            }
            return ret; 
        }; 
        cout << memo(0, sum, 0) << '\n'; 
    }
    return 0; 
}