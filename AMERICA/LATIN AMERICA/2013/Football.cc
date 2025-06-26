#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0);
    int N, G;
    cin >> N >> G;  
    vector<int>margin(N);  
    for(int i = 0, R, S; i < N; i++) { 
        cin >> R >> S; 
        margin[i] = R - S; 
    }
    sort(margin.rbegin(), margin.rend()); 
    int ret = 0; 
    for(int i = 0; i < N; i++) { 
        if(margin[i] > 0) { 
            ret += 3; 
        }
        else if(margin[i] < 0) { 
            if(G > abs(margin[i])) { 
                G = G - abs(margin[i]) - 1; 
                ret += 3; 
            }
            else if(G == abs(margin[i])) { 
                G = G - abs(margin[i]); 
                ret++; 
            }
        }
        else { 
            if(G > 0) {ret += 3; G--; }
            else {ret++; }
        }
    }
    cout << ret << '\n'; 
    return 0;
}