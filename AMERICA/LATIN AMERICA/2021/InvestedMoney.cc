#include "bits/stdc++.h"

using namespace std;

int f(int x, int d) { 
    x += 30; 
    while(((x + d) % 7 + 7) % 7 < 2) x++; 
    if(((x + d) % 7 + 7) % 7 == 2) x = -((-x) % 91);
    if(x >= 0) return x; 
    return f(x, d); 
}

int main(void) { 
    int n;
    string s; 
    cin >> s >> n;
    vector<string>ss = {"Sat", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri"}; 
    int p = find(ss.begin(), ss.end(), s) - ss.begin(); 
    int ret = (int) 1e9; 
    for(int i = 0, x; i < n; i++) { 
        cin >> x; 
        ret = min(ret, f(-x, p)); 
    }
    cout << ret << '\n'; 
    return 0; 
}