#include "bits/stdc++.h"

using namespace std;

#define sz(x) x.size()

struct AhoCorasick
{
   enum
   {
      alpha = 26,
      first = 'a'
   }; // change this!
   struct Node
   {
      // (nmatches is optional)
      int back, next[alpha], start = -1, end = -1, nmatches = 0;
      Node(int v) { memset(next, v, sizeof(next)); }
   };
   vector<Node> N;
   vector<int>len; 
   vector<int> backp;
   void insert(string &s, int j)
   {
      assert(!s.empty());
      int n = 0;
      for (char c : s)
      {
         int &m = N[n].next[c - first];
         if (m == -1)
         {
            n = m = sz(N);
            N.emplace_back(-1);
         }
         else
            n = m;
      }
      if (N[n].end == -1)
         N[n].start = j;
      backp.push_back(N[n].end);
      N[n].end = j;
      N[n].nmatches++;
   }
   AhoCorasick(vector<string> &pat) : N(1, -1)
   {
      len.resize(sz(pat)); 
      for(int i = 0; i < sz(pat); i++) 
      {
         insert(pat[i], i);
         len[i] = (int) pat[i].length(); 
      }
      N[0].back = sz(N);
      N.emplace_back(0);

      queue<int> q;
      for (q.push(0); !q.empty(); q.pop())
      {
         int n = q.front(), prev = N[n].back;
         for(int i = 0; i < alpha; i++)
         {
            int &ed = N[n].next[i], y = N[prev].next[i];
            if (ed == -1)
               ed = y;
            else
            {
               N[ed].back = y;
               (N[ed].end == -1 ? N[ed].end : backp[N[ed].start]) = N[y].end;
               N[ed].nmatches += N[y].nmatches;
               q.push(ed);
            }
         }
      }
   }
   string find_ret(string word)
   {
      string ret;
      vector<int>st;
      st.push_back(0); 
      for(char c : word)
      {
         int cc = N[st.back()].next[c - first];
         ret += c;
         st.push_back(cc);
         if(N[cc].end != -1)
         {
            ret.resize(ret.size() - len[N[cc].end]); 
            st.resize(st.size()   - len[N[cc].end]); 
         }
      }
      return ret; 
   }
   vector<int> find(string word)
   {
      int n = 0;
      vector<int> res; // ll count = 0;
      for (char c : word)
      {
         n = N[n].next[c - first];
         res.push_back(N[n].end);
         // count += N[n].nmatches;
      }
      return res;
   }
   vector<vector<int>> findAll(vector<string> &pat, string word)
   {
      vector<int> r = find(word);
      vector<vector<int>> res(sz(word));
      for(int i = 0; i < sz(word); i++)
      {
         int ind = r[i];
         while (ind != -1)
         {
            res[i - sz(pat[ind]) + 1].push_back(ind);
            ind = backp[ind];
         }
      }
      return res;
   }
};

int main(void)
{ 
   string Word; 
   cin >> Word; 
   int N;
   cin >> N;
   vector<string>pat(N); 
   for(int i = 0; i < N; i++)
   {
      cin >> pat[i]; 
   }
   AhoCorasick aho(pat); 
   cout << aho.find_ret(Word) << '\n'; 
   return 0; 
}









