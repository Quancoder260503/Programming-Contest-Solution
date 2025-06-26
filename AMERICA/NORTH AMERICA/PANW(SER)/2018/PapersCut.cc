#include "bits/stdc++.h"

using namespace std; 

const int maxf = 100; 

#define sz(x) int(x.size())

map<int, int>cache[maxf]; 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    string A, B;
    cin >> A >> B; 
    cache[0][0] = -1; 
    for(int i = 1; i <= A.size(); i++) {
        for(int j = 1; j <= i; j++) {
            string curr = A.substr(j - 1, i - j + 1);  
            vector<int>mask;  
            for(int s = 0; s + i - j < B.size(); s++) { 
                if(B.substr(s, i - j + 1) == curr) { 
                    mask.push_back(((1 << (i - j + 1)) - 1) << s); 
                } 
            }
            for(auto m : mask) { 
                for(auto [x, y] : cache[j - 1])  if((m & x) == 0) { 
                    int nmask = m | x; 
                    if(cache[i].count(nmask)) { 
                        cache[i][nmask] = min(cache[i][nmask], y + 1); 
                    }
                    else { 
                        cache[i][nmask] = y + 1; 
                    } 
                }
            }
        }
    }
    cout << cache[sz(A)][(1 << sz(A)) - 1] << '\n'; 
    return 0; 
}