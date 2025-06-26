#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int64_t n, m; 
    cin >> n >> m; 
    int64_t g = gcd(n, m); 
    n /= g;
    m /= g; 
    cout << (n % 2 == m % 2 ? g : 0) << '\n'; 
    return 0; 
}