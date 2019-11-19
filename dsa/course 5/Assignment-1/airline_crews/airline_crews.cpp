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
  int row_num, col_num;

private:
  /* List of all - forward and backward - edges */
  vector<Edge> edges;

  /* These adjacency lists store only indices of edges in the edges list */
  vector<vector<size_t>> graph;

public:
  explicit FlowGraph(int row, int col) : graph(row + col + 2), row_num(row), col_num(col) {}

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
  int num_row, num_col;
  std::cin >> num_row >> num_col;
  FlowGraph graph(num_row, num_col);
  for (int i = 1; i <= num_row; ++i)
  {
    graph.add_edge(0, i, 1);
    for (int j = 1; j <= num_col; j++)
    {
      int bit;
      cin >> bit;
      if (bit)
        graph.add_edge(i, num_row + j, 1);
    }
  }
  for (int j = 1; j <= num_col; j++)
    graph.add_edge(num_row + j, num_row + num_col + 1, 1);
  return graph;
}

vector<int> get_crew(FlowGraph &graph, int from, int to)
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
      //vector<int> nodes_to_push;
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
  vector<int> crew_number;
  for (int i = 1; i <= graph.row_num; i++)
  {
    for (auto id : graph.get_ids(i))
    {
      auto edge = graph.get_edge(id);
      if (edge.flow && edge.to > graph.row_num && edge.to <= graph.row_num + graph.col_num)
        crew_number.push_back(edge.to - graph.row_num);
    }
    if (crew_number.size() < i)
      crew_number.push_back(-1);
  }
  // for (int i = 1; i <= graph.row_num; i++)
  // {
  //   int flow = 0;
  //   for (auto id : graph.get_ids(i))
  //   {
  //     auto edge = graph.get_edge(id);
  //     flow += edge.flow;
  //   }
  //   if (flow)
  //     crew_number.push_back(flow);
  //   else
  //   {
  //     crew_number.push_back(-1);
  //   }
  // }
  return crew_number;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  FlowGraph graph = read_data();
  for (auto i : get_crew(graph, 0, graph.row_num + graph.col_num + 1))
    cout << i << ' ';
  return 0;
}
