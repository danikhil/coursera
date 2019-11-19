#include <iostream>
#include <vector>
#include <map>
#include <limits.h>
#include <math.h>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

class Charts
{
public:
    struct DisjointSet
    {
        int root;
        vector<int> stock;
    };

private:
    vector<DisjointSet> dsu;
    int n, k;

public:
    Charts(int n, int k) : dsu(n), n(n), k(k) {}

    void ReadData()
    {
        for (int i = 0; i < n; i++)
        {
            dsu[i].stock.resize(k);
            for (int j = 0; j < k; j++)
                cin >> dsu[i].stock[j];
        }
        sort(dsu.begin(), dsu.end(), compare);
        for (int i = 0; i < n; i++)
        {
            dsu[i].root = i;
        }
    }

    static bool compare(const DisjointSet &a, const DisjointSet &b)
    {
        for (int i = 0; i < a.stock.size(); ++i)
            if (a.stock[i] >= b.stock[i])
                return false;
        return true;
    }

    int find_root(vector<DisjointSet> &dsu, int node)
    {
        while (dsu[node].root != node)
        {
            dsu[node].root = dsu[dsu[node].root].root;
            node = dsu[node].root;
        }
        return node;
    }

    bool set_union(vector<DisjointSet> &dsu, int x, int y)
    {
        int root_x = find_root(dsu, x);
        int root_y = find_root(dsu, y);
        if (root_x == root_y)
            return false;
        if (compare(dsu[root_y], dsu[root_x]))
        {
            dsu[root_y].root = root_x;
            return true;
        }
        else if (compare(dsu[root_x], dsu[root_y]))
        {
            dsu[root_x].root = root_y;
            return true;
        }
        else
        {
            return false;
        }
    }

    int solve()
    {
        //cout << '\n';
        // for (int i = 0; i < n; i++)
        // {
        //     for (int j = 0; j < k; j++)
        //         cout << dsu[i].stock[j] << ' ';
        //     cout << '\n';
        // }
        // cout << '\n';
        for (int i = 0; i < n - 1; i++)
        {
            int j = find_root(dsu, i) + 1;
            while (j < n)
            {
                if (set_union(dsu, i, j))
                    j = find_root(dsu, i) + 1;
                else
                {
                    j++;
                }
                // << '\n';
            }
            //cout << '\n';
        }

        vector<bool> check(n, false);
        for (int i = 0; i < n; i++)
        {
            check[find_root(dsu, i)] = true;
        }
        int c = 0;
        for (int i : check)
            if (i)
                c++;
        return c;
    }
};

int main()
{
    int n, k;
    cin >> n >> k;
    Charts stock_chart(n, k);
    stock_chart.ReadData();
    cout << stock_chart.solve();
    return 0;
}