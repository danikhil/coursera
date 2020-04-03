#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
};

struct ConvertGSMNetworkProblemToSat {
    int numVertices;
    vector<Edge> edges;
    const int num_color=3;

    ConvertGSMNetworkProblemToSat(int n, int m) :
        numVertices(n),
        edges(m)
    {  }

    void printEquisatisfiableSatFormula() {
        // This solution prints a simple satisfiable formula
        // and passes about half of the tests.
        // Change this function to solve the problem.

        const int C = num_color*edges.size()+numVertices;
        const int V = numVertices*num_color;

        cout << C << ' ' << V << '\n';
        
        for (int j = 0, cnt = 1; j < numVertices; ++j, cnt += num_color) {
            cout << cnt << ' ' <<  cnt + 1 << ' ' << cnt + 2 << " 0\n";
        }

        for (const Edge& e : edges) {
            cout <<  -((e.from - 1) * num_color + 1) << ' ' << -((e.to - 1) * num_color + 1) << " 0\n";
            cout <<  -((e.from - 1) * num_color + 2) << ' ' << -((e.to - 1) * num_color + 2) << " 0\n";
            cout <<  -((e.from - 1) * num_color + 3) << ' ' << -((e.to - 1) * num_color + 3) << " 0\n";
        }

    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertGSMNetworkProblemToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> converter.edges[i].from >> converter.edges[i].to;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
