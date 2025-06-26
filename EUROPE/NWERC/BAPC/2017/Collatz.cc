#include "bits/stdc++.h"
using namespace std;
const int LOG = 21;
const int MAX = 5e5 + 10;
int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N;
    while (cin >> N)
    {
        vector<int64_t> a(N);
        for (int i = 0; i < N; i++)
        {
            cin >> a[i];
        }
        set<int64_t> cset;
        set<int64_t> ret; 
        for (int i = 0; i < N; i++)
        {
            set<int64_t> nset;
            nset.insert(a[i]);
            for (auto it : cset) nset.insert(gcd(a[i], it));
            for (auto it : nset) ret.insert(it); 
            nset.swap(cset); 
        }
        cout << ret.size() << '\n';
    }
    return 0;
}
