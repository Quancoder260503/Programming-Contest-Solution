#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    int r, c; 
    cin >> r >> c; 
    vector<int>a(r * c), b(r * c); 
    for(int i = 0; i < r * c; i++) { 
        cin >> a[i]; 
        a[i]--; 
    }
    for(int i = 0; i < r * c; i++) { 
        cin >> b[i]; 
        b[i]--; 
    }
    vector<pair<int, int>>ret;
    for(int i = 0; i < r * c; i++) { 
        int pa = find(a.begin(), a.end(), i) - a.begin(); 
        int pb = find(b.begin(), b.end(), i) - b.begin(); 
        int aend = (pa / c + 1) * c; 
        while(a[pb] != i) { 
            int swp = lower_bound(a.begin() + pa, a.begin() + aend, a[pb]) - a.begin() - 1;
            ret.push_back({pb, swp});
            swap(a[pb], a[swp]); 
        }
    }
    cout << ret.size() << '\n';
    for(auto [u, v] : ret) { 
        cout << (u / c) + 1 << " " << (u % c) + 1 << " " << (v / c) + 1  << " " << (v % c) + 1 << '\n'; 
    }
    return 0; 
}