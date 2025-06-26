#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 10;
const int64_t INF = 1e18; 

map<int, int>ctr[maxf]; 
vector<int>ing[maxf]; 
int a[maxf]; 

int main(void)
{
    int N, S, M, D, K; 
    while(cin >> N >> S >> M >> D >> K)
    {
        for(int i = 1; i <= N; i++) cin >> a[i]; 
        for(int i = 1; i <= S + M + D; i++)
        {
            int k; 
            cin >> k; 
            for(int j = 0; j < k; j++)
            {
                int x;
                cin >> x; 
                ing[i].push_back(x); 
            }
        }
        for(int i = 0; i < K; i++)
        {
            int U, V; 
            cin >> U >> V; 
            ctr[U][V] = ctr[V][U] = 1; 
        }
        int64_t ret = 0; 
        for(int i = 1; i <= S; i++) for(int j = S + 1; j <= S + M; j++) for(int k = S + M + 1; k <= S + M + D; k++)
        {
            if(ctr[i][j] || ctr[j][k] || ctr[k][i]) continue; 
            set<int>s; 
            for(auto it : ing[i]) s.insert(it); 
            for(auto it : ing[j]) s.insert(it); 
            for(auto it : ing[k]) s.insert(it); 
            int64_t curr = 1; 
            for(auto it : s) 
            {
                if(log(curr) + log(a[it]) > log(INF))
                {
                    cout << "too many" << '\n'; 
                    goto done; 
                }
                curr = curr * a[it];
            }
            if(ret > INF - curr)
            {
                cout << "too many" << '\n'; 
                goto done; 
            }           
            ret += curr; 
        }
        cout << ret << '\n'; 
    done:; 
    }
    return 0; 
}