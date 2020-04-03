#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

#define fast ios_base::sync_with_stdio(false)

int find_height(vector<vector<int>> &tree, int node)
{
    if (tree[node].empty())
        return 0;
    int s = 0;
    for (int i = 0; i < tree[node].size(); i++)
        s = max(s, 1 + find_height(tree, tree[node][i]));
    return s;
}

int main()
{
    fast;
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    vector<vector<int>> tree(100001);
    int root;
    for (int i = 0; i < n; i++)
    {
        if (v[i] == -1)
            root = i;
        else
        {
            tree[v[i]].push_back(i);
        }
    }
    cout << find_height(tree, root) + 1;
    return 0;
}