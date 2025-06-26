#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int MAXN = 2e5 + 10;
string s[MAXN];
int n;
struct Node
{
    Node *c[10];
};
Node *root = new Node();
void insert(Node *node, string &s, int pos, int L)
{
    if (pos == L)
        return;
    if (!node->c[s[pos] - '0'])
        node->c[s[pos] - '0'] = new Node();
    insert(node->c[s[pos] - '0'], s, pos + 1, L);
}
string query(Node *node, string &s, int pos, int L)
{
    if (pos == L) return "";
    vector<int> at;
    for (int i = 0; i <= 9; i++)
    {
        if (node->c[i]) at.push_back(i);
    }
    assert(at.size());
    for(int i = at.size() - 1; i >= 0; i--)
    {
        if(at[i] + s[pos] - '0' >= 10) continue;
        int tot = (at[i] + s[pos] - '0');
        return (char)(tot + '0') + query(node->c[at[i]], s, pos + 1, L);
    }
    int tot = (s[pos] - '0' + at[at.size() - 1]) % 10;
    return (char) (tot + '0') + query(node -> c[at[at.size() - 1]], s, pos + 1, L); 
}
signed main(void)
{
    cin >> n;
    int N = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        N = max((int)s[i].length(), N);
    }
    for (int i = 1; i <= n; i++)
    {
        if (s[i].length() == N)
            continue;
        reverse(s[i].begin(), s[i].end());
        while (s[i].length() < N) s[i] += "0";
        reverse(s[i].begin(), s[i].end());
    }
    lint ans = 0;
    insert(root, s[1], 0, N);
    for (int i = 2; i <= n; i++)
    {
        ans = max(ans, stoll(query(root, s[i], 0, N)));
        insert(root, s[i], 0, N);
    }
    cout << ans << '\n';
    return 0;
}