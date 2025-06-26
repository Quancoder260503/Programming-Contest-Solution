#include "bits/stdc++.h"

using namespace std; 

#define sz(x) (int) x.size()

int to_card(char c) {  
    if(c == 'A') return 0; 
    if(c <= '7') return c - '1'; 
    return 7; 
}

struct State
{
    int total[8]; 
    int up[7]; 
    int pile[7]; 
    State() {
        fill(up, up + 7, false); 
        fill(total, total + 7, 4);
        total[7] = 24;  
    }
    State(string s) {
        fill(up, up + 7, false); 
        fill(total, total + 8, 4); 
        fill(pile, pile + 7, 0); 
        total[7] = 24; 
        for(int i = 0; i < sz(s); i++) { 
            total[pile[i] = to_card(s[i])]--; 
        }
    }
    int key() const {
        int h_val = 0; 
        for(int i = 0; i < 7; i++) {
            h_val = h_val * 2; 
            if(up[i]) h_val++; 
        }
        for(int i = 0; i < 7; i++) { 
            h_val = h_val * 5; 
            h_val += total[i]; 
        }
        h_val *= 25; 
        h_val += total[7]; 
        return h_val; 
    }
    bool operator < (const State &s) const { 
        return key() < s.key(); 
    }
    int end() const { 
        return (count(up, up + 7, false) == 0); 
    }
    int left() const {
        return accumulate(total, total + 8, 0); 
    }
    void flip(int c) { 
        total[c]--; 
        while(true) {
            if(c >= 7 || up[c]) return;  
            up[c] = 1; 
            c = pile[c]; 
        }
    }
}; 

map<State, double>dyn; 

double f(State s) {  
    if(dyn.count(s)) return dyn[s]; 
    double ret = 0.0; 
    if(s.end()) return dyn[s] = ret;
    ret = 1;  
    for(int i = 0; i < 8; i++) if(s.total[i] > 0) { 
        State next = s; 
        next.flip(i); 
        ret += 1.0 * s.total[i] / s.left() * f(next); 
    }
    return dyn[s] = ret; 
}

int main(void){
    string s; 
    cin >> s; 
    State cc(s); 
    cout << fixed << setprecision(16) << f(cc) << '\n'; 
    return 0; 
}