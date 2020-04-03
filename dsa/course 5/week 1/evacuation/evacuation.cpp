#include <iostream>
#include <vector>
#include <map>
#include <limits.h>
#include <math.h>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

/* This class implements a bit unusual scheme for storing edges of the graph,
 * in order to retrieve the backward edge for a given edge quickly. */
class FlowGraph
{
public:
    struct Edge
    {
        int from, to, capacity, flow;
    };

private:
    /* List of all - forward and backward - edges */
    vector<Edge> edges;

    /* These adjacency lists store only indices of edges in the edges list */
    vector<vector<size_t>> graph;

public:
    explicit FlowGraph(size_t n) : graph(n) {}

    void add_edge(int from, int to, int capacity)
    {
        /* Note that we first append a forward edge and then a backward edge,
         * so all forward edges are stored at even indices (starting from 0),
         * whereas backward edges are stored at odd indices in the list edges */
        Edge forward_edge = {from, to, capacity, 0};
        Edge backward_edge = {to, from, 0, 0};
        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);
        graph[to].push_back(edges.size());
        edges.push_back(backward_edge);
    }

    size_t size() const
    {
        return graph.size();
    }

    const vector<size_t> &get_ids(int from) const
    {
        return graph[from];
    }

    const Edge &get_edge(size_t id) const
    {
        return edges[id];
    }

    void add_flow(size_t id, int flow)
    {
        /* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
         * due to the described above scheme. On the other hand, when we have to get a "backward"
         * edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
         * should be taken.
         *
         * It turns out that id ^ 1 works for both cases. Think this through! */
        edges[id].flow += flow;
        edges[id ^ 1].flow -= flow;
    }
};

FlowGraph read_data()
{
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    FlowGraph graph(vertex_count);
    for (int i = 0; i < edge_count; ++i)
    {
        int u, v, capacity;
        std::cin >> u >> v >> capacity;
        graph.add_edge(u - 1, v - 1, capacity);
    }
    return graph;
}

int max_flow(FlowGraph &graph, int from, int to)
{
    while (true)
    {
        bool reach_end = false;
        vector<bool> visited(to + 1, false);
        vector<int> ids(to + 1);
        queue<int> q;
        stack<int> vis_order;
        q.push(from);
        visited[from] = true;
        while (!q.empty())
        {
            int k = q.front();
            q.pop();
            for (auto id : graph.get_ids(k))
            {
                auto edge = graph.get_edge(id);
                if ((!visited[edge.to]) && edge.capacity - edge.flow > 0)
                {
                    q.push(edge.to);
                    visited[edge.to] = true;
                    ids[edge.to] = id;
                }
                if (visited[to])
                {
                    reach_end = true;
                    break;
                }
            }
        }
        if (!reach_end)
            break;
        int crr_node = to;
        int min_flow = INT_MAX;
        while (crr_node)
        {
            int id = ids[crr_node];
            vis_order.push(id);
            auto edge = graph.get_edge(id);
            crr_node = edge.from;
            min_flow = min(edge.capacity - edge.flow, min_flow);
        }
        while (!vis_order.empty())
        {
            graph.add_flow(vis_order.top(), min_flow);
            vis_order.pop();
        }
    }
    int max_flow = 0;
    for (auto id : graph.get_ids(0))
    {
        auto edge = graph.get_edge(id);
        max_flow += edge.flow;
    }
    return max_flow;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    FlowGraph graph = read_data();

    std::cout << max_flow(graph, 0, graph.size() - 1) << "\n";
    return 0;
}
