#include <bits/stdc++.h>
using namespace std;

struct Clause {
    int firstVar;
    int secondVar;
};

struct TwoSatisfiability {
    int numVars;
    vector<int> adjList;
    vector<int> radjList;
    vector<int> order, comp;
    vector<bool> visited,assignment;

    TwoSatisfiability(int n, int m) :
        numVars(n), adjList(2*n), radjList(2*n), comp(2*n)
    {  }

    void DFS(int var) {

        int u = var+numVars;
        visited[abs(var)]=1;

        for(auto i:adjList) {

            int v = i+numVars;
            if(visited[abs(v)])
            continue;
            DFS(var);
        }
        s.push(-var);
    }

    bool isSatisfiable(vector<int>& result) {

        visited.assign(numVars,0);
        for(int i=0;i<numVars;i++)
        {
            if(!visited[abs(i)])
            continue;
            DFS(i-numVars);
        }
        for(int i=0;i<numVars;i++)
        {
            result[i]=!graph[numVars+i].set_value;
        }
        return var;
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    TwoSatisfiability twoSat(n, m);
    for (int i = 0; i < m; ++i) {

        int u,v;
        cin >> u >> v;
        if(u<0)
        u=abs(u)+1;
        if(v<0)
        v=abs(v)+1;
        twoSat.adjList[u-1].push_back(v-1);
        twoSat.adjList[v-1].push_back(v-1);
        twoSat.radjList[v-1].push_back(u-1);
    }

    vector<int> result(n);
    if (twoSat.isSatisfiable(result)) {
        cout << "SATISFIABLE" << endl;
        for (int i = 1; i <= n; ++i) {
            if (result[i-1]) {
                cout << -i;
            } else {
                cout << i;
            }
            if (i < n) {
                cout << " ";
            } else {
                cout << endl;
            }
        }
    } else {
        cout << "UNSATISFIABLE" << endl;
    }

    return 0;
}
