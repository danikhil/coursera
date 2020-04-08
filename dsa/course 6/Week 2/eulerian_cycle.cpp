#include <bits/stdc++.h>
using namespace std;

typedef vector<forward_list<int> > Graph;

vector<int> eulerian_cycle(Graph &graph)
{
    stack<int> path;
    vector<int> cycle;
    int nodes = graph.size();

    int start_vetrex=0;

    path.push(start_vetrex);

    while(!path.empty())
    {
        if(graph[start_vetrex].empty())
        {
            cycle.push_back(start_vetrex);
            start_vetrex = path.top();
            path.pop();
        }
        else
        {
            path.push(start_vetrex);
            int next = graph[start_vetrex].front();
            graph[start_vetrex].pop_front();
            start_vetrex = next;
        }
    }
    return vector<int>(cycle.rbegin(), cycle.rend());    
}

bool check_degrees(const std::vector<int> &in, const std::vector<int> &out)
{
    for(size_t i = 0; i < in.size(); ++i)
        if(in[i] != out[i]) return false;
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int nodes,edges;
    cin >> nodes >> edges;

    Graph graph(nodes);

    vector<int> in(nodes),out(nodes);
    for(int i=0;i<edges;i++)
    {
        int u, v;
        cin >> u >> v;
        graph[--u].push_front(--v);
        in[v]++;
        out[u]++;
    }

    if(!check_degrees(in, out))
    {
        std::cout << 0 << std::endl;
        return 0;
    }

    vector<int> cycle = eulerian_cycle(graph);

    cout << 1 << '\n';
    for(int i=0;i<cycle.size()-1;i++)
    cout << cycle[i]+1 << ' ';
    
    return 0;
}