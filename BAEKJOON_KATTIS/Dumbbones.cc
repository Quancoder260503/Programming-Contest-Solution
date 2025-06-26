#include "bits/stdc++.h"

using namespace std;

const int maxf = 1005; 

double dyn[maxf], pl, pr;
int n;  

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    while(cin >> n) {  
        if(!n) break; 
        cin >> pl >> pr; 
        for(int i = 0; i < maxf; i++) dyn[i] = 1e50; 
        dyn[0] = 0; 
        for(int i = 1; i <= n; i++) for(int j = 0; j < i; j++) { 
            dyn[i] = min(dyn[i], dyn[j] + dyn[i - j - 1] + (1 + dyn[j] * pl + dyn[i - j - 1] * pr) / (1 - pl - pr)); 
        }
        cout << fixed << setprecision(2) << dyn[n] << '\n'; 
    } 
    return 0; 
}