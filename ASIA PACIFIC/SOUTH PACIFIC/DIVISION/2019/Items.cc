#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int s, c; 
    cin >> s >> c; 
    string sc;
    map<string, int>mp, mp1;
    for(int i = 0, m; i < s; i++) {
        cin >> m >> sc;
        if(m >  1) mp[sc]  += m; 
        if(m == 1) mp1[sc] += 1; 
    } 
    for(int i = 0, m; i < c; i++) { 
        cin >> m >> sc; 
        if(m == 1 && mp1.count(sc)) { 
            mp1.erase(sc); 
            continue; 
        }
        if(mp.count(sc + 's') && m == 1) { 
            if(mp[sc + 's'] < m) {
                puts("error");  
                return 0; 
            }
            mp[sc + 's'] = mp[sc + 's'] - m;
            if(mp[sc + 's'] == 0) mp.erase(sc + 's'); 
        }
        else if(mp.count(sc) && m  > 1) { 
            if(m < 2 || mp[sc] < m) { 
                puts("error");
                return 0; 
            }
            mp[sc] -= m; 
            if(mp[sc] == 0) mp.erase(sc); 
        }
        else { 
            puts("error"); 
            return 0; 
        }
    }
    int sum = 0; 
    for(const auto &[u, v] : mp) { 
        sum += v;
    }
    for(const auto &[u, v] : mp1) { 
        sum += v;
    }
    puts(sum > 1 ? "items" : (sum == 1 ? "item" : "null")); 
    return 0; 
}