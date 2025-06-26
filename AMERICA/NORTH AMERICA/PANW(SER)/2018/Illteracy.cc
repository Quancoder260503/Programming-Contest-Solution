#include "bits/stdc++.h"

using namespace std;

string ord = "ABCDEF"; 
#define LEN 8 

const int maxf = 1e7 + 1; 

int dist[maxf]; 
int pw[LEN + 2]; 

int bfs(const string src, const string target)
{
    if (src == target) return 0;
    queue<int>q;
    int fsrc = 0; 
    pw[0] = 1; 
    for(int i = 1; i < LEN; i++)  pw[i] = pw[i - 1] * 7; 
    for(int i = 1; i <= LEN; i++) fsrc += pw[i - 1] * (src[i] - 'A' + 1);
    q.push(fsrc); 
    dist[fsrc] = 1; 
    while(q.size())
    {
        int fu = q.front();
        string u = " "; 
        int su = fu; 
        while(su)
        {
            u += ('A' + su % 7 - 1);
            su = (su - su % 7) / 7;  
        }
        q.pop(); 
        for(int i = 1; i <= LEN; i++)
        {
            string v = u;
            if(u[i] == 'A')
            {
                if(i + 1 <= LEN) v[i + 1] = ord[(ord.find(v[i + 1]) + 1) % 6]; 
                if(i > 1)        v[i - 1] = ord[(ord.find(v[i - 1]) + 1) % 6];
            }
            else if(u[i] == 'B')
            {
                if(1 < i  && i + 1 <= LEN)
                {
                    v[i + 1] = v[i - 1]; 
                }
            }
            else if(u[i] == 'C')
            {
                v[LEN + 1 - i] = ord[(ord.find(v[LEN + 1 - i]) + 1) % 6]; 
            }
            else if(u[i] == 'D')
            {
                if(1 < i && i < 8)
                {
                    if (i - 1 < 8 - i)
                    {
                        for (int j = 1; j <= i - 1; j++)
                            v[j] = ord[(ord.find(v[j]) + 1) % 6];
                    }
                    else
                    {
                        for (int j = i + 1; j <= 8; j++)
                            v[j] = ord[(ord.find(v[j]) + 1) % 6];
                    }
                }
            }
            else if(u[i] == 'E')
            {
                if(1 < i && i < 8)
                {
                    int d = min(i - 1, 8 - i);
                    v[i - d] = ord[(ord.find(v[i - d]) + 1) % 6];
                    v[i + d] = ord[(ord.find(v[i + d]) + 1) % 6];
                }
            }       
            else
            {
                if(i & 1) v[(i + 9) / 2] = ord[(ord.find(v[(i + 9) / 2]) + 1) % 6]; 
                else      v[i / 2]       = ord[(ord.find(v[i / 2])       + 1) % 6]; 
            }
            int64_t fv = 0;
            for (int j = 1; j <= LEN; j++) fv += pw[j - 1] * (v[j] - 'A' + 1);
            if(dist[fv] == 0)
            {
                dist[fv] = dist[fu] + 1; 
                if(v == target) return dist[fv] - 1; 
                q.push(fv); 
            }
        }
    }
    return -1; 
}

int main(void)
{
    string a, b; 
    cin >> a >> b;
    a = " " + a;
    b = " " + b; 
    cout << bfs(a, b) << '\n'; 
    return 0; 
}