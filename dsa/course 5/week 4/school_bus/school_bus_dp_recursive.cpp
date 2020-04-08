/* start from 1111111....111 and goes to 0000000..0001*/

#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int> > Matrix;

const int INF = 1e9;

struct Route {

    int cost;
    vector<int> landmarks;
    Route() {}
    Route(int cost) : cost(cost) {}
    Route(int cost, int v) : cost(cost) {
        landmarks.push_back(v);
    }

    void min_route(const Route &p, int cost) {
        if(this->cost>p.cost + cost)
        {
            this -> cost = p.cost + cost;
            this ->landmarks = p.landmarks;
        }
    }
};

Matrix read_data() {
    int vertex_count, edge_count;
    cin >> vertex_count >> edge_count;
    Matrix graph(vertex_count, vector<int>(vertex_count, INF));
    for (int i = 0; i < edge_count; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        --from, --to;
        graph[from][to] = graph[to][from] = weight;
    }
    return graph;
}

vector<vector<Route>> tour_data;

Route optimal_tour(const Matrix &graph, int v, int path_permutation) {

    if(path_permutation==1)
    {
        return Route(graph[0][v], v);
    }
    if(tour_data[path_permutation][v].cost!=-1)
    return tour_data[path_permutation][v];

    Route min_cost_path(INF);
    bitset<18> path_bits(path_permutation);
    for(int u=1;u<graph.size();u++)
    {
        if(path_bits[u]==0||graph[u][v]>=INF)
        continue;
        int new_permutation = path_permutation ^ (1<<u);
        Route path = optimal_tour(graph, u, new_permutation);
        min_cost_path.min_route(path, graph[u][v]);
    }
    min_cost_path.landmarks.push_back(v);
    tour_data[path_permutation][v] = min_cost_path;
    return tour_data[path_permutation][v];
}

Route optimal_hamiltonian_cycle(const Matrix &graph) {

    int size = graph.size();
    int path_permutation = (1<<size);
    tour_data = vector<vector<Route>> (path_permutation, vector<Route>(size,Route(-1)));

    return optimal_tour(graph,0, path_permutation-1);
}

void print_answer(const Route& answer) {
    std::cout << answer.cost << "\n";
    if (answer.cost == -1)
        return;
    const vector<int>& path = answer.landmarks;
    for (auto it=path.rbegin();it!=path.rend();++it)
        std::cout << *it+1 << " ";
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);

    Matrix graph = read_data();
    Route path = optimal_hamiltonian_cycle(graph);
    if(path.cost>=INF)
    path = Route(-1);
    print_answer(path);
    return 0;
}