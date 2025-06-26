#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e9;
const int INF = 1e7 + 10;
const int mod = 1e9 + 7; 
long long n,m,q,dsz,E,a,b;
int timer = 1;
long long binpow(long long a, long long b){
    if(b == 0) return 1;
    long long res = 1;
    while(b > 0){
        if(b & 1) res = res % mod * a % mod;
        a = a % mod * a % mod;
        b >>= 1; 
    }
    return res % mod;
}
int main(){
    cout<<binpow(N, N - 1)<<endl; 
}