#include "bits/stdc++.h"

using namespace std; 

int main(void)
{
    string a, b;
    cin >> a;
    int N = a.length(); 
    int n = N / 3; 
    for(int i = 0; i < n; i++) b += "PER"; 
    int ret = 0; 
    for(int i = 0; i < N; i++) ret += (a[i] == b[i]); 
    ret = N - ret;
    cout << ret << '\n'; 
    return 0; 
}