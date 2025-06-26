#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size()) 

const int maxf = 1e5; 
const int64_t oo = 1e18; 

int64_t fact[maxf]; 

int main(void) { 
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0);
    int N, sum = 0; 
    int64_t K;
    cin >> N >> K;
    --K; 
    vector<int>ret; 
    vector<int>perm = {0}; 
    vector<int>visited(N, false); 
    fact[0] = 1;  
    for(int i = 1; i < maxf; i++) { 
        fact[i] = oo; 
    }
    for(int i = 1; i < maxf; i++) { 
        fact[i] = fact[i - 1] * i; 
        if(fact[i] > oo / i) break; 
    }
    for(int i = 0; i < N - 1; i++) { 
        vector<pair<int, int>>cand; 
        for(int j = 1; j < N; j++) if(!visited[j]) {
            cand.push_back({(j - perm[i] + N) % N, j}); 
        }
        sort(cand.begin(), cand.end()); 
        for(const auto &[x, y] : cand) { 
            if(K >= fact[N - i - 2]) { 
                K = K - fact[N - i - 2]; 
                continue; 
            }
            visited[y] = true; 
            perm.push_back(y); 
            ret.push_back(x); 
            break; 
        }
    }
    for(int i = 0; i < ret.size(); i++) { 
        cout << ret[i] << " "; 
    }
    cout << '\n'; 
    return 0; 
}