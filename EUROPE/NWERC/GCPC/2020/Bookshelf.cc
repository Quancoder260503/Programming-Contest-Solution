#include "bits/stdc++.h"
using namespace std; 
const int MAX = 1e4 + 20; 
bitset<MAX>dyn; 
int main(void)
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int N, H, W; 
    while(cin >> N >> W >> H)
    {
        vector<int>h(N), w(N); 
        for(int i = 0; i < N; i++) cin >> w[i] >> h[i]; 
        if(*max_element(h.begin(), h.end()) > H)
        {
            cout << "impossible" << '\n'; 
            continue; 
        }
        else if(accumulate(w.begin(), w.end(), 0) <= W)
        {
            cout << "-1" << '\n'; 
            continue; 
        } 
        vector<int>ord(N);
        iota(ord.begin(), ord.end(), 0);
        auto cmp = [&](int a, int b)
        {
            return h[a] == h[b] ? w[a] < w[b] : h[a] < h[b]; 
        }; 
        sort(ord.rbegin(), ord.rend(), cmp); 
        int Lh = h[ord[0]]; 
        int Uh = H - h[ord[0]]; 
        int Lw = W, Uw = W; 
        int ptr = 0; 
        while(ptr < N && w[ord[ptr]] <= Lw && Uh < h[ord[ptr]] && h[ord[ptr]] <= Lh) 
        {
            Lw = Lw - w[ord[ptr]]; 
            ptr++; 
        }
        if(h[ord[ptr]] > Uh)
        {
            cout << "impossible" << '\n'; 
            continue; 
        }
        if(Lw == 0)
        {
            int acc = 0; 
            for(int i = ptr; i < N; i++) acc += w[ord[i]]; 
            if(acc <= W && h[ord[ptr]] <= Uh) 
            {
                cout << Lh << '\n'; 
            }
            else 
            {
                cout << "impossible" << '\n'; 
            }
            continue; 
        }
        dyn[0] = 1;
        int ctr = 0; 
        for(int i = ptr; i < N; i++)
        {
            ctr += w[ord[i]]; 
            dyn |= dyn << w[ord[i]]; 
        }
        int ret = 0; 
        for(int i = 1; i <= W; i++)
        {
            if(dyn[i] && i <= Lw && ctr - i <= W)
            {
                ret = 1;
                break; 
            }
            if(ret) break; 
        }
        if(ret)
        {
            cout << Lh << '\n'; 
        }
        else 
        {
            cout << "impossible" << '\n'; 
        }
    }
    return 0; 
}