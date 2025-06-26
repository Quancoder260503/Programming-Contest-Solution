#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    int tc; 
    cin >> tc;
    while(tc--) {
        int n; 
        cin >> n; 
        vector<int>l(n), r(n); 
        for(int i = 0; i < n; i++) cin >> l[i] >> r[i];
        map<pair<int, int>, int>g; 
        function<int(int, int)> grundy = [&](int i, int j) {
            if(i >= j) return 0; 
            if(g.count({i, j})) return g[{i, j}]; 
            set<int>gr; 
            for(int k = 0; k < n; k++) { 
                if(i <= l[k] && r[k] <= j) {
                    gr.insert(grundy(i, l[k]) ^ grundy(r[k], j)); 
                }
            }
            int mex = 0; 
            while(gr.count(mex)) mex++; 
            return g[{i, j}] = mex; 
        };
        cout << (grundy(1, 100) ? "Alice" : "Bob") << '\n';  
    }  
    return 0; 
}