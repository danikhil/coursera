#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> g, gt;
vector<bool> used;
vector<int> order, comp;
vector<bool> assignment;

void dfs1(int v) {
    used[v] = true;
    for (int u : g[v]) {
        if (!used[u])
            dfs1(u);
    }
    order.push_back(v);
}

void dfs2(int v, int cl) {
    comp[v] = cl;
    for (int u : gt[v]) {
        if (comp[u] == -1)
            dfs2(u, cl);
    }
}

bool solve_2SAT() {
    used.assign(n, false);
    for (int i = 0; i < n; ++i) {
        if (!used[i])
            dfs1(i);
    }

    comp.assign(n, -1);
    for (int i = 0, j = 0; i < n; ++i) {
        int v = order[n - i - 1];
        if (comp[v] == -1)
            dfs2(v, j++);
    }

    assignment.assign(n / 2, false);
    for (int i = 0; i < n; i += 2) {
        if (comp[i] == comp[i + 1])
            return false;
        assignment[i / 2] = comp[i] > comp[i + 1];
    }
    return true;
}

int main()
{
    int m;
    cin >> n >> m;
    n = 2*n;
    g = vector<vector<int> > (n, vector<int>());
    gt = vector<vector<int> > (n, vector<int>());
    for(int i=0;i<m;i++)
    {
        int u,v;
        cin >> u >> v;
        int u_prime, v_prime;
        if(u<0)
        {
            u_prime = 2*(abs(u)-1);
            u = u_prime+1;
        }
        else
        {
            u = 2*(u-1);
            u_prime=u+1;
        }
        if(v<0)
        {
            v_prime = 2*(abs(v)-1);
            v = v_prime+1;;
        }
        else
        {
            v = 2*(v-1);
            v_prime = v+1;
        }
        g[u_prime].push_back(v);
        g[v_prime].push_back(u);
        gt[v].push_back(u_prime);
        gt[u].push_back(v_prime); 
    }
    bool possible = solve_2SAT();
    if(possible)
    {
        cout << "SATISFIABLE\n";
        for(int i=0;i<n/2;i++)
        {
            if(assignment[i])
            cout << i+1 << ' ';
            else
            cout << -(i+1) << ' ';
        }
    }
    else
    cout << "UNSATISFIABLE";
    return 0;
}