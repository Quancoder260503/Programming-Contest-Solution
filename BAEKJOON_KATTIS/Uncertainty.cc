#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

struct event { 
    int s, a, b; 
}; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    int N; 
    cin >> N; 
    vector<event>h; 
    for(int i = 0, s, a, b; i < N; i++) { 
        cin >> s >> a >> b; 
        h.push_back({s, s + a, s + b}); 
    }
    vector<double>dyn(N), opt(N);
    opt[N - 1] = dyn[N - 1] = 1.0;   
    for(int i = N - 2; i >= 0; i--) { 
        int j = i + 1; 
        while(j < N && h[j].s < h[i].a) j++; 
        dyn[i] = 1.0; 
        int curr = h[i].a - 1; 
        while(j < N && curr < h[i].b) { 
            int next = h[j].s;
            if(next > h[i].b) next = h[i].b; 
            dyn[i] += opt[j] * (next - curr) / (1.0 * (h[i].b - h[i].a + 1)); 
            while(j < N && h[j].s == next) j++; 
            curr = next;
        }
        opt[i] = max(opt[i + 1], dyn[i]); 
    }
    cout << fixed << setprecision(10) << opt[0] << '\n'; 
    return 0; 
}