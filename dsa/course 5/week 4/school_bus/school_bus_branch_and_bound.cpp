#include<bits/stdc++.h>

using std::vector;
typedef vector<vector<int> > Matrix;

const int INF = 1e9;

Matrix read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    Matrix graph(vertex_count, vector<int>(vertex_count, INF));
    for (int i = 0; i < edge_count; ++i) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        --from, --to;
        graph[from][to] = graph[to][from] = weight;
    }
    return graph;
}

int first_min(const Matrix &graph, int i) {

    int mn=INF;
    for(int k=0;k<graph.size();k++)
    {
        if(i!=k)
        mn=std::min(mn, graph[i][k]);
    }
    return mn;
}

int second_min(const Matrix &graph, int i) {

    int f_mn=INF,s_mn=INF;

    for(int k=0;k<graph.size();k++)
    {
        if(i==k)
        continue;
        if(graph[i][k]<=f_mn)
        {
            f_mn=graph[i][k];
            s_mn=f_mn;
        }
        else if(graph[i][k]<s_mn)
        s_mn=graph[i][k];
    }    
    return s_mn;
}

std::pair<int, vector<int> > ans = {INF, vector<int>()};

void optimal_path(const Matrix& graph, int u, vector<int> reached, int min_cost, std::bitset<18> b, int curr_bound) {
    
    reached.push_back(u);
    b[u]=1;
    if(reached.size()==graph.size())
    {
        min_cost += graph[u][0];
        if(ans.first>min_cost)
        {
            ans.first = min_cost;
            ans.second = reached;
        }
        return ;
    }
    for(int v=0;v<graph.size();v++)
    {
        if(b[v]==1||graph[u][v]==INF)
        continue;
        int temp=curr_bound;
        if (reached.size()==1) 
            curr_bound -= (first_min(graph, reached.back()) + first_min(graph, v))/2; 
        else
            curr_bound -= (second_min(graph, reached.back()) + first_min(graph, v))/2;
        if(curr_bound+graph[u][v]<ans.first)
        {
            optimal_path(graph, v, reached, min_cost+graph[u][v], b, curr_bound);
        }
        temp=curr_bound;
    }
    return ;
}

void print_answer(const std::pair<int, vector<int> >& answer) {
    std::cout << answer.first << "\n";
    if (answer.first == -1)
        return;
    const vector<int>& path = answer.second;
    for (size_t i = 0; i < path.size(); ++i)
        std::cout << path[i]+1 << " ";
    std::cout << "\n";
}

int main() {
    std::bitset<18> b(0);
    int curr_bound=0;
    Matrix graph=read_data();
    for (int i=0; i<graph.size(); i++) 
    curr_bound += first_min(graph, i) + second_min(graph, i); 
  
    curr_bound = (curr_bound&1)? curr_bound/2 + 1 : curr_bound/2;
    optimal_path(graph, 0, vector<int>(), 0, b, curr_bound);
    if(ans.first>=INF)
    ans.first=-1;
    print_answer(ans);
    return 0;
}
