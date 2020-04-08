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

Route optimal_hamiltonian_cycle(const Matrix &graph) {

    int size = graph.size();
    vector<vector<Route>> tour_data;
    int t_size = 1<<size;
    tour_data = vector<vector<Route>> (t_size, vector<Route>(size,Route(INF)));

    for(int i=1;i<size;i++)
    {
        tour_data[0][i] = Route(graph[0][i], 0);
    }


    for(int from=1;from<size;from++)
    {
        for(int p_perm = 3; p_perm < t_size; p_perm++)
        {
            if(p_perm==t_size-1)
            {
                from=0;
            }
            else if( (p_perm&1)==0 || (p_perm&(1<<from)))
            continue;
            bitset<18> b(p_perm);
            for(int to=1;to<size;to++)
            {
                if(b[to]==0)
                continue;
                int new_perm = p_perm ^ (1<<to);
                tour_data[p_perm][to].min_route(tour_data[new_perm][to], graph[to][from]);
                tour_data[p_perm][to].landmarks.push_back(to);
            }
        }
    }
    return tour_data[t_size-1][0];
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