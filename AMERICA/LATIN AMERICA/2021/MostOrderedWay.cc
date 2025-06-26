#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n; 
    cin >> n;
    vector<int64_t>a(n), d(n); 
    for(int i = 0; i < n; i++) { 
        cin >> a[i] >> d[i]; 
    }
    vector<int>ord(n);
    iota(ord.begin(), ord.end(), 0); 
    sort(ord.begin(), ord.end(), [&](int i, int j){ 
        return d[i] < d[j]; 
    }); 
    vector<int64_t>acc(n);
    for(int i = 0; i < n; i++) { 
        acc[i] = (i ? acc[i - 1] : 0) + a[ord[i]]; 
        if(acc[i] > d[ord[i]]) { 
            cout << "*\n";
            exit(0);  
        }
    }
    int64_t time_alloc = 0;
    for(int iter = 0; sz(ord); iter++) { 
        int64_t cur_time = time_alloc, dline = d[ord.back()]; 
        int opt = 0; 
        for(int i = 0; i < sz(ord); i++) { 
            if(dline >= a[ord[i]] && ord[i] < ord[opt]) opt = i; 
            cur_time += a[ord[i]]; 
            dline = min(dline, d[ord[i]] - cur_time); 
        }
        cout << ord[opt] + 1 << ' ';
        time_alloc += a[ord[opt]]; 
        ord.erase(ord.begin() + opt); 
    }
    cout << '\n'; 
    return 0;
}

/*
   For each candidate in order 
*/ 