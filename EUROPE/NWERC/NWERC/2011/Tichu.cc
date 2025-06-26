#include "bits/stdc++.h"

using namespace std; 

const int N = 100; 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int tc; 
    cin >> tc; 
    map<char, int>ord; 
    vector<char>val = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'}; 
    for(int i = 0; i < val.size(); i++) { 
        ord[val[i]] = i; 
    }
    while(tc--) { 
        vector<string>a(13); 
        for(int i = 0; i < 13; i++) { 
            cin >> a[i]; 
        }
        // pre_compute whether the set is valid 
        vector<int>match((1 << 13), false); 
        vector<int>dyn((1 << 13), -1);
        vector<int>F((1 << 13),   -1);  
        for(int mask = 0; mask < (1 << 13); mask++) { 
            vector<string>cards; 
            for(int i = 0; i < 13; i++) if(mask & (1 << i)) { 
                cards.push_back(a[i]); 
            }
            sort(cards.begin(), cards.end(), [&](string a, string b) { 
                return ord[a[0]] < ord[b[0]]; 
            }); 
            int consec = cards.size() >= 5, same_val = true, full_house = false; 
            for(int i = 1; i < cards.size(); i++) { 
                consec   &= (ord[cards[i - 1][0]] + 1 ==  ord[cards[i][0]]);
                same_val &= (cards[i - 1][0] == cards[i][0]);
            }
            if(__builtin_popcount(mask) == 5) { 
                map<int, int>cc; 
                for(auto &x  :  cards) { 
                    cc[ord[x[0]]]++; 
                }
                if(cc.size() == 2) { 
                    full_house = (cc.begin()->second == 2 || cc.begin()->second == 3); 
                }
            }
            match[mask] = (full_house || same_val || consec); 
        }
        function<int(int)> memo = [&](int mask) { 
            if(mask == 0) return 0;
            int& ret = dyn[mask];
            if(ret != -1) return ret; 
            ret = N;  
            for(int smask = mask; ; smask = (smask - 1) & mask) { 
                int cost = memo(smask); 
                if(match[mask ^ smask] && ret > 1 + cost) {
                    ret = 1 + cost; 
                    F[mask] = smask; 
                }
                if(smask == 0) break; 
            }
            return ret; 
        }; 
        cout << memo((1 << 13) - 1) << '\n'; 
        int fmask = (1 << 13) - 1; 
        for(; F[fmask] != -1; ) { 
            int dmask = fmask ^ F[fmask]; 
            for(int i = 0; i < 13; i++) if(dmask & (1 << i)) { 
                cout << a[i] << " "; 
            }
            cout << '\n'; 
            fmask = F[fmask]; 
        }
    }
    return 0; 
}