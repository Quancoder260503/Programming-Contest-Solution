#include "bits/stdc++.h"

using namespace std;

#define sz(x) x.size()
#define rep(i, j, k) for(int i = j; i < k; i++)

vector<int> Z(const string &S)
{
    vector<int>z(sz(S));
    int l = -1, r = -1;
    rep(i, 1, sz(S))
    {
        z[i] = i >= r ? 0 : min(r - i, z[i - l]);
        while (i + z[i] < sz(S) && S[i + z[i]] == S[z[i]]) z[i]++;
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}

const int maxf = 2e5 + 2; 
int ctr[maxf]; 

int main(void)
{
    string S; 
    cin >> S;
    int N = S.length(); 
    auto zfunc = Z(S); 
    vector<int>ret; 
    for(int i = 0; i < zfunc.size(); i++)
    {
        ctr[1]++; 
        ctr[zfunc[i] + 1]--; 
        if(zfunc[i] == N - i) ret.push_back(zfunc[i]); 
    }
    for(int i = 1; i < maxf; i++) ctr[i] += ctr[i - 1];
    sort(ret.begin(), ret.end()); 
    cout << ret.size() + 1 << '\n'; 
    for(auto v : ret) cout << v << " " << ctr[v] + 1 << '\n'; 
    cout << N << " " << 1 << '\n'; 
    return 0; 
}