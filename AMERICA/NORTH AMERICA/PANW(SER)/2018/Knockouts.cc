#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int A, B;
    string S; 
    while(cin >> S >> A >> B)
    {
        map<string, pair<double, string>>dyn[7][7][2]; 
        function<pair<double, string>(string, int, int, int)>doit; 
        cout << fixed << setprecision(5);
        doit = [&](string s, int a, int b, int state) -> pair<double, string>
        {
            if(s.length() == 0) return {0.0, "-1"}; 
            if(dyn[a][b][state].count(s)) return dyn[a][b][state][s]; 
            int N   = s.length();
            pair<double, string> ret;
            pair<double, string> ret2 = {1e9, "-1"}; 
            int cont   = false;
            for(int mask = 0; mask < (1 << N); mask++)
            {
                string T = ""; 
                string M = ""; 
                int acc = 0;
                pair<double, string> tret;  
                for(int i = 0; i < N; i++)
                {
                    if(mask & (1 << i)) {acc += (s[i] - '0'); M += s[i];}
                    else T += s[i]; 
                }
                if(acc != a + b) continue;
                cont = true;
                tret.second = M; 
                for(int i = 1; i < 7; i++) for(int j = 1; j < 7; j++)
                {
                    tret.first += doit(T, i, j, state).first; 
                }
                tret.first /= 36.0; 
                if(state) ret  = max(ret, tret);
                else      ret2 = min(ret2, tret);  
            }
            if(!cont) return dyn[a][b][state][s] = {stoi(s) * 1.0, "-1"}; 
            return dyn[a][b][state][s] = (state ? ret : ret2); 
        };
        auto ret = doit(S, A, B, 0); 
        cout << ret.second << " " << ret.first<< '\n'; 
        ret = doit(S, A, B, 1);
        cout << ret.second << " " << ret.first << '\n';
    }
    return 0;
}