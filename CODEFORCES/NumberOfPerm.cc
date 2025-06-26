#include "bits/stdc++.h"

using namespace std;

const int mod = 998244353;
const int maxf = 1e6 + 2;

int64_t ifact[maxf], fact[maxf];

int64_t fpow(int64_t a, int64_t k)
{
    if (!k)
        return 1;
    int64_t res = a, tmp = a;
    k--;
    while (k)
    {
        if (k & 1)
        {
            res = (long long)res * tmp % mod;
        }
        tmp = (long long)tmp * tmp % mod;
        k >>= 1;
    }
    return res;
}

void init(void)
{
    fact[0] = ifact[0] = 1;
    for (int i = 1; i < maxf; i++)
    {
        fact[i] = fact[i - 1] * i % mod;
        ifact[i] = fpow(fact[i], mod - 2);
    }
    return;
}

int main(void)
{
    init();
    int n;
    cin >> n;
    vector<pair<int, int>> sortme;
    for (int i = 0, x, y; i < n; i++)
    {
        cin >> x >> y;
        sortme.push_back({x, y});
    }
    sort(sortme.begin(), sortme.end()); 
    int64_t f = 1, s = 1, fs = 1;
    for (int i = 0; i < sortme.size(); i++)
    {
        int j = i;
        while (j < sortme.size() && sortme[i].first == sortme[j].first) j++;
        f = f * fact[j - i] % mod;
        i = j - 1;
    }
    auto cmp = [&](pair<int, int>&a, pair<int, int>&b)
    {
        return a.second == b.second ? a.first < b.first : a.second < b.second;   
    };
    sort(sortme.begin(), sortme.end(), cmp);
    for (int i = 0; i < sortme.size(); i++)
    {
        int j = i;
        while (j < sortme.size() && sortme[i].second == sortme[j].second) j++;
        s = s * fact[j - i] % mod;
        i = j - 1;
    }
    int64_t ret = (f + s) % mod; 
    bool chk = 1; 
    sort(sortme.begin(), sortme.end()); 
    for(int i = 0; i + 1 < sortme.size(); i++)
    {
        chk = chk & (sortme[i].first <= sortme[i + 1].first && sortme[i].second <= sortme[i + 1].second); 
    }
    if(chk)
    {
        for (int i = 0; i < sortme.size(); i++)
        {
            int j = i;
            while (j < sortme.size() && sortme[i].second == sortme[j].second && sortme[i].first == sortme[j].first) j++;
            fs = fs * fact[j - i] % mod;
            i = j - 1;
        }
        ret = (ret - fs + mod) % mod; 
    }
    cout << (fact[n] - ret + mod) % mod << '\n'; 
    return 0;
}