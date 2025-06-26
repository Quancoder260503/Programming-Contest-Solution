#include "bits/stdc++.h"

using namespace std;

const int mod = 1e9 + 7;
const int maxf = 1e5 + 10; 

string vowels = "aeiouAEIOU"; 
string consonants; 

int is_vowels(char c)
{
    return (vowels.find(c) != -1); 
}

void init(void)
{
    for (char c = 'a'; c <= 'z'; c++) if(!is_vowels(c)) consonants += c; 
    for (char c = 'A'; c <= 'Z'; c++) if(!is_vowels(c)) consonants += c; 
    return; 
}

int64_t dyn[maxf][10][42], prefix[maxf][10][42], suffix[maxf][10][42]; 
int64_t vsuff[10], vpref[10]; 
int64_t pc[42], sc[42], pv[10], sv[10]; 

int main(void)
{
    string S; 
    cin >> S;
    S = " " + S;  
    int N = S.length(); 
    int64_t ret = 0; 
    init();
    for(int i = N - 1; i > 0; i--)
    {
        for (int a = 0; a < 10; a++) for (int b = 0; b < 42; b++)
        {
            suffix[i][a][b] += suffix[i + 1][a][b];
            suffix[i][a][b] %= mod; 
        }
        if(!is_vowels(S[i]))
        {
            int c = consonants.find(S[i]); 
            for(int a = 0; a < 10; a++)
            {
                suffix[i][a][c] += vsuff[a]; 
                suffix[i][a][c] %= mod; 
            }
        }
        else vsuff[vowels.find(S[i])]++; 
    }
    for(int i = 1; i < N; i++)
    {
        if(is_vowels(S[i]))
        {
            int64_t ptot = 0, stot = 0; 
            memset(pc, 0, sizeof(pc));
            memset(sc, 0, sizeof(sc)); 
            memset(pv, 0, sizeof(pv)); 
            memset(sv, 0, sizeof(sv)); 
            for(int a = 0; a < 10; a++) if(vowels.find(S[i]) != a) 
            {
                for (int b = 0; b < 42; b++) 
                {
                    ptot += prefix[i - 1][a][b];  ptot %= mod; 
                    stot += suffix[i + 1][a][b];  stot %= mod; 
                    ret += 1LL * prefix[i - 1][a][b] * suffix[i + 1][a][b] % mod; ret  %= mod;  
                    pc[b] += prefix[i - 1][a][b];  pc[b] %= mod; 
                    sc[b] += suffix[i + 1][a][b];  sc[b] %= mod; 
                    pv[a] += prefix[i - 1][a][b];  pv[a] %= mod; 
                    sv[a] += suffix[i + 1][a][b];  sv[a] %= mod; 
                }
            }
            for(int a = 0; a < 10; a++) 
            {
                ret = (mod + ret - 1LL * pv[a] * sv[a] % mod) % mod; 
            }
            for(int b = 0; b < 42; b++) 
            {
                ret = (mod + ret - 1LL * pc[b] * sc[b] % mod) % mod; 
            } 
            ret += 1LL * ptot * stot % mod;
            ret %= mod;  
        }
        for (int a = 0; a < 10; a++) for (int b = 0; b < 42; b++)
        {
            prefix[i][a][b] += prefix[i - 1][a][b];
            prefix[i][a][b] %= mod; 
        }
        if (!is_vowels(S[i]))
        {
            int c = consonants.find(S[i]);
            for (int a = 0; a < 10; a++)
            {
                prefix[i][a][c] += vpref[a];
                prefix[i][a][c] %= mod; 
            }
        }
        else vpref[vowels.find(S[i])]++;
    }
    cout << ret << '\n';
    return 0; 
}
