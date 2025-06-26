#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    string S, T;
    while (cin >> S >> T)
    {
        S = " " + S;
        int N = S.length();
        int M = T.length();
        vector<vector<int>> pos(N, vector<int>(26, -1));
        vector<int> cnt(26);
        for (int i = 1; i < N; i++)
        {
            for (int j = i - 1; j >= 0; j--)
            {
                pos[j][S[i] - 'a'] = i;
                if (S[i] == S[j])
                    break;
            }
        }
        for (int i = 0; i < M; i++)
        {
            cnt[T[i] - 'a']++;
        }
        auto tryit = [&](int p, int at)
        {
            vector<int> curr(cnt.begin(), cnt.end());
            for (int _ = p; _ < M; _++)
            {
                pair<int, int> res = {N, -1};
                for (int ch = 0; ch < 26; ch++)
                {
                    if (pos[at][ch] == -1 || curr[ch] == 0) continue;
                    res = min(res, {pos[at][ch], ch});
                }
                if (res.first == N) return false;
                curr[res.second]--;
                at = pos[at][res.second];
            }
            if (*max_element(curr.begin(), curr.end()) == 0) return true;
            return false;
        };
        int at = 0;
        string ret;
        if (!tryit(0, 0))
        {
            puts("-1");
            goto done;
        }
        for (int i = 0; i <= M; i++)
        {
            for (int ch = 0; ch < 26; ch++)
            {
                if (cnt[ch] == 0 || pos[at][ch] == -1) continue;
                cnt[ch]--;
                if (tryit(i, pos[at][ch]))
                {
                    ret += (char)(ch + 'a');
                    at = pos[at][ch];
                    break;
                }
                cnt[ch]++;
            }
        }
        cout << ret << '\n';
    }
done:
    return 0;
}