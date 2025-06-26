#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int) x.size()

class SegmentTree
{
private:
    // Data storage
    vector<int> tree;    // Segment tree
    vector<int> lazy;    // Lazy propagation
    vector<int> array;   // Original array
    int length; // Array length

    // Bitmask operations to access children
    int leftChild(int p) {
        return p << 1;
    }
    int rightChild(int p) {
        return (p << 1) + 1;
    }
    void build(int node, int start, int finish) {
        // cout << "Node: " << node << " " << start << " " << finish << endl;
        if (start == finish) {
            // Leaf node
            tree[node] = array[start];
        }
        else {
            int mid = (start + finish) / 2;
            // Recurse on left child
            build(leftChild(node), start, mid);
            // Recurse on right child
            build(rightChild(node), mid + 1, finish);
            // Parent node
            // This depends on the query type of the Segment Tree (cur: query min)
            tree[node] = min(tree[leftChild(node)], tree[rightChild(node)]);
        }
    }

    void updateRange(int node, int start, int finish, int left, int right, int64_t value)
    {
        // cout << "updateRange " << node << " " << start << " " << finish << " " << left << " " << right << " " << value << endl;

        // Check whether there are pending update
        if (lazy[node] != 0)
        {
            // This node needs to be updated
            // This depends on the type of the Segment Tree (cur: query min, update add)
            tree[node] += lazy[node];
            if (start != finish)
            {
                // Mark left child as lazy
                lazy[leftChild(node)] += lazy[node];
                // Mark right child as lazy;
                lazy[rightChild(node)] += lazy[node];
            }
            lazy[node] = 0; // Mark that lazy update has been done
        }

        // Main process
        if (finish < start || right < start || finish < left)
        {
            // Node range is outside the query range
            return;
        }
        else if (left <= start and finish <= right)
        {
            // Node range is inside the query range
            // This depends on the type of the Segment Tree (cur: query min, update add)
            tree[node] += value;
            if (start != finish)
            {
                // Not leaf node
                lazy[leftChild(node)] += value;  // Create pending update
                lazy[rightChild(node)] += value; // Create pending update
            }
            return;
        }
        else
        {
            int mid = (start + finish) / 2;
            // Recurse on left child
            updateRange(leftChild(node), start, mid, left, right, value);
            // Recurse on right child
            updateRange(rightChild(node), mid + 1, finish, left, right, value);
            // This depends on the type of the Segment Tree (cur: query min)
            tree[node] = min(tree[leftChild(node)], tree[rightChild(node)]);
        }
    }

    int64_t queryRange(int node, int start, int finish, int left, int right)
    {
        if (finish < start || right < start || finish < left)
        {
            // Node range is outside the query range
            return LLONG_MAX;
        }
        else
        {
            // Check whether there are pending update
            if (lazy[node] != 0)
            {
                // This node needs to be updated
                // This depends on the type of the Segment Tree (cur: query min, update add)
                tree[node] += lazy[node];
                if (start != finish)
                {
                    // Mark left child as lazy
                    lazy[leftChild(node)] += lazy[node];
                    // Mark right child as lazy;
                    lazy[rightChild(node)] += lazy[node];
                }
                lazy[node] = 0; // Mark that lazy update has been done
            }

            if (left <= start && finish <= right)
            {
                // Node range is inside the query range
                return tree[node];
            }
            else
            {
                int mid = (start + finish) / 2;
                int64_t leftQuery = queryRange(leftChild(node), start, mid, left, right);
                int64_t rightQuery = queryRange(rightChild(node), mid + 1, finish, left, right);
                // This depends on the query type of the Segment Tree (cur: query min)
                return min(leftQuery, rightQuery);
            }
        }
    };

public:
    SegmentTree(const vector<int> &_array)
    {
        array = _array;
        length = (int)array.size();
        tree.assign(4 * length, 0);
        lazy.assign(4 * length, 0);
        build(1, 0, length - 1);
    }

    void updateElement(int index, int value)
    {
        updateRange(1, 1, length, index, index, value);
    }

    void updateRange(int left, int right, int64_t value)
    {
        updateRange(1, 1, length, left, right, value);
    }

    int64_t queryRange(int left, int right)
    {
        return queryRange(1, 1, length, left, right);
    }
    int64_t query()
    {
        return queryRange(1, 1, length, 1, length);
    }
};

int main(void)
{
    int n, m, q; 
    cin >> n >> m >> q; 
    vector<vector<int>>perf; 
    vector<int>x(q), y(q), z(q); 
    vector<int>a(n);
    vector<int>r(m + 1);  
    for(int i = 0; i < n; i++) { 
        cin >> a[i]; 
    }
    int d = a[0]; 
    perf.push_back({}); 
    for(int i = 1; i <= m; i++) {
        cin >> r[i]; 
        vector<int>cc{-1}; 
        for(int j = 0, rr = 0; j < r[i]; j++)
        {
            cin >> rr;
            cc.push_back(rr);  
        }
        perf.push_back(cc); 
    }
    for (int i = 0; i < q; i++)
    {
        cin >> x[i] >> y[i] >> z[i];
    }
    vector<int>hi(m + 1); 
    for(int i = 0; i < n; i++)
    {
        hi[0] += (a[i] >= d); 
    }
    for(int i = 1; i <= m; i++) for(int j = 1; j <= r[i]; j++) { 
        hi[i] += (perf[i][j] >= d); 
    }
    int prefix = 0; 
    vector<int>rem(m); 
    for(int i = 0; i < m; i++)
    {
        prefix += hi[i];
        rem[i]  = n - prefix - r[i + 1];
    }
    SegmentTree ds(rem); 
    int cret = (ds.query() >= 0); 
    for(int i = 0; i < q; i++) {
        int ret = 0;  
        if(perf[x[i]][y[i]] > d && z[i] < d) {
            ds.updateRange(x[i] + 1, sz(rem), 1); 
            ret = (ds.query() >= 0); 
        }
        else if(perf[x[i]][y[i]] < d && z[i] > d) {
            ds.updateRange(x[i] + 1, sz(rem), -1);
            ret = (ds.query() >= 0);
        }
        else 
        {
            ret = cret; 
        }
        cout << ret << '\n'; 
        perf[x[i]][y[i]] = z[i]; 
        cret = ret; 
    }
    return 0;
}