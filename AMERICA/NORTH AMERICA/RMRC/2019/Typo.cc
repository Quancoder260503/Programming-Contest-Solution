#include "bits/stdc++.h"

using namespace std; 

const int baseA = 31;
const int baseB = 37;
const int mod = 1e9 + 7; 

int64_t fpow(int64_t a, int64_t k)
{
    if (!k) return 1;
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

const int maxf = 1e6 + 2; 

int64_t pA[maxf], pB[maxf], invA[maxf], invB[maxf]; 
map<int64_t, int>h_val, g_val;

void init()
{
    pA[0] = pB[0] = invA[0] = invB[0] = 1; 
    for(int i = 1; i < maxf; i++)
    {
        pA[i]  = pA[i - 1] * baseA % mod; 
        pB[i]  = pB[i - 1] * baseB % mod;
        invA[i] = fpow(pA[i], mod - 2);  
        invB[i] = fpow(pB[i], mod - 2); 
    }
    return; 
}

void get_hash(const string &s)
{
    int N = s.length();
    int64_t reta = 0, retb = 0; 
    for(int i = 0; i < N; i++) 
    {
        reta += (s[i] - 'a' + 1) * pA[i] % mod; 
        reta %= mod; 
        retb += (s[i] - 'a' + 1) * pB[i] % mod; 
        retb %= mod; 
    }
    h_val[reta]++;  
    g_val[retb]++; 
    return; 
}

int chk(const string &s)
{
    int N = s.length(); 
    vector<int64_t>prefix(N), prefix2(N); 
    for(int i = 0; i < N; i++) 
    {
        prefix[i]  = (i ? prefix[i - 1] : 0)  + (s[i] - 'a' + 1) * pA[i] % mod;
        prefix[i]  %= mod;
        prefix2[i] = (i ? prefix2[i - 1] : 0) + (s[i] - 'a' + 1) * pB[i] % mod; 
        prefix2[i] %= mod; 
    }
    for(int i = 0; i < N; i++)
    {
        int64_t reta = 0, retb = 0; 
        if(i > 0)
        {
            reta = prefix[i - 1];
            retb = prefix2[i - 1]; 
        }
        if(i + 1 < N)
        {
            reta = (reta + invA[i + 1] % mod * (prefix[N - 1] - prefix[i]   + mod) % mod * pA[i] % mod) % mod;
            retb = (retb + invB[i + 1] % mod * (prefix2[N - 1] - prefix2[i] + mod) % mod * pB[i] % mod) % mod; 
        }
        if(!h_val.count(reta) || !g_val.count(retb)) continue; 
        return true; 
    }
    return false; 
}

int main(void)
{
    int N; 
    init(); 
    cin >> N;
    vector<string>s(N); 
    for(int i = 0; i < N; i++) 
    {
        cin >> s[i]; 
        get_hash(s[i]); 
    }
    vector<string>ret; 
    //for(int i = 0; i < N; i++) cout << h_val[i] << " "<< g_val[i] << '\n'; 
    for(int i = 0; i < N; i++)
    {
        if(chk(s[i])) ret.push_back(s[i]); 
    }
    if(ret.size())
    {
        for(auto it : ret) cout << it << '\n'; 
    }
    else 
    {
        cout << "NO TYPOS" << '\n'; 
    }
    return 0; 
}