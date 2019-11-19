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
  int nodes;

private:
  /* List of all - forward and backward - edges */
  vector<Edge> edges;

  /* These adjacency lists store only indices of edges in the edges list */
  vector<vector<size_t>> graph;

public:
  explicit FlowGraph(int n) : graph(nodes + 2), nodes(n) {}

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

  void update_capacity(size_t id, int flow)
  {
    /* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
         * due to the described above scheme. On the other hand, when we have to get a "backward"
         * edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
         * should be taken.
         *
         * It turns out that id ^ 1 works for both cases. Think this through! */
    edges[id].capacity -= flow;
    edges[id ^ 1].capacity += flow;
  }
};

class StockCharts
{
public:
  void Solve()
  {
    vector<vector<int>> stock_data = ReadData();
    int result = MinCharts(stock_data);
    WriteResponse(result);
  }

private:
  vector<vector<int>> ReadData()
  {
    int num_stocks, num_points;
    cin >> num_stocks >> num_points;
    vector<vector<int>> stock_data(num_stocks, vector<int>(num_points));
    for (int i = 0; i < num_stocks; ++i)
      for (int j = 0; j < num_points; ++j)
      {
        cin >> stock_data[i][j];
      }
    return stock_data;
  }

  void WriteResponse(int result)
  {
    cout << result << "\n";
  }

  int MinCharts(const vector<vector<int>> &stock_data)
  {
    // Replace this incorrect greedy algorithm with an
    // algorithm that correctly finds the minimum number
    // of charts on which we can put all the stock data
    // without intersections of graphs on one chart.

    int num_stocks = stock_data.size();

    FlowGraph charts(2 * num_stocks + 2);

    for (int i = 0; i < num_stocks; i++)
      charts.add_edge(0, i + 1, 1);

    for (int i = 0; i < num_stocks; i++)
    {
      for (int j = i + 1; j < num_stocks; j++)
      {
        if (compare(stock_data[i], stock_data[j]))
          charts.add_edge(i + 1, j + num_stocks + 1, 1);
        else if (compare(stock_data[j], stock_data[i]))
          charts.add_edge(j + 1, i + num_stocks + 1, 1);
      }
    }

    for (int i = num_stocks + 1; i < 2 * num_stocks + 1; i++)
      charts.add_edge(i, 2 * num_stocks + 1, 1);

    while (true)
    {
      bool reach_end = false;
      vector<bool> visited(2 * num_stocks + 2, false);
      vector<int> ids(2 * num_stocks + 2);
      queue<int> q;
      q.push(0);
      visited[0] = true;
      while (!q.empty())
      {
        int k = q.front();
        q.pop();
        //vector<int> nodes_to_push;
        for (auto id : charts.get_ids(k))
        {
          auto edge = charts.get_edge(id);
          if ((!visited[edge.to]) && edge.capacity - edge.flow > 0)
          {
            q.push(edge.to);
            visited[edge.to] = true;
            ids[edge.to] = id;
          }
          if (visited[2 * num_stocks + 1])
          {
            reach_end = true;
            break;
          }
        }
      }
      if (!reach_end)
        break;

      int crr_node = 2 * num_stocks + 1;

      while (crr_node)
      {
        int id = ids[crr_node];
        auto edge = charts.get_edge(id);
        crr_node = edge.from;
        charts.update_capacity(id, 1);
      }
    }

    int res = 0;
    for (auto id : charts.get_ids(0))
    {
      auto edge = charts.get_edge(id);
      if (edge.capacity > 0)
        res++;
    }
    return res;
  }

  bool compare(const vector<int> &stock1, const vector<int> &stock2)
  {
    for (int i = 0; i < stock1.size(); ++i)
      if (stock1[i] >= stock2[i])
        return false;
    return true;
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  StockCharts stock_charts;
  stock_charts.Solve();
  return 0;
}
