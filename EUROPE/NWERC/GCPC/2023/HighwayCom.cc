#include "bits/stdc++.h"

using namespace std;

#define int64_t unsigned long long

mt19937_64 rng(435243);

const int maxf = 250;
const int mod = 1e9 + 7;
const int maxT = 1e7;

int64_t fib[maxf];
map<int64_t, int64_t>ifib; 

int64_t get_rand(void)
{
    return rng() % 100;
}

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

int main(void)
{
    int N;
    cin >> N;
    if (N == 0)
    {
        cout << "##.\n.##";
        return 0;
    }
    if (N == 1)
    {
        cout << ".\n.";
        return 0;
    }
    fib[0] = fib[1] = ifib[0] = ifib[1] = 1; 
    for (int i = 2; i < maxf; i++)
    {
        fib[i]  = (fib[i - 1] + fib[i - 2]) % mod;
        ifib[i] = fpow(fib[i], mod - 2); 
    }
    map<int64_t, vector<int>> a;
    for (int i = 0; i < maxT; i++)
    {
        vector<int> seta;
        int64_t ret = 1;
        for (int64_t c = 0, sum = 0; sum + c < 95; c = get_rand())
        {
            sum += c;
            if (c) seta.push_back(c);
            ret = ret * fib[c] % mod;
        }
        if (a.count(ret) == 0) a[ret] = seta;
    }
    for (int i = 0; i < maxT; i++)
    {
        vector<int> setb;
        int64_t rret = N;
        for (int64_t c = 0, sum = 0; sum + c < 95; c = get_rand())
        {
            sum += c;
            setb.push_back(c);
            rret = rret * ifib[c] % mod;
        }
        if (a.count(rret))
        {
            auto ret = a[rret];
            for (auto v : setb) ret.push_back(v);
            for (int _ = 0; _ < 2; _++)
            {
                for (int j = 0; j < ret.size(); j++)
                {
                    for (int k = 0; k < ret[j]; k++)  cout << ".";
                    cout << (j == ret.size() - 1 ? '\n' : '#');
                }
            }
            return 0;
        }
    }
    return 0;
}